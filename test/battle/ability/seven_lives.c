#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Seven Lives survives a knockout hit with 1 HP and forces a switch")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MEOWTH) { Ability(ABILITY_SEVEN_LIVES); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ABILITY_POPUP(opponent, ABILITY_SEVEN_LIVES);
        NOT MESSAGE("The opposing Meowth fainted!");
    } THEN {
        EXPECT_EQ(gBattleStruct->sevenLivesUsed[B_SIDE_OPPONENT][0], 1);
        EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_HP), 1);
        EXPECT_EQ(gBattlerPartyIndexes[B_POSITION_OPPONENT_LEFT], 1);
    }
}

SINGLE_BATTLE_TEST("Seven Lives fails when there is no ally to switch to")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MEOWTH) { Ability(ABILITY_SEVEN_LIVES); HP(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_SEVEN_LIVES);
        MESSAGE("The opposing Meowth fainted!");
    }
}

SINGLE_BATTLE_TEST("Seven Lives runs out after seven escapes")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MEOWTH) { Ability(ABILITY_SEVEN_LIVES); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
    } SCENE {
        MESSAGE("The opposing Meowth fainted!");
    } THEN {
        EXPECT_EQ(gBattleStruct->sevenLivesUsed[B_SIDE_OPPONENT][0], 7);
    }
}

SINGLE_BATTLE_TEST("Seven Lives ignores indirect damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MEOWTH) { Ability(ABILITY_SEVEN_LIVES); HP(1); Status1(STATUS1_POISON); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { SEND_OUT(opponent, 1); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_SEVEN_LIVES);
        MESSAGE("The opposing Meowth fainted!");
    }
}
