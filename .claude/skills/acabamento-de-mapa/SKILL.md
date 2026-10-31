---
name: acabamento-de-mapa
description: Use ao pintar, gerar ou revisar o acabamento de um mapa com o johto_general - bordas de praia, areia com grama, cantos, colunas de arvores, montanha em degraus com borda de tras e laterais - e sempre que o usuario tiver editado no Porymap um mapa que voce gerou (para aprender com a edicao em vez de sobrescreve-la). Traz as regras aprendidas do mapa SunMoonAltar retocado a mao pelo autor e confirmadas nos mapas de Johto, e o diff_mapas.py que extrai licoes de qualquer edicao.
---

# Acabamento de mapa (Johto)

Regras tiradas da montanha e da ilha do `SunMoonAltar` retocadas à mão pelo autor no
Porymap (338 células mudadas sobre o mapa gerado) e **conferidas** com `neighbours_of`
nos mapas de Johto. Estão em código em `JOHTO`, `pick_sand`, `pick_forest` e `tree_base`
(`.claude/skills/prototipo-de-mapa/mapa_kit.py`).

**Peça errada não dá erro de build.** O mapa só fica feio ou com emendas.

## Aprender com a edição do autor

Quando o usuário retoca um mapa seu no Porymap, **a versão dele é a referência**:

```bash
cp data/layouts/<Mapa>/map.bin $SCRATCH/antes_do_meu_ajuste.bin      # sempre, antes de mexer
python3 .claude/skills/acabamento-de-mapa/diff_mapas.py GERADO.bin data/layouts/<Mapa>/map.bin \
    --layout <Mapa> --png $SCRATCH/diff.png
```

- Leia as substituições mais comuns: cada padrão repetido é uma regra.
- Confirme a regra nos mapas do jogo:
  `neighbours_of(maps_using('gTileset_Johto_General'), peça, dx, dy)`.
- Grave a regra em `mapa_kit.py` e nesta tabela.
- Mudança pedida depois disso vai **por cima do mapa dele**, trocando metatile e
  preservando colisão e elevação (`v & ~0x7ff | novo`). Nunca regenere por cima.

## Regras

### Praia

| Regra | Peças |
|---|---|
| Entre mar e grama, **no mínimo 2 células de areia**: uma leva a borda de água, a outra a de grama | — |
| Areia com água: N S O L | 269 285 276 278 |
| Cantos convexos | 268 270 284 286 |
| Canto côncavo areia/água **não existe** no `johto_general`: costa reta, só cantos convexos | — |
| Areia com grama: N S O L | 212 228 219 221 |
| Cantos areia/grama: NO NE SO SE | **211 213 227 229** |
| A terra pode ir até a borda do mapa; o `border.bin` de mar faz o resto | — |

### Árvores

| Regra | Peças |
|---|---|
| Árvore = **coluna de 2 de largura**; entra inteira ou não entra | — |
| Topo sobre grama | **14 \| 15** |
| Corpo, fase presa ao **topo da coluna** (não à paridade global da linha) | ímpar 26 \| 27, par 18 \| 19 |
| Corpo com outra coluna encostada | ímpar 654 \| 655, par 646 \| 647 |
| Última linha | **30 \| 31** |
| Base, na célula de grama **abaixo** (bloqueada) | **36 \| 37** |
| Colunas vizinhas **escalonadas** (uma começa uma linha abaixo); uma célula de grama antes da praia | — |
| Nunca 26 \| 27 no topo: vira sebe | — |

### Montanha

| Regra | Peças |
|---|---|
| Topo do platô | 113 |
| Face (degrau para baixo) e pontas | 124; 123 \| 125 |
| Borda lateral de degrau interno | 115 (esq.) \| 117 (dir.) |
| **Cada platô tem borda de trás**, conforme o que há atrás: sobre grama / rocha / areia | 104 105 106 / 107 108 109 / 152 108 154 |
| Laterais externas em faixas de 2–3 colunas repetidas | 112… (esq.) \| …117 (dir.) |
| Cantos da base sobre grama | 120 \| 122 |
| Sem a borda de trás ou sem as laterais externas a montanha fica "cortada" | — |
| Montanha em outra cor: use os **clones** do secundário, nunca misture com a peça do primário | skill `montar-tileset` |

## Revisar um mapa (checklist)

- [ ] Render do repositório: `python3 .claude/skills/prototipo-de-mapa/mapa_kit.py <Mapa> out.png` (e `--noite`)
- [ ] Praia: em todo lugar onde mar e grama se aproximam há duas faixas de areia; cantos 211/213/227/229 nas curvas da grama
- [ ] Árvores: nenhuma meia-árvore; topo 14|15, fim 30|31, base 36|37; sem sebe
- [ ] Montanha: toda borda de trás fechada; laterais externas; nada da cor do primário misturado com clone
- [ ] Colisão: árvores, bases e rocha bloqueadas; `check_objects` sem NPC em bloqueio
- [ ] Se o autor retocou: o diff foi lido e as regras novas foram gravadas aqui

## Aprendido na Abundance Isle (30/10/2026)

Ferramentas em `.claude/skills/criar-aventura/ferramentas/`. Regra geral: **descobrir a peça pela
vizinhança nos mapas que já usam o mesmo par de tilesets** (`learn_walls`/assinatura de 8 vizinhos),
nunca escolher no olho. O autor reprovou na hora um mapa "chapado": ilha retangular, rocha lisa sem borda,
platô em forma de caixa.

### Montanha de Johto em níveis (`plateau()` em `kit_aventura.py`)

Nível sobre grama: borda de trás 104/105/106, laterais 112/114, face 123|124|125, base 120|121|122,
topo 113. Nível sobre rocha: borda de trás 107/108/109, laterais 115/117, sem base. Escada de 2:
137|145 na face e na base. Boca de caverna: 169 na linha da base ou da face. Pedra solta no topo da rocha:
167 (a 159 tem cantos verdes).

### Caverna de gelo (`johto_general` + `cave_ice`)

Parede = célula bloqueada vizinha do chão, peça pela assinatura (NO N NE O L SO S SE, 1 = chão):
S → 0x419, N → 0x409, L → 0x412, O → 0x410, só SE → 0x41b, só SO → 0x41c, só NE/NO → 0x409,
côncavos S+L 0x41a, S+O 0x418, N+L 0x40a, N+O 0x408; enchimento 0x411. Chão 0x459, gelo 0x4cb
(desliza), bola de neve 0x4c7, pedra 2×2 0x41d/0x41e/0x425/0x426, estalagmite 0x41f+0x427, saída
para fora 0x407 na borda de baixo. Tabela pronta em `CAVE_WALL`/`cave_wall()`.

### Ruínas de deserto (`johto_general` + `desert`, regra da RegirockChamber — `ruina_kit.py`)

Paredão **acima de cada sala, na largura dela**: topo 0x42a, meio 0x432, base 0x43a (até 4 linhas);
bordas laterais 0x423 (chão a leste) e 0x421 (chão a oeste) **subindo junto do paredão**; borda de baixo
0x41a com cantos 0x41b/0x419; enchimento 0x422. O paredão para **uma linha antes** do chão da sala de
cima (essa linha é a borda de baixo dela). Separação mínima entre salas empilhadas: 5 linhas; lado a
lado: 2 colunas. Paredão curto demais ou parede de 1 coluna = "clipando".

### Deserto (`johto_general` + `desert_village`, como a VajraDesertEast)

- Dois níveis: areia escura 0x575 em cima, areia clara 0x408 embaixo, separados por um **paredão de 7
  linhas**: 0x56e, 0x437, 0x42a, 0x43a, 0x42a, 0x432, 0x43a. Escada no paredão: 3 colunas 0x89|0x91|0x91
  (sem aro na linha de cima). Boca de caverna 2×2: 0x41e 0x41f / 0x426 0x427 (as de baixo andáveis, warp).
- Água encontra areia pela **borda desenhada na célula de água** (marrom): terra a N 0x123, S 0x582,
  O 0x12a, L 0x12c; côncavos N+L 0x517, N+O 0x516, S+L 0x580, S+O 0x581; só NE 0x130, só NO 0x131.
  A areia clara do deserto não tem jogo de bordas próprio; não use a praia de Johto (0x115) misturada.
- Enfeites (blocos inteiros): palmeira clara 0x48e/0x48f · 0x496/0x497 · 0x49e/0x49f (linha de cima
  andável); palmeira escura 0x57d/0x57e · 0x585/0x586 · 0x58d/0x58e; cacto 0x414/0x415 · 0x41c/0x41d ·
  0x424/0x425; duna 0x4b0/0x4b1 · 0x4b8/0x4b9; ossada 0x407 ou 0x40f; pedra 0x438; capim claro 0x410,
  escuro 0x589 em **manchas irregulares** (blob com ruído), nunca retângulos.
- Poço de areia movediça 4×3: 0x488..0x49d (o desert não tem buraco de queda com comportamento; para
  derrubar ao pisar, clone o secundário com o atributo de queda).

### Carimbar prédio de outro mapa

- Carimbe **só o corpo do prédio**: árvores, cerca e células vazias em volta vêm junto e ficam péssimas
  sobre rocha (fachada da Burned Tower na Thunder Ridge).
- Se ainda sobrar verde, a grama está **dentro do metatile** (camadas de baixo/meio). Clone o secundário
  para o mapa e troque, nesses metatiles, as entradas de grama (tiles 0x1, 0x13, 0x26c, 0x26d, 0x27d,
  paleta 0) pela camada da rocha 113 (`thunder_ridge`, 61 entradas trocadas).
- Fachada de ginásio mostra "GYM": escolha outro prédio ou retoque.

### Desenho novo dentro de um tileset

`instalar_arte.py`: clona o secundário, procura **tiles não referenciados** e **índices livres** de uma
paleta 7–12, reduz o desenho até caber, grava o desenho na camada do meio com o chão do lugar
(camada do meio do metatile de chão) embaixo. Confira renderizando **dos arquivos** do clone.
