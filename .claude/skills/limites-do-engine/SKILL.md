---
name: limites-do-engine
description: Use ao aumentar ou diagnosticar limites do engine - quantos NPCs/objetos aparecem ao mesmo tempo (OBJECT_EVENTS_COUNT, 40), quantos sprites (MAX_SPRITES 127 e gOamLimit 128), paletas de sprite (16 slots), VRAM de sprite (1024 tiles), tamanho do save (flash de 256 KB desde 24/10/2026, SaveBlock1 com 7412 B livres) e RAM (EWRAM/IWRAM), inclusive mudando o mGBA patchado (mais bancos de flash, mais RAM). Use tambem quando um NPC nao aparece num mapa cheio, aparece com a cor errada ou invisivel, a chuva falha, ou waitmovement trava com muitos objetos. Traz os scripts que medem a folga de save/RAM e o pior caso de objetos por mapa.
---

# Limites do engine

Guia completo, com números, arquivos e plano de execução em etapas:
**[`.claude/limites-do-engine.md`](../../limites-do-engine.md)**. Leia antes
de mexer.

Premissa: o projeto é **emulator-only**. Save antigo não precisa continuar
funcionando, e o mGBA de `tools/mgba-master` pode ser alterado (RAM, flash,
CPU) quando isso ajudar. Depois de mudar o mGBA: `make mgba-windows`.

## Meça primeiro (os números mudam)

```bash
make -j$(nproc)
dev_scripts/medir_limites_ram_save.sh          # folga de save, sprites, EWRAM/IWRAM
python3 dev_scripts/limites_janela_objetos.py  # pior janela de spawn (20x17) por mapa
python3 dev_scripts/limites_janela_objetos.py --mapa NewBarkTown
```

## O que é software (sobe) e o que é hardware (não sobe)

| Limite | Hoje | Sobe? |
|---|---|---|
| Objetos na janela de spawn (`OBJECT_EVENTS_COUNT`) | 40, jogador incluso | o save aguenta +205; a parede agora é sprite/OAM |
| `MAX_SPRITES` | 127 | já no teto do bitfield de 7 bits |
| `gOamLimit` (entradas de OAM por frame) | 128 | já no máximo do hardware |
| Paletas de sprite | 16 | **não**: 4 bits no OAM |
| VRAM de sprite | 1024 tiles | **não**: índice de 10 bits |
| Save | 36/64 setores (256 KB) | sim, com mais bancos de flash no mGBA |

## As armadilhas (todas compilam limpo)

1. **`waitmovement`**: já usa arrays em EWRAM (`sMovementFinished`), sem
   máscara u16. Não volte a guardar estado em `gTasks[].data[]`; o teste
   `test/script_movement.c` pega isso.
2. **Não cresça `SaveBlock1.objectEvents` no meio da struct.** Os offsets
   estão presos por `STATIC_ASSERT` por causa das caixas 16–19 do PC
   (código do upstream Eemeliri). Os slots ≥ 16 vão em `objectEventsExtra[]`
   **no fim** (`GetSavedObjectEvent` em `load_save.c`). Subir para 25–27:
   só a constante e `T_SAVEBLOCK1_SIZE` em `test/save.c`.
3. **Cada objeto gasta 2 sprites** (sombra ligada). 40 objetos + jogador =
   ~82 de 127, e o OAM do hardware são 128: acima de ~60 objetos só
   desligando sombra.
4. **Cor errada** = faltou slot de paleta. **Invisível** num mapa cheio de
   Pokémon = faltou VRAM (cada espécie carrega a folha inteira). A
   solução é design: paletas `NPC_1..4` e poucas espécies diferentes na
   tela.
5. Os `16` literais em `field_weather.c`, `field_effect_helpers.c`,
   `overworld.c` e `field_screen_effect.c` são de **paleta**. Não mexa.

## Teste em runtime obrigatório

Build limpo não prova nada. No mGBA:
- `WorldHub` (pomar + Elite 4 = 21 objetos na pior janela, todos devem aparecer);
- `applymovement` em mais de 16 objetos + `waitmovement`;
- chuva;
- salvar e carregar com objetos ≥ 16 carregados;
- sair e voltar para a janela;
- follower ligado.
