from __future__ import annotations

import unittest

from tools.soulgold_docs.parsers.forms import (
    add_environment_form_locations,
    add_item_form_change_locations,
    add_nexus_random_fragment_form_locations,
)


class ItemFormTests(unittest.TestCase):
    def forms(self, *species: str) -> dict:
        locations: dict = {}
        by_species = {s: object() for s in species}
        add_item_form_change_locations(locations, by_species)  # type: ignore[arg-type]
        return locations

    def test_nectars_sold_in_olivine(self) -> None:
        locations = self.forms("SPECIES_ORICORIO_PAU")
        self.assertIn(("Olivine City", "Use Pink Nectar"),
                      {(l["name"], l["method"]) for l in locations["SPECIES_ORICORIO_PAU"]})

    def test_memories_come_from_gladion_rematch_range(self) -> None:
        locations = self.forms("SPECIES_SILVALLY_FAIRY", "SPECIES_SILVALLY_FIRE")
        for species in ("SPECIES_SILVALLY_FAIRY", "SPECIES_SILVALLY_FIRE"):
            self.assertEqual(locations[species][0]["map"], "MAP_CIANWOOD_CITY")

    def test_nexus_drops(self) -> None:
        locations = self.forms("SPECIES_KYUREM_BLACK", "SPECIES_GENESECT_CHILL", "SPECIES_ZYGARDE_10_AURA_BREAK")
        self.assertEqual(locations["SPECIES_KYUREM_BLACK"][0]["method"], "Fuse with DNA Splicers")
        self.assertEqual(locations["SPECIES_GENESECT_CHILL"][0]["name"], "Nexus (Genesect boss drop)")
        self.assertEqual(locations["SPECIES_ZYGARDE_10_AURA_BREAK"][0]["name"], "Nexus (Zygarde boss drop)")

    def test_item_outside_the_rom_is_no_source(self) -> None:
        # The Meteorite only exists in Mt. Chimney, which is not in the ROM.
        locations = self.forms("SPECIES_DEOXYS_ATTACK")
        self.assertNotIn("SPECIES_DEOXYS_ATTACK", locations)

    def test_deoxys_fragment_rolls_a_forme(self) -> None:
        locations: dict = {}
        add_nexus_random_fragment_form_locations(locations, {"SPECIES_DEOXYS_SPEED": object()})  # type: ignore[arg-type]
        self.assertEqual(locations["SPECIES_DEOXYS_SPEED"][0]["method"], "Nexus fragment (random form)")

    def test_burmy_sandy_changes_after_battle(self) -> None:
        locations: dict = {}
        add_environment_form_locations(locations, {"SPECIES_BURMY_SANDY": object()})  # type: ignore[arg-type]
        self.assertIn("cave", locations["SPECIES_BURMY_SANDY"][0]["method"])


if __name__ == "__main__":
    unittest.main()
