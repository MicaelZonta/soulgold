import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from kitA1 import *
D = os.path.dirname(os.path.abspath(__file__))
W, H = 33, 37
T = [['T'] * W for _ in range(H)]
def clear(x0, x1, y0, y1):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1): T[y][x] = '.'
clear(3, 29, 4, 13)       # G: jardim do Arauto (lago + santuario)
clear(6, 8, 14, 18)       # corredor oeste G <-> M
clear(15, 17, 14, 18)     # atalho central (fechado por arvore de Cut)
clear(3, 29, 19, 24)      # M: clareira dos canteiros (labirinto de sebes)
clear(24, 26, 25, 29)     # corredor leste M <-> L
clear(9, 26, 30, 36)      # L: entrada (vem de Harvest Fields pelo sul)
clear(27, 32, 30, 32)     # bolsao escondido a leste da entrada
g = Grid(W, H, pack_block(0x40e))
warn = ilex_forest(g, T)
for y in range(H):
    for x in range(W):
        if T[y][x] == '.': g.set(x, y, 0x40e if (x + y) % 3 else 0x40f)
# lago do jardim e santuario do bosque (pecas do IlexForest)
stamp(g, 'IlexForest', 26, 17, 9, 6, 5, 6)                 # lago 9x6 em (5..13, 6..11)
stamp(g, 'IlexForest', 31, 34, 3, 3, 21, 4)                # santuario 3x3 em (21..23, 4..6)
SHRINE_FRONT = (22, 7)
# canteiros de flores (primavera) no jardim
FLOW = [(x, y) for y in range(8, 13) for x in range(16, 29) if (x + 2 * y) % 3 == 0 and (x, y) != SHRINE_FRONT]
FLOW += [(x, 12) for x in range(5, 14)] + [(14, y) for y in range(5, 12)]
for x, y in FLOW: g.set(x, y, 0x402 if (x + y) % 2 else 4)
# labirinto de sebes (arbustos redondos 0x438) na clareira M
HEDGE = [(x, 21) for x in range(3, 13)] + [(x, 21) for x in range(15, 23)] + [(12, y) for y in range(19, 21)] \
      + [(x, 23) for x in range(9, 20)] + [(22, y) for y in range(22, 25)] + [(x, 21) for x in range(25, 30)]
for p in HEDGE: g.set(*p, 0x438, 1)
# bolsao: fechado do lado da entrada por sebe com 1 vao escondido atras de arvore
for y in range(30, 33): g.set(27, y, 0x438, 1)
g.set(27, 32, 0x40e)                                         # vao
WARP_S = (16, 36)
blocks = g.flat()
OBJ = [
    o('ENAMORUS', 'OBJ_EVENT_GFX_SPECIES(ENAMORUS)', 17, 9, 'DOWN', 'SpringGrove_EventScript_Enamorus', flag='FLAG_HIDE_SPRING_GROVE_ENAMORUS'),
    o('GARDENIA', 'GARDENIA', 19, 20, 'DOWN', 'SpringGrove_EventScript_Gardenia', ttype='TRAINER_TYPE_NORMAL', sight='3'),
    o('RAMOS', 'RAMOS', 20, 7, 'RIGHT', 'SpringGrove_EventScript_Ramos'),
    o('CUT_TREE', 'CUT_TREE', 16, 15, script='EventScript_CutTree'),
    o('ITEM_SHINY_STONE', 'ITEM_BALL', 12, 11, script='SpringGrove_EventScript_ItemShinyStone'),   # prainha do lago
    o('ITEM_MIRACLE_SEED', 'ITEM_BALL', 4, 22, script='SpringGrove_EventScript_ItemMiracleSeed'),
    o('ITEM_SWEET_APPLE', 'ITEM_BALL', 31, 31, script='SpringGrove_EventScript_ItemSweetApple'),
    o('PICNICKER', 'PICNICKER', 11, 33, 'RIGHT', 'SpringGrove_EventScript_Picnicker', ttype='TRAINER_TYPE_NORMAL', sight='4'),
]
bad = check_objects(blocks, W, OBJ)
d = bfs(blocks, W, H, WARP_S)
reach = {ob['local_id']: (ob['x'], ob['y']) in d or any((ob['x'] + dx, ob['y'] + dy) in d for dx, dy in ((0, 1), (1, 0), (-1, 0), (0, -1)))
         for ob in OBJ}
write_blocks(os.path.join(D, 'map.bin'), g.b)
write_blocks(os.path.join(D, 'border.bin'), [[pack_block(0x418, 1), pack_block(0x419, 1)], [pack_block(0x410, 1), pack_block(0x411, 1)]])
L = load_layout('IlexForest')
cv = render_blocks(blocks, W, H, L['prim'], L['sec'], objects=OBJ)
write_png(os.path.join(D, 'dia.png'), cv, 2)
write_png(os.path.join(D, 'colisao.png'), render_blocks(blocks, W, H, L['prim'], L['sec'], objects=OBJ, overlay=True, marks=[(WARP_S, (200, 120, 255))]), 2)
inverno = [b for b in OBJ if b['local_id'] not in ('ENAMORUS',)]
b2 = list(blocks)
for x, y in FLOW: b2[y * W + x] = pack_block(0x40e)
write_png(os.path.join(D, 'estado.png'), render_blocks(b2, W, H, L['prim'], L['sec'], objects=inverno), 2)
info = dict(map='AbundanceIsle_SpringGrove', ingame='Spring Grove', w=W, h=H,
    primary='gTileset_Johto_NorthWest', secondary='gTileset_IlexForest', map_type='MAP_TYPE_ROUTE',
    warps=[dict(x=WARP_S[0], y=WARP_S[1], dest_map='MAP_ABUNDANCE_ISLE_HARVEST_FIELDS', dest_warp_id='1', nota='saida sul para Harvest Fields (boca do bosque)')],
    connections=[], objects=OBJ,
    explorar=['Caminho em zigue-zague: entrada ao sul -> corredor leste -> labirinto de sebes -> corredor oeste -> jardim; o atalho central so abre com Cut.',
              'Bolsao escondido a leste da entrada, por um vao na sebe: Sweet Apple.',
              'Prainha no canto do lago, atras dos canteiros: Shiny Stone, a pedra da primavera. O lago tem Surf e pesca.',
              'Canto oeste do labirinto: Miracle Seed.',
              'Gardenia (treinadora de planta, batalha opcional com revanche semanal): cuida do bosque e conta que as flores morreram com a neve; depois da primavera diz que "o bosque voltou a respirar".',
              'Ramos (jardineiro, ao lado do santuario): explica o Arauto da Primavera, que chega pelo mar quando o inverno acaba e pune quem fere a vida; e quem manda o jogador falar com o guardiao.',
              'Picnicker na entrada: treinadora comum.',
              'Santuario do bosque (o do Ilex) no fundo do jardim: Enamorus aparece diante dele na primavera.'],
    historia='Ato 5: o jardim estava sem flores no inverno do Ghetsis. Depois do Landorus, as flores abrem e o Enamorus chega ao santuario do bosque para a batalha de captura.',
    estados=dict(dia='Primavera: canteiros floridos, Enamorus no jardim.', estado='Inverno: canteiros vazios, sem Enamorus.'),
    conferido='check_objects=%s; BFS da entrada (16,36) alcanca: %s; avisos de paridade das arvores: %s' % (bad, reach, warn))
json.dump(info, open(os.path.join(D, 'info.json'), 'w'), indent=1, ensure_ascii=False)
print(info['conferido'])
