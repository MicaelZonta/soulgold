import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__))
SRC = 'GoldenrodBattleArcadeBattleRoom'          # gTileset_ArcadeBattle + gTileset_ArcadeLobby: arquibancada, telao, campo
L = src(SRC)
# alarga 4 colunas de cada lado (repete as colunas de chao 3 e 12) e aprofunda a arquibancada (repete a linha 4)
W0, H0 = L['w'], L['h']
def col_map(X):
    if X < 3: return X
    if X < 3 + 5: return 3                        # 4 copias extras da coluna 3
    if X < 12 + 4: return X - 4
    if X < 12 + 4 + 5: return 12
    return X - 8
def row_map(Y):
    if Y < 4: return Y
    if Y < 6: return 4                            # +1 fileira de assentos
    return Y - 1
MW, MH = W0 + 8, H0 + 1
g = Grid(MW, MH, 0)
for y in range(MH):
    for x in range(MW): g.raw(x, y, L['blocks'][row_map(y) * W0 + col_map(x)])
write_blocks(os.path.join(P, 'border.bin'), [[pack_block(0, 1)] * 2] * 2)
DOOR = (11, MH - 2)                               # acima do capacho (76/77/78)
SCREEN = (11, 8)                                  # telao = quadro de quem esta hoje (placa)
objs = [o('RECEPTIONIST', 'NURSE', 14, MH - 4, 'LEFT', 'FestivalArena_EventScript_Receptionist'),
        # lugares dos desafiantes: bancos laterais (lado esquerdo = vermelho, direito = azul); o script escolhe quem aparece no dia
        o('SEAT_LEFT_1', 'LEON', 3, 9, 'RIGHT', 'FestivalArena_EventScript_ChallengerLeft1', flag='FLAG_TEMP_11'),
        o('SEAT_LEFT_2', 'CYNTHIA', 3, 12, 'RIGHT', 'FestivalArena_EventScript_ChallengerLeft2', flag='FLAG_TEMP_12'),
        o('SEAT_RIGHT_1', 'DIANTHA', 20, 9, 'LEFT', 'FestivalArena_EventScript_ChallengerRight1', flag='FLAG_TEMP_13'),
        o('SEAT_RIGHT_2', 'VOLKNER', 20, 12, 'LEFT', 'FestivalArena_EventScript_ChallengerRight2', flag='FLAG_TEMP_14'),
        o('FAN_1', 'YOUNGSTER', 6, 3, 'DOWN', 'FestivalArena_EventScript_Fan1'),
        o('FAN_2', 'LASS', 15, 4, 'DOWN', 'FestivalArena_EventScript_Fan2'),
        o('FAN_3', 'GENTLEMAN', 18, 3, 'DOWN', 'FestivalArena_EventScript_Fan3')]
saturday = [x for x in objs if not x['local_id'].startswith('SEAT')] + [
        o('SAT_N', 'N', 9, 10, 'RIGHT', 'FestivalArena_EventScript_SaturdayN', flag='FLAG_TEMP_15'),
        o('SAT_HILDA', 'HILDA', 9, 11, 'RIGHT', 'FestivalArena_EventScript_SaturdayHilda', flag='FLAG_TEMP_15')]
BG = [dict(type='sign', x=SCREEN[0], y=SCREEN[1], script='FestivalArena_EventScript_TodaysBoard', nota="telão: \"Today's Challengers\" (rodízio diário; sábado: N & Hilda)"),
      dict(type='sign', x=12, y=SCREEN[1], script='FestivalArena_EventScript_TodaysBoard', nota='mesma placa (telão tem 2 de largura útil)')]
b = g.flat(); d = bfs(b, MW, MH, DOOR)
bad = [x['local_id'] for x in objs + saturday if not alcanca(d, x) and not x['local_id'].startswith('FAN')]; assert not bad, bad
assert alcanca(d, dict(x=SCREEN[0], y=SCREEN[1])), 'telao'
info = dict(map='AbundanceIsle_FestivalArena', ingame='Festival Arena', primary=L['info']['primary_tileset'], secondary=L['info']['secondary_tileset'],
    map_type='MAP_TYPE_INDOOR',
    warps=[dict(x=DOOR[0], y=DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE', dest_warp_id='5', nota='saída para a porta da arena na Cape (31,27)'),
           dict(x=DOOR[0] + 1, y=DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE', dest_warp_id='5', nota='segunda célula do capacho')],
    connections=[], bg_events=BG,
    explorar=['Arena pós-jogo com arquibancada cheia de torcedores, telão e campo no centro (base: sala de batalha do Battle Arcade de Goldenrod, alargada).',
              "Telão = quadro \"Today's Challengers\": diz quem está hoje. Rodízio diário do elenco do Nexus nos quatro lugares dos bancos laterais (exemplo no render: Leon, Cynthia, Diantha, Volkner).",
              'Aos sábados os bancos ficam vazios e N e Hilda esperam juntos à beira do campo para uma batalha em dupla.',
              'Recepcionista perto da porta explica as regras (uma revanche por desafiante por dia).',
              'Torcedores na arquibancada (cenário, atrás do parapeito; script NULL ou fala por placa no parapeito).'],
    historia='Pós-jogo da ilha: depois da primavera, a vila do cabo faz um festival e os campeões que vieram pela tempestade ficam para revanches.',
    estados={'dia': 'Dia comum: quatro desafiantes de exemplo nos bancos.', 'estado': 'Sábado: N e Hilda à beira do campo, bancos vazios.'},
    conferido='Peças só de GoldenrodBattleArcadeBattleRoom (mesmo par de tilesets), alargada repetindo colunas de chão e a fileira de assentos; BFS da porta até todos os NPCs e o telão; check_objects. Atenção: o mapa original não tem warp — o capacho 77 é bloqueado, por isso o warp está na célula de chão logo acima; conferir o comportamento de saída na instalação.')
entregar(P, g, L['prim'], L['sec'], info, objs, estado=True, estado_objs=saturday)
