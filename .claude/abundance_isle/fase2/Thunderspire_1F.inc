Thunderspire_1F_EventScript_Stele3::
	lockall
	goto_if_set FLAG_ABUNDANCE_STELE_3, Thunderspire_1F_EventScript_Stele3_Done
	msgbox Thunderspire_1F_EventScript_Stele3_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STELE_3
	msgbox Thunderspire_1F_EventScript_Stele3_TextRub, MSGBOX_DEFAULT
	releaseall
	end

Thunderspire_1F_EventScript_Stele3_Done::
	msgbox Thunderspire_1F_EventScript_Stele3_Text, MSGBOX_DEFAULT
	releaseall
	end

Thunderspire_1F_EventScript_Stele3_Text:
	.string "A fragment of an old stele.\p"
	.string "“...the Lord of the Fertile Land\n"
	.string "came down only when both stood\n"
	.string "before it together...”$"
Thunderspire_1F_EventScript_Stele3_TextRub:
	.string "{PLAYER} made a rubbing of the\n"
	.string "fragment for Lenora.$"

Thunderspire_1F_EventScript_Candle1::
	lockall
	goto_if_set FLAG_ABUNDANCE_CANDLE_1, Thunderspire_1F_EventScript_Candle1_Lit
	msgbox Thunderspire_1F_EventScript_Candle1_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_CANDLE_1
	playse SE_M_EMBER
	removeobject LOCALID_THUNDERSPIRE_1F_CANDLE_1
	clearflag FLAG_TEMP_1A
	addobject LOCALID_THUNDERSPIRE_1F_CANDLE_LIT_1
	releaseall
	end

Thunderspire_1F_EventScript_Candle1_Lit::
	msgbox Thunderspire_1F_EventScript_Candle1_TextLit, MSGBOX_DEFAULT
	releaseall
	end

Thunderspire_1F_EventScript_Candle1_Text:
	.string "An old spirit candle. {PLAYER} lit\n"
	.string "it, and the flame burned blue.$"
Thunderspire_1F_EventScript_Candle1_TextLit:
	.string "The blue flame flickers quietly.$"

Thunderspire_1F_EventScript_Candle2::
	lockall
	goto_if_set FLAG_ABUNDANCE_CANDLE_2, Thunderspire_1F_EventScript_Candle2_Lit
	msgbox Thunderspire_1F_EventScript_Candle2_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_CANDLE_2
	playse SE_M_EMBER
	removeobject LOCALID_THUNDERSPIRE_1F_CANDLE_2
	clearflag FLAG_TEMP_1B
	addobject LOCALID_THUNDERSPIRE_1F_CANDLE_LIT_2
	releaseall
	end

Thunderspire_1F_EventScript_Candle2_Lit::
	msgbox Thunderspire_1F_EventScript_Candle2_TextLit, MSGBOX_DEFAULT
	releaseall
	end

Thunderspire_1F_EventScript_Candle2_Text:
	.string "An old spirit candle. {PLAYER} lit\n"
	.string "it, and the flame burned blue.$"
Thunderspire_1F_EventScript_Candle2_TextLit:
	.string "The blue flame flickers quietly.$"

Thunderspire_1F_EventScript_Cheren::
	msgbox Thunderspire_1F_EventScript_Cheren_Text, MSGBOX_NPC
	end

Thunderspire_1F_EventScript_Cheren_Text:
	.string "{SPEAKER NAME_CHEREN}The Plasma are guarding the\n"
	.string "stairs. Something is up there.\p"
	.string "Be careful. I'll keep these\n"
	.string "grunts busy down here.$"

