---
name: mapa-de-ligacoes
description: Use sempre que precisar saber o que existe numa cidade ou rota e como os mapas se ligam - "casas de Blackthorn", "que interiores tem Goldenrod", "onde fica o Centro de X", escolher uma casa/sala para uma cena, saber por qual porta se entra num mapa, achar o caminho ate um mapa, conferir se um mapa novo ficou ligado ao mundo, ou se um mapa e alcancavel, inalcancavel ou fora da ROM. Tambem para auditar conteudo (lendario, treinador, flag, item) que so vive num mapa morto, e ao ver o aviso "map_graph" no build ou o check "Mapa de ligacoes" falhar no CI.
---

# Mapa de ligações

`dev_scripts/map_graph.py` monta o grafo de todos os mapas (portas, conexões
e `warp` de script) e responde em um comando. **Não abra `map.json` um por um
para descobrir o que tem numa cidade** — pergunte ao script.

## Perguntas do dia a dia

```bash
python3 dev_scripts/map_graph.py area Blackthorn               # tudo: casas, ginásio, centro, loja, cavernas
python3 dev_scripts/map_graph.py area Goldenrod --tipo casa    # só as casas
python3 dev_scripts/map_graph.py info BlackthornCity_House2    # porta de entrada, saídas, tamanho, estado
python3 dev_scripts/map_graph.py caminho DarkraiInnFinalRoom   # rota a partir do quarto do jogador
python3 dev_scripts/map_graph.py buscar lab                    # procura por nome, MAPSEC ou tipo
python3 dev_scripts/map_graph.py inalcancaveis                 # mapas da ROM que ninguém alcança
```

O nome é livre: `Blackthorn`, `blackthorn city`, `BlackthornCity`,
`MAP_BLACKTHORN_CITY` ou `route 30` funcionam.

`area` devolve, para cada porta da cidade/rota: **tipo** (casa, ginasio,
centro, loja, laboratorio, caverna, porto, portao, torre, outro, ou "outra
área" quando a porta leva a outro lugar), **mapa**, **porta** (x,y no mapa de
fora), **tamanho** do layout, **objetos** já no mapa, **linhas de script** e
**estado**. Andares internos aparecem indentados embaixo do mapa de onde se
sobe. Depois lista os mapas da mesma MAPSEC que **não** têm porta a partir da
cidade (e por onde se entra neles).

Para escolher uma casa para uma cena: poucas linhas de script e poucos
objetos = casa livre; muitas = já tem evento, abra o script antes.

## Os três estados

| Estado | Quer dizer |
|---|---|
| `alcancavel` | ligado ao mundo a partir do quarto do jogador |
| `INALCANCAVEL` | está na ROM, mas nenhuma porta/conexão/warp leva até ele |
| `fora da ROM` | o grupo dele está em `rom_excluded_groups` de `data/maps/map_groups.json` — **não é compilado** |

Dos 1107 `map.json` do repositório, **619 estão na ROM** e **555 são
alcançáveis** (25/09/2026). Os 488 fora da ROM são os grupos
`gMapGroup_Emerald1..5` mais 2 pastas que não estão em grupo nenhum
(`CherrygrovePokeCenter`, `Route121_SafariZoneGate_SafariZoneEntrance`).
Conteúdo que só vive num mapa `fora da ROM` ou `INALCANCAVEL` **não existe
para o jogador** — lendário, treinador, item, flag.

## O check automático

- **No build:** `make` roda `map_graph.py check` quando algum `map.json`,
  `scripts.inc`, `map_groups.json` ou a lista de referência muda. **Só avisa**
  (`map_graph: AVISO — ...`), nunca quebra o build.
- **No CI:** `.github/workflows/map-graph.yml` roda `check --strict` e
  **falha** se aparecer mapa desligado novo.
- **Lista de referência:** `docs/MAPAS_INALCANCAVEIS.txt` — os 64 mapas da
  ROM que já são inalcançáveis hoje (SS Aqua, Safari Zone, Battle Frontier de
  Johto, variantes de noite, mapas de teste). Gerada, nunca editada à mão.

Quando o aviso aparecer:

1. Mapa novo que devia estar ligado → falta a porta: `warp_events` no
   `map.json` de fora **e** a porta de volta no de dentro (`dest_warp_id`
   certo dos dois lados), ou a `connection`.
2. Mapa desligado de propósito (em construção, só alcançado por código) →
   `python3 dev_scripts/map_graph.py check --atualizar` e confira o
   `git diff docs/MAPAS_INALCANCAVEIS.txt`.
3. "Mapa que agora é alcançável" → alguém ligou um mapa antigo; rode
   `--atualizar` para a lista acompanhar.

Também dá para rodar direto: `make map-graph-check` (modo estrito).

## O que o grafo **não** sabe

- **História.** Porta trancada por flag, NPC bloqueando, cena obrigatória: o
  grafo conta como aberto. "Alcançável" = ligado, não = liberado.
- **Obstáculo de campo.** Ledge de mão única, Surf, Cut, Strength, Waterfall.
  O caminho que ele mostra pode não ser andável naquela ordem.
- **Warp feito em C** (fora as Hidden Grottos, que ele já trata como raiz) e
  warp para `MAP_DYNAMIC`. Mapa só alcançado assim aparece `INALCANCAVEL` —
  vai para a lista de referência de propósito.
- **Warps de `data/scripts/*.inc`** só contam para o mapa cujo script chama o
  label (é o caso do Battle Arcade). Tratá-los como raiz global fazia metade
  de Hoenn parecer visitável — foi o erro da primeira versão.

## Usado por

- `.claude/rift_missions/nexus/POOL_LENDARIOS.md` — "método de obtenção" só
  conta em mapa alcançável.
- Skills `diagnosticar-flag` e `adicionar-batalha-npc`: flag ou treinador que
  só vive em mapa `INALCANCAVEL`/`fora da ROM` está morto mesmo compilando.
