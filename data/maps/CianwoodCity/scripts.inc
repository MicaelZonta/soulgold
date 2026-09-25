CianwoodCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CianwoodCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CianwoodCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, CianwoodCity_EventScript_InitializeSuicune
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

CianwoodCity_RemoveEusine::
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	end

@ Gated on VAR_TEMP_1 (reset to 0 by CityEnter below on every map entry), not
@ on a flag/var that is constantly true. MAP_SCRIPT_ON_FRAME_TABLE
@ conditions are re-checked by TryRunOnFrameMapScript() every single frame
@ the map is loaded, and merely queuing a script that frame
@ (ScriptContext_SetupScript) locks the player's field controls for it -
@ PlayerStep only runs on frames where no script gets queued. Gating
@ directly on a condition that holds for most of the game (e.g. "Fly not
@ received yet") would re-lock controls every single frame forever and
@ PlayerStep would never run again: the player stuck in place the instant
@ they enter Cianwood City, indistinguishable from the game freezing.
@ Gating on VAR_TEMP_1 instead - the very first thing
@ CianwoodCity_EventScript_GladionAutoTrigger does is mark it 1 - makes this
@ fire at most once per visit.
CianwoodCity_OnFrame::
	map_script_2 VAR_TEMP_1, 0, CianwoodCity_EventScript_GladionAutoTrigger
	.2byte 0

CianwoodCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CIANWOOD_CITY
	callnative SetTimeBasedEncounters
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

CianwoodCity_EventScript_InitializeSuicune::
	call CianwoodCity_EventScript_ApplyGladionVisibility
	call CianwoodCity_EventScript_ApplyPostGladionVisibility
	goto_if_ge VAR_SUICUNE_ENCOUNTERS, 2, CianwoodCity_EventScript_InitializeNothing
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setrespawn HEAL_LOCATION_CIANWOOD_CITY
	setvar VAR_TEMP_0, 1
	end

CianwoodCity_EventScript_InitializeNothing::
	setvar VAR_TEMP_0, 1
	end

@ Runs on MAP_SCRIPT_ON_LOAD (via InitializeSuicune above), which is BEFORE
@ this map's object events spawn (TrySpawnObjectEvents). Gladion/Type: Null
@ share one map.json template flag, FLAG_HIDE_CIANWOOD_GLADION, which is
@ the only thing the object-spawn system actually checks on every
@ camera-triggered (re)spawn attempt (UpdateObjectEventsForCameraUpdate ->
@ TrySpawnObjectEvents, src/event_object_movement.c) - a script that just
@ removeobjects them once is not enough, because that same camera system
@ respawns any in-view object whose template flag is clear every time it
@ scrolls back into view, independent of anything a script already did.
@ FLAG_HIDE_CIANWOOD_GLADION itself carries no meaning - it is recomputed
@ here, every load, straight from FLAG_DEFEATED_CIANWOOD_GYM (set in
@ CianwoodGym_EventScript_ChuckVictory) and FLAG_RECEIVED_HM_FLY (set once
@ the cutscene actually delivers the HM), which remain the only real source
@ of truth for whether Gladion is around.
CianwoodCity_EventScript_ApplyGladionVisibility::
	goto_if_unset FLAG_DEFEATED_CIANWOOD_GYM, CianwoodCity_EventScript_ApplyGladionVisibility_Hide
	goto_if_set FLAG_RECEIVED_HM_FLY, CianwoodCity_EventScript_ApplyGladionVisibility_Hide
	clearflag FLAG_HIDE_CIANWOOD_GLADION
	return

CianwoodCity_EventScript_ApplyGladionVisibility_Hide::
	setflag FLAG_HIDE_CIANWOOD_GLADION
	return

@ Runs at most once per visit (see the VAR_TEMP_1 guard above). Gladion/
@ Type: Null's visibility itself is already handled reliably by
@ CianwoodCity_EventScript_ApplyGladionVisibility on every load - this only
@ needs to decide whether to launch the cutscene this visit.
CianwoodCity_EventScript_GladionAutoTrigger::
	setvar VAR_TEMP_1, 1
	goto_if_unset FLAG_DEFEATED_CIANWOOD_GYM, CianwoodCity_EventScript_GladionAutoTrigger_End
	goto_if_set FLAG_RECEIVED_HM_FLY, CianwoodCity_EventScript_GladionAutoTrigger_End
	@ checkitemspace gates before lockall/dialogue: a full bag just skips the
	@ cutscene this visit (Gladion/Type: Null stay visible, per the flag
	@ above) - leaving and re-entering the map retries it, instead of the
	@ game replaying the whole cutscene mid-visit.
	checkitemspace ITEM_HM_FLY, 1
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_GladionAutoTrigger_End
	lockall
	call CianwoodCity_EventScript_HideDecorativesForGladionScene
	goto CianwoodCity_EventScript_GladionIntro

CianwoodCity_EventScript_GladionAutoTrigger_End::
	end

@ Hides every other Cianwood City decorative for the duration of the scene
@ (only Gladion, Type: Null and Chuck's wife stay), both for the "all NPCs
@ gone during the cutscene" staging and to free object-event slots. Only
@ touches objects whose map.json flag is the dummy "0" - removeobject also
@ FlagSets whatever flag is wired to the object it removes
@ (RemoveObjectEventByLocalIdAndMap in src/event_object_movement.c), so this
@ deliberately excludes Suicune/Eusine (FLAG_HIDE_CIANWOOD_SUICUNE/EUSINE -
@ their own encounter state), the two breakable rocks (FLAG_TEMP_1/2 -
@ generic scratch flags reused all over the ROM), the Engineer
@ (FLAG_AMPHAROS_HEALED - an unrelated achievement flag) and the item ball
@ (FLAG_CIANWOOD_GOLDEN_BOTTLECAP - "already picked up"), and Cameron
@ (FLAG_HIDE_CAMERON - his own quest state). Removing any of those would
@ silently set a flag that means something else entirely. The objects
@ below have no named LOCALID constant in map.json, so they're addressed by
@ their plain local id (matches the numbering in CianwoodCity_ObjectEvents).
CianwoodCity_EventScript_HideDecorativesForGladionScene::
	removeobject LOCALID_CIANWOOD_YOUNGSTER
	removeobject LOCALID_CIANWOOD_BATTLEGIRL
	removeobject 3  @ Fat Man (PokefanM)
	removeobject 7  @ Staryu
	removeobject 8  @ Staryu
	removeobject 9  @ Staryu
	removeobject 10 @ Binacle
	removeobject 11 @ Crabrawler
	removeobject 12 @ Geodude
	removeobject 13 @ Geodude
	removeobject 14 @ Pidgeotto
	return

CianwoodCity_EventScript_RestoreDecorativesAfterGladionScene::
	addobject LOCALID_CIANWOOD_YOUNGSTER
	addobject LOCALID_CIANWOOD_BATTLEGIRL
	addobject 3
	addobject 7
	addobject 8
	addobject 9
	addobject 10
	addobject 11
	addobject 12
	addobject 13
	addobject 14
	return

CianwoodCity_EventScript_Test::
	lock
	random 2
	call_if_eq VAR_RESULT, 1, EventScript_RockSmashHeartscale
	release
	end

@ FLAG_RECEIVED_HM_FLY is the single source of truth here (see the Gladion
@ cutscene below, and CianwoodCity_EventScript_ApplyGladionVisibility): this
@ no longer hands out the HM itself during the normal story window. She now
@ points the player to Gladion instead, and only falls back to delivering
@ the HM herself if the player reaches her after the Gladion/Type: Null
@ window has already closed (FLAG_SYS_GAME_CLEAR, used here as the
@ "post-League" guard since there is no dedicated post-Blackthorn flag yet;
@ see docs/GLADION_CIANWOOD_REFINAMENTO_COMPLETO_V3.md section 7) - Gladion's
@ own auto-trigger already covers every other visit, so this is mostly a
@ defensive backstop at this point.
CianwoodCity_EventScript_ChucksWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLY, CianwoodCity_EventScript_ChucksWifeAlreadyHasFly
	goto_if_unset FLAG_BADGE05_GET, CianwoodCity_EventScript_ChucksWifeBeforeBadge
	goto_if_set FLAG_SYS_GAME_CLEAR, CianwoodCity_EventScript_ChucksWifeLateDelivery
	msgbox CianwoodCity_Text_ChucksWifePointToGladion, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeBeforeBadge::
	msgbox CianwoodCity_Text_ChucksWifeEasierToFly, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_ChucksWifeBeatChuck, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeAlreadyHasFly::
	msgbox CianwoodCity_Text_ChucksWifeChubby, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Late/deferred path only (player never crossed paths with Gladion before
@ finishing the League): same delivery contract as Gladion's own
@ (checkitemspace first, reconcile if the HM is somehow already present,
@ confirm giveitem's result before marking FLAG_RECEIVED_HM_FLY complete),
@ just without the choreography since Gladion/Type: Null are not part of
@ this branch.
CianwoodCity_EventScript_ChucksWifeLateDelivery::
	checkitemspace ITEM_HM_FLY, 1
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_ChucksWifeLateDeliveryFailed
	checkitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_ChucksWifeLateDeliveryReconcile
	msgbox CianwoodCity_Text_ChucksWifeGiveHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_ChucksWifeLateDeliveryFailed
CianwoodCity_EventScript_ChucksWifeLateDeliveryReconcile::
	setflag FLAG_RECEIVED_HM_FLY
	msgbox CianwoodCity_Text_ChucksWifeFlySpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeLateDeliveryFailed::
	msgbox CianwoodCity_Text_ChucksWifeLateDeliveryFailed, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_ChucksWifeEasierToFly:
	.string "You crossed the sea to get here?\p"
	.string "That must have been hard.\p"
	.string "It would be much easier if your\n"
	.string "Pokémon knew how to Fly...$"

CianwoodCity_Text_ChucksWifeBeatChuck:
	.string "But you can't use Fly without this\n"
	.string "city's Gym Badge.\p"
	.string "If you beat the Gym Leader here,\n"
	.string "come see me.\p"
	.string "I'll have a nice gift for you.$"

CianwoodCity_Text_ChucksWifeGiveHM:
	.string "That's Cianwood's Gym Badge!\p"
	.string "Then you should take this HM.$"

CianwoodCity_Text_ChucksWifeFlySpeech:
	.string "Teach Fly to your Pokémon.\p"
	.string "You will be able to Fly instantly\n"
	.string "to anywhere you have visited.$"

CianwoodCity_Text_ChucksWifeChubby:
	.string "My husband lost to you, so he needs\n"
	.string "to train harder.\p"
	.string "That's good, since he was getting\n"
	.string "a little chubby.$"

CianwoodCity_Text_ChucksWifePointToGladion:
	.string "Gladion has something for you.\n"
	.string "Go and speak to him.$"

CianwoodCity_Text_ChucksWifeLateDeliveryFailed:
	.string "Give me a moment.\n"
	.string "Come back in a little while.$"

@ ---------------------------------------------------------------------------
@ Gladion at Cianwood: forced automatic Fly handoff right after Chuck.
@ Entered only from CianwoodCity_EventScript_GladionAutoTrigger above (see
@ CianwoodCity_OnFrame) - there is no player-triggered entry point anymore,
@ so there is no yes/no about starting it and no way to walk away mid-scene
@ (lockall is already active by the time this runs).
@
@ VAR_TEMP_2/3 are scratch for this single visit only (CianwoodCity_EventScript_CityEnter
@ zeroes them on every entry, so no other script reusing these slots can leak in):
@   VAR_TEMP_2 - battle outcome, copied right after GetBattleOutcome
@   VAR_TEMP_3 - B_FLAG_NO_WHITEOUT state from before the battle, to restore exactly
@
@ Anchors used below (see section 5 of the doc): Gladion (17,47), Type: Null
@ (17,48), Chuck's wife (18,47, already her existing position). Movement
@ scripts here are a first pass, not confirmed against the live collision map.
@ ---------------------------------------------------------------------------

CianwoodCity_EventScript_GladionIntro::
	turnobject LOCALID_CIANWOOD_GLADION, DIR_EAST
	turnobject LOCALID_CIANWOOD_CHUCKSWIFE, DIR_WEST
	msgbox CianwoodCity_Text_WifeAllThisWay, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_WifeTakeFly, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionNotInHurry, MSGBOX_DEFAULT
	closemessage

	playse SE_PIN
	applymovement LOCALID_CIANWOOD_TYPENULL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_CIANWOOD_GLADION, Common_Movement_ExclamationMark
	waitmovement 0
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE

	@ Player steps off the door tile down into the plaza, to (15,46).
	applymovement OBJ_EVENT_ID_PLAYER, CianwoodCity_Movement_PlayerStepForward
	waitmovement 0

	@ Both walk over together (queued before one waitmovement, so they move
	@ side by side instead of one after the other): Gladion (17,47) ->
	@ (15,47), Type: Null (17,48) -> (14,47), ending up on Gladion's west,
	@ same row. Step-by-step they never want the same tile at the same time.
	applymovement LOCALID_CIANWOOD_GLADION, CianwoodCity_Movement_GladionToPlayer
	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullToGladionsWest
	waitmovement 0
	@ The player is NORTH of both of them (they came up from the beach side,
	@ the player came down out of the gym door) - so facing the player is
	@ DIR_NORTH. Facing south here is what had them staring away from the
	@ player the whole scene.
	turnobject LOCALID_CIANWOOD_GLADION, DIR_NORTH
	turnobject LOCALID_CIANWOOD_TYPENULL, DIR_NORTH
	msgbox CianwoodCity_Text_GladionLookWhoItIs, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionBeatChuck, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_WifeLostTrackOfTime, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_WifeBroughtHM, MSGBOX_DEFAULT
	closemessage

	@ She heads inside to check on Chuck. The door tile (15,44) is solid in
	@ the collision map and NPCs can't trigger a real door warp anyway, so
	@ she walks to (15,45) directly below it, turns to face the door
	@ (face_up, end of her movement), and the fade covers her vanishing -
	@ same trick already used for Erika in CeladonCity/scripts.inc.
	turnobject LOCALID_CIANWOOD_CHUCKSWIFE, DIR_WEST
	delay 12
	applymovement LOCALID_CIANWOOD_CHUCKSWIFE, CianwoodCity_Movement_ChucksWifeToGymDoor
	waitmovement 0
	delay 12
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CIANWOOD_CHUCKSWIFE
	fadescreenswapbuffers FADE_FROM_BLACK

	msgbox CianwoodCity_Text_GladionLillieGoldenrod, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionFlowersBattle, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionEnjoyingHere, MSGBOX_DEFAULT
	closemessage

	msgbox CianwoodCity_Text_GladionSoAmI, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionLookingForTrainers, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionWholeMorning, MSGBOX_DEFAULT
	closemessage

	@ Talking about Type: Null now (west of him) - Type: Null looks back up
	@ at Gladion (east) while he does, then both settle back on the player.
	turnobject LOCALID_CIANWOOD_GLADION, DIR_WEST
	turnobject LOCALID_CIANWOOD_TYPENULL, DIR_EAST
	msgbox CianwoodCity_Text_GladionEveryTimeWater, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionThenFollowing, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionStayedLonger, MSGBOX_DEFAULT
	closemessage

	delay 24
	turnobject LOCALID_CIANWOOD_GLADION, DIR_NORTH
	turnobject LOCALID_CIANWOOD_TYPENULL, DIR_NORTH
	msgbox CianwoodCity_Text_GladionGoodMorning, MSGBOX_DEFAULT
	closemessage
	call CianwoodCity_EventScript_CosmogComment

	goto CianwoodCity_EventScript_GladionChallenge

@ No choice offered: the fight is forced (see the auto-trigger this is
@ entered from). CianwoodCity_Text_GladionBattleQuestion is shown as a
@ statement, not an actual MSGBOX_YESNO prompt.
CianwoodCity_EventScript_GladionChallenge::
	@ Asking Type: Null if he remembers you - looks west at him first, then
	@ back at you (DIR_NORTH) for the rest. Type: Null perks up in place
	@ rather than walking anywhere, so he stays on Gladion's west for the
	@ whole conversation.
	turnobject LOCALID_CIANWOOD_GLADION, DIR_WEST
	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullPerkUp
	waitmovement 0
	msgbox CianwoodCity_Text_GladionRememberTrainer, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionWantToFindOut, MSGBOX_DEFAULT
	turnobject LOCALID_CIANWOOD_GLADION, DIR_NORTH
	msgbox CianwoodCity_Text_GladionRematchBeforeLeave, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionFlyEitherWay, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionBattleQuestion, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionFirstHeal, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionReadyDontHoldBack, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal

	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_3, VAR_RESULT
	setflag B_FLAG_NO_WHITEOUT
	setvar VAR_LAST_TALKED, LOCALID_CIANWOOD_GLADION
	trainerbattle_no_intro TRAINER_GLADION_CIANWOOD, CianwoodCity_Text_GladionDefeatedByPlayer
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_3, TRUE, CianwoodCity_EventScript_GladionKeepWhiteoutOff
	clearflag B_FLAG_NO_WHITEOUT
CianwoodCity_EventScript_GladionKeepWhiteoutOff::
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE

	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, CianwoodCity_EventScript_GladionPlayerWon
	goto_if_eq VAR_TEMP_2, B_OUTCOME_LOST, CianwoodCity_EventScript_GladionPlayerLost
	goto_if_eq VAR_TEMP_2, B_OUTCOME_DREW, CianwoodCity_EventScript_GladionDraw
	goto_if_eq VAR_TEMP_2, B_OUTCOME_FORFEITED, CianwoodCity_EventScript_GladionForfeit
	goto CianwoodCity_EventScript_GladionUnexpectedOutcome

@ B_OUTCOME_WON: Gladion's own line (CianwoodCity_Text_GladionDefeatedByPlayer)
@ already played automatically when his last Pokémon fainted.
CianwoodCity_EventScript_GladionPlayerWon::
	turnobject LOCALID_CIANWOOD_GLADION, DIR_WEST
	turnobject LOCALID_CIANWOOD_TYPENULL, DIR_EAST
	msgbox CianwoodCity_Text_GladionNeedAnotherPlan, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionYouNoticedToo, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

CianwoodCity_EventScript_GladionPlayerLost::
	msgbox CianwoodCity_Text_GladionThatOneWasOurs, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionMadeUsWorkForIt, MSGBOX_DEFAULT
	turnobject LOCALID_CIANWOOD_GLADION, DIR_WEST
	turnobject LOCALID_CIANWOOD_TYPENULL, DIR_EAST
	msgbox CianwoodCity_Text_GladionStayedFocused, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionGoodWork, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

CianwoodCity_EventScript_GladionDraw::
	msgbox CianwoodCity_Text_GladionDraw, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

CianwoodCity_EventScript_GladionForfeit::
	msgbox CianwoodCity_Text_GladionForfeit, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

@ Not a real outcome of a local trainer battle. Still concludes the event
@ and delivers Fly (same policy as DragonsDen_Shrine and the Violet City
@ Pokemon Center), so the player is never sent back to re-battle Gladion.
@ GladionDeliver heals the party and restores the hidden NPCs at the end.
CianwoodCity_EventScript_GladionUnexpectedOutcome::
	msgbox CianwoodCity_Text_GladionUnexpectedOutcome, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

CianwoodCity_EventScript_GladionDeliver::
	call Common_EventScript_OutOfCenterPartyHeal
	@ Every outcome branch above (Won/Lost/Draw/Forfeit/UnexpectedOutcome)
	@ funnels in here; Won/Lost leave them facing each other, so put both
	@ back on the player (north of them) before talking to them.
	turnobject LOCALID_CIANWOOD_GLADION, DIR_NORTH
	turnobject LOCALID_CIANWOOD_TYPENULL, DIR_NORTH
	msgbox CianwoodCity_Text_GladionHereHMFromWife, MSGBOX_DEFAULT
	checkitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_GladionItemAlreadyPresent
	giveitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_GladionGiveItemFailed
CianwoodCity_EventScript_GladionItemAlreadyPresent::
	setflag FLAG_RECEIVED_HM_FLY
	msgbox CianwoodCity_Text_GladionFlyMakesTripEasier, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionTellLillie, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionHeardWholeStory, MSGBOX_DEFAULT
	closemessage

	@ Type: Null walks ahead onto column 16 (the only one that stays clear
	@ going south - 14 and 15 are both walled off at y=50/51) and looks
	@ back. Gladion watches him go (south-west of Gladion now, but DIR_SOUTH
	@ reads fine for "watching him walk off"), then turns back to the player.
	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullFirstStep
	waitmovement 0
	turnobject LOCALID_CIANWOOD_GLADION, DIR_SOUTH
	delay 20
	msgbox CianwoodCity_Text_GladionMadeUpYourMind, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionImComing, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_CIANWOOD_GLADION, DIR_NORTH
	msgbox CianwoodCity_Text_GladionSeeYouAround, MSGBOX_DEFAULT
	closemessage

	playbgm MUS_HG_RIVAL_EXIT, TRUE
	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullContinue
	waitmovement 0
	applymovement LOCALID_CIANWOOD_GLADION, CianwoodCity_Movement_GladionFollow
	waitmovement 0
	removeobject LOCALID_CIANWOOD_TYPENULL
	removeobject LOCALID_CIANWOOD_GLADION
	@ Mini dark fade once they're actually gone, before the city (Chuck's
	@ wife included - she went inside to check on him earlier in this same
	@ scene, see the fade in GladionIntro) comes back.
	fadescreenswapbuffers FADE_TO_BLACK
	delay 30
	addobject LOCALID_CIANWOOD_CHUCKSWIFE
	fadescreenswapbuffers FADE_FROM_BLACK
	call CianwoodCity_EventScript_RestoreDecorativesAfterGladionScene
	fadedefaultbgm
	releaseall
	end

@ Should not happen: checkitemspace already confirmed room before the
@ battle. If it fails anyway, FLAG_RECEIVED_HM_FLY stays unset, so the
@ on-frame trigger (CianwoodCity_EventScript_GladionAutoTrigger) just
@ replays the whole cutscene the next time checkitemspace passes.
CianwoodCity_EventScript_GladionGiveItemFailed::
	msgbox CianwoodCity_Text_GladionDeliveryFailed, MSGBOX_DEFAULT
	closemessage
	call CianwoodCity_EventScript_RestoreDecorativesAfterGladionScene
	fadedefaultbgm
	releaseall
	end

@ Every movement below is checked against data/layouts/CianwoodCity/map.bin.
@ Collision there is ONE bit (bit 11, MAPGRID_COLLISION_MASK 0x0800 in
@ include/global.fieldmap.h) - metatile ids take bits 0-10 - and any
@ nonzero value is impassable (GetCollisionFlagsAtCoords). The relevant
@ part of the plaza, with # = blocked:
@
@        x=12 13 14 15 16 17 18
@   y=44   .  .  #  #  #  #  .     gym facade; the door tile (15,44) itself
@   y=45   .  .  .  .  .  .  .     is solid, NPCs can't stand on or cross it
@   y=46   .  .  .  .  .  .  .
@   y=47   .  .  .  .  .  .  .
@   y=48   .  .  .  .  .  .  .
@   y=49   #  #  .  .  .  .  .
@   y=50   #  #  #  #  .  .  .     going south, only column 16+ stays open
@   y=51   #  #  #  #  .  .  .
@
@ Layout of the scene: the player comes DOWN out of the gym door, so the
@ player ends up NORTH of everyone else - facing the player is DIR_NORTH,
@ not DIR_SOUTH.
@   player      (15,45) -> (15,46)
@   Gladion     (17,47) -> (15,47)
@   Type: Null  (17,48) -> (14,47), on Gladion's west, same row
@   wife        (18,47) -> (15,45), below the door, facing up into it

@ One step further into the plaza, off the door tile.
CianwoodCity_Movement_PlayerStepForward:
	walk_down
	step_end

@ Gladion (17,47) -> (15,47).
CianwoodCity_Movement_GladionToPlayer:
	walk_left
	walk_left
	step_end

@ Type: Null (17,48) -> (14,47). Queued together with GladionToPlayer above
@ so they cross the plaza side by side. Tile by tile they never want the
@ same square at the same time: Gladion takes (16,47) then (15,47) while
@ Type: Null takes (16,48) then (15,48), and Type: Null's last two steps
@ happen after Gladion has already stopped.
CianwoodCity_Movement_TypeNullToGladionsWest:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ (18,47) -> (15,45), directly below the door, then faces up into it.
@ Routed over row 47 -> 45 so she never crosses Gladion (15,47),
@ Type: Null (14,47) or the player (15,46).
CianwoodCity_Movement_ChucksWifeToGymDoor:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	face_up
	step_end

@ Type: Null perks up without leaving Gladion's west - no position change,
@ so nothing can collide and he stays put for the whole conversation.
CianwoodCity_Movement_TypeNullPerkUp:
	walk_in_place_faster_up
	face_up
	step_end

@ Farewell. Type: Null (14,47) walks ahead and shifts onto column 16, the
@ only one that stays clear heading south (14 and 15 are walled off at
@ y=50/51), then looks back: (14,48) -> (15,48) -> (16,48), face up.
CianwoodCity_Movement_TypeNullFirstStep:
	walk_down
	walk_right
	walk_right
	face_up
	step_end

@ (16,48) -> (16,52), straight down the clear column.
CianwoodCity_Movement_TypeNullContinue:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Gladion (15,47) -> (16,50), following him down the same column. Runs
@ after Type: Null has already finished, so the column is clear behind him;
@ stops two tiles short of Type: Null, which is fine - both get
@ removeobject'd immediately after.
CianwoodCity_Movement_GladionFollow:
	walk_right
	walk_down
	walk_down
	walk_down
	step_end

CianwoodCity_Text_WifeAllThisWay:
	.string "Chuck's wife: You came all this\n"
	.string "way, and you're going back by\l"
	.string "sea?$"

CianwoodCity_Text_WifeTakeFly:
	.string "Take Fly. Even someone who\n"
	.string "enjoys walking needs a rest.$"

CianwoodCity_Text_GladionNotInHurry:
	.string "{SPEAKER NAME_GLADION}I'm not in a hurry.$"

CianwoodCity_Text_GladionLookWhoItIs:
	.string "{SPEAKER NAME_GLADION}Look who it is.$"

CianwoodCity_Text_GladionBeatChuck:
	.string "You beat Chuck? He doesn't\n"
	.string "usually cut a training session\l"
	.string "short.$"

CianwoodCity_Text_WifeLostTrackOfTime:
	.string "Chuck's wife: And then he says\n"
	.string "he lost track of time!$"

CianwoodCity_Text_WifeBroughtHM:
	.string "I brought an HM for you, too.\n"
	.string "Gladion, would you pass it\l"
	.string "along? I'll see if my husband\l"
	.string "will finally take a break.$"

CianwoodCity_Text_GladionLillieGoldenrod:
	.string "{SPEAKER NAME_GLADION}Lillie told me about\n"
	.string "Goldenrod.$"

CianwoodCity_Text_GladionFlowersBattle:
	.string "First the battle. Then the\n"
	.string "flowers. Then back to the\l"
	.string "battle.$"

CianwoodCity_Text_GladionEnjoyingHere:
	.string "She's enjoying it here.$"

CianwoodCity_Text_GladionSoAmI:
	.string "{SPEAKER NAME_GLADION}So am I.$"

CianwoodCity_Text_GladionLookingForTrainers:
	.string "I thought I'd spend my time in\n"
	.string "Johto looking for the strongest\l"
	.string "Trainers.$"

CianwoodCity_Text_GladionWholeMorning:
	.string "Instead, we spent a whole\n"
	.string "morning on this beach. He was\l"
	.string "still getting used to the\l"
	.string "waves.$"

CianwoodCity_Text_GladionEveryTimeWater:
	.string "Every time the water came near\n"
	.string "him, he backed away.$"

CianwoodCity_Text_GladionThenFollowing:
	.string "Then he started following it\n"
	.string "back.$"

CianwoodCity_Text_GladionStayedLonger:
	.string "We stayed longer than I\n"
	.string "planned.$"

CianwoodCity_Text_GladionGoodMorning:
	.string "It was a good morning.$"

CianwoodCity_Text_GladionRememberTrainer:
	.string "{SPEAKER NAME_GLADION}You remember this\n"
	.string "Trainer?$"

CianwoodCity_Text_GladionWantToFindOut:
	.string "Yeah. I want to find out, too.$"

CianwoodCity_Text_GladionRematchBeforeLeave:
	.string "A rematch before you leave?$"

CianwoodCity_Text_GladionFlyEitherWay:
	.string "Fly is yours either way. The\n"
	.string "battle is something I'm asking\l"
	.string "for.$"

CianwoodCity_Text_GladionBattleQuestion:
	.string "Let's battle.$"

CianwoodCity_Text_GladionFirstHeal:
	.string "First, let's take care of your\n"
	.string "Pokémon. I want you at your\l"
	.string "best.$"

CianwoodCity_Text_GladionReadyDontHoldBack:
	.string "Ready. Don't hold back.$"

CianwoodCity_Text_GladionDefeatedByPlayer:
	.string "You've changed since Violet.\p"
	.string "I looked for the same openings.\n"
	.string "They weren't there anymore.$"

CianwoodCity_Text_GladionNeedAnotherPlan:
	.string "We'll need another plan.$"

CianwoodCity_Text_GladionYouNoticedToo:
	.string "You noticed it too, didn't you?$"

CianwoodCity_Text_GladionThatOneWasOurs:
	.string "That one was ours.$"

CianwoodCity_Text_GladionMadeUsWorkForIt:
	.string "But you made us work for it.$"

CianwoodCity_Text_GladionStayedFocused:
	.string "You stayed focused. Let's keep\n"
	.string "working on that.$"

CianwoodCity_Text_GladionGoodWork:
	.string "Good work.$"

CianwoodCity_Text_GladionDraw:
	.string "That was close for both of us.\n"
	.string "Let's look after our Pokémon.$"

CianwoodCity_Text_GladionForfeit:
	.string "All right. We can stop. I'll\n"
	.string "take care of your Pokémon.$"

CianwoodCity_Text_GladionUnexpectedOutcome:
	.string "That didn't end cleanly. Let me\n"
	.string "take care of your Pokémon.$"

CianwoodCity_Text_GladionHereHMFromWife:
	.string "{SPEAKER NAME_GLADION}Here. The HM she left\n"
	.string "for you.$"

CianwoodCity_Text_GladionFlyMakesTripEasier:
	.string "Fly. It'll make the trip back\n"
	.string "easier.$"

CianwoodCity_Text_GladionTellLillie:
	.string "If you see Lillie, tell her\n"
	.string "we're doing fine.$"

CianwoodCity_Text_GladionHeardWholeStory:
	.string "And that I heard the whole\n"
	.string "story about the battle.$"

CianwoodCity_Text_GladionMadeUpYourMind:
	.string "Made up your mind?$"

CianwoodCity_Text_GladionImComing:
	.string "I'm coming.$"

CianwoodCity_Text_GladionSeeYouAround:
	.string "See you around, {PLAYER}.$"

CianwoodCity_Text_GladionDeliveryFailed:
	.string "Give me a moment.\n"
	.string "Come back in a little while.$"

CianwoodCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Youngster:
	.string "If you use Fly, you can get back\n"
	.string "to Olivine instantly.$"

CianwoodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokefanM:
	.string "Boulders to the north of town can\n"
	.string "be crushed.\p"
	.string "They may be hiding something.\p"
	.string "Your Pokémon could use Rock Smash\n"
	.string "to break them.$"

CianwoodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Lass:
	.string "Chuck, the Gym Leader, spars with\n"
	.string "his fighting Pokémon.$"

CianwoodCity_EventScript_SuicuneTrigger::
	lock
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune2
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune3
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	delay 30
	playbgm MUS_HG_EUSINE, TRUE
	clearflag FLAG_HIDE_CIANWOOD_EUSINE
	addobject LOCALID_CIANWOOD_EUSINE
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine1
	waitmovement 0
	delay 55
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine2
	waitmovement 0 
	createfieldmugshot MUGSHOT_EUSINE
	msgbox CianwoodCity_Text_EusineSuicune, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_EUSINE, CianwoodCity_Text_EusineBeaten
	playbgm MUS_HG_EUSINE, TRUE
	createfieldmugshot MUGSHOT_EUSINE
	msgbox CianwoodCity_Text_EusineAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine3
	waitmovement 0
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setflag FLAG_HIDE_CIANWOOD_SUICUNE
	removeobject LOCALID_CIANWOOD_SUICUNE
	removeobject LOCALID_CIANWOOD_EUSINE
	setvar VAR_SUICUNE_ENCOUNTERS, 2
	setvar VAR_CIANWOOD_CITY_STATE, 2
	fadedefaultbgm
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, CianwoodCity_EventScript_DoneJohtoSuicune
	release
	end

CianwoodCity_EventScript_DoneJohtoSuicune::
	setvar VAR_SUICUNE_ENCOUNTERS, 3
	return

CianwoodCity_Movement_Suicune1:
	jump_in_place_right_left
	jump_in_place_right_left
	face_down
	step_end

CianwoodCity_Movement_Suicune2:
	jump_down
	jump_2_down
	jump_right
	face_up
	step_end

CianwoodCity_Movement_Suicune3:
	jump_2_down
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

CianwoodCity_Movement_Eusine1:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_right
	step_end

CianwoodCity_Movement_Eusine2:
	face_up
	walk_up
	walk_up
	step_end

CianwoodCity_Movement_Eusine3:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

CianwoodCity_Text_EusineSuicune:
	.string "Eusine: Yo, {PLAYER}.\p"
	.string "Wasn't that Suicune just now?\p"
	.string "I only caught a quick glimpse, but\n"
	.string "I thought I saw Suicune running on\l"
	.string "the waves.\p"
	.string "Suicune is beautiful and grand.\p"
	.string "And it races through towns and\n"
	.string "roads at simply awesome speeds.\p"
	.string "It's wonderful…\p"
	.string "I want to see Suicune up close…\p"
	.string "I've decided.\p"
	.string "I'll battle you as a trainer to\n"
	.string "earn Suicune's respect!\p"
	.string "Come on, {PLAYER}. Let's battle now!$"

CianwoodCity_Text_EusineBeaten:
	.string "I hate to admit it, but you win.$"

CianwoodCity_Text_EusineAfter:
	.string "You're amazing, {PLAYER}!\p"
	.string "No wonder Pokémon gravitate to you.\p"
	.string "I get it now.\p"
	.string "I'm going to keep searching for\n"
	.string "Suicune.\p"
	.string "I'm sure we'll see each other again.\p"
	.string "See you around!$"

CianwoodCity_EventScript_CitySign::
	lock
	msgbox CianwoodCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_Sign:
	.string "Cianwood City\p"
	.string "A Port Surrounded by Rough Seas$"

CianwoodCity_EventScript_GymSign::
	lock
	msgbox CianwoodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_GymSign:
	.string "Cianwood City Pokémon Gym\p"
	.string "Leader: Chuck\p"
	.string "His Roaring Fists Do the Talking$"

CianwoodCity_EventScript_Pharmacy::
	lock
	msgbox CianwoodCity_Text_PharmacySign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_PharmacySign:
	.string "500 Years of Tradition\p"
	.string "Cianwood City Pharmacy\p"
	.string "We Await Your Medicinal Queries$"

CianwoodCity_EventScript_CaveSign::
	lock
	msgbox CianwoodCity_Text_Safari, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_EventScript_Engineer::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Engineer, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Safari:
	.string "Cliff Edge Cave\n"
	.string "Road to the Safari Zone.$"

CianwoodCity_Text_Engineer:
	.string "This path is under construction.\n"
	.string "We're getting the new Safari Zone\l"
	.string "up and running!$"

@ Optional Sun & Moon callback: Gladion recognises Cosmog from Alola and learns what was in the egg he handed over (he never knew).
@ Reacts to the first non-egg Cosmog/Cosmoem/Solgaleo/Lunala in the party
@ (CheckMysteryEggPokemon, the special Elm's Eviolite scene uses). Nothing
@ else changes: no flag, no var; VAR_RESULT is free at every call site.
CianwoodCity_EventScript_CosmogComment::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	goto_if_eq VAR_RESULT, SPECIES_NONE, CianwoodCity_EventScript_CosmogCommentEnd
	bufferspeciesname STR_VAR_1, VAR_RESULT
	applymovement LOCALID_CIANWOOD_TYPENULL, Common_Movement_ExclamationMark
	waitmovement LOCALID_CIANWOOD_TYPENULL
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, CianwoodCity_EventScript_CosmogCommentCosmog
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, CianwoodCity_EventScript_CosmogCommentCosmoem
	msgbox CianwoodCity_Text_CosmogLegend, MSGBOX_DEFAULT
	closemessage
	return

CianwoodCity_EventScript_CosmogCommentCosmog::
	msgbox CianwoodCity_Text_Cosmog, MSGBOX_DEFAULT
	closemessage
	return

CianwoodCity_EventScript_CosmogCommentCosmoem::
	msgbox CianwoodCity_Text_CosmogCosmoem, MSGBOX_DEFAULT
	closemessage
	return

CianwoodCity_EventScript_CosmogCommentEnd::
	return

CianwoodCity_Text_Cosmog:
	.string "{SPEAKER NAME_GLADION}…Wait. That's a\n"
	.string "Cosmog.\p"
	.string "So that's what was in the egg.\p"
	.string "Lillie had one, in Alola. It got\n"
	.string "her into more trouble than I\l"
	.string "can count.\p"
	.string "Got her out of some, too.\p"
	.string "Keep it close. They wander.$"

CianwoodCity_Text_CosmogCosmoem:
	.string "{SPEAKER NAME_GLADION}That's a Cosmoem.\n"
	.string "So that's what was in the egg.\p"
	.string "It's not asleep. It's building\n"
	.string "itself.\p"
	.string "Don't rush it.$"

CianwoodCity_Text_CosmogLegend:
	.string "{SPEAKER NAME_GLADION}…A {STR_VAR_1}.\n"
	.string "From that egg.\p"
	.string "Type: Null, look. Somebody\n"
	.string "grew up faster than you.\p"
	.string "Lillie is going to want to see\n"
	.string "this.$"

@ ============================================================================
@ Post-game Gladion (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.8).
@ A NEW pair of objects beside the farewell tile, on FLAG_TEMP_3 - not
@ FLAG_TEMP_1/2, which are this map's two breakable rocks, and not the old
@ FLAG_HIDE_CIANWOOD_GLADION pair, whose flag belongs to the pre-League
@ campaign.
@ Tuesday, Wednesday and Saturday, and only from state 16 on. Same closed window
@ as everywhere else in this event: a goto_if_ge alone would put him on this
@ beach from New Game.
@ The Silvally shares his flag and nothing here ever removeobjects either of
@ them, so they appear and vanish together.
@ ============================================================================
CianwoodCity_EventScript_ApplyPostGladionVisibility::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CianwoodCity_EventScript_HidePostGladion
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CianwoodCity_EventScript_ShowPostGladion
	goto_if_eq VAR_RESULT, WEEKDAY_WED, CianwoodCity_EventScript_ShowPostGladion
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CianwoodCity_EventScript_ShowPostGladion
CianwoodCity_EventScript_HidePostGladion::
	setflag FLAG_TEMP_3
	return
CianwoodCity_EventScript_ShowPostGladion::
	clearflag FLAG_TEMP_3
	return

@ One box, then the rematch if today's daily flag is still clear. A normal
@ trainer battle: no B_FLAG_NO_WHITEOUT. The daily flag is set BEFORE the battle,
@ because after it is unreachable on a loss.
CianwoodCity_EventScript_PostGladion::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PostGladion, MSGBOX_DEFAULT
	closemessage
	goto_if_set FLAG_DAILY_REMATCH_GLADION, CianwoodCity_EventScript_PostGladionDone
	msgbox CianwoodCity_Text_PostGladionRematchAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CianwoodCity_EventScript_PostGladionNo
	setflag FLAG_DAILY_REMATCH_GLADION
	trainerbattle_no_intro TRAINER_GLADION_POSTGAME, CianwoodCity_Text_PostGladionBeaten
	msgbox CianwoodCity_Text_PostGladionAfter, MSGBOX_DEFAULT
	release
	end

CianwoodCity_EventScript_PostGladionNo::
	msgbox CianwoodCity_Text_PostGladionRematchNo, MSGBOX_DEFAULT
	release
	end

CianwoodCity_EventScript_PostGladionDone::
	msgbox CianwoodCity_Text_PostGladionDoneToday, MSGBOX_DEFAULT
	release
	end

CianwoodCity_Text_PostGladion:
	.string "{SPEAKER NAME_GLADION}You found me.\p"
	.string "This is where I told you I was going.\n"
	.string "Three cities ago, on this beach, I said I\l"
	.string "was going to train here until I was\l"
	.string "worth something in a fight. You\l"
	.string "probably don't remember.\p"
	.string "I trained here. Then I got called to\n"
	.string "Blackthorn, and then I spent four\l"
	.string "cities watching you do the actual work.\l"
	.string "So I came back and started over.$"

@ the YES/NO
CianwoodCity_Text_PostGladionRematchAsk:
	.string "{SPEAKER NAME_GLADION}You know why you're here.\p"
	.string "Every time we've done this, one of us\n"
	.string "needed something. An egg. A HM. A road. A\l"
	.string "city that was on fire.\p"
	.string "Nobody needs anything today. That's\n"
	.string "the only kind of fight I've never had\l"
	.string "with you. Ready?$"

CianwoodCity_Text_PostGladionRematchNo:
	.string "{SPEAKER NAME_GLADION}Then go and do whatever it is you came\n"
	.string "to Cianwood for.\p"
	.string "I'm not going anywhere. That's rather\n"
	.string "the point of this place.$"

@ trainer defeat text
CianwoodCity_Text_PostGladionBeaten:
	.string "{SPEAKER NAME_GLADION}…Good.\p"
	.string "Do it again tomorrow.$"

CianwoodCity_Text_PostGladionAfter:
	.string "{SPEAKER NAME_GLADION}Silvally wants another one. Silvally is\n"
	.string "not in charge.\p"
	.string "Tomorrow. Go on.$"

CianwoodCity_Text_PostGladionDoneToday:
	.string "{SPEAKER NAME_GLADION}Once a day. I train in between, and that\n"
	.string "only works if there's an in between.$"
