import sys, os, json
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from torre_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
W, H = 29, 25
g = andar(W, H, exit_mat=False)
DOWN = (3, 5); g.set(*DOWN, 0x40d, 0, 3)          # buraco/escada que desce ao 1F (chegada)
# andar quase todo desabado: um caminho em S por cima dos buracos
poco(g, 6, 4, 26, 8)
poco(g, 2, 10, 22, 14)
poco(g, 6, 16, 26, 19)
# atalho: o S tem uma passagem estreita bloqueada por um pedregulho de Strength
SHORT = (24, 12)
for y in range(10, 15): g.set(24, y, FLOOR, 0, 3) if False else None
# canto fantasma (Alister) e entulho
for p in ((2, 8), (4, 8), (27, 15), (25, 21), (9, 21)): g.set(*p, BOULDER, 1, 0)
for p in ((3, 17), (24, 12), (5, 21), (16, 21)): g.set(*p, SCORCH, 1, 0)
UP = (26, 22); escada_sobe(g, *UP)                  # para o cume
for x in (12, 20): estatua(g, x, 9) if False else None
P = 'LOCALID_THUNDERSPIRE_2F_'
OBJ = [obj(P, 'ALISTER', 'ALISTER', 3, 21, 'RIGHT', 'Thunderspire2F_EventScript_Alister'),
       obj(P, 'ROCK', 'BREAKABLE_ROCK', 27, 8, script='EventScript_RockSmash'),
       obj(P, 'ITEM_LEDGE', 'ITEM_BALL', 27, 4, script='Thunderspire2F_EventScript_ItemSpellTag'),
       obj(P, 'ITEM_GAP', 'ITEM_BALL', 2, 15, script='Thunderspire2F_EventScript_ItemDragonFang'),
       obj(P, 'GRUNT_3', 'SCIENTIST_1', 14, 15, 'LEFT', 'Thunderspire2F_EventScript_Grunt3', 'TRAINER_TYPE_NORMAL', '5'),
       obj(P, 'GRUNT_4', 'SCIENTIST_1', 18, 20, 'LEFT', 'Thunderspire2F_EventScript_Grunt4', 'TRAINER_TYPE_NORMAL', '5')]
boulder = {(27, 8)}
d = alcance(g, DOWN, extra_block=boulder)
rep = {'escada cume': perto(d, UP), 'item beirada': perto(d, (27, 4)), 'item vao': perto(d, (2, 15)), 'alister': perto(d, (3, 21))}
print('bloqueio', check_objects(g.flat(), W, OBJ), rep)
for y in range(H):
    print(''.join('o' if (x, y) in d else ('#' if g.b[y][x] >> 11 & 1 or g.b[y][x] >> 12 == 4 else '.') for x in range(W)))
write_blocks(os.path.join(OUT, 'map.bin'), g.b)
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0, 1, 0)] * 2] * 2)
render(g, OBJ, OUT, 'dia.png')
render(g, [q for q in OBJ if 'GRUNT' not in q['local_id']], OUT, 'estado.png', night=0.7)
render(g, OBJ, OUT, 'colisao.png', overlay=True, marks=[(DOWN, (200, 120, 255)), (UP, (200, 120, 255))])
info = {"map": "THUNDERSPIRE_2F", "ingame": "Thunderspire 2F", "w": W, "h": H,
        "primary": "gTileset_Johto_Building", "secondary": "gTileset_BurnedTower", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": DOWN[0], "y": DOWN[1], "dest_map": "MAP_THUNDERSPIRE_1F", "dest_warp_id": "1", "nota": "desce ao 1F (escada do 1F em 3,5)"},
                  {"x": UP[0], "y": UP[1], "dest_map": "MAP_THUNDERSPIRE_3F", "dest_warp_id": "0", "nota": "sobe ao 3F (chega em 26,22)"}],
        "connections": [], "objects": OBJ, "explorar": [], "historia": "",
        "estados": {"dia": "Ato 4: recrutas no caminho em S.", "estado": "Depois (noite): só Alister nas ruínas."},
        "conferido": "check_objects sem bloqueio; BFS da chegada (pedra no lugar): %s" % json.dumps(rep)}
info["explorar"] = ["O andar quase todo desabou: três buracos enormes deixam só um caminho em S da chegada até a escada do 3F.",
                    "Beirada nordeste com Spell Tag, num corredor estreito fechado por uma pedra de Rock Smash.",
                    "Vão entre buracos à esquerda com Dragon Fang.",
                    "Alister, num canto escuro das ruínas: diz ter visto 'a sombra de um dragão negro' dormindo no alto; fica ali como fantasma da torre e conta histórias diferentes à noite.",
                    "Dois recrutas do Plasma no caminho em S."]
info["historia"] = "Andar do meio da torre. Os recrutas são a última barreira antes do Ghetsis; Alister prepara o clima sobrenatural do despertar."
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
