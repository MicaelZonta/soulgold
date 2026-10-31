import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from crater_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
c = Cave(28, 24)
c.room(3, 5, 22, 19)        # M camara da cratera
c.room(23, 10, 24, 11)      # M -> Z (passagem estreita)
c.room(25, 7, 26, 13)       # Z nicho da Zinnia
c.walls()
c.ladder_up(12, 20, 'MAP_FROSTFALL_CRATER_B1F', '2', 'sobe para o canto do lago do B1F (33,26)') if False else None
# escada na parede norte da sala de chegada nao existe (ela fica abaixo da camara): sobe pela parede oeste da camara
c.ladder_up(5, 5, 'MAP_FROSTFALL_CRATER_B1F', '2', 'sobe para o canto do lago do B1F (33,26)')
LAND = (12, 18); c.warp(*LAND, 'MAP_FROSTFALL_CRATER_B1F', '3', 'pouso do buraco do salao de gelo (warp de chegada)')
# cratera: anel de pedras de neve em volta de um lago de gelo; no centro, a ilha do Icicle Plate
c.ice(7, 8, 18, 15)
ISLE = (12, 11); c.g.set(*ISLE, FLOOR, 0); c.g.set(13, 11, FLOOR, 0)
RING = [(7, 8), (9, 8), (16, 8), (18, 9), (18, 13), (16, 15), (10, 15), (7, 14), (13, 9), (11, 13), (15, 12), (8, 11)]
for p in RING: c.ball(*p)
c.big(3, 15); c.big(20, 5); c.big(3, 9) if False else None
for p in ((20, 16), (6, 17), (21, 12), (4, 12)): c.icicle(*p)
# passagem da Zinnia escondida atras de estalactites: so 1 celula livre
c.g.set(22, 9, 0x41f, 1)
c.obj('ZINNIA', 'ZINNIA', 25, 9, 'DOWN', 'FrostfallCrater_Core_EventScript_Zinnia')
c.obj('ITEM_ICICLEPLATE', 'ITEM_BALL', *ISLE, script='FrostfallCrater_Core_EventScript_ItemIciclePlate')
c.obj('ITEM_DRAGONFANG', 'ITEM_BALL', 26, 13, script='FrostfallCrater_Core_EventScript_ItemDragonFang')
c.obj('ITEM_HIDDEN_NUGGET', 'ITEM_BALL', 21, 18, script='FrostfallCrater_Core_EventScript_ItemCometShard')
d = c.reach(LAND)
assert (5, 5) in d, 'escada'
for nome, p in (('placa', ISLE), ('zinnia', (25, 9)), ('dragon fang', (26, 13)), ('comet', (21, 18))):
    assert c.can_take(d, p) is not None, nome
nb = [(ISLE[0] + dx, ISLE[1] + dy) for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)) if (ISLE[0] + dx, ISLE[1] + dy) in d]
pth = c.path(LAND, min(nb, key=lambda q: d[q]))
c.save(OUT, dict(map='FROSTFALL_CRATER_CORE', ingame='Frostfall Crater Core', map_type='MAP_TYPE_UNDERGROUND', connections=[],
    explorar=['Camara da cratera: lago de gelo cercado de pedras de neve; o Icicle Plate fica na ilha do centro, alcancada deslizando (%d movimentos)' % c.can_take(d, ISLE),
              'Nicho escondido a leste, atras de estalactites (passagem de 1 celula): Zinnia e uma Dragon Fang',
              'Zinnia (guardia da lore dos meteoros e dragoes) conta que o Kyurem caiu num meteorito de gelo e e a "casca vazia" do dragao original; batalha opcional; se o jogador tem Kyurem na equipe, fala especial',
              'Comet Shard escondido no canto sudeste (lasca do meteorito)',
              'So se chega aqui pelo buraco do salao de gelo ou pela escada do canto do lago (B1F)'],
    historia='O fundo da cratera, onde o fragmento do meteorito do Kyurem caiu. Andar opcional: segredo e lore.',
    estados={'dia': 'Camara com a Zinnia no nicho.'},
    conferido='check_objects ok; BFS do pouso do buraco (12,18) ate a escada, a ilha do centro, o nicho da Zinnia e o Comet Shard.'),
    path=pth)
print('ok CORE', c.warps)
