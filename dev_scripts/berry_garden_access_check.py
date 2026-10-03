#!/usr/bin/env python3
"""Confere que o elenco da horta nunca tranca um canteiro (Route 30).

Roda na raiz do repo:

    python3 dev_scripts/berry_garden_access_check.py

Le o data/maps/Route30/map.json:
  - canteiros = objetos OBJ_EVENT_GFX_BERRY_TREE da horta (x 22..33, y 37..46);
  - elenco    = objetos com flag FLAG_TEMP_HIDE_<quem> (Bram, Laurel, Tilly,
                Bugsy e quem vier depois: Klara, Avery, Peony...).
Poe o elenco INTEIRO de pe ao mesmo tempo e confere, a partir da porta da casa,
que todo canteiro tem um vizinho alcancavel a pe. Bloquear mais tiles nunca
abre caminho, entao passar com todos juntos vale para qualquer horario e dia
da semana.

Colisao e agua saem de .claude/qa/rota.py (bit 11 do map.bin; agua, lago e
ledge pelo comportamento do metatile, que o dump_mapa.py nao mostra: agua tem
colisao 0). Foi assim que o Bugsy de (32,43) apareceu dentro do lago e o Bram
de (31,45) trancou dois canteiros (Parte 8, 03/10/2026).

Sai com 1 e lista os canteiros trancados quando a regra falha.
"""
import json
import os
import sys
from collections import deque

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.join(RAIZ, ".claude/qa"))
import rota  # noqa: E402

MAPA = "Route30"
PORTA = (26, 40)          # o tile de chegada fica logo abaixo do warp (26,39)
AREA = (range(22, 34), range(37, 47))


def main():
    m = json.load(open(os.path.join(RAIZ, f"data/maps/{MAPA}/map.json")))
    w, h, bloqueio, bordas = rota.load(MAPA, objs=set())
    canteiros, elenco = [], {}
    for o in m["object_events"]:
        pos = (o["x"], o["y"])
        if o["graphics_id"] == "OBJ_EVENT_GFX_BERRY_TREE" and o["x"] in AREA[0] and o["y"] in AREA[1]:
            canteiros.append(pos)
        elif o["flag"].startswith("FLAG_TEMP_HIDE_") and o["graphics_id"] != "OBJ_EVENT_GFX_BERRY_TREE":
            elenco[o["flag"][len("FLAG_TEMP_HIDE_"):]] = pos
    erros = []
    for quem, pos in elenco.items():
        if pos in bloqueio:
            erros.append(f"{quem} em {pos}: tile bloqueado ou agua")
    fechado = bloqueio | set(canteiros) | set(elenco.values())
    visto, fila = {PORTA}, deque([PORTA])
    while fila:
        c = fila.popleft()
        for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            n = (c[0] + dx, c[1] + dy)
            if 0 <= n[0] < w and 0 <= n[1] < h and n not in fechado and n not in visto \
                    and frozenset({c, n}) not in bordas:
                visto.add(n)
                fila.append(n)
    for c in canteiros:
        if not any((c[0] + dx, c[1] + dy) in visto for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
            erros.append(f"canteiro {c} trancado com o elenco em {elenco}")
    if erros:
        print("\n".join(erros))
        sys.exit(1)
    print(f"ok: {len(canteiros)} canteiros alcancaveis com {', '.join(f'{k} {v}' for k, v in elenco.items())}")


if __name__ == "__main__":
    main()
