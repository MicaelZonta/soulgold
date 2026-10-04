# B01 — Goldenrod congela se o rival da Route 34 vier antes da Whitney

**Gravidade:** ALTA (jogo parado; só sai resetando) · **Probabilidade:** alta — é uma ordem natural de jogo
**Tipo:** gatilho de frame sem trava (livelock) · **Status:** CORRIGIDO em 30/09/2026 (build limpo; falta teste no mGBA)

## Sintoma

Jogador vence o rival na Route 34, volta para Goldenrod City sem ter vencido a
Whitney e **não consegue mais andar** ao entrar na cidade. Parece crash, mas
música e animações continuam.

## Onde

- `data/maps/GoldenrodCity/scripts.pory:460-461` (o `.inc` é gerado)

```
Goldenrod_OnFrame::
	map_script_2 VAR_RIVAL_STATE, 6, GoldenrodCity_RivalAfterWhitney
```

- `GoldenrodCity/scripts.pory:565` — `GoldenrodCity_RivalAfterWhitney` só
  avança se `FLAG_DEFEATED_GOLDENROD_CITY_GYM` estiver setada; senão faz `end`
  **sem mudar `VAR_RIVAL_STATE`**.
- `data/maps/Route34/scripts.inc:273` — `setvar VAR_RIVAL_STATE, 6` no fim da
  batalha do rival, sem exigir a insígnia de Goldenrod. O gatilho da Route 34
  é `VAR_RIVAL_STATE == 5` (setado na Route 32), então dá para fazê-lo antes
  do ginásio.

## Por quê

`TryRunOnFrameMapScript` reavalia a tabela todo frame. Com `VAR_RIVAL_STATE == 6`
e a Whitney invicta, a condição fica verdadeira para sempre: o script é
enfileirado todo frame, `ScriptContext_SetupScript` trava os controles e
`PlayerStep` nunca roda (`src/overworld.c`, `DoCB1_Overworld`). É exatamente o
defeito documentado na skill `visibilidade-e-gatilhos` §4 (o antigo
`VAR_GETFLY` de Cianwood).

## Reproduzir

1. Save com `VAR_RIVAL_STATE = 5`, sem a insígnia de Goldenrod.
2. Ir de Goldenrod à Route 34 e pisar no gatilho do rival (y=37). Vencer.
3. Voltar para Goldenrod City → jogador congelado.

## Correção sugerida

Trava por visita com `VAR_TEMP_*`, armada só quando as duas condições valem
(padrão da skill `visibilidade-e-gatilhos` §4). Em `GoldenrodCity/scripts.pory`:

```
GoldenrodCity_OnTransition::            @ já existe: acrescentar
	setvar VAR_TEMP_1, 0
	goto_if_ne VAR_RIVAL_STATE, 6, ...
	goto_if_unset FLAG_DEFEATED_GOLDENROD_CITY_GYM, ...
	setvar VAR_TEMP_1, 1                @ só aqui a cena pode disparar
	...

Goldenrod_OnFrame::
	map_script_2 VAR_TEMP_1, 1, GoldenrodCity_RivalAfterWhitney

GoldenrodCity_RivalAfterWhitney:        @ primeira instrução:
	setvar VAR_TEMP_1, 2
```

Antes: conferir que `VAR_TEMP_1` não é usada por outro script do mapa
(`grep -n VAR_TEMP_ data/maps/GoldenrodCity/scripts.pory` hoje não acha nada).
Testar entrando na cidade nos três estados: antes do rival, rival sem Whitney,
rival com Whitney.
