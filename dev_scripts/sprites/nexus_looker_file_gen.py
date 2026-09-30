# -*- coding: utf-8 -*-
# Gera graphics/object_events/pics/misc/nexus_looker_file.png (16x16, um
# quadro), graphics/object_events/palettes/nexus_looker_file.pal e um preview
# ampliado. O Looker File do Nexus (NEXUS_REGRAS R18): um caderno aberto no
# chao, capa marrom gasta, paginas creme com linhas, e um brilho violeta nas
# bordas - ele nao devia estar ali. Rodar com o Python do Windows (PIL).
from PIL import Image

PAL = [
    (248, 0, 248),    # 0 transparente
    (40, 24, 16),     # 1 contorno
    (104, 64, 40),    # 2 capa marrom
    (152, 96, 56),    # 3 capa clara
    (248, 240, 208),  # 4 pagina creme
    (216, 200, 160),  # 5 pagina sombra / dobra
    (96, 104, 152),   # 6 linhas de tinta
    (184, 96, 232),   # 7 brilho violeta do Nexus
    (232, 168, 248),  # 8 brilho claro
] + [(0, 0, 0)] * 7

# 16x16: caderno aberto, levemente em perspectiva (visto de cima no chao).
ART = [
    "................",
    "................",
    "................",
    "..7..........7..",
    ".111111.1111111.",
    ".1444451544444 1".replace(" ", "4"),
    ".1466451546664 1".replace(" ", "4"),
    ".1444451544444 1".replace(" ", "4"),
    ".1466451546664 1".replace(" ", "4"),
    ".1444451544444 1".replace(" ", "4"),
    ".1466451546644 1".replace(" ", "4"),
    ".1444451544444 1".replace(" ", "4"),
    ".12222213222221 ".replace(" ", "."),
    "..1111111111111.",
    ".8............7.",
    "................",
]

CODE = {".": 0, "1": 1, "2": 2, "3": 3, "4": 4, "5": 5, "6": 6, "7": 7, "8": 8}

img = Image.new("P", (16, 16), 0)
flat = []
for c in PAL:
    flat += list(c)
img.putpalette(flat)
px = img.load()
for y, row in enumerate(ART):
    assert len(row) == 16, (y, row, len(row))
    for x, ch in enumerate(row):
        px[x, y] = CODE[ch]

img.save("graphics/object_events/pics/misc/nexus_looker_file.png", transparency=0)

with open("graphics/object_events/palettes/nexus_looker_file.pal", "w", newline="\n") as f:
    f.write("JASC-PAL\n0100\n16\n")
    for r, g, b in PAL:
        f.write("%d %d %d\n" % (r, g, b))

img.convert("RGB").resize((16 * 8, 16 * 8), Image.NEAREST).save(
    "dev_scripts/sprites/nexus_looker_file_preview.png")
print("ok")
