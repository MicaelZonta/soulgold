import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); sys.path.insert(0, 'dev_scripts/sprites')
import experimento as X, exp2 as X2, propostas_overworld as P
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))

def H_hibrido(mats, grupos, W, H, linhas='prio'):
    """colunas: seam carving espalhado + rosto protegido, por direcao; linhas: apaga com prioridade."""
    h, w = len(mats[0]), len(mats[0][0])
    prots = [X.mascara_rosto(m) for m in mats]
    out = [None]*len(mats)
    for g in set(grupos):
        idx = [i for i in range(len(mats)) if grupos[i]==g]
        ms = X2.seams_espalhado([mats[i] for i in idx], w-W, [prots[i] for i in idx])
        for i,m in zip(idx, ms): out[i] = m
    esc = X.escolher_prio if linhas=='prio' else P.escolher_descartes
    rows = esc(out, h-H) if H < h else list(range(h))
    return [X.to_img([m[y] for y in rows]) for m in out]

if __name__ == '__main__':
    z = 8; FR = [0,1,2,7]
    def cel(im, z, bg=(120,176,96,255)):
        c = Image.new('RGBA', (34,34), bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
        return c.resize((34*z,34*z), Image.NEAREST)
    linhas = []
    for nome, (W,H) in [('Leon',(16,21)), ('Lusamine',(16,21)), ('Steven',(16,21)), ('Ramos',(16,22))]:
        p = P.preparar(nome); mats = X.mats_de(p['canv']); g = p['grupos']
        if nome == 'Ramos': mats = X2.limpar_jpg(mats)
        for rot, f in [('A atual', lambda m: X.reduzir_drop(m,g,W,H,P.escolher_descartes)),
                       ('H hibrido: seam colunas + prioridade linhas', lambda m: H_hibrido(m,g,W,H)),
                       ('B3 seam nos dois eixos', lambda m: X2.B3(m,g,W,H,True))]:
            frs = f(mats); res = X.quant(frs, 16); c,gp,iso = X.metricas(frs)
            linhas.append((f'{nome} {W}x{H}  {rot}   cores {c} gaps {gp}', [P.quadro_rgba(res,i,16) for i in FR]))
    cw = 34*z+4
    img = Image.new('RGB', (len(FR)*cw+12, len(linhas)*(34*z+22)+10), (40,40,48)); d = ImageDraw.Draw(img)
    for k,(rot, frs) in enumerate(linhas):
        y = 10+k*(34*z+22); d.text((8,y), rot, fill=(255,220,120))
        for i,fr in enumerate(frs): img.paste(cel(fr,z), (8+i*cw, y+14))
    img.save(f'{SC}/exp3.png')
