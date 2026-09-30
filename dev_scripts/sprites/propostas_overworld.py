#!/usr/bin/env python3
"""Propostas de overworld em varios tamanhos, com folha de comparacao.

Regra do autor (27/09/2026): sprite de overworld novo nao vai direto para o
jogo. Primeiro geram-se VARIAS opcoes de tamanho (boneco com 16, 17, 18...
px de largura, ate o maximo que a arte permite sem ampliar e sem passar de
31 px de altura) mais uma folha de comparacao ampliada ao lado do jogador e
do sprite atual; o autor escolhe o tamanho; so entao `final` grava o PNG.

    propostas_overworld.py propostas [Nome ...]
        -> .filetransfer/.trainers/<Nome>/Sprite - comparacao no jogo.png
           (uma linha por largura; a esquerda o sprite de hoje e o jogador)
    propostas_overworld.py final <Nome> <largura> <saida.png> [--quadro 16] [--altura H]
        -> folha do jogo 32x32 (ou 16x32 com --quadro 16; 9 quadros, ou 12 se
           a arte tem o lado direito); sem --altura, altura proporcional

Reducao (auditoria de 29/09/2026, .filetransfer/.trainers/_auditoria resize 16px/):
  - colunas: costura RETA de menor energia (gradiente + contorno + mascara de
    rosto) com penalidade forte nas vizinhas da ultima removida, a mesma em
    todos os quadros da mesma direcao; preserva olhos e boca quando o cabelo
    disputa espaco com o rosto, sem serrar (costura diagonal serra cabelo e
    silhueta) e sem perder a proporcao chapeu/corpo (Hilda). Quanto mais a
    arte encolhe, maior a parte apagada em faixas uniformes antes da costura
    (parte_por_conteudo): so conteudo a 50% deixa os olhos enormes (Zinnia);
  - linhas: apaga em faixas uniformes a linha mais barata, com custo que
    protege traco escuro de 1 px (seam carving nas linhas achata capacete e
    topo de cabeca, por isso nao e usado aqui);
  - fonte JPG passa por median cut (24 cores) ANTES de reduzir (senao o contorno
    dobra); a fusao final a 15 fica para depois (antes, apaga os olhos da Agatha);
  - altura desacoplada da largura: alem da proporcional, propoe a altura do
    elenco (18-22 px) quando a proporcional cai fora; `final ... --altura H`.
Arte que tambem existe em 2x (k=2) da tamanhos acima do nativo sem ampliar.
Cada personagem e uma entrada em CHARS (arquivo, grade e celulas na ordem do
jogo). Precisa de Pillow (no WSL: Python do Windows).
"""
import os
import sys
from PIL import Image, ImageDraw

AQUI = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, AQUI)
import sprite_gba as G  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(AQUI))
FT = os.path.join(ROOT, '.filetransfer', '.trainers')

# Ordem do jogo: parado baixo, parado cima, parado esq, 2x baixo, 2x cima, 2x esq
# e, se a arte tiver, parado dir + 2x dir (sAnimTable_StandardAsym, 12 quadros).
# Celulas sao (linha, coluna) da grade da folha de origem.
RPG = [(0, 0), (3, 0), (1, 0), (0, 1), (0, 3), (3, 1), (3, 3), (1, 1), (1, 3), (2, 0), (2, 1), (2, 3)]
L3 = [(1, 0), (0, 0), (2, 0), (1, 1), (1, 2), (0, 1), (0, 2), (2, 1), (2, 2), (3, 0), (3, 1), (3, 2)]
PLAT = [(0, 0), (1, 0), (2, 0), (5, 0), (6, 0), (3, 0), (4, 0), (7, 0), (8, 0)]  # tira vertical Platinum/HGSS
# linhas = direcao (baixo, cima, esq, dir), colunas = parado, passo, parado, passo
BCED = [(0, 0), (1, 0), (2, 0), (0, 1), (0, 3), (1, 1), (1, 3), (2, 1), (2, 3), (3, 0), (3, 1), (3, 3)]
FILA = [(0, i) for i in range(12)]  # ja na ordem do jogo, numa linha so
# 7 quadros (FRLG): passo de baixo e de cima espelhado ('m') para fazer o segundo passo
FRLG7 = [(0, 0), (0, 1), (0, 2), (0, 3), (0, 3, 'm'), (0, 4), (0, 4, 'm'), (0, 5), (0, 6)]
OW = 'graphics/object_events/pics/people/'
SP = OW + 'special/'
# Cada personagem: f = 'Pasta/Sprite - AUTOR.*' em .filetransfer/.trainers; grade em pixels nativos
# (depois de desfazer k); frames = celulas (linha, coluna) na ordem do jogo.
CHARS = {
    'Agatha': dict(f='Agatha/Sprite - RegentOfRaios.jpg', k=2, jpg=True, cell=(34, 36), x0=0, y0=0, px=34, py=36, frames=RPG,
                   cred='RegentOfRaios'),
    # teste (30/09): folha 6x4 ampliada por IA; linhas cima/baixo/esq/dir, colunas 0-2 parado, 3 e 4 passos
    'Agatha IA': dict(f='Agatha/image.png', pasta='Agatha', k=1, reamostrar=(256, 40), cell=(40, 40), x0=0, y0=0,
                      px=40, py=40, grade=True, frames=[(1, 0), (0, 0), (2, 0), (1, 3), (1, 4), (0, 3), (0, 4),
                      (2, 3), (2, 4), (3, 0), (3, 3), (3, 4)], pre_cores=96, cred='desconhecido'),
    'Alder': dict(f='Alder/Sprite - aveontrainer.png', k=1, cell=(32, 48), x0=0, y0=0, px=32, py=48, grade=True, frames=RPG, cred='aveontrainer'),
    'Anabel': dict(f='Anabel/Sprite - Vergolophus.png', k=1, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                   cred='Vergolophus', atual=OW + 'frontier_brains/anabel.png'),
    'Ash': dict(f='Ash/Sprite - RichardPT e PKMNTrainerSpriterC.png', k=2, cell=(15, 22), x0=0, y0=1, px=15.2, py=22.9, grade=True,
                frames=RPG, cred='RichardPT e PKMNTrainerSpriterC'),
    'Barry': dict(f='Barry/Sprite - redblueyellow (rip).png', k=1, cell=(34, 34), x0=0, y0=0, px=34, py=34, frames=BCED,
                  cred='redblueyellow (rip)'),
    'Blue': dict(f='Blue/Sprite - chrisx698.png', k=1, jpg=True, cell=(24, 35), x0=0, ys=[0, 35, 70, 104], px=24.5,
                 frames=[(0, 0), (1, 0), (3, 0), (0, 1), (0, 2), (1, 1), (1, 2), (3, 1), (3, 2), (2, 0), (2, 1), (2, 2)],
                 cred='chrisx698', atual=OW + 'gym_leaders/blue.png'),
    'Brendan': dict(f='Brendan/Sprite - hyo-oppa.png', k=1, cell=(25, 33), x0=7, ys=[0, 33, 64, 97], px=25,
                    frames=[(0, 1), (1, 1), (2, 1), (0, 0), (0, 2), (1, 0), (1, 2), (2, 0), (2, 2), (3, 1), (3, 0), (3, 2)],
                    cred='hyo-oppa', atual=SP + 'brendan_hoenn.png'),
    'Bruno': dict(f='Bruno/Sprite - desconhecido.png', k=1, cell=(30, 31), x0=0, y0=1, px=30, py=32,
                  frames=[(1, 2), (0, 0), (1, 0), (2, 2), (3, 2), (0, 2), (3, 1), (2, 0), (3, 0), (0, 1), (1, 1), (2, 1)],
                  cred='desconhecido', atual=OW + 'elite_four/bruno.png'),
    'Byron': dict(f='Byron/Sprite - oficial Platinum.png', k=1, cell=(27, 32), x0=0, y0=0, px=27, py=32, frames=PLAT,
                  cred='oficial (Platinum)', atual=SP + 'byron.png'),
    'Cheren': dict(f='Cheren/Sprite - PurpleZaffre.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG, cred='PurpleZaffre'),
    'Colress': dict(f='Colress/Sprite - Pizza Sun.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                    cred='Pizza Sun', atual=SP + 'colress.png'),
    'Cynthia': dict(f='Cynthia/Sprite - oficial Platinum.png', k=1, cell=(27, 32), x0=0, y0=0, px=27, py=32, frames=PLAT,
                    cred='oficial (Platinum)', atual=SP + 'cynthia.png'),
    'Cyrus': dict(f='Cyrus/Sprite - RHcks.png', k=1, jpg=True, cell=(16, 34), x0=2, y0=1, px=16.2, py=34, frames=FILA[:9],
                  cred='RHcks'),
    'Diantha': dict(f='Diantha/Sprite - Lolw3e932.png', k=1, cell=(32, 48), x0=0, y0=0, px=32, py=48, grade=True, frames=RPG, cred='Lolw3e932'),
    'Elesa': dict(f='Elesa/Sprite - RHcks.png', k=1, crop=(1, 159, 145, 183), cell=(16, 24), x0=0, y0=0, px=16,
                  py=24, grade=True, frames=[(0, i) for i in range(9)], cred='RHcks', atual=SP + 'elesa.png'),
    'Fantina': dict(f='Fantina/Sprite - oficial Platinum.png', k=1, cell=(27, 32), x0=0, y0=0, px=27, py=32, frames=PLAT,
                    cred='oficial (Platinum)', atual=SP + 'fantina.png'),
    'Gardenia': dict(f='Gardenia/Sprite - oficial Platinum.png', k=1, cell=(27, 32), x0=0, y0=0, px=27, py=32, frames=PLAT,
                     cred='oficial (Platinum)'),
    'Gladion': dict(f='Gladion/Sprite - Derlo.png', k=1, crop=(0, 0, 100, 200), cell=(33, 50), x0=0,
                    ys=[14, 80, 144], px=33, frames=[(0, 0), (1, 0), (2, 0), (0, 1), (0, 2), (1, 1), (1, 2), (2, 1), (2, 2)],
                    cred='Derlo', atual=SP + 'gladion.png'),
    'Guzma': dict(f='Guzma/Sprite - PurpleZafree.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                  cred='PurpleZafree', atual=SP + 'guzma.png'),
    'Hau': dict(f='Hau/Sprite - Wergan.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG, cred='Wergan'),
    'Hilda': dict(f='Hilda/Sprite - Redboy265.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG, cred='Redboy265'),
    'Jessie': dict(pasta='Jessie e James', f='Jessie e James/Sprite - FallenSoldier.png', k=1, cell=(17, 24), x0=1, y0=2,
                   px=17.3, py=24, frames=FRLG7, cred='FallenSoldier'),
    'James': dict(pasta='Jessie e James', f='Jessie e James/Sprite - FallenSoldier.png', k=1, cell=(15, 24), x0=7, y0=36,
                  px=15.3, py=24, frames=FRLG7, cred='FallenSoldier'),
    'Kukui': dict(f='Kukui/Sprite - Wolfgang62.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                  cred='Wolfgang62', atual=SP + 'kukui.png'),
    'Leon': dict(f='Leon/Sprite - Wolfang62.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG, cred='Wolfang62'),
    'Lillie': dict(f='Lillie/Sprite - UlithiumDragon.png', k=1, cell=(16, 32), x0=0, y0=0, px=16, py=32, grade=True,
                   frames=FILA[:9], cred='UlithiumDragon', atual=SP + 'lillie.png'),
    'Looker': dict(f='Looker/Sprite - Vergolophus.png', k=1, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                   cred='Vergolophus', atual=SP + 'looker.png'),
    'Lorelei': dict(f='Lorelei/Sprite - Purple Zaffre.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                    cred='Purple Zaffre'),
    'Lusamine': dict(f='Lusamine/Sprite - DiegoWT.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                     cred='DiegoWT', atual=SP + 'lusamine.png'),
    'Misty': dict(f='Misty/Sprite - Lime029.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                  cred='Lime029', atual=OW + 'gym_leaders/misty.png'),
    'N': dict(f='N/Sprite - Boyaloxer e outros.png', k=2, jpg=True, cell=(16, 20), x0=0, y0=76, px=16, py=20, grade=True, frames=FILA[:9],
              cred='Boyaloxer e outros'),
    # folha 6x4 de 256 px ampliada por IA (sem grade fixa: 5 a 8 px por pixel); linhas cima, baixo,
    # esq, dir; colunas 0-2 andar (1 = parado), 3-5 correr. A antiga (zender1752, JPG) foi para outras/.
    # pre_cores=96: com 40 o median cut junta o rosa do top e o branco num tom so e o top sai branco
    'Olivia': dict(f='Olivia/Sprite - desconhecido.png', k=1, reamostrar=(256, 40), cell=(40, 40), x0=0, y0=0,
                   px=40, py=40, grade=True, frames=[(1, 1), (0, 1), (2, 1), (1, 0), (1, 2), (0, 0), (0, 2),
                   (2, 0), (2, 2), (3, 1), (3, 0), (3, 2)], pre_cores=96, cred='desconhecido'),
    'Ramos': dict(f='Ramos/Sprite - desconhecido.jpg', k=2, jpg=True, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                  cred='desconhecido', atual=SP + 'ramos.png'),
    'Shelly': dict(f='Shelly/Sprite - Swizzler121.png', k=1, cell=(28, 28), x0=0, y0=0, px=30, py=30,
                   frames=[(0, 0), (0, 2), (0, 1), (1, 0), (2, 0), (1, 2), (2, 2), (1, 1), (2, 1), (0, 3), (1, 3), (2, 3)],
                   cred='Swizzler121'),
    'Soliera': dict(f='Soliera/Sprite - Mid117.png', k=1, cell=(22, 33), x0=4, y0=4, px=22.7, py=33.3,
                    frames=[(0, 1), (3, 1), (1, 1), (0, 0), (0, 2), (3, 0), (3, 2), (1, 0), (1, 2), (2, 1), (2, 0), (2, 2)],
                    cred='Mid117', atual=SP + 'soliera.png'),
    'Steven': dict(f='Steven/Sprite - Klein.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                   cred='Klein', atual=OW + 'steven.png', bgs=[(148, 147, 146)]),  # sombra cinza sob os pes: o jogo ja desenha sombra
    'Volkner': dict(f='Volkner/Sprite - desconhecido.png', k=1, cell=(23, 32), x0=0, y0=0, px=23, py=32, frames=PLAT,
                    cred='desconhecido', atual=SP + 'volkner.png'),
    'Zinnia': dict(f='Zinnia/Sprite - Aveontrainer.png', k=1, cell=(32, 48), x0=0, y0=0, px=32, py=48, grade=True, frames=RPG, cred='Aveontrainer'),
}
GRUPOS = [0, 1, 2, 0, 0, 1, 1, 2, 2, 3, 3, 3]


def dist(a, b):
    return sum(abs(a[i] - b[i]) for i in range(3))


def mediana2(im):
    """reduz 2x pela mediana do bloco (limpa ruido de JPG)."""
    w, h = im.width // 2, im.height // 2
    out = Image.new('RGBA', (w, h))
    s = im.load()
    for y in range(h):
        for x in range(w):
            ps = [s[2 * x + i, 2 * y + j] for i in (0, 1) for j in (0, 1)]
            ps.sort(key=lambda p: sum(p[:3]))
            a, b = ps[1], ps[2]
            out.putpixel((x, y), tuple((a[i] + b[i]) // 2 for i in range(4)))
    return out


def lisa(px, size, col):
    """fracao dos pixels da cor com a vizinhanca 3x3 inteira da mesma cor."""
    W, H = size
    tot = sol = 0
    for y in range(1, H - 1):
        for x in range(1, W - 1):
            if px[x, y][:3] == col:
                tot += 1
                sol += all(px[x + a, y + b][:3] == col for a in (-1, 0, 1) for b in (-1, 0, 1))
    return sol / max(tot, 1)


def sem_fundo(im, jpg, extra=()):
    """remove a cor do canto e a cor de dentro da primeira celula (fundo de celula)."""
    im = im.copy(); px = im.load()
    bgs = [px[0, 0]]
    tol = 70 if jpg else 0
    # procura cor de fundo de celula: cor mais comum que nao e a de fora
    cnt = {}
    for y in range(im.height):
        for x in range(im.width):
            p = px[x, y]
            if p[3] >= 128:
                cnt[p[:3]] = cnt.get(p[:3], 0) + 1
    canto = None
    if bgs[0][3] >= 128 and cnt.get(bgs[0][:3], 0) < im.width * im.height * 0.05:
        canto = bgs[0]   # canto e uma linha de borda, nao o fundo (Cyrus: navy escuro igual a sombra da perna)
        bgs = []         # a borda so serve de porta de entrada para o preenchimento
    if not bgs or bgs[0][3] >= 128:
        for col, n in sorted(cnt.items(), key=lambda t: -t[1])[:2]:
            # fundo de celula e area lisa; cor do corpo muito usada (cabelo do Byron, 17%) nao
            if n > im.width * im.height * 0.15 and lisa(px, im.size, col) > 0.5:
                bgs.append(col + (255,))
    bgs += [e + (255,) for e in extra]
    isbg = lambda p: p[3] < 128 or any(b[3] >= 128 and dist(p, b) <= tol for b in bgs)
    passa = lambda p: isbg(p) or (canto is not None and dist(p, canto) <= tol)
    if not jpg:
        for y in range(im.height):
            for x in range(im.width):
                if isbg(px[x, y]):
                    px[x, y] = (0, 0, 0, 0)
        return im
    # JPG: preenche a partir da borda da imagem e das linhas da grade, para nao furar o corpo
    W, H = im.size
    marca = [[passa(px[x, y]) for x in range(W)] for y in range(H)]
    linha = extra[-1] + (255,) if extra else None
    st = [(x, y) for y in range(H) for x in range(W)
          if marca[y][x] and (x in (0, W - 1) or y in (0, H - 1) or (linha and dist(px[x, y], linha) <= 40))]
    vis = set(st)
    while st:
        x, y = st.pop()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            q = (x + dx, y + dy)
            if 0 <= q[0] < W and 0 <= q[1] < H and q not in vis and marca[q[1]][q[0]]:
                vis.add(q); st.append(q)
    # a cor do canto (borda/grade) so e apagada nas linhas e colunas em que ela domina;
    # dentro do boneco a mesma cor pode ser sombra (Cyrus)
    ecanto = lambda p: canto is not None and p[3] >= 128 and dist(p, canto) <= tol
    lin = {y for y in range(H) if sum(1 for x in range(W) if ecanto(px[x, y])) >= 0.6 * W}
    col = {x for x in range(W) if sum(1 for y in range(H) if ecanto(px[x, y])) >= 0.6 * H}
    for (x, y) in vis:
        if isbg(px[x, y]) or (ecanto(px[x, y]) and (y in lin or x in col)):
            px[x, y] = (0, 0, 0, 0)
    return im


def componentes(im):
    w, h = im.size; px = im.load()
    lab = {}
    comps = []
    for y in range(h):
        for x in range(w):
            if px[x, y][3] and (x, y) not in lab:
                st = [(x, y)]; lab[(x, y)] = len(comps); pts = []
                while st:
                    a, b = st.pop(); pts.append((a, b))
                    for da in (-1, 0, 1):
                        for db in (-1, 0, 1):
                            q = (a + da, b + db)
                            if 0 <= q[0] < w and 0 <= q[1] < h and q not in lab and px[q][3]:
                                lab[q] = len(comps); st.append(q)
                comps.append(pts)
    return comps


def desfazer_ampliacao_ia(im, C, N):
    """celulas de C px ampliadas sem grade fixa (upscale por IA: o pixel da arte varia
    de 5 a 8 px) -> celulas de N px. Cada pixel novo e o medoide dos pixels opacos do
    miolo do bloco (metade central, longe das bordas borradas); bloco mais transparente
    que opaco vira fundo. Tira sujeira solta (componente < 8 px) da sombra borrada."""
    import numpy as np
    A = np.asarray(im.convert('RGBA')).astype(float)
    p = C / N
    ny, nx = im.height // C, im.width // C
    out = np.zeros((ny * N, nx * N, 4), np.uint8)
    for r in range(ny):
        for c in range(nx):
            cel = A[r * C:(r + 1) * C, c * C:(c + 1) * C]
            for j in range(N):
                for i in range(N):
                    y0, y1 = round((j + .25) * p), round((j + .75) * p)
                    x0, x1 = round((i + .25) * p), round((i + .75) * p)
                    b = cel[y0:y1 + 1, x0:x1 + 1].reshape(-1, 4)
                    op = b[b[:, 3] >= 170]
                    if 2 * len(op) < len(b):
                        continue
                    med = np.median(op[:, :3], 0)
                    k = op[np.argmin(np.abs(op[:, :3] - med).sum(1)), :3]
                    out[r * N + j, c * N + i] = (*k.astype(np.uint8), 255)
    im = Image.fromarray(out, 'RGBA')
    px = im.load()
    for pts in componentes(im):
        if len(pts) < 8:
            for q in pts:
                px[q] = (0, 0, 0, 0)
    return im


def frames_nativos(c, big=False):
    im = Image.open(os.path.join(FT, c['f'])).convert('RGBA')
    if 'crop' in c:
        im = im.crop(c['crop'])
    if 'reamostrar' in c:
        im = desfazer_ampliacao_ia(im, *c['reamostrar'])
    e = 2 if big else 1
    if c['k'] == 2 and not big:
        im = mediana2(im) if c.get('jpg') else im.resize((im.width // 2, im.height // 2), Image.NEAREST)
    im = sem_fundo(im, c.get('jpg'), c.get('bgs', ()))
    cw, ch = c['cell'][0] * e, c['cell'][1] * e
    comps = componentes(im)
    M = 10 * e
    out = []
    for fr in c['frames']:
        r, col = fr[:2]
        x = round((c['xs'][col] if 'xs' in c else c['x0'] + col * c['px']) * e)
        y = round((c['ys'][r] if 'ys' in c else c['y0'] + r * c['py']) * e)
        q = Image.new('RGBA', (cw + 2 * M, ch + 2 * M), (0, 0, 0, 0))
        if c.get('grade'):  # quadros encostados: recorta o retangulo da celula
            r = im.crop((x, y, x + cw, y + ch))
            q.paste(r, (M, M), r)
            out.append(q.transpose(Image.FLIP_LEFT_RIGHT) if 'm' in fr[2:] else q)
            continue
        for pts in comps:
            if len(pts) < 3:
                continue
            xs = [p[0] for p in pts]; ys = [p[1] for p in pts]
            if max(xs) - min(xs) > 1.5 * cw or max(ys) - min(ys) > 1.5 * ch:
                continue  # linhas da grade da folha, nao boneco
            cx = (min(xs) + max(xs)) / 2; cy = (min(ys) + max(ys)) / 2
            if x <= cx < x + cw and y <= cy < y + ch:
                for p in pts:
                    q.putpixel((p[0] - x + M, p[1] - y + M), im.getpixel(p))
        out.append(q.transpose(Image.FLIP_LEFT_RIGHT) if 'm' in fr[2:] else q)
    grupos = GRUPOS[:len(out)]
    ref = {}
    for i, g in enumerate(grupos):
        if g not in ref:
            ref[g] = out[i].getbbox()
    return out, grupos, ref


def montar(out, grupos, ref, fw=48, fh=40):
    """cola cada quadro num canvas comum, com pes na mesma linha e centro no meio."""
    canv = []
    for i, cell in enumerate(out):
        b = ref[grupos[i]]
        cx = (b[0] + b[2]) / 2
        ox = round(fw / 2 - cx)
        oy = fh - 1 - b[3]
        q = Image.new('RGBA', (fw, fh), (0, 0, 0, 0))
        q.paste(cell, (ox, oy), cell)
        canv.append(q)
    return canv


def uniao(canv):
    bs = [q.getbbox() for q in canv]
    return (min(b[0] for b in bs), min(b[1] for b in bs), max(b[2] for b in bs), max(b[3] for b in bs))


ALTURA_ELENCO = (18, 22)   # altura dos 16 px aprovados do jogo (Gladion, Kukui, Looker, Lillie)


def lum(p):
    return 0.299 * p[0] + 0.587 * p[1] + 0.114 * p[2]


def escuro(p):
    return p[3] >= 128 and lum(p) < 80


def escolher_descartes(mats, n):
    """mats: lista de matrizes (linhas de pixels), mesmas dimensoes. Escolhe n indices a
    descartar espalhados pelo corpo (uma por faixa), somando em todos os quadros o
    custo de apagar a linha: pixels que mudam em relacao a vizinha, mais um peso
    alto para pixel escuro que so existe nessa linha (traco de contorno de 1 px)."""
    L = len(mats[0])

    def custo(i):
        c = 0
        for m in mats:
            for x, (p, q) in enumerate(zip(m[i], m[i - 1])):
                if p != q:
                    c += 1
                if (p[3] >= 128) != (q[3] >= 128):
                    c += 1
                if escuro(p):
                    nxt = m[i + 1][x] if i + 1 < L else (0, 0, 0, 0)
                    if not escuro(q) and not escuro(nxt):
                        c += 6
        return c
    keep = set(range(L))
    for k in range(n):
        a = round(k * L / n); b = round((k + 1) * L / n)
        cand = [i for i in range(max(a, 1), b) if i - 1 in keep and i in keep]
        if not cand:
            continue
        i = min(cand, key=lambda i: (custo(i), abs(i - (a + b) / 2)))
        keep.discard(i)
    return sorted(keep)


def olhos(m):
    """grupos de pixels escuros cercados de pixels claros (olho, boca): lista de listas (x, y)."""
    h, w = len(m), len(m[0])
    sem = set()
    for y in range(1, h - 1):
        for x in range(1, w - 1):
            p = m[y][x]
            if p[3] < 128 or lum(p) >= 110:
                continue
            viz = [m[y + dy][x + dx] for dx in (-1, 0, 1) for dy in (-1, 0, 1) if dx or dy]
            if sum(1 for q in viz if q[3] >= 128 and lum(q) > 140) >= 5:
                sem.add((x, y))
    # so as sementes, ligadas em 8 vizinhos (crescer para pixel escuro vizinho engole o contorno)
    grupos = []
    vis = set()
    for s0 in sem:
        if s0 in vis:
            continue
        st = [s0]; vis.add(s0); g = []
        while st:
            x, y = st.pop(); g.append((x, y))
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    q = (x + dx, y + dy)
                    if q in sem and q not in vis:
                        vis.add(q); st.append(q)
        grupos.append(g)
    return grupos


def mascara_rosto(m):
    """olhos/boca e a vizinhanca 3x3: protegido."""
    h, w = len(m), len(m[0])
    mk = [[False] * w for _ in range(h)]
    for g in olhos(m):
        for x, y in g:
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    if 0 <= x + dx < w and 0 <= y + dy < h:
                        mk[y + dy][x + dx] = True
    return mk


OLHO_1PX_ATE = 16   # boneco ate esta largura: olho com 1 coluna (regra do elenco 16x32, 30/09)


def afinar_olhos(mats, n):
    """no elenco 16x32 o olho tem 1 px de largura por 2 de altura. Olho mais largo no
    quadro parado: fica a coluna mais perto do eixo, as outras saem (em par espelhado),
    antes do resto da reducao. Devolve (mats, colunas que faltam tirar)."""
    cx = centro(mats[0])
    if cx is None:
        return mats, n
    w = len(mats[0][0])
    fora = set()
    for g in olhos(mats[0]):
        xs = sorted({x for x, y in g}, key=lambda x: (abs(x - cx), x))
        if 1 < len(xs) <= 4:          # 2 a 4 colunas: olho; mais largo e outra coisa (franja)
            fora |= set(xs[1:])
    fora |= {round(2 * cx - x) for x in list(fora) if 0 <= round(2 * cx - x) < w}
    fora = sorted(fora)[:n]
    if not fora:
        return mats, n
    cols = [x for x in range(w) if x not in fora]
    return [[[r[c] for c in cols] for r in m] for m in mats], n - len(fora)


def energia(m, prot):
    """custo de tirar cada pixel: borda da silhueta, diferenca com os vizinhos,
    pixel de contorno e mascara de rosto."""
    h, w = len(m), len(m[0])
    E = [[0.0] * w for _ in range(h)]
    for y in range(h):
        for x in range(w):
            p = m[y][x]
            e = 0.0
            for dx, dy in ((1, 0), (0, 1), (-1, 0), (0, -1)):
                xx, yy = x + dx, y + dy
                q = m[yy][xx] if 0 <= xx < w and 0 <= yy < h else (0, 0, 0, 0)
                if (p[3] >= 128) != (q[3] >= 128):
                    e += 60
                elif p[3] >= 128:
                    e += sum(abs(p[i] - q[i]) for i in range(3)) / 3
            if escuro(p):
                e += 120
            if prot[y][x]:
                e += 300
            E[y][x] = e
    return E


# Costura em coluna RETA (None): costura diagonal serra cabelo e silhueta (Gladion, Steven,
# Diantha, 29/09). A penalidade de vizinhanca forte (800, raio 3) espalha os cortes e mantem
# a proporcao chapeu/corpo (Hilda) sem voltar as faixas cegas que apagam o rosto (Lusamine).
DIAGONAL = None


def costura(Es, diag=None):
    """caminho de cima para baixo (uma coluna por linha, passo de ate 1) de menor energia
    somada em todas as matrizes; `diag` e o custo de cada passo diagonal (None = reta)."""
    diag = DIAGONAL if diag is None else diag
    h, w = len(Es[0]), len(Es[0][0])
    D = [[sum(e[y][x] for e in Es) for x in range(w)] for y in range(h)]
    back = [[0] * w for _ in range(h)]
    for y in range(1, h):
        for x in range(w):
            best, bv = x, D[y - 1][x]
            if diag is not None:
                for xx in (x - 1, x + 1):
                    if 0 <= xx < w and D[y - 1][xx] + diag < bv:
                        bv, best = D[y - 1][xx] + diag, xx
            D[y][x] += bv; back[y][x] = best
    x = min(range(w), key=lambda x: D[h - 1][x])
    s = [0] * h
    for y in range(h - 1, -1, -1):
        s[y] = x; x = back[y][x]
    return s


def tirar_costura(m, s):
    return [r[:c] + r[c + 1:] for r, c in zip(m, s)]


def centro(m):
    """eixo vertical do boneco (meio da caixa de pixels opacos) num quadro; None se vazio."""
    xs = [x for r in m for x, p in enumerate(r) if p[3] >= 128]
    return (min(xs) + max(xs)) / 2 if xs else None


def seam_colunas(mats, n, pen=800, raio=3, decai=0.9, espelhar=False):
    """tira n colunas (costura reta), as mesmas em todos os quadros (mesma direcao), com
    penalidade nas colunas vizinhas da ultima removida para espalhar o corte. Com
    `espelhar` (quadros de frente/costas) as colunas saem aos pares simetricos em
    relacao ao eixo do boneco, senao um olho fica com 4 px e o outro com 2 (Zinnia)."""
    mats = [[r[:] for r in m] for m in mats]
    prots = [mascara_rosto(m) for m in mats]
    h = len(mats[0])
    extra = [[0.0] * len(mats[0][0]) for _ in range(h)]
    cx = centro(mats[0]) if espelhar else None
    falta = n
    while falta > 0:
        Es = [energia(m, prots[i]) for i, m in enumerate(mats)] + [extra]
        w = len(extra[0])
        C = [sum(e[y][x] for e in Es for y in range(h)) for x in range(w)]
        if cx is not None and falta >= 2:
            pares = [(x, round(2 * cx - x)) for x in range(w) if x < round(2 * cx - x) < w]
            if pares:
                a, b = min(pares, key=lambda t: C[t[0]] + C[t[1]])
                tirar = [b, a]     # o maior indice primeiro, para nao deslocar o outro
                cx -= 1            # o eixo anda uma coluna para a esquerda
            else:
                tirar = [min(range(w), key=C.__getitem__)]
        else:
            tirar = [min(range(w), key=C.__getitem__)]
        for x0 in tirar:
            s = [x0] * h
            mats = [tirar_costura(m, s) for m in mats]
            prots = [tirar_costura(p, s) for p in prots]
            extra = tirar_costura(extra, s)
            w = len(extra[0])
            for y in range(h):
                for d in range(-raio, raio + 1):
                    x = x0 + d
                    if 0 <= x < w:
                        extra[y][x] += pen * (raio + 1 - abs(d)) / (raio + 1)
        for y in range(h):
            for x in range(w):
                extra[y][x] *= decai
        falta -= len(tirar)
    return mats


def parte_por_conteudo(razao):
    """fracao das colunas removidas que o custo de conteudo escolhe; o resto sai em faixas
    uniformes. Encolher pela metade (arte chibi de 32 px: Zinnia, Diantha) so por conteudo
    mantem os olhos na largura nativa e some com a pele em volta (olhos enormes, 30/09);
    uniforme puro apaga o rosto quando o cabelo disputa espaco (Lusamine, r=0,59)."""
    return min(1.0, max(0.0, (razao - 0.4) / 0.4))


def colunas_uniformes(mats, n, espelhar=False):
    """apaga n colunas em faixas uniformes com o custo de escolher_descartes (transposto).
    Com `espelhar` (frente/costas), escolhe na metade esquerda e espelha no eixo do boneco;
    se n e impar, a coluna extra e a do eixo (ou a mais barata que sobrar)."""
    w = len(mats[0][0])
    T = [[list(c) for c in zip(*m)] for m in mats]
    cx = centro(mats[0]) if espelhar else None
    if cx is None or n < 2:
        cols = escolher_descartes(T, n)
        return [[[r[c] for c in cols] for r in m] for m in mats]
    esq = [x for x in range(w) if x < round(2 * cx - x) < w]      # colunas com par a direita
    keep_e = escolher_descartes([[t[x] for x in esq] for t in T], n // 2)
    fora = {esq[i] for i in range(len(esq)) if i not in keep_e}
    fora |= {round(2 * cx - x) for x in list(fora)}
    if n % 2:
        meio = [x for x in range(w) if round(2 * cx - x) == x and x not in fora]
        if meio:
            fora.add(meio[0])
        else:
            resto = [x for x in range(w) if x not in fora]
            keep_r = escolher_descartes([[t[x] for x in resto] for t in T], 1)
            fora |= {resto[i] for i in range(len(resto)) if i not in keep_r}
    cols = [x for x in range(w) if x not in fora]
    return [[[r[c] for c in cols] for r in m] for m in mats]


def reduzir(canv, grupos, W, H):
    """colunas: parte em faixas uniformes, parte por costura de conteudo (por direcao);
    depois linhas apagadas em faixas com prioridade."""
    L, T, R, B = uniao(canv)
    mats = [[[q.getpixel((x, y)) for x in range(L, R)] for y in range(T, B)] for q in canv]
    h, w = B - T, R - L
    n = max(0, w - W)
    k = round(n * parte_por_conteudo(W / w))
    out = [None] * len(mats)
    for g in set(grupos):
        idx = [i for i in range(len(mats)) if grupos[i] == g]
        ms = [mats[i] for i in idx]
        esp = g in (0, 1)   # frente e costas: colunas aos pares espelhados
        ng, kg = n, k
        if g == 0 and W <= OLHO_1PX_ATE and n:
            ms, ng = afinar_olhos(ms, n)
            kg = min(k, ng)
        if ng - kg:
            ms = colunas_uniformes(ms, ng - kg, espelhar=esp)
        if kg:
            ms = seam_colunas(ms, kg, espelhar=esp)
        for i, m in zip(idx, ms):
            out[i] = m
    rows = escolher_descartes(out, h - H) if H < h else list(range(h))
    res = []
    for m in out:
        im = Image.new('RGBA', (len(m[0]), len(rows)), (0, 0, 0, 0))
        for y, r in enumerate(rows):
            for x, p in enumerate(m[r]):
                im.putpixel((x, y), p)
        res.append(im)
    return res


def folha(frames, fw, fh=32, pes=30):
    """frames todos com mesmo tamanho (caixa comum). Centraliza e poe pes na linha `pes`."""
    w, h = frames[0].size
    ox = (fw - w) // 2
    oy = pes + 1 - h
    s = Image.new('RGBA', (fw * len(frames), fh), (0, 0, 0, 0))
    for i, f in enumerate(frames):
        s.paste(f, (i * fw + ox, oy), f)
    return s


def pre_quant(sheet, n=40):
    """JPG: reduz as cores com median cut antes da fusao fina."""
    cores = {sheet.getpixel((x, y))[:3] for x in range(sheet.width) for y in range(sheet.height) if sheet.getpixel((x, y))[3] >= 128}
    if len(cores) <= n:
        return sheet
    rgb = sheet.convert('RGB')
    q = rgb.quantize(n, method=Image.Quantize.MEDIANCUT).convert('RGB')
    out = sheet.copy()
    for y in range(sheet.height):
        for x in range(sheet.width):
            if sheet.getpixel((x, y))[3] >= 128:
                out.putpixel((x, y), q.getpixel((x, y)) + (255,))
    return out


def limpar_jpg(canv, n=24):
    """tira o ruido do JPG antes de reduzir: median cut para n cores (todos os quadros
    juntos), SEM a fusao gulosa ate 15, que fica para depois de reduzir. Reduzir com
    ruido dobra o contorno (Ramos); fundir a 15 antes apaga os olhos, cor rara que a
    fusao por quantidade absorve na pele (Agatha, 30/09)."""
    w, h = canv[0].size
    sheet = Image.new('RGBA', (w * len(canv), h), (0, 0, 0, 0))
    for i, q in enumerate(canv):
        sheet.paste(q, (i * w, 0))
    q = pre_quant(sheet, n)
    return [q.crop((i * w, 0, i * w + w, h)) for i in range(len(canv))]


def tirar_halo_verde(q, voltas=3):
    """JPG sobre fundo verde deixa uma franja verde-escura em volta do boneco que o
    preenchimento do fundo nao pega (tolerancia menor que a distancia) e que gasta
    3 das 24 cores do median cut; sem ela a Olivia perdia ate o tom claro do top.
    Apaga pixel esverdeado encostado no transparente, de fora para dentro."""
    q = q.copy(); px = q.load(); W, H = q.size
    verde = lambda p: p[3] >= 128 and p[1] > p[0] + 4 and p[1] > p[2] + 8
    fora = lambda x, y: not (0 <= x < W and 0 <= y < H) or px[x, y][3] < 128
    for _ in range(voltas):
        borda = [(x, y) for y in range(H) for x in range(W) if verde(px[x, y])
                 and any(fora(x + a, y + b) for a, b in ((1, 0), (-1, 0), (0, 1), (0, -1)))]
        for k in borda:
            px[k] = (0, 0, 0, 0)
    return q


def preparar(nome):
    c = CHARS[nome]
    out, grupos, ref = frames_nativos(c)
    canv = montar(out, grupos, ref)
    if c.get('halo'):
        canv = [tirar_halo_verde(q) for q in canv]
    if c.get('jpg'):
        canv = limpar_jpg(canv)
    L, T, R, B = uniao(canv)
    p = dict(c=c, grupos=grupos, canv=canv, w0=R - L, h0=B - T, canv2=None)
    if c['k'] == 2 and not c.get('jpg'):
        o2, g2, r2 = frames_nativos(c, big=True)
        p['canv2'] = montar(o2, g2, r2, 96, 80)
        L, T, R, B = uniao(p['canv2'])
        p['w2'], p['h2'] = R - L, B - T
    return p


def altura_elenco(W, H):
    """altura alternativa quando a proporcional cai fora do elenco: baixa demais (arte
    mais larga que alta, Lusamine) sobe para 20; alta demais so importa ate 18 px de
    largura (Ramos, Leon) e desce para 22. Fora disso, devolve a propria H."""
    if H < ALTURA_ELENCO[0]:
        return 20
    if H > ALTURA_ELENCO[1] and W <= 18:
        return ALTURA_ELENCO[1]
    return H


def gerar(p, W, fw=None, H=None):
    """folha indexada com o boneco em W px de largura e H de altura (None = proporcional);
    None se nao cabe sem ampliar. Devolve (H, quadro, folha, origem)."""
    fontes = [(p['canv'], p['w0'], p['h0'], 'nativo')]
    if p['canv2']:
        fontes.append((p['canv2'], p['w2'], p['h2'], 'da arte 2x'))
    for canv, w0, h0, origem in fontes:
        Hp = round(h0 * W / w0)
        Ha = H or Hp
        if W <= w0 and Ha <= h0 and Ha <= 31:
            if origem == 'nativo' and (W != w0 or Ha != h0):
                origem = ''
            if H and H != Hp:
                origem = (origem + '  altura do elenco' if Ha == altura_elenco(W, Hp) else origem + f'  altura {H}').strip()
            fr = reduzir(canv, p['grupos'], W, Ha)
            fw = fw or (16 if W <= 16 else 32)
            res, fus = G.quantizar(pre_quant(folha(fr, fw), p['c'].get('pre_cores', 40)), 15)
            return Ha, fw, tirar_fiapos(res, fw), origem
    return None


def tirar_fiapos(res, fw):
    """apaga, em cada quadro, pedaco solto do boneco com 1 px de espessura (resto de
    linha de grade da folha: a linha branca acima da cabeca do Byron, 30/09)."""
    px = res.load()
    for f in range(res.width // fw):
        vis, comps = set(), []
        for y in range(res.height):
            for x in range(fw):
                if px[f * fw + x, y] and (x, y) not in vis:
                    st, c = [(x, y)], []
                    vis.add((x, y))
                    while st:
                        a, b = st.pop(); c.append((a, b))
                        for da in (-1, 0, 1):
                            for db in (-1, 0, 1):
                                q = (a + da, b + db)
                                if 0 <= q[0] < fw and 0 <= q[1] < res.height and q not in vis and px[f * fw + q[0], q[1]]:
                                    vis.add(q); st.append(q)
                    comps.append(c)
        comps.sort(key=len)
        for c in comps[:-1]:
            if len({a for a, _ in c}) == 1 or len({b for _, b in c}) == 1:
                for a, b in c:
                    px[f * fw + a, b] = 0
    return res


def cmd_propostas(nomes):
    for nome in nomes:
        p = preparar(nome)
        print(f"{nome}: nativo {p['w0']}x{p['h0']}" + (f", arte 2x {p['w2']}x{p['h2']}" if p['canv2'] else ''))
        feitos = []
        for W in range(16, 33):
            g = gerar(p, W)
            if not g:
                break
            H, fw, res, origem = g
            feitos.append((W, H, fw, res, origem))
            print(f'  {W}x{H} {origem}')
            He = altura_elenco(W, H)
            if He != H:   # proporcional cai fora do elenco: propoe tambem a altura do elenco
                g = gerar(p, W, H=He)
                if g:
                    feitos.append((W,) + g)
                    print(f'  {W}x{g[0]} {g[3]}')
        comparar(nome, feitos, p['c'])


def cmd_final(nome, W, saida, fw=32, H=None):
    p = preparar(nome)
    if fw == 16 and W > 16:
        sys.exit('quadro 16x32 comporta boneco de no maximo 16 px')
    g = gerar(p, W, fw=fw, H=H)
    if not g:
        sys.exit(f'{nome}: {W}x{H or "?"} nao cabe sem ampliar a arte')
    H, fw, res, _ = g
    res.save(saida)
    print(f'{nome}: boneco {W}x{H}, {res.width // fw} quadros {fw}x32 -> {saida}')


def quadro_rgba(res, i, qfw):
    fr = res.convert('RGBA').crop((i * qfw, 0, i * qfw + qfw, 32))
    px = fr.load()
    for yy in range(32):
        for xx in range(qfw):
            if res.getpixel((i * qfw + xx, yy)) == 0:
                px[xx, yy] = (0, 0, 0, 0)
    return fr


def celula(fr, z, bgc=(120, 176, 96, 255)):
    cell = Image.new('RGBA', (32, 32), bgc)
    cell.paste(fr, ((32 - fr.width) // 2, 0), fr)
    return cell.resize((32 * z, 32 * z), Image.NEAREST)


def refs(c):
    """quadro parado de frente do sprite atual do personagem no jogo e do jogador."""
    out = []
    for rot, p in [('no jogo hoje', c.get('atual')), ('jogador', OW + 'brendan/walking.png')]:
        fp = p and os.path.join(ROOT, *p.split('/'))
        if fp and os.path.exists(fp):
            m = Image.open(fp)
            qfw = 32 if m.width % 32 == 0 and m.width >= 288 else 16
            out.append((rot, quadro_rgba(m, 0, qfw)))
    return out


def comparar(nome, feitos, c, z=4):
    """folha de comparacao ampliada: cada linha uma proposta; a esquerda, referencias em escala."""
    rs = refs(c)
    fa = c.get('atual') and os.path.join(ROOT, *c['atual'].split('/'))
    atual = Image.open(fa) if fa and os.path.exists(fa) else None
    n = max(r[3].width // r[2] for r in feitos)
    rowh = 32 * z + 18
    xoff = 10 + len(rs) * (32 * z + 8) + 16
    W = xoff + n * 32 * z + 10
    img = Image.new('RGB', (W, 34 + rowh * len(feitos)), (40, 40, 48))
    d = ImageDraw.Draw(img)
    d.text((6, 8), f'{nome} - arte: {c.get("cred", "?")} - ampliado {z}x - cada quadrado e um quadro 32x32; vermelho = limite do quadro 16x32', fill=(230, 230, 230))
    for k, (Wd, H, qfw, res, origem) in enumerate(feitos):
        y0 = 34 + k * rowh
        for j, (rot, fr) in enumerate(rs):
            x = 10 + j * (32 * z + 8)
            img.paste(celula(fr, z, (90, 130, 72, 255)), (x, y0 + 14))
            if k == 0:
                d.text((x, y0), rot, fill=(170, 170, 170))
        igual = atual is not None and atual.size == res.size and \
            list(atual.convert('RGBA').getdata()) == list(res.convert('RGBA').getdata())
        d.text((xoff, y0), f'boneco {Wd}x{H}  (quadro {qfw}x32)  {origem}' + ('  = IGUAL AO JOGO HOJE' if igual else ''),
               fill=(120, 255, 140) if igual else (255, 220, 120))
        for i in range(res.width // qfw):
            x = xoff + i * 32 * z
            img.paste(celula(quadro_rgba(res, i, qfw), z), (x, y0 + 14))
            d.rectangle((x, y0 + 14, x + 32 * z - 1, y0 + 14 + 32 * z - 1), outline=(30, 30, 30))
            if qfw == 16:
                d.rectangle((x + 8 * z, y0 + 14, x + 24 * z - 1, y0 + 14 + 32 * z - 1), outline=(200, 60, 60))
    pasta = c.get('pasta', nome)
    sufixo = f' ({nome})' if pasta != nome else ''
    img.save(os.path.join(FT, pasta, f'Sprite - comparacao no jogo{sufixo}.png'))


if __name__ == '__main__':
    a = sys.argv[1:]
    if a[:1] == ['final'] and len(a) >= 4:
        opts = dict(zip(a[4::2], a[5::2]))
        if set(opts) - {'--quadro', '--altura'}:
            sys.exit(__doc__)
        cmd_final(a[1], int(a[2]), a[3], int(opts.get('--quadro', 32)), int(opts['--altura']) if '--altura' in opts else None)
    elif a[:1] == ['propostas']:
        cmd_propostas(a[1:] or list(CHARS))
    else:
        sys.exit(__doc__)
