#!/usr/bin/env python3
"""Acrescenta falantes para a plaquinha e regera o bloco NAME_* do charmap.

    python3 adicionar_falante.py PRYCE "Pryce"
    python3 adicionar_falante.py FARFETCHD "Farfetch'd" DIRECTOR "Director"
    python3 adicionar_falante.py --sincronizar     # so regera o charmap

Tres arquivos precisam concordar, na mesma ordem:
  1. include/constants/speaker_names.h   enum SpeakerNames (define o indice)
  2. src/data/speaker_names.h            gSpeakerNamesTable (o texto na tela)
  3. charmap.txt                         NAME_X = alto baixo

O enum e a fonte de verdade. Falante novo entra SEMPRE no fim (antes de
SP_NAME_COUNT); os existentes nunca sao reordenados. O bloco do charmap e
reescrito inteiro a partir do enum, entao ele nao sai de ordem.

O indice vai em 2 bytes (SPEAKER_ARG_BYTES), cada um de 00 a F9 (FA..FF sao
quebras, codigo de controle, placeholder e fim de texto), entao
indice = alto * 250 + baixo: ate 62500 falantes. A base vem de
SPEAKER_ARG_BASE em include/constants/speaker_names.h.
"""
import os
import re
import sys

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
ENUM = os.path.join(RAIZ, "include/constants/speaker_names.h")
TABELA = os.path.join(RAIZ, "src/data/speaker_names.h")
CHARMAP = os.path.join(RAIZ, "charmap.txt")
BASE = int(re.search(r"#define SPEAKER_ARG_BASE\s+(\d+)", open(ENUM, encoding="utf-8").read()).group(1))


def codificar(indice):
    """indice -> 'AA BB' (nenhum byte chega a FA)."""
    return "%02X %02X" % divmod(indice, BASE)


def ler(caminho):
    return open(caminho, encoding="utf-8").read()


def gravar(caminho, texto):
    open(caminho, "w", encoding="utf-8").write(texto)


def nomes_do_enum():
    corpo = re.search(r"enum SpeakerNames \{(.*?)\};", ler(ENUM), re.S).group(1)
    return [n for n in re.findall(r"SP_NAME_(\w+)", corpo) if n != "COUNT"]


def sincronizar_charmap():
    nomes = nomes_do_enum()
    linhas = ["NAME_%s = %s" % (n, codificar(i)) for i, n in enumerate(nomes)]
    linhas.append("NAME_COUNT = %s" % codificar(len(nomes)))
    texto = ler(CHARMAP)
    novo, n = re.subn(
        r"^NAME_NONE = .*?^NAME_COUNT = [^\n]*$",
        "\n".join(linhas),
        texto,
        count=1,
        flags=re.S | re.M,
    )
    if n != 1:
        sys.exit("charmap.txt: bloco NAME_NONE..NAME_COUNT nao encontrado")
    if novo != texto:
        gravar(CHARMAP, novo)
    return len(nomes)


def acrescentar(pares):
    existentes = set(nomes_do_enum())
    enum = ler(ENUM)
    tabela = ler(TABELA)
    for const, visivel in pares:
        if not re.fullmatch(r"[A-Z][A-Z0-9_]*", const):
            sys.exit("nome de constante invalido: %s" % const)
        if const in existentes:
            print("ja existe: SP_NAME_%s (pulado)" % const)
            continue
        existentes.add(const)
        enum = enum.replace(
            "    SP_NAME_COUNT\n", "    SP_NAME_%s,\n    SP_NAME_COUNT\n" % const, 1
        )
        visivel = visivel.replace("\\", "\\\\").replace('"', '\\"')
        tabela = re.sub(
            r"\n\};",
            '\n    [SP_NAME_%s] = COMPOUND_STRING("%s"),\n};' % (const, visivel),
            tabela,
            count=1,
        )
        print("acrescentado: SP_NAME_%s = \"%s\"" % (const, visivel))
    gravar(ENUM, enum)
    gravar(TABELA, tabela)


def main():
    args = sys.argv[1:]
    if args == ["--sincronizar"]:
        pass
    elif args and len(args) % 2 == 0:
        acrescentar(list(zip(args[::2], args[1::2])))
    else:
        print(__doc__)
        return 1
    total = sincronizar_charmap()
    print("%d falantes; charmap.txt sincronizado." % total)
    print("Confira: python3 .claude/skills/nomear-falante/checar_falantes.py")
    return 0


if __name__ == "__main__":
    sys.exit(main())
