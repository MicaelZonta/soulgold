AbundanceIsle_SpringGrove_EventScript_Enamorus::
	lock
	faceplayer
	msgbox AbundanceIsle_SpringGrove_EventScript_Enamorus_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_ENAMORUS, 70, LOCALID_ABUNDANCE_ISLE_SPRING_GROVE_ENAMORUS, FLAG_TEMP_11, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, AbundanceIsle_SpringGrove_EventScript_Enamorus_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AbundanceIsle_SpringGrove_EventScript_Enamorus_Beaten
	release
	end

AbundanceIsle_SpringGrove_EventScript_Enamorus_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_ABUNDANCE_ISLE_SPRING_GROVE_ENAMORUS
	fadescreenswapbuffers FADE_FROM_BLACK
AbundanceIsle_SpringGrove_EventScript_Enamorus_Done:
	setflag FLAG_ABUNDANCE_ENAMORUS_DONE
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 8, AbundanceIsle_SpringGrove_EventScript_Enamorus_Advance
	release
	end

AbundanceIsle_SpringGrove_EventScript_Enamorus_Advance:
	setvar VAR_ABUNDANCE_ISLE_STATE, 9
	return

AbundanceIsle_SpringGrove_EventScript_Enamorus_Text_Intro:
	.string "A warm breeze fills the garden.\n"
	.string "The Herald of Spring has come\n"
	.string "from across the sea!$"
AbundanceIsle_SpringGrove_EventScript_Seed6::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_6, AbundanceIsle_SpringGrove_EventScript_Seed6_Empty
	msgbox AbundanceIsle_SpringGrove_EventScript_Seed6_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_6
	removeobject LOCALID_ABUNDANCE_ISLE_SPRING_GROVE_SEED_6
	releaseall
	end

AbundanceIsle_SpringGrove_EventScript_Seed6_Empty::
	msgbox AbundanceIsle_SpringGrove_EventScript_Seed6_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_SpringGrove_EventScript_Seed6_Text:
	.string "A sack of seeds blown here by the\n"
	.string "storm!\p"
	.string "{PLAYER} took the sack to return\n"
	.string "it to the farm.$"
AbundanceIsle_SpringGrove_EventScript_Seed6_TextEmpty:
	.string "Nothing here but a few stray\n"
	.string "seeds.$"

AbundanceIsle_SpringGrove_EventScript_Ramos::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_GARDEN_DONE, AbundanceIsle_SpringGrove_EventScript_Ramos_After
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_SpringGrove_EventScript_Ramos_Before
	goto_if_ge VAR_ABUNDANCE_GARDEN_DAYS, 3, AbundanceIsle_SpringGrove_EventScript_Ramos_Reward
	goto_if_set FLAG_DAILY_ABUNDANCE_GARDEN, AbundanceIsle_SpringGrove_EventScript_Ramos_Tomorrow
	msgbox AbundanceIsle_SpringGrove_EventScript_Ramos_TextWater, MSGBOX_DEFAULT
	setflag FLAG_DAILY_ABUNDANCE_GARDEN
	addvar VAR_ABUNDANCE_GARDEN_DAYS, 1
	goto_if_ge VAR_ABUNDANCE_GARDEN_DAYS, 3, AbundanceIsle_SpringGrove_EventScript_Ramos_Reward
	msgbox AbundanceIsle_SpringGrove_EventScript_Ramos_TextAgain, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SpringGrove_EventScript_Ramos_Reward::
	msgbox AbundanceIsle_SpringGrove_EventScript_Ramos_TextReward, MSGBOX_DEFAULT
	checkitemspace ITEM_BIG_ROOT
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_SpringGrove_EventScript_Ramos_BagFull
	giveitem ITEM_BIG_ROOT
	setflag FLAG_ABUNDANCE_GARDEN_DONE
	release
	end

AbundanceIsle_SpringGrove_EventScript_Ramos_Before::
	msgbox AbundanceIsle_SpringGrove_EventScript_Ramos_TextBefore, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SpringGrove_EventScript_Ramos_Tomorrow::
	msgbox AbundanceIsle_SpringGrove_EventScript_Ramos_TextTomorrow, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SpringGrove_EventScript_Ramos_After::
	msgbox AbundanceIsle_SpringGrove_EventScript_Ramos_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SpringGrove_EventScript_Ramos_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SpringGrove_EventScript_Ramos_TextBefore:
	.string "{SPEAKER NAME_RAMOS}The founders planted these beds\n"
	.string "“for the one who comes from the\n"
	.string "sea when winter ends.”\p"
	.string "Funny thing is, nobody remembers\n"
	.string "who that is anymore.$"
AbundanceIsle_SpringGrove_EventScript_Ramos_TextWater:
	.string "{SPEAKER NAME_RAMOS}Spring is here! Help me water\n"
	.string "the herald's beds, would you?\p"
	.string "...There. That's the way.$"
AbundanceIsle_SpringGrove_EventScript_Ramos_TextAgain:
	.string "{SPEAKER NAME_RAMOS}Come back tomorrow and we'll\n"
	.string "do it again.$"
AbundanceIsle_SpringGrove_EventScript_Ramos_TextTomorrow:
	.string "{SPEAKER NAME_RAMOS}Plants need patience. Tomorrow!$"
AbundanceIsle_SpringGrove_EventScript_Ramos_TextReward:
	.string "{SPEAKER NAME_RAMOS}Look at them bloom! The herald\n"
	.string "would be proud.\p"
	.string "Here, a root from the oldest bed.$"
AbundanceIsle_SpringGrove_EventScript_Ramos_TextAfter:
	.string "{SPEAKER NAME_RAMOS}Every spring, the garden\n"
	.string "remembers.$"

AbundanceIsle_SpringGrove_EventScript_Gardenia::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_GARDENIA, AbundanceIsle_SpringGrove_EventScript_Gardenia_After
	msgbox AbundanceIsle_SpringGrove_EventScript_Gardenia_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GARDENIA, AbundanceIsle_SpringGrove_EventScript_Gardenia_TextBeaten
	release
	end

AbundanceIsle_SpringGrove_EventScript_Gardenia_After::
	msgbox AbundanceIsle_SpringGrove_EventScript_Gardenia_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SpringGrove_EventScript_Gardenia_TextChallenge:
	.string "{SPEAKER NAME_GARDENIA}This grove is the first place\n"
	.string "spring touches. Let's battle in\n"
	.string "its honor!$"
AbundanceIsle_SpringGrove_EventScript_Gardenia_TextBeaten:
	.string "Gardenia: You bloomed beautifully!$"
AbundanceIsle_SpringGrove_EventScript_Gardenia_TextAfter:
	.string "{SPEAKER NAME_GARDENIA}Come see the flowers anytime!$"

