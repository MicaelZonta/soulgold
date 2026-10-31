Thunderspire_Summit_EventScript_Ghetsis::
Thunderspire_Summit_EventScript_N::
	lock
	faceplayer
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 5, Thunderspire_Summit_EventScript_TooEarly
	msgbox Thunderspire_Summit_Text_Climax, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GHETSIS_2, Thunderspire_Summit_Text_GhetsisBeaten
	msgbox Thunderspire_Summit_Text_StoneWakes, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_TEMP_11
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_GHETSIS
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_N
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_TORNADUS_SKY
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_THUNDURUS_SKY
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_DARK_STONE
	clearflag FLAG_TEMP_12
	addobject LOCALID_THUNDERSPIRE_SUMMIT_ZEKROM
	addobject LOCALID_THUNDERSPIRE_SUMMIT_N_AFTER
	addobject LOCALID_THUNDERSPIRE_SUMMIT_HILDA_AFTER
	setvar VAR_ABUNDANCE_ISLE_STATE, 6
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox Thunderspire_Summit_Text_ZekromRefuses, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_TooEarly::
	msgbox Thunderspire_Summit_Text_TooEarly, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_Text_TooEarly:
	.string "The black stone is cold and\n"
	.string "silent.$"
Thunderspire_Summit_Text_Climax:
	.string "{SPEAKER NAME_GHETSIS}You again! Stand aside, N. The\n"
	.string "Dark Stone will obey ME!\p"
	.string "{SPEAKER NAME_N}No. Zekrom chooses its own hero.\n"
	.string "It will never choose you.\p"
	.string "{SPEAKER NAME_GHETSIS}Then I will crush the child who\n"
	.string "keeps getting in my way!$"
Thunderspire_Summit_Text_GhetsisBeaten:
	.string "Ghetsis: No... NO!$"
Thunderspire_Summit_Text_StoneWakes:
	.string "Lightning strikes the altar!\n"
	.string "The Dark Stone splits open...$"
Thunderspire_Summit_Text_ZekromRefuses:
	.string "Zekrom roared at Ghetsis, and he\n"
	.string "fled down the tower in terror.\p"
	.string "{SPEAKER NAME_N}It wants to know your ideals,\n"
	.string "{PLAYER}. Show it who you are.$"
Thunderspire_Summit_EventScript_Zekrom::
	lock
	faceplayer
	msgbox Thunderspire_Summit_EventScript_Zekrom_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_ZEKROM, 75, LOCALID_THUNDERSPIRE_SUMMIT_ZEKROM, FLAG_TEMP_12, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Thunderspire_Summit_EventScript_Zekrom_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Thunderspire_Summit_EventScript_Zekrom_Beaten
	release
	end

Thunderspire_Summit_EventScript_Zekrom_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_12
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_ZEKROM
	fadescreenswapbuffers FADE_FROM_BLACK
Thunderspire_Summit_EventScript_Zekrom_Done:
	setflag FLAG_ABUNDANCE_ZEKROM_DONE
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 99, Thunderspire_Summit_EventScript_Zekrom_Advance
	release
	end

Thunderspire_Summit_EventScript_Zekrom_Advance:
	setvar VAR_ABUNDANCE_ISLE_STATE, 99
	return

Thunderspire_Summit_EventScript_Zekrom_Text_Intro:
	.string "Zekrom's eyes burn with\n"
	.string "lightning. It wants to test you!$"

@ N entrega os DNA Splicers (cena 12)
Thunderspire_Summit_EventScript_NAfter::
	lock
	faceplayer
	goto_if_unset FLAG_ABUNDANCE_ZEKROM_DONE, Thunderspire_Summit_EventScript_NWaitZekrom
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 7, Thunderspire_Summit_EventScript_NDone
	msgbox Thunderspire_Summit_Text_NSplicers, MSGBOX_DEFAULT
	checkitemspace ITEM_DNA_SPLICERS
	goto_if_eq VAR_RESULT, FALSE, Thunderspire_Summit_EventScript_NBagFull
	giveitem ITEM_DNA_SPLICERS
	setvar VAR_ABUNDANCE_ISLE_STATE, 7
	msgbox Thunderspire_Summit_Text_NAfterSplicers, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_NBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_NWaitZekrom::
	msgbox Thunderspire_Summit_Text_NWait, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_NDone::
	msgbox Thunderspire_Summit_Text_NAfterSplicers, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_Text_NWait:
	.string "{SPEAKER NAME_N}Zekrom is waiting for you.$"
Thunderspire_Summit_Text_NSplicers:
	.string "{SPEAKER NAME_N}Ghetsis dropped these as he ran.\n"
	.string "The DNA Splicers.\p"
	.string "They should not be a weapon.\n"
	.string "Take them. You will know when\n"
	.string "the time is right.$"
Thunderspire_Summit_Text_NAfterSplicers:
	.string "{SPEAKER NAME_N}The island will wake now. Go and\n"
	.string "see the shrine, {PLAYER}.$"
Thunderspire_Summit_EventScript_HildaAfter::
	lock
	faceplayer
	msgbox Thunderspire_Summit_EventScript_HildaAfter_Text, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_HildaAfter_Text:
	.string "{SPEAKER NAME_HILDA}A hero of ideals... Zekrom\n"
	.string "chose well.$"

Thunderspire_Summit_EventScript_DarkStone::
	msgbox Thunderspire_Summit_EventScript_DarkStone_Text, MSGBOX_NPC
	end

Thunderspire_Summit_EventScript_DarkStone_Text:
	.string "A black stone, crackling with\n"
	.string "static. It feels... watchful.$"

