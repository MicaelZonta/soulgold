# Blackthorn — Buzzwole + Pheromosa (Rift Mission 1) — plano de implementação ESQUELETO

**Status:** **esqueleto implementado**, `make -j$(nproc)` limpo. Runtime pendente (§11).
Revisão 2 — 19/09/2026; implementado em 19/09/2026.
**Modo:** esqueleto (skill `evento-esqueleto`). Diálogo curto, coreografia mínima,
mas estado, visibilidade, gatilhos, batalha e retry **completos e corretos**.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6 (V14).
**Missão seguinte:** [`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) — continua a var nos estados 4→5→6 e substitui o stub da Missão 2 deixado em `OlivineCity_House1` (§4.4).

Escopo: da ligação do Looker após o Hall of Fame até o fim do incidente de
Blackthorn, terminando com o gancho que manda o jogador de volta a Olivine para
a Missão 2 (Xurkitree + Celesteela, Mahogany, Lillie).

**Mudanças da revisão 2:**
- Looker sai da Route 29. Looker e Anabel moram em `OlivineCity_House1` **desde o começo do jogo, sem flag**; `VAR_RIFT_MISSIONS_STATE` só troca o diálogo e dispara a cena.
- Ligação do Elm e do Looker uma após a outra: aprovado.
- Batalha: o jogador **escolhe** Buzzwole ou Pheromosa; Gladion + Silvally enfrentam a outra. Estrutura padrão de todas as missões.
- A luta do jogador usa o **sistema de boss** do projeto (`setbossbattle`).

---

## 0. Resumo do fluxo

```text
New Game ─ Looker + Anabel já estão em OlivineCity_House1 (diálogo "de férias")
Hall of Fame (1ª vez)                  VAR_RIFT_MISSIONS_STATE = 1
  └─ sair de casa em New Bark ───────▶ ligação do Elm, depois do Looker    → 2
       └─ entrar em OlivineCity_House1 ▶ cena: Looker + Anabel, briefing  → 3  + setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
            └─ Blackthorn: cidade vazia (só Looker, Anabel, Gladion, Silvally)
                 └─ falar com Looker ▶ SIM ▶ cena 100% scriptada ▶ ruptura: Buzzwole + Pheromosa
                      └─ ESCOLHA: qual você enfrenta? Gladion + Silvally ficam com a outra
                           └─ boss battle simples contra a escolhida
                                ├─ perdeu / desistiu → blackout → Centro de Blackthorn (Joy) → flag setada → recomeça
                                ├─ outro             → reset silencioso → recomeça
                                └─ venceu            → fala do Gladion conforme a escolha → gancho
                                                       → clearflag + estado 4 → warp no lugar (cidade repovoa)
                                     └─ Olivine House1: stub da Missão 2
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `VAR_RIFT_MISSIONS_STATE` | `include/constants/vars.h` | `0x4120` | Primeira livre depois de `VAR_MOM_FURFROU_EXP` (0x411F). `VARS_END` = 0x42FF. Nenhum uso de `0x4120`. |
| `FLAG_EVENT_ULTRABEAST_BLACKTHORN` | `include/constants/flags.h` | `0x1040` | Bloco custom, logo após `FLAG_GLADION_VICTORY_ROAD_DONE` (0x103F, ainda não commitado — confirmar). Atualizar `CUSTOM_FLAGS_END`. |
| `FLAG_NO_CATCHING` | `include/constants/flags.h` | `0x1041` | Para `B_FLAG_NO_CATCHING`. |
| `B_FLAG_NO_CATCHING` | `include/config/battle.h:259` | `0` → `FLAG_NO_CATCHING` | Mesmo padrão de `B_FLAG_NO_WHITEOUT FLAG_NO_WHITEOUT` (linha 266). |

`FLAG_NO_CATCHING` é **flag de batalha**: a engine a limpa sozinha ao fim de toda
batalha (`Overworld_ResetBattleFlagsAndVars`, `src/overworld.c:425-441`). Setar
imediatamente antes da batalha. Reaproveitada por todas as Rift Missions.

**Não é preciso bloquear fuga.** Em boss battle, "Run" é desistência explícita
(`CanPlayerForfeitBattle`, `src/battle_main.c:6688`): o resultado é
`B_OUTCOME_FORFEITED`, que conta como derrota → blackout → retry. `B_FLAG_NO_RUNNING`
nem é consultado em boss (`src/battle_util.c:739`). Por isso não há `FLAG_NO_RUNNING`.

Comentário obrigatório acima de cada `#define` novo (padrão de
`FLAG_HIDE_CIANWOOD_GLADION`): quem seta, quem limpa, onde.

### 1.2 Máquina de estados `VAR_RIFT_MISSIONS_STATE`

| Valor | Significado | Quem escreve | Quem lê |
|---|---|---|---|
| 0 | Antes do primeiro Hall of Fame | — (New Game) | Olivine House1 (diálogo "de férias") |
| 1 | Liga vencida; ligação do Looker pendente | `PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags` | `NewBarkTown_OnFrame`; Olivine House1 (mesmo diálogo do 0) |
| 2 | Ligação recebida; ir a Olivine | `NewBarkTown_EventScript_LookerCall` | Olivine House1 (cena de chegada + briefing) |
| 3 | Briefing feito; incidente de Blackthorn **ativo** | `OlivineCity_House1_EventScript_Briefing` | Olivine House1 ("vá na frente") |
| 4 | Blackthorn resolvido; briefing da Missão 2 pendente | `BlackthornCity_EventScript_UBResolved` | Olivine House1 (stub da Missão 2) |
| 5+ | Reservado para as próximas missões | próximos docs | — |

**Invariante:** `FLAG_EVENT_ULTRABEAST_BLACKTHORN` setada ⇔ `VAR_RIFT_MISSIONS_STATE == 3`.
As duas mudam **juntas, no mesmo script** (Olivine seta, Blackthorn limpa). A flag
existe só porque o campo `flag` do `map.json` não lê var — é ela que esconde a
cidade. A var é a autoridade da história.

Nenhuma outra flag/var persistente. A escolha do jogador (qual UB enfrentar) é
temporária: numa nova tentativa ele escolhe de novo.

### 1.3 Temporários por mapa

| Mapa | Temp | Uso |
|---|---|---|
| `OlivineCity_House1` | `VAR_TEMP_1` | Trava uma-vez-por-visita do gatilho de frame |
| `BlackthornCity` | `FLAG_TEMP_1` | Cache de visibilidade do elenco (Looker, Anabel, Gladion, Silvally) |
| `BlackthornCity` | `FLAG_TEMP_2` | Cache das Ultra Beasts (sempre escondidas até a cena) |
| `BlackthornCity` | `VAR_TEMP_2` | Resultado da batalha |
| `BlackthornCity` | `VAR_TEMP_3` | Escolha do jogador: 0 = Buzzwole, 1 = Pheromosa. Sobrevive à batalha (voltar da batalha não recarrega o mapa, mesmo padrão de `ReceptionGate`). |

Conferido: nenhum `FLAG_TEMP`/`VAR_TEMP` em `BlackthornCity/scripts.inc` nem em
`OlivineCity_House1/scripts.pory`. Reconfirmar antes de implementar:
`grep -rn "FLAG_TEMP_[12]\b\|VAR_TEMP_[123]\b" data/maps/BlackthornCity data/maps/OlivineCity_House1 data/scripts/`.

---

## 2. Etapa A — Tirar o Looker da Route 29

`Route29` tem `.pory` → editar só `data/maps/Route29/scripts.pory` e o `map.json`.

1. `Route29/map.json`: apagar o objeto 2 (`OBJ_EVENT_GFX_LOOKER`, (37,14), `Route29_EventScript_Looker`).
2. `Route29/scripts.pory`: apagar `Route29_EventScript_Looker` (linha ~162) e `Route29_Text_Looker` (linha ~270).

Apagar do meio da lista renumera os local ids 3-17 → 2-16. **Seguro aqui**, conferido:
- nenhum script da Route 29 usa local id (só `OBJ_EVENT_ID_CAMERA`/`OBJ_EVENT_ID_PLAYER`);
- nenhum `LOCALID_ROUTE29_*` em `map_event_ids.h`, nenhum objeto com `local_id` nomeado;
- árvore de Cut usa `VAR_LAST_TALKED`; berry tree usa o próprio id, não o local id.

Reconfirmar com `grep -rn "MAP_ROUTE29" data/ src/ | grep -i "object\|localid"` antes.
Observação: o Looker estava no mesmo tile (37,14) que a `FR_LASS` (objeto 9); a remoção
também desfaz essa sobreposição.

---

## 3. Etapa B — Ligação do Looker (New Bark)

### 3.1 Hall of Fame

`data/maps/PokemonLeague_HallOfFame/scripts.inc` (sem `.pory`), em
`PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags` (linha ~58), junto dos
outros `setvar`:

```asm
	setvar VAR_RIFT_MISSIONS_STATE, 1
```

Só a primeira vitória passa por esse bloco; revanches não reativam a ligação.

### 3.2 Gatilho em New Bark

Após o HoF, `special GameClear` leva o jogador a `NewBarkTown_PlayersHouse_1F`.
"Sair de casa" = primeiro frame em `NewBarkTown`, onde já existe a cadeia pós-Liga.

`data/maps/NewBarkTown/scripts.pory`, bloco `raw`:

```asm
NewBarkTown_OnFrame::
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
	map_script_2 VAR_RIFT_MISSIONS_STATE, 1, NewBarkTown_EventScript_LookerCall   @ NOVO
	map_script_2 VAR_NEWBARK_TOWN_STATE, 11, NewBarkTown_EventScript_ArcherArcadeCall
	...
```

A tabela dispara a **primeira** entrada verdadeira por frame: Elm (6 → 7) primeiro,
Looker no frame seguinte — uma ligação após a outra, como aprovado. A condição
`== 1` não congela o jogo porque a primeira instrução do script muda a var
(skill `visibilidade-e-gatilhos` §4).

```asm
NewBarkTown_EventScript_LookerCall::
	setvar VAR_RIFT_MISSIONS_STATE, 2          @ primeira instrução: para de disparar
	lock
	pokenavcall NewBarkTown_Text_LookerCall
	waitmessage
	delay 30
	release
	end
```

Texto (inglês, placeholder — caixas de ~34 colunas):

> Looker: Hello? Is this {PLAYER}, the new Champion of Johto?
> My name is Looker. International Police. You may have seen me in Olivine... on holiday.
> The holiday is over. Strange creatures have been appearing in Johto. Creatures that should not be here.
> I would very much like your help. Please come to our house in Olivine City — the one on the north side, closest to the Gym.

(Casa: `OlivineCity` warp 4 → `OlivineCity_House1` em (27,24); das três casas da rua
norte (x=27, 31, 36) é a mais próxima do Ginásio em (11,27).)

---

## 4. Etapa C — Olivine: casa do Looker e da Anabel

### 4.1 Mover o NPC da troca do Voltorb para `OlivineCity_House3` (7,4)

Hoje: `OlivineCity_House1/map.json` objeto 1 = `OBJ_EVENT_GFX_ENGINEER` (4,4),
`script: Olivine_VoltorbTrade`, `flag: 0`; script em `OlivineCity_House1/scripts.pory`.

1. `OlivineCity_House3/map.json`: **anexar no fim** de `object_events` (vira local id 2):
   ```json
   {
     "graphics_id": "OBJ_EVENT_GFX_ENGINEER",
     "x": 7, "y": 4, "elevation": 0,
     "movement_type": "MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT",
     "movement_range_x": 0, "movement_range_y": 0,
     "trainer_type": "TRAINER_TYPE_NONE",
     "trainer_sight_or_berry_tree_id": "0",
     "script": "Olivine_VoltorbTrade",
     "flag": "0"
   }
   ```
   (7,4) é chão, à direita da mesa (5-6,4-5). O Fisher (4,4) continua como local id 1.
2. Mover `Olivine_VoltorbTrade`, `VoltorbTrade_Declined`, `VoltorbTrade_NotRequested`
   e os três textos para `OlivineCity_House3/scripts.inc` (House3 **não tem** `.pory`).
   Copiar a tradução asm já gerada em `OlivineCity_House1/scripts.inc`, sem as linhas `# N "..."`.
3. Apagar esses scripts do `OlivineCity_House1/scripts.pory`.
4. Remover o objeto do engenheiro do `OlivineCity_House1/map.json`.

`FLAG_OLIVINE_NPC_TRADE_COMPLETED` continua sendo o estado da troca.

### 4.2 Objetos de `OlivineCity_House1` — sempre presentes

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 1 | `LOCALID_OLIVINE_HOUSE1_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (4,5) | `MOVEMENT_TYPE_FACE_DOWN` | `OlivineCity_House1_EventScript_Looker` | `0` |
| 2 | `LOCALID_OLIVINE_HOUSE1_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (7,5) | `MOVEMENT_TYPE_FACE_DOWN` | `OlivineCity_House1_EventScript_Anabel` | `0` |

Sem flag: estão na casa do New Game em diante. **Nunca usar `removeobject` neles**: com
flag 0 eles voltariam no primeiro passo do jogador (a câmera respawna objetos de flag
limpa). Saídas de cena são feitas andando de volta ao lugar.

Adicionar as duas linhas em `include/constants/map_event_ids.h` à mão, sob
`// MAP_OLIVINE_CITY_HOUSE1` (skill `batalha-sem-blackout`, seção `local_id`).

Planta (`dump_mapa.py OlivineCity_House1`, y cresce para baixo):

```text
      x= 0 1 2 3 4 5 6 7 8 9 10
  y=2    . . . . . . . . . . .
  y=3    . . . . . . . . . . .
  y=4    . . . . . # # . . . .      mesa (5-6,4-5)
  y=5    . . . . L # # A . . .      L = Looker (4,5)   A = Anabel (7,5)
  y=6    . . . . . . . . . . .
  y=7    . . . . . . . . . . .
  y=8    # . . . W . . . . .        W = entrada (4,8): o jogador nasce aqui, olhando para cima
```

### 4.3 Scripts de mapa (`OlivineCity_House1/scripts.pory`, bloco `raw`)

Sem `ON_TRANSITION`: não há visibilidade a calcular. Só o gatilho de chegada.

```asm
OlivineCity_House1_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_House1_OnFrame
	.byte 0

OlivineCity_House1_OnFrame::
	map_script_2 VAR_TEMP_1, 0, OlivineCity_House1_EventScript_BriefingTrigger
	.2byte 0

@ Dispara uma vez por visita (VAR_TEMP_1 zera a cada load). Só encena no
@ estado 2 e só se o jogador acabou de entrar pela porta; fora disso, o
@ briefing roda pelo script de objeto do Looker, sem coreografia.
OlivineCity_House1_EventScript_BriefingTrigger::
	setvar VAR_TEMP_1, 1                        @ primeira instrução
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_End
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 4, OlivineCity_House1_EventScript_End
	goto_if_ne VAR_0x8005, 8, OlivineCity_House1_EventScript_End
	lockall
	hidefollower
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
	@ Looker (4,5)->(4,6)->(4,7), olha para baixo (jogador em (4,8)).
	@ Anabel (7,5)->(7,6)->(7,7)->(6,7)->(5,7), olha para baixo.
	@ Caminhos sem tile em comum -> andam juntos.
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
	call OlivineCity_House1_EventScript_BriefingTalk
	@ Volta: caminhos inversos, também disjuntos.
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerReturn
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelReturn
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
	releaseall
	end

OlivineCity_House1_EventScript_End::
	end

OlivineCity_House1_Movement_LookerApproach:  walk_down, walk_down, face_down, step_end
OlivineCity_House1_Movement_AnabelApproach:  walk_down, walk_down, walk_left, walk_left, face_down, step_end
OlivineCity_House1_Movement_LookerReturn:    walk_up, walk_up, face_down, step_end
OlivineCity_House1_Movement_AnabelReturn:    walk_right, walk_right, walk_up, walk_up, face_down, step_end

@ Comum à cena e ao script de objeto. Muda o estado no fim.
OlivineCity_House1_EventScript_BriefingTalk::
	msgbox ... (textos abaixo)
	closemessage
	setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN     @ invariante: flag e var juntas
	setvar VAR_RIFT_MISSIONS_STATE, 3
	return
```

Textos do briefing (inglês, placeholder):

> Looker: Ah, {PLAYER}! You came. Allow me to introduce myself properly: Looker, International Police.
> And this is my Chief, Anabel. The holiday was... a cover.
> Anabel: Thank you for coming, Champion.
> Looker: Creatures from beyond Ultra Wormholes have been sighted in Johto. We call them Ultra Beasts.
> Anabel: Two of them were reported in Blackthorn City. The residents are staying indoors.
> Looker: A young Trainer named Gladion is already there, keeping watch.
> Anabel: We leave at once. Meet us by the Pokémon Center in Blackthorn. And prepare well — these are not ordinary Pokémon.

### 4.4 Scripts de objeto — diálogo por estado

`OlivineCity_House1_EventScript_Looker` (`lock`, `faceplayer`, ramifica por `VAR_RIFT_MISSIONS_STATE`):

| Estado | Fala (placeholder) |
|---|---|
| 0-1 | "Looker: Hm? Oh, pay no attention to moi. I am simply... on holiday. Yes. A holiday by the sea." |
| 2 | `call OlivineCity_House1_EventScript_BriefingTalk` (sem coreografia) |
| 3 | "Looker: Blackthorn, {PLAYER}! We are leaving right behind you!" |
| ≥ 4 | **Stub da Missão 2:** "Looker: We are still confirming reports from Mahogany Town. Come back soon, {PLAYER}!" — substituído pelo doc da Missão 2. |

`OlivineCity_House1_EventScript_Anabel`:

| Estado | Fala (placeholder) |
|---|---|
| 0-1 | "Anabel: Looker insists we are on vacation. He has been reading the same newspaper for three days." |
| 2 | `call OlivineCity_House1_EventScript_BriefingTalk` |
| 3 | "Anabel: Go on ahead. We'll be there before you reach the Pokémon Center." |
| ≥ 4 | "Anabel: Rest while you can. Looker will brief you on the next report." |

(Venda de Beast Balls entra depois, ver §9.)

---

## 5. Etapa D — Blackthorn: cidade vazia

### 5.1 Esconder a cidade

`BlackthornCity/map.json`: trocar `"flag": "0"` por
`"flag": "FLAG_EVENT_ULTRABEAST_BLACKTHORN"` em todos os NPCs e Pokémon ambientes:

| Local id | Objeto | (x,y) |
|---|---|---|
| 1 | Youngster | (16,28) |
| 2 | Boy (Gym boy) | (25,27) |
| 3 | Fat man (Santos) | (27,39) |
| 4 | Cooltrainer F | (44,31) |
| 5 | Battle Girl | (12,40) |
| 6 | Black Belt | (33,44) |
| 7 | Sage (`LOCALID_BLACKTHORN_SAGE`) | (25,13) |
| 8-15 | OW Dragonair, Graveler ×2, Gligar, Ursaring, Donphan, Horsea ×2 | vários |
| 27 | Fisherman (Super Rod) | (11,52) |

**Não mexer:** 16 (item ball, `FLAG_BLACKTHORN_ADRENALINE_ORB`) e 17-26 (light sprites,
`FLAG_NIGHT_POKEMON`). Nunca `removeobject` nesses objetos (setaria a flag do evento).

**A Joy continua:** está em `BlackthornCity_PokemonCenter` (outro mapa), que não é
tocado. Porta do Centro (27,48) livre durante todo o evento. Ginásio, Mart e casas
continuam acessíveis — só o exterior esvazia.

### 5.2 Elenco — anexar no fim de `object_events` (locais 28-33)

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 28 | `LOCALID_BLACKTHORN_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (25,53) | `FACE_UP` | `BlackthornCity_EventScript_UBLooker` | `FLAG_TEMP_1` |
| 29 | `LOCALID_BLACKTHORN_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (26,53) | `FACE_UP` | `BlackthornCity_EventScript_UBAnabel` | `FLAG_TEMP_1` |
| 30 | `LOCALID_BLACKTHORN_UB_GLADION` | `OBJ_EVENT_GFX_GLADION` | (20,49) | `FACE_LEFT` | `BlackthornCity_EventScript_UBGladion` | `FLAG_TEMP_1` |
| 31 | `LOCALID_BLACKTHORN_UB_SILVALLY` | `OBJ_EVENT_GFX_SPECIES(SILVALLY)` | (19,49) | `FACE_LEFT` | `NULL` | `FLAG_TEMP_1` |
| 32 | `LOCALID_BLACKTHORN_UB_BUZZWOLE` | `OBJ_EVENT_GFX_SPECIES(BUZZWOLE)` | (16,50) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 33 | `LOCALID_BLACKTHORN_UB_PHEROMOSA` | `OBJ_EVENT_GFX_SPECIES(PHEROMOSA)` | (16,49) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |

- Todos com `movement_range 0`, `TRAINER_TYPE_NONE`.
- Buzzwole e Pheromosa têm `overworld.png` e bloco `OVERWORLD(`; Silvally já é usado em `ReceptionGate`.
- Linhas novas em `map_event_ids.h` sob `// MAP_BLACKTHORN_CITY`, à mão.
- 33 templates < limite de 64.

Looker e Anabel ficam em Olivine **e** aqui durante o estado 3 — aceito pelo autor, o
evento inteiro é cutscene. Ver §10.

### 5.3 Visibilidade — `ON_TRANSITION`

`BlackthornCity/scripts.inc` (sem `.pory`). Em `BlackthornCity_EventScript_CityEnter`
(o `ON_TRANSITION` atual), adicionar `call BlackthornCity_EventScript_ApplyUBVisibility`:

```asm
@ Elenco (FLAG_TEMP_1) visível só com o incidente ativo. Ultra Beasts
@ (FLAG_TEMP_2) sempre escondidas no load: só a cena as faz aparecer.
@ Temps zeram a cada load (ClearTempFieldEventData), então recalcula sempre.
BlackthornCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	goto_if_unset FLAG_EVENT_ULTRABEAST_BLACKTHORN, BlackthornCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	return
BlackthornCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	return
```

Roda também ao entrar pela borda (Route 44/45), não só por warp.

### 5.4 Planta da cena (dump real, bit 11; `#` = bloqueado)

```text
       x= 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
  y=48     #  #  #  #  #  .  .  .  .  .  #  #  #  W  #     W (27,48) = porta do Pokémon Center
  y=49     .  .  P  .  .  S  G  .  .  .  .  .  .  f  .     f (27,49) = pouso do Fly / saída do Centro
  y=50     .  .  B  .  .  .  *  .  .  .  .  .  .  .  .     * (20,50) = posição de combate do jogador
  y=51     .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
  y=52     .  #  .  .  #  #  .  .  .  #  #  t  a  .  .     t (25,52) = ÚNICO tile para falar com Looker
  y=53     #  #  #  #  #  #  .  .  .  #  #  L  A  #  #     a (26,52) = único tile para falar com Anabel
  y=54     .  .  .  #  #  #  .  .  .  #  #  #  #  #  #

  L Looker (25,53)   A Anabel (26,53)   G Gladion (20,49)   S Silvally (19,49)
  B Buzzwole (16,50) P Pheromosa (16,49)   — B/P escondidos até a cena
```

O Looker fica no "bolso" (25,53): (24,53) e (25,54) são parede e (26,53) é a Anabel.
**Só dá para falar com ele de (25,52), olhando para baixo.** Isso torna o início da
cena determinístico sem `getplayerxy`. Documentar num comentário `@` acima do script.

### 5.5 Conversas antes da cena

- `BlackthornCity_EventScript_UBAnabel` (`lock`, `faceplayer`):
  "Anabel: Looker has the details. Speak with him when you're ready."
- `BlackthornCity_EventScript_UBGladion` (`lock`, `faceplayer`):
  "Gladion: ...You're the Champion now? Good. Talk to Looker. Silvally and I are watching the west road."
  Depois `turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_WEST`.

---

## 6. Etapa E — A cena (100% scriptada a partir do SIM)

### 6.1 Pré-checagens (`BlackthornCity_EventScript_UBLooker`)

```asm
BlackthornCity_EventScript_UBLooker::
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox BlackthornCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBNotReady
	goto BlackthornCity_EventScript_UBScene
```

- `UBNotReady`: "Looker: Of course. The Pokémon Center is right behind us. I will be here." → `release`, `end`.
- Nenhum estado muda antes do SIM. O SIM é o último ponto de saída.
- Não é preciso checar quantidade de Pokémon: a batalha é simples (a revisão 1 exigia 2 por ser dupla).

> `UBLookerGreet` — Looker: {PLAYER}! Good. The street is clear, the residents are safe indoors. The readings are strongest to the west.
> `UBReady` — Looker: Once we begin, there is no stopping halfway. Are your Pokémon ready?

### 6.2 Ruptura

```asm
BlackthornCity_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	@ Jogador (25,52) -> (25,51) -> (25,50) -> (24..20,50), olha para oeste.
	applymovement OBJ_EVENT_ID_PLAYER, BlackthornCity_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Looker (25,53)->(25,52), Anabel (26,53)->(26,52): mesma sequência, colunas
	@ diferentes, sem cruzamento -> juntos. Ambos terminam olhando para oeste.
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_StepUpFaceLeft
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_StepUpFaceLeft
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	msgbox BlackthornCity_Text_UBGladionBrief, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1          @ vertical pan
	setvar VAR_0x8005, 1          @ horizontal pan
	setvar VAR_0x8006, 20         @ num shakes
	setvar VAR_0x8007, 6          @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_BLACKTHORN_UB_BUZZWOLE
	addobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox BlackthornCity_Text_UBAppear, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBChoose

BlackthornCity_Movement_PlayerToLine:
	walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, walk_left, face_left, step_end
BlackthornCity_Movement_StepUpFaceLeft:
	walk_up, face_left, step_end
```

Conferido tile a tile (bit 11): (25,51), (25,50), (24..20,50) livres; ninguém no caminho
(Gladion/Silvally estão na linha 49). Com o jogador em (20,50) a câmera cobre x 13..27,
y ~46..55: UBs, Gladion, Looker e Anabel ficam na tela.

> `UBGladionBrief` — Gladion: You're here. Something tore the air open over there a minute ago.
> Anabel: Looker, keep the doors shut. I'll watch the Center.
> `UBAppear` — Looker: Two of them! Buzzwole and Pheromosa!

### 6.3 A escolha — estrutura padrão de todas as missões

O jogador escolhe qual Ultra Beast enfrenta. O acompanhante da missão enfrenta a outra.
Sem opção de cancelar (`ignoreBPress = TRUE`): a cena já começou.

```asm
BlackthornCity_EventScript_UBChoose::
	msgbox BlackthornCity_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, BlackthornCity_Text_ChoiceBuzzwole, BlackthornCity_Text_ChoicePheromosa
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Buzzwole, 1 = Pheromosa
	closemessage
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBPickPheromosa
	@ Buzzwole: ela reage ao jogador; Gladion/Silvally já olham para oeste (Pheromosa em (16,49)).
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	msgbox BlackthornCity_Text_UBPickedBuzzwole, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBBattle
BlackthornCity_EventScript_UBPickPheromosa::
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	msgbox BlackthornCity_Text_UBPickedPheromosa, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBBattle
```

Modelo de menu: `GoldenrodCity_RadioTower_2F/scripts.inc:222`. Direções: todos os atores
já estão virados para o oeste e as UBs para o leste, qualquer que seja a escolha — o
jogador em (20,50) e o Gladion em (20,49) estão a leste das duas. Nenhum `turnobject` é
necessário.

> `UBChoosePrompt` — Gladion: We split them. Pick one, {PLAYER}. Silvally and I take the other.
> `ChoiceBuzzwole` — "Buzzwole" · `ChoicePheromosa` — "Pheromosa"
> `UBPickedBuzzwole` — Gladion: The big one's yours, then. Silvally — the fast one!
> `UBPickedPheromosa` — Gladion: Fine. Silvally, we hold the big one. Don't let it near the houses!

### 6.4 Batalha — boss simples

Sistema de boss do projeto (`src/battle_boss.c`, macros em `asm/macros/event.inc:2193-2245`):
barras de HP múltiplas, IA inteligente automática (`IsWildMonSmart`), "Run" vira
desistência. Só existe em batalha **simples** — batalha dupla cancela a configuração de
boss (`InitBossBattleData`). Por isso a escolha também resolve a limitação do engine.

Usa as mesmas peças de `bosslegendaryencounter`, mas sem esconder objeto por captura
(captura está bloqueada) e com tratamento próprio dos resultados:

```asm
BlackthornCity_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                   @ design: sem captura antecipada em Blackthorn
	@ B_FLAG_NO_WHITEOUT NÃO é setado: perder = blackout (batalha de ameaça).
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBSetupPheromosa
	setbossbattle 2, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_BUZZWOLE, 70
	goto BlackthornCity_EventScript_UBStartBattle
BlackthornCity_EventScript_UBSetupPheromosa::
	setbossbattle 2, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_PHEROMOSA, 70
BlackthornCity_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, BlackthornCity_EventScript_UBResolved
	goto BlackthornCity_EventScript_UBUnresolved
```

- `setbossbattle` antes de `seteventmon`, na mesma ordem das macros existentes. Nenhum
  caminho sai do script entre os dois, então não é preciso `clearbossbattle`.
- 2 barras, multiplicador 110, sem perfil de fases (Buzzwole/Pheromosa não têm Mega nem
  perfil; `autoMega` não encontra nada e segue normal). Nível 70 (referência: Rayquaza e
  Genesect bosses usam 70; Lance/E4 ~68-70).
- Música: `BattleSetup_StartLegendaryBattle` cai no `default` → `MUS_DP_VS_LEGEND`.
- Golpes: os de nível do `learnset` (sem `seteventmonmoves` no esqueleto).

Resultados (`IsPlayerDefeated`, `src/battle_setup.c:1107`; `CB2_EndScriptedWildBattle`, `:679`):

| Resultado | O que acontece | Por quê |
|---|---|---|
| `B_OUTCOME_WON` | Continua para §7 | A UB escolhida desmaiou |
| `LOST` / `DREW` | **Blackout** → Centro de Blackthorn (Joy) | `CB2_WhiteOut`; `BlackthornCity_OnLoad` faz `setrespawn HEAL_LOCATION_BLACKTHORN_CITY` |
| `FORFEITED` (o jogador escolheu "Run" no boss) | **Blackout**, igual à derrota | Boss transforma fuga em desistência (`HandleEndTurn_RanFromBattle`, `src/battle_main.c:5893`) |
| `CAUGHT` / `RAN` / outro | `UBUnresolved`: reset da cena | Inalcançáveis (bola bloqueada; fuga vira FORFEITED), tratados por segurança. Nunca viram vitória. |

**Retry:** nada foi salvo como concluído. A flag do evento continua setada; ao sair do
Centro a cidade continua vazia, o elenco volta às posições do `map.json` e as UBs voltam
a ficar escondidas. Falar com o Looker recomeça do §6.1 — **inclusive a escolha**, que
pode ser outra.

```asm
BlackthornCity_EventScript_UBUnresolved::
	msgbox BlackthornCity_Text_UBGotAway, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_BLACKTHORN_CITY, 27, 49       @ recarrega: elenco no lugar, UBs escondidas
	waitstate
```

> `UBGotAway` — Looker: They slipped back through the rift... It is not over. Regroup, and we try again.

---

## 7. Etapa F — Resolução e gancho

A luta do Gladion contra a outra UB é **narrativa**: não há batalha para ela. Ela se
resolve junto com a vitória do jogador, e a fala do Gladion muda conforme a escolha.

```asm
BlackthornCity_EventScript_UBResolved::
	@ Os dois objetos continuam no mapa após a batalha (não há recarga).
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_BUZZWOLE      @ flag = FLAG_TEMP_2: seguro
	removeobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreen FADE_FROM_WHITE
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBGladionFoughtBuzzwole
	msgbox BlackthornCity_Text_UBGladionFoughtPheromosa, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBAfterBattle
BlackthornCity_EventScript_UBGladionFoughtBuzzwole::
	msgbox BlackthornCity_Text_UBGladionFoughtBuzzwole, MSGBOX_DEFAULT
BlackthornCity_EventScript_UBAfterBattle::
	msgbox BlackthornCity_Text_UBAfterGladion, MSGBOX_DEFAULT
	closemessage
	@ Looker (25,52)->(25,51)->(25,50)->(24..21,50), olha oeste (jogador em (20,50)).
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_LookerToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	@ Anabel (26,52)->(26,51)->(25..22,51), olha oeste. SEQUENCIAL: o caminho dela
	@ passa por (25,51), que o Looker ocupa no passo 1 -> nunca andar juntos.
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_AnabelToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight   @ data/scripts/movement.inc:46
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_SOUTH             @ jogador (20,50) está abaixo
	msgbox BlackthornCity_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_BLACKTHORN   @ invariante: flag e var juntas
	setvar VAR_RIFT_MISSIONS_STATE, 4
	warpsilent MAP_BLACKTHORN_CITY, 20, 50       @ recarrega no lugar: cidade repovoa,
	waitstate                                    @ elenco some pelo ON_TRANSITION

BlackthornCity_Movement_LookerToPlayer:
	walk_up, walk_up, walk_left, walk_left, walk_left, walk_left, face_left, step_end
BlackthornCity_Movement_AnabelToPlayer:
	walk_up, walk_left, walk_left, walk_left, walk_left, face_left, step_end
```

Posições finais: jogador (20,50) → leste; Looker (21,50) → oeste; Anabel (22,51) → oeste;
Gladion (20,49) → sul; Silvally (19,49) → oeste. Anabel fica uma linha abaixo do jogador:
visível acima da caixa de texto.

Por que `warpsilent` no lugar: com a flag limpa, os NPCs escondidos só voltariam quando a
câmera andasse, surgindo do nada. Recarregar faz o `ON_TRANSITION` esconder o elenco e
spawnar a cidade de uma vez, sob o fade. Gladion e Silvally somem juntos, como pede
`parceiro-pokemon-de-npc`.

Textos (inglês, placeholder) — **o último bloco é o gancho para Olivine**:

> `UBGladionFoughtPheromosa` (jogador escolheu Buzzwole) — Gladion: Pheromosa was fast. Silvally was faster.
> `UBGladionFoughtBuzzwole` (jogador escolheu Pheromosa) — Gladion: That Buzzwole hit like a wall. Silvally didn't give it an inch.
> `UBAfterGladion` — Gladion: ...They're gone. Back through wherever they came from. You held your side. Good.
>
> `UBHook` — Looker: Magnificent work, both of you! And no one was hurt. That is what matters most.
> Anabel: This was not a single incident. The rift closed, but the readings did not stop.
> Looker: While you were fighting, our office received another report. Strange lights over the Lake of Rage, near Mahogany Town.
> Anabel: Rest first, {PLAYER}. When you're ready, come back to our house in Olivine. We'll brief you there.
> Gladion: Mahogany... Lillie was heading that way. If this involves her, I want to know.
> Looker: Then it is settled! Olivine, {PLAYER}. We will be waiting!

---

## 8. Arquivos tocados (checklist de implementação)

| Arquivo | Mudança |
|---|---|
| `include/constants/vars.h` | `VAR_RIFT_MISSIONS_STATE 0x4120` + comentário |
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_BLACKTHORN` 0x1040, `FLAG_NO_CATCHING` 0x1041 + comentários; `CUSTOM_FLAGS_END` |
| `include/config/battle.h` | `B_FLAG_NO_CATCHING FLAG_NO_CATCHING` |
| `include/constants/map_event_ids.h` | 2 locais em Olivine House1, 6 em Blackthorn (à mão) |
| `data/maps/Route29/map.json` | apaga o objeto do Looker |
| `data/maps/Route29/scripts.pory` | apaga `Route29_EventScript_Looker` e `Route29_Text_Looker` |
| `data/maps/PokemonLeague_HallOfFame/scripts.inc` | `setvar VAR_RIFT_MISSIONS_STATE, 1` |
| `data/maps/NewBarkTown/scripts.pory` | entrada no `OnFrame` + `LookerCall` + texto |
| `data/maps/OlivineCity_House1/map.json` | remove engenheiro; adiciona Looker e Anabel com flag `0` |
| `data/maps/OlivineCity_House1/scripts.pory` | remove Voltorb; `ON_FRAME`, cena, briefing, diálogos por estado |
| `data/maps/OlivineCity_House3/map.json` | engenheiro do Voltorb em (7,4), no fim |
| `data/maps/OlivineCity_House3/scripts.inc` | scripts/textos do Voltorb (asm) |
| `data/maps/BlackthornCity/map.json` | flag do evento em 16 objetos; 6 objetos novos no fim |
| `data/maps/BlackthornCity/scripts.inc` | visibilidade, conversas, cena, escolha, boss, resolução, textos, movimentos |

Não editar `events.inc`/`header.inc`/`connections.inc` nem os `.inc` gerados de mapas
com `.pory`. Validar com `make -j$(nproc)`.

### 8.1 Divergências da implementação em relação ao texto acima

Todas cosméticas; o contrato de §1, §6 e §7 foi seguido à risca.

- Todo `warpsilent` é seguido de `waitstate`, `releaseall`, `end` (o plano parava no
  `waitstate`; sem `end` o script cairia nos bytes seguintes).
- `BlackthornCity_EventScript_UBGladionFoughtBuzzwole` **cai** em
  `..._UBAfterBattle` em vez de saltar: são rótulos contíguos.
- Os diálogos por estado em Olivine terminam num rótulo comum
  `OlivineCity_House1_EventScript_ReleaseEnd` (`closemessage`, `release`, `end`).
- Os textos foram quebrados em linhas reais de `.string` (`\n`/`\l`/`\p`).
- Reconferido na implementação: `0x4120` livre; nenhum `FLAG_TEMP_1/2` nem
  `VAR_TEMP_1/2/3` em Blackthorn, Olivine House1/House3 ou New Bark, nem em
  script comum alcançável desses mapas; nenhum `LOCALID_ROUTE29_*` nem
  `removeobject` sobre objeto da Route 29 ou de Blackthorn; a colisão real de
  Blackthorn (y=48..54, x=14..28) e de Olivine House1 bate tile a tile com as
  plantas de §4.2 e §5.4; `ClearTempFieldEventData` só roda em `LoadMapFromWarp`
  e `LoadMapFromCameraTransition` (`src/overworld.c:874,936`), logo `VAR_TEMP_3`
  sobrevive à batalha; `Overworld_ResetBattleFlagsAndVars` limpa
  `B_FLAG_NO_CATCHING` (`src/overworld.c:440`).
- O Sage (25,13) fica ao lado, não em cima, do caminho para a Dragon's Den
  (warp em (26,12)): escondê-lo durante o incidente não abre nem fecha nada.

---

## 9. Esqueleto × evolução

O que está **deliberadamente simples**. Cada item vira um comentário
`@ SKELETON: <o que falta>` no script correspondente, para que
`grep -rn "SKELETON:" data/maps/{Route29,NewBarkTown,OlivineCity_House1,BlackthornCity}`
liste tudo que falta polir:

| Item | Esqueleto | Evolução prevista |
|---|---|---|
| Luta do Gladion | Narrativa: resolvida junto com a vitória do jogador, fala muda pela escolha | Mostrar o combate dele na tela (animação de golpe, grito, UB recuando) antes ou depois da luta do jogador. Batalha real com Gladion **não** é o plano: a estrutura "cada um enfrenta uma" é a decisão de design. |
| Chefes | `setbossbattle 2, …, 110`, nível 70, golpes de nível | `bosslegendaryencounterwithmoves`-style: `seteventmonmoves` com moveset curado, mais barras, multiplicador, item; perfil de fases próprio em `battle_boss.c` se quiser mudança de fase. |
| Diálogos | Curtos, placeholder | Reescrever pela voz do design §3.1 (Gladion curto e concreto; Looker teatral/caloroso; Anabel precisa). |
| Coreografia | Ruptura = tremor + flash; UBs surgem paradas; a escolhida só dá "!" | Movimento das UBs, a escolhida avançar até o jogador, música própria, animação de portal. |
| Saída do elenco | Warp no lugar em Blackthorn | Gladion e Silvally caminhando para fora (Silvally na frente), Looker e Anabel indo para o Centro. |
| Moradores | Somem | Reações dos moradores depois do evento. |
| Anabel | Só fala | Beast Balls em Olivine a partir do estado 4 (design §5). |

**O que NÃO pode regredir numa evolução:** a máquina de estados §1.2, a invariante
flag ⇔ estado 3, a visibilidade por template, o SIM como único ponto de saída, a escolha
refeita a cada tentativa, o tratamento de todos os resultados e a proibição de captura
em Blackthorn.

---

## 10. Pendências e riscos conhecidos

- **Looker e Anabel em dois lugares no estado 3: aceito pelo autor.** O evento inteiro é uma
  cutscene; eles continuam na casa de Olivine (sem flag) e também aparecem em Blackthorn. Não
  esconder em Olivine. O diálogo do estado 3 ("we are leaving right behind you") basta.
- ~~`FLAG_GLADION_VICTORY_ROAD_DONE` (0x103F) ainda não commitado~~ — confirmado em 0x103F na implementação; `FLAG_EVENT_ULTRABEAST_BLACKTHORN` = 0x1040 e `FLAG_NO_CATCHING` = 0x1041, com `CUSTOM_FLAGS_END` apontando para a última.
- Money loss no blackout/desistência é o padrão da engine; aceito pelo design (batalha de ameaça).
- `FLAG_NO_CATCHING` passa a existir para qualquer script. Como a engine a limpa após toda
  batalha, esquecer de limpá-la não vaza para batalhas futuras.

---

## 11. Teste em runtime

- [ ] Route 29 sem Looker; Lusamine, Lass, Cut tree, berry tree e item continuam funcionando.
- [ ] New Game → Olivine House1: Looker e Anabel presentes com diálogo "de férias"; engenheiro do Voltorb em House3 (7,4), troca funciona e lembra `FLAG_OLIVINE_NPC_TRADE_COMPLETED`.
- [ ] HoF → sair de casa: ligação do Elm, depois do Looker; reentrar em New Bark não repete. Revanche da Liga não reativa.
- [ ] Estado 2: entrar na casa dispara a cena; os dois param lado a lado olhando para baixo, falam e voltam ao lugar sem atravessar a mesa. Estado vira 3.
- [ ] Estado 3: diálogo "vá na frente" em Olivine; Blackthorn sem nenhum NPC/Pokémon ambiente; item ball e luzes noturnas intactos; Centro, Joy, Mart, Ginásio acessíveis.
- [ ] Chegar por Fly, Route 45, Route 44 e Ice Path: elenco sempre presente, UBs sempre ausentes.
- [ ] Falar com Anabel e Gladion antes: falas curtas, nada muda. "Não" com o Looker libera.
- [ ] "Sim": cena roda sem input até o menu; menu não fecha com B.
- [ ] Escolher Buzzwole: boss Buzzwole com 2 barras; Gladion fala da Pheromosa depois. Idem invertido.
- [ ] Bolsa: bola bloqueada. "Run": desistência → blackout.
- [ ] Perder: acorda no Centro de Blackthorn; cidade ainda vazia, elenco no lugar; Looker recomeça e a escolha pode ser outra.
- [ ] Vencer: UBs somem, Looker e Anabel se aproximam sem sobrepor ninguém, gancho de Mahogany/Olivine, fade, cidade repovoada, elenco ausente, follower de volta.
- [ ] Estado 4: stub da Missão 2 em Olivine.
- [ ] Salvar/recarregar em cada estado (2, 3, 4) mantém tudo acima.

---

## 12. Feedback da implementação (19/09/2026)

Escrito depois de implementar o plano inteiro, para quem for evoluir esta cena
ou escrever o doc da Missão 2. O §8.1 lista *o que* ficou diferente; esta seção
diz *o que o plano acertou, o que faltou nele e o que ficou frágil*.

### 12.1 Resultado

Implementado de ponta a ponta, sem cortar escopo. `make -j$(nproc)` limpo
(ROM 92,47%, EWRAM 94,28%). 14 arquivos do §8 tocados, mais os `.inc` gerados.
Nenhum teste em runtime — o §11 continua inteiro em aberto.

### 12.2 O que o plano acertou (e economizou o trabalho de refazer)

Conferido contra os dados reais, não contra o texto:

- **As plantas de §4.2 e §5.4 batem tile a tile com a colisão real** (bit 11,
  `dump_mapa.py`). Nenhum `walk_*` precisou ser corrigido, nenhuma direção de
  olhar precisou ser reinvertida. É o item que mais costuma custar caro e veio
  pronto.
- **Os números de linha citados estavam exatos:** `include/config/battle.h:259`
  (`B_FLAG_NO_CATCHING`) e `:266` (`B_FLAG_NO_WHITEOUT`).
- **A lista de 16 objetos a esconder em Blackthorn estava exata.** A edição
  rodou com `assert o['flag'] == '0'` nos 16 e com a checagem inversa nos 11
  intocados (item ball + light sprites): nenhum falhou.
- **Endereços livres confirmados:** `0x4120` sem nenhum uso; `0x103F` de fato
  ocupado por `FLAG_GLADION_VICTORY_ROAD_DONE` (já no tree); `FLAG_TEMP_1/2` e
  `VAR_TEMP_1/2/3` livres nos quatro mapas **e** em todo script comum
  alcançável deles (`cave_of_origin`, `contest_hall`, `interview` e os do
  Battle Arcade usam essas temps, mas nenhum é chamado desses mapas).
- **§1.3 — `VAR_TEMP_3` sobrevive à batalha:** confirmado na fonte.
  `ClearTempFieldEventData` só é chamado de `LoadMapFromWarp` e
  `LoadMapFromCameraTransition` (`src/overworld.c:874,936`), e voltar de
  batalha não passa por nenhum dos dois.
- **§6.3 — `ignoreBPress = TRUE` realmente elimina o caso B:** em
  `Task_HandleScrollingMultichoiceInput` (`src/script_menu.c:500-506`) o
  `LIST_CANCEL` é engolido e o menu nem fecha. `VAR_RESULT` só pode sair 0 ou
  1, então **não** falta um tratamento de `MULTI_B_PRESSED`.
- **§1.1 — a engine limpa a flag de batalha sozinha:**
  `Overworld_ResetBattleFlagsAndVars` faz `FlagClear(B_FLAG_NO_CATCHING)`
  (`src/overworld.c:440`).

### 12.3 O que faltou no plano

- **`warpsilent` sem `end` (§6.2 e §7) — o único erro que viraria bug.** Os dois
  blocos terminavam em `waitstate`. Copiado literalmente, o script cairia nos
  bytes do rótulo seguinte. Corrigido para `waitstate` / `releaseall` / `end`.
- **O plano não disse o que acontece com o follower depois do `hidefollower`
  em Olivine.** Lá não há warp no fim da cena, ao contrário de Blackthorn, e
  este repo não tem `showfollower`. Verificado: o follower sai da bola sozinho
  no primeiro passo do jogador depois do `releaseall`
  (`src/event_object_movement.c:6225-6241`, que só se recusa a emergir enquanto
  `ArePlayerFieldControlsLocked()`). Não precisa de nada — mas precisava estar
  escrito.
- **O plano não conferiu se o Sage (25,13) é gate físico da Dragon's Den.** Ele
  agora some durante o incidente. Não é: o warp da Den fica em (26,12) e
  (26,13) é livre, então ele nunca bloqueou nada. A verificação faltava.
- **§3.2 não registrou uma inconsistência vizinha.**
  `NewBarkTown_EventScript_ElmCallAfterLeague` muda `VAR_NEWBARK_TOWN_STATE`
  **no fim**, não na primeira instrução. Funciona (a tabela de frame não é
  reavaliada enquanto um script roda), mas agora as duas entradas vizinhas
  seguem padrões diferentes. A entrada nova segue a regra da skill; quem mexer
  ali não deve "uniformizar" a nova pela antiga.

### 12.4 Dependências frágeis criadas por esta implementação

Coisas que não existiam antes e que uma evolução distraída quebra em silêncio:

- **Os 16 objetos de Blackthorn agora carregam
  `FLAG_EVENT_ULTRABEAST_BLACKTHORN`.** Antes eram `flag: 0`, onde
  `removeobject` era inofensivo. Agora um `removeobject` em qualquer um deles
  **seta a flag do evento e esvazia a cidade**. Vale para o Youngster, o Gym
  boy, o Santos, o pescador do Super Rod e os 8 Pokémon de ambiente.
- **A ordem das entradas do `NewBarkTown_OnFrame`.** Elm precisa vir antes do
  Looker; inverter as linhas inverte a ordem das duas ligações.
- **`VAR_TEMP_3` depende de não haver recarga de mapa entre a escolha e o fim
  da cena.** Se a evolução puser um warp, um `setrespawn` com recarga ou
  qualquer coisa que passe por `LoadMapFromWarp` entre o `dynmultichoice` e o
  `UBResolved`, a escolha do jogador se perde e o Gladion narra a UB errada.
- **Objetos novos sempre no fim de `object_events`.** Os locais 28-33 são
  posicionais; inserir qualquer coisa no meio renumera o elenco inteiro.

### 12.5 O que só o runtime decide (além do §11)

- **Anabel em (22,51), uma linha abaixo do jogador durante o gancho.** É o
  único ponto da cena em que apostei que a caixa de texto não a cobre. Se
  cobrir: trocar `BlackthornCity_Movement_AnabelToPlayer` para
  `walk_up, walk_up, walk_left × 4, face_left`, levando-a a **(22,50)** — tile
  livre, na mesma linha do jogador e do Looker, e o caminho continua limpo
  porque o Looker já parou em (21,50) antes dela andar (os dois são
  sequenciais justamente por isso).
- **A ruptura** (`ShakeCamera` → `FADE_TO_WHITE` → `addobject` ×2 →
  `FADE_FROM_WHITE` → dois `playmoncry`) nunca foi vista rodando. É o trecho
  mais provável de ficar feio sem estar errado.
- **Nível 70, 2 barras, multiplicador 110** são chute do plano por analogia com
  Rayquaza/Genesect. Só o playtest diz se a luta é ameaça ou parede.

### 12.6 Para o doc da Missão 2

O que compensa copiar deste doc: a tabela de temporários por mapa (§1.3), a
planta ASCII tirada da colisão real com o caminho de cada ator em coordenadas
(§5.4), e a tabela de resultados de batalha (§6.4). O que compensa fazer
diferente: terminar todo bloco de script do doc em `end`, e dizer
explicitamente o que acontece com o follower em cada cena que não termina em
warp.
