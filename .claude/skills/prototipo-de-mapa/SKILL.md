---
name: prototipo-de-mapa
description: Use ao propor ou redesenhar um mapa antes (ou em vez) de pinta-lo a mao - compor o map.bin com pecas do primario escolhidas pelos mapas que ja existem, carimbar um tileset novo, posicionar os NPCs com o sprite real, renderizar dia/noite/cena/colisao e publicar o documento-pagina do prototipo (estilo da pagina do Altar do Sol e da Lua). Tambem use para renderizar um mapa do repositorio como ele esta (conferir NPC em bloqueio, ver a noite, gerar imagem para discutir). Para desenhar o tileset novo em si use montar-tileset; para registrar use adicionar-tileset.
---

# Protótipo de mapa e documento

O resultado tem duas partes:

1. **Arquivos de verdade**: `map.bin`, `border.bin` e os `object_events` no formato do
   `map.json`, prontos para instalar e abrir no Porymap.
2. **Página do protótipo** (Artifact): viewer com os estados do mapa, rota da área,
   NPCs, tilesets, orçamento, paletas, o que muda no `map.json`, passos e pendências.

Tudo em python puro. O kit é `mapa_kit.py` (usa `../montar-tileset/tileset_kit.py`).
O exemplo real e completo é a ilha do `SunMoonAltar`:

```bash
python3 .claude/skills/montar-tileset/exemplo_altar_sol_lua.py /tmp/p      # tileset do altar
python3 .claude/skills/prototipo-de-mapa/exemplo_ilha_altar.py /tmp/p      # ilha, renders, objetos
python3 .claude/skills/prototipo-de-mapa/mapa_kit.py SunMoonAltar /tmp/n.png --noite   # mapa do repo
```

## Antes de compor: ler

- O **design** do evento (`.claude/*_DESIGN*.md`, `*_IMPLEMENTATION.md`): quem está no
  mapa, em que estados, o que é bloqueio de história. Quantos NPCs dão o tamanho.
- O **mapa atual** (`data/maps/<Mapa>/map.json`, layout em `layouts.json`). Se o
  usuário já pintou algo, **copie o `map.bin` para o scratchpad antes** de sobrescrever.
- Mapas parecidos que já existem, **renderizados**: `render_repo_map` mostra como
  Johto resolve praia, montanha, cais. Copie a solução, não invente.

## Compor (receita do exemplo)

| # | Passo | Kit |
|---|---|---|
| 1 | Grade de **classes** (água, areia, grama, floresta, carimbo, cais) por regra | lista de listas |
| 2 | Classe → metatile pelas peças aprendidas | `JOHTO`, `pick_sand`, `pick_forest` |
| 3 | Carimbar o tileset novo com a colisão dele | `altar_grid.json` do `montar-tileset` |
| 4 | Colisão e elevação por célula: chão 3, água 1 | `pack_block`, `write_blocks` |
| 5 | NPCs no formato do `map.json`, **conferidos** | `check_objects` |
| 6 | Renders: dia, transição, noite, cena, estado final, colisão | `render_blocks` |

**Peça errada não dá erro.** Nunca escolha borda "no olho". Aprenda dos mapas:

- `learn_edges(maps_using('gTileset_Johto_General'), MetatileClasses(P), 'S', 'W')`
  devolve, para cada vizinhança, o metatile que os mapeadores usaram.
- `neighbours_of(maps, 105, -1, 0)` descobre o que fica ao lado de uma peça. Foi assim
  que saíram as pontas da borda de trás da montanha (104, 105, 106).
- `labeled_sheet` gera folha numerada para conferir visualmente.

Já aprendido e guardado em `JOHTO`:

- **Praia:** 8 bordas. Não existe canto côncavo, então a costa tem de ser convexa.
- **Areia com grama:** 4 bordas e 4 cantos (211, 213, 227 e 229).
- **Árvores:** colunas de 2 de largura com topo 14|15, fim 30|31 e base 36|37, com a
  fase presa ao topo da coluna (`pick_forest` e `tree_base`).
- **Cais:** 3 colunas.
- **Pedras no mar:** blocos 2×2.
- **Montanha:** degraus internos (113, 124, 115/117, 123/125) e fechamento externo
  (104/105/106 atrás, 112/114 nas laterais, 120/122 na base). **Sem o fechamento
  externo a montanha fica aberta.**

As regras completas de acabamento (praia de 2 células, cantos 211/213/227/229, borda de
trás de cada platô) estão na skill `acabamento-de-mapa`. **Se o autor retocou o mapa no
Porymap, rode o `diff_mapas.py` dela antes de mexer.**

## Posicionar NPCs

- Posição = célula; `check_objects` acusa NPC em bloqueio ou água.
- Parceiro Pokémon fora da Poké Ball: `OBJ_EVENT_GFX_SPECIES(X)` e `script: NULL`
  (skill `parceiro-pokemon-de-npc`).
- Navio: `OBJ_EVENT_GFX_SS_TIDAL`, 96×40, elevação 1, `script: 0x0`. Não gasta tile.
- Cena grande: conte **paletas de sprite** (16 slots). Só é carregado o que está perto
  da câmera; o que fica a mais de uma tela de distância não pesa.
- Sem warp de entrada, o debug põe o jogador no **centro do mapa**: deixe o centro
  andável ou avise.
- Um `map.json` que ainda vai virar evento: flags e visibilidade pela skill
  `visibilidade-e-gatilhos`.

## A página

`modelo_pagina.html` é a página do altar, pronta para servir de molde. Copie para o
scratchpad, troque o conteúdo seção por seção e mantenha CSS, tokens e estrutura:

| Seção | Conteúdo |
|---|---|
| Hero | viewer com botões de estado (dia, noite, cena, estado final, colisão), 4 números, 1 parágrafo |
| Rota | faixas de linhas do mapa, de onde o jogador chega até o ponto central |
| Quem fica onde | tabela de NPCs (x,y e direção) e pontos (Fly, warp, entradas) |
| Tilesets | peças do primário por metatile, números do secundário, barras de orçamento |
| Técnica do tileset | se houver (ex.: um tile, duas tintas), com recortes ampliados |
| Paletas | `{{PALETAS}}` gerado dos `.pal` (dia e noite) |
| Folha de tiles | `tiles_colored.png` |
| O que muda no `map.json` | tabela campo, hoje e proposta |
| Passos e pendências | lista numerada e cartões; o que é decisão do autor fica destacado |

```bash
python3 .claude/skills/prototipo-de-mapa/montar_pagina.py modelo.html saida.html --base DIR_DAS_IMAGENS \
    --tileset data/tilesets/secondary/<nome> --swap 7,9,10 --nome "7=Pedra" --nome "8=Montanha"
```

Depois publique com a ferramenta Artifact (ícone `map`). Para atualizar, republique o
mesmo arquivo, que mantém o link. Texto da página em português; **texto que aparece no
jogo, em inglês**.

## Instalar no repositório (quando o usuário aprovar)

1. Tileset: skill `adicionar-tileset` (headers, e `#define` para expressões por causa
   do Porymap).
2. `layouts.json`: tamanho e tilesets. `map.bin` e `border.bin` gerados.
3. `map.json`: `map_type` **TOWN/CITY/ROUTE** se o tileset troca de cor com o horário;
   objetos; `scripts.inc` com um script por NPC que não seja parceiro.
4. `check_tileset.py`, `make`, `check_objects` sobre o mapa instalado e render do
   repositório (`mapa_kit.py <Mapa> out.png --noite`).
5. Peça para o usuário abrir no **Porymap** e no jogo.

## Armadilhas

| Sintoma | Causa |
|---|---|
| Borda de praia com mancha de rocha | Canto côncavo pegou peça de Cianwood (areia com rocha) |
| Montanha "cortada" atrás/nos lados | Usou degrau interno (115/117/123/125) na borda externa |
| Página bonita, jogo diferente | Render feito das variáveis do gerador; renderize **dos arquivos** |
| Usuário editou no Porymap e o gerador apagou | Nunca regenere por cima do `map.bin` do repo sem comparar; aplique a mudança sobre o mapa dele (ex.: troca de metatile preservando colisão) |
| NPC dentro da parede | Coordenada não conferida com `check_objects` |
| Build falha em `check-song-config` | A música do `map.json` está desligada em `include/config/songs_enabled.h` (ROM cheia). Escolha uma ligada (`grep " 1$"`) antes de ligar outra |
| Fundo de batalha preto ou lixo | Entrada de `gBattleEnvironmentInfo` sem `.background`/`.palette` (o `ULTRA_SPACE` do expansion vinha assim). Fundo novo: 256×112 de arte, `tiles.bin` 64×32 (duas telas iguais, linhas 14+ = tile vazio), `palette.pal` de 48 cores (BG 2–4); cena ligada por `MAP_BATTLE_SCENE_*` em `sMapBattleSceneMapping`. Exemplo: `montar-tileset/exemplo_fundo_batalha_ultra.py` |
| Lendário de 64×64 cortado no render | Sprite de overworld de espécie pode ter 64 px; `sprite_for` lê o tamanho do PNG |
