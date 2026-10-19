#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Gigantamax Megas are announced as \"<Species> G\"")
{
    GIVEN {
        PLAYER(SPECIES_CHARIZARD) { Item(ITEM_GIGANTATITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        MESSAGE("Charizard has Mega Evolved into Charizard G!");
    } THEN {
        EXPECT_EQ(player->species, SPECIES_CHARIZARD_GMAX);
    }
}

SINGLE_BATTLE_TEST("Charizard G sets Fire Terrain when it Mega Evolves")
{
    GIVEN {
        PLAYER(SPECIES_CHARIZARD) { Item(ITEM_GIGANTATITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        MESSAGE("Charizard has Mega Evolved into Charizard G!");
        ABILITY_POPUP(player, ABILITY_BLAZING_SURGE);
        MESSAGE("Flames spread across the battlefield!");
    }
}

SINGLE_BATTLE_TEST("Drednaw G sets Stealth Rock when it Mega Evolves")
{
    GIVEN {
        PLAYER(SPECIES_DREDNAW) { Item(ITEM_GIGANTATITE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_STONESURGE);
    } THEN {
        EXPECT(IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEALTH_ROCK));
    }
}

SINGLE_BATTLE_TEST("Gigantamax Megas revert to their base form after the battle")
{
    GIVEN {
        PLAYER(SPECIES_VENUSAUR) { Item(ITEM_GIGANTATITE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, gimmick: GIMMICK_MEGA); }
    } THEN {
        EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_VENUSAUR);
    }
}

SINGLE_BATTLE_TEST("Lapras G turns Normal moves into Ice through its Frozen Resonance innate")
{
    GIVEN {
        PLAYER(SPECIES_LAPRAS) { Item(ITEM_ICETITE); USE_DEFAULT_INNATES; }
        OPPONENT(SPECIES_DRATINI);
    } WHEN {
        TURN { MOVE(player, MOVE_BODY_SLAM, gimmick: GIMMICK_MEGA); }
    } SCENE {
        MESSAGE("Lapras has Mega Evolved into Lapras G!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BODY_SLAM, player);
        MESSAGE("It's super effective!");
    }
}
