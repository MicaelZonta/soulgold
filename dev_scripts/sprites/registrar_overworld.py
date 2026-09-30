#!/usr/bin/env python3
"""Registra (ou ajusta) o overworld de um personagem nos 8 lugares do jogo.

    registrar_overworld.py <Nome> <png> --quadro 16|32 [--const NOME_C] [--c NomeC]

<png> e o PNG do jogo ja gravado (propostas_overworld.py final): o numero de
quadros sai da largura (9 = sAnimTable_Standard, 12 = sAnimTable_StandardAsym).
Idempotente: o que ja existe e reescrito com o formato novo (16x32 <-> 32x32,
9 <-> 12 quadros); o que falta e criado ao lado da Brendan Hoenn:

  spritesheet_rules.mk      regra -mwidth 2|4 -mheight 4 (sem ela o NPC fica invisivel)
  event_objects.h           OBJ_EVENT_GFX_* (NUM_OBJ_EVENT_GFX++) e OBJ_EVENT_PAL_TAG_*
  object_event_graphics.h   INCBIN do .4bpp e do .gbapal
  object_event_pic_tables.h sPicTable_* com overworld_frame(pic, 2|4, 4, i)
  object_event_graphics_info.h  size/width/height/oam/subsprites/anims (+ paleta propria)
  object_event_graphics_info_pointers.h  extern + [OBJ_EVENT_GFX_*]
  event_object_movement.c   {gObjectEventPal_*, OBJ_EVENT_PAL_TAG_*}

Quem usava paleta compartilhada de NPC (Misty: OBJ_EVENT_PAL_TAG_NPC_3) ganha
paleta propria, porque a arte nova tem outras cores.
"""
import argparse
import os
import re
import sys

from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RULES = 'spritesheet_rules.mk'
CONST = 'include/constants/event_objects.h'
GFX = 'src/data/object_events/object_event_graphics.h'
PICS = 'src/data/object_events/object_event_pic_tables.h'
INFO = 'src/data/object_events/object_event_graphics_info.h'
PTRS = 'src/data/object_events/object_event_graphics_info_pointers.h'
MOVE = 'src/event_object_movement.c'
ANCORA = 'BrendanHoenn'   # ultimo personagem registrado a mao; novos entram depois dele


def ler(p):
    with open(os.path.join(ROOT, p), encoding='utf-8') as f:
        return f.read()


def gravar(p, s):
    with open(os.path.join(ROOT, p), 'w', encoding='utf-8', newline='\n') as f:
        f.write(s)


def inserir_apos(s, padrao, novo, ultimo=True):
    """insere `novo` (linhas) depois da linha que casa `padrao` (a ultima, por padrao)."""
    ms = list(re.finditer(padrao, s, re.M))
    if not ms:
        sys.exit(f'ancora nao achada: {padrao}')
    m = ms[-1] if ultimo else ms[0]
    fim = s.index('\n', m.end()) + 1
    return s[:fim] + novo + s[fim:]


def regra(png, mw):
    s = ler(RULES)
    alvo = '$(OBJEVENTGFXDIR)/' + png[len('graphics/object_events/pics/'):-4] + '.4bpp'
    pat = re.compile(re.escape(alvo) + r': %\.4bpp: %\.png\n\t\$\(GFX\) \$< \$@ -mwidth \d+ -mheight 4')
    novo = f'{alvo}: %.4bpp: %.png\n\t$(GFX) $< $@ -mwidth {mw} -mheight 4'
    if pat.search(s):
        s = pat.sub(novo.replace('\\', '\\\\'), s)
    else:
        s = s.rstrip('\n') + '\n\n' + novo + '\n'
    gravar(RULES, s)


def constantes(K, novo_pal):
    s = ler(CONST)
    if not re.search(rf'#define OBJ_EVENT_GFX_{K}\s', s):
        n = int(re.search(r'#define NUM_OBJ_EVENT_GFX\s+(\d+)', s).group(1))
        s = s.replace('\n// NOTE: The maximum amount of object events',
                      f'#define OBJ_EVENT_GFX_{K:<30} {n}\n\n// NOTE: The maximum amount of object events', 1)
        s = re.sub(r'(#define NUM_OBJ_EVENT_GFX\s+)\d+', lambda m: m.group(1) + str(n + 1), s)
    if novo_pal and not re.search(rf'#define OBJ_EVENT_PAL_TAG_{K}\s', s):
        # faixa dos personagens: 0x11xx abaixo de OBJ_EVENT_PAL_TAG_NONE (0x11FF)
        tags = [int(v, 16) for v in re.findall(r'#define OBJ_EVENT_PAL_TAG_\w+\s+0x(11[0-9A-Ea-e][0-9A-Fa-f])\b', s)]
        s = inserir_apos(s, rf'^#define OBJ_EVENT_PAL_TAG_\w+\s+0x{max(tags):04X}\b.*$',
                         f'#define OBJ_EVENT_PAL_TAG_{K:<26} 0x{max(tags) + 1:04X}\n')
    gravar(CONST, s)


def graficos(C, png, novo_pal):
    s = ler(GFX)
    base = png[:-4]
    if f'gObjectEventPic_{C}[]' not in s:
        s = inserir_apos(s, rf'^const u32 gObjectEventPic_{ANCORA}\[\].*$',
                         f'const u32 gObjectEventPic_{C}[] = INCBIN_U32("{base}.4bpp");\n')
    if novo_pal and f'gObjectEventPal_{C}[]' not in s:
        s = inserir_apos(s, rf'^const u16 gObjectEventPal_{ANCORA}\[\].*$',
                         f'const u16 gObjectEventPal_{C}[] = INCBIN_U16("{base}.gbapal");\n')
    gravar(GFX, s)


def pic_table(C, mw, n):
    s = ler(PICS)
    corpo = ''.join(f'    overworld_frame(gObjectEventPic_{C}, {mw}, 4, {i}),\n' for i in range(n))
    bloco = f'static const struct SpriteFrameImage sPicTable_{C}[] = {{\n{corpo}}};\n'
    pat = re.compile(rf'static const struct SpriteFrameImage sPicTable_{C}\[\] = \{{\n.*?\n\}};\n', re.S)
    if pat.search(s):
        s = pat.sub(lambda m: bloco, s)
    else:
        m = re.search(rf'static const struct SpriteFrameImage sPicTable_{ANCORA}\[\] = \{{\n.*?\n\}};\n', s, re.S)
        s = s[:m.end()] + '\n' + bloco + s[m.end():]
    gravar(PICS, s)


def info(C, K, fw, n, pal_tag):
    s = ler(INFO)
    size, oam = (256, '16x32') if fw == 16 else (512, '32x32')
    anim = 'sAnimTable_StandardAsym' if n == 12 else 'sAnimTable_Standard'
    linha = re.compile(rf'^const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{C} = \{{(TAG_NONE, )(\w+)(, \w+, )\d+, \d+, \d+(, [^,]+, [^,]+, [^,]+, [^,]+, [^,]+, )'
                       rf'&gObjectEventBaseOam_\w+, sOamTables_\w+, sAnimTable_\w+(, .*)$', re.M)
    multi = re.compile(rf'const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{C} = \{{\n.*?\n\}};', re.S)
    if linha.search(s):
        s = linha.sub(lambda m: f'const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{C} = {{{m.group(1)}{pal_tag}'
                      f'{m.group(3)}{size}, {fw}, 32{m.group(4)}&gObjectEventBaseOam_{oam}, sOamTables_{oam}, {anim}{m.group(5)}', s)
    elif multi.search(s):
        def ajusta(m):
            b = m.group(0)
            for campo, v in (('paletteTag', pal_tag), ('size', size), ('width', fw), ('height', 32),
                             ('oam', f'&gObjectEventBaseOam_{oam}'), ('subspriteTables', f'sOamTables_{oam}'), ('anims', anim)):
                b = re.sub(rf'(\.{campo} = )[^,]+,', lambda mm: f'{mm.group(1)}{v},', b)
            return b
        s = multi.sub(ajusta, s)
    else:
        s = inserir_apos(s, rf'^const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{ANCORA} = .*$',
                         f'const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_{C} = {{TAG_NONE, {pal_tag}, '
                         f'OBJ_EVENT_PAL_TAG_NONE, {size}, {fw}, 32, 4, SHADOW_SIZE_M, FALSE, FALSE, TRACKS_FOOT, '
                         f'&gObjectEventBaseOam_{oam}, sOamTables_{oam}, {anim}, sPicTable_{C}, gDummySpriteAffineAnimTable}};\n')
    gravar(INFO, s)


def ponteiros(C, K):
    s = ler(PTRS)
    if f'gObjectEventGraphicsInfo_{C};' not in s:
        s = inserir_apos(s, rf'^extern const struct ObjectEventGraphicsInfo\s+gObjectEventGraphicsInfo_{ANCORA};$',
                         f'extern const struct ObjectEventGraphicsInfo  gObjectEventGraphicsInfo_{C};\n')
    if f'[OBJ_EVENT_GFX_{K}]' not in s:
        s = inserir_apos(s, rf'^\s*\[OBJ_EVENT_GFX_BRENDAN_HOENN\] = .*$',
                         f'    {"[OBJ_EVENT_GFX_" + K + "] =":<46}&gObjectEventGraphicsInfo_{C},\n')
    gravar(PTRS, s)


def paleta(C, K):
    s = ler(MOVE)
    if f'gObjectEventPal_{C},' not in s:
        s = inserir_apos(s, rf'^\s*\{{gObjectEventPal_{ANCORA},.*$',
                         f'    {{{"gObjectEventPal_" + C + ",":<40} OBJ_EVENT_PAL_TAG_{K}}},\n')
    gravar(MOVE, s)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('nome')
    ap.add_argument('png')
    ap.add_argument('--quadro', type=int, choices=(16, 32), required=True)
    ap.add_argument('--const')
    ap.add_argument('--c')
    a = ap.parse_args()
    C = a.c or a.nome
    K = a.const or re.sub(r'(?<!^)(?=[A-Z])', '_', C).upper()
    png = a.png.replace('\\', '/')
    im = Image.open(os.path.join(ROOT, png))
    if im.mode != 'P' or im.height != 32 or im.width % a.quadro:
        sys.exit(f'{png}: {im.mode} {im.size} nao e folha indexada de quadros {a.quadro}x32')
    n = im.width // a.quadro
    if n not in (9, 12):
        sys.exit(f'{png}: {n} quadros (esperado 9 ou 12)')
    mw = a.quadro // 8
    # paleta: a propria do personagem; se hoje usa a compartilhada de NPC, passa a ter uma
    s = ler(INFO)
    m = re.search(rf'gObjectEventGraphicsInfo_{C} = \{{\s*(?:TAG_NONE, |\.tileTag = TAG_NONE,\s*\.paletteTag = )(\w+)', s)
    atual = m.group(1) if m else None
    pal_tag = f'OBJ_EVENT_PAL_TAG_{K}'
    novo_pal = atual != pal_tag or not re.search(rf'#define {pal_tag}\s', ler(CONST))
    regra(png, mw)
    constantes(K, novo_pal)
    graficos(C, png, novo_pal)
    pic_table(C, mw, n)
    info(C, K, a.quadro, n, pal_tag)
    ponteiros(C, K)
    if novo_pal:
        paleta(C, K)
    print(f'{C}: OBJ_EVENT_GFX_{K}, {n} quadros {a.quadro}x32' + (f', paleta nova {pal_tag}' if novo_pal else ''))


if __name__ == '__main__':
    main()
