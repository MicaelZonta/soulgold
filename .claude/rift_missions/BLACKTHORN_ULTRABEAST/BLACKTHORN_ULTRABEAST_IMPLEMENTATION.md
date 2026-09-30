# Blackthorn — Necrozma, Buzzwole + Pheromosa (Rift Mission 1) — implementação

**Status:** **roteiro V2 (auditoria V3) implementado — 25/09/2026, revisão 5.** `make -j$(nproc)` limpo; **runtime pendente, e a cena mudou o suficiente para NÃO herdar o "testei tudo, ficou perfeito" de 22/09/2026** (lista nova no §11). Receita reutilizável: skill `evoluir-historia-de-evento`.
Revisão 5 — 25/09/2026 (§15 e §16). Revisão 4 — 23/09/2026 (§14). Revisão 3 — 22/09/2026 (§13). Revisão 2 — 19/09/2026.
**Modo:** história final. O esqueleto foi superado nas revisões 3 e 5; o que resta de placeholder está no §9.
**Roteiro da cena (falas e movimentos):** [`BLACKTHORN_ULTRABEAST_SCRIPT_V2.md`](BLACKTHORN_ULTRABEAST_SCRIPT_V2.md) — **é ele que vale**. O [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md) é o roteiro da revisão 3 e fica como histórico.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6 regras comuns (V26), §23, §29.
**Missão seguinte:** [`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](../MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) — continua a var nos estados 4→5→6. **Atenção:** o estado 4 deixou de abrir o briefing sozinho (§15.3).

**Mudanças da revisão 5 (25/09/2026)** — detalhe em §15, reflexão em §16:
- Todas as falas da ligação, do briefing de Olivine e da cena inteira substituídas pelo roteiro V2.
- Uma caixa, um falante. O briefing da M1 virou cinco `msgbox` seguidos.
- O ataque da Clair tem efeito visível: o Necrozma recua um tile e volta.
- A ruptura ganhou **objeto próprio** (`OBJ_EVENT_GFX_ALTAR_RIFT` em (14,51)).
- As duas UBs avançam com ritmos e linhas diferentes; o Silvally intercepta frente e depois lateral.
- O Gladion **nomeia o Necrozma** em cena. A regra "ninguém o nomeia" morreu no design.
- A Anabel **tenta conter** a UB derrotada; a ligação repele a Ball.
- A oscilação da ruptura depois da absorção é obrigatória em todos os ramos.
- O parceiro da família Cosmog é um **ator de verdade** em (19,51) — quatro templates, um é adicionado.
- O Type: Null do presente é objeto próprio em (19,49), visível ao lado do Silvally; origem revisada (veio de Alola com o Gladion).
- **Retry com checkpoint persistente** (`FLAG_BLACKTHORN_UB_ENGAGED`) e texto próprio.
- **Falha de entrega não repete a batalha** (`FLAG_BLACKTHORN_TYPE_NULL_PENDING`).
- Trilha de ameaça (`fadeoutbgm` / `playbgm MUS_DP_LEGEND_APPEARS, TRUE` / `fadedefaultbgm`).
- **Convocação por telefone, uma por dia** (`FLAG_DAILY_LOOKER_CALL` + `FLAG_RIFT_LOOKER_SUMMONS`), e o estado 4 passa a **esperar a ligação** antes de oferecer o briefing.

**Mudanças da revisão 4 (23/09/2026):** flashes com `fadescreenswapbuffers` (§14).

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

**Constantes da revisão 5 (25/09/2026):**

| Constante | Arquivo | Valor | O que é |
|---|---|---|---|
| `FLAG_BLACKTHORN_UB_ENGAGED` | `include/constants/flags.h` | `0x1047` | Checkpoint de retry: a fenda já foi aberta e o Gladion já se apresentou. Setada no último beat antes da escolha, limpa no fim da missão. **É o único estado da cena que sobrevive a um blackout**, porque o blackout recarrega o mapa e mata todo `FLAG_TEMP_*`. |
| `FLAG_BLACKTHORN_TYPE_NULL_PENDING` | `include/constants/flags.h` | `0x1048` | Cidade salva, presente pendente. Mantém só Gladion + Silvally na rua e um diálogo que conclui **só** a entrega. |
| `FLAG_RIFT_LOOKER_SUMMONS` | `include/constants/flags.h` | `0x1049` | Convite emitido: o Looker ligou e o briefing em Olivine está disponível. Persiste entre dias e saves; enquanto está setada, **não** há nova ligação; enquanto está limpa, a casa só dá a fala de espera. Gate dos estados 4, 6, 8 e 10 — **não** do 2. |
| `FLAG_DAILY_LOOKER_CALL` | `include/constants/flags.h` | `DAILY_FLAGS_START + 0x2F` | O Looker já ligou hoje. Daily flag: o `ClearDailyFlags` a limpa na virada da data (calendário do jogo, não 24 h). Setada também por **todo** script que fecha uma missão. |

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
| 4 | Blackthorn resolvido; **convocação da Missão 2 pendente** | `BlackthornCity_EventScript_UBHook` | `ShouldDoRiftMissionCall`; Olivine House1 (espera **ou** briefing, conforme `FLAG_RIFT_LOOKER_SUMMONS`) |
| 5+ | Reservado para as próximas missões | próximos docs | — |

**Invariante:** `FLAG_EVENT_ULTRABEAST_BLACKTHORN` setada ⇔ `VAR_RIFT_MISSIONS_STATE == 3`.
As duas mudam **juntas, no mesmo script** (Olivine seta, Blackthorn limpa). A flag
existe só porque o campo `flag` do `map.json` não lê var — é ela que esconde a
cidade. A var é a autoridade da história.

**Invariante nova da revisão 5:** um estado par ≥ 4 significa *missão anterior
fechada, próxima convocação pendente* — **não** "briefing disponível". O briefing
só existe com `FLAG_RIFT_LOOKER_SUMMONS` setada, e é a ligação do Looker que a
seta. O estado 2 é a exceção deliberada: a convocação dele é a cena de ligação em
New Bark, aquele convite não expira nem se repete, e submetê-lo à flag travaria
qualquer save feito antes de a flag existir.

A escolha do jogador (qual UB enfrentar) continua temporária: numa nova tentativa
ele escolhe de novo. As outras três flags persistentes da missão estão no §1.1.

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
| `BlackthornCity` | `FLAG_TEMP_5` | Cache do ator do parceiro do jogador — **quatro** templates (Cosmog, Cosmoem, Solgaleo, Lunala) no mesmo tile (19,51) partilhando uma flag. No máximo um é adicionado, e o `removeobject` esconde os quatro — rev. 5 |
| `BlackthornCity` | `FLAG_TEMP_6` | Cache da ruptura (14,51). Aberta quando o Necrozma rasga, fechada atrás dele; num retry o load a devolve aberta — rev. 5 |
| `BlackthornCity` | `FLAG_TEMP_7` | Cache do Type: Null do presente (19,49) — rev. 5 |

Conferido em 25/09/2026: `FLAG_TEMP_5/6/7` não aparecem em nenhum script comum
(`data/scripts/`) nem em `src/`, só em mapas distintos deste.

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

O texto do briefing (`OlivineCity_House1_Text_Briefing`) está em [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md), "Ato 2".
Restrição que o texto precisa respeitar: **não mencionar o Gladion nem as duas
Ultra Beasts** — são as surpresas da cena.

### 4.4 Scripts de objeto — ramificação por estado

`OlivineCity_House1_EventScript_Looker` e `..._EventScript_Anabel`: `lock`,
`faceplayer` e um `goto_if_eq` por valor de `VAR_RIFT_MISSIONS_STATE`.

| Estado | Looker | Anabel |
|---|---|---|
| 0-1 | `Text_LookerHoliday` | `Text_AnabelHoliday` |
| 2 | `call ..._EventScript_BriefingTalk` (sem coreografia) | idem |
| 3 | `Text_LookerGoAhead` | `Text_AnabelGoAhead` |
| ≥ 4 | briefing da Missão 2 em diante (docs das missões seguintes) | idem |

As falas estão em [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md), "Ato 2". A casa é o hub de todas as missões: cada doc
acrescenta o ramo do seu estado, nunca reescreve os anteriores.

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

| Objeto | Script | Nota técnica |
|---|---|---|
| Anabel | `UBAnabel` | `faceplayer`. Ramo extra com família Cosmog na equipe (`CheckMysteryEggPokemon`). |
| Clair | `UBClair` | **Sem** `faceplayer`: ela não tira os olhos do Necrozma. |
| Kingdra | `UBKingdra` | `playmoncry` + narração. |
| Necrozma | `UBNecrozma` | Narração. Ramo extra com família Cosmog, com grito. |

Todas terminam em `BlackthornCity_EventScript_UBReleaseEnd`. Nenhuma muda estado.
Os textos estão em [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md), "Ato 3".

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

### 6.2 Chegada, ruptura e resgate (`BlackthornCity_EventScript_UBScene`)

**A cena inteira — beats, movimentos e falas — está em [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md), "Ato 5".** Aqui só o
que a implementação precisa garantir:

- `lockall` + `hidefollower` na primeira linha; nada mais devolve o controle até o fim.
- O jogador é levado a (20,50) por `PlayerToLine`, caminho fixo: **não** há
  `getplayerxy`, porque o único tile de onde se fala com o Looker é (25,52).
- Buzzwole e Pheromosa entram por `addobject` sob `FLAG_TEMP_2`; Gladion e Silvally
  por `addobject` sob `FLAG_TEMP_3`, em y=44 — seis linhas acima do combate, **fora
  da câmera**.
- Cada par que anda junto tem caminhos disjuntos passo a passo; os que se cruzam
  andam em sequência.
- Flash = `fadescreenswapbuffers`, nunca `fadescreen` (§14).

### 6.3 A escolha — estrutura padrão

`dynmultichoice ... TRUE ...` (sem cancelar: a cena já começou), resultado em
`VAR_TEMP_3` (0 = Buzzwole, 1 = Pheromosa), "!" sobre a escolhida. A escolha é
**por tentativa**: depois de um blackout o jogador escolhe de novo.

Nenhum `turnobject` é preciso: jogador (20,50), Silvally (19,50) e Gladion (20,49)
estão a leste das duas UBs em x=17, que olham para o leste.

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

Padrão de **todas** as missões (design §6, regras comuns). Coreografia e falas:
[`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md), "Ato 6".

Contrato técnico desta etapa:

- As duas UBs são removidas sob a flag delas (`FLAG_TEMP_2`) — `removeobject` setar
  essa flag é inofensivo.
- O Necrozma é removido sob **flag própria** (`FLAG_TEMP_4`), para não encostar na
  flag do elenco da rua.
- **Ninguém o nomeia.** Para todos é "the creature" / "that crystal thing".

### 6.6 Reação opcional à família Cosmog (`UBNecrozmaSensesCosmog`)

`specialvar VAR_RESULT, CheckMysteryEggPokemon` → `VAR_TEMP_4`. Checado **depois** da
batalha, porque a batalha pode evoluir o Pokémon. Com `SPECIES_NONE` a cena segue
sem nada. `VAR_TEMP_4` é lida de novo na conversa final (§7), que ganha um bloco
extra — um texto para Cosmog/Cosmoem e outro para Solgaleo/Lunala.

O passo do Necrozma em direção ao jogador, (14,50)→(15,50), só é livre porque o
Buzzwole já foi removido. Falas: [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md).
---

## 7. Etapa F — Conversa, presente e gancho

**Coreografia e falas:** [`BLACKTHORN_ULTRABEAST_SCRIPT.md`](BLACKTHORN_ULTRABEAST_SCRIPT.md), "Ato 7".

Ordem técnica:

1. `UBAftermath`; bloco Cosmog/lendária se `VAR_TEMP_4` ≠ `SPECIES_NONE` (§6.6).
2. **Presente** (`UBGift`):

   ```asm
   bufferspeciesname STR_VAR_1, SPECIES_TYPE_NULL
   givemon SPECIES_TYPE_NULL, 50
   goto_if_eq VAR_RESULT, MON_CANT_GIVE, BlackthornCity_EventScript_UBGiftNoRoom
   call Common_EventScript_GiftMon                 @ fanfarra, apelido, aviso de PC
   ```

   **Guarda:** `MON_CANT_GIVE` é inalcançável (§6.1), mas se acontecer vai para
   `UBGiftNoRoom` → `UBUnresolved`, **antes** de qualquer mudança de estado: a missão é
   refeita e o presente nunca se perde.
3. `UBHook` — gancho **sem destino**; a Missão 2 só é revelada no briefing seguinte.
4. `FADE_TO_BLACK` → `clearflag FLAG_EVENT_ULTRABEAST_BLACKTHORN` + `setvar
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

**Nada aqui foi testado depois da revisão 5.** O "testei tudo, ficou perfeito" de
22/09/2026 vale para a revisão 3; a cena mudou em quase todos os beats, e a
sequência de convocação é inteiramente nova.

### 11.1. Convocação por telefone (novo)

- [ ] HoF → sair de casa: ligação do Elm, **depois** a do Looker, uma por frame, sem sobreposição.
- [ ] Estado 2: o Looker **não** liga de novo nos dias seguintes, e o briefing em Olivine está disponível na hora (sem esperar ligação).
- [ ] Terminar Blackthorn **no mesmo dia** da ligação de New Bark: nenhuma segunda ligação naquele dia.
- [ ] Estado 4 antes da ligação: falar com Looker e com Anabel dá a fala de espera, cada um com a **própria plaquinha**; entrar na casa não encena nada.
- [ ] Dormir/avançar a data → andar fora de Olivine House1: a ligação toca **uma vez**, nomeia Mahogany, e não toca mais nesse dia.
- [ ] Depois da ligação: o briefing da M2 aparece (pelo gatilho de frame **e** falando com qualquer um dos dois) e a fala de espera desaparece.
- [ ] Estar **dentro** da casa não consome a chamada: ela toca ao sair.
- [ ] Recarregar o save com o convite emitido: o convite continua; sem ele, a espera continua.
- [ ] Presente pendente (equipe 6 + PC cheio forçado): **nenhuma** ligação até a entrega ser concluída.
- [ ] Retry depois de blackout: nenhum telefone.

### 11.2. Cena de Blackthorn (revista)

- [ ] Estado 3 em Blackthorn: rua vazia; Looker, Anabel, Clair, Kingdra e Necrozma presentes; **Gladion, Silvally, UBs e ruptura ausentes**.
- [ ] Portas: Ginásio, Mart e as três casas mostram só o bilhete curto e não entram; o Centro entra.
- [ ] Chegar por Fly, Route 45, Route 44 e Ice Path: mesmo elenco.
- [ ] Falar com Anabel, Clair, Kingdra e Necrozma: uma caixa cada, plaquinha certa, **nenhuma** extensão de Cosmog antes da cena.
- [ ] Equipe 6 + PC cheio: o Looker dá a mensagem curta de espaço e **não** pergunta SIM/NÃO. Com espaço, nada é dito.
- [ ] SIM: Clair olha e volta; `Kingdra! Dragon Pulse!` é caixa própria; o Necrozma **recua até (13,50), pulsa e volta a (14,50)** sem virar de lado.
- [ ] A ruptura aparece em (14,51) com sprite visível, e o tema de ameaça entra **antes** de as UBs aparecerem.
- [ ] Carga: o Buzzwole em linha reta e a Pheromosa com pausa + amago + corrida mais rápida. **Não** parecem uma formação.
- [ ] O jogador vira sul no aviso do Looker; o Silvally cai em (19,50), bate para oeste (Buzzwole a (17,50)), vira sul e bate (Pheromosa a (17,51)); ninguém sobreposto.
- [ ] O Gladion para em (20,49); o jogador confirma com o gesto e volta a oeste; `Necrozma. What's it doing here?` com plaquinha GLADION.
- [ ] A plaquinha **em cima do menu Buzzwole/Pheromosa é GLADION**.
- [ ] Boss com 3 barras, moveset e item certos; bola bloqueada.
- [ ] Vitória: a Anabel sobe para (26,51), arremessa, a Ball é repelida — **a UP alvo é a que o jogador derrotou**, nas duas escolhas.
- [ ] Absorção: Kingdra e Silvally atacam antes; as UBs dão o passo contra o arrasto; **só as UBs somem**; o Necrozma continua visível, pulsa mais claro e a **ruptura oscila** — inclusive sem família Cosmog na equipe.
- [ ] Com Cosmog, Cosmoem, Solgaleo e Lunala (um por vez): o Pokémon **aparece em (19,51) antes da fala**, com o cry certo; o Cosmoem não anda; o Necrozma dá o passo até (15,50); o parceiro é **recolhido na tela** antes do reagrupamento.
- [ ] Com Solgaleo **e** Lunala na equipe: um só aparece, e é o primeiro da ordem da equipe; não troca de espécie no meio.
- [ ] Rescaldo: o Looker chega a (21,50) e a Anabel a (22,51) **partindo de (26,51)**; ninguém cruza tile ocupado; a Anabel fica visível acima da caixa.
- [ ] Presente: o Silvally abre (19,50) indo a (18,50); o Type: Null **aparece em (19,49) e os dois ficam na tela juntos**; ele desce sozinho e olha o jogador.
- [ ] A fala da origem diz **Alola** e Route 45 como treino.
- [ ] Type: Null com vaga na equipe (fanfarra + apelido) e com equipe cheia (vai para o PC com aviso). O ator só é recolhido **depois** de a entrega ser aceita.
- [ ] Gancho: o Looker pede para **esperar a ligação** e não manda ninguém a Olivine agora.
- [ ] Fim: fade, cidade repovoada, portas abertas, follower de volta, elenco sumido.
- [ ] À noite: entrar na cena e conferir que o **quarto flash** está tão claro quanto o primeiro, e que a trilha de ameaça volta certa depois do boss.

### 11.3. Retry e presente pendente (novo)

- [ ] Perder o boss → blackout → voltar à rua: **UBs em (17,50)/(17,51), Silvally em (19,50), Gladion em (20,49), ruptura aberta**, Necrozma no lugar.
- [ ] Falar com o Gladion nesse estado: a fala curta de retry, **sem** ele virar para o jogador.
- [ ] Falar com o Looker: texto de retry ("Clair and Gladion are holding them back"), pergunta da Anabel, e o SIM cai **direto na escolha** — sem telefonema, sem reconhecimento da Clair, sem reapresentação do Gladion.
- [ ] O tema de ameaça toca de novo na retomada (o `savedMusic` foi zerado pelo load).
- [ ] Desistir (Run) e perder: os dois passam pelo mesmo caminho.
- [ ] Forçar equipe 6 + PC cheio **depois** do SIM (debug): a cidade é salva, o estado vai a 4, a cidade repovoa e **só** Gladion + Silvally ficam na rua; falar com ele conclui a entrega e os dois saem a pé pelo norte.
- [ ] Salvar/recarregar com o presente pendente: os dois continuam lá.
- [ ] Salvar/recarregar nos estados 2, 3 e 4.

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

## 14. Revisão 4 — o escurecimento dos flashes (23/09/2026)

Feedback do autor depois de jogar: *"quando as Ultra Beasts aparecem é para
ficar mais escuro e é legal, mas fica impossivelmente escuro"*. Vale para as
quatro missões; corrigido nas quatro de uma vez.

### 14.1 A causa

Não havia escurecimento nenhum no script — o que a cena tinha era **flash**, e o
flash é que estava escurecendo a cidade a cada repetição.

`fadescreen FADE_TO_*` copia `gPlttBufferFaded` por cima de `gPlttBufferUnfaded`
antes de escurecer (`FadeScreen`, `src/field_weather.c`; o próprio comentário do
upstream avisa: *"works fine, except if the screen is faded back in without
transitioning to a different screen"*). O `FADE_FROM_*` seguinte chama
`BeginTimeOfDayPaletteFade`, que aplica o tint de horário **em cima do buffer que
já estava tintado**.

À noite o tint é `coeff = 10`, `TINT_NIGHT` ≈ 0,46 (`gTimeOfDayBlend`,
`src/overworld.c:1618`). Cada par de flashes multiplica a cena por 0,46 de novo:
dois pares ≈ 4,4% do brilho original, e a cidade vira a tela preta da foto do
autor. De dia `coeff = 0` e nada acontece — por isso o bug só aparece na cena,
que é noturna, e nunca no resto do jogo.

### 14.2 A correção

Todo `fadescreen` **de dentro da cena** virou `fadescreenswapbuffers`, que faz o
mesmo efeito com BLDY no hardware (`FadeScreenHardware`) e não encosta nas
paletas. O `FADE_FROM_*` reseta os registradores de blend no fim
(`shouldResetBlendRegisters`), então não sobra estado.

Continuam com `fadescreen FADE_TO_BLACK` **só** os dois pontos em que um warp
recarrega o mapa logo depois e as paletas são refeitas do zero:
`UBUnresolved` (retry depois do blackout) e `UBHook` (recarga em lugar com
o incidente encerrado).

O padrão já era o recomendado em `.claude/skills/visibilidade-e-gatilhos`
(§ do `addobject` sob fade) e é o que o macro `bosslegendaryencounter` usa em
`asm/macros/event.inc`. A receita de flash da skill
`evoluir-historia-de-evento` §6 estava errada e foi corrigida junto.

**Conferido:** `make -j$(nproc)` limpo. **Runtime pendente** — o teste é entrar
na cena **à noite** e conferir que a quarta ruptura está tão clara quanto a
primeira.

## 15. Revisão 5 — o roteiro V2 e a convocação diária (25/09/2026)

Duas entregas: o autor entregou `BLACKTHORN_ULTRABEAST_SCRIPT_V2.md` (com a
auditoria V3 dentro, §18 dele) para ser implementado, e pediu numa frase que o
Looker passasse a **ligar** para chamar o jogador a Olivine, uma vez por dia,
"e esse pattern daqui em diante".

### 15.1. Pedido → como ficou

| Pedido | Como ficou |
|---|---|
| Uma caixa, um falante | Os textos com três e quatro plaquinhas dentro foram quebrados. O briefing da M1 virou **cinco** `msgbox` seguidos sem `closemessage`, cada um começando com o seu `{SPEAKER ...}` — `TrySetSpeakerFromMessage` só lê o começo de cada mensagem. |
| Ligação inicial curta, sem a cobertura das férias | `NewBarkTown_Text_LookerCall` reescrito. |
| O ataque da Clair tem de ter efeito | `UBClairAttack` em caixa própria + `Movement_NecrozmaPushedBack` (14,50)→(13,50) com `lock_facing_direction`, pulso, `Movement_NecrozmaReturns`. |
| Ruptura com borda visível | `LOCALID_BLACKTHORN_UB_RIFT`, `OBJ_EVENT_GFX_ALTAR_RIFT` (o mesmo sprite 32x32 do altar), (14,51), `FLAG_TEMP_6`. Não precisou de gráfico novo. |
| UBs com ritmos diferentes | `Movement_BuzzwoleCharge` (3× `walk_fast_right`) e `Movement_PheromosaCharge` (`delay_16` + amago + 3× `walk_faster_right`). |
| Resgate: frente e depois lateral | `Movement_SilvallyStrikeLeft` → recuo do Buzzwole → `Movement_SilvallyStrikeDown` → recuo da Pheromosa. Sequencial. |
| Gladion nomeia o Necrozma | `UBNecrozmaNamed`. A regra "ninguém o nomeia" foi **reescrita** no design §6, não duplicada. |
| Tentativa de contenção | `UBContain`: (26,52)→(26,51), arremesso, `SE_M_REFLECT`, `UBRiftPulse`, `SE_BALL_BOUNCE_1`. Alvo escolhido por `VAR_TEMP_3`. |
| Absorção tentada, não assistida | Kingdra e Silvally atacam a ligação antes; `Movement_UBPulledIn` ganhou um `walk_in_place_fast_right` de resistência antes do arrasto. |
| Só as UBs somem | O flash da absorção remove **apenas** as duas; o Necrozma e a ruptura saem num flash próprio, depois. |
| Oscilação obrigatória | `UBFlash` (ganho de luz) → pulso → `UBRiftPulse` + `SE_WARP_IN`, fora de qualquer `goto_if`. |
| Parceiro visível antes da fala | Quatro templates em (19,51) com `FLAG_TEMP_5`; `UBAddPartner` adiciona um; `playmoncry VAR_TEMP_4` (o comando passa por `VarGet`); `UBPartnerShrinks` não sai do tile, porque o Cosmoem flutua. |
| Type: Null distinto do Silvally | Objeto próprio em (19,49); o Silvally libera (19,50) indo a (18,50); os dois na tela juntos. |
| Origem do Type: Null (auditoria V3) | `UBGladionGiftFound` reescrito: veio de Alola com o Gladion; a Route 45 é onde treinam. |
| Confiança vinda da campanha (V3) | `UBGladionGiftOffer`: "I've seen how you treat your Pokémon." |
| Retry sem reapresentar ninguém | `FLAG_BLACKTHORN_UB_ENGAGED` + `StageUBRetry` (`setobjectxyperm`) + `UBSceneRetry` + quatro textos próprios. |
| Falha de entrega não repete a batalha | `FLAG_BLACKTHORN_TYPE_NULL_PENDING` + `StageGiftPending` + `UBGiftRetry` no script de objeto do Gladion. |
| Resultado sem vitória não diz que fugiram | `UBUnresolved`. |
| Trilha | `fadeoutbgm 4` no aviso, `playbgm MUS_DP_LEGEND_APPEARS, TRUE` na ruptura, `fadedefaultbgm` depois de a rua ser declarada limpa. O `playbgm` é repetido no retry. |
| Bilhete da porta curto | `UBDoorLocked` sem a narração anterior. |
| Briefing da M2 coerente | Chama o Necrozma pelo nome e já diz o que a Anabel procura: cortar a ligação. |
| Balanceamento | **Intocado.** |
| Ligação do Looker, uma por dia, e o pattern do arco | §15.3. |

### 15.2. Como o retry foi resolvido, e por que precisou de flag persistente

O blackout **recarrega o mapa**, e é isso que mata o retry barato: `FLAG_TEMP_*`
e `VAR_TEMP_*` são zerados por `ClearTempFieldEventData`, então na volta não
existe nenhum vestígio de que a fenda foi aberta. Sem um bit persistente, a
segunda tentativa reapresenta o resgate de surpresa, o reconhecimento da Clair e
a identificação do Necrozma — que é exatamente o que o roteiro proíbe.

`FLAG_BLACKTHORN_UB_ENGAGED` é setada no **último** beat antes da escolha, o que
dá a linha de corte certa: tudo que é apresentação fica acima dela, e nada abaixo
dela é apresentação. O `ON_TRANSITION` lê a flag e reconstrói a rua com
`setobjectxyperm` — e não com `setobjectxy`, porque os templates são recarregados
do header do mapa a cada load, então a mudança vale para esta sessão de mapa e
some sozinha (é o mesmo motivo pelo qual `BlackThornCity_EventScript_MoveGymBoy`
vive no `ON_LOAD`).

`MOVEMENT_TYPE_FACE_DOWN` do Gladion e do Silvally virou `MOVEMENT_TYPE_FACE_LEFT`
no `map.json`: no primeiro encontro eles nascem fora da câmera e o `applymovement`
manda em tudo, mas num retry eles estão **parados** na rua desde o load, e olhar
para o sul enquanto duas Ultra Beasts estão a oeste é errado de graça.

### 15.3. A convocação por telefone

O pedido era "o Looker te liga para te chamar a Olivine, uma vez por dia". A
auditoria V3 do roteiro (§13.3 dele) foi mais longe e transformou isso em **gate
do briefing**: até a ligação acontecer, a casa em Olivine não encena nada e só dá
uma fala de espera.

Implementação:

| Peça | Onde |
|---|---|
| Quando ligar | `ShouldDoRiftMissionCall`, `src/field_control_avatar.c`, dentro de `TryStartStepCountScript` — ao lado das ligações do Wally e do Scott. É o único lugar que só roda em controle livre. |
| O que a ligação diz | `RiftMissions_EventScript_LookerCall`, `data/scripts/rift_missions.inc` (arquivo novo, incluído em `data/event_scripts.s`, `extern` em `include/event_scripts.h`). Um texto por estado; a ligação **nomeia a próxima cidade**, e o briefing dá o plano. |
| Uma por dia | `FLAG_DAILY_LOOKER_CALL`, daily flag. `ClearDailyFlags` a limpa na virada da data — calendário do jogo, não 24 h. |
| Convite pendente | `FLAG_RIFT_LOOKER_SUMMONS`, persistente. Enquanto setada, nenhuma ligação nova; enquanto limpa, a casa só espera. Limpa por `BriefingTalk` e pela cena de reunião. |
| Nada de ligação com pendência | A predicate recusa com `FLAG_BLACKTHORN_TYPE_NULL_PENDING` setada. **Toda missão futura que possa terminar com presente pendente precisa entrar nessa condição.** |
| Fim de missão conta como a ligação do dia | `setflag FLAG_DAILY_LOOKER_CALL` nos cinco scripts que fecham uma missão (New Bark ×2, Blackthorn, Mahogany, Cherrygrove). |
| Estados | 4, 6, 8, 10. **O 2 está fora**: a convocação de Blackthorn é a cena de ligação em New Bark, e o roteiro §4 diz que aquele convite "persiste até o briefing, sem expirar nem produzir lembretes nos dias seguintes". |

**Por que o estado 2 não é gated pela flag do convite.** Duas razões, e a segunda
é a que decide: o convite dele já foi entregue por uma cena dedicada, e um save
feito antes desta revisão está no estado 2 **sem** a flag. Gating o 2 travaria
esse save para sempre, porque o 2 também não está na lista de ligações.

**Por que a ligação toca depois, e não no passo seguinte ao fim da missão.** O
Looker acabou de pedir em pessoa, na rua, que o jogador espere a ligação. Ligar um
passo depois seria ridículo. Por isso o script que fecha a missão **gasta** a
ligação do dia. Quem espera um dia recebe o telefone; quem não espera nada, não
recebe ligação nenhuma — e continua sem briefing, que é o ponto.

### 15.4. Arquivos tocados na revisão 5

| Arquivo | O quê |
|---|---|
| `include/constants/flags.h` | `FLAG_BLACKTHORN_UB_ENGAGED` 0x1047, `FLAG_BLACKTHORN_TYPE_NULL_PENDING` 0x1048, `FLAG_RIFT_LOOKER_SUMMONS` 0x1049, `CUSTOM_FLAGS_END`; `FLAG_DAILY_LOOKER_CALL` reclamada de `FLAG_UNUSED_0x94F` |
| `src/field_control_avatar.c` | `ShouldDoRiftMissionCall` + o gancho no `TryStartStepCountScript` |
| `data/scripts/rift_missions.inc` | **novo** — a ligação e os quatro textos |
| `data/event_scripts.s`, `include/event_scripts.h` | ligação do arquivo novo |
| `data/maps/BlackthornCity/map.json` | 6 objetos novos (ruptura, 4 parceiros, Type: Null); Gladion e Silvally olhando oeste; script no Gladion |
| `data/maps/BlackthornCity/scripts.inc` | seção da M1 reescrita inteira: visibilidade em três formas, cena, retry, contenção, parceiro-ator, presente, pendência, textos |
| `data/maps/NewBarkTown/scripts.pory` | texto da ligação; daily flag na ligação e no fim da M4 |
| `data/maps/OlivineCity_House1/scripts.pory` | briefing M1 em cinco textos; falas de férias e de "vá na frente"; gate do convite nos estados 4/6/8/10; duas falas de espera; continuidade do briefing M2 |
| `data/maps/Mahoganytown/scripts.inc`, `data/maps/CherrygroveCity/scripts.pory` | daily flag no fim da missão |
| `docs/SOULGOLD_FLAGS_AUDIT.csv` | regenerado |
| `.claude/rift_missions/SOULGOLD_RIFT_MISSIONS_DESIGN.md` | regras comuns novas e reescritas + §29 |

## 16. Reflexão — o que esta revisão ensina para as próximas missões

Escrito depois de implementar, olhando o código e não o plano.

### 16.1. O que o roteiro V2 fez de certo, e vale copiar

- **Ele separa contrato de fala.** As seções 2, 14, 15 e 17 dele são contratos
  ("a oscilação é obrigatória em todos os ramos", "o parceiro aparece antes de a
  fala descrevê-lo", "não fazer substituição cega por nome de label"), e é isso
  que torna o roteiro implementável sem adivinhação. Roteiro que é só diálogo
  obriga quem implementa a inventar a encenação, e aí a cena fica com a cara de
  quem digitou, não de quem escreveu.
- **Ele diz o que NÃO fazer, por beat.** "Não afirmar que um único golpe derrubou
  as duas", "não dizer que Cosmoem anda se o asset apenas flutua", "não declarar
  imunidade universal a Poké Balls". Cada uma dessas frases economizou um erro
  que compilaria limpo.
- **Ele avisa onde não tem certeza.** "Não pressupor slot livre para um objeto
  adicional", "este roteiro não inventa um ID de flag disponível". Isso é melhor
  do que um número errado com cara de decisão.

### 16.2. O que ficou frágil, e onde vai doer

- **Uma caixa por falante multiplica o número de labels.** A seção da M1 passou de
  ~30 para ~50 textos. O ganho (plaquinha sempre certa) é real, mas o custo é que
  qualquer reordenação de beat agora move cinco `msgbox` em vez de um. A M2, a M3
  e a M4 ainda têm caixas com três falantes dentro; quando forem convertidas,
  converta **junto com a ordem dos beats**, não depois.
- **`FLAG_TEMP_5` partilhada por quatro templates é econômica e silenciosa.** Se
  alguém acrescentar um quinto parceiro e esquecer de dar `addobject` só a um
  deles, aparecem dois Pokémon no mesmo tile e o build fica limpo. O comentário
  no `ApplyUBVisibility` é a única proteção.
- **O retry depende de o `ON_TRANSITION` rodar antes do primeiro spawn.** É
  verdade hoje e é a base de todo `ApplyUBVisibility` do arco, mas é uma
  propriedade do motor que nenhum teste cobre. Se um dia o retry voltar com o
  elenco nos tiles de template, este é o primeiro lugar a olhar.
- **A predicate da ligação conhece uma flag de Blackthorn.**
  `ShouldDoRiftMissionCall` cita `FLAG_BLACKTHORN_TYPE_NULL_PENDING` por nome.
  Funciona, e é honesto, mas é acoplamento: a segunda missão que puder terminar
  com presente pendente vai ter de acrescentar outra linha ali, e ninguém vai
  lembrar. Se chegar a três, vale uma flag genérica "pendência de missão".
- **`OlivineCity_House1_Text_WaitForMahoganyCall` tem nome errado de propósito.**
  É o nome que o roteiro fixou, e é usado nos quatro estados de espera, não só no
  de Mahogany. Mantido para o roteiro e o código concordarem no `grep`.

### 16.3. O que o arco herda daqui, e ainda não cumpre

1. **Checkpoint de retry** — M2, M3 e M4 reapresentam a cena inteira depois de um
   blackout. A M2 é a pior: ela tem duas rodadas de batalha.
2. **Passe de diálogo pela identidade do Necrozma.** Ele é nomeado em Blackthorn.
   As falas de cena das outras três ainda tratam o nome como segredo em alguns
   pontos. O briefing da M2 já foi corrigido; o resto é diálogo, não contrato.
3. **Trilha da ruptura** na M2 e na M4.
4. **Convocação por telefone** já vale para as quatro, porque o mecanismo é
   global — mas cada missão precisa conferir que o **fim** dela seta
   `FLAG_DAILY_LOOKER_CALL` (as cinco já setam) e que a despedida dela pede para
   esperar a ligação em vez de mandar o jogador a Olivine. **Só a M1 pede.**
5. **Tentativa de contenção** — a M1 planta "essa ainda está ligada à fenda". A
   M2 responde com a barreira de gelo, o que já estava escrito; a M3 e a M4 não
   têm nada equivalente e deviam ganhar, porque a pista agora existe.

### 16.4. O que só o runtime decide

- Se o sprite da ruptura em (14,51) **lê** como uma fenda ao lado do Necrozma ou
  como um enfeite no chão embaixo dele. Ele é `inanimate`, então não tem
  animação própria: quem faz a fenda "oscilar" é o tremor de câmera.
- Se a diferença de ritmo entre Buzzwole e Pheromosa é visível de verdade ou se o
  `delay_16` só parece lag.
- Se o arremesso da Anabel sem sprite de Ball lê como um arremesso.
- Se cinco caixas seguidas de briefing, sem a caixa descer entre elas, ficam
  confortáveis de ler.
- Se a ligação do Looker tocando em qualquer mapa incomoda (dentro de caverna,
  no meio de uma dungeon). O filtro pronto é o `MapAllowsMatchCall` do Match
  Call, e é uma linha.
