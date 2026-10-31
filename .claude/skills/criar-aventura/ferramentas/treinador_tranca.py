#!/usr/bin/env python3
"""Acha treinador (ou NPC parado) que tranca caminho: com ele como bloqueio, alguma parte do mapa (warp, item,
NPC) deixa de ser alcancavel a partir das entradas. Treinador vencido NAO sai do lugar, entao isso prende o
jogador. Uso: python3 treinador_tranca.py Mapa [Mapa...]   (rodar da raiz do repo)"""
import collections, json, sys
sys.path.insert(0, '.claude/qa')
import rota


def alcance(mapa, extra_block, so_de=None):
    w, h, block, edges = rota.load(mapa, set())
    j = json.load(open(f'data/maps/{mapa}/map.json'))
    ini = [(p['x'], p['y']) for p in j['warp_events']] if so_de is None else [so_de]
    seen = set(p for p in ini if p not in extra_block)
    q = collections.deque(seen)
    while q:
        c = q.popleft()
        for d in rota.DIRS.values():
            n = (c[0] + d[0], c[1] + d[1])
            if 0 <= n[0] < w and 0 <= n[1] < h and n not in block and n not in extra_block and n not in seen \
                    and frozenset({c, n}) not in edges:
                seen.add(n); q.append(n)
    return seen, j


for mapa in sys.argv[1:]:
    _, j = alcance(mapa, set())
    alvos = {(o['x'], o['y']): o['local_id'] for o in j['object_events']}
    alvos.update({(p['x'], p['y']): 'warp' for p in j['warp_events']})
    viz = lambda c, S: any((c[0] + dx, c[1] + dy) in S for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0), (0, 0)))
    for o in j['object_events']:
        if o.get('trainer_type', 'TRAINER_TYPE_NONE') == 'TRAINER_TYPE_NONE':
            continue
        p = (o['x'], o['y'])
        for wp in j['warp_events']:          # o jogador entra por UMA porta: tem que alcancar o resto dali
            s0 = (wp['x'], wp['y'])
            base, _ = alcance(mapa, set(), s0)
            sem, _ = alcance(mapa, {p}, s0)
            perdidos = [n for c, n in alvos.items() if c != p and viz(c, base) and not viz(c, sem)]
            if perdidos:
                print(f'{mapa}: {o["local_id"]} em {p} tranca (entrando por {s0}) -> {", ".join(sorted(set(perdidos))[:6])}')
                break
