"""Converte arte de treinador para front pic grande (80x80).

Uso (precisa de PIL; no WSL use o Python do Windows):
    python trainer_pic_large.py <arte.png> <saida_large.png> [opcoes]

Opcoes:
    --bg R,G,B          cor de fundo (padrao: a cor mais comum da arte)
    --crop x0,y0,x1,y1  recorta a arte antes (moldura, folha com varios desenhos)
    --grid N            arte "pixel art ampliada": recupera a versao nativa pela
                        mediana do miolo de cada bloco NxN (N pode ser fracionario)
    --merge             passa de 15 cores? funde a cor de menor custo
                        (pixels x distancia) na vizinha mais proxima, ate 15
    --palette ref.png   modo REDUCAO: figura maior que 80x80 e reduzida para
                        caber, por voto de area com preferencia ao contorno,
                        usando a paleta (feita a mao) de ref.png

Sem --palette a figura e colada 1:1, sem redimensionar; maior que 80x80 e erro.
Ancoragem igual a do jogo: o quadro comeca em y=8 na tela, como os 64x64.
Figura de ate 64 px de altura fica com os pes na linha 63 (mesmo chao dos
64x64); figura mais alta desce, ate a linha 79. Assim a cabeca nunca corta.
"""
import sys
from collections import Counter
from PIL import Image

SIZE = 80
NORMAL_FEET_ROW = 63


def opt(name):
    if name in sys.argv:
        return sys.argv[sys.argv.index(name) + 1]
    return None


def dist(a, b):
    return sum((x - y) ** 2 for x, y in zip(a[:3], b[:3])) ** 0.5


def recover_grid(im, n):
    """Mediana do miolo de cada bloco n x n (ignora a borda anti-aliasada)."""
    w, h = round(im.width / n), round(im.height / n)
    out = Image.new('RGBA', (w, h))
    for by in range(h):
        for bx in range(w):
            x0, y0 = int(bx * n + n * 0.25), int(by * n + n * 0.25)
            x1, y1 = max(x0 + 1, int(bx * n + n * 0.75)), max(y0 + 1, int(by * n + n * 0.75))
            c = Counter(im.getpixel((x, y)) for y in range(y0, min(y1, im.height))
                        for x in range(x0, min(x1, im.width)))
            out.putpixel((bx, by), c.most_common(1)[0][0])
    return out


def main():
    args = [a for i, a in enumerate(sys.argv[1:], 1)
            if not a.startswith('--') and not sys.argv[i - 1] in ('--bg', '--crop', '--grid', '--palette')]
    src, out = args
    im = Image.open(src).convert('RGBA')
    if opt('--crop'):
        im = im.crop(tuple(int(v) for v in opt('--crop').split(',')))
    if opt('--grid'):
        im = recover_grid(im, float(opt('--grid')))
    if opt('--bg'):
        bg = tuple(int(c) for c in opt('--bg').split(',')) + (255,)
    else:
        bg = Counter(im.get_flattened_data()).most_common(1)[0][0]

    def is_bg(p):
        return p[3] < 128 or p[:3] == bg[:3]

    mask = Image.new('L', im.size)
    mask.putdata([0 if is_bg(p) else 255 for p in im.get_flattened_data()])
    fig = im.crop(mask.getbbox())

    if opt('--palette'):
        fig, palette = reduce_to_palette(fig, is_bg, opt('--palette'))
    else:
        fig, palette = keep_colors(fig, is_bg, bg)

    w, h = fig.size
    if w > SIZE or h > SIZE:
        sys.exit(f'figura {w}x{h} passa de {SIZE}x{SIZE}: use --crop, --grid ou --palette')

    bottom = max(NORMAL_FEET_ROW, h - 1)
    x0, y0 = (SIZE - w) // 2, bottom - h + 1
    out_im = Image.new('P', (SIZE, SIZE), 0)
    out_im.putpalette([v for c in palette for v in c])
    for y in range(h):
        for x in range(w):
            i = fig.getpixel((x, y))
            if i:
                out_im.putpixel((x0 + x, y0 + y), i)
    out_im.save(out, bits=4)
    print(f'{out}: figura {w}x{h}, {sum(1 for c in palette[1:] if c != (0, 0, 0))} cores, linhas {y0}-{bottom}')


def keep_colors(fig, is_bg, bg):
    """Copia 1:1; devolve imagem de indices e paleta (indice 0 = fundo)."""
    counts = Counter(p[:3] for p in fig.get_flattened_data() if not is_bg(p))
    remap = {c: c for c in counts}
    if len(counts) > 15:
        if '--merge' not in sys.argv:
            sys.exit(f'{len(counts)} cores (maximo 15 + transparencia); use --merge ou escolha a paleta a mao')
        while len(counts) > 15:
            c = min(counts, key=lambda c: counts[c] * min(dist(c, o) for o in counts if o != c))
            into = min((o for o in counts if o != c), key=lambda o: dist(c, o))
            print(f'  funde {c} ({counts[c]} px) em {into}')
            counts[into] += counts.pop(c)
            for k, v in remap.items():
                if v == c:
                    remap[k] = into
    colors = sorted(counts, key=lambda c: -counts[c])
    palette = [bg[:3]] + colors + [(0, 0, 0)] * (15 - len(colors))
    index = {k: palette.index(v) for k, v in remap.items()}
    idx = Image.new('L', fig.size)
    idx.putdata([0 if is_bg(p) else index[p[:3]] for p in fig.get_flattened_data()])
    return idx, palette


def reduce_to_palette(fig, is_bg, ref_path):
    """Reduz para caber em 80x80: voto de area sobre a paleta de ref.png.

    Cada pixel de saida olha o bloco de origem; fundo so vence com maioria;
    o contorno (cor mais escura) vence com 1/4 do bloco, para nao sumir."""
    ref = Image.open(ref_path)
    pal = ref.getpalette()[:48]
    palette = [tuple(pal[i:i + 3]) for i in range(0, 48, 3)]
    outline = min(range(1, 16), key=lambda i: sum(palette[i]))
    scale = min(SIZE / fig.width, SIZE / fig.height)
    w, h = max(1, round(fig.width * scale)), max(1, round(fig.height * scale))
    near = {}

    def nearest(p):
        if p[:3] not in near:
            near[p[:3]] = min(range(1, 16), key=lambda i: dist(p, palette[i]))
        return near[p[:3]]

    idx = Image.new('L', (w, h))
    for y in range(h):
        for x in range(w):
            sx0, sx1 = int(x / scale), max(int(x / scale) + 1, int((x + 1) / scale))
            sy0, sy1 = int(y / scale), max(int(y / scale) + 1, int((y + 1) / scale))
            votes = Counter()
            for sy in range(sy0, min(sy1, fig.height)):
                for sx in range(sx0, min(sx1, fig.width)):
                    p = fig.getpixel((sx, sy))
                    votes[0 if is_bg(p) else nearest(p)] += 1
            total = sum(votes.values())
            if votes[0] * 2 > total:
                continue
            del votes[0]
            if votes[outline] * 4 >= total:
                idx.putpixel((x, y), outline)
            else:
                idx.putpixel((x, y), votes.most_common(1)[0][0])
    return idx, palette


if __name__ == '__main__':
    main()
