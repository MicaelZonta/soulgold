import sys; sys.path.insert(0, '.')
from desenho import Tela
OL = (32, 32, 48)
ICE = [(120, 200, 240), (184, 232, 248), (248, 248, 255), (64, 136, 200)]
MET = [(96, 104, 120), (144, 152, 168), (56, 60, 72), (200, 208, 216)]
PL = [(40, 64, 152), (248, 248, 248), (88, 120, 216)]   # azul do Team Plasma
def escudo(t, cx, cy):
    t.poly([(cx - 4, cy - 4), (cx + 4, cy - 4), (cx + 4, cy + 1), (cx, cy + 5), (cx - 4, cy + 1)], PL[0])
    t.vline(cx - 1, cy - 2, cy + 2, PL[1]); t.rect(cx - 1, cy - 2, cx + 1, cy - 1, PL[1]); t.px(cx + 1, cy, PL[1])
def cristal(t, cx, base, h, w):
    t.poly([(cx - w, base), (cx - w, base - h + w), (cx, base - h), (cx + w, base - h + w), (cx + w, base)], ICE[0])
    t.poly([(cx - w, base), (cx - w, base - h + w), (cx, base - h), (cx, base)], ICE[1]); t.vline(cx - w + 1, base - h + w + 1, base - 2, ICE[2])

def A():   # meteorito de gelo preso por garras e cabos
    t = Tela(48, 32)
    t.ellipse(24, 18, 13, 11, ICE[3]); t.ellipse(23, 16, 11, 9, ICE[0]); t.ellipse(20, 13, 5, 4, ICE[1]); t.ellipse(19, 12, 2, 1, ICE[2])
    for x0, y0 in ((8, 26), (20, 29), (33, 26)): t.line(x0, y0, x0 + 6, y0 - 5, ICE[2])     # rachaduras
    for side in (-1, 1):                                                                    # garras
        x = 24 + side * 14
        t.rect(min(x, x + side * 6), 6, max(x, x + side * 6), 28, MET[0]); t.vline(x, 6, 28, MET[1])
        t.rect(x - side * 2 - 1, 10, x - side * 2 + 1, 13, MET[3]); t.rect(x - side * 2 - 1, 21, x - side * 2 + 1, 24, MET[3])
    t.line(2, 31, 9, 26, MET[2]); t.line(46, 31, 39, 26, MET[2]); t.line(0, 30, 6, 22, MET[2])  # cabos
    escudo(t, 41, 5)
    t.outline(OL); return t

def B():   # Frost Engine: console com janela do nucleo de gelo
    t = Tela(48, 32)
    t.rect(3, 6, 44, 30, MET[0]); t.hline(3, 44, 6, MET[3]); t.rect(3, 26, 44, 30, MET[2])
    t.rect(14, 9, 33, 23, MET[2]); t.rect(15, 10, 32, 22, ICE[3]); cristal(t, 23, 22, 12, 4); cristal(t, 29, 22, 8, 2)
    for y in (11, 15, 19): t.hline(5, 11, y, MET[2]); t.hline(36, 42, y, MET[2])           # grelhas
    for i, c in enumerate(((248, 80, 72), (248, 200, 72), (96, 216, 120))): t.rect(37 + i * 2, 23, 37 + i * 2, 24, c)
    t.rect(20, 1, 27, 6, MET[1]); escudo(t, 24, 3)                                          # chamine com emblema
    t.outline(OL); return t

def C():   # canhao de gelo apontado para o ceu, com o meteorito no berco
    t = Tela(48, 32)
    t.rect(6, 22, 41, 30, MET[2]); t.hline(6, 41, 22, MET[1])
    t.poly([(28, 22), (34, 2), (42, 4), (38, 22)], MET[0]); t.line(34, 2, 42, 4, MET[3]); t.line(29, 21, 35, 3, MET[1])
    t.ellipse(38, 3, 4, 2, ICE[1])
    t.ellipse(15, 15, 9, 8, ICE[3]); t.ellipse(14, 13, 7, 6, ICE[0]); t.ellipse(12, 11, 3, 2, ICE[2])
    t.line(15, 22, 34, 12, ICE[1]); t.line(15, 21, 34, 11, ICE[0])                         # tubo de energia
    escudo(t, 24, 26)
    t.outline(OL); return t

def D():   # divisor de DNA: dois casulos (preto e branco) ligados por uma helice ao nucleo de gelo
    t = Tela(48, 32)
    t.rect(2, 26, 45, 30, MET[2]); t.hline(2, 45, 26, MET[1])
    for cx, body, shine in ((8, (48, 48, 64), (96, 96, 120)), (40, (232, 232, 240), (255, 255, 255))):
        t.ellipse(cx, 15, 6, 11, body); t.vline(cx - 3, 8, 22, shine); t.rect(cx - 6, 24, cx + 6, 26, MET[0])
    t.ellipse(24, 16, 6, 7, ICE[3]); t.ellipse(24, 15, 4, 5, ICE[0]); t.px(22, 13, ICE[2])
    import math
    for x in range(13, 36):                                                                  # helice
        if 18 <= x <= 30: continue
        y1 = 15 + 3 * math.sin(x * .7); y2 = 15 - 3 * math.sin(x * .7)
        t.px(x, round(y1), PL[2]); t.px(x, round(y2), (248, 120, 72))
    escudo(t, 24, 5)
    t.outline(OL); return t
PROPOSTAS = [('A', 'Meteorito acorrentado', A), ('B', 'Frost Engine (console)', B), ('C', 'Canhao de gelo', C), ('D', 'Divisor de DNA', D)]
