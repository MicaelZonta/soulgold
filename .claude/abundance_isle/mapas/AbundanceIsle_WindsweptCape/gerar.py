import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__))
MW, MH = 44, 42
W_, S_, G_, F_, X_ = 'W', 'S', 'G', 'F', 'X'
T = [[W_] * MW for _ in range(MH)]
def land(x, y):
    dx, dy = (x + .5 - 26) / 16.5, (y + .5 - 16) / 15.5
    return abs(dx) ** 3.5 + abs(dy) ** 3.5 <= 1
for y in range(MH):
    for x in range(MW):
        if land(x, y): T[y][x] = G_
def near(x, y, cls, r):
    for dy in range(-r, r + 1):
        for dx in range(-r, r + 1):
            xx, yy = x + dx, y + dy
            if not (0 <= xx < MW and 0 <= yy < MH) or T[yy][xx] in cls: return True
    return False
beach = [[T[y][x] == G_ and near(x, y, (W_,), 2) for x in range(MW)] for y in range(MH)]
for y in range(MH):
    for x in range(MW):
        if beach[y][x]: T[y][x] = S_
def fill(x0, x1, y0, y1, c, only=(G_,)):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if T[y][x] in only: T[y][x] = c
MT = (25, 3, 39, 13)                       # penhasco do cabo
fill(MT[0] - 1, MT[2] + 1, MT[1] - 1, MT[3] + 1, X_)
fill(12, 24, 14, 22, S_)                   # vila (areia)
fill(17, 18, 23, 29, S_)                   # rua ate o cais do Plasma
fill(25, 37, 15, 16, S_)                   # rua leste ao pe do penhasco
ARENA = (28, 23)                           # fachada da Festival Arena (ginasio de Cianwood, 7x5)
fill(ARENA[0] - 1, ARENA[0] + 7, ARENA[1] - 1, ARENA[1] + 5, S_)
fill(19, 30, 28, 29, S_)                   # rua da arena ate a vila
fill(31, 31, 14, 14, S_, only=(G_, X_))
# quebra-mar: lingua de areia saindo da praia oeste (3 linhas)
for y in range(19, 22):
    for x in range(3, 14):
        if T[y][x] == W_: T[y][x] = S_
for i, cx in enumerate(range(12, 22, 2)):  # bosque ao norte da vila (colunas escalonadas)
    for y in range(5 + i % 2, 12 - (i + 1) % 2):
        if all(T[y][x] == G_ and not near(x, y, (S_, W_), 1) for x in (cx, cx + 1)): T[y][cx] = T[y][cx + 1] = F_
g = Grid(MW, MH, pack_block(JOHTO['water'], 0, 1))
for y in range(MH):
    for x in range(MW):
        t = T[y][x]
        if t == W_: continue
        if t == S_: g.set(x, y, pick_sand(T, x, y, grassy=('G', 'F', 'X')))
        elif t == F_: g.set(x, y, pick_forest(T, x, y), 1)
        else:
            b = tree_base(T, x, y); g.set(x, y, b, 1) if b else g.set(x, y, JOHTO['grass'])
plateau(g, *MT)
plateau(g, 29, 4, 37, 8, on='rock', base=False)
for y in (12, 13): g.set(36, y, 137); g.set(37, y, 145)            # escada do penhasco
for y in (7, 8): g.set(30, y, 137); g.set(31, y, 145)              # escada do mirante
CAVE = (31, 13); g.set(*CAVE, 169, 0)
for p in ((27, 5), (38, 10), (33, 11)): g.set(*p, 167, 1)
# vila: Centro Pokemon e duas casas (carimbos de Cianwood, mesmo par de tilesets)
PC = (14, 14); stamp(g, 'CianwoodCity', 29, 41, 5, 5, *PC); PC_DOOR = (PC[0] + 2, PC[1] + 4)
HOUSES = [(20, 15), (13, 20)]
for hx, hy in HOUSES: stamp(g, 'CianwoodCity', 22, 36, 4, 4, hx, hy)
HDOORS = [(hx + 1, hy + 3) for hx, hy in HOUSES]
# cais do Plasma (sul) e quebra-mar (oeste)
dock_top = max(y for y in range(MH) if T[y][18] == S_) + 1
DOCK = list(range(dock_top, dock_top + 7))
for y in DOCK:
    for i, x in enumerate((16, 17, 18)): g.set(x, y, JOHTO['pier'][i])
FRIGATE_WARP = (18, DOCK[-1])
bw_x, west_top = 4, 19
# capim alto e pedras no mar (o vento)
for y in range(17, 23):
    for x in range(26, 36):
        if T[y][x] == G_: g.set(x, y, 10)
for rx, ry in ((40, 20), (41, 26), (36, 32), (6, 10), (4, 30), (30, 36), (40, 4)):
    if all(0 <= ry + dy < MH and 0 <= rx + dx < MW and T[ry + dy][rx + dx] == W_ for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']): g.set(rx + dx, ry + dy, mid, 1, 1)
SIGN = (19, 22); g.set(*SIGN, 2, 1)
stamp(g, 'CianwoodCity', 12, 40, 7, 5, *ARENA); ARENA_DOOR = (ARENA[0] + 3, ARENA[1] + 4)
ARENA_SIGN = (ARENA[0] - 1, ARENA[1] + 4); g.set(*ARENA_SIGN, 2, 1)
write_blocks(os.path.join(P, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
objs = [
    o('PLASMA_FRIGATE', 'SS_TIDAL', 21, DOCK[-1], 'LEFT', '0x0', elev=1),
    o('GRUNT_DOCK_1', 'SCIENTIST_1', 16, dock_top, 'DOWN', 'WindsweptCape_EventScript_DockGuard1'),
    o('GRUNT_DOCK_2', 'SCIENTIST_1', 17, dock_top, 'DOWN', 'WindsweptCape_EventScript_DockGuard2'),
    o('GRUNT_DOCK_3', 'SCIENTIST_1', 18, dock_top, 'DOWN', 'WindsweptCape_EventScript_DockGuard3'),
    o('NESSA', 'NESSA', bw_x, west_top + 1, 'LEFT', 'WindsweptCape_EventScript_Nessa'),
    o('SKYLA', 'SKYLA', 33, 6, 'UP', 'WindsweptCape_EventScript_Skyla'),
    o('ITEM_LOOKOUT', 'ITEM_BALL', 35, 5, script='WindsweptCape_EventScript_ItemPrettyFeather'),
    o('ITEM_GROVE', 'ITEM_BALL', 22, 7, script='WindsweptCape_EventScript_ItemWindStoneShard'),
    o('ITEM_CLIFF', 'ITEM_BALL', 38, 9, script='WindsweptCape_EventScript_ItemStarPiece'),
    o('SAILOR', 'SAILOR', 22, 21, 'LEFT', 'WindsweptCape_EventScript_Sailor'),
    o('BIRDKEEPER', 'YOUNGSTER', 30, 19, 'RIGHT', 'WindsweptCape_EventScript_Youngster', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('FISHERMAN', 'FISHERMAN', 37, 26, 'DOWN', 'WindsweptCape_EventScript_Fisherman', ttype='TRAINER_TYPE_NORMAL', sight='2'),
]
b = g.flat()
start = PC_DOOR[0], PC_DOOR[1] + 1
d = bfs(b, MW, MH, start, extra_block={(x['x'], x['y']) for x in objs if x['local_id'].startswith('GRUNT')})
d_all = bfs(b, MW, MH, start)
rep = {'boca da Gale Cave': CAVE in d, 'mirante (Skyla/item)': alcanca(d, objs[4]) and alcanca(d, objs[5]),
       'item do bosque': alcanca(d, objs[6]), 'item do penhasco': alcanca(d, objs[7]),
       'quebra-mar (Nessa)': alcanca(d, objs[3]),
       'cais do navio bloqueado pelos guardas': FRIGATE_WARP not in d, 'cais livre sem guardas': FRIGATE_WARP in d_all,
       'casas': all((x, y + 1) in d for x, y in HDOORS), 'arena': (ARENA_DOOR[0], ARENA_DOOR[1] + 1) in d}
print(rep)
if not all(rep.values()):
    L0 = src('CianwoodCity'); write_png(os.path.join(P, 'debug.png'), render_blocks(b, MW, MH, L0['prim'], L0['sec'], objects=objs, overlay=True), 2); print('dock_top', dock_top, 'bw_x', bw_x, HDOORS); raise SystemExit(1)
info = dict(map='AbundanceIsle_WindsweptCape', ingame='Windswept Cape', primary='gTileset_Johto_General', secondary='gTileset_CianwoodCity',
    map_type='MAP_TYPE_TOWN',
    warps=[dict(x=PC_DOOR[0], y=PC_DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_POKEMON_CENTER', dest_warp_id='0', nota='porta do PC'),
           dict(x=FRIGATE_WARP[0], y=FRIGATE_WARP[1], dest_map='MAP_PLASMA_FRIGATE_DECK', dest_warp_id='0', nota='prancha no fim do cais -> convés do Plasma Frigate (fork C)'),
           dict(x=CAVE[0], y=CAVE[1], dest_map='MAP_ABUNDANCE_ISLE_GALE_CAVE', dest_warp_id='0', nota='boca da Gale Cave no pé do penhasco'),
           dict(x=HDOORS[0][0], y=HDOORS[0][1], dest_map='MAP_ABUNDANCE_ISLE_SKYLA_HANGAR', dest_warp_id='0', nota="casa 1 -> Skyla's Hangar"),
           dict(x=HDOORS[1][0], y=HDOORS[1][1], dest_map='MAP_ABUNDANCE_ISLE_ELDER_HOUSE', dest_warp_id='0', nota="casa 2 -> Elder's House"),
           dict(x=ARENA_DOOR[0], y=ARENA_DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_FESTIVAL_ARENA', dest_warp_id='0', nota='porta da Festival Arena (fachada = ginasio de Cianwood)')],
    connections=[dict(direction='west', map='MAP_ABUNDANCE_ISLE', offset=0, nota='mar dos dois lados: chega-se de Surf vindo do hub')],
    explorar=['Vila do cabo com o único Centro Pokémon da ilha, o galpão do avião da Skyla e a casa do ancião que toca o sino às 18h.',
              'Penhasco em dois níveis: escada leva ao mirante, onde está Skyla, a piloto de Unova presa pela tempestade; ela vigia o céu e conta que viu dois vultos (Tornadus e Thundurus) brigando nas nuvens. Batalha opcional depois que a tempestade acaba.',
              'Pretty Feather no mirante e Star Piece numa ponta do penhasco.',
              'Quebra-mar (língua de areia) a oeste: Nessa treina seus Pokémon de Água nas ondas da tempestade; batalha opcional e fala sobre o mar quente demais para essa neve (pista do plano do Ghetsis).',
              'Cais ao sul com o Plasma Frigate ancorado; três recrutas fecham o cais até o ato 2.',
              'Festival Arena (fachada de ginásio) no prado sul: revanches do elenco do Nexus em rodízio diário; placa na porta.',
              'Boca da Gale Cave ao pé do penhasco (passagem para a Gale Shore).',
              'Bosque com item escondido, prado de capim alto e pedras no mar castigadas pelo vento.'],
    historia='Porto do cabo, onde o Plasma Frigate está ancorado. É a base de apoio do Ghetsis na ilha; o cais fica fechado pelos recrutas até a máquina da cratera parar.',
    estados={'dia': 'Cabo com o navio do Plasma (placeholder: SS Tidal) e os guardas no cais.'},
    conferido='BFS a partir do PC: Gale Cave, mirante, itens, quebra-mar e casas alcançáveis; cais do navio fechado com os guardas e livre sem eles; check_objects.',
    frigate_dock=dict(warp=FRIGATE_WARP, navio=(21, DOCK[-1])))
L = src('CianwoodCity')
entregar(P, g, L['prim'], L['sec'], info, objs)
