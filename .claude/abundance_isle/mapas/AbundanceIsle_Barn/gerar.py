import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from interior import *
D = os.path.dirname(os.path.abspath(__file__))
# fardo de feno extra (2x2, pecas do proprio celeiro) fechando um cantinho com item escondido atras
EDITS = [(10, 16, 0x444, 1), (11, 16, 0x445, 1), (10, 17, 0x44c, 1), (11, 17, 0x44d, 1)]
OBJ = [o('MILTANK', 'OBJ_EVENT_GFX_SPECIES(MILTANK)', 13, 5, 'DOWN', 'AbundanceBarn_EventScript_Miltank'),
       o('KID', 'TWIN', 12, 5, 'RIGHT', 'AbundanceBarn_EventScript_Kid'),
       o('MAREEP_1', 'OBJ_EVENT_GFX_SPECIES(MAREEP)', 3, 12, 'DOWN', 'AbundanceBarn_EventScript_Mareep'),
       o('MAREEP_2', 'OBJ_EVENT_GFX_SPECIES(MAREEP)', 4, 12, 'LEFT', 'AbundanceBarn_EventScript_Mareep'),
       o('TAUROS', 'OBJ_EVENT_GFX_SPECIES(TAUROS)', 13, 12, 'LEFT', 'AbundanceBarn_EventScript_Tauros'),
       o('FARFETCHD', 'OBJ_EVENT_GFX_SPECIES(FARFETCHD)', 4, 5, 'DOWN', 'AbundanceBarn_EventScript_Farfetchd'),
       o('ITEM_LEFTOVERS', 'ITEM_BALL', 12, 17, script='AbundanceBarn_EventScript_ItemLeftovers')]
interior(D, 'Route39_Barn', dict(map='AbundanceIsle_Barn', ingame='Abundance Barn',
    warps=[dict(x=8, y=18, dest_map='MAP_ABUNDANCE_ISLE', dest_warp_id='2', nota='porta do celeiro no hub (30,23)')], connections=[],
    explorar=['Miltank tremendo de frio na baia: o menino pede 3 berries para aquece-la; em troca, Moomoo Milk toda semana.',
              'Fardo de feno novo esconde um cantinho a direita da porta: Leftovers.',
              'Mareep, Tauros e Farfetch\'d nas baias (Farfetch\'d foge para fora no inverno e volta na primavera).'],
    historia='Ato 1: mostra o custo do inverno na fazenda (animais doentes, colheita parada).',
    estados=dict(dia='Interior do celeiro com os animais.')), OBJ, (8, 18), EDITS)
