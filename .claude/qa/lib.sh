# Macros de navegacao do menu de debug (L+START)
QA_DIR=${QA_DIR:-/tmp/qa}; Q="python3 $(dirname "${BASH_SOURCE[0]}")/q.py"
dbg_main() { # $1 = indice no menu principal
  echo "combo L+START 10 40; rep $1 press DOWN 4 8; press A 6 30"; }
bm() { # $1 = indice no submenu Berry Master
  echo "$(dbg_main 9); rep $1 press DOWN 4 8; press A 6 30"; }
# seqshots PREFIX N : print, A, print, A ... (N prints)
seqshots() { local s=""; for i in $(seq 1 $2); do s="$s; wait 70; shot $1_$(printf %02d $i).png"; [ $i -lt $2 ] && s="$s; press A 6 20"; done; echo "${s#; }"; }
clean() { echo "rep 8 press B 6 24; wait 20"; }
clock() { echo "$(bm 3); rep $1 press DOWN 4 8; press A 6 30"; }  # 0:+1h 1:+6h 2:+24h 3:7:00 4:new day
QA_TOOLS=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
pos() { python3 -c "import sys; sys.path.insert(0,'$QA_TOOLS'); import ir; print('pos=%s' % (ir.pos(),))"; }
# num N : digita N no seletor numerico do debug (comeca em 1, digito das unidades)
num() { local n=$1 h=$(( $1/100 )) t=$(( ($1/10)%10 )) o=$(( $1%10 )) s="press RIGHT 4 6; press RIGHT 4 6"
  s="$s; rep $h press UP 4 6; press LEFT 4 6; rep $t press UP 4 6; press LEFT 4 6"
  if [ $o -eq 0 ]; then s="$s; press DOWN 4 6"; else s="$s; rep $(( o-1 )) press UP 4 6"; fi
  echo "$s" | sed 's/rep 0 [^;]*;//g'; }
give() { echo "$(dbg_main 3); press A 6 30; $(num $1); press A 6 30; $(num $2); press A 6 40"; }  # give ITEM QTD
num0() { local h=$(( $1/100 )) t=$(( ($1/10)%10 )) o=$(( $1%10 ))
  echo "press RIGHT 4 6; press RIGHT 4 6; rep $h press UP 4 6; press LEFT 4 6; rep $t press UP 4 6; press LEFT 4 6; rep $o press UP 4 6" | sed 's/rep 0 [^;]*;//g; s/; rep 0 [^;]*$//'; }
warp() { echo "$(dbg_main 0); press DOWN 4 8; press A 6 30; $(num0 $1); press A 6 20; $(num0 $2); press A 6 20; $(num0 $3); press A 6 20"; }  # warp GRUPO MAPA WARP
book() { echo "$(bm 4); rep $1 press DOWN 4 8; press A 6 30"; }  # 0:8 1:11 2:12 3:22 4:32 5:60 6:66 7:67 8:unpaid
lvl() { echo "$(bm 5); rep $(( $1-1 )) press DOWN 4 8; press A 6 30"; }  # lvl 1..4
fill() { echo "$(dbg_main 1); press DOWN 4 8; press A 6 30; rep $1 press DOWN 4 8; press A 6 60"; }  # 3:Items 6:Berries
clearbag() { echo "$(dbg_main 1); press DOWN 4 8; press DOWN 4 8; press A 6 60"; }
