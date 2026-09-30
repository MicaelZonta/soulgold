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
