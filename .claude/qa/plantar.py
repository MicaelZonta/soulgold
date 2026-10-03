#!/usr/bin/env python3
"""Planta uma berry numa cova: anda ate ela, abre o "plantar?", escolhe a berry
na bolsa pela posicao lida da RAM e fecha as falas.

    plantar.py Mapa X Y ITEM_SITRUS_BERRY [--prefixo /tmp/qa/ev/Tnn]

O cursor do bolso e lembrado entre aberturas: por isso sobe ate o topo (UP
nao da a volta) antes de descer ate a berry. Sai com erro se a berry nao esta
na bolsa ou se a cova nao perguntou "plantar?".
"""
import argparse, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import q, ir, bolsa
from conversa import classify

POCKET_BERRIES = 6   # enum Pocket (include/constants/item.h)


def plant(mapname, x, y, item, prefix=None):
    names = {v: k for k, v in bolsa.item_names().items()}
    want = names[item]
    order = list(bolsa.read("berries").keys())
    if want not in order:
        sys.exit(f"{item} nao esta na bolsa")
    ir.go(mapname, (x, y))
    shot = (prefix or "/tmp/qa/plantar") + "_pergunta.png"
    q.run(["press A 6 10", "wait 70", f"shot {shot}"])
    if classify(shot) != "yesno":
        sys.exit("a cova nao perguntou 'plantar?' (ocupada? sem berry?)")
    q.run(["wait 20", "press A 6 70"])                       # Yes -> bolsa
    # A lista da volta (UP no topo vai para "Close Bag") e lembra o cursor:
    # le gBagPosition.cursorPosition/scrollPosition[POCKET_BERRIES] e anda a diferenca.
    bp = ir.sym("gBagPosition")
    cur = int(q.run([f"r16 {bp + 8 + 2 * POCKET_BERRIES}"]).split("=")[1]) \
        + int(q.run([f"r16 {bp + 24 + 2 * POCKET_BERRIES}"]).split("=")[1])
    d = order.index(want) - cur
    q.run(["wait 1"] + [f"press {'DOWN' if d > 0 else 'UP'} 4 8"] * abs(d))
    q.run([f"shot {(prefix or '/tmp/qa/plantar')}_bolsa.png", "press A 6 30"])
    q.run(["press A 6 60"] * 3 + ["press B 6 24"] * 6)       # falas "planted"
    return True


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("mapa"); ap.add_argument("x", type=int); ap.add_argument("y", type=int)
    ap.add_argument("item"); ap.add_argument("--prefixo")
    a = ap.parse_args()
    plant(a.mapa, a.x, a.y, a.item, a.prefixo)
    print("plantado")
