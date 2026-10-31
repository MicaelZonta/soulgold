"""Light Stone (Reshiram adormecido), 32x32, <=15 cores. Par da Pedra Escura (arte_pedra.py):
mesmas quatro ideias, em branco com fogo; a C e a gemea da Pedra Escura C escolhida pelo autor."""
import sys, math
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from desenho import Tela
OL = (88, 88, 104)
WH = [(232, 232, 240), (248, 248, 255), (200, 204, 220), (168, 172, 192)]   # base, brilho, sombra, sombra funda
FI = [(248, 104, 48), (255, 192, 88), (200, 56, 40)]                        # fogo: laranja, amarelo, vermelho
def A():   # oval branca com veios de fogo
    t = Tela(32, 32)
    t.ellipse(16, 18, 10, 12, WH[0]); t.ellipse(19, 22, 6, 7, WH[2]); t.ellipse(13, 13, 5, 5, WH[1])
    pts = [(15, 8), (18, 15), (13, 17), (17, 26)]
    for a, b in zip(pts, pts[1:]): t.line(*a, *b, FI[0])
    t.px(18, 15, FI[1]); t.px(13, 17, FI[1])
    t.outline(OL); return t
def B():   # no pedestal de arenito, com brasas soltas
    t = Tela(32, 32)
    t.rect(7, 25, 24, 30, (200, 168, 112)); t.hline(7, 24, 25, (232, 208, 152)); t.rect(9, 22, 22, 24, (176, 140, 96))
    t.ellipse(16, 13, 7, 9, WH[0]); t.ellipse(18, 16, 4, 5, WH[2]); t.ellipse(14, 9, 3, 3, WH[1])
    for x, y in ((10, 4), (23, 6), (25, 16), (6, 14)): t.px(x, y, FI[1]); t.px(x + 1, y, FI[0])
    t.outline(OL); return t
def C():   # escama facetada com espiral: gemea da Pedra Escura C
    t = Tela(32, 32)
    t.poly([(16, 3), (26, 12), (25, 24), (16, 30), (7, 24), (6, 12)], WH[0])
    t.poly([(16, 3), (26, 12), (16, 14)], WH[2]); t.poly([(6, 12), (16, 3), (16, 14)], WH[1])
    for i in range(40):
        a = i * .35; r = 1 + i * .18
        t.px(16 + r * math.cos(a), 20 + r * math.sin(a) * .8, WH[3])
    t.px(16, 20, FI[0]); t.px(17, 20, FI[1])
    t.outline(OL); return t
def D():   # despertando: aura de chamas
    t = Tela(32, 32)
    for i in range(24):
        a = i / 24 * 2 * math.pi; r = 13 + (2 if i % 2 else 0)
        t.px(16 + r * math.cos(a), 17 + r * math.sin(a) * 1.05, FI[0] if i % 3 else FI[1])
    t.ellipse(16, 17, 8, 10, WH[0]); t.ellipse(18, 20, 5, 6, WH[2]); t.ellipse(14, 13, 3, 4, WH[1])
    t.line(12, 9, 15, 15, FI[2]); t.line(15, 15, 12, 18, FI[0])
    return t
PROPOSTAS = [('A', 'Oval com veios de fogo', A), ('B', 'No pedestal de arenito', B),
             ('C', 'Escama em espiral (gemea da Pedra Escura C)', C), ('D', 'Despertando (aura de chamas)', D)]
