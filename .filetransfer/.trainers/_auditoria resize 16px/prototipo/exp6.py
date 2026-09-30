import sys, os
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P, sprite_gba as G
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))
z = 6; FR = [0, 2, 7]
modo = sys.argv[1]; NOMES = sys.argv[2].split(',')

def limpar_suave(canv, n):
    """so median cut para n cores (sem fusao gulosa); a fusao final a 15 fica para depois de reduzir."""
    w, h = canv[0].size
    sheet = Image.new('RGBA', (w*len(canv), h), (0,0,0,0))
    for i,q in enumerate(canv): sheet.paste(q, (i*w, 0))
    q = P.pre_quant(sheet, n)
    return [q.crop((i*w, 0, i*w+w, h)) for i in range(len(canv))]

def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA',(34,34),bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas = []
orig_energia = P.energia; orig_limpar = P.limpar_jpg
for nome in NOMES:
    c = P.CHARS[nome]
    if modo == 'jpg':
        VARS = [('limpo 15 (atual)', lambda cv: orig_limpar(cv, 15)), ('median cut 32', lambda cv: limpar_suave(cv, 32)),
                ('median cut 24', lambda cv: limpar_suave(cv, 24)), ('sem limpar (antes)', lambda cv: cv)]
        for rot, f in VARS:
            P.limpar_jpg = f
            p = P.preparar(nome)
            for W in (16, 18):
                g = P.gerar(p, W); Hp = g[0]; He = P.altura_elenco(W, Hp); H = He if He != Hp else Hp
                res = P.gerar(p, W, H=H)[2]; qfw = 16 if W<=16 else 32
                linhas.append((f'{nome} {W}x{H}  {rot}', [P.quadro_rgba(res,i,qfw) for i in FR]))
    else:
        p = P.preparar(nome)
        for W in (16, 18):
            g = P.gerar(p, W); Hp = g[0]; He = P.altura_elenco(W, Hp); H = He if He != Hp else Hp
            razao = W / p['w0']
            for rot, peso in [('rosto +300 (atual)', 300), ('rosto +100', 100), ('rosto 0', 0), (f'rosto 300*razao^2={300*razao*razao:.0f}', 300*razao*razao)]:
                def en(m, prot, peso=peso):
                    E = orig_energia(m, prot)
                    if peso != 300:
                        for y in range(len(E)):
                            for x in range(len(E[0])):
                                if prot[y][x]: E[y][x] += peso - 300
                    return E
                P.energia = en
                res = P.gerar(p, W, H=H)[2]; qfw = 16 if W<=16 else 32
                linhas.append((f'{nome} {W}x{H}  {rot}', [P.quadro_rgba(res,i,qfw) for i in FR]))
        P.energia = orig_energia
cw=34*z+4
img=Image.new('RGB',(len(FR)*cw+12, len(linhas)*(34*z+20)+10),(40,40,48)); dr=ImageDraw.Draw(img)
for k,(rot,frs) in enumerate(linhas):
    y=10+k*(34*z+20); dr.text((8,y),rot,fill=(255,220,120))
    for i,fr in enumerate(frs): img.paste(cel(fr,z),(8+i*cw,y+12))
img.save(f'{SC}/exp6_{modo}_{NOMES[0]}.png')
