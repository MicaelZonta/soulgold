"""Aloca IDs e gera os times dos treinadores da Abundance Isle (fase 2a).
- treinadores comuns: vem do state.json (objetos com trainer_type do prototipo);
- batalhas de historia: GHETSIS_1..3 e N_AND_HILDA (times escritos a mao abaixo).
Idempotente: se TRAINER_ABUNDANCE_* ja existe, reaproveita o mesmo ID e regrava o bloco do .party.
Saida: instalar/treinadores.json  {local_id: {const, sight, cls, map}}."""
import sys as _sys, os as _os; _sys.path.insert(0, _os.path.dirname(_os.path.abspath(__file__))); import plasma
import json, os, re, subprocess, random
R = '/home/ADMIN/decomps/soulgold_v1'
os.chdir(R)
SC = os.path.join(R, '.claude/abundance_isle')
st = json.load(open(SC + '/instalar/state.json'))
NEXUS_TALK = ('VOLKNER', 'ELESA', 'GARDENIA', 'JESSIE', 'JAMES')   # personagens: batalha propria na fase 2b

# ------------------------------------------------------------------ classe por objeto
CLASSES = {  # chave: (Class, Pic, Gender, Music, AI)
 'HIKER': ('Hiker', 'Hiker', 'Male', 'Dp Hiker', 'Basic Trainer'),
 'PICNICKER': ('Picnicker', 'Picnicker', 'Female', 'Hg Girl 1', 'Basic Trainer'),
 'FISHERMAN': ('Fisherman', 'Fisherman', 'Male', 'Hg Boy 2', 'Basic Trainer'),
 'SWIMMER_F': ('Swimmer F', 'Swimmer F', 'Female', 'Hg Girl 2', 'Basic Trainer'),
 'SWIMMER_M': ('Swimmer M', 'Swimmer M', 'Male', 'Hg Boy 2', 'Basic Trainer'),
 'CAMPER': ('Camper', 'Camper', 'Male', 'Hg Boy 1', 'Basic Trainer'),
 'LASS': ('Lass', 'Lass', 'Female', 'Hg Girl 1', 'Basic Trainer'),
 'BIRD': ('Bird Keeper', 'Bird Keeper', 'Male', 'Hg Boy 1', 'Smart Trainer'),
 'BLACK_BELT': ('Black Belt', 'Black Belt', 'Male', 'Hg Boy 2', 'Basic Trainer'),
 'BEAUTY': ('Beauty', 'Beauty', 'Female', 'Hg Girl 2', 'Basic Trainer'),
 'PLASMA': ('Scientist', 'Scientist', 'Male', 'Hg Suspicious 2', 'Basic Trainer'),   # placeholder do Team Plasma
 'RUIN': ('Ruin Maniac', 'Ruin Maniac', 'Male', 'Dp Hiker', 'Smart Trainer'),
}
def classify(lid, gfx):
    u = lid.upper()
    if 'RUIN_MANIAC' in u: return 'RUIN'
    if 'SWIMMER' in u: return 'SWIMMER_F' if int(re.findall(r'\d+', u)[-1]) % 2 == 0 else 'SWIMMER_M'
    for k, c in (('HIKER', 'HIKER'), ('PICNICKER', 'PICNICKER'), ('FISHERMAN', 'FISHERMAN'), ('BEAUTY', 'BEAUTY'),
                 ('BLACK_BELT', 'BLACK_BELT'), ('BIRDKEEPER', 'BIRD'), ('LASS', 'LASS'), ('BOARDER', 'CAMPER'),
                 ('FARMHAND', 'CAMPER'), ('CAMPER', 'CAMPER')):
        if k in u: return c
    return 'PLASMA'    # GRUNT, SCIENTIST, RESEARCHER, CHIEF, ASSIST, DIGGER, GUARD...
# ------------------------------------------------------------------ area -> nivel e tema
def area(mapdir):
    m = mapdir.upper()
    if 'RUINS' in m or 'EMBERDUNE' in m or 'SUNSET' in m: return 'ruins', 78
    if 'THUNDER' in m: return 'storm', 75
    if 'FRIGATE' in m: return 'frigate', 74
    if 'CRATER' in m: return 'ice', 72
    return 'isle', 70
POOLS = {
 ('PLASMA', 'ice'): ['Beartic', 'Cryogonal', 'Vanilluxe', 'Weavile', 'Liepard', 'Garbodor', 'Mamoswine'],
 ('PLASMA', 'frigate'): ['Seismitoad', 'Krookodile', 'Scrafty', 'Liepard', 'Garbodor', 'Klinklang', 'Eelektross', 'Crobat'],
 ('PLASMA', 'storm'): ['Eelektross', 'Zebstrika', 'Galvantula', 'Scrafty', 'Krookodile', 'Magnezone'],
 ('PLASMA', 'ruins'): ['Krookodile', 'Cofagrigus', 'Sigilyph', 'Scrafty', 'Garbodor', 'Darmanitan'],
 ('PLASMA', 'isle'): ['Watchog', 'Liepard', 'Scrafty', 'Garbodor', 'Krookodile'],
 ('HIKER', '*'): ['Gigalith', 'Excadrill', 'Golem', 'Steelix', 'Conkeldurr', 'Rhyperior'],
 ('PICNICKER', '*'): ['Lilligant', 'Whimsicott', 'Sawsbuck', 'Audino', 'Maractus', 'Leavanny'],
 ('FISHERMAN', '*'): ['Gyarados', 'Seaking', 'Whiscash', 'Lanturn', 'Basculin', 'Kingdra'],
 ('SWIMMER_F', '*'): ['Jellicent', 'Alomomola', 'Swanna', 'Milotic', 'Lapras'],
 ('SWIMMER_M', '*'): ['Carracosta', 'Basculin', 'Seismitoad', 'Starmie', 'Tentacruel'],
 ('CAMPER', '*'): ['Stoutland', 'Simisage', 'Simisear', 'Simipour', 'Sawsbuck', 'Tauros'],
 ('LASS', '*'): ['Cinccino', 'Whimsicott', 'Gothitelle', 'Lilligant', 'Audino'],
 ('BIRD', '*'): ['Unfezant', 'Braviary', 'Swoobat', 'Sigilyph', 'Swanna'],
 ('BLACK_BELT', '*'): ['Throh', 'Sawk', 'Conkeldurr', 'Mienshao', 'Scrafty'],
 ('BEAUTY', '*'): ['Swanna', 'Cinccino', 'Gothitelle', 'Lilligant', 'Milotic'],
 ('RUIN', '*'): ['Golurk', 'Cofagrigus', 'Sigilyph', 'Krookodile', 'Claydol'],
}
NAMES = {'HIKER': ['Brom', 'Gus', 'Hollis', 'Dexter', 'Ike', 'Ruben'], 'PICNICKER': ['Daisy', 'Clover', 'Wren'],
         'FISHERMAN': ['Amos', 'Cyrus', 'Elton', 'Finn'], 'SWIMMER_F': ['Coral', 'Marina'], 'SWIMMER_M': ['Brody', 'Kai'],
         'CAMPER': ['Otis', 'Rudy', 'Tobias'], 'LASS': ['Poppy', 'Tessa'], 'BIRD': ['Gale'], 'BLACK_BELT': ['Koji'],
         'BEAUTY': ['Celeste'], 'PLASMA': ['Grunt'], 'RUIN': ['Hector', 'Ozzy', 'Pierce']}

def pool(cls, ar):
    return POOLS.get((cls, ar)) or POOLS.get((cls, '*')) or POOLS[('PLASMA', 'isle')]

# ------------------------------------------------------------------ IDs livres (mesma logica do ids_livres.py)
op = open('include/constants/opponents.h').read()
out = subprocess.run(['python3', '.claude/skills/adicionar-batalha-npc/ids_livres.py'], capture_output=True, text=True).stdout
ranges = [(int(a), int(b)) for a, b in re.findall(r'^\s+(\d+)-(\d+)\s+\(', out, re.M)]
free = [i for a, b in ranges for i in range(a, b + 1)]
by_id = {int(n): name for name, n in re.findall(r'#define\s+(TRAINER_\w+)\s+(\d+)\b', op)}
existing = {name: int(n) for name, n in re.findall(r'#define\s+(TRAINER_ABUNDANCE_\w+)\s+(\d+)\b', op)}

def alloc(const):
    global op
    if const in existing: return existing[const]
    i = free.pop(0)
    old = by_id[i]
    op = re.sub(r'#define\s+%s\s+%d\b' % (old, i), '#define %s %d' % (const, i), op, count=1)
    existing[const] = i
    return i

party = open('src/data/trainers.party').read()
def put_block(const, body):
    global party
    blk = '=== %s ===\n%s\n' % (const, body.strip('\n') + '\n')
    m = re.search(r'=== %s ===\n.*?(?=\n=== |\Z)' % const, party, re.S)
    if m: party = party[:m.start()] + blk.rstrip('\n') + party[m.end():]
    else: party = party.rstrip('\n') + '\n\n' + blk

res = {}
rng = random.Random(30102026)
cnt = {}
for lid, (mapdir, sight) in sorted(st['trainers'].items()):
    suf = lid.split('_')[-1]
    if any(n in lid for n in NEXUS_TALK): continue
    cls = classify(lid, '')
    ar, lv = area(mapdir)
    short = re.sub(r'^LOCALID_', '', lid)
    short = re.sub(r'LOCALID_[A-Z0-9]+?_(?=SWIMMER)', '', short).replace('SUNSET_STRAIT_SUNSET_STRAIT_', 'SUNSET_STRAIT_')
    const = 'TRAINER_ABUNDANCE_' + re.sub(r'^(ABUNDANCE_ISLE_|LOCALID_)', '', short)
    const = re.sub(r'_+', '_', const)
    alloc(const)
    C = CLASSES[cls]
    if cls == 'PLASMA':
        _c, _p, _g = plasma.trainer_look(lid)
        C = (_c, _p, _g) + C[3:]
    nm = NAMES[cls][cnt.get(cls, 0) % len(NAMES[cls])]; cnt[cls] = cnt.get(cls, 0) + 1
    n = 2 + rng.randrange(3) if cls != 'PLASMA' else 2 + rng.randrange(2)
    mons = rng.sample(pool(cls, ar), min(n, len(pool(cls, ar))))
    body = 'Name: %s\nClass: %s\nPic: %s\nGender: %s\nMusic: %s\nDouble Battle: No\nAI: %s\n' % (nm, C[0], C[1], C[2], C[3], C[4])
    for k, sp in enumerate(mons):
        body += '\n%s\nLevel: %d\nIVs: 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe\n' % (sp, lv + k)
    put_block(const, body)
    res[lid] = dict(const=const, sight=sight if sight not in ('0', 0) else '3', cls=cls, map=mapdir)

# ------------------------------------------------------------------ batalhas de historia
STORY = {
 'TRAINER_ABUNDANCE_GHETSIS_1': ('Ghetsis', 'Team Plasma', 'Ghetsis', 'Male', 'Hg Sage', 'No', 76,
                                 ['Cofagrigus', 'Seismitoad', 'Bouffalant', 'Bisharp', 'Eelektross', 'Hydreigon']),
 'TRAINER_ABUNDANCE_GHETSIS_2': ('Ghetsis', 'Team Plasma', 'Ghetsis', 'Male', 'Hg Sage', 'No', 80,
                                 ['Cofagrigus', 'Seismitoad', 'Bouffalant', 'Bisharp', 'Eelektross', 'Hydreigon']),
 'TRAINER_ABUNDANCE_GHETSIS_3': ('Ghetsis', 'Team Plasma', 'Ghetsis', 'Male', 'Hg Sage', 'No', 84,
                                 ['Cofagrigus', 'Seismitoad', 'Bouffalant', 'Bisharp', 'Eelektross', 'Hydreigon']),
 'TRAINER_ABUNDANCE_CRATER_GUARD': ('Grunt', 'Team Plasma', 'Plasma Grunt M', 'Male', 'Hg Suspicious 2', 'No', 70,
                                    ['Liepard', 'Garbodor', 'Scrafty']),
 # ---- missoes (fase 3); pic de placeholder quando o personagem nao tem sprite de batalha
 'TRAINER_ABUNDANCE_LENORA': ('Lenora', 'Pkmn Trainer 1', 'Lenora', 'Female', 'Female', 'No', 78, ['Watchog', 'Stoutland', 'Cinccino', 'Bouffalant', 'Braviary', 'Audino']),
 'TRAINER_ABUNDANCE_CYNTHIA': ('Cynthia', 'Pkmn Trainer 1', 'Cynthia', 'Female', 'Female', 'No', 82, ['Spiritomb', 'Milotic', 'Lucario', 'Roserade', 'Togekiss', 'Garchomp']),
 'TRAINER_ABUNDANCE_JESSIE_JAMES': ('Jess&James', 'Team Rocket', 'Jessie James', 'Female', 'Rocket', 'Yes', 74, ['Arbok', 'Weezing', 'Seviper', 'Cacnea', 'Wobbuffet', 'Meowth']),
 'TRAINER_ABUNDANCE_VOLKNER': ('Volkner', 'Leader', 'Volkner', 'Male', 'Cool', 'No', 78, ['Jolteon', 'Raichu', 'Luxray', 'Electivire', 'Rotom', 'Magnezone']),
 'TRAINER_ABUNDANCE_ELESA': ('Elesa', 'Leader', 'Elesa', 'Female', 'Female', 'No', 78, ['Emolga', 'Zebstrika', 'Eelektross', 'Ampharos', 'Rotom', 'Galvantula']),
 'TRAINER_ABUNDANCE_WINONA': ('Winona', 'Leader', 'Leader Winona', 'Female', 'Female', 'No', 76, ['Swellow', 'Pelipper', 'Tropius', 'Skarmory', 'Altaria', 'Braviary']),
 'TRAINER_ABUNDANCE_BYRON': ('Byron', 'Leader', 'Byron', 'Male', 'Hiker', 'No', 76, ['Bronzong', 'Steelix', 'Bastiodon', 'Probopass', 'Excadrill', 'Aggron']),
 'TRAINER_ABUNDANCE_ZINNIA': ('Zinnia', 'Pkmn Trainer 1', 'Zinnia', 'Female', 'Female', 'No', 82, ['Whismur', 'Tyrantrum', 'Altaria', 'Goodra', 'Noivern', 'Salamence']),
 'TRAINER_ABUNDANCE_GARDENIA': ('Gardenia', 'Leader', 'Gardenia', 'Female', 'Female', 'No', 76, ['Cherrim', 'Roserade', 'Tangrowth', 'Leafeon', 'Whimsicott', 'Torterra']),
 'TRAINER_ABUNDANCE_NEMONA': ('Nemona', 'Pkmn Trainer 1', 'Nemona', 'Female', 'Female', 'No', 78, ['Lycanroc', 'Goodra', 'Orthworm', 'Dudunsparce', 'Pawmot', 'Meowscarada']),
 'TRAINER_ABUNDANCE_BARRY': ('Barry', 'Pkmn Trainer 1', 'Barry', 'Male', 'Male', 'No', 78, ['Staraptor', 'Heracross', 'Roserade', 'Floatzel', 'Snorlax', 'Empoleon']),
 'TRAINER_ABUNDANCE_LUCY': ('Lucy', 'Pike Queen', 'Pike Queen Lucy', 'Female', 'Female', 'No', 80, ['Seviper', 'Milotic', 'Shuckle', 'Gengar', 'Arbok', 'Drapion']),
 'TRAINER_ABUNDANCE_SPENSER': ('Spenser', 'Palace Maven', 'Palace Maven Spenser', 'Male', 'Male', 'No', 80, ['Crobat', 'Slaking', 'Lapras', 'Arcanine', 'Gardevoir', 'Shiftry']),
 'TRAINER_ABUNDANCE_TATE_LIZA': ('Tate&Liza', 'Leader', 'Leader Tate And Liza', 'Male', 'Intense', 'Yes', 80, ['Solrock', 'Lunatone', 'Claydol', 'Xatu', 'Metagross', 'Gardevoir']),
 'TRAINER_ABUNDANCE_GRETA': ('Greta', 'Arena Tycoon', 'Arena Tycoon Greta', 'Female', 'Female', 'No', 80, ['Heracross', 'Umbreon', 'Gengar', 'Breloom', 'Shedinja', 'Medicham']),
 'TRAINER_ABUNDANCE_NOLAND': ('Noland', 'Factory Head', 'Factory Head Noland', 'Male', 'Male', 'No', 76, ['Golduck', 'Gyarados', 'Starmie', 'Swanna', 'Pelipper', 'Kingdra']),
 'TRAINER_ABUNDANCE_ARENA_LEON': ('Leon', 'Champion', 'Leon', 'Male', 'Hg Champion', 'No', 84, ['Aegislash', 'Dragapult', 'Haxorus', 'Rhyperior', 'Seismitoad', 'Charizard']),
 'TRAINER_ABUNDANCE_ARENA_CYNTHIA': ('Cynthia', 'Pkmn Trainer 1', 'Cynthia', 'Female', 'Female', 'No', 84, ['Spiritomb', 'Milotic', 'Lucario', 'Roserade', 'Togekiss', 'Garchomp']),
 'TRAINER_ABUNDANCE_ARENA_DIANTHA': ('Diantha', 'Pkmn Trainer 1', 'Diantha', 'Female', 'Female', 'No', 84, ['Hawlucha', 'Tyrantrum', 'Aurorus', 'Gourgeist', 'Goodra', 'Gardevoir']),
 'TRAINER_ABUNDANCE_ARENA_VOLKNER': ('Volkner', 'Leader', 'Volkner', 'Male', 'Cool', 'No', 84, ['Jolteon', 'Raichu', 'Luxray', 'Electivire', 'Rotom', 'Magnezone']),
 'TRAINER_ABUNDANCE_N_AND_HILDA': ('N & Hilda', 'Pkmn Trainer 1', 'N', 'Male', 'Hg Sage', 'Yes', 85,
                                   ['Zoroark', 'Carracosta', 'Klinklang', 'Serperior', 'Emboar', 'Samurott']),
}
for const, (nm, cl, pic, g, mus, dbl, lv, mons) in STORY.items():
    alloc(const)
    body = 'Name: %s\nClass: %s\nPic: %s\nGender: %s\nMusic: %s\nDouble Battle: %s\nAI: Smart Trainer\n' % (nm, cl, pic, g, mus, dbl)
    for k, sp in enumerate(mons):
        body += '\n%s\nLevel: %d\nIVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe\n' % (sp, lv + (k // 2))
    put_block(const, body)
open('include/constants/opponents.h', 'w').write(op)
party = re.sub(r'([^\n])\n(=== TRAINER_)', r'\1\n\n\2', party)
open('src/data/trainers.party', 'w').write(party.rstrip('\n') + '\n')
json.dump(res, open(SC + '/instalar/treinadores.json', 'w'), indent=1)
print('treinadores comuns', len(res), 'de historia', len(STORY), 'IDs livres restantes', len(free))
