#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Centiferno traps the target in Fire Spin with damaging Fire moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CENTIFERNO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        ABILITY_POPUP(player, ABILITY_CENTIFERNO);
        MESSAGE("The opposing Wobbuffet became trapped in the vortex!");
    } THEN {
        EXPECT(opponent->volatiles.wrapped);
        EXPECT_EQ((u32)opponent->volatiles.wrappedMove, MOVE_FIRE_SPIN);
    }
}

SINGLE_BATTLE_TEST("Centiferno only resets the Fire Spin duration when reapplied")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CENTIFERNO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        ABILITY_POPUP(player, ABILITY_CENTIFERNO);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        NOT ABILITY_POPUP(player, ABILITY_CENTIFERNO);
    } THEN {
        EXPECT(opponent->volatiles.wrapped);
        EXPECT_EQ((u32)opponent->volatiles.wrapTurns, 3);
    }
}

SINGLE_BATTLE_TEST("Centiferno does not trigger on non-Fire moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_CENTIFERNO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_CENTIFERNO);
    } THEN {
        EXPECT(!opponent->volatiles.wrapped);
    }
}
