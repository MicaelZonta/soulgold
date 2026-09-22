# Mahogany — Necrozma, Xurkitree + Celesteela (Rift Mission 2) — implementação

**Status:** **história evoluída (revisão 3)** — 22/09/2026. Build limpo
(`make -j$(nproc)`). Runtime pendente: checklist em §10. A tabela *pedido →
como ficou* está em §13.
Revisão 3 — 22/09/2026 (revisão 1: plano; revisão 2: esqueleto + §12;
revisão 3: a história, skill `evoluir-historia-de-evento`).
**Modo:** a cena deixou de ser esqueleto: falas finais, arco dramático completo,
Pryce, Necrozma e duas batalhas seguidas. Estado, flags, invariantes, ponto de
saída e retry continuam os da revisão 2 (§1, sem mudança de valor).
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md) §6 (regras comuns) e §6.2.
**Missão anterior:** [`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md)
— este doc **continua** a máquina de estados dela; a M1 revisão 3 é o modelo da
história (§5–§7 e §13 daquele doc).

Escopo: do gancho final de Blackthorn (o jogador volta a Olivine) até o fim do
incidente de Mahogany, terminando com o gancho **sem destino** que manda o
jogador de volta a Olivine. A Missão 3 (Cherrygrove) é revelada no briefing dela.

**A história em três linhas.** Mahogany está sem luz há três noites; a Lillie
está lá há dois dias (o jogador descobre isso ao chegar) e o Pryce termina de
levar os últimos moradores para o Ginásio na frente do jogador. O Necrozma
aparece, ignora o Blizzard do Pryce e deixa Xurkitree e Celesteela passarem —
duas UBs que se mantêm vivas uma pela outra; o jogador vence a sua, a outra a
revive, a Lillie entende o porquê e pede gelo ao Pryce: uma parede de gelo
separa as duas e a segunda luta é para valer. O Necrozma absorve as duas e some;
a Lillie reconhece aquela luz de Alola e não diz mais nada. O Pryce volta para
o Ginásio.

**Decisões desta missão:**
- Elenco: **Looker, Anabel, Lillie (+ Alolan Ninetales), Pryce (+ Mamoswine)**,
  dois moradores (velho + menino) e o **Necrozma**.
- Local: `Mahoganytown`, rua sul, entre o Pokémon Center e o Ginásio.
- **Duas batalhas seguidas contra a mesma UB** (a escolhida): rodada 1 curta
  (2 barras), rodada 2 no alvo da escala (4 barras / Lv80 / x130). A Anabel cura
  o time entre as duas.
- Mesma estrutura padrão: escolha + boss simples, captura bloqueada, derrota =
  blackout e retry — agora da cena inteira, as duas rodadas.

---

## 0. Resumo do fluxo

```text
Blackthorn resolvido                     VAR_RIFT_MISSIONS_STATE = 4
  └─ entrar em OlivineCity_House1 ─────▶ cena: Looker + Anabel, briefing M2 → 5
                                           + setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
                                           (briefing NÃO cita Lillie nem evacuação)
       └─ Mahogany: portas trancadas (menos o Centro); na rua só o elenco:
          Looker, Anabel, Lillie + Ninetales (descoberta), Pryce + Mamoswine
          e os dois últimos moradores na porta do Ginásio
            └─ falar com Looker ▶ Lillie expõe a leitura dela ▶ SIM
                 └─ cena 100% scriptada:
                    Pryce leva os moradores para dentro ▶ Necrozma chega ▶ Blizzard sem efeito
                    ▶ fenda: Xurkitree + Celesteela ▶ a sinergia na tela ▶ Celesteela avança
                    no jogador, Ninetales o salva
                      └─ ESCOLHA: qual você enfrenta? Lillie + Ninetales ficam com a outra
                           └─ RODADA 1: boss 2 barras, Lv80, x130
                                ├─ perdeu / desistiu → blackout → Centro → recomeça do SIM
                                ├─ outro             → reset silencioso → recomeça
                                └─ venceu → a outra UB REVIVE a derrotada pela sinergia
                                     └─ Lillie bola o plano; Anabel cura o time;
                                        Ninetales + Mamoswine erguem a parede de gelo
                                          └─ RODADA 2: boss 4 barras, Lv80, x130
                                               ├─ perdeu / desistiu / outro → idem acima
                                               └─ venceu → Necrozma ABSORVE as duas e some
                                                    → reações; Pryce entra no Ginásio
                                                    → gancho sem destino
                                                    → clearflag + estado 6 → warp no lugar
                                     └─ Olivine House1: briefing da Missão 3 revela Cherrygrove
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_ULTRABEAST_MAHOGANY` | `include/constants/flags.h` | `0x1042` | Primeira livre depois de `FLAG_NO_CATCHING` (0x1041). **Atualizar `CUSTOM_FLAGS_END`** para apontar nela (hoje aponta para `FLAG_NO_CATCHING`, `flags.h:1776`). |
| `LOCALID_MAHOGANY_UB_*` | `include/constants/map_event_ids.h` | 10-20 | **Gerado** pelo `mapjson` a partir do campo `local_id` do `map.json` (não editar à mão). 10-15 na rev. 2; 16-20 (Necrozma, Pryce, Mamoswine, velho, menino) na rev. 3. |

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
| `Mahoganytown` | `FLAG_TEMP_3` | Os dois últimos moradores (velho, menino) — visíveis com o incidente; a cena os faz entrar no Ginásio (rev. 3) |
| `Mahoganytown` | `FLAG_TEMP_4` | Necrozma — sempre escondido no load; só a cena o traz (rev. 3) |
| `Mahoganytown` | `FLAG_TEMP_5` | Pryce + Mamoswine — visíveis com o incidente; entram no Ginásio no fim (rev. 3) |
| `Mahoganytown` | `VAR_TEMP_2` | Resultado da batalha (as duas rodadas) |
| `Mahoganytown` | `VAR_TEMP_3` | Escolha do jogador: 0 = Xurkitree, 1 = Celesteela. Vale para as **duas** rodadas da tentativa. Sobrevive às batalhas (voltar da batalha não passa por `LoadMapFromWarp`) |
| `Mahoganytown` | `VAR_TEMP_4` | Espécie da família Cosmog a que o Necrozma reagiu (`SPECIES_NONE` = sem reação); relida na conversa final (rev. 3) |

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
| **5** | "Anabel: Go on. Mr. Pryce does not strike me as a man who calls for help lightly." (rev. 3: a Lillie saiu daqui — ela é descoberta em Mahogany) |
| **≥ 6** | "Anabel: Rest. Looker will brief you on Cherrygrove." |

Ordem dos `goto_if_eq`: 2, 3, 4, 5, depois `goto_if_ge ... 6`, e o `msgbox` de
férias como default. **Não** deixar nenhum `goto_if_ge ... 4` sobrando do código
atual: ele engoliria os estados 5 e 6.

Todos os ramos continuam terminando em `OlivineCity_House1_EventScript_ReleaseEnd`.

> `Text_BriefingM2` — **final (rev. 3)**. Cita a ligação do Pryce e o apagão,
> e mais nada: a Lillie, a evacuação (fala do próprio Pryce) e o Necrozma são o
> que o jogador encontra em Mahogany.
> Looker: {PLAYER}! Your timing is uncanny. It has started again. Mahogany Town.
> Anabel: Two signatures again. One electrical. One… heavy.
> Looker: The town lost its power three nights ago. Every lamp, every machine. Only the Pokémon Center still has light.
> Anabel: The readings come from the town itself. Every night, at the same hour. No sign of the light from Blackthorn. Not yet.
> Looker: The Gym Leader, Pryce, telephoned us himself. He said four words. “Lights out. Come now.” …I have decided to find that reassuring.
> Anabel: Meet us by the Pokémon Center, {PLAYER}. Prepare for two of them. Not one.

"No sign of the light from Blackthorn. Not yet." é a promessa que a cena quebra:
o Necrozma aparece em Mahogany.

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
Porta do Centro (21,19) livre durante todo o evento. **Rev. 3:** Ginásio, Shop
e House1 ficam trancados (§3.1.1); Valor Cavern (33,19) e o gate da Route 43
(14,4) continuam acessíveis.

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

### 3.1.1 Portas trancadas (rev. 3, pedido do autor: "igual Blackthorn")

Com a flag do evento setada, **toda porta de prédio de Mahogany recusa o
jogador, menos a do Pokémon Center**. Mesmo mecanismo da M1 (§5.2 daquele doc):
uma linha a mais em `sLockedTownDoors` (`src/field_control_avatar.c`):

```c
{ FLAG_EVENT_ULTRABEAST_MAHOGANY,   MAP_MAHOGANYTOWN,    MAP_MAHOGANY_TOWN_POKEMON_CENTER,   Mahoganytown_EventScript_DoorLocked },
```

e o `extern` em `include/event_scripts.h`. Fala: "The door is locked tight. A
note is taped to it, stiff with frost: “Everyone is safe. This door stays shut
until I say so. --Pryce”".

Portas afetadas (comportamento `0x69`, porta animada): Ginásio (10,19), Shop
(15,10), House1 (27,10). **Não afetadas** (comportamento `0x60`, porta não
animada — `MetatileBehavior_IsWarpDoor` só aceita a animada): o **gate da Route
43** (14,4) e a **Valor Cavern** (33,19). Medido no `metatile_attributes.bin`
dos dois tilesets, não suposto. Isso é o desejado: o gate é saída de rota, não
casa, e a caverna segue a regra "entrada de caverna fica aberta".

A trava dura o tempo da flag: o `clearflag` da vitória destranca tudo. É também
o que dá sentido ao Pryce entrar no Ginásio no fim: a porta abre para ele
(`opendoor`) e a trava cai logo depois com a flag.

### 3.2 Objetos — `object_events` 10-20

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 10 | `LOCALID_MAHOGANY_UB_NINETALES` | `OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)` | (19,22) | `FACE_UP` | `NULL` | `FLAG_TEMP_1` |
| 11 | `LOCALID_MAHOGANY_UB_LILLIE` | `OBJ_EVENT_GFX_LILLIE` | (20,22) | `FACE_UP` | `Mahoganytown_EventScript_UBLillie` | `FLAG_TEMP_1` |
| 12 | `LOCALID_MAHOGANY_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (21,22) | `FACE_UP` | `Mahoganytown_EventScript_UBLooker` | `FLAG_TEMP_1` |
| 13 | `LOCALID_MAHOGANY_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (22,22) | `FACE_UP` | `Mahoganytown_EventScript_UBAnabel` | `FLAG_TEMP_1` |
| 14 | `LOCALID_MAHOGANY_UB_XURKITREE` | `OBJ_EVENT_GFX_SPECIES(XURKITREE)` | **(12,20)** | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 15 | `LOCALID_MAHOGANY_UB_CELESTEELA` | `OBJ_EVENT_GFX_SPECIES(CELESTEELA)` | **(12,22)** | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 16 | `LOCALID_MAHOGANY_UB_NECROZMA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA)` | (11,21) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_4` |
| 17 | `LOCALID_MAHOGANY_UB_PRYCE` | `OBJ_EVENT_GFX_PRYCE` | (11,20) | `FACE_LEFT` | `Mahoganytown_EventScript_UBPryce` | `FLAG_TEMP_5` |
| 18 | `LOCALID_MAHOGANY_UB_MAMOSWINE` | `OBJ_EVENT_GFX_SPECIES(MAMOSWINE)` | (11,21) | `FACE_LEFT` | `Mahoganytown_EventScript_UBMamoswine` | `FLAG_TEMP_5` |
| 19 | `LOCALID_MAHOGANY_UB_OLD_MAN` | `OBJ_EVENT_GFX_OLD_MAN_1` | (10,20) | `FACE_RIGHT` | `Mahoganytown_EventScript_UBOldMan` | `FLAG_TEMP_3` |
| 20 | `LOCALID_MAHOGANY_UB_BOY` | `OBJ_EVENT_GFX_LITTLE_BOY` | (10,21) | `FACE_UP` | `Mahoganytown_EventScript_UBBoy` | `FLAG_TEMP_3` |

- Negrito = mudou na rev. 3 (as UBs saíram de (13,21)/(13,22) para flanquear o
  Necrozma com um tile livre entre elas — (12,21) —, onde fica a parede de gelo).
  16-20 são **novos, no fim**; nenhum local id anterior mudou.
- `map_event_ids.h` é **gerado** pelo `mapjson` a partir do `local_id` (a §3.2
  antiga mandava editar à mão; corrigido, como na M1).
- Necrozma e Mamoswine dividem (11,21) no `map.json`: o Necrozma está sempre
  escondido no load e só é adicionado depois que o Mamoswine saiu dali.
- O velho fica em (10,20), o tile do Fat man vanilla (local 4,
  `FLAG_HIDE_MAHOGANY_TOWN_FATMAN`, setada para sempre em `RocketHideout_B2F`).
- `OBJ_EVENT_GFX_OLD_MAN_1` e `LITTLE_BOY` usam a paleta `NPC_4`, a mesma da
  Anabel: nenhuma paleta nova para os moradores.
- Conferido: `MAMOSWINE` tem bloco `OVERWORLD(` (`gen_2_families.h`, 32x32);
  `NECROZMA` já é usado em Blackthorn; `OBJ_EVENT_GFX_PRYCE` existe (Ginásio,
  Lake of Rage).
- **Orçamento:** jogador + follower + 11 = **13/16**. Paletas na tela: jogador,
  follower, Lillie, Looker, NPC_4, Pryce, Ninetales, Xurkitree, Celesteela,
  Necrozma, Mamoswine = **11**, o mesmo número de Blackthorn (validado).
- 20 templates < limite de 64.

Looker e Anabel ficam em Olivine **e** aqui durante o estado 5 — aceito pelo
autor, o evento inteiro é cutscene (design §5). Ver §9.

### 3.3 Visibilidade — `ON_TRANSITION`

```asm
Mahoganytown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2          @ UBs: sempre escondidas no load
	setflag FLAG_TEMP_4          @ Necrozma: sempre escondido no load
	goto_if_unset FLAG_EVENT_ULTRABEAST_MAHOGANY, Mahoganytown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1        @ elenco
	clearflag FLAG_TEMP_3        @ os dois moradores
	clearflag FLAG_TEMP_5        @ Pryce + Mamoswine
	return
Mahoganytown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	return
```

Roda também ao entrar pela borda (Route 42, 44) e pelo gate da Route 43.
Retry depois de blackout: moradores, Pryce e Mamoswine voltam à porta do
Ginásio; UBs e Necrozma voltam escondidos. A cena inteira se repete.

### 3.4 Planta da cena (dump real, bit 11; `#` = bloqueado)

`python3 .claude/skills/encenar-cutscene/dump_mapa.py Mahoganytown`

```text
       x= 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23
  y=19     #  W  #  #  .  .  .  .  .  .  #  #  W  #  #   W (10,19) Ginásio, (21,19) Centro
  y=20     .  O  P  X  >  >  .  .  .  .  .  .  f  .  .   f (21,20) pouso do Fly
  y=21     .  B  M  :  >  n  N  L  .  .  .  .  t  .  .   t (21,21) ÚNICO tile para falar com Looker
  y=22     .  .  .  C  >  >  *  .  .  n  L  K  A  .  .   * (17,22) posição do jogador
  y=23     #  #  #  #  #  #  #  #  #  #  #  #  #  #  #

  Antes da cena: O velho (10,20)  B menino (10,21)  P Pryce (11,20)  M Mamoswine (11,21)
                 n Ninetales (19,22)  L Lillie (20,22)  K Looker (21,22)  A Anabel (22,22)
  Na cena:       Pryce -> (14,20), Mamoswine -> (13,21) (linha de frente)
                 Ninetales -> (15,21) -> (14,21) na parede; Lillie -> (16,21)
                 Necrozma aparece em (11,21); X Xurkitree (12,20), C Celesteela (12,22)
                 ':' (12,21) = o vão entre as duas, onde a parede de gelo sobe
```

Câmera com o jogador em (17,22): x 10..24, y ~18..27. A porta do Ginásio
(10,19) está na tela — a evacuação e a saída do Pryce acontecem à vista.
**Ninguém fica ao sul do jogador** em nenhum momento.

O Looker continua no bolso (21,22) — início determinístico sem `getplayerxy`.
O Pryce só é alcançável de (12,20) antes da cena ((11,19) é parede, (10,20) o
velho, (11,21) o Mamoswine).

### 3.5 Conversas antes da cena

| Objeto | Script | Comportamento |
|---|---|---|
| Anabel | `UBAnabel` | `faceplayer`; o Centro tem gerador próprio, "a única luz da cidade"; cure-se lá e fale com o Looker. |
| Lillie | `UBLillie` | **A descoberta.** "{PLAYER}?! You're the Champion they've been waiting for? …Of course you are." Veio ver Johto por conta própria, as luzes apagaram, observa há dois dias; prefere explicar a todos de uma vez. **Com família Cosmog:** Ninetales dá "!" primeiro; Cosmog — "keeps looking up at the sky. Nebby used to do that. Right before something went wrong."; Cosmoem — "gone so still. Nebby went still like that, once."; Solgaleo/Lunala — "hasn't taken its eyes off the west end of town… I think it already knows." Termina com `turnobject ... DIR_NORTH`. |
| Pryce | `UBPryce` | **Sem** `faceplayer` (está ocupado evacuando). "Every soul in Mahogany is under my Gym tonight. Every soul but this one." — o velho recusa largar a lamparina; o Pryce manda o jogador ao detetive. **Com família Cosmog:** "That {species} of yours is shivering in its ball. It isn't the cold. I would know." |
| Mamoswine | `UBMamoswine` | Grito + "standing guard beside Pryce, still as ice." |
| Velho | `UBOldMan` | Sessenta anos acendendo a lamparina da varanda; não vai se esconder. Volta a olhar para o Pryce (leste). |
| Menino | `UBBoy` | "Grandpa says the monster only eats electricity. …It doesn't eat Pokémon too, does it?" Volta a olhar para o avô (norte). |

Nenhuma muda estado.

---

## 4. Etapa C — A cena (100% scriptada a partir do SIM)

### 4.1 Pré-checagens (`Mahoganytown_EventScript_UBLooker`)

Igual à rev. 2: `UBLookerGreet` → `UBLillieTheory` → `UBReady` (SIM/NÃO). Nenhum
estado muda antes do SIM; sem presente, sem checagem de espaço.

- `UBLookerGreet` — o Looker apresenta a Lillie ao jogador com humor ("yes,
  before you ask. That is a young lady with a notebook"); ela chegou antes de
  todos; o Pryce pediu que ela saísse, duas vezes, e ela agradeceu educadamente
  as duas vezes.
- `UBLillieTheory` — a Lillie expõe o que viu: duas UBs, mesma fenda, mesma hora;
  **"First there's a light. Then the tear. Then them."** (semente do Necrozma); uma
  puxa a eletricidade, a outra queima e devolve. A Anabel nomeia ("A closed
  loop"); o Looker duvida ("a great deal to conclude from one notebook"); a Lillie
  sustenta ("Two nights of notes. Same order. Same hour."), a Anabel confirma com
  os instrumentos. O plano dela: **separar as duas.** Ela ainda não sabe que isso
  não basta — é o que a cena ensina.
- `UBReady` — "Then we do it her way. Once it opens, there is no stepping back."

### 4.2 A cena (`Mahoganytown_EventScript_UBScene`)

1. **Aproximação** — idêntica à rev. 2 e com a mesma ordem obrigatória:
   Lillie/Ninetales → jogador → Looker/Anabel.
2. **A evacuação, na tela.** Lillie: "Mr. Pryce! It's almost time!" O velho vira
   para o Pryce; `UBPryceEvacuates` ("You heard her, Hector. Inside." — "Sixty
   years, Pryce." — "Then don't make tonight the night I lose you over it. You'll
   light it tomorrow. Take the boy."). `opendoor 10,19`; velho (10,20)→(10,19),
   `set_invisible`, `removeobject`; depois o menino (10,21)→(10,20)→(10,19) —
   **sequencial**, ele pisa no tile que o velho deixa. `closedoor`.
3. **O Pryce assume a linha de frente.** Pryce (11,20)→(14,20) e Mamoswine
   (11,21)→(13,21), linhas diferentes, juntos. Pryce vira para o leste (jogador
   em (17,22): dx=+3 domina) e diz **ele mesmo** que evacuou ("That's the last of
   them. Mahogany is empty. … I moved every family into my Gym myself."), se
   apresenta ao Campeão e se recusa a entrar. Volta para o oeste.
4. **A ameaça chega.** Lillie: "There! The light!" → tremor → flash →
   `clearflag FLAG_TEMP_4` + `addobject` Necrozma em (11,21) → grito → "!" em
   Lillie, Pryce, Looker e Anabel → `UBNecrozmaArrives`: Looker o reconhece de
   Blackthorn; Anabel conclui que ele **abre** as fendas; a Lillie reconhece a
   luz ("No, no, no. I know that light." — "Not now. Please."); Pryce: "Mamoswine!
   Blizzard!"
5. **A autoridade local tenta e falha.** Mamoswine `walk_in_place_fast_left` ×2
   + grito → flash → Necrozma pulsa → `UBNoEffect` ("Not even frost on it. Fifty
   years."; Looker: "In Blackthorn it was the same").
6. **Escalada.** Grito do Necrozma → tremor → flash → Xurkitree (12,20) e
   Celesteela (12,22) → gritos → `UBAppear` (Anabel: "Rift opening!" + a **semente
   de Faller**, "I felt that one before the readings moved. Never mind. Later.";
   Looker nomeia as duas, como na rev. 2 — são UBs catalogadas, não o mistério).
7. **A sinergia, mostrada antes de explicada.** Xurkitree pulsa (drena), pulsa
   para baixo (manda a corrente), flash, Celesteela pulsa para cima (recebe) com
   grito → `UBSynergy` (narração + Anabel: "Energy passing between the two
   signatures. Both ways." + Lillie: "One drinks, the other burns. Together they
   never run dry.").
8. **Perigo direto ao jogador.** Looker: "The heavy one! It is coming at you!" →
   Celesteela `walk_fast_right` ×3, (12,22)→(15,22), dois tiles do jogador. O
   Ninetales, logo acima em (15,21), ataca para baixo + grito → tremor → flash →
   Celesteela é **jogada de volta** a (12,22) de costas (`lock_facing_direction`).
   `UBSaved`: Lillie ("Ninetales, Icy Wind! Keep it away from {PLAYER}!"), e o
   Pryce aprova ("That one's got a good cold in her.").

### 4.3 A escolha

Igual à rev. 2 (`dynmultichoice ... TRUE ...`, `VAR_TEMP_3`, "!" na escolhida).
Todos já olham certo: jogador (17,22), Lillie (16,21) e Ninetales (15,21) a
leste das duas UBs em x=12, que olham para o leste. O `UBChoosePrompt` inclui o
Pryce ("And I'll watch the crystal one. For whatever good it does."). A escolha
vale para as **duas** rodadas.

### 4.4 Duas batalhas seguidas (pedido do autor)

| | Rodada 1 | Rodada 2 |
|---|---|---|
| `setbossbattle` | **2 barras**, x130, sem perfil | **4 barras**, x130, sem perfil |
| Xurkitree | Lv80, Magnet, Tail Glow / Thunderbolt / Energy Ball / Dazzling Gleam | idem |
| Celesteela | Lv80, Leftovers, Heavy Slam / Flamethrower / Earthquake / Air Slash | idem |
| Entre as rodadas | — | a Anabel cura o time (`special HealPlayerParty` + `MUS_HEAL`) |

- A rodada 1 é **curta de propósito**: precisa parecer vitória para a virada
  funcionar. A rodada 2 é o alvo da escala do design (M2 = 4 / Lv80 / x130).
- `B_FLAG_NO_CATCHING` é setada antes de **cada** rodada (a engine limpa no fim
  de toda batalha). `B_FLAG_NO_WHITEOUT` em nenhuma.
- Ordem das macros igual à rev. 2 e à de `bosslegendaryencounterwithmoves`.
- **Se o playtest disser parede:** rodada 1 → 1 barra; x130 → 120 nas duas;
  rodada 2 → 3 barras; tirar o item; só então o nível. Um parafuso por vez.

Resultados (as duas rodadas têm o mesmo tratamento):

| Resultado | O que acontece |
|---|---|
| `B_OUTCOME_WON` na rodada 1 | §4.5 (a virada) |
| `B_OUTCOME_WON` na rodada 2 | §5 |
| `LOST` / `DREW` / `FORFEITED` ("Run" no boss) | Blackout → Centro de Mahogany; o script não continua |
| `CAUGHT` / `RAN` / outro (inalcançáveis) | `UBUnresolved`: fala + `warpsilent` (21,20) → recomeça |

**Retry:** nada é salvo entre as rodadas. Perder na rodada 2 recomeça a cena
inteira, rodada 1 inclusive (a escolha também). Aceito: a rodada 1 é curta. Se o
runtime mostrar que isso cansa, a saída exige estado novo (um `VAR_TEMP` não
sobrevive ao blackout) — decisão do autor, não de quem evoluir.

### 4.5 A virada: a sinergia revive a derrotada (`UBRevived` / `UBLilliePlan`)

1. `UBDown<escolhida>` — a Lillie comemora e se corta ("It's down! … It's--
   …Wait. Celesteela!").
2. A parceira **manda** (pulsa na direção da derrotada: Celesteela para cima,
   Xurkitree para baixo), flash, a derrotada **recebe** (pulsa de volta) com
   grito → `UBRevived<escolhida>` (narração: a derrotada se levanta inteira).
3. "!" em Lillie, Pryce, Looker e Anabel → `UBLilliePlan`: Looker ("Impossible!
   We had it!"), Anabel ("Whatever one loses, the other gives back."), Pryce
   ("Like melting a glacier with a match."), e a Lillie **admite o erro e
   refaz o plano** ("…I was wrong. Splitting them isn't enough. The current
   still jumps the gap. So we close the gap. … Ice doesn't carry current. Mr.
   Pryce, can Mamoswine make ice?" — "Can it make ice. …Girl, you are standing
   in Mahogany.").
4. **Cuidado antes da luta:** Anabel (22,21)→(22,22)→(18,22), ao lado do jogador
   (linha 22 vazia desde a aproximação); o jogador vira para ela; fade → cura →
   fanfarra → "There. Every one of them, ready. Now finish it." A Anabel fica em
   (18,22) até o fim.
5. **A parede.** Ninetales (15,21)→(14,21), ao lado do Mamoswine (13,21). Lillie:
   "Ninetales, Aurora Veil! Right between them!"; Pryce: "Mamoswine. Freeze it
   solid." Os dois atacam para o oeste, no vão (12,21) → gritos → tremor → flash.
   As UBs tentam de novo (pulsam uma para a outra) → `UBWallHolds`: "The current
   crackled against it… and died." — "This time it stays down!"

A sinergia **nossa** (Lillie + Pryce, gelo de dois Pokémon) vence a sinergia
**deles**. É a leitura do tema da missão (design §3.2: observar, explicar,
sustentar — e aqui também corrigir o próprio plano diante do grupo).

---

## 5. Etapa D — Absorção, reações e gancho

### 5.1 Absorção pelo Necrozma (`UBResolved` / `UBAbsorb`) — padrão de todas as missões

1. Fala da Lillie conforme a escolha (a luta dela é narrativa): a UB dela "kept
   reaching for the other one. There was nothing left to reach" / "Ice doesn't
   give anything back."
2. Necrozma pulsa + grito. As duas UBs são **arrastadas de costas** um tile até
   ele: (12,20)→(11,20) e (12,22)→(11,22).
3. Tremor → flash → `removeobject` das duas (`FLAG_TEMP_2`) → grito.
4. "!" em Pryce, Lillie, Looker e Anabel → `UBAbsorbed`: Pryce ("It's…
   swallowing them."), Looker ("Again! Just as in Blackthorn."), Anabel ("It
   opened the tear, let them feed for three nights… and now it collects them."),
   Lillie ("It's feeding. The same way it did before." — Looker: "Before?
   Mademoiselle, before WHEN?" — "…Later. I promise.").
5. §5.2 (opcional).
6. Tremor → flash → `removeobject` do Necrozma (`FLAG_TEMP_4`, própria) →
   `UBNecrozmaGone` (Pryce: "…Gone."; Looker: as lâmpadas voltando).

**Ninguém o nomeia.** Looker e Anabel: "the creature from Blackthorn". Pryce nunca
o viu. A Lillie **reconhece** (continuidade USUM) e se recusa a falar na rua — o
mesmo corte do Gladion em Blackthorn ("In Alola." — "Later."). Os dois irmãos
sabem; nenhum dos dois conta ainda. O nome fica para a reunião de Olivine.

### 5.2 Reação opcional à família Cosmog (`UBNecrozmaSensesCosmog`)

Idêntica em mecânica à M1 §6.6: `CheckMysteryEggPokemon` → `VAR_TEMP_4`,
checado **depois** das batalhas. Necrozma dá um passo para o jogador,
(11,21)→(12,21) (o vão, vazio); "!" no jogador; grito.
- Cosmog/Cosmoem: encara a Poké Ball, o Pokémon treme; **Lillie**: "No! Not that
  one! Ninetales, stay by {PLAYER}!" (na M1 era o Gladion com o Silvally).
- Solgaleo/Lunala: a luz se acende entre os dois; ele recua e encara.
- Na conversa final, bloco extra: Lillie ("It looked at your {species}. Only at
  it. Promise me you'll keep it close.") + Anabel ("In Blackthorn, and now here.
  It keeps finding one."); ou, com a lendária, Lillie ("I've never seen that
  light back away from anything.") + Anabel.

Pré-cena, sem estado: Lillie (três falas, uma por estágio, lembrando o Nebby
sem chamar o Pokémon do jogador de Nebby) e Pryce (§3.5).

### 5.3 Conversa, Pryce volta ao Ginásio, gancho

```text
Looker (21,21) → (18,21) olhando oeste. Anabel já está em (18,22).
turnobject: Pryce, Mamoswine e Ninetales → leste; Lillie → sul. Jogador → leste.
```

1. `UBAftermath`: Looker pergunta primeiro se alguém se feriu ("the report can
   wait a moment"); Pryce ("more winters than the three of you put together…
   Not one like this, though."); Anabel ("Twice now. That is not chance. That is
   a pattern."); Looker cobra a Lillie; ela promete contar tudo, "not in the
   middle of the street. Not tonight."; Looker: "Waiting is also detective work."
2. Bloco Cosmog/lendária se `VAR_TEMP_4` ≠ `SPECIES_NONE` (§5.2).
3. **Pryce volta para o seu povo** (pedido do autor). Jogador vira para o oeste;
   `UBPryceGoodbye` (Mahogany deve uma noite de luz ao Campeão; elogia a Lillie
   — "clear thinking with a storm in your face. Winter would approve."; "And
   Hector can light his blasted lamp."). `opendoor 10,19`; Pryce
   (14,20)→(10,20)→(10,19), some; **depois** o Mamoswine (13,21)→(10,21)→(10,20)
   →(10,19), some (sequencial: os dois últimos tiles dele são os do Pryce).
   `closedoor`.
4. Jogador → leste. `UBHook` — **sem destino**: Anabel pede as anotações da
   Lillie; Lillie fica mais uns dias "in case it comes back"; Anabel: "It will
   open another rift. Where, and when, we don't know yet."; Looker: "So we keep
   watching. Rest, {PLAYER}. Then come back to our house in Olivine. The moment
   something opens, you will be the first to know."; Lillie agradece por ouvirem
   o plano dela — "Both of them. Even the wrong one."
5. `FADE_TO_BLACK` → `clearflag FLAG_EVENT_ULTRABEAST_MAHOGANY` + `setvar
   VAR_RIFT_MISSIONS_STATE, 6` → `warpsilent MAP_MAHOGANYTOWN, 17, 22` →
   `waitstate` → `releaseall` → `end`. A cidade repovoa, o elenco some, as portas
   destrancam, o follower volta.

**Continuidade corrigida junto:** o briefing da M3 abria com "Cherrygrove at
last", apoiado no gancho antigo que citava Cherrygrove e Kukui. Agora abre com
"It has opened again. Cherrygrove City." — o briefing é quem revela o lugar.

---

## 6. Arquivos tocados

| Arquivo | Rev. 2 (esqueleto) | Rev. 3 (história) |
|---|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_MAHOGANY 0x1042` + comentário; `CUSTOM_FLAGS_END` | — |
| `include/constants/map_event_ids.h` | (gerado) | (gerado) locais 16-20 |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho de dois estados, despachante, ramos 4/5/≥6 | `Text_BriefingM2` final (sem Lillie, sem evacuação, com a ligação do Pryce); `Text_AnabelGoAheadM2` sem a Lillie; `Text_BriefingM3` abre revelando Cherrygrove |
| `data/maps/Mahoganytown/map.json` | flag do evento em 8 moradores; locais 10-15 | UBs para (12,20)/(12,22); locais 16-20 (Necrozma, Pryce, Mamoswine, velho, menino) |
| `data/maps/Mahoganytown/scripts.inc` | visibilidade + seção da Missão 2 | visibilidade com `FLAG_TEMP_3..5`; seção da Missão 2 **reescrita** (cena, duas rodadas, absorção, reações, falas finais) |
| `src/field_control_avatar.c` | — | linha de Mahogany em `sLockedTownDoors` |
| `include/event_scripts.h` | — | `extern Mahoganytown_EventScript_DoorLocked` |

Não editar `events.inc`/`header.inc`/`connections.inc` nem o `.inc` gerado de
`OlivineCity_House1`. Validar com `make -j$(nproc)`.

---

## 7. O que ainda é simples × evolução

Rev. 3 apagou todos os `@ SKELETON:` de falas de Mahogany. O único que sobra na
seção é o da coreografia (topo de `UBScene`):
`grep -rn "SKELETON:" data/maps/Mahoganytown`.

| Item | Hoje | Evolução possível |
|---|---|---|
| Golpes, fenda, parede de gelo | Tremor + flash; Pokémon só andam no lugar | Animações de golpe (field effects), sprite de portal, metatile de gelo com `setmetatile` no vão (12,21) |
| Apagão | Só dito nas falas | Paleta escura na cidade durante o incidente, lâmpadas voltando no fim |
| Música | `MUS_DP_VS_LEGEND` nas duas rodadas | Tema próprio do Necrozma na chegada |
| Moradores depois do evento | Voltam como eram | O velho acendendo a lamparina; o vendedor de Rage Candy Bar comentando |
| Rodada 1 no retry | Refeita junto com a 2 | Só com estado novo; decisão do autor (§4.4) |
| Beast Balls | Pendentes desde a M1 | Design §5 |

**O que NÃO pode regredir numa evolução:** a máquina de estados §1.2, a
invariante flag ⇔ estado 5, a visibilidade por template, o SIM como único ponto
de saída, a escolha refeita a cada tentativa e válida para as duas rodadas, o
tratamento de todos os resultados **nas duas rodadas**, a proibição de captura
(setada antes de cada rodada), a regra de que `VAR_TEMP_0`/`VAR_TEMP_1` são do
vendedor, a surpresa da Lillie (nada antes da cena a cita), o gancho sem
destino e ninguém nomeando o Necrozma.

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
- **(Rev. 3) A ordem da evacuação e da saída do Pryce é sequencial.** O menino
  pisa no tile que o velho deixa; o Mamoswine usa os dois últimos tiles do
  Pryce. Juntar qualquer par num só `waitmovement` faz um tentar entrar no tile
  do outro no mesmo tick.
- **(Rev. 3) O vão (12,21) precisa ficar vazio.** É onde a parede "fica" e onde o
  Necrozma dá o passo da reação ao Cosmog. Nenhum ator pode terminar ali.
- **(Rev. 3) `B_FLAG_NO_CATCHING` antes de cada rodada.** A engine a limpa ao fim
  da rodada 1; tirar o segundo `setflag` libera a bola na rodada 2.
- **(Rev. 3) A Anabel mora em (18,22) da cura em diante.** A conversa final não a
  move de novo; mover a cura para outro ponto exige refazer §5.3.
- **O despachante `BriefingTalk` de Olivine agora serve duas missões.** Um
  `goto_if_ge VAR_RIFT_MISSIONS_STATE, 4` sobrando em qualquer ramo de Looker ou
  Anabel engole os estados 5 e 6.

---

## 9. Pendências e riscos conhecidos

- **Looker e Anabel em dois lugares no estado 5: aceito pelo autor** (mesma
  decisão da M1). Não esconder em Olivine.
- **Duas rodadas de x130 seguidas.** A rodada 1 tem 2 barras e há cura entre
  elas, mas nada disso foi jogado. Caminho de redução em §4.4.
- **Retry refaz as duas rodadas.** Perder na rodada 2 custa a rodada 1 de novo.
  Sem estado novo não há como pular (§4.4).
- **Cura no meio da cutscene** (`special HealPlayerParty` sob `FADE_TO_BLACK`)
  é inédita nas Rift Missions; o runtime confirma que a fanfarra não briga com a
  música do mapa.
- **`opendoor`/`closedoor` com a trava ativa:** a animação é só de metatile e
  não passa por `TryLockedDoorScript`; confirmar em runtime que o velho, o menino
  e o Pryce "entram" pela porta sem glitch visual.
- **O velho em (10,20)** depende de `FLAG_HIDE_MAHOGANY_TOWN_FATMAN` continuar
  setada no pós-game (§3.2). Se alguma revisão voltar a mostrar o Fat man, os
  dois disputam o tile.
- **O Fat man (10,20) não é tocado.** Conflito de duas flags num só campo já tem
  solução aprovada no doc da M3 §3.1.1, se um dia for preciso.
- Money loss no blackout/desistência é o padrão da engine; aceito pelo design.
- **Beast Balls continuam pendentes** desde a M1 (design §5).

---

## 10. Teste em runtime

- [ ] Estado 4: a cena de chegada em Olivine dá o briefing da M2 **sem** citar a Lillie nem a evacuação; cita a ligação do Pryce. Estado vira 5.
- [ ] Estado 5 em Olivine: Anabel fala do Pryce, não da Lillie.
- [ ] Estado 5 em Mahogany (chegar por Fly, Route 42, gate da Route 43 e Route 44): moradores vanilla ausentes; Looker, Anabel, Lillie + Ninetales, Pryce + Mamoswine, velho e menino presentes; UBs e Necrozma ausentes.
- [ ] Portas: Ginásio, Shop e House1 recusam com o bilhete do Pryce; Centro abre; gate da Route 43 e Valor Cavern abrem.
- [ ] Conversas antes da cena (Lillie surpresa, Pryce ocupado, velho, menino, Mamoswine, Anabel), com e sem família Cosmog; cada um volta a olhar para onde olhava.
- [ ] (21,21) continua sendo o único tile para falar com o Looker.
- [ ] SIM: aproximação sem sobreposição; velho e menino entram no Ginásio pela porta animada; Pryce e Mamoswine vão para (14,20)/(13,21) sem atravessar ninguém.
- [ ] Necrozma aparece em (11,21) com "!" nos quatro; Blizzard sem efeito; fenda com as UBs em (12,20)/(12,22); a sinergia lê como troca de energia.
- [ ] Celesteela avança até (15,22) e é jogada de volta a (12,22) pelo Ninetales.
- [ ] Menu da escolha não fecha com B.
- [ ] Rodada 1 (2 barras) → a outra UB revive a derrotada → "!" → plano da Lillie → Anabel anda até (18,22) e cura (time cheio de HP/PP depois) → Ninetales vai a (14,21) → parede → rodada 2 (4 barras) contra a **mesma** UB. Testar as duas escolhas.
- [ ] Bolsa: bola bloqueada nas **duas** rodadas. "Run": desistência → blackout.
- [ ] Perder na rodada 1 **e** na rodada 2 de propósito: acorda no Centro de Mahogany; tudo volta ao estado de antes do SIM (moradores e Pryce na porta do Ginásio).
- [ ] Vencer: absorção (UBs arrastadas até o Necrozma), "!" nos quatro, reação ao Cosmog (se houver), Necrozma some, Looker se aproxima, Pryce e Mamoswine entram no Ginásio, gancho sem destino, fade, cidade repovoada, portas destrancadas, follower de volta.
- [ ] Estado 6: briefing da M3 em Olivine começa com "It has opened again. Cherrygrove City."
- [ ] Vendedor de Rage Candy Bar continua funcionando depois do evento.
- [ ] Salvar/recarregar em cada estado (4, 5, 6).
- [ ] Regressão da M1: Blackthorn povoada e destrancada em todos os estados ≥ 4.

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

## 12. Feedback da implementação da revisão 2 (19/09/2026) — histórico

Registro do esqueleto. Onde contradiz §3–§5 (posições das UBs, falas, uma
batalha só), vale a revisão 3.

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

---

## 13. Revisão 3 — a história (22/09/2026)

Feedback do autor sobre o esqueleto: "o esqueleto está pronto, agora vamos
montar uma história épica". Feito com a skill `evoluir-historia-de-evento`,
tendo a M1 revisão 3 como modelo. O que foi pedido e como ficou:

| Pedido | Como ficou |
|---|---|
| História épica; a vibe é boa, falta história | Arco completo (§4.2–§5.3): a cidade já em movimento (evacuação), a autoridade local tenta e falha (Blizzard), escalada (fenda), perigo ao jogador (Celesteela avança, Ninetales salva), a virada (revive), o plano, a vitória de verdade, a consequência inesperada (absorção), reações, cuidado (Looker pergunta pelas pessoas; Anabel cura), gancho. |
| Diálogos naturais, pela personalidade | Todas as falas reescritas pela voz do design §3.1: Looker teatral que se corrige e pergunta primeiro pelas pessoas; Anabel precisa (nomeia o loop, conclui que o Necrozma abre as fendas, "That is a pattern"); Lillie educada, específica, sustenta e **corrige** o próprio plano; Pryce seco, paciente, fala em inverno. Nenhum `@ SKELETON:` de fala sobrou. |
| Trancar todas as portas como em Blackthorn | §3.1.1: uma linha em `sLockedTownDoors`, bilhete do Pryce. O gate da Route 43 e a Valor Cavern ficam abertos — são porta não animada, medido no tileset. |
| A Lillie estar na cidade é descoberta, não aviso | Tirada do `BriefingM2` e do "vá na frente" da Anabel em Olivine; `grep` confirma que nenhum texto antes da cena a cita. A fala dela ao ser encontrada é de surpresa ("{PLAYER}?! You're the Champion they've been waiting for?"). |
| O Pryce aparece evacuando e é ele quem diz que evacuou; talvez depois entra no Ginásio | Objetos 17-20. Antes da cena ele discute com o último morador na porta do Ginásio; na cena leva o velho e o menino para dentro (porta animada), diz "I moved every family into my Gym myself", e no fim volta para o Ginásio com o Mamoswine. O briefing não fala de evacuação. |
| Reforçar a sinergia das UBs; virar padrão | A sinergia é **mostrada** (pulsos + flash) antes de explicada, **vence** a rodada 1 (revive) e é **derrotada** por outra sinergia (Lillie + Pryce, gelo). Regra comum no design §6. |
| Pryce luta com o Necrozma | Mamoswine usa Blizzard na chegada, sem efeito (passo "autoridade local tenta e falha", como a Clair). Ele fica "de olho na criatura de cristal" durante a luta e depois empresta o gelo para a parede. |
| Lutar 2× seguidas; a sinergia os recupera; a Lillie percebe e bola a estratégia | §4.4–§4.5: rodada 1 (2 barras) → a parceira revive a derrotada → a Lillie admite que separar não basta, "Ice doesn't carry current" → parede de gelo no vão entre as duas → a Anabel cura → rodada 2 (4 barras). |
| Na segunda vocês derrotam de verdade | A parede corta a troca na tela ("The current crackled against it… and died") antes da rodada 2; depois dela, a fala da Lillie confirma que a UB dela também caiu sem ter a quem recorrer. |
| O Necrozma absorve os dois e desaparece | §5.1, mesmo padrão da M1 (arrasto de costas, flash, some). |
| Personagens espantados com o Necrozma | "!" nos quatro na **chegada** e na **absorção**; falas próprias em `UBNecrozmaArrives`, `UBAbsorbed` e `UBAftermath`. A Lillie reconhece a luz de Alola e não diz mais — o eco do Gladion na M1. |
| Reação opcional do Necrozma e dos NPCs ao Cosmog | §5.2 (Necrozma + Lillie/Anabel depois da batalha) e §3.5 (Lillie e Pryce antes). Sem estado. |
| Absorção em todos os encontros | Já era regra comum (V19); agora M1 e M2 cumprem. |
| Não dizer onde é o próximo evento | `UBHook` sem destino ("volte a Olivine, a gente avisa"). O `BriefingM3` deixou de dizer "Cherrygrove at last" e passou a revelar o lugar. |

**Ambiguidades resolvidas por escrito:**
- "Pryce lutará com Necrozma novamente" — lido como "igual à Clair na M1": um
  golpe na chegada que não faz efeito. Ele não batalha com o jogador.
- "Talvez depois entrar na Gym" — feito no fim, depois da absorção: é o líder
  voltando para o povo que ele guardou.
- Dificuldade de duas lutas seguidas: a rodada 1 ficou curta (2 barras) para
  parecer vitória; a rodada 2 é o alvo da escala (4 / Lv80 / x130); a Anabel cura
  entre elas (cuidado antes do relatório, e evita que a rodada 2 vire parede
  por desgaste).
- A Lillie conhecer o Necrozma: coerente com a continuidade USUM do design
  §3.1; ela **reconhece** sem nomear, como o Gladion.

**Conferido:** `make -j$(nproc)` limpo; local ids 10-15 intactos, 16-20 no fim
(`map_event_ids.h` gerado); todos os 19 caminhos da cena simulados contra a
colisão (bit 11) e livres; nenhum par de atores disputa tile no mesmo passo
(os pares simultâneos andam em linhas diferentes; os que dividem tiles são
sequenciais); larguras de linha dentro do máximo já usado em Blackthorn;
nenhuma ocorrência de "Lillie" em Olivine antes da cena.

**Runtime:** pendente — §10. Maiores riscos: o equilíbrio de duas rodadas de
x130, a cura sob fade no meio da cutscene, e as portas animadas abrindo com a
trava ativa.
