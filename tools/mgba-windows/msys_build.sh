# Roda DENTRO do MSYS2 (chamado por tools/mgba-windows/build.sh).
# Uso: msys_build.sh <pasta de trabalho> <pasta destino>   (caminhos MSYS2)
export MSYSTEM=UCRT64
source /etc/profile
# set -e so depois do /etc/profile: ele tem comandos que falham de proposito.
set -euo pipefail

WORK=$1
DEST=$2
SRC=$WORK/mgba-soulgold-src
BUILD=$WORK/mgba-soulgold-build

pacman -S --needed --noconfirm make \
    mingw-w64-ucrt-x86_64-{cmake,gcc,libepoxy,libzip,pkgconf,qt6-base,qt6-multimedia,qt6-tools,qt6-translations,SDL2,sqlite3,libpng,zlib,ntldd} \
    > "$WORK/mgba-soulgold-pacman.log"

# Estatico (libmgba dentro do exe): com libmgba.dll o exe morre ao abrir com
# "32 bit pseudo relocation out of range". SDL ligado: e o SDL que le o
# controle no frontend Qt.
echo "== configurando"
cmake -S "$SRC" -B "$BUILD" -G "MSYS Makefiles" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_QT=ON -DFORCE_QT_VERSION=6 \
    -DBUILD_SDL=ON -DSDL_VERSION=2 \
    -DBUILD_STATIC=ON -DBUILD_SHARED=OFF \
    -DUSE_FFMPEG=OFF -DUSE_LUA=OFF -DENABLE_SCRIPTING=OFF -DUSE_DISCORD_RPC=OFF \
    > "$WORK/mgba-soulgold-cmake.log"
echo "== compilando (log: $WORK/mgba-soulgold-make.log)"
make -C "$BUILD" -j"$(nproc)" mgba-qt > "$WORK/mgba-soulgold-make.log" 2>&1 \
    || { tail -30 "$WORK/mgba-soulgold-make.log"; exit 1; }

# Atualiza a pasta sem apaga-la (pode ter saves/portable.ini do autor).
echo "== instalando em $DEST"
mkdir -p "$DEST"
cp "$BUILD/mGBA.exe" "$DEST/"
windeployqt6 --release --no-translations "$DEST/mGBA.exe" > "$WORK/mgba-soulgold-deploy.log" 2>&1
for f in "$DEST"/*.exe "$DEST"/*.dll "$DEST"/*/*.dll; do
    { ntldd -R "$f" 2>/dev/null | grep -i 'ucrt64' | sed 's/.*=> \(.*\) (0x.*/\1/'; } || true
done | sort -u | while read -r p; do cp -u "$(cygpath -u "$p")" "$DEST"/; done

ls -la "$DEST/mGBA.exe"
echo "ok: mGBA SoulGold atualizado ($(du -sh "$DEST" | cut -f1))"
