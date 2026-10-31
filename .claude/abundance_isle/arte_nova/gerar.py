"""Propostas de arte nova da Abundance Isle (31/10/2026), SO PROPOSTA: nada registrado no jogo.
Vela espiritual (2 estados), placa de mural e navio Plasma Frigate, 4 propostas (A-D) cada.
PNG indexado, <= 16 cores, indice 0 = transparente (formato de sprite do GBA).
    python3 .claude/abundance_isle/arte_nova/gerar.py <pasta_das_cenas>
<pasta_das_cenas> recebe tambem as folhas ampliadas e as cenas para a pagina."""
import os, sys
from PIL import Image, ImageDraw

AQUI = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(AQUI, '..', '..', '..'))
TRANSP = (255, 0, 255)


class Spr:
    def __init__(self, w, h, cores):
        assert len(cores) <= 15
        self.pal = [TRANSP] + list(cores)
        self.im = Image.new('P', (w, h), 0)
        flat = []
        for c in self.pal + [(0, 0, 0)] * (256 - len(self.pal)):
            flat += list(c)
        self.im.putpalette(flat)
        self.d = ImageDraw.Draw(self.im)

    def c(self, i):
        return i

    def px(self, x, y, i):
        if 0 <= x < self.im.width and 0 <= y < self.im.height:
            self.im.putpixel((x, y), i)

    def rect(self, x0, y0, x1, y1, i):
        self.d.rectangle([x0, y0, x1, y1], fill=i)

    def line(self, pts, i):
        self.d.line(pts, fill=i)

    def ell(self, x0, y0, x1, y1, i):
        self.d.ellipse([x0, y0, x1, y1], fill=i)

    def poly(self, pts, i):
        self.d.polygon(pts, fill=i)

    def save(self, path):
        self.im.save(path, transparency=0)


def chama(s, cx, base_y, h, cor_out, cor_mid, cor_in):
    """chama azul em gota, centrada em cx, com a base em base_y."""
    for y in range(h):
        t = y / max(1, h - 1)              # 0 topo .. 1 base
        r = int(round(0.5 + t * 2.2)) if t < 0.8 else 2
        yy = base_y - h + 1 + y
        for x in range(cx - r, cx + r + 1):
            s.px(x, yy, cor_out)
        if r >= 1:
            for x in range(cx - r + 1, cx + r):
                s.px(x, yy, cor_mid)
        if r >= 2 and t > 0.45:
            s.px(cx, yy, cor_in)


# ======================================================================== VELAS (16x16 / 16x32, 2 quadros)
def vela_A(acesa):    # vela alta de cera branca em base de pedra, 16x32
    s = Spr(16, 32, [(40, 40, 56), (96, 96, 112), (150, 150, 165), (232, 228, 214), (196, 190, 172),
                     (60, 90, 200), (110, 170, 255), (220, 240, 255), (70, 60, 50)])
    s.rect(3, 26, 12, 30, 1); s.rect(4, 26, 11, 29, 2); s.rect(4, 26, 11, 26, 3)          # base
    s.rect(5, 12, 10, 25, 1); s.rect(6, 12, 9, 25, 4); s.rect(6, 12, 7, 25, 5); s.px(9, 14, 5); s.px(9, 15, 5)
    s.rect(6, 12, 9, 12, 5)
    s.px(7, 11, 9); s.px(8, 11, 9); s.px(7, 10, 9)                                             # pavio
    if acesa:
        chama(s, 7, 10, 8, 6, 7, 8)
    return s


def vela_B(acesa):    # vela curta roxa em suporte de ferro, 16x16
    s = Spr(16, 16, [(30, 26, 40), (70, 66, 80), (120, 116, 130), (110, 70, 150), (150, 110, 190),
                     (60, 90, 200), (110, 170, 255), (220, 240, 255)])
    s.rect(3, 13, 12, 14, 1); s.rect(4, 13, 11, 13, 3); s.rect(6, 11, 9, 12, 2)               # prato de ferro
    s.rect(5, 6, 10, 11, 1); s.rect(6, 6, 9, 11, 4); s.rect(6, 6, 7, 11, 5)                   # vela roxa
    s.px(7, 5, 1); s.px(8, 5, 1)
    if acesa:
        chama(s, 7, 4, 5, 6, 7, 8)
    return s


def vela_C(acesa):    # candelabro de tres velas (fantasma), 16x32
    s = Spr(16, 32, [(30, 30, 40), (80, 70, 60), (140, 120, 80), (200, 180, 120), (230, 226, 210),
                     (180, 176, 160), (60, 90, 200), (110, 170, 255), (220, 240, 255)])
    s.rect(4, 29, 11, 30, 1); s.rect(7, 18, 8, 29, 2); s.px(7, 18, 3)                          # pe
    s.line([(2, 18), (13, 18)], 2); s.line([(2, 17), (13, 17)], 3)                              # bracos
    for cx in (2, 7, 12):
        top = 10 if cx == 7 else 12
        s.rect(cx - 1, top, cx + 1, 16, 5); s.rect(cx - 1, top, cx, 16, 4)
        s.px(cx, top - 1, 1)
        if acesa:
            chama(s, cx, top - 1, 5, 6, 7, 8)
    return s


def vela_D(acesa):    # lanterna de pedra (toro) com a chama na janela, 16x32
    s = Spr(16, 32, [(40, 40, 48), (90, 90, 100), (140, 140, 150), (180, 180, 190), (20, 20, 30),
                     (60, 90, 200), (110, 170, 255), (220, 240, 255)])
    s.poly([(1, 9), (14, 9), (12, 6), (3, 6)], 2); s.line([(1, 9), (14, 9)], 1); s.rect(6, 4, 9, 5, 3)   # telhado
    s.rect(3, 10, 12, 19, 2); s.rect(3, 10, 3, 19, 3); s.rect(12, 10, 12, 19, 1)                         # corpo
    s.rect(5, 12, 10, 17, 5)                                                                             # janela
    s.rect(6, 20, 9, 26, 2); s.rect(6, 20, 6, 26, 3)                                                     # coluna
    s.rect(3, 27, 12, 30, 1); s.rect(4, 27, 11, 28, 2)                                                   # base
    if acesa:
        s.rect(5, 12, 10, 17, 6); chama(s, 7, 17, 5, 6, 7, 8); s.px(8, 16, 8)
    return s


VELAS = {'A': vela_A, 'B': vela_B, 'C': vela_C, 'D': vela_D}


# ======================================================================== MURAIS
ARENITO = [(70, 52, 36), (130, 100, 66), (180, 150, 104), (214, 190, 140), (236, 220, 180), (40, 30, 24),
           (240, 240, 236), (34, 34, 44), (120, 200, 255)]


def mural_A():        # tabuleta de pe 16x32 com glifos e um dragao
    s = Spr(16, 32, ARENITO)
    s.rect(2, 3, 13, 29, 2); s.rect(3, 4, 12, 28, 3); s.rect(2, 3, 13, 3, 4); s.rect(13, 4, 13, 29, 1)
    s.ell(2, 0, 13, 7, 2); s.ell(3, 1, 12, 7, 3)                        # topo arredondado
    for y in (8, 11, 22, 25):
        s.line([(4, y), (11, y)], 1)
        for x in range(4, 12, 2):
            s.px(x, y - 1, 1)
    s.line([(5, 18), (7, 15), (9, 17), (11, 14)], 6)                     # dragao estilizado
    s.px(11, 13, 6); s.px(5, 19, 6)
    s.rect(1, 29, 14, 31, 0 + 1)
    return s


def mural_B():        # placa de chao 16x16 com selo circular
    s = Spr(16, 16, ARENITO)
    s.rect(1, 3, 14, 14, 1); s.rect(1, 2, 14, 12, 2); s.rect(2, 3, 13, 11, 3)
    s.ell(4, 4, 11, 10, 2); s.ell(5, 5, 10, 9, 3)
    s.line([(6, 7), (9, 7)], 6); s.px(7, 6, 6); s.px(8, 8, 6)            # sigilo
    s.px(3, 4, 4); s.px(12, 10, 1)
    return s


def mural_C():        # fragmento de obelisco 16x32 com os dois dragoes (branco e preto) em espiral
    s = Spr(16, 32, ARENITO)
    s.poly([(4, 2), (11, 1), (13, 29), (2, 29)], 2); s.poly([(5, 3), (11, 2), (12, 28), (3, 28)], 3)
    s.line([(11, 1), (13, 29)], 1)
    s.ell(4, 11, 11, 18, 7); s.ell(4, 11, 7, 18, 6)                      # yin-yang preto/branco
    s.ell(5, 11, 8, 14, 7); s.ell(7, 15, 10, 18, 6)
    s.px(6, 12, 6); s.px(8, 16, 7)
    s.line([(4, 22), (11, 22)], 1); s.line([(4, 25), (11, 25)], 1)
    s.rect(1, 29, 14, 31, 1)
    return s


def mural_D():        # placa larga 32x32 encostada, moldura, relevo de dois dragoes
    s = Spr(32, 32, ARENITO)
    s.rect(1, 4, 30, 28, 1); s.rect(2, 4, 29, 26, 2); s.rect(4, 6, 27, 24, 3)
    s.rect(2, 4, 29, 4, 4)
    s.line([(6, 18), (9, 12), (12, 16), (15, 10)], 6); s.px(15, 9, 6); s.px(16, 10, 6)      # dragao branco
    s.line([(25, 18), (22, 12), (19, 16), (16, 22)], 7); s.px(25, 19, 7); s.px(26, 18, 7)   # dragao preto
    s.ell(14, 8, 17, 11, 8)                                              # pedra no meio
    s.rect(1, 28, 30, 31, 0 + 1)
    return s


MURAIS = {'A': mural_A, 'B': mural_B, 'C': mural_C, 'D': mural_D}

# ======================================================================== NAVIO (96x40, como o SS Tidal)
PLASMA = [(24, 26, 38), (52, 58, 78), (86, 94, 120), (130, 140, 168), (190, 196, 214), (240, 242, 248),
          (40, 90, 180), (90, 150, 230), (180, 40, 50), (230, 200, 60), (14, 14, 20), (70, 110, 150)]


def escudo(s, x, y, azul=6, claro=5, borda=0):
    """emblema do Team Plasma simplificado: escudo 7x9 dividido, com P."""
    s.poly([(x, y), (x + 6, y), (x + 6, y + 5), (x + 3, y + 8), (x, y + 5)], borda)
    s.poly([(x + 1, y + 1), (x + 5, y + 1), (x + 5, y + 5), (x + 3, y + 7), (x + 1, y + 5)], azul)
    s.poly([(x + 1, y + 1), (x + 3, y + 1), (x + 3, y + 7), (x + 1, y + 5)], azul + 1)
    s.line([(x + 2, y + 2), (x + 2, y + 6)], claro); s.line([(x + 2, y + 2), (x + 4, y + 2)], claro)
    s.line([(x + 4, y + 2), (x + 4, y + 4)], claro); s.line([(x + 2, y + 4), (x + 4, y + 4)], claro)


def tidal_recolor(mapa):
    """SS Tidal com as cores trocadas (mesmo desenho e tamanho)."""
    src = Image.open(os.path.join(ROOT, 'graphics/object_events/pics/misc/ss_tidal.png'))
    pal = src.getpalette()[:48]
    cores = [tuple(pal[i * 3:i * 3 + 3]) for i in range(16)]
    novas = [mapa.get(i, cores[i]) for i in range(1, 16)]
    s = Spr(96, 40, novas[:15])
    s.im.paste(src)
    return s


def navio_A():        # SS Tidal pintado de Plasma: casco escuro, faixa azul, escudo no casco
    s = tidal_recolor({1: (196, 204, 220), 2: (150, 160, 184), 3: (110, 120, 146), 4: (80, 88, 110), 5: (58, 64, 84),
                       6: (36, 40, 56), 7: (24, 26, 38), 8: (40, 90, 180), 9: (90, 150, 230), 10: (14, 14, 20),
                       11: (60, 110, 200), 12: (230, 230, 240), 15: (40, 46, 64)})
    escudo(s, 8, 18, azul=8, claro=12, borda=10)
    return s


def navio_B():        # SS Tidal em preto e dourado (chamines viram torres de radar)
    s = tidal_recolor({1: (120, 120, 132), 2: (90, 90, 102), 3: (66, 66, 78), 4: (48, 48, 58), 5: (34, 34, 42),
                       6: (24, 24, 30), 7: (14, 14, 18), 8: (200, 170, 60), 9: (240, 210, 90), 10: (8, 8, 10),
                       11: (230, 200, 60), 12: (240, 240, 230), 15: (30, 30, 38)})
    escudo(s, 40, 22, azul=11, claro=12, borda=10)
    return s


class SprP(Spr):
    """Spr cujos indices 0.. contam a partir de PLASMA[0] (o 0 do GBA, transparente, fica fora)."""
    def px(self, x, y, i): Spr.px(self, x, y, i + 1)
    def rect(self, x0, y0, x1, y1, i): Spr.rect(self, x0, y0, x1, y1, i + 1)
    def line(self, pts, i): Spr.line(self, pts, i + 1)
    def ell(self, x0, y0, x1, y1, i): Spr.ell(self, x0, y0, x1, y1, i + 1)
    def poly(self, pts, i): Spr.poly(self, pts, i + 1)


def navio_C():        # fragata a vela: casco escuro, 2 velas pretas com o escudo
    s = SprP(96, 40, PLASMA)
    s.poly([(4, 26), (92, 26), (84, 37), (12, 37)], 1); s.poly([(6, 27), (90, 27), (83, 35), (13, 35)], 2)
    s.line([(4, 26), (92, 26)], 4); s.line([(12, 37), (84, 37)], 11)
    s.rect(10, 30, 86, 31, 7)                                            # faixa azul
    for x in range(18, 80, 8):
        s.rect(x, 32, x + 2, 33, 11)                                     # escotilhas
    for mx in (30, 60):
        s.rect(mx, 2, mx + 1, 26, 3)                                     # mastros
        s.poly([(mx - 13, 5), (mx + 14, 5), (mx + 12, 22), (mx - 11, 22)], 0)
        s.poly([(mx - 12, 6), (mx + 13, 6), (mx + 11, 21), (mx - 10, 21)], 10)
        escudo(s, mx - 3, 9, azul=6, claro=5, borda=0)
    s.poly([(80, 26), (94, 18), (92, 26)], 1)                            # proa
    s.rect(8, 21, 20, 25, 2); s.rect(9, 22, 19, 24, 3)                   # castelo de popa
    return s


def navio_D():        # navio de guerra angular (furtivo) com luzes azuis
    s = SprP(96, 40, PLASMA)
    s.poly([(2, 24), (94, 22), (86, 37), (8, 37)], 0); s.poly([(4, 25), (91, 23), (85, 35), (9, 35)], 1)
    s.line([(4, 25), (91, 23)], 3)
    s.poly([(24, 24), (30, 10), (66, 10), (74, 23)], 0); s.poly([(26, 23), (31, 11), (65, 11), (72, 22)], 2)
    s.poly([(38, 11), (42, 3), (54, 3), (58, 11)], 0); s.poly([(40, 10), (43, 4), (53, 4), (56, 10)], 3)
    for x in range(34, 64, 5):
        s.rect(x, 15, x + 2, 16, 7)                                       # janelas azuis
    s.rect(44, 6, 51, 7, 7)
    s.rect(12, 30, 84, 31, 6)
    escudo(s, 14, 26, azul=6, claro=5, borda=10)
    s.line([(48, 0), (48, 3)], 4); s.px(47, 0, 8)                         # antena com luz vermelha
    return s


NAVIOS = {'A': navio_A, 'B': navio_B, 'C': navio_C, 'D': navio_D}


def rgba(s):
    im = s.im.convert('RGBA')
    px = im.load(); src = s.im.load()
    for y in range(im.height):
        for x in range(im.width):
            if src[x, y] == 0:
                px[x, y] = (0, 0, 0, 0)
    return im


def main(out):
    os.makedirs(out, exist_ok=True)
    res = {}
    for nome, tab in (('vela', VELAS), ('mural', MURAIS), ('navio', NAVIOS)):
        pasta = os.path.join(AQUI, nome); os.makedirs(pasta, exist_ok=True)
        for k, fn in tab.items():
            if nome == 'vela':      # folha com os 2 quadros: apagada | acesa
                a, b = fn(False), fn(True)
                w, h = a.im.size
                s = Spr(w * 2, h, a.pal[1:])
                s.im.paste(a.im, (0, 0)); s.im.paste(b.im, (w, 0))
                quadros = [a, b]
            else:
                s = fn(); quadros = [s]
            s.save(os.path.join(pasta, f'proposta_{k}.png'))
            n = len({p for p in s.im.getdata()})
            res[(nome, k)] = (quadros, s.im.size, n)
    return res


if __name__ == '__main__':
    r = main(sys.argv[1] if len(sys.argv) > 1 else '/tmp')
    for (nome, k), (_, size, n) in r.items():
        print(nome, k, size, 'cores usadas (com transp.):', n)
