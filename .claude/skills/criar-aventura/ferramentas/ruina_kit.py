import os
"""Kit das Truthsand Ruins: johto_general + desert (pecas aprendidas de RegirockChamber e
VajraPyramidOutside). Salas = conjunto de celulas de chao; paredes classificadas por vizinhanca:
penhasco de 3 linhas acima do chao (1066/1074/1082, pontas 1065.. e ..1067), laterais 1059/1057,
borda de baixo 1050 (cantos 1051/1049), enchimento 1058."""
import sys, os, json
SC = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SC)
from kit_aventura import *
PRIM = 'gTileset_Johto_General'; SEC = 'gTileset_Desert'
SAND, PATH, FILL = 1032, 1034, 1058
CLIFF = {1: (1081, 1082, 1083), 2: (1073, 1074, 1075), 3: (1065, 1066, 1067)}

class Ruina:
    def __init__(s, w, h):
        s.w, s.h = w, h
        s.floor = [[False] * w for _ in range(h)]
        s.g = Grid(w, h, pack_block(FILL, 1))
        s.objs, s.warps, s.bgs = [], [], []
    def room(s, x0, y0, x1, y1):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                if 0 <= x < s.w and 0 <= y < s.h: s.floor[y][x] = True
    def F(s, x, y): return 0 <= x < s.w and 0 <= y < s.h and s.floor[y][x]
    def cliffk(s, x, y):
        if s.F(x, y): return 0
        for k in (1, 2, 3):
            if s.F(x, y + k) and all(not s.F(x, y + j) for j in range(1, k)): return k
        return 0
    FH = 4                                  # altura maxima do paredao acima de cada sala
    def paint(s):
        """Regra da RegirockChamber: paredao (topo 0x42a, meio 0x432, base 0x43a) acima de cada sala, na
        largura dela; bordas laterais 0x423/0x421 subindo junto; borda de baixo 0x41a com cantos 0x41b/0x419;
        enchimento 0x422. O paredao para uma linha antes do chao de cima (para a borda de baixo dele)."""
        g, F = s.g, s.F
        face = {}
        for y in range(s.h):
            for x in range(s.w):
                if F(x, y) and not F(x, y - 1):
                    cells = []
                    for k in range(1, s.FH + 1):
                        yy = y - k
                        if yy < 0 or F(x, yy) or F(x, yy - 1): break
                        cells.append(yy)
                    for i, yy in enumerate(cells):
                        top = i == len(cells) - 1
                        face[(x, yy)] = 0x43a if i == 0 and not top else (0x42a if top and len(cells) > 1 else (0x43a if i == 0 else 0x432))
        FF = lambda x, y: F(x, y) or (x, y) in face
        for y in range(s.h):
            for x in range(s.w):
                if F(x, y): g.set(x, y, SAND, 0); continue
                if (x, y) in face: g.set(x, y, face[(x, y)], 1); continue
                N, E, W = F(x, y - 1), FF(x + 1, y), FF(x - 1, y)
                if N and F(x + 1, y): m = 0x41b
                elif N and F(x - 1, y): m = 0x419
                elif N: m = 0x41a
                elif E: m = 0x423
                elif W: m = 0x421
                else: m = FILL
                g.set(x, y, m, 1)
    # ---- decoracao (sobre chao)
    def path(s, cells):
        for x, y in cells: s.g.set(x, y, PATH, 0)
    def statue(s, x, y, right=False):      # 1x2, topo 1286/1287 + base 1294/1295
        s.g.set(x, y, 1287 if right else 1286, 1); s.g.set(x, y + 1, 1295 if right else 1294, 1)
    def skeleton(s, x, y): s.g.set(x, y, 1031, 1); s.g.set(x, y + 1, 1039, 1)
    def rock2x3(s, x, y):
        for (dx, dy), m in zip([(0, 0), (1, 0), (0, 1), (1, 1), (0, 2), (1, 2)], (1044, 1045, 1052, 1053, 1060, 1061)): s.g.set(x + dx, y + dy, m, 1)
    def dune(s, x, y):
        for (dx, dy), m in zip([(0, 0), (1, 0), (0, 1), (1, 1)], (1200, 1201, 1208, 1209)): s.g.set(x + dx, y + dy, m, 0)
    def crate(s, x, y):                      # caixote 2x2 de escavacao
        for (dx, dy), m in zip([(0, 0), (1, 0), (0, 1), (1, 1)], (1104, 1105, 1120, 1121)): s.g.set(x + dx, y + dy, m, 1)
    def scaffold(s, x, y, n):                # tabuas verticais de escoramento
        for i in range(n): s.g.set(x + i, y, 1112 + i % 4, 1)
    def hole(s, x, y):                       # sumidouro de areia 1x2 (warp na celula de baixo)
        s.g.set(x, y, 1119, 0); s.g.set(x, y + 1, 1127, 0)
    def ladder(s, x, y): s.g.set(x, y, 1159, 0)
    def door(s, x, y): s.g.set(x, y, 1206, 0)   # abertura escura (MB_NON_ANIMATED_DOOR)
    def obj(s, lid, gfx, x, y, face='DOWN', script='0x0', ttype='TRAINER_TYPE_NONE', sight='0', flag='0'):
        s.objs.append(dict(local_id=lid, graphics_id='OBJ_EVENT_GFX_' + gfx, x=x, y=y, elevation=3,
                           movement_type='MOVEMENT_TYPE_FACE_' + face, movement_range_x=0, movement_range_y=0,
                           trainer_type=ttype, trainer_sight_or_berry_tree_id=sight, script=script, flag=flag))
    def warp(s, x, y, dest, wid, nota): s.warps.append(dict(x=x, y=y, dest_map=dest, dest_warp_id=str(wid), nota=nota))
    def bg(s, x, y, script): s.bgs.append(dict(type='sign', x=x, y=y, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_ANY', script=script))
    # ---- saida
    def blocks(s): return s.g.flat()
    def check(s, starts, targets, extra_block=(), ignore=()):
        """targets: nome -> celula; alcancado se a celula OU um vizinho 4-dir for alcancado.
        Objetos bloqueiam (menos itens, os de ceu e os em `ignore`)."""
        b = s.blocks(); bl = set(extra_block)
        for o in s.objs:
            if o['graphics_id'] != 'OBJ_EVENT_GFX_ITEM_BALL' and 'SKY' not in o['local_id'] and o['local_id'] not in ignore:
                bl.add((o['x'], o['y']))
        walk = lambda x, y: not (b[y * s.w + x] >> 11 & 1) and (x, y) not in bl
        res = {}
        for st in starts:
            d = slide_reach(st, walk, lambda x, y: False, s.w, s.h)
            for nm, t in targets.items():
                c = [d[q] for q in (t, (t[0] + 1, t[1]), (t[0] - 1, t[1]), (t[0], t[1] + 1), (t[0], t[1] - 1)) if q in d]
                if c: res.setdefault(nm, min(c))
        bad = check_objects(b, s.w, [o for o in s.objs if 'SKY' not in o['local_id']])
        return res, bad
    def render(s, path, objs=None, overlay=False, marks=(), extra=None, dark=0.0):
        L = load_layout('RegirockChamber')
        cv = render_blocks(s.blocks(), s.w, s.h, L['prim'], L['sec'], overlay=overlay, marks=marks)
        if dark:
            cv = [[tuple(int(c[k] * (1 - dark) + (40, 30, 20)[k] * dark) for k in range(3)) for c in row] for row in cv]
        if extra: extra(cv)
        for o in sorted(objs if objs is not None else s.objs, key=lambda q: q['y']): draw_object(cv, o)
        write_png(path, cv, 2)
    def save(s, d, info):
        write_blocks(os.path.join(d, 'map.bin'), s.g.b)
        write_blocks(os.path.join(d, 'border.bin'), [[pack_block(FILL, 1)] * 2] * 2)
        info.update(w=s.w, h=s.h, primary=PRIM, secondary=SEC, warps=s.warps, objects=s.objs, bg_events=s.bgs, connections=[])
        json.dump(info, open(os.path.join(d, 'info.json'), 'w'), indent=1, ensure_ascii=False)
