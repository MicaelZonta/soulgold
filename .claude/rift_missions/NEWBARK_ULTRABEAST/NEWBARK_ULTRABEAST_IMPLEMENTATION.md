# New Bark — Kartana + Guzzlord + Nihilego (Rift Mission 4) — implementação

**Status:** **história implementada (revisão 4)** — 22/09/2026,
`make -j$(nproc)` limpo. Runtime **pendente** (checklist §10).

**Ordem de precedência deste arquivo, de cima para baixo:**
**§13** (revisão 4 — a história, 22/09/2026) vence **§12** (divergências do
esqueleto, 20/09/2026), que vence o resto. Onde o texto antigo descrever a
cena de outro jeito, ele é **registro do raciocínio**, não contrato.

**Modo:** o esqueleto (skill `evento-esqueleto`) saiu em 20/09/2026 e continua
sendo a espinha: estado, visibilidade, gatilhos, batalha e retry não mudaram
uma linha. A revisão 4 (skill `evoluir-historia-de-evento`) trocou o que
acontece **em volta** deles.
**Roteiro da cena (falas e movimentos):** [`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md)
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6, §6.4 (V17).
**Missões anteriores:**
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](../BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (M1),
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](../MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (M2) e
[`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](../CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (M3)
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
  eixos + item (§4.4), com a ressalva condicional do design §6.
- Mesma estrutura padrão: escolha + boss simples, captura bloqueada, derrota =
  blackout e retry.
- Esta é a primeira missão que **esconde NPCs dentro de dois interiores**
  (a mãe em casa, o Elm no laboratório), porque os dois estão a um warp da cena.

---

## 0. Resumo do fluxo

```text
Cherrygrove resolvido                    VAR_RIFT_MISSIONS_STATE = 8
  └─ entrar em OlivineCity_House1 ─────▶ cena: Looker + Anabel, briefing M4 → 9
                                           + a conversa de Faller, sentada
                                           + setflag FLAG_EVENT_ULTRABEAST_NEWBARK
       └─ New Bark: cidade vazia (só o elenco da missão)
            └─ Fly / blackout largam o jogador em (20,12) = o tile de fala
            └─ falar com Looker ▶ relógio do Elm pela Anabel ▶ SIM
                 └─ cena 100% scriptada:
                    três rupturas em terra: Kartana + Guzzlord + Nihilego
                      └─ SINERGIA: as três derivam no mesmo instante, 2x
                           └─ a Nihilego dá o bote no jogador; o Azumarill corta
                                └─ Lusamine quer as três ▶ a MÃE a faz parar
                                     └─ Anabel dá o CONTRA: têm de cair juntas
                                          └─ o "não" ao rival ▶ a LUSAMINE o derruba
                                               └─ ESCOLHA (3 opções); os quatro batem juntos
                                                    └─ boss simples, 4 barras, Lv90, x150
       ┌──────────────────────────────────────────────────────┘
       ├─ perdeu / desistiu → blackout → (20,12) curado → flag setada → recomeça
       ├─ outro → reset silencioso → recomeça
       └─ venceu → as três caem juntas
                    └─ a CRIATURA sai do asfalto em (16,12)
                         └─ o rival a ataca sozinho e é jogado de volta
                              └─ ela ABSORVE as três
                                   └─ vira outra coisa e derruba os QUATRO num golpe
                                        └─ (opcional) reage à família Cosmog
                                             └─ some, e a rua fica inteira
                                                  └─ Anabel: nove UBs, quatro missões,
                                                     "we softened them for it"
                                                       └─ gancho → clearflag + estado 10
                                                          → warp no lugar
                    └─ Olivine House1: reunião do design §7
```

**A missão termina em derrota narrativa.** A cidade fica de pé, ninguém se
machuca, nenhuma janela quebra — e a coisa leva o que veio buscar e vai embora.
Isso é contrato da revisão 4, não sabor: o §7 e o §9 do design dependem dele.

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_ULTRABEAST_NEWBARK` | `include/constants/flags.h` | `0x1044` | Primeira livre depois de `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` (`0x1043`). **Atualizar `CUSTOM_FLAGS_END`** para apontar nela (hoje aponta para a de Cherrygrove, `flags.h:1788`). Conferir com `grep -n "0x1044" include/constants/flags.h` antes. |
| `LOCALID_NEWBARK_UB_*` | `include/constants/map_event_ids.h` | 16-27 | Doze linhas novas (dez no esqueleto, mais `_NECROZMA` 26 e `_ULTRA_NECROZMA` 27 na revisão 4; `_MARILL` 20 virou `_AZUMARILL`), **dentro da seção `// MAP_NEW_BARK_TOWN` que já existe** (`:823-826`, com `LOCALID_NEWBARK_MARILL 9`, `LOCALID_NEWBARK_RIVAL 10`, `LOCALID_NEWBARK_MARILL2 11`). Não criar cabeçalho novo, como na M3. |

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
| `NewBarkTown` | `FLAG_TEMP_5` | **(rev. 4)** Cache **só da criatura** — flag própria, pelo mesmo motivo: a cena faz `removeobject` nela |
| `NewBarkTown` | `FLAG_TEMP_6` | **(rev. 4)** Cache **só do que ela vira** — idem |
| `NewBarkTown` | `VAR_TEMP_2` | Resultado da batalha |
| `NewBarkTown` | `VAR_TEMP_3` | Escolha: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego. Sobrevive à batalha (voltar de batalha não passa por `LoadMapFromWarp`) |
| `NewBarkTown` | `VAR_TEMP_4` | **(rev. 4)** Espécie da família Cosmog na equipe (`SPECIES_NONE` = nenhuma), amostrada **depois** da batalha e relida pela conversa final |
| `NewBarkTown_PlayersHouse_1F` | `FLAG_TEMP_1` | Cache de visibilidade da mãe dentro de casa (§3.6) |
| `NewBarkTown_Lab` | `FLAG_TEMP_1` | Cache de visibilidade do Elm dentro do laboratório (§3.6) |

`FLAG_TEMP_3`, `FLAG_TEMP_4`, `FLAG_TEMP_5` e `FLAG_TEMP_6` **precisam ser
separadas de `FLAG_TEMP_1`** por um
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

Durante o incidente (pico, atualizado na revisão 4):

| Ocupante | Slots |
|---|---|
| Jogador | 1 |
| Follower do jogador | 1 |
| Elenco + UBs da missão | 10 |
| A criatura (`FLAG_TEMP_5`) | 1 |
| O que ela vira (`FLAG_TEMP_6`) | **0** no pico — só entra depois que as três UBs **e** a criatura saíram (§5.1) |
| 4 light sprites | **0** — ver abaixo |
| **Total** | **13 / 16** |

`TrySpawnObjectEvents` trata light sprite como caso especial
(`src/event_object_movement.c:3168`): ela vai para `SpawnLightSprite`, que faz
`CreateSprite()` em `gSprites[]` e **nunca** encosta em `gObjectEvents[]`. As
quatro lâmpadas de New Bark custam zero contra o teto de 16.

**Onde o orçamento importa de verdade:** objeto que não cabe **não spawna, sem
erro nenhum**, e `TrySpawnObjectEvents` percorre os templates **em ordem** — os
dez desta missão são os **últimos** do array. Estourar o teto tira o **Looker**
do mapa, e a missão fica sem como começar.

**Regra que fica para quem evoluir a cena:** a M4 tem **três** slots livres
(eram quatro; a revisão 4 gastou um com a criatura). Todo object event novo
consome um. Passar de 16 quebra em silêncio.

O par criatura / o-que-ela-vira só custa **um** slot porque os dois nunca estão
spawnados ao mesmo tempo: o `removeobject` de um e o `addobject` do outro ficam
sob o mesmo `fadescreen` (§5.1). São dois **templates** e duas flags temporárias,
porque `removeobject` seta a flag do template — mas um slot só.

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

**O briefing é onde a conversa de Faller acontece (revisão 4).** Pedido do
autor: *"o diálogo de Faller não faz sentido durante a luta, tem que ser
mostrado em Olivine antes de tudo e depois na hora do retorno"*. Três rupturas
abrindo juntas são a primeira coisa que a Anabel **sente de outra cidade** — de
uma cadeira em Olivine, com sessenta milhas de mar e uma montanha no meio —, e é
esse susto que a faz finalmente sentar o jogador e contar a coisa inteira. New
Bark fica só com a **retomada** de uma caixa (`UBAnabelPromise`, §5.1). Não
devolver a fala longa para a rua.

**Duas coisas que este briefing não diz, de propósito (revisão 4):**

1. **O Kukui não vai a New Bark.** A cadeia é **Elm → Kukui → Looker**: o Elm
   postou seis semanas de uma leitura que ele mesmo achava quebrada para o
   único homem que não riria dela, e esse homem telefonou para a polícia antes
   de terminar de ler. O Kukui **vai para casa**; quem fica dentro da análise é
   o Elm, que é dono do instrumento, das seis semanas e da cidade. O gancho da
   M3 foi reescrito do outro lado para plantar exatamente isso (§13.2).
2. **A Lusamine não é mencionada em lugar nenhum.** Ninguém mandou chamá-la e
   ninguém a anuncia — ela simplesmente está na estrada quando o jogador chega.
   Pôr o nome dela aqui gasta a única surpresa que a missão tem antes da
   criatura.

As três caixas do briefing (`Text_BriefingM4`, `Text_BriefingM4Faller`,
`Text_BriefingM4NewBark`), os dois "vá na frente" e os dois textos do estado ≥ 10
estão em [`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md), "Ato 1".

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
| 20 | `LOCALID_NEWBARK_UB_AZUMARILL` | `OBJ_EVENT_GFX_SPECIES(AZUMARILL)` | 22,13 | `FACE_UP` | `FLAG_TEMP_1` | `NULL` |
| 21 | `LOCALID_NEWBARK_UB_ELM` | `OBJ_EVENT_GFX_PROF_ELM` | 11,10 | `FACE_DOWN` | `FLAG_TEMP_3` | `NewBarkTown_EventScript_UBElm` |
| 22 | `LOCALID_NEWBARK_UB_LUSAMINE` | `OBJ_EVENT_GFX_LUSAMINE` | 3,12 | `FACE_RIGHT` | `FLAG_TEMP_4` | `NewBarkTown_EventScript_UBLusamine` |
| 23 | `LOCALID_NEWBARK_UB_KARTANA` | `OBJ_EVENT_GFX_SPECIES(KARTANA)` | 15,10 | `FACE_DOWN` | `FLAG_TEMP_2` | `NULL` |
| 24 | `LOCALID_NEWBARK_UB_GUZZLORD` | `OBJ_EVENT_GFX_SPECIES(GUZZLORD)` | 23,15 | `FACE_UP` | `FLAG_TEMP_2` | `NULL` |
| 25 | `LOCALID_NEWBARK_UB_NIHILEGO` | `OBJ_EVENT_GFX_SPECIES(NIHILEGO)` | 14,13 | `FACE_RIGHT` | `FLAG_TEMP_2` | `NULL` |
| **26** | `LOCALID_NEWBARK_UB_NECROZMA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA)` | 16,12 | `FACE_RIGHT` | **`FLAG_TEMP_5`** | `NULL` |
| **27** | `LOCALID_NEWBARK_UB_ULTRA_NECROZMA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA_ULTRA)` | 16,12 | `FACE_RIGHT` | **`FLAG_TEMP_6`** | `NULL` |

Conferido em 20/09/2026: `OBJ_EVENT_GFX_LOOKER` (334), `ANABEL` (70),
`LUSAMINE` (330), `PROF_ELM` (242) e `MOM` (215) existem em
`include/constants/event_objects.h`; `KARTANA`, `GUZZLORD` e `NIHILEGO` têm
bloco `OVERWORLD(` (`SIZE_32x32`, `SHADOW_SIZE_M`) e `.isUltraBeast = TRUE` em
`src/data/pokemon/species_info/gen_7_families.h`.

Reconferido em 22/09/2026 (revisão 4): `AZUMARILL`, `NECROZMA` e
`NECROZMA_ULTRA` também têm bloco `OVERWORLD(` (`SIZE_32x32`). As duas
Necrozma nascem **no mesmo tile (16,12)**, e isso é seguro **porque nunca
estão spawnadas ao mesmo tempo** — o `removeobject` de uma e o `addobject` da
outra ficam sob o mesmo flash (§5.1). Elas têm flags temporárias **próprias**
justamente para que esse `removeobject` não encoste em mais ninguém.

**O Marill virou Azumarill (revisão 4, pedido do autor):** nesse ponto da
história o Gold/Crystal já evoluiu o parceiro. O `local_id` 20 foi renomeado
junto (`LOCALID_NEWBARK_UB_AZUMARILL`) — os três objetos escondidos por
`FLAG_HIDE_NEWBARK_RIVALMARILL` (locais 9, 10, 11) **não** mudam: são o par
antigo, do começo do jogo, e continuam mortos no pós-E4.

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

### 3.4 Planta da cena (colisão real) — atualizada na revisão 4

Lida em 20/09/2026 com as máscaras corretas deste repo (§12.7 do doc da M3:
metatile `0x07FF`, colisão `0x0800` shift 11) e **reconferida com
`dump_mapa.py` em 22/09/2026**, depois de acrescentar os dois objetos novos e
toda a coreografia da revisão 4.

**Não há um único tile de água em `LAYOUT_NEW_BARK_TOWN`** (30×39). Diferente da
M3, aqui a leitura de comportamento não muda nenhuma decisão: a cena é de rua.

```text
      x= 2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
  y= 9   #  #  #  .  .  #  #  #  D  #  .  #  .  .  .  .  #  #  #  #  #  #  #  #
  y=10   #  #  .  .  .  .  .  .  .  E' .  .  .  1  1a 1b #  #  #  #  #  #  #  #
  y=11   .  .  .  .  .  .  .  .  .  .  .  .  .  .  Nk #  #  #  d  #  #  .  .  .
  y=12   .  U' .  .  .  .  .  .  .  .  .  .  .  .  N  U  M  *  K  A  E  .  .  .
  y=13   .  .  .  .  .  .  .  .  .  .  .  .  2  2a 2b 2c 2d 2e .  G  z  .  .  .
  y=14   .  .  .  .  .  .  .  #  .  .  .  .  .  .  a3 a2 a1 aX .  .  z' .  .  .
  y=15   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  3  3a 3b
  y=16   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .

  D  porta do laboratorio (warp 10,9)      d  porta da casa do jogador (warp 20,11)
  *  jogador (20,12): Fly, blackout e o UNICO tile de fala do Looker
  K  Looker (21,12)   A  Anabel (22,12)    M  mae (19,12)
  G  Gold/Crystal (21,13)                  z  Azumarill no inicio (22,13)
  z' Azumarill depois do corte (19,14)
  U' Lusamine no inicio (3,12)             E' Elm no inicio (11,10)
  U  Lusamine depois do fade (18,12), e (17,12) do no em diante
  E  Elm depois do fade (23,12)
  1  Kartana (15,10) -> 1a (16,10) -> 1b (17,10) na deriva em uníssono
  2  Nihilego (14,13) -> 2a -> 2b na deriva, depois 2c 2d 2e no bote,
     parando em (19,13): uma diagonal do jogador e logo abaixo da mãe
  3  Guzzlord (23,15) -> 3a (24,15) -> 3b (25,15); (26,15) é parede
  a1 a2 a3  a corrida do Azumarill contra a criatura, terminando em (16,14)
  N  a criatura (16,12) — e o mesmo tile do que ela vira
  Nk (16,11) é para onde a Kartana é arrastada antes de ser comida
```

**O bolso do Looker.** (21,12) tem parede ao norte — (21,11) é a parede da casa
do jogador, colisão 1, conferido —, a Anabel a leste e o Gold/Crystal ao sul. O
único vizinho livre é **(20,12)**, a oeste. Não é preciso `getplayerxy`.

**E (20,12) é onde o jogo larga o jogador nos dois caminhos que importam:**
`HEAL_LOCATION_NEW_BARK_TOWN` é (20,12) (`src/data/heal_locations.h:139-144`),
`NewBarkTown_OnLoad` refaz o `setrespawn` a cada load, e o Fly usa a mesma heal
location (`sMapHealLocations[MAPSEC_NEW_BARK_TOWN]`, `src/region_map.c:340`).
Chegar de Fly e voltar de um blackout põem o jogador **exatamente no tile de
fala**. É a melhor recuperação do arco e ela veio de graça.

**Ninguém fica ao sul do jogador, nem por um passo.** (20,13) continua vazio a
cena inteira, e é por isso que a coreografia do Azumarill dá a volta por **y=14**
em vez de cortar reto: ele nunca precisa parar na frente do jogador. Esse
contrato do esqueleto sobreviveu à revisão 4 sem exceção.

**Todos os 26 tiles novos da revisão 4 foram medidos**, e nenhum par de atores
disputa tile no mesmo passo: a deriva em uníssono acontece em três linhas
diferentes (y=10, y=13, y=15); o bote da Nihilego corre em y=13 enquanto o
Azumarill corre em y=14; o arrasto da absorção aponta os três para (16,12) por
caminhos que não se cruzam.

**As três UBs são alcançáveis a pé**, diferente da M3. Não é problema: elas só
existem enquanto o jogador está sob `lockall`, e têm `script: NULL`. Registrado
para que ninguém "conserte" isso pondo colisão onde não precisa.

### 3.5 Conversas antes da cena

Cinco NPCs com uma fala curta cada, no padrão da M3 (`lock`, `faceplayer`,
`msgbox`, `closemessage`, `turnobject` de volta ao olhar do `map.json`,
`release`). São o que dá ao jogador a chance de conhecer a Lusamine **sozinho,
na estrada**, antes de tudo.

| Quem | Tile | Nota técnica |
|---|---|---|
| Lusamine | (3,12) | Primeira fala dela no arco. `turnobject DIR_EAST` no fim. Ramo extra de família Cosmog. |
| Elm | (11,10) | `turnobject DIR_SOUTH`. Ramo extra de família Cosmog. |
| Mãe | (19,12) | `turnobject DIR_EAST`. (19,11) é parede. |
| Gold/Crystal | (21,13) | `turnobject DIR_NORTH`. **Pede para lutar aqui** — primeira das três metades do arco (as outras duas estão na cena). |
| Anabel | (22,12) | `turnobject DIR_WEST`. Só alcançável pela volta longa, por y=14. **Não** explica nada aqui: a conversa dela aconteceu em Olivine. |

Os textos estão em [`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md), "Ato 2".

#### 3.5.1 Reações opcionais à família Cosmog (revisão 4)

Pedido do autor: *"Necrozma deve ter alguma reação opcional e NPCs também sobre
Cosmog na party"*. Padrão do design §4.11 e da M3: `specialvar VAR_RESULT,
CheckMysteryEggPokemon`, **zero flag, zero var persistente**, e sem o Pokémon a
cena corre idêntica.

| Onde | Quem | O que |
|---|---|---|
| Conversa ociosa | **Lusamine** | Design §6.4 finalmente na tela: ela é a única pessoa viva que sabe como aquela luz se parece do outro lado, porque usou um. E ela é quem diz, na mesma caixa, que **nada disso é culpa do jogador** — regra inegociável do design. |
| Conversa ociosa | **Elm** | Ele é quem identificou o ovo. Dois quadros de encantamento e a lembrança de onde está pisando. |
| Depois da batalha, §5.1 | **O que a criatura vira** | Uma fala por estágio: Cosmog/Cosmoem (ela *espera* por ele) e Solgaleo/Lunala (ela **hesita** — a única coisa na rua inteira que a fez parar). |
| Conversa final, §5.1 | **Lusamine** | Relê `VAR_TEMP_4` e fecha: foi a única vez que aquilo largou algo que queria. |

A amostragem de §5.1 é feita **depois** da batalha de propósito — a batalha pode
evoluir o Pokémon — e fica em `VAR_TEMP_4` para a conversa final reler.

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

**Reescrita na revisão 4.** A ordem dos beats abaixo é o contrato; o texto final
está no `.pory`, com um comentário por bloco explicando por que ele existe.

### 4.1 Pré-checagens (`NewBarkTown_EventScript_UBLooker`)

Inalterado desde o esqueleto. Só alcançável de (20,12), olhando para leste. Nada
muda de estado antes do SIM; o SIM é o último ponto de saída. Batalha simples,
então não há checagem de equipe; não há presente, então a regra da skill
`entregar-pokemon-ou-ovo` não se aplica.

O relógio do Elm continua vindo **antes** do SIM, mas quem o lê é a **Anabel**
(`UBClockRelay`), porque o Elm está em (11,10), **fora da câmera** — §12.3. Não
devolver a voz dele para cá sem mover o objeto junto.

Falas: [`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md), "Ato 3".

### 4.2 A cena (`NewBarkTown_EventScript_UBScene`)

**A cena inteira — beats, movimentos e falas — está em [`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md), "Ato 4".** Aqui só o
que a implementação precisa garantir:

- `lockall` + `hidefollower` na primeira linha.
- **O Elm e a Lusamine entram em quadro pelo template, não por `setobjectxy`.**
  ⚠ `setobjectxy` **não funciona** neles e **falha em silêncio** (§8): os dois
  estão fora da janela de spawn. O trio obrigatório é
  `removeobject` → `setobjectxyperm` → `clearflag` + `addobject`, nesta ordem, e
  é por isso que Elm e Lusamine **não** dividem `FLAG_TEMP_1`.
- **A sinergia é o drift em uníssono:** as três andam um tile a leste no mesmo
  frame, de três cantos do mapa que não se enxergam, duas vezes. Quem percebe que
  é o mesmo instante é o **Elm** — o único na estrada com um relógio.
- **O bote da Nihilego** termina em (19,13): diagonal ao jogador e **embaixo da
  mãe**. O corte do Azumarill vai **pela volta**, por y=14, porque (20,13) é
  deliberadamente vazio; os dois caminhos nunca dividem um tile.
- **A virada da mãe é o beat** (`turnobject DIR_WEST`, dando as costas à própria
  filha/filho para encarar a Lusamine). Não encurtar.
- O `closemessage` antes do passo da Lusamine é **load-bearing**: sem ele o passo
  dela roda atrás de uma caixa de texto aberta.
- **As três metades do arco do Gold/Crystal** — pedido na conversa ociosa, "não"
  na cena, Lusamine derrubando o "não" — não podem ser separadas.
- Flash = `fadescreenswapbuffers`, nunca `fadescreen` (§14).

### 4.3 A escolha e a distribuição

`dynmultichoice ... TRUE, 3 ...` (`maxBeforeScroll` 3 para as três opções caberem
sem rolagem), resultado em `VAR_TEMP_3` (0 Kartana, 1 Guzzlord, 2 Nihilego), "!"
sobre a escolhida. A escolha é **por tentativa**.

**Distribuição** (design §6.4) — a Lusamine fica com a Nihilego sempre que o
jogador não a leva; é a que ela veio buscar e a que ela tem de responder por.
Decisão de personagem, não conveniência:

| Escolha | Lusamine | Anabel |
|---|---|---|
| 0 Kartana | Nihilego | Guzzlord |
| 1 Guzzlord | Nihilego | Kartana |
| 2 Nihilego | Guzzlord | Kartana |

Gold/Crystal são o quarto par de mãos na que o jogador pegar. Cada fala
`UBPicked*` **diz** quem fica com quem, para a tabela ser legível de dentro do
jogo e não só deste doc.

### 4.4 Batalha — boss simples, quarto degrau da escala

**Inalterada em tudo**: `setbossbattle 4, SPECIES_NONE, 150`, nível 90, movesets
e itens dos três, `B_FLAG_NO_CATCHING`, `B_FLAG_NO_WHITEOUT` **não** setada,
todos os resultados tratados, derrota = blackout + retry com a escolha refeita,
e a ressalva condicional do design §6 (se x140 for parede na M3, este número
herda a correção; ordem dos parafusos no comentário do `.pory`).

`UBGotAway` ganhou uma linha: *"All four of us."*

---

## 5. Etapa D — A vitória que não é vitória

**Esta é a mudança grande da revisão 4.** O esqueleto terminava com as três UBs
voltando e a cidade de pé. Agora a cidade fica de pé e **a missão é perdida**,
que é o pedido do autor: *"Necrozma absorve os 3, se transforma em Ultra
Necrozma e derrota todos rapidamente e desaparece"* / *"defendemos a cidade mas
perdemos"*.

### 5.1 Contrato técnico da Etapa D

**Beats, movimentos e falas:** [`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md), "Ato 5", "Ato 6" e "Ato 7".

- **As três UBs NÃO são removidas quando o jogador vence.** Elas ficam caídas na
  estrada — precisam estar lá para o que vem recolhê-las. A remoção acontece só
  na absorção.
- **A criatura entra pela rua**, em (16,12), sob `FLAG_TEMP_5` (flag própria).
- **O que ela vira** entra sob `FLAG_TEMP_6`, no **mesmo tile**, debaixo de um
  flash só: os dois **nunca** existem ao mesmo tempo — é por isso que o pico de
  objetos da cena é 13 e não 14, e por isso cada um precisa da própria `FLAG_TEMP`.
- **As três UBs compartilham `FLAG_TEMP_2`** e isso é correto: as três saem juntas.
- Arrastos da absorção, todos medidos e sem se cruzarem: Kartana (17,10)→(16,11),
  Nihilego (19,13)→(17,13), Guzzlord (25,15)→(23,15).
- **Reação opcional à família Cosmog** (§5.2): `CheckMysteryEggPokemon` →
  `VAR_TEMP_4`, amostrada **depois** da batalha (ela pode evoluir o Pokémon) e
  relida pela conversa final. Zero flag, zero var persistente.
- **No rescaldo ninguém anda.** Todo mundo já está na linha e (20,13) continua
  vazio, então a caixa de texto não esconde ninguém. O Azumarill fica em (18,14)
  e a Lusamine em (17,12), onde a luta deixou os dois.
- **A ordem das caixas do rescaldo é o argumento** e não pode ser reordenada: as
  pessoas (Looker, sempre) → o custo (Elm) → o que aquilo era (Anabel, a conta de
  nove) → a derrota dita por quem tem autoridade (Lusamine) → o rival → a mãe →
  a promessa → [Cosmog] → o gancho.
- **Fecho:** `fadescreen FADE_TO_BLACK` → `clearflag FLAG_EVENT_ULTRABEAST_NEWBARK`
  + `setvar VAR_RIFT_MISSIONS_STATE, 10` (invariante: flag e var juntas) →
  `warpsilent MAP_NEW_BARK_TOWN, 20, 12` → `waitstate` → `releaseall`.

### 5.2 O que não pode sair daqui

- A **conversa de Faller não volta** para esta rua: ela acontece em Olivine,
  sentada (§2.3). New Bark fica só com a retomada de uma caixa.
- As **três metades** do arco do Gold/Crystal — o pedido na conversa ociosa, o
  "não" na cena e a Lusamine derrubando o "não" — são uma coisa só.
- A cidade fica de pé e **ninguém ganha**. Era esse o plano desde a M1.

---

## 6. Arquivos tocados (checklist de implementação)

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_NEWBARK 0x1044` + comentário; `CUSTOM_FLAGS_END` movida (esqueleto; **inalterado** na rev. 4) |
| `include/constants/map_event_ids.h` | locais 16-25 (esqueleto) + **26 `_NECROZMA` e 27 `_ULTRA_NECROZMA`**; `_MARILL` 20 → `_AZUMARILL` |
| `data/maps/OlivineCity_House1/scripts.pory` | esqueleto: gatilho 2/4/6/8, ramo M4, estados 8/9/≥10. **Rev. 4:** `Text_BriefingM4` reescrito inteiro (cadeia Elm→Kukui→Looker, Lusamine fora, a conversa de Faller) e uma caixa do `Text_ReunionOpen` ajustada — "four in four" deixou de ser vitória |
| `data/maps/CherrygroveCity/scripts.pory` | **Rev. 4:** a última caixa do `Text_UBHook` do Kukui. Ele **não** vai a New Bark; vai ler todos os logs de Johto, o que é o que produz o aviso do Elm. Par obrigatório com o `Text_BriefingM4` |
| `data/maps/NewBarkTown/map.json` | flag do evento em 7 objetos; Marill → **Azumarill**; 12 objetos novos no fim (25 → 27 templates). As 4 light sprites **não** mudam (§3.1.1) |
| `data/maps/NewBarkTown/scripts.pory` | uma linha `call` no `ON_TRANSITION` existente; bloco da missão **reescrito inteiro** na rev. 4: `FLAG_TEMP_5/6` na visibilidade, helpers `UBFlash`/`UBShake`, reações ao Cosmog nas conversas, sinergia, bote, corte, nó, contra-ataque, o rival admitido, escolha, boss, a criatura, a absorção, o que ela vira, rescaldo, gancho, 13 rótulos de movimento e todos os textos |
| `data/maps/NewBarkTown_PlayersHouse_1F/scripts.inc` | **`.inc` direto — este mapa não tem `.pory`**; recálculo da mãe (§3.6) |
| `data/maps/NewBarkTown_Lab/scripts.pory` | recálculo do Elm (§3.6) |
| `data/maps/NewBarkTown_PlayersHouse_1F/map.json` | `flag` do `LOCALID_MOM` vira `FLAG_TEMP_1` |
| `data/maps/NewBarkTown_Lab/map.json` | `flag` do `LOCALID_ELM` vira `FLAG_TEMP_1` |

**Ordem de edição.** Flags/localids → `map.json` dos dois interiores **junto com**
os `ON_TRANSITION` deles (nunca um sem o outro) → `map.json` de New Bark → resto
do `scripts.pory` de New Bark → Olivine → Cherrygrove → build.

---

## 7. O que ainda é simples × o que não pode regredir

**Continua simples de propósito (pode melhorar):**

- A chegada do Elm e da Lusamine ainda é um fade com `setobjectxyperm` +
  `addobject`. Podiam entrar correndo.
- As rupturas continuam sendo tremor + flash branco. Podiam ter paleta, clima e
  música próprias, e abrir em tempos diferentes.
- As lutas da Lusamine e da Anabel continuam fora de tela. Batalha de verdade
  contra qualquer uma das duas **não** é o plano (design §7/§9).
- O tombo dos quatro em §5.1 é narração + tremor grande, não recuo por tile.
- A cena inteira se repete a cada tentativa. Mitigação possível (não feita): um
  ramo curto por `VAR_TEMP` quando a cena já rodou nesta visita. **Não** usar
  flag persistente para isso.

**Não pode regredir sem atualizar este doc e o design:**

- Valores 8/9/10 da var e a invariante flag ⇔ 9.
- **A missão termina em derrota.** A criatura absorve as três, vira outra coisa,
  derruba os quatro e sai. A cidade fica inteira e ninguém se machuca.
- **A conta de nove** (§5.1 item 3): quatro missões, nove Ultra Beasts, todas
  levadas por ela. É o que reenquadra o arco inteiro, e o design §7/§9 conta com
  isso.
- A conversa de Faller acontece **em Olivine**, sentada, antes de tudo, e volta
  **uma vez** no rescaldo. Não devolver a fala longa para a rua.
- **O Kukui não vai a New Bark**, e a cadeia é Elm → Kukui → Looker. O gancho da
  M3 e o `Text_BriefingM4` são um par.
- **A Lusamine não é anunciada em Olivine.**
- A distribuição das UBs (Lusamine fica com Nihilego sempre que o jogador não a
  escolher) e o Gold/Crystal indo **com o jogador**.
- Quem derruba o "não" ao Gold/Crystal é a **Lusamine**, e é consequência direta
  do que a mãe disse na cena anterior.
- A sinergia **mostrada antes de explicada**, e o contra-ataque como motivo
  interno da escolha.
- O tile de fala único (20,12) e o bolso do Looker.
- **(20,13) vazio**, a cena inteira, inclusive em passagem.
- `FLAG_TEMP_3`, `_4`, `_5` e `_6` separadas da `FLAG_TEMP_1`, e as três
  `setflag` incondicionais no `ON_TRANSITION`.
- Os dois recálculos de interior (§3.6) andando junto com os dois `map.json`.
- O orçamento de §1.4: **três** slots livres, e acabou.
- As quatro light sprites ficam com `FLAG_NIGHT_POKEMON`.

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

- **Orçamento de objetos (§1.4).** Pico medido em código: **13/16** durante a
  chegada da criatura. Testar **à noite** mesmo assim — a conta é leitura de
  código, não medição em jogo. Se algum ator sumir, é aqui.
- **Dois templates no mesmo tile (16,12).** A criatura e o que ela vira nunca
  coexistem, e o `removeobject`/`addobject` fica sob um flash. É o ponto novo de
  falha silenciosa da revisão 4: se a segunda não aparecer, o problema é ordem,
  não coordenada.
- **Coreografia nova sem runtime.** Quatorze `applymovement` novos, medidos com
  `dump_mapa.py` mas não jogados. Os mais arriscados: a deriva simultânea das
  três (três `waitmovement` seguidos) e o corte do Azumarill em paralelo ao bote
  da Nihilego.
- **x150 nunca foi jogado, e x140 também não.** Ressalva do design §6; caminho de
  redução no comentário do `.pory`.
- **Três sprites 32x32 ao mesmo tempo**, um deles o Guzzlord — e, por alguns
  segundos, quatro, com a criatura. Pode ficar visualmente pesado.
- **A cena inteira se repete a cada tentativa**, e ficou mais longa que no
  esqueleto. Num retry isso cansa mais do que cansava.
- **A mãe e o Elm dentro de casa** continuam sendo a única regressão possível em
  conteúdo pré-existente, e é silenciosa.
- **`VAR_NEWBARK_TOWN_STATE` e `VAR_RIVAL_STATE` no pós-E4** foram deduzidos por
  leitura de código, não medidos em jogo.
- **A reunião de Olivine (PRÉ-NECROZMA) foi escrita quando a M4 terminava em
  vitória.** A revisão 4 ajustou **uma** caixa (`Text_ReunionOpen`). O resto
  daquela cena continua coerente, mas quem for evoluí-la deve reler §5.1 antes.
- Beast Balls com a Anabel continuam pendentes desde a M1.

---

## 10. Teste em runtime

**Nada disto foi jogado.** Ordem otimizada para achar cedo o que quebra mais
coisas.

1. **Com a missão inativa:** entrar na casa do jogador e no laboratório. A mãe e
   o Elm têm de estar lá, normais (erro seguro de §3.6).
2. Estado 8, entrar em `OlivineCity_House1` pela porta (4,8): briefing M4
   completo, **com a conversa de Faller**, estado vira 9. Conferir que o Kukui
   **não** é dito como indo a New Bark e que a **Lusamine não é citada**.
3. Estado 9, chegar em New Bark **por Fly**: o jogador cai em (20,12); a cidade
   está vazia; o elenco está nos sete tiles; as três UBs, a criatura e o que ela
   vira **ausentes**; **nenhum segundo Gold/Crystal em (12,13)**; o parceiro do
   rival é um **Azumarill**.
4. **Repetir o passo 3 à noite.** As quatro lâmpadas continuam acesas. Se algum
   ator da missão não aparecer, a conta de §1.4 está errada.
5. Entrar em casa e no laboratório **durante** o incidente: os dois vazios.
6. Falar com o Looker de (21,13), (22,12) e (21,11) — impossível. Só (20,12).
7. Falar com a Lusamine em (3,12) e com o Elm em (11,10). **Com um Cosmog /
   Cosmoem / Solgaleo / Lunala na equipe**, conferir as caixas extras dos dois —
   e **sem** a família, conferir que não sobra caixa nenhuma.
8. SIM → cena inteira. Pontos de falha silenciosa, em ordem:
   a Lusamine aparecendo em (18,12) e o Elm em (23,12); as três derivando
   **juntas**, duas vezes; a Nihilego parando em (19,13) e o Azumarill chegando
   em (19,14) **por fora**; a mãe virando para oeste no nó e voltando no fim;
   a caixa de texto não cobrindo o Gold/Crystal nem o Azumarill.
9. Escolher e **perder de propósito**: blackout devolve o jogador **curado** em
   (20,12), cidade ainda vazia, Looker ainda em (21,12), **nenhuma UB e nenhuma
   criatura na rua**, e todos os atores de volta aos tiles do `map.json`. Falar
   de novo e escolher **outra** UB.
10. Desistir com "Run" numa segunda tentativa: mesmo resultado.
11. Vencer, e conferir a segunda metade inteira: a criatura nascendo em (16,12);
    o Azumarill correndo até (16,14) e sendo jogado para (18,14); as três
    arrastadas e sumindo juntas; **o que ela vira aparecendo no mesmo tile**; os
    quatro batendo para oeste; o tremor grande; a saída dela; o repovoamento, o
    estado 10, o stub/reunião em Olivine, a mãe e o Elm de volta.
12. Repetir o passo 11 **com** e **sem** a família Cosmog na equipe, e uma vez
    com um Cosmog que **evolui durante a batalha** (é por isso que a amostragem
    é feita depois).
13. Salvar e recarregar em cada estado (8, 9, 10) e entrar no mapa por Route 29 e
    por Route 27, não só por Fly.
14. Regressões: Blackthorn, Mahogany e Cherrygrove povoadas; o gancho novo do
    Kukui em Cherrygrove; estados 3, 5 e 7 como antes; o presente do Friendly
    Trader de Cherrygrove ainda não repetível.

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

A tabela de §4.3 (Lusamine fica com Nihilego sempre que o jogador não a escolhe)
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

---

## 13. Revisão 4 — a história (22/09/2026)

Feedback do autor sobre o esqueleto: *"o esqueleto está pronto, agora vamos
montar uma história épica"*. Feito com a skill `evoluir-historia-de-evento`,
tendo a revisão 3 de Cherrygrove como modelo. **Esta seção vence §12, que vence
o resto do arquivo.**

Nada de estado mudou: `VAR_RIFT_MISSIONS_STATE` 8/9/10, a invariante flag ⇔ 9, a
estrutura escolha + boss, `B_FLAG_NO_CATCHING`, o tratamento dos cinco
resultados de batalha e o retry por blackout estão **exatamente** como o
esqueleto os deixou.

### 13.1 Pedido → como ficou

| Pedido | Como ficou |
|---|---|
| Esqueleto pronto; montar uma **história épica** | Arco completo (§4.2–§5.2 e o roteiro): sinergia mostrada, perigo direto ao jogador, corte de quem ninguém autorizou, o nó da Lusamine desfeito pela mãe, o contra-ataque que exige quatro pessoas, o "não" derrubado por quem acabou de aprender a perguntar, e a vitória tomada de volta — absorção, transformação, quatro treinadores no chão em um golpe. |
| Diálogos mais naturais e de acordo com a personalidade | Todas as falas reescritas ou retrabalhadas pela voz do design §3.1. Looker teatral e formal que pergunta pelas pessoas antes do relatório; Anabel separando observação de hipótese e cortando o próprio assunto; Lusamine elaborada e aprendendo a perguntar em tempo real; Elm humilde e **concreto** (o relógio, a margem do caderno, "three into one"); mãe curta e sem sermão; Gold/Crystal sem plaquinha nenhuma, nos dois gêneros. Zero `@ SKELETON:` de fala em `data/maps/NewBarkTown`. |
| A vibe é boa mas falta história | Ver a linha acima e o §0: a cena agora tem começo (a cidade que não evacua e um relógio contando), meio (a sinergia e o plano que ela obriga) e fim (a coisa que estava esperando o plano funcionar). |
| **O Kukui não vai a New Bark**; faz mais sentido o **Elm avisar o Kukui, que avisa o Looker**, e o Elm estar por dentro da análise | `Text_BriefingM4` reescrito inteiro (§2.3) e a última caixa do `Text_UBHook` de **Cherrygrove** reescrita junto (§13.2): o Kukui vai para casa lendo todos os logs de Johto, acha as seis semanas de "check the sensor" do Elm e telefona para a polícia. Quem fica no chão é o Elm — é o instrumento dele, a cidade dele e o erro dele. A fala ociosa do Elm em New Bark conta a mesma cadeia pela boca dele. |
| **Anabel ter sentido de longe** e explicar o que é ser Faller **em Olivine**, por serem 3 Ultra Beasts | §2.3. Três rupturas juntas são a primeira coisa que ela sente de **outra cidade** — "Blackthorn I felt from the street… these three I felt from this chair. From Olivine." É esse susto que a faz pedir a cadeira e contar a coisa inteira, sentada, antes de qualquer perigo. |
| O diálogo de Faller **não faz sentido durante a luta**: mostrar em Olivine antes de tudo e depois **na hora do retorno** | A fala longa saiu de `UBAnabelFaller` (que não existe mais). Em campo sobraram duas caixas (`UBAnabelStands`), e ela mesma recusa repetir: *"I'm not saying it again in the middle of a road."* A retomada é **uma** caixa no rescaldo (`UBAnabelPromise`, §5.1 item 7). Comentário no `.pory` proibindo devolver a fala longa. |
| **Lusamine não deve ser mencionada em Olivine**; ela simplesmente está na cidade | As três caixas dela saíram do briefing. Na rua, a fala ociosa dela ganhou *"Nobody sent for me. I read the same numbers they did and I got in a boat."*, e quando ela entra na linha o Looker diz que ninguém o avisou. |
| O rival **já tem Azumarill** nesse ponto | `local_id` 20: `OBJ_EVENT_GFX_SPECIES(MARILL)` → `AZUMARILL`, e a constante renomeada para `LOCALID_NEWBARK_UB_AZUMARILL`. Os três objetos antigos escondidos por `FLAG_HIDE_NEWBARK_RIVALMARILL` não mudam. |
| **O rival Gold/Kris luta com o Necrozma dessa vez** | Roteiro, "Ato 5". Ele vai sozinho, sem ordem, porque foi admitido trinta segundos antes. O Azumarill corre (19,14)→(16,14), bate duas vezes e é **jogado** de volta sem se virar. E ele já tinha lutado antes: é o Azumarill dele que corta o bote da Nihilego na cena, **antes** de qualquer adulto autorizar qualquer coisa. |
| O rival **se sente incapaz**; é interessante ele estar tentando se provar | Plantado na fala ociosa ("time completo há um ano, e nunca estive na sala onde importava"), regado no "não" e no *"Right. Doors. It's always doors."*, colhido no *"…Say that again. No. Don't. If you say it again I'll cry"* quando a Lusamine o admite, e fechado no rescaldo: *"I finally got in, and it didn't even turn its head."* — respondido pela Lusamine, não pelo jogador. |
| A temática de **sinergia** entre as UBs é ótima: reforçar e virar padrão | §4.3, e a sinergia agora é **estrutural**, não decorativa: as três derivam no mesmo instante de três pontos que não se enxergam; o Elm mede; a Anabel nomeia ("one thing wearing three bodies"); e o **contra-ataque** que isso obriga (cair no mesmo instante) é o que cria a vaga do quarto treinador e dá motivo interno ao menu de escolha. Registrado como regra comum do arco no design §6. |
| **Forçar Lusamine, rival, você e Anabel a trabalhar em equipe** | §4.2–§4.3: quatro pessoas, três alvos, uma marca — o Gold/Crystal vai **com o jogador**, e as três falas de escolha dizem a divisão inteira e fecham em *"On my mark. All four."* E §5.1 usa a mesma formação contra a coisa nova, **de propósito**, para mostrar que dessa vez não basta. |
| **Necrozma absorve as 3, vira Ultra Necrozma, derrota todos rapidamente e desaparece** | §5.2 a §5.1. Dois templates novos no mesmo tile (16,12), flags temporárias próprias, nunca spawnados juntos. Absorção no padrão das M1/M2/M3, agora com três. O golpe é um `applymovement` dos quatro + flash + tremor grande, e a narração diz o resto: *"It was over before any of them finished the motion."* Nenhuma batalha nova: a do jogador contra Ultra Necrozma continua sendo o design §9. |
| A história acaba com **"defendemos a cidade mas perdemos"** — o que era esse ser, qual era o plano dele desde o começo | §5.1. A Lusamine exige que se diga primeiro que ninguém se machucou e nenhuma janela quebrou, e **então** diz que perderam. A resposta à pergunta é a conta da Anabel: nove Ultra Beasts, quatro missões, todas levadas por ela — *"It was never attacking us at all."* / Looker: *"…It was collecting."* / Anabel: **"And we softened them for it. Four times."** A narração da saída fecha: nada quebrou, porque **nunca foi pela cidade**. |
| Gosto da plotline da **mãe ensinando a Lusamine a acreditar nos outros**, porque ela acredita em você | A fala da Lusamine, engordada com o exemplo concreto (a manhã em que ela deixou uma criança de dez anos ir a Cherrygrove sozinha) e a tese: *"Believing in somebody is worse than doing it yourself. It just happens to be the thing that works."* E o "não" derrubado é a lição **virando ação** na cena seguinte, quando a Lusamine contraria a polícia para pôr o garoto na linha. |
| **Reação opcional do Necrozma e dos NPCs** sobre Cosmog na party | §3.5.1 e §5.1: Lusamine e Elm nas conversas ociosas, a coisa nova depois da batalha (uma fala por estágio) e a Lusamine outra vez na conversa final, relendo `VAR_TEMP_4`. Zero flag, zero var persistente; sem o Pokémon a cena é idêntica. É também onde o design §6.4 (ela usou um Cosmog, ela sabe como aquilo se parece do outro lado) finalmente chega à tela — com a regra inegociável dita por ela: **não é culpa do jogador**. |

### 13.2 Ambiguidades e contradições resolvidas por escrito

- **"O Kukui não vai" × o gancho da M3 dizia que ele ia.** O pedido novo vence
  (skill `evoluir-historia-de-evento` §1), e o trecho contrário foi **reescrito**
  em vez de deixado vivo: a última caixa do `CherrygroveCity_Text_UBHook` deixou
  de ser *"And I'm coming with"* e virou ele indo para casa ler todos os logs da
  região — que é exatamente o que produz o aviso do Elm. O par
  gancho-da-M3 ↔ `Text_BriefingM4` está anotado nos dois arquivos.
- **"O rival luta" × o design §6.4 dizia "nenhum dos três novos batalha"** e
  *"não transformar Gold/Crystal em parceiro de batalha: um quarto ator diluiria
  a escolha"*. Resolvido sem quebrar nenhum dos dois: ele **não** ganha batalha
  de treinador e **não** ganha um quarto alvo — ele entra **na mesma** UB que o
  jogador. A escolha continua sendo de três. O design §6.4 foi reescrito.
- **"Trabalhar em equipe" × a estrutura escolha + boss é contrato do arco.** A
  estrutura ficou intacta; o que mudou foi a **justificativa**: a sinergia obriga
  simultaneidade, a simultaneidade obriga quatro pessoas, e o menu passou a ser o
  reparto de um plano em vez de uma divisão de conveniência.
- **A derrota × o §7 (reunião) já implementado, que abria com "Four in four. The
  file is closed."** Uma caixa do `Text_ReunionOpen` foi ajustada para
  reconhecer que o arquivo fechou com algo pior do que o motivo de tê-lo aberto.
  O resto da reunião continua coerente e **não** foi reescrito — quem for evoluir
  o PRÉ-NECROZMA deve reler §5.1 antes.
- **A reação da Lusamine ao Cosmog × o design §6.4 diz que a missão "não checa a
  família de Cosmog em momento algum".** As duas coisas convivem porque a
  checagem é **opcional e sem estado**: não bloqueia nada, não grava nada, e sem
  o Pokémon a cena é idêntica. A única verificação de equipe do arco continua
  sendo a do §7. Registrado no design.
- **A mãe dando lição em quem é especialista × "experiência não é previsão"
  (design §3.3).** Não há conflito: ela não prevê nada e não sabe nada de Ultra
  Beasts. Ela reconhece **um comportamento humano** que já teve, e é o único
  momento do arco em que alguém de fora da investigação tem razão contra um
  especialista — o que o design §6.4 já autorizava.

### 13.3 Conferido

- `make -j$(nproc)` limpo. ROM 92,73%, EWRAM 94,28%, IWRAM 73,77%.
- `events.inc` gerado: **27 templates**, os 25 antigos **na mesma ordem**
  (locais 9, 10 e 11 do trio antigo intactos), Necrozma 26 e Ultra Necrozma 27
  no fim.
- Planta relida com `dump_mapa.py` **depois** de inserir os dois objetos e toda
  a coreografia: os 26 tiles novos são andáveis, nenhum par de atores disputa
  tile no mesmo passo, e o bolso do Looker continua fechando — só (20,12)
  alcança.
- (20,13) continua vazio a cena inteira, inclusive em passagem.
- `medir_linha.py` nos três `.pory` tocados: **nenhuma linha passa de 208 px**.
- `checar_falantes.py`: 13 falantes, tudo em ordem; nenhum falante novo foi
  preciso. As falas do Gold/Crystal que vêm **depois** de uma caixa com nome
  abrem com `{SPEAKER NAME_NONE}`, para não herdarem a plaquinha de outra
  pessoa.
- Nenhum travessão `—` (U+2014) em texto de jogo.
- `grep -rn "SKELETON" data/maps/NewBarkTown`: **zero**.
- `grep -rn "LOCALID_NEWBARK_UB_MARILL"`: **zero** em todo o repositório.
- Orçamento recontado: pico **13/16**.

### 13.4 Runtime

**Pendente.** Checklist em §10 (reescrito para a cena nova); os riscos novos
estão em §9, e os dois maiores são os dois templates no mesmo tile e as
quatorze coreografias novas que nunca rodaram.

## 14. Revisão 5 — o escurecimento dos flashes (23/09/2026)

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
o incidente encerrado). O par `FADE_TO_BLACK`/`FADE_FROM_BLACK` que reposiciona
o Elm e traz a Lusamine fica **dentro** da cena, sem recarga de mapa, e também
virou `fadescreenswapbuffers`.

O padrão já era o recomendado em `.claude/skills/visibilidade-e-gatilhos`
(§ do `addobject` sob fade) e é o que o macro `bosslegendaryencounter` usa em
`asm/macros/event.inc`. A receita de flash da skill
`evoluir-historia-de-evento` §6 estava errada e foi corrigida junto.

**Conferido:** `make -j$(nproc)` limpo. **Runtime pendente** — o teste é entrar
na cena **à noite** e conferir que a quarta ruptura está tão clara quanto a
primeira.
