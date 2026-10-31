"""Fundo da Sunset Strait (Dive). Mesmas dimensoes da Strait; pecas da Route33South_Underwater
(primario underwater). Salao com a massa do naufragio no meio e a boca do casco na face sul dela."""
import sys, os, json
SC = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha'
sys.path.insert(0, SC)
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
MW, MH = 40, 56
FILL, FLOOR, ARCH = 0x44, 0x21, 0x82
g = Grid(MW, MH, pack_block(FILL, 1, 0))
W1 = lambda m: pack_block(m, 1, 0)
def room(x0, y0, x1, y1):
    """Sala submarina: moldura como a da Route33South_Underwater (borda de cima 68/76/69, face 9d/a5/ad
    em 3 fileiras, laterais 6f+f / d+6d, base 6 e 66)."""
    for x in range(x0, x1 + 1):
        g.raw(x, y0, W1(0x68 if x == x0 else 0x69 if x == x1 else 0x76))
    for k, mid in enumerate((0x9d, 0xa5, 0xad)):
        y = y0 + 1 + k
        for x in range(x0, x1 + 1):
            if x == x0: m = 0x6f
            elif x == x1: m = 0x6d
            elif x == x0 + 1: m = 0x48 if k == 0 else 0xf
            elif x == x1 - 1: m = 0x49 if k == 0 else 0xd
            else: m = mid
            g.raw(x, y, W1(m))
    for y in range(y0 + 4, y1 - 1):
        for x in range(x0, x1 + 1):
            if x == x0: g.raw(x, y, W1(0x6f))
            elif x == x0 + 1: g.raw(x, y, W1(0xf))
            elif x == x1 - 1: g.raw(x, y, W1(0xd))
            elif x == x1: g.raw(x, y, W1(0x6d))
            else: g.set(x, y, FLOOR, 0, 0)
    for x in range(x0, x1 + 1):
        g.raw(x, y1 - 1, W1(0x6f if x == x0 else 0x50 if x == x0 + 1 else 0x6d if x == x1 else 0xd if x == x1 - 1 else 0x6))
        g.raw(x, y1, W1(0x70 if x == x0 else 0x71 if x == x1 else 0x66))
def block(x0, y0, x1, y1):
    """Massa solta no meio da sala: borda norte 6/66, face sul 76/9d/a5/ad, lados d+6d (oeste) e 6f+f (leste)."""
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if y == y0: m = 0x6
            elif y == y0 + 1: m = 0x66
            elif y == y1 - 3: m = 0x76
            elif y == y1 - 2: m = 0x9d
            elif y == y1 - 1: m = 0xa5
            elif y == y1: m = 0xad
            else: m = FILL
            if y not in (y0,) and y < y1 - 3:
                if x == x0: m = 0xd
                elif x == x1: m = 0xf
            g.raw(x, y, W1(m))
room(1, 1, 38, 54)
HULL = (10, 22, 29, 33)
block(*HULL)
WRECK_DOOR = (19, HULL[3]); g.set(*WRECK_DOOR, ARCH, 0, 0)
block(4, 12, 9, 18); block(29, 40, 35, 46); block(31, 8, 35, 13)
L = src('Route33South_Underwater')
def emerge(x, y):                                       # anel 5x5 da Route33South_Underwater, centro 3x3 claro
    for dy in range(5):
        for dx in range(5):
            v = L['blocks'][(13 + dy) * L['w'] + 17 + dx]
            g.raw(x - 1 + dx, y - 1 + dy, (v & 0x7ff) | (0 << 11) | (0 << 12))
DIVES = [(22, 7), (5, 48)]                              # canto NO de cada ponto 3x3 (igual na superficie)
for p in DIVES: emerge(*p)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[W1(FILL)] * 2] * 2)
blocks = g.flat()
def o(lid, gfx, x, y, script='0x0', flag='0'):
    return {'local_id': 'LOCALID_SUNSET_STRAIT_UNDERWATER_' + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 0,
            'movement_type': 'MOVEMENT_TYPE_FACE_DOWN', 'movement_range_x': 0, 'movement_range_y': 0, 'trainer_type': 'TRAINER_TYPE_NONE',
            'trainer_sight_or_berry_tree_id': '0', 'script': script, 'flag': flag}
OBJS = [o('ITEM_REEF', 'ITEM_BALL', 33, 15, 'SunsetStraitUnderwater_EventScript_ItemDeepSeaScale'),
        o('ITEM_HULL', 'ITEM_BALL', 28, 35, 'SunsetStraitUnderwater_EventScript_ItemHeartScale'),
        o('ITEM_SOUTH', 'ITEM_BALL', 34, 50, 'SunsetStraitUnderwater_EventScript_ItemDeepSeaTooth')]
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1)
d = slide_reach((DIVES[0][0] + 1, DIVES[0][1] + 1), walk, lambda x, y: False, MW, MH)
ok = {ob['local_id'].split('_')[-1]: (ob['x'], ob['y']) in d for ob in OBJS}
ok['casco'] = WRECK_DOOR in d; ok['ponto B'] = (DIVES[1][0] + 1, DIVES[1][1] + 1) in d
bad = check_objects(blocks, MW, [dict(ob, elevation=3) for ob in OBJS])
print('bloqueio:', bad, 'alcance:', ok)
P = load_tileset('primary', 'underwater'); Sx = load_tileset('secondary', 'cianwood_city')
write_png(os.path.join(OUT, 'dia.png'), render_blocks(blocks, MW, MH, P, Sx, objects=OBJS), 2)
write_png(os.path.join(OUT, 'colisao.png'), render_blocks(blocks, MW, MH, P, Sx, objects=OBJS, overlay=True,
          marks=[(WRECK_DOOR, (200, 120, 255))] + [((x + 1, y + 1), (80, 230, 120)) for x, y in DIVES]), 2)
info = dict(map='AbundanceIsle_SunsetStrait_Underwater', ingame='Sunset Strait', w=MW, h=MH, primary='gTileset_underwater',
    secondary='gTileset_CianwoodCity', map_type='MAP_TYPE_UNDERWATER', music='MUS_UNDERWATER', weather='WEATHER_UNDERWATER',
    warps=[dict(x=WRECK_DOOR[0], y=WRECK_DOOR[1], dest_map='MAP_SUNKEN_TRUTH_SHIP', dest_warp_id='0', nota='rombo no casco (boca 0x82 na face sul da massa do naufragio)')],
    connections=[dict(direction='emerge', map='MAP_ABUNDANCE_ISLE_SUNSET_STRAIT', offset=0, nota='sobe nos dois pontos claros (mesmas coordenadas da agua funda da superficie)')],
    dive_spots=[dict(x=x, y=y, w=3, h=3) for x, y in DIVES], objects=OBJS,
    explorar=['Dois pontos de mergulho (agua funda 3x3 na superficie): um perto do cais, outro no sudoeste.',
              'A massa escura no meio e o casco do navio dos seguidores do Heroi da Verdade; o rombo na face sul leva ao interior (bolsa de ar).',
              'Tres rochedos submarinos escondem itens: Deep Sea Scale, Heart Scale ao pe do casco e Deep Sea Tooth no fundo sul.'],
    historia='Ato 6 (opcional antes das ruinas): o navio que trouxe a Light Stone afundou aqui; o mural de bordo conta onde ela foi escondida.',
    estados={'dia': 'Fundo do estreito.'}, conferido='check_objects: %s; BFS a partir do ponto A: %s' % (bad, ok))
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
