"""Truthsand Ruins B1F: cada sumidouro do 1F cai num lugar diferente. Sala A (oeste) e a cava do
Plasma (leste, escada deles) dao no labirinto central; a Trilha da Verdade (sul) so se alcanca pelo
3o sumidouro (ou quebrando as pedras do portao) e tem o sumidouro que desce ao Hall of Truth."""
import sys, os; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)) + '/..')
from ruina_kit import *
D = os.path.dirname(os.path.abspath(__file__))
P = 'LOCALID_TRUTHSAND_RUINS_B1F_'
r = Ruina(36, 31)
r.room(2, 4, 11, 10)            # A: sala desabada (pouso do sumidouro 1)
r.room(6, 11, 7, 13)            # A -> labirinto
r.room(23, 4, 33, 11)           # B: cava do Plasma (pouso do sumidouro 2 + escada deles)
r.room(28, 12, 29, 13)          # B -> labirinto
r.room(2, 14, 33, 19)           # labirinto central
r.room(17, 20, 18, 21)          # portao da Trilha (pedras)
r.room(10, 22, 25, 28)          # C: Trilha da Verdade
r.paint()
# labirinto: dunas e estatuas formando corredores
for x in range(4, 32, 6): r.statue(x, 15)
for x in range(7, 32, 6): r.statue(x, 17, right=True)
r.dune(10, 18); r.dune(25, 14); r.skeleton(32, 14)
r.skeleton(9, 5); r.dune(4, 8); r.statue(6, 4)
# cava do Plasma
LADDER = (28, 5); r.ladder(*LADDER)
r.crate(24, 5); r.crate(31, 9); r.scaffold(25, 3, 4) if False else None
# Trilha da Verdade: avenida de estatuas ate o sumidouro do fundo
r.path([(x, y) for x in (17, 18) for y in range(22, 26)])
for y in (23, 25): r.statue(14, y); r.statue(21, y, right=True)
HOLE_HALL = (17, 27); r.hole(*HOLE_HALL)
LADDER_UP = (24, 23); r.ladder(*LADDER_UP)
LAND = {'A': (6, 6), 'B': (30, 6), 'C': (12, 24)}
# ---------------- warps (indices usados pelo 1F e pelo Hall)
r.warp(*LADDER, 'MAP_TRUTHSAND_RUINS_1F', 1, 'escada do Plasma (sobe ao 1F)')
r.warp(*LAND['A'], 'MAP_TRUTHSAND_RUINS_1F', 2, 'pouso do sumidouro 1 (so chegada)')
r.warp(*LAND['B'], 'MAP_TRUTHSAND_RUINS_1F', 3, 'pouso do sumidouro 2 (so chegada)')
r.warp(*LAND['C'], 'MAP_TRUTHSAND_RUINS_1F', 4, 'pouso do sumidouro 3 (so chegada)')
r.warp(HOLE_HALL[0], HOLE_HALL[1] + 1, 'MAP_TRUTHSAND_RUINS_HALL_OF_TRUTH', 0, 'sumidouro da Trilha: cai no Hall of Truth')
r.warp(*LADDER_UP, 'MAP_TRUTHSAND_RUINS_HALL_OF_TRUTH', 1, 'escada que volta do Hall')
# ---------------- objetos
r.obj(P + 'PLASMA_CHIEF', 'SCIENTIST_1', 27, 8, 'DOWN', 'TruthsandRuinsB1F_EventScript_PlasmaChief', 'TRAINER_TYPE_NORMAL', '3')
r.obj(P + 'GRUNT', 'SCIENTIST_1', 28, 12, 'UP', 'TruthsandRuinsB1F_EventScript_Grunt', 'TRAINER_TYPE_NORMAL', '3')
r.obj(P + 'GRETA', 'GRETA', 20, 16, 'LEFT', 'TruthsandRuinsB1F_EventScript_Greta')
r.obj(P + 'RUIN_MANIAC', 'HIKER', 5, 18, 'RIGHT', 'TruthsandRuinsB1F_EventScript_RuinManiac', 'TRAINER_TYPE_NORMAL', '4')
r.obj(P + 'ROCK_1', 'BREAKABLE_ROCK', 17, 20, script='EventScript_RockSmash')
r.obj(P + 'ROCK_2', 'BREAKABLE_ROCK', 18, 20, script='EventScript_RockSmash')
r.obj(P + 'ITEM_A', 'ITEM_BALL', 2, 4, script='TruthsandRuinsB1F_EventScript_ItemHardStone')
r.obj(P + 'ITEM_DIG', 'ITEM_BALL', 33, 4, script='TruthsandRuinsB1F_EventScript_ItemRelicSilver')
r.obj(P + 'ITEM_MAZE', 'ITEM_BALL', 33, 19, script='TruthsandRuinsB1F_EventScript_ItemCharcoal')
r.obj(P + 'ITEM_TRAIL', 'ITEM_BALL', 25, 28, script='TruthsandRuinsB1F_EventScript_ItemRelicCrown')
r.bg(17, 21, 'TruthsandRuinsB1F_EventScript_GateInscription')
r.bg(18, 22, 'TruthsandRuinsB1F_EventScript_TrailInscription')
# ---------------- conferencia
T = {'escada': LADDER, 'buraco_hall': (HOLE_HALL[0], HOLE_HALL[1] + 1), 'escada_hall': LADDER_UP}
T.update({o['local_id'][len(P):]: (o['x'], o['y']) for o in r.objs if 'ITEM' in o['local_id']})
for nm, st in LAND.items():
    a, bad = r.check([st], T)
    print('pouso', nm, a)
b, _ = r.check([LAND['A']], T, ignore=[P + 'ROCK_1', P + 'ROCK_2'])
print('pouso A com Rock Smash:', b)
print('bloqueio:', bad)
r.render(D + '/dia.png')
r.render(D + '/colisao.png', overlay=True, marks=[((w['x'], w['y']), (200, 120, 255)) for w in r.warps])
r.save(D, dict(map='TRUTHSAND_RUINS_B1F', ingame='Truthsand Ruins B1F', map_type='MAP_TYPE_UNDERGROUND',
  explorar=['Cada sumidouro do 1F cai num lugar diferente: sala desabada (oeste), cava do Plasma (leste) ou a Trilha da Verdade (sul)',
            'Cava do Plasma: o chefe da escavacao (batalha) e a escada que eles cavaram; Relic Silver no fundo',
            'Labirinto de estatuas e dunas no centro: Greta (Arena Tycoon) cacando tesouro, batalha opcional; Ruin Maniac',
            'Portao da Trilha: duas pedras de Rock Smash; quem nao tem precisa voltar e escolher o 3o sumidouro (a pista do Spenser: a verdade fica ao sul)',
            'Trilha da Verdade: avenida de estatuas ate o sumidouro que desce ao Hall of Truth; Relic Crown escondida no canto; escada de volta do Hall'],
  historia='Ato 6: o Plasma achou o caminho errado (a cava deles nao chega ao Hall). So quem segue a inscricao, andando reto pela Trilha da Verdade, cai na camara da Light Stone.',
  estados={'dia': 'Escavacao do Plasma no leste; Trilha da Verdade isolada ao sul.'},
  conferido='check_objects ok; BFS de cada pouso (A, B, C) para escada, sumidouro do Hall e itens; Trilha so pelo pouso C ou com Rock Smash'))
