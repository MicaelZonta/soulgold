import sys; sys.path.insert(0, '.')
from desenho import Tela
OL = (48, 40, 56)
STONE = [(120, 120, 128), (160, 160, 168), (200, 200, 200), (88, 88, 104)]   # base, claro, brilho, sombra
WOOD = [(152, 88, 48), (192, 128, 72), (104, 56, 32)]
RED = [(200, 56, 40), (240, 104, 72), (136, 32, 32)]
def plinto(t, x0, x1, y0, y1):
    t.rect(x0, y0, x1, y1, STONE[0]); t.hline(x0, x1, y0, STONE[1]); t.hline(x0, x1, y1, STONE[3])
    for x in range(x0 + 3, x1, 7): t.vline(x, y0 + 1, y1 - 1, STONE[3])

def A():   # hokora de madeira: telhado vermelho, porta escura, shide branco, oferenda
    t = Tela(48, 48)
    plinto(t, 4, 43, 40, 46); plinto(t, 9, 38, 35, 39)
    t.rect(14, 18, 33, 34, WOOD[0]); t.vline(14, 18, 34, WOOD[2]); t.vline(33, 18, 34, WOOD[2])
    for y in range(20, 34, 3): t.hline(15, 32, y, WOOD[1])
    t.rect(20, 22, 27, 34, (40, 32, 40)); t.rect(21, 23, 26, 34, (72, 48, 56))                # porta
    t.vline(23, 23, 34, (40, 32, 40)); t.vline(24, 23, 34, (40, 32, 40))
    t.poly([(6, 18), (24, 4), (42, 18), (38, 20), (24, 9), (10, 20)], RED[0])                 # telhado
    t.poly([(10, 18), (24, 8), (38, 18)], RED[0]); t.line(6, 18, 24, 4, RED[1]); t.line(24, 4, 42, 18, RED[2])
    t.hline(8, 40, 19, RED[2]); t.hline(9, 39, 18, RED[0])
    t.rect(22, 2, 25, 4, WOOD[2])                                                              # cumeeira
    for x in (17, 30):                                                                         # shide (papel em zigue-zague)
        t.px(x, 20, (248, 248, 240)); t.px(x + 1, 21, (248, 248, 240)); t.px(x, 22, (248, 248, 240)); t.px(x + 1, 23, (248, 248, 240))
    t.hline(15, 32, 20, (232, 216, 160))                                                       # corda shimenawa
    t.ellipse(12, 37, 2.5, 2, (232, 200, 72)); t.ellipse(36, 37, 2.5, 2, (120, 184, 72))      # oferendas: fruta e folha
    t.outline(OL); return t

def B():   # tres pedras das Forcas + flor de Enamorus
    t = Tela(48, 48)
    plinto(t, 2, 45, 40, 46)
    def pedra(cx, top, w, base_col, light, mark):
        t.poly([(cx - w, 40), (cx - w + 1, top + 4), (cx - 1, top), (cx + 1, top), (cx + w - 1, top + 4), (cx + w, 40)], base_col)
        t.vline(cx - w + 2, top + 5, 38, light); mark(cx, top)
    def nuvem(cx, top):
        for dx, dy, r in ((-2, 14, 3), (2, 13, 3), (0, 11, 3)): t.ellipse(cx + dx, top + dy, r, 2, (120, 200, 120))
        t.line(cx - 4, top + 18, cx + 4, top + 18, (64, 136, 72))
    def raio(cx, top):
        pts = [(cx + 2, top + 8), (cx - 2, top + 15), (cx + 1, top + 15), (cx - 2, top + 22)]
        for a, b in zip(pts, pts[1:]): t.line(*a, *b, (248, 224, 96))
    def terra(cx, top):
        t.ellipse(cx, top + 14, 4, 4, (232, 136, 64)); t.ellipse(cx, top + 14, 2, 2, (248, 200, 120))
    pedra(10, 16, 7, (112, 128, 112), (152, 168, 152), nuvem)
    pedra(24, 6, 8, (136, 112, 96), (176, 152, 128), terra)
    pedra(38, 16, 7, (104, 104, 136), (144, 144, 176), raio)
    for cx in (17, 31):                                                                        # flores rosa (Enamorus)
        t.ellipse(cx, 37, 2, 2, (240, 136, 184)); t.px(cx, 37, (248, 232, 120))
    t.outline(OL); return t

def C():   # torii vermelho + altar de pedra com tigela
    t = Tela(48, 48)
    t.rect(8, 10, 11, 44, RED[0]); t.rect(36, 10, 39, 44, RED[0]); t.vline(8, 10, 44, RED[1]); t.vline(36, 10, 44, RED[1])
    t.rect(7, 42, 12, 45, (40, 40, 48)); t.rect(35, 42, 40, 45, (40, 40, 48))
    t.poly([(2, 6), (46, 6), (44, 10), (4, 10)], (40, 40, 48)); t.rect(4, 10, 43, 12, RED[0])  # kasagi + shimaki
    t.rect(6, 15, 41, 17, RED[0]); t.hline(6, 41, 17, RED[2])                                    # nuki
    t.rect(22, 11, 25, 15, RED[2]); t.rect(22, 12, 25, 14, (232, 200, 72))                       # placa
    plinto(t, 15, 32, 34, 40); t.rect(17, 31, 30, 33, STONE[1]); t.hline(17, 30, 31, STONE[2])
    t.ellipse(24, 30, 4, 2, (88, 64, 48)); t.ellipse(24, 29, 3, 1, (232, 200, 72))              # tigela com graos
    for x in (19, 29): t.rect(x - 1, 26, x, 30, (248, 248, 240)); t.px(x, 25, (248, 160, 72))    # velas
    t.outline(OL); return t

def D():   # altar da colheita: estela com o simbolo de Landorus e oferendas
    t = Tela(48, 48)
    plinto(t, 3, 44, 38, 46)
    t.rect(14, 6, 33, 34, STONE[0]); t.poly([(14, 6), (24, 1), (33, 6)], STONE[0]); t.vline(15, 6, 33, STONE[1]); t.vline(32, 6, 33, STONE[3])
    t.rect(17, 9, 30, 30, STONE[3]); t.rect(18, 10, 29, 29, (176, 152, 120))                    # painel
    t.ellipse(23.5, 19, 5, 6, (200, 120, 56)); t.ellipse(23.5, 19, 3, 4, (232, 168, 88))        # emblema: rosto de Landorus
    t.line(19, 13, 16, 9, (200, 120, 56)); t.line(28, 13, 31, 9, (200, 120, 56))                # chifres
    t.rect(22, 18, 25, 19, (104, 56, 32))
    t.rect(6, 34, 41, 37, WOOD[0]); t.hline(6, 41, 34, WOOD[1])                                 # mesa de oferendas
    for cx, c in ((9, (232, 72, 56)), (13, (248, 200, 64)), (35, (152, 88, 200)), (39, (120, 200, 88))):
        t.ellipse(cx, 32, 2, 2, c); t.px(cx - 1, 31, (248, 248, 240))
    for x in (18, 29):                                                                          # feixes de trigo
        t.rect(x, 26, x + 1, 33, (216, 176, 72)); t.ellipse(x + .5, 25, 2, 3, (240, 208, 96))
    t.outline(OL); return t
PROPOSTAS = [('A', 'Hokora de madeira', A), ('B', 'Pedras das Tres Forcas', B), ('C', 'Torii e altar', C), ('D', 'Estela da Colheita', D)]
