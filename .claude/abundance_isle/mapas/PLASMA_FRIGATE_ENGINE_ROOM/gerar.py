import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
SRC = 'Route10_PowerPlantBackRoom'
W, H = 26, 16
g = Grid(W, H, 0)
put(g, nine(SRC, 0, 0, 18, 14, W, H, cx=8, px=1, cy=10, py=1), 0, 0)
L = src(SRC); sv = lambda x, y: L['blocks'][y * L['w'] + x]
DX = W - 18; DY = H - 14
ARRIVE = (12 + DX, 13 + DY)                    # capacho de baixo: escada que vem do porao
# segundo condensador de frio (o gerador 3x4 do original repetido a direita): "DNA Lab"
for y in range(2, 6):
    for x in range(10, 13): g.raw(x + DX - 3, y, sv(x, y))
# barris de refrigerante: fecham o canto sudoeste; o item fica num nicho so alcancavel pela fresta da parede (coluna 2)
bar = [sv(3, 10), sv(4, 10), sv(5, 10)], [sv(3, 11), sv(4, 11), sv(5, 11)]
BARRELS = [(x, 12) for x in range(3, 7)] + [(x, 13) for x in range(2, 7)]
for (x, y) in BARRELS: g.raw(x, y, bar[y - 12][(x - 2) % 3])
NOOK = (2, 12)
P = 'LOCALID_PLASMA_FRIGATE_ENGINE_ROOM_'
def o(lid, gfx, x, y, face='DOWN', script='', ttype='TRAINER_TYPE_NONE', sight='0'):
    return {'local_id': P + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': '0'}
OBJ = [o('CHIEF', 'SCIENTIST_1', 13, 5, 'DOWN', 'PlasmaFrigateEngine_EventScript_ChiefScientist', 'TRAINER_TYPE_NORMAL', '3'),
       o('ASSIST_1', 'SCIENTIST_1', 5, 7, 'UP', 'PlasmaFrigateEngine_EventScript_Assistant1', 'TRAINER_TYPE_NORMAL', '4'),
       o('ASSIST_2', 'SCIENTIST_1', 22, 11, 'LEFT', 'PlasmaFrigateEngine_EventScript_Assistant2', 'TRAINER_TYPE_NORMAL', '4'),
       o('ITEM_BARRELS', 'ITEM_BALL', *NOOK, script='PlasmaFrigateEngine_EventScript_ItemIceStone'),
       o('ITEM_CONSOLE', 'ITEM_BALL', 22, 3, script='PlasmaFrigateEngine_EventScript_ItemUpGrade')]
blocks = g.flat()
walk = lambda x, y: not (blocks[y * W + x] >> 11 & 1)
d = slide_reach(ARRIVE, walk, lambda x, y: False, W, H)
nb = lambda c: min([d[n] for n in ((c[0], c[1] + 1), (c[0], c[1] - 1), (c[0] + 1, c[1]), (c[0] - 1, c[1]), c) if n in d], default=None)
rep = {q['local_id'].replace(P, ''): nb((q['x'], q['y'])) for q in OBJ}
print('bloqueio', check_objects(blocks, W, OBJ), rep)
for y in range(H): print(''.join('o' if (x, y) in d else ('#' if blocks[y * W + x] >> 11 & 1 else '.') for x in range(W)))
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0x8, 1)] * 2] * 2)
LL = load_layout(SRC)
def R(objs, overlay=False, marks=()):
    cv = render_blocks(blocks, W, H, LL['prim'], LL['sec'], overlay=overlay, marks=marks)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
write_png(os.path.join(OUT, 'dia.png'), R(OBJ), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJ, True, [(ARRIVE, (200, 120, 255)), (NOOK, (255, 230, 80))]), 2)
json.dump(dict(rep=rep, arrive=ARRIVE), open(os.path.join(OUT, '_tmp.json'), 'w'))
os.remove(os.path.join(OUT, '_tmp.json'))
info = {"map": "PLASMA_FRIGATE_ENGINE_ROOM", "ingame": "Plasma Frigate Engine Room", "w": W, "h": H,
        "primary": "gTileset_Johto_Building_Hns", "secondary": "gTileset_PowerPlant_GeneratorRoom_Hns", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": ARRIVE[0], "y": ARRIVE[1], "dest_map": "MAP_PLASMA_FRIGATE_HOLD", "dest_warp_id": "1", "nota": "capacho: escada da casa de máquinas do Hold (3,12)"}],
        "connections": [], "objects": OBJ,
        "bg_events": [{"type": "sign", "x": 19, "y": 8, "script": "PlasmaFrigateEngine_EventScript_DNAConsole", "nota": "consoles: dados dos DNA Splicers"},
                      {"type": "sign", "x": 11, "y": 4, "script": "PlasmaFrigateEngine_EventScript_ColdCondenser", "nota": "condensadores: amostra do frio do meteorito"},
                      {"type": "sign", "x": 1, "y": 4, "script": "PlasmaFrigateEngine_EventScript_ColdStorageDoor", "nota": "porta vermelha trancada (câmara fria)"}],
        "explorar": ["Casa de máquinas virada laboratório: dois condensadores puxam o frio da amostra do meteorito (o mesmo que a Frostfall Crater bombeia); consoles com os dados de fusão dos DNA Splicers.",
                     "Salão de baixo e galeria de cima ligados por um corredor estreito guardado por um assistente.",
                     "Cientista-chefe do Plasma diante dos condensadores: batalha; depois explica que a fusão só funciona com o Zekrom desperto.",
                     "Nicho atrás da pilha de barris, alcançado só pela fresta da parede oeste: Ice Stone.",
                     "Up-Grade no canto da galeria, atrás dos condensadores.",
                     "Porta vermelha da câmara fria trancada (gancho futuro)."],
        "historia": "Coração técnico do Plasma no navio: liga a cratera (frio) ao plano do cume (fusão). Só se entra com o uniforme da missão 'Undercover' da Rosa.",
        "estados": {"dia": "Equipe científica a bordo."},
        "conferido": "check_objects sem bloqueio; BFS do capacho: %s" % json.dumps(rep)}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
