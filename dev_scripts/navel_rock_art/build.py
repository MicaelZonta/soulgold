"""RGB dos mapas -> tileset secundario GBA (384 tiles, paletas 7..12) + blocos dos mapas.

Uso: python build.py <grupo> <saida.json>    grupo = cave | island
Saida: JSON com tiles (indices 8x8), paletas, metatiles (12 entradas), atributos,
blocos de cada mapa e o estado aberto do portao. Quem escreve os arquivos do repo e
o write_repo.py (python do WSL, com o tileset_kit)."""
import sys, os, json, numpy as np
from PIL import Image
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import art
from grids import MAPS

MAX_TILES = 384
NPAL = 6
WALK = set('.SHLEXiVPDNg')
BEHAV = {'L': 0x61, 'E': 0x61, 'X': 0x60, 'C': 0x60}
# comportamento so de uma celula: a ponta do cais e a volta para Vermilion (MB_SOUTH_ARROW_WARP)
BEHAV_AT = {('ext', 9, 38): 0x65}
SEA_META = 299          # mar animado do primario (kanto_general_hns)

OPEN = {'room1', 'room2', 'room3'}   # salas com estado aberto (brecha, fenda, portao) para setmetatile
CLEAR = 99              # pixel transparente da camada de cima (vira o indice 0)
GROUPS = {'room1': ['room1'], 'room2': ['room2'], 'room3': ['room3'], 'room4': ['room4'], 'ext': ['ext']}

def q5(img):
    return (img.astype(int) >> 3)          # RGB555 por canal, 0..31

def tiles_of(img):
    H, W = img.shape[:2]
    return img.reshape(H // 8, 8, W // 8, 8, 3).transpose(0, 2, 1, 3, 4)

def kmeans(X, w, k, it=25, seed=0):
    X = X.astype(float); w = w.astype(float)
    if len(X) <= k:
        return X.copy()
    rng = np.random.default_rng(seed)
    # k-means++ simples
    C = [X[rng.choice(len(X), p=w / w.sum())]]
    for _ in range(k - 1):
        d = ((X[:, None] - np.array(C)[None]) ** 2).sum(2).min(1) * w
        C.append(X[rng.choice(len(X), p=d / d.sum())] if d.sum() > 0 else X[0])
    C = np.array(C)
    for _ in range(it):
        a = ((X[:, None] - C[None]) ** 2).sum(2).argmin(1)
        for i in range(k):
            m = a == i
            if m.any():
                C[i] = (X[m] * w[m, None]).sum(0) / w[m].sum()
    return np.round(C)

def tile_err(T, pal):
    """T: (n,64,3) ; pal: (15,3) -> erro por tile e indices (1..15; 0 = transparente)."""
    clear = T[:, :, 0] == CLEAR
    d = ((T[:, :, None, :] - pal[None, None]) ** 2).sum(3)
    return np.where(clear, 0, d.min(2)).sum(1), np.where(clear, 0, d.argmin(2) + 1)

def fit_palettes(U, cnt):
    """U: tiles unicos (n,64,3) em RGB555. Agrupa em NPAL paletas de 15 cores."""
    n = len(U)
    Um = np.ma.masked_equal(U, CLEAR)
    feat = np.concatenate([Um.mean(1).filled(0), Um.std(1).filled(0)], 1)
    C = kmeans(feat, cnt, NPAL, seed=1)
    a = ((feat[:, None] - C[None]) ** 2).sum(2).argmin(1)
    for it in range(10):
        pals = []
        for p in range(NPAL):
            m = a == p
            if not m.any():
                pals.append(np.zeros((15, 3))); continue
            px = U[m].reshape(-1, 3); w = np.repeat(cnt[m], 64)
            ok = px[:, 0] != CLEAR
            px, w = px[ok], w[ok]
            cols, inv = np.unique(px, axis=0, return_inverse=True)
            ww = np.bincount(inv.ravel(), w)
            pals.append(kmeans(cols, ww, 15, seed=it))
        pals = [np.pad(p, ((0, 15 - len(p)), (0, 0)), mode='edge') if len(p) < 15 else p for p in pals]
        E = np.stack([tile_err(U, p)[0] for p in pals], 1)
        na = E.argmin(1)
        tot = (E[np.arange(n), na] * cnt).sum()
        print('  iter', it, 'erro', int(tot), 'tiles por paleta', np.bincount(na, minlength=NPAL).tolist())
        if (na == a).all():
            break
        a = na
    return np.array(pals), a

FLIPS = [(0, 0), (1, 0), (0, 1), (1, 1)]
def flipped(t, h, v):
    t = t.reshape(8, 8)
    if h: t = t[:, ::-1]
    if v: t = t[::-1]
    return t.reshape(64)

def main(group, out):
    names = GROUPS[group]
    sea = None
    if group == 'ext':
        sea = np.array(Image.open(os.path.join(HERE, 'sea299.png')).convert('RGB'))
    renders = {}
    for n in names:
        renders[n] = art.render(MAPS[n], sea_px=sea, layers=True)
        if n in OPEN:
            renders[n + '_open'] = art.render(MAPS[n], gate_open=True, layers=True)
    # celulas que vao para o tileset (o mar aberto do porto e o primario)
    def is_open_sea(grid, cx, cy):
        for dy in (-1, 0, 1):
            for dx in (-1, 0, 1):
                y, x = cy + dy, cx + dx
                if 0 <= y < len(grid) and 0 <= x < len(grid[0]) and grid[y][x] != '~':
                    return False
        return True
    allt = []      # (mapa, cx, cy, entrada 0..3 baixo / 8..11 cima, tile RGB555 64x3)
    for n, (img, top, tm) in renders.items():
        grid = MAPS[n.replace('_open', '')]
        T = tiles_of(q5(img))
        top = q5(top); top[~tm] = CLEAR
        TT, TM = tiles_of(top), tm.reshape(tm.shape[0] // 8, 8, tm.shape[1] // 8, 8).any((1, 3))
        for cy in range(len(grid)):
            for cx in range(len(grid[0])):
                if sea is not None and is_open_sea(grid, cx, cy):
                    continue
                for q in range(4):
                    ty, tx = cy * 2 + q // 2, cx * 2 + q % 2
                    allt.append((n, cx, cy, q, T[ty, tx].reshape(64, 3)))
                    if TM[ty, tx]:
                        allt.append((n, cx, cy, 8 + q, TT[ty, tx].reshape(64, 3)))
    arr = np.stack([t[4] for t in allt])
    U, inv, cnt = np.unique(arr.reshape(len(arr), -1), axis=0, return_inverse=True, return_counts=True)
    inv = inv.ravel()
    U = U.reshape(-1, 64, 3)
    print(group, 'tiles RGB unicos', len(U))
    pals, a = fit_palettes(U, cnt)
    # indexa
    idx = np.zeros((len(U), 64), int)
    for p in range(NPAL):
        m = a == p
        if m.any():
            idx[m] = tile_err(U[m], pals[p])[1]
    # dedup com flip: chave = (paleta, indices)
    def canon(p, t):
        best = None
        for h, v in FLIPS:
            k = (p, tuple(flipped(t, h, v)))
            if best is None or k < best[0]:
                best = (k, h, v)
        return best
    keys = {}
    ucanon = []
    for i in range(len(U)):
        k, h, v = canon(a[i], idx[i])
        if k not in keys:
            keys[k] = len(keys)
        ucanon.append((keys[k], h, v))
    print(group, 'tiles indexados unicos (com flip)', len(keys))
    # funde os mais parecidos ate caber (mesma paleta), pesando pelo uso
    klist = list(keys.keys())
    use = np.zeros(len(klist))
    for i, (k, h, v) in enumerate(ucanon):
        use[k] += cnt[i]
    rep = list(range(len(klist)))
    def rgb_of(k):
        p, t = klist[k]
        t = np.array(t)
        return np.where(t[:, None] == 0, -40, pals[p][t - 1])
    alive = set(range(len(klist)))
    blank_like = None
    if len(klist) > MAX_TILES - 1:
        R = np.stack([rgb_of(k) for k in range(len(klist))]).astype(float)
        P = np.array([k[0] for k in klist])
        while len(alive) > MAX_TILES - 1:
            al = np.array(sorted(alive))
            best = (1e18, None, None)
            for p in range(NPAL):
                ids = al[P[al] == p]
                if len(ids) < 2: continue
                X = R[ids].reshape(len(ids), -1)
                D = ((X[:, None] - X[None]) ** 2).sum(2)
                np.fill_diagonal(D, 1e18)
                # custo: diferenca vezes o uso do que some
                wmin = np.minimum(use[ids][:, None], use[ids][None])
                Cc = D
                i, j = np.unravel_index(Cc.argmin(), Cc.shape)
                if Cc[i, j] < best[0]:
                    best = (Cc[i, j], ids[i], ids[j])
            _, i, j = best
            keep, drop = (i, j) if use[i] >= use[j] else (j, i)
            alive.discard(drop); use[keep] += use[drop]
            for r in range(len(rep)):
                if rep[r] == drop: rep[r] = keep
            # fundir varios por rodada para acelerar
        print(group, 'depois de fundir', len(alive))
    final = {k: n + 1 for n, k in enumerate(sorted(alive))}   # tile 0 do secundario fica vazio
    tiles_out = [[0] * 64] + [list(klist[k][1]) for k in sorted(alive)]
    # entradas por tile RGB unico
    def entry_of(i):
        k, h, v = ucanon[i]
        k = rep[k]
        p, t = klist[k]
        # descobre o flip certo em relacao ao representante
        tt = np.array(t)
        for hh, vv in FLIPS:
            if (flipped(idx[i], hh, vv) == tt).all():
                h, v = hh, vv; break
        return (640 + final[k]) | (h << 10) | (v << 11) | ((7 + p) << 12)
    # metatiles
    metas, mindex = [], {}
    blocks = {}
    pos = {}
    for n_i, (n, cx, cy, q, _) in enumerate(allt):
        pos.setdefault((n, cx, cy), [0] * 12)[q] = entry_of(inv[n_i])
    gate = []
    for n in renders:
        grid = MAPS[n.replace('_open', '')]
        Wc, Hc = len(grid[0]), len(grid)
        bl = []
        for cy in range(Hc):
            for cx in range(Wc):
                ch = grid[cy][cx]
                coll = 0 if ch in WALK else 1
                if ch == 'C' and grid[cy][cx - 1] == 'C' and grid[cy][cx + 1] == 'C':
                    coll = 0
                if (n, cx, cy) not in pos:
                    bl.append((SEA_META, 1)); continue
                ent = tuple(pos[(n, cx, cy)])
                beh = BEHAV_AT.get((n, cx, cy), BEHAV.get(ch, 0))
                key = (ent, beh)
                if key not in mindex:
                    mindex[key] = len(metas); metas.append(key)
                bl.append((1024 + mindex[key], coll))
        blocks[n] = dict(w=Wc, h=Hc, cells=bl)
    for n in names:
        if n + '_open' in blocks:
            c, o = blocks[n]['cells'], blocks.pop(n + '_open')['cells']
            Wn = blocks[n]['w']
            gate = [dict(x=i % Wn, y=i // Wn, closed=c[i][0], open=o[i][0], coll=o[i][1])
                    for i in range(len(c)) if c[i][0] != o[i][0]]
    print(group, 'metatiles', len(metas), 'tiles', len(tiles_out), 'portao', len(gate))
    pal_rgb = [[[int(v) * 8 for v in c] for c in [(31, 0, 31)] + [tuple(x) for x in p]] for p in pals]
    json.dump(dict(tiles=tiles_out, pals=pal_rgb, metas=[list(m[0]) for m in metas],
                   attrs=[m[1] for m in metas], blocks=blocks, gate=gate), open(out, 'w'), default=int)
    # previa do resultado (como o jogo desenha)
    for n, b in blocks.items():
        img = np.zeros((b['h'] * 16, b['w'] * 16, 3), np.uint8)
        for i, (mid, coll) in enumerate(b['cells']):
            cx, cy = i % b['w'], i // b['w']
            if mid < 1024:
                img[cy * 16:cy * 16 + 16, cx * 16:cx * 16 + 16] = sea; continue
            ents = metas[mid - 1024][0]
            for q, e in list(enumerate(ents[:4])) + [(q, ents[8 + q]) for q in range(4)]:
                if e == 0: continue
                t = np.array(tiles_out[(e & 0x3ff) - 640]).reshape(8, 8)
                if e >> 10 & 1: t = t[:, ::-1]
                if e >> 11 & 1: t = t[::-1]
                pal = np.array(pal_rgb[(e >> 12) - 7])
                y0, x0 = cy * 16 + q // 2 * 8, cx * 16 + q % 2 * 8
                cell = img[y0:y0 + 8, x0:x0 + 8]
                cell[t > 0] = pal[t][t > 0]
        Image.fromarray(img).resize((img.shape[1] * 3, img.shape[0] * 3), Image.NEAREST).save(
            os.path.join(os.path.dirname(os.path.abspath(out)), 'gba_%s.png' % n))

if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
