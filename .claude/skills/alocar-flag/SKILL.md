---
name: alocar-flag
description: Use ao precisar de uma flag nova - marcar progresso de historia, "ja peguei este item", "ja falei com este NPC", esconder NPC por progresso, destravar area, liberar presente. Cobre onde alocar (bloco CUSTOM_FLAGS, que e o unico lugar certo), como mover CUSTOM_FLAGS_END, quando NAO criar flag nenhuma (FLAG_TEMP, VAR, ou flag que ja existe), e as tres faixas que parecem livres e nao sao (FLAG_UNUSED_1xx do Match Call, faixa de treinador, FLAG_GARBAGEFLAG). Use tambem ao escolher numero de flag, ao ver "flag nova" em qualquer doc de implementacao, e antes de editar include/constants/flags.h.
---

# Alocar uma flag nova

O espaço de flags é grande (2693 posições livres) mas o save é congelado:
`FLAGS_COUNT` não pode crescer mais que 8 bits sem quebrar os `STATIC_ASSERT`
de `src/save.c`, que existem para não corromper os saves de quem já joga.
Então flag não é escassa, mas **cada número escolhido é permanente**: ele fica
gravado nos saves e trocar depois muda o significado de um bit que já está
ligado na memória de alguém.

Detalhes e números: `.claude/SOULGOLD_FLAGS_AUDIT.md`.

## 1. Antes de criar, confira se precisa mesmo

Três perguntas, em ordem:

**Já existe uma flag que significa isso?** O jogo tem 1735. Progresso de
ginásio, HM recebida, badge, líder derrotado, item entregue — quase tudo já
tem nome:

```bash
grep -rn "FLAG_DEFEATED_.*_GYM\|FLAG_RECEIVED_HM_\|FLAG_VISITED_" include/constants/flags.h
grep -i "<palavra-chave>" docs/SOULGOLD_FLAGS_AUDIT.csv
```

**O estado precisa sobreviver a sair do mapa?** Se não — cena em andamento,
"já falei nesta visita", trava de gatilho de frame — use `FLAG_TEMP_*` ou
`VAR_TEMP_*`. Elas moram na RAM, zeram a cada carregamento de mapa
(`ClearTempFieldEventData`, `src/event_data.c:60`) e **não custam save**.
`FLAG_TEMP_B/C/D/F` estão livres hoje; confira antes de usar, porque scripts
comuns reusam as baixas:

```bash
grep -rn "FLAG_TEMP_<N>\b" data/maps/<Mapa>/ data/scripts/ src/*.c
```

**É um contador ou um estado com mais de dois valores?** Então é `VAR_*`, não
uma coleção de flags. Uma var guarda 65536 estados no mesmo espaço de 16
flags, e o script lê com `goto_if_eq`. As Rift Missions fazem assim
(`VAR_RIFT_MISSIONS_STATE`), com flag só onde o `map.json` exige uma
(o campo `flag` não sabe ler var).

**É para ligar um comportamento da engine?** (não capturar, não desmaiar,
shiny forçado, EXP Share, sem colisão...) Então **não crie flag**: esses
comportamentos já têm uma flag ligada por apelido em `include/config/*.h`
(`B_FLAG_NO_CATCHING`, `I_EXP_SHARE_FLAG`, `OW_FLAG_NO_COLLISION`...). Use o
apelido no script. Criar flag nova ou chutar a de nome parecido é o erro
descrito em `diagnosticar-flag` seção 1 — compila, roda e não faz nada.

## 2. Onde alocar: bloco `CUSTOM_FLAGS`

`include/global.h` fixa a política e a protege com asserts:

```c
STATIC_ASSERT(SYSTEM_FLAGS_END < CUSTOM_FLAGS_START, CustomFlagsOverlapSystemFlags);
STATIC_ASSERT(CUSTOM_FLAGS_END < FLAG_0x1500, CustomFlagsOverflowAllocation);
// "all new standalone flags belong in CUSTOM_FLAGS"
```

O bloco começa em `0x1000`. As posições `0x1000–0x1046` estão todas ocupadas,
então **a próxima flag nova continua em `0x1047`**, e o bloco pode ir até
`0x14FF` — 1209 posições.

Edição em `include/constants/flags.h`, no fim do bloco:

```c
#define FLAG_VISITED_SUN_MOON_ALTAR                 0x1046
#define FLAG_MINHA_COISA_NOVA                       0x1047 // o que significa, e quem seta
#define CUSTOM_FLAGS_END                            FLAG_MINHA_COISA_NOVA
```

Três detalhes que importam:

- **`CUSTOM_FLAGS_END` sempre aponta para a última alocação.** É o que o
  assert usa para garantir que o bloco não invadiu `FLAG_0x1500`. Esquecer de
  mover não quebra o build hoje — quebra daqui a 1209 flags, ou some com a
  única pista de até onde o bloco chegou.
- **Comentário obrigatório.** O script de auditoria copia o comentário para o
  catálogo; é o único campo que guarda intenção. "o que é" e "quem seta"
  bastam.
- **Nunca renumere flag existente** para abrir espaço. Renomear é grátis,
  renumerar mexe em save alheio.

## 3. As faixas que parecem livres e não são

| Faixa | Por que não |
|---|---|
| `FLAG_UNUSED_165`, `167`, `169`, `16A–16C`, `176`, `179`, `17B`, `17C`, `181`, `184–188` | Estão dentro do bloco do Match Call (`0x15C–0x198`), que o código escreve por aritmética: `FlagSet(TRAINER_REGISTERED_FLAGS_START + index)` (`src/pokenav_match_call_data.c:1173`). O nome diz "unused", a posição não é |
| `0x19A–0x1A9` | Mesmo bloco, sobra do fim dele |
| `0x500–0x91F` | Flag de treinador: é `TRAINER_FLAGS_START + id`. Usar aqui é dar a um treinador a sua flag |
| `0x920–0x98B` | Também de treinador, já reclamado e **cheio** (protegido por `TrainersOverlapReclaimedFlags`) |
| `FLAG_GARBAGEFLAG` (`0x53`) | É a flag-lixo que 224 mapas usam no campo `flag` de objetos sempre visíveis. Um `setflag` nela some com centenas de NPCs de uma vez |
| `FLAG_TEMP_*` para estado persistente | Zera ao trocar de mapa |
| `0xA4C–0xFFF` | Livre de verdade, mas é a reserva de expansão de `SYSTEM_FLAGS`. Não misture com flag de conteúdo |

Regra prática: se você está prestes a usar um número fora de `0x1047+`,
pergunte por que — quase sempre a resposta certa é o bloco `CUSTOM`.

## 4. Flags de visibilidade de NPC

O campo `flag` do `object_event` aceita **uma** flag e não sabe inverter nem
combinar condições, então um NPC que aparece "entre A e B" precisa de uma flag
dedicada de cache, recalculada no `ON_LOAD` a partir das flags de progresso
reais. Isso é assunto da skill `visibilidade-e-gatilhos` — leia antes de
alocar, porque em boa parte dos casos dá para usar uma `FLAG_TEMP_*` e não
gastar flag persistente nenhuma.

## 5. Catalogue

Toda alocação termina rodando a skill `catalogar-flags`:

```bash
python3 dev_scripts/flag_audit.py --csv
grep "FLAG_MINHA_COISA_NOVA\b" docs/SOULGOLD_FLAGS_AUDIT.csv
```

A linha confirma que a flag caiu no bloco `CUSTOM` e diz se ela já nasceu
órfã (`NUNCA_REFERENCIADA`), só escrita (`SO_ESCRITA`) ou só lida
(`SO_LEITURA`).

## Checklist

- [ ] Procurei uma flag existente antes de criar
- [ ] Não é caso de `FLAG_TEMP_*`, `VAR_TEMP_*` nem `VAR_*`
- [ ] Não é comportamento de engine que já tem apelido em `include/config/`
- [ ] Número no bloco `CUSTOM` (`0x1047` em diante), sequencial
- [ ] `CUSTOM_FLAGS_END` aponta para a minha flag
- [ ] Comentário diz o que significa e quem seta
- [ ] Build limpo (os asserts de `global.h` e `save.c` rodam no build)
- [ ] `catalogar-flags` rodado e diff do CSV conferido
