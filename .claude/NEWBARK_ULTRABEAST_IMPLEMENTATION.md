# New Bark — Kartana + Guzzlord + Nihilego (Rift Mission 4) — plano de implementação ESQUELETO

**Status:** **esqueleto implementado** — 20/09/2026, `make -j$(nproc)` limpo.
Runtime **pendente** (checklist §10). O documento foi escrito antes do código;
onde os dois divergiram, o código venceu e a divergência está registrada em
**§12**, no fim deste arquivo. Ler §12 antes de acreditar em qualquer trecho
abaixo.
**Modo:** esqueleto (skill `evento-esqueleto`). Diálogo curto, coreografia
mínima, mas estado, visibilidade, gatilhos, batalha e retry **completos e
corretos**.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6, §6.4 (V17).
**Missões anteriores:**
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (M1),
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (M2) e
[`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (M3)
— este doc **continua** a máquina de estados das três, **substitui** o stub da
Missão 4 que a M3 deixou em `OlivineCity_House1` (§2.3 daquele doc), e o
transforma no stub da **reunião** do design §7. É a última missão do arco.

Escopo: do gancho final de Cherrygrove (o jogador volta a Olivine) até o fim do
incidente de New Bark, terminando com o gancho que convoca Lusamine, Lillie,
Gladion, Kukui, Looker e Anabel para o escritório de Olivine (design §7).

**Decisões desta missão:**
- Elenco em campo: **Looker, Anabel, Lusamine, Prof. Elm, a mãe do jogador e
  Gold/Crystal (+ Marill)**. Sete objetos de elenco — o dobro da M3. Só o
  jogador batalha; Lusamine e Anabel ficam com as outras duas UBs de forma
  narrativa.
- Local: `NewBarkTown`, **a rua em frente à casa do jogador**. O tile de fala
  do Looker é (20,12), que é **o mesmo tile onde o Fly e o blackout largam o
  jogador** — o começo mais determinístico do arco.
- **Três** Ultra Beasts, espalhadas em terra: não há água neste mapa.
- Escala: 4 barras (teto), **nível 90**, **multiplicador 150**, moveset de dois
  eixos + item (§4.6), com a ressalva condicional do design §6.
- Mesma estrutura padrão: escolha + boss simples, captura bloqueada, derrota =
  blackout e retry.
- Esta é a primeira missão que **esconde NPCs dentro de dois interiores**
  (a mãe em casa, o Elm no laboratório), porque os dois estão a um warp da cena.

---

## 0. Resumo do fluxo

```text
Cherrygrove resolvido                    VAR_RIFT_MISSIONS_STATE = 8
  └─ entrar em OlivineCity_House1 ─────▶ cena: Looker + Anabel, briefing M4 → 9
                                           + setflag FLAG_EVENT_ULTRABEAST_NEWBARK
       └─ New Bark: cidade vazia (só o elenco da missão)
            └─ Fly / blackout largam o jogador em (20,12) = o tile de fala
            └─ falar com Looker ▶ Elm dá o cronômetro ▶ SIM
                 └─ cena 100% scriptada ▶ três rupturas em terra:
                    Kartana + Guzzlord + Nihilego
                      └─ Lusamine quer as três ▶ a MÃE a faz parar
                           └─ Lusamine pergunta ▶ ANABEL revela que é Faller
                                └─ ESCOLHA (3 opções); Lusamine fica com
                                   Nihilego sempre que o jogador não escolher
                                     └─ boss simples, 4 barras, Lv90, x150
                                          ├─ perdeu / desistiu → blackout →
                                          │  (20,12) curado → flag setada → recomeça
                                          ├─ outro → reset silencioso → recomeça
                                          └─ venceu → falas por escolha → gancho
                                             → clearflag + estado 10 → warp no lugar
                                     └─ Olivine House1: stub da REUNIÃO (§7)
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_ULTRABEAST_NEWBARK` | `include/constants/flags.h` | `0x1044` | Primeira livre depois de `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` (`0x1043`). **Atualizar `CUSTOM_FLAGS_END`** para apontar nela (hoje aponta para a de Cherrygrove, `flags.h:1788`). Conferir com `grep -n "0x1044" include/constants/flags.h` antes. |
| `LOCALID_NEWBARK_UB_*` | `include/constants/map_event_ids.h` | 16-25 | Dez linhas novas, **dentro da seção `// MAP_NEW_BARK_TOWN` que já existe** (`:823-826`, com `LOCALID_NEWBARK_MARILL 9`, `LOCALID_NEWBARK_RIVAL 10`, `LOCALID_NEWBARK_MARILL2 11`). Não criar cabeçalho novo, como na M3. |

Comentário obrigatório acima do `#define` novo, no mesmo padrão dos três
anteriores: quem seta, quem limpa, e a frase de que ela só existe porque o campo
`flag` do `map.json` não lê var.

Nenhuma var nova. `FLAG_NO_CATCHING` / `B_FLAG_NO_CATCHING` existem desde
Blackthorn e são compartilhadas; a engine as limpa sozinha ao fim de toda
batalha (`Overworld_ResetBattleFlagsAndVars`, `src/overworld.c`) — setar
imediatamente antes da batalha e **nunca** limpar à mão.

**Não é preciso bloquear fuga.** Em boss battle "Run" é desistência explícita
(`CanPlayerForfeitBattle`, `src/battle_main.c`): `B_OUTCOME_FORFEITED`, que
conta como derrota → blackout → retry.

### 1.2 Máquina de estados `VAR_RIFT_MISSIONS_STATE` (fim da cadeia)

`VAR_RIFT_MISSIONS_STATE` = `0x4120` (`include/constants/vars.h:319`).
Valores 0-3 no doc de Blackthorn §1.2; 4-6 no de Mahogany §1.2; 6-8 no de
Cherrygrove §1.2. **Nenhum deles muda.**

| Valor | Significado | Quem escreve | Quem lê |
|---|---|---|---|
| 8 | Cherrygrove resolvido; briefing da Missão 4 pendente | `CherrygroveCity_EventScript_UBResolved` (já existe) | Olivine House1 (cena de chegada + briefing M4) |
| 9 | Briefing M4 feito; incidente de New Bark **ativo** | `OlivineCity_House1_EventScript_BriefingTalkM4` | Olivine House1 ("vá na frente"); `NewBarkTown_OnTransition`; a fala de retry da mãe |
| 10 | New Bark resolvido; **reunião de Olivine pendente** | `NewBarkTown_EventScript_UBResolved` | Olivine House1 (stub da reunião) |
| 11+ | Reservado para a reunião / expedição (design §7) | próximo doc | — |

**O valor 10 não abre missão nenhuma.** A regra de sobreposição (resolvido de
uma = briefing pendente da seguinte) termina aqui: 10 significa *quatro missões
concluídas, reunião pendente*.

**Invariante:** `FLAG_EVENT_ULTRABEAST_NEWBARK` setada ⇔ `VAR_RIFT_MISSIONS_STATE == 9`.
As duas mudam **juntas, no mesmo script** (Olivine seta, New Bark limpa). A flag
existe só porque o campo `flag` do `map.json` não lê var — é ela que esvazia a
cidade e que acende os dois interiores. A var é a autoridade da história.

As invariantes das M1/M2/M3 continuam valendo e **não** são tocadas. As quatro
flags nunca estão setadas ao mesmo tempo, porque a var só tem um valor.

Nenhuma outra flag/var persistente. A escolha do jogador é temporária: numa nova
tentativa ele escolhe de novo.

### 1.3 Temporários por mapa

Conferido em 20/09/2026: **nenhum `FLAG_TEMP_*` nem `VAR_TEMP_*` é usado hoje em
`NewBarkTown`** (nem os símbolos diretos, nem nenhum dos aliases de `vars.h`
`:360-370`, incluindo `VAR_TEMP_TRANSFERRED_SPECIES`, que foi a armadilha da M3).
Ainda assim a missão começa em `VAR_TEMP_2`, por uniformidade com as outras três.

| Mapa | Temp | Uso |
|---|---|---|
| `OlivineCity_House1` | `VAR_TEMP_1` | Trava uma-vez-por-visita do gatilho de frame (**já existe**; passa a servir aos estados 2, 4, 6 **e** 8) |
| `NewBarkTown` | `FLAG_TEMP_1` | Cache de visibilidade do elenco fixo (Looker, Anabel, mãe, Gold/Crystal, Marill) |
| `NewBarkTown` | `FLAG_TEMP_2` | Cache das três Ultra Beasts (sempre escondidas até a cena) |
| `NewBarkTown` | `FLAG_TEMP_3` | Cache **só do Elm** — separado porque a cena faz `removeobject` nele (§4.2) |
| `NewBarkTown` | `FLAG_TEMP_4` | Cache **só da Lusamine** — mesmo motivo |
| `NewBarkTown` | `VAR_TEMP_2` | Resultado da batalha |
| `NewBarkTown` | `VAR_TEMP_3` | Escolha: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego. Sobrevive à batalha (voltar de batalha não passa por `LoadMapFromWarp`) |
| `NewBarkTown_PlayersHouse_1F` | `FLAG_TEMP_1` | Cache de visibilidade da mãe dentro de casa (§3.6) |
| `NewBarkTown_Lab` | `FLAG_TEMP_1` | Cache de visibilidade do Elm dentro do laboratório (§3.6) |

`FLAG_TEMP_3` e `FLAG_TEMP_4` **precisam ser separadas de `FLAG_TEMP_1`** por um
motivo concreto: `removeobject` seta a flag do template do objeto. Se o Elm e a
Lusamine dividissem a flag do elenco, o `removeobject` de §4.2 esconderia o
elenco inteiro no meio da cena. Mesma lógica pela qual a M3 pôs as UBs em
`FLAG_TEMP_2` própria.

Evitar `FLAG_TEMP_E`, que a engine reserva para suprimir o follower. Os usos de
`VAR_TEMP_2/3` e `FLAG_TEMP_*` em `data/scripts/` são de `contest_hall`,
`battle_arcade_*` e `interview.inc` — outros mapas; temporários zeram a cada
load (`ClearTempFieldEventData`), então não há conflito.

Reconfirmar antes de implementar:

```bash
grep -rn "FLAG_TEMP_[1-5]\b\|VAR_TEMP_[0-3]\b" \
  data/maps/NewBarkTown data/maps/NewBarkTown_PlayersHouse_1F \
  data/maps/NewBarkTown_Lab data/maps/OlivineCity_House1
```

### 1.4 Orçamento de objetos — a conta que não pode estourar

`OBJECT_EVENTS_COUNT` é **16** (`include/constants/global.h:83`) e inclui o
jogador. `OBJECT_EVENT_TEMPLATES_COUNT` é 64, e 15 + 10 = 25 templates cabem com
folga — o problema **não** é o template, é o spawn simultâneo.

> **CORRIGIDO EM 20/09/2026, DEPOIS DE MEDIR** (§12.8). A tabela original desta
> seção contava as quatro light sprites como quatro slots e chegava a 16/16, e
> foi **por causa dela** que o plano mandava escondê-las. A conta estava errada:
> light sprite **não ocupa slot de object event**. A conta certa é 12/16 com as
> lâmpadas intactas, e a M4 **não toca no sistema de luminosidade**.

Durante o incidente:

| Ocupante | Slots |
|---|---|
| Jogador | 1 |
| Follower do jogador | 1 |
| Elenco + UBs da missão | 10 |
| 4 light sprites | **0** — ver abaixo |
| **Total** | **12 / 16** |

`TrySpawnObjectEvents` trata light sprite como caso especial
(`src/event_object_movement.c:3168`): ela vai para `SpawnLightSprite`, que faz
`CreateSprite()` em `gSprites[]` e **nunca** encosta em `gObjectEvents[]`. As
quatro lâmpadas de New Bark custam zero contra o teto de 16.

**Onde o orçamento importa de verdade:** objeto que não cabe **não spawna, sem
erro nenhum**, e `TrySpawnObjectEvents` percorre os templates **em ordem** — os
dez desta missão são os **últimos** do array. Estourar o teto tira o **Looker**
do mapa, e a missão fica sem como começar.

**Regra que fica para quem evoluir a cena:** a M4 tem quatro slots livres. Todo
object event novo consome um. Passar de 16 quebra em silêncio.

---

## 2. Etapa A — Olivine: briefing da Missão 4

`OlivineCity_House1` tem `.pory` → editar só `data/maps/OlivineCity_House1/scripts.pory`.
O `map.json` **não muda**: Looker e Anabel já existem com `flag: 0`.

É o quarto uso do mesmo padrão de acréscimo. Nenhum objeto novo, nenhuma
coreografia nova.

### 2.1 O gatilho de chegada passa a atender quatro estados

`OlivineCity_House1_EventScript_BriefingTrigger` ganha **uma** linha:

```asm
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_StageBriefing   @ NOVO
	end
```

A checagem de `getplayerxy` em (4,8) e a trava `VAR_TEMP_1` continuam como
estão. `StageBriefing` não muda em nada.

### 2.2 `BriefingTalk` ganha o ramo da M4

```asm
OlivineCity_House1_EventScript_BriefingTalk::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_BriefingTalkM4   @ NOVO
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_BriefingTalkM3
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_BriefingTalkM2
	@ cai no M1 (estado 2)

OlivineCity_House1_EventScript_BriefingTalkM4::
	msgbox OlivineCity_House1_Text_BriefingM4, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_EVENT_ULTRABEAST_NEWBARK
	setvar VAR_RIFT_MISSIONS_STATE, 9
	return
```

Acrescentar a quarta invariante ao comentário que já lista as três acima do
rótulo. O "estado mais alto primeiro" continua valendo.

### 2.3 Diálogo por estado — Looker e Anabel

`goto_if_ge VAR_RIFT_MISSIONS_STATE, 8, ..._LookerMission4` **tem que virar
`, 10, ..._LookerReunion`** — com o 8, os estados 9 e 10 nunca são alcançados. É
exatamente o erro que a M3 teve de apagar (lá era `, 6,`), e o comentário acima
dos dois despachantes já cita o episódio pelo nome. Acrescentar a M4 a ele.

| Estado | O que acontece |
|---|---|
| 0-7 | inalterado |
| **8** | `call ..._BriefingTalk` → **M4**. O rótulo `..._LookerBrief` já existe e já atende 2, 4 e 6: basta apontar o 8 para ele. |
| **9** | **Novo** `Text_LookerGoAheadM4` |
| **≥ 10** | `..._LookerMission4` **é renomeado** para `..._LookerReunion`, e `..._Text_LookerMission4Stub` para `..._Text_LookerReunionStub`, com texto novo (todo mundo vindo para Olivine). |

```asm
@ NAO acrescentar nenhum "goto_if_ge VAR_RIFT_MISSIONS_STATE, 8" aqui - ele
@ engoliria os estados 9 e 10. Terceiro aviso do mesmo tipo neste arquivo.
OlivineCity_House1_EventScript_Looker::
	lock
	faceplayer
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2,  OlivineCity_House1_EventScript_LookerBrief
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3,  OlivineCity_House1_EventScript_LookerGoAhead
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4,  OlivineCity_House1_EventScript_LookerBrief
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5,  OlivineCity_House1_EventScript_LookerGoAheadM2
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6,  OlivineCity_House1_EventScript_LookerBrief
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7,  OlivineCity_House1_EventScript_LookerGoAheadM3
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8,  OlivineCity_House1_EventScript_LookerBrief      @ NOVO
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9,  OlivineCity_House1_EventScript_LookerGoAheadM4  @ NOVO
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerReunion    @ era 8 -> Mission4
	msgbox OlivineCity_House1_Text_LookerHoliday, MSGBOX_DEFAULT
	goto OlivineCity_House1_EventScript_ReleaseEnd
```

`OlivineCity_House1_EventScript_Anabel` recebe a mesma cirurgia, com
`..._AnabelBrief`, `..._AnabelGoAheadM4` e `..._AnabelReunion`.

Todos os ramos continuam terminando em `OlivineCity_House1_EventScript_ReleaseEnd`.

**Checagem pós-edição obrigatória:**
`grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE" data/maps/OlivineCity_House1/scripts.pory`
tem que devolver **exatamente duas** linhas de código, ambas com `, 10,`.

Textos (inglês, placeholder — quebrar em caixas de ~34 colunas na implementação):

> `Text_BriefingM4` — é o briefing mais longo do arco de propósito (design §6.4).
> Looker: {PLAYER}. Sit down. No — actually, don't. There isn't time and you won't anyway.
> Looker: Cherrygrove holds. And the Professor? Did he eat something, at last?
> Anabel: He went straight to New Bark. He says Professor Elm has had the same reading for six weeks and wrote it off as a broken sensor.
> Looker: Then let us look at it. ...Three, Anabel?
> Anabel: Three. Opening together. Closing together. It isn't a rhythm this time, it's—
> Anabel: ...Put it in the report. I'll write it myself.
> Looker: {PLAYER}. New Bark Town has no Pokémon Center. No Gym. It has a laboratory and about forty people.
> Looker: We told them to leave. Half of them would not.
> Looker: Your mother is one of the half.
> Anabel: Madame Lusamine is already there, standing on the road in. She asked for you by name, and she asked us to stay out of it.
> Looker: Three missions, {PLAYER}, and I have never once asked you this.
> Looker: ...Do you want to go?
> Anabel: Heal everything. Take these. And we are going with you — that part is not a question.
>
> `Text_LookerGoAheadM4` —
> Looker: New Bark Town, {PLAYER}. Your own front door. I am sorry it is this one.
>
> `Text_AnabelGoAheadM4` —
> Anabel: Go. We'll be a step behind you the whole way.
>
> `Text_LookerReunionStub` (estado ≥ 10) —
> Looker: They are all coming here, {PLAYER}. Madame Lusamine, her children, the Professor. To this small room. I am told there are not enough chairs, and I am told it does not matter. Come back soon!
>
> `Text_AnabelReunionStub` (estado ≥ 10) —
> Anabel: Rest while you can. When everyone is here, we stop investigating and start preparing.

---

## 3. Etapa B — New Bark: a cidade que não evacua

`NewBarkTown` **tem** `.pory` → editar `data/maps/NewBarkTown/scripts.pory` e
`data/maps/NewBarkTown/map.json`. **Não** editar `scripts.inc`: é gerado.

### 3.1 Esconder a cidade

Sete objetos existentes ganham `FLAG_EVENT_ULTRABEAST_NEWBARK` no campo `flag`
do `map.json` (hoje todos com `"flag": "0"`):

| local | Gráfico | x,y |
|---|---|---|
| 1 | `OBJ_EVENT_GFX_FAT_MAN` | 22,24 |
| 2 | `OBJ_EVENT_GFX_FR_LASS` | 9,16 |
| 4 | `OBJ_EVENT_GFX_SPECIES(WOOPER_PALDEA)` | 10,23 |
| 5 | `OBJ_EVENT_GFX_SPECIES(PIDGEY)` | 24,35 |
| 6 | `OBJ_EVENT_GFX_SPECIES(PIDGEY)` | 16,4 |
| 7 | `OBJ_EVENT_GFX_SPECIES(PIDGEY)` | 5,29 |
| 8 | `OBJ_EVENT_GFX_SPECIES(PIDGEY)` | 7,2 |

**Consequência permanente, igual à das três missões anteriores:** um
`removeobject` em qualquer um desses sete passa a **esvaziar a cidade**. Pôr o
`WARNING` no cabeçalho do bloco em `scripts.pory`.

Objetos com flag própria que ficam **fora** da evacuação, por já estarem
escondidos no pós-E4 — verificado por rastreamento de código, e a conferir em
runtime:

- **local 3, Silver** (`FLAG_HIDE_SILVER_NEWBARKTOWN`): setada em
  `Route30_MrPokemonsHouse/scripts.pory:213`, no recado do Mr. Pokémon, e nunca
  mais limpa depois do começo do jogo.
- **locais 9, 10 e 11, o trio Gold/Crystal + dois Marill**
  (`FLAG_HIDE_NEWBARK_RIVALMARILL`): `NewBarkTown_EventScript_RivalBattle`
  termina em três `removeobject` (`scripts.pory:432-434`), e `removeobject`
  **seta a flag do template** (`RemoveObjectEventByLocalIdAndMap`,
  `src/event_object_movement.c:1588`). Depois da batalha do rival o trio some
  para sempre. **Isso importa:** se estivessem visíveis, haveria um segundo
  Gold/Crystal em (12,13) enquanto o da missão está em (21,13), e um Marill em
  (11,13), colado na Nihilego de (14,13). Conferir cedo no teste (§10).
  **Nunca limpar `FLAG_HIDE_NEWBARK_RIVALMARILL`.**

#### 3.1.1 As quatro light sprites (locais 12-15) — **NÃO são tocadas**

> **DESCARTADO EM 20/09/2026.** Esta seção mandava trocar o campo `flag` das
> quatro `OBJ_EVENT_GFX_LIGHT_SPRITE` por um cache `FLAG_TEMP_5` para
> escondê-las durante o incidente. Foi implementado, medido e **revertido**.
> Elas continuam com `FLAG_NIGHT_POKEMON`, exatamente como antes da missão.

Dois motivos eram alegados, e os dois caíram:

1. **Orçamento** — era o motivo principal, e estava baseado na conta errada de
   §1.4. Light sprite não ocupa slot de object event
   (`src/event_object_movement.c:3168` → `SpawnLightSprite` → `CreateSprite` em
   `gSprites[]`). Esconder as quatro não libera nada, porque não havia nada
   ocupado.
2. **Leitura de cena** — "cidade evacuada à noite fica no escuro" é bonito, mas
   não paga o preço: o cache é amostrado uma vez por `ON_TRANSITION`, então
   virar a noite **parado** na cidade deixava de acender as lâmpadas até o
   próximo carregamento de mapa. Regressão cosmética em conteúdo
   pré-existente, em troca de nada.

Fica registrado o que **é** verdade sobre a polaridade, porque continua valendo
para quem for mexer nisso um dia: `FLAG_NIGHT_POKEMON` é **limpa à noite** e
setada no resto do dia (`UpdateTimeOfDay`, `src/overworld.c:1642` e `:1673`).
Como o campo `flag` esconde quando setado, as lâmpadas acendem exatamente
enquanto a flag está limpa. Quem ler o nome e assumir o contrário inverte o dia
e a noite.

**Nenhum `removeobject` nas lâmpadas**, nunca — isso continua valendo.

### 3.2 Elenco e Ultra Beasts — anexar no fim de `object_events`

Dez objetos novos, **sempre no fim** do array, com `local_id` explícito (contrato
da M2). Todos `movement_type` fixo, `trainer_type: "TRAINER_TYPE_NONE"`,
`sight_radius_tree_etc: 0`, `elevation: 3` (conferir contra os vizinhos).

| local | Constante | Gráfico | x,y | Olhar | `flag` | script |
|---|---|---|---|---|---|---|
| 16 | `LOCALID_NEWBARK_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | 21,12 | `FACE_LEFT` | `FLAG_TEMP_1` | `NewBarkTown_EventScript_UBLooker` |
| 17 | `LOCALID_NEWBARK_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | 22,12 | `FACE_LEFT` | `FLAG_TEMP_1` | `NewBarkTown_EventScript_UBAnabel` |
| 18 | `LOCALID_NEWBARK_UB_MOM` | `OBJ_EVENT_GFX_MOM` | 19,12 | `FACE_RIGHT` | `FLAG_TEMP_1` | `NewBarkTown_EventScript_UBMom` |
| 19 | `LOCALID_NEWBARK_UB_RIVAL` | `OBJ_EVENT_GFX_VAR_0` | 21,13 | `FACE_UP` | `FLAG_TEMP_1` | `NewBarkTown_EventScript_UBRival` |
| 20 | `LOCALID_NEWBARK_UB_MARILL` | `OBJ_EVENT_GFX_SPECIES(MARILL)` | 22,13 | `FACE_UP` | `FLAG_TEMP_1` | `NULL` |
| 21 | `LOCALID_NEWBARK_UB_ELM` | `OBJ_EVENT_GFX_PROF_ELM` | 11,10 | `FACE_DOWN` | `FLAG_TEMP_3` | `NewBarkTown_EventScript_UBElm` |
| 22 | `LOCALID_NEWBARK_UB_LUSAMINE` | `OBJ_EVENT_GFX_LUSAMINE` | 3,12 | `FACE_RIGHT` | `FLAG_TEMP_4` | `NewBarkTown_EventScript_UBLusamine` |
| 23 | `LOCALID_NEWBARK_UB_KARTANA` | `OBJ_EVENT_GFX_SPECIES(KARTANA)` | 15,10 | `FACE_DOWN` | `FLAG_TEMP_2` | `NULL` |
| 24 | `LOCALID_NEWBARK_UB_GUZZLORD` | `OBJ_EVENT_GFX_SPECIES(GUZZLORD)` | 23,15 | `FACE_UP` | `FLAG_TEMP_2` | `NULL` |
| 25 | `LOCALID_NEWBARK_UB_NIHILEGO` | `OBJ_EVENT_GFX_SPECIES(NIHILEGO)` | 14,13 | `FACE_RIGHT` | `FLAG_TEMP_2` | `NULL` |

Conferido em 20/09/2026: `OBJ_EVENT_GFX_LOOKER` (334), `ANABEL` (70),
`LUSAMINE` (330), `PROF_ELM` (242) e `MOM` (215) existem em
`include/constants/event_objects.h`; `KARTANA`, `GUZZLORD` e `NIHILEGO` têm
bloco `OVERWORLD(` (`SIZE_32x32`, `SHADOW_SIZE_M`) e `.isUltraBeast = TRUE` em
`src/data/pokemon/species_info/gen_7_families.h`.

**`OBJ_EVENT_GFX_VAR_0` no local 19 não precisa de nada novo:**
`NewBarkTown_OnTransition` **já** começa com
`call Common_EventScript_SetupRivalGfxId` (`scripts.pory:48`), que resolve
`VAR_OBJ_GFX_ID_0` para Brendan ou May conforme o gênero do jogador
(`data/scripts/rival_graphics.inc`). O mesmo var serve ao local 10, que está
escondido — não há conflito.

### 3.3 Visibilidade — `ON_TRANSITION` (já existe; ganha uma linha)

`NewBarkTown_OnTransition` hoje é:

```asm
NewBarkTown_OnTransition::
    call Common_EventScript_SetupRivalGfxId
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end
```

⚠ Os dois `goto_if_eq` são **`goto`, não `call`**: quem cair neles não volta. A
linha nova tem que entrar **antes** deles, logo abaixo do `call` existente, ou o
recálculo não roda nos estados 2 e 4. (Fora do escopo desta missão, porque a
questline é estritamente pós-E4 e `VAR_NEWBARK_TOWN_STATE` ≥ 7 lá — mas a ordem
certa custa zero e evita uma regressão boba num New Game.)

```asm
NewBarkTown_OnTransition::
    call Common_EventScript_SetupRivalGfxId
	call NewBarkTown_EventScript_ApplyUBVisibility          @ NOVO - antes dos goto
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end

@ Roda antes de qualquer objeto spawnar - setflag/clearflag funcionam aqui e
@ removeobject nao. Temporarios zeram a cada load, entao isto recalcula do
@ zero toda vez.
NewBarkTown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2                                     @ UBs: so a cena as traz
	call NewBarkTown_EventScript_ApplyLampVisibility
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_4
	return

NewBarkTown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	return
```

**Nenhuma entrada nova em `NewBarkTown_OnFrame`.** A missão começa por conversa,
não por gatilho de frame. Isso é deliberado: a tabela já tem cinco entradas, uma
delas `map_script_2 VAR_RIFT_MISSIONS_STATE, 1` (a ligação do Looker que abriu o
arco), e ela roda a primeira entrada verdadeira por frame. Não disputar com ela.
As outras quatro estão mortas no pós-E4 — `VAR_NEWBARK_TOWN_STATE` ≥ 7 e
`VAR_RIVAL_STATE` = 12 —, o que também mata os seis `coord_events` de saída
(valores 2 e 4). **Medir, não supor**, na primeira sessão de teste.

### 3.4 Planta da cena (colisão real)

Lida em 20/09/2026 com as máscaras corretas deste repo (§12.7 do doc da M3:
metatile `0x07FF`, colisão `0x0800` shift 11). O leitor foi validado contra a
planta já conferida de Cherrygrove antes de ser usado aqui.

**Não há um único tile de água em `LAYOUT_NEW_BARK_TOWN`** (30×39). Diferente da
M3, aqui a leitura de comportamento não muda nenhuma decisão: a cena é de rua.

```text
      x= 2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
  y= 8   #  #  #  .  .  #  #  #  #  #  .  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  # 
  y= 9   #  #  #  .  .  #  #  #  D  #  .  #  .  .  .  .  #  #  #  #  #  #  #  #  #  #  #  # 
  y=10   #  #  .  .  .  .  .  .  .  E' .  .  .  1  .  .  #  #  #  #  #  #  #  #  #  #  #  # 
  y=11   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  #  #  #  d  #  #  .  .  .  .  .  .  . 
  y=12   .  U' .  .  .  .  .  .  .  .  .  .  .  .  .  .  U  M  *  K  A  E  .  .  .  .  .  . 
  y=13   .  .  .  .  .  .  .  .  .  .  .  .  2  .  .  .  .  .  .  G  m  .  .  .  .  .  .  . 
  y=14   .  .  .  .  .  .  .  .  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  . 
  y=15   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  3  .  .  #  #  #  # 
  y=16   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  #  #  #  # 

  D  porta do laboratorio (warp 10,9)      d  porta da casa do jogador (warp 20,11)
  *  jogador (20,12): Fly, blackout e o UNICO tile de fala do Looker
  K  Looker (21,12)   A  Anabel (22,12)    M  mae (19,12)
  U  Lusamine depois de entrar (18,12)     E  Elm depois de entrar (23,12)
  G  Gold/Crystal (21,13)                  m  Marill (22,13)
  U' Lusamine no inicio (3,12)             E' Elm no inicio (11,10)
  1  Kartana (15,10)  2  Nihilego (14,13)  3  Guzzlord (23,15)
```

**O bolso do Looker.** (21,12) tem parede ao norte — (21,11) é a parede da casa
do jogador, colisão 1, conferido —, a Anabel a leste e o Gold/Crystal ao sul. O
único vizinho livre é **(20,12)**, a oeste. Não é preciso `getplayerxy`.

**E (20,12) é onde o jogo larga o jogador nos dois caminhos que importam:**
`HEAL_LOCATION_NEW_BARK_TOWN` é (20,12) (`src/data/heal_locations.h:139-144`),
`NewBarkTown_OnLoad` refaz o `setrespawn` a cada load, e o Fly usa a mesma heal
location (`sMapHealLocations[MAPSEC_NEW_BARK_TOWN]`, `src/region_map.c:340`).
Chegar de Fly e voltar de um blackout põem o jogador **exatamente no tile de
fala**, virado para o Looker depois de um passo. É a melhor recuperação do arco
e ela veio de graça.

**Ninguém fica ao sul do jogador.** (20,13) fica vazio de propósito: com o
jogador em y=12 a caixa de texto cobre o rodapé da tela (y≈15+), e os atores de
y=13 estão fora dela. Não pôr objeto em (20,13) numa evolução.

**A porta de casa continua aberta.** O jogador em (20,12) pode subir e entrar
(20,11). Isso é inofensivo — a cena só começa ao falar com o Looker, e ao sair
ele volta para (20,12). A casa está vazia durante o incidente (§3.6).

**As três UBs são alcançáveis a pé**, diferente da M3. Não é problema: elas só
existem enquanto o jogador está sob `lockall`, e têm `script: NULL`. Registrado
para que ninguém "conserte" isso pondo colisão onde não precisa.

### 3.5 Conversas antes da cena

Cinco NPCs com uma fala curta cada, no padrão da M3 (`lock`, `faceplayer`,
`msgbox`, `closemessage`, `turnobject` de volta ao olhar do `map.json`,
`release`). São o que dá ao jogador a chance de conhecer a Lusamine **sozinho,
na estrada**, antes de tudo — que é o beat que o gancho da M3 prometeu.

- **Lusamine (3,12).** A primeira fala dela no arco inteiro. Educada, ensaiada,
  e ela sabe que está indo mal. Não adianta nada do nó da cena.
- **Elm (11,10).** As seis semanas e o caderno. Ele já sabe que errou.
- **Mãe (19,12).** Recusa o abrigo. Uma caixa, sem drama.
- **Gold/Crystal (21,13).** Está fazendo a ronda porta a porta. Pede para lutar,
  aqui, cedo — e o não vem depois, na cena.
- **Anabel (22,12).** Instrução precisa. **Não** planta semente nenhuma: as
  sementes já foram plantadas na M2, na M3 e no briefing; a próxima vez que ela
  tocar no assunto é a revelação.

Textos (inglês, placeholder):

> `UBLusamineIdle` —
> Lusamine: You are taller than the photographs. ...Forgive me. I have practiced this and I am still doing it badly.
> Lusamine: Lillie writes about you. Gladion does not write, but he mentions you, which from him is the same thing.
> Lusamine: We will talk properly when this is over. If I am still someone you want to talk to.
>
> `UBElmIdle` —
> Elm: Six weeks. Six weeks of the same reading, and every time I wrote "check the sensor" in the margin.
> Elm: Professor Kukui's notes came this morning. I ran them against my log and... it isn't the sensor. It never was.
> Elm: Everyone who would come is in the lab. It's the strongest building in town, which is not saying much.
>
> `UBMomIdle` —
> Mom: I'm not going into the lab, {PLAYER}. Don't ask me again.
> Mom: I've been watching that road for two years. I know how to watch a road.
>
> `UBRivalIdle` — (sem o nome: serve aos dois gêneros)
> Every house on this street, twice. The Hanlons wouldn't open the door until I said your name.
> Hey — when it starts, put me in. I've got a full team. I've had a full team for a year.
>
> `UBAnabelIdle` —
> Anabel: Three signatures, and they are breathing together. In and out. I have never seen that.
> Anabel: Stay on this street. If I tell you to move, move first and ask me after.

### 3.6 Os dois interiores — a mãe em casa e o Elm no laboratório

A mãe (`NewBarkTown_PlayersHouse_1F`, `LOCALID_MOM`, hoje `"flag": "0"`) e o Elm
(`NewBarkTown_Lab`, `LOCALID_ELM`, hoje `"flag": "0"`) precisam sumir de dentro
enquanto estão na rua. O design §5 aceita Looker e Anabel em dois lugares porque
estão a uma cidade de distância; estes dois estão a **um warp**, e a mãe em
particular fica a um tile da porta.

Os dois mapas **já têm `ON_TRANSITION`** (`PlayersHouse_1F/scripts.inc:7`,
`Lab/scripts.pory:8`), então é um `call` em cada um:

```asm
@ Mae visivel <=> nao ha incidente. Padrao aprovado na M3: o campo flag do
@ template vira cache temporario e a verdade continua sendo a flag do evento.
@ Temporarios zeram a cada load, entao o default e VISIVEL - se este bloco
@ nao rodar, a mae aparece, que e o erro seguro.
NewBarkTown_PlayersHouse_1F_ApplyMomVisibility::
	clearflag FLAG_TEMP_1
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_PlayersHouse_1F_MomStays
	setflag FLAG_TEMP_1
NewBarkTown_PlayersHouse_1F_MomStays::
	return
```

Idêntico no laboratório para `LOCALID_ELM`. ⚠ No `PlayersHouse_1F` o
`ON_TRANSITION` usa `call_if_eq`, então acrescentar a linha é seguro em qualquer
posição; no `Lab` ele usa `goto_if_eq`, então a linha nova tem que vir **antes**
deles, como em New Bark.

**Nunca `removeobject` na mãe nem no Elm.** E o `NewBarkTown_Lab_OnTransition`
faz `setobjectxyperm LOCALID_ELM` em alguns estados — isso não conflita com a
visibilidade, mas conferir que o Elm volta ao lugar certo depois da missão.

---

## 4. Etapa C — A cena (100% scriptada a partir do SIM)

### 4.1 Pré-checagens (`NewBarkTown_EventScript_UBLooker`)

```asm
@ So alcancavel de (20,12), olhando para leste: (21,11) e a parede da casa, e
@ os vizinhos sul/leste do Looker sao o Gold/Crystal e a Anabel. Nao precisa
@ de getplayerxy. (20,12) tambem e onde o Fly e o blackout largam o jogador.
@ Nada muda de estado antes do SIM. O SIM e o ultimo ponto de saida.
@ A leitura do Elm vem ANTES do SIM de proposito: e o cronometro dele que
@ transforma "tres rupturas" em "agora", igual a leitura da Lillie na M2 e a
@ do Kukui na M3.
NewBarkTown_EventScript_UBLooker::
	lock
	faceplayer
	msgbox NewBarkTown_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBElmClock, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBNotReady
	goto NewBarkTown_EventScript_UBScene

NewBarkTown_EventScript_UBNotReady::
	msgbox NewBarkTown_Text_UBNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end
```

Batalha simples: não é preciso checar quantidade de Pokémon. Não há presente,
então não há checagem de espaço (a regra da skill `entregar-pokemon-ou-ovo` não
se aplica a esta missão).

> `UBLookerGreet` —
> Looker: {PLAYER}. Right on your own doorstep. I have worked a great many streets and I have never liked this one less.
> Looker: The Professor has been counting. He says we are close.
>
> `UBElmClock` —
> Elm: Three minutes. Maybe four — the interval has been shortening all morning.
> Elm: They breathe together, all three. That's what I couldn't see for six weeks and Kukui saw in one page.
> Anabel: He's right. I can feel the draw of it from here.
> Looker: {PLAYER}. Madame Lusamine intends to handle all three herself. I would very much like you to be standing beside me when she says it out loud.
>
> `UBReady` —
> Looker: Worse than Cherrygrove. Worse than anything we have sent you into.
> Anabel: Are you ready?
>
> `UBNotReady` —
> Looker: Then take the time. Your mother is not moving, and neither am I.

### 4.2 Ruptura

Duas coisas acontecem sob o mesmo fade: o Elm e a Lusamine entram na linha, e as
três rupturas abrem.

⚠ **`setobjectxy` não serve aqui, e falha em silêncio.**
`TryMoveObjectEventToMapCoords` (`src/event_object_movement.c:3812`) só age se o
objeto estiver **spawnado**, e o spawn só acontece perto da câmera
(`TrySpawnObjectEvents`, `:3148`, janela = tela ± 2). O Elm em (11,10) está na
borda dessa janela e a Lusamine em (3,12) está muito fora. O caminho correto é
mexer no **template** e re-spawnar:

```asm
NewBarkTown_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	fadescreen FADE_TO_BLACK
	@ Elm (11,10) -> (23,12) e Lusamine (3,12) -> (18,12). removeobject e no-op
	@ se o objeto nao estiver spawnado, e se estiver seta SO a flag temporaria
	@ dele - por isso os dois tem FLAG_TEMP_3/4 proprias e nao a do elenco.
	@ setobjectxyperm mexe no template (vale enquanto o mapa estiver carregado);
	@ o clearflag + addobject spawna na posicao nova. A ordem e obrigatoria.
	removeobject LOCALID_NEWBARK_UB_ELM
	setobjectxyperm LOCALID_NEWBARK_UB_ELM, 23, 12
	clearflag FLAG_TEMP_3
	addobject LOCALID_NEWBARK_UB_ELM
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_WEST
	removeobject LOCALID_NEWBARK_UB_LUSAMINE
	setobjectxyperm LOCALID_NEWBARK_UB_LUSAMINE, 18, 12
	clearflag FLAG_TEMP_4
	addobject LOCALID_NEWBARK_UB_LUSAMINE
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
	fadescreen FADE_FROM_BLACK
	msgbox NewBarkTown_Text_UBTheyArrive, MSGBOX_DEFAULT
	closemessage
	@ Tremor, depois o flash branco que traz as tres.
	setvar VAR_0x8004, 2   @ pan vertical
	setvar VAR_0x8005, 1   @ pan horizontal
	setvar VAR_0x8006, 32  @ numero de tremidas
	setvar VAR_0x8007, 4   @ atraso
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_NEWBARK_UB_KARTANA
	addobject LOCALID_NEWBARK_UB_GUZZLORD
	addobject LOCALID_NEWBARK_UB_NIHILEGO
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox NewBarkTown_Text_UBAppear, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBKnot
```

**SKELETON:** a chegada do Elm e da Lusamine é um fade. Evolução: os dois
correndo de verdade, com `applymovement` longo; a ruptura com paleta, clima e
música próprias.

**Ninguém anda nesta cena.** Não há `applymovement` de caminhada em §4.2 — os
sete atores já estão nos tiles definitivos. É o que torna esta cena, que tem o
dobro de gente da M3, mais simples de encenar do que ela.

> `UBTheyArrive` —
> Lusamine: I came the moment I read it. Professor, your log — you kept it. You kept six weeks of it.
> Elm: I kept it because I thought it was wrong. That is not the same as being useful.
> Lusamine: Today it is exactly the same thing.
>
> `UBAppear` —
> Looker: Three. Over the laboratory, over the road, over this street.
> Elm: That's them. That's the reading. Six weeks of it, standing in my town.

### 4.3 O nó — Lusamine quer as três, e a mãe a faz parar

```asm
NewBarkTown_EventScript_UBKnot::
	@ Lusamine (18,12) -> (17,12), um passo a oeste, em direcao as rupturas.
	@ (17,12) e livre e continua dentro da camera (x>=13).
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_StepLeftFaceLeft
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
	msgbox NewBarkTown_Text_UBLusamineTakesThree, MSGBOX_DEFAULT
	closemessage
	@ A mae vira as costas para o proprio filho para encarar a Lusamine. O
	@ turnobject e o beat: nao encurtar isso numa evolucao.
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
	msgbox NewBarkTown_Text_UBMomStopsHer, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
	msgbox NewBarkTown_Text_UBLusamineAsks, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBAnabelReveal
```

> `UBLusamineTakesThree` —
> Lusamine: Three of them. Then I will take three.
> Lusamine: No — listen to me. I know what they are. I know it better than anyone standing on this road. Nobody else here has to go near them.
>
> `UBMomStopsHer` —
> Mom: Ma'am.
> Mom: My child is standing right there and I'm not going inside either, so I'm not going to lecture you.
> Mom: But you're not protecting anyone. You're making sure that if it goes wrong, it goes wrong to you.
> Mom: I know the difference. I've wanted to do it too. Every week for two years.
> Mom: It isn't the same thing. It only feels like it from in here.
> Lusamine: ...
> Lusamine: My daughter said something very close to that to me, once. I did not hear it either.
>
> `UBLusamineAsks` —
> Lusamine: Very well. Then I will do the thing I am worst at.
> Lusamine: Anabel. What do your instruments give me?

### 4.4 A revelação da Anabel

Entre o pedido da Lusamine e a escolha do jogador, pela sequência de sete passos
do design §3.1. **Não é flashback, não tem flag, e não para a missão.**

```asm
@ O Looker ja esta em (21,12), colado nela em (22,12): ele nao precisa andar
@ para amparar. A exclamacao + turnobject bastam.
NewBarkTown_EventScript_UBAnabelReveal::
	msgbox NewBarkTown_Text_UBAnabelBreaks, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_LOOKER, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_EAST
	delay 30
	msgbox NewBarkTown_Text_UBAnabelFaller, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST   @ volta a encarar o jogador
	msgbox NewBarkTown_Text_UBAnabelPicks, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBChoose
```

> `UBAnabelBreaks` —
> Anabel: They give me... they give me...
> Anabel: ...
> Looker: Chief. Chief.
>
> `UBAnabelFaller` —
> Anabel: I'm here. I'm here. Looker, let go, I can stand.
> Anabel: {PLAYER}. You should hear this from me and not from a file.
> Anabel: I came through one of these. I'm a Faller.
> Anabel: I don't remember where I came from. I've stopped pretending that will come back.
> Anabel: I remember someone's hand. That's the whole memory. Someone reached down, and I wasn't alone anymore.
> Anabel: So that's what we do. Everyone who comes through gets that, and everyone who goes in comes home. Both. Always both.
> Looker: Thank you for telling them, Chief.
>
> `UBAnabelPicks` —
> Anabel: Report later. I'm taking one now.
> Lusamine: ...Thank you. {PLAYER} — which one will you take? I am asking. I am not deciding it for you.

### 4.5 A escolha e a distribuição

Três opções, `ignoreBPress TRUE` (a cena já começou, então `VAR_RESULT` só pode
ser 0, 1 ou 2), `maxBeforeScroll 3` para caber sem rolagem. `dynmultichoice`
aceita vararg (`asm/macros/event.inc:1942`), então três itens não exigem nada
novo.

**Regra de distribuição (design §6.4): Lusamine fica com Nihilego sempre que o
jogador não a escolher.**

| `VAR_TEMP_3` | Jogador | Lusamine | Anabel |
|---|---|---|---|
| 0 | Kartana | **Nihilego** | Guzzlord |
| 1 | Guzzlord | **Nihilego** | Kartana |
| 2 | Nihilego | Guzzlord | Kartana |

```asm
NewBarkTown_EventScript_UBChoose::
	msgbox NewBarkTown_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_Text_ChoiceKartana, NewBarkTown_Text_ChoiceGuzzlord, NewBarkTown_Text_ChoiceNihilego
	copyvar VAR_TEMP_3, VAR_RESULT
	closemessage
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPickGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPickNihilego
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	msgbox NewBarkTown_Text_UBPickedKartana, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBBattle

NewBarkTown_EventScript_UBPickGuzzlord::
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	msgbox NewBarkTown_Text_UBPickedGuzzlord, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBBattle

@ O unico ramo em que a Lusamine perde a UB que veio buscar. UMA linha, e ela
@ aceita - design section 6.4. Nao transformar isso em discussao.
NewBarkTown_EventScript_UBPickNihilego::
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	msgbox NewBarkTown_Text_UBPickedNihilego, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBBattle
```

> `UBChoosePrompt` —
> Looker: Choose, {PLAYER}. Quickly, and then not again.
>
> `UBPickedKartana` —
> Lusamine: The blade. Then I take the one that matters to me, and Anabel takes the weight.
>
> `UBPickedGuzzlord` —
> Lusamine: The mouth. Be careful — it does not stop because you are tired.
>
> `UBPickedNihilego` —
> Lusamine: ...That one was mine to answer for.
> Lusamine: No. That is exactly the sentence I promised my children I would stop saying. Thank you for taking it.

### 4.6 Batalha — boss simples, quarto degrau da escala

Mesma armação das três missões anteriores. `B_FLAG_NO_WHITEOUT` **não** é setada:
é batalha de ameaça, derrota = blackout e retry. Ordem das macros igual à de
`bosslegendaryencounterwithmoves`.

```asm
@ NAO e esqueleto: os numeros abaixo sao o alvo. Quarto degrau, depois de
@ Blackthorn (2 barras / Lv70 / x110), Mahogany (4 / Lv80 / x130) e
@ Cherrygrove (4 / Lv85 / x140). As barras estao no teto desde a M2.
@
@ RESSALVA DO DESIGN section 6: x140 nunca foi jogado. Se o runtime da M3
@ mostrar que x140 ja e parede, ESTE numero herda a correcao em vez de subir.
@ Ordem de afrouxar, um parafuso por vez:
@   1. tirar o item do chefe reclamado
@   2. multiplicador 150 -> 145 -> 140
@   3. trocar o golpe de preparo/controle por um quarto golpe de ataque
@   4. nivel 90 -> 85
@ As barras nao sao parafuso.
NewBarkTown_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                  @ a engine limpa no fim da batalha
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBSetupGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBSetupNihilego
	@ Kartana - a que SOBE. Frageis defesas, Swords Dance, item de dano puro.
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_KARTANA, 90, ITEM_MUSCLE_BAND
	seteventmonmoves MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_SACRED_SWORD, MOVE_SMART_STRIKE
	goto NewBarkTown_EventScript_UBStartBattle

@ Guzzlord - a que AGUENTA. HP absurdo, Leftovers e Toxic: guerra de atrito.
NewBarkTown_EventScript_UBSetupGuzzlord::
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_GUZZLORD, 90, ITEM_LEFTOVERS
	seteventmonmoves MOVE_TOXIC, MOVE_CRUNCH, MOVE_HEAVY_SLAM, MOVE_DRAGON_TAIL
	goto NewBarkTown_EventScript_UBStartBattle

@ Nihilego - a que ATRAPALHA. Acid Spray derruba a Sp.Def do jogador, Toxic
@ soma, Black Sludge cura por ser Poison. A mais irritante das tres.
NewBarkTown_EventScript_UBSetupNihilego::
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_NIHILEGO, 90, ITEM_BLACK_SLUDGE
	seteventmonmoves MOVE_ACID_SPRAY, MOVE_TOXIC, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE

@ LOST, DREW e FORFEITED nunca voltam aqui - a engine da blackout e devolve o
@ jogador CURADO em (20,12) (DoWhiteOut chama HealPlayerParty sozinho,
@ src/overworld.c:384; nao depende de balcao de Centro, e New Bark nao tem
@ um). CAUGHT e RAN sao inalcancaveis (ball bloqueada; Run vira FORFEITED num
@ boss) mas sao tratados: o que nao for WON reinicia a cena, nunca a vence.
NewBarkTown_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, NewBarkTown_EventScript_UBResolved
	goto NewBarkTown_EventScript_UBUnresolved
```

| Resultado | O que acontece |
|---|---|
| `B_OUTCOME_WON` | `..._UBResolved` → falas por escolha → gancho → estado 10 |
| `B_OUTCOME_LOST` | blackout pela engine; equipe curada; jogador em (20,12); flag ainda setada; estado 9; recomeça falando com o Looker, escolha refeita |
| `B_OUTCOME_FORFEITED` ("Run") | idem LOST |
| `B_OUTCOME_DREW` | idem LOST |
| `B_OUTCOME_CAUGHT` | inalcançável (`B_FLAG_NO_CATCHING`); cai em `..._UBUnresolved` |
| `B_OUTCOME_RAN` / qualquer outro | inalcançável; cai em `..._UBUnresolved` |

```asm
@ Nada foi registrado como feito: a flag do evento continua setada, recarregar
@ devolve o elenco aos tiles do map.json com as UBs escondidas de novo, e
@ falar com o Looker reinicia a cena inteira - a escolha inclusive. O warp
@ tambem devolve o Elm e a Lusamine as posicoes originais do template, porque
@ LoadMapFromWarp rele os templates.
NewBarkTown_EventScript_UBUnresolved::
	msgbox NewBarkTown_Text_UBGotAway, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
	waitstate
	releaseall
	end
```

---

## 5. Etapa D — Resolução e gancho

As lutas da Lusamine e da Anabel são **narrativas**: resolvem junto com a
vitória do jogador, e só as falas mudam conforme a escolha.

```asm
NewBarkTown_EventScript_UBResolved::
	@ Os tres objetos continuam no mapa apos a batalha (nao ha recarga).
	@ A flag deles e FLAG_TEMP_2: removeobject seta-la e inofensivo.
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_NEWBARK_UB_KARTANA
	removeobject LOCALID_NEWBARK_UB_GUZZLORD
	removeobject LOCALID_NEWBARK_UB_NIHILEGO
	fadescreen FADE_FROM_WHITE
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAfterGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBAfterNihilego
	msgbox NewBarkTown_Text_UBAfterKartana, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBAftermath

NewBarkTown_EventScript_UBAfterGuzzlord::
	msgbox NewBarkTown_Text_UBAfterGuzzlord, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBAftermath

NewBarkTown_EventScript_UBAfterNihilego::
	msgbox NewBarkTown_Text_UBAfterNihilego, MSGBOX_DEFAULT

@ Quatro batidas curtas: o custo (Elm), o que o protagonista nao pode dizer
@ (Gold/Crystal), a mae, e o gancho. Ninguem anda: todos ja estao na linha e
@ ninguem esta ao sul do jogador.
NewBarkTown_EventScript_UBAftermath::
	msgbox NewBarkTown_Text_UBElmCost, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_UP
	msgbox NewBarkTown_Text_UBRival, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_RIGHT   @ volta a encarar o filho
	msgbox NewBarkTown_Text_UBMom, MSGBOX_DEFAULT
	closemessage
	msgbox NewBarkTown_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_NEWBARK   @ invariante: flag e var juntas
	setvar VAR_RIFT_MISSIONS_STATE, 10
	@ Recarrega no lugar: os sete moradores voltam, as lampadas voltam a
	@ depender so da hora, o elenco some e o follower volta (desfaz o
	@ hidefollower). Sem isso, tudo isso apareceria aos poucos conforme a
	@ camera andasse.
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
	waitstate
	releaseall
	end
```

**SKELETON:** a luta da Lusamine e a da Anabel acontecem fora de tela. Evolução
pode encená-las; batalha de verdade contra qualquer uma das duas **não** é o
plano (a da Lusamine está reservada para o design §7/§9).

> `UBAfterKartana` (o jogador levou Kartana) —
> Lusamine: Mine went back the moment yours did. They came together and they leave together — of course they do.
> Anabel: Mine too. Nothing I did. They just... stopped being interested.
>
> `UBAfterGuzzlord` —
> Lusamine: You stood in front of that for how long? ...Lillie was right about you. She is right a great deal lately.
> Anabel: All three withdrew at once. Whatever held them here let go.
>
> `UBAfterNihilego` —
> Lusamine: I watched you do that. I made myself watch all of it.
> Lusamine: Thank you. I will not say it a third time, but I mean it more each time.
>
> `UBElmCost` —
> Elm: The sensors are gone. Every one of them. Melted, or whatever that was.
> Elm: ...I don't mind. I have six weeks of data and I finally know what it was. That's a better trade than most of my week.
>
> `UBRival` — (sem o nome: serve aos dois gêneros)
> I stood in the road and watched you do that.
> I'm not sad about it. I just wanted to say it out loud, one time, while everybody could hear me.
> Right. Doors. Forty people to let back out.
>
> `UBMom` —
> Mom: Come inside when you can. I'll leave the light on. You know I will.
>
> `UBHook` — **este bloco é o gancho para a reunião do design §7**
> Anabel: Looker. They didn't scatter.
> Anabel: All three closed toward the same bearing. I can put a place on a map now. I have never once been able to do that.
> Looker: Then the investigation is finished, and something else begins.
> Lusamine: Inspector. Call my children. Both of them. And Professor Kukui.
> Lusamine: Not as Aether. I owe these people an accounting, and two of them are mine.
> Looker: Olivine, then. All of us, in that small room. I apologise in advance for the chairs.
> Looker: {PLAYER} — bring your partner. Not for a test. Everyone in that room has been waiting a long time to meet them.

```asm
NewBarkTown_Movement_StepLeftFaceLeft:
	walk_left
	face_left
	step_end
```

---

## 6. Arquivos tocados (checklist de implementação)

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_NEWBARK 0x1044` + comentário; mover `CUSTOM_FLAGS_END` |
| `include/constants/map_event_ids.h` | 10 locais (16-25) **dentro da seção `// MAP_NEW_BARK_TOWN` existente** |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho atende 2/4/6/8; `BriefingTalk` ganha o ramo M4; ramos 8/9/≥10 em Looker e Anabel; stub da M4 vira stub da **reunião**; textos novos |
| `data/maps/NewBarkTown/map.json` | flag do evento em **7** objetos; 10 objetos novos no fim. As 4 light sprites **não mudam** (§3.1.1) |
| `data/maps/NewBarkTown/scripts.pory` | uma linha `call` no `ON_TRANSITION` existente (**antes** dos dois `goto_if_eq`); bloco `raw` novo no fim com visibilidade, conversas, cena, nó, revelação, escolha, boss, resolução, textos e movimento |
| `data/maps/NewBarkTown_PlayersHouse_1F/scripts.inc` | **`.inc` direto — este mapa não tem `.pory`**; uma linha no `ON_TRANSITION` existente + o recálculo da mãe (§3.6) |
| `data/maps/NewBarkTown_Lab/scripts.pory` | uma linha no `ON_TRANSITION` existente + o recálculo do Elm (§3.6) |
| `data/maps/NewBarkTown_PlayersHouse_1F/map.json` | `flag` do `LOCALID_MOM` vira `FLAG_TEMP_1` |
| `data/maps/NewBarkTown_Lab/map.json` | `flag` do `LOCALID_ELM` vira `FLAG_TEMP_1` |

**Ordem de edição.** Flags/localids → `map.json` dos dois interiores **junto com**
os `ON_TRANSITION` deles (nunca um sem o outro: com o `flag` trocado e sem o
recálculo, a mãe e o Elm somem de casa) → `map.json` de New Bark → resto do
`scripts.pory` de New Bark → Olivine → build.

---

## 7. Esqueleto × evolução

**Está simples de propósito (pode melhorar):**

- A chegada do Elm e da Lusamine é um fade com `setobjectxyperm` + `addobject`.
  Evolução: os dois correndo, com coreografia real.
- A ruptura é tremor + flash branco; as três UBs surgem paradas. Evolução:
  paleta, clima, música própria, três aberturas em tempos diferentes.
- As lutas da Lusamine e da Anabel são off-screen.
- Todo diálogo é placeholder e está marcado com `@ SKELETON:`.
- Ninguém anda na cena inteira, o que é barato e um pouco estático.

**Não pode regredir sem atualizar este doc e o design:**

- Valores 8/9/10 da var e a invariante flag ⇔ 9.
- A distribuição das UBs (Lusamine fica com Nihilego sempre que o jogador não a
  escolher) — é decisão de personagem, não de conveniência.
- O tile de fala único (20,12) e o bolso do Looker: mexer em qualquer um dos
  três vizinhos dele quebra o começo determinístico.
- (20,13) vazio.
- `FLAG_TEMP_3` e `FLAG_TEMP_4` separadas da `FLAG_TEMP_1`.
- Os dois recálculos de interior (§3.6) andando junto com os dois `map.json`.
- O orçamento de §1.4: quatro slots livres, e acabou.
- As quatro light sprites ficam com `FLAG_NIGHT_POKEMON`. A M4 não mexe no
  sistema de luminosidade, e §1.4 explica por que não precisa.
- A revelação da Anabel acontece **aqui**, não na reunião (design §3.1, V17).

---

## 8. Dependências frágeis criadas por este plano

1. **`ON_TRANSITION` compartilhado em três mapas.** New Bark divide o bloco com
   `Common_EventScript_SetupRivalGfxId` e com dois `goto_if_eq` que não voltam;
   o laboratório, com `NewBarkTown_Lab_EventScript_ElmAtComputer`. A ordem das
   linhas é carga estrutural em ambos. Comentar isso no código.
2. **Sete moradores com a flag do evento.** `removeobject` em qualquer um
   esvazia a cidade.
3. **`FLAG_HIDE_NEWBARK_RIVALMARILL` não pode ser limpa por ninguém.** Se for, o
   jogador vê dois Gold/Crystal.
4. **Os dois `map.json` de interior e os dois recálculos formam um par.** Um sem
   o outro apaga um NPC permanente.
5. **`setobjectxy` é proibido nesta cena.** Quem "simplificar" o bloco de §4.2
   trocando o trio `removeobject`/`setobjectxyperm`/`addobject` por um
   `setobjectxy` vai ver a Lusamine não aparecer — sem erro nenhum.
6. ~~As lâmpadas dependem da polaridade invertida de `FLAG_NIGHT_POKEMON`.~~
   **Deixou de ser dependência desta missão** (§3.1.1): as lâmpadas ficaram como
   estavam. A polaridade invertida continua sendo verdade sobre a engine e está
   registrada em §3.1.1 para quem for mexer nelas um dia.

---

## 9. Pendências e riscos conhecidos

- **Orçamento de objetos (§1.4).** Risco novo desta missão. É o único item do
  arco medido em código antes de ser jogado: 12/16 durante o incidente, com as
  lâmpadas custando zero. Testar **à noite** mesmo assim — a conta é leitura de
  código, não medição em jogo.
- **x150 nunca foi jogado, e x140 também não.** A ressalva do design §6 vale:
  este número pode nascer errado. Caminho de redução em §4.6.
- **Três sprites 32x32 ao mesmo tempo**, um deles o Guzzlord. Nenhum mapa do
  projeto tem isso hoje. Pode ficar visualmente pesado.
- **A cena inteira se repete a cada tentativa**, inclusive o nó da Lusamine e a
  revelação da Anabel — que é a fala mais longa do arco. Num retry isso cansa.
  Mitigação possível numa evolução (não no esqueleto): um ramo curto por
  `VAR_TEMP` quando a cena já rodou nesta visita. **Não** usar flag persistente
  para isso.
- **A mãe e o Elm dentro de casa** são a única regressão possível em conteúdo
  pré-existente, e é do mesmo tipo da do Friendly Trader da M3: silenciosa.
- **`VAR_NEWBARK_TOWN_STATE` e `VAR_RIVAL_STATE` no pós-E4** foram deduzidos por
  leitura de código, não medidos em jogo.
- Beast Balls com a Anabel continuam pendentes desde a M1.

---

## 10. Teste em runtime

Ordem otimizada para achar cedo o que quebra mais coisas:

1. **Antes de tudo, com a missão inativa:** entrar na casa do jogador e no
   laboratório. A mãe e o Elm têm de estar lá, normais. É o erro seguro de §3.6
   e é barato.
2. Estado 8, entrar em `OlivineCity_House1` pela porta (4,8): briefing M4, estado
   vira 9. Falar com os dois depois: falas de "vá na frente".
3. Estado 9, chegar em New Bark **por Fly**: o jogador cai em (20,12); a cidade
   está vazia (sete moradores fora); o elenco está nos sete tiles; as três UBs
   ausentes; **nenhum segundo Gold/Crystal em (12,13)**.
4. **Repetir o passo 3 à noite.** As quatro lâmpadas têm de **continuar
   acesas** — a missão não mexe nelas (§3.1.1). Se algum ator da missão não
   aparecer, a conta de §1.4 está errada.
5. Entrar em casa e no laboratório **durante** o incidente: os dois têm de estar
   vazios (a mãe e o Elm estão na rua).
6. Tentar falar com o Looker de (21,13), (22,12) e (21,11) — tem de ser
   impossível. Só (20,12) funciona.
7. Andar até (3,12) e (11,10) e ouvir a Lusamine e o Elm. Voltar.
8. SIM → assistir à cena inteira. Conferir que a Lusamine **aparece** em (18,12)
   e o Elm em (23,12) (é o ponto de falha silenciosa nº 1), que a mãe vira para
   oeste no nó e volta a virar para leste no fim, e que a caixa de texto não
   cobre o Gold/Crystal nem o Marill.
9. Escolher e **perder de propósito**: blackout tem de devolver o jogador
   **curado** em (20,12), com a cidade ainda vazia e o Looker ainda em (21,12).
   Falar com ele de novo e escolher **outra** UB.
10. Desistir com "Run" numa segunda tentativa: mesmo resultado.
11. Só então vencer, e conferir o repovoamento, o estado 10, o stub da reunião em
    Olivine, e que a mãe e o Elm voltaram para dentro.
12. Salvar e recarregar em cada estado (8, 9, 10) e entrar no mapa por Route 29 e
    por Route 27, não só por Fly.
13. Regressões: Blackthorn, Mahogany e Cherrygrove povoadas; estados 3, 5 e 7
    ainda se comportando como antes; o presente do Friendly Trader de Cherrygrove
    ainda não repetível.

---

## 11. O que este doc copiou das M1/M2/M3 e o que fez diferente

**Copiou sem mudar:** a estrutura escolha + boss; uma flag persistente por
missão com invariante; três valores de var; `FLAG_NO_CATCHING` compartilhada;
cache de visibilidade em `FLAG_TEMP_*` recalculado no `ON_TRANSITION`; o padrão
de acréscimo do escritório de Olivine; `warpsilent` + `waitstate` + `releaseall`
no fim; `local_id` explícito e objetos novos sempre no fim de `object_events`;
tratar todos os resultados de batalha e nunca cair na vitória por omissão.

**Fez diferente, e por quê:**

1. **Três UBs e sete atores de elenco** — o dobro da M3. Foi o que trouxe o
   orçamento de objetos (§1.4) para dentro do planejamento pela primeira vez.
2. **Tentou esconder as light sprites e desfez.** Virou a primeira armadilha de
   orçamento *medida* do arco — e a medição disse que não havia orçamento nenhum
   em jogo (§1.4, §3.1.1, §12.8).
3. **Esconder NPCs em dois interiores** — primeira vez no arco.
4. **Nenhuma caminhada na cena.** A M3 tinha três blocos de `applymovement` com
   ordem obrigatória; aqui os atores já estão no lugar e os dois que faltam
   entram sob fade. Mais gente, menos coreografia.
5. **`setobjectxy` descartado por leitura de código**, não por tentativa e erro
   (§4.2). É a armadilha nova que este doc deixa documentada para os próximos.
6. **O tile de fala é o tile de respawn.** As três missões anteriores pagaram
   caminhada de retry (20 tiles na M3); esta paga zero, por sorte de mapa.
7. **A cadeia de estados termina.** O stub da "próxima missão" virou stub da
   reunião, e o valor 10 não abre missão nenhuma.


---

## 12. Divergências entre este plano e o código implementado

Escritas em 20/09/2026, durante a implementação. Onde o texto acima conflita
com esta seção, **esta seção é a verdade** — o resto ficou como registro do
raciocínio.

### 12.1 `DIR_UP` e `DIR_RIGHT` não existem neste repo

§5 pedia `turnobject ..., DIR_UP` e `turnobject ..., DIR_RIGHT`. As únicas
direções cardeais declaradas são `DIR_SOUTH`, `DIR_NORTH`, `DIR_WEST` e
`DIR_EAST` (`include/constants/global.h:218-221`). No código são
`DIR_NORTH`/`DIR_EAST` — e, no caso do Gold/Crystal, `DIR_WEST` (ver §12.6).

### 12.2 `elevation` é 0, não 3

§3.2 dizia `elevation: 3` com a ressalva "conferir contra os vizinhos". Os
**quinze** objetos que já existiam em `NewBarkTown` usam `elevation: 0`. Os dez
novos usam 0 também.

### 12.3 O Elm não podia falar antes de chegar

§4.1 punha `Elm: Three minutes…` numa caixa **antes** do SIM. O Elm está em
(11,10) nessa hora — nove tiles a oeste e fora da câmera —, e só entra na linha
em §4.2. A leitura continua vindo antes do SIM, como o plano queria, mas quem a
lê é a **Anabel**, que está em (22,12); o texto virou
`NewBarkTown_Text_UBClockRelay`. A voz do próprio Elm entra junto com o objeto
dele, em `UBTheyArrive`. O rótulo `UBElmClock` não existe no código.

### 12.4 Faltava um `closemessage` entre §4.2 e §4.3

`msgbox UBAppear` era seguido direto por `goto UBKnot`, que abre com
`applymovement`. O passo da Lusamine rodaria **atrás da caixa de texto ainda
aberta**. A M3 não tem esse problema porque o bloco seguinte dela começa com
`msgbox`. Acrescentado `closemessage` no fim de `UBScene`.

### 12.5 A distribuição das UBs não chegava à tela em 2 dos 3 ramos

A tabela de §4.5 (Lusamine fica com Nihilego sempre que o jogador não a escolhe)
só era legível em `UBPickedKartana`. Nos outros dois ramos o jogador nunca
descobria quem ficou com o quê. As três falas agora **dizem a divisão inteira
em voz alta**, que é o único lugar onde uma decisão de personagem do design
§6.4 pode existir para quem joga.

### 12.6 O "não" ao Gold/Crystal não existia

§3.5 prometia, sobre a fala ociosa do rival: *"Pede para lutar, aqui, cedo — e o
não vem depois, na cena."* A cena não tinha esse beat em lugar nenhum. Foi
acrescentado `NewBarkTown_EventScript_UBRivalRefused`, entre a revelação da
Anabel e a escolha: o rival insiste, Looker e Anabel recusam — e a recusa é
*porque* ele é o único ali que não é polícia, nem Aether, nem Campeão, e é quem
bateu nas quarenta portas. Textos `UBRivalAsks` e `UBRivalRefused`.

Os dois tiles não permitem olhar para o jogador: o rival está em (21,13) e o
jogador em (20,12), que é diagonal. Ele vira para **oeste** (a coluna do
jogador), não para o norte — ao norte dele está o Looker. O mesmo vale para o
`turnobject` do rival em §5.

### 12.7 O travessão não existe no charmap

`—` (U+2014) não está em `charmap.txt` e **quebra o build** com
`error: unknown character U+2014`. Todos viraram `-`. As aspas curvas `“ ”`
(B1/B2) e as reticências `…` (B0) **estão** no charmap e foram mantidas.

### 12.8 O orçamento de §1.4 estava errado, e as lâmpadas voltaram ao lugar

A conta de §1.4 dava 16/16 porque somava as quatro light sprites como quatro
slots de object event. **Elas não são object events.**
`TrySpawnObjectEvents` faz um desvio explícito para elas
(`src/event_object_movement.c:3168`):

```c
if (template->graphicsId == OBJ_EVENT_GFX_LIGHT_SPRITE)
    SpawnLightSprite(npcX, npcY, cameraX, cameraY, template->trainerRange_berryTreeId);
else
    TrySpawnObjectEventTemplate(template, ...);
```

`SpawnLightSprite` (`:3056`) faz `CreateSprite()` em `gSprites[]` e nunca toca
em `gObjectEvents[]`. As quatro lâmpadas custam **zero** contra
`OBJECT_EVENTS_COUNT`. A conta verdadeira durante o incidente é
**12/16** — jogador, follower e os dez objetos da missão —, com as lâmpadas
inteiras.

Consequência: o único motivo técnico para escondê-las não existia. Elas foram
devolvidas a `FLAG_NIGHT_POKEMON` no `map.json`, e
`NewBarkTown_EventScript_ApplyLampVisibility` / `..._LampsStayHidden` foram
**apagados**. `FLAG_TEMP_5` não é usada por esta missão.

O que sobrou do orçamento, e continua valendo, está no comentário do código: o
teto importa porque objeto que não cabe **não spawna, sem erro nenhum**, e os
templates são percorridos **em ordem** — os dez desta missão são os últimos, e
quem some primeiro é o **Looker**.

### 12.9 A missão não mexe no sistema de luminosidade

Consequência direta de §12.8. Não há mais regressão cosmética nenhuma nas
lâmpadas: virar a noite parado em New Bark acende as quatro na hora, como
sempre acendeu, porque o campo `flag` delas voltou a ser lido a cada respawn de
câmera.

### 12.10 Confirmações que o plano pedia e que foram feitas

- `0x1044` estava livre; `CUSTOM_FLAGS_END` agora aponta para
  `FLAG_EVENT_ULTRABEAST_NEWBARK`.
- `grep` de `FLAG_TEMP_*`/`VAR_TEMP_*` em `NewBarkTown`,
  `NewBarkTown_PlayersHouse_1F`, `NewBarkTown_Lab` e `OlivineCity_House1`:
  **zero** ocorrências fora da trava `VAR_TEMP_1` de Olivine. Sem conflito.
- `FLAG_HIDE_NEWBARK_RIVALMARILL` é garantida: além dos três `removeobject` de
  `VAR_RIVAL_STATE` 2→3, há um `setflag` **explícito** em
  `data/maps/NewBarkTown/scripts.pory` na cena de `VAR_RIVAL_STATE` 0→1. O trio
  fica escondido no pós-E4. Mesmo assim, conferir no passo 3 de §10.
- Polaridade de `FLAG_NIGHT_POKEMON` conferida em `UpdateTimeOfDay`
  (`src/overworld.c:1642` e `:1673`): **limpa à noite**. O plano estava certo.
- `NewBarkTown_Lab_OnTransition` usa `goto_if_eq` (o `call` novo entrou antes);
  `NewBarkTown_PlayersHouse_1F_OnTransition` usa `call_if_eq` (posição livre, e
  entrou primeiro por uniformidade). O plano estava certo nos dois.
- `HEAL_LOCATION_NEW_BARK_TOWN` é (20,12) (`src/data/heal_locations.h:139-144`).
  O tile de fala é mesmo o tile de respawn.
- Planta de colisão reconferida com `dump_mapa.py` **depois** de inserir os dez
  objetos: os dez caem em tiles andáveis, e o bolso do Looker fecha — (21,11) é
  parede, (22,12) é a Anabel, (21,13) é o Gold/Crystal. Só (20,12) alcança.
- Checagem pós-edição de §2.3: `grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE"
  data/maps/OlivineCity_House1/scripts.pory` devolve **exatamente duas** linhas
  de código, ambas com `, 10,`.

### 12.11 O que continua pendente

Tudo em §9, mais o runtime inteiro de §10. Nada desta missão foi jogado.
