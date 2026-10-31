TruthsandRuins_1F_MapScripts::
	.byte 0

TruthsandRuins_1F_EventScript_GruntLadder::
	trainerbattle_single TRAINER_ABUNDANCE_TRUTHSAND_RUINS_1F_GRUNT_LADDER, TruthsandRuins_1F_EventScript_GruntLadder_Text_Seen, TruthsandRuins_1F_EventScript_GruntLadder_Text_Beaten
	msgbox TruthsandRuins_1F_EventScript_GruntLadder_Text_After, MSGBOX_AUTOCLOSE
	end

TruthsandRuins_1F_EventScript_GruntCamp::
	trainerbattle_single TRAINER_ABUNDANCE_TRUTHSAND_RUINS_1F_GRUNT_CAMP, TruthsandRuins_1F_EventScript_GruntCamp_Text_Seen, TruthsandRuins_1F_EventScript_GruntCamp_Text_Beaten
	msgbox TruthsandRuins_1F_EventScript_GruntCamp_Text_After, MSGBOX_AUTOCLOSE
	end

TruthsandRuins_1F_EventScript_RuinManiac::
	trainerbattle_single TRAINER_ABUNDANCE_TRUTHSAND_RUINS_1F_RUIN_MANIAC, TruthsandRuins_1F_EventScript_RuinManiac_Text_Seen, TruthsandRuins_1F_EventScript_RuinManiac_Text_Beaten
	msgbox TruthsandRuins_1F_EventScript_RuinManiac_Text_After, MSGBOX_AUTOCLOSE
	end

TruthsandRuins_1F_EventScript_WarpTrigger2::
	lockall
	setwarp MAP_TRUTHSAND_RUINS_B1F, 1
	special DoFallWarp
	waitstate
	end

TruthsandRuins_1F_EventScript_WarpTrigger3::
	lockall
	setwarp MAP_TRUTHSAND_RUINS_B1F, 2
	special DoFallWarp
	waitstate
	end

TruthsandRuins_1F_EventScript_WarpTrigger4::
	lockall
	setwarp MAP_TRUTHSAND_RUINS_B1F, 3
	special DoFallWarp
	waitstate
	end

TruthsandRuins_1F_EventScript_GruntLadder_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

TruthsandRuins_1F_EventScript_GruntLadder_Text_Beaten:
	.string "Wh-what? Our plans...$"

TruthsandRuins_1F_EventScript_GruntLadder_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

TruthsandRuins_1F_EventScript_GruntCamp_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

TruthsandRuins_1F_EventScript_GruntCamp_Text_Beaten:
	.string "Wh-what? Our plans...$"

TruthsandRuins_1F_EventScript_GruntCamp_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

TruthsandRuins_1F_EventScript_RuinManiac_Text_Seen:
	.string "These ruins hold the legend of the\nHero of Truth! Don't touch anything!$"

TruthsandRuins_1F_EventScript_RuinManiac_Text_Beaten:
	.string "Ahh, my notes!$"

TruthsandRuins_1F_EventScript_RuinManiac_Text_After:
	.string "The murals speak of a white stone\nthat sleeps under the sand.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/TruthsandRuins_1F.inc)
TruthsandRuins_1F_EventScript_Mural1::
	lockall
	msgbox TruthsandRuins_1F_EventScript_Mural1_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_MURAL_1
	releaseall
	end

TruthsandRuins_1F_EventScript_Mural1_Text:
	.string "An old stone obelisk, carved on\n"
	.string "every side.\p"
	.string "Two brothers raise a city, a\n"
	.string "single dragon above them.$"

TruthsandRuins_1F_EventScript_Mural2::
	lockall
	msgbox TruthsandRuins_1F_EventScript_Mural2_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_MURAL_2
	releaseall
	end

TruthsandRuins_1F_EventScript_Mural2_Text:
	.string "An old stone obelisk, carved on\n"
	.string "every side.\p"
	.string "The brothers turn away from\n"
	.string "each other.$"

TruthsandRuins_1F_EventScript_Lucy::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_MURALS_DONE, TruthsandRuins_1F_EventScript_Lucy_After
	goto_if_unset FLAG_ABUNDANCE_MURAL_1, TruthsandRuins_1F_EventScript_Lucy_Ask
	goto_if_unset FLAG_ABUNDANCE_MURAL_2, TruthsandRuins_1F_EventScript_Lucy_Ask
	goto_if_unset FLAG_ABUNDANCE_MURAL_3, TruthsandRuins_1F_EventScript_Lucy_Ask
	goto_if_unset FLAG_ABUNDANCE_MURAL_4, TruthsandRuins_1F_EventScript_Lucy_Ask
	goto_if_unset FLAG_ABUNDANCE_MURAL_5, TruthsandRuins_1F_EventScript_Lucy_Ask
	msgbox TruthsandRuins_1F_EventScript_Lucy_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_LUCY, TruthsandRuins_1F_EventScript_Lucy_TextBeaten
	checkitemspace ITEM_SUN_STONE
	goto_if_eq VAR_RESULT, FALSE, TruthsandRuins_1F_EventScript_Lucy_BagFull
	giveitem ITEM_SUN_STONE
	setflag FLAG_ABUNDANCE_MURALS_DONE
	release
	end

TruthsandRuins_1F_EventScript_Lucy_Ask::
	msgbox TruthsandRuins_1F_EventScript_Lucy_TextAsk, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_1F_EventScript_Lucy_After::
	msgbox TruthsandRuins_1F_EventScript_Lucy_TextAfter, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_1F_EventScript_Lucy_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_1F_EventScript_Lucy_TextAsk:
	.string "{SPEAKER NAME_LUCY}...Five murals tell the whole\n"
	.string "story. Read them all.$"
TruthsandRuins_1F_EventScript_Lucy_TextChallenge:
	.string "{SPEAKER NAME_LUCY}You read every mural. Then you\n"
	.string "know the truth. Prove it.$"
TruthsandRuins_1F_EventScript_Lucy_TextBeaten:
	.string "Lucy: ...Acceptable.$"
TruthsandRuins_1F_EventScript_Lucy_TextAfter:
	.string "{SPEAKER NAME_LUCY}...The sand keeps its secrets well.$"

TruthsandRuins_1F_EventScript_Spenser::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_SPENSER, TruthsandRuins_1F_EventScript_Spenser_After
	msgbox TruthsandRuins_1F_EventScript_Spenser_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_SPENSER, TruthsandRuins_1F_EventScript_Spenser_TextBeaten
	checkitemspace ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, FALSE, TruthsandRuins_1F_EventScript_Spenser_BagFull
	giveitem ITEM_FIRE_STONE
	release
	end

TruthsandRuins_1F_EventScript_Spenser_After::
	msgbox TruthsandRuins_1F_EventScript_Spenser_TextAfter, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_1F_EventScript_Spenser_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_1F_EventScript_Spenser_TextChallenge:
	.string "{SPEAKER NAME_SPENSER}These ruins test the spirit.\n"
	.string "Let me test yours!$"
TruthsandRuins_1F_EventScript_Spenser_TextBeaten:
	.string "Spenser: Your spirit is true.$"
TruthsandRuins_1F_EventScript_Spenser_TextAfter:
	.string "{SPEAKER NAME_SPENSER}Truth lives where we least look.$"

TruthsandRuins_1F_EventScript_MuralTruth::
	msgbox TruthsandRuins_1F_EventScript_MuralTruth_Text, MSGBOX_SIGN
	end

TruthsandRuins_1F_EventScript_MuralTruth_Text:
	.string "“To find the truth, walk where\n"
	.string "the sand swallows the sun.”$"

TruthsandRuins_1F_EventScript_Sign::
	msgbox TruthsandRuins_1F_EventScript_Sign_Text, MSGBOX_SIGN
	end

TruthsandRuins_1F_EventScript_Sign_Text:
	.string "TRUTHSAND RUINS\n"
	.string "Beware of quicksand!$"


