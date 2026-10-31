"""Sunset Strait: rota de mar entre a Harvest Fields (norte) e a Emberdune Isle (sul).
Ilhotas de praia, recifes, um rochedo com a gruta do Shrine of the First Dragon."""
import sys, os, json
SC = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha'
sys.path.insert(0, SC)
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
MW, MH = 40, 56
W_, S_, G_, F_, X_ = 'W', 'S', 'G', 'F', 'X'
T = [[W_] * MW for _ in range(MH)]
def blob(cx, cy, rx, ry, p=3.0):
    for y in range(MH):
        for x in range(MW):
            if abs((x + .5 - cx) / rx) ** p + abs((y + .5 - cy) / ry) ** p <= 1: T[y][x] = G_
ISLETS = {'A': (8.5, 12, 5.5, 4.5), 'B': (30, 26.5, 7, 7), 'C': (8, 37, 3.2, 2.6), 'D': (18, 47, 5.5, 3.2)}
for cx, cy, rx, ry in ISLETS.values(): blob(cx, cy, rx, ry)
for _ in range(3):                                   # tira pontas de 1 celula (a praia nao tem canto concavo)
    for y in range(MH):
        for x in range(MW):
            if T[y][x] == G_ and sum(1 for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))
                                     if 0 <= x + dx < MW and 0 <= y + dy < MH and T[y + dy][x + dx] == G_) < 2:
                T[y][x] = W_
def near(x, y, cls, r):
    for dy in range(-r, r + 1):
        for dx in range(-r, r + 1):
            xx, yy = x + dx, y + dy
            if not (0 <= xx < MW and 0 <= yy < MH) or T[yy][xx] in cls: return True
    return False
beach = [[T[y][x] == G_ and near(x, y, (W_,), 2) for x in range(MW)] for y in range(MH)]
for y in range(MH):
    for x in range(MW):
        if beach[y][x]: T[y][x] = S_
# ilhota B: rochedo (montanha) no meio
MT = (26, 21, 34, 29)
for y in range(MT[1] - 1, MT[3] + 2):
    for x in range(MT[0] - 1, MT[2] + 2):
        if T[y][x] == G_: T[y][x] = X_
# arvores na ilhota A (2 colunas)
for x0 in (6, 8, 10):
    for y in range(10, 14):
        if all(T[y][x] == G_ and not near(x, y, (S_, W_), 1) for x in (x0, x0 + 1)): T[y][x0] = T[y][x0 + 1] = F_
g = Grid(MW, MH, pack_block(JOHTO['water'], 0, 1))
for y in range(MH):
    for x in range(MW):
        t = T[y][x]
        if t == W_: continue
        if t == S_: g.set(x, y, pick_sand(T, x, y, grassy=('G', 'F', 'X')))
        elif t == F_: g.set(x, y, pick_forest(T, x, y), 1)
        else:
            b = tree_base(T, x, y); g.set(x, y, b, 1) if b else g.set(x, y, JOHTO['grass'])
plateau(g, *MT)
plateau(g, 28, 22, 32, 25, on='rock', base=False)
SHRINE_DOOR = (30, MT[3]); g.set(*SHRINE_DOOR, 169, 0)           # gruta no pe do rochedo
for p in ((27, 27),): g.set(*p, 167, 1)
for y in (MT[3] - 1, MT[3]): g.set(32, y, 137); g.set(33, y, 145)        # escada ate o 1o nivel
# cais (continua o da Harvest Fields em x 16..18) que termina no mar
for y in range(0, 3):
    for i, x in enumerate((16, 17, 18)): g.set(x, y, JOHTO['pier'][i])
# recifes 2x2: corredores de Surf
REEFS = [(2, 2), (24, 4), (34, 6), (20, 12), (14, 18), (2, 22), (18, 26), (12, 30), (36, 38), (24, 38), (2, 44), (28, 46), (34, 50), (8, 52)]
for rx, ry in REEFS:
    if all(T[ry + dy][rx + dx] == W_ for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']): g.set(rx + dx, ry + dy, mid, 1, 1)
# agua funda (Dive): 3x3 da Route33South (2f0..302), elevacao 1, nas mesmas coordenadas do fundo
DIVES = [(22, 7), (5, 48)]
DEEP = ((0x2f0, 0x2f1, 0x2f2), (0x2f8, 0x2f9, 0x2fa), (0x300, 0x301, 0x302))
for dx0, dy0 in DIVES:
    assert all(T[dy0 + dy][dx0 + dx] == W_ and (g.b[dy0 + dy][dx0 + dx] & 0x7ff) == JOHTO['water'] for dx in range(3) for dy in range(3))
    for dy in range(3):
        for dx in range(3): g.set(dx0 + dx, dy0 + dy, DEEP[dy][dx], 0, 1)
# capim alto na ilhota D (encontros) e flores na A
for y in range(45, 49):
    for x in range(15, 21):
        if T[y][x] == G_: g.set(x, y, 10)
for x, y in ((7, 14), (10, 15), (11, 14)):
    if T[y][x] == G_: g.set(x, y, JOHTO['flowers'])
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
blocks = g.flat()

def o(lid, gfx, x, y, face='DOWN', script='0x0', ttype='TRAINER_TYPE_NONE', sight='0', elev=3, flag='0'):
    return {'local_id': 'LOCALID_SUNSET_STRAIT_' + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': elev,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0, 'trainer_type': ttype,
            'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
OBJS = [
    o('SWIMMER_1', 'SWIMMER_M_WATER', 12, 6, 'LEFT', 'SunsetStrait_EventScript_Swimmer1', 'TRAINER_TYPE_NORMAL', '4', elev=1),
    o('SWIMMER_2', 'SWIMMER_F_WATER', 26, 10, 'DOWN', 'SunsetStrait_EventScript_Swimmer2', 'TRAINER_TYPE_NORMAL', '4', elev=1),
    o('SWIMMER_3', 'SWIMMER_M_WATER', 6, 28, 'RIGHT', 'SunsetStrait_EventScript_Swimmer3', 'TRAINER_TYPE_NORMAL', '4', elev=1),
    o('SWIMMER_4', 'SWIMMER_F_WATER', 32, 42, 'LEFT', 'SunsetStrait_EventScript_Swimmer4', 'TRAINER_TYPE_NORMAL', '4', elev=1),
    o('SHELLY', 'SHELLY', 11, 9, 'DOWN', 'SunsetStrait_EventScript_Shelly'),
    o('JUAN', 'JUAN', 19, 45, 'DOWN', 'SunsetStrait_EventScript_Juan'),
    o('TATE', 'TATE', 29, 31, 'UP', 'SunsetStrait_EventScript_Tate'),
    o('ITEM_ISLET_A', 'ITEM_BALL', 5, 12, script='SunsetStrait_EventScript_ItemMysticWater'),
    o('ITEM_SANDBAR', 'ITEM_BALL', 8, 37, script='SunsetStrait_EventScript_ItemBigPearl'),
    o('ITEM_ROCK', 'ITEM_BALL', 33, 23, script='SunsetStrait_EventScript_ItemDragonScale'),
    o('ITEM_ISLET_D', 'ITEM_BALL', 22, 47, script='SunsetStrait_EventScript_ItemShellBell'),
]
bad = check_objects(blocks, MW, OBJS)
print('bloqueio/agua:', bad)
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1)
ice = lambda x, y: False
d = slide_reach((17, 0), walk, ice, MW, MH)                       # andando + Surf (agua e andavel aqui)
reach = {k: d.get((ob['x'], ob['y'])) is not None or any((ob['x'] + dx, ob['y'] + dy) in d for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0)))
         for k, ob in ((ob['local_id'], ob) for ob in OBJS)}
print('alcance (com Surf):', reach, 'gruta', SHRINE_DOOR in d, 'borda sul', any((x, MH - 1) in d for x in range(MW)))
P = load_tileset('primary', 'johto_general'); Sx = load_tileset('secondary', 'cianwood_city')
cv = render_blocks(blocks, MW, MH, P, Sx, objects=OBJS)
write_png(os.path.join(OUT, 'dia.png'), cv, 2)
write_png(os.path.join(OUT, 'colisao.png'), render_blocks(blocks, MW, MH, P, Sx, objects=OBJS, overlay=True, marks=[(SHRINE_DOOR, (200, 120, 255))] + [((x + 1, y + 1), (80, 230, 120)) for x, y in DIVES]), 2)
info = dict(map='AbundanceIsle_SunsetStrait', ingame='Sunset Strait', w=MW, h=MH, primary='gTileset_Johto_General', secondary='gTileset_CianwoodCity',
    map_type='MAP_TYPE_ROUTE',
    warps=[dict(x=SHRINE_DOOR[0], y=SHRINE_DOOR[1], dest_map='MAP_SHRINE_OF_THE_FIRST_DRAGON', dest_warp_id='0', nota='gruta no pe do rochedo da ilhota B')],
    connections=[dict(direction='up', map='MAP_ABUNDANCE_ISLE_HARVEST_FIELDS', offset=0, nota='mar dos dois lados; o cais da Harvest Fields (x 16..18) continua aqui e termina no mar'),
                 dict(direction='down', map='MAP_EMBERDUNE_ISLE', offset=0, nota='mar dos dois lados'),
                 dict(direction='dive', map='MAP_ABUNDANCE_ISLE_SUNSET_STRAIT_UNDERWATER', offset=0, nota='agua funda 3x3 em (22,7) e (5,48)')],
    dive_spots=[dict(x=x, y=y, w=3, h=3) for x, y in DIVES],
    objects=OBJS,
    explorar=['Fim do cais da Harvest Fields: daqui so de Surf; recifes 2x2 formam corredores ate o sul.',
              'Ilhota A com bosque e flores: Shelly (ex-admin da Equipe Aqua) estuda as correntes quentes que trazem o verao; Mystic Water no bosque.',
              'Rochedo da ilhota B: gruta no pe do penhasco leva ao Shrine of the First Dragon; Tate guarda a entrada ("so os dois juntos abrem"; a Liza esta la dentro); Dragon Scale no alto, subindo pela escada do rochedo.',
              'Banco de areia C escondido entre recifes: Big Pearl.',
              'Ilhota D com capim alto (encontros) e Juan, mestre de Agua que pinta o por do sol do estreito (batalha opcional); Shell Bell.',
              'Quatro nadadores (treinadores) espalhados pelos corredores.',
              'Duas manchas de agua funda (Dive): perto do fim do cais e no sudoeste. Embaixo, o casco do Sunken Truth Ship.'],
    historia='Ato 6: caminho por mar ate a Emberdune Isle. O rochedo com a gruta guarda o Shrine of the First Dragon, palco do fecho (N e Hilda) e do uso dos DNA Splicers.',
    estados={'dia': 'Estreito com nadadores, Shelly, Juan e Tate.'},
    conferido='check_objects: %s; alcance com Surf a partir do cais: gruta=%s, borda sul=%s' % (bad, SHRINE_DOOR in d, any((x, MH - 1) in d for x in range(MW))))
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
