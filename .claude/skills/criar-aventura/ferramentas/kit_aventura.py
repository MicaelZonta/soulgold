import os
"""Utilitarios da ilha: grade de blocos 2D, carimbo de mapas existentes, montanha em niveis."""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'prototipo-de-mapa'))
from mapa_kit import *

class Grid:
    def __init__(s, w, h, fill):
        s.w, s.h = w, h; s.b = [[fill] * w for _ in range(h)]
    def set(s, x, y, mid, coll=0, elev=3):
        if 0 <= x < s.w and 0 <= y < s.h: s.b[y][x] = pack_block(mid, coll, elev)
    def raw(s, x, y, v):
        if 0 <= x < s.w and 0 <= y < s.h: s.b[y][x] = v
    def flat(s): return [v for r in s.b for v in r]

_SRC = {}
def src(name):
    if name not in _SRC:
        L = load_layout(name); _SRC[name] = L
    return _SRC[name]

def stamp(g, name, sx, sy, w, h, dx, dy, skip=()):
    """Copia o retangulo (sx,sy,w,h) do map.bin de `name` para g em (dx,dy), com colisao/elevacao."""
    L = src(name)
    for y in range(h):
        for x in range(w):
            v = L['blocks'][(sy + y) * L['w'] + sx + x]
            if (v & 0x7ff) in skip: continue
            g.raw(dx + x, dy + y, v)

def nine(name, sx, sy, w, h, W, H, cx=None, cy=None, px=1, py=1):
    """Recorte (sx,sy,w,h) redimensionado para WxH repetindo as colunas cx..cx+px-1 e as
    linhas cy..cy+py-1 (periodo px/py preserva a fase). -> lista de linhas de valores."""
    L = src(name)
    cx = w // 2 if cx is None else cx; cy = h // 2 if cy is None else cy
    def mapc(X, n, c, p, N):
        if X < c: return X
        tail = n - (c + p)
        if X >= N - tail: return X - (N - n)
        return c + (X - c) % p
    out = []
    for Y in range(H):
        yy = mapc(Y, h, cy, py, H)
        out.append([L['blocks'][(sy + yy) * L['w'] + sx + mapc(X, w, cx, px, W)] for X in range(W)])
    return out

def put(g, rows, dx, dy):
    for y, r in enumerate(rows):
        for x, v in enumerate(r):
            if v is not None: g.raw(dx + x, dy + y, v)

def plateau(g, x0, y0, x1, y1, on='grass', base=True):
    """Plato de rocha (johto_general) de x0..x1, y0..y1 (inclusive). on = o que ha atras/ao redor."""
    rim = {'grass': (104, 105, 106), 'rock': (107, 108, 109), 'sand': (152, 108, 154)}[on]
    sl, sr = (112, 114) if on != 'rock' else (115, 117)
    last = y1 - (1 if base else 0)
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            L, R = x == x0, x == x1
            if y == y0:   m = rim[0] if L else rim[2] if R else rim[1]
            elif base and y == y1: m = 120 if L else 122 if R else 121
            elif y == last: m = 123 if L else 125 if R else 124
            else:         m = sl if L else sr if R else 113
            g.set(x, y, m, 1)
    for y in range(y0 + 1, last):        # topo andavel
        for x in range(x0 + 1, x1):
            g.set(x, y, 113, 0)

NB8 = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]
def learn_walls(maps, is_wall=lambda v: v >> 11 & 1):
    """Para cada celula bloqueada com vizinho andavel: assinatura dos 8 vizinhos andaveis -> Counter(id)."""
    import collections
    rules = collections.defaultdict(collections.Counter)
    for m in maps:
        L = src(m); W, H, B = L['w'], L['h'], L['blocks']
        for y in range(1, H - 1):
            for x in range(1, W - 1):
                v = B[y * W + x]
                if not is_wall(v): continue
                sig = ''.join('0' if is_wall(B[(y + dy) * W + x + dx]) else '1' for dx, dy in NB8)
                if '1' in sig: rules[sig][v & 0x7ff] += 1
    return rules

CAVE_WALL = {'00000111': 0x419, '11100000': 0x409, '00101001': 0x412, '10010100': 0x410,
        '00000001': 0x41b, '00000100': 0x41c, '00100000': 0x409, '10000000': 0x409,
        '10010111': 0x418, '00101111': 0x41a, '11101001': 0x40a, '11110100': 0x408}
def cave_wall(sig):
    if sig in CAVE_WALL: return CAVE_WALL[sig]
    NW, N, NE, W, E, SW, S, SE = (c == '1' for c in sig)
    if S and E and not N: return 0x41a
    if S and W and not N: return 0x418
    if N and E and not S: return 0x40a
    if N and W and not S: return 0x408
    if S: return 0x419
    if N: return 0x409
    if E: return 0x412
    if W: return 0x410
    if SE: return 0x41b
    if SW: return 0x41c
    return 0x409

def slide_reach(start, walk, ice, W, H):
    """BFS com deslizamento no gelo. walk(x,y) andavel; ice(x,y) desliza. -> dict celula->passos."""
    from collections import deque
    dist = {start: 0}; q = deque([start])
    while q:
        p = q.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            x, y = p
            while True:
                nx, ny = x + dx, y + dy
                if not (0 <= nx < W and 0 <= ny < H and walk(nx, ny)): break
                x, y = nx, ny
                if not ice(x, y): break
            if (x, y) not in dist:
                dist[(x, y)] = dist[p] + 1; q.append((x, y))
    return dist
