#!/usr/bin/env python3
"""Dump da grade de colisao de um mapa, com objetos e warps sobrepostos.

Uso:
    python3 .claude/skills/encenar-cutscene/dump_mapa.py CianwoodCity
    python3 .claude/skills/encenar-cutscene/dump_mapa.py CianwoodCity 12 21 43 52

Os quatro numeros opcionais recortam a regiao (x0 x1 y0 y1), inclusivos.
Sem eles imprime o mapa inteiro.

Legenda:
    .  chao livre          #  colisao (parede/movel/vazio)
    0-9 A-Z  objeto (marcador na lista abaixo, sobre o tile dele)
    W  warp

Formato do map.bin (include/global.fieldmap.h): u16 little-endian por bloco,
bits 0-10 = metatile id, bit 11 = COLISAO (1 bit!), bits 12-15 = elevacao.
Decodificar colisao como 2 bits a partir do bit 10 e o erro classico: o bit
alto do metatile vaza e o chao vira parede fantasma.
"""

import json
import os
import struct
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))


def carregar_layout(nome_mapa):
    caminho = os.path.join(ROOT, "data", "maps", nome_mapa, "map.json")
    if not os.path.exists(caminho):
        sys.exit(f"nao achei {caminho}")
    mapa = json.load(open(caminho))

    layouts = json.load(open(os.path.join(ROOT, "data", "layouts", "layouts.json")))
    layout = next(
        (l for l in layouts["layouts"] if l["id"] == mapa["layout"]),
        None,
    )
    if layout is None:
        sys.exit(f"layout {mapa['layout']} nao encontrado em layouts.json")

    w, h = layout["width"], layout["height"]
    bin_path = os.path.join(ROOT, layout["blockdata_filepath"]) if layout.get(
        "blockdata_filepath"
    ) else os.path.join(ROOT, "data", "layouts", layout["name"].replace("_Layout", ""), "map.bin")
    blocos = struct.unpack(f"<{w * h}H", open(bin_path, "rb").read())
    return mapa, w, h, blocos


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    nome = sys.argv[1]
    mapa, w, h, blocos = carregar_layout(nome)

    if len(sys.argv) >= 6:
        x0, x1, y0, y1 = (int(v) for v in sys.argv[2:6])
    else:
        x0, x1, y0, y1 = 0, w - 1, 0, h - 1
    x0, x1 = max(0, x0), min(w - 1, x1)
    y0, y1 = max(0, y0), min(h - 1, y1)

    def colisao(x, y):
        return (blocos[y * w + x] >> 11) & 1

    # base36 para nao repetir marcador em mapa com mais de 10 objetos
    alfabeto = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"

    def marcador(i):
        return alfabeto[i] if i < len(alfabeto) else "?"

    objetos = mapa.get("object_events", [])
    em_tile = {}
    for i, o in enumerate(objetos):
        em_tile[(o["x"], o["y"])] = marcador(i)
    for wp in mapa.get("warp_events", []):
        em_tile.setdefault((wp["x"], wp["y"]), "W")

    print(f"{nome}  ({w}x{h})   x={x0}..{x1}  y={y0}..{y1}")
    print()
    print("     " + "".join(f"{x % 10:2}" for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        linha = ""
        for x in range(x0, x1 + 1):
            marca = em_tile.get((x, y))
            linha += f" {marca}" if marca else (" #" if colisao(x, y) else " .")
        print(f"y={y:3} {linha}")

    print()
    print("objetos (marcador: local_id  grafico  (x,y)  flag):")
    for i, o in enumerate(objetos):
        lid = o.get("local_id") or f"<sem nome, local id {i + 1}>"
        print(
            f"  {marcador(i)}: {lid}  {o['graphics_id']}  "
            f"({o['x']},{o['y']})  flag={o.get('flag', '0')}"
        )

    warps = mapa.get("warp_events", [])
    if warps:
        print()
        print("warps (W): destino  (x,y)")
        for wp in warps:
            print(f"     {wp['dest_map']}#{wp['dest_warp_id']}  ({wp['x']},{wp['y']})")
        print()
        print("  Para saber ONDE o jogador nasce ao vir de outro mapa, procure o")
        print("  warp_def deste mapa cujo indice == dest_warp_id do warp de origem.")


if __name__ == "__main__":
    main()
