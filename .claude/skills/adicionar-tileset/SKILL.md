---
name: adicionar-tileset
description: Use ao adicionar, portar ou corrigir um tileset de mapa - tiles.png, metatiles.bin, paletas, registro em src/data/tilesets/*.h e ligacao em data/layouts/layouts.json. Use tambem ao diagnosticar mapa com desenho deslocado, tiles em branco, cor certa no Porymap e errada no jogo, tela de lixo ao entrar no mapa, ou tileset que some da ROM. Nao use para sprite de NPC (skill adicionar-npc) nem para grafico de treinador.
---

# Tileset novo

Passo a passo completo, com exemplos reais:
**[`.claude/adicionar-tileset.md`](../../adicionar-tileset.md)**.

## Antes de desenhar: os números não são os do pokeemerald

Fonte de verdade é **`include/fieldmap.h`**. O SoulGold mudou a divisão
primário/secundário e usa **triple layer**.

| | Primário | Secundário |
|---|---|---|
| Tiles | **640** (`tiles.png` ≤ 128×320) | **384** (≤ 128×192) |
| Metatiles | 1024 | 1024 |
| Paletas visíveis | índices **0–6** | índices **7–12** |
| Base do tile id em `metatiles.bin` | 0 | **640** (vanilla: 512) |
| Bytes por metatile | **24** (12 tiles) | **24** |

> ⚠️ Tileset trazido de pokeemerald ou de outro hack tem `metatiles.bin` com
> base **512**. Aqui a base é **640** — o desenho inteiro sai **deslocado 128
> tiles**, e o build não reclama. É a armadilha nº 1.

## Os 9 lugares

| # | Arquivo |
|---|---|
| 1 | `data/tilesets/{primary,secondary}/<nome>/tiles.png` — 128 px de largura, indexado |
| 2 | `.../palettes/00.pal` … `12.pal` (13 arquivos; só o `.pal` se commita) |
| 3 | `.../metatiles.bin` — múltiplo de 24 bytes |
| 4 | `.../metatile_attributes.bin` — 2 bytes por metatile |
| 5 | `src/data/tilesets/graphics.h` — tiles + paletas |
| 6 | `src/data/tilesets/metatiles.h` — metatiles + attributes |
| 7 | `src/data/tilesets/headers.h` — `const struct Tileset gTileset_<Nome>` |
| 8 | `data/layouts/layouts.json` — **sem isto o tileset não entra na ROM** |
| 9 | `include/constants/metatile_labels.h` — só se um script usar `setmetatile` |

Porymap (`Tools ▸ New Tileset`) faz de 1 a 7. **8 e 9 são sempre seus.**
`data/layouts/layouts.inc` é gerado — nunca edite à mão.

## Confira antes de abrir o jogo

```bash
python3 .claude/skills/adicionar-tileset/check_tileset.py secondary/<nome>
```

Lê os limites do `fieldmap.h` e acusa split de 512, estouro de tiles, tamanho
errado de `metatiles.bin`, `isCompressed` que não casa com o INCBIN, paletas
faltando e tileset fora de `layouts.json`. Hoje os 174 tilesets em uso passam
limpos — qualquer `X` é coisa sua.

## Armadilhas

| Sintoma | Causa |
|---|---|
| Desenho todo deslocado | `metatiles.bin` com base 512 em vez de 640 |
| Pedaços em branco / lixo | `tiles.png` passou de 384 (secundário) ou 640 (primário) |
| Cor certa no Porymap, errada no jogo | Tile de secundário pintado com paleta 0–6; secundário só lê 7–12 |
| Tela de lixo ao entrar no mapa | `isCompressed = TRUE` com INCBIN de `tiles.4bpp` cru (tem que ser `.fastSmol`) |
| Tileset some mesmo registrado | Nenhum layout usa → `--gc-sections` corta do binário |
| Metatiles bagunçados do meio pro fim | `metatiles.bin` não múltiplo de 24 (triple layer, 12 tiles) |
| Animação mexe o tile errado | Offset chumbado do vanilla em vez de `NUM_TILES_IN_PRIMARY + n` |
| PNG editado não muda nada | Cache do make — apague os `.4bpp*`/`.gbapal` ao lado |
| Binário sujando o `git status` | `.4bpp`, `.gbapal` e `.fastSmol` são gerados; commite só `.png`, `.pal`, `.bin` |
| Porymap: "unknown secondary tileset label", mas o build passa | Campo do struct com expressão (`.swapPalettes = SWAP_PAL(7) \| …`): o parser do Porymap descarta o tileset. Ponha a expressão num `#define` no topo de `headers.h` e use só o nome no campo |
| Arte com versão noturna preta ou errada no jogo | A noite do slot `s` é o arquivo `(s+9)%16` do próprio secundário (7→00, 9→02, 10→03); e o mapa precisa ser TOWN/CITY/ROUTE |

Para **criar** o conteúdo do tileset (arte, paletas, clones do primário, troca dia/noite) use a skill `montar-tileset`.

## Checklist

- [ ] `tiles.png` 128 px de largura, indexado, dentro do teto de 640/384
- [ ] Tiles pintados com paleta **7–12** se o tileset for secundário
- [ ] `metatiles.bin` múltiplo de 24 bytes; attributes com a mesma contagem
- [ ] Se portado de outro projeto: tile ids rebaseados de 512 para 640
- [ ] Registrado nos **três** headers, com `isSecondary` batendo com a pasta
- [ ] `isCompressed = TRUE` **e** INCBIN de `tiles.4bpp.fastSmol`
- [ ] Ligado em `data/layouts/layouts.json`
- [ ] `check_tileset.py` sem nenhum `X`
- [ ] `make -j$(nproc)` e **entrei no mapa** para ver cor, camada e colisão
