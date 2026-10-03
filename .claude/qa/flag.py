#!/usr/bin/env python3
"""Le ou muda uma flag do save direto na RAM (gSaveBlock1Ptr->flags).

    flag.py FLAG_BADGE02_GET        # le
    flag.py FLAG_BADGE02_GET 1      # liga (0 desliga)
    flag.py --dex 265 415           # marca na Pokedex como capturados (nacional)

O numero da flag e o offset de flags[] saem do compilador (cpp + offsetof)
contra os headers do repo, nunca de valor fixo. Para testar cena que depende
de insignia/progresso sem jogar ate la. Lembre: flag TEMP e diaria tambem
moram aqui, e o mapa so relê o que importa no proximo load."""
import subprocess, sys, tempfile, os, re
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import q
from ir import sym

REPO = Path(__file__).resolve().parents[2]


def compiled(expr_lines):
    src = '#include "global.h"\n#include "constants/flags.h"\n#include <stddef.h>\n' + expr_lines
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write(src)
        name = f.name
    cpp = subprocess.run(["arm-none-eabi-cpp", "-iquote", str(REPO / "include"), "-DMODERN=1", "-DTESTING=0",
                          "-DEMERALD", "-std=gnu17", name], capture_output=True, text=True, cwd=REPO).stdout
    os.unlink(name)
    cc1 = sorted(Path("/usr/lib/gcc/arm-none-eabi").glob("*/cc1"))[-1]
    asm = subprocess.run([str(cc1), "-quiet", "-mthumb", "-O2", "-mabi=apcs-gnu", "-march=armv4t", "-std=gnu17",
                          "-o", "-", "-"], input=cpp, capture_output=True, text=True).stdout
    return {m.group(1): int(m.group(2)) for m in re.finditer(r"^(\w+):\n\s+\.word\s+(-?\d+)", asm, re.M)}



def main():
    if sys.argv[1] == "--dex":   # marca especies como capturadas (numeros da Pokedex nacional)
        off = compiled("const int off = offsetof(struct SaveBlock1, dexCaught);\n")["off"]
        base = int(q.run([f"r32 {sym('gSaveBlock1Ptr')}"]).split("=")[1])
        for num in map(int, sys.argv[2:]):
            i, addr = num - 1, base + off + (num - 1) // 8
            byte = int(q.run([f"r8 {addr}"]).split("=")[1]) | (1 << (i % 8))
            q.run([f"w8 {addr} {byte}"])
            print(f"dex {num}: capturado")
        return
    name = sys.argv[1]
    v = compiled(f"const int num = {name};\nconst int off = offsetof(struct SaveBlock1, flags);\n")
    num, off = v["num"], v["off"]
    base = int(q.run([f"r32 {sym('gSaveBlock1Ptr')}"]).split("=")[1])
    addr = base + off + num // 8
    byte = int(q.run([f"r8 {addr}"]).split("=")[1])
    if len(sys.argv) > 2:
        byte = byte | (1 << (num % 8)) if sys.argv[2] == "1" else byte & ~(1 << (num % 8))
        q.run([f"w8 {addr} {byte}"])
    print(f"{name} (0x{num:x}) = {(byte >> (num % 8)) & 1}")


if __name__ == "__main__":
    main()
