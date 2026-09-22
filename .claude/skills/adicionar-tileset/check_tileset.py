#!/usr/bin/env python3
"""Confere um tileset do SoulGold contra os limites reais de include/fieldmap.h.

    python3 .claude/skills/adicionar-tileset/check_tileset.py secondary/meu_tileset
    python3 .claude/skills/adicionar-tileset/check_tileset.py --all

Nada aqui e adivinhado: os limites sao lidos de include/fieldmap.h e a
conferencia de tile id usa o conteudo real de metatiles.bin.
"""
import json
import os
import re
import struct
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))


def limits():
    src = open(os.path.join(ROOT, "include/fieldmap.h")).read()
    g = lambda n: int(re.search(r"#define %s\s+(\d+)" % n, src).group(1))
    return {n: g(n) for n in (
        "NUM_TILES_IN_PRIMARY", "NUM_TILES_TOTAL",
        "NUM_METATILES_IN_PRIMARY", "NUM_METATILES_TOTAL",
        "NUM_PALS_IN_PRIMARY", "NUM_PALS_TOTAL", "NUM_TILES_PER_METATILE")}


def png_tiles(path):
    d = open(path, "rb").read(26)
    if d[:8] != b"\x89PNG\r\n\x1a\n":
        return None, None, None
    w, h = struct.unpack(">II", d[16:24])
    return (w // 8) * (h // 8), w, h


def registered():
    """{pasta: nome do simbolo} a partir de src/data/tilesets/graphics.h"""
    src = open(os.path.join(ROOT, "src/data/tilesets/graphics.h")).read()
    out = {}
    for sym, folder in re.findall(
            r'gTilesetTiles_(\w+)\[\] = INCBIN_U32\("data/tilesets/([\w/]+)/', src):
        out[folder] = sym
    return out


def check(folder, L, reg, layouts, verbose=True):
    d = os.path.join(ROOT, "data/tilesets", folder)
    is_sec = folder.startswith("secondary/")
    kind = "secundario" if is_sec else "primario"
    problems, notes = [], []

    max_tiles = (L["NUM_TILES_TOTAL"] - L["NUM_TILES_IN_PRIMARY"]) if is_sec \
        else L["NUM_TILES_IN_PRIMARY"]
    max_mt = (L["NUM_METATILES_TOTAL"] - L["NUM_METATILES_IN_PRIMARY"]) if is_sec \
        else L["NUM_METATILES_IN_PRIMARY"]
    tile_base = L["NUM_TILES_IN_PRIMARY"] if is_sec else 0

    # --- tiles.png
    png = os.path.join(d, "tiles.png")
    n_tiles = None
    if not os.path.exists(png):
        problems.append("falta tiles.png")
    else:
        n_tiles, w, h = png_tiles(png)
        if w != 128:
            problems.append(f"tiles.png tem {w}px de largura; tem que ser 128")
        if n_tiles and n_tiles > max_tiles:
            problems.append(
                f"tiles.png tem {n_tiles} tiles, acima do teto de {max_tiles} "
                f"para {kind} — os tiles acima de {max_tiles - 1} nunca chegam na VRAM")

    # --- metatiles.bin / metatile_attributes.bin
    mtb = os.path.join(d, "metatiles.bin")
    atb = os.path.join(d, "metatile_attributes.bin")
    n_mt = None
    if not os.path.exists(mtb):
        problems.append("falta metatiles.bin")
    else:
        raw = open(mtb, "rb").read()
        per = L["NUM_TILES_PER_METATILE"] * 2
        if len(raw) % per:
            problems.append(
                f"metatiles.bin tem {len(raw)} bytes, nao multiplo de {per} "
                f"({L['NUM_TILES_PER_METATILE']} tiles/metatile, triple layer)")
        n_mt = len(raw) // per
        if n_mt > max_mt:
            problems.append(f"{n_mt} metatiles, acima do teto de {max_mt} para {kind}")

        ids = [struct.unpack("<H", raw[i:i + 2])[0] & 0x3FF for i in range(0, len(raw), 2)]
        nz = [i for i in ids if i]
        lo, hi = (min(nz), max(ids)) if nz else (0, 0)
        notes.append(f"tile ids usados: {lo}..{hi}")
        if hi >= L["NUM_TILES_TOTAL"]:
            problems.append(f"metatiles referenciam tile {hi} >= NUM_TILES_TOTAL")
        if is_sec:
            own = [i for i in nz if i >= tile_base]
            if own and n_tiles and max(own) - tile_base >= n_tiles:
                problems.append(
                    f"metatiles usam o tile {max(own)} (indice {max(own) - tile_base} "
                    f"dentro do secundario), mas tiles.png so tem {n_tiles}")
            # o classico: tileset portado com o split de 512
            if nz and 512 <= lo < tile_base:
                problems.append(
                    f"menor tile id proprio e {lo}: cheira a tileset portado com "
                    f"NUM_TILES_IN_PRIMARY=512. Aqui o split e {tile_base} — "
                    f"tudo sai deslocado {tile_base - 512} tiles")
            elif nz and lo < tile_base:
                notes.append(
                    f"usa tiles do primario ({lo} < {tile_base}) — normal se for de proposito")
        else:
            if hi >= L["NUM_TILES_IN_PRIMARY"]:
                notes.append(
                    f"metatiles do primario referenciam o tile {hi}, que mora na faixa "
                    f"do secundario — o desenho muda conforme o secundario pareado")

    if os.path.exists(atb) and n_mt:
        n_at = os.path.getsize(atb) // 2
        if n_at != n_mt:
            problems.append(
                f"metatile_attributes.bin tem {n_at} entradas mas metatiles.bin tem {n_mt}")
    elif not os.path.exists(atb):
        problems.append("falta metatile_attributes.bin")

    # --- paletas
    pals = sorted(f for f in os.listdir(os.path.join(d, "palettes"))
                  if f.endswith(".pal")) if os.path.isdir(os.path.join(d, "palettes")) else []
    need = L["NUM_PALS_TOTAL"] if is_sec else L["NUM_PALS_IN_PRIMARY"]
    if len(pals) < need:
        problems.append(
            f"so {len(pals)} arquivos .pal; {kind} precisa de pelo menos {need} "
            f"(00..{need - 1:02d})")
    if is_sec:
        notes.append(
            f"visiveis em jogo: paletas {L['NUM_PALS_IN_PRIMARY']}.."
            f"{L['NUM_PALS_TOTAL'] - 1} (as 00..{L['NUM_PALS_IN_PRIMARY'] - 1:02d} "
            f"sao ignoradas em secundario)")

    # --- registro em C e uso em layout
    sym = reg.get(folder)
    if not sym:
        problems.append("nao aparece em src/data/tilesets/graphics.h")
    else:
        hdr = open(os.path.join(ROOT, "src/data/tilesets/headers.h")).read()
        mts = open(os.path.join(ROOT, "src/data/tilesets/metatiles.h")).read()
        if f"gMetatiles_{sym}[]" not in mts:
            problems.append(f"gMetatiles_{sym} ausente de metatiles.h")
        m = re.search(r"const struct Tileset gTileset_%s =\s*\{(.*?)\};" % re.escape(sym),
                      hdr, re.S)
        if not m:
            problems.append(f"gTileset_{sym} ausente de headers.h")
        else:
            body = m.group(1)
            comp = "isCompressed = TRUE" in body
            incbin = re.search(
                r'gTilesetTiles_%s\[\] = INCBIN_U32\("([^"]+)"' % re.escape(sym),
                open(os.path.join(ROOT, "src/data/tilesets/graphics.h")).read())
            fast = incbin and incbin.group(1).endswith((".fastSmol", ".smol"))
            if comp != bool(fast):
                problems.append(
                    "isCompressed=%s mas o INCBIN aponta para %s — compactado pede "
                    "tiles.4bpp.fastSmol; cru pede tiles.4bpp"
                    % (comp, incbin.group(1).rsplit("/", 1)[-1] if incbin else "?"))
            want_sec = "isSecondary = TRUE" in body
            if want_sec != is_sec:
                problems.append(
                    f"isSecondary={want_sec} mas o tileset mora em {folder.split('/')[0]}/")
            if f"gTileset_{sym}" not in layouts:
                notes.append("nenhum layout usa esse tileset — --gc-sections corta "
                             "ele da ROM ate voce ligar em data/layouts/layouts.json")

    if verbose or problems:
        head = f"{folder}  [{kind}]"
        if n_tiles is not None:
            head += f"  tiles {n_tiles}/{max_tiles}"
        if n_mt is not None:
            head += f"  metatiles {n_mt}/{max_mt}"
        head += f"  pals {len(pals)}"
        print(head)
        for n in notes:
            print("   . " + n)
        for p in problems:
            print("   X " + p)
        print()
    return not problems


def main():
    L = limits()
    reg = registered()
    layouts = open(os.path.join(ROOT, "data/layouts/layouts.json")).read()
    args = sys.argv[1:]
    if not args:
        print(__doc__)
        return 1
    if args[0] == "--all":
        targets = sorted(
            f"{k}/{n}" for k in ("primary", "secondary")
            for n in os.listdir(os.path.join(ROOT, "data/tilesets", k))
            if os.path.isdir(os.path.join(ROOT, "data/tilesets", k, n)))
        bad = [t for t in targets if not check(t, L, reg, layouts, verbose=False)]
        print(f"{len(targets)} tilesets conferidos, {len(bad)} com problema")
        return 0
    ok = all(check(t.strip("/"), L, reg, layouts) for t in args)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
