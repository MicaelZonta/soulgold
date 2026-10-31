NsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NsRoom_OnTransition
	.byte 0

NsRoom_OnTransition::
	call NsRoom_EventScript_Vis_TEMP_11
	end

NsRoom_EventScript_Vis_TEMP_11::
	goto_if_eq VAR_ABUNDANCE_ISLE_STATE, 11, NsRoom_EventScript_Vis_TEMP_11_Show
NsRoom_EventScript_Vis_TEMP_11_No::
NsRoom_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
NsRoom_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

NsRoom_EventScript_WarpTrigger0::
	warp MAP_EMBERDUNE_ISLE, 4
	waitstate
	end

@ ---------------- fase 2 (.claude/abundance_isle/fase2/NsRoom.inc)
NsRoom_EventScript_N::
	msgbox NsRoom_EventScript_N_Text, MSGBOX_NPC
	end

NsRoom_EventScript_N_Text:
	.string "{SPEAKER NAME_N}I built this room to remember\n"
	.string "the one I grew up in.\p"
	.string "Toys, a train that goes around\n"
	.string "and around... I used to think the\n"
	.string "whole world was this small.$"

NsRoom_EventScript_Hilda::
	msgbox NsRoom_EventScript_Hilda_Text, MSGBOX_NPC
	end

NsRoom_EventScript_Hilda_Text:
	.string "{SPEAKER NAME_HILDA}He won't say it, but he's\n"
	.string "scared. Of Ghetsis. Of the past.\p"
	.string "We'll face it together this time.$"

NsRoom_EventScript_Dolls::
	msgbox NsRoom_EventScript_Dolls_Text, MSGBOX_NPC
	end

NsRoom_EventScript_Dolls_Text:
	.string "A row of old Pokemon dolls,\n"
	.string "lovingly patched up.$"

NsRoom_EventScript_Cushion::
	msgbox NsRoom_EventScript_Cushion_Text, MSGBOX_NPC
	end

NsRoom_EventScript_Cushion_Text:
	.string "A worn cushion. Zorua seems\n"
	.string "to like napping here.$"

NsRoom_EventScript_PC::
	msgbox NsRoom_EventScript_PC_Text, MSGBOX_SIGN
	end

NsRoom_EventScript_PC_Text:
	.string "N's PC. A file is open:\n"
	.string "“Letters I never sent.”$"

NsRoom_EventScript_Bookshelf::
	msgbox NsRoom_EventScript_Bookshelf_Text, MSGBOX_SIGN
	end

NsRoom_EventScript_Bookshelf_Text:
	.string "Books on math, myths and\n"
	.string "the history of Unova.$"

NsRoom_EventScript_ToyTrain::
	msgbox NsRoom_EventScript_ToyTrain_Text, MSGBOX_SIGN
	end

NsRoom_EventScript_ToyTrain_Text:
	.string "A toy train circles the track.\n"
	.string "Round and round, never stopping.$"


