import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from torre_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
W, H = 29, 25
g = andar(W, H)
ENTRY = [(x, H - 3) for x in range(W) if (g.b[H - 3][x] & 0x7ff) in (0x425, 0x426, 0x427)]
DOOR = ENTRY[1] if len(ENTRY) > 1 else (16, H - 3)
# buracos abertos pelos raios: obrigam a rodear pelas pontes de tabua
poco(g, 6, 15, 24, 19)        # grande, logo a frente da entrada
poco(g, 2, 9, 10, 13)         # esquerda
poco(g, 13, 8, 22, 12)        # centro: ilha de tabua no meio (item)
poco(g, 13, 4, 26, 6)         # fundo direito
poco(g, 24, 8, 26, 16)        # coluna direita
# ilha do item: o centro do poco central volta a ser chao, ligado so por uma ponte estreita vinda de cima
for y in range(9, 12):
    for x in range(16, 20): g.set(x, y, FLOOR, 0, 3)
for x in range(16, 20): g.set(x, 8, FLOOR, 0, 3)        # abre o topo da ilha
g.set(15, 9, 0x412, 1, 0); g.set(20, 9, 0x410, 1, 0)
for x in range(16, 20): g.set(x, 7, FLOOR, 0, 3); g.set(x, 6, FLOOR, 0, 3); g.set(x, 5, FLOOR, 0, 3); g.set(x, 4, FLOOR, 0, 3)
# entulho e marcas de queimado
for p in ((3, 15), (3, 16), (4, 20), (25, 20), (11, 6), (12, 14), (22, 14)): g.set(*p, BOULDER, 1, 0)
for p in ((8, 6), (5, 20), (23, 21), (21, 13)): g.set(*p, SCORCH, 1, 0)
# estatuas de dragao ladeando a entrada (os herois gemeos)
for x in (DOOR[0] - 4, DOOR[0] + 4): estatua(g, x, H - 3)
UP = (3, 5); escada_sobe(g, *UP)
P = 'LOCALID_THUNDERSPIRE_1F_'
OBJ = [obj(P, 'CHEREN', 'CHEREN', DOOR[0] - 3, H - 5, 'UP', 'Thunderspire1F_EventScript_Cheren'),
       obj(P, 'ITEM_ISLAND', 'ITEM_BALL', 18, 10, script='Thunderspire1F_EventScript_ItemDragonScale'),
       obj(P, 'ITEM_CORNER', 'ITEM_BALL', 26, 21, script='Thunderspire1F_EventScript_ItemZinc'),
       obj(P, 'GRUNT_1', 'SCIENTIST_1', 9, 21, 'RIGHT', 'Thunderspire1F_EventScript_Grunt1', 'TRAINER_TYPE_NORMAL', '4'),
       obj(P, 'GRUNT_2', 'SCIENTIST_1', 11, 7, 'DOWN', 'Thunderspire1F_EventScript_Grunt2', 'TRAINER_TYPE_NORMAL', '3')]
d = alcance(g, DOOR)
rep = {'escada': perto(d, UP), 'item ilha': perto(d, (18, 10)), 'item canto': perto(d, (26, 21))}
print('bloqueio', check_objects(g.flat(), W, OBJ), rep)
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0, 1, 0)] * 2] * 2)
render(g, OBJ, OUT, 'dia.png')
render(g, OBJ, OUT, 'colisao.png', overlay=True, marks=[(DOOR, (200, 120, 255)), (UP, (200, 120, 255))])
info = {"map": "THUNDERSPIRE_1F", "ingame": "Thunderspire 1F", "w": W, "h": H,
        "primary": "gTileset_Johto_Building", "secondary": "gTileset_BurnedTower", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": DOOR[0], "y": DOOR[1], "dest_map": "MAP_THUNDER_RIDGE", "dest_warp_id": "1", "nota": "entrada (tapete); Thunder Ridge porta em (18,10)"},
                  {"x": UP[0], "y": UP[1], "dest_map": "MAP_THUNDERSPIRE_2F", "dest_warp_id": "0", "nota": "escada para o 2F"}],
        "connections": [], "objects": OBJ,
        "explorar": ["Buracos abertos pelos raios cortam o andar: a escada fica no canto oposto à entrada e é preciso contornar pelos corredores de tábua.",
                     "Ilha de tábua no meio do buraco central, alcançada por uma ponte estreita que desce do fundo: Dragon Scale.",
                     "Zinc no canto sudeste, atrás do entulho.",
                     "Estátuas de dragão ladeando a entrada (os heróis gêmeos).",
                     "Cheren (professor) estuda as estátuas e conta a lenda dos heróis gêmeos e das pedras Clara e Escura; volta a falar depois do ato 4.",
                     "Dois recrutas do Plasma no caminho."],
        "historia": "Primeiro andar da torre em ruínas que leva ao cume. Os recrutas seguram o jogador enquanto Ghetsis sobe; Cheren dá o contexto da Pedra Escura.",
        "estados": {"dia": "Ato 4: recrutas e Cheren."},
        "conferido": "check_objects sem bloqueio; BFS da entrada: %s" % json.dumps(rep)}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
