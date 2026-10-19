#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Abyssal Maw restores 25% of the damage dealt by Ghost-type moves")
{
    s16 damage;
    s16 healed;
    GIVEN {
        ASSUME(GetMoveType(MOVE_SHADOW_CLAW) == TYPE_GHOST);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ABYSSAL_MAW); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SHADOW_CLAW); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &damage);
        ABILITY_POPUP(player, ABILITY_ABYSSAL_MAW);
        HP_BAR(player, captureDamage: &healed);
    } THEN {
        EXPECT_EQ(-healed, damage / 4);
    }
}

SINGLE_BATTLE_TEST("Abyssal Maw does not drain with other moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_ABYSSAL_MAW); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_ABYSSAL_MAW);
    }
}
