import sys, json, struct
SC = '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha'
sys.path.insert(0, SC + '/install'); sys.path.insert(0, SC); sys.path.insert(0, SC + '/m20/AbundanceIsle_SkylaHangar')
from art import *
from kit2 import read_blocks, write_blocks
import arte_santuario, arte_maquina, arte_aviao
P = load_tileset('primary', 'johto_general')
def entries_of(prim, sec, mid):
    m = prim['metas'][mid] if mid < 1024 else sec['metas'][mid - 1024]
    return m[4:8] if any(m[4:8]) else m[0:4]
def setcells(mapdir, w, x0, y0, grid):
    b = read_blocks(SC + '/m20/%s/map.bin' % mapdir)
    for r, row in enumerate(grid):
        for c, mid in enumerate(row):
            i = (y0 + r) * w + x0 + c
            b[i] = (b[i] & ~0x7ff) | mid | (1 << 11)          # bloqueado
    write_blocks(SC + '/m20/%s/map.bin' % mapdir, [b[k * w:(k + 1) * w] for k in range(len(b) // w)])
res = {}
# 1. santuario A no clone da fazenda (hub)
clone('route38_farmland', 'abundance_farmland')
g = install('abundance_farmland', arte_santuario.A(), lambda c, r: P['metas'][1][4:8])
I = json.load(open(SC + '/m20/AbundanceIsle/info.json')); setcells('AbundanceIsle', I['w'], 9, 19, g); res['santuario'] = g
# 2. maquina D no clone do gelo (lab)
clone('cave_ice', 'frostfall_crater')
S = load_tileset(None, path=ROOTD + 'frostfall_crater')
g = install('frostfall_crater', arte_maquina.D(), lambda c, r: S['metas'][0x59][4:8])
I = json.load(open(SC + '/m20/FROSTFALL_CRATER_LAB/info.json')); m = I['maquina']; setcells('FROSTFALL_CRATER_LAB', I['w'], m['x'], m['y'], g); res['maquina'] = g
# 3. aviao A no clone do armazem (hangar), chao celula a celula
clone('goldenrod_underground_storage', 'skyla_hangar')
S = load_tileset(None, path=ROOTD + 'skyla_hangar')
I = json.load(open(SC + '/m20/AbundanceIsle_SkylaHangar/info.json'))
HB = read_blocks(SC + '/m20/AbundanceIsle_SkylaHangar/map.bin')
X0, Y0 = 6, 3
g = install('skyla_hangar', arte_aviao.A(), lambda c, r: entries_of(P if False else load_tileset('primary', 'johto_building'), S, HB[(Y0 + r) * I['w'] + X0 + c] & 0x7ff))
setcells('AbundanceIsle_SkylaHangar', I['w'], X0, Y0, g); res['aviao'] = g
json.dump(res, open(SC + '/install/art_ids.json', 'w'))
print(res)
