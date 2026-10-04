# B08 — Flags: pendências da auditoria de 24/09 e limite de objetos por mapa

**Gravidade:** BAIXA · **Status:** flags CORRIGIDAS em 30/09/2026 (ver revisão abaixo); limite de objetos continua aberto

## Estado do catálogo de flags (30/09/2026)

`python3 dev_scripts/flag_audit.py --csv` gerado num arquivo à parte e
comparado com `docs/SOULGOLD_FLAGS_AUDIT.csv` do `HEAD`: **nenhuma flag mudou
de valor ou de status**. Nenhuma flag fora do array de save. O trabalho recente
(Berry Master partes 1-6, limites do engine) não criou flag órfã.

Continuam em aberto os itens da seção 7 de `.claude/SOULGOLD_FLAGS_AUDIT.md`:

| Item | Resumo | Efeito no jogo |
|---|---|---|
| 7.3 | `FLAG_EXP_SHARE` (0x4A6) setada 4× no lab do Elm, ninguém lê | nenhum (a que funciona é `FLAG_EXP_SHARE_OPTION`) |
| 7.4 | `FLAG_TRAINER_LEVELSCALING`, `FLAG_WILD_LEVELSCALING`, `FLAG_LEVEL_SCALING_ON` (Route 36) | o NPC "liga" algo que não existe; scaling é fixo em `level_scaling.h` |
| 7.5 | `FLAG_HIDE_ILEX_FOREST_KURT`, `FLAG_HIDE_OLIVINE_PORT_OAK`, `FLAG_HIDE_ROUTE22_JANINE`: flags de ocultação que nenhum `map.json` usa | esses NPCs não somem pela flag |
| 7.6 | 5 flags lidas e nunca escritas (`FLAG_SYS_LAKE_OF_RAGE_TIDE`, `FLAG_DAILY_BUG_CONTEST_COMPLETED`, ...) | ramo "já fiz" inalcançável |
| 7.7 | `FLAG_HIDE_ROUTE34_RIVAL`, `FLAG_HIDE_SPROUT_BASEMENT_ITEM` no `map.json` e nunca escritas | objeto visível para sempre |

Achado novo desta auditoria, fora do catálogo: **B02** (`FLAG_GARBAGEFLAG`
lida como estado). O catálogo marca a flag como `EM_USO`, então o problema não
aparece lá — ele só se vê seguindo quem lê e quem escreve.

## `removeobject` que seta flag de progresso

`python3 bug/auditar_scripts.py --so REMOVE_FLAG` lista 32 pontos em que o
objeto removido tem como flag uma flag de progresso (não `FLAG_HIDE_*`/`TEMP`).
Conferidos por amostra, são intencionais (a flag de progresso é usada de
propósito como flag de ocultação: `FLAG_GLADION_VICTORY_ROAD_DONE`,
`FLAG_DELIVERED_EGG`, as grutas). Só vira bug se o `removeobject` acontecer
antes de a conquista ser verdade. Nada a fazer agora; útil ao mexer nesses
mapas.

## Objetos demais na janela de spawn

`python3 dev_scripts/limites_janela_objetos.py` (limite `OBJECT_EVENTS_COUNT`
= 16, jogador e follower inclusos). Mapas alcançáveis com mais objetos **sem
flag** do que cabem ao mesmo tempo:

| Mapa | Objetos sem flag na pior janela |
|---|---|
| `WorldHub` | 36 |
| `MauvilleCity_GameCorner` (Goldenrod) | 21 |
| `WorldHub2` | 18 |
| `RailwayCave` | 16 (+ jogador + follower) |

O excesso não trava: `TrySpawnObjectEvent` falha calado e o NPC não aparece.
Trava só se um script fizer `applymovement` + `waitmovement` num NPC que não
spawnou — `waitmovement` devolve na hora, então a cena "pula". Tratamento e
opções de aumentar o limite: skill `limites-do-engine`.

## Revisão item a item (30/09/2026)

| Item | Veredito | Ação sugerida |
|---|---|---|
| `FLAG_EXP_SHARE` (lab do Elm) | resto de antes do menu de opções (port de 11/2025); a EXP Share liga pelo rival + `FLAG_EXP_SHARE_OPTION`. Inofensivo | apagar os 2 `setflag` |
| 3 flags de level scaling (Route 36) | o upstream (Eemeliri, `fa819be537`, 04/2026) passou o scaling para o menu de opções; as flags não ligam nada. Inofensivo | apagar os 3 `setflag` |
| Kurt do Ilex | o objeto usa `FLAG_HIDE_CELEBI`, não `FLAG_HIDE_ILEX_FOREST_KURT`. Quando o Celebi aparece, o Kurt aparece junto, parado, antes da entrada dele (`addobject` não olha flag, então a cena roda) | trocar a flag no `map.json` |
| **NOVO: Ilex antes de Azalea** | as flags de esconder do Ilex (Celebi, Kurt, mestre, aprendiz, Farfetch'd 1–4) só são setadas pelo gatilho de chegada em Azalea. Vindo pela Route 34, medido na colisão + janela da câmera: Celebi, Kurt, mestre, aprendiz e Farfetch'd 3 **aparecem na tela** | setar essas flags no `ON_TRANSITION` do Ilex enquanto `FLAG_VISITED_AZALEA_TOWN` estiver limpa |
| Oak no porto de Olivine | removido de propósito pelo upstream (`96eb05b4c8`, "we ain't going to kanto"); o Kubfu que ele dava foi para a Blackthorn Cave | nada (flag morta) |
| **Janine (Route 22)** | o upstream (`666d92bda2`) tirou o objeto dela do ReceptionGate ao mover a Liga. O script dela é o único `clearflag FLAG_HIDE_DOJO_JANINE`: a **revanche dela no Dojo VIP ficou impossível** | recolocar a Janine num mapa (decisão de lugar) |
| `FLAG_SYS_LAKE_OF_RAGE_TIDE` | a maré calculada vai para `FLAG_SYS_SHOAL_TIDE`; o lago lê a flag errada. Efeito: depois do estado 14 de Mahogany o lago nunca tem tempestade (o ramo "maré alta" só sorteia 50% de tempestade; o layout é o mesmo) | ler `FLAG_SYS_SHOAL_TIDE` |
| `FLAG_DAILY_BUG_CONTEST_COMPLETED` | ramo inalcançável, mas os atendentes já somem com `FLAG_DAILY_BUG_DONE`. Inofensivo | trocar pela `FLAG_DAILY_BUG_DONE` ou deixar |
| `FLAG_NO_WT_...`, `SS_TIDAL`, `PETALBURG_MART` | só em mapas fora da ROM | nada |
| Rival da Route 34, item do porão da Sprout | **alarme falso**: `removeobject` (rival) e `finditem` do item ball setam a flag do objeto pela engine; o catálogo não enxerga | nada |
