#!/usr/bin/env python3
"""Le um bolso da bolsa direto da RAM (itemId + quantidade decifrada).

    bolsa.py [berries|items|key]      # padrao: berries

Offsets de SaveBlock1/SaveBlock2 tirados com offsetof() compilado contra os
headers do jogo (ver SKILL.md, secao "offsets"). Se a struct mudar, refaca.
"""
import re, struct, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import q
from ir import sym

REPO = Path(__file__).resolve().parents[2]
POCKETS = {"berries": (3572, 70), "items": (1352, 150), "key": (2212, 50)}
OFF_ENC = 76   # SaveBlock2.encryptionKey


def item_names():
    """Percorre o enum de itens: valores explicitos, aliases e auto-incremento."""
    txt = open(REPO / "include/constants/items.h").read()
    names, vals, cur = {}, {"FIRST_BERRY_INDEX": 514}, -1
    for k, v in re.findall(r"^\s*(ITEM_\w+)\s*(?:=\s*([\w]+))?\s*,", txt, re.M):
        cur = (int(v) if v.isdigit() else vals.get(v, cur + 1)) if v else cur + 1
        vals[k] = cur
        names.setdefault(cur, k)
    return names


def read(pocket="berries"):
    off, count = POCKETS[pocket]
    sb1 = int(q.run([f"r32 {sym('gSaveBlock1Ptr')}"]).split("=")[1])
    sb2 = int(q.run([f"r32 {sym('gSaveBlock2Ptr')}"]).split("=")[1])
    key = int(q.run([f"r32 {sb2 + OFF_ENC}"]).split("=")[1]) & 0xFFFF
    raw = bytes.fromhex(q.run([f"range {sb1 + off} {count * 4}"]).split("=")[1])
    out = {}
    for i in range(count):
        it, qty = struct.unpack_from("<HH", raw, i * 4)
        if it:
            out[it] = qty ^ key
    return out


if __name__ == "__main__":
    names = item_names()
    for it, qty in read(sys.argv[1] if len(sys.argv) > 1 else "berries").items():
        print(f"{names.get(it, it)}\t{qty}")
