import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from kitA1 import *
D = os.path.dirname(os.path.abspath(__file__))
MW, MH = 40, 54
W_, S_, G_, F_, X_ = 'W', 'S', 'G', 'F', 'X'
T = [[W_] * MW for _ in range(MH)]
for y in range(MH):
    for x in range(MW):
        dx, dy = (x + .5 - 17.5) / 16.2, (y + .5 - 27) / 24.5
        if abs(dx) ** 4 + abs(dy) ** 4 <= 1: T[y][x] = G_
def near(x, y, cls, r):
    for dy in range(-r, r + 1):
        for dx in range(-r, r + 1):
            xx, yy = x + dx, y + dy
            if not (0 <= xx < MW and 0 <= yy < MH) or T[yy][xx] in cls: return True
    return False
beach = [[T[y][x] == G_ and near(x, y, (W_,), 2) for x in range(MW)] for y in range(MH)]
for y in range(MH):
    for x in range(MW):
        if beach[y][x]: T[y][x] = S_
def fill(x0, x1, y0, y1, c, only=(G_,)):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if T[y][x] in only: T[y][x] = c
# reservas: cercas, casa, celeiro de graos
PLOTS = [(5, 13, 16, 24), (20, 13, 30, 24)]
for x0, y0, x1, y1 in PLOTS: fill(x0, x1, y0, y1, X_)
HOUSE = (6, 28); fill(5, 10, 27, 31, X_)
GRAN = (22, 28); fill(21, 27, 27, 34, X_)
# trilhas
fill(17, 18, 12, 47, S_)           # eixo norte-sul (para na mata)
fill(4, 33, 25, 26, S_)            # rua dos campos ate a praia leste
fill(7, 8, 31, 33, S_, only=(G_, X_)); fill(7, 16, 32, 33, S_)   # porta da casa ate o eixo
fill(11, 16, 36, 37, S_)           # pracinha da estela
# mata ao norte com a boca do bosque (Spring Grove)
def col(x0, y0, y1):
    for y in range(y0, y1 + 1):
        if all(0 <= x < MW and T[y][x] == G_ and not near(x, y, (S_, W_), 1) for x in (x0, x0 + 1)):
            T[y][x0] = T[y][x0 + 1] = F_
for i, cx in enumerate(list(range(1, 17, 2)) + list(range(19, 35, 2))):   # mata densa; trilha de grama 17-18
    for y in range(5, 11 + i % 2):
        if all(0 <= x < MW and T[y][x] == G_ and not near(x, y, (S_, W_), 1) for x in (cx, cx + 1)):
            T[y][cx] = T[y][cx + 1] = F_
# pomar ao sul (colunas curtas)
for i, cx in enumerate(range(5, 16, 3)): col(cx, 40 + i % 2, 44)
for i, cx in enumerate(range(21, 31, 3)): col(cx, 40 + (i + 1) % 2, 44)
g = Grid(MW, MH, pack_block(JOHTO['water'], 0, 1))
for y in range(MH):
    for x in range(MW):
        t = T[y][x]
        if t == W_: continue
        if t == S_: g.set(x, y, pick_sand(T, x, y, grassy=('G', 'F', 'X')))
        elif t == F_: g.set(x, y, pick_forest(T, x, y), 1)
        else:
            b = tree_base(T, x, y)
            g.set(x, y, b, 1) if b else g.set(x, y, JOHTO['grass'])
# boca do bosque: a trilha termina entre as arvores
WARP_GROVE = (17, 5)
WARP_GROVE2 = (18, 5)
# cercas dos campos (pecas do primario, como na fazenda do hub) com plantacao = capim alto
GATES = {(9, 24), (10, 24), (25, 24), (26, 24), (16, 18), (20, 18)}
for x0, y0, x1, y1 in PLOTS:
    for x in range(x0, x1 + 1):
        g.set(x, y0, 0xe7, 1); g.set(x, y1, 0xd6 if (x - x0) % 2 == 0 else 0xd7, 1)
    for y in range(y0, y1 + 1):
        g.set(x0, y, 0xf4, 1); g.set(x1, y, 0xf5, 1)
    g.set(x0, y0, 0xec, 1); g.set(x1, y0, 0xed, 1); g.set(x1, y1, 0xfd, 1)
    for y in range(y0 + 1, y1):
        for x in range(x0 + 1, x1): g.set(x, y, 10)
for p in GATES: g.set(*p, JOHTO['grass'])
# espantalho-pedra no meio de cada campo: pedra (167) como marco
for p in ((9, 19), (25, 19)): g.set(*p, 167, 1)
stamp(g, 'Route39', 18, 13, 4, 3, HOUSE[0], HOUSE[1])       # casa do guardiao (porta em +1,+2)
DOOR = (HOUSE[0] + 1, HOUSE[1] + 2)
stamp(g, 'Route39', 11, 19, 5, 6, GRAN[0], GRAN[1])         # celeiro de graos (sem porta)
for x in range(GRAN[0], GRAN[0] + 5): g.set(x, GRAN[1] + 6, 0xd9)   # terreiro
STELE = (12, 35); g.set(*STELE, 167, 1)                      # estela antiga (pedra)
SIGNS = {'fields': (16, 27), 'grove': (16, 12)}
for p in SIGNS.values(): g.set(*p, 2, 1)
# bolsao atras da casa do guardiao (passa pelo vao entre a casa e a cerca)
pier_top = max(y for y in range(MH) if T[y][17] == S_) + 1
for y in range(pier_top, pier_top + 2):
    for i, x in enumerate((16, 17, 18)): g.set(x, y, JOHTO['pier'][i])
blocks = g.flat()
def free_near(x, y):
    for r in range(4):
        for dy in range(-r, r + 1):
            for dx in range(-r, r + 1):
                v = blocks[(y + dy) * MW + x + dx]
                if not (v >> 11 & 1) and (v >> 12) != 1: return (x + dx, y + dy)
SIT = free_near(13, 42)
OBJ = [
    o('JESSIE', 'JESSIE', 28, 33, 'LEFT', 'HarvestFields_EventScript_JessieJames', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('JAMES', 'JAMES', 28, 34, 'LEFT', 'HarvestFields_EventScript_JessieJames', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('LENORA', 'LENORA', 12, 36, 'UP', 'HarvestFields_EventScript_Lenora'),
    o('FARMHAND', 'MAN_3', 22, 18, 'DOWN', 'HarvestFields_EventScript_Farmhand', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('LASS', 'LASS', 6, 21, 'RIGHT', 'HarvestFields_EventScript_Lass', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('ITEM_REVIVE', 'ITEM_BALL', 5, 33, script='HarvestFields_EventScript_ItemRevive'),
    o('ITEM_SITRUS', 'ITEM_BALL', *SIT, script='HarvestFields_EventScript_ItemSitrusBerry'),
    o('ITEM_FIELD', 'ITEM_BALL', 29, 14, script='HarvestFields_EventScript_ItemSoftSand'),
    o('ITEM_BEACH', 'ITEM_BALL', 9, 4, script='HarvestFields_EventScript_ItemPearl'),
]
bad = check_objects(blocks, MW, OBJ)
d = bfs(blocks, MW, MH, (17, pier_top - 1))
reach = {ob['local_id']: any((ob['x'] + a, ob['y'] + b) in d for a, b in ((0, 1), (1, 0), (-1, 0), (0, -1), (0, 0))) for ob in OBJ}
reach['WARP_GROVE'] = WARP_GROVE in d;  reach['DOOR_KEEPER'] = (DOOR[0], DOOR[1] + 1) in d
write_blocks(os.path.join(D, 'map.bin'), g.b)
write_blocks(os.path.join(D, 'border.bin'), [[pack_block(JOHTO['water'], 0, 1)] * 2] * 2)
PJ = load_tileset('primary', 'johto_general'); SF = load_tileset('secondary', 'route38_farmland')
write_png(os.path.join(D, 'dia.png'), render_blocks(blocks, MW, MH, PJ, SF, objects=OBJ), 2)
write_png(os.path.join(D, 'colisao.png'), render_blocks(blocks, MW, MH, PJ, SF, objects=OBJ, overlay=True,
          marks=[(WARP_GROVE, (200, 120, 255)), (WARP_GROVE2, (200, 120, 255)), (DOOR, (200, 120, 255))]), 2)
info = dict(map='AbundanceIsle_HarvestFields', ingame='Harvest Fields', w=MW, h=MH,
    primary='gTileset_Johto_General', secondary='gTileset_Route38_Farmland', map_type='MAP_TYPE_ROUTE',
    warps=[dict(x=DOOR[0], y=DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_KEEPER_HOUSE', dest_warp_id='0', nota='porta da casa do guardiao'),
           dict(x=WARP_GROVE[0], y=WARP_GROVE[1], dest_map='MAP_ABUNDANCE_ISLE_SPRING_GROVE', dest_warp_id='0', nota='boca do bosque ao norte; chega em (16,36) no Spring Grove'),
           dict(x=WARP_GROVE2[0], y=WARP_GROVE2[1], dest_map='MAP_ABUNDANCE_ISLE_SPRING_GROVE', dest_warp_id='0', nota='segunda celula da boca do bosque')],
    connections=[dict(direction='east', map='MAP_ABUNDANCE_ISLE', offset=0, nota='borda leste e mar (x 34..39); o hub tem mar na borda oeste. Chega-se de Surf. Tambem ha um cais ao sul (y %d) para barco' % pier_top)],
    objects=OBJ,
    explorar=['Dois campos cercados de plantacao (capim alto com encontros), cada um com duas porteiras: da para cortar caminho por dentro ou rodear.',
              'Jessie e James escondidos atras do celeiro de graos, "tramando roubar a colheita e os lendarios": batalha dupla opcional; depois do ato 5 voltam com outro plano (revanche).',
              'Lenora diante da estela antiga na pracinha: le a inscricao das Forcas da Natureza e pede ao jogador que veja o santuario do hub; depois do Landorus, batalha opcional.',
              'Casa do guardiao (oeste), com Revive no gramado ao lado.',
              'Pomar ao sul: Sitrus Berry entre as fileiras.',
              'Canto nordeste do campo leste: Soft Sand. Pearl na beira norte, atras do pinheiral.',
              'Pinheiral ao norte: a trilha de grama entre as arvores leva a boca do Spring Grove (placa no comeco). Da para contornar o pinheiral pela beira da praia, onde fica o Pearl.',
              'Treinadores: peao no campo leste, Lass no campo oeste.'],
    historia='Atos 1 e 5: casa do guardiao (pergaminhos, Reveal Glass) e passagem para o Spring Grove do Enamorus; Jessie e James sao o alivio comico.',
    estados=dict(dia='Dia, com todos os NPCs.'),
    conferido='check_objects=%s; BFS do cais alcanca: %s' % (bad, reach))
json.dump(info, open(os.path.join(D, 'info.json'), 'w'), indent=1, ensure_ascii=False)
print(info['conferido'])
