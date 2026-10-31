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

