---
name: diagnosticar-flag
description: Use quando algo controlado por flag nao acontece no jogo apesar do build limpo - a cena nao dispara, o NPC nao some nem volta, o presente sai duas vezes, a batalha continua capturavel, o item reaparece, o "ja fiz isso" nao e lembrado. Cobre as seis causas silenciosas: flag espelho de config (B_FLAG_/I_FLAG_/OW_FLAG_) em vez da flag crua, flag setada que ninguem le, flag lida que ninguem seta, flag com valor fora do array de save, flag de template do map.json que nenhum script escreve, e flag que so vive em mapa fora da ROM. Use tambem para investigar se uma flag especifica esta viva, quem a le e quem a escreve.
---

# Diagnosticar flag que não faz efeito

O sintoma é sempre o mesmo: o build passa, o script "roda", e no jogo não
acontece nada. Flag errada nunca dá erro de compilação — `setflag` aceita
qualquer número.

Comece pelo catálogo, que responde três perguntas de uma vez:

```bash
grep "FLAG_A_SUSPEITA\b" docs/SOULGOLD_FLAGS_AUDIT.csv
```

As colunas são `valor,dec,nome,bloco,status,leituras,escritas,arquivos,mapas,escopo,comentario`.
O `status` já aponta a causa na maior parte dos casos. Se o CSV estiver velho,
rode `python3 dev_scripts/flag_audit.py --csv` antes (skill `catalogar-flags`).

## 1. Comportamento de engine: a flag certa é a do config

Sintoma: "setei a flag de não capturar / não desmaiar / shiny forçado e não
mudou nada".

A engine nunca lê a flag pelo nome cru — lê por um apelido em
`include/config/*.h`. E existem pares de nomes parecidos onde **só um está
ligado**:

| Comportamento | Apelido que a engine lê | Flag real hoje | Nome parecido que NÃO funciona |
|---|---|---|---|
| Não capturar | `B_FLAG_NO_CATCHING` | `FLAG_NO_CATCHING` (`0x1041`) | `FLAG_SYS_NO_CATCHING` (`0x24`) |
| Não desmaiar | `B_FLAG_NO_WHITEOUT` | `FLAG_NO_WHITEOUT` | — |
| Sem colisão | `OW_FLAG_NO_COLLISION` | `FLAG_COLLISION` (`0x2AA`) | `FLAG_SYS_NO_COLLISION` (`0x20`) |
| Sem encontro | `OW_FLAG_NO_ENCOUNTER` | `FLAG_SYS_NO_ENCOUNTER` | — |
| EXP Share | `I_EXP_SHARE_FLAG` | `FLAG_EXP_SHARE_OPTION` (`0x296`) | `FLAG_EXP_SHARE` (`0x4A6`) |
| Shiny forçado | `P_FLAG_FORCE_SHINY` | `FLAG_SET_SHINY` | — |

Confira sempre na fonte, porque isso muda com o tempo:

```bash
grep -rn "_FLAG_[A-Z_]*  *FLAG_" include/config/*.h
```

Um apelido definido como `0` significa que o recurso está **desligado** —
setar qualquer flag não vai ligá-lo.

**Escreva o apelido no script**, não a flag: `setflag B_FLAG_NO_CATCHING`.
Assim, se a flag por trás mudar, o script continua certo.

## 2. `SO_ESCRITA` — ninguém lê essa marca

O script marca progresso e nada consulta a marca. Sintomas: o NPC repete a
fala inicial, o presente pode ser pego de novo, a porta não abre depois do
evento.

```bash
git grep -n "FLAG_X\b" -- data src include | grep -v flags.h
```

Se só aparecerem `setflag`/`clearflag`, falta o `goto_if_set` — ou a flag é
decorativa e o comportamento esperado depende de outra coisa. Casos reais
neste repo: `FLAG_BADGE13..16_GET` (o cartão lê `FLAG_DEFEATED_*_GYM`),
`FLAG_EXP_SHARE`, as três flags de level scaling da Route36.

## 3. `SO_LEITURA` — nada seta, o `goto_if_set` nunca dá verdadeiro

O caminho "já fiz isso" está escrito e é inalcançável. Pode ser que o
`setflag` tenha sido esquecido, ou que o estado tenha migrado para uma `VAR_*`
e o `goto_if_set` seja restos.

Antes de concluir que falta o `setflag`, confira os dois lugares onde a
escrita não aparece como `setflag`:

- **Macros que recebem a flag como parâmetro** — `legendaryencounter`,
  `bosslegendaryencounter`, `bosslegendaryencounterwithmoves` passam a flag em
  `VAR_0x8007` e o special faz o `FlagSet` (`asm/macros/event.inc:2177`)
- **Aritmética em C** — `TRAINER_FLAGS_START + id`,
  `TRAINER_REGISTERED_FLAGS_START + i`, `FLAG_DECORATION_1 + i`,
  `FLAG_BADGE01_GET + i`. O `git grep` pelo nome não encontra essas

## 4. Valor fora do array de save

`GetFlagPointer` (`src/event_data.c:329`) **não checa limite**: qualquer valor
entre `FLAGS_COUNT` (5448) e `SPECIAL_FLAGS_START` (`0x4000`) vira uma escrita
fora de `flags[]`, em cima de `vars[]` ou `gameStats[]`. Sintoma: a flag
"funciona" até alguém mexer numa var, e aí o estado se desfaz sozinho.

```bash
python3 dev_scripts/flag_audit.py     # imprime "ERRO: flag fora do array" se houver
```

Quase sempre é dígito a mais no hexadecimal — foi o caso de
`FLAG_R39_NORTH_ROCKY_HELMET` (`0x2A92` no lugar de `0x2A9`).

## 5. NPC que não some, ou não volta

A flag do campo `flag` do `object_event` é o **único** controle de
visibilidade, e ela é consultada toda vez que a câmera tenta respawnar o
objeto. Três variações do mesmo defeito:

- `setflag` numa flag de esconder que **nenhum `map.json` referencia** (o CSV
  mostra `mapas` vazio): não esconde ninguém. Reais aqui:
  `FLAG_HIDE_ILEX_FOREST_KURT`, `FLAG_HIDE_OLIVINE_PORT_OAK`,
  `FLAG_HIDE_ROUTE22_JANINE`
- flag no `map.json` que **nada escreve**: o objeto fica visível para sempre
- `removeobject` sem a flag: ele volta quando a câmera o trouxer de novo, e
  ainda seta a flag do objeto removido — que pode significar outra coisa

Isso tem skill própria, com o padrão correto de cache recalculado no
`ON_LOAD`: `visibilidade-e-gatilhos`.

## 6. Flag que só vive em mapa fora da ROM

Se o CSV diz `SO_MAPAS_FORA_DA_ROM`, o único script que mexe nela está num
mapa de `rom_excluded_groups` (`gMapGroup_Emerald1..5`) — 432 mapas que
`tools/mapjson/mapjson.cpp` remove inteiros da ROM. A flag nunca muda numa
partida real. É o caso de 140 flags, quase todas herança de Hoenn.

Cuidado com o inverso: os 54 mapas de `rom_shared_script_maps` têm o
`scripts.inc` montado apesar do mapa não existir. Uma flag lá pode estar viva
se um mapa vivo chamar aquela label:

```bash
git grep -n "<Label_Do_Script>" -- data/maps
```

## 7. O estado zerou sozinho

- `FLAG_TEMP_*` (`0x00–0x1F`): zeram a cada carregamento de mapa
  (`ClearTempFieldEventData`). Não servem para progresso
- Bloco `DAILY` (`0x1508–0x1547`): zeram na virada do dia
- `SPECIAL_FLAGS` (`0x4000+`): moram em EWRAM, não vão para o save

## Ordem sugerida

1. `grep` no CSV → o `status` costuma responder
2. Se for comportamento de engine, seção 1 (é a causa mais comum e a mais
   invisível)
3. `git grep` pelo nome, separando quem lê de quem escreve
4. Se nada explicar, procure escrita por macro ou por aritmética (seção 3)

Ao terminar a correção, rode `catalogar-flags`: o diff do CSV confirma que a
flag saiu de `SO_ESCRITA`/`SO_LEITURA` e virou `EM_USO`.
