import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
def o(lid, gfx, x, y, face='DOWN', script='', flag='0', ttype='TRAINER_TYPE_NONE', sight='0', elev=3):
    return {'local_id': lid, 'graphics_id': gfx if gfx.startswith('OBJ_') else 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y,
            'elevation': elev, 'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
def ilex_forest(g, T, F='T'):
    """Arvores do IlexForest em colunas de 3 (x%3 = esquerda/meio/direita). Sequencia vertical de cada
    trecho: topo 408 | 410,418 alternando | 420 | 428 (sombra). Trecho que encosta na borda do mapa nao tem topo/fim."""
    H, W = len(T), len(T[0]); warn = []
    for x in range(W):
        y = 0
        while y < H:
            if T[y][x] != F: y += 1; continue
            a = y
            while y < H and T[y][x] == F: y += 1
            b = y - 1
            for yy in range(a, b + 1):
                k = b - yy if b < H - 1 else None
                if k is None:                                   # encosta embaixo: so preenchimento
                    base = 0x418 if (yy - a) % 2 == (0 if a == 0 else 1) else 0x410
                    if a > 0 and yy == a: base = 0x408
                elif k == 0: base = 0x428
                elif k == 1: base = 0x420
                elif yy == a and a > 0: base = 0x408
                else: base = 0x418 if k % 2 == 0 else 0x410
                g.set(x, yy, base + x % 3, 1)
            if a > 0 and b < H - 1 and (b - a + 1) % 2 == 0: warn.append((x, a, b))
    return warn
def bfs(blocks, W, H, start):
    walk = lambda x, y: not (blocks[y * W + x] >> 11 & 1)
    return slide_reach(start, walk, lambda x, y: False, W, H)
