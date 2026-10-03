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

A Klara (assalto da manha, parte 11) e o visitante da noite (Ato 2, parte 12)
ficam DE PROPOSITO na frente de um canteiro e vao embora na cena: ficam fora da
conta acima, mas o jogador tem de alcancar um vizinho de cada um.
Para ela a regra e outra: em cada posicao da tabela sKlaraSpots
(src/berry_garden.c), com o resto do elenco de pe, o jogador alcanca um tile
vizinho dela (para falar) e ela nao esta em tile bloqueado nem em cima de alguem.

Sai com 1 e lista os canteiros trancados quando a regra falha.
"""
import json
import os
import re
import sys
from collections import deque

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.join(RAIZ, ".claude/qa"))
import rota  # noqa: E402

MAPA = "Route30"
PORTA = (26, 40)            # o tile de chegada fica logo abaixo do warp (26,39)
SO_NA_HORA = {"KLARA", "SPECTRIER"}  # de pe na frente de um canteiro so durante a cena
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
    fixos = {k: v for k, v in elenco.items() if k not in SO_NA_HORA}

    def alcance(extra):
        fechado = bloqueio | set(canteiros) | set(fixos.values()) | set(extra)
        visto, fila = {PORTA}, deque([PORTA])
        while fila:
            c = fila.popleft()
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                n = (c[0] + dx, c[1] + dy)
                if 0 <= n[0] < w and 0 <= n[1] < h and n not in fechado and n not in visto \
                        and frozenset({c, n}) not in bordas:
                    visto.add(n)
                    fila.append(n)
        return visto

    visto = alcance(())
    for c in canteiros:
        if not any((c[0] + dx, c[1] + dy) in visto for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
            erros.append(f"canteiro {c} trancado com o elenco em {elenco}")
    src = open(os.path.join(RAIZ, "src/berry_garden.c")).read()
    tabela = src[src.index("sKlaraSpots[] ="):]
    tabela = tabela[:tabela.index("};")]
    spots = [(int(x), int(y)) for x, y in re.findall(r"\{\s*(\d+),\s*(\d+),\s*MOVEMENT_TYPE", tabela)]
    if len(spots) != len(canteiros) - 1:   # menos o canteiro da Laurel
        erros.append(f"sKlaraSpots tem {len(spots)} posicoes para {len(canteiros) - 1} canteiros da horta")
    for k in spots:
        if k in bloqueio or k in set(canteiros) or k in fixos.values():
            erros.append(f"Klara em {k}: tile bloqueado, canteiro ou alguem do elenco")
            continue
        perto = alcance([k])
        if not any((k[0] + dx, k[1] + dy) in perto for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
            erros.append(f"Klara em {k}: o jogador nao chega ate ela")
    for quem in SO_NA_HORA - {"KLARA"}:
        k = elenco.get(quem)
        if k is None:
            continue
        perto = alcance([k])
        if not any((k[0] + dx, k[1] + dy) in perto for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))):
            erros.append(f"{quem} em {k}: o jogador nao chega ate ele")
    if erros:
        print("\n".join(erros))
        sys.exit(1)
    print(f"ok: {len(canteiros)} canteiros alcancaveis com {', '.join(f'{k} {v}' for k, v in fixos.items())}; "
          f"Klara alcancavel nas {len(spots)} posicoes")


if __name__ == "__main__":
    main()
