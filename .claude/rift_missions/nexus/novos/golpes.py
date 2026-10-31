#!/usr/bin/env python3
"""Confere se cada Pokemon dos times TRAINER_NEXUS_* (ou de um prefixo dado) aprende os golpes que tem:
level-up, ovo, TM/tutor (all_learnables.json) e golpes universais, da especie ou de qualquer pre-evolucao.

    python3 .claude/rift_missions/nexus/novos/golpes.py [PREFIXO]   # padrao: TRAINER_NEXUS_"""
import glob, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import integrar

os.chdir(integrar.ROOT)
info_txt = ''.join(open(f).read() for f in glob.glob('src/data/pokemon/species_info/*.h'))
lvl_txt = ''.join(open(f).read() for f in glob.glob('src/data/pokemon/level_up_learnsets/*.h'))
egg_txt = open('src/data/pokemon/egg_moves.h').read()
allL = json.load(open('src/data/pokemon/all_learnables.json'))
univ = set(json.load(open('src/data/pokemon/special_movesets.json')).get('universalMoves', []))


def table(txt, kind):
    return {m.group(1): set(re.findall(r'(MOVE_\w+)', m.group(2)))
            for m in re.finditer(r'static const (?:struct LevelUpMove|u16) (s\w+%s)\[\]\s*=\s*\{(.*?)\};' % kind, txt, re.S)}


LVL, EGG = table(lvl_txt, 'LevelUpLearnset'), table(egg_txt, 'EggMoveLearnset')
entries = {}
for m in re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*\{(.*?)\n    \},', info_txt, re.S):
    entries[m.group(1)] = m.group(2)
prevo = {}
for sp, body in entries.items():
    for ev in re.findall(r'\{EVO_\w+,\s*[^,]*,\s*(SPECIES_\w+)', body):
        prevo.setdefault(ev, sp)
alias = {m.group(1): m.group(2) for m in re.finditer(r'#define (SPECIES_\w+)\s+(SPECIES_\w+)\s*$', open('include/constants/species.h').read(), re.M)}


def learnable(sp):
    out, seen = set(univ), set()
    while sp and sp not in seen:
        seen.add(sp)
        sp = alias.get(sp, sp)
        body = entries.get(sp, '')
        for key, tab in (('levelUpLearnset', LVL), ('eggMoveLearnset', EGG)):
            r = re.search(r'\.%s\s*=\s*(s\w+)' % key, body)
            if r:
                out |= tab.get(r.group(1), set())
        name = sp[8:]
        while name:
            if name in allL:
                out |= set(allL[name]); break
            name = name.rsplit('_', 1)[0] if '_' in name else ''
        sp = prevo.get(sp)
    return out


def move_const(name):
    return 'MOVE_' + re.sub(r'[\s\-]+', '_', re.sub(r"['’.,:]", '', name.upper()))


pref = sys.argv[1] if len(sys.argv) > 1 else 'TRAINER_NEXUS_'
blocks = integrar.parse_party(open('src/data/trainers.party').read())
ruins = 0
for c, body in blocks.items():
    if not c.startswith(pref):
        continue
    _, mons = integrar.mons_of(body)
    for mon in mons:
        lines = mon.strip().split('\n')
        nm = lines[0].split('@')[0].strip()
        sp = integrar.const_of(re.sub(r'\s*\((M|F)\)$', '', nm))
        ok = learnable(sp)
        for l in lines:
            if l.startswith('- '):
                mv = move_const(l[2:].strip())
                if mv not in ok:
                    ruins += 1
                    print(f'{c[14:]:14} {nm:22} {l[2:].strip()}')
print(ruins, 'golpes sem fonte')
