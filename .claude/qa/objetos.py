#!/usr/bin/env python3
"""Lista os gObjectEvents ativos (slot, localId, x, y). Prova se um NPC/arvore
foi criado de fato: o limite e OBJECT_EVENTS_COUNT (lido do header) por janela de camera."""
import re, struct, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import q
from ir import sym

SIZE, OFF_LOCAL, OFF_COORDS = 36, 8, 16   # sizeof/offsetof(struct ObjectEvent)
COUNT = int(re.search(r"#define OBJECT_EVENTS_COUNT (\d+)",
    (Path(__file__).parents[2] / "include/constants/global.h").read_text()).group(1))
raw = bytes.fromhex(q.run([f"range {sym('gObjectEvents')} {COUNT * SIZE}"]).split("=")[1])
n = 0
for i in range(COUNT):
    o = raw[i * SIZE:(i + 1) * SIZE]
    if o[0] & 1:
        n += 1
        x, y = struct.unpack_from("<hh", o, OFF_COORDS)
        print(f"slot{i:2} local={o[OFF_LOCAL]:3} ({x - 7},{y - 7})")
print(f"ativos: {n} de {COUNT}")
