# Greenfield: 5 propostas de tileset de cristal (gTileset_Greenfield = NewBarkTown + pecas novas no fim).
# Pagina: https://claude.ai/artifact/W2haZmEgrB8MxF3CKdTaz3 — o autor escolheu a E (Instante parado), 03/10/2026.
# python3 .claude/berry_master/prototipo_corceis/greenfield_cristal.py <saida> [--instalar E]
#   -> por proposta: tileset escrito (tiles.png, palettes, metatiles.bin), map.bin, renders dia/noite/zoom.
#   --instalar E grava o tileset em data/tilesets/secondary/greenfield e o map.bin em data/layouts/Greenfield.
# A base e o layout GreenfieldAfter (o mapa sem cristais, que o jogo usa depois do Glastrier).
# A rampa e a paleta da E tem de bater com GreenfieldCrystal_Tint e GREENFIELD_CRYSTAL_PAL (src/berry_garden.c).
# O render le os ARQUIVOS escritos e aplica o mesmo TintTowardRamp do jogo (src/berry_garden.c).
import sys, os, json, struct, collections
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..', '..'))
sys.path.insert(0, os.path.join(ROOT, '.claude/skills/prototipo-de-mapa'))
from mapa_kit import *

ARGS = [a for a in sys.argv[1:] if not a.startswith('--')]
INSTALAR = sys.argv[sys.argv.index('--instalar') + 1] if '--instalar' in sys.argv else None
OUT = ARGS[0] if ARGS and ARGS[0] != INSTALAR else os.path.join(HERE, 'greenfield_cristal')
os.makedirs(OUT, exist_ok=True)
L = load_layout('GreenfieldAfter'); W, H = L['w'], L['h']
P, NB = L['prim'], L['sec']
BASE = list(L['blocks'])
OBJS = json.load(open(os.path.join(ROOT, 'data/maps/Greenfield/map.json')))['object_events']
NB_TILES = 1 + max((e & 0x3ff) - 640 for m in NB['metas'] for e in m if (e & 0x3ff) >= 640)   # 253
NB_METAS = len(NB['metas'])                                                                    # 216
GRASS = list(P['metas'][0][4:8])        # grama lisa (camada do meio do metatile 0)
PATH = list(P['metas'][220][4:8])       # areia do caminho (miolo)

# ============================================================== arte (chaves de material)
def shard(cv, cx, by, h, hw, lean=0.0, glyph=False, prism=False):
    """Prisma de cristal com ponta: luz de cima a esquerda, aresta clara, face direita escura."""
    th = max(3, int(hw * 1.7))
    top = by - h + 1
    for y in range(top, by + 1):
        t = y - top
        w = hw * min(1.0, (t + 1) / th)
        c = cx + lean * (by - y) / h
        xl, xr = int(round(c - w)), int(round(c + w))
        for x in range(xl, xr + 1):
            if x in (xl, xr) or t == 0 or y == by:
                k = 'o'
            else:
                r = (x - c) / max(w, 0.5)
                k = 'l' if r < -0.2 else 'h' if r < 0.12 else 'm' if r < 0.55 else 'd'
                if by - y <= 2 and k != 'd':
                    k = {'l': 'm', 'h': 'l', 'm': 'd'}[k]
                if prism and k == 'm':      # face direita refrata: arco-iris de cima para baixo
                    k = ('p4', 'p3', 'p2', 'p1')[min(3, 4 * t // max(h - 2, 1))]
            cv.put(x, y, k)
    cv.put(int(round(cx + lean * (h - th) / h)), top + th, 'w')     # brilho na aresta
    if glyph:   # olho de Unown gravado na face
        gy = top + h // 2; gx = int(round(cx + lean * (by - gy) / h))
        for dx, dy in ((-1, -2), (0, -2), (1, -2), (-2, -1), (2, -1), (-2, 0), (2, 0), (-2, 1), (2, 1), (-1, 2), (0, 2), (1, 2)):
            cv.put(gx + dx, gy + dy, 'g')
        cv.put(gx, gy, 'g')

def shadow(cv, x0, x1, y):
    """Sombra no chao, para a direita e para baixo (luz de cima a esquerda); so em pixel vazio."""
    for x in range(x0, x1 + 1):
        for yy in (y, y + 1):
            if cv.get(x, yy) is None and not (yy == y + 1 and x in (x0, x1)): cv.put(x, yy, 'sh')

def piece_small(cv, ox, oy, s):
    shadow(cv, ox + 2, ox + 15, oy + 13)
    shard(cv, ox + 5, oy + 14, 12, 2.6, -1.6, prism=s['prism'])
    shard(cv, ox + 10, oy + 14, 9, 2.2, 1.8, prism=s['prism'])
    shard(cv, ox + 3, oy + 14, 5, 1.6, -1.2, prism=s['prism'])
def piece_small2(cv, ox, oy, s):
    shadow(cv, ox + 2, ox + 15, oy + 13)
    shard(cv, ox + 9, oy + 14, 11, 2.8, 1.2, prism=s['prism'])
    shard(cv, ox + 4, oy + 14, 7, 2.0, -1.8, prism=s['prism'])
    shard(cv, ox + 13, oy + 14, 4, 1.4, 1.0, prism=s['prism'])
def piece_tall(cv, ox, oy, s):          # 16x32: celula de cima so visual (camada top)
    shadow(cv, ox + 1, ox + 15, oy + 29)
    shard(cv, ox + 12, oy + 30, 11, 2.2, 1.6, prism=s['prism'])
    shard(cv, ox + 7, oy + 30, 27, 3.8, -0.8, glyph=s['glyph'], prism=s['prism'])
    shard(cv, ox + 3, oy + 30, 8, 1.8, -1.6, prism=s['prism'])
def piece_big(cv, ox, oy, s):           # 32x32, 2x2 bloqueado
    shadow(cv, ox + 1, ox + 31, oy + 29)
    shard(cv, ox + 22, oy + 30, 22, 4.2, 1.6, prism=s['prism'])
    shard(cv, ox + 8, oy + 30, 20, 3.8, -2.4, prism=s['prism'])
    shard(cv, ox + 15, oy + 30, 30, 5.2, 0.2, glyph=s['glyph'], prism=s['prism'])
    shard(cv, ox + 4, oy + 30, 9, 2.2, -1.5, prism=s['prism'])
    shard(cv, ox + 27, oy + 30, 10, 2.2, 1.5, prism=s['prism'])
    shard(cv, ox + 11, oy + 30, 8, 2.0, 0.6, prism=s['prism'])
def piece_flower(cv, ox, oy, s, big=False):
    """Flor de vidro (andavel). big=True: tulipa de cristal 16x32, cima na camada top."""
    if big:
        for y in range(oy + 14, oy + 31): cv.put(ox + 8, y, 'd'); cv.put(ox + 7, y, 'm')
        for i in range(5):
            cv.put(ox + 9 + i, oy + 24 - i, 'l'); cv.put(ox + 10 + i, oy + 24 - i, 'o')
            cv.put(ox + 6 - i, oy + 27 - i, 'l'); cv.put(ox + 5 - i, oy + 27 - i, 'o')
        shard(cv, ox + 5, oy + 15, 9, 2.4, -1.2, prism=s['prism'])
        shard(cv, ox + 11, oy + 15, 9, 2.4, 1.2, prism=s['prism'])
        shard(cv, ox + 8, oy + 15, 12, 3.0, 0, prism=s['prism'])
        for x in range(ox + 5, ox + 12): cv.put(x, oy + 15, 'o')
        return
    for fx, fy in ((4, 5), (11, 9)):
        X, Y = ox + fx, oy + fy
        cv.vline(X, Y + 3, Y + 6, 'd'); cv.put(X + 1, Y + 5, 'm')
        for dx, dy in ((0, -2), (-2, 0), (2, 0), (0, 2)):       # 4 petalas em losango
            for ex, ey in ((0, 0), (-1, 0), (1, 0), (0, -1), (0, 1)):
                px, py = X + dx + ex, Y + dy + ey
                k = 'h' if ex + ey < 0 else 'l' if ex + ey == 0 else 'm'
                cv.put(px, py, k)
        for y in range(Y - 4, Y + 5):
            for x in range(X - 4, X + 5):
                if cv.get(x, y) is None and any(cv.get(x + a, y + b) in ('h', 'l', 'm') for a, b in ((1, 0), (-1, 0), (0, 1), (0, -1))):
                    cv.put(x, y, 'o')
        cv.put(X, Y, 'w' if not s['prism'] else 'p2')
        cv.put(X - 1, Y - 1, 'p1' if s['prism'] else 'h')

def piece_vein(cv, ox, oy, s, v):
    """Lascas de cristal deitadas no caminho (andavel, camada do meio sobre a areia)."""
    pts = [(3, 12, 2), (7, 9, 1), (11, 11, 2), (13, 5, 1), (5, 4, 1)] if v == 0 else [(4, 6, 2), (9, 4, 1), (12, 10, 2), (6, 12, 1), (2, 2, 1)]
    for x, y, r in pts:
        X, Y = ox + x, oy + y
        for dy in range(-r - 1, r + 2):
            for dx in range(-r - 2, r + 3):
                d = abs(dx) / (r + 1.5) + abs(dy) / (r + 0.5)
                if d <= 1.0:
                    edge = abs(dx) / (r + 1.5) + abs(dy) / (r + 0.5) > 0.62
                    k = 'o' if edge else ('h' if dx < 0 and dy <= 0 else 'l' if dy <= 0 else 'm')
                    cv.put(X + dx, Y + dy, k)
        cv.put(X - 1, Y - 1, 'w')

# Folha: cada peca em celulas 16x16; (nome, col, row, w, h, como montar cada celula)
SHEET = [('small', 0, 0, 1, 1), ('small2', 1, 0, 1, 1), ('flower', 2, 0, 1, 1), ('vein0', 3, 0, 1, 1), ('vein1', 4, 0, 1, 1),
         ('tall', 5, 0, 1, 2), ('tulip', 6, 0, 1, 2), ('big', 7, 0, 2, 2)]
def draw_sheet(s):
    cv = Canvas(16 * 9, 32)
    piece_small(cv, 0, 0, s); piece_small2(cv, 16, 0, s); piece_flower(cv, 32, 0, s)
    piece_vein(cv, 48, 0, s, 0); piece_vein(cv, 64, 0, s, 1)
    piece_tall(cv, 80, 0, s); piece_flower(cv, 96, 0, s, big=True); piece_big(cv, 112, 0, s)
    return cv

KEYS = ['o', 'd', 'm', 'l', 'h', 'w', 'sh', 'g', 'p1', 'p2', 'p3', 'p4']
def rgb(*v): return tuple(v)

# ============================================================== as 5 propostas
TINT_ICE = ((6, 8, 14), (28, 31, 31))          # o de hoje (GreenfieldCrystal_Tint)
PROPS = [
    dict(id='A', nome='Gelo fiel', tint=TINT_ICE, exempt=False, glyph=False, prism=False,
         cores=dict(o=(40, 64, 112), d=(96, 144, 200), m=(144, 192, 232), l=(200, 232, 248), h=(232, 248, 255), w=(255, 255, 255)),
         resumo='O filtro de hoje continua igual; entram só cristais azul-gelo espalhados, tingidos junto com a cidade. É a mudança mais discreta.',
         pecas=dict(small=[(5, 9), (16, 9), (24, 12), (5, 16), (19, 19), (23, 21), (8, 30), (18, 29)],
                    small2=[(13, 11), (4, 23), (12, 18), (23, 17)],
                    tall=[(15, 12), (7, 21)], big=[], flower=[], tulip=[], vein=[])),
    dict(id='B', nome='Cristal Unown', tint=((7, 5, 13), (29, 27, 31)), exempt=True, glyph=True, prism=False,
         cores=dict(o=(56, 32, 96), d=(120, 88, 184), m=(168, 136, 224), l=(208, 184, 248), h=(240, 224, 255), w=(255, 255, 255), g=(72, 32, 128)),
         resumo='Como no filme: cristal lilás brotando do chão em blocos grandes, com o olho de um Unown gravado nos maiores. A cidade fica num tom lavanda e os cristais saem do filtro para manter a cor.',
         pecas=dict(small=[(5, 9), (24, 12), (19, 21), (8, 30), (23, 21)], small2=[(17, 9), (4, 23), (12, 19), (18, 29)],
                    tall=[(7, 18), (16, 12), (24, 17)], big=[(13, 11), (5, 14), (18, 17)], flower=[], tulip=[], vein=[])),
    dict(id='C', nome='Jardim de vidro', tint=((8, 11, 12), (29, 31, 30)), exempt=True, glyph=False, prism=False,
         cores=dict(o=(112, 80, 128), d=(200, 168, 216), m=(232, 208, 240), l=(250, 236, 250), h=(255, 250, 255), w=(255, 255, 255)),
         resumo='Greenfield é a cidade das flores: todas as flores viram flores de vidro e nascem tulipas de cristal da altura de uma pessoa. Quase nenhum espinho; a Peonia diz “the flowers are glass” e o jogador vê isso.',
         pecas=dict(small=[(24, 12), (8, 30)], small2=[(4, 23)], tall=[], big=[], vein=[],
                    flower='todas', tulip=[(15, 12), (7, 18), (19, 19), (23, 17), (5, 16), (13, 12), (24, 16)])),
    dict(id='D', nome='A onda da mansão', tint=TINT_ICE, exempt=True, glyph=False, prism=False,
         cores=dict(o=(16, 56, 88), d=(32, 120, 160), m=(72, 184, 216), l=(152, 232, 248), h=(216, 252, 255), w=(255, 255, 255)),
         resumo='O cristal nasce da mansão: blocos enormes encostados nela, veios correndo pelo caminho para o sul e espinhos cada vez mais raros. O olho vai sozinho até a porta. Cristal turquesa mais forte que a cidade.',
         pecas=dict(big=[(5, 9), (14, 9), (13, 11)], tall=[(16, 12), (6, 15), (4, 17), (24, 12)],
                    small=[(15, 11), (7, 7), (5, 13), (17, 12), (12, 17), (23, 16)], small2=[(18, 17), (7, 20), (24, 15)],
                    vein=[(8, 12), (9, 12), (10, 12), (11, 12), (13, 14), (12, 14), (15, 14), (18, 14), (10, 17), (10, 20), (21, 17), (10, 24)],
                    flower=[], tulip=[])),
    dict(id='E', nome='Instante parado', tint=((12, 13, 17), (30, 31, 31)), exempt=True, glyph=False, prism=True,
         cores=dict(o=(80, 88, 128), d=(168, 176, 208), m=(208, 216, 240), l=(240, 244, 255), h=(255, 255, 255), w=(255, 255, 255),
                    p1=(255, 168, 200), p2=(255, 232, 144), p3=(152, 240, 208), p4=(152, 200, 255)),
         resumo='Uma foto desbotada: a cidade quase branca, como um dia que parou, e cristais claros com reflexos de arco-íris. É a mais “mágica” e a que mais contrasta com a Greenfield de depois.',
         pecas=dict(small=[(5, 9), (16, 9), (24, 12), (19, 19), (8, 30), (23, 21)], small2=[(4, 23), (12, 18), (18, 29)],
                    tall=[(7, 18), (16, 12), (24, 17)], big=[(13, 11)], flower='todas', tulip=[], vein=[(10, 17), (21, 25), (14, 31)])),
]

# ============================================================== montar o tileset de uma proposta
def build(p):
    sh = (47, 114, 86) if not p['exempt'] else tint_pal([(47, 114, 86)], p['tint'])[0]
    p['cores'] = dict(p['cores'], sh=sh)
    s = dict(glyph=p['glyph'], prism=p['prism'])
    keys = [k for k in KEYS if k in p['cores']]
    pal = PaletteSet({7: keys}, {k: (p['cores'][k], None) for k in keys})
    cv = draw_sheet(s)
    tmap, bad = cut_tiles(cv, pal)
    assert not bad, bad
    bank = TileBank()
    def quads(c, r):
        out = []
        for q in range(4):
            t = tmap.get((c * 2 + q % 2, r * 2 + q // 2))
            if not t: out.append(0); continue
            i, hf, vf = bank.add(t[1])
            out.append(entry(640 + NB_TILES - 1 + i, hf, vf, 7) if i else 0)   # banco: 0 = vazio, 1.. depois dos do New Bark
        return out
    metas = [list(m) for m in NB['metas']]
    ids = {}
    def add(name, cells_entries):
        ids[name] = len(metas) + 1024
        for e in cells_entries: metas.append(e)
    Z = [0] * 4
    add('small', [GRASS + quads(0, 0) + Z]); add('small2', [GRASS + quads(1, 0) + Z])
    add('flower', [GRASS + quads(2, 0) + Z])
    add('vein0', [PATH + quads(3, 0) + Z]); add('vein1', [PATH + quads(4, 0) + Z])
    add('tall', [Z + GRASS + quads(5, 0), GRASS + quads(5, 1) + Z])          # cima: top; baixo: meio
    add('tulip', [Z + GRASS + quads(6, 0), GRASS + quads(6, 1) + Z])
    add('big', [GRASS + quads(7, 0) + Z, GRASS + quads(8, 0) + Z, GRASS + quads(7, 1) + Z, GRASS + quads(8, 1) + Z])
    return dict(metas=metas, new_tiles=bank.tiles[1:], ids=ids, pal=pal, cv=cv)

def write_ts(folder, p, b):
    os.makedirs(os.path.join(folder, 'palettes'), exist_ok=True)
    tiles = NB['tiles'][:NB_TILES] + b['new_tiles']
    assert len(tiles) <= 384, len(tiles)
    for i in range(13):
        cols = NB['pals'].get(i, [(0, 0, 0)] * 16)
        if i == 7: cols = b['pal'].colors_of(7)
        write_pal(os.path.join(folder, 'palettes', '%02d.pal' % i), [rgb5(c) for c in cols])
    rows = (len(tiles) + 15) // 16
    idx = [[0] * 128 for _ in range(rows * 8)]
    for n, t in enumerate(tiles):
        for y in range(8):
            for x in range(8):
                idx[(n // 16) * 8 + y][(n % 16) * 8 + x] = t[y][x]
    write_png_indexed4(os.path.join(folder, 'tiles.png'), idx, b['pal'].colors_of(7))
    with open(os.path.join(folder, 'metatiles.bin'), 'wb') as f:
        for m in b['metas']: f.write(struct.pack('<12H', *m))
    with open(os.path.join(folder, 'metatile_attributes.bin'), 'wb') as f:
        f.write(NB['attrs'] + b'\0\0' * (len(b['metas']) - NB_METAS))
    return len(tiles)

# ============================================================== colocar no mapa
def place(p, ids):
    b = list(BASE); pc = p['pecas']; blocked = set()
    def put(x, y, mid, coll):
        b[y * W + x] = pack_block(mid, coll); (blocked.add((x, y)) if coll else None)
    for x, y in pc['small']: put(x, y, ids['small'], 1)
    for x, y in pc['small2']: put(x, y, ids['small2'], 1)
    for x, y in pc['tall']: put(x, y - 1, ids['tall'], 0); put(x, y, ids['tall'] + 1, 1)
    for x, y in pc['tulip']: put(x, y - 1, ids['tulip'], 0); put(x, y, ids['tulip'] + 1, 1)
    for x, y in pc['big']:
        for i, (dx, dy) in enumerate(((0, 0), (1, 0), (0, 1), (1, 1))): put(x + dx, y + dy, ids['big'] + i, 1)
    for n, (x, y) in enumerate(pc['vein']): put(x, y, ids['vein0'] + n % 2, 0)
    if pc['flower'] == 'todas':
        for i, v in enumerate(b):
            if v & 0x7ff == 4: b[i] = pack_block(ids['flower'])
    return b, blocked

GRASSY = {0, 1, 4, 8, 9}
def check(p, b, blocked):
    """Pecas so em grama (veio so em areia) e tudo alcancavel a partir da entrada oeste."""
    pc = p['pecas']; erros = []
    for x, y in blocked | {(x, y - 1) for x, y in pc['tall'] + pc['tulip']}:
        if BASE[y * W + x] & 0x7ff not in GRASSY: erros.append(('fora da grama', x, y, BASE[y * W + x] & 0x7ff))
    for x, y in pc['vein']:
        if BASE[y * W + x] & 0x7ff != 220: erros.append(('veio fora da areia', x, y))
    npc = {(o['x'], o['y']) for o in OBJS if o['graphics_id'] != 'OBJ_EVENT_GFX_PEONIA'}
    free = lambda x, y: 0 <= x < W and 0 <= y < H and not (b[y * W + x] >> 11 & 1) and (x, y) not in npc
    seen, q = {(0, 12)}, collections.deque([(0, 12)])
    while q:
        x, y = q.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            n = (x + dx, y + dy)
            if n not in seen and free(*n): seen.add(n); q.append(n)
    alvos = {'porta da mansao': [(10, 10)], 'placa': [(10, 15)], 'casa leste': [(20, 12)], 'casa oeste': [(4, 22)],
             'casa do meio': [(15, 22)], 'casa sul': [(15, 29)], 'porta lateral': [(12, 8)],
             'mulher': [(10, 16), (12, 16), (11, 15), (11, 17)], 'velho': [(19, 22), (21, 22), (20, 21), (20, 23)],
             'menino': [(9, 29), (11, 29), (10, 28), (10, 30)]}
    for k, cells in alvos.items():
        if not any(c in seen for c in cells): erros.append(('inalcancavel', k))
    for x, y in npc | {(o['x'], o['y']) for o in OBJS}:
        if (x, y) in blocked: erros.append(('NPC em cima de cristal', x, y))
    return erros

# ============================================================== render como o jogo
def to5(c): return [v >> 3 for v in c]
def to8(v): return (v << 3) | (v >> 2)
def tint_pal(cols, ramp):
    dark, light = ramp; out = []
    for c in cols:
        r, g, b = to5(c); l = (r * 5 + g * 9 + b * 2) // 16
        out.append(tuple(to8(((dark[k] + (light[k] - dark[k]) * l // 31) * 3 + (r, g, b)[k]) // 4) for k in range(3)))
    return out
def tinted(ts, ramp, exempt):
    t = dict(ts); t['pals'] = {i: (c if (exempt and i == 7) or ramp is None else tint_pal(c, ramp)) for i, c in ts['pals'].items()}
    return t
def render(b, prim, sec, night=0.0, objs=OBJS):
    return render_blocks(b, W, H, prim, sec, night=night, objects=objs)
def save(name, cv, scale=2): write_png(os.path.join(OUT, name + '.png'), cv, scale)
PEONIA = [o for o in OBJS if o['graphics_id'] == 'OBJ_EVENT_GFX_PEONIA']
PLAYER = dict(PEONIA[0], graphics_id='OBJ_EVENT_GFX_BRENDAN_NORMAL', x=4, y=12) if PEONIA else None
report = {}
for p in PROPS:
    bld = build(p)
    folder = os.path.join(OUT, 'tileset_' + p['id'])
    ntiles = write_ts(folder, p, bld)
    sec = load_tileset(None, path=folder)                      # confere lendo o que foi escrito
    b, blocked = place(p, bld['ids'])
    erros = check(p, b, blocked)
    write_blocks(os.path.join(OUT, 'map_%s.bin' % p['id']), [b[y * W:(y + 1) * W] for y in range(H)])
    primT = tinted(P, p['tint'], False); secT = tinted(sec, p['tint'], p['exempt'])
    objs = OBJS + [PLAYER]
    dia = render(b, primT, secT, objs=objs)
    save('%s_dia' % p['id'], dia)
    save('%s_noite' % p['id'], render(b, primT, secT, night=1.0, objs=objs), 1)
    save('%s_zoom' % p['id'], [row[3 * 16:20 * 16] for row in dia[6 * 16:20 * 16]], 3)
    # folha das pecas: cada peca sobre a grama/areia tingida
    I = bld['ids']; SW = 16; bb = [pack_block(0)] * (SW * 3)
    for x in range(5, 8):
        for y in range(3): bb[y * SW + x] = pack_block(220)
    for (x, y), m in {(1, 1): I['small'], (2, 1): I['small2'], (3, 1): I['flower'], (5, 1): I['vein0'], (7, 1): I['vein1'],
                      (9, 0): I['tall'], (9, 1): I['tall'] + 1, (11, 0): I['tulip'], (11, 1): I['tulip'] + 1,
                      (13, 0): I['big'], (14, 0): I['big'] + 1, (13, 1): I['big'] + 2, (14, 1): I['big'] + 3}.items():
        bb[y * SW + x] = pack_block(m)
    save('%s_pecas' % p['id'], render_blocks(bb, SW, 3, primT, secT, objects=[]), 4)
    usado = {k: (len(v) if isinstance(v, list) else sum(1 for x in BASE if x & 0x7ff == 4)) for k, v in p['pecas'].items()}
    report[p['id']] = dict(nome=p['nome'], tiles_novos=len(bld['new_tiles']), tiles_total=ntiles,
                           metatiles_novos=len(bld['metas']) - NB_METAS, celulas_bloqueadas=len(blocked),
                           usado=usado, erros=erros)
    print(p['id'], report[p['id']])
    if p['id'] == INSTALAR:
        assert not erros, erros
        write_ts(os.path.join(ROOT, 'data/tilesets/secondary/greenfield'), p, bld)
        write_blocks(os.path.join(ROOT, 'data/layouts/Greenfield/map.bin'), [b[y * W:(y + 1) * W] for y in range(H)])
        print('instalado', p['id'], 'metatiles novos a partir de', 1024 + NB_METAS)

# depois (estado 12): New Bark original, sem cristal e sem filtro
save('depois_dia', render(BASE, P, NB, objs=OBJS + [PLAYER]))
save('hoje_dia', render(BASE, tinted(P, TINT_ICE, False), tinted(NB, TINT_ICE, False), objs=OBJS + [PLAYER]))
json.dump(report, open(os.path.join(OUT, 'report.json'), 'w'), indent=1, ensure_ascii=False)
