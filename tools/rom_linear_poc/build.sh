#!/usr/bin/env bash
# POC do mapeamento linear de 96 MB: compila o mGBA patchado (tools/mgba-master)
# e o romrun (runner headless) em $OUT (padrao: build/rom_linear_poc).
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
OUT=${OUT:-$ROOT/build/rom_linear_poc}
M=$ROOT/tools/mgba-master
mkdir -p "$OUT/mgba"
cmake -S "$M" -B "$OUT/mgba" -DCMAKE_BUILD_TYPE=Release -DBUILD_HEADLESS=ON \
    -DBUILD_QT=OFF -DBUILD_SDL=OFF -DUSE_FFMPEG=OFF -DUSE_EDITLINE=OFF -DUSE_ELF=OFF \
    -DUSE_LUA=OFF -DENABLE_SCRIPTING=OFF -DUSE_DISCORD_RPC=OFF -DUSE_SQLITE3=OFF \
    -DUSE_LIBZIP=OFF -DUSE_MINIZIP=OFF -DBUILD_STATIC=ON -DBUILD_SHARED=OFF \
    -DM_CORE_GB=OFF -DUSE_DEBUGGERS=OFF -DUSE_GDB_STUB=OFF > "$OUT/cmake.log"
make -C "$OUT/mgba" -j"$(nproc)" mgba mgba-headless > "$OUT/make.log"
# Mesmos defines que o libmgba foi compilado, senao o layout de struct mCore diverge.
DEFS=$(grep C_DEFINES "$(find "$OUT/mgba" -path '*mgba-headless.dir/flags.make')" | cut -d= -f2-)
# shellcheck disable=SC2086
gcc -O2 -std=gnu11 $DEFS -o "$OUT/romrun" "$ROOT/tools/rom_linear_poc/romrun.c" \
    -I"$OUT/mgba/include" -I"$M/src" -I"$M/include" "$OUT/mgba/libmgba.a" \
    -lpng -lfreetype -lz -lm -lpthread
echo "ok: $OUT/romrun  e  $OUT/mgba/mgba-headless"
