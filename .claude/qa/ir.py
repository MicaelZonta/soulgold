#!/usr/bin/env python3
"""Leva o jogador ate (X,Y) no mapa atual, com realimentacao pela RAM.

    ir.py <Mapa> X Y        # Mapa = pasta em data/maps (ex.: Route30)

Se (X,Y) for bloqueado (NPC, arvore, cova), para ao lado e vira o rosto para
ele. A cada passo le gSaveBlock1Ptr->pos; se nao andou (a virada come o
aperto, ou um NPC passou na frente), tenta de novo e recalcula a rota.
"""
import os, struct, subprocess, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import q
from rota import path, DIRS

REPO = Path(__file__).resolve().parents[2]


def sym(name):
    out = subprocess.run(["arm-none-eabi-nm", str(REPO / "Soulgold.elf")], capture_output=True, text=True).stdout
    for line in out.splitlines():
        p = line.split()
        if len(p) == 3 and p[2] == name:
            return int(p[0], 16)
    raise KeyError(name)


SB1 = None


def pos():
    global SB1
    if SB1 is None:
        SB1 = sym("gSaveBlock1Ptr")
    base = int(q.run([f"r32 {SB1}"]).split("=")[1])
    h = q.run([f"range {base} 4"]).split("=")[1]
    return struct.unpack("<hh", bytes.fromhex(h))


def live_objects():
    """Posicoes dos gObjectEvents ativos, menos jogador (255) e follower (254):
    so o que existe de verdade agora bloqueia a rota (NPC escondido por flag
    nao). Layout de struct ObjectEvent como em objetos.py."""
    import re
    count = int(re.search(r"#define OBJECT_EVENTS_COUNT (\d+)",
        (REPO / "include/constants/global.h").read_text()).group(1))
    size, off_local, off_coords = 36, 8, 16
    raw = bytes.fromhex(q.run([f"range {sym('gObjectEvents')} {count * size}"]).split("=")[1])
    objs = set()
    for i in range(count):
        o = raw[i * size:(i + 1) * size]
        if o[0] & 1 and o[off_local] not in (254, 255):
            x, y = struct.unpack_from("<hh", o, off_coords)
            objs.add((x - 7, y - 7))
    return objs


def go(mapname, target):
    q.run(["press B 6 24"] * 8)   # fecha caixa de texto que tenha ficado aberta
    for _ in range(200):
        cur = pos()
        steps, face = path(mapname, cur, target, live_objects())
        if not steps:
            if face:
                q.run([f"press {face} 10 12"])   # < 8 quadros nao chega a virar
            return cur
        q.run([f"press {steps[0]} 14 4"])
        if pos() == cur:            # so virou: aperta de novo
            q.run([f"press {steps[0]} 14 4"])
    sys.exit("nao chegou")


if __name__ == "__main__":
    print("pos", go(sys.argv[1], (int(sys.argv[2]), int(sys.argv[3]))))
