#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Gravitas sets Gravity for 5 turns on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_GRAVITAS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_GRAVITAS);
        MESSAGE("Gravity intensified!");
    } THEN {
        EXPECT(gFieldStatuses & STATUS_FIELD_GRAVITY);
        EXPECT_EQ(gFieldTimers.gravityTimer, 4);
    }
}

SINGLE_BATTLE_TEST("Gravitas boosts the user's moves by 20% against grounded targets during Gravity", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_GRAVITY_WELL; }
    PARAMETRIZE { ability = ABILITY_GRAVITAS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.2), results[1].damage);
    }
}
