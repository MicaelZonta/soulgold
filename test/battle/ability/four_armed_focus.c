#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Four-Armed Focus raises accuracy and critical-hit stages before each punching move")
{
    GIVEN {
        ASSUME(IsPunchingMove(MOVE_MEGA_PUNCH));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOUR_ARMED_FOCUS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MEGA_PUNCH); }
        TURN { MOVE(player, MOVE_MEGA_PUNCH); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_FOUR_ARMED_FOCUS);
        MESSAGE("Wobbuffet focused all four arms!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_PUNCH, player);
        ABILITY_POPUP(player, ABILITY_FOUR_ARMED_FOCUS);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_PUNCH, player);
    } THEN {
        EXPECT_EQ((u32)player->volatiles.fourArmedFocusStages, 2);
    }
}

SINGLE_BATTLE_TEST("Four-Armed Focus guarantees critical hits after three punches")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOUR_ARMED_FOCUS); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(9999); MaxHP(9999); }
    } WHEN {
        TURN { MOVE(player, MOVE_MEGA_PUNCH); }
        TURN { MOVE(player, MOVE_MEGA_PUNCH); }
        TURN { MOVE(player, MOVE_MEGA_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_PUNCH, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_PUNCH, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_PUNCH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Four-Armed Focus does not trigger on non-punching moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOUR_ARMED_FOCUS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_FOUR_ARMED_FOCUS);
    } THEN {
        EXPECT_EQ((u32)player->volatiles.fourArmedFocusStages, 0);
    }
}
