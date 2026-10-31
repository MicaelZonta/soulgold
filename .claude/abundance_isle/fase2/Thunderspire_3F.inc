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

