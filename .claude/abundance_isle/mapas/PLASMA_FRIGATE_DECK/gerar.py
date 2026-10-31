import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
SRC = 'SSAqua_1F'
W, H = 37, 21
g = Grid(W, H, 0)
put(g, nine(SRC, 13, 0, 25, 21, W, H, cx=2, px=12, cy=0, py=1), 0, 0)
L = src(SRC)
def sv(x, y): return L['blocks'][y * L['w'] + x]
# bloco central (camarotes) refeito na largura nova: 16..45-12=33+12
X0, X1 = 16 - 13, 33 - 13 + 12
for x in range(X0, X1 + 1):
    L_, R_ = x == X0, x == X1
    win = (x - X0) % 4 == 3 and not (L_ or R_)
    g.raw(x, 9, sv(19, 9) if win else sv(17, 9))
    g.raw(x, 10, sv(16 if L_ else 33 if R_ else (19 if win else 17), 10))
    for y in range(11, 16): g.raw(x, y, sv(16 if L_ else 33 if R_ else 17, y))
    g.raw(x, 16, sv(16 if L_ else 33 if R_ else 17, 16))
    seq = [sv(17, 17), sv(18, 17), sv(19, 17), sv(20, 17)]
    g.raw(x, 17, sv(16, 17) if L_ else sv(33, 17) if R_ else seq[(x - X0 - 1) % 4])
# portas dos camarotes: sem mapa interno -> trancadas (o capacho vira chao)
DOORS_UP = [(x, 9) for x in range(W) if (g.b[9][x] & 0x7ff) == 0x515]
DOORS_DN = [(x, 17) for x in range(W) if (g.b[17][x] & 0x7ff) == 0x3d]
GANG = (29 + 12 - 13, 1)                      # prancha (era 29,1 no SS Aqua) -> cais da Windswept Cape
STAIRS = (36 + 12 - 13, 15)                   # escada para o porao
P = 'LOCALID_PLASMA_FRIGATE_DECK_'
def o(lid, gfx, x, y, face='DOWN', script='', ttype='TRAINER_TYPE_NONE', sight='0', mv=None):
    return {'local_id': P + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': mv or 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': '0'}
OBJ = [o('GRUNT_GANG', 'SCIENTIST_1', GANG[0], 6, 'DOWN', 'PlasmaFrigateDeck_EventScript_GangwayGuard', 'TRAINER_TYPE_NORMAL', '3'),
       o('GRUNT_N', 'SCIENTIST_1', 8, 8, 'RIGHT', 'PlasmaFrigateDeck_EventScript_Grunt1', 'TRAINER_TYPE_NORMAL', '5'),
       o('GRUNT_S', 'SCIENTIST_1', 24, 19, 'LEFT', 'PlasmaFrigateDeck_EventScript_Grunt2', 'TRAINER_TYPE_NORMAL', '5'),
       o('GRUNT_E', 'SCIENTIST_1', 34, 11, 'UP', 'PlasmaFrigateDeck_EventScript_Grunt3', 'TRAINER_TYPE_NORMAL', '3'),
       o('ROSA', 'ROSA', 2, 19, 'RIGHT', 'PlasmaFrigateDeck_EventScript_Rosa'),
       o('ITEM_WEST', 'ITEM_BALL', 1, 9, script='PlasmaFrigateDeck_EventScript_ItemFullRestore'),
       o('ITEM_STERN', 'ITEM_BALL', 35, 19, script='PlasmaFrigateDeck_EventScript_ItemPPUp')]
blocks = g.flat()
walk = lambda x, y: not (blocks[y * W + x] >> 11 & 1)
d = slide_reach((GANG[0], GANG[1] + 1), walk, lambda x, y: False, W, H)
nb = lambda c: min([d[n] for n in ((c[0], c[1] + 1), (c[0], c[1] - 1), (c[0] + 1, c[1]), (c[0] - 1, c[1]), c) if n in d], default=None)
rep = {'escada': nb(STAIRS), 'rosa': nb((2, 19)), 'item oeste': nb((1, 9)), 'item popa': nb((35, 19))}
print('bloqueio', check_objects(blocks, W, OBJ), rep, 'portas', DOORS_UP, DOORS_DN)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0x408, 1)] * 2] * 2)
LL = load_layout(SRC)
def R(objs, overlay=False, marks=()):
    cv = render_blocks(blocks, W, H, LL['prim'], LL['sec'], overlay=overlay, marks=marks)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
write_png(os.path.join(OUT, 'dia.png'), R(OBJ), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJ, True, [(GANG, (200, 120, 255)), (STAIRS, (200, 120, 255))] + [(p, (255, 230, 80)) for p in DOORS_UP + DOORS_DN]), 2)
info = {"map": "PLASMA_FRIGATE_DECK", "ingame": "Plasma Frigate", "w": W, "h": H,
        "primary": "gTileset_Johto_General_Hns", "secondary": "gTileset_ssaqua_Hns", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": GANG[0], "y": GANG[1], "dest_map": "MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE", "dest_warp_id": "1", "nota": "prancha; Cape (18,37)"},
                  {"x": STAIRS[0], "y": STAIRS[1], "dest_map": "MAP_PLASMA_FRIGATE_HOLD", "dest_warp_id": "0", "nota": "escada para o porão"},
                  {"x": 18, "y": 17, "dest_map": "MAP_PLASMA_FRIGATE_CABINS", "dest_warp_id": "0", "nota": "porta: aposentos do Ghetsis"},
                  {"x": 10, "y": 17, "dest_map": "MAP_PLASMA_FRIGATE_CABINS", "dest_warp_id": "1", "nota": "porta: vestiário do Plasma"}],
        "connections": [], "objects": OBJ,
        "explorar": ["Convés em anel ao redor dos camarotes: a prancha chega no alto e a escada do porão fica na popa, do lado oposto; quatro recrutas patrulham as duas voltas.",
                     "Camarotes: duas portas abrem (sul, x=10 vestiário e x=18 aposentos do Ghetsis, no mapa Cabins); as outras 12 são trancadas (amarelo no mapa de colisão).",
                     "Full Restore no canto oeste, PP Up na popa.",
                     "Rosa (protagonista do BW2) escondida no canto sudoeste: entrou no navio atrás dos DNA Splicers; cura a equipe e conta que o Colress-substituto guarda as notas no porão. Some depois do ato 4."],
        "historia": "Base de apoio do Neo Plasma, ancorada no cabo. Visita opcional entre os atos 2 e 4: aqui o jogador descobre o plano Kyurem Black.",
        "estados": {"dia": "Navio com a tripulação do Plasma."},
        "conferido": "check_objects sem bloqueio; BFS da prancha: %s" % json.dumps(rep)}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
