"""Arte do Navel Rock: planta (grids.py) -> imagem RGB em pixels de GBA.

Terreno desenhado por regra (so depende da celula e das 8 vizinhas, para o
dedup do tileset funcionar), objetos carimbados da folha 2.png reduzida.
Roda no Python do Windows (numpy/scipy/PIL)."""
import sys, os, numpy as np
from PIL import Image
from scipy import ndimage

C = 16
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from grids import MAPS

ROCK = [(58, 25, 31), (90, 36, 44), (116, 48, 56), (139, 61, 67), (163, 79, 82), (187, 109, 106), (215, 141, 134)]
SAND = [(196, 149, 85), (216, 184, 138), (228, 199, 151), (239, 213, 165), (245, 225, 184)]
WET = (205, 160, 104)
BLUE = [(16, 52, 128), (14, 97, 199), (18, 131, 236), (62, 158, 237), (130, 193, 240), (230, 244, 252)]
TURQ = [(25, 140, 160), (27, 187, 198), (53, 207, 209), (99, 229, 223), (160, 240, 236), (235, 252, 252)]
TURQ_RIM = (214, 146, 84)
GRASS = [(32, 95, 53), (50, 130, 68), (78, 154, 73), (110, 178, 79), (150, 200, 86)]
FLOWER = [(250, 214, 80), (236, 120, 70)]
VOID = (16, 12, 14)

SOLID_ROCK = set('#WXYC:R')      # celulas desenhadas como rocha
WATER_B = set('~bHK')
WATER_T = set('=BG')

def noise(*a):
    x = 0
    for v in a:
        x = (x * 1000003 + int(v) + 0x9e3779b9) & 0xffffffff
    x = (x ^ (x >> 15)) * 0x2c1b3c6d & 0xffffffff
    x = (x ^ (x >> 12)) * 0x297a2d39 & 0xffffffff
    return (x ^ (x >> 15)) & 0xffffffff

# ---------------------------------------------------------------- texturas 16x16 periodicas
TP = 32   # periodo da textura do topo da rocha

def boulder_texture():
    """Topo da rocha: pedras arredondadas de tamanhos variados (periodo TP), luz de cima-esquerda."""
    T = np.zeros((TP, TP, 3), np.uint8)
    blobs = [(5, 5, 7.0), (17, 3, 6.0), (27, 7, 7.5), (11, 15, 8.0), (24, 19, 7.0), (3, 23, 7.5),
             (15, 28, 6.5), (29, 29, 6.0), (8, 31, 5.0), (20, 11, 4.5), (32, 16, 5.5), (0, 14, 5.0)]
    for y in range(TP):
        for x in range(TP):
            best = None
            for (bx, by, r) in blobs:
                for ox in (-TP, 0, TP):
                    for oy in (-TP, 0, TP):
                        dx, dy = x + .5 - (bx + ox), y + .5 - (by + oy)
                        d2 = (dx * dx + dy * dy) / (r * r)
                        if d2 < 1:
                            h = (by + oy) * 1.0 - d2 * 4
                            if best is None or h > best[0]:
                                best = (h, dx / r, dy / r, d2)
            if best is None:
                lv = 1
            else:
                h, nx, ny, d2 = best
                light = -0.75 * nx - 0.85 * ny
                if d2 > 0.85: lv = 0 if ny > 0.1 else 1
                elif light > 0.9: lv = 6
                elif light > 0.5: lv = 5
                elif light > 0.0: lv = 4
                elif light > -0.5: lv = 3
                else: lv = 2
            T[y, x] = ROCK[lv]
    return T

FACE_H = 11
def face_texture():
    """Face sul do penhasco: colunas verticais (periodo 16 em x), indice [h, x], h = distancia ao pe."""
    F = np.zeros((FACE_H + 3, 16, 3), np.uint8)
    cols = [0, 5, 9, 13]          # x de inicio de cada coluna
    for h in range(FACE_H + 3):
        for x in range(16):
            s = max(c for c in cols if c <= x); w = ([c for c in cols if c > x] + [16])[0] - s
            u = (x - s) / max(w - 1, 1)
            lv = 4 if u < 0.25 else 3 if u < 0.6 else 2 if u < 0.85 else 1
            if x == s: lv = 1
            if h <= 1: lv = max(lv - 1, 1)
            if h >= FACE_H - 1: lv = min(lv + 1, 5)
            F[h, x] = ROCK[lv]
    return F

BT, FT = boulder_texture(), face_texture()

def sand_px(x, y, variant):
    n = noise(x % 16, y % 16, variant) % 100
    if n < 4: return SAND[0]
    if n < 14: return SAND[1]
    if n < 22: return SAND[3]
    if n < 24: return SAND[4]
    return SAND[2]

def grass_px(x, y):
    n = noise(x % 16, y % 16, 7) % 100
    if n < 3: return FLOWER[(x // 3 + y) % 2]
    if n < 15: return GRASS[2]
    if n < 30: return GRASS[4]
    return GRASS[3]

def water_px(x, y, ramp):
    # ondinhas: tracos horizontais claros, periodo 16
    x, y = x % 16, y % 16
    k = noise(x // 4, y, 3) % 100
    if (y % 8 == 3 and k < 35) or (y % 8 == 6 and (x + 4) % 16 < 3): return ramp[3]
    return ramp[2] if (y // 2 + x // 4) % 4 else ramp[1]

# ---------------------------------------------------------------- forma suave por celula
def shaped(mask_cells, r=5):
    """Mascara de pixel a partir da grade, cantos arredondados. Borda da grade = replicada."""
    pad = np.pad(mask_cells, 1, mode='edge')
    m = np.kron(pad, np.ones((C, C), bool))
    disk = np.hypot(*np.mgrid[-r:r + 1, -r:r + 1]) <= r
    m = ndimage.binary_closing(np.pad(m, r, mode='edge'), disk)[r:-r, r:-r]
    m = ndimage.binary_opening(np.pad(m, r, mode='edge'), disk)[r:-r, r:-r]
    return m[C:-C, C:-C]

def lumpy(m, amp=2, seed=1):
    """Calombos na borda da rocha, periodicos em 16 (dependem so da posicao na celula)."""
    H, W = m.shape
    out = m.copy()
    yy, xx = np.mgrid[0:H, 0:W]
    bx = np.array([[(noise(x % 16 // 4, seed) % (amp + 1)) for x in range(W)]] * H)
    by = np.array([[(noise(y % 16 // 4, seed + 1) % (amp + 1))] * W for y in range(H)])
    # cresce para baixo (rocha acima), para cima, para os lados
    for d in range(1, amp + 1):
        out |= np.roll(m, d, 0) & (bx >= d) & (yy >= d)
        out |= np.roll(m, -d, 0) & (bx >= d) & (yy < H - d)
        out |= np.roll(m, d, 1) & (by >= d) & (xx >= d)
        out |= np.roll(m, -d, 1) & (by >= d) & (xx < W - d)
    return out

def run_below(m):
    """Para cada pixel de rocha: quantos pixels ate o primeiro nao-rocha descendo."""
    H, W = m.shape
    d = np.full((H, W), 999, int)
    cur = np.full(W, 999)
    for y in range(H - 1, -1, -1):
        cur = np.where(m[y], cur + 1, 0)
        d[y] = cur
    return d

# ---------------------------------------------------------------- folha de pecas
SHEET = None
def sheet():
    global SHEET
    if SHEET is None:
        SHEET = Image.open(os.path.join(HERE, 'folha_tileset.png')).convert('RGBA')
    return SHEET

PIECES = {   # bbox na folha 2.png (x, y, w, h), lidos do seg.py
    'boulder_s': (140, 569, 50, 49), 'boulder_s2': (70, 555, 58, 60), 'boulder_m': (360, 538, 59, 87),
    'boulder_t': (429, 519, 96, 119), 'boulder_l': (628, 513, 104, 129), 'boulder_xl': (746, 521, 127, 128),
    'stairs': (17, 652, 135, 97), 'bridge': (760, 658, 186, 86), 'ladder': (1479, 640, 36, 65),
    'geyser': (994, 506, 83, 145), 'geyser2': (1087, 520, 82, 131), 'waterfall': (1080, 389, 92, 105),
    'waterfall_w': (921, 389, 152, 104), 'plate': (647, 881, 70, 64), 'gate_open': (26, 830, 215, 159),
    'gate_closed': (367, 852, 156, 136), 'pillar_l': (311, 852, 42, 131), 'pillar_r': (534, 856, 42, 127),
    'cave': (1065, 260, 65, 106), 'cave_big': (1140, 256, 156, 122), 'dock': (1154, 663, 95, 162),
    'sign': (1257, 879, 56, 63), 'bush_s': (935, 855, 40, 41), 'bush_m': (1180, 866, 53, 55),
    'bush_l': (1003, 908, 88, 75), 'splash': (1371, 520, 62, 49),
}

def piece(name, w, h, crop=None):
    x, y, pw, ph = PIECES[name]
    im = sheet().crop((x, y, x + pw, y + ph))
    if crop:
        l, t, r, b = crop
        im = im.crop((int(pw * l), int(ph * t), int(pw * r), int(ph * b)))
    im = im.resize((w, h), Image.BOX)
    a = np.array(im).astype(int)
    rgb, al = a[..., :3], a[..., 3]
    # o alfa da folha nunca chega a 255; recupera a cor dividindo pelo alfa (premultiplicado pelo BOX)
    return rgb.astype(np.uint8), al > 110

def paste(img, name, px, py, w, h, crop=None, flip=False, mask_out=None):
    rgb, m = piece(name, w, h, crop)
    if flip: rgb, m = rgb[:, ::-1], m[:, ::-1]
    H, W = img.shape[:2]
    for y in range(h):
        for x in range(w):
            X, Y = px + x, py + y
            if m[y, x] and 0 <= X < W and 0 <= Y < H:
                img[Y, X] = rgb[y, x]
                if mask_out is not None:
                    mask_out[Y, X] = True

# ---------------------------------------------------------------- render do mapa
def cells(grid, chars):
    return np.array([[ch in chars for ch in row] for row in grid])

def render(grid, gate_open=False, sea_px=None, layers=False):
    """gate_open: estado aberto do portao, da brecha (R) e da fenda (F).
    layers: devolve tambem a camada de cima (rgb, mascara): o vapor dos geiseres que
    sobe para a celula de cima cobre o jogador que passa por tras."""
    Hc, Wc = len(grid), len(grid[0])
    H, W = Hc * C, Wc * C
    img = np.zeros((H, W, 3), np.uint8)
    top = np.zeros((H, W, 3), np.uint8)
    tm = np.zeros((H, W), bool)
    def geyser(X, Y, cx, cy):
        # cone na propria celula (camada de baixo); o vapor acima dela vai para a de cima
        tmp = np.zeros_like(img); m = np.zeros((H, W), bool)
        paste(tmp, 'geyser' if noise(cx, cy) % 2 else 'geyser2', X - 4, Y - 24, 24, 40, mask_out=m)
        up = m.copy(); up[Y:] = False
        down = m & ~up
        img[down] = tmp[down]
        top[up] = tmp[up]; tm[up] = True
    yy, xx = np.mgrid[0:H, 0:W]
    # areia de fundo (duas variantes por celula)
    for y in range(H):
        for x in range(W):
            img[y, x] = sand_px(x, y, 0)
    ocean = sea_px is not None
    # agua
    for chars, ramp, rim in ((WATER_B, BLUE, WET), (WATER_T, TURQ, TURQ_RIM)):
        wm = shaped(cells(grid, chars | ({'D'} if ocean and chars is WATER_B else set())), 4)
        if not wm.any(): continue
        din = ndimage.distance_transform_edt(wm)
        dout = ndimage.distance_transform_edt(~wm)
        img[(~wm) & (dout <= 1.5)] = rim
        for y, x in zip(*np.nonzero(wm)):
            d = din[y, x]
            if ocean and chars is WATER_B:
                c = sea_px[y % 16, x % 16]
                if d <= 1.2: c = ramp[5]
                elif d <= 2.2: c = ramp[4]
            else:
                c = ramp[5] if d <= 1.2 else ramp[4] if d <= 2.2 else ramp[3] if d <= 3.2 else water_px(x, y, ramp)
            img[y, x] = c
    # grama
    gm = shaped(cells(grid, set('gt')), 4)
    if gm.any():
        din = ndimage.distance_transform_edt(gm)
        for y, x in zip(*np.nonzero(gm)):
            img[y, x] = GRASS[1] if din[y, x] <= 1.2 else grass_px(x, y)
    # rocha (o vazio conta como rocha para a forma)
    rc = cells(grid, SOLID_ROCK)
    rm = lumpy(shaped(rc, 5), 2)
    below = run_below(rm)
    din = ndimage.distance_transform_edt(np.pad(rm, 1, mode='edge'))[1:-1, 1:-1]
    # sombra no chao, logo abaixo da face
    sh = (~rm) & (np.roll(rm, 1, 0) | np.roll(rm, 2, 0)) & (yy > 2)
    img[sh] = (img[sh].astype(int) * 0.78).astype(np.uint8)
    for y, x in zip(*np.nonzero(rm)):
        b = below[y, x]
        if b < FACE_H:
            c = FT[b, x % 16]
        elif b < FACE_H + 1:
            c = ROCK[5]                          # beirada de cima da face
        else:
            c = BT[y % TP, x % TP]
        if din[y, x] <= 1.0:
            c = ROCK[0]
        img[y, x] = c
    # estampas
    for cy, row in enumerate(grid):
        for cx, ch in enumerate(row):
            X, Y = cx * C, cy * C
            left = row[cx - 1] if cx else ch
            if ch == 'o':
                paste(img, 'boulder_m' if noise(cx, cy) % 3 == 0 else 'boulder_s2' if noise(cx, cy) % 3 == 1 else 'boulder_s', X, Y - 1, 16, 17)
            elif ch in 'bB':
                ramp = BLUE if ch == 'b' else TURQ
                for y in range(Y + 11, Y + 15):
                    for x in range(X + 1, X + 15):
                        if ((x - X - 7.5) / 7) ** 2 + ((y - Y - 12.5) / 2.2) ** 2 < 1:
                            img[y, x] = ramp[5]
                paste(img, 'boulder_m', X + 1, Y - 2, 14, 16)
            elif ch == 'S' and left != 'S':
                # escada: degraus cinza, so o miolo da peca (sem as rochas laterais), uma faixa por linha
                n = 1
                while cx + n < len(row) and row[cx + n] == 'S': n += 1
                paste(img, 'stairs', X, Y, n * C, 16, crop=(0.2, 0.06, 0.8, 0.94))
            elif ch == 'Q':
                paste(img, ['boulder_t', 'boulder_l', 'boulder_xl'][noise(cx, cy, 4) % 3], X + 1, Y - 2, 30, 33)
            elif ch == 'H':
                # ponte em tres partes: ponta, meio repetido, ponta (o meio custa os mesmos tiles)
                right = row[cx + 1] if cx + 1 < len(row) else ch
                part = (0, 1 / 3) if left != 'H' else (2 / 3, 1) if right != 'H' else (0.4, 0.6)
                paste(img, 'bridge', X, Y + 1, 16, 15, crop=(part[0], 0, part[1], 1))
            elif ch == 'L':
                paste(img, 'ladder', X + 3, Y - 10, 10, 24)
            elif ch == 'E':
                for y in range(Y - 6, Y + 16):
                    for x in range(X + 1, X + 15):
                        dx = (x - X - 7.5) / 7
                        if y >= Y - 6 + 7 * dx * dx:
                            img[y, x] = VOID if y < Y + 12 else (60, 40, 40)
            elif ch in 'GK' or (ch == 'F' and gate_open):
                geyser(X, Y, cx, cy)
            elif ch == 'F':     # a fenda: o cone do geiser sem o vapor, com a pedra preta entupindo
                paste(img, 'geyser2', X - 4, Y, 24, 16, crop=(0, 0.6, 1, 1))
                for y in range(Y + 1, Y + 9):
                    for x in range(X + 3, X + 13):
                        r = ((x - X - 7.5) / 5) ** 2 + ((y - Y - 5) / 3.6) ** 2
                        if r < 1:
                            img[y, x] = VOID if r > 0.7 else ROCK[1] if (x + y) % 5 else ROCK[2]
                img[Y + 3, X + 6] = ROCK[3]; img[Y + 3, X + 7] = ROCK[3]
            elif ch == 'W' and (cy == 0 or grid[cy - 1][cx] != 'W') and left != 'W':
                n = 1
                while cx + n < len(row) and row[cx + n] == 'W': n += 1
                h = 1
                while cy + h < len(grid) and grid[cy + h][cx] == 'W': h += 1
                paste(img, 'waterfall', X, Y, n * C, h * C + 6)
            elif ch == 'P':
                paste(img, 'plate', X + 1, Y + 2, 14, 13)
            elif ch == 'R' and not gate_open:
                # a brecha: rachadura funda em zigue-zague, borda clara de pedra lascada,
                # com agua brilhando no fundo (o mar esta do outro lado)
                xs = [7, 6, 6, 5, 6, 7, 8, 9, 9, 8, 7, 7, 6, 6]
                for i, x0 in enumerate(xs):
                    y = Y + 1 + i
                    w = 2 if 3 <= i <= 10 else 1
                    img[y, X + x0 - 1] = ROCK[5]
                    for k in range(w):
                        img[y, X + x0 + k] = VOID
                    img[y, X + x0 + w] = ROCK[0]
                    if i in (5, 7): img[y, X + x0] = BLUE[2]
                for i, (dx, dy) in enumerate(((3, 4), (4, 5), (11, 9), (12, 10))):
                    img[Y + dy, X + dx] = VOID
            elif ch == 'R':
                # aberta: buraco escuro na face e um fio de mar descendo ate a areia
                for y in range(Y + 2, Y + 13):
                    for x in range(X + 2, X + 14):
                        r = ((x - X - 7.5) / 5.5) ** 2 + ((y - Y - 7) / 5) ** 2
                        if r < 1:
                            img[y, x] = ROCK[0] if r > 0.75 else VOID
                for y in range(Y + 7, Y + 22):
                    for x in range(X + 6, X + 10):
                        img[y, x] = BLUE[4] if x == X + 7 else BLUE[2] if x == X + 8 else BLUE[1]
                for y in range(Y + 19, Y + 25):
                    for x in range(X + 2, X + 14):
                        if ((x - X - 7.5) / 6) ** 2 + ((y - Y - 22) / 2.6) ** 2 < 1:
                            img[y, x] = BLUE[3] if (x + y) % 4 else BLUE[4]
            elif ch == 'C' and left != 'C' and (cy == 0 or grid[cy - 1][cx] != 'C'):
                paste(img, 'cave_big', X - 4, Y - 22, 56, 38)
            elif ch == 'N':
                paste(img, 'sign', X + 1, Y + 2, 14, 12)
            elif ch == 't':
                paste(img, ['bush_s', 'bush_m', 'bush_l'][noise(cx, cy, 2) % 3], X + 1, Y + 1, 14, 14)
            elif ch == 'D' and left != 'D' and (cy == 0 or grid[cy - 1][cx] != 'D'):
                n = 1
                while cx + n < len(row) and row[cx + n] == 'D': n += 1
                h = 1
                while cy + h < len(grid) and grid[cy + h][cx] == 'D': h += 1
                paste(img, 'dock', X, Y - 4, n * C, h * C + 4)
    # portao (4x2 de Y + o X embaixo no meio)
    for cy, row in enumerate(grid):
        if 'Y' in row and (cy == 0 or 'Y' not in grid[cy - 1]):
            cx = row.index('Y')
            paste(img, 'gate_open' if gate_open else 'gate_closed', cx * C - 6, cy * C - 8, 3 * C + 12, 3 * C + 8)
            break
    # vazio
    vm = np.kron(cells(grid, ':'), np.ones((C, C), bool))
    img[vm] = VOID
    if layers:
        return img, top, tm
    return img

def preview(name, out, scale=3, gate_open=False):
    img = render(MAPS[name], gate_open)
    Image.fromarray(img).resize((img.shape[1] * scale, img.shape[0] * scale), Image.NEAREST).save(out)

if __name__ == '__main__':
    # python art.py <pasta de saida> room1 room2 ...  -> previa RGB (antes de virar GBA)
    for n in sys.argv[2:]:
        preview(n, os.path.join(sys.argv[1], 'prev_%s.png' % n))
        print('ok', n)
