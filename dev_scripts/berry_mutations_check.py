#!/usr/bin/env python3
"""Confere a tabela de cruzamento de berries (sBerryMutations, src/berry.c).

Roda na raiz do repo:

    python3 dev_scripts/berry_mutations_check.py

Regras (.claude/berry_master/REI_DA_COLHEITA.md secao 4):
  1. cabe em 6 bits (no maximo 63 linhas; o save guarda indice + 1);
  2. nenhum par de pais se repete, em qualquer ordem;
  3. nenhuma berry tem duas receitas, e nenhuma das 8 iniciais tem receita;
  4. toda berry de Cheri a Maranga, menos a Enigma, e inicial ou tem receita;
  5. toda receita e alcancavel a partir das 8 iniciais;
  6. a geracao de cada berry (quantos cruzamentos a separam das iniciais)
     e a da tabela do secao 4.2 do design, e as receitas sao as mesmas.

Sai com 1 e lista os erros quando alguma regra falha.
"""
import os
import re
import sys

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
BERRY_C = os.path.join(RAIZ, "src/berry.c")
ITEMS_H = os.path.join(RAIZ, "include/constants/items.h")
DESIGN = os.path.join(RAIZ, ".claude/berry_master/REI_DA_COLHEITA.md")

INICIAIS = ["CHERI", "CHESTO", "PECHA", "RAWST", "ASPEAR", "LEPPA", "ORAN", "PERSIM"]


def ler(caminho):
    with open(caminho, encoding="utf-8") as f:
        return f.read()


def berries_do_enum():
    """Nomes de CHERI a MARANGA, na ordem do enum (sem a Enigma do e-Reader)."""
    texto = ler(ITEMS_H)
    nomes = re.findall(r"^\s*ITEM_(\w+)_BERRY\s*=\s*(?:FIRST_BERRY_INDEX|\d+),", texto, re.M)
    fim = nomes.index("MARANGA")
    return nomes[: fim + 1]


def tabela_do_c():
    texto = ler(BERRY_C)
    corpo = re.search(r"static const u8 sBerryMutations\[\]\[3\] = \{(.*?)\n\};", texto, re.S).group(1)
    linhas = re.findall(
        r"\{ITEM_TO_BERRY\(ITEM_(\w+)_BERRY\),\s*ITEM_TO_BERRY\(ITEM_(\w+)_BERRY\),\s*ITEM_TO_BERRY\(ITEM_(\w+)_BERRY\)\}",
        corpo,
    )
    return [(a, b, c) for a, b, c in linhas]


def tabela_do_design():
    """(geracao, berry, pai1, pai2) de cada linha do secao 4.2."""
    texto = ler(DESIGN)
    secao = texto[texto.index("### 4.2 Todas as receitas"):texto.index("## 5.")]
    linhas = re.findall(r"^\|\s*(\d)\s*\|\s*\*\*(\w+)\*\*\s*\|\s*(\w+)\s*\+\s*(\w+)\s*\|", secao, re.M)
    return [(int(g), b.upper(), p1.upper(), p2.upper()) for g, b, p1, p2 in linhas]


def geracoes(receitas):
    """Berry -> geracao, por ponto fixo a partir das iniciais."""
    gen = {b: 0 for b in INICIAIS}
    mudou = True
    while mudou:
        mudou = False
        for a, b, c in receitas:
            if a in gen and b in gen:
                g = max(gen[a], gen[b]) + 1
                if gen.get(c, 99) > g:
                    gen[c] = g
                    mudou = True
    return gen


def main():
    erros = []
    todas = berries_do_enum()
    receitas = tabela_do_c()

    if len(receitas) > 63:
        erros.append("%d receitas: nao cabem em 6 bits (maximo 63)" % len(receitas))

    pares = {}
    for a, b, c in receitas:
        chave = frozenset((a, b))
        if chave in pares:
            erros.append("par %s + %s repetido: da %s e %s" % (a, b, pares[chave], c))
        pares[chave] = c
        for nome in (a, b, c):
            if nome not in todas:
                erros.append("%s nao e uma berry de Cheri a Maranga" % nome)

    saidas = {}
    for a, b, c in receitas:
        if c in INICIAIS:
            erros.append("%s e inicial e nao pode ter receita (%s + %s)" % (c, a, b))
        if c in saidas:
            erros.append("%s tem duas receitas: %s e %s + %s" % (c, saidas[c], a, b))
        saidas[c] = "%s + %s" % (a, b)

    for nome in todas:
        if nome == "ENIGMA":
            if nome in saidas:
                erros.append("a Enigma nao pode ter receita (%s)" % saidas[nome])
            continue
        if nome not in INICIAIS and nome not in saidas:
            erros.append("%s nao e inicial e nao tem receita" % nome)

    gen = geracoes(receitas)
    for a, b, c in receitas:
        if c not in gen:
            erros.append("%s (%s + %s) nao e alcancavel a partir das iniciais" % (c, a, b))

    design = tabela_do_design()
    if len(design) != len(receitas):
        erros.append("design tem %d receitas e o codigo %d" % (len(design), len(receitas)))
    for g, berry, p1, p2 in design:
        if berry not in saidas:
            erros.append("design: %s nao tem receita no codigo" % berry)
            continue
        if frozenset((p1, p2)) != frozenset(saidas[berry].split(" + ")):
            erros.append("design: %s = %s + %s, codigo: %s" % (berry, p1, p2, saidas[berry]))
        if gen.get(berry) != g:
            erros.append("design: %s e geracao %d, o codigo da %s" % (berry, g, gen.get(berry)))

    if erros:
        print("berry_mutations_check: %d erro(s)" % len(erros))
        for e in erros:
            print("  - " + e)
        return 1

    por_geracao = {}
    for b, g in gen.items():
        por_geracao.setdefault(g, []).append(b)
    resumo = ", ".join("%d: %d" % (g, len(por_geracao[g])) for g in sorted(por_geracao))
    print("berry_mutations_check: ok - %d receitas, %d berries alcancaveis (geracao: %s)"
          % (len(receitas), len(gen), resumo))
    return 0


if __name__ == "__main__":
    sys.exit(main())
