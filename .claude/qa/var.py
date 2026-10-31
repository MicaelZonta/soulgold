#!/usr/bin/env python3
"""Le ou muda uma var do save direto na RAM (gSaveBlock1Ptr->vars).

    var.py VAR_ABUNDANCE_ISLE_STATE        # le
    var.py VAR_ABUNDANCE_ISLE_STATE 4      # escreve

Mesmo esquema do flag.py: numero e offset vem do compilador. So vale para
VARS_START..VARS_END (as VAR_TEMP_* tambem moram aqui; VAR_0x8000+ nao)."""
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import q
from ir import sym
from flag import compiled


def main():
    name = sys.argv[1]
    v = compiled(f'#include "constants/vars.h"\nconst int num = {name} - VARS_START;\n'
                 f'const int off = offsetof(struct SaveBlock1, vars);\n')
    addr = int(q.run([f"r32 {sym('gSaveBlock1Ptr')}"]).split("=")[1]) + v["off"] + v["num"] * 2
    if len(sys.argv) > 2:
        q.run([f"w16 {addr} {int(sys.argv[2], 0)}"])
    print(f"{name} = {int(q.run([f'r16 {addr}']).split('=')[1])}")


if __name__ == "__main__":
    main()
