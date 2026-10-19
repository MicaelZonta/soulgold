# Agatha — Proposta Codex

Sprite de campo novo, desenhado pixel a pixel na escala do projeto: **16×22 pixels visíveis** centralizados em quadros de 32×32. O desenho respeita o limite de largura 16×32. Para comparação, a Agatha atual ocupa 16×22 e o jogador 14×19 pixels.

São 12 quadros na ordem da engine: baixo, cima, esquerda, direita, depois dois passos por direção. O corpo permanece fixo na caminhada, os sapatos terminam sempre na mesma linha e cada quadro foi verificado para evitar pixels desconectados.

- `Sprite.png`: 384×32, PNG indexado de 4 bits; índice 0 transparente.
- `Sprite.4bpp` e `Sprite.gbapal`: conversão GBA da proposta.
- `Sprite - comparacao no jogo.png`: montagem na escala do jogo, ampliada 4×; não é captura da ROM.
- `gerar_sprite.py`: fonte do desenho e das validações.

A proposta ainda não foi instalada em `graphics/object_events/`.
