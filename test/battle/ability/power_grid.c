#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Power Grid stores a charge when hit by a special move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_POWER_GRID); }
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        ABILITY_POPUP(opponent, ABILITY_POWER_GRID);
        MESSAGE("The opposing Wobbuffet stored the energy!");
    } THEN {
        EXPECT(opponent->volatiles.powerGridCharged);
    }
}

SINGLE_BATTLE_TEST("Power Grid does not charge from physical moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_POWER_GRID); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_POWER_GRID);
    }
}

SINGLE_BATTLE_TEST("Power Grid's charge boosts the next special move by 30% and is spent", s16 damage)
{
    bool32 charged;
    PARAMETRIZE { charged = FALSE; }
    PARAMETRIZE { charged = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_POWER_GRID); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, charged ? MOVE_EMBER : MOVE_CELEBRATE); MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } THEN {
        EXPECT(!player->volatiles.powerGridCharged);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[1].damage);
    }
}
