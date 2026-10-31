AbundanceIsle_GaleCave_MapScripts::
	.byte 0

AbundanceIsle_GaleCave_EventScript_Hiker::
	trainerbattle_single TRAINER_ABUNDANCE_GALE_CAVE_HIKER, AbundanceIsle_GaleCave_EventScript_Hiker_Text_Seen, AbundanceIsle_GaleCave_EventScript_Hiker_Text_Beaten
	msgbox AbundanceIsle_GaleCave_EventScript_Hiker_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_GaleCave_EventScript_PlasmaScout::
	trainerbattle_single TRAINER_ABUNDANCE_GALE_CAVE_GRUNT, AbundanceIsle_GaleCave_EventScript_PlasmaScout_Text_Seen, AbundanceIsle_GaleCave_EventScript_PlasmaScout_Text_Beaten
	msgbox AbundanceIsle_GaleCave_EventScript_PlasmaScout_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_GaleCave_EventScript_Hiker_Text_Seen:
	.string "These rocks have been shaking with\nthunder all week! Let's battle!$"

AbundanceIsle_GaleCave_EventScript_Hiker_Text_Beaten:
	.string "Whoa, you've got legs of steel!$"

AbundanceIsle_GaleCave_EventScript_Hiker_Text_After:
	.string "A real hiker never fears a storm.$"

AbundanceIsle_GaleCave_EventScript_PlasmaScout_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

AbundanceIsle_GaleCave_EventScript_PlasmaScout_Text_Beaten:
	.string "Wh-what? Our plans...$"

AbundanceIsle_GaleCave_EventScript_PlasmaScout_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_GaleCave.inc)
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


