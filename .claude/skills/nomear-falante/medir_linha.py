#!/usr/bin/env python3
"""Mede a largura real, em pixels, das linhas de texto de um script de mapa.

A caixa de dialogo do overworld tem 27 tiles de largura (216 px, janela 0,
src/menu.c sStandardTextBox_WindowTemplates) e imprime em FONT_NORMAL, cujas
larguras de glifo estao em src/fonts.c (gFontNormalLatinGlyphWidths) e cujo
letterSpacing e 0 (src/text.c).

Uso:
    python3 medir_linha.py <arquivo.inc|.pory> [...]        # so o que estoura
    python3 medir_linha.py --todas <arquivo>                # todas as linhas
    python3 medir_linha.py --largura "texto solto"          # mede uma string

O limite pratico e LIMITE_PX; o vanilla ja usa linhas de ate ~208 px.
"""
import os
import re
import sys

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
LIMITE_PX = 208  # 27 tiles = 216 px; 208 deixa a folga que o vanilla usa


def _larguras_fonte():
    """gFontNormalLatinGlyphWidths, em ordem de byte de charmap."""
    src = open(os.path.join(RAIZ, "src", "fonts.c"), encoding="utf-8").read()
    corpo = re.search(
        r"gFontNormalLatinGlyphWidths\[\]\s*=\s*\{(.*?)\};", src, re.S
    ).group(1)
    return [int(n) for n in re.findall(r"\d+", corpo)]


def _charmap():
    """char do .inc -> byte, lido de charmap.txt (so as entradas de 1 byte)."""
    tabela = {}
    caminho = os.path.join(RAIZ, "charmap.txt")
    for linha in open(caminho, encoding="utf-8"):
        linha = linha.split("@")[0].strip()
        if "=" not in linha:
            continue
        esq, dir_ = linha.split("=", 1)
        esq, dir_ = esq.strip(), dir_.strip()
        bytes_ = dir_.split()
        if len(bytes_) != 1:
            continue
        try:
            valor = int(bytes_[0], 16)
        except ValueError:
            continue
        if esq.startswith("'") and esq.endswith("'") and len(esq) >= 3:
            tabela[esq[1:-1]] = valor
        elif len(esq) == 1:
            tabela[esq] = valor
    return tabela


LARGURAS = _larguras_fonte()
CHARMAP = _charmap()

# {CODIGO} que nao ocupa pixel nenhum na linha
CTRL_SEM_LARGURA = re.compile(
    r"\{(SPEAKER|COLOR|HIGHLIGHT|SHADOW|COLOR_HIGHLIGHT_SHADOW|PALETTE|FONT|"
    r"RESET_FONT|PAUSE|PAUSE_UNTIL_PRESS|WAIT_SE|PLAY_BGM|PLAY_SE|ESCAPE|"
    r"PAUSE_MUSIC|RESUME_MUSIC|CREATE_MUGSHOT|DESTROY_MUGSHOT|CLEAR|SKIP|"
    r"CLEAR_TO|MIN_LETTER_SPACING|JPN|ENG|ACCENT|BACKGROUND|TEXT_COLORS)\b[^}]*\}"
)

# {PLACEHOLDER} que vira texto em runtime: medido pelo pior caso plausivel
PLACEHOLDERS = {
    "PLAYER": "Kristina",   # 8 letras; o jogo permite ate 10, mas 7-8 e o real
    "STR_VAR_1": "Celesteela",
    "STR_VAR_2": "Celesteela",
    "STR_VAR_3": "Celesteela",
    "RIVAL": "Silver",
}


def largura(texto):
    """Largura em pixels de uma linha ja sem \\n \\l \\p."""
    texto = CTRL_SEM_LARGURA.sub("", texto)
    for nome, amostra in PLACEHOLDERS.items():
        texto = texto.replace("{%s}" % nome, amostra)
    texto = re.sub(r"\{[^}]*\}", "?", texto)  # placeholder desconhecido
    total = 0
    for ch in texto:
        byte = CHARMAP.get(ch)
        if byte is None:
            byte = CHARMAP.get("?", 0xAC)
        total += LARGURAS[byte] if byte < len(LARGURAS) else 6
    return total


def linhas_do_arquivo(caminho):
    """Gera (numero_da_linha, rotulo, texto_da_linha) para cada .string."""
    rotulo = "?"
    for n, linha in enumerate(open(caminho, encoding="utf-8"), 1):
        marca = re.match(r"^(\w+):\s*$", linha) or re.match(
            r"^\s*(\w+):\s*$", linha
        )
        if marca:
            rotulo = marca.group(1)
            continue
        m = re.search(r'\.string\s+"(.*)"\s*$', linha.rstrip())
        if not m:
            continue
        corpo = m.group(1)
        corpo = re.sub(r"(\\[nlp]|\$)$", "", corpo)
        yield n, rotulo, corpo


def main():
    args = sys.argv[1:]
    if args and args[0] == "--largura":
        for t in args[1:]:
            print("%4d px  %s" % (largura(t), t))
        return 0
    todas = False
    if args and args[0] == "--todas":
        todas, args = True, args[1:]
    if not args:
        print(__doc__)
        return 1
    estouros = 0
    for caminho in args:
        for n, rotulo, corpo in linhas_do_arquivo(caminho):
            px = largura(corpo)
            if px > LIMITE_PX:
                estouros += 1
                print("ESTOURA %s:%d  %3d px  [%s]  %s" % (caminho, n, px, rotulo, corpo))
            elif todas:
                print("        %s:%d  %3d px  [%s]  %s" % (caminho, n, px, rotulo, corpo))
    if not estouros:
        print("Nenhuma linha passa de %d px." % LIMITE_PX)
    return 0


if __name__ == "__main__":
    sys.exit(main())
