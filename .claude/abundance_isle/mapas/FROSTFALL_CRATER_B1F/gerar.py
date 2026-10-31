import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from crater_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
c = Cave(36, 30)
c.room(26, 3, 33, 7)        # R chegada (escada do 1F)
c.room(29, 8, 30, 11)       # R -> L
c.room(24, 12, 33, 26)      # L lago congelado
c.room(21, 19, 23, 20)      # L -> P
c.room(5, 3, 20, 20)        # P salao de gelo
c.room(4, 8, 4, 9)          # P -> G
c.room(1, 7, 3, 11)         # G saida para o laboratorio
c.walls()
c.ladder_up(30, 3, 'MAP_FROSTFALL_CRATER_1F', '1', 'sobe para a camara norte do 1F (12,4)')
c.ladder_down(2, 10, 'MAP_FROSTFALL_CRATER_LAB', '0', 'meta do quebra-cabeca: desce para o laboratorio')
c.ladder_up(32, 12, 'MAP_FROSTFALL_CRATER_CORE', '0', 'volta do Core (sobe do fundo)') if False else None
# ---- lago (leste): Icy Rock numa ilha, alcancada deslizando
c.ice(25, 13, 32, 25)
LAKE_ITEM = (28, 19); c.g.set(*LAKE_ITEM, FLOOR, 0)
for p in ((25, 14), (31, 13), (29, 15), (26, 21), (32, 22), (27, 25), (30, 24)): c.ball(*p)
c.big(32, 3); c.big(26, 3)
# volta do Core: escada na parede norte do lago
c.ladder_down(33, 26, 'MAP_FROSTFALL_CRATER_CORE', '0', 'escada no canto do lago para o Core (o buraco e o atalho secreto)')
# ---- salao de gelo
for y in range(3, 19):
    for x in range(5, 21): c.g.set(x, y, ICE, 0)
ITEM = (5, 3); c.g.set(*ITEM, FLOOR, 0)
GOAL = (4, 8)
cand = [(x, y) for y in range(4, 19) for x in range(5, 21) if (x, y) not in (ITEM,) and not (x == 5 and y in (8, 9))]
# ---- objetos
c.obj('BYRON', 'BYRON', 26, 12, 'DOWN', 'FrostfallCrater_B1F_EventScript_Byron')
c.obj('ITEM_ICYROCK', 'ITEM_BALL', *LAKE_ITEM, script='FrostfallCrater_B1F_EventScript_ItemIcyRock')
c.obj('ITEM_NEVERMELT', 'ITEM_BALL', *ITEM, script='FrostfallCrater_B1F_EventScript_ItemNeverMeltIce')
c.obj('SCIENTIST', 'SCIENTIST_1', 22, 19, 'LEFT', 'FrostfallCrater_B1F_EventScript_PlasmaScientist', ttype='TRAINER_TYPE_NORMAL', sight='3')
c.obj('BOARDER', 'CAMPER', 13, 20, 'UP', 'FrostfallCrater_B1F_EventScript_Camper', ttype='TRAINER_TYPE_NORMAL', sight='2')
base = [r[:] for r in c.g.b]
warps0 = list(c.warps)
best = None; rng = random.Random(23)
for trial in range(9000):
    rocks = rng.sample(cand, 16)
    hole = rng.choice([p for p in cand if p not in rocks and 8 <= p[0] <= 18 and 6 <= p[1] <= 16])
    c.g.b = [r[:] for r in base]
    for p in rocks: c.ball(*p)
    c.g.set(*hole, 0x406, 0); c.warps = warps0 + [dict(x=hole[0], y=hole[1], dest_map='', dest_warp_id='', nota='')]
    d = c.reach((12, 20))
    g = d.get((2, 10))
    it, h = c.can_take(d, ITEM), d.get(hole)
    if g and it and h and 9 <= g <= 16 and it >= 7 and h >= 6:
        sc = g + it + h
        if not best or sc > best[0]: best = (sc, rocks, hole, g, it, h)
assert best, 'sem quebra-cabeca'
_, ROCKS, HOLE, G, IT, H = best
c.g.b = [r[:] for r in base]; c.warps = warps0
for p in ROCKS: c.ball(*p)
c.hole(*HOLE, 'MAP_FROSTFALL_CRATER_CORE', '1', 'buraco secreto numa ilha de pedra no meio do gelo: cai no Core')
c.big(18, 19) if False else None
for p in ((22, 26), (25, 8)): pass
c.icicle(24, 25) if False else None
# ---- verificacao
d = c.reach((30, 4))
for nome, p in (('meta', (2, 10)), ('buraco', HOLE), ('escada core', (33, 26))):
    assert p in d, nome
for nome, p in (('lago', LAKE_ITEM), ('item', ITEM), ('byron', (26, 12))):
    assert c.can_take(d, p) is not None, nome
pth = c.path((30, 4), (2, 10))
c.save(OUT, dict(map='FROSTFALL_CRATER_B1F', ingame='Frostfall Crater B1F', map_type='MAP_TYPE_UNDERGROUND', connections=[],
    explorar=['Salao de gelo 16x16: %d movimentos ate a escada do laboratorio' % G,
              'Never-Melt Ice no canto mais dificil do gelo (%d movimentos)' % IT,
              'Buraco secreto numa ilha de pedra no meio do gelo (%d movimentos): cai no Core' % H,
              'Lago congelado com Icy Rock numa ilha, alcancada deslizando',
              'Byron (mineiro, Canalave) no lago estudando lascas do meteorito: explica que a rocha "nao e deste mundo" e aponta o fundo da cratera; batalha opcional',
              'Cientista do Plasma vigiando a passagem do lago para o salao; Camper treinando no gelo'],
    historia='Andar do frio puro: o fragmento do meteorito congelou o lago subterraneo. O caminho ao laboratorio exige atravessar o salao de gelo.',
    estados={'dia': 'Andar com o quebra-cabeca (rosa no mapa de colisao = solucao ate o laboratorio).'},
    conferido='check_objects ok; quebra-cabeca gerado por busca e conferido por BFS com deslize sobre o map.bin final: escada (30,4) -> meta, item, buraco e escada do Core.'),
    path=pth)
print('ok B1F', G, IT, H, HOLE, c.warps)
