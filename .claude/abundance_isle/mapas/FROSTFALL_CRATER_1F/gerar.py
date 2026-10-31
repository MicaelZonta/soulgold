import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from crater_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
c = Cave(34, 28)
c.room(13, 20, 20, 24)      # A saguao de entrada
c.room(16, 15, 17, 19)      # corredor do posto de controle
c.room(5, 8, 27, 14)        # C caverna central (lago congelado a oeste)
c.room(2, 10, 4, 12)        # W nicho escondido
c.room(16, 6, 17, 7)        # corredor C -> N
c.room(9, 2, 24, 5)         # N camara norte (escada para B1F)
c.room(25, 3, 26, 3)        # passagem N -> E (parede de gelo)
c.room(27, 2, 31, 6)        # E escada do atalho para o laboratorio
c.walls()
c.exit_south(16, 25, 'MAP_ABUNDANCE_ISLE', '?', 'boca da cratera no hub (11,16)')
# lago congelado com a ilha do item
c.ice(5, 8, 13, 14)
POND_ITEM = (9, 11); c.g.set(*POND_ITEM, FLOOR, 0)
for p in ((6, 9), (12, 8), (8, 13), (11, 12), (5, 12), (10, 9)): c.ball(*p)
# nicho: atras de estalactites (passagem de 1 celula em (4,11))
c.g.set(4, 10, 0x41f, 1); c.g.set(4, 12, 0x427, 1)
# decoracao
c.big(21, 9); c.big(25, 12); c.big(9, 2); c.big(23, 2)
for p in ((19, 12), (14, 20), (19, 22), (13, 3)): c.icicle(*p)
# escadas
c.ladder_down(12, 4, 'MAP_FROSTFALL_CRATER_B1F', '0', 'desce para o salao de gelo')
SHORT = [(25, 3), (26, 3)]
for p in SHORT: c.ball(*p)
c.marks += [(p, (255, 230, 80)) for p in SHORT]
c.ladder_down(30, 4, 'MAP_FROSTFALL_CRATER_LAB', '1', 'atalho: so depois que a maquina para (parede de gelo em 25-26,3)')
# objetos
c.obj('GRUNT_1', 'SCIENTIST_1', 16, 18, 'RIGHT', 'FrostfallCrater_1F_EventScript_Grunt1', ttype='TRAINER_TYPE_NORMAL', sight='3')
c.obj('GRUNT_2', 'SCIENTIST_1', 17, 15, 'LEFT', 'FrostfallCrater_1F_EventScript_Grunt2', ttype='TRAINER_TYPE_NORMAL', sight='3')
c.obj('ITEM_SNOWBALL', 'ITEM_BALL', *POND_ITEM, script='FrostfallCrater_1F_EventScript_ItemSnowball')
c.obj('ITEM_ICEHEAL', 'ITEM_BALL', 2, 11, script='FrostfallCrater_1F_EventScript_ItemIceHeal')
c.obj('HIKER', 'HIKER', 22, 13, 'LEFT', 'FrostfallCrater_1F_EventScript_Hiker', ttype='TRAINER_TYPE_NORMAL', sight='4')
LORELEI = c.obj('LORELEI', 'LORELEI', 15, 9, 'LEFT', 'FrostfallCrater_1F_EventScript_Lorelei')
# verificacao
d = c.reach((16, 24))
for nome, p in (('item do lago', POND_ITEM), ('nicho', (2, 11)), ('lorelei', (15, 9))):
    assert c.can_take(d, p) is not None, nome
assert (12, 4) in d, 'escada B1F'
assert (30, 4) not in d, 'atalho deveria estar fechado'
d2 = c.reach((16, 24), ()) if False else None
b_after = c.g.flat()
for x, y in SHORT: b_after[y * c.w + x] = pack_block(FLOOR, 0)
pth = c.path((16, 24), (12, 4))
c.save(OUT, dict(map='FROSTFALL_CRATER_1F', ingame='Frostfall Crater 1F', map_type='MAP_TYPE_UNDERGROUND', connections=[],
    explorar=['Lago congelado: a Snowball fica numa ilha de pedra, alcancada deslizando (%d movimentos)' % c.can_take(d, POND_ITEM),
              'Nicho escondido a oeste, entre estalactites: Ice Heal',
              'Posto de controle do Plasma: dois recrutas no corredor estreito, impossivel passar sem lutar',
              'Escada da camara leste presa atras de gelo: atalho direto ao laboratorio, abre quando a maquina para',
              'Hiker preso pelo frio na caverna central',
              'Lorelei (mestre de gelo de Kanto) na beira do lago congelado, investigando o frio fora de epoca: explica que o gelo "nao e natural, tem a assinatura de um dragao"; batalha opcional depois do evento (revanche do Nexus fora do loop)'],
    historia='Boca da cratera, guardada pelo Neo Plasma. O frio sai do fundo e congela ate o lago da entrada.',
    estados={'dia': 'Antes da maquina parar (atalho fechado).', 'estado': 'Depois: parede de gelo do atalho derretida.'},
    conferido='check_objects ok; BFS com deslize da entrada (16,24) ao item do lago, ao nicho e a escada do B1F; atalho (30,4) inalcancavel antes do evento.'),
    estado=(b_after, [o for o in c.objects if 'GRUNT' not in o['local_id']]), path=pth)
print('ok 1F', c.warps)
