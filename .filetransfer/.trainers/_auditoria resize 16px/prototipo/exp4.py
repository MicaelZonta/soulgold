import sys, os
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 6; FR = [0, 2, 7, 8]
NOMES = sys.argv[1].split(',')
VARS = [('A antigo (uniforme)', 'A'), ('diagonal livre', 0), ('diagonal +60', 60), ('diagonal +150', 150), ('coluna reta', None)]
def reduzir_A(canv, grupos, W, H):
    L,T,R,B = P.uniao(canv)
    mats = [[[q.getpixel((x,y)) for x in range(L,R)] for y in range(T,B)] for q in canv]
    h,w = B-T, R-L
    def esc(ms, n):
        Lr = len(ms[0])
        def diff(i): return sum(sum(1 for p,q in zip(m[i], m[i-1]) if p!=q) for m in ms)
        keep=set(range(Lr))
        for k in range(n):
            a=round(k*Lr/n); b=round((k+1)*Lr/n)
            cand=[i for i in range(max(a,1),b) if i-1 in keep and i in keep]
            if not cand: continue
            keep.discard(min(cand, key=lambda i:(diff(i),abs(i-(a+b)/2))))
        return sorted(keep)
    rows = esc(mats, h-H) if H<h else list(range(h))
    mats = [[m[y] for y in rows] for m in mats]
    res=[]; cs={}
    for g in set(grupos):
        ms=[[list(c) for c in zip(*mats[i])] for i in range(len(mats)) if grupos[i]==g]
        cs[g]=esc(ms, w-W) if W<w else list(range(w))
    for i,m in enumerate(mats):
        im=Image.new('RGBA',(len(cs[grupos[i]]),len(rows)),(0,0,0,0))
        for y,r in enumerate(m):
            for x,cx in enumerate(cs[grupos[i]]): im.putpixel((x,y), r[cx])
        res.append(im)
    return res
def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA',(34,34),bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas=[]
for nome in NOMES:
    p = P.preparar(nome)
    for W in (16, 18):
        g = P.gerar(p, W); Hp = g[0]; He = P.altura_elenco(W, Hp); H = He if He != Hp else Hp
        for rot, d in VARS:
            P.DIAGONAL = d
            if d == 'A':
                fr = reduzir_A(p['canv'], p['grupos'], W, H)
                res = P.G.quantizar(P.pre_quant(P.folha(fr, 16 if W<=16 else 32)), 15)[0]
            else:
                res = P.gerar(p, W, H=H)[2]
            qfw = 16 if W<=16 else 32
            linhas.append((f'{nome} {W}x{H}  {rot}', [P.quadro_rgba(res,i,qfw) for i in FR]))
cw=34*z+4
img=Image.new('RGB',(len(FR)*cw+12, len(linhas)*(34*z+20)+10),(40,40,48)); dr=ImageDraw.Draw(img)
for k,(rot,frs) in enumerate(linhas):
    y=10+k*(34*z+20); dr.text((8,y),rot,fill=(255,220,120))
    for i,fr in enumerate(frs): img.paste(cel(fr,z),(8+i*cw,y+12))
img.save(f'{SC}/exp4_{NOMES[0]}.png')
