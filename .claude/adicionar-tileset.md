# Como adicionar um tileset novo no SoulGold

Guia derivado dos tilesets de Johto já presentes (`secondary/cherrygrove_city`,
`secondary/azalea_town`, `primary/johto_general`) e de um tileset descartável
criado, compilado e apagado durante a escrita deste guia.

> ⚠️ **Leia [Os números que mandam](#os-números-que-mandam) antes de desenhar
> qualquer coisa.** O SoulGold **não** usa a divisão primário/secundário do
> pokeemerald de fábrica. Tileset trazido de outro projeto sai **deslocado
> 128 tiles** e compila limpo.

---

## Checklist rápido

| # | Arquivo | O que fazer |
|---|---------|-------------|
| 1 | `data/tilesets/{primary,secondary}/<nome>/tiles.png` | A folha de tiles, 128 px de largura, indexada |
| 2 | `.../<nome>/palettes/00.pal` … `12.pal` | As paletas em JASC `.pal` (13 arquivos) |
| 3 | `.../<nome>/metatiles.bin` | Os metatiles — **24 bytes cada** (triple layer) |
| 4 | `.../<nome>/metatile_attributes.bin` | 2 bytes por metatile |
| 5 | `src/data/tilesets/graphics.h` | `gTilesetTiles_<Nome>` + `gTilesetPalettes_<Nome>` |
| 6 | `src/data/tilesets/metatiles.h` | `gMetatiles_<Nome>` + `gMetatileAttributes_<Nome>` |
| 7 | `src/data/tilesets/headers.h` | `const struct Tileset gTileset_<Nome>` |
| 8 | `data/layouts/layouts.json` | Ligar em algum layout — senão o tileset **não entra na ROM** |
| 9 | `include/constants/metatile_labels.h` | Só se algum script mexer nesses metatiles |

Os passos 1–7 o **Porymap** faz sozinho (`Tools ▸ New Tileset`). Os passos 8 e 9
são seus em qualquer caminho.

---

## Os números que mandam

Fonte de verdade: **`include/fieldmap.h`**. Não copie número de tutorial de
pokeemerald — este projeto mudou a divisão para dar mais espaço aos primários de
Johto.

| Constante | SoulGold | pokeemerald de fábrica |
|---|---|---|
| `NUM_TILES_IN_PRIMARY` | **640** | 512 |
| `NUM_TILES_TOTAL` | 1024 | 1024 |
| `NUM_METATILES_IN_PRIMARY` | **1024** | 512 |
| `NUM_METATILES_TOTAL` | 2048 | 1024 |
| `NUM_PALS_IN_PRIMARY` | 7 | 6 |
| `NUM_PALS_TOTAL` | 13 | 13 |
| `NUM_TILES_PER_METATILE` | **12** (triple layer) | 8 |

Daí saem os tetos reais:

| | Primário | Secundário |
|---|---|---|
| Tiles | **640** (`tiles.png` até 128×320) | **384** (até 128×192) |
| Metatiles | **1024** | **1024** |
| `metatiles.bin` | ≤ 24576 bytes | ≤ 24576 bytes |
| Paletas visíveis | índices **0–6** | índices **7–12** |
| Base do tile id | 0 | **640** |

`fieldmap.c` copia sempre o bloco inteiro (`CopyPrimaryTilesetToVram` manda 640
tiles, `CopySecondaryTilesetToVram` manda 384 a partir do offset 640). Tile que
passe do teto simplesmente **nunca chega na VRAM** — sem erro, sem aviso.

### A armadilha do split 512 → 640

`metatiles.bin` guarda **índice absoluto de tile**, já com a base do secundário
embutida. Um tileset secundário feito num projeto com `NUM_TILES_IN_PRIMARY=512`
tem ids começando em ~512; aqui a base é 640. Resultado: **todo o desenho sai
deslocado 128 tiles**, e o build não reclama de nada.

Dá para ver isso nos restos de Hoenn que sobraram no repositório:

```
secondary/pokemon_center   tile ids usados: 513..989   ← split de 512, quebrado
secondary/cherrygrove_city tile ids usados:   6..888   ← feito aqui, correto
```

O verificador da skill detecta esse caso. Rode-o **antes** de abrir o jogo:

```bash
python3 .claude/skills/adicionar-tileset/check_tileset.py secondary/<nome>
```

---

## Passo a passo

### 1. `tiles.png`

- **128 px de largura**, sempre (16 tiles por linha). A altura é múltipla de 8.
- PNG **indexado** (colormap). Cor de índice 0 = transparência.
- Altura máxima: **320 px** (primário) / **192 px** (secundário).

A regra genérica do `Makefile` (`%.4bpp: %.png`) já converte. Você **não**
precisa de regra nova em `graphics_file_rules.mk` — aquelas entradas com
`-num_tiles N -Wnum_tiles` são uma trava opcional que avisa quando o número de
tiles de um tileset antigo muda. Se quiser a trava para o seu, adicione junto
das vizinhas:

```make
$(TILESETGFXDIR)/secondary/<nome>/tiles.4bpp: %.4bpp: %.png
	$(GFX) $< $@ -num_tiles 224 -Wnum_tiles
```

### 2. Paletas

- Commite só os **`.pal`** (JASC). Os `.gbapal` são gerados e estão no
  `.gitignore`.
- Convenção dos tilesets de Johto: **13 arquivos**, `00.pal` a `12.pal`.
  Os tilesets de Hoenn têm 16 — é herança, não alvo.
- **Num tileset secundário, as paletas 00–06 são ignoradas.** `LoadTilesetPalette`
  lê a partir de `palettes[NUM_PALS_IN_PRIMARY]`, ou seja, o índice 7. Pintar o
  tile com cor da paleta 3 num secundário mostra a paleta do *primário pareado*,
  não a sua. É a causa nº 1 de "cor certa no Porymap, cor errada no jogo".
- `<n>.pla` ao lado do `<n>.pal` é opcional: um txt com os índices de cor que
  ganham o bit alto (usado pelo sistema de luz/noite). `tools/gbagfx/jasc_pal.c`
  lê automaticamente se o arquivo existir.

Campos relacionados no `struct Tileset`, todos opcionais:

| Campo | Para quê |
|---|---|
| `swapPalettes` | paleta tem versão noturna em `((x + 9) % 16).pal`; use a macro `SWAP_PAL(x)` |
| `lightPalettes` | bitmask de paletas tratadas como luz no blend de horário |
| `customLightColor` | quais dessas usam cor 15 própria |

### 3. `metatiles.bin` e `metatile_attributes.bin`

O projeto está em **triple layer** (`enable_triple_layer_metatiles=1` no
`porymap.project.cfg`, `NUM_TILES_PER_METATILE 12`):

- **24 bytes por metatile** (12 tiles × 2 bytes), não 16.
- Cada entrada de 2 bytes: bits 0–9 tile id, bit 10 hflip, bit 11 vflip,
  bits 12–15 paleta.
- `metatile_attributes.bin`: **2 bytes por metatile**. Máscaras em uso —
  comportamento `0xFF`, tipo de camada `0xF000`. Terrain e encounter type estão
  desligados (`0x0`) neste projeto.

Os três tipos de camada (`global.fieldmap.h`): `NORMAL` (usa middle+top),
`COVERED` (bottom+middle), `SPLIT` (bottom+top).

Arquivos `bottom.png` / `middle.png` / `top.png` / `attributes.csv` que aparecem
em alguns tilesets primários são resíduo do conversor externo mencionado em
`data/tilesets/tileset_fixer.txt`. **Não entram no build** — nada no `Makefile`
nem em `tools/` lê `attributes.csv`.

### 4. Registrar nos três headers

`src/data/tilesets/graphics.h`:

```c
const u32 gTilesetTiles_MeuTileset[] = INCBIN_U32("data/tilesets/secondary/meu_tileset/tiles.4bpp.fastSmol");

const u16 gTilesetPalettes_MeuTileset[][16] =
{
    INCBIN_U16("data/tilesets/secondary/meu_tileset/palettes/00.gbapal"),
    /* ... até ... */
    INCBIN_U16("data/tilesets/secondary/meu_tileset/palettes/12.gbapal"),
};
```

`src/data/tilesets/metatiles.h`:

```c
const u16 gMetatiles_MeuTileset[] = INCBIN_U16("data/tilesets/secondary/meu_tileset/metatiles.bin");
const u16 gMetatileAttributes_MeuTileset[] = INCBIN_U16("data/tilesets/secondary/meu_tileset/metatile_attributes.bin");
```

`src/data/tilesets/headers.h`:

```c
const struct Tileset gTileset_MeuTileset =
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_MeuTileset,
    .palettes = gTilesetPalettes_MeuTileset,
    .metatiles = gMetatiles_MeuTileset,
    .metatileAttributes = gMetatileAttributes_MeuTileset,
    .callback = NULL,
};
```

Sobre `isCompressed`:

| `isCompressed` | INCBIN tem que apontar para |
|---|---|
| `TRUE` | `tiles.4bpp.fastSmol` (ou `.smol`) |
| `FALSE` | `tiles.4bpp` cru |

Trocar os dois **compila** e enche a tela de lixo. O padrão do projeto é
`TRUE` + `.fastSmol`.

Não é preciso mexer em `include/tilesets.h`: ele só declara os poucos tilesets
que código C referencia pelo nome. O `layouts.inc` gerado usa o símbolo direto
em assembly (`.4byte gTileset_MeuTileset`).

### 5. Ligar num layout

`data/layouts/layouts.json` — o `layouts.inc` é gerado disso, nunca edite à mão:

```json
{
  "id": "LAYOUT_MINHA_SALA",
  "name": "MinhaSala_Layout",
  "width": 12, "height": 10,
  "primary_tileset": "gTileset_Johto_Building",
  "secondary_tileset": "gTileset_MeuTileset",
  "border_filepath": "data/layouts/MinhaSala/border.bin",
  "blockdata_filepath": "data/layouts/MinhaSala/map.bin"
}
```

**Tileset que nenhum layout usa não chega na ROM**: o link roda com
`--gc-sections` e corta os `const` sem referência. Se você adicionou tudo e o
tileset "sumiu", é isso.

### 6. Animação (opcional)

Só se algum tile tiver que se mexer (água, flor, fonte):

1. Frames em `data/tilesets/<k>/<nome>/anim/<efeito>/0.png`, `1.png`, …
2. `INCBIN_U16` de cada `.4bpp` em `src/tileset_anims.c`, mais o array de frames.
3. `InitTilesetAnim_<Nome>()` + o `TilesetAnim_<Nome>(timer)`, no molde de
   `InitTilesetAnim_AzaleaTown_Gym`.
4. Declarar em `include/tileset_anims.h` e pôr em `.callback` no `headers.h`.

O destino na VRAM **tem que ser relativo**:

```c
AppendTilesetAnimToBuffer(frames[i],
    (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 99)), 0x80);
```

Offset fixo copiado do vanilla (`TILE_OFFSET_4BPP(521)`, que é 512+9) anima o
tile errado sob o split de 640. Há casos assim no `tileset_anims.c`, herdados de
Hoenn — não os use de modelo.

### 7. `metatile_labels.h` (opcional)

Só se algum script fizer `setmetatile` nesses metatiles. Agrupe por tileset,
como o arquivo já faz:

```c
// gTileset_MeuTileset
#define METATILE_MeuTileset_Door  0x41B
```

---

## Conferir antes de abrir o jogo

```bash
python3 .claude/skills/adicionar-tileset/check_tileset.py secondary/meu_tileset
```

Ele lê os limites de `include/fieldmap.h` (não são chumbados) e confere:
contagem de tiles, tamanho de `metatiles.bin` contra os 24 bytes do triple
layer, faixa real de tile id usada, casamento entre `isCompressed` e o INCBIN,
`isSecondary` contra a pasta, número de paletas, registro nos três headers e uso
em `layouts.json`.

`--all` varre o repositório inteiro. Referência: dos 174 tilesets ligados a
algum layout hoje, **nenhum** acusa problema; os que acusam são tilesets de
Hoenn órfãos, sem layout vivo.

Depois:

```bash
make -j$(nproc)
```

Compilar só prova que compila. **Entre no mapa** e olhe: cor, deslocamento,
colisão e as camadas.

---

## Armadilhas

| Sintoma | Causa |
|---|---|
| Desenho todo deslocado, tiles trocados | `metatiles.bin` feito com `NUM_TILES_IN_PRIMARY=512`; aqui é 640 |
| Parte do tileset aparece em branco/lixo | `tiles.png` passou de 384 tiles (secundário) ou 640 (primário) |
| Cor certa no Porymap, errada no jogo | Tile secundário pintado com paleta 0–6; secundário só enxerga 7–12 |
| Tela de lixo ao entrar no mapa | `isCompressed` não casa com `.fastSmol`/`.4bpp` no INCBIN |
| Tileset "não existe" mesmo com tudo registrado | Nenhum layout usa → `--gc-sections` cortou |
| Metatiles bagunçados a partir de certo ponto | `metatiles.bin` com tamanho não múltiplo de 24 (triple layer) |
| Metatiles renderizam, atributos não batem | `metatile_attributes.bin` com contagem diferente de `metatiles.bin` |
| Animação mexe o tile errado | Offset chumbado do vanilla em vez de `NUM_TILES_IN_PRIMARY + n` |
| PNG novo não aparece depois de editar | Cache do make — apague os `.4bpp*`/`.gbapal` ao lado |
| Metatile do primário muda de cara conforme o mapa | Metatile do primário referencia tile ≥ 640, que pertence ao secundário pareado |
| `git status` cheio de binário | Você commitou `.4bpp`, `.gbapal` ou `.fastSmol` — são gerados |

---

## O que é gerado e o que se commita

| Commita | Gerado (gitignored) |
|---|---|
| `tiles.png` | `tiles.4bpp`, `tiles.4bpp.fastSmol` |
| `palettes/*.pal`, `palettes/*.pla` | `palettes/*.gbapal` |
| `metatiles.bin`, `metatile_attributes.bin` | `data/layouts/layouts.inc` |
| `anim/**/*.png` | `anim/**/*.4bpp` |
