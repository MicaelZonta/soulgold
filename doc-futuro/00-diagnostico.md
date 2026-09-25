# Diagnóstico: onde o SoulGold está hoje

Números medidos no binário e no `.map` deste repositório em 22/09/2026
(commit `179a1196f9`, branch `soulgold-rift-missions`).

## O arquivo

| | bytes | |
|---|---:|---|
| `Soulgold.gba` no disco | 33.554.432 | 32,00 MB |
| Conteúdo real (antes do padding) | 31.100.004 | **29,66 MB** |
| Padding `0xFF` no fim | 2.453.428 | 2,34 MB |

Os 32 MB **não** são conteúdo. São o `gbafix -p` arredondando para a
potência de 2 seguinte, em [Makefile:657](../Makefile#L657):

```make
$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@
	$(FIX) $@ -p --silent
```

A implementação está em
[tools/gbafix/gbafix.c:295-308](../tools/gbafix/gbafix.c#L295-L308): acha o
bit mais alto do tamanho e completa com `0xFF` até a próxima potência de 2.

**Consequência prática que precisa ser dita antes de qualquer decisão:** no
primeiro byte acima de 32 MB, o `-p` passa a arredondar para **64 MB**. Um
jogo de 33 MB vira um arquivo de 64 MB. Em qualquer abordagem que ultrapasse
o limite, `-p` tem de sair da linha de comando e ser trocado por um
alinhamento de 4 bytes.

## A margem real

O teto de endereçamento é 0x08000000–0x09FFFFFF = 32 MB. Sobram
**2,34 MB**, ou 7,9% do orçamento. A otimização de conteúdo já foi feita e
está fora de escopo, então essa margem só diminui.

## Layout atual

De `objdump -h Soulgold.elf`:

| seção | VMA | tamanho | |
|---|---|---:|---|
| `.text` (código) | 0x08000000 | 0x2978B0 | 2,59 MB |
| `script_data` | 0x082978B0 | 0x1734C0 | 1,45 MB |
| `.rodata` | 0x0840AD70 | 0x199E140 | **25,62 MB** |
| fim (`__rom_end`) | 0x09DA8EB0 | | 29,66 MB |

**Código é 8,7% da ROM. `.rodata` é 86,4%.** Isso é o dado mais importante
do diagnóstico: o problema é inteiramente de dados, não de código. Toda
abordagem que consiga dar endereço a dados acima de 32 MB resolve o
problema, mesmo sem mexer em uma linha de lógica de jogo.

## Quem ocupa o espaço

Agregado por objeto a partir de `Soulgold.map` (29,31 MB dos 29,66 MB
atribuíveis; o resto é alinhamento e símbolos do linker):

| objeto | tamanho | % da ROM |
|---|---:|---:|
| `data/sound_data.o` | 10.138 KB | 34,2% |
| `src/pokemon.o` | 6.102 KB | 20,6% |
| `src/tilesets.o` | 2.544 KB | 8,6% |
| `data/maps.o` | 1.318 KB | 4,5% |
| `src/graphics.o` | 964 KB | 3,3% |
| `src/event_object_movement.o` | 829 KB | 2,8% |
| `src/fonts.o` | 422 KB | 1,4% |
| **soma dos 7** | **22.317 KB** | **75,4%** |

Fontes no disco, para dimensionar o que ainda pode crescer:
`graphics/pokemon` = 159 MB, `sound/` = 93 MB (dos quais
`sound/songs` = 48 MB e `sound/direct_sound_samples` = 40 MB).

Sete objetos concentram três quartos da ROM. Qualquer mecanismo de
realocação — seção alta, banco, disco virtual — só precisa alcançar esses
sete para valer a pena. Isso é o que torna a abordagem A tão barata e o que
limita o ganho marginal de B e C.

## O toolchain

- `MODERN=1` apenas. O `agbcc` está formalmente descontinuado no repo
  ([Makefile:362-365](../Makefile#L362-L365)). O código compila com
  `arm-none-eabi-gcc`, `-std=gnu17`
  ([Makefile:162](../Makefile#L162)). Isso importa muito para a
  abordagem D: é C moderno, não C de 2001 dependente de um compilador morto.
- Assembly restante: 3.421 linhas em 5 arquivos (`src/crt0.s` 185,
  `src/decompress_asm.s` 128, `src/libgcnmultiboot.s` 641, `src/m4a_1.s`
  2.414, `src/rom_header.s` 53) mais `libagbsyscall/libagbsyscall.s` (432).
  Total ~3.850 linhas de ARM.
- C/H em `src/` + `include/`: **1.328.375 linhas**.
- Acoplamento a hardware: 153 arquivos `.c` citam algum `REG_`, com 2.746
  referências no total; 200 usos de `DmaCopy`/`DmaFill`/`DmaClear`.
- Apenas 2 usos de `IWRAM_CODE`/`EWRAM_CODE` — quase nada de código
  posicionado à mão.

## A infra de testes

`make check` roda **1.027 arquivos de teste** em `test/` através de um
binário **pré-compilado** do mGBA:

```make
ROMTEST     ?= $(TOOLS_DIR)/mgba/mgba-rom-test
ROMTESTHYDRA := $(TOOLS_DIR)/mgba-rom-test-hydra/mgba-rom-test-hydra
```

([Makefile:232-239](../Makefile#L232-L239)) — `tools/mgba/` contém só
executáveis (`mgba-rom-test`, `.exe`, `-mac`), sem fonte.

Esse binário tem a mesma limitação de 32 MB do mGBA normal. **Toda
abordagem que aumente a ROM quebra `make check` por completo até que
`mgba-rom-test` seja recompilado com o mesmo patch.** É um custo fixo de A,
B e C que não aparece na descrição das abordagens.

## O material que já está aqui

`tools/mgba-master/` é a árvore de fontes completa do **mGBA 0.11.0**
(83 MB, **não versionada** — `git ls-files` retorna 0 arquivos). Ela contém
tudo que A, B e C precisam patchear, e contém um precedente funcionando de
bank switching (ver [02-abordagem-b.md](02-abordagem-b.md)).

`tools/mgba-rom-test-hydra/` (120 KB, 4 arquivos versionados) é o runner
paralelo de testes.

Ou seja: o ponto de partida para modificar o emulador já está no disco.
