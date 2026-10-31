"""Interior a partir de um layout existente (mesmos tilesets): copia o map.bin, aplica trocas e grava entrega."""
import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from kitA1 import *
def interior(D, base, info, objs, warp, edits=(), start=None, crop_w=None):
    L = load_layout(base); W, H = L['w'], L['h']
    b = list(L['blocks'])
    if crop_w:
        b = [b[y * W + x] for y in range(H) for x in range(crop_w)]; W = crop_w
    for x, y, mid, coll in edits: b[y * W + x] = pack_block(mid, coll, b[y * W + x] >> 12)
    write_blocks(os.path.join(D, 'map.bin'), [b[y * W:(y + 1) * W] for y in range(H)])
    import shutil; shutil.copy(os.path.join(ROOT, L['info']['border_filepath']), os.path.join(D, 'border.bin'))
    bad = check_objects(b, W, objs)
    d = bfs(b, W, H, start or (warp[0], warp[1] - 1))
    reach = {ob['local_id']: any((ob['x'] + dx, ob['y'] + dy) in d for dx, dy in ((0, 1), (1, 0), (-1, 0), (0, -1), (0, 0))) for ob in objs}
    write_png(os.path.join(D, 'dia.png'), render_blocks(b, W, H, L['prim'], L['sec'], objects=objs), 3)
    write_png(os.path.join(D, 'colisao.png'), render_blocks(b, W, H, L['prim'], L['sec'], objects=objs, overlay=True, marks=[(warp, (200, 120, 255))]), 3)
    info.update(w=W, h=H, primary=L['info']['primary_tileset'], secondary=L['info']['secondary_tileset'], map_type='MAP_TYPE_INDOOR', objects=objs,
                conferido='base %s (layout copiado%s, %d celulas trocadas); check_objects=%s; alcancavel da porta: %s' % (base, ', cortado em %d colunas' % W if crop_w else '', len(edits), bad, reach))
    json.dump(info, open(os.path.join(D, 'info.json'), 'w'), indent=1, ensure_ascii=False)
    print(info['map'], info['conferido'])
    return b, W, H, L
