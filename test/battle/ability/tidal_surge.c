#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Tidal Surge sets Water Terrain on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TIDAL_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_TIDAL_SURGE);
        MESSAGE("Water flooded the battlefield!");
    } THEN {
        EXPECT(gFieldStatuses & STATUS_FIELD_WATER_TERRAIN);
    }
}

SINGLE_BATTLE_TEST("Water Terrain boosts grounded Water-type moves by 30%", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_TIDAL_SURGE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.3), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Water Terrain heals grounded Water types by 1/16 at the end of the turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TIDAL_SURGE); }
        OPPONENT(SPECIES_SQUIRTLE) { MaxHP(160); HP(80); }
    } WHEN {
        TURN { }
    } SCENE {
        MESSAGE("The opposing Squirtle is healed by the watery terrain!");
        HP_BAR(opponent, damage: -10);
    }
}

SINGLE_BATTLE_TEST("Tidal Surge replaces another terrain")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TIDAL_SURGE); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_BLAZING_SURGE); }
    } WHEN {
        TURN { }
    } THEN {
        EXPECT(!(gFieldStatuses & STATUS_FIELD_FIRE_TERRAIN) != !(gFieldStatuses & STATUS_FIELD_WATER_TERRAIN));
    }
}
