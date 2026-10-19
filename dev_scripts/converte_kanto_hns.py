#!/usr/bin/env python3
"""Converte dados de mapa/tileset do pokehns (HnS 2.0.6) para o formato do
SoulGold (Fase 1 do plano em .claude/pokehns/ANALISE_POKEHNS_2.0.6.md).

Diferenças de formato (medidas, ver K3 da análise):
  - map.bin do P: metatile 10 bits (0x03FF), colisão 2 bits (0x0C00).
    No S: metatile 11 bits (0x07FF), colisão 1 bit (0x0800).
  - NUM_METATILES_IN_PRIMARY: 640 no P, 1024 no S → ID >= 640 ganha +384.
  - metatiles.bin do P: 16 B/metatile (dual layer). No S: 24 B (triple),
    expandido conforme o layer type dos atributos (bits 12-15), que são
    zerados no resultado.
  - Byte de behavior dos atributos: 4 IDs mudam de número e 7 IDs-lixo
    viram MB_NORMAL (0), conforme .claude/pokehns/behavior_remap.json.

Uso:
  python3 dev_scripts/converte_kanto_hns.py layout  --src <dir P com map.bin>  --dst <dir S>
  python3 dev_scripts/converte_kanto_hns.py tileset --src <dir P do tileset>   --dst <dir S>

Nunca roda in-place: --src e --dst precisam ser diretórios diferentes, e
--src tipicamente aponta para dentro de .filetransfer/pokehns-*/.
"""
import argparse
import json
import os
import shutil
import struct
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REMAP_JSON = os.path.join(REPO, ".claude", "pokehns", "behavior_remap.json")

OLD_METATILE_MASK = 0x03FF
OLD_COLLISION_MASK = 0x0C00
OLD_ELEVATION_SHIFT = 12
OLD_METATILES_IN_PRIMARY = 640
NEW_METATILES_IN_PRIMARY = 1024
METATILE_OFFSET = NEW_METATILES_IN_PRIMARY - OLD_METATILES_IN_PRIMARY  # 384

OLD_METATILE_BYTES = 16   # 8 tiles de 2 B
NEW_METATILE_BYTES = 24   # 12 tiles de 2 B
ATTR_LAYER_MASK = 0xF000
ATTR_LAYER_SHIFT = 12
ATTR_BEHAVIOR_MASK = 0x00FF


def load_behavior_map() -> dict[int, int]:
    """p_behavior -> s_behavior (só os que mudam)."""
    with open(REMAP_JSON) as f:
        remap = json.load(f)["remap"]
    out: dict[int, int] = {}
    for entry in remap.values():
        pid = entry["p_id"]
        if entry.get("sanitizar"):
            out[pid] = 0
        elif entry.get("action") == "novo" and not entry.get("identidade", True):
            out[pid] = entry["s_id_proposto"]
    return out


def convert_metatile_id(mid: int) -> int:
    return mid + METATILE_OFFSET if mid >= OLD_METATILES_IN_PRIMARY else mid


def convert_map_bin(src: str, dst: str) -> None:
    data = open(src, "rb").read()
    vals = struct.unpack(f"<{len(data)//2}H", data)
    out = []
    for v in vals:
        mid = convert_metatile_id(v & OLD_METATILE_MASK)
        collision = 1 if (v & OLD_COLLISION_MASK) else 0
        elevation = v >> OLD_ELEVATION_SHIFT
        out.append(mid | (collision << 11) | (elevation << 12))
    with open(dst, "wb") as f:
        f.write(struct.pack(f"<{len(out)}H", *out))


def convert_border_bin(src: str, dst: str) -> None:
    data = open(src, "rb").read()
    vals = struct.unpack(f"<{len(data)//2}H", data)
    out = [convert_metatile_id(v & OLD_METATILE_MASK) for v in vals]
    with open(dst, "wb") as f:
        f.write(struct.pack(f"<{len(out)}H", *out))


def cmd_layout(src_dir: str, dst_dir: str) -> None:
    os.makedirs(dst_dir, exist_ok=True)
    did = []
    for name in ("map.bin", "border.bin"):
        s = os.path.join(src_dir, name)
        if not os.path.exists(s):
            continue
        d = os.path.join(dst_dir, name)
        (convert_map_bin if name == "map.bin" else convert_border_bin)(s, d)
        did.append(name)
    if not did:
        sys.exit(f"[ERRO] nem map.bin nem border.bin em {src_dir}")
    print(f"[OK] layout {os.path.basename(dst_dir)}: {', '.join(did)} convertidos")


def cmd_tileset(src_dir: str, dst_dir: str) -> None:
    beh_map = load_behavior_map()
    mt_src = os.path.join(src_dir, "metatiles.bin")
    at_src = os.path.join(src_dir, "metatile_attributes.bin")
    for p in (mt_src, at_src):
        if not os.path.exists(p):
            sys.exit(f"[ERRO] falta {p}")

    at_data = open(at_src, "rb").read()
    if len(at_data) % 2:
        sys.exit(f"[ERRO] atributos com tamanho ímpar: {at_src}")
    attrs = struct.unpack(f"<{len(at_data)//2}H", at_data)

    mt_data = open(mt_src, "rb").read()
    n_meta = len(mt_data) // OLD_METATILE_BYTES
    if len(mt_data) % OLD_METATILE_BYTES or n_meta != len(attrs):
        sys.exit(
            f"[ERRO] {src_dir}: {n_meta} metatiles x {len(attrs)} atributos — "
            "não parece um tileset dual-layer do P (já convertido?)"
        )

    new_attrs = []
    remapped = 0
    for a in attrs:
        beh = a & ATTR_BEHAVIOR_MASK
        if beh in beh_map:
            a = (a & ~ATTR_BEHAVIOR_MASK) | beh_map[beh]
            remapped += 1
        new_attrs.append(a & ~ATTR_LAYER_MASK)  # zera layer bits, como no S

    new_meta = []
    for i in range(n_meta):
        tiles = struct.unpack(
            "<8H", mt_data[i * OLD_METATILE_BYTES:(i + 1) * OLD_METATILE_BYTES]
        )
        layer = (attrs[i] & ATTR_LAYER_MASK) >> ATTR_LAYER_SHIFT
        if layer == 0:        # middle/top -> bottom vazio
            new_meta += [0] * 4 + list(tiles)
        elif layer == 1:      # bottom/middle -> top vazio
            new_meta += list(tiles) + [0] * 4
        elif layer == 2:      # bottom/top -> middle vazio
            new_meta += list(tiles[:4]) + [0] * 4 + list(tiles[4:])
        else:
            new_meta += [0] * 12

    os.makedirs(dst_dir, exist_ok=True)
    with open(os.path.join(dst_dir, "metatiles.bin"), "wb") as f:
        f.write(struct.pack(f"<{len(new_meta)}H", *new_meta))
    with open(os.path.join(dst_dir, "metatile_attributes.bin"), "wb") as f:
        f.write(struct.pack(f"<{len(new_attrs)}H", *new_attrs))

    # arte e paletas vão junto, sem conversão
    copied = []
    for extra in os.listdir(src_dir):
        if extra in ("metatiles.bin", "metatile_attributes.bin"):
            continue
        s = os.path.join(src_dir, extra)
        d = os.path.join(dst_dir, extra)
        if os.path.isdir(s):
            shutil.copytree(s, d, dirs_exist_ok=True)
        else:
            shutil.copy2(s, d)
        copied.append(extra)
    print(
        f"[OK] tileset {os.path.basename(dst_dir)}: {n_meta} metatiles 16->24 B, "
        f"{remapped} behaviors remapeados, copiados: {', '.join(sorted(copied))}"
    )


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name in ("layout", "tileset"):
        p = sub.add_parser(name)
        p.add_argument("--src", required=True)
        p.add_argument("--dst", required=True)
    args = ap.parse_args()

    src = os.path.abspath(args.src)
    dst = os.path.abspath(args.dst)
    if src == dst:
        sys.exit("[ERRO] --src e --dst iguais: este conversor nunca roda in-place.")
    if not os.path.isdir(src):
        sys.exit(f"[ERRO] --src não é diretório: {src}")

    if args.cmd == "layout":
        cmd_layout(src, dst)
    else:
        cmd_tileset(src, dst)


if __name__ == "__main__":
    main()
