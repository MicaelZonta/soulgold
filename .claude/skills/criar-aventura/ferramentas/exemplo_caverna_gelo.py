import os
import sys, json, random; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from kit_aventura import *
OUT = sys.argv[1]; os.makedirs(OUT, exist_ok=True)
MW, MH = 36, 31
SNOW, FLOOR, ICE, BALL = 0x411, 0x459, 0x4cb, 0x4c7
floor = [[False] * MW for _ in range(MH)]
def room(x0, y0, x1, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1): floor[y][x] = True
room(14, 24, 21, 27)   # A  entrada
room(17, 19, 18, 23)   # corredor A -> H
room(12, 15, 23, 18)   # H  saguao dos recrutas
room(11, 16, 11, 17)   # passagem H -> P
room(2, 2, 10, 17)     # P  sala do gelo (quebra-cabeca)
room(11, 4, 11, 5)     # saida do quebra-cabeca -> laboratorio
room(12, 2, 31, 8)     # L  laboratorio do Ghetsis
room(24, 16, 24, 17)   # passagem H -> E
room(25, 12, 33, 22)   # E  lago congelado
room(28, 9, 29, 11)    # atalho L <-> E (fechado por gelo ate a maquina parar)
F = lambda x, y: 0 <= x < MW and 0 <= y < MH and floor[y][x]
g = Grid(MW, MH, pack_block(SNOW, 1))
for y in range(MH):
    for x in range(MW):
        if floor[y][x]: g.set(x, y, FLOOR, 0); continue
        sig = ''.join('1' if F(x + dx, y + dy) else '0' for dx, dy in NB8)
        if '1' in sig: g.set(x, y, cave_wall(sig), 1)
EXIT = (17, 28); g.set(*EXIT, 0x407, 0)
# ---------------- P: gelo nas linhas 2..15, chao nas 16..17. Meta: sair por (11,4)/(11,5)
PUZ = [(x, y) for y in range(2, 16) for x in range(2, 11)]
for x, y in PUZ: g.set(x, y, ICE, 0)
ITEM_P = (2, 2)                                   # canto do gelo: Never-Melt Ice
g.set(*ITEM_P, FLOOR, 0)
# ---------------- E: lago congelado com ilha de item no meio (mini quebra-cabeca)
for y in range(13, 21):
    for x in range(26, 33): g.set(x, y, ICE, 0)
ITEM_E = (29, 16); g.set(*ITEM_E, FLOOR, 0)
for p in ((26, 13), (32, 14), (27, 19), (31, 20), (30, 13), (28, 15)): g.set(*p, BALL, 1)
# atalho: parede de gelo (bola de neve) bloqueando ate a maquina parar
SHORTCUT = [(28, 10), (29, 10)]
for p in SHORTCUT: g.set(*p, BALL, 1)
# ---------------- decoracao
def big(x, y):
    for (dx, dy), m in zip(((0, 0), (1, 0), (0, 1), (1, 1)), (0x41d, 0x41e, 0x425, 0x426)): g.set(x + dx, y + dy, m, 1)
big(12, 7); big(30, 2); big(14, 26) if False else None
for x, y in ((13, 15), (22, 15), (20, 24), (14, 24), (25, 21), (33, 12)): g.set(x, y, 0x41f, 1); g.set(x, y + 1, 0x427, 1)
MACHINE = (20, 2)
for y in range(2):
    for x in range(3): g.set(MACHINE[0] + x, MACHINE[1] + y, FLOOR, 1)
# ---------------- quebra-cabeca: procura pedras de neve que deem um caminho com varios deslizes
base = g.flat()
PUZ_SET = set(PUZ)
def run(rocks):
    b = list(base)
    for x, y in rocks: b[y * MW + x] = pack_block(BALL, 1)
    walk = lambda x, y: not (b[y * MW + x] >> 11 & 1)
    ice = lambda x, y: (b[y * MW + x] & 0x7ff) == ICE
    return slide_reach((6, 17), walk, ice, MW, MH)
cand = [p for p in PUZ if p != ITEM_P and p[1] <= 14 and p not in ((10, 4), (10, 5))]
best = None; rng = random.Random(11)
for trial in range(6000):
    rocks = rng.sample(cand, 10)
    d = run(rocks)
    goal = min([d[c] for c in ((11, 4), (11, 5)) if c in d], default=None)
    item = d.get(ITEM_P)
    if goal and item and 6 <= goal <= 9 and item >= goal:
        sc = goal * 2 + item
        if not best or sc > best[0]: best = (sc, sorted(rocks), goal, item)
assert best, 'sem quebra-cabeca'
ROCKS = best[1]
for p in ROCKS: g.set(*p, BALL, 1)
# conferir: tudo alcancavel a partir da entrada (atalho fechado)
blocks = g.flat()
walk = lambda x, y: not (blocks[y * MW + x] >> 11 & 1)
ice = lambda x, y: (blocks[y * MW + x] & 0x7ff) == ICE
d = slide_reach((17, 27), walk, ice, MW, MH)
for name, c in (('item gelo', ITEM_P), ('item lago', ITEM_E), ('laboratorio', (21, 6))):
    print(name, c, 'passos' if c in d else 'INALCANCAVEL', d.get(c))
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(SNOW, 1)] * 2] * 2)
json.dump(dict(w=MW, h=MH, exit=EXIT, machine=MACHINE, rocks=ROCKS, item_p=ITEM_P, item_e=ITEM_E,
               shortcut=SHORTCUT, goal_moves=best[2], item_moves=best[3]), open(os.path.join(OUT, 'info.json'), 'w'))
print('quebra-cabeca: meta em', best[2], 'deslizes; item em', best[3])
