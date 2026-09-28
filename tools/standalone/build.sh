#!/usr/bin/env bash
# Jogaveis standalone do SoulGold: o mGBA patchado do repo (tools/mgba-master,
# unico que carrega a ROM de 96 MB) compilado com a ROM embutida, bootando
# direto no jogo sem menu:
#
#   Soulgold.exe  - Windows x86_64. ROM embutida no proprio exe; no primeiro
#                   uso ela e extraida para ao lado do executavel e o .sav
#                   nasce ali. Um arquivo so, duplo clique e joga.
#   Soulgold.nro  - Switch com CFW (Homebrew Launcher). ROM no RomFS do .nro;
#                   saves em <config do mgba>/soulgold no SD.
#
# Uso: tools/standalone/build.sh [--pc] [--switch]   (sem argumento: os dois)
# Chamado por `make standalone` / `standalone-pc` / `standalone-switch`.
set -euo pipefail

ROOT=$(cd "$(dirname "$0")/../.." && pwd)
MGBA=$ROOT/tools/mgba-master
ROM=$ROOT/Soulgold.gba
OUT=$ROOT/build/standalone
DEPS=$ROOT/tools/standalone/deps
SDL2_VER=2.30.11
JOBS=$(nproc)

die() { echo "erro: $*" >&2; exit 1; }

[ -f "$ROM" ] || die "Soulgold.gba nao existe - rode 'make' antes (o alvo 'make standalone' ja faz isso)"

# Flags comuns: mesmo espirito do tools/rom_linear_poc/build.sh - so o nucleo
# GBA, sem os opcionais que pedem bibliotecas extras.
COMMON_FLAGS=(
    -DCMAKE_BUILD_TYPE=Release
    -DBUILD_QT=OFF -DUSE_FFMPEG=OFF -DUSE_MINIZIP=OFF -DUSE_LIBZIP=OFF
    -DUSE_SQLITE3=OFF -DUSE_ELF=OFF -DUSE_LUA=OFF -DENABLE_SCRIPTING=OFF
    -DUSE_DISCORD_RPC=OFF -DUSE_DEBUGGERS=OFF -DUSE_GDB_STUB=OFF
    -DUSE_EDITLINE=OFF -DM_CORE_GB=OFF
)

build_pc() {
    echo "== Soulgold.exe (Windows x86_64) =="
    command -v x86_64-w64-mingw32-gcc >/dev/null \
        || die "mingw-w64 nao instalado. Rode: sudo apt install mingw-w64 pkg-config"
    command -v pkg-config >/dev/null \
        || die "pkg-config nao instalado. Rode: sudo apt install pkg-config"

    # SDL2 devel para mingw, preparado para link ESTATICO (exe de arquivo
    # unico): apaga import libs/DLL para -lSDL2 resolver na libSDL2.a, apaga o
    # config de CMake para o mGBA cair no caminho pkg-config (que controlamos
    # via sdl2.pc), conserta o prefix e funde Libs.private em Libs.
    local P=$DEPS/SDL2-$SDL2_VER/x86_64-w64-mingw32
    if [ ! -f "$P/.prepared" ]; then
        mkdir -p "$DEPS"
        local TAR=$DEPS/SDL2-devel-$SDL2_VER-mingw.tar.gz
        [ -f "$TAR" ] || curl -fL --retry 3 -o "$TAR" \
            "https://github.com/libsdl-org/SDL/releases/download/release-$SDL2_VER/SDL2-devel-$SDL2_VER-mingw.tar.gz"
        tar -xzf "$TAR" -C "$DEPS"
        rm -f "$P"/lib/libSDL2.dll.a "$P"/bin/SDL2.dll
        rm -rf "$P"/lib/cmake
        python3 - "$P" <<'EOF'
import re, sys, pathlib
prefix = sys.argv[1]
pc = pathlib.Path(prefix) / "lib/pkgconfig/sdl2.pc"
text = pc.read_text()
text = re.sub(r"^prefix=.*$", "prefix=" + prefix, text, flags=re.M)
priv = re.search(r"^Libs\.private:\s*(.*)$", text, flags=re.M)
if priv:
    text = re.sub(r"^(Libs:.*)$", r"\1 " + priv.group(1).replace("\\", "\\\\"), text, flags=re.M)
pc.write_text(text)
EOF
        touch "$P/.prepared"
    fi

    # ROM como objeto linkavel: simbolos _binary_soulgold_rom_bin_{start,end}.
    mkdir -p "$OUT/pc"
    cp "$ROM" "$OUT/pc/soulgold_rom.bin"
    (cd "$OUT/pc" && x86_64-w64-mingw32-ld -r -b binary soulgold_rom.bin -o soulgold_rom.o)

    PKG_CONFIG_LIBDIR="$P/lib/pkgconfig" SOULGOLD_SDL2_PREFIX="$P" \
    cmake -S "$MGBA" -B "$OUT/pc/mgba" \
        -DCMAKE_TOOLCHAIN_FILE="$ROOT/tools/standalone/mingw-w64-x86_64.cmake" \
        "${COMMON_FLAGS[@]}" \
        -DBUILD_SDL=ON -DSDL_VERSION=2 \
        -DBUILD_GL=OFF -DBUILD_GLES2=OFF -DBUILD_GLES3=OFF -DUSE_EPOXY=OFF \
        -DUSE_ZLIB=OFF -DUSE_PNG=OFF \
        -DBUILD_STATIC=ON -DBUILD_SHARED=OFF \
        -DCMAKE_C_FLAGS="-DSOULGOLD_STANDALONE" \
        -DCMAKE_EXE_LINKER_FLAGS="$OUT/pc/soulgold_rom.o -static" \
        > "$OUT/pc/cmake.log"
    make -C "$OUT/pc/mgba" -j"$JOBS" mgba-sdl > "$OUT/pc/make.log"

    local EXE
    EXE=$(find "$OUT/pc/mgba" -maxdepth 2 -name 'mgba*.exe' | head -1)
    [ -n "$EXE" ] || die "build ok mas nao achei o .exe em $OUT/pc/mgba"
    # A ROM embutida tem 30+ MB; um exe menor que ela significa blob de fora.
    [ "$(stat -c%s "$EXE")" -gt "$(stat -c%s "$ROM")" ] \
        || die "$EXE menor que a ROM - o blob nao foi linkado"
    cp "$EXE" "$ROOT/Soulgold.exe"
    echo "ok: $ROOT/Soulgold.exe ($(du -h "$ROOT/Soulgold.exe" | cut -f1))"
}

build_switch() {
    echo "== Soulgold.nro (Switch, CFW) =="
    local DKP=${DEVKITPRO:-/opt/devkitpro}
    if [ ! -x "$DKP/devkitA64/bin/aarch64-none-elf-gcc" ] || [ ! -x "$DKP/tools/bin/elf2nro" ]; then
        die "devkitPro nao instalado. Rode:
  wget https://apt.devkitpro.org/install-devkitpro-pacman
  chmod +x install-devkitpro-pacman && sudo ./install-devkitpro-pacman
  sudo dkp-pacman -S switch-dev switch-tools switch-mesa switch-libdrm_nouveau \\
      switch-zlib switch-libpng switch-freetype"
    fi
    export DEVKITPRO=$DKP
    export PATH=$DKP/tools/bin:$DKP/devkitA64/bin:$PATH

    mkdir -p "$OUT/switch"
    cmake -S "$MGBA" -B "$OUT/switch/mgba" \
        -DCMAKE_TOOLCHAIN_FILE="$MGBA/src/platform/switch/CMakeToolchain.txt" \
        "${COMMON_FLAGS[@]}" \
        -DSOULGOLD_ROM="$ROM" \
        -DCMAKE_C_FLAGS="-DSOULGOLD_STANDALONE" \
        > "$OUT/switch/cmake.log"
    make -C "$OUT/switch/mgba" -j"$JOBS" mgba.nro > "$OUT/switch/make.log"

    local NRO
    NRO=$(find "$OUT/switch/mgba" -name 'mgba.nro' | head -1)
    [ -n "$NRO" ] || die "build ok mas nao achei o .nro em $OUT/switch/mgba"
    [ "$(stat -c%s "$NRO")" -gt "$(stat -c%s "$ROM")" ] \
        || die "$NRO menor que a ROM - o RomFS nao levou a Soulgold.gba"
    cp "$NRO" "$ROOT/Soulgold.nro"
    echo "ok: $ROOT/Soulgold.nro ($(du -h "$ROOT/Soulgold.nro" | cut -f1))"
    echo "    (copie para sd:/switch/ e abra pelo Homebrew Launcher em modo"
    echo "     full-app - segurando R sobre um jogo - por causa da RAM)"
}

PC=0; SWITCH=0
for arg in "$@"; do
    case $arg in
        --pc) PC=1 ;;
        --switch) SWITCH=1 ;;
        *) die "argumento desconhecido: $arg (use --pc e/ou --switch)" ;;
    esac
done
if [ $PC -eq 0 ] && [ $SWITCH -eq 0 ]; then PC=1; SWITCH=1; fi

mkdir -p "$OUT"
[ $PC -eq 1 ] && build_pc
[ $SWITCH -eq 1 ] && build_switch
echo "standalone: concluido"
