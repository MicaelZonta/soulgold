# Prototipo dos 4 mapas das dungeons dos corceis (REI_DA_COLHEITA.md secao 15, versao enxuta).
# python3 .claude/berry_master/prototipo_corceis/gera.py  -> renders, map.bin e objetos nesta pasta.
# Pagina: https://claude.ai/artifact/R65MTm61Y7NGT8doiocyRY
import sys, os, json, random, copy
sys.path.insert(0, '/home/user/soulgold/.claude/skills/prototipo-de-mapa')
from mapa_kit import *
S = os.path.dirname(os.path.abspath(__file__)); OUT = S  # renders e arquivos ficam ao lado do script; os.makedirs(OUT, exist_ok=True)
random.seed(7)

def obj(gfx, x, y, face='DOWN', script='NULL', lid=''):
    return {'local_id': lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': 3,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': 'TRAINER_TYPE_NONE', 'trainer_sight_or_berry_tree_id': '0', 'script': script, 'flag': '0'}
def lum(c): return 0.3 * c[0] + 0.59 * c[1] + 0.11 * c[2]
def tint(cv, f):
    return [[f(c, x, y) for x, c in enumerate(row)] for y, row in enumerate(cv)]
def crystal(c, x, y):
    if c == (0, 0, 0): return c
    l = lum(c)
    r, g, b = l * 0.55 + 70, l * 0.75 + 70, l * 0.55 + 125
    if (x * 7 + y * 13) % 97 == 0 and l > 90: r = g = b = 255          # brilho
    return tuple(min(255, int(v)) for v in (r, g, b))
def sepia(c, x, y):
    if c == (0, 0, 0): return c
    l = lum(c)
    return tuple(min(255, int(v)) for v in (l * 1.08 + 18, l * 0.86 + 8, l * 0.62))
def fire(c, x, y):
    if c == (0, 0, 0): return c
    return tuple(min(255, int(v)) for v in (c[0] * 1.15 + 30, c[1] * 0.72 + 5, c[2] * 0.45))
def draw_on(cv, objs, night=False):
    for o in sorted(objs, key=lambda o: o['y']): draw_object(cv, o, night)
    return cv
def save(name, cv): write_png(os.path.join(OUT, name + '.png'), cv, 2)
def overlay_marks(cv, marks):
    for (mx, my), col in marks:
        for i in range(16):
            for p in (0, 1, 14, 15):
                cv[my*16+p][mx*16+i] = col; cv[my*16+i][mx*16+p] = col
    return cv
report = {}

# ================================================================ G1 Greenfield (base: NewBarkTown)
L = load_layout('NewBarkTown'); W, H = L['w'], L['h']
b = list(L['blocks'])
flowers = 0
for y in range(H):
    for x in range(W):
        v = b[y*W+x]
        if (v & 0x7ff) == 1 and not (v >> 11 & 1) and random.random() < 0.28:
            b[y*W+x] = (v & ~0x7ff) | 4; flowers += 1
PEONIA = obj('PICNICKER', 3, 12, 'RIGHT', lid='PEONIA')
PLAYER = obj('BRENDAN_NORMAL', 4, 12, 'RIGHT')
FROZEN = [obj('WOMAN_1', 11, 16, 'DOWN', 'Greenfield_EventScript_FrozenWoman'),
          obj('OLD_MAN_1', 20, 22, 'LEFT', 'Greenfield_EventScript_FrozenOldMan'),
          obj('BOY', 10, 29, 'UP', 'Greenfield_EventScript_FrozenBoy')]
g1_objs = FROZEN + [PEONIA]
print('G1 check', check_objects(b, W, g1_objs + [PLAYER]))
swap = swap_slots(L['info']['primary_tileset']) + swap_slots(L['info']['secondary_tileset'])
base = render_blocks(b, W, H, L['prim'], L['sec'], swap=swap, objects=FROZEN)
save('g1_cristal', draw_on(tint(base, crystal), [PEONIA, PLAYER]))
save('g1_depois', render_blocks(b, W, H, L['prim'], L['sec'], swap=swap, objects=FROZEN + [PEONIA, PLAYER]))
save('g1_colisao', render_blocks(b, W, H, L['prim'], L['sec'], swap=swap, objects=g1_objs, overlay=True,
                                 marks=[((0, 12), (200, 120, 255)), ((6, 9), (80, 230, 120))]))
write_blocks(os.path.join(OUT, 'greenfield_map.bin'), [b[y*W:(y+1)*W] for y in range(H)])
json.dump(g1_objs, open(os.path.join(OUT, 'greenfield_objects.json'), 'w'), indent=2)
report['g1'] = dict(w=W, h=H, flores=flowers)

# ================================================================ G2 Mansao Hale (base: DarkraiInn1, recorte + salao)
L = load_layout('DarkraiInn1'); SW = L['w']
src = [L['blocks'][y*SW:(y+1)*SW] for y in range(L['h'])]
X0, X1 = 19, 45
rows = [r[X0:X1] for r in src[0:7]] + [src[5][X0:X1]] * 3 + [r[X0:X1] for r in src[7:20]]
W2, H2 = X1 - X0, len(rows)
b2 = [v for r in rows for v in r]
Y = lambda y: y + 3 if y >= 7 else y     # linha da fonte -> linha do prototipo
MOLLY = obj('WOMAN_2', 35 - X0, Y(14), 'UP', 'GreenfieldMansion_EventScript_Molly', 'MOLLY')
GLAS = obj('SPECIES(GLASTRIER)', 13, 5, 'DOWN', 'GreenfieldMansion_EventScript_Glastrier', 'GLASTRIER')
PL2 = obj('BRENDAN_NORMAL', 29 - X0, Y(18), 'UP'); PE2 = obj('PICNICKER', 30 - X0, Y(18), 'UP')
PL2b = obj('BRENDAN_NORMAL', 13, 8, 'UP'); PE2b = obj('PICNICKER', 11, 9, 'UP')
MOLLY_b = dict(MOLLY, x=15, y=9, movement_type='MOVEMENT_TYPE_FACE_UP')
print('G2 check', check_objects(b2, W2, [MOLLY, GLAS, PL2, PE2, PL2b, PE2b, MOLLY_b]))
R2 = lambda objs, **kw: render_blocks(b2, W2, H2, L['prim'], L['sec'], objects=objs, **kw)
cv = R2([]);
salao = [[crystal(c, x, y) if y < 11 * 16 else c for x, c in enumerate(row)] for y, row in enumerate(cv)]
save('g2_chegada', draw_on([row[:] for row in salao], [MOLLY, GLAS, PL2, PE2]))
save('g2_chefe', draw_on([row[:] for row in salao], [GLAS, PL2b, PE2b, MOLLY_b]))
save('g2_depois', R2([MOLLY_b, PL2b, PE2b]))
save('g2_colisao', R2([MOLLY, GLAS], overlay=True, marks=[((29 - X0, Y(19)), (200, 120, 255))]))
write_blocks(os.path.join(OUT, 'mansion_map.bin'), rows)
report['g2'] = dict(w=W2, h=H2)

# ================================================================ S1 Torre de Bronze 1F (base: BurnedTower_1F sem buracos)
L = load_layout('BurnedTower_1F'); W3, H3 = L['w'], L['h']
b3 = list(L['blocks']); keep = {1024, 585, 1061, 1062, 1063}
for y in range(4, 23):
    for x in range(2, 26):
        if (b3[y*W3+x] & 0x7ff) not in keep:
            b3[y*W3+x] = pack_block(1024)
for (x, y) in ((6, 8), (20, 8), (6, 14), (20, 14)):
    b3[y*W3+x] = pack_block(585, 1)
SAGES = [obj('SAGE', 9, 8, 'RIGHT', 'BrassTowerMemory_EventScript_Sage1'),
         obj('SAGE', 17, 11, 'DOWN', 'BrassTowerMemory_EventScript_Sage2'),
         obj('SAGE', 5, 17, 'UP', 'BrassTowerMemory_EventScript_Sage3')]
KIM = obj('KIMONO_GIRL', 22, 19, 'LEFT', 'BrassTowerMemory_EventScript_KimonoMemory')
PL3 = obj('BRENDAN_NORMAL', 15, 21, 'UP'); MO3 = obj('MORTY', 14, 21, 'UP'); EU3 = obj('EUSINE', 16, 21, 'UP'); PE3 = obj('PICNICKER', 13, 21, 'UP')
print('S1 check', check_objects(b3, W3, SAGES + [KIM, PL3, MO3, EU3, PE3]))
R3 = lambda objs, **kw: render_blocks(b3, W3, H3, L['prim'], L['sec'], objects=objs, **kw)
save('s1_entardecer', draw_on(tint(R3(SAGES + [KIM]), sepia), [PL3, MO3, EU3, PE3]))
save('s1_hoje', render_repo_map('BurnedTower_1F', objects=[]))
save('s1_colisao', R3(SAGES + [KIM], overlay=True, marks=[((14, 4), (255, 160, 60)), ((15, 23), (200, 120, 255))]))
write_blocks(os.path.join(OUT, 'brasstower_1f_map.bin'), [b3[y*W3:(y+1)*W3] for y in range(H3)])
json.dump(SAGES + [KIM], open(os.path.join(OUT, 'brasstower_1f_objects.json'), 'w'), indent=2)
report['s1'] = dict(w=W3, h=H3)

# ================================================================ S2 Telhado em chamas (base: TinTower_RoofDay)
L = load_layout('TinTower_RoofDay'); W4, H4 = L['w'], L['h']
b4 = list(L['blocks'])
SPEC = obj('SPECIES(SPECTRIER)', 10, 8, 'DOWN', 'BrassTowerRoof_EventScript_Spectrier', 'SPECTRIER')
TOMO = obj('SAGE', 10, 9, 'DOWN', 'BrassTowerRoof_EventScript_Tomo', 'TOMO')
PL4 = obj('BRENDAN_NORMAL', 10, 11, 'UP'); MO4 = obj('MORTY', 9, 12, 'UP'); EU4 = obj('EUSINE', 11, 12, 'UP'); PE4 = obj('PICNICKER', 10, 13, 'UP')
HOOH = obj('SPECIES(HO_OH)', 4, 3, 'RIGHT')
print('S2 check', check_objects(b4, W4, [SPEC, TOMO, PL4, MO4, EU4, PE4]))
cv = render_blocks(b4, W4, H4, L['prim'], L['sec'], objects=[])
sky = {i for i, v in enumerate(b4) if (v & 0x7ff) == 1172}
def burn(cv, t=0.0):
    out = []
    for y, row in enumerate(cv):
        nr = []
        for x, c in enumerate(row):
            i = (y // 16) * W4 + x // 16
            if i in sky:
                k = y / (H4 * 16)
                c = (int(90 + 150 * k), int(20 + 70 * k), int(30 + 10 * k))
                if random.random() < 0.004: c = (255, 220, 120)
            else:
                c = fire(c, x, y)
                if (v := b4[i] & 0x7ff) in (1150, 1151) and random.random() < 0.05 * (1 + (y % 16 < 6)):
                    c = random.choice([(255, 140, 40), (255, 90, 30), (255, 210, 90)])
            nr.append(c)
        out.append(nr)
    return out
burned = burn(cv)
save('s2_tomo', draw_on([r[:] for r in burned], [SPEC, TOMO, PL4, MO4, EU4, PE4]))
save('s2_hooh', draw_on([r[:] for r in burned], [SPEC, PL4, MO4, EU4, PE4, HOOH]))
save('s2_colisao', render_blocks(b4, W4, H4, L['prim'], L['sec'], objects=[SPEC, TOMO], overlay=True, marks=[((10, 14), (200, 120, 255))]))
json.dump([SPEC, TOMO], open(os.path.join(OUT, 'brasstower_roof_objects.json'), 'w'), indent=2)
report['s2'] = dict(w=W4, h=H4)
json.dump(report, open(os.path.join(OUT, 'report.json'), 'w'))
print(report)
