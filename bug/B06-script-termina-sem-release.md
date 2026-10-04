# B06 — Scripts que terminam com `lock` ativo (NPC congelado, jogador "desliza")

**Gravidade:** BAIXA/MÉDIA (glitch visual até trocar de mapa; não trava o jogo)
**Tipo:** `lock`/`lockall` sem `release` antes de `end` · **Status:** CORRIGIDO em 30/09/2026 nos casos confirmados (build limpo; falta teste no mGBA)

## O que acontece de fato

Medido na engine: `lock` marca os objetos (inclusive o jogador) como `frozen` e
pausa a animação dos sprites. Se o script chega em `end` sem `release`:

- o jogador **ainda anda** — `frozen` só bloqueia o callback de movimento, e o
  passo do jogador é *held movement*, que roda mesmo congelado
  (`UpdateObjectEventCurrentMovement`, `src/event_object_movement.c:7286`);
- mas anda **sem animação de passo** (sprite pausado) e os NPCs do mapa ficam
  parados;
- volta ao normal no próximo `release` de qualquer script ou ao trocar de mapa.

Não é travamento; é o tipo de coisa que parece bug grave para quem joga.

## Casos confirmados à mão

| Onde | Caminho sem `release` |
|---|---|
| `CherrygroveCity_PokemonCenter/scripts.inc:35-43` `CherryGrove_Pokecenter_Chansey` | sempre. É a Chansey de **26 Centros Pokémon** vivos (todos apontam para esse script) |
| `PewterCity/scripts.inc:22-28` `PewterCity_EventScript_Gramps` | `VAR_LUGIA_OR_HOOH` ainda 0 (antes da cena de Ecruteak). O valor 2 nunca é escrito |
| `Route39_FarmHouse/scripts.inc:30-41` `FarmerM` | recusar comprar leite |
| `goto ..., Common_EventScript_BagIsFull` com bolsa cheia | `BagIsFull` termina em `return`; por `goto` isso encerra o script sem `release`. Vivos: `Gate_GoldenrodCity_Route35:54`, `GoldenrodCity_RadioTower_4F:183`, `IlexForest:193`, `Mahoganytown:230`, `NationalPark_Normal:50`, `Route5_House:7`, `SlowpokeWell_B2F:35` (e o Kurt, B03). Trocar por `Common_EventScript_ShowBagIsFull` |

A Chansey é a que vale corrigir primeiro: qualquer jogador que fale com ela
vê o efeito.

## Lista completa (com ruído)

`python3 bug/auditar_scripts.py --so TRAVA_LOCK` lista ~120 pontos; muitos são
falso positivo (ramo inalcançável depois de `switch` exaustivo, macros
`move_tutor`/`trainerbattle` que o analisador não expande, blocos `.if`).
`TRAVA_LOCK_POSSIVEL` separa os que vêm logo depois de `switch`/`goto_if
VAR_RESULT` — quase todos inalcançáveis. Revisar caso a caso antes de mexer.

## Correção aplicada (30/09/2026)

- `release` antes do `end`: Chansey dos Centros
  (`CherrygroveCity_PokemonCenter/scripts.inc`), Gramps de Pewter (com a var
  ainda 0 ele continua sem falar nada, mas libera o jogador) e fazendeiro da
  Route 39 ao recusar o leite.
- `goto ..., Common_EventScript_BagIsFull` virou `Common_EventScript_ShowBagIsFull`
  nos 7 mapas vivos (`.pory` onde existe: Gate_GoldenrodCity_Route35,
  GoldenrodCity_RadioTower_4F, IlexForest, NationalPark_Normal; `.inc`:
  Mahoganytown, Route5_House, SlowpokeWell_B2F).
- O resto da lista `TRAVA_LOCK` do analisador (87 hoje) não foi mexido: é
  majoritariamente falso positivo.

## Análise da lista completa (30/09/2026)

Os 87 achados de `TRAVA_LOCK` eram 42 pontos únicos (o mesmo script usado em
vários mapas conta várias vezes). Todos lidos à mão:

**17 reais, corrigidos com `release`/`releaseall`:** atendentes 1–3 do Safari
de Fuchsia; entrada e saída da Cycling Road (portão Celadon/Route 16, também
usado no portão da Route 18); Petrel abordado pelo norte (Radio Tower 5F);
recusa do corte de cabelo e as duas cenas da Kimono Girl no subterrâneo de
Goldenrod; despachante do Elm sem estado correspondente, "shouldn't touch" da
maleta e os dois finais da cena do policial (NewBarkTown_Lab); porta já aberta
do Rocket Hideout B3F; policial da Power Plant (3 falas); marinheiro de One
Island (usava `message` sem esperar: a caixa ficava aberta); Kurt no Slowpoke
Well B1F; "not enough valid Pokémon" do Battle Arcade.

**Bug maior achado no caminho — Ability Expert do Fighting Dojo:** o
`special SwitchMonAbility` estava comentado (a função existe em
`src/field_specials.c` mas nunca foi registrada) e o script testava
`VAR_RESULT`, que ainda valia TRUE do `checkmoney`. Toda visita cobrava
**25.000 e não trocava nada**, inclusive cancelando o menu. Agora chama a
função por `callnative`; cancelar ou escolher Ovo não cobra.

**25 falsos positivos:** `switch`/sim-não exaustivos (Name Rater, elevadores,
telefone da Darkrai Inn, Ability Expert, Ice Path), reinício do jogo
(`DoSoftReset`, `frontier_reset`), espaço já checado antes (Randy), código
morto (`FossilMonReady`), bloco `.if` (berry tree), macro `move_tutor` que o
analisador não expande, e o Battle Pyramid (código original do Emerald).
