"""Grama alta nos mapas da Abundance Isle que nao tinham nenhuma (hub, Harvest Fields, Gale Shore, Thunder Ridge).

Pinta manchas retangulares de 0x00D (grama alta do Johto_General, a mesma das rotas de Johto) so sobre
chao de grama aberto (0x001, andavel, elevacao 3), a 2+ celulas de warp, objeto, gatilho e placa, sem
encostar em agua. Grava no map.bin do PROTOTIPO (mapas/<Mapa>/map.bin): o maps.py copia para o repo.
Idempotente: mapa que ja tem 0x00D fica como esta. Rodar da raiz do repo, antes do maps.py.

    python3 .claude/abundance_isle/instalar/grama.py [--render DIR]"""
import json, os, struct, sys

SC = '.claude/abundance_isle'
GRAMA = 0x00D
CHAO = {0x001}                       # chao de grama
CHAO_MAPA = {'THUNDER_RIDGE': {0x001, 0x071}}   # o Ridge e quase todo terra de montanha (0x071)
# mapa -> (numero de manchas, (largura, altura) maximas)
ALVO = {'AbundanceIsle': (3, (6, 4)), 'AbundanceIsle_HarvestFields': (4, (7, 4)),
        'AbundanceIsle_GaleShore': (3, (6, 4)), 'THUNDER_RIDGE': (4, (6, 4))}


def pintar(d, n, maxwh):
    info = json.load(open(f'{SC}/mapas/{d}/info.json'))
    w, h = info['w'], info['h']
    path = f'{SC}/mapas/{d}/map.bin'
    b = list(struct.unpack('<%dH' % (w * h), open(path, 'rb').read()))
    if any(v & 0x7FF == GRAMA for v in b):
        return 0
    chao = CHAO_MAPA.get(d, CHAO)
    perto = set()
    pts = [(o['x'], o['y']) for o in info['objects']] + [(p['x'], p['y']) for p in info['warps']]
    pts += [(e['x'], e['y']) for e in info.get('bg_events', [])] + [(e['x'], e['y']) for e in info.get('coord_events', [])]
    for x0, y0 in pts:
        for dy in range(-2, 3):
            for dx in range(-2, 3):
                perto.add((x0 + dx, y0 + dy))

    def ok(x, y):
        if not (1 <= x < w - 1 and 1 <= y < h - 1) or (x, y) in perto:
            return False
        v = b[y * w + x]
        return v & 0x7FF in chao and not v >> 11 & 1 and v >> 12 == 3

    def andavel(x, y):   # margem: qualquer chao andavel da mesma elevacao (nao agua, nao parede)
        if not (0 <= x < w and 0 <= y < h) or (x, y) in perto:
            return False
        v = b[y * w + x]
        return not v >> 11 & 1 and v >> 12 == 3

    usados = set()
    feitos = 0
    mw, mh = maxwh
    for _ in range(n):
        best = None
        for y in range(h):
            for x in range(w):
                for ww in range(mw, 2, -1):
                    for hh in range(mh, 1, -1):
                        cel = [(x + i, y + j) for j in range(hh) for i in range(ww)]
                        # margem de 1 celula de chao em volta (nao cola em parede/caminho/outra mancha)
                        borda = [(x + i, y + j) for j in range(-1, hh + 1) for i in range(-1, ww + 1)]
                        if all(ok(*c) for c in cel) and all(andavel(*c) for c in borda) and not (set(cel) & usados):
                            area = ww * hh
                            if best is None or area > best[0]:
                                best = (area, cel, borda)
                            break
                    else:
                        continue
                    break
        if not best:
            break
        for x, y in best[1]:
            b[y * w + x] = (b[y * w + x] & ~0x7FF) | GRAMA
        usados |= set(best[2])
        # espalha: nada de outra mancha a menos de 6 celulas desta
        xs = [c[0] for c in best[1]]; ys = [c[1] for c in best[1]]
        for yy in range(min(ys) - 4, max(ys) + 5):
            for xx in range(min(xs) - 4, max(xs) + 5):
                usados.add((xx, yy))
        feitos += 1
    open(path, 'wb').write(struct.pack('<%dH' % (w * h), *b))
    return feitos


def main():
    for d, (n, wh) in ALVO.items():
        print(d, 'manchas:', pintar(d, n, wh))


if __name__ == '__main__':
    main()
