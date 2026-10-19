#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Hibernate reduces damage taken by 25% while asleep", s16 damage)
{
    u32 status;
    PARAMETRIZE { status = STATUS1_NONE; }
    PARAMETRIZE { status = STATUS1_SLEEP_TURN(3); }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_HIBERNATE); Status1(status); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.75), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Hibernate restores 1/8 of max HP at the end of the turn while asleep")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_HIBERNATE); MaxHP(160); HP(80); Status1(STATUS1_SLEEP_TURN(3)); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_HIBERNATE);
        HP_BAR(player, damage: -20);
    }
}

SINGLE_BATTLE_TEST("Hibernate does not heal while awake")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_HIBERNATE); MaxHP(160); HP(80); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_HIBERNATE);
    }
}
