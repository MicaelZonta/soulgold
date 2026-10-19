from pathlib import Path
from shutil import copyfile
from PIL import Image, ImageDraw

SCRIPT = Path(__file__).resolve()
ROOT = (SCRIPT.parents[4] if SCRIPT.parent.name == 'PropostaCodex'
        else Path(r'\\wsl.localhost\Ubuntu\home\ADMIN\decomps\soulgold_v1'))
OUT = ROOT / '.filetransfer/.trainers/Agatha/PropostaCodex'
OUT.mkdir(exist_ok=True)

# Thirteen opaque colors plus palette entry 0 for transparency.
RGB = [
    (0, 0, 0),       # transparent
    (27, 23, 31),    # outline
    (113, 91, 80),   # hair shadow
    (184, 157, 130), # hair middle
    (236, 211, 172), # hair light
    (253, 239, 205), # hair shine
    (172, 113, 99),  # skin shade
    (244, 190, 160), # skin
    (68, 42, 84),    # dark purple
    (127, 80, 149),  # purple
    (34, 69, 56),    # dark green
    (81, 121, 87),   # green
    (247, 234, 216), # apron
    (239, 192, 92),  # cat eyes
    (94, 69, 62),    # shoes
    (176, 129, 179), # dress highlight
]
PAL = [channel for rgb in RGB for channel in rgb] + [0] * (256 * 3 - 48)
I, HD, HM, HL, HH, SD, S, PD, P, GD, G, W, Y, B, PL = range(1, 16)

def poly(d, points, color):
    d.polygon(points, fill=color)

def box(d, coords, color):
    d.rectangle(coords, fill=color)

def line(d, points, color):
    d.line(points, fill=color)

def body(d, facing):
    # The same compact body is used for every walking phase.
    poly(d, [(4, 12), (11, 12), (13, 15), (13, 18),
             (11, 20), (4, 20), (2, 18), (2, 15)], I)
    poly(d, [(4, 14), (11, 14), (12, 18), (10, 19),
             (4, 19), (3, 18)], PD)
    poly(d, [(5, 15), (10, 15), (11, 18), (9, 19),
             (5, 18)], P)
    line(d, [(5, 18), (7, 19), (10, 18)], PL)
    if facing == 'front':
        poly(d, [(6, 15), (9, 15), (10, 18), (9, 19),
                 (6, 19)], W)
        box(d, (7, 17, 7, 17), HL)
    elif facing == 'back':
        box(d, (7, 14, 8, 15), W)
        box(d, (6, 15, 6, 16), W)
        box(d, (9, 15, 9, 16), W)
    # Dark green collar is chunky like other overworld sprites.
    poly(d, [(3, 11), (12, 11), (14, 13), (12, 15),
             (9, 14), (7, 15), (4, 14), (2, 15),
             (1, 13)], I)
    poly(d, [(3, 12), (12, 12), (13, 13), (10, 13),
             (7, 14), (4, 13), (2, 14)], GD)
    line(d, [(4, 12), (6, 13), (8, 13)], G)
    box(d, (10, 12, 12, 12), G)
    box(d, (3, 14, 4, 15), S)
    box(d, (11, 14, 12, 15), S)

def front_hair_face(d):
    # Voluminous hair, but only 12 pixels high like the existing trainer art.
    poly(d, [(5, 0), (9, 0), (12, 2), (13, 5),
             (15, 7), (14, 10), (12, 11), (10, 10),
             (9, 12), (4, 12), (2, 10), (0, 10),
             (0, 7), (2, 5), (2, 2)], I)
    poly(d, [(5, 1), (9, 1), (11, 3), (12, 5),
             (14, 7), (13, 9), (11, 10), (9, 11),
             (4, 11), (2, 9), (1, 9), (1, 7),
             (3, 5), (3, 3)], HD)
    poly(d, [(5, 2), (9, 1), (11, 3), (11, 6),
             (9, 8), (3, 8), (3, 4)], HM)
    poly(d, [(5, 2), (8, 1), (10, 3), (10, 5),
             (7, 6), (4, 5), (4, 3)], HL)
    line(d, [(6, 2), (8, 1), (9, 3)], HH)
    box(d, (1, 7, 2, 9), HL)
    box(d, (12, 7, 13, 9), HL)
    # Skin panel and high-contrast expression.
    poly(d, [(5, 5), (10, 5), (12, 7), (12, 10),
             (10, 12), (5, 12), (3, 10), (3, 7)], I)
    poly(d, [(5, 6), (10, 6), (11, 8), (11, 10),
             (9, 11), (6, 11), (4, 10), (4, 8)], SD)
    poly(d, [(5, 6), (9, 6), (10, 8), (10, 10),
             (9, 10), (6, 10), (5, 9)], S)
    # Fringe frames the face without covering either eye.
    poly(d, [(3, 4), (6, 3), (8, 5), (7, 7),
             (4, 7), (3, 9), (2, 8)], HM)
    line(d, [(4, 4), (6, 4), (7, 5)], HL)
    box(d, (11, 5, 12, 7), HL)
    line(d, [(5, 7), (6, 7)], HD)
    line(d, [(9, 7), (10, 7)], HD)
    box(d, (5, 8, 5, 8), I)
    box(d, (10, 8, 10, 8), I)
    box(d, (7, 9, 7, 9), SD)
    box(d, (7, 11, 8, 11), HD)

def back_hair(d):
    poly(d, [(5, 0), (9, 0), (12, 2), (13, 5),
             (15, 8), (13, 11), (10, 12), (4, 12),
             (2, 10), (0, 10), (0, 7), (2, 5),
             (2, 2)], I)
    poly(d, [(5, 1), (9, 1), (11, 3), (12, 6),
             (14, 8), (12, 10), (10, 11), (4, 11),
             (2, 9), (1, 9), (1, 7), (3, 5),
             (3, 3)], HD)
    poly(d, [(5, 2), (9, 1), (11, 3), (11, 7),
             (9, 10), (5, 10), (3, 8), (3, 4)], HM)
    poly(d, [(5, 2), (8, 1), (10, 3), (10, 6),
             (8, 8), (4, 8), (4, 4)], HL)
    line(d, [(6, 2), (8, 1), (9, 3)], HH)
    line(d, [(4, 9), (6, 11), (9, 11)], HD)
    box(d, (1, 8, 2, 9), HL)
    box(d, (12, 8, 13, 9), HL)

def side_hair_face(d):
    # Right-facing original; left-facing frame mirrors the entire sprite.
    poly(d, [(5, 0), (9, 0), (12, 2), (13, 5),
             (14, 8), (13, 11), (10, 12), (4, 12),
             (1, 10), (0, 8), (2, 5), (2, 2)], I)
    poly(d, [(5, 1), (9, 1), (11, 3), (12, 6),
             (13, 8), (12, 10), (9, 11), (4, 11),
             (2, 9), (1, 8), (3, 5), (3, 3)], HD)
    poly(d, [(5, 2), (9, 1), (11, 3), (11, 6),
             (9, 9), (4, 9), (2, 8), (3, 4)], HM)
    poly(d, [(5, 2), (8, 1), (10, 3), (10, 5),
             (7, 7), (4, 6), (4, 3)], HL)
    line(d, [(6, 2), (8, 1), (9, 3)], HH)
    poly(d, [(9, 5), (12, 5), (14, 7), (14, 10),
             (12, 12), (9, 11), (8, 8)], I)
    poly(d, [(9, 6), (12, 6), (13, 8), (13, 10),
             (11, 11), (9, 10)], SD)
    poly(d, [(10, 6), (12, 6), (13, 8), (12, 10),
             (10, 9)], S)
    poly(d, [(6, 4), (9, 3), (11, 5), (10, 7),
             (8, 8), (7, 10), (5, 8)], HM)
    line(d, [(7, 4), (9, 4), (10, 5)], HL)
    box(d, (12, 8, 12, 8), I)
    box(d, (12, 10, 12, 10), SD)
    box(d, (1, 8, 2, 9), HL)

def cane(d):
    # The cat and cane form a single shape connected to Agatha's hand.
    line(d, [(15, 14), (15, 21)], I)
    box(d, (14, 16, 14, 20), HD)
    poly(d, [(12, 14), (12, 12), (13, 13), (14, 12),
             (15, 13), (15, 15), (13, 15)], I)
    box(d, (14, 14, 14, 14), Y)
    box(d, (12, 15, 14, 15), HD)

def shoes(d, facing, phase):
    positions = ([(4, 9), (3, 10), (5, 8)] if facing in ('front', 'back')
                 else [(5, 9), (4, 10), (6, 8)])[phase]
    for x in positions:
        box(d, (x, 19, x + 1, 20), B)
        box(d, (x - 1, 20, x + 1, 21), I)
        box(d, (x, 20, x, 20), HD)

def draw_frame(facing, phase):
    im = Image.new('P', (16, 22), 0)
    im.putpalette(PAL)
    d = ImageDraw.Draw(im)
    body(d, facing)
    if facing == 'front':
        front_hair_face(d)
    elif facing == 'back':
        back_hair(d)
    else:
        side_hair_face(d)
    if facing != 'back':
        cane(d)
    shoes(d, facing, phase)
    if facing == 'left':
        im = im.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
    im.info['transparency'] = 0
    return im

ORDER = [('front', 0), ('back', 0), ('left', 0), ('right', 0),
         ('front', 1), ('front', 2), ('back', 1), ('back', 2),
         ('left', 1), ('left', 2), ('right', 1), ('right', 2)]
frames = [draw_frame(facing, phase) for facing, phase in ORDER]
sheet = Image.new('P', (384, 32), 0)
sheet.putpalette(PAL)
for i, frame in enumerate(frames):
    sheet.paste(frame, (i * 32 + 8, 9))
sheet.info['transparency'] = 0
sheet.save(OUT / 'Sprite.png', transparency=0, bits=4)

# All pixels belong to one character; upper pixels are stationary while
# walking and every shoe ends at the same y coordinate.
for i, frame in enumerate(frames):
    occupied = {(x, y) for y in range(22) for x in range(16)
                if frame.getpixel((x, y)) != 0}
    assert occupied and max(y for _, y in occupied) == 21, i
    connected = {occupied.pop()}
    queue = list(connected)
    while queue:
        x, y = queue.pop()
        for dx in (-1, 0, 1):
            for dy in (-1, 0, 1):
                neighbor = x + dx, y + dy
                if neighbor in occupied:
                    occupied.remove(neighbor)
                    connected.add(neighbor)
                    queue.append(neighbor)
    assert not occupied, (i, len(occupied))
for trio in ((0, 4, 5), (1, 6, 7), (2, 8, 9), (3, 10, 11)):
    upper = frames[trio[0]].crop((0, 0, 16, 19)).tobytes()
    assert all(frames[i].crop((0, 0, 16, 19)).tobytes() == upper
               for i in trio[1:]), trio

current = Image.open(ROOT / 'graphics/object_events/pics/people/special/agatha.png')
current_crop = current.crop((0, 0, 32, 32))
mask = Image.new('L', (32, 32))
mask.putdata([0 if current_crop.getpixel((x, y)) == 0 else 255
              for y in range(32) for x in range(32)])
current_rgba = current_crop.convert('RGBA')
current_rgba.putalpha(mask)
source_comp = Image.open(ROOT / '.filetransfer/.trainers/Agatha/Sprite - comparacao no jogo.png').convert('RGB')
player = source_comp.crop((146, 49, 274, 177)).resize((32, 32), Image.Resampling.NEAREST)

preview = Image.new('RGB', (1216, 420), (35, 36, 45))
d = ImageDraw.Draw(preview)
grass = (91, 133, 74)
def tile(im, x, y, scale):
    bg = Image.new('RGB', (32, 32), grass)
    if im.mode == 'RGBA':
        bg.paste(im, (0, 0), im)
    else:
        bg.paste(im, (0, 0))
    preview.paste(bg.resize((32 * scale, 32 * scale), Image.Resampling.NEAREST), (x, y))

d.text((24, 20), 'AGATHA | nova arte no estilo do jogador | area visivel 16 x 22', fill='white')
for x, label, sprite in [(40, 'Agatha atual', current_rgba),
                         (224, 'Jogador', player),
                         (408, 'Agatha proposta', sheet.convert('RGBA').crop((0, 0, 32, 32)))]:
    d.text((x, 56), label, fill='white')
    tile(sprite, x, 76, 4)
d.text((24, 236), '12 quadros da engine | corpo fixo, sapatos na mesma linha', fill='white')
for i in range(12):
    x = 24 + i * 98
    tile(sheet.convert('RGBA').crop((i * 32, 0, (i + 1) * 32, 32)), x, 262, 3)
    d.text((x + 43, 364), str(i), fill='white')
preview.save(OUT / 'Sprite - comparacao no jogo.png')

(OUT / 'README.md').write_text(
    '# Agatha — Proposta Codex\n\n'
    'Sprite de campo novo, desenhado pixel a pixel na escala do projeto: '
    '**16×22 pixels visíveis** centralizados em quadros de 32×32. '
    'O desenho respeita o limite de largura 16×32. Para comparação, '
    'a Agatha atual ocupa 16×22 e o jogador 14×19 pixels.\n\n'
    'São 12 quadros na ordem da engine: baixo, cima, esquerda, direita, '
    'depois dois passos por direção. O corpo permanece fixo na caminhada, '
    'os sapatos terminam sempre na mesma linha e cada quadro foi '
    'verificado para evitar pixels desconectados.\n\n'
    '- `Sprite.png`: 384×32, PNG indexado de 4 bits; índice 0 transparente.\n'
    '- `Sprite.4bpp` e `Sprite.gbapal`: conversão GBA da proposta.\n'
    '- `Sprite - comparacao no jogo.png`: montagem na escala do jogo, '
    'ampliada 4×; não é captura da ROM.\n'
    '- `gerar_sprite.py`: fonte do desenho e das validações.\n\n'
    'A proposta ainda não foi instalada em `graphics/object_events/`.\n',
    encoding='utf-8',
)
if SCRIPT != OUT / 'gerar_sprite.py':
    copyfile(SCRIPT, OUT / 'gerar_sprite.py')
print('created', OUT)
