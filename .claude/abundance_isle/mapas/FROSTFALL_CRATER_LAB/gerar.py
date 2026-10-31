import sys, importlib; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from crater_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
MAQ = reduzir(importlib.import_module('arte_maquina').PROPOSTAS[0][2]())
c = Cave(34, 26)
c.room(5, 3, 28, 11)        # H salao da maquina
c.room(2, 16, 7, 21)        # W chegada (escada do B1F)
c.room(8, 18, 12, 19)       # W -> corredor
c.room(13, 14, 14, 21)      # corredor que sobe ate o salao
c.room(13, 12, 14, 13)
c.room(15, 17, 20, 21)      # S almoxarifado do Plasma
c.room(26, 16, 31, 21)      # E escada do atalho (1F)
c.room(28, 12, 29, 15)      # E -> H (gelo do atalho)
c.walls()
c.ladder_up(4, 16, 'MAP_FROSTFALL_CRATER_B1F', '1', 'sobe para o salao de gelo (2,10)')
c.ladder_up(29, 16, 'MAP_FROSTFALL_CRATER_1F', '2', 'atalho para a camara leste do 1F (30,4)')
MX, MY = 15, 3
c.block_art(MX, MY, 3, 2)
SHORT = [(28, 13), (29, 13)]
for p in SHORT: c.ball(*p)
c.marks += [(p, (255, 230, 80)) for p in SHORT]
# chao congelado em volta da maquina (o frio vaza)
c.ice(9, 5, 12, 9); c.ice(20, 5, 24, 9)
for p in ((10, 6), (22, 8), (11, 9), (21, 5)): c.ball(*p)
c.big(5, 3); c.big(27, 3); c.big(18, 20)
for p in ((6, 9), (26, 8), (2, 19), (30, 19)): c.icicle(*p)
# objetos
GH = c.obj('GHETSIS', 'SAGE', MX + 1, MY + 3, 'DOWN', 'FrostfallCrater_Lab_EventScript_Ghetsis')
c.obj('SCIENTIST_A', 'SCIENTIST_1', MX - 1, MY + 2, 'UP', 'FrostfallCrater_Lab_EventScript_ScientistA')
c.obj('SCIENTIST_B', 'SCIENTIST_1', MX + 3, MY + 2, 'UP', 'FrostfallCrater_Lab_EventScript_ScientistB')
c.obj('GRUNT_3', 'SCIENTIST_1', 14, 16, 'LEFT', 'FrostfallCrater_Lab_EventScript_Grunt3', ttype='TRAINER_TYPE_NORMAL', sight='4')
c.obj('GRUNT_4', 'SCIENTIST_1', 13, 13, 'DOWN', 'FrostfallCrater_Lab_EventScript_Grunt4', ttype='TRAINER_TYPE_NORMAL', sight='3')
c.obj('ITEM_TM', 'ITEM_BALL', 19, 18, script='FrostfallCrater_Lab_EventScript_ItemTMBlizzard')
c.obj('ITEM_MAXREVIVE', 'ITEM_BALL', 15, 21, script='FrostfallCrater_Lab_EventScript_ItemMaxRevive')
N = c.obj('N_LAB', 'N', MX - 1, MY + 4, 'UP', 'FrostfallCrater_Lab_EventScript_N'); N['_estado'] = 1
ICE_ST = c.obj('ITEM_ICESTONE', 'ITEM_BALL', MX + 1, MY + 3, script='FrostfallCrater_Lab_EventScript_ItemIceStone'); ICE_ST['_estado'] = 1
# verificacao
d = c.reach((4, 17))
assert c.can_take(d, (GH['x'], GH['y'])) is not None, 'ghetsis'
for p in ((19, 18), (15, 21)): assert c.can_take(d, p) is not None, p
assert (29, 16) not in d, 'atalho deveria estar fechado'
after = [r[:] for r in c.g.b]
for x, y in SHORT: after[y][x] = pack_block(FLOOR, 0)
saved = c.g.b; c.g.b = after
d2 = c.reach((4, 17), ignore=('GHETSIS', 'SCIENTIST_A', 'SCIENTIST_B'))
assert (29, 16) in d2, 'atalho depois'
c.g.b = saved
pth = c.path((4, 17), (GH['x'], GH['y'] + 1))
estado_objs = [o for o in c.objects if o['local_id'] not in ('GHETSIS', 'SCIENTIST_A', 'SCIENTIST_B', 'GRUNT_3', 'GRUNT_4')] + []
for o in estado_objs: o.pop('_estado', None) if False else None
c.save(OUT, dict(map='FROSTFALL_CRATER_LAB', ingame='Frostfall Crater Lab', map_type='MAP_TYPE_UNDERGROUND', connections=[],
    explorar=['Salao da maquina com o chao congelado em volta: duas poças de gelo com pedras de neve',
              'Almoxarifado do Plasma: TM Blizzard e Max Revive',
              'Corredor guardado por dois recrutas (um olha o corredor, outro a saida para o salao)',
              'Escada do atalho para o 1F atras de gelo: derrete quando a maquina para',
              'Depois: Ice Stone onde estava o Ghetsis; N fica examinando o meteorito'],
    historia='Ghetsis explica o plano (frio do meteorito -> tempestades -> raios na Pedra Escura -> Zekrom + Kyurem). Batalha; ele foge para o cume. O jogador desliga a maquina.',
    estados={'dia': 'Climax: Ghetsis e os cientistas diante da maquina (arte proposta A).',
             'estado': 'Depois: atalho aberto, Ice Stone e N no lugar do Ghetsis.'},
    maquina={'x': MX, 'y': MY, 'w': 3, 'h': 2},
    conferido='check_objects ok; BFS da escada do B1F (4,17) ate o Ghetsis e os dois itens; atalho (29,16) fechado antes e aberto depois (com o Ghetsis e os cientistas fora).'),
    arts=[(MAQ, MX, MY)], estado=(sum(after, []), estado_objs + [dict(N, **{}), dict(ICE_ST)]), path=pth)
print('ok LAB', c.warps)
