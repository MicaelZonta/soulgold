#!/usr/bin/env python3
"""Cliente do driver.lua: manda um lote de comandos e espera o ACK.

    q.py "press A" "wait 30" "shot /tmp/qa/x.png"
    q.py -f lote.txt
"""
import os, sys, time

DIR = os.environ.get("QA_DIR", "/tmp/qa")
CMD, ACK = f"{DIR}/cmd.txt", f"{DIR}/ack.txt"


def expand(args):
    lines = []
    for a in args:
        for c in a.split(";"):
            c = c.strip()
            if c.startswith("rep "):          # rep N <comando>
                _, n, rest = c.split(" ", 2)
                lines += [rest] * int(n)
            elif c:
                lines.append(c)
    return lines


def run(lines, timeout=600):
    lines = expand(lines)
    if os.path.exists(ACK):
        os.remove(ACK)
    with open(CMD + ".tmp", "w") as f:
        f.write("\n".join(lines) + "\n")
    os.rename(CMD + ".tmp", CMD)
    t0 = time.time()
    while not os.path.exists(ACK):
        if time.time() - t0 > timeout:
            sys.exit("timeout")
        time.sleep(0.02)
    with open(ACK) as f:
        return f.read().strip()


if __name__ == "__main__":
    args = sys.argv[1:]
    if args and args[0] == "-f":
        args = [l for l in open(args[1]).read().splitlines() if l.strip()]
    print(run(args))
