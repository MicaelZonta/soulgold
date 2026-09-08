# Como montar uma batalha com um NPC no SoulGold

Guia derivado do **Youngster Joey** (`Route30`), o treinador mais simples do jogo:
1 Rattata nível 5, batalha por visão, texto antes/depois.

Complementa [`adicionar-npc.md`](adicionar-npc.md) — aquele ensina a **desenhar** o NPC
(sprite, paleta, graphics info); este ensina a fazer o NPC **batalhar**.
Se o seu treinador usa um sprite que já existe (`OBJ_EVENT_GFX_YOUNGSTER`, etc.),
só este guia basta.

---

## Checklist rápido

| # | Arquivo | O que fazer |
|---|---------|-------------|
| 1 | `include/constants/opponents.h` | Um `TRAINER_<NOME>` com ID livre (reaproveite um `TRAINER_UNUSED_*`) |
| 2 | `src/data/trainers.party` | Bloco `=== TRAINER_<NOME> ===` com classe, sprite, música, IA e o time |
| 3 | `data/maps/<Mapa>/map.json` | Object event com `trainer_type` + raio de visão + `script` |
| 4 | `data/maps/<Mapa>/scripts.pory` (ou `.inc`) | `trainerbattle_single` + `msgbox` pós-batalha |
| 5 | mesmo arquivo de script | Os 3 textos: **Seen**, **Beaten**, **After** |

> Nada de flag nova: **a flag de "derrotado" é automática** (`TRAINER_FLAGS_START + ID`) —
> mas por isso mesmo o ID escolhido tem que estar numa faixa cuja flag ainda esteja livre.
> Ver [passo 1](#1-o-id-em-includeconstantsopponentsh): use `280`, `951-963` ou `968-1055`.

---

## O exemplo completo (Joey)

Tudo o que existe do Joey, nos 4 lugares:

```c
// include/constants/opponents.h:328
#define TRAINER_JOEY                        322
```

```
# src/data/trainers.party:1095
=== TRAINER_JOEY ===
Name: Joey
Class: Youngster
Pic: Youngster
Gender: Male
Music: Hg Boy 1
Double Battle: No
AI: Basic Trainer

Rattata
Level: 5
IVs: 0 HP / 0 Atk / 0 Def / 0 SpA / 0 SpD / 0 Spe
```

```json
// data/maps/Route30/map.json — object_events[1]
{
  "graphics_id": "OBJ_EVENT_GFX_YOUNGSTER",
  "x": 20, "y": 28, "elevation": 0,
  "movement_type": "MOVEMENT_TYPE_FACE_RIGHT",
  "movement_range_x": 5, "movement_range_y": 5,
  "trainer_type": "TRAINER_TYPE_NORMAL",
  "trainer_sight_or_berry_tree_id": "5",
  "script": "Route30_EventScript_Youngster_Joey",
  "flag": "FLAG_HIDE_ROUTE_30_NPCS"
}
```

```
Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_Text_YoungsterJoey1Seen:
	.string "I just lost, so I'm trying to\n"
	.string "find more Pokémon.\p"
	.string "Wait! You look weak! Come on,\n"
	.string "let's battle!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "Ack! I lost again!\n"
	.string "Doggone it!$"

Route30_Text_YoungsterJoey1After:
	.string "Do I have to have more Pokémon\n"
	.string "in order to battle better?\p"
	.string "No! I'm sticking with this one\n"
	.string "no matter what!$"
```

---

## Passo a passo

### 1. O ID em `include/constants/opponents.h`

Você **não cria flag nenhuma** para um treinador: a flag de "derrotado" é derivada do ID
(`TRAINER_FLAGS_START (0x500) + ID`, `include/constants/flags.h:1346` e
`src/battle_setup.c:1411`). Em compensação, **escolher o ID é escolher uma flag** — e
nem todo `TRAINER_UNUSED_*` tem a flag livre neste projeto.

#### IDs realmente livres

| Faixa de ID | Flags | Status |
|-------------|-------|--------|
| `280`, `951-963`, `968-1055` | `0x500+ID`, ainda intocadas | ✅ **use estes** (102 slots) |
| `1056-1163` | `0x920-0x98B` foram **reaproveitadas** como flags normais | ❌ **não use** |
| `1164` (`TRAINER_UNUSED_300`) | fora do range | ❌ não use |

O bloco `RECLAIMED_TRAINER_FLAGS_START/END` (`include/constants/flags.h:1573`) diz isso
explicitamente — `// unused trainer IDs 1056-1163` — e as flags dessa faixa hoje são
`FLAG_SNOWTOP_*`, `FLAG_VAJRAPYRAMID*`, `FLAG_LATITEMPLE_*`, etc. Um treinador criado
nessa faixa **compartilha a flag com um evento de mapa**: vencer o treinador dispara o
evento, e o evento marca o treinador como já derrotado.

Para conferir se um ID candidato está limpo:

```bash
printf '0x%X\n' $((0x500 + 1042))          # ID -> flag
grep -n "0x920\|RECLAIMED" include/constants/flags.h   # a faixa proibida
```

#### Como adicionar

Renomeie um `TRAINER_UNUSED_*` **da faixa livre**, mantendo o número. Foi assim que os
quatro treinadores da Route29 entraram ([opponents.h:945](../include/constants/opponents.h#L945)):

```c
#define TRAINER_LUSAMINE                  964   // era TRAINER_UNUSED_100
#define TRAINER_LILLIE                    965   // era TRAINER_UNUSED_101
#define TRAINER_KUKUI                     966   // era TRAINER_UNUSED_102
#define TRAINER_GLADION                   967   // era TRAINER_UNUSED_103
```

- **Não** mexa em `TRAINERS_COUNT` / `MAX_TRAINERS_COUNT`: eles definem onde começam as
  `SYSTEM_FLAGS`, então mudar o valor **desloca todas as flags do jogo** e invalida saves.
- Nada de `#define FLAG_DERROTEI_MEU_NPC` — essa flag não existe como símbolo.

#### E se eu não quiser gastar um slot?

Não dá para ter `trainerbattle_*` sem flag — a flag é o que impede a batalha de repetir.
Mas dá para **um mesmo ID batalhar várias vezes, com times diferentes**: ver
[Reusar um treinador em várias batalhas](#reusar-um-treinador-em-várias-batalhas-1-slot-vários-times).

### 2. O time em `src/data/trainers.party`

Formato **Showdown/competitivo**, processado pelo `tools/trainerproc` que gera
`src/data/trainers.h` (**gitignored — nunca edite o `.h`**). O cabeçalho do próprio
`trainers.party` (linhas 1-85) é a referência canônica de todos os campos; o resumo:

**Do treinador** — obrigatórios `Name` e `Pic`; recomendados:

| Campo | Vira | Onde ver os valores |
|-------|------|---------------------|
| `Class:` | `TRAINER_CLASS_*` | `include/constants/trainers.h:~360+` |
| `Pic:` | `TRAINER_PIC_FRONT_*` | `include/constants/trainers.h:~20+` |
| `Music:` | `TRAINER_ENCOUNTER_MUSIC_*` | `include/constants/trainers.h:~430+` |
| `Gender:` | `Male` / `Female` | — |
| `Battle Type:` | `Singles` / `Doubles` | (`Double Battle: Yes` é o alias antigo) |
| `AI:` | `AI_FLAG_*` separadas por `/` | `include/constants/battle_ai.h` |
| `Items:` | até 4 itens de uso do treinador, separados por `/` | `constants/items.h` |
| `Mugshot:` | mugshot na transição: `Purple`/`Green`/`Pink`/`Blue`/`Yellow` | — |
| `Difficulty:` | `Normal` (padrão) ou `Hard` | ver abaixo |

A conversão é por nome com espaços: `Class: Bird Keeper` → `TRAINER_CLASS_BIRD_KEEPER`,
`Music: Hg Boy 1` → `TRAINER_ENCOUNTER_MUSIC_HG_BOY_1`. Também aceita a constante crua.

**Dos Pokémon** — só a espécie é obrigatória; a linha da espécie carrega apelido, gênero
e item: `Alfredo (Rattata) (M) @ Oran Berry`. Depois, um campo por linha:
`Level`, `Ability`, `IVs`, `EVs`, `Ball`, `Happiness`, `<Nature> Nature`, `Shiny`,
`Tera Type`, `Dynamax Level`, `Gigantamax`. Os golpes vêm **por último**, um `- Golpe`
por linha.

> ⚠️ Padrões: **sem `Level:` o mon vem nível 100**; sem `IVs:` vem com 31 em tudo.
> Por isso todo treinador de rota do SoulGold traz `Level:` e `IVs: 0 .../...`.

**Golpes omitidos = golpes automáticos.** Se você não escrever nenhum `- Golpe`, o jogo
monta o set na hora da batalha (últimos 4 golpes de level-up; em Hard, um set melhor
conforme o nível). Se escrever **qualquer** golpe, os 4 slots passam a ser exatamente os
escritos — use `- None` para deixar um slot vazio de propósito (é o que Falkner faz).

**Versão Hard:** repita o mesmo `=== TRAINER_X ===` num segundo bloco com
`Difficulty: Hard` e outro time (ver `TRAINER_FALKNER_1`, linhas 12783 e 12817). Sem esse
bloco, o modo Hard reaproveita o time Normal.

Um bloco vai do `=== TRAINER_X ===` até o próximo `===`. **Linha em branco obrigatória**
entre o cabeçalho do treinador e o primeiro mon, e entre um mon e o próximo.

### 3. O NPC no mapa

Em `data/maps/<Mapa>/map.json`, o object event:

| Campo | Para um treinador |
|-------|-------------------|
| `trainer_type` | `TRAINER_TYPE_NORMAL` (vê para frente), `TRAINER_TYPE_SEE_ALL_DIRECTIONS`, `TRAINER_TYPE_BURIED`, `TRAINER_TYPE_SENTRY`, ou `TRAINER_TYPE_NONE` (só batalha se você falar com ele) — `include/constants/trainer_types.h` |
| `trainer_sight_or_berry_tree_id` | **raio de visão em tiles** (Joey: `"5"`, Mikey e Don: `"2"`). Com `TRAINER_TYPE_NONE`, deixe `"0"` |
| `movement_type` | define para onde ele olha; a visão sai dessa direção |
| `script` | o `<Mapa>_EventScript_<Nome>` do passo 4 |
| `flag` | `"0"` = sempre visível; uma flag esconde o NPC quando setada |

O **localId** de um object event é o `índice no array + 1`. Só precisa dele para
`applymovement`/`turnobject`; declare no topo do script como o Route30 faz:

```
.set LOCALID_ROUTE_30_JOEY, 6
```

### 4. O script

Mapas com `scripts.pory` são a fonte da verdade — o `.inc` é **gerado** pelo build
(`Makefile:502`). Edite o `.pory`; se o mapa só tem `.inc`, edite o `.inc`.
No SoulGold vários `.pory` são um bloco `raw \`...\`` gigante com asm dentro (é o caso de
`Route29/scripts.pory`), então a sintaxe abaixo serve para os dois.

```
Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end
```

Como funciona: o `trainerbattle_single` **encerra o script** ao vencer a batalha; o
`msgbox` seguinte é o que roda quando você fala com o treinador **já derrotado**. Por isso
o padrão é sempre 3 textos (Seen / Beaten / After).

> ⚠️ **Não coloque `lock`/`faceplayer` antes do `trainerbattle`.** A engine já cuida da
> aproximação e do "!" quando o treinador te avista. Um `lock` antes trava a cena.

Macros disponíveis (`asm/macros/event.inc:733-805`):

| Macro | Uso |
|-------|-----|
| `trainerbattle_single trainer, seen, beaten [, event_script] [, music]` | o caso normal; com `event_script` a batalha continua num script (`TRAINER_BATTLE_CONTINUE_SCRIPT`) |
| `trainerbattle_double trainer, seen, beaten, not_enough_mons [, event_script]` | duplas — exige o texto de "só tem 1 Pokémon" |
| `trainerbattle_no_intro trainer, beaten` | batalha disparada por script (sem fala de avistamento) |
| `trainerbattle_rematch trainer, seen, beaten` | revanche |
| `trainerbattle_two_trainers a, beaten_a, b, beaten_b` | dois treinadores em sequência |
| `trainerbattle_earlyrival trainer, flags, beaten, victory` | rival do começo (dá pra perder) |

Batalha dentro de uma cena (padrão do "route expert" da Route31, em poryscript):

```
    msgbox("Você venceu todos daqui. Vamos lutar.")
    trainerbattle_no_intro(TRAINER_ROUTE_31_EXPERT, "Popped off...")
    createfieldmugshot(MUGSHOT_COOLTRAINER_M)
    msgbox("Você é melhor do que eu imaginava.")
    giveitem(ITEM_AIR_BALLOON)
```

Consultar se já foi derrotado: `defeated(TRAINER_JOEY)` no poryscript
(`goto_if_defeated` / `checktrainerflag` no asm). Para permitir rebatalha,
`cleartrainerflag TRAINER_X`.

### 5. Os textos

No mesmo arquivo, depois dos scripts. `\n` = nova linha, `\p` = nova caixa,
`$` = fim da string. Nome padrão: `<Mapa>_Text_<Nome><Seen|Beaten|After>`.

### 6. Build

```bash
make release USE_LTO_ON_RELEASE=1 -j32
```

O build regenera `src/data/trainers.h` a partir do `.party` (`trainer_rules.mk:10`) e o
`scripts.inc` a partir do `.pory`. Para checar só os dados do treinador, sem ROM:

```bash
make src/data/trainers.h && grep -n "TRAINER_MEU_NPC" -A 30 src/data/trainers.h
```

---

## Variações comuns

**Treinador que só batalha se você falar com ele** (caso Lusamine/Lillie/Kukui/Gladion na
Route29): `trainer_type: "TRAINER_TYPE_NONE"`, `trainer_sight_or_berry_tree_id: "0"`, e o
script continua sendo `trainerbattle_single` — a engine faz o `faceplayer` sozinha.

**NPC que parece treinador mas não batalha** (o "Joey lutando" da Route30, object 5):
`TRAINER_TYPE_NONE` + script comum com `lock`/`msgbox`/`release`. Dá para simular a
batalha com `applymovement ..., Common_Movement_QuestionMark` e `playse SE_PIN`.

**Revanche por Vs. Seeker / route expert:** os pré-requisitos ficam em
`src/vs_seeker.c` (`sRoute31ExpertPrerequisites[]` lista `TRAINER_WADE`, `TRAINER_JOEY`,
`TRAINER_MIKEY`, `TRAINER_DON`). Se você adicionar um treinador numa rota que tem expert,
decida se ele entra nessa lista. Documentação: `docs/tutorials/vs_seeker.md`.

**Docs do projeto:** `docs/data/trainers.json` é gerado por
`tools/soulgold_docs/build_docs.py` e alimenta a página de treinadores — regenere depois
de adicionar treinadores novos, se quiser o site em dia.

---

## Reusar um treinador em várias batalhas (1 slot, vários times)

O que consome slot é o **ID** (e a flag derivada dele), não a batalha. Um único
`TRAINER_X` pode ser usado a história inteira. Três abordagens, da mais barata para a mais
flexível — dá para combinar.

### A. Mesmo time, várias vezes — `cleartrainerflag`

A flag é o único bloqueio. Limpando ela, o mesmo NPC volta a ser batalhável:

```
	trainerbattle_no_intro TRAINER_KUKUI, Route29_Text_KukuiBeaten
	cleartrainerflag TRAINER_KUKUI
	addvar VAR_KUKUI_BATTLES, 1
```

- **Custo:** 0 slots extras. **Limite:** time sempre idêntico.
- Cuidado: enquanto a flag estiver limpa, um NPC com `TRAINER_TYPE_NORMAL` volta a te
  avistar. Para batalha só de história, use `TRAINER_TYPE_NONE` + `trainerbattle_no_intro`
  dentro do script, e controle o "quando" com uma `VAR_*`.
- Vale também para **vários NPCs compartilharem um ID** (clones, capangas do Team Rocket):
  todos usam o mesmo `TRAINER_X` e o mesmo estado de derrotado.

### B. Time sorteado a cada batalha — Trainer Party Pool

Já implementado no repo ([`src/trainer_pools.c`](../src/trainer_pools.c), doc completa em
[`docs/tutorials/how_to_trainer_party_pool.md`](../docs/tutorials/how_to_trainer_party_pool.md)).
Basta declarar **mais Pokémon do que o `Party Size`** — o resto é automático:

```
=== TRAINER_KUKUI ===
Name: Kukui
Class: Expert
Pic: Expert M
Party Size: 4
AI: Basic Trainer

Incineroar
Level: 40
Tags: Ace

Braviary
Level: 38
Tags: Lead

Lycanroc
Level: 38

(… mais 8 Pokémon …)
```

- `Tags: Lead` força o Pokémon para o **primeiro** slot; `Tags: Ace` para o **último**.
  Outras tags: `Weather Setter`, `Weather Abuser`, `Support`, `Tag 5..7`.
- `Pool Rules`, `Pool Prune`, `Pool Pick Functions` afinam o sorteio
  (`src/data/battle_pool_rules.h`). O padrão já respeita Lead/Ace e evita espécie repetida.
- `Copy Pool: TRAINER_Y` faz o treinador usar o pool de outro — bom para "os 3 capangas
  sorteiam do mesmo bolo" sem duplicar dados.
- **Custo:** 0 slots extras. **Limite:** é sorteio; você não escolhe qual time em qual
  momento da história.

### C. Time escolhido pela história — hook em C

O gancho é [`CreateNPCTrainerParty`](../src/battle_main.c#L2189), em `src/battle_main.c`.
Ela **já faz exatamente essa troca** para o campo `overrideTrainer`: copia a
`struct Trainer` para a stack e sobrescreve `.party` / `.partySize` antes de gerar o time.
Basta um caso a mais, chaveado por uma `VAR_*`:

```c
static const struct TrainerMon sKukuiTeam2[] = { /* … */ };
static const struct TrainerMon sKukuiTeam3[] = { /* … */ };

// dentro de CreateNPCTrainerParty(), antes do return
if (trainerNum == TRAINER_KUKUI)
{
    struct Trainer t = *GetTrainerStructFromId(trainerNum);
    switch (VarGet(VAR_KUKUI_BATTLE_STAGE))
    {
    case 1: t.party = sKukuiTeam2; t.partySize = ARRAY_COUNT(sKukuiTeam2); break;
    case 2: t.party = sKukuiTeam3; t.partySize = ARRAY_COUNT(sKukuiTeam3); break;
    }
    return CreateNPCTrainerPartyFromTrainer(party, &t, firstTrainer, gBattleTypeFlags, trainerNum);
}
```

- Os times alternativos são `const struct TrainerMon[]` normais — **não consomem ID nem
  flag**. A história controla com `setvar` + `cleartrainerflag` (opção A).
- Mesma técnica serve para **escalar nível** (`t.party` fixo, mexendo numa cópia dos mons)
  ou trocar `aiFlags` conforme o progresso.
- ⚠️ `overrideTrainer` (o `Copy Pool` do `.party`) é **dado estático em ROM** — não serve
  para trocar em runtime. Por isso essa opção precisa mesmo do hook em C.
- **Custo:** 0 slots extras, mas é código: entra no diff de `battle_main.c` e precisa de
  atenção em merge com upstream.

### Resumo

| | Slots | Time varia | Controlado pela história |
|---|---|---|---|
| A. `cleartrainerflag` | 0 | ❌ | ✅ (quando) |
| B. Party Pool | 0 | ✅ aleatório | ❌ |
| C. Hook em C | 0 | ✅ escolhido | ✅ |

---

## Armadilhas

| Sintoma | Causa provável |
|---------|----------------|
| Mon nível 100 com IV 31 | Faltou `Level:` / `IVs:` no `.party` — são esses os padrões |
| Time com golpes "errados" | Nenhum golpe escrito → set automático por level-up. Escreva os 4 (use `- None` para vazio) |
| Erro do trainerproc apontando linha estranha | Faltou a **linha em branco** entre cabeçalho e mon, ou entre mons |
| `undefined reference to TRAINER_X` | Bloco no `.party` existe mas o `#define` em `opponents.h` não (ou vice-versa) |
| Vencer o treinador dispara um evento aleatório de outro mapa | ID na faixa `1056-1163`: a flag foi reaproveitada. Mova o treinador para um ID livre |
| Treinador nasce "já derrotado" / volta a ser batalhável sozinho | Mesma colisão de flag, no sentido inverso |
| Treinador nunca te avista | `trainer_type` ficou `TRAINER_TYPE_NONE`, raio `"0"`, ou `movement_type` aponta para outro lado |
| A cena trava ao ser avistado | `lock`/`faceplayer` antes do `trainerbattle_*` |
| Batalha repete infinitamente | Script não usa `trainerbattle_*` (que seta a flag), ou algum `cleartrainerflag` sobrando |
| Editou `src/data/trainers.h` e sumiu | Ele é **gerado** e gitignored — a fonte é `src/data/trainers.party` |
| Editou `scripts.inc` de um mapa com `.pory` e sumiu | O `.inc` é gerado do `.pory` |
| Texto pós-batalha nunca aparece | Ele só roda ao falar com o treinador **já derrotado** — é o comportamento correto |
| Treinador invisível / não aparece | Isso é sprite/flag: ver [`adicionar-npc.md`](adicionar-npc.md) |
