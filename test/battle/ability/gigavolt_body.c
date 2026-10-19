#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Gigavolt Body reduces direct damage by 25%", s16 damage)
{
    enum Ability ability;
    enum Move move;
    PARAMETRIZE { ability = ABILITY_NONE; move = MOVE_SCRATCH; }
    PARAMETRIZE { ability = ABILITY_GIGAVOLT_BODY; move = MOVE_SCRATCH; }
    PARAMETRIZE { ability = ABILITY_NONE; move = MOVE_EMBER; }
    PARAMETRIZE { ability = ABILITY_GIGAVOLT_BODY; move = MOVE_EMBER; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.75), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, UQ_4_12(0.75), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Gigavolt Body does not reduce indirect damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_GIGAVOLT_BODY); MaxHP(160); HP(160); Status1(STATUS1_POISON); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } THEN {
        EXPECT_EQ(player->hp, 140);
    }
}
