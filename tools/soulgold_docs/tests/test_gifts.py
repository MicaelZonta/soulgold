from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
from types import SimpleNamespace

from tools.soulgold_docs.parsers import gifts
from tools.soulgold_docs.parsers.gifts import FOSSIL_REVIVAL_ITEMS, add_gift_species_locations, add_scripted_encounter_species_locations


class GiftLocationTests(unittest.TestCase):
    def test_oaks_pokedex_reward_is_the_manaphy_mystery_egg(self) -> None:
        # O ovo do Oak era de Arceus. Decisao de 19/10/2026: o Arceus vem das
        # Sinjoh Ruins e o Oak passou a dar o Mystery Egg (Manaphy).
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {"SPECIES_MANAPHY": object(), "SPECIES_ARCEUS_NORMAL": object()},
        )

        oak = [
            location for location in locations["SPECIES_MANAPHY"]
            if location["map"] == "MAP_GOLDENROD_CITY_RADIO_TOWER_2F"
        ]
        self.assertEqual(len(oak), 1)
        self.assertEqual(oak[0]["name"], "Gift from Oak (Pokédex completion reward)")
        self.assertEqual(oak[0]["method"], "Gift Egg")
        self.assertFalse(any(
            location["map"] == "MAP_GOLDENROD_CITY_RADIO_TOWER_2F"
            for location in locations.get("SPECIES_ARCEUS_NORMAL", [])
        ))

    def test_achievement_rewards_include_their_trophy_milestones(self) -> None:
        expected = {
            "SPECIES_GRENINJA_BOND": 30,
            "SPECIES_POIPOLE": 45,
            "SPECIES_FLOETTE_ETERNAL": 60,
            "SPECIES_ZARUDE": 75,
            "SPECIES_MAGEARNA_ORIGINAL": 100,
        }
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {species: object() for species in expected},
        )

        for species, trophies in expected.items():
            with self.subTest(species=species):
                self.assertEqual(len(locations[species]), 1)
                location = locations[species][0]
                self.assertEqual(location["map"], "MAP_ROUTE40_HOUSE4")
                self.assertEqual(
                    location["name"],
                    f"Route 40 Achievement reward ({trophies} trophies)",
                )
                self.assertEqual(location["method"], "Gift")

    def test_goldenrod_game_corner_prizes_are_exchange_sources(self) -> None:
        prizes = {
            "SPECIES_PAWNIARD",
            "SPECIES_MUNCHLAX",
            "SPECIES_SNEASEL_HISUI",
            "SPECIES_DEINO",
            "SPECIES_PORYGON",
        }
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {species: object() for species in prizes},
        )

        for species in prizes:
            with self.subTest(species=species):
                exchange = next(
                    location for location in locations[species]
                    if location["map"] == "MAP_GOLDENROD_CITY_GAME_CORNER"
                )
                self.assertEqual(exchange["name"], "Goldenrod Game Corner")
                self.assertEqual(exchange["method"], "Exchange")
                self.assertEqual(exchange["minLevel"], 15)
                self.assertEqual(exchange["maxLevel"], 15)

    def test_battle_cafe_prizes_are_point_exchange_sources(self) -> None:
        # O Cafe vai sendo esvaziado: toda especie que ganha fonte no mundo sai
        # do balcao de pontos (politica do autor, 19/10/2026). Ja sairam as aves
        # de Galar, os quatro Tapus, Koraidon e Miraidon; sobraram as Forcas da
        # Natureza.
        prizes = {
            "SPECIES_TORNADUS_INCARNATE",
            "SPECIES_THUNDURUS_INCARNATE",
            "SPECIES_LANDORUS_INCARNATE",
            "SPECIES_ENAMORUS_INCARNATE",
        }
        removed = {
            "SPECIES_ARTICUNO_GALAR",
            "SPECIES_ZAPDOS_GALAR",
            "SPECIES_MOLTRES_GALAR",
            "SPECIES_TAPU_KOKO",
            "SPECIES_TAPU_LELE",
            "SPECIES_TAPU_BULU",
            "SPECIES_TAPU_FINI",
            "SPECIES_MIRAIDON",
            "SPECIES_KORAIDON",
        }
        other_species = {"SPECIES_DIANCIE", "SPECIES_ZAPDOS"}
        by_species = {species: object() for species in prizes | removed | other_species}
        locations = {}

        for _ in range(2):
            add_gift_species_locations(locations, by_species)

        for species in prizes:
            with self.subTest(species=species):
                cafe_locations = [
                    location for location in locations.get(species, [])
                    if location["map"] == "MAP_BATTLE_CAFE"
                ]
                self.assertEqual(cafe_locations, [{
                    "map": "MAP_BATTLE_CAFE",
                    "name": "Battle Cafe point exchange",
                    "time": "",
                    "method": "Exchange",
                    "minLevel": 70,
                    "maxLevel": 70,
                    "rate": None,
                }])

        for species in removed:
            with self.subTest(removed=species):
                self.assertFalse(any(
                    location["map"] == "MAP_BATTLE_CAFE"
                    for location in locations.get(species, [])
                ))

        diancie = [
            location for location in locations["SPECIES_DIANCIE"]
            if location["map"] == "MAP_BATTLE_CAFE"
        ]
        self.assertEqual(len(diancie), 1)
        self.assertEqual(diancie[0]["name"], "Battle Cafe")
        self.assertEqual(diancie[0]["method"], "Gift")
        self.assertFalse(any(
            location["map"] == "MAP_BATTLE_CAFE"
            for location in locations.get("SPECIES_ZAPDOS", [])
        ))

    def test_fossil_revivals_are_not_presented_as_ordinary_gifts(self) -> None:
        locations = {}

        add_gift_species_locations(  # type: ignore[arg-type]
            locations,
            {species: object() for species in FOSSIL_REVIVAL_ITEMS},
        )

        for species, fossil in FOSSIL_REVIVAL_ITEMS.items():
            with self.subTest(species=species):
                expected_count = 2 if species == "SPECIES_KABUTO" else 1
                self.assertEqual(len(locations[species]), expected_count)
                location = locations[species][0]
                self.assertEqual(location["map"], "MAP_RUINS_OF_ALPH_LAB")
                self.assertEqual(location["name"], "Ruins of Alph Lab")
                self.assertIn(
                    fossil.removeprefix("ITEM_").replace("_", " ").title(),
                    location["method"],
                )
                self.assertNotEqual(location["method"], "Gift")

        for species in {
            "SPECIES_LILEEP",
            "SPECIES_KABUTO",
            "SPECIES_AERODACTYL",
            "SPECIES_ARCHEN",
            "SPECIES_TYRUNT",
            "SPECIES_AMAURA",
        }:
            self.assertIn("found via Rock Smash in Ruins of Alph", locations[species][0]["method"])

        self.assertEqual(locations["SPECIES_KABUTO"][0]["minLevel"], 5)
        self.assertIn("before 4th badge", locations["SPECIES_KABUTO"][0]["method"])
        self.assertEqual(locations["SPECIES_KABUTO"][1]["minLevel"], 20)
        self.assertIn("after 4th badge", locations["SPECIES_KABUTO"][1]["method"])


class ScriptedEncounterTests(unittest.TestCase):
    def test_live_static_encounters_have_area_method_and_level(self) -> None:
        expected = {
            "SPECIES_SUDOWOODO": ("Route 36", 30),
            "SPECIES_LAPRAS": ("Union Cave B2F", 45),
            "SPECIES_GYARADOS": ("Lake of Rage", 35),
            "SPECIES_ELECTRODE": ("Rocket Hideout B2F", 40),
        }
        locations = {}
        for _ in range(2):
            add_scripted_encounter_species_locations(locations, {key: object() for key in expected})
        for species, (area, level) in expected.items():
            with self.subTest(species=species):
                matches = [row for row in locations[species]
                           if row["name"] == area and row["minLevel"] == level]
                self.assertEqual(len(matches), 1)
                self.assertEqual(matches[0]["maxLevel"], level)
                self.assertEqual(matches[0]["method"], "Static encounter")
                self.assertIsNone(matches[0]["rate"])

    def test_live_kanto_snorlax_is_listed(self) -> None:
        # Kanto saiu da lista de exclusao do site em 27/10/2026, junto com a
        # adocao do Kanto do HnS: o Snorlax da Vermilion e conteudo alcancavel.
        locations = {}
        add_scripted_encounter_species_locations(locations, {"SPECIES_SNORLAX": object()})
        matches = [row for row in locations["SPECIES_SNORLAX"]
                   if row["map"] == "MAP_VERMILION_CITY"]
        self.assertEqual(len(matches), 1)
        self.assertEqual(matches[0]["minLevel"], 50)

    def test_live_route41_tentacruel_guardians_are_not_listed(self) -> None:
        locations = {}
        add_scripted_encounter_species_locations(locations, {"SPECIES_TENTACRUEL": object()})
        self.assertNotIn("SPECIES_TENTACRUEL", locations)

    def test_skips_uncatchable_and_unreachable_battles_and_preserves_legendaries(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            map_dir = root / "data/maps/Route36"
            map_dir.mkdir(parents=True)
            groups = root / "groups.json"
            groups.write_text(json.dumps({"group_order": ["Johto"], "Johto": ["Route36"]}))
            (map_dir / "map.json").write_text(json.dumps({
                "id": "MAP_ROUTE36", "name": "Route36",
                "object_events": [{"script": "Encounter"}],
            }))
            (map_dir / "scripts.inc").write_text("""Encounter::
    setflag FLAG_SYS_NO_CATCHING
    setwildbattle SPECIES_MACHAMP, 1
    dowildbattle
    clearflag FLAG_SYS_NO_CATCHING
    setwildbattle SPECIES_SUDOWOODO, 30
    dowildbattle
    legendaryencounter SPECIES_MEWTWO, 70, 1, FLAG_TEST
    seteventmon SPECIES_MEWTWO, 70
    end
Unused::
    setwildbattle SPECIES_LAPRAS, 45
    dowildbattle
    end
""")
            locations = {}
            with patch.object(gifts, "REPO_ROOT", root), patch.object(gifts, "MAP_GROUPS_JSON", groups):
                add_scripted_encounter_species_locations(locations, {
                    species: SimpleNamespace(categories=["legendary"] if species == "SPECIES_MEWTWO" else [])
                    for species in ["SPECIES_MACHAMP", "SPECIES_SUDOWOODO", "SPECIES_MEWTWO", "SPECIES_LAPRAS"]
                })
            self.assertEqual(set(locations), {"SPECIES_SUDOWOODO", "SPECIES_MEWTWO"})
            self.assertEqual(len(locations["SPECIES_MEWTWO"]), 1)
            self.assertEqual(locations["SPECIES_MEWTWO"][0]["method"], "Legendary encounter")


if __name__ == "__main__":
    unittest.main()
