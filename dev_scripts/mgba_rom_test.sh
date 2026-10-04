#!/usr/bin/env bash
# Substituto do mgba-rom-test pre-compilado para `make check`.
#
# A ROM (e a de teste, ~55 MiB por shard) passa de 32 MiB e so roda no mGBA
# patchado de tools/mgba-master. O mgba-headless dele aceita as mesmas opcoes
# que o mgba-rom-test-hydra passa (-l, -C, -R; sai no SWI 3), mas sem libelf
# nao carrega ELF - e no Linux o hydra entrega o ELF direto. Entao: converte
# para binario num arquivo temporario e chama o headless.
#
# Uso (pelo hydra): mgba_rom_test.sh [opcoes do mGBA...] <rom ou elf>
set -euo pipefail

ROOT=$(cd "$(dirname "$0")/.." && pwd)
HEADLESS=${MGBA_HEADLESS:-$ROOT/build/mgba-rom-test/mgba-headless}
OBJCOPY=${OBJCOPY:-arm-none-eabi-objcopy}

rom=${*: -1}
opts=("${@:1:$#-1}")

if [ "$(head -c 4 "$rom" | od -An -c | tr -d ' ')" = '177ELF' ]; then
    bin=$(mktemp "${TMPDIR:-/tmp}/mgba-rom-test-XXXXXX.gba")
    trap 'rm -f "$bin"' EXIT
    "$OBJCOPY" -O binary "$rom" "$bin"
    rom=$bin
fi

# Sem exec: o trap precisa apagar o binario temporario no fim.
"$HEADLESS" "${opts[@]}" "$rom"
