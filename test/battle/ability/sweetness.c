#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Sweetness cures the user's status and sets Mist on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SWEETNESS); Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_SWEETNESS);
        MESSAGE("A sweet aroma wrapped your team in a soothing mist!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
        EXPECT(gSideStatuses[B_SIDE_PLAYER] & SIDE_STATUS_MIST);
    }
}

DOUBLE_BATTLE_TEST("Sweetness also cures its ally's status")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SWEETNESS); }
        PLAYER(SPECIES_WYNAUT) { Status1(STATUS1_PARALYSIS); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_SWEETNESS);
    } THEN {
        EXPECT_EQ(playerRight->status1, STATUS1_NONE);
    }
}
