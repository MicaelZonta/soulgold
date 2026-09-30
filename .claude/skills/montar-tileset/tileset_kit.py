#!/usr/bin/env python3
"""Kit para montar e verificar tilesets do SoulGold sem PIL (python puro).

Usado pelas skills `montar-tileset` e `prototipo-de-mapa`. Importe assim:

    import sys; sys.path.insert(0, '.claude/skills/montar-tileset')
    from tileset_kit import *

Tres partes:
  1. PNG / paletas / tilesets do repositorio (ler, desenhar metatile, renderizar)
  2. Autoria: canvas com "chaves de material" -> tiles 8x8 com UMA paleta cada,
     deduplicados com flip, metatiles de 24 bytes (triple layer)
  3. Escrita dos arquivos do tileset + verificacao lendo os arquivos escritos
     (do jeito que o jogo le, incluindo a paleta noturna do swapPalettes)

Numeros (confira em include/fieldmap.h): primario 640 tiles / paletas 0-6,
secundario 384 tiles / paletas 7-12 / tile id base 640, metatile = 12 entradas.
"""
import os, re, struct, zlib

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
NUM_TILES_IN_PRIMARY = 640
NUM_METATILES_IN_PRIMARY = 1024
NIGHT_TINT = (0.456, 0.456, 0.615)          # TINT_NIGHT em src/overworld.c

# =========================================================================== PNG
def read_png(path):
    """-> (w, h, mode, pixels, plte). mode 'P' = indices; 'RGB'/'RGBA' = tuplas."""
    d = open(path, 'rb').read(); p = 8; idat = b''; plte = None
    while p < len(d):
        n, t = struct.unpack('>I4s', d[p:p + 8]); c = d[p + 8:p + 8 + n]; p += 12 + n
        if t == b'IHDR': W, H, bd, ct = struct.unpack('>IIBB', c[:10])
        elif t == b'PLTE': plte = [tuple(c[i:i + 3]) for i in range(0, len(c), 3)]
        elif t == b'IDAT': idat += c
    raw = zlib.decompress(idat)
    ch = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}[ct]
    bits = bd * ch; st = (W * bits + 7) // 8; bpp = max(1, bits // 8)
    rows = []; prev = bytearray(st); i = 0
    for _ in range(H):
        f = raw[i]; line = bytearray(raw[i + 1:i + 1 + st]); i += 1 + st
        for x in range(st):
            a = line[x - bpp] if x >= bpp else 0; b = prev[x]; c = prev[x - bpp] if x >= bpp else 0
            if f == 1: line[x] = (line[x] + a) & 255
            elif f == 2: line[x] = (line[x] + b) & 255
            elif f == 3: line[x] = (line[x] + (a + b) // 2) & 255
            elif f == 4:
                pp = a + b - c; pa, pb, pc = abs(pp - a), abs(pp - b), abs(pp - c)
                line[x] = (line[x] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        rows.append(bytes(line)); prev = line
    if ct == 3:
        if bd == 8:
            return W, H, 'P', [list(r[:W]) for r in rows], plte
        if bd == 4:
            return W, H, 'P', [[(r[x >> 1] >> (4 if x % 2 == 0 else 0)) & 15 for x in range(W)] for r in rows], plte
        raise ValueError('PNG indexado com %d bits' % bd)
    return W, H, {2: 'RGB', 6: 'RGBA'}.get(ct, '?'), [[tuple(r[x * ch:x * ch + ch]) for x in range(W)] for r in rows], None

def _chunk(t, c):
    return struct.pack('>I', len(c)) + t + c + struct.pack('>I', zlib.crc32(t + c) & 0xffffffff)

def write_png(path, pix, scale=1):
    """pix: linhas de tuplas (r,g,b). scale inteiro amplia sem suavizar."""
    if scale > 1:
        pix = [[c for c in r for _ in range(scale)] for r in pix for _ in range(scale)]
    H, W = len(pix), len(pix[0])
    raw = bytearray()
    for r in pix:
        raw.append(0)
        for c in r: raw += bytes(c[:3])
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + _chunk(b'IHDR', struct.pack('>IIBBBBB', W, H, 8, 2, 0, 0, 0))
                           + _chunk(b'IDAT', zlib.compress(bytes(raw), 6)) + _chunk(b'IEND', b''))

def write_png_indexed4(path, idx, pal):
    """PNG indexado de 4 bits (o formato de tiles.png). idx: linhas de 0..15."""
    H, W = len(idx), len(idx[0])
    raw = bytearray()
    for r in idx:
        raw.append(0)
        for x in range(0, W, 2): raw.append((r[x] << 4) | r[x + 1])
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + _chunk(b'IHDR', struct.pack('>IIBBBBB', W, H, 4, 3, 0, 0, 0))
                           + _chunk(b'PLTE', b''.join(bytes(c) for c in pal))
                           + _chunk(b'IDAT', zlib.compress(bytes(raw), 6)) + _chunk(b'IEND', b''))

def crop(pix, x0, y0, x1, y1):
    return [r[x0:x1] for r in pix[y0:y1]]

# =========================================================================== paletas
def read_pal(path):
    L = open(path).read().split('\n')
    return [tuple(int(v) for v in l.split()) for l in L[3:3 + 16] if l.strip()]

def write_pal(path, cols):
    cols = list(cols) + [(0, 0, 0)] * (16 - len(cols))
    with open(path, 'w') as f:
        f.write('JASC-PAL\r\n0100\r\n16\r\n' + ''.join('%d %d %d\r\n' % tuple(c) for c in cols[:16]))

def rgb5(c):
    """Arredonda para o que o GBA mostra (5 bits por canal)."""
    return tuple((v >> 3) << 3 for v in c)

def night_file_for_slot(slot):
    """swapPalettes: o slot `slot` (7..12) mistura com a paleta (slot + 9) % 16 DO PROPRIO secundario.
    7->00, 8->01, 9->02, 10->03, 11->04, 12->05. (UpdateAltBgPalettes em src/overworld.c)"""
    return (slot + 9) % 16

def swap_mask(slots):
    """Valor de .swapPalettes para slots do secundario (7..12). Igual a OR de SWAP_PAL(s)."""
    return sum(1 << (s - 7) for s in slots)

# =========================================================================== tilesets do repo
def tileset_dir(sym):
    """gTileset_Johto_General -> ('primary', 'johto_general') lendo graphics.h."""
    g = open(os.path.join(ROOT, 'src/data/tilesets/graphics.h')).read()
    name = sym.replace('gTileset_', '')
    m = re.search(r'gTilesetTiles_' + re.escape(name) + r'\[\]\s*=\s*INCBIN_U32\("data/tilesets/(\w+)/(\w+)/', g)
    if not m:
        raise KeyError(sym)
    return m.group(1), m.group(2)

def load_tileset(kind, name=None, path=None):
    """Le tiles.png, palettes/NN.pal, metatiles.bin e attributes de um tileset.
    kind/name = pasta em data/tilesets; ou path = pasta qualquer (ex.: rascunho)."""
    base = path or os.path.join(ROOT, 'data/tilesets', kind, name)
    W, H, _, px, _ = read_png(os.path.join(base, 'tiles.png'))
    tiles = [[[px[ty * 8 + y][tx * 8 + x] & 15 for x in range(8)] for y in range(8)]
             for ty in range(H // 8) for tx in range(W // 8)]
    pals = {}
    for i in range(16):
        f = os.path.join(base, 'palettes', '%02d.pal' % i)
        if os.path.exists(f):
            pals[i] = read_pal(f)
    mt = open(os.path.join(base, 'metatiles.bin'), 'rb').read()
    metas = [struct.unpack('<12H', mt[i:i + 24]) for i in range(0, len(mt), 24)]
    af = os.path.join(base, 'metatile_attributes.bin')
    attrs = open(af, 'rb').read() if os.path.exists(af) else b''
    return dict(tiles=tiles, pals=pals, metas=metas, attrs=attrs, path=base)

EMPTY_SECONDARY = {'tiles': [], 'pals': {}, 'metas': [], 'attrs': b''}

def combine(prim, sec, night=0.0, swap=()):
    """VRAM como o jogo monta: tiles 0..639 do primario + os do secundario a partir de 640;
    paletas 0-6 do primario, 7-12 do secundario. `night` 0..1 mistura as paletas de `swap`
    com a versao noturna ((s+9)%16) — a mesma conta de UpdateAltBgPalettes."""
    tiles = prim['tiles'][:NUM_TILES_IN_PRIMARY]
    tiles = tiles + [[[0] * 8 for _ in range(8)]] * (NUM_TILES_IN_PRIMARY - len(tiles)) + sec['tiles']
    pals = [prim['pals'].get(i, [(0, 0, 0)] * 16) for i in range(7)]
    for s in range(7, 13):
        d = sec['pals'].get(s, [(0, 0, 0)] * 16)
        if s in swap and night:
            n = sec['pals'].get(night_file_for_slot(s), d)
            d = [tuple(int(d[i][c] * (1 - night) + n[i][c] * night) for c in range(3)) for i in range(16)]
        pals.append(d)
    return tiles, pals

def draw_meta(canvas, ox, oy, entries, tiles, pals, layers=(0, 1, 2)):
    """Desenha um metatile (12 entradas: bottom, middle, top) em canvas[y][x]."""
    for L in layers:
        for q in range(4):
            e = entries[L * 4 + q]
            tid = e & 0x3ff; hf = e >> 10 & 1; vf = e >> 11 & 1; pl = e >> 12
            if tid >= len(tiles):
                continue
            t = tiles[tid]; pal = pals[pl] if pl < 13 else pals[0]
            bx = ox + (q % 2) * 8; by = oy + (q // 2) * 8
            for y in range(8):
                row = t[7 - y if vf else y]
                for x in range(8):
                    c = row[7 - x if hf else x]
                    if c == 0 and L > 0:
                        continue
                    canvas[by + y][bx + x] = pal[c]

def metatile_entries(prim, sec, mid):
    return prim['metas'][mid] if mid < NUM_METATILES_IN_PRIMARY else sec['metas'][mid - NUM_METATILES_IN_PRIMARY]

def apply_night_tint(pix, amount=1.0):
    mul = [1 - amount * (1 - k) for k in NIGHT_TINT]
    return [[(int(c[0] * mul[0]), int(c[1] * mul[1]), int(c[2] * mul[2])) for c in r] for r in pix]

def render_metatile_sheet(prim, sec, ids, cols=8, night=0.0, swap=()):
    tiles, pals = combine(prim, sec, night, swap)
    rows = (len(ids) + cols - 1) // cols
    cv = [[(255, 0, 255)] * (cols * 16) for _ in range(rows * 16)]
    for n, mid in enumerate(ids):
        draw_meta(cv, (n % cols) * 16, (n // cols) * 16, metatile_entries(prim, sec, mid), tiles, pals)
    return cv

_FONT = {'0': '111101101101111', '1': '010110010010111', '2': '111001111100111', '3': '111001111001111',
         '4': '101101111001001', '5': '111100111001111', '6': '111100111101111', '7': '111001001001001',
         '8': '111101111101111', '9': '111101111001111'}

def labeled_sheet(prim, sec, ids, cols=12):
    """Folha com o numero de cada metatile embaixo — para escolher pecas no olho."""
    tiles, pals = combine(prim, sec)
    cell = 24; rows = (len(ids) + cols - 1) // cols
    cv = [[(40, 40, 40)] * (cols * cell) for _ in range(rows * cell)]
    for n, mid in enumerate(ids):
        x = (n % cols) * cell; y = (n // cols) * cell
        draw_meta(cv, x + 4, y + 1, metatile_entries(prim, sec, mid), tiles, pals)
        for i, ch in enumerate(str(mid)):
            b = _FONT[ch]
            for yy in range(5):
                for xx in range(4):
                    on = xx < 3 and b[yy * 3 + xx] == '1'
                    cv[y + 18 + yy][x + 1 + i * 4 + xx] = (255, 255, 255) if on else (0, 0, 0)
    return cv

# =========================================================================== autoria
class Canvas:
    """Desenho em pixels com CHAVES de material ('s1', 'w2', 'out'...), nao cores.
    A cor so existe na paleta; e isso que permite a mesma arte trocar de cor
    (dia/noite) e cada tile 8x8 escolher a paleta que contem todas as suas chaves."""
    def __init__(self, w, h):
        self.w, self.h = w, h
        self.px = [[None] * w for _ in range(h)]
    def put(self, x, y, k):
        if 0 <= x < self.w and 0 <= y < self.h:
            self.px[y][x] = k
    def get(self, x, y):
        return self.px[y][x] if 0 <= x < self.w and 0 <= y < self.h else None
    def rect(self, x0, y0, x1, y1, k):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                self.put(x, y, k)
    def hline(self, x0, x1, y, k):
        for x in range(x0, x1 + 1): self.put(x, y, k)
    def vline(self, x, y0, y1, k):
        for y in range(y0, y1 + 1): self.put(x, y, k)
    def mirror_x(self):
        """Copia a metade esquerda para a direita. Com largura multipla de 16 o eixo cai
        numa borda de tile, e os tiles da direita viram flips gratis dos da esquerda."""
        for y in range(self.h):
            for x in range(self.w // 2):
                self.px[y][self.w - 1 - x] = self.px[y][x]
    def copy(self):
        c = Canvas(self.w, self.h); c.px = [r[:] for r in self.px]; return c

def noise(x):
    """Ruido deterministico (mesma arte a cada execucao)."""
    x = (x * 374761393) & 0xffffffff
    x = (x ^ (x >> 13)) * 1274126177 & 0xffffffff
    return x ^ (x >> 16)

class PaletteSet:
    """slots: {7: ['out', 's0', ...]} -> a chave na posicao i vira o indice i+1 (0 = transparente).
    colors: {'s0': ((r,g,b) dia, (r,g,b) noite ou None)}.
    order: ordem em que um tile tenta as paletas (a primeira que contem todas as chaves)."""
    def __init__(self, slots, colors, order=None, swap=()):
        for s, keys in slots.items():
            assert 7 <= s <= 12, 'secundario so enxerga as paletas 7..12'
            assert len(keys) <= 15, 'paleta %d tem %d cores (max 15 + transparente)' % (s, len(keys))
            for k in keys:
                assert k in colors, 'chave %r sem cor' % k
        self.slots, self.colors = slots, colors
        self.order = order or sorted(slots)
        self.swap = list(swap)
    def slot_for(self, keys):
        keys = set(keys) - {None}
        if not keys:
            return None
        for s in self.order:
            if keys <= set(self.slots[s]):
                return s
        return -1
    def colors_of(self, slot, night=False):
        cols = [(255, 0, 255)] + [(0, 0, 0)] * 15
        for i, k in enumerate(self.slots.get(slot, [])):
            d, n = self.colors[k]
            cols[i + 1] = rgb5(n if (night and n) else d)
        return cols

def cut_tiles(canvas, palset):
    """-> ({(tx,ty): (slot, tile8x8)}, conflitos). Conflito = tile cujas chaves nao cabem em
    nenhuma paleta sozinha: mude o desenho (alinhe o elemento a grade 8x8) ou a paleta."""
    res, bad = {}, []
    for ty in range(canvas.h // 8):
        for tx in range(canvas.w // 8):
            keys = [canvas.px[ty * 8 + y][tx * 8 + x] for y in range(8) for x in range(8)]
            slot = palset.slot_for(keys)
            if slot is None:
                continue
            if slot == -1:
                bad.append((tx, ty, sorted(set(keys) - {None})))
                continue
            order = palset.slots[slot]
            res[(tx, ty)] = (slot, tuple(tuple((order.index(canvas.px[ty * 8 + y][tx * 8 + x]) + 1)
                                               if canvas.px[ty * 8 + y][tx * 8 + x] else 0
                                               for x in range(8)) for y in range(8)))
    return res, bad

def flips(t):
    return [(t, 0, 0), (tuple(tuple(r[::-1]) for r in t), 1, 0),
            (tuple(t[::-1]), 0, 1), (tuple(tuple(r[::-1]) for r in t[::-1]), 1, 1)]

class TileBank:
    """Tiles unicos do secundario; tile 0 e vazio. Reaproveita flips H/V."""
    def __init__(self):
        blank = tuple(tuple([0] * 8) for _ in range(8))
        self.tiles = [blank]
        self.lookup = {blank: (0, 0, 0)}
    def add(self, t):
        for v, hf, vf in flips(t):
            if v in self.lookup:
                i, h0, v0 = self.lookup[v]
                return i, hf ^ h0, vf ^ v0
        self.tiles.append(t)
        self.lookup[t] = (len(self.tiles) - 1, 0, 0)
        return len(self.tiles) - 1, 0, 0

def entry(tile_id, hflip, vflip, pal):
    """Uma entrada de metatile: bits 0-9 tile, 10 hflip, 11 vflip, 12-15 paleta."""
    return (tile_id & 0x3ff) | (hflip << 10) | (vflip << 11) | (pal << 12)

def primary_ref(prim, metatile_id, remap):
    """Copia as 12 entradas de um metatile do PRIMARIO trocando paletas (ex.: {1: 8}).
    Os tiles continuam os do primario (custo zero no secundario); so a cor muda.
    O slot novo precisa ter, nos MESMOS indices, as cores que os tiles usam."""
    return [((e & 0x0fff) | (remap.get(e >> 12, e >> 12) << 12)) if e else 0 for e in prim['metas'][metatile_id]]

def used_color_indices(prim, metatile_ids):
    """Indices de cor que os tiles desses metatiles do primario realmente usam."""
    used = set()
    for m in metatile_ids:
        for e in prim['metas'][m]:
            if e:
                for r in prim['tiles'][e & 0x3ff]:
                    used.update(r)
    return sorted(used)

def build_cells(tiles_map, bank, cols, rows, base=None, top=frozenset(), ground=None, metas=None):
    """Transforma os tiles cortados em metatiles, celula de 16x16 por celula.
      base(c, r)  -> 12 entradas de um metatile por baixo (ex.: primary_ref de rocha) ou None
      top         -> celulas cujo desenho vai para a camada de CIMA (cobre sprites!) por
                     cima de uma base que ja usa bottom+middle
      ground      -> 4 entradas para a camada de baixo quando o desenho tem transparencia
                     e nao ha base (ex.: grama do primario: prim['metas'][1][4:8])
      metas       -> lista existente para acumular (varios estados no mesmo tileset)
    -> (lista de metatiles, {(c, r): indice ou None})"""
    metas = [] if metas is None else metas
    grid = {}
    for r in range(rows):
        for c in range(cols):
            quads, any_px, transparent = [], False, False
            for q in range(4):
                tx, ty = c * 2 + q % 2, r * 2 + q // 2
                if (tx, ty) in tiles_map:
                    any_px = True
                    slot, t = tiles_map[(tx, ty)]
                    transparent |= any(0 in row for row in t)
                    i, hf, vf = bank.add(t)
                    quads.append(entry(NUM_TILES_IN_PRIMARY + i, hf, vf, slot))
                else:
                    transparent = True
                    quads.append(0)
            b = base(c, r) if base else None
            if not any_px:
                m = tuple(b) if b is not None else None
            elif b is not None and transparent:
                if (c, r) not in top:
                    raise ValueError('celula %s desenha por cima de uma base mas nao esta em `top`' % ((c, r),))
                m = tuple(list(b[:8]) + quads)
            else:
                m = tuple((list(ground) if (transparent and ground) else [0] * 4) + quads + [0] * 4)
            if m is None:
                grid[(c, r)] = None
                continue
            if m not in metas:
                metas.append(m)
            grid[(c, r)] = metas.index(m)
    return metas, grid

def write_tileset(folder, bank, metas, palset, attrs=None, preview_slot=None):
    """Escreve tiles.png (indexado 4 bits, 128 px), palettes/00..12.pal, metatiles.bin e
    metatile_attributes.bin. As paletas 00..05 recebem a versao NOTURNA dos slots em
    palset.swap (slot s -> arquivo (s+9)%16); as outras 00..06 ficam pretas (ignoradas)."""
    os.makedirs(os.path.join(folder, 'palettes'), exist_ok=True)
    assert len(bank.tiles) <= 384, 'secundario passou de 384 tiles (%d)' % len(bank.tiles)
    for i in range(13):
        cols = [(0, 0, 0)] * 16
        if 7 <= i <= 12 and i in palset.slots:
            cols = palset.colors_of(i)
        for s in palset.swap:
            if night_file_for_slot(s) == i:
                cols = palset.colors_of(s, night=True)
        write_pal(os.path.join(folder, 'palettes', '%02d.pal' % i), cols)
    rows = (len(bank.tiles) + 15) // 16
    idx = [[0] * 128 for _ in range(rows * 8)]
    for n, t in enumerate(bank.tiles):
        for y in range(8):
            for x in range(8):
                idx[(n // 16) * 8 + y][(n % 16) * 8 + x] = t[y][x]
    write_png_indexed4(os.path.join(folder, 'tiles.png'), idx, palset.colors_of(preview_slot or palset.order[0]))
    with open(os.path.join(folder, 'metatiles.bin'), 'wb') as f:
        for m in metas:
            f.write(struct.pack('<12H', *m))
    with open(os.path.join(folder, 'metatile_attributes.bin'), 'wb') as f:
        for i in range(len(metas)):
            f.write(struct.pack('<H', (attrs or {}).get(i, 0)))

def colored_tile_sheet(bank, tiles_maps, palset, night=False):
    """Folha dos tiles unicos, cada um com a paleta que usa (a folha 'legivel' do tiles.png)."""
    use = {}
    for tm in tiles_maps:
        for (s, t) in tm.values():
            for v, _, _ in flips(t):
                if v in bank.lookup:
                    use.setdefault(bank.lookup[v][0], s)
                    break
    rows = (len(bank.tiles) + 15) // 16
    cv = [[(255, 0, 255)] * 128 for _ in range(rows * 8)]
    for n, t in enumerate(bank.tiles):
        pal = palset.colors_of(use.get(n, palset.order[0]), night)
        for y in range(8):
            for x in range(8):
                if t[y][x]:
                    cv[(n // 16) * 8 + y][(n % 16) * 8 + x] = pal[t[y][x]]
    return cv
