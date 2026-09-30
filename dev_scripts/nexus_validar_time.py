#!/usr/bin/env python3
"""Confere os times do Nexus escritos nas fichas (.claude/rift_missions/nexus/).

Pega todo bloco de codigo que comeca com "=== TRAINER_NEXUS_" nas fichas
(ou em arquivos .party/.md passados na linha de comando), passa pelo
trainerproc de verdade e confere cada Pokemon contra os dados do jogo:

  - especie, item, habilidade, pic e classe existem
  - habilidade e uma das tres da especie
  - os 4 golpes sao aprendiveis (level-up gen 9, TM/tutor, egg move da familia)
  - 31 IV e 252 EV em tudo (NEXUS_REGRAS R13), 4 golpes escritos
  - 6 Pokemon, sem especie repetida
  - vagas do Traditional (R10/R11): exatamente 1 lendario, 1 semi-lendario e
    1 Mega (pedra certa para a especie; Primal e Dragon Ascent contam como Mega)

Uso:
  python3 dev_scripts/nexus_validar_time.py                 # todas as fichas
  python3 dev_scripts/nexus_validar_time.py ficha.md ...    # so estas

Precisa de src/data/pokemon/teachable_learnsets.h (gerado pelo build; sem o
toolchain ARM, gere com os tres scripts de tools/learnset_helpers como o
Makefile faz) e de tools/trainerproc/trainerproc compilado.
"""
import glob
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)

# NEXUS_REGRAS R10: miticos que ocupam a vaga de lendario. Os outros miticos
# sao semi-lendarios.
MYTHICAL_AS_LEGEND = {
    'ARCEUS', 'DARKRAI', 'DEOXYS', 'HOOPA', 'GENESECT', 'MAGEARNA', 'MARSHADOW',
}


def read(path):
    with open(path, encoding='utf-8') as f:
        return f.read()


def parse_species():
    info = {}
    family_of = {}
    for path in sorted(glob.glob('src/data/pokemon/species_info/gen_*_families.h')):
        text = read(path)
        # habilidades por macro (#if P_UPDATED_ABILITIES >= GEN_x / #else): vale a
        # primeira definicao, porque P_UPDATED_ABILITIES e GEN_LATEST
        ability_macros = {}
        for mm in re.finditer(r'#define (\w+_ABILITIES)\s*\{([^}]*)\}', text):
            ability_macros.setdefault(mm.group(1), re.findall(r'ABILITY_\w+', mm.group(2)))
        # especies escritas por macro (GENESECT_SPECIES_INFO(form) etc.)
        macros = {}
        for mm in re.finditer(r'#define (\w+_SPECIES_INFO)\(([^)]*)\)((?:.*\\\n)*.*)', text):
            params = [x.strip() for x in mm.group(2).split(',') if x.strip()]
            macros[mm.group(1)] = (params, mm.group(3))
        # entries
        for fam in re.finditer(r'#if P_FAMILY_(\w+)\n(.*?)#endif //P_FAMILY_\1', text, re.S):
            fname, body = fam.groups()
            starts = [m for m in re.finditer(r'^\s*\[(SPECIES_\w+)\]\s*=', body, re.M)]
            for i, m in enumerate(starts):
                end = starts[i + 1].start() if i + 1 < len(starts) else len(body)
                chunk = body[m.end():end]
                sp = m.group(1)
                mac = re.match(r'\s*(\w+_SPECIES_INFO)\(([^)]*)\)', chunk)
                if mac and mac.group(1) in macros:
                    params, mbody = macros[mac.group(1)]
                    args = [x.strip() for x in mac.group(2).split(',')]
                    for prm, arg in zip(params, args):
                        mbody = re.sub(r'\b' + re.escape(prm) + r'\b', arg, mbody)
                    chunk = mbody.replace("##", "") + chunk
                d = {'family': fname}
                a = re.search(r'\.abilities\s*=\s*\{([^}]*)\}', chunk)
                am = re.search(r'\.abilities\s*=\s*(\w+_ABILITIES)\b', chunk)
                if am and am.group(1) in ability_macros:
                    d['abilities'] = ability_macros[am.group(1)]
                else:
                    d['abilities'] = re.findall(r'ABILITY_\w+', a.group(1)) if a else []
                for flag in ('isRestrictedLegendary', 'isSubLegendary', 'isMythical',
                             'isUltraBeast', 'isParadox', 'isMegaEvolution', 'isPrimalReversion'):
                    d[flag] = bool(re.search(r'\.' + flag + r'\s*=\s*TRUE', chunk))
                for key in ('levelUpLearnset', 'teachableLearnset', 'eggMoveLearnset', 'formChangeTable'):
                    mm = re.search(r'\.' + key + r'\s*=\s*(\w+)', chunk)
                    d[key] = mm.group(1) if mm else None
                info[sp] = d
                family_of.setdefault(fname, []).append(sp)
    return info, family_of


def parse_move_arrays(path, pattern):
    out = {}
    text = read(path)
    for m in re.finditer(pattern, text, re.S):
        out[m.group(1)] = set(re.findall(r'MOVE_\w+', m.group(2)))
    return out


def parse_form_changes():
    text = read('src/data/pokemon/form_change_tables.h')
    out = {}
    for m in re.finditer(r'static const struct FormChange (\w+)\[\] =\s*\{(.*?)\n\};', text, re.S):
        megas = []
        for e in re.finditer(r'FORM_CHANGE_MOVE\s*,\s*(SPECIES_\w+)\s*,\s*(MOVE_\w+)\s*,\s*WHEN_LEARNED', m.group(2)):
            megas.append(('FORM_MOVE', e.group(1), e.group(2)))
        for e in re.finditer(r'FORM_CHANGE_BATTLE_(MEGA_EVOLUTION_ITEM|PRIMAL_REVERSION|MEGA_EVOLUTION_MOVE)\s*,\s*(SPECIES_\w+)\s*(?:,\s*(\w+))?', m.group(2)):
            megas.append((e.group(1), e.group(2), e.group(3)))
        out[m.group(1)] = megas
    return out


def extract_blocks(paths):
    blocks = []
    for p in paths:
        text = read(p)
        if p.endswith('.party'):
            parts = re.split(r'(?m)^(?==== )', text)
            blocks += [(p, b.strip() + '\n') for b in parts if b.startswith('=== TRAINER_NEXUS_')]
            continue
        for m in re.finditer(r'```[a-z]*\n(=== TRAINER_NEXUS_.*?)```', text, re.S):
            blocks.append((p, m.group(1)))
    return blocks


def run_trainerproc(party_text):
    with tempfile.TemporaryDirectory() as tmp:
        src = os.path.join(tmp, 'nexus.party')
        out = os.path.join(tmp, 'nexus.h')
        with open(src, 'w', encoding='utf-8') as f:
            f.write(party_text)
        cpp = subprocess.run(['cpp', '-iquote', 'include', '-Wno-trigraphs', '-DMODERN=1', '-DTESTING=0',
                              '-DEMERALD', '-std=gnu17', '-traditional-cpp', '-'],
                             input=party_text, capture_output=True, text=True)
        tp = subprocess.run(['tools/trainerproc/trainerproc', '-o', out, '-i', src, '-'],
                            input=cpp.stdout, capture_output=True, text=True)
        if tp.returncode != 0:
            return None, tp.stderr + tp.stdout
        return read(out), ''


def main():
    args = sys.argv[1:]
    paths = args or sorted(glob.glob('.claude/rift_missions/nexus/*/*.md'))
    blocks = extract_blocks(paths)
    if not blocks:
        print('Nenhum bloco === TRAINER_NEXUS_ encontrado.')
        return 0

    species, families = parse_species()
    levelup = parse_move_arrays('src/data/pokemon/level_up_learnsets/gen_9.h',
                                r'static const struct LevelUpMove (\w+)\[\] = \{(.*?)\};')
    teach = parse_move_arrays('src/data/pokemon/teachable_learnsets.h',
                              r'static const u16 (\w+)\[\] = \{(.*?)\};')
    egg = parse_move_arrays('src/data/pokemon/egg_moves.h', r'static const u16 (\w+)\[\] = \{(.*?)\};')
    forms = parse_form_changes()
    items = set(re.findall(r'\b(ITEM_\w+)\s*=', read('include/constants/items.h'))) | {'ITEM_NONE'}
    aliases = dict(re.findall(r'#define (SPECIES_\w+)\s+(SPECIES_\w+)', read('include/constants/species.h')))
    trainer_consts = read('include/constants/trainers.h')
    moves_h = set(re.findall(r'\b(MOVE_\w+)\s*=', read('include/constants/moves.h')))

    total_err = 0
    seen = {}
    for path, block in blocks:
        tid = re.match(r'=== (TRAINER_NEXUS_\w+) ===', block).group(1)
        where = os.path.relpath(path)
        if tid in seen and seen[tid] != where:
            print(f'{tid}: bloco repetido em {seen[tid]} e {where}')
            total_err += 1
        seen[tid] = where
        errs = []
        out, msg = run_trainerproc(block)
        if out is None:
            print(f'✗ {tid} ({where})\n    trainerproc: {msg.strip()}')
            total_err += 1
            continue
        pic = re.search(r'\.trainerPic = (\w+)', out).group(1)
        cls = re.search(r'\.trainerClass = (\w+)', out).group(1)
        if not re.search(r'\b' + pic + r'\b', trainer_consts):
            errs.append(f'pic {pic} nao existe')
        if not re.search(r'\b' + cls + r'\b', trainer_consts):
            errs.append(f'classe {cls} nao existe')
        parts = re.split(r'\.species = ', out)[1:]
        mons = [(re.match(r'(SPECIES_\w+)', p).group(1), p) for p in parts]
        if len(mons) != 6:
            errs.append(f'{len(mons)} Pokemon (precisa de 6)')
        legend, semi, mega = [], [], []
        seen_species = set()
        for sp, body in mons:
            while sp in aliases:
                sp = aliases[sp]
            name = sp.replace('SPECIES_', '')
            d = species.get(sp)
            if not d:
                errs.append(f'{name}: especie nao existe')
                continue
            if sp in seen_species:
                errs.append(f'{name}: especie repetida')
            seen_species.add(sp)
            item = re.search(r'\.heldItem = \{ (\w+)', body)
            item = item.group(1) if item else 'ITEM_NONE'
            if item not in items:
                errs.append(f'{name}: item {item} nao existe')
            ab = re.search(r'\.ability = (\w+)', body)
            ab = ab.group(1) if ab else None
            if ab is None:
                errs.append(f'{name}: sem Ability')
            elif ab not in d['abilities']:
                errs.append(f'{name}: {ab} nao e habilidade da especie ({", ".join(a for a in d["abilities"] if a != "ABILITY_NONE")})')
            if 'TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31)' not in body:
                errs.append(f'{name}: IVs nao sao 31 em tudo')
            if 'TRAINER_PARTY_EVS(252, 252, 252, 252, 252, 252)' not in body:
                errs.append(f'{name}: EVs nao sao 252 em tudo')
            if '.nature' not in body:
                errs.append(f'{name}: sem Nature')
            mv = re.search(r'\.moves = \{(.*?)\}', body, re.S)
            mv = re.findall(r'MOVE_\w+', mv.group(1)) if mv else []
            if len(mv) != 4:
                errs.append(f'{name}: {len(mv)} golpes (precisa de 4)')
            learn = set()
            learn |= levelup.get(d['levelUpLearnset'], set())
            learn |= teach.get(d['teachableLearnset'], set())
            for other in families.get(d['family'], []):
                learn |= egg.get(species[other]['eggMoveLearnset'], set())
            # golpe que a forma ganha ao trocar (Rotom-Wash -> Hydro Pump)
            for kind, target, trig in forms.get(d['formChangeTable'], []):
                if kind == 'FORM_MOVE' and target == sp:
                    learn.add(trig)
            for m in mv:
                if m not in moves_h:
                    errs.append(f'{name}: golpe {m} nao existe')
                elif m not in learn:
                    errs.append(f'{name}: nao aprende {m.replace("MOVE_", "")}')
            # categorias
            if d['isRestrictedLegendary'] or (d['isMythical'] and any(name.startswith(x) for x in MYTHICAL_AS_LEGEND)):
                legend.append(name)
            elif d['isSubLegendary'] or d['isUltraBeast'] or d['isParadox'] or d['isMythical']:
                semi.append(name)
            for kind, target, trig in forms.get(d['formChangeTable'], []):
                if kind == 'MEGA_EVOLUTION_ITEM' and trig == item:
                    mega.append(f'{name}->{target.replace("SPECIES_", "")}')
                elif kind == 'PRIMAL_REVERSION' and trig == item:
                    mega.append(f'{name}->{target.replace("SPECIES_", "")}')
                elif kind == 'MEGA_EVOLUTION_MOVE' and trig in mv:
                    mega.append(f'{name}->{target.replace("SPECIES_", "")}')
        if len(legend) != 1:
            errs.append(f'lendarios: {legend or "nenhum"} (precisa de exatamente 1)')
        if len(semi) != 1:
            errs.append(f'semi-lendarios: {semi or "nenhum"} (precisa de exatamente 1)')
        if len(mega) != 1:
            errs.append(f'Megas: {mega or "nenhuma"} (precisa de exatamente 1)')
        summary = f'L={",".join(legend)} S={",".join(semi)} M={",".join(mega)}'
        if errs:
            total_err += len(errs)
            print(f'✗ {tid} ({where})  {summary}')
            for e in errs:
                print('    ' + e)
        else:
            print(f'✓ {tid}  {summary}')
    print(f'\n{len(blocks)} times, {total_err} problema(s).')
    return 1 if total_err else 0


if __name__ == '__main__':
    sys.exit(main())
