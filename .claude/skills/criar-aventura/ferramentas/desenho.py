"""Mini-biblioteca de pixel art: tela RGB com transparencia (None)."""
import math
class Tela:
    def __init__(s, w, h): s.w, s.h = w, h; s.p = [[None] * w for _ in range(h)]
    def px(s, x, y, c):
        x, y = int(x), int(y)
        if 0 <= x < s.w and 0 <= y < s.h and c is not None: s.p[y][x] = c
    def rect(s, x0, y0, x1, y1, c):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1): s.px(x, y, c)
    def hline(s, x0, x1, y, c): s.rect(x0, y, x1, y, c)
    def vline(s, x, y0, y1, c): s.rect(x, y0, x, y1, c)
    def ellipse(s, cx, cy, rx, ry, c):
        for y in range(int(cy - ry) - 1, int(cy + ry) + 2):
            for x in range(int(cx - rx) - 1, int(cx + rx) + 2):
                if ((x + .5 - cx) / rx) ** 2 + ((y + .5 - cy) / ry) ** 2 <= 1: s.px(x, y, c)
    def poly(s, pts, c):
        ys = [p[1] for p in pts]
        for y in range(int(min(ys)), int(max(ys)) + 1):
            xs = []
            n = len(pts)
            for i in range(n):
                (x0, y0), (x1, y1) = pts[i], pts[(i + 1) % n]
                if (y0 <= y + .5 < y1) or (y1 <= y + .5 < y0):
                    xs.append(x0 + (y + .5 - y0) * (x1 - x0) / (y1 - y0))
            xs.sort()
            for a, b in zip(xs[::2], xs[1::2]):
                for x in range(int(round(a)), int(round(b))): s.px(x, y, c)
    def line(s, x0, y0, x1, y1, c):
        n = int(max(abs(x1 - x0), abs(y1 - y0))) + 1
        for i in range(n + 1):
            t = i / max(n, 1); s.px(round(x0 + (x1 - x0) * t), round(y0 + (y1 - y0) * t), c)
    def outline(s, c, diag=False):
        """Contorno de 1 px por fora do que ja foi desenhado."""
        add = []
        nb = [(1, 0), (-1, 0), (0, 1), (0, -1)] + ([(1, 1), (-1, -1), (1, -1), (-1, 1)] if diag else [])
        for y in range(s.h):
            for x in range(s.w):
                if s.p[y][x] is None and any(0 <= x + dx < s.w and 0 <= y + dy < s.h and s.p[y + dy][x + dx] is not None for dx, dy in nb):
                    add.append((x, y))
        for x, y in add: s.p[y][x] = c
    def shade_where(s, cond, c):
        for y in range(s.h):
            for x in range(s.w):
                if s.p[y][x] is not None and cond(x, y, s.p[y][x]): s.p[y][x] = c
    def colors(s): return {c for r in s.p for c in r if c is not None}
    def over(s, base, ox, oy):
        """Compoe sobre uma imagem RGB (lista de linhas) na posicao ox, oy."""
        for y in range(s.h):
            for x in range(s.w):
                c = s.p[y][x]
                if c is not None and 0 <= oy + y < len(base) and 0 <= ox + x < len(base[0]): base[oy + y][ox + x] = c
        return base
    def rgb(s, bg=(0, 0, 0)): return [[c if c is not None else bg for c in r] for r in s.p]

def reduzir(t, n=15):
    """Funde as cores mais proximas ate caber em n (uma paleta de 16 com a transparente)."""
    cols = list(t.colors())
    m = {c: c for c in cols}
    cnt = {}
    for r in t.p:
        for c in r:
            if c is not None: cnt[c] = cnt.get(c, 0) + 1
    while len(cols) > n:
        best = None
        for i in range(len(cols)):
            for j in range(i + 1, len(cols)):
                d = sum((a - b) ** 2 for a, b in zip(cols[i], cols[j]))
                if best is None or d < best[0]: best = (d, i, j)
        _, i, j = best
        keep, drop = (cols[i], cols[j]) if cnt[cols[i]] >= cnt[cols[j]] else (cols[j], cols[i])
        cnt[keep] += cnt.pop(drop); cols.remove(drop)
        for k, v in m.items():
            if v == drop: m[k] = keep
    t.p = [[m[c] if c is not None else None for c in r] for r in t.p]
    return t
