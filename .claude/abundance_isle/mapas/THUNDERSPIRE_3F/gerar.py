import sys, os, json
from collections import deque
sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from torre_kit import *
OUT = os.path.dirname(os.path.abspath(__file__))
W, H = 29, 25
g = andar(W, H, exit_mat=False)
ARRIVE = (26, 22); g.set(*ARRIVE, 0x40d, 0, 3)          # chega do 2F (desce de volta)
# paredes de buraco que separam as quatro salas; cada vao tem um portao de entulho
poco(g, 2, 15, 5, 17); poco(g, 7, 15, 27, 17)           # S | resto      vao A em x=6
poco(g, 13, 4, 15, 11); poco(g, 13, 13, 15, 15)         # W | E,N        vao B em y=12
poco(g, 16, 8, 19, 10); poco(g, 21, 8, 27, 10)          # E | N          vao C em x=20
GATES = {'A': (6, 16), 'B': (14, 12), 'C': (20, 9), 'D': (17, 6)}
UP = (17, 5); escada_sobe(g, *UP)                       # para o cume
for p in ((16, 5), (18, 5), (16, 6), (18, 6)): g.set(*p, BOULDER, 1, 0)   # nicho da escada
# para-raios: os "pilares de dragao" (estatua) — interage-se na base
RODS = {'Earth': (4, 20), 'Wind': (3, 6), 'Thunder': (26, 13), 'Ideal': (26, 5)}
for p in RODS.values(): estatua(g, *p)
TOGGLE = {'Earth': 'A', 'Wind': 'AB', 'Thunder': 'BC', 'Ideal': 'CD'}
MURAL = (10, 18)
g.set(*MURAL, 0x249, 1, 0); g.set(MURAL[0], MURAL[1] - 1, 0x40f, 0, 3)
for p in ((12, 21), (20, 19), (8, 12), (24, 13), (22, 4)): g.set(*p, SCORCH, 1, 0)
HIDDEN = (2, 4)                                          # item escondido no canto da sala oeste
def blocks_for(open_gates):
    b = g.flat()
    for k, (x, y) in GATES.items():
        b[y * W + x] = pack_block(FLOOR, 0, 3) if k in open_gates else pack_block(BOULDER, 1, 0)
    return b
def reach(open_gates, start):
    b = blocks_for(open_gates)
    walk = lambda x, y: not (b[y * W + x] >> 11 & 1) and (b[y * W + x] >> 12) in (3, 0)
    return slide_reach(start, walk, lambda x, y: False, W, H)
def can_use(d, p):   # alcanca a base pela frente (de baixo)
    return (p[0], p[1] + 1) in d
# ---- busca de estados: (portoes abertos, celula de referencia)
start = (frozenset(), ARRIVE)
seen = {start: None}; q = deque([start]); goal = None
while q:
    st = q.popleft(); gates, pos = st
    d = reach(gates, pos)
    if (UP[0], UP[1] + 1) in d: goal = st; break
    for rod, p in RODS.items():
        if can_use(d, p):
            ng = frozenset(set(gates) ^ set(TOGGLE[rod]))
            ns = (ng, (p[0], p[1] + 1))
            if ns not in seen: seen[ns] = (st, rod); q.append(ns)
seq = []
s = goal
while seen[s]: s, rod = seen[s][0], seen[s][1]; seq.append(rod)
seq = seq[::-1]
# sem trava: de todo estado alcancado da para voltar a chegada
def back_ok(st):
    gates, pos = st
    sn = {st}; qq = deque([st])
    while qq:
        gg, pp = qq.popleft(); d = reach(gg, pp)
        if ARRIVE in d: return True
        for rod, p in RODS.items():
            if can_use(d, p):
                ns = (frozenset(set(gg) ^ set(TOGGLE[rod])), (p[0], p[1] + 1))
                if ns not in sn: sn.add(ns); qq.append(ns)
    return False
softlock = [sorted(k[0]) for k in seen if not back_ok(k)]
print('ordem minima:', seq, '| estados explorados:', len(seen), '| travas:', softlock)
P = 'LOCALID_THUNDERSPIRE_3F_'
OBJ = [obj(P, 'GRUNT_1', 'SCIENTIST_1', 8, 7, 'RIGHT', 'Thunderspire3F_EventScript_Grunt5', 'TRAINER_TYPE_NORMAL', '4'),
       obj(P, 'GRUNT_2', 'SCIENTIST_1', 18, 12, 'DOWN', 'Thunderspire3F_EventScript_Grunt6', 'TRAINER_TYPE_NORMAL', '3'),
       obj(P, 'GRUNT_3', 'SCIENTIST_1', 21, 5, 'LEFT', 'Thunderspire3F_EventScript_Grunt7', 'TRAINER_TYPE_NORMAL', '3'),
       obj(P, 'ITEM_EAST', 'ITEM_BALL', 27, 11, script='Thunderspire3F_EventScript_ItemCellBattery')]
BG = [{'type': 'sign', 'x': MURAL[0], 'y': MURAL[1], 'script': 'Thunderspire3F_EventScript_Mural', 'nota': 'mural: "First the earth wakes, then the wind rises, then the thunder falls; only then may the ideal be struck."'}] + \
     [{'type': 'sign', 'x': p[0], 'y': p[1], 'script': 'Thunderspire3F_EventScript_Rod' + r, 'nota': 'para-raios %s: alterna portões %s' % (r, '+'.join(TOGGLE[r]))} for r, p in RODS.items()] + \
     [{'type': 'hidden_item', 'x': HIDDEN[0], 'y': HIDDEN[1], 'item': 'ITEM_MAGNET', 'flag': 'a alocar'}]
gates_final = set()
for r in seq: gates_final ^= set(TOGGLE[r])
b0 = blocks_for(set()); bf = blocks_for(gates_final)
d0 = reach(set(), ARRIVE)
print('bloqueio', check_objects(b0, W, OBJ), 'item leste (precisa de C? )', (27, 12) in d0)
write_blocks(os.path.join(OUT, 'map.bin'), [b0[y * W:(y + 1) * W] for y in range(H)])
write_blocks(os.path.join(OUT, 'border.bin'), [[pack_block(0, 1, 0)] * 2] * 2)
L = load_layout('BurnedTower_1F')
def R(b, objs, overlay=False, marks=(), night=0.0):
    cv = render_blocks(b, W, H, L['prim'], L['sec'], overlay=overlay, marks=marks, night=night)
    for ob in sorted(objs, key=lambda q: q['y']): draw_object(cv, ob, night > .5)
    return cv
mk = [(ARRIVE, (200, 120, 255)), (UP, (200, 120, 255))] + [(p, (255, 230, 80)) for p in GATES.values()] + \
     [(p, (80, 230, 120)) for p in RODS.values()] + [(HIDDEN, (255, 120, 200)), (MURAL, (120, 200, 255))]
write_png(os.path.join(OUT, 'dia.png'), R(b0, OBJ), 2)
write_png(os.path.join(OUT, 'estado.png'), R(bf, [o_ for o_ in OBJ if 'ITEM' in o_['local_id']], night=0.6), 2)
write_png(os.path.join(OUT, 'colisao.png'), R(b0, OBJ, True, mk), 2)
info = {"map": "THUNDERSPIRE_3F", "ingame": "Thunderspire 3F", "w": W, "h": H,
        "primary": "gTileset_Johto_Building", "secondary": "gTileset_BurnedTower", "map_type": "MAP_TYPE_INDOOR",
        "warps": [{"x": ARRIVE[0], "y": ARRIVE[1], "dest_map": "MAP_THUNDERSPIRE_2F", "dest_warp_id": "1", "nota": "desce ao 2F (escada do 2F em 26,22)"},
                  {"x": UP[0], "y": UP[1], "dest_map": "MAP_THUNDERSPIRE_SUMMIT", "dest_warp_id": "0", "nota": "sobe ao cume; chegada em (15,34)"}],
        "connections": [], "objects": OBJ, "bg_events": BG,
        "puzzle": {"portoes": GATES, "para_raios": RODS, "alterna": TOGGLE, "ordem": seq,
                   "implementacao": "portão fechado = 0x407 (entulho, bloqueado); aberto = 0x400 (chão). Cada para-raios faz setmetatile nos portões que alterna + special DrawWholeMapView; estado em 1 VAR (bits A-D) restaurado no ON_LOAD.",
                   "estados_explorados": len(seen), "travas": softlock},
        "explorar": ["Quebra-cabeça dos para-raios: quatro pilares (Terra, Vento, Trovão, Ideal), um por sala; cada um alterna portões de entulho entre as salas.",
                     "Mural ao lado da chegada dá a ordem em verso: terra, vento, trovão e, por último, o ideal — o mesmo que Volkner e Elesa contaram sobre os raios na Thunder Ridge.",
                     "Ordem certa: Terra abre a sala oeste; Vento fecha a passagem de volta e abre a leste; Trovão fecha a leste e abre a norte; Ideal abre o nicho da escada do cume. Tocar fora de ordem só desfaz um passo — não há trava (provado por busca de estados).",
                     "Magnet escondido no canto noroeste da sala oeste; Cell Battery na ponta da sala leste.",
                     "Três recrutas do Plasma, um por sala."],
        "historia": "O andar onde Ghetsis canaliza os raios para o cume: ligar os para-raios na ordem da lenda desvia a energia e abre o caminho até ele.",
        "estados": {"dia": "Todos os portões fechados (início).", "estado": "Depois da sequência certa: só o portão D (nicho da escada) aberto, recrutas vencidos."},
        "conferido": "check_objects sem bloqueio; busca de estados (portões × posição): ordem mínima %s, %d estados, travas %s" % (seq, len(seen), softlock)}
json.dump(info, open(os.path.join(OUT, 'info.json'), 'w'), indent=1, ensure_ascii=False)
