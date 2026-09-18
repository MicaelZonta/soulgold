#!/usr/bin/env python3
"""Lista os TRAINER_IDs realmente livres agora.

    python3 .claude/skills/adicionar-batalha-npc/ids_livres.py
    python3 .claude/skills/adicionar-batalha-npc/ids_livres.py --todos

Por que existe: a flag de "derrotado" de um treinador e derivada do ID
(TRAINER_FLAGS_START 0x500 + ID). Escolher o ID E escolher a flag. Uma faixa
anotada num guia envelhece assim que alguem cria um treinador novo - e usar
um ID ja tomado faz o treinador compartilhar flag com outro evento
(vencer um dispara o outro). Entao confira aqui, nao na memoria.

Um ID conta como livre quando:
  - ID < MAX_TRAINERS_COUNT (acima disso a flag sai do espaco de treinador), e
  - toda constante nele comeca com TRAINER_UNUSED (inclui TRAINER_UNUSEDNAME_), e
  - nao existe bloco "=== TRAINER_X ===" em src/data/trainers.party, e
  - nenhuma FLAG_* nomeada ocupa a flag 0x500+ID (e assim que a faixa
    RECLAIMED_TRAINER_FLAGS_* aparece - checamos o arquivo, nao a constante,
    para pegar tambem qualquer reaproveitamento futuro fora dela).

Ainda assim, antes de fechar num ID, confirme que ele nao e citado em lugar
nenhum alem do opponents.h:

    grep -rn "\\bTRAINER_UNUSED_XXX\\b" data/ src/ include/ | grep -v opponents.h
"""

import os
import re
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
TRAINER_FLAGS_START = 0x500


def main():
    mostrar_todos = "--todos" in sys.argv

    ids = {}
    for ln in open(os.path.join(ROOT, "include/constants/opponents.h")):
        m = re.match(r"#define\s+(TRAINER_\w+)\s+(\d+)", ln)
        if m:
            ids.setdefault(int(m.group(2)), []).append(m.group(1))

    party = open(os.path.join(ROOT, "src/data/trainers.party")).read()
    com_time = set(re.findall(r"^===\s*(TRAINER_\w+)\s*===", party, re.M))

    flags_txt = open(os.path.join(ROOT, "include/constants/flags.h")).read()
    opp_txt = open(os.path.join(ROOT, "include/constants/opponents.h")).read()

    m = re.search(r"#define\s+MAX_TRAINERS_COUNT\s+(\d+)", opp_txt)
    max_trainers = int(m.group(1)) if m else 1164

    # toda flag nomeada que caiu dentro do espaco de treinador: aquele ID
    # pertence a um evento de historia, nao a um treinador.
    flag_tomada = {}
    for ln in flags_txt.splitlines():
        m = re.match(r"#define\s+(FLAG_\w+)\s+(0x[0-9A-Fa-f]+)\s*(//.*)?$", ln.strip())
        if m:
            v = int(m.group(2), 0)
            if TRAINER_FLAGS_START <= v < TRAINER_FLAGS_START + max_trainers:
                flag_tomada[v - TRAINER_FLAGS_START] = m.group(1)

    livres, fora, por_flag = [], [], []
    for i, nomes in ids.items():
        if i == 0:
            continue
        if i >= max_trainers:
            fora.append((i, nomes))
            continue
        if i in flag_tomada:
            por_flag.append((i, flag_tomada[i]))
            continue
        parece_livre = all(n.startswith("TRAINER_UNUSED") for n in nomes)
        tem_time = any(n in com_time for n in nomes)
        if parece_livre and not tem_time:
            livres.append(i)

    livres.sort()

    def faixas(nums):
        out, ini, ant = [], None, None
        for n in nums:
            if ini is None:
                ini = ant = n
            elif n == ant + 1:
                ant = n
            else:
                out.append((ini, ant))
                ini = ant = n
        if ini is not None:
            out.append((ini, ant))
        return out

    print(f"MAX_TRAINERS_COUNT = {max_trainers}  (IDs validos: 1..{max_trainers - 1})")
    if por_flag:
        blocos = faixas(sorted(i for i, _ in por_flag))
        print(f"\n{len(por_flag)} IDs NAO usaveis: a flag virou flag de historia")
        for a, b in blocos:
            print(f"   IDs {a}-{b}  (flags {hex(TRAINER_FLAGS_START + a)}-"
                  f"{hex(TRAINER_FLAGS_START + b)}), ex.: {dict(por_flag)[a]}")
    if fora:
        for i, nomes in sorted(fora):
            print(f"\n{i} = {', '.join(nomes)}: fora do range, NUNCA use")

    print(f"\n{len(livres)} IDs livres, em {len(faixas(livres))} faixas:\n")
    for a, b in faixas(livres):
        n = b - a + 1
        exemplo = ids[a][0]
        print(f"  {a:>5}-{b:<5} ({n:>3} slots)  ex.: {exemplo} -> flag {hex(TRAINER_FLAGS_START + a)}")

    if mostrar_todos:
        print("\ntodos os IDs livres:")
        print("  " + " ".join(str(i) for i in livres))

    print("\nPara usar: renomeie o TRAINER_UNUSED_* daquele ID em")
    print("include/constants/opponents.h, mantendo o numero, e crie o bloco")
    print("=== TRAINER_<NOME> === em src/data/trainers.party.")


if __name__ == "__main__":
    main()
