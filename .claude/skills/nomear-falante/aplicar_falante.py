#!/usr/bin/env python3
"""Troca o prefixo "Nome: " das falas pelo codigo {SPEAKER NAME_X}.

    .string "Looker: {PLAYER}! You came.\\n"
    ->
    .string "{SPEAKER NAME_LOOKER}{PLAYER}! You came.\\n"

O codigo de controle nao ocupa pixel nenhum, entao a linha so ENCOLHE: as
quebras de linha do autor (que sao batidas de cena, nao acaso) ficam como
estao. Nada de reencaixar paragrafo.

Regra do motor (src/field_name_box.c, TrySetSpeakerFromMessage): cada
mensagem diz quem fala. Sem {SPEAKER ...} antes da primeira letra, a mensagem
nao tem plaquinha - narracao nunca herda o nome da caixa anterior. Por isso
este conversor nao precisa marcar narracao com NAME_NONE.

Dentro de UMA mensagem, porem, as paginas seguidas (\\p) continuam com o mesmo
nome. Uma pagina de narracao no meio de um bloco que comecou com fala fica
com a plaquinha pendurada: o conversor nao adivinha essas, ele as LISTA no
fim para conferencia a mao.

Uso:
    python3 aplicar_falante.py --conferir <arquivo> [...]   # diff, nao grava
    python3 aplicar_falante.py --aplicar  <arquivo> [...]   # grava

Edite SEMPRE o .pory quando ele existir; o .inc e gerado.
"""
import difflib
import re
import sys

# prefixo escrito na fala -> constante de charmap.txt
FALANTES = {
    "Looker": "NAME_LOOKER",
    "Anabel": "NAME_ANABEL",
    "Lillie": "NAME_LILLIE",
    "Gladion": "NAME_GLADION",
    "Kukui": "NAME_KUKUI",
    "Pryce": "NAME_PRYCE",
    "Clair": "NAME_CLAIR",
    "Old man": "NAME_OLD_MAN",
    "Elm": "NAME_ELM",
    "Lusamine": "NAME_LUSAMINE",
    "Mom": "NAME_MOM",
}

RE_STRING = re.compile(r'^(\s*)\.string\s+"(.*)"\s*$')
RE_ROTULO = re.compile(r"^\s*(\w+):\s*$")
RE_PREFIXO = re.compile(r"^(%s): " % "|".join(re.escape(n) for n in FALANTES))


def converter(caminho):
    """Devolve (texto_novo, trocas, suspeitas_de_narracao)."""
    linhas = open(caminho, encoding="utf-8").read().split("\n")
    saida = []
    trocas = 0
    suspeitas = []  # rotulos de blocos a conferir a mao

    rotulo = "?"
    # dentro do bloco atual: ja houve uma fala com nome?
    em_fala = False
    # a proxima .string comeca uma pagina nova?
    nova_pagina = True

    for n, linha in enumerate(linhas, 1):
        marca = RE_ROTULO.match(linha)
        if marca:
            rotulo = marca.group(1)
            em_fala = False
            nova_pagina = True
            saida.append(linha)
            continue

        m = RE_STRING.match(linha)
        if not m:
            saida.append(linha)
            continue

        indent, corpo = m.group(1), m.group(2)

        if nova_pagina:
            prefixo = RE_PREFIXO.match(corpo)
            if prefixo:
                corpo = "{SPEAKER %s}%s" % (
                    FALANTES[prefixo.group(1)],
                    corpo[prefixo.end():],
                )
                linha = '%s.string "%s"' % (indent, corpo)
                trocas += 1
                em_fala = True
            elif em_fala and rotulo not in suspeitas:
                # Quase sempre e so a continuacao da mesma fala, que ja herda
                # o nome de graca. So importa quando a pagina e NARRACAO: ai a
                # plaquinha do falante anterior fica pendurada sobre ela e o
                # bloco precisa de um {SPEAKER NAME_NONE} a mao. Nao da para
                # distinguir os dois casos por regra, entao aqui so sai a
                # lista de blocos a olhar.
                suspeitas.append(rotulo)

        # a proxima linha abre pagina nova se esta terminou a pagina
        nova_pagina = corpo.endswith("\\p") or corpo.endswith("$")
        saida.append(linha)

    return "\n".join(saida), trocas, suspeitas


def main():
    args = sys.argv[1:]
    if not args or args[0] not in ("--conferir", "--aplicar"):
        print(__doc__)
        return 1
    aplicar = args[0] == "--aplicar"

    for caminho in args[1:]:
        antigo = open(caminho, encoding="utf-8").read()
        novo, trocas, suspeitas = converter(caminho)
        print("%s: %d falas marcadas" % (caminho, trocas))
        if aplicar:
            open(caminho, "w", encoding="utf-8").write(novo)
        else:
            for l in difflib.unified_diff(
                antigo.split("\n"), novo.split("\n"), lineterm="", n=0
            ):
                print(l)
        if suspeitas:
            print(
                "  %d blocos tem pagina sem nome depois de uma fala."
                % len(suspeitas)
            )
            print(
                "  Continuacao da mesma fala: nada a fazer. Narracao: ponha\n"
                "  {SPEAKER NAME_NONE} no comeco da pagina. Blocos:"
            )
            for rotulo in suspeitas:
                print("    " + rotulo)
    return 0


if __name__ == "__main__":
    sys.exit(main())
