# D) Port nativo para PC (SDL sobre a decomp)

**Veredito: é o destino final correto do projeto e a pior decisão
possível para tomar agora.** Resolve o limite de ROM como efeito
colateral de reescrever a fundação inteira.

---

## A escala

| | |
|---|---:|
| C/H em `src/` + `include/` | **1.328.375 linhas** |
| ARM assembly a reescrever | ~3.850 linhas |
| Arquivos `.c` que citam `REG_` | 153 |
| Referências a `REG_*` | 2.746 |
| Usos de `DmaCopy`/`DmaFill`/`DmaClear` | 200 |
| Arquivos de teste que dependem do harness GBA | 1.027 |

Para efeito de comparação: a abordagem A são ~5 linhas no jogo.

## O que joga a favor

Dois fatos do repo tornam D menos impossível do que parece:

1. **`MODERN=1` apenas.** O `agbcc` está descontinuado
   ([Makefile:362-365](../Makefile#L362-L365)) e o build usa
   `arm-none-eabi-gcc` com `-std=gnu17`
   ([Makefile:162](../Makefile#L162)). O código é C moderno e portável na
   maior parte — não depende de um compilador de 2001 com extensões
   próprias. Isso elimina a maior barreira histórica dos ports de decomp.
2. **Quase nada de código posicionado à mão.** Só **2** usos de
   `IWRAM_CODE`/`EWRAM_CODE` em todo o `src/`. O assembly restante é
   concentrado e identificável, não espalhado.

## 1. O que muda no repositório do jogo

### A camada de hardware

Os 2.746 `REG_*` em 153 arquivos precisam de um substituto. Não são 2.746
casos distintos — a maioria é DISPCNT/BGxCNT/BGxHOFS repetidos — mas cada
arquivo é um ponto de contato.

Subsistemas a reimplementar do zero:

- **PPU.** 4 backgrounds com scroll, modos de tela, affine (modos 1/2),
  janelas, blending, prioridades, 128 sprites OAM com affine. É o item
  mais caro e o mais fácil de errar sutilmente: o jogo depende do
  comportamento exato de camadas e blending.
- **Som.** `src/m4a.c` + `src/m4a_1.s` (2.414 linhas ARM) + `src/m4a_tables.c`.
  O mixer roda por DMA sincronizado a timer. Precisa virar mixer em
  software com callback de áudio.
- **DMA.** 200 pontos de uso. Vira `memcpy`, mas os modos especiais
  (HBlank DMA para efeitos de tela, FIFO de áudio) precisam de emulação de
  comportamento, não só de cópia.
- **Timers e interrupções.** `VBlankIntrWait` e o loop principal em
  `src/crt0.s` (185 linhas) viram um game loop com vsync.
- **BIOS calls.** `libagbsyscall` (432 linhas): `LZ77UnComp*`, `RLUnComp*`,
  `BitUnPack`, `Diff*UnFilter`, `ObjAffineSet`, `BgAffineSet`, `Div`,
  `Sqrt`, `ArcTan2`. Reimplementação direta, mas tem de bater bit a bit
  com o BIOS, senão gráficos saem corrompidos.
- **Flash 128K.** `src/agb_flash*.c` viram arquivo de save.
  [include/gba/flash_internal.h:4](../include/gba/flash_internal.h#L4).

### O problema de 64 bits

```c
#define T1_READ_PTR(ptr) (u8 *) T1_READ_32(ptr)
#define T2_READ_PTR(ptr) (void *) T2_READ_32(ptr)
```
[include/global.h:114,120](../include/global.h#L114-L120)

Lê 32 bits e converte em ponteiro. Em x86-64 isso trunca. Não é um caso
isolado: há 87 casts do tipo `(u32)&` / `(u32)(` em `src/`.

Somado a isso, **216 `STATIC_ASSERT` sobre `sizeof`** travam layouts de
struct — inclusive os do save:

```c
STATIC_ASSERT(sizeof(struct SaveBlock2) == 0xB30, SaveBlock2LegacySize);
STATIC_ASSERT(sizeof(struct SaveBlock1) == 0x3C54, SaveBlock1LegacySize);
```
[src/save.c:93-114](../src/save.c#L93-L114)

Toda struct que contenha ponteiro muda de tamanho num alvo de 64 bits, e
esses asserts disparam. Isso é **bom** — falha em compilação, não em
runtime — mas define o caminho: ou se compila em **ILP32** (`-m32` no x86,
o que barra ARM64 e macOS moderno), ou se converte todo ponteiro
persistido em índice/offset, mexendo nos formatos de save.

A compatibilidade com saves existentes é um requisito não trivial aqui: um
`Soulgold.sav` na raiz do repo indica que há saves em uso.

### Estimativa

Ports nativos de decomps de Pokémon são projetos de **dezenas de milhares
de linhas** e meses de trabalho dedicado, mesmo partindo de uma decomp
limpa. Nada neste repositório sugere que seria diferente. Considere
**20.000+ linhas** de camada de plataforma e correções, mais a migração do
harness de 1.027 testes, que hoje depende de rodar uma ROM num emulador.

## 2. O que muda na camada de plataforma

Deixa de existir emulador. Entra SDL (ou equivalente) fazendo janela,
entrada, áudio e apresentação de framebuffer. Em compensação, somem todos
os custos de A/B/C ligados ao mGBA: não há patch de `memory.c` para
rebasear, não há `mgba-rom-test` para recompilar em três plataformas, não
há savestate de emulador para manter compatível.

## 3. Riscos técnicos

1. **Risco de regressão em massa.** Cada detalhe de PPU errado é um bug
   visual em algum lugar do jogo. Não há como validar 1.027 testes
   enquanto o harness não for portado, então a migração acontece
   justamente no período em que a rede de segurança está desligada.
2. **Paridade de comportamento.** O jogo foi ajustado contra o
   comportamento real do hardware — timing de DMA, ordem de blending,
   janelas. Diferenças sutis aparecem como "a cena está um pouco errada",
   que é a categoria mais cara de diagnosticar.
3. **Fim do ferramental do ecossistema.** Porymap, `mgba-rom-test`,
   savestates, ferramentas de romhacking, patches distribuídos como BPS —
   tudo assume um `.gba`. O repo tem `porymap.project.cfg` e um fluxo de
   trabalho inteiro construído em cima disso; as skills do projeto
   (`prototipo-de-mapa`, `acabamento-de-mapa`) dependem dele.
4. **Distribuição muda de natureza.** O modelo atual — patch sobre a ROM
   do Emerald do usuário, sem embutir a ROM original — é o que mantém o
   projeto em terreno defensável. Um executável nativo contendo todos os
   assets não tem esse mesmo enquadramento. **Isso é uma consideração
   legal, não técnica, e é provavelmente a mais importante de D** —
   convém resolvê-la antes de qualquer linha de código.
5. **Custo de oportunidade.** Durante a migração, o desenvolvimento de
   conteúdo para. Num projeto cujo trabalho corrente é adicionar mapas,
   cenas e eventos, isso é o custo dominante.

## Quando D faz sentido

Quando o objetivo deixar de ser "caber" e passar a ser "sair do GBA" —
resolução maior, widescreen, 60fps, mods, Steam Deck. Aí D não é caro: é a
única opção, e o limite de ROM some junto.

Enquanto o objetivo for continuar fazendo o jogo que já existe, D é
reescrever a fundação para ganhar 2,34 MB de margem.
