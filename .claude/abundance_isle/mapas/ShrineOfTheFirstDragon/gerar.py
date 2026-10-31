"""Shrine of the First Dragon: salao do DragonsDen_Shrine alargado (cabecas de dragao no alto, serpentes
nos lados) com tres altares: Verdade (Reshiram), Vazio (Kyurem) e Ideais (Zekrom)."""
import sys, os, json
SC = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha'
sys.path.insert(0, SC)
from kit2 import *
OUT = os.path.dirname(os.path.abspath(__file__))
SRC = 'DragonsDen_Shrine'
MW, MH = 24, 20
g = Grid(MW, MH, 0)
put(g, nine(SRC, 0, 4, 14, 14, MW, MH, cx=3, px=2, cy=7, py=2), 0, 0)
L = src(SRC); B = lambda x, y: L['blocks'][y * L['w'] + x]
FLOOR = B(3, 11)
# limpa o que veio repetido/deslocado da sala original (tapete, estatuas, tapete da porta, saida, emblema)
for y in range(5, MH):
    for x in range(3, 20): g.raw(x, y, FLOOR)
for x in range(0, MW): g.raw(x, MH - 1, B(0, 17))               # linha preta de baixo
# parede do fundo: troca o emblema deslocado pela cabeca de dragao comum
for y in range(2, 5):
    for x in range(3, 20):
        g.raw(x, y, B(3 + (x - 3) % 2, 6 + y - 2))
def stamp_src(sx, sy, w, h, dx, dy): stamp(g, SRC, sx, sy, w, h, dx, dy)
ALTARS = {'TRUTH': 4, 'VOID': 10, 'IDEALS': 16}
for x0 in ALTARS.values(): stamp_src(5, 9, 3, 2, x0, 7)             # tapete-altar 3x2
stamp_src(6, 8, 1, 1, 11, 4)                                         # emblema central na parede, acima do altar do Vazio
for x, y in ((8, 7), (14, 7), (8, 12), (14, 12), (5, 14), (17, 14)):
    stamp_src(4, 14, 1, 2, x, y)                                     # estatuas 1x2 (4ff/500)
stamp_src(5, 16, 3, 1, 10, MH - 2)                                   # tapete da porta
stamp_src(5, 17, 3, 1, 10, MH - 1)                                   # saida
EXIT = (11, MH - 2)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0, 1)] * 2] * 2)
blocks = g.flat()

def o(lid, gfx, x, y, face='DOWN', script='0x0', ttype='TRAINER_TYPE_NONE', sight='0', elev=3, flag='0'):
    return {'local_id': 'LOCALID_SHRINE_OF_THE_FIRST_DRAGON_' + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y,
            'elevation': elev, 'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
OBJS = [
    o('N', 'N', 10, 10, 'DOWN', 'ShrineFirstDragon_EventScript_N'),
    o('HILDA', 'HILDA', 12, 10, 'DOWN', 'ShrineFirstDragon_EventScript_Hilda'),
    o('LIZA', 'LIZA', 13, 16, 'LEFT', 'ShrineFirstDragon_EventScript_Liza'),
    o('LEON', 'LEON', 18, 11, 'LEFT', 'ShrineFirstDragon_EventScript_Leon'),
    o('DIANTHA', 'DIANTHA', 4, 11, 'RIGHT', 'ShrineFirstDragon_EventScript_Diantha'),
    o('ITEM_HIDDEN', 'ITEM_BALL', 19, 16, script='ShrineFirstDragon_EventScript_ItemDracoPlate'),
]
BGS = [dict(type='sign', x=5, y=4, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='ShrineFirstDragon_EventScript_MuralTruth'),
       dict(type='sign', x=11, y=4, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='ShrineFirstDragon_EventScript_MuralFirstDragon'),
       dict(type='sign', x=17, y=4, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='ShrineFirstDragon_EventScript_MuralIdeals'),
       dict(type='sign', x=11, y=8, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_ANY', script='ShrineFirstDragon_EventScript_AltarVoid'),
       dict(type='sign', x=5, y=8, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_ANY', script='ShrineFirstDragon_EventScript_AltarTruth'),
       dict(type='sign', x=17, y=8, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_ANY', script='ShrineFirstDragon_EventScript_AltarIdeals')]
bad = check_objects(blocks, MW, OBJS)
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1)
d = slide_reach(EXIT, walk, lambda x, y: False, MW, MH)
ok = lambda x, y: any((x + dx, y + dy) in d for dx, dy in ((0, 0), (0, 1), (0, -1), (1, 0), (-1, 0)))
reach = {ob['local_id'].split('DRAGON_')[1]: ok(ob['x'], ob['y']) for ob in OBJS}
reach.update({b['script'].split('_')[-1]: ok(b['x'], b['y']) for b in BGS})
print('bloqueio:', bad, 'alcance:', reach)
Lk = load_layout(SRC)
def R(objs, **kw): return render_blocks(blocks, MW, MH, Lk['prim'], Lk['sec'], objects=objs, **kw)
write_png(os.path.join(OUT, 'dia.png'), R([x for x in OBJS if x['local_id'].split('_')[-1] not in ('N', 'HILDA')]), 3)
write_png(os.path.join(OUT, 'estado.png'), R(OBJS), 3)
write_png(os.path.join(OUT, 'colisao.png'), R(OBJS, overlay=True, marks=[(EXIT, (200, 120, 255))] + [((b['x'], b['y']), (255, 230, 80)) for b in BGS]), 3)
info = dict(map='ShrineOfTheFirstDragon', ingame='Shrine of the First Dragon', w=MW, h=MH, primary=Lk['info']['primary_tileset'],
    secondary=Lk['info']['secondary_tileset'], map_type='MAP_TYPE_INDOOR',
    warps=[dict(x=EXIT[0], y=EXIT[1], dest_map='MAP_ABUNDANCE_ISLE_SUNSET_STRAIT', dest_warp_id='0', nota='tapete da porta -> gruta do rochedo da Sunset Strait')],
    connections=[], objects=OBJS, bg_events=BGS,
    explorar=['Tres murais no alto: o Heroi da Verdade com o dragao branco, o Primeiro Dragao inteiro (centro) e o Heroi dos Ideais com o dragao negro.',
              'Tres altares: Verdade (Reshiram), Vazio (Kyurem) e Ideais (Zekrom). Com Kyurem e um dos dois na equipe, o altar do Vazio oferece a cerimonia dos DNA Splicers (Kyurem Black ou White).',
              'Liza, irma gemea do Tate que guarda a gruta la fora: "dois herois, dois gemeos" (fala de lore; batalha dupla Tate+Liza depois do fecho).',
              'Diantha estuda os murais e conta a versao de Kalos de "um poder que se divide" (batalha opcional).',
              'Leon, o campeao de Galar, veio ver a lenda e desafia quem venceu N e Hilda (superchefe opcional, revanche semanal).',
              'Draco Plate escondida atras da estatua do canto leste.'],
    historia='Fecho do ato 6 (e de toda a historia): N e Hilda esperam diante do altar do Vazio; batalha dupla final contra o jogador. Depois, os murais completos e a cerimonia do Kyurem com os DNA Splicers.',
    estados={'dia': 'Santuario sem N e Hilda (pos-jogo: Leon, Diantha e Liza).', 'estado': 'Fecho: N e Hilda diante do altar do Vazio.'},
    conferido='check_objects: %s; BFS a partir da porta: %s' % (bad, 'tudo alcancavel' if all(reach.values()) else reach))
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
