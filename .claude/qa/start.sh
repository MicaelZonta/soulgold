#!/bin/bash
# Sobe o emulador parado esperando comandos. Rode com run_in_background (o
# processo morre junto com o shell se for so '&'). QA_DIR = pasta de trabalho.
REPO=$(cd "$(dirname "$0")/../.." && pwd)
export QA_DIR=${QA_DIR:-/tmp/qa}
mkdir -p "$QA_DIR"; rm -f "$QA_DIR"/cmd.txt "$QA_DIR"/ack.txt
cd "$QA_DIR" && exec "${QA_BUILD:-/tmp/qa-build}/qa-headless" --script "$REPO/.claude/qa/driver.lua" \
  "${1:-$REPO/Soulgold.gba}" >/dev/null 2>&1
