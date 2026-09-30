import sys, os
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 10; NOMES = sys.argv[1].split(',')
def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA',(20,24),bg); c.paste(im, ((20-im.width)//2, 23-im.height), im)
    return c.resize((20*z,24*z), Image.NEAREST)
linhas=[]
for nome in NOMES:
    p = P.preparar(nome)
    g = P.gerar(p, 16); Hp = g[0]; He = P.altura_elenco(16, Hp); H = He if He != Hp else Hp
    res = P.gerar(p, 16, H=H)[2]
    fr = [P.quadro_rgba(res, i, 16) for i in (0, 1, 3)]
    ol = P.olhos([[fr[0].getpixel((x,y)) for x in range(16)] for y in range(32)])
    linhas.append((f'{nome} 16x{H}  olhos: ' + ', '.join(f'{len({x for x,_ in g})}x{len({y for _,y in g})}' for g in ol), [f.crop((0,8,16,32)) for f in fr]))
img = Image.new('RGB', (3*(20*z+6)+10, len(linhas)*(24*z+22)+10), (40,40,48)); d = ImageDraw.Draw(img)
for k,(rot,frs) in enumerate(linhas):
    y = 10+k*(24*z+22); d.text((8,y), rot, fill=(255,220,120))
    for i,f in enumerate(frs): img.paste(cel(f,z), (8+i*(20*z+6), y+14))
img.save(f'{SC}/olhos16.png')
