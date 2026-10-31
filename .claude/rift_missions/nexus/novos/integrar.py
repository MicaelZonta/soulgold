#!/usr/bin/env python3
"""Integra o lote de treinadores novos do Nexus (31/10/2026) e confere as regras.

    python3 .claude/rift_missions/nexus/novos/integrar.py --conferir   # so valida times.party / falas.inc
    python3 .claude/rift_missions/nexus/novos/integrar.py --aplicar    # valida e grava no repo

Entradas (nesta pasta): manifest.json (IDs, classe, pic, genero, boneco), times.party e falas.inc
(montados pelo Codex). Grava: src/data/trainers.party (blocos TRAINER_NEXUS_*), data/scripts/nexus.inc
(Nexus_EventScript_<X>_Fight + falas) e src/data/nexus/trainers.h (linha X(...)). Idempotente.

Confere por time (NEXUS_REGRAS R10-R13): 6 Pokemon; exatamente 1 lendario, 1 semi-lendario e 1 Mega
(Mega de lendario/semi conta nas duas vagas; Primal conta como Mega); 31 IV e 252 EV em tudo; Nature,
item, habilidade e 4 golpes escritos; habilidade existe no .abilities da especie (o trainerproc nao confere
e o jogo estoura na batalha)."""
import json, os, re, sys, glob

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', '..'))
AQUI = os.path.dirname(os.path.abspath(__file__))
os.chdir(ROOT)

# mitico -> vaga (NEXUS_REGRAS R10, tabela fechada)
MITICO_LENDARIO = {'ARCEUS', 'DARKRAI', 'DEOXYS', 'HOOPA', 'GENESECT', 'MAGEARNA', 'MARSHADOW'}


def species_table():
    """SPECIES_X -> dict(abilities, cat, base) a partir de species_info/*.h"""
    out = {}
    def entries(txt):
        for m in re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*\{(.*?)\n    \},', txt, re.S):
            yield m.group(1), m.group(2)
        # especie montada por macro: [SPECIES_X] = MACRO(...) -> corpo do #define MACRO
        macros = {mm.group(1): mm.group(2) for mm in re.finditer(r'#define (\w+)\([^)]*\)\s*\\\n(.*?)(?<!\\)\n', txt, re.S)}
        for m in re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*(\w+)\(', txt):
            if m.group(2) in macros:
                yield m.group(1), macros[m.group(2)]
    global ALL_INFO
    ALL_INFO = ''.join(open(f).read() for f in glob.glob('src/data/pokemon/species_info/*.h'))
    for f in glob.glob('src/data/pokemon/species_info/*.h'):
        for sp, body in entries(open(f).read()):
            ab = re.search(r'\.abilities\s*=\s*\{([^}]*)\}', body)
            if not ab:   # .abilities = GENGAR_ABILITIES (#if de geracao): aceita qualquer uma das definicoes
                mac = re.search(r'\.abilities\s*=\s*(\w+)', body)
                if mac:
                    defs = re.findall(r'#define %s \{([^}]*)\}' % mac.group(1), ALL_INFO)
                    ab = type('M', (), {'group': lambda self, i, d=','.join(defs): d})()
            flags = {k for k in ('isRestrictedLegendary', 'isSubLegendary', 'isUltraBeast', 'isParadox', 'isMythical', 'isMegaEvolution', 'isPrimalReversion')
                     if re.search(r'\.%s\s*=\s*TRUE' % k, body)}
            out[sp] = dict(abilities={a.strip() for a in ab.group(1).split(',')} if ab else set(), flags=flags)
    # apelidos: #define SPECIES_URSHIFU SPECIES_URSHIFU_SINGLE_STRIKE
    for m in re.finditer(r'#define (SPECIES_\w+)\s+(SPECIES_\w+)\s*$', open('include/constants/species.h').read(), re.M):
        if m.group(2) in out and m.group(1) not in out:
            out[m.group(1)] = out[m.group(2)]
    return out


def const_of(name):
    """Nome do .party -> SPECIES_*, como o trainerproc."""
    s = name.upper().replace('♀', '_F').replace('♂', '_M').replace('É', 'E')
    s = re.sub(r"[.'’:]", '', s)
    s = re.sub(r'[\s\-]+', '_', s)
    return 'SPECIES_' + s


def category(sp, info):
    base = sp.replace('SPECIES_', '').split('_')[0]
    f = info.get(sp, {}).get('flags', set())
    if 'isRestrictedLegendary' in f or ('isMythical' in f and base in MITICO_LENDARIO):
        return 'L'
    if f & {'isSubLegendary', 'isUltraBeast', 'isParadox', 'isMythical'}:
        return 'S'
    return 'C'


def parse_party(txt):
    blocks = {}
    for m in re.finditer(r'^=== (TRAINER_\w+) ===\n(.*?)(?=^=== |\Z)', txt, re.S | re.M):
        blocks[m.group(1)] = m.group(2).rstrip('\n') + '\n'
    return blocks


def mons_of(body):
    parts = re.split(r'\n\s*\n', body.strip())
    return parts[0], parts[1:]


def mega_items():
    txt = open('src/data/items.h').read()
    out = set()
    for m in re.finditer(r'\.name = ITEM_NAME\("([^"]+)"\),(.*?)\n    \},', txt, re.S):
        if re.search(r'HOLD_EFFECT_(MEGA_STONE|PRIMAL_ORB)', m.group(2)):
            out.add(m.group(1))
    out |= set(re.findall(r'TYPE_MEGA_STONE\(\w+, "([^"]+)"', txt))   # pedras de tipo do hack (Electrite...)
    return out


MEGA_ITEMS = set()


def check(man, blocks, falas, info):
    MEGA_ITEMS.update(mega_items())
    erros = []
    for m in man:
        c = m['trainer_const']
        if c not in blocks:
            erros.append(f'{c}: sem time'); continue
        head, mons = mons_of(blocks[c])
        if len(mons) != 6:
            erros.append(f'{c}: {len(mons)} Pokemon')
        cats = {'L': 0, 'S': 0, 'M': 0}
        for mon in mons:
            lines = mon.strip().split('\n')
            first = lines[0]
            nm = first.split('@')[0].strip()
            nm = re.sub(r'\s*\((M|F)\)$', '', re.sub(r'^.*\((.*)\)$', r'\1', nm) if '(' in nm and not nm.endswith(('(M)', '(F)')) else nm)
            item = first.split('@')[1].strip() if '@' in first else ''
            sp = const_of(nm)
            if sp not in info:
                erros.append(f'{c}: especie desconhecida "{nm}" ({sp})'); continue
            cat = category(sp, info)
            if cat in 'LS':
                cats[cat] += 1
            mega = item in MEGA_ITEMS or any(l.strip() == '- Dragon Ascent' for l in lines) and 'RAYQUAZA' in sp
            if mega:
                cats['M'] += 1
            ab = next((l.split(':', 1)[1].strip() for l in lines if l.startswith('Ability:')), None)
            if not ab:
                erros.append(f'{c}: {nm} sem Ability')
            else:
                ac = 'ABILITY_' + re.sub(r'[\s\-]+', '_', re.sub(r"['’]", '', ab.upper()))
                if ac not in info[sp]['abilities']:
                    erros.append(f'{c}: {nm} nao tem {ab} ({", ".join(sorted(info[sp]["abilities"] - {"ABILITY_NONE"}))})')
            if not any(l.endswith(' Nature') for l in lines):
                erros.append(f'{c}: {nm} sem Nature')
            if not item:
                erros.append(f'{c}: {nm} sem item')
            if 'IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe' not in mon:
                erros.append(f'{c}: {nm} IV != 31')
            if 'EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe' not in mon:
                erros.append(f'{c}: {nm} EV != 252')
            if sum(1 for l in lines if l.startswith('- ')) != 4:
                erros.append(f'{c}: {nm} sem 4 golpes')
        if (cats['L'], cats['S'], cats['M']) != (1, 1, 1):
            erros.append(f'{c}: lendario/semi/mega = {cats["L"]}/{cats["S"]}/{cats["M"]} (R11 pede 1/1/1)')
        for k in ('Intro', 'Defeat'):
            if not re.search(r'^Nexus_Text_%s_%s:' % (m['script'], k), falas, re.M):
                erros.append(f'{c}: falta Nexus_Text_{m["script"]}_{k}')
    return erros


def header(m):
    return (f"Name: {m['name']}\nClass: {m['cls']}\nPic: {m['pic']}\nGender: {m['gender']}\n"
            f"Music: {'Female' if m['gender'] == 'Female' else 'Male'}\nDouble Battle: {'Yes' if m['enum'] == 'JESSIE_JAMES' else 'No'}\nAI: Smart Trainer\n")


def aplicar(man, blocks, falas):
    p = 'src/data/trainers.party'
    party = open(p).read()
    for m in man:
        c = m['trainer_const']
        _, mons = mons_of(blocks[c])
        body = header(m) + '\n' + '\n\n'.join(x.strip('\n') for x in mons) + '\n'
        new = f'=== {c} ===\n{body}'
        old = re.search(r'^=== %s ===\n.*?(?=^=== |\Z)' % c, party, re.S | re.M)
        if old:
            party = party[:old.start()] + new + '\n' + party[old.end():]
        else:
            party = party.rstrip('\n') + '\n\n' + new
    open(p, 'w').write(party)

    p = 'data/scripts/nexus.inc'
    inc = open(p).read()
    mark0, mark1 = '@ ---- lote de 31/10/2026 (inicio) ----\n', '@ ---- lote de 31/10/2026 (fim) ----\n'
    inc = re.sub(re.escape(mark0) + '.*?' + re.escape(mark1), '', inc, flags=re.S)
    fights = ''.join(f"Nexus_EventScript_{m['script']}_Fight::\n\tnexus_fight {m['trainer_const']}, Nexus_Text_{m['script']}_Intro, "
                     f"Nexus_Text_{m['script']}_Defeat\n\treturn\n\n" for m in man)
    inc = inc.rstrip('\n') + '\n\n' + mark0 + fights + falas.strip('\n') + '\n' + mark1
    open(p, 'w').write(inc)

    p = 'src/data/nexus/trainers.h'
    h = open(p).read()
    for m in man:
        if re.search(r'X\(%s,' % m['enum'], h):
            continue
        line = f"    X({m['enum']}, {m['script']}, {m['trainer_const']}, {m['gfx']})"
        last = list(re.finditer(r'^    X\(.*\\\n', h, re.M))[-1]
        h = h[:last.end()] + f'{line:<75}\\\n' + h[last.end():]
    open(p, 'w').write(h)


def main():
    man = json.load(open(os.path.join(AQUI, 'manifest.json')))
    blocks = parse_party(open(os.path.join(AQUI, 'times.party')).read())
    falas = open(os.path.join(AQUI, 'falas.inc')).read()
    info = species_table()
    erros = check(man, blocks, falas, info)
    for e in erros:
        print('X', e)
    print(f'{len(man)} treinadores, {len(erros)} problemas')
    if '--aplicar' in sys.argv:
        if erros and '--forcar' not in sys.argv:
            sys.exit('nao aplicado: corrija os problemas (ou --forcar)')
        aplicar(man, blocks, falas)
        print('aplicado')


if __name__ == '__main__':
    main()
