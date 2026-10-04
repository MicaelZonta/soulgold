#!/usr/bin/env python3
"""Tentativas de cruzamento na horta da Route 30 (Bloco D do roteiro).

    cruzar.py --plantas "ITEM_CHESTO_BERRY@28,43 ITEM_CHERI_BERRY@29,43" \
              --alvo 29,43 --mutacao ITEM_LUM_BERRY --max 10 --prefixo /tmp/qa/ev/T24

Cada tentativa: Empty the garden -> planta na ordem dada (a ULTIMA e a que
sorteia a mutacao contra as ja plantadas) -> Ripen -> colhe o alvo com print
de cada caixa -> confere na RAM se a mutacao entrou na bolsa. Para na
primeira mutacao, a menos que --todas (para medir frequencia).
"""
import argparse, subprocess, sys
from pathlib import Path

HERE = Path(__file__).parent
sys.path.insert(0, str(HERE))
import q, bolsa
from plantar import plant


def macro(name, *args):
    return subprocess.run(["bash", "-c", f". {HERE}/lib.sh; {name} {' '.join(map(str, args))}"],
                          capture_output=True, text=True).stdout.strip()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--plantas", required=True)
    ap.add_argument("--alvo", required=True)
    ap.add_argument("--mutacao", required=True)
    ap.add_argument("--max", type=int, default=10)
    ap.add_argument("--prefixo", default="/tmp/qa/cruz")
    ap.add_argument("--todas", action="store_true")
    ap.add_argument("--jitter", type=int, default=0,
                    help="espera aleatoria (0..N quadros) antes do ultimo plantio: tira o input "
                         "de quadro-exato, que pode correlacionar o RNG entre tentativas")
    a = ap.parse_args()
    names = {v: k for k, v in bolsa.item_names().items()}
    mut = names[a.mutacao]
    tx, ty = map(int, a.alvo.split(","))
    hits = 0
    for t in range(1, a.max + 1):
        q.run([macro("clean"), macro("bm", 8), "wait 90", macro("clean"), "wait 120"])
        specs = a.plantas.split()
        for k, spec in enumerate(specs):
            if a.jitter and k == len(specs) - 1:
                import random
                q.run([f"wait {random.randint(1, a.jitter)}"])
            item, xy = spec.split("@")
            x, y = map(int, xy.split(","))
            plant("Route30", x, y, item)
        q.run([macro("clean"), macro("bm", 6), "wait 90", macro("clean"), "wait 120"])
        before = bolsa.read().get(mut, 0)
        import ir
        ir.go("Route30", (tx, ty))
        r = subprocess.run([sys.executable, str(HERE / "conversa.py"), f"{a.prefixo}_t{t:02d}",
                            "--abrir", "--respostas", "Y"], capture_output=True, text=True).stdout
        got = bolsa.read().get(mut, 0) - before
        hits += got > 0
        print(f"tentativa {t}: {a.mutacao} +{got}", flush=True)
        if got and not a.todas:
            break
    print(f"mutacoes: {hits}/{t}")


if __name__ == "__main__":
    main()
