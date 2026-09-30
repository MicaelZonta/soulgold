#!/usr/bin/env python3
"""Confere que os tres lugares que definem os falantes concordam.

O byte gravado no texto e o indice do enum. Se charmap.txt, o enum e a tabela
saem de ordem, TODA fala ja escrita passa a mostrar o nome errado - e o build
continua limpo. Por isso esta checagem existe.

    python3 checar_falantes.py

Confere:
  1. include/constants/speaker_names.h  (o enum, que define os indices)
  2. src/data/speaker_names.h           (o texto na tela)
  3. charmap.txt                        (os nomes para {SPEAKER NAME_X})
  4. todo {SPEAKER NAME_X} usado em data/ aponta para um nome que existe
  5. nenhuma linha de fala ficou com o prefixo "Nome: " sobrando
  6. nenhum texto de msgbox estoura gStringVar4 (1000 bytes)
"""
import os
import re
import sys

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))


def ler(caminho):
    return open(os.path.join(RAIZ, caminho), encoding="utf-8").read()


def do_enum():
    corpo = re.search(r"enum SpeakerNames \{(.*?)\};", ler("include/constants/speaker_names.h"), re.S).group(1)
    nomes = re.findall(r"SP_NAME_(\w+)", corpo)
    return [n for n in nomes if n != "COUNT"]


def da_tabela():
    corpo = re.search(r"gSpeakerNamesTable\[SP_NAME_COUNT\]\s*=\s*\{(.*?)\n\};", ler("src/data/speaker_names.h"), re.S).group(1)
    return re.findall(r"\[SP_NAME_(\w+)\]", corpo)


def do_charmap():
    pares = []
    for linha in ler("charmap.txt").split("\n"):
        m = re.match(r"^NAME_(\w+) = ([0-9A-Fa-f]+)\s*(@.*)?$", linha.strip())
        if m:
            pares.append((m.group(1), int(m.group(2), 16)))
    return pares


def usados():
    achados = {}
    for pasta in ("data", "src"):
        for raiz, _, arquivos in os.walk(os.path.join(RAIZ, pasta)):
            for nome in arquivos:
                if not nome.endswith((".inc", ".pory", ".h", ".c")):
                    continue
                caminho = os.path.join(raiz, nome)
                try:
                    texto = open(caminho, encoding="utf-8").read()
                except (OSError, UnicodeDecodeError):
                    continue
                for m in re.finditer(r"\{SPEAKER (\w+)\}", texto):
                    achados.setdefault(m.group(1), set()).add(
                        os.path.relpath(caminho, RAIZ)
                    )
    return achados


# --- 6: tamanho do texto -----------------------------------------------------
# msgbox expande o texto INTEIRO em gStringVar4 antes de desenhar qualquer
# coisa (ExpandStringAndStartDrawFieldMessage, src/field_message_box.c), e
# gStringVar4 tem 1000 bytes (EWRAM_DATA u8 gStringVar4[0x3E8],
# src/string_util.c). StringExpandPlaceholders nao checa tamanho: um texto
# maior escreve por cima da EWRAM seguinte e o jogo TRAVA na hora da fala.
# O build continua limpo - por isso esta checagem existe.
# Conserto: quebrar em varios msgbox seguidos, SEM closemessage entre eles
# (a caixa nao desce), cada parte comecando com o seu {SPEAKER ...}.
LIMITE = 1000
FOLGA = 900


def bytes_do_texto(linhas):
    total = 0
    for corpo in linhas:
        corpo = re.sub(r"\\[nlpz]", ".", corpo)
        corpo = corpo.replace("$", "")
        corpo = re.sub(r"\{SPEAKER [A-Z_0-9]+\}", "..", corpo)
        # nome de jogador/rival e STR_VAR_* ocupam o buffer inteiro deles
        corpo = re.sub(r"\{(PLAYER|RIVAL|STR_VAR_[1-3])\}", "." * 10, corpo)
        corpo = re.sub(r"\{[A-Z_0-9 ]+\}", ".", corpo)
        total += len(corpo)
    return total + 1  # EOS


def textos_grandes():
    achados = []
    for raiz, _, arquivos in os.walk(os.path.join(RAIZ, "data")):
        for nome in arquivos:
            if not nome.endswith((".inc", ".pory")):
                continue
            caminho = os.path.join(raiz, nome)
            # onde ha .pory o .inc e gerado: mediria tudo duas vezes
            if nome == "scripts.inc" and os.path.exists(
                os.path.join(raiz, "scripts.pory")
            ):
                continue
            try:
                texto = open(caminho, encoding="utf-8").read()
            except (OSError, UnicodeDecodeError):
                continue
            rotulo, linha, corpos = None, 0, []
            for n, l in enumerate(texto.split("\n"), 1):
                s = l.strip()
                if s.startswith("#") or s.startswith("@") or not s:
                    continue
                m = re.match(r"^([A-Za-z0-9_]+):+$", s)
                if m:
                    if rotulo and corpos:
                        achados.append(
                            (bytes_do_texto(corpos), rotulo, caminho, linha)
                        )
                    rotulo, linha, corpos = m.group(1), n, []
                    continue
                if s.startswith(".string") and rotulo:
                    c = s[len(".string"):].strip()
                    if c.startswith('"'):
                        c = c[1:c.rfind('"')]
                    corpos.append(c)
                elif not s.startswith(".string"):
                    if rotulo and corpos:
                        achados.append(
                            (bytes_do_texto(corpos), rotulo, caminho, linha)
                        )
                    rotulo, corpos = None, []
            if rotulo and corpos:
                achados.append((bytes_do_texto(corpos), rotulo, caminho, linha))
    return achados


def main():
    erros = []

    enum = do_enum()
    tabela = da_tabela()
    charmap = do_charmap()

    # 1 x 2: a tabela nao precisa listar NONE, mas o resto tem que bater
    esperado = [n for n in enum if n != "NONE"]
    if tabela != esperado:
        erros.append(
            "tabela x enum fora de ordem:\n  enum:   %s\n  tabela: %s"
            % (esperado, tabela)
        )

    # 1 x 3: charmap tem que repetir o enum, indice por indice, mais COUNT
    nomes_charmap = [n for n, _ in charmap if n != "COUNT"]
    if nomes_charmap != enum:
        erros.append(
            "charmap.txt x enum fora de ordem:\n  enum:    %s\n  charmap: %s"
            % (enum, nomes_charmap)
        )
    for i, (nome, valor) in enumerate([p for p in charmap if p[0] != "COUNT"]):
        if valor != i:
            erros.append(
                "charmap.txt: NAME_%s deveria valer %02X e vale %02X"
                % (nome, i, valor)
            )
    conta = dict(charmap).get("COUNT")
    if conta is not None and conta != len(enum):
        erros.append(
            "charmap.txt: NAME_COUNT deveria valer %02X e vale %02X"
            % (len(enum), conta)
        )

    # 4: todo uso aponta para um nome existente
    conhecidos = {"NAME_" + n for n in enum} | {"NAME_NONE"}
    for nome, arquivos in sorted(usados().items()):
        if nome not in conhecidos:
            erros.append(
                "{SPEAKER %s} nao existe em charmap.txt (em %s)"
                % (nome, ", ".join(sorted(arquivos)))
            )

    # 5: prefixo "Nome: " sobrando num bloco que ja usa plaquinha
    legiveis = {n.replace("_", " ").title() for n in enum}
    for raiz, _, arquivos in os.walk(os.path.join(RAIZ, "data", "maps")):
        for nome in arquivos:
            if nome not in ("scripts.inc", "scripts.pory"):
                continue
            caminho = os.path.join(raiz, nome)
            texto = open(caminho, encoding="utf-8").read()
            if "{SPEAKER" not in texto:
                continue
            for n, linha in enumerate(texto.split("\n"), 1):
                m = re.search(r'\.string "([A-Z][A-Za-z. ]{1,14}): ', linha)
                if m and m.group(1) in legiveis:
                    erros.append(
                        "%s:%d ainda comeca com %r em vez da plaquinha"
                        % (os.path.relpath(caminho, RAIZ), n, m.group(1) + ": ")
                    )

    # 6: texto grande demais para gStringVar4
    avisos = []
    for n, rotulo, caminho, linha in sorted(textos_grandes(), reverse=True):
        onde = "%s:%d %s" % (os.path.relpath(caminho, RAIZ), linha, rotulo)
        if n > LIMITE:
            erros.append(
                "%s tem ~%d bytes e estoura gStringVar4 (%d): o jogo trava "
                "nesta fala. Quebre em varios msgbox seguidos, sem "
                "closemessage entre eles." % (onde, n, LIMITE)
            )
        elif n > FOLGA:
            avisos.append("%s tem ~%d bytes (limite %d)" % (onde, n, LIMITE))

    if erros:
        for e in erros:
            print("ERRO: " + e)
        return 1
    for a in avisos:
        print("AVISO: " + a)
    print("%d falantes, tudo em ordem." % len(enum))
    return 0


if __name__ == "__main__":
    sys.exit(main())
