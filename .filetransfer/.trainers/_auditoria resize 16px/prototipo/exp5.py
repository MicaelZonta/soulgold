import sys, os
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 6; FR = [0, 2, 7, 8]
NOMES = sys.argv[1].split(',')
orig = P.seam_colunas
VARS = [('reta pen150 r2 (atual)', 150, 2, 0.85), ('reta pen400 r3', 400, 3, 0.85), ('reta pen800 r3', 800, 3, 0.9), ('reta pen400 r4 sem decair', 400, 4, 1.0)]
def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA',(34,34),bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas=[]
P.DIAGONAL = None
for nome in NOMES:
    p = P.preparar(nome)
    for W in (16, 18):
        g = P.gerar(p, W); Hp = g[0]; He = P.altura_elenco(W, Hp); H = He if He != Hp else Hp
        for rot, pen, raio, dec in VARS:
            def sc(mats, n, pen=pen, raio=raio, dec=dec):
                mats = [[r[:] for r in m] for m in mats]
                prots = [P.mascara_rosto(m) for m in mats]
                h = len(mats[0]); extra = [[0.0]*len(mats[0][0]) for _ in range(h)]
                for _ in range(n):
                    Es = [P.energia(m, prots[i]) for i,m in enumerate(mats)] + [extra]
                    s = P.costura(Es)
                    mats = [P.tirar_costura(m, s) for m in mats]; prots = [P.tirar_costura(q, s) for q in prots]; extra = P.tirar_costura(extra, s)
                    w = len(extra[0])
                    for y in range(h):
                        for d in range(-raio, raio+1):
                            x = s[y]+d
                            if 0 <= x < w: extra[y][x] += pen*(raio+1-abs(d))/(raio+1)
                        for x in range(w): extra[y][x] *= dec
                return mats
            P.seam_colunas = sc
            res = P.gerar(p, W, H=H)[2]
            qfw = 16 if W<=16 else 32
            linhas.append((f'{nome} {W}x{H}  {rot}', [P.quadro_rgba(res,i,qfw) for i in FR]))
cw=34*z+4
img=Image.new('RGB',(len(FR)*cw+12, len(linhas)*(34*z+20)+10),(40,40,48)); dr=ImageDraw.Draw(img)
for k,(rot,frs) in enumerate(linhas):
    y=10+k*(34*z+20); dr.text((8,y),rot,fill=(255,220,120))
    for i,fr in enumerate(frs): img.paste(cel(fr,z),(8+i*cw,y+12))
img.save(f'{SC}/exp5_{NOMES[0]}.png')
