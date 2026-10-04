"""Berry Master's garden pests (Route 30): the only source of eight families.

Read from src/berry_garden.c, so the site follows the game: every species in
the sPests table (by Berry colour, hour and the Berry's generation) plus the
two the mulch brings (GardenPest_Pick). Scatterbug is stored as the Fancy
pattern and turned into any pattern by GetWildFormVariantSpecies, exactly like
a wild slot, so add_wild_random_form_locations expands it afterwards.
"""

from __future__ import annotations

import re

from ..c_parser import read, strip_c_comments
from ..models import SpeciesLocation, SpeciesRow
from ..paths import BERRY_GARDEN_C

PESTS_RE = re.compile(r"sPests\[[^\]]*\]\[[^\]]*\]\s*=\s*\{(.*?)\};", re.DOTALL)
PICK_RE = re.compile(r"u16 GardenPest_Pick\(.*?\n\}", re.DOTALL)


def add_berry_garden_pest_locations(
    locations: dict[str, list[SpeciesLocation]],
    by_species: dict[str, SpeciesRow],
) -> None:
    try:
        text = strip_c_comments(read(BERRY_GARDEN_C))
    except FileNotFoundError:
        return
    pool: list[str] = []
    for block in (PESTS_RE.search(text), PICK_RE.search(text)):
        if not block:
            continue
        for species in re.findall(r"\bSPECIES_[A-Z0-9_]+\b", block.group(0)):
            if species in by_species and species not in pool:
                pool.append(species)
    for species in pool:
        location: SpeciesLocation = {
            "map": "MAP_ROUTE30",
            "name": "Route 30",
            "time": "",
            "method": "Berry Master's garden (pest on a Berry plot)",
            "minLevel": 10,
            "maxLevel": 60,
            "rate": None,
        }
        locations.setdefault(species, [])
        if location not in locations[species]:
            locations[species].append(location)
