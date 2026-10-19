#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Foam Overflow sets Foam Terrain for 3 turns with offensive Water moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOAM_OVERFLOW); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
        TURN { }
        TURN { }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
        ABILITY_POPUP(player, ABILITY_FOAM_OVERFLOW);
        MESSAGE("Foam bubbled up across the battlefield!");
        MESSAGE("The foam on the battlefield popped away.");
    } THEN {
        EXPECT(!(gFieldStatuses & STATUS_FIELD_FOAM_TERRAIN));
    }
}

SINGLE_BATTLE_TEST("Foam Overflow renews Foam Terrain")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOAM_OVERFLOW); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_FOAM_OVERFLOW);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
        NOT ABILITY_POPUP(player, ABILITY_FOAM_OVERFLOW);
    } THEN {
        EXPECT_EQ(gFieldTimers.terrainTimer, 2);
    }
}

SINGLE_BATTLE_TEST("Foam Terrain makes slower grounded Pokemon move first")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOAM_OVERFLOW); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); }
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
    }
}

SINGLE_BATTLE_TEST("Foam Terrain does not invert speed against Pokemon that are not grounded")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOAM_OVERFLOW); Speed(10); }
        OPPONENT(SPECIES_PIDGEY) { Speed(5); }
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
}

SINGLE_BATTLE_TEST("Foam Terrain cures the status of grounded Water types at the end of the turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FOAM_OVERFLOW); }
        OPPONENT(SPECIES_SQUIRTLE) { Status1(STATUS1_BURN); }
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } SCENE {
        MESSAGE("The foam washed away the opposing Squirtle's status!");
    } THEN {
        EXPECT_EQ(opponent->status1, STATUS1_NONE);
    }
}
