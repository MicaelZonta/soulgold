from __future__ import annotations

import unittest

from tools.soulgold_docs.parsers.forms import (
    add_mom_grooming_form_locations,
    add_wild_random_form_locations,
)


def wild(method: str = "Land Mons") -> dict:
    return {"map": "MAP_X", "name": "X", "time": "", "method": method,
            "minLevel": 5, "maxLevel": 7, "rate": 20}


class FormSourceTests(unittest.TestCase):
    def test_random_wild_forms_inherit_the_slot_locations(self) -> None:
        forms = ["SPECIES_TATSUGIRI_CURLY", "SPECIES_TATSUGIRI_DROOPY", "SPECIES_TATSUGIRI_STRETCHY"]
        locations = {"SPECIES_TATSUGIRI_CURLY": [wild("Fishing Mons")]}

        add_wild_random_form_locations(locations, {s: object() for s in forms})  # type: ignore[arg-type]

        for species in forms[1:]:
            with self.subTest(species=species):
                self.assertEqual(
                    [l["method"] for l in locations[species]],
                    ["Fishing Mons (random form)"],
                )

    def test_only_wild_locations_are_inherited(self) -> None:
        gacha = {**wild(), "method": "Gachapon (Rare)"}
        locations = {"SPECIES_SQUAWKABILLY_GREEN": [gacha]}

        add_wild_random_form_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_SQUAWKABILLY_GREEN": object(), "SPECIES_SQUAWKABILLY_BLUE": object()},
        )

        self.assertNotIn("SPECIES_SQUAWKABILLY_BLUE", locations)

    def test_mom_grooms_furfrou_and_deerling_forms(self) -> None:
        species = ["SPECIES_FURFROU_KABUKI", "SPECIES_DEERLING_WINTER", "SPECIES_SAWSBUCK_SPRING", "SPECIES_PIKACHU_LIBRE", "SPECIES_PIKACHU_WORLD"]
        locations = {}

        add_mom_grooming_form_locations(locations, {s: object() for s in species})  # type: ignore[arg-type]

        for s in species:
            with self.subTest(species=s):
                self.assertEqual(locations[s][0]["name"], "New Bark Town (Mom)")


if __name__ == "__main__":
    unittest.main()
