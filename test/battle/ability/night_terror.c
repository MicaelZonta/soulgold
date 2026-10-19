#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Night Terror makes the target drowsy with its first non-resisted Dark or Fairy hit")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_BITE) == TYPE_DARK);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NIGHT_TERROR); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
        TURN { }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BITE, player);
        ABILITY_POPUP(player, ABILITY_NIGHT_TERROR);
        MESSAGE("The opposing Wobbuffet grew drowsy!");
        MESSAGE("The opposing Wobbuffet fell asleep!");
    } THEN {
        EXPECT(opponent->status1 & STATUS1_SLEEP);
    }
}

SINGLE_BATTLE_TEST("Night Terror does not trigger on resisted hits")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NIGHT_TERROR); }
        OPPONENT(SPECIES_UMBREON);
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_NIGHT_TERROR);
    }
}

SINGLE_BATTLE_TEST("Night Terror only triggers once per entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NIGHT_TERROR); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_INSOMNIA); }
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_NIGHT_TERROR);
    }
}

SINGLE_BATTLE_TEST("Night Terror keeps only one target asleep at a time")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NIGHT_TERROR); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_BITE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
        TURN { SWITCH(player, 1); SWITCH(opponent, 1); }
        TURN { SWITCH(player, 0); }
        TURN { MOVE(player, MOVE_BITE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_NIGHT_TERROR);
        MESSAGE("The opposing Wobbuffet fell asleep!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BITE, player);
        NOT ABILITY_POPUP(player, ABILITY_NIGHT_TERROR);
    }
}
