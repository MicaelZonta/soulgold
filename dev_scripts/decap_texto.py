#!/usr/bin/env python3
"""Tira a CAIXA ALTA estilo GSC/Gen-3 do texto de mapa.

O texto importado do pokehns escreve nome proprio, especie, item, golpe e
lugar em CAIXA ALTA ("There's a rare POKeMON on this route.", "LEADER: BROCK").
O SoulGold e decapado: "Pokemon", "Leader: Brock", "Zephyrbadge".

Dois modos, decididos por BLOCO de texto (rotulo + .string ate o `$`):

  bloco MISTO  (tem minuscula)  -> so troca o que da match no dicionario de
                                   nomes do repositorio (especie/golpe/item/
                                   habilidade/MAPSEC/falante) ou na tabela
                                   PALAVRAS. Palavra em caixa alta que sobra e
                                   ENFASE do autor ("I STILL only sell...") e
                                   fica como esta - o relatorio lista todas.
  bloco TODO EM CAIXA ALTA      -> placa/diretorio/lista: vira Title Case, com
                                   as palavras pequenas (of, to, and...) em
                                   minuscula e as da tabela MANTER intactas.
                                   Rotulo em FRASES vira sentenca normal.

Rotulos em PULAR ficam intocados (voz de maquina, que no SoulGold tambem e
escrita em caixa alta - ver AbandonedRocketHideout).

Uso:
    python3 dev_scripts/decap_texto.py --resumo   <arquivo> [...]
    python3 dev_scripts/decap_texto.py --conferir <arquivo> [...]
    python3 dev_scripts/decap_texto.py --aplicar  <arquivo> [...]
    python3 dev_scripts/decap_texto.py --blocos-caixa-alta <arquivo> [...]

Edite SEMPRE o .pory quando ele existir; o .inc e gerado.
"""
import argparse
import collections
import glob
import json
import os
import re
import sys

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# ---------------------------------------------------------------- dicionario
def nomes_do_repo():
    """Nome canonico de especie/golpe/item/habilidade/MAPSEC/falante."""
    nomes = set()
    def add(s):
        s = s.strip()
        if s and '{' not in s and not s.startswith('?'):
            nomes.add(s)

    for f in glob.glob(os.path.join(RAIZ, 'src/data/pokemon/species_info/*.h')):
        txt = open(f, encoding='utf-8').read()
        for m in re.finditer(r'\.speciesName\s*=\s*_\("([^"]+)"\)', txt):
            add(m.group(1))
    for arq, pat in (
        ('src/data/moves_info.h', r'\.name\s*=\s*(?:COMPOUND_STRING|_)\("([^"]+)"'),
        ('src/data/items.h', r'\.name\s*=\s*(?:ITEM_NAME|COMPOUND_STRING|_)\("([^"]+)"'),
        ('src/data/abilities.h',
         r'\.name\s*=\s*(?:COMPOUND_STRING|HANDLE_EXPANDED_ABILITY_NAME|_)\("([^"]+)"'),
        ('src/data/speaker_names.h', r'COMPOUND_STRING\("([^"]+)"\)'),
    ):
        txt = open(os.path.join(RAIZ, arq), encoding='utf-8').read()
        for m in re.finditer(pat, txt):
            add(m.group(1))
    j = json.load(open(os.path.join(RAIZ, 'src/data/region_map/region_map_sections.json'),
                       encoding='utf-8'))
    for e in j.get('map_sections', []):
        if e.get('name'):
            add(e['name'])
    return nomes

# Frases que o repositorio nao tem numa tabela de nomes (lugar, instituicao,
# titulo). Chave = a frase em caixa alta sem pontuacao; valor = como se escreve.
FRASES_MANUAIS = """
Pokemon Center | Pokemon Centers | Pokemon Gym | Pokemon Gyms | Pokemon League
Pokemon Fan Club | Pokemon Contest Hall | Pokemon Academy | Pokemon Trainer
Gym Leader | Gym Leaders | Gym Badge | Gym Badges | Gym Trainers | Elite Four
League Champ | League Champion | Safari Zone | Safari Level | Magnet Train
Magnet Train Station | Radio Tower | Radio Station | Kanto Radio Station
Game Corner | Game Freak | Development Room | Development Office | Dept.Store
Silph Co. | Devon Corp. | Fighting Dojo | Victory Road | Rock Tunnel
Diglett's Cave | Underground Path | Cycling Road | Sea Cottage | Soul House
Cerulean Cape | Indigo Plateau | Reception Gate | Mt.Moon Square | Mt Moon Square
Hot Springs | Hot Springs Cave | Sinjoh Ruins | New Sinjoh | Research Lab
Trainer Tips | Trainer House | Trainer's Market | Service Counter | Drug Store
Wiseman Gifts | Rooftop Square | Director's Office | Office Building
Fishing Spot | Wild Hibernation Den | Vermilion Port | Silence Bridge
Tohjo Falls | Lake of Rage | Family Cafe | Celadon Mansion | Manager's Suite
Bill's House | Blue's House | Red's House | Oak's Lab | Pokemon Lab
Poke Doll | Poke Ball | Poke Flute | S.S.Ticket | S.S. Ticket | Expn Card
Day of Week Siblings | Pewter Museum | Power Plant | Seafoam Islands
Mr.Psychic's | Mr. Psychic | Lt. Surge | Lt.Surge | Warden Baoba
Melemele Isle | Akala Isle | Ula'ula Isle | Poni Isle | Alola Isles | Akala Villa
Melemele Isle Mart | Mt. Lanikala | Heart & Soul | Rocket Hideout
Pokemon Federa- | Wild Charge | Victory Dance | Ultra Eclipse | Pokemon Talk
Head Office | Heart Scales | Lovely Mail | Sword and Shield | The Eggening
Guard Spec. | open source | Mt. Lanikala | Day of Week Siblings | Poke Doll
Safari Level | Gift Shop | Police Station | Bug Catching Contest
"""

# Palavra isolada. Valor = como se escreve. So o que NAO sai do dicionario.
PALAVRAS = {
    # ficam em caixa alta
    'TM': 'TM', 'TMS': 'TMs', 'HM': 'HM', 'HMS': 'HMs', 'PC': 'PC',
    'PP': 'PP', 'TV': 'TV', 'HQ': 'HQ', 'DJ': 'DJ', 'OK': 'OK', 'DNA': 'DNA',
    'NES': 'NES', 'EXPN': 'EXPN', 'PM': 'PM', 'AM': 'AM', 'BP': 'BP',
    'SP.DEF.': 'Sp.Def.', 'SP.ATK.': 'Sp.Atk.',
    # lugar, instituicao, coisa que faz parte de nome proprio
    'GYM': 'Gym', 'GYMS': 'Gyms', 'LEADER': 'Leader', 'LEADERS': 'Leaders',
    'BADGE': 'Badge', 'BADGES': 'Badges', 'TRAINER': 'Trainer',
    'TRAINERS': 'Trainers', "TRAINER'S": "Trainer's",
    'CITY': 'City', 'TOWN': 'Town', 'ISLAND': 'Island', 'ISLANDS': 'Islands',
    'ISLE': 'Isle', 'ISLES': 'Isles', 'CAVE': 'Cave', 'ROUTE': 'Route',
    'ROAD': 'Road', 'TOWER': 'Tower', 'PATH': 'Path', 'TUNNEL': 'Tunnel',
    'PLATEAU': 'Plateau', 'MOUNTAIN': 'Mountain', 'FALLS': 'Falls',
    'LAKE': 'Lake', 'BRIDGE': 'Bridge', 'PORT': 'Port', 'GATE': 'Gate',
    'STATION': 'Station', 'CENTER': 'Center', 'CENTERS': 'Centers',
    'MART': 'Mart', 'HOUSE': 'House', 'LAB': 'Lab', 'MUSEUM': 'Museum',
    'MANSION': 'Mansion', 'SHOP': 'Shop', 'STORE': 'Store', 'CLUB': 'Club',
    'HALL': 'Hall', 'DEN': 'Den', 'CAPE': 'Cape', 'SQUARE': 'Square',
    'ZONE': 'Zone', 'ROOM': 'Room', 'OFFICE': 'Office',
    'BUILDING': 'Building', 'ENTRANCE': 'Entrance', 'LEAGUE': 'League',
    'CHAMPION': 'Champion', 'CHAMP': 'Champ', 'REGION': 'region',
    'RUINS': 'Ruins', 'VILLA': 'Villa', 'SHELTER': 'Shelter',
    'SPRINGS': 'Springs', 'COTTAGE': 'Cottage', 'PLANT': 'Plant',
    'DOJO': 'Dojo', 'CORNER': 'Corner', 'MARKET': 'Market',
    'COUNTER': 'Counter', 'RECEPTION': 'Reception', 'SALES': 'Sales',
    'PERSONNEL': 'Personnel', 'PRODUCTION': 'Production',
    'PRODUCER': 'Producer', 'DIRECTOR': 'Director',
    "DIRECTOR'S": "Director's", 'MANAGER': 'Manager',
    "MANAGER'S": "Manager's", 'CHAIRMAN': 'Chairman', 'WARDEN': 'Warden',
    'KEEPERS': 'Keepers', 'GUARD': 'Guard', 'CAPTAIN': 'Captain',
    'DESIGNER': 'Designer', 'PROGRAMMER': 'Programmer', 'ARTIST': 'Artist',
    'CHEF': 'Chef', 'HIKER': 'Hiker', 'GURU': 'Guru', 'WISEMAN': 'Wiseman',
    'LINGUIST': 'Linguist', 'SCIENCE': 'Science', 'RESEARCH': 'Research',
    'DEVELOPMENT': 'Development', 'GRAPHIC': 'Graphic', 'MUSIC': 'Music',
    'ENGLISH': 'English', 'POLICE': 'Police', 'SERVICE': 'Service',
    'ELEVATOR': 'Elevator', 'VENDING': 'Vending', 'SOUVENIR': 'Souvenir',
    'ROOFTOP': 'Rooftop', 'DEPT': 'Dept', 'DEPT.STORE': 'Dept.Store',
    'DEPT.STORE!': 'Dept.Store!', 'CO.': 'Co.', 'CORP.': 'Corp.',
    'BROS.': 'Bros.', 'BROS': 'Bros', 'MT': 'Mt', 'MT.': 'Mt.',
    'MR': 'Mr', 'MR.': 'Mr.', 'LT': 'Lt', 'LT.': 'Lt.', 'PROF': 'Prof',
    'PROF.': 'Prof.', 'PROFESSOR': 'Professor', 'SAFARI': 'Safari',
    'CONTEST': 'Contest', 'FAN': 'Fan', 'FAMILY': 'Family', 'CAFE': 'Cafe',
    'SOUL': 'Soul', 'HEART': 'Heart', 'SPOT': 'Spot', 'FISHING': 'Fishing',
    'UNDERGROUND': 'Underground', 'CYCLING': 'Cycling', 'VICTORY': 'Victory',
    'INDIGO': 'Indigo', 'DIPLOMA': 'Diploma', 'ITEMFINDER': 'Itemfinder',
    'BICYCLE': 'Bicycle', 'BIKE': 'Bike', 'EGG': 'Egg', 'BERRY': 'Berry',
    'MAIL': 'Mail', 'CARD': 'Card', 'PASS': 'Pass', 'PASSES': 'Passes',
    'TICKET': 'Ticket', 'FLUTE': 'Flute', 'DOLL': 'Doll', 'BALL': 'Ball',
    'BALLS': 'Balls', 'ROD': 'Rod', 'RODS': 'Rods', 'STONE': 'Stone',
    'PLATE': 'Plate', 'PLATES': 'Plates', 'CANDY': 'Candy', 'REPEL': 'Repel',
    'UPGRADE': 'Upgrade', 'CANDYBAR': 'Candybar', 'GIFT': 'Gift',
    'GIFTS': 'Gifts', 'TEAM': 'Team', 'ROCKET': 'Rocket', 'KIMONO': 'Kimono',
    'GIRLS': 'Girls', 'TWINS': 'Twins', 'DUDE': 'Dude', 'KING': 'King',
    'NOBLE': 'Noble', 'LEGENDARY': 'Legendary', 'ELITE': 'Elite',
    'FOUR': 'Four', 'WINNING': 'Winning', 'BIRD': 'Bird', 'WILD': 'Wild',
    'SEA': 'Sea', 'NORTH': 'North', 'WEST': 'West', 'SOUTH': 'South',
    'EAST': 'East', 'DOWNHILL': 'Downhill', 'CHANNEL': 'Channel',
    'RADIO': 'Radio', 'MAP': 'Map', 'CASE': 'Case', 'PACK': 'Pack',
    'BAG': 'Bag', 'ELECTRIC': 'Electric', 'PSYCHIC': 'Psychic',
    "PSYCHIC'S": "Psychic's", 'FIRE': 'Fire', 'WATER': 'Water',
    'FLYING': 'Flying', 'BUG': 'Bug', 'POISON': 'Poison', 'ROCK': 'Rock',
    'STEEL': 'Steel', 'DRAGON': 'Dragon', 'KARATE': 'Karate',
    'FIGHTING': 'Fighting', 'FOREST': 'Forest', 'SKY': 'Sky',
    'LUNAR': 'Lunar', 'AURORA': 'Aurora', 'MYSTICAL': 'Mystical',
    'EXCELLENT': 'Excellent', 'DANGER': 'Danger', 'PART': 'Part',
    'ROUND': 'Round', 'LEVEL': 'Level', 'TYPE': 'Type', 'FORM': 'Form',
    'MILK': 'Milk', 'MOOMOO': 'Moomoo', 'DEMAKE': 'Demake',
    'DEMAKES': 'Demakes', 'PHANTONOMY': 'Phantonomy', 'FEDERATION': 'Federation',
    'FEDERA-': 'Federa-', 'TION': 'tion', 'SPEARY': 'Speary',
    'RATTEY': 'Rattey', 'DENNIS': 'Dennis', 'KA-BOOM': 'Ka-boom',
    'PI-PIKACHU': 'Pi-Pikachu', 'GRANPDA': 'Grandpa', 'COASING': 'Coasting',
    'POKEMON': 'Pokemon', 'POKé': 'Poke', 'POKéMON': 'Pokemon',
    'POKéDEX': 'Pokedex', 'POKéGEAR': 'Pokegear', 'POKéMART': 'Pokemart',
    'POKéCENTER': 'Pokecenter', 'SPEC.': 'Spec.',
    'OKAY': 'Okay', 'WELCOME': 'Welcome', 'SILENCE': 'Silence',
    'GATEWAY': 'Gateway', 'LINK': 'Link', 'VOICE': 'Voice', 'POWER': 'Power',
    'MIRROR': 'Mirror', 'WALL': 'Wall', 'LIFE': 'Life', 'VOLUNTEER': 'Volunteer',
    'TRAIN': 'Train', 'SHIP': 'Ship', 'PORYGON': 'Porygon',
    'CLICK': 'click', 'SILPH': 'Silph', 'DEVON': 'Devon', 'GAME': 'Game',
    'FREAK': 'Freak', 'OPEN': 'Open', 'AHEAD': 'Ahead', 'TIPS': 'Tips',
    'ULTIMATE': 'Ultimate', 'PLUS': 'Plus', 'SUPER': 'Super', 'FAST': 'Fast',
    # regioes, cidades, pessoas que o repositorio nao tem numa tabela
    'KANTO': 'Kanto', 'JOHTO': 'Johto', 'ALOLA': 'Alola', 'HOENN': 'Hoenn',
    'SINNOH': 'Sinnoh', 'UNOVA': 'Unova', 'SINJOH': 'Sinjoh', 'GALAR': 'Galar',
    'CINNABAR': 'Cinnabar', 'CELADON': 'Celadon', 'CERULEAN': 'Cerulean',
    'SAFFRON': 'Saffron', 'FUCHSIA': 'Fuchsia', 'VIRIDIAN': 'Viridian',
    'LAVENDER': 'Lavender', 'PEWTER': 'Pewter', 'PALLET': 'Pallet',
    'VERMILION': 'Vermilion', 'SEAFOAM': 'Seafoam', 'FORTREE': 'Fortree',
    'GOLDENROD': 'Goldenrod', 'ECRUTEAK': 'Ecruteak', 'AZALEA': 'Azalea',
    'VIOLET': 'Violet', 'OLIVINE': 'Olivine', 'CIANWOOD': 'Cianwood',
    'BLACKTHORN': 'Blackthorn', 'MAHOGANY': 'Mahogany', 'TOHJO': 'Tohjo',
    'MELEMELE': 'Melemele', 'AKALA': 'Akala', 'PONI': 'Poni',
    "ULA'ULA": "Ula'ula", "HAU'OLI": "Hau'oli", 'LANIKALA': 'Lanikala',
    'ALPH': 'Alph', 'AZURE': 'Azure', 'INDIGO': 'Indigo', 'SILVER': 'Silver',
    'MT.SILVER': 'Mt.Silver', 'MT.MOON': 'Mt.Moon', 'S.S.AQUA': 'S.S.Aqua',
    'S.S.TICKET': 'S.S.Ticket', 'PROF.OAK': 'Prof.Oak', 'MR.FUJI': 'Mr.Fuji',
    'MR.PSYCHIC': 'Mr.Psychic', 'DEPT.STORE': 'Dept.Store',
    'SAMSON': 'Samson', 'WOODY': 'Woody', 'TORY': 'Tory', 'MAGGIE': 'Maggie',
    'MIHARU': 'Miharu', 'SHIZUKO': 'Shizuko', 'YOUKO': 'Youko',
    'ELIO': 'Elio', 'FINLEY': 'Finley', 'LILY': 'Lily', 'MARY': 'Mary',
    'TUSCANY': 'Tuscany', 'FRIEDA': 'Frieda', 'WESLEY': 'Wesley',
    'SANTOS': 'Santos', 'ARTHUR': 'Arthur', 'MONICA': 'Monica',
    'BAOBA': 'Baoba', 'DAISY': 'Daisy', 'FUJI': 'Fuji', 'ECLIPSE': 'Eclipse',
    'ULTRA': 'Ultra', 'TALK': 'Talk', 'SCALES': 'Scales', 'HEAD': 'Head',
    'TELEPORTER': 'Teleporter', 'PHANTONOMY': 'Phantonomy',
    # badges, do jeito que o SoulGold escreve (Zephyrbadge)
    'BOULDERBADGE': 'Boulderbadge', 'CASCADEBADGE': 'Cascadebadge',
    'THUNDERBADGE': 'Thunderbadge', 'RAINBOWBADGE': 'Rainbowbadge',
    'SOULBADGE': 'Soulbadge', 'MARSHBADGE': 'Marshbadge',
    'VOLCANOBADGE': 'Volcanobadge', 'EARTHBADGE': 'Earthbadge',
    'ZEPHYRBADGE': 'Zephyrbadge', 'HIVEBADGE': 'Hivebadge',
    'PLAINBADGE': 'Plainbadge', 'FOGBADGE': 'Fogbadge',
    'STORMBADGE': 'Stormbadge', 'MINERALBADGE': 'Mineralbadge',
    'GLACIERBADGE': 'Glacierbadge', 'RISINGBADGE': 'Risingbadge',
    # estatistica, item, coisa solta
    'SPECIAL': 'Special', 'DEFENSE': 'Defense', 'SP.DEF': 'Sp.Def',
    'SP.ATK': 'Sp.Atk', 'COIN': 'coin', 'MALASADAS': 'malasadas',
    'EXTREMESPEED': 'Extreme Speed', 'DOLL--CLEFAIRY': 'Doll--Clefairy',
    'LOVELY': 'Lovely', 'SWORD': 'Sword', 'SHIELD': 'Shield',
    'SOURCE': 'source', 'EGGENING': 'Eggening', 'MACHINES': 'Machines',
    'OWNED': 'owned', 'LITTER': 'Litter', 'DETECTED': 'detected',
    'BETWEEN': 'Between', 'FAIREST': 'fairest', 'ONE': 'one', 'WAY': 'Way',
    'MYSELF': 'myself', 'CANCEL': 'Cancel',
    # grito e onomatopeia: caixa alta e a entonacao, fica como esta
    'AGH': 'AGH', 'URGH': 'URGH', 'SHRIEEEEK': 'SHRIEEEEK',
    'TUUUUU': 'TUUUUU', 'KEEEEEEEEEEEE': 'KEEEEEEEEEEEE',
    'SHAAAAAAAA': 'SHAAAAAAAA', 'KA-BOOM': 'KA-BOOM',
    'PI-PIKACHU': 'PI-PIKACHU', 'CLICK': 'CLICK', 'BOOM': 'BOOM',
}

# Palavra pequena: minuscula no meio de um titulo em Title Case.
PEQUENAS = {'A', 'AN', 'AND', 'THE', 'OF', 'TO', 'IN', 'ON', 'AT', 'BY',
            'FOR', 'OR', 'INTO', 'WITH', 'FROM'}

# Rotulo cujo texto NAO se toca (voz de maquina, placar, enfase proposital).
PULAR = {
    'Route25_BillsHouse_Text_Teleporter',   # voz de maquina
    'Route22_Text_Silver5',                 # "ALL BY MYSELF!" e grito do rival
    'Route25_BillsHouse_Text_NotInParty',   # voz da maquina do Teleporter
}

# Rotulo de bloco todo em caixa alta que e FRASE, nao placa: vira sentenca.
FRASES_NAO_PLACA = {
    'CeladonMansionRoofHouse_Text_PharmacistStory',
    'ViridianCity_Text_WelcomeSign',
    'PewterCity_Text_WelcomeSign',
    'Copycat_Text_Dodrio2',          # "mirror, mirror on the wall..."
    'FuchsiaCity_Text_SafariZone',   # "Safari Zone / now owned by / Devon Corp."
}

# -------------------------------------------------------------- tokenizacao
TOKEN = re.compile(r"[A-Za-zé][A-Za-zé0-9'.]*(?:-(?!-)[A-Za-zé0-9'.]*)*")
PLACEHOLDER = re.compile(r'\{[^}]*\}')
# Caixa que o tokenizador nao enxerga (minuscula no meio da palavra).
PRE_TROCA = [
    (re.compile(r'\bPOKeMON\b'), 'Pokémon'),
    (re.compile(r'\bPOKeDEX\b'), 'Pokédex'),
    (re.compile(r'\bPokéGear\b'), 'Pokégear'),
    (re.compile(r'\b([A-Z]{3,})-(?:TYPE|type)(s?)\b'),
     lambda m: m.group(1).capitalize() + '-type' + m.group(2)),
    (re.compile(r'\bSKY-blue\b'), 'Sky-blue'),
]
QUEBRA = re.compile(r'\\[nlp]')


SUFIXO = re.compile(r"((?:'[sS]|es|s)?[.,!?;:…]*)$")
TM_HM = re.compile(r'^(?:TM|HM)\d+$')
X_TYPE = re.compile(r'^([A-Z]+)-TYPE$')


def parte(tok):
    """Separa miolo e sufixo ("BILL's" -> BILL + 's; "SP.DEF." -> SP.DEF + .)."""
    m = SUFIXO.search(tok)
    miolo, suf = tok[:m.start()], m.group(1)
    if suf[:2] == "'S":
        suf = "'s" + suf[2:]
    return miolo, suf


def junta(canon, cauda):
    """Cola a forma canonica com o sufixo do token original, sem duplicar."""
    if cauda[:2] == "'s" and canon[-2:].lower() == "'s":
        canon = canon[:-2]
    while cauda and canon[-1:] == cauda[0] and cauda[0] in '.,!?;:…':
        canon = canon[:-1]
    return canon + cauda


def eh_caixa_alta(tok):
    miolo, _ = parte(tok)
    letras = [c for c in miolo if c.isalpha()]
    return len(letras) >= 2 and all(c.isupper() or c == 'é' for c in letras) \
        and any(c.isupper() for c in letras)


def chave(tok):
    """Chave de dicionario: sem sufixo, sem acento de caixa."""
    miolo, _ = parte(tok)
    return miolo.upper().replace('É', 'é')


def titulo(tok):
    """Primeira letra de cada subpalavra separada por ponto; resto minusculo."""
    out = []
    novo = True
    for c in tok:
        if novo and c.isalpha():
            out.append(c.upper())
            novo = False
        elif c == '.':
            out.append(c)
            novo = True
        else:
            out.append(c.lower() if c.isalpha() else c)
    return ''.join(out)


class Decap:
    def __init__(self):
        self.frases = {}
        self.palavras = dict(PALAVRAS)
        for nome in nomes_do_repo():
            self._add_frase(nome)
        for linha in FRASES_MANUAIS.split('\n'):
            for nome in linha.split('|'):
                if nome.strip():
                    self._add_frase(nome.strip())
        # "Pokemon" do repo nao tem o é; o texto do jogo usa Pokémon
        self.palavras['POKéMON'] = 'Pokémon'
        self.palavras['POKéDEX'] = 'Pokédex'
        self.palavras['POKéGEAR'] = 'Pokégear'
        self.palavras['POKéMART'] = 'Pokémart'
        self.palavras['POKéCENTER'] = 'Pokécenter'
        self.palavras['POKé'] = 'Poké'
        self.palavras['POKEMON'] = 'Pokémon'
        self.desconhecidas = collections.Counter()
        self.enfase = collections.Counter()
        self.blocos_placa = []

    def _add_frase(self, nome):
        toks = [t for t in nome.split() if TOKEN.fullmatch(t) or True]
        toks = nome.split()
        k = ' '.join(chave(t) for t in toks)
        if len(toks) == 1:
            self.palavras.setdefault(k, nome)
        else:
            self.frases.setdefault(k, toks)

    # ---------------------------------------------------------------- bloco
    def converte_bloco(self, linhas, rotulo):
        """linhas: lista de str (conteudo entre as aspas). Devolve nova lista."""
        if rotulo in PULAR:
            return linhas, []
        junto = ''.join(linhas)
        limpo = QUEBRA.sub(' ', PLACEHOLDER.sub('', junto))
        letras = [c for c in limpo if c.isalpha() and c != 'é']
        if not letras:
            return linhas, []
        todo_caixa = not any(c.islower() for c in letras)
        modo = 'placa' if todo_caixa else 'misto'
        if todo_caixa and rotulo in FRASES_NAO_PLACA:
            modo = 'frase'
        if todo_caixa:
            self.blocos_placa.append((rotulo, modo, ' '.join(linhas)))
        novas, notas = [], []
        # um bloco e convertido como uma sequencia de tokens continua, para que
        # uma frase possa atravessar \n
        toks = []          # (idx_linha, inicio, fim, texto)
        for i, l in enumerate(linhas):
            for pat, rep in PRE_TROCA:
                l = pat.sub(rep, l)
            linhas[i] = l
            mascara = QUEBRA.sub('  ', PLACEHOLDER.sub(
                lambda x: ' ' * len(x.group(0)), l))
            for m in TOKEN.finditer(mascara):
                toks.append([i, m.start(), m.end(), m.group(0)])
        trocas = {}
        inicio_sentenca = True
        j = 0
        while j < len(toks):
            tok = toks[j][3]
            if not eh_caixa_alta(tok):
                if modo != 'placa':
                    inicio_sentenca = tok.endswith(('.', '!', '?'))
                j += 1
                continue
            # tenta frase (do maior para o menor)
            achou = None
            for n in range(min(5, len(toks) - j), 1, -1):
                seq = toks[j:j + n]
                if not all(eh_caixa_alta(t[3]) for t in seq):
                    continue
                k = ' '.join(chave(t[3]) for t in seq)
                if k in self.frases:
                    achou = (n, self.frases[k])
                    break
            if achou:
                n, canon = achou
                for t, novo in zip(toks[j:j + n], canon):
                    _, cauda = parte(t[3])
                    trocas[(t[0], t[1], t[2])] = junta(novo, cauda)
                j += n
                inicio_sentenca = False
                continue
            k = chave(tok)
            _, cauda = parte(tok)
            if TM_HM.match(k):
                j += 1
                inicio_sentenca = False
                continue
            mt = X_TYPE.match(k)
            if mt:
                trocas[(toks[j][0], toks[j][1], toks[j][2])] = \
                    titulo(mt.group(1)) + '-type' + cauda
                j += 1
                inicio_sentenca = False
                continue
            if k in self.palavras:
                base = self.palavras[k]
                if modo == 'placa' and k in PEQUENAS and not inicio_sentenca:
                    base = base.lower()
                novo = junta(base, cauda)
                trocas[(toks[j][0], toks[j][1], toks[j][2])] = novo
            elif modo == 'placa':
                if k in PEQUENAS and not inicio_sentenca:
                    novo = tok.lower()
                else:
                    novo = titulo(tok)
                trocas[(toks[j][0], toks[j][1], toks[j][2])] = novo
                if k not in PEQUENAS:
                    self.desconhecidas[k] += 1
                    notas.append(('PLACA-DESCONHECIDA', rotulo, tok))
            elif modo == 'frase':
                novo = titulo(tok) if inicio_sentenca else tok.lower()
                trocas[(toks[j][0], toks[j][1], toks[j][2])] = novo
                self.desconhecidas[k] += 1
            else:
                self.enfase[k] += 1
                notas.append(('ENFASE', rotulo, tok))
            if modo == 'placa':
                inicio_sentenca = tok.endswith(('.', '!', '?'))
            else:
                inicio_sentenca = tok.endswith(('.', '!', '?'))
            j += 1
        for i, l in enumerate(linhas):
            pend = sorted([t for t in trocas if t[0] == i], key=lambda t: -t[1])
            for (_, a, b) in pend:
                l = l[:a] + trocas[(i, a, b)] + l[b:]
            novas.append(l)
        return novas, notas


# ----------------------------------------------------------------- arquivos
RE_ROTULO = re.compile(r'^(\w+)::?\s*$')
RE_STRING = re.compile(r'^(\s*\.string\s+")(.*)("\s*)$')


def processa(arq, dec):
    linhas = open(arq, encoding='utf-8').read().split('\n')
    saida = list(linhas)
    rotulo = None
    i = 0
    notas = []
    n_blocos = 0
    while i < len(linhas):
        m = RE_ROTULO.match(linhas[i])
        if m:
            rotulo = m.group(1)
            i += 1
            continue
        m = RE_STRING.match(linhas[i])
        if not m:
            i += 1
            continue
        # junta o bloco
        idxs, conteudos, pre, pos = [], [], [], []
        j = i
        while j < len(linhas):
            mm = RE_STRING.match(linhas[j])
            if not mm:
                break
            idxs.append(j)
            pre.append(mm.group(1))
            conteudos.append(mm.group(2))
            pos.append(mm.group(3))
            if mm.group(2).rstrip().endswith('$'):
                j += 1
                break
            j += 1
        novas, nts = dec.converte_bloco(conteudos, rotulo)
        notas += nts
        if novas != conteudos:
            n_blocos += 1
        for k, idx in enumerate(idxs):
            saida[idx] = pre[k] + novas[k] + pos[k]
        i = j
    return linhas, saida, notas, n_blocos


def main():
    ap = argparse.ArgumentParser()
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--resumo', action='store_true')
    g.add_argument('--conferir', action='store_true')
    g.add_argument('--aplicar', action='store_true')
    g.add_argument('--blocos-caixa-alta', action='store_true')
    ap.add_argument('arquivos', nargs='+')
    a = ap.parse_args()
    dec = Decap()
    total = 0
    for arq in a.arquivos:
        antes, depois, notas, n = processa(arq, dec)
        total += n
        if a.conferir and antes != depois:
            import difflib
            for l in difflib.unified_diff(antes, depois, arq, arq + ' (decap)',
                                          lineterm='', n=0):
                print(l)
        if a.aplicar and antes != depois:
            open(arq, 'w', encoding='utf-8').write('\n'.join(depois))
            print(f'{arq}: {n} blocos')
        if a.resumo and n:
            print(f'{arq}: {n} blocos')
    print(f'--- total: {total} blocos mudados')
    if a.blocos_caixa_alta:
        for rot, modo, txt in dec.blocos_placa:
            print(f'{modo}\t{rot}\t{txt}')
    if dec.desconhecidas:
        print('--- palavra de placa fora do dicionario (virou Title Case):')
        for w, c in dec.desconhecidas.most_common():
            print(f'  {c:4d}  {w}')
    if dec.enfase:
        print('--- caixa alta MANTIDA em bloco misto (enfase do autor?):')
        for w, c in dec.enfase.most_common():
            print(f'  {c:4d}  {w}')


if __name__ == '__main__':
    main()
