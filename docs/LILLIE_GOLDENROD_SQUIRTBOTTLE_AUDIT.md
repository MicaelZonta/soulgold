# Auditoria: Lillie na Floricultura de Goldenrod (revanche + entrega do SquirtBottle)

Escopo: avaliar o impacto técnico de colocar a Lillie dentro de
`GoldenrodCity_FlowerShop`, assumindo o evento de entrega do SquirtBottle
(hoje feito pela dona da loja, após Whitney), com uma batalha obrigatória
contra ela antes da entrega. **A NPC antiga da loja continua existindo** —
uma nova flag apenas controla se a Lillie aparece dentro da loja e é ela
quem passa a lutar/entregar o item.

Baseado em auditoria de código feita em 2026-09-12, branch
`soulgold-rift-missions`. Todas as referências são `arquivo:linha` no estado
atual do branch. Nada foi implementado ainda — este documento é só o
levantamento de impacto, para orientar a implementação.

Este cenário já está descrito em design em
`.claude/SOULGOLD_RIFT_MISSIONS_DESIGN_V1.md`, seção **4.6 "Lillie em
Goldenrod — revanche e entrega do SquirtBottle"** (linhas 396-424), que pede
explicitamente para reaproveitar o evento existente e "atualizar as falas
de encaminhamento e a antiga NPC entregadora para que apontem para Lillie e
não ofereçam outra cópia". Fora de escopo (conforme o próprio doc, linha
424): o encontro de Gladion em Mahogany, Gladion em Azalea e o próprio
encontro do Sudowoodo em Route 36 — nenhum desses é tocado aqui.

---

## 1. Estado atual do evento (antes de qualquer mudança)

### 1.1 Mapa

- `data/maps/GoldenrodCity_FlowerShop/map.json` — `MAP_GOLDENROD_CITY_FLOWER_SHOP`.
- `data/maps/GoldenrodCity_FlowerShop/scripts.pory` — fonte (poryscript);
  `scripts.inc` é gerado a partir dele, não editar direto.
- **Atenção ao editar este arquivo**: o mesmo `.pory`/`.inc` também concatena,
  num bloco `raw` mais abaixo, os scripts de **outro mapa**,
  `Route104_PrettyPetalFlowerShop` (labels
  `Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl` etc.). Não é
  relacionado ao SquirtBottle, mas é fácil mexer no arquivo errado por engano.

### 1.2 NPCs do mapa (`object_events` do `map.json`)

| # (localId) | graphics_id | x,y | script | flag |
|---|---|---|---|---|
| 1 | `OBJ_EVENT_GFX_GIRL_1` | 2,4 | `GoldenrodCity_FlowerShop_EventScript_Owner` (dona da loja — entrega o item hoje) | `0` (sempre visível) |
| 2 | `OBJ_EVENT_GFX_WOMAN_2` | 10,8 | `Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl` | `0` |
| 3 | `OBJ_EVENT_GFX_ATTENDANT` | 8,3 | `FlowerShopMulchVendor` | `0` |
| 4 | `OBJ_EVENT_GFX_TWIN` | 11,5 | `GoldenrodCity_FlowerShop_EventScript_Floria1` ("Floria", comenta a mesma progressão em texto) | `0` |
| 5 | `OBJ_EVENT_GFX_GIRL_2` | 4,7 | `UniversityFlorist` | `0` |

Nenhum NPC tem `trainer_type` diferente de `TRAINER_TYPE_NONE` hoje (loja sem
treinadores). O `.pory` **não declara nenhum `.set LOCALID_...`** para este
mapa — precisa ser adicionado se a Lillie exigir `applymovement`/`removeobject`
por localId (padrão usado em outras cenas, ver seção 3).

### 1.3 Script de entrega (`GoldenrodCity_FlowerShop_EventScript_Owner`)

`data/maps/GoldenrodCity_FlowerShop/scripts.pory:5-39`:

```
GoldenrodCity_FlowerShop_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
	closemessage
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
	end

GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
	giveitem ITEM_SQUIRTBOTTLE
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
	closemessage
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
	end
```

**Isto é o ponto central do impacto**: hoje, assim que `FLAG_BADGE03_GET`
está setada, a própria dona da loja entrega o item direto, sem nenhuma
batalha. Se a Lillie for adicionada sem mexer nesse `goto_if_set
FLAG_BADGE03_GET, ...GiveSquirtBottle`, o jogador pode simplesmente falar
com a NPC antiga primeiro e pular a Lillie inteira — duplicando o caminho de
entrega e esvaziando a cena nova. Esse branch **precisa ser alterado** (ver
seção 4.2).

Flags usadas nesse script (`include/constants/flags.h`):

| Flag | Valor | Linha | Significado |
|---|---|---|---|
| `FLAG_BADGE03_GET` | `SYSTEM_FLAGS + 0x9` | 1364 | Whitney derrotada (badge 3) |
| `FLAG_RECEIVED_SQUIRTBOTTLE` | `0x394` | 967 | SquirtBottle já entregue (usada em outros mapas, ver seção 5) |
| `FLAG_HIDE_SUDOWOODO` | `0x2E6` | 793 | Sudowoodo já resolvido (Route 36) |
| `FLAG_STARTED_SEASONAL_PERFUME_QUEST` | `SYSTEM_FLAGS + 0x3` | 1356 | Sub-evento não relacionado (perfume), roda depois de qualquer ramo acima |

### 1.4 Script paralelo ("Floria", NPC #4)

`GoldenrodCity_FlowerShop_EventScript_Floria1/2/3` (linhas 80-100) só comenta
a mesma progressão em texto (não entrega item), checando as mesmas flags
`FLAG_HIDE_SUDOWOODO`/`FLAG_BADGE03_GET`. Não precisa mudar para a Lillie
funcionar, mas character-wise ela é "a irmã da moça do SquirtBottle" — texto
não referencia diretamente quem entrega o item, então não quebra.

---

## 2. Infraestrutura já existente para a Lillie

Já pronta e usada em outra cena (`Route30_MrPokemonsHouse`, a cena do
Mystery Egg / Vulpix intro):

- **Gráficos**: `OBJ_EVENT_GFX_LILLIE = 331` (`include/constants/event_objects.h:338`),
  paleta `OBJ_EVENT_PAL_TAG_LILLIE` (`:516`), entradas completas em
  `src/data/object_events/object_event_graphics_info.h:4679` e
  `..._pointers.h:671`, sprites em
  `graphics/object_events/pics/people/special/lillie.*`.
- **Trainer battle**: `TRAINER_LILLIE = 965` (`include/constants/opponents.h:946`),
  classe `TRAINER_CLASS_LASS`, música `TRAINER_ENCOUNTER_MUSIC_HG_GIRL_1`,
  `AI_FLAG_BASIC_TRAINER`, batalha simples.
- **Trainer pic de batalha**: `TRAINER_PIC_FRONT_LILLIE`
  (`src/data/graphics/trainers.h:557`), sprite em
  `graphics/trainers/front_pics/lillie.*`.

### ⚠️ `TRAINER_LILLIE` já está ocupado por outra cena, em outro nível — vai ter um trainer novo

O time atual de `TRAINER_LILLIE` (`src/data/trainers.party:19686-19697`) é:

```
=== TRAINER_LILLIE ===
Name: Lillie
Class: Lass
Pic: Lillie
Music: Hg Girl 1
AI: Basic Trainer

Vulpix Alola
Level: 7
IVs: 0 HP / 0 Atk / 0 Def / 0 SpA / 0 SpD / 0 Spe
```

Esse é o time da cena de abertura em `Route30_MrPokemonsHouse` (nível 7, IVs
0 — condizente com jogador recém-saído de Newbark). Whitney
(`src/data/trainers.party:5113`) tem um time nível 25-27.

**Decisão do time**: haverá um **trainer ID novo** dedicado à revanche de
Goldenrod — `TRAINER_LILLIE` (965) **não é tocado** e continua servindo só a
cena de Route 30.

- ID livre sugerido: `TRAINER_UNUSED_104 = 968`
  (`include/constants/opponents.h:949`), imediatamente após `TRAINER_GLADION`.
  A faixa realmente livre, segundo `.claude/adicionar-batalha-npc.md`, é
  `951-963` e `968-1055` (a faixa `1056-1163` está proibida — flags
  reaproveitadas). Renomear para algo como `TRAINER_LILLIE_GOLDENROD` (ou
  `TRAINER_LILLIE_2`, seguindo o padrão `_1`/`_2` já usado no projeto para
  revanches de líder de ginásio, ex. `TRAINER_WHITNEY_1`/`TRAINER_WHITNEY_2`,
  `trainers.party:5113,5197`).
- A flag de "derrotada" não precisa ser criada manualmente — é derivada
  automaticamente do ID do treinador (`TRAINER_FLAGS_START (0x500) + ID`,
  `include/constants/flags.h:1346`, `src/battle_setup.c:1411`).
- Time da revanche: novo bloco `=== TRAINER_LILLIE_GOLDENROD ===` em
  `src/data/trainers.party`, com Pokémon e nível próprios (o design doc,
  seção 4.6, não especifica — é decisão de balanceamento em aberto, seção 6).
  Como é um ID totalmente separado, não há risco de afetar a cena de
  Route 30 nem depender de nenhuma opção de save para o time "valer".

O projeto também tem um sistema de **level scaling por treinador**
(`src/level_scaling.c`, `src/data/level_scaling_rules.h`,
`gTrainerLevelScalingRules[TRAINERS_COUNT]`) capaz de reescalar nível e até
evoluir a espécie autorada via `.manageEvolutions = TRUE`
(`EvolveSpeciesForLevel`, `src/level_scaling.c:332-369`) — mas ele é opt-in
por save (`gSaveBlock2Ptr->optionsTrainerLevelScaling`, default `OFF` em
`src/new_game.c:132`) e não é necessário aqui: com um trainer ID próprio, a
revanche já nasce com o time/nível corretos sem depender dessa opção. Fica
registrado como um recurso existente no projeto, caso o time queira usá-lo
depois para outra coisa, mas **não é o mecanismo usado nesta implementação**.

---

## 3. Padrão idiomático de referência: Gladion em `VioletCity_PokemonCenter`

É o caso mais próximo já implementado no projeto de "NPC nova assume um
evento de entrega existente, com batalha obrigatória antes, controlada por
flag de visibilidade dedicada" — commit `26bff3ccd9 Gladion added!`.

`data/maps/VioletCity_PokemonCenter/map.json` (object event do Gladion):

```json
{
  "graphics_id": "OBJ_EVENT_GFX_GLADION",
  "x": 9, "y": 4,
  "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
  "trainer_type": "TRAINER_TYPE_NONE",
  "script": "VioletCity_PokemonCenter_EventScript_Gladion",
  "flag": "FLAG_HIDE_VIOLET_CITY_GLADION"
}
```

`data/maps/VioletCity_PokemonCenter/scripts.pory:1-2,8-60` (resumo do fluxo):

```
.set LOCALID_VIOLET_GLADION, 6
...
VioletCity_PokemonCenter_EventScript_Gladion::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, VioletCity_PokemonCenter_EventScript_Gladion_Received
	... (checa espaço no time/PC) ...
	call Common_EventScript_OutOfCenterPartyHeal
	trainerbattle_no_intro TRAINER_GLADION, VioletCity_PokeCenter_Text_GladionVictory
	msgbox VioletCity_PokeCenter_Text_GladionGiveEgg, MSGBOX_DEFAULT
	giveegg SPECIES_COSMOG
	...
	applymovement LOCALID_VIOLET_GLADION, VioletCity_PokemonCenter_Movement_GladionLeave
	waitmovement 0
	removeobject LOCALID_VIOLET_GLADION
	setflag FLAG_RECEIVED_MYSTERY_EGG
	setflag FLAG_HIDE_VIOLET_CITY_GLADION
	release
	end
```

Pontos a copiar para a Lillie:

- `flag` do object event = flag de visibilidade dedicada, setada só no final
  do script (não é a mesma flag de "recebeu o item").
- `trainerbattle_no_intro TRAINER_X, texto_de_vitoria` — sem `lock`/
  `faceplayer` antes da chamada (a engine cuida).
- Cura o time (`call Common_EventScript_OutOfCenterPartyHeal`) antes da
  batalha — equivalente ao pedido do design doc ("curando o time antes da
  batalha", linha 406).
- `applymovement` + `removeobject` no final, usando um `LOCALID_...`
  declarado no topo do `.pory`.
- **Nenhuma checagem de "antes de Falkner"** existe no script do Gladion —
  ele fica visível no Pokémon Center desde o início, e o próprio diálogo
  decide o que fazer. Isso é relevante para a seção 5 abaixo (janela de
  visibilidade da Lillie precisa ser resolvida de outro jeito, porque aqui
  há uma flag de progresso real, `FLAG_BADGE03_GET`, no meio do caminho).

Ver também `docs/GLADION_VIOLET_PLANO_CHECKLIST.md` no histórico do commit
`26bff3ccd9` (`git show 26bff3ccd9~1:docs/GLADION_VIOLET_PLANO_CHECKLIST.md`
— arquivo já removido da árvore de trabalho) para o plano completo dessa
implementação, que documentou decisões similares às que faltam aqui (time,
falas, sequência).

---

## 4. Impactos por arquivo

### 4.1 `data/maps/GoldenrodCity_FlowerShop/map.json`

- Adicionar um **6º `object_event`**: `graphics_id: OBJ_EVENT_GFX_LILLIE`,
  `trainer_type: TRAINER_TYPE_NONE`, `script` novo (seção 4.2), `flag` = nova
  flag de visibilidade (seção 4.3).
- Escolher coordenadas livres dentro da loja (ocupadas hoje: (2,4), (10,8),
  (8,3), (11,5), (4,7) — layout precisa ser conferido no tileset, não
  auditado aqui em detalhe de colisão).
- Adicionar `.set LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, 6` no topo do
  `.pory` (não existe nenhum `.set LOCALID_...` hoje neste mapa).

### 4.2 `data/maps/GoldenrodCity_FlowerShop/scripts.pory` (+ `.inc` gerado)

Dois pontos de mudança:

1. **Novo script da Lillie** (batalha + entrega), no padrão do Gladion:
   cura o time, `trainerbattle_no_intro <NOVO_TRAINER>, <texto_vitoria>`,
   depois `giveitem ITEM_SQUIRTBOTTLE` + `setflag FLAG_RECEIVED_SQUIRTBOTTLE`
   (a mesma flag que a NPC antiga já usa — ver por quê isso importa abaixo),
   `applymovement`/`removeobject` e `setflag <nova_flag_de_visibilidade>`.
   As falas já estão propostas em português/inglês no design doc (seção 4.6,
   linhas 416-422).

2. **Editar `GoldenrodCity_FlowerShop_EventScript_Owner`** — o branch
   `goto_if_set FLAG_BADGE03_GET, ...GiveSquirtBottle` não pode mais levar
   direto à entrega. Precisa passar a checar também a nova flag da Lillie
   (só entrega direto se, por algum motivo, a Lillie já tiver sido resolvida
   e ainda assim `FLAG_RECEIVED_SQUIRTBOTTLE` não estiver setada — cenário
   que não deveria ocorrer se a Lillie sempre entrega ela mesma) ou, mais
   simples, **remover esse branch de entrega direta** e substituí-lo por uma
   fala que direciona o jogador para a Lillie (dentro da própria loja).
   Como a Lillie seta `FLAG_RECEIVED_SQUIRTBOTTLE` ao entregar, o branch
   `goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, ...GotSquirtBottle` (que já existe
   e vem **antes** do branch da badge) continua funcionando sem alteração
   para a conversa "pós-entrega" com a NPC antiga — só o meio do caminho
   (badge 3 batida, item ainda não entregue) precisa de texto novo.

Nenhuma mudança é necessária em `GoldenrodCity_FlowerShop_EventScript_Floria1/2/3`
nem em `Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl` /
`FlowerShopMulchVendor` / `UniversityFlorist` (não dependem dessas flags).

### 4.3 `include/constants/flags.h` — nova flag de visibilidade

Não existe hoje nenhuma flag de "Lillie visível/resolvida no FlowerShop de
Goldenrod". Duas opções:

- **Reaproveitar um slot já livre**: `FLAG_UNUSED_35C` (`flags.h:911`,
  comentário: `// Formerly FLAG_HIDE_NEWBARKTOWN_LAB_AIDE; freed when the
  lab aide stopped being hidden for the Gladion Egg hand-off`). Confirmado
  por grep que **não é referenciada em nenhum script/mapa hoje** — é o
  único slot "freed" disponível na faixa de flags de história (`0x2E0-0x3A0`).
  Renomear para algo como `FLAG_HIDE_GOLDENROD_FLOWER_SHOP_LILLIE`, seguindo
  o padrão de comentário `// Formerly ...` já usado no projeto para manter
  compatibilidade de ID (`flags.h:911,940,941`).
- **Alocar um número novo**, se o time preferir não reciclar esse slot.

Decisão de nome/número é aberta — não escolhi um valor definitivo aqui de
propósito (ver seção 6).

### 4.4 `include/constants/opponents.h` + `src/data/trainers.party`

- Novo `#define TRAINER_LILLIE_GOLDENROD 968` (reciclando
  `TRAINER_UNUSED_104`, ver seção 2), com o time da revanche (espécies/
  nível/composição a decidir, seção 6).
- **Não mexer em `TRAINER_LILLIE` (965)** — continua servindo só
  `Route30_MrPokemonsHouse`, sem qualquer alteração.
- `src/data/trainers.h` é gerado a partir de `trainers.party` via
  `tools/trainerproc` — não editar `trainers.h` direto.

### 4.5 Blocos de "flagheap" que tocam essas mesmas flags

Existem blocos de setflag/clearflag em massa (idioma do projeto, marcado com
comentário `@flagheap`/`@LOCAL FLAGHEAP`) que **já mexem em
`FLAG_RECEIVED_SQUIRTBOTTLE` e `FLAG_HIDE_SUDOWOODO`** e vão precisar
incluir a nova flag da Lillie para não ficarem inconsistentes:

- `data/maps/GoldenrodCity/scripts.pory:11-32`, dentro de
  `GoldenrodCity_EventScript_Trigger` (`@flagheap`) —
  `clearflag FLAG_RECEIVED_SQUIRTBOTTLE` (linha 32).
- `data/maps/VioletCity/scripts.pory:24-39`, dentro de
  `VioletCity_EventScript_Trigger` (`@LOCAL FLAGHEAP`) —
  `clearflag FLAG_HIDE_SUDOWOODO` (linha 34).
- `data/maps/PokemonLeague_HallOfFame/scripts.inc:72-98`, dentro de
  `PokemonLeague_HallOfFame_EventScript_SetGameClearFlags` —
  `clearflag FLAG_HIDE_SUDOWOODO` (linha ~98).

Não investiguei a fundo o gatilho exato desses três blocos (parecem scripts
de "normalização em massa" ao entrar pela primeira vez numa cidade/ao bater
o Hall da Fama, prováveis para suportar pular conteúdo/New Game+ ou estados
de save específicos) — mas o padrão é claro: **toda flag relacionada ao
SquirtBottle/Sudowoodo é replicada nesses três lugares**. Se a nova flag da
Lillie não for adicionada nos mesmos três blocos, um jogador que passe por
esses gatilhos pode ficar com a Lillie escondida para sempre (flag setada
mas nunca limpa) enquanto `FLAG_RECEIVED_SQUIRTBOTTLE`/`FLAG_HIDE_SUDOWOODO`
são resetadas — um estado inconsistente (Sudowoodo "resetado" mas sem
ninguém para reentregar o item, já que a NPC antiga não entrega mais
diretamente).

### 4.6 Consistência narrativa externa (não quebra código, mas vale revisar)

Outros mapas fazem referência textual ao evento sem depender de *quem*
entrega:

- `data/maps/Route36/scripts.pory:344-349` — uma NPC ("hint lady", irmã da
  Floria) diz: *"You beat Whitney? You should go see my sister in the
  Goldenrod Flower Shop! She might lend you a special watering bottle!"*
  (gatilhada por `!flag(FLAG_RECEIVED_SQUIRTBOTTLE)`). Continua correto
  mesmo com a Lillie entregando (ela está fisicamente na floricultura),
  mas o texto assume que é "a irmã" quem empresta — pode valer a pena um
  ajuste de texto por imersão, não é obrigatório.
- `data/maps/Gate_GoldenrodCity_Route35/scripts.pory:59` — só checa
  `FLAG_HIDE_SUDOWOODO`, sem menção a quem entregou. Sem impacto.

---

## 5. Problema técnico a resolver: janela de visibilidade da Lillie

O campo `"flag"` de um `object_event` no `map.json` só expressa **uma**
condição de "esconder quando setada" — ele não expressa nativamente
"aparecer só depois de X e sumir depois de Y" (duas condições). No caso do
Gladion (seção 3) isso não é um problema prático porque não há uma segunda
flag de progresso no meio do caminho: ele fica visível desde o início e o
próprio script decide o que fazer.

Para a Lillie no FlowerShop, existe uma janela real: ela só deveria poder
ser desafiada **depois de `FLAG_BADGE03_GET`** (senão o jogador luta com ela
e recebe o SquirtBottle antes de vencer Whitney, furando a progressão) e
**antes de `FLAG_RECEIVED_SQUIRTBOTTLE`** (depois ela deveria estar
escondida). Como o `map.json` só resolve o "depois" (via `flag` = nova flag
de visibilidade, setada ao final do script dela), o "antes de Whitney"
precisa ser resolvido **dentro do próprio script da Lillie**, com um branch
inicial tipo:

```
goto_if_unset FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Lillie_NotYet
```

levando a uma fala de preenchimento (ela ainda não conseguiu o SquirtBottle
com a florista, sem batalha), similar ao que `GoldenrodCity_FlowerShop_Text_Owner1`
já faz para a NPC antiga hoje. Isso significa que a Lillie fica **visível na
loja o tempo todo** (antes e depois de Whitney), só o diálogo/batalha é que
mudam — que é exatamente o padrão que o Gladion já usa (visível sempre,
lógica no diálogo).

---

## 6. Decisões em aberto (não resolvidas nesta auditoria)

- [ ] Nome e número final da nova flag de visibilidade (recomendação:
  reaproveitar `FLAG_UNUSED_35C`, seção 4.3).
- [x] **Decidido**: novo trainer ID dedicado à revanche —
  `TRAINER_LILLIE_GOLDENROD` (sugestão: reciclar `TRAINER_UNUSED_104 = 968`,
  seção 2/4.4). `TRAINER_LILLIE` (965) não é tocado. Falta decidir:
  - [ ] Time da revanche (espécies, níveis, natureza, IVs/EVs, golpes) —
    o design doc (seção 4.6) só diz "menciona seu treino com Vulpix", sem
    especificar a composição. Balancear contra um jogador recém-saído do
    ginásio de Whitney (nível de referência ~lvl 20-25, ver o próprio time
    de Whitney, `trainers.party:5113`).
  - [ ] Se a Vulpix Alola do design (mesma espécie da cena de Route 30, já
    mais forte/evoluída) continua sendo a protagonista do time novo, ou se
    o time é outra composição — é uma escolha de conteúdo, não técnica.
- [ ] Coordenadas/posição inicial da Lillie dentro da loja e trajeto de
  saída (`applymovement`) — não auditado em nível de colisão/tileset.
- [ ] Texto final da NPC antiga para o meio-do-caminho (badge 3 batida,
  item ainda não entregue pela Lillie) — hoje esse estado não existe
  (a NPC entrega direto); precisa de uma fala nova redirecionando para a
  Lillie.
- [ ] Se vale a pena ajustar o texto da "hint lady" de Route 36 (seção 4.6)
  por imersão — não obrigatório.
- [ ] Investigar o gatilho exato dos três blocos de "flagheap" (seção 4.5)
  antes de replicar a nova flag neles, para confirmar que o comportamento
  esperado (resetar tudo) é o mesmo que se aplica ao caso da Lillie.

---

## 7. Checklist de implementação proposto (nada feito ainda)

- [ ] Criar/renomear flag de visibilidade da Lillie em `include/constants/flags.h`.
- [ ] Criar novo trainer ID em `include/constants/opponents.h` (reciclando
  `TRAINER_UNUSED_104` → `TRAINER_LILLIE_GOLDENROD`) e o time dele em
  `src/data/trainers.party` (`TRAINER_LILLIE` de Route 30 não é tocado).
- [ ] Adicionar `.set LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE` e o 6º
  `object_event` (Lillie) em `data/maps/GoldenrodCity_FlowerShop/map.json`.
- [ ] Escrever o novo script da Lillie em
  `data/maps/GoldenrodCity_FlowerShop/scripts.pory` (branch "antes de
  Whitney", cura de time, `trainerbattle_no_intro TRAINER_LILLIE_GOLDENROD, ...`,
  entrega do item, `applymovement`/`removeobject`, `setflag` da nova flag).
- [ ] Editar `GoldenrodCity_FlowerShop_EventScript_Owner` para remover/
  redirecionar o branch de entrega direta por `FLAG_BADGE03_GET`.
- [ ] Recompilar `.pory` → `.inc` (poryscript) e regenerar `trainers.h` via
  `tools/trainerproc`.
- [ ] Adicionar a nova flag aos três blocos de flagheap (seção 4.5), depois
  de confirmar o gatilho deles.
- [ ] Testar: chegar na loja antes de Whitney (Lillie não deve lutar/entregar);
  bater Whitney e falar com a NPC antiga primeiro (não deve entregar sozinha);
  falar com a Lillie, perder de propósito (cena deve poder repetir); vencer
  (deve entregar o item, sumir, `FLAG_RECEIVED_SQUIRTBOTTLE` setada); voltar
  à loja depois (NPC antiga com o texto de "já entregue", Lillie ausente);
  usar o SquirtBottle em Route 36 normalmente (Sudowoodo não deve notar
  diferença de quem entregou); confirmar que a cena de Route 30 continua
  intacta (nenhum arquivo dela foi tocado).

---

## 8. O que NÃO foi encontrado / não foi auditado

- Nenhuma flag `FLAG_MET_LILLIE` existe no projeto.
- Não foi feita auditoria de colisão/tileset da loja para escolher a
  posição exata da Lillie.
- Não foi auditado o gatilho exato dos três blocos de "flagheap" (apenas a
  presença deles e das flags relevantes dentro).
- Não foi auditado o script do Sudowoodo em si (`Route36`) além dos pontos
  que consomem `FLAG_HIDE_SUDOWOODO`/`ITEM_SQUIRTBOTTLE`/
  `FLAG_RECEIVED_SQUIRTBOTTLE` citados na seção 4.6 — nada ali depende de
  quem entregou o item, só do item em si e da flag.

---

Co-Authored-By: Claude Sonnet 5 <noreply@anthropic.com>
