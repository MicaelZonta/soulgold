#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Drum Solo's Grass moves ignore Reflect", s16 damage)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_CELEBRATE; }
    PARAMETRIZE { move = MOVE_REFLECT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DRUM_SOLO); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, move); MOVE(player, MOVE_BRANCH_POKE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Drum Solo's Grass moves ignore Defense boosts", s16 damage)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_CELEBRATE; }
    PARAMETRIZE { move = MOVE_IRON_DEFENSE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DRUM_SOLO); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, move); MOVE(player, MOVE_BRANCH_POKE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Drum Solo's Grass moves ignore defensive Abilities")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DRUM_SOLO); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SAP_SIPPER); }
    } WHEN {
        TURN { MOVE(player, MOVE_BRANCH_POKE); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_SAP_SIPPER);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Drum Solo does not let non-Grass moves ignore Reflect", s16 damage)
{
    enum Move move;
    PARAMETRIZE { move = MOVE_CELEBRATE; }
    PARAMETRIZE { move = MOVE_REFLECT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DRUM_SOLO); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(2); }
    } WHEN {
        TURN { MOVE(opponent, move); MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.5), results[1].damage);
    }
}
