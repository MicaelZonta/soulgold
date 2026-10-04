#!/usr/bin/env bash
# Mede o orcamento de save e de RAM que limita aumentar OBJECT_EVENTS_COUNT,
# MAX_SPRITES e afins. Compila um .c descartavel com os mesmos flags do build
# (so para pegar sizeof), le o Soulgold.elf e imprime o que sobra.
#
# Uso: dev_scripts/medir_limites_ram_save.sh   (na raiz do repo, depois de um make)
set -euo pipefail
cd "$(git rev-parse --show-toplevel)"

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT

cat > "$tmp/sz.c" <<'EOF'
#include "global.h"
#include "save.h"
#include "sprite.h"
#include "event_object_movement.h"
const u32 v_sb1      = sizeof(struct SaveBlock1);
const u32 v_sb1_cap  = SECTOR_DATA_SIZE * (SECTOR_ID_SAVEBLOCK1_END - SECTOR_ID_SAVEBLOCK1_START + 1);
const u32 v_sb1_fut  = sizeof(((struct SaveBlock1 *)0)->futureReserved);
const u32 v_sb2      = sizeof(struct SaveBlock2);
const u32 v_sb2_cap  = SECTOR_DATA_SIZE;
const u32 v_objev    = sizeof(struct ObjectEvent);
const u32 v_objcount = OBJECT_EVENTS_COUNT;
const u32 v_sprite   = sizeof(struct Sprite);
const u32 v_maxspr   = MAX_SPRITES;
const u32 v_sectors  = SECTORS_COUNT;
EOF

arm-none-eabi-cpp -iquote include -Wno-trigraphs -DMODERN=1 -DTESTING=0 -DEMERALD -std=gnu17 "$tmp/sz.c" \
  | /usr/lib/gcc/arm-none-eabi/*/cc1 -quiet -mthumb -O2 -mabi=apcs-gnu -march=armv4t -std=gnu17 -o "$tmp/sz.s" -

val() { awk -v s="$1:" '$1==s {getline; print $2; exit}' "$tmp/sz.s"; }

sb1=$(val v_sb1); cap=$(val v_sb1_cap); objev=$(val v_objev); cnt=$(val v_objcount)
free=$((cap - sb1))
echo "== Save (flash de $(val v_sectors) setores) =="
echo "SaveBlock1: $sb1 / $cap bytes  -> $free livres no ultimo setor (+ futureReserved de $(val v_sb1_fut))"
echo "SaveBlock2: $(val v_sb2) / $(val v_sb2_cap) bytes"
echo "ObjectEvent: $objev bytes; OBJECT_EVENTS_COUNT = $cnt"
echo "  -> cabem mais $((free / objev)) objetos sem aumentar o save (maximo $((cnt + free / objev)))"
echo
echo "== Sprites =="
echo "MAX_SPRITES = $(val v_maxspr); struct Sprite = $(val v_sprite) bytes (cada +32 sprites = $(( $(val v_sprite) * 32 )) bytes de EWRAM)"
echo "gOamLimit (src/sprite.c): $(grep -m1 -oE 'gOamLimit = (0x[0-9A-Fa-f]+|[1-9][0-9]*)' src/sprite.c)"
echo
echo "== RAM (Soulgold.elf) =="
arm-none-eabi-size -A Soulgold.elf | awk '
  /^\.ewram/ {e+=$2} /^\.iwram/ {i+=$2}
  END {printf "EWRAM: %d / 262144 (%d livres)\nIWRAM: %d / 32768 (%d livres)\n", e, 262144-e, i, 32768-i}'
echo "Heap (gHeap, dentro da EWRAM): $(grep -o 'HEAP_SIZE 0x[0-9A-Fa-f]*' include/malloc.h)"
