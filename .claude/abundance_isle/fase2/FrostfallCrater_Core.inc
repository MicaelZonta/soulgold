FrostfallCrater_Core_EventScript_Stele4::
	lockall
	goto_if_set FLAG_ABUNDANCE_STELE_4, FrostfallCrater_Core_EventScript_Stele4_Done
	msgbox FrostfallCrater_Core_EventScript_Stele4_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STELE_4
	msgbox FrostfallCrater_Core_EventScript_Stele4_TextRub, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Core_EventScript_Stele4_Done::
	msgbox FrostfallCrater_Core_EventScript_Stele4_Text, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Core_EventScript_Stele4_Text:
	.string "A fragment of an old stele.\p"
	.string "“...and the year the cold star fell,\n"
	.string "no lord came at all.”$"
FrostfallCrater_Core_EventScript_Stele4_TextRub:
	.string "{PLAYER} made a rubbing of the\n"
	.string "fragment for Lenora.$"

FrostfallCrater_Core_EventScript_Zinnia::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ZINNIA_TALE, FrostfallCrater_Core_EventScript_Zinnia_After
	checkspecies SPECIES_KYUREM
	goto_if_eq VAR_RESULT, FALSE, FrostfallCrater_Core_EventScript_Zinnia_Idle
	msgbox FrostfallCrater_Core_EventScript_Zinnia_TextTale, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_ZINNIA, FrostfallCrater_Core_EventScript_Zinnia_TextBeaten
	checkitemspace ITEM_DRACO_PLATE
	goto_if_eq VAR_RESULT, FALSE, FrostfallCrater_Core_EventScript_Zinnia_BagFull
	giveitem ITEM_DRACO_PLATE
	setflag FLAG_ABUNDANCE_ZINNIA_TALE
	release
	end

FrostfallCrater_Core_EventScript_Zinnia_Idle::
	msgbox FrostfallCrater_Core_EventScript_Zinnia_TextIdle, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_Core_EventScript_Zinnia_After::
	msgbox FrostfallCrater_Core_EventScript_Zinnia_TextAfter, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_Core_EventScript_Zinnia_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_Core_EventScript_Zinnia_TextIdle:
	.string "{SPEAKER NAME_ZINNIA}A star of ice fell here once.\n"
	.string "The year without harvest.\p"
	.string "If you ever travel with the\n"
	.string "dragon of the void, come back.\n"
	.string "I'll tell you its story.$"
FrostfallCrater_Core_EventScript_Zinnia_TextTale:
	.string "{SPEAKER NAME_ZINNIA}That cold... you have Kyurem.\p"
	.string "My people say it rode the star\n"
	.string "down. Others say it's the shell\n"
	.string "of the first dragon.\p"
	.string "Whatever it is, it chose you.\n"
	.string "Show me you deserve it!$"
FrostfallCrater_Core_EventScript_Zinnia_TextBeaten:
	.string "Zinnia: Ha! The void suits you.$"
FrostfallCrater_Core_EventScript_Zinnia_TextAfter:
	.string "{SPEAKER NAME_ZINNIA}Look after that dragon.$"

