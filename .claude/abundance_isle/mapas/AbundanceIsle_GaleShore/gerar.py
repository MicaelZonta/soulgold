import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__))
MW, MH = 46, 32
W_, S_, G_, F_, X_ = 'W', 'S', 'G', 'F', 'X'
T = [[W_] * MW for _ in range(MH)]
def land(x, y):
    dx, dy = (x + .5 - 23) / 21.0, (y + .5 - 10) / 9.0
    return abs(dx) ** 3 + abs(dy) ** 3 <= 1
for y in range(MH):
    for x in range(MW):
        if land(x, y): T[y][x] = G_
for y in range(16, 22):                          # ponta de areia ao sul (praia larga onde se chega de Surf)
    for x in range(18, 28):
        if T[y][x] == W_ and abs(x - 22.5) <= (22 - y) * 1.2 + 2: T[y][x] = G_
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
MT = (8, 3, 30, 9)
for y in range(MT[1] - 1, MT[3] + 2):
    for x in range(MT[0] - 1, MT[2] + 2):
        if T[y][x] == G_: T[y][x] = X_
ISLET = (5, 22, 9, 24)                           # ilhota de areia dentro da laguna (so de Surf)
for y in range(ISLET[1], ISLET[3] + 1):
    for x in range(ISLET[0], ISLET[2] + 1): T[y][x] = S_
g = Grid(MW, MH, pack_block(JOHTO['water'], 0, 1))
for y in range(MH):
    for x in range(MW):
        t = T[y][x]
        if t == W_: continue
        if t == S_: g.set(x, y, pick_sand(T, x, y, grassy=('G', 'F', 'X')))
        else: g.set(x, y, JOHTO['grass'])
plateau(g, *MT)
plateau(g, 13, 4, 24, 6, on='rock', base=False)
for y in (8, 9): g.set(27, y, 137); g.set(28, y, 145)
for y in (5, 6): g.set(14, y, 137); g.set(15, y, 145)
CAVE = (11, 9); g.set(*CAVE, 169, 0)
# circulo de pedras esculpidas pelo vento: onde o Tornadus pousa (abertura a oeste)
CX, CY = 37, 10
RING = [(CX + dx, CY + dy) for dx in range(-3, 4) for dy in range(-3, 4) if max(abs(dx), abs(dy)) == 3 and not (dx == -3 and dy in (0, 1))]
for p in RING:
    if T[p[1]][p[0]] in (G_, X_): g.set(*p, 167, 1)
for y in range(CY - 2, CY + 3):
    for x in range(CX - 2, CX + 3): g.set(x, y, 10)                 # capim alto dentro do circulo (o vento deita)
# laguna: pedras no mar fechando a ilhota
LAG = [(2, 19), (4, 19), (6, 19), (8, 19), (10, 20), (11, 22), (10, 25), (2, 26), (4, 26), (6, 26), (8, 26), (0, 22)]
for rx, ry in LAG:
    if all(0 <= ry + dy < MH and 0 <= rx + dx < MW and T[ry + dy][rx + dx] == W_ for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']): g.set(rx + dx, ry + dy, mid, 1, 1)
for rx, ry in ((40, 22), (34, 26), (14, 27), (42, 3)):
    if all(0 <= ry + dy < MH and 0 <= rx + dx < MW and T[ry + dy][rx + dx] == W_ for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']): g.set(rx + dx, ry + dy, mid, 1, 1)
SIGN = (24, 12); g.set(*SIGN, 2, 1)
for y in range(12, 16):                          # capim alto varrido pelo vento
    for x in range(7, 17):
        if T[y][x] == G_ and (x + y) % 5: g.set(x, y, 10)
for p in ((19, 14), (28, 15), (6, 11)):
    if T[p[1]][p[0]] == G_: g.set(*p, 167, 1)
write_blocks(os.path.join(P, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
base = [
    o('WINONA', 'WINONA', CX - 5, CY, 'RIGHT', 'GaleShore_EventScript_Winona'),
    o('ITEM_PLATEAU', 'ITEM_BALL', 20, 5, script='GaleShore_EventScript_ItemFloatStone'),
    o('ITEM_ISLET', 'ITEM_BALL', 7, 23, script='GaleShore_EventScript_ItemPearlString'),
    o('ITEM_RING', 'ITEM_BALL', CX + 2, CY - 2, script='GaleShore_EventScript_ItemAirBalloon'),
    o('FISHERMAN', 'FISHERMAN', 22, 19, 'DOWN', 'GaleShore_EventScript_Fisherman', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('BEAUTY', 'BEAUTY', 30, 13, 'LEFT', 'GaleShore_EventScript_Beauty', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('HIKER', 'HIKER', 26, 6, 'LEFT', 'GaleShore_EventScript_Hiker', ttype='TRAINER_TYPE_NORMAL', sight='3'),
]
storm = base + [o('TORNADUS', 'SPECIES(TORNADUS)', CX, CY, 'LEFT', 'GaleShore_EventScript_Tornadus', flag='FLAG_HIDE_GALE_SHORE_TORNADUS')]
b = g.flat()
start = (CAVE[0], CAVE[1] + 1)
d = bfs(b, MW, MH, start); ds = bfs_surf(b, MW, MH, start)
rep = {'circulo do Tornadus': (CX, CY) in d, 'item do platô': alcanca(d, base[1]), 'item do círculo': alcanca(d, base[3]),
       'ilhota só de Surf': alcanca(ds, base[2]) and not alcanca(d, base[2]), 'praia sul (chegada de Surf)': (22, 21) in ds}
print(rep); assert all(rep.values()), rep
def estado(bb):
    return render_blocks(bb, MW, MH, src('CianwoodCity')['prim'], src('CianwoodCity')['sec'], objects=storm)
info = dict(map='AbundanceIsle_GaleShore', ingame='Gale Shore', primary='gTileset_Johto_General', secondary='gTileset_CianwoodCity',
    map_type='MAP_TYPE_ROUTE',
    warps=[dict(x=CAVE[0], y=CAVE[1], dest_map='MAP_ABUNDANCE_ISLE_GALE_CAVE', dest_warp_id='1', nota='boca da caverna no pé do penhasco -> saída norte da Gale Cave')],
    connections=[dict(direction='south', map='MAP_ABUNDANCE_ISLE', offset=0, nota='mar dos dois lados: Surf a partir da praia norte do hub')],
    explorar=['Círculo de pedras esculpidas pelo vento, com o capim deitado: é onde o Tornadus cai exausto (ato 3). Air Balloon no canto do círculo.',
              'Winona (especialista em voadores, de Hoenn) estuda o Tornadus na beira do círculo: explica que ele está ferido, não bravo, e depois da captura oferece batalha opcional.',
              'Penhasco em dois níveis com a saída da Gale Cave; Float Stone no topo.',
              'Laguna fechada por pedras no mar a sudoeste, com uma ilhota de areia: Pearl String, só de Surf.',
              'Prado de capim alto a oeste (encontros de voadores); praia larga ao sul onde se chega de Surf vindo do hub; pescador, Beauty e Hiker como treinadores.'],
    historia='Praia ao norte, atrás da montanha do hub. Depois que a máquina da cratera para, o Tornadus cai no círculo de pedras: batalha de captura (ato 3).',
    estados={'dia': 'Praia antes do ato 3 (sem o Tornadus).', 'estado': 'Ato 3: Tornadus pousado no círculo de pedras, Winona observando.'},
    conferido='BFS da saída da caverna: círculo, platô e itens alcançáveis a pé; ilhota só com Surf; praia sul alcançável de Surf; check_objects.')
L = src('CianwoodCity')
entregar(P, g, L['prim'], L['sec'], info, base, estado=estado, estado_objs=storm)
