#!/usr/bin/env bash
# Compila o mGBA patchado do repo (tools/mgba-master, unico que carrega a ROM
# de 96 MB) como emulador normal de Windows - frontend Qt, com menu e controle
# (SDL2) - e atualiza a pasta de emuladores do autor. Roda no WSL; a
# compilacao em si acontece no MSYS2 do Windows (caminho oficial do mGBA).
#
# Uso: make mgba-windows    (ou tools/mgba-windows/build.sh)
#
# Variaveis opcionais (caminhos Windows):
#   MSYS2_ROOT  padrao %USERPROFILE%\msys64
#   MGBA_WORK   padrao %USERPROFILE%   (cria mgba-soulgold-src e -build ali)
#   MGBA_DEST   padrao %USERPROFILE%\Documents\Emulators\mGBA SoulGold
#
# A configuracao (controles, perfil do DualSense) fica em %APPDATA%\mGBA e e
# compartilhada com o mGBA oficial instalado - recompilar nao mexe nela.
set -euo pipefail

ROOT=$(cd "$(dirname "$0")/../.." && pwd)
die() { echo "erro: $*" >&2; exit 1; }

command -v cmd.exe >/dev/null || die "cmd.exe nao encontrado - isto precisa rodar no WSL"
WINHOME=$(cd /mnt/c && cmd.exe /c 'echo %USERPROFILE%' 2>/dev/null | tr -d '\r')
[ -n "$WINHOME" ] || die "nao consegui ler %USERPROFILE%"

MSYS2_ROOT=${MSYS2_ROOT:-$WINHOME\\msys64}
MGBA_WORK=${MGBA_WORK:-$WINHOME}
MGBA_DEST=${MGBA_DEST:-$WINHOME\\Documents\\Emulators\\mGBA SoulGold}

BASH_EXE=$(wslpath -u "$MSYS2_ROOT")/usr/bin/bash.exe
if [ ! -x "$BASH_EXE" ]; then
    die "MSYS2 nao encontrado em $MSYS2_ROOT. Para instalar (sem admin):
  curl -fL -o msys2.tar.zst https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.zst
  copie para $WINHOME e extraia com o tar do Windows:  tar -xf msys2.tar.zst -C \"$WINHOME\"
  depois, no bash.exe do MSYS2:  pacman -Syuu --noconfirm
  (os pacotes do mGBA o msys_build.sh instala sozinho)"
fi

if tasklist.exe 2>/dev/null | grep -qi '^mGBA\.exe'; then
    die "feche o mGBA antes de recompilar (o Windows trava o exe aberto)"
fi

WORK_U=$(wslpath -u "$MGBA_WORK")
mkdir -p "$WORK_U/mgba-soulgold-src"
rsync -a --delete --exclude 'build*/' "$ROOT/tools/mgba-master/" "$WORK_U/mgba-soulgold-src/"
cp "$ROOT/tools/mgba-windows/msys_build.sh" "$WORK_U/mgba-soulgold-src/.msys_build.sh"

# Caminhos no formato do MSYS2 (/c/Users/...).
to_msys() { local u; u=$(wslpath -u "$1"); echo "/${u#/mnt/}"; }

cd "$WORK_U"
"$BASH_EXE" -l "$(to_msys "$MGBA_WORK")/mgba-soulgold-src/.msys_build.sh" \
    "$(to_msys "$MGBA_WORK")" "$(to_msys "$MGBA_DEST")"
