import sys, json; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
OUT = sys.argv[1]; os.makedirs(OUT, exist_ok=True)
MW, MH = 46, 54
W_, S_, G_, F_, X_ = 'W', 'S', 'G', 'F', 'X'    # X = reservado (montanha, fazenda, lago): grama por baixo
T = [[W_] * MW for _ in range(MH)]
def land(x, y):
    dx, dy = (x + .5 - 23) / 21.4, (y + .5 - 25.5) / 24.0
    return abs(dx) ** 4 + abs(dy) ** 4 <= 1
for y in range(MH):
    for x in range(MW):
        if land(x, y): T[y][x] = G_
# enseada a leste: o mar entra (praia escondida atras da floresta)
for y in range(33, 41):
    for x in range(40, MW): T[y][x] = W_
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
MT = (7, 4, 38, 16)
fill(MT[0] - 1, MT[2] + 1, MT[1] - 1, MT[3] + 1, X_)
FARM = (27, 19, 40, 31)                        # cerca da fazenda (inclusive)
fill(FARM[0], FARM[2], FARM[1], FARM[3], X_)
POND = (6, 24, 13, 28)                         # lago do santuario
fill(POND[0] - 1, POND[2] + 1, POND[1] - 1, POND[3] + 1, X_)
# trilhas
fill(22, 23, 17, 48, S_)                       # eixo norte-sul ate o cais
fill(8, 26, 32, 33, S_)                        # rua oeste: santuario <-> eixo
fill(15, 17, 19, 31, S_)                       # rua da praca ate a rua oeste
fill(7, 17, 22, 23, S_)                        # adro do santuario, entre ele e o lago
fill(24, 32, 32, 33, S_)                       # rua leste ate a porteira da fazenda
fill(31, 32, 31, 32, S_, only=(G_, X_))
# florestas em colunas de 2, escalonadas
def col(x0, y0, y1):
    for y in range(y0, y1 + 1):
        if all(0 <= x < MW and T[y][x] == G_ and not near(x, y, (S_, W_), 1) for x in (x0, x0 + 1)):
            T[y][x0] = T[y][x0 + 1] = F_
def region(x0, x1, y0, y1):
    for i, cx in enumerate(range(x0, x1, 2)):
        col(cx, y0 + (i % 2), y1 - ((i + 1) % 2))
region(2, 6, 5, 22); region(39, 44, 5, 18)
region(2, 12, 35, 47)                          # mata oeste
region(39, 44, 20, 32)
CLEAR = (29, 39, 34, 42)                       # clareira secreta dentro da mata leste
for i, cx in enumerate(range(25, 39, 2)):      # mata leste fechada, colunas escalonadas
    for y in range(35 + i % 2, 47 - (i + 1) % 2):
        inside = CLEAR[0] <= cx <= CLEAR[2] and CLEAR[1] <= y <= CLEAR[3]
        trail = cx == 33 and y < CLEAR[1]
        if not inside and not trail and all(T[y][x] == G_ for x in (cx, cx + 1)) and T[y + 1][cx] != S_:
            T[y][cx] = T[y][cx + 1] = F_
g = Grid(MW, MH, pack_block(JOHTO['water'], 0, 1))
for y in range(MH):
    for x in range(MW):
        t = T[y][x]
        if t == W_: continue
        if t == S_: g.set(x, y, pick_sand(T, x, y, grassy=('G', 'F', 'X')))
        elif t == F_: g.set(x, y, pick_forest(T, x, y), 1)
        else:
            b = tree_base(T, x, y)
            g.set(x, y, b, 1) if b else g.set(x, y, JOHTO['grass'])
# ---------------- montanha em tres niveis
plateau(g, *MT)
plateau(g, 11, 5, 34, 11, on='rock', base=False)
plateau(g, 17, 6, 28, 8, on='rock', base=False)
for y in (MT[3] - 1, MT[3]): g.set(22, y, 137); g.set(23, y, 145)
for y in (10, 11): g.set(15, y, 137); g.set(16, y, 145)          # escada do nivel 2 fica a oeste: obriga a rodear
FROST = (11, MT[3]); g.set(*FROST, 169, 0)
SUMMIT = (25, 8); g.set(*SUMMIT, 169, 0)
BOULDERS = [(9, 7), (36, 9), (31, 13), (13, 13), (30, 6), (33, 10)]
for p in BOULDERS: g.set(*p, 167, 1)
# ---------------- lago do santuario (pecas do lago da Route 31, agua elevacao 1)
x0, y0, x1, y1 = POND
for y in range(y0, y1 + 1):
    for x in range(x0, x1 + 1):
        L, R, Tp, B = x == x0, x == x1, y == y0, y == y1
        m = (0x1a5 if L else 0x1a7 if R else 0x1a6) if Tp else (0x268 if L else 0x269 if R else 0x1d1) if B else (0x1a0 if L else 0x1a2 if R else 0x1a1)
        g.set(x, y, m, 0, 1)
for p in ((8, 26), (11, 25)): g.set(*p, 0x1fa, 0, 1)        # vitorias-regias
SHRINE = (9, 19)                                            # santuario 3x3 (desenho novo), de frente para o lago
for y in range(3):
    for x in range(3): g.set(SHRINE[0] + x, SHRINE[1] + y, 1, 1)
# ---------------- fazenda: cerca do primario, celeiro e casa da Route 39 (mesmos tilesets)
fx0, fy0, fx1, fy1 = FARM
GATE = (31, 32)
for x in range(fx0, fx1 + 1):
    g.set(x, fy0, 0xe7, 1); g.set(x, fy1, 0xd6 if (x - fx0) % 2 == 0 else 0xd7, 1)
for y in range(fy0, fy1 + 1):
    g.set(fx0, y, 0xf4, 1); g.set(fx1, y, 0xf5, 1)
g.set(fx0, fy0, 0xec, 1); g.set(fx1, fy0, 0xed, 1); g.set(fx1, fy1, 0xfd, 1)
g.set(31, fy1, 277); g.set(32, fy1, 277)                     # porteira aberta no sul
for y in range(fy0 + 1, fy1):
    for x in range(fx0 + 1, fx1): g.set(x, y, JOHTO['grass'])
stamp(g, 'Route39', 12, 12, 6, 4, 28, 20)                   # celeiro (Abundance Barn)
stamp(g, 'Route39', 18, 13, 4, 3, 35, 21)                   # casa do fazendeiro
BARN_DOOR, HOUSE_DOOR = (30, 23), (36, 23)
for y in range(24, 26):
    for x in range(29, 38): g.set(x, y, 0xd9)               # terreiro de terra
FIELD = [(x, y) for y in range(26, 31) for x in range(29, 39)]
for x, y in FIELD: g.set(x, y, 10)                          # plantacao = capim alto (encontros)
# ---------------- jardim (Enamorus): canteiros ao redor da praca
FLOWERS = [(x, y) for y in range(29, 32) for x in range(4, 15) if T[y][x] == G_]          # canteiro sul do lago
FLOWERS += [(x, y) for y in range(17, 22) for x in range(5, 18) if T[y][x] == G_
            and not (SHRINE[0] - 1 <= x <= SHRINE[0] + 3 and y >= SHRINE[1] - 1) and (x + y) % 3 == 0]
FLOWERS += [(x, y) for y in range(24, 29) for x in range(4, 6) if T[y][x] == G_]
FLOWERS += [(x, y) for y in range(24, 29) for x in range(14, 15) if T[y][x] == G_]
for cx, cy in ((13, 37), (17, 39), (14, 41), (8, 37)):    # touceiras 2x2
    FLOWERS += [(cx + dx, cy + dy) for dx in (0, 1) for dy in (0, 1) if T[cy + dy][cx + dx] == G_ and not tree_base(T, cx + dx, cy + dy)]
for p in FLOWERS: g.set(*p, JOHTO['flowers'])
# capim alto: prados do leste e ao pe da montanha
GRASS = [(x, y) for y in range(18, 31) for x in range(24, 27) if T[y][x] == G_]
GRASS += [(x, y) for y in range(17, 20) for x in range(28, 40) if T[y][x] in (G_, X_) and y < FARM[1]]
GRASS += [(x, y) for y in range(43, 48) for x in range(13, 21) if T[y][x] == G_]
GRASS += [(x, y) for y in range(18, 31) for x in range(18, 21) if T[y][x] == G_]
GRASS += [(x, y) for y in range(5, 22) for x in range(2, 7) if T[y][x] == G_]
GRASS += [(x, y) for y in range(5, 18) for x in range(39, 44) if T[y][x] == G_]
for p in GRASS: g.set(*p, 10)
# arvore de Cut fechando a trilha da clareira, placas, pedras no mar
CUT = (33, 34); g.set(*CUT, JOHTO["grass"], 0)   # a arvore e o objeto CUT_TREE
SIGNS = {'island': (21, 47), 'shrine': (14, 21), 'farm': (33, 33)}
for p in SIGNS.values(): g.set(*p, 2, 1)
for rx, ry in ((2, 49), (41, 50), (1, 3), (42, 2), (43, 36)):
    if all(0 <= ry + dy < MH and 0 <= rx + dx < MW and T[ry + dy][rx + dx] == W_ for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']): g.set(rx + dx, ry + dy, mid, 1, 1)
pier_top = max(y for y in range(MH) if T[y][22] == S_) + 1
for y in range(pier_top, pier_top + 3):
    for i, x in enumerate((21, 22, 23)): g.set(x, y, JOHTO['pier'][i])
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
json.dump(dict(w=MW, h=MH, shrine=SHRINE, frost=FROST, summit=SUMMIT, barn_door=BARN_DOOR, house_door=HOUSE_DOOR,
               pier_top=pier_top, cut=CUT, clear=CLEAR, signs=SIGNS, flowers=FLOWERS, pond=POND),
          open(os.path.join(OUT, 'info.json'), 'w'))
print('ok pier', pier_top)
