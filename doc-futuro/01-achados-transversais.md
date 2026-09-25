# Achados transversais

Cinco coisas encontradas no código real que quebram em **qualquer**
abordagem que ponha dados acima de 0x0A000000 (A, B e C). Nenhuma delas dá
erro de compilação. Todas compilam limpo e quebram em runtime ou em
silêncio — exatamente a categoria de armadilha que o `CLAUDE.md` deste repo
manda tratar como prioridade.

Elas não estão na descrição de nenhuma das abordagens propostas. São o
custo escondido comum a todas.

---

## 1. `ROM_END` é 0x0A000000, e há um range-check usando ele

```c
#define ROM_START 0x8000000
#define ROM_END   0xA000000
```
[include/gba/defines.h:37-38](../include/gba/defines.h#L37-L38)

O consumidor problemático é o sistema de plaquinha de falante, adicionado
neste romhack:

```c
void SetSpeaker(struct ScriptContext *ctx)
{
    u32 arg = ScriptReadWord(ctx);
    const u8 *speaker = NULL;

    if (arg < SP_NAME_COUNT)
        speaker = gSpeakerNamesTable[arg];
    else if (arg >= ROM_START && arg < ROM_END)
        speaker = (const u8 *)arg;

    SetSpeakerNameForNextMessage(speaker);
}
```
[src/field_name_box.c:190-200](../src/field_name_box.c#L190-L200)

Se uma string de nome de falante cair acima de 0x0A000000, `arg < ROM_END`
é falso, `speaker` fica `NULL` e **a plaquinha simplesmente não aparece**.
Sem crash, sem aviso. A cena roda inteira com a caixa de diálogo sem nome.

Esse código é da branch atual (`nomear-falante`, arquivo modificado no `git
status`). É o exemplo mais limpo de por que a auditoria tinha que ser feita
no código real e não no pokeemerald-expansion de referência.

**Correção:** `ROM_END` passa a ser o topo da nova janela (0x0E000000 em A).
Uma linha. Mas tem de ser lembrada.

## 2. `malloc` empacota ponteiros de ROM em 25 bits

```c
struct MemBlock
{
    u16 allocated:1;
    u16 unused_00:4;
    u16 locationHi:11;   // High 11 bits of location pointer.
    u16 magic;
    u32 size:18;
    u32 locationLo:14;   // Low 14 bits of location pointer.
    ...
};
```
[include/malloc.h](../include/malloc.h) (campos nas linhas 23 e 32)

Gravado em [src/malloc.c:77-78](../src/malloc.c#L77-L78):

```c
pos->locationHi = ((uintptr_t)location) >> 14;
pos->locationLo = (uintptr_t)location;
```

E reconstruído em [src/malloc.c:269](../src/malloc.c#L269):

```c
return (const char *)(ROM_START | (block->locationHi << 14) | block->locationLo);
```

11 + 14 = **25 bits = exatamente 32 MB**. Não é coincidência: o campo foi
dimensionado para o limite do GBA. Acima de 32 MB, `locationHi` trunca
silenciosamente e `MemBlockLocation()` devolve um ponteiro de ROM errado —
apontando para o espelho dentro dos primeiros 32 MB.

É uma facilidade de depuração (rastrear de qual `__FILE__` veio cada
alocação), não lógica de jogo, então não trava nada. Mas ela passa a mentir
no exato momento em que você mais vai precisar dela: depurando a migração.

**Correção:** o header tem `unused_00:4` logo ao lado. Levar `locationHi`
de 11 para 15 bits consome esses 4 e dá 29 bits = 512 MB, sem crescer a
struct. A struct é o cabeçalho de toda alocação do heap, então crescê-la
custaria memória em cima de um heap que já é apertado — usar os bits livres
é a saída certa.

## 3. A regra `make syms` filtra endereços por prefixo

```make
$(SYM): $(ELF)
	$(OBJDUMP) -t $< | sort -u | grep -E "^0[2389]" | ...
```
[Makefile:665](../Makefile#L665)

O `grep -E "^0[2389]"` aceita símbolos em 0x02 (EWRAM), 0x03 (IWRAM), 0x08
e 0x09 (ROM). Símbolos em **0x0A a 0x0D são descartados**.

O `.sym` alimenta o carregamento de símbolos do mGBA e ferramentas de
depuração. Depois da migração, todo símbolo de `.rodata` — 86% da ROM —
sumiria do arquivo, e qualquer breakpoint ou inspeção sobre dados ficaria
cego. Na abordagem A, que é justamente a que move `.rodata` para cima, isso
atinge tudo que interessa.

**Correção:** `grep -E "^0[23ABCD89]"` ou simplesmente `"^0"`.

## 4. `gbafix -p` arredonda para potência de 2

Já descrito em [00-diagnostico.md](00-diagnostico.md). Repetido aqui porque
é um dos cinco: com 33 MB de conteúdo, o `-p` de
[Makefile:657](../Makefile#L657) gera um arquivo de **64 MB**, quase metade
dele `0xFF`.

**Correção:** trocar `-p` por alinhamento de 4 bytes no passo de
`objcopy`. O padding para potência de 2 existe por causa de cartuchos
físicos; como a distribuição aqui é um executável próprio, ele perdeu a
função.

## 5. `make check` quebra inteiro até o `mgba-rom-test` ser recompilado

1.027 arquivos de teste rodam sobre o binário pré-compilado
`tools/mgba/mgba-rom-test` ([Makefile:232-239](../Makefile#L232-L239)), que
tem o mesmo teto de 32 MB descrito em
[02-abordagem-b.md](02-abordagem-b.md#o-teto-está-no-carregamento).

No instante em que a ROM passa de 32 MB, `GBALoadROM` trunca o arquivo e
**todos** os testes passam a rodar contra uma ROM cortada. O sintoma não é
"teste X falhou": é falha em massa e sem sentido.

`tools/mgba/` não tem fonte — só os três executáveis. A recompilação sai de
`tools/mgba-master/`, e o binário resultante precisa ser produzido para
Linux, Windows e macOS, já que o Makefile seleciona um dos três por
plataforma.

**Custo:** é um item de infraestrutura, não de código de jogo, e é fácil de
esquecer no planejamento porque nenhuma das quatro abordagens o menciona.
Vale para A, B e C. A abordagem D o elimina junto com o emulador, mas ao
preço de reescrever o harness de testes.

---

## Resumo

| # | Achado | Local | Sintoma | Custo |
|---|---|---|---|---|
| 1 | `ROM_END` = 0x0A000000 | `field_name_box.c:196` | plaquinha de nome some, em silêncio | 1 linha |
| 2 | ponteiro de ROM em 25 bits | `malloc.h:23,32` | `MemBlockLocation` mente | 1 linha |
| 3 | `syms` filtra `^0[2389]` | `Makefile:665` | símbolos de dados somem | 1 linha |
| 4 | `gbafix -p` | `Makefile:657` | arquivo de 64 MB | 1 linha |
| 5 | `mgba-rom-test` pré-compilado | `Makefile:232` | 1.027 testes falham juntos | recompilar ×3 plataformas |

Quatro dos cinco são de uma linha. O quinto é trabalho de infra real. O
que os torna perigosos não é o tamanho: é que nenhum deles aparece como
erro de build, e três deles falham em silêncio.
