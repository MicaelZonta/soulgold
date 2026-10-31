"""Andar da Thunderspire: moldura da BurnedTower_1F alargada, chao limpo, buracos de raio retangulares."""
import sys, os
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
FLOOR, BOULDER, SCORCH = 0x400, 0x407, 0x40e
def andar(W, H, exit_mat=True):
    g = Grid(W, H, 0)
    put(g, nine('BurnedTower_1F', 0, 0, 27, 25, W, H, cx=8, px=1, cy=8, py=1), 0, 0)
    for y in range(4, H - 2):
        for x in range(2, W - 1): g.set(x, y, FLOOR, 0, 3)
    mx = [x for x in range(W) if (g.b[H - 2][x] & 0x7ff) in (0x1a, 0x1b, 0x1c)]
    for x, m in zip(mx, (0x425, 0x426, 0x427)): g.set(x, H - 3, m, 0, 3)
    if not exit_mat:                                     # sem saida embaixo: fecha a soleira
        for x in range(W):
            for y in (H - 3, H - 2): pass
        mx = [x for x in range(W) if (g.b[H - 2][x] & 0x7ff) in (0x1a, 0x1b, 0x1c)]
        for x in mx: g.set(x, H - 2, 0, 1, 0)
        for x in range(2, W - 1): g.set(x, H - 3, FLOOR, 0, 3)
    return g
def poco(g, x0, y0, x1, y1):
    """Buraco aberto pelo raio: borda bloqueada, fundo em elevacao 4 (inacessivel)."""
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            L, R, T, B = x == x0, x == x1, y == y0, y == y1
            if T:   m = 0x408 if L else 0x40a if R else 0x409
            elif B: m = 0x418 if L else 0x41a if R else 0x419
            else:   m = 0x410 if L else 0x412 if R else 0x411
            if T or B or L or R: g.set(x, y, m, 1, 0)
            else: g.set(x, y, m, 0, 4)
def escada_sobe(g, x, y):
    g.set(x, y - 1, 0x415, 1, 0); g.set(x, y, 0x41d, 0, 3)
def estatua(g, x, y):
    g.set(x, y - 1, 0x40f, 0, 3); g.set(x, y, 0x249, 1, 0)
def obj(pref, lid, gfx, x, y, face='DOWN', script='', ttype='TRAINER_TYPE_NONE', sight='0', flag='0'):
    return {'local_id': pref + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
def alcance(g, start, extra_block=()):
    b = g.flat(); W = g.w
    walk = lambda x, y: not (b[y * W + x] >> 11 & 1) and (b[y * W + x] >> 12) in (3, 0) and (x, y) not in extra_block
    return slide_reach(start, walk, lambda x, y: False, W, g.h)
def perto(d, c):
    return min([d[n] for n in ((c[0], c[1] + 1), (c[0], c[1] - 1), (c[0] + 1, c[1]), (c[0] - 1, c[1]), c) if n in d], default=None)
def render(g, objs, out, name, overlay=False, marks=(), night=0.0):
    L = load_layout('BurnedTower_1F')
    cv = render_blocks(g.flat(), g.w, g.h, L['prim'], L['sec'], overlay=overlay, marks=marks, night=night)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob, night > .5)
    write_png(os.path.join(out, name), cv, 2)
