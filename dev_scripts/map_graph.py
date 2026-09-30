#!/usr/bin/env python3
"""Mapa de ligacoes de SoulGold: quem leva a quem, o que e alcancavel.

Roda na raiz do repo:

    python3 dev_scripts/map_graph.py area Blackthorn          # tudo que tem em Blackthorn
    python3 dev_scripts/map_graph.py area Blackthorn --tipo casa
    python3 dev_scripts/map_graph.py info BlackthornCity_House2
    python3 dev_scripts/map_graph.py caminho MAP_DARKRAI_INN_FINAL_ROOM
    python3 dev_scripts/map_graph.py buscar pokecenter
    python3 dev_scripts/map_graph.py inalcancaveis
    python3 dev_scripts/map_graph.py check [--strict]          # usado pelo make e pelo CI
    python3 dev_scripts/map_graph.py check --atualizar         # regrava a lista de referencia

Como o grafo e montado:
  - Nos: todo mapa de data/maps/*/map.json. "Na ROM" = grupo de
    map_groups.json que NAO esta em rom_excluded_groups.
  - Arestas: connections e warp_events do map.json, mais todo comando warp*/
    set*warp com destino fixo no scripts.inc do proprio mapa.
  - Raiz: o quarto do jogador (src/new_game.c) e as Hidden Grottos, que sao
    alcancadas por codigo C (src/hidden_grotto.c), nao por warp.
  - NAO entram: warps de data/scripts/*.inc (quase todos sao sobras do
    Emerald e fariam metade de Hoenn parecer visitavel), warps para
    MAP_DYNAMIC, e warps feitos em C. Um mapa so alcancado assim aparece como
    inalcancavel; se for de proposito, ele vai para a lista de referencia.
  - "Alcancavel" quer dizer ligado ao mundo. Nao diz se a historia libera a
    porta: flags e vars nao sao consideradas.

A lista de referencia (docs/MAPAS_INALCANCAVEIS.txt) guarda os mapas da ROM
que ja sao inalcancaveis de proposito ou por heranca. O check so reclama do
que mudar em relacao a ela.
"""

import argparse
import glob
import json
import os
import re
import sys
import unicodedata
from collections import deque

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASELINE = 'docs/MAPAS_INALCANCAVEIS.txt'
START = 'MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F'
OUTDOOR = {'MAP_TYPE_CITY', 'MAP_TYPE_TOWN', 'MAP_TYPE_ROUTE', 'MAP_TYPE_OCEAN_ROUTE', 'MAP_TYPE_UNDERWATER'}
WARP_RX = re.compile(r'^\s*(warp\w*|set(?:dynamic|escape|hole|dive)?warp)\s+(MAP_\w+)', re.M)

TIPOS = [  # (categoria, regex no nome da pasta) - primeira que casar vence
    ('centro', r'PokemonCenter|PokeCenter|Pokecenter'),
    ('ginasio', r'Gym'),
    ('loja', r'Mart|DepartmentStore|Shop|Market|Boutique|Cafe'),
    ('laboratorio', r'Lab'),
    ('casa', r'House|Home|Apartment|Inn|Mansion|Hotel|Lodge|Cottage|Dorm|Bedroom|Room\d'),
    ('porto', r'Port|Harbor|Dock|Ferry|SSAqua|Ship'),
    ('portao', r'Gate'),
    ('torre', r'Tower|Pillar|Lighthouse|Pyramid'),
]


def norm(s):
    s = unicodedata.normalize('NFKD', s).encode('ascii', 'ignore').decode().lower()
    s = re.sub(r'^map_', '', s)
    s = re.sub(r'^mapsec_', '', s)
    return re.sub(r'[^a-z0-9]', '', s)


class Graph:
    def __init__(self):
        g = json.load(open('data/maps/map_groups.json'))
        excluded = set(g.get('rom_excluded_groups') or [])
        self.group_of = {}
        for grp in g['group_order']:
            for folder in g.get(grp, []):
                self.group_of[folder] = grp
        self.in_rom = {f for f, grp in self.group_of.items() if grp not in excluded}
        sizes = {l['id']: (l.get('width'), l.get('height'))
                 for l in json.load(open('data/layouts/layouts.json'))['layouts'] if 'id' in l}
        self.maps = {}      # MAP_ID -> dict
        self.by_folder = {}
        for path in sorted(glob.glob('data/maps/*/map.json')):
            folder = path.split('/')[2]
            j = json.load(open(path))
            mid = j['id']
            m = dict(id=mid, folder=folder, type=j.get('map_type', ''), mapsec=j.get('region_map_section', ''),
                     size=sizes.get(j.get('layout'), (None, None)), objects=j.get('object_events') or [],
                     warps=[], connections=[c['map'] for c in (j.get('connections') or [])],
                     script_warps=set(), rom=folder in self.in_rom)
            for i, w in enumerate(j.get('warp_events') or []):
                m['warps'].append(dict(i=i, x=w['x'], y=w['y'], dest=w['dest_map']))
            sp = 'data/maps/%s/scripts.inc' % folder
            m['script_lines'] = 0
            if os.path.exists(sp):
                txt = open(sp).read()
                m['script_warps'] = {d for _, d in WARP_RX.findall(txt)}
                m['script_lines'] = txt.count('\n')
            self.maps[mid] = m
            self.by_folder[folder] = mid
        self._shared_script_warps()
        grotto = open('src/hidden_grotto.c').read() if os.path.exists('src/hidden_grotto.c') else ''
        self.roots = [START] + sorted(set(re.findall(r'MAP_GROUP\((MAP_HIDDEN_GROTTO_(?!UNUSED)\w+)\)', grotto)))
        self.incoming = {}
        for mid, m in self.maps.items():
            for d in self.out(mid):
                self.incoming.setdefault(d, set()).add(mid)
        self._bfs()

    def _shared_script_warps(self):
        """Warp feito num script de OUTRO arquivo (data/scripts/*.inc, pasta so de
        script, ou label de outro mapa) conta para o mapa que chama esse label."""
        files = glob.glob('data/maps/*/scripts.inc') + glob.glob('data/scripts/*.inc')
        owner, fwarps, frefs = {}, {}, {}
        tok = re.compile(r'\b([A-Za-z]\w*_\w+)\b')
        for f in files:
            txt = open(f).read()
            for lab in re.findall(r'^(\w+)::?', txt, re.M): owner.setdefault(lab, f)
            fwarps[f] = {d for _, d in WARP_RX.findall(txt)}
            frefs[f] = set(tok.findall(txt))
        calls = {f: {owner[t] for t in refs if t in owner and owner[t] != f} for f, refs in frefs.items()}
        for mid, m in self.maps.items():
            f = 'data/maps/%s/scripts.inc' % m['folder']
            if f not in calls: continue
            seen, stack = {f}, list(calls[f])
            while stack:
                g = stack.pop()
                if g in seen: continue
                seen.add(g)
                # outro MAPA com map.json nao empresta seus warps (eles ja sao arestas dele)
                if g.startswith('data/maps/') and g.split('/')[2] in self.by_folder: continue
                m['script_warps'] |= fwarps.get(g, set())
                stack.extend(calls.get(g, ()))

    def out(self, mid):
        m = self.maps.get(mid)
        if not m: return set()
        return {w['dest'] for w in m['warps']} | set(m['connections']) | m['script_warps']

    def _bfs(self):
        # Primeiro a partir do quarto do jogador (caminhos legiveis); depois as
        # Hidden Grottos, que so entram por codigo C, para o que sobrou.
        self.parent = {}
        for roots in ([self.roots[0]], self.roots[1:]):
            q = deque()
            for r in roots:
                if r in self.maps and r not in self.parent:
                    self.parent[r] = None; q.append(r)
            while q:
                cur = q.popleft()
                for n in sorted(self.out(cur)):
                    if n in self.maps and n not in self.parent and self.maps[n]['rom']:
                        self.parent[n] = cur; q.append(n)

    def reachable(self, mid):
        return mid in self.parent

    def path(self, mid):
        if mid not in self.parent: return None
        out = []
        while mid: out.append(mid); mid = self.parent[mid]
        return list(reversed(out))

    def status(self, mid):
        m = self.maps[mid]
        if not m['rom']: return 'fora da ROM'
        return 'alcancavel' if self.reachable(mid) else 'INALCANCAVEL'

    def resolve(self, name):
        """Nome livre -> lista de MAP_IDs (pasta, MAP_ID ou MAPSEC)."""
        n = norm(name)
        exact = [mid for mid, m in self.maps.items() if n in (norm(m['folder']), norm(mid))]
        if exact: return exact
        sec = [mid for mid, m in self.maps.items() if norm(m['mapsec']) == n or norm(m['mapsec']) in (n + 'city', n + 'town')]
        if sec: return sec
        pre = [mid for mid, m in self.maps.items() if norm(m['folder']).startswith(n)]
        if pre: return pre
        return [mid for mid, m in self.maps.items() if n in norm(m['folder'])]


def tipo(m):
    for t, rx in TIPOS:
        if re.search(rx, m['folder']): return t
    return {'MAP_TYPE_UNDERGROUND': 'caverna', 'MAP_TYPE_SECRET_BASE': 'base secreta'}.get(m['type'], 'outro')


def nome(m):
    return m['folder']


def tam(m):
    w, h = m['size']
    return '%sx%s' % (w, h) if w else '?'


# ---------------------------------------------------------------- comandos
def cmd_area(G, args):
    cands = G.resolve(args.nome)
    if not cands:
        print('Nada encontrado para "%s". Tente: map_graph.py buscar %s' % (args.nome, args.nome)); return 1
    secs = {G.maps[c]['mapsec'] for c in cands}
    seeds = [c for c in cands if G.maps[c]['type'] in OUTDOOR]
    if not seeds:
        seeds = [mid for mid, m in G.maps.items() if m['mapsec'] in secs and m['type'] in OUTDOOR] or cands
    secs |= {G.maps[s]['mapsec'] for s in seeds}
    found = {}   # mid -> (parent, warp, depth)
    q = deque((s, 0) for s in seeds)
    seen = set(seeds)
    while q:
        cur, depth = q.popleft()
        for w in G.maps[cur]['warps']:
            d = w['dest']
            if d not in G.maps or d in seen: continue
            dm = G.maps[d]
            if dm['type'] in OUTDOOR: continue
            seen.add(d)
            other = dm['mapsec'] not in secs
            found[d] = (cur, w, depth + 1, other)
            if not other: q.append((d, depth + 1))
    loose = [mid for mid, m in G.maps.items() if m['mapsec'] in secs and mid not in found and mid not in seeds]

    print('Área: %s  (MAPSEC: %s)' % (', '.join(nome(G.maps[s]) for s in seeds), ', '.join(sorted(secs))))
    for s in seeds:
        m = G.maps[s]
        print('  %s  %s  %s  %d objetos  %s' % (nome(m), m['type'].replace('MAP_TYPE_', '').lower(), tam(m), len(m['objects']), G.status(s)))
    rows = []
    for d, (par, w, depth, other) in found.items():
        m = G.maps[d]
        t = 'outra área' if other else tipo(m)
        if args.tipo and args.tipo != 'todos' and t != args.tipo: continue
        porta = '(%d,%d) em %s' % (w['x'], w['y'], nome(G.maps[par]))
        rows.append((depth, par != seeds[0], t, nome(m), porta, tam(m), len(m['objects']), m['script_lines'], G.status(d)))
    rows.sort(key=lambda r: (r[0], r[2], r[3]))
    if rows:
        print('\nPortas a partir da área (%d):' % len(rows))
        print('  %-12s %-38s %-34s %-7s %-4s %-6s %s' % ('tipo', 'mapa', 'porta', 'tam', 'obj', 'script', 'estado'))
        for depth, _, t, n, porta, sz, nobj, sl, st in rows:
            print('  %-12s %-38s %-34s %-7s %-4d %-6d %s' % (t, ('  ' * (depth - 1)) + n, porta, sz, nobj, sl, st))
    if loose and (not args.tipo or args.tipo == 'todos'):
        print('\nMesma MAPSEC, mas sem porta a partir da área (%d):' % len(loose))
        for mid in sorted(loose, key=lambda x: G.maps[x]['folder']):
            m = G.maps[mid]
            viaq = sorted(nome(G.maps[i]) for i in G.incoming.get(mid, ()) if i in G.maps)
            print('  %-12s %-38s %-7s %-4d via: %s  [%s]' % (tipo(m), nome(m), tam(m), len(m['objects']),
                                                          ', '.join(viaq) or '—', G.status(mid)))
    return 0


def cmd_info(G, args):
    cands = G.resolve(args.mapa)
    if not cands: print('Nada encontrado.'); return 1
    if len(cands) > 1 and not args.todos:
        print('Vários mapas batem; seja mais específico ou use --todos:')
        for c in sorted(cands): print('  ', G.maps[c]['folder'])
        return 1
    for mid in cands:
        m = G.maps[mid]
        print('%s  (%s)' % (m['folder'], mid))
        print('  tipo: %s / %s   MAPSEC: %s   tamanho: %s   objetos: %d   script: %d linhas' % (
            tipo(m), m['type'].replace('MAP_TYPE_', '').lower(), m['mapsec'], tam(m), len(m['objects']), m['script_lines']))
        print('  grupo: %s   estado: %s' % (G.group_of.get(m['folder'], '?'), G.status(mid)))
        p = G.path(mid)
        if p: print('  caminho: ' + ' -> '.join(G.maps[x]['folder'] for x in p))
        print('  entra por:')
        for src in sorted(G.incoming.get(mid, ())):
            if src not in G.maps: continue
            sm = G.maps[src]
            how = ['porta (%d,%d)' % (w['x'], w['y']) for w in sm['warps'] if w['dest'] == mid]
            if mid in sm['connections']: how.append('conexão')
            if mid in sm['script_warps']: how.append('warp de script')
            print('    %-38s %-30s [%s]' % (sm['folder'], ', '.join(how), G.status(src)))
        print('  sai para:')
        for w in m['warps']:
            dn = G.maps[w['dest']]['folder'] if w['dest'] in G.maps else w['dest']
            print('    porta (%d,%d) -> %s' % (w['x'], w['y'], dn))
        for c in m['connections']:
            print('    conexão -> %s' % (G.maps[c]['folder'] if c in G.maps else c))
        for d in sorted(m['script_warps']):
            print('    warp de script -> %s' % (G.maps[d]['folder'] if d in G.maps else d))
    return 0


def cmd_caminho(G, args):
    cands = G.resolve(args.mapa)
    for mid in cands[:10]:
        p = G.path(mid)
        m = G.maps[mid]
        if p: print('%s: %s' % (m['folder'], ' -> '.join(G.maps[x]['folder'] for x in p)))
        else: print('%s: sem caminho (%s)' % (m['folder'], G.status(mid)))
    return 0 if cands else 1


def cmd_buscar(G, args):
    n = norm(args.texto)
    hits = sorted((m['folder'], mid) for mid, m in G.maps.items()
                  if n in norm(m['folder']) or n in norm(m['mapsec']) or n in norm(tipo(m)))
    for f, mid in hits:
        m = G.maps[mid]
        print('%-40s %-12s %-26s %s' % (f, tipo(m), m['mapsec'].replace('MAPSEC_', ''), G.status(mid)))
    print('%d mapa(s)' % len(hits))
    return 0


def unreachable(G):
    return sorted(m['folder'] for mid, m in G.maps.items() if m['rom'] and not G.reachable(mid))


def cmd_inalcancaveis(G, args):
    for f in unreachable(G):
        if args.filtro and norm(args.filtro) not in norm(f): continue
        m = G.maps[G.by_folder[f]]
        viaq = sorted(G.maps[i]['folder'] for i in G.incoming.get(m['id'], ()) if i in G.maps)
        print('%-40s %-12s via: %s' % (f, tipo(m), ', '.join(viaq) or '— (ninguém leva até aqui)'))
    return 0


def cmd_check(G, args):
    now = unreachable(G)
    if args.atualizar:
        with open(BASELINE, 'w') as fh:
            fh.write('# Mapas da ROM que o grafo de ligacoes nao alcanca (dev_scripts/map_graph.py).\n'
                     '# Gerado; nao editar a mao. Regenerar com: python3 dev_scripts/map_graph.py check --atualizar\n'
                     '# Mapa novo que aparecer aqui no diff = mapa que ninguem liga ao mundo.\n')
            for f in now: fh.write(f + '\n')
        print('%s regravado: %d mapas inalcançáveis de %d na ROM.' % (BASELINE, len(now), len(G.in_rom)))
        return 0
    base = set()
    if os.path.exists(BASELINE):
        base = {l.strip() for l in open(BASELINE) if l.strip() and not l.startswith('#')}
    new = [f for f in now if f not in base]
    fixed = sorted(f for f in base if f not in now)
    tag = 'map_graph'
    if not new and not fixed:
        print('%s: ok — %d mapas alcançáveis, nenhum mapa novo desligado.' % (tag, len(G.parent)))
        return 0
    if new:
        print('%s: AVISO — mapa(s) da ROM que ninguém alcança e não estão em %s:' % (tag, BASELINE))
        for f in new:
            m = G.maps[G.by_folder[f]]
            viaq = sorted(G.maps[i]['folder'] for i in G.incoming.get(m['id'], ()) if i in G.maps)
            print('  - %s  (entra por: %s)' % (f, ', '.join(viaq) or 'ninguém — falta a porta/conexão'))
        print('  Ligue o mapa ao mundo, ou, se for de propósito, rode: python3 dev_scripts/map_graph.py check --atualizar')
    if fixed:
        print('%s: mapa(s) que agora são alcançáveis (atualize a lista com --atualizar):' % tag)
        for f in fixed: print('  + %s' % f)
    return 1 if (args.strict and new) else 0


def main():
    os.chdir(ROOT)
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    a = sub.add_parser('area', help='tudo que tem numa cidade/rota: casas, ginásio, centro...')
    a.add_argument('nome'); a.add_argument('--tipo', help='casa, ginasio, centro, loja, laboratorio, caverna, porto, portao, torre, outro')
    i = sub.add_parser('info', help='detalhes de um mapa: quem leva até ele e para onde ele leva')
    i.add_argument('mapa'); i.add_argument('--todos', action='store_true')
    c = sub.add_parser('caminho', help='caminho a partir do quarto do jogador')
    c.add_argument('mapa')
    b = sub.add_parser('buscar', help='lista mapas por pedaço do nome, MAPSEC ou tipo')
    b.add_argument('texto')
    u = sub.add_parser('inalcancaveis', help='mapas da ROM que ninguém alcança')
    u.add_argument('--filtro')
    k = sub.add_parser('check', help='compara com a lista de referência (make/CI)')
    k.add_argument('--strict', action='store_true', help='sai com erro se houver mapa novo desligado')
    k.add_argument('--atualizar', action='store_true', help='regrava a lista de referência')
    args = ap.parse_args()
    G = Graph()
    return {'area': cmd_area, 'info': cmd_info, 'caminho': cmd_caminho, 'buscar': cmd_buscar,
            'inalcancaveis': cmd_inalcancaveis, 'check': cmd_check}[args.cmd](G, args)


if __name__ == '__main__':
    sys.exit(main())
