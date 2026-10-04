# Cenouras do Rei: 3 propostas de arte (folhas no canteiro da Laurel (23,38), ícones 24x24, descrições).
# Página: https://claude.ai/artifact/KvYi8zKVNGyVgGv5UgjByH — o autor escolheu a C (A noite revela), 03/10/2026.
# python3 .claude/berry_master/prototipo_corceis/cenouras_do_rei.py <saida> [--instalar C]
#   --instalar C grava os ícones (graphics/items/icons + icon_palettes) e as duas folhas de
#   overworld do canteiro (graphics/object_events/pics/people/special/kings_carrot_*.png):
#   9 quadros 16x32, 0 = marca (plantada), 1 = folhas fechadas (pronta, de dia),
#   2 = folhas acesas (pronta, de noite); o quadro sai da direção (baixo/cima/esquerda).
import sys, os, math, json
ROOT = '/home/ADMIN/decomps/soulgold_v1'
sys.path.insert(0, os.path.join(ROOT, '.claude/skills/prototipo-de-mapa'))
from mapa_kit import *

ARGS = [a for a in sys.argv[1:] if not a.startswith('--')]
INSTALAR = sys.argv[sys.argv.index('--instalar') + 1] if '--instalar' in sys.argv else None
OUT = ARGS[0] if ARGS and ARGS[0] != INSTALAR else os.path.join(os.path.dirname(os.path.abspath(__file__)), 'cenouras_do_rei')
os.makedirs(OUT, exist_ok=True)
PX, PY = 23, 38                        # o canteiro
CX0, CY0, CX1, CY1 = 20, 35, 27, 40    # recorte do mapa
OUTLINE = (48, 48, 48)

# ------------------------------------------------------------------ cores
ICE = dict(  # Iceroot: raiz branca-azulada, rama verde-gelo com ponta de geada
    root=[(96, 128, 176), (144, 184, 224), (192, 224, 248), (232, 248, 255)],
    leaf=[(48, 112, 104), (88, 160, 144), (152, 208, 192), (224, 248, 248)],
    fx=[(255, 255, 255), (176, 224, 255)])
SHADE = dict(  # Shaderoot: raiz roxa-quase-preta, rama violeta escura com brilho lilás
    root=[(40, 24, 64), (72, 48, 112), (112, 80, 160), (168, 136, 208)],
    leaf=[(64, 52, 96), (100, 80, 144), (140, 112, 192), (208, 184, 248)],
    fx=[(232, 208, 255), (144, 104, 224)])

class G:
    def __init__(s, w, h): s.w, s.h = w, h; s.p = [[None] * w for _ in range(h)]
    def put(s, x, y, c):
        x, y = int(round(x)), int(round(y))
        if 0 <= x < s.w and 0 <= y < s.h: s.p[y][x] = c
    def get(s, x, y): return s.p[y][x] if 0 <= x < s.w and 0 <= y < s.h else None
    def outline(s, col=OUTLINE):
        add = []
        for y in range(s.h):
            for x in range(s.w):
                if s.p[y][x] is None and any(s.get(x + dx, y + dy) not in (None, col) for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
                    add.append((x, y))
        for x, y in add: s.p[y][x] = col

def root(g, tip, sh, wmax, R, grooves=True):
    """Raiz cônica da ponta `tip` ao ombro `sh`; luz de cima à esquerda."""
    (tx, ty), (sx, sy) = tip, sh
    L = math.hypot(sx - tx, sy - ty); ux, uy = (sx - tx) / L, (sy - ty) / L; nx, ny = -uy, ux
    for y in range(g.h):
        for x in range(g.w):
            px, py = x - tx, y - ty
            t = px * ux + py * uy; d = px * nx + py * ny
            if t < -0.5 or t > L + 1.2: continue
            w = wmax * min(1.0, max(0.0, t / L) ** 0.8) if t <= L else wmax * math.sqrt(max(0, 1 - ((t - L) / 1.4) ** 2))
            if abs(d) > w + 0.15 or w < 0.35: continue
            r = d / max(w, 0.5)                       # -1 .. 1 de um lado ao outro
            side = r * (-1 if nx + ny < 0 else 1)     # >0 = lado da luz
            k = 3 if side > 0.45 else 2 if side > -0.1 else 1 if side > -0.6 else 0
            if grooves and int(t) % 4 == 2 and 0.2 < t / L < 0.92 and k > 0: k -= 1
            g.put(x, y, R[k])

def frond(g, x0, y0, ang, n, Lc, w=1, curl=7):
    """Folha: talo curvo de n px e folíolos."""
    x, y = x0, y0
    for i in range(n):
        a = math.radians(ang + i * curl)
        x += math.cos(a); y -= math.sin(a)
        g.put(x, y, Lc[1])
        if w and i > 1 and i % 2 == 0:
            sgn = 1 if (i // 2) % 2 else -1
            g.put(x + math.cos(a + 1.6 * sgn), y - math.sin(a + 1.6 * sgn), Lc[2] if sgn > 0 else Lc[0])
    g.put(x, y, Lc[3])
    return x, y

def to_rgb(g, bg=None):
    return [[c if c else bg for c in r] for r in g.p]

# ------------------------------------------------------------------ ícones 24x24
def icon(P, style):
    g = G(24, 24)
    if style == 'C':                                   # torrão de terra na ponta, cenoura recém-arrancada
        root(g, (4, 22), (12, 12), 4.2, P['root'])
        for (x, y) in ((2, 19), (3, 20), (4, 22), (5, 21), (3, 22), (6, 22), (2, 21), (5, 23)):
            g.put(x, y, (120, 88, 56) if (x + y) % 2 else (88, 64, 40))
    else:
        root(g, (3, 22), (12, 12), 4.6, P['root'])
    for ang, n in ((118, 8), (80, 10), (45, 10), (8, 8)):
        ex, ey = frond(g, 13, 10, ang, n, P['leaf'])
    if style == 'B':                                   # aura: cristais (Iceroot) ou fiapos (Shaderoot)
        fx = P['fx']
        for (x, y) in ((2, 13), (1, 12), (3, 12), (2, 11), (6, 6), (7, 7), (5, 7), (6, 8), (19, 18), (20, 19), (18, 19)):
            g.put(x, y, fx[(x + y) % 2])
    g.outline()
    if style in ('A', 'C'):                            # brilho no ombro
        g.put(10, 13, P['fx'][0]); g.put(8, 15, P['fx'][0])
    return g

# ------------------------------------------------------------------ canteiro
def plot_art(P, style, stage, night):
    """Arte 16x32 (a célula do canteiro é a de baixo). stage: 'plantada' | 'pronta'."""
    g = G(16, 32)
    L = P['leaf']
    if style == 'A':                                   # metatile: brotos / rama baixa dentro da célula
        if stage == 'plantada':
            pass                                       # "The soil is keeping its secret."
        else:
            for x0, a, n in ((7, 66, 7), (8, 112, 7), (6, 140, 5), (9, 38, 5), (8, 90, 8)): frond(g, x0, 28, a, n, L, curl=1)
            for x in range(6, 11): g.put(x, 28, P['root'][2])          # ombro da cenoura
            g.put(7, 28, P['root'][3]); g.put(10, 28, P['root'][1])
    elif style == 'B':                                 # objeto 16x32: rama alta que passa da célula
        if stage == 'plantada':
            pass
        else:
            for x0, a, n in ((7, 76, 13), (9, 104, 13), (6, 128, 9), (10, 52, 9), (8, 90, 16)): frond(g, x0, 25, a, n, L, curl=1)
            for y in (26, 27, 28):
                for x in range(5, 12): g.put(x, y, P['root'][2 if x < 9 else 1])
            g.put(6, 26, P['root'][3]); g.put(7, 26, P['root'][3])
    elif style == 'C':                                 # de dia só a marca no chão; de noite a rama acesa
        if not (stage == 'pronta' and night):
            mark = P['fx'][1] if P is ICE else P['root'][0]
            for (x, y) in ((5, 24), (8, 23), (11, 25), (4, 27), (12, 28), (7, 29), (10, 30), (6, 26), (9, 26)):
                g.put(x, y, mark)
            if stage == 'pronta':                      # folhas fechadas, esperando o escuro
                for x0, a, n in ((7, 80, 4), (9, 100, 4), (8, 90, 5)): frond(g, x0, 28, a, n, [P['leaf'][0], P['leaf'][1], P['leaf'][1], P['leaf'][2]], w=0, curl=1)
        else:
            for x0, a, n in ((7, 66, 8), (8, 112, 8), (6, 140, 6), (9, 38, 6), (8, 90, 10)): frond(g, x0, 28, a, n, [P['leaf'][2], P['leaf'][3], P['fx'][0], P['fx'][0]], curl=1)
            for (x, y) in ((3, 17), (13, 15), (2, 24), (14, 22), (8, 13)): g.put(x, y, P['fx'][1])
    if style != 'C' or (stage == 'pronta' and night):
        dk = tuple(int(v * 0.55) for v in P['leaf'][0])
        g.outline(dk if style != 'C' else P['fx'][1])
    return g

# ------------------------------------------------------------------ cena
L0 = load_layout('Route30'); W = L0['w']
def scene(night):
    cv = render_repo_map('Route30', objects=[], night=1.0 if night else 0.0)
    return [row[:] for row in cv]
DAY, NIGHT = scene(False), scene(True)
def composite(P, style, stage, night):
    cv = [row[:] for row in (NIGHT if night else DAY)]
    art = plot_art(P, style, stage, night)
    pix = [[c for c in r] for r in art.p]
    if night:
        flat = [[c if c else (0, 0, 0) for c in r] for r in pix]
        dim = apply_night_tint(flat, 1.0) if not (style == 'C') else apply_night_tint(flat, 0.35)
        pix = [[dim[y][x] if pix[y][x] else None for x in range(16)] for y in range(32)]
    ox, oy = PX * 16, (PY - 1) * 16
    for y in range(32):
        for x in range(16):
            if pix[y][x]: cv[oy + y][ox + x] = pix[y][x]
    return crop(cv, CX0 * 16, CY0 * 16, CX1 * 16, CY1 * 16)

for style in 'ABC':
    for nome, P in (('ice', ICE), ('shade', SHADE)):
        write_png(os.path.join(OUT, '%s_icon_%s.png' % (style, nome)), to_rgb(icon(P, style), (0, 0, 0, )) if False else
                  [[c if c else (236, 232, 222) for c in r] for r in icon(P, style).p], 6)
        write_png(os.path.join(OUT, '%s_icon_%s_1x.png' % (style, nome)), [[c if c else (236, 232, 222) for c in r] for r in icon(P, style).p], 2)
        for stage in ('plantada', 'pronta'):
            for night in (False, True):
                if stage == 'plantada' and night: continue
                write_png(os.path.join(OUT, '%s_%s_%s_%s.png' % (style, nome, stage, 'noite' if night else 'dia')),
                          composite(P, style, stage, night), 3)
# cores por ícone (cabe em 16?)
rep = {}
for style in 'ABC':
    for nome, P in (('ice', ICE), ('shade', SHADE)):
        cols = {c for r in icon(P, style).p for c in r if c}
        rep['%s_%s' % (style, nome)] = len(cols)
json.dump(rep, open(os.path.join(OUT, 'cores.json'), 'w'))
print(rep)

# ------------------------------------------------------------------ instalar
def indexed(rows, pal):
    """rows de RGB/None -> índices na paleta (0 = transparente)."""
    return [[0 if c is None else 1 + pal.index(c) for c in r] for r in rows]

def write_jasc(path, cols):
    with open(path, 'w', newline='\r\n') as f:
        f.write('JASC-PAL\n0100\n16\n' + ''.join('%d %d %d\n' % tuple(c) for c in cols))

if INSTALAR:
    st = INSTALAR
    q = lambda c: rgb5(c) if c else None                # cores de 5 bits, como o GBA guarda
    # overworld: as duas cenouras na mesma paleta
    frames = {}
    for nome, P in (('ice', ICE), ('shade', SHADE)):
        fr = [plot_art(P, st, 'plantada', False), plot_art(P, st, 'pronta', False), plot_art(P, st, 'pronta', True)]
        frames[nome] = [[[q(c) for c in r] for r in g.p] for g in fr]
    cols = sorted({c for fs in frames.values() for f in fs for r in f for c in r if c}, key=sum)
    assert len(cols) <= 15, len(cols)
    pal = [(0, 0, 0)] + cols + [(0, 0, 0)] * (15 - len(cols))
    for nome, fs in frames.items():
        order = [0, 1, 2, 0, 0, 1, 1, 2, 2]
        sheet = [sum([indexed(fs[i], cols)[y] for i in order], []) for y in range(32)]
        write_png_indexed4(os.path.join(ROOT, 'graphics/object_events/pics/people/special/kings_carrot_%s.png' % nome), sheet, pal)
    # ícones 24x24, um por cenoura, paleta própria
    for nome, P, item in (('ice', ICE, 'iceroot_carrot'), ('shade', SHADE, 'shaderoot_carrot')):
        g = icon(P, st)
        px = [[q(c) for c in r] for r in g.p]
        ic = sorted({c for r in px for c in r if c}, key=sum)
        assert len(ic) <= 15, len(ic)
        ipal = [(211, 211, 211)] + ic + [(0, 0, 0)] * (15 - len(ic))
        write_png_indexed4(os.path.join(ROOT, 'graphics/items/icons/%s.png' % item), indexed(px, ic), ipal)
        write_jasc(os.path.join(ROOT, 'graphics/items/icon_palettes/%s.pal' % item), ipal)
    print('instalado', st, '- cores do overworld', len(cols))
