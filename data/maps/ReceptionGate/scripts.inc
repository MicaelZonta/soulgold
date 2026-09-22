.set LOCALID_INDIGOJUNCTION_POLICEMAN, 1
.set LOCALID_INDIGOJUNCTION_JANINE, 4

ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ReceptionGate_OnTransition
	.byte 0

ReceptionGate_OnTransition::
	@ Old saves: a Champion who never saw the Gladion scene must not find
	@ him standing in the corridor with nothing to say.
	call_if_set FLAG_IS_CHAMPION, ReceptionGate_EventScript_CloseGladionScene
	end

ReceptionGate_EventScript_CloseGladionScene::
	setflag FLAG_GLADION_VICTORY_ROAD_DONE
	return

ReceptionGate_EventScript_Janine::
    lock
    faceplayer
    msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_ROUTE22_JANINE
    removeobject LOCALID_INDIGOJUNCTION_JANINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_JANINE
    release
    end

ReceptionGate_Text_Janine:
    .string "Jaine: I'm on the way to my dad's\n"
    .string "house to give him his lunch.\p"
    .string "The Elite Four has no time to rest\n"
    .string "day or night. It's such hard work,\l"
    .string "you know?\p"
    .string "If you're ready for another battle,\n"
    .string "I'll be at the Dojo later.$"


ReceptionGate_EventScript_Officer::
    lock
    faceplayer
    goto_if_set FLAG_IS_CHAMPION, ReceptionGate_EventScript_OfficerCleared
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_OfficerNotEnough
    goto_if_set FLAG_LEGENDARY_STORY_CAP, ReceptionGate_EventScript_OfficerCleared
    call ReceptionGate_EventScript_ShowStoryGuidance
    closemessage
    release
    end

ReceptionGate_EventScript_OfficerNotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    release
    end

ReceptionGate_EventScript_OfficerCleared::
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    release
    end

ReceptionGate_Trigger::
    lock
    playse SE_PIN
    applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, Common_Movement_ExclamationMark
    delay 20
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
    goto_if_unset FLAG_LEGENDARY_STORY_CAP, ReceptionGate_EventScript_StoryBlocked
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    setvar VAR_ROUTE27_STATE, 1
    release
    end

ReceptionGate_EventScript_StoryBlocked::
    call ReceptionGate_EventScript_ShowStoryGuidance
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end 

ReceptionGate_EventScript_NotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end

ReceptionGate_EventScript_ShowStoryGuidance::
    goto_if_ge VAR_ECRUTEAK_CITY_THEATER, 7, ReceptionGate_EventScript_ShowLegendaryGuidance
    goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 9, ReceptionGate_EventScript_ShowLegendaryGuidance
    goto_if_ge VAR_ECRUTEAK_CITY_THEATER, 4, ReceptionGate_EventScript_ShowKimonoGuidance
    goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 8, ReceptionGate_EventScript_ShowKimonoGuidance
    msgbox VictoryRoadGate_Text_VisitElm, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_ShowKimonoGuidance::
    msgbox VictoryRoadGate_Text_VisitKimonoGirls, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_ShowLegendaryGuidance::
    goto_if_eq VAR_LUGIA_OR_HOOH, 1, ReceptionGate_EventScript_ShowWhirlIslandsGuidance
    goto ReceptionGate_EventScript_ShowTinTowerGuidance

ReceptionGate_EventScript_ShowWhirlIslandsGuidance::
    msgbox VictoryRoadGate_Text_VisitWhirlIslands, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_ShowTinTowerGuidance::
    msgbox VictoryRoadGate_Text_VisitTinTower, MSGBOX_DEFAULT
    return

ReceptionGate_EventScript_SilverGuard::
    msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
    end
ReceptionGate_EventScript_KantoGuard::
    msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
    end

VictoryRoadGate_Text_VisitElm:
    .string "You're {PLAYER}, right?\p"
    .string "Prof. Elm has been trying to\n"
    .string "reach you.\p"
    .string "Go see him at his Lab in\n"
    .string "New Bark Town!$"

VictoryRoadGate_Text_VisitKimonoGirls:
    .string "One of the Kimono Girls asked me\n"
    .string "to relay a message.\p"
    .string "They're waiting for you at the\n"
    .string "Ecruteak Dance Theater.$"

VictoryRoadGate_Text_VisitWhirlIslands:
    .string "The Kimono Girls traced the\n"
    .string "Legendary Pokémon to the\l"
    .string "Whirl Islands.\p"
    .string "Head there before challenging the\n"
    .string "Pokémon League.$"

VictoryRoadGate_Text_VisitTinTower:
    .string "The Kimono Girls traced the\n"
    .string "Legendary Pokémon to the\l"
    .string "Tin Tower.\p"
    .string "Head there before challenging the\n"
    .string "Pokémon League.$"

VictoryRoadGate_Text_NotEnoughBadges:
    .string "You don't have all the Gym Badges\n"
    .string "of Johto.\p"
    .string "I'm sorry, but I can't let you go\n"
    .string "through.$"

VictoryRoadGate_Text_EightBadges:
    .string "Oh! The eight Badges of Johto!\p"
    .string "Please, go right on through!$"

VictoryRoadGate_Text_LeftBlackBelt:
    .string "This way leads to Mt.Silver.\p"
    .string "You'll see scary-strong Pokémon out\n"
    .string "there.$"

VictoryRoadGate_Text_RightBlackBelt:
    .string "Off to the Pokémon League, are you?\p"
    .string "The Elite Four are so strong it's\n"
    .string "scary, and they're ready for you!$"

@ ---------------------------------------------------------------------------
@ Gladion + Silvally, farewell battle before Victory Road.
@ See docs/GLADION_VICTORY_ROAD_PROPOSTA_E_AUDITORIA_V2.md.
@
@ Forced scene. The north corridor is only reachable through the guard's
@ tile (11,14), and the guard only lets a player with 8 badges and the
@ legendary story done through, so no progress check is needed here.
@ Completion is FLAG_GLADION_VICTORY_ROAD_DONE, set for every outcome.
@
@ Visibility: both objects use FLAG_GLADION_VICTORY_ROAD_DONE directly as their
@ template flag - always on the map until the scene ends, then gone for good.
@ The y=5 triggers use VAR_TEMP_1 == 0, which is always true here (nothing on
@ this map writes VAR_TEMP_1), and the script itself checks the flag.
@
@ Scratch vars (all written before being read):
@   VAR_0x8004/8005 - player x/y at the trigger
@   VAR_TEMP_2      - battle outcome, copied right after GetBattleOutcome
@   VAR_TEMP_3      - B_FLAG_NO_WHITEOUT state from before the battle
@
@ North corridor (dump_mapa.py), # = blocked, W = warp to VictoryRoadKanto_B2F:
@
@        x= 9 10 11 12
@   y=1   #  W  W  #
@   y=2   .  .  .  .
@   y=3   .  G  S  .      G/S start: Gladion (10,3), Silvally (11,3), facing up
@   y=4   .  .  .  .
@   y=5   t  t  t  t      t = trigger (VAR_ROUTE27_STATE == 1)
@   ...   .  .  .  .      columns 9..12 open down to y=12
@   y=13  #  #  .  .      funnel toward the guard starts here
@
@ Scene layout (y grows downward):
@   player    (x,5) -> (10,5), facing up
@   Silvally  (11,3) -> (11,4)              beside Gladion, diagonal to player
@   Gladion   (10,3) -> (10,4)              directly north of the player
@   Gladion <-> Silvally: DIR_EAST / DIR_WEST. Both -> player: DIR_SOUTH.
@ Exit: they shift to columns 11/12, stop at y=5 on the player's east for the
@ last line, then walk down together and are removed at y=12 (off screen,
@ before the y=13 funnel and the guard).
@ ---------------------------------------------------------------------------

@ Runs only while both objects are on the map (flag unset). Only fires
@ walking north: coming back out of the cave (facing south) or sidestepping
@ along y=5 does nothing.
ReceptionGate_EventScript_GladionTrigger::
	goto_if_set FLAG_GLADION_VICTORY_ROAD_DONE, ReceptionGate_EventScript_GladionTriggerEnd
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_ne VAR_RESULT, DIR_NORTH, ReceptionGate_EventScript_GladionTriggerEnd
	lockall
	hidefollower
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 9, ReceptionGate_EventScript_GladionPlayerFrom9
	call_if_eq VAR_0x8004, 11, ReceptionGate_EventScript_GladionPlayerFrom11
	call_if_eq VAR_0x8004, 12, ReceptionGate_EventScript_GladionPlayerFrom12
	goto ReceptionGate_EventScript_GladionIntro

ReceptionGate_EventScript_GladionTriggerEnd::
	end

ReceptionGate_EventScript_GladionPlayerFrom9::
	applymovement OBJ_EVENT_ID_PLAYER, ReceptionGate_Movement_PlayerFrom9
	waitmovement 0
	return

ReceptionGate_EventScript_GladionPlayerFrom11::
	applymovement OBJ_EVENT_ID_PLAYER, ReceptionGate_Movement_PlayerFrom11
	waitmovement 0
	return

ReceptionGate_EventScript_GladionPlayerFrom12::
	applymovement OBJ_EVENT_ID_PLAYER, ReceptionGate_Movement_PlayerFrom12
	waitmovement 0
	return

ReceptionGate_EventScript_GladionIntro::
	delay 16
	@ Silvally notices the player first: turns, cry, one step to (11,4).
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	playse SE_PIN
	applymovement LOCALID_RECEPTIONGATE_SILVALLY, Common_Movement_ExclamationMark
	waitmovement LOCALID_RECEPTIONGATE_SILVALLY
	playmoncry SPECIES_SILVALLY, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_RECEPTIONGATE_SILVALLY, ReceptionGate_Movement_StepDown
	waitmovement LOCALID_RECEPTIONGATE_SILVALLY
	delay 8
	@ Gladion turns and steps down to (10,4), right in front of the player.
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	applymovement LOCALID_RECEPTIONGATE_GLADION, ReceptionGate_Movement_StepDown
	waitmovement LOCALID_RECEPTIONGATE_GLADION
	msgbox ReceptionGate_Text_GladionThereYouAre, MSGBOX_DEFAULT
	closemessage

	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_EAST
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_WEST
	delay 16
	msgbox ReceptionGate_Text_GladionBackInCianwood, MSGBOX_DEFAULT
	closemessage

	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionOneMoreBattle, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal

	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_EAST
	msgbox ReceptionGate_Text_GladionReady, MSGBOX_DEFAULT
	closemessage
	@ Silvally takes position: faces the player and hops once.
	applymovement LOCALID_RECEPTIONGATE_SILVALLY, ReceptionGate_Movement_SilvallyTakePosition
	waitmovement LOCALID_RECEPTIONGATE_SILVALLY
	msgbox ReceptionGate_Text_GladionTakeFirstStep, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH

	@ No yes/no: the battle is mandatory, and every outcome concludes the
	@ scene without whiteout (skill batalha-sem-blackout).
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_3, VAR_RESULT
	setflag B_FLAG_NO_WHITEOUT
	setvar VAR_LAST_TALKED, LOCALID_RECEPTIONGATE_GLADION
	trainerbattle_no_intro TRAINER_GLADION_VICTORY_ROAD, ReceptionGate_Text_GladionDefeated
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_3, TRUE, ReceptionGate_EventScript_GladionKeepWhiteoutOff
	clearflag B_FLAG_NO_WHITEOUT
ReceptionGate_EventScript_GladionKeepWhiteoutOff::
	@ Silent heal: the only heal line was the one before the battle.
	call Common_EventScript_OutOfCenterPartyHeal
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, ReceptionGate_EventScript_GladionPlayerWon
	goto_if_eq VAR_TEMP_2, B_OUTCOME_LOST, ReceptionGate_EventScript_GladionPlayerLost
	goto_if_eq VAR_TEMP_2, B_OUTCOME_DREW, ReceptionGate_EventScript_GladionDraw
	goto_if_eq VAR_TEMP_2, B_OUTCOME_FORFEITED, ReceptionGate_EventScript_GladionForfeit
	goto ReceptionGate_EventScript_GladionUnexpectedOutcome

@ B_OUTCOME_WON: ReceptionGate_Text_GladionDefeated already played in battle.
ReceptionGate_EventScript_GladionPlayerWon::
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionYouGaveUsAnAnswer, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_EAST
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_WEST
	delay 16
	msgbox ReceptionGate_Text_GladionStillWorkToDo, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionNotTheSameBattle, MSGBOX_DEFAULT
	closemessage
	goto ReceptionGate_EventScript_GladionFarewell

ReceptionGate_EventScript_GladionPlayerLost::
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionReadyThisTime, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_EAST
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_WEST
	delay 16
	msgbox ReceptionGate_Text_GladionYouTrustedMe, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionMakeUsPay, MSGBOX_DEFAULT
	closemessage
	goto ReceptionGate_EventScript_GladionFarewell

ReceptionGate_EventScript_GladionDraw::
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionDraw, MSGBOX_DEFAULT
	closemessage
	goto ReceptionGate_EventScript_GladionFarewell

ReceptionGate_EventScript_GladionForfeit::
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionForfeit, MSGBOX_DEFAULT
	closemessage
	goto ReceptionGate_EventScript_GladionFarewell

@ Not a real outcome of a local trainer battle. Still concludes the scene
@ (same policy as DragonsDen_Shrine/CianwoodCity) so it can't be farmed.
ReceptionGate_EventScript_GladionUnexpectedOutcome::
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionUnexpectedOutcome, MSGBOX_DEFAULT
	closemessage
	goto ReceptionGate_EventScript_GladionFarewell

ReceptionGate_EventScript_GladionFarewell::
	setflag FLAG_GLADION_VICTORY_ROAD_DONE
	@ Both look up the passage toward Victory Road, then back at the player.
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_NORTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_NORTH
	delay 40
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_SOUTH
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_SOUTH
	msgbox ReceptionGate_Text_GladionFromHere, MSGBOX_DEFAULT
	closemessage

	@ Side by side on columns 11/12, one step down, on the player's east:
	@   Silvally (11,4) -> (12,4) -> wait -> (12,5)
	@   Gladion  (10,4) -> wait -> (11,4) -> (11,5)
	@ Gladion only enters (11,4) one full step after Silvally left it.
	playbgm MUS_HG_RIVAL_EXIT, TRUE
	applymovement LOCALID_RECEPTIONGATE_SILVALLY, ReceptionGate_Movement_SilvallySideBySide
	applymovement LOCALID_RECEPTIONGATE_GLADION, ReceptionGate_Movement_GladionSideBySide
	waitmovement LOCALID_RECEPTIONGATE_SILVALLY
	waitmovement LOCALID_RECEPTIONGATE_GLADION
	@ Player (10,5) is WEST of both now.
	turnobject LOCALID_RECEPTIONGATE_GLADION, DIR_WEST
	turnobject LOCALID_RECEPTIONGATE_SILVALLY, DIR_WEST
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox ReceptionGate_Text_GladionSeeYouAfterLeague, MSGBOX_DEFAULT
	closemessage

	@ Same sequence from (11,5)/(12,5): formation kept, down to y=12.
	applymovement LOCALID_RECEPTIONGATE_SILVALLY, ReceptionGate_Movement_LeaveSouth
	applymovement LOCALID_RECEPTIONGATE_GLADION, ReceptionGate_Movement_LeaveSouth
	waitmovement LOCALID_RECEPTIONGATE_SILVALLY
	waitmovement LOCALID_RECEPTIONGATE_GLADION
	@ Both objects use FLAG_GLADION_VICTORY_ROAD_DONE, already set above.
	removeobject LOCALID_RECEPTIONGATE_SILVALLY
	removeobject LOCALID_RECEPTIONGATE_GLADION
	delay 16
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	fadedefaultbgm
	releaseall
	end

ReceptionGate_Movement_PlayerFrom9:
	walk_right
	face_up
	step_end

ReceptionGate_Movement_PlayerFrom11:
	walk_left
	face_up
	step_end

ReceptionGate_Movement_PlayerFrom12:
	walk_left
	walk_left
	face_up
	step_end

ReceptionGate_Movement_StepDown:
	walk_down
	step_end

ReceptionGate_Movement_SilvallyTakePosition:
	face_down
	jump_in_place_down
	step_end

@ Silvally (11,4) -> (12,4), waits one step, -> (12,5).
ReceptionGate_Movement_SilvallySideBySide:
	walk_right
	delay_16
	walk_down
	step_end

@ Gladion (10,4), waits one step, -> (11,4) -> (11,5).
ReceptionGate_Movement_GladionSideBySide:
	delay_16
	walk_right
	walk_down
	step_end

@ (x,5) -> (x,12). Columns 11 and 12 are open all the way down.
ReceptionGate_Movement_LeaveSouth:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

ReceptionGate_Text_GladionThereYouAre:
	.string "Gladion: There you are, {PLAYER}.\p"
	.string "Looks like he noticed you first.\p"
	.string "Remember Type: Null from Cianwood?\p"
	.string "This is Silvally.$"

ReceptionGate_Text_GladionBackInCianwood:
	.string "Gladion: Back in Cianwood, he\n"
	.string "walked ahead before I was ready.\p"
	.string "I thought I had to call him back.\n"
	.string "I just had to keep up.$"

ReceptionGate_Text_GladionOneMoreBattle:
	.string "Gladion: Victory Road is ahead.\n"
	.string "We took a different route here.\p"
	.string "Before we go our separate ways,\n"
	.string "I want one more battle.\p"
	.string "All six. Everything we've learned.\p"
	.string "Your team has come a long way too.\n"
	.string "Let's meet at full strength.$"

ReceptionGate_Text_GladionReady:
	.string "Gladion: Ready?$"

ReceptionGate_Text_GladionTakeFirstStep:
	.string "Then take the first step.$"

ReceptionGate_Text_GladionDefeated:
	.string "…You got us.\n"
	.string "All six of us.$"

ReceptionGate_Text_GladionYouGaveUsAnAnswer:
	.string "Gladion: I wanted to see how far\n"
	.string "we'd come. You gave us an answer.$"

ReceptionGate_Text_GladionStillWorkToDo:
	.string "We still have work to do.$"

ReceptionGate_Text_GladionNotTheSameBattle:
	.string "Next time, don't expect\n"
	.string "the same battle.$"

ReceptionGate_Text_GladionReadyThisTime:
	.string "Gladion: We were ready this time.$"

ReceptionGate_Text_GladionYouTrustedMe:
	.string "You trusted me out there.\n"
	.string "I felt it.$"

ReceptionGate_Text_GladionMakeUsPay:
	.string "You know our team better now.\n"
	.string "Next time, make us pay for it.$"

ReceptionGate_Text_GladionDraw:
	.string "Gladion: Neither team has\n"
	.string "anything left.\p"
	.string "…We'll settle it another day.$"

ReceptionGate_Text_GladionForfeit:
	.string "Gladion: You're stopping here?\n"
	.string "All right.\p"
	.string "Then we'll leave it unfinished.\n"
	.string "Take care of your team.$"

ReceptionGate_Text_GladionUnexpectedOutcome:
	.string "Gladion: That didn't end\n"
	.string "the way I expected.\p"
	.string "Let's make sure\n"
	.string "everyone's all right.$"

ReceptionGate_Text_GladionFromHere:
	.string "Gladion: From here,\n"
	.string "it's you and your team.\p"
	.string "I won't tell you how\n"
	.string "to face the League.\p"
	.string "Just come back with a battle\n"
	.string "worth showing us.$"

ReceptionGate_Text_GladionSeeYouAfterLeague:
	.string "Gladion: …See you after the League,\n"
	.string "{PLAYER}.$"
