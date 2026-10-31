#!/usr/bin/env python3
"""Instant Win: avanca texto com B ate o menu de acao (comparado ao print de referencia) e usa o debug de batalha."""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import q
from PIL import Image, ImageChops, ImageStat
REF = Image.open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'menu_acao_ref.png')).convert('RGB').crop((120, 112, 240, 160))
def at_menu():
    cur = os.path.join(q.DIR, 'win_cur.png'); q.run([f'shot {cur}'])
    im = Image.open(cur).convert('RGB').crop((120, 112, 240, 160))
    return sum(ImageStat.Stat(ImageChops.difference(im, REF)).mean) < 12
for i in range(40):
    if at_menu():
        q.run(['press SELECT 10 120', 'rep 16 press DOWN 4 8', 'press A 6 60', 'rep 3 press B 6 30', 'wait 300'])
        print('instant win'); break
    q.run(['press B 6 60'])
else:
    print('menu nao encontrado'); sys.exit(1)
