#!/usr/bin/env python3
"""Brilho do portao de cristal das Ruins of Alph (Berry Master, caminho branco).

A luz que "se curva como se passasse por vidro" entre as pedras: um painel de
vidro quase invisivel (pontos gelados esparsos, para a mata aparecer atras) e um
reflexo diagonal que desce por ele, com a franja de arco-iris dos cristais de
Greenfield. 5 quadros de 16x32: 0 = so o vidro (fica parado mais tempo), 1..4 =
o reflexo descendo. Sai indexado, 16 cores, indice 0 transparente.

    python3 dev_scripts/sprites/brilho_portal_cristal.py [saida.png]
"""
import sys
from PIL import Image

OUT = sys.argv[1] if len(sys.argv) > 1 else 'graphics/object_events/pics/misc/crystal_glint.png'
W, H, N = 16, 32, 5

PAL = [
    (255, 0, 255),    # 0 transparente
    (248, 248, 248),  # 1 branco
    (208, 240, 248),  # 2 ciano palido
    (160, 216, 240),  # 3 ciano claro
    (112, 176, 232),  # 4 azul gelo
    (248, 136, 144),  # 5 franja vermelha
    (248, 224, 128),  # 6 franja amarela
    (152, 232, 168),  # 7 franja verde
    (184, 160, 248),  # 8 franja violeta
]
PAL += [(0, 0, 0)] * (16 - len(PAL))


def vidro(px, f):
    # duas bordas do painel em pontilhado cerrado (1 sim, 1 nao) que anda 1 px
    # por quadro, e um veio claro no meio: visivel de longe, mas a mata ainda
    # aparece entre os pontos
    for y in range(3, 31):
        if (y + f) % 2 == 0:
            px[3, y] = 3
            px[12, y] = 3
        else:
            px[4, y] = 2
            px[11, y] = 2
        if (y + f) % 4 == 1:
            px[7, y] = 2
            px[8, y + 1 if y < 30 else y] = 3
    for x in range(3, 13):
        if (x + f) % 2 == 0:
            px[x, 2] = 4
            px[x, 31] = 4


def reflexo(px, y0):
    # faixa diagonal de 3 px (ciano, branco, ciano) de borda a borda, subindo
    # 1 px a cada 2 colunas; franja de arco-iris logo abaixo
    franja = [5, 6, 7, 8]
    for i, x in enumerate(range(3, 13)):
        y = y0 - i // 2
        for dy, c in ((-2, 2), (-1, 1), (0, 1), (1, 2)):
            if 0 <= y + dy < H:
                px[x, y + dy] = c
        if 0 <= y + 2 < H:
            px[x, y + 2] = franja[i % 4]


def faisca(px, x, y, grande):
    # estrela de 4 pontas: centro branco, bracos ciano (2 px na grande)
    px[x, y] = 1
    for d in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        for k in range(1, 3 if grande else 2):
            xx, yy = x + d[0] * k, y + d[1] * k
            if 0 <= xx < W and 0 <= yy < H:
                px[xx, yy] = 1 if k == 1 and grande else 3


im = Image.new('P', (W * N, H), 0)
im.putpalette([c for rgb in PAL for c in rgb])
FAISCAS = {0: [(13, 6, True)], 1: [(2, 20, False)], 2: [(13, 12, True), (5, 27, False)],
           3: [(2, 8, True)], 4: [(12, 25, True), (6, 4, False)]}
for f in range(N):
    q = Image.new('P', (W, H), 0)
    px = q.load()
    vidro(px, f)
    if f:
        reflexo(px, 8 + (f - 1) * 6)
    for x, y, g in FAISCAS[f]:
        faisca(px, x, y, g)
    im.paste(q, (f * W, 0))
im.save(OUT)
print('ok', OUT, im.size)
