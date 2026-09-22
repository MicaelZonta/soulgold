# Cherrygrove — Blacephalon + Stakataka (Rift Mission 3) — plano de implementação ESQUELETO

**Status:** **esqueleto implementado** — 20/09/2026. Build limpo
(`make -j$(nproc)`), runtime pendente. Revisão 2: o plano das §§0-11 foi seguido
inteiro, sem cortes e sem mudança de contrato; o feedback da implementação está
em §12, e §12.7 acrescenta um recado técnico obrigatório para a Missão 4.
**Modo:** esqueleto (skill `evento-esqueleto`). Diálogo curto, coreografia mínima,
mas estado, visibilidade, gatilhos, batalha e retry **completos e corretos**.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5, §6, §6.3 (V16).
**Missões anteriores:**
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (M1) e
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (M2)
— este doc **continua** a máquina de estados das duas e **substitui** o stub da
Missão 3 que a M2 deixou em `OlivineCity_House1` (§2.3 daquele doc), que vira o
stub da Missão 4.

Escopo: do gancho final de Mahogany (o jogador volta a Olivine) até o fim do
incidente de Cherrygrove, terminando com o gancho que manda o jogador de volta a
Olivine para a Missão 4 (Kartana + Guzzlord + Nihilego, New Bark, Lusamine).

**Decisões desta missão:**
- Elenco: **Looker, Anabel e Kukui**. Kukui **não** tem Pokémon fora da Poké Ball:
  a regra de parceiro visível do design §3.2 nomeia só Lillie e Gladion. O elenco
  em campo cai de quatro objetos (M2) para três.
- Local: `CherrygroveCity`, **o canto noroeste da praia** — a faixa de areia
  (26-29, 7) onde a rua principal encontra o mar. É "a shore" do gancho da M2.
- As Ultra Beasts surgem **sobre a água**, a oeste: a ruptura abre no mar.
- Escala: 4 barras (teto), **nível 85**, **multiplicador 140**, moveset curado com
  **um golpe de controle cada** (Calm Mind / Trick Room) e item. Continua a
  escalada M1 → M2 → M3 (§4.4).
- Mesma estrutura padrão: escolha + boss simples, captura bloqueada, derrota =
  blackout e retry.

---

## 0. Resumo do fluxo

```text
Mahogany resolvido                       VAR_RIFT_MISSIONS_STATE = 6
  └─ entrar em OlivineCity_House1 ─────▶ cena: Looker + Anabel, briefing M3 → 7
                                           + setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
       └─ Cherrygrove: cidade vazia (só Looker, Anabel, Kukui)
            └─ falar com Looker ▶ Kukui expõe o padrão das duas ▶ SIM
                 └─ cena 100% scriptada ▶ ruptura no mar: Blacephalon + Stakataka
                      └─ ESCOLHA: qual você enfrenta? Kukui fica com a outra
                           └─ boss battle simples, 4 barras, Lv85, x140, moveset + item
                                ├─ perdeu / desistiu → blackout → Centro de Cherrygrove → flag setada → recomeça
                                ├─ outro             → reset silencioso → recomeça
                                └─ venceu            → fala do Kukui conforme a escolha → gancho
                                                       → clearflag + estado 8 → warp no lugar (cidade repovoa)
                                     └─ Olivine House1: stub da Missão 4 (New Bark / Lusamine)
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` | `include/constants/flags.h` | `0x1043` | Primeira livre depois de `FLAG_EVENT_ULTRABEAST_MAHOGANY` (0x1042). Conferido: `grep -n "0x1043" include/constants/flags.h` não retorna nada. **Atualizar `CUSTOM_FLAGS_END`** para apontar nela (hoje aponta para `FLAG_EVENT_ULTRABEAST_MAHOGANY`). |
| `LOCALID_CHERRYGROVE_UB_*` | `include/constants/map_event_ids.h` | 20-24 | Cinco linhas novas, à mão, **dentro da seção `// MAP_CHERRYGROVE_CITY` que já existe** (`:199-203`, com `LOCALID_GUIDE_GENT 1`, `LOCALID_CHERRYGROVE_SILVER 13`, `LOCALID_CHERRY_ZIGZAGOON 16`, `LOCALID_CHERRY_RATTATA 17`). Diferente da M2, aqui **não** se cria cabeçalho novo. |

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

> ⚠ **`VAR_TEMP_1` está OCUPADO em `CherrygroveCity`.**
> `include/constants/vars.h:370` define `VAR_TEMP_TRANSFERRED_SPECIES` como
> **`VAR_TEMP_1`**, e `Cherrygrove_FriendlyTrader` o usa nos dois ramos da troca
> (`scripts.pory:683` e `:698`). Mesma armadilha da M2 (lá era o vendedor de Rage
> Candy Bar), com nome diferente. Por isso esta missão também começa em
> `VAR_TEMP_2`. `VAR_TEMP_0` está livre no mapa, mas fica sem uso de propósito:
> as três missões usam `VAR_TEMP_2/3` e vale a pena manter a uniformidade.

`FLAG_TEMP_1` a `FLAG_TEMP_4` estão livres em `CherrygroveCity` (nenhuma
ocorrência de `FLAG_TEMP` no `.pory` nem no `.inc` gerado). `FLAG_TEMP_3/4` são
muito usadas no projeto, mas **sempre dentro de um mapa só** (Ice Path, Fuchsia
Gym, Dragon's Den, Cerulean Cave…), e temporárias não atravessam load — não há
conflito. Evitar `FLAG_TEMP_E`, que a engine reserva para suprimir o follower. Os usos de
`VAR_TEMP_2/3` e `FLAG_TEMP_2` que aparecem em `data/scripts/` são de
`contest_hall`, `battle_arcade_*` e `interview.inc` — outros mapas; temporários
zeram a cada load (`ClearTempFieldEventData`), então não há conflito.

Reconfirmar antes de implementar:

```bash
grep -rn "FLAG_TEMP_[12]\b\|VAR_TEMP_[0123]\b" data/maps/CherrygroveCity data/maps/OlivineCity_House1
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
tem que devolver **exatamente duas** linhas, ambas com `, 8,`.

Textos (inglês, placeholder — caixas de ~34 colunas):

> `Text_BriefingM3` —
> Looker: {PLAYER}! Cherrygrove at last. The report is confirmed.
> Anabel: Two signatures. One of them will not hold still.
> Looker: Professor Kukui has been on that shore for four days. He will not leave it.
> Anabel: He says the tear over the sea opens and closes on a rhythm. He wants to see it open.
> Looker: He is a scientist. I would also like him to be a careful man.
> Anabel: The town is clear, {PLAYER}. Go and get the Professor off that beach.
>
> `Text_LookerGoAheadM3` —
> Looker: The northwest shore, {PLAYER}. You cannot miss him. He is the one in the lab coat.
>
> `Text_AnabelGoAheadM3` —
> Anabel: Go on. And please make the Professor sit down for one minute.
>
> `Text_LookerMission4Stub` (estado ≥ 8) —
> Looker: New Bark Town. Madame Lusamine is still standing on that road, and she has not moved. Come back soon, {PLAYER}!
>
> `Text_AnabelMission4Stub` (estado ≥ 8) —
> Anabel: Rest. Looker will brief you on New Bark.

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

### 3.2 Elenco e Ultra Beasts — anexar no fim de `object_events` (locais 20-24)

| Local id | Nome | Gráfico | (x,y) | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 20 | `LOCALID_CHERRYGROVE_UB_KUKUI` | `OBJ_EVENT_GFX_KUKUI` | (26,7) | `FACE_DOWN` | `CherrygroveCity_EventScript_UBKukui` | `FLAG_TEMP_1` |
| 21 | `LOCALID_CHERRYGROVE_UB_LOOKER` | `OBJ_EVENT_GFX_LOOKER` | (27,7) | `FACE_DOWN` | `CherrygroveCity_EventScript_UBLooker` | `FLAG_TEMP_1` |
| 22 | `LOCALID_CHERRYGROVE_UB_ANABEL` | `OBJ_EVENT_GFX_ANABEL` | (28,7) | `FACE_DOWN` | `CherrygroveCity_EventScript_UBAnabel` | `FLAG_TEMP_1` |
| 23 | `LOCALID_CHERRYGROVE_UB_BLACEPHALON` | `OBJ_EVENT_GFX_SPECIES(BLACEPHALON)` | (24,9) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |
| 24 | `LOCALID_CHERRYGROVE_UB_STAKATAKA` | `OBJ_EVENT_GFX_SPECIES(STAKATAKA)` | (24,10) | `FACE_RIGHT` | `NULL` | `FLAG_TEMP_2` |

- Todos com `"elevation": 0` (os 19 objetos existentes do mapa usam 0 sem
  exceção), `movement_range_x/y: 0`, `TRAINER_TYPE_NONE`,
  `trainer_sight_or_berry_tree_id: "0"`, e `"local_id"` explícito com o nome da
  constante — como a M2 acabou fazendo (§12.3 daquele doc).
- **`FACE_DOWN`, não `FACE_UP`.** O elenco está encostado na parede norte e o
  jogador chega pela rua, vindo do sul/leste. Esta é a primeira missão em que o
  elenco olha para baixo; não copiar o `FACE_UP` da M2 por hábito.
- Conferido: `BLACEPHALON` e `STAKATAKA` têm bloco `OVERWORLD(` em
  `src/data/pokemon/species_info/gen_7_families.h` (`SIZE_32x32`, `SHADOW_SIZE_M`,
  paleta e paleta shiny próprias; Blacephalon com `sAnimTable_Following_Asym`,
  Stakataka com `sAnimTable_Following`). Ambas `.isUltraBeast = TRUE` e
  `.perfectIVCount = LEGENDARY_PERFECT_IV_COUNT`.
- `OBJ_EVENT_GFX_KUKUI` = 332 (`include/constants/event_objects.h:339`), com
  `gObjectEventGraphicsInfo_Kukui` registrado em
  `src/data/object_events/object_event_graphics_info_pointers.h:672` e já usado
  em `Route30_MrPokemonsHouse`. `OBJ_EVENT_GFX_ANABEL` = 70,
  `OBJ_EVENT_GFX_LOOKER` = 334, ambos já usados em Olivine House1, Blackthorn e
  Mahogany.
- **As duas UBs ficam sobre o mar**, em (24,9) e (24,10), tiles de
  `MB_OCEAN_WATER`. Não é gambiarra: o próprio mapa já tem quatro Corsola e dois
  Staryu parados em tiles de água ((4,11), (6,12), (4,24), (2,25), (25,16),
  (27,26)). A ruptura abre no mar, que é a razão de Kukui não sair da praia — e
  o oceano tem a vantagem de o jogador a pé não conseguir chegar nelas, ao
  contrário da água rasa de x=25 (ver o aviso em §3.4).
- **Sempre no fim de `object_events`:** os locais 20-24 são posicionais; inserir
  qualquer coisa no meio renumera `LOCALID_CHERRYGROVE_SILVER` (13),
  `LOCALID_CHERRY_ZIGZAGOON` (16) e `LOCALID_CHERRY_RATTATA` (17), que são lidos
  por script.
- 24 templates < limite de 64.

Looker e Anabel ficam em Olivine **e** aqui durante o estado 7 — aceito pelo
autor desde a M1, o evento inteiro é cutscene (design §5). Ver §9.

### 3.3 Visibilidade — `ON_TRANSITION` (já existe; ganha uma linha)

Diferente de Blackthorn e Mahogany, `CherrygroveCity` **já tem** `ON_TRANSITION`.
Não criar outro: acrescentar o `call` dentro do que existe, sem reordenar nada.

```asm
CherrygroveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CherrygroveCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, CherrygroveCity_OnLoad
	.byte 0

CherrygroveCity_OnTransition::
	callnative SetTimeBasedEncounters
	call CherrygroveCity_EventScript_ApplyUBVisibility   @ NOVO
	end

@ Elenco (FLAG_TEMP_1) visível só com o incidente ativo. Ultra Beasts
@ (FLAG_TEMP_2) sempre escondidas no load: só a cena as faz aparecer.
@ Temps zeram a cada load (ClearTempFieldEventData), então recalcula sempre.
CherrygroveCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	call CherrygroveCity_EventScript_ApplyGiftMonVisibility
	goto_if_unset FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	return

CherrygroveCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	return

@ Presentes do Friendly Trader (locais 16 e 17), §3.1.1.
@ FLAG_PICKED_* continua sendo a verdade persistente; FLAG_TEMP_3/4 são só o
@ cache que o campo "flag" do template consegue ler.
@   visível <=> (ainda não foi pego) E (não há incidente ativo)
CherrygroveCity_EventScript_ApplyGiftMonVisibility::
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	goto_if_set FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_GiftMonsStayHidden
	goto_if_set FLAG_PICKED_ZIGZAGOON, CherrygroveCity_EventScript_GiftMonRattataOnly
	clearflag FLAG_TEMP_3
CherrygroveCity_EventScript_GiftMonRattataOnly::
	goto_if_set FLAG_PICKED_RATTATA, CherrygroveCity_EventScript_GiftMonsStayHidden
	clearflag FLAG_TEMP_4
CherrygroveCity_EventScript_GiftMonsStayHidden::
	return
```

Tabela-verdade do bloco dos presentes, conferida ramo a ramo:

| Incidente | `PICKED_ZIGZAGOON` | `PICKED_RATTATA` | Zigzagoon | Rattata |
|---|---|---|---|---|
| ativo | qualquer | qualquer | escondido | escondido |
| não | não | não | **visível** | **visível** |
| não | sim | não | escondido | **visível** |
| não | não | sim | **visível** | escondido |
| não | sim | sim | escondido | escondido |

As três últimas linhas são exatamente o comportamento de hoje; só a primeira é
nova. O `call` aninhado (`OnTransition` → `ApplyUBVisibility` → `ApplyGiftMon…`)
é seguro: a pilha de `call` do contexto de script comporta bem mais que dois
níveis, e cada `goto` do meio não desempilha nada.

`SetTimeBasedEncounters` mexe em `FLAG_NIGHT_POKEMON` (objeto 6) e não toca em
`FLAG_TEMP_1/2`: a ordem das duas linhas é indiferente. O `call` vem depois
porque o `callnative` existente já estava lá.

Roda também ao entrar pela borda — Route 29 (oeste/norte) e Route 30 (leste) —,
não só por warp.

### 3.4 Planta da cena (colisão real + comportamento de metatile)

```bash
python3 .claude/skills/encenar-cutscene/dump_mapa.py CherrygroveCity 21 32 5 12
```

O `dump_mapa.py` só lê o bit 11 (colisão). **Neste mapa isso não basta:** boa
parte da orla tem colisão 0 e mesmo assim é água. A distinção areia / água rasa /
oceano abaixo veio dos `metatile_attributes.bin` de `johto_general` (primário,
metatiles < 1024) e `cherrygrove_city` (secundário), lendo
`attributes & METATILE_ATTR_BEHAVIOR_MASK` e comparando com
`include/constants/metatile_behaviors.h`. **Qualquer cena de praia ou porto
precisa dessa segunda leitura**; só a colisão engana.

```text
       x= 21 22 23 24 25 26 27 28 29 30 31 32
  y= 5       #  #  #  #  #  #  #  #  #  #  #  #
  y= 6       #  #  #  #  #  #  #  #  #  #  #  #   parede norte: (21..32, 6) é toda bloqueada
  y= 7       ~  w  w  w  w  U  K  A  s  .  .  .   U Kukui (26,7)  K Looker (27,7)  A Anabel (28,7)
  y= 8       ~  ~  ~  ~  c  s  t  s  .  .  .  .   t (27,8) = ÚNICO tile para falar com o Looker
  y= 9       ~  ~  ~  B  c  s  s  .  .  .  .  .   B Blacephalon (24,9)   c = Corsola (escondido)
  y=10       ~  ~  ~  S  w  s  *  .  .  .  .  .   S Stakataka (24,10)    * (27,10) = jogador no fim
  y=11       ~  ~  ~  ~  w  s  s  .  .  .  .  #
  y=12       ~  ~  ~  ~  w  s  s  .  .  #  #  #

  #  colisão      s  areia (MB_SAND)          .  chão comum (MB_NORMAL)
  ~  oceano (MB_OCEAN_WATER): só de Surf, o jogador a pé NÃO entra
  w  água rasa (MB_SHALLOW_WATER): colisão 0, o jogador a pé ANDA nela
```

> ⚠ **A coluna x=25 (e a faixa (22..25, 7)) é água RASA, não barreira.** O bit de
> colisão dela é 0 e o jogador anda nela a pé, chapinhando. Não confundir com o
> oceano de x≤24, esse sim intransponível sem Surf. As duas Ultra Beasts ficam em
> tiles de **oceano** de propósito: ninguém encosta nelas a pé.

O Looker fica no "bolso" (27,7): **(27,6) é parede**, (26,7) é o Kukui e (28,7) é
a Anabel. **Só dá para falar com ele de (27,8), olhando para cima.** Isso torna o
início da cena determinístico sem `getplayerxy`. Documentar num comentário `@`
acima do script.

O Kukui e a Anabel **não** têm bolso, e não precisam: são só conversa. O Kukui é
alcançável de (26,8) e também de **(25,7)**, que é água rasa andável — a primeira
versão desta planta errou isso, achando que x=25 era barreira. A Anabel é
alcançável de (28,8) e (29,7). Nada disso afeta o início da cena, que só o Looker
dispara.

Caminho do Centro até a cena, para o retry: a saída do Centro fica em **(47,8)**
(`HEAL_LOCATION_CHERRYGROVE_CITY`, `src/data/heal_locations.h:277-282`), e a
linha **y=8 é livre de x=27 a x=49**, sem um único objeto no caminho. São 20
passos retos para oeste até o tile de conversa. Ver §9 para o custo real do
retry.

### 3.5 Conversas antes da cena

- `CherrygroveCity_EventScript_UBAnabel` (`lock`, `faceplayer`):
  "Anabel: The town is in the Gym at Violet. Two buses, no argument."
  "Speak with Looker when you're ready."
  Depois `turnobject LOCALID_CHERRYGROVE_UB_ANABEL, DIR_SOUTH` (volta ao
  `FACE_DOWN` do `map.json`).
- `CherrygroveCity_EventScript_UBKukui` (`lock`, `faceplayer`):
  "Kukui: {PLAYER}! Four days I've been out here, cousin."
  "I'd rather tell it once, with everyone listening — go talk to Looker."
  Depois `turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_SOUTH`.

Os dois `turnobject` são no-op quando o jogador fala do único tile possível
(`faceplayer` já os deixa virados para o sul), mas ficam: documentam a intenção
e protegem contra uma evolução que mude as posições. Custo zero. Mesma decisão da
M2 (§12.3, item 2).

---

## 4. Etapa C — A cena (100% scriptada a partir do SIM)

### 4.1 Pré-checagens (`CherrygroveCity_EventScript_UBLooker`)

```asm
@ Só alcançável de (27,8), olhando para cima: (27,6) é parede e os vizinhos
@ leste/oeste do Looker são a Anabel e o Kukui. Não precisa de getplayerxy.
CherrygroveCity_EventScript_UBLooker::
	lock
	faceplayer
	msgbox CherrygroveCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox CherrygroveCity_Text_UBKukuiTheory, MSGBOX_DEFAULT
	msgbox CherrygroveCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_UBNotReady
	goto CherrygroveCity_EventScript_UBScene

CherrygroveCity_EventScript_UBNotReady::
	msgbox CherrygroveCity_Text_UBNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end
```

- Nenhum estado muda antes do SIM. O SIM é o último ponto de saída.
- Batalha simples: não é preciso checar quantidade de Pokémon.
- A exposição do Kukui vem **antes** do SIM de propósito: o design §3.2 pede
  "curiosidade acompanhada de responsabilidade pelo entorno; observações de
  coordenação e movimento viram ajuda prática". A observação dele (as duas UBs
  trabalham em par, uma distrai e a outra entra) **é** a justificativa da
  estrutura escolha + boss, igual à leitura da Lillie na M2. Looker cobra os
  quatro dias na praia; Kukui responde com a razão responsável; Anabel confirma
  com um dado.

> `UBLookerGreet` —
> Looker: {PLAYER}! Over here. And watch your footing — that water is not behaving.
> The tear has opened twice since dawn. Both times it closed before we could reach it.
>
> `UBKukuiTheory` —
> Kukui: {PLAYER}! Man, am I glad it's you.
> Four days on this beach, and I've finally got it: those two work as a pair.
> The bright one goes first. It flashes, everybody looks — and nobody sees the big one walking in behind it.
> Looker: Professor. Four days. On a beach. Under a hole in the sky.
> Kukui: Yeah. And if it opened with nobody watching, who tells this town when to run? I stayed so somebody would know.
> Anabel: He called the second opening eleven minutes early. He's earned the beach.
> Kukui: So here's the play: one of us takes the bright one's eyes, the other takes the wall. Split them up and neither one gets to hide.
>
> `UBReady` —
> Looker: One warning, {PLAYER}. These two are worse than Mahogany.
> Anabel: Bring everything you have. Are you ready?
>
> `UBNotReady` —
> Looker: Wise. The Center is open, and I am not moving from this sand.

### 4.2 Ruptura

Ordem obrigatória: **Kukui primeiro, depois o jogador, depois Looker e Anabel.**
O Looker só pode descer depois que o jogador libera (27,8), e o Kukui desce
primeiro porque é ele que vai ficar na frente.

```asm
CherrygroveCity_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	@ Kukui   (26,7)->(26,8)->(26,9)->(26,10), olha oeste. Coluna x=26 o tempo
	@ todo; termina ao lado do jogador, que vem parar em (27,10).
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_KukuiAdvance
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
	@ Jogador (27,8)->(27,9)->(27,10), olha oeste. Coluna x=27 o tempo todo.
	@ Nenhum tile em comum com o Kukui em nenhum passo; mesmo assim vai depois,
	@ para que (27,8) só vague quando o jogador já saiu.
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Looker (27,7)->(27,8), Anabel (28,7)->(28,8): colunas diferentes, sem
	@ cruzamento -> juntos. (27,8) só vaga quando o jogador desce, acima.
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_StepDownFaceLeft
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_StepDownFaceLeft
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
	msgbox CherrygroveCity_Text_UBRiftWarning, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1          @ vertical pan
	setvar VAR_0x8005, 1          @ horizontal pan
	setvar VAR_0x8006, 24         @ num shakes
	setvar VAR_0x8007, 5          @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
	addobject LOCALID_CHERRYGROVE_UB_STAKATAKA
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox CherrygroveCity_Text_UBAppear, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_UBChoose

CherrygroveCity_Movement_KukuiAdvance:
	walk_down, walk_down, walk_down, face_left, step_end
CherrygroveCity_Movement_PlayerToLine:
	walk_down, walk_down, face_left, step_end
CherrygroveCity_Movement_StepDownFaceLeft:
	walk_down, face_left, step_end
```

Conferido tile a tile nos `metatile_attributes`: (26,8), (26,9), (26,10), (27,8),
(27,9), (27,10) e (28,8) são **areia** (`MB_SAND`, colisão 0); (28,9) e (28,10),
usados na saída em §5, são chão comum. Nenhum ator pisa em água em passo nenhum. Nenhum objeto da cidade fica no caminho — os
dois Corsola em (25,8)/(25,9) estão escondidos pela flag do evento e, de todo
modo, estão sobre água, fora da rota.

Posições ao fim da aproximação:

```text
  y= 7                                  (26,7), (27,7), (28,7) vazios
  y= 8                       Looker(27,8)   Anabel(28,8)
  y= 9   Blacephalon(24,9)
  y=10   Stakataka(24,10)    Kukui(26,10)   Jogador(27,10)
```

Com o jogador em (27,10) a câmera cobre x ≈ 20..34, y ≈ 6..15: as duas UBs
(x=24), o Kukui, o Looker e a Anabel ficam na tela.
**O jogador é o ator mais ao sul da cena** — empatam em `y` com ele só o Kukui,
ao lado, e o Stakataka, três tiles a oeste. Ninguém fica abaixo dele, então a
caixa de texto não cobre personagem nenhum (a mesma garantia geométrica da
M2 §4.2).

Todo mundo já olha para o lado certo em qualquer ramo da escolha: o jogador, o
Kukui, o Looker e a Anabel estão a leste das duas UBs e terminam olhando para
oeste (`face_left`); as duas UBs olham para leste (`FACE_RIGHT` no `map.json`).
Nenhum `turnobject` é necessário.

> `UBRiftWarning` — Kukui: There! The water's going flat — that's the tell! Everybody back!
>
> `UBAppear` —
> Looker: Blacephalon! And that is— what is that?
> Kukui: Stakataka! Whoa. That's not one Pokémon, cousin. That's a whole crowd of them, stacked up.
> Anabel: ...The sea went quiet before the readings did. Again.
> Anabel: Later. Not now.

(A fala da Anabel é a única semente de Faller aqui, e é a continuação direta da
linha dela em Mahogany. O design reserva a revelação para a reunião antes do
altar, §7 item 6 — não adiantar.)

### 4.3 A escolha — estrutura padrão de todas as missões

Sem opção de cancelar (`ignoreBPress = TRUE`): a cena já começou. Já confirmado
na M2 em `Task_HandleScrollingMultichoiceInput` (`src/script_menu.c`) que o
`LIST_CANCEL` é engolido — `VAR_RESULT` só pode sair 0 ou 1, não falta
tratamento de `MULTI_B_PRESSED`.

```asm
CherrygroveCity_EventScript_UBChoose::
	msgbox CherrygroveCity_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, CherrygroveCity_Text_ChoiceBlacephalon, CherrygroveCity_Text_ChoiceStakataka
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Blacephalon, 1 = Stakataka
	closemessage
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBPickStakataka
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, Common_Movement_ExclamationMark
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
	msgbox CherrygroveCity_Text_UBPickedBlacephalon, MSGBOX_DEFAULT
	closemessage
	goto CherrygroveCity_EventScript_UBBattle

CherrygroveCity_EventScript_UBPickStakataka::
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, Common_Movement_ExclamationMark
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
	msgbox CherrygroveCity_Text_UBPickedStakataka, MSGBOX_DEFAULT
	closemessage
	goto CherrygroveCity_EventScript_UBBattle
```

> `UBChoosePrompt` —
> Kukui: Call it, {PLAYER}! Which one do you want?
> I'll take whatever's left, and I'll keep it looking at me.
>
> `ChoiceBlacephalon` — "Blacephalon" · `ChoiceStakataka` — "Stakataka"
>
> `UBPickedBlacephalon` — Kukui: The bright one's yours! Don't watch the lights — watch its feet!
> I've got the wall. Come on, big guy, over here!
>
> `UBPickedStakataka` — Kukui: The wall is yours! Get under it before it settles!
> I'll keep the fireworks busy. Let's go!

### 4.4 Batalha — boss simples, terceiro degrau da escala

Mesmas peças da M2, com os parafusos apertados mais uma volta. O sistema de boss
só existe em batalha **simples** (`InitBossBattleData`), que é a outra razão de a
missão dividir as UBs.

```asm
@ SKELETON: coreografia e falas são placeholder; os números abaixo NÃO são.
@ Terceiro degrau da escala: M1 = 2 barras/Lv70/x110, M2 = 4/Lv80/x130.
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

CherrygroveCity_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, CherrygroveCity_EventScript_UBResolved
	goto CherrygroveCity_EventScript_UBUnresolved
```

Ordem das macros idêntica à de `bosslegendaryencounterwithmoves`
(`asm/macros/event.inc:2231-2247`): `setbossbattle` → `playmoncry` →
`seteventmon` → `seteventmonmoves` → `special`. `seteventmon` aceita o item como
3º parâmetro (`asm/macros/event.inc:2159`). Nenhum caminho sai do script entre
elas, então não é preciso `clearbossbattle`.

**Os números, e por que estes:**

| Parafuso | M1 Blackthorn | M2 Mahogany | **M3 Cherrygrove** | Limite / referência |
|---|---|---|---|---|
| Barras | 2 | 4 | **4** | `MAX_BOSS_HEALTH_BARS 4` (`include/battle_boss.h:4`) — já estava no teto na M2; não sobe mais |
| Nível | 70 | 80 | **85** | Acima dos 80 dos lendários do repo; abaixo do que a M4 deve usar |
| Multiplicador | 110 | 130 | **140** | `DEFAULT_BOSS_STAT_MULTIPLIER 110`. A M2 foi o primeiro acima de 110 no projeto |
| Moveset | golpes de nível | curado, 4 slots | **curado + 1 golpe de controle cada** | `seteventmonmoves` |
| Item | nenhum | Magnet / Leftovers | **Wise Glasses / Weakness Policy** | 3º parâmetro de `seteventmon` |
| Perfil de fases | `NONE` | `NONE` | `NONE` | Os 9 perfis existentes são todos de troca de forma (Mega/Primal/Tera); UBs não têm |

**Com as barras no teto desde a M2, a escalada da M3 tem que vir de outro lugar.**
Os dois degraus novos são o nível/multiplicador e, principalmente, **um golpe de
controle em cada chefe** — é a diferença qualitativa, não só numérica:

- **Blacephalon** (SpA altíssima, Spe alta, frágil) — `Calm Mind` é o análogo do
  Tail Glow do Xurkitree, mas cumulativo em ataque **e** defesa especial; com 4
  barras ela empilha. `Shadow Ball` (STAB Fantasma) e `Flamethrower` (STAB Fogo)
  são os dois STABs; `Psyshock` bate na Defesa física e quebra o muro especial
  que normalmente segura um setup especial. **Wise Glasses** multiplica os três
  golpes especiais, em vez de um só tipo como o Magnet da M2.
  - **`Mind Blown` foi deliberadamente deixado de fora**, mesmo sendo o golpe
    assinatura: ele custa metade dos HP máximos, e num chefe de 4 barras isso é a
    IA se matando de graça. Não "corrigir" isso numa evolução sem medir.
- **Stakataka** (Def monstruosa, Atk alta, Spe 13) — `Trick Room` é o degrau de
  verdade: com ele o chefe mais lento do jogo passa a agir **primeiro**, e o
  `Gyro Ball` continua no máximo de poder, porque a fórmula dele lê o *stat* de
  velocidade, não a ordem do turno. `Stone Edge` é o STAB Pedra e `Body Press`
  converte a Defesa dele em dano. **Weakness Policy** pune a rota óbvia
  (Lutador/Terra pegam 4x) com +2/+2 — o jogador tem que escolher entre matar
  rápido e alimentar o chefe.

Movesets conferidos contra `src/data/pokemon/all_learnables.json`: os oito golpes
estão nas listas de `BLACEPHALON` e `STAKATAKA` (não é exigência da engine — é
coerência). Os dois itens existem: `ITEM_WISE_GLASSES = 476` e
`ITEM_WEAKNESS_POLICY = 502` (`include/constants/items.h`).

Música: `BattleSetup_StartLegendaryBattle` cai no `default` → `MUS_DP_VS_LEGEND`.

**Se o playtest disser que é parede em vez de ameaça**, mexer nesta ordem, um de
cada vez — **a ordem é diferente da M2**, porque aqui o item é o parafuso mais
solto:
1. Tirar o `ITEM_WEAKNESS_POLICY` do Stakataka (é o item com maior variância).
2. Multiplicador 140 → 135 → 130.
3. Trocar `Trick Room` por um quarto golpe de ataque.
4. Nível 85 → 80.
As barras já estão no teto e não são parafuso. Não mexer em nada de §1 para
"compensar".

Resultados (`IsPlayerDefeated`, `src/battle_setup.c`):

| Resultado | O que acontece | Por quê |
|---|---|---|
| `B_OUTCOME_WON` | Continua para §5 | A UB escolhida desmaiou |
| `LOST` / `DREW` | **Blackout** → Centro de Cherrygrove | `CB2_WhiteOut`; `CherrygroveCity_OnLoad` faz `setrespawn HEAL_LOCATION_CHERRYGROVE_CITY`, e a tabela de whiteout manda para `MAP_CHERRYGROVE_CITY_POKEMON_CENTER` (`src/data/heal_locations.h:538`) |
| `FORFEITED` ("Run" no boss) | **Blackout**, igual à derrota | Boss transforma fuga em desistência (`HandleEndTurn_RanFromBattle`, `src/battle_main.c`) |
| `CAUGHT` / `RAN` / outro | `UBUnresolved`: reset da cena | Inalcançáveis (bola bloqueada; fuga vira FORFEITED), tratados por segurança. Nunca viram vitória. |

**Retry:** nada foi salvo como concluído. A flag do evento continua setada; ao
sair do Centro a cidade continua vazia, o elenco volta às posições do `map.json`
e as UBs voltam a ficar escondidas. Falar com o Looker recomeça do §4.1 —
**inclusive a escolha**, que pode ser outra.

```asm
CherrygroveCity_EventScript_UBUnresolved::
	msgbox CherrygroveCity_Text_UBGotAway, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_CHERRYGROVE_CITY, 28, 8       @ recarrega: elenco no lugar, UBs escondidas
	waitstate
	releaseall
	end
```

> `UBGotAway` —
> Looker: They closed ranks again. We are back where we started.
> Kukui: Then we go again. I'm not leaving this beach either.

(28,8) fica a um passo a leste do tile de conversa do Looker, na areia livre.

---

## 5. Etapa D — Resolução e gancho

A luta do Kukui contra a outra UB é **narrativa**: não há batalha para ele. Ela se
resolve junto com a vitória do jogador, e a fala do Kukui muda conforme a escolha.

```asm
CherrygroveCity_EventScript_UBResolved::
	@ Os dois objetos continuam no mapa após a batalha (não há recarga).
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_CHERRYGROVE_UB_BLACEPHALON   @ flag = FLAG_TEMP_2: seguro
	removeobject LOCALID_CHERRYGROVE_UB_STAKATAKA
	fadescreen FADE_FROM_WHITE
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon
	msgbox CherrygroveCity_Text_UBKukuiFoughtStakataka, MSGBOX_DEFAULT
	goto CherrygroveCity_EventScript_UBAfterBattle

CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon::
	msgbox CherrygroveCity_Text_UBKukuiFoughtBlacephalon, MSGBOX_DEFAULT

CherrygroveCity_EventScript_UBAfterBattle::
	msgbox CherrygroveCity_Text_UBAfterKukui, MSGBOX_DEFAULT
	closemessage
	@ Looker (27,8)->(27,9), olha oeste. Mesma coluna do jogador, uma linha
	@ acima dele; nunca ao sul, para não ficar sob a caixa de texto.
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_StepDownFaceLeft
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
	@ Anabel (28,8)->(28,9)->(28,10), olha oeste. Coluna própria (x=28), sempre
	@ a leste do jogador; nenhum tile em comum com o Looker. SEQUENCIAL por
	@ clareza de leitura da cena.
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelToPlayer
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_EAST     @ jogador (27,10) está exatamente a leste dele
	msgbox CherrygroveCity_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE   @ invariante: flag e var juntas
	setvar VAR_RIFT_MISSIONS_STATE, 8
	warpsilent MAP_CHERRYGROVE_CITY, 27, 10       @ recarrega no lugar: cidade repovoa,
	waitstate                                     @ elenco some pelo ON_TRANSITION
	releaseall
	end

CherrygroveCity_Movement_AnabelToPlayer:
	walk_down, walk_down, face_left, step_end
```

Posições finais: jogador (27,10) → oeste; Looker (27,9) → oeste (logo acima do
jogador); Anabel (28,10) → oeste (imediatamente a leste do jogador, na mesma
linha); Kukui (26,10) → **leste**, encarando o jogador de frente, sem diagonal.
O jogador fica cercado em linha: Kukui a oeste, Anabel a leste, Looker ao norte.
Conferido: (27,9) é areia; (28,9) e (28,10) são chão comum; todos livres.
**Ninguém fica ao sul do jogador** — a caixa de texto não cobre ator nenhum.

O `CherrygroveCity_Movement_StepDownFaceLeft` é o mesmo rótulo de §4.2,
reaproveitado.

Por que `warpsilent` no lugar: com a flag limpa, os catorze objetos escondidos —
mais os presentes do trader, cuja visibilidade também é recalculada no load — só
voltariam quando a câmera andasse, surgindo do nada. Recarregar faz o
`ON_TRANSITION` esconder o elenco e spawnar a cidade de uma vez, sob o fade. O
follower do jogador volta pelo warp, desfazendo o `hidefollower`.

Textos (inglês, placeholder) — **o último bloco é o gancho para Olivine**:

> `UBKukuiFoughtStakataka` (o jogador escolheu Blacephalon) —
> Kukui: Stakataka never got a step in. Turns out if you stay right in front of it, it has to keep deciding.
>
> `UBKukuiFoughtBlacephalon` (o jogador escolheu Stakataka) —
> Kukui: The bright one kept flashing at me, and I kept not looking. It ran out of tricks.
>
> `UBAfterKukui` —
> Kukui: Look at the water — it's coming back. They're going home on their own.
> Four days out here for eleven minutes of that. Worth every one of them.
>
> `UBHook` —
> Looker: Professor, you will now come off this beach and eat something. That is not a request.
> Kukui: Yeah, yeah. ...{PLAYER}. That thing about watching their feet? Write it down. Somebody's going to need it.
> Anabel: Looker. The next reading came in while we were out there.
> Anabel: New Bark Town. Three signatures this time.
> Looker: Three. In the town where {PLAYER} started.
> Anabel: And there is a woman already waiting on the road in. She gave us a name.
> Looker: ...Lusamine. Come back to the house in Olivine, {PLAYER}. We are not sending you into that one blind.

---

## 6. Arquivos tocados (checklist de implementação)

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_ULTRABEAST_CHERRYGROVE 0x1043` + comentário; mover `CUSTOM_FLAGS_END` |
| `include/constants/map_event_ids.h` | 5 locais (20-24) **dentro da seção `// MAP_CHERRYGROVE_CITY` existente** |
| `data/maps/OlivineCity_House1/scripts.pory` | gatilho atende os estados 2, 4 e 6; `BriefingTalk` ganha o ramo M3; ramos 6/7/≥8 em Looker e Anabel; stub da M3 vira stub da M4; textos novos |
| `data/maps/CherrygroveCity/map.json` | flag do evento em **14** objetos; `flag` dos locais 16 e 17 vira `FLAG_TEMP_3`/`FLAG_TEMP_4` (§3.1.1); 5 objetos novos no fim |
| `data/maps/CherrygroveCity/scripts.pory` | uma linha `call` no `ON_TRANSITION` existente; **dois `setflag(FLAG_PICKED_*)` no `Cherrygrove_FriendlyTrader`** (§3.1.1, obrigatório); bloco `raw` novo no fim do arquivo com visibilidade, conversas, cena, escolha, boss, resolução, textos e movimentos |

Não editar `events.inc`/`header.inc`/`connections.inc`, nem os `.inc` gerados de
`CherrygroveCity` e `OlivineCity_House1`, nem `map.json.bak`. Validar com
`make -j$(nproc)`.

**Sobre o `.pory` de Cherrygrove:** o arquivo é um `raw` gigante (linhas 1-578)
seguido de sete `script` em sintaxe poryscript. São **três** pontos de edição:
o `ON_TRANSITION`, dentro do `raw` (uma linha); o `Cherrygrove_FriendlyTrader`,
na parte poryscript (duas linhas, sintaxe `setflag(...)` com parênteses); e
**todo o resto num `raw` novo, acrescentado no fim do arquivo**, para que o diff
não encoste no conteúdo existente.

Ordem sugerida: flags/localids → **`setflag(FLAG_PICKED_*)` no trader** →
`map.json` de Cherrygrove → resto do `scripts.pory` de Cherrygrove →
`scripts.pory` de Olivine → build. O `setflag` vem **antes** da troca do
`map.json` de propósito: assim não existe nenhum commit intermediário em que o
presente seja repetível.

---

## 7. Esqueleto × evolução

O que está **deliberadamente simples**. Cada item vira um comentário
`@ SKELETON: <o que falta>` no script correspondente, para que
`grep -rn "SKELETON:" data/maps/{CherrygroveCity,OlivineCity_House1}` liste tudo
que falta polir:

| Item | Esqueleto | Evolução prevista |
|---|---|---|
| Luta do Kukui | Narrativa: resolvida junto com a vitória do jogador, fala muda pela escolha | Mostrar o combate dele na tela. Batalha real contra Kukui **não** é o plano. |
| Kukui sem parceiro visível | Três objetos de elenco, nenhum Pokémon ao lado dele | O design §3.2 só exige parceiro fora da Poké Ball para Lillie e Gladion. Um Rockruff/Incineroar ao lado do Kukui é opcional; se entrar, segue a skill `parceiro-pokemon-de-npc` e vira o local 25, **no fim** de `object_events`. |
| Chefes | 4 barras, Lv85, x140, moveset + item — **já é o alvo**, não é placeholder | `setdynamicaifunc` (`asm/macros/event.inc`) para uma IA própria; perfil de fases novo em `src/battle_boss.c` se algum dia existir troca de forma para UB. |
| Coreografia Kukui + jogador | Dois blocos sequenciais | Podem virar **um bloco paralelo**: as colunas x=26 (Kukui) e x=27 (jogador) nunca se cruzam em nenhum passo, e os dois terminam lado a lado em (26,10)/(27,10). Evolução segura e mais bonita. |
| Diálogos | Curtos, placeholder | Reescrever pela voz do design §3.1 (Kukui entusiasmado e concreto, sem virar piada; Looker teatral; Anabel precisa). |
| Ruptura | Tremor + flash; UBs surgem paradas; a escolhida só dá "!" | Mar recuando antes da abertura (`setweather`, paleta), animação de portal sobre a água, música própria, as luzes do Blacephalon piscando. |
| Saída do elenco | Warp no lugar | Kukui sendo arrastado para o Centro, Looker e Anabel saindo pela rua a leste. |
| Moradores | Somem | Reações dos moradores depois do evento (o Fisher e a Little girl têm material óbvio). |
| Anabel | Só fala; a semente de Faller é uma linha | Beast Balls em Olivine (design §5, pendente desde a M1). |
| Gancho da M4 | Stub "come back soon" em Olivine | Substituído pelo doc da Missão 4 (New Bark / Lusamine), que continua a var em 9+. |

**O que NÃO pode regredir numa evolução:** a máquina de estados §1.2, a
invariante flag ⇔ estado 7, os dois `setflag(FLAG_PICKED_*)` do trader (§3.1.1), a visibilidade por template, o SIM como único ponto
de saída, a escolha refeita a cada tentativa, o tratamento de todos os
resultados, a proibição de captura, os locais 20-24 no fim de `object_events`, e
a regra de que `VAR_TEMP_1` é do `Cherrygrove_FriendlyTrader`.

---

## 8. Dependências frágeis criadas por este plano

Coisas que não existem hoje e que uma evolução distraída quebra em silêncio:

- **Os 14 objetos de Cherrygrove passam a carregar `FLAG_EVENT_ULTRABEAST_CHERRYGROVE`.**
  Um `removeobject` em qualquer um deles **esvazia a cidade**. Vale para o Fisher,
  o Boy, a Lass, os quatro Corsola, os dois Staryu, o Aipom, a Little girl, o
  Zigzagoon e o Friendly Trader.
- **`FLAG_PICKED_ZIGZAGOON` e `FLAG_PICKED_RATTATA` deixam de ser setadas pelo
  `removeobject` e passam a depender de dois `setflag` explícitos** (§3.1.1).
  Apagar qualquer um dos dois torna o presente **repetível para sempre**, com
  build limpo e sem nenhum sintoma até alguém notar o farm. Esta é a dependência
  mais perigosa criada por esta missão, e a única que estraga conteúdo que já
  existia antes dela.
- **`FLAG_TEMP_3` e `FLAG_TEMP_4` viram flags de visibilidade em Cherrygrove.**
  Qualquer script novo no mapa que as use como flag de trabalho faz um dos dois
  presentes sumir ou reaparecer sozinho.
- **`VAR_TEMP_1` é `VAR_TEMP_TRANSFERRED_SPECIES`** (`vars.h:370`), do
  `Cherrygrove_FriendlyTrader`. Qualquer script novo em `CherrygroveCity` que use
  `VAR_TEMP_1` corrompe a troca — e vice-versa.
- **A ordem dos três blocos de `applymovement` em §4.2.** Kukui → jogador →
  Looker/Anabel. Mover o Looker antes do jogador o faz tentar descer para (27,8)
  ocupado.
- **`VAR_TEMP_3` depende de não haver recarga de mapa entre a escolha e o fim da
  cena.** Qualquer warp ou coisa que passe por `LoadMapFromWarp` entre o
  `dynmultichoice` e o `UBResolved` perde a escolha, e o Kukui narra a UB errada.
- **Objetos novos sempre no fim de `object_events`.** Inserir no meio renumera
  `LOCALID_CHERRYGROVE_SILVER` (13), `LOCALID_CHERRY_ZIGZAGOON` (16) e
  `LOCALID_CHERRY_RATTATA` (17), todos lidos por script.
- **O despachante `BriefingTalk` de Olivine agora serve três missões.** Um
  `goto_if_ge VAR_RIFT_MISSIONS_STATE, 6` sobrando em qualquer ramo de Looker ou
  Anabel engole os estados 7 e 8 — é exatamente a linha que esta missão remove.
  A checagem de `grep` está em §2.3.
- **O `ON_TRANSITION` de Cherrygrove é compartilhado** com
  `SetTimeBasedEncounters`. Quem mexer nele tem que preservar as duas linhas.

---

## 9. Pendências e riscos conhecidos

- **Retry custa uma caminhada de 20 tiles.** O blackout devolve o jogador ao
  Centro de Cherrygrove; a saída fica em (47,8) e o tile de conversa em (27,8).
  A linha y=8 é reta e livre de x=27 a x=49, sem obstáculo nem objeto, mas são 20
  passos. Nas M1 e M2 o Centro ficava a um passo da cena. **Aceito**: a praia é o
  local pedido pelo gancho da M2 e não há Centro mais perto. Se virar reclamação
  de playtest, a saída é encenar a missão mais a leste, não mudar heal location
  (ela é global e vale para toda a campanha).
- **O trio da troca (locais 15/16/17) some inteiro durante o incidente**, mas ao
  custo de mexer num evento que existia antes desta missão (§3.1.1). O risco não
  é a cidade ficar errada: é o presente virar repetível se o `setflag` explícito
  for esquecido ou removido numa evolução futura. A checagem barata está na
  lista de runtime de §10.
- **Comportamento antigo preservado de propósito:** pegar um dos dois presentes
  continua deixando o outro de pé na rua. É esquisito, é anterior a esta missão,
  e **não** é consertado aqui.
- **`ITEM_WEAKNESS_POLICY` num chefe de 4 barras é inédito no projeto.** Com
  Stakataka 4x fraco a Lutador e Terra, o gatilho é quase certo. É o parafuso nº 1
  da lista de redução de §4.4 justamente por isso.
- **Multiplicador 140 é o maior do repo** (a M2 já tinha estreado o primeiro
  acima de 110). Só o runtime decide se é ameaça ou parede.
- **Looker e Anabel em dois lugares no estado 7: aceito pelo autor** (mesma
  decisão da M1 e da M2). Eles continuam na casa de Olivine (sem flag) e também
  aparecem em Cherrygrove. Não esconder em Olivine.
- **UBs sobre água.** O padrão já existe no mapa (seis Pokémon de overworld
  parados em tiles de água), mas nenhum deles é 32x32. Só o runtime mostra se o
  sprite grande do Stakataka fica bem no tile de mar.
- Money loss no blackout/desistência é o padrão da engine; aceito pelo design
  (batalha de ameaça).
- **Beast Balls continuam pendentes** desde a M1 (design §5).

---

## 10. Teste em runtime

- [ ] Estado 6: entrar em Olivine House1 pela porta dispara a cena; Looker e Anabel dão o briefing da M3 e voltam ao lugar. Estado vira 7.
- [ ] Estado 6 entrando de outro jeito (sem a coreografia): falar com Looker **ou** com Anabel dá o mesmo briefing e o mesmo estado 7.
- [ ] Estados 3 e 5 continuam se comportando como antes (regressão das M1 e M2): a cena de chegada **não** dispara e o diálogo é "vá na frente".
- [ ] Estado 7: diálogo "vá na frente" em Olivine; Cherrygrove sem Fisher, Boy, Lass, os 4 Corsola, os 2 Staryu, o Aipom, a Little girl, o Zigzagoon **e o trio da troca inteiro — treinador, Zigzagoon de Galar e Rattata de Alola**; Centro, Mart, as três casas, o Darkrai Inn e o warp (29,21) acessíveis.
- [ ] Chegar por Route 29 e Route 30 e por Fly: elenco sempre presente, UBs sempre ausentes.
- [ ] Falar com Anabel e Kukui antes: falas curtas, nada muda; os dois voltam a olhar para baixo. "Não" com o Looker libera e não muda estado.
- [ ] Confirmar que **(27,8) é mesmo o único tile** de onde se fala com o Looker: tentar por (26,8), (28,8), (29,7) e pela linha y=7 dos dois lados.
- [ ] "Sim": Kukui desce, depois o jogador, depois Looker e Anabel. Nenhum ator sobreposto, ninguém andando sobre a água.
- [ ] O jogador consegue pisar na água rasa de x=25 (isso é normal e esperado), mas **não** consegue chegar a (24,9)/(24,10) a pé — e falar com o Looker de lá continua impossível.
- [ ] Tremor + flash + as duas UBs aparecendo em (24,9)/(24,10) **sobre o mar**; os dois gritos tocam; o sprite 32x32 do Stakataka não fica cortado nem sobre o tile errado.
- [ ] Menu da escolha não fecha com B.
- [ ] Escolher Blacephalon: boss com **4 barras**, nível 85, Calm Mind cedo, Wise Glasses no bolso. Kukui fala do Stakataka depois. Idem invertido (Stakataka, Trick Room no primeiro turno, Weakness Policy disparando com golpe Lutador/Terra).
- [ ] Bolsa: bola bloqueada nas duas. "Run": desistência → blackout.
- [ ] Perder de propósito: acorda no Centro de **Cherrygrove**; cidade ainda vazia, elenco no lugar, UBs ausentes; caminhar de volta pela linha y=8 sem obstáculo; Looker recomeça e a escolha pode ser outra.
- [ ] Vencer: UBs somem, Looker e Anabel descem sem sobrepor ninguém, Kukui vira para o leste e encara o jogador, gancho de New Bark/Lusamine, fade, cidade repovoada, elenco ausente, follower de volta.
- [ ] Estado 8: stub da Missão 4 em Olivine, com Looker e Anabel; reentrar em Cherrygrove não traz o elenco nem as UBs de volta.
- [ ] `Cherrygrove_FriendlyTrader` continua funcionando depois do evento (é o script do mapa que usa `VAR_TEMP_1`).
- [ ] **Checagem de espaço do trader** (§12.3 item 5), com 6 na party: com vaga no PC, a oferta aparece normalmente e o Pokémon vai para a caixa (com a fala de "sent to PC"); com **o PC também cheio**, o trader dá a fala de "sem espaço" e **a oferta nem chega a aparecer** — e, ao abrir espaço e voltar, o presente continua disponível (nenhuma `FLAG_PICKED_*` foi setada).
- [ ] **Regressão do presente, num save que ainda não pegou nenhum** (§3.1.1), nesta ordem:
  1. Antes do estado 7: os três estão na rua; pegar o Zigzagoon. Ele some, o Rattata **continua** de pé, o trader passa a dizer "Has my Pokémon been helpful?".
  2. Sair do mapa e voltar: o Zigzagoon **não** volta. Salvar, recarregar, voltar: continua sem voltar. *(É isto que prova que o `setflag(FLAG_PICKED_ZIGZAGOON)` explícito está lá; sem ele o presente volta e vira farm infinito.)*
  3. Idem para o Rattata, em outro save.
- [ ] Num save que **já** pegou um presente: durante o estado 7 o outro também some, e depois do estado 8 ele volta — e só ele.
- [ ] O tour do Guide Gent e a cena do Silver continuam mortos no pós-E4 (`VAR_CHERRYGROVE_CITY_STATE == 4`).
- [ ] Salvar/recarregar em cada estado (6, 7, 8) mantém tudo acima.
- [ ] Regressão: `FLAG_EVENT_ULTRABEAST_BLACKTHORN` e `FLAG_EVENT_ULTRABEAST_MAHOGANY` continuam limpas e as duas cidades continuam povoadas em todos os estados ≥ 6.

---

## 11. O que este doc copiou das M1/M2 (e o que fez diferente)

**Copiado:** a tabela de temporários por mapa, a planta ASCII tirada da colisão
real com o caminho de cada ator em coordenadas, a tabela de resultados de
batalha, o padrão "bolso de parede" para o tile de conversa, o `warpsilent` no
lugar sob fade, a tabela "esqueleto × evolução", a regra de que todo bloco
termina em `end`, e a conferência dos gatilhos herdados do mapa antes de esconder
os objetos que eles referenciam.

**Diferente, de propósito:**

1. **O elenco olha para baixo** (`FACE_DOWN`), porque está encostado na parede
   norte. M1 e M2 usavam `FACE_UP`. Copiar por hábito deixa o elenco de costas.
2. **O `ON_TRANSITION` já existia** e é compartilhado com
   `SetTimeBasedEncounters`: aqui se acrescenta um `call`, não um map script.
3. **A seção `// MAP_CHERRYGROVE_CITY` já existe** em `map_event_ids.h`: os
   locais novos entram nela, sem cabeçalho novo.
4. **Três atores de elenco, não quatro**: Kukui não tem parceiro fora da Poké
   Ball, porque o design §3.2 só exige isso de Lillie e Gladion.
5. **As UBs ficam sobre a água.** Primeira missão em que a ruptura não abre em
   terra firme.
6. **O Centro fica longe** (20 tiles), ao contrário das duas primeiras missões.
   O custo do retry está registrado em §9 em vez de ser escondido.
7. **A escala não sobe em barras** (já estavam no teto na M2): sobe em nível,
   multiplicador e, principalmente, num golpe de controle por chefe.
8. **A ordem de redução de dificuldade começa pelo item**, não pelo
   multiplicador, porque `ITEM_WEAKNESS_POLICY` é o parafuso de maior variância.
9. **Primeira missão que precisa mexer num evento alheio.** Para esvaziar a
   cidade de verdade foi preciso trocar o mecanismo de visibilidade dos dois
   presentes do Friendly Trader pelo padrão `FLAG_HIDE_CIANWOOD_GLADION` (flag
   burra no template, verdade persistente recalculada no load) e tornar
   explícito um `setflag` que hoje só acontece por efeito colateral do
   `removeobject`. M1 e M2 nunca tocaram em conteúdo pré-existente.
10. **A planta foi lida duas vezes:** colisão (`dump_mapa.py`) **e** comportamento
   de metatile. Blackthorn e Mahogany eram cenas de rua, onde o bit de colisão
   conta a história inteira. Numa orla ele não conta: metade da praia tem colisão
   0 e é água. O primeiro rascunho desta planta tratou a coluna x=25 como
   barreira e estava errado. **A Missão 4 (New Bark, que também tem costa) deve
   repetir a leitura dupla.**

---

## 12. Feedback da implementação (20/09/2026)

Seção escrita **depois** de implementar, conforme a skill `evento-esqueleto` §6.
Serve para o próximo agente saber o que é fato verificado no checkout e o que
continua sendo aposta.

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
