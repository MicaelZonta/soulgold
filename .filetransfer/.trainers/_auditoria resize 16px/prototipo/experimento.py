"""Compara estrategias de reducao para overworld pequeno (16-18 px)."""
import sys, os, math
sys.path.insert(0, 'dev_scripts/sprites')
import propostas_overworld as P
import sprite_gba as G
from PIL import Image, ImageDraw
SC = os.path.dirname(os.path.abspath(__file__))

def lum(p): return 0.299*p[0]+0.587*p[1]+0.114*p[2]

def mats_de(canv):
    L,T,R,B = P.uniao(canv)
    return [[[q.getpixel((x,y)) for x in range(L,R)] for y in range(T,B)] for q in canv]

def to_img(m):
    im = Image.new('RGBA', (len(m[0]), len(m)), (0,0,0,0))
    for y,r in enumerate(m):
        for x,p in enumerate(r): im.putpixel((x,y), p)
    return im

def T_(m): return [list(c) for c in zip(*m)]

# ---------------- A: atual (drop uniforme, mais parecida com a vizinha)
def A_atual(mats, grupos, W, H):
    return [to_img(m) for m in P.reduzir_mats(mats, grupos, W, H)] if hasattr(P,'reduzir_mats') else None

def reduzir_drop(mats, grupos, W, H, escolher):
    h, w = len(mats[0]), len(mats[0][0])
    rows = escolher(mats, h-H) if H < h else list(range(h))
    mats = [[m[y] for y in rows] for m in mats]
    res = []; colsets = {}
    for g in set(grupos):
        ms = [T_(mats[i]) for i in range(len(mats)) if grupos[i]==g]
        colsets[g] = escolher(ms, w-W) if W < w else list(range(w))
    for i,m in enumerate(mats):
        cols = colsets[grupos[i]]
        res.append(to_img([[r[c] for c in cols] for r in m]))
    return res

# ---------------- E: drop com prioridade (contorno e olhos pesam)
def escuro(p): return p[3] >= 128 and lum(p) < 80
def escolher_prio(mats, n):
    """como o atual, mas o custo de apagar a linha i = pixels que mudam + peso por
    pixel de contorno que so existe nessa linha (linha i escura onde i-1 e i+1 nao sao)."""
    L = len(mats[0])
    def custo(i):
        c = 0
        for m in mats:
            for x,(p,q) in enumerate(zip(m[i], m[i-1])):
                if p != q: c += 1
                if escuro(p):
                    nxt = m[i+1][x] if i+1 < L else (0,0,0,0)
                    if not escuro(q) and not escuro(nxt): c += 6   # traco de 1px que sumiria
                if p[3]>=128 and q[3]<128 or p[3]<128 and q[3]>=128: c += 1
        return c
    keep = set(range(L)); 
    for k in range(n):
        a = round(k*L/n); b = round((k+1)*L/n)
        cand = [i for i in range(max(a,1), b) if i-1 in keep and i in keep]
        if not cand: continue
        i = min(cand, key=lambda i: (custo(i), abs(i-(a+b)/2)))
        keep.discard(i)
    return sorted(keep)

# ---------------- B: seam carving (energia = gradiente + contorno + rosto)
def energia(m, prot=None):
    h, w = len(m), len(m[0])
    E = [[0.0]*w for _ in range(h)]
    for y in range(h):
        for x in range(w):
            p = m[y][x]
            e = 0.0
            for dx,dy in ((1,0),(0,1),(-1,0),(0,-1)):
                xx,yy = x+dx,y+dy
                q = m[yy][xx] if 0<=xx<w and 0<=yy<h else (0,0,0,0)
                if (p[3]>=128) != (q[3]>=128): e += 60
                elif p[3]>=128: e += sum(abs(p[i]-q[i]) for i in range(3))/3
            if escuro(p): e += 120
            if prot is not None and prot[y][x]: e += 300
            E[y][x] = e
    return E

def seam_vertical(Es):
    """menor caminho de cima para baixo somando a energia de todas as matrizes."""
    h, w = len(Es[0]), len(Es[0][0])
    E = [[sum(e[y][x] for e in Es) for x in range(w)] for y in range(h)]
    D = [row[:] for row in E]; back = [[0]*w for _ in range(h)]
    for y in range(1,h):
        for x in range(w):
            best = x; bv = D[y-1][x]
            for dx in (-1,1):
                xx = x+dx
                if 0<=xx<w and D[y-1][xx] < bv: bv = D[y-1][xx]; best = xx
            D[y][x] += bv; back[y][x] = best
    x = min(range(w), key=lambda x: D[h-1][x])
    seam = [0]*h
    for y in range(h-1,-1,-1):
        seam[y] = x; x = back[y][x]
    return seam

def remove_seam(m, seam):
    return [r[:s]+r[s+1:] for r,s in zip(m, seam)]

def seams(mats, n, prots=None):
    mats = [[r[:] for r in m] for m in mats]
    prots = [[r[:] for r in p] for p in prots] if prots else None
    for _ in range(n):
        Es = [energia(m, prots[i] if prots else None) for i,m in enumerate(mats)]
        s = seam_vertical(Es)
        mats = [remove_seam(m, s) for m in mats]
        if prots: prots = [remove_seam(p, s) for p in prots]
    return mats

def B_seam(mats, grupos, W, H, prot=False):
    h, w = len(mats[0]), len(mats[0][0])
    prots = [mascara_rosto(m) for m in mats] if prot else None
    # colunas por grupo (mesmas colunas nos quadros da mesma direcao)
    out = [None]*len(mats)
    for g in set(grupos):
        idx = [i for i in range(len(mats)) if grupos[i]==g]
        ms = seams([mats[i] for i in idx], w-W, [prots[i] for i in idx] if prots else None)
        for i,m in zip(idx, ms): out[i] = m
    # linhas: transpoe, seams em todos os quadros juntos
    tm = [T_(m) for m in out]
    tp = [T_(mascara_rosto(m)) for m in out] if prot else None
    tm = seams(tm, h-H, tp)
    return [to_img(T_(m)) for m in tm]

def mascara_rosto(m):
    """pixels escuros pequenos (olhos/boca) cercados de cor clara na metade de cima: protege."""
    h, w = len(m), len(m[0])
    mk = [[False]*w for _ in range(h)]
    for y in range(1,h-1):
        for x in range(1,w-1):
            p = m[y][x]
            if p[3]<128: continue
            viz = [m[y+dy][x+dx] for dx in (-1,0,1) for dy in (-1,0,1) if (dx or dy)]
            claros = sum(1 for q in viz if q[3]>=128 and lum(q) > 140)
            if lum(p) < 110 and claros >= 5:   # pixel escuro cercado de claro = olho/boca
                for dx in (-1,0,1):
                    for dy in (-1,0,1): mk[y+dy][x+dx] = True
    return mk

# ---------------- C: media de area + encaixe na paleta + contorno reforcado
def paleta_src(mats):
    cnt = {}
    for m in mats:
        for r in m:
            for p in r:
                if p[3]>=128: cnt[p[:3]] = cnt.get(p[:3],0)+1
    return cnt

def snap(c, pal):
    return min(pal, key=lambda q: 2*(c[0]-q[0])**2+4*(c[1]-q[1])**2+3*(c[2]-q[2])**2)

def caixa(m, W, H):
    """para cada pixel alvo: lista de (peso, pixel fonte) pela area coberta."""
    h, w = len(m), len(m[0])
    sx, sy = w/W, h/H
    out = []
    for ty in range(H):
        row = []
        y0, y1 = ty*sy, (ty+1)*sy
        for tx in range(W):
            x0, x1 = tx*sx, (tx+1)*sx
            pesos = []
            for y in range(int(y0), min(h, int(math.ceil(y1)))):
                fy = min(y1, y+1)-max(y0, y)
                for x in range(int(x0), min(w, int(math.ceil(x1)))):
                    fx = min(x1, x+1)-max(x0, x)
                    if fx>0 and fy>0: pesos.append((fx*fy, m[y][x]))
            row.append(pesos)
        out.append(row)
    return out

def C_media(mats, grupos, W, H, contorno=True, modo='media'):
    pal = list(paleta_src(mats))
    escuros = [c for c in pal if lum(c) < 80]
    res = []
    for m in mats:
        cx = caixa(m, W, H)
        im = Image.new('RGBA', (W,H), (0,0,0,0))
        for y in range(H):
            for x in range(W):
                ps = cx[y][x]
                tot = sum(w for w,_ in ps)
                op = [(w,p) for w,p in ps if p[3]>=128]
                cob = sum(w for w,_ in op)
                if cob < tot*0.5: continue
                if modo == 'media':
                    c = tuple(round(sum(w*p[i] for w,p in op)/cob) for i in range(3))
                    c = snap(c, pal)
                else:  # voto ponderado: contorno pesa 2x, pixel escuro pequeno 1.5x
                    v = {}
                    for w,p in op:
                        k = p[:3]; peso = w*(2.0 if lum(p)<80 else 1.0)
                        v[k] = v.get(k,0)+peso
                    c = max(v, key=v.get)
                if contorno and escuros:
                    esc = sum(w for w,p in op if lum(p) < 80)
                    if esc >= cob*0.45: c = snap(tuple(round(sum(w*p[i] for w,p in op if lum(p)<80)/esc) for i in range(3)), escuros)
                im.putpixel((x,y), c+(255,))
        if contorno and escuros:
            im = fechar_contorno(im, escuros)
        res.append(im)
    return res

def fechar_contorno(im, escuros):
    """pixel opaco na borda da silhueta que nao e escuro vira o escuro mais proximo."""
    W,H = im.size; px = im.load(); out = im.copy(); o = out.load()
    for y in range(H):
        for x in range(W):
            p = px[x,y]
            if p[3]<128 or lum(p)<80: continue
            borda = any(not (0<=x+dx<W and 0<=y+dy<H) or px[x+dx,y+dy][3]<128 for dx,dy in ((1,0),(-1,0),(0,1),(0,-1)))
            if borda: o[x,y] = snap(p[:3], escuros)+(255,)
    return out

def D_lanczos(mats, grupos, W, H):
    pal = list(paleta_src(mats))
    res = []
    for m in mats:
        im = to_img(m).resize((W,H), Image.LANCZOS)
        px = im.load()
        for y in range(H):
            for x in range(W):
                p = px[x,y]
                px[x,y] = snap(p[:3], pal)+(255,) if p[3]>=128 else (0,0,0,0)
        res.append(im)
    return res

# ---------------- metricas
def metricas(frs):
    gaps = iso = 0; cores = set()
    for im in frs:
        W,H = im.size; px = im.load()
        for y in range(H):
            for x in range(W):
                p = px[x,y]
                if p[3]<128: continue
                cores.add(p[:3])
                viz = [px[x+dx,y+dy] if 0<=x+dx<W and 0<=y+dy<H else (0,0,0,0) for dx,dy in ((1,0),(-1,0),(0,1),(0,-1))]
                if any(q[3]<128 for q in viz) and lum(p) >= 80: gaps += 1
                if all(q[3]<128 or q[:3]!=p[:3] for q in viz): iso += 1
    return len(cores), gaps, iso

def quant(frs, fw):
    return G.quantizar(P.pre_quant(P.folha(frs, fw)), 15)[0]

ESTRATEGIAS = [
    ('A atual: apaga linha/coluna uniforme', lambda m,g,W,H: reduzir_drop(m,g,W,H,P.escolher_descartes)),
    ('E apaga c/ prioridade contorno+olhos', lambda m,g,W,H: reduzir_drop(m,g,W,H,escolher_prio)),
    ('B seam carving (energia)', lambda m,g,W,H: B_seam(m,g,W,H,False)),
    ('B2 seam carving + rosto protegido', lambda m,g,W,H: B_seam(m,g,W,H,True)),
    ('C media de area + paleta + contorno', lambda m,g,W,H: C_media(m,g,W,H,True,'media')),
    ('C2 voto ponderado + contorno', lambda m,g,W,H: C_media(m,g,W,H,True,'voto')),
    ('D lanczos + paleta (sem contorno)', D_lanczos),
]

def rodar(nome, tamanhos, z=4):
    p = P.preparar(nome)
    mats = mats_de(p['canv']); grupos = p['grupos']
    h0, w0 = len(mats), 0
    h0, w0 = p['h0'], p['w0']
    linhas = []
    print(f'{nome} nativo {w0}x{h0}')
    print(f'{"estrategia":42s} {"alvo":8s} cores gaps isol')
    for (W,H) in tamanhos:
        for rot, f in ESTRATEGIAS:
            frs = f(mats, grupos, W, H)
            c,gp,iso = metricas(frs)
            fw = 16 if W<=16 else 32
            res = quant(frs, fw)
            linhas.append((f'{rot}  {W}x{H}', res, fw, (c,gp,iso)))
            print(f'{rot:42s} {W}x{H:<5} {c:4d} {gp:4d} {iso:4d}')
    # folha
    rs = P.refs(p['c'])
    n = max(r[1].width//r[2] for r in linhas)
    rowh = 32*z+18; xoff = 10+len(rs)*(32*z+8)+16
    img = Image.new('RGB', (xoff+n*32*z+10, 34+rowh*len(linhas)), (40,40,48)); d = ImageDraw.Draw(img)
    d.text((6,8), f'{nome} - nativo {w0}x{h0} - estrategias de reducao (cores antes da paleta / gaps de contorno / pixels isolados)', fill=(230,230,230))
    for k,(rot,res,qfw,(c,gp,iso)) in enumerate(linhas):
        y0 = 34+k*rowh
        for j,(r,fr) in enumerate(rs):
            x = 10+j*(32*z+8); img.paste(P.celula(fr,z,(90,130,72,255)),(x,y0+14))
            if k==0: d.text((x,y0),r,fill=(170,170,170))
        d.text((xoff,y0), f'{rot}   cores {c}  gaps {gp}  isolados {iso}', fill=(255,220,120))
        for i in range(res.width//qfw):
            x = xoff+i*32*z
            img.paste(P.celula(P.quadro_rgba(res,i,qfw),z),(x,y0+14))
            d.rectangle((x,y0+14,x+32*z-1,y0+14+32*z-1),outline=(30,30,30))
    img.save(f'{SC}/{nome}_estrategias.png')

if __name__ == '__main__':
    nome = sys.argv[1]
    tams = [tuple(int(v) for v in t.split('x')) for t in sys.argv[2:]] or [(16,20)]
    rodar(nome, tams)
