FrostfallCrater_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_ABUNDANCE_FROSTFALL_CRATER_1F_GRUNT_1, FrostfallCrater_1F_EventScript_Grunt1_Text_Seen, FrostfallCrater_1F_EventScript_Grunt1_Text_Beaten
	msgbox FrostfallCrater_1F_EventScript_Grunt1_Text_After, MSGBOX_AUTOCLOSE
	end

FrostfallCrater_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_ABUNDANCE_FROSTFALL_CRATER_1F_GRUNT_2, FrostfallCrater_1F_EventScript_Grunt2_Text_Seen, FrostfallCrater_1F_EventScript_Grunt2_Text_Beaten
	msgbox FrostfallCrater_1F_EventScript_Grunt2_Text_After, MSGBOX_AUTOCLOSE
	end

FrostfallCrater_1F_EventScript_Hiker::
	trainerbattle_single TRAINER_ABUNDANCE_FROSTFALL_CRATER_1F_HIKER, FrostfallCrater_1F_EventScript_Hiker_Text_Seen, FrostfallCrater_1F_EventScript_Hiker_Text_Beaten
	msgbox FrostfallCrater_1F_EventScript_Hiker_Text_After, MSGBOX_AUTOCLOSE
	end

FrostfallCrater_1F_EventScript_Grunt1_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

FrostfallCrater_1F_EventScript_Grunt1_Text_Beaten:
	.string "Wh-what? Our plans...$"

FrostfallCrater_1F_EventScript_Grunt1_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

FrostfallCrater_1F_EventScript_Grunt2_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

FrostfallCrater_1F_EventScript_Grunt2_Text_Beaten:
	.string "Wh-what? Our plans...$"

FrostfallCrater_1F_EventScript_Grunt2_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

FrostfallCrater_1F_EventScript_Hiker_Text_Seen:
	.string "These rocks have been shaking with\nthunder all week! Let's battle!$"

FrostfallCrater_1F_EventScript_Hiker_Text_Beaten:
	.string "Whoa, you've got legs of steel!$"

FrostfallCrater_1F_EventScript_Hiker_Text_After:
	.string "A real hiker never fears a storm.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/FrostfallCrater_1F.inc)
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

