#!/usr/bin/env python3
"""Importa um mapa do pokehns (HnS 2.0.6) por cima do mapa homônimo do
SoulGold (adoção do Kanto — Fases 2/3 do plano).

Por mapa:
  1. map.json e scripts.inc do P → transformados (tira _HNS/_hns,
     OBJ_EVENT_GFX_MON_BASE+SPECIES_X → OBJ_EVENT_GFX_SPECIES(X)) e gravados
     por cima dos do S. scripts.pory antigo do S é apagado (o .inc novo é a
     fonte).
  2. map.bin/border.bin do layout do P → convertidos (converte_kanto_hns)
     para a pasta de layout do S.
  3. Entrada do S em data/layouts/layouts.json → width/height do P e
     tilesets do P (gTileset_*_Hns, que precisam estar registrados antes).

events.inc/header.inc/connections.inc são regenerados pelo build (mapjson).

Uso: python3 dev_scripts/importa_mapa_hns.py Mapa1 [Mapa2 ...]
     (nomes sem sufixo, como em .claude/pokehns/KANTO_ESCOPO.txt)
"""
import json
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "dev_scripts"))
from converte_kanto_hns import convert_map_bin, convert_border_bin  # noqa: E402

P = os.path.join(REPO, ".filetransfer", "pokehns-expansion-Release-v2.0.6")

MON_BASE_RE = re.compile(r"OBJ_EVENT_GFX_MON_BASE\s*\+\s*SPECIES_([A-Z0-9_]+)")
# _HNS/_hns somem também no MEIO de identificador (PalletTown_hns_MapScripts).
HNS_UPPER_RE = re.compile(r"_HNS(?=_|\b)")
HNS_LOWER_RE = re.compile(r"_hns(?=_|\b)")


def transforma(texto: str) -> str:
    texto = MON_BASE_RE.sub(r"OBJ_EVENT_GFX_SPECIES(\1)", texto)
    texto = HNS_UPPER_RE.sub("", texto)
    texto = HNS_LOWER_RE.sub("", texto)
    return texto


def layout_dirs(mapa: str) -> tuple[str, str, dict]:
    """(dir_layout_P, dir_layout_S, entrada_P) a partir dos layouts.json."""
    pj = json.load(open(os.path.join(P, "data/maps", mapa + "_hns", "map.json")))
    p_layout_id = pj["layout"]
    s_layout_id = transforma(p_layout_id)

    p_layouts = json.load(open(os.path.join(P, "data/layouts/layouts.json")))
    s_layouts = json.load(open(os.path.join(REPO, "data/layouts/layouts.json")))
    p_entry = next(l for l in p_layouts["layouts"] if l and l.get("id") == p_layout_id)
    s_entry = next(l for l in s_layouts["layouts"] if l and l.get("id") == s_layout_id)
    return (
        os.path.join(P, os.path.dirname(p_entry["blockdata_filepath"])),
        os.path.join(REPO, os.path.dirname(s_entry["blockdata_filepath"])),
        p_entry,
    )


def importa(mapa: str, s_layouts: dict) -> None:
    p_dir = os.path.join(P, "data/maps", mapa + "_hns")
    s_dir = os.path.join(REPO, "data/maps", mapa)
    if not os.path.isdir(p_dir):
        sys.exit(f"[ERRO] {p_dir} não existe")
    if not os.path.isdir(s_dir):
        sys.exit(f"[ERRO] {s_dir} não existe (mapa novo? crie antes)")

    # local_ids nomeados do map.json atual do S: código fora do mapa pode
    # referenciá-los (ex. heal_locations -> LOCALID_PROF_OAK), e o HnS não
    # nomeia objetos. Preserva religando por graphics_id (primeiro que casar).
    s_json_path = os.path.join(s_dir, "map.json")
    locais_antigos = []
    if os.path.exists(s_json_path):
        for o in json.load(open(s_json_path)).get("object_events", []):
            if o.get("local_id"):
                locais_antigos.append((o["local_id"], o["graphics_id"]))

    # 1. map.json + scripts.inc
    for nome in ("map.json", "scripts.inc"):
        src = os.path.join(p_dir, nome)
        if not os.path.exists(src):
            sys.exit(f"[ERRO] falta {src}")
        texto = transforma(open(src, encoding="utf-8").read())
        open(os.path.join(s_dir, nome), "w", encoding="utf-8").write(texto)

    if locais_antigos:
        novo = json.load(open(s_json_path))
        objs = novo.get("object_events", [])
        usados = set()
        for lid, gfx in locais_antigos:
            alvo = next((o for i, o in enumerate(objs)
                         if i not in usados and o.get("graphics_id") == gfx
                         and not o.get("local_id")), None)
            if alvo is not None:
                alvo["local_id"] = lid
                usados.add(objs.index(alvo))
                print(f"  [{mapa}] local_id {lid} religado em {gfx}")
            else:
                print(f"  [{mapa}] AVISO: local_id {lid} ({gfx}) sem objeto "
                      f"correspondente no mapa importado — religar à mão")
        with open(s_json_path, "w", encoding="utf-8") as f:
            json.dump(novo, f, indent=2)
            f.write("\n")
    pory = os.path.join(s_dir, "scripts.pory")
    if os.path.exists(pory):
        os.remove(pory)
        print(f"  [{mapa}] scripts.pory antigo removido (o .inc importado é a fonte)")

    # 2. layout binário
    p_lay, s_lay, p_entry = layout_dirs(mapa)
    convert_map_bin(os.path.join(p_lay, "map.bin"), os.path.join(s_lay, "map.bin"))
    p_border = os.path.join(p_lay, "border.bin")
    if os.path.exists(p_border):
        convert_border_bin(p_border, os.path.join(s_lay, "border.bin"))

    # 3. entrada no layouts.json do S
    s_layout_id = transforma(p_entry["id"])
    entry = next(l for l in s_layouts["layouts"] if l and l.get("id") == s_layout_id)
    antes = (entry["width"], entry["height"], entry["primary_tileset"], entry["secondary_tileset"])
    entry["width"] = p_entry["width"]
    entry["height"] = p_entry["height"]
    entry["primary_tileset"] = p_entry["primary_tileset"]
    entry["secondary_tileset"] = p_entry["secondary_tileset"]
    depois = (entry["width"], entry["height"], entry["primary_tileset"], entry["secondary_tileset"])
    print(f"  [{mapa}] layout {s_layout_id}: {antes} -> {depois}")


def main() -> None:
    mapas = sys.argv[1:]
    if not mapas:
        sys.exit(__doc__)
    s_layouts_path = os.path.join(REPO, "data/layouts/layouts.json")
    s_layouts = json.load(open(s_layouts_path))
    for m in mapas:
        importa(m, s_layouts)
    with open(s_layouts_path, "w", encoding="utf-8") as f:
        json.dump(s_layouts, f, indent=2)
        f.write("\n")
    print(f"[OK] {len(mapas)} mapa(s) importados; layouts.json atualizado")


if __name__ == "__main__":
    main()
