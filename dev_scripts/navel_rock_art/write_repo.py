"""JSON do build.py -> arquivos do repositorio (tileset + map.bin + border.bin).

Uso (python do WSL, na raiz do repo):
    python3 dev_scripts/navel_rock_art/write_repo.py <pasta com os json>

Fluxo completo (o build.py precisa de numpy/scipy/PIL: Python do Windows):
    PY=/mnt/c/Users/User/AppData/Local/Programs/Python/Python310/python.exe
    for g in ext room1 room2 room3 room4; do $PY "$(wslpath -w dev_scripts/navel_rock_art/build.py)" $g "$(wslpath -w $OUT/$g.json)"; done
    python3 dev_scripts/navel_rock_art/write_repo.py $OUT
Os estados abertos (brecha room1, fenda room2, portao room3) saem em
$OUT/<grupo>_open.txt: os #define vao para metatile_labels.h e os setmetatile para
NavelRock_<Mapa>_SetOpen em data/scripts/navel_rock.inc. Mudar a ordem dos
metatiles muda esses ids: cole de novo depois de regenerar.
"""
import sys, os, json, struct
sys.path.insert(0, '.claude/skills/montar-tileset')
from tileset_kit import write_png_indexed4, write_pal, load_tileset

SRC = sys.argv[1]
# grupo -> (pasta do tileset, layout)
TARGETS = {
    'ext':   ('navel_rock_island',        'NavelRock_Exterior'),
    'room1': ('navel_rock_tide_grotto',   'NavelRock_SeaBreach'),
    'room2': ('navel_rock_hot_springs',   'NavelRock_FireVent'),
    'room3': ('navel_rock_steam_gallery', 'NavelRock_SteamGallery'),
    'room4': ('navel_rock_sanctum',       'NavelRock_SteamChamber'),
}
ELEV = 3
# grupo com estado aberto -> (tileset nos labels, nome do estado)
OPEN_NAMES = {'room1': ('TideGrotto', 'BreachOpen'), 'room2': ('HotSprings', 'VentOpen'),
              'room3': ('SteamGallery', 'GateOpen')}

for g, (folder, layout) in TARGETS.items():
    d = json.load(open(os.path.join(SRC, g + '.json')))
    base = os.path.join('data/tilesets/secondary', folder)
    os.makedirs(os.path.join(base, 'palettes'), exist_ok=True)
    tiles = d['tiles']
    assert len(tiles) <= 384, (g, len(tiles))
    rows = (len(tiles) + 15) // 16
    idx = [[0] * 128 for _ in range(rows * 8)]
    for n, t in enumerate(tiles):
        for y in range(8):
            for x in range(8):
                idx[(n // 16) * 8 + y][(n % 16) * 8 + x] = t[y * 8 + x]
    pals = {7 + i: [tuple(c) for c in p] for i, p in enumerate(d['pals'])}
    write_png_indexed4(os.path.join(base, 'tiles.png'), idx, pals[7])
    for i in range(16):
        write_pal(os.path.join(base, 'palettes', '%02d.pal' % i), pals.get(i, [(0, 0, 0)] * 16))
    with open(os.path.join(base, 'metatiles.bin'), 'wb') as f:
        for m in d['metas']:
            assert len(m) == 12
            f.write(struct.pack('<12H', *m))
    with open(os.path.join(base, 'metatile_attributes.bin'), 'wb') as f:
        for a in d['attrs']:
            f.write(struct.pack('<H', a))
    # mapa
    b = d['blocks'][g]
    os.makedirs(os.path.join('data/layouts', layout), exist_ok=True)
    with open(os.path.join('data/layouts', layout, 'map.bin'), 'wb') as f:
        for i, (mid, coll) in enumerate(b['cells']):
            assert mid < 2048
            if g == 'room3' and (i % b['w'], i // b['w']) == (14, 6):
                coll = 1      # a porta do portao nasce fechada; o ON_LOAD abre
            f.write(struct.pack('<H', mid | (coll << 11) | (ELEV << 12)))
    # borda 2x2: canto de cima-esquerda do mapa (rocha macica) ou o mar
    W = b['w']
    cells = b['cells']
    if g == 'ext':
        border = [299] * 4
    else:
        border = [cells[0][0], cells[1][0], cells[W][0], cells[W + 1][0]]
    with open(os.path.join('data/layouts', layout, 'border.bin'), 'wb') as f:
        for mid in border:
            f.write(struct.pack('<H', mid | (1 << 11) | (ELEV << 12)))
    # conferencia: relendo o que foi escrito
    T = load_tileset(None, path=base)
    print('%-6s %-26s tiles %3d metatiles %3d  mapa %dx%d  portao %d' % (
        g, folder, len(tiles), len(T['metas']), b['w'], b['h'], len(d['gate'])))
    if d['gate']:
        json.dump(d['gate'], open(os.path.join(SRC, g + '_gate.json'), 'w'))
        # labels e setmetatile do estado aberto, prontos para colar
        mapa, estado = OPEN_NAMES[g]
        x0 = min(c['x'] for c in d['gate']); y0 = min(c['y'] for c in d['gate'])
        with open(os.path.join(SRC, g + '_open.txt'), 'w') as f:
            f.write('// gTileset_NavelRock_%s\n' % mapa)
            for c in d['gate']:
                f.write('#define METATILE_NavelRock_%s_%s_r%dc%d  0x%X\n' % (mapa, estado, c['y'] - y0, c['x'] - x0, c['open']))
            f.write('\n')
            for c in d['gate']:
                f.write('\tsetmetatile %d, %d, METATILE_NavelRock_%s_%s_r%dc%d, %s\n' % (
                    c['x'], c['y'], mapa, estado, c['y'] - y0, c['x'] - x0, 'TRUE' if c['coll'] else 'FALSE'))
