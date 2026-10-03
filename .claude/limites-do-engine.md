# Limites do engine: objetos, sprites, paletas, VRAM, save e RAM

Análise de 30/09/2026 (branch `rift-mission-v1-complete`). **Etapa A
aplicada em 02/10/2026**: 24 objetos, 96 sprites, OAM 128 (detalhes no fim).
Os números mudam com o código: **meça de novo antes de agir** com os dois
scripts:

```bash
dev_scripts/medir_limites_ram_save.sh            # save, sprites, EWRAM/IWRAM (precisa de make antes)
python3 dev_scripts/limites_janela_objetos.py    # pior janela de spawn por mapa
```

Premissa do projeto: **emulator-only** (só roda no mGBA patchado de
`tools/mgba-master`). Compatibilidade com saves antigos **não** importa, e
dá para mudar o mGBA (RAM, save, CPU) quando isso trouxer um limite melhor.
Fidelidade ao GBA real não é requisito.

## Mapa dos limites

| Limite | Valor | Onde | Natureza | Sobe? |
|---|---|---|---|---|
| Objetos carregados | 24 (jogador + follower inclusos) | `OBJECT_EVENTS_COUNT`, `include/constants/global.h` | software | sim |
| Templates por mapa | 64 | `OBJECT_EVENT_TEMPLATES_COUNT` | software (vai no save: 24 B cada) | sim, custa save |
| Sprites | 96 | `MAX_SPRITES`, `include/sprite.h` | software | sim, até 127 |
| Entradas de OAM por frame | 128 | `gOamLimit = 128` em `ResetSpriteData`, `src/sprite.c` | software (hardware = 128) | sim, até 128 |
| Paletas de sprite | 16 slots | `sSpritePaletteTags[16]`, `src/sprite.c` | **hardware** (4 bits no attr2 do OAM) | não |
| VRAM de sprite | 1024 tiles | `sSpriteTileAllocBitmap[128]` | **hardware** (índice de 10 bits) | não |
| Flash (save) | 128 KB = 32 setores, todos usados | `include/save.h` | cartucho | sim, via mGBA |
| EWRAM / IWRAM | 256 KB / 32 KB | `ld_script_modern.ld` | hardware | sim, via mGBA (caro) |

O patch que o mGBA já tem ("ROM linear de 96 MiB") só mexe no
mapeamento da ROM. Ele **não** muda RAM, save, sprites nem PPU.

## 1. Objetos simultâneos (`OBJECT_EVENTS_COUNT`)

O limite vale para a **janela de spawn**, não para o mapa inteiro.
`TrySpawnObjectEvents` (`src/event_object_movement.c`) carrega só os
templates num retângulo de 20 × 17 tiles em volta do jogador: x em
[P-9, P+10] e y em [P-7, P+9]. Quem sai da janela é descarregado. Quando
o array enche, o NPC excedente **simplesmente não aparece**, sem erro.

### O que quebra se só trocar o número

1. **`applymovement` / `waitmovement` travam.** Veja
   `src/script_movement.c`: a task `ScriptMovement_MoveObjects` guarda
   - em `data[0]` uma máscara **u16** de "terminou" (`1u << moveScrId`);
   - em `data[1..]` os IDs de objeto, um byte cada. A task tem
     `NUM_TASK_DATA = 16` s16, ou seja 30 bytes úteis.

   Com mais de 16 objetos, o bit ≥ 16 some e o objeto nunca termina, então
   o `waitmovement` fica preso. Com mais de 30, os IDs estouram a task.
   **Conserto:** tirar isso da task e usar arrays próprios em EWRAM:
   `static EWRAM_DATA u8 sMoveObjEventIds[OBJECT_EVENTS_COUNT]` e
   `static EWRAM_DATA bool8 sMoveFinished[OBJECT_EVENTS_COUNT]`, ao lado do
   `sMovementScripts` que já existe. Ou então um `u32`/bitmap com
   `STATIC_ASSERT(OBJECT_EVENTS_COUNT <= 32)`. Isso compila limpo e trava
   no jogo: o teste em runtime é obrigatório.

2. **Save.** `SaveBlock1.objectEvents[OBJECT_EVENTS_COUNT]` fica no
   **meio** da struct (offset 0xA30), antes de flags e vars. O `save.c` tem
   `STATIC_ASSERT`s de offset (`registeredItems == 0x3484`,
   `pokemonStorageExtensionTail == 0x349A`, `futureReserved == 0x3C32`,
   `sizeof == 0x3C54`), porque as caixas 16–19 do PC usam essas posições
   (código do upstream Eemeliri). Crescer o array ali desloca tudo e
   quebra os asserts e a lógica das caixas extras.

   **Faça assim:** mantenha `objectEvents[16]` onde está e acrescente
   `struct ObjectEvent objectEventsExtra[OBJECT_EVENTS_COUNT - 16];` **no
   fim** do `SaveBlock1`, depois de `futureReserved`. Atualize só o assert
   `SaveBlock1LegacySize`. `SaveObjectEvents`/`LoadObjectEvents`
   (`src/load_save.c`) passam a copiar os índices ≥ 16 para o array extra,
   com o mesmo swap de bytes do `graphicsId` e o mesmo tratamento do
   follower.

   Orçamento: `ObjectEvent` = 36 B. Sobram 428 B no último setor do
   SaveBlock1, então cabem **+11 (máximo 27)** sem aumentar o save. O
   tamanho do chunk é `sizeof`, então o checksum cobre o que foi
   acrescentado sem mudança extra. Confirme ainda que nada escreve no
   `gReadWriteSector->data` além do chunk do SaveBlock1 no setor 4
   (`CopyPokemonStorageExtensionTailToSaveSector` escreve **dentro** da
   struct).

3. **Os outros ~100 usos** da constante são laços `i < OBJECT_EVENTS_COUNT`
   ou o próprio valor usado como "nenhum", e funcionam sem mudança. Revise
   só:
   - `u8` usado como índice: vai até 255, então está ok;
   - `trainer_see.c` (`trainerObjects[OBJECT_EVENTS_COUNT]`);
   - `follower_npc.c` (`objId == OBJECT_EVENTS_COUNT` = sem follower);
   - `field_mugshot.c`;
   - `rotating_tile_puzzle.c`.

   Os `16` literais soltos em `field_weather.c`, `field_effect_helpers.c`,
   `overworld.c:UpdatePalettesWithTime` e `field_screen_effect.c` são de
   **paleta**, não de objeto. Não mexa.

   ```bash
   grep -rn "OBJECT_EVENTS_COUNT" src include
   grep -rnE "\b(i|j) *< *16\b" src/event_object_movement.c src/field_*.c src/overworld.c src/script*.c src/scrcmd.c
   ```

## 2. Sprites (`MAX_SPRITES`) e OAM (`gOamLimit`)

Com `OW_OBJECT_VANILLA_SHADOWS FALSE` (`include/config/overworld.h`),
**cada objeto gasta 2 sprites**: o boneco e a sombra. Somam no mesmo pool:
- clima: chuva 24, neve 16, areia 20+5, névoa/cinzas 20
  (`include/constants/field_weather.h`);
- grama, pegadas, reflexos, DexNav e a interface.

| Cenário | Sprites |
|---|---|
| hoje: 16 obj × 2 + chuva | 32 + 24 = 56 de 64 |
| 24 obj × 2 + chuva | 48 + 24 = 72: **estoura** |

Quando estoura, `CreateSprite` devolve `MAX_SPRITES`. O objeto não
aparece ou o clima fica com falhas, sem erro. Por isso `MAX_SPRITES`
precisa subir **junto** com os objetos.

- `MAX_SPRITES` ≤ **127**: `party_menu.c`/`swsh_party_menu.c` guardam ID de
  sprite em bitfield de 7 bits, e o próprio `MAX_SPRITES` serve de
  sentinela. 96 é um valor confortável.
- Custo: `struct Sprite` = 68 B, então +32 sprites = ~2,2 KB de EWRAM.
  `sSpriteOrder`, `sSpriteCopyRequests`, `sSpriteTileRangeTags` etc. são
  dimensionados pela constante.
- `gOamLimit = 64` em `ResetSpriteData` é **outro** teto: entradas de OAM
  por frame. Sprite com subsprites gasta várias entradas. Suba para 128
  (o máximo do hardware; `gMain.oamBuffer[128]`; `slot_machine.c` já usa
  0x80).
- Limite de pixels de sprite por scanline: com 16 px de largura cabem ~59
  sprites na mesma linha. Não é problema.

## 3. Paletas de sprite: 16 slots (hardware)

O OAM só tem 4 bits de paleta, e isso não sobe sem estender a PPU. No
overworld as paletas são **dinâmicas por tag** (`LoadSpritePalette` pega
o primeiro slot livre; `InitObjectEventPalettes` não é chamada). Quem
disputa os 16 slots:
- jogador;
- as 4 paletas comuns de NPC (`OBJ_EVENT_PAL_TAG_NPC_1..4`), divididas por
  quase todo NPC;
- **cada** NPC com paleta própria;
- **cada espécie** de Pokémon de overworld ou follower
  (`OW_PKMN_OBJECTS_SHARE_PALETTES FALSE`);
- efeitos de campo e reflexos.

Quando falta slot, o índice vira 0xFF e o boneco aparece **com a cor
errada**.

**É o próximo teto a estourar em cena com muitos Pokémon diferentes**
(a janela de NewBarkTown tem 14 espécies, mesmo que por flag não
apareçam todas juntas). Mitigação, não aumento:
- NPC novo usa `NPC_1..4` sempre que der (skill `adicionar-npc`);
- espécies repetidas dividem a paleta;
- evite cenas com mais de ~8 espécies diferentes visíveis.

A coluna `especies` do `limites_janela_objetos.py` mostra o risco.

## 4. VRAM de sprite: 1024 tiles (hardware)

O índice de tile tem 10 bits. Quem gasta:
- **NPC comum** (`.compressed = FALSE`): só o quadro atual por sprite,
  8 tiles (16x32) ou 16 tiles (32x32). É barato.
- **Pokémon de overworld e followers** (`OW_GFX_COMPRESS TRUE`): a
  **folha inteira** por espécie, dividida por tag. Ver
  `LoadSheetGraphicsInfo` em `event_object_movement.c`.

Quando falta VRAM, `tileStart <= 0` e o objeto fica
`invisible = TRUE`: aparece invisível, sem erro. O risco é o mesmo das
paletas, ou seja, muitas espécies diferentes na tela.

## 5. Save: flash de 128 KB, cheio

`include/save.h` mostra os 32 setores de 4 KB todos ocupados:

| Setores | Uso |
|---|---|
| 0–13 | slot 1 |
| 14–27 | slot 2 |
| 28–29 | caixa 19 e Hall of Fame (reaproveitados; eram HoF/Trainer Hill) |
| 30–31 | overflow das caixas extras (eram Recorded Battle) |

`SaveBlock2` tem ~1,2 KB livres. `SaveBlock1` tem 428 B mais os 34 B de
`futureReserved`.

### Aumentar o save pelo mGBA

O flash de 128 KB já é **2 bancos de 64 KB**, e o jogo já troca de banco
(`SwitchFlashBank` em `src/agb_flash.c`, `SECTORS_PER_BANK 16`). Para
512 KB ou 1 MB basta ter mais bancos.

**mGBA** (`tools/mgba-master/src/gba/savedata.c`):
- `FLASH_COMMAND_SWITCH_BANK` rejeita `value < 2`: aceitar até N bancos;
- tipo novo (ex.: `GBA_SAVEDATA_FLASH_XL`) com tamanho próprio em
  `GBASavedataSize`, `GBASavedataClone`, `GBASavedataForceType`/init e
  `mappedMemoryFree`;
- detecção: pelo tamanho do `.sav`, ou por entrada em
  `src/gba/overrides.c` com o game code da ROM, ou por uma string-marcador
  na ROM (como o `FLASH1M_V`);
- savestate: o banco atual vai em 1 bit
  (`GBASerializedSavedataFlagsFillFlashBank`,
  `currentBank == &data[0x10000]`), então precisa de mais bits (há bits
  reservados nos flags);
- menu de override de save do frontend Qt, se for exposto.

**Jogo:**
- `gFlash->romSize` e `SECTORS_COUNT`;
- o `agb_flash` já divide o setor em banco e setor local.

**Layout:** o `save.c` é do upstream Eemeliri e muito customizado (caixas
16–19). Reorganizar gera conflito em todo pull (memória
`pull-do-upstream-eemeliri`). Prefira **acrescentar** setores novos
(32+) para dados novos, com assinatura e checksum próprios, sem mover o
layout atual. Com os setores novos, objetos, templates, flags e vars
extras podem ir para lá.

Após mudar o mGBA: `make mgba-windows` com o mGBA fechado.

## 6. RAM e CPU

- **EWRAM:** ~13 KB livres estáticos, mais o heap `gHeap` de 0x1D000
  (116 KB, `include/malloc.h`). **IWRAM:** ~8,5 KB livres. Chega para
  24–27 objetos e 96 sprites.
- **Expandir EWRAM no mGBA** é possível (mapear 0x02000000+ sem espelho,
  como foi feito com a ROM), mas caro:
  - 37 referências a `GBA_SIZE_EWRAM` em `memory.c`, `gba.c`, `core.c`,
    `bios.c`, `cheats.c` e libretro;
  - `GBASerializedState` tem `wram[GBA_SIZE_EWRAM]` fixo, então o savestate
    precisa de extdata;
  - no jogo, `LENGTH` da EWRAM no linker script.

  Só vale quando a EWRAM de fato acabar.
- **CPU:** ninguém mediu. Cada objeto custa atualização por frame. Teste
  24 objetos andando em cena cheia. Se houver lag, o mGBA pode ganhar
  overclock (não existe no upstream).

## Plano de execução recomendado

**Etapa A: sem aumentar o save** (objetos até 27) — **FEITA em 02/10/2026**
1. `OBJECT_EVENTS_COUNT` 16 → 24.
2. `script_movement.c`: arrays próprios em EWRAM no lugar da máscara u16.
3. `SaveBlock1`: `objectEventsExtra[OBJECT_EVENTS_COUNT - 16]` no fim;
   `load_save.c` copia os extras; atualizar o assert `SaveBlock1LegacySize`.
4. `MAX_SPRITES` 64 → 96; `gOamLimit` 64 → 128.
5. `make -j$(nproc)`, depois `dev_scripts/medir_limites_ram_save.sh` para
   conferir a folga.
6. **Teste em runtime no mGBA:**
   - o `WorldHub`: a pior janela era de 36 objetos; em 03/10/2026 os grupos de
     NPC foram afastados do pomar (mapa 20x58) e ela caiu para 21. Todas as
     árvores e NPCs da janela devem aparecer (`objetos.py`);
   - uma cena com `applymovement` em mais de 16 objetos + `waitmovement`;
   - chuva no mesmo mapa;
   - salvar, carregar e conferir os objetos ≥ 16 na posição certa;
   - andar para fora e voltar para a janela (despawn/respawn);
   - follower ligado.

**Etapa B: mais de 27 objetos ou mais save**
1. mGBA com flash de 512 KB ou 1 MB (seção 5).
2. Setores novos acrescentados, sem mexer no layout do upstream.
3. Então mover `objectEventsExtra` (e o que mais precisar) para lá e
   subir `OBJECT_EVENTS_COUNT` à vontade. O próximo teto passa a ser
   `MAX_SPRITES` ≤ 127 (2 por objeto: ~50 objetos com clima).

### Como a Etapa A ficou no código

- `OBJECT_EVENTS_COUNT 24` e `OBJECT_EVENTS_SAVE_LEGACY_COUNT 16` em
  `include/constants/global.h`.
- `SaveBlock1.objectEvents[16]` no lugar de sempre; `objectEventsExtra[8]`
  no fim (offset 0x3C54, assert `SaveBlock1ObjectEventsExtraOffset`).
  `load_save.c` usa `GetSavedObjectEvent(i)` para escolher o array.
- **Saves antigos continuam carregando:** o setor é zerado antes de gravar,
  então os bytes novos eram zero e o checksum bate; os extras voltam
  inativos.
- `script_movement.c`: `sMovementObjEventIds[]` e `sMovementFinished[]` em
  EWRAM; a task não guarda mais nada em `data[]`.
- Teste: `test/script_movement.c` (24 objetos em `applymovement` +
  roundtrip de save dos slots ≥ 16). `T_SAVEBLOCK1_SIZE 15732` em
  `test/save.c`.
- **O mGBA não precisou mudar:** 128 entradas de OAM e 1024 tiles são o
  hardware normal do GBA. Só a Etapa B (save maior) mexe no emulador.
- Folga depois: SaveBlock1 com 140 B no último setor (+3 objetos no
  máximo), EWRAM ~9 KB, IWRAM ~8,4 KB.

**Paletas e VRAM** continuam hardware. Trate como regra de design, não
como limite a subir.
