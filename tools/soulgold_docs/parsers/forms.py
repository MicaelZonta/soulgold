"""Parse special overworld sources for obtainable Pokemon forms."""

from __future__ import annotations

import json
import re

from ..c_parser import read, strip_c_comments
from ..models import SpeciesLocation, SpeciesRow
from ..map_names import is_docs_excluded_map, map_display_name
from ..paths import FORM_CHANGE_TABLES_H, MAP_GROUPS_JSON, REPO_ROOT
from .gifts import reachable_script_labels, script_blocks


ROTOM_FORM_TABLE_RE = re.compile(
    r"sRotomFormChangeTable\[\]\s*=\s*\{(.*?)\};",
    re.DOTALL,
)
ROTOM_FORM_RE = re.compile(
    r"\{\s*FORM_CHANGE_MOVE\s*,\s*(SPECIES_ROTOM_[A-Z0-9_]+)\s*,",
)
ROTOM_APARTMENT_MAP = "GoldenrodApartmentBasement"


def _rotom_forms() -> list[str]:
    try:
        text = strip_c_comments(read(FORM_CHANGE_TABLES_H))
    except FileNotFoundError:
        return []
    table = ROTOM_FORM_TABLE_RE.search(text)
    return ROTOM_FORM_RE.findall(table.group(1)) if table else []


def add_rotom_form_change_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    """Point alternate Rotom forms to their Goldenrod appliance location."""
    map_dir = REPO_ROOT / "data" / "maps" / ROTOM_APARTMENT_MAP
    try:
        map_data = json.loads(read(map_dir / "map.json"))
        blocks = script_blocks(read(map_dir / "scripts.inc"))
    except (FileNotFoundError, json.JSONDecodeError):
        return

    reachable = reachable_script_labels(map_data, blocks)
    if not any("ChangeRotomForm" in blocks[label] for label in reachable):
        return

    for species in _rotom_forms():
        if species not in by_species:
            continue
        location: SpeciesLocation = {
            "map": str(map_data.get("id") or ""),
            "name": "Goldenrod Apartment Basement",
            "time": "",
            "method": "Bring Rotom here to change form",
            "minLevel": None,
            "maxLevel": None,
            "rate": None,
        }
        locations.setdefault(species, [])
        if location not in locations[species]:
            locations[species].append(location)


WILD_FORM_ARRAY_RE = re.compile(
    r"static\s+const\s+u16\s+(sWild\w+)\[\]\s*=\s*\{(.*?)\};",
    re.DOTALL,
)
WILD_FORM_RULE_RE = re.compile(
    r"if\s*\(\s*species\s*==\s*(SPECIES_[A-Z0-9_]+)\s*\)\s*return\s+(sWild\w+)\["
)
MOM_HOUSE_MAP = "NewBarkTown_PlayersHouse_1F"
MOM_GROOMING_ARRAY_RE = re.compile(
    r"static\s+const\s+u16\s+(sMomFurfrouTrimOrder|sMomDeerlingSeasonalForms)\b[^=]*=\s*\{(.*?)\n\};",
    re.DOTALL,
)
MOM_GROOMING_SPECIALS = {
    "sMomFurfrouTrimOrder": ("ApplyFurfrouTrim", "Mom's grooming (Furfrou trim)"),
    "sMomDeerlingSeasonalForms": ("ApplySeasonalForm", "Mom's grooming (Seasonal Perfume)"),
}


def _add_location(
    locations: dict[str, list[SpeciesLocation]],
    species: str,
    location: SpeciesLocation,
) -> None:
    locations.setdefault(species, [])
    if location not in locations[species]:
        locations[species].append(location)


def add_wild_random_form_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    """A wild slot of Minior, Pumpkaboo, Scatterbug... rolls one of the cosmetic
    forms at encounter time (GetWildFormVariantSpecies, src/wild_encounter.c):
    every form in the pool gets the wild locations of the slot's species."""
    try:
        text = strip_c_comments(read(REPO_ROOT / "src/wild_encounter.c"))
    except FileNotFoundError:
        return

    pools = {
        name: re.findall(r"\bSPECIES_[A-Z0-9_]+\b", body)
        for name, body in WILD_FORM_ARRAY_RE.findall(text)
    }
    for slot_species, pool_name in WILD_FORM_RULE_RE.findall(text):
        wild = [
            location for location in locations.get(slot_species, [])
            if str(location.get("method", "")).endswith(" Mons")
        ]
        for species in pools.get(pool_name, []):
            if species == slot_species or species not in by_species:
                continue
            for location in wild:
                _add_location(locations, species, {
                    **location,
                    "method": f"{location['method']} (random form)",
                })


def add_mom_grooming_form_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    """Mom (New Bark Town) re-trims Furfrou and changes Deerling/Sawsbuck season."""
    map_dir = REPO_ROOT / "data" / "maps" / MOM_HOUSE_MAP
    try:
        map_data = json.loads(read(map_dir / "map.json"))
        blocks = script_blocks(read(map_dir / "scripts.inc"))
        text = strip_c_comments(read(REPO_ROOT / "src/field_specials.c"))
    except (FileNotFoundError, json.JSONDecodeError):
        return

    reachable_text = "\n".join(blocks[label] for label in reachable_script_labels(map_data, blocks))
    for array_name, body in MOM_GROOMING_ARRAY_RE.findall(text):
        special, method = MOM_GROOMING_SPECIALS[array_name]
        if not re.search(rf"\bspecial\s+{special}\b", reachable_text):
            continue
        for species in re.findall(r"\bSPECIES_[A-Z0-9_]+\b", body):
            if species not in by_species:
                continue
            _add_location(locations, species, {
                "map": str(map_data.get("id") or ""),
                "name": "New Bark Town (Mom)",
                "time": "",
                "method": method,
                "minLevel": None,
                "maxLevel": None,
                "rate": None,
            })


# ---------------------------------------------------------------------------
# Forms reached with an item (Hold / Use / Zygarde Cube / fusion), shown where
# the item can actually be obtained. An item "can be obtained" when a script
# the player can reach names it - a Mart list, a giveitem, or a run of
# consecutive items drawn by GetRandomMissingItemInRange (Memories, Drives).
# ---------------------------------------------------------------------------
ITEM_FORM_CHANGE_RE = re.compile(
    r"\{FORM_CHANGE_(ITEM_HOLD|ITEM_USE|ITEM_USE_MULTICHOICE)\s*,\s*(SPECIES_[A-Z0-9_]+)\s*,\s*(ITEM_[A-Z0-9_]+)"
)
FUSION_RE = re.compile(
    r"\{\s*\d+\s*,\s*(ITEM_[A-Z0-9_]+)\s*,\s*SPECIES_[A-Z0-9_]+\s*,\s*SPECIES_[A-Z0-9_]+\s*,\s*(SPECIES_[A-Z0-9_]+)"
)
ITEM_RANGE_RE = re.compile(
    r"setvar\s+VAR_0x8004\s*,\s*(ITEM_[A-Z0-9_]+)\s*\n\s*setvar\s+VAR_0x8005\s*,\s*(ITEM_[A-Z0-9_]+)\s*-\s*\1\s*\+\s*1"
)
NEXUS_AFTER_BOSS_RE = re.compile(
    r"\.species\s*=\s*(SPECIES_[A-Z0-9_]+)[^\n]*NEXUS_AFTER_BOSS\((\w+)\)"
)
FORM_ITEM_VERBS = {
    "ITEM_HOLD": "Hold",
    "ITEM_USE": "Use",
    "ITEM_USE_MULTICHOICE": "Use",
}


def _item_values() -> dict[str, int]:
    text = strip_c_comments(read(REPO_ROOT / "include/constants/items.h"))
    return {name: int(value) for name, value in re.findall(r"\b(ITEM_[A-Z0-9_]+)\s*=\s*(\d+)\s*,", text)}


def _items_named(text: str, values: dict[str, int]) -> set[str]:
    found = set(re.findall(r"\bITEM_[A-Z0-9_]+\b", text))
    by_value = {value: name for name, value in values.items()}
    for first, last in ITEM_RANGE_RE.findall(text):
        if first in values and last in values:
            found.update(by_value[v] for v in range(values[first], values[last] + 1) if v in by_value)
    return found


_ITEM_NAMES: dict[str, str] = {}


def _item_display(item: str) -> str:
    if not _ITEM_NAMES:
        text = read(REPO_ROOT / "src/data/items.h")
        _ITEM_NAMES.update(re.findall(r"\[(ITEM_[A-Z0-9_]+)\]\s*=\s*\{\s*\.name\s*=\s*ITEM_NAME\(\"([^\"]*)\"\)", text))
    return _ITEM_NAMES.get(item) or item.removeprefix("ITEM_").replace("_", " ").title()


def _reachable_from(blocks: dict[str, str], root: str) -> set[str]:
    seen: set[str] = set()
    pending = [root]
    while pending:
        label = pending.pop()
        if label in seen or label not in blocks:
            continue
        seen.add(label)
        pending.extend(set(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", blocks[label])) & set(blocks))
    return seen


def form_item_sources(wanted: set[str]) -> dict[str, list[tuple[str, str]]]:
    """item -> [(map constant, where)] for the items in `wanted`."""
    values = _item_values()
    sources: dict[str, list[tuple[str, str]]] = {}

    def add(item: str, where: tuple[str, str]) -> None:
        if item in wanted and where not in sources.setdefault(item, []):
            sources[item].append(where)

    map_groups = json.loads(read(MAP_GROUPS_JSON))
    for group_name in map_groups.get("group_order") or []:
        for map_name in map_groups.get(group_name) or []:
            if is_docs_excluded_map(map_name, group_name):
                continue
            map_dir = REPO_ROOT / "data" / "maps" / map_name
            try:
                map_data = json.loads(read(map_dir / "map.json"))
                blocks = script_blocks(read(map_dir / "scripts.inc"))
            except (FileNotFoundError, json.JSONDecodeError):
                continue
            where = (str(map_data.get("id") or ""), map_display_name(map_data, map_name))
            text = "\n".join(blocks[label] for label in reachable_script_labels(map_data, blocks))
            for item in _items_named(text, values):
                add(item, where)

    # Nexus after-boss drops: data/scripts/nexus.inc, one script per legendary.
    try:
        legendaries = strip_c_comments(read(REPO_ROOT / "src/data/nexus/legendaries.h"))
        blocks = script_blocks(read(REPO_ROOT / "data/scripts/nexus.inc"))
    except FileNotFoundError:
        return sources
    for species, concept in NEXUS_AFTER_BOSS_RE.findall(legendaries):
        labels = _reachable_from(blocks, f"Nexus_EventScript_{concept}_AfterBoss")
        text = "\n".join(blocks[label] for label in labels)
        name = species.removeprefix("SPECIES_").replace("_", " ").title()
        for item in _items_named(text, values):
            add(item, ("MAP_NEXUS", f"Nexus ({name} boss drop)"))
    return sources


def add_item_form_change_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    try:
        text = strip_c_comments(read(FORM_CHANGE_TABLES_H))
    except FileNotFoundError:
        return

    changes = [
        (target, item, FORM_ITEM_VERBS[method])
        for method, target, item in ITEM_FORM_CHANGE_RE.findall(text)
        if item != "ITEM_NONE"
    ]
    changes += [(target, item, "Fuse with") for item, target in FUSION_RE.findall(text)]
    sources = form_item_sources({item for _, item, _ in changes})
    for target, item, verb in changes:
        if target not in by_species:
            continue
        for map_constant, where in sources.get(item, []):
            _add_location(locations, target, {
                "map": map_constant,
                "name": where,
                "time": "",
                "method": f"{verb} {_item_display(item)}",
                "minLevel": None,
                "maxLevel": None,
                "rate": None,
            })


# ---------------------------------------------------------------------------
# Burmy changes its cloak after a battle fought in a given environment.
# ---------------------------------------------------------------------------
ENVIRONMENT_FORM_RE = re.compile(
    r"\{FORM_CHANGE_END_BATTLE_ENVIRONMENT\s*,\s*(SPECIES_[A-Z0-9_]+)\s*,\s*BATTLE_ENVIRONMENT_([A-Z_]+)"
)


def add_environment_form_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    try:
        text = strip_c_comments(read(FORM_CHANGE_TABLES_H))
    except FileNotFoundError:
        return
    environments: dict[str, list[str]] = {}
    for target, environment in ENVIRONMENT_FORM_RE.findall(text):
        name = environment.replace("_", " ").lower()
        if name not in environments.setdefault(target, []):
            environments[target].append(name)
    for target, names in environments.items():
        if target not in by_species or locations.get(target):
            continue
        _add_location(locations, target, {
            "map": "",
            "name": "After a battle",
            "time": "",
            "method": "Form change: battle in " + " / ".join(names),
            "minLevel": None,
            "maxLevel": None,
            "rate": None,
        })


# ---------------------------------------------------------------------------
# Nexus fragments that roll a random form (src/nexus.c, s*FragmentForms).
# ---------------------------------------------------------------------------
FRAGMENT_FORMS_RE = re.compile(
    r"static\s+const\s+u16\s+s\w*FragmentForms\[\]\s*=\s*\{(.*?)\};",
    re.DOTALL,
)


def add_nexus_random_fragment_form_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    try:
        text = strip_c_comments(read(REPO_ROOT / "src/nexus.c"))
    except FileNotFoundError:
        return
    for body in FRAGMENT_FORMS_RE.findall(text):
        for species in re.findall(r"\bSPECIES_[A-Z0-9_]+\b", body):
            if species not in by_species:
                continue
            _add_location(locations, species, {
                "map": "MAP_NEXUS",
                "name": "Nexus (post-Necrozma daily, boss fragment)",
                "time": "",
                "method": "Nexus fragment (random form)",
                "minLevel": 1,
                "maxLevel": 1,
                "rate": None,
            })
