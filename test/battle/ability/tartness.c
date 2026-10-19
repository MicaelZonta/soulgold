#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Tartness makes the user's moves never miss")
{
    PASSES_RANDOMLY(10, 10, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_ZAP_CANNON) == 50);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TARTNESS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ZAP_CANNON); }
    } SCENE {
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Tartness ignores the target's evasion boosts")
{
    PASSES_RANDOMLY(10, 10, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TARTNESS); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_DOUBLE_TEAM); MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Tartness does not stop the opponent's moves from missing")
{
    PASSES_RANDOMLY(1, 2, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TARTNESS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_ZAP_CANNON); }
    } SCENE {
        HP_BAR(player);
    }
}
