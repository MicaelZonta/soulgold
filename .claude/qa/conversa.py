#!/usr/bin/env python3
"""Conduz uma conversa ja aberta (ou abre com A) e guarda um print por caixa.

    conversa.py PREFIXO [--respostas YN...] [--abrir] [--max 40]

- Tira print, decide e aperta: caixa de texto -> A; menu Yes/No -> a proxima
  resposta da lista (Y = A, N = DOWN + A); sem caixa nenhuma -> fim.
- Prints repetidos (a mesma caixa ainda imprimindo) nao sao guardados.
- Para menus que nao sao Yes/No (multichoice, listas), ele para e avisa:
  o chamador decide e chama de novo.
Imprime a lista de prints e o motivo de parada.
"""
import argparse, hashlib, sys
from pathlib import Path
from PIL import Image

sys.path.insert(0, str(Path(__file__).parent))
import q

WHITE = (255, 255, 255)


def classify(path):
    im = Image.open(path).convert("RGB")
    yesno = sum(1 for x in range(168, 216) for y in range(70, 104) if im.getpixel((x, y)) == WHITE)
    text = sum(1 for x in range(8, 232) for y in range(124, 152) if im.getpixel((x, y)) == WHITE)
    # menu no canto superior esquerdo (dynmultichoice / listas do debug)
    menu = sum(1 for x in range(4, 100) for y in range(4, 60) if im.getpixel((x, y)) == WHITE)
    if yesno > 800 and text > 2000:
        return "yesno"
    if menu > 2000 and text > 2000:   # caixa de dinheiro sozinha da ~1400
        return "menu"
    if text > 2000:
        return "text"
    return "none"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("prefix")
    ap.add_argument("--respostas", default="")
    ap.add_argument("--abrir", action="store_true")
    ap.add_argument("--max", type=int, default=40)
    a = ap.parse_args()
    answers = list(a.respostas.upper())
    if a.abrir:
        q.run(["press A 6 10"])
    saved, last, n, idle = [], None, 0, 0
    for i in range(a.max * 3):
        tmp = f"{a.prefix}_tmp.png"
        q.run(["wait 50", f"shot {tmp}"])
        kind = classify(tmp)
        h = hashlib.md5(open(tmp, "rb").read()).hexdigest()
        if h != last:
            n += 1
            out = f"{a.prefix}_{n:02d}.png"
            Path(tmp).rename(out)
            saved.append(out)
            last = h
        if kind == "none":
            idle += 1
            if idle >= 2:
                print("fim: sem caixa"); break
            continue
        idle = 0
        if kind == "menu":
            print("parou: menu (nao Yes/No)"); break
        if kind == "yesno":
            if not answers:
                print("parou: Yes/No sem resposta na lista"); break
            r = answers.pop(0)
            q.run(["wait 30", "press DOWN 6 20", "press A 6 20"] if r == "N" else ["wait 30", "press A 6 20"])
            continue
        q.run(["press A 6 20"])
        if len(saved) >= a.max:
            print("parou: max"); break
    Path(f"{a.prefix}_tmp.png").unlink(missing_ok=True)
    try:
        print("\n".join(saved))
    except BrokenPipeError:
        pass


if __name__ == "__main__":
    main()
