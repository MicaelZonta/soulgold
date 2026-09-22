#!/usr/bin/env python3
"""Exemplo completo: a ilha do SunMoonAltar (30x30) = johto_general + gTileset_AltarSunMoon.

    python3 .claude/skills/montar-tileset/exemplo_altar_sol_lua.py SAIDA/
    python3 .claude/skills/prototipo-de-mapa/exemplo_ilha_altar.py SAIDA/

Le SAIDA/altar_grid.json + SAIDA/altar_sun_moon/ e escreve em SAIDA/ilha/:
map.bin, border.bin, objects.json (object_events prontos para o map.json) e os renders
dia, noite, transicao, clima, base, colisao. Nada no repositorio e alterado.

Receita (vale para qualquer mapa):
  1. grade de CLASSES (agua, areia, grama, floresta, carimbo, cais) desenhada por regra
  2. cada classe vira metatile pelas pecas aprendidas (JOHTO em mapa_kit.py)
  3. carimbo do tileset novo com sua grade de colisao
  4. objetos do map.json, conferidos contra a colisao (check_objects)
  5. renders de cada estado com os sprites reais
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from mapa_kit import *

BASE = sys.argv[1] if len(sys.argv) > 1 else 'altar_out'
OUT = os.path.join(BASE, 'ilha'); os.makedirs(OUT, exist_ok=True)
A = json.load(open(os.path.join(BASE, 'altar_grid.json')))
SEC = load_tileset(None, path=os.path.join(BASE, 'altar_sun_moon'))
PRIM = load_tileset('primary', 'johto_general')
MW = MH = 30
AX = 7
AY = 16 - A['h']                 # a base do altar (escadaria) fica sempre na linha 15

# ------------------------------------------------------------------ 1. classes
W_, S_, G_, F_, A_, P_ = 'W', 'S', 'G', 'F', 'A', 'P'
T = [[W_] * MW for _ in range(MH)]
def land(x, y):
    dx, dy = (x + 0.5 - 15.0) / 13.6, (y + 0.5 - 13.4) / 12.6
    return abs(dx) ** 5 + abs(dy) ** 5 <= 1       # expoente alto = costa reta, so cantos convexos
for y in range(MH):
    for x in range(MW):
        if land(x, y):
            T[y][x] = G_
def near(x, y, cls, r):
    for dy in range(-r, r + 1):
        for dx in range(-r, r + 1):
            xx, yy = x + dx, y + dy
            if not (0 <= xx < MW and 0 <= yy < MH) or T[yy][xx] in cls:
                return True
    return False
# praia com pelo menos 2 celulas entre mar e grama: uma para a borda de agua, outra para a de grama
beach = [[T[y][x] == G_ and near(x, y, (W_,), 2) for x in range(MW)] for y in range(MH)]
for y in range(MH):
    for x in range(MW):
        if beach[y][x]:
            T[y][x] = S_
for y in range(16, MH):                          # trilha da escadaria ate a praia
    for x in range(13, 16):
        if T[y][x] == G_: T[y][x] = S_
for y in (16, 17):                               # pracinha em frente a escadaria
    for x in range(11, 18):
        if T[y][x] == G_: T[y][x] = S_
# arvores: colunas de 2 de largura nas laterais do altar, escalonadas (uma comeca uma linha
# abaixo da outra), com uma celula de grama antes da praia e espaco para a base 36|37 embaixo
def tree_column(x0, y0, y1):
    for y in range(y0, y1 + 1):
        ok = all(T[y][x] == G_ and not near(x, y, (S_, W_), 1) for x in (x0, x0 + 1))
        if ok:                                     # a arvore entra inteira (2 celulas) ou nao entra
            T[y][x0] = T[y][x0 + 1] = F_
for x0, y0 in ((AX - 4, AY + 1), (AX - 2, AY), (AX + A['w'], AY), (AX + A['w'] + 2, AY + 1)):
    tree_column(x0, y0, 15 - (1 if y0 == AY + 1 else 0))
for y in range(A['h']):
    for x in range(A['w']):
        T[AY + y][AX + x] = A_
pier_top = max(y for y in range(MH) if T[y][14] == S_) + 1
for y in range(pier_top, min(pier_top + 3, MH)):
    for x in (13, 14, 15):
        T[y][x] = P_

# ------------------------------------------------------------------ 2-3. metatiles, colisao, elevacao
grid = [[0] * MW for _ in range(MH)]
for y in range(MH):
    for x in range(MW):
        t = T[y][x]
        if t == W_:
            grid[y][x] = pack_block(JOHTO['water'], 0, 1)
        elif t == S_:
            grid[y][x] = pack_block(pick_sand(T, x, y))
        elif t == G_:
            b = tree_base(T, x, y)
            grid[y][x] = pack_block(b, 1) if b else pack_block(JOHTO['grass'])
        elif t == F_:
            grid[y][x] = pack_block(pick_forest(T, x, y), 1)
        elif t == P_:
            grid[y][x] = pack_block(JOHTO['pier'][x - 13])
        else:
            g = A['grid'][y - AY][x - AX]
            walk = A['walk'][y - AY][x - AX]
            grid[y][x] = pack_block(JOHTO['grass'] if g is None else NUM_METATILES_IN_PRIMARY + g, 0 if walk else 1)
for (rx, ry) in ((3, 27), (24, 27), (0, 1), (27, 3)):
    if all(T[ry + dy][rx + dx] == W_ for dx in (0, 1) for dy in (0, 1)):
        for (dx, dy), mid in zip(((0, 0), (1, 0), (0, 1), (1, 1)), JOHTO['sea_rock_2x2']):
            grid[ry + dy][rx + dx] = pack_block(mid, 1, 1)
for (fx, fy) in ((7, 21), (8, 22), (20, 20), (21, 21), (19, 21)):
    if T[fy][fx] == G_:
        grid[fy][fx] = pack_block(JOHTO['flowers'])
write_blocks(os.path.join(OUT, 'map.bin'), grid)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
blocks = [v for row in grid for v in row]

# ------------------------------------------------------------------ 4. objetos (formato do map.json)
def obj(local, gfx, x, y, face, script, elev=3):
    return {'local_id': 'LOCALID_SUN_MOON_ALTAR_' + local, 'graphics_id': gfx, 'x': x, 'y': y, 'elevation': elev,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': 'TRAINER_TYPE_NONE', 'trainer_sight_or_berry_tree_id': '0', 'script': script, 'flag': '0'}
SHIP = obj('SS_TIDAL', 'OBJ_EVENT_GFX_SS_TIDAL', 19, pier_top + 2, 'RIGHT', '0x0', elev=1)
SAILOR = obj('SAILOR', 'OBJ_EVENT_GFX_SAILOR', 15, pier_top + 1, 'RIGHT', 'SunMoonAltar_EventScript_Sailor')
CLIMAX = [
    obj('LUSAMINE', 'OBJ_EVENT_GFX_LUSAMINE', 14, 9, 'DOWN', 'SunMoonAltar_EventScript_Lusamine'),
    obj('LILLIE', 'OBJ_EVENT_GFX_LILLIE', 12, 11, 'UP', 'SunMoonAltar_EventScript_Lillie'),
    obj('NINETALES', 'OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)', 11, 11, 'UP', 'NULL'),
    obj('GLADION', 'OBJ_EVENT_GFX_GLADION', 16, 11, 'UP', 'SunMoonAltar_EventScript_Gladion'),
    obj('SILVALLY', 'OBJ_EVENT_GFX_SPECIES(SILVALLY)', 17, 11, 'UP', 'NULL'),
    obj('LOOKER', 'OBJ_EVENT_GFX_LOOKER', 13, 13, 'UP', 'SunMoonAltar_EventScript_Looker'),
    obj('ANABEL', 'OBJ_EVENT_GFX_ANABEL', 15, 13, 'UP', 'SunMoonAltar_EventScript_Anabel'),
    obj('KUKUI', 'OBJ_EVENT_GFX_KUKUI', 10, 14, 'UP', 'SunMoonAltar_EventScript_Kukui'),
    SAILOR, SHIP,
]
PLAYER = obj('PLAYER', 'OBJ_EVENT_GFX_BRENDAN_NORMAL', 14, 11, 'UP', '')
BASE_NPCS = [dict(o, x=x, y=y, movement_type='MOVEMENT_TYPE_FACE_DOWN') for o, (x, y) in
             ((CLIMAX[5], (9, 19)), (CLIMAX[6], (11, 19)))] + [SAILOR, SHIP]
bad = check_objects(blocks, MW, CLIMAX + BASE_NPCS + [PLAYER])
assert not bad, bad
json.dump(CLIMAX, open(os.path.join(OUT, 'objects.json'), 'w'), indent=2)

# ------------------------------------------------------------------ 5. renders
def portal_blocks():
    out = list(blocks)
    for y in range(A['h']):
        for x in range(A['w']):
            g = A['portal'][y][x]
            if g is not None:
                i = (AY + y) * MW + AX + x
                out[i] = (out[i] & ~0x7ff) | (NUM_METATILES_IN_PRIMARY + g)
    return out
HEAL, WARP = (14, pier_top - 1), (14, 9)
R = lambda **kw: render_blocks(kw.pop('b', blocks), MW, MH, PRIM, SEC, swap=A['swap'], **kw)
write_png(os.path.join(OUT, 'dia.png'), R(objects=[SHIP]), 2)
write_png(os.path.join(OUT, 'transicao.png'), R(night=0.5, objects=[SHIP]), 2)
write_png(os.path.join(OUT, 'noite.png'), R(night=1.0, objects=[SHIP]), 2)
write_png(os.path.join(OUT, 'climax.png'), R(objects=CLIMAX + [PLAYER]), 2)
write_png(os.path.join(OUT, 'base_noite.png'), R(b=portal_blocks(), night=1.0, objects=BASE_NPCS), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(objects=CLIMAX, overlay=True, marks=[(HEAL, (80, 230, 120)), (WARP, (200, 120, 255))]), 2)
print('AY', AY, 'cais', pier_top, 'pouso', HEAL, '->', OUT)

# ------------------------------------------------------------------ 6. detalhes ampliados (recortes 1x -> 6x)
# disco: colunas 6..8 do altar, centro 34 px abaixo do topo da estela
dx0, dy0 = (AX + 6) * 16, (AY + A['h'] - 12) * 16 + 8
for nome, nt in (('disco_dia', 0.0), ('disco_transicao', 0.5), ('disco_noite', 1.0)):
    write_png(os.path.join(OUT, nome + '.png'), crop(R(night=nt), dx0, dy0, dx0 + 48, dy0 + 56), 6)
