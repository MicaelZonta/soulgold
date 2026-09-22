#!/usr/bin/env python3
"""Exemplo completo: o secundario do Altar do Sol e da Lua (gTileset_AltarSunMoon).

    python3 .claude/skills/montar-tileset/exemplo_altar_sol_lua.py SAIDA/ [--sem-borda]

Escreve SAIDA/altar_sun_moon/{tiles.png, palettes/, metatiles.bin, metatile_attributes.bin},
SAIDA/altar_grid.json (metatile e colisao por celula, para compor o mapa) e
SAIDA/tiles_colored.png. E o gerador do tileset que esta no repositorio.

Mostra as quatro tecnicas da skill:
  1. encosta montada com metatiles do PRIMARIO recoloridos (primary_ref, custo 0 tile)
  2. templo desenhado com chaves de material, cortado em tiles de UMA paleta cada
  3. sol e lua nos MESMOS pixels, trocados pelo swapPalettes (paletas 9 e 10)
  4. um segundo estado (portal) no mesmo tileset, para setmetatile
--sem-borda gera a versao antiga, sem a borda de tras da montanha (15x12).
"""
import json, math, os, struct, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from tileset_kit import *

OUT = sys.argv[1] if len(sys.argv) > 1 and not sys.argv[1].startswith('--') else 'altar_out'
RIM = '--sem-borda' not in sys.argv
P = load_tileset('primary', 'johto_general')

# ------------------------------------------------------------------ cores e paletas
OUTL = (64, 44, 52)
S = [(252, 246, 226), (234, 220, 186), (208, 188, 150), (170, 146, 114), (122, 100, 86)]
FACE = S[1]                                      # cor lisa da face do disco (onde o glifo "some")
W = [(208, 250, 244), (112, 214, 228), (56, 164, 212), (40, 104, 168)]
G = [(168, 224, 112), (112, 188, 88), (64, 136, 72), (40, 88, 64)]
SUN = [(255, 246, 176), (248, 200, 64), (192, 116, 32)]
MOON = [(242, 228, 255), (190, 160, 248), (128, 96, 208)]
GLOW_DAY, GLOW_NIGHT = (176, 250, 255), (226, 184, 255)
FLOWER_DAY = [(255, 255, 255), (255, 222, 96), (240, 144, 72)]
FLOWER_NIGHT = [(236, 212, 255), (188, 140, 244), (124, 92, 204)]
PORTAL = [(255, 255, 255), (176, 248, 255), (96, 200, 248), (160, 120, 248), (208, 72, 200), (88, 40, 136)]
# rocha: a paleta 1 do johto_general INTEIRA, indice por indice, com os marrons puxados para
# terracota e os cinzas/contornos aquecidos. O slot 8 so serve a rocha do primario (nenhum tile
# desenhado aqui usa o slot 8), entao qualquer peca de montanha do primario fica recoloravel.
ROCK = {1: (238, 226, 214), 2: (214, 198, 184), 3: (188, 168, 156), 4: (118, 98, 108), 5: (48, 32, 36),
        6: (244, 234, 222), 7: (90, 189, 139), 8: (96, 72, 82), 9: (246, 208, 176), 10: (232, 180, 138),
        11: (206, 132, 100), 12: (168, 90, 72), 13: (128, 62, 56), 14: (86, 42, 48), 15: (98, 189, 129)}

COLORS = {
    'out': (OUTL, None),
    **{'s%d' % i: (S[i], None) for i in range(5)},
    **{'w%d' % i: (W[i], None) for i in range(4)},
    **{'g%d' % i: (G[i], None) for i in range(4)},
    **{'r%d' % i: (c, None) for i, c in ROCK.items()},
    'glow': (GLOW_DAY, GLOW_NIGHT),
    **{'sun%d' % i: (SUN[i], FACE) for i in range(3)},     # sol: dourado de dia, some a noite
    **{'moon%d' % i: (FACE, MOON[i]) for i in range(3)},   # lua: some de dia, lilas a noite
    'both': (SUN[1], MOON[1]),                              # pixel comum aos dois glifos
    **{'fl%d' % i: (FLOWER_DAY[i], FLOWER_NIGHT[i]) for i in range(3)},
    **{'p%d' % i: (PORTAL[i], None) for i in range(6)},
}
PAL = PaletteSet({
    7:  ['out', 's0', 's1', 's2', 's3', 's4', 'w0', 'w1', 'w2', 'w3', 'glow', 'g0', 'g1', 'g2'],
    8:  ['r%d' % i for i in range(1, 16)],          # = paleta 1 do primario, recolorida
    9:  ['out', 's0', 's1', 's2', 's3', 's4', 'sun0', 'sun1', 'sun2', 'moon0', 'moon1', 'moon2', 'both', 'glow', 'w1'],
    10: ['out', 'g0', 'g1', 'g2', 'g3', 'fl0', 'fl1', 'fl2', 's0', 's1', 's2', 's3', 's4', 'w1', 'w2'],
    11: ['out', 's0', 's1', 's2', 's3', 's4', 'p0', 'p1', 'p2', 'p3', 'p4', 'p5'],
}, COLORS, order=[7, 9, 10, 8, 11], swap=[7, 9, 10])
ROCK_SLOT = 8

# ------------------------------------------------------------------ canvas
MW = 15
OY = 16 if RIM else 0                  # a borda de tras ocupa a primeira linha de celulas
MH = 12 + OY // 16
CW, CH = MW * 16, MH * 16
CX = CW // 2                           # eixo do espelho numa borda de tile
cv = Canvas(CW, CH)
h = noise
def put(x, y, k): cv.put(x, y + OY, k)
def get(x, y): return cv.get(x, y + OY)
def hline(x0, x1, y, k):
    for x in range(x0, x1 + 1): put(x, y, k)
def vline(x, y0, y1, k):
    for y in range(y0, y1 + 1): put(x, y, k)

# ------------------------------------------------------------------ montanha: metatiles do primario
# degraus internos: 113 topo, 124 face, 115/117 bordas, 123/125 pontas da face.
# fechamento externo sobre grama: 104 105 106 (borda de tras), 112/114 (laterais), 120/122 (base).
LEVELS = [(4, 10, 1), (2, 12, 3), (1, 13, 4), (0, 14, 8), (0, 14, 11)]
def rock_piece(c, r):
    if RIM:
        if r == 0:
            return 104 if c == 0 else 106 if c == MW - 1 else 105
        r -= 1
    for (x0, x1, f) in LEVELS:
        if x0 <= c <= x1 and r <= f:
            if RIM and c in (0, MW - 1):            # lado de fora da montanha
                if r == 11:
                    return 120 if c == 0 else 122
                return 112 if c == 0 else 114
            if r == f:
                return 123 if c == x0 else 125 if c == x1 else 124
            return 115 if c == x0 else 117 if c == x1 else 113
    return None
ROCKGRID = [[rock_piece(c, r) for c in range(MW)] for r in range(MH)]

# ------------------------------------------------------------------ primitivas de pedra (luz de cima a esquerda)
def slab(x0, y0, x1, y1, seed=0):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            lx, ly = (x - x0) % 16, (y - y0) % 16
            cell = ((x - x0) // 16 + (y - y0) // 16 + seed) % 2
            if lx == 15 or ly == 15: k = 's3'
            elif lx == 0 or ly == 0: k = 's0'
            elif lx == 14 or ly == 14: k = 's2'
            else:
                r = h(x * 7 + y * 13 + seed) % 23
                k = 's2' if r == 0 else 's0' if r == 1 else 's1'
                if cell and r in (2, 3) and (x + y) % 2:
                    k = 's2'
            put(x, y, k)

def blocks(x0, y0, x1, y1, lip=True):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            yy = y - y0 - (4 if lip else 0)
            if lip and y - y0 < 4:
                k = ['out', 's0', 's1', 's3'][y - y0]
            else:
                row, ly = yy // 6, yy % 6
                lx = (x - x0 + (8 if row % 2 else 0)) % 16
                if ly == 5 or lx == 15: k = 's4'
                elif ly == 0 or lx == 0: k = 's1'
                elif ly == 4: k = 's3'
                else: k = 's2' if h(x * 5 + y * 3) % 9 else 's3'
            put(x, y, k)

def stairs(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        ly = (y - y0) % 4
        for x in range(x0 + 3, x1 - 2):
            put(x, y, ['s0', 's1', 's2', 's4'][ly])
        for x in (x0, x1):
            put(x, y, 'out')
        put(x0 + 1, y, 's1'); put(x0 + 2, y, 's2')
        put(x1 - 1, y, 's3'); put(x1 - 2, y, 's2')
        put(x0 + 3, y, 's3' if ly != 0 else 's2')

def cast_shadow(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            k = get(x, y)
            if k in ('s0', 's1', 's2') and (x + y) % 2 == 0:
                put(x, y, {'s0': 's1', 's1': 's2', 's2': 's3'}[k])
            elif k in ('s0', 's1'):
                put(x, y, {'s0': 's1', 's1': 's2'}[k])

def water_trough(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if x in (x0, x1): k = 'out'
            elif x == x0 + 1: k = 's3'
            elif x == x1 - 1: k = 's0'
            else:
                t = (y * 2 + x) % 11
                k = 'w0' if t == 0 else 'w1' if t < 4 else 'w2' if x < x1 - 2 else 'w3'
            put(x, y, k)

def bed(x0, y0, x1, y1, seed):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            r = h(x * 17 + y * 5 + seed) % 16
            put(x, y, 'g1' if r < 6 else 'g2' if r < 11 else 'g0' if r < 13 else 'g3')
    for x in range(x0, x1 + 1):
        put(x, y0, 'out'); put(x, y0 + 1, 's0'); put(x, y1, 'out'); put(x, y1 - 1, 's3')
    for y in range(y0, y1 + 1):
        put(x0, y, 'out'); put(x0 + 1, y, 's0'); put(x1, y, 'out'); put(x1 - 1, y, 's3')
    n = 0
    for fy in range(y0 + 4, y1 - 3, 5):
        for fx in range(x0 + 4 + (fy // 5) % 2 * 2, x1 - 3, 5):
            n += 1
            c = 'fl0' if n % 3 else 'fl1'
            put(fx, fy, 'fl1' if c == 'fl0' else 'fl2')
            put(fx - 1, fy, c); put(fx + 1, fy, c); put(fx, fy - 1, c); put(fx, fy + 1, 'g3')

def glyph(cx, cy, r, stars=True):
    """Sol e lua carimbados nos mesmos pixels com tintas separadas (ver COLORS)."""
    sunpx, moonpx = {}, {}
    core = r * 0.45
    for y in range(int(cy - r) - 1, int(cy + r) + 2):
        for x in range(int(cx - r) - 1, int(cx + r) + 2):
            dx, dy = x + 0.5 - cx, y + 0.5 - cy
            d = math.hypot(dx, dy); ang = math.atan2(dy, dx)
            k = None
            if d <= core:
                k = 'sun0' if dx + dy < -core * 0.6 else 'sun1'
            elif d <= core + 1:
                k = 'sun2'
            else:
                seg = (ang + math.pi) / (2 * math.pi) * 8
                frac = abs(seg - round(seg))
                lim = r if int(round(seg)) % 2 == 0 else r * 0.72
                width = (1 - (d - core) / (lim - core)) * 0.42
                if d <= lim and frac < width:
                    k = 'sun1' if frac < width * 0.5 else 'sun2'
            if k:
                sunpx[(x, y)] = k
            rm = r * 0.8
            if d <= rm:
                d2 = math.hypot(dx - r * 0.42, dy + r * 0.28)
                if d2 > rm * 0.86:
                    if d > rm - 1 or d2 < rm * 0.86 + 1: mk = 'moon2'
                    elif dx < -rm * 0.4: mk = 'moon0'
                    else: mk = 'moon1'
                    moonpx[(x, y)] = mk
    if stars:
        for (sx, sy) in ((0.55, -0.55), (0.75, 0.1), (0.3, 0.7)):
            moonpx[(int(cx + sx * r), int(cy + sy * r))] = 'moon0'
    for p in set(sunpx) | set(moonpx):
        put(p[0], p[1], 'both' if (p in sunpx and p in moonpx) else (sunpx.get(p) or moonpx.get(p)))

# ------------------------------------------------------------------ colunata (linha 4)
for y in range(64, 80):
    for x in range(32, 96):
        put(x, y, 's4' if (x + y) % 2 else 's3')
hline(32, 95, 64, 'out'); hline(32, 95, 65, 's1'); hline(32, 95, 66, 's3')
for cx in (36, 52, 68, 84):
    for y in range(67, 80):
        put(cx - 3, y, 'out'); put(cx + 4, y, 'out')
        put(cx - 2, y, 's0'); put(cx - 1, y, 's1'); put(cx, y, 's1'); put(cx + 1, y, 's1')
        put(cx + 2, y, 's2'); put(cx + 3, y, 's3')
    hline(cx - 4, cx + 5, 67, 'out'); hline(cx - 4, cx + 5, 68, 's0'); hline(cx - 4, cx + 5, 69, 's2')
    hline(cx - 4, cx + 5, 77, 's0'); hline(cx - 4, cx + 5, 78, 's2'); hline(cx - 4, cx + 5, 79, 'out')
    for y in (68, 69, 77, 78):
        put(cx - 4, y, 'out'); put(cx + 5, y, 'out')
for x in range(32, 96):
    if get(x, 72) in ('s3', 's4'):
        put(x, 71, 'out'); put(x, 72, 's0'); put(x, 73, 's1'); put(x, 74, 's3'); put(x, 75, 'out')
        if x % 4 == 0:
            for y in range(76, 79):
                put(x, y, 's1')
vline(32, 64, 79, 'out')

# ------------------------------------------------------------------ palco (linhas 5..7)
slab(48, 80, CX - 1, 127, seed=1)
cast_shadow(48, 80, CX - 1, 83)
for y in range(80, 128):
    put(32, y, 'out'); put(33, y, 's0'); put(34, y, 's1'); put(35, y, 's2')
    put(44, y, 's0'); put(45, y, 's1'); put(46, y, 's2'); put(47, y, 's3')
water_trough(36, 80, 43, 127)
MED = (64, 96)
for y in range(80, 112):
    for x in range(48, 80):
        d = math.hypot(x + 0.5 - MED[0], y + 0.5 - MED[1])
        a = math.atan2(y + 0.5 - MED[1], x + 0.5 - MED[0])
        if d <= 14.5:
            if d > 13.5: k = 'out'
            elif d > 11.5: k = 's0' if math.sin(a + math.pi / 4) < -0.3 else 's3' if math.sin(a + math.pi / 4) > 0.3 else 's1'
            elif d > 10.5: k = 'out'
            elif d > 9.5: k = 's3' if math.sin(a + math.pi / 4) < 0 else 's0'
            else: k = 's1'
            put(x, y, k)

# ------------------------------------------------------------------ muro do palco (linha 8), terraco (9..10), muro da frente (11)
blocks(32, 128, CX - 1, 143)
for y in range(128, 144):
    for x in range(37, 43):
        put(x, y, ['w1', 'w0', 'w1', 'w2', 'w2', 'w3'][x - 37] if (y * 3 + x) % 7 else 'w0')
    put(36, y, 'out'); put(43, y, 'out')
slab(16, 144, CX - 1, 175, seed=0)
cast_shadow(16, 144, CX - 1, 147)
vline(16, 144, 175, 'out'); vline(17, 144, 175, 's3')
for y in range(144, 160):
    for x in range(32, 48):
        if x in (32, 47) or y == 159: k = 'out'
        elif x == 33 or y == 158: k = 's0' if y != 158 else 's1'
        elif x == 46: k = 's2'
        else:
            k = 'w2' if (x + y * 2) % 9 else 'w0'
            if y < 147: k = 'w3'
        put(x, y, k)
for (x, y) in ((37, 147), (40, 146), (42, 148), (38, 149)):
    put(x, y, 'w0')
bed(16, 144, 31, 175, 21)
blocks(16, 176, CX - 1, 191)
vline(16, 176, 191, 'out')

def orb_pillar(cx):
    for y in range(152, 160):
        for x in range(cx + 2, cx + 9 - (159 - y) // 3):
            if get(x, y) in ('s0', 's1', 's2'):
                put(x, y, 's3' if (x + y) % 2 else 's2')
    for y in range(134, 156):
        put(cx - 4, y, 'out'); put(cx + 3, y, 'out')
        put(cx - 3, y, 's0'); put(cx - 2, y, 's1'); put(cx - 1, y, 's1'); put(cx, y, 's2'); put(cx + 1, y, 's2'); put(cx + 2, y, 's3')
    for x in range(cx - 6, cx + 6):
        put(x, 153, 'out'); put(x, 154, 's0'); put(x, 155, 's2'); put(x, 156, 's3'); put(x, 157, 'out')
    for y in (154, 155, 156):
        put(cx - 6, y, 'out'); put(cx + 5, y, 'out')
    for x in range(cx - 6, cx + 6):
        put(x, 133, 'out'); put(x, 134, 's0'); put(x, 135, 's2'); put(x, 136, 'out')
    put(cx - 6, 134, 'out'); put(cx + 5, 134, 'out'); put(cx - 6, 135, 'out'); put(cx + 5, 135, 'out')
orb_pillar(72)

cv.mirror_x()

# ------------------------------------------------------------------ estela com o disco (colunas 6..8, linhas 0..4)
SX0, SX1, ARCH_R = 96, 143, 12
def in_stele(x, y):
    if not (SX0 <= x <= SX1 and 2 <= y <= 79):
        return False
    for (cx, cy) in ((SX0 + ARCH_R, 2 + ARCH_R), (SX1 - ARCH_R, 2 + ARCH_R)):
        if y < cy and ((x < SX0 + ARCH_R and cx == SX0 + ARCH_R) or (x > SX1 - ARCH_R and cx == SX1 - ARCH_R)):
            if math.hypot(x + 0.5 - cx - 0.5, y + 0.5 - cy - 0.5) > ARCH_R:
                return False
    return True
def inset(x, y, d):
    return in_stele(x - d, y) and in_stele(x + d, y) and in_stele(x, y - d) and y <= 75 - d
for y in range(0, 80):
    for x in range(96, 144):
        if not in_stele(x, y):
            continue
        edge = not (in_stele(x - 1, y) and in_stele(x + 1, y) and in_stele(x, y - 1) and (y == 79 or in_stele(x, y + 1)))
        if edge: k = 'out'
        elif not in_stele(x - 2, y) or not in_stele(x, y - 2): k = 's0'
        elif not in_stele(x + 2, y): k = 's3'
        elif inset(x, y, 4) and not inset(x, y, 5):
            k = 's4' if (not inset(x - 1, y, 4) or not inset(x, y - 1, 4)) else 's0'
        elif inset(x, y, 5) and not inset(x, y, 6):
            k = 's0' if (not inset(x - 1, y, 5) or not inset(x, y - 1, 5)) else 's3'
        else:
            f = (x - 96) % 6
            k = 's3' if f == 0 else 's1' if f == 1 else ('s2' if h(x * 3 + y * 11) % 13 else 's3')
        put(x, y, k)
for x in range(94, 146):
    put(x, 76, 'out'); put(x, 77, 's0'); put(x, 78, 's2'); put(x, 79, 'out')
put(94, 77, 'out'); put(94, 78, 'out'); put(145, 77, 'out'); put(145, 78, 'out')

DCX, DCY = 120, 34
for y in range(8, 62):
    for x in range(96, 144):
        d = math.hypot(x + 0.5 - DCX, y + 0.5 - DCY)
        a = math.sin(math.atan2(y + 0.5 - DCY, x + 0.5 - DCX) + math.pi / 4)
        if d <= 22.5:
            if d > 21.5: k = 'out'
            elif d > 18.5: k = 's0' if a < -0.35 else 's3' if a > 0.35 else 's1'
            elif d > 17.5: k = 'out'
            elif d > 16.5: k = 's3' if a < 0 else 's1'
            else: k = 's1'
            put(x, y, k)
for y in range(12, 64):
    for x in range(98, 142):
        d = math.hypot(x + 0.5 - 122, y + 0.5 - 36)
        dd = math.hypot(x + 0.5 - DCX, y + 0.5 - DCY)
        if dd > 22.5 and d <= 23.5 and get(x, y) in ('s1', 's2', 's3', 's0'):
            put(x, y, 's4' if (x + y) % 2 else 's3')
for y in list(range(58, 80)) + list(range(80, 128)):
    for x in range(116, 124):
        if y < 80: k = ['out', 's3', 'w1', 'glow', 'glow', 'w1', 's0', 'out'][x - 116]
        else: k = ['s3', 'w1', 'glow', 'glow', 'glow', 'glow', 'w1', 's0'][x - 116]
        put(x, y, k)
stairs(96, 128, 143, 143)
stairs(80, 176, 159, 191)
glyph(DCX, DCY, 13.5)
glyph(MED[0], MED[1], 8.5, stars=False)
glyph(CW - MED[0], MED[1], 8.5, stars=False)
for ocx in (72, CW - 72):
    for y in range(118, 134):
        for x in range(ocx - 8, ocx + 8):
            d = math.hypot(x + 0.5 - ocx, y + 0.5 - 126)
            if d <= 6.6:
                put(x, y, 'out' if d > 5.6 else 's1')
    glyph(ocx, 126, 4.7, stars=False)
    put(ocx - 3, 122, 's0'); put(ocx - 2, 121, 's0')

# o topo arredondado da estela mostra rocha atras: essas celulas desenham na camada de cima
ROW0 = OY // 16
TOP = {(c, ROW0) for c in (6, 7, 8)}

def portal_canvas():
    pv = cv.copy()
    for y in range(8, 62):
        for x in range(96, 144):
            dx, dy = x + 0.5 - DCX, y + 0.5 - DCY
            d = math.hypot(dx, dy)
            if d <= 16.5:
                v = (math.atan2(dy, dx) / (2 * math.pi) * 3 + d / 5.0) % 1.0
                pv.put(x, y + OY, 'p0' if d < 3 else 'p1' if d < 5 else ['p2', 'p3', 'p4', 'p5', 'p3', 'p2'][int(v * 6)])
            elif get(x, y) in ('sun0', 'sun1', 'sun2', 'moon0', 'moon1', 'moon2', 'both'):
                pv.put(x, y + OY, 's1')
    return pv

# ------------------------------------------------------------------ colisao por celula (1 = anda)
WALK = [[0] * MW for _ in range(MH)]
def walk(r, c): WALK[r + ROW0][c] = 1
for r in (5, 6, 7):
    for c in range(3, 12): walk(r, c)
for c in (6, 7, 8): walk(8, c)
for r in (9, 10):
    for c in range(1, 14): walk(r, c)
for c in (2, 12, 4, 10): WALK[9 + ROW0][c] = 0          # espelhos d'agua e bases dos orbes
for c in range(5, 10): walk(11, c)

# ------------------------------------------------------------------ tiles -> metatiles -> arquivos
day_tiles, bad = cut_tiles(cv, PAL)
portal_tiles, bad2 = cut_tiles(portal_canvas(), PAL)
if bad or bad2:
    for b in (bad + bad2)[:20]:
        print('CONFLITO DE PALETA', b)
    sys.exit(1)
bank = TileBank()
base = lambda c, r: primary_ref(P, ROCKGRID[r][c], {1: ROCK_SLOT}) if ROCKGRID[r][c] is not None else None
ground = P['metas'][1][4:8]                       # grama do johto_general (camada do meio dele)
metas, grid = build_cells(day_tiles, bank, MW, MH, base=base, top=TOP, ground=ground)
n_t, n_m = len(bank.tiles), len(metas)
_, pgrid = build_cells(portal_tiles, bank, MW, MH, base=base, top=TOP, ground=ground, metas=metas)
print('tiles %d/384 (altar %d, portal +%d); metatiles %d (altar %d, portal +%d)'
      % (len(bank.tiles), n_t, len(bank.tiles) - n_t, len(metas), n_m, len(metas) - n_m))

# ------------------------------------------------------------------ familia de montanha terracota
# Todas as pecas de montanha do johto_general, clonadas com a paleta 8, NO FIM da lista (os indices
# que os mapas ja usam nao mudam). Custo: 0 tiles, 24 bytes cada. Achadas por inundacao a partir
# do 113 nos mapas de Johto (vizinhos com >= 30% de pixels de rocha), sem placa e sem estacas.
ROCK_FAMILY = [24, 25, 104, 105, 106, 107, 108, 109, 112, 113, 114, 115, 117, 120, 121, 122, 123, 124, 125,
    128, 129, 130, 131, 132, 133, 134, 135, 136, 138, 139, 140, 141, 142, 143, 144, 146, 150, 151, 152, 153,
    154, 158, 159, 160, 162, 163, 164, 166, 167, 168, 169, 170, 174, 175, 176, 177, 178, 179, 180, 181, 182,
    183, 184, 185, 186, 187, 192, 193, 200, 201, 234, 235, 240, 241, 242, 243, 271, 279, 287, 288, 289, 290,
    292, 351, 368, 369, 421, 423, 429, 431, 464, 466, 469, 474, 475, 476, 480, 481, 482, 483, 484, 487, 497,
    498, 499, 500, 507, 511, 522, 523, 525, 526, 527, 528, 532, 533, 535, 537, 538, 539, 541, 542, 543, 548,
    550, 553, 562, 563, 567, 569, 570, 571, 576, 588, 595, 596, 603, 608, 610, 613, 614, 615, 616, 617, 618,
    619, 620, 621, 633, 640, 641, 642, 643, 644, 645, 659, 660, 663, 682, 716, 717, 719, 725, 726, 733, 734]
attrs = {}
family = {}
for mid in ROCK_FAMILY:
    family[mid] = len(metas)
    metas.append(tuple(primary_ref(P, mid, {1: ROCK_SLOT})))
    attrs[family[mid]] = struct.unpack('<H', P['attrs'][mid * 2:mid * 2 + 2])[0]
print('familia de montanha: %d metatiles (secundario %d..%d)' % (len(family), min(family.values()), max(family.values())))

write_tileset(os.path.join(OUT, 'altar_sun_moon'), bank, metas, PAL, attrs=attrs, preview_slot=7)
write_png(os.path.join(OUT, 'tiles_colored.png'), colored_tile_sheet(bank, [day_tiles, portal_tiles], PAL), 3)
json.dump({'w': MW, 'h': MH,
           'grid': [[grid[(c, r)] for c in range(MW)] for r in range(MH)],
           'portal': [[pgrid[(c, r)] for c in range(MW)] for r in range(MH)],
           'walk': WALK, 'swap': PAL.swap, 'rock_family': family,
           'tiles': len(bank.tiles), 'tiles_altar': n_t, 'metatiles': len(metas), 'metatiles_altar': n_m},
          open(os.path.join(OUT, 'altar_grid.json'), 'w'))
print('ok ->', OUT)
