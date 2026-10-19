#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Stonesurge sets Stealth Rock on the foe's side on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_STONESURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_STONESURGE);
        MESSAGE("Pointed stones float in the air around the opposing team!");
    } THEN {
        EXPECT(IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEALTH_ROCK));
    }
}

SINGLE_BATTLE_TEST("Stonesurge sets Stealth Rock again every time it enters")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_STONESURGE); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_DEFOG); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_STONESURGE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DEFOG, opponent);
        ABILITY_POPUP(player, ABILITY_STONESURGE);
    } THEN {
        EXPECT(IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEALTH_ROCK));
    }
}
