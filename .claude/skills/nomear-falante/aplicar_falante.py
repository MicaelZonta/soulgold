#!/usr/bin/env python3
"""Troca o prefixo "Nome: " das falas pelo codigo {SPEAKER NAME_X}.

    .string "Looker: {PLAYER}! You came.\\n"
    ->
    .string "{SPEAKER NAME_LOOKER}{PLAYER}! You came.\\n"

O codigo de controle nao ocupa pixel nenhum, entao a linha so ENCOLHE: as
quebras de linha do autor (que sao batidas de cena, nao acaso) ficam como
estao. Nada de reencaixar paragrafo.

Os falantes conhecidos saem de src/data/speaker_names.h (o texto da plaquinha,
sem diferenca de maiuscula: "BILL: " e "Bill: " viram NAME_BILL), mais os
APELIDOS abaixo ("Prof. Elm: " -> NAME_ELM). Prefixos que parecem falante mas
nao sao (placa de ginasio "Leader: Falkner", "Type: Null") ficam em
NAO_FALANTES. Um prefixo que nao esta em nenhum dos dois sai como
DESCONHECIDO: acrescente o falante com adicionar_falante.py (ou o apelido /
a excecao aqui) e rode de novo.

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
    python3 aplicar_falante.py --resumo   <arquivo> [...]   # so contagens

Edite SEMPRE o .pory quando ele existir; o .inc e gerado.
"""
import difflib
import os
import re
import sys

RAIZ = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))

# prefixo escrito na fala (minusculo) -> constante, quando difere do texto
# da plaquinha
APELIDOS = {
    "prof. elm": "NAME_ELM",
    "prof elm": "NAME_ELM",
    "prof.elm": "NAME_ELM",
    "prof. oak": "NAME_OAK",
    "prof.oak": "NAME_OAK",
    "mr.fuji": "NAME_MR_FUJI",
    "lt. surge": "NAME_LT_SURGE",
    "surge": "NAME_LT_SURGE",
    "prof. birch": "NAME_BIRCH",
    "baoba": "NAME_WARDEN_BAOBA",
    "???": "NAME_UNKNOWN",
}

# "Algo: " no comeco da linha que NAO e alguem falando
NAO_FALANTES = {
    "leader",           # placa de ginasio: "Leader: Falkner"
    "type",             # "Type: Null, look..."
    "remember type",    # "...Remember Type: Null"
    "remember this",
    "nothing's wasted",
    "left",             # quadro do dojo: "Left: Hp, Def, Sdef"
    "right",
    "battle tent",      # placa: "Battle Tent: Factory"
    "a button",
    "b button",
    "mind",             # ficha do Nexus: "Mind: ... Skill: ..."
    "body",
    "skill",
    "cinnabar gym leader",  # placa da Route 20: "Cinnabar Gym Leader: Blaine"
    "but let me say this",
    "here's some advice",
    "system note",      # placa: "System note: The area ahead..."
    "power relay",      # terminal: "POWER RELAY: NOT DETECTED"
    "error",
    "heart rate",
}


def falantes_da_tabela():
    texto = open(
        os.path.join(RAIZ, "src/data/speaker_names.h"), encoding="utf-8"
    ).read()
    tabela = {}
    for const, visivel in re.findall(
        r'\[SP_NAME_(\w+)\]\s*=\s*COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)', texto
    ):
        if "{" in visivel:
            continue
        tabela.setdefault(visivel.replace('\\"', '"').lower(), "NAME_" + const)
    return tabela


FALANTES = falantes_da_tabela()
FALANTES.update({k: v for k, v in APELIDOS.items()})

RE_STRING = re.compile(r'^(\s*)\.string\s+"(.*)"\s*$')
RE_ROTULO = re.compile(r"^\s*(\w+):+\s*$")
RE_PREFIXO = re.compile(r"^([A-Z][A-Za-zÉé.&' ]{0,18}): ")


# Texto que aparece DENTRO da batalha (fala de derrota do treinador etc.). Na
# batalha nao existe plaquinha: text.c so consome o {SPEAKER ...}. Converter
# um texto desses apagaria o nome da tela, entao ele fica com "Nome: ".
# posicao (0 = primeiro argumento) dos textos de batalha em cada macro de
# asm/macros/event.inc
ARGS_DE_BATALHA = {
    "trainerbattle": (4, 9, 10),
    "trainerbattle_single": (2,),
    "trainerbattle_double": (2,),
    "trainerbattle_rematch": (2,),
    "trainerbattle_rematch_double": (2,),
    "trainerbattle_no_intro": (1,),
    "trainerbattle_two_trainers": (1, 3),
    "trainerbattle_earlyrival": (2, 3),
}
RE_CHAMADA = re.compile(r"\b(trainerbattle\w*)\b[ (]+([^)\n]*)")


def textos_de_batalha():
    rotulos = set()
    for pasta in ("data/maps", "data/scripts"):
        for raiz, _, arquivos in os.walk(os.path.join(RAIZ, pasta)):
            for nome in arquivos:
                if not nome.endswith((".inc", ".pory")):
                    continue
                texto = open(os.path.join(raiz, nome), encoding="utf-8").read()
                for macro, args in RE_CHAMADA.findall(texto):
                    args = [a.strip() for a in args.split(",")]
                    for i in ARGS_DE_BATALHA.get(macro, ()):
                        if i < len(args):
                            rotulos.add(args[i])
    return rotulos


TEXTOS_DE_BATALHA = textos_de_batalha()


def constante(prefixo):
    """"Prof. Elm" -> NAME_ELM; None para nao-falante; '' se desconhecido."""
    chave = prefixo.lower()
    if chave in NAO_FALANTES:
        return None
    return FALANTES.get(chave, "")


# Texto inline do Poryscript: msgbox("Blaine: ...") ou
# pokenavcall("???: ...\n\n   Archer: ..."). Numa string de varias linhas,
# linha em branco e troca de pagina (\p), entao o prefixo pode vir no comeco
# da string, logo depois de um \p ou logo depois de uma linha em branco.
RE_INLINE = re.compile(
    r'\b(msgbox|message|pokenavcall)\(\s*(?:format\(\s*)?"((?:[^"\\]|\\.)*)"', re.S
)
RE_INICIO_DE_PAGINA = re.compile(
    r"(^|\\p|\n[ \t]*\n[ \t]*)([A-Z?][A-Za-z\u00c9\u00e9.&' ?]{0,18}): "
)


def converter_inline(texto, desconhecidos):
    trocas = [0]

    def na_string(m):
        corpo = m.group(2)

        def troca(p):
            const = constante(p.group(2))
            if const == "":
                desconhecidos.append((texto[: m.start()].count("\n") + 1, p.group(2)))
            if not const:
                return p.group(0)
            trocas[0] += 1
            return "%s{SPEAKER %s}" % (p.group(1), const)

        novo = RE_INICIO_DE_PAGINA.sub(troca, corpo)
        inicio = m.start(2) - m.start(0)
        return m.group(0)[:inicio] + novo + m.group(0)[inicio + len(corpo):]

    return RE_INLINE.sub(na_string, texto), trocas[0]


def converter(caminho):
    """Devolve (texto_novo, trocas, suspeitas, desconhecidos, meio)."""
    linhas = open(caminho, encoding="utf-8").read().split("\n")
    saida = []
    trocas = 0
    suspeitas = []  # rotulos de blocos a conferir a mao
    desconhecidos = []  # (linha, prefixo)
    meio = []  # (linha, prefixo) falante no meio de uma pagina
    batalha = []  # rotulos mantidos com "Nome: " porque aparecem na batalha

    rotulo = "?"
    em_fala = False
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
            # um comando de script entre textos encerra o bloco
            if linha.strip() and not linha.strip().startswith(("@", "#", "//")):
                em_fala = False
                nova_pagina = True
            saida.append(linha)
            continue

        indent, corpo = m.group(1), m.group(2)
        prefixo = RE_PREFIXO.match(corpo)
        const = constante(prefixo.group(1)) if prefixo else None

        if prefixo and const == "":
            desconhecidos.append((n, prefixo.group(1)))
        elif prefixo and const and not nova_pagina and rotulo not in TEXTOS_DE_BATALHA:
            meio.append((n, prefixo.group(1)))

        if nova_pagina and const and rotulo in TEXTOS_DE_BATALHA:
            if rotulo not in batalha:
                batalha.append(rotulo)
        elif nova_pagina:
            if const:
                corpo = "{SPEAKER %s}%s" % (const, corpo[prefixo.end():])
                linha = '%s.string "%s"' % (indent, corpo)
                trocas += 1
                em_fala = True
            elif em_fala and rotulo not in suspeitas:
                # Quase sempre e so a continuacao da mesma fala, que ja herda
                # o nome de graca. So importa quando a pagina e NARRACAO: ai a
                # plaquinha do falante anterior fica pendurada sobre ela e o
                # bloco precisa de um {SPEAKER NAME_NONE} a mao.
                suspeitas.append(rotulo)

        # a proxima linha abre pagina nova se esta terminou a pagina
        nova_pagina = corpo.endswith("\\p") or corpo.endswith("$")
        if corpo.endswith("$"):
            em_fala = False
        saida.append(linha)

    texto = "\n".join(saida)
    if caminho.endswith(".pory"):
        texto, n = converter_inline(texto, desconhecidos)
        trocas += n
    return texto, trocas, suspeitas, desconhecidos, meio, batalha


def main():
    args = sys.argv[1:]
    if not args or args[0] not in ("--conferir", "--aplicar", "--resumo"):
        print(__doc__)
        return 1
    modo = args[0]

    total = 0
    for caminho in args[1:]:
        antigo = open(caminho, encoding="utf-8").read()
        novo, trocas, suspeitas, desconhecidos, meio, batalha = converter(caminho)
        total += trocas
        if not (trocas or desconhecidos or meio or batalha):
            continue
        print("%s: %d falas marcadas" % (caminho, trocas))
        for n, p in desconhecidos:
            print("  DESCONHECIDO %d: %r" % (n, p + ": "))
        for n, p in meio:
            print("  MEIO DE PAGINA %d: %r (troque a mao)" % (n, p + ": "))
        for r in batalha:
            print("  BATALHA %s: fica com \"Nome: \" (sem plaquinha na batalha)" % r)
        if modo == "--aplicar":
            open(caminho, "w", encoding="utf-8").write(novo)
        elif modo == "--conferir":
            for l in difflib.unified_diff(
                antigo.split("\n"), novo.split("\n"), lineterm="", n=0
            ):
                print(l)
        if suspeitas and modo != "--resumo":
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
    print("total: %d falas" % total)
    return 0


if __name__ == "__main__":
    sys.exit(main())
