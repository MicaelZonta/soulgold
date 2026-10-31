import os
"""Clona um secundario e encaixa um desenho (Tela) nos tiles e indices de paleta livres.
Devolve os ids dos metatiles novos (grade cols x rows) para gravar no map.bin."""
import sys, os, shutil, struct, glob
SC = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SC); sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'montar-tileset'))
from tileset_kit import *
from desenho import reduzir
ROOTD = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..', '..', 'data', 'tilesets', 'secondary') + '/'

def clone(src, dst):
    d = ROOTD + dst
    if not os.path.exists(d):
        shutil.copytree(ROOTD + src, d, ignore=shutil.ignore_patterns('*.4bpp*', '*.gbapal', '*.fastSmol', '*.smol'))
    return d

def c5(c): return tuple((v >> 3) << 3 for v in c)

def install(dst, art, ground_entries, max_colors=15):
    """art: Tela (w,h multiplos de 16). ground_entries(c,r) -> 4 entradas da camada de baixo.
    -> grade [[metatile_id_secundario]] (ja somado 1024)."""
    d = ROOTD + dst
    T = load_tileset(None, path=d)
    W, H, _, idx, pngpal = read_png(d + '/tiles.png')
    ntiles = (W // 8) * (H // 8)
    used_t = set(); usage = {s: set() for s in range(16)}
    for m in T['metas']:
        for e in m:
            t = e & 0x3ff
            if t >= 640:
                used_t.add(t - 640)
                if t - 640 < len(T['tiles']):
                    for row in T['tiles'][t - 640]: usage[e >> 12].update(row)
    free_tiles = [i for i in range(1, 384) if i not in used_t]
    pals = {s: read_pal(d + '/palettes/%02d.pal' % s) for s in range(13)}
    # escolhe o slot: reaproveita cor exata (em 5 bits) e usa indices livres para o resto
    best = None
    for n in range(max_colors, 3, -1):
        a = reduzir(art_copy(art), n)
        cols = [c5(c) for c in a.colors()]
        for s in range(7, 13):
            ex = {c5(pals[s][i]): i for i in usage[s] - {0}}
            freei = [i for i in range(1, 16) if i not in usage[s]]
            need = [c for c in cols if c not in ex]
            if len(need) <= len(freei):
                best = (s, a, ex, freei, need); break
        if best: break
    assert best, 'nao coube paleta'
    s, a, ex, freei, need = best
    cmap = dict(ex)
    for c, i in zip(need, freei):
        cmap[c] = i; pals[s][i] = c
    write_pal(d + '/palettes/%02d.pal' % s, pals[s])
    # corta em tiles 8x8 com indices do slot s
    tw, th = a.w // 8, a.h // 8
    newtiles = {}; bank = {}
    def key(t): return t
    def flipsets(t):
        return [(t, 0, 0), (tuple(r[::-1] for r in t), 1, 0), (tuple(t[::-1]), 0, 1), (tuple(r[::-1] for r in t[::-1]), 1, 1)]
    fi = iter(free_tiles)
    for ty in range(th):
        for tx in range(tw):
            t = tuple(tuple(cmap[c5(a.p[ty * 8 + y][tx * 8 + x])] if a.p[ty * 8 + y][tx * 8 + x] is not None else 0
                            for x in range(8)) for y in range(8))
            if not any(any(r) for r in t): newtiles[(tx, ty)] = None; continue
            hit = None
            for v, hf, vf in flipsets(t):
                if v in bank: hit = (bank[v], hf, vf); break
            if not hit:
                ti = next(fi); bank[t] = ti; hit = (ti, 0, 0)
                for y in range(8):
                    for x in range(8): idx[(ti // 16) * 8 + y][(ti % 16) * 8 + x] = t[y][x]
            newtiles[(tx, ty)] = hit
    write_png_indexed4(d + '/tiles.png', idx, pngpal if pngpal else pals[s])
    # metatiles: chao em baixo, desenho no meio
    metas = open(d + '/metatiles.bin', 'rb').read(); attrs = open(d + '/metatile_attributes.bin', 'rb').read()
    base = len(metas) // 24
    grid = []; out = bytearray(metas); outa = bytearray(attrs)
    for r in range(a.h // 16):
        row = []
        for c in range(a.w // 16):
            q = []
            for k in range(4):
                h = newtiles[(c * 2 + k % 2, r * 2 + k // 2)]
                q.append(0 if h is None else entry(NUM_TILES_IN_PRIMARY + h[0], h[1], h[2], s))
            m = list(ground_entries(c, r)) + q + [0] * 4
            out += struct.pack('<12H', *m); outa += struct.pack('<H', 0)
            row.append(1024 + base + len(row) + r * (a.w // 16))
        grid.append(row)
    open(d + '/metatiles.bin', 'wb').write(out); open(d + '/metatile_attributes.bin', 'wb').write(outa)
    print(dst, 'slot', s, 'cores', len(a.colors()), 'tiles novos', len(bank), 'metatiles', base, '..', len(out) // 24 - 1)
    return grid

def art_copy(t):
    import copy; return copy.deepcopy(t)
