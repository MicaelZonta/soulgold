#!/usr/bin/env python3
"""Converte e confere sprites para o GBA (front pic de treinador e overworld).

Requer Pillow (pip install pillow). Todos os comandos escrevem PNG indexado
com indice 0 = transparente e no maximo 16 cores, que e o que o gbagfx aceita.

  nativo     imagem ampliada (2x, 4x...) -> tamanho de pixel real
  front      qualquer sprite de treinador -> front pic 64x64
  overworld  folha em grade (qualquer ordem) -> folha do jogo, 9 quadros
  conferir   mede um PNG contra as regras (tamanho, cores, indice 0, quadros)
  rom        uso de ROM/EWRAM/IWRAM do ultimo build e custo dos graficos

Guia: .claude/sprites-restricoes-e-custos.md
"""
import argparse
import math
import os
import re
import subprocess
import sys

try:
    from PIL import Image
except ImportError:
    sys.exit("Pillow nao instalado: pip install pillow")

# Cor do indice 0 (transparente) nas saidas. Tem que ser uma cor que NAO existe
# no desenho: se o preto do contorno for igual a cor do indice 0, o contorno
# inteiro vira transparente (aconteceu com o Guzma).
TRANSP = (120, 184, 152)


# ---------------------------------------------------------------- utilidades
def rgba(path):
    return Image.open(path).convert("RGBA")


def escala_detectada(im):
    """Maior fator que divide todas as sequencias de pixels iguais."""
    px = im.load()
    w, h = im.size
    g = 0
    for y in range(h):
        run = 1
        for x in range(1, w):
            if px[x, y] == px[x - 1, y]:
                run += 1
            else:
                g = math.gcd(g, run)
                run = 1
        g = math.gcd(g, run)
    for x in range(w):
        run = 1
        for y in range(1, h):
            if px[x, y] == px[x, y - 1]:
                run += 1
            else:
                g = math.gcd(g, run)
                run = 1
        g = math.gcd(g, run)
    return max(g, 1)


def fundo_transparente(im, cor=None):
    """Troca a cor de fundo (canto superior esquerdo, ou `cor`) por alfa 0."""
    im = im.copy()
    px = im.load()
    bg = cor or px[0, 0]
    if len(bg) == 4 and bg[3] == 0:
        return im
    for y in range(im.height):
        for x in range(im.width):
            if px[x, y][:3] == bg[:3]:
                px[x, y] = (0, 0, 0, 0)
    return im


def reduzir_sem_reamostrar(im, alvo_w, alvo_h):
    """Encolhe o boneco apagando linhas/colunas, sem inventar pixel.

    Divide o boneco em faixas iguais e, em cada faixa, apaga a linha (coluna)
    mais parecida com a vizinha. Espalhar o corte pelo corpo inteiro mantem as
    proporcoes; cortar so onde ha mais repeticao achata pernas e deixa a
    cabeca enorme (primeira tentativa do Guzma).
    """
    x0, y0, x1, y1 = im.getbbox()
    A = [[im.getpixel((x, y)) for x in range(x0, x1)] for y in range(y0, y1)]

    def diff(a, b):
        return sum(1 for p, q in zip(a, b) if p != q)

    def drop(rows, n):
        L = len(rows)
        keep = set(range(L))
        for k in range(n):
            a = round(k * L / n)
            b = round((k + 1) * L / n)
            cand = [i for i in range(max(a, 1), b) if i - 1 in keep and i in keep]
            if not cand:
                continue
            i = min(cand, key=lambda i: (diff(rows[i], rows[i - 1]), abs(i - (a + b) / 2)))
            keep.discard(i)
        return [rows[i] for i in sorted(keep)]

    h, w = len(A), len(A[0])
    if h <= alvo_h and w <= alvo_w:
        return im.crop((x0, y0, x1, y1)), 1.0
    s = min(alvo_h / h, alvo_w / w)
    rows = drop(A, h - round(h * s))
    cols = drop([list(c) for c in zip(*rows)], w - round(w * s))
    rows = [list(r) for r in zip(*cols)]
    out = Image.new("RGBA", (len(rows[0]), len(rows)), (0, 0, 0, 0))
    for y, r in enumerate(rows):
        for x, p in enumerate(r):
            out.putpixel((x, y), p)
    return out, s


def quantizar(im, n_opacas=15):
    """RGBA -> P com indice 0 transparente e ate n_opacas cores.

    Funde sempre o par mais proximo, pesado pela quantidade de pixels: a cor
    rara vai para a vizinha mais parecida. Devolve (imagem, fusoes).
    """
    cnt = {}
    for y in range(im.height):
        for x in range(im.width):
            p = im.getpixel((x, y))
            if p[3] >= 128:
                cnt[p[:3]] = cnt.get(p[:3], 0) + 1
    M = {c: c for c in cnt}

    def d2(a, b):
        return 2 * (a[0] - b[0]) ** 2 + 4 * (a[1] - b[1]) ** 2 + 3 * (a[2] - b[2]) ** 2

    fusoes = []
    while len(cnt) > n_opacas:
        cs = list(cnt)
        best = None
        for a in cs:
            for b in cs:
                if a != b:
                    cost = d2(a, b) * cnt[a]
                    if best is None or cost < best[0]:
                        best = (cost, a, b)
        _, a, b = best
        fusoes.append((a, cnt[a], b))
        cnt[b] += cnt.pop(a)
        for k, v in M.items():
            if v == a:
                M[k] = b
    opq = sorted(cnt, key=sum)
    transp = TRANSP
    while transp in opq:
        transp = ((transp[0] + 7) % 256, transp[1], transp[2])
    pal = [transp] + opq
    pal += [(0, 0, 0)] * (16 - len(pal))
    res = Image.new("P", im.size, 0)
    res.putpalette([v for c in pal for v in c])
    for y in range(im.height):
        for x in range(im.width):
            p = im.getpixel((x, y))
            if p[3] >= 128:
                res.putpixel((x, y), 1 + opq.index(M[p[:3]]))
    return res, fusoes


def relatar_fusoes(fusoes):
    for a, n, b in fusoes:
        print(f"  fundiu {a} ({n} px) -> {b}")


# ---------------------------------------------------------------- comandos
def cmd_nativo(a):
    im = rgba(a.entrada)
    k = a.fator or escala_detectada(im)
    out = im.resize((im.width // k, im.height // k), Image.NEAREST)
    out.save(a.saida)
    print(f"fator {k}x -> {out.size[0]}x{out.size[1]}  ({a.saida})")


def cmd_front(a):
    im = rgba(a.entrada)
    k = escala_detectada(im)
    if k > 1:
        im = im.resize((im.width // k, im.height // k), Image.NEAREST)
        print(f"imagem estava ampliada {k}x -> {im.size[0]}x{im.size[1]}")
    im = fundo_transparente(im)
    boneco, s = reduzir_sem_reamostrar(im, 64, 64)
    if s < 1:
        print(f"boneco reduzido a {s:.0%} (linhas/colunas repetidas removidas)")
    out = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
    w, h = boneco.size
    out.paste(boneco, ((64 - w) // 2, 64 - h))   # centralizado, pes na ultima linha
    res, fus = quantizar(out, 15)
    relatar_fusoes(fus)
    res.save(a.saida)
    print(f"front pic 64x64 -> {a.saida}")


ORDEM_JOGO = ["baixo", "cima", "esquerda", "baixo_a", "baixo_b", "cima_a", "cima_b", "esquerda_a", "esquerda_b"]


def cmd_overworld(a):
    """--mapa lista 9 celulas 'linha,coluna' da grade, na ordem do jogo:
    parado baixo, parado cima, parado esquerda, 2x andar baixo, 2x andar cima,
    2x andar esquerda. A direita o jogo espelha da esquerda."""
    im = rgba(a.entrada)
    k = escala_detectada(im) if a.fator is None else a.fator
    if k > 1:
        im = im.resize((im.width // k, im.height // k), Image.NEAREST)
        print(f"folha estava ampliada {k}x -> {im.size[0]}x{im.size[1]}")
    im = fundo_transparente(im)
    cw, ch = a.celula
    cells = [tuple(int(v) for v in c.split(",")) for c in a.mapa.split()]
    if len(cells) != 9:
        sys.exit("--mapa precisa de 9 celulas 'linha,coluna'")
    fw, fh = a.quadro
    # bbox comum de todos os quadros, para recortar todos com o mesmo deslocamento
    boxes = [im.crop((c * cw, r * ch, c * cw + cw, r * ch + ch)).getbbox() for r, c in cells]
    L = min(b[0] for b in boxes)
    T = min(b[1] for b in boxes)
    R = max(b[2] for b in boxes)
    B = max(b[3] for b in boxes)
    if R - L > fw or B - T > fh:
        print(f"AVISO: o boneco ocupa {R-L}x{B-T} e nao cabe em {fw}x{fh}; "
              f"use --quadro 32 32 ou corte a arte", file=sys.stderr)
    ox = (fw - (R - L)) // 2 - L
    oy = fh - 1 - (B - 1) + a.pes_offset     # pes na ultima linha (ou acima, com --pes-offset)
    sheet = Image.new("RGBA", (fw * 9, fh), (0, 0, 0, 0))
    for i, (r, c) in enumerate(cells):
        cell = im.crop((c * cw, r * ch, c * cw + cw, r * ch + ch))
        q = Image.new("RGBA", (fw, fh), (0, 0, 0, 0))
        q.paste(cell, (ox, oy), cell)
        sheet.paste(q, (i * fw, 0))
    res, fus = quantizar(sheet, 15)
    relatar_fusoes(fus)
    res.save(a.saida)
    print(f"overworld {fw*9}x{fh} (9 quadros {fw}x{fh}) -> {a.saida}")


def cmd_conferir(a):
    m = Image.open(a.png)
    ok = True
    print(f"{a.png}: {m.size[0]}x{m.size[1]} modo {m.mode}")
    if m.mode != "P":
        print("  ERRO: nao e indexado (precisa ser PNG com paleta)")
        return 1
    usados = sorted({m.getpixel((x, y)) for y in range(m.height) for x in range(m.width)})
    pal = m.getpalette()[:48]
    cores = [tuple(pal[i * 3:i * 3 + 3]) for i in range(16)]
    print(f"  indices usados: {len(usados)} (maximo 16, incluindo o 0)")
    if max(usados) > 15:
        print("  ERRO: indice acima de 15 -> gbagfx 'too many colors'")
        ok = False
    iguais = [i for i in usados if i and cores[i] == cores[0]]
    if iguais:
        print(f"  AVISO: indices {iguais} tem a mesma cor do indice 0 {cores[0]}; "
              "outras ferramentas podem juntar os dois e apagar essas partes")
    w, h = m.size
    if (w, h) == (64, 64):
        print("  formato: front pic / mugshot 64x64")
        bb = m.point(lambda v: 255 if v else 0).getbbox()
        print(f"  boneco ocupa x{bb[0]}-{bb[2]-1} y{bb[1]}-{bb[3]-1}")
    elif h in (32,) and w % 16 == 0:
        fw = 32 if w == 288 else 16 if w == 144 else None
        if fw is None:
            print("  AVISO: largura nao e 144 (9x16) nem 288 (9x32)")
            fw = 16
        print(f"  formato: overworld {w // fw} quadros de {fw}x32")
        mask = m.point(lambda v: 255 if v else 0)
        for i in range(w // fw):
            bb = mask.crop((i * fw, 0, i * fw + fw, 32)).getbbox()
            if not bb:
                print(f"  quadro {i}: VAZIO")
                ok = False
                continue
            print(f"  quadro {i} ({ORDEM_JOGO[i] if i < 9 else '?'}): {bb[2]-bb[0]}x{bb[3]-bb[1]} "
                  f"x{bb[0]}-{bb[2]-1} y{bb[1]}-{bb[3]-1}")
    else:
        print("  AVISO: tamanho nao bate com front pic (64x64) nem overworld (144x32 / 288x32)")
    return 0 if ok else 1


def cmd_rom(a):
    log = a.log
    if log and os.path.exists(log):
        txt = open(log, errors="replace").read()
        for m in re.finditer(r"^\s*(EWRAM|IWRAM|ROM):\s+(\d+) B\s+(\S+ \S+)\s+([\d.]+)%", txt, re.M):
            print(f"{m.group(1):6s} {int(m.group(2)):>10,} B  {m.group(4)}%")
    elf = a.elf
    if not os.path.exists(elf):
        sys.exit(f"{elf} nao existe: rode `make` antes")
    try:
        nm = subprocess.run(["arm-none-eabi-nm", "-S", elf], capture_output=True, text=True, check=True).stdout
    except (FileNotFoundError, subprocess.CalledProcessError):
        sys.exit("arm-none-eabi-nm indisponivel (instale gcc-arm-none-eabi)")
    sym = {}
    for l in nm.splitlines():
        p = l.split()
        if len(p) == 4:
            sym[p[3]] = int(p[1], 16)
    tot = 33554432
    fim = [int(l.split()[0], 16) for l in nm.splitlines() if l.endswith(" __rom_end")]
    if fim:
        usado = fim[0] - 0x08000000
        print(f"ROM usada {usado:,} B de {tot:,} ({usado/tot:.2%}), livre {(tot-usado)/1048576:.2f} MB")

    def soma(pref):
        v = [s for k, s in sym.items() if k.startswith(pref)]
        return len(v), sum(v)

    for nome, pref in [("overworlds (gObjectEventPic_)", "gObjectEventPic_"),
                       ("front pics (gTrainerFrontPic_)", "gTrainerFrontPic_"),
                       ("mugshots (sFieldMugshotGfx_)", "sFieldMugshotGfx_")]:
        n, s = soma(pref)
        if n:
            print(f"{nome:34s} {n:4d} simbolos {s/1024:8.1f} KB  media {s/n:6.0f} B")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)

    p = sub.add_parser("nativo", help="desfaz a ampliacao (2x, 4x...)")
    p.add_argument("entrada"); p.add_argument("saida")
    p.add_argument("--fator", type=int)
    p.set_defaults(f=cmd_nativo)

    p = sub.add_parser("front", help="gera front pic 64x64 de 16 cores")
    p.add_argument("entrada"); p.add_argument("saida")
    p.set_defaults(f=cmd_front)

    p = sub.add_parser("overworld", help="remonta folha em grade na ordem do jogo")
    p.add_argument("entrada"); p.add_argument("saida")
    p.add_argument("--celula", type=int, nargs=2, required=True, metavar=("W", "H"),
                   help="tamanho de cada celula da grade, ja no tamanho nativo")
    p.add_argument("--mapa", required=True,
                   help="9 celulas 'linha,coluna' na ordem do jogo, ex: '0,0 3,0 1,0 0,1 0,3 3,1 3,3 1,1 1,3'")
    p.add_argument("--quadro", type=int, nargs=2, default=(16, 32), metavar=("W", "H"),
                   help="16 32 (padrao) ou 32 32")
    p.add_argument("--fator", type=int, help="forca o fator de ampliacao (padrao: detecta)")
    p.add_argument("--pes-offset", type=int, default=-1,
                   help="linhas acima da ultima onde ficam os pes (padrao -1: linha 30, como a maioria)")
    p.set_defaults(f=cmd_overworld)

    p = sub.add_parser("conferir", help="mede um PNG contra as regras")
    p.add_argument("png")
    p.set_defaults(f=cmd_conferir)

    p = sub.add_parser("rom", help="uso de memoria e custo dos graficos no ultimo build")
    p.add_argument("--elf", default="Soulgold.elf")
    p.add_argument("--log", help="log do make, para ler o bloco 'Memory region'")
    p.set_defaults(f=cmd_rom)

    a = ap.parse_args()
    sys.exit(a.f(a) or 0)


if __name__ == "__main__":
    main()
