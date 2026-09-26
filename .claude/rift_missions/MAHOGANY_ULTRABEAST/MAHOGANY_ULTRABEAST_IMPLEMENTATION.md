# Mahogany — Necrozma, Xurkitree + Celesteela (Rift Mission 2) — implementação

**Status:** **roteiro V3 aplicado (revisão 6)** — 25/09/2026. Build limpo
(`make -j$(nproc)`). Runtime pendente: checklist em §16.10. As tabelas
*pedido → como ficou* estão em §13 (rev. 3), §14 (rev. 4) e **§16.6 (rev. 6)**.
Revisão 6 — 25/09/2026 (rev. 1: plano; rev. 2: esqueleto + §12; rev. 3: a
história; rev. 4: a voz da Lillie e a plaquinha; rev. 5: os clarões; rev. 6: o
roteiro V3 inteiro, com o mapa alargado e a barreira de gelo de verdade).
**§16 SUBSTITUI §1.1, §1.3, §3.2, §3.3, §3.4, §4.2–§4.5 e §5.** Onde houver
conflito, vale §16: a rua tem cinco linhas, o elenco mudou de tile, a parede de
gelo existe como metatile e há quatro flags persistentes novas.
**Roteiro da cena (falas e movimentos):** [`MAHOGANY_ULTRABEAST_SCRIPT_V2.md`](MAHOGANY_ULTRABEAST_SCRIPT_V2.md)
(V3, 25/09/2026; o [`_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md) anterior é histórico)
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §6 (regras comuns) e §6.2.
**Missão anterior:** [`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](../BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md)
— este doc **continua** a máquina de estados dela; a M1 revisão 3 é o modelo da
história (§5–§7 e §13 daquele doc).

Escopo: do gancho final de Blackthorn (o jogador volta a Olivine) até o fim do
incidente de Mahogany, terminando com o gancho **sem destino** que manda o
jogador de volta a Olivine. A Missão 3 (Cherrygrove) é revelada no briefing dela.

**A história em três linhas (rev. 6).** Mahogany está sem energia e a Lillie
vem observando duas Ultra Beasts da janela do Ginásio: ela viu uma luz correr de
uma até a outra e propõe afastá-las. O plano é testado e **não basta** — a UB
distante manda a própria carga pelo elo e a que caiu se reergue, perdendo brilho
quem enviou. Ela corrige a hipótese na hora e pede ao Pryce uma parede de gelo
atravessada **no trajeto**; funciona, e a segunda luta é para valer. O Necrozma
então alcança as duas por cima do gelo e as recolhe — mas a Anabel continua com
as duas assinaturas depois da absorção, e é essa a primeira razão concreta para
acreditar que as UBs ainda podem ser recuperadas. O Pryce vai buscar a lâmpada
do Hector; a Lillie fica até os moradores voltarem.

**Decisões desta missão:**
- Elenco: **Looker, Anabel, Lillie (+ Alolan Ninetales), Pryce (+ Mamoswine)**,
  dois moradores (velho + menino) e o **Necrozma**.
- Local: `Mahoganytown`, rua sul, entre o Pokémon Center e o Ginásio, **alargada
  em duas linhas** para esta missão (§16.1): `y=20..24`, `x=6..26`.
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

`OlivineCity_House1_EventScript_Looker` e `..._EventScript_Anabel` (`lock`,
`faceplayer`) passam a ramificar:

| Estado | Looker | Anabel |
|---|---|---|
| 0-1 | `Text_LookerHoliday` | `Text_AnabelHoliday` |
| 2 | `call ..._BriefingTalk` → M1 | idem |
| 3 | `Text_LookerGoAhead` | `Text_AnabelGoAhead` |
| **4** | `call ..._BriefingTalk` → **M2** | idem |
| **5** | **Novo** `Text_LookerGoAheadM2` | **Novo** `Text_AnabelGoAheadM2` |
| **≥ 6** | stub da Missão 3 | stub da Missão 3 |

O estado 4 substitui `..._EventScript_LookerMission2` / `..._AnabelMission2` e os
textos `..._Text_LookerMission2Stub` / `..._Text_AnabelMission2Stub`, que são
**apagados**.

Ordem dos `goto_if_eq`: 2, 3, 4, 5, depois `goto_if_ge ... 6`, e o `msgbox` de
férias como default. **Não** deixar nenhum `goto_if_ge ... 4` sobrando do código
atual: ele engoliria os estados 5 e 6.

Todos os ramos continuam terminando em `OlivineCity_House1_EventScript_ReleaseEnd`.

O texto do briefing (`Text_BriefingM2`) e os dois "vá na frente" estão em
[`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md), "Ato 1". Restrição que o texto precisa respeitar: cita a ligação do Pryce e
o apagão, **e mais nada** — a Lillie, a evacuação e o Necrozma são o que o
jogador encontra em Mahogany.

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

| Objeto | Script | Nota técnica |
|---|---|---|
| Anabel | `UBAnabel` | `faceplayer`. |
| Lillie | `UBLillie` | `faceplayer`, e `turnobject DIR_NORTH` no fim para ela voltar a olhar a rua. Quatro ramos de família Cosmog (Cosmog / Cosmoem / lendária / nenhum), com "!" na Ninetales antes. |
| Pryce | `UBPryce` | **Sem** `faceplayer`: está evacuando. Só alcançável de (12,20). Ramo extra com família Cosmog. |
| Mamoswine | `UBMamoswine` | `playmoncry` + narração. |
| Velho | `UBOldMan` | `turnobject DIR_EAST` no fim (volta a discutir com o Pryce). |
| Menino | `UBBoy` | `turnobject DIR_NORTH` no fim (volta a olhar o avô). |

Nenhuma muda estado. Os textos estão em [`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md), "Ato 2".

---

## 4. Etapa C — A cena (100% scriptada a partir do SIM)

### 4.1 Pré-checagens (`Mahoganytown_EventScript_UBLooker`)

`UBLookerGreet` → `UBLillieTheory` → `UBReady` (SIM/NÃO). Nenhum estado muda
antes do SIM; **sem presente, logo sem checagem de espaço** (diferente da M1).

A leitura da Lillie vem **antes** do SIM de propósito: ela tem de ter contado ao
grupo o que viu antes de alguém se mexer (design §3.2). O que ela ainda **não**
sabe — que manter as duas separadas não basta — é o que a cena ensina.

Falas: [`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md), "Ato 3".

### 4.2 A cena (`Mahoganytown_EventScript_UBScene`)

**A cena inteira — beats, movimentos e falas — está em [`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md), "Ato 4".** Aqui só o
que a implementação precisa garantir:

- `lockall` + `hidefollower` na primeira linha.
- **A ordem dos três blocos de aproximação é load-bearing:** Lillie/Ninetales →
  jogador → Looker/Anabel. A Ninetales passa por (17,22), tile final do jogador;
  Looker e Anabel só sobem depois que o jogador desocupa (21,21).
- A evacuação acontece **na tela**: `opendoor`/`closedoor` em (10,19), velho e
  menino saem **em sequência** (o menino pisa no tile que o velho deixa) e são
  removidos sob `FLAG_TEMP_3`.
- Necrozma entra por `addobject` em (11,21), o tile que o Mamoswine acabou de
  largar, sob `FLAG_TEMP_4`; as duas UBs sob `FLAG_TEMP_2`, uma de cada lado dele.
- A carga da Celesteela pela linha 22 para **dois tiles antes** do jogador; a
  linha está vazia porque Mamoswine e Ninetales estão na 21.
- Cada par que anda junto tem caminhos disjuntos passo a passo.
- Flash = `fadescreenswapbuffers`, nunca `fadescreen` (§15).

### 4.3 A escolha

`dynmultichoice ... TRUE ...` (sem cancelar), resultado em `VAR_TEMP_3`
(0 = Xurkitree, 1 = Celesteela), "!" sobre a escolhida. **Vale para as duas
rodadas**; depois de um blackout o jogador escolhe de novo.

Nenhum `turnobject` é preciso: jogador (17,22), Lillie (16,21) e Ninetales
(15,21) estão a leste das duas UBs em x=12, que olham para o leste.

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

Coreografia e falas: [`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md), "Ato 6".

Contrato técnico desta etapa:

- A fala da Lillie muda conforme a escolha; a luta dela é **narrativa** e resolve
  junto com a vitória do jogador.
- As duas UBs são removidas sob a flag delas (`FLAG_TEMP_2`); o Necrozma sob
  **flag própria** (`FLAG_TEMP_4`), para não encostar na flag do elenco.
- **Ninguém o nomeia.** Looker e Anabel: "the creature from Blackthorn". Pryce
  nunca o viu. A Lillie **reconhece** (continuidade USUM) e se recusa a falar na
  rua — o mesmo corte do Gladion em Blackthorn. O nome fica para a reunião de Olivine.

### 5.2 Reação opcional à família Cosmog (`UBNecrozmaSensesCosmog`)

Idêntica em mecânica à M1 §6.6: `CheckMysteryEggPokemon` → `VAR_TEMP_4`, checado
**depois** das batalhas (elas podem evoluir o Pokémon). O passo do Necrozma em
direção ao jogador, (11,21)→(12,21), cai no vão onde a parede de gelo esteve —
livre, ninguém fica nele. `VAR_TEMP_4` é lida de novo na conversa final, que
ganha um bloco extra.

Pré-cena, sem estado: a Lillie tem uma fala por estágio da família Cosmog e o
Pryce mais uma (§3.5). Falas: [`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md).

### 5.3 Conversa, Pryce volta ao Ginásio, gancho

**Coreografia e falas:** [`MAHOGANY_ULTRABEAST_SCRIPT.md`](MAHOGANY_ULTRABEAST_SCRIPT.md), "Ato 7".

Ordem técnica:

1. `UBAftermath`; bloco Cosmog/lendária se `VAR_TEMP_4` ≠ `SPECIES_NONE` (§5.2).
2. **Pryce volta para o seu povo** (pedido do autor): `opendoor 10,19` → Pryce
   (14,20)→(10,19), `removeobject`; **depois** o Mamoswine (13,21)→(10,19),
   `removeobject`; `closedoor`. **Sequencial**: os dois últimos tiles do Mamoswine
   são os do Pryce. A flag deles é `FLAG_TEMP_5`, então `removeobject` é inofensivo.
3. `UBHook` — gancho **sem destino**; a Missão 3 só é revelada no briefing seguinte.
4. `FADE_TO_BLACK` → `clearflag FLAG_EVENT_ULTRABEAST_MAHOGANY` + `setvar
   VAR_RIFT_MISSIONS_STATE, 6` → `warpsilent MAP_MAHOGANYTOWN, 17, 22` →
   `waitstate` → `releaseall` → `end`. A cidade repovoa, o elenco some, as portas
   destrancam e o warp desfaz o `hidefollower`.

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

Revisão 4 acrescenta a plaquinha com o nome do falante, que é **de motor** e
vale para o jogo inteiro (skill `nomear-falante`):

| Arquivo | Rev. 4 |
|---|---|
| `include/constants/speaker_names.h` | elenco das Rift Missions no enum (`SP_NAME_LOOKER` … `SP_NAME_LUSAMINE`) |
| `src/data/speaker_names.h` | o texto de cada plaquinha; `MOM` virou `Mom` |
| `charmap.txt` | `NAME_LOOKER` … `NAME_LUSAMINE`, para escrever `{SPEAKER NAME_X}` |
| `src/field_name_box.c` | `TrySetSpeakerFromMessage` (plaquinha decidida antes de a caixa subir, e **limpa** quando a mensagem não diz falante), `IsNameboxShowingSpeaker`, `SetSpeakerNameForNextMessage` |
| `src/field_message_box.c` | chama o pré-scan nas duas entradas de mensagem |
| `src/text.c` | não redesenha a plaquinha quando o falante não mudou |
| `src/string_util.c` | `GetExtCtrlCodeLength(EXT_CTRL_CODE_SPEAKER)` era 1 e virou 2 (o código tem 1 byte de argumento) |
| `src/battle_setup.c` | fala de entrada de treinador passa por `SetSpeakerNameForNextMessage` |
| `data/maps/Mahoganytown/scripts.inc` | 89 falas com `{SPEAKER NAME_X}` no lugar do prefixo `"Nome: "` |
| + 12 arquivos de mapa dos eventos anteriores | mesma conversão (§14) |

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
destino e ninguém nomeando o Necrozma. **(Rev. 4)** A Lillie nunca prevê nada:
ela relata, duvida e erra; qualquer fala que a faça soar como quem sabia o que
ia acontecer pertence à Anabel e aos instrumentos dela. E a ordem dos falantes
em `speaker_names.h`/`charmap.txt` nunca muda — reordenar troca o nome de toda
fala já escrita, com build limpo.

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

Revisão 4:

- [ ] A plaquinha aparece **junto** com a caixa (não entra depois, com um pulo) e some ao fechar.
- [ ] Em `UBLillieTheory`, `UBNecrozmaArrives`, `UBAftermath` e `UBHook` a plaquinha troca de nome na página certa e **não** fica pendurada sobre narração.
- [ ] Narração pura (`UBRevived*`, `UBWallHolds`, `UBSynergy`, `UBNecrozmaSenses*`) começa **sem** plaquinha.
- [ ] Nenhuma fala ainda mostra `"Nome: "` dentro da caixa.
- [ ] Regressão da plaquinha de treinador: fala de entrada de um treinador comum ainda mostra o nome dele.
- [ ] Regressão do Match Call: a plaquinha do telefone continua com a paleta do Pokénav.
- [ ] A Lillie, na leitura dela, soa como quem observou e pode estar errada; ninguém anuncia a luz antes de ela chegar.

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

---

## 14. Revisão 4 — a voz da Lillie e a plaquinha do falante (22/09/2026)

Segundo retorno do autor sobre a cena, depois de jogar a revisão 3. Feito com
as skills `evoluir-historia-de-evento` e `nomear-falante` (esta última **criada
nesta revisão**, §14.2).

### 14.1 Pedido → como ficou

| Pedido | Como ficou |
|---|---|
| "Ficou muito melhor!" | Arco, coreografia, batalhas, absorção e gancho da rev. 3 **intocados**. Só falas mudaram. |
| A Lillie fala como se soubesse que tudo isso ia acontecer | Era literal no texto: **ela era o relógio da cena**. Dizia "First there's a light. Then the tear. Then them." (previa o Necrozma), "tonight's hour is soon", "Mr. Pryce! It's almost time!" e "There! The light! Here it comes!". Tudo isso saiu dela. |
| Ela tem experiência com isso, mas deveria ser inesperado | A **experiência ficou e ganhou peso**: reconhece as UBs à primeira vista ("I knew what they were the moment I saw them") e reconhece a luz do Necrozma. O **inesperado virou explícito**: "I was never supposed to see one again", "two days and I still don't understand any of it", e, na chegada do Necrozma, "It has no business being anywhere near this town." |
| Reescreve os diálogos dela | 9 blocos reescritos: `UBLillieIdle`, `UBLillieTheory`, `UBNotReady`, `UBTimeIsClose` (era `UBLillieWarnsPryce`), `UBLightComing`, `UBNecrozmaArrives`, `UBSynergy`, `UBChoosePrompt`, `UBAftermath`, mais o ajuste de vocabulário em `UBLilliePlan` ("splitting" → "keeping them apart"). |
| — (decorrência) | **O relógio passou para a Anabel**, que já tinha instrumentos e é quem deve medir. A Lillie chama o Pryce pelo morador, não pela hora. E **ninguém anuncia a luz**: a Anabel vê o instrumento sair do que ela conhece, o Pryce vê a luz na rua. |
| Nome de quem fala acima da caixa, como em luta de treinador | Feito, §14.2. 89 falas em Mahogany. |
| Nos eventos anteriores também (Gladion, Lillie, Kukui, Looker, Anabel) | Feito: **13 arquivos de mapa, 380 falas**. Lista em §14.3. |
| Transformar isso numa skill | `.claude/skills/nomear-falante/` — SKILL.md + 3 ferramentas. |
| Simplificar o código para ter um jeito fácil | §14.2: a regra virou "cada mensagem diz quem fala"; escrever `{SPEAKER NAME_X}` no começo do texto é tudo. |

**Ambiguidade resolvida por escrito:** "ela tem experiência" × "deveria ser
inesperado" não é contradição — são dois eixos. Ela sabe **o que** são (Ultra
Beasts, e a luz), e não sabe **por que estão aqui** nem o que vai acontecer.
A cena inteira passou a apoiar essa divisão, e a regra ficou escrita no
cabeçalho de vozes de `scripts.inc`.

### 14.2 A plaquinha: o que existia e o que foi feito

O motor já tinha a peça (`src/field_name_box.c`, `EXT_CTRL_CODE_SPEAKER`,
`gSpeakerNamesTable`), usada só pela fala de entrada de treinador
(`OW_NAME_BOX_NPC_TRAINER`), e **sem uma única ocorrência em texto de mapa**.
O que faltava para ela ser usável em diálogo de cena:

1. **A plaquinha entrava depois da caixa.** O nome só era lido quando o
   renderizador chegava no código, e a caixa já tinha subido. `TrySetSpeakerFromMessage`
   lê um `{SPEAKER ...}` que venha antes da primeira letra, **antes** de montar
   a caixa.
2. **Narração herdava o nome da fala anterior.** Agora uma mensagem que não diz
   falante **limpa** a plaquinha. Isso é o que torna a escrita simples: só se
   marca quem fala, nunca o silêncio — e narração em `msgbox` próprio não pede
   nada. (O único caso que ainda pede `{SPEAKER NAME_NONE}` é narração **dentro**
   de uma fala, na mesma mensagem.)
3. **Quem define o falante de fora do texto** (`setspeaker`, treinador) passou
   por `SetSpeakerNameForNextMessage`, que arma o nome para uma mensagem — sem
   isso, a limpeza do item 2 apagaria a plaquinha do treinador.
4. **Página nova do mesmo falante repintava a janela** (e o quadro da caixa).
   `IsNameboxShowingSpeaker` corta isso.
5. **Bug de motor corrigido:** `GetExtCtrlCodeLength(EXT_CTRL_CODE_SPEAKER)`
   valia 1 e o código tem 1 byte de argumento; `SkipExtCtrlCode` parava em cima
   do argumento e o lia como texto. Latente enquanto ninguém usava o código.

Resultado para quem escreve: **`{SPEAKER NAME_LILLIE}` no começo da fala, e só.**

### 14.3 Conversão dos eventos anteriores

`aplicar_falante.py` troca `"Nome: "` pelo código **sem reencaixar o
parágrafo** — as quebras de linha do autor são batidas de cena, e o código não
ocupa pixel, então a linha só encurta.

| Arquivo | Falas |
|---|---|
| `data/maps/Mahoganytown/scripts.inc` | 89 |
| `data/maps/OlivineCity_House1/scripts.pory` | 63 |
| `data/maps/BlackthornCity/scripts.inc` | 44 |
| `data/maps/CherrygroveCity/scripts.pory` | 31 |
| `data/maps/DragonsDen_Shrine/scripts.inc` | 29 |
| `data/maps/NewBarkTown/scripts.pory` | 49 |
| `data/maps/Route30_MrPokemonsHouse/scripts.pory` | 28 |
| `data/maps/GoldenrodCity_FlowerShop/scripts.pory` | 28 |
| `data/maps/ReceptionGate/scripts.inc` | 14 |
| `data/maps/CianwoodCity/scripts.inc` | 9 |
| `data/maps/VioletCity_PokemonCenter/scripts.pory` | 6 |
| `data/maps/BattleFrontier_BattleTowerBattleRoom/scripts.pory` | 3 |
| `data/maps/DragonsDen_Cavern/scripts.pory` | 1 |

Elenco na tabela: Looker, Anabel, Lillie, Gladion, Kukui, Pryce, Clair, Old man,
Elm, Lusamine, mais Mom e Player que já existiam.

**O defeito que quase passou, e que a skill agora manda procurar:** um `"Elm: "`
no meio de um bloco do Looker e oito `"Lusamine: "` em blocos de New Bark
ficariam com a **plaquinha do falante errado** — build limpo, texto certo no
arquivo, nome errado na tela. Encontrados varrendo prefixos restantes dentro de
blocos já convertidos. `"Type: Null"` é falso positivo dessa varredura.

### 14.4 Conferido

- `make -j$(nproc)` limpo. ROM 92,69%, EWRAM 94,28%, IWRAM 73,77%.
- `checar_falantes.py`: enum, tabela e `charmap.txt` batem índice por índice;
  todo `{SPEAKER NAME_X}` usado existe; nenhum prefixo `"Nome: "` sobrando.
- `medir_linha.py`: nenhuma linha passa de 208 px em nenhum arquivo tocado.
- Os `.inc` gerados a partir de `.pory` carregam os códigos (poryscript repassa).
- Estado, flags, invariantes, coreografia, batalhas e ponto de saída: **sem
  nenhuma mudança** de valor em relação à revisão 3. A única mudança de script
  foi o rótulo `UBLillieWarnsPryce` → `UBTimeIsClose` (um `msgbox`).

**Runtime:** pendente — §10, agora com os sete itens da plaquinha.

## 15. Revisão 5 — escurecimento dos flashes e o reencontro da Lillie (23/09/2026)

Feedback do autor depois de jogar: *"quando as Ultra Beasts aparecem é para
ficar mais escuro e é legal, mas fica impossivelmente escuro"*. Vale para as
quatro missões; corrigido nas quatro de uma vez.

### 15.1 A causa

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

### 15.2 A correção

Todo `fadescreen` **de dentro da cena** virou `fadescreenswapbuffers`, que faz o
mesmo efeito com BLDY no hardware (`FadeScreenHardware`) e não encosta nas
paletas. O `FADE_FROM_*` reseta os registradores de blend no fim
(`shouldResetBlendRegisters`), então não sobra estado.

Continuam com `fadescreen FADE_TO_BLACK` **só** os dois pontos em que um warp
recarrega o mapa logo depois e as paletas são refeitas do zero:
`UBUnresolved` (retry depois do blackout) e `UBHook` (recarga em lugar com
o incidente encerrado). O par `FADE_TO_BLACK`/`FADE_FROM_BLACK` da cura da
Anabel entre as duas rodadas fica **dentro** da cena, sem recarga de mapa, e
também virou `fadescreenswapbuffers`.

O padrão já era o recomendado em `.claude/skills/visibilidade-e-gatilhos`
(§ do `addobject` sob fade) e é o que o macro `bosslegendaryencounter` usa em
`asm/macros/event.inc`. A receita de flash da skill
`evoluir-historia-de-evento` §6 estava errada e foi corrigida junto.

**Conferido:** `make -j$(nproc)` limpo. **Runtime pendente** — o teste é entrar
na cena **à noite** e conferir que a quarta ruptura está tão clara quanto a
primeira.

### 15.3 A fala de reencontro da Lillie (pedido do mesmo dia)

Feedback do autor: *"a Lillie no diálogo pré-luta fala uma fala totalmente
desconectada e bizarra, sobre Johto"*.

Era o `UBLillieIdle`, que abria assim:

> {PLAYER}?! / You're the Champion they've been waiting for? / …Of course you
> are. Who else would it be? / **I came to Johto to see it. That's all. Just to
> see it.**

Dois problemas, e o segundo é o que soa bizarro:

1. **"it" não tem antecedente.** A intenção registrada era "veio ver Johto por
   conta própria"; o que saiu foi uma frase que aponta para nada.
2. **Ela está explicando ao jogador que veio para Johto — e o jogador esteve com
   ela em Johto três vezes.** Route 30 (primeira batalha), Goldenrod (a
   SquirtBottle, a segunda batalha, "we've traveled some of the same roads") e
   Dragon's Den ("thank you, {PLAYER}"). A caixa tratava um reencontro como uma
   apresentação.

Reescrita como reencontro. O que **entrou**: ela reconhece o jogador na hora; o
Looker anunciou "o Campeão" sem dizer quem era; ela parou em Mahogany por uma
noite e a Ninetales gosta do frio (motivo concreto para estar ali, e observação,
não previsão). O que **ficou intacto**: as luzes apagando, ter reconhecido as
Ultra Beasts à primeira vista, "I was never supposed to see one again", dois dias
de anotações sem entender nada, e mandar falar com o Looker.

O que **continua fora**: a Lusamine. A primeira aparição dela no arco é a M4
(New Bark, §2 daquele doc: *"a Lusamine não é mencionada em lugar nenhum"*),
então a Lillie não diz com quem viaja. E a regra de voz da rev. 4 vale: nenhuma
previsão em nenhuma das linhas novas.

Nada de estado mudou — é uma caixa de texto. `medir_linha.py` sem linha acima de
208 px e `checar_falantes.py` com os 13 falantes em ordem.

**Não mexido, mas anotado:** o `UBLookerGreet` ainda apresenta a Lillie ao
jogador ("That is a young lady with a notebook"). Funciona, porque o Looker não
sabe que os dois se conhecem, mas se o autor quiser fechar o laço, o lugar é uma
frase da Lillie dizendo isso a ele.
---

## 16. Revisão 6 — o roteiro V3 aplicado (25/09/2026)

**Fonte:** [`MAHOGANY_ULTRABEAST_SCRIPT_V2.md`](MAHOGANY_ULTRABEAST_SCRIPT_V2.md)
(roteiro revisado V3, 25/09/2026) e
[`SOULGOLD_RIFT_ARCO_NARRATIVO.md`](../SOULGOLD_RIFT_ARCO_NARRATIVO.md) §7.
Esta seção **substitui** §1.1, §1.3, §3.2, §3.3, §3.4, §4.2–§4.5 e §5 acima:
onde houver conflito, vale o que está aqui.

### 16.0 Três decisões de escopo perguntadas ao autor antes de escrever

| Pergunta | Resposta | Consequência |
| --- | --- | --- |
| §3 proíbe a faixa comprimida. Alargar, remanejar ou reencenar? | **Alargar a rua sul em duas linhas** | `map.bin` editado: `y=23` e `y=24` viram rua |
| §2.3 pede plaquinha `NARRATOR`/`NOTE`/`SYSTEM` | **Sem plaquinha na narração** | o motor já não herda o nome anterior; entraram só `HECTOR` e `BOY` |
| §9 exige um ponto de alimentação real | **Trocar a fala para as lâmpadas da rua** | zero arte nova; "power lines" virou "street lamps" |

### 16.1 O mapa foi alargado

`data/layouts/Mahoganytown/map.bin`, colunas `x=4..27`: a faixa sul desceu dois
tiles (`y=23→25`, `y=24→26`, `y=25→27`) e as duas linhas liberadas viraram rua,
repetindo a linha do meio do canteiro de areia (`0xDB`/`0xDC`/`0xDD`) com a
borda de baixo (`0xE3`/`0xE4`/`0xE5`) em `y=24`. A cerca e o morro ficaram em
`y=25`/`y=26`, e a altura 28 do layout comporta isso exatamente.

Resultado: a rua passou de **3 para 5 linhas** (`y=20..24`, `x=6..26`). É a
dependência que o roteiro cobrava, e sem ela nada do resto cabe: duas UBs de
32×32, Necrozma, Mamoswine, quatro treinadores e uma parede não entram em três
linhas sem se encavalar.

Nada mais do mapa mudou: warps, conexões (Route 42/43/44), `HEAL_LOCATION`
(21,20) e a área leste estão intactos.

### 16.2 A barreira de gelo é de verdade

Quatro metatiles novos no fim do secundário `gTileset_MahoganyTown`
(tiles livres 281–296, paleta 12, desenho na camada do **meio**, então os
sprites passam na frente):

| Rótulo | ID |
| --- | --- |
| `METATILE_MahoganyTown_IceWall_Left` | `0x53E` |
| `METATILE_MahoganyTown_IceWall_Middle` | `0x53F` |
| `METATILE_MahoganyTown_IceWall_Right` | `0x540` |
| `METATILE_MahoganyTown_IceWall_Broken` | `0x541` |

A parede ocupa `(14,22) (15,22) (16,22)`, atravessada no fluxo que desce a
coluna 15 entre Xurkitree `(15,20)` e Celesteela `(15,24)`. É pintada com
`setmetatile ... TRUE` (intransponível para o jogador), rompida no meio no
retry e apagada para areia lisa (`0xDC`) quando o Pryce manda abrir passagem.
Nenhum objeto foi gasto nela e nenhum movimento roteirizado a atravessa.

### 16.3 Três áreas, duas câmeras

| Área | Quem | Tiles |
| --- | --- | --- |
| Abrigo | Hector, neto, Pryce, Mamoswine, depois Looker | `x=9..12` |
| Rua | Xurkitree norte `y=20`, Celesteela sul `y=24`, Necrozma e a fenda a oeste | `x=7..16` |
| Apoio | jogador, Lillie/Ninetales, Anabel, porta do Centro | `x=17..21` |

A cena usa `special SpawnCameraObject` com dois enquadramentos: **(13,22)** na
evacuação e **(14,22)** no confronto. A conta que decide as duas: a tela tem
15×10 metatiles com o tile da câmera na coluna 7, linha 4, e a caixa de
diálogo cobre as **três linhas de baixo**. Com a câmera em `y=22` essas três
linhas são `y=25..27`, a faixa de rocha ao sul da cidade — ou seja, **ninguém
fica atrás da caixa** e a frente sul em `y=24` continua visível. É por isso
que os dois enquadramentos estão na linha 22 e não na 21.

### 16.4 Elenco no `map.json`

| Objeto | Tile | Flag |
| --- | --- | --- |
| Hector (`OLD_MAN`) | (9,20) | `FLAG_TEMP_3` |
| neto (`BOY`) | (9,21) | `FLAG_TEMP_3` |
| Pryce | (11,20) | `FLAG_TEMP_5` |
| Mamoswine | (12,22) | `FLAG_TEMP_5` |
| Anabel | (19,20) | `FLAG_TEMP_1` |
| Looker | (20,20) | `FLAG_TEMP_1` |
| Ninetales | (19,21) | `FLAG_TEMP_8` |
| Lillie | (20,21) | `FLAG_TEMP_8` |
| Xurkitree | (15,20) | `FLAG_TEMP_2` |
| Celesteela | (15,24) | `FLAG_TEMP_2` |
| Necrozma | (8,22) | `FLAG_TEMP_4` |
| fenda (`OBJ_EVENT_GFX_ALTAR_RIFT`) | (7,22) | `FLAG_TEMP_6` |
| Cosmog / Cosmoem / Solgaleo / Lunala | (17,23) | `FLAG_TEMP_7` |

Duas medidas que o build não confere e que custaram um reposicionamento cada:

- **Mamoswine saiu de (11,21).** Sprite de 32×32 em cima do Pryce (11,20):
  ele sumia por completo. Foi para (12,22).
- **O parceiro saiu de (18,23).** Ali ele, o jogador (18,22), a Lillie (19,22)
  e a Ninetales (19,23) viravam uma mancha só. Foi para (17,23), duas colunas
  livres da Ninetales, à frente do gelo.

Âncoras separadas não bastam: **o tamanho do sprite é que decide.**

`FLAG_TEMP_8` é novo e existe por um motivo: a Lillie e a Ninetales são as
únicas duas que **continuam na rua depois da missão**, então não podem dividir
a flag do resto do elenco.

Orçamento no momento mais cheio (parceiro fora da Ball, antes de o Necrozma
sair): jogador + follower escondido + Lillie + Ninetales + Looker + Anabel +
Pryce + Mamoswine + Xurkitree + Celesteela + Necrozma + fenda + parceiro =
**13/16**. Hector e o neto já saíram antes disso.

### 16.5 Estado persistente novo (bloco `CUSTOM_FLAGS`)

| Flag | Valor | Significa |
| --- | --- | --- |
| `FLAG_MAHOGANY_UB_ENGAGED` | `0x104A` | as apresentações já aconteceram; blackout volta como retry |
| `FLAG_MAHOGANY_UB_SAW_RECHARGE` | `0x104B` | o grupo já viu a recarga; separa os dois tipos de retry |
| `FLAG_MAHOGANY_UB_PICKED_CELESTEELA` | `0x104C` | espelho do `VAR_TEMP_3` que sobrevive ao blackout |
| `FLAG_MAHOGANY_UB_LILLIE_SETTLING` | `0x104D` | consumida pelo `ON_TRANSITION` seguinte |

As quatro são limpas por `Mahoganytown_EventScript_UBFinish`.
`VAR_TEMP_6` novo: a Lillie não mostra o caderno duas vezes na mesma visita.
`VAR_TEMP_0`/`VAR_TEMP_1` continuam do vendedor de Rage Candy Bar.

### 16.6 Pedido → como ficou

| Pedido do roteiro V3 | Como ficou |
| --- | --- |
| Não reusar a faixa de três tiles | Rua alargada para cinco linhas; §16.1 |
| Três áreas com corredores independentes | §16.3, com dois enquadramentos de câmera |
| Distâncias reais entre as frentes | Xurkitree `y=20`, Celesteela `y=24`: três linhas livres, e dois tiles entre cada frente e seu treinador nas duas escolhas |
| Conferir o tamanho visual dos sprites | Mamoswine e o parceiro remanejados depois de renderizar; §16.4 |
| Necrozma identificado desde o briefing | A Anabel diz o nome na primeira caixa em que ele aparece; nada de "a criatura" |
| Sem circuito infinito | Uma recarga, com origem e custo: a fonte **perde brilho** ao enviar (`UBSendsUp`/`UBSendsDown` + `UBRises`) |
| Sem gelo como lei universal | A parede corta **aquele trajeto**; a Lillie e a Anabel só afirmam o que a tela mostrou |
| Pryce cobre, não ataca em vão | Ele começa pondo o Mamoswine entre o Necrozma e a porta do Ginásio; o Blizzard inútil saiu |
| Lillie sem autodepreciação | Uma linha de correção ("I thought the distance would break it. It didn't.") e já o pedido do plano melhor |
| Vento da Ninetales cobrindo o Mamoswine | `UBNinetalesCover` antes de `UBWallOrder`; a cura só acontece com a parede de pé |
| Evidência antes da conclusão | `UBFlowBlocked` mostra a corrente morrer no gelo e a UB falhar **antes** da fala da Anabel |
| Necrozma recolhe por cima do gelo | Mamoswine bloqueia o chão (`UBPryceIntercept`), ele sai da linha (`NecrozmaSlipsAside`) e o elo novo passa por cima; a parede não é removida |
| Dois sinais persistem após a absorção | `UBAbsorbedRead` / `UBAbsorbedConfirm`, com o instrumento, **sem depender da party** |
| Parceiro é ator real | Quatro templates em (17,23), um `addobject`; Solgaleo/Lunala estabiliza a borda e a leitura melhora, mas as UBs continuam com o Necrozma |
| Pryce cumpre a promessa da lâmpada | `UBPryceGoodbye`; ele e o Mamoswine saem **a oeste, para fora do enquadramento**, não para dentro do Ginásio |
| Lillie fica até os moradores voltarem | `FLAG_MAHOGANY_UB_LILLIE_SETTLING`: ela fica nessa carga de mapa e some na visita seguinte |
| Retry reconhece o aprendizado | Dois formatos, conforme `FLAG_MAHOGANY_UB_SAW_RECHARGE`; §16.7 |
| Barreira rompida por impacto físico | `UBWallBreaks`: a UB que o jogador enfrentava bate no gelo, um trecho cai, **e só então** a corrente volta |
| Convocação diária | Já existia (`FLAG_DAILY_LOOKER_CALL` + `FLAG_RIFT_LOOKER_SUMMONS`); só os textos mudaram |
| Briefing reconhece Blackthorn V3 | `BriefingM2Welcome/Link/Town/Meet`, quatro caixas, um falante em cada |
| Espera própria antes de Cherrygrove | `OlivineCity_House1_Text_WaitForCherrygroveCall`, ligada ao estado 6 |
| Nada de "tonight" | Nenhum texto da missão cita hora; o apagão é lâmpada e equipamento |
| Plaquinha em todos os diálogos | `HECTOR` e `BOY` acrescentados; narração e bilhete seguem sem plaquinha por decisão do autor |

### 16.7 Os dois retries

`ON_TRANSITION` → `StageUBRetry` devolve a rua por `setobjectxyperm` (as UBs,
o Necrozma, a fenda, o Pryce em (10,21), o Mamoswine em (10,22), o Looker em
(12,20) e o trio de apoio na linha), e o `ON_LOAD` pinta a parede se ela já
tinha sido erguida.

| Situação | O que acontece |
| --- | --- |
| Perdeu a rodada 1 na primeira tentativa | A Lillie refaz a pergunta, a escolha volta e a recarga ainda é descoberta com as falas da primeira execução |
| Perdeu com a parede já de pé | `UBWallBreaks` mostra a UB rompendo um trecho do gelo, a corrente volta, `UBRetryPlan` (Anabel) resume o plano em três linhas e a recarga usa `UBRetryRecharge` |

Quem reinicia é a **Lillie** (ela está na linha de apoio); o Looker, do abrigo,
só diz que a rua está segura e o Centro pronto. Os vizinhos livres dela são
exatamente (18,22) e (19,21), então um `getplayerxy` põe o jogador na linha sem
warp.

### 16.8 Áudio

`fadeoutbgm 4` quando a Anabel vê a leitura subir, `playbgm MUS_DP_LEGEND_APPEARS, TRUE`
quando o Necrozma aparece (o `TRUE` grava em `savedMusic`, então as duas
batalhas devolvem a trilha certa), fanfarra curta na cura e `fadedefaultbgm` só
**depois** de a passagem fechar. Carregar mapa limpa o `savedMusic` sozinho, e
por isso o retry começa limpo.

Todos os clarões usam `fadescreenswapbuffers` (a regra da revisão 5 continua
valendo); `fadescreen` só onde um warp recarrega o mapa logo depois.

### 16.9 Conferido

- `make -j$(nproc)` limpo.
- `medir_linha.py`: nenhuma linha acima de 208 px nos três arquivos de texto.
- `checar_falantes.py`: 16 falantes em ordem.
- `flag_audit.py --csv`: as quatro flags novas entram como `EM_USO`,
  `MAPA_UNICO:Mahoganytown`, com leitura e escrita. Nenhuma órfã.
- Simulação de todas as 47 travessias contra a colisão real do `map.bin`: toda
  chegada bate com o tile projetado; os dois únicos "bloqueios" são a porta do
  Ginásio (10,19), que movimento roteirizado atravessa de propósito, como já
  fazia a versão anterior.
- Renders dos quatro enquadramentos (início, abrigo, frente norte, frente sul,
  parceiro) conferidos um a um — foi assim que os dois sprites encavalados de
  §16.4 apareceram.
- Nenhum travessão (U+2014) em nenhum texto.

### 16.10 O que continua pendente

**Runtime.** Nada abaixo foi jogado; o build só prova que compila.

1. Falar com o Looker em (21,20) e conferir que ele é alcançável só dali.
2. A evacuação inteira: o neto entra antes, o Hector atrás, a porta fecha.
3. Os dois enquadramentos de câmera, com a caixa de diálogo aberta, para
   confirmar que a faixa de rocha é mesmo o que ela cobre.
4. As duas escolhas, as duas rodadas, a cura e a parede.
5. Perder a rodada 1 e perder a rodada 2: os dois retries são diferentes.
6. Os três ramos de parceiro (sem Cosmog, Cosmog/Cosmoem, Solgaleo/Lunala).
7. A resolução: moradores de volta, portas destrancadas, follower de volta,
   Lillie na rua nessa carga e ausente na visita seguinte.
8. De dia **e** de noite, por causa do tint e dos clarões.

**Mapa no Porymap.** A rua alargada e os quatro metatiles de gelo ainda não
foram abertos no Porymap pelo autor. A skill `acabamento-de-mapa` vale aqui: se
ele retocar a borda sul, o retoque dele é a referência.
