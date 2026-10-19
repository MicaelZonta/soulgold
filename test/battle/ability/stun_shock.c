#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Stun Shock has a 30% chance to paralyze or poison with sound moves")
{
    PASSES_RANDOMLY(3, 10, RNG_STUN_SHOCK);
    GIVEN {
        ASSUME(IsSoundMove(MOVE_HYPER_VOICE));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_STUN_SHOCK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
        ABILITY_POPUP(player, ABILITY_STUN_SHOCK);
    } THEN {
        EXPECT(opponent->status1 & (STATUS1_PARALYSIS | STATUS1_POISON));
    }
}

SINGLE_BATTLE_TEST("Stun Shock picks paralysis or poison at random")
{
    PASSES_RANDOMLY(1, 2, RNG_STUN_SHOCK_STATUS);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_STUN_SHOCK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE, WITH_RNG(RNG_STUN_SHOCK, TRUE)); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_STUN_SHOCK);
    } THEN {
        EXPECT(opponent->status1 & STATUS1_PARALYSIS);
    }
}

SINGLE_BATTLE_TEST("Stun Shock does not trigger on non-sound moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_STUN_SHOCK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_STUN_SHOCK, TRUE)); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_STUN_SHOCK);
    }
}
