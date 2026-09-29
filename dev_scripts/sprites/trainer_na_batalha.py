#!/usr/bin/env python3
"""Comparacao do front pic de treinador NA BATALHA, em varios tamanhos.

Para cada personagem de .filetransfer/.trainers/<Nome>/ le 'Trainer - AUTOR.*'
e grava 'Trainer - comparacao no jogo.png': a tela de batalha (fundo 1 Forest,
240x160) com o treinador na posicao do jogo, lado a lado:

    no jogo hoje  |  64x64 (todas as telas)  |  80x80 (so na batalha, TRAINER_SPRITE_LARGE)

Posicao igual a do jogo: centro do sprite em (176, 40); o 64x64 comeca em
y=8 e o 80x80 tambem (sobra para baixo, ver battle_gfx_sfx_util.c). Cores ja
reduzidas a 15 + transparencia, como o jogo mostraria.

    trainer_na_batalha.py [Nome ...]      (sem nome: todos de TRAINERS)

Precisa de Pillow (no WSL: Python do Windows).
"""
import glob
import os
import sys
from collections import Counter
from PIL import Image, ImageDraw

AQUI = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, AQUI)
sys.path.insert(0, os.path.dirname(AQUI))
import sprite_gba as G  # noqa: E402
from trainer_pic_large import recover_grid  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(AQUI))
TR = os.path.join(ROOT, '.filetransfer', '.trainers')
FP = 'graphics/trainers/front_pics/'
FUNDO = 'graphics/battle_environment/plain/1 Forest.png'

# atual: front pic de hoje (64x64); o _large ao lado, se existir, e o da batalha.
# grid: arte ampliada por fator nao inteiro (mediana do miolo de cada bloco).
# jpg: fundo com ruido, tirado por tolerancia a partir da borda.
TRAINERS = {
    'Agatha': {}, 'Alder': {}, 'Ash': {}, 'Barry': {}, 'Cheren': {}, 'Cyrus': dict(jpg=True),
    'Diantha': {}, 'Gardenia': {}, 'Hau': {}, 'Hilda': dict(jpg=True), 'Jessie e James': {},
    'Leon': {}, 'Lorelei': {}, 'N': dict(jpg=True, grid=2), 'Olivia': {}, 'Shelly': {}, 'Zinnia': {},
    'Anabel': dict(atual='salon_maiden_anabel'),
    'Blue': dict(atual='leader_blue', jpg=True),
    'Brendan': dict(atual='brendan_rs'),
    'Bruno': dict(atual='elite_four_bruno'),
    'Byron': dict(atual='byron'),
    'Colress': dict(atual='colress', grid=518 / 80),
    'Cynthia': dict(atual='cynthia_front_pic', large='cynthia_large'),
    'Elesa': dict(atual='elesa'),
    'Fantina': dict(atual='fantina'),
    'Gladion': dict(atual='gladion'),
    'Guzma': dict(atual='guzma'),
    'Kukui': dict(atual='kukui'),
    'Lillie': dict(atual='lillie', grid=5),
    'Lusamine': dict(atual='lusamine'),
    'Misty': dict(atual='misty'),
    'Ramos': dict(atual='ramos'),
    'Soliera': dict(atual='soliera'),
    'Steven': dict(atual='steven', grid=1452 / 76),
    'Volkner': dict(atual='volkner'),
}

TELA = (240, 160)
CAMPO = 112          # altura do cenario; abaixo fica a caixa de texto
CENTRO = (176, 40)   # centro do sprite do oponente (battle_anim_mons.c)


def dist(a, b):
    return sum(abs(a[i] - b[i]) for i in range(3))


def sem_fundo(im, jpg):
    """Tira o fundo a partir da borda: as cores que ocupam boa parte da borda
    viram transparentes nas regioes ligadas a ela (o corpo nunca fura)."""
    im = im.copy(); px = im.load(); W, H = im.size
    borda = [px[x, y] for x in range(W) for y in (0, H - 1)] + [px[x, y] for y in range(H) for x in (0, W - 1)]
    cnt = Counter(p[:3] for p in borda if p[3] >= 128)
    tol = 60 if jpg else 0
    # no JPG o ruido espalha o fundo em tons vizinhos: conta a vizinhanca de cada cor
    fundos = [c for c in cnt if sum(n for o, n in cnt.items() if dist(c, o) <= tol // 2) >= len(borda) * 0.15]
    isbg = lambda p: p[3] < 128 or any(dist(p, f) <= tol for f in fundos)
    st = [(x, y) for x in range(W) for y in (0, H - 1)] + [(x, y) for y in range(H) for x in (0, W - 1)]
    st = [q for q in st if isbg(px[q])]
    vis = set(st)
    while st:
        x, y = st.pop()
        for q in ((x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)):
            if 0 <= q[0] < W and 0 <= q[1] < H and q not in vis and isbg(px[q]):
                vis.add(q); st.append(q)
    for q in vis:
        px[q] = (0, 0, 0, 0)
    for y in range(H):  # alfa parcial vira opaco ou some
        for x in range(W):
            if 0 < px[x, y][3] < 128:
                px[x, y] = (0, 0, 0, 0)
            elif px[x, y][3]:
                px[x, y] = px[x, y][:3] + (255,)
    return im


def figura(nome, c):
    f = glob.glob(os.path.join(TR, nome, 'Trainer - *'))
    f = [x for x in f if 'comparacao' not in x]
    if not f:
        return None, None
    im = Image.open(f[0]).convert('RGBA')
    if c.get('grid'):
        im = recover_grid(im, c['grid'])
    else:
        k = G.escala_detectada(im) if im.width * im.height <= 160 * 160 else 1
        if k > 1:
            im = im.resize((im.width // k, im.height // k), Image.NEAREST)
    im = sem_fundo(im, c.get('jpg'))
    return im.crop(im.getbbox()), os.path.basename(f[0])


def indexada(fig, lado):
    """Figura -> quadro lado x lado com <=15 cores; reduz (sem reamostrar) se nao cabe."""
    w, h = fig.size
    if w > lado or h > lado:
        fig, s = G.reduzir_sem_reamostrar(fig, lado, lado)
        rot = f'reduzido a {s:.0%}'
    else:
        rot = 'nativo, sem reducao'
    q = Image.new('RGBA', (lado, lado), (0, 0, 0, 0))
    fw, fh = fig.size
    pes = 63 if lado == 64 else max(63, fh - 1)   # mesmo chao dos 64x64 (trainer_pic_large.py)
    q.paste(fig, ((lado - fw) // 2, pes - fh + 1), fig)
    cores = {p[:3] for p in q.getdata() if p[3]}
    if len(cores) > 40:
        rgb = q.convert('RGB').quantize(40, method=Image.Quantize.MEDIANCUT).convert('RGB')
        q = Image.merge('RGBA', (*rgb.split(), q.getchannel('A')))
    res, _ = G.quantizar(q, 15)
    return rgba_de(res), rot


def rgba_de(p):
    out = p.convert('RGBA'); px = out.load()
    for y in range(p.height):
        for x in range(p.width):
            if p.getpixel((x, y)) == 0:
                px[x, y] = (0, 0, 0, 0)
    return out


def tela(pic):
    t = Image.new('RGBA', TELA, (248, 248, 248, 255))
    fundo = Image.open(os.path.join(ROOT, FUNDO)).convert('RGBA').crop((0, 0, 240, CAMPO))
    t.paste(fundo, (0, 0))
    d = ImageDraw.Draw(t)
    d.rectangle((14, 16, 111, 43), fill=(248, 248, 224), outline=(64, 64, 64))       # caixa de vida
    d.rectangle((4, CAMPO + 3, 235, 156), fill=(248, 248, 248), outline=(96, 112, 136), width=2)  # texto
    if pic is not None:
        t.alpha_composite(pic, (CENTRO[0] - pic.width // 2, CENTRO[1] - 32))
    return t


def comparar(nome, z=2):
    c = TRAINERS[nome]
    fig, arq = figura(nome, c)
    if fig is None:
        print(f'{nome}: sem Trainer, pulado')
        return
    paineis = []
    if c.get('atual'):
        base = os.path.join(ROOT, FP)
        large = os.path.join(base, (c.get('large') or c['atual'] + '_large') + '.png')
        p64 = os.path.join(base, c['atual'] + '.png')
        if os.path.exists(large):
            paineis.append(('no jogo hoje - 80x80 (batalha)', rgba_de(Image.open(large))))
        elif os.path.exists(p64):
            paineis.append(('no jogo hoje - 64x64', rgba_de(Image.open(p64))))
    if fig.width <= 64 and fig.height <= 64:
        pic, _ = indexada(fig, 64)
        paineis.append(('64x64 - nativo, sem reducao (cabe; o 80x80 nao mudaria nada)', pic))
    else:
        for lado in (64, 80):
            pic, rot = indexada(fig, lado)
            paineis.append((f'{lado}x{lado} - {rot}', pic))
    w, h = TELA[0] * z, TELA[1] * z
    gap, topo = 16, 40
    img = Image.new('RGB', (gap + len(paineis) * (w + gap), topo + h + 16 + 80 + gap), (40, 40, 48))
    d = ImageDraw.Draw(img)
    d.text((gap, 8), f'{nome} - Trainer: {arq} - figura {fig.width}x{fig.height} depois de tirar ampliacao e fundo'
           f' - tela de batalha {z}x', fill=(230, 230, 230))
    d.text((gap, 22), 'o 64x64 e o que Pokenav, card e Dome usam; o 80x80 (TRAINER_SPRITE_LARGE) so aparece na batalha',
           fill=(170, 170, 170))
    for i, (rot, pic) in enumerate(paineis):
        x = gap + i * (w + gap)
        img.paste(tela(pic).resize((w, h), Image.NEAREST).convert('RGB'), (x, topo))
        d.text((x, topo + h + 4), rot, fill=(255, 220, 120))
        # tamanho real (1x) embaixo
        real = Image.new('RGBA', (pic.width, pic.height), (120, 176, 96, 255))
        real.alpha_composite(pic)
        img.paste(real.convert('RGB'), (x, topo + h + 20))
    img.save(os.path.join(TR, nome, 'Trainer - comparacao no jogo.png'))
    print(f'{nome}: figura {fig.width}x{fig.height} ({arq})')


if __name__ == '__main__':
    for n in sys.argv[1:] or list(TRAINERS):
        comparar(n)
