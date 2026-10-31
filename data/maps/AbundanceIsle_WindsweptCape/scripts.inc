AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_11::
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_11_Show
AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_11_No::
AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E::
	gettime
	goto_if_lt VAR_0x8000, 6, AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E_Show_No
	goto_if_lt VAR_0x8000, 20, AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E_Show
AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E_No::
AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E_Show_No::
	setflag FLAG_TEMP_1E
	return
AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E_Show::
	clearflag FLAG_TEMP_1E
	return

AbundanceIsle_WindsweptCape_EventScript_Youngster::
	trainerbattle_single TRAINER_ABUNDANCE_WINDSWEPT_CAPE_BIRDKEEPER, AbundanceIsle_WindsweptCape_EventScript_Youngster_Text_Seen, AbundanceIsle_WindsweptCape_EventScript_Youngster_Text_Beaten
	msgbox AbundanceIsle_WindsweptCape_EventScript_Youngster_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_WindsweptCape_EventScript_Fisherman::
	trainerbattle_single TRAINER_ABUNDANCE_WINDSWEPT_CAPE_FISHERMAN, AbundanceIsle_WindsweptCape_EventScript_Fisherman_Text_Seen, AbundanceIsle_WindsweptCape_EventScript_Fisherman_Text_Beaten
	msgbox AbundanceIsle_WindsweptCape_EventScript_Fisherman_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_WindsweptCape_EventScript_WarpTrigger1::
	warp MAP_PLASMA_FRIGATE_DECK, 0
	waitstate
	end

AbundanceIsle_WindsweptCape_EventScript_Youngster_Text_Seen:
	.string "My birds can't fly in these winds!\nBut they can still battle!$"

AbundanceIsle_WindsweptCape_EventScript_Youngster_Text_Beaten:
	.string "Grounded...$"

AbundanceIsle_WindsweptCape_EventScript_Youngster_Text_After:
	.string "When the winds calm down, we'll\nsoar again.$"

AbundanceIsle_WindsweptCape_EventScript_Fisherman_Text_Seen:
	.string "The fish here bite even in this\nweird weather. You, too?$"

AbundanceIsle_WindsweptCape_EventScript_Fisherman_Text_Beaten:
	.string "Snapped my line!$"

AbundanceIsle_WindsweptCape_EventScript_Fisherman_Text_After:
	.string "The sea always gives something back.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_WindsweptCape.inc)
AbundanceIsle_WindsweptCape_EventScript_Seed5::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_5, AbundanceIsle_WindsweptCape_EventScript_Seed5_Empty
	msgbox AbundanceIsle_WindsweptCape_EventScript_Seed5_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_5
	removeobject LOCALID_ABUNDANCE_ISLE_WINDSWEPT_CAPE_SEED_5
	releaseall
	end

AbundanceIsle_WindsweptCape_EventScript_Seed5_Empty::
	msgbox AbundanceIsle_WindsweptCape_EventScript_Seed5_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_WindsweptCape_EventScript_Seed5_Text:
	.string "A sack of seeds blown here by the\n"
	.string "storm!\p"
	.string "{PLAYER} took the sack to return\n"
	.string "it to the farm.$"
AbundanceIsle_WindsweptCape_EventScript_Seed5_TextEmpty:
	.string "Nothing here but a few stray\n"
	.string "seeds.$"

AbundanceIsle_WindsweptCape_EventScript_DoorLocked::
	msgbox AbundanceIsle_WindsweptCape_EventScript_DoorLocked_Text, MSGBOX_SIGN
	end

AbundanceIsle_WindsweptCape_EventScript_DoorLocked_Text:
	.string "The door is locked. Everyone in\n"
	.string "the village has gone home for\n"
	.string "the night.$"

AbundanceIsle_WindsweptCape_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_WindsweptCape_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AbundanceIsle_WindsweptCape_OnFrame
	.byte 0

AbundanceIsle_WindsweptCape_OnTransition::
	call AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_11
	call AbundanceIsle_WindsweptCape_EventScript_Vis_TEMP_1E
	end

AbundanceIsle_WindsweptCape_OnFrame::
	map_script_2 VAR_TEMP_1, 0, AbundanceIsle_WindsweptCape_EventScript_Bell
	.2byte 0

AbundanceIsle_WindsweptCape_EventScript_Bell::
	setvar VAR_TEMP_1, 1
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_WindsweptCape_EventScript_BellEnd
	gettime
	goto_if_ne VAR_0x8000, 18, AbundanceIsle_WindsweptCape_EventScript_BellEnd
	lockall
	playse SE_M_HEAL_BELL
	waitse
	msgbox AbundanceIsle_WindsweptCape_Text_Bell, MSGBOX_DEFAULT
	releaseall
AbundanceIsle_WindsweptCape_EventScript_BellEnd::
	end

AbundanceIsle_WindsweptCape_Text_Bell:
	.string "Ding... dong...\p"
	.string "The harvest bell rings across the\n"
	.string "village. Time to come home.$"

AbundanceIsle_WindsweptCape_EventScript_DockGuard1::
	msgbox AbundanceIsle_WindsweptCape_EventScript_DockGuard1_Text, MSGBOX_NPC
	end

AbundanceIsle_WindsweptCape_EventScript_DockGuard1_Text:
	.string "{SPEAKER NAME_GRUNT}This dock belongs to Team Plasma\n"
	.string "now! Go back the way you came!$"

AbundanceIsle_WindsweptCape_EventScript_DockGuard2::
	msgbox AbundanceIsle_WindsweptCape_EventScript_DockGuard2_Text, MSGBOX_NPC
	end

AbundanceIsle_WindsweptCape_EventScript_DockGuard2_Text:
	.string "{SPEAKER NAME_GRUNT}Our frigate is anchored here\n"
	.string "for the liberation of Pokemon!$"

AbundanceIsle_WindsweptCape_EventScript_DockGuard3::
	msgbox AbundanceIsle_WindsweptCape_EventScript_DockGuard3_Text, MSGBOX_NPC
	end

AbundanceIsle_WindsweptCape_EventScript_DockGuard3_Text:
	.string "{SPEAKER NAME_GRUNT}Lord Ghetsis will make the winter\n"
	.string "last forever. Shiver all you like!$"

AbundanceIsle_WindsweptCape_EventScript_Nessa::
	msgbox AbundanceIsle_WindsweptCape_EventScript_Nessa_Text, MSGBOX_NPC
	end

AbundanceIsle_WindsweptCape_EventScript_Nessa_Text:
	.string "{SPEAKER NAME_NESSA}The sea around this cape is\n"
	.string "wild. The wind spins in circles.\p"
	.string "Even my Drednaw doesn't like\n"
	.string "swimming here.$"

AbundanceIsle_WindsweptCape_EventScript_Skyla::
	msgbox AbundanceIsle_WindsweptCape_EventScript_Skyla_Text, MSGBOX_NPC
	end

AbundanceIsle_WindsweptCape_EventScript_Skyla_Text:
	.string "{SPEAKER NAME_SKYLA}From up here you can see the\n"
	.string "storm turning around the crater.\p"
	.string "Like the whole sky is being\n"
	.string "pulled toward it...$"

AbundanceIsle_WindsweptCape_EventScript_Sailor::
	msgbox AbundanceIsle_WindsweptCape_EventScript_Sailor_Text, MSGBOX_NPC
	end

AbundanceIsle_WindsweptCape_EventScript_Sailor_Text:
	.string "The ferry won't sail while that\n"
	.string "Plasma ship blocks the dock.$"


