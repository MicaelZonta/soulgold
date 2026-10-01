#!/usr/bin/env python3
"""Mede, por mapa, o pior caso de objetos dentro da janela de spawn.

TrySpawnObjectEvents (src/event_object_movement.c) so carrega objetos numa
janela de 20 x 17 tiles em volta do jogador: x em [P-9, P+10], y em [P-7, P+9].
O limite OBJECT_EVENTS_COUNT vale para essa janela (jogador e follower inclusos),
nao para o mapa inteiro.

Para cada mapa, desliza a janela e reporta a posicao com mais objetos:
  janela      objetos dentro da janela (com ou sem flag)
  semFlag     desses, quantos nao tem flag de ocultacao (aparecem todos juntos)
  especies    graphics_id OBJ_EVENT_GFX_SPECIES distintos (1 paleta + 1 folha de VRAM cada)
  paletasNPC  paletteTag distintos dos NPCs comuns
  x y         centro da janela (coordenada do jogador no map.json)

Uso:
  python3 dev_scripts/limites_janela_objetos.py            # top 30
  python3 dev_scripts/limites_janela_objetos.py --limite 23 # conta mapas acima de N
  python3 dev_scripts/limites_janela_objetos.py --mapa NewBarkTown
"""
import argparse
import glob
import json
import re

GFX_PTRS = 'src/data/object_events/object_event_graphics_info_pointers.h'
GFX_INFO = 'src/data/object_events/object_event_graphics_info.h'


def load_palettes():
    ptr = open(GFX_PTRS).read()
    gfx2info = dict(re.findall(r'\[(OBJ_EVENT_GFX_\w+)\]\s*=\s*&(\w+)', ptr))
    info_pal = {}
    text = open(GFX_INFO).read()
    for m in re.finditer(r'ObjectEventGraphicsInfo (\w+) = \{(.*?)\};', text, re.S):
        pal = re.search(r'\.paletteTag\s*=\s*(\w+)', m.group(2))
        info_pal[m.group(1)] = pal.group(1) if pal else '?'
    return {g: info_pal.get(i, '?') for g, i in gfx2info.items()}


def worst_window(objs, gfx_pal):
    best = (0, 0, 0, 0, 0, 0)
    xs = [o['x'] for o in objs]
    ys = [o['y'] for o in objs]
    for px in range(min(xs) - 10, max(xs) + 10):
        for py in range(min(ys) - 9, max(ys) + 8):
            w = [o for o in objs if px - 9 <= o['x'] <= px + 10 and py - 7 <= o['y'] <= py + 9]
            if len(w) <= best[0]:
                continue
            species = {o['graphics_id'] for o in w if 'SPECIES' in o['graphics_id']}
            pals = {gfx_pal.get(o['graphics_id'], '?') for o in w if 'SPECIES' not in o['graphics_id']}
            no_flag = sum(1 for o in w if o.get('flag', '0') in ('0', ''))
            best = (len(w), no_flag, len(species), len(pals), px, py)
    return best


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--limite', type=int, default=15,
                    help='objetos alem do jogador (OBJECT_EVENTS_COUNT - 1); padrao 15')
    ap.add_argument('--mapa', help='so este mapa')
    ap.add_argument('--top', type=int, default=30)
    args = ap.parse_args()

    gfx_pal = load_palettes()
    rows = []
    for mj in sorted(glob.glob('data/maps/*/map.json')):
        d = json.load(open(mj))
        if args.mapa and d['name'] != args.mapa:
            continue
        objs = [o for o in d.get('object_events', [])
                if o.get('type', 'object') == 'object'
                and 'LIGHT_SPRITE' not in o.get('graphics_id', '')]
        if objs:
            rows.append(worst_window(objs, gfx_pal) + (d['name'],))

    rows.sort(reverse=True)
    print('janela semFlag especies paletasNPC x y mapa')
    for r in rows[:args.top]:
        print(*r)
    print(f'mapas com janela > {args.limite}: {sum(1 for r in rows if r[0] > args.limite)}'
          f' | sem flag > {args.limite}: {sum(1 for r in rows if r[1] > args.limite)}')


if __name__ == '__main__':
    main()
