#!/usr/bin/env python3
"""Kit para prototipar mapas do SoulGold: compor map.bin, aprender bordas dos mapas
existentes, renderizar dia/noite/colisao e desenhar os NPCs com o sprite real.

    import sys; sys.path.insert(0, '.claude/skills/prototipo-de-mapa')
    from mapa_kit import *

Depende de ../montar-tileset/tileset_kit.py (PNG, paletas, draw_meta).
Formato de uma celula do map.bin (include/global.fieldmap.h): bits 0-10 metatile,
bit 11 colisao, bits 12-15 elevacao. Metatile >= 1024 e do secundario.
Elevacao usada em Johto: 3 = chao, 1 = agua (surf). Veja OlivineCity_PortOutside.
"""
import collections, json, os, re, struct, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'montar-tileset'))
from tileset_kit import *            # noqa: F401,F403

# =========================================================================== layouts
def layout_info(name):
    """name = 'SunMoonAltar' ou 'SunMoonAltar_Layout' -> entrada de layouts.json."""
    want = name if name.endswith('_Layout') else name + '_Layout'
    for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts']:
        if l.get('name') == want:
            return l
    raise KeyError(want)

def read_blocks(path):
    d = open(path, 'rb').read()
    return [struct.unpack('<H', d[i:i + 2])[0] for i in range(0, len(d), 2)]

def pack_block(metatile, collision=0, elevation=3):
    return (metatile & 0x7ff) | ((collision & 1) << 11) | ((elevation & 0xf) << 12)

def write_blocks(path, grid):
    """grid[y][x] = valor ja empacotado (pack_block)."""
    with open(path, 'wb') as f:
        for row in grid:
            for v in row:
                f.write(struct.pack('<H', v))

def load_layout(name):
    """-> dict(w, h, blocks, prim, sec) com os tilesets carregados."""
    L = layout_info(name)
    pk, pn = tileset_dir(L['primary_tileset'])
    sk, sn = tileset_dir(L['secondary_tileset'])
    return dict(w=L['width'], h=L['height'], blocks=read_blocks(os.path.join(ROOT, L['blockdata_filepath'])),
                prim=load_tileset(pk, pn), sec=load_tileset(sk, sn), info=L)

# =========================================================================== classificar e aprender bordas
def classify_color(c):
    """Classe grosseira de um pixel: W agua, S areia, G grama, x resto. Ajuste se precisar."""
    r, g, b = c
    if b > r + 30 and b > g - 10: return 'W'
    if r > 180 and g > 170 and b < 170: return 'S'
    if g > r + 20 and g > b: return 'G'
    return 'x'

class MetatileClasses:
    """Fracao de cada classe de pixel por metatile do primario (cacheado)."""
    def __init__(self, prim):
        self.prim = prim
        self.tiles, self.pals = combine(prim, EMPTY_SECONDARY)
        self.cache = {}
    def comp(self, mid):
        if mid >= NUM_METATILES_IN_PRIMARY or mid >= len(self.prim['metas']):
            return {'x': 1.0}
        if mid not in self.cache:
            cv = [[(0, 0, 0)] * 16 for _ in range(16)]
            draw_meta(cv, 0, 0, self.prim['metas'][mid], self.tiles, self.pals)
            c = collections.Counter(classify_color(cv[y][x]) for y in range(16) for x in range(16))
            self.cache[mid] = {k: v / 256 for k, v in c.items()}
        return self.cache[mid]

NB8 = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]

def learn_edges(maps, classes, inner, outer, inner_min=0.3, outer_min=0.9):
    """Aprende qual metatile os mapeadores puseram em cada vizinhanca.
    Para cada celula que tem `inner` (ex.: 'S' areia) mas nao e pura, marca quais dos 8
    vizinhos sao `outer` puros (ex.: 'W' agua) -> assinatura '11100000' (NO N NE O L SO S SE).
    -> {assinatura: Counter(metatile)}. Use o mais comum de cada assinatura."""
    rules = collections.defaultdict(collections.Counter)
    for m in maps:
        L = layout_info(m); W, H = L['width'], L['height']
        ids = [v & 0x7ff for v in read_blocks(os.path.join(ROOT, L['blockdata_filepath']))]
        for y in range(1, H - 1):
            for x in range(1, W - 1):
                v = ids[y * W + x]
                c = classes.comp(v)
                if v >= NUM_METATILES_IN_PRIMARY or c.get(inner, 0) < inner_min or c.get(inner, 0) >= 0.97:
                    continue
                sig = ''.join('1' if classes.comp(ids[(y + dy) * W + x + dx]).get(outer, 0) >= outer_min else '0'
                              for dx, dy in NB8)
                if '1' in sig:
                    rules[sig][v] += 1
    return rules

def neighbours_of(maps, target, dx, dy):
    """O que os mapeadores poem na posicao (dx,dy) relativa ao metatile `target`.
    Ex.: neighbours_of(maps, 105, -1, 0) acha a ponta esquerda da borda de tras da rocha."""
    c = collections.Counter()
    for m in maps:
        L = layout_info(m); W, H = L['width'], L['height']
        ids = [v & 0x7ff for v in read_blocks(os.path.join(ROOT, L['blockdata_filepath']))]
        for y in range(H):
            for x in range(W):
                if ids[y * W + x] == target and 0 <= x + dx < W and 0 <= y + dy < H:
                    c[ids[(y + dy) * W + x + dx]] += 1
    return c

def maps_using(primary_symbol):
    """Layouts do repositorio com esse primario e map.bin existente (fonte para aprender)."""
    out = []
    for l in json.load(open(os.path.join(ROOT, 'data/layouts/layouts.json')))['layouts']:
        if l.get('primary_tileset') == primary_symbol and os.path.exists(os.path.join(ROOT, l.get('blockdata_filepath', '-'))):
            out.append(l['name'][:-len('_Layout')])
    return out

# =========================================================================== pecas do johto_general
# Aprendidas com learn_edges/neighbours_of sobre Route41, CianwoodCity, OlivineCity, Route40
# e as rotas de Johto. Nao ha canto concavo de areia com agua: faca costa convexa.
JOHTO = {
    'water': 299, 'sand': 277, 'grass': 1, 'flowers': 4,
    # areia com agua do lado indicado
    'sand_water': {'N': 269, 'S': 285, 'W': 276, 'E': 278, 'NW': 268, 'NE': 270, 'SW': 284, 'SE': 286},
    # areia com grama do lado indicado (a borda e desenhada na celula de areia) e os cantos
    # (areia com grama em dois lados): 211 NO, 213 NE, 227 SO, 229 SE
    'sand_grass': {'N': 212, 'S': 228, 'W': 219, 'E': 221, 'NW': 211, 'NE': 213, 'SW': 227, 'SE': 229},
    # arvores em coluna de 2 de largura, com FASE presa ao topo da coluna:
    # topo 14|15, corpo alternando (26|27, 18|19) na borda ou (654|655, 646|647) quando ha arvore
    # do lado, fim 30|31, e a base 36|37 vai na celula de GRAMA logo abaixo (bloqueada)
    'tree': {'top': (14, 15), 'odd_edge': (26, 27), 'even_edge': (18, 19), 'odd_in': (654, 655),
             'even_in': (646, 647), 'last': (30, 31), 'base': (36, 37)},
    # floresta antiga (blocos): mantida por compatibilidade; prefira 'tree'
    'forest': {'A': (646, 647), 'B': (654, 655), 'top': (26, 27), 'bottom': (36, 37),
               'left': (18, 26), 'right': (19, 27)},
    'pier': (453, 454, 455),                       # cais vertical de 3 colunas
    'sea_rock_2x2': (459, 460, 467, 468),
    # montanha: degraus internos e fechamento externo sobre grama
    'rock': {'top': 113, 'face': 124, 'step_left': 115, 'step_right': 117,
             'face_left': 123, 'face_right': 125,
             'rim': (104, 105, 106), 'side_left': 112, 'side_right': 114,
             'base_left': 120, 'base': 121, 'base_right': 122,
             # borda de tras de CADA plato, conforme o que ha atras dele:
             'rim_on_grass': (104, 105, 106), 'rim_on_rock': (107, 108, 109), 'rim_on_sand': (152, 108, 154)},
}

def pick_sand(T, x, y, W='W', grassy=('G', 'F')):
    """Metatile de areia para a celula (x,y) do mapa de classes T (lista de strings/listas)."""
    H, Wd = len(T), len(T[0])
    def is_(xx, yy, cls):
        return (not (0 <= xx < Wd and 0 <= yy < H)) and W in cls or (0 <= xx < Wd and 0 <= yy < H and T[yy][xx] in cls)
    n, s, w, e = is_(x, y - 1, (W,)), is_(x, y + 1, (W,)), is_(x - 1, y, (W,)), is_(x + 1, y, (W,))
    sw = JOHTO['sand_water']
    for cond, k in ((n and w, 'NW'), (n and e, 'NE'), (s and w, 'SW'), (s and e, 'SE'),
                    (n, 'N'), (s, 'S'), (w, 'W'), (e, 'E')):
        if cond:
            return sw[k]
    n, s, w, e = is_(x, y - 1, grassy), is_(x, y + 1, grassy), is_(x - 1, y, grassy), is_(x + 1, y, grassy)
    sg = JOHTO['sand_grass']
    for cond, k in ((n and w, 'NW'), (n and e, 'NE'), (s and w, 'SW'), (s and e, 'SE'),
                    (n, 'N'), (s, 'S'), (w, 'W'), (e, 'E')):
        if cond:
            return sg[k]
    return JOHTO['sand']

def pick_forest(T, x, y, F='F'):
    """Arvores em colunas (JOHTO['tree']). A fase vem do TOPO da coluna e o lado (metade
    esquerda/direita da arvore) vem do inicio da faixa horizontal: nunca da paridade global."""
    t = JOHTO['tree']
    H, Wd = len(T), len(T[0])
    inF = lambda xx, yy: 0 <= xx < Wd and 0 <= yy < H and T[yy][xx] == F
    top = y
    while inF(x, top - 1):
        top -= 1
    start = x
    while inF(start - 1, y):
        start -= 1
    half = (x - start) % 2                        # 0 = metade esquerda, 1 = direita
    k = y - top
    if k == 0:
        return t['top'][half]
    if not inF(x, y + 1):
        return t['last'][half]
    inner = inF(x + 1, y) if half else inF(x - 1, y)
    if k % 2:
        return (t['odd_in'] if inner else t['odd_edge'])[half]
    return (t['even_in'] if inner else t['even_edge'])[half]

def tree_base(T, x, y, F='F'):
    """Celula de grama logo abaixo de uma coluna de arvores recebe a base (36|37), bloqueada."""
    H, Wd = len(T), len(T[0])
    if not (0 < y < H and T[y - 1][x] == F and T[y][x] != F):
        return None
    start = x
    while 0 <= start - 1 and T[y - 1][start - 1] == F:
        start -= 1
    return JOHTO['tree']['base'][(x - start) % 2]

# =========================================================================== sprites de NPC
_GFX_CACHE = {}
def _gfx_tables():
    if _GFX_CACHE:
        return _GFX_CACHE
    rd = lambda p: open(os.path.join(ROOT, p)).read()
    ptr = dict(re.findall(r'\[(OBJ_EVENT_GFX_\w+)\]\s*=\s*&(gObjectEventGraphicsInfo_\w+)',
                          rd('src/data/object_events/object_event_graphics_info_pointers.h')))
    info = {}
    for name, body in re.findall(r'const struct ObjectEventGraphicsInfo (gObjectEventGraphicsInfo_\w+)\s*=\s*\{(.*?)\};',
                                 rd('src/data/object_events/object_event_graphics_info.h'), re.S):
        g = lambda k: (re.search(r'\.' + k + r'\s*=\s*([^,\n]+)', body) or [None, None])[1]
        if '.width' in body:                                  # inicializador com nomes (.width = ...)
            info[name] = dict(w=int(g('width') or 16), h=int(g('height') or 32), images=(g('images') or '').strip())
        else:                                            # posicional: tileTag, pal, refl, size, width, height, ...
            parts = [t.strip() for t in body.split(',')]
            pic = next((t for t in parts if t.startswith('sPicTable_')), None)
            info[name] = dict(w=int(parts[4]), h=int(parts[5]), images=pic)
    pics = {}
    for tab, body in re.findall(r'(sPicTable_\w+)\[\]\s*=\s*\{(.*?)\};', rd('src/data/object_events/object_event_pic_tables.h'), re.S):
        m = re.search(r'\((gObjectEventPic_\w+)', body)
        if m:
            pics[tab] = m.group(1)
    files = dict(re.findall(r'(gObjectEventPic_\w+)\[\]\s*=\s*INCBIN_U\d+\("([^"]+)\.4bpp', rd('src/data/object_events/object_event_graphics.h')))
    _GFX_CACHE.update(ptr=ptr, info=info, pics=pics, files=files)
    return _GFX_CACHE

def sprite_for(graphics_id):
    """OBJ_EVENT_GFX_X -> (png, frame_w, frame_h, paleta) ou None.
    OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA) -> graphics/pokemon/ninetales/alola/overworld.png."""
    m = re.match(r'OBJ_EVENT_GFX_SPECIES\((\w+)\)', graphics_id)
    if m:
        parts = m.group(1).lower().split('_')
        for k in range(len(parts), 0, -1):
            d = os.path.join(ROOT, 'graphics/pokemon', '_'.join(parts[:k]), *parts[k:])
            if os.path.exists(os.path.join(d, 'overworld.png')):
                pal = os.path.join(d, 'overworld_normal.pal')
                png = os.path.join(d, 'overworld.png')
                side = read_png(png)[1]          # quadros quadrados: 32x32 ou 64x64 (Kyogre, Lugia)
                return png, side, side, read_pal(pal) if os.path.exists(pal) else None
        return None
    t = _gfx_tables()
    inf = t['info'].get(t['ptr'].get(graphics_id, ''))
    if not inf:
        return None
    base = t['files'].get(t['pics'].get(inf['images'], ''))
    if not base:
        return None
    return os.path.join(ROOT, base + '.png'), inf['w'], inf['h'], None

FACING_FRAME = {'MOVEMENT_TYPE_FACE_DOWN': (0, False), 'MOVEMENT_TYPE_FACE_UP': (1, False),
                'MOVEMENT_TYPE_FACE_LEFT': (2, False), 'MOVEMENT_TYPE_FACE_RIGHT': (2, True)}

def draw_object(canvas, obj, night=False):
    """obj = entrada de object_events do map.json (graphics_id, x, y, movement_type).
    Posicao: sprite centralizado na celula, com o pe na base dela."""
    s = sprite_for(obj['graphics_id'])
    if not s:
        return False
    path, fw, fh, pal = s
    Wp, Hp, _, px, plte = read_png(path)
    pal = pal or plte
    frame, flip = FACING_FRAME.get(obj.get('movement_type'), (0, False))
    if Wp < fw * (frame + 1):
        frame, flip = 0, False
    ox, oy = obj['x'] * 16 + 8 - fw // 2, obj['y'] * 16 + 16 - fh
    for yy in range(min(fh, Hp)):
        for xx in range(fw):
            v = px[yy][frame * fw + (fw - 1 - xx if flip else xx)]
            if not v:
                continue
            c = pal[v % len(pal)]
            if night:
                c = tuple(int(c[k] * NIGHT_TINT[k]) for k in range(3))
            X, Y = ox + xx, oy + yy
            if 0 <= X < len(canvas[0]) and 0 <= Y < len(canvas):
                canvas[Y][X] = c
    return True

# =========================================================================== render de mapa
def render_blocks(blocks, w, h, prim, sec, night=0.0, swap=(), objects=(), overlay=False, marks=()):
    """blocks = lista w*h de valores do map.bin. night 0..1 usa a mistura do swapPalettes E o
    TINT_NIGHT do DNS. overlay pinta bloqueio (vermelho) e agua (azul). marks = [((x,y), cor)]."""
    tiles, pals = combine(prim, sec, night, swap)
    cv = [[(0, 0, 0)] * (w * 16) for _ in range(h * 16)]
    for i, v in enumerate(blocks):
        draw_meta(cv, (i % w) * 16, (i // w) * 16, metatile_entries(prim, sec, v & 0x7ff), tiles, pals)
    if night:
        cv = apply_night_tint(cv, night)
    if overlay:
        for i, v in enumerate(blocks):
            coll, elev = v >> 11 & 1, v >> 12
            if coll or elev == 1:
                tint, a = ((220, 40, 40), .38) if coll else ((40, 120, 255), .18)
                for yy in range(16):
                    for xx in range(16):
                        X, Y = (i % w) * 16 + xx, (i // w) * 16 + yy
                        c = cv[Y][X]
                        cv[Y][X] = tuple(int(c[k] * (1 - a) + tint[k] * a) for k in range(3))
    for (mx, my), col in marks:
        for i in range(16):
            for p in (0, 1, 14, 15):
                cv[my * 16 + p][mx * 16 + i] = col
                cv[my * 16 + i][mx * 16 + p] = col
    for o in sorted(objects, key=lambda o: o['y']):
        draw_object(cv, o, night > 0.5)
    return cv

def swap_slots(tileset_symbol):
    """Slots com versao noturna declarados em headers.h (.swapPalettes), resolvendo #define."""
    hdr = open(os.path.join(ROOT, 'src/data/tilesets/headers.h')).read()
    m = re.search(r'const struct Tileset ' + re.escape(tileset_symbol) + r'\s*=\s*\{(.*?)\};', hdr, re.S)
    if not m:
        return []
    v = re.search(r'^\s*\.swapPalettes\s*=\s*([^,]+),', m.group(1), re.M)
    if not v:
        return []
    expr = v.group(1)
    d = re.search(r'#define\s+' + re.escape(expr.strip()) + r'\s+(.+)', hdr)
    if d:
        expr = d.group(1)
    return [int(n) for n in re.findall(r'SWAP_PAL\((\d+)\)', expr)]

def render_repo_map(map_name, **kw):
    """Renderiza um mapa do repositorio como esta (map.bin + map.json + tilesets)."""
    L = load_layout(map_name)
    m = json.load(open(os.path.join(ROOT, 'data/maps', map_name, 'map.json')))
    swap = kw.pop('swap', None)
    if swap is None:
        swap = swap_slots(L['info']['primary_tileset']) + swap_slots(L['info']['secondary_tileset'])
    return render_blocks(L['blocks'], L['w'], L['h'], L['prim'], L['sec'], swap=swap,
                         objects=kw.pop('objects', m.get('object_events', [])), **kw)

def check_objects(blocks, w, objects):
    """Lista NPCs em cima de bloqueio ou de agua (erro que nao aparece no build)."""
    bad = []
    for o in objects:
        v = blocks[o['y'] * w + o['x']]
        if (v >> 11 & 1) and o.get('elevation', 3) != 1:
            bad.append((o.get('local_id'), o['x'], o['y'], 'bloqueado'))
        elif (v >> 12) == 1 and o.get('elevation', 3) != 1:
            bad.append((o.get('local_id'), o['x'], o['y'], 'agua'))
    return bad

if __name__ == '__main__':
    # uso rapido: python3 mapa_kit.py NomeDoMapa saida.png [--noite] [--colisao]
    name, out = sys.argv[1], sys.argv[2]
    night = 1.0 if '--noite' in sys.argv else 0.0
    write_png(out, render_repo_map(name, night=night, overlay='--colisao' in sys.argv), 2)
    print('ok', out)
