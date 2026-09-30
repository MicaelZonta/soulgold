import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); sys.path.insert(0, 'dev_scripts/sprites')
import experimento as X, exp2 as X2, exp3 as X3, propostas_overworld as P
from PIL import Image, ImageDraw
OUT = sys.argv[1]; z = 5
ALVOS = {'Leon': [(16,21),(18,24)], 'Lusamine': [(16,21),(18,22)], 'Steven': [(16,21),(18,24)], 'Ramos': [(16,22),(18,26)]}
tab = []
for nome, alvos in ALVOS.items():
    p = P.preparar(nome); mats = X.mats_de(p['canv']); g = p['grupos']
    jpg = p['c'].get('jpg')
    if jpg: mats = X2.limpar_jpg(mats)
    linhas = [(f'nativo {p["w0"]}x{p["h0"]}' + ('  (JPG limpo para 15 cores antes de reduzir)' if jpg else ''), [X.to_img(m) for m in mats], None)]
    for (W,H) in alvos:
        qfw = 16 if W<=16 else 32
        for rot, f in [('ATUAL: apaga linha/coluna uniforme', lambda m: X.reduzir_drop(m,g,W,H,P.escolher_descartes)),
                       ('PROPOSTO: seam carving nas colunas (rosto protegido) + apaga linhas com prioridade de contorno', lambda m: X3.H_hibrido(m,g,W,H))]:
            frs = f(mats); res = X.quant(frs, qfw); c,gp,iso = X.metricas(frs)
            tab.append((nome, W, H, rot[:8], c, gp))
            linhas.append((f'{W}x{H} (quadro {qfw}x32)  {rot}   [gaps de contorno {gp}]', [P.quadro_rgba(res,i,qfw) for i in range(res.width//qfw)], (W,H)))
    rs = P.refs(p['c'])
    n = max(len(l[1]) for l in linhas)
    xoff = 10+len(rs)*(32*z+8)+16; rowh = 32*z+18
    img = Image.new('RGB', (xoff+n*32*z+10, 34+rowh*len(linhas)), (40,40,48)); d = ImageDraw.Draw(img)
    d.text((6,8), f'{nome} - arte: {p["c"]["cred"]} - ampliado {z}x - reducao atual x proposta', fill=(230,230,230))
    for k,(rot, frs, _) in enumerate(linhas):
        y0 = 34+k*rowh
        for j,(r,fr) in enumerate(rs):
            x = 10+j*(32*z+8); img.paste(P.celula(fr,z,(90,130,72,255)),(x,y0+14))
            if k==0: d.text((x,y0),r,fill=(170,170,170))
        d.text((xoff,y0), rot, fill=(120,255,140) if 'PROPOSTO' in rot else (255,220,120))
        for i,fr in enumerate(frs):
            x = xoff+i*32*z
            cell = Image.new('RGBA',(32,32),(120,176,96,255)); cell.paste(fr, ((32-fr.width)//2, 31-fr.height if k==0 else 0), fr)
            img.paste(cell.resize((32*z,32*z),Image.NEAREST),(x,y0+14)); d.rectangle((x,y0+14,x+32*z-1,y0+14+32*z-1),outline=(30,30,30))
    img.save(os.path.join(OUT, f'{nome} - atual x proposto.png'))
print(f'{"nome":10s} alvo   metodo   cores gaps')
for t in tab: print(f'{t[0]:10s} {t[1]}x{t[2]:<3} {t[3]:8s} {t[4]:4d} {t[5]:4d}')
