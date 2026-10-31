"""Truthsand Ruins - Hall of Truth: quem cai pelo sumidouro da Trilha chega numa antecamara;
dali o salao grande, com avenida de estatuas ate o altar em degraus (a piramide da Vajra,
carimbada) onde dorme a Light Stone. Nichos secretos dos dois lados."""
import sys, os, importlib; sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)) + '/..')
from ruina_kit import *
D = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, D + '/props'); sys.path.insert(0, SC)
import arte_light
from desenho import reduzir
P = 'LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_'
r = Ruina(33, 32)
r.room(2, 23, 9, 29)            # antecamara de pouso
r.room(10, 26, 11, 27)          # antecamara -> salao
r.room(6, 4, 26, 22)            # salao grande
r.room(28, 8, 30, 12)           # nicho leste
r.room(27, 10, 27, 11)          # passagem leste
r.room(2, 8, 4, 12)             # nicho oeste
r.room(5, 10, 5, 10)            # fresta oeste (pedra)
r.paint()
# altar: a piramide em degraus da VajraPyramidOutside (11x7), escada no meio (x=16)
stamp(r.g, 'VajraPyramidOutside', 11, 5, 11, 7, 11, 4)
STONE = (16, 6)                 # degrau de cima, diante da porta do altar
r.path([(16, y) for y in range(11, 23)])
for y in (13, 16, 19): r.statue(13, y); r.statue(19, y, right=True)
r.skeleton(7, 20); r.skeleton(25, 6); r.dune(23, 18); r.dune(8, 13)
r.dune(28, 9)                   # duna no nicho leste (decoracao)
LAND = (5, 25); LADDER = (3, 28); r.ladder(*LADDER)
# ---------------- warps
r.warp(*LAND, 'MAP_TRUTHSAND_RUINS_B1F', 4, 'pouso do sumidouro da Trilha (so chegada)')
r.warp(*LADDER, 'MAP_TRUTHSAND_RUINS_B1F', 5, 'escada de volta a Trilha da Verdade')
# ---------------- objetos (estado base + estados do climax e do depois)
BASE = []
def o(*a, **k):
    r.obj(*a, **k); return r.objs[-1]
o(P + 'ROCK', 'BREAKABLE_ROCK', 5, 10, script='EventScript_RockSmash')
o(P + 'ITEM_EAST', 'ITEM_BALL', 30, 12, script='TruthsandRuinsHall_EventScript_ItemFlamePlate')
o(P + 'ITEM_WEST', 'ITEM_BALL', 2, 8, script='TruthsandRuinsHall_EventScript_ItemFireStone')
o(P + 'ITEM_LANDING', 'ITEM_BALL', 9, 29, script='TruthsandRuinsHall_EventScript_ItemRelicVase')
BASE = list(r.objs)
CLIMAX = [o(P + 'LIGHT_STONE', 'LIGHT_STONE', STONE[0], STONE[1], script='TruthsandRuinsHall_EventScript_LightStone'),
          o(P + 'GHETSIS', 'SAGE', 16, 8, 'UP', 'TruthsandRuinsHall_EventScript_Ghetsis'),
          o(P + 'GRUNT_1', 'SCIENTIST_1', 14, 11, 'UP', 'TruthsandRuinsHall_EventScript_Grunt1'),
          o(P + 'GRUNT_2', 'SCIENTIST_1', 18, 11, 'UP', 'TruthsandRuinsHall_EventScript_Grunt2'),
          o(P + 'HILDA', 'HILDA', 15, 14, 'UP', 'TruthsandRuinsHall_EventScript_Hilda'),
          o(P + 'LENORA', 'LENORA', 17, 15, 'UP', 'TruthsandRuinsHall_EventScript_Lenora')]
AFTER = [o(P + 'RESHIRAM', 'SPECIES(RESHIRAM)', 16, 9, 'DOWN', 'TruthsandRuinsHall_EventScript_Reshiram'),
         o(P + 'HILDA_AFTER', 'HILDA', 15, 13, 'UP', 'TruthsandRuinsHall_EventScript_HildaAfter')]
r.bg(9, 4, 'TruthsandRuinsHall_EventScript_MuralTwinHeroes')
r.bg(23, 4, 'TruthsandRuinsHall_EventScript_MuralTruth')
r.bg(16, 5, 'TruthsandRuinsHall_EventScript_AltarDoor')
# ---------------- conferencia (estado base: so pedra, itens)
objs_all = r.objs
r.objs = BASE
T = {'escada': LADDER, 'altar': (16, 7), 'mural_o': (9, 5), 'mural_l': (23, 5)}
T.update({x['local_id'][len(P):]: (x['x'], x['y']) for x in BASE if 'ITEM' in x['local_id']})
sem, bad = r.check([LAND], T); com, _ = r.check([LAND], T, ignore=[P + 'ROCK'])
print('sem Rock Smash:', sem); print('com Rock Smash:', com)
r.objs = objs_all
print('bloqueio:', check_objects(r.blocks(), r.w, objs_all))
# ---------------- renders (a Light Stone desenhada por cima: o sprite novo ainda nao existe no repo)
def stone_over(art):
    def f(cv): art.over(cv, STONE[0] * 16 - 8, STONE[1] * 16 - 16)
    return f
ART = [(c, n, reduzir(fn(), 15)) for c, n, fn in arte_light.PROPOSTAS]
r.render(D + '/dia.png', objs=BASE, extra=stone_over(ART[2][2]))
r.render(D + '/estado.png', objs=BASE + [x for x in CLIMAX if x['local_id'] != P + 'LIGHT_STONE'], extra=stone_over(ART[2][2]), dark=0.25)
r.render(D + '/depois.png', objs=BASE + AFTER)
r.render(D + '/colisao.png', objs=BASE, overlay=True, marks=[((w['x'], w['y']), (200, 120, 255)) for w in r.warps] + [(STONE, (255, 230, 80))])
for c, n, art in ART:                                           # 4 propostas: isolada e no mapa
    write_png(D + '/props/light_stone_%s.png' % c, art.rgb((232, 232, 236)), 4)
    r.render(D + '/props/_tmp.png', objs=BASE + [x for x in CLIMAX if x['local_id'] != P + 'LIGHT_STONE'], extra=stone_over(art), dark=0.25)
    w_, h_, _, px, pal = read_png(D + '/props/_tmp.png')
    full = [[pal[v] for v in row] for row in px] if pal else px
    write_png(D + '/props/no_mapa_%s.png' % c, crop(full, (11 * 32), (2 * 32), (22 * 32), (16 * 32)), 1)
os.remove(D + '/props/_tmp.png')
r.save(D, dict(map='TRUTHSAND_RUINS_HALL_OF_TRUTH', ingame='Truthsand Ruins - Hall of Truth', map_type='MAP_TYPE_UNDERGROUND',
  explorar=['Antecamara de pouso (quem cai pelo sumidouro da Trilha): Relic Vase e a escada de volta ao B1F',
            'Salao grande: avenida de estatuas ate o altar em degraus; a Light Stone dorme no degrau de cima, diante da porta selada',
            'Murais dos dois lados do altar: os herois gemeos e o dragao partido (verdade x ideais); a porta do altar tem a inscricao final',
            'Nicho oeste atras de pedra de Rock Smash: Fire Stone; nicho leste: Flame Plate (a placa do Reshiram, par da Zap Plate do cume)',
            'Esqueletos fosseis e dunas: o salao estava enterrado ha seculos'],
  historia='Ato 6, climax: Ghetsis (ou o que sobrou do Plasma) chega primeiro e tenta acordar a Light Stone. Hilda e Lenora chegam com o jogador. A pedra desperta, o Reshiram recusa o Ghetsis e testa o jogador (captura). Hilda: no BW foi ela a escolhida; aqui ela deixa o Reshiram escolher de novo.',
  estados={'dia': 'Salao em silencio, Light Stone no altar (proposta C, gemea da Pedra Escura C).',
           'estado': 'Climax: Ghetsis no degrau diante da Light Stone, dois recrutas, Hilda e Lenora chegando.',
           'depois': 'Reshiram desperto no altar; Hilda assiste.'},
  light_stone=dict(x=STONE[0], y=STONE[1], gfx='OBJ_EVENT_GFX_LIGHT_STONE (novo, 32x32, 1 quadro, como a Pedra Escura)',
                   propostas=[[c, n] for c, n, _ in ART], pasta='props/'),
  conferido='check_objects ok; BFS do pouso ate altar, murais, escada e itens (nicho oeste so com Rock Smash)'))
r.objs = objs_all
import json
i = json.load(open(D + '/info.json')); i['objects'] = objs_all; json.dump(i, open(D + '/info.json', 'w'), indent=1, ensure_ascii=False)
