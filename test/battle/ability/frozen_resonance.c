#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Frozen Resonance turns Normal-type moves into Ice-type moves")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SCRATCH) == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FROZEN_RESONANCE); }
        OPPONENT(SPECIES_DRATINI);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Frozen Resonance boosts converted moves like Refrigerate", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_REFRIGERATE; }
    PARAMETRIZE { ability = ABILITY_FROZEN_RESONANCE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Frozen Resonance summons snow for 5 turns when the user uses a sound move")
{
    GIVEN {
        ASSUME(IsSoundMove(MOVE_HYPER_VOICE));
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FROZEN_RESONANCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
        ABILITY_POPUP(player, ABILITY_FROZEN_RESONANCE);
        MESSAGE("It started to snow!");
    } THEN {
        EXPECT(gBattleWeather & B_WEATHER_SNOW);
    }
}

SINGLE_BATTLE_TEST("Frozen Resonance renews snow instead of announcing it again")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FROZEN_RESONANCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
        TURN { MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
        ABILITY_POPUP(player, ABILITY_FROZEN_RESONANCE);
        MESSAGE("It started to snow!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPER_VOICE, player);
        NOT ABILITY_POPUP(player, ABILITY_FROZEN_RESONANCE);
    } THEN {
        EXPECT_EQ(gBattleStruct->weatherDuration, 4); // Renewed to 5, then the end of turn ticks it once.
    }
}

SINGLE_BATTLE_TEST("Frozen Resonance does not summon snow with non-sound moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_FROZEN_RESONANCE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_FROZEN_RESONANCE);
    } THEN {
        EXPECT(!(gBattleWeather & B_WEATHER_SNOW));
    }
}
