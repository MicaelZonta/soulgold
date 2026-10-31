"""Canto de brinquedos do N (4x3 metatiles = 64x48): trilho de trem, bola de basquete e skate,
homenagem ao quarto do castelo do N no BW. 4 propostas, <=15 cores cada."""
import sys, math
sys.path.insert(0, '/home/ADMIN/decomps/soulgold_v1/.claude/skills/criar-aventura/ferramentas')
from desenho import Tela
OL = (40, 40, 56)
RAIL, TIE = (136, 144, 168), (120, 80, 56)
TRAIN = [(64, 112, 200), (120, 168, 240), (232, 72, 64)]
BALL, BALLD = (232, 128, 48), (160, 72, 24)
BOARD, WHEEL = (72, 184, 120), (232, 232, 232)
def trilho_oval(t, cx, cy, rx, ry):
    for a in range(0, 360, 6):
        r = math.radians(a)
        x, y = cx + rx * math.cos(r), cy + ry * math.sin(r)
        t.px(x, y, RAIL); t.px(cx + (rx - 3) * math.cos(r), cy + (ry - 3) * math.sin(r), RAIL)
        if a % 18 == 0: t.line(x, y, cx + (rx - 3) * math.cos(r), cy + (ry - 3) * math.sin(r), TIE)
def trem(t, x, y):
    t.rect(x, y, x + 7, y + 4, TRAIN[0]); t.rect(x + 1, y + 1, x + 3, y + 2, TRAIN[1]); t.rect(x + 6, y - 2, x + 7, y, TRAIN[2])
    t.rect(x + 9, y, x + 15, y + 4, TRAIN[2]); t.px(x + 2, y + 5, OL); t.px(x + 6, y + 5, OL); t.px(x + 11, y + 5, OL); t.px(x + 14, y + 5, OL)
def bola(t, cx, cy, r=4):
    t.ellipse(cx, cy, r, r, BALL); t.line(cx - r, cy, cx + r, cy, BALLD); t.line(cx, cy - r, cx, cy + r, BALLD)
def skate(t, x, y, ang=0):
    t.rect(x, y, x + 13, y + 2, BOARD); t.hline(x + 1, x + 12, y, (128, 224, 160))
    for wx in (x + 2, x + 11): t.px(wx, y + 3, WHEEL); t.px(wx, y - 1, WHEEL)
def tapete(t, c=(232, 216, 176)):
    t.rect(2, 4, 61, 45, c); t.hline(2, 61, 4, (248, 240, 216))
def A():   # oval classico com o trem, bola e skate ao lado
    t = Tela(64, 48); tapete(t); trilho_oval(t, 30, 24, 24, 15); trem(t, 18, 8); bola(t, 52, 38); skate(t, 6, 38); t.outline(OL); return t
def B():   # trilho em oito
    t = Tela(64, 48); tapete(t, (208, 224, 240)); trilho_oval(t, 18, 24, 13, 13); trilho_oval(t, 45, 24, 13, 13); trem(t, 32, 9)
    bola(t, 18, 24, 5); skate(t, 38, 22); t.outline(OL); return t
def C():   # aro de basquete no canto e trilho em volta
    t = Tela(64, 48); tapete(t, (224, 232, 200)); trilho_oval(t, 32, 26, 27, 16)
    t.rect(46, 6, 48, 20, (160, 160, 176)); t.rect(40, 4, 54, 9, (248, 248, 248)); t.ellipse(47, 11, 4, 2, (232, 72, 64))
    bola(t, 30, 26, 5); trem(t, 10, 33); skate(t, 14, 17); t.outline(OL); return t
def D():   # brinquedos espalhados num tatame, trilho reto com curva
    t = Tela(64, 48); tapete(t, (240, 208, 208))
    for x in range(6, 52, 1): t.px(x, 12, RAIL); t.px(x, 15, RAIL)
    for x in range(6, 52, 4): t.vline(x, 12, 15, TIE)
    trilho_oval(t, 52, 26, 8, 12); trem(t, 14, 9); bola(t, 14, 34, 5); bola(t, 28, 38, 3); skate(t, 34, 30); t.outline(OL); return t
PROPOSTAS = [('A', 'Oval com o trem', A), ('B', 'Trilho em oito', B), ('C', 'Aro de basquete e trilho', C), ('D', 'Brinquedos no tatame', D)]
