#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Sweet Finale makes healing moves restore 25% more HP")
{
    GIVEN {
        ASSUME(IsHealingMove(MOVE_RECOVER));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SWEET_FINALE); MaxHP(400); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RECOVER); }
    } SCENE {
        HP_BAR(player, damage: -250);
    }
}

DOUBLE_BATTLE_TEST("Sweet Finale shares half of the HP it restores with its ally")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SWEET_FINALE); MaxHP(400); HP(1); }
        PLAYER(SPECIES_WYNAUT) { MaxHP(400); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_RECOVER); }
    } SCENE {
        HP_BAR(playerLeft, damage: -250);
        ABILITY_POPUP(playerLeft, ABILITY_SWEET_FINALE);
        HP_BAR(playerRight, damage: -125);
        MESSAGE("Wynaut shared the sweet treat!");
    }
}
