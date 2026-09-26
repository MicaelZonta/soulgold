# Auditoria de flags — SoulGold

Levantamento completo do espaço de flags: o que existe, o que o jogo realmente
usa, o que está morto, quanto sobra e onde dá para otimizar.

- Levantamento: 24/09/2026 · revisado 25/09/2026 (higienização dos itens 1–3 da
  seção 10 aplicada) · branch `soulgold-rift-missions`
- Fonte de verdade: `include/constants/flags.h` + varredura de todo arquivo versionado
- Tabela linha a linha das 1735 flags: [`docs/SOULGOLD_FLAGS_AUDIT.csv`](../docs/SOULGOLD_FLAGS_AUDIT.csv)
- Para refazer o levantamento: `python3 dev_scripts/flag_audit.py --csv`

---

## 1. Resumo executivo

| Pergunta | Resposta |
|---|---|
| Quantas flags existem nomeadas? | **1735** defines (1713 valores distintos — 22 valores têm dois nomes) |
| Quanto o save reserva? | `FLAGS_COUNT = 5448` (0x1548) = **681 bytes** em `SaveBlock1.flags[]` |
| Quantas o jogo realmente usa? | **1300** |
| Quantas nunca são referenciadas em lugar nenhum? | **250** (246 + 4 citadas só em doc) |
| Quantas só existem para mapas que não entram na ROM (Hoenn)? | **141** |
| Quantas são escritas e nunca lidas (não fazem nada)? | **39** |
| Quantas são lidas e nunca escritas (provável bug)? | **5** |
| Quantos slots do espaço de flags não têm nome nenhum? | **2692** |
| Quantas flags novas posso criar hoje sem tocar no save? | **~3100** (2692 buracos + ~430 recicláveis) |
| Dá para aumentar `FLAGS_COUNT`? | Só em **+8**, e isso é *outra* conta: é o quanto o array pode crescer **depois** de esgotar os 2692 slots livres dentro dele. Ver seção 3 |
| Alguma flag está fora do array? | **Nenhuma.** Era `FLAG_R39_NORTH_ROCKY_HELMET = 0x2A92`, corrigida para `0x2A9` em 25/09/2026 — seção 7.1 |

O quadro é folgado: não há escassez de flags. O que existe é **bagunça** —
duas flags para a mesma coisa, flags setadas que ninguém lê, um bloco de
Hoenn morto no meio do espaço baixo, e um bloco oficial para flags novas
(`CUSTOM_FLAGS`) que já está 100% cheio enquanto 1209 slots livres esperam
logo depois dele.

---

## 2. Como o espaço está organizado

`FLAGS_COUNT` é 5448. O intervalo `0x0000–0x1547` se divide assim:

| Faixa | Bloco | Slots | Ocupados | O que é |
|---|---|---:|---:|---|
| `0x000–0x01F` | TEMP | 32 | 31 | RAM; zeram ao carregar o mapa. Não custam save |
| `0x020–0x4FF` | SCRIPT/EVENT | 1248 | 1231 | Herança do Emerald + tudo que SoulGold acrescentou por cima |
| `0x500–0x91F` | TRAINER | 1056 | (implícito) | `TRAINER_FLAGS_START + id do treinador`; 543 IDs em uso |
| `0x920–0x98B` | RECLAIMED_TRAINER | 108 | 108 | IDs de treinador 1056–1163 reaproveitados como flags comuns |
| `0x98C–0xA4B` | SYSTEM | 192 | 192 | `SYSTEM_FLAGS` + conteúdo novo do hack |
| `0xA4C–0xFFF` | — | 1460 | 0 | **vazio** |
| `0x1000–0x1046` | CUSTOM | 71 | 71 | Bloco oficial de flags standalone novas — **cheio** |
| `0x1047–0x14FF` | — | 1209 | 0 | **vazio** |
| `0x1500–0x1507` | cauda | 8 | 1 | `FLAG_0x1500` + padding até `DAILY_FLAGS_START` |
| `0x1508–0x1547` | DAILY | 64 | 64 | Zeram na virada do dia |

("Ocupados" conta posições distintas; 1735 nomes cobrem 1713 posições porque 22
valores têm dois nomes — ver 8.1.)

Fora do save, em EWRAM: `SPECIAL_FLAGS` (`0x4000–0x407F`, 6 nomeadas de 128) e,
só em build de teste, `TESTING_FLAGS` (`0x5000+`).

**Ocupação por bloco e situação de uso:**

```
bloco                 nomes    uso  nunca   fora   so_w   so_r
TEMP                     36     29      4      3      0      0
SCRIPT/EVENT           1248    878    200    137     29      3
RECLAIMED_TRAINER       108     99      5      0      4      0
SYSTEM                  192    169     11      0      7      5
CUSTOM                   71     71      0      0      0      0
DAILY                    65     42     22      0      0      1
SPECIAL(EWRAM)            6      5      1      0      0      0
TESTING                   8      3      5      0      0      0
```

(`fora` = só usada em mapa que não entra na ROM; `so_w` = só escrita;
`so_r` = só lida.)

### 2.1 Buracos livres

```
0xA4C-0xFFF    1460 slots
0x1047-0x14FF  1209 slots
0x19A-0x1A9      16 slots   <- dentro do bloco Match Call, ver 8.1
0x1501-0x1507     7 slots
```

Esses 2692 slots **já estão pagos**: os bytes existem no save hoje, zerados.
Usá-los não muda o tamanho de nada e não quebra save nenhum.

---

## 3. O teto real: `FLAGS_COUNT` está praticamente congelado

`SaveBlock1.flags[]` fica em `0x1270`, **antes** de `vars[]`, `gameStats[]` e de
tudo mais. `src/save.c` trava os offsets seguintes com `STATIC_ASSERT`:

```c
STATIC_ASSERT(offsetof(struct SaveBlock1, registeredItems) == 0x3484, ...);
STATIC_ASSERT(offsetof(struct SaveBlock1, futureReserved)  == 0x349A, ...);
STATIC_ASSERT(sizeof(struct SaveBlock1) == 0x3C54, SaveBlock1LegacySize);
```

Aumentar `FLAGS_COUNT` empurra todo o resto e derruba esses asserts — o que é
exatamente a proteção certa, porque esse deslocamento corromperia os saves que
já existem por aí.

Testado neste levantamento (compilando `build/emerald/src/save.o` com
`FLAGS_COUNT` alterado e revertendo em seguida):

| `FLAGS_COUNT` | `NUM_FLAG_BYTES` | Resultado |
|---|---:|---|
| 5448 (atual) | 681 | compila |
| **5456 (+8)** | 682 | **compila** — o byte de padding antes de `vars[]` (u16) absorve |
| 5464 (+16) | 683 | `SaveBlock1ShortcutMagicOffset ... is negative` |
| 7496 (+2048) | 938 | idem, 4 asserts quebrados |

Ou seja: **existem exatamente 8 flags a mais disponíveis por crescimento**, e
nem um bit além. Isso não se soma nem se confunde com os 2692 slots da seção
2.1: aqueles já estão *dentro* do array de hoje e não dependem de crescer
coisa nenhuma — são eles que você vai gastar nos próximos anos. O +8 só
entraria em cena depois que os 2692 acabassem. `SAVEBLOCK1_FUTURE_RESERVED_BYTES` (1978 bytes, em
`include/config/save.h`) **não ajuda**: ele fica no fim da struct, depois dos
offsets travados; reduzi-lo não compensa o empurrão que `flags[]` dá.

Se um dia forem necessários milhares de bits a mais, o caminho é um segundo
array (`flags2[]`) alocado **dentro** de `futureReserved`, com `FlagGet`/`FlagSet`
roteando por faixa. Não é necessário hoje: sobram 2692 slots no array atual.

---

## 4. Onde criar flag nova, hoje

`include/global.h` já define a política e a protege com asserts:

```c
STATIC_ASSERT(SYSTEM_FLAGS_END < CUSTOM_FLAGS_START, CustomFlagsOverlapSystemFlags);
STATIC_ASSERT(CUSTOM_FLAGS_END < FLAG_0x1500, CustomFlagsOverflowAllocation);
```

> "all new standalone flags belong in CUSTOM_FLAGS"

Só que `CUSTOM_FLAGS` (`0x1000–0x1046`) **está cheio**: 71 de 71 slots
nomeados e em uso. O assert permite crescer até `0x14FF`.

**Recomendação:** continuar a numeração a partir de `0x1047` e seguir movendo
`CUSTOM_FLAGS_END` para a última alocação, como o comentário do arquivo já
manda. São **1209 flags** disponíveis nesse bloco, sem tocar em save, sem
tocar em `FLAGS_COUNT`, sem risco de colisão com treinador, Match Call ou
bloco diário.

Desde 25/09/2026 isso está escrito no próprio `flags.h`: o cabeçalho do bloco
documenta a faixa `0x1000–0x14FF` e há um marcador `// PROXIMA FLAG NOVA: 0x1047`
logo abaixo de `CUSTOM_FLAGS_END`.

A segunda reserva (`0xA4C–0xFFF`, 1460 slots) fica logo depois de
`SYSTEM_FLAGS`. Vale deixá-la para expansão de `SYSTEM_FLAGS`/conteúdo novo e
não misturar os dois usos.

**Não usar:**
- `0x19A–0x1A9` — dentro do bloco Match Call (seção 8.1)
- qualquer coisa em `0x500–0x91F` — são flags de treinador por ID
- `FLAG_TEMP_*` para estado que precisa sobreviver à troca de mapa

---

## 5. Flags de Hoenn: 140 flags para mapas que não existem no jogo

`data/maps/map_groups.json` tem `rom_excluded_groups` com
`gMapGroup_Emerald1..5`. `tools/mapjson/mapjson.cpp` e
`tools/mapjson/filter_event_scripts.py` removem esses mapas da ROM inteira —
headers, eventos, conexões, layouts e scripts. São **432 mapas fora do jogo**
(486 do grupo menos os 54 de `rom_shared_script_maps`, cujos scripts continuam
montados porque mapas vivos chamam rotinas deles).

**140 flags só aparecem nesses mapas mortos.** Não há um `setflag` sequer em
conteúdo alcançável; são bits que nunca mudam numa partida real.

Casos que valem atenção antes de reciclar (nome enganoso, conteúdo vivo
equivalente pode existir com **outra** flag):

- `FLAG_DEFEATED_ENTEI` / `RAIKOU` / `SUICUNE` (`0x465–0x467`) — só nos mapas
  `MagmaHideout_3F_1R_Entei`, `NewMauville_Inside_Raikou`,
  `ShoalCave_LowTideIceRoom_Suicune`, todos fora da ROM. Os cães do jogo usam
  outro caminho (ver `FLAG_CAUGHT_ENTEI`/`RAIKOU` na seção 7.4)
- `FLAG_DEFEATED_MEWTWO` (`0x4B`) — `CeruleanCave3` está fora; a caverna viva é
  `CeruleanCave_1F/B1F/B2F`
- `FLAG_DEFEATED_ARTICUNO/ZAPDOS/MOLTRES`, `FLAG_UNLOCK_BIRDS` — mapas
  `*_Articuno/_Zapdos/_Moltres2` do grupo Emerald3
- `FLAG_HIDDEN_ITEM_*` de rotas de Hoenn (Route 104–128, Petalburg, Artisan
  Cave, Safari Zone de Hoenn) — 45 delas

Lista completa das 140 (valor, nome, mapa morto onde aparece): **anexo A**.

### 5.1 A zona cinzenta: 56 flags só em `rom_shared_script_maps`

Os 54 mapas de `rom_shared_script_maps` são um caso à parte: o **mapa** não
entra na ROM (header, eventos e layout são removidos), mas o `scripts.inc`
**continua montado**, porque rotinas dele são chamadas de conteúdo vivo. Esta
auditoria os trata como vivos — é a leitura conservadora.

**56 flags** têm como único mapa "vivo" um desses. Concentram-se em:

```
SootopolisCity             7      BattleFrontier_ExchangeServiceCorner  4
MauvilleCity               6      Route120 / TrickHousePuzzle1          3 cada
LilycoveCity_ContestLobby  6      LittlerootTown_MaysHouse_1F/2F        3 cada
```

Exemplos: `FLAG_MET_RIVAL_MOM`, `FLAG_TV_EXPLAINED`, `FLAG_BIRCH_AIDE_MET`,
`FLAG_MAUVILLE_GYM_BARRIERS_STATE`, `FLAG_UNLOCK_MEWTWO`,
`FLAG_RECEIVED_POTION_OLDALE`, `FLAG_DEFEATED_RIVAL_ROUTE103`,
`FLAG_TEMP_1B/1C/1E`.

Para reciclar qualquer uma delas é preciso primeiro checar se a **label** que a
usa é realmente chamada de um mapa vivo (`git grep "<label>" data/maps`). Se
não for, a flag é tão morta quanto as 140 da lista acima — só que sem prova
automática.

---

## 6. 250 flags que nunca são referenciadas

Nenhuma ocorrência em script, em `map.json`, em `src/`, em `test/`. Divisão:

- **151** com nome "real" (alguém alocou e nunca usou) — anexo B
- **56** `FLAG_REGISTERED_*` do Match Call (usadas implicitamente por aritmética
  — seção 8.1)
- **42** já nomeadas `FLAG_UNUSED_*` / `FLAG_GARBAGE*` — anexo C

Destaques do primeiro grupo:

- `FLAG_MOVE_TUTOR_TAUGHT_*` (`0x1B1–0x1BA`) — 10 flags do tutor de Hoenn
- `FLAG_SYS_NO_COLLISION`, `NO_TRAINER_SEE`, `NO_BAG_USE`, `NO_BATTLE_DMG`,
  `PC_FROM_DEBUG_MENU` — debug que o menu atual não usa
- `FLAG_HIDE_ILEX_FOREST_FARFETCHD`, `FLAG_HIDE_LAKEOFRAGE_POLICE`,
  `FLAG_HIDE_WHIRLISLANDS_GUARD`, `FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_1..3` —
  ocultação de NPC de Johto que ficou pelo caminho
- `FLAG_UNLOCKED_KURT_BALLS`, `FLAG_POSTGAME_CAP2..4`, `FLAG_JIRACHI`,
  `FLAG_INCREASE_DIFFICULTY`, `FLAG_NO_SHINY`, `FLAG_EVEN_FASTER_JOY`,
  `FLAG_LIMIT_TO_50`, `FLAG_UNLOCK_DOGS` — features alocadas e não implementadas
  (ou implementadas por outro mecanismo)
- `FLAG_ITEM_*` diversas (`0x3F9`, `0x435`, `0x45D`, `0x463`, `0x46A`, `0x478`,
  `0x489`, `0x4DE`) — item ball que não existe no mapa

> Antes de reciclar qualquer uma destas: elas podem ser o "gancho" de uma
> feature que o autor ainda pretende fazer. O CSV traz o comentário original
> de cada uma.

---

## 7. Problemas encontrados (isto é o que vale corrigir)

### 7.1 `FLAG_R39_NORTH_ROCKY_HELMET` escrevia fora do array de flags — RESOLVIDO 25/09/2026

> **Corrigido.** `flags.h` agora traz `0x2A9`, e `flag_audit.py` não acusa mais
> flag fora de `flags[]`. O buraco de um slot da seção 2.1 sumiu com isso.
> Efeito em save antigo: quem já pegou o Rocky Helmet pega de novo uma vez.

```c
#define FLAG_R39_NORTH_TRADE         0x2A8
#define FLAG_R39_NORTH_ROCKY_HELMET  0x2A92   // <- linha 732 de flags.h
#define FLAG_COLLISION               0x2AA
```

`0x2A92` é dígito a mais em `0x2A9` — e `0x2A9` é, não por acaso, o único
buraco de um slot só que a varredura encontrou na faixa baixa.

O valor 0x2A92 (10898) é maior que `FLAGS_COUNT` (5448) e menor que
`SPECIAL_FLAGS_START`, então `GetFlagPointer` (`src/event_data.c:329`) devolve
`&gSaveBlock1Ptr->flags[1362]` sem checar limite — mas `flags[]` só tem 681
bytes. `setflag FLAG_R39_NORTH_ROCKY_HELMET`
(`data/maps/Gate_Route39North/scripts.pory:31`) liga o bit 2 do byte 680 de
`vars[]`, isto é, o byte baixo de **`VAR 0x4154`** (`vars[340]`).

Hoje isso não causa dano visível: a maior var nomeada é `VAR_KURT_TODAY`
(`0x4121`), então `0x4154` está vazia e o bit se comporta como uma flag
qualquer — o `goto_if_set` da linha 23 lê o mesmo lugar e funciona. O problema
é que é uma bomba-relógio: no dia em que alguém alocar `VAR 0x4154`, pegar o
Rocky Helmet passa a somar 4 nessa var, e mexer nela passa a "desfazer" o
presente.

Foi trocado `0x2A92` por `0x2A9` em `flags.h` (o `.pory` usa o nome, não o
número, e não precisou mudar). Custo para quem já jogou: o bit muda de lugar,
então quem já pegou o Rocky Helmet consegue pegar de novo uma vez. Nada além
disso.

### 7.2 `FLAG_SYS_NO_CATCHING` não desligava captura nenhuma — RESOLVIDO 25/09/2026

> **Corrigido.** Route41 (`scripts.pory`) e SaffronCity_FightingDojo
> (`scripts.inc`, 6 pares) agora usam `B_FLAG_NO_CATCHING`. O define de
> `FLAG_SYS_NO_CATCHING` ganhou um `// NAO USE` no `flags.h`; as ocorrências que
> sobraram estão só em MagmaHideout/NewMauville/ShoalCave, fora da ROM, e por
> isso a flag passou de `SO_ESCRITA` para `SO_MAPAS_FORA_DA_ROM` no catálogo.

A engine lê `B_FLAG_NO_CATCHING`, e `include/config/battle.h` define:

```c
#define B_FLAG_NO_CATCHING   FLAG_NO_CATCHING    // 0x1041
```

As Rift Missions fazem certo (`setflag B_FLAG_NO_CATCHING` em Blackthorn,
Cherrygrove, Mahogany, NewBark, UltraSpaceArena). Mas dois mapas vivos setam a
flag **errada**, `FLAG_SYS_NO_CATCHING` (`0x24`), que nada lê:

- `data/maps/Route41/scripts.pory:202` e `:207`
- `data/maps/SaffronCity_FightingDojo/scripts.inc` — 6 pares set/clear

Efeito no jogo: nessas batalhas o jogador **ainda conseguia capturar**. Os dois
passaram a usar `B_FLAG_NO_CATCHING`. O Dojo não tem `.pory`, então a edição foi
direto no `.inc`; Route41 tem, e só o `.pory` foi tocado.

### 7.3 Duas flags de EXP Share, só uma funciona

- `FLAG_EXP_SHARE_OPTION` (`0x296`) — é a que `include/config/item.h` liga em
  `I_EXP_SHARE_FLAG`; setada em `Gate_Route31_VioletCity`. **Funciona.**
- `FLAG_EXP_SHARE` (`0x4A6`) — setada 4× em `NewBarkTown_Lab`, lida por
  ninguém. **Não faz nada.**

### 7.4 As três flags de level scaling não ligam nada

`Route36/scripts.pory:135-137` seta `FLAG_TRAINER_LEVELSCALING`,
`FLAG_WILD_LEVELSCALING` e `FLAG_LEVEL_SCALING_ON`. Nenhuma é lida em lugar
nenhum: o scaling é decidido em `include/config/level_scaling.h`
(`B_LEVEL_SCALING_ENABLED TRUE`). Ou o NPC deveria mexer em algo de verdade,
ou as três linhas são decorativas.

### 7.5 40 flags escritas que ninguém lê

O padrão se repete: o script marca progresso e nada consulta a marca. Alguns
são inofensivos (`FLAG_CAMERON_PHOTO2..4`), outros indicam feature pela metade:

- `FLAG_BADGE13_GET`, `FLAG_BADGE14_GET`, `FLAG_BADGE15_GET` — os ginásios de
  Kanto setam, mas o cartão de treinador desenha as insígnias 9–16 a partir de
  `sKantoGymFlags[]` (`src/trainer_card.c:48`), que usa
  `FLAG_DEFEATED_*_GYM`. As oito `FLAG_BADGE09..16_GET` são redundantes
- `FLAG_CAUGHT_ENTEI`, `FLAG_CAUGHT_RAIKOU` (`EcruteakCity`) — setadas, nunca
  checadas; o "já peguei o cão" é decidido por outro caminho
- `FLAG_HIDE_ILEX_FOREST_KURT` (6 escritas), `FLAG_HIDE_OLIVINE_PORT_OAK` (3),
  `FLAG_HIDE_ROUTE22_JANINE` (3) — flag de ocultação que **nenhum** `map.json`
  referencia no campo `flag`. Escondem/mostram coisa nenhuma
- `FLAG_ALLOW_SOUTH_JOHTO_PASS`, `FLAG_GET_HEADBUTT`,
  `FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT`, `FLAG_ROCKETHIDEOUT2_BATTLE`

Lista completa: anexo D.

### 7.6 5 flags lidas que ninguém escreve

Estas são as mais perigosas — o `goto_if_set` nunca dá verdadeiro:

```
0x02D  FLAG_NO_WT_BECAUSE_CHALLENGE                  BattleFrontier_ExchangeServiceCorner
0x0F7  FLAG_DEFEATED_SS_TIDAL_TRAINERS               SSTidalCorridor
0x128  FLAG_PETALBURG_MART_EXPANDED_ITEMS          
0xA1C  FLAG_SYS_LAKE_OF_RAGE_TIDE                    LakeOfRage
0x150B FLAG_DAILY_BUG_CONTEST_COMPLETED              Gate_NationalPark
```

- `FLAG_SYS_LAKE_OF_RAGE_TIDE`, `FLAG_DAILY_BUG_CONTEST_COMPLETED` (o concurso
  vivo usa `FLAG_DAILY_BUG_DONE`), `FLAG_NO_WT_BECAUSE_CHALLENGE`

#### `FLAG_ICEPATH_BOULDER1..4` era alarme falso — verificado 25/09/2026

A lista original trazia `0xA46–0xA49`. **O quebra-cabeça funciona**: quem liga
essas flags é a engine, não script nenhum, e por isso a varredura não via a
escrita.

As quatro são o campo `"flag"` dos quatro `OBJ_EVENT_GFX_PUSHABLE_BOULDER` de
`IcePath_B1F`. Ao empurrar uma pedra para um buraco (`MB_MT_PYRE_HOLE`, medido
em `data/layouts/IcePath_B1F/map.bin` nas posições 17,7 · 10,12 · 11,17 ·
18,18), `PushBoulder_End` chama `HandleBoulderFallThroughHole`
(`src/field_control_avatar.c:1461`), que chama
`RemoveObjectEventByLocalIdAndMap` — e esta faz
`FlagSet(flagId do template)` (`src/event_object_movement.c:1593`). O bit fica
gravado no save. `IcePath_B2F` lê as quatro no `ON_TRANSITION` (`SetBoulders`)
e usa `FLAG_TEMP_1..4` para esconder a pedra correspondente lá embaixo.

Dois detalhes que sobraram, nenhum deles quebra o jogo:

- O `FlagClear(trainerType)` da mesma função é no-op aqui: os quatro objetos têm
  `trainer_type: TRAINER_TYPE_NONE`, e `GetFlagPointer(0)` devolve `NULL`. Não
  faz falta, porque `FLAG_TEMP_*` zera ao carregar o mapa e quem decide a
  visibilidade em B2F é o `ON_TRANSITION`
- `IcePath_B1F/scripts.inc` abre com quatro `.set LOCALID_ICEPATH2_BOULDER*` que
  não batem com a ordem dos objetos no `map.json` e que nenhum script usa

**Isso era um defeito do `flag_audit.py`, corrigido junto:** `SO_ESCRITA` já
descartava flags citadas em `map.json`, `SO_LEITURA` não. Qualquer flag no campo
`"flag"` de um `object_event` pode ser escrita pela engine sem aparecer por nome
em script nenhum — `removeobject` (`ScrCmd_removeobject`) e o item ball comum
passam pelo mesmo `RemoveObjectEventByLocalIdAndMap`. A regra ficou simétrica, e
as quatro voltaram para `EM_USO`.

### 7.7 Flag de ocultação usada em `map.json` e nunca escrita

Objeto com `"flag"` preenchido que nada seta nem limpa: fica **visível para
sempre** (a flag nasce zerada) e o `setflag` de "já peguei / já saiu" nunca
acontece.

```
0x42D  FLAG_ITEM_ROCKETHIDEOUT1_BIG_NUGGET      RocketHideout, RocketHideout_B1F
0x42E  FLAG_ITEM_ROCKETHIDEOUT1_REVIVE          RocketHideout, RocketHideout_B1F
0x42F  FLAG_ITEM_ROCKETHIDEOUT1_HYPER_POTION    RocketHideout, RocketHideout_B1F
0x430  FLAG_ITEM_ROCKETHIDEOUT2_TM_THIEF        RocketHideout_B2F
0x431  FLAG_ITEM_ROCKETHIDEOUT3_ICE_HEAL        RocketHideout_B3F
0x432  FLAG_ITEM_ROCKETHIDEOUT3_PROTEIN         RocketHideout_B3F
0x433  FLAG_ITEM_ROCKETHIDEOUT3_FULL_HEAL       RocketHideout_B3F
0x434  FLAG_ITEM_ROCKETHIDEOUT3_GUARD_SPEC      RocketHideout_B3F
0x95A  FLAG_HIDE_SPROUT_BASEMENT_ITEM           SproutTower_Basement
0xA34  FLAG_HIDE_ROUTE34_RIVAL                  Route34
```

As oito do Rocket Hideout são item balls: o item ball comum é apagado pela
própria engine ao ser pego, então provavelmente estão certas — mas as três
primeiras aparecem em **dois** mapas (`RocketHideout` e `RocketHideout_B1F`),
o que significa o mesmo bit servindo a dois objetos. Vale conferir no Porymap.
`FLAG_HIDE_ROUTE34_RIVAL` e `FLAG_HIDE_SPROUT_BASEMENT_ITEM` são as que
merecem olhada de verdade.

---

## 8. Armadilhas estruturais (não são bugs, mas mordem)

### 8.1 `FLAG_UNUSED_165` e companhia **não** são livres

O bloco de registro do Match Call é implícito:

```c
FlagSet(TRAINER_REGISTERED_FLAGS_START + index);   // src/pokenav_match_call_data.c:1173
```

`TRAINER_REGISTERED_FLAGS_START = 0x15C` e há 61 entradas de rematch, ou seja
o bloco ocupa **`0x15C–0x198`**. Só que 11 posições dentro desse intervalo
foram renomeadas como reutilizáveis:

```
0x165 FLAG_UNUSED_165 == FLAG_REGISTERED_CINDY      0x17B FLAG_UNUSED_17B == FLAG_REGISTERED_MADELINE
0x167 FLAG_UNUSED_167 == FLAG_REGISTERED_KOJI       0x17C FLAG_UNUSED_17C == FLAG_REGISTERED_JENNY
0x169 FLAG_UNUSED_169 == FLAG_REGISTERED_DALTON     0x181 FLAG_UNUSED_181 == FLAG_REGISTERED_EDWIN
0x16A FLAG_UNUSED_16A == FLAG_REGISTERED_BERNIE     0x184 FLAG_UNUSED_184 == FLAG_REGISTERED_GABRIELLE
0x16B FLAG_UNUSED_16B == FLAG_REGISTERED_ETHAN      0x185 FLAG_UNUSED_185 == FLAG_REGISTERED_CATHERINE
0x16C FLAG_UNUSED_16C == FLAG_REGISTERED_JOHN_AND_JAY  (+ 0x176, 0x179, 0x186, 0x187, 0x188)
```

Na prática o risco hoje é baixo: nenhum treinador da `gRematchTable` aparece
em mapa vivo (`TRAINER_ROSE_1`, `TRAINER_ANDRES_1`, … não são batalháveis), e
o `FlagSet` só roda ao derrotar um deles. Mas o alias está lá: se um dia um
rematch voltar a existir, ele escreve por cima da feature que usar
`FLAG_UNUSED_165`. **Prefira `CUSTOM_FLAGS` a qualquer `FLAG_UNUSED_1xx`.**

### 8.2 `FLAG_GARBAGEFLAG` (`0x53`) é a flag-lixo do projeto

1411 ocorrências em 317 arquivos, 224 mapas. É a flag que objetos "sempre
visíveis" carregam no campo `flag` do `map.json`. Consequência prática: um
`setflag FLAG_GARBAGEFLAG` some com centenas de NPCs ao mesmo tempo. Nunca
escrever nela; nunca reciclar `0x53`.

### 8.3 Flags de treinador são implícitas

`0x500 + id` é a flag "já derrotei este treinador". 1164 slots reservados,
**543 IDs realmente usados**. Os IDs 1056–1163 foram formalmente reaproveitados
como flags comuns (`RECLAIMED_TRAINER_FLAGS_START = 0x920`), com trava em
`include/global.h`:

```c
STATIC_ASSERT(TRAINER_TITLE_DEFENSE_LEAF < TRAINER_UNUSED_192, TrainersOverlapReclaimedFlags);
```

Esse bloco está **cheio** (108/108). Os ~510 IDs não usados abaixo de 1056
continuam reservados — dá para reclamá-los do mesmo jeito no futuro, mas é
trabalho mais arriscado (cada ID reclamado some da lista de treinadores
disponíveis) e desnecessário enquanto `0x1047–0x14FF` estiver vazio. O
histórico dessa limpeza está em `docs/SOULGOLD_TRAINER_REMOVAL_*.csv`.

### 8.4 Bloco diário

`0x1508–0x1547`, 64 slots, todos nomeados — mas **22 nunca referenciados**
(incluindo `FLAG_UNUSED_0x94F..0x95F`, 17 seguidos no fim do bloco, e as
berries de rotas de Hoenn). Quem precisar de "uma vez por dia" tem 17 slots
prontos ali.

### 8.5 `FLAG_TEMP_*` não custa save

32 bits em RAM, zerados a cada carregamento de mapa. 4 estão livres
(`FLAG_TEMP_B/C/D/F`) e outras só aparecem em mapas de Hoenn
(`FLAG_TEMP_1D`, `1F`, `11`). Estado que só precisa durar uma cena deve usar
essas, não flag persistente — vale como regra de revisão.

---

## 9. Escopo: flags que vivem dentro de um mapa só

**577 flags** (de 1296 em uso) só aparecem em um único mapa vivo, espalhadas
por **222 mapas**. É o perfil normal de um romhack: item ball, hidden item,
"já falei com este NPC", ocultação local.

Na lista abaixo, `SootopolisCity`, `MauvilleCity` e `LilycoveCity_ContestLobby`
são mapas de `rom_shared_script_maps` — contam como vivos porque o script deles
está montado, mas o mapa não existe (seção 5.1).

Mapas que mais concentram flags próprias:

```
BattleCafe                                   19
RuinsOfAlph_PuzzleAndRewardChambers          16
VajraDesertEast                              9
IlexForest                                   8
Route47                                      8
SootopolisCity                               7
GoldenrodCity_UndergroundSwitches            7
MtMortar_1F_North                            7
LilycoveCity_ContestLobby                    6
EcruteakCity                                 6
Route32                                      6
Route34                                      6
Route27                                      6
BattleFrontier_BattleTowerMultiPartnerRoom   6
ViridianForest                               6
MtMortar_Depths_1                            6
MeteorCave1_LegendaryRoom                    6
MeteorCave2_LegendaryRoom                    6
SnowtopMountain_B1F                          5
MauvilleCity                                 5
```

Isso é diagnóstico, não problema. O que vale observar:

- `BattleCafe` (19) e `RuinsOfAlph_PuzzleAndRewardChambers` (16) são sistemas
  inteiros construídos em flags. Se algum dia precisarem de mais estado,
  provavelmente é caso de `VAR_*` com bitfield, não de mais 19 flags
- Flag de escopo local que guarda estado **de uma visita só** (cena, diálogo em
  andamento, quem já falou) deveria ser `FLAG_TEMP_*` ou `VAR_TEMP_*`. A skill
  `batalha-sem-blackout` já documenta esse padrão

---

## 10. Plano de otimização sugerido

Em ordem de retorno sobre esforço:

**1. Barato e sem risco — desbloquear espaço para o que vem por aí** — ✅ FEITO
em 25/09/2026. O cabeçalho do bloco em `flags.h` agora diz que `CUSTOM_FLAGS` vai
até `0x14FF`, e logo abaixo de `CUSTOM_FLAGS_END` há um marcador
`// PROXIMA FLAG NOVA: 0x1047`. Nenhum número foi alocado ainda: os 1209 slots
continuam livres e o `STATIC_ASSERT(CUSTOM_FLAGS_END < FLAG_0x1500)` continua
sendo o teto.

**2. Corrigir os bugs da seção 7** — ✅ FEITO em 25/09/2026 para os três que
estavam na fila. O `0x2A92` virou `0x2A9` (7.1); Route41 e Saffron Dojo passaram
a usar `B_FLAG_NO_CATCHING` (7.2); e `FLAG_ICEPATH_BOULDER1..4` (7.6) era alarme
falso — o quebra-cabeça funciona, quem escreve as quatro é a engine, e o que foi
corrigido ali foi o `flag_audit.py`. Continuam abertos, sem dono: 7.3 (EXP
Share), 7.4 (level scaling), 7.5 (40 → 39 flags só escritas), o resto do 7.6 e o
7.7.

**3. Limpeza declarativa (não muda save)** — ✅ FEITO em 25/09/2026. `flags.h`
ganhou 141 marcadores `// fora da ROM` e 136 `// livre desde 24/09/2026`, mais
uma legenda no topo do arquivo explicando os dois e um aviso em bloco nos 16
`FLAG_UNUSED_1xx` do Match Call (8.1). Foram 136 e não 151 porque as que o nome
(`FLAG_UNUSED_*`, `FLAG_GARBAGE*`, `FLAG_REGISTERED_*`, `TESTING_FLAG_UNUSED_*`)
ou o comentário (`// Unused Flag`) já denunciavam ficaram como estavam. Nada foi
renumerado: os bits estão em saves antigos, e renomear é grátis enquanto
renumerar não é.

**4. Só se um dia faltar espaço** — reciclar as faixas contíguas do anexo E
(230 flags em 21 faixas, a maior com 57 slots seguidos em `0x15C–0x194`).
Regra: reciclar **muda o significado de um bit que saves antigos já têm
setado**. Uma flag de Hoenn que o jogador nunca pôde setar é segura; uma
"nunca referenciada" que já foi usada em versão anterior do hack, não.

**5. Não fazer** — mexer em `FLAGS_COUNT` (seção 3), reusar `FLAG_UNUSED_1xx`
(8.1), tocar em `FLAG_GARBAGEFLAG` (8.2).

---

## Anexo A — 141 flags só em mapas fora da ROM

```
0x011  FLAG_TEMP_HIDE_MIRAGE_ISLAND_BERRY_TREE          Route130
0x01D  FLAG_TEMP_1D                                     Route130, ShoalCave_LowTideIceRoom_Suicune +1
0x01F  FLAG_TEMP_1F                                     Route130, ShoalCave_LowTideIceRoom_Suicune +1
0x024  FLAG_SYS_NO_CATCHING                             MagmaHideout_3F_1R_Entei, NewMauville_Inside_Raikou +1
0x02B  FLAG_SYS_SET_BATTLE_BGM                          MagmaHideout_3F_1R_Entei, NewMauville_Inside_Raikou +1
0x02F  FLAG_DOME_FOSSIL_ALTERING_CAVE                   CeruleanCave2
0x045  FLAG_DEFEATED_ARTICUNO                           MeteorFalls_Articuno
0x046  FLAG_DEFEATED_ZAPDOS                             ScorchedSlab_Zapdos
0x047  FLAG_DEFEATED_MOLTRES                            VictoryRoad_Moltres2
0x04B  FLAG_DEFEATED_MEWTWO                             CeruleanCave3
0x04D  FLAG_UNLOCK_BIRDS                                MeteorFalls_Articuno, ScorchedSlab_Zapdos +1
0x059  FLAG_DECLINED_BIKE                               MauvilleCity_BikeShop
0x05C  FLAG_COLLECTED_ALL_SILVER_SYMBOLS                BattleFrontier_ScottsHouse
0x065  FLAG_MOSSDEEP_GYM_SWITCH_2                       MossdeepCity, MossdeepCity_Gym
0x066  FLAG_MOSSDEEP_GYM_SWITCH_3                       MossdeepCity, MossdeepCity_Gym
0x067  FLAG_MOSSDEEP_GYM_SWITCH_4                       MossdeepCity, MossdeepCity_Gym
0x068  FLAG_OLD_AMBER_ALTERING_CAVE                     CeruleanCave2
0x073  FLAG_RECEIVED_METEORITE                          MtChimney
0x076  FLAG_MET_HIDDEN_POWER_GIVER                      FortreeCity_House2
0x079  FLAG_RECEIVED_TM_BRICK_BREAK                     SootopolisCity_House1
0x07B  FLAG_RECEIVED_HM_DIVE                            MossdeepCity, MossdeepCity_StevensHouse
0x07D  FLAG_DEFEATED_RIVAL_ROUTE_104                    Route104
0x07F  FLAG_MET_PRETTY_PETAL_SHOP_OWNER                 Route104
0x087  FLAG_THANKED_FOR_PLAYING_WITH_WALLY              PetalburgCity_WallysHouse
0x08C  FLAG_RECEIVED_6_SODA_POP                         Route109_SeashoreHouse
0x08D  FLAG_DEFEATED_SEASHORE_HOUSE                     Route109_SeashoreHouse
0x08E  FLAG_DEVON_GOODS_STOLEN                          Route116, RustboroCity +2
0x08F  FLAG_RECOVERED_DEVON_GOODS                       Route116, RustboroCity +2
0x090  FLAG_RETURNED_DEVON_GOODS                        RustboroCity, RustboroCity_DevonCorp_1F
0x093  FLAG_MR_BRINEY_SAILING_INTRO                     Route104_MrBrineysHouse
0x094  FLAG_DOCK_REJECTED_DEVON_GOODS                   SlateportCity, SlateportCity_SternsShipyard_1F
0x098  FLAG_RECEIVED_SUPER_ROD                          MossdeepCity_House3
0x099  FLAG_RUSTBORO_NPC_TRADE_COMPLETED                RustboroCity_House1
0x09A  FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED              PacifidlogTown_House3
0x09B  FLAG_FORTREE_NPC_TRADE_COMPLETED                 FortreeCity_House1
0x09C  FLAG_BATTLE_FRONTIER_TRADE_DONE                  BattleFrontier_Lounge6
0x09F  FLAG_INTERACTED_WITH_DEVON_EMPLOYEE_GOODS_STOLEN RustboroCity
0x0A6  FLAG_RECEIVED_TM_BULK_UP                         DewfordTown_Gym
0x0A9  FLAG_RECEIVED_TM_FACADE                          PetalburgCity_Gym
0x0BF  FLAG_DEFEATED_GRUNT_SPACE_CENTER_1F              MossdeepCity_SpaceCenter_1F
0x0C0  FLAG_RECEIVED_SUN_STONE_MOSSDEEP                 MossdeepCity_SpaceCenter_1F
0x0CA  FLAG_RECEIVED_PINK_SCARF                         SlateportCity_PokemonFanClub
0x0CB  FLAG_RECEIVED_GREEN_SCARF                        SlateportCity_PokemonFanClub
0x0CC  FLAG_RECEIVED_YELLOW_SCARF                       SlateportCity_PokemonFanClub
0x0CE  FLAG_ENCOUNTERED_LATIAS_OR_LATIOS                SouthernIsland_Interior
0x0D2  FLAG_FAN_CLUB_STRENGTH_SHARED                    LilycoveCity_PokemonTrainerFanClub
0x0D3  FLAG_DEFEATED_RIVAL_RUSTBORO                     RustboroCity
0x0D5  FLAG_RECEIVED_PREMIER_BALL_RUSTBORO              RustboroCity_Flat2_2F
0x0DA  FLAG_MET_WAILMER_TRAINER                         LilycoveCity
0x0DB  FLAG_EVIL_LEADER_PLEASE_STOP                     MtChimney
0x0DE  FLAG_WINGULL_SENT_ON_ERRAND                      FortreeCity_House4
0x0DF  FLAG_RECEIVED_MENTAL_HERB                        FortreeCity_House4
0x0E3  FLAG_RECEIVED_GOOD_ROD                           Route118
0x0E5  FLAG_RECEIVED_TM_RETURN                          FallarborTown_CozmosHouse
0x0E8  FLAG_RECEIVED_TM_GIGA_DRAIN                      Route123
0x0EA  FLAG_RECEIVED_TM_REST                            LilycoveCity_House2
0x0EB  FLAG_RECEIVED_TM_ATTRACT                         VerdanturfTown_BattleTentLobby
0x0EC  FLAG_RECEIVED_GLASS_ORNAMENT                     LilycoveCity_LilycoveMuseum_2F
0x0ED  FLAG_RECEIVED_SILVER_SHIELD                      BattleFrontier_ScottsHouse
0x0EE  FLAG_RECEIVED_GOLD_SHIELD                        BattleFrontier_ScottsHouse
0x0EF  FLAG_USED_STORAGE_KEY                            AbandonedShip_Corridors_B1F
0x0F0  FLAG_USED_ROOM_1_KEY                             AbandonedShip_HiddenFloorCorridors
0x0F1  FLAG_USED_ROOM_2_KEY                             AbandonedShip_HiddenFloorCorridors
0x0F2  FLAG_USED_ROOM_4_KEY                             AbandonedShip_HiddenFloorCorridors
0x0F3  FLAG_USED_ROOM_6_KEY                             AbandonedShip_HiddenFloorCorridors
0x0F6  FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104             Route104
0x0F8  FLAG_RECEIVED_SPELON_BERRY                       Route123_BerryMastersHouse
0x0F9  FLAG_RECEIVED_PAMTRE_BERRY                       Route123_BerryMastersHouse
0x0FA  FLAG_RECEIVED_WATMEL_BERRY                       Route123_BerryMastersHouse
0x0FB  FLAG_RECEIVED_DURIN_BERRY                        Route123_BerryMastersHouse
0x0FC  FLAG_RECEIVED_BELUE_BERRY                        Route123_BerryMastersHouse
0x101  FLAG_RECEIVED_OLD_ROD                            DewfordTown
0x102  FLAG_RECEIVED_COIN_CASE                          MauvilleCity_House2
0x103  FLAG_RETURNED_RED_OR_BLUE_ORB                    MtPyre_Summit
0x105  FLAG_RECEIVED_TM_DIG                             Route114_FossilManiacsHouse
0x106  FLAG_RECEIVED_TM_BULLET_SEED                     Route104
0x107  FLAG_ENTERED_ELITE_FOUR                          EverGrandeCity_PokemonLeague_1F
0x108  FLAG_RECEIVED_TM_HIDDEN_POWER                    FortreeCity_House2
0x10F  FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE               SlateportCity_Harbor
0x113  FLAG_RECEIVED_QUICK_CLAW                         RustboroCity_PokemonSchool
0x114  FLAG_RECEIVED_KINGS_ROCK                         MossdeepCity
0x115  FLAG_RECEIVED_MACHO_BRACE                        Route111_WinstrateFamilysHouse
0x116  FLAG_RECEIVED_SOOTHE_BELL                        SlateportCity_PokemonFanClub
0x11A  FLAG_RECEIVED_CLEANSE_TAG                        MtPyre_1F
0x11E  FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE              LilycoveCity
0x120  FLAG_MET_RIVAL_RUSTBORO                          Route104, RustboroCity
0x126  FLAG_EXCHANGED_SCANNER                           AbandonedShip_CaptainsOffice, SlateportCity_Harbor
0x129  FLAG_RECEIVED_MIRACLE_SEED                       PetalburgWoods
0x12A  FLAG_RECEIVED_BELDUM                             MossdeepCity_StevensHouse
0x12B  FLAG_RECEIVED_FANCLUB_TM_THIS_WEEK               PacifidlogTown_House2
0x12C  FLAG_MET_FANCLUB_YOUNGER_BROTHER                 PacifidlogTown_House2
0x12D  FLAG_RIVAL_LEFT_FOR_ROUTE103                     LittlerootTown
0x12E  FLAG_OMIT_DIVE_FROM_STEVEN_LETTER                MossdeepCity_StevensHouse
0x136  FLAG_MET_SCOTT_RUSTBORO                          RustboroCity_PokemonSchool
0x139  FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS                JaggedPass
0x151  FLAG_RECEIVED_POWDER_JAR                         SlateportCity
0x153  FLAG_MET_BATTLE_FRONTIER_BREEDER                 BattleFrontier_Lounge1
0x156  FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN              SlateportCity_PokemonFanClub
0x1BB  FLAG_DEFEATED_REGIROCK                           DesertRuins
0x1BD  FLAG_DEFEATED_REGISTEEL                          AncientTomb
0x1C0  FLAG_DEFEATED_RAYQUAZA                           SkyPillar_Top
0x1C1  FLAG_DEFEATED_VOLTORB_1_NEW_MAUVILLE             NewMauville_Inside
0x1C2  FLAG_DEFEATED_VOLTORB_2_NEW_MAUVILLE             NewMauville_Inside
0x1C3  FLAG_DEFEATED_VOLTORB_3_NEW_MAUVILLE             NewMauville_Inside
0x1C4  FLAG_DEFEATED_ELECTRODE_1_AQUA_HIDEOUT           AquaHideout_B1F
0x1C5  FLAG_DEFEATED_ELECTRODE_2_AQUA_HIDEOUT           AquaHideout_B1F
0x1C8  FLAG_DEFEATED_LATIAS_OR_LATIOS                   SouthernIsland_Interior
0x1C9  FLAG_CAUGHT_LATIAS_OR_LATIOS                     SouthernIsland_Interior
0x1CB  FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE       RustboroCity_PokemonSchool
0x1CC  FLAG_MET_SCOTT_IN_VERDANTURF                     VerdanturfTown_BattleTentLobby
0x1CD  FLAG_MET_SCOTT_IN_FALLARBOR                      FallarborTown_BattleTentLobby
0x1CF  FLAG_MET_SCOTT_IN_EVERGRANDE                     EverGrandeCity_PokemonCenter_1F, EverGrandeCity_SidneysRoom
0x1D1  FLAG_SCOTT_GIVES_BATTLE_POINTS                   BattleFrontier_ScottsHouse
0x1D2  FLAG_COLLECTED_ALL_GOLD_SYMBOLS                  BattleFrontier_ScottsHouse
0x29A  FLAG_VISITED_BATTLE_FRONTIER                     BattleFrontier_ReceptionGate
0x2CD  FLAG_HIDE_SAFARI_ZONE_SOUTH_CONSTRUCTION_WORKERS SafariZone_South
0x2CF  FLAG_HIDE_ROUTE_104_RIVAL                        Route104, Route104_MrBrineysHouse
0x2D4  FLAG_HIDE_PETALBURG_WOODS_DEVON_EMPLOYEE         PetalburgWoods
0x2D5  FLAG_HIDE_PETALBURG_WOODS_AQUA_GRUNT             PetalburgWoods
0x2D6  FLAG_HIDE_PETALBURG_CITY_WALLY                   PetalburgCity, PetalburgCity_Gym
0x2D7  FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_INVISIBLE_NINJA_BOY MossdeepCity_StevensHouse
0x2FC  FLAG_HIDE_BIRTH_ISLAND_DEOXYS_TRIANGLE           BirthIsland_Exterior
0x465  FLAG_DEFEATED_ENTEI                              MagmaHideout_3F_1R_Entei
0x466  FLAG_DEFEATED_RAIKOU                             NewMauville_Inside_Raikou
0x467  FLAG_DEFEATED_SUICUNE                            ShoalCave_LowTideIceRoom_Suicune
0x48A  FLAG_ITEM_ARTISAN_CAVE_B1F_HP_UP                 ArtisanCave_B1F
0x48B  FLAG_ITEM_ARTISAN_CAVE_1F_CARBOS                 ArtisanCave_1F
0x48C  FLAG_ITEM_MAGMA_HIDEOUT_2F_2R_MAX_ELIXIR         MagmaHideout_2F_2R
0x48D  FLAG_ITEM_MAGMA_HIDEOUT_2F_2R_FULL_RESTORE       MagmaHideout_2F_2R
0x48E  FLAG_ITEM_MAGMA_HIDEOUT_3F_1R_NUGGET             MagmaHideout_3F_1R
0x48F  FLAG_ITEM_MAGMA_HIDEOUT_3F_2R_PP_MAX             MagmaHideout_3F_2R
0x490  FLAG_ITEM_MAGMA_HIDEOUT_4F_MAX_REVIVE            MagmaHideout_4F
0x491  FLAG_ITEM_SAFARI_ZONE_NORTH_EAST_NUGGET          SafariZone_Northeast
0x492  FLAG_ITEM_SAFARI_ZONE_SOUTH_EAST_BIG_PEARL       SafariZone_Southeast
0x495  FLAG_ENTEI_BATTLE_1                              MagmaHideout_3F_1R_Entei
0x496  FLAG_ENTEI_BATTLE_2                              MagmaHideout_3F_1R_Entei
0x497  FLAG_ENTEI_BATTLE_3                              MagmaHideout_3F_1R_Entei
0x49A  FLAG_RAIKOU_BATTLE_1                             NewMauville_Inside_Raikou
0x49C  FLAG_RAIKOU_BATTLE_2                             NewMauville_Inside_Raikou
0x49D  FLAG_SUICUNE_BATTLE_1                            ShoalCave_LowTideIceRoom_Suicune
0x49E  FLAG_SUICUNE_BATTLE_2                            ShoalCave_LowTideIceRoom_Suicune
```

## Anexo B — 151 flags nomeadas e nunca referenciadas

```
0x00B  FLAG_TEMP_B                                 
0x00C  FLAG_TEMP_C                                 
0x00D  FLAG_TEMP_D                                 
0x00F  FLAG_TEMP_F                                 
0x020  FLAG_SYS_NO_COLLISION                       
0x022  FLAG_SYS_NO_TRAINER_SEE                     
0x023  FLAG_SYS_NO_BAG_USE                         
0x025  FLAG_SYS_PC_FROM_DEBUG_MENU                 
0x027  FLAG_SYS_NO_BATTLE_DMG                      
0x02C  FLAG_WONDERTRADE_FIRSTIME                   
0x03B  FLAG_DEFEATED_REGIELEKI                     
0x03D  FLAG_HIDE_REGIDRAGO                         
0x03E  FLAG_SAPPHIRE_KECLEON                       
0x03F  FLAG_SYS_BRAILLE_REGIDRAGO_COMPLETED        
0x040  FLAG_DEFEATED_REGIDRAGO                     
0x041  FLAG_DEFEATED_DUSKNOIR                      
0x042  FLAG_SYS_BRAILLE_REGIGIGAS_COMPLETED        
0x043  FLAG_DEFEATED_REGIGIGAS                     
0x04F  FLAG_RASH_MINT_METEOR_FALLS                 
0x050  FLAG_GARBAGEFLAG_STILL                      
0x054  FLAG_LIMIT_TO_50                            
0x055  FLAG_UNLOCK_DOGS                            
0x05E  FLAG_GARBAGEFLAG2                           
0x0AB  FLAG_RECEIVED_TM_CALM_MIND                  
0x0DC  FLAG_NEVER_SET_0x0DC                        
0x0E7  FLAG_RECEIVED_TM_ROAR                       
0x0FE  FLAG_GARBAGEFLAG4                           
0x10A  FLAG_RECEIVED_LAVARIDGE_EGG                 
0x11B  FLAG_HIDE_BLAINE                            
0x1B1  FLAG_MOVE_TUTOR_TAUGHT_SWAGGER              
0x1B2  FLAG_MOVE_TUTOR_TAUGHT_ROLLOUT              
0x1B3  FLAG_MOVE_TUTOR_TAUGHT_FURY_CUTTER          
0x1B4  FLAG_MOVE_TUTOR_TAUGHT_MIMIC                
0x1B5  FLAG_MOVE_TUTOR_TAUGHT_METRONOME            
0x1B6  FLAG_MOVE_TUTOR_TAUGHT_SLEEP_TALK           
0x1B7  FLAG_MOVE_TUTOR_TAUGHT_SUBSTITUTE           
0x1B8  FLAG_MOVE_TUTOR_TAUGHT_DYNAMICPUNCH         
0x1B9  FLAG_MOVE_TUTOR_TAUGHT_DOUBLE_EDGE          
0x1BA  FLAG_MOVE_TUTOR_TAUGHT_EXPLOSION            
0x1DA  FLAG_WT_ENABLED                             
0x1DE  FLAG_INFINITE_STUFF                         
0x1DF  FLAG_INFINITE_STUFF_GIRL                    
0x217  FLAG_HIDDEN_ITEM_SS_TIDAL_LOWER_DECK_LEFTOVERS
0x218  FLAG_HIDDEN_ITEM_UNDERWATER_124_CALCIUM     
0x22F  FLAG_HIDDEN_ITEM_PETALBURG_WOODS_TINY_MUSHROOM_1
0x230  FLAG_HIDDEN_ITEM_PETALBURG_WOODS_TINY_MUSHROOM_2
0x231  FLAG_HIDDEN_ITEM_PETALBURG_WOODS_POKE_BALL  
0x232  FLAG_HIDDEN_ITEM_ROUTE_104_POKE_BALL        
0x233  FLAG_HIDDEN_ITEM_ROUTE_106_POKE_BALL        
0x234  FLAG_HIDDEN_ITEM_ROUTE_109_ETHER            
0x235  FLAG_HIDDEN_ITEM_ROUTE_110_POKE_BALL        
0x236  FLAG_HIDDEN_ITEM_ROUTE_118_HEART_SCALE      
0x23A  FLAG_HIDDEN_ITEM_ROUTE_120_ZINC             
0x23B  FLAG_HIDDEN_ITEM_ROUTE_120_RARE_CANDY_1     
0x23C  FLAG_HIDDEN_ITEM_ROUTE_117_REPEL            
0x23D  FLAG_HIDDEN_ITEM_ROUTE_121_FULL_HEAL        
0x23E  FLAG_HIDDEN_ITEM_ROUTE_123_HYPER_POTION     
0x23F  FLAG_HIDDEN_ITEM_LILYCOVE_CITY_POKE_BALL    
0x240  FLAG_HIDDEN_ITEM_JAGGED_PASS_GREAT_BALL     
0x241  FLAG_HIDDEN_ITEM_JAGGED_PASS_FULL_HEAL      
0x242  FLAG_HIDDEN_ITEM_MT_PYRE_EXTERIOR_MAX_ETHER 
0x243  FLAG_HIDDEN_ITEM_MT_PYRE_SUMMIT_ZINC        
0x244  FLAG_HIDDEN_ITEM_MT_PYRE_SUMMIT_RARE_CANDY  
0x245  FLAG_HIDDEN_ITEM_VICTORY_ROAD_1F_ULTRA_BALL 
0x246  FLAG_HIDDEN_ITEM_VICTORY_ROAD_B2F_ELIXIR    
0x247  FLAG_HIDDEN_ITEM_VICTORY_ROAD_B2F_MAX_REPEL 
0x248  FLAG_HIDDEN_ITEM_ROUTE_120_REVIVE           
0x249  FLAG_HIDDEN_ITEM_ROUTE_104_ANTIDOTE         
0x24A  FLAG_HIDDEN_ITEM_ROUTE_108_RARE_CANDY       
0x24B  FLAG_HIDDEN_ITEM_ROUTE_119_MAX_ETHER        
0x24C  FLAG_HIDDEN_ITEM_ROUTE_104_HEART_SCALE      
0x24D  FLAG_HIDDEN_ITEM_ROUTE_105_HEART_SCALE      
0x24E  FLAG_HIDDEN_ITEM_ROUTE_109_HEART_SCALE_2    
0x24F  FLAG_HIDDEN_ITEM_ROUTE_109_HEART_SCALE_3    
0x250  FLAG_HIDDEN_ITEM_ROUTE_128_HEART_SCALE_1    
0x251  FLAG_HIDDEN_ITEM_ROUTE_128_HEART_SCALE_2    
0x252  FLAG_HIDDEN_ITEM_ROUTE_128_HEART_SCALE_3    
0x253  FLAG_HIDDEN_ITEM_PETALBURG_CITY_RARE_CANDY  
0x255  FLAG_HIDDEN_ITEM_ROUTE_115_HEART_SCALE      
0x256  FLAG_HIDDEN_ITEM_ROUTE_113_NUGGET           
0x257  FLAG_HIDDEN_ITEM_ROUTE_123_PP_UP            
0x258  FLAG_HIDDEN_ITEM_ROUTE_121_MAX_REVIVE       
0x259  FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_CALCIUM   
0x25A  FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_ZINC      
0x25B  FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_PROTEIN   
0x25C  FLAG_HIDDEN_ITEM_ARTISAN_CAVE_B1F_IRON      
0x25D  FLAG_HIDDEN_ITEM_SAFARI_ZONE_SOUTH_EAST_FULL_RESTORE
0x25E  FLAG_HIDDEN_ITEM_SAFARI_ZONE_NORTH_EAST_RARE_CANDY
0x25F  FLAG_HIDDEN_ITEM_SAFARI_ZONE_NORTH_EAST_ZINC
0x260  FLAG_HIDDEN_ITEM_SAFARI_ZONE_SOUTH_EAST_PP_UP
0x261  FLAG_HIDDEN_ITEM_NAVEL_ROCK_TOP_SACRED_ASH  
0x262  FLAG_HIDDEN_ITEM_ROUTE_123_RARE_CANDY       
0x263  FLAG_HIDDEN_ITEM_ROUTE_105_BIG_PEARL        
0x264  FLAG_MINTS_CLERK                            
0x265  FLAG_EXTRA_LEGENDARIES                      
0x266  FLAG_OLD_MAN_AND_DUSCLOPS                   
0x267  FLAG_CERULEAN_CAVE_LUCKY_EGG                
0x2B5  FLAG_HIDE_VICITNI                           
0x2BC  FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG      
0x2D0  FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE  
0x2D1  FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH  
0x2D3  FLAG_HIDE_ROUTE_103_RIVAL                   
0x2EC  FLAG_GOLDENROD_CITY_AIDE_VISITED            
0x2F5  FLAG_FIXED_TRAIN                            
0x2FE  FLAG_HIDE_BUG_CONTEST_BUGS                  
0x363  FLAG_HIDE_LAKEOFRAGE_POLICE                 
0x381  FLAG_HIDE_ILEX_FOREST_FARFETCHD             
0x387  FLAG_UNLOCKED_KURT_BALLS                    
0x3D2  FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_1        
0x3D3  FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_2        
0x3D4  FLAG_HIDE_ROCKETHIDEOUT2_ELECTRODE_3        
0x3DC  FLAG_HIDE_WHIRLISLANDS_GUARD                
0x3E8  FLAG_ITEM_GARBAGEFLAG                       
0x3F9  FLAG_ITEM_MTMORTAR3_RARE_CANDY              
0x435  FLAG_ITEM_ROCKETHIDEOUT3_HYPER_POTION       
0x45D  FLAG_ITEM_ROCKTUNNEL1_TM_FACADE             
0x463  FLAG_ITEM_CELADON_LEFTOVERS                 
0x468  FLAG_DEFEATEDCELEBI                         
0x46A  FLAG_ITEM_ROUTE13_CALCIUM                   
0x478  FLAG_ITEM_MTMOON_MOONSTONE                  
0x479  FLAG_EVEN_FASTER_JOY                        
0x489  FLAG_ITEM_ROUTE20_SHELL_BELL                
0x493  FLAG_JIRACHI                                
0x494  FLAG_ROBERTO1                               
0x498  FLAG_INCREASE_DIFFICULTY                    
0x49B  FLAG_LANDMARK_DRACO_CHAMBER                 
0x49F  FLAG_NO_SLOW_STAIR_MOVEMENT                 
0x4DE  FLAG_ITEM_BELLCHIME_BIG_MUSHROOM            
0x4F9  FLAG_NO_SHINY                               
0x924  FLAG_SNOWTOP_CALCIUM_EX                     
0x934  FLAG_POSTGAME_CAP2                          
0x935  FLAG_POSTGAME_CAP3                          
0x936  FLAG_POSTGAME_CAP4                          
0x963  FLAG_HIDE_M_WAREHOUSE                       
0x9C3  FLAG_SYS_CAVE_SHIP                          
0x9C4  FLAG_SYS_CAVE_WONDER                        
0x9C5  FLAG_SYS_CAVE_BATTLE                        
0x9D5  FLAG_LANDMARK_SOUTHERN_ISLAND               
0x9FF  FLAG_MAP_SCRIPT_CHECKED_DEOXYS              
0xA05  FLAG_ARRIVED_AT_MARINE_CAVE_EMERGE_SPOT     
0xA06  FLAG_ARRIVED_AT_TERRA_CAVE_ENTRANCE         
0xA08  FLAG_ENTERED_MIRAGE_TOWER                   
0xA0D  FLAG_ARRIVED_AT_NAVEL_ROCK                  
0xA20  FLAG_GOLDEN_COLOSSEUM                       
0xA21  FLAG_NEVER_TURNED_OFF_HARD                  
0x1500  FLAG_0x1500                                 
0x1513  FLAG_DAILY_ROUTE_114_RECEIVED_BERRY         
0x1514  FLAG_DAILY_ROUTE_111_RECEIVED_BERRY         
0x1516  FLAG_DAILY_ROUTE_120_RECEIVED_BERRY         
0x1517  FLAG_DAILY_LILYCOVE_RECEIVED_BERRY          
0x151A  FLAG_DAILY_SOOTOPOLIS_RECEIVED_BERRY
```

## Anexo C — 42 flags já marcadas como não usadas

```
0x165  FLAG_UNUSED_165                             
0x167  FLAG_UNUSED_167                             
0x169  FLAG_UNUSED_169                             
0x16A  FLAG_UNUSED_16A                             
0x16B  FLAG_UNUSED_16B                             
0x16C  FLAG_UNUSED_16C                             
0x176  FLAG_UNUSED_176                             
0x179  FLAG_UNUSED_179                             
0x17B  FLAG_UNUSED_17B                             
0x17C  FLAG_UNUSED_17C                             
0x181  FLAG_UNUSED_181                             
0x184  FLAG_UNUSED_184                             
0x185  FLAG_UNUSED_185                             
0x186  FLAG_UNUSED_186                             
0x187  FLAG_UNUSED_187                             
0x188  FLAG_UNUSED_188                             
0x35C  FLAG_UNUSED_35C                             
0x3EC  FLAG_ITEM_UNUSED0EC                         
0x4FA  FLAG_UNUSED_4FA                             
0x1537  FLAG_UNUSED_0x94F                           
0x1538  FLAG_UNUSED_0x950                           
0x1539  FLAG_UNUSED_0x951                           
0x153A  FLAG_UNUSED_0x952                           
0x153B  FLAG_UNUSED_0x953                           
0x153C  FLAG_UNUSED_0x954                           
0x153D  FLAG_UNUSED_0x955                           
0x153E  FLAG_UNUSED_0x956                           
0x153F  FLAG_UNUSED_0x957                           
0x1540  FLAG_UNUSED_0x958                           
0x1541  FLAG_UNUSED_0x959                           
0x1542  FLAG_UNUSED_0x95A                           
0x1543  FLAG_UNUSED_0x95B                           
0x1544  FLAG_UNUSED_0x95C                           
0x1545  FLAG_UNUSED_0x95D                           
0x1546  FLAG_UNUSED_0x95E                           
0x1547  FLAG_UNUSED_0x95F                           
0x4003  FLAG_SPECIAL_FLAG_UNUSED_0x4003             
0x5003  TESTING_FLAG_UNUSED_3                       
0x5004  TESTING_FLAG_UNUSED_4                       
0x5005  TESTING_FLAG_UNUSED_5                       
0x5006  TESTING_FLAG_UNUSED_6                       
0x5007  TESTING_FLAG_UNUSED_7
```

## Anexo D — 39 flags escritas e nunca lidas

```
0x057  FLAG_MET_RIVAL_MOM                            LittlerootTown_BrendansHouse_1F
0x0A5  FLAG_RECEIVED_TM_ROCK_TOMB                    RustboroCity_Gym
0x0A7  FLAG_RECEIVED_TM_SHOCK_WAVE                   MauvilleCity_Gym
0x0AC  FLAG_RECEIVED_TM_WATER_PULSE                  SootopolisCity_Gym_1F
0x0DD  FLAG_RECEIVED_GO_GOGGLES                      LavaridgeTown
0x0FF  FLAG_LATIOS_OR_LATIAS_ROAMING               
0x10E  FLAG_CONTEST_SKETCH_CREATED                 
0x111  FLAG_POKERUS_EXPLAINED                      
0x123  FLAG_RECEIVED_SS_TICKET                     
0x28B  FLAG_HIDE_ROUTE22_JANINE                      PokemonLeague_HallOfFame
0x29C  FLAG_ALLOW_SOUTH_JOHTO_PASS                   NewBarkTown_Lab
0x29F  FLAG_LEVEL_SCALING_ON                         Route36
0x2B3  FLAG_HIDE_MANAPHY                             PokemonLeague_HallOfFame
0x2B6  FLAG_HIDE_CHI_YU                              PokemonLeague_HallOfFame
0x2B8  FLAG_HIDE_DIANCIE                             PokemonLeague_HallOfFame
0x2EA  FLAG_HIDE_ILEX_FOREST_KURT                    AzaleaTown
0x2EB  FLAG_MOVE_TUTOR_TAUGHT_HEADBUTT               AzaleaTown
0x31A  FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD          VermilionCity
0x31B  FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD         PalletTown_Lab
0x350  FLAG_HIDE_OLIVINE_PORT_OAK                    NewBarkTown_Lab
0x372  FLAG_GET_HEADBUTT                             AzaleaTown_Gym
0x377  FLAG_HIDE_MRPOKEMON                         
0x3B2  FLAG_CAUGHT_ENTEI                             EcruteakCity
0x3B3  FLAG_CAUGHT_RAIKOU                            EcruteakCity
0x3B4  FLAG_HIDE_ROUTE39_SHADOW                      EcruteakCity
0x3D7  FLAG_HIDE_TOHJO_GIOVANNI                    
0x499  FLAG_ROCKETHIDEOUT2_BATTLE                    RocketHideout_B2F
0x4A6  FLAG_EXP_SHARE                                NewBarkTown_Lab
0x933  FLAG_POSTGAME_CAP1                            CeruleanCave_B2F
0x943  FLAG_CAMERON_PHOTO2                           RuinsOfAlph_Outside
0x944  FLAG_CAMERON_PHOTO3                           RuinsOfAlph_Outside
0x945  FLAG_CAMERON_PHOTO4                           RuinsOfAlph_Outside
0x9AB  FLAG_VISITED_CERULEAN_CITY                    CeruleanCity
0xA04  FLAG_ARRIVED_ON_FARAWAY_ISLAND                FarawayIsland_Entrance
0xA15  FLAG_BADGE13_GET                              SaffronCity_Gym
0xA16  FLAG_BADGE14_GET                              FuchsiaCity_Gym
0xA17  FLAG_BADGE15_GET                            
0xA22  FLAG_TRAINER_LEVELSCALING                     Route36
0xA23  FLAG_WILD_LEVELSCALING                        Route36
```

## Anexo E — faixas contíguas recicláveis

Só faixas de 4 slots ou mais, juntando "nunca referenciada" e "só em mapa fora
da ROM". Leia a seção 10, item 4, antes de usar.

```
faixas contiguas reciclaveis (>=4 slots): 21 faixas, 230 flags
0x15C-0x194   57  FLAG_REGISTERED_ROSE ... FLAG_REGISTERED_JUAN
0x23A-0x253   26  FLAG_HIDDEN_ITEM_ROUTE_120_ZINC ... FLAG_HIDDEN_ITEM_PETALBURG_CITY_RARE_CANDY
0x255-0x267   19  FLAG_HIDDEN_ITEM_ROUTE_115_HEART_SCALE ... FLAG_CERULEAN_CAVE_LUCKY_EGG
0x1537-0x1547   17  FLAG_UNUSED_0x94F ... FLAG_UNUSED_0x95F
0x489-0x498   16  FLAG_ITEM_ROUTE20_SHELL_BELL ... FLAG_INCREASE_DIFFICULTY
0x1B1-0x1BB   11  FLAG_MOVE_TUTOR_TAUGHT_SWAGGER ... FLAG_DEFEATED_REGIROCK
0x0EA-0x0F3   10  FLAG_RECEIVED_TM_REST ... FLAG_USED_ROOM_6_KEY
0x22F-0x236    8  FLAG_HIDDEN_ITEM_PETALBURG_WOODS_TINY_MUSHROOM_1 ... FLAG_HIDDEN_ITEM_ROUTE_118_HEART_SCALE
0x03D-0x043    7  FLAG_HIDE_REGIDRAGO ... FLAG_DEFEATED_REGIGIGAS
0x129-0x12E    6  FLAG_RECEIVED_MIRACLE_SEED ... FLAG_OMIT_DIVE_FROM_STEVEN_LETTER
0x1C0-0x1C5    6  FLAG_DEFEATED_RAYQUAZA ... FLAG_DEFEATED_ELECTRODE_2_AQUA_HIDEOUT
0x49A-0x49F    6  FLAG_RAIKOU_BATTLE_1 ... FLAG_NO_SLOW_STAIR_MOVEMENT
0x08C-0x090    5  FLAG_RECEIVED_6_SODA_POP ... FLAG_RETURNED_DEVON_GOODS
0x098-0x09C    5  FLAG_RECEIVED_SUPER_ROD ... FLAG_BATTLE_FRONTIER_TRADE_DONE
0x0F8-0x0FC    5  FLAG_RECEIVED_SPELON_BERRY ... FLAG_RECEIVED_BELUE_BERRY
0x2D3-0x2D7    5  FLAG_HIDE_ROUTE_103_RIVAL ... FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_INVISIBLE_NINJA_BOY
0x5003-0x5007    5  TESTING_FLAG_UNUSED_3 ... TESTING_FLAG_UNUSED_7
0x065-0x068    4  FLAG_MOSSDEEP_GYM_SWITCH_2 ... FLAG_OLD_AMBER_ALTERING_CAVE
0x105-0x108    4  FLAG_RECEIVED_TM_DIG ... FLAG_RECEIVED_TM_HIDDEN_POWER
0x113-0x116    4  FLAG_RECEIVED_QUICK_CLAW ... FLAG_RECEIVED_SOOTHE_BELL
0x465-0x468    4  FLAG_DEFEATED_ENTEI ... FLAG_DEFEATEDCELEBI
```

---

## Como este documento foi produzido

```bash
python3 dev_scripts/flag_audit.py --csv
```

O script resolve todos os `#define` de `flags.h` (inclusive os que dependem de
`opponents.h`/`rematches.h`), varre todo arquivo versionado, classifica cada
ocorrência em leitura / escrita / outro — tratando `setflag`, `clearflag`,
`goto_if_*`, `FlagGet`/`FlagSet` e as macros `*legendaryencounter`, que passam
a flag em `VAR_0x8007` — e cruza com `rom_excluded_groups` para separar o que
só existe em mapa de Hoenn.

Limites conhecidos: uso por aritmética (`FLAG_X + i`) não é detectado
automaticamente — os casos conhecidos são `TRAINER_FLAGS_START + id`,
`TRAINER_REGISTERED_FLAGS_START + i`, `FLAG_DECORATION_1 + i`,
`FLAG_SYS_TOWER_SILVER/GOLD + facility*2`, `FLAG_HIDE_UNION_ROOM_PLAYER_1 + idx`
e `FLAG_BADGE01_GET + i` (só as oito de Johto), e todos estão tratados no texto.
