AbundanceIsle_Barn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_Barn_OnTransition
	.byte 0

AbundanceIsle_Barn_OnTransition::
	call AbundanceIsle_Barn_EventScript_Vis_TEMP_11
	end

AbundanceIsle_Barn_EventScript_Vis_TEMP_11::
	goto_if_eq VAR_ABUNDANCE_ROCKET_STAGE, 1, AbundanceIsle_Barn_EventScript_Vis_TEMP_11_Show
AbundanceIsle_Barn_EventScript_Vis_TEMP_11_No::
AbundanceIsle_Barn_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
AbundanceIsle_Barn_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

AbundanceIsle_Barn_EventScript_Miltank::
	lock
	faceplayer
	playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox AbundanceIsle_Barn_EventScript_Miltank_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

AbundanceIsle_Barn_EventScript_Mareep::
	lock
	faceplayer
	playmoncry SPECIES_MAREEP, CRY_MODE_NORMAL
	msgbox AbundanceIsle_Barn_EventScript_Mareep_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

AbundanceIsle_Barn_EventScript_Tauros::
	lock
	faceplayer
	playmoncry SPECIES_TAUROS, CRY_MODE_NORMAL
	msgbox AbundanceIsle_Barn_EventScript_Tauros_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

AbundanceIsle_Barn_EventScript_Farfetchd::
	lock
	faceplayer
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox AbundanceIsle_Barn_EventScript_Farfetchd_Text, MSGBOX_DEFAULT
	waitmoncry
	release
	end

AbundanceIsle_Barn_EventScript_Miltank_Text:
	.string "Miltank!$"

AbundanceIsle_Barn_EventScript_Mareep_Text:
	.string "Mareep!$"

AbundanceIsle_Barn_EventScript_Tauros_Text:
	.string "Tauros!$"

AbundanceIsle_Barn_EventScript_Farfetchd_Text:
	.string "Farfetchd!$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_Barn.inc)
AbundanceIsle_Barn_EventScript_JessieBarn::
	lock
	faceplayer
	msgbox AbundanceIsle_Barn_EventScript_JessieBarn_Text, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_ABUNDANCE_ISLE_BARN_JESSIE
	removeobject LOCALID_ABUNDANCE_ISLE_BARN_JAMES
	setvar VAR_ABUNDANCE_ROCKET_STAGE, 2
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

AbundanceIsle_Barn_EventScript_JessieBarn_Text:
	.string "{SPEAKER NAME_JESSIE}Achoo! This hay is NOT a good\n"
	.string "hiding place!\p"
	.string "{SPEAKER NAME_JAMES}We heard Team Plasma pays well\n"
	.string "for secrets. To their ship!$"

AbundanceIsle_Barn_EventScript_Kid::
	msgbox AbundanceIsle_Barn_EventScript_Kid_Text, MSGBOX_NPC
	end

AbundanceIsle_Barn_EventScript_Kid_Text:
	.string "The Miltank stopped giving milk\n"
	.string "when the snow came.\p"
	.string "Mom says it's too cold. I say\n"
	.string "the Miltank is sad.$"


