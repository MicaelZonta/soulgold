#!/usr/bin/env python3
"""Gerador REAL do gTileset_UltraSpaceArena e do map.bin/border.bin do UltraSpaceArena (21x21).

    python3 .claude/skills/montar-tileset/exemplo_arena_ultra_espaco.py SAIDA/

Tecnicas alem do altar: cena inteira num canvas so; carimbo (stamp) de pecas repetidas
alinhadas a 8 px (a copia custa 0 tile); detalhe de variante preso a um quadrante 8x8;
segunda camada ov para a camada TOP (cristal dos lampioes cobre quem passa atras).

Mapa impar (21x21) com a COLUNA 10 no centro: pontes, encaixes e fendas tem 3 celulas de
largura, e jogador, oponente e lendario ficam todos na coluna 10.
O centro em pixel e x = 168, que cai numa borda de tile de 8: a metade esquerda e desenhada
e espelhada, e a direita sai de graca por hflip.
"""
import json, math, os, struct, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'prototipo-de-mapa'))
from mapa_kit import *

OUT = sys.argv[1] if len(sys.argv) > 1 else 'arena_out'
os.makedirs(OUT, exist_ok=True)
N = 21                      # celulas
S = N * 16                  # 336 pixels
C = S // 2                  # 168: centro da celula 10 e borda de tile
MID = 10                    # coluna/linha do centro
h = noise

# =========================================================================== cores
VOID = (14, 9, 32)
CORE = (3, 2, 9)
NEB = [(34, 16, 70), (62, 28, 118), (104, 50, 170), (150, 92, 222), (204, 164, 250)]
STAR = [(255, 255, 255), (206, 188, 255), (150, 204, 255), (255, 232, 150)]
OUTL = (16, 12, 30)
ST = [(178, 180, 222), (132, 132, 184), (98, 96, 148), (70, 66, 114), (46, 41, 80)]
CR = [(244, 252, 255), (172, 232, 255), (130, 160, 250), (100, 80, 204)]
GOLD = [(255, 250, 212), (250, 216, 112), (214, 160, 60), (146, 96, 42)]
FL = [(246, 244, 255), (222, 218, 246), (198, 192, 232), (166, 158, 210)]
RIFT = [(255, 255, 255), (184, 244, 255), (112, 196, 252), (164, 112, 250), (214, 84, 214), (92, 40, 152)]

COLORS = {'void': (VOID, None), 'core': (CORE, None), 'out': (OUTL, None)}
COLORS.update({'n%d' % i: (c, None) for i, c in enumerate(NEB)})
COLORS.update({'*%d' % i: (c, None) for i, c in enumerate(STAR)})
COLORS.update({'s%d' % i: (c, None) for i, c in enumerate(ST)})
COLORS.update({'c%d' % i: (c, None) for i, c in enumerate(CR)})
COLORS.update({'g%d' % i: (c, None) for i, c in enumerate(GOLD)})
COLORS.update({'f%d' % i: (c, None) for i, c in enumerate(FL)})
COLORS.update({'p%d' % i: (c, None) for i, c in enumerate(RIFT)})

PAL = PaletteSet({
    7:  ['void', 'core', 'n0', 'n1', 'n2', 'n3', 'n4', '*0', '*1', '*2', '*3'],                       # vazio
    8:  ['void', 'out', 's0', 's1', 's2', 's3', 's4', 'c0', 'c1', 'c2', 'c3', '*0', '*1', '*2', 'n3'], # pedra e cristal
    9:  ['out', 's1', 's2', 's3', 's4', 'g0', 'g1', 'g2', 'g3', 'f0', 'f1', 'f2', 'f3', 'c0', 'c1'],   # piso, ouro, luz
    11: ['void', 'out', 's1', 's2', 's3', 's4', 'p0', 'p1', 'p2', 'p3', 'p4', 'p5', 'n2', 'n3', 'c1'], # fendas
}, COLORS, order=[7, 8, 9, 11])

cv = Canvas(S, S)
cv.rect(0, 0, S - 1, S - 1, 'void')
put, get = cv.put, cv.get
def in_map(x, y): return 0 <= x < S and 0 <= y < S
STONE = ('s0', 's1', 's2', 's3', 's4')

# =========================================================================== geometria (celulas)
def platform(c, r):
    dx, dy = abs(c - MID), abs(r - MID)
    return dx + dy <= 6 or (dx <= 1 and dy <= 6) or (dy <= 1 and dx <= 6)
PLAT = {(c, r) for c in range(N) for r in range(N) if platform(c, r)}
AXIS = (MID - 1, MID, MID + 1)                              # caminhos de 3 celulas
BRIDGE_V = {(c, r) for c in AXIS for r in (2, 3, 17, 18)}
BRIDGE_H = {(c, r) for r in AXIS for c in (2, 3, 17, 18)}
PAD_N = {(c, r) for c in AXIS for r in (0, 1)}
PAD_S = {(c, r) for c in AXIS for r in (19, 20)}
PAD_W = {(c, r) for r in AXIS for c in (0, 1)}
PAD_E = {(c, r) for r in AXIS for c in (19, 20)}
PAD = PAD_N | PAD_S | PAD_W | PAD_E
LAMPS = [(MID - 3, MID - 3), (MID + 3, MID - 3), (MID - 3, MID + 3), (MID + 3, MID + 3)]
SOLID = PLAT | BRIDGE_V | BRIDGE_H | PAD

def solid_px(x, y):
    return in_map(x, y) and (x // 16, y // 16) in SOLID

# =========================================================================== piso de pedra (4 lajes)
def slab(x, y, var):
    lx, ly = x % 16, y % 16
    if lx == 15 or ly == 15: return 's4'
    if lx == 14 or ly == 14: return 's3'
    if ly == 0 or lx == 0: return 's1'
    if ly == 1 and lx < 13: return 's1' if lx % 3 else 's2'
    n = h(lx * 31 + ly * 7)
    k = 's2'
    if n % 11 == 0: k = 's3'
    elif n % 17 == 1: k = 's1'
    if var == 1:                                        # rachadura com borda iluminada
        crack = {(2, 3), (3, 3), (4, 4), (4, 5), (5, 6), (6, 6)}
        if (lx, ly) in crack: return 's4'
        if (lx - 1, ly - 1) in crack or (lx, ly - 1) in crack: return 's1'
    if var == 2 and lx + ly >= 22:                      # canto lascado
        return 's3' if lx + ly == 22 else 's4' if lx + ly == 23 else k
    if var == 4:                                        # quatro tijolos pequenos
        if lx in (7, 8) or ly in (7, 8):
            return 's4' if (lx == 7 or ly == 7) else 's1'
    if var == 3:                                        # veio de cristal
        vein = {(9, 4): 'c0', (10, 5): 'c1', (8, 5): 'c1', (9, 5): 'c1', (9, 6): 'c1', (10, 6): 's4', (9, 7): 's4'}
        if (lx, ly) in vein: return vein[(lx, ly)]
    return k

for (c, r) in PLAT:
    var = [0, 4, 1, 0, 2, 4, 3, 0, 1, 0, 4][h(min(c, 2 * MID - c) * 13 + r * 71) % 11]
    for y in range(r * 16, r * 16 + 16):
        for x in range(c * 16, c * 16 + 16):
            put(x, y, slab(x, y, var))

# =========================================================================== losango claro com borda de ouro
def man(x, y): return abs(x + .5 - C) + abs(y + .5 - C)
RIM = [(57, 'g3'), (58, 'g1'), (59, 'g0'), (60, 'g1'), (61, 'g2'), (62, 'g3'), (63, 'out')]
for y in range(C - 64, C + 64):
    for x in range(C - 64, C + 64):
        m = man(x, y)
        if m < 57:
            lx, ly = x % 16, y % 16
            k = 'f1'
            if lx == 0 or ly == 0: k = 'f2'
            elif lx == 15 or ly == 15: k = 'f0'
            elif h(lx * 13 + ly * 17) % 23 == 0: k = 'f0'
            if m > 53: k = 'f2' if k != 'f0' else 'f1'
            put(x, y, k)
        elif m < 64:
            for lim, k in RIM:
                if m < lim + 1:
                    put(x, y, k); break
# pinos de ouro no meio de cada lado do losango
for (sx, sy) in ((C - 30, C - 30), (C - 30, C + 29)):
    for (dx, dy, k) in ((0, 0, 'g0'), (-1, 0, 'g1'), (1, 0, 'g2'), (0, -1, 'g1'), (0, 1, 'g2'),
                        (-1, -1, 'g3'), (1, 1, 'g3'), (-1, 1, 'g3'), (1, -1, 'g3')):
        put(sx + dx, sy + dy, k)

# =========================================================================== emblema (Ultra Necrozma estilizado)
EM = {}
O = 8                                          # o desenho foi feito para centro 160; o novo e 168
def tri(a, b, c_, k):
    a, b, c_ = [(p[0] + O, p[1] + O) for p in (a, b, c_)]
    xs = [a[0], b[0], c_[0]]; ys = [a[1], b[1], c_[1]]
    for y in range(int(min(ys)), int(max(ys)) + 1):
        for x in range(int(min(xs)), int(max(xs)) + 1):
            px, py = x + .5, y + .5
            d1 = (px - b[0]) * (a[1] - b[1]) - (a[0] - b[0]) * (py - b[1])
            d2 = (px - c_[0]) * (b[1] - c_[1]) - (b[0] - c_[0]) * (py - c_[1])
            d3 = (px - a[0]) * (c_[1] - a[1]) - (c_[0] - a[0]) * (py - a[1])
            if not ((d1 < 0 or d2 < 0 or d3 < 0) and (d1 > 0 or d2 > 0 or d3 > 0)) and x < C:
                EM[(x, y)] = k
def quad(a, b, c_, d, k):
    tri(a, b, c_, k); tri(a, c_, d, k)
quad((152, 128), (134, 126), (128, 134), (151, 141), 'g1')
tri((142, 128), (135, 118), (137, 129), 'g1')
quad((150, 144), (118, 146), (108, 155), (150, 156), 'g1')
tri((124, 147), (114, 140), (120, 148), 'g1')
quad((151, 159), (124, 170), (127, 180), (152, 170), 'g1')
tri((134, 175), (133, 190), (140, 173), 'g1')
quad((160, 110), (146, 150), (160, 204), (160, 204), 'g2')
quad((160, 118), (151, 150), (160, 184), (160, 184), 'g1')
tri((160, 98), (156, 116), (160, 118), 'g1')
tri((151, 104), (151, 122), (156, 118), 'g1')
tri((160, 202), (157, 206), (160, 214), 'g2')
for y in range(140 + O, 160 + O):
    for x in range(150 + O, C):
        d = abs(x + .5 - C) + abs(y + .5 - (150 + O))
        if d < 8.5: EM[(x, y)] = 'c0' if d < 2.5 else 'f0' if d < 4.5 else 'g0'
for (sx, sy, rr) in ((136 + O, 194 + O, 4), (147 + O, 211 + O, 3)):
    for y in range(sy - rr, sy + rr):
        for x in range(sx - rr, sx + rr):
            if abs(x + .5 - sx) + abs(y + .5 - sy) < rr: EM[(x, y)] = 'g1'
def emblem_key(x, y):
    return EM.get((x, y)) if x < C else EM.get((2 * C - 1 - x, y))
# brilho em volta (piso mais claro) e sombra embaixo a direita
for (x, y) in list(EM):
    for (dx, dy) in ((-1, 0), (0, -1), (-1, -1), (-2, 0), (0, -2)):
        if emblem_key(x + dx, y + dy) is None and get(x + dx, y + dy) in ('f1', 'f2'):
            put(x + dx, y + dy, 'f0')
for (x, y) in list(EM):
    if emblem_key(x + 1, y + 1) is None and get(x + 1, y + 1) in ('f0', 'f1', 'f2'):
        put(x + 1, y + 1, 'f3')
for (x, y), k in EM.items():
    nb = [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]
    if any(emblem_key(*p) is None for p in nb): kk = 'g3'
    elif k == 'g1' and (emblem_key(x - 1, y - 1) is None or emblem_key(x, y - 2) is None): kk = 'g0'
    elif k == 'g1' and (emblem_key(x + 1, y + 1) is None or emblem_key(x + 2, y) is None): kk = 'g2'
    else: kk = k
    put(x, y, kk)

# =========================================================================== encaixes (chao, com luz no centro)
def socket(cx, cy):
    for y in range(cy - 10, cy + 10):
        for x in range(cx - 10, cx + 10):
            ax, ay = abs(x + .5 - cx), abs(y + .5 - cy)
            m = ax + ay
            if max(ax, ay) > 9: k = 'out'
            elif max(ax, ay) > 8: k = 's1' if (y < cy - 8 or x < cx - 8) else 's3'
            elif m < 1.5: k = 'c0'
            elif m < 3: k = 'c1'
            elif m < 4: k = 'g0'
            elif m < 5.5: k = 's4'
            elif m < 6.5: k = 'g0'
            elif m < 8: k = 'g1'
            elif m < 9: k = 'g3'
            else: k = 's4' if (x + y) % 2 else 's3'
            put(x, y, k)
socket(C, 5 * 16 + 8); socket(C, 15 * 16 + 8); socket(5 * 16 + 8, C); socket(15 * 16 + 8, C)

# =========================================================================== borda externa da plataforma
def edge_pass(cells):
    for (c, r) in cells:
        for y in range(r * 16, r * 16 + 16):
            for x in range(c * 16, c * 16 + 16):
                if get(x, y) not in STONE: continue
                n_, s_ = not solid_px(x, y - 1), not solid_px(x, y + 1)
                w_, e_ = not solid_px(x - 1, y), not solid_px(x + 1, y)
                if n_ or s_ or w_ or e_: put(x, y, 'out')
                elif not solid_px(x, y - 2) or not solid_px(x - 2, y): put(x, y, 's1')
                elif not solid_px(x, y - 3): put(x, y, 's2')
                elif not solid_px(x + 2, y) or not solid_px(x, y + 2): put(x, y, 's3')
edge_pass(PLAT)

# =========================================================================== lampioes (bloqueiam)
# Pilar na celula do lampiao; o cristal flutua na celula de CIMA, desenhado na camada top
# (ov): quem passa atras do lampiao fica atras do cristal, como deve ser.
ov = Canvas(S, S)
def lamp(cc, rr):
    X, Y = cc * 16, rr * 16
    cx = X + 8
    for y in range(Y, Y + 16):                                      # luz no chao em volta da base
        for x in range(X, X + 16):
            d = math.hypot(x + .5 - cx, (y + .5 - (Y + 12)) * 1.4)
            k = get(x, y)
            if k in ('s2', 's3', 's4') and d < 8.5:
                put(x, y, 's1' if d < 5.5 else ('c2' if (x + y) % 2 == 0 else 's1') if d < 7 else ('s1' if (x + y) % 2 else k))
    for y in range(Y + 10, Y + 15):                                 # plinto
        for x in range(X + 2, X + 14):
            lx, ly = x - (X + 2), y - (Y + 10)
            if lx in (0, 11) or ly == 4: k = 'out'
            elif ly == 0: k = 's0' if lx < 8 else 's1'
            elif ly == 1: k = 's1' if lx < 3 else 's2' if lx < 9 else 's3'
            else: k = 's2' if lx < 3 else 's3' if lx < 9 else 's4'
            put(x, y, k)
    for y in range(Y + 2, Y + 10):                                  # fuste com runa acesa
        for x in range(X + 5, X + 11):
            put(x, y, ['out', 's1', 's2', 's3', 's4', 'out'][x - (X + 5)])
    for (x, y, k) in ((cx - 1, Y + 4, 'c2'), (cx - 1, Y + 5, 'c1'), (cx, Y + 5, 'c2'), (cx - 1, Y + 6, 'c0'),
                      (cx, Y + 6, 'c1'), (cx - 1, Y + 7, 'c2')):
        put(x, y, k)
    for y in range(Y, Y + 3):                                       # capitel iluminado por cima
        for x in range(X + 4, X + 12):
            lx, ly = x - (X + 4), y - Y
            if lx in (0, 7) or ly == 2: k = 'out'
            elif ly == 0: k = 'c2' if 2 <= lx <= 5 else 's0'
            else: k = 's1' if lx < 4 else 's2'
            put(x, y, k)
    ccy = Y - 7                                                     # cristal flutuante (camada top)
    for y in range(ccy - 7, ccy + 7):
        for x in range(cx - 5, cx + 5):
            ax, dy = abs(x + .5 - cx), y + .5 - ccy
            v = ax / 4.2 + abs(dy) / 6.6
            if v > 1: continue
            left = x < cx
            if v > .78: k = 'c3'
            elif dy < 0: k = 'c0' if left else 'c1'
            else: k = 'c1' if left else 'c2'
            ov.put(x, y, k)
    ov.put(cx - 2, ccy - 3, '*0'); ov.put(cx - 2, ccy - 2, '*0'); ov.put(cx - 1, ccy - 4, '*0')
    for (dx, dy, k) in ((-7, -1, '*1'), (6, 1, '*2'), (-1, -9, '*1'), (-5, -6, '*2'), (5, -6, 'c1'),
                        (-5, 5, 'c2'), (4, 6, 'c1'), (-8, 3, 'c2')):
        ov.put(cx + dx, ccy + dy, k)
for (c, r) in LAMPS:
    lamp(c, r)

# =========================================================================== pontes (3 de largura) e degraus
LO = (MID - 1) * 16                                   # 144: comeco da faixa da ponte
def bridge_px(a, b):
    la = a - LO                                       # 0..47 atravessado
    if la in (0, 47): return 'out'
    if la == 1: return 'g0'
    if la == 2: return 'g1'
    if la == 45: return 'g2'
    if la == 46: return 'g3'
    lb = b % 16
    if lb == 0 or la in (16, 32): return 'f2'
    if la in (17, 33) or lb == 1: return 'f0'
    return 'f0' if la == 3 else 'f3' if la == 44 else 'f1'
def stairs_px(a, b, down):
    la = a - LO
    if la < 3 or la > 44: return bridge_px(a, b)
    s = (b % 16) if down else 15 - (b % 16)
    return ['f0', 'f1', 'f2', 'f3'][s % 4]
def star_inlay(cx, cy):
    pts = {(0, 0): 'g0', (-1, 0): 'g1', (1, 0): 'g1', (0, -1): 'g1', (0, 1): 'g1',
           (-2, 0): 'g2', (2, 0): 'g2', (0, -2): 'g2', (0, 2): 'g2', (0, -3): 'g3', (0, 3): 'g3',
           (-3, 0): 'g3', (3, 0): 'g3', (-1, -1): 'g2', (1, 1): 'g2', (-1, 1): 'g2', (1, -1): 'g2'}
    for (dx, dy), k in pts.items():
        put(cx + dx, cy + dy, k)
STAIRS_V = {3: True, 17: False}
STAIRS_H = {3: True, 17: False}
for (c, r) in BRIDGE_V:
    for y in range(r * 16, r * 16 + 16):
        for x in range(c * 16, c * 16 + 16):
            put(x, y, stairs_px(x, y, STAIRS_V[r]) if r in STAIRS_V else bridge_px(x, y))
for (c, r) in BRIDGE_H:
    for y in range(r * 16, r * 16 + 16):
        for x in range(c * 16, c * 16 + 16):
            put(x, y, stairs_px(y, x, STAIRS_H[c]) if c in STAIRS_H else bridge_px(y, x))
star_inlay(C, 2 * 16 + 8); star_inlay(C, 18 * 16 + 8); star_inlay(2 * 16 + 8, C); star_inlay(18 * 16 + 8, C)

# =========================================================================== fendas: placa em relevo
def pad(cx, cy, hw, hh):
    def inside(x, y):
        ax, ay = abs(x + .5 - cx), abs(y + .5 - cy)
        return ax <= hw and ay <= hh and ax + ay <= hw + hh - 8
    for y in range(cy - hh - 1, cy + hh + 1):
        for x in range(cx - hw - 1, cx + hw + 1):
            if not inside(x, y): continue
            d = math.hypot(x + .5 - cx, y + .5 - cy)
            if not all(inside(x + a, y + b) for a, b in ((1, 0), (-1, 0), (0, 1), (0, -1))): k = 'out'
            elif not inside(x, y - 2) or not inside(x - 2, y): k = 's1'
            elif not inside(x, y + 3) or not inside(x + 3, y): k = 's4' if (not inside(x, y + 2) or not inside(x + 2, y)) else 's3'
            elif d < 12.5: k = 'p5'
            elif d < 13.5: k = 's4'                                  # sulco em volta do vortice
            elif d < 14.5: k = 's1' if (x >= cx or y >= cy) else 's3'
            else:
                n = h(int(x - cx + 40) * 7 + int(y - cy + 40) * 13)
                k = 's3' if n % 9 == 0 else 's1' if n % 11 == 0 else 's2'
            put(x, y, k)
    runes = [(cx - 18, cy), (cx + 17, cy)] if hw > hh else [(cx, cy - 18), (cx, cy + 17)]
    for (rx, ry) in runes:
        for (dx, dy, k) in ((0, 0, 'c1'), (-1, 0, 'n3'), (1, 0, 'n3'), (0, -1, 'n3'), (0, 1, 'n3'),
                            (-1, -1, 's4'), (1, 1, 's1')):
            if inside(rx + dx, ry + dy): put(rx + dx, ry + dy, k)
PADS_C = [(C, 16, 23, 15), (C, S - 16, 23, 15), (16, C, 15, 23), (S - 16, C, 15, 23)]
for pc in PADS_C:
    pad(*pc)

# =========================================================================== faces de baixo (espessura)
FACEPX = set()
def face_under(x, y0):
    seq = ['s2', 's2', 's3', 's3', 's3', 's3', 's4', 's4', 's4']
    if x % 16 in (5, 11): seq = ['s2', 's3', 's4', 's4', 's4', 's3', 's4', 's4', 's4']
    if x % 32 == 11: seq[4:6] = ['c1', 'c2']
    seq += ['s4'] * [0, 2, 1, 3, 0, 1, 4, 2, 0, 1, 2, 5, 1, 0, 2, 1][x % 16] + ['out']
    y = y0
    for kk in seq:
        if get(x, y) != 'void': break
        put(x, y, kk); FACEPX.add((x, y)); y += 1
for x in range(S):
    for y in range(S - 1, 0, -1):
        if get(x, y) == 'out' and get(x, y + 1) == 'void' and get(x, y - 1) not in ('void', 'out', None) \
                and (x, y) not in FACEPX:
            face_under(x, y + 1)
for (x, y) in list(FACEPX):
    if get(x - 1, y) == 'void' or get(x + 1, y) == 'void':
        put(x, y, 'out')

# =========================================================================== espelho
cv.mirror_x()
ov.mirror_x()

# vortice em espiral (assimetrico: desenhado depois do espelho, igual nas quatro fendas)
def vortex(cx, cy):
    for y in range(cy - 13, cy + 13):
        for x in range(cx - 13, cx + 13):
            dx, dy = x + .5 - cx, y + .5 - cy
            d = math.hypot(dx, dy)
            if d >= 12.5: continue
            if d >= 11.5: k = 'out'
            elif d >= 10.5: k = 'c1'
            else:
                arm = math.cos(3 * math.atan2(dy, dx) + d * .8)
                v = 1 - d / 10.5 + .24 * arm + ((x + y) % 2) * .07
                k = 'p5'
                for lim, kk in ((.9, 'p0'), (.74, 'p1'), (.56, 'p2'), (.38, 'p3'), (.2, 'p4')):
                    if v >= lim: k = kk; break
            put(x, y, k)
for (vx, vy, _, _) in PADS_C:
    vortex(vx, vy)

# =========================================================================== vazio: estrelas, galaxias, ilhas
STARS = [
    [],
    [(4, 11, '*1'), (12, 3, '*2')],
    [(7, 7, '*0'), (6, 7, '*1'), (8, 7, '*1'), (7, 6, '*1'), (7, 8, '*1'), (5, 7, '*2'), (9, 7, '*2'),
     (7, 5, '*2'), (7, 9, '*2')],
    [(9, 8, '*0'), (8, 8, '*3'), (10, 8, '*3'), (9, 7, '*3'), (9, 9, '*3'), (7, 8, 'n3'), (11, 8, 'n3'),
     (9, 6, 'n3'), (9, 10, 'n3'), (9, 5, 'n2'), (9, 11, 'n2')],
    [(3, 4, '*1'), (13, 12, '*0')],
    [(11, 5, '*0'), (10, 5, '*2'), (12, 5, '*2'), (11, 4, '*2'), (11, 6, '*2')],
    [(9, 7, '*0')],
]
def galaxy(cx, cy, R):
    for y in range(cy - R, cy + R):
        for x in range(cx - R, cx + R):
            dx, dy = x + .5 - cx, y + .5 - cy
            d = math.hypot(dx, dy)
            if d >= R or get(x, y) != 'void': continue
            arm = math.cos(2 * (math.atan2(dy, dx) - 2.3 * math.log(d + 1)))
            v = (arm * .5 + .5) * (1 - d / R) * 1.5 + max(0, 1 - d / 7) * 1.4 + ((x + y) % 2) * .18
            k = 'void'
            for lim, kk in ((1.55, '*0'), (1.25, 'n4'), (0.98, 'n3'), (0.74, 'n2'), (0.52, 'n1'), (0.34, 'n0')):
                if v >= lim: k = kk; break
            put(x, y, k)

def black_hole(cx, cy):
    for y in range(cy - 16, cy + 16):
        for x in range(cx - 16, cx + 16):
            d = math.hypot(x + .5 - cx, y + .5 - cy)
            chk = (x + y) % 2
            if d < 7.5: k = 'core'
            elif d < 8.5: k = 'n4'
            elif d < 9.5: k = '*1'
            elif d < 10.5: k = 'n3'
            elif d < 12.5: k = 'n2' if chk else 'n3'
            elif d < 14: k = 'n1' if chk else 'n2'
            elif d < 16: k = 'n0' if chk else 'void'
            else: continue
            put(x, y, k)

def crystal(bx, by, hgt, wid, tilt=0.0):
    """prisma de cristal da base (bx,by) ate a ponta, inclinado por `tilt` (px de x por px de y).
    Faceta clara a esquerda, meio, faceta escura a direita, ponta facetada, contorno violeta."""
    half = wid / 2.0
    tipl = min(wid * 1.3, hgt * .4)
    body_end = 1 - tipl / hgt
    pts = {}
    for y in range(by - hgt - 1, by + 1):
        t = (by + .5 - (y + .5)) / hgt
        if t < 0 or t > 1: continue
        ax_ = bx + tilt * hgt * t
        w_here = half if t <= body_end else half * (1 - t) / (1 - body_end)
        for x in range(int(ax_ - half) - 2, int(ax_ + half) + 3):
            u = x + .5 - ax_
            if abs(u) <= w_here + .01:
                pts[(x, y)] = (u / max(w_here, .6), t)
    for (x, y), (f, t) in pts.items():
        edge = any((x + a, y + b) not in pts for a, b in ((1, 0), (-1, 0), (0, -1)))
        if edge: k = 'c3' if f > -.2 else 'c2'
        elif t > body_end: k = 'c0' if f < 0 else 'c2'
        elif f < -.4: k = 'c0' if t > .55 else 'c1'
        elif f < .2: k = 'c1'
        else: k = 'c2'
        if not edge and y == by: k = 'c3'
        put(x, y, k)
    hx = int(bx + tilt * hgt * .55 - half * .35)
    for yy in range(int(by - hgt * .6), int(by - hgt * .35)):
        if (hx, yy) in pts: put(hx, yy, '*0')
    return int(bx + tilt * hgt), by - hgt

def sparkle(x, y):
    for (dx, dy, k) in ((0, 0, '*0'), (-1, 0, '*1'), (1, 0, '*1'), (0, -1, '*1'), (0, 1, '*1'), (0, -2, '*2'), (0, 2, '*2')):
        if get(x + dx, y + dy) == 'void': put(x + dx, y + dy, k)

def island(cx, ty, rx, ry, depth, crystals=(), shards=()):
    """ilha flutuante em 3/4: tampo oval irregular, face em cone com estratos, estalactites,
    cristais facetados com luz refletida no tampo."""
    cyt = ty + ry
    rr = lambda th: 1 + .07 * math.sin(3 * th + cx) + .05 * math.sin(5 * th + ty)
    top = set()
    for y in range(ty - 3, ty + 2 * ry + 4):
        for x in range(cx - rx - 4, cx + rx + 4):
            dx, dy = (x + .5 - cx) / rx, (y + .5 - cyt) / ry
            if dx * dx + dy * dy <= rr(math.atan2(dy, dx)) ** 2:
                top.add((x, y))
    cones, px_ = [], cx - rx + 4
    while px_ < cx + rx - 3:
        cones.append((px_, 2 + h(px_ * 7 + ty) % 5))
        px_ += 3 + h(px_ + ty * 3) % 3
    face = set()
    for x in sorted({x for x, _ in top}):
        ybot = max(y for (xx, y) in top if xx == x)
        u = (x + .5 - cx) / rx
        L = int(depth * max(0, 1 - abs(u) ** 1.6) + max([hh - abs(x - c) * 1.7 for c, hh in cones] + [0]) * (1 - abs(u)))
        wob = int(1.6 * math.sin(x * .45 + cx))
        for i in range(1, L + 1):
            y = ybot + i
            frac = i / max(L, 1)
            if u < -.5: k = 's2' if frac < .55 else 's3'
            elif u < .15: k = 's3' if frac < .6 else 's4'
            else: k = 's3' if (u < .5 and frac < .35) else 's4'
            if i == 1: k = 's4'
            elif (i + wob) % 6 == 0 and frac < .85: k = 's4'
            elif (i + wob) % 6 == 1 and frac < .7 and u < .3: k = 's2' if u < -.2 else 's3'
            if i >= L - 1 and L > 4: k = 's4'
            put(x, y, k); face.add((x, y))
    for (x, y) in top:
        nb = lambda a, b: (x + a, y + b) in top
        u = (x + .5 - cx) / rx
        if not (nb(0, -1) and nb(-1, 0) and nb(1, 0)): k = 'out'
        elif not nb(0, 1): k = 's1'                              # beirada da frente
        elif not nb(0, -2) or not nb(-2, 0): k = 's0'
        elif not nb(0, 2): k = 's2'
        else:
            n = h((x - cx + 50) * 11 + (y - ty) * 29 + rx)
            k = 's3' if n % 10 == 0 else 's0' if n % 14 == 1 else 's1' if u < .45 else 's2'
            if u > .7: k = 's2' if k != 's3' else 's3'
        put(x, y, k)
    for (dx_, dy_, hh, ww, tl) in crystals:                       # luz dos cristais no tampo
        bx, by = cx + dx_, cyt + dy_
        for (x, y) in top:
            d = math.hypot(x + .5 - bx, (y + .5 - by) * 1.8)
            if d < 7 and get(x, y) in ('s1', 's2', 's3'):
                put(x, y, 'c2' if d < 4.5 and (x + y) % 2 == 0 else 's0' if d < 5.5 else 's1')
    pts = [(x, y) for y in range(ty - 4, ty + 2 * ry + depth + 12) for x in range(cx - rx - 4, cx + rx + 5)
           if get(x, y) == 'void' and any((x + a, y + b) in face or (x + a, y + b) in top
                                          for a, b in ((1, 0), (-1, 0), (0, 1), (0, -1)))]
    for p in pts: put(*p, 'out')
    for (sx, sy, sh) in shards:                                   # lascas de cristal na face
        crystal(cx + sx, cyt + ry + sy, sh, 3, .5 if sx > 0 else -.5)
    for (dx_, dy_, hh, ww, tl) in sorted(crystals, key=lambda c: c[1]):
        tx, tyy = crystal(cx + dx_, cyt + dy_, hh, ww, tl)
        if hh >= 16: sparkle(tx, tyy - 3)

def place(fn, *a, **k):
    """desenha e confere que so pintou por cima de vazio."""
    before = [row[:] for row in cv.px]
    fn(*a, **k)
    hit = [(x, y) for y in range(S) for x in range(S) if cv.px[y][x] != before[y][x] and before[y][x] != 'void']
    assert not hit, ('sem espaco', fn.__name__, a, hit[:3])

def stamp(box, dx0, dy0, mirror=False):
    """copia a arte (nao-vazio) de box=(x0,y0,x1,y1) para (dx0,dy0), espelhada ou nao.
    Com tudo alinhado a 8 px a copia reusa os mesmos tiles (flip gratis)."""
    x0, y0, x1, y1 = box
    assert x0 % 8 == y0 % 8 == dx0 % 8 == dy0 % 8 == 0 and (x1 - x0) % 8 == 0
    src = {(x, y): get(x, y) for y in range(y0, y1) for x in range(x0, x1) if get(x, y) != 'void'}
    def go():
        for (x, y), k in src.items():
            put(dx0 + ((x1 - 1 - x) if mirror else (x - x0)), dy0 + (y - y0), k)
    place(go)

place(galaxy, 48, 48, 30)
place(galaxy, 288, 288, 30)
place(black_hole, 240, 40)
place(island, 298, 92, 24, 8, 24,
      crystals=((-15, 4, 9, 4, -.45), (-8, 2, 21, 7, -.22), (1, 0, 32, 9, .03), (10, 3, 18, 6, .3), (17, 5, 8, 4, .5)),
      shards=((-12, 4, 5), (9, 8, 4)))
stamp((264, 56, 328, 144), 8, 208, mirror=True)                  # ilha grande: a segunda e espelho
place(island, 32, 108, 13, 5, 13, crystals=((-3, 1, 14, 5, -.12), (5, 2, 8, 3, .35)))
stamp((16, 88, 48, 136), 224, 280, mirror=True)                  # rocha com cristal
place(island, 112, 26, 13, 5, 12)
stamp((96, 16, 128, 56), 48, 288)                                # rochas soltas
stamp((96, 16, 128, 56), 296, 200, mirror=True)

for r in range(N):
    for c in range(N):
        if all(get(c * 16 + x, r * 16 + y) == 'void' for y in range(16) for x in range(16)):
            v = [0, 0, 0, 1, 1, 4, 4, 6, 6, 2, 5, 1, 4, 6, 3, 0][h(c * 57 + r * 131) % 16]
            for (x, y, k) in STARS[v]:
                put(c * 16 + x, r * 16 + y, k)

bcv = Canvas(32, 32)
bcv.rect(0, 0, 31, 31, 'void')
for (c, r, v) in ((0, 0, 1), (1, 0, 0), (0, 1, 6), (1, 1, 4)):
    for (x, y, k) in STARS[v]:
        bcv.put(c * 16 + x, r * 16 + y, k)

# =========================================================================== corte e arquivos
tiles, bad = cut_tiles(cv, PAL)
otiles, bad3 = cut_tiles(ov, PAL)
btiles, bad2 = cut_tiles(bcv, PAL)
if bad or bad2 or bad3:
    for b in (bad + bad2 + bad3)[:30]:
        print('CONFLITO', b)
    sys.exit(1)
bank = TileBank()
metas = []
def quads(tmap, c, r):
    q = []
    for i in range(4):
        key = (c * 2 + i % 2, r * 2 + i // 2)
        if key in tmap:
            slot, t = tmap[key]
            ti, hf, vf = bank.add(t)
            q.append(entry(NUM_TILES_IN_PRIMARY + ti, hf, vf, slot))
        else:
            q.append(0)
    return q
def build(tmap, omap, cols, rows):
    """camada do meio = cena opaca; camada de cima = ov (cristais que cobrem sprites)."""
    g = {}
    for r in range(rows):
        for c in range(cols):
            m = tuple([0] * 4 + quads(tmap, c, r) + quads(omap, c, r))
            if m not in metas: metas.append(m)
            g[(c, r)] = metas.index(m)
    return g
grid = build(tiles, otiles, N, N)
bgrid = build(btiles, {}, 2, 2)
TOPCELLS = sorted({(tx // 2, ty // 2) for (tx, ty) in otiles})

WALK = [[1 if ((c, r) in SOLID and (c, r) not in LAMPS) else 0 for c in range(N)] for r in range(N)]
blocks = [pack_block(1024 + grid[(c, r)], 0 if WALK[r][c] else 1, 3) for r in range(N) for c in range(N)]
border = [pack_block(1024 + bgrid[(c, r)], 1, 3) for r in range(2) for c in range(2)]

write_tileset(os.path.join(OUT, 'ultra_space_arena'), bank, metas, PAL, preview_slot=7)
write_blocks(os.path.join(OUT, 'map.bin'), [blocks[r * N:(r + 1) * N] for r in range(N)])
write_blocks(os.path.join(OUT, 'border.bin'), [border[:2], border[2:]])
write_png(os.path.join(OUT, 'tiles_colored.png'), colored_tile_sheet(bank, [tiles, btiles, otiles], PAL), 3)

per_pal = {}
for (s, t) in list(tiles.values()) + list(btiles.values()) + list(otiles.values()):
    per_pal.setdefault(s, set()).add(bank.add(t)[0])
stats = dict(n=N, tiles=len(bank.tiles), metatiles=len(metas), walk=sum(map(sum, WALK)),
             per_pal={k: len(v) for k, v in sorted(per_pal.items())}, top=TOPCELLS)
json.dump(stats, open(os.path.join(OUT, 'stats.json'), 'w'))
print(stats)
