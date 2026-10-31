import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__)); sys.path.insert(0, P)
import arte_aviao; from desenho import reduzir
SRC = 'GoldenrodCity_UndergroundStorage'           # johto_building + goldenrod_underground_storage (galpao com caixotes)
MW, MH = 18, 14
FL, SH = 0x401, 0x402
g = Grid(MW, MH, pack_block(0, 1))
for x in range(MW):
    g.set(x, 0, 0x409, 1); g.set(x, 1, 0x411, 1)
g.set(0, 0, 0x408, 1); g.set(MW - 1, 0, 0x40c, 1)
for y in range(1, MH - 1):
    g.set(0, y, 0x410, 1); g.set(MW - 1, y, 0x414, 1)
    for x in range(1, MW - 1): g.set(x, y, SH if x == 1 else FL, 0)
for x in range(MW): g.set(x, MH - 1, 0x8, 1)
DOOR = (4, MH - 2)
g.set(4, MH - 2, 0xe7, 0)       # capacho (primario Johto_Building)
g.set(4, MH - 1, 0x1b, 1)
def crate(x, y):
    for (dx, dy), m in zip(((0, 0), (1, 0), (0, 1), (1, 1)), (0x490, 0x491, 0x498, 0x499)): g.set(x + dx, y + dy, m, 1)
    if x + 2 < MW - 1 and (g.b[y + 1][x + 2] & 0x7ff) == FL: g.set(x + 2, y + 1, 0x403, 0)
for x, y in ((1, 2), (1, 4), (14, 2), (14, 4), (14, 9), (12, 9), (1, 9)): crate(x, y)
PLANE = (6, 3)                                      # 4x3 metatiles: desenho novo (4 propostas)
for y in range(3):
    for x in range(4): g.set(PLANE[0] + x, PLANE[1] + y, FL, 1)
write_blocks(os.path.join(P, 'border.bin'), [[pack_block(0, 1)] * 2] * 2)
grounded = [o('SKYLA', 'SKYLA', 7, 7, 'UP', 'SkylaHangar_EventScript_SkylaGrounded'),
            o('MECHANIC', 'MAN_4', 10, 4, 'LEFT', 'SkylaHangar_EventScript_Mechanic'),
            o('ITEM_CARGO', 'ITEM_BALL', 3, 8, script='SkylaHangar_EventScript_ItemZoomLens')]
ready = [o('SKYLA_READY', 'SKYLA', 5, 10, 'DOWN', 'SkylaHangar_EventScript_SkylaFlight'),
         o('MECHANIC', 'MAN_4', 10, 4, 'LEFT', 'SkylaHangar_EventScript_Mechanic')]
b = g.flat(); d = bfs(b, MW, MH, DOOR)
bad = [x['local_id'] for x in grounded + ready if not alcanca(d, x)]; assert not bad, bad
L = src(SRC)
ART = [(c, n, reduzir(f())) for c, n, f in arte_aviao.PROPOSTAS]
def render(objs, art=0, overlay=False):
    cv = render_blocks(b, MW, MH, L['prim'], L['sec'], overlay=overlay, marks=[(DOOR, (200, 120, 255))] if overlay else ())
    ART[art][2].over(cv, PLANE[0] * 16, PLANE[1] * 16)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob)
    return cv
for i, (c, n, art) in enumerate(ART):
    write_png(os.path.join(P, 'props', 'no_mapa_%s.png' % c), render(grounded, i), 3)
info = dict(map='AbundanceIsle_SkylaHangar', ingame="Skyla's Hangar", primary='gTileset_Johto_Building', secondary='gTileset_Goldenrod_Underground_Storage',
    map_type='MAP_TYPE_INDOOR',
    warps=[dict(x=DOOR[0], y=DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE', dest_warp_id='3', nota='porta da casa 1 da Windswept Cape (21,18)')],
    connections=[],
    explorar=['Missão "Grounded": o avião de carga da Skyla está preso no galpão pela tempestade; ela não decola enquanto Tornadus e Thundurus brigarem no céu.',
              'Mecânico conserta o motor e comenta que a neve congelou o combustível (pista do frio artificial da cratera).',
              'Caixotes de carga de Unova pelo galpão; Zoom Lens atrás de uma pilha.',
              'Depois do ato 3, Skyla espera na porta: oferece levar o jogador de volta a Johto num voo (viagem rápida ilha <-> Johto) e uma batalha opcional.'],
    historia='Galpão da Skyla no cabo. Enquanto a tempestade durar o avião fica preso ("Grounded"); quando o céu limpa ela vira o transporte de volta a Johto.',
    estados={'dia': 'Ato 1-2: Skyla olhando o avião preso, mecânico trabalhando.', 'estado': 'Depois do ato 3: Skyla pronta para voar, perto da porta.'},
    conferido='Peças do galpão de GoldenrodCity_UndergroundStorage (paredes 408/409/40c/410/411/414, chão 401/402, caixotes 490/491/498/499, sombra 403); capacho do primário Johto_Building como nas casas; BFS da porta até todos os NPCs e itens; check_objects.',
    desenho_novo=dict(nome='avião da Skyla', area='4x3 metatiles em (6,3)', propostas=[[c, n] for c, n, _ in ART], pasta='props/'))
os.makedirs(P, exist_ok=True)
write_blocks(os.path.join(P, 'map.bin'), g.b)
write_png(os.path.join(P, 'dia.png'), render(grounded), 2)
write_png(os.path.join(P, 'estado.png'), render(ready, 3 if False else 0), 2)
write_png(os.path.join(P, 'colisao.png'), render(grounded, overlay=True), 2)
info.update(w=MW, h=MH, objects=grounded + [x for x in ready if x['local_id'] == 'SKYLA_READY'])
json.dump(info, open(os.path.join(P, 'info.json'), 'w'), indent=1, ensure_ascii=False)
print('hangar check_objects:', check_objects(b, MW, grounded + ready))
