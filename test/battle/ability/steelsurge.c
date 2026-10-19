#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Steelsurge sets sharp steel on the foe's side on entry")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_STEELSURGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_STEELSURGE);
        MESSAGE("Sharp-pointed pieces of steel started floating around the opposing Pokémon!");
    } THEN {
        EXPECT(IsHazardOnSide(B_SIDE_OPPONENT, HAZARDS_STEELSURGE));
    }
}
