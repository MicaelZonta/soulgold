# B04 — Casa do Kukui na Route 30 (mapa `Route30_MrPokemonsHouse`): bolsa cheia repete a cena do Mystery Egg (com a batalha da Lillie)

**Gravidade:** MÉDIA · **Probabilidade:** muito baixa (bolso de Key Items cheio no início do jogo)
**Tipo:** gatilho de frame que termina sem avançar a var · **Status:** CORRIGIDO em 30/09/2026 (build limpo; falta teste no mGBA)

## Onde

`data/maps/Route30_MrPokemonsHouse/scripts.inc:33` (gatilho
`VAR_CHERRYGROVE_CITY_STATE == 1`) e `:154-155`:

```
	giveitem ITEM_MYSTERY_EGG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
```

`ShowBagIsFull` faz `release; end` e a var continua 1: no frame seguinte a cena
recomeça do zero, incluindo a batalha contra a Lillie. O comentário do próprio
script (linha 37-39) diz que a var só vira 2 no fim — este é o único caminho que
não chega lá.

## Correção sugerida

`checkitemspace ITEM_MYSTERY_EGG` no começo da cena (antes do primeiro
diálogo); sem espaço, uma fala curta do Kukui pedindo para liberar espaço e
`setvar` numa `VAR_TEMP_*` de trava por visita, para o gatilho não repetir até
o jogador sair e voltar.
