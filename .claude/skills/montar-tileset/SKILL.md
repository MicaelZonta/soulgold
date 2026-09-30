---
name: montar-tileset
description: Use ao CRIAR o conteudo de um tileset novo por codigo (sem PIL) - desenhar a arte em pixels, cortar em tiles 8x8 com uma paleta cada, deduplicar com flip, montar metatiles de 24 bytes e escrever tiles.png/paletas/metatiles.bin - e ao reaproveitar pecas do primario com outra cor (montanha terracota), fazer arte que troca com o horario (swapPalettes, sol de dia/lua a noite), guardar um segundo estado para setmetatile, ou deixar um tileset legivel no Porymap. Para so REGISTRAR um tileset pronto (headers, layouts.json, split 640) use adicionar-tileset.
---

# Montar um tileset por código

O kit `tileset_kit.py` (python puro) faz tudo: PNG, paletas, leitura dos tilesets do
repositório, render e autoria. O exemplo completo e real é
[`exemplo_altar_sol_lua.py`](exemplo_altar_sol_lua.py), o gerador do
`gTileset_AltarSunMoon` que está no jogo.

```bash
python3 .claude/skills/montar-tileset/exemplo_altar_sol_lua.py /tmp/saida   # gera e imprime o orçamento
```

O segundo exemplo real é [`exemplo_arena_ultra_espaco.py`](exemplo_arena_ultra_espaco.py), o
gerador do `gTileset_UltraSpaceArena` e do `map.bin` do `UltraSpaceArena`. A cena inteira
vira um canvas, e o orçamento de 384 tiles é segurado por espelho no eixo, carimbo de peças
repetidas e detalhe de variante preso a um quadrante 8×8. Ele também mostra como usar uma
segunda camada (top).

Depois de gerado, **registrar e ligar** é a skill `adicionar-tileset`.

## O fluxo

| # | Passo | Kit |
|---|---|---|
| 1 | Desenhar em pixels com **chaves de material** (`'s1'`, `'w2'`, `'out'`), não cores | `Canvas`, `noise` |
| 2 | Paletas: chave → cor de dia (e de noite) por slot 7–12 | `PaletteSet` |
| 3 | Cortar: cada tile 8×8 escolhe a paleta que contém **todas** as suas chaves | `cut_tiles` |
| 4 | Deduplicar com flip H/V | `TileBank` |
| 5 | Metatiles por célula 16×16, com base do primário embaixo se houver | `build_cells`, `primary_ref` |
| 6 | Escrever os arquivos (as paletas noturnas vão no slot certo) | `write_tileset` |
| 7 | **Conferir lendo os arquivos escritos**, não as variáveis do gerador | `load_tileset(path=)` + `combine(..., night=1)` |

Conflito no passo 3 significa que o desenho mistura, num mesmo 8×8, cores de duas
paletas. A saída é **alinhar o elemento à grade de 8** ou juntar as chaves numa
paleta. Não force.

## As quatro técnicas

**1. Peça do primário com outra cor, custando zero tile.** Um metatile do secundário
pode apontar para tiles do primário (id < 640) com uma paleta **do secundário**.
`primary_ref(P, 113, {1: 8})` copia o metatile 113 trocando a paleta 1 pela 8. A
paleta 8 precisa ter, **nos mesmos índices**, as cores que esses tiles usam. Confira
com `used_color_indices`. Se nenhum tile desenhado usa o slot, faça dele uma cópia
inteira da paleta do primário recolorida. Assim qualquer peça daquela família
funciona, como os 166 clones de montanha terracota do altar.

**2. Sol de dia, lua à noite sem script.** Desenhe os dois glifos **nos mesmos
pixels** com tintas separadas: `sun*` (cor de dia = dourado, de noite = cor da face),
`moon*` (dia = cor da face, noite = lilás) e `both` para os pixels comuns. Ligue
`.swapPalettes`. A face sob o glifo precisa ser **de uma cor lisa**, senão o glifo
apagado deixa marca.

**3. Estado alternativo** (portal, porta aberta): corte um segundo canvas e passe a
mesma lista em `build_cells(..., metas=metas)`. Os metatiles extras vão para
`setmetatile` e para `metatile_labels.h`.

**4. Arte sobre uma base do primário:** a base ocupa bottom+middle, e o desenho só
cabe na camada **top**, que cobre sprites. Use apenas onde o jogador nunca fica atrás
(`top=` no `build_cells` exige que você declare as células). Onde o jogador anda ou
encosta, desenhe a célula opaca.

## Números que o build não confere

| Regra | Onde |
|---|---|
| Secundário enxerga só as paletas **7–12**; 00–06 do arquivo são ignoradas... | `fieldmap.c` |
| ...exceto como **versão noturna**: o slot `s` mistura com o arquivo `(s+9)%16` do próprio secundário (7→00, 9→02, 10→03) | `UpdateAltBgPalettes` |
| A troca só roda em mapa `MAP_TYPE_TOWN/CITY/ROUTE/OCEAN_ROUTE` | `MapHasNaturalLight` |
| Transição: 19h–21h e 6h–10h misturam as duas paletas; lua plena 21h–6h | `UpdateTimeOfDay` |
| 384 tiles no secundário, 24 bytes por metatile, entradas bits 0-9 tile / 10 hflip / 11 vflip / 12-15 paleta | `include/fieldmap.h` |
| O motor desenha **as três camadas** sempre; o tipo de camada do atributo não importa (só 0xFF = porta) | `DrawMetatile` |
| Índice 0 é transparente em qualquer paleta | — |

## Porymap (6.3.1)

O Porymap lê `headers.h` com um parser simples. **Um campo com expressão some com o
tileset inteiro** ("unknown secondary tileset label"). O build compila normalmente.

```c
// topo de headers.h, junto do SWAP_PAL:
#define SWAP_PALS_MEU_TILESET (SWAP_PAL(7) | SWAP_PAL(9))
// no struct, um identificador só, depois de .isSecondary:
    .swapPalettes = SWAP_PALS_MEU_TILESET,
```

O Porymap mostra sempre as cores de dia. Para dar ao mapeador peças de outra cor,
**inclua os clones como metatiles** (técnica 1): ele pinta com eles normalmente.
Anexe clones novos **no fim** da lista de metatiles. Mudar a ordem troca o desenho de
todo mapa que já usa o tileset.

## Armadilhas que já custaram caro

| Sintoma | Causa |
|---|---|
| Medalhões/flores **pretos à noite** no jogo, certos no render | Paleta noturna gravada no arquivo errado; use `write_tileset` e confira lendo os arquivos |
| Altar sempre sol | `map_type` do mapa não é TOWN/CITY/ROUTE |
| Montanha de uma cor, pedaços de outra | Mapa misturando peça do primário (cor original) com clone; troque as células pelos clones |
| Desenho do alto cobrindo a cabeça do jogador | Arte na camada top numa célula onde ele encosta |
| Arte "achatada" perto do jogo original | Desenhar à mão o que o primário já tem: reaproveite a rocha/árvore/água com `primary_ref` e desenhe só o que é novo; luz de cima à esquerda, contorno escuro quente, sombra projetada |
| Canto de praia côncavo sem peça | O `johto_general` não tem: faça costa convexa |
| Tileset estourou 384 com detalhe novo | Peças repetidas desenhadas duas vezes com ruído diferente. Carimbe a cópia (`stamp`) alinhada a 8 px, espelhada se quiser; ruído só de `(x%16, y%16)`; detalhe de variante dentro de um quadrante 8×8 |
| Objeto alto (cristal, lampião) sem profundidade | Desenhe a parte de cima num canvas separado e monte o metatile com ele na camada **top** da célula de cima; quem passa atrás fica atrás |
| Mapa ímpar para centralizar | Com caminhos de 3 células o centro é a coluna do meio: largura ímpar (21), eixo em `x = 168`, que ainda é borda de tile |

## Checklist

- [ ] Nenhum conflito de paleta no corte; `tiles` ≤ 384
- [ ] Paleta de clone com as cores **nos índices** que os tiles do primário usam
- [ ] Glifos que trocam: face lisa, `sun*`/`moon*`/`both`, `.swapPalettes` com o `#define`
- [ ] Clones e estados novos **anexados no fim**; índices antigos intactos (compare os bytes)
- [ ] Render lido dos arquivos escritos, de dia e de noite
- [ ] Registro e ligação: skill `adicionar-tileset` (`check_tileset.py` sem `X`)
- [ ] Mapa aberto no **Porymap** e jogo aberto de dia e de noite
