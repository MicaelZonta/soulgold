# A) mGBA com mapeamento linear 0x08000000–0x0DFFFFFF (96 MB)

**Veredito: é a abordagem recomendada.** É de longe a mais barata das
quatro, e o achado central abaixo a torna mais barata ainda do que a
proposta original supõe.

---

## O achado que muda a proposta

A proposta original diz: *"Código fica nos primeiros 32MB; dados grandes vão
para uma seção de linker posicionada acima de 0x0A000000."*

**Esse split não é necessário e custa caro.** As regiões de ROM do GBA
(0x08, 0x0A, 0x0C) são contíguas no espaço de endereços. Se o mapeamento é
linear, o linker não precisa saber que existe uma fronteira em 0x0A000000 —
basta uma única região de 96 MB e as seções fluem por cima da fronteira
sozinhas.

Por que isso importa: o `.gba` é gerado por `objcopy -O binary`
([Makefile:656](../Makefile#L656)), onde **offset no arquivo = endereço −
0x08000000**. Um buraco no espaço de endereços vira um buraco real de bytes
no arquivo.

| | tamanho do `.gba` |
|---|---:|
| Região única de 96 MB, seções contíguas | **29,66 MB** |
| `.text`+`script_data` baixos, `.rodata` em 0x0A000000 | **57,62 MB** |

O split proposto desperdiçaria **27,96 MB** de `0xFF` no meio do arquivo,
porque `.text` + `script_data` somam só 4,04 MB e o buraco até 0x0A000000
teria 27,96 MB. Duplicaria o tamanho do download sem ganhar nada.

Com região única, o arquivo hoje **não muda de tamanho** — continua 29,66 MB
— e só cresce quando o conteúdo crescer de verdade.

## 1. O que muda no repositório do jogo

### Linker: uma linha

[ld_script_modern.ld:11](../ld_script_modern.ld#L11):

```diff
-    ROM    (rx) : ORIGIN = 0x8000000, LENGTH = 32M
+    ROM    (rx) : ORIGIN = 0x8000000, LENGTH = 96M
```

Só isso. As seções em [ld_script_modern.ld:51-98](../ld_script_modern.ld#L51-L98)
(`.text`, `script_data`, `.rodata`, `.data.iwram`, `.data.ewram`) já usam
`> ROM` e continuam fluindo em ordem. Nada precisa ser reposicionado,
reagrupado ou anotado.

A save continua Flash 128K em 0x0E000000. A janela nova termina em
0x0DFFFFFF, um byte antes — **não há colisão**.
[include/gba/flash_internal.h:4](../include/gba/flash_internal.h#L4) define
`FLASH_BASE 0xE000000` e não precisa mudar.

### O resto: os achados transversais

Os cinco itens de [01-achados-transversais.md](01-achados-transversais.md).
Quatro são de uma linha; o quinto é recompilar o `mgba-rom-test`.

Vale registrar o que **não** precisa mudar, porque é o que sustenta o
veredito:

- **O motor de som usa ponteiro de 32 bits puro.** `struct WaveData` e
  `struct ToneData` em
  [include/gba/m4a_internal.h](../include/gba/m4a_internal.h) guardam
  `struct WaveData *wav`, `s8 *currentPointer` — sem bitfield, sem offset
  empacotado. Os 10,1 MB de `data/sound_data.o` (34% da ROM) sobem para
  além de 32 MB sem tocar em uma linha do `m4a`.
- **Nenhuma tabela de gráficos empacota ponteiro.** `struct
  CompressedSpriteSheet` ([include/sprite.h:19](../include/sprite.h#L19))
  é `const u32 *data` + dois `u16`. Os 6,1 MB de `src/pokemon.o` e os
  2,5 MB de `src/tilesets.o` sobem de graça.
- **Não há suposição de faixa de ROM no código de jogo.** Uma varredura
  por `0x08000000`, `0x01FFFFFF` e `0x09FFFFFF` em `src/` e `include/`
  devolve só ocorrências de `0x80000000` (bit de sinal, flags de
  `MUSICPLAYER_STATUS_PAUSE`, `gFieldEffectArguments`) — nada de
  endereçamento. As duas únicas exceções reais são os achados 1 e 2.

### Estimativa

| item | linhas |
|---|---:|
| `ld_script_modern.ld` | 1 |
| `defines.h` (`ROM_END`) | 1 |
| `malloc.h` (bitfield) | 1 |
| `Makefile` (`syms`, `gbafix -p`) | 2 |
| **total no repo do jogo** | **~5** |

Cinco linhas. Não há sistema de jogo afetado, nenhuma cena para reencenar,
nenhum script para reescrever.

## 2. O que muda no emulador

Aqui está a segunda parte do achado. Em `tools/mgba-master/` (mGBA 0.11.0),
todo acesso à ROM passa por uma máscara:

```c
if ((address & (GBA_SIZE_ROM0 - 1)) < memory->romSize) {
    value = ((uint8_t*) memory->rom)[address & (GBA_SIZE_ROM0 - 1)];
}
```
[src/gba/memory.c:708-709](../tools/mgba-master/src/gba/memory.c#L708-L709)

`GBA_SIZE_ROM0 - 1` = **0x01FFFFFF**. É essa máscara, e só ela, que cria os
espelhos: ela joga fora os bits que distinguem 0x08 de 0x0A e de 0x0C.

A máscara linear correta é **0x07FFFFFF**, e ela funciona porque as regiões
são contíguas:

| endereço | `& 0x07FFFFFF` | offset linear (`addr − 0x08000000`) |
|---|---|---|
| 0x08000000 | 0x00000000 | 0x00000000 |
| 0x09FFFFFF | 0x01FFFFFF | 0x01FFFFFF |
| 0x0A000000 | 0x02000000 | 0x02000000 |
| 0x0C000000 | 0x04000000 | 0x04000000 |
| 0x0DFFFFFF | 0x05FFFFFF | 0x05FFFFFF |

São idênticos em toda a faixa. **`address & 0x07FFFFFF` é exatamente
`address − 0x08000000` para 0x08000000–0x0DFFFFFF.** O mapeamento linear
não exige lógica nova: é uma troca de constante.

### Os pontos a patchear

- **26 ocorrências** de `GBA_SIZE_ROM0 - N` em
  [src/gba/memory.c](../tools/mgba-master/src/gba/memory.c), nos caminhos de
  `load8/16/32`, `store*`, `GBASetActiveRegion` e nas macros `LOAD_CART`
  ([linha 427](../tools/mgba-master/src/gba/memory.c#L427)). Substituição
  mecânica por uma `GBA_ROM_LINEAR_MASK`.
- **`GBALoadROM`** em
  [src/gba/gba.c:425-493](../tools/mgba-master/src/gba/gba.c#L425-L493).
  Hoje qualquer arquivo maior que 32 MB é truncado:
  ```c
  if (gba->pristineRomSize > GBA_SIZE_ROM0) {
      ...
      gba->memory.rom = vf->map(vf, GBA_SIZE_ROM0, MAP_READ);
      gba->memory.romSize = GBA_SIZE_ROM0;
  }
  ```
  Precisa aceitar até 96 MB. Continua sendo `vf->map()` — mmap, não cópia,
  então não custa RAM residente.
- **`romMask` / `activeMask`.** O núcleo ARM executa via
  `activeRegion[(pc & activeMask) >> 2]`
  ([include/mgba/internal/arm/isa-inlines.h:76-88](../tools/mgba-master/include/mgba/internal/arm/isa-inlines.h#L76-L88),
  [src/arm/arm.c:205](../tools/mgba-master/src/arm/arm.c#L205)). Em
  [memory.c:345-346](../tools/mgba-master/src/gba/memory.c#L345-L346),
  `activeMask = memory->romMask`, calculado por `toPow2(romSize) - 1`.

  **Cuidado real:** 96 MB não é potência de 2. `toPow2(96MB)` = 128 MB, e
  `activeMask` = 0x07FFFFFF — que é justamente a máscara linear correta. O
  resultado sai certo, mas o buffer mapeado precisa ser de 128 MB (ou os
  acessos acima de `romSize` precisam continuar barrados pela comparação
  `< memory->romSize`, que já existe em todos os caminhos). A segunda opção
  é a correta e já está no código; basta não quebrá-la ao mexer nas máscaras.

- **Waitstates.** `waitstatesRegion[address >> BASE_OFFSET]`
  ([memory.c:426](../tools/mgba-master/src/gba/memory.c#L426)) indexa por
  região: 0x08/0x09 usam WS0, 0x0A/0x0B WS1, 0x0C/0x0D WS2. Continua
  funcionando; só significa que dados acima de 32 MB serão lidos com o
  timing de WS1/WS2 conforme o `WAITCNT` do jogo. Em emulador isso é
  cosmético, mas muda o número de ciclos e portanto pode deslocar
  ligeiramente o timing de DMA de áudio.

**Estimativa no emulador: ~40 linhas**, quase todas substituição mecânica
de constante. Mais o build para três plataformas.

## 3. Riscos técnicos

**Baixos, e concentrados em um lugar só.**

1. **Espelhos deixam de existir.** Qualquer código que hoje dependa de ler
   0x0A000000 e receber o conteúdo de 0x08000000 passa a ler dados
   diferentes. A varredura não achou nada assim no jogo — mas o BIOS, o
   `libagbsyscall` e o `m4a` são código pré-existente. Risco residual
   pequeno, detectável rodando a suíte de 1.027 testes depois de
   recompilar o `mgba-rom-test`.
2. **Timing de áudio.** O mixer de som roda por DMA com timer; samples
   acima de 32 MB passam a ter waitstate de WS1/WS2. Se o jogo configurar
   `WAITCNT` só pensando em WS0, o custo de leitura sobe. Mitigação: manter
   `data/sound_data.o` abaixo de 32 MB na ordem do linker, o que é fácil —
   é o primeiro objeto de `.rodata` hoje.
3. **Savestates.** `GBASerialize` grava `romSize`/`romMask`. Savestates
   feitos antes e depois do patch não serão compatíveis. Irrelevante em
   desenvolvimento, relevante se houver savestates distribuídos.
4. **Divergência do upstream.** O fork do mGBA passa a carregar um patch
   permanente em `memory.c`, o arquivo mais movimentado do core. Cada
   rebase em cima do mGBA vai ter conflito ali. É o custo recorrente real
   da abordagem — pequeno, mas para sempre.
5. **Teto de 96 MB.** A abordagem não é infinita. Dá 3,2× o espaço atual;
   com 29,66 MB hoje, sobram ~66 MB. Pelo ritmo de crescimento do projeto
   isso é bastante, mas é um teto — e, diferente de B e C, chegar nele
   exige trocar de abordagem em vez de só adicionar conteúdo.

## Por que é a recomendada

Cinco linhas no jogo, ~40 no emulador, nenhum sistema de jogo tocado,
nenhum conteúdo reautorado, e o arquivo distribuído **não cresce**. As
outras três abordagens custam uma ou duas ordens de grandeza mais para
resolver um problema que, pelos números do diagnóstico, é de 2,34 MB de
margem e não de arquitetura.

O caminho de saída também é limpo: se um dia 96 MB não bastarem, A não
atrapalha a migração para C ou D — os dados continuam onde estão e as duas
abordagens partem do mesmo lugar que partiriam hoje.
