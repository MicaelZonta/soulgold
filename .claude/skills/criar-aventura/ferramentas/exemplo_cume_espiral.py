import os
import sys, json; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from kit_aventura import *
OUT = sys.argv[1]; os.makedirs(OUT, exist_ok=True)
SRC = 'SpearPillarTop'
MW, MH = 40, 45
g = Grid(MW, MH, 0)
put(g, nine(SRC, 0, 0, 32, 31, MW, 31, cx=21, px=2, cy=0, py=1), 0, 0)      # ceu, encosta e patio alargados
lower = nine(SRC, 0, 31, 32, 14, MW, 14, cx=31, px=1, cy=0, py=1)           # base: mantida, completa a direita
put(g, lower, 0, 31)
FLOOR, B1, B2, B3 = 0x404, 0x401, 0x402, 0x403
X0, Y0, X1, Y1 = 9, 7, 30, 21                                                 # interior do patio
for y in range(Y0, Y1 + 1):
    for x in range(X0, X1 + 1): g.set(x, y, FLOOR, 0)
# ---- espiral (Dragonspiral): paredes de colunas em pe (2 alturas) e caidas (2 larguras)
#  legenda: | coluna em pe (topo na celula), = coluna caida (2 celulas), b coluna quebrada
SPIRAL = [
    "......................",
    ".=.=.=.=.=.=.=.=.=....",
    ".|......|...........|.",
    "......................",
    ".|..=.=.=.=.=.=.....|.",
    "...............|......",
    ".|..................|.",
    "....|..........|......",
    ".|..................|.",
    "....=.=.=.=.=.=.......",
    ".|..................|.",
    "......................",
    ".=.=.=.=.=.=.=.=.=.=..",
    "......................",
    "......................",
]
for j, row in enumerate(SPIRAL):
    for i, c in enumerate(row):
        x, y = X0 + i, Y0 + j
        if c == '=': g.set(x, y, 0x425, 1); g.set(x + 1, y, 0x426, 1)
        elif c == '|': g.set(x, y, 0x42a, 1); g.set(x, y + 1, 0x432, 1)
        elif c == 'b': g.set(x, y, 0x42c, 1); g.set(x, y + 1, 0x434, 1)
# ---- altar no centro: mosaico 401/402/403
AX0, AY0, AX1, AY1 = X0 + 6, Y0 + 5, X0 + 13, Y0 + 8
for y in range(AY0, AY1 + 1):
    for x in range(AX0, AX1 + 1):
        edge = x in (AX0, AX1) or y in (AY0, AY1)
        ring = x in (AX0 + 1, AX1 - 1) or y in (AY0 + 1, AY1 - 1)
        g.set(x, y, B1 if edge else B2 if ring else B3, 0)
STONE = ((AX0 + AX1) // 2, (AY0 + AY1) // 2)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[read_blocks(os.path.join(ROOT, layout_info(SRC)['border_filepath']))[i] for i in (0, 1)],
                                              [read_blocks(os.path.join(ROOT, layout_info(SRC)['border_filepath']))[i] for i in (2, 3)]])
# alcance a partir da base
b = g.flat()
walk = lambda x, y: not (b[y * MW + x] >> 11 & 1)
d = slide_reach((15, 33), walk, lambda x, y: False, MW, MH)
print('pedra escura', STONE, 'passos', d.get((STONE[0], STONE[1] + 1)))
for j in range(Y0 - 1, Y1 + 3):
    print(''.join('o' if (x, j) in d else ('#' if not walk(x, j) else '.') for x in range(X0 - 1, X1 + 2)))
json.dump(dict(w=MW, h=MH, stone=STONE, patio=(X0, Y0, X1, Y1)), open(os.path.join(OUT, 'info.json'), 'w'))
