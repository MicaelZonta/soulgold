#!/bin/bash
# Prepara o QA headless: toolchain, ROM de desenvolvimento e um mGBA headless
# (com Lua e buffer de video) compilado a partir de tools/mgba-master SEM alterar
# o fonte do repo. Uso: .claude/qa/setup.sh   (idempotente)
set -e
REPO=$(cd "$(dirname "$0")/../.." && pwd)
OUT=${QA_BUILD:-/tmp/qa-build}
mkdir -p "$OUT"

if ! command -v arm-none-eabi-gcc >/dev/null; then
  apt-get update -qq
  DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi libpng-dev \
    liblua5.4-dev zlib1g-dev libsqlite3-dev libelf-dev libedit-dev pkg-config >/dev/null
fi
python3 -c "import PIL" 2>/dev/null || pip install -q pillow

# mGBA headless com Lua (libzip desligado: o cmake do Ubuntu quebra com ele)
if [ ! -x "$OUT/qa-headless" ]; then
  mkdir -p "$OUT/mgba" && cd "$OUT/mgba"
  cmake "$REPO/tools/mgba-master" -DBUILD_HEADLESS=ON -DBUILD_QT=OFF -DBUILD_SDL=OFF \
    -DUSE_LUA=ON -DUSE_LIBZIP=OFF -DUSE_MINIZIP=OFF -DUSE_FFMPEG=OFF -DUSE_EPOXY=OFF \
    -DBUILD_GL=OFF -DBUILD_GLES2=OFF -DBUILD_GLES3=OFF -DUSE_DISCORD_RPC=OFF \
    -DCMAKE_BUILD_TYPE=Release >/dev/null
  make -j"$(nproc)" mgba-headless >/dev/null
  # O headless original nao tem buffer de video: emu:screenshot() sai vazio (33 bytes).
  cp "$REPO/tools/mgba-master/src/platform/headless-main.c" "$OUT/qa-headless.c"
  python3 - "$OUT/qa-headless.c" <<'PY'
import sys; p = sys.argv[1]; s = open(p).read()
s = s.replace("\tif (!mCoreLoadFile(core, args.fname)) {",
  "\t{ unsigned w, h; core->baseVideoSize(core, &w, &h); mColor* vb = calloc(w * h, sizeof(mColor)); core->setVideoBuffer(core, vb, w); }\n\tif (!mCoreLoadFile(core, args.fname)) {", 1)
# e o headless tambem nao liga a save a um arquivo: sem isto o save do jogo some ao fechar
s = s.replace("\tif (!mCoreLoadFile(core, args.fname)) {\n\t\tgoto loadError;\n\t}",
  "\tif (!mCoreLoadFile(core, args.fname)) {\n\t\tgoto loadError;\n\t}\n\tmCoreAutoloadSave(core);", 1)
open(p, "w").write(s)
PY
  F=CMakeFiles/mgba-headless.dir/flags.make
  DEFS=$(grep -o '\-D[A-Z_0-9]*[=A-Za-z0-9_"]*' $F | sort -u | tr '\n' ' ')
  INC=$(sed -n 's/^C_INCLUDES = //p' $F)
  gcc -O2 $DEFS $INC "$OUT/qa-headless.c" -o "$OUT/qa-headless" -L"$OUT/mgba" -lmgba -Wl,-rpath,"$OUT/mgba"
fi

cd "$REPO" && make -j"$(nproc)" -O >/dev/null
echo "ok: $OUT/qa-headless  ROM: $REPO/Soulgold.gba"
