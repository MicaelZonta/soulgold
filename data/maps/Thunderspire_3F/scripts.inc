Thunderspire_3F_MapScripts::
	.byte 0

Thunderspire_3F_EventScript_Grunt5::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_3F_GRUNT_1, Thunderspire_3F_EventScript_Grunt5_Text_Seen, Thunderspire_3F_EventScript_Grunt5_Text_Beaten
	msgbox Thunderspire_3F_EventScript_Grunt5_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_3F_EventScript_Grunt6::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_3F_GRUNT_2, Thunderspire_3F_EventScript_Grunt6_Text_Seen, Thunderspire_3F_EventScript_Grunt6_Text_Beaten
	msgbox Thunderspire_3F_EventScript_Grunt6_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_3F_EventScript_Grunt7::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_3F_GRUNT_3, Thunderspire_3F_EventScript_Grunt7_Text_Seen, Thunderspire_3F_EventScript_Grunt7_Text_Beaten
	msgbox Thunderspire_3F_EventScript_Grunt7_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_3F_EventScript_Grunt5_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_3F_EventScript_Grunt5_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_3F_EventScript_Grunt5_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

Thunderspire_3F_EventScript_Grunt6_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_3F_EventScript_Grunt6_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_3F_EventScript_Grunt6_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

Thunderspire_3F_EventScript_Grunt7_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_3F_EventScript_Grunt7_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_3F_EventScript_Grunt7_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/Thunderspire_3F.inc)
Thunderspire_3F_EventScript_ToggleA::
	goto_if_set FLAG_TEMP_15, Thunderspire_3F_EventScript_CloseA
	setflag FLAG_TEMP_15
	setmetatile 6, 16, 0x400, FALSE
	return
Thunderspire_3F_EventScript_CloseA::
	clearflag FLAG_TEMP_15
	setmetatile 6, 16, 0x407, TRUE
	return

Thunderspire_3F_EventScript_ToggleB::
	goto_if_set FLAG_TEMP_16, Thunderspire_3F_EventScript_CloseB
	setflag FLAG_TEMP_16
	setmetatile 14, 12, 0x400, FALSE
	return
Thunderspire_3F_EventScript_CloseB::
	clearflag FLAG_TEMP_16
	setmetatile 14, 12, 0x407, TRUE
	return

Thunderspire_3F_EventScript_ToggleC::
	goto_if_set FLAG_TEMP_17, Thunderspire_3F_EventScript_CloseC
	setflag FLAG_TEMP_17
	setmetatile 20, 9, 0x400, FALSE
	return
Thunderspire_3F_EventScript_CloseC::
	clearflag FLAG_TEMP_17
	setmetatile 20, 9, 0x407, TRUE
	return

Thunderspire_3F_EventScript_ToggleD::
	goto_if_set FLAG_TEMP_18, Thunderspire_3F_EventScript_CloseD
	setflag FLAG_TEMP_18
	setmetatile 17, 6, 0x400, FALSE
	return
Thunderspire_3F_EventScript_CloseD::
	clearflag FLAG_TEMP_18
	setmetatile 17, 6, 0x407, TRUE
	return

Thunderspire_3F_EventScript_RodEarth::
	lockall
	msgbox Thunderspire_3F_EventScript_RodEarth_Text, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	call Thunderspire_3F_EventScript_ToggleA
	special DrawWholeMapView
	releaseall
	end

Thunderspire_3F_EventScript_RodEarth_Text:
	.string "{PLAYER} touched the lightning rod.\n"
	.string "Thunder rumbles through the tower!$"

Thunderspire_3F_EventScript_RodWind::
	lockall
	msgbox Thunderspire_3F_EventScript_RodWind_Text, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	call Thunderspire_3F_EventScript_ToggleA
	call Thunderspire_3F_EventScript_ToggleB
	special DrawWholeMapView
	releaseall
	end

Thunderspire_3F_EventScript_RodWind_Text:
	.string "{PLAYER} touched the lightning rod.\n"
	.string "Thunder rumbles through the tower!$"

Thunderspire_3F_EventScript_RodThunder::
	lockall
	msgbox Thunderspire_3F_EventScript_RodThunder_Text, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	call Thunderspire_3F_EventScript_ToggleB
	call Thunderspire_3F_EventScript_ToggleC
	special DrawWholeMapView
	releaseall
	end

Thunderspire_3F_EventScript_RodThunder_Text:
	.string "{PLAYER} touched the lightning rod.\n"
	.string "Thunder rumbles through the tower!$"

Thunderspire_3F_EventScript_RodIdeal::
	lockall
	msgbox Thunderspire_3F_EventScript_RodIdeal_Text, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	call Thunderspire_3F_EventScript_ToggleC
	call Thunderspire_3F_EventScript_ToggleD
	special DrawWholeMapView
	releaseall
	end

Thunderspire_3F_EventScript_RodIdeal_Text:
	.string "{PLAYER} touched the lightning rod.\n"
	.string "Thunder rumbles through the tower!$"

Thunderspire_3F_EventScript_Mural::
	msgbox Thunderspire_3F_EventScript_Mural_Text, MSGBOX_SIGN
	end

Thunderspire_3F_EventScript_Mural_Text:
	.string "“First the earth wakes, then the\n"
	.string "wind rises, then the thunder falls;\n"
	.string "only then may the ideal be struck.”$"


