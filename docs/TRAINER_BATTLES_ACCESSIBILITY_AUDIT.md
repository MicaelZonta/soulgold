# Auditoria: acessibilidade das batalhas de treinador (`trainers.party`)

Escopo: para cada `TRAINER_XXXX` declarado em `include/constants/opponents.h`,
verificar (1) se ele tem um time definido em `src/data/trainers.party`, (2) se
ele é de fato **acionado** por algum sistema do jogo (script de mapa
`trainerbattle*`, sistema de revanche/Match Call, Battle Dome/PWT ou Title
Defense), e cruzar as duas informações para dizer se a batalha é **acessível
em jogo** ou não.

Auditoria feita em 2026-09-12, branch `soulgold-rift-missions`. Baseado
inteiramente em busca estática no código-fonte (scripts `.pory`/`.inc`,
`src/*.c`); não foi jogado nada no emulador para confirmar em tempo de
execução.

CSV completo (1137 linhas, uma por `TRAINER_`) em
[`TRAINER_BATTLES_ACCESSIBILITY_AUDIT.csv`](TRAINER_BATTLES_ACCESSIBILITY_AUDIT.csv).

## 1. Método

- **Times definidos**: todo bloco `=== TRAINER_XXXX ===` em
  `src/data/trainers.party` (551 nomes únicos; alguns nomes se repetem porque
  o formato permite um bloco por `Difficulty`, ex. `DIFFICULTY_NORMAL` /
  `DIFFICULTY_HARD` — não é duplicidade indevida, é o recurso de "Trainer
  Difficulty" do `trainerproc`).
- **Acionado por script de mapa**: ocorrência de `TRAINER_XXXX` como argumento
  de `trainerbattle_single`, `trainerbattle_double`, `trainerbattle_no_intro`,
  `trainerbattle_rematch` ou `trainerbattle_rematch_double` em qualquer
  `data/maps/*/scripts.pory` ou `scripts.inc`.
- **Acionado por outro sistema**: aparição em `src/battle_setup.c` /
  `src/match_call.c` (tabela de revanches + Rotom Phone / PokéGear),
  `src/battle_dome.c` (Battle Dome / PWT) ou `src/title_defense.c` (sistema
  próprio deste hack de desafio dos líderes/Elite Four pós-campeão).
- `TRAINER_UNUSED_###` (210 IDs) são slots explicitamente reservados pelo
  próprio arquivo de constantes — tratados à parte, não contam como "batalha
  planejada e quebrada".

## 2. Resultado geral (1137 `TRAINER_` reais, exclui `TRAINER_NONE`)

| Status | Qtde | Significado |
|---|---:|---|
| `OK` (acessível) | 529 | Tem time **e** é acionado por algum sistema — batalha jogável hoje. |
| `BROKEN_REFERENCE` | 345 | É acionado (script de mapa e/ou revanche/etc.) **mas não tem time** em `trainers.party` — a batalha, se disparada, usaria um `Trainer` zerado. |
| `RESERVED_SLOT` | 210 | `TRAINER_UNUSED_###`, slot de expansão vazio, sem nome próprio. |
| `UNUSED_NAMED_ID` | 32 | Tem nome próprio (não é slot genérico) mas sem time e sem nenhuma referência — provável placeholder para conteúdo futuro. |
| `ORPHANED_PARTY` | 21 | Tem time completo em `trainers.party`, mas não é acionado em lugar nenhum encontrado — time morto, nunca aparece em jogo. |

Dos 345 "quebrados": **203** são chamados diretamente por um `trainerbattle*`
num script de mapa (o caso mais grave — o jogador pode literalmente andar até
o NPC e a batalha vai carregar um time vazio), e os outros **142** só
aparecem em estágios de revanche (`src/battle_setup.c`) que ainda não têm
time nem para o primeiro estágio, então nunca vão ficar acessíveis via
Match Call enquanto isso não for preenchido.

## 3. `BROKEN_REFERENCE` — o achado mais importante

Não é ruído espalhado: **é concentrado quase inteiramente em mapas de Hoenn**
que parecem ter sido importados com os scripts originais (incluindo as
chamadas `trainerbattle`) mas sem os times terem sido portados para
`trainers.party`. Contagem de NPCs quebrados por mapa (top 20, das 203
ocorrências em script de mapa):

| Mapa | NPCs quebrados |
|---|---:|
| Route119 | 10 |
| Route110 | 10 |
| Route103 | 9 |
| Route114 | 8 |
| Route111 | 8 |
| Route104 | 7 |
| MossdeepCity_Gym | 7 |
| Route115 | 6 |
| Route113 | 6 |
| LilycoveCity | 6 |
| Route123 | 5 |
| Route121 | 5 |
| Route117 | 5 |
| MtChimney | 5 |
| MagmaHideout_4F | 5 |
| VictoryRoad_1F | 4 |
| SSTidalCorridor | 4 |
| Route134 | 4 |
| Route120 | 4 |
| MagmaHideout_2F_2R | 4 |
| DewfordTown_Gym | 4 |

Exemplos concretos confirmados manualmente:
- `data/maps/Route121/scripts.inc:144` — `trainerbattle_single TRAINER_MARCEL, ...` — `TRAINER_MARCEL` sem time.
- `data/maps/MtPyre_2F/scripts.inc:36` — `trainerbattle_single TRAINER_LEAH, ...` — `TRAINER_LEAH` sem time.
- `data/maps/EverGrandeCity_ChampionsRoom/scripts.inc:43` — `trainerbattle_no_intro TRAINER_WALLACE, ...` — o próprio Wallace, campeão de Hoenn, sem time definido em nenhuma variante (`TRAINER_WALLACE` nem `TRAINER_WALLACE2`).

Também aparecem líderes de ginásio inteiros sem time (`TRAINER_ROXANNE_1`,
`TRAINER_WATTSON_1`, `TRAINER_NORMAN_1`, `TRAINER_WINONA_1`, `TRAINER_TATE_AND_LIZA_1`,
`TRAINER_JUAN_1`), o Team Magma inteiro (`TRAINER_MAXIE_MT_CHIMNEY`,
`TRAINER_MAXIE_MAGMA_HIDEOUT`, `TRAINER_TABITHA_MT_CHIMNEY`,
`TRAINER_TABITHA_MAGMA_HIDEOUT`, `TRAINER_GRUNT_MAGMA_HIDEOUT_1` a `_16`), o
Alto Comando (`TRAINER_PHOEBE`, `TRAINER_GLACIA`), e todas as variações de
rival Brendan/May por rota/starter (`TRAINER_BRENDAN_ROUTE_103_TORCHIC`,
`TRAINER_MAY_LILYCOVE_MUDKIP`, etc.) — 203 nomes completos estão no CSV com
`status=BROKEN_REFERENCE` e `used_map_script=Yes`.

**Se um jogador andar em qualquer um desses mapas hoje, essas batalhas
específicas vão ativar com um treinador sem Pokémon.** Antes de liberar essas
áreas de Hoenn para o jogador, essa lista de 203 precisa ganhar times em
`trainers.party` (ou os NPCs/scripts precisam ser removidos/desabilitados até
lá).

## 4. `ORPHANED_PARTY` — times prontos que nunca batalham

21 treinadores têm time 100% definido em `trainers.party` mas não são
chamados por nenhum script de mapa nem sistema (revanche, Battle Dome, Title
Defense):

`TRAINER_TYLER`, `TRAINER_TONY`, `TRAINER_VERONICA`, `TRAINER_THERESA`,
`TRAINER_STEVE`, `TRAINER_KOJI`, `TRAINER_BLUE_2`, `TRAINER_GRUNT`,
`TRAINER_GRUNT_24`, `TRAINER_GRUNT_25`, `TRAINER_GRUNT_30`,
`TRAINER_GRUNT_32`, `TRAINER_RUSS`, `TRAINER_HARVEY`, `TRAINER_WALTER`,
`TRAINER_KENDRA`, `TRAINER_ANDY`, `TRAINER_JOHN`, `TRAINER_ETHEL`,
`TRAINER_CARLENE`, `TRAINER_KUKUI`.

Alguns nomes chamam atenção (`TRAINER_KUKUI`, `TRAINER_JOHN`, `TRAINER_STEVE`)
por soarem como personagens de Alola — coerente com a hipótese de que são
conteúdo preparado com antecedência para uma futura região/arco (a julgar
pelos commits recentes "Ultra Dimenssion Start" / "Rift Missions"), só que
ainda sem NPC/script no mapa apontando pra eles. Time pronto não é uma
"batalha quebrada" (não crasha nada), só é conteúdo morto até alguém colocar
um NPC ou entrada de revanche usando esse ID.

## 5. `UNUSED_NAMED_ID` — placeholders explícitos

32 nomes têm ID e nome próprios reservados no `opponents.h` mas nenhum time
nem uso. A maioria é claramente estágio futuro de uma cadeia de revanche já
em uso (ex. `TRAINER_VALERIE_4`/`_5`, `TRAINER_TIMOTHY_3`/`_4`/`_5`,
`TRAINER_WINSTON_5`, `TRAINER_LOLA_2`/`_3`/`_4`, `TRAINER_CHANSEY3`/`_4`/`_5`)
ou placeholders nomeados como tal (`TRAINER_BRENDAN_PLACEHOLDER`,
`TRAINER_MAY_PLACEHOLDER`, `TRAINER_UNUSEDNAME_2`). Lista completa no CSV
(`status=UNUSED_NAMED_ID`).

## 6. `RESERVED_SLOT`

210 `TRAINER_UNUSED_###` — apenas espaço reservado em `opponents.h` para
crescimento futuro do array `gTrainers`. Não representam trabalho pendente,
listados no CSV só por completude.

## 7. Colunas do CSV

| Coluna | Significado |
|---|---|
| `id` | ID numérico do treinador em `opponents.h`. |
| `name` | Constante `TRAINER_XXXX`. |
| `has_party` | `Yes`/`No` — tem bloco de time em `trainers.party`. |
| `used_map_script` | `Yes`/`No` — aparece em `trainerbattle*` em algum `scripts.pory`/`.inc`. |
| `used_other_system` | `Rematch/MatchCall`, `BattleDome/PWT`, `TitleDefense`, combinação delas com `\|`, ou `-`. |
| `status` | `OK` / `BROKEN_REFERENCE` / `ORPHANED_PARTY` / `UNUSED_NAMED_ID` / `RESERVED_SLOT`. |
| `accessible` | `Yes` / `No` / `N/A` (para slots/placeholders sem uso nenhum). |
| `reason` | Explicação em uma frase do veredito. |

## 8. Limitações

- Verificação puramente estática (grep sobre `.pory`/`.inc`/`.c`). Não cobre
  lógica que monta o ID do treinador dinamicamente em runtime a partir de uma
  variável (nenhum caso desses foi encontrado nos sistemas revisados, mas não
  dá pra descartar 100%).
- Battle Frontier, Battle Tent e Trainer Hill usam suas próprias tabelas
  (`battle_frontier_trainers.h`, `battle_tent.h`, `trainer_hill.h`) que **não**
  referenciam `TRAINER_XXXX` — são geradas a partir de outro pool de dados e
  ficam fora do escopo desta auditoria (não afetam o resultado acima).
- Não confirma que o **caminho até o mapa** esteja liberado (ex. se o mapa em
  si é alcançável nesta versão do jogo) — só que, uma vez no mapa, o script
  do NPC dispara com ou sem time válido.
