ShrineOfTheFirstDragon_EventScript_N::
ShrineOfTheFirstDragon_EventScript_Hilda::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 14, ShrineOfTheFirstDragon_EventScript_NDone
	msgbox ShrineOfTheFirstDragon_Text_Final, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_N_AND_HILDA, ShrineOfTheFirstDragon_Text_FinalBeaten
	setvar VAR_ABUNDANCE_ISLE_STATE, 14
	msgbox ShrineOfTheFirstDragon_Text_FinalAfter, MSGBOX_DEFAULT
	release
	end

ShrineOfTheFirstDragon_EventScript_NDone::
	goto_if_set FLAG_DAILY_ABUNDANCE_DUO, ShrineOfTheFirstDragon_EventScript_NDone_Talk
	msgbox ShrineOfTheFirstDragon_EventScript_NDone_TextRematch, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ShrineOfTheFirstDragon_EventScript_NDone_Talk
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_N_AND_HILDA
	trainerbattle_no_intro TRAINER_ABUNDANCE_N_AND_HILDA, ShrineOfTheFirstDragon_Text_FinalBeaten
	setflag FLAG_DAILY_ABUNDANCE_DUO
	release
	end
ShrineOfTheFirstDragon_EventScript_NDone_Talk::
	msgbox ShrineOfTheFirstDragon_Text_FinalAfter, MSGBOX_DEFAULT
	release
	end

ShrineOfTheFirstDragon_Text_Final:
	.string "{SPEAKER NAME_N}Once there was one dragon, and\n"
	.string "two brothers who loved it.\n"
	.string "When they quarreled, it became three.\p"
	.string "Truth, ideals... and the emptiness\n"
	.string "left behind. Kyurem.\p"
	.string "{SPEAKER NAME_HILDA}Before you go, {PLAYER}... one last\n"
	.string "battle. N and me, together!$"
ShrineOfTheFirstDragon_Text_FinalBeaten:
	.string "N: Truth and ideals... in one\n"
	.string "Trainer.$"
ShrineOfTheFirstDragon_Text_FinalAfter:
	.string "{SPEAKER NAME_N}With the DNA Splicers, Kyurem\n"
	.string "can borrow a hero's strength.\n"
	.string "Use them kindly.\p"
	.string "{SPEAKER NAME_HILDA}Come back anytime. We'll be\n"
	.string "right here, arguing about truth.$"
ShrineOfTheFirstDragon_EventScript_MuralTruth::
	msgbox ShrineOfTheFirstDragon_EventScript_MuralTruth_Text, MSGBOX_SIGN
	end

ShrineOfTheFirstDragon_EventScript_MuralTruth_Text:
	.string "A white dragon breathes fire\n"
	.string "beside the elder brother.$"

ShrineOfTheFirstDragon_EventScript_MuralIdeals::
	msgbox ShrineOfTheFirstDragon_EventScript_MuralIdeals_Text, MSGBOX_SIGN
	end

ShrineOfTheFirstDragon_EventScript_MuralIdeals_Text:
	.string "A black dragon wreathed in\n"
	.string "lightning beside the younger\n"
	.string "brother.$"

ShrineOfTheFirstDragon_EventScript_MuralFirstDragon::
	msgbox ShrineOfTheFirstDragon_EventScript_MuralFirstDragon_Text, MSGBOX_SIGN
	end

ShrineOfTheFirstDragon_EventScript_MuralFirstDragon_Text:
	.string "“Once there was one dragon, and two\n"
	.string "brothers who loved it.”\p"
	.string "“When they quarreled, it became\n"
	.string "three.”$"

ShrineOfTheFirstDragon_EventScript_AltarTruth::
	msgbox ShrineOfTheFirstDragon_EventScript_AltarTruth_Text, MSGBOX_SIGN
	end

ShrineOfTheFirstDragon_EventScript_AltarTruth_Text:
	.string "The Altar of Truth. The stone\n"
	.string "is warm.$"

ShrineOfTheFirstDragon_EventScript_AltarIdeals::
	msgbox ShrineOfTheFirstDragon_EventScript_AltarIdeals_Text, MSGBOX_SIGN
	end

ShrineOfTheFirstDragon_EventScript_AltarIdeals_Text:
	.string "The Altar of Ideals. Static\n"
	.string "crackles on the stone.$"

ShrineOfTheFirstDragon_EventScript_AltarVoid::
	msgbox ShrineOfTheFirstDragon_EventScript_AltarVoid_Text, MSGBOX_SIGN
	end

ShrineOfTheFirstDragon_EventScript_AltarVoid_Text:
	.string "The Altar of the Void. It is\n"
	.string "cold as ice.$"

ShrineOfTheFirstDragon_EventScript_NDone_TextRematch:
	.string "{SPEAKER NAME_N}{PLAYER}! Up for another battle?\n"
	.string "Hilda says she's been practicing.$"

ShrineOfTheFirstDragon_EventScript_Liza::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_TATE_LIZA, ShrineOfTheFirstDragon_EventScript_Liza_After
	msgbox ShrineOfTheFirstDragon_EventScript_Liza_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_TATE_LIZA, ShrineOfTheFirstDragon_EventScript_Liza_TextBeaten
	checkitemspace ITEM_TWISTED_SPOON
	goto_if_eq VAR_RESULT, FALSE, ShrineOfTheFirstDragon_EventScript_Liza_BagFull
	giveitem ITEM_TWISTED_SPOON
	release
	end

ShrineOfTheFirstDragon_EventScript_Liza_After::
	msgbox ShrineOfTheFirstDragon_EventScript_Liza_TextAfter, MSGBOX_DEFAULT
	release
	end

ShrineOfTheFirstDragon_EventScript_Liza_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

ShrineOfTheFirstDragon_EventScript_Liza_TextChallenge:
	.string "{SPEAKER NAME_LIZA}Two brothers, one dragon...\n"
	.string "like us, two twins, one mind.$"
ShrineOfTheFirstDragon_EventScript_Liza_TextBeaten:
	.string "Tate & Liza: Mirrored perfectly!$"
ShrineOfTheFirstDragon_EventScript_Liza_TextAfter:
	.string "{SPEAKER NAME_LIZA}We'll never fight like the\n"
	.string "brothers did.$"

ShrineOfTheFirstDragon_EventScript_Leon::
	msgbox ShrineOfTheFirstDragon_EventScript_Leon_Text, MSGBOX_NPC
	end

ShrineOfTheFirstDragon_EventScript_Leon_Text:
	.string "{SPEAKER NAME_LEON}A legend of two brothers and\n"
	.string "their dragon. I've heard it told\n"
	.string "a hundred different ways.$"

ShrineOfTheFirstDragon_EventScript_Diantha::
	msgbox ShrineOfTheFirstDragon_EventScript_Diantha_Text, MSGBOX_NPC
	end

ShrineOfTheFirstDragon_EventScript_Diantha_Text:
	.string "{SPEAKER NAME_DIANTHA}Truth and ideals... like two\n"
	.string "roles one actor plays. Neither is\n"
	.string "false.$"

