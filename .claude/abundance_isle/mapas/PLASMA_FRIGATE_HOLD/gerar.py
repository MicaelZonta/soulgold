import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
SRC = 'SSAqua_B1F'
W, H = 40, 16
g = Grid(W, H, 0)
put(g, nine(SRC, 0, 0, 34, 16, W, H, cx=17, px=6, cy=0, py=1), 0, 0)   # alojamento alargado (beliches em periodo 3)
SH = W - 34
ARRIVE = (30 + SH, 12)          # escada da direita: vem do convés
ENGINE = (3, 12)                # escada da esquerda: casa de máquinas (trancada)
P = 'LOCALID_PLASMA_FRIGATE_HOLD_'
def o(lid, gfx, x, y, face='DOWN', script='', ttype='TRAINER_TYPE_NONE', sight='0'):
    return {'local_id': P + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': '0'}
OBJ = [o('ENGINE_GUARD', 'SCIENTIST_1', 3, 11, 'DOWN', 'PlasmaFrigateHold_EventScript_EngineGuard'),
       o('RESEARCHER', 'SCIENTIST_1', 7, 10, 'RIGHT', 'PlasmaFrigateHold_EventScript_Researcher', 'TRAINER_TYPE_NORMAL', '2'),
       o('GRUNT_BUNK_1', 'SCIENTIST_1', 17, 11, 'RIGHT', 'PlasmaFrigateHold_EventScript_Grunt4', 'TRAINER_TYPE_NORMAL', '3'),
       o('GRUNT_BUNK_2', 'SCIENTIST_1', 28, 14, 'LEFT', 'PlasmaFrigateHold_EventScript_Grunt5', 'TRAINER_TYPE_NORMAL', '4'),
       o('GRUNT_HALL', 'SCIENTIST_1', 14, 4, 'RIGHT', 'PlasmaFrigateHold_EventScript_Grunt6', 'TRAINER_TYPE_NORMAL', '6'),
       o('ITEM_LAB', 'ITEM_BALL', 12, 14, script='PlasmaFrigateHold_EventScript_ItemDuskBall'),
       o('ITEM_BUNK', 'ITEM_BALL', 31, 11, script='PlasmaFrigateHold_EventScript_ItemNeverMeltIce'),
       o('ITEM_HALL', 'ITEM_BALL', 1, 3, script='PlasmaFrigateHold_EventScript_ItemMaxElixir')]
blocks = g.flat()
walk = lambda x, y: not (blocks[y * W + x] >> 11 & 1) and (x, y) != (3, 11)
d = slide_reach(ARRIVE, walk, lambda x, y: False, W, H)
nb = lambda c: min([d[n] for n in ((c[0], c[1] + 1), (c[0], c[1] - 1), (c[0] + 1, c[1]), (c[0] - 1, c[1]), c) if n in d], default=None)
rep = {q['local_id'].replace(P, ''): nb((q['x'], q['y'])) for q in OBJ}
print('bloqueio', check_objects(blocks, W, OBJ), rep)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0x408, 1)] * 2] * 2)
LL = load_layout(SRC)
def R(objs, overlay=False, marks=()):
    cv = render_blocks(blocks, W, H, LL['prim'], LL['sec'], overlay=overlay, marks=marks)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
write_png(os.path.join(OUT, 'dia.png'), R(OBJ), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJ, True, [(ARRIVE, (200, 120, 255)), (ENGINE, (200, 120, 255))]), 2)
info = {"map": "PLASMA_FRIGATE_HOLD", "ingame": "Plasma Frigate Hold", "w": W, "h": H,
        "primary": "gTileset_Johto_General_Hns", "secondary": "gTileset_ssaqua_Hns", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": ARRIVE[0], "y": ARRIVE[1], "dest_map": "MAP_PLASMA_FRIGATE_DECK", "dest_warp_id": "1", "nota": "escada do convés (Deck 35,15)"},
                  {"x": ENGINE[0], "y": ENGINE[1], "dest_map": "MAP_PLASMA_FRIGATE_ENGINE_ROOM", "dest_warp_id": "0", "nota": "casa de máquinas / DNA Lab; o guarda só sai da frente com o uniforme Plasma"}],
        "connections": [], "objects": OBJ,
        "explorar": ["Porão em U: corredor roxo por cima, laboratório à esquerda, alojamento comprido no meio, escada do convés à direita.",
                     "Laboratório (as mesas do refeitório viram bancadas): o pesquisador do Plasma tem as notas do 'Projeto Ideal Negro' — fundir Zekrom e Kyurem com os DNA Splicers — e luta para protegê-las. Dusk Ball no canto.",
                     "Alojamento com fileiras de beliches: Never-Melt Ice esquecido entre as camas; dois recrutas de folga.",
                     "Max Elixir no canto noroeste do corredor, vigiado por um recruta de visão longa.",
                     "Escada da casa de máquinas guardada: 'Authorized personnel only.' Com o uniforme Plasma (missão Undercover da Rosa) o guarda deixa passar para o DNA Lab."],
        "historia": "Onde o jogador lê o plano do Ghetsis por escrito (Kyurem Black). Opcional, mas dá a recompensa e o contexto antes do cume.",
        "estados": {"dia": "Tripulação do Plasma a bordo."},
        "conferido": "check_objects sem bloqueio; BFS da escada do convés: %s" % json.dumps(rep)}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
