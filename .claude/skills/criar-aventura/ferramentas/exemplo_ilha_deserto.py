import os
"""Emberdune Isle v2: ilha de areia em dois niveis, como a VajraDesertEast. Planalto de areia escura ao norte
(chegada pelo mar), paredao de 7 linhas atravessando a ilha com escada e a boca das Truthsand Ruins, deserto
claro ao sul com oasis, casa do N, pocos de areia movedica, cactos, dunas e ossadas. Agua com a borda marrom
desenhada na propria celula de agua (pecas aprendidas da VajraDesertEast)."""
import sys, os, json, math
SC = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SC)
from kit_aventura import *
OUT = os.path.dirname(os.path.abspath(__file__))
MW, MH = 40, 46
DARK, PALE, DGRASS, PGRASS = 0x575, 0x408, 0x589, 0x410
B0 = 18                                                   # linha do aro do paredao (7 linhas: 18..24)
# ------------------------------------------------------------ forma da ilha (costa irregular, suavizada)
land = [[False] * MW for _ in range(MH)]
for y in range(MH):
    for x in range(MW):
        a = math.atan2(y - 23.5, x - 19.5)
        r = 1 + 0.07 * math.sin(3 * a + 0.6) + 0.05 * math.sin(5 * a + 2.0)
        dx, dy = (x + .5 - 19.5) / (18.2 * r), (y + .5 - 23.5) / (21.2 * r)
        land[y][x] = abs(dx) ** 3.2 + abs(dy) ** 3.2 <= 1
for _ in range(2):                                        # tira pontas de 1 celula (abre e fecha)
    nl = [[land[y][x] and sum(land[y + dy][x + dx] for dx, dy in NB8 if 0 <= y + dy < MH and 0 <= x + dx < MW) >= 4
           for x in range(MW)] for y in range(MH)]
    land = [[nl[y][x] or (sum(nl[y + dy][x + dx] for dx, dy in NB8 if 0 <= y + dy < MH and 0 <= x + dx < MW) >= 6)
             for x in range(MW)] for y in range(MH)]
L = lambda x, y: 0 <= x < MW and 0 <= y < MH and land[y][x]
g = Grid(MW, MH, pack_block(JOHTO['water'], 0, 1))
def lip(x, y):
    n, s, w, e = L(x, y - 1), L(x, y + 1), L(x - 1, y), L(x + 1, y)
    if n and e: return 0x517
    if n and w: return 0x516
    if s and e: return 0x580
    if s and w: return 0x581
    if n: return 0x123
    if s: return 0x582
    if w: return 0x12a
    if e: return 0x12c
    if L(x + 1, y - 1): return 0x130
    if L(x - 1, y - 1): return 0x131
    return JOHTO['water']
for y in range(MH):
    for x in range(MW):
        if land[y][x]: g.set(x, y, DARK if y < B0 else PALE)
        else: g.set(x, y, lip(x, y), 0, 1)
# ------------------------------------------------------------ paredao com escada e boca das ruinas
FACE = [0x56e, 0x437, 0x42a, 0x43a, 0x42a, 0x432, 0x43a]
STAIRS = (31, 32, 33)
for k, m in enumerate(FACE):
    for x in range(MW):
        if L(x, B0 + k):
            if x in STAIRS: g.set(x, B0 + k, DARK if k == 0 else (0x89 if x == STAIRS[0] else 0x91), 0)
            else: g.set(x, B0 + k, m, 1)
RUINS = [(19, B0 + 6), (20, B0 + 6)]
g.set(19, B0 + 5, 0x41e, 1); g.set(20, B0 + 5, 0x41f, 1); g.set(19, B0 + 6, 0x426, 0); g.set(20, B0 + 6, 0x427, 0)
# ------------------------------------------------------------ enfeites (pecas da VajraDesertEast)
def put_block(x, y, rows, walk_top=False):
    for dy, row in enumerate(rows):
        for dx, m in enumerate(row):
            if m is not None and L(x + dx, y + dy): g.set(x + dx, y + dy, m, 0 if (walk_top and dy == 0) else 1)
PALM_D = ((0x57d, 0x57e), (0x585, 0x586), (0x58d, 0x58e))
PALM_P = ((0x48e, 0x48f), (0x496, 0x497), (0x49e, 0x49f))
CACTUS = ((0x414, 0x415), (0x41c, 0x41d), (0x424, 0x425))
DUNE = ((0x4b0, 0x4b1), (0x4b8, 0x4b9))
def palm(x, y, dark): put_block(x, y, PALM_D if dark else PALM_P, walk_top=True)
def patch(cells, m):
    for x, y in cells:
        if L(x, y) and (g.b[y][x] & 0x7ff) in (DARK, PALE): g.set(x, y, m)
def blob(cx, cy, rx, ry, seed=0):
    return [(x, y) for y in range(cy - ry, cy + ry + 1) for x in range(cx - rx, cx + rx + 1)
            if ((x - cx) / (rx + .5)) ** 2 + ((y - cy) / (ry + .5)) ** 2 + 0.25 * math.sin(x * 1.7 + y * 2.3 + seed) <= 1]
# planalto escuro: dois bosques de palmeiras e capim escuro
for p in ((6, 6), (8, 7), (4, 9), (7, 10), (29, 6), (31, 7), (33, 9), (27, 9)): palm(*p, True)
patch(blob(15, 9, 3, 1, 1), DGRASS); patch(blob(23, 12, 3, 1, 2), DGRASS); patch(blob(11, 14, 2, 1, 3), DGRASS); patch(blob(30, 14, 2, 1, 7), DGRASS)
for p in ((19, 5), (13, 4), (26, 4)): palm(*p, True)
# deserto claro
OASIS = (4, 33, 10, 37)                                    # lago do oasis (agua com borda)
for x, y in blob(7, 35, 3, 2, 9) + [(5, 35), (9, 35), (7, 33), (7, 37)]:
    land[y][x] = False
for y in range(OASIS[1] - 1, OASIS[3] + 2):
    for x in range(OASIS[0] - 1, OASIS[2] + 2):
        if not land[y][x]: g.set(x, y, lip(x, y), 0, 1)
NS_HOUSE = (5, 27); stamp(g, 'RintoVillage', 19, 28, 4, 5, *NS_HOUSE); NS_DOOR = (NS_HOUSE[0] + 1, NS_HOUSE[1] + 4)
for p in ((2, 28), (11, 30), (12, 34), (3, 38), (9, 39)): palm(*p, False)
for p in ((24, 37), (34, 27), (15, 39), (29, 40)): put_block(*p, CACTUS, walk_top=True)
for p in ((14, 28), (27, 31), (21, 41)): put_block(*p, DUNE)
for p, m in (((23, 27), 0x407), ((36, 32), 0x40f), ((17, 36), 0x407), ((32, 37), 0x438), ((13, 32), 0x438)):
    if L(*p): g.set(*p, m, 1)
patch(blob(29, 34, 3, 2, 4), PGRASS); patch(blob(16, 30, 2, 1, 5), PGRASS); patch(blob(8, 41, 3, 1, 6), PGRASS)
def pit(x, y, open_bottom=False):                         # poco de areia movedica 4x3 (pecas da DesertVillage)
    for dy, row in enumerate(((0x488, 0x489, 0x492, 0x493), (0x490, 0x491, 0x49a, 0x49b), (0x498, 0x499, 0x49c, 0x49d))):
        for dx, m in enumerate(row): g.set(x + dx, y + dy, m, 0 if (dy == 1 and dx in (1, 2)) or (open_bottom and dy == 2 and dx in (1, 2)) else 1)
PITS = [(23, 30), (30, 29)]
for p in PITS: pit(*p)
pit(17, 33, open_bottom=True); SECRET_PIT = (18, 34)
for rx, ry in ((1, 1), (35, 2), (37, 42), (1, 43)):
    if all(not L(rx + dx, ry + dy) for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']): g.set(rx + dx, ry + dy, mid, 1, 1)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
blocks = g.flat()
def o(lid, gfx, x, y, face='DOWN', script='0x0', ttype='TRAINER_TYPE_NONE', sight='0', elev=3, flag='0'):
    return {'local_id': 'LOCALID_EMBERDUNE_ISLE_' + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': elev,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0, 'trainer_type': ttype,
            'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
north = min(y for y in range(MH) if L(19, y))
OBJS = [
    o('HILDA', 'HILDA', 18, north + 1, 'DOWN', 'EmberduneIsle_EventScript_Hilda'),
    o('LENORA', 'LENORA', 21, north + 1, 'DOWN', 'EmberduneIsle_EventScript_Lenora'),
    o('DIGGER_1', 'SCIENTIST_1', 18, B0 + 7, 'UP', 'EmberduneIsle_EventScript_Digger1', 'TRAINER_TYPE_NORMAL', '3'),
    o('DIGGER_2', 'SCIENTIST_1', 21, B0 + 7, 'UP', 'EmberduneIsle_EventScript_Digger2', 'TRAINER_TYPE_NORMAL', '3'),
    o('BEA', 'BEA', 26, 35, 'LEFT', 'EmberduneIsle_EventScript_Bea'),
    o('GRETA', 'GRETA', 35, 30, 'LEFT', 'EmberduneIsle_EventScript_Greta'),
    o('HIKER', 'HIKER', 24, 13, 'LEFT', 'EmberduneIsle_EventScript_Hiker', 'TRAINER_TYPE_NORMAL', '3'),
    o('RUIN_MANIAC', 'HIKER', 30, B0 - 1, 'RIGHT', 'EmberduneIsle_EventScript_RuinManiac', 'TRAINER_TYPE_NORMAL', '3'),
    o('ITEM_BONES', 'ITEM_BALL', 36, 33, script='EmberduneIsle_EventScript_ItemHeatRock'),
    o('ITEM_OASIS', 'ITEM_BALL', 5, 12, script='EmberduneIsle_EventScript_ItemSunStone'),
    o('ITEM_CORNER', 'ITEM_BALL', 9, 42, script='EmberduneIsle_EventScript_ItemSoftSand'),
    o('ITEM_MESA', 'ITEM_BALL', 3, 16, script='EmberduneIsle_EventScript_ItemFireStone'),
]
bad = check_objects(blocks, MW, OBJS)
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1) and (blocks[y * MW + x] >> 12) != 1
d = slide_reach((19, north), walk, lambda x, y: False, MW, MH)
def near_ok(ob): return any((ob['x'] + dx, ob['y'] + dy) in d for dx, dy in ((0, 0), (0, 1), (0, -1), (1, 0), (-1, 0)))
reach = {ob['local_id'][23:]: near_ok(ob) for ob in OBJS}
print('bloqueio/agua:', bad); print('alcance a pe da praia norte:', reach)
print('ruinas', all(p in d for p in RUINS), 'poco secreto', SECRET_PIT in d, 'casa do N', (NS_DOOR[0], NS_DOOR[1] + 1) in d)
P = load_tileset('primary', 'johto_general'); Sx = load_tileset('secondary', 'desert_village')
def R(objs, **kw): return render_blocks(blocks, MW, MH, P, Sx, objects=objs, **kw)
base = [ob for ob in OBJS if ob['local_id'][23:] not in ('HILDA', 'LENORA')]
write_png(os.path.join(OUT, 'dia.png'), R(base), 2)
write_png(os.path.join(OUT, 'estado.png'), R(OBJS), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJS, overlay=True, marks=[(p, (200, 120, 255)) for p in RUINS + [SECRET_PIT, NS_DOOR]]), 2)
info = json.load(open(os.path.join(OUT, 'info_v1.json')))
info.update(w=MW, h=MH, objects=OBJS,
    warps=[dict(x=19, y=B0 + 6, dest_map='MAP_TRUTHSAND_RUINS_1F', dest_warp_id='0', nota='boca das ruinas (esquerda); indice 0'),
           dict(x=20, y=B0 + 6, dest_map='MAP_TRUTHSAND_RUINS_1F', dest_warp_id='0', nota='boca das ruinas (direita)'),
           dict(x=SECRET_PIT[0], y=SECRET_PIT[1], dest_map='MAP_TRUTHSAND_RUINS_B1F', dest_warp_id='3', nota='poco secreto: queda de mao unica'),
           dict(x=SECRET_PIT[0] + 1, y=SECRET_PIT[1], dest_map='MAP_TRUTHSAND_RUINS_B1F', dest_warp_id='3', nota='idem'),
           dict(x=NS_DOOR[0], y=NS_DOOR[1], dest_map='MAP_NS_ROOM', dest_warp_id='0', nota='porta da casinha do N (oasis)')],
    explorar=['Dois niveis como a VajraDesertEast: planalto de areia escura ao norte (chegada pelo mar) e deserto claro ao sul.',
              'Paredao de 7 linhas atravessa a ilha; a unica descida e a escada do leste, que obriga a contornar o planalto.',
              'Boca das Truthsand Ruins escavada no meio do paredao; dois escavadores do Plasma guardam a entrada.',
              'Bosques de palmeiras nos dois cantos do planalto (Sun Stone escondida no do oeste) e capim escuro com encontros.',
              'Oasis no sudoeste com o lago e a casinha do N (o quarto de brinquedos).',
              'Tres pocos de areia movedica; o do meio derruba direto no B1F das ruinas (atalho secreto).',
              'Cactos, dunas, ossadas e capim claro no deserto; Heat Rock perto da ossada leste, Soft Sand no sul, Fire Stone na ponta oeste do planalto.',
              'Bea treina no calor do deserto; Greta desafia quem venceu os escavadores; o maniaco por ruinas conta a lenda no alto da escada.'],
    conferido='check_objects: %s; BFS a pe da praia norte: NPCs/itens %s, boca das ruinas %s, poco secreto %s, casa do N %s' % (
        bad, all(reach.values()), all(p in d for p in RUINS), SECRET_PIT in d, (NS_DOOR[0], NS_DOOR[1] + 1) in d))
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
