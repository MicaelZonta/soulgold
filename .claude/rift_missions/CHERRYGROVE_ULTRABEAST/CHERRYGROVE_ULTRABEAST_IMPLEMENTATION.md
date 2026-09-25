# Cherrygrove — Necrozma, Blacephalon + Stakataka (Rift Mission 3) — implementação

**Status:** **história evoluída** — revisão 3, 22/09/2026. Build limpo
(`make -j$(nproc)`), **runtime pendente**. A revisão 3 transformou o esqueleto
em história a pedido do autor ("o esqueleto está pronto, agora vamos montar uma
história épica") — tabela *pedido → como ficou* em **§13**. O feedback da
implementação do esqueleto está em §12 e vale como histórico: nada do que ele
mediu mudou, mas §4, §5 e §7 foram reescritos por cima.
**Modo:** história (skill `evoluir-historia-de-evento`). Estado, visibilidade,
gatilhos, batalha e retry **não mudaram** desde o esqueleto.
**Roteiro da cena (falas e movimentos):** [`CHERRYGROVE_ULTRABEAST_SCRIPT.md`](CHERRYGROVE_ULTRABEAST_SCRIPT.md)
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §3.1, §5, §6, §6.3 (V21).
**Missões anteriores:**
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](../BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (M1) e
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](../MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (M2).

Escopo: do gancho final de Mahogany (o jogador volta a Olivine) até o fim do
incidente de Cherrygrove, terminando com um gancho **sem destino** que manda o
jogador de volta a Olivine — é o briefing da Missão 4 que revela New Bark.

**Decisões desta missão:**
- Elenco: **Looker, Anabel e Kukui**, mais o **Necrozma** (regra comum do arco)
  e o **Incineroar do Kukui**, que entra em cena no meio da luta e sai antes do
  fim. Kukui continua **sem parceiro fora da Poké Ball** na chegada: a regra
  visual do design §3.2 nomeia só Lillie e Gladion, e é justamente por ninguém
  ter visto uma Poké Ball nele em quatro dias que a surpresa funciona.
- Local: `CherrygroveCity`, **o canto noroeste da praia** — a faixa de areia
  (26-29, 7) onde a rua principal encontra o mar.
- A ruptura abre **sobre o mar**, a oeste: Necrozma sobe da água parada em
  (22,10) e é ele quem a rasga.
- Escala: 4 barras (teto), **nível 85**, **multiplicador 140**, moveset curado
  com **um golpe de controle cada** (Calm Mind / Trick Room) e item.
- Mesma estrutura padrão: escolha + boss simples, captura bloqueada, derrota =
  blackout e retry.
- **Três coisas que esta missão estreia na campanha** e que o design registrou
  como regra ou como continuidade: a sinergia das UBs com **consequência
  visual** (o teleporte sob o flash), a **revelação da Anabel como Faller**
  (antecipada de New Bark para cá) e o **Kukui fundador da Liga de Alola**,
  subestimado de propósito pelos dois policiais até a hora em que ele age.

---

## 0. Resumo do fluxo

```text
Mahogany resolvido                       VAR_RIFT_MISSIONS_STATE = 6
  └─ entrar em OlivineCity_House1 ─────▶ cena: briefing M3 → 7
                                           + setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
                                           (foi o KUKUI quem ligou; Looker e Anabel
                                            leem a ficha de duas páginas dele e o
                                            tratam como civil — erro de propósito)
       └─ Cherrygrove: cidade vazia, portas trancadas (só o Centro aberto)
            └─ falar com Looker ▶ teoria do Kukui (errada num detalhe) ▶ SIM
                 └─ cena 100% scriptada:
                      Anabel sente antes do instrumento ▶ Necrozma sobe do mar
                      ▶ ele rasga a fenda ▶ Blacephalon + Stakataka
                      ▶ SINERGIA: flash da Blacephalon, o Stakataka já está mais perto
                      ▶ de novo: colado no jogador
                      ▶ SURPRESA: Kukui solta o Incineroar e afasta o Stakataka
                         (e conta que fundou a Liga de Alola)
                      ▶ o Necrozma mira o JOGADOR ▶ Anabel entra na frente
                         ▶ REVELAÇÃO: ela é uma Faller
                      └─ ESCOLHA: qual você enfrenta? Kukui fica com a outra
                           └─ boss battle simples, 4 barras, Lv85, x140, moveset + item
                                ├─ perdeu / desistiu → blackout → Centro → recomeça
                                ├─ outro             → reset silencioso → recomeça
                                └─ venceu            → fala do Kukui conforme a escolha
                                     └─ Necrozma ABSORVE as duas e some
                                        (+ reação opcional à família Cosmog)
                                     └─ cuidado com as pessoas, convite do Kukui,
                                        gancho SEM destino
                                        → clearflag + estado 8 → warp no lugar
                                     └─ Olivine House1: briefing da Missão 4
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` | `include/constants/flags.h` | `0x1043` | Primeira livre depois de `FLAG_EVENT_ULTRABEAST_MAHOGANY` (0x1042). Conferido: `grep -n "0x1043" include/constants/flags.h` não retorna nada. **Atualizar `CUSTOM_FLAGS_END`** para apontar nela (hoje aponta para `FLAG_EVENT_ULTRABEAST_MAHOGANY`). |
| `LOCALID_CHERRYGROVE_UB_*` | `include/constants/map_event_ids.h` | 20-26 | Cinco linhas no esqueleto (20-24) + **duas na revisão 3** (`_NECROZMA` 25, `_INCINEROAR` 26), à mão, **dentro da seção `// MAP_CHERRYGROVE_CITY` que já existe** (`:199-203`, com `LOCALID_GUIDE_GENT 1`, `LOCALID_CHERRYGROVE_SILVER 13`, `LOCALID_CHERRY_ZIGZAGOON 16`, `LOCALID_CHERRY_RATTATA 17`). Diferente da M2, aqui **não** se cria cabeçalho novo. |

Nenhuma var nova, nenhuma flag de batalha nova: `FLAG_NO_CATCHING` /
`B_FLAG_NO_CATCHING` já existem desde Blackthorn e são compartilhadas por todas
as Rift Missions. A engine limpa `FLAG_NO_CATCHING` sozinha ao fim de toda
batalha (`Overworld_ResetBattleFlagsAndVars`, `src/overworld.c`) — setar
imediatamente antes da batalha e nunca limpar à mão.

Comentário obrigatório acima do `#define` novo, no mesmo padrão dos dois
anteriores (`flags.h`, blocos de `FLAG_EVENT_ULTRABEAST_BLACKTHORN` e
`FLAG_EVENT_ULTRABEAST_MAHOGANY`): quem seta, quem limpa, e a frase de que ela só
existe porque o campo `flag` do `map.json` não lê var.

**Não é preciso bloquear fuga.** Em boss battle "Run" é desistência explícita
(`CanPlayerForfeitBattle`, `src/battle_main.c`): resultado `B_OUTCOME_FORFEITED`,
que conta como derrota → blackout → retry.

### 1.2 Máquina de estados `VAR_RIFT_MISSIONS_STATE` (continuação)

`VAR_RIFT_MISSIONS_STATE` = `0x4120` (`include/constants/vars.h:319`).
Valores 0-3 estão no doc de Blackthorn §1.2; 4-6 no doc de Mahogany §1.2.
**Nenhum deles muda.**

| Valor | Significado | Quem escreve | Quem lê |
|---|---|---|---|
| 6 | Mahogany resolvido; briefing da Missão 3 pendente | `Mahoganytown_EventScript_UBResolved` (já existe) | Olivine House1 (cena de chegada + briefing M3) |
| 7 | Briefing M3 feito; incidente de Cherrygrove **ativo** | `OlivineCity_House1_EventScript_BriefingTalkM3` | Olivine House1 ("vá na frente"); `CherrygroveCity_OnTransition` |
| 8 | Cherrygrove resolvido; briefing da Missão 4 pendente | `CherrygroveCity_EventScript_UBResolved` | Olivine House1 (stub da Missão 4) |
| 9+ | Reservado para a Missão 4 (New Bark) | próximo doc | — |

**Invariante:** `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` setada ⇔ `VAR_RIFT_MISSIONS_STATE == 7`.
As duas mudam **juntas, no mesmo script** (Olivine seta, Cherrygrove limpa). A
flag existe só porque o campo `flag` do `map.json` não lê var — é ela que esvazia
a cidade. A var é a autoridade da história.

As invariantes de Blackthorn (flag ⇔ estado 3) e de Mahogany (flag ⇔ estado 5)
continuam valendo e **não** são tocadas por esta missão. As três flags nunca
estão setadas ao mesmo tempo, porque a var só tem um valor.

Nenhuma outra flag/var persistente. A escolha do jogador (qual UB enfrentar) é
temporária: numa nova tentativa ele escolhe de novo.

### 1.3 Temporários por mapa

| Mapa | Temp | Uso |
|---|---|---|
| `OlivineCity_House1` | `VAR_TEMP_1` | Trava uma-vez-por-visita do gatilho de frame (**já existe**; agora serve aos estados 2, 4 **e** 6) |
| `CherrygroveCity` | `FLAG_TEMP_1` | Cache de visibilidade do elenco (Looker, Anabel, Kukui) |
| `CherrygroveCity` | `FLAG_TEMP_2` | Cache das Ultra Beasts (sempre escondidas até a cena) |
| `CherrygroveCity` | `VAR_TEMP_2` | Resultado da batalha |
| `CherrygroveCity` | `VAR_TEMP_3` | Escolha do jogador: 0 = Blacephalon, 1 = Stakataka. Sobrevive à batalha (voltar da batalha não passa por `LoadMapFromWarp`) |
| `CherrygroveCity` | `FLAG_TEMP_3` | Cache de visibilidade do Zigzagoon de Galar do Friendly Trader (§3.1.1) |
| `CherrygroveCity` | `FLAG_TEMP_4` | Cache de visibilidade do Rattata de Alola do Friendly Trader (§3.1.1) |
| `CherrygroveCity` | `FLAG_TEMP_5` | **(rev. 3)** Cache do Necrozma — flag **própria**, para o `removeobject` das UBs nunca encostar nele |
| `CherrygroveCity` | `FLAG_TEMP_6` | **(rev. 3)** Cache do Incineroar do Kukui — mesmo motivo |
| `CherrygroveCity` | `VAR_TEMP_4` | **(rev. 3)** Espécie da família Cosmog a que o Necrozma reagiu (`SPECIES_NONE` = não reagiu). Relida pela conversa final |

> ⚠ **`VAR_TEMP_1` está OCUPADO em `CherrygroveCity`.**
> `include/constants/vars.h:370` define `VAR_TEMP_TRANSFERRED_SPECIES` como
> **`VAR_TEMP_1`**, e `Cherrygrove_FriendlyTrader` o usa nos dois ramos da troca
> (`scripts.pory:683` e `:698`). Mesma armadilha da M2 (lá era o vendedor de Rage
> Candy Bar), com nome diferente. Por isso esta missão também começa em
> `VAR_TEMP_2`. `VAR_TEMP_0` está livre no mapa, mas fica sem uso de propósito:
> as três missões usam `VAR_TEMP_2/3` e vale a pena manter a uniformidade.

`FLAG_TEMP_1` a `FLAG_TEMP_6` estão livres em `CherrygroveCity` (antes desta
missão não havia **nenhuma** ocorrência de `FLAG_TEMP` no `.pory` nem no `.inc`
gerado; `FLAG_TEMP_5` a `FLAG_TEMP_10` estão marcadas como *Unused Flag* em
`include/constants/flags.h`). `VAR_TEMP_4` também está livre no mapa. `FLAG_TEMP_3/4` são
muito usadas no projeto, mas **sempre dentro de um mapa só** (Ice Path, Fuchsia
Gym, Dragon's Den, Cerulean Cave…), e temporárias não atravessam load — não há
conflito. Evitar `FLAG_TEMP_E`, que a engine reserva para suprimir o follower. Os usos de
`VAR_TEMP_2/3` e `FLAG_TEMP_2` que aparecem em `data/scripts/` são de
`contest_hall`, `battle_arcade_*` e `interview.inc` — outros mapas; temporários
zeram a cada load (`ClearTempFieldEventData`), então não há conflito.

Reconfirmar antes de implementar:

```bash
grep -rn "FLAG_TEMP_[1-6]\b\|VAR_TEMP_[01234]\b" data/maps/CherrygroveCity data/maps/OlivineCity_House1
```

---

## 2. Etapa A — Olivine: briefing da Missão 3

`OlivineCity_House1` tem `.pory` → editar só `data/maps/OlivineCity_House1/scripts.pory`.
O `map.json` **não muda**: Looker e Anabel já existem com `flag: 0` e continuam
morando lá desde o New Game.

A M2 já transformou o gatilho de chegada e o `BriefingTalk` em despachantes. A M3
só **acrescenta um estado a cada um** — nenhuma coreografia nova, nenhum objeto novo.

### 2.1 O gatilho de chegada passa a atender três estados

Hoje (depois da M2) `OlivineCity_House1_EventScript_BriefingTrigger` tem duas
linhas de despacho (`scripts.pory:42-43`). Acrescentar a terceira, mantendo a
trava `VAR_TEMP_1` **como primeira instrução** e a checagem de porta:

```asm
OlivineCity_House1_EventScript_BriefingTrigger::
	setvar VAR_TEMP_1, 1                        @ primeira instrução: para de disparar
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 4, OlivineCity_House1_EventScript_End
	goto_if_ne VAR_0x8005, 8, OlivineCity_House1_EventScript_End
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefing   @ NOVO
	end
```

`OlivineCity_House1_EventScript_StageBriefing` (o `lockall` / `hidefollower` /
aproximação / `call ...BriefingTalk` / volta / `releaseall` / `end`) fica
**intocado**. As posições (4,5)/(7,5)/(4,8) e os quatro `Movement_*` são
reaproveitados inteiros pela terceira vez.

### 2.2 `BriefingTalk` ganha o ramo da M3

O rótulo `OlivineCity_House1_EventScript_BriefingTalk` continua sendo o **único**
ponto que muda flag+var, e continua sendo chamado tanto pela cena quanto pelos
scripts de objeto:

```asm
@ Invariantes:
@   FLAG_EVENT_ULTRABEAST_BLACKTHORN  setada <=> VAR_RIFT_MISSIONS_STATE == 3
@   FLAG_EVENT_ULTRABEAST_MAHOGANY    setada <=> VAR_RIFT_MISSIONS_STATE == 5
@   FLAG_EVENT_ULTRABEAST_CHERRYGROVE setada <=> VAR_RIFT_MISSIONS_STATE == 7
@ Flag e var mudam sempre no mesmo bloco.
OlivineCity_House1_EventScript_BriefingTalk::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_BriefingTalkM3   @ NOVO
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

OlivineCity_House1_EventScript_BriefingTalkM3::                                            @ NOVO
	msgbox OlivineCity_House1_Text_BriefingM3, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
	setvar VAR_RIFT_MISSIONS_STATE, 7
	return
```

A ordem dos dois `goto_if_eq` **importa pouco** (os valores são exclusivos), mas
manter o estado mais alto em cima deixa o bloco lido de trás para frente, na
ordem em que as missões foram acrescentadas.

`goto` dentro de um script alcançado por `call` é seguro: `call` empilha o
endereço de retorno e `return` o desempilha, independentemente de quantos `goto`
houve no meio. Já provado nas duas missões anteriores.

### 2.3 Diálogo por estado — Looker e Anabel

`OlivineCity_House1_EventScript_Looker` hoje termina em
`goto_if_ge VAR_RIFT_MISSIONS_STATE, 6, ..._LookerMission3` (`scripts.pory:134`).
**Essa linha tem que sair** — com ela, os estados 7 e 8 nunca são alcançados.

| Estado | O que acontece |
|---|---|
| 0-1 | `Text_LookerHoliday` (inalterado) |
| 2 | `call ..._BriefingTalk` → M1 (inalterado) |
| 3 | `Text_LookerGoAhead` (inalterado) |
| 4 | `call ..._BriefingTalk` → M2 (inalterado) |
| 5 | `Text_LookerGoAheadM2` (inalterado) |
| **6** | `call ..._BriefingTalk` → **M3**. O rótulo `..._LookerBrief` já existe e já é o destino dos estados 2 e 4: basta apontar o 6 para ele. |
| **7** | **Novo** `Text_LookerGoAheadM3` |
| **≥ 8** | `..._LookerMission3` **é renomeado** para `..._LookerMission4`, e `..._Text_LookerMission3Stub` para `..._Text_LookerMission4Stub`, com texto novo (New Bark / Lusamine). |

```asm
@ NÃO acrescentar nenhum "goto_if_ge VAR_RIFT_MISSIONS_STATE, 6" aqui - ele
@ engoliria os estados 7 e 8. O mesmo aviso que a M2 deixou para o 4.
OlivineCity_House1_EventScript_Looker::
	lock
	faceplayer
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_LookerBrief
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_LookerGoAhead
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_LookerBrief
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_LookerGoAheadM2
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerBrief      @ NOVO
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_LookerGoAheadM3  @ NOVO
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_LookerMission4   @ era 6 -> Mission3
	msgbox OlivineCity_House1_Text_LookerHoliday, MSGBOX_DEFAULT
	goto OlivineCity_House1_EventScript_ReleaseEnd
```

`OlivineCity_House1_EventScript_Anabel` recebe exatamente a mesma cirurgia
(`scripts.pory:161-165`), com `..._AnabelBrief`, `..._AnabelGoAheadM3` e
`..._AnabelMission4`.

Todos os ramos continuam terminando em `OlivineCity_House1_EventScript_ReleaseEnd`.

**Checagem pós-edição obrigatória:** `grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE" data/maps/OlivineCity_House1/scripts.pory`
tem que devolver **exatamente duas** linhas de código, e nenhuma delas pode usar
um valor que a missão seguinte ainda vá ocupar. Na época do esqueleto eram duas
com `, 8,`; depois que a M4 e a reunião entraram, são duas com `, 12,` (o altar).
A armadilha é sempre a mesma: um `goto_if_ge` com valor baixo demais engole
silenciosamente todos os estados acima dele.

**Textos da revisão 3 (finais)** — `Text_BriefingM3`, `Text_LookerGoAheadM3` e
`Text_AnabelGoAheadM3` estão em [`CHERRYGROVE_ULTRABEAST_SCRIPT.md`](CHERRYGROVE_ULTRABEAST_SCRIPT.md), "Ato 1".

O briefing deixou de ser um resumo do que o jogador vai ver e virou a **cena de
erro de julgamento** que a praia paga: quem avisou foi o **Kukui**, por telefone,
quatro dias antes; a ficha dele tem duas páginas, sem registro de força nem
autorização de combate; os dois concluem que há um civil sentado embaixo de um
céu aberto. **Nada de Ultra Beast é nomeado ali, e a criatura de luz também não**
— essas são da praia.

> ⚠ **A ficha de duas páginas é load-bearing.** Ela é montada aqui para ser
> desmontada em `CherrygroveCity_Text_UBKukuiRevealed`, onde o Kukui explica que
> ninguém em Alola escreve relatório sobre o cara que fundou a Liga. Mexer num
> dos dois lados sem o outro mata a piada e a cena.
>
> **Os dois stubs da Missão 4 não existem mais:** a M4 foi implementada e o
> estado ≥ 8 cai no despachante dela (`Text_BriefingM4`), que é quem revela New
> Bark, as três assinaturas e a Lusamine. O gancho desta missão **não pode**
> citar nenhum dos três (§5, "gancho sem destino").

---

## 3. Etapa B — Cherrygrove: cidade vazia

`CherrygroveCity` **tem** `.pory` → editar `data/maps/CherrygroveCity/scripts.pory`
e `data/maps/CherrygroveCity/map.json`. **Não** editar `scripts.inc`: ele é
gerado a partir do `.pory` e a edição some no próximo build.

> ⚠ Existe um `data/maps/CherrygroveCity/map.json.bak` no checkout. O build
> **não** o lê. Não editar, e não se deixar confundir por ele num `grep` — ele
> está desatualizado (tem menos `coord_events` que o `map.json` vigente).

### 3.1 Esconder a cidade

`CherrygroveCity/map.json`: trocar `"flag": "0"` por
`"flag": "FLAG_EVENT_ULTRABEAST_CHERRYGROVE"` nos **catorze** objetos abaixo.

| Local id | Objeto | (x,y) |
|---|---|---|
| 2 | Fisher | (18,19) |
| 3 | Boy | (45,15) |
| 4 | Lass (FR) | (39,11) |
| 5 | OW Corsola | (25,9) |
| 7 | OW Corsola | (25,8) |
| 8 | OW Staryu | (27,26) |
| 9 | OW Corsola | (4,11) |
| 10 | OW Corsola | (6,12) |
| 11 | OW Corsola | (4,24) |
| 12 | OW Corsola | (2,25) |
| 14 | OW Aipom | (54,7) |
| 18 | Little girl | (33,23) |
| 15 | Friendly Trader | (43,22) |
| 19 | OW Zigzagoon | (35,20) |

Os locais **5 e 7** são os dois Corsola em (25,9) e (25,8): eles ficam a **um
tile** do elenco da cena. Esconder os dois é o que mais importa visualmente.

**Os seis objetos que NÃO são tocados** — todos já têm flag própria, e o campo
`flag` do template só comporta uma:

| Local id | Objeto | Flag própria | Por que fica de fora |
|---|---|---|---|
| 1 | Guide Gent (57,8) | `FLAG_HIDE_GUIDE_GENT_CHERRYGROVE` | Só aparece com `VAR_CHERRYGROVE_CITY_STATE == 0`; no pós-E4 já está escondido (e o próprio tour dá `removeobject` nele, `scripts.pory:126`). |
| 6 | Staryu (25,16) | `FLAG_NIGHT_POKEMON` | Encontro noturno, controlado por `SetTimeBasedEncounters` no `ON_TRANSITION`. Fica 9 tiles ao sul da cena, fora da câmera. |
| 13 | Silver (65,10) | `FLAG_HIDE_SILVER_CHERRYGROVE` | Setada no fim da cena do rival (`scripts.pory:279-280`); no pós-E4 já está escondido. |
| 16 | Zigzagoon Galar (42,22) | `FLAG_PICKED_ZIGZAGOON` | **Escondido por outro caminho** — §3.1.1. |
| 17 | Rattata Alola (44,22) | `FLAG_PICKED_RATTATA` | **Escondido por outro caminho** — §3.1.1. |

### 3.1.1 Os dois presentes do Friendly Trader (locais 16 e 17)

O treinador (local 15) recebe a flag do evento como qualquer morador. Os **dois
Pokémon dele não podem**: o campo `flag` do template já está ocupado por
`FLAG_PICKED_ZIGZAGOON` e `FLAG_PICKED_RATTATA`, e o campo só comporta uma flag.
Deixar os dois na rua enquanto o dono some é pior do que deixar os três — então
eles somem por um caminho diferente.

**Padrão usado:** o mesmo de `FLAG_HIDE_CIANWOOD_GLADION` (`flags.h`) — o campo
`flag` do template passa a ser uma flag **burra**, recalculada a cada load a
partir da verdade persistente, que não muda de lugar.

| Local | `flag` do template, antes | `flag` do template, depois | Verdade persistente |
|---|---|---|---|
| 16 | `FLAG_PICKED_ZIGZAGOON` | **`FLAG_TEMP_3`** | `FLAG_PICKED_ZIGZAGOON` (inalterada) |
| 17 | `FLAG_PICKED_RATTATA` | **`FLAG_TEMP_4`** | `FLAG_PICKED_RATTATA` (inalterada) |

Regra recalculada no `ON_TRANSITION` (§3.3):

```text
presente visível  ⇔  (ainda não foi pego)  E  (não há incidente ativo)
```

> ⛔ **ARMADILHA — leia antes de tocar no `map.json`.**
> Hoje **nada no projeto faz `setflag FLAG_PICKED_ZIGZAGOON` nem
> `setflag FLAG_PICKED_RATTATA`.** Quem as seta é o efeito colateral do
> `removeobject` dentro de `Cherrygrove_FriendlyTrader`
> (`scripts.pory:687` e `:702`): `RemoveObjectEventByLocalIdAndMap`
> (`src/event_object_movement.c:1588-1596`) faz
> `FlagSet(GetObjectEventFlagIdByObjectEventId(objectEventId))` — ou seja, seta a
> flag **do template**. Conferido por `grep`: as duas constantes só aparecem no
> `if` do próprio trader, no `map.json` e em `flags.h`.
>
> **Consequência:** no instante em que o template passa a apontar para
> `FLAG_TEMP_3/4`, o `removeobject` para de tornar o presente permanente. Se essa
> troca for feita sem o `setflag` explícito, **o presente vira repetível para
> sempre** — o jogador farma Zigzagoon de Galar e Rattata de Alola sem limite, e
> o build continua limpo.

Edição obrigatória, na parte **poryscript** de `data/maps/CherrygroveCity/scripts.pory`
(script `Cherrygrove_FriendlyTrader`), uma linha em cada `case`:

```diff
             case 0:
                 setvar(VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZIGZAGOON_GALAR)
                 bufferspeciesname(STR_VAR_1, SPECIES_ZIGZAGOON_GALAR)
                 givemon(SPECIES_ZIGZAGOON_GALAR, 5)
                 showgivemonpic(10, 3)
+                setflag(FLAG_PICKED_ZIGZAGOON)
                 removeobject(LOCALID_CHERRY_ZIGZAGOON)
```

```diff
             case 1:
                 setvar(VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_RATTATA_ALOLA)
                 bufferspeciesname(STR_VAR_1, SPECIES_RATTATA_ALOLA)
                 givemon(SPECIES_RATTATA_ALOLA, 5)
                 showgivemonpic(10, 3)
+                setflag(FLAG_PICKED_RATTATA)
                 removeobject(LOCALID_CHERRY_RATTATA)
```

O `removeobject` **continua** onde está: ele agora seta `FLAG_TEMP_3`/`FLAG_TEMP_4`,
que é exatamente o cache certo para o resto daquela visita ao mapa. O
`setflag` novo é quem torna a escolha permanente. O `if` do trader
(`flag(FLAG_PICKED_ZIGZAGOON) || flag(FLAG_PICKED_RATTATA)`) não muda.

> **Nota da implementação (20/09/2026).** O `setflag` explícito é, na prática,
> **mais robusto que o mecanismo antigo**: a permanência deixou de depender de o
> objeto estar spawnado no instante do `removeobject`. Além disso, o trader
> ganhou uma checagem de espaço de party/PC **antes da fala da oferta** — ver
> §12.3 item 5. Ela é anterior e independente desta missão em motivação, mas
> entrou junto.

**Comportamento preservado ao pé da letra:** hoje, pegar um presente esconde só
aquele objeto e deixa o outro de pé na rua. A regra acima reproduz isso — cada
presente é escondido apenas pela própria flag `PICKED`. Esta missão **não**
conserta esse detalhe; se for para mudar, é decisão de outro trabalho.

**O Centro continua:** a Joy está em `CherrygroveCity_PokemonCenter` (outro
mapa), intocado. Porta do Centro (47,7) e do Mart (41,7) livres durante todo o
evento; House1 (34,13), House2 (42,14), House3 (50,17), a porta do Darkrai Inn
(34,34) e o warp (29,21) continuam acessíveis — só o exterior esvazia.

**Gatilhos herdados, conferidos como inofensivos no pós-E4:**

- Os **seis** `coord_events` do mapa cobrem `VAR_CHERRYGROVE_CITY_STATE` **0**
  (três tiles do Guide Gent, em (57,9)/(57,10)/(57,11)) e **3** (três tiles do
  Silver, em (56,10)/(56,9)/(56,11)). A var termina em **4**, setada por
  `CherryGroveCity_Silver_AfterBattle` (`scripts.pory`, junto com
  `setflag FLAG_HIDE_SILVER_CHERRYGROVE`), etapa obrigatória no começo do jogo.
  No pós-E4 nenhum dos seis dispara — e portanto nenhum `applymovement`/
  `turnobject` roda sobre objeto escondido.
- `CherrygroveCity_MapScripts` **não tem** `ON_FRAME_TABLE`. Nada dispara por
  frame neste mapa.
- `CherrygroveCity_OnLoad` (`setrespawn HEAL_LOCATION_CHERRYGROVE_CITY`)
  continua como está. É ele que garante que o blackout devolve o jogador ao
  Centro de Cherrygrove.
- **Nenhum `removeobject` do mapa toca os 14 objetos acima.** Os quatro que
  existem são `LOCALID_GUIDE_GENT`, `LOCALID_CHERRYGROVE_SILVER`,
  `LOCALID_CHERRY_ZIGZAGOON` e `LOCALID_CHERRY_RATTATA`. Os dois primeiros
  continuam com flag própria e não são tocados por esta missão; os dois últimos
  passam a ter `FLAG_TEMP_3`/`FLAG_TEMP_4` no template, e é justamente por isso
  que o `setflag` explícito de §3.1.1 é obrigatório.

> ⚠ **Dependência criada:** depois desta mudança, um `removeobject` em qualquer
> dos catorze objetos acima **seta `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` e esvazia
> a cidade**. Antes eram `flag: 0`, onde `removeobject` era inofensivo.

### 3.1.2 Portas trancadas (rev. 3 — regra comum do arco, pendente desde o esqueleto)

Regra comum do design §6: durante o incidente **toda porta de prédio recusa o
jogador, menos a do Pokémon Center**. Uma linha na tabela
`sLockedTownDoors` (`src/field_control_avatar.c`) e um `extern` em
`include/event_scripts.h`:

```c
{ FLAG_EVENT_ULTRABEAST_CHERRYGROVE, MAP_CHERRYGROVE_CITY, MAP_CHERRYGROVE_CITY_POKEMON_CENTER, CherrygroveCity_EventScript_DoorLocked },
```

- Fecham: Mart (41,7), House1 (34,13), House2 (42,14), House3 (50,17) e o
  Darkrai Inn (34,34). Abre: o Centro (47,7) — **obrigatório**, é o retorno do
  blackout e a cura do retry.
- O warp (29,21) não é porta animada (`MetatileBehavior_IsWarpDoor`), então a
  trava não o vê e ele continua funcionando, como as entradas de caverna da M1
  e o gate da Route 43 da M2.
- Cherrygrove **não tem Ginásio**, então o bilhete não é de Líder: é da Polícia
  Internacional, que é quem evacuou ("The town is at the Violet Gym").

### 3.2 Elenco, Ultra Beasts, Necrozma e Incineroar — no fim de `object_events` (locais 20-26)

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 20 | `LOCALID_CHERRYGROVE_UB_KUKUI` | `OBJ_EVENT_GFX_KUKUI` | (26,7) | `FACE_DOWN` | `..._EventScript_UBKukui` | `FLAG_TEMP_1` |
| 21 | `LOCALID_CHERRYGROVE_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (27,7) | `FACE_DOWN` | `..._EventScript_UBLooker` | `FLAG_TEMP_1` |
| 22 | `LOCALID_CHERRYGROVE_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (28,7) | `FACE_DOWN` | `..._EventScript_UBAnabel` | `FLAG_TEMP_1` |
| 23 | `LOCALID_CHERRYGROVE_UB_BLACEPHALON` | `OBJ_EVENT_GFX_SPECIES(BLACEPHALON)` | (24,9) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 24 | `LOCALID_CHERRYGROVE_UB_STAKATAKA` | `OBJ_EVENT_GFX_SPECIES(STAKATAKA)` | (24,10) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| **25** | `LOCALID_CHERRYGROVE_UB_NECROZMA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA)` | (22,10) | `FACE_RIGHT` | `NULL` | **`FLAG_TEMP_5`** |
| **26** | `LOCALID_CHERRYGROVE_UB_INCINEROAR` | `OBJ_EVENT_GFX_SPECIES(INCINEROAR)` | (26,9) | `FACE_LEFT` | `NULL` | **`FLAG_TEMP_6`** |

- Todos com `"elevation": 0`, `movement_range_x/y: 0`, `TRAINER_TYPE_NONE`,
  `trainer_sight_or_berry_tree_id: "0"` e `"local_id"` explícito.
- **`FACE_DOWN` no elenco, não `FACE_UP`:** está encostado na parede norte e o
  jogador chega pela rua, vindo do sul/leste.
- **Necrozma e Incineroar têm flag própria** (`FLAG_TEMP_5`/`FLAG_TEMP_6`), e
  não `FLAG_TEMP_2`. Não é preciosismo: o `removeobject` das duas UBs na
  absorção **seta a flag do template**; se os cinco dividissem uma flag, o
  `removeobject` mexeria no elenco de terceiros. Mesma decisão da M1.
- **O Necrozma fica sobre o mar** em (22,10), ocean water, cinco colunas a
  oeste do jogador. Com o jogador em (27,10) a câmera cobre x ≈ 20..34, e
  depois que ele é puxado para (28,10) cobre x ≈ 21..35 — o Necrozma continua
  dentro do quadro nas duas.
- **O Incineroar nasce em (26,9)**, areia, entre o Kukui (26,8) e o Stakataka
  (26,10) no instante em que ele é solto. É a única razão de o Kukui parar em
  (26,8) e não descer até a linha do jogador.
- Conferido: `INCINEROAR` e `NECROZMA` têm bloco `OVERWORLD(` (`SIZE_32x32`,
  `SHADOW_SIZE_M`), como `BLACEPHALON` e `STAKATAKA`.
- **Sempre no fim de `object_events`:** inserir no meio renumera
  `LOCALID_CHERRYGROVE_SILVER` (13), `LOCALID_CHERRY_ZIGZAGOON` (16) e
  `LOCALID_CHERRY_RATTATA` (17), que são lidos por script.
- **Orçamento:** 26 templates < 64. Spawn simultâneo no pico da cena = jogador
  + follower (escondido) + 7 = 9 < `OBJECT_EVENTS_COUNT` (16). Durante o
  incidente o mapa spawna **menos** objetos que fora dele.

Looker e Anabel ficam em Olivine **e** aqui durante o estado 7 — aceito pelo
autor desde a M1, o evento inteiro é cutscene (design §5).

### 3.3 Visibilidade — `ON_TRANSITION` (já existe; ganha uma linha)

`CherrygroveCity` **já tem** `ON_TRANSITION`. Não criar outro: acrescentar o
`call` dentro do que existe, sem reordenar nada.

```asm
CherrygroveCity_OnTransition::
	callnative SetTimeBasedEncounters
	call CherrygroveCity_EventScript_ApplyUBVisibility   @ NOVO
	end

CherrygroveCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2                 @ Ultra Beasts
	setflag FLAG_TEMP_5                 @ Necrozma      (rev. 3)
	setflag FLAG_TEMP_6                 @ Incineroar    (rev. 3)
	call CherrygroveCity_EventScript_ApplyGiftMonVisibility
	goto_if_unset FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	return

CherrygroveCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	return
```

**As três `setflag` são incondicionais e rodam em todo load.** É isso que faz o
retry depois de um blackout começar limpo de graça: as UBs, o Necrozma e o
Incineroar voltam escondidos sem que nenhum script precise lembrar de escondê-los.

O bloco dos presentes do trader (`ApplyGiftMonVisibility`) é o mesmo do
esqueleto, com a mesma tabela-verdade; não foi tocado pela revisão 3.

`SetTimeBasedEncounters` mexe em `FLAG_NIGHT_POKEMON` (objeto 6) e não toca nos
temporários da missão: a ordem das duas linhas é indiferente. Roda também ao
entrar pela borda — Route 29 e Route 30 —, não só por warp.

### 3.4 Planta da cena (colisão real + comportamento de metatile)

```bash
python3 .claude/skills/encenar-cutscene/dump_mapa.py CherrygroveCity 21 32 5 12
```

O `dump_mapa.py` só lê o bit 11 (colisão). **Neste mapa isso não basta:** boa
parte da orla tem colisão 0 e mesmo assim é água. A distinção areia / água rasa
/ oceano veio dos `metatile_attributes.bin` de `johto_general` e
`cherrygrove_city` (§12.7 explica como ler os dois neste repo).

```text
       x= 21 22 23 24 25 26 27 28 29 30 31 32
  y= 5       #  #  #  #  #  #  #  #  #  #  #  #
  y= 6       #  #  #  #  #  #  #  #  #  #  #  #   parede norte
  y= 7       ~  w  w  w  w  U  K  A  s  .  .  .   U Kukui (26,7)  K Looker (27,7)
  y= 8       ~  ~  ~  ~  w  u  l  s  s  .  .  .   A Anabel (28,7)
  y= 9       ~  ~  n  B  w  i  L  a  .  .  .  .   t (27,8) = ÚNICO tile do Looker
  y=10       ~  N  n  S  w  X  p  P  k  .  .  .   B Blacephalon (24,9)
  y=11       ~  ~  ~  ~  w  s  s  .  .  .  .  #   S Stakataka   (24,10)
  y=12       ~  ~  ~  ~  w  s  s  .  .  #  #  #   N Necrozma    (22,10)

  #  colisão      s  areia (MB_SAND)          .  chão comum (MB_NORMAL)
  ~  oceano (MB_OCEAN_WATER): só de Surf, o jogador a pé NÃO entra
  w  água rasa (MB_SHALLOW_WATER): colisão 0, o jogador a pé ANDA nela
```

Minúsculas = onde cada ator para, em duas levas:

| Marca | Quem | Quando |
|---|---|---|
| `u` (26,8) | Kukui | fim da aproximação, e fica aí até a conversa final |
| `l` (27,8) | Looker | fim da aproximação |
| `a` (28,9) | Anabel | fim da aproximação |
| `p` (27,10) | jogador | fim da aproximação |
| `X` (26,10) | Stakataka | fim do avanço silencioso — **um tile a oeste do jogador** |
| `i` (26,9) | Incineroar | ao ser solto, entre o Kukui e o Stakataka |
| `L` (27,9) | Looker | quando corre até a Anabel caída |
| `p` (27,10) | **Anabel** | quando entra na frente do jogador (ele saiu) |
| `P` (28,10) | jogador | depois de ser puxado; fica aí até o fim |
| `k` (29,10) | Kukui | conversa final, pela volta (linha 8 → coluna 29) |
| `n` (23,9) e (23,10) | Blacephalon e Stakataka | arrastados para o Necrozma na absorção |

> ⚠ **A coluna x=25 (e a faixa (22..25, 7)) é água RASA, não barreira.** O
> jogador anda nela a pé. Não confundir com o oceano de x≤24, esse sim
> intransponível sem Surf. As duas UBs e o Necrozma ficam em **oceano** de
> propósito: ninguém encosta neles a pé.

O Looker fica no "bolso" (27,7): **(27,6) é parede**, (26,7) é o Kukui e (28,7)
é a Anabel. **Só dá para falar com ele de (27,8), olhando para cima** — é o que
torna o início da cena determinístico sem `getplayerxy`.

**Garantia da caixa de texto:** em nenhum momento com diálogo aberto existe ator
ao sul do jogador. Na primeira leva ele é o mais ao sul da linha; depois de ser
puxado para (28,10), os três que restam estão a oeste (Anabel), ao norte
(Looker) e a leste (Kukui), e (28,11) fica vazio de propósito.

Caminho do Centro até a cena, para o retry: a saída fica em **(47,8)** e a linha
**y=8 é livre de x=27 a x=49** — 20 passos retos. Ver §9.

### 3.5 Conversas antes da cena

Todas com reação **opcional** à família Cosmog (`CheckMysteryEggPokemon`), sem
nenhuma flag nem var: sem o Pokémon na equipe a conversa é idêntica.

| Objeto | Script | Nota técnica |
|---|---|---|
| Anabel | `..._EventScript_UBAnabel` | `faceplayer` + ramo Cosmog. |
| Kukui | `..._EventScript_UBKukui` | `faceplayer` + ramo Cosmog. Ele **reconhece a espécie na hora** — morou com um — mas nunca chama o Pokémon do jogador pelo nome do que ele conheceu (design §3.3). Também alcançável de (25,7), que é água rasa. |

Os dois terminam com `turnobject … DIR_SOUTH` (volta ao `FACE_DOWN` do
`map.json`). São no-op hoje, e ficam como proteção a qualquer evolução que mude
as posições.

Os textos estão em [`CHERRYGROVE_ULTRABEAST_SCRIPT.md`](CHERRYGROVE_ULTRABEAST_SCRIPT.md), "Ato 2".

---

## 4. Etapa C — A cena (100% scriptada a partir do SIM)

### 4.1 Pré-checagens (`CherrygroveCity_EventScript_UBLooker`)

```asm
CherrygroveCity_EventScript_UBLooker::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox CherrygroveCity_Text_UBKukuiTheory, MSGBOX_DEFAULT
	msgbox CherrygroveCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_UBNotReady
	goto CherrygroveCity_EventScript_UBScene
```

- Nenhum estado muda antes do SIM. O SIM é o último ponto de saída.
- Batalha simples e **sem presente**: não é preciso checar party nem PC (ao
  contrário da M1, onde o Type: Null obrigava a checagem antes do SIM).
- **A teoria do Kukui vem antes do SIM e está errada de propósito.** Ele conclui
  que a pesada **anda** por trás das luzes; a cena o corrige na cara dele, e é
  assim que a sinergia é **mostrada antes de explicada** (design §6). Errar em
  voz alta é o que lhe dá direito à fala seguinte. Texto: [`CHERRYGROVE_ULTRABEAST_SCRIPT.md`](CHERRYGROVE_ULTRABEAST_SCRIPT.md), "Ato 3".

### 4.2 A cena (`CherrygroveCity_EventScript_UBScene`)

**A cena inteira — beats, movimentos e falas — está em [`CHERRYGROVE_ULTRABEAST_SCRIPT.md`](CHERRYGROVE_ULTRABEAST_SCRIPT.md), "Ato 4".** Aqui só o
que a implementação precisa garantir:

- `lockall` + `hidefollower` na primeira linha.
- **A ordem dos três blocos de aproximação é load-bearing:** Kukui → jogador →
  Looker/Anabel. O Looker só desce depois que o jogador libera (27,8). Cada tile
  andado foi conferido no `metatile_attributes`: **ninguém pisa na água**.
- O Kukui para em (26,8) e **não** em (26,10): (26,9) tem de ficar livre para o
  Incineroar e (26,10) para o avanço silencioso da Stakataka.
- **A sinergia é `setobjectxy` debaixo do flash, não um atalho:** a Stakataka
  nunca anda — o teletransporte **é** o truque. (24,10) → (25,10) → (26,10),
  tudo na linha 10, parando um tile a oeste do jogador.
- A troca da Anabel na frente do jogador é **sequencial** e nunca disputa tile:
  ela vai a (27,9), o jogador é puxado para (28,10) **ainda olhando oeste**, e
  ela cai no (27,10) vago. Ninguém termina ao sul do jogador, então a caixa de
  texto não cobre ninguém pelo resto da missão.
- Necrozma entra sob `FLAG_TEMP_5`, as UBs sob `FLAG_TEMP_2`, o Incineroar sob
  `FLAG_TEMP_6` — três caches separados de propósito.
- Flash = `fadescreenswapbuffers`, nunca `fadescreen` (§14).
- **Trilha:** `fadeoutbgm 4` quando a Anabel sente; `playbgm
  MUS_DP_LEGEND_APPEARS, TRUE` quando o Necrozma aparece — o `save_song TRUE` é o
  que faz a música da cena voltar depois da batalha de boss; `fadedefaultbgm` na
  conversa final. Qualquer carregamento de mapa limpa o `savedMusic`, então o
  retry depois de blackout começa do tema normal e a cena o troca de novo.

### 4.3 A sinergia é a razão da estrutura

A relação entre as duas **não** é "uma distrai e a outra anda": a clara apaga a
baía e a pesada simplesmente **está mais perto** quando a vista volta. A
contramedida é a estrutura padrão escolha + boss, e aqui ela tem motivo interno:
**quem está sendo olhado não pode se esconder.** O prompt da escolha diz
exatamente isso.

### 4.4 A surpresa do Kukui

A subestimação é plantada no briefing (a ficha de duas páginas), regada no
"Behind me, Professor" e colhida quando o Incineroar cai em (26,9).

> ⚠ **A ficha de duas páginas é load-bearing.** Ela é montada no `Text_BriefingM3`
> para ser desmontada em `CherrygroveCity_Text_UBKukuiRevealed`. Mexer num dos
> dois lados sem o outro mata a piada e a cena.

### 4.5 A Anabel é uma Faller

O pressentimento (§4.2, primeira metade) e o resgate (segunda metade) são as duas
partes de uma revelação só. **A primeira revelação do Faller acontece aqui** — o
comentário no `.pory` de New Bark proíbe, por escrito, devolvê-la para lá. A
recapitulação de uma caixa na reunião de Olivine já foi atualizada.

### 4.6 A escolha — estrutura padrão de todas as missões

`dynmultichoice ... TRUE ...` (sem cancelar: a cena já começou, `VAR_RESULT` só
sai 0 ou 1), resultado em `VAR_TEMP_3` (0 = Blacephalon, 1 = Stakataka), "!"
sobre a escolhida. A escolha é **por tentativa**.

Todos já olham para o lado certo em qualquer ramo: jogador (28,10), Anabel
(27,10), Looker (27,9), Kukui (26,8) e Incineroar (26,9) estão a leste das duas
UBs e olham para oeste; as UBs são `FACE_RIGHT`. Só o Looker precisa de um
`turnobject DIR_WEST` (ele tinha virado para a Anabel).

### 4.7 Batalha — boss simples, terceiro degrau da escala

**Não mudou nada** em relação ao esqueleto: 4 barras, nível 85, multiplicador
140, moveset curado com um golpe de controle cada e item.

```asm
CherrygroveCity_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                   @ limpa pela engine no fim da batalha
	@ B_FLAG_NO_WHITEOUT NÃO é setado: perder = blackout (batalha de ameaça).
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBSetupStakataka
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_BLACEPHALON, 85, ITEM_WISE_GLASSES
	seteventmonmoves MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_FLAMETHROWER, MOVE_PSYSHOCK
	goto CherrygroveCity_EventScript_UBStartBattle

CherrygroveCity_EventScript_UBSetupStakataka::
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_STAKATAKA, 85, ITEM_WEAKNESS_POLICY
	seteventmonmoves MOVE_TRICK_ROOM, MOVE_GYRO_BALL, MOVE_STONE_EDGE, MOVE_BODY_PRESS
```

**Os números, e por que estes:**

| Parafuso | M1 Blackthorn | M2 Mahogany | **M3 Cherrygrove** | Limite / referência |
|---|---|---|---|---|
| Barras | 3 | 4 | **4** | `MAX_BOSS_HEALTH_BARS 4` — no teto desde a M2 |
| Nível | 75 | 80 | **85** | Acima dos 80 dos lendários do repo |
| Multiplicador | 120 | 130 | **140** | `DEFAULT_BOSS_STAT_MULTIPLIER` é 110; 140 é o maior do repo |
| Moveset | curado + item | curado, 4 slots | **curado + 1 golpe de controle cada** | `seteventmonmoves` |
| Item | Leftovers / Life Orb | Magnet / Leftovers | **Wise Glasses / Weakness Policy** | 3º parâmetro de `seteventmon` |
| Perfil de fases | `NONE` | `NONE` | `NONE` | Os 9 perfis existentes são de troca de forma; UBs não têm |

- **Blacephalon** — `Calm Mind` sobe ataque **e** defesa especial e, com 4
  barras, empilha. `Shadow Ball` e `Flamethrower` são os STABs; `Psyshock` bate
  na Defesa física e quebra o muro especial que normalmente segura um setup.
  **Wise Glasses** multiplica os três golpes especiais.
  **`Mind Blown` ficou de fora de propósito:** custa metade dos HP máximos, e
  num chefe de 4 barras é a IA se matando de graça.
- **Stakataka** — `Trick Room` é o degrau de verdade: o chefe mais lento do jogo
  passa a agir **primeiro**, e o `Gyro Ball` continua no máximo de poder porque
  a fórmula lê o *stat* de velocidade, não a ordem do turno. `Stone Edge` é o
  STAB e `Body Press` converte a Defesa em dano. **Weakness Policy** pune a rota
  óbvia (Lutador/Terra pegam 4×) com +2/+2.

**Se o playtest disser parede em vez de ameaça**, mexer nesta ordem, um por vez
— diferente da M2, porque aqui o item é o parafuso mais solto:
1. Tirar o `ITEM_WEAKNESS_POLICY` do Stakataka.
2. Multiplicador 140 → 135 → 130.
3. Trocar `Trick Room` por um quarto golpe de ataque.
4. Nível 85 → 80.

Resultados (`IsPlayerDefeated`, `src/battle_setup.c`):

| Resultado | O que acontece | Por quê |
|---|---|---|
| `B_OUTCOME_WON` | Continua para §5 | A UB escolhida desmaiou |
| `LOST` / `DREW` | **Blackout** → Centro de Cherrygrove | `CB2_WhiteOut`; `CherrygroveCity_OnLoad` faz `setrespawn HEAL_LOCATION_CHERRYGROVE_CITY` |
| `FORFEITED` ("Run") | **Blackout**, igual à derrota | Boss transforma fuga em desistência |
| `CAUGHT` / `RAN` / outro | `UBUnresolved`: reset da cena | Inalcançáveis; tratados por segurança. Nunca viram vitória |

**Retry:** nada foi salvo como concluído. A flag continua setada; ao sair do
Centro a cidade continua vazia, o elenco volta às posições do `map.json`, e as
UBs, o Necrozma e o Incineroar voltam escondidos pelas três `setflag` do
`ON_TRANSITION`. Falar com o Looker recomeça do §4.1 — **inclusive a escolha**.

> `UBGotAway` — Looker: The light closed over them. We are back where we started.
> Kukui: Then we go again. I'm not leaving this beach either.
> Anabel: Heal, and come back. We hold here.

---

## 5. Etapa D — Vitória do Kukui, absorção, reações e gancho

**Coreografia e falas:** [`CHERRYGROVE_ULTRABEAST_SCRIPT.md`](CHERRYGROVE_ULTRABEAST_SCRIPT.md), "Ato 5" e "Ato 6".

Contrato técnico desta etapa:

- **A luta do Kukui é narrativa** — não há batalha para ele. Resolve junto com a
  vitória do jogador; só a fala muda com a escolha. O Incineroar dá um golpe para
  oeste e é recolhido antes da conversa final. Ele **não** vira treinador batalhável.
- **Absorção** (padrão de todas as missões): as duas UBs são arrastadas um tile a
  oeste, para (23,9) e (23,10), oceano aberto, e removidas sob a flag delas
  (`FLAG_TEMP_2`). Necrozma e Incineroar têm flags próprias (`FLAG_TEMP_5` e
  `FLAG_TEMP_6`), então nenhum `removeobject` daqui encosta em terceiros.
- **Ninguém o nomeia.** Para Johto continua sendo "the thing from Blackthorn" /
  "that creature" — o nome fica para a reunião antes do altar (design §6).
- **Reação opcional à família Cosmog:** `CheckMysteryEggPokemon` → `VAR_TEMP_4`,
  checada **depois** da batalha (ela pode evoluir o Pokémon), sem gastar flag
  nenhuma. Sem o Pokémon na equipe o bloco é um `specialvar` e um `return`. O
  passo do Necrozma, (22,10)→(23,10), só é livre porque a Stakataka já saiu.
  `VAR_TEMP_4` é lida de novo na conversa final, que ganha um bloco extra.
- **Conversa final:** `fadedefaultbgm` (a ameaça foi embora), o Incineroar é
  recolhido — é isso que libera (26,9) para o primeiro passo do Kukui —, e o
  elenco se alinha **ortogonalmente** em volta do jogador em (28,10). Ninguém fica
  em (28,11): a caixa de texto não cobre nenhum deles.
- **Gancho sem destino.** O Kukui **não** vai junto; o que ele faz é a corrente
  que começa a Missão 4. `CherrygroveCity_Text_UBHook` e
  `OlivineCity_House1_Text_BriefingM4` são **um par** — nunca editar uma sem a outra.
- **Fecho:** `FADE_TO_BLACK` → `clearflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE` +
  `setvar VAR_RIFT_MISSIONS_STATE, 8` → `warpsilent MAP_CHERRYGROVE_CITY, 28, 10`.
  O `warpsilent` no lugar é **obrigatório**: com a flag limpa, os catorze
  moradores — mais os presentes do trader — só voltariam quando a câmera andasse,
  surgindo do nada. Recarregar faz o `ON_TRANSITION` esconder o elenco, repovoar a
  cidade, destrancar as portas e devolver o follower de uma vez, sob o fade.

---

## 6. Arquivos tocados

**Esqueleto (20/09/2026)** — cinco arquivos:

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_CHERRYGROVE 0x1043` + comentário; `CUSTOM_FLAGS_END` movida |
| `include/constants/map_event_ids.h` | locais 20-24 dentro da seção `// MAP_CHERRYGROVE_CITY` existente |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho atende 2/4/6; `BriefingTalk` ganha o ramo M3; ramos 6/7/≥8 em Looker e Anabel |
| `data/maps/CherrygroveCity/map.json` | flag do evento em 14 objetos; locais 16/17 para `FLAG_TEMP_3/4`; 5 objetos novos |
| `data/maps/CherrygroveCity/scripts.pory` | `call` no `ON_TRANSITION`; **dois `setflag(FLAG_PICKED_*)` no trader**; bloco `raw` novo no fim |

**Revisão 3 — a história (22/09/2026)** — seis arquivos:

| Arquivo | Mudança |
|---|---|
| `include/constants/map_event_ids.h` | `LOCALID_CHERRYGROVE_UB_NECROZMA 25` e `..._INCINEROAR 26` |
| `data/maps/CherrygroveCity/map.json` | dois objetos novos **no fim** (Necrozma (22,10) `FLAG_TEMP_5`; Incineroar (26,9) `FLAG_TEMP_6`); 24 → 26 templates |
| `data/maps/CherrygroveCity/scripts.pory` | bloco `raw` da missão **reescrito inteiro**: cabeçalho com a planta nova e a história em três linhas, `DoorLocked`, `setflag FLAG_TEMP_5/6` na visibilidade, reações ao Cosmog nas conversas, cena nova (§4.2–§4.5), sinergia, absorção, `UBNecrozmaSensesCosmog`, conversa final e gancho sem destino, 14 rótulos de movimento, todos os textos |
| `data/maps/OlivineCity_House1/scripts.pory` | `Text_BriefingM3` reescrito (a ligação do Kukui, a ficha de duas páginas), `LookerGoAheadM3`/`AnabelGoAheadM3` reescritos, comentário da reunião corrigido para citar Cherrygrove, `@ SKELETON:` obsoleto removido |
| `data/maps/NewBarkTown/scripts.pory` | **continuidade**: `Text_UBAnabelFaller` deixa de ser a primeira revelação e passa a ser "o resto"; comentário novo proibindo devolver a primeira revelação para lá |
| `src/field_control_avatar.c` + `include/event_scripts.h` | uma linha em `sLockedTownDoors` + o `extern` |

Não editar `events.inc`/`header.inc`/`connections.inc`, nem os `.inc` gerados de
`CherrygroveCity`, `OlivineCity_House1` e `NewBarkTown`, nem `map.json.bak`.
Validar com `make -j$(nproc)`.

**Sobre o `.pory` de Cherrygrove:** o arquivo é um `raw` gigante (linhas 1-578),
sete `script` em sintaxe poryscript, e **um segundo `raw` no fim** que é a
missão inteira. A revisão 3 só tocou nesse último bloco — o diff não encosta em
nada do conteúdo antigo.

---

## 7. O que ainda é simples × evolução

| Item | Hoje | Evolução possível |
|---|---|---|
| Luta do Kukui | Narrativa, com o Incineroar dando dois golpes na tela e falas que mudam pela escolha | Encenar a troca de golpes inteira. Batalha real contra o Kukui continua **fora** do plano. |
| Chefes | 4 barras, Lv85, x140, moveset + item — **é o alvo**, não placeholder | `setdynamicaifunc` para uma IA própria; perfil de fases novo se algum dia existir troca de forma para UB. |
| Ruptura | Tremor, flash, `setobjectxy` sob o branco | Mar recuando (`setweather`, paleta), animação de portal sobre a água, música própria, as luzes da Blacephalon piscando. |
| Saída do elenco | Warp no lugar | Kukui sendo arrastado para o Centro, Looker e Anabel saindo pela rua a leste. |
| Moradores | Somem, portas trancadas | Reações dos moradores depois do evento (o Fisher e a Little girl têm material óbvio). |
| Anabel | A revelação acontece aqui; as Beast Balls continuam pendentes | Beast Balls em Olivine (design §5, pendente desde a M1). |
| Incineroar | Entra, bate duas vezes, volta para a bola | Poderia ficar ao lado do Kukui na conversa final; custaria mudar a formação ortogonal de §5.3. |

**O que NÃO pode regredir:** a máquina de estados §1.2, a invariante flag ⇔
estado 7, os dois `setflag(FLAG_PICKED_*)` do trader (§3.1.1), as três `setflag`
de visibilidade do `ON_TRANSITION`, o SIM como único ponto de saída, a escolha
refeita a cada tentativa, o tratamento de todos os resultados, a proibição de
captura, os locais 20-26 no fim de `object_events`, a regra de que `VAR_TEMP_1`
é do `Cherrygrove_FriendlyTrader`, e — novo na revisão 3 — a **ordem dos tiles**
de §3.4 e a **continuidade da revelação da Anabel** com a Missão 4.

---

## 8. Dependências frágeis

Coisas que não existem sozinhas e que uma evolução distraída quebra em silêncio:

- **Os 14 objetos de Cherrygrove carregam `FLAG_EVENT_ULTRABEAST_CHERRYGROVE`.**
  Um `removeobject` em qualquer um deles **esvazia a cidade**.
- **`FLAG_PICKED_ZIGZAGOON` e `FLAG_PICKED_RATTATA` dependem de dois `setflag`
  explícitos** (§3.1.1). Apagar qualquer um torna o presente **repetível para
  sempre**, com build limpo e sem nenhum sintoma. É a dependência mais perigosa
  do projeto e a única que estraga conteúdo anterior à missão.
- **`FLAG_TEMP_3` e `FLAG_TEMP_4` são visibilidade dos presentes**; `FLAG_TEMP_5`
  e `FLAG_TEMP_6` são o Necrozma e o Incineroar. Script novo no mapa que use
  qualquer uma delas como flag de trabalho faz alguém sumir ou aparecer sozinho.
- **`VAR_TEMP_1` é `VAR_TEMP_TRANSFERRED_SPECIES`**, do trader.
- **A ordem dos três blocos de `applymovement` da chegada** (Kukui → jogador →
  Looker/Anabel). Mover o Looker antes do jogador o faz tentar descer para um
  (27,8) ocupado.
- **O Kukui tem de parar em (26,8).** (26,9) é do Incineroar e (26,10) é onde o
  Stakataka aterrissa. Descê-lo "para perto do jogador" quebra as duas cenas.
- **A troca de lugar do §4.5 é sequencial.** Anabel para (27,9) → jogador puxado
  para (28,10) → Anabel para (27,10) → Looker para (27,9). Paralelizar qualquer
  par faz dois atores disputarem o mesmo tile.
- **`VAR_TEMP_3` depende de não haver recarga de mapa entre a escolha e o fim.**
  Qualquer warp entre o `dynmultichoice` e o `UBResolved` perde a escolha e o
  Kukui narra a UB errada.
- **`VAR_TEMP_4` é lido duas vezes** (na absorção e na conversa final). Quem
  puser outro `specialvar VAR_RESULT` no meio tem de preservar a cópia.
- **A ficha de duas páginas** do briefing e o `UBKukuiRevealed` são um par.
- **O gancho e o `Text_BriefingM4`** são um par ("eat something", "I'm coming with").
- **A revelação da Anabel e a cena de New Bark** são um par (§4.5).
- **Objetos novos sempre no fim de `object_events`.**
- **O `ON_TRANSITION` de Cherrygrove é compartilhado** com
  `SetTimeBasedEncounters`: preservar as duas linhas.
- **Nenhum `goto_if_ge VAR_RIFT_MISSIONS_STATE` novo em Olivine** sem checar que
  ele não engole os estados 7 e 8.

---

## 9. Pendências e riscos conhecidos

- **Runtime da revisão 3 pendente.** O build só prova que monta.
- **Risco nº 1 — o `setobjectxy` sob o flash.** É a primeira vez que a campanha
  teleporta um objeto no meio de uma cutscene. O que só o runtime mostra: se o
  sprite 32×32 do Stakataka reaparece limpo no tile novo, se a sombra o
  acompanha, e se o `FADE_FROM_WHITE` não deixa um frame com ele nos dois
  lugares. **Se der problema, o plano B é andar com ele com a tela branca**
  (`applymovement` entre os dois `fadescreen`), que é mais lento mas usa só o
  que a M1 e a M2 já usaram.
- **Risco nº 2 — a regressão do presente do trader** (§3.1.1), herdada do
  esqueleto e ainda não testada. Quebra em silêncio. Testar **cedo**.
- **Risco nº 3 — a cena ficou longa**, e o retry a repete inteira. A M4 já
  registrou que uma cena longa repetida cansa (doc da M4 §9). Aqui o retry
  recomeça de `UBLooker`, ou seja, **repete tudo**. Se o playtest reclamar, o
  corte barato é pular a teoria do Kukui e o pressentimento da Anabel numa
  segunda tentativa, com um `VAR_TEMP` de "já viu" — mas isso é decisão do
  autor, não foi feito, e tem de sair do `VAR_TEMP_5+` porque 2, 3 e 4 estão
  ocupados.
- **Retry custa uma caminhada de 20 tiles** (Centro em (47,8), cena em (27,8)).
  Aceito: não há Centro mais perto da praia.
- **`ITEM_WEAKNESS_POLICY` num chefe de 4 barras é inédito** e **x140 é o maior
  multiplicador do repo**. Só o runtime decide se é ameaça ou parede; caminho de
  redução em §4.7, um parafuso por vez.
- **Sprites 32×32 sobre água.** O mapa já tem seis Pokémon de overworld parados
  em água, mas nenhum é 32×32 — e agora são três (Blacephalon, Stakataka,
  Necrozma).
- **Looker e Anabel em dois lugares no estado 7: aceito pelo autor.**
- **Comportamento antigo preservado de propósito:** pegar um dos dois presentes
  do trader continua deixando o outro de pé na rua.
- **Beast Balls continuam pendentes** desde a M1 (design §5).

---

## 10. Teste em runtime

**Regressões do esqueleto (fazer primeiro, são as mais baratas e as que
quebram mais coisa):**

- [ ] Num save que ainda não pegou presente nenhum e com estado < 7: pegar o
      Zigzagoon, sair do mapa, voltar, salvar, recarregar, voltar. Ele **não**
      pode voltar, e o Rattata tem que continuar de pé. Idem para o Rattata em
      outro save.
- [ ] Checagem de espaço do trader com 6 na party: com vaga no PC a oferta
      aparece; com o PC também cheio a oferta **nem chega a aparecer** e nenhuma
      `FLAG_PICKED_*` é setada.
- [ ] Estados 3 e 5 continuam se comportando como antes (M1 e M2 não regrediram);
      Blackthorn e Mahogany continuam povoadas.

**Olivine, estado 6:**

- [ ] Entrar pela porta dispara a cena; o briefing novo cita a ligação do Kukui
      e a ficha de duas páginas; Looker e Anabel voltam ao lugar; estado vira 7.
- [ ] Entrando de outro jeito, falar com Looker **ou** Anabel dá o mesmo
      briefing e o mesmo estado 7.
- [ ] Estado 7: "vá na frente" novo nos dois.

**Cherrygrove, estado 7:**

- [ ] Cidade sem os 14 moradores **e sem o trio da troca inteiro**; Centro
      aberto; **Mart, as três casas e o Darkrai Inn recusando o jogador com o
      bilhete**; o warp (29,21) continua funcionando.
- [ ] Chegar por Route 29, Route 30 e Fly: elenco presente; UBs, Necrozma e
      Incineroar **ausentes** nas três.
- [ ] Conversas: Anabel e Kukui com e sem um Cosmog na equipe (as duas caixas
      extras aparecem só com ele); os dois voltam a olhar para baixo; "Não" com
      o Looker libera e não muda estado.
- [ ] Confirmar que **(27,8) é o único tile** de onde se fala com o Looker.

**A cena:**

- [ ] "Sim": Kukui desce **um** tile só (26,8), depois o jogador, depois Looker e
      Anabel. Nenhum ator sobreposto, ninguém andando sobre a água.
- [ ] O `SE_PIN` + "!" da Anabel toca antes de qualquer sinal do Necrozma.
- [ ] Necrozma aparece em (22,10) **sobre o mar** e fica dentro do quadro.
- [ ] Fenda, os dois gritos, as duas UBs em (24,9) e (24,10).
- [ ] **Sinergia:** primeiro flash → o Stakataka está em (25,10); segundo flash →
      está em (26,10), colado no jogador. O sprite reaparece limpo, sem fantasma
      no tile antigo e com a sombra certa. **É o item de maior risco.**
- [ ] Incineroar nasce em (26,9), bate para baixo, o Stakataka volta de costas
      até (24,10); a fala do Kukui sobre a Liga aparece depois.
- [ ] O Necrozma pulsa, a Anabel vai para (27,9), o jogador é puxado para
      (28,10) **ainda olhando para oeste**, a Anabel desce para (27,10), o Looker
      desce para (27,9) e olha para ela. Ninguém sobrepõe ninguém.
- [ ] As cinco caixas da revelação; nenhuma delas cobre um ator.
- [ ] Menu da escolha não fecha com B.

**Batalha e retry:**

- [ ] Blacephalon: 4 barras, Lv85, Calm Mind cedo, Wise Glasses. Stakataka:
      Trick Room no primeiro turno, Weakness Policy disparando com Lutador/Terra.
- [ ] Bolsa: bola bloqueada nas duas. "Run": desistência → blackout.
- [ ] Perder de propósito: acorda no Centro de **Cherrygrove**; cidade ainda
      vazia, portas ainda trancadas, elenco no lugar, **UBs, Necrozma e
      Incineroar ausentes**; a cena recomeça do zero e a escolha pode ser outra.

**Vitória:**

- [ ] O Incineroar dá o golpe final na tela e a fala do Kukui corresponde à UB
      que o jogador **não** escolheu.
- [ ] Absorção: as duas arrastadas para (23,9)/(23,10), flash, somem; "!" nos
      três; falas de espanto.
- [ ] Com Cosmog/Cosmoem na equipe: o Necrozma se inclina para (23,10) e a fala
      certa aparece. Com Solgaleo/Lunala: a fala do recuo. **Evoluir o Cosmog
      durante a batalha e conferir que a fala usada é a da forma nova.**
- [ ] Necrozma some; Looker pergunta pelas pessoas; o Incineroar volta para a
      bola; Looker vai para (28,9) e Kukui dá a volta até (29,10); ninguém
      atravessa ninguém.
- [ ] O convite do Kukui e o gancho **sem citar New Bark, Lusamine nem três
      assinaturas**.
- [ ] Fade, cidade repovoada, **portas destrancadas**, elenco ausente, follower
      de volta, jogador em (28,10).

**Depois:**

- [ ] Estado 8: briefing da Missão 4 em Olivine revela New Bark, as três
      assinaturas e a Lusamine como **novidade**, e a pergunta "did he eat
      something, at last?" continua fazendo sentido.
- [ ] Missão 4 em campo: a cena da Anabel abre com "On that beach in
      Cherrygrove…" e **não** repete a primeira revelação.
- [ ] Reunião de Olivine (estado 10): a recapitulação de uma caixa continua
      coerente.
- [ ] `Cherrygrove_FriendlyTrader` continua funcionando depois do evento.
- [ ] Salvar/recarregar em cada estado (6, 7, 8) mantém tudo acima.

---

## 11. O que esta missão faz diferente das M1/M2

**Copiado:** a tabela de temporários por mapa, a planta ASCII tirada da colisão
real, a tabela de resultados de batalha, o "bolso de parede" para o tile de
conversa, o `warpsilent` no lugar sob fade, o padrão do Necrozma, a reação
opcional à família Cosmog, as portas trancadas e o gancho sem destino.

**Diferente, de propósito:**

1. **O elenco olha para baixo** (`FACE_DOWN`), porque está encostado na parede
   norte. M1 e M2 usavam `FACE_UP`.
2. **O `ON_TRANSITION` já existia** e é compartilhado com
   `SetTimeBasedEncounters`: aqui se acrescenta um `call`, não um map script.
3. **Três atores de elenco, não quatro**, e o parceiro Pokémon **entra no meio
   da cena** em vez de estar lá desde o começo. A regra visual do design §3.2
   fala da presença overworld permanente de Lillie e Gladion; uma Poké Ball
   aberta no meio da luta é encenação, não identidade — e aqui é a surpresa.
4. **A ruptura abre sobre a água**, e a planta foi lida duas vezes (colisão
   **e** comportamento de metatile). Numa orla o bit de colisão mente: metade da
   praia tem colisão 0 e é água.
5. **A escala não sobe em barras** (teto desde a M2): sobe em nível,
   multiplicador e num golpe de controle por chefe.
6. **A ordem de redução de dificuldade começa pelo item**, não pelo
   multiplicador.
7. **O Centro fica longe** (20 tiles), ao contrário das duas primeiras missões.
8. **Primeira missão que mexe num evento alheio** (os presentes do trader,
   §3.1.1) e **primeira que mexe numa missão posterior** (a revelação da Anabel
   em New Bark, §4.5).
9. **Primeira que usa `setobjectxy` como mecânica**, não como conveniência.
10. **Primeira em que a "autoridade local que tenta e falha" não existe** —
    Cherrygrove não tem Ginásio. O papel foi substituído por dois: o Kukui, que
    tenta e **acerta** (e por isso é surpresa), e a Anabel, que entra na frente
    e paga o preço.

---

## 12. Feedback da implementação do ESQUELETO (20/09/2026) — histórico

Seção escrita **depois** de implementar o esqueleto, conforme a skill
`evento-esqueleto` §6. Fica como **histórico**: tudo que ela mediu continua
valendo (a planta, os temporários, a armadilha do trader, o formato de mapa
deste repo), mas §4, §5 e §7 foram reescritos pela revisão 3 e os números de
linha e as falas citados aqui são os do esqueleto. Onde este bloco e a §13
discordarem, **vale a §13**.

### 12.1 Resultado

**Implementado inteiro, sem cortes.** Nenhum item do plano ficou de fora e
nenhuma decisão de §1 (estado, invariantes, temporários) foi alterada.
`make -j$(nproc)` limpo; ROM linkada (ROM 92,50%, EWRAM 94,28%, IWRAM 73,74%).

Arquivos tocados — exatamente os cinco previstos em §6, nada além:

| Arquivo | O que entrou |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_CHERRYGROVE 0x1043` + comentário de 5 linhas; `CUSTOM_FLAGS_END` movido para ela |
| `include/constants/map_event_ids.h` | 5 locais (20-24) **dentro da seção `// MAP_CHERRYGROVE_CITY` existente**, sem cabeçalho novo |
| `data/maps/CherrygroveCity/map.json` | 14 moradores com a flag do evento; locais 16/17 para `FLAG_TEMP_3`/`FLAG_TEMP_4`; 5 objetos novos no fim (+86 −16 linhas; 19 → 24 templates) |
| `data/maps/CherrygroveCity/scripts.pory` | 1 linha no `ON_TRANSITION` existente; 2 `setflag(FLAG_PICKED_*)` no trader (+ comentário); bloco `raw` novo no fim (730 → 1273 linhas) |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho de três estados, ramo M3 no despachante, ramos 6/7/≥8 em Looker e Anabel, stub da M3 → M4, textos (288 → 352 linhas) |

Ordem de edição seguida à risca: flags/localids → **`setflag(FLAG_PICKED_*)`** →
`map.json` → resto do `scripts.pory` de Cherrygrove → Olivine → build. Como §6
mandava, **não existiu nenhum estado intermediário do checkout em que o presente
do trader fosse repetível**.

### 12.2 Premissas do plano que foram reconferidas e bateram

Tudo abaixo foi medido no checkout, não herdado do plano:

- **A planta de §3.4 está certa tile a tile.** Colisão por `dump_mapa.py`
  (parede em y=5/6; tudo livre em y=7..13 de x=21 a x=29) **e** comportamento de
  metatile lido dos `metatile_attributes.bin` de `johto_general` e
  `cherrygrove_city`. O resultado bate exatamente com o desenho do plano,
  inclusive a distinção que importa: (26..29, 7) e (26..27, 8..13) são `MB_SAND`;
  **x=25 e a faixa (22..25, 7) são `MB_SHALLOW_WATER` (colisão 0, andável a pé)**;
  x≤24 de y=8 para baixo é `MB_OCEAN_WATER`. (24,9) e (24,10) — onde ficam as
  duas UBs — são oceano.
- **Os 7 tiles pisados pelos atores são areia ou chão comum:** (26,8), (26,9),
  (26,10), (27,8), (27,9), (27,10), (28,8) são `MB_SAND`; (28,9) e (28,10) são
  `MB_NORMAL`. Ninguém pisa em água em passo nenhum, nos dois blocos de
  coreografia (§4.2 e §5).
- **O bolso do Looker confere:** (27,6) tem colisão 1, (26,7) é o Kukui e (28,7)
  é a Anabel. (27,8) é o único vizinho livre.
- **O caminho do retry confere:** `HEAL_LOCATION_CHERRYGROVE_CITY` é (47,8)
  (`src/data/heal_locations.h:277-282`) e a linha y=8 é livre de x=27 a x=49
  (x=50 é parede). 20 passos retos, sem objeto no caminho.
- **`VAR_TEMP_1` é `VAR_TEMP_TRANSFERRED_SPECIES`** (`vars.h:370`) e é usada nos
  dois ramos do trader. A missão usa só `VAR_TEMP_2/3`. `FLAG_TEMP_1` a
  `FLAG_TEMP_4` estavam livres no mapa antes da edição (zero ocorrências).
- **A armadilha de §3.1.1 era real.** `grep` confirmou: antes desta missão
  **nada no projeto fazia `setflag FLAG_PICKED_ZIGZAGOON` nem
  `setflag FLAG_PICKED_RATTATA`** — as duas constantes só apareciam no `if` do
  próprio trader, no `map.json` e em `flags.h`. Quem as setava era o efeito
  colateral do `removeobject`. Os dois `setflag` explícitos entraram **antes** da
  troca do `map.json`.
- **Os 14 moradores tinham `flag: "0"`** e os locais 16/17 tinham exatamente
  `FLAG_PICKED_ZIGZAGOON`/`FLAG_PICKED_RATTATA` — asserção no script de edição,
  não inspeção visual. Os 6 objetos de flag própria ficaram intocados.
- **Só existem 4 `removeobject` em Cherrygrove** (`LOCALID_GUIDE_GENT`,
  `LOCALID_CHERRYGROVE_SILVER`, `LOCALID_CHERRY_ZIGZAGOON`,
  `LOCALID_CHERRY_RATTATA`), mais os 2 novos nas UBs (`FLAG_TEMP_2`). Nenhum toca
  os 14 objetos que agora carregam a flag do evento.
- **`BLACEPHALON` e `STAKATAKA` têm bloco `OVERWORLD(`** (`SIZE_32x32`,
  `SHADOW_SIZE_M`, `TRACKS_FOOT`), ambas `.isUltraBeast = TRUE`.
- **Os 8 golpes e os 2 itens existem** (`ITEM_WISE_GLASSES` 476,
  `ITEM_WEAKNESS_POLICY` 502); `OBJ_EVENT_GFX_KUKUI` (332), `LOOKER` (334) e
  `ANABEL` (70) existem; `ShakeCamera` está em `data/specials.inc:360`;
  `Common_Movement_ExclamationMark` em `data/scripts/movement.inc:8`.
- **`MAX_BOSS_HEALTH_BARS` é 4** (`include/battle_boss.h:4`) e
  `DEFAULT_BOSS_STAT_MULTIPLIER` é 110 — as 4 barras são o teto, não escolha.
- **`OBJECT_EVENT_TEMPLATES_COUNT` é 64** (`include/constants/global.h:88`): 24
  templates cabem com folga. `OBJECT_EVENTS_COUNT` (spawn simultâneo) é 16, mas
  os 5 objetos novos ficam todos escondidos fora do incidente e, durante ele, o
  mapa spawna **menos** objetos que antes — a missão não aumenta a pressão no
  orçamento de spawn em momento nenhum.
- **O `events.inc` gerado confirma os locais 20-24 na ordem certa**, com os 19
  antigos inalterados: `LOCALID_CHERRYGROVE_SILVER` continua 13,
  `LOCALID_CHERRY_ZIGZAGOON` 16 e `LOCALID_CHERRY_RATTATA` 17.
- **Checagem obrigatória de §2.3 passou:**
  `grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE" data/maps/OlivineCity_House1/scripts.pory`
  devolve exatamente duas linhas de código, ambas com `, 8,`.

### 12.3 Divergências em relação ao plano

Quatro, todas pequenas, nenhuma muda contrato:

1. **O plano quase levou a uma planta errada — não por culpa dele, mas de quem
   fosse reler o mapa com as máscaras de vanilla.** Ver §12.7: este repo **não**
   usa o formato de `pokeemerald` para `map.bin` nem para
   `metatile_attributes.bin`. A primeira leitura desta implementação, feita com
   as máscaras clássicas, produziu uma planta em que a praia inteira era "chão
   comum" e as UBs ficavam em cima de terra firme. A planta do plano só foi
   confirmada depois de corrigir as máscaras. **Nada mudou no código por causa
   disso**, mas a §12.7 foi acrescentada para a Missão 4 não repetir o erro.
2. **`CherrygroveCity_Movement_AnabelToPlayer` e
   `CherrygroveCity_Movement_PlayerToLine` têm corpo idêntico**
   (`walk_down, walk_down, face_left, step_end`). Ficaram como **dois rótulos
   separados**, como o plano listava, porque descrevem caminhos de atores
   diferentes ((28,8)→(28,10) e (27,8)→(27,10)) e uma evolução que mexa num não
   deve mexer no outro por acidente. Custo: 4 bytes.
3. **Os dois `turnobject` de §3.5 continuam sendo no-op hoje**, como o plano já
   previa: falando do único tile possível, `faceplayer` já deixa Kukui e Anabel
   virados para o sul. Ficaram pelo mesmo motivo da M2 — documentam a intenção e
   protegem uma evolução que mude posições.
4. **Comentário novo no `ON_TRANSITION` compartilhado.** O plano só pedia a linha
   de `call`; entraram também três linhas de `@` avisando que o bloco é
   compartilhado com `SetTimeBasedEncounters` e que as duas linhas têm que
   sobreviver a qualquer edição futura (é a dependência frágil listada em §8).

5. **Conserto extra no `Cherrygrove_FriendlyTrader`, a pedido do autor
   (20/09/2026): checagem de espaço antes de qualquer diálogo de oferta.** Não
   estava no plano. O trader tinha um furo anterior a esta missão: com a party
   **e** o PC cheios, `givemon` devolve `MON_CANT_GIVE`,
   `Common_EventScript_GiftMon` (`data/event_scripts.s:1152`) só trata
   `MON_GIVEN_TO_PARTY` e `MON_GIVEN_TO_PC`, e o presente sumia — com a flag
   marcada como pego. Agora, **antes da fala da oferta**:

   ```
   getpartysize
   if (var(VAR_RESULT) == PARTY_SIZE) {
       specialvar(VAR_RESULT, ScriptCheckFreePokemonStorageSpace)
       if (var(VAR_RESULT) == FALSE) { goto(Cherrygrove_TraderNoRoom) }
   }
   ```

   Só **party cheia E PC cheio** bloqueia: com apenas a party cheia, `givemon`
   manda para o PC sozinho. Mesmo padrão do ovo de Cosmog em
   `VioletCity_PokemonCenter` (`scripts.pory:16-22`). Há ainda uma guarda
   defensiva `MON_CANT_GIVE` depois de cada `givemon`, **antes do
   `setflag(FLAG_PICKED_*)`**, para que um presente que falhe nunca se marque
   como pego. `Cherrygrove_TraderNoRoom` é o destino comum das duas e só fala e
   libera (o `lock` é de quem chamou). Conferido no `.inc` gerado: os três
   caminhos (party com vaga / PC com vaga / os dois cheios) e as duas guardas
   pulam para os rótulos certos, e **nenhum diálogo de oferta aparece** quando
   não há espaço.

Textos: o conteúdo é o do plano. A quebra em `\n` / `\l` / `\p` foi feita na
implementação, e travessões longos viraram vírgulas ou ponto final para caber na
caixa — nenhuma frase mudou de sentido.

### 12.4 O que o build **não** prova

O build limpo prova que monta e linka. Não prova nada do seguinte, que é o que a
checklist de §10 existe para cobrir:

- **Risco nº 1 — a regressão do presente do trader (§3.1.1).** É a única coisa
  que esta missão pode quebrar em conteúdo que já existia, e quebra **em
  silêncio**: se o `setflag(FLAG_PICKED_*)` não funcionar como esperado, o
  presente volta a aparecer no próximo load e vira farm infinito, com build
  limpo e sem nenhum sintoma. O teste é o item "Regressão do presente" de §10 e
  tem que ser feito **cedo**, não no fim.
- **Risco nº 2 — o elenco não spawnar.** O bolso do Looker depende de o Kukui e
  a Anabel estarem em (26,7) e (28,7). Se `FLAG_TEMP_1` ficar setada por algum
  motivo, o Looker fica sozinho e vira alcançável por três lados; a cena começa
  com o jogador no lugar errado e toda a coreografia de §4.2 desanda sem erro.
- Que **x140 com 4 barras no nível 85** é "ameaça" e não "parede". É o maior
  multiplicador do repo e o `ITEM_WEAKNESS_POLICY` num chefe de 4 barras é
  inédito. Caminho de redução em §4.4, um parafuso por vez, começando pelo item.
- Que o **sprite 32x32 do Stakataka sobre um tile de oceano** fica bem. O mapa já
  tem seis Pokémon de overworld parados em água, mas nenhum é 32x32.
- Que a caixa de texto não cobre ninguém. O argumento ("ninguém fica ao sul do
  jogador") é geométrico e confere na planta, mas a altura real dos sprites das
  UBs não foi medida contra a caixa.
- Que a caminhada de 20 tiles do retry não irrita no playtest (§9).
- Que o follower volta certo nas duas saídas (as duas terminam em `warpsilent`,
  o que desfaz o `hidefollower` — mas só o runtime confirma).

### 12.5 Ordem sugerida de teste no emulador

Otimizada para achar cedo o que quebra mais coisas, não para seguir §10 na ordem
escrita:

1. **Antes de qualquer coisa da missão**, num save que ainda não pegou presente
   nenhum e com `VAR_RIFT_MISSIONS_STATE` < 7: pegar o Zigzagoon, sair do mapa,
   voltar, salvar, recarregar, voltar. Ele **não** pode voltar, e o Rattata tem
   que continuar de pé. É o risco nº 1 e é barato de testar.
2. Estado 6, entrar em Olivine House1 pela porta: briefing M3, estado vira 7.
3. Estado 7, chegar em Cherrygrove por **Fly**: a cidade está vazia (inclusive o
   trio da troca inteiro)? o elenco está nos três tiles? as UBs estão ausentes?
   — valida `ON_TRANSITION`, `map.json` e o bolso do Looker de uma vez.
4. Tentar falar com o Looker de (26,8), (28,8), (29,7) e da linha y=7 — tem que
   ser impossível. Entrar na água rasa de x=25 (isso é normal) e confirmar que
   (24,9)/(24,10) continuam inalcançáveis a pé.
5. SIM → assistir a coreografia inteira até as UBs aparecerem. Se algum ator
   atravessar outro, é a ordem dos três `applymovement` de §4.2.
6. Escolher e **perder de propósito** — o retry é a parte que mais depende do
   estado estar certo. Conferir que a escolha pode ser outra na segunda vez.
7. Só então vencer, e conferir o repovoamento, o estado 8 e o stub da M4.
8. Por último, as regressões: trader funcionando depois do evento, Blackthorn e
   Mahogany povoadas, estados 3 e 5 ainda se comportando como antes.

### 12.6 Para quem for evoluir

Ler §7 e §8 antes de tocar em qualquer coisa. Os quatro itens que mais
provavelmente serão quebrados por distração, em ordem de risco:

1. Apagar um dos **dois `setflag(FLAG_PICKED_*)`** do `Cherrygrove_FriendlyTrader`
   — torna o presente repetível para sempre. Há um comentário de 5 linhas em
   caixa alta acima de cada um.
2. `removeobject` num dos **14 moradores** de Cherrygrove — **esvazia a cidade**.
   Há um `WARNING` no cabeçalho da seção em `scripts.pory`.
3. A **ordem dos três blocos de `applymovement`** em
   `CherrygroveCity_EventScript_UBScene` (Kukui → jogador → Looker/Anabel).
4. Qualquer `goto_if_ge VAR_RIFT_MISSIONS_STATE, 6` novo em Olivine — engole os
   estados 7 e 8. Foi exatamente a linha que esta missão teve de apagar, e o
   comentário acima dos dois despachantes agora cita o episódio pelo nome.

`grep -rn "SKELETON:" data/maps/CherrygroveCity data/maps/OlivineCity_House1`
lista os 8 pontos que ainda são placeholder.

### 12.7 Recado técnico para a Missão 4: como ler a colisão deste repo

§11 item 10 já mandava a Missão 4 (New Bark, que também tem costa) repetir a
leitura dupla. Esta seção diz **como**, porque o formato dos arquivos aqui não é
o de `pokeemerald` e a diferença é silenciosa: com as máscaras erradas sai uma
planta plausível e completamente falsa.

| Campo | `pokeemerald` vanilla | **Este repo** | Onde conferir |
|---|---|---|---|
| Id do metatile em `map.bin` | `0x03FF` (bits 0-9) | **`0x07FF` (bits 0-10)** | `include/global.fieldmap.h:7` |
| Colisão em `map.bin` | `0x0C00`, 2 bits, shift 10 | **`0x0800`, 1 bit, shift 11** | `include/global.fieldmap.h:8,11` |
| Entrada de `metatile_attributes.bin` | `u32` (4 bytes) | **`u16` (2 bytes)** | `include/global.fieldmap.h:74` (`const u16 *metatileAttributes`) |
| Bytes por metatile em `metatiles.bin` | 16 (8 tiles) | **24 (12 tiles, tileset de 3 camadas)** | `metatiles.bin` ÷ 24 = nº de entradas de `attributes` ÷ 2 |
| Metatiles no primário | 512 | **1024** | `include/fieldmap.h:6` |
| Comportamento dentro do atributo | `& 0x00FF` | `& 0x00FF` (igual) | `include/global.fieldmap.h:39` |

Duas conferências baratas que pegam o erro na hora:

- `os.path.getsize(metatiles.bin) // 24` tem que dar
  `os.path.getsize(metatile_attributes.bin) // 2`. Se não der, a suposição de
  tamanho está errada. (Em `johto_general`: 18840/24 = 1570/2 = **785**.)
- `include/constants/metatile_behaviors.h` neste repo é um **`enum`**, não uma
  lista de `#define`. Um parser de `#define` devolve zero nomes e o script
  imprime hexadecimal, que "parece funcionar". Valores conferidos neste repo:
  `MB_NORMAL` = 0x00, `MB_OCEAN_WATER` = 0x15, `MB_SHALLOW_WATER` = 0x17,
  `MB_SAND` = 0x21, `MB_DEEP_WATER` = 0x12. **Não são os de cor de memória de
  `pokeemerald`** — extrair do `enum`, sempre.

E a regra de leitura que a praia de Cherrygrove ensinou, que vale igual para New
Bark: **`MB_SHALLOW_WATER` tem colisão 0 e o jogador anda nela a pé.** Só
`MB_OCEAN_WATER` (e água funda) segura quem está sem Surf. Um script que trate
"colisão 0" como "chão bom" põe ator dentro d'água; um que trate "água" como
"barreira" fecha um caminho que está aberto. Numa cena de costa as duas leituras
são obrigatórias.

O script usado nesta implementação está em §12.7 apenas como descrição; o
`dump_mapa.py` da skill `encenar-cutscene` **continua lendo só o bit de
colisão**, e isso basta para cenas de rua. Para costa, complementar à mão.


---

## 13. Revisão 3 — a história (22/09/2026)

Feedback do autor sobre o esqueleto: *"o esqueleto está pronto, agora vamos
montar uma história épica"*. Feito com a skill `evoluir-historia-de-evento`,
tendo a M1 revisão 3 e a M2 revisão 3 como modelo.

### 13.1 Pedido → como ficou

| Pedido | Como ficou |
|---|---|
| Legal ter sido o **Kukui quem avisou o Looker**; deixar a conversa na casa de Olivine mais interessante | `Text_BriefingM3` reescrito inteiro (§2.3): o relatório chegou por telefone, quatro dias antes, de um pesquisador de Alola que deu janela, direção e maré — e **corrigiu a janela duas vezes, certo as duas**. Looker manda ler a ficha dele em voz alta, e ela tem duas páginas. |
| Diálogos mais naturais, de acordo com a personalidade | Todas as falas reescritas pela voz do design §3.1. Looker teatral e formal que pergunta primeiro pelas pessoas; Anabel precisa, separando observação de hipótese; Kukui informal, concreto e **específico sobre movimento** ("a house still has to decide where to stand"), nunca reduzido a bordão. Nenhum `@ SKELETON:` de fala sobrou no mapa. |
| A vibe é boa mas falta história | Arco completo (§4.2–§5.3): o mundo já em movimento (a baía errada, o Kukui de plantão), escalada (o Necrozma abre a fenda), **perigo direto ao jogador duas vezes** (o Stakataka colado nele; o Necrozma mirando nele), dois resgates de quem ninguém esperava, a consequência inesperada depois da vitória (a absorção), reações na voz de cada um, cuidado antes do relatório, um presente com significado e um gancho sem destino. |
| O Necrozma ataca de novo; **a Anabel sente antes** dele aparecer e **defende o protagonista**; a condição de Faller dela abre já nesse ponto | §4.2 (ela para no meio de uma instrução: "It's here." / "There is nothing on the meter." / "I know.") e §4.5 (o Necrozma vira para o jogador, ela entra na frente, a baía fica branca e ela fica de joelho na areia; cinco caixas de pé e volta ao trabalho). |
| Reforçar a **sinergia** entre as UBs; virar padrão dos próximos encontros e ficar mais interessante | §4.3: a sinergia é **mostrada** antes de explicada e **corrige o especialista na cara dele**. A clara não cobre a pesada enquanto ela anda — ela apaga a baía e a pesada **já está mais perto** (`setobjectxy` sob o flash), duas vezes, a segunda colada no jogador. A contramedida ganhou motivo interno: quem está sendo olhado não pode se esconder. Regra comum ampliada no design §6. |
| O Necrozma **absorve os dois** e desaparece no final | §5.1, mesmo padrão da M1 e da M2: pulso, arrasto de costas até encostar nele, flash, `removeobject`, espanto dos três, e ele vai embora pela mesma luz. |
| Reação opcional do Necrozma **e dos NPCs** sobre Cosmog na party | §5.2 (Necrozma depois da batalha, uma fala por estágio) + §3.5 (Anabel e Kukui **antes** da cena) + `UBAftermathCosmog`/`UBAftermathLegend` na conversa final. Zero flag, zero var persistente; sem o Pokémon a cena é idêntica. |
| Uma surpresa sobre ele **lutar bem**, ligada a ele ser o **Fundador da Liga de Alola**; os personagens subestimam ele um pouco | Plantado no briefing (a ficha de duas páginas, "no combat authorisation"), regado na cena ("Behind me, Professor." / "Nah.") e colhido em §4.4: ele solta o Incineroar, tira o Stakataka de cima do jogador, e explica que ninguém em Alola escreve relatório sobre o cara que **fundou a Liga** — e que por um tempo foi ele quem ficava no fim dela. A Anabel pede desculpa pela ficha. |
| **Não dizer onde é o próximo evento**; deve ser mistério até voltar a Olivine | `UBHook` reescrito: "The readings haven't settled… Where, and when, we don't know yet. So we keep watching. Come back to our house in Olivine. The moment something opens, you will be the first to know." Nenhuma menção a New Bark, à Lusamine ou às três assinaturas. Quem revela é o `Text_BriefingM4`, que já estava escrito assim. |

### 13.2 Ambiguidades e contradições resolvidas por escrito

- **"A condição de Faller abre nesse ponto" × a M4 já tinha a revelação.** O
  pedido novo vence (skill `evoluir-historia-de-evento` §1). A revelação foi
  **dividida**: aqui ela diz **o que é**, em cinco caixas, sob pressão, e corta
  ("The rest of it later"); em New Bark, com três fendas abrindo juntas, sai **o
  resto** — o que ela lembra, o que não lembra, a mão, e a promessa. O texto da
  M4 foi ajustado em duas frases e ganhou um comentário proibindo devolver a
  primeira revelação para lá. O design §3.1 (tabela da progressão e a frase
  "sua experiência não concede poderes para detectar portais") foi reescrito.
- **"Ela sente antes" × a regra "experiência não é previsão" (design §3.3).** A
  regra continua valendo para todo mundo, e para a Anabel ela foi **precisada**,
  não revogada: ela **sente uma ruptura**, que é uma sensação física de Faller;
  ela **não** sabe o que vem, quantos são, nem o que vai acontecer — continua
  sendo o instrumento que conta, e no briefing continua sendo ele que mede.
  Registrado no design.
- **O Kukui sem parceiro fora da Poké Ball (design §3.2) × ele lutar bem.** A
  regra visual fala da presença overworld **permanente** de Lillie e Gladion.
  Kukui chega sozinho na praia e continua sozinho na chegada — e é exatamente
  por isso que a Poké Ball no meio da luta funciona. O Incineroar entra em cena,
  dá dois golpes e volta para a bola antes da conversa final.
- **Cherrygrove não tem Ginásio**, então a regra "o Líder local tenta e falha"
  não tem quem cumpra. Em vez de inventar uma autoridade, o papel foi
  substituído por dois (§11 item 10).
- **Portas trancadas** eram regra comum pendente desde o esqueleto; entraram
  nesta revisão (§3.1.2), com bilhete da Polícia Internacional em vez de Líder.

### 13.3 Conferido

- `make -j$(nproc)` limpo. ROM 92,70%, EWRAM 94,28%, IWRAM 73,77%.
- `events.inc` gerado: 26 templates, os 24 antigos **na mesma ordem**
  (`LOCALID_CHERRYGROVE_SILVER` 13, `..._ZIGZAGOON` 16, `..._RATTATA` 17
  intactos), Necrozma 25 e Incineroar 26 no fim.
- Planta relida com o script de `metatile_attributes` de §12.7, não com as
  máscaras de vanilla: todo tile pisado por ator é `MB_SAND` ou `MB_NORMAL`;
  (22,10), (23,9), (23,10), (24,9) e (24,10) são `MB_OCEAN_WATER`; (25,10) é
  `MB_SHALLOW_WATER` e só o Stakataka passa por ela, de teleporte.
- Nenhum par de atores disputa tile no mesmo passo: os pares simultâneos andam
  em colunas diferentes, e a troca do §4.5 é sequencial.
- `medir_linha.py` nos quatro `.pory` tocados: nenhuma linha passa de 208 px.
- `checar_falantes.py`: 13 falantes, tudo em ordem; toda fala nova tem
  plaquinha e nenhuma narração herda a anterior.
- `grep` em Olivine: `goto_if_ge VAR_RIFT_MISSIONS_STATE` continua aparecendo
  exatamente duas vezes em código, ambas com `, 12,` (o altar) — nenhuma delas
  engole os estados 7 e 8.
- `grep -rn "SKELETON:"` em `data/maps/CherrygroveCity`: **zero**.

### 13.4 Runtime

**Pendente.** Checklist em §10; os três maiores riscos estão em §9, e o
primeiro deles — o `setobjectxy` sob o flash — tem plano B escrito.

## 14. Revisão 4 — escurecimento dos flashes e a trilha da cena (23/09/2026)

Dois pedidos do autor depois de jogar.

### 14.1 "Fica impossivelmente escuro"

Não havia escurecimento nenhum no script — o **flash** é que escurecia a cidade
a cada repetição.

`fadescreen FADE_TO_*` copia `gPlttBufferFaded` por cima de `gPlttBufferUnfaded`
antes de escurecer (`FadeScreen`, `src/field_weather.c`; o comentário do upstream
avisa: *"works fine, except if the screen is faded back in without transitioning
to a different screen"*). O `FADE_FROM_*` seguinte chama
`BeginTimeOfDayPaletteFade`, que reaplica o tint de horário **em cima de paletas
já tintadas**. À noite o tint é `coeff = 10`, `TINT_NIGHT` ≈ 0,46
(`gTimeOfDayBlend`, `src/overworld.c:1618`): cada par de flashes multiplica a
cena por 0,46 outra vez, e a M3 dá **oito** flashes antes da escolha. De dia
`coeff = 0` e nada acontece; por isso só a cena, que é noturna, adoece.

Todo `fadescreen` de dentro da cena virou `fadescreenswapbuffers` — mesmo efeito
com BLDY no hardware (`FadeScreenHardware`), sem tocar em paleta, e com os
registradores de blend resetados no fim do `FADE_FROM_*`. Continuam
`fadescreen FADE_TO_BLACK` apenas `UBUnresolved` (retry depois do blackout) e
`UBHook` (recarga em lugar), onde o warp refaz as paletas do zero. A receita de
flash da skill `evoluir-historia-de-evento` §6 estava errada e foi corrigida
junto.

### 14.2 "A música não muda, fica bizarra a música feliz"

A cena tocava `MUS_HG_CHERRYGROVE` de ponta a ponta — o tema de praia da cidade
enquanto o Necrozma rasga o céu.

| Ponto | Comando | Por quê |
|---|---|---|
| Depois de `UBAnabelSenses`, antes do tremor | `fadeoutbgm 4` | A Anabel sente antes dos instrumentos; a cidade emudece. O tremor e a subida do Necrozma acontecem em silêncio. |
| Logo depois do `addobject` do Necrozma | `playbgm MUS_DP_LEGEND_APPEARS, TRUE` | Trilha própria a partir do momento em que a coisa aparece. |
| Topo de `UBAftermath` | `fadedefaultbgm` | Acabou: limpa o `savedMusic` e devolve o tema da cidade. |

O `TRUE` do `playbgm` grava em `gSaveBlock1Ptr->savedMusic`
(`Overworld_SetSavedMusic`), e é o que faz a **batalha de boss devolver a trilha
certa**: ao voltar dela, `Overworld_PlaySpecialMapMusic` prefere o `savedMusic` ao
tema do mapa. Não vaza: qualquer carregamento de mapa chama
`Overworld_ClearSavedMusic`, então o retry depois do blackout começa do tema
normal e a cena o troca de novo, e o `fadedefaultbgm` do pós-cena limpa o resto.

`MUS_DP_LEGEND_APPEARS` estava desligada em `include/config/songs_enabled.h`
(`SONG_MUS_DP_LEGEND_APPEARS 0`) e foi ligada. ROM em 92,73% depois disso.

**Pendente nas outras três missões.** O pedido foi sobre a M3; M1, M2 e M4
continuam sem troca de trilha. Quando forem feitas, é a mesma receita, e a
mesma trilha mantém o padrão do Necrozma.

**Conferido:** `make -j$(nproc)` limpo. **Runtime pendente** — testar **à noite**:
a oitava ruptura tão clara quanto a primeira, a música caindo na fala da Anabel,
voltando igual depois da batalha e virando tema de cidade no pós-cena.
