import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, 'dev_scripts/sprites')
import experimento as X, propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 8
ALVOS = {'Leon': [(16,21),(18,24)], 'Lusamine': [(16,21),(18,22)], 'Steven': [(16,21),(18,24)], 'Ramos': [(16,22),(18,26)]}
EST = [e for e in X.ESTRATEGIAS if e[0][:2] in ('A ','E ','B2','C2')]
FR = [0,1,2,7]
def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA', (34,34), bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas = []
for nome, alvos in ALVOS.items():
    p = P.preparar(nome); mats = X.mats_de(p['canv']); g = p['grupos']
    nat = [X.to_img(mats[i]) for i in FR]
    linhas.append((f'{nome}  nativo {p["w0"]}x{p["h0"]}', nat))
    for (W,H) in alvos:
        for rot, f in EST:
            frs = f(mats, g, W, H)
            res = X.quant(frs, 16 if W<=16 else 32)
            qfw = 16 if W<=16 else 32
            linhas.append((f'{nome} {W}x{H}  {rot}', [P.quadro_rgba(res, i, qfw) for i in FR]))
cw = 34*z+4
img = Image.new('RGB', (len(FR)*cw+12, len(linhas)*(34*z+22)+10), (40,40,48)); d = ImageDraw.Draw(img)
for k,(rot, frs) in enumerate(linhas):
    y = 10+k*(34*z+22)
    d.text((8,y), rot, fill=(255,220,120))
    for i,fr in enumerate(frs):
        img.paste(cel(fr, z), (8+i*cw, y+14))
img.save(f'{SC}/closeup.png')
# recorta por personagem
n_por = 1+2*len(EST)
for j,nome in enumerate(ALVOS):
    y0 = 10+j*n_por*(34*z+22); y1 = 10+(j+1)*n_por*(34*z+22)
    img.crop((0,y0-4,img.width,y1)).save(f'{SC}/closeup_{nome}.png')
