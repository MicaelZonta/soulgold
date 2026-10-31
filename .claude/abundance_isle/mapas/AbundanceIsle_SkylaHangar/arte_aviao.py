import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from desenho import Tela
OL = (32, 32, 48)
def aviao(body, light, dark, wing, wingl, prop=(96, 96, 104), extra=None, floats=False, biplane=False):
    t = Tela(64, 48)
    if floats:
        for y in (14, 30): t.rect(14, y, 50, y + 3, (232, 232, 224)); t.hline(14, 50, y, (255, 255, 255))
    t.rect(4, 18, 58, 28, wing); t.hline(4, 58, 18, wingl)                     # asa (vista de cima)
    if biplane: t.rect(8, 14, 54, 16, wing); t.rect(8, 30, 54, 32, wing)
    t.poly([(30, 2), (34, 2), (36, 10), (37, 40), (34, 46), (30, 46), (27, 40), (28, 10)], body)  # fuselagem
    t.vline(30, 6, 42, light); t.vline(35, 8, 42, dark)
    t.rect(22, 40, 42, 44, wing); t.hline(22, 42, 40, wingl)                     # leme horizontal
    t.rect(29, 4, 35, 8, (120, 200, 240)); t.hline(30, 34, 5, (200, 240, 255))   # cabine
    for x in (14, 50): t.ellipse(x, 17, 3, 2, dark); t.hline(x - 5, x + 5, 15, prop)   # motores e helices
    t.hline(27, 37, 1, prop)
    if extra: extra(t)
    t.outline(OL); return t
def A():  # cargueiro azul da Skyla (bimotor)
    return aviao((88, 152, 232), (168, 208, 248), (48, 96, 176), (216, 224, 232), (248, 248, 248),
                 extra=lambda t: (t.rect(31, 22, 33, 26, (232, 88, 72))))
def B():  # biplano amarelo de entregas
    return aviao((240, 200, 64), (248, 232, 144), (184, 136, 40), (200, 72, 56), (240, 120, 96), biplane=True)
def C():  # hidroaviao com flutuadores
    return aviao((232, 232, 240), (255, 255, 255), (144, 152, 176), (72, 136, 200), (128, 184, 232), floats=True)
def D():  # aviao coberto por lona, preso por cordas (estado "Grounded")
    t = Tela(64, 48)
    t.poly([(4, 20), (30, 4), (34, 4), (60, 20), (58, 30), (36, 44), (28, 44), (6, 30)], (96, 120, 88))
    t.poly([(4, 20), (30, 4), (32, 4), (32, 44), (28, 44), (6, 30)], (120, 148, 104))
    for x0 in (10, 22, 42, 54): t.line(x0, 14, x0 - 4, 38, (200, 176, 120))
    for y in (18, 26, 34): t.hline(8, 56, y, (72, 92, 64))
    t.rect(29, 1, 35, 4, (88, 152, 232))
    t.outline(OL); return t
PROPOSTAS = [('A', 'Cargueiro azul (bimotor)', A), ('B', 'Biplano de entregas', B), ('C', 'Hidroavião', C), ('D', 'Coberto pela lona (preso pela tempestade)', D)]
