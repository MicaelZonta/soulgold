"""Parse special overworld sources for obtainable Pokemon forms."""

from __future__ import annotations

import json
import re

from ..c_parser import read, strip_c_comments
from ..models import SpeciesLocation, SpeciesRow
from ..paths import FORM_CHANGE_TABLES_H, REPO_ROOT
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
