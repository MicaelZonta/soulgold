# Pré-Necrozma — a reunião de Olivine — implementação (roteiro V2)

**Status:** **roteiro V2 implementado** — 26/09/2026. Substituição integral do
conteúdo da reunião do esqueleto (20/09/2026) pelo
[`PRE_NECROZMA_ULTRABEAST_SCRIPT_V2.md`](PRE_NECROZMA_ULTRABEAST_SCRIPT_V2.md):
falas finais, coreografia nova, teste do parceiro em cena, consulta ao PC,
entrega idempotente do passe e pós-game do chá. `make -j$(nproc)` limpo.
**Runtime pendente:** nada deste evento foi jogado (nem o esqueleto).
**Roteiro anterior (histórico):** [`PRE_NECROZMA_ULTRABEAST_SCRIPT.md`](PRE_NECROZMA_ULTRABEAST_SCRIPT.md) —
não descreve mais a cena; o V2 venceu.
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §7.
**Contratos vizinhos:** a máquina de estados 12–16 e a saída de Looker/Anabel
da casa são do doc do Altar
([`ALTAR_SUN_MOON_IMPLEMENTATION.md`](../ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md),
§10.6) e **não mudaram aqui**. A convocação diária
(`RiftMissions_EventScript_LookerCall`, `ShouldDoRiftMissionCall`) é a do V2 de
New Bark e também não mudou: o texto da ligação já era o do V2 desta reunião.

## 0. Resumo do fluxo (V2)

```text
estado 10, SEM convite     casa aberta, só Looker e Anabel; fala de espera
                           (WaitForAltarCall). Visitantes NÃO reunidos.
  └─ ligação diária (FLAG_RIFT_LOOKER_SUMMONS) — já existia, texto do V2
estado 10, COM convite     elenco na sala; entrar pela porta (4,8) encena UMA vez
  └─ CENA: destino e problema ▶ uma saída de verdade ▶ pergunta do parceiro
       ├─ sem Solgaleo/Lunala na equipe ▶ orientação verificada (PC/evolução/
       │    neutra) ▶ estado 11
       ├─ "Not now" no menu (ou B) ▶ estado 11
       └─ elegível ▶ TESTE (parceiro em cena, pulso, luzes) ▶ funções ▶ passe
            ▶ FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED + estado 12 ▶ warpsilent (4,7)
estado 11                  entrar NÃO inicia nada; Looker/Anabel oferecem a
                           retomada (Yes/Not yet) ▶ só elegibilidade + teste
estados 12–15              orientação repetível para o porto
estado ≥16                 dom/sex: família na sala, Lusamine sentada à mesa
                           (setobjectxyperm), textos do chá; Looker/Anabel no altar
```

## 1. Estado — o que o V2 mudou e o que não mudou

**Nenhuma flag persistente nova, nenhuma var nova.** Os valores 10/11/12, a
invariante `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` ⇔ `estado >= 12` (setados
juntos, flag nunca limpa) e a checagem de equipe são os do esqueleto.

| Mudança | Onde | Por quê |
|---|---|---|
| Estado 10 **sem convite** não mostra o elenco | `ApplyReunionVisibility` / `ApplyKukuiVisibility` ganham `ShowReunionCastIfSummoned` / `ShowKukuiIfSummoned` lendo `FLAG_RIFT_LOOKER_SUMMONS` | V2 §2: antes da ligação a base está acessível mas a reunião não existe. A cena limpa a flag do convite, mas muda o estado para 11/12 no mesmo script — nenhum load vê "10 sem convite com elenco" |
| Estado 11 **não** dispara nada na entrada | linha do 11 removida do gatilho de frame; `StageRecheck` apagado | V2 §6: a retomada é oferecida por Looker e Anabel na conversa (`ReunionResume`, menu Yes/Not yet) |
| `FLAG_TEMP_4` = parceiro de cena | `ON_TRANSITION` seta **sempre**; só o teste limpa e só o teste remove | Instância de cena do Pokémon escolhido; flag própria, então `removeobject` nela é seguro e não toca em ninguém |
| Deferimento também registra 11 | `ReunionDeferred` (menu "Not now"/B) e `ReunionNoRoom` | V2 §6: antes de devolver controle por falta do parceiro **ou adiamento**, estado 11 |

Temporários do mapa agora: `VAR_TEMP_1` (trava do gatilho), `FLAG_TEMP_1`
(família), `FLAG_TEMP_2` (Looker/Anabel, do doc do Altar), `FLAG_TEMP_3`
(Kukui), `FLAG_TEMP_4` (parceiro). `VAR_TEMP_2`/`VAR_TEMP_3` são rascunho
dentro de um único run de script (espécie escolhida / resultado do
checkspecies); nada os lê entre visitas. `FLAG_TEMP_E` continua reservada ao
follower.

**Orçamento de objetos: 11/16.** Jogador + follower + Looker + Anabel + 4
visitantes + Ninetales + Silvally + parceiro de cena. Cinco slots livres.

## 2. O parceiro em cena — objeto 9

| Campo | Valor |
|---|---|
| `local_id` | `LOCALID_OLIVINE_HOUSE1_PARTNER` = 9 (`map_event_ids.h`, seção da casa) |
| `graphics_id` | `OBJ_EVENT_GFX_VAR_0` — resolvido de `VAR_OBJ_GFX_ID_0` no spawn |
| posição | (6,7), medida livre no `dump_mapa.py`; sprite 64x64 alcança a linha 6 (colunas 5–7, tudo chão) e **não** sobrepõe a mesa (linhas 4–5) |
| `flag` | `FLAG_TEMP_4`, setada incondicionalmente no `ON_TRANSITION` |

O script seta `VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(SOLGALEO)` ou
`(LUNALA)` **antes** do `addobject` — mesmo mecanismo de
`data/scripts/rival_graphics.inc`. A resolução var→espécie está em
`GetObjectEventGraphicsInfo` (`src/event_object_movement.c:3564-3571`).
`playmoncry` aceita var (`ScrCmd_playmoncry` faz `VarGet`), então o cry usa
`VAR_TEMP_2` com a espécie escolhida.

**Nunca é o follower:** `hidefollower` roda antes do `addobject` em todos os
caminhos (nas encenações e no início do teste, que também serve à retomada sob
`lock`), então o mesmo Pokémon nunca está na sala duas vezes. O follower volta
no load do `warpsilent` final.

## 3. A cena principal (estado 10, uma vez)

`StageReunion`: Looker exclama, o **jogador** entra um tile ((4,8)→(4,7),
`Movement_PlayerEnter`) — Looker e Anabel **ficam na mesa**; os dois avanços
antigos até a porta foram cortados (V2 §3), e o centro da sala fica livre para
o teste. Os movimentos `LookerApproach`/`AnabelApproach`/`*Return` continuam no
arquivo servindo aos quatro briefings.

`ReunionScene`, beats do V2 §4–5 (toda direção mira ator de tile fixo; nada lê
a posição viva do jogador sem guarda):

1. Looker abre (`ReunionOpen`) e indica o mapa na mesa (vira leste).
2. Kukui pega o pico no indicador (exclamação) — `ReunionKukui`.
3. Lillie encara a mãe (leste) — `ReunionLillie`; Lusamine responde com o
   limite do equipamento — `ReunionLusamineEvidence`.
4. Gladion pergunta pela volta — `ReunionGladionPlan`.
5. Lusamine abre o estojo: um passo (9,6)→(9,7), medido livre, e encara o
   estojo ao lado do Kukui (oeste) — `ReunionStabilizer`. Anabel vira leste,
   assume o módulo portátil (`ReunionAnabelReturn`) e mostra a Beast Ball do
   Kurt (`ReunionCapture`) — **a Ball fica com ela** até a captura roteirizada
   do Ato IV do Altar.
6. Liderança: Lusamine vira ao mapa (norte) — `ReunionLusamineCross`; Lillie
   pede os controles — `ReunionLillieBoundary`; pausa (`delay 40`), Lusamine
   olha a filha (oeste) e ensina **uma** coisa concreta —
   `ReunionLusamineControl`; Anabel fecha — `ReunionAnabelLeadership`.
7. Kukui pede o parceiro — `ReunionAsk` — e o script **cai** na elegibilidade.

Equipamento (base + módulo) é **só texto e gesto**: decisão do autor "texto
antes de arte nova" (roteiros V2). Se um dia ganhar asset, entra como evolução
visual sem mexer em estado.

## 4. Elegibilidade e orientação

**O gate não mudou:** `checkspecies SPECIES_SOLGALEO` / `SPECIES_LUNALA`, só
equipe, qualquer um dos dois, Cosmog/Cosmoem não passam. O que o V2 acrescentou
fica **nas bordas** do gate:

- **Os dois presentes** → `dynmultichoice` (Solgaleo / Lunala / Not now),
  `ignoreBPress FALSE`: **B equivale a "Not now"** (`MULTI_B_PRESSED` = 127 cai
  no `goto` final para `ReunionDeferred`). Menu é texto de sistema, sem
  plaquinha.
- **Nenhum presente** → `ReunionGuidance`, consulta **só de leitura** para
  escolher a fala verdadeira, nunca para liberar o teste:
  1. Solgaleo ou Lunala no PC → `ReunionStored` ("Bring ... from the PC");
  2. Cosmog/Cosmoem **confirmado**: na equipe via `CheckMysteryEggPokemon`
     (`src/braille_puzzles.c` — ignora ovo e só responde depois do evento do
     ovo de Violet, ou seja, procedência verificada), ou no PC via o special
     novo → `ReunionUnevolved`;
  3. nada verificável → `ReunionMissing`, a fala neutra.
  Ovo não chocado não prova espécie (V2 §6) e cai de propósito na neutra.

**Special novo:** `CheckPCHasSpecies` (`src/field_specials.c`, registrado em
`data/specials.inc`). Lê `gSpecialVar_0x8004`, varre todas as boxes com
`GetBoxMonData(GetBoxedMonPtr(...), MON_DATA_SPECIES_OR_EGG)` — ovo reporta
`SPECIES_EGG` e não conta. Reutilizável (o Altar §Ato III também consulta
equipe/PC).

**Retomada (estado 11):** `LookerRecheck`/`AnabelRecheck` → `ReunionResume`
(caixa + menu Yes/Not yet, caixa fechada **depois** do menu, padrão do
NewBark). "Yes" → só elegibilidade + teste, sem repetir `ReunionAsk` nem a
discussão. "Not yet"/B → devolve controle, estado intacto.

## 5. O teste (V2 §7) e o fechamento

`ReunionTest`, na ordem:

1. **`checkitemspace ITEM_SUN_MOON_TICKET, 1` antes de qualquer coisa.** É o
   único jeito de a entrega falhar (bolso de Key Items cheio). Falhou →
   `ReunionNoRoom` (texto próprio), estado 11, nada aconteceu. Passou → o
   `giveitem` no fim **do mesmo run** não pode falhar; não existe estado 12 sem
   passe e não existe estado meio-entregue. Este é o mecanismo escolhido para o
   contrato de recuperação do V2 §8 — prevenção no mesmo script em vez de um
   marcador persistente de "teste concluído", que exigiria flag nova para um
   caso que a pré-checagem elimina.
2. `hidefollower`; virada do jogador para (6,7) **guardada por `getplayerxy`**
   (só quando ele está em (4,7), o tile do caminho do gatilho).
3. Flash (`fadescreenswapbuffers`, nunca `fadescreen` — não corrompe o tint de
   horário), `clearflag FLAG_TEMP_4` + `addobject`, flash de volta, cry uma vez.
4. `fadeoutbgm 4` (a pausa do V2), `ReunionTestStart`; o parceiro vira ao
   **módulo** (norte, Anabel em (7,5)); um brilho breve (par de
   `fadescreenswapbuffers`); `fadedefaultbgm`; exclamação do Kukui;
   `ReunionTestResult`. **Nenhuma fenda, nenhum tremor, nenhum tema de
   batalha.**
5. Reação curta: `ReunionGladionPartner` (versão padrão — ver §7),
   `emote_heart` da Lillie (`Movement_LillieHeart`). Sem rodada de elogios.
6. `ReunionAssignments`; Looker volta ao sul e entrega o passe:
   `checkitem` primeiro (**idempotente** — se já existe, não duplica),
   `giveitem ITEM_SUN_MOON_TICKET` (fanfarra padrão, sem plaquinha),
   `ReunionTicketUse`.
7. Recolhe o parceiro (flash + `removeobject` — flag própria), `fadescreen
   FADE_TO_BLACK` (permitido: warp recarrega já em seguida),
   `setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` + `setvar ..., 12` **colados**,
   `warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7` + `waitstate` + `releaseall` +
   `end`. (4,7) não é o warp; o gatilho de frame morre duas vezes no reload.

Looker e Anabel **ficam na base** nos estados 12–15 (orientação repetível
`LookerAltar`/`AnabelAltar`, textos do V2 §10); quem some no reload são os
visitantes. O Altar revalida o parceiro na fenda (`checkspecies` lá), então
guardar o Pokémon depois da reunião não revoga nada.

## 6. Estado 11 e pós-game

- **Ociosas do estado 11** (V2 §9): `IdleLusamine`/`IdleLillie`/`IdleGladion`/
  `IdleKukui` reescritas — preparação, nenhuma informação indispensável.
  Ninetales e Silvally continuam `script: NULL` (V2: a cena está completa
  assim; o cry opcional é evolução).
- **Estado ≥16** (V2 §11): mesmos dois dias do doc do Altar (domingo e sexta,
  `GetDayOfWeek`). `ApplyPostgameSeating` (novo, no `ON_TRANSITION`) move o
  template da Lusamine para **(5,6)** — à mesa, perto dos filhos, olhando a
  Lillie — via `setobjectxyperm`, que edita a cópia RAM do load corrente;
  abaixo de 16 a posição ROM (9,6) fica intacta. Textos novos do chá
  (`HouseLusaminePost`/`HouseLilliePost`/`HouseGladionPost`); a fala antiga do
  Silvally "dormindo sob a mesa" morreu com eles (o sprite nunca esteve lá).
  Bule na mesa **não** representado — "texto antes de arte nova".

## 7. Decisões de implementação (pedido do V2 → como ficou)

| V2 pedia | Como ficou |
|---|---|
| Convocação única integrada a New Bark e ao limite diário | Já existia (`RiftMissions_EventScript_LookerCall`, texto idêntico ao `Phone_Text_LookerAltarInvite`); nada duplicado. Adiar "dentro da base" já estava em `ShouldDoRiftMissionCall` |
| Sem reunião automática antes do convite | Gatilho já era `StageReunionIfCalled`; o V2 acrescentou os **visitantes** não aparecerem antes (gate de summons na visibilidade) |
| Cena principal uma vez; 11 só retomada | Mantido; retomada virou oferta em conversa com menu, e a entrada no 11 não dispara nada |
| Menu SYSTEM Solgaleo/Lunala/Not now; saída de menu devolve controle | `dynmultichoice` com B liberado; B e "Not now" caem juntos em `ReunionDeferred` |
| Equipe e PC separados; Cosmog/Cosmoem não liberam | Gate intacto; PC só orienta (`CheckPCHasSpecies` novo) |
| Parceiro visível, sprite correto, cry, sem follower duplicado | Objeto 9 `OBJ_EVENT_GFX_VAR_0`; `hidefollower` antes do `addobject` em todo caminho |
| Teste sem fenda, resposta limitada | Flashes `fadescreenswapbuffers` + pausa de BGM; resultado é compatibilidade |
| Beast Ball mostrada, retida por Anabel, sem crafting | Só texto (`ReunionCapture`); consistente com o Altar rev. 2 (Ball do Kurt) |
| Passe sem duplicação; falha recuperável sem repetir a reunião | `checkitem` (idempotência) + `checkitemspace` **antes** do teste (prevenção no mesmo run; ver §5 item 1) |
| Callback do Gladion só com procedência verificável | **Versão padrão.** Nenhum campo do save prova qual exemplar saiu do ovo de Violet; a variante "Hard to believe I carried that egg." ficou de fora |
| Emissor/estojo reconhecíveis "ou assets simples" | Texto e gesto; sem asset novo (decisão do autor: texto antes de arte) |
| Bule na mesa "se viável" | Não representado; só nas falas |
| Pós-game nos dias existentes, Lusamine perto da família | Dom/sex do Altar; `setobjectxyperm` para (5,6) |

## 8. Arquivos tocados

| Arquivo | Mudança |
|---|---|
| `data/maps/OlivineCity_House1/scripts.pory` | Reescrita da reunião inteira: visibilidade com gate de summons, `ApplyPostgameSeating`, gatilho sem estado 11, `StageReunion` novo, cena V2, elegibilidade/orientação/retomada/teste, 3 movimentos novos, todos os textos da reunião, ociosas, 12+, ≥16 |
| `data/maps/OlivineCity_House1/map.json` | Objeto 9 (parceiro), `OBJ_EVENT_GFX_VAR_0`, (6,7), `FLAG_TEMP_4`, fim do array |
| `include/constants/map_event_ids.h` | `LOCALID_OLIVINE_HOUSE1_PARTNER` 9 |
| `src/field_specials.c` | `CheckPCHasSpecies` (ao lado de `CheckPartyHasSpecies`) |
| `data/specials.inc` | `def_special CheckPCHasSpecies` |

Nenhuma flag persistente nova, nenhuma var nova, nenhum gráfico novo, nenhuma
batalha. `flags.h` e `vars.h` intactos.

## 9. O que não pode regredir (contrato para evoluções)

- Valores 10/11/12 e a invariante da flag (setados juntos; flag nunca limpa).
- Estado 10 sem `FLAG_RIFT_LOOKER_SUMMONS` = sala sem visitantes **e** sem cena.
- Estado 11 sem diálogo automático na entrada; retomada só por conversa, e
  "Yes" nunca repete a discussão.
- Gate = `checkspecies` na equipe, os dois aceitos, família não conta; PC é
  orientação, nunca gate.
- `FLAG_TEMP_4` setada incondicionalmente no `ON_TRANSITION`; `removeobject`
  só no parceiro (flag própria). Nos outros seis, separar a flag antes.
- `checkitemspace` antes do teste no mesmo run do `giveitem`; `checkitem`
  antes do `giveitem`; estado 12 nunca sem o passe.
- `hidefollower` antes do `addobject` do parceiro em todo caminho.
- Destino do `warpsilent` fora do warp; `fadescreenswapbuffers` (nunca
  `fadescreen`) para flashes que voltam ao mesmo mapa.
- Nenhuma direção derivada da posição viva do jogador sem guarda de
  `getplayerxy`.
- `setobjectxyperm` da Lusamine só em ≥16, recalculado por load.
- Orçamento: 11/16, e o parceiro é o último do array de `object_events`.

## 10. Pendências e riscos

- **Runtime: nada foi jogado.** Riscos visuais que só o jogo mostra: sprite
  64x64 do parceiro em (6,7) sobre os vizinhos; menu sobre caixa aberta na
  retomada; plaquinha × fanfarra do passe.
- **`VAR_OBJ_GFX_ID_0` é compartilhada no projeto** (rival, Battle Tent etc.).
  Seguro porque todo usuário a seta imediatamente antes do spawn — padrão do
  projeto — mas um template de `OBJ_EVENT_GFX_VAR_0` que spawnasse sem setar
  leria valor velho.
- **Follower some no estado 11 até sair da casa** quando o deferimento vem da
  cena longa (o `hidefollower` do `StageReunion` não tem inverso sem load). O
  mesmo comportamento do esqueleto; se incomodar em runtime, `warpsilent` sob
  fade no fim dos ramos de deferimento — nunca estado novo.
- **`CheckMysteryEggPokemon` exige `FLAG_RECEIVED_MYSTERY_EGG`.** Um Cosmog
  obtido fora do evento do ovo (trade/debug) cai na fala neutra, não na de
  evolução. Aceito: a neutra não afirma nada falso.
- **`checkspecies` do gate vê ovo como espécie** (`MON_DATA_SPECIES`). Sem ovo
  legítimo de Solgaleo/Lunala, ninguém passa o gate com ovo — registrado desde
  o esqueleto.
- Os avisos do `checar_falantes.py` sobre `Elm:` em `NewBarkTown_Lab` são
  legado pré-existente, fora do escopo deste evento.

## 11. Teste em runtime

1. Estado < 10: casa só com Looker e Anabel; nada da reunião.
2. **Estado 10 sem convite:** entrar na casa — sala vazia de visitantes,
   nenhum gatilho; Looker diz `WaitForAltarCall`. Sair, receber a ligação
   (dia novo, fora da base), reentrar: elenco completo, cena roda uma vez.
3. Cena: Looker/Anabel ficam na mesa; jogador entra um tile; Lusamine dá o
   passo (9,6)→(9,7) e as viradas batem com o §3; caixa não cobre ninguém.
4. **Sem Solgaleo/Lunala:** (a) com Solgaleo só no PC → fala do PC; (b) com
   Cosmog na equipe (pós-ovo) → fala de evolução; (c) com Cosmog só no PC →
   fala de evolução; (d) sem nada → fala neutra; (e) com ovo não chocado na
   equipe e nada mais → fala neutra. Todos terminam no estado 11.
5. **Com os dois na equipe:** menu aparece; B devolve controle com estado 11;
   cada opção mostra o sprite e o cry **da espécie escolhida**.
6. Estado 11: entrar na casa não dispara nada; falar com os 4 visitantes (uma
   caixa cada); Looker/Anabel oferecem Yes/Not yet; "Yes" vai direto à
   elegibilidade (sem `ReunionAsk`, sem discussão).
7. Teste: flash, sprite correto, cry uma vez, luzes (flash breve), BGM cai e
   volta, exclamação do Kukui, reação do Gladion, coração da Lillie.
8. Passe: fanfarra; estado 12; reload em (4,7); visitantes fora;
   Looker/Anabel em (4,5)/(7,5); follower de volta; `checkitem` no bag.
9. Bolso de Key Items cheio (forçar): fala de "make room", estado 11, nada
   spawnou; retomada funciona depois de abrir espaço.
10. Estados 12–15: orientações repetíveis; sair/voltar não repete nada.
11. Estado ≥16, domingo e sexta: os cinco na sala, **Lusamine em (5,6)**;
    textos do chá; outros dias: sala vazia (Looker/Anabel no altar).
12. Regressões: briefings 2/4/6/8 intactos (movimentos reaproveitados);
    convocação diária dos estados 4/6/8/10; save/reload em 10-com-convite,
    10-sem-convite, 11 e 12, dentro e fora da casa.
