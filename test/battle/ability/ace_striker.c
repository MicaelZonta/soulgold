#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Ace Striker boosts ball and bomb moves by 30%", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_ACE_STRIKER; }
    GIVEN {
        ASSUME(IsBallisticMove(MOVE_PYRO_BALL));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PYRO_BALL); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Ace Striker does not boost other moves", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_ACE_STRIKER; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Ace Striker's ball and bomb moves ignore the target's Ability")
{
    GIVEN {
        ASSUME(IsBallisticMove(MOVE_SHADOW_BALL));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ACE_STRIKER); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_BULLETPROOF); }
    } WHEN {
        TURN { MOVE(player, MOVE_SHADOW_BALL); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_BULLETPROOF);
        HP_BAR(opponent);
    }
}
