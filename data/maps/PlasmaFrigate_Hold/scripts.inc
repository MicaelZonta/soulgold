PlasmaFrigate_Hold_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PlasmaFrigate_Hold_OnTransition
	.byte 0

PlasmaFrigate_Hold_OnTransition::
	call PlasmaFrigate_Hold_EventScript_Vis_TEMP_11
	end

PlasmaFrigate_Hold_EventScript_Vis_TEMP_11::
	goto_if_unset FLAG_ABUNDANCE_PLASMA_UNIFORM, PlasmaFrigate_Hold_EventScript_Vis_TEMP_11_Show
PlasmaFrigate_Hold_EventScript_Vis_TEMP_11_No::
PlasmaFrigate_Hold_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
PlasmaFrigate_Hold_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

PlasmaFrigate_Hold_EventScript_Researcher::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_HOLD_RESEARCHER, PlasmaFrigate_Hold_EventScript_Researcher_Text_Seen, PlasmaFrigate_Hold_EventScript_Researcher_Text_Beaten
	msgbox PlasmaFrigate_Hold_EventScript_Researcher_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Hold_EventScript_Grunt4::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_HOLD_GRUNT_BUNK_1, PlasmaFrigate_Hold_EventScript_Grunt4_Text_Seen, PlasmaFrigate_Hold_EventScript_Grunt4_Text_Beaten
	msgbox PlasmaFrigate_Hold_EventScript_Grunt4_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Hold_EventScript_Grunt5::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_HOLD_GRUNT_BUNK_2, PlasmaFrigate_Hold_EventScript_Grunt5_Text_Seen, PlasmaFrigate_Hold_EventScript_Grunt5_Text_Beaten
	msgbox PlasmaFrigate_Hold_EventScript_Grunt5_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Hold_EventScript_Grunt6::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_HOLD_GRUNT_HALL, PlasmaFrigate_Hold_EventScript_Grunt6_Text_Seen, PlasmaFrigate_Hold_EventScript_Grunt6_Text_Beaten
	msgbox PlasmaFrigate_Hold_EventScript_Grunt6_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Hold_EventScript_Researcher_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Hold_EventScript_Researcher_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Hold_EventScript_Researcher_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_Hold_EventScript_Grunt4_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Hold_EventScript_Grunt4_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Hold_EventScript_Grunt4_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_Hold_EventScript_Grunt5_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Hold_EventScript_Grunt5_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Hold_EventScript_Grunt5_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_Hold_EventScript_Grunt6_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Hold_EventScript_Grunt6_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Hold_EventScript_Grunt6_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/PlasmaFrigate_Hold.inc)
PlasmaFrigate_Hold_EventScript_EngineGuard::
	msgbox PlasmaFrigate_Hold_EventScript_EngineGuard_Text, MSGBOX_NPC
	end

PlasmaFrigate_Hold_EventScript_EngineGuard_Text:
	.string "{SPEAKER NAME_GRUNT}Engine room is for crew only!\n"
	.string "Where's your uniform?$"


