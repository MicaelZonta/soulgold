#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Deadeye makes projectile moves always land a critical hit")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_SNIPE_SHOT; }
    PARAMETRIZE { move = MOVE_SHADOW_BALL; }
    PARAMETRIZE { move = MOVE_WATER_GUN; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DEADEYE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Deadeye does not guarantee critical hits for other moves")
{
    PASSES_RANDOMLY(23, 24, RNG_CRITICAL_HIT);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DEADEYE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Deadeye critical hits do not get the Sniper bonus", s16 damage)
{
    enum Ability innate;
    PARAMETRIZE { innate = ABILITY_NONE; }
    PARAMETRIZE { innate = ABILITY_SNIPER; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_DEADEYE); Innates(innate); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SNIPE_SHOT); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}
