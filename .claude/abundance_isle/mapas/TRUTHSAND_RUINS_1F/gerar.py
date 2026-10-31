"""Truthsand Ruins 1F: entrada, avenida das estatuas, acampamento de escavacao do Plasma (escada
deles para o B1F), galeria dos sumidouros (3 buracos que derrubam para o B1F) e a antecamara
das inscricoes, com um cofre atras de pedra de Rock Smash."""
import sys, os; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)) + '/..')
from ruina_kit import *
D = os.path.dirname(os.path.abspath(__file__))
P = 'LOCALID_TRUTHSAND_RUINS_1F_'
r = Ruina(36, 30)
# ---------------- salas
r.room(11, 18, 24, 25)          # saguao de entrada (avenida das estatuas)
r.room(17, 26, 18, 28)          # corredor da saida
r.room(17, 29, 17, 29)          # abertura para fora
r.room(17, 14, 18, 17)          # corredor saguao -> antecamara
r.room(12, 6, 23, 13)           # antecamara das inscricoes
r.room(8, 6, 10, 8)             # cofre (atras da pedra)
r.room(11, 7, 11, 7)            # fresta da pedra
r.room(2, 12, 8, 24)            # acampamento do Plasma
r.room(9, 22, 10, 23)           # passagem saguao -> acampamento
r.room(27, 8, 34, 24)           # galeria dos sumidouros
r.room(25, 21, 26, 22)          # passagem saguao -> galeria
r.room(24, 9, 26, 10)           # passagem antecamara -> galeria (alto)
r.paint()
# ---------------- decoracao e funcoes
r.door(17, 29)
r.path([(x, y) for x in (17, 18) for y in range(18, 29)])
for y in (19, 22): r.statue(13, y); r.statue(22, y, right=True)
for x in (14, 21): r.statue(x, 7)                               # estatuas da antecamara
r.skeleton(30, 20); r.dune(32, 10); r.dune(28, 16); r.dune(32, 18)
r.crate(3, 13); r.crate(6, 18); r.crate(3, 21); r.scaffold(5, 12, 3)
LADDER = (7, 14); r.ladder(*LADDER)
HOLES = [(29, 11), (33, 14), (29, 22)]
for h in HOLES: r.hole(*h)
# ---------------- warps
r.warp(17, 29, 'MAP_EMBERDUNE_ISLE', 0, 'saida para a Emberdune Isle')
r.warp(*LADDER, 'MAP_TRUTHSAND_RUINS_B1F', 0, 'escada do Plasma (cava deles)')
for i, (x, y) in enumerate(HOLES):
    r.warp(x, y + 1, 'MAP_TRUTHSAND_RUINS_B1F', 1 + i, 'sumidouro %d (cai no B1F)' % (i + 1))
# ---------------- objetos
r.obj(P + 'SPENSER', 'SPENSER', 18, 9, 'UP', 'TruthsandRuins1F_EventScript_Spenser')
r.obj(P + 'LUCY', 'LUCY', 14, 24, 'UP', 'TruthsandRuins1F_EventScript_Lucy')
r.obj(P + 'GRUNT_LADDER', 'SCIENTIST_1', 7, 15, 'DOWN', 'TruthsandRuins1F_EventScript_GruntLadder', 'TRAINER_TYPE_NORMAL', '2')
r.obj(P + 'GRUNT_CAMP', 'SCIENTIST_1', 4, 17, 'RIGHT', 'TruthsandRuins1F_EventScript_GruntCamp', 'TRAINER_TYPE_NORMAL', '4')
r.obj(P + 'RUIN_MANIAC', 'HIKER', 31, 13, 'LEFT', 'TruthsandRuins1F_EventScript_RuinManiac', 'TRAINER_TYPE_NORMAL', '3')
r.obj(P + 'ROCK', 'BREAKABLE_ROCK', 11, 7, 'DOWN', 'EventScript_RockSmash')
r.obj(P + 'ITEM_VAULT', 'ITEM_BALL', 8, 6, script='TruthsandRuins1F_EventScript_ItemRelicGold')
r.obj(P + 'ITEM_CAMP', 'ITEM_BALL', 2, 24, script='TruthsandRuins1F_EventScript_ItemDigKit')
r.obj(P + 'ITEM_FOSSIL', 'ITEM_BALL', 31, 21, script='TruthsandRuins1F_EventScript_ItemSoftSand')
r.obj(P + 'ITEM_GALLERY', 'ITEM_BALL', 34, 8, script='TruthsandRuins1F_EventScript_ItemStardust')
r.bg(18, 5, 'TruthsandRuins1F_EventScript_MuralTruth')         # parede de cima da antecamara
r.bg(12, 25, 'TruthsandRuins1F_EventScript_Sign')
# ---------------- conferencia
T = {'saida': (17, 28), 'escada': LADDER, 'cofre': (8, 7), 'mural': (18, 6)}
T.update({'buraco%d' % (i + 1): (x, y + 1) for i, (x, y) in enumerate(HOLES)})
T.update({o['local_id'][len(P):]: (o['x'], o['y']) for o in r.objs if 'ITEM' in o['local_id']})
sem, bad = r.check([(17, 28)], T)                             # pedra de pe
com, _ = r.check([(17, 28)], T, ignore=[P + 'ROCK'])            # pedra quebrada
print('bloqueio:', bad)
print('sem Rock Smash:', sem); print('com Rock Smash:', com)
r.render(D + '/dia.png')
r.render(D + '/colisao.png', overlay=True, marks=[((w['x'], w['y']), (200, 120, 255)) for w in r.warps])
r.save(D, dict(map='TRUTHSAND_RUINS_1F', ingame='Truthsand Ruins 1F', map_type='MAP_TYPE_UNDERGROUND',
  explorar=['Avenida de estatuas da entrada: Lucy (Pike Queen) estuda o silencio das ruinas; batalha opcional depois do ato 6',
            'Antecamara das inscricoes: Spenser medita diante do mural do Heroi da Verdade (conta a lenda e da a pista dos sumidouros)',
            'Cofre secreto atras de pedra de Rock Smash: Relic Gold (eco da Relic Castle)',
            'Acampamento de escavacao do Plasma: caixotes, escoras, dois recrutas e a escada que eles cavaram ate o B1F',
            'Galeria dos sumidouros: tres buracos de areia; cada um derruba numa parte diferente do B1F (so um leva ao caminho certo)',
            'Esqueleto fossil e Soft Sand ao lado; Stardust no canto da galeria; Ruin Maniac (treinador)'],
  historia='Ato 6: a Lenora juntou a estela e descobriu que os seguidores do Heroi da Verdade esconderam a Light Stone sob estas ruinas. O Plasma ja esta escavando: o jogador decide entre a escada deles (guardada) e os sumidouros.',
  estados={'dia': 'Ruinas com a escavacao do Plasma em andamento.'},
  conferido='check_objects ok; BFS da saida alcanca escada, os 3 sumidouros, o mural e os itens (o cofre so com Rock Smash)'))
