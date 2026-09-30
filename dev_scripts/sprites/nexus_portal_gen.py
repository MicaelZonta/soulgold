# -*- coding: utf-8 -*-
# Gera graphics/object_events/pics/misc/nexus_portal.png (128x32, 4 quadros
# 32x32 em loop) e um preview ampliado. Rodar com o Python do Windows (PIL).
import math
from PIL import Image

PAL = [
    (248, 0, 248),    # 0 transparente
    (16, 8, 32),      # 1 vazio quase preto
    (48, 24, 80),     # 2 violeta profundo
    (88, 40, 136),    # 3 violeta
    (136, 56, 184),   # 4 roxo
    (192, 80, 216),   # 5 magenta
    (232, 120, 240),  # 6 rosa brilhante
    (248, 184, 248),  # 7 rosa palido
    (248, 248, 248),  # 8 nucleo branco
    (248, 208, 96),   # 9 ouro
    (200, 144, 40),   # 10 ouro escuro
    (120, 216, 248),  # 11 faisca ciano
] + [(0, 0, 0)] * 4

W, H, FRAMES = 32, 32, 4
CX, CY = 15.5, 15.5
RX, RY = 12.0, 15.0

img = Image.new("P", (W * FRAMES, H), 0)
flat = []
for c in PAL:
    flat += list(c)
img.putpalette(flat)
px = img.load()

for f in range(FRAMES):
    phase = f * (2.0 * math.pi / FRAMES)
    ox = f * W
    for y in range(H):
        for x in range(W):
            dx = (x - CX) / RX
            dy = (y - CY) / RY
            rr = math.hypot(dx, dy)
            th = math.atan2(dy, dx)
            c = 0
            if rr > 1.06:
                c = 0
            elif rr > 0.90:
                # aro dourado com brilho girando
                shimmer = math.sin(5.0 * th - phase * 2.0)
                c = 9 if shimmer > -0.55 else 10
            else:
                # bandas por raio, do nucleo branco ao violeta da borda
                if rr < 0.14:
                    base = 8
                elif rr < 0.28:
                    base = 7
                elif rr < 0.44:
                    base = 6
                elif rr < 0.60:
                    base = 5
                elif rr < 0.74:
                    base = 4
                elif rr < 0.84:
                    base = 3
                else:
                    base = 2
                # bracos em espiral girando com o quadro
                arm = math.sin(2.0 * th + 9.5 * rr - phase)
                if arm > 0.45 and 2 <= base <= 6:
                    base += 1
                elif arm < -0.65 and 3 <= base <= 7:
                    base -= 1
                # fundo entre os bracos afunda para o quase-preto
                if base == 2 and arm < -0.2:
                    base = 1
                c = base
            px[ox + x, y] = c
    # tres faiscas ciano orbitando o aro
    for k in range(3):
        a = phase * 0.5 + k * 2.0 * math.pi / 3.0
        sx = int(round(CX + math.cos(a) * (RX * 0.97)))
        sy = int(round(CY + math.sin(a) * (RY * 0.97)))
        if 0 <= sx < W and 0 <= sy < H:
            px[ox + sx, sy] = 11

img.save("graphics/object_events/pics/misc/nexus_portal.png", transparency=0)

big = img.convert("RGB").resize((W * FRAMES * 4, H * 4), Image.NEAREST)
big.save("dev_scripts/sprites/nexus_portal_preview.png")
print("ok")
