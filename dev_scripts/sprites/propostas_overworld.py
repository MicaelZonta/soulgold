#!/usr/bin/env python3
"""Propostas de overworld em varios tamanhos, com folha de comparacao.

Regra do autor (27/09/2026): sprite de overworld novo nao vai direto para o
jogo. Primeiro geram-se VARIAS opcoes de tamanho (boneco com 16, 17, 18...
px de largura, ate o maximo que a arte permite sem ampliar e sem passar de
31 px de altura) mais uma folha de comparacao ampliada ao lado do jogador e
do sprite atual; o autor escolhe o tamanho; so entao `final` grava o PNG.

    propostas_overworld.py propostas [Nome ...]
        -> .filetransfer/<Nome>/<Nome> - overworld WxH (quadro 32x32).png
        -> .filetransfer/<Nome>/<Nome> - overworld propostas comparadas.png
    propostas_overworld.py final <Nome> <largura> <saida.png> [--quadro 16]
        -> folha do jogo 32x32 (ou 16x32 com --quadro 16; 9 quadros, ou 12 se
           a arte tem o lado direito)

A reducao apaga linhas/colunas (a mais parecida com a vizinha, espalhadas pelo
corpo): as mesmas linhas em todos os quadros, colunas escolhidas por direcao.
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
FT = os.path.join(ROOT, '.filetransfer')

# Ordem do jogo: parado baixo, parado cima, parado esq, 2x baixo, 2x cima, 2x esq
# e, se a arte tiver, parado dir + 2x dir (sAnimTable_StandardAsym, 12 quadros).
# Celulas sao (linha, coluna) da grade da folha de origem.
RPG = [(0, 0), (3, 0), (1, 0), (0, 1), (0, 3), (3, 1), (3, 3), (1, 1), (1, 3), (2, 0), (2, 1), (2, 3)]
L3 = [(1, 0), (0, 0), (2, 0), (1, 1), (1, 2), (0, 1), (0, 2), (2, 1), (2, 2), (3, 0), (3, 1), (3, 2)]
OW = 'graphics/object_events/pics/people/'
CHARS = {
    'Looker': dict(f='Looker/Sprite - Vergolophus.png', k=1, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                   cred='Vergolophus', atual=OW + 'special/looker.png'),
    'Anabel': dict(f='Anabel/Trainer- Vergolophus.png', k=1, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                   cred='Vergolophus', atual=OW + 'frontier_brains/anabel.png'),
    'Kukui': dict(f='Kukui/Sprite - Wolfgang62.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                  cred='Wolfgang62', atual=OW + 'special/kukui.png'),
    'Lusamine': dict(f='Lusamine/Lusamine Sprite Diego WT.png', k=2, cell=(32, 32), x0=0, y0=0, px=32, py=32, frames=RPG,
                     cred='DiegoWT', atual=OW + 'special/lusamine.png'),
    'Lillie': dict(f='Lillie/Sprite.png', k=2, crop=(89, 1, 251, 249), cell=(26, 30), x0=0, y0=0, px=27, py=31,
                   frames=L3, bgs=[(153, 87, 53)], cred='Zender1752', atual=OW + 'special/lillie.png'),
    'Gladion': dict(f='Gladion/Gladion - Sprite e Trainer - Derlo.png', k=1, crop=(0, 0, 100, 200), cell=(33, 50), x0=0,
                    ys=[14, 80, 144], px=33, frames=[(0, 0), (1, 0), (2, 0), (0, 1), (0, 2), (1, 1), (1, 2), (2, 1), (2, 2)],
                    cred='Derlo', atual=OW + 'special/gladion.png'),
    'Cynthia': dict(f='Cynthia/Sprite.png', k=1, cell=(27, 32), x0=0, y0=0, px=27, py=32,
                    frames=[(0, 0), (1, 0), (2, 0), (5, 0), (6, 0), (3, 0), (4, 0), (7, 0), (8, 0)], cred='oficial (Platinum)'),
    'Brendan': dict(f='Brendan/hyo-oppa  - Sprite e Trainer.png', k=1, cell=(25, 33), x0=7, ys=[0, 33, 64, 97], px=25,
                    frames=[(0, 1), (1, 1), (2, 1), (0, 0), (0, 2), (1, 0), (1, 2), (2, 0), (2, 2), (3, 1), (3, 0), (3, 2)],
                    cred='hyo-oppa'),
    'Elesa': dict(f='Elesa/Elesa - Sprite - RHcks.png', k=1, crop=(1, 159, 145, 183), cell=(16, 24), x0=0, y0=0, px=16,
                  py=24, grade=True, frames=[(0, i) for i in range(9)], cred='RHcks', atual=OW + 'special/elesa.png'),
    'Blue': dict(f='Blue/Sprite e Trainer chrisx698.jpg', k=1, jpg=True, cell=(24, 35), x0=0, ys=[0, 35, 70, 104], px=24.5,
                 frames=[(0, 0), (1, 0), (3, 0), (0, 1), (0, 2), (1, 1), (1, 2), (3, 1), (3, 2), (2, 0), (2, 1), (2, 2)],
                 cred='chrisx698', atual=OW + 'gym_leaders/blue.png'),
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
    if bgs[0][3] >= 128:
        for col, n in sorted(cnt.items(), key=lambda t: -t[1])[:2]:
            if n > im.width * im.height * 0.15:
                bgs.append(col + (255,))
    bgs += [e + (255,) for e in extra]
    isbg = lambda p: p[3] < 128 or any(b[3] >= 128 and dist(p, b) <= tol for b in bgs)
    if not jpg:
        for y in range(im.height):
            for x in range(im.width):
                if isbg(px[x, y]):
                    px[x, y] = (0, 0, 0, 0)
        return im
    # JPG: preenche a partir da borda da imagem e das linhas da grade, para nao furar o corpo
    W, H = im.size
    marca = [[isbg(px[x, y]) for x in range(W)] for y in range(H)]
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
    for (x, y) in vis:
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


def frames_nativos(c, big=False):
    im = Image.open(os.path.join(FT, c['f'])).convert('RGBA')
    if 'crop' in c:
        im = im.crop(c['crop'])
    e = 2 if big else 1
    if c['k'] == 2 and not big:
        im = mediana2(im) if c.get('jpg') else im.resize((im.width // 2, im.height // 2), Image.NEAREST)
    im = sem_fundo(im, c.get('jpg'), c.get('bgs', ()))
    cw, ch = c['cell'][0] * e, c['cell'][1] * e
    comps = componentes(im)
    M = 10 * e
    out = []
    for (r, col) in c['frames']:
        x = round((c['x0'] + col * c['px']) * e)
        y = (c['ys'][r] if 'ys' in c else c['y0'] + r * c['py']) * e
        q = Image.new('RGBA', (cw + 2 * M, ch + 2 * M), (0, 0, 0, 0))
        if c.get('grade'):  # quadros encostados: recorta o retangulo da celula
            r = im.crop((x, y, x + cw, y + ch))
            q.paste(r, (M, M), r)
            out.append(q)
            continue
        for pts in comps:
            if len(pts) < 3:
                continue
            xs = [p[0] for p in pts]; ys = [p[1] for p in pts]
            cx = (min(xs) + max(xs)) / 2; cy = (min(ys) + max(ys)) / 2
            if x <= cx < x + cw and y <= cy < y + ch:
                for p in pts:
                    q.putpixel((p[0] - x + M, p[1] - y + M), im.getpixel(p))
        out.append(q)
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


def escolher_descartes(mats, n):
    """mats: lista de matrizes (linhas de pixels), mesmas dimensoes. Escolhe n indices a
    descartar espalhados, somando a diferenca com a vizinha em todos os quadros."""
    L = len(mats[0])
    def diff(i):
        return sum(sum(1 for p, q in zip(m[i], m[i - 1]) if p != q) for m in mats)
    keep = set(range(L))
    drop = []
    for k in range(n):
        a = round(k * L / n); b = round((k + 1) * L / n)
        cand = [i for i in range(max(a, 1), b) if i - 1 in keep and i in keep]
        if not cand:
            continue
        i = min(cand, key=lambda i: (diff(i), abs(i - (a + b) / 2)))
        keep.discard(i); drop.append(i)
    return sorted(keep)


def reduzir(canv, grupos, W, H):
    L, T, R, B = uniao(canv)
    mats = [[[q.getpixel((x, y)) for x in range(L, R)] for y in range(T, B)] for q in canv]
    h, w = B - T, R - L
    rows = escolher_descartes(mats, h - H) if H < h else list(range(h))
    mats = [[m[y] for y in rows] for m in mats]
    res = []
    colsets = {}
    for g in set(grupos):
        ms = [[list(c) for c in zip(*mats[i])] for i in range(len(mats)) if grupos[i] == g]
        colsets[g] = escolher_descartes(ms, w - W) if W < w else list(range(w))
    for i, m in enumerate(mats):
        cols = colsets[grupos[i]]
        im = Image.new('RGBA', (len(cols), len(rows)), (0, 0, 0, 0))
        for y, r in enumerate(m):
            for x, cx in enumerate(cols):
                im.putpixel((x, y), r[cx])
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


def preparar(nome):
    c = CHARS[nome]
    out, grupos, ref = frames_nativos(c)
    canv = montar(out, grupos, ref)
    L, T, R, B = uniao(canv)
    p = dict(c=c, grupos=grupos, canv=canv, w0=R - L, h0=B - T, canv2=None)
    if c['k'] == 2 and not c.get('jpg'):
        o2, g2, r2 = frames_nativos(c, big=True)
        p['canv2'] = montar(o2, g2, r2, 96, 80)
        L, T, R, B = uniao(p['canv2'])
        p['w2'], p['h2'] = R - L, B - T
    return p


def gerar(p, W, fw=None):
    """folha indexada com o boneco em W px de largura; None se nao cabe sem ampliar."""
    if W <= p['w0']:
        H = round(p['h0'] * W / p['w0'])
        canv, origem = p['canv'], ('nativo' if W == p['w0'] else '')
    elif p['canv2'] and round(p['h2'] * W / p['w2']) <= 31:
        H = round(p['h2'] * W / p['w2'])
        canv, origem = p['canv2'], 'da arte 2x'
    else:
        return None
    if H > 31:
        return None
    fr = reduzir(canv, p['grupos'], W, H)
    fw = fw or (16 if W <= 16 else 32)
    res, fus = G.quantizar(pre_quant(folha(fr, fw)), 15)
    return H, fw, res, origem


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
            fn = os.path.join(FT, nome, f'{nome} - overworld {W}x{H} (quadro {fw}x32).png')
            res.save(fn)
            feitos.append((W, H, fw, res, origem))
            print(f'  {W}x{H} {origem}')
        comparar(nome, feitos, p['c'])


def cmd_final(nome, W, saida, fw=32):
    p = preparar(nome)
    if fw == 16 and W > 16:
        sys.exit('quadro 16x32 comporta boneco de no maximo 16 px')
    g = gerar(p, W, fw=fw)
    if not g:
        sys.exit(f'{nome}: {W} px nao cabe sem ampliar a arte')
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
        d.text((xoff, y0), f'boneco {Wd}x{H}  (quadro {qfw}x32)  {origem}', fill=(255, 220, 120))
        for i in range(res.width // qfw):
            x = xoff + i * 32 * z
            img.paste(celula(quadro_rgba(res, i, qfw), z), (x, y0 + 14))
            d.rectangle((x, y0 + 14, x + 32 * z - 1, y0 + 14 + 32 * z - 1), outline=(30, 30, 30))
            if qfw == 16:
                d.rectangle((x + 8 * z, y0 + 14, x + 24 * z - 1, y0 + 14 + 32 * z - 1), outline=(200, 60, 60))
    img.save(os.path.join(FT, nome, f'{nome} - overworld propostas comparadas.png'))


if __name__ == '__main__':
    a = sys.argv[1:]
    if a[:1] == ['final'] and len(a) in (4, 6) and (len(a) == 4 or a[4] == '--quadro'):
        cmd_final(a[1], int(a[2]), a[3], int(a[5]) if len(a) == 6 else 32)
    elif a[:1] == ['propostas']:
        cmd_propostas(a[1:] or list(CHARS))
    else:
        sys.exit(__doc__)
