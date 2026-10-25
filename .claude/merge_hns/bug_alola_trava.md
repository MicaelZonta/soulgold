# Melemele Isle travava ao entrar — resolvido (24/10/2026)

**Sintoma:** ao chegar na Melemele Isle o jogo parava de responder. A plaquinha
com o nome do mapa ficava na tela para sempre e nenhum botão funcionava. Não era
tela preta nem reset: as interrupções continuavam (`gMain.vblankCounter1` subia
60 por 60 quadros), mas o laço principal estava morto.

## Causa

A porta da casa de Melemele é o metatile **70** do `gTileset_AlolaIsland`, com
comportamento `MB_ANIMATED_DOOR`. Esse id **não estava** em
`sDoorAnimGraphicsTable` (`src/field_door.c`) — a Fase 8 trouxe os mapas e o
tileset de Alola, mas não as entradas de porta que o pokehns tem.

Ao sair pela porta, `Task_ExitDoor` (`src/field_screen_effect.c`, estado 2)
chama `FieldAnimateDoorClose`, que fazia:

```c
gfx = GetDoorGraphics(sDoorAnimGraphicsTable, MapGridGetMetatileIdAt(x, y));
if (gfx->size == DOOR_SIZE_2x2)   // gfx é NULL quando o id não está na tabela
```

`GetDoorGraphics` devolve `NULL` quando o id não está na tabela. Ler `gfx->size`
de `NULL` é comportamento indefinido, e o GCC **provou** isso e trocou o acesso
por uma instrução indefinida:

```
 815d454:  beq.n  815d484        ; chegou ao terminador da tabela -> NULL
 815d484:  ldrb   r3, [r3, #3]   ; gfx->size com gfx == NULL
 815d486:  udf    #255           ; <- aqui o jogo morre
```

O ARM7TDMI desvia para o handler de instrução indefinida da BIOS, que fica em
laço. Por isso tudo congelava com as interrupções ainda vivas — e por isso a
plaquinha ficava: a tarefa dela roda no laço principal, que nunca mais rodou.

Build limpo, nenhum aviso. Só aparece **no jogo**, e só em mapa cujo metatile de
porta não está na tabela.

## Conserto (3 partes)

| Arquivo | O quê |
|---|---|
| `src/field_door.c` | `if (gfx == NULL) return -1;` em `FieldAnimateDoorClose` e `FieldAnimateDoorOpen` — porta não registrada agora só deixa de animar, nunca trava |
| `src/field_door.c` | entradas `METATILE_Alola_Door` (70) e `METATILE_Alola_Door_PokeCenter` (98), com os gráficos do pokehns (`graphics/door_anims/alola_door.png`, `alola_pokecenter_door.png`, paleta 2, `DOOR_SIZE_1x1` = 3 quadros de 16x16) |
| `include/constants/metatile_labels.h` | os dois rótulos novos, bloco `// gTileset_AlolaIsland` |

## Provado no jogo (24/10/2026, QA headless)

- Melemele Isle (`warp 36 2 0`): plaquinha sobe e **sai**, o jogador anda, entra
  na casa (`Task_DoDoorWarp` + `Task_AnimateDoor` ativos) e sai de novo pela
  porta — o caminho que matava o jogo.
- Akala (`36 0 0`), Ulaula (`36 4 0`) e Poni (`36 3 0`): carregam e andam.
- A porta anima de verdade: `/tmp/qa/porta_zoom.png` mostra fechada → meia →
  aberta, com a paleta da casa.

## O que ficou de fora (de propósito)

- **Metatiles 114 e 122** do `gTileset_AlolaIsland` também são
  `MB_ANIMATED_DOOR` e continuam sem gráfico — como no próprio pokehns. Nenhum
  warp das ilhas cai neles (varredura de todos os `warp_events`), então são
  porta de enfeite: não animam e, com a guarda, não travam.
- A tabela casa a porta **só pelo id do metatile**, sem olhar o tileset (o
  pokehns tem um campo `tileset` a mais). Hoje nenhum outro tileset usa 70 ou 98
  como porta — a varredura abaixo confirma —, mas um tileset novo que use pode
  herdar a porta de Alola sem erro de build.
- A varredura achou 7 layouts de **Hoenn** (Lilycove, Mossdeep, Route 110,
  Ever Grande, Fallarbor, Birth Island, Sootopolis) com metatile de porta fora
  da tabela. São `map.bin` antigos, ainda no formato de 10 bits, em mapas que
  ninguém alcança; com a guarda não travam mais. Não foram mexidos.

## A ferramenta que achou

`.claude/qa/driver.lua` ganhou o comando `pc` (r0..r15). Com o jogo travado:
ler os registradores, achar o símbolo com `arm-none-eabi-addr2line`, e
desmontar a região com `arm-none-eabi-objdump -d --start-address=...`. Foi o
`udf #255` no desmonte que fechou o caso.

**Armadilha:** o `pc` sozinho engana. O emulador pausa sempre no mesmo ponto do
quadro, então quase toda amostra cai na espera de VBlank da BIOS ou no callback
de HBlank — foi o que mandou a investigação para o lado errado antes. A prova de
que o laço principal estava morto foi outra: escrever um valor em
`gMain.heldKeys` e ver que `ReadKeys` nunca o apagava.

A varredura de portas sem entrada na tabela está em
`dev_scripts/portas_sem_grafico.py`.
