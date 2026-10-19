#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Blazing Surge sets Fire Terrain for 5 turns on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_BLAZING_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
        TURN { }
        TURN { }
        TURN { }
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_BLAZING_SURGE);
        MESSAGE("Flames spread across the battlefield!");
        MESSAGE("The flames on the battlefield died down.");
    } THEN {
        EXPECT(!(gFieldStatuses & STATUS_FIELD_FIRE_TERRAIN));
    }
}

SINGLE_BATTLE_TEST("Fire Terrain boosts grounded Fire-type moves by 30%", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_BLAZING_SURGE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Fire Terrain heals grounded Fire types by 1/16 at the end of the turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_BLAZING_SURGE); }
        OPPONENT(SPECIES_CHARMANDER) { MaxHP(160); HP(80); }
    } WHEN {
        TURN { }
    } SCENE {
        MESSAGE("The opposing Charmander is healed by the fiery terrain!");
        HP_BAR(opponent, damage: -10);
    }
}

SINGLE_BATTLE_TEST("Fire Terrain does not heal non-Fire types")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_BLAZING_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(160); HP(80); }
    } WHEN {
        TURN { }
    } SCENE {
        NOT MESSAGE("The opposing Wobbuffet is healed by the fiery terrain!");
    }
}
