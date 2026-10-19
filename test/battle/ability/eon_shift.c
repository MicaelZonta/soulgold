#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Eon Shift changes the user to the Eeveelution type that resists the move")
{
    enum Move move;
    enum Type type;
    PARAMETRIZE { move = MOVE_EMBER;        type = TYPE_WATER; }
    PARAMETRIZE { move = MOVE_WATER_GUN;    type = TYPE_GRASS; }
    PARAMETRIZE { move = MOVE_KARATE_CHOP;  type = TYPE_PSYCHIC; }
    PARAMETRIZE { move = MOVE_DRAGON_BREATH; type = TYPE_FAIRY; }
    PARAMETRIZE { move = MOVE_GUST;         type = TYPE_ELECTRIC; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_EEVEE) { Ability(ABILITY_EON_SHIFT); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        ABILITY_POPUP(opponent, ABILITY_EON_SHIFT);
    } THEN {
        EXPECT_EQ((enum Type)opponent->types[0], type);
        EXPECT_EQ((enum Type)opponent->types[1], type);
    }
}

SINGLE_BATTLE_TEST("Eon Shift does nothing against types no Eeveelution resists")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_EEVEE) { Ability(ABILITY_EON_SHIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(opponent, ABILITY_EON_SHIFT);
    } THEN {
        EXPECT_EQ((enum Type)opponent->types[0], TYPE_NORMAL);
    }
}

SINGLE_BATTLE_TEST("Eon Shift makes the next hit of the same type resisted")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_EEVEE) { Ability(ABILITY_EON_SHIFT); }
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_EON_SHIFT);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        MESSAGE("It's not very effective…");
    }
}

SINGLE_BATTLE_TEST("Eevee G has Eon Shift as an innate after Mega Evolving")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_EEVEE) { Item(ITEM_GIGANTATITE); USE_DEFAULT_INNATES; }
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); MOVE(player, MOVE_EMBER); }
    } SCENE {
        MESSAGE("The opposing Eevee has Mega Evolved into Eevee G!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        ABILITY_POPUP(opponent, ABILITY_EON_SHIFT);
    } THEN {
        EXPECT_EQ((enum Type)opponent->types[0], TYPE_WATER);
    }
}
