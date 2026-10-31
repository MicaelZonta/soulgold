import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__))
SRC = 'UnionCave_1F'                                   # johto_general + cave_default
MW, MH = 40, 28
FILL, FLOOR, ROCK = 0x411, 0x401, 0x403
floor = [[False] * MW for _ in range(MH)]
def room(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1): floor[y][x] = True
room(15, 20, 24, 25)     # sala sul (entrada pela Windswept Cape)
room(18, 18, 20, 19)     # corredor
room(3, 6, 36, 17)       # salao dos ventos
room(5, 18, 5, 19)       # passagem da sala escondida (fechada por pedra quebravel)
room(3, 20, 9, 24)       # sala escondida
room(33, 4, 34, 5)       # corredor norte
room(30, 2, 36, 3)       # sala norte (saida para Gale Shore)
F = lambda x, y: 0 <= x < MW and 0 <= y < MH and floor[y][x]
g = Grid(MW, MH, pack_block(FILL, 1))
for y in range(MH):
    for x in range(MW):
        if floor[y][x]: g.set(x, y, FLOOR, 0); continue
        sig = ''.join('1' if F(x + dx, y + dy) else '0' for dx, dy in NB8)
        if '1' in sig: g.set(x, y, cave_wall(sig), 1)
SOUTH = (19, 26); g.set(*SOUTH, 0x407, 0); g.set(19, 27, 0x449, 1)
NORTH = (33, 2); g.set(33, 1, 0x40c, 1); g.set(*NORTH, 0x414, 0)
def pool(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            L, R, T, B = x == x0, x == x1, y == y0, y == y1
            m = (0x4a1 if L else 0x4a3 if R else 0x4a2) if T else (0x4b0 if L else 0x4b8 if R else 0x4b4) if B else (0x4a9 if L else 0x4ab if R else 0x4aa)
            g.set(x, y, m, 0, 1)
pool(23, 6, 30, 17)      # lago que corta o salao: o lado leste (e a saida norte) so de Surf
pool(7, 9, 12, 13)       # poca a oeste
# rochas: corredores de vento (fileiras que formam um labirinto curto no oeste do salao)
ROCKS = [(14, 7), (15, 7), (16, 7), (17, 7), (14, 9), (14, 10), (14, 11), (17, 10), (18, 10), (19, 10), (20, 10),
         (17, 13), (17, 14), (17, 15), (20, 14), (21, 14), (4, 15), (5, 15), (8, 16), (34, 8), (35, 12), (32, 15),
         (16, 23), (23, 21), (4, 22), (8, 21)]
for p in ROCKS: g.set(*p, ROCK, 1)
write_blocks(os.path.join(P, 'border.bin'), [[pack_block(FILL, 1)] * 2] * 2)
BOULDER = (20, 12)
objs = [
    o('BREAKABLE_ROCK', 'BREAKABLE_ROCK', 5, 18, script='EventScript_RockSmash'),
    o('BOULDER', 'PUSHABLE_BOULDER', *BOULDER, script='EventScript_StrengthBoulder'),
    o('ITEM_SMOOTHROCK', 'ITEM_BALL', 35, 16, script='GaleCave_EventScript_ItemSmoothRock'),
    o('ITEM_BIGPEARL', 'ITEM_BALL', 4, 21, script='GaleCave_EventScript_ItemBigPearl'),
    o('ITEM_SHARPBEAK', 'ITEM_BALL', 15, 8, script='GaleCave_EventScript_ItemSharpBeak'),
    o('HIKER', 'HIKER', 21, 21, 'LEFT', 'GaleCave_EventScript_Hiker', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('GRUNT', 'SCIENTIST_1', 31, 8, 'LEFT', 'GaleCave_EventScript_PlasmaScout', ttype='TRAINER_TYPE_NORMAL', sight='4'),
    o('NOLAND', 'NOLAND', 7, 22, 'RIGHT', 'GaleCave_EventScript_Noland'),
]
b = g.flat()
d_walk = bfs(b, MW, MH, (19, 25), extra_block={(5, 18), BOULDER})
d_surf = bfs_surf(b, MW, MH, (19, 25), extra_block={(5, 18), BOULDER})
d_all = bfs_surf(b, MW, MH, (19, 25))
rep = {
 'saida norte a pe': NORTH in d_walk, 'saida norte com Surf': NORTH in d_surf,
 'Smooth Rock (leste, Surf)': alcanca(d_surf, objs[2]) and not alcanca(d_walk, objs[2]),
 'sala escondida fechada sem Rock Smash': not alcanca(d_surf, objs[3]), 'sala escondida com Rock Smash': alcanca(d_all, objs[3]),
 'Sharp Beak': alcanca(d_walk, objs[4]),
}
print(rep); assert all(v for k, v in rep.items() if k != 'saida norte a pe') and not rep['saida norte a pe']
info = dict(map='AbundanceIsle_GaleCave', ingame='Gale Cave', primary='gTileset_Johto_General', secondary='gTileset_Cave_Default',
    map_type='MAP_TYPE_UNDERGROUND',
    warps=[dict(x=SOUTH[0], y=SOUTH[1], dest_map='MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE', dest_warp_id='2', nota='boca da caverna na Windswept Cape'),
           dict(x=NORTH[0], y=NORTH[1], dest_map='MAP_ABUNDANCE_ISLE_GALE_SHORE', dest_warp_id='0', nota='buraco na parede norte -> Gale Shore')],
    connections=[],
    explorar=['Salão dos Ventos com fileiras de pedras formando corredores curtos; Sharp Beak no canto do labirinto.',
              'Um lago corta o salão de norte a sul: a saída para a Gale Shore e a Smooth Rock só com Surf.',
              'Pedra de Rock Smash esconde uma sala a sudoeste com a Big Pearl.',
              'Pedra de Strength no meio do salão (atalho entre as fileiras).',
              'Desafio escondido na sala secreta: Noland (Frontier Brain da Battle Factory) treina ali longe da tempestade; batalha opcional forte, uma vez.',
              'Batedor do Plasma vigia o lado leste do lago; Hiker na sala da entrada.'],
    historia='Passagem por baixo do cabo ligando a Windswept Cape à Gale Shore. O vento da tempestade assobia pelas fendas (texto de ambiente); o batedor do Plasma procura o lugar onde o Tornadus vai cair.',
    estados={'dia': 'Caverna com objetos (pedra quebrável, pedra de Strength, itens, treinadores, Noland).'},
    conferido='Paredes pela tabela aprendida (cave_wall) de UnionCave/DarkCave; peças do lago de UnionCave_1F (elevação 1); saídas 0x407/0x449 e 0x40c/0x414 como nos mapas originais; BFS: saída norte só com Surf, sala secreta só com Rock Smash; check_objects.')
L = src(SRC)
entregar(P, g, L['prim'], L['sec'], info, objs)
