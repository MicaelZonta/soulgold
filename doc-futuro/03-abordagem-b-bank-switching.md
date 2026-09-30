# B) mGBA com bank switching

**Veredito: tecnicamente viável, com precedente pronto no repo — mas é a
pior relação custo/benefício das quatro.** Paga o preço de gerenciamento
manual de bancos para resolver um problema que A resolve sem gerenciamento
nenhum.

---

## O precedente: o mapper Matrix já existe no mGBA

Achado importante: o mGBA **já implementa** um controlador de bancos para
GBA, e a fonte está no repo.

[tools/mgba-master/src/gba/cart/matrix.c](../tools/mgba-master/src/gba/cart/matrix.c)
(134 linhas) e
[include/mgba/internal/gba/cart/matrix.h](../tools/mgba-master/include/mgba/internal/gba/cart/matrix.h).

Ele faz exatamente o que a abordagem B descreve:

```c
static void _remapMatrix(struct GBA* gba) {
    ...
    gba->romVf->seek(gba->romVf, gba->memory.matrix.paddr, SEEK_SET);
    gba->romVf->read(gba->romVf, &gba->memory.rom[gba->memory.matrix.vaddr >> 2],
                     gba->memory.matrix.size);
}
```
[matrix.c:16-37](../tools/mgba-master/src/gba/cart/matrix.c#L16-L37)

Quatro registradores — `cmd`, `paddr` (endereço físico no arquivo), `vaddr`
(endereço virtual na janela), `size` — em
[matrix.c:52-80](../tools/mgba-master/src/gba/cart/matrix.c#L52-L80).

O despacho está integrado ao caminho de escrita da ROM:

```c
if (memory->matrix.size && (address & 0x01FFFF00) == 0x00800100) {
    GBAMatrixWrite(gba, address & 0x3C, value);
}
```
[memory.c:813-814](../tools/mgba-master/src/gba/memory.c#L813-L814) e
[memory.c:940-941](../tools/mgba-master/src/gba/memory.c#L940-L941)

Ou seja: o jogo troca de banco escrevendo em **0x08800100–0x0880013C**.
Ativação por `ident == 'M'` no byte 0xAC do header
([gba.c:435-440](../tools/mgba-master/src/gba/gba.c#L435-L440)) — hoje o
SoulGold tem `BPEE` ali, com `'B'` em 0xAC
([Makefile:3](../Makefile#L3)).

Serialização de savestate já resolvida em
[matrix.c:100-134](../tools/mgba-master/src/gba/cart/matrix.c#L100-L134).

### Mas a geometria dele é inutilizável

Os validadores em
[matrix.c:17-28](../tools/mgba-master/src/gba/cart/matrix.c#L17-L28)
rejeitam qualquer `vaddr` ou `size` com bits fora de `0x00001E00`:

```c
if (gba->memory.matrix.vaddr & 0xFFFFE1FF) { /* rejeita */ }
if (gba->memory.matrix.size  & 0xFFFFE1FF) { /* rejeita */ }
if ((vaddr + size - 1) & 0xFFFFE000)       { /* rejeita */ }
```

Traduzindo: `vaddr` e `size` são múltiplos de 512 e o fim tem de caber em
0x2000. A janela inteira é de **8 KB**, com 16 mapeamentos de 512 bytes
(`GBA_MATRIX_MAPPINGS_MAX 16`), e fica no **começo** do espaço de ROM —
justamente onde moram o header e o `crt0`. `paddr` é mascarado para
`0x03FFFFFF`, ou seja, arquivo de no máximo 64 MB.

Uma janela de 8 KB é irrelevante diante de `.rodata` = 25,62 MB. O mapper
foi feito para um cartucho específico que trocava um trecho pequeno, não
para um jogo cujo conteúdo é 86% dados.

**Conclusão do precedente:** não serve como está, mas serve como molde. A
estrutura (decodificação de registrador, integração no `store`, savestate,
leitura via `romVf`) é reaproveitável quase inteira, o que corta talvez
metade do trabalho de emulador da abordagem B.

## 1. O que muda no repositório do jogo

Aqui está o problema real de B, e ele não é o emulador — é o jogo.

Com bancos, **um ponteiro deixa de identificar um dado**. Ler
`gMonFrontPicTable[species].data` só faz sentido se o banco certo estiver
montado naquele instante. Isso contamina todo acesso a dado grande:

- `data/sound_data.o` (10,1 MB) — o mixer de áudio lê samples **por DMA,
  continuamente, no meio do frame**, a partir de `struct WaveData *wav`
  ([m4a_internal.h](../include/gba/m4a_internal.h)). Um banco trocado
  durante a reprodução corta o som ou toca lixo. Na prática, samples de
  DirectSound **não podem** viver em banco trocável sem reescrever o
  mixer, que é `src/m4a_1.s` — 2.414 linhas de ARM assembly.
- `src/pokemon.o` (6,1 MB) — sprites são lidos por `LZ77UnComp*` a partir
  de ponteiro de ROM. Há **273 chamadas** de descompressão em `src/`. Cada
  uma passa a precisar saber em que banco está sua fonte.
- `src/tilesets.o` (2,5 MB), `data/maps.o` (1,3 MB) — carregados na
  transição de mapa, onde um banco seria até natural. É o único
  subsistema onde B encaixa bem.

Não existe hoje nenhuma camada de indireção onde enfiar o "monte o banco N
antes de usar este ponteiro". Teria de ser criada e aplicada em cada
ponto de uso. As 273 chamadas de descompressão são só o piso: some as
tabelas de som, as de sprite de overworld
(`src/event_object_movement.o`, 829 KB) e as fontes (422 KB).

**Estimativa: 1.500–4.000 linhas**, espalhadas por dezenas de arquivos, com
mudança de contrato em estruturas de dados públicas — e, pior, com a
correção não verificável por compilação. Um banco errado compila
perfeitamente e mostra o sprite errado.

Some a isso os achados transversais de
[01-achados-transversais.md](01-achados-transversais.md), que se aplicam
igualmente.

## 2. O que muda no emulador

Menos do que se imagina, graças ao Matrix:

- Generalizar `matrix.c` para janela grande: afrouxar os validadores de
  [matrix.c:17-28](../tools/mgba-master/src/gba/cart/matrix.c#L17-L28),
  aumentar `GBA_MATRIX_MAPPINGS_MAX`, ampliar a máscara de `paddr` além de
  `0x03FFFFFF`. ~100–200 linhas.
- Ou escrever um mapper próprio no mesmo formato, plugado no mesmo ponto de
  [memory.c:813](../tools/mgba-master/src/gba/memory.c#L813). Mesma ordem
  de grandeza.
- `GBALoadROM` continua precisando aceitar arquivo grande, mas **não**
  precisa mapear tudo: é justamente a vantagem de B — a janela na memória
  do emulador permanece de 32 MB e o resto fica no arquivo.
- Savestate: `matrix` já é serializado; um mapper novo precisa do
  equivalente.

**Estimativa no emulador: ~200–300 linhas.** Comparável a A, talvez o
dobro.

## 3. Riscos técnicos

1. **Custo de cópia no meio do frame.** `_remapMatrix` faz `seek` + `read`
   síncronos. Trocar um banco de megabytes durante o gameplay causa
   engasgo. Não há DMA assíncrono nem pré-carga no modelo.
2. **Áudio é incompatível com bancos.** O mixer lê samples continuamente;
   é o maior objeto da ROM (34%) e o que menos tolera troca de banco.
   Resultado: os 10,1 MB que mais pesam são justamente os que teriam de
   ficar fora do esquema de bancos — o que derruba boa parte do ganho.
3. **Bugs silenciosos e não determinísticos.** Um banco errado não trava:
   mostra gráfico errado, toca som errado, ou mostra o certo porque por
   acaso o banco anterior ainda estava montado. É a pior classe de bug
   para depurar, e é exatamente a que o `CLAUDE.md` deste projeto trata
   como prioridade.
4. **Savestates ficam dependentes do estado de banco.** Um savestate salvo
   no meio de uma troca precisa restaurar o conteúdo da janela, não só os
   registradores. O `matrix` resolve isso remapeando na desserialização;
   um mapper novo precisa fazer igual, sob pena de savestate corrompido.
5. **Carga cognitiva permanente.** Diferente de A, B não é um patch que se
   aplica e esquece: todo conteúdo novo daqui para frente precisa ser
   alocado a um banco por alguém que entenda o esquema. Num projeto cujo
   fluxo é adicionar mapas, sprites e músicas, isso é imposto recorrente.

## Quando B faria sentido

Se o alvo fosse hardware real com flashcart, B seria a única opção da lista
— espelhos e mapeamento linear não existem em um AGB de verdade. O
enunciado, porém, dispensa hardware real explicitamente. Sem essa
restrição, B paga todos os custos de um mapper sem colher o único benefício
que justificaria tê-lo.
