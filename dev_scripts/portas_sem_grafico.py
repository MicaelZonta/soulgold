#!/usr/bin/env python3
"""Acha metatile com comportamento de porta que nao esta em sDoorAnimGraphicsTable."""
import json, re, struct, sys
from pathlib import Path

R = Path('.')
MB_NON_ANIMATED_DOOR, MB_ANIMATED_DOOR = 96, 105

# ids da tabela de portas
labels = {}
for m in re.finditer(r'#define\s+(METATILE_\w+)\s+(0x[0-9A-Fa-f]+|\d+)', (R/'include/constants/metatile_labels.h').read_text()):
    labels[m.group(1)] = int(m.group(2), 0)
door_src = re.search(r'sDoorAnimGraphicsTable\[\] =\s*\{(.*?)\n\};', (R/'src/field_door.c').read_text(), re.S).group(1)
table = set()
for line in door_src.splitlines():
    line = line.strip()
    if line.startswith('//') or not line.startswith('{'):
        continue
    n = re.match(r'\{\s*(METATILE_\w+)', line)
    if n:
        if n.group(1) in labels: table.add(labels[n.group(1)])
        else: print('AVISO: label desconhecido', n.group(1))
print(f'tabela de portas: {len(table)} ids')

# tileset -> pasta de atributos
hdr = (R/'src/data/tilesets/headers.h').read_text()
attr = {}
for blk in re.finditer(r'const struct Tileset (gTileset_\w+)\s*=\s*\{(.*?)\n\};', hdr, re.S):
    name, body = blk.group(1), blk.group(2)
    p = re.search(r'metatile_attributes.bin"', body)
    mm = re.search(r'\.metatileAttributes\s*=\s*\w*\(?"?([^",)]*metatile_attributes\.bin)', body)
    if not mm:
        mm = re.search(r'INCBIN_[A-Z0-9]+\("([^"]*metatile_attributes\.bin)"\)', body)
    if mm: attr[name] = mm.group(1)
# fallback: variaveis gMetatileAttributes_X
for m in re.finditer(r'const u1[66]\s+(\w*MetatileAttributes\w*)\[\]\s*=\s*INCBIN_U16\("([^"]+)"\)', hdr):
    pass

def behaviors(sym):
    """lista de comportamentos por indice de metatile do tileset"""
    path = attr.get(sym)
    if not path:
        # procura pela convencao de pasta
        snake = re.sub(r'(?<!^)(?=[A-Z])', '_', sym[len('gTileset_'):]).lower()
        for sub in ('primary', 'secondary'):
            c = R/f'data/tilesets/{sub}/{snake}/metatile_attributes.bin'
            if c.exists(): path = str(c); break
    if not path or not Path(path).exists(): return None
    b = Path(path).read_bytes()
    return [int.from_bytes(b[i:i+2], 'little') & 0x1FF for i in range(0, len(b), 2)]

NUM_PRIMARY = int(re.search(r'#define NUM_METATILES_IN_PRIMARY\s+(\d+)', (R/'include/fieldmap.h').read_text()).group(1)) \
    if re.search(r'NUM_METATILES_IN_PRIMARY', (R/'include/fieldmap.h').read_text()) else 640
print('NUM_METATILES_IN_PRIMARY =', NUM_PRIMARY)

layouts = json.load(open(R/'data/layouts/layouts.json'))['layouts']
# mapas por layout
maps = {}
for mj in sorted(Path('data/maps').glob('*/map.json')):
    j = json.load(open(mj))
    maps.setdefault(j['layout'], []).append(j['id'])

ruim = {}
for L in layouts:
    bp = Path(L.get('blockdata_filepath', ''))
    if not bp.exists(): continue
    prim = behaviors(L['primary_tileset']); sec = behaviors(L['secondary_tileset'])
    if prim is None: continue
    raw = bp.read_bytes()
    seen = set()
    for i in range(0, len(raw) - 1, 2):
        seen.add(struct.unpack_from('<H', raw, i)[0] & 0x7FF)
    for mid in seen:
        if mid < NUM_PRIMARY:
            bh = prim[mid] if mid < len(prim) else None
        else:
            k = mid - NUM_PRIMARY
            bh = sec[k] if sec and k < len(sec) else None
        if bh in (MB_ANIMATED_DOOR,) and mid not in table:
            ruim.setdefault((L['id'], L['primary_tileset'], L['secondary_tileset'], mid), 0)
            ruim[(L['id'], L['primary_tileset'], L['secondary_tileset'], mid)] += 1

print(f'\n{len(ruim)} caso(s) de porta animada sem entrada na tabela:\n')
for (lid, p, s, mid) in sorted(ruim):
    print(f'  {lid:38} metatile {mid:5}  prim={p} sec={s}')
    for mn in maps.get(lid, [])[:4]: print(f'        {mn}')
