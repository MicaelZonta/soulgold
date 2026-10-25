# B09 — Os `udf` da ROM: triagem (25/10/2026)

`udf #255` (`0xdeff`) é o `__builtin_trap()` do GCC para Thumb. O compilador
emite isso quando **prova** que um caminho é comportamento indefinido —
ponteiro nulo desreferenciado, divisão por zero, índice fora do array — e
isola o caminho num trap. Se o jogo chegar lá, executa instrução indefinida.
Foi um desses que matava a Melemele Isle (`.claude/merge_hns/bug_alola_trava.md`).

Como achar:

```bash
arm-none-eabi-objdump -d Soulgold.elf | grep -n udf
```

No build de teste de 25/10/2026 são **8**. `addr2line` não ajuda (o build
passa por `cpp` e a linha fica `<stdin>:?`), então a triagem foi feita pelo
par desmontagem + fonte.

## Resumo

| # | endereço | função | arquivo | o que o GCC provou | alcançável hoje |
|---|---|---|---|---|---|
| 1 | `806e954` | `UpdateBattlerValue` | `battle_debug.c` | escrita em NULL (`movs r3,#0; strh r3,[r3,#0]`) | **não** — menu de debug de batalha |
| 2 | `806f154` | `SetUpModifyArrows` | `battle_debug.c` | leitura em ponteiro nulo | **não** — menu de debug de batalha |
| 3 | `8098f8e` | `BattleStringExpandPlaceholders` | `battle_message.c` | leitura em NULL (`movs r3,#0; ldrb r3,[r3,#0]`) | **não determinado** |
| 4 | `80ab2ca` | `Cmd_averagestats` | `battle_script_commands.c` | `*GetBattlerStat(...)` com retorno NULL | **não** — só 4 usos, todos válidos |
| 5 | `80d20c8` | `AddMovePoints` | `battle_tv.c` | leitura em NULL | **não determinado** |
| 6 | `819bf4e` | `GetItemStatus1Mask` | `item.c` | `GetItemEffect()[3]` com retorno 0 | **não** — item fora da ROM |
| 7 | `820521a` | `UseStatIncreaseItem` | `pokemon.c` | `itemEffect[0]` com `itemEffect = 0` | **não** — item fora da ROM |
| 8 | `82a102e` | `ChooseRockSmashItem` (inlinado em `TryGetRockSmashItem`) | `wild_encounter.c` | `Random() % totalWeight` com `totalWeight == 0` | **não** — nenhuma tabela com peso 0 |

Nenhum dos oito é alcançável hoje pelos seis que foram fechados; dois ficaram
sem prova. Três deles, porém, são **bombas-relógio**: viram crash de verdade
com uma mudança de conteúdo que não dá nenhum erro de build.

## 8. `ChooseRockSmashItem` — a bomba mais fácil de pisar

`src/wild_encounter.c:1147`

```c
for (i = 0; i < count; i++)
    totalWeight += items[i].weight;

roll = Random() % totalWeight;        // <- totalWeight pode ser 0
```

Hoje não estoura: a única tabela de mapa (`sRockSmashItems_RuinsOfAlph`) tem
19 itens de peso 10 (total 190) e a geral tem 4 de peso 25 (total 100).

Vira crash no dia em que alguém acrescentar uma `RockSmashItemTable` com
`count = 0` ou com todos os pesos zerados. E `count = 0` quebra duas vezes:

```c
for (i = 0; i < count - 1; i++)       // count e u8: count - 1 promove a int -1,
                                      // comparado contra u32 vira 0xFFFFFFFF
```

Guarda sugerida (não aplicada — o autor decide):

```c
if (totalWeight == 0)
    return items[0].itemId;           // ou cair na sRockSmashItems_General
```

## 4. `Cmd_averagestats` — a segunda bomba

`src/battle_script_commands.c:12530`

```c
static u16 *GetBattlerStat(struct BattlePokemon *battler, enum Stat stat)
{
    switch (stat)
    {
    case STAT_ATK:   return &battler->attack;
    case STAT_DEF:   return &battler->defense;
    case STAT_SPATK: return &battler->spAttack;
    case STAT_SPDEF: return &battler->spDefense;
    default:         return NULL;     // <- STAT_HP, STAT_SPEED, STAT_ACC, STAT_EVASION
    }
}
```

`Cmd_averagestats` desreferencia o retorno sem checar. Os únicos usos hoje são
`data/battle_scripts_1.s:1920-1931` — Power Split (`STAT_ATK`/`STAT_SPATK`) e
Guard Split (`STAT_DEF`/`STAT_SPDEF`), os quatro casos válidos. Um
`averagestats STAT_SPEED` num golpe novo compila limpo e trava a batalha.

## 6 e 7. `GetItemStatus1Mask` e `UseStatIncreaseItem` — mesma raiz

`include/config/save.h:13` tem `FREE_ENIGMA_BERRY TRUE` (libera 52 bytes do
save). Com isso:

```c
const u8 *GetItemEffect(enum Item itemId)        // src/item.c:866
{
    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
        return 0;                                 // FREE_ENIGMA_BERRY == TRUE
    ...
}

u32 GetItemStatus1Mask(enum Item itemId)          // src/item.c:982
{
    const u8 *effect = GetItemEffect(itemId);
    switch (effect[3])                            // <- NULL[3]
```

`UseStatIncreaseItem` (`src/pokemon.c`) faz o mesmo por conta própria fora de
batalha (`itemEffect = 0` e depois `itemEffect[0]`).

Não é alcançável porque a `ITEM_ENIGMA_BERRY_E_READER` não entra na bolsa: o
único `giveitem` está em `data/maps/PetalburgCity_Gym/scripts.inc:319`, e o
`map_graph.py` dá o mapa como **fora da ROM**; além disso o script ainda passa
por `IsEnigmaBerryValid` (que exige dados de e-Reader) e por
`VAR_ENIGMA_BERRY_AVAILABLE`.

Terceira bomba: basta a berry virar obtenível em qualquer mapa para os dois
traps ficarem a uma tecla de distância (usar o item na bolsa).

## 1 e 2. `battle_debug.c` — só no build de teste

`include/config/debug.h:11`: `DEBUG_BATTLE_MENU DISABLED_ON_RELEASE`. O menu
de debug de batalha (Select dentro da batalha) não existe em `make release`.
No build do dia a dia os dois traps estão lá, atrás do menu de debug.

## 3 e 5. Sem prova

`BattleStringExpandPlaceholders` (`battle_message.c`) e `AddMovePoints`
(`battle_tv.c`). Nos dois a sequência é a canônica do GCC —
`movs r3,#0; ldrb/ldrh r3,[r3,#0]; udf`, leitura explícita do endereço 0 —
então o compilador provou um ponteiro nulo num caminho; falta achar **qual
entrada** leva até lá.

Pistas para quem pegar:

- `BattleStringExpandPlaceholders`: o trap cai logo depois de
  `BattleStringGetTrainerName`. O laço de cópia já tem `if (toCpy != NULL)`
  (`src/battle_message.c:3628`), então o caminho isolado é outro ponteiro, não
  o `toCpy` da cópia.
- `AddMovePoints`: antes do trap o código lê um `u16`, extrai um campo de
  3 bits (`lsls #23; lsrs #29`) e desvia para o trap quando ele é diferente de
  zero. Cheira a `GetMoveAdditionalEffectById(move, i)` devolvendo NULL.

Os dois são código de batalha comum (não é debug, não é Hoenn morto), então
valem um segundo passe antes da release.

## Método, para a próxima vez

```bash
arm-none-eabi-objdump -d Soulgold.elf | grep -n udf
# para cada endereco:
arm-none-eabi-objdump -d --start-address=0xNNN-0x60 --stop-address=0xNNN+8 Soulgold.elf
arm-none-eabi-addr2line -e Soulgold.elf -f -p 0xNNN   # da o simbolo (a linha nao)
```

As três assinaturas que apareceram:

| desmontagem antes do `udf` | significa |
|---|---|
| `movs r3,#0; ldrb/ldrh/strh r3,[r3,#0]` | ponteiro provado nulo, caminho isolado |
| `bl Random32` / `bl __umodsi3` ausente | `% 0` provado |
| `bl AssertfCrashScreen` e o código segue | assert que não interrompe, e o índice fora do array vira trap |
