# Salão da mansão Hale com cristal (o saguão fica normal): 3 propostas + 1 alternativa.
# Página: https://claude.ai/artifact/CksFTUjbBYQX2ycHb6JcXo — o autor escolheu a C (Instante parado), 03/10/2026.
# python3 .claude/berry_master/prototipo_corceis/salao_cristal.py <saida> [--instalar C]
#   --instalar C grava o tileset em data/tilesets/secondary/hale_mansion (gTileset_HaleMansion)
#   e o map.bin em data/layouts/Greenfield_Mansion.
# A base é o layout GreenfieldMansionAfter (a mansão sem cristal, que o jogo usa depois do Glastrier).
#   A  Salão vitrificado: tileset próprio (cópia do Inn), slots 7/8 viram rampas de cristal,
#      as peças do salão são duplicadas e repintadas nelas. Mesmo mapa.
#   B  Cristal crescendo: tileset próprio, salão com as cores da casa e peças de cristal
#      novas (slot 8) no chão, na parede e sob o Glastrier. Mesmo mapa.
#   C  Salão em mapa próprio: sem tileset novo; MapTint_Mode liga o filtro de Greenfield
#      no mapa novo. A escada vira warp.
import sys, os, json, struct, collections, shutil
ROOT = '/home/ADMIN/decomps/soulgold_v1'
sys.path.insert(0, os.path.join(ROOT, '.claude/skills/prototipo-de-mapa'))
from mapa_kit import *

ARGS = [a for a in sys.argv[1:] if not a.startswith('--')]
INSTALAR = sys.argv[sys.argv.index('--instalar') + 1] if '--instalar' in sys.argv else None
OUT = ARGS[0] if ARGS and ARGS[0] != INSTALAR else os.path.join(os.path.dirname(os.path.abspath(__file__)), 'salao_cristal')
os.makedirs(OUT, exist_ok=True)
L = load_layout('GreenfieldMansionAfter'); W, H = L['w'], L['h']; P, S = L['prim'], L['sec']
BASE = list(L['blocks'])
OBJS = json.load(open(os.path.join(ROOT, 'data/maps/Greenfield_Mansion/map.json')))['object_events']
BYID = {o['local_id']: o for o in OBJS}
MOLLY, GLAS, SCI, MOLLY_S = (BYID['LOCALID_MANSION_' + k] for k in ('MOLLY', 'GLASTRIER', 'SCIENTIST', 'MOLLY_SALON'))
def obj(gfx, x, y, face='UP'):
    return dict(local_id='', graphics_id='OBJ_EVENT_GFX_' + gfx, x=x, y=y, elevation=3,
                movement_type='MOVEMENT_TYPE_FACE_' + face, script='NULL', flag='0')
PLAYER = obj('BRENDAN_NORMAL', 13, 8); PEONIA = obj('PICNICKER', 11, 9)
CENA = [GLAS, MOLLY_S, PLAYER, PEONIA, SCI, MOLLY]
NB_TILES = 1 + max((e & 0x3ff) - 640 for m in S['metas'] for e in m if (e & 0x3ff) >= 640)   # 181
NB_METAS = len(S['metas'])                                                                    # 128
TILES, PALS = combine(P, S)

def zone(x, y):
    """'full' no salão, 'geada' no corredor que desce até a escada, None no saguão."""
    if y <= 9: return 'full'
    if y <= 11 and x <= 5: return 'geada'
    return None

def save(name, cv, scale=2): write_png(os.path.join(OUT, name + '.png'), cv, scale)
def to5(c): return [v >> 3 for v in c]
def to8(v): return (v << 3) | (v >> 2)

# ------------------------------------------------- a mesma conta do jogo (src/berry_garden.c)
CRYSTAL = ((12, 13, 17), (30, 31, 31))           # GreenfieldCrystal_Tint (proposta E de Greenfield)
def tint(c, ramp=CRYSTAL, k=3):
    c5 = to5(c); l = (c5[0] * 5 + c5[1] * 9 + c5[2] * 2) // 16
    d, li = ramp
    out = [((d[i] + (li[i] - d[i]) * l // 31) * k + c5[i] * (4 - k)) // 4 for i in range(3)]
    return tuple(to8(v) for v in out)

def kmeans(colors, n):
    """colors = Counter{rgb: peso} -> n cores (ordenadas por luz)."""
    pts = list(colors.items())
    if len(pts) <= n: return sorted(c for c, _ in pts)
    pts.sort(key=lambda p: sum(p[0]))
    cent = [pts[int(i * (len(pts) - 1) / (n - 1))][0] for i in range(n)]
    for _ in range(25):
        acc = [[0, 0, 0, 0] for _ in cent]
        for c, w in pts:
            j = min(range(len(cent)), key=lambda j: sum((c[k] - cent[j][k]) ** 2 for k in range(3)))
            for k in range(3): acc[j][k] += c[k] * w
            acc[j][3] += w
        cent = [tuple(rgb5(tuple(a[k] // a[3] for k in range(3)))) if a[3] else cent[j] for j, a in enumerate(acc)]
    return sorted(set(cent), key=sum)

def nearest(c, pal):
    return 1 + min(range(len(pal)), key=lambda j: sum((c[k] - pal[j][k]) ** 2 for k in range(3)))

# ================================================================= tileset próprio (A e B)
class NewTS:
    """Cópia do secundário do Inn que recebe tiles e metatiles novos no fim."""
    def __init__(self):
        self.tiles = [t for t in S['tiles'][:NB_TILES]]
        self.metas = list(S['metas']); self.attrs = bytearray(S['attrs'])
        self.pals = {i: list(S['pals'].get(i, [(0, 0, 0)] * 16)) for i in range(16)}
        self.index = {}
    def tile(self, px):
        key = tuple(tuple(r) for r in px)
        for hf in (0, 1):
            for vf in (0, 1):
                k = tuple(tuple(r[::-1] if hf else r) for r in (key[::-1] if vf else key))
                if k in self.index: return self.index[k], hf, vf
        self.tiles.append([list(r) for r in key]); self.index[key] = 640 + len(self.tiles) - 1
        return self.index[key], 0, 0
    def meta(self, entries, attr=0):
        self.metas.append(tuple(entries)); self.attrs += struct.pack('<H', attr)
        return 1024 + len(self.metas) - 1
    def write(self, folder):
        os.makedirs(os.path.join(folder, 'palettes'), exist_ok=True)
        assert len(self.tiles) <= 384, len(self.tiles)
        assert len(self.metas) <= 1024, len(self.metas)
        for i in range(13):
            write_pal(os.path.join(folder, 'palettes', '%02d.pal' % i), [rgb5(c) for c in (self.pals[i] + [(0, 0, 0)] * 16)[:16]])
        rows = (len(self.tiles) + 15) // 16
        idx = [[0] * 128 for _ in range(rows * 8)]
        for n, t in enumerate(self.tiles):
            for y in range(8):
                for x in range(8): idx[(n // 16) * 8 + y][(n % 16) * 8 + x] = t[y][x]
        write_png_indexed4(os.path.join(folder, 'tiles.png'), idx, self.pals[7])
        with open(os.path.join(folder, 'metatiles.bin'), 'wb') as f:
            for m in self.metas: f.write(struct.pack('<12H', *m))
        open(os.path.join(folder, 'metatile_attributes.bin'), 'wb').write(bytes(self.attrs))
        return dict(tiles=len(self.tiles), metas=len(self.metas))

def attr_of(mid):
    a = P['attrs'] if mid < 1024 else S['attrs']; i = mid if mid < 1024 else mid - 1024
    return struct.unpack('<H', a[i * 2:i * 2 + 2])[0]

def read_back(folder, mapbin):
    sec = load_tileset(None, path=folder)
    return sec, read_blocks(mapbin)

report = {}

# ================================================================= A · salão vitrificado
def build_a():
    ts = NewTS()
    used = collections.defaultdict(set)                          # zona -> metatiles
    for i, v in enumerate(BASE):
        z = zone(i % W, i // W)
        if z and (v & 0x7ff): used[z].add(v & 0x7ff)
    # 1) cores que o filtro dá a cada pixel do salão; 15 por rampa (slot 7 cheio, slot 8 geada)
    RAMPS = {'full': (7, 3), 'geada': (8, 2)}                    # slot, peso do filtro (3/4 e 1/2)
    hist = {z: collections.Counter() for z in RAMPS}
    for z, mids in used.items():
        for mid in mids:
            for e in metatile_entries(P, S, mid):
                t, pl = TILES[e & 0x3ff], PALS[e >> 12]
                for r in t:
                    for c in r:
                        if c: hist[z][rgb5(tint(pl[c], k=RAMPS[z][1]))] += 1
    for z, (slot, _) in RAMPS.items():
        cols = kmeans(hist[z], 15)
        ts.pals[slot] = [(248, 0, 248)] + cols + [(0, 0, 0)] * (15 - len(cols))
    # 2) duplicar cada metatile do salão com tiles repintados
    dup = {}
    for z, mids in used.items():
        slot, k = RAMPS[z]; pal = ts.pals[slot][1:16]
        for mid in sorted(mids):
            ents = []
            for e in metatile_entries(P, S, mid):
                tid, hf, vf, pl = e & 0x3ff, e >> 10 & 1, e >> 11 & 1, e >> 12
                src = TILES[tid]
                if not any(any(r) for r in src):
                    ents.append(e); continue
                px = [[nearest(rgb5(tint(PALS[pl][c], k=k)), pal) if c else 0 for c in r] for r in src]
                nt, h2, v2 = ts.tile(px)
                ents.append(nt - 640 + 640 | ((hf ^ h2) << 10) | ((vf ^ v2) << 11) | (slot << 12))
            dup[(z, mid)] = ts.meta(ents, attr_of(mid))
    b = list(BASE)
    for i, v in enumerate(b):
        z = zone(i % W, i // W)
        if z and (v & 0x7ff): b[i] = (v & ~0x7ff) | dup[(z, v & 0x7ff)]
    return ts, b, used

def report_check(bb, seen, need):
    return [k for k, v in need.items() if v not in seen] + [str(x) for x in check_objects(bb, W, CENA)]

def finalize(tag, ts, b):
    folder = os.path.join(OUT, tag + '_tileset'); r = ts.write(folder)
    write_blocks(os.path.join(OUT, tag + '_map.bin'), [b[y * W:(y + 1) * W] for y in range(H)])
    sec, bb = read_back(folder, os.path.join(OUT, tag + '_map.bin'))
    full = render_blocks(bb, W, H, P, sec, objects=CENA)
    save(tag + '_cena', full)
    save(tag + '_colisao', render_blocks(bb, W, H, P, sec, objects=CENA, overlay=True))
    save(tag + '_zoom', crop(full, 6 * 16, 1 * 16, 21 * 16, 13 * 16), 3)
    def walk(x, y): return 0 <= x < W and 0 <= y < H and not (bb[y * W + x] >> 11 & 1)
    start = (3, 11); seen = {start}; q = [start]
    while q:
        x, y = q.pop()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            n = (x + dx, y + dy)
            if n not in seen and walk(*n): seen.add(n); q.append(n)
    need = {'jogador chega (13,8)': (13, 8), 'jogador após a captura (13,6)': (13, 6), 'nota do Hale, de (14,4)': (14, 4),
            'Molly no salão (14,9)': (14, 9), 'Peonia (11,9)': (11, 9)}
    if tag == INSTALAR:
        assert not report_check(bb, seen, need), report_check(bb, seen, need)
        dest = os.path.join(ROOT, 'data/tilesets/secondary/hale_mansion')
        for n in ('tiles.png', 'metatiles.bin', 'metatile_attributes.bin'):
            os.makedirs(os.path.join(dest, 'palettes'), exist_ok=True); shutil.copy(os.path.join(folder, n), os.path.join(dest, n))
        for i in range(13):
            shutil.copy(os.path.join(folder, 'palettes', '%02d.pal' % i), os.path.join(dest, 'palettes', '%02d.pal' % i))
        shutil.copy(os.path.join(OUT, tag + '_map.bin'), os.path.join(ROOT, 'data/layouts/Greenfield_Mansion/map.bin'))
        print('instalado', tag, '- tiles', r['tiles'], 'metatiles', r['metas'])
    report[tag] = dict(r, novos_tiles=r['tiles'] - NB_TILES, novos_metas=r['metas'] - NB_METAS,
                       acesso={k: (v in seen) for k, v in need.items()}, npc_em_bloqueio=check_objects(bb, W, CENA),
                       pals={n: [list(c) for c in ts.pals[n]] for n in (7, 8)})

def proposta_a():
    ts, b, used = build_a()
    finalize('A', ts, b)
    report['A'].update(metas_salao=len(used['full']), metas_geada=len(used['geada']))

# ================================================================= B · cristal crescendo
GF = read_pal(os.path.join(ROOT, 'data/tilesets/secondary/greenfield/palettes/07.pal'))
# slot 8: a paleta de cristal de Greenfield + sombra quente no assoalho
B_PAL = [(248, 0, 248), GF[1], GF[2], GF[3], GF[4], GF[5], GF[7], GF[8], GF[9], GF[10], GF[11],
         (120, 88, 72), (176, 200, 232), (0, 0, 0), (0, 0, 0), (0, 0, 0)]
K = dict(o=1, d=2, m=3, l=4, h=5, w=5, sh2=6, p1=7, p2=8, p3=9, p4=10, sh=11, g=12)

class Cv:
    def __init__(self, w, h): self.w, self.h = w, h; self.px = [[None] * w for _ in range(h)]
    def put(self, x, y, k):
        if 0 <= x < self.w and 0 <= y < self.h: self.px[y][x] = k
    def get(self, x, y): return self.px[y][x] if 0 <= x < self.w and 0 <= y < self.h else None
    def cell(self, cx, cy):
        return [[K[self.px[cy * 16 + y][cx * 16 + x]] if self.px[cy * 16 + y][cx * 16 + x] else 0 for x in range(16)] for y in range(16)]

def shard(cv, cx, by, h, hw, lean=0.0, prism=False):
    """Prisma com ponta (o mesmo desenho de Greenfield): luz de cima à esquerda."""
    th = max(3, int(hw * 1.7)); top = by - h + 1
    for y in range(top, by + 1):
        t = y - top; w = hw * min(1.0, (t + 1) / th); c = cx + lean * (by - y) / h
        xl, xr = int(round(c - w)), int(round(c + w))
        for x in range(xl, xr + 1):
            if x in (xl, xr) or t == 0 or y == by: k = 'o'
            else:
                r = (x - c) / max(w, 0.5)
                k = 'l' if r < -0.2 else 'h' if r < 0.12 else 'm' if r < 0.55 else 'd'
                if by - y <= 2 and k != 'd': k = {'l': 'm', 'h': 'l', 'm': 'd'}[k]
                if prism and k == 'm': k = ('p4', 'p3', 'p2', 'p1')[min(3, 4 * t // max(h - 2, 1))]
            cv.put(x, y, k)
    cv.put(int(round(cx + lean * (h - th) / h)), top + th, 'w')

def shadow(cv, x0, x1, y):
    for x in range(x0, x1 + 1):
        for yy in (y, y + 1):
            if cv.get(x, yy) is None and not (yy == y + 1 and x in (x0, x1)): cv.put(x, yy, 'sh')

def vein(cv, ox, oy, seed):
    """Geada no assoalho: rachaduras finas, andáveis."""
    import random; R = random.Random(seed)
    for _ in range(3):
        x, y = ox + R.randint(2, 13), oy + R.randint(2, 13)
        for _ in range(R.randint(5, 9)):
            cv.put(x, y, R.choice(('m', 'd', 'l')))
            x += R.choice((-1, 0, 1, 1)); y += R.choice((-1, 0, 1))
            x = max(ox, min(ox + 15, x)); y = max(oy, min(oy + 15, y))

def crust(cv, ox, oy, h, seed):
    """Crosta de cristal subindo pela parede (sobreposta à parede original)."""
    import random; R = random.Random(seed)
    for i in range(4):
        cx = ox + 2 + i * 4 + R.randint(-1, 1)
        shard(cv, cx, oy + h - 1, R.randint(h // 2, h), R.choice((2, 2, 3)), lean=R.choice((-0.6, 0, 0.6)), prism=(i == 1))

def grow(ts, b0, slot, off):
    """Peças de cristal (arte no `slot`, cores a partir do índice off+1) por cima do mapa b0."""
    cv = Cv(16 * 16, 4 * 16)
    shard(cv, 8, 14, 13, 4); shard(cv, 4, 14, 7, 2, -0.4); shard(cv, 12, 14, 8, 2, 0.5); shadow(cv, 2, 14, 15)   # c0: tufo
    shard(cv, 16 + 8, 30, 29, 5, prism=True); shard(cv, 16 + 3, 30, 10, 2, -0.5); shard(cv, 16 + 13, 30, 12, 2, 0.4); shadow(cv, 16 + 1, 16 + 15, 31)  # c1 1x2 alto
    shard(cv, 32 + 16, 30, 30, 9, prism=True); shard(cv, 32 + 5, 30, 18, 4, -0.5); shard(cv, 32 + 27, 30, 20, 4, 0.5)
    shard(cv, 32 + 10, 30, 9, 2, -0.2); shard(cv, 32 + 22, 30, 10, 2, 0.3); shadow(cv, 32 + 1, 32 + 31, 31)       # c2-3 2x2 grande
    for i in range(4): vein(cv, (4 + i) * 16, 0, 11 + i)                                                       # c4-7 geada
    for i in range(4): crust(cv, (8 + i) * 16, 0, 32, 40 + i)                                                   # c8-11 crosta 1x2
    for i in range(3):                                                                                         # c12-14 cama
        ox = (12 + i) * 16
        for x in range(ox, ox + 16):
            for y in range(10, 16): cv.put(x, y, 'l' if y == 10 else 'm' if y < 13 else 'd' if y < 15 else 'o')
        shard(cv, ox + 4 + i * 3, 11, 7, 2, 0.3); shard(cv, ox + 11, 11, 5, 1, -0.3)
    def ent(cx, cy, q):
        px = cv.cell(cx, cy); sub = [[c + off if c else 0 for c in r[(q % 2) * 8:(q % 2) * 8 + 8]] for r in px[(q // 2) * 8:(q // 2) * 8 + 8]]
        if not any(any(r) for r in sub): return 0
        nt, hf, vf = ts.tile(sub); return nt | (hf << 10) | (vf << 11) | (slot << 12)
    cache = {}
    def over(x, y, cx, cy, top=False):
        """O metatile que está em (x,y) com a arte (cx,cy) na camada de cima (top) ou do meio."""
        mid = b0[y * W + x] & 0x7ff
        if (mid, cx, cy, top) not in cache:
            e = list(ts.metas[mid - 1024]) if mid >= 1024 else list(P['metas'][mid])
            free = [l for l in (1, 2) if not any(e[l * 4:l * 4 + 4])]
            l = 2 if top and 2 in free else free[0]
            e[l * 4:l * 4 + 4] = [ent(cx, cy, q) for q in range(4)]
            cache[(mid, cx, cy, top)] = ts.meta(e, struct.unpack('<H', bytes(ts.attrs[(mid - 1024) * 2:(mid - 1024) * 2 + 2]))[0] if mid >= 1024 else attr_of(mid))
        return cache[(mid, cx, cy, top)]
    b = list(b0); blocked = set()
    def put(x, y, mid, coll=0):
        b[y * W + x] = pack_block(mid, coll, 3)
        if coll: blocked.add((x, y))
    for i, x in enumerate((0, 1, 2, 9, 10, 17, 23, 24, 25)):                      # crosta na parede
        for dy, cy in ((2, 0), (3, 1)): put(x, dy, over(x, dy, 8 + i % 4, cy), 1)
    for (x, y) in ((0, 5), (25, 5), (4, 9), (21, 9), (17, 5), (7, 6)): put(x, y, over(x, y, 0, 0), 1)
    for (x, y) in ((3, 5), (22, 5), (10, 5), (19, 7)):
        put(x, y - 1, over(x, y - 1, 1, 0, top=True), b0[(y - 1) * W + x] >> 11 & 1); put(x, y, over(x, y, 1, 1), 1)
    for (x, y) in ((1, 6), (23, 6)):
        for dx in (0, 1):
            for dy in (0, 1): put(x + dx, y + dy, over(x + dx, y + dy, 2 + dx, dy), 1)
    for i, x in enumerate((12, 13, 14)): put(x, 5, over(x, 5, 12 + i, 0), 0); blocked.add((x, 5))   # cama do Glastrier (andável, mas sem geada por cima)
    import random; R = random.Random(7)
    for y in range(5, 12):                                                          # geada, andável
        for x in range(W):
            if zone(x, y) and (x, y) not in blocked and (BASE[y * W + x] & 0x7ff) == 1 and R.random() < (0.20 if y < 10 else 0.12):
                put(x, y, over(x, y, 4 + R.randrange(4), 0), 0)
    return b, cv

def proposta_b():
    ts = NewTS(); ts.pals[7] = B_PAL
    # o quadro da parede (1040) tem 1 cor no slot 7 que o slot 8 também tem: passa todo para o 8
    e = list(metatile_entries(P, S, 1040))
    for n, v in enumerate(e):
        if v >> 12 == 7:
            px = [[6 if c == 4 else c for c in r] for r in TILES[v & 0x3ff]]
            nt, hf, vf = ts.tile(px)
            e[n] = nt | ((v >> 10 & 1) ^ hf) << 10 | ((v >> 11 & 1) ^ vf) << 11 | (8 << 12)
    quadro = ts.meta(e, attr_of(1040))
    b0 = [(v & ~0x7ff) | quadro if (v & 0x7ff) == 1040 else v for v in BASE]
    b, cv = grow(ts, b0, 7, 0)
    finalize('B', ts, b)
    save('pecas', [[tuple(B_PAL[K[k]]) if k else (40, 40, 52) for k in row] for row in cv.px], 3)

def proposta_c():
    """A + B, como Greenfield: o salão com o filtro (slot 7) e as peças (slot 8, depois da geada)."""
    ts, b0, used = build_a()
    g = [c for c in ts.pals[8][1:] if c != (0, 0, 0)]
    assert len(g) + 12 <= 15, len(g)
    ts.pals[8] = [(248, 0, 248)] + g + B_PAL[1:13] + [(0, 0, 0)] * (3 - len(g))
    b, cv = grow(ts, b0, 8, len(g))
    finalize('C', ts, b)

# ================================================================= C · mapa próprio com o filtro
def proposta_d():
    pals = [list(p) for p in PALS]
    tinted = [[rgb5(tint(c)) for c in p] for p in pals]
    def render_with(pl, blocks, w, h, objs):
        cv = [[(0, 0, 0)] * (w * 16) for _ in range(h * 16)]
        for i, v in enumerate(blocks):
            draw_meta(cv, (i % w) * 16, (i // w) * 16, metatile_entries(P, S, v & 0x7ff), TILES, pl)
        for o in sorted(objs, key=lambda o: o['y']): draw_object(cv, o, False)
        return cv
    # salão: linhas 0..13 (a escada desce até a 14); saguão: o resto, sem mudança
    HS = 14
    sal = BASE[:HS * W]
    objs = [o for o in CENA if o['y'] < HS]
    save('D_salao', render_with(tinted, sal, W, HS, objs))
    full = render_with(tinted, BASE, W, H, [])[:HS * 16] + render_with(pals, BASE, W, H, [])[HS * 16:]
    for o in sorted(CENA, key=lambda o: o['y']): draw_object(full, o, False)
    save('D_cena', full)
    save('D_zoom', crop(full, 6 * 16, 1 * 16, 21 * 16, 13 * 16), 3)
    report['D'] = dict(altura_salao=HS)

save('hoje', render_blocks(BASE, W, H, P, S, objects=CENA))
save('hoje_zoom', crop(render_blocks(BASE, W, H, P, S, objects=CENA), 6 * 16, 1 * 16, 21 * 16, 13 * 16), 3)
proposta_a(); proposta_b(); proposta_c(); proposta_d()
json.dump(report, open(os.path.join(OUT, 'report.json'), 'w'), indent=1)
print(json.dumps({k: {kk: vv for kk, vv in v.items() if kk != 'pals'} for k, v in report.items()}, indent=1, ensure_ascii=False))
