# C) Disco virtual (registrador de I/O + arquivo externo)

**Veredito: a mais elegante conceitualmente, a segunda melhor a longo
prazo, e cara demais para o problema atual.** Vale conhecer porque é o
caminho natural se A um dia saturar.

---

## A ideia

Um registrador de I/O fictício no emulador recebe "carregue o recurso N em
tal endereço da EWRAM/VRAM". Os dados saem da ROM e vão para um arquivo
externo, sem endereço fixo. O limite de tamanho desaparece de vez.

## 1. O que muda no repositório do jogo

Este é o ponto: **C inverte o modelo de dados do jogo inteiro.**

Hoje todo dado grande é alcançado por um ponteiro constante numa tabela de
`.rodata`. `struct CompressedSpriteSheet` é
`{ const u32 *data; u16 size; u16 tag; }`
([include/sprite.h:19](../include/sprite.h#L19)). `struct ToneData` guarda
`struct WaveData *wav`
([include/gba/m4a_internal.h](../include/gba/m4a_internal.h)). Em C, esses
ponteiros viram IDs de recurso, e todo consumidor passa a ter de pedir o
recurso antes de usá-lo — e ter onde colocá-lo.

O "onde colocar" é o problema estrutural. A EWRAM tem **256 KB**
([ld_script_modern.ld:9](../ld_script_modern.ld#L9)) e já está quase toda
alocada: `.ewram.sbss` sozinho ocupa 0x3C560 = 242 KB (`objdump -h`). Não
há espaço para ser cache de um conjunto de dados de 25,62 MB. O jogo
precisaria de uma política de cache e despejo — decidir o que sai quando
algo entra — que hoje não existe em lugar nenhum.

Subsistemas afetados, com o tamanho que cada um traz:

| subsistema | objeto | tamanho | dificuldade |
|---|---|---:|---|
| Som | `data/sound_data.o` | 10,1 MB | **proibitiva** (ver risco 1) |
| Sprites de Pokémon | `src/pokemon.o` | 6,1 MB | alta — 273 pontos de descompressão |
| Tilesets | `src/tilesets.o` | 2,5 MB | **baixa** — já carregam na troca de mapa |
| Mapas | `data/maps.o` | 1,3 MB | baixa — mesma janela |
| Gráficos diversos | `src/graphics.o` | 964 KB | média |
| Sprites de overworld | `src/event_object_movement.o` | 829 KB | média |
| Fontes | `src/fonts.o` | 422 KB | alta — usadas a todo instante |

As 273 chamadas de `LZ77UnComp*`/`DecompressDataWithHeader*` em `src/` são
o mapa de calor do trabalho: cada uma é um lugar onde hoje se lê direto da
ROM e onde passaria a ser preciso garantir residência.

**Estimativa: 3.000–8.000 linhas**, mais um sistema de cache novo, mais a
reautoria de todas as tabelas de recurso (que são dados gerados — então
também mexe nas ferramentas de `graphics_file_rules.mk` e
`spritesheet_rules.mk`).

## 2. O que muda no emulador

Esta parte é surpreendentemente pequena e limpa.

Há espaço de I/O livre de sobra: `GBA_REG_MAX = 0x20A`
([include/mgba/internal/gba/io.h:154](../tools/mgba-master/include/mgba/internal/gba/io.h#L154))
enquanto a região de I/O tem 0x400 bytes (`GBA_SIZE_IO = 0x00000400`,
[memory.h:60](../tools/mgba-master/include/mgba/internal/gba/memory.h#L60)).
A faixa **0x0400020A–0x040003FE** está inteiramente livre para
registradores fictícios.

O que implementar:
- Decodificação dos registradores novos em `GBAIOWrite`/`GBAIORead`
  (`src/gba/io.c`): ID do recurso, endereço de destino, tamanho, status.
- Um `VFile` para o arquivo de recursos, usando a mesma infra que
  `matrix.c` já usa (`gba->romVf->seek`/`read`).
- Escrita direta em EWRAM/VRAM, honrando os mesmos limites de acesso a VRAM
  que o DMA honra.
- Serialização: o estado do "disco" entra no savestate.

**Estimativa: ~300–500 linhas.** Menos que B na parte de jogo? Não — mais
no jogo e parecido no emulador.

## 3. Riscos técnicos

1. **Áudio é o bloqueio duro.** O mixer lê samples continuamente por DMA a
   partir de `struct WaveData *wav`. Um sample tem de estar residente
   durante toda a reprodução. `sound/direct_sound_samples` são 40 MB no
   disco e `sound/songs` 48 MB; nada disso cabe em 256 KB de EWRAM. Para o
   maior objeto da ROM (34%), C **não funciona** sem reescrever
   `src/m4a_1.s` (2.414 linhas de ARM) para streaming — e streaming de
   áudio com o timer de DMA do GBA é um projeto por si só.
2. **Latência vira bug de jogo.** Carregar é agora uma operação com
   duração. Todo lugar que hoje assume "o dado está lá" precisa de estado
   de espera. Onde não houver, aparece sprite em branco por um frame — ou
   permanentemente, se a espera for esquecida. Compila limpo, quebra no
   jogo.
3. **Sincronia com savestates.** Savestate no meio de um carregamento
   precisa capturar a operação em curso. Um savestate que restaura
   "carregando" sem o conteúdo deixa o jogo com lixo em VRAM.
4. **Dois artefatos distribuídos.** Deixa de haver um `.gba` e passa a haver
   ROM + arquivo de recursos, que precisam casar em versão. Um patch que
   atualize um e não o outro corrompe o jogo de formas difíceis de
   diagnosticar. A distribuição hoje já prevê patch sobre a ROM do Emerald
   do usuário; isso acrescenta um segundo eixo de versionamento.
5. **Perda de ferramental.** Os dados deixam de ter endereço, então somem
   de `make syms`, do visualizador de memória do mGBA e de qualquer
   inspeção por endereço. Depurar gráfico errado fica bem mais difícil.

## Onde C brilha

Para **tilesets e mapas** (3,8 MB somados), C é quase natural: eles já são
carregados em bloco na troca de mapa, já têm um ponto de entrada único, e a
latência é escondida pela transição de tela. Uma versão reduzida de C —
disco virtual só para tileset/mapa — seria barata e traria 3,8 MB.

Mas 3,8 MB é menos do que A entrega com cinco linhas, e A entrega sem
sistema de cache nenhum. Ver
[05-abordagem-e-hibrida.md](05-abordagem-e-hibrida.md) para quando essa
versão reduzida passa a fazer sentido.
