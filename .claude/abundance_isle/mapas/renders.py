import sys, json, random, importlib
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
os_ = __import__('os'); os_.chdir('/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha')
from kit2 import *
from desenho import reduzir
OUT = 'img'; os.makedirs(OUT, exist_ok=True)
ART = {k: [(c, n, reduzir(f())) for c, n, f in importlib.import_module(m).PROPOSTAS]
       for k, m in (('santuario', 'arte_santuario'), ('maquina', 'arte_maquina'), ('pedra', 'arte_pedra'))}
def o(lid, gfx, x, y, face='DOWN', script='', flag='0', ttype='TRAINER_TYPE_NONE', sight='0', elev=3):
    return {'local_id': lid, 'graphics_id': 'OBJ_EVENT_GFX_' + gfx, 'x': x, 'y': y, 'elevation': elev,
            'movement_type': 'MOVEMENT_TYPE_FACE_' + face, 'movement_range_x': 0, 'movement_range_y': 0,
            'trainer_type': ttype, 'trainer_sight_or_berry_tree_id': sight, 'script': script, 'flag': flag}
def save(name, cv, scale=2): write_png(os.path.join(OUT, name), cv, scale)
def snow(cv, seed=3, amt=.28):
    r = random.Random(seed); H, W = len(cv), len(cv[0])
    cv = [[tuple(int(c[k] * (1 - amt) + (226, 234, 248)[k] * amt) for k in range(3)) for c in row] for row in cv]
    for _ in range(W * H // 90):
        x, y = r.randrange(W - 1), r.randrange(H - 1)
        for dx, dy in ((0, 0), (1, 0), (0, 1), (1, 1)): cv[y + dy][x + dx] = (250, 250, 255)
    return cv
def storm(cv, amt=.45):
    return [[tuple(int(c[k] * (1 - amt) + (40, 36, 72)[k] * amt) for k in range(3)) for c in row] for row in cv]
def mark_path(cv, pts, col):
    for (x0, y0), (x1, y1) in zip(pts, pts[1:]):
        n = max(abs(x1 - x0), abs(y1 - y0)) * 16
        for i in range(n + 1):
            X = int((x0 + (x1 - x0) * i / max(n, 1)) * 16 + 8); Y = int((y0 + (y1 - y0) * i / max(n, 1)) * 16 + 8)
            for d in (-1, 0, 1):
                cv[Y + d][X] = col; cv[Y][X + d] = col

# ============================================================== ILHA
E_ = json.load(open('ext/info.json')); EB = read_blocks('ext/map.bin'); EW, EH = E_['w'], E_['h']
PJ = load_tileset('primary', 'johto_general'); SF = load_tileset('secondary', 'route38_farmland')
pt = E_['pier_top']
SHIP = o('SS_TIDAL', 'SS_TIDAL', 25, pt + 2, 'RIGHT', '0x0', elev=1)
BASE_NPC = [
    o('SAILOR', 'SAILOR', 22, pt + 1, 'UP', 'AbundanceIsle_EventScript_Sailor'),
    o('KEEPER', 'OLD_MAN', 10, 22, 'DOWN', 'AbundanceIsle_EventScript_ShrineKeeper'),
    o('FARMER', 'MAN_3', 32, 24, 'DOWN', 'AbundanceIsle_EventScript_Farmer'),
    o('FARMER_WIFE', 'WOMAN_2', 37, 24, 'LEFT', 'AbundanceIsle_EventScript_FarmerWife'),
    o('HIKER', 'HIKER', 30, 13, 'LEFT', 'AbundanceIsle_EventScript_Hiker', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('PICNICKER', 'PICNICKER', 26, 20, 'DOWN', 'AbundanceIsle_EventScript_Picnicker', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('FISHERMAN', 'FISHERMAN', 21, pt + 2, 'LEFT', 'AbundanceIsle_EventScript_Fisherman', ttype='TRAINER_TYPE_NORMAL', sight='2'),
    o('ITEM_NORTH_BEACH', 'ITEM_BALL', 22, 2, script='AbundanceIsle_EventScript_ItemDampRock'),
    o('ITEM_PLATEAU', 'ITEM_BALL', 33, 8, script='AbundanceIsle_EventScript_ItemThunderStone'),
    o('ITEM_CLIFF', 'ITEM_BALL', 36, 14, script='AbundanceIsle_EventScript_ItemHardStone'),
    o('ITEM_GLADE', 'ITEM_BALL', 31, 41, script='AbundanceIsle_EventScript_ItemMiracleSeed'),
    o('CUT_TREE', 'CUT_TREE', *E_['cut'], script='EventScript_CutTree'),
    SHIP]
WINTER = BASE_NPC + [
    o('N', 'N', 14, 23, 'LEFT', 'AbundanceIsle_EventScript_N'),
    o('HILDA', 'HILDA', 15, 23, 'LEFT', 'AbundanceIsle_EventScript_Hilda'),
    o('GRUNT_1', 'SCIENTIST_1', 10, 17, 'DOWN', 'AbundanceIsle_EventScript_PlasmaGuard1'),
    o('GRUNT_2', 'SCIENTIST_1', 12, 17, 'DOWN', 'AbundanceIsle_EventScript_PlasmaGuard2'),
    o('TORNADUS_STORM', 'SPECIES(TORNADUS)', 14, 12, 'RIGHT', 'NULL'),
    o('THUNDURUS_STORM', 'SPECIES(THUNDURUS)', 31, 12, 'LEFT', 'NULL')]
SPRING = [x for x in BASE_NPC] + [
    o('TORNADUS', 'SPECIES(TORNADUS)', 30, 2, 'DOWN', 'AbundanceIsle_EventScript_Tornadus'),
    o('THUNDURUS', 'SPECIES(THUNDURUS)', 20, 7, 'DOWN', 'AbundanceIsle_EventScript_Thundurus'),
    o('LANDORUS', 'SPECIES(LANDORUS)', 10, 23, 'DOWN', 'AbundanceIsle_EventScript_Landorus'),
    o('ENAMORUS', 'SPECIES(ENAMORUS)', 9, 31, 'UP', 'AbundanceIsle_EventScript_Enamorus'),
    o('N_DOCK', 'N', 23, 48, 'UP', 'AbundanceIsle_EventScript_NFarewell'),
    o('HILDA_DOCK', 'HILDA', 22, 48, 'UP', 'AbundanceIsle_EventScript_HildaFarewell')]
SPRING[1] = dict(SPRING[1], x=12, y=23, movement_type='MOVEMENT_TYPE_FACE_LEFT')
bad = [b for b in check_objects(EB, EW, WINTER + SPRING) if 'STORM' not in b[0]]
print('ilha objetos em bloqueio/agua:', bad)
def ext(flowers=True, night=0.0, objs=(), shrine=0, overlay=False, marks=()):
    b = list(EB)
    if not flowers:
        for x, y in E_['flowers']: b[y * EW + x] = (b[y * EW + x] & ~0x7ff) | JOHTO['grass']
    cv = render_blocks(b, EW, EH, PJ, SF, night=night, overlay=overlay, marks=marks)
    ART['santuario'][shrine][2].over(cv, E_['shrine'][0] * 16, E_['shrine'][1] * 16)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob, night > .5)
    return cv
inv = ext(flowers=False, objs=WINTER); save('ilha_inverno.png', snow(inv))
save('ilha_primavera.png', ext(objs=SPRING))
save('ilha_noite.png', ext(night=1.0, objs=[SHIP]))
WARPS = {'frost': E_['frost'], 'summit': E_['summit'], 'barn': E_['barn_door'], 'house': E_['house_door']}
mk = [(p, (200, 120, 255)) for p in WARPS.values()] + [(tuple(p), (255, 230, 80)) for p in E_['signs'].values()]
save('ilha_colisao.png', ext(objs=BASE_NPC, overlay=True, marks=mk))
sx, sy = E_['shrine']
for i, (c, n, art) in enumerate(ART['santuario']):
    cv = ext(objs=SPRING, shrine=i)
    save('santuario_%s.png' % c, crop(cv, (sx - 4) * 16, (sy - 3) * 16, (sx + 7) * 16, (sy + 6) * 16), 3)

# ============================================================== CRATERA
F_ = json.load(open('frost/info.json')); FB = read_blocks('frost/map.bin'); FW, FH = F_['w'], F_['h']
LI = load_layout('SnowtopMountain_B1F')
mx, my = F_['machine']
FROST_BASE = [
    o('ITEM_NEVERMELT', 'ITEM_BALL', *F_['item_p'], script='FrostfallCrater_EventScript_ItemNeverMeltIce'),
    o('ITEM_ICYROCK', 'ITEM_BALL', *F_['item_e'], script='FrostfallCrater_EventScript_ItemIcyRock'),
    o('GRUNT_3', 'SCIENTIST_1', 15, 17, 'RIGHT', 'FrostfallCrater_EventScript_Grunt3', ttype='TRAINER_TYPE_NORMAL', sight='4'),
    o('GRUNT_4', 'SCIENTIST_1', 20, 16, 'LEFT', 'FrostfallCrater_EventScript_Grunt4', ttype='TRAINER_TYPE_NORMAL', sight='4')]
FROST_CLIMAX = FROST_BASE + [
    o('GHETSIS', 'SAGE', mx + 1, my + 3, 'DOWN', 'FrostfallCrater_EventScript_Ghetsis'),
    o('SCIENTIST_A', 'SCIENTIST_1', mx - 2, my + 2, 'UP', 'FrostfallCrater_EventScript_ScientistA'),
    o('SCIENTIST_B', 'SCIENTIST_1', mx + 4, my + 2, 'UP', 'FrostfallCrater_EventScript_ScientistB')]
FROST_AFTER = FROST_BASE[2:] + [o('ITEM_ICESTONE', 'ITEM_BALL', mx + 1, my + 3, script='FrostfallCrater_EventScript_ItemIceStone'),
                                o('N_CRATER', 'N', mx - 1, my + 3, 'UP', 'FrostfallCrater_EventScript_N')]
print('cratera objetos:', check_objects(FB, FW, FROST_CLIMAX + FROST_AFTER))
def frost(objs=(), mach=0, after=False, overlay=False, marks=(), path=None):
    b = list(FB)
    if after:
        for x, y in F_['shortcut']: b[y * FW + x] = pack_block(0x459, 0)
    cv = render_blocks(b, FW, FH, LI['prim'], LI['sec'], overlay=overlay, marks=marks)
    ART['maquina'][mach][2].over(cv, mx * 16, my * 16)
    if path: mark_path(cv, path, (255, 80, 200))
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
save('cratera_climax.png', frost(FROST_CLIMAX))
save('cratera_depois.png', frost(FROST_AFTER, after=True))
# solucao do gelo: reconstroi o caminho pelo BFS com deslizes
def solution(start, goal):
    from collections import deque
    walk = lambda x, y: not (FB[y * FW + x] >> 11 & 1)
    ice = lambda x, y: (FB[y * FW + x] & 0x7ff) == 0x4cb
    prev = {start: None}; q = deque([start])
    while q:
        p = q.popleft()
        if p == goal: break
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            x, y = p
            while True:
                nx, ny = x + dx, y + dy
                if not walk(nx, ny): break
                x, y = nx, ny
                if not ice(x, y): break
            if (x, y) not in prev: prev[(x, y)] = p; q.append((x, y))
    path = [goal]
    while prev[path[-1]]: path.append(prev[path[-1]])
    return path[::-1]
sol = solution((6, 17), (11, 5) if True else None)
save('cratera_colisao.png', frost(FROST_BASE, overlay=True, path=sol,
     marks=[(tuple(F_['exit']), (200, 120, 255))] + [(tuple(p), (255, 230, 80)) for p in F_['shortcut']]))
for i, (c, n, art) in enumerate(ART['maquina']):
    save('maquina_%s.png' % c, crop(frost(FROST_CLIMAX, mach=i), (mx - 4) * 16, (my - 1) * 16, (mx + 7) * 16, (my + 6) * 16), 3)
json.dump(sol, open('frost/solucao.json', 'w'))

# ============================================================== CUME
U_ = json.load(open('summit/info.json')); UB = read_blocks('summit/map.bin'); UW, UH = U_['w'], U_['h']
LS = load_layout('SpearPillarTop')
stx, sty = U_['stone']
SUM_BASE = [o('ITEM_ZAPPLATE', 'ITEM_BALL', 12, 9, script='Thunderspire_EventScript_ItemZapPlate'),
            o('ITEM_DRAGONFANG', 'ITEM_BALL', 31, 21, script='Thunderspire_EventScript_ItemDragonFang')]
SUM_CLIMAX = SUM_BASE + [
    o('GHETSIS', 'SAGE', stx + 2, sty + 2, 'UP', 'Thunderspire_EventScript_Ghetsis'),
    o('N', 'N', stx - 2, sty + 2, 'UP', 'Thunderspire_EventScript_N'),
    o('TORNADUS_SKY', 'SPECIES(TORNADUS)', 6, 4, 'RIGHT', 'NULL'),
    o('THUNDURUS_SKY', 'SPECIES(THUNDURUS)', 33, 4, 'LEFT', 'NULL')]
SUM_AFTER = SUM_BASE + [o('ZEKROM', 'SPECIES(ZEKROM)', stx, sty + 1, 'DOWN', 'Thunderspire_EventScript_Zekrom'),
                        o('N_AFTER', 'N', stx - 2, sty + 2, 'UP', 'Thunderspire_EventScript_NAfter'),
                        o('HILDA_AFTER', 'HILDA', stx + 2, sty + 2, 'UP', 'Thunderspire_EventScript_HildaAfter')]
print('cume objetos:', [b for b in check_objects(UB, UW, SUM_CLIMAX + SUM_AFTER) if 'SKY' not in b[0]])
def summit(objs=(), stone=0, night=0.0, overlay=False, marks=(), dark=False, show_stone=True):
    cv = render_blocks(UB, UW, UH, LS['prim'], LS['sec'], night=night, overlay=overlay, marks=marks)
    if dark: cv = storm(cv)
    if show_stone: ART['pedra'][stone][2].over(cv, stx * 16 - 8, sty * 16 - 16)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob, dark)
    return cv
ARRIVE = (15, 34)
save('cume_climax.png', summit(SUM_CLIMAX, dark=True))
save('cume_depois.png', summit(SUM_AFTER, show_stone=False))
save('cume_colisao.png', summit(SUM_BASE, overlay=True, marks=[(ARRIVE, (200, 120, 255)), ((stx, sty), (255, 230, 80))]))
for i, (c, n, art) in enumerate(ART['pedra']):
    save('pedra_%s.png' % c, crop(summit(SUM_CLIMAX, stone=i, dark=True), (stx - 5) * 16, (sty - 4) * 16, (stx + 6) * 16, (sty + 4) * 16), 3)
# arte isolada ampliada
for k, lst in ART.items():
    for c, n, art in lst:
        save('arte_%s_%s.png' % (k, c), art.rgb((232, 232, 236)), 4)
json.dump(dict(ilha=dict(inverno=WINTER, primavera=SPRING), cratera=dict(climax=FROST_CLIMAX, depois=FROST_AFTER),
               cume=dict(climax=SUM_CLIMAX, depois=SUM_AFTER), arrive=ARRIVE, warps=WARPS),
          open('objetos.json', 'w'), indent=1)
print('ok', 'solucao', sol)
