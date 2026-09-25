# doc-futuro — como ultrapassar o limite de 32 MB de ROM

Auditoria comparativa das formas de tirar o SoulGold do teto de
endereçamento do GBA. Feita sobre o código real deste repositório em
22/09/2026 (commit `179a1196f9`, branch `soulgold-rift-missions`) e sobre a
árvore do mGBA 0.11.0 em `tools/mgba-master/`.

Nada foi alterado fora deste diretório. Nenhum commit foi feito.

## Recomendação

**Abordagem A — mapeamento linear 0x08000000–0x0DFFFFFF — com uma correção
importante na proposta original.**

Custo total: **~5 linhas** no repositório do jogo, **~40 linhas** no
emulador, nenhum sistema de jogo afetado, nenhum conteúdo reautorado, e o
`.gba` distribuído **não muda de tamanho**.

As duas descobertas que sustentam isso:

1. **O split de seções proposto não é necessário e custaria 27,96 MB.** As
   regiões de ROM do GBA são contíguas; com mapeamento linear basta uma
   única região de 96 MB no linker e as seções atravessam 0x0A000000
   sozinhas. Forçar `.rodata` para 0x0A000000 abriria um buraco real de
   `0xFF` no arquivo, levando o `.gba` de 29,66 MB para 57,62 MB.
2. **O mapeamento linear é uma troca de constante no mGBA.** Todo acesso à
   ROM passa por `address & 0x01FFFFFF`, e é essa máscara que cria os
   espelhos. Como 0x08–0x0D são contíguos, `address & 0x07FFFFFF` é
   exatamente `address − 0x08000000` em toda a faixa. Não há lógica nova a
   escrever.

## Comparação

| | A — linear | B — bancos | C — disco virtual | D — port nativo |
|---|---|---|---|---|
| Teto | 96 MB | ilimitado | ilimitado | ilimitado |
| Linhas no jogo | **~5** | 1.500–4.000 | 3.000–8.000 | 20.000+ |
| Linhas no emulador | ~40 | 200–300 | 300–500 | — (substitui) |
| Sistemas de jogo tocados | **nenhum** | som, gráficos, mapas | todos os de dados | todos |
| Tamanho do `.gba` | **inalterado** | menor | menor + 2º arquivo | n/a |
| Funciona para áudio (34% da ROM) | **sim** | não | não | sim |
| Bugs silenciosos introduzidos | poucos | **muitos** | muitos | muitos |
| Mantém Porymap / testes / BPS | **sim** | sim | parcial | **não** |
| Custo recorrente | rebase do patch | **alocar banco por asset** | versionar 2 artefatos | — |

## Documentos

| | |
|---|---|
| [00-diagnostico.md](00-diagnostico.md) | Onde o projeto está: 29,66 MB reais, 2,34 MB de margem, quem ocupa o espaço, o toolchain, a infra de testes |
| [01-achados-transversais.md](01-achados-transversais.md) | **Cinco bugs que atingem A, B e C igualmente** e não aparecem em nenhuma das propostas. Três falham em silêncio |
| [02-abordagem-a-linear.md](02-abordagem-a-linear.md) | A recomendada, com o patch exato |
| [03-abordagem-b-bank-switching.md](03-abordagem-b-bank-switching.md) | Bancos — inclui o mapper Matrix que já existe no mGBA |
| [04-abordagem-c-disco-virtual.md](04-abordagem-c-disco-virtual.md) | Disco virtual — elegante, cara, bloqueada no áudio |
| [05-abordagem-d-port-nativo.md](05-abordagem-d-port-nativo.md) | Port SDL — destino final, decisão errada agora |
| [06-abordagem-e-hibrida.md](06-abordagem-e-hibrida.md) | Abordagem adicional: linear agora, disco virtual seletivo depois |

## Achados que valem a leitura mesmo se a decisão for outra

- **`ROM_END` é 0x0A000000** e há um range-check usando ele em
  [src/field_name_box.c:196](../src/field_name_box.c#L196), no sistema de
  plaquinha de falante desta branch. Uma string de nome acima de
  0x0A000000 faz a plaquinha **sumir em silêncio**.
- **O `malloc` empacota ponteiros de ROM em 25 bits** (`locationHi:11` +
  `locationLo:14` em [include/malloc.h](../include/malloc.h)) — exatamente
  32 MB. Acima disso, `MemBlockLocation()` mente. Há 4 bits livres ao lado
  para corrigir.
- **`gbafix -p` arredonda para potência de 2**
  ([Makefile:657](../Makefile#L657)). Os 32 MB do arquivo atual são padding:
  o conteúdo é 29,66 MB. No primeiro byte acima de 32 MB, o arquivo vira
  **64 MB**.
- **`make syms` filtra `^0[2389]`** ([Makefile:665](../Makefile#L665)) —
  símbolos em 0x0A–0x0D somem, ou seja, 86% da ROM ficaria sem símbolo
  justamente na depuração da migração.
- **`make check` roda 1.027 testes num `mgba-rom-test` pré-compilado**
  ([Makefile:232](../Makefile#L232)), sem fonte em `tools/mgba/`. Passou de
  32 MB, ele trunca a ROM e os testes falham em massa. Vale para A, B e C.
- **O mGBA já tem um bank switcher** (`src/gba/cart/matrix.c`), com
  registradores em 0x08800100 e savestate resolvido — mas a janela dele é
  de **8 KB** no início da ROM, inutilizável aqui. Serve como molde, não
  como solução.
- **O motor de som usa ponteiro de 32 bits puro** (`struct WaveData *wav`),
  sem empacotamento. Os 10,1 MB de `sound_data.o` migram sem tocar no
  `m4a` — é o que torna A barata e o que B e C não conseguem replicar.

## Nota sobre o entregável

O pedido inicial citava `RELATORIO_LIMITE_ROM.md` na raiz; a instrução
final pediu tudo dentro de `doc-futuro/`. Segui a segunda — o arquivo na
raiz não foi criado. Se quiser os dois, é só dizer.
