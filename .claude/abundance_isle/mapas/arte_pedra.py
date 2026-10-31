import sys; sys.path.insert(0, '.')
from desenho import Tela
OL = (16, 16, 24)
BK = [(40, 40, 56), (72, 72, 96), (112, 112, 144), (24, 24, 32)]
BL = [(80, 160, 248), (168, 216, 255), (248, 248, 120)]
def A():   # pedra oval com rachaduras de raio azul
    t = Tela(32, 32)
    t.ellipse(16, 18, 10, 12, BK[0]); t.ellipse(13, 13, 5, 5, BK[1]); t.ellipse(12, 11, 2, 2, BK[2])
    pts = [(17, 8), (14, 15), (19, 17), (15, 26)]
    for a, b in zip(pts, pts[1:]): t.line(*a, *b, BL[0])
    t.px(14, 15, BL[1]); t.px(19, 17, BL[1])
    t.outline(OL); return t
def B():   # pedra sobre pedestal de pedra
    t = Tela(32, 32)
    t.rect(7, 25, 24, 30, (136, 120, 104)); t.hline(7, 24, 25, (176, 160, 136)); t.rect(9, 22, 22, 24, (112, 96, 88))
    t.ellipse(16, 13, 7, 9, BK[0]); t.ellipse(14, 9, 3, 3, BK[1]); t.px(13, 8, BK[2])
    for x, y in ((10, 4), (23, 6), (25, 16), (6, 14)): t.px(x, y, BL[1]); t.px(x + 1, y, BL[0])
    t.outline(OL); return t
def C():   # semente/escama (inspirada no formato oficial): espiral e cristas
    t = Tela(32, 32)
    t.poly([(16, 3), (26, 12), (25, 24), (16, 30), (7, 24), (6, 12)], BK[0])
    t.poly([(16, 3), (26, 12), (16, 14)], BK[1]); t.poly([(6, 12), (16, 3), (16, 14)], BK[2])
    import math
    for i in range(40):
        a = i * .35; r = 1 + i * .18
        t.px(16 + r * math.cos(a), 20 + r * math.sin(a) * .8, BK[2])
    t.px(16, 20, BL[0]); t.px(17, 20, BL[1])
    t.outline(OL); return t
def D():   # pedra envolta em aura eletrica (estado "despertando")
    t = Tela(32, 32)
    import math
    for i in range(24):
        a = i / 24 * 2 * math.pi
        r = 13 + (2 if i % 2 else 0)
        t.px(16 + r * math.cos(a), 17 + r * math.sin(a) * 1.05, BL[0] if i % 3 else BL[2])
    t.ellipse(16, 17, 8, 10, BK[0]); t.ellipse(14, 13, 3, 4, BK[1]); t.px(13, 11, BK[2])
    t.line(21, 9, 18, 15, BL[1]); t.line(18, 15, 21, 18, BL[1])
    return t
PROPOSTAS = [('A', 'Oval com veios de raio', A), ('B', 'No pedestal', B), ('C', 'Escama em espiral', C), ('D', 'Despertando (aura)', D)]
