import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__))
SRC = 'EcruteakCity_House2'                        # johto_building + house_lab: chao de madeira, tapete escuro, livro aberto na mesa
L = src(SRC)
g = Grid(L['w'], L['h'], 0); stamp(g, SRC, 0, 0, L['w'], L['h'], 0, 0)
import shutil; shutil.copy(os.path.join(ROOT, L['info']['border_filepath']), os.path.join(P, 'border.bin'))
SHELF = ((0x13d, 0x13e), (0x145, 0x146), (0x14d, 0x14e))      # estante verde 2x3 (topo, corpo bloqueados; sombra andavel)
def shelf(x):
    for dy, (a, b) in enumerate(SHELF):
        coll = 1 if dy < 2 else 0
        g.set(x, dy, a, coll); g.set(x + 1, dy, b, coll)
shelf(0); shelf(7)                                  # duas estantes a mais (no lugar da geladeira e do armario): biblioteca de lore
DOOR = (4, 8)
objs = [o('ELDER', 'OLD_MAN', 5, 4, 'RIGHT', 'ElderHouse_EventScript_Elder'),
        o('GRANDDAUGHTER', 'LITTLE_GIRL', 2, 6, 'UP', 'ElderHouse_EventScript_Granddaughter'),
        o('ELDER_BELL', 'OLD_MAN', 9, 7, 'UP', 'ElderHouse_EventScript_ElderBellTime')]
BG = [dict(type='sign', x=0, y=1, script='ElderHouse_EventScript_BookYearWithoutHarvest', nota='"The Year Without Harvest": a estrela gelada que caiu no mar e o inverno que durou um verão inteiro'),
      dict(type='sign', x=7, y=1, script='ElderHouse_EventScript_BookForcesOfNature', nota='livro dos gênios do vento e do trovão e do Senhor da Terra Fértil'),
      dict(type='sign', x=9, y=1, script='ElderHouse_EventScript_BookHeraldOfSpring', nota='o Arauto da Primavera que vem pelo mar'),
      dict(type='sign', x=10, y=7, script='ElderHouse_EventScript_BellRope', nota='corda do sino (só texto: o sino fica no telhado)')]
b = g.flat(); d = bfs(b, g.w, g.h, DOOR)
bad = [x['local_id'] for x in objs if not alcanca(d, x)]; assert not bad, bad
bad = [(s['x'], s['y']) for s in BG if not alcanca(d, s)]; assert not bad, bad
info = dict(map='AbundanceIsle_ElderHouse', ingame="Elder's House", primary=L['info']['primary_tileset'], secondary=L['info']['secondary_tileset'],
    map_type='MAP_TYPE_INDOOR',
    warps=[dict(x=DOOR[0], y=DOOR[1], dest_map='MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE', dest_warp_id='4', nota='porta da casa 2 da Windswept Cape (14,23)')],
    connections=[], bg_events=BG,
    explorar=['O ancião conta "The Year Without Harvest": há muito tempo uma estrela gelada caiu no mar perto da ilha e um inverno durou o verão inteiro; desde então ninguém anda nos campos em noite de neve (eco de Lacunosa e do meteorito do Kyurem).',
              'Às 18h ele não está à mesa: fica junto à corda do sino (ELDER_BELL) e toca o sino do cabo; quem fala com ele nessa hora ouve por que o sino avisa a noite.',
              'Três estantes com livros de lore lidos como placas: o ano sem colheita, os gênios do vento e do trovão e o Senhor da Terra Fértil, e o Arauto da Primavera.',
              'A neta conta que viu "olhos amarelos" no gelo da cratera (pista do Kyurem, sem spoiler).'],
    historia="Casa do ancião do cabo. Liga o inverno do Ghetsis à lenda antiga da estrela gelada: a ilha já viveu isso antes, e é assim que o jogador entende de onde vem o frio da Frostfall Crater.",
    estados={'dia': 'De dia: ancião à mesa com o livro aberto, neta perto da estante. (ELDER e ELDER_BELL são o mesmo NPC em horários diferentes.)'},
    conferido='Layout de EcruteakCity_House2 com duas estantes extras (peças 13d/13e/145/146/14d/14e da própria casa); BFS da porta até NPCs e às 4 placas; check_objects.')
entregar(P, g, L['prim'], L['sec'], info, objs)
