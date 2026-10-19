#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Meltdown's punching moves inflict Torment")
{
    GIVEN {
        ASSUME(IsPunchingMove(MOVE_MEGA_PUNCH));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MELTDOWN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MEGA_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_PUNCH, player);
        ABILITY_POPUP(player, ABILITY_MELTDOWN);
        MESSAGE("The opposing Wobbuffet was subjected to torment!");
    } THEN {
        EXPECT(opponent->volatiles.torment);
    }
}

SINGLE_BATTLE_TEST("Meltdown does not trigger on non-punching moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_MELTDOWN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_MELTDOWN);
    } THEN {
        EXPECT(!opponent->volatiles.torment);
    }
}
