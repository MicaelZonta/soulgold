#!/usr/bin/env python3
"""Integra os campeoes extras dos lendarios do Nexus (meta: todo treinador campeao de >= 3 lendarios).

    python3 .claude/rift_missions/nexus/novos/campeoes.py --conferir
    python3 .claude/rift_missions/nexus/novos/campeoes.py --aplicar

Entradas (nesta pasta): campeoes.json [{trainer, species, script}] e falas_campeao.inc (montados pelo Codex).
Grava, entre marcadores (idempotente): src/data/nexus/champions.h (extern + linha da tabela) e
data/scripts/nexus.inc (Nexus_EventScript_<script>_ChampionFight + falas). O sorteio do campeao do dia entre
o campeao original do lendario e estes extras fica em src/nexus.c (GetTodaysChampion)."""
import collections, json, os, re, sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..', '..'))
AQUI = os.path.dirname(os.path.abspath(__file__))
os.chdir(ROOT)


def estado():
    leg = open('src/data/nexus/legendaries.h').read()
    tr = open('src/data/nexus/trainers.h').read()
    trainers = {e: s for e, s, t, g in re.findall(r'X\((\w+),\s*(\w+),\s*(TRAINER_NEXUS_\w+),\s*(OBJ_EVENT_GFX_\w+)\)', tr)}
    atuais = re.findall(r'\.species\s*=\s*(SPECIES_\w+),\s*\.champion = NEXUS_TRAINER_(\w+)', leg)
    return trainers, atuais


def check(novos, falas, trainers, atuais):
    erros = []
    especies = {s for s, _ in atuais}
    pares = {(t, s) for s, t in atuais}
    vistos = set()
    for n in novos:
        t, s, sc = n['trainer'], n['species'], n['script']
        if t not in trainers:
            erros.append(f'{sc}: treinador {t} nao esta no pool')
        if s not in especies:
            erros.append(f'{sc}: {s} nao e lendario do pool')
        if (t, s) in pares or (t, s) in vistos:
            erros.append(f'{sc}: {t} ja e campeao de {s}')
        vistos.add((t, s))
        if not re.fullmatch(r'[A-Za-z0-9_]+', sc):
            erros.append(f'{sc}: nome de script invalido')
        for k in ('ChampionIntro', 'ChampionDefeat', 'ChampionAfter'):
            if not re.search(r'^Nexus_Text_%s_%s:' % (sc, k), falas, re.M):
                erros.append(f'{sc}: falta Nexus_Text_{sc}_{k}')
        if not re.search(r'^Nexus_Text_%s_ChampionAfter:\n\t\.string "\{SPEAKER ' % sc, falas, re.M):
            erros.append(f'{sc}: _ChampionAfter sem plaquinha (R16)')
    total = collections.Counter(t for _, t in atuais) + collections.Counter(n['trainer'] for n in novos)
    for t in trainers:
        if total[t] < 3:
            erros.append(f'{t}: so {total[t]} lendario(s)')
    scripts = collections.Counter(n['script'] for n in novos)
    erros += [f'{s}: script repetido' for s, c in scripts.items() if c > 1]
    return erros, total


def troca(txt, ini, fim, novo):
    a, b = txt.index(ini) + len(ini), txt.index(fim)
    return txt[:a] + novo + txt[b:]


def aplicar(novos, falas):
    p = 'src/data/nexus/champions.h'
    h = open(p).read()
    ext = ''.join(f"NEXUS_EXTRA_CHAMPION_EXTERN({n['script']})\n" for n in novos)
    tab = ''.join(f"    NEXUS_EXTRA_CHAMPION({n['species'][8:]}, {n['trainer']}, {n['script']}),\n" for n in novos)
    h = troca(h, '// ---- gerado (inicio) ----\n', '// ---- gerado (fim) ----', ext)
    h = troca(h, '// ---- tabela gerada (inicio) ----\n', '// ---- tabela gerada (fim) ----', tab)
    open(p, 'w').write(h)

    p = 'data/scripts/nexus.inc'
    inc = open(p).read()
    m0, m1 = '@ ---- campeoes extras (inicio) ----\n', '@ ---- campeoes extras (fim) ----\n'
    inc = re.sub(re.escape(m0) + '.*?' + re.escape(m1), '', inc, flags=re.S)
    tr = {e: t for e, s, t, g in re.findall(r'X\((\w+),\s*(\w+),\s*(TRAINER_NEXUS_\w+),\s*(OBJ_EVENT_GFX_\w+)\)',
                                             open('src/data/nexus/trainers.h').read())}
    fights = ''.join(
        f"Nexus_EventScript_{n['script']}_ChampionFight::\n"
        f"\tnexus_fight {tr[n['trainer']]}, Nexus_Text_{n['script']}_ChampionIntro, Nexus_Text_{n['script']}_ChampionDefeat\n"
        f"\tgoto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return\n"
        f"\tmsgbox Nexus_Text_{n['script']}_ChampionAfter, MSGBOX_DEFAULT\n\tclosemessage\n\treturn\n\n" for n in novos)
    inc = inc.rstrip('\n') + '\n\n' + m0 + fights + falas.strip('\n') + '\n' + m1
    open(p, 'w').write(inc)


def main():
    novos = json.load(open(os.path.join(AQUI, 'campeoes.json')))
    falas = open(os.path.join(AQUI, 'falas_campeao.inc')).read()
    trainers, atuais = estado()
    erros, total = check(novos, falas, trainers, atuais)
    for e in erros:
        print('X', e)
    por_lend = collections.Counter(n['species'] for n in novos)
    print(f'{len(novos)} associacoes novas; treinadores com >=3: {sum(1 for t in trainers if total[t] >= 3)}/{len(trainers)}; '
          f'lendario com mais campeoes: {max(por_lend.values()) + 1 if por_lend else 1}; {len(erros)} problemas')
    if '--aplicar' in sys.argv:
        if erros and '--forcar' not in sys.argv:
            sys.exit('nao aplicado')
        aplicar(novos, falas)
        print('aplicado')


if __name__ == '__main__':
    main()
