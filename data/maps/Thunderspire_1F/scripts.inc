Thunderspire_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Thunderspire_1F_OnTransition
	.byte 0

Thunderspire_1F_OnTransition::
	call Thunderspire_1F_EventScript_Vis_TEMP_1A
	call Thunderspire_1F_EventScript_Vis_TEMP_1B
	end

Thunderspire_1F_EventScript_Vis_TEMP_1A::
	goto_if_set FLAG_ABUNDANCE_CANDLE_1, Thunderspire_1F_EventScript_Vis_TEMP_1A_Show
Thunderspire_1F_EventScript_Vis_TEMP_1A_No::
Thunderspire_1F_EventScript_Vis_TEMP_1A_Show_No::
	setflag FLAG_TEMP_1A
	return
Thunderspire_1F_EventScript_Vis_TEMP_1A_Show::
	clearflag FLAG_TEMP_1A
	return

Thunderspire_1F_EventScript_Vis_TEMP_1B::
	goto_if_set FLAG_ABUNDANCE_CANDLE_2, Thunderspire_1F_EventScript_Vis_TEMP_1B_Show
Thunderspire_1F_EventScript_Vis_TEMP_1B_No::
Thunderspire_1F_EventScript_Vis_TEMP_1B_Show_No::
	setflag FLAG_TEMP_1B
	return
Thunderspire_1F_EventScript_Vis_TEMP_1B_Show::
	clearflag FLAG_TEMP_1B
	return

Thunderspire_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_1F_GRUNT_1, Thunderspire_1F_EventScript_Grunt1_Text_Seen, Thunderspire_1F_EventScript_Grunt1_Text_Beaten
	msgbox Thunderspire_1F_EventScript_Grunt1_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_ABUNDANCE_THUNDERSPIRE_1F_GRUNT_2, Thunderspire_1F_EventScript_Grunt2_Text_Seen, Thunderspire_1F_EventScript_Grunt2_Text_Beaten
	msgbox Thunderspire_1F_EventScript_Grunt2_Text_After, MSGBOX_AUTOCLOSE
	end

Thunderspire_1F_EventScript_Grunt1_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_1F_EventScript_Grunt1_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_1F_EventScript_Grunt1_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

Thunderspire_1F_EventScript_Grunt2_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

Thunderspire_1F_EventScript_Grunt2_Text_Beaten:
	.string "Wh-what? Our plans...$"

Thunderspire_1F_EventScript_Grunt2_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/Thunderspire_1F.inc)
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


