import sys, os
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 6; FR = [0, 2, 7]
NOMES = sys.argv[1].split(',')
orig_seam = P.seam_colunas; orig_mask = P.mascara_rosto

def uniforme(mats, n):
    """apaga n colunas em faixas uniformes (custo = diff com a vizinha), como o metodo antigo."""
    ms = [[list(c) for c in zip(*m)] for m in mats]
    L = len(ms[0])
    def diff(i): return sum(sum(1 for p,q in zip(m[i], m[i-1]) if p!=q) for m in ms)
    keep = set(range(L))
    for k in range(n):
        a = round(k*L/n); b = round((k+1)*L/n)
        cand = [i for i in range(max(a,1), b) if i-1 in keep and i in keep]
        if not cand: continue
        keep.discard(min(cand, key=lambda i:(diff(i), abs(i-(a+b)/2))))
    cols = sorted(keep)
    return [[[r[c] for c in cols] for r in m] for m in mats]

def mistura(alpha_fn):
    def sc(mats, n):
        w = len(mats[0][0]); r = (w - n) / w
        a = alpha_fn(r); k = round(n * a)
        mats = uniforme(mats, n - k) if n - k > 0 else mats
        return orig_seam(mats, k) if k > 0 else mats
    return sc

def mask_faixa(m):
    mk = orig_mask(m)
    h, w = len(mk), len(mk[0])
    ys = [y for y in range(h) if any(mk[y])]
    if not ys: return mk
    xs = [x for y in ys for x in range(w) if mk[y][x]]
    y0, y1, x0, x1 = min(ys), max(ys), min(xs), max(xs)
    for y in range(y0, y1+1):
        for x in range(x0, x1+1):
            if m[y][x][3] >= 128: mk[y][x] = True
    return mk

def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA',(34,34),bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas = []
VARS = [('atual', None, None),
        ('A mistura: uniforme + conteudo, alpha=(r-0.45)/0.25', mistura(lambda r: min(1, max(0.25, (r-0.45)/0.25))), None),
        ('A2 mistura alpha=(r-0.4)/0.4', mistura(lambda r: min(1, max(0.0, (r-0.4)/0.4))), None),
        ('B faixa do rosto inteira protegida', None, mask_faixa)]
for nome in NOMES:
    p = P.preparar(nome)
    for W in (16, 18):
        g = P.gerar(p, W); Hp = g[0]; He = P.altura_elenco(W, Hp); H = He if He != Hp else Hp
        for rot, sc, mk in VARS:
            P.seam_colunas = sc or orig_seam; P.mascara_rosto = mk or orig_mask
            res = P.gerar(p, W, H=H)[2]; qfw = 16 if W<=16 else 32
            linhas.append((f'{nome} {W}x{H} (w0 {p["w0"]}, r={W/p["w0"]:.2f})  {rot}', [P.quadro_rgba(res,i,qfw) for i in FR]))
cw=34*z+4
img=Image.new('RGB',(len(FR)*cw+12, len(linhas)*(34*z+20)+10),(40,40,48)); dr=ImageDraw.Draw(img)
for k,(rot,frs) in enumerate(linhas):
    y=10+k*(34*z+20); dr.text((8,y),rot,fill=(255,220,120))
    for i,fr in enumerate(frs): img.paste(cel(fr,z),(8+i*cw,y+12))
img.save(f'{SC}/exp8_{NOMES[0]}.png')
