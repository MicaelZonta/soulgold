# Nexus — implementação do modo Daily

Implementado em 27/09/2026, em modo **esqueleto** (skill `evento-esqueleto`):
estado, sorteio, salas, lutas, boss, prêmio e presente funcionam de ponta a
ponta; falas de sala e coreografia são mínimas (`@ SKELETON:`).
Regras: [`NEXUS_REGRAS.md`](NEXUS_REGRAS.md) — vencem este arquivo.

## 1. Status e escopo

- **Do quê até o quê:** o jogador fala com a fenda do Altar (estado ≥ 16 de
  `VAR_RIFT_MISSIONS_STATE`), passa pela checagem Traditional (R10), entra no
  mapa `Nexus`, escolhe 1 de 3 treinadores em 4 salas, enfrenta o campeão do
  lendário (com o Looker File do dia no chão, R18), enfrenta o lendário na
  forma superior (R19, sem captura na batalha), leva o **fragmento** dele
  com uma bola da bolsa (R17), ganha o prêmio (R9), e a dimensão desmorona e
  o expulsa para o Altar.
- **Revisão 3 (27/09/2026):** fragmento, Looker Files, forma superior —
  build limpo, **ainda não testada em runtime** (itens novos no §9).
- **Build:** limpo. **Runtime:** primeiro teste do autor em 27/09/2026 achou
  seis defeitos; todos corrigidos na revisão do mesmo dia (§8 tem a lista, e
  o checklist §9 foi refeito para revalidar).
- Só o modo **Daily** (R4). Gauntlet/Infinito não têm estrutura preparada.

## 2. Como o código está dividido — o que mexer para cada ideia

O pedido foi "fácil de reiterar, ideias e regras desacopladas". A divisão é:

| Camada | Arquivo | O que tem | Muda quando |
|---|---|---|---|
| **Conteúdo** | `src/data/nexus/trainers.h` | pool de treinadores (uma linha cada) | entra/sai treinador |
| | `src/data/nexus/legendaries.h` | pool de lendários: campeão, R1, parâmetros do boss, script extra | entra/sai lendário, balanceamento do boss |
| | `src/data/nexus/prizes.h` | grupos de prêmio com peso | muda o prêmio |
| | `src/data/nexus/mythicals.h` | míticos que ocupam vaga de lendário | tabela de míticos muda |
| | `data/scripts/nexus.inc` | as lutas (falas R16) e os Looker Files (R18) | falas, lutas novas, cadernos |
| | `src/data/trainers.party` | os times | time |
| **Regras** | `src/nexus.c` | um bloco por regra: R15 estado, R3 sorteio, R1 filtro, R5 salas/portas, R2/R6/R8 boss, R9 prêmio, R10 Traditional | uma regra muda |
| | `include/constants/nexus.h` | forma do Daily: nº de salas, portas, progresso | estrutura muda (ex.: 5 salas) |
| **Fluxo** | `data/maps/Nexus/scripts.inc` | salas, portas, textos, coreografia | a cena muda |
| **Entrada** | `data/maps/SunMoonAltar/scripts.inc` (`SunMoonAltar_EventScript_Rift`) | R10 + warp | a porta de entrada muda |

O script do mapa **não sabe** quem são os treinadores nem qual é o lendário:
pergunta tudo ao C pelos specials `Nexus_*`. O C **não sabe** de objetos,
flags temporárias ou textos do mapa.

### Receitas

**Treinador novo no pool**
1. Time `TRAINER_NEXUS_<NOME>` no `.party` (ID aposentado < 1056, R16) e o
   `#define` em `opponents.h`.
2. `Nexus_EventScript_<Nome>_Fight` e `_ChampionFight` em
   `data/scripts/nexus.inc` (copiar um par existente).
3. Uma linha `X(NOME, Nome, TRAINER_NEXUS_NOME, OBJ_EVENT_GFX_NOME)` em
   `src/data/nexus/trainers.h`.
Pronto: aparece nas salas, escala pelo R2 (o level scaling lê a mesma tabela)
e fica disponível como campeão.

**Lendário novo no pool** — uma linha em `src/data/nexus/legendaries.h` com o
campeão (que precisa estar na tabela de treinadores), `requiresCaught` pelo
R1 (conferir [`POOL_LENDARIOS.md`](POOL_LENDARIOS.md)) e os parâmetros do boss.
Precisa ter sprite de overworld (`OBJ_EVENT_GFX_SPECIES`).

**Looker File de um lendário** (R18) — texto `Nexus_Text_<Conceito>_LookerFile`
e script `Nexus_EventScript_<Conceito>_LookerFile` (msgbox + `return`) em
`data/scripts/nexus.inc`, e `NEXUS_LOOKER_FILE(<Conceito>)` +
`NEXUS_LOOKER_FILE_EXTERN(<Conceito>)` em `legendaries.h`. A abertura ("a
notebook lies open…") e o fecho ("dated a day that has not happened yet") são
comuns, no script do mapa.

**Algo especial depois do fragmento** — script em
`data/scripts/nexus.inc` terminando em `return`, apontado em
`.afterBossScript` da linha do lendário. Estado "já entregue hoje": bit 12
(`Nexus_IsGiftTaken`/`Nexus_MarkGiftTaken`). Use `NEXUS_AFTER_BOSS(<Conceito>)`
+ `NEXUS_AFTER_BOSS_EXTERN(<Conceito>)` em `legendaries.h`. Em uso desde
28/09/2026 pelos **drops de item de forma** (R22): Kyurem (DNA Splicers),
Genesect (um Drive que falta, via `GetRandomMissingItemInRange`) e Zygarde
(Zygarde Cube). O script roda depois do fragmento **e** de novo na chegada ao
dia já concluído, então bolsa cheia não perde o drop no mesmo dia.

**Prêmio** — editar `sNexusPrizeGroups` (grupo = faixa contínua de IDs + peso).

**Mudar uma regra** — só o bloco dela em `src/nexus.c`. Ex.: salas com 2
portas = `NEXUS_DOORS_PER_ROOM`; filtro diferente de lendário =
`IsLegendaryEligible`; nível do boss = `GetBossLevel`.

**Testar sem jogar tudo** — menu de debug, *Rift Missions*:
`Nexus: enter` (entra na sala 1 de qualquer lugar, sem a checagem R10),
`Nexus: new day` (estado zerado e sorteio novo), `Nexus fights…` (cada luta
isolada).

## 3. Estado

| Constante | Valor | Arquivo |
|---|---|---|
| `VAR_NEXUS_DAILY` | `0x4124` | `include/constants/vars.h` |
| `FLAG_DAILY_NEXUS_NEW_DAY` | `DAILY_FLAGS_START + 0x31` (era `FLAG_UNUSED_0x951`) | `include/constants/flags.h` |
| `FLAG_NEXUS_RULES_EXPLAINED` | `0x1051` (CUSTOM) — regras explicadas 1x por save, na primeira chegada | `include/constants/flags.h` |
| `FLAG_UNUSED_0x949` | `DAILY_FLAGS_START + 0x29` — **era `FLAG_DAILY_ALTAR_RIFT`**, livre | `include/constants/flags.h` |

`VAR_NEXUS_DAILY` (R15; campos lidos e escritos só em `src/nexus.c`):

| Bits | Campo | Escreve | Lê |
|---|---|---|---|
| 0–7 | porta escolhida nas salas 1–4 (2 bits; 3 = nenhuma) | `Nexus_ChooseDoor`, no SIM | `GetDoorState`, `Nexus_IsRoomChosen` |
| 8–10 | progresso: 0–5 lutas vencidas, 6 = boss nocauteado (fragmento esperando), 7 = fragmento levado | `Nexus_RecordFightWon` logo após a vitória; `Nexus_RecordBossBeaten`; `Nexus_RecordCapture` | tudo |
| 11 | prêmio R9 pego hoje | `Nexus_MarkPrizeTaken` | `Nexus_GetPrize` |
| 12 | presente pós-boss pego hoje (`afterBossScript`: drops do R22) | `Nexus_MarkGiftTaken` | `Nexus_IsGiftTaken` |
| 13–15 | **sala onde o jogador está** (0–5) | `Nexus_EnterFromAltar`, `Nexus_AdvanceRoom`, `Nexus_LeaveToAltar` | `Nexus_BeginMapLoad`, specials de porta |

Valor inicial do dia: `0x00FF` (portas "nenhuma", resto zero).

**Invariantes**
- `sala ≤ progresso` sempre; se `progresso ≥ 6`, `sala = 5` (`ClampRoom`, a
  cada load).
- Porta escolhida numa sala < progresso existe (escrita antes da luta).
- Virada do dia: `ClearDailyFlags` limpa `FLAG_DAILY_NEXUS_NEW_DAY` **e**
  `UpdatePerDay` troca a `dailySeed` no mesmo instante; o primeiro toque no
  Nexus depois disso zera a var (padrão do Kurt).
- O sorteio **não** é salvo: é função de `dailySeed` (+ Pokédex, pelo R1).

**Sorteio** (`src/nexus.c`, `DailyHash` com um *salt* por uso):
- lendário: entre os elegíveis pelo R1, `hash % n`;
- salas: todos os treinadores menos o campeão do dia, embaralhados
  (Fisher–Yates); porta *k* da sala *r* = posição `3r + k`. As 3 portas de
  uma sala são sempre pessoas diferentes; com 9 não-campeões a sala 4 repete
  as pessoas da sala 1 (some sozinho quando o pool passar de 12);
- prêmio: grupo por peso, depois item do grupo;
- forma superior do boss (R19): `GetBossSpecies`, entre os alvos de
  Mega/Primal/Ultra Burst da espécie e as fusões em que ela é o
  `targetSpecies1` de `gFusionTablePointers`, `hash % n` (até dois passos).

**Temporários do mapa `Nexus`**: `FLAG_TEMP_1–3` treinadores O/N/L,
`4–6` portais O/N/L, `7` lendário/fragmento, `8` prêmio, `9` Looker File. `VAR_TEMP_0` saída sul,
`1` trava de chegada, `3` resultado de batalha (macro `nexus_fight`),
`4` porta em uso, `6` item do prêmio. `VAR_OBJ_GFX_ID_0–2` sprites das
portas, `_3` o lendário.

⚠ **Esconder qualquer coisa no Nexus é `setflag FLAG_TEMP_n` + `removeobject`,
nessa ordem.** Os braços da cruz ficam longe: o objeto a fechar quase sempre
está **despawnado** (fora do retângulo da câmera), e `removeobject` em objeto
despawnado é no-op silencioso que **não** seta flag nenhuma — andando até lá,
`TrySpawnObjectEvents` devolvia o treinador vencido e o portal fechado (o bug
"a Elesa continuou lá" do teste de 27/09). O `setflag` explícito é o que
segura; o `removeobject` só despacha quem está em cena.

## 4. O mapa `Nexus`

`data/maps/Nexus/` — novo, `MAP_TYPE_INDOOR`, **mesmo layout** da arena
(`LAYOUT_ULTRA_SPACE_ARENA`), grupo `gMapGroup_RiftMissions`. Tipo `INDOOR`
de propósito: o par `ROUTE → UNDERGROUND` é o da transição de caverna
suspeita da tela branca (doc do Altar §18.5); `ROUTE → INDOOR` não tem
transição especial. Uma sala = um load do mesmo mapa.

```
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
y=  1  # # # # # # # # # . P . # # # # # # # # #     P portal norte (10,1)
y=  4  # # # # # # # # # . T . # # # # # # # # #     T treinador norte (10,4)
y=  6  # # # # # # # # . . L . . # # # # # # # #     L lendário (10,6)
y=  7  # # # # # # # # . . $ . . # # # # # # # #     $ prêmio (10,7)
y= 13  # # # # # # # # . . . . F # # # # # # # #     F Looker File (12,13), só sala 4
y= 10  . P . . T . . . . . . . . . . . T . . P .     oeste T(4,10) P(1,10) · leste T(16,10) P(19,10)
y= 19  # # # # # # # # # . @ . # # # # # # # # #     @ chegada (10,19), olhando para cima
y= 20  # # # # # # # # # x x x # # # # # # # # #     x saída para o Altar (14,11)
```

| Sala (bits 13–15) | Mostra |
|---|---|
| 0–3, progresso = sala, sem escolha | 3 treinadores + 3 portais |
| 0–3, progresso = sala, porta escolhida (voltou depois de perder) | só o treinador e o portal escolhidos |
| 0–3, progresso > sala | só o portal escolhido (passa sem lutar, R3) |
| 4 (campeão) | treinador + portal do norte + caderno do Looker File (R18) |
| 5 (boss), progresso 5 | o lendário |
| 5, progresso 6 | o fragmento (mesmo objeto, sprite da primeira forma) |
| 5, progresso 7 | a bola do prêmio, se ainda não pega |

## 5. Resultados

**Luta de treinador** (`nexus_fight`, sem blackout, sem perder dinheiro):

| Resultado | O que acontece |
|---|---|
| `WON` | progresso +1 na hora; treinador some num pulso branco; "the portal flares open"; o portal leva à sala seguinte |
| qualquer outro | "pushes you out" → Altar (14,11), `sala = 0`. Escolha e progresso ficam |

A macro `nexus_fight` seta `B_FLAG_NO_WHITEOUT` antes e **limpa sempre**
depois. (A versão anterior tentava "salvar e restaurar" lendo `VAR_RESULT`
após `checkflag` — que escreve `comparisonResult`, não `VAR_RESULT` — e podia
vazar a flag ligada para o resto do jogo.)

**Boss** (`B_FLAG_NO_WHITEOUT` + `B_FLAG_NO_CATCHING`; `CB2_EndScriptedWildBattle` respeita a no-whiteout):

| Resultado | O que acontece |
|---|---|
| `WON` (nocaute) | progresso 6 na hora; "it comes apart"; o objeto em (10,6) renasce com o sprite do **fragmento** (`VAR_OBJ_GFX_ID_3`); segue direto para a oferta |
| `RAN`, `MON_FLED` | continua ali |
| `LOST`, `DREW`, `FORFEITED` | expulso, como numa luta perdida |

**Fragmento** (`Nexus_EventScript_Fragment`, também ao falar com ele depois):
espaço na equipe/PC → bola → oferta. UB: `checkitem ITEM_BEAST_BALL` e SIM/NÃO;
outro: SIM/NÃO e `chooseitem POCKET_POKE_BALLS`. `Nexus_GiveFragment` cria a
primeira forma no nível 1, com os IVs perfeitos do boss e a bola escolhida;
só depois do `MON_GIVEN_*` a bola é removida e o progresso vai a 7. Sem bola,
sem espaço ou cancelou: nada gravado, o fragmento espera.

**O final** (`Nexus_EventScript_Finale` → `_Collapse`): prêmio do R9 com
`checkitemspace` antes (`finditem`; bolsa cheia deixa a bola no chão para a
visita quieta do mesmo dia), depois tremor (`ShakeCamera`, padrão do Altar),
dois flashes brancos (`fadescreenswapbuffers`, nunca `fadescreen` — o fade
comum compõe o tint de horário sobre si mesmo e suja a tela a cada flash),
`SE_M_EARTHQUAKE`/`SE_M_EXPLOSION` e warp para o Altar. Reentrar num dia
concluído abre direto na sala final quieta (`ClampRoom`), que reoferece
presente e prêmio pendentes.

## 6. Arquivos tocados

- [x] `include/constants/nexus.h`, `include/nexus.h`, `src/nexus.c`, `src/data/nexus/*.h` — novos
- [x] `data/maps/Nexus/map.json`, `scripts.inc` — novos; `data/maps/map_groups.json`; `data/event_scripts.s` (include do mapa e de `constants/nexus.h`)
- [x] `data/specials.inc` — specials `Nexus_*`
- [x] `data/scripts/nexus.inc` — lutas e os 10 Looker Files (o `AfterBoss_Poipole` saiu na revisão 3)
- [x] `include/constants/vars.h`, `include/constants/flags.h`, `docs/SOULGOLD_FLAGS_AUDIT.csv`
- [x] `src/level_scaling.c`, `src/data/level_scaling_rules.h` — `IsNexusTrainer` lê a tabela do Nexus; a lista duplicada `sNexusTrainerIds` saiu
- [x] `src/battle_setup.c` — `CB2_EndScriptedWildBattle` respeita `B_FLAG_NO_WHITEOUT`
- [x] `src/battle_bg.c` — `MAP_BATTLE_SCENE_ULTRA_SPACE` vence a classe do treinador (Leader/Champion) e o branch de lendário: toda batalha no Nexus/arena usa o campo Ultra Space
- [x] portal próprio: `graphics/object_events/pics/misc/nexus_portal.png` (+ `.pal`, gerados por `dev_scripts/sprites/nexus_portal_gen.py`), `OBJ_EVENT_GFX_NEXUS_PORTAL`/`OBJ_EVENT_PAL_TAG_NEXUS_PORTAL`, registro nos 5 arquivos de object events + `spritesheet_rules.mk` (`-mwidth 4 -mheight 4`)
- [x] `data/maps/SunMoonAltar/scripts.inc` — fenda sempre aberta no ≥ 16, R10, warp para `MAP_NEXUS`, fala da Anabel pelo `Nexus_IsDoneToday`
- [x] `data/maps/UltraSpaceArena/scripts.inc` — saiu o esqueleto da "fenda vazia" (inalcançável)
- [x] `src/debug.c`, `data/scripts/debug.inc` — `Nexus: enter`, `Nexus: new day`
- [x] revisão 3: caderno `OBJ_EVENT_GFX_NEXUS_LOOKER_FILE` (16x16, 1 quadro; `graphics/object_events/pics/misc/nexus_looker_file.png` + `.pal`, gerados por `dev_scripts/sprites/nexus_looker_file_gen.py`; registro nos 5 arquivos + `spritesheet_rules.mk` `-mwidth 2 -mheight 2`); objeto `LOCALID_NEXUS_LOOKER_FILE` (9) no fim do `map.json`

## 7. Esqueleto × evolução

| Simples hoje | Como evoluir |
|---|---|
| Regras numa narração única; salas silenciosas | skill `evoluir-historia-de-evento`; um fragmento do dia pode vir de um campo novo na linha do lendário (mas chegada de sala fica **silenciosa** — decisão do autor, 27/09) |
| Fechamento/vitória num pulso branco + `SE_M_TELEPORT` | coreografia por treinador (cada um sai do seu jeito) |
| Desmoronamento: 2 tremores + 2 flashes + warp | queda de pedaços do cenário (`setmetatile`), música cortando |
| Layout emprestado da arena | layout próprio: só `map.json` + coordenadas do cabeçalho do script |
| Boss com `NEXUS_BOSS_DEFAULT` (4 barras, x140) | parâmetros por lendário na tabela |
| Texto R10 da Anabel genérico | voz da Anabel |

**Não pode regredir:** layout de bits da var; `sala ≤ progresso`; escrita do
estado **no momento** do evento (R15); SIM/NÃO antes de `Nexus_ChooseDoor`;
só `WON` avança; nenhuma cura dentro do Nexus (R5.2); espaço conferido antes
de oferta de Pokémon ou item; objetos novos no **fim** de `object_events`.

## 8. Pendências e riscos

**Corrigido em 27/09/2026, após o primeiro teste do autor** (todos
compilavam limpo e quebravam no jogo):

1. Treinador vencido/portas fechadas **voltavam** ao andar pelo mapa:
   `removeobject` em objeto despawnado (braço longe da câmera) é no-op e não
   seta flag → agora todo esconder é `setflag FLAG_TEMP_n` + `removeobject`.
2. A tela ia **sujando** a cada fade e só limpava saindo e entrando:
   `fadescreen` compõe o tint de horário sobre si mesmo → todo flash que
   volta para o mesmo mapa virou `fadescreenswapbuffers`.
3. `B_FLAG_NO_WHITEOUT` podia **vazar ligada** para o resto do jogo: a macro
   lia `VAR_RESULT` depois de `checkflag` (que escreve `comparisonResult`) →
   agora seta antes e limpa sempre.
4. Batalha de treinador no Nexus abria no **cenário de Líder** (Elesa é
   `TRAINER_CLASS_LEADER`) e o boss no de **prédio** (mapa INDOOR) →
   `MAP_BATTLE_SCENE_ULTRA_SPACE` agora vence os dois em `src/battle_bg.c`.
5. A sala 4 **repetia o trio** da sala 1 (wrap do embaralhado único) →
   sorteio por sala, sem o campeão e sem o trio da sala anterior.
6. Nocaute no boss não dava **nada** e o prêmio ficava inalcançável sem
   capturar → nocaute entrega o lendário (rendição) e o dia fecha com
   prêmio + desmoronamento nos dois desfechos.

**Ainda em aberto:**

- **Reconfirmar com o autor:** (a) derrota fora do boss deixa o time
  desmaiado no Altar e ninguém cura ali — R3 diz "sai e pode curar", mas não
  há PC no Altar; (b) bits 13–15 da var passaram a guardar a sala.
- R1 muda o sorteio no mesmo dia se o jogador capturar um lendário fora dali
  (aceito pelo R15); a troca pode mudar os treinadores atrás das portas no
  meio de uma tentativa.
- Sprite grande de UB em (10,6) pode sobrepor a parede de cima — conferir.
- O portal novo (32x32) encosta na parede atrás dele nos três braços — é
  intencional (portal encaixado no arco), conferir se agrada em runtime.

## 9. Teste em runtime (refeito para a revisão de 27/09)

- [ ] Estado 16: a fenda do Altar aparece sempre, várias entradas no mesmo dia
- [ ] R10: 2 lendários / 2 semi / 2 Megas na equipe → recusa com a fala certa, nada escrito
- [ ] **Primeira entrada do save**: narração das regras; segunda entrada em diante: chegada muda em toda sala
- [ ] Sala 1: 3 treinadores diferentes; NÃO não muda nada; SIM fecha os outros dois num pulso branco
- [ ] **Vencer, depois andar até os DOIS braços fechados**: nada reaparece (era o bug da Elesa)
- [ ] Vários flashes/entradas seguidas: a tela não escurece nem suja (era o "limpa a tela")
- [ ] **Depois de uma luta do Nexus, perder uma batalha normal fora dele**: blackout normal (a no-whiteout não vazou)
- [ ] Toda batalha (sala, campeão com Steven/Elesa, boss) abre no **campo Ultra Space**
- [ ] Sala 4 **nunca** repete o trio da sala 1; salas vizinhas não repetem ninguém
- [ ] Portal novo: vórtice animado nos três braços, sem paleta estourada, visível de dia e de noite
- [ ] Vencer → portal leva à sala 2; salvar e carregar em cada sala
- [ ] **Perder de propósito** na sala 2 → Altar, sem dinheiro perdido; voltar: sala 1 só com o portal escolhido, sala 2 com o mesmo treinador
- [ ] Sair pelo sul no meio e voltar: mesmo resultado
- [ ] Campeão: falas do lendário + `_ChampionAfter`
- [ ] Boss: nível = maior da equipe; 3 IVs 31; perder, fugir → continua ali
- [ ] **Jogar bola no boss**: "Poké Balls cannot be used right now!"
- [ ] **Nocautear o boss**: texto do desfazer, sprite troca para o fragmento, oferta
- [ ] UB **sem Beast Ball**: recusa, nada gasto; sair e voltar → abre na sala 5 com o fragmento esperando
- [ ] UB **com Beast Ball**: SIM gasta 1 Beast Ball; fragmento nível 1, primeira forma (Naganadel → Poipole), 3 IVs 31, na Beast Ball; prêmio + desmoronamento
- [ ] Lendário não-UB (quando entrar no pool): abre o bolso de bolas; cancelar não gasta nada; a bola escolhida é a do Pokémon
- [ ] Party E PC cheios: fragmento espera, nada gasto
- [ ] Sala do campeão: caderno em (12,13) com o Looker File do lendário do dia; salas 1–4 e 6 sem caderno; sprite visível parado
- [ ] Forma superior (quando entrar lendário com Mega): boss na Mega, forma sorteada muda com o dia
- [ ] Prêmio com a bolsa cheia: desmoronamento mesmo assim; voltar no dia acha a bola na sala quieta
- [ ] Reentrar num dia concluído: abre direto na sala final quieta
- [ ] `Nexus: new day` → sorteio novo; virar o relógio de verdade → idem
- [ ] Battle Format Singles e Doubles nas lutas de treinador
