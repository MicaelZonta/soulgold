from __future__ import annotations

import unittest

from tools.soulgold_docs.parsers.gifts import (
    add_gachapon_species_locations,
    add_gift_species_locations,
    add_scripted_legendary_species_locations,
    named_gift_table,
)


class ScriptedSourceTests(unittest.TestCase):
    def test_nicknamed_gift_table_is_read_from_c(self) -> None:
        self.assertEqual(named_gift_table()["1"], ("SPECIES_SPEAROW", 20))
        self.assertEqual(named_gift_table()["2"], ("SPECIES_SHUCKLE", 20))

    def test_kenya_is_a_nicknamed_gift_from_randy(self) -> None:
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_SPEAROW": object()},
        )

        kenya = [l for l in locations["SPECIES_SPEAROW"] if l["method"] == "Gift (nicknamed)"]
        self.assertEqual([(l["map"], l["minLevel"]) for l in kenya], [("MAP_GATE_GOLDENROD_CITY_ROUTE35", 20)])

    def test_nicknamed_gift_with_no_npc_is_not_a_source(self) -> None:
        # Shuckie's script still exists, but no object runs it: Kirk's house
        # gives Gimmighoul now.
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_SHUCKLE": object()},
        )

        nicknamed = [
            l for l in locations.get("SPECIES_SHUCKLE", [])
            if l["method"] == "Gift (nicknamed)"
        ]
        self.assertEqual(nicknamed, [])

    def test_unreachable_test_script_is_not_a_gift(self) -> None:
        # Route25_BillsHouse_Test gives Spinda, but no event ever runs it.
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_SPINDA": object()},
        )

        self.assertNotIn("SPECIES_SPINDA", locations)

    def test_catchable_static_encounter_is_a_source(self) -> None:
        locations = {}

        add_scripted_legendary_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_SUDOWOODO": object()},
        )

        route36 = [l for l in locations["SPECIES_SUDOWOODO"] if l["map"] == "MAP_ROUTE36"]
        self.assertEqual(len(route36), 1)
        self.assertEqual(route36[0]["method"], "Static encounter")
        self.assertEqual(route36[0]["minLevel"], 30)

    def test_boss_fight_without_catching_is_not_a_source(self) -> None:
        # The Fighting Dojo battles set B_FLAG_NO_CATCHING first.
        locations = {}

        add_scripted_legendary_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_LICKILICKY": object()},
        )

        dojo = [
            l for l in locations.get("SPECIES_LICKILICKY", [])
            if l["map"] == "MAP_SAFFRON_CITY_FIGHTING_DOJO"
        ]
        self.assertEqual(dojo, [])

    def test_every_gachapon_machine_is_read(self) -> None:
        locations = {}

        add_gachapon_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_CLEFAIRY": object(), "SPECIES_SENTRET": object()},
        )

        self.assertIn(
            "Goldenrod Gachapon (Great machine)",
            {l["name"] for l in locations["SPECIES_CLEFAIRY"]},
        )
        self.assertIn(
            "Goldenrod Gachapon (Basic machine)",
            {l["name"] for l in locations["SPECIES_SENTRET"]},
        )


if __name__ == "__main__":
    unittest.main()
