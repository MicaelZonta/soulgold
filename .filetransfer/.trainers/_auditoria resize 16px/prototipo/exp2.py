import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__))); sys.path.insert(0, 'dev_scripts/sprites')
import experimento as X, propostas_overworld as P, sprite_gba as G
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))

def seams_espalhado(mats, n, prots=None, pen=150, raio=2):
    """seam carving com penalidade nas colunas vizinhas da ultima costura removida."""
    mats = [[r[:] for r in m] for m in mats]
    prots = [[r[:] for r in p] for p in prots] if prots else None
    h = len(mats[0]); extra = [[0.0]*len(mats[0][0]) for _ in range(h)]
    for _ in range(n):
        Es = [X.energia(m, prots[i] if prots else None) for i,m in enumerate(mats)]
        Es.append(extra)
        s = X.seam_vertical(Es)
        mats = [X.remove_seam(m, s) for m in mats]
        if prots: prots = [X.remove_seam(p, s) for p in prots]
        extra = X.remove_seam(extra, s)
        w = len(extra[0])
        for y in range(h):
            for d in range(-raio, raio+1):
                x = s[y]+d
                if 0 <= x < w: extra[y][x] += pen*(raio+1-abs(d))/(raio+1)
            for x in range(w): extra[y][x] *= 0.85   # decai com o tempo
    return mats

def B3(mats, grupos, W, H, prot=True):
    h, w = len(mats[0]), len(mats[0][0])
    prots = [X.mascara_rosto(m) for m in mats] if prot else None
    out = [None]*len(mats)
    for g in set(grupos):
        idx = [i for i in range(len(mats)) if grupos[i]==g]
        ms = seams_espalhado([mats[i] for i in idx], w-W, [prots[i] for i in idx] if prots else None)
        for i,m in zip(idx, ms): out[i] = m
    tm = [X.T_(m) for m in out]; tp = [X.T_(X.mascara_rosto(m)) for m in out] if prot else None
    tm = seams_espalhado(tm, h-H, tp)
    return [X.to_img(X.T_(m)) for m in tm]

def limpar_jpg(mats, n=15):
    """quantiza a fonte (todos os quadros juntos) para n cores ANTES de reduzir."""
    h, w = len(mats[0]), len(mats[0][0])
    sheet = Image.new('RGBA', (w*len(mats), h), (0,0,0,0))
    for i,m in enumerate(mats): sheet.paste(X.to_img(m), (i*w, 0))
    q, _ = G.quantizar(P.pre_quant(sheet, 40), n)
    rgba = q.convert('RGBA'); px = rgba.load()
    for y in range(h):
        for x in range(w*len(mats)):
            if q.getpixel((x,y)) == 0: px[x,y] = (0,0,0,0)
    return [[[rgba.getpixel((i*w+x, y)) for x in range(w)] for y in range(h)] for i in range(len(mats))]

z = 8; FR = [0,1,2,7]
def cel(im, z, bg=(120,176,96,255)):
    c = Image.new('RGBA', (34,34), bg); c.paste(im, ((34-im.width)//2, 33-im.height), im)
    return c.resize((34*z,34*z), Image.NEAREST)
linhas = []
for nome, (W,H) in [('Ramos',(16,22)), ('Lusamine',(16,21)), ('Leon',(16,21))]:
    p = P.preparar(nome); mats = X.mats_de(p['canv']); g = p['grupos']
    variantes = [('B2 seam + rosto', mats, lambda m: X.B_seam(m,g,W,H,True)),
                 ('B3 seam + rosto + espalhado', mats, lambda m: B3(m,g,W,H,True))]
    if nome == 'Ramos':
        lim = limpar_jpg(mats)
        variantes += [('JPG limpo 15 cores + A atual', lim, lambda m: X.reduzir_drop(m,g,W,H,P.escolher_descartes)),
                      ('JPG limpo 15 cores + E prioridade', lim, lambda m: X.reduzir_drop(m,g,W,H,X.escolher_prio)),
                      ('JPG limpo 15 cores + B3', lim, lambda m: B3(m,g,W,H,True))]
    for rot, src, f in variantes:
        frs = f(src); res = X.quant(frs, 16)
        c,gp,iso = X.metricas(frs)
        linhas.append((f'{nome} {W}x{H}  {rot}   cores {c} gaps {gp}', [P.quadro_rgba(res,i,16) for i in FR]))
        print(rot, c, gp, iso)
cw = 34*z+4
img = Image.new('RGB', (len(FR)*cw+12, len(linhas)*(34*z+22)+10), (40,40,48)); d = ImageDraw.Draw(img)
for k,(rot, frs) in enumerate(linhas):
    y = 10+k*(34*z+22); d.text((8,y), rot, fill=(255,220,120))
    for i,fr in enumerate(frs): img.paste(cel(fr,z), (8+i*cw, y+14))
img.save(f'{SC}/exp2.png')
