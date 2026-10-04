#!/usr/bin/env python3
"""Lista os gSprites ativos com o intervalo de tiles de VRAM que cada um usa e
aponta sobreposicoes (dois sprites desenhando nos mesmos tiles = grafico
corrompido, "listras"). Layout da struct Sprite medido com offsetof (68 bytes;
inUse no bit 0 de 0x3E; OAM nos 8 primeiros)."""
import re, struct, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import q
from ir import sym

SIZE, OFF_FLAGS = 68, 0x3E
MAX = int(re.search(r"#define MAX_SPRITES (\d+)", (Path(__file__).parents[2] / "include/sprite.h").read_text()).group(1))
# tiles 4bpp por (shape, size): quadrado, horizontal, vertical
TILES = {(0, 0): 1, (0, 1): 4, (0, 2): 16, (0, 3): 64, (1, 0): 2, (1, 1): 4, (1, 2): 8, (1, 3): 32,
         (2, 0): 2, (2, 1): 4, (2, 2): 8, (2, 3): 32}
raw = bytes.fromhex(q.run([f"range {sym('gSprites')} {MAX * SIZE}"]).split("=")[1])
live = []
for i in range(MAX):
    s = raw[i * SIZE:(i + 1) * SIZE]
    if not (struct.unpack_from("<H", s, OFF_FLAGS)[0] & 1):
        continue
    a0, a1, a2 = struct.unpack_from("<HHH", s, 0)
    shape, size, tile = a0 >> 14, a1 >> 14, a2 & 0x3FF
    n = TILES.get((shape, size), 1)
    images = struct.unpack_from("<I", s, 12)[0]
    live.append((i, tile, n, images))
    print(f"sprite {i:2} tiles {tile:4}..{tile + n - 1:4} ({n:2}) images={images:08x}")
# Objetos: quem e cada sprite (ObjectEvent.spriteId em 35, localId em 8).
COUNT = int(re.search(r"#define OBJECT_EVENTS_COUNT (\d+)", (Path(__file__).parents[2] / "include/constants/global.h").read_text()).group(1))
objs = bytes.fromhex(q.run([f"range {sym('gObjectEvents')} {COUNT * 36}"]).split("=")[1])
owner = {}
for k in range(COUNT):
    o = objs[k * 36:(k + 1) * 36]
    if o[0] & 1:
        owner[o[35]] = f"objeto local {o[8]}"
# So interessa sobreposicao com quem tem imagens proprias (objetos): sombras e
# efeitos com folha compartilhada (mesmo tile) sao normais.
for a in live:
    if a[0] not in owner:
        continue
    for b in live:
        if b[0] != a[0] and a[1] < b[1] + b[2] and b[1] < a[1] + a[2]:
            quem = owner.get(b[0], "efeito/sombra")
            print(f"SOBREPOE: sprite {a[0]} ({owner[a[0]]}, tiles {a[1]}..{a[1]+a[2]-1}) x sprite {b[0]} ({quem}, {b[1]}..{b[1]+b[2]-1})")
