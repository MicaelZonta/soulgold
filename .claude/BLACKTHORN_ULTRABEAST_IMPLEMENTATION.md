# Blackthorn — Necrozma, Buzzwole + Pheromosa (Rift Mission 1) — implementação

**Status:** **história evoluída (revisão 3, 22/09/2026) e validada em runtime pelo autor (22/09/2026: "testei tudo, ficou perfeito")**, incluindo as reações pré-Liga à família Cosmog. `make -j$(nproc)` limpo. Receita reutilizável: skill `evoluir-historia-de-evento`.
Revisão 3 — 22/09/2026 (feedback do autor, §13). Revisão 2 — 19/09/2026.
**Modo:** esqueleto (skill `evento-esqueleto`). Diálogo curto, coreografia mínima,
mas estado, visibilidade, gatilhos, batalha e retry **completos e corretos**.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6 regras comuns (V19), §23.
**Missão seguinte:** [`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) — continua a var nos estados 4→5→6 e substitui o stub da Missão 2 deixado em `OlivineCity_House1` (§4.4).

Escopo: da ligação do Looker após o Hall of Fame até o fim do incidente de
Blackthorn, terminando com o gancho que manda o jogador de volta a Olivine **sem dizer
onde será a próxima ocorrência** (a Missão 2 é revelada no briefing).

**Mudanças da revisão 3 (22/09/2026)** — detalhe em §13:
- História: Clair (+ Kingdra) já luta contra o Necrozma na chegada; o Necrozma abre a fenda; Buzzwole e Pheromosa atacam o jogador; Gladion + Silvally chegam de surpresa; depois da luta o Necrozma absorve as duas UBs; o Gladion dá um Type: Null.
- Gladion não é mencionado antes da cena e fica escondido até o resgate.
- Portas da cidade trancadas (menos o Centro) durante o incidente — mecanismo em C.
- Checagem de equipe **e** PC cheios antes do SIM do Looker (presente do Type: Null).
- Boss mais difícil: 3 barras / Lv75 / x120 / moveset curado + item.
- Reação opcional à família Cosmog (Necrozma e elenco).
- Gancho sem destino; falas finais na ligação, no briefing e em toda a cena.

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
       └─ entrar em OlivineCity_House1 ▶ briefing: Clair e "um Pokémon feito de luz"
                                          (sem Gladion)                  → 3  + setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
            └─ Blackthorn: cidade vazia, portas trancadas (menos o Centro)
               na rua: Looker, Anabel, Clair + Kingdra contra o Necrozma
                 └─ falar com Looker ▶ equipe E PC cheios? → "regra da Anabel", volta depois
                      └─ SIM ▶ cena 100% scriptada:
                           Kingdra ataca, sem efeito ▶ Necrozma abre a fenda ▶ Buzzwole + Pheromosa
                           avançam no jogador ▶ Silvally salta na frente, Gladion chega
                           └─ ESCOLHA: qual você enfrenta? Gladion + Silvally ficam com a outra
                                └─ boss 3 barras / Lv75 / x120 contra a escolhida
                                     ├─ perdeu / desistiu → blackout → Centro de Blackthorn → recomeça
                                     ├─ outro             → reset silencioso → recomeça
                                     └─ venceu → Necrozma absorve as duas UBs, elenco espantado
                                                 → [família Cosmog na equipe: Necrozma reage]
                                                 → Necrozma some → conversa → Gladion dá Type: Null
                                                 → gancho sem destino
                                                 → clearflag + estado 4 → warp no lugar (cidade repovoa)
                                          └─ Olivine House1: briefing da Missão 2 (Mahogany revelado ali)
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
| `BlackthornCity` | `FLAG_TEMP_1` | Cache do elenco da rua: Looker, Anabel, Clair, Kingdra (visível com o incidente ativo) |
| `BlackthornCity` | `FLAG_TEMP_2` | Cache das Ultra Beasts (sempre escondidas até a cena) |
| `BlackthornCity` | `FLAG_TEMP_3` | Cache de Gladion + Silvally (sempre escondidos até o resgate) — rev. 3 |
| `BlackthornCity` | `FLAG_TEMP_4` | Cache do Necrozma (visível com o incidente ativo; flag própria porque a cena o remove sozinho) — rev. 3 |
| `BlackthornCity` | `VAR_TEMP_2` | Resultado da batalha |
| `BlackthornCity` | `VAR_TEMP_3` | Escolha do jogador: 0 = Buzzwole, 1 = Pheromosa. Sobrevive à batalha (voltar da batalha não recarrega o mapa, mesmo padrão de `ReceptionGate`). |
| `BlackthornCity` | `VAR_TEMP_4` | Espécie da família Cosmog a que o Necrozma reagiu (`SPECIES_NONE` = sem reação). Lida de novo na conversa final — rev. 3 |

Conferido em 22/09/2026: nenhum `FLAG_TEMP_1..4` nem `VAR_TEMP_1..4` em
`BlackthornCity/scripts.inc` além destes, nem em script comum alcançável do mapa.
O fluxo de apelido do Type: Null (`Common_EventScript_GiftMon`) passa por
`ChangePokemonNickname` e volta ao campo por `ResumeMap`, que **não** zera temps.

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

Texto final (rev. 3) em `NewBarkTown_Text_LookerCall`. Abertura teatral que ele
mesmo corrige, confissão do "homem de férias", e só o pedido para ir a Olivine:
**nenhuma criatura, cidade ou nome é revelado por telefone.**

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

Texto final (rev. 3) em `OlivineCity_House1_Text_Briefing`. Conteúdo, nesta ordem:
Looker se apresenta de verdade e apresenta a chefe; Anabel explica o "holiday";
Looker fala das leituras que em Alola precediam Ultra Wormholes; Anabel define
Ultra Beasts ("não são vilões: a maioria está perdida, assustada e é muito forte");
Looker conta que a **Líder de Ginásio de Blackthorn** ligou descrevendo "um Pokémon
feito de luz" no meio da cidade; Anabel: a Clair mandou todos para dentro e segura
a criatura sozinha; ponto de encontro no Centro de Blackthorn.

**Não mencionar o Gladion nem as duas Ultra Beasts** — são as surpresas da cena.

### 4.4 Scripts de objeto — diálogo por estado

`OlivineCity_House1_EventScript_Looker` (`lock`, `faceplayer`, ramifica por `VAR_RIFT_MISSIONS_STATE`):

| Estado | Fala (placeholder) |
|---|---|
| 0-1 | "Looker: Hm? Oh, pay no attention to moi. I am simply... on holiday. Yes. A holiday by the sea." |
| 2 | `call OlivineCity_House1_EventScript_BriefingTalk` (sem coreografia) |
| 3 | "Looker: Blackthorn, {PLAYER}! Clair cannot hold it forever. We are leaving right behind you!" |
| ≥ 4 | Substituído pelo briefing da Missão 2 (doc da M2). Rev. 3: o texto `BriefingM2` agora **revela** Mahogany ("It has started again. Mahogany Town.") e não cita mais o "Lake of Rage" do gancho antigo. |

`OlivineCity_House1_EventScript_Anabel`:

| Estado | Fala (placeholder) |
|---|---|
| 0-1 | "Anabel: Looker insists we are on vacation. He has been reading the same newspaper for three days." |
| 2 | `call OlivineCity_House1_EventScript_BriefingTalk` |
| 3 | "Anabel: Go on ahead. We'll be there before you reach the Pokémon Center." |
| ≥ 4 | "Anabel: Rest while you can. Looker will brief you on the next report." |

(Venda de Beast Balls entra depois, ver §9.)

---

## 5. Etapa D — Blackthorn: cidade vazia e portas trancadas

### 5.1 Esconder a cidade

`BlackthornCity/map.json`: os 16 NPCs e Pokémon ambientes têm
`"flag": "FLAG_EVENT_ULTRABEAST_BLACKTHORN"`:

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

### 5.2 Portas trancadas (rev. 3, sugestão do autor)

Com a flag do evento setada, **toda porta de prédio de Blackthorn recusa o
jogador, menos a do Pokémon Center** (cura e retorno do blackout). Resolve de
uma vez o problema da Clair duplicada: não dá para entrar no Ginásio e encontrá-la
lá enquanto ela luta na rua.

Mecanismo em `src/field_control_avatar.c`:

- `sLockedTownDoors[]` — uma linha por missão: `{ flag do evento, mapa da cidade,
  mapa da porta que fica aberta, script }`. Linha atual:
  `{ FLAG_EVENT_ULTRABEAST_BLACKTHORN, MAP_BLACKTHORN_CITY, MAP_BLACKTHORN_CITY_POKEMON_CENTER, BlackthornCity_EventScript_DoorLocked }`.
- `TryLockedDoorScript` roda **antes** de `TryDoorWarp` em `ProcessPlayerFieldInput`,
  com as mesmas condições de entrada (olhando para o norte, metatile de porta, warp
  no tile). Se a linha casa e o destino não é o Centro, dispara o script e não há warp.
- `BlackthornCity_EventScript_DoorLocked` (declarado em `include/event_scripts.h`):
  "The door is locked tight. A note is taped to it: “Stay inside until I say so.
  --Clair, Gym Leader”".

Portas afetadas: Ginásio (24,26), House1 (21,39), House2/Move Bros (36,41), Mart
(16,48), House3 (10,49). **Não afetadas** (não são porta): Dragon's Den (26,12),
Ice Path (42,22), Blackthorn Cave (39,18). A trava dura exatamente o tempo da flag:
o `clearflag` da vitória destranca tudo, sem estado novo.

### 5.3 Elenco — `object_events` 28-36

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 28 | `LOCALID_BLACKTHORN_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (25,53) | `FACE_UP` | `BlackthornCity_EventScript_UBLooker` | `FLAG_TEMP_1` |
| 29 | `LOCALID_BLACKTHORN_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (26,53) | `FACE_UP` | `BlackthornCity_EventScript_UBAnabel` | `FLAG_TEMP_1` |
| 30 | `LOCALID_BLACKTHORN_UB_GLADION` | `OBJ_EVENT_GFX_GLADION` | **(20,44)** | `FACE_DOWN` | `NULL` | **`FLAG_TEMP_3`** |
| 31 | `LOCALID_BLACKTHORN_UB_SILVALLY` | `OBJ_EVENT_GFX_SPECIES(SILVALLY)` | **(19,44)** | `FACE_DOWN` | `NULL` | **`FLAG_TEMP_3`** |
| 32 | `LOCALID_BLACKTHORN_UB_BUZZWOLE` | `OBJ_EVENT_GFX_SPECIES(BUZZWOLE)` | **(15,50)** | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 33 | `LOCALID_BLACKTHORN_UB_PHEROMOSA` | `OBJ_EVENT_GFX_SPECIES(PHEROMOSA)` | **(15,51)** | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 34 | `LOCALID_BLACKTHORN_UB_CLAIR` | `OBJ_EVENT_GFX_CLAIR` | (18,49) | `FACE_LEFT` | `BlackthornCity_EventScript_UBClair` | `FLAG_TEMP_1` |
| 35 | `LOCALID_BLACKTHORN_UB_KINGDRA` | `OBJ_EVENT_GFX_SPECIES(KINGDRA)` | (17,49) | `FACE_LEFT` | `BlackthornCity_EventScript_UBKingdra` | `FLAG_TEMP_1` |
| 36 | `LOCALID_BLACKTHORN_UB_NECROZMA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA)` | (14,50) | `FACE_RIGHT` | `BlackthornCity_EventScript_UBNecrozma` | `FLAG_TEMP_4` |

- Negrito = mudou na rev. 3. 34-36 são **novos, no fim**; nenhum local id anterior mudou.
- `map_event_ids.h` é **gerado** pelo `mapjson` a partir do campo `local_id` (corrige a
  §5.2 antiga, que mandava editar à mão).
- Gladion e Silvally ficam em y=44, seis linhas acima do ponto de combate: fora da
  câmera quando são adicionados.
- Kingdra e Necrozma têm `overworld.png` (o do Necrozma é 32x32, marcado TODO no species info).
- Orçamento: jogador + follower + 9 = **11/16**. Light sprites não contam (doc da M4 §12.8).
- (16,49), saída do Mart, fica livre de propósito.

### 5.4 Visibilidade — `ON_TRANSITION`

`BlackthornCity_EventScript_ApplyUBVisibility`, chamado de `BlackthornCity_EventScript_CityEnter`:

```asm
BlackthornCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2          @ UBs: sempre escondidas no load
	setflag FLAG_TEMP_3          @ Gladion + Silvally: sempre escondidos no load
	goto_if_unset FLAG_EVENT_ULTRABEAST_BLACKTHORN, BlackthornCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1        @ elenco da rua
	clearflag FLAG_TEMP_4        @ Necrozma
	return
BlackthornCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_4
	return
```

### 5.5 Planta da cena (dump real, bit 11; `#` = bloqueado)

```text
       x= 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
  y=44     .  .  .  .  .  .  s  g  .  .  .  .  .  .  .     s/g spawn de Silvally/Gladion (escondidos)
  y=45     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
  y=46     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
  y=47     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
  y=48     .  #  #  W  #  .  v  |  .  .  .  .  #  #  W     W (16,48) Mart, (27,48) Centro
  y=49     #  .  .  .  K  C  :  G  .  .  .  .  .  .  f     f (27,49) pouso do Fly
  y=50     .  N  B  >  >  b  S  *  .  .  .  .  .  .  .     * (20,50) posição de combate do jogador
  y=51     .  .  P  >  >  p  .  .  .  .  .  .  .  .  .
  y=52     .  .  #  .  .  #  #  .  .  .  #  #  t  a  .     t (25,52) ÚNICO tile para falar com Looker
  y=53     #  #  #  #  #  #  #  .  .  .  #  #  L  A  #

  N Necrozma (14,50)   K Kingdra (17,49)   C Clair (18,49)
  B Buzzwole (15,50) → carga até b (18,50) → recua para (17,50)
  P Pheromosa (15,51) → carga até p (18,51) → recua para (17,51)
  s Silvally (19,44) → desce a coluna 19 até (19,48) → jump_2 sobre (19,49) → S (19,50)
  g Gladion (20,44) → desce a coluna 20 → G (20,49), logo acima do jogador
```

O Looker continua no bolso (25,53): só dá para falar com ele de (25,52), olhando para
baixo — início determinístico sem `getplayerxy`.

### 5.6 Conversas antes da cena

| Objeto | Script | Comportamento |
|---|---|---|
| Anabel | `UBAnabel` | `faceplayer`; casas seladas, a Clair não recuou um passo; "fale com o Looker quando estiver pronto". **Com família Cosmog:** "is that a {species} with you? In Alola they call them children of the stars. Keep it close today." |
| Clair | `UBClair` | **Sem** `faceplayer` (não tira os olhos do Necrozma). "Stay back. I've got it." — a criatura saiu de um clarão de manhã, não machuca ninguém, "está esperando alguma coisa"; manda falar com o detetive. |
| Kingdra | `UBKingdra` | Grito + "não tira os olhos da criatura". |
| Necrozma | `UBNecrozma` | Descrição (cristal negro, luz sumindo para dentro dele, não nota o jogador). **Reação opcional:** com família Cosmog, vira a cabeça para a Poké Ball do {species}, com grito. |

Todas terminam em `BlackthornCity_EventScript_UBReleaseEnd`. Nenhuma muda estado.

---

## 6. Etapa E — A cena (100% scriptada a partir do SIM)

### 6.1 Pré-checagens (`BlackthornCity_EventScript_UBLooker`)

```asm
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	getpartysize                                   @ presente do Type: Null no fim:
	goto_if_ne VAR_RESULT, PARTY_SIZE, ..._UBLookerAsk   @ só equipe E PC cheios bloqueiam
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, ..._UBLookerAsk
	msgbox BlackthornCity_Text_UBNoRoom, MSGBOX_DEFAULT   @ "regra da Anabel"
	goto BlackthornCity_EventScript_UBReleaseEnd
..._UBLookerAsk::
	msgbox BlackthornCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBNotReady
	goto BlackthornCity_EventScript_UBScene
```

- Nenhum estado muda antes do SIM. O SIM é o último ponto de saída.
- A checagem de espaço vem antes de qualquer oferta (skill `entregar-pokemon-ou-ovo`)
  e não revela o presente: a justificativa é a regra da Anabel — "sempre espaço para
  mais um Pokémon; se uma fenda deixar alguém para trás, ele precisa ter para onde ir".
- Nada entre o SIM e o `givemon` pode encher equipe ou PC: a batalha bloqueia captura.

### 6.2 Chegada e ruptura (`BlackthornCity_EventScript_UBScene`)

1. `lockall`, `hidefollower`; jogador (25,52) → (20,50) olhando oeste
   (`PlayerToLine`, igual à rev. 2). Looker e Anabel sobem um passo juntos.
2. Clair vira para o leste (jogador em (20,50): dx=+2 domina), fala
   (`UBClairArrive`: Lance falou do Campeão; "estou tentando machucar isso há uma
   hora"; "Kingdra! Dragon Pulse!") e volta para o oeste.
3. Kingdra `walk_in_place_fast_left` ×2 + grito → flash branco → Necrozma
   `walk_in_place_fast_right` ×3 → `UBNoEffect` ("nem um arranhão... ele bebe a luz").
4. Grito do Necrozma → tremor → `FADE_TO_WHITE` → `clearflag FLAG_TEMP_2` + `addobject`
   das duas UBs → `FADE_FROM_WHITE` → gritos → `UBAppear` (Anabel: "Rift opening! Two
   signatures!"; Looker: "get back! They are coming right at you!").
5. **Carga:** Buzzwole (15,50)→(18,50), Pheromosa (15,51)→(18,51), `walk_fast_right` ×3,
   mesma sequência em linhas deslocadas → formação preservada.
6. **Resgate:** `clearflag FLAG_TEMP_3` + `addobject` Silvally e Gladion (fora da tela).
   Silvally `walk_faster_down` ×4 + `jump_2_down` → (19,50), entre o Buzzwole e o
   jogador; Gladion `walk_fast_down` ×5 → (20,49). Colunas diferentes → juntos.
   Grito do Silvally + tremor; as duas UBs recuam um tile de costas
   (`lock_facing_direction` + `walk_fast_left`) para (17,50)/(17,51).
7. "!" sobre Looker, Anabel e Clair → `UBGladionArrives` (Gladion: "Don't just stand
   there."; Looker: "And who might YOU be?!"; Gladion se apresenta — viu a luz sobre as
   montanhas; Clair: "Another Trainer? Fine. The more the better!").

### 6.3 A escolha — estrutura padrão

Igual à rev. 2 (`dynmultichoice ... TRUE ...`, `VAR_TEMP_3`, "!" na escolhida). Todos
já olham certo: jogador (20,50), Silvally (19,50) e Gladion (20,49) estão a leste das
duas UBs em x=17, que olham para o leste. O `UBChoosePrompt` inclui a Clair:
"And I'll keep that crystal thing busy. Go!".

### 6.4 Batalha — boss simples, mais difícil (rev. 3)

| | Buzzwole | Pheromosa |
|---|---|---|
| `setbossbattle` | 3 barras, x120, sem perfil | 3 barras, x120, sem perfil |
| Nível / item | 75 / Leftovers | 75 / Life Orb |
| Golpes (`seteventmonmoves`) | Bulk Up, Drain Punch, Leech Life, Ice Punch | Quiver Dance, Bug Buzz, Focus Blast, Ice Beam |

Ordem: `setbossbattle` → `playmoncry` → `seteventmon` → `seteventmonmoves` →
`BattleSetup_StartLegendaryBattle`. `B_FLAG_NO_CATCHING` setada logo antes;
`B_FLAG_NO_WHITEOUT` **não**. A escala continua subindo: M2 = 4 / Lv80 / x130.

Resultados — sem mudança em relação à rev. 2:

| Resultado | O que acontece |
|---|---|
| `B_OUTCOME_WON` | §7 |
| `LOST` / `DREW` / `FORFEITED` ("Run" no boss) | Blackout → Centro de Blackthorn; o script não continua |
| `CAUGHT` / `RAN` / outro (inalcançáveis) | `UBUnresolved`: fala + `warpsilent` (27,49) → recomeça |

**Retry:** a flag continua setada; o load devolve o elenco da rua ao lugar e esconde
de novo UBs, Gladion e Silvally. Falar com o Looker refaz tudo — pré-checagem e
escolha inclusive.

### 6.5 Absorção pelo Necrozma (`BlackthornCity_EventScript_UBResolved` / `UBAbsorb`)

Padrão de **todas** as missões (design §6, regras comuns).

1. Fala do Gladion conforme a escolha (a luta dele é narrativa, como na rev. 2).
2. Necrozma pulsa + grito. As duas UBs são **arrastadas de costas** de (17,y) para
   (15,y) (`lock_facing_direction` + `walk_slow_left` ×2), ao lado dele.
3. Tremor → `FADE_TO_WHITE` → `removeobject` das duas (flag `FLAG_TEMP_2`) →
   `FADE_FROM_WHITE` → grito.
4. "!" sobre Clair, Gladion, Looker e Anabel → `UBAbsorbed`: Clair ("It's pulling
   them in!"), Looker ("It... took them."), Gladion ("It didn't fight them. It fed on
   them."), Anabel ("That is not how an Ultra Beast behaves. That is not how anything
   behaves.").
5. §6.6 (opcional).
6. Tremor → flash → `removeobject` do Necrozma (flag própria `FLAG_TEMP_4`, não toca
   no elenco) → `UBNecrozmaGone` (Clair: abriu um buraco no céu, comeu o que saiu e foi embora).

**Ninguém o nomeia.** Para todos é "the creature" / "that crystal thing".

### 6.6 Reação opcional à família Cosmog (`UBNecrozmaSensesCosmog`)

`specialvar VAR_RESULT, CheckMysteryEggPokemon` → `VAR_TEMP_4`. Checado **depois** da
batalha, porque a batalha pode evoluir o Pokémon. Com `SPECIES_NONE` a cena segue
sem nada.

- Necrozma dá um passo para o jogador, (14,50)→(15,50) (livre desde a remoção do
  Buzzwole); "!" sobre o jogador; grito.
- Cosmog/Cosmoem: encara a Poké Ball; o Pokémon treme; Gladion manda o Silvally
  para a frente.
- Solgaleo/Lunala: a luz se acende entre os dois; ele recua, se firma e encara; o
  Pokémon do jogador não desvia o olhar.
- Na conversa final (§7), um bloco extra: Gladion ("It looked at your {species}. Not
  at us. Keep it close.") e Anabel ("children of the stars..."), ou, com a lendária,
  Gladion ("It flinched at your {species}. Remember that.") e Anabel ("legend of the
  sky itself").

---

## 7. Etapa F — Conversa, presente e gancho

```text
Looker (25,52) → (21,50) olhando oeste; depois Anabel (26,52) → (22,51) — sequencial,
o caminho dela cruza (25,51) (igual à rev. 2).
turnobject: Clair e Kingdra → leste; Gladion → sul (jogador abaixo); Silvally → leste.
Jogador → leste.
```

1. `UBAftermath`: Looker pergunta primeiro se alguém se feriu ("the report can wait a
   moment"); Clair agradece em nome da cidade e vai treinar "até entender o que acabou
   de ver"; Anabel resume ("It wasn't attacking Blackthorn. It was feeding."); Gladion:
   "I've seen light like that before. In Alola." — Looker quer saber mais — "Later."
2. Bloco Cosmog/lendária se `VAR_TEMP_4` ≠ `SPECIES_NONE` (§6.6).
3. **Presente** (`UBGift`): jogador vira para o norte (Gladion). `UBGladionGift`: outro
   Type: Null, encontrado sozinho nas montanhas depois da Route 45, abandonado; não se
   acomoda com ele, "vive tentando ser a sombra do Silvally"; assistiu o jogador lutar,
   "já decidiu".
   ```asm
   bufferspeciesname STR_VAR_1, SPECIES_TYPE_NULL
   givemon SPECIES_TYPE_NULL, 50
   goto_if_eq VAR_RESULT, MON_CANT_GIVE, BlackthornCity_EventScript_UBGiftNoRoom
   call Common_EventScript_GiftMon                 @ fanfarra, apelido, aviso de PC
   ```
   `UBGladionGiftAfter`: "Don't decide everything for it. Let it take the first step.
   It'll surprise you." — a lição do arco do próprio Gladion (design §3).
   **Guarda:** `MON_CANT_GIVE` é inalcançável (§6.1), mas se acontecer vai para
   `UBGiftNoRoom` → `UBUnresolved`, **antes** de qualquer mudança de estado: a missão é
   refeita e o presente nunca se perde.
4. Jogador → leste. `UBHook` — **sem destino**: Anabel ("the readings haven't settled;
   that creature will open another rift; where and when, we don't know yet"); Looker
   ("So we keep watching. Rest, then come to our house in Olivine. The moment something
   opens, you will be the first to know."); Gladion ("If it shows up again, it won't be
   alone. Silvally. We're going.").
5. `FADE_TO_BLACK` → `clearflag FLAG_EVENT_ULTRABEAST_BLACKTHORN` + `setvar
   VAR_RIFT_MISSIONS_STATE, 4` → `warpsilent MAP_BLACKTHORN_CITY, 20, 50` → `waitstate`
   → `releaseall` → `end`. A cidade repovoa, o elenco some, as portas destrancam.

---

## 8. Arquivos tocados

| Arquivo | Rev. 2 | Rev. 3 |
|---|---|---|
| `include/constants/vars.h` | `VAR_RIFT_MISSIONS_STATE 0x4120` | — |
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_BLACKTHORN` 0x1040, `FLAG_NO_CATCHING` 0x1041 | — |
| `include/config/battle.h` | `B_FLAG_NO_CATCHING FLAG_NO_CATCHING` | — |
| `include/constants/map_event_ids.h` | locais de Olivine/Blackthorn | regenerado (34-36) |
| `include/event_scripts.h` | — | `BlackthornCity_EventScript_DoorLocked` |
| `src/field_control_avatar.c` | — | `sLockedTownDoors`, `TryLockedDoorScript` |
| `data/maps/Route29/*` | remove o Looker | — |
| `data/maps/PokemonLeague_HallOfFame/scripts.inc` | `setvar ..., 1` | — |
| `data/maps/NewBarkTown/scripts.pory` | ligação | texto final da ligação |
| `data/maps/OlivineCity_House1/*` | casa, briefing, diálogos | briefing M1 final (sem Gladion); `BriefingM2` revela Mahogany; "go ahead" do estado 3 |
| `data/maps/OlivineCity_House3/*` | troca do Voltorb | — |
| `data/maps/BlackthornCity/map.json` | flag nos 16; elenco 28-33 | Gladion/Silvally/UBs reposicionados; 34-36 novos |
| `data/maps/BlackthornCity/scripts.inc` | visibilidade, cena, boss | seção da M1 reescrita inteira |

Fora da M1, na mesma revisão (design §4.11): comentários opcionais sobre a família
Cosmog em `GoldenrodCity_FlowerShop/scripts.pory`, `CianwoodCity/scripts.inc`,
`DragonsDen_Shrine/scripts.inc` e `ReceptionGate/scripts.inc`.

---

## 9. Esqueleto × evolução

`grep -rn "SKELETON:" data/maps/BlackthornCity` lista o que falta polir.

| Item | Hoje (rev. 3) | Evolução prevista |
|---|---|---|
| Falas | **Finais** (ligação, briefing M1, cena inteira) | Só ajuste de quebra de linha depois do runtime. |
| Coreografia | Golpes = andar no lugar + flash; ruptura = tremor + flash | Animações de golpe (field effects), sprite de portal, música própria do Necrozma. |
| Luta do Gladion | Narrativa, fala muda pela escolha | Mostrar o combate dele na tela. Batalha real com ele **não** é o plano. |
| Chefes | 3 barras / Lv75 / x120 / moveset curado + item | Ajustar só depois do runtime; perfil de fases próprio se quiser. |
| Type: Null | Lv50, Poké Ball comum, sem item | Nível/bola/itens (Memórias?) a decidir. |
| Saída do elenco | Warp no lugar | Gladion + Silvally saindo a pé pelo norte; Clair abrindo as portas. |
| Moradores | Somem; portas trancadas | Reações dos moradores depois do evento. |
| Anabel | Só fala | Beast Balls em Olivine a partir do estado 4 (design §5). |

**O que NÃO pode regredir:** a máquina de estados §1.2, a invariante flag ⇔ estado 3,
a visibilidade por template (inclusive Gladion/Silvally **sempre** escondidos no load),
o SIM como único ponto de saída, a checagem de espaço **antes** do SIM, a guarda
`MON_CANT_GIVE` antes do `clearflag`/`setvar`, a escolha refeita a cada tentativa, o
tratamento de todos os resultados, a proibição de captura, a absorção das **duas** UBs
pelo Necrozma, o Necrozma sem nome, o gancho sem destino e o Centro como única porta aberta.

---

## 10. Pendências e riscos conhecidos

- **Looker e Anabel em dois lugares no estado 3: aceito pelo autor** (inalterado).
- **Clair no Dragon's Den.** Se a revanche do Den ainda não aconteceu, a Clair pode
  estar lá também — a entrada do Den é caverna, não porta, e fica aberta. Não há como
  escondê-la sem mexer em `FLAG_HIDE_DEN_CLAIR`. Baixo impacto; conferir no runtime.
- **`VAR_TEMP_3`/`VAR_TEMP_4` dependem de não haver recarga de mapa** entre a escolha e
  o fim da cena. O apelido do Type: Null passa por `ChangePokemonNickname` e volta por
  `ResumeMap` (sem `ClearTempFieldEventData`) — e acontece depois da última leitura de
  `VAR_TEMP_4` de qualquer jeito.
- **Portas:** `TryLockedDoorScript` compara o mapa atual com a linha da tabela a cada
  tentativa de porta; custo desprezível. Uma porta nova no Blackthorn fica trancada
  automaticamente; um segundo prédio que precise ficar aberto exigiria outro campo.
- Money loss no blackout/desistência: padrão da engine, aceito.
- O sprite de overworld do Necrozma é 32x32 (TODO 64x64 no species info).

---

## 11. Teste em runtime

- [ ] Route 29 sem Looker; troca do Voltorb em House3 (inalterados da rev. 2).
- [ ] HoF → sair de casa: ligação do Elm, depois do Looker (texto novo, sem spoiler).
- [ ] Estado 2 → briefing em Olivine: cita Clair e "um Pokémon feito de luz"; **não** cita Gladion.
- [ ] Estado 3 em Blackthorn: rua vazia; Looker, Anabel, Clair, Kingdra e Necrozma presentes; **Gladion e Silvally ausentes**.
- [ ] Portas: Ginásio, Mart e as três casas mostram a fala da Clair e não entram; o Centro entra. Dragon's Den e Ice Path continuam acessíveis.
- [ ] Chegar por Fly, Route 45, Route 44 e Ice Path: mesmo elenco, UBs/Gladion ausentes.
- [ ] Falar com Anabel, Clair, Kingdra e Necrozma com e sem Cosmog na equipe.
- [ ] Equipe 6 + PC cheio: Looker dá a "regra da Anabel" e não pergunta SIM/NÃO. Liberar espaço → pergunta normal.
- [ ] SIM: a Clair olha para o jogador e volta; ataque do Kingdra; ruptura; carga das UBs **sem atravessar a Clair**; o Silvally salta e cai em (19,50); o Gladion chega em (20,49); ninguém sobreposto.
- [ ] Escolha Buzzwole e Pheromosa: boss com 3 barras, moveset e item certos. Ver se a luta é ameaça ou parede.
- [ ] Bola bloqueada; "Run" → blackout; perder → Centro; cidade vazia; Gladion escondido de novo; nova escolha.
- [ ] Vencer: absorção das duas UBs, "!" em quatro personagens, Necrozma some.
- [ ] Com Cosmog, Cosmoem, Solgaleo e Lunala (um por vez): Necrozma dá o passo, falas certas, bloco extra na conversa. Sem nenhum: nada.
- [ ] Type: Null com vaga na equipe (fanfarra + apelido) e com equipe cheia (vai para o PC com aviso). Cena continua depois do apelido.
- [ ] Anabel em (22,51) visível acima da caixa de texto (risco herdado, §12.5).
- [ ] Gancho sem destino; fade; cidade repovoada; portas abertas; follower de volta.
- [ ] Estado 4 em Olivine: briefing da M2 revela Mahogany.
- [ ] Salvar/recarregar nos estados 2, 3 e 4.

---

## 12. Feedback da implementação da revisão 2 (19/09/2026) — histórico

> Registro da rev. 2. Onde contradiz as seções acima (posições, textos, números do
> boss), valem as de cima e o §13.

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

---

## 13. Revisão 3 — a história (22/09/2026)

Feedback do autor sobre o esqueleto: "o esqueleto está pronto, agora vamos montar
uma história épica". O que foi pedido e como ficou:

| Pedido | Como ficou |
|---|---|
| Diálogos naturais, pela personalidade | Falas finais na ligação, no briefing e na cena; vozes do design §3.1 (Looker teatral que se corrige e pergunta primeiro pelas pessoas; Anabel precisa; Gladion curto; Clair orgulhosa e responsável pela cidade). |
| Looker não fala do Gladion antes | Briefing reescrito; Gladion/Silvally escondidos (`FLAG_TEMP_3`) até o resgate; o Looker nem sabe quem ele é. |
| Uma história real em Blackthorn | §6.2: Clair já lutando → golpe sem efeito → ruptura → carga → resgate. |
| UBs atacam o jogador; Gladion salva no último segundo | Carga até (18,y); Silvally salta para (19,50); Gladion para em (20,49). O pedido dizia "Type: Null"; o parceiro do Gladion no pós-game é o **Silvally** (design §1, regra visual), então o resgate é dele. |
| Próximo evento é mistério | Gancho sem destino; `BriefingM2` passou a revelar Mahogany. |
| Clair participa | Objetos 34 (Clair) e 35 (Kingdra); foi ela quem chamou a polícia e evacuou a cidade. |
| Clair já lutando com o Necrozma; os outros dois aparecem e atacam | Objeto 36 (Necrozma); §6.2. |
| Necrozma absorve as UBs em todos os encontros | §6.5; regra comum no design §6. **Só a M1 cumpre hoje.** |
| Personagens espantados com o Necrozma | "!" em quatro personagens + `UBAbsorbed` + `UBAftermath`. |
| Luta mais difícil | 3 barras / Lv75 / x120 / moveset curado + item (§6.4). |
| Gladion dá um Type: Null; equipe e PC cheios bloqueiam o SIM | §6.1 e §7.3. O design proibia esse presente; a proibição foi substituída (design §3). |
| Reação opcional do Necrozma e dos NPCs ao Cosmog | §5.6 (antes da cena) e §6.6 (depois da batalha). |
| Sugestão no meio do trabalho: fechar as portas em vez de esconder a Clair do Ginásio | §5.2, mecanismo em C com uma linha por missão. |

Também nesta revisão, fora do mapa: comentários opcionais da Lillie e do Gladion
sobre a família Cosmog nos quatro encontros pré-Liga em que ela pode existir
(design §4.11).

**Conferido:** `make -j$(nproc)` limpo; local ids 28-33 intactos, 34-36 no fim;
todos os tiles dos caminhos novos livres no `dump_mapa.py`; nenhum ator termina no
tile de outro; `VAR_RESULT` não é lido depois de nenhum dos quatro pontos de
inserção pré-Liga antes de ser reescrito.

**Runtime (22/09/2026):** validado pelo autor, sem correções. Os pontos abaixo eram os riscos antes do teste: o salto do Silvally (`jump_2_down` sobre um tile
livre) e se a carga das UBs parece ataque ou passeio; o equilíbrio da luta nova;
se a Anabel em (22,51) fica visível; o fluxo de apelido do Type: Null no meio de uma
cutscene com `lockall`.
