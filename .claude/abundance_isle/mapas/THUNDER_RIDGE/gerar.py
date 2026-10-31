import sys, os, json
B = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha'
sys.path.insert(0, B)
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
MW, MH = 36, 46
GR = JOHTO['grass']
g = Grid(MW, MH, pack_block(GR))
# ---------------- terracos de rocha (do mais baixo ao mais alto), escadas alternando lados
plateau(g, 0, 1, 35, 37)                          # nivel 1 (largo)
plateau(g, 3, 2, 32, 30, on='rock', base=False)   # nivel 2
plateau(g, 6, 3, 29, 20, on='rock', base=False)   # nivel 3 (o da torre)
for y in (36, 37): g.set(29, y, 137); g.set(30, y, 145)       # escada 1 (direita)
for y in (29, 30): g.set(6, y, 137); g.set(7, y, 145)         # escada 2 (esquerda)
for y in (19, 20): g.set(21, y, 137); g.set(22, y, 145)       # escada 3
# ---------------- base: mata e capim, boca de chegada (vinda do hub) num afloramento
for y in range(38, MH):
    for x in range(MW): g.set(x, y, GR)
plateau(g, 2, 39, 11, 43)
ARRIVE = (6, 43); g.set(*ARRIVE, 169, 0)
T = [['G'] * MW for _ in range(MH)]
for x0 in range(14, 28, 2):
    for y in range(40 + (x0 // 2) % 2, 45): T[y][x0] = T[y][x0 + 1] = 'F'
for y in range(MH):
    for x in range(MW):
        if T[y][x] == 'F': g.set(x, y, pick_forest(T, x, y), 1)
        else:
            b = tree_base(T, x, y)
            if b: g.set(x, y, b, 1)
for x in range(12, 14):
    for y in range(39, 45): g.set(x, y, 10)
for x in range(0, 2):
    for y in range(39, 46): g.set(x, y, 10)
for x in range(31, 36):
    for y in range(41, 46): g.set(x, y, 10)
# ---------------- nivel 3: torre (fachada da Burned Tower de Ecruteak) e arvores queimadas
FAC = (14, 4)
stamp(g, 'EcruteakCity', 20, 8, 5, 6, FAC[0] + 2, FAC[1] + 1)   # so o predio: arvores, cerca e vazio ficam de fora (rocha do plato por baixo)
DOOR = (FAC[0] + 4, FAC[1] + 6)                                # (22,13) no original
for x in range(FAC[0] + 1, FAC[0] + 8): g.set(x, FAC[1] + 7, 0xd9)
for x in range(FAC[0] + 3, FAC[0] + 6): g.set(x, FAC[1] + 8, 0xd9)
# afloramento dos raios (Thundurus) a leste do nivel 3, fechado por pedras quebraveis
for y in range(4, 20):                                          # crista de pedras separa o afloramento
    if y not in (11, 12): g.set(25, y, 167, 1)
SPOT = (27, 11)
# pedras e capim em cada nivel
for p in ((10, 33), (24, 32), (4, 27), (33, 28), (9, 14), (22, 23), (12, 24)): g.set(*p, 167, 1)
GRASS = [(x, y) for y in range(31, 35) for x in range(9, 20)] + [(x, y) for y in range(22, 27) for x in range(27, 31)] + \
        [(x, y) for y in range(15, 18) for x in range(8, 13)]
GRASS = []  # sem capim sobre a rocha (o johto_general nao tem capim alto de montanha)
for p in GRASS: g.set(*p, 10)
# ---------------- objetos
def o(lid, gfx, x, y, face='DOWN', script='', ttype='TRAINER_TYPE_NONE', sight='0', flag='0'):
    return {'local_id': 'LOCALID_THUNDER_RIDGE_' + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
OBJ = [
    o('HIKER', 'HIKER', 20, 34, 'LEFT', 'ThunderRidge_EventScript_Hiker', 'TRAINER_TYPE_NORMAL', '4'),
    o('BLACK_BELT', 'BLACK_BELT', 12, 22, 'RIGHT', 'ThunderRidge_EventScript_BlackBelt', 'TRAINER_TYPE_NORMAL', '4'),
    o('GRUNT', 'SCIENTIST_1', DOOR[0], DOOR[1] + 1, 'DOWN', 'ThunderRidge_EventScript_PlasmaGuard', 'TRAINER_TYPE_NORMAL', '3'),
    o('ROCK_1', 'BREAKABLE_ROCK', 25, 11, script='EventScript_RockSmash'),
    o('ROCK_2', 'BREAKABLE_ROCK', 25, 12, script='EventScript_RockSmash'),
    o('VOLKNER', 'VOLKNER', 9, 26, 'RIGHT', 'ThunderRidge_EventScript_Volkner', 'TRAINER_TYPE_NORMAL', '3'),
    o('ELESA', 'ELESA', 10, 27, 'UP', 'ThunderRidge_EventScript_Elesa', 'TRAINER_TYPE_NORMAL', '3'),
    o('ALDER', 'ALDER', 18, 14, 'DOWN', 'ThunderRidge_EventScript_Alder'),
    o('ITEM_TALLGRASS', 'ITEM_BALL', 1, 44, script='ThunderRidge_EventScript_ItemElectirizer'),
    o('ITEM_LEDGE', 'ITEM_BALL', 33, 26, script='ThunderRidge_EventScript_ItemMaxRevive'),
    o('ITEM_SPOT', 'ITEM_BALL', 28, 10, script='ThunderRidge_EventScript_ItemThunderStone'),
    o('ITEM_FOREST', 'ITEM_BALL', 34, 44, script='ThunderRidge_EventScript_ItemHiddenRareCandy'),
]
THUND = o('THUNDURUS', 'SPECIES(THUNDURUS)', *SPOT, 'LEFT', 'ThunderRidge_EventScript_Thundurus')
blocks = g.flat()
bad = check_objects(blocks, MW, OBJ + [THUND])
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1) or (blocks[y * MW + x] & 0x7ff) == 169
rocks = {(o_['x'], o_['y']) for o_ in OBJ if 'ROCK' in o_['local_id']}
d_closed = slide_reach((ARRIVE[0], ARRIVE[1] + 0), lambda x, y: walk(x, y) and (x, y) not in rocks, lambda x, y: False, MW, MH)
d_open = slide_reach(ARRIVE, walk, lambda x, y: False, MW, MH)
rep = {}
for name, c in (('porta da torre', DOOR), ('thundurus', SPOT)) + tuple((q['local_id'], (q['x'], q['y'])) for q in OBJ if 'ITEM' in q['local_id']):
    nb = [(c[0] + dx, c[1] + dy) for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0))]
    rep[name] = (min([d_closed[n] for n in nb if n in d_closed], default=None), min([d_open[n] for n in nb if n in d_open], default=None))
print('bloqueio:', bad); print('alcance (sem Rock Smash, com):', rep)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(GR)] * 2] * 2)
P = load_tileset('primary', 'johto_general'); SX = load_tileset('secondary', 'thunder_ridge')
def R(objs, overlay=False, marks=(), night=0.0):
    cv = render_blocks(blocks, MW, MH, P, SX, overlay=overlay, marks=marks, night=night)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob, night > .5)
    return cv
write_png(os.path.join(OUT, 'dia.png'), R(OBJ), 2)
write_png(os.path.join(OUT, 'estado.png'), R([q for q in OBJ if 'GRUNT' not in q['local_id']] + [THUND], night=0.6), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJ, True, [(ARRIVE, (200, 120, 255)), (DOOR, (200, 120, 255)), (SPOT, (255, 230, 80))]), 2)
info = {"map": "THUNDER_RIDGE", "ingame": "Thunder Ridge", "w": MW, "h": MH,
        "primary": "gTileset_Johto_General", "secondary": "gTileset_ThunderRidge", "map_type": "MAP_TYPE_ROUTE",
        "warps": [{"x": ARRIVE[0], "y": ARRIVE[1], "dest_map": "MAP_ABUNDANCE_ISLE", "dest_warp_id": "1", "nota": "boca de caverna; o hub a liga em (25,8)"},
                  {"x": DOOR[0], "y": DOOR[1], "dest_map": "MAP_THUNDERSPIRE_1F", "dest_warp_id": "0", "nota": "porta da torre"}],
        "connections": [],
        "objects": OBJ + [THUND],
        "explorar": ["Subida em zigue-zague por 3 terraços de rocha: cada escada fica do lado oposto da anterior.",
                     "No alto, a fachada da torre em ruínas cercada de árvores vermelhas, 'queimadas' pelos raios.",
                     "Afloramento dos raios a leste do último terraço, fechado por duas pedras de Rock Smash: Thunder Stone e o pouso do Thundurus.",
                     "Max Revive na beirada leste do 1º terraço, escondido atrás da quina do 2º.",
                     "Capim alto no pé do morro (Rare Candy no canto) e capim alto dos dois lados da boca da caverna (Electirizer).",
                     "Treinadores: Hiker e Black Belt nos terraços; recruta do Plasma guardando a porta da torre.",
                     "Volkner e Elesa no 2º terraço: vieram atrás dos raios e estudam a tempestade; batalha dupla opcional (dupla elétrica) depois do ato 2.",
                     "Alder, andarilho, descansa diante da torre: fala sobre ideais e verdades antes do jogador subir (prepara o encontro com o Zekrom)."],
        "historia": "Caminho do hub até a Thunderspire. No ato 1 os raios caem no afloramento e o recruta guarda a porta; no ato 3, com a máquina parada, o Thundurus exausto fica no afloramento para a batalha de captura.",
        "estados": {"dia": "Ato 1-2: recruta na porta, afloramento fechado por pedras.", "estado": "Ato 3 (entardecer): Thundurus caído no afloramento dos raios."},
        "conferido": "check_objects sem bloqueio; BFS da boca de chegada: %s" % json.dumps({k: v for k, v in rep.items()})}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
