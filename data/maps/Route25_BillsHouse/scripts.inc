Route25_BillsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route25_BillsHouse_OnTransition
	.byte 0

Route25_BillsHouse_OnTransition::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	end

Route25_BillsHouse_EventScript_TeleporterTest::
	lockall
	goto_if_unset FLAG_TELEPORTER_UNLOCKED, Route25_BillsHouse_EndChoice
	helpwindow HELP_TELEPORTER_WINDOW
	msgbox Route25_BillsHouse_Text_Teleporter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EndChoice
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, Route25_BillsHouse_Text_Meowth, Route25_BillsHouse_Text_Ponyta, Route25_BillsHouse_Text_Rapidash, Route25_BillsHouse_Text_Slowpoke, Route25_BillsHouse_Text_Slowbro, Route25_BillsHouse_Text_Slowking, Route25_BillsHouse_Text_Farfetchd, Route25_BillsHouse_Text_Weezing, Route25_BillsHouse_Text_MrMime, Route25_BillsHouse_Text_Articuno, Route25_BillsHouse_Text_Zapdos, Route25_BillsHouse_Text_Moltres, Route25_BillsHouse_Text_Corsola, Route25_BillsHouse_Text_Zigzagoon, Route25_BillsHouse_Text_Linoone, Route25_BillsHouse_Text_Cancel
	switch VAR_RESULT
	case 0, Route25_BillsHouse_PickMeowth
	case 1, Route25_BillsHouse_PickPonyta
	case 2, Route25_BillsHouse_PickRapidash
	case 3, Route25_BillsHouse_PickSlowpoke
	case 4, Route25_BillsHouse_PickSlowbro
	case 5, Route25_BillsHouse_PickSlowking
	case 6, Route25_BillsHouse_PickFarfetchd
	case 7, Route25_BillsHouse_PickWeezing
	case 8, Route25_BillsHouse_PickMrMime
	case 9, Route25_BillsHouse_PickArticuno
	case 10, Route25_BillsHouse_PickZapdos
	case 11, Route25_BillsHouse_PickMoltres
	case 12, Route25_BillsHouse_PickCorsola
	case 13, Route25_BillsHouse_PickZigzagoon
	case 14, Route25_BillsHouse_PickLinoone
	case 15, Route25_BillsHouse_EndChoice
	case 127, Route25_BillsHouse_EndChoice
	end

Route25_BillsHouse_Text_Teleporter:
	.string "THIS MACHINE WILL TRANSFORM\n"
	.string "A POKéMON INTO ITS GALARIAN FORM\l"
	.string "THIS PROCESS IS PERMANENT.\l"
	.string "WOULD YOU LIKE TO PROCEED?$"

Route25_BillsHouse_PickMeowth::
	setvar VAR_0x8004, SPECIES_MEOWTH
	setvar VAR_TEMP_0, SPECIES_MEOWTH
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickPonyta::
	setvar VAR_0x8004, SPECIES_PONYTA
	setvar VAR_TEMP_0, SPECIES_PONYTA
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickRapidash::
	setvar VAR_0x8004, SPECIES_RAPIDASH
	setvar VAR_TEMP_0, SPECIES_RAPIDASH
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickSlowpoke::
	setvar VAR_0x8004, SPECIES_SLOWPOKE
	setvar VAR_TEMP_0, SPECIES_SLOWPOKE
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickSlowbro::
	setvar VAR_0x8004, SPECIES_SLOWBRO
	setvar VAR_TEMP_0, SPECIES_SLOWBRO
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickSlowking::
	setvar VAR_0x8004, SPECIES_SLOWKING
	setvar VAR_TEMP_0, SPECIES_SLOWKING
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickFarfetchd::
	setvar VAR_0x8004, SPECIES_FARFETCHD
	setvar VAR_TEMP_0, SPECIES_FARFETCHD
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickWeezing::
	setvar VAR_0x8004, SPECIES_WEEZING
	setvar VAR_TEMP_0, SPECIES_WEEZING
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickMrMime::
	setvar VAR_0x8004, SPECIES_MR_MIME
	setvar VAR_TEMP_0, SPECIES_MR_MIME
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickArticuno::
	setvar VAR_0x8004, SPECIES_ARTICUNO
	setvar VAR_TEMP_0, SPECIES_ARTICUNO
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickZapdos::
	setvar VAR_0x8004, SPECIES_ZAPDOS
	setvar VAR_TEMP_0, SPECIES_ZAPDOS
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickMoltres::
	setvar VAR_0x8004, SPECIES_MOLTRES
	setvar VAR_TEMP_0, SPECIES_MOLTRES
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickCorsola::
	setvar VAR_0x8004, SPECIES_CORSOLA
	setvar VAR_TEMP_0, SPECIES_CORSOLA
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickZigzagoon::
	setvar VAR_0x8004, SPECIES_ZIGZAGOON
	setvar VAR_TEMP_0, SPECIES_ZIGZAGOON
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_PickLinoone::
	setvar VAR_0x8004, SPECIES_LINOONE
	setvar VAR_TEMP_0, SPECIES_LINOONE
	goto Route25_BillsHouse_CheckParty
	end

Route25_BillsHouse_EndChoice::
	closemessage
	releaseall
	end

Route25_BillsHouse_CheckParty::
	special CheckPartyForSpecies
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_NoPokemon
	closemessage
	goto Route25_BillsHouse_CutsceneSetup
	end

Route25_BillsHouse_NoPokemon::
	msgbox Route25_BillsHouse_Text_NotInParty
	closemessage
	releaseall
	end


Route25_BillsHouse_SetPlayerMale::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_GOLD_NORMAL
	return

Route25_BillsHouse_SetPlayerFemale::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_KRIS_NORMAL
	return

Route25_BillsHouse_CutsceneSetup::
	fadescreen FADE_TO_BLACK
	clearflag FLAG_TEMP_1
	copyvar VAR_OBJ_GFX_ID_0, VAR_TEMP_0
	addvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_MON
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route25_BillsHouse_SetPlayerMale
	call_if_eq VAR_RESULT, FEMALE, Route25_BillsHouse_SetPlayerFemale
	addobject LOCALID_BILLS_GRANDPA_PLAYER
	addobject LOCALID_BILLS_GRANDPA_OLD_MON
	applymovement OBJ_EVENT_ID_PLAYER, Route25_BillsHouse_Movement_HidePlayer
	hidefollower
	turnobject LOCALID_BILLS_GRANDPA, DIR_NORTH
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Route25_BillsHouse_Movement_CameraPanUp
	waitmovement 0
	delay 60
	fadescreen FADE_FROM_BLACK

Route25_BillsHouse_CutsceneBeforeTeleport::
	delay 60
	opendoor 10, 3
	waitdooranim
	playmoncry VAR_TEMP_0, CRY_MODE_NORMAL
	waitmoncry 
	applymovement LOCALID_BILLS_GRANDPA_OLD_MON, Common_Movement_WalkUp1
	waitmovement 0
	turnobject LOCALID_BILLS_GRANDPA_OLD_MON, DIR_SOUTH
	applymovement LOCALID_BILLS_GRANDPA_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	turnobject LOCALID_BILLS_GRANDPA_PLAYER, DIR_NORTH
	playse SE_CONTEST_CURTAIN_FALL
	closedoor 10, 3
	delay 10
	removeobject LOCALID_BILLS_GRANDPA_OLD_MON
	waitdooranim

Route25_BillsHouse_CutsceneTeleport::
	delay 35
	playse SE_PIN
	waitse
	setvar VAR_0x8004, 0
	special AnimateTeleporterHousing
	delay 10
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	setvar VAR_0x8004, 1
	special AnimateTeleporterHousing
	playse SE_WARP_IN
	special AnimateTeleporterCable
	delay 30
	applymovement LOCALID_BILLS_GRANDPA_PLAYER, Route25_BillsHouse_Movement_PlayerMoveLeft
	waitse
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	call Route25_BillsHouse_BeepSE
	special GetRegionalFormSpecies
	copyvar VAR_TEMP_1, VAR_RESULT
	clearflag FLAG_TEMP_2
	copyvar VAR_OBJ_GFX_ID_1, VAR_TEMP_1
	addvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_MON
	
Route25_BillsHouse_CutsceneAfterTeleport::
	opendoor 3, 3
	delay 10
	addobject LOCALID_BILLS_GRANDPA_NEW_MON
	waitdooranim
	applymovement LOCALID_BILLS_GRANDPA_PLAYER, Route25_BillsHouse_Movement_PlayerSlideDown
	playse SE_LEDGE
	applymovement LOCALID_BILLS_GRANDPA_NEW_MON, Common_Movement_WalkDown1
	waitmovement 0
	waitmovement 0
	@playse SE_PIN
	@applymovement LOCALID_BILLS_GRANDPA_PLAYER, Common_Movement_ExclamationMark
	@delay 60
	playse SE_CONTEST_CURTAIN_FALL
	closedoor 3, 3
	delay 10
	applymovement LOCALID_BILLS_GRANDPA_NEW_MON, Route25_BillsHouse_Movement_MonCelebration
	waitmovement 0
	playmoncry VAR_TEMP_0, CRY_MODE_NORMAL
	waitmoncry
	delay 60

Route25_BillsHouse_CutsceneCleanup::
	fadescreen FADE_TO_BLACK
	applymovement OBJ_EVENT_ID_CAMERA, Route25_BillsHouse_Movement_CameraPanDown
	waitmovement 0
	removeobject LOCALID_BILLS_GRANDPA_NEW_MON
	removeobject LOCALID_BILLS_GRANDPA_OLD_MON
	removeobject LOCALID_BILLS_GRANDPA_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Route25_BillsHouse_Movement_ShowPlayer
	waitmovement 0
	turnobject LOCALID_BILLS_GRANDPA, DIR_SOUTH
	special RemoveCameraObject
	special ConvertToRegionalForm
	delay 60
	callnative UpdateFollowingPokemon
	fadescreen FADE_FROM_BLACK
	setflag FLAG_USED_TELEPORTER
	releaseall
	end

Route25_BillsHouse_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route25_BillsHouse_Movement_CameraPanDown:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

Route25_BillsHouse_Movement_PlayerMoveLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_up
	step_end

Route25_BillsHouse_Movement_PlayerSlideDown:
	lock_facing_direction
	jump_down
	unlock_facing_direction
	step_end

Route25_BillsHouse_BeepSE::
	playse SE_BALL
	waitse
	delay 20
	return

Route25_BillsHouse_Movement_HidePlayer:
	set_invisible
	step_end

Route25_BillsHouse_Movement_ShowPlayer:
	set_visible
	step_end

Route25_BillsHouse_Text_Meowth:
	.string "Meowth$"

Route25_BillsHouse_Text_Ponyta:
	.string "Ponyta$"

Route25_BillsHouse_Text_Rapidash:
	.string "Rapidash$"

Route25_BillsHouse_Text_Slowpoke:
	.string "Slowpoke$"

Route25_BillsHouse_Text_Slowbro:
	.string "Slowbro$"

Route25_BillsHouse_Text_Slowking:
	.string "Slowking$"

Route25_BillsHouse_Text_Farfetchd:
	.string "Farfetch'd$"

Route25_BillsHouse_Text_Weezing:
	.string "Weezing$"

Route25_BillsHouse_Text_MrMime:
	.string "Mr. Mime$"

Route25_BillsHouse_Text_Articuno:
	.string "Articuno$"

Route25_BillsHouse_Text_Zapdos:
	.string "Zapdos$"

Route25_BillsHouse_Text_Moltres:
	.string "Moltres$"

Route25_BillsHouse_Text_Corsola:
	.string "Corsola$"

Route25_BillsHouse_Text_Zigzagoon:
	.string "Zigzagoon$"

Route25_BillsHouse_Text_Linoone:
	.string "Linoone$"

Route25_BillsHouse_Text_Cancel:
	.string "Cancel$"

Route25_BillsHouse_Text_NotInParty:
	.string "POKéMON NOT DETECTED.$"

@VAR_BILLS_GRANDPA

Route25_BillsHouse_EventScript_Gramps::
	lock
	faceplayer
	@ 1-5: pedidos do SoulGold (Spinda..Pichu); 6: os 5 foram mostrados.
	@ 7-11: pedidos do HnS (Meowth..Slowpoke, destrava o Teleporter); 12: tudo mostrado.
	goto_if_eq VAR_BILLS_GRANDPA, 1, Route25_BillsHouse_EventScript_Gramps_Spinda
	goto_if_eq VAR_BILLS_GRANDPA, 2, Route25_BillsHouse_EventScript_Gramps_Roselia
	goto_if_eq VAR_BILLS_GRANDPA, 3, Route25_BillsHouse_EventScript_Gramps_Lotad
	goto_if_eq VAR_BILLS_GRANDPA, 4, Route25_BillsHouse_EventScript_Gramps_Growlithe
	goto_if_eq VAR_BILLS_GRANDPA, 5, Route25_BillsHouse_EventScript_Gramps_Pichu
	goto_if_eq VAR_BILLS_GRANDPA, 6, Route25_BillsHouse_EventScript_Gramps_Meowth
	goto_if_eq VAR_BILLS_GRANDPA, 7, Route25_BillsHouse_EventScript_Gramps_Meowth
	goto_if_eq VAR_BILLS_GRANDPA, 8, Route25_BillsHouse_EventScript_Gramps_Zigzagoon
	goto_if_eq VAR_BILLS_GRANDPA, 9, Route25_BillsHouse_EventScript_Gramps_Ponyta
	goto_if_eq VAR_BILLS_GRANDPA, 10, Route25_BillsHouse_EventScript_Gramps_Farfetchd
	goto_if_eq VAR_BILLS_GRANDPA, 11, Route25_BillsHouse_EventScript_Gramps_Slowpoke
	goto_if_eq VAR_BILLS_GRANDPA, 12, Route25_BillsHouse_EventScript_Gramps_ShownAll
	msgbox Route25_BillsHouse_Text_GrandpaIntro, MSGBOX_DEFAULT
	setvar VAR_BILLS_GRANDPA, 1
	goto Route25_BillsHouse_EventScript_Gramps_Spinda

Route25_BillsHouse_EventScript_Gramps_Declined::
	msgbox Route25_BillsHouse_Text_YouDontHaveIt, MSGBOX_DEFAULT
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_WrongMon::
	msgbox Route25_BillsHouse_Text_WrongPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_AskToSee::
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_AskToSeeNone
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_AskToSeeNone
	copyvar VAR_0x8005, VAR_0x8004
	specialvar VAR_RESULT, GetTradeSpecies
	return

Route25_BillsHouse_EventScript_Gramps_AskToSeeNone::
	setvar VAR_RESULT, SPECIES_NONE
	return

Route25_BillsHouse_EventScript_Gramps_Spinda::
	msgbox Route25_BillsHouse_Text_Spinda, MSGBOX_DEFAULT
	call Route25_BillsHouse_EventScript_Gramps_AskToSee
	goto_if_eq VAR_RESULT, SPECIES_NONE, Route25_BillsHouse_EventScript_Gramps_Declined
	goto_if_ne VAR_RESULT, SPECIES_SPINDA, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_SPINDA
	setvar VAR_TEMP_0, ITEM_EVERSTONE
	setvar VAR_TEMP_1, 1
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Roselia::
	msgbox Route25_BillsHouse_Text_Roselia, MSGBOX_DEFAULT
	call Route25_BillsHouse_EventScript_Gramps_AskToSee
	goto_if_eq VAR_RESULT, SPECIES_NONE, Route25_BillsHouse_EventScript_Gramps_Declined
	goto_if_ne VAR_RESULT, SPECIES_ROSELIA, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_ROSELIA
	setvar VAR_TEMP_0, ITEM_LEAF_STONE
	setvar VAR_TEMP_1, 3
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Lotad::
	msgbox Route25_BillsHouse_Text_Lotad, MSGBOX_DEFAULT
	call Route25_BillsHouse_EventScript_Gramps_AskToSee
	goto_if_eq VAR_RESULT, SPECIES_NONE, Route25_BillsHouse_EventScript_Gramps_Declined
	goto_if_ne VAR_RESULT, SPECIES_LOTAD, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_LOTAD
	setvar VAR_TEMP_0, ITEM_DEEP_SEA_TOOTH
	setvar VAR_TEMP_1, 1
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Growlithe::
	msgbox Route25_BillsHouse_Text_Growlithe, MSGBOX_DEFAULT
	call Route25_BillsHouse_EventScript_Gramps_AskToSee
	goto_if_eq VAR_RESULT, SPECIES_NONE, Route25_BillsHouse_EventScript_Gramps_Declined
	goto_if_ne VAR_RESULT, SPECIES_GROWLITHE, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_GROWLITHE
	setvar VAR_TEMP_0, ITEM_SUN_STONE
	setvar VAR_TEMP_1, 1
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Pichu::
	msgbox Route25_BillsHouse_Text_Pichu, MSGBOX_DEFAULT
	call Route25_BillsHouse_EventScript_Gramps_AskToSee
	goto_if_eq VAR_RESULT, SPECIES_NONE, Route25_BillsHouse_EventScript_Gramps_Declined
	goto_if_ne VAR_RESULT, SPECIES_PICHU, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_PICHU
	setvar VAR_TEMP_0, ITEM_DEEP_SEA_SCALE
	setvar VAR_TEMP_1, 1
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Meowth::
	goto_if_eq VAR_BILLS_GRANDPA, 6, Route25_BillsHouse_EventScript_Gramps_StartHnSChain
	goto Route25_BillsHouse_EventScript_Gramps_MeowthAsk

Route25_BillsHouse_EventScript_Gramps_StartHnSChain::
	setvar VAR_BILLS_GRANDPA, 7
Route25_BillsHouse_EventScript_Gramps_MeowthAsk::
	msgbox Route25_BillsHouse_Text_GrampsMeowth, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_MEOWTH, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_MEOWTH
	setvar VAR_TEMP_0, ITEM_EXP_CANDY_L
	setvar VAR_TEMP_1, 1
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Zigzagoon::
	msgbox Route25_BillsHouse_Text_GrampsZigzagoon, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_ZIGZAGOON, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON
	setvar VAR_TEMP_0, ITEM_EXP_CANDY_L
	setvar VAR_TEMP_1, 3
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Ponyta::
	msgbox Route25_BillsHouse_Text_GrampsPonyta, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_eq VAR_RESULT, SPECIES_PONYTA, Route25_BillsHouse_EventScript_Gramps_PonytaRightMon
	goto_if_eq VAR_RESULT, SPECIES_RAPIDASH, Route25_BillsHouse_EventScript_Gramps_PonytaRightMon
	goto Route25_BillsHouse_EventScript_Gramps_WrongMon
Route25_BillsHouse_EventScript_Gramps_PonytaRightMon::
	bufferspeciesname STR_VAR_1, SPECIES_PONYTA
	setvar VAR_TEMP_0, ITEM_EXP_CANDY_L
	setvar VAR_TEMP_1, 5
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Farfetchd::
	msgbox Route25_BillsHouse_Text_GrampsFarfetchd, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_FARFETCHD, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_FARFETCHD
	setvar VAR_TEMP_0, ITEM_EXP_CANDY_L
	setvar VAR_TEMP_1, 7
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Slowpoke::
	msgbox Route25_BillsHouse_Text_GrampsSlowpoke, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_SLOWPOKE, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_SLOWPOKE
	goto Route25_BillsHouse_EventScript_Gramps_SlowpokeReward

Route25_BillsHouse_EventScript_Gramps_SlowpokeReward::
	msgbox Route25_BillsHouse_Text_ShownPokemon, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_Appreciation, MSGBOX_DEFAULT
	giveitem ITEM_GALARICA_CUFF
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	giveitem ITEM_GALARICA_WREATH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route25_BillsHouse_Text_TeleporterUnlocked, MSGBOX_DEFAULT
	setflag FLAG_TELEPORTER_UNLOCKED
	addvar VAR_BILLS_GRANDPA, 1
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_ShownAll::
	msgbox Route25_BillsHouse_Text_ShownAll, MSGBOX_DEFAULT
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_Correctmon::
	checkitemspace VAR_TEMP_0, VAR_TEMP_1
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route25_BillsHouse_Text_ShownPokemon, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_Appreciation, MSGBOX_DEFAULT
	setvar VAR_0x8006, 0
Route25_BillsHouse_EventScript_Gramps_GiveLoop::
	giveitem VAR_TEMP_0
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	addvar VAR_0x8006, 1
	compare VAR_0x8006, VAR_TEMP_1
	goto_if_lt Route25_BillsHouse_EventScript_Gramps_GiveLoop
	msgbox Route25_BillsHouse_Text_ComeAgain, MSGBOX_DEFAULT
	addvar VAR_BILLS_GRANDPA, 1
	closemessage
	release
	end

Route25_BillsHouse_Test::
	givemon SPECIES_MEOWTH, 10
	givemon SPECIES_ZIGZAGOON, 10
	givemon SPECIES_PONYTA, 10
	givemon SPECIES_FARFETCHD, 10
	givemon SPECIES_SLOWPOKE, 10
	end

Route25_BillsHouse_Movement_MonCelebration:
	jump_in_place_down
	jump_in_place_left
	jump_in_place_right
	jump_in_place_down
	step_end

Route25_BillsHouse_Text_GrandpaIntro:
	.string "Hm? You know Bill? He's my\n"
	.string "grandson.\p"
	.string "He's in Johto. He does\n"
	.string "something with PCs, so I'm\l"
	.string "housesitting.$"

Route25_BillsHouse_Text_GrampsMeowth:
	.string "My grandson Bill told me about\n"
	.string "a Pokémon that has sharp claws,\l"
	.string "a charm on its head, and is\p"
	.string "said to bring good fortune.$"

Route25_BillsHouse_Text_GrampsZigzagoon:
	.string "Bill mentioned a Pokémon that\n"
	.string "runs around in a zigzag\l"
	.string "pattern.\p"
	.string "It's quite the little\n"
	.string "scavenger, I hear.$"

Route25_BillsHouse_Text_GrampsPonyta:
	.string "Do you know of a Pokémon with\n"
	.string "a fiery mane?\p"
	.string "I hear it can run faster than\n"
	.string "most trains.$"

Route25_BillsHouse_Text_GrampsFarfetchd:
	.string "Bill told me about a Pokémon\n"
	.string "that always carries a stalk\l"
	.string "of leek with it.\p"
	.string "Quite the peculiar creature.$"

Route25_BillsHouse_Text_GrampsSlowpoke:
	.string "Do you know the Pokémon that\n"
	.string "is always staring blankly?\p"
	.string "Its tail is often sold on the\n"
	.string "black market.$"

Route25_BillsHouse_Text_TeleporterUnlocked:
	.string "Oh, one more thing!\p"
	.string "Bill's Teleporter.\n"
	.string "That's the big machine over there.\p"
	.string "He never quite got it working.\p"
	.string "But it does curious things to\n"
	.string "Pokémon.\p"
	.string "You're welcome to try it, if\n"
	.string "you'd like!\p"
	.string "Just use that computer over there.$"

Route25_BillsHouse_Text_AskToSeeMon:
	.string "If you have that Pokémon, may I\n"
	.string "see it, please?$"

Route25_BillsHouse_Text_ExcitedToSee:
	.string "You will show me? How good of\n"
	.string "you!$"

Route25_BillsHouse_Text_YouDontHaveIt:
	.string "You don't have it?\n"
	.string "That's too bad…$"

Route25_BillsHouse_Text_ShownPokemon:
	.string "Ah, so that is {STR_VAR_1}?\p"
	.string "Isn't it cute! That's so kind\n"
	.string "of you.$"

Route25_BillsHouse_Text_Appreciation:
	.string "Thanks!\p"
	.string "This is a token of my\n"
	.string "appreciation.$"

Route25_BillsHouse_Text_ComeAgain:
	.string "Come visit again sometime.$"

Route25_BillsHouse_Text_ShownAll:
	.string "Thanks for showing me so many\n"
	.string "cute Pokémon.\p"
	.string "I really enjoyed myself. I'm\n"
	.string "glad I've lived such a long life.\p"
	.string "Feel free to use the Teleporter\n"
	.string "whenever you like.$"

Route25_BillsHouse_Text_WrongPokemon:
	.string "Hm?\p"
	.string "That's not the Pokémon that I\n"
	.string "was told about.$"

Route25_BillsHouse_Text_Spinda:
	.string "My grandson Bill told me about\n"
	.string "a Pokémon that is covered in\l"
	.string "a random pattern.$"

Route25_BillsHouse_Text_Roselia:
	.string "Ah, my grandson mentioned a\n"
	.string "green Pokémon that has flowers\l"
	.string "growing from its wrists.$"

Route25_BillsHouse_Text_Lotad:
	.string "Do you know of a water Pokémon\n"
	.string "that has a big lily pad on\l"
	.string "its head?\p"
	.string "I heard there are some at the\n"
	.string "Fuchsia Safari Zone.\p"
	.string "I would surely like to see it.$"

Route25_BillsHouse_Text_Growlithe:
	.string "Bill told me about a Pokémon\n"
	.string "that is very loyal to its\l"
	.string "trainer.\p"
	.string "It's supposed to Roar well.$"

Route25_BillsHouse_Text_Pichu:
	.string "Do you know that hugely popular\n"
	.string "Pokémon?\p"
	.string "The Pokémon that has a yellow\n"
	.string "body and red cheeks.\p"
	.string "I would love to see what it\n"
	.string "looks like before it evolves.$"
