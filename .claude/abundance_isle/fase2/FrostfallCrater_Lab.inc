FrostfallCrater_Lab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FrostfallCrater_Lab_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, FrostfallCrater_Lab_OnLoad
	.byte 0

FrostfallCrater_Lab_OnTransition::
	call FrostfallCrater_Lab_EventScript_Vis_TEMP_11
	call FrostfallCrater_Lab_EventScript_Vis_TEMP_12
	end

FrostfallCrater_Lab_OnLoad::
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_Lab_EventScript_Melt
	end

FrostfallCrater_Lab_EventScript_Melt::
	setmetatile 28, 13, 0x459, FALSE
	setmetatile 29, 13, 0x459, FALSE
	return

@ Cena 5: o plano do Ghetsis
FrostfallCrater_Lab_EventScript_Ghetsis::
	lock
	faceplayer
	msgbox FrostfallCrater_Lab_Text_GhetsisPlan, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GHETSIS_1, FrostfallCrater_Lab_Text_GhetsisBeaten
	msgbox FrostfallCrater_Lab_Text_GhetsisFlee, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_FROSTFALL_CRATER_LAB_GHETSIS
	removeobject LOCALID_FROSTFALL_CRATER_LAB_SCIENTIST_A
	removeobject LOCALID_FROSTFALL_CRATER_LAB_SCIENTIST_B
	call_if_lt VAR_ABUNDANCE_ISLE_STATE, 3, FrostfallCrater_Lab_EventScript_SetBeaten
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

FrostfallCrater_Lab_EventScript_SetBeaten::
	setvar VAR_ABUNDANCE_ISLE_STATE, 3
	return

@ Cena 6: desligar a maquina
FrostfallCrater_Lab_EventScript_Machine::
	lockall
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_Lab_EventScript_MachineOff
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 3, FrostfallCrater_Lab_EventScript_MachineGuarded
	msgbox FrostfallCrater_Lab_Text_MachineShutdown, MSGBOX_DEFAULT
	closemessage
	playse SE_M_BLIZZARD
	setflag FLAG_TEMP_12
	setvar VAR_ABUNDANCE_ISLE_STATE, 4
	call FrostfallCrater_Lab_EventScript_Melt
	special DrawWholeMapView
	msgbox FrostfallCrater_Lab_Text_SnowStops, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Lab_EventScript_MachineGuarded::
	msgbox FrostfallCrater_Lab_Text_MachineHum, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Lab_EventScript_MachineOff::
	msgbox FrostfallCrater_Lab_Text_MachineSilent, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Lab_Text_GhetsisPlan:
	.string "{SPEAKER NAME_GHETSIS}So, a child has wandered into my\n"
	.string "laboratory.\p"
	.string "Behold. A fragment of the meteor\n"
	.string "that carried Kyurem to this world.\n"
	.string "Its cold is endless.\p"
	.string "Cold air against a warm sea makes\n"
	.string "storms without end. The genies go\n"
	.string "mad, and their lightning gathers.\p"
	.string "That lightning will wake the Dark\n"
	.string "Stone. With Zekrom and Kyurem\n"
	.string "joined, no one will defy me!$"
FrostfallCrater_Lab_Text_GhetsisBeaten:
	.string "Ghetsis: Impossible! You...\n"
	.string "insignificant...!$"
FrostfallCrater_Lab_Text_GhetsisFlee:
	.string "{SPEAKER NAME_GHETSIS}It hardly matters. The storm has\n"
	.string "done its work.\p"
	.string "I go to the summit. The Dark\n"
	.string "Stone will answer to me!$"
FrostfallCrater_Lab_Text_MachineShutdown:
	.string "You pulled the main lever.\n"
	.string "The machine groans and falls\n"
	.string "silent...$"
FrostfallCrater_Lab_Text_SnowStops:
	.string "Somewhere far above, the snow\n"
	.string "stops falling.$"
FrostfallCrater_Lab_Text_MachineHum:
	.string "The machine hums with a terrible\n"
	.string "cold. Ghetsis is in the way.$"
FrostfallCrater_Lab_Text_MachineSilent:
	.string "The machine is silent. The meteor\n"
	.string "fragment glows faintly.$"
FrostfallCrater_Lab_EventScript_N::
	lock
	faceplayer
	msgbox FrostfallCrater_Lab_EventScript_N_Text, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_Lab_EventScript_N_Text:
	.string "{SPEAKER NAME_N}This stone came from beyond the\n"
	.string "sky. Kyurem was born of it...\n"
	.string "or of what remained of a dragon.\p"
	.string "The genies fell from the storm.\n"
	.string "One crashed on the northern shore,\n"
	.string "the other on the thunder ridge.$"

FrostfallCrater_Lab_EventScript_ScientistA::
	msgbox FrostfallCrater_Lab_EventScript_ScientistA_Text, MSGBOX_NPC
	end

FrostfallCrater_Lab_EventScript_ScientistA_Text:
	.string "{SPEAKER NAME_SCIENTIST}The meteor's cold is limitless!\n"
	.string "With it, Kyurem can be controlled!$"

FrostfallCrater_Lab_EventScript_ScientistB::
	msgbox FrostfallCrater_Lab_EventScript_ScientistB_Text, MSGBOX_NPC
	end

FrostfallCrater_Lab_EventScript_ScientistB_Text:
	.string "{SPEAKER NAME_SCIENTIST}The machine splits the DNA of the\n"
	.string "ice dragon... in theory.$"

