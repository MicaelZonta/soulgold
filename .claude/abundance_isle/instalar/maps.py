"""Instala os 24 mapas da Abundance Isle no repositorio (fase 1: mapas, ligacoes, objetos,
visibilidade por estado, itens). Idempotente: pode rodar de novo (reescreve o que e dele)."""
import json, os, re, shutil, glob, sys
R = '/home/ADMIN/decomps/soulgold_v1'
SC = os.path.join(R, '.claude/abundance_isle')
M20 = SC + '/mapas'
os.chdir(R)

# --------------------------------------------------------------------------- tabela de mapas
# dir m20 -> (nome do mapa, MAPSEC, musica, tipo override)
MAPS = {
 'AbundanceIsle':              ('AbundanceIsle', 'MAPSEC_ABUNDANCE_ISLE', 'MUS_HG_ROUTE38'),
 'AbundanceIsle_Barn':         ('AbundanceIsle_Barn', 'MAPSEC_ABUNDANCE_ISLE', 'MUS_HG_ROUTE38'),
 'AbundanceIsle_Farmhouse':    ('AbundanceIsle_Farmhouse', 'MAPSEC_ABUNDANCE_ISLE', 'MUS_HG_ROUTE38'),
 'AbundanceIsle_HarvestFields':('AbundanceIsle_HarvestFields', 'MAPSEC_HARVEST_FIELDS', 'MUS_HG_ROUTE38'),
 'AbundanceIsle_KeeperHouse':  ('AbundanceIsle_KeeperHouse', 'MAPSEC_HARVEST_FIELDS', 'MUS_HG_ROUTE38'),
 'AbundanceIsle_SpringGrove':  ('AbundanceIsle_SpringGrove', 'MAPSEC_SPRING_GROVE', 'MUS_DP_LAKE'),
 'AbundanceIsle_WindsweptCape':('AbundanceIsle_WindsweptCape', 'MAPSEC_WINDSWEPT_CAPE', 'MUS_HG_CIANWOOD'),
 'AbundanceIsle_PokemonCenter':('AbundanceIsle_PokemonCenter', 'MAPSEC_WINDSWEPT_CAPE', 'MUS_HG_POKE_CENTER'),
 'AbundanceIsle_SkylaHangar':  ('AbundanceIsle_SkylaHangar', 'MAPSEC_WINDSWEPT_CAPE', 'MUS_HG_CIANWOOD'),
 'AbundanceIsle_ElderHouse':   ('AbundanceIsle_ElderHouse', 'MAPSEC_WINDSWEPT_CAPE', 'MUS_HG_CIANWOOD'),
 'AbundanceIsle_GaleShore':    ('AbundanceIsle_GaleShore', 'MAPSEC_GALE_SHORE', 'MUS_DP_ROUTE216_DAY'),
 'AbundanceIsle_GaleCave':     ('AbundanceIsle_GaleCave', 'MAPSEC_GALE_CAVE', 'MUS_HG_UNION_CAVE'),
 'FROSTFALL_CRATER_1F':        ('FrostfallCrater_1F', 'MAPSEC_FROSTFALL_CRATER', 'MUS_HG_ICE_PATH'),
 'FROSTFALL_CRATER_B1F':       ('FrostfallCrater_B1F', 'MAPSEC_FROSTFALL_CRATER', 'MUS_HG_ICE_PATH'),
 'FROSTFALL_CRATER_LAB':       ('FrostfallCrater_Lab', 'MAPSEC_FROSTFALL_CRATER', 'MUS_HG_ICE_PATH'),
 'FROSTFALL_CRATER_CORE':      ('FrostfallCrater_Core', 'MAPSEC_FROSTFALL_CRATER', 'MUS_HG_ICE_PATH'),
 'THUNDER_RIDGE':              ('ThunderRidge', 'MAPSEC_THUNDER_RIDGE', 'MUS_DP_STARK_MOUNTAIN'),
 'THUNDERSPIRE_1F':            ('Thunderspire_1F', 'MAPSEC_THUNDERSPIRE', 'MUS_HG_BURNED_TOWER'),
 'THUNDERSPIRE_2F':            ('Thunderspire_2F', 'MAPSEC_THUNDERSPIRE', 'MUS_HG_BURNED_TOWER'),
 'ThunderspireSummit':         ('Thunderspire_Summit', 'MAPSEC_THUNDERSPIRE', 'MUS_DP_SPEAR_PILLAR'),
 'PLASMA_FRIGATE_DECK':        ('PlasmaFrigate_Deck', 'MAPSEC_PLASMA_FRIGATE', 'MUS_HG_SS_AQUA'),
 'PLASMA_FRIGATE_HOLD':        ('PlasmaFrigate_Hold', 'MAPSEC_PLASMA_FRIGATE', 'MUS_HG_SS_AQUA'),
 'PLASMA_FRIGATE_CABINS':      ('PlasmaFrigate_Cabins', 'MAPSEC_PLASMA_FRIGATE', 'MUS_HG_SS_AQUA'),
 'PLASMA_FRIGATE_ENGINE_ROOM': ('PlasmaFrigate_EngineRoom', 'MAPSEC_PLASMA_FRIGATE', 'MUS_HG_SS_AQUA'),
 'THUNDERSPIRE_3F':            ('Thunderspire_3F', 'MAPSEC_THUNDERSPIRE', 'MUS_HG_BURNED_TOWER'),
 'AbundanceIsle_FestivalArena':('AbundanceIsle_FestivalArena', 'MAPSEC_WINDSWEPT_CAPE', 'MUS_HG_POKE_CENTER'),
 'AbundanceIsle_SunsetStrait': ('AbundanceIsle_SunsetStrait', 'MAPSEC_SUNSET_STRAIT', 'MUS_HG_ROUTE38'),
 'AbundanceIsle_SunsetStrait_Underwater': ('AbundanceIsle_SunsetStrait_Underwater', 'MAPSEC_SUNSET_STRAIT', 'MUS_HG_ROUTE38'),
 'SunkenTruthShip':            ('SunkenTruthShip', 'MAPSEC_SUNSET_STRAIT', 'MUS_HG_SS_AQUA'),
 'ShrineOfTheFirstDragon':     ('ShrineOfTheFirstDragon', 'MAPSEC_SHRINE_OF_THE_FIRST_DRAGON', 'MUS_DP_SPEAR_PILLAR'),
 'EmberduneIsle':              ('EmberduneIsle', 'MAPSEC_EMBERDUNE_ISLE', 'MUS_HG_ROUTE38'),
 'NsRoom':                     ('NsRoom', 'MAPSEC_EMBERDUNE_ISLE', 'MUS_HG_ROUTE38'),
 'TRUTHSAND_RUINS_1F':         ('TruthsandRuins_1F', 'MAPSEC_TRUTHSAND_RUINS', 'MUS_HG_UNION_CAVE'),
 'TRUTHSAND_RUINS_B1F':        ('TruthsandRuins_B1F', 'MAPSEC_TRUTHSAND_RUINS', 'MUS_HG_UNION_CAVE'),
 'TRUTHSAND_RUINS_HALL_OF_TRUTH': ('TruthsandRuins_HallOfTruth', 'MAPSEC_TRUTHSAND_RUINS', 'MUS_DP_SPEAR_PILLAR'),
}
MAPSECS = [('MAPSEC_ABUNDANCE_ISLE', 'Abundance Isle'), ('MAPSEC_HARVEST_FIELDS', 'Harvest Fields'),
           ('MAPSEC_SPRING_GROVE', 'Spring Grove'), ('MAPSEC_WINDSWEPT_CAPE', 'Windswept Cape'),
           ('MAPSEC_GALE_SHORE', 'Gale Shore'), ('MAPSEC_GALE_CAVE', 'Gale Cave'),
           ('MAPSEC_FROSTFALL_CRATER', 'Frostfall Crater'), ('MAPSEC_THUNDER_RIDGE', 'Thunder Ridge'),
           ('MAPSEC_THUNDERSPIRE', 'Thunderspire'), ('MAPSEC_PLASMA_FRIGATE', 'Plasma Frigate'),
           ('MAPSEC_SUNSET_STRAIT', 'Sunset Strait'), ('MAPSEC_EMBERDUNE_ISLE', 'Emberdune Isle'),
           ('MAPSEC_TRUTHSAND_RUINS', 'Truthsand Ruins'), ('MAPSEC_SHRINE_OF_THE_FIRST_DRAGON', 'First Dragon Shrine')]
SECONDARY_SWAP = {'gTileset_Route38_Farmland': 'gTileset_AbundanceFarmland', 'gTileset_Cave_Ice': 'gTileset_FrostfallCrater',
                  'gTileset_Goldenrod_Underground_Storage': 'gTileset_SkylaHangar'}
GROUP = 'gMapGroup_AbundanceIsle'
ORDER = list(MAPS)

def mapid(name):  # AbundanceIsle_HarvestFields -> MAP_ABUNDANCE_ISLE_HARVEST_FIELDS
    s = re.sub(r'(?<=[a-z])(?=[A-Z0-9])|(?<=[A-Z])(?=[A-Z][a-z])', '_', name).upper()
    return 'MAP_' + re.sub(r'_+', '_', s)
INFO = {d: json.load(open(f'{M20}/{d}/info.json')) for d in ORDER}
OLD2NEW = {}  # constante usada pelos forks -> constante real
for d in ORDER:
    i = INFO[d]; m = i['map']
    old = 'MAP_' + m if m.isupper() else mapid(m)
    OLD2NEW[old] = mapid(MAPS[d][0])
OLD2NEW['MAP_THUNDERSPIRE_SUMMIT'] = mapid('Thunderspire_Summit')
for d in ORDER: assert mapid(MAPS[d][0]) not in ('',), d
def short(d): return mapid(MAPS[d][0])[4:]

# --------------------------------------------------------------------------- itens
ITEMS = set(re.findall(r'\b(ITEM_[A-Z0-9_]+)\b', open('include/constants/items.h').read())) | {'ITEM_TM_BLIZZARD'}
ITEM_FIX = {'ITEM_SOOTH_BELL': 'ITEM_SOOTHE_BELL', 'ITEM_WIND_STONE_SHARD': 'ITEM_WIDE_LENS', 'ITEM_DIG_KIT': 'ITEM_RELIC_COPPER'}
def item_of(script):
    m = re.search(r'Item(?:Hidden)?([A-Z][A-Za-z0-9]*)$', script)
    c = 'ITEM_' + re.sub(r'(?<=[a-z0-9])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])', '_', m.group(1)).upper()
    c = ITEM_FIX.get(c, c)
    assert c in ITEMS, (script, c)
    return c

# --------------------------------------------------------------------------- objetos: remocoes, extras, visibilidade
DROP = {'AbundanceIsle': {'TORNADUS', 'THUNDURUS', 'ENAMORUS'}, 'FROSTFALL_CRATER_LAB': {'ITEM_ICESTONE'}}
EXTRA = {'ThunderspireSummit': [dict(local_id='DARK_STONE', graphics_id='OBJ_EVENT_GFX_DARK_STONE', x=18, y=13, elevation=3,
          movement_type='MOVEMENT_TYPE_FACE_DOWN', movement_range_x=0, movement_range_y=0, trainer_type='TRAINER_TYPE_NONE',
          trainer_sight_or_berry_tree_id='0', script='Thunderspire_Summit_EventScript_DarkStone', flag='0')]}
# visibilidade: mapa -> {grupo FLAG_TEMP: (condicao de MOSTRAR em asm, [sufixos de local_id])}
S = 'VAR_ABUNDANCE_ISLE_STATE'
VIS = {
 'AbundanceIsle': {
   'FLAG_TEMP_11': ('lt4', ['N', 'HILDA', 'TORNADUS_STORM', 'THUNDURUS_STORM']),
   'FLAG_TEMP_12': ('lt2', ['GRUNT_1', 'GRUNT_2']),
   'FLAG_TEMP_13': ('landorus', ['LANDORUS']),
   'FLAG_TEMP_14': ('dock', ['N_DOCK', 'HILDA_DOCK'])},
 'AbundanceIsle_GaleShore': {'FLAG_TEMP_11': ('tornadus', ['TORNADUS'])},
 'THUNDER_RIDGE': {'FLAG_TEMP_11': ('thundurus', ['THUNDURUS']), 'FLAG_TEMP_12': ('lt5', ['GRUNT'])},
 'AbundanceIsle_WindsweptCape': {'FLAG_TEMP_11': ('lt4', ['GRUNT_DOCK_1', 'GRUNT_DOCK_2', 'GRUNT_DOCK_3'])},
 'AbundanceIsle_SpringGrove': {'FLAG_TEMP_11': ('enamorus', ['ENAMORUS'])},
 'AbundanceIsle_SkylaHangar': {'FLAG_TEMP_11': ('lt4', ['SKYLA']), 'FLAG_TEMP_12': ('ge4', ['SKYLA_READY'])},
 'AbundanceIsle_ElderHouse': {'FLAG_TEMP_11': ('day', ['ELDER']), 'FLAG_TEMP_12': ('dusk', ['ELDER_BELL'])},
 'FROSTFALL_CRATER_LAB': {'FLAG_TEMP_11': ('lt4', ['GHETSIS', 'SCIENTIST_A', 'SCIENTIST_B']), 'FLAG_TEMP_12': ('n_lab', ['N_LAB'])},
 'EmberduneIsle': {'FLAG_TEMP_11': ('eq11', ['HILDA', 'LENORA'])},
 'NsRoom': {'FLAG_TEMP_11': ('eq11', ['N', 'HILDA', 'ZORUA'])},
 'TRUTHSAND_RUINS_HALL_OF_TRUTH': {'FLAG_TEMP_11': ('eq11', ['GHETSIS', 'GRUNT_1', 'GRUNT_2', 'HILDA', 'LENORA']),
                                   'FLAG_TEMP_12': ('lt12', ['LIGHT_STONE']),
                                   'FLAG_TEMP_13': ('reshiram', ['RESHIRAM', 'HILDA_AFTER'])},
 'ShrineOfTheFirstDragon': {'FLAG_TEMP_11': ('ge13', ['N', 'HILDA'])},
 'ThunderspireSummit': {'FLAG_TEMP_11': ('lt6', ['GHETSIS', 'N', 'TORNADUS_SKY', 'THUNDURUS_SKY', 'DARK_STONE']),
                        'FLAG_TEMP_12': ('eq6', ['ZEKROM', 'N_AFTER', 'HILDA_AFTER'])},
}
# condicoes: rotulo -> corpo asm que pula para _Show quando deve mostrar (cai em _Hide se nao)
def cond_asm(c, show):
    if c.startswith('lt'): return f'\tgoto_if_lt {S}, {c[2:]}, {show}\n'
    if c.startswith('ge'): return f'\tgoto_if_ge {S}, {c[2:]}, {show}\n'
    if c.startswith('eq'): return f'\tgoto_if_eq {S}, {c[2:]}, {show}\n'
    if c == 'tornadus':  return f'\tgoto_if_set FLAG_ABUNDANCE_TORNADUS_DONE, {show}_No\n\tgoto_if_ge {S}, 4, {show}\n'
    if c == 'thundurus': return f'\tgoto_if_set FLAG_ABUNDANCE_THUNDURUS_DONE, {show}_No\n\tgoto_if_ge {S}, 4, {show}\n'
    if c == 'landorus':
        return (f'\tgoto_if_set FLAG_ABUNDANCE_LANDORUS_DONE, {show}_No\n\tgoto_if_unset FLAG_ABUNDANCE_TORNADUS_DONE, {show}_No\n'
                f'\tgoto_if_unset FLAG_ABUNDANCE_THUNDURUS_DONE, {show}_No\n\tgoto_if_ge {S}, 7, {show}\n')
    if c == 'reshiram':  return f'\tgoto_if_set FLAG_ABUNDANCE_RESHIRAM_DONE, {show}_No\n\tgoto_if_eq {S}, 12, {show}\n'
    if c == 'enamorus':  return f'\tgoto_if_set FLAG_ABUNDANCE_ENAMORUS_DONE, {show}_No\n\tgoto_if_ge {S}, 8, {show}\n'
    if c == 'dock':      return f'\tgoto_if_ge {S}, 10, {show}_No\n\tgoto_if_ge {S}, 7, {show}\n'
    if c == 'n_lab':     return f'\tgoto_if_ge {S}, 6, {show}_No\n\tgoto_if_ge {S}, 4, {show}\n'
    if c == 'day':       return f'\tgettime\n\tgoto_if_lt VAR_0x8000, 18, {show}\n'
    if c == 'dusk':      return f'\tgettime\n\tgoto_if_ge VAR_0x8000, 18, {show}\n'
    raise KeyError(c)

# fase 3: placas, itens escondidos, objetos e visibilidade calculados pelo fase3.place() (instalar/extras.json)
_ex = os.path.join(SC, 'instalar', 'extras.json')
if os.path.exists(_ex):
    _EX = json.load(open(_ex))
    for _d, _e in _EX['extras'].items():
        INFO[_d].setdefault('bg_events', []).extend(_e['bg'])
        EXTRA.setdefault(_d, []).extend(_e['objects'])
    for _d, _v in _EX['vis'].items():
        VIS.setdefault(_d, {}).update({k: tuple(v) for k, v in _v.items()})

import sys as _sys; _sys.path.insert(0, os.path.join(SC, 'instalar')); import plasma
TALL_TRAINER = {}   # local_id -> (sight) para a fase 2
_tp = os.path.join(SC, 'instalar', 'treinadores.json')
TREIN = json.load(open(_tp)) if os.path.exists(_tp) else {}
def norm_objects(d):
    i = INFO[d]; out = []; seen = set(); pre = 'LOCALID_' + short(d) + '_'
    objs = [o for o in i['objects'] if o['local_id'].replace(pre, '') not in DROP.get(d, set())] + EXTRA.get(d, [])
    vis = {suf: fl for fl, (_, sufs) in VIS.get(d, {}).items() for suf in sufs}
    for o in objs:
        o = dict(o)
        suf = re.sub(r'^LOCALID_[A-Z0-9_]*?(?=[A-Z][A-Z0-9]*(?:_[A-Z0-9]+)*$)', '', o['local_id']) if False else o['local_id']
        for p in ('LOCALID_' + i['map'] + '_', pre):
            if suf.startswith(p): suf = suf[len(p):]
        if 'LOCALID_' in suf:                       # prefixo repetido vindo do prototipo
            suf = suf.split('LOCALID_')[-1]
            toks = short(d).split('_')
            for k in range(len(toks)):
                p = '_'.join(toks[k:]) + '_'
                if suf.startswith(p): suf = suf[len(p):]; break
        o['local_id'] = pre + suf
        assert o['local_id'] not in seen, o['local_id']; seen.add(o['local_id'])
        o['flag'] = vis.get(suf, o['flag'] if o.get('keep_flag') else '0')   # extras (fase3) trazem a propria flag
        if o['graphics_id'] == 'OBJ_EVENT_GFX_ITEM_BALL':
            it = item_of(o['script'])
            o['trainer_sight_or_berry_tree_id'] = it
            o['flag'] = 'FLAG_ITEM_' + short(d) + '_' + it[5:]
            o['script'] = 'Common_EventScript_FindItem'
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            TALL_TRAINER[o['local_id']] = (d, o['trainer_sight_or_berry_tree_id'])
            if o['local_id'] in TREIN:
                o['trainer_type'] = 'TRAINER_TYPE_NORMAL'; o['trainer_sight_or_berry_tree_id'] = str(TREIN[o['local_id']]['sight'])
            else:
                o['trainer_type'] = 'TRAINER_TYPE_NONE'; o['trainer_sight_or_berry_tree_id'] = '0'
        if o['graphics_id'] == 'OBJ_EVENT_GFX_CUT_TREE': o['graphics_id'] = 'OBJ_EVENT_GFX_CUTTABLE_TREE'
        o['graphics_id'] = plasma.object_gfx(o['local_id'], o['graphics_id'])
        if o['script'] == 'Common_EventScript_Nurse': o['script'] = MAPS[d][0] + '_EventScript_Nurse'
        if '_EventScript_' in o['script'] and not o['script'].startswith(('Common_', 'EventScript_')):
            o['script'] = MAPS[d][0] + '_EventScript_' + o['script'].split('_EventScript_', 1)[1]
        if o['script'] in ('NULL', '0x0', ''):
            o['script'] = '0x0'
        o.setdefault('elevation', 3)
        out.append({k: o[k] for k in ('local_id', 'graphics_id', 'x', 'y', 'elevation', 'movement_type', 'movement_range_x',
                                      'movement_range_y', 'trainer_type', 'trainer_sight_or_berry_tree_id', 'script', 'flag')})
    return out

# --------------------------------------------------------------------------- comportamento das pecas (warp so dispara em peca de warp)
import struct, collections
MB = {}
_val = 0
for ln in open('include/constants/metatile_behaviors.h').read().split('\n'):
    m = re.match(r'\s*(MB_\w+)\s*(?:=\s*(0x[0-9A-Fa-f]+|\d+))?\s*,', ln)
    if m:
        if m.group(2): _val = int(m.group(2), 0)
        MB[m.group(1)] = _val; _val += 1
WARP_BEH = {v for k, v in MB.items() if any(t in k for t in ('DOOR', 'LADDER', 'ESCALATOR', 'ARROW_WARP', 'LAVARIDGE', 'AQUA_HIDEOUT_WARP', 'MT_PYRE_HOLE', 'MOSSDEEP_GYM_WARP', 'UNION_ROOM_WARP', 'DEEP_SOUTH_WARP', 'STAIRS', 'CAVE_DOOR', 'HOLE'))}
_ATTR = {}
def attrs_of(sym):
    if sym not in _ATTR:
        import importlib.util, sys as _s
        _s.path.insert(0, os.path.join(R, '.claude/skills/montar-tileset'))
        from tileset_kit import tileset_dir
        kind, nm = tileset_dir(sym)
        p = os.path.join(R, 'data/tilesets', kind, nm, 'metatile_attributes.bin')
        raw = open(p, 'rb').read(); _ATTR[sym] = [struct.unpack_from('<H', raw, j * 2)[0] for j in range(len(raw) // 2)]
    return _ATTR[sym]
def behavior_at(d, i, x, y):
    b = open(f'{M20}/{d}/map.bin', 'rb').read(); v = struct.unpack_from('<H', b, (y * i['w'] + x) * 2)[0] & 0x7ff
    sec = SECONDARY_SWAP.get(i['secondary'], i['secondary'])
    a = attrs_of(i['primary']) if v < 1024 else attrs_of(sec); k = v if v < 1024 else v - 1024
    return (a[k] & 0xff) if k < len(a) else -1
WARP_TRIGGERS = collections.defaultdict(list)
# --------------------------------------------------------------------------- escrita
layouts = json.load(open('data/layouts/layouts.json'))
lay_by = {l['id']: l for l in layouts['layouts'] if 'id' in l}
groups = json.load(open('data/maps/map_groups.json'))
item_flags = []
scripts_needed = {}
for d in ORDER:
    name, mapsec, music = MAPS[d]; i = INFO[d]; mid = mapid(name); lid = 'LAYOUT_' + mid[4:]
    os.makedirs(f'data/layouts/{name}', exist_ok=True); os.makedirs(f'data/maps/{name}', exist_ok=True)
    shutil.copy(f'{M20}/{d}/map.bin', f'data/layouts/{name}/map.bin')
    shutil.copy(f'{M20}/{d}/border.bin', f'data/layouts/{name}/border.bin')
    sec = SECONDARY_SWAP.get(i['secondary'], i['secondary'])
    L = dict(id=lid, name=name + '_Layout', width=i['w'], height=i['h'], primary_tileset=i['primary'], secondary_tileset=sec,
             border_filepath=f'data/layouts/{name}/border.bin', blockdata_filepath=f'data/layouts/{name}/map.bin')
    if lid in lay_by: lay_by[lid].clear(); lay_by[lid].update(L)
    else: layouts['layouts'].append(L); lay_by[lid] = L
    objs = norm_objects(d)
    for o in objs:
        if o['flag'].startswith('FLAG_ITEM_'): item_flags.append((o['flag'], o['trainer_sight_or_berry_tree_id'], name))
    warps = [dict(x=w['x'], y=w['y'], elevation=0, dest_map=OLD2NEW.get(w['dest_map'], w['dest_map']), dest_warp_id=str(w['dest_warp_id']))
             for w in i['warps']]
    for w in warps: assert w['dest_map'] in OLD2NEW.values(), (d, w)
    coords = []
    for k, w in enumerate(warps):
        beh = behavior_at(d, i, w['x'], w['y'])
        nota = (i['warps'][k].get('nota') or '').lower()
        if beh not in WARP_BEH and not any(t in nota for t in ('pouso', 'chegada', 'landing', 'so chegada')):
            coords.append(dict(type='trigger', x=w['x'], y=w['y'], elevation=0, var='VAR_TEMP_0', var_value='0',
                               script=f'{name}_EventScript_WarpTrigger{k}'))
            queda = any(t in nota for t in ('queda', 'buraco secreto', 'sumidouro'))   # cai com animacao (DoFallWarp)
            WARP_TRIGGERS[name].append((k, w['dest_map'], w['dest_warp_id'], queda))
    DIRMAP = {'west': 'left', 'east': 'right', 'north': 'up', 'south': 'down', 'dive': 'dive', 'emerge': 'emerge'}
    conns = [dict(map=OLD2NEW[c['map']], offset=c.get('offset', 0), direction=DIRMAP.get(c['direction'], c['direction']))
             for c in i.get('connections', [])]
    bgs = []
    for b in i.get('bg_events', []):
        b = dict(b); b.setdefault('type', 'sign'); b.setdefault('elevation', 0)
        if b['type'] == 'hidden_item':
            fl = 'FLAG_HIDDEN_ITEM_' + short(d) + '_' + b['item'][5:]
            item_flags.append((fl, b['item'], name))
            bgs.append(dict(type='hidden_item', x=b['x'], y=b['y'], elevation=0, item=b['item'], flag=fl, quantity=1)); continue
        b.setdefault('player_facing_dir', 'BG_EVENT_PLAYER_FACING_ANY')
        if '_EventScript_' in b.get('script', '') and not b['script'].startswith(('Common_', 'EventScript_')):
            b['script'] = name + '_EventScript_' + b['script'].split('_EventScript_', 1)[1]
        bgs.append({k: b[k] for k in ('type', 'x', 'y', 'elevation', 'player_facing_dir', 'script')})
    mt = i.get('map_type', 'MAP_TYPE_INDOOR')
    mj = dict(id=mid, name=name, layout=lid, music=music, region_map_section=mapsec, requires_flash=False,
              weather='WEATHER_UNDERWATER_BUBBLES' if mt == 'MAP_TYPE_UNDERWATER' else 'WEATHER_NONE', map_type=mt, allow_cycling=mt in ('MAP_TYPE_ROUTE', 'MAP_TYPE_TOWN'),
              allow_escaping=mt == 'MAP_TYPE_UNDERGROUND', allow_running=True, show_map_name=mt != 'MAP_TYPE_INDOOR',
              battle_scene='MAP_BATTLE_SCENE_NORMAL', connections=conns or None, object_events=objs, warp_events=warps,
              coord_events=coords, bg_events=bgs)
    json.dump(mj, open(f'data/maps/{name}/map.json', 'w'), indent=2); open(f'data/maps/{name}/map.json', 'a').write('\n')
    scripts_needed[name] = (d, objs, bgs)
json.dump(layouts, open('data/layouts/layouts.json', 'w'), indent=2); open('data/layouts/layouts.json', 'a').write('\n')
names = [MAPS[d][0] for d in ORDER]
groups[GROUP] = names
if GROUP not in groups['group_order']: groups['group_order'].append(GROUP)
json.dump(groups, open('data/maps/map_groups.json', 'w'), indent=2); open('data/maps/map_groups.json', 'a').write('\n')
json.dump(dict(item_flags=item_flags, trainers=TALL_TRAINER, old2new=OLD2NEW, names=names), open(SC + '/instalar/state.json', 'w'), indent=1)

# --------------------------------------------------------------------------- MAPSECs
sj = json.load(open('src/data/region_map/region_map_sections.json'))
ids = [s['id'] for s in sj['map_sections']]
for k, n in MAPSECS:
    if k not in ids:
        pos = ids.index('MAPSEC_NONE') if 'MAPSEC_NONE' in ids else len(ids)
        sj['map_sections'].insert(pos, dict(id=k, name=n, x=0, y=0, width=1, height=1)); ids.insert(pos, k)
json.dump(sj, open('src/data/region_map/region_map_sections.json', 'w'), indent=2); open('src/data/region_map/region_map_sections.json', 'a').write('\n')

# --------------------------------------------------------------------------- flags e var
f = open('include/constants/flags.h').read()
nxt = int(re.search(r'// PROXIMA FLAG NOVA: 0x([0-9A-F]+)', f).group(1), 16)
lines = []
want = [('FLAG_ABUNDANCE_TORNADUS_DONE', 'o Tornadus da Gale Shore foi capturado ou vencido; setada no script dele (Abundance Isle)'),
        ('FLAG_ABUNDANCE_THUNDURUS_DONE', 'o Thundurus da Thunder Ridge foi capturado ou vencido; setada no script dele'),
        ('FLAG_ABUNDANCE_LANDORUS_DONE', 'o Landorus do santuario da Abundance Isle foi capturado ou vencido'),
        ('FLAG_ABUNDANCE_ENAMORUS_DONE', 'o Enamorus do Spring Grove foi capturado ou vencido'),
        ('FLAG_ABUNDANCE_ZEKROM_DONE', 'o Zekrom do Thunderspire Summit foi capturado ou vencido'),
        ('FLAG_ABUNDANCE_RESHIRAM_DONE', 'o Reshiram do Hall of Truth (Truthsand Ruins) foi capturado ou vencido')]
want += [(fl, '%s em %s (Abundance Isle); setada pelo finditem' % (it, mp)) for fl, it, mp in item_flags]
seen = set()
for nm, c in want:
    if nm in seen or re.search(r'#define %s\b' % nm, f): continue
    seen.add(nm)
    lines.append('#define %-43s 0x%X // %s' % (nm, nxt, c)); nxt += 1
if lines:
    last = lines[-1].split()[1]
    f = re.sub(r'#define CUSTOM_FLAGS_END\s+\w+\n// PROXIMA FLAG NOVA: 0x[0-9A-F]+',
               '\n'.join(lines) + '\n#define CUSTOM_FLAGS_END                            %s\n// PROXIMA FLAG NOVA: 0x%X' % (last, nxt), f)
    open('include/constants/flags.h', 'w').write(f)
print('flags novas', len(lines))
v = open('include/constants/vars.h').read()
if 'VAR_ABUNDANCE_ISLE_STATE' not in v:
    nv = int(re.search(r'// PROXIMA VAR NOVA: 0x([0-9A-F]+)', v).group(1), 16)
    v = v.replace('// PROXIMA VAR NOVA: 0x%X' % nv,
                  '#define VAR_ABUNDANCE_ISLE_STATE                 0x%X // historia da Abundance Isle: 0 nao chegou, 1 inverno, 2 entrou na cratera, 3 venceu o Ghetsis no lab, 4 maquina desligada, 5 viu os planos no Frigate, 6 venceu o Ghetsis no cume, 7 Zekrom resolvido e DNA Splicers, 8 Landorus e Reveal Glass, 9 Enamorus, 10 despedida\n// PROXIMA VAR NOVA: 0x%X' % (nv, nv + 1))
    open('include/constants/vars.h', 'w').write(v)

# --------------------------------------------------------------------------- includes
es = open('data/event_scripts.s').read()
add = ''.join(f'\t.include "data/maps/{n}/scripts.inc"\n' for n in names if f'data/maps/{n}/scripts.inc' not in es)
if add:
    es = es.replace('\t.include "data/maps/UlaulaIsle/scripts.inc"\n', '\t.include "data/maps/UlaulaIsle/scripts.inc"\n' + add)
    open('data/event_scripts.s', 'w').write(es)
json.dump({n: dict(d=v[0], objs=v[1], bgs=v[2], warp_triggers=WARP_TRIGGERS.get(n, [])) for n, v in scripts_needed.items()}, open(SC + '/instalar/scripts_needed.json', 'w'), indent=1)
json.dump({k: v for k, v in VIS.items()}, open(SC + '/instalar/vis.json', 'w'))
print('mapas', len(names), 'itens', len(item_flags), 'treinadores pendentes', len(TALL_TRAINER))
