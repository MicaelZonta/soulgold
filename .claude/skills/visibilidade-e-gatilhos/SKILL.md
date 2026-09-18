---
name: visibilidade-e-gatilhos
description: Use ao fazer um NPC aparecer ou sumir conforme o progresso da historia (addobject, removeobject, campo flag do map.json) ou ao criar um gatilho automatico de mapa (MAP_SCRIPT_ON_FRAME_TABLE, map_script_2, ON_LOAD, ON_TRANSITION). Cobre por que removeobject sozinho nunca segura um NPC escondido, por que ele corrompe flags de terceiros, e o padrao de gatilho que trava o jogo.
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

## Checklist

- [ ] Todo NPC que precisa sumir por progresso tem `flag` própria no `map.json`
- [ ] Essa flag é recalculada no `ON_LOAD` a partir das flags de progresso reais
- [ ] Conferi a flag de cada objeto antes de `removeobject` nele
- [ ] Nenhum `removeobject`/`addobject` em `ON_LOAD`/`ON_TRANSITION`
- [ ] Nenhum `map_script_2` condicionado a estado de longa duração
- [ ] Gatilho de frame marca a var da própria condição na primeira instrução
- [ ] Testei entrando no mapa **antes** e **depois** do evento, e revisitando
