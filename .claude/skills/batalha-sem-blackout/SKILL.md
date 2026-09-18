---
name: batalha-sem-blackout
description: Use quando uma batalha de historia precisa continuar em vitoria E em derrota, sem blackout nem penalidade - batalha de treino, rival que entrega um item de qualquer jeito, cena que nao pode travar se o jogador perder. Cobre B_FLAG_NO_WHITEOUT, GetBattleOutcome e os 4 resultados, checkitemspace antes de entregar item, estado por visita com VAR_TEMP sem criar flag, e registrar local_id novo sem sujar map_event_ids.h.
---

# Batalha que continua em vitória ou derrota

Guia completo, derivado da revanche da Lillie em Goldenrod:
**[`.claude/permitir-derrota-em-batalha.md`](../../permitir-derrota-em-batalha.md)**.

Para a batalha padrão (perder = blackout, que é o certo na maioria dos
casos), use a skill `adicionar-batalha-npc`.

## O problema

Por padrão, perder um `trainerbattle_*` chama o callback de derrota
(blackout, volta pro Centro, cobra dinheiro) **antes** de qualquer script
seguinte. Um `msgbox` de derrota depois do `trainerbattle` **nunca é
alcançado**.

## O padrão

```
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_5, VAR_RESULT          @ lembra se JA estava ligada
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_X, Text_DerrotaDoNPC
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT          @ salva ANTES de qualquer outra chamada
	goto_if_eq VAR_TEMP_5, TRUE, ..._NaoDesligaWhiteout
	clearflag B_FLAG_NO_WHITEOUT
..._NaoDesligaWhiteout::
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, ..._Venceu
	goto_if_eq VAR_TEMP_3, B_OUTCOME_LOST, ..._Perdeu
	goto_if_eq VAR_TEMP_3, B_OUTCOME_DREW, ..._Empate
	goto_if_eq VAR_TEMP_3, B_OUTCOME_FORFEITED, ..._Desistiu
	goto ..._ResultadoInesperado
```

Três detalhes que não podem ser cortados:

1. **Salve o estado anterior de `B_FLAG_NO_WHITEOUT`** e só limpe se estava
   limpo. Limpar incondicionalmente desliga a flag de quem a ligou antes.
2. **Copie `GetBattleOutcome` imediatamente**, antes de cura, música ou
   qualquer outra chamada — `VAR_RESULT` é reciclado por tudo.
3. **Trate os 4 resultados** + um ramo de inesperado. `B_OUTCOME_DREW` e
   `B_OUTCOME_FORFEITED` acontecem de verdade.

## Entregar item: `checkitemspace` antes, confirmar depois

```
	checkitemspace ITEM_X, 1
	goto_if_eq VAR_RESULT, FALSE, ..._SemEspaco
	...
	giveitem ITEM_X
	goto_if_eq VAR_RESULT, FALSE, ..._Falhou
	setflag FLAG_<entregue>      @ só DEPOIS de confirmar
```

Marque o progresso **só depois** do `giveitem` confirmar. E prefira checar
o espaço **antes da cena longa**, não no fim — assim a bolsa cheia não faz
o jogador assistir tudo pra não receber nada.

## Estado "desta visita" sem criar flag

`VAR_TEMP_*` zerado no `MAP_SCRIPT_ON_TRANSITION` dá estado por visita sem
gastar flag persistente. Útil para fase da cena e para o resultado da
batalha. Zere no `ON_TRANSITION`, não confie no valor de entrada.

> Cuidado: `VAR_TEMP_*` é global e reusado pelo jogo inteiro. Ele serve
> para estado que vive **dentro de uma visita**, nunca para progresso.

## `local_id` novo sem sujar `map_event_ids.h`

`include/constants/map_event_ids.h` é **gerado** a partir do `"local_id"`
de todos os `map.json`. O valor é a posição (1-based) do objeto no array.

> ⚠️ **Não rode `mapjson event_constants` com `$(find data/maps -name
> map.json)` na mão.** A ordem do `find` difere do `$(wildcard)` do
> Makefile: o resultado é correto mas **reordena o arquivo inteiro**,
> gerando um diff gigante em mapas que você nem tocou. Edite
> `map_event_ids.h` à mão no estilo alfabético existente e deixe a `make`
> completa confirmar.

Para regenerar só o seu mapa:

```bash
tools/mapjson/mapjson map emerald data/maps/<Mapa>/map.json data/layouts/layouts.json data/maps/<Mapa>
```

## Checklist

- [ ] Estado anterior de `B_FLAG_NO_WHITEOUT` salvo e restaurado, não limpo à força
- [ ] `GetBattleOutcome` copiado imediatamente após o `trainerbattle`
- [ ] Os 4 resultados tratados + ramo de inesperado
- [ ] `checkitemspace` antes da cena; progresso marcado só após `giveitem` confirmar
- [ ] `VAR_TEMP_*` da cena zerados no `ON_TRANSITION`
- [ ] Testei **perdendo** de propósito: sem blackout, sem penalidade, cena conclui
- [ ] Testei empate/desistência se forem alcançáveis
