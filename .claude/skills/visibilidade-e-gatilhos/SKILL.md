---
name: visibilidade-e-gatilhos
description: Use ao fazer um NPC aparecer ou sumir conforme o progresso da historia (addobject, removeobject, campo flag do map.json) ou ao criar um gatilho automatico de mapa (MAP_SCRIPT_ON_FRAME_TABLE, map_script_2, ON_LOAD, ON_TRANSITION). Cobre por que removeobject sozinho nunca segura um NPC escondido, por que ele corrompe flags de terceiros, o padrao de gatilho que trava o jogo, e como usar FLAG_TEMP_* como flag de ocultacao sem gastar flag persistente.
---

# Visibilidade de NPC e gatilhos de mapa

Três armadilhas desta engine, todas silenciosas: o código compila, o
script "roda", e o resultado no jogo é errado ou travado.

## 1. A flag do template é o ÚNICO controle real de visibilidade

O campo `flag` do `object_event` no `map.json` é o que a engine consulta
**toda vez que tenta spawnar** o objeto. `removeobject` via script não
substitui isso.

Motivo: conforme o jogador anda, `UpdateObjectEventsForCameraUpdate`
(`src/event_object_movement.c:3878`) chama `TrySpawnObjectEvents`, que
respawna **qualquer objeto dentro da área visível cuja flag esteja limpa**
(`:3166`), e `RemoveObjectEventsOutsideView` despeja quem sai de vista.
Ou seja: um `removeobject` some com o NPC naquele instante, mas **assim
que a câmera o tirar e trouxer de volta, ele reaparece** — não importa
quantas vezes o seu script o removeu.

> Sintoma clássico: "escondi o NPC mas ele volta quando eu ando pela
> cidade". Não adianta remover mais vezes; tem que ser pela flag.

**Padrão correto** — flag dedicada recalculada a cada carregamento:

```
CianwoodCity_EventScript_InitializeSuicune::       @ MAP_SCRIPT_ON_LOAD
	call CianwoodCity_EventScript_ApplyGladionVisibility
	...

CianwoodCity_EventScript_ApplyGladionVisibility::
	goto_if_unset FLAG_DEFEATED_CIANWOOD_GYM, ..._Hide
	goto_if_set FLAG_RECEIVED_HM_FLY, ..._Hide
	clearflag FLAG_HIDE_CIANWOOD_GLADION
	return
..._Hide::
	setflag FLAG_HIDE_CIANWOOD_GLADION
	return
```

A flag do template é só um **cache** — quem manda são as flags de
progresso reais, relidas todo load. Uma flag dedicada por NPC (ou por
grupo que aparece junto) é o custo mínimo inevitável: o campo aceita
**uma** flag e não sabe inverter nem combinar condições. Se a regra é
"aparece entre A e B", você precisa desse cache.

Mesmo padrão já usado neste repo por Suicune/Eusine em CianwoodCity.

## 2. `removeobject` SETA a flag do objeto removido

`RemoveObjectEventByLocalIdAndMap` (`src/event_object_movement.c:1588`)
faz `FlagSet(GetObjectEventFlagIdByObjectEventId(...))` antes de remover.

Então `removeobject` num objeto cuja flag **significa outra coisa**
corrompe esse estado em silêncio. Exemplos reais em CianwoodCity:

| Objeto | flag | O que `removeobject` estragaria |
|---|---|---|
| Engenheiro | `FLAG_AMPHAROS_HEALED` | marca conquista não relacionada |
| Item ball | `FLAG_CIANWOOD_GOLDEN_BOTTLECAP` | item vira "já coletado", some pra sempre |
| Pedras | `FLAG_TEMP_1/2` | flags de rascunho reusadas pelo jogo inteiro |
| Suicune/Eusine | `FLAG_HIDE_CIANWOOD_*` | quebra o encontro lendário |

**Antes de qualquer `removeobject`, confira a flag do objeto no
`map.json`.** É seguro quando a flag é `0` ou é uma flag dedicada de
esconder daquele NPC. Rode `dump_mapa.py` (skill `encenar-cutscene`), que
já lista a flag de cada objeto.

Para "o NPC entrou no prédio", o padrão da casa é andar até perto da porta
e sumir sob um fade (o tile de porta é sólido e NPC não dispara warp):

```
	applymovement <NPC>, <Movimento ate a porta>   @ termina com face_up
	waitmovement 0
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject <NPC>
	fadescreenswapbuffers FADE_FROM_BLACK
```

## 3. `removeobject` em `ON_LOAD`/`ON_TRANSITION` é no-op silencioso

Ordem real do carregamento de mapa:

1. `RunOnTransitionMapScript()` → `MAP_SCRIPT_ON_TRANSITION`
2. `InitMap()` → `RunOnLoadMapScript()` → `MAP_SCRIPT_ON_LOAD`
   (`src/fieldmap.c:72`)
3. **só então** `InitObjectEventsLocal()` → `TrySpawnObjectEvents()`
   (`src/overworld.c:2551`)

`removeobject` só age sobre o que já está em `gObjectEvents[]`. Nos passos
1 e 2 **nada foi spawnado ainda**, então ele não encontra nada e não faz
nada — sem erro, sem aviso.

| Onde | `setflag`/`clearflag` de visibilidade | `removeobject`/`addobject` |
|---|---|---|
| `ON_TRANSITION`, `ON_LOAD` | ✅ é o lugar certo (antes do spawn) | ❌ no-op |
| `ON_FRAME_TABLE`, script de NPC | ✅ funciona | ✅ funciona (já spawnado) |

## 4. O gatilho de frame que trava o jogo

`MAP_SCRIPT_ON_FRAME_TABLE` é reavaliado **todo frame** por
`TryRunOnFrameMapScript` (`src/script.c:410`). E só enfileirar o script já
trava os controles: `ScriptContext_SetupScript` chama
`LockPlayerFieldControls` (`src/script.c:287`), e em `DoCB1_Overworld`
(`src/overworld.c:1587`) o `PlayerStep` só roda nos frames em que **nenhum**
script foi disparado.

Consequência: se a condição do `map_script_2` for verdadeira **durante boa
parte do jogo**, ela dispara todo frame, os controles são retravados todo
frame, e `PlayerStep` nunca roda. O jogador congela ao entrar no mapa —
parece crash, mas é livelock.

> Foi exatamente isso que `map_script_2 VAR_GETFLY, 0, ...` causou:
> `VAR_GETFLY == 0` é o estado padrão do jogo inteiro antes do ginásio.

**Nunca** condicione um gatilho de frame direto numa flag/var de progresso
de longa duração. Use uma `VAR_TEMP_*` como trava de uma-vez-por-visita,
zerada no `ON_TRANSITION`, e marque-a como **primeira instrução** do script:

```
CianwoodCity_OnFrame::
	map_script_2 VAR_TEMP_1, 0, CianwoodCity_EventScript_GladionAutoTrigger
	.2byte 0

CianwoodCity_EventScript_CityEnter::          @ ON_TRANSITION
	setvar VAR_TEMP_1, 0
	...

CianwoodCity_EventScript_GladionAutoTrigger::
	setvar VAR_TEMP_1, 1                      @ primeira coisa: para de disparar
	goto_if_unset FLAG_DEFEATED_CIANWOOD_GYM, ..._End
	goto_if_set FLAG_RECEIVED_HM_FLY, ..._End
	lockall
	...
```

Uma trava dentro do script não basta: a condição do `map_script_2` é
avaliada **fora** dele, sem saber do estado interno. A variável da própria
condição é que precisa mudar.

## 5. Reuse flags de progresso existentes

Antes de criar flag nova, procure uma que já signifique aquilo:

```bash
grep -rn "FLAG_RECEIVED_HM_\|FLAG_DEFEATED_.*_GYM" include/constants/flags.h
```

`FLAG_DEFEATED_<CIDADE>_GYM` e `FLAG_RECEIVED_HM_<HM>` já existem para
todos os ginásios/HMs. Flag nova só para o **cache de visibilidade** da
seção 1, e no fim do bloco `CUSTOM_FLAGS`, atualizando `CUSTOM_FLAGS_END`.

## 6. NPC preso a um único mapa: `FLAG_TEMP_*` como cache, sem flag nova

Se o NPC só existe **num mapa** e **num valor de var** (ex.: Lillie no
Shrine só quando `VAR_BLACKTHORN_CITY_STATE == 2`), o cache da seção 1 não
precisa de flag persistente. Use uma `FLAG_TEMP_*` e recalcule no
`ON_TRANSITION`:

```
DragonsDen_Shrine_OnTransition::
	call_if_eq VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_EventScript_ShowLillie
	call_if_ne VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_EventScript_HideLillie
	end
```

(`ShowLillie` = `clearflag FLAG_TEMP_1`, `HideLillie` = `setflag FLAG_TEMP_1`;
`"flag": "FLAG_TEMP_1"` nos objetos do `map.json`.)

Por que é seguro:

- `ClearTempFieldEventData()` (`src/event_data.c:60`) zera **todas** as
  `FLAG_TEMP_*` e `VAR_TEMP_*` a cada carregamento de mapa. Isso acontece nas
  duas rotas, warp e troca de mapa por borda (`LoadMapFromWarp` e
  `LoadMapFromCameraTransition`, `src/overworld.c`), **antes** do
  `RunOnTransitionMapScript()`. O seu `ON_TRANSITION` sempre parte do zero.
- `ON_TRANSITION` roda antes do spawn (seção 3), então o `setflag` vale para
  o primeiro spawn.
- O `removeobject` da saída seta a própria `FLAG_TEMP_*` (seção 2), o que é
  inofensivo porque a flag não significa nada fora desse mapa.

Antes de escolher o número, confira que nenhum script do mapa ou script
comum chamado nele usa a mesma temp:

```bash
grep -rn "FLAG_TEMP_<N>\b" data/maps/<Mapa>/ data/scripts/ src/*.c
```

(`FLAG_TEMP_2` é usada por `data/scripts/contest_hall.inc` e
`interview.inc`.)

Não serve quando o NPC aparece em **mais de um mapa** pelo mesmo estado, nem
quando o estado precisa sobreviver a sair e voltar sem ser recalculado.
Nesses casos use flag dedicada (seção 1).

**Mesma ideia para marcas de "já mostrei esta fala nesta visita":** o
script não tem operação bitwise (só `setvar`/`addvar`/`subvar`/`copyvar`),
então não dá para montar bitmask num `VAR_TEMP_*`. Use uma `FLAG_TEMP_*`
por marca, com `goto_if_set`/`setflag`. Exemplo: as seis reações rejeitadas
do quiz em `DragonsDen_Shrine/scripts.inc` (`FLAG_TEMP_2..7`).

## Checklist

- [ ] Todo NPC que precisa sumir por progresso tem `flag` própria no `map.json`
      (ou uma `FLAG_TEMP_*` recalculada no `ON_TRANSITION`, se ele é de um mapa só — seção 6)
- [ ] Essa flag é recalculada no `ON_LOAD` a partir das flags de progresso reais
- [ ] Conferi a flag de cada objeto antes de `removeobject` nele
- [ ] Nenhum `removeobject`/`addobject` em `ON_LOAD`/`ON_TRANSITION`
- [ ] Nenhum `map_script_2` condicionado a estado de longa duração
- [ ] Gatilho de frame marca a var da própria condição na primeira instrução
- [ ] Testei entrando no mapa **antes** e **depois** do evento, e revisitando
