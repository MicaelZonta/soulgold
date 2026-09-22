#!/usr/bin/env python3
"""Duas propostas de fundo de batalha para a arena (BATTLE_ENVIRONMENT_ULTRA_SPACE, hoje vazio).

    python3 .claude/skills/montar-tileset/exemplo_fundo_batalha_ultra.py SAIDA/

Gerador REAL de graphics/battle_environment/ultra_space/ (proposta A; SAIDA/ultra_space/).

Regras do fundo de batalha: area visivel 240x112 (o resto fica sob a caixa de texto),
3 paletas de 16 cores (BG 2..4 no jogo; aqui slots 7..9 do kit), UMA paleta por tile 8x8.
Posicoes dos Pokemon (sBattlerCoords, singles): inimigo centro (176,40), jogador (72,80).
A: plataformas flutuantes com borda de ouro no vazio.
B: o chao da propria arena (render do map.bin) projetado em perspectiva.
"""
import math, os, struct, sys
ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'))
sys.path.insert(0, os.path.join(ROOT, '.claude/skills/prototipo-de-mapa'))
from mapa_kit import *

OUT = sys.argv[1]
os.makedirs(OUT, exist_ok=True)
W, H = 256, 112              # 32 colunas de tile (o tilemap tem 32); a tela mostra 240
VIS = 240
h = noise

VOID = (14, 9, 32); CORE = (3, 2, 9); OUTL = (16, 12, 30)
NEB = [(34, 16, 70), (62, 28, 118), (104, 50, 170), (150, 92, 222), (204, 164, 250)]
STAR = [(255, 255, 255), (206, 188, 255), (150, 204, 255), (255, 232, 150)]
ST = [(178, 180, 222), (132, 132, 184), (98, 96, 148), (70, 66, 114), (46, 41, 80)]
CR = [(244, 252, 255), (172, 232, 255), (130, 160, 250), (100, 80, 204)]
GOLD = [(255, 250, 212), (250, 216, 112), (214, 160, 60), (146, 96, 42)]
FL = [(246, 244, 255), (222, 218, 246), (198, 192, 232), (166, 158, 210)]
RIFT = [(255, 255, 255), (184, 244, 255), (112, 196, 252), (164, 112, 250), (214, 84, 214), (92, 40, 152)]
COLORS = {'void': (VOID, None), 'core': (CORE, None), 'out': (OUTL, None)}
for pre, arr in (('n', NEB), ('*', STAR), ('s', ST), ('c', CR), ('g', GOLD), ('f', FL), ('p', RIFT)):
    COLORS.update({'%s%d' % (pre, i): (c, None) for i, c in enumerate(arr)})

def sanitize(cv, pal):
    """Tile com cores de duas paletas: fica com a paleta que cobre mais pixels e troca o resto
    pela cor mais proxima dela (normalmente estrela/nevoa perto de uma plataforma)."""
    fixed = 0
    for ty in range(cv.h // 8):
        for tx in range(cv.w // 8):
            keys = [cv.px[ty * 8 + y][tx * 8 + x] for y in range(8) for x in range(8)]
            if pal.slot_for(keys) != -1: continue
            best = max(pal.order, key=lambda s: sum(k in pal.slots[s] for k in keys))
            allowed = pal.slots[best]
            for y in range(8):
                for x in range(8):
                    k = cv.px[ty * 8 + y][tx * 8 + x]
                    if k not in allowed:
                        c = COLORS[k][0]
                        cv.px[ty * 8 + y][tx * 8 + x] = min(allowed, key=lambda a: sum((COLORS[a][0][i] - c[i]) ** 2 for i in range(3)))
            fixed += 1
    return fixed

def finish(name, cv, pal):
    fixed = sanitize(cv, pal)
    tiles, bad = cut_tiles(cv, pal)
    assert not bad, bad[:3]
    bank = TileBank()
    for t in tiles.values(): bank.add(t[1])
    img = [[COLORS[k][0] if k else (0, 0, 0) for k in row[:VIS]] for row in cv.px]
    if name == 'A':
        export(cv, pal, tiles, os.path.join(OUT, 'ultra_space'))
    write_png(os.path.join(OUT, '%s_fundo.png' % name), img, 3)
    shot = with_mons(img)
    write_png(os.path.join(OUT, '%s_batalha.png' % name), shot, 3)
    print(name, 'tiles', len(bank.tiles), 'celulas corrigidas', fixed)
    return len(bank.tiles)

def export(cv, pal, tiles, folder):
    """Arquivos no formato de graphics/battle_environment/<nome>/: tiles.png (4bpp, 128 px),
    tiles.bin (64x32 entradas = duas telas 32x32 iguais; linhas 14+ = tile vazio, paleta 0,
    ficam sob a caixa de texto) e palette.pal (48 cores = BG 2, 3, 4)."""
    os.makedirs(folder, exist_ok=True)
    bank = TileBank()                                        # tile 0 = vazio
    screen = [0] * 1024
    for ty in range(H // 8):
        for tx in range(32):
            slot, t = tiles[(tx, ty)]
            i, hf, vf = bank.add(t)
            screen[ty * 32 + tx] = i | (hf << 10) | (vf << 11) | ((slot - 7 + 2) << 12)
    assert len(bank.tiles) <= 512, len(bank.tiles)
    with open(os.path.join(folder, 'tiles.bin'), 'wb') as f:
        for v in screen + screen:
            f.write(struct.pack('<H', v))
    rows = (len(bank.tiles) + 15) // 16
    idx = [[0] * 128 for _ in range(rows * 8)]
    for n, t in enumerate(bank.tiles):
        for y in range(8):
            for x in range(8):
                idx[(n // 16) * 8 + y][(n % 16) * 8 + x] = t[y][x]
    cols = []
    for s_ in (7, 8, 9):
        c = pal.colors_of(s_)
        c[0] = VOID                                          # indice 0 nunca e usado; cor neutra
        cols += c
    write_png_indexed4(os.path.join(folder, 'tiles.png'), idx, cols[:16])
    with open(os.path.join(folder, 'palette.pal'), 'w', newline='\r\n') as f:
        f.write('JASC-PAL\n0100\n48\n' + ''.join('%d %d %d\n' % c for c in cols))
    print('exportado', folder, 'tiles', len(bank.tiles))

def sprite(path, palpath):
    Wp, Hp, _, px, _ = read_png(path)
    pal = read_pal(palpath)
    return [[pal[v] if v else None for v in r[:64]] for r in px[:64]]
FRONT = sprite(ROOT + '/graphics/pokemon/necrozma/ultra/front.png', ROOT + '/graphics/pokemon/necrozma/ultra/normal.pal')
BACK = sprite(ROOT + '/graphics/pokemon/solgaleo/back.png', ROOT + '/graphics/pokemon/solgaleo/normal.pal')
def with_mons(img):
    out = [r[:] for r in img] + [[(56, 56, 72)] * VIS for _ in range(48)]
    for y in range(48):                                      # caixa de texto (simulada)
        for x in range(VIS):
            if y in (0, 47) or x in (0, VIS - 1): out[H + y][x] = (40, 40, 48)
            elif y in (1, 46) or x in (1, VIS - 2): out[H + y][x] = (200, 200, 208)
    for spr, (cx, cy) in ((FRONT, (176, 40)), (BACK, (72, 80))):
        for y in range(64):
            for x in range(64):
                c = spr[y][x]
                X, Y = cx - 32 + x, cy - 32 + y
                if c and 0 <= X < VIS and 0 <= Y < H:             # a caixa cobre o que passa de 112
                    out[Y][X] = c
    return out

# =========================================================================== ceu comum
def sky(cv, nebula_y=None):
    for y in range(H):
        for x in range(W):
            cv.put(x, y, 'void')
    for i in range(70):                                      # estrelas
        x, y = h(i * 97 + 5) % W, h(i * 31 + 17) % H
        cv.put(x, y, ['*1', '*2', '*0', '*1', 'n3'][h(i) % 5])
    for (x, y) in ((22, 14), (100, 30), (214, 20), (132, 8), (60, 50)):
        for (dx, dy, k) in ((0, 0, '*0'), (-1, 0, '*1'), (1, 0, '*1'), (0, -1, '*1'), (0, 1, '*1'), (-2, 0, '*2'), (2, 0, '*2'), (0, -2, '*2'), (0, 2, '*2')):
            cv.put(x + dx, y + dy, k)
    if nebula_y is not None:                                 # faixa de nevoa roxa perto do horizonte
        for y in range(H):
            for x in range(W):
                v = math.exp(-((y - nebula_y) / 12.0) ** 2) * (0.7 + 0.3 * math.sin(x * 0.045 + math.sin(y * 0.2)))
                v += ((x + y) % 2) * .1
                for lim, k in ((1.0, 'n3'), (.8, 'n2'), (.55, 'n1'), (.35, 'n0')):
                    if v >= lim and cv.get(x, y) == 'void':
                        cv.put(x, y, k); break

def galaxy(cv, cx, cy, R):
    for y in range(cy - R, cy + R):
        for x in range(cx - R, cx + R):
            dx, dy = (x + .5 - cx), (y + .5 - cy) * 1.5
            d = math.hypot(dx, dy)
            if d >= R: continue
            arm = math.cos(2 * (math.atan2(dy, dx) - 2.3 * math.log(d + 1)))
            v = (arm * .5 + .5) * (1 - d / R) * 1.5 + max(0, 1 - d / 6) * 1.4 + ((x + y) % 2) * .18
            for lim, kk in ((1.55, '*0'), (1.25, 'n4'), (0.98, 'n3'), (0.74, 'n2'), (0.52, 'n1'), (0.34, 'n0')):
                if v >= lim: cv.put(x, y, kk); break

def black_hole(cv, cx, cy, r=9):
    for y in range(cy - r - 4, cy + r + 4):
        for x in range(cx - r - 4, cx + r + 4):
            d = math.hypot(x + .5 - cx, y + .5 - cy)
            chk = (x + y) % 2
            if d < r * .55: k = 'core'
            elif d < r * .65: k = 'n4'
            elif d < r * .75: k = '*1'
            elif d < r * .9: k = 'n3'
            elif d < r * 1.1: k = 'n2' if chk else 'n3'
            elif d < r * 1.3: k = 'n1' if chk else 'void'
            else: continue
            cv.put(x, y, k)

# =========================================================================== A: plataformas flutuantes (epica)
def rift(cv, cx, cy, R):
    """a fenda do Ultra Espaco: raios de luz saindo do centro e vortice em espiral."""
    for i in range(11):                                       # raios (desenhados antes do vortice)
        ang = -math.pi + i * (2 * math.pi / 11) + .17
        for y in range(H):
            for x in range(W):
                dx, dy = x + .5 - cx, y + .5 - cy
                d = math.hypot(dx, dy)
                if d < R * .8: continue
                da = abs((math.atan2(dy, dx) - ang + math.pi) % (2 * math.pi) - math.pi)
                width = .045 + (.025 if i % 3 == 0 else 0)
                if da < width and cv.get(x, y) in ('void', 'core', 'n0', 'n1'):
                    fall = d / (R * 3.2)
                    if da < width * .35 and fall < .75: cv.put(x, y, 'n3' if fall < .45 else 'n2')
                    elif (x + y) % 2 == 0 and fall < 1.1: cv.put(x, y, 'n2' if fall < .6 else 'n1')
    for y in range(cy - int(R * 1.4), cy + int(R * 1.4)):
        for x in range(cx - int(R * 1.4), cx + int(R * 1.4)):
            dx, dy = x + .5 - cx, y + .5 - cy
            d = math.hypot(dx, dy)
            if d > R * 1.35: continue
            chk = (x + y) % 2
            if d < 3.5: k = '*0'
            elif d < 6: k = 'p1'
            elif d < R:
                v = (1 - d / R) + .22 * math.cos(3 * math.atan2(dy, dx) - d * .3) + chk * .06
                k = 'n2'
                for lim, kk in ((.74, 'p1'), (.58, 'p2'), (.45, 'n4'), (.33, 'p3'), (.21, 'p4'), (.1, 'n3')):
                    if v >= lim: k = kk; break
            elif d < R * 1.06: k = 'p2'                         # aro de luz
            elif d < R * 1.18: k = 'n3' if chk else 'n2'
            else: k = 'n2' if chk else 'n1'
            if k: cv.put(x, y, k)

def nebula(cv):
    """nevoa em camadas perto do horizonte, com fiapos magenta por cima."""
    for y in range(40, H):
        for x in range(W):
            if cv.get(x, y) not in ('void', 'core'): continue
            v = (math.sin(x * .05 + math.sin(y * .13) * 2) * .5 + math.sin(x * .021 - y * .09 + 1.3) * .5) * .5 + .5
            v *= math.exp(-((y - 76) / 18.0) ** 2) * 1.25
            v += ((x + y) % 2) * .09
            for lim, k in ((1.1, 'p4'), (1.0, 'p3'), (.84, 'n3'), (.66, 'n2'), (.48, 'n1'), (.3, 'n0')):
                if v >= lim: cv.put(x, y, k); break

def shard(cv, cx, cy, hh, glow=True):
    """fragmento de cristal flutuando (losango alto) com brilho."""
    for y in range(cy - hh, cy + hh + 1):
        w = int((hh - abs(y - cy)) * .45)
        for x in range(cx - w, cx + w + 1):
            k = 'c3' if abs(x - cx) == w else 'c0' if x < cx and y < cy else 'c1' if x <= cx else 'c2'
            cv.put(x, y, k)
    if glow:
        cv.put(cx, cy - hh - 2, '*0'); cv.put(cx - 1, cy - hh - 2, '*1'); cv.put(cx + 1, cy - hh - 2, '*1')

def platform(cv, cx, cy, rx, ry, depth, hang=()):
    """palco flutuante: aro de ouro triplo, rosa-dos-ventos gravada, gema, faixa de runas acesas,
    estalactites, cristais pendurados e brilho ciano embaixo."""
    top = {}
    for y in range(cy - ry - 1, cy + ry + 2):
        for x in range(cx - rx - 1, cx + rx + 2):
            e = ((x + .5 - cx) / rx) ** 2 + ((y + .5 - cy) / ry) ** 2
            if e <= 1: top[(x, y)] = e
    bottom = {}
    for x in range(cx - rx, cx + rx + 1):                   # face lateral
        ys = [y for (xx, y) in top if xx == x]
        if not ys: continue
        yb = max(ys)
        u = (x + .5 - cx) / rx
        core = math.sqrt(max(0, 1 - u * u))
        L = int(depth * core) + (int(core * 6) if h(x * 7 + cy) % 3 == 0 else h(x * 5 + cy) % 3)
        for i in range(1, L + 1):
            frac = i / max(L, 1)
            if i == 1: k = 'g2'
            elif i == 2: k = 'g3'
            elif i == 3: k = 'out'
            elif i == 5 and x % 5 in (1, 2) and frac < .7: k = 'c1'          # runas acesas
            elif i == 5 and x % 5 in (0, 3) and frac < .7: k = 'c2'
            else:
                k = 's2' if (u < -.35 and frac < .5) else 's3' if frac < .55 else 's4'
                if (i + int(1.5 * math.sin(x * .5))) % 6 == 0 and 4 < i: k = 's4'
            cv.put(x, yb + i, k)
        cv.put(x, yb + L + 1, 'out')
        bottom[x] = yb + L + 1
    for x, yb in bottom.items():                              # brilho embaixo (luz das runas)
        for i in range(2, 9):
            if cv.get(x, yb + i) in ('void', 'core', 'n0', 'n1') and (x + yb + i) % 2 == 0 and h(x * 3 + i) % 3:
                cv.put(x, yb + i, 'p2' if i < 5 else 'n2')
    for (x, y), e in top.items():
        nx, ny = (x + .5 - cx) / rx, (y + .5 - cy) / ry
        up = y < cy
        if e > .93: k = 'out'
        elif e > .85: k = 'g0' if up else 'g2'
        elif e > .80: k = 'g3'
        elif e > .72: k = 'g1' if up else 'g2'
        elif e > .68: k = 'g3'
        else:
            k = 'f0' if ny < -.35 else 'f2' if ny > .45 else 'f1'
            dd = abs(nx) + abs(ny)
            if abs(x + .5 - cx) < 1 or abs(y + .5 - cy) < .6: k = 'g2'       # rosa-dos-ventos
            if abs(abs(nx) - abs(ny)) < .03 and dd < .6: k = 'g3'
            if .5 <= dd < .56: k = 'g1'
            if dd < .26: k = 'g3'
            if dd < .22: k = 'c2' if ny > 0 else 'c1'
            if dd < .1: k = 'f0'
        cv.put(x, y, k)
    for (bx, hh) in hang:                                     # cristais pendurados (ponta para baixo)
        by = bottom.get(bx, cy) - 2
        for i in range(hh):
            w = max(0, int((hh - i) * .3))
            for dx in range(-w, w + 1):
                k = 'c3' if abs(dx) == w and w > 0 else 'c0' if dx < 0 and i < hh * .5 else 'c1' if dx <= 0 else 'c2'
                cv.put(bx + dx, by + i, k)

def proposta_a():
    cv = Canvas(W, H)
    for y in range(H):                                        # fundo: topo mais escuro
        for x in range(W):
            cv.put(x, y, 'core' if (y < 10 or (y < 22 and (x + y) % 2 == 0)) else 'void')
    for i in range(80):
        x, y = h(i * 97 + 5) % W, h(i * 31 + 17) % H
        cv.put(x, y, ['*1', '*2', '*0', '*1', '*2'][h(i) % 5])
    nebula(cv)
    rift(cv, 92, 38, 26)
    for (x, y) in ((22, 12), (214, 18), (132, 6), (16, 56), (232, 50)):
        for (dx, dy, k) in ((0, 0, '*0'), (-1, 0, '*1'), (1, 0, '*1'), (0, -1, '*1'), (0, 1, '*1'),
                            (-2, 0, '*2'), (2, 0, '*2'), (0, -2, '*2'), (0, 2, '*2'), (0, -3, '*3'), (0, 3, '*3')):
            cv.put(x + dx, y + dy, k)
    for (sx, sy, hh) in ((30, 34, 5), (140, 70, 3), (224, 80, 4), (8, 90, 3), (120, 88, 3)):
        shard(cv, sx, sy, hh)
    platform(cv, 176, 70, 52, 12, 14, hang=((158, 9), (170, 13), (190, 7), (204, 5)))   # oponente
    platform(cv, 70, 109, 82, 17, 10)                                                     # jogador
    pal = PaletteSet({
        7: ['void', 'core', 'n0', 'n1', 'n2', 'n3', 'n4', '*0', '*1', '*2', '*3', 'p1', 'p2', 'p3', 'p4'],
        8: ['void', 'out', 's2', 's3', 's4', 'f0', 'f1', 'f2', 'f3', 'g0', 'g1', 'g2', 'g3', 'c1', 'c2'],
        9: ['void', 'out', 's1', 's2', 's3', 's4', 'c0', 'c1', 'c2', 'c3', '*0', '*1', 'n1', 'n2', 'p2'],
    }, COLORS, order=[7, 8, 9])
    return finish('A', cv, pal)

# =========================================================================== B: a arena em perspectiva
def proposta_b():
    L = load_layout('UltraSpaceArena')
    arena = render_blocks(L['blocks'], L['w'], L['h'], L['prim'], L['sec'])
    AW = len(arena[0]); AH = len(arena)
    key_of = {}
    for k, (c, _) in COLORS.items():
        key_of.setdefault(c, k)
    near = {}
    def to_key(c):
        if c in key_of: return key_of[c]
        if c not in near:
            near[c] = min(COLORS, key=lambda k: sum((COLORS[k][0][i] - c[i]) ** 2 for i in range(3)))
        return near[c]
    cv = Canvas(W, H)
    HOR = 56
    sky(cv, nebula_y=HOR - 6)
    galaxy(cv, 40, 22, 20)
    black_hole(cv, 206, 14, 8)
    F = 56.0
    # camera ao sul, olhando para o norte, no eixo da coluna 10: o losango fica simetrico e o
    # oponente (alto a direita) cai dentro dele; o jogador fica perto da ponta sul
    def arena_xy(sx, sy):
        z = F / (sy - HOR + .5)
        ay = 270 - z * 33.0
        ax = 168 + (sx - 120) * z * .27
        return ax, ay, z
    for sy in range(HOR, H):
        for sx in range(W):
            ax, ay, z = arena_xy(sx, sy)
            # media de 2x2 amostras para amaciar o serrilhado da distancia
            acc = [0, 0, 0]; n = 0
            for ox in (-.25, .25):
                for oy in (-.25, .25):
                    X, Y = int(ax + ox * z * .27), int(ay + oy * z * 33.0 / F * 2)
                    c = arena[Y][X] if (0 <= X < AW and 0 <= Y < AH) else VOID
                    for i in range(3): acc[i] += c[i]
                    n += 1
            c = tuple(v // n for v in acc)
            cv.put(sx, sy, to_key(c))
    # linha do horizonte: brilho da fenda norte e degrade para o vazio
    for sx in range(W):
        if cv.get(sx, HOR) == 'void': cv.put(sx, HOR, 'n0')
    pal = PaletteSet({
        7: ['void', 'core', 'n0', 'n1', 'n2', 'n3', 'n4', '*0', '*1', '*2', '*3'],
        8: ['void', 'out', 's1', 's2', 's3', 's4', 'f0', 'f1', 'f2', 'f3', 'g0', 'g1', 'g2', 'g3', 'c1'],
        9: ['void', 'out', 's1', 's2', 's3', 's4', 'p1', 'p2', 'p3', 'p4', 'p5', 'c0', 'c1', 'c2', 'n2'],
    }, COLORS, order=[7, 8, 9])
    return finish('B', cv, pal)

na = proposta_a()
nb = proposta_b()
open(os.path.join(OUT, 'fundos.txt'), 'w').write('A %d\nB %d\n' % (na, nb))
