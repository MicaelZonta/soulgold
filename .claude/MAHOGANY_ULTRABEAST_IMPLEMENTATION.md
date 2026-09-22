# Mahogany — Xurkitree + Celesteela (Rift Mission 2) — plano de implementação ESQUELETO

**Status:** **esqueleto implementado** — 19/09/2026. Build limpo
(`make -j$(nproc)`). Runtime pendente: checklist em §10.
Revisão 2 — 19/09/2026 (revisão 1: plano; revisão 2: implementação + §12).
**Modo:** esqueleto (skill `evento-esqueleto`). Diálogo curto, coreografia mínima,
mas estado, visibilidade, gatilhos, batalha e retry **completos e corretos**.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6 (V14/V15).
**Missão anterior:** [`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md)
— este doc **continua** a máquina de estados dela e **substitui** o stub da Missão 2
que ficou em `OlivineCity_House1` (§4.4 daquele doc).

Escopo: do gancho final de Blackthorn (o jogador volta a Olivine) até o fim do
incidente de Mahogany, terminando com o gancho que manda o jogador de volta a
Olivine para a Missão 3 (Blacephalon + Stakataka, Cherrygrove, Kukui).

**Decisões desta missão:**
- Elenco: **Looker, Anabel e Lillie** (+ Alolan Ninetales fora da Poké Ball).
- Local: `Mahoganytown`, praça sul, na frente do Pokémon Center.
- Os chefes são **muito mais fortes** que os de Blackthorn: 4 barras, nível 80,
  multiplicador 130, moveset curado e item segurado. É a escalada deliberada da
  Missão 1 → Missão 2 (§6.4). Blackthorn fica como a missão-tutorial.
- Mesma estrutura padrão: escolha + boss simples, captura bloqueada, derrota =
  blackout e retry.

---

## 0. Resumo do fluxo

```text
Blackthorn resolvido                     VAR_RIFT_MISSIONS_STATE = 4
  └─ entrar em OlivineCity_House1 ─────▶ cena: Looker + Anabel, briefing M2 → 5
                                           + setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
       └─ Mahogany: cidade vazia (só Looker, Anabel, Lillie, Ninetales)
            └─ falar com Looker ▶ Lillie expõe a leitura dela ▶ SIM
                 └─ cena 100% scriptada ▶ ruptura: Xurkitree + Celesteela
                      └─ ESCOLHA: qual você enfrenta? Lillie + Ninetales ficam com a outra
                           └─ boss battle simples, 4 barras, Lv80, x130, moveset + item
                                ├─ perdeu / desistiu → blackout → Centro de Mahogany (Joy) → flag setada → recomeça
                                ├─ outro             → reset silencioso → recomeça
                                └─ venceu            → fala da Lillie conforme a escolha → gancho
                                                       → clearflag + estado 6 → warp no lugar (cidade repovoa)
                                     └─ Olivine House1: stub da Missão 3 (Cherrygrove / Kukui)
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_ULTRABEAST_MAHOGANY` | `include/constants/flags.h` | `0x1042` | Primeira livre depois de `FLAG_NO_CATCHING` (0x1041). **Atualizar `CUSTOM_FLAGS_END`** para apontar nela (hoje aponta para `FLAG_NO_CATCHING`, `flags.h:1776`). |
| `LOCALID_MAHOGANY_UB_*` | `include/constants/map_event_ids.h` | 10-15 | Seis linhas novas, à mão, sob um cabeçalho `// MAP_MAHOGANYTOWN` novo (o arquivo ainda não tem essa seção). |

Nenhuma var nova, nenhuma flag de batalha nova: `FLAG_NO_CATCHING` /
`B_FLAG_NO_CATCHING` já existem desde Blackthorn e são compartilhadas por
todas as Rift Missions. A engine limpa `FLAG_NO_CATCHING` sozinha ao fim de
toda batalha (`Overworld_ResetBattleFlagsAndVars`, `src/overworld.c:440`) —
setar imediatamente antes da batalha e nunca limpar à mão.

Comentário obrigatório acima do `#define` novo, no padrão de
`FLAG_EVENT_ULTRABEAST_BLACKTHORN` (`flags.h:1765-1770`): quem seta, quem
limpa, e a frase de que ela só existe porque o campo `flag` do `map.json` não
lê var.

**Não é preciso bloquear fuga.** Em boss battle "Run" é desistência explícita
(`CanPlayerForfeitBattle`, `src/battle_main.c:6688`): resultado
`B_OUTCOME_FORFEITED`, que conta como derrota → blackout → retry.

### 1.2 Máquina de estados `VAR_RIFT_MISSIONS_STATE` (continuação)

Valores 0-3 estão definidos no doc de Blackthorn §1.2 e **não mudam**.

| Valor | Significado | Quem escreve | Quem lê |
|---|---|---|---|
| 4 | Blackthorn resolvido; briefing da Missão 2 pendente | `BlackthornCity_EventScript_UBResolved` (já existe) | Olivine House1 (cena de chegada + briefing M2) |
| 5 | Briefing M2 feito; incidente de Mahogany **ativo** | `OlivineCity_House1_EventScript_BriefingTalkM2` | Olivine House1 ("vá na frente"); `Mahoganytown_OnTransition` |
| 6 | Mahogany resolvido; briefing da Missão 3 pendente | `Mahoganytown_EventScript_UBResolved` | Olivine House1 (stub da Missão 3) |
| 7+ | Reservado para a Missão 3 (Cherrygrove) | próximo doc | — |

**Invariante:** `FLAG_EVENT_ULTRABEAST_MAHOGANY` setada ⇔ `VAR_RIFT_MISSIONS_STATE == 5`.
As duas mudam **juntas, no mesmo script** (Olivine seta, Mahogany limpa). A flag
existe só porque o campo `flag` do `map.json` não lê var — é ela que esvazia a
cidade. A var é a autoridade da história.

A invariante de Blackthorn (`FLAG_EVENT_ULTRABEAST_BLACKTHORN` ⇔ estado 3)
continua valendo e **não** é tocada por esta missão. As duas flags nunca estão
setadas ao mesmo tempo, porque a var só tem um valor.

Nenhuma outra flag/var persistente. A escolha do jogador (qual UB enfrentar) é
temporária: numa nova tentativa ele escolhe de novo.

### 1.3 Temporários por mapa

| Mapa | Temp | Uso |
|---|---|---|
| `OlivineCity_House1` | `VAR_TEMP_1` | Trava uma-vez-por-visita do gatilho de frame (**já existe**; agora serve aos estados 2 **e** 4) |
| `Mahoganytown` | `FLAG_TEMP_1` | Cache de visibilidade do elenco (Looker, Anabel, Lillie, Ninetales) |
| `Mahoganytown` | `FLAG_TEMP_2` | Cache das Ultra Beasts (sempre escondidas até a cena) |
| `Mahoganytown` | `VAR_TEMP_2` | Resultado da batalha |
| `Mahoganytown` | `VAR_TEMP_3` | Escolha do jogador: 0 = Xurkitree, 1 = Celesteela. Sobrevive à batalha (voltar da batalha não passa por `LoadMapFromWarp`) |

> ⚠ **`VAR_TEMP_0` e `VAR_TEMP_1` estão OCUPADOS em `Mahoganytown`.**
> `MahoganyTown_EventScript_MerchantTrigger` e os quatro ramos do vendedor de
> Rage Candy Bar fazem `getplayerxy VAR_TEMP_0, VAR_TEMP_1`
> (`data/maps/Mahoganytown/scripts.inc:102,119,160,171,181`). Por isso esta
> missão começa em `VAR_TEMP_2` — diferente de Blackthorn, onde `VAR_TEMP_1` era
> a trava de gatilho. Não "uniformizar" com o doc anterior.

`FLAG_TEMP_1` e `FLAG_TEMP_2` estão livres em `Mahoganytown` (nenhuma ocorrência
de `FLAG_TEMP` no `scripts.inc`). Reconfirmar antes de implementar:
`grep -rn "FLAG_TEMP_[12]\b\|VAR_TEMP_[0123]\b" data/maps/Mahoganytown data/maps/OlivineCity_House1 data/scripts/`.

---

## 2. Etapa A — Olivine: briefing da Missão 2

`OlivineCity_House1` tem `.pory` → editar só `data/maps/OlivineCity_House1/scripts.pory`.
O `map.json` **não muda**: Looker e Anabel já existem com `flag: 0` e continuam
morando lá desde o New Game.

### 2.1 O gatilho de chegada passa a atender dois estados

Hoje `OlivineCity_House1_EventScript_BriefingTrigger` desiste com
`goto_if_ne VAR_RIFT_MISSIONS_STATE, 2, ..._End`. Trocar por um despacho, mantendo
a checagem de porta e a trava `VAR_TEMP_1` **como primeira instrução**:

```asm
OlivineCity_House1_EventScript_BriefingTrigger::
	setvar VAR_TEMP_1, 1                        @ primeira instrução: para de disparar
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 4, OlivineCity_House1_EventScript_End
	goto_if_ne VAR_0x8005, 8, OlivineCity_House1_EventScript_End
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefing
	end
```

`OlivineCity_House1_EventScript_StageBriefing` é o corpo que hoje vem depois dos
`goto_if_ne` (o `lockall` / `hidefollower` / aproximação / `call ...BriefingTalk` /
volta / `releaseall` / `end`), **sem nenhuma mudança**. A coreografia, os quatro
`Movement_*` e as posições (4,5)/(7,5)/(4,8) são reaproveitados inteiros.

### 2.2 `BriefingTalk` vira um despachante

O rótulo `OlivineCity_House1_EventScript_BriefingTalk` continua sendo o único
ponto que muda flag+var, e continua sendo chamado tanto pela cena quanto pelos
scripts de objeto. Ele passa a escolher o briefing pelo estado:

```asm
@ Invariantes:
@   FLAG_EVENT_ULTRABEAST_BLACKTHORN setada <=> VAR_RIFT_MISSIONS_STATE == 3
@   FLAG_EVENT_ULTRABEAST_MAHOGANY   setada <=> VAR_RIFT_MISSIONS_STATE == 5
@ Flag e var mudam sempre no mesmo bloco.
OlivineCity_House1_EventScript_BriefingTalk::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_BriefingTalkM2
	@ cai no M1 (estado 2)
OlivineCity_House1_EventScript_BriefingTalkM1::
	msgbox OlivineCity_House1_Text_Briefing, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
	setvar VAR_RIFT_MISSIONS_STATE, 3
	return

OlivineCity_House1_EventScript_BriefingTalkM2::
	msgbox OlivineCity_House1_Text_BriefingM2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
	setvar VAR_RIFT_MISSIONS_STATE, 5
	return
```

`goto` dentro de um script alcançado por `call` é seguro: `call` empilha o
endereço de retorno e `return` o desempilha, independentemente de quantos `goto`
houve no meio.

### 2.3 Diálogo por estado — Looker e Anabel

`OlivineCity_House1_EventScript_Looker` (`lock`, `faceplayer`) passa a ramificar:

| Estado | O que acontece |
|---|---|
| 0-1 | `Text_LookerHoliday` (inalterado) |
| 2 | `call ..._BriefingTalk` → M1 (inalterado) |
| 3 | `Text_LookerGoAhead` (Blackthorn, inalterado) |
| **4** | `call ..._BriefingTalk` → **M2**. Substitui `..._EventScript_LookerMission2` e o texto `..._Text_LookerMission2Stub`, que são **apagados**. |
| **5** | **Novo** `Text_LookerGoAheadM2`: "Looker: Mahogany, {PLAYER}! We are right behind you." |
| **≥ 6** | **Novo** stub da Missão 3: "Looker: Cherrygrove. We are still waiting on the Professor's own report. Come back soon, {PLAYER}!" |

`OlivineCity_House1_EventScript_Anabel`, mesma estrutura:

| Estado | O que acontece |
|---|---|
| 0-1 | `Text_AnabelHoliday` (inalterado) |
| 2 | `call ..._BriefingTalk` (inalterado) |
| 3 | `Text_AnabelGoAhead` (inalterado) |
| **4** | `call ..._BriefingTalk` → M2. Substitui `..._AnabelMission2` / `..._Text_AnabelMission2Stub`. |
| **5** | "Anabel: Go on. Lillie is already there. She has been for two days." |
| **≥ 6** | "Anabel: Rest. Looker will brief you on Cherrygrove." |

Ordem dos `goto_if_eq`: 2, 3, 4, 5, depois `goto_if_ge ... 6`, e o `msgbox` de
férias como default. **Não** deixar nenhum `goto_if_ge ... 4` sobrando do código
atual: ele engoliria os estados 5 e 6.

Todos os ramos continuam terminando em `OlivineCity_House1_EventScript_ReleaseEnd`.

> `Text_BriefingM2` (inglês, placeholder — caixas de ~34 colunas):
> Looker: {PLAYER}! Perfect timing. The Mahogany report is confirmed.
> Anabel: Two signatures again. One electrical. One... heavy.
> Looker: The town lost its power three nights ago. Every lamp, every machine.
> Anabel: And the readings did not come from the Lake of Rage after all. They came from the town itself.
> Looker: There is more. A young lady reached Mahogany before we did, and has been taking notes for two days.
> Anabel: Lillie. She refused to leave. She says she already knows what those two are doing.
> Looker: Mahogany Town, {PLAYER}. Hear her out before you act.

(Continuidade: o gancho de Blackthorn falava em "strange lights over the Lake of
Rage". O briefing corrige a origem de propósito — é o que Lillie descobriu.)

---

## 3. Etapa B — Mahogany: cidade vazia

`Mahoganytown` **não tem** `.pory` → editar `data/maps/Mahoganytown/scripts.inc`
direto, e `data/maps/Mahoganytown/map.json`.

### 3.1 Esconder a cidade

`Mahoganytown/map.json`: trocar `"flag": "0"` por
`"flag": "FLAG_EVENT_ULTRABEAST_MAHOGANY"` nos **oito** objetos abaixo:

| Local id | Objeto | (x,y) |
|---|---|---|
| 1 | Old man (Gramps) | (7,13) |
| 2 | Woman (Lass) | (24,8) |
| 3 | Balding man (vendedor de Rage Candy Bar) | (30,11) |
| 5 | OW Aipom | (27,6) |
| 6 | OW Aipom | (29,17) |
| 7 | OW Aipom | (24,17) |
| 8 | OW Aipom | (6,2) |
| 9 | OW Delibird | (8,16) |

**Não mexer no objeto 4** (Fat man / Fisher, (10,20)): ele já tem flag própria,
`FLAG_HIDE_MAHOGANY_TOWN_FATMAN`. Verificado: essa flag é limpa uma única vez em
`MahoganyTown_EventScript_TownTrigger` (primeira chegada à cidade) e **setada de
novo** em `RocketHideout_B2F/scripts.inc:555`, sem nenhum `clearflag` depois. No
pós-E4 ele já está invisível — a cidade fica vazia sem tocar na flag de outra
quest.

**A Joy continua:** está em `MahoganyTown_PokemonCenter` (outro mapa), intocado.
Porta do Centro (21,19) livre durante todo o evento. Ginásio (10,19), Shop
(15,10), House1 (27,10), Valor Cavern (33,19) e o gate da Route 43 (14,4)
continuam acessíveis — só o exterior esvazia.

**Gatilhos herdados, conferidos como inofensivos no pós-E4:**
- Os 50 `coord_events` do vendedor cobrem `VAR_MAHOGANY_TOWN_STATE` 1-16. No
  pós-E4 essa var vale **17** (setada em `GoldenrodCity_RadioTower_5F/scripts.inc:951`,
  etapa obrigatória antes da Liga), então nenhum deles dispara — e portanto o
  `turnobject LOCALID_MAHOGANY_MERCHANT` nunca roda com o vendedor escondido.
- `Mahoganytown_OnFrame` só tem a entrada `VAR_MAHOGANY_TOWN_STATE == 15`
  (`RocketTrigger`): idem, nunca dispara.
- `Mahoganytown_OnLoad` (`FixTree` + `setrespawn HEAL_LOCATION_MAHOGANYTOWN`)
  continua como está. É ele que garante que o blackout devolve o jogador ao
  Centro de Mahogany.

> ⚠ **Dependência criada:** depois desta mudança, um `removeobject` em qualquer
> dos oito objetos acima **seta `FLAG_EVENT_ULTRABEAST_MAHOGANY` e esvazia a
> cidade**. Antes eram `flag: 0`, onde `removeobject` era inofensivo.

### 3.2 Elenco — anexar no fim de `object_events` (locais 10-15)

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 10 | `LOCALID_MAHOGANY_UB_NINETALES` | `OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)` | (19,22) | `FACE_UP` | `NULL` | `FLAG_TEMP_1` |
| 11 | `LOCALID_MAHOGANY_UB_LILLIE` | `OBJ_EVENT_GFX_LILLIE` | (20,22) | `FACE_UP` | `Mahoganytown_EventScript_UBLillie` | `FLAG_TEMP_1` |
| 12 | `LOCALID_MAHOGANY_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (21,22) | `FACE_UP` | `Mahoganytown_EventScript_UBLooker` | `FLAG_TEMP_1` |
| 13 | `LOCALID_MAHOGANY_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (22,22) | `FACE_UP` | `Mahoganytown_EventScript_UBAnabel` | `FLAG_TEMP_1` |
| 14 | `LOCALID_MAHOGANY_UB_XURKITREE` | `OBJ_EVENT_GFX_SPECIES(XURKITREE)` | (13,21) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 15 | `LOCALID_MAHOGANY_UB_CELESTEELA` | `OBJ_EVENT_GFX_SPECIES(CELESTEELA)` | (13,22) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |

- Todos com `"elevation": 0`, `movement_range_x/y: 0`, `TRAINER_TYPE_NONE`,
  `trainer_sight_or_berry_tree_id: "0"`.
- Conferido: `XURKITREE` e `CELESTEELA` têm bloco `OVERWORLD(` em
  `src/data/pokemon/species_info/gen_7_families.h:6913` e `:6989` (tabelas de pic em `:6914` e `:6990`)
  (`SIZE_32x32`, paletas próprias). `NINETALES_ALOLA` já é usado em
  `DragonsDen_Shrine` (objeto 6), `LILLIE` em três mapas, `LOOKER`/`ANABEL` em
  Olivine House1 e Blackthorn.
- **Sempre no fim de `object_events`:** os locais 10-15 são posicionais; inserir
  qualquer coisa no meio renumera o elenco inteiro.
- Seis linhas novas em `include/constants/map_event_ids.h`, à mão, sob um
  cabeçalho `// MAP_MAHOGANYTOWN` novo. Cuidado: `LOCALID_MAHOGANY_NURSE` já
  existe **duas vezes** no arquivo (`:657` e `:904`, ambas com valor 1, para o
  Centro) — usar o prefixo `LOCALID_MAHOGANY_UB_` evita colisão.
- `LOCALID_MAHOGANY_MERCHANT` continua definido com `.set` no topo do
  `scripts.inc` (valor 3). Não mexer.
- 15 templates < limite de 64.

Looker e Anabel ficam em Olivine **e** aqui durante o estado 5 — aceito pelo
autor, o evento inteiro é cutscene (design §5). Ver §9.

### 3.3 Visibilidade — `ON_TRANSITION` (novo)

`Mahoganytown` hoje só tem `ON_LOAD` e `ON_FRAME_TABLE`. Adicionar a linha do
meio, sem reordenar as outras:

```asm
Mahoganytown_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Mahoganytown_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Mahoganytown_OnTransition   @ NOVO
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Mahoganytown_OnFrame
	.byte 0

Mahoganytown_OnTransition::
	call Mahoganytown_EventScript_ApplyUBVisibility
	end

@ Elenco (FLAG_TEMP_1) visível só com o incidente ativo. Ultra Beasts
@ (FLAG_TEMP_2) sempre escondidas no load: só a cena as faz aparecer.
@ Temps zeram a cada load (ClearTempFieldEventData), então recalcula sempre.
Mahoganytown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	goto_if_unset FLAG_EVENT_ULTRABEAST_MAHOGANY, Mahoganytown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	return

Mahoganytown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	return
```

Roda também ao entrar pela borda — Route 42 (oeste), Route 43 (norte, pelo gate)
e Route 44 (leste) —, não só por warp.

### 3.4 Planta da cena (dump real, bit 11; `#` = bloqueado)

`python3 .claude/skills/encenar-cutscene/dump_mapa.py Mahoganytown 11 24 19 23`

```text
       x= 11 12 13 14 15 16 17 18 19 20 21 22 23 24
  y=19      #  #  .  .  .  .  .  .  #  #  W  #  #  #    W (21,19) = porta do Pokémon Center
  y=20      .  .  .  .  .  .  .  .  .  .  f  .  .  .    f (21,20) = pouso do Fly / saída do Centro
  y=21      .  .  X  .  .  .  .  .  .  .  t  .  .  .    t (21,21) = ÚNICO tile para falar com Looker
  y=22      .  .  C  .  .  .  *  .  N  L  K  A  .  .    * (17,22) = posição de combate do jogador
  y=23      #  #  #  #  #  #  #  #  #  #  #  #  #  #

  N Ninetales (19,22)  L Lillie (20,22)  K Looker (21,22)  A Anabel (22,22)
  X Xurkitree (13,21)  C Celesteela (13,22)   — X/C escondidos até a cena
```

O Looker fica no "bolso" (21,22): (21,23) é parede, (20,22) é a Lillie e (22,22) é
a Anabel. **Só dá para falar com ele de (21,21), olhando para baixo.** Isso torna
o início da cena determinístico sem `getplayerxy`. Documentar num comentário `@`
acima do script.

Bônus conferido: `HEAL_LOCATION_MAHOGANYTOWN` fica em **(21,20)**
(`src/data/heal_locations.h:181-185`) — o mesmo tile em que o jogador sai do
Centro. Chegar de Fly ou sair do Centro deixa o jogador a um passo do tile de
conversa, olhando na direção certa.

Lillie e Anabel continuam conversáveis antes da cena: (20,21) e (22,21) estão
livres acima delas. Ninetales é `script: NULL`.

### 3.5 Conversas antes da cena

- `Mahoganytown_EventScript_UBAnabel` (`lock`, `faceplayer`):
  "Anabel: The residents are in the Gym basement. Pryce opened it himself."
  "Speak with Looker when you're ready."
- `Mahoganytown_EventScript_UBLillie` (`lock`, `faceplayer`):
  "Lillie: {PLAYER}. I was hoping it would be you."
  "I've watched them for two days. I'd rather explain it to everyone at once —
  go on, talk to Looker."
  Depois `turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_NORTH` (volta ao
  `FACE_UP` do `map.json`; ela e o Ninetales precisam continuar olhando para a
  rua quando a cena começar).

---

## 4. Etapa C — A cena (100% scriptada a partir do SIM)

### 4.1 Pré-checagens (`Mahoganytown_EventScript_UBLooker`)

```asm
@ Só alcançável de (21,21), olhando para baixo: (21,23) é parede e os vizinhos
@ leste/oeste do Looker são a Anabel e a Lillie. Não precisa de getplayerxy.
Mahoganytown_EventScript_UBLooker::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox Mahoganytown_Text_UBLillieTheory, MSGBOX_DEFAULT
	msgbox Mahoganytown_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Mahoganytown_EventScript_UBNotReady
	goto Mahoganytown_EventScript_UBScene

Mahoganytown_EventScript_UBNotReady::
	msgbox Mahoganytown_Text_UBNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end
```

- Nenhum estado muda antes do SIM. O SIM é o último ponto de saída.
- Batalha simples: não é preciso checar quantidade de Pokémon.
- A exposição da Lillie vem **antes** do SIM de propósito: ela precisa ter dito a
  ideia dela para o grupo antes de qualquer um se mexer (design §3.2 — "observa
  antes de agir, explica sua ideia ao grupo e sustenta sua posição").

> `UBLookerGreet` — Looker: {PLAYER}! You are here, and the street is empty. Excellent.
> The power is still out. Whatever is drawing it has not finished.
>
> `UBLillieTheory` —
> Lillie: May I? I've had two days to watch them.
> Looker: Please, mademoiselle.
> Lillie: They aren't hunting anything. They're feeding each other.
> The tall one pulls the current out of everything in the town. The other burns it off, and the air fills up again.
> Looker: ...Forgive me. That is a great deal to conclude from notes.
> Lillie: It's what I saw. Four times, at the same interval.
> If we push them both at once, they only come back stronger. We have to split them and hold them apart.
> Anabel: She's right. The instruments show the same cycle. I should have read it sooner.
> Looker: Then we do it her way.
>
> `UBReady` — Looker: One warning, {PLAYER}. These two have been feeding for three nights.
> They are not what we met in Blackthorn.
> Anabel: Bring everything you have. Are you ready?
>
> `UBNotReady` — Looker: Wise. The Center still has its own generator. I will be here.

### 4.2 Ruptura

Ordem obrigatória: **Lillie e Ninetales primeiro, depois o jogador, depois Looker
e Anabel.** O caminho do Ninetales passa por (17,22), que é o tile final do
jogador; e Looker/Anabel só podem subir depois que o jogador libera (21,21).

```asm
Mahoganytown_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	@ Ninetales (19,22)->(18,22)->(17,22)->(16,22)->(15,22)->(15,21), olha oeste.
	@ Lillie    (20,22)->(20,21)->(19,21)->(18,21)->(17,21)->(16,21), olha oeste.
	@ Linhas diferentes o tempo todo (ele em y=22, ela em y=21) e nenhum tile em
	@ comum em nenhum passo -> andam juntos. O parceiro vai na frente.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesAdvance
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieAdvance
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	@ Jogador (21,21)->(20,21)->(19,21)->(18,21)->(17,21)->(17,22), olha oeste.
	@ Só depois dos dois: (17,22) é tile de passagem do Ninetales.
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Looker (21,22)->(21,21), Anabel (22,22)->(22,21): colunas diferentes, sem
	@ cruzamento -> juntos. (21,21) só vaga quando o jogador sai, acima.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_StepUpFaceLeft
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_StepUpFaceLeft
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	msgbox Mahoganytown_Text_UBRiftWarning, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1          @ vertical pan
	setvar VAR_0x8005, 1          @ horizontal pan
	setvar VAR_0x8006, 24         @ num shakes
	setvar VAR_0x8007, 5          @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_MAHOGANY_UB_XURKITREE
	addobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Mahoganytown_Text_UBAppear, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBChoose

Mahoganytown_Movement_NinetalesAdvance:
	walk_left, walk_left, walk_left, walk_left, walk_up, face_left, step_end
Mahoganytown_Movement_LillieAdvance:
	walk_up, walk_left, walk_left, walk_left, walk_left, face_left, step_end
Mahoganytown_Movement_PlayerToLine:
	walk_left, walk_left, walk_left, walk_left, walk_down, face_left, step_end
Mahoganytown_Movement_StepUpFaceLeft:
	walk_up, face_left, step_end
```

Conferido tile a tile (bit 11, `dump_mapa.py Mahoganytown 11 26 20 22`): a faixa
x=11..26 em y=20, 21 e 22 é **toda** livre, e y=23 é parede de x=1 a x=27.
Nenhum objeto da cidade fica no caminho (os oito estão escondidos; o Fat man em
(10,20) já está escondido desde o Rocket Hideout e está fora da faixa).

Posições ao fim da aproximação:

```text
  y=21   ... X(13,21)  .  Ninetales(15,21) Lillie(16,21)  .  ...  Looker(21,21) Anabel(22,21)
  y=22   ... C(13,22)  .        .               .     Jogador(17,22)
```

Com o jogador em (17,22) a câmera cobre x 10..24, y ~18..27: as duas UBs (x=13),
Lillie, Ninetales, Looker e Anabel ficam na tela. **O jogador é o ator mais ao
sul da cena** — ninguém fica abaixo dele, então a caixa de texto não cobre
nenhum personagem (ao contrário de Blackthorn §12.5).

Todo mundo já olha para o lado certo em qualquer ramo da escolha: o jogador e
Lillie estão a leste das duas UBs, e as duas UBs olham para o leste
(`FACE_RIGHT`). Nenhum `turnobject` é necessário.

> `UBRiftWarning` — Lillie: There. The air is folding over itself— get back!
> `UBAppear` — Looker: Xurkitree! And Celesteela!
> Anabel: ...I felt that one before the readings moved.
> Anabel: Never mind. Later.

(A fala da Anabel é a única semente de Faller aqui. O design reserva a revelação
para a reunião antes do altar, §7 item 6 — não adiantar.)

### 4.3 A escolha — estrutura padrão de todas as missões

Sem opção de cancelar (`ignoreBPress = TRUE`): a cena já começou. Confirmado em
`Task_HandleScrollingMultichoiceInput` (`src/script_menu.c:500-506`) que o
`LIST_CANCEL` é engolido — `VAR_RESULT` só pode sair 0 ou 1, não falta
tratamento de `MULTI_B_PRESSED`.

```asm
Mahoganytown_EventScript_UBChoose::
	msgbox Mahoganytown_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, Mahoganytown_Text_ChoiceXurkitree, Mahoganytown_Text_ChoiceCelesteela
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Xurkitree, 1 = Celesteela
	closemessage
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBPickCelesteela
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	msgbox Mahoganytown_Text_UBPickedXurkitree, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle

Mahoganytown_EventScript_UBPickCelesteela::
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	msgbox Mahoganytown_Text_UBPickedCelesteela, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle
```

> `UBChoosePrompt` — Lillie: We split them now, while they're still apart.
> Pick one, {PLAYER}. Ninetales and I will hold the other.
> `ChoiceXurkitree` — "Xurkitree" · `ChoiceCelesteela` — "Celesteela"
> `UBPickedXurkitree` — Lillie: Then the tall one is ours. Ninetales — Snow, now!
> `UBPickedCelesteela` — Lillie: All right. Ninetales, get between it and the power lines. Don't let it drink!

### 4.4 Batalha — boss simples e **muito** mais forte

Mesmas peças de Blackthorn, com os quatro parafusos apertados. O sistema de boss
só existe em batalha **simples** (`InitBossBattleData`), que é a outra razão de a
missão dividir as UBs.

```asm
@ SKELETON: coreografia e falas são placeholder; os números abaixo NÃO são.
@ Escalada deliberada sobre Blackthorn (2 barras / Lv70 / x110).
Mahoganytown_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                   @ limpa pela engine no fim da batalha
	@ B_FLAG_NO_WHITEOUT NÃO é setado: perder = blackout (batalha de ameaça).
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBSetupCelesteela
	setbossbattle 4, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_XURKITREE, 80, ITEM_MAGNET
	seteventmonmoves MOVE_TAIL_GLOW, MOVE_THUNDERBOLT, MOVE_ENERGY_BALL, MOVE_DAZZLING_GLEAM
	goto Mahoganytown_EventScript_UBStartBattle

Mahoganytown_EventScript_UBSetupCelesteela::
	setbossbattle 4, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_CELESTEELA, 80, ITEM_LEFTOVERS
	seteventmonmoves MOVE_HEAVY_SLAM, MOVE_FLAMETHROWER, MOVE_EARTHQUAKE, MOVE_AIR_SLASH

Mahoganytown_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, Mahoganytown_EventScript_UBResolved
	goto Mahoganytown_EventScript_UBUnresolved
```

Ordem das macros idêntica à de `bosslegendaryencounterwithmoves`
(`asm/macros/event.inc:2231-2247`): `setbossbattle` → `playmoncry` →
`seteventmon` → `seteventmonmoves` → `special`. Nenhum caminho sai do script
entre elas, então não é preciso `clearbossbattle`.

**Os números, e por que estes:**

| Parafuso | Blackthorn (M1) | **Mahogany (M2)** | Limite / referência |
|---|---|---|---|
| Barras | 2 | **4** | `MAX_BOSS_HEALTH_BARS 4` (`include/battle_boss.h:4`) — é o teto |
| Nível | 70 | **80** | Mewtwo, Kyogre, Latios, Hoopa do repo usam 80 |
| Multiplicador | 110 | **130** | `DEFAULT_BOSS_STAT_MULTIPLIER 110`. **Nada no repo passa de 110 hoje** — este é o primeiro. Aplica-se a Atk/Def/Spe/SpA/SpD, com `min(MAX_u16, …)` (`src/battle_boss.c:678-687`) |
| Moveset | golpes de nível | **curado, 4 slots** | `seteventmonmoves` |
| Item | nenhum | **Magnet / Leftovers** | terceiro parâmetro de `seteventmon` |
| Perfil de fases | `NONE` | `NONE` | UBs não têm Mega/Primal/Tera; os 9 perfis existentes são todos de troca de forma (`src/battle_boss.c:355-400`) |

Movesets conferidos contra `src/data/pokemon/all_learnables.json`: os oito
golpes são aprendíveis pelas espécies (não é exigência da engine — é coerência).
Ambas têm `ABILITY_BEAST_BOOST` e `perfectIVCount = LEGENDARY_PERFECT_IV_COUNT`.

- **Xurkitree** — Tail Glow (+3 SpA) + STAB especial + cobertura. Com 4 barras ela
  usa Tail Glow cedo e o resto da luta é corrida contra o relógio. Magnet reforça
  o Thunderbolt.
- **Celesteela** — parede ofensiva: Heavy Slam (STAB físico pesado),
  Flamethrower e Earthquake cobrem Aço/Fada/Elétrico, Air Slash é o segundo STAB.
  Leftovers alonga as quatro barras sem criar loop de stall (por isso **não** tem
  Leech Seed).

Música: `BattleSetup_StartLegendaryBattle` cai no `default` → `MUS_DP_VS_LEGEND`.

**Se o playtest disser que é parede em vez de ameaça**, mexer nesta ordem, um de
cada vez: multiplicador 130 → 120; barras 4 → 3; tirar o item; só então o nível.
Não mexer em nada de §1 para "compensar".

Resultados (`IsPlayerDefeated`, `src/battle_setup.c:1107`):

| Resultado | O que acontece | Por quê |
|---|---|---|
| `B_OUTCOME_WON` | Continua para §5 | A UB escolhida desmaiou |
| `LOST` / `DREW` | **Blackout** → Centro de Mahogany (Joy) | `CB2_WhiteOut`; `Mahoganytown_OnLoad` faz `setrespawn HEAL_LOCATION_MAHOGANYTOWN` |
| `FORFEITED` ("Run" no boss) | **Blackout**, igual à derrota | Boss transforma fuga em desistência (`HandleEndTurn_RanFromBattle`, `src/battle_main.c:5893`) |
| `CAUGHT` / `RAN` / outro | `UBUnresolved`: reset da cena | Inalcançáveis (bola bloqueada; fuga vira FORFEITED), tratados por segurança. Nunca viram vitória. |

**Retry:** nada foi salvo como concluído. A flag do evento continua setada; ao
sair do Centro a cidade continua vazia, o elenco volta às posições do `map.json`
e as UBs voltam a ficar escondidas. Falar com o Looker recomeça do §4.1 —
**inclusive a escolha**, que pode ser outra.

```asm
Mahoganytown_EventScript_UBUnresolved::
	msgbox Mahoganytown_Text_UBGotAway, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_MAHOGANYTOWN, 21, 20          @ recarrega: elenco no lugar, UBs escondidas
	waitstate
	releaseall
	end
```

> `UBGotAway` — Looker: They closed the gap again... The cycle starts over.
> Lillie: Then we do it again. I'm not leaving.

(21,20) é o tile de Fly / saída do Centro: o jogador reaparece a um passo do
tile de conversa do Looker.

---

## 5. Etapa D — Resolução e gancho

A luta da Lillie contra a outra UB é **narrativa**: não há batalha para ela. Ela
se resolve junto com a vitória do jogador, e a fala da Lillie muda conforme a
escolha.

```asm
Mahoganytown_EventScript_UBResolved::
	@ Os dois objetos continuam no mapa após a batalha (não há recarga).
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_XURKITREE       @ flag = FLAG_TEMP_2: seguro
	removeobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreen FADE_FROM_WHITE
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBLillieFoughtXurkitree
	msgbox Mahoganytown_Text_UBLillieFoughtCelesteela, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBAfterBattle

Mahoganytown_EventScript_UBLillieFoughtXurkitree::
	msgbox Mahoganytown_Text_UBLillieFoughtXurkitree, MSGBOX_DEFAULT

Mahoganytown_EventScript_UBAfterBattle::
	msgbox Mahoganytown_Text_UBAfterLillie, MSGBOX_DEFAULT
	closemessage
	@ Looker (21,21)->(20,21)->(19,21)->(18,21), olha oeste.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_LookerToPlayer
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	@ Anabel (22,21)->(22,22)->(21,22)->(20,22)->(19,22)->(18,22), olha oeste.
	@ Linha própria (y=22) e sempre atrás do jogador (17,22): nenhum tile em
	@ comum com o Looker, mas SEQUENCIAL por clareza de leitura da cena.
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToPlayer
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight   @ data/scripts/movement.inc:46
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_SOUTH               @ jogador (17,22) está abaixo
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_SOUTH
	msgbox Mahoganytown_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_MAHOGANY     @ invariante: flag e var juntas
	setvar VAR_RIFT_MISSIONS_STATE, 6
	warpsilent MAP_MAHOGANYTOWN, 17, 22          @ recarrega no lugar: cidade repovoa,
	waitstate                                    @ elenco some pelo ON_TRANSITION
	releaseall
	end

Mahoganytown_Movement_LookerToPlayer:
	walk_left, walk_left, walk_left, face_left, step_end
Mahoganytown_Movement_AnabelToPlayer:
	walk_down, walk_left, walk_left, walk_left, walk_left, face_left, step_end
```

Posições finais: jogador (17,22) → leste; Looker (18,21) → oeste;
Anabel (18,22) → oeste (imediatamente a leste do jogador, na mesma linha);
Lillie (16,21) → sul; Ninetales (15,21) → sul.
Conferido: (18,21), (18,22), (19..22,22) e (22,22) estão livres; a Anabel desce
para y=22 só depois que o Looker já passou por y=21, e o caminho dela em y=22
está vazio porque a Lillie e o Ninetales estão em y=21.
**Ninguém fica ao sul do jogador** — a caixa de texto não cobre ator nenhum.

Por que `warpsilent` no lugar: com a flag limpa, os oito NPCs escondidos só
voltariam quando a câmera andasse, surgindo do nada. Recarregar faz o
`ON_TRANSITION` esconder o elenco e spawnar a cidade de uma vez, sob o fade.
Lillie e Ninetales somem juntos, como pede `parceiro-pokemon-de-npc`, e o
follower do jogador volta pelo warp.

Textos (inglês, placeholder) — **o último bloco é o gancho para Olivine**:

> `UBLillieFoughtCelesteela` (jogador escolheu Xurkitree) — Lillie: Celesteela never got off the ground. Ninetales kept the air cold, and it stayed heavy.
> `UBLillieFoughtXurkitree` (jogador escolheu Celesteela) — Lillie: Xurkitree had nothing left to pull. We kept it off the lines until it went dim.
> `UBAfterLillie` — Lillie: They're going back on their own now. Look — they're not even fighting it.
> ...I was right about them. I'm glad I said it out loud.
>
> `UBHook` — Looker: Magnifique! And the lamps — {PLAYER}, look! The town has its light back!
> Anabel: Lillie. Your reading was better than my instruments. I'd like your notes.
> Lillie: You can have all of them. I'm going to keep watching.
> Looker: One more thing before you rest, {PLAYER}. A report came in while we were busy.
> Anabel: Cherrygrove City. Two more signatures — and a man in a lab coat who will not leave the shore.
> Looker: Professor Kukui. But of course it is Professor Kukui.
> Anabel: Come back to the house in Olivine when you're ready. We'll brief you there.
> Lillie: Cherrygrove... Tell the Professor I'm fine. He worries.

---

## 6. Arquivos tocados (checklist de implementação)

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_MAHOGANY 0x1042` + comentário; mover `CUSTOM_FLAGS_END` |
| `include/constants/map_event_ids.h` | seção `// MAP_MAHOGANYTOWN` nova, 6 locais (10-15), à mão |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho atende estados 2 e 4; `BriefingTalk` vira despachante; ramos 4/5/≥6 em Looker e Anabel; apaga os dois stubs da M2; textos novos |
| `data/maps/Mahoganytown/map.json` | flag do evento em 8 objetos; 6 objetos novos no fim |
| `data/maps/Mahoganytown/scripts.inc` | `ON_TRANSITION` + visibilidade, conversas, cena, escolha, boss, resolução, textos, movimentos |

Não editar `events.inc`/`header.inc`/`connections.inc` nem o `.inc` gerado de
`OlivineCity_House1`. Validar com `make -j$(nproc)`.

Ordem sugerida: flags/localids → `map.json` de Mahogany → `scripts.inc` de
Mahogany → `scripts.pory` de Olivine → build.

---

## 7. Esqueleto × evolução

O que está **deliberadamente simples**. Cada item vira um comentário
`@ SKELETON: <o que falta>` no script correspondente, para que
`grep -rn "SKELETON:" data/maps/{Mahoganytown,OlivineCity_House1}` liste tudo que
falta polir:

| Item | Esqueleto | Evolução prevista |
|---|---|---|
| Luta da Lillie | Narrativa: resolvida junto com a vitória do jogador, fala muda pela escolha | Mostrar o combate dela na tela (Ninetales, Snow, animação de golpe, UB recuando). Batalha real contra Lillie **não** é o plano. |
| Chefes | 4 barras, Lv80, x130, moveset + item — **já é o alvo**, não é placeholder | Perfil de fases próprio em `battle_boss.c` (ex.: Xurkitree trocando de comportamento quando a última barra abre); `setdynamicaifunc`. |
| Diálogos | Curtos, placeholder | Reescrever pela voz do design §3.1 (Lillie observadora e firme; Looker teatral/caloroso; Anabel precisa). |
| Coreografia | Ruptura = tremor + flash; UBs surgem paradas; a escolhida só dá "!" | Apagão visual da cidade (paleta/`setweather`), luzes voltando no fim, animação de portal, música própria. |
| Saída do elenco | Warp no lugar em Mahogany | Lillie e Ninetales saindo a pé para a Route 43, Looker e Anabel indo para o Centro. |
| Moradores | Somem | Reações dos moradores depois do evento (o vendedor de Rage Candy Bar tem material óbvio). |
| Anabel | Só fala; a semente de Faller é uma linha | Beast Balls em Olivine (design §5, ainda pendente desde a M1); desenvolver a semente sem adiantar a revelação do §7. |
| Gancho da M3 | Stub "come back soon" em Olivine | Substituído pelo doc da Missão 3 (Cherrygrove / Kukui), que continua a var em 7+. |

**O que NÃO pode regredir numa evolução:** a máquina de estados §1.2, a
invariante flag ⇔ estado 5, a visibilidade por template, o SIM como único ponto
de saída, a escolha refeita a cada tentativa, o tratamento de todos os
resultados, a proibição de captura e a regra de que `VAR_TEMP_0`/`VAR_TEMP_1` são
do vendedor de Rage Candy Bar.

---

## 8. Dependências frágeis criadas por este plano

Coisas que não existem hoje e que uma evolução distraída quebra em silêncio:

- **Os 8 objetos de Mahogany passam a carregar `FLAG_EVENT_ULTRABEAST_MAHOGANY`.**
  Um `removeobject` em qualquer um deles **esvazia a cidade**. Vale para o
  Gramps, a Lass, o vendedor de Rage Candy Bar, os quatro Aipom e o Delibird.
- **`VAR_TEMP_0` e `VAR_TEMP_1` são do vendedor.** Qualquer script novo em
  `Mahoganytown` que use essas duas corrompe o `getplayerxy` dele — e vice-versa.
- **A ordem dos três blocos de `applymovement` em §4.2.** Lillie/Ninetales →
  jogador → Looker/Anabel. Inverter os dois primeiros faz o Ninetales tentar
  atravessar o jogador em (17,22); mover o Looker antes do jogador o faz tentar
  subir para (21,21) ocupado.
- **`VAR_TEMP_3` depende de não haver recarga de mapa entre a escolha e o fim da
  cena.** Qualquer warp, `setrespawn` com recarga ou coisa que passe por
  `LoadMapFromWarp` entre o `dynmultichoice` e o `UBResolved` perde a escolha, e
  a Lillie narra a UB errada.
- **Objetos novos sempre no fim de `object_events`.** Os locais 10-15 são
  posicionais.
- **O despachante `BriefingTalk` de Olivine agora serve duas missões.** Um
  `goto_if_ge VAR_RIFT_MISSIONS_STATE, 4` sobrando em qualquer ramo de Looker ou
  Anabel engole os estados 5 e 6.

---

## 9. Pendências e riscos conhecidos

- **Looker e Anabel em dois lugares no estado 5: aceito pelo autor** (mesma
  decisão da M1). O evento inteiro é cutscene; eles continuam na casa de Olivine
  (sem flag) e também aparecem em Mahogany. Não esconder em Olivine.
- **Multiplicador 130 é inédito no repo.** Nenhum boss existente passa de 110.
  O caminho de redução está em §4.4; a decisão de "beeem mais forte" é do autor.
- **Assimetria M1 × M2.** Blackthorn (2 barras / Lv70 / x110) fica bem mais fácil
  que Mahogany. Isso é escalada intencional. Se o autor quiser nivelar por cima,
  é uma edição de duas linhas em `BlackthornCity/scripts.inc:440,447` mais o
  `seteventmon` — **e** uma atualização do doc da M1 §9.
- **O Fat man (10,20) não é tocado.** Ele já está escondido desde
  `RocketHideout_B2F/scripts.inc:555`. Se alguma revisão futura voltar a
  mostrá-lo no pós-game, ele passa a ser o único morador visível durante o
  incidente e precisará entrar na lista de §3.1 — o que exige resolver o conflito
  de duas flags num só campo. **Esse conflito já tem solução aprovada:** ver
  §3.1.1 do doc da Missão 3 (`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`), que
  troca o campo `flag` do template por um cache temporário recalculado no
  `ON_TRANSITION` e mantém a flag antiga como verdade persistente.
- Money loss no blackout/desistência é o padrão da engine; aceito pelo design
  (batalha de ameaça).
- **Beast Balls continuam pendentes** desde a M1 (design §5). Enquanto a captura
  estiver bloqueada nas missões, a venda não tem função — mas o design promete
  "desde o início das missões pós-E4".

---

## 10. Teste em runtime

- [ ] Estado 4: entrar em Olivine House1 pela porta dispara a cena; Looker e Anabel param lado a lado, dão o briefing da M2 e voltam ao lugar sem atravessar a mesa. Estado vira 5.
- [ ] Estado 4 entrando de outro jeito (sem a coreografia): falar com Looker **ou** com Anabel dá o mesmo briefing e o mesmo estado 5.
- [ ] Estado 3 (Blackthorn ainda ativo) continua se comportando como antes: a cena de chegada **não** dispara e o diálogo é "vá na frente".
- [ ] Estado 5: diálogo "vá na frente" em Olivine; Mahogany sem Gramps, Lass, vendedor, os 4 Aipom e o Delibird; Centro, Joy, Ginásio, Shop, House1, Valor Cavern e o gate da Route 43 acessíveis.
- [ ] Chegar por Fly, Route 42, Route 43 (gate) e Route 44: elenco sempre presente, UBs sempre ausentes.
- [ ] Falar com Anabel e Lillie antes: falas curtas, nada muda; Lillie volta a olhar para cima. "Não" com o Looker libera e não muda estado.
- [ ] Confirmar que **(21,21) é mesmo o único tile** de onde se fala com o Looker: tentar por (20,21), (22,21) e pela linha y=22 dos dois lados.
- [ ] "Sim": Ninetales e Lillie avançam juntos sem se atravessar, o jogador desce para (17,22), Looker e Anabel sobem. Nenhum ator sobreposto, nenhum atravessando parede.
- [ ] Tremor + flash + as duas UBs aparecendo em (13,21)/(13,22); os dois gritos tocam.
- [ ] Menu da escolha não fecha com B.
- [ ] Escolher Xurkitree: boss Xurkitree com **4 barras**, nível 80, Tail Glow no primeiro ou segundo turno, Magnet no bolso. Lillie fala da Celesteela depois. Idem invertido (Celesteela, Leftovers, Heavy Slam).
- [ ] Bolsa: bola bloqueada nas duas. "Run": desistência → blackout.
- [ ] Perder de propósito: acorda no Centro de **Mahogany**; cidade ainda vazia, elenco no lugar, UBs ausentes; Looker recomeça e a escolha pode ser outra.
- [ ] Vencer: UBs somem, Looker e Anabel se aproximam sem sobrepor ninguém, Lillie e Ninetales viram para o sul, gancho de Cherrygrove/Olivine, fade, cidade repovoada, elenco ausente, follower de volta.
- [ ] Estado 6: stub da Missão 3 em Olivine, com Looker e Anabel; reentrar em Mahogany não traz o elenco nem as UBs de volta.
- [ ] Vendedor de Rage Candy Bar continua funcionando depois do evento (é o único script da cidade que usa `VAR_TEMP_0/1`).
- [ ] Salvar/recarregar em cada estado (4, 5, 6) mantém tudo acima.
- [ ] Regressão da M1: `FLAG_EVENT_ULTRABEAST_BLACKTHORN` continua limpa e Blackthorn continua povoada em todos os estados ≥ 4.

---

## 11. O que este doc copiou da M1 (e o que fez diferente)

Seguindo o §12.6 do doc de Blackthorn.

**Copiado:** a tabela de temporários por mapa, a planta ASCII tirada da colisão
real com o caminho de cada ator em coordenadas, a tabela de resultados de
batalha, o padrão "bolso de parede" para o tile de conversa, o `warpsilent` no
lugar sob fade e a tabela "esqueleto × evolução".

**Diferente, de propósito:**
1. **Todo bloco de script termina em `end`** (o plano da M1 parava no `waitstate`
   e isso foi o único erro que virou bug lá).
2. **O follower está dito explicitamente:** as duas saídas da cena de Mahogany
   (vitória e reset) terminam em `warpsilent`, então o `hidefollower` é desfeito
   pela recarga. Em Olivine não há warp — o follower sai da bola sozinho no
   primeiro passo depois do `releaseall`
   (`src/event_object_movement.c:6225-6241`), comportamento já verificado na M1.
3. **O jogador é o ator mais ao sul da cena**, eliminando a aposta da M1 §12.5
   (Anabel abaixo do jogador, podendo ser coberta pela caixa de texto).
4. **Começa em `VAR_TEMP_2`**, porque `VAR_TEMP_0/1` são do vendedor.
5. **Conferiu os gatilhos herdados do mapa** (`coord_events` e `OnFrame`) antes
   de esconder os objetos que eles referenciam — a checagem que faltou na M1 no
   caso do Sage.

---

## 12. Feedback da implementação (19/09/2026)

Seção escrita **depois** de implementar, conforme a skill `evento-esqueleto` §6
("atualizado quando o código divergir"). Serve para o próximo agente saber o
que é fato verificado e o que continua sendo aposta.

### 12.1 Resultado

**Implementado inteiro, sem cortes.** Nenhum item do plano ficou de fora e
nenhuma decisão de §1 (estado, invariantes, temporários) foi alterada.
`make -j$(nproc)` limpo; ROM linkada (ROM 92,49%, EWRAM 94,28%, IWRAM 73,74%).

Arquivos tocados — exatamente os cinco previstos em §6, nada além:

| Arquivo | O que entrou |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_MAHOGANY 0x1042` + comentário de 5 linhas; `CUSTOM_FLAGS_END` movido para ela |
| `include/constants/map_event_ids.h` | seção `// MAP_MAHOGANYTOWN` nova (antes de `MAP_MAHOGANY_TOWN_POKEMON_CENTER`), locais 10-15 |
| `data/maps/Mahoganytown/map.json` | 8 moradores com a flag do evento; 6 objetos novos no fim (+92 −8 linhas) |
| `data/maps/Mahoganytown/scripts.inc` | `ON_TRANSITION` + visibilidade no topo; seção da Missão 2 anexada no fim (339 → 831 linhas) |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho de dois estados, despachante de briefing, ramos 4/5/≥6, textos |

### 12.2 Premissas do plano que foram reconferidas e bateram

Tudo abaixo foi medido no checkout, não herdado do plano:

- **Colisão.** `dump_mapa.py Mahoganytown 11 26 18 24` reproduz a planta de §3.4
  tile a tile. `y=20/21/22` livres de x=11 a x=26; `y=23` parede inteira;
  (21,19) é a porta do Centro; (21,23) é parede, confirmando o bolso do Looker.
  **Os seis caminhos de §4.2 e §5 foram simulados passo a passo** — nenhum par
  de atores disputa um tile em nenhum passo.
- **`VAR_TEMP_0/1` são do vendedor** — 5 ocorrências de `getplayerxy VAR_TEMP_0,
  VAR_TEMP_1` (o plano dizia 5 linhas; os números de linha mudaram com a
  edição). A missão usa só `VAR_TEMP_2/3`. Zero colisão.
- **`FLAG_TEMP_1/2` livres** em `Mahoganytown` antes da edição.
- **Os 8 moradores tinham `flag: "0"`**; o Fat man (local 4) tinha
  `FLAG_HIDE_MAHOGANY_TOWN_FATMAN` e não foi tocado. Asserção no script de
  edição, não inspeção visual.
- **`VAR_MAHOGANY_TOWN_STATE` = 17 no pós-E4** (`GoldenrodCity_RadioTower_5F/scripts.inc:951`),
  e os 48 `coord_events` do vendedor cobrem só 1-16 → o
  `turnobject LOCALID_MAHOGANY_MERCHANT` nunca roda com ele escondido.
  Reforçado por uma checagem nova: **`VAR_RIFT_MISSIONS_STATE` só sai de 0 em
  `PokemonLeague_HallOfFame/scripts.inc:72`**, então a questline inteira é
  estritamente pós-E4 e o estado 17 é garantido.
- **`XURKITREE` e `CELESTEELA` têm bloco `OVERWORLD(`** (`SIZE_32x32`, paleta
  própria, `sAnimTable_Following_Asym` e `sAnimTable_Following`). Ambas
  `.isUltraBeast = TRUE` e `perfectIVCount = LEGENDARY_PERFECT_IV_COUNT`.
- **Os 8 golpes e os 2 itens existem**; `OBJ_EVENT_GFX_LILLIE/LOOKER/ANABEL`
  existem (331/334/70).
- **`MAX_BOSS_HEALTH_BARS` é 4** (`include/battle_boss.h:4`) — as 4 barras são o
  teto, não um número escolhido. `DEFAULT_BOSS_STAT_MULTIPLIER` é 110.
- **Ordem das macros de boss** conferida contra
  `bosslegendaryencounterwithmoves` (`asm/macros/event.inc:2231`);
  `seteventmon` aceita item como 3º parâmetro (`:2159`).
- **Nenhum `removeobject`** em Mahoganytown fora das duas UBs (`FLAG_TEMP_2`).
  A dependência frágil de §8 está criada, mas hoje não há quem a dispare.

### 12.3 Divergências em relação ao plano

Três, todas pequenas, nenhuma muda contrato:

1. **`local_id` explícito no `map.json`.** O plano falava só em "anexar no fim".
   Os seis objetos novos levam o campo `"local_id"` com o nome da constante,
   como Blackthorn já faz. O `events.inc` gerado confirma 10-15 na ordem certa.
   Os 9 objetos antigos continuam sem o campo (implícitos 1-9). Isso torna os
   ids **auto-documentados**, mas não revoga a regra de §8: continuar anexando
   no fim.
2. **`Mahoganytown_EventScript_UBLillie` termina com `turnobject ... DIR_NORTH`
   que é um no-op.** Ela só é alcançável de (20,21) — (20,23) é parede, (19,22)
   é o Ninetales e (21,22) é o Looker —, então `faceplayer` já a deixa virada
   para o norte. A linha ficou, como o plano pedia, porque documenta a intenção
   (voltar ao `FACE_UP` do `map.json`) e protege contra uma evolução que mude a
   posição dela. Custo zero.
3. **Um stub a mais em Olivine.** O plano previa apagar
   `..._LookerMission2` / `..._AnabelMission2`. Eles viraram **dois** rótulos
   cada: `..._LookerGoAheadM2` (estado 5) e `..._LookerMission3` (estado ≥6),
   idem para a Anabel. Os textos `..._Text_*Mission2Stub` foram apagados e não
   sobrou nenhuma referência órfã (verificado por `grep` em `data/`, `src/`,
   `include/`).

### 12.4 O que o build **não** prova

O build limpo prova que monta e linka. Não prova nada do seguinte, que é o que
a checklist de §10 existe para cobrir:

- Que o Looker é mesmo inalcançável fora de (21,21). O bolso foi derivado da
  colisão e das posições da Lillie e da Anabel — mas a Lillie e a Anabel só
  estão lá **se o elenco spawnou**. Se por algum motivo `FLAG_TEMP_1` ficar
  setada, o Looker fica sozinho no meio da rua e vira alcançável por três
  lados; a cena então começa com o jogador no lugar errado e a coreografia
  inteira de §4.2 desanda em silêncio. **Este é o risco nº 1 do runtime.**
- Que x130 com 4 barras no nível 80 é "ameaça" e não "parede". É inédito no
  repo. Caminho de redução em §4.4, um parafuso por vez.
- Que o `ShakeCamera` + `FADE_TO_WHITE` + dois `playmoncry` não fica longo
  demais antes do `dynmultichoice`.
- Que a caixa de texto não cobre ninguém. O argumento ("o jogador é o ator mais
  ao sul") é geométrico e confere na planta, mas a altura real do sprite de
  32x32 das UBs não foi medida contra a caixa.
- Que o follower volta certo nas duas saídas. As duas terminam em `warpsilent`,
  o que desfaz o `hidefollower` — mas só o runtime confirma.

### 12.5 Ordem sugerida de teste no emulador

Otimizada para achar cedo o que quebra mais coisas, não para seguir §10 na
ordem escrita:

1. Estado 5, chegar em Mahogany por **Fly**: a cidade está vazia? o elenco está
   nos quatro tiles? as UBs estão ausentes? — isso valida `ON_TRANSITION`,
   `map.json` e o bolso do Looker de uma vez.
2. Tentar falar com o Looker de (20,21), (22,21) e da linha y=22 — tem que ser
   impossível.
3. SIM → assistir a coreografia inteira até as UBs aparecerem. Se algum ator
   atravessar outro, é a ordem dos três `applymovement` de §4.2.
4. Escolher e **perder de propósito** — o retry é a parte que mais depende do
   estado estar certo.
5. Só então vencer, e conferir o repovoamento e o estado 6.
6. Por último, as regressões: vendedor de Rage Candy Bar, Blackthorn povoada,
   estado 3 ainda se comportando como antes.

### 12.6 Para quem for evoluir

Ler §7 e §8 antes de tocar em qualquer coisa. Os três itens que mais
provavelmente serão quebrados por distração, em ordem de risco:

1. A **ordem dos três blocos de `applymovement`** em `Mahoganytown_EventScript_UBScene`.
2. Qualquer `goto_if_ge VAR_RIFT_MISSIONS_STATE, 4` novo em Olivine — engole os
   estados 5 e 6. Há comentário no código avisando, acima de cada um dos dois
   despachantes.
3. `removeobject` num dos 8 moradores de Mahogany — **esvazia a cidade**. Há um
   `WARNING` no cabeçalho da seção em `scripts.inc`.

`grep -rn "SKELETON:" data/maps/Mahoganytown data/maps/OlivineCity_House1`
lista tudo que ainda é placeholder.
