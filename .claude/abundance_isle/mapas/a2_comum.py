import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
def o(lid, gfx, x, y, face='DOWN', script='', flag='0', ttype='TRAINER_TYPE_NONE', sight='0', elev=3, move=None):
    return {'local_id': lid, 'graphics_id': gfx if gfx.startswith('OBJ_') else 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y,
            'elevation': elev, 'movement_type': move or 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0,
            'movement_range_y': 0, 'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight,
            'script': script, 'flag': flag}
def bfs(blocks, w, h, start, extra_block=()):
    walk = lambda x, y: not (blocks[y * w + x] >> 11 & 1) and (blocks[y * w + x] >> 12) != 1 and (x, y) not in extra_block
    return slide_reach(start, walk, lambda x, y: False, w, h)
def bfs_surf(blocks, w, h, start, extra_block=()):
    walk = lambda x, y: not (blocks[y * w + x] >> 11 & 1) and (x, y) not in extra_block
    return slide_reach(start, walk, lambda x, y: False, w, h)
def entregar(pasta, g, prim, sec, info, objs, estado=None, estado_objs=None, render_kw=None):
    os.makedirs(pasta, exist_ok=True)
    write_blocks(os.path.join(pasta, 'map.bin'), g.b)
    b = g.flat(); kw = render_kw or {}
    cv = render_blocks(b, g.w, g.h, prim, sec, objects=objs, **kw)
    write_png(os.path.join(pasta, 'dia.png'), cv, 2)
    marks = [((wp['x'], wp['y']), (200, 120, 255)) for wp in info['warps']]
    write_png(os.path.join(pasta, 'colisao.png'), render_blocks(b, g.w, g.h, prim, sec, objects=objs, overlay=True, marks=marks, **kw), 2)
    if estado:
        write_png(os.path.join(pasta, 'estado.png'), estado(b) if callable(estado) else render_blocks(b, g.w, g.h, prim, sec, objects=estado_objs, **kw), 2)
    bad = check_objects(b, g.w, [x for x in objs + (estado_objs or []) if 'SS_TIDAL' not in x['graphics_id']])
    info.update(w=g.w, h=g.h, objects=objs + [x for x in (estado_objs or []) if x not in objs])
    json.dump(info, open(os.path.join(pasta, 'info.json'), 'w'), indent=1, ensure_ascii=False)
    print(info['map'], g.w, 'x', g.h, 'check_objects:', bad)
    return bad
def alcanca(d, ob):
    x, y = ob['x'], ob['y']
    return any(p in d for p in ((x, y), (x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)))
