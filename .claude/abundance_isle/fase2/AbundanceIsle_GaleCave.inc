AbundanceIsle_GaleCave_EventScript_Stele2::
	lockall
	goto_if_set FLAG_ABUNDANCE_STELE_2, AbundanceIsle_GaleCave_EventScript_Stele2_Done
	msgbox AbundanceIsle_GaleCave_EventScript_Stele2_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STELE_2
	msgbox AbundanceIsle_GaleCave_EventScript_Stele2_TextRub, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_GaleCave_EventScript_Stele2_Done::
	msgbox AbundanceIsle_GaleCave_EventScript_Stele2_Text, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_GaleCave_EventScript_Stele2_Text:
	.string "A fragment of an old stele.\p"
	.string "“...but each wished the sky for\n"
	.string "itself, and the fields turned\n"
	.string "to dust...”$"
AbundanceIsle_GaleCave_EventScript_Stele2_TextRub:
	.string "{PLAYER} made a rubbing of the\n"
	.string "fragment for Lenora.$"

AbundanceIsle_GaleCave_EventScript_Noland::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_NOLAND, AbundanceIsle_GaleCave_EventScript_Noland_After
	msgbox AbundanceIsle_GaleCave_EventScript_Noland_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_NOLAND, AbundanceIsle_GaleCave_EventScript_Noland_TextBeaten
	release
	end

AbundanceIsle_GaleCave_EventScript_Noland_After::
	msgbox AbundanceIsle_GaleCave_EventScript_Noland_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_GaleCave_EventScript_Noland_TextChallenge:
	.string "{SPEAKER NAME_NOLAND}Found my secret spot, huh? Let's\n"
	.string "see what you've got!$"
AbundanceIsle_GaleCave_EventScript_Noland_TextBeaten:
	.string "Noland: Ha! Nice moves!$"
AbundanceIsle_GaleCave_EventScript_Noland_TextAfter:
	.string "{SPEAKER NAME_NOLAND}Keep this spot secret, yeah?$"

