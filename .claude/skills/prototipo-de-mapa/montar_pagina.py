#!/usr/bin/env python3
"""Monta a pagina HTML do prototipo (arquivo unico, imagens embutidas) a partir de um modelo.

    python3 .claude/skills/prototipo-de-mapa/montar_pagina.py MODELO.html SAIDA.html --base DIR \
        [--tileset DIR_DO_TILESET --swap 7,9,10 --nome "7=Pedra, agua e musgo" --nome "8=Rocha"]

Marcadores no modelo:
  {{IMG:caminho/relativo.png}}  -> data:image/png;base64 (caminho relativo a --base)
  {{PALETAS}}                   -> cartoes de paleta (dia e, se em --swap, noite) lidos dos .pal
  {{NUM:chave}}                 -> valor de --num chave=valor (ex.: tiles=249)
A pagina precisa caber em 16 MB: prefira renders 2x e recortes pequenos.
"""
import argparse, base64, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'montar-tileset'))
from tileset_kit import read_pal, night_file_for_slot

ap = argparse.ArgumentParser()
ap.add_argument('modelo'); ap.add_argument('saida')
ap.add_argument('--base', default='.')
ap.add_argument('--tileset')
ap.add_argument('--swap', default='')
ap.add_argument('--nome', action='append', default=[])
ap.add_argument('--num', action='append', default=[])
a = ap.parse_args()

html = open(a.modelo).read()
hexc = lambda c: '#%02x%02x%02x' % tuple(c[:3])

if '{{PALETAS}}' in html:
    if not a.tileset:
        sys.exit('o modelo usa {{PALETAS}}: passe --tileset')
    swap = [int(s) for s in a.swap.split(',') if s]
    nomes = dict(n.split('=', 1) for n in a.nome)
    cards = []
    for s in range(7, 13):
        f = os.path.join(a.tileset, 'palettes', '%02d.pal' % s)
        if not os.path.exists(f):
            continue
        day = read_pal(f)
        if not any(day[1:]):                      # paleta vazia: nao mostra
            continue
        used = [i for i in range(1, 16) if day[i] != (0, 0, 0)] or list(range(1, 16))
        row = lambda cols: ''.join('<i style="background:%s"></i>' % hexc(cols[i]) for i in used)
        night = ''
        tag = ''
        if s in swap:
            n = read_pal(os.path.join(a.tileset, 'palettes', '%02d.pal' % night_file_for_slot(s)))
            night = '<div class="sw"><span class="lbl">noite</span>%s</div>' % row(n)
            tag = '<span class="tag moon">noite em %02d.pal</span>' % night_file_for_slot(s)
        cards.append('<div class="pal"><div class="pal-head"><span class="mono">%02d.pal</span><span>%s</span>%s</div>'
                     '<div class="sw"><span class="lbl">dia</span>%s</div>%s</div>'
                     % (s, nomes.get(str(s), ''), tag, row(day), night))
    html = html.replace('{{PALETAS}}', '\n'.join(cards))

for kv in a.num:
    k, v = kv.split('=', 1)
    html = html.replace('{{NUM:%s}}' % k, v)

def img(m):
    p = os.path.join(a.base, m.group(1))
    if not os.path.exists(p):
        sys.exit('imagem nao encontrada: %s' % p)
    return 'data:image/png;base64,' + base64.b64encode(open(p, 'rb').read()).decode()
html = re.sub(r'\{\{IMG:([^}]+)\}\}', img, html)

left = re.findall(r'\{\{[A-Z]+[^}]*\}\}', html)
if left:
    sys.exit('marcadores sem valor: %s' % sorted(set(left)))
open(a.saida, 'w').write(html)
print('%s: %.0f KB' % (a.saida, len(html) / 1024))
