#!/usr/bin/env python3
"""Tabela de campos do SaveBlock1 (offset e tamanho), medida de verdade.

Nao estima: monta um .c com offsetof de cada campo, compila so ate o assembly
com o compilador do projeto e le os .word. Os campos saem do proprio header
depois do pre-processador, entao os #if (FREE_*) ja estao resolvidos.

    python3 dev_scripts/mapa_saveblock.py [SaveBlock1|SaveBlock2|SaveBlock3]
"""
import glob
import os
import re
import subprocess
import sys
import tempfile

RAIZ = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CPP = ['arm-none-eabi-cpp', '-iquote', 'include', '-DMODERN=1', '-DTESTING=0',
       '-DEMERALD', '-std=gnu17']


def cc1():
    c = glob.glob('/usr/lib/gcc/arm-none-eabi/*/cc1')
    if not c:
        sys.exit('cc1 do arm-none-eabi nao encontrado')
    return c[0]


def campos_da_struct(nome):
    with tempfile.NamedTemporaryFile('w', suffix='.c', delete=False) as f:
        f.write('#include "global.h"\n')
        tmp = f.name
    pre = subprocess.run(CPP + [tmp], capture_output=True, text=True, cwd=RAIZ).stdout
    os.unlink(tmp)
    i = pre.index('struct %s\n{' % nome)
    corpo = pre[i:pre.index('\n};', i)]
    out = []
    for l in corpo.split('\n'):
        m = re.match(r'^\s*[A-Za-z_][\w \*]*?\s(\**)(\w+)\s*(\[[^;]*\])?;$', l)
        if m:
            out.append(m.group(2))
    return out


def offsets(nome, campos):
    src = '#include "global.h"\n#include <stddef.h>\nconst unsigned int t[] = {\n'
    src += '    sizeof(struct %s),\n' % nome
    for c in campos:
        src += '    offsetof(struct %s, %s),\n' % (nome, c)
    src += '};\n'
    with tempfile.NamedTemporaryFile('w', suffix='.c', delete=False) as f:
        f.write(src)
        tmp = f.name
    pre = subprocess.run(CPP + [tmp], capture_output=True, text=True, cwd=RAIZ).stdout
    os.unlink(tmp)
    asm = subprocess.run([cc1(), '-quiet', '-mthumb', '-O2', '-mabi=apcs-gnu',
                          '-march=armv4t', '-std=gnu17', '-o', '-', '-'],
                         input=pre, capture_output=True, text=True, cwd=RAIZ).stdout
    vals = [int(m.group(1)) for m in re.finditer(r'\.word\s+(\d+)', asm[asm.index('t:'):])]
    return vals[0], vals[1:len(campos) + 1]


def main():
    nome = sys.argv[1] if len(sys.argv) > 1 else 'SaveBlock1'
    campos = campos_da_struct(nome)
    tam, offs = offsets(nome, campos)
    pares = sorted(zip(offs, campos))
    print('struct %s: %d bytes\n' % (nome, tam))
    print('%7s  %8s  %s' % ('bytes', 'offset', 'campo'))
    linhas = []
    for k, (o, n) in enumerate(pares):
        fim = pares[k + 1][0] if k + 1 < len(pares) else tam
        linhas.append((fim - o, o, n))
    for sz, o, n in sorted(linhas, reverse=True):
        print('%7d  0x%06X  %s' % (sz, o, n))


if __name__ == '__main__':
    main()
