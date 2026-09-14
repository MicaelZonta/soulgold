CianwoodCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CianwoodCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CianwoodCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, CianwoodCity_EventScript_InitializeSuicune
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

CianwoodCity_RemoveEusine::
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	end

CianwoodCity_OnFrame::
	.2byte 0

@ Fly used to be handed over automatically the first time this map script ran
@ with VAR_GETFLY == 1 (CianwoodCity_EventScript_Flytrigger, now removed).
@ The handoff is manual now, through Gladion (see the Gladion cutscene below),
@ so nothing should fire on its own here anymore.
CianwoodCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CIANWOOD_CITY
	callnative SetTimeBasedEncounters
	setvar VAR_TEMP_1, 0
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

CianwoodCity_EventScript_InitializeSuicune::
	call CianwoodCity_EventScript_ApplyGladionSceneObjects
	goto_if_ge VAR_SUICUNE_ENCOUNTERS, 2, CianwoodCity_EventScript_InitializeNothing
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setrespawn HEAL_LOCATION_CIANWOOD_CITY
	setvar VAR_TEMP_0, 1
	end

CianwoodCity_EventScript_InitializeNothing::
	setvar VAR_TEMP_0, 1
	end

@ Runs on every entry into this map (MAP_SCRIPT_ON_LOAD, via
@ CianwoodCity_EventScript_InitializeSuicune above). Gladion and Type: Null
@ only exist in their map.json template (flag "0", always spawned); this is
@ what actually gates their presence to VAR_GETFLY == 1, by removing them
@ again on every load where that isn't true. While they're around, the
@ Youngster/Battle Girl decoratives are removed instead, so Cianwood's peak
@ object-event count doesn't grow: see docs/GLADION_CIANWOOD_REFINAMENTO_COMPLETO_V3.md
@ section 6. Neither swap needs a new flag: both sides are recomputed here,
@ every load, straight from VAR_GETFLY.
CianwoodCity_EventScript_ApplyGladionSceneObjects::
	goto_if_eq VAR_GETFLY, 1, CianwoodCity_EventScript_ApplyGladionSceneObjects_Active
	removeobject LOCALID_CIANWOOD_GLADION
	removeobject LOCALID_CIANWOOD_TYPENULL
	return

CianwoodCity_EventScript_ApplyGladionSceneObjects_Active::
	removeobject LOCALID_CIANWOOD_YOUNGSTER
	removeobject LOCALID_CIANWOOD_BATTLEGIRL
	return

CianwoodCity_EventScript_Test::
	lock
	random 2
	call_if_eq VAR_RESULT, 1, EventScript_RockSmashHeartscale
	release
	end

@ VAR_GETFLY is the single source of truth here (see the Gladion cutscene
@ below): this no longer hands out the HM itself during the normal story
@ window. GLD-01 (audit finding: this used to give the HM without ever
@ syncing VAR_GETFLY to 2, so the old OnFrame trigger could hand out a
@ second one) is fixed by removing that direct handoff entirely, not by
@ patching it - she now points the player to Gladion instead, and only
@ falls back to delivering the HM herself if the player reaches her after
@ the Gladion/Type: Null window has already closed (FLAG_SYS_GAME_CLEAR,
@ used here as the "post-League" guard since there is no dedicated
@ post-Blackthorn flag yet; see docs/GLADION_CIANWOOD_REFINAMENTO_COMPLETO_V3.md
@ section 7).
CianwoodCity_EventScript_ChucksWife::
	lock
	faceplayer
	goto_if_eq VAR_GETFLY, 2, CianwoodCity_EventScript_ChucksWifeAlreadyHasFly
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
@ confirm giveitem's result before marking VAR_GETFLY complete), just
@ without the choreography since Gladion/Type: Null are not part of this
@ branch.
CianwoodCity_EventScript_ChucksWifeLateDelivery::
	checkitemspace ITEM_HM_FLY, 1
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_ChucksWifeLateDeliveryFailed
	checkitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_ChucksWifeLateDeliveryReconcile
	msgbox CianwoodCity_Text_ChucksWifeGiveHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_ChucksWifeLateDeliveryFailed
CianwoodCity_EventScript_ChucksWifeLateDeliveryReconcile::
	setvar VAR_GETFLY, 2
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
@ Gladion at Cianwood: manual Fly handoff after Chuck.
@ See docs/GLADION_CIANWOOD_REFINAMENTO_COMPLETO_V3.md for the full design.
@
@ Presence: Gladion (LOCALID_CIANWOOD_GLADION) and Type: Null
@ (LOCALID_CIANWOOD_TYPENULL) are gated purely by VAR_GETFLY == 1, recomputed
@ on every map load by CianwoodCity_EventScript_ApplyGladionSceneObjects
@ above - no flag of their own. Declining, winning, or losing the rematch all
@ lead to the same delivery step; only VAR_GETFLY (0/1/2, already existing)
@ tracks completion.
@
@ VAR_TEMP_1/2/3 are scratch for this single visit only (CianwoodCity_EventScript_CityEnter
@ zeroes them on every entry, so no other script reusing these slots can leak in):
@   VAR_TEMP_1 - 0 = intro not played yet this visit, 1 = intro done, 2 = delivery pending
@   VAR_TEMP_2 - battle outcome, copied right after GetBattleOutcome
@   VAR_TEMP_3 - B_FLAG_NO_WHITEOUT state from before the battle, to restore exactly
@
@ Anchors used below (see section 5 of the doc): Gladion (17,47), Type: Null
@ (17,48), Chuck's wife (18,47, already her existing position). Movement
@ scripts here are a first pass, not confirmed against the live collision map.
@ ---------------------------------------------------------------------------

CianwoodCity_EventScript_Gladion::
	lock
	goto_if_ne VAR_GETFLY, 1, CianwoodCity_EventScript_GladionAlreadyGone
	goto_if_eq VAR_TEMP_1, 2, CianwoodCity_EventScript_GladionRetryDelivery
	checkitemspace ITEM_HM_FLY, 1
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_GladionBusy
	lockall
	goto_if_eq VAR_TEMP_1, 1, CianwoodCity_EventScript_GladionChallenge
	goto CianwoodCity_EventScript_GladionIntro
	end

@ Defensive only: the object shouldn't be on the map at all once VAR_GETFLY
@ leaves 1 (see CianwoodCity_EventScript_ApplyGladionSceneObjects).
CianwoodCity_EventScript_GladionAlreadyGone::
	release
	end

CianwoodCity_EventScript_GladionBusy::
	faceplayer
	msgbox CianwoodCity_Text_GladionBusy1, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionBusy2, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_CIANWOOD_GLADION, DIR_SOUTH
	release
	end

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
	faceplayer
	msgbox CianwoodCity_Text_GladionLookWhoItIs, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionBeatChuck, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_WifeLostTrackOfTime, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_WifeBroughtHM, MSGBOX_DEFAULT
	closemessage

	turnobject LOCALID_CIANWOOD_CHUCKSWIFE, DIR_WEST
	delay 12
	applymovement LOCALID_CIANWOOD_CHUCKSWIFE, CianwoodCity_Movement_ChucksWifeToSafeSpot
	waitmovement 0

	msgbox CianwoodCity_Text_GladionLillieGoldenrod, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionFlowersBattle, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionEnjoyingHere, MSGBOX_DEFAULT
	closemessage

	msgbox CianwoodCity_Text_GladionSoAmI, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionLookingForTrainers, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionWholeMorning, MSGBOX_DEFAULT
	closemessage

	turnobject LOCALID_CIANWOOD_GLADION, DIR_SOUTH
	msgbox CianwoodCity_Text_GladionEveryTimeWater, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionThenFollowing, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionStayedLonger, MSGBOX_DEFAULT
	closemessage

	delay 24
	faceplayer
	msgbox CianwoodCity_Text_GladionGoodMorning, MSGBOX_DEFAULT
	closemessage

	setvar VAR_TEMP_1, 1
	goto CianwoodCity_EventScript_GladionChallenge

CianwoodCity_EventScript_GladionChallenge::
	turnobject LOCALID_CIANWOOD_GLADION, DIR_SOUTH
	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullApproach
	waitmovement 0
	faceplayer
	msgbox CianwoodCity_Text_GladionRememberTrainer, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionWantToFindOut, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionRematchBeforeLeave, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionFlyEitherWay, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionBattleQuestion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CianwoodCity_EventScript_GladionDecline

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

CianwoodCity_EventScript_GladionDecline::
	msgbox CianwoodCity_Text_GladionFineAnotherTime, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

@ B_OUTCOME_WON: Gladion's own line (CianwoodCity_Text_GladionDefeatedByPlayer)
@ already played automatically when his last Pokémon fainted.
CianwoodCity_EventScript_GladionPlayerWon::
	turnobject LOCALID_CIANWOOD_GLADION, DIR_SOUTH
	msgbox CianwoodCity_Text_GladionNeedAnotherPlan, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionYouNoticedToo, MSGBOX_DEFAULT
	closemessage
	goto CianwoodCity_EventScript_GladionDeliver

CianwoodCity_EventScript_GladionPlayerLost::
	msgbox CianwoodCity_Text_GladionThatOneWasOurs, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionMadeUsWorkForIt, MSGBOX_DEFAULT
	turnobject LOCALID_CIANWOOD_GLADION, DIR_SOUTH
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

@ Link-battle-shaped/unexpected outcome only: heal, restore music and
@ controls, but do not deliver the item or mark the encounter concluded -
@ mirrors GoldenrodCity_FlowerShop_EventScript_LillieUnexpectedOutcome.
CianwoodCity_EventScript_GladionUnexpectedOutcome::
	msgbox CianwoodCity_Text_GladionUnexpectedOutcome, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	fadedefaultbgm
	releaseall
	end

CianwoodCity_EventScript_GladionDeliver::
	setvar VAR_TEMP_1, 2
	call Common_EventScript_OutOfCenterPartyHeal

@ Re-entered manually (VAR_TEMP_1 == 2): the intro, challenge and battle
@ already happened this visit, only retry the delivery step. Should not
@ normally be needed - checkitemspace already confirmed room back in
@ CianwoodCity_EventScript_Gladion - but if giveitem fails anyway, VAR_TEMP_1
@ stays 2 so talking to Gladion again only retries this step.
CianwoodCity_EventScript_GladionRetryDelivery::
	lockall
	msgbox CianwoodCity_Text_GladionHereHMFromWife, MSGBOX_DEFAULT
	checkitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_GladionItemAlreadyPresent
	giveitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, FALSE, CianwoodCity_EventScript_GladionGiveItemFailed
CianwoodCity_EventScript_GladionItemAlreadyPresent::
	setvar VAR_GETFLY, 2
	msgbox CianwoodCity_Text_GladionFlyMakesTripEasier, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionTellLillie, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionHeardWholeStory, MSGBOX_DEFAULT
	closemessage

	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullFirstStep
	waitmovement 0
	delay 20
	msgbox CianwoodCity_Text_GladionMadeUpYourMind, MSGBOX_DEFAULT
	msgbox CianwoodCity_Text_GladionImComing, MSGBOX_DEFAULT
	closemessage
	faceplayer
	msgbox CianwoodCity_Text_GladionSeeYouAround, MSGBOX_DEFAULT
	closemessage

	playbgm MUS_HG_RIVAL_EXIT, TRUE
	applymovement LOCALID_CIANWOOD_TYPENULL, CianwoodCity_Movement_TypeNullContinue
	applymovement LOCALID_CIANWOOD_GLADION, CianwoodCity_Movement_GladionFollow
	waitmovement 0
	removeobject LOCALID_CIANWOOD_TYPENULL
	removeobject LOCALID_CIANWOOD_GLADION
	fadedefaultbgm
	releaseall
	end

@ Should not happen: checkitemspace already confirmed room before the
@ battle. If it fails anyway, VAR_TEMP_1 stays 2 so talking to Gladion
@ again only retries this delivery step, without repeating the intro/battle.
CianwoodCity_EventScript_GladionGiveItemFailed::
	msgbox CianwoodCity_Text_GladionDeliveryFailed, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	releaseall
	end

CianwoodCity_EventScript_TypeNullInteract::
	lock
	playmoncry SPECIES_TYPE_NULL, CRY_MODE_NORMAL
	waitmoncry
	goto CianwoodCity_EventScript_Gladion

CianwoodCity_Movement_ChucksWifeToSafeSpot:
	walk_right
	walk_right
	face_down
	step_end

CianwoodCity_Movement_TypeNullApproach:
	walk_down
	face_up
	step_end

CianwoodCity_Movement_TypeNullFirstStep:
	walk_down
	face_up
	step_end

CianwoodCity_Movement_TypeNullContinue:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CianwoodCity_Movement_GladionFollow:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CianwoodCity_Text_GladionBusy1:
	.string "Not now. We're finishing our\n"
	.string "training.$"

CianwoodCity_Text_GladionBusy2:
	.string "Come back later.$"

CianwoodCity_Text_WifeAllThisWay:
	.string "Chuck's wife: You came all this\n"
	.string "way, and you're going back by\l"
	.string "sea?$"

CianwoodCity_Text_WifeTakeFly:
	.string "Take Fly. Even someone who\n"
	.string "enjoys walking needs a rest.$"

CianwoodCity_Text_GladionNotInHurry:
	.string "Gladion: I'm not in a hurry.$"

CianwoodCity_Text_GladionLookWhoItIs:
	.string "Gladion: Look who it is.$"

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
	.string "Gladion: Lillie told me about\n"
	.string "Goldenrod.$"

CianwoodCity_Text_GladionFlowersBattle:
	.string "First the battle. Then the\n"
	.string "flowers. Then back to the\l"
	.string "battle.$"

CianwoodCity_Text_GladionEnjoyingHere:
	.string "She's enjoying it here.$"

CianwoodCity_Text_GladionSoAmI:
	.string "Gladion: So am I.$"

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
	.string "Gladion: You remember this\n"
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
	.string "Let's battle?$"

CianwoodCity_Text_GladionFineAnotherTime:
	.string "Fine. Another time.$"

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
	.string "We should stop here. Let me\n"
	.string "take care of your Pokémon.$"

CianwoodCity_Text_GladionHereHMFromWife:
	.string "Gladion: Here. The HM she left\n"
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
