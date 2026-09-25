#!/usr/bin/env python3
"""Auditoria das flags de SoulGold.

Roda na raiz do repo:

    python3 dev_scripts/flag_audit.py            # resumo no terminal
    python3 dev_scripts/flag_audit.py --csv      # regrava docs/SOULGOLD_FLAGS_AUDIT.csv

O que ele faz:
  1. Resolve TODOS os #define de include/constants/flags.h para numero
     (inclusive os que dependem de opponents.h / rematches.h).
  2. Varre todo arquivo versionado procurando cada nome de flag, e classifica
     cada ocorrencia em leitura (goto_if_set, FlagGet, ...), escrita (setflag,
     clearflag, FlagSet, as macros *legendaryencounter) ou outro (tabela de
     dados, campo "flag" de map.json).
  3. Marca como fora da ROM tudo que so aparece em mapa de rom_excluded_groups
     (data/maps/map_groups.json) - esses mapas nao existem no jogo compilado.

Leia docs/SOULGOLD_FLAGS_AUDIT.csv e .claude/SOULGOLD_FLAGS_AUDIT.md para o
resultado interpretado.
"""

import argparse
import collections
import csv
import json
import os
import re
import subprocess
import sys

EXT = ('.c', '.h', '.inc', '.pory', '.json', '.s', '.txt', '.md', '.py', '.mk',
       '.party', '.cfg', '.sh')
SKIP_DIRS = ('build/', 'graphics/', 'sound/')
FLAGS_H = "include/constants/flags.h"

# Comandos de script que ESCREVEM a flag. As macros *legendaryencounter passam
# a flag em VAR_0x8007 e o special BattleSetup_Finish* faz o FlagSet.
WRITE_CMD = {'setflag', 'clearflag', 'legendaryencounter',
             'bosslegendaryencounter', 'bosslegendaryencounterwithmoves'}
READ_CMD = {'goto_if_set', 'goto_if_unset', 'call_if_set', 'call_if_unset',
            'checkflag', 'vgoto_if_set', 'vgoto_if_unset', 'if', 'elif', 'while'}

TOKEN = re.compile(r'\b(FLAG_[A-Z0-9_]+|TESTING_FLAG_[A-Z0-9_]+)\b')


def parse_defines(path, ns):
    """Le #defines em ordem, avaliando a expressao no namespace acumulado."""
    order = []
    txt = open(path, encoding='utf-8', errors='replace').read().replace("\\\n", " ")
    for m in re.finditer(r'^#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.*)$', txt, re.M):
        name, rest = m.group(1), m.group(2)
        if '//' in rest:
            expr, comment = rest.split('//', 1)
        elif '/*' in rest:
            expr, comment = rest.split('/*', 1)
        else:
            expr, comment = rest, ''
        expr = expr.strip()
        comment = comment.strip().rstrip('*/').strip()
        if not expr:
            continue
        try:
            val = eval(expr, {"__builtins__": {}}, ns)
        except Exception:
            val = None
        if isinstance(val, int):
            ns[name] = val
        order.append((name, comment, val, txt.count("\n", 0, m.start()) + 1))
    return order


def load_flags(root):
    ns = {}
    rem = open(os.path.join(root, "include/constants/rematches.h")).read()
    i = 0
    for m in re.finditer(r'^\s*(REMATCH_[A-Z0-9_]+)\s*(?:=\s*([^,]+))?,', rem, re.M):
        if m.group(2):
            i = eval(m.group(2), {"__builtins__": {}}, ns)
        ns[m.group(1)] = i
        i += 1
    parse_defines(os.path.join(root, "include/constants/opponents.h"), ns)
    order = parse_defines(os.path.join(root, FLAGS_H), ns)
    flags = [dict(name=n, comment=c, value=v, line=l) for n, c, v, l in order
             if v is not None and n.startswith(('FLAG_', 'TESTING_FLAG_'))]
    return flags, ns


def dead_maps(root):
    g = json.load(open(os.path.join(root, "data/maps/map_groups.json")))
    excluded = {m for grp in g["rom_excluded_groups"] for m in g[grp]}
    return excluded - set(g["rom_shared_script_maps"])


def scan(root, names):
    files = subprocess.check_output(["git", "ls-files"], cwd=root, text=True).splitlines()
    rec = collections.defaultdict(lambda: dict(
        files=collections.Counter(), maps=collections.Counter(),
        mapjson=collections.Counter(), reads=0, writes=0, other=0, src=0))
    for f in files:
        if not f.endswith(EXT) or f.startswith(SKIP_DIRS) or f == FLAGS_H:
            continue
        try:
            txt = open(os.path.join(root, f), encoding='utf-8', errors='replace').read()
        except OSError:
            continue
        if 'FLAG_' not in txt:
            continue
        parts = f.split('/')
        is_map = f.startswith("data/maps/") and len(parts) > 2
        mapname = parts[2] if is_map else None
        scriptlike = f.endswith(('.inc', '.pory'))
        for line in txt.splitlines():
            if 'FLAG_' not in line:
                continue
            cmd = re.match(r'([A-Za-z_][A-Za-z0-9_]*)', line.strip())
            cmd = cmd.group(1) if cmd else ''
            for m in TOKEN.finditer(line):
                n = m.group(1)
                if n not in names:
                    continue
                r = rec[n]
                r['files'][f] += 1
                if scriptlike:
                    if cmd in WRITE_CMD:
                        r['writes'] += 1
                    elif cmd in READ_CMD or 'flag(' in line:
                        r['reads'] += 1
                    else:
                        r['other'] += 1
                else:
                    pre = line[max(0, m.start() - 30):m.start()]
                    if re.search(r'(FlagSet|FlagClear|FlagToggle)\s*\(\s*$', pre):
                        r['writes'] += 1
                    elif re.search(r'FlagGet\s*\(\s*$', pre):
                        r['reads'] += 1
                    else:
                        r['other'] += 1
                if is_map:
                    r['maps'][mapname] += 1
                    if parts[-1] == "map.json":
                        r['mapjson'][mapname] += 1
                elif f.startswith(("src/", "include/")):
                    r['src'] += 1
    return rec


def classify(flag, rec, dead):
    u = rec.get(flag['name'])
    if not u:
        return "NUNCA_REFERENCIADA", ""
    files = {p for p in u['files']
             if not (p.startswith(('.claude/', 'docs/')) or p.endswith('.md'))}
    maps = set(u['maps'])
    live = maps - dead
    code = [p for p in files if not p.startswith("data/maps/")]
    if not files:
        st = "SO_EM_DOC"
    elif maps and not code and not live:
        st = "SO_MAPAS_FORA_DA_ROM"
    elif u['writes'] and not u['reads'] and not u['mapjson'] and not u['src']:
        st = "SO_ESCRITA"
    elif u['reads'] and not u['writes'] and not u['src']:
        st = "SO_LEITURA"
    else:
        st = "EM_USO"
    if code:
        scope = "GLOBAL(codigo)"
    elif len(live) == 1:
        scope = "MAPA_UNICO:" + next(iter(live))
    elif len(live) > 1:
        scope = "MULTI_MAPA(%d)" % len(live)
    else:
        scope = ""
    return st, scope


def block_of(v, ns):
    if v <= 0x1F:
        return "TEMP"
    if v >= 0x5000:
        return "TESTING"
    if v >= 0x4000:
        return "SPECIAL(EWRAM)"
    if v < ns['TRAINER_FLAGS_START']:
        return "SCRIPT/EVENT"
    if v < ns['RECLAIMED_TRAINER_FLAGS_START']:
        return "TRAINER"
    if v <= ns['TRAINER_FLAGS_END']:
        return "RECLAIMED_TRAINER"
    if v < ns['CUSTOM_FLAGS_START']:
        return "SYSTEM"
    if v <= ns['CUSTOM_FLAGS_END']:
        return "CUSTOM"
    if v < ns['DAILY_FLAGS_START']:
        return "LIVRE"
    return "DAILY"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", action="store_true", help="regrava docs/SOULGOLD_FLAGS_AUDIT.csv")
    args = ap.parse_args()
    root = os.getcwd()
    if not os.path.exists(os.path.join(root, FLAGS_H)):
        sys.exit("rode na raiz do repo")

    flags, ns = load_flags(root)
    dead = dead_maps(root)
    rec = scan(root, {f['name'] for f in flags})

    rows = []
    for f in sorted(flags, key=lambda x: (x['value'], x['name'])):
        u = rec.get(f['name'], {})
        st, scope = classify(f, rec, dead)
        live = sorted(set(u.get('maps', {})) - dead)
        rows.append(dict(valor="0x%X" % f['value'], dec=f['value'], nome=f['name'],
                         bloco=block_of(f['value'], ns), status=st,
                         leituras=u.get('reads', 0), escritas=u.get('writes', 0),
                         arquivos=len(u.get('files', {})), mapas=";".join(live[:4]),
                         escopo=scope, comentario=f['comment']))

    # buracos: posicoes persistentes sem nenhum nome
    named = {f['value'] for f in flags}
    holes = []
    for v in range(0x20, ns['FLAGS_COUNT']):
        if ns['TRAINER_FLAGS_START'] <= v <= ns['TRAINER_FLAGS_END'] or v in named:
            continue
        if holes and v == holes[-1][1] + 1:
            holes[-1][1] = v
        else:
            holes.append([v, v])

    print("flags nomeadas: %d   FLAGS_COUNT: %d (0x%X)" % (len(flags), ns['FLAGS_COUNT'], ns['FLAGS_COUNT']))
    print(collections.Counter(r['status'] for r in rows).most_common())
    fora = [f for f in flags
            if ns['FLAGS_COUNT'] <= f['value'] < 0x4000]
    if fora:
        print("ERRO: flag fora do array flags[] (escreve em cima de vars/gameStats):")
        for f in fora:
            print("   0x%X %s" % (f['value'], f['name']))

    print("buracos sem nome (fora do bloco trainer): %d slots em %d faixas" %
          (sum(b - a + 1 for a, b in holes), len(holes)))
    for a, b in sorted(holes, key=lambda r: r[0] - r[1])[:8]:
        print("   0x%X-0x%X  (%d)" % (a, b, b - a + 1))

    if args.csv:
        out = os.path.join(root, "docs/SOULGOLD_FLAGS_AUDIT.csv")
        with open(out, "w", newline='', encoding='utf-8') as fh:
            w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()))
            w.writeheader()
            w.writerows(rows)
        print("escrito:", out)


if __name__ == "__main__":
    main()
