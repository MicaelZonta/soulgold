@ Heart & Soul interactions: flavor text for new metatile behaviors, ported from pokehns 2.0.6.
@ Dispatched from GetInteractedMetatileScript / GetInteractedWaterScript (src/field_control_avatar.c).
@ Pending (needs script command `checkpartymove`, absent here): EventScript_Headbutt for MB_HEADBUTT_TREE.

EventScript_Kitchen::
	msgbox Text_Kitchen, MSGBOX_SIGN
	end

EventScript_Dresser::
	msgbox Text_Dresser, MSGBOX_SIGN
	end

EventScript_Blueprints::
	msgbox Text_Blueprints, MSGBOX_SIGN
	end

EventScript_Painting::
	msgbox Text_Painting, MSGBOX_SIGN
	end

EventScript_PowerPlantMachine::
	msgbox Text_PowerPlantMachine, MSGBOX_SIGN
	end

EventScript_Telephone::
	msgbox Text_Telephone, MSGBOX_SIGN
	end

EventScript_AdvertisingPoster::
	msgbox Text_AdvertisingPoster, MSGBOX_SIGN
	end

EventScript_Cup::
	msgbox Text_Cup, MSGBOX_SIGN
	end

EventScript_NeatlyLinedUpTools::
	msgbox Text_NeatlyLinedUpTools, MSGBOX_SIGN
	end

EventScript_ImpressiveMachine::
	msgbox Text_ImpressiveMachine, MSGBOX_SIGN
	end

EventScript_VideoGame::
	msgbox Text_VideoGame, MSGBOX_SIGN
	end

EventScript_Burglary::
	msgbox Text_Burglary, MSGBOX_SIGN
	end

EventScript_Indigo_UltimateGoal::
	msgbox Text_Indigo_UltimateGoal, MSGBOX_SIGN
	end

EventScript_Indigo_HighestAuthority::
	msgbox Text_Indigo_HighestAuthority, MSGBOX_SIGN
	end

EventScript_CurrentTooFast::
	lockall
	checkfieldmove FIELD_MOVE_SURF
	goto_if_eq VAR_RESULT, FALSE, EventScript_CurrentTooFastEndMsg
	playse SE_SELECT
	msgbox Text_CurrentTooFast
EventScript_CurrentTooFastEndMsg::
	releaseall
	end

Text_Kitchen::
	.string "It smells delicious!\n"
	.string "Somebody's been cooking here.$"

Text_Dresser::
	.string "It's a nicely made dresser.\n"
	.string "It will hold a lot of stuff.$"

Text_Blueprints::
	.string "It's a blueprint of some sort.\n"
	.string "It's filled with diagrams and text.$"

Text_Painting::
	.string "It's a pretty picture of a POKéMON.\n"
	.string "It looks like it's feeling good.$"

Text_PowerPlantMachine::
	.string "What could this machine be?\n"
	.string "Better not mess around with it!$"

Text_Telephone::
	.string "It's a telephone.\n"
	.string "Better not use it.$"

Text_AdvertisingPoster::
	.string "It's an advertising poster about\n"
	.string "all kinds of products.$"

Text_Cup::
	.string "It's a cup with a POKéMON mark\n"
	.string "on it.$"

Text_NeatlyLinedUpTools::
	.string "All sorts of tools are lined up\n"
	.string "neatly.$"

Text_ImpressiveMachine::
	.string "It's a machine of some sort.\n"
	.string "It sure is impressive.$"

Text_VideoGame::
	.string "It's the latest video game!\n"
	.string "It sure looks fun!$"

Text_Burglary::
	.string "There are obvious signs of burglary\n"
	.string "here…$"

Text_Indigo_UltimateGoal::
	.string "INDIGO PLATEAU\p"
	.string "The ultimate goal of TRAINERS!\n"
	.string "POKéMON LEAGUE HQ$"

Text_Indigo_HighestAuthority::
	.string "INDIGO PLATEAU\p"
	.string "The highest POKéMON authority!\n"
	.string "POKéMON LEAGUE HQ$"

@ Interact with a headbutt tree (MB_HEADBUTT_TREE). Encounters reuse the map's
@ rock smash table, like in HnS.
EventScript_Headbutt::
	lockall
	goto_if_unset FLAG_GET_HEADBUTT, EventScript_CantHeadbuttTree
	checkpartymove MOVE_HEADBUTT
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantHeadbuttTree
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	msgbox Text_MonUsedHeadbutt, MSGBOX_DEFAULT
	closemessage
	isfollowerfieldmoveuser VAR_0x8004
EventScript_HeadbuttTree::
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
	applymovement VAR_LAST_TALKED, Movement_HeadbuttTree
	playse SE_M_HEADBUTT
	waitmovement 0
	special RockSmashWildEncounter
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndHeadbutt
	waitstate
	releaseall
	end

EventScript_EndHeadbutt::
	releaseall
	end

Movement_HeadbuttTree:
	rock_smash_break
	step_end

EventScript_CantHeadbuttTree::
	msgbox Text_CantHeadbutt, MSGBOX_DEFAULT
	releaseall
	end

Text_MonUsedHeadbutt::
	.string "{STR_VAR_1} used HEADBUTT!$"

Text_CantHeadbutt::
	.string "It's a small tree, but a wild\n"
	.string "POKéMON may be living within.$"
