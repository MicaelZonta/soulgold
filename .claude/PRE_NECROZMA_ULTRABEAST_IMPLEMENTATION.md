# Pré-Necrozma — a reunião de Olivine — plano de implementação ESQUELETO

**Status:** **esqueleto implementado** — 20/09/2026. Implementado **inteiro,
sem cortes**, nos cinco arquivos previstos em §6, sem alterar nenhuma decisão
de estado. `make -j$(nproc)` limpo. **Runtime pendente**: nada deste evento foi
jogado. O §12 registra o feedback da implementação e **vence o resto deste
arquivo** onde os dois divergirem.
**Modo:** esqueleto (skill `evento-esqueleto`). Diálogo curto, coreografia
mínima, mas estado, visibilidade, gatilhos, checagem de time e repetição
**completos e corretos**.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](SOULGOLD_RIFT_MISSIONS_DESIGN.md)
§5, §7 (bloco “Estado e escopo do evento (V18)”), §8 e §9 — revisão V18.
**Documentos anteriores:**
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (M1),
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (M2),
[`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (M3) e
[`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md) (M4).
Este doc **continua** a máquina de estados das quatro missões e **substitui** o
stub da reunião que a M4 deixou em `OlivineCity_House1`.

## Escopo — as três decisões do autor

1. **O evento acontece inteiro dentro de `OlivineCity_House1`.** Nenhum mapa
   novo, nenhuma viagem, nenhuma cena de rua. Todo o elenco principal está na
   sala.
2. **Termina antes da ida ao altar.** Navio, altar, duelo da Lusamine e Ultra
   Necrozma são do documento seguinte.
3. **Entrega o gancho do altar** e termina ligando **uma flag persistente**,
   `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED`, que é o handoff para a sessão do
   Necrozma.

Do gancho final de New Bark (o jogador volta a Olivine, estado 10) até o estado
12 com a flag ligada. É o primeiro evento do arco que **não** é missão de Ultra
Beast: **não há batalha nenhuma neste documento**, e portanto não há blackout,
retry, `FLAG_NO_CATCHING` nem boss.

**Decisões deste evento:**
- Elenco na sala: **Looker, Anabel, Lusamine, Lillie (+ Ninetales), Gladion
  (+ Silvally) e Kukui** — seis personagens e dois parceiros fora da Poké Ball
  por §3.2. **Oito objetos e o jogador.**
- Looker e Anabel **já existem** com `flag: 0` e não são tocados. Os **seis**
  objetos novos são os quatro visitantes e os dois parceiros.
- A única condição do arco (§7): **Solgaleo OU Lunala na equipe**. Ela não
  bloqueia nada retroativamente e não repete missão nenhuma.
- **A cutscene longa roda uma vez.** Se faltar o parceiro evoluído, o estado vai
  para 11 e a partir daí a pergunta é um ramo curto. É a pendência da M4 (§9
  daquele doc: “a cena inteira se repete a cada tentativa… num retry isso
  cansa”) resolvida antes de custar.

---

## 0. Resumo do fluxo

```text
New Bark resolvido                        VAR_RIFT_MISSIONS_STATE = 10
  └─ ON_TRANSITION mostra os seis visitantes (FLAG_TEMP_1 limpa)
  └─ entrar em OlivineCity_House1 pela porta (4,8)
       └─ gatilho de frame, estado 10 ▶ CUTSCENE DA REUNIÃO (uma vez)
            Looker abre ▶ Kukui dá o lugar ▶ Lusamine diz por que chamou
            ▶ Lillie e Gladion se encaram ▶ Lusamine quer atravessar
            ▶ Anabel impõe a condição, como Faller (argumento, não notícia)
                 └─ CHECAGEM: Solgaleo OU Lunala na equipe?
                      ├─ NÃO ▶ fala do Looker ▶ estado 11
                      │        └─ elenco CONTINUA na sala; voltar (ou falar com
                      │           o Looker) repete só a pergunta, nunca a cena
                      └─ SIM ▶ falas de reconhecimento ▶ GANCHO DO ALTAR
                               └─ setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED
                                  setvar estado 12
                                  warpsilent no lugar ▶ os seis saem de cena
                                    └─ Looker e Anabel: falas de “nos vemos no
                                       porto” (fim deste documento)

estado 12 + flag ligada  ─────▶  entrada do doc do altar / Ultra Necrozma
```

---

## 1. Estado — contrato

### 1.1 Constantes novas

| Constante | Arquivo | Valor | Observação |
|---|---|---|---|
| `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` | `include/constants/flags.h` | `0x1045` | Primeira livre depois de `FLAG_EVENT_ULTRABEAST_NEWBARK` (`0x1044`). Conferido livre em 20/09/2026 (`grep -n "0x1045" include/constants/flags.h` → nada). **Mover `CUSTOM_FLAGS_END`** para ela (hoje aponta para a de New Bark, `flags.h:1797`). |
| `LOCALID_OLIVINE_HOUSE1_LUSAMINE` | `include/constants/map_event_ids.h` | 3 | Dentro da seção `// MAP_OLIVINE_CITY_HOUSE1` que já existe (`:865-867`). Não criar cabeçalho novo. |
| `LOCALID_OLIVINE_HOUSE1_LILLIE` | idem | 4 | |
| `LOCALID_OLIVINE_HOUSE1_NINETALES` | idem | 5 | |
| `LOCALID_OLIVINE_HOUSE1_GLADION` | idem | 6 | |
| `LOCALID_OLIVINE_HOUSE1_SILVALLY` | idem | 7 | |
| `LOCALID_OLIVINE_HOUSE1_KUKUI` | idem | 8 | |

Comentário obrigatório acima do `#define` da flag, no padrão dos quatro
anteriores, dizendo quem seta, **que ela nunca é limpa** e para que serve.
Modelo:

```c
// Pre-Necrozma: the Olivine reunion is over, Solgaleo or Lunala was confirmed
// in the party, and the expedition to the altar is released. Set together with
// VAR_RIFT_MISSIONS_STATE = 12 by OlivineCity_House1_EventScript_ReunionConfirmed
// and NEVER cleared - unlike the four mission flags, this one is a permanent
// unlock. It exists because a map.json "flag" field cannot read a var: it is
// what the altar document will use to light up the ship and the altar objects.
// The var is still the story's authority.
// Invariant: set if and only if VAR_RIFT_MISSIONS_STATE >= 12.
#define FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED          0x1045
#define CUSTOM_FLAGS_END                            FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED
```

**Nenhuma var nova.** `FLAG_NO_CATCHING` / `B_FLAG_NO_CATCHING` não são usadas:
não há batalha neste evento.

**Dívida a pagar de passagem:** o bloco de comentário de
`VAR_RIFT_MISSIONS_STATE` em `include/constants/vars.h:311-318` documenta só os
valores **0 a 4** — ficou parado desde a M1, enquanto as M2/M3/M4 acrescentaram
5 a 10. Este evento estende o bloco até **12**. É barato e é o único lugar do
projeto onde a máquina de estados inteira fica visível para quem abre o header.

### 1.2 Máquina de estados `VAR_RIFT_MISSIONS_STATE` (depois do fim da cadeia de missões)

`VAR_RIFT_MISSIONS_STATE` = `0x4120` (`include/constants/vars.h:319`).
Valores 0-3 no doc de Blackthorn §1.2; 4-6 no de Mahogany; 6-8 no de
Cherrygrove; 8-10 no de New Bark. **Nenhum deles muda.**

| Valor | Significado | Quem escreve | Quem lê |
|---|---|---|---|
| 10 | Quatro missões concluídas; reunião pendente. O elenco **está** na sala | `NewBarkTown_EventScript_UBResolved` (já existe) | `OlivineCity_House1_OnTransition` (mostra o elenco); gatilho de frame (cutscene); Looker e Anabel |
| 11 | Reunião **feita**; falta Solgaleo ou Lunala na equipe. O elenco continua na sala | `OlivineCity_House1_EventScript_ReunionNotYet` | `OlivineCity_House1_OnTransition` (mostra o elenco); gatilho de frame (só a pergunta); Looker, Anabel e os quatro visitantes |
| 12 | Reunião completa; expedição ao altar liberada. **Fim deste documento** | `OlivineCity_House1_EventScript_ReunionConfirmed` | `OlivineCity_House1_OnTransition` (esconde o elenco); Looker e Anabel (falas de porto) |
| 13+ | Reservado para o altar / Ultra Necrozma (design §8 e §9) | próximo doc | — |

**A regra de sobreposição acabou na M4 e não volta.** Cada missão gastava três
valores com o “resolvido” servindo de “briefing pendente” da seguinte; aqui
10 → 11 → 12 são três valores deste evento, e o 12 não abre nada: é a porta do
doc seguinte.

**Por que o 11 existe.** Não é necessidade técnica — é o §7 item 4 (“a expedição
permanece pendente, sem repetir missões concluídas”) e é o que impede a cutscene
longa de tocar outra vez enquanto o jogador termina de evoluir o Cosmog. Sem
ele, cada visita à casa repetiria a cena mais longa do arco para fazer a mesma
pergunta.

**Invariantes:**

- `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` setada ⇔ `VAR_RIFT_MISSIONS_STATE >= 12`.
  As duas mudam **juntas, no mesmo script**, e a flag **nunca** é limpa. É o
  oposto das quatro flags de missão, que são “incidente ativo” e são limpas na
  resolução.
- Estado 10 ou 11 ⇔ `FLAG_TEMP_1` limpa neste mapa ⇔ os seis visitantes visíveis.
  Recalculado no load, nunca persistido.
- As quatro invariantes das missões continuam valendo e **não** são tocadas. Em
  10, 11 e 12 nenhuma das quatro flags de missão está setada.

### 1.3 Temporários por mapa

Conferido em 20/09/2026 (`grep -rn "FLAG_TEMP\|VAR_TEMP" data/maps/OlivineCity_House1/`):
o único temporário usado hoje neste mapa é `VAR_TEMP_1`, a trava do gatilho de
frame. **Nenhuma `FLAG_TEMP_*` é usada.**

| Temp | Uso |
|---|---|
| `VAR_TEMP_1` | Trava uma-vez-por-visita do gatilho de frame (**já existe**; passa a servir aos estados 2, 4, 6, 8 **e** 10, 11) |
| `FLAG_TEMP_1` | Cache de visibilidade dos **seis** visitantes (Lusamine, Lillie, Ninetales, Gladion, Silvally, Kukui) |

**Uma flag temporária basta, e não pode ser mais de uma.** A razão pela qual a
M4 precisou de `FLAG_TEMP_3` e `FLAG_TEMP_4` separadas era `removeobject` no
meio da cena (que seta a flag do template e levaria o elenco inteiro junto).
**Este evento não tem `removeobject` nenhum:** quem tira os seis da sala é o
`warpsilent` do fim, que recarrega o mapa e deixa o `ON_TRANSITION` esconder
todos de uma vez. Se uma evolução da cena introduzir `removeobject` em qualquer
um dos seis, ela **tem** de separar a flag daquele objeto antes.

Evitar `FLAG_TEMP_E`, que a engine reserva para suprimir o follower. Os usos de
`FLAG_TEMP_1` em `data/maps/` são de outros mapas (Mahogany, Cherrygrove, New
Bark e os dois interiores de New Bark); temporários zeram a cada load
(`ClearTempFieldEventData`), então não há conflito.

Reconfirmar antes de implementar:

```bash
grep -rn "FLAG_TEMP_[1-5]\b\|VAR_TEMP_[0-3]\b" data/maps/OlivineCity_House1
```

### 1.4 Orçamento de objetos

`OBJECT_EVENTS_COUNT` é **16** (`include/constants/global.h:83`) e inclui o
jogador. A conta desta sala, com a reunião na tela:

| Ocupante | Slots |
|---|---|
| Jogador | 1 |
| Follower do jogador | 1 |
| Looker e Anabel (já existiam) | 2 |
| Quatro visitantes | 4 |
| Ninetales e Silvally | 2 |
| **Total** | **10 / 16** |

Seis slots livres. A cutscene faz `hidefollower`, mas a conta acima **não**
desconta o follower: o objeto continua alocado, e de qualquer forma o número
tem de fechar antes da cena, quando o follower está visível.

Esta é a segunda cena do arco com o orçamento medido em vez de estimado (a
primeira foi a M4, §1.4 e §12.8 daquele doc). Vale a mesma regra: **objeto que
não cabe não spawna, sem erro nenhum**, os templates são percorridos em ordem, e
quem desaparece primeiro é quem foi acrescentado por último — aqui, o Kukui.
A nota de escala do design §7 (“a sala comporta”) fica assim medida.

---

## 2. Etapa A — os seis objetos novos

`OlivineCity_House1` tem `.pory` → editar só
`data/maps/OlivineCity_House1/scripts.pory` (o arquivo inteiro é um único bloco
`raw`, então tudo abaixo é asm). O `map.json` **muda**: seis objetos novos no
**fim** de `object_events`, com `local_id` explícito (regra fixada na M2).

### 2.1 Planta da cena (colisão real)

Saída de `python3 .claude/skills/encenar-cutscene/dump_mapa.py OlivineCity_House1`
em 20/09/2026, com os seis objetos novos marcados. O mapa tem 13x10; as colunas
x=11 e x=12 são parede em todas as linhas e ficaram fora da tabela. **`y` cresce
para baixo.**

```text
       x= 0  1  2  3  4  5  6  7  8  9 10
  y= 2   .  .  .  .  .  .  .  .  .  .  .     fora da câmera quando o jogador está em (4,8)
  y= 3   .  .  .  .  .  .  .  .  .  .  .     fora da câmera
  y= 4   .  .  .  .  .  #  #  .  .  .  .     a mesa (5-6, 4-5) é sólida
  y= 5   .  .  .  .  L  #  #  A  .  .  .     L = Looker (4,5)      A = Anabel (7,5)
  y= 6   .  .  N  I  .  .  .  .  .  U  .     N = Ninetales (2,6)   I = Lillie (3,6)   U = Lusamine (9,6)
  y= 7   .  .  S  G  .  .  .  .  K  .  .     S = Silvally (2,7)    G = Gladion (3,7)  K = Kukui (8,7)
  y= 8   #  .  .  .  W  .  .  .  .  .  #     W = porta (4,8): único warp, e onde o jogador está na cena
  y= 9   #  #  #  #  #  #  #  #  #  #  #
```

Conferências feitas nessa planta:

- **Os seis tiles novos são andáveis** e nenhum é a mesa: (2,6), (3,6), (9,6),
  (2,7), (3,7), (8,7). Nas linhas y=6 e y=7 o mapa é livre de x=0 a x=10.
- **A porta (4,8) fica livre**, e ninguém está em y=8. O jogador nunca é
  cercado: chega em (4,8) e sai por lá.
- **Ninguém ao sul do jogador**, então a caixa de texto não cobre ator nenhum.
  Com o jogador em (4,8), a câmera mostra x=-3..11 e y=4..13; a caixa ocupa as
  linhas de baixo, que aqui são parede (y=9) ou inexistentes. **As linhas y=2 e
  y=3 ficam fora da tela** — é por isso que nenhum ator da reunião está nelas.
- **Os dois caminhos herdados dos briefings continuam livres**, tile por tile:
  Looker (4,5)→(4,6)→(4,7) e Anabel (7,5)→(7,6)→(7,7)→(6,7)→(5,7). Nenhum dos
  seis objetos novos pisa em nenhum desses tiles, e os dois caminhos não
  compartilham tile em nenhum passo — por isso os dois andam juntos, como nos
  quatro briefings.
- **Pares dono/parceiro adjacentes:** Lillie (3,6) com Ninetales (2,6), Gladion
  (3,7) com Silvally (2,7). A família fica num bloco 2x2 à esquerda; a Lusamine
  fica **sozinha do outro lado da sala**, encostada na parede leste. Isso é
  encenação da cena, não conveniência: os filhos de um lado, a mãe do outro, e é
  a distância que a conversa de família do §7 não resolve.
- **Direções de olhar derivadas, não supostas.** `y` cresce para baixo e “leste”
  é +x. A coluna do jogador é x=4: quem está a oeste dela (x=2,3) olha para
  **leste**; quem está a leste (x=8,9) olha para **oeste**.

### 2.2 Objetos novos — `data/maps/OlivineCity_House1/map.json`

Anexar **no fim** de `object_events`, nesta ordem (o `local_id` é explícito, mas
a ordem do array é o que decide quem some primeiro se o teto de §1.4 for
estourado um dia):

| local_id | Constante | Gráfico | x,y | movement_type | script | flag |
|---|---|---|---|---|---|---|
| 3 | `LOCALID_OLIVINE_HOUSE1_LUSAMINE` | `OBJ_EVENT_GFX_LUSAMINE` | 9,6 | `MOVEMENT_TYPE_FACE_LEFT` | `OlivineCity_House1_EventScript_ReunionLusamine` | `FLAG_TEMP_1` |
| 4 | `LOCALID_OLIVINE_HOUSE1_LILLIE` | `OBJ_EVENT_GFX_LILLIE` | 3,6 | `MOVEMENT_TYPE_FACE_RIGHT` | `OlivineCity_House1_EventScript_ReunionLillie` | `FLAG_TEMP_1` |
| 5 | `LOCALID_OLIVINE_HOUSE1_NINETALES` | `OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)` | 2,6 | `MOVEMENT_TYPE_FACE_RIGHT` | `NULL` | `FLAG_TEMP_1` |
| 6 | `LOCALID_OLIVINE_HOUSE1_GLADION` | `OBJ_EVENT_GFX_GLADION` | 3,7 | `MOVEMENT_TYPE_FACE_RIGHT` | `OlivineCity_House1_EventScript_ReunionGladion` | `FLAG_TEMP_1` |
| 7 | `LOCALID_OLIVINE_HOUSE1_SILVALLY` | `OBJ_EVENT_GFX_SPECIES(SILVALLY)` | 2,7 | `MOVEMENT_TYPE_FACE_RIGHT` | `NULL` | `FLAG_TEMP_1` |
| 8 | `LOCALID_OLIVINE_HOUSE1_KUKUI` | `OBJ_EVENT_GFX_KUKUI` | 8,7 | `MOVEMENT_TYPE_FACE_LEFT` | `OlivineCity_House1_EventScript_ReunionKukui` | `FLAG_TEMP_1` |

Campos restantes iguais aos dois objetos que já existem no arquivo:
`"elevation": 0`, `"movement_range_x": 0`, `"movement_range_y": 0`,
`"trainer_type": "TRAINER_TYPE_NONE"`, `"trainer_sight_or_berry_tree_id": "0"`.
**`elevation` é 0** — é o que os dois objetos existentes usam, e a M4 registrou
(§12.2) que `elevation: 3` foi um erro de plano copiado do `pokeemerald`.

Conferido em 20/09/2026:

- `OBJ_EVENT_GFX_LUSAMINE` (330), `OBJ_EVENT_GFX_LILLIE` (331),
  `OBJ_EVENT_GFX_KUKUI` (332) e `OBJ_EVENT_GFX_GLADION` (333) existem em
  `include/constants/event_objects.h:337-340`, e os quatro já são usados em
  mapas do projeto (Route 29, New Bark, Cherrygrove, Route 30).
- `OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)` já é usado em `Mahoganytown` e
  `DragonsDen_Shrine`; `OBJ_EVENT_GFX_SPECIES(SILVALLY)` em `BlackthornCity` e
  `ReceptionGate`. Os dois parceiros têm sprite de overworld e `script: "NULL"`,
  como o Ninetales da M2.
- O `map.json` **não** ganha `coord_events` nem `bg_events` novos, e o warp
  continua único.

**Os parceiros seguem §3.2 sem exceção:** Ninetales e Silvally fora da Poké
Ball, ao lado dos donos, com a **mesma** flag de ocultação deles — entram e
saem juntos, que é o padrão da skill `parceiro-pokemon-de-npc`. Lusamine e
Kukui continuam sem parceiro, porque §3.2 nomeia só Lillie e Gladion e o design
proíbe criar exceção por conveniência de cena.

---

## 3. Etapa B — visibilidade

### 3.1 O mapa ganha um `ON_TRANSITION` (não tinha nenhum)

Até aqui este mapa só tinha `MAP_SCRIPT_ON_FRAME_TABLE`, e o comentário do
arquivo dizia o porquê: “No ON_TRANSITION: there is no visibility to compute,
both objects are always present.” **Isso deixa de ser verdade** e o comentário
tem de ser corrigido junto.

```asm
OlivineCity_House1_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_House1_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_House1_OnFrame
	.byte 0

@ NEW with the pre-Necrozma reunion. Looker and Anabel still have "flag": "0"
@ and are never touched here. The six reunion objects DO need this: their hide
@ flag is FLAG_TEMP_1, and ClearTempFieldEventData zeroes every temp on every
@ load - so the DEFAULT IS VISIBLE, and this block is the only thing that keeps
@ Lusamine and the others out of the room for the whole game before state 10.
@ It runs before the first spawn, on every load of this map.
OlivineCity_House1_OnTransition::
	call OlivineCity_House1_EventScript_ApplyReunionVisibility
	end

@ FLAG_TEMP_1 - the four visitors and the two partners. Shown ONLY in states 10
@ (reunion pending) and 11 (reunion held, waiting for the evolved partner).
@ From 12 on they are gone for good: they went ahead to the port.
OlivineCity_House1_EventScript_ApplyReunionVisibility::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowReunionCast
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowReunionCast
	setflag FLAG_TEMP_1
	return

OlivineCity_House1_EventScript_ShowReunionCast::
	clearflag FLAG_TEMP_1
	return
```

Três coisas que esse bloco tem de respeitar, e que são a razão de ele existir:

1. **Roda sem condição.** Não pode ficar atrás de `goto_if_set` de nada: os
   temporários voltam zerados de todo load, e temp zerada significa **visível**.
   Uma versão “otimizada” que só rodasse no estado 10 encheria a casa de
   visitantes durante o jogo inteiro.
2. **É `setflag`/`clearflag`, nunca `removeobject`.** `removeobject` num objeto
   escondido por flag não segura nada (skill `visibilidade-e-gatilhos`) e ainda
   corromperia a flag compartilhada dos seis.
3. **`goto_if_eq` com dois valores, não `goto_if_ge`.** O erro que Olivine já
   cometeu três vezes (§4.5) mora neste arquivo.

É o mesmo desenho de `Mahoganytown_EventScript_ApplyUBVisibility`
(`data/maps/Mahoganytown/scripts.inc`), inclusive o `call` + `return` com um
`goto` no meio.

---

## 4. Etapa C — a cena

### 4.1 O gatilho de chegada passa a atender seis estados

O gatilho existente (`OlivineCity_House1_EventScript_BriefingTrigger`) já faz o
certo: `setvar VAR_TEMP_1, 1` como **primeira** instrução, e só encena se o
jogador estiver em (4,8). Ganha **duas linhas**:

```asm
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_StageBriefing
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_StageReunion
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_StageRecheck
	end
```

**O começo é determinístico de graça neste mapa:** (4,8) é o **único** warp da
casa, então no estado 10 o jogador está necessariamente ali quando o gatilho
dispara, e a checagem de `getplayerxy` nunca falha. Não há Fly nem Dig em
interior. Ainda assim os scripts de objeto também levam à cena (§4.5), porque é
o padrão do arquivo e porque um estado não pode ficar sem saída.

### 4.2 A encenação

```asm
@ The reunion cutscene. Reached from the frame trigger at state 10 and from the
@ Looker/Anabel object scripts at state 10. It plays ONCE: it always ends in
@ state 11 or 12, and neither re-enters it. That is the M4 lesson applied
@ before it costs anything (M4 doc section 9: the long scene replaying on every
@ attempt is tiring) - here the long version plays once and "did your partner
@ evolve yet?" is a short branch.
@
@ Looker and Anabel reuse the SAME movements as the four briefings:
@   Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
@   Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
@ Both paths are free of all six new objects and share no tile on any step
@ (checked tile by tile, section 2.1).
OlivineCity_House1_EventScript_StageReunion::
	lockall
	hidefollower
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
	goto OlivineCity_House1_EventScript_ReunionScene

@ State 11 arrival: no choreography beyond Looker stepping down to the player,
@ and no recap of the meeting. He asks the one question that is still open.
OlivineCity_House1_EventScript_StageRecheck::
	lockall
	hidefollower
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
	goto OlivineCity_House1_EventScript_ReunionCheck
```

**Ninguém volta para o lugar no fim.** Os quatro briefings mandavam Looker e
Anabel caminharem de volta; aqui a reunião **continua acontecendo** depois que a
caixa fecha, e os dois ficam onde pararam até o próximo load, que os devolve aos
tiles do template. Isso é de propósito e é mais barato; a porta (4,8) não fica
bloqueada, porque o jogador termina a cena **em cima** dela. Os movimentos
`LookerReturn`/`AnabelReturn` continuam no arquivo, usados pelos briefings.

### 4.3 A conversa

```asm
@ Beats, in the order design section 7 fixes them:
@   1. Looker closes the New Bark report and names the room.
@   2. Kukui: Anabel's bearing plus Elm's six weeks became a PLACE. He is
@      already facing west (into the room), so he needs no turnobject.
@   3. Lusamine says why she asked for this. Lillie (3,6) and Gladion (3,7) are
@      in the same column, one tile apart, so they can look AT EACH OTHER:
@      y grows downward, so Lillie faces DIR_SOUTH and Gladion DIR_NORTH. Then
@      both go back to DIR_EAST, facing the room and their mother.
@      The family conversation opens here and is NOT resolved here (design 7).
@   4. Lusamine states she intends to cross. ANABEL sets the condition, as a
@      Faller - and it is an ARGUMENT, not news: she told them in New Bark
@      (design 3.1 / 6.4). ONE box of recap, no more. She is at (5,7) and
@      Lusamine is at (9,6), so she turns DIR_EAST to face her, then back.
@   5-6. Anabel names what the passage needs; Looker checks -> ReunionCheck.
OlivineCity_House1_EventScript_ReunionScene::
	msgbox OlivineCity_House1_Text_ReunionOpen, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionKukui, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionLusamineCalled, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_SOUTH
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_NORTH
	msgbox OlivineCity_House1_Text_ReunionLillie, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionGladion, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_EAST
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_EAST
	msgbox OlivineCity_House1_Text_ReunionCross, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_EAST
	msgbox OlivineCity_House1_Text_ReunionCondition, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_SOUTH
	goto OlivineCity_House1_EventScript_ReunionCheck
```

Uma regra que este bloco segue e que vale para qualquer cena grande:
**nenhuma direção aqui é derivada da posição viva do jogador.** Todo
`turnobject` aponta para outro ator, cujo tile é fixo. Por isso a cena está
correta tanto vinda do gatilho (jogador em (4,8)) quanto vinda de um script de
objeto (jogador em qualquer tile da sala). A M4 tropeçou no lado oposto disso
(§12.6: tile diagonal não permite “olhar para o jogador”).

`closemessage` depois de **toda** caixa seguida de `turnobject` ou
`applymovement` — a armadilha registrada na M4 §12.4: sem ele o movimento roda
atrás da caixa aberta.

### 4.4 A checagem de time — a única do arco

```asm
@ The one gate of the arc (design sections 7 and 8): Solgaleo OR Lunala, in the
@ PARTY. checkspecies compiles to Scrcmd_checkspecies (src/scrcmd.c), which
@ calls CheckPartyHasSpecies (src/field_specials.c:4422): it walks gPlayerParty
@ only and returns into VAR_RESULT. Consequences, all of them wanted by the
@ design:
@   - one in the PC does not count; a Pokedex entry does not count;
@   - Cosmog and Cosmoem do not pass, and no evolution happens here;
@   - EITHER species satisfies it, and having both is never required.
@ Two checks, never one, and never a check for the family.
@ Reachable from the long scene, from the state-11 trigger and from the Looker
@ and Anabel object scripts, so it must read as a standalone question.
OlivineCity_House1_EventScript_ReunionCheck::
	msgbox OlivineCity_House1_Text_ReunionAsk, MSGBOX_DEFAULT
	closemessage
	checkspecies SPECIES_SOLGALEO
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
	checkspecies SPECIES_LUNALA
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
	goto OlivineCity_House1_EventScript_ReunionNotYet

@ Not yet. Nothing is spent: no mission is replayed, nobody leaves the room,
@ and the only thing that changes is 10 -> 11, which is what stops the long
@ cutscene from playing again. From 11 this whole block is four boxes.
@ releaseall (not release) because this script is reached from a lockall
@ context AND from a lock context: releaseall is correct in both, release would
@ leave the other objects frozen after the cutscene.
OlivineCity_House1_EventScript_ReunionNotYet::
	msgbox OlivineCity_House1_Text_ReunionNotYet, MSGBOX_DEFAULT
	closemessage
	setvar VAR_RIFT_MISSIONS_STATE, 11
	releaseall
	end
```

O `setvar 11` é idempotente: rodar de novo no estado 11 reescreve 11. Não existe
caminho que volte de 11 para 10, e não existe estado novo para o “já perguntei”.

### 4.5 Os scripts de objeto — e o erro que Olivine já cometeu três vezes

O ramo que existe hoje em Looker e Anabel é
`goto_if_ge VAR_RIFT_MISSIONS_STATE, 10, ..._Reunion`. Ele **tem de ser
quebrado em três**, e este é o quarto aviso do mesmo tipo no mesmo arquivo:

```asm
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_LookerGoAheadM4
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerReunion
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_LookerRecheck
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_LookerAltar
```

> **Se o `goto_if_ge ..., 10` ficar,** o estado 11 e o 12 nunca são alcançados
> pelos scripts de objeto: o jogador que voltar com Solgaleo e falar com o
> Looker recebe a cutscene inteira outra vez, e depois do estado 12 os dois
> continuam dizendo o texto da reunião. Build limpo, zero sintoma até jogar.
> A M3 apagou uma dessas linhas deixada pela M2; a M4 moveu outra deixada pela
> M3. **Estado novo entra como `goto_if_eq`; só o último da lista pode ser
> `goto_if_ge`.**

Checagem obrigatória depois de editar (tem de devolver **exatamente duas**
linhas de código, ambas com `, 12,`):

```bash
grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE" data/maps/OlivineCity_House1/scripts.pory
```

Os ramos novos, em Looker e em Anabel (os dois rótulos de stub de reunião que a
M4 deixou, `LookerReunion` e `AnabelReunion`, são **reaproveitados** — deixam de
ser stub e passam a chamar a cena de verdade):

```asm
OlivineCity_House1_EventScript_LookerReunion::
	goto OlivineCity_House1_EventScript_ReunionScene

OlivineCity_House1_EventScript_LookerRecheck::
	goto OlivineCity_House1_EventScript_ReunionCheck

@ SKELETON: last stop of this document. The ship, the voyage and the altar
@ belong to the next one, which starts from FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED
@ and VAR_RIFT_MISSIONS_STATE >= 12.
OlivineCity_House1_EventScript_LookerAltar::
	msgbox OlivineCity_House1_Text_LookerAltar, MSGBOX_DEFAULT
	goto OlivineCity_House1_EventScript_ReleaseEnd
```

Idem para Anabel (`AnabelReunion` → `goto ..._ReunionScene`, `AnabelRecheck` →
`goto ..._ReunionCheck`, `AnabelAltar` → sua própria caixa). O `@ SKELETON:` das
Beast Balls (§5 do design, pendente desde a M1) continua no script dela.

**Por que o script de objeto pode rodar a cutscene inteira.** `ReunionScene` não
tem `applymovement` nenhum, só `msgbox` e `turnobject` em atores de tile fixo, e
nenhum dos seis visitantes tem movimento de vagar (todos são `MOVEMENT_TYPE_FACE_*`).
Sob `lock` a cena roda igual; o que muda é só a ausência do passo do Looker.

Os quatro visitantes ganham um script de uma caixa cada
(`ReunionLusamine`, `ReunionLillie`, `ReunionGladion`, `ReunionKukui`), no
padrão `lock` / `faceplayer` / `msgbox` / `goto ..._ReleaseEnd`. Eles servem ao
estado 11, que é o único em que o jogador anda pela sala com todos presentes.
Sem ramo por estado: no 12 eles não estão lá para serem falados.

---

## 5. Etapa D — o gancho e a flag

```asm
@ Confirmed. The room recognises the Pokemon that came out of the egg Gladion
@ handed the player in Violet, and then Looker gives the hook to the altar.
@ Design section 7 item 7 (releasing the ship) and everything at the altar
@ belong to the NEXT document: this event ends on the flag.
@ Every turnobject here aims at a visitor on a fixed tile, because this block
@ is reachable from the frame trigger AND from two object scripts.
OlivineCity_House1_EventScript_ReunionConfirmed::
	msgbox OlivineCity_House1_Text_ReunionSeeIt, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionGladionEgg, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionLillieProud, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionLusamineKnows, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionWayBack, MSGBOX_DEFAULT
	closemessage
	msgbox OlivineCity_House1_Text_ReunionHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED   @ handoff; NEVER cleared
	setvar VAR_RIFT_MISSIONS_STATE, 12           @ invariant: flag and var together
	@ Reload in place: ON_TRANSITION hides the six visitors (they went ahead to
	@ the port), Looker and Anabel snap back to (4,5)/(7,5) from their
	@ templates, and the follower comes back (undoes hidefollower). Without
	@ this, all of that would happen in pieces as the camera moved.
	@ (4,7), not (4,8): do not respawn the player on the room's only warp tile.
	@ (4,7) is guaranteed free, because by state 12 the six are already hidden.
	warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7
	waitstate
	releaseall
	end
```

Quatro coisas nesse bloco que não são estilo, são contrato:

1. **`setflag` e `setvar` no mesmo script, colados.** É a invariante de §1.2. Se
   uma evolução separar os dois, a flag e a história divergem sem sintoma.
2. **`warpsilent` + `waitstate` + `releaseall` + `end`,** na ordem. É o erro que
   a M1 cometeu e que virou regra para todo doc do arco.
3. **Destino (4,7), não (4,8).** O mapa tem um único warp, em (4,8); recarregar o
   jogador em cima dele é pedir para descobrir em runtime se a engine reentra no
   warp. (4,7) fica a um tile ao norte, está livre no estado 12 e não é warp.
   O gatilho de frame dispara depois desse load com `VAR_TEMP_1` zerada, mas
   morre duas vezes: o jogador não está em (4,8) **e** o estado 12 não casa com
   nenhum `goto_if_eq` da lista.
4. **O evento acaba aqui.** Nenhum `setvar` para 13, nenhum objeto de navio,
   nenhum warp para o altar. O doc seguinte começa lendo a flag.

Falas pós-reunião (estado ≥ 12), que são o único conteúdo novo permanente que
este evento deixa na casa:

- `Text_LookerAltar` — Looker, no porto de Olivine, quando o jogador estiver
  pronto. É o gancho repetível: quem salvou e desligou tem de conseguir
  relembrar para onde ir falando com ele.
- `Text_AnabelAltar` — Anabel, a condição dela em uma linha: ninguém atravessa
  sem plano de volta.

### 5.1 Textos

Todos `@ SKELETON:` — placeholder curto, na voz do design §3.1 (Looker
teatral e caloroso; Anabel precisa; Lusamine formal e sem rodeio; Lillie direta;
Gladion econômico; Kukui entusiasmado). **Sem travessão `—`** (U+2014 não está
em `charmap.txt` e quebra o build, M4 §12.7); `“ ”` e `…` podem.

> `ReunionOpen` —
> Looker: {PLAYER}. Come in. Mind the chairs - there are not enough of them, and I have stopped apologising.
> Looker: New Bark holds. Four in four. The file is closed.
> Looker: Which is why everyone in this room came when I asked. Look at them. I did not have to explain twice.
>
> `ReunionKukui` —
> Kukui: Your rifts closed toward one bearing. Anabel's number, Elm's six weeks of it, my rhythm.
> Kukui: Three wrong tools, one answer. There's a place out there, {PLAYER}. An altar. We can put a boat on it.
>
> `ReunionLusamineCalled` —
> Lusamine: I asked the Inspector to call this meeting.
> Lusamine: Not as Aether. Aether would have sent a report.
> Lusamine: I owe the people in this room an accounting, and two of them are mine.
>
> `ReunionLillie` — (they look at each other first)
> Lillie: ...You asked for us. Both of us.
> Lillie: I'm not going to pretend that's nothing. It isn't nothing.
>
> `ReunionGladion` —
> Gladion: We'll do the accounting after.
> Gladion: Whatever is at that altar, it doesn't wait for our family to sort itself out.
>
> `ReunionCross` —
> Lusamine: Then let me say the rest of it plainly. I intend to cross.
> Lusamine: I have been on the other side of a door like that one. Nobody else in this room has.
>
> `ReunionCondition` — **one box of recap, no more (design 3.1)**
> Anabel: You have. I have as well, and I came back wrong, and I told you all so in New Bark.
> Anabel: So here is my condition, Madame, and it is not negotiable: nobody crosses without a way back.
> Anabel: Not you. Not me. Not the Champion.
>
> `ReunionAsk` — **must read standalone: it is also the state-11 question**
> Anabel: And a way through needs something that can open it. Not a machine. We tried machines for six weeks.
> Looker: {PLAYER}. Your partner. The one that started as an egg. May we see them?
>
> `ReunionNotYet` — design section 7, Looker's proposed speech
> Looker: ...Ah. Not yet.
> Kukui: That's not a no! That's a “give it time”. It's still growing into what it's going to be.
> Looker: Then we prepare, and you raise them. Come back when they have finished becoming Solgaleo or Lunala.
> Looker: We are not going anywhere. Frankly, there is nowhere for six people to go in this room.
>
> `ReunionSeeIt` —
> Looker: ...Oh.
> Anabel: That is it. That is the reading, standing in a living room in Olivine.
>
> `ReunionGladionEgg` —
> Gladion: I handed you that egg in Violet and told you to keep it away from people like us.
> Gladion: You did better than that. You raised it.
>
> `ReunionLillieProud` —
> Lillie: I knew the whole way. Every time we met, I knew.
> Lillie: I just wanted to be here when somebody finally said it out loud.
>
> `ReunionLusamineKnows` —
> Lusamine: That light is what opens the way. I am the only person alive who knows what it looks like from the other side.
> Lusamine: Thank you for not letting me do this alone. I am told that is the lesson.
>
> `ReunionWayBack` —
> Anabel: My condition stands. We go together, and we come back.
>
> `ReunionHook` — **this is the handoff to the altar document**
> Looker: Then it is settled. There is a ship at the Olivine port, and it is ours for as long as this takes.
> Looker: We sail for the altar, {PLAYER}. You, your partner, and everyone in this room who can keep up.
> Looker: Come to the port when you are ready. Rest first. Whatever is waiting at that altar has waited a long time; it can wait for you to heal.
>
> `LookerAltar` — (state 12 and up)
> Looker: The ship is at the port whenever you are ready, {PLAYER}.
> Looker: Madame Lusamine went ahead. Of course she did.
>
> `AnabelAltar` —
> Anabel: We leave when you do, not before.
> Anabel: And we come back. That part is the whole plan.
>
> Idle lines for state 11 (one box each) —
> `IdleLusamine`: I will not pace. Pacing is for people without instruments.
> `IdleLillie`: Take your time with them. I mean it - that's not a polite thing to say, it's the actual advice.
> `IdleGladion`: Go and train. That's not an insult, it's what I'd be doing.
> `IdleKukui`: Six weeks of bad data and one good afternoon! Science, {PLAYER}!

---

## 6. Arquivos tocados (checklist de implementação)

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED 0x1045` + comentário; mover `CUSTOM_FLAGS_END` |
| `include/constants/vars.h` | Estender o comentário de `VAR_RIFT_MISSIONS_STATE` de 4 até 12 (dívida das M2/M3/M4) |
| `include/constants/map_event_ids.h` | 6 locais (3-8) **dentro da seção `// MAP_OLIVINE_CITY_HOUSE1` existente** |
| `data/maps/OlivineCity_House1/map.json` | 6 objetos novos no fim de `object_events`, `flag: FLAG_TEMP_1`, `local_id` explícito |
| `data/maps/OlivineCity_House1/scripts.pory` | `ON_TRANSITION` novo + visibilidade; 2 linhas no gatilho de frame; `StageReunion`/`StageRecheck`; `ReunionScene`; `ReunionCheck`; `ReunionNotYet`; `ReunionConfirmed`; 4 scripts de visitante; ramos 10/11/≥12 em Looker e Anabel (**quebrando o `goto_if_ge ..., 10`**); corrigir o comentário “No ON_TRANSITION”; textos novos |

Cinco arquivos, um mapa, nenhum gráfico novo, nenhuma batalha, nenhum treinador,
nenhum `trainers.party`. É o evento mais barato do arco em arquivos e o mais
caro em atores simultâneos.

**Ordem de edição.** Flag e localids → `map.json` **junto com** o
`ON_TRANSITION` (nunca um sem o outro: com os seis objetos em `FLAG_TEMP_1` e
sem o recálculo, a Lusamine aparece na casa desde o New Game) → resto do
`scripts.pory` → `vars.h` → build.

---

## 7. Esqueleto × evolução

**Está simples de propósito (pode melhorar):**

- Ninguém anda além do Looker e da Anabel, e os dois reaproveitam os movimentos
  dos briefings. Evolução: os visitantes se reposicionando, alguém se
  levantando, a Lusamine andando até o jogador na fala dela.
- Nenhuma música própria, nenhum efeito. Evolução: troca de BGM na entrada da
  cena e silêncio na caixa da Lusamine.
- O parceiro do jogador não aparece na cena, embora a cena seja **sobre** ele.
  Evolução possível (e a mais valiosa aqui): mostrar o Solgaleo/Lunala do
  jogador sob `fadescreen`, com o cry, no `ReunionSeeIt`. Custa um objeto do
  orçamento de §1.4 ou um `playmoncry` sem objeto.
- Todo diálogo é placeholder e está marcado com `@ SKELETON:`.
- As falas ociosas do estado 11 são uma caixa cada.
- No estado 11 o Looker desce até o jogador, mas a Anabel fala de onde está.

**Não pode regredir sem atualizar este doc e o design:**

- Valores 10/11/12 e a invariante `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` ⇔ `>= 12`,
  com a flag **nunca** limpa.
- O estado 11: a cutscene longa não pode voltar a tocar quando o jogador
  reentra sem o parceiro evoluído.
- A checagem olhar **só a equipe**, aceitar **qualquer um dos dois** e não checar
  a família de Cosmog.
- `ON_TRANSITION` rodando sem condição, e `FLAG_TEMP_1` sendo a flag dos seis.
  Quem introduzir `removeobject` em qualquer um deles tem de separar a flag
  daquele objeto primeiro (§1.3).
- Os seis `local_id` (3-8) e a ordem no fim de `object_events`.
- Os dois caminhos de Looker e Anabel ficarem livres: nenhum objeto novo em
  (4,6), (4,7), (7,6), (7,7), (6,7) ou (5,7).
- Ninguém em y=8 e ninguém em y=2/y=3 (fora da câmera).
- O destino do `warpsilent` **não** ser o tile do warp.
- Nenhuma direção derivada da posição viva do jogador em `ReunionScene`,
  `ReunionCheck` ou `ReunionConfirmed`.
- Os dois parceiros fora da Poké Ball (§3.2), com a flag dos donos.
- O orçamento de §1.4: seis slots livres, e acabou.

---

## 8. Dependências frágeis criadas por este plano

1. **`goto_if_ge VAR_RIFT_MISSIONS_STATE` neste arquivo.** Quarta vez que o
   mesmo padrão ameaça engolir estados novos (§4.5). O `grep` de verificação é
   obrigatório depois de editar.
2. **`FLAG_TEMP_1` é compartilhada pelos seis.** Qualquer `removeobject` num
   deles esconde os outros cinco.
3. **O `ON_TRANSITION` é novo neste mapa e é o único guarda dos seis objetos.**
   Se alguém o tornar condicional, a Lusamine passa a morar na casa desde o New
   Game. O comentário antigo (“there is no visibility to compute”) tem de morrer
   junto com a mudança, ou o próximo leitor acredita nele.
4. **O `VAR_TEMP_1` do gatilho de frame agora serve a seis estados.** Continua
   sendo `setvar` na primeira instrução; mexer nisso trava os controles.
5. **A flag é um handoff que ninguém lê ainda.** Até o doc do altar existir,
   `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` é escrita e nunca lida. Isso é
   intencional e é o pedido do autor, mas significa que um erro nela não tem
   sintoma nenhum **nesta** sessão: conferir em runtime pelo estado 12 e pelas
   falas de porto, não pela flag.
6. **Os dois rótulos de stub da M4 (`LookerReunion`, `AnabelReunion`) mudam de
   significado** em vez de serem apagados. Quem procurar “o stub da reunião” no
   `grep` vai achar a cena de verdade.

---

## 9. Pendências e riscos conhecidos

- **Runtime: nada deste evento foi jogado** (nem nenhuma das quatro missões).
  O build limpo prova só que compila.
- **O follower fica escondido no estado 11 até o jogador sair da casa.**
  `hidefollower` não tem inverso (§12.3 item 1): não existe `showfollower` em
  `asm/macros/event.inc`, e só um load de mapa o traz de volta. O ramo do estado
  11 termina em `releaseall` sem `warpsilent`, então o parceiro do jogador some
  enquanto ele anda pela sala falando com os seis. No estado 12 o problema não
  existe, porque `ReunionConfirmed` recarrega o mapa. É o mesmo comportamento
  das quatro briefings, mas dura mais aqui. Se em runtime incomodar, a correção
  é um `warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7` sob fade no fim de
  `ReunionNotYet` — **nunca** um `setvar` novo nem um estado novo.
- **Oito objetos e o jogador numa sala de 11x7 tiles úteis.** A conta fecha em
  10/16 por leitura de código (§1.4), não por medição em jogo. É o risco nº 1 do
  passo 3 de §10.
- **A sala é a cena mais cheia do arco e a caixa de texto é grande.** A planta
  garante que ninguém está ao sul do jogador, mas isso é geometria de mapa, não
  teste visual.
- **`checkspecies` não filtra ovo.** `CheckPartyHasSpecies` compara
  `MON_DATA_SPECIES`, que um ovo também tem. Na prática é inofensivo: não existe
  ovo de Solgaleo nem de Lunala por criação, então nenhum jogador legítimo passa
  a checagem com um ovo. Fica registrado porque a exigência do §7 (“um ovo não
  satisfaz o requisito”) é atendida por acidente da espécie, não por guarda no
  script.
- **A cena longa não tem escape.** São treze caixas antes da checagem, e quem já
  viu não vê de novo — mas quem viu **uma** vez viu inteira. Se em runtime isso
  parecer longo demais, a redução é cortar caixas, nunca mover a checagem para
  antes das falas: a checagem é o clímax da cena.
- **Beast Balls com a Anabel** (§5 do design) continuam pendentes desde a M1, e
  este evento passa pelo script dela sem resolvê-las.
- **A recomendação do §8 do design** — reconferir Solgaleo/Lunala na primeira
  abertura do portal — é do doc do altar. Este evento **não** guarda qual dos
  dois o jogador tem, e não deve passar a guardar.
- **Nada aqui prepara o retry do Ultra Necrozma** (§9 do design), que continua
  sendo decisão a tomar **antes** de implementar o encontro.

---

## 10. Teste em runtime

Ordem otimizada para achar cedo o que quebra mais coisas:

1. **Antes de tudo, com o evento inativo** (estado 0, ou qualquer valor de 1 a
   9): entrar na casa. Só Looker e Anabel estão lá. **Nenhum visitante
   visível** — é o erro silencioso de §3.1 e é o teste mais barato do arquivo.
   Repetir depois de salvar e recarregar dentro da casa.
2. Estado 9 (missão 4 ativa): os dois ainda dizem as falas de “vá na frente”.
   Nada da reunião aparece.
3. Estado 10, entrar pela porta (4,8): os seis visitantes estão nos seis tiles
   da planta, **todos os oito objetos desenhados** (se faltar alguém, a conta de
   §1.4 está errada e quem sumiu é o Kukui); Looker e Anabel descem; a cutscene
   roda inteira. Conferir que Lillie e Gladion se encaram e voltam a olhar para
   leste, que a Anabel vira para a Lusamine e volta, e que a caixa de texto não
   cobre ninguém.
4. **Sem Solgaleo e sem Lunala:** a cena termina na fala do Looker, o estado vai
   para 11, ninguém sai da sala. Sair e voltar: **a cutscene longa não roda de
   novo** — só o Looker desce e faz a pergunta.
5. No estado 11, falar com Looker, Anabel e os quatro visitantes: seis falas,
   nenhuma delas a cutscene. **Conferir o follower** enquanto se anda pela sala:
   ele fica escondido até sair da casa (§9), e é aqui que se decide se isso é
   aceitável ou se `ReunionNotYet` precisa do `warpsilent`.
6. **Com Cosmog na equipe** e depois **com Cosmoem**: a checagem continua
   falhando. Com Solgaleo **no PC** e nada na equipe: continua falhando. Esses
   três são o §7 do design em forma de teste.
7. Guardar Solgaleo na equipe e entrar: a cena continua do
   `ReunionSeeIt`, a flag liga, o estado vai para 12, o mapa recarrega, o
   jogador aparece em (4,7), **os seis desaparecem**, Looker e Anabel voltam a
   (4,5) e (7,5) e o follower volta.
8. Repetir o passo 7 num save separado com **Lunala** em vez de Solgaleo.
9. Estado 12: falar com Looker e Anabel (falas de porto). Sair e voltar várias
   vezes: nada se repete, nenhum visitante volta, e o gatilho de frame não faz
   nada.
10. Salvar e recarregar em cada estado (10, 11, 12) **dentro** da casa e
    **fora** dela, e reentrar.
11. Alcançar a cena pelo caminho alternativo: no estado 10, entrar, deixar o
    gatilho rodar, e num save separado falar com a **Anabel** em vez de esperar
    o gatilho (o ramo de script de objeto). A cena tem de rodar igual, sem
    ninguém olhando para o lado errado.
12. Regressões: os quatro briefings (estados 2, 4, 6, 8) ainda encenam e ainda
    setam o par flag/estado certo; as quatro cidades das missões continuam
    povoadas no estado 12; o presente do Friendly Trader de Cherrygrove continua
    não repetível.

---

## 11. O que este doc copiou das M1-M4 e o que faz diferente

**Copiou sem mudar:** uma var única de progresso; flag persistente só quando o
`map.json` exige, com invariante escrita; cache de visibilidade em `FLAG_TEMP_*`
recalculado no `ON_TRANSITION` sem condição; `local_id` explícito e objetos
novos sempre no **fim** de `object_events`; `warpsilent` + `waitstate` +
`releaseall` + `end` para mudar a população do mapa sob fade; começo
determinístico por tile único; `closemessage` antes de todo movimento; nenhuma
direção suposta; `@ SKELETON:` em tudo que é provisório.

**Faz diferente, e por quê:**

1. **Não tem batalha.** É o primeiro evento do arco assim. Sem boss, sem
   `FLAG_NO_CATCHING`, sem blackout, sem retry — e por isso sem o mecanismo que
   dava “tentar de novo” de graça. O papel do retry aqui é o **estado 11**.
2. **O gate é o time do jogador, não a vitória.** A única checagem de time do
   arco, e ela pode falhar indefinidamente sem que nada se perca.
3. **A cena longa roda uma vez.** As quatro missões repetiam tudo a cada
   tentativa; a M4 registrou isso como cansaço (§9 daquele doc). Aqui a
   separação cutscene/pergunta é decisão de estado, não de texto.
4. **Uma flag que nunca é limpa.** As quatro flags de missão são “incidente
   ativo”; esta é um desbloqueio permanente, e é o primeiro handoff por flag
   entre dois documentos do arco.
5. **Oito atores num interior pequeno**, contra sete numa rua aberta na M4. O
   orçamento sobra (10/16), mas a geometria é apertada: é o primeiro doc em que
   a câmera e a caixa de texto decidiram **onde** os atores podem estar (nada em
   y=2/y=3, nada em y=8).
6. **Uma única `FLAG_TEMP_*` para o elenco inteiro**, porque não há
   `removeobject` na cena. A M4 precisou de quatro.
7. **Reaproveita coreografia existente sem escrever movimento novo.** Nenhum
   `Movement_` novo no arquivo.
8. **Termina apontando para fora.** É o primeiro doc do arco cujo produto final
   é uma flag para outro documento, e não uma cidade de pé.

---

## 12. Divergências entre este plano e o código implementado

**Implementado em 20/09/2026.** Esta seção **vence o resto do arquivo** onde os
dois divergirem. O plano foi executado **inteiro, sem cortes**, nos cinco
arquivos de §6, e **nenhuma decisão de estado mudou**: os valores 10/11/12, a
invariante da flag, `FLAG_TEMP_1` como flag única dos seis, os seis `local_id`
(3-8) no fim de `object_events`, o destino (4,7) do `warpsilent` e a checagem
dupla de espécie saíram exatamente como escritos.

Build: `make -j$(nproc)` limpo. ROM 92,54% / EWRAM 94,28% / IWRAM 73,74% — este
evento não acrescentou gráfico nem dado, só script e seis templates.

### 12.1 Tudo que o plano previu e o código confirmou

Conferido item a item **no checkout**, antes de editar:

| Previsto em | Confirmado |
|---|---|
| §1.1 | `0x1045` livre; `CUSTOM_FLAGS_END` apontava para `FLAG_EVENT_ULTRABEAST_NEWBARK` em `flags.h:1797` |
| §1.1 | A seção `// MAP_OLIVINE_CITY_HOUSE1` já existia com os local ids 1 e 2 |
| §1.3 | O único temporário do mapa era `VAR_TEMP_1`; nenhuma `FLAG_TEMP_*` em uso |
| §2.1 | `dump_mapa.py` reproduziu a planta do plano tile por tile: (2,6), (3,6), (9,6), (2,7), (3,7), (8,7) andáveis, mesa sólida em (5-6, 4-5), warp único em (4,8) |
| §2.2 | Os quatro `OBJ_EVENT_GFX_*` humanos em `event_objects.h:337-340`; `OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)` e `(SILVALLY)` já em uso em outros mapas |
| §4.4 | `checkspecies` existe (`asm/macros/event.inc:2622`), chama `Scrcmd_checkspecies` (`src/scrcmd.c:3298`) → `CheckPartyHasSpecies` (`src/field_specials.c:4422`), que percorre **só** `gPlayerParty`. `SPECIES_SOLGALEO` = 791, `SPECIES_LUNALA` = 792 |
| §4.5 | O `goto_if_ge VAR_RIFT_MISSIONS_STATE, 10` estava lá, nos **dois** scripts de objeto, como o plano avisou |
| §5 | O padrão `fadescreen` + `setflag`/`setvar` + `warpsilent` + `waitstate` + `releaseall` + `end` é literalmente o de `NewBarkTown_EventScript_UBResolved` |

O `grep` obrigatório de §4.5 depois de editar devolveu **exatamente duas** linhas
de código, ambas `, 12,` (`LookerAltar` e `AnabelAltar`). A quarta ocorrência do
erro foi evitada.

`dump_mapa.py` rodado **de novo depois** do `map.json`: os oito objetos saem nos
oito tiles do plano, nenhum em y=8, nenhum em y=2/y=3, nenhum sobre (4,6),
(4,7), (7,6), (7,7), (6,7) ou (5,7).

### 12.2 Divergências de fato

1. **A planta no cabeçalho do `scripts.pory` estava errada desde a M1, e foi
   corrigida junto.** A linha `y=8` do comentário antigo tinha dez células e
   terminava em `. . .`; o `map.bin` tem parede em (0,8) **e** em (10,8), e a
   linha y=9 é parede inteira. O comentário novo traz as duas linhas completas,
   mais y=9. Ninguém tinha medido essa borda porque nenhuma cena chegava perto
   dela; a reunião coloca a Lusamine em (9,6) e o Kukui em (8,7), a dois tiles
   do canto, então passou a importar.

2. **O comentário de `vars.h` foi além do que §1.1 pedia.** O plano mandava
   estender a lista de valores de 4 até 12. O código fez isso **e** escreveu as
   **cinco invariantes** (as quatro flags de missão e a do altar) no mesmo bloco,
   porque as quatro primeiras só existiam espalhadas pelos quatro docs e pelo
   `scripts.pory` de Olivine. É mais barato agora do que na sexta vez.

3. **Os dois textos de stub da M4 foram apagados, não reaproveitados.** §4.5
   dizia que os **rótulos** `LookerReunion` e `AnabelReunion` mudam de
   significado — isso aconteceu. Mas os **textos** que eles usavam
   (`Text_LookerReunionStub` e `Text_AnabelReunionStub`) ficaram órfãos, e a
   skill `encenar-cutscene` manda apagar órfão em vez de deixar para trás. Os
   dois saíram do arquivo.

4. **O `@ SKELETON:` das Beast Balls mudou de lugar.** Ele morava colado em
   `AnabelReunion`, que agora é uma linha só (`goto ..._ReunionScene`). Foi
   reescrito acima do bloco, dizendo explicitamente que este evento **passa pelo
   script da Anabel sem resolver a pendência** — que é o que §9 já registrava.

5. **`ReunionConfirmed` não ganhou o comentário de quatro itens que §5 lista.**
   Os quatro contratos (flag e var colados, ordem do `warpsilent`, destino
   (4,7), o evento acaba aqui) foram escritos como comentários `@` **dentro** do
   bloco, ao lado da linha que cada um governa, em vez de um parágrafo acima
   dele. Mesma informação, mais perto do código que ela protege.

6. **O texto de §5.1 era prosa e virou `.string`.** Quebra em linhas de no
   máximo ~30 caracteres, com `\n` / `\l` / `\p`, no formato das quatro
   briefings do arquivo. Nenhuma fala foi cortada nem reescrita. Caracteres
   conferidos em `charmap.txt` antes de usar: `…` (B0), `“` (B1), `”` (B2) e a
   apóstrofe ASCII, que o arquivo já usa. Nenhum travessão `—` no arquivo
   (`grep` de U+2014 vazio), como a M4 §12.7 exige.

### 12.3 O que a implementação descobriu e o plano não sabia

1. **Não existe `showfollower`.** `asm/macros/event.inc` só tem `hidefollower`
   (`:2646`) e `hidefollowernpc` (`:2860`). O follower volta **exclusivamente**
   no próximo load de mapa. Consequência para este evento, que o plano não
   previu: no ramo do estado 11 (`ReunionNotYet`) **não há `warpsilent`**, então
   o follower fica escondido até o jogador sair da casa. É exatamente o
   comportamento das quatro briefings, mas aqui ele dura mais tempo em tela,
   porque o jogador tende a ficar na sala falando com os seis. **Não é bug de
   estado** (o próximo load conserta), e virou risco de runtime em §9.

2. **`OBJ_EVENT_GFX_SPECIES(...)` no `map.json` não aparece no `grep` do
   `events.inc` pelo nome do mapa.** As duas linhas dos parceiros são geradas
   corretamente, mas só se veem contando `object_event` (8) ou olhando o arquivo
   inteiro. Vale para quem for conferir o próximo evento com muitos parceiros.

3. **O `ON_TRANSITION` novo teve de ser declarado antes do `ON_FRAME_TABLE`** em
   `OlivineCity_House1_MapScripts`, que é a ordem que os outros mapas do arco
   usam. O `.byte 0` terminador continua sendo um só.
