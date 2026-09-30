#!/usr/bin/env python3
"""Auditoria dos itens de SoulGold.

Roda na raiz do repo:

    python3 dev_scripts/item_audit.py               # resumo no terminal
    python3 dev_scripts/item_audit.py --csv         # regrava docs/SOULGOLD_ITEMS_AUDIT.csv
    python3 dev_scripts/item_audit.py --md          # regrava docs/SOULGOLD_ITEMS_AUDIT.md
    python3 dev_scripts/item_audit.py --dump-status "SEM FONTE"   # debug: lista um status

O que ele faz:
  1. Le TODOS os ITEM_* de include/constants/items.h, na ordem, com a secao
     (comentario) onde cada um vive.
  2. Le descricao e pocket de cada item em src/data/items.h.
  3. Varre data/maps/**/scripts.{inc,pory}, data/scripts/*.inc e
     data/event_scripts.s procurando giveitem/additem/finditem/mart/
     setitemandprice/givemon, alem de:
       - blocos multi-linha `mart NOME { ITEM_X ITEM_Y }` do poryscript;
       - o padrao "var computado" (`setvar VAR_X, ITEM_Y` .. `giveitem VAR_X`),
         que e como o crafting do Kurt entrega bola (ver
         .claude/KURT_BALL_CRAFT_DESIGN.md secao 2.8) sem 27 giveitem literais;
       - o sorteio de berry do Route 30 Berry Master, que sorteia um item
         dentro de uma FAIXA continua do enum (random N + addvar + giveitem
         VAR_RESULT), nao uma tabela;
       - `setitemandprice` (Battle Frontier Exchange Service Corner - troca
         held item por BP, e uma loja de verdade so com comando proprio).
  4. Item ball visivel no mapa: `object_events[].trainer_sight_or_berry_tree_id`
     em data/maps/*/map.json (o engine reaproveita esse campo para guardar o
     ITEM_* da bolinha do overworld - MUITO mais comum que hidden_item).
  5. Held items de especie selvagem (itemCommon/itemRare em
     src/data/pokemon/species_info/*.h) e held items de treinador
     (sintaxe Showdown "@ Item" em src/data/trainers.party) - so contam
     via Roubo/Golpe do Dia, entao ficam numa categoria fraca separada.
  6. Le a tabela de Pickup (sPickupTable em src/battle_script_commands.c),
     Hidden Grotto (.rareItem em src/hidden_grotto.c), Rock Smash e vara de
     pescar (tabelas pequenas de src/wild_encounter.c, conferidas a mao) e o
     premio da Favor Lady de Lilycove (src/data/lilycove_lady.h).
  7. Marca como "fora da campanha" toda fonte que so existe em mapa de
     rom_excluded_groups (data/maps/map_groups.json) que NAO esta na lista
     de excecao rom_shared_script_maps - esses mapas sao o jogo base de Hoenn,
     nao fazem parte da campanha de Johto/Kanto e nao contam como obtivel.

Limitacoes conhecidas (nao tente resolver so com este script):
  - So detecta os comandos literais acima ou o padrao var-computado; um
    giveitem de uma var carregada por caminho que este script nao rastreia
    passa batido e o item aparece como SEM FONTE por engano.
  - Held item de especie selvagem nao confere se a especie aparece em algum
    encontro selvagem alcancavel - so que o campo existe no data table.
  - "Fora da campanha" e so o filtro de grupo de mapa; um mapa de Johto/Kanto
    morto (sem ligacao) NAO e pego aqui - isso e a skill mapa-de-ligacoes.
  - "SO MENCIONADO" e uma zona cinzenta: o item aparece num script (checkitem,
    comparacao, bufferitemname...) mas nenhum comando de entrega reconhecido
    foi achado NUM MAPA DA CAMPANHA - pode ser giveitem real que o regex nao
    pegou, ou pode ser giveitem que so existe num mapa fora da campanha (ver
    ITEM_POWDER_JAR: dado em SlateportCity, fora da campanha, e so
    "mencionado" por um checkitem de cable_club.inc que conta como campanha).

Leia docs/SOULGOLD_ITEMS_AUDIT.csv e docs/SOULGOLD_ITEMS_AUDIT.md para o
resultado interpretado.
"""

import argparse
import collections
import csv
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

STRONG = {
    "Script (dado ao jogador)",
    "Script (dado ao jogador, var computado)",
    "Script (additem)",
    "Script (finditem)",
    "Loja / pokemart",
    "Item escondido (hidden_item)",
    "Item ball no mapa (object_event)",
    "Held item de presente (givemon)",
    "Pickup (habilidade)",
    "Rock Smash",
    "Vara de pescar (item bonus)",
    "Favor Lady (Lilycove)",
    "Hidden Grotto (item raro)",
    "Sorteio de pool (Route30 Berry Master, comum)",
    "Sorteio de pool (Route30 Berry Master, raro pos-Liga)",
}
WEAK = {
    "Held item selvagem (Roubo/Golpe do Dia)",
    "Held item de treinador (so via Roubo)",
}


def parse_item_constants(root):
    items = []
    alias_of = {}
    section = "?"
    name_re = re.compile(r'^\s*(ITEM_[A-Z0-9_]+)\s*=\s*([^,]+),')
    with open(os.path.join(root, "include/constants/items.h")) as f:
        for line in f:
            s = line.strip()
            if s.startswith("//") and not s.startswith("// Pre-Gen"):
                section = s.lstrip("/ ").strip()
                continue
            m = name_re.match(line)
            if not m:
                continue
            nm, val = m.group(1), m.group(2).strip()
            if nm == "ITEMS_COUNT":
                continue
            if val.isdigit():
                items.append([nm, int(val), section])
            else:
                alias_of[nm] = val.split("//")[0].strip()

    # ITEM_CHERI_BERRY = FIRST_BERRY_INDEX (514) is a real item, not an alias
    # of a nonexistent constant - patch it back in.
    if alias_of.get("ITEM_CHERI_BERRY") == "FIRST_BERRY_INDEX":
        del alias_of["ITEM_CHERI_BERRY"]
        items.append(["ITEM_CHERI_BERRY", 514, "Berries"])
        items.sort(key=lambda r: r[1])

    # ITEM_TM01..ITEM_TM100 e ITEM_HM01..ITEM_HM10 sao os slots numericos RUS
    # (ITEM_TM01 = 582); o nome de verdade (ITEM_TM_WORK_UP = ITEM_TM01, o
    # unico que tem bloco de descricao/pocket em src/data/items.h) so existe
    # depois de expandir a macro RECURSIVELY(R_ZIP(...)) em
    # include/constants/items.h, que regex nenhum le sem rodar o
    # preprocessador. Sem este patch, o script trata ITEM_TM01 como um item
    # de verdade (sem pocket, sem descricao - cai em SEM_POCKET) e nunca ve
    # ITEM_TM_WORK_UP. Resolve lendo FOREACH_TM/FOREACH_HM de
    # include/constants/tms_hms.h (a mesma lista que gera a macro) e trocando
    # o nome numerico pelo nome de verdade na lista de items canonicos.
    tmhm_path = os.path.join(root, "include/constants/tms_hms.h")
    if os.path.exists(tmhm_path):
        tmhm_text = open(tmhm_path).read()
        friendly_by_numeric = {}
        tm_block = re.search(r'FOREACH_TM\(F\)\s*\\(.*?)#define\s+FOREACH_HM', tmhm_text, re.S)
        hm_block = re.search(r'FOREACH_HM\(F\)\s*\\(.*?)#define\s+FOREACH_TMHM', tmhm_text, re.S)
        if tm_block:
            for i, name in enumerate(re.findall(r'F\(([A-Z0-9_]+)\)', tm_block.group(1)), start=1):
                friendly_by_numeric[f"ITEM_TM{i:02d}"] = f"ITEM_TM_{name}"
        if hm_block:
            for i, name in enumerate(re.findall(r'F\(([A-Z0-9_]+)\)', hm_block.group(1)), start=1):
                friendly_by_numeric[f"ITEM_HM{i:02d}"] = f"ITEM_HM_{name}"

        by_name = {row[0]: row for row in items}
        for numeric_name, friendly_name in friendly_by_numeric.items():
            row = by_name.get(numeric_name)
            if row is None:
                continue
            row[0] = friendly_name
            alias_of[numeric_name] = friendly_name
        items.sort(key=lambda r: r[1])

    return items, alias_of


def parse_item_data(root):
    desc, pocket, dispname = {}, {}, {}
    with open(os.path.join(root, "src/data/items.h")) as f:
        text = f.read()

    # A lot of common items (Full Heal, Max Revive, ...) share one description
    # string declared once near the top (`static const u8 sFullHealDesc[] =
    # _("...")`) and referenced by name instead of inlining the literal again.
    shared_desc = {}
    for m in re.finditer(
            r'static\s+const\s+u8\s+(s\w+)\s*\[\]\s*=(.*?);', text, re.S):
        parts = re.findall(r'"([^"]*)"', m.group(2))
        if parts:
            d = " ".join(p.replace("\\n", " ") for p in parts)
            shared_desc[m.group(1)] = re.sub(r"\s+", " ", d).strip()

    for block in re.split(r'\n(?=\s*\[ITEM_)', text):
        m = re.match(r'\s*\[(ITEM_[A-Z0-9_]+)\]', block)
        if not m:
            continue
        nm = m.group(1)
        # .description = COMPOUND_STRING("a\n" "b\n" "c."), -- capture everything
        # up to the next `.field =` (whatever macro wraps the string literals),
        # OR .description = sSomeSharedDesc, a reference resolved above.
        dm = re.search(r'\.description\s*=(.*?)(?:\n\s*\.\w+\s*=|\n\s*\},)', block, re.S)
        if dm:
            raw = dm.group(1)
            parts = re.findall(r'"([^"]*)"', raw)
            if parts:
                d = " ".join(p.replace("\\n", " ") for p in parts)
                desc[nm] = re.sub(r"\s+", " ", d).strip()
            else:
                rm = re.search(r'(s\w+)', raw)
                if rm and rm.group(1) in shared_desc:
                    desc[nm] = shared_desc[rm.group(1)]
        pm = re.search(r'\.pocket\s*=\s*(POCKET_[A-Z_]+)', block)
        if pm:
            pocket[nm] = pm.group(1)
        nmm = re.search(r'\.name\s*=\s*ITEM_NAME\(\s*"([^"]+)"', block)
        if nmm:
            dispname[nm] = nmm.group(1)

    # Os 18 "type-tite" (ITEM_NORMALITE..ITEM_FAIRYTITE) nao tem bloco
    # [ITEM_X]={...} literal - sao geradas pela macro TYPE_MEGA_STONE(itemId,
    # itemName, typeName, iconName) definida no proprio items.h. Sem isso
    # eles caem em SEM_POCKET e sem descricao.
    for m in re.finditer(
        r'TYPE_MEGA_STONE\(\s*(ITEM_[A-Z0-9_]+)\s*,\s*"([^"]+)"\s*,\s*"([^"]+)"',
        text,
    ):
        item_name, display_name, type_name = m.groups()
        pocket[item_name] = "POCKET_MEGASTONES"
        desc[item_name] = f"Allows certain Pokemon to Mega Evolve into {type_name}-type form."
        dispname[item_name] = display_name

    return desc, pocket, dispname


def load_campaign_filter(root):
    mg = json.load(open(os.path.join(root, "data/maps/map_groups.json")))
    excluded_groups = set(mg["rom_excluded_groups"])
    shared_ok = set(mg["rom_shared_script_maps"])
    excluded_maps = set()
    for g in excluded_groups:
        for m in mg.get(g, []):
            if m not in shared_ok:
                excluded_maps.add(m)
    return excluded_maps


def build_rows():
    """Monta a lista de dicts (um por item canonico) com status/fontes.
    Separado do main() para poder ser reusado por --dump e por testes."""
    os.chdir(ROOT)
    excluded_maps = load_campaign_filter(ROOT)

    def in_campaign(mapname):
        return mapname not in excluded_maps

    items, alias_of = parse_item_constants(ROOT)
    desc, pocket, dispname = parse_item_data(ROOT)
    id_by_name = {nm: i for nm, i, _ in items}
    name_by_id = {i: nm for nm, i, _ in items}

    acq = collections.defaultdict(list)  # name -> [(category, detail, in_campaign)]

    def add(nm, cat, detail, campaign=True):
        acq[nm].append((cat, detail, campaign))

    script_files = (glob.glob("data/maps/**/scripts.inc", recursive=True)
                    + glob.glob("data/maps/**/scripts.pory", recursive=True)
                    + glob.glob("data/scripts/*.inc")
                    + ["data/event_scripts.s"])

    item_tok_re = re.compile(r'\bITEM_[A-Z0-9_]+\b')
    giveitem_var_re = re.compile(r'^\s*giveitem\s+(VAR_[A-Za-z0-9_]+)\b', re.I)
    setvar_item_re = re.compile(r'^\s*setvar\s+(VAR_[A-Za-z0-9_]+)\s*,\s*(ITEM_[A-Z0-9_]+)\b')

    for path in script_files:
        if not os.path.isfile(path):
            continue
        mapname = path.split("/")[2] if path.startswith("data/maps/") else os.path.basename(path)
        camp = in_campaign(mapname) if path.startswith("data/maps/") else True

        with open(path, errors="ignore") as f:
            lines = f.readlines()

        # pass 1: literal giveitem/additem/mart lines, incl. multi-line pory mart blocks
        in_mart_block = False
        for lineno, line in enumerate(lines, 1):
            s = line.strip()
            if s.startswith("//") or s.startswith("@") or s.startswith("#"):
                continue
            if re.match(r'^\s*mart\s+\S+\s*\{', s):
                in_mart_block = True
                continue
            if in_mart_block:
                if "}" in s:
                    in_mart_block = False
                    continue
                for t in item_tok_re.findall(s):
                    add(t, "Loja / pokemart", f"{path} ({mapname})", camp)
                continue

            toks = item_tok_re.findall(s)
            if not toks:
                continue
            if re.match(r'^\s*(giveitem|giveitemtoclerk)\b', s, re.I):
                for t in toks:
                    add(t, "Script (dado ao jogador)", f"{path}:{lineno}", camp)
            elif re.match(r'^\s*additem\b', s, re.I):
                for t in toks:
                    add(t, "Script (additem)", f"{path}:{lineno}", camp)
            elif re.match(r'^\s*finditem\b', s, re.I):
                for t in toks:
                    add(t, "Script (finditem)", f"{path}:{lineno}", camp)
            elif re.match(r'^\s*(\.2byte|mart)\b', s, re.I):
                for t in toks:
                    add(t, "Loja / pokemart", f"{path} ({mapname})", camp)
            elif re.match(r'^\s*setitemandprice\b', s, re.I):
                # Battle Frontier Exchange Service Corner: troca held item por
                # BP a um preco fixo - e uma loja de verdade, so com comando
                # proprio em vez de mart/.2byte.
                for t in toks:
                    add(t, "Loja / pokemart", f"{path} ({mapname})", camp)
            elif re.match(r'^\s*givemon\b', s, re.I):
                # givemon SPECIES, level, HELD_ITEM[, ...] - o item aqui e o
                # held item do presente, nao um giveitem, mas ainda e uma
                # forma real de o jogador obter aquele item (fica no bag do
                # Pokemon recebido).
                for t in toks:
                    add(t, "Held item de presente (givemon)", f"{path}:{lineno}", camp)
            elif re.match(r'^\s*removeitem\b', s, re.I):
                pass
            else:
                for t in toks:
                    add(t, "Mencionado em script (verificar)", f"{path}:{lineno}: {s[:80]}", camp)

        # pass 2: computed giveitem (Kurt-style generic subroutine)
        given_vars = {m.group(1).upper() for line in lines
                      if (m := giveitem_var_re.match(line.strip()))}
        if given_vars:
            for lineno, line in enumerate(lines, 1):
                m = setvar_item_re.match(line.strip())
                if m and m.group(1).upper() in given_vars:
                    add(m.group(2), "Script (dado ao jogador, var computado)", f"{path}:{lineno}", camp)

    # Route 30 Berry Master: dynamic range draw (section 5.2 of the Kurt doc)
    for lo_nm, hi_nm, label in [
        ("ITEM_CHERI_BERRY", "ITEM_ROSELI_BERRY", "Sorteio de pool (Route30 Berry Master, comum)"),
        ("ITEM_LIECHI_BERRY", "ITEM_MARANGA_BERRY", "Sorteio de pool (Route30 Berry Master, raro pos-Liga)"),
    ]:
        lo, hi = id_by_name[lo_nm], id_by_name[hi_nm]
        for i in range(lo, hi + 1):
            if i in name_by_id:
                add(name_by_id[i], label, "data/maps/Route30_House/scripts.inc (Route30_House)", True)

    for mp in glob.glob("data/maps/**/map.json", recursive=True):
        d = json.load(open(mp))
        mapname = mp.split("/")[2]
        camp = in_campaign(mapname)
        for be in d.get("bg_events", []):
            if be.get("type") == "hidden_item":
                add(be["item"], "Item escondido (hidden_item)", mapname, camp)
        # Item ball visivel no mapa (o boneco/objeto de poke ball parado):
        # o item de fato aparece no campo trainer_sight_or_berry_tree_id do
        # object_event (reaproveitado pelo engine para guardar o ITEM_* da
        # bolinha), nao em bg_events. Isso e MUITO mais comum que
        # hidden_item para TM/HM e mega stone.
        for oe in d.get("object_events", []):
            val = oe.get("trainer_sight_or_berry_tree_id", "")
            if isinstance(val, str) and val.startswith("ITEM_"):
                add(val, "Item ball no mapa (object_event)", mapname, camp)

    # Hidden Grotto: item raro sorteado quando a Pokemon da toca e capturada
    # (src/hidden_grotto.c). Mecanica propria (BW2-like), nao existe no
    # pokeemerald-expansion vanilla.
    grotto_text = None
    try:
        grotto_text = open("src/hidden_grotto.c", errors="ignore").read()
    except FileNotFoundError:
        pass
    if grotto_text:
        for t in re.findall(r'\.rareItem\s*=\s*(ITEM_[A-Z0-9_]+)', grotto_text):
            add(t, "Hidden Grotto (item raro)", "src/hidden_grotto.c", True)

    # Rock Smash e vara de pescar: tabelas pequenas e fixas do proprio engine
    # (src/wild_encounter.c), conferidas manualmente nesta auditoria - nao
    # vale a pena reparsear a struct com regex fragil.
    misc_hardcoded = {
        "Rock Smash": [
            "ITEM_RED_SHARD", "ITEM_BLUE_SHARD", "ITEM_YELLOW_SHARD", "ITEM_GREEN_SHARD",
            "ITEM_DOME_FOSSIL", "ITEM_ROOT_FOSSIL", "ITEM_PLUME_FOSSIL", "ITEM_JAW_FOSSIL",
            "ITEM_SAIL_FOSSIL", "ITEM_OLD_AMBER", "ITEM_COVER_FOSSIL",
        ],
        "Vara de pescar (item bonus)": [
            "ITEM_HEALTH_FEATHER", "ITEM_MUSCLE_FEATHER", "ITEM_RESIST_FEATHER",
            "ITEM_GENIUS_FEATHER", "ITEM_CLEVER_FEATHER", "ITEM_SWIFT_FEATHER",
            "ITEM_BOTTLE_CAP", "ITEM_GOLD_BOTTLE_CAP",
        ],
        "Favor Lady (Lilycove)": [
            "ITEM_LUXURY_BALL", "ITEM_NUGGET", "ITEM_PROTEIN", "ITEM_HEART_SCALE",
            "ITEM_RARE_CANDY", "ITEM_PP_MAX",
        ],
    }
    for label, item_list in misc_hardcoded.items():
        for t in item_list:
            add(t, label, "src/wild_encounter.c ou src/data/lilycove_lady.h (tabela conferida a mao)", True)

    species_files = (glob.glob("src/data/pokemon/species_info/*.h")
                      + glob.glob("src/data/pokemon/species_info/**/*.h", recursive=True))
    for path in species_files:
        text = open(path, errors="ignore").read()
        for m in re.finditer(r'\.item(?:Common|Rare)\s*=\s*(ITEM_[A-Z0-9_]+)', text):
            add(m.group(1), "Held item selvagem (Roubo/Golpe do Dia)", os.path.basename(path), True)

    name_to_item = {nm[len("ITEM_"):].replace("_", " ").title(): nm for nm in id_by_name}
    for lineno, line in enumerate(open("src/data/trainers.party", errors="ignore"), 1):
        m = re.search(r'@\s*(.+)$', line.strip())
        if not m:
            continue
        raw = m.group(1).strip()
        if raw.upper().startswith("ITEM_"):
            add(raw.upper(), "Held item de treinador (so via Roubo)", f"trainers.party:{lineno}")
        elif raw.title() in name_to_item:
            add(name_to_item[raw.title()], "Held item de treinador (so via Roubo)", f"trainers.party:{lineno}")

    text = open("src/battle_script_commands.c", errors="ignore").read()
    pm = re.search(r'sPickupTable\[\]\s*=\s*\{(.*?)\n\};', text, re.S)
    if pm:
        for t in item_tok_re.findall(pm.group(1)):
            add(t, "Pickup (habilidade)", "battle_script_commands.c sPickupTable")

    for alias, canon in alias_of.items():
        if canon in acq and alias not in acq:
            acq[alias] = acq[canon]
        if alias in acq and canon not in acq:
            acq[canon] = acq[alias]

    rows = []
    for nm, iid, sect in items:
        sources = acq.get(nm, [])
        in_camp = [s for s in sources if s[2]]
        out_camp = [s for s in sources if not s[2]]
        strong = [s for s in in_camp if s[0] in STRONG]
        weak = [s for s in in_camp if s[0] in WEAK]
        mention = [s for s in in_camp if s[0] not in STRONG and s[0] not in WEAK]
        if strong:
            status, how = "OBTIVEL", sorted({c for c, d, _ in strong})
        elif weak:
            status, how = "SO VIA ROUBO/GOLPE", sorted({c for c, d, _ in weak})
        elif mention:
            status, how = "SO MENCIONADO", ["ver script"]
        elif out_camp:
            status, how = "SO EM MAPA FORA DA CAMPANHA", sorted({c for c, d, _ in out_camp})
        else:
            status, how = "SEM FONTE", []
        examples = (strong or weak or mention or out_camp)[:3]
        rows.append({
            "id": iid, "name": nm, "section": sect, "pocket": pocket.get(nm, ""),
            "display_name": dispname.get(nm, ""),
            "status": status, "how": "; ".join(how),
            "description": desc.get(nm, ""),
            "example_source": examples[0][1] if examples else "",
            "sources_detail": strong + weak + mention,
            "out_camp_detail": out_camp,
            "trainer_held_only": any(c == "Held item de treinador (so via Roubo)" for c, d, cc in weak),
        })

    return rows


POCKET_ORDER = [
    "POCKET_POKE_BALLS",
    "POCKET_ITEMS",
    "POCKET_MEDICINE",
    "POCKET_BATTLE_ITEMS",
    "POCKET_BERRIES",
    "POCKET_TM_HM",
    "POCKET_MEGASTONES",
    "POCKET_KEY_ITEMS",
]
POCKET_LABEL = {
    "POCKET_POKE_BALLS": "Poké Balls",
    "POCKET_ITEMS": "Itens",
    "POCKET_MEDICINE": "Remédios (Medicine)",
    "POCKET_BATTLE_ITEMS": "Itens de batalha / held items",
    "POCKET_BERRIES": "Berries",
    "POCKET_TM_HM": "TMs & HMs",
    "POCKET_MEGASTONES": "Mega Stones",
    "POCKET_KEY_ITEMS": "Key Items",
}
# Notas de contexto para o leitor humano nao estranhar buckets grandes e
# repetitivos - escritas a mao apos amostragem manual desta auditoria
# (27/09/2026), nao geradas automaticamente.
POCKET_ORPHAN_NOTE = {
    "POCKET_MEGASTONES": (
        "A maioria destas são as mega stones oficiais (uma por espécie, "
        "`gGengarite` etc.) da base pokeemerald-expansion. O SoulGold parece "
        "ter optado por um sistema próprio de mega evolução por TIPO (os 18 "
        "itens `ITEM_*TITE` genéricos em Poké Balls/Itens, tipo "
        "`ITEM_NORMALITE`/`ITEM_FIRETITE`, gerados pela macro "
        "`TYPE_MEGA_STONE` — esses SÃO vendidos em `AzaleaTown_Mart`). As "
        "mega stones de espécie individual abaixo não têm nenhum giveitem, "
        "loja ou item ball — parecem sobra da tabela vanilla, não conteúdo "
        "cortado por engano."
    ),
    "POCKET_BATTLE_ITEMS": (
        "Boa parte é Plate (Arceus), Drive (Genesect), Memory (Silvally) e "
        "Z-Crystal (golpes Z de Alola) — mecânicas de gerações/jogos "
        "específicos que este romhack de Johto/Kanto provavelmente nunca "
        "pretendeu ativar. Vale conferir se alguma delas é usada por algum "
        "Pokémon relevante da campanha antes de descartar a lista inteira."
    ),
    "POCKET_ITEMS": (
        "Inclui os 13 `ITEM_*_APRICORN` coloridos — CONFIRMADO em "
        "`.claude/KURT_BALL_CRAFT_DESIGN.md` seção 1.5 que são um corte "
        "conhecido (\"apricorn não é obtenível no jogo\", `APRICORN_TREE_COUNT` "
        "é 0): não é achado do script, é órfão documentado à espera da Fase "
        "2. O resto é majoritariamente Sweet (Milcery), fóssil/Relic Gen4-9, "
        "Mulch Gen4 (diferente do Mulch Gen8 que a Flower Shop já vende) e "
        "Tera Shard (mecânica de Terastallize) — prováveis mecânicas Gen6-9 "
        "não ativadas nesta campanha."
    ),
    "POCKET_KEY_ITEMS": (
        "Muitos são key items de Kanto (`ITEM_SILPH_SCOPE`, `ITEM_LIFT_KEY`, "
        "`ITEM_SECRET_KEY`, `ITEM_GOLD_TEETH`) — o mapa correspondente já se "
        "chama `AbandonedRocketHideout`, sugerindo que essa sub-questline foi "
        "conscientemente esvaziada nesta campanha, não esquecida. Vale "
        "conferir os key items de Sevii Islands/Orange Islands "
        "(`ITEM_TRI_PASS`, `ITEM_RAINBOW_PASS`, `ITEM_TEA`) e os de "
        "gimmick tardio (Z-Power Ring, Dynamax Band, Tera Orb) com mais "
        "atenção, pois indicam mecânica de geração later nunca ligada."
    ),
}

STATUS_LABEL = {
    "OBTIVEL": "Sim",
    "SO VIA ROUBO/GOLPE": "Só held item (Roubo/Golpe do Dia)",
    "SO MENCIONADO": "Verificar (só mencionado em script)",
    "SO EM MAPA FORA DA CAMPANHA": "Não (só em mapa fora da campanha)",
    "SEM FONTE": "Não",
}
# Itens especificos do SoulGold (Rift Missions / Nexus / mecanicas proprias)
# que nao existem no pokeemerald-expansion vanilla.
SOULGOLD_EXCLUSIVE = {
    "ITEM_BONDSTONE", "ITEM_SHIN_GENOME", "ITEM_BLACK_MIRROR", "ITEM_GS_BALL",
    "ITEM_DARK_CRYSTAL", "ITEM_REVERSE_CANDY", "ITEM_ZEROMIN",
    "ITEM_WITHERED_HERB", "ITEM_BRITTLE_HERB", "ITEM_DULL_HERB",
    "ITEM_SOGGY_HERB", "ITEM_GROOMING_KIT", "ITEM_SEASONAL_PERFUME",
    "ITEM_GIGANTATITE", "ITEM_SUN_MOON_TICKET",
}


def _short_detail(det, maxlen=48):
    # "Mencionado em script (verificar)" guarda o trecho de codigo junto do
    # path:lineno (util pro --dump-status), mas isso lota a tabela do doc -
    # corta no primeiro path:lineno e descarta o resto.
    m = re.match(r'^([^:]+:\d+):', det)
    short = m.group(1) if m else det
    if len(short) > maxlen:
        short = "…" + short[-(maxlen - 1):]
    return short


def _format_detail_list(detail_tuples, limit=3):
    by_cat = collections.defaultdict(list)
    for cat, det, _camp in detail_tuples:
        by_cat[cat].append(_short_detail(det))
    parts = []
    for cat in sorted(by_cat):
        uniq = sorted(set(by_cat[cat]))
        shown = uniq[:limit]
        more = f" (+{len(uniq) - limit})" if len(uniq) > limit else ""
        parts.append(f"{cat}: {', '.join(shown)}{more}")
    return " | ".join(parts)


def write_markdown(rows):
    by_pocket = collections.defaultdict(list)
    for r in rows:
        by_pocket[r["pocket"] or "SEM_POCKET"].append(r)

    lines = []
    lines.append("# Auditoria de itens do SoulGold")
    lines.append("")
    lines.append(
        "Catálogo de todos os `ITEM_*` de `include/constants/items.h` cruzados "
        "com `gItemsInfo` (`src/data/items.h`) e com toda fonte de obtenção "
        "que este levantamento conseguiu achar no repo, para localizar "
        "**itens órfãos**: itens que existem na tabela mas que nenhum "
        "script/mapa/loja/mecânica do jogo entrega ao jogador."
    )
    lines.append("")
    lines.append(
        "Gerado por `dev_scripts/item_audit.py` "
        "(`python3 dev_scripts/item_audit.py --md`). É levantamento estático "
        "(grep + parse de `.h`/`.inc`/`.pory`/`.json`), não substitui testar "
        "no jogo — leia o cabeçalho do script para a lista completa de fontes "
        "reconhecidas e as limitações conhecidas."
    )
    lines.append("")
    lines.append("Colunas da tabela:")
    lines.append("")
    lines.append("- **Item** — constante `ITEM_*` e nome em inglês (como aparece no jogo).")
    lines.append("- **O que faz** — resumo da `.description` da tabela (texto do jogo, em inglês).")
    lines.append(
        "- **Obtível in-game?** — Sim / Não / Verificar (mencionado em script "
        "mas sem comando de entrega reconhecido) / Só held item (via Roubo ou "
        "Golpe do Dia) / Não (só em mapa fora da campanha, isto é, conteúdo "
        "de Hoenn/Emerald que sobrou no repo mas não faz parte da campanha "
        "Johto/Kanto do SoulGold)."
    )
    lines.append("- **Como se obtém** — toda fonte encontrada, truncada quando há muitos locais.")
    lines.append("")
    lines.append(
        "Itens marcados **★ exclusivo SoulGold** são específicos do romhack "
        "(Rift Missions / Nexus / mecânicas próprias) e não existem no "
        "pokeemerald-expansion vanilla — são os mais prováveis de estarem "
        "esquecidos num evento incompleto."
    )
    lines.append("")

    counts = collections.Counter(r["status"] for r in rows)
    total = len(rows)
    lines.append(
        f"**Resumo**: {total} itens catalogados — "
        f"{counts.get('OBTIVEL', 0)} obtíveis, "
        f"{counts.get('SO VIA ROUBO/GOLPE', 0)} só held item (Roubo/Golpe do Dia), "
        f"{counts.get('SO MENCIONADO', 0)} para verificar manualmente, "
        f"{counts.get('SO EM MAPA FORA DA CAMPANHA', 0)} só em mapa fora da "
        f"campanha, e **{counts.get('SEM FONTE', 0)} sem nenhuma fonte "
        "encontrada** (candidatos a órfão — ver seção final)."
    )
    lines.append("")

    for pocket in POCKET_ORDER + (["SEM_POCKET"] if "SEM_POCKET" in by_pocket else []):
        prows = by_pocket.get(pocket)
        if not prows:
            continue
        label = POCKET_LABEL.get(pocket, pocket)
        lines.append(f"## {label} ({len(prows)})")
        lines.append("")
        lines.append("| Item | O que faz | Obtível in-game? | Como se obtém |")
        lines.append("|---|---|---|---|")
        for r in sorted(prows, key=lambda x: x["name"]):
            star = "★ " if r["name"] in SOULGOLD_EXCLUSIVE else ""
            desc = (r["description"] or "-").replace("|", "\\|")
            status = STATUS_LABEL.get(r["status"], r["status"])
            # So mostra a fonte relevante pro status: pra "Sim" so a fonte
            # forte (esconder o "mencionado em script" que so e ruido quando
            # ja tem uma fonte real); pra "so held item" so a fonte fraca;
            # pra "verificar"/"fora da campanha" mostra o que tiver.
            if r["status"] == "OBTIVEL":
                show = [s for s in r["sources_detail"] if s[0] in STRONG]
            elif r["status"] == "SO VIA ROUBO/GOLPE":
                show = [s for s in r["sources_detail"] if s[0] in WEAK]
            elif r["status"] == "SO EM MAPA FORA DA CAMPANHA":
                show = r["out_camp_detail"]
            else:
                show = r["sources_detail"]
            src = _format_detail_list(show).replace("|", "\\|") or "-"
            disp = r["display_name"] or r["name"][5:].replace("_", " ").title()
            lines.append(f"| {star}`{r['name']}` — {disp} | {desc} | {status} | {src} |")
        lines.append("")

    # Órfãos: SEM FONTE e (a titulo informativo) SO MENCIONADO / FORA DA CAMPANHA,
    # porque na pratica nenhum dos tres entrega o item ao jogador na campanha.
    lines.append("## Itens órfãos (candidatos)")
    lines.append("")
    lines.append(
        "Agrupados por pocket. **Sem fonte** = nenhuma fonte reconhecida foi "
        "achada em lugar nenhum. **Só mencionado** = o item aparece num "
        "script (`checkitem`, comparação, `bufferitemname`...) mas nenhum "
        "comando de entrega foi achado numa fonte de campanha — pode ser um "
        "giveitem que o regex não reconheceu, ou pode ser dado só num mapa "
        "fora da campanha (ver limitações no cabeçalho do script). **Fora da "
        "campanha** = só existe um giveitem/loja num mapa de Hoenn/Emerald "
        "que não faz parte da campanha Johto/Kanto. Isto é uma lista para o "
        "autor decidir o que fazer com cada um — nada foi alterado."
    )
    lines.append("")

    orphan_statuses = ["SEM FONTE", "SO MENCIONADO", "SO EM MAPA FORA DA CAMPANHA"]
    orphan_sub_label = {
        "SEM FONTE": "sem fonte",
        "SO MENCIONADO": "só mencionado",
        "SO EM MAPA FORA DA CAMPANHA": "fora da campanha",
    }
    orphan_by_pocket = collections.defaultdict(list)
    for r in rows:
        if r["status"] in orphan_statuses:
            orphan_by_pocket[r["pocket"] or "SEM_POCKET"].append(r)

    for pocket in POCKET_ORDER + (["SEM_POCKET"] if "SEM_POCKET" in orphan_by_pocket else []):
        prows = orphan_by_pocket.get(pocket)
        if not prows:
            continue
        label = POCKET_LABEL.get(pocket, pocket)
        lines.append(f"### {label} ({len(prows)})")
        lines.append("")
        note = POCKET_ORPHAN_NOTE.get(pocket)
        if note:
            lines.append(f"> {note}")
            lines.append("")
        for r in sorted(prows, key=lambda x: (orphan_statuses.index(x["status"]), x["name"])):
            star = "★ " if r["name"] in SOULGOLD_EXCLUSIVE else ""
            sub = orphan_sub_label[r["status"]]
            desc = r["description"] or "(sem descrição)"
            lines.append(f"- {star}`{r['name']}` [{sub}] — {desc}")
        lines.append("")

    out_path = os.path.join(ROOT, "docs/SOULGOLD_ITEMS_AUDIT.md")
    with open(out_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines) + "\n")
    return out_path


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--csv", action="store_true", help="regrava docs/SOULGOLD_ITEMS_AUDIT.csv")
    ap.add_argument("--md", action="store_true", help="regrava docs/SOULGOLD_ITEMS_AUDIT.md")
    ap.add_argument("--dump-status", help="debug: lista os itens com este status")
    args = ap.parse_args()

    rows = build_rows()

    print("total de itens:", len(rows))
    print(collections.Counter(r["status"] for r in rows).most_common())

    if args.dump_status:
        for r in rows:
            if r["status"] == args.dump_status:
                print(r["name"], "|", r["pocket"], "|", r["description"][:60])

    if args.csv:
        out = os.path.join(ROOT, "docs/SOULGOLD_ITEMS_AUDIT.csv")
        with open(out, "w", newline="", encoding="utf-8") as fh:
            fieldnames = [k for k in rows[0].keys() if k not in ("sources_detail",)]
            w = csv.DictWriter(fh, fieldnames=fieldnames, extrasaction="ignore")
            w.writeheader()
            w.writerows(rows)
        print("escrito:", out)

    if args.md:
        out = write_markdown(rows)
        print("escrito:", out)


if __name__ == "__main__":
    main()
