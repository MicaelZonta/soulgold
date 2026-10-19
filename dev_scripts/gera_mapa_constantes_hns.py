#!/usr/bin/env python3
"""Gera o mapa de constantes para a adoção do Kanto do HnS (Fase 1.3).

Varre scripts.inc + map.json dos mapas do escopo (KANTO_ESCOPO.txt) no
pokehns, normaliza os sufixos _HNS e classifica cada constante:
  - "rename": existe no S após tirar _HNS (resolve com sed mecânico);
  - "ok": já existe com o mesmo nome;
  - "faltante": precisa de alocação/decisão (flags, vars, trainers, gfx,
    itens/TMs) — com proposta de número para flags (0x1097+) e vars (0x4132+).

Saída: .claude/pokehns/mapa_constantes.json e .md (revisão humana).
Uso: python3 dev_scripts/gera_mapa_constantes_hns.py [raiz_do_pokehns]
"""
import json
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
P = Path(sys.argv[1]) if len(sys.argv) > 1 else REPO / ".filetransfer/pokehns-expansion-Release-v2.0.6"
ESCOPO = REPO / ".claude/pokehns/KANTO_ESCOPO.txt"
OUT_DIR = REPO / ".claude/pokehns"

PREFIXES = ("FLAG_", "VAR_", "TRAINER_", "OBJ_EVENT_GFX_", "ITEM_", "SPECIES_", "MUS_", "SE_", "MAP_")
TOKEN_RE = re.compile(r"\b(" + "|".join(PREFIXES) + r")[A-Z0-9_]+\b")
FLAG_PROX = 0x1097   # CUSTOM_FLAGS: próxima livre (flags.h, ver skill alocar-flag)
VAR_PROX = 0x4132    # vars.h: comentário "PROXIMA VAR NOVA"


def tokens_do_escopo() -> dict[str, set[str]]:
    """token -> mapas que o usam."""
    mapas = [l.strip() for l in ESCOPO.read_text().splitlines()
             if l.strip() and not l.startswith("#")]
    uso: dict[str, set[str]] = defaultdict(set)
    faltando = []
    for m in mapas:
        d = P / "data/maps" / f"{m}_hns"
        if not d.is_dir():
            faltando.append(m)
            continue
        for fname in ("scripts.inc", "map.json"):
            f = d / fname
            if f.exists():
                for t in TOKEN_RE.findall(f.read_text(errors="replace")):
                    pass
                for mt in re.finditer(TOKEN_RE, f.read_text(errors="replace")):
                    uso[mt.group(0)].add(m)
    if faltando:
        print(f"AVISO: {len(faltando)} mapas do escopo sem pasta _hns no P: {faltando[:5]}")
    return uso


def nomes_definidos_no_s() -> set[str]:
    nomes: set[str] = set()
    define_re = re.compile(r"#define\s+([A-Z0-9_]+)")
    enum_re = re.compile(r"^\s*([A-Z][A-Z0-9_]*)\s*(?:=[^,]*)?,")
    arquivos = [
        "include/constants/flags.h", "include/constants/vars.h",
        "include/constants/opponents.h", "include/constants/event_objects.h",
        "include/constants/items.h", "include/constants/songs.h",
        "include/constants/species.h", "include/constants/map_groups.h",
        "include/constants/map_types.h", "include/constants/map_scripts.h",
    ]
    for a in arquivos:
        p = REPO / a
        if not p.exists():
            continue
        txt = p.read_text(errors="replace")
        nomes.update(define_re.findall(txt))
        for line in txt.splitlines():
            m = enum_re.match(line)
            if m:
                nomes.add(m.group(1))
    # ITEM_TM_<GOLPE> gerados por macro a partir do FOREACH_TM do S
    tms = REPO / "include/constants/tms_hms.h"
    if tms.exists():
        for mv in re.findall(r"^\s*F\(([A-Z0-9_]+)\)", tms.read_text(), re.M):
            nomes.add("ITEM_TM_" + mv)
            nomes.add("ITEM_HM_" + mv)
    return nomes


def normaliza(token: str) -> str:
    return token[:-4] if token.endswith("_HNS") else token


def main() -> None:
    uso = tokens_do_escopo()
    s_nomes = nomes_definidos_no_s()

    resultado = {"ok": [], "rename": [], "faltante": defaultdict(list)}
    for token in sorted(uso):
        base = normaliza(token)
        if token in s_nomes:
            resultado["ok"].append(token)
        elif base in s_nomes:
            resultado["rename"].append(token)
        else:
            categoria = next(p for p in PREFIXES if base.startswith(p))
            resultado["faltante"][categoria].append(
                {"token": token, "base": base, "n_mapas": len(uso[token]),
                 "mapas": sorted(uso[token])[:4]})

    # propostas de número
    for i, e in enumerate(resultado["faltante"].get("FLAG_", [])):
        e["proposta"] = f"0x{FLAG_PROX + i:X}"
    for i, e in enumerate(resultado["faltante"].get("VAR_", [])):
        e["proposta"] = f"0x{VAR_PROX + i:X}"

    OUT_DIR.joinpath("mapa_constantes.json").write_text(
        json.dumps(resultado, indent=1, ensure_ascii=False, default=list))

    linhas = ["# Mapa de constantes — Kanto do HnS (gerado)", ""]
    linhas.append(f"- Já existem no S: **{len(resultado['ok'])}**")
    linhas.append(f"- Resolvem com rename `_HNS` → sem sufixo: **{len(resultado['rename'])}**")
    tot_falt = sum(len(v) for v in resultado["faltante"].values())
    linhas.append(f"- Faltantes (alocar/decidir): **{tot_falt}**")
    for cat, lst in sorted(resultado["faltante"].items()):
        linhas.append(f"\n## {cat} faltantes ({len(lst)})\n")
        linhas.append("| token | proposta | mapas que usam |")
        linhas.append("|---|---|---|")
        for e in lst:
            linhas.append(
                f"| `{e['token']}` | {e.get('proposta','—')} | "
                f"{e['n_mapas']}: {', '.join(e['mapas'])} |")
    OUT_DIR.joinpath("mapa_constantes.md").write_text("\n".join(linhas) + "\n")

    print(f"ok={len(resultado['ok'])} rename={len(resultado['rename'])} faltantes={tot_falt}")
    for cat, lst in sorted(resultado["faltante"].items()):
        print(f"  {cat}: {len(lst)}")
    print(f"Saida: {OUT_DIR/'mapa_constantes.md'}")


if __name__ == "__main__":
    main()
