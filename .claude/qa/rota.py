#!/usr/bin/env python3
"""Calcula o caminho a pe entre dois pontos de um mapa e imprime comandos do driver.

    rota.py <Mapa> X0 Y0 X1 Y1 [--face DIR]

Usa a colisao do map.bin (bit 11, MAPGRID_COLLISION_MASK de global.fieldmap.h:
o ID do metatile tem 11 bits, nunca o layout de 10 bits do pokeemerald) e trata
todo object_event como bloqueio (NPC parado, arvore de berry...). O destino pode ser um tile
bloqueado: entao o caminho para no vizinho e vira o rosto para ele (bom para
"falar com" / "olhar para" uma arvore). Agua, cachoeira e ledges contam como bloqueio (sem Surf, sem pular).
Saida: uma linha com os comandos separados por ';' (para o q.py).
"""
import json, re, struct, sys
from collections import deque
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]


# include/global.fieldmap.h e include/fieldmap.h (medir, nunca supor)
METATILE_ID_MASK, COLLISION_MASK, NUM_PRIMARY = 0x07FF, 0x0800, 1024


def load(mapname, objs=None):
    """objs: posicoes dos objetos VIVOS (ir.py le da RAM). Sem isso, todo
    object_event do map.json bloqueia, inclusive os escondidos por flag."""
    m = json.load(open(REPO / f"data/maps/{mapname}/map.json"))
    layouts = json.load(open(REPO / "data/layouts/layouts.json"))["layouts"]
    lay = next(l for l in layouts if l["id"] == m["layout"])
    raw = open(REPO / lay["blockdata_filepath"], "rb").read()
    w, h = lay["width"], lay["height"]
    cells = struct.unpack(f"<{w*h}H", raw)
    block = {(x, y) for y in range(h) for x in range(w) if cells[y * w + x] & COLLISION_MASK}
    if objs is None:
        objs = {(o["x"], o["y"]) for o in m.get("object_events", [])}
    # Bordas direcionais (MB_IMPASSABLE_WEST etc., ex.: borda de tapete): a
    # borda daquele lado do tile nao se cruza em nenhum sentido.
    edges = set()
    attrs = [tileset_attrs(lay["primary_tileset"]), tileset_attrs(lay["secondary_tileset"])]
    names = behavior_names()
    for y in range(h):
        for x in range(w):
            mid = cells[y * w + x] & METATILE_ID_MASK
            a = attrs[0] if mid < NUM_PRIMARY else attrs[1]
            i = mid if mid < NUM_PRIMARY else mid - NUM_PRIMARY
            if a is None or i * 2 + 2 > len(a):
                continue
            name = names[struct.unpack_from("<H", a, i * 2)[0] & 0xFF]
            # agua (so com Surf), cachoeira e ledge (pulo de mao unica): fora da rota a pe
            if any(k in name for k in ("WATER", "POND", "OCEAN", "WATERFALL", "JUMP_", "DIVE")):
                block.add((x, y))
            for side in ("NORTH", "SOUTH", "EAST", "WEST"):
                if name.startswith("MB_IMPASSABLE_") and side in name.replace("MB_IMPASSABLE_", ""):
                    d = {"NORTH": (0, -1), "SOUTH": (0, 1), "EAST": (1, 0), "WEST": (-1, 0)}[side]
                    edges.add(frozenset({(x, y), (x + d[0], y + d[1])}))
    return w, h, block | objs, edges


def tileset_attrs(sym):
    src = open(REPO / "src/data/tilesets/metatiles.h").read()
    m = re.search(r"gMetatileAttributes_%s\[\] = INCBIN_U16\(\"([^\"]+)\"" % sym.replace("gTileset_", ""), src)
    return open(REPO / m.group(1), "rb").read() if m else None


def behavior_names():
    src = open(REPO / "include/constants/metatile_behaviors.h").read()
    body = src[src.index("{") + 1:src.index("}")]
    return re.findall(r"^\s*(MB_\w+)", body, re.M)


DIRS = {"UP": (0, -1), "DOWN": (0, 1), "LEFT": (-1, 0), "RIGHT": (1, 0)}


def path(mapname, a, b, objs=None):
    w, h, block, edges = load(mapname, objs)
    goals = {b} if b not in block else {(b[0] - d[0], b[1] - d[1]) for d in DIRS.values()}
    prev = {a: None}
    q = deque([a])
    while q:
        c = q.popleft()
        if c in goals:
            break
        for name, (dx, dy) in DIRS.items():
            n = (c[0] + dx, c[1] + dy)
            if 0 <= n[0] < w and 0 <= n[1] < h and n not in block and n not in prev \
                    and frozenset({c, n}) not in edges:
                prev[n] = (c, name)
                q.append(n)
    else:
        sys.exit("sem caminho")
    steps = []
    while prev[c]:
        c, d = prev[c]
        steps.append(d)
    steps.reverse()
    end = a
    for s in steps:
        end = (end[0] + DIRS[s][0], end[1] + DIRS[s][1])
    face = None
    if b != end:
        face = next(n for n, d in DIRS.items() if (end[0] + d[0], end[1] + d[1]) == b)
    return steps, face


if __name__ == "__main__":
    mp, x0, y0, x1, y1 = sys.argv[1], *map(int, sys.argv[2:6])
    steps, face = path(mp, (x0, y0), (x1, y1))
    # Um passo por comando: segurar 16 quadros = 1 tile andando (24 quando vira).
    cmds, last = [], None
    for s in steps:
        cmds.append(f"press {s} {16 if s == last else 24} 2")
        last = s
    if face and face != last:
        cmds.append(f"press {face} 6 12")
    print("; ".join(cmds) if cmds else "wait 1")
