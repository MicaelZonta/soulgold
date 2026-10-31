Thunderspire_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Thunderspire_2F_OnTransition
	.byte 0

Thunderspire_2F_OnTransition::
	call Thunderspire_2F_EventScript_Vis_TEMP_1A
	call Thunderspire_2F_EventScript_Vis_TEMP_1B
	end

Thunderspire_2F_EventScript_Vis_TEMP_1A::
	goto_if_set FLAG_ABUNDANCE_CANDLE_3, Thunderspire_2F_EventScript_Vis_TEMP_1A_Show
Thunderspire_2F_EventScript_Vis_TEMP_1A_No::
Thunderspire_2F_EventScript_Vis_TEMP_1A_Show_No::
	setflag FLAG_TEMP_1A
	return
Thunderspire_2F_EventScript_Vis_TEMP_1A_Show::
	clearflag FLAG_TEMP_1A
	return

Thunderspire_2F_EventScript_Vis_TEMP_1B::
	goto_if_set FLAG_ABUNDANCE_CANDLE_4, Thunderspire_2F_EventScript_Vis_TEMP_1B_Show
Thunderspire_2F_EventScript_Vis_TEMP_1B_No::
Thunderspire_2F_EventScript_Vis_TEMP_1B_Show_No::
	setflag FLAG_TEMP_1B
	return
Thunderspire_2F_EventScript_Vis_TEMP_1B_Show::
	clearflag FLAG_TEMP_1B
	return

Thunderspire_2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_2F_GRUNT_3, Thunderspire_2F_EventScript_Grunt3_Text_Seen, Thunderspire_2F_EventScript_Grunt3_Text_Beaten
	msgbox Thunderspire_2F_EventScript_Grunt3_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_2F_GRUNT_4, Thunderspire_2F_EventScript_Grunt4_Text_Seen, Thunderspire_2F_EventScript_Grunt4_Text_Beaten
	msgbox Thunderspire_2F_EventScript_Grunt4_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_2F_EventScript_Grunt3_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_2F_EventScript_Grunt3_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_2F_EventScript_Grunt3_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

Thunderspire_2F_EventScript_Grunt4_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_2F_EventScript_Grunt4_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_2F_EventScript_Grunt4_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/Thunderspire_2F.inc)
Thunderspire_2F_EventScript_Candle3::
	lockall
	goto_if_set FLAG_ABUNDANCE_CANDLE_3, Thunderspire_2F_EventScript_Candle3_Lit
	msgbox Thunderspire_2F_EventScript_Candle3_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_CANDLE_3
	playse SE_M_EMBER
	removeobject LOCALID_THUNDERSPIRE_2F_CANDLE_3
	clearflag FLAG_TEMP_1A
	addobject LOCALID_THUNDERSPIRE_2F_CANDLE_LIT_3
	releaseall
	end

Thunderspire_2F_EventScript_Candle3_Lit::
	msgbox Thunderspire_2F_EventScript_Candle3_TextLit, MSGBOX_DEFAULT
	releaseall
	end

Thunderspire_2F_EventScript_Candle3_Text:
	.string "An old spirit candle. {PLAYER} lit\n"
	.string "it, and the flame burned blue.$"
Thunderspire_2F_EventScript_Candle3_TextLit:
	.string "The blue flame flickers quietly.$"

Thunderspire_2F_EventScript_Candle4::
	lockall
	goto_if_set FLAG_ABUNDANCE_CANDLE_4, Thunderspire_2F_EventScript_Candle4_Lit
	msgbox Thunderspire_2F_EventScript_Candle4_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_CANDLE_4
	playse SE_M_EMBER
	removeobject LOCALID_THUNDERSPIRE_2F_CANDLE_4
	clearflag FLAG_TEMP_1B
	addobject LOCALID_THUNDERSPIRE_2F_CANDLE_LIT_4
	releaseall
	end

Thunderspire_2F_EventScript_Candle4_Lit::
	msgbox Thunderspire_2F_EventScript_Candle4_TextLit, MSGBOX_DEFAULT
	releaseall
	end

Thunderspire_2F_EventScript_Candle4_Text:
	.string "An old spirit candle. {PLAYER} lit\n"
	.string "it, and the flame burned blue.$"
Thunderspire_2F_EventScript_Candle4_TextLit:
	.string "The blue flame flickers quietly.$"

Thunderspire_2F_EventScript_Alister::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_CANDLES_DONE, Thunderspire_2F_EventScript_Alister_After
	goto_if_unset FLAG_ABUNDANCE_CANDLE_1, Thunderspire_2F_EventScript_Alister_Ask
	goto_if_unset FLAG_ABUNDANCE_CANDLE_2, Thunderspire_2F_EventScript_Alister_Ask
	goto_if_unset FLAG_ABUNDANCE_CANDLE_3, Thunderspire_2F_EventScript_Alister_Ask
	goto_if_unset FLAG_ABUNDANCE_CANDLE_4, Thunderspire_2F_EventScript_Alister_Ask
	msgbox Thunderspire_2F_EventScript_Alister_TextDone, MSGBOX_DEFAULT
	checkitemspace ITEM_REAPER_CLOTH
	goto_if_eq VAR_RESULT, FALSE, Thunderspire_2F_EventScript_Alister_BagFull
	giveitem ITEM_REAPER_CLOTH
	setflag FLAG_ABUNDANCE_CANDLES_DONE
	release
	end

Thunderspire_2F_EventScript_Alister_Ask::
	msgbox Thunderspire_2F_EventScript_Alister_TextAsk, MSGBOX_DEFAULT
	release
	end

Thunderspire_2F_EventScript_Alister_After::
	msgbox Thunderspire_2F_EventScript_Alister_TextAfter, MSGBOX_DEFAULT
	release
	end

Thunderspire_2F_EventScript_Alister_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

Thunderspire_2F_EventScript_Alister_TextAsk:
	.string "{SPEAKER NAME_ALLISTER}B-boo... sorry. The ghosts here\n"
	.string "are lonely.\p"
	.string "Four spirit candles went out in\n"
	.string "this tower. Could you light them?$"
Thunderspire_2F_EventScript_Alister_TextDone:
	.string "{SPEAKER NAME_ALLISTER}All four... I can see him now.\n"
	.string "The builder who carried the Dark\n"
	.string "Stone here. He's smiling.\p"
	.string "Th-thank you. Take this.$"
Thunderspire_2F_EventScript_Alister_TextAfter:
	.string "{SPEAKER NAME_ALLISTER}The tower feels warmer now.$"


