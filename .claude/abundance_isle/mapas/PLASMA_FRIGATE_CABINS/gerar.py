import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
SRC = 'SSAqua_CaptainsRoom'
L = src(SRC)
sv = lambda x, y: L['blocks'][y * L['w'] + x]
W, H = 25, 11
g = Grid(W, H, pack_block(0x408, 1))
# ---- camarote 1: aposentos do Ghetsis (o camarote do capitao, com a escrivaninha e o diario)
put(g, nine(SRC, 0, 0, 11, 10, 11, 10), 0, 0)
GH_DOOR = (5, 9)
# ---- camarote 2: vestiario do Plasma (mesma casca, mais larga, parede de armarios)
X2 = 12
put(g, nine(SRC, 0, 0, 11, 10, 13, 10, cx=5, px=1, cy=5, py=1), X2, 0)
for y in range(2, 9):
    for x in range(X2 + 1, X2 + 12): g.raw(x, y, sv(2, 5) if x > X2 + 1 else sv(1, 5))
for x in range(X2 + 1, X2 + 12): g.raw(x, 2, sv(1, 2) if x == X2 + 1 else sv(2, 2))
# fundo: parede lisa com fileira de armarios (a estante alta do camarote) e dois beliches nas pontas
for x in range(X2 + 1, X2 + 12): g.raw(x, 1, sv(1, 1))
LOCKERS = list(range(X2 + 4, X2 + 10))
for x in LOCKERS: g.raw(x, 1, sv(7, 1)); g.raw(x, 2, sv(7, 2))
for bx in (X2 + 1, X2 + 10):
    g.raw(bx, 2, sv(8, 2)); g.raw(bx + 1, 2, sv(9, 2)); g.raw(bx, 3, sv(8, 3)); g.raw(bx + 1, 3, sv(9, 3))
# bancos no meio (as cadeiras amarelas do camarote)
for x in (X2 + 4, X2 + 7): g.raw(x, 6, sv(9, 6)); g.raw(x, 7, sv(9, 7))
LK_DOOR = (X2 + 6, 9)
for x in range(X2 + 1, X2 + 12): g.raw(x, 9, sv(1, 9))
g.raw(*LK_DOOR, sv(5, 9))
P = 'LOCALID_PLASMA_FRIGATE_CABINS_'
def o(lid, gfx, x, y, face='DOWN', script='', ttype='TRAINER_TYPE_NONE', sight='0'):
    return {'local_id': P + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': '0'}
OBJ = [o('GHETSIS_GUARD', 'SCIENTIST_1', 2, 6, 'RIGHT', 'PlasmaFrigateCabins_EventScript_QuartersGuard', 'TRAINER_TYPE_NORMAL', '4'),
       o('ITEM_QUARTERS', 'ITEM_BALL', 8, 7, script='PlasmaFrigateCabins_EventScript_ItemRareCandy'),
       o('GRUNT_LOCKER_1', 'SCIENTIST_1', X2 + 3, 5, 'RIGHT', 'PlasmaFrigateCabins_EventScript_LockerGrunt1', 'TRAINER_TYPE_NORMAL', '3'),
       o('GRUNT_LOCKER_2', 'SCIENTIST_1', X2 + 10, 7, 'LEFT', 'PlasmaFrigateCabins_EventScript_LockerGrunt2', 'TRAINER_TYPE_NORMAL', '3')]
BG = [{'type': 'sign', 'x': 5, 'y': 4, 'script': 'PlasmaFrigateCabins_EventScript_GhetsisDiary', 'nota': 'diário na escrivaninha'},
      {'type': 'sign', 'x': 7, 'y': 2, 'script': 'PlasmaFrigateCabins_EventScript_GhetsisPlans', 'nota': 'estante: planos do Kyurem Black'},
      {'type': 'sign', 'x': X2 + 8, 'y': 2, 'script': 'PlasmaFrigateCabins_EventScript_UniformLocker', 'nota': 'armário do uniforme (missão Undercover)'}]
blocks = g.flat()
walk = lambda x, y: not (blocks[y * W + x] >> 11 & 1)
rep = {}
for nome, door, alvos in (('aposentos', GH_DOOR, {'diario (frente)': (5, 5), 'item': (8, 7), 'guarda': (2, 6)}),
                          ('vestiario', LK_DOOR, {'armario uniforme (frente)': (X2 + 8, 3), 'grunt1': (X2 + 3, 5), 'grunt2': (X2 + 10, 7)})):
    d = slide_reach(door, walk, lambda x, y: False, W, H)
    for k, c in alvos.items():
        rep[nome + ':' + k] = min([d[n] for n in ((c[0], c[1] + 1), (c[0], c[1] - 1), (c[0] + 1, c[1]), (c[0] - 1, c[1]), c) if n in d], default=None)
print('bloqueio', check_objects(blocks, W, OBJ), rep)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0x408, 1)] * 2] * 2)
LL = load_layout(SRC)
def R(objs, overlay=False, marks=()):
    cv = render_blocks(blocks, W, H, LL['prim'], LL['sec'], overlay=overlay, marks=marks)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
write_png(os.path.join(OUT, 'dia.png'), R(OBJ), 3)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJ, True, [(GH_DOOR, (200, 120, 255)), (LK_DOOR, (200, 120, 255))] + [((b['x'], b['y']), (255, 230, 80)) for b in BG]), 3)
info = {"map": "PLASMA_FRIGATE_CABINS", "ingame": "Plasma Frigate Cabins", "w": W, "h": H,
        "primary": "gTileset_Johto_General_Hns", "secondary": "gTileset_ssaqua_Hns", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": GH_DOOR[0], "y": GH_DOOR[1], "dest_map": "MAP_PLASMA_FRIGATE_DECK", "dest_warp_id": "2", "nota": "aposentos do Ghetsis <- porta do Deck (18,17)"},
                  {"x": LK_DOOR[0], "y": LK_DOOR[1], "dest_map": "MAP_PLASMA_FRIGATE_DECK", "dest_warp_id": "3", "nota": "vestiário <- porta do Deck (10,17)"}],
        "connections": [], "objects": OBJ, "bg_events": BG,
        "explorar": ["Dois camarotes no mesmo mapa, cada um com a sua porta no convés; as outras 12 portas do convés continuam trancadas.",
                     "Aposentos do Ghetsis: o diário na escrivaninha (a 'profecia da Spire': o raio que desperta o herói negro) e, na estante, os planos do Kyurem Black. Um guarda; Rare Candy no canto.",
                     "Vestiário do Plasma: parede de armários e bancos; no armário marcado está o uniforme Plasma da missão 'Undercover' da Rosa — com ele os recrutas do porão deixam o jogador passar sem lutar.",
                     "Dois recrutas trocando de turno no vestiário."],
        "historia": "Onde o jogador lê, da mão do Ghetsis, o plano inteiro (profecia da Spire, Kyurem Black) e pega o disfarce que a Rosa pediu.",
        "estados": {"dia": "Tripulação a bordo."},
        "conferido": "check_objects sem bloqueio; BFS de cada porta: %s" % json.dumps(rep)}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
