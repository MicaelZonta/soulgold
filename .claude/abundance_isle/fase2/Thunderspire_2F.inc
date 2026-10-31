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

