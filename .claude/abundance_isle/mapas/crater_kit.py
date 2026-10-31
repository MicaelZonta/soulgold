"""Pecas e utilitarios comuns dos andares da Frostfall Crater (johto_general + cave_ice)."""
import sys, os, json, random
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
from desenho import reduzir
SNOW, FLOOR, ICE, BALL = 0x411, 0x459, 0x4cb, 0x4c7
LI = load_layout('SnowtopMountain_B1F')
PRIM, SEC = 'gTileset_Johto_General', 'gTileset_Cave_Ice'

class Cave:
    def __init__(s, w, h):
        s.w, s.h = w, h
        s.floor = [[False] * w for _ in range(h)]
        s.g = Grid(w, h, pack_block(SNOW, 1))
        s.objects, s.warps, s.marks = [], [], []
    def room(s, x0, y0, x1, y1):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1): s.floor[y][x] = True
    def F(s, x, y): return 0 <= x < s.w and 0 <= y < s.h and s.floor[y][x]
    def walls(s):
        for y in range(s.h):
            for x in range(s.w):
                if s.floor[y][x]: s.g.set(x, y, FLOOR, 0); continue
                sig = ''.join('1' if s.F(x + dx, y + dy) else '0' for dx, dy in NB8)
                if '1' in sig: s.g.set(x, y, cave_wall(sig), 1)
    # ---- pecas
    def ice(s, x0, y0, x1, y1):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                if s.floor[y][x]: s.g.set(x, y, ICE, 0)
    def ball(s, x, y): s.g.set(x, y, BALL, 1)
    def big(s, x, y):
        for (dx, dy), m in zip(((0, 0), (1, 0), (0, 1), (1, 1)), (0x41d, 0x41e, 0x425, 0x426)): s.g.set(x + dx, y + dy, m, 1)
    def icicle(s, x, y): s.g.set(x, y, 0x41f, 1); s.g.set(x, y + 1, 0x427, 1)
    def exit_south(s, x, y, dest, wid='0', nota=''):
        """Saida no chao (0x407) com a moldura de porta abaixo (448/449/44a)."""
        s.g.set(x, y, 0x407, 0); s.g.set(x - 1, y + 1, 0x448, 1); s.g.set(x, y + 1, 0x449, 1); s.g.set(x + 1, y + 1, 0x44a, 1)
        s.warp(x, y, dest, wid, nota)
    def ladder_up(s, x, y, dest, wid='0', nota=''):
        """Escada encostada na parede: 0x40e na parede (y-1), 0x416 no chao (warp)."""
        s.g.set(x, y - 1, 0x40e, 1, 0); s.g.set(x, y, 0x416, 0); s.warp(x, y, dest, wid, nota)
    def ladder_down(s, x, y, dest, wid='0', nota=''):
        s.g.set(x, y, 0x405, 0); s.warp(x, y, dest, wid, nota)
    def hole(s, x, y, dest, wid='0', nota=''):
        s.g.set(x, y, 0x406, 0); s.warp(x, y, dest, wid, nota)
    def warp(s, x, y, dest, wid, nota):
        s.warps.append(dict(x=x, y=y, dest_map=dest, dest_warp_id=str(wid), nota=nota))
    def block_art(s, x0, y0, w, h):
        for y in range(h):
            for x in range(w): s.g.set(x0 + x, y0 + y, FLOOR, 1)
    # ---- objetos
    def obj(s, lid, gfx, x, y, face='DOWN', script='0x0', flag='0', ttype='TRAINER_TYPE_NONE', sight='0'):
        o = {'local_id': lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
             'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
             'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
        s.objects.append(o); return o
    # ---- verificacao: objetos bloqueiam (e param o deslize); warps encerram o caminho
    def _graph(s, extra_block=(), ignore=()):
        b = s.g.flat(); W = s.w
        occ = {(o['x'], o['y']) for o in s.objects if o['local_id'] not in ignore and not o.get('_estado')} | set(extra_block)
        warps = {(w['x'], w['y']) for w in s.warps}
        walk = lambda x, y: 0 <= x < s.w and 0 <= y < s.h and not (b[y * W + x] >> 11 & 1) and (x, y) not in occ
        ice = lambda x, y: (b[y * W + x] & 0x7ff) == ICE
        return walk, ice, warps
    def _bfs(s, start, extra_block=(), ignore=()):
        from collections import deque
        walk, ice, warps = s._graph(extra_block, ignore)
        prev = {start: None}; dist = {start: 0}; q = deque([start])
        while q:
            p = q.popleft()
            if p in warps and p != start: continue
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                x, y = p
                while True:
                    nx, ny = x + dx, y + dy
                    if not walk(nx, ny): break
                    x, y = nx, ny
                    if not ice(x, y) or (x, y) in warps: break
                if (x, y) not in prev: prev[(x, y)] = p; dist[(x, y)] = dist[p] + 1; q.append((x, y))
        return dist, prev
    def reach(s, start, extra_block=(), ignore=()):
        return s._bfs(start, extra_block, ignore)[0]
    def can_take(s, d, p):
        """Item/NPC em p: alcancavel se algum vizinho foi alcancado."""
        return min([d[(p[0] + dx, p[1] + dy)] for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)) if (p[0] + dx, p[1] + dy) in d], default=None)
    def path(s, start, goal, extra_block=(), ignore=()):
        d, prev = s._bfs(start, extra_block, ignore)
        if goal not in prev: return None
        out = [goal]
        while prev[out[-1]]: out.append(prev[out[-1]])
        return out[::-1]
    # ---- saida
    def save(s, out, info, arts=(), estado=None, path=None):
        os.makedirs(out, exist_ok=True)
        write_blocks(os.path.join(out, 'map.bin'), s.g.b)
        write_blocks(os.path.join(out, 'border.bin'), [[pack_block(SNOW, 1)] * 2] * 2)
        npc = [o for o in s.objects if 'SPECIES' not in o['graphics_id']]
        bad = check_objects(s.g.flat(), s.w, npc)
        assert not bad, bad
        def render(objs, overlay=False, marks=(), blocks=None, pth=None):
            cv = render_blocks(blocks or s.g.flat(), s.w, s.h, LI['prim'], LI['sec'], overlay=overlay, marks=marks)
            for art, ax, ay in arts: art.over(cv, ax * 16, ay * 16)
            if pth:
                for (x0, y0), (x1, y1) in zip(pth, pth[1:]):
                    n = max(abs(x1 - x0), abs(y1 - y0)) * 16
                    for i in range(n + 1):
                        X = int((x0 + (x1 - x0) * i / max(n, 1)) * 16 + 8); Y = int((y0 + (y1 - y0) * i / max(n, 1)) * 16 + 8)
                        for d in (-1, 0, 1): cv[Y + d][X] = (255, 80, 200); cv[Y][X + d] = (255, 80, 200)
            for o in sorted(objs, key=lambda q: q['y']): draw_object(cv, o)
            return cv
        vis = [o for o in s.objects if not o.get('_estado')]
        write_png(os.path.join(out, 'dia.png'), render(vis), 2)
        mk = [((w['x'], w['y']), (200, 120, 255)) for w in s.warps] + s.marks
        write_png(os.path.join(out, 'colisao.png'), render(vis, True, mk, pth=path), 2)
        if estado:
            blocks, objs = estado
            write_png(os.path.join(out, 'estado.png'), render(objs, blocks=blocks), 2)
        objs_out = [{k: v for k, v in o.items() if not k.startswith('_')} for o in s.objects]
        info.update(w=s.w, h=s.h, primary=PRIM, secondary=SEC, warps=s.warps, objects=objs_out)
        json.dump(info, open(os.path.join(out, 'info.json'), 'w'), indent=1, ensure_ascii=False)
