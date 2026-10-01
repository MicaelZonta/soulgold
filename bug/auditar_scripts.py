#!/usr/bin/env python3
"""Auditoria estatica de scripts de mapa: travamentos, estados e objetos.

Roda na raiz do repo (depois de um build, para os .inc gerados dos .pory
existirem):

    python3 bug/auditar_scripts.py            # relatorio completo
    python3 bug/auditar_scripts.py --so TRAVA # so uma categoria

Categorias (cada achado sai com arquivo:linha):

  TRAVA_LOCK     caminho que chega a `end` com lock/lockall ativo -> NPCs
                 parados e jogador sem animacao ate trocar de mapa (nao trava).
                 Segue call/goto/goto_if/case entre arquivos. _POSSIVEL = logo
                 apos switch/goto_if VAR_RESULT, quase sempre inalcancavel
  TRAVA_LACO     laco sem nenhum comando que espere frame -> congela de vez.
                 _POSSIVEL = o laco muda estado, pode terminar
  TRAVA_FRAME_PERSIST  map_script_2 condicionado a var persistente (so aviso;
                 TRAVA_FRAME e quem diz se o alvo muda a var)
  TRAVA_FRAME    alvo de map_script_2 (ON_FRAME_TABLE) com caminho que termina
                 sem escrever a var da condicao -> dispara todo frame (livelock)
  TRAVA_IMEDIATO comando que espera frame (msgbox, waitmovement, delay, lock,
                 fadescreen...) num script de ON_LOAD / ON_TRANSITION /
                 ON_RESUME / ON_RETURN_TO_FIELD / ON_WARP_INTO / coord event
                 com var 0: RunScriptImmediately gira em loop -> congela
  CALL_END       `call` para rotina que termina em `end`: o resto do chamador
                 nunca roda (inclusive o release dele)
  OBJ_ID         applymovement/removeobject/... com local id que nao existe
                 no mapa (LOCALID de outro mapa ou numero > qtde de objetos)
  REMOVE_FLAG    removeobject em objeto cuja flag do template nao e de
                 ocultacao (FLAG_GARBAGEFLAG, item, progresso)
  WARP           warp para mapa fora da ROM, warp id inexistente ou x,y fora
                 do layout
  VAR_ESTADO     var comparada com valor que nada escreve (ramo morto ou
                 setvar esquecido)
  TRAINER_DUP    mesmo TRAINER_* em dois mapas (dividem a flag de derrota)
  FALLTHROUGH    rotina sem end/return/goto que cai na label seguinte
"""
import argparse
import collections
import json
import os
import re
import sys

ROOT = os.getcwd()

# ---------------------------------------------------------------- mapas
groups = json.load(open("data/maps/map_groups.json"))
excluded = {m for g in groups["rom_excluded_groups"] for m in groups[g]}
shared = set(groups["rom_shared_script_maps"])
all_maps = [m for g in groups["group_order"] for m in groups[g]]
live_maps = [m for m in all_maps if m not in excluded]
import subprocess
_ina = subprocess.run([sys.executable, "dev_scripts/map_graph.py", "inalcancaveis"],
                      capture_output=True, text=True).stdout
unreachable = {l.split()[0] for l in _ina.splitlines() if l.strip() and not l.startswith(" ")}
# mapas que o jogador consegue pisar (ligados ao mundo)
play_maps = [m for m in live_maps if m not in unreachable]

layouts = {l["id"]: l for l in json.load(open("data/layouts/layouts.json"))["layouts"] if "id" in l}
mapinfo = {}          # nome da pasta -> dict
mapid_to_name = {}
for m in all_maps:
    p = f"data/maps/{m}/map.json"
    if not os.path.exists(p):
        continue
    d = json.load(open(p))
    mapinfo[m] = d
    mapid_to_name[d["id"]] = m

# ---------------------------------------------------------------- scripts
FILTERED = "build/emerald/data/event_scripts.filtered.s"
if not os.path.exists(FILTERED):
    sys.exit(f"falta {FILTERED}: rode `make -j$(nproc)` antes")
files = [("data/event_scripts.s", None)]
for inc in re.findall(r'^\s*\.include\s+"(data/[^"]+\.inc)"', open(FILTERED).read(), re.M):
    if inc.startswith(("data/text/", "data/script_cmd_table", "data/specials")):
        continue
    mm = re.match(r"data/maps/([^/]+)/scripts\.inc", inc)
    files.append((inc, mm.group(1) if mm else None))

LABEL = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)::?\s*(?:@.*)?$")
insts = {}     # arquivo -> lista de (linha, cmd, args)
labels = {}    # label -> (arquivo, idx)
filemap = {}
sets = {}      # (arquivo) -> {.set nome: valor}
for path, m in files:
    filemap[path] = m
    out = []
    loc = {}
    for n, raw in enumerate(open(path, encoding="utf-8", errors="replace"), 1):
        line = raw.split("@")[0].split("//")[0].strip()
        if not line:
            continue
        lm = LABEL.match(line)
        if lm:
            labels.setdefault(lm.group(1), (path, len(out)))
            continue
        if line.startswith(".set"):
            a = [x.strip() for x in line[4:].split(",")]
            if len(a) == 2:
                loc[a[0]] = a[1]
            continue
        if line.startswith((".", "#")):
            parts = line.split(None, 1)
            args = [x.strip() for x in parts[1].split(",")] if len(parts) > 1 and parts[0] == ".4byte" else []
            out.append((n, parts[0], args))
            continue
        parts = line.split(None, 1)
        args = []
        if len(parts) > 1:
            for x in parts[1].split(","):
                x = x.strip()
                # macro GAS aceita argumento separado por espaco
                args += x.split() if re.fullmatch(r"[A-Za-z0-9_]+(\s+[A-Za-z0-9_]+)+", x) else [x]
        out.append((n, parts[0], args))
    insts[path] = out
    sets[path] = loc

TERM = {"end", "endram", "return", "goto", "releaseend", "step_end"}
WARPS = {"warp", "warpsilent", "warpdoor", "warphole", "warpteleport", "warpspinenter",
         "warpmossdeepgym", "warpwhitefade", "warpsootopolislegend", "warp_heal"}
BLOCKING = {"msgbox", "message", "waitmessage", "waitbuttonpress", "waitmovement", "delay",
            "fadescreen", "fadescreenspeed", "fadescreenswapbuffers", "waitstate", "waitfanfare",
            "waitse", "waitmoncry", "lock", "lockall", "yesnobox", "multichoice",
            "multichoicedefault", "dowildbattle", "trainerbattle_single", "waitdooranim",
            "playfanfare", "giveitem", "finditem", "givemon", "waitmovementat", "fadedefaultbgm"}
LOCKCMDS = {"lock", "lockall"}
RELCMDS = {"release", "releaseall", "releaseend"}
MSG_RELEASE = {"MSGBOX_NPC", "MSGBOX_SIGN", "MSGBOX_AUTOCLOSE", "2", "3", "6"}
OBJCMDS = {"applymovement", "removeobject", "addobject", "turnobject", "setobjectxy",
           "setobjectxyperm", "showobjectat", "hideobjectat", "setobjectmovementtype",
           "setobjectsubpriority", "resetobjectsubpriority", "copyobjectxytoperm"}
SPECIAL_IDS = {"LOCALID_PLAYER", "OBJ_EVENT_ID_PLAYER", "LOCALID_FOLLOWER", "OBJ_EVENT_ID_FOLLOWER",
               "LOCALID_CAMERA", "OBJ_EVENT_ID_CAMERA", "255", "254", "127", "0xFF", "0xFE",
               "VAR_LAST_TALKED", "LOCALID_NONE", "OBJ_EVENT_ID_NPC_FOLLOWER"}

findings = collections.defaultdict(list)


def add(cat, path, line, msg):
    findings[cat].append((path, line, msg))


def label_args(cmd, args):
    """labels para onde o comando pode desviar."""
    if cmd in ("goto", "call"):
        return args[:1]
    if cmd.startswith(("goto_if", "call_if")) or cmd == "case":
        return args[-1:]
    if cmd.startswith("trainerbattle"):
        return [a for a in args if a in labels]
    return []


# ------------------------------------------------ TRAVA_LOCK / CALL_END
def ends_with_end(path, idx, seen=None):
    """a rotina que comeca em idx termina (por algum caminho) com end?"""
    seen = seen or set()
    code = insts[path]
    i = idx
    while i < len(code):
        if (path, i) in seen:
            return False
        seen.add((path, i))
        n, cmd, args = code[i]
        if cmd in ("end", "releaseend", "endram"):
            prev = code[i - 1][1] if i else ""
            # `end` logo apos switch/goto_if exaustivo costuma ser inalcancavel
            return not (prev == "case" or prev.startswith("goto_if"))
        if cmd == "return":
            return False
        if cmd in WARPS:
            return False
        if cmd == "goto":
            t = labels.get(args[0]) if args else None
            return bool(t) and ends_with_end(*t, seen)
        if cmd.startswith("goto_if") or cmd == "case":
            t = labels.get(args[-1])
            if t and ends_with_end(*t, seen):
                return True
        i += 1
    return False


def walk_lock(entry_label, why):
    if entry_label not in labels:
        return
    start = labels[entry_label]
    stack = [(start[0], start[1], False, ())]
    seen = set()
    steps = 0
    while stack:
        path, i, locked, cs = stack.pop()
        while True:
            steps += 1
            if steps > 400000:
                return
            key = (path, i, locked, cs)
            if key in seen:
                break
            seen.add(key)
            code = insts[path]
            if i >= len(code):
                break
            n, cmd, args = code[i]
            if cmd in LOCKCMDS:
                locked = True
            elif cmd in RELCMDS:
                locked = False
            elif cmd in ("msgbox",) and len(args) > 1 and args[1] in MSG_RELEASE:
                locked = False
            elif cmd == "callstd" and args and args[0] in MSG_RELEASE:
                locked = False
            if cmd in WARPS:
                break               # troca de mapa recria os objetos
            if cmd in ("end", "endram") or (cmd == "return" and not cs):
                if locked:
                    prev = code[i - 1] if i else (0, "", [])
                    guarded = prev[1] == "case" or (prev[1].startswith("goto_if") and prev[2][:1] == ["VAR_RESULT"])
                    cat = "TRAVA_LOCK_POSSIVEL" if guarded else "TRAVA_LOCK"
                    add(cat, path, n, f"`{cmd}` com lock ativo (entrada: {entry_label}, {why})"
                        + (" -- logo apos switch/goto_if VAR_RESULT: talvez inalcancavel" if guarded else ""))
                break
            if cmd == "releaseend":
                break
            if cmd == "return":
                rp, ri = cs[-1]
                path, i, cs = rp, ri, cs[:-1]
                continue
            if cmd == "goto":
                t = labels.get(args[0]) if args else None
                if not t:
                    break
                path, i = t
                continue
            if cmd == "call" or cmd.startswith("call_if"):
                t = labels.get(args[-1] if cmd != "call" else args[0])
                if t and len(cs) < 8:
                    if cmd == "call":
                        cs2 = cs + ((path, i + 1),)
                        path, i, cs = t[0], t[1], cs2
                        continue
                    stack.append((t[0], t[1], locked, cs + ((path, i + 1),)))
                i += 1
                continue
            if cmd.startswith("goto_if") or cmd == "case":
                t = labels.get(args[-1]) if args else None
                if t:
                    stack.append((t[0], t[1], locked, cs))
            i += 1


# ------------------------------------------------ TRAVA_FRAME
def var_written(cmd, args, var):
    if not args:
        return False
    if cmd in ("setvar", "addvar", "subvar", "copyvar", "specialvar", "setorcopyvar",
               "random", "getpartysize", "checkitem"):
        return args[0] == var
    return False


def walk_frame(entry_label, var, value, table_path, table_line):
    if entry_label not in labels:
        add("TRAVA_FRAME", table_path, table_line, f"alvo {entry_label} nao existe")
        return
    start = labels[entry_label]
    stack = [(start[0], start[1], ())]
    seen = set()
    bad = set()
    while stack:
        path, i, cs = stack.pop()
        while True:
            key = (path, i, cs)
            if key in seen:
                break
            seen.add(key)
            code = insts[path]
            if i >= len(code):
                break
            n, cmd, args = code[i]
            if var_written(cmd, args, var):
                if not (cmd == "setvar" and len(args) > 1 and args[1] == value):
                    break          # este caminho muda a condicao: ok
            if cmd in WARPS:
                break               # troca de mapa: var temp zera
            if cmd in ("end", "endram", "releaseend") or (cmd == "return" and not cs):
                bad.add((path, n))
                break
            if cmd == "return":
                (path, i), cs = cs[-1], cs[:-1]
                continue
            if cmd == "goto":
                t = labels.get(args[0]) if args else None
                if not t:
                    break
                path, i = t
                continue
            if cmd == "call" or cmd.startswith("call_if"):
                t = labels.get(args[0] if cmd == "call" else args[-1])
                if t and len(cs) < 8:
                    if cmd == "call":
                        path, i, cs = t[0], t[1], cs + ((path, i + 1),)
                        continue
                    stack.append((t[0], t[1], cs + ((path, i + 1),)))
                i += 1
                continue
            if cmd.startswith("goto_if") or cmd == "case":
                t = labels.get(args[-1]) if args else None
                if t:
                    stack.append((t[0], t[1], cs))
            i += 1
    for p, n in sorted(bad):
        add("TRAVA_FRAME", p, n,
            f"`map_script_2 {var}, {value}, {entry_label}` ({table_path}:{table_line}) "
            f"chega aqui sem mudar {var}")


# ------------------------------------------------ TRAVA_IMEDIATO
def walk_immediate(entry_label, why):
    if entry_label not in labels:
        return
    start = labels[entry_label]
    stack = [(start[0], start[1], ())]
    seen = set()
    while stack:
        path, i, cs = stack.pop()
        while True:
            key = (path, i, cs)
            if key in seen:
                break
            seen.add(key)
            code = insts[path]
            if i >= len(code):
                break
            n, cmd, args = code[i]
            if cmd in BLOCKING:
                add("TRAVA_IMEDIATO", path, n, f"`{cmd}` em script imediato ({why}: {entry_label})")
            if cmd in ("end", "endram") or (cmd == "return" and not cs):
                break
            if cmd == "return":
                (path, i), cs = cs[-1], cs[:-1]
                continue
            if cmd == "goto":
                t = labels.get(args[0]) if args else None
                if not t:
                    break
                path, i = t
                continue
            if cmd == "call" or cmd.startswith("call_if"):
                t = labels.get(args[0] if cmd == "call" else args[-1])
                if t and len(cs) < 8:
                    if cmd == "call":
                        path, i, cs = t[0], t[1], cs + ((path, i + 1),)
                        continue
                    stack.append((t[0], t[1], cs + ((path, i + 1),)))
                i += 1
                continue
            if cmd.startswith("goto_if") or cmd == "case":
                t = labels.get(args[-1]) if args else None
                if t:
                    stack.append((t[0], t[1], cs))
            i += 1


IMMEDIATE = {"MAP_SCRIPT_ON_LOAD", "MAP_SCRIPT_ON_TRANSITION", "MAP_SCRIPT_ON_RESUME",
             "MAP_SCRIPT_ON_RETURN_TO_FIELD", "MAP_SCRIPT_ON_DIVE_WARP"}


def map_tables(m):
    lab = f"{m}_MapScripts"
    if lab not in labels:
        return []
    path, i = labels[lab]
    out = []
    code = insts[path]
    while i < len(code):
        n, cmd, args = code[i]
        if cmd != "map_script":
            break
        out.append((n, args[0], args[1]))
        i += 1
    return out


def table_entries(label):
    """entradas de uma tabela map_script_2."""
    path, i = labels[label]
    code = insts[path]
    out = []
    while i < len(code):
        n, cmd, args = code[i]
        if cmd != "map_script_2":
            break
        out.append((n, args[0], args[1], args[2]))
        i += 1
    return path, out


# ------------------------------------------------ roda por mapa
entries = []   # (label, why, mapa)
for m in play_maps:
    d = mapinfo.get(m)
    if not d:
        continue
    for n, kind, lab in map_tables(m):
        if kind in IMMEDIATE:
            walk_immediate(lab, kind)
            walk_lock(lab, kind)
        elif kind == "MAP_SCRIPT_ON_FRAME_TABLE" and lab in labels:
            tp, ents = table_entries(lab)
            for tn, var, val, target in ents:
                if not var.startswith("VAR_TEMP"):
                    add("TRAVA_FRAME_PERSIST", tp, tn,
                        f"`map_script_2 {var}, {val}` usa var persistente (dispara em toda visita enquanto valer)")
                walk_frame(target, var, val, tp, tn)
                entries.append((target, "ON_FRAME", m))
        elif kind == "MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE" and lab in labels:
            tp, ents = table_entries(lab)
            for tn, var, val, target in ents:
                walk_immediate(target, "ON_WARP_INTO")
    for o in d.get("object_events", []):
        if o.get("script") and o["script"] != "NULL":
            entries.append((o["script"], "objeto", m))
    for c in d.get("coord_events", []):
        if c.get("type") == "trigger" and c.get("script"):
            if str(c.get("var")) in ("0", "TRIGGER_RUN_IMMEDIATELY"):
                walk_immediate(c["script"], "coord var 0")
            else:
                entries.append((c["script"], "coord", m))
    for b in d.get("bg_events", []):
        if b.get("script"):
            entries.append((b["script"], "bg", m))

for lab, why, m in entries:
    walk_lock(lab, f"{why} em {m}")

# ------------------------------------------------ alcancabilidade
# Raizes: tudo que um mapa vivo aponta (tabelas, objetos, placas, gatilhos)
# e toda label citada em src/*.c. A partir dai, qualquer argumento que seja
# label (goto, call, branches, trainerbattle, ponteiros .4byte) e seguido.
csrc = ""
for dp, dn, fn in os.walk("src"):
    for f in fn:
        if f.endswith(".c"):
            csrc += open(os.path.join(dp, f), errors="replace").read()
c_idents = set(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", csrc))
roots = {l for l, _, _ in entries}
for m in play_maps:
    roots.add(f"{m}_MapScripts")
    for n, kind, lab in map_tables(m):
        roots.add(lab)
        if kind in ("MAP_SCRIPT_ON_FRAME_TABLE", "MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE") and lab in labels:
            roots.update(t for _, _, _, t in table_entries(lab)[1])
    for c in mapinfo.get(m, {}).get("coord_events", []):
        if c.get("script"):
            roots.add(c["script"])
roots |= (c_idents & set(labels))
reach = set()          # (arquivo, linha)
todo = [labels[r] for r in roots if r in labels]
seen_pos = set()
while todo:
    path, i = todo.pop()
    code = insts[path]
    while i < len(code) and (path, i) not in seen_pos:
        seen_pos.add((path, i))
        n, cmd, args = code[i]
        reach.add((path, n))
        for a in args:
            for tok in re.findall(r"[A-Za-z_][A-Za-z0-9_]*", a):
                if tok in labels:
                    todo.append(labels[tok])
        if cmd in ("end", "endram", "return", "goto", "releaseend"):
            break
        i += 1

# CALL_END
for path, code in insts.items():
    for n, cmd, args in code:
        if cmd == "call" and args and args[0] in labels:
            if ends_with_end(*labels[args[0]]):
                add("CALL_END", path, n, f"`call {args[0]}` chega num `end`: o resto de quem chamou nao roda")

# FALLTHROUGH (so em mapas vivos; label seguida de outra label sem terminador)
for path, code in insts.items():
    if not path.startswith("data/maps/"):
        continue
    starts = sorted({i for (p, i) in labels.values() if p == path})
    for i in starts:
        if i == 0 or i >= len(code):
            continue
        pn, pcmd, pargs = code[i - 1]
        if pcmd.startswith(".") or pcmd.startswith("step") or pcmd.startswith(("walk", "face", "delay_", "jump", "emote", "lock_facing", "unlock_facing", "set_", "slide", "run", "player_run")):
            continue
        if pcmd in TERM or pcmd in WARPS or pcmd == "map_script" or pcmd == "map_script_2":
            continue
        if pcmd.startswith(("goto_if", "call_if")) or pcmd in ("case", "pokemartlistend", "frontier_set"):
            continue
        name = [k for k, v in labels.items() if v == (path, i)]
        add("FALLTHROUGH", path, pn, f"`{pcmd}` cai direto em {name[0] if name else '?'}")

# ------------------------------------------------ OBJ_ID / REMOVE_FLAG
all_localids = {}
for m, d in mapinfo.items():
    for idx, o in enumerate(d.get("object_events", []), 1):
        if o.get("local_id"):
            all_localids.setdefault(o["local_id"], []).append(m)

HIDE_OK = re.compile(r"^(0|FLAG_HIDE_|FLAG_TEMP_|FLAG_.*HIDE|FLAG_TEMP)")
for path, code in insts.items():
    m = filemap.get(path)
    if not m or m not in mapinfo or m in excluded:
        continue
    objs = mapinfo[m].get("object_events", [])
    names = {o.get("local_id"): k for k, o in enumerate(objs, 1) if o.get("local_id")}
    for k, (n, cmd, args) in enumerate(code):
        if cmd not in OBJCMDS or not args:
            continue
        a = args[0]
        a = sets[path].get(a, a)
        if a in SPECIAL_IDS or a.startswith("VAR_"):
            continue
        idx = None
        if a in names:
            idx = names[a]
        elif re.fullmatch(r"\d+", a):
            idx = int(a)
            if idx < 1 or idx > len(objs):
                add("OBJ_ID", path, n, f"`{cmd} {a}`: {m} so tem {len(objs)} objetos")
                continue
        elif a.startswith("LOCALID_"):
            other = all_localids.get(a)
            add("OBJ_ID", path, n, f"`{cmd} {a}`: id de {other or 'lugar nenhum'}, nao de {m}")
            continue
        else:
            continue
        if cmd == "removeobject" and idx:
            fl = objs[idx - 1].get("flag", "0")
            # setflag explicito da mesma flag na mesma cena = intencional
            recent = code[max(0, k - 80):k + 30]
            if any(c == "setflag" and a[:1] == [fl] for _, c, a in recent):
                continue
            if not HIDE_OK.match(fl):
                sev = "CRITICO: some com centenas de NPCs" if fl == "FLAG_GARBAGEFLAG" else "flag com outro significado"
                add("REMOVE_FLAG", path, n, f"`removeobject {args[0]}` seta {fl} ({sev})")

# ------------------------------------------------ WARP
def check_warp(path, n, dest, rest, src):
    if dest in ("MAP_DYNAMIC", "MAP_NONE", "MAP_UNDEFINED") or not dest.startswith("MAP_"):
        return
    dm = mapid_to_name.get(dest)
    if not dm:
        add("WARP", path, n, f"{src}: destino {dest} nao existe")
        return
    if dm in excluded:
        add("WARP", path, n, f"{src}: destino {dest} esta fora da ROM")
        return
    d = mapinfo[dm]
    rest = [r for r in rest if r]
    if len(rest) == 3:          # warp MAP, warpId, x, y: warpId invalido cai no x,y
        try:
            w = int(rest[0], 0)
        except ValueError:
            return
        rest = rest[:1] if w < len(d.get("warp_events", [])) else rest[1:]
    if len(rest) == 1:
        try:
            w = int(rest[0], 0)
        except ValueError:
            return
        if w not in (0x7F, 0xFF, 127, 255) and w >= len(d.get("warp_events", [])):
            add("WARP", path, n, f"{src}: {dest} warp {w}, mas o mapa tem {len(d.get('warp_events', []))}")
    elif len(rest) >= 2:
        try:
            x, y = int(rest[0], 0), int(rest[1], 0)
        except ValueError:
            return
        lay = layouts.get(d["layout"])
        if lay and not (0 <= x < lay["width"] and 0 <= y < lay["height"]):
            add("WARP", path, n, f"{src}: {dest} ({x},{y}) fora do layout {lay['width']}x{lay['height']}")


for m in live_maps:
    d = mapinfo.get(m)
    if not d:
        continue
    for k, w in enumerate(d.get("warp_events", [])):
        check_warp(f"data/maps/{m}/map.json", k, w["dest_map"], [str(w["dest_warp_id"])], f"warp_event {k}")
for path, code in insts.items():
    m = filemap.get(path)
    if m and m in excluded:
        continue
    for n, cmd, args in code:
        if cmd in WARPS and args:
            check_warp(path, n, args[0], args[1:], cmd)

# ------------------------------------------------ VAR_ESTADO
vars_h = open("include/constants/vars.h").read()
var_names = set(re.findall(r"#define\s+(VAR_[A-Z0-9_]+)\s", vars_h))
written = collections.defaultdict(set)
compared = collections.defaultdict(list)
dyn = set()
CMP = re.compile(r"^(goto_if|call_if)_(eq|ne|lt|ge|le|gt)$")
for path, code in insts.items():
    m = filemap.get(path)
    if m and m in excluded:
        continue
    last_switch = None
    for n, cmd, args in code:
        if not args:
            continue
        if cmd == "setvar" and len(args) > 1:
            written[args[0]].add(args[1])
        elif cmd in ("addvar", "subvar", "copyvar", "specialvar", "setorcopyvar", "random", "buffernumberstring"):
            dyn.add(args[0])
        elif CMP.match(cmd) and len(args) >= 3:
            compared[args[0]].append((path, n, args[1]))
        elif cmd == "compare" and len(args) >= 2:
            compared[args[0]].append((path, n, args[1]))
        elif cmd == "switch":
            last_switch = args[0]
        elif cmd == "case" and last_switch:
            compared[last_switch].append((path, n, args[0]))
        elif cmd == "map_script_2" and len(args) >= 2:
            compared[args[0]].append((path, n, args[1]))
for m in live_maps:
    for c in mapinfo.get(m, {}).get("coord_events", []):
        if c.get("var", "0") not in ("0",) and str(c.get("var", "")).startswith("VAR_"):
            compared[c["var"]].append((f"data/maps/{m}/map.json", 0, str(c.get("var_value"))))
for v, cmps in compared.items():
    # VAR_ITEM_ID = gSpecialVar_ItemId, escrita em C (menu da bolsa) com outro nome
    if not v.startswith("VAR_") or v.startswith(("VAR_TEMP", "VAR_0x", "VAR_RESULT", "VAR_SPECIAL", "VAR_FACING", "VAR_LAST_TALKED", "VAR_ITEM_ID")):
        continue
    if v in dyn or re.search(r"VarSet\s*\(\s*" + v + r"\b", csrc) or re.search(r"\b" + v + r"\b", csrc):
        continue          # escrita dinamica ou em C: nao da para fechar
    w = written.get(v, set())
    for path, n, val in cmps:
        if val in w:
            continue
        if val in ("0", "FALSE") and True:
            continue      # valor inicial do save
        add("VAR_ESTADO", path, n, f"{v} comparada com {val}; valores escritos: {sorted(w) or 'nenhum'}")

# ------------------------------------------------ TRAINER_DUP
tuse = collections.defaultdict(set)
for path, code in insts.items():
    m = filemap.get(path)
    if not m or m in excluded:
        continue
    for n, cmd, args in code:
        if cmd.startswith("trainerbattle") and cmd != "trainerbattle":
            for a in args:
                if a.startswith("TRAINER_") and a != "TRAINER_NONE":
                    tuse[a].add(m)
for t, ms in sorted(tuse.items()):
    if len(ms) > 1:
        add("TRAINER_DUP", "-", 0, f"{t} usado em {sorted(ms)}")

# ------------------------------------------------ TRAVA_LACO
# Laco sem nenhum comando que devolva o controle ao engine (wait*, msgbox,
# delay, lock, fadescreen, menu, batalha, warp) gira dentro de um frame so:
# o jogo congela de verdade. Grafo de posicoes alcancaveis; SCC via Tarjan.
YIELD = {"waitstate", "waitmessage", "waitbuttonpress", "waitmovement", "waitmovementat", "delay",
         "msgbox", "message", "lock", "lockall", "fadescreen", "fadescreenspeed", "fadescreenswapbuffers",
         "multichoice", "multichoicedefault", "multichoicegrid", "dynmultichoice", "yesnobox", "waitfanfare",
         "waitse", "waitmoncry", "dowildbattle", "dotrainerbattle", "giveitem", "finditem", "callstd",
         "waitdooranim", "release", "releaseall", "chooseitem", "pokemart", "pokemartdecoration",
         "setwildbattle", "trainerbattle_single", "trainerbattle_double", "trainerbattle_no_intro",
         "trainerbattle_two_trainers", "trainerbattle_earlyrival", "playfanfare", "fadenewbgm",
         "givemon", "giveegg", "closemessage", "special"} | WARPS
WRITES = ("setvar", "addvar", "subvar", "copyvar", "specialvar", "callnative", "random", "setflag",
          "clearflag", "checkitem", "checkitemspace", "getpartysize", "removeitem", "additem",
          "setorcopyvar", "checkplayergender", "dotimebasedevents", "gettime", "checkpartymove")
succ = collections.defaultdict(list)
nodes = [pos for pos in seen_pos]
nodeset = set(nodes)
for (path, i) in nodes:
    n, cmd, args = insts[path][i]
    if cmd in YIELD or cmd.startswith(("trainerbattle", "wait")):
        continue
    nxt = []
    if cmd not in ("end", "endram", "return", "goto", "releaseend"):
        nxt.append((path, i + 1))
    for l in label_args(cmd, args):
        if l in labels:
            nxt.append(labels[l])
    succ[(path, i)] = [x for x in nxt if x in nodeset and not (
        insts[x[0]][x[1]][1] in YIELD or insts[x[0]][x[1]][1].startswith(("trainerbattle", "wait")))]
sys.setrecursionlimit(100000)
index = {}; low = {}; onst = set(); st = []; sccs = []; cnt = [0]
def strong(v):
    work = [(v, 0)]
    while work:
        v, k = work.pop()
        if k == 0:
            index[v] = low[v] = cnt[0]; cnt[0] += 1; st.append(v); onst.add(v)
        recurse = False
        ws = succ.get(v, [])
        for j in range(k, len(ws)):
            w = ws[j]
            if w not in index:
                work.append((v, j + 1)); work.append((w, 0)); recurse = True; break
            elif w in onst:
                low[v] = min(low[v], index[w])
        if recurse:
            continue
        if low[v] == index[v]:
            comp = []
            while True:
                w = st.pop(); onst.discard(w); comp.append(w)
                if w == v:
                    break
            sccs.append(comp)
        if work:
            u = work[-1][0]
            low[u] = min(low[u], low[v])
for v in list(succ):
    if v not in index:
        strong(v)
for comp in sccs:
    if len(comp) == 1 and comp[0] not in succ.get(comp[0], []):
        continue
    cmds = [insts[p][i] for p, i in comp]
    writes = any(c[1].startswith(WRITES) for c in cmds)
    p0, i0 = min(comp)
    cat = "TRAVA_LACO_POSSIVEL" if writes else "TRAVA_LACO"
    add(cat, p0, insts[p0][i0][0], f"laco de {len(comp)} comandos sem espera"
        + (" (muda estado dentro: pode terminar)" if writes else " e sem mudar estado: se entrar, nunca sai"))

# ------------------------------------------------ TRAVA_WAITSTATE
# waitstate para o script ate alguem chamar ScriptContext_Enable. Sem um
# special/warp/batalha/menu logo antes, ninguem chama: o jogo para de vez
# (era o caso do sandpit, com o warphole comentado).
RESUMERS = ("special", "specialvar", "callnative", "dowildbattle", "dotrainerbattle", "setwildbattle",
            "chooseitem", "fadescreen", "playfanfare", "legendaryencounter", "bosslegendaryencounter",
            "bosslegendaryencounterwithmoves", "checkspecies", "forcesave", "ingame_trade", "dofieldeffect",
            "playmoncry", "startcontest", "warp", "pokemart", "special2", "choosecontestmon",
            "setmonmetlocation", "trainerbattle", "frontier_", "arcade_", "pyramid_", "tower_",
            "dome_", "palace_", "factory_", "pike_", "arena_", "dynmultichoice", "lockall", "lock",
            "dofacilitytrainerbattle", "chooseboxmon", "secretbase", "multichoice", "yesnobox")
for path, code in insts.items():
    for k, (n, cmd, args) in enumerate(code):
        if cmd != "waitstate" or (path, n) not in reach:
            continue
        prev = code[k - 1][1] if k else ""
        back = [c for _, c, _ in code[max(0, k - 4):k]]
        if not any(c.startswith(RESUMERS) or c in WARPS for c in back):
            add("TRAVA_WAITSTATE", path, n, f"`waitstate` logo depois de `{prev}`: nada retoma o script")

# ------------------------------------------------ saida
ap = argparse.ArgumentParser()
ap.add_argument("--so")
a = ap.parse_args()
total = 0
ONLY_LIVE = {"TRAVA_WAITSTATE", "TRAVA_LACO", "TRAVA_LACO_POSSIVEL", "CALL_END", "FALLTHROUGH", "VAR_ESTADO", "OBJ_ID", "REMOVE_FLAG", "WARP", "TRAVA_LOCK", "TRAVA_LOCK_POSSIVEL"}
for cat in sorted(findings):
    if a.so and cat != a.so:
        continue
    uniq = sorted(set(findings[cat]))
    if cat in ONLY_LIVE:
        uniq = [f for f in uniq if not f[0].endswith((".inc", ".s")) or (f[0], f[1]) in reach]
    uniq = [f for f in uniq if not (f[0].startswith("data/maps/") and f[0].split("/")[2] in unreachable)]
    if not uniq:
        continue
    total += len(uniq)
    print(f"\n== {cat} ({len(uniq)})")
    for p, n, msg in uniq:
        print(f"  {p}:{n}  {msg}")
print(f"\ntotal: {total}")
