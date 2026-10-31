FrostfallCrater_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FrostfallCrater_1F_OnLoad
	.byte 0

FrostfallCrater_1F_OnLoad::
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_1F_EventScript_Melt
	end

FrostfallCrater_1F_EventScript_Melt::
	setmetatile 25, 3, 0x459, FALSE
	setmetatile 26, 3, 0x459, FALSE
	return

FrostfallCrater_1F_EventScript_Lorelei::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_1F_EventScript_LoreleiAfter
	msgbox FrostfallCrater_1F_Text_Lorelei, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_1F_EventScript_LoreleiAfter::
	msgbox FrostfallCrater_1F_Text_LoreleiAfter, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_1F_Text_Lorelei:
	.string "{SPEAKER NAME_LORELEI}This isn't ice.\p"
	.string "It's something drinking the\n"
	.string "warmth out of the whole island.\n"
	.string "It's coming from deeper inside.$"
FrostfallCrater_1F_Text_LoreleiAfter:
	.string "{SPEAKER NAME_LORELEI}The cold is fading. Whatever you\n"
	.string "did down there, it worked.$"
