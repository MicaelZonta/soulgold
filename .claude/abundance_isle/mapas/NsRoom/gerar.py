"""N's Room: esconderijo do N na Emberdune, homenagem ao quarto de brinquedos do castelo (BW).
Pecas do quarto do jogador (Johto_Building + PlayersHouse); o canto de brinquedos e desenho novo (props/)."""
import sys, os, json, importlib
SC = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha'
sys.path.insert(0, SC); sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from kit2 import *
from desenho import reduzir
import arte_brinquedos
OUT = os.path.dirname(os.path.abspath(__file__))
SRC = 'NewBarkTown_PlayersHouse_2F'
MW, MH = 17, 12
L = src(SRC); B = lambda x, y: L['blocks'][y * L['w'] + x]
FLOOR = B(4, 4)
g = Grid(MW, MH, FLOOR)
for x in range(MW):                                    # parede do fundo (2 fileiras), igual a do quarto do jogador
    g.raw(x, 0, B(0 if x == 0 else 10 if x == MW - 1 else 3, 0) if x in (0, MW - 1) else B(3, 0))
    g.raw(x, 1, B(3, 1))
for y in range(2, MH): g.raw(0, y, B(0, 3))
stamp(g, SRC, 0, 0, 3, 3, 0, 0)                        # planta e PC
stamp(g, SRC, 3, 0, 2, 4, 4, 0)                        # TV com console
stamp(g, SRC, 5, 0, 2, 3, 8, 0)                        # estante
stamp(g, SRC, 0, 5, 3, 3, 1, 8)                        # cama
stamp(g, SRC, 6, 5, 4, 4, 2, 3)                        # tapete com mesinha
stamp(g, SRC, 10, 0, 1, 2, MW - 1, 0)                  # relogio
TOYS = (11, 6)                                         # canto de brinquedos 4x3 (desenho novo)
for y in range(3):
    for x in range(4): g.set(TOYS[0] + x, TOYS[1] + y, FLOOR & 0x7ff, 1)
EXIT = (8, MH - 1)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0, 1, 0)] * 2] * 2)
blocks = g.flat()
def o(lid, gfx, x, y, face='DOWN', script='0x0', flag='0'):
    return {'local_id': 'LOCALID_NS_ROOM_' + lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0, 'trainer_type': 'TRAINER_TYPE_NONE',
            'trainer_sight_or_berry_tree_id': '0', 'script': script, 'flag': flag}
BASE = [o('DOLL_PIKACHU', 'PIKACHU_DOLL', 13, 2, script='NsRoom_EventScript_Dolls'),
        o('DOLL_TEPIG', 'CYNDAQUIL_DOLL', 14, 2, script='NsRoom_EventScript_Dolls'),
        o('DOLL_DITTO', 'DITTO_DOLL', 15, 3, script='NsRoom_EventScript_Dolls'),
        o('CUSHION', 'BALL_CUSHION', 6, 9, script='NsRoom_EventScript_Cushion'),
        o('ITEM_TOYBOX', 'ITEM_BALL', 15, 10, script='NsRoom_EventScript_ItemSootheBell')]
SCENE = BASE + [o('N', 'N', 10, 5, 'RIGHT', 'NsRoom_EventScript_N'), o('HILDA', 'HILDA', 7, 6, 'UP', 'NsRoom_EventScript_Hilda'),
                o('ZORUA', 'SPECIES(ZORUA)', 11, 5, 'LEFT', '0x0')]
BGS = [dict(type='sign', x=1, y=1, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='NsRoom_EventScript_PC'),
       dict(type='sign', x=8, y=1, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='NsRoom_EventScript_Bookshelf'),
       dict(type='sign', x=12, y=8, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_ANY', script='NsRoom_EventScript_ToyTrain')]
bad = check_objects(blocks, MW, SCENE)
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1)
d = slide_reach(EXIT, walk, lambda x, y: False, MW, MH)
okp = lambda x, y: any((x + dx, y + dy) in d for dx, dy in ((0, 0), (0, 1), (0, -1), (1, 0), (-1, 0)))
reach = {ob['local_id'][16:]: okp(ob['x'], ob['y']) for ob in SCENE}
reach.update({b['script'].split('_')[-1]: okp(b['x'], b['y']) for b in BGS})
print('bloqueio:', bad, 'alcance:', reach)
Lk = load_layout(SRC)
ARTS = [(c, n, reduzir(f())) for c, n, f in arte_brinquedos.PROPOSTAS]
def R(objs, k=0, **kw):
    cv = render_blocks(blocks, MW, MH, Lk['prim'], Lk['sec'], **kw)
    ARTS[k][2].over(cv, TOYS[0] * 16, TOYS[1] * 16)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
write_png(os.path.join(OUT, 'dia.png'), R(BASE), 3)
write_png(os.path.join(OUT, 'estado.png'), R(SCENE), 3)
write_png(os.path.join(OUT, 'colisao.png'), R(SCENE, overlay=True, marks=[(EXIT, (200, 120, 255))]), 3)
for i, (c, n, a) in enumerate(ARTS):
    write_png(os.path.join(OUT, 'props', 'brinquedos_%s.png' % c), a.rgb((232, 232, 236)), 4)
    write_png(os.path.join(OUT, 'props', 'no_mapa_%s.png' % c), crop(R(BASE, i), 6 * 16, 2 * 16, MW * 16, MH * 16), 3)
info = dict(map='NsRoom', ingame="N's Room", w=MW, h=MH, primary=Lk['info']['primary_tileset'], secondary=Lk['info']['secondary_tileset'],
    map_type='MAP_TYPE_INDOOR', warps=[dict(x=EXIT[0], y=EXIT[1], dest_map='MAP_EMBERDUNE_ISLE', dest_warp_id='4', nota='porta da casinha no oasis oeste da Emberdune')],
    connections=[], objects=SCENE, bg_events=BGS,
    desenho_novo=dict(nome='canto de brinquedos do N', area='4x3 metatiles em (%d,%d)' % TOYS,
                      propostas=[[c, n] for c, n, _ in ARTS], pasta='props/'),
    explorar=['Homenagem ao quarto do castelo do N no BW: canto de brinquedos com trilho de trem, bola de basquete e skate (desenho novo, 4 propostas).',
              'Bonecos de Pokemon na prateleira e uma almofada de Poke Ball; o PC tem anotacoes do N sobre "verdade e ideais".',
              'Estante: livros infantis e um caderno com desenhos de Pokemon que ele "ouviu".',
              'Soothe Bell na caixa de brinquedos.'],
    historia='Ato 6, antes das ruinas: momento pessoal do N e da Hilda. Ele mostra o quarto que montou "para lembrar que um dia foi so uma crianca"; a Hilda conta quando o Reshiram a escolheu. O Zorua, primeiro amigo do N, fica no canto.',
    estados={'dia': 'Quarto vazio (proposta A do canto de brinquedos).', 'estado': 'Cena: N, Hilda e o Zorua.'},
    conferido='check_objects: %s; BFS da porta: %s' % (bad, 'tudo alcancavel' if all(reach.values()) else reach))
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
