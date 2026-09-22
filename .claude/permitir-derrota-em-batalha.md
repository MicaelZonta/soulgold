# Como fazer uma batalha que continua em vitória OU derrota

Guia derivado da revanche da Lillie na floricultura de Goldenrod
(`docs/LILLIE_GOLDENROD_REFINAMENTO_COMPLETO_V5.md`,
`data/maps/GoldenrodCity_FlowerShop/scripts.pory`).

Complementa [`adicionar-batalha-npc.md`](adicionar-batalha-npc.md) — aquele
guia cobre o caso padrão, onde **perder para um `trainerbattle_*` sempre
causa blackout e para o script ali** (ele mesmo diz isso: "é o comportamento
desejado numa cutscene"). Este guia é para o caso oposto: uma batalha de
treino/história onde **ganhar ou perder deve levar ao mesmo desfecho**
(entregar um item, liberar uma rota, etc.), só variando o texto.

> Não confunda com "rebatalhável" (`cleartrainerflag`, já coberto no outro
> guia). Aqui o problema é **não travar/dar blackout na primeira derrota**,
> não permitir lutar de novo depois.

---

## O problema

Por padrão, perder um `trainerbattle_single`/`trainerbattle_no_intro` chama
o callback de derrota do jogo (mostra o mapa entrando em blackout, manda
pro Pokémon Center mais próximo e cobra a penalidade de dinheiro) **antes**
de qualquer script seguinte rodar. Não dá pra simplesmente colocar
`msgbox` de derrota depois do `trainerbattle` — ele nunca é alcançado.

## A solução: `B_FLAG_NO_WHITEOUT` + `GetBattleOutcome`

```
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_5, VAR_RESULT          @ lembra se já estava ligada
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_X, Text_DerrotaDoNPC
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT          @ salva ANTES de qualquer outra chamada
	goto_if_eq VAR_TEMP_5, TRUE, EventScript_NaoDesligaWhiteout
	clearflag B_FLAG_NO_WHITEOUT
EventScript_NaoDesligaWhiteout::
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, EventScript_Venceu
	goto_if_eq VAR_TEMP_3, B_OUTCOME_LOST, EventScript_Perdeu
	goto_if_eq VAR_TEMP_3, B_OUTCOME_DREW, EventScript_Empate
	goto_if_eq VAR_TEMP_3, B_OUTCOME_FORFEITED, EventScript_Desistiu
	goto EventScript_ResultadoInesperado
```

- `B_FLAG_NO_WHITEOUT` (`include/config/battle.h:266`, é `FLAG_NO_WHITEOUT`)
  faz o jogador **não** ser mandado pro Center ao perder — mas **não cura o
  time sozinho**, o comentário do próprio config avisa disso. Cure antes E
  depois do `trainerbattle` você mesmo (`call
  Common_EventScript_OutOfCenterPartyHeal`).
- `GetBattleOutcome` é `special`, não macro pronta: `specialvar VAR_RESULT,
  GetBattleOutcome`. Os valores (`include/constants/battle.h:145-155`):
  `B_OUTCOME_WON`, `B_OUTCOME_LOST`, `B_OUTCOME_DREW`, `B_OUTCOME_RAN`,
  `B_OUTCOME_FORFEITED`, etc. Trate qualquer valor fora dos que você espera
  (ex.: `B_OUTCOME_RAN`/link battle) como uma saída defensiva — cura,
  restaura música/controles, mas **não** dá a recompensa. Nunca vire
  `B_OUTCOME_LOST` em vitória por omissão.
- **Salve `VAR_TEMP_3` logo após o `specialvar`**, antes de chamar
  `Common_EventScript_OutOfCenterPartyHeal` ou qualquer outro `special` —
  eles podem reescrever `VAR_RESULT`.
- **Preserve o estado anterior da flag.** Se `B_FLAG_NO_WHITEOUT` já
  estivesse ligada por algum outro motivo ao entrar no script (raro, mas
  possível), desligar sem checar apaga esse estado alheio. Salve com
  `checkflag`+`copyvar` antes, e só desligue se não estava ligada antes.
- O texto passado como `lose_text` do `trainerbattle_no_intro` **sempre
  aparece automaticamente quando o NPC perde** (é a fala embutida do motor
  de batalha) — não é opcional e não dá pra pular. Escreva-o como a
  primeira linha do desfecho de vitória do jogador, não como um texto solto.
- O jogo volta sozinho pra música que tocava antes da batalha; se você quer
  uma música específica tocando logo após (ex.: retomar o tema de uma
  cutscene), dê um `playbgm <MUS>, TRUE` explícito depois do
  `specialvar`/`copyvar` — não assuma que o que tocava antes do
  `trainerbattle` volta a tocar por conta própria em todos os casos.

---

## Item que só pode ser entregue com espaço na Bag

Quando a cena cura o time e/ou dá um item de recompensa **antes** de deixar
o jogador ir embora, cheque a Bag **antes de travar a cena com `lockall`**:

```
	checkitemspace ITEM_X, 1
	goto_if_eq VAR_RESULT, FALSE, EventScript_SemEspaco
	... (cura, batalha, entrega) ...

EventScript_SemEspaco::
	msgbox Text_VoltaComEspaco, MSGBOX_DEFAULT
	closemessage
	releaseall             @ NÃO lockall sem soltar depois — libera saída
	end
```

`checkitemspace itemId, quantity` (padrão `quantity=1`) seta `VAR_RESULT =
FALSE` quando **não** há espaço — é fácil trocar o sentido do
`goto_if_eq` de cabeça pra baixo, confira sempre contra o comentário do
macro (`asm/macros/event.inc:555`). Nunca cure nem inicie a batalha antes
dessa checagem: se a entrega falhar por Bag cheia, o jogador não pode ter
gastado um Full Heal à toa.

`giveitem` já reflete o mesmo `VAR_RESULT` (`TRUE`/`FALSE`) — mesmo tendo
checado antes, trate uma falha aqui como caso excepcional (mensagem +
`releaseall`, sem perder o progresso já feito) em vez de around assumir que
nunca acontece.

---

## Estado "desta visita" sem criar flag nova

Uma cena que pode ser interrompida (Bag cheia) e retomada na mesma visita
precisa de scratch state, mas **`VAR_TEMP_0`–`VAR_TEMP_F` são globais e
outros mapas reaproveitam os mesmos números** (`GoldenrodCity_GameCorner` e
`BattleFrontier_BattleTowerBattleRoom` já usam `VAR_TEMP_2`, por exemplo).
Se o jogador visitar outro mapa que deixa `VAR_TEMP_2` != 0 e depois entrar
no seu mapa, um `coord_event` com `"var_value": "0"` pode nunca disparar —
ou, pior, disparar errado se o valor coincidir.

A solução é resetar o scratch state **toda vez que o mapa é carregado**,
não confiar no valor residual:

```
MeuMapa_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MeuMapa_OnTransition
	.byte 0

MeuMapa_OnTransition::
	setvar VAR_TEMP_2, 0    @ 0 = ainda não abordou o jogador nesta visita
	setvar VAR_TEMP_3, 0    @ resultado da batalha, capturado após GetBattleOutcome
	setvar VAR_TEMP_4, 0    @ 1 = treino aceito, entrega pendente
	end
```

Isso também resolve "sair do mapa e voltar" de graça: qualquer estado
intermediário (aproximação já feita, batalha aceita) é descartado ao
recarregar, sem precisar de nenhum código de reset manual — mesma lógica
que `encenar-evento.md` já descreve para o `MAP_SCRIPT_ON_FRAME_TABLE`
reiniciar cutscenes após um blackout, só que aqui é **intencional a cada
entrada**, não só após perder.

`MAP_SCRIPT_ON_TRANSITION` roda ao entrar por warp; não é o mesmo gancho
do `MAP_SCRIPT_ON_FRAME_TABLE` (que reavalia uma `VAR_*` a cada frame
enquanto o mapa está aberto — use os dois juntos se a cena também precisa
retomar sozinha depois de um blackout de verdade em outra parte do fluxo).

---

## Registrar um `local_id` novo sem bagunçar `map_event_ids.h`

`include/constants/map_event_ids.h` é **gerado** (`mapjson event_constants`,
ver `map_data_rules.mk`) a partir do campo `"local_id"` de todos os
`map.json` do jogo — não é um arquivo pra escrever `.set` à mão dentro do
`.pory`. No `map.json` do seu mapa:

```json
{ "local_id": "LOCALID_MEUMAPA_LILLIE", "graphics_id": "OBJ_EVENT_GFX_LILLIE", ... }
```

O valor numérico vira automaticamente a posição (1-based) desse objeto no
array. Para conferir o valor sem rodar o build inteiro:

```bash
tools/mapjson/mapjson map emerald data/maps/<Mapa>/map.json data/layouts/layouts.json data/maps/<Mapa>
tools/poryscript/poryscript -i data/maps/<Mapa>/scripts.pory -o data/maps/<Mapa>/scripts.inc \
  -fc tools/poryscript/font_config.json -cc tools/poryscript/command_config.json
make src/data/trainers.h   # só se você também mexeu em trainers.party
```

> ⚠️ **Não rode `tools/mapjson/mapjson event_constants emerald $(find data/maps
> -name map.json) include/constants/map_event_ids.h` na mão.** A ordem dos
> arquivos que o `find` devolve **não é a mesma** que o `$(wildcard ...)` do
> Makefile usa — o resultado é tecnicamente correto, mas reordena o arquivo
> inteiro e gera um diff gigante e espúrio em blocos de outros mapas que
> você nem tocou. Prefira editar `map_event_ids.h` à mão, no mesmo estilo
> alfabético que ele já usa (é só um bloco `// MAP_X` + `#define
> LOCALID_...`), e deixar a próxima `make` completa confirmar que bate.

---

## Falas com mais de um personagem sem mugshot

O prefixo `Nome: ` **não é "sempre que for Gladion/Kukui/Lillie"** — é
"sempre que a cena tem mais de um falante possível e não é óbvio quem é
quem". O teste é sobre a cena, não sobre o personagem:

- **Um NPC só, `lock`/`faceplayer` normal → sem prefixo.** É o padrão do
  resto do jogo (`GoldenrodCity_FlowerShop_Text_Owner1..4`, `Text_Floria`)
  e vale igual pros três: a cena do Gladion/Mystery Egg em
  `VioletCity_PokemonCenter/scripts.pory`
  (`VioletCity_PokeCenter_Text_GladionRecognizes`,
  `_GladionPartner1/2`, `_GladionVictory`, `_GladionGiveEgg`...) **não** tem
  `Gladion:` em nenhuma linha, porque só ele fala ali. Não adicione o
  prefixo numa cena dessas só porque "é o Gladion" — ficaria redundante e
  inconsistente com o resto do arquivo.
- **Duas ou mais NPCs conversando entre si na mesma cena** (nenhuma delas
  é só "o jogador falando com alguém") → prefixe quem não é óbvio, como
  `MrPokemonHouse_Text_Intro4` (`"Kukui: And this is Lillie.$"`, com Kukui
  *e* Oak *e* Lillie na cena) ou a cena nova da Lillie em Goldenrod
  (Lillie *e* a florista). É fácil esquecer o prefixo quando um dos lados
  fala pouco e parece "implícito" — por isso o teste é útil aqui,
  não no caso de um falante só.

Teste rápido antes de fechar o texto de uma cena com 2+ falantes (já é
regra editorial em `.claude/SOULGOLD_RIFT_MISSIONS_DESIGN.md`, seção
3.3): tirando a identificação do falante, a escolha de palavras ainda dá
pra saber quem fala? Se não, ou falta o prefixo, ou a fala está genérica
demais.

---

## Checagem final antes de fechar a task

- [ ] `B_FLAG_NO_WHITEOUT` é ligada logo antes do `trainerbattle_*` e
      desligada logo depois — nunca fica ligada numa saída da cena.
- [ ] Estado anterior da flag foi salvo e restaurado, não sobrescrito.
- [ ] `VAR_TEMP_3` (ou similar) captura `GetBattleOutcome` **antes** de
      qualquer outro `special`/`call` que possa mexer em `VAR_RESULT`.
- [ ] Todo `B_OUTCOME_*` que você não trata explicitamente cai numa saída
      defensiva (cura, restaura música/controles, sem recompensa).
- [ ] `checkitemspace` roda antes de curar/lutar, não depois.
- [ ] Scratch state (`VAR_TEMP_*`) é resetado no `MAP_SCRIPT_ON_TRANSITION`
      do mapa, não assumido como zerado.
- [ ] `local_id` novo declarado no `map.json`, não com `.set` manual no
      `.pory` nem regenerando `map_event_ids.h` inteiro pelo `find`.
- [ ] Prefixo `Nome:` só nas cenas com 2+ falantes; cena de um NPC só
      (mesmo sendo Gladion/Kukui/Lillie) fica sem prefixo, igual ao resto
      do arquivo.
- [ ] `make` limpo, e o diff final só toca os arquivos do seu mapa/trainer
      (nenhum outro `map_event_ids.h`/mapa reordenado de graça).
