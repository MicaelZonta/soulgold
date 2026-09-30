import sys, os
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 6; FR = [0, 2, 7]
NOMES = sys.argv[1].split(',')
orig = P.escolher_descartes
def fabrica(bonus):
    def esc(mats, n):
        L = len(mats[0])
        def custo(i):
            c = 0
            for m in mats:
                for x,(p,q) in enumerate(zip(m[i], m[i-1])):
                    if p != q: c += 1
                    if (p[3]>=128) != (q[3]>=128): c += 1
                    if bonus and P.escuro(p):
                        nxt = m[i+1][x] if i+1 < L else (0,0,0,0)
                        if not P.escuro(q) and not P.escuro(nxt): c += bonus
            return c
        keep = set(range(L))
        for k in range(n):
            a = round(k*L/n); b = round((k+1)*L/n)
            cand = [i for i in range(max(a,1), b) if i-1 in keep and i in keep]
            if not cand: continue
            keep.discard(min(cand, key=lambda i: (custo(i), abs(i-(a+b)/2))))
        return sorted(keep)
    return esc
def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA',(34,34),bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas = []
for nome in NOMES:
    p = P.preparar(nome)
    for W in (16, 18):
        g = P.gerar(p, W); Hp = g[0]; He = P.altura_elenco(W, Hp); H = He if He != Hp else Hp
        razao = H / p['h0']
        for rot, b in [('linhas prio +6 (atual)', 6), ('linhas so diff (antigo)', 0), (f'linhas prio 6*razao^2={6*razao*razao:.1f}', 6*razao*razao), ('linhas prio +2', 2)]:
            P.escolher_descartes = fabrica(b)
            res = P.gerar(p, W, H=H)[2]; qfw = 16 if W<=16 else 32
            linhas.append((f'{nome} {W}x{H} (h0 {p["h0"]})  {rot}', [P.quadro_rgba(res,i,qfw) for i in FR]))
cw=34*z+4
img=Image.new('RGB',(len(FR)*cw+12, len(linhas)*(34*z+20)+10),(40,40,48)); dr=ImageDraw.Draw(img)
for k,(rot,frs) in enumerate(linhas):
    y=10+k*(34*z+20); dr.text((8,y),rot,fill=(255,220,120))
    for i,fr in enumerate(frs): img.paste(cel(fr,z),(8+i*cw,y+12))
img.save(f'{SC}/exp7_{NOMES[0]}.png')
