#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Wind Rage sets Tailwind for 4 turns on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_WIND_RAGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_WIND_RAGE);
        MESSAGE("The Tailwind blew from behind your team!");
    } THEN {
        EXPECT(gSideStatuses[B_SIDE_PLAYER] & SIDE_STATUS_TAILWIND);
    }
}

SINGLE_BATTLE_TEST("Wind Rage removes hazards on its side and the foe's screens on entry")
{
    GIVEN {
        PLAYER(SPECIES_WYNAUT);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_WIND_RAGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_STEALTH_ROCK); }
        TURN { MOVE(opponent, MOVE_REFLECT); }
        TURN { SWITCH(player, 1); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_WIND_RAGE);
        MESSAGE("Wobbuffet's raging wind cleared the field!");
        MESSAGE("The Tailwind blew from behind your team!");
    } THEN {
        EXPECT(!IsHazardOnSide(B_SIDE_PLAYER, HAZARDS_STEALTH_ROCK));
        EXPECT(!(gSideStatuses[B_SIDE_OPPONENT] & SIDE_STATUS_REFLECT));
    }
}
