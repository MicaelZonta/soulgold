import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from interior import *
D = os.path.dirname(os.path.abspath(__file__))
OBJ = [o('FARMER_GRANDPA', 'BALDING_MAN', 4, 4, 'DOWN', 'AbundanceFarmhouse_EventScript_Grandpa'),
       o('FARMER_WIFE', 'WOMAN_3', 7, 5, 'LEFT', 'AbundanceFarmhouse_EventScript_Wife'),
       o('ITEM_BIG_ROOT', 'ITEM_BALL', 10, 7, script='AbundanceFarmhouse_EventScript_ItemBigRoot')]
interior(D, 'Route39_FarmHouse', dict(map='AbundanceIsle_Farmhouse', ingame='Farmhouse',
    warps=[dict(x=4, y=8, dest_map='MAP_ABUNDANCE_ISLE', dest_warp_id='3', nota='porta da casa no hub (36,23)')], connections=[],
    explorar=['A esposa deixa a equipe descansar na mesa (cura completa): a ilha nao tem Centro no hub.',
              'O avo conta como era a ilha antes do inverno e a cancao da colheita (pista do santuario).',
              'Big Root no canto do quarto.'],
    historia='Ato 1: ponto de descanso e de pistas; o avo manda o jogador ao guardiao em Harvest Fields.',
    estados=dict(dia='Interior da casa.')), OBJ, (4, 8))
