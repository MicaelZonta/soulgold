#!/usr/bin/env python3
"""Compara dois map.bin do mesmo layout e mostra o que mudou - para aprender com a edicao
que o usuario fez no Porymap em cima de um mapa gerado (ou entre duas versoes).

    python3 .claude/skills/acabamento-de-mapa/diff_mapas.py ANTES.bin DEPOIS.bin --layout SunMoonAltar \
        [--png comparacao.png]

Imprime: quantas celulas mudaram, as substituicoes mais comuns (metatile antes -> depois),
mudancas so de colisao/elevacao, e a grade com as celulas alteradas. Com --png, renderiza
ANTES | DEPOIS lado a lado com as celulas mudadas contornadas.
Metatile >= 1024 aparece como sN (N = indice no secundario).
"""
import argparse, collections, os, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'prototipo-de-mapa'))
from mapa_kit import load_layout, read_blocks, render_blocks, write_png, swap_slots

ap = argparse.ArgumentParser()
ap.add_argument('antes'); ap.add_argument('depois')
ap.add_argument('--layout', required=True, help='nome do mapa/layout (tilesets e largura)')
ap.add_argument('--png')
a = ap.parse_args()

L = load_layout(a.layout)
W, H = L['w'], L['h']
A, B = read_blocks(a.antes), read_blocks(a.depois)
assert len(A) == len(B) == W * H, 'tamanhos diferentes: %d %d (layout %dx%d)' % (len(A), len(B), W, H)
name = lambda v: str(v & 0x7ff) if (v & 0x7ff) < 1024 else 's%d' % ((v & 0x7ff) - 1024)

subs, flags, changed = collections.Counter(), collections.Counter(), set()
for i, (x, y) in enumerate(zip(A, B)):
    if x == y:
        continue
    changed.add(i)
    if (x & 0x7ff) != (y & 0x7ff):
        subs[(name(x), name(y))] += 1
    else:
        flags[('colisao %d->%d' % (x >> 11 & 1, y >> 11 & 1), 'elevacao %d->%d' % (x >> 12, y >> 12))] += 1
print('celulas mudadas: %d de %d' % (len(changed), W * H))
print('\nsubstituicoes mais comuns (antes -> depois):')
for (x, y), n in subs.most_common(40):
    print('  %6s -> %-6s x%d' % (x, y, n))
if flags:
    print('\nso colisao/elevacao:')
    for k, n in flags.most_common():
        print('  %s, %s x%d' % (k[0], k[1], n))
print('\ngrade (. igual, # mudou):')
for y in range(H):
    print('%3d ' % y + ''.join('#' if y * W + x in changed else '.' for x in range(W)))

if a.png:
    swap = swap_slots(L['info']['primary_tileset']) + swap_slots(L['info']['secondary_tileset'])
    ra = render_blocks(A, W, H, L['prim'], L['sec'], swap=swap)
    rb = render_blocks(B, W, H, L['prim'], L['sec'], swap=swap)
    for img in (ra, rb):
        for i in changed:
            x0, y0 = (i % W) * 16, (i // W) * 16
            for k in range(16):
                for p in (0, 15):
                    img[y0 + p][x0 + k] = (255, 0, 255)
                    img[y0 + k][x0 + p] = (255, 0, 255)
    gap = [(40, 40, 40)] * 8
    write_png(a.png, [ra[y] + gap + rb[y] for y in range(H * 16)], 2)
    print('\n->', a.png)
