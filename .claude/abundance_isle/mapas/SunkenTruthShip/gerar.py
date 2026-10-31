"""Sunken Truth Ship: interior do casco (bolsa de ar), com as pecas de madeira em ruinas da Burned Tower
(torre_kit do fork C). Rombos, entulho, figura de proa, mural da Light Stone, cabine secreta do capitao."""
import sys, os, json
M20 = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20'
sys.path.insert(0, M20)
from torre_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
MW, MH = 28, 18
g = andar(MW, MH)
EXIT = [(x, MH - 3) for x in range(MW) if (g.b[MH - 3][x] & 0x7ff) == 0x426][0]
# rombos no fundo do casco (agua escura la embaixo: inacessivel)
poco(g, 4, 6, 8, 9); poco(g, 18, 10, 21, 13); poco(g, 10, 12, 13, 14)
# antepara de entulho que fecha a cabine do capitao (canto nordeste); a passagem e uma tabua quebravel
CABIN = (20, 4, MW - 2, 8)
for x in range(CABIN[0], CABIN[2] + 1): g.set(x, CABIN[3] + 1, BOULDER, 1, 3)
for y in range(CABIN[1], CABIN[3] + 2): g.set(CABIN[0] - 1, y, BOULDER, 1, 3)
PLANK = (CABIN[0] + 2, CABIN[3] + 1); g.set(*PLANK, FLOOR, 0, 3)  # o objeto BREAKABLE_ROCK fica aqui
for p in ((3, 12), (15, 5), (24, 13), (9, 4)): g.set(*p, BOULDER, 1, 3)
estatua(g, 13, 5)                                      # figura de proa caida (estatua)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0, 1, 0)] * 2] * 2)
P = 'LOCALID_SUNKEN_TRUTH_SHIP_'
OBJS = [
    obj(P, 'PHOEBE', 'PHOEBE', 6, 14, 'UP', 'SunkenTruthShip_EventScript_Phoebe'),
    obj(P, 'PLANK', 'BREAKABLE_ROCK', *PLANK, script='EventScript_RockSmash'),
    obj(P, 'ITEM_RELIC_GOLD', 'ITEM_BALL', 2, 4, script='SunkenTruthShip_EventScript_ItemRelicGold'),
    obj(P, 'ITEM_FLAME_PLATE', 'ITEM_BALL', 16, 14, script='SunkenTruthShip_EventScript_ItemFlamePlate'),
    obj(P, 'ITEM_BOTTLE_CAP', 'ITEM_BALL', 25, 14, script='SunkenTruthShip_EventScript_ItemBottleCap'),
    obj(P, 'ITEM_RELIC_CROWN', 'ITEM_BALL', CABIN[2] - 1, CABIN[1], script='SunkenTruthShip_EventScript_ItemRelicCrown'),
]
BGS = [dict(type='sign', x=11, y=3, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='SunkenTruthShip_EventScript_MuralLightStone'),
       dict(type='sign', x=CABIN[0] + 1, y=CABIN[1], elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='SunkenTruthShip_EventScript_CaptainsLog'),
       dict(type='sign', x=13, y=6, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_ANY', script='SunkenTruthShip_EventScript_Figurehead')]
bad = check_objects(g.flat(), MW, OBJS)
d_no = alcance(g, EXIT, extra_block={PLANK}); d_rs = alcance(g, EXIT)
reach = {ob['local_id'][len(P):]: (perto(d_no, (ob['x'], ob['y'])) is not None, perto(d_rs, (ob['x'], ob['y'])) is not None) for ob in OBJS}
reach.update({b['script'].split('_')[-1]: (perto(d_no, (b['x'], b['y'])) is not None, perto(d_rs, (b['x'], b['y'])) is not None) for b in BGS})
print('bloqueio:', bad, '\nalcance (sem, com Rock Smash):', reach)
render(g, OBJS, OUT, 'dia.png')
render(g, OBJS, OUT, 'colisao.png', overlay=True, marks=[(EXIT, (200, 120, 255)), (PLANK, (255, 230, 80))])
info = dict(map='SunkenTruthShip', ingame='Sunken Truth Ship', w=MW, h=MH, primary='gTileset_Johto_Building', secondary='gTileset_BurnedTower',
    map_type='MAP_TYPE_INDOOR', music='MUS_HG_BURNED_TOWER',
    warps=[dict(x=EXIT[0], y=EXIT[1], dest_map='MAP_ABUNDANCE_ISLE_SUNSET_STRAIT_UNDERWATER', dest_warp_id='0', nota='volta ao rombo do casco no fundo do mar')],
    connections=[], objects=OBJS, bg_events=BGS,
    explorar=['Bolsa de ar dentro do casco: madeira podre, rombos que dao para a agua escura (cair nao e possivel; sao paredes).',
              'Mural de bordo (parede norte): a Light Stone num bau, o navio partindo de Unova e uma ilha de areia ao sul - a pista das Truthsand Ruins.',
              'Figura de proa caida: um dragao branco esculpido.',
              'Cabine do capitao atras de uma tabua quebravel (Rock Smash): diario de bordo ("we buried it beneath the dune, where only truth may enter") e uma Relic Crown.',
              'Relic Gold, Flame Plate (a placa do tipo do Reshiram) e Bottle Cap pelo casco.',
              'Phoebe, da Elite dos Quatro de Hoenn, sente os espiritos do navio e desafia o jogador (batalha opcional, Fantasma).'],
    historia='Ato 6 (opcional): prova de que a Light Stone veio de Unova por mar; o diario de bordo confirma o esconderijo sob a duna.',
    estados={'dia': 'Interior do naufragio.'},
    conferido='check_objects: %s; BFS da saida: tudo menos a cabine sem Rock Smash; com Rock Smash tudo: %s' % (bad, all(v[1] for v in reach.values())))
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
