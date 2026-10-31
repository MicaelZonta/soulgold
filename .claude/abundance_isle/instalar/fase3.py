"""Fase 3 da Abundance Isle: missoes secundarias, eventos de mundo, arena, para-raios, uniforme, ponto de cura.
- place(): resolve posicoes (parede/chao mais proximos) e grava instalar/extras.json (lido pelo maps.py);
- build(F, txt, talk): acrescenta os scripts ao dicionario F do fase2.py.
Rodar pelo fase2.py (que importa este arquivo) depois de place()."""
import json, os, re, struct, collections
R = '/home/ADMIN/decomps/soulgold_v1'
SC = os.path.join(R, '.claude/abundance_isle')
M20 = SC + '/mapas'
S = 'VAR_ABUNDANCE_ISLE_STATE'

# ------------------------------------------------------------------ posicoes
def _grid(d):
    i = json.load(open(f'{M20}/{d}/info.json'))
    raw = open(f'{M20}/{d}/map.bin', 'rb').read()
    b = [struct.unpack_from('<H', raw, k * 2)[0] for k in range(len(raw) // 2)]
    return i, b

def _walk(i, b, x, y):
    if not (0 <= x < i['w'] and 0 <= y < i['h']): return False
    v = b[y * i['w'] + x]
    return not (v >> 11 & 1) and (v >> 12) != 1

def _taken(i):
    t = {(o['x'], o['y']) for o in i['objects']} | {(w['x'], w['y']) for w in i['warps']}
    t |= {(e['x'], e['y']) for e in i.get('bg_events', [])}
    return t

def _reach(d):
    """celulas alcancaveis a partir dos warps (elevacao igual, ou 0/15 de um lado); objetos nao bloqueiam
    (pedra, boulder e arvore de corte se resolvem com HM). Os pisos de elevacao 4 das torres sao fechados."""
    i, b = _grid(d); w, h = i['w'], i['h']
    el = lambda x, y: b[y * w + x] >> 12
    seen = {(p['x'], p['y']) for p in i['warps'] if 0 <= p['x'] < w and 0 <= p['y'] < h}
    q = collections.deque(seen)
    while q:
        x, y = q.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            p = (x + dx, y + dy)
            if p in seen or not (0 <= p[0] < w and 0 <= p[1] < h) or b[p[1] * w + p[0]] >> 11 & 1: continue
            a, c = el(x, y), el(*p)
            if a == c or a in (0, 15) or c in (0, 15): seen.add(p); q.append(p)
    return seen

def wall_near(d, x0, y0, used):
    """parede (bloqueada) com chao alcancavel logo abaixo, a mais proxima de (x0,y0)."""
    i, b = _grid(d); taken = _taken(i) | used; ok = _reach(d)
    best = None
    for y in range(i['h'] - 1):
        for x in range(i['w']):
            if not _walk(i, b, x, y) and (x, y + 1) in ok and (x, y) not in taken and (x, y + 1) not in taken:
                dd = abs(x - x0) + abs(y - y0)
                if best is None or dd < best[0]: best = (dd, x, y)
    return best[1], best[2]

def open_floor_near(d, x0, y0, used):
    i, b = _grid(d); taken = _taken(i) | used; ok = _reach(d)
    best = None
    for y in range(1, i['h'] - 1):
        for x in range(1, i['w'] - 1):
            viz = [(x + dx, y + dy) for dy in (-1, 0, 1) for dx in (-1, 0, 1)]
            if all(v in ok and v not in taken for v in viz):
                dd = abs(x - x0) + abs(y - y0)
                if best is None or dd < best[0]: best = (dd, x, y)
    return best[1], best[2]

def floor_near(d, x0, y0, used):
    i, b = _grid(d); taken = _taken(i) | used; ok = _reach(d)
    best = None
    for y in range(i['h']):
        for x in range(i['w']):
            if (x, y) in ok and (x, y) not in taken:
                dd = abs(x - x0) + abs(y - y0)
                if best is None or dd < best[0]: best = (dd, x, y)
    return best[1], best[2]

# (mapa do prototipo, tipo, perto de, nome do script / item)
SIGNS = [
    ('AbundanceIsle_HarvestFields', 'wall', (12, 35), 'Stele1'),
    ('AbundanceIsle_GaleCave', 'wall', (7, 21), 'Stele2'),
    ('THUNDERSPIRE_1F', 'wall', (14, 19), 'Stele3'),
    ('FROSTFALL_CRATER_CORE', 'wall', (25, 8), 'Stele4'),
    ('AbundanceIsle', 'wall', (34, 27), 'Seed1'),
    ('AbundanceIsle_HarvestFields', 'wall', (16, 20), 'Seed2'),
    ('AbundanceIsle_HarvestFields', 'wall', (24, 21), 'Seed3'),
    ('AbundanceIsle_GaleShore', 'wall', (16, 12), 'Seed4'),
    ('AbundanceIsle_WindsweptCape', 'wall', (10, 28), 'Seed5'),
    ('AbundanceIsle_SpringGrove', 'wall', (8, 26), 'Seed6'),
    ('THUNDERSPIRE_1F', 'wall', (8, 9), 'Candle1'),
    ('THUNDERSPIRE_1F', 'wall', (22, 20), 'Candle2'),
    ('THUNDERSPIRE_2F', 'wall', (6, 12), 'Candle3'),
    ('THUNDERSPIRE_2F', 'wall', (27, 5), 'Candle4'),
    ('TRUTHSAND_RUINS_1F', 'wall', (14, 6), 'Mural1'),
    ('TRUTHSAND_RUINS_1F', 'wall', (30, 9), 'Mural2'),
    ('TRUTHSAND_RUINS_B1F', 'wall', (8, 4), 'Mural3'),
    ('TRUTHSAND_RUINS_B1F', 'wall', (16, 14), 'Mural4'),
    ('AbundanceIsle_PokemonCenter', 'wall', (3, 2), 'NoticeBoard'),
]
HIDDEN = [('FROSTFALL_CRATER_1F', (20, 20), 'ITEM_COMET_SHARD', 'FLAG_HIDDEN_ITEM_FROSTFALL_CRATER_1F_COMET_SHARD'),
          ('FROSTFALL_CRATER_B1F', (20, 26), 'ITEM_COMET_SHARD', 'FLAG_HIDDEN_ITEM_FROSTFALL_CRATER_B1F_COMET_SHARD'),
          ('FROSTFALL_CRATER_LAB', (8, 20), 'ITEM_COMET_SHARD', 'FLAG_HIDDEN_ITEM_FROSTFALL_CRATER_LAB_COMET_SHARD')]
OBJS = [('AbundanceIsle', (34, 27), 'JESSIE_STAND', 'JESSIE', 'HonestStand'), ('AbundanceIsle', (35, 27), 'JAMES_STAND', 'JAMES', 'HonestStand'),
        ('AbundanceIsle_Barn', (9, 15), 'JESSIE', 'JESSIE', 'JessieBarn'), ('AbundanceIsle_Barn', (10, 15), 'JAMES', 'JAMES', 'JessieBarn'),
        ('PLASMA_FRIGATE_DECK', (20, 18), 'JESSIE', 'JESSIE', 'JessieDeck'), ('PLASMA_FRIGATE_DECK', (21, 18), 'JAMES', 'JAMES', 'JessieDeck')]
VIS = {'AbundanceIsle_HarvestFields': {'FLAG_TEMP_15': ('rocket0', ['JESSIE', 'JAMES'])},
       'AbundanceIsle_Barn': {'FLAG_TEMP_11': ('rocket1', ['JESSIE', 'JAMES'])},
       'PLASMA_FRIGATE_DECK': {'FLAG_TEMP_11': ('rocket2', ['JESSIE', 'JAMES'])},
       'PLASMA_FRIGATE_HOLD': {'FLAG_TEMP_11': ('nouniform', ['ENGINE_GUARD'])},
       'AbundanceIsle_FestivalArena': {'FLAG_TEMP_15': ('sat14', ['SAT_N', 'SAT_HILDA']),          # sabado: N e Hilda na arena
                                        'FLAG_TEMP_16': ('notsat', ['SEAT_LEFT_1', 'SEAT_LEFT_2', 'SEAT_RIGHT_1', 'SEAT_RIGHT_2'])},
       'AbundanceIsle': {'FLAG_TEMP_15': ('rocketsat', ['JESSIE_STAND', 'JAMES_STAND'])},          # barraca "honesta" de sabado
       'AbundanceIsle_WindsweptCape': {'FLAG_TEMP_1E': ('notnight', [])},                          # ligada = noite: portas trancadas (C)
       }
VIS['AbundanceIsle_HarvestFields']['FLAG_TEMP_1E'] = ('notnight', [])
VIS['THUNDERSPIRE_1F'] = {'FLAG_TEMP_1A': ('flag:FLAG_ABUNDANCE_CANDLE_1', ['CANDLE_LIT_1']),
                          'FLAG_TEMP_1B': ('flag:FLAG_ABUNDANCE_CANDLE_2', ['CANDLE_LIT_2'])}
VIS['THUNDERSPIRE_2F'] = {'FLAG_TEMP_1A': ('flag:FLAG_ABUNDANCE_CANDLE_3', ['CANDLE_LIT_3']),
                          'FLAG_TEMP_1B': ('flag:FLAG_ABUNDANCE_CANDLE_4', ['CANDLE_LIT_4'])}

# placa invisivel -> objeto visivel (velas e murais nao tem sprite que sirva: continuam placa)
MARCADOR = {'Seed': ('OBJ_EVENT_GFX_BIRCHS_BAG', 'FLAG_ABUNDANCE_SEED_{n}'),    # some quando o saco e recolhido
            'Stele': ('OBJ_EVENT_GFX_DEOXYS_TRIANGLE', '0'),                    # o fragmento fica (so decalque)
            'Mural': ('OBJ_EVENT_GFX_MURAL_OBELISK', '0'),                      # obelisco dos dois dragoes (arte C, 31/10)
            'Candle': ('OBJ_EVENT_GFX_SPIRIT_CANDLE', 'FLAG_ABUNDANCE_CANDLE_{n}')}   # apagada; a acesa e um 2o objeto (abaixo)


def mapshort(name):   # AbundanceIsle_HarvestFields -> ABUNDANCE_ISLE_HARVEST_FIELDS (igual ao maps.py)
    return re.sub(r'(?<=[a-z])(?=[A-Z0-9])|(?<=[A-Z])(?=[A-Z][a-z])', '_', name).upper()


# placas em posicao fixa (pedra de oferenda dos dois lados do santuario do hub; o Keeper fica na frente)
FIXED_BG = [('AbundanceIsle', 9, 21, 'Offering'), ('AbundanceIsle', 11, 21, 'Offering')]


def place():
    ex = collections.defaultdict(lambda: dict(bg=[], objects=[]))
    used = collections.defaultdict(set)
    for d, x, y, nm in FIXED_BG:
        used[d].add((x, y))
        ex[d]['bg'].append(dict(type='sign', x=x, y=y, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='X_EventScript_' + nm))
    for d, kind, near, nm in SIGNS:
        marca = MARCADOR.get(re.sub(r'\d+$', '', nm))
        if marca:   # objeto solto no chao, numa celula aberta (as 8 vizinhas livres: nao tranca caminho)
            x, y = open_floor_near(d, *near, used[d])
            for dy in (-1, 0, 1):
                for dx in (-1, 0, 1):
                    used[d].add((x + dx, y + dy))
        else:
            x, y = wall_near(d, *near, used[d]); used[d].add((x, y))
        if marca:   # ponto de missao visivel: objeto parado na parede, falado de baixo
            gfx, flag = marca
            if nm.startswith('Candle'):   # vela acesa no mesmo lugar: aparece quando a flag da vela esta ligada
                ex[d]['objects'].append(dict(local_id='CANDLE_LIT_' + nm[-1], graphics_id='OBJ_EVENT_GFX_SPIRIT_CANDLE_LIT', x=x, y=y,
                                             elevation=3, movement_type='MOVEMENT_TYPE_NONE', movement_range_x=0, movement_range_y=0,
                                             trainer_type='TRAINER_TYPE_NONE', trainer_sight_or_berry_tree_id='0',
                                             script='X_EventScript_' + nm, flag='0'))
            ex[d]['objects'].append(dict(local_id=re.sub(r'(\d+)$', r'_\1', nm.upper()), graphics_id=gfx, x=x, y=y,
                                         elevation=3, movement_type='MOVEMENT_TYPE_NONE', movement_range_x=0, movement_range_y=0,
                                         trainer_type='TRAINER_TYPE_NONE', trainer_sight_or_berry_tree_id='0',
                                         script='X_EventScript_' + nm, flag=flag.format(n=nm[-1]), keep_flag=True))
            continue
        ex[d]['bg'].append(dict(type='sign', x=x, y=y, elevation=0, player_facing_dir='BG_EVENT_PLAYER_FACING_NORTH', script='X_EventScript_' + nm))
    for d, near, item, flag in HIDDEN:
        x, y = floor_near(d, *near, used[d]); used[d].add((x, y))
        ex[d]['bg'].append(dict(type='hidden_item', x=x, y=y, elevation=0, item=item, flag=flag, quantity=1))
    par = {}
    for d, near, suf, gfx, scr in OBJS:
        if suf.startswith('JAMES') and (d, suf.replace('JAMES', 'JESSIE')) in par:   # dupla lado a lado
            jx, jy = par[(d, suf.replace('JAMES', 'JESSIE'))]
            near = (jx + 1, jy)
        x, y = floor_near(d, *near, used[d]); used[d].add((x, y)); par[(d, suf)] = (x, y)
        ex[d]['objects'].append(dict(local_id=suf, graphics_id='OBJ_EVENT_GFX_' + gfx, x=x, y=y, elevation=3,
                                     movement_type='MOVEMENT_TYPE_FACE_DOWN', movement_range_x=0, movement_range_y=0,
                                     trainer_type='TRAINER_TYPE_NONE', trainer_sight_or_berry_tree_id='0', script='X_EventScript_' + scr, flag='0'))
    json.dump(dict(extras=ex, vis=VIS), open(SC + '/instalar/extras.json', 'w'), indent=1)
    return ex

# ------------------------------------------------------------------ scripts
def build(F, txt, talk):
    def add(mp, s): F[mp] = F.get(mp, '') + s
    def item_reward(label, item):
        return f'''	checkitemspace {item}
	goto_if_eq VAR_RESULT, FALSE, {label}_BagFull
	giveitem {item}
'''
    def bagfull(label): return f'{label}_BagFull::\n\tmsgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT\n\trelease\n\tend\n\n'
    def drop(mp, label):
        """tira do fase2 um NPC simples (talk) que a missao reescreve"""
        s = F[mp]
        s2 = re.sub(r'^%s::\n(?:.*\n)*?\tend\n\n' % label, '', s, count=1, flags=re.M)
        s2 = re.sub(r'^%s_Text:\n(?:\t\.string.*\n)+\n?' % label, '', s2, count=1, flags=re.M)
        assert s2 != s, label
        F[mp] = s2
    def sub(mp, old, new):
        assert old in F[mp], (mp, old[:40]); F[mp] = F[mp].replace(old, new, 1)

    for mp, nm in (('AbundanceIsle_GaleShore', 'Winona'), ('ThunderRidge', 'Volkner'), ('ThunderRidge', 'Elesa'), ('ThunderRidge', 'Alder'),
                   ('FrostfallCrater_B1F', 'Byron'), ('FrostfallCrater_Core', 'Zinnia'), ('AbundanceIsle_SpringGrove', 'Ramos'),
                   ('AbundanceIsle_SpringGrove', 'Gardenia'), ('EmberduneIsle', 'Greta')):
        drop(mp, f'{mp}_EventScript_{nm}')

    # Lenora: com os 4 fragmentos, le a estela inteira, batalha e premia (antes de qualquer outra fala)
    le = 'AbundanceIsle_HarvestFields_EventScript_Lenora'
    sub('AbundanceIsle_HarvestFields', f'{le}::\n\tlock\n\tfaceplayer\n',
        f'{le}::\n\tlock\n\tfaceplayer\n\tgoto_if_unset FLAG_ABUNDANCE_STELE_REWARD, {le}_SteleCheck\n{le}_Main::\n')
    add('AbundanceIsle_HarvestFields', f'''{le}_SteleCheck::
''' + ''.join(f'\tgoto_if_unset FLAG_ABUNDANCE_STELE_{n}, {le}_Main\n' for n in range(1, 5)) + f'''	msgbox {le}_TextStele, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_LENORA, {le}_TextSteleBeaten
''' + item_reward(le, 'ITEM_BIG_NUGGET') + f'''	setflag FLAG_ABUNDANCE_STELE_REWARD
	release
	end

''' + bagfull(le) + txt(le + '_TextStele', ['All four rubbings! Now the whole', 'stele reads...'],
                         ['“The genies quarreled, the lord', 'came down, and the year the cold', 'star fell, no lord came at all.”'],
                         ['History is a battle of its own.', 'Let\'s celebrate with one!'], speaker='LENORA')
        + txt(le + '_TextSteleBeaten', ['Lenora: A textbook victory!']) + '\n')

    # murais do Hall: o das Twin Heroes conta para Sands of Truth
    tw = 'TruthsandRuins_HallOfTruth_EventScript_MuralTwinHeroes'
    sub('TruthsandRuins_HallOfTruth', f'{tw}::\n\tmsgbox {tw}_Text, MSGBOX_SIGN\n\tend\n',
        f'{tw}::\n\tlockall\n\tmsgbox {tw}_Text, MSGBOX_DEFAULT\n\tsetflag FLAG_ABUNDANCE_MURAL_5\n\treleaseall\n\tend\n')

    # revanche diaria da dupla N & Hilda
    nd = 'ShrineOfTheFirstDragon_EventScript_NDone'
    sub('ShrineOfTheFirstDragon', f'{nd}::\n\tmsgbox ShrineOfTheFirstDragon_Text_FinalAfter, MSGBOX_DEFAULT\n\trelease\n\tend\n',
        f'''{nd}::
	goto_if_set FLAG_DAILY_ABUNDANCE_DUO, {nd}_Talk
	msgbox {nd}_TextRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {nd}_Talk
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_N_AND_HILDA
	trainerbattle_no_intro TRAINER_ABUNDANCE_N_AND_HILDA, ShrineOfTheFirstDragon_Text_FinalBeaten
	setflag FLAG_DAILY_ABUNDANCE_DUO
	release
	end
{nd}_Talk::
	msgbox ShrineOfTheFirstDragon_Text_FinalAfter, MSGBOX_DEFAULT
	release
	end
''')
    add('ShrineOfTheFirstDragon', txt(nd + '_TextRematch', ['{PLAYER}! Up for another battle?', 'Hilda says she\'s been practicing.'], speaker='N') + '\n')

    # ---------------- 1. The Broken Stele (fragmentos)
    FRAG = {1: ('AbundanceIsle_HarvestFields', ['“...the Wind Genie carried the', 'clouds, the Thunder Genie broke', 'the hard earth...”']),
            2: ('AbundanceIsle_GaleCave', ['“...but each wished the sky for', 'itself, and the fields turned', 'to dust...”']),
            3: ('Thunderspire_1F', ['“...the Lord of the Fertile Land', 'came down only when both stood', 'before it together...”']),
            4: ('FrostfallCrater_Core', ['“...and the year the cold star fell,', 'no lord came at all.”'])}
    for n, (mp, lines) in FRAG.items():
        lb = f'{mp}_EventScript_Stele{n}'
        add(mp, f'''{lb}::
	lockall
	goto_if_set FLAG_ABUNDANCE_STELE_{n}, {lb}_Done
	msgbox {lb}_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STELE_{n}
	msgbox {lb}_TextRub, MSGBOX_DEFAULT
	releaseall
	end

{lb}_Done::
	msgbox {lb}_Text, MSGBOX_DEFAULT
	releaseall
	end

''' + txt(lb + '_Text', ['A fragment of an old stele.'], lines) + txt(lb + '_TextRub', ['{PLAYER} made a rubbing of the', 'fragment for Lenora.']) + '\n')

    # ---------------- 2. Scrolls of the Four (Cynthia)
    sc = 'AbundanceIsle_KeeperHouse_EventScript_Cynthia'
    scrolls = [['The first scroll: the Wind Genie,', 'who carries the rain clouds.'], ['The second: the Thunder Genie,', 'whose lightning wakes the soil.'],
               ['The third: the Lord of the Fertile', 'Land, who calms them both.'], ['The fourth... a visitor from the sea', 'who ends the winter. Enamorus!']]
    s = f'''{sc}::
	lock
	faceplayer
	setvar VAR_0x8000, 0
	call_if_ge {S}, 2, {sc}_Inc
	call_if_ge {S}, 4, {sc}_Inc
	call_if_ge {S}, 7, {sc}_Inc
	call_if_ge {S}, 9, {sc}_Inc
	compare VAR_ABUNDANCE_CYNTHIA_SCROLLS, VAR_0x8000
	goto_if_lt {sc}_Read
	goto_if_lt VAR_ABUNDANCE_CYNTHIA_SCROLLS, 4, {sc}_Wait
	goto_if_defeated TRAINER_ABUNDANCE_CYNTHIA, {sc}_After
	msgbox {sc}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_CYNTHIA, {sc}_TextBeaten
''' + item_reward(sc, 'ITEM_SHINY_STONE') + f'''	release
	end

{sc}_Inc::
	addvar VAR_0x8000, 1
	return

{sc}_Read::
	addvar VAR_ABUNDANCE_CYNTHIA_SCROLLS, 1
	goto_if_eq VAR_ABUNDANCE_CYNTHIA_SCROLLS, 1, {sc}_S1
	goto_if_eq VAR_ABUNDANCE_CYNTHIA_SCROLLS, 2, {sc}_S2
	goto_if_eq VAR_ABUNDANCE_CYNTHIA_SCROLLS, 3, {sc}_S3
	msgbox {sc}_TextS4, MSGBOX_DEFAULT
	release
	end
{sc}_S1::
	msgbox {sc}_TextS1, MSGBOX_DEFAULT
	release
	end
{sc}_S2::
	msgbox {sc}_TextS2, MSGBOX_DEFAULT
	release
	end
{sc}_S3::
	msgbox {sc}_TextS3, MSGBOX_DEFAULT
	release
	end

{sc}_Wait::
	msgbox {sc}_TextWait, MSGBOX_DEFAULT
	release
	end

{sc}_After::
	msgbox {sc}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(sc)
    for k in range(4):
        s += txt(f'{sc}_TextS{k + 1}', ['I found another scroll in the', 'keeper\'s archive.'], scrolls[k], speaker='CYNTHIA')
    s += txt(f'{sc}_TextWait', ['The next scroll is still sealed.', 'Come back as the island changes.'], speaker='CYNTHIA') \
        + txt(f'{sc}_TextChallenge', ['All four scrolls... the island\'s', 'whole myth. Thank you.'], ['Now, let me see how strong the', 'one who lived it has become!'], speaker='CYNTHIA') \
        + txt(f'{sc}_TextBeaten', ['Cynthia: Splendid. Truly.']) \
        + txt(f'{sc}_TextAfter', ['Myths are how people remember', 'what Pokemon taught them.'], speaker='CYNTHIA') + '\n'
    add('AbundanceIsle_KeeperHouse', s)

    # ---------------- 3. Seeds in the Storm
    SEEDS = {1: 'AbundanceIsle', 2: 'AbundanceIsle_HarvestFields', 3: 'AbundanceIsle_HarvestFields', 4: 'AbundanceIsle_GaleShore',
             5: 'AbundanceIsle_WindsweptCape', 6: 'AbundanceIsle_SpringGrove'}
    for n, mp in SEEDS.items():
        lb = f'{mp}_EventScript_Seed{n}'
        add(mp, f'''{lb}::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_{n}, {lb}_Empty
	msgbox {lb}_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_{n}
	removeobject LOCALID_{mapshort(mp)}_SEED_{n}
	releaseall
	end

{lb}_Empty::
	msgbox {lb}_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

''' + txt(lb + '_Text', ['A sack of seeds blown here by the', 'storm!'], ['{PLAYER} took the sack to return', 'it to the farm.']) + txt(lb + '_TextEmpty', ['Nothing here but a few stray', 'seeds.']) + '\n')
    fm = 'AbundanceIsle_EventScript_Farmer'
    s = f'''{fm}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_SEEDS_DONE, {fm}_Stand
	setvar VAR_0x8000, 0
''' + ''.join(f'\tcall_if_set FLAG_ABUNDANCE_SEED_{n}, {fm}_Inc\n' for n in range(1, 7)) + f'''	goto_if_eq VAR_0x8000, 6, {fm}_AllSeeds
	buffernumberstring STR_VAR_1, VAR_0x8000
	msgbox {fm}_TextAsk, MSGBOX_DEFAULT
	release
	end

{fm}_Inc::
	addvar VAR_0x8000, 1
	return

{fm}_AllSeeds::
	setflag FLAG_ABUNDANCE_SEEDS_DONE
	msgbox {fm}_TextThanks, MSGBOX_DEFAULT
	goto {fm}_Stand

{fm}_Stand::
	goto_if_set FLAG_DAILY_ABUNDANCE_FARM_STAND, {fm}_StandDone
	random 3
	goto_if_eq VAR_RESULT, 1, {fm}_Lum
	goto_if_eq VAR_RESULT, 2, {fm}_Leppa
	setvar VAR_0x8008, ITEM_SITRUS_BERRY
	goto {fm}_Give
{fm}_Lum::
	setvar VAR_0x8008, ITEM_LUM_BERRY
	goto {fm}_Give
{fm}_Leppa::
	setvar VAR_0x8008, ITEM_LEPPA_BERRY
{fm}_Give::
	msgbox {fm}_TextStand, MSGBOX_DEFAULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, {fm}_BagFull
	giveitem VAR_0x8008
	setflag FLAG_DAILY_ABUNDANCE_FARM_STAND
	release
	end

{fm}_StandDone::
	msgbox {fm}_TextStandDone, MSGBOX_DEFAULT
	release
	end

''' + bagfull(fm) + txt(f'{fm}_TextAsk', ['The storm scattered six sacks of', 'seed all over the islands!'],
                         ['You\'ve found {{STR_VAR_1}} so far.', 'Bring them all back and the farm', 'can plant again.'], speaker='FARMER') \
        + txt(f'{fm}_TextThanks', ['All six sacks! The fields will be', 'green again by next season.'], ['Our stand is open again. Come by', 'every day for a fresh berry!'], speaker='FARMER') \
        + txt(f'{fm}_TextStand', ['Here, today\'s pick from the', 'harvest!'], speaker='FARMER') \
        + txt(f'{fm}_TextStandDone', ['That\'s all for today. Come back', 'tomorrow!'], speaker='FARMER') + '\n'
    add('AbundanceIsle', s.replace('{{STR_VAR_1}}', '{STR_VAR_1}'))

    # ---------------- 4. The Scarecrow Scheme (Jessie e James)
    hf = 'AbundanceIsle_HarvestFields_EventScript_JessieJames'
    add('AbundanceIsle_HarvestFields', f'''{hf}::
	lock
	faceplayer
	msgbox {hf}_Text, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_15
	removeobject LOCALID_ABUNDANCE_ISLE_HARVEST_FIELDS_JESSIE
	removeobject LOCALID_ABUNDANCE_ISLE_HARVEST_FIELDS_JAMES
	setvar VAR_ABUNDANCE_ROCKET_STAGE, 1
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

''' + txt(hf + '_Text', ['We\'re just two perfectly normal', 'scarecrows! Nothing to see here!'],
          ['{SPEAKER NAME_JAMES}...Jessie, the twerp is staring.', 'Retreat to the barn!'], speaker='JESSIE') + '\n')
    bj = 'AbundanceIsle_Barn_EventScript_JessieBarn'
    add('AbundanceIsle_Barn', f'''{bj}::
	lock
	faceplayer
	msgbox {bj}_Text, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_ABUNDANCE_ISLE_BARN_JESSIE
	removeobject LOCALID_ABUNDANCE_ISLE_BARN_JAMES
	setvar VAR_ABUNDANCE_ROCKET_STAGE, 2
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

''' + txt(bj + '_Text', ['Achoo! This hay is NOT a good', 'hiding place!'],
          ['{SPEAKER NAME_JAMES}We heard Team Plasma pays well', 'for secrets. To their ship!'], speaker='JESSIE') + '\n')
    dj = 'PlasmaFrigate_Deck_EventScript_JessieDeck'
    add('PlasmaFrigate_Deck', f'''{dj}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ROCKET_REWARD, {dj}_Done
	msgbox {dj}_Text, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_JESSIE_JAMES, {dj}_TextBeaten
	msgbox {dj}_TextAfter, MSGBOX_DEFAULT
''' + item_reward(dj, 'ITEM_AMULET_COIN') + f'''	setflag FLAG_ABUNDANCE_ROCKET_REWARD
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_PLASMA_FRIGATE_DECK_JESSIE
	removeobject LOCALID_PLASMA_FRIGATE_DECK_JAMES
	setvar VAR_ABUNDANCE_ROCKET_STAGE, 3
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

{dj}_Done::
	release
	end

''' + bagfull(dj) + txt(dj + '_Text', ['The Plasma wouldn\'t buy our', 'secrets! So we\'ll take it out', 'on YOU!'], speaker='JESSIE')
        + txt(dj + '_TextBeaten', ['Jessie: Looks like we\'re blasting', 'off again!']) + txt(dj + '_TextAfter', ['...Fine. Take this. We\'d only', 'lose it anyway.'], speaker='JAMES') + '\n')

    # ---------------- 5. Grounded (Skyla)
    sk = 'AbundanceIsle_SkylaHangar_EventScript_SkylaFlight'
    add('AbundanceIsle_SkylaHangar', f'''{sk}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_SKYLA_PLATE, {sk}_Offer
	msgbox {sk}_TextThanks, MSGBOX_DEFAULT
''' + item_reward(sk, 'ITEM_SKY_PLATE') + f'''	setflag FLAG_ABUNDANCE_SKYLA_PLATE
{sk}_Offer::
	msgbox {sk}_TextOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {sk}_No
	msgbox {sk}_TextGo, MSGBOX_DEFAULT
	closemessage
	warp MAP_OLIVINE_CITY_PORT_OUTSIDE, 11, 5
	waitstate
	release
	end

{sk}_No::
	release
	end

''' + bagfull(sk) + txt(sk + '_TextThanks', ['The skies are clear again! My', 'plane can finally fly.'], ['Here, a little thank-you.'], speaker='SKYLA')
        + txt(sk + '_TextOffer', ['Want a lift back to Olivine?', 'It\'s a short hop!'], speaker='SKYLA') + txt(sk + '_TextGo', ['Buckle up!'], speaker='SKYLA') + '\n')
    add('AbundanceIsle_SkylaHangar', talk('AbundanceIsle_SkylaHangar_EventScript_SkylaGrounded', 'SKYLA',
        ['My cargo plane is stuck here.', 'Nobody flies into a storm that', 'never ends.']))

    # ---------------- 6. Eye of the Storm (Winona -> Volkner) + batalhas opcionais
    wi = 'AbundanceIsle_GaleShore_EventScript_Winona'
    add('AbundanceIsle_GaleShore', f'''{wi}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_STORM_GAUGE, {wi}_Battle
	msgbox {wi}_TextGauge, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STORM_GAUGE
	release
	end

{wi}_Battle::
	goto_if_defeated TRAINER_ABUNDANCE_WINONA, {wi}_After
	msgbox {wi}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_WINONA, {wi}_TextBeaten
	release
	end

{wi}_After::
	msgbox {wi}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + txt(wi + '_TextGauge', ['The winds here spin around the', 'crater. Something pulls them.'],
          ['Take my storm readings to Volkner', 'on the Thunder Ridge. He\'s measuring', 'the lightning.'], speaker='WINONA')
        + txt(wi + '_TextChallenge', ['Let\'s see how your Pokemon fly', 'against this wind!'], speaker='WINONA') + txt(wi + '_TextBeaten', ['Winona: Beautifully flown.'])
        + txt(wi + '_TextAfter', ['When the winds calm, the Wind', 'Genie will come down.'], speaker='WINONA') + '\n')
    vo = 'ThunderRidge_EventScript_Volkner'
    add('ThunderRidge', f'''{vo}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_STORM_DATA_DONE, {vo}_Battle
	goto_if_unset FLAG_ABUNDANCE_STORM_GAUGE, {vo}_Idle
	msgbox {vo}_TextData, MSGBOX_DEFAULT
''' + item_reward(vo, 'ITEM_ELECTIRIZER') + f'''	setflag FLAG_ABUNDANCE_STORM_DATA_DONE
	release
	end

{vo}_Idle::
	msgbox {vo}_TextIdle, MSGBOX_DEFAULT
	release
	end

{vo}_Battle::
	goto_if_defeated TRAINER_ABUNDANCE_VOLKNER, {vo}_After
	msgbox {vo}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_VOLKNER, {vo}_TextBeaten
	release
	end

{vo}_After::
	msgbox {vo}_TextIdle, MSGBOX_DEFAULT
	release
	end

''' + bagfull(vo) + txt(vo + '_TextIdle', ['Lightning strikes this ridge more', 'than anywhere I\'ve seen. It\'s', 'like it\'s being called.'], speaker='VOLKNER')
        + txt(vo + '_TextData', ['Winona\'s wind data... it all', 'spirals around the crater.'], ['The storm is artificial. Thanks.', 'Take this for your trouble.'], speaker='VOLKNER')
        + txt(vo + '_TextChallenge', ['Now I\'m curious. Show me a', 'battle with some real spark!'], speaker='VOLKNER') + txt(vo + '_TextBeaten', ['Volkner: Heh. That woke me up.']) + '\n')
    el = 'ThunderRidge_EventScript_Elesa'
    add('ThunderRidge', f'''{el}::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_ELESA, {el}_After
	msgbox {el}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_ELESA, {el}_TextBeaten
	release
	end

{el}_After::
	msgbox {el}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + txt(el + '_TextChallenge', ['These sparks would make a gorgeous', 'runway. Shall we dazzle them?'], speaker='ELESA')
        + txt(el + '_TextBeaten', ['Elesa: Shocking... in a good way!']) + txt(el + '_TextAfter', ['The lightning is calmer now.', 'Almost pretty.'], speaker='ELESA') + '\n')

    # ---------------- 7. Frozen Stars (Byron troca Comet Shard)
    by = 'FrostfallCrater_B1F_EventScript_Byron'
    add('FrostfallCrater_B1F', f'''{by}::
	lock
	faceplayer
	checkitem ITEM_COMET_SHARD
	goto_if_eq VAR_RESULT, FALSE, {by}_NoShard
	msgbox {by}_TextOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {by}_No
	goto_if_eq VAR_ABUNDANCE_BYRON_TRADES, 1, {by}_T2
	goto_if_eq VAR_ABUNDANCE_BYRON_TRADES, 2, {by}_T3
	setvar VAR_0x8008, ITEM_NEVER_MELT_ICE
	goto {by}_Trade
{by}_T2::
	setvar VAR_0x8008, ITEM_ICICLE_PLATE
	goto {by}_Trade
{by}_T3::
	setvar VAR_0x8008, ITEM_DRAGON_FANG
{by}_Trade::
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, {by}_BagFull
	removeitem ITEM_COMET_SHARD
	giveitem VAR_0x8008
	addvar VAR_ABUNDANCE_BYRON_TRADES, 1
	goto_if_lt VAR_ABUNDANCE_BYRON_TRADES, 3, {by}_End
	setvar VAR_ABUNDANCE_BYRON_TRADES, 0
{by}_End::
	release
	end

{by}_No::
	release
	end

{by}_NoShard::
	msgbox {by}_TextNoShard, MSGBOX_DEFAULT
	release
	end

''' + bagfull(by) + txt(by + '_TextNoShard', ['These shards aren\'t from this', 'world. Harder than any steel!'],
                         ['Find me a Comet Shard from the', 'crater and I\'ll trade you', 'something good.'], speaker='BYRON')
        + txt(by + '_TextOffer', ['A Comet Shard! Will you trade it', 'to me?'], speaker='BYRON') + '\n')

    # ---------------- 8. Draconid Tale (Zinnia, com Kyurem na equipe)
    zi = 'FrostfallCrater_Core_EventScript_Zinnia'
    add('FrostfallCrater_Core', f'''{zi}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ZINNIA_TALE, {zi}_After
	checkspecies SPECIES_KYUREM
	goto_if_eq VAR_RESULT, FALSE, {zi}_Idle
	msgbox {zi}_TextTale, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_ZINNIA, {zi}_TextBeaten
''' + item_reward(zi, 'ITEM_DRACO_PLATE') + f'''	setflag FLAG_ABUNDANCE_ZINNIA_TALE
	release
	end

{zi}_Idle::
	msgbox {zi}_TextIdle, MSGBOX_DEFAULT
	release
	end

{zi}_After::
	msgbox {zi}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(zi) + txt(zi + '_TextIdle', ['A star of ice fell here once.', 'The year without harvest.'],
                         ['If you ever travel with the', 'dragon of the void, come back.', 'I\'ll tell you its story.'], speaker='ZINNIA')
        + txt(zi + '_TextTale', ['That cold... you have Kyurem.'], ['My people say it rode the star', 'down. Others say it\'s the shell', 'of the first dragon.'],
              ['Whatever it is, it chose you.', 'Show me you deserve it!'], speaker='ZINNIA')
        + txt(zi + '_TextBeaten', ['Zinnia: Ha! The void suits you.']) + txt(zi + '_TextAfter', ['Look after that dragon.'], speaker='ZINNIA') + '\n')

    # ---------------- 9. Candles of the Spire (Allister)
    for n, mp in ((1, 'Thunderspire_1F'), (2, 'Thunderspire_1F'), (3, 'Thunderspire_2F'), (4, 'Thunderspire_2F')):
        lb = f'{mp}_EventScript_Candle{n}'
        add(mp, f'''{lb}::
	lockall
	goto_if_set FLAG_ABUNDANCE_CANDLE_{n}, {lb}_Lit
	msgbox {lb}_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_CANDLE_{n}
	playse SE_M_EMBER
	removeobject LOCALID_{mapshort(mp)}_CANDLE_{n}
	clearflag FLAG_TEMP_1{'A' if n % 2 else 'B'}
	addobject LOCALID_{mapshort(mp)}_CANDLE_LIT_{n}
	releaseall
	end

{lb}_Lit::
	msgbox {lb}_TextLit, MSGBOX_DEFAULT
	releaseall
	end

''' + txt(lb + '_Text', ['An old spirit candle. {PLAYER} lit', 'it, and the flame burned blue.']) + txt(lb + '_TextLit', ['The blue flame flickers quietly.']) + '\n')
    al = 'Thunderspire_2F_EventScript_Alister'
    add('Thunderspire_2F', f'''{al}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_CANDLES_DONE, {al}_After
''' + ''.join(f'\tgoto_if_unset FLAG_ABUNDANCE_CANDLE_{n}, {al}_Ask\n' for n in range(1, 5)) + f'''	msgbox {al}_TextDone, MSGBOX_DEFAULT
''' + item_reward(al, 'ITEM_REAPER_CLOTH') + f'''	setflag FLAG_ABUNDANCE_CANDLES_DONE
	release
	end

{al}_Ask::
	msgbox {al}_TextAsk, MSGBOX_DEFAULT
	release
	end

{al}_After::
	msgbox {al}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(al) + txt(al + '_TextAsk', ['B-boo... sorry. The ghosts here', 'are lonely.'], ['Four spirit candles went out in', 'this tower. Could you light them?'], speaker='ALLISTER')
        + txt(al + '_TextDone', ['All four... I can see him now.', 'The builder who carried the Dark', 'Stone here. He\'s smiling.'], ['Th-thank you. Take this.'], speaker='ALLISTER')
        + txt(al + '_TextAfter', ['The tower feels warmer now.'], speaker='ALLISTER') + '\n')

    # ---------------- 10. Undercover (uniforme + Rosa)
    un = 'PlasmaFrigate_Cabins_EventScript_UniformLocker'
    add('PlasmaFrigate_Cabins', f'''{un}::
	lockall
	goto_if_set FLAG_ABUNDANCE_PLASMA_UNIFORM, {un}_Empty
	msgbox {un}_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_PLASMA_UNIFORM
	releaseall
	end

{un}_Empty::
	msgbox {un}_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

''' + txt(un + '_Text', ['A spare Team Plasma uniform!', '{PLAYER} put it on over their', 'clothes.'], ['Now the guards might let you', 'pass...']) + txt(un + '_TextEmpty', ['An empty locker.']) + '\n')
    add('PlasmaFrigate_Hold', talk('PlasmaFrigate_Hold_EventScript_EngineGuard', 'GRUNT', ['Engine room is for crew only!', 'Where\'s your uniform?']))
    ro = 'PlasmaFrigate_Deck_EventScript_Rosa'
    add('PlasmaFrigate_Deck', f'''{ro}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ROSA_REWARD, {ro}_After
	goto_if_defeated TRAINER_ABUNDANCE_PLASMA_FRIGATE_ENGINE_ROOM_CHIEF, {ro}_Reward
	special HealPlayerParty
	msgbox {ro}_TextHint, MSGBOX_DEFAULT
	release
	end

{ro}_Reward::
	msgbox {ro}_TextThanks, MSGBOX_DEFAULT
''' + item_reward(ro, 'ITEM_MAX_REVIVE') + f'''	setflag FLAG_ABUNDANCE_ROSA_REWARD
	release
	end

{ro}_After::
	special HealPlayerParty
	msgbox {ro}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(ro) + txt(ro + '_TextHint', ['Shh! I snuck aboard too. Let me', 'heal your team.'],
                         ['The DNA research is in the engine', 'room. A guard blocks the stairs...', 'Find a uniform in the cabins!'], speaker='ROSA')
        + txt(ro + '_TextThanks', ['You beat their chief scientist?', 'Amazing! Take this, partner.'], speaker='ROSA')
        + txt(ro + '_TextAfter', ['Rest up. I\'ll keep watch.'], speaker='ROSA') + '\n')

    # ---------------- 11/12. Barry (uma vez) e Nemona (diaria)
    ba = 'AbundanceIsle_PokemonCenter_EventScript_Barry'
    add('AbundanceIsle_PokemonCenter', f'''{ba}::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_BARRY, {ba}_After
	msgbox {ba}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_BARRY, {ba}_TextBeaten
''' + item_reward(ba, 'ITEM_QUICK_CLAW') + f'''	release
	end

{ba}_After::
	msgbox {ba}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(ba) + txt(ba + '_TextChallenge', ['Hey! You! I\'m racing to the top', 'of the Thunderspire... but first,', 'a battle! Ten seconds! Go!'], speaker='BARRY')
        + txt(ba + '_TextBeaten', ['Barry: Whaaat?! I\'ll fine you!']) + txt(ba + '_TextAfter', ['Next time I\'ll be faster. I\'ll', 'fine you a million!'], speaker='BARRY') + '\n')
    ne = 'AbundanceIsle_PokemonCenter_EventScript_Nemona'
    add('AbundanceIsle_PokemonCenter', f'''{ne}::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_NEMONA, {ne}_Tomorrow
	msgbox {ne}_TextChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {ne}_No
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_NEMONA
	trainerbattle_no_intro TRAINER_ABUNDANCE_NEMONA, {ne}_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_NEMONA
	msgbox {ne}_TextAfter, MSGBOX_DEFAULT
	release
	end

{ne}_No::
	release
	end

{ne}_Tomorrow::
	msgbox {ne}_TextTomorrow, MSGBOX_DEFAULT
	release
	end

''' + txt(ne + '_TextChallenge', ['Battle! Battle! I\'ve been waiting', 'all day! Ready?'], speaker='NEMONA')
        + txt(ne + '_TextBeaten', ['Nemona: That was SO good!']) + txt(ne + '_TextAfter', ['Same time tomorrow, okay?!'], speaker='NEMONA')
        + txt(ne + '_TextTomorrow', ['I\'m all battled out... for today!', 'Tomorrow!'], speaker='NEMONA') + '\n')

    # ---------------- 13. Questions of Ideals (Alder)
    ad = 'ThunderRidge_EventScript_Alder'
    s = f'''{ad}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ALDER_DONE, {ad}_After
	setvar VAR_ABUNDANCE_IDEALS, 0
	msgbox {ad}_TextQ1, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, {ad}_Ideal
	msgbox {ad}_TextQ2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, {ad}_Ideal
	msgbox {ad}_TextQ3, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, {ad}_Ideal
	goto_if_ge VAR_ABUNDANCE_IDEALS, 2, {ad}_IdealsWin
	msgbox {ad}_TextTruth, MSGBOX_DEFAULT
	goto {ad}_Give
{ad}_IdealsWin::
	msgbox {ad}_TextIdeals, MSGBOX_DEFAULT
{ad}_Give::
''' + item_reward(ad, 'ITEM_EXPERT_BELT') + f'''	setflag FLAG_ABUNDANCE_ALDER_DONE
	release
	end

{ad}_Ideal::
	addvar VAR_ABUNDANCE_IDEALS, 1
	return

{ad}_After::
	msgbox {ad}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(ad)
    s += txt(ad + '_TextQ1', ['Tell me, young one. Would you', 'keep a bright dream over a hard', 'truth?'], speaker='ALDER') \
        + txt(ad + '_TextQ2', ['If the world doesn\'t match what', 'you believe, do you change the', 'world?'], speaker='ALDER') \
        + txt(ad + '_TextQ3', ['Would you follow a path no one', 'has walked before?'], speaker='ALDER') \
        + txt(ad + '_TextIdeals', ['Ideals, then! The black dragon', 'will like you.'], ['Take this. Strength for the', 'road you chose.'], speaker='ALDER') \
        + txt(ad + '_TextTruth', ['Truth, then. The white dragon', 'would understand you.'], ['Take this. Strength for the', 'road you chose.'], speaker='ALDER') \
        + txt(ad + '_TextAfter', ['Truth and ideals aren\'t enemies.', 'They\'re two halves of one heart.'], speaker='ALDER') + '\n'
    add('ThunderRidge', s)

    # ---------------- 14. The Herald's Garden (Ramos) + Gardenia
    ra = 'AbundanceIsle_SpringGrove_EventScript_Ramos'
    add('AbundanceIsle_SpringGrove', f'''{ra}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_GARDEN_DONE, {ra}_After
	goto_if_lt {S}, 9, {ra}_Before
	goto_if_ge VAR_ABUNDANCE_GARDEN_DAYS, 3, {ra}_Reward
	goto_if_set FLAG_DAILY_ABUNDANCE_GARDEN, {ra}_Tomorrow
	msgbox {ra}_TextWater, MSGBOX_DEFAULT
	setflag FLAG_DAILY_ABUNDANCE_GARDEN
	addvar VAR_ABUNDANCE_GARDEN_DAYS, 1
	goto_if_ge VAR_ABUNDANCE_GARDEN_DAYS, 3, {ra}_Reward
	msgbox {ra}_TextAgain, MSGBOX_DEFAULT
	release
	end

{ra}_Reward::
	msgbox {ra}_TextReward, MSGBOX_DEFAULT
''' + item_reward(ra, 'ITEM_BIG_ROOT') + f'''	setflag FLAG_ABUNDANCE_GARDEN_DONE
	release
	end

{ra}_Before::
	msgbox {ra}_TextBefore, MSGBOX_DEFAULT
	release
	end

{ra}_Tomorrow::
	msgbox {ra}_TextTomorrow, MSGBOX_DEFAULT
	release
	end

{ra}_After::
	msgbox {ra}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(ra) + txt(ra + '_TextBefore', ['The founders planted these beds', '“for the one who comes from the', 'sea when winter ends.”'], ['Funny thing is, nobody remembers', 'who that is anymore.'], speaker='RAMOS')
        + txt(ra + '_TextWater', ['Spring is here! Help me water', 'the herald\'s beds, would you?'], ['...There. That\'s the way.'], speaker='RAMOS')
        + txt(ra + '_TextAgain', ['Come back tomorrow and we\'ll', 'do it again.'], speaker='RAMOS')
        + txt(ra + '_TextTomorrow', ['Plants need patience. Tomorrow!'], speaker='RAMOS')
        + txt(ra + '_TextReward', ['Look at them bloom! The herald', 'would be proud.'], ['Here, a root from the oldest bed.'], speaker='RAMOS')
        + txt(ra + '_TextAfter', ['Every spring, the garden', 'remembers.'], speaker='RAMOS') + '\n')
    ga = 'AbundanceIsle_SpringGrove_EventScript_Gardenia'
    add('AbundanceIsle_SpringGrove', f'''{ga}::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_GARDENIA, {ga}_After
	msgbox {ga}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GARDENIA, {ga}_TextBeaten
	release
	end

{ga}_After::
	msgbox {ga}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + txt(ga + '_TextChallenge', ['This grove is the first place', 'spring touches. Let\'s battle in', 'its honor!'], speaker='GARDENIA')
        + txt(ga + '_TextBeaten', ['Gardenia: You bloomed beautifully!']) + txt(ga + '_TextAfter', ['Come see the flowers anytime!'], speaker='GARDENIA') + '\n')

    # ---------------- 15. Sands of Truth (murais; Lucy recompensa, Spenser batalha)
    for n, mp in ((1, 'TruthsandRuins_1F'), (2, 'TruthsandRuins_1F'), (3, 'TruthsandRuins_B1F'), (4, 'TruthsandRuins_B1F')):
        lb = f'{mp}_EventScript_Mural{n}'
        lines = {1: ['Two brothers raise a city, a', 'single dragon above them.'], 2: ['The brothers turn away from', 'each other.'],
                 3: ['The dragon splits in two: white', 'flame and black lightning.'], 4: ['A third shape, cold and empty,', 'is left behind in the ice.']}[n]
        add(mp, f'''{lb}::
	lockall
	msgbox {lb}_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_MURAL_{n}
	releaseall
	end

''' + txt(lb + '_Text', ['An old stone obelisk, carved on', 'every side.'], lines) + '\n')
    lu = 'TruthsandRuins_1F_EventScript_Lucy'
    add('TruthsandRuins_1F', f'''{lu}::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_MURALS_DONE, {lu}_After
''' + ''.join(f'\tgoto_if_unset FLAG_ABUNDANCE_MURAL_{n}, {lu}_Ask\n' for n in range(1, 6)) + f'''	msgbox {lu}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_LUCY, {lu}_TextBeaten
''' + item_reward(lu, 'ITEM_SUN_STONE') + f'''	setflag FLAG_ABUNDANCE_MURALS_DONE
	release
	end

{lu}_Ask::
	msgbox {lu}_TextAsk, MSGBOX_DEFAULT
	release
	end

{lu}_After::
	msgbox {lu}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(lu) + txt(lu + '_TextAsk', ['...Five murals tell the whole', 'story. Read them all.'], speaker='LUCY')
        + txt(lu + '_TextChallenge', ['You read every mural. Then you', 'know the truth. Prove it.'], speaker='LUCY')
        + txt(lu + '_TextBeaten', ['Lucy: ...Acceptable.']) + txt(lu + '_TextAfter', ['...The sand keeps its secrets well.'], speaker='LUCY') + '\n')
    sp = 'TruthsandRuins_1F_EventScript_Spenser'
    add('TruthsandRuins_1F', f'''{sp}::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_SPENSER, {sp}_After
	msgbox {sp}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_SPENSER, {sp}_TextBeaten
''' + item_reward(sp, 'ITEM_FIRE_STONE') + f'''	release
	end

{sp}_After::
	msgbox {sp}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + bagfull(sp) + txt(sp + '_TextChallenge', ['These ruins test the spirit.', 'Let me test yours!'], speaker='SPENSER')
        + txt(sp + '_TextBeaten', ['Spenser: Your spirit is true.']) + txt(sp + '_TextAfter', ['Truth lives where we least look.'], speaker='SPENSER') + '\n')

    # ---------------- 16. Twin Mirrors (Tate & Liza) e batalhas soltas (Greta, Noland)
    for mp, nm, tr, spk, a, b, after, item in (
            ('ShrineOfTheFirstDragon', 'Liza', 'TRAINER_ABUNDANCE_TATE_LIZA', 'LIZA', ['Two brothers, one dragon...', 'like us, two twins, one mind.'], 'Tate & Liza: Mirrored perfectly!', ['We\'ll never fight like the', 'brothers did.'], 'ITEM_TWISTED_SPOON'),
            ('EmberduneIsle', 'Greta', 'TRAINER_ABUNDANCE_GRETA', 'GRETA', ['You beat those diggers? Then', 'battle me, Arena style!'], 'Greta: Whoa, what a fighter!', ['Come back when you want a real', 'workout!'], None),
            ('AbundanceIsle_GaleCave', 'Noland', 'TRAINER_ABUNDANCE_NOLAND', 'NOLAND', ['Found my secret spot, huh? Let\'s', 'see what you\'ve got!'], 'Noland: Ha! Nice moves!', ['Keep this spot secret, yeah?'], None)):
        lb = f'{mp}_EventScript_{nm}'
        give = item_reward(lb, item) if item else ''
        add(mp, f'''{lb}::
	lock
	faceplayer
	goto_if_defeated {tr}, {lb}_After
	msgbox {lb}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro {tr}, {lb}_TextBeaten
{give}	release
	end

{lb}_After::
	msgbox {lb}_TextAfter, MSGBOX_DEFAULT
	release
	end

''' + (bagfull(lb) if item else '') + txt(lb + '_TextChallenge', a, speaker=spk) + txt(lb + '_TextBeaten', [b]) + txt(lb + '_TextAfter', after, speaker=spk) + '\n')

    # ---------------- eventos de mundo
    nb = 'AbundanceIsle_PokemonCenter_EventScript_NoticeBoard'
    add('AbundanceIsle_PokemonCenter', f'''{nb}::
	lockall
	goto_if_ge {S}, 9, {nb}_Festival
	goto_if_ge {S}, 4, {nb}_Clear
	msgbox {nb}_TextSnow, MSGBOX_SIGN
	releaseall
	end
{nb}_Clear::
	msgbox {nb}_TextClear, MSGBOX_SIGN
	releaseall
	end
{nb}_Festival::
	msgbox {nb}_TextFestival, MSGBOX_SIGN
	releaseall
	end

''' + txt(nb + '_TextSnow', ['NOTICE: Ferry delayed. Snow in', 'harvest season?! Farmers\' meeting', 'at the barn tonight.']) \
        + txt(nb + '_TextClear', ['NOTICE: Snow has stopped! Beware', 'of the strange ship at the cape.']) \
        + txt(nb + '_TextFestival', ['NOTICE: Spring is back! The farm', 'stand and the Festival Arena are', 'open every day.']) + '\n')
    pc = 'AbundanceIsle_PokemonCenter'
    add(pc, f'''{pc}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {pc}_OnTransition
	.byte 0

{pc}_OnTransition::
	setrespawn HEAL_LOCATION_WINDSWEPT_CAPE
	end

''')
    kw = 'AbundanceIsle_KeeperHouse_EventScript_Wife'
    add('AbundanceIsle_KeeperHouse', f'''{kw}::
	lock
	faceplayer
	goto_if_ge {S}, 10, {kw}_Letter
	msgbox {kw}_Text, MSGBOX_DEFAULT
	release
	end

{kw}_Letter::
	goto_if_set FLAG_ABUNDANCE_N_LETTER, {kw}_LetterRead
	msgbox {kw}_TextLetter, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_N_LETTER
	release
	end

{kw}_LetterRead::
	msgbox {kw}_TextLetterRead, MSGBOX_DEFAULT
	release
	end

''' + txt(kw + '_TextLetterRead', ['That young man writes the', 'loveliest letters. Go see Lenora,', 'dear!']) + txt(kw + '_Text', ['My husband hasn\'t slept since the', 'snow came. He talks to that', 'shrine all night.']) \
        + txt(kw + '_TextLetter', ['A letter came for you, dear.'], ['“The winds sound happy now. I', 'wanted you to know. Lenora found', 'something in the old stele...”'],
              ['“...go see her when you can. --N”']) + '\n')
    # arena: sorteio diario e batalha
    ar = 'AbundanceIsle_FestivalArena_EventScript_Receptionist'
    seats = [('ChallengerLeft1', 'TRAINER_ABUNDANCE_ARENA_LEON', 'LEON'), ('ChallengerLeft2', 'TRAINER_ABUNDANCE_ARENA_CYNTHIA', 'CYNTHIA'),
             ('ChallengerRight1', 'TRAINER_ABUNDANCE_ARENA_DIANTHA', 'DIANTHA'), ('ChallengerRight2', 'TRAINER_ABUNDANCE_ARENA_VOLKNER', 'VOLKNER')]
    s = f'''{ar}::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, {ar}_Done
	random 4
	copyvar VAR_ABUNDANCE_ARENA_PICK, VAR_RESULT
	msgbox {ar}_TextToday, MSGBOX_DEFAULT
	release
	end

{ar}_Done::
	msgbox {ar}_TextDone, MSGBOX_DEFAULT
	release
	end

''' + txt(ar + '_TextToday', ['Welcome to the Festival Arena!', 'Today\'s challenger is waiting', 'on the benches. Go talk to them!']) \
        + txt(ar + '_TextDone', ['That\'s today\'s match! Come back', 'tomorrow for a new challenger.']) + '\n'
    for k, (nm, tr, spk) in enumerate(seats):
        lb = f'AbundanceIsle_FestivalArena_EventScript_{nm}'
        s += f'''{lb}::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, {lb}_Rest
	goto_if_ne VAR_ABUNDANCE_ARENA_PICK, {k}, {lb}_Rest
	msgbox {lb}_TextChallenge, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag {tr}
	trainerbattle_no_intro {tr}, {lb}_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	release
	end

{lb}_Rest::
	msgbox {lb}_TextRest, MSGBOX_DEFAULT
	release
	end

''' + txt(lb + '_TextChallenge', ['So I\'m today\'s challenger.', 'Let\'s give the crowd a show!'], speaker=spk) \
            + txt(lb + '_TextBeaten', [spk.capitalize() + ': What a match!']) + txt(lb + '_TextRest', ['I\'m just watching today.'], speaker=spk) + '\n'
    add('AbundanceIsle_FestivalArena', s)
    # revanche diaria da dupla (santuario)
    # (o script do N/Hilda no santuario ja existe no fase2; a revanche entra no ramo _NDone)

    # ---------------- para-raios do 3F (portoes por FLAG_TEMP, recomecam a cada visita)
    t3 = 'Thunderspire_3F'
    GATES = {'A': (6, 16), 'B': (14, 12), 'C': (20, 9), 'D': (17, 6)}
    GF = {'A': 'FLAG_TEMP_15', 'B': 'FLAG_TEMP_16', 'C': 'FLAG_TEMP_17', 'D': 'FLAG_TEMP_18'}
    RODS = {'RodEarth': 'A', 'RodWind': 'AB', 'RodThunder': 'BC', 'RodIdeal': 'CD'}
    s = ''
    for g, (x, y) in GATES.items():
        s += f'''{t3}_EventScript_Toggle{g}::
	goto_if_set {GF[g]}, {t3}_EventScript_Close{g}
	setflag {GF[g]}
	setmetatile {x}, {y}, 0x400, FALSE
	return
{t3}_EventScript_Close{g}::
	clearflag {GF[g]}
	setmetatile {x}, {y}, 0x407, TRUE
	return

'''
    for rod, gs in RODS.items():
        lb = f'{t3}_EventScript_{rod}'
        s += f'{lb}::\n\tlockall\n\tmsgbox {lb}_Text, MSGBOX_DEFAULT\n\tclosemessage\n\tplayse SE_THUNDER\n' \
             + ''.join(f'\tcall {t3}_EventScript_Toggle{g}\n' for g in gs) + '\tspecial DrawWholeMapView\n\treleaseall\n\tend\n\n' \
             + txt(lb + '_Text', ['{PLAYER} touched the lightning rod.', 'Thunder rumbles through the tower!']) + '\n'
    s += f'{t3}_EventScript_Mural::\n\tmsgbox {t3}_EventScript_Mural_Text, MSGBOX_SIGN\n\tend\n\n' + \
        txt(f'{t3}_EventScript_Mural_Text', ['“First the earth wakes, then the', 'wind rises, then the thunder falls;', 'only then may the ideal be struck.”']) + '\n'
    add(t3, s)

    # ================= sabados, noite na vila, sino e dias de tempestade (31/10/2026)
    SAT = '\tspecialvar VAR_RESULT, GetDayOfWeek\n'
    # hub: chama a visibilidade da barraca de sabado (o OnTransition do hub e do fase2)
    sub('AbundanceIsle', '\tcall AbundanceIsle_EventScript_Vis_TEMP_14\n',
        '\tcall AbundanceIsle_EventScript_Vis_TEMP_14\n\tcall AbundanceIsle_EventScript_Vis_TEMP_15\n')
    # barraca "honesta" de Jessie e James (sabado, depois do Frigate)
    hs = 'AbundanceIsle_EventScript_HonestStand'
    add('AbundanceIsle', f"""{hs}::
	lock
	faceplayer
	msgbox {hs}_Text, MSGBOX_DEFAULT
	pokemart {hs}_Mart
	msgbox {hs}_TextBye, MSGBOX_DEFAULT
	release
	end

	.align 2
{hs}_Mart:
	.2byte ITEM_MOOMOO_MILK
	.2byte ITEM_LEMONADE
	.2byte ITEM_SODA_POP
	.2byte ITEM_HONEY
	.2byte ITEM_BIG_MUSHROOM
	.2byte ITEM_TINY_MUSHROOM
	.2byte ITEM_NONE

""" + txt(hs + '_Text', ['Welcome to Team Rocket\'s perfectly', 'honest Saturday stand!'],
          ['{SPEAKER NAME_JAMES}Everything bought fair and square!', 'Mostly. Well, partly.'], speaker='JESSIE')
        + txt(hs + '_TextBye', ['Come back next Saturday! We\'ll', 'still be honest... probably.'], speaker='JESSIE') + '\n')
    # oferenda no santuario (sabado: um item da colheita por dia)
    of = 'AbundanceIsle_EventScript_Offering'
    add('AbundanceIsle', f"""{of}::
	lockall
{SAT}	goto_if_ne VAR_RESULT, WEEKDAY_SAT, {of}_Weekday
	goto_if_lt {S}, 9, {of}_Weekday
	goto_if_set FLAG_DAILY_ABUNDANCE_OFFERING, {of}_Done
	random 6
	goto_if_eq VAR_RESULT, 1, {of}_I1
	goto_if_eq VAR_RESULT, 2, {of}_I2
	goto_if_eq VAR_RESULT, 3, {of}_I3
	goto_if_eq VAR_RESULT, 4, {of}_I4
	goto_if_eq VAR_RESULT, 5, {of}_I5
	setvar VAR_0x8008, ITEM_SITRUS_BERRY
	goto {of}_Give
{of}_I1::
	setvar VAR_0x8008, ITEM_LUM_BERRY
	goto {of}_Give
{of}_I2::
	setvar VAR_0x8008, ITEM_MIRACLE_SEED
	goto {of}_Give
{of}_I3::
	setvar VAR_0x8008, ITEM_SWEET_APPLE
	goto {of}_Give
{of}_I4::
	setvar VAR_0x8008, ITEM_BIG_ROOT
	goto {of}_Give
{of}_I5::
	setvar VAR_0x8008, ITEM_MOOMOO_MILK
{of}_Give::
	msgbox {of}_TextSaturday, MSGBOX_DEFAULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, {of}_BagFull
	giveitem VAR_0x8008
	setflag FLAG_DAILY_ABUNDANCE_OFFERING
	releaseall
	end

{of}_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	releaseall
	end

{of}_Done::
	msgbox {of}_TextDone, MSGBOX_DEFAULT
	releaseall
	end

{of}_Weekday::
	msgbox {of}_TextWeekday, MSGBOX_DEFAULT
	releaseall
	end

""" + txt(of + '_TextWeekday', ['A small offering stone before the', 'shrine.'], ['On Saturdays, the village leaves the', 'first fruits of the harvest here.'])
        + txt(of + '_TextSaturday', ['Fresh fruits of the harvest rest on', 'the offering stone.'], ['The shrine seems to want {PLAYER}', 'to take one.'])
        + txt(of + '_TextDone', ['The offering stone is bare. The', 'shrine has given enough today.']) + '\n')
    # barraca da fazenda: no sabado vem tambem um Mulch
    fm = 'AbundanceIsle_EventScript_Farmer'
    sub('AbundanceIsle', '\tgiveitem VAR_0x8008\n\tsetflag FLAG_DAILY_ABUNDANCE_FARM_STAND\n\trelease\n',
        f'\tgiveitem VAR_0x8008\n\tsetflag FLAG_DAILY_ABUNDANCE_FARM_STAND\n\tcall {fm}_SaturdayMulch\n\trelease\n')
    add('AbundanceIsle', f"""{fm}_SaturdayMulch::
{SAT}	goto_if_ne VAR_RESULT, WEEKDAY_SAT, {fm}_Return
	random 4
	setvar VAR_0x8008, ITEM_GROWTH_MULCH
	call_if_eq VAR_RESULT, 1, {fm}_MulchDamp
	call_if_eq VAR_RESULT, 2, {fm}_MulchStable
	call_if_eq VAR_RESULT, 3, {fm}_MulchGooey
	msgbox {fm}_TextMulch, MSGBOX_DEFAULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, {fm}_Return
	giveitem VAR_0x8008
{fm}_Return::
	return
{fm}_MulchDamp::
	setvar VAR_0x8008, ITEM_DAMP_MULCH
	return
{fm}_MulchStable::
	setvar VAR_0x8008, ITEM_STABLE_MULCH
	return
{fm}_MulchGooey::
	setvar VAR_0x8008, ITEM_GOOEY_MULCH
	return

""" + txt(fm + '_TextMulch', ['It\'s Saturday market! Take some', 'mulch for your own berries, too.'], speaker='FARMER') + '\n')
    # arena no sabado: bancos vazios, N e Hilda esperam a dupla
    ar = 'AbundanceIsle_FestivalArena_EventScript_Receptionist'
    sub('AbundanceIsle_FestivalArena', f'{ar}::\n\tlock\n\tfaceplayer\n',
        f'{ar}::\n\tlock\n\tfaceplayer\n\tgoto_if_lt {S}, 14, {ar}_Normal\n{SAT}\tgoto_if_eq VAR_RESULT, WEEKDAY_SAT, {ar}_Saturday\n{ar}_Normal::\n')
    add('AbundanceIsle_FestivalArena', f"""{ar}_Saturday::
	msgbox {ar}_TextSaturday, MSGBOX_DEFAULT
	release
	end

""" + txt(ar + '_TextSaturday', ['Saturdays are special! The benches', 'are empty...'], ['...because two very special guests', 'are waiting by the field. Go on!']) + '\n')
    sd = 'AbundanceIsle_FestivalArena_EventScript_SaturdayDuo'
    for nm in ('SaturdayN', 'SaturdayHilda'):
        add('AbundanceIsle_FestivalArena', f'AbundanceIsle_FestivalArena_EventScript_{nm}::\n\tgoto {sd}\n\n')
    add('AbundanceIsle_FestivalArena', f"""{sd}::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_ARENA, {sd}_Done
	msgbox {sd}_TextChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {sd}_No
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_N_AND_HILDA
	trainerbattle_no_intro TRAINER_ABUNDANCE_N_AND_HILDA, {sd}_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_ARENA
	msgbox {sd}_TextAfter, MSGBOX_DEFAULT
	release
	end

{sd}_No::
	release
	end

{sd}_Done::
	msgbox {sd}_TextAfter, MSGBOX_DEFAULT
	release
	end

""" + txt(sd + '_TextChallenge', ['{PLAYER}! The crowd wants a double', 'battle. Will you give them one?'],
          ['{SPEAKER NAME_HILDA}Don\'t hold back. We won\'t!'], speaker='N')
        + txt(sd + '_TextBeaten', ['N: The crowd sounds... happy.'])
        + txt(sd + '_TextAfter', ['Every Saturday we come here. It\'s', 'the only crowd N doesn\'t mind.'], speaker='HILDA') + '\n')
    # noite na vila: portas trancadas (sLockedTownDoors, src/field_control_avatar.c)
    for mp in ('AbundanceIsle_WindsweptCape', 'AbundanceIsle_HarvestFields'):
        lk = f'{mp}_EventScript_DoorLocked'
        add(mp, f'{lk}::\n\tmsgbox {lk}_Text, MSGBOX_SIGN\n\tend\n\n' +
            txt(lk + '_Text', ['The door is locked. Everyone in', 'the village has gone home for', 'the night.']) + '\n')
    # cabo: MapScripts proprio (visibilidade + sino das 18h, so depois que a primavera voltou)
    cp = 'AbundanceIsle_WindsweptCape'
    add(cp, f"""{cp}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {cp}_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, {cp}_OnFrame
	.byte 0

{cp}_OnTransition::
	call {cp}_EventScript_Vis_TEMP_11
	call {cp}_EventScript_Vis_TEMP_1E
	end

{cp}_OnFrame::
	map_script_2 VAR_TEMP_1, 0, {cp}_EventScript_Bell
	.2byte 0

{cp}_EventScript_Bell::
	setvar VAR_TEMP_1, 1
	goto_if_lt {S}, 9, {cp}_EventScript_BellEnd
	gettime
	goto_if_ne VAR_0x8000, 18, {cp}_EventScript_BellEnd
	lockall
	playse SE_M_HEAL_BELL
	waitse
	msgbox {cp}_Text_Bell, MSGBOX_DEFAULT
	releaseall
{cp}_EventScript_BellEnd::
	end

""" + txt(f'{cp}_Text_Bell', ['Ding... dong...'], ['The harvest bell rings across the', 'village. Time to come home.']) + '\n')
    # dias de tempestade (pos-jogo): sorteio 1x por dia, clima, tabela de selvagens (C) e revanches
    def storm(mp, vis, weather):
        add(mp, f"""{mp}_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, {mp}_OnTransition
	.byte 0

{mp}_OnTransition::
""" + ''.join(f'\tcall {mp}_EventScript_Vis_{v}\n' for v in vis) + f"""	call {mp}_EventScript_StormRoll
	call_if_eq VAR_ABUNDANCE_STORM, 1, {mp}_EventScript_StormWeather
	end

{mp}_EventScript_StormRoll::
	goto_if_ge {S}, 14, {mp}_EventScript_StormRollDay
	setvar VAR_ABUNDANCE_STORM, 0
	return
{mp}_EventScript_StormRollDay::
	goto_if_set FLAG_DAILY_ABUNDANCE_STORM_ROLLED, {mp}_EventScript_StormRollEnd
	setflag FLAG_DAILY_ABUNDANCE_STORM_ROLLED
	setvar VAR_ABUNDANCE_STORM, 0
	random 3
	goto_if_ne VAR_RESULT, 0, {mp}_EventScript_StormRollEnd
	setvar VAR_ABUNDANCE_STORM, 1
{mp}_EventScript_StormRollEnd::
	return

{mp}_EventScript_StormWeather::
	setweather {weather}
	return

""")
    storm('ThunderRidge', ['TEMP_11', 'TEMP_12'], 'WEATHER_RAIN_THUNDERSTORM')
    storm('AbundanceIsle_GaleShore', ['TEMP_11'], 'WEATHER_DOWNPOUR')
    for mp, nm, tr, spk, line in (('ThunderRidge', 'Volkner', 'TRAINER_ABUNDANCE_VOLKNER', 'VOLKNER', ['Lightning everywhere. Now THIS', 'is battle weather. Again?']),
                                  ('ThunderRidge', 'Elesa', 'TRAINER_ABUNDANCE_ELESA', 'ELESA', ['A storm runway! Shall we shine', 'once more?']),
                                  ('AbundanceIsle_GaleShore', 'Winona', 'TRAINER_ABUNDANCE_WINONA', 'WINONA', ['Feel that wind? My Pokemon want', 'a rematch in it!'])):
        lb = f'{mp}_EventScript_{nm}'
        sub(mp, f'{lb}_After::\n', f'{lb}_After::\n\tgoto_if_eq VAR_ABUNDANCE_STORM, 1, {lb}_StormRematch\n')
        add(mp, f"""{lb}_StormRematch::
	msgbox {lb}_TextStorm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, {lb}_StormNo
	closemessage
	cleartrainerflag {tr}
	trainerbattle_no_intro {tr}, {lb}_TextBeaten
	release
	end
{lb}_StormNo::
	release
	end

""" + txt(lb + '_TextStorm', line, speaker=spk) + '\n')

    # ---------------- falas proprias no lugar dos "..." do esqueleto
    FILL = {
     'AbundanceIsle': [('FarmerWife', None, [['My husband counts every sack of', 'seed twice. Since the storm, he', 'counts them three times.']])],
     'AbundanceIsle_Barn': [('Kid', None, [['The Miltank stopped giving milk', 'when the snow came.'], ['Mom says it\'s too cold. I say', 'the Miltank is sad.']])],
     'AbundanceIsle_Farmhouse': [('Grandpa', None, [['When I was a boy, the old folk', 'told of a year with no harvest.'], ['“The cold star fell,” they said.', 'I thought it was just a story.']]),
                                 ('Wife', None, [['Help yourself to some tea, dear.', 'It\'s the only warm thing left', 'on this island.']])],
     'AbundanceIsle_KeeperHouse': [('Apprentice', None, [['The Keeper says the shrine', 'remembers every harvest.'], ['I\'m supposed to sweep it every', 'morning... even in the snow.']])],
     'AbundanceIsle_WindsweptCape': [('DockGuard1', 'GRUNT', [['This dock belongs to Team Plasma', 'now! Go back the way you came!']]),
                                     ('DockGuard2', 'GRUNT', [['Our frigate is anchored here', 'for the liberation of Pokemon!']]),
                                     ('DockGuard3', 'GRUNT', [['Lord Ghetsis will make the winter', 'last forever. Shiver all you like!']]),
                                     ('Nessa', 'NESSA', [['The sea around this cape is', 'wild. The wind spins in circles.'], ['Even my Drednaw doesn\'t like', 'swimming here.']]),
                                     ('Skyla', 'SKYLA', [['From up here you can see the', 'storm turning around the crater.'], ['Like the whole sky is being', 'pulled toward it...']]),
                                     ('Sailor', None, [['The ferry won\'t sail while that', 'Plasma ship blocks the dock.']])],
     'AbundanceIsle_PokemonCenter': [('Girl', None, [['I came for the harvest festival,', 'but it\'s snowing!'], ['My Vulpix loves it, at least.']]),
                                     ('Sailor', None, [['Strange winds out at sea. Like', 'two storms fighting each other.']]),
                                     ('OldWoman', None, [['In my mother\'s time, a spring', 'visitor came across the sea.'], ['When it left the island, the', 'flowers wouldn\'t open.']])],
     'AbundanceIsle_SkylaHangar': [('Mechanic', 'MECHANIC', [['The engine\'s fine. It\'s the', 'weather that\'s broken!'], ['No pilot flies into a storm that', 'turns in circles.']])],
     'AbundanceIsle_ElderHouse': [('Elder', None, [['The bell of this house rings at', 'dusk, to call the harvest home.'], ['It hasn\'t rung since the snow.', 'Nothing is coming home.']]),
                                  ('Granddaughter', None, [['Grandpa rings the bell every', 'evening. Come back at dusk!']]),
                                  ('ElderBellTime', None, [['Dusk... time for the bell.'], ['Ding... dong...', 'May the harvest come home.']]),
                                  ('BookYearWithoutHarvest', None, [['“The Year Without Harvest.”'], ['“A star of ice fell into the', 'crater. Snow covered the fields', 'for a whole year...”']]),
                                  ('BookForcesOfNature', None, [['“The Forces of Nature.”'], ['“The Wind Genie and the Thunder', 'Genie fought over the sky. The', 'Lord of the Land calmed them.”']]),
                                  ('BookHeraldOfSpring', None, [['“The Herald of Spring.”'], ['“She comes from across the sea', 'when the winter ends, and love', 'blooms where she walks.”']]),
                                  ('BellRope', None, [['The rope of the harvest bell.', 'It\'s worn smooth by many hands.']])],
     'FrostfallCrater_Lab': [('ScientistA', 'SCIENTIST', [['The meteor\'s cold is limitless!', 'With it, Kyurem can be controlled!']]),
                             ('ScientistB', 'SCIENTIST', [['The machine splits the DNA of the', 'ice dragon... in theory.']])],
     'Thunderspire_1F': [('Cheren', 'CHEREN', [['The Plasma are guarding the', 'stairs. Something is up there.'], ['Be careful. I\'ll keep these', 'grunts busy down here.']])],
     'Thunderspire_Summit': [('DarkStone', None, [['A black stone, crackling with', 'static. It feels... watchful.']])],
     'PlasmaFrigate_EngineRoom': [('DNAConsole', None, [['“PROJECT: SPLIT DRAGON”'], ['“Goal: separate Kyurem from', 'the cold and fuse it with the', 'hero dragons.”']]),
                                  ('ColdCondenser', None, [['A condenser full of crackling', 'ice. It hums with a deep cold.']]),
                                  ('ColdStorageDoor', None, [['“COLD STORAGE. Authorized', 'personnel only.”']])],
     'AbundanceIsle_FestivalArena': [('Fan1', None, [['Every day there\'s a new', 'challenger. I never miss one!']]),
                                     ('Fan2', None, [['I saw a Champion here yesterday!', 'Or was it a Gym Leader?']]),
                                     ('Fan3', None, [['The festival only came back once', 'spring did. Thank you, kid!']]),
                                     ('TodaysBoard', None, [['FESTIVAL ARENA', 'One challenger a day!'], ['Ask at the counter to see who', 'is waiting on the benches.']])],
     'AbundanceIsle_SunsetStrait': [('Shelly', 'SHELLY', [['The sunsets here are the', 'best in the world. Don\'t argue.']]),
                                    ('Juan', 'JUAN', [['Beneath these waves sleeps an', 'old ship. The water remembers it.']]),
                                    ('Tate', 'TATE', [['Liza went to the shrine without', 'me! We always do things together!']])],
     'SunkenTruthShip': [('Phoebe', 'PHOEBE', [['This ship carried the Light', 'Stone once. Its spirits are', 'still keeping watch.']]),
                         ('MuralLightStone', None, [['A carving of a white stone,', 'carried away from a burning city.']]),
                         ('CaptainsLog', None, [['The captain\'s log...'], ['“We carry the white stone south,', 'to the island of sand, where the', 'sun sets. Let it sleep there.”']]),
                         ('Figurehead', None, [['A figurehead shaped like a', 'white dragon. Barnacles cover', 'its wings.']])],
     'ShrineOfTheFirstDragon': [('Leon', 'LEON', [['A legend of two brothers and', 'their dragon. I\'ve heard it told', 'a hundred different ways.']]),
                                ('Diantha', 'DIANTHA', [['Truth and ideals... like two', 'roles one actor plays. Neither is', 'false.']])],
     'NsRoom': [('Dolls', None, [['A row of old Pokemon dolls,', 'lovingly patched up.']]),
                ('Cushion', None, [['A worn cushion. Zorua seems', 'to like napping here.']]),
                ('PC', None, [['N\'s PC. A file is open:', '“Letters I never sent.”']]),
                ('Bookshelf', None, [['Books on math, myths and', 'the history of Unova.']]),
                ('ToyTrain', None, [['A toy train circles the track.', 'Round and round, never stopping.']])],
     'TruthsandRuins_1F': [('MuralTruth', None, [['“To find the truth, walk where', 'the sand swallows the sun.”']]),
                           ('Sign', None, [['TRUTHSAND RUINS', 'Beware of quicksand!']])],
     'TruthsandRuins_B1F': [('Greta', 'GRETA', [['These ruins are a great', 'workout. I\'ll meet you on', 'Emberdune when you\'re ready!']]),
                            ('GateInscription', None, [['“Beyond this gate rests the', 'stone of truth. Enter with', 'an honest heart.”']]),
                            ('TrailInscription', None, [['“Follow the sun\'s path through', 'the sand.”']])],
     'TruthsandRuins_HallOfTruth': [('Grunt1', 'GRUNT', [['Lord Ghetsis is at the altar.', 'You\'re too late!']]),
                                    ('Grunt2', 'GRUNT', [['The Light Stone will be ours!', 'Then both dragons obey us!']]),
                                    ('Hilda', 'HILDA', [['Ghetsis is right there. We', 'stop him here, together.']]),
                                    ('Lenora', 'LENORA', [['History won\'t repeat itself.', 'Not on my watch!']])],
    }
    for mp, rows in FILL.items():
        mj = json.load(open(os.path.join(R, 'data/maps', mp, 'map.json')))
        bgs = {b.get('script') for b in mj['bg_events']}
        for nm, spk, pages in rows:
            lb = f'{mp}_EventScript_{nm}'
            assert not re.search(r'^%s::' % lb, F.get(mp, ''), re.M), lb
            kind = 'MSGBOX_SIGN' if lb in bgs else 'MSGBOX_NPC'
            add(mp, f'{lb}::\n\tmsgbox {lb}_Text, {kind}\n\tend\n\n' + txt(lb + '_Text', *pages, speaker=spk) + '\n')
    return F

if __name__ == '__main__':
    ex = place()
    for d, e in ex.items():
        print(d, [(b.get('script', b.get('item')), b['x'], b['y']) for b in e['bg']], [(o['local_id'], o['x'], o['y']) for o in e['objects']])
