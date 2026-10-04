# B03 — Casa do Kurt: bolsa de Poké Balls cheia prende o jogador numa cena em laço

**Gravidade:** ALTA (preso até resetar) · **Probabilidade:** baixa (bolso de Balls cheio)
**Tipo:** gatilho de frame + `goto` para rotina com `return` · **Status:** CORRIGIDO em 30/09/2026 (build limpo; falta teste no mGBA)

## Sintoma

Ao voltar do Slowpoke Well, Kurt entrega uma Fast Ball. Se ela não couber, o
jogo mostra "bag is full" e a cena **recomeça imediatamente**, para sempre.

## Onde

`data/maps/AzaleaTown_KurtsHouse/scripts.pory:13` e `:116-122`

```
AzaleaTown_KurtsHouse_OnFrame::
	map_script_2 VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell

AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
	lock
	...
	giveitem ITEM_FAST_BALL
	setflag FLAG_DAILY_KURT_FREE_BALLS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
```

## Por quê

Dois defeitos juntos:

1. `Common_EventScript_BagIsFull` (`data/event_scripts.s:754`) termina em
   `return`. Chegando por `goto`, a pilha está vazia e o `return` só encerra o
   script — **sem `release`**. (A versão para `goto` é
   `Common_EventScript_ShowBagIsFull`, que tem `release; end`.)
2. `VAR_AZALEA_TOWN_STATE` continua 3, então o gatilho de frame dispara de novo
   no frame seguinte.

## Correção sugerida

Checar espaço **antes** da cena (`checkitemspace ITEM_FAST_BALL`) e, se não
couber, avançar o estado mesmo assim e deixar a Fast Ball para a próxima
conversa com o Kurt; ou avançar `VAR_AZALEA_TOWN_STATE` antes do `giveitem`.
Em qualquer caso, trocar o `goto` por `Common_EventScript_ShowBagIsFull`.
Note também que `FLAG_DAILY_KURT_FREE_BALLS` é setada antes de saber se a Ball
entrou.
