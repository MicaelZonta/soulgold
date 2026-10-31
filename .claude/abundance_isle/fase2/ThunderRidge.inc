ThunderRidge_EventScript_Thundurus::
	lock
	faceplayer
	msgbox ThunderRidge_EventScript_Thundurus_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_THUNDURUS, 70, LOCALID_THUNDER_RIDGE_THUNDURUS, FLAG_TEMP_11, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, ThunderRidge_EventScript_Thundurus_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, ThunderRidge_EventScript_Thundurus_Beaten
	release
	end

ThunderRidge_EventScript_Thundurus_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_THUNDER_RIDGE_THUNDURUS
	fadescreenswapbuffers FADE_FROM_BLACK
ThunderRidge_EventScript_Thundurus_Done:
	setflag FLAG_ABUNDANCE_THUNDURUS_DONE
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 99, ThunderRidge_EventScript_Thundurus_Advance
	release
	end

ThunderRidge_EventScript_Thundurus_Advance:
	setvar VAR_ABUNDANCE_ISLE_STATE, 99
	return

ThunderRidge_EventScript_Thundurus_Text_Intro:
	.string "Sparks crackle over the peak.\n"
	.string "The Thunder Genie roars!$"
ThunderRidge_EventScript_PlasmaGuard::
	msgbox ThunderRidge_EventScript_PlasmaGuard_Text, MSGBOX_NPC
	end

ThunderRidge_EventScript_PlasmaGuard_Text:
	.string "{SPEAKER NAME_GRUNT}No one enters the tower!\n"
	.string "Lord Ghetsis's orders!$"

ThunderRidge_EventScript_Volkner::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_STORM_DATA_DONE, ThunderRidge_EventScript_Volkner_Battle
	goto_if_unset FLAG_ABUNDANCE_STORM_GAUGE, ThunderRidge_EventScript_Volkner_Idle
	msgbox ThunderRidge_EventScript_Volkner_TextData, MSGBOX_DEFAULT
	checkitemspace ITEM_ELECTIRIZER
	goto_if_eq VAR_RESULT, FALSE, ThunderRidge_EventScript_Volkner_BagFull
	giveitem ITEM_ELECTIRIZER
	setflag FLAG_ABUNDANCE_STORM_DATA_DONE
	release
	end

ThunderRidge_EventScript_Volkner_Idle::
	msgbox ThunderRidge_EventScript_Volkner_TextIdle, MSGBOX_DEFAULT
	release
	end

ThunderRidge_EventScript_Volkner_Battle::
	goto_if_defeated TRAINER_ABUNDANCE_VOLKNER, ThunderRidge_EventScript_Volkner_After
	msgbox ThunderRidge_EventScript_Volkner_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_VOLKNER, ThunderRidge_EventScript_Volkner_TextBeaten
	release
	end

ThunderRidge_EventScript_Volkner_After::
	goto_if_eq VAR_ABUNDANCE_STORM, 1, ThunderRidge_EventScript_Volkner_StormRematch
	msgbox ThunderRidge_EventScript_Volkner_TextIdle, MSGBOX_DEFAULT
	release
	end

ThunderRidge_EventScript_Volkner_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

ThunderRidge_EventScript_Volkner_TextIdle:
	.string "{SPEAKER NAME_VOLKNER}Lightning strikes this ridge more\n"
	.string "than anywhere I've seen. It's\n"
	.string "like it's being called.$"
ThunderRidge_EventScript_Volkner_TextData:
	.string "{SPEAKER NAME_VOLKNER}Winona's wind data... it all\n"
	.string "spirals around the crater.\p"
	.string "The storm is artificial. Thanks.\n"
	.string "Take this for your trouble.$"
ThunderRidge_EventScript_Volkner_TextChallenge:
	.string "{SPEAKER NAME_VOLKNER}Now I'm curious. Show me a\n"
	.string "battle with some real spark!$"
ThunderRidge_EventScript_Volkner_TextBeaten:
	.string "Volkner: Heh. That woke me up.$"

ThunderRidge_EventScript_Elesa::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_ELESA, ThunderRidge_EventScript_Elesa_After
	msgbox ThunderRidge_EventScript_Elesa_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_ELESA, ThunderRidge_EventScript_Elesa_TextBeaten
	release
	end

ThunderRidge_EventScript_Elesa_After::
	goto_if_eq VAR_ABUNDANCE_STORM, 1, ThunderRidge_EventScript_Elesa_StormRematch
	msgbox ThunderRidge_EventScript_Elesa_TextAfter, MSGBOX_DEFAULT
	release
	end

ThunderRidge_EventScript_Elesa_TextChallenge:
	.string "{SPEAKER NAME_ELESA}These sparks would make a gorgeous\n"
	.string "runway. Shall we dazzle them?$"
ThunderRidge_EventScript_Elesa_TextBeaten:
	.string "Elesa: Shocking... in a good way!$"
ThunderRidge_EventScript_Elesa_TextAfter:
	.string "{SPEAKER NAME_ELESA}The lightning is calmer now.\n"
	.string "Almost pretty.$"

ThunderRidge_EventScript_Alder::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ALDER_DONE, ThunderRidge_EventScript_Alder_After
	setvar VAR_ABUNDANCE_IDEALS, 0
	msgbox ThunderRidge_EventScript_Alder_TextQ1, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, ThunderRidge_EventScript_Alder_Ideal
	msgbox ThunderRidge_EventScript_Alder_TextQ2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, ThunderRidge_EventScript_Alder_Ideal
	msgbox ThunderRidge_EventScript_Alder_TextQ3, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, ThunderRidge_EventScript_Alder_Ideal
	goto_if_ge VAR_ABUNDANCE_IDEALS, 2, ThunderRidge_EventScript_Alder_IdealsWin
	msgbox ThunderRidge_EventScript_Alder_TextTruth, MSGBOX_DEFAULT
	goto ThunderRidge_EventScript_Alder_Give
ThunderRidge_EventScript_Alder_IdealsWin::
	msgbox ThunderRidge_EventScript_Alder_TextIdeals, MSGBOX_DEFAULT
ThunderRidge_EventScript_Alder_Give::
	checkitemspace ITEM_EXPERT_BELT
	goto_if_eq VAR_RESULT, FALSE, ThunderRidge_EventScript_Alder_BagFull
	giveitem ITEM_EXPERT_BELT
	setflag FLAG_ABUNDANCE_ALDER_DONE
	release
	end

ThunderRidge_EventScript_Alder_Ideal::
	addvar VAR_ABUNDANCE_IDEALS, 1
	return

ThunderRidge_EventScript_Alder_After::
	msgbox ThunderRidge_EventScript_Alder_TextAfter, MSGBOX_DEFAULT
	release
	end

ThunderRidge_EventScript_Alder_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

ThunderRidge_EventScript_Alder_TextQ1:
	.string "{SPEAKER NAME_ALDER}Tell me, young one. Would you\n"
	.string "keep a bright dream over a hard\n"
	.string "truth?$"
ThunderRidge_EventScript_Alder_TextQ2:
	.string "{SPEAKER NAME_ALDER}If the world doesn't match what\n"
	.string "you believe, do you change the\n"
	.string "world?$"
ThunderRidge_EventScript_Alder_TextQ3:
	.string "{SPEAKER NAME_ALDER}Would you follow a path no one\n"
	.string "has walked before?$"
ThunderRidge_EventScript_Alder_TextIdeals:
	.string "{SPEAKER NAME_ALDER}Ideals, then! The black dragon\n"
	.string "will like you.\p"
	.string "Take this. Strength for the\n"
	.string "road you chose.$"
ThunderRidge_EventScript_Alder_TextTruth:
	.string "{SPEAKER NAME_ALDER}Truth, then. The white dragon\n"
	.string "would understand you.\p"
	.string "Take this. Strength for the\n"
	.string "road you chose.$"
ThunderRidge_EventScript_Alder_TextAfter:
	.string "{SPEAKER NAME_ALDER}Truth and ideals aren't enemies.\n"
	.string "They're two halves of one heart.$"

ThunderRidge_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThunderRidge_OnTransition
	.byte 0

ThunderRidge_OnTransition::
	call ThunderRidge_EventScript_Vis_TEMP_11
	call ThunderRidge_EventScript_Vis_TEMP_12
	call ThunderRidge_EventScript_StormRoll
	call_if_eq VAR_ABUNDANCE_STORM, 1, ThunderRidge_EventScript_StormWeather
	end

ThunderRidge_EventScript_StormRoll::
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 14, ThunderRidge_EventScript_StormRollDay
	setvar VAR_ABUNDANCE_STORM, 0
	return
ThunderRidge_EventScript_StormRollDay::
	goto_if_set FLAG_DAILY_ABUNDANCE_STORM_ROLLED, ThunderRidge_EventScript_StormRollEnd
	setflag FLAG_DAILY_ABUNDANCE_STORM_ROLLED
	setvar VAR_ABUNDANCE_STORM, 0
	random 3
	goto_if_ne VAR_RESULT, 0, ThunderRidge_EventScript_StormRollEnd
	setvar VAR_ABUNDANCE_STORM, 1
ThunderRidge_EventScript_StormRollEnd::
	return

ThunderRidge_EventScript_StormWeather::
	setweather WEATHER_RAIN_THUNDERSTORM
	return

ThunderRidge_EventScript_Volkner_StormRematch::
	msgbox ThunderRidge_EventScript_Volkner_TextStorm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ThunderRidge_EventScript_Volkner_StormNo
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_VOLKNER
	trainerbattle_no_intro TRAINER_ABUNDANCE_VOLKNER, ThunderRidge_EventScript_Volkner_TextBeaten
	release
	end
ThunderRidge_EventScript_Volkner_StormNo::
	release
	end

ThunderRidge_EventScript_Volkner_TextStorm:
	.string "{SPEAKER NAME_VOLKNER}Lightning everywhere. Now THIS\n"
	.string "is battle weather. Again?$"

ThunderRidge_EventScript_Elesa_StormRematch::
	msgbox ThunderRidge_EventScript_Elesa_TextStorm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ThunderRidge_EventScript_Elesa_StormNo
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_ELESA
	trainerbattle_no_intro TRAINER_ABUNDANCE_ELESA, ThunderRidge_EventScript_Elesa_TextBeaten
	release
	end
ThunderRidge_EventScript_Elesa_StormNo::
	release
	end

ThunderRidge_EventScript_Elesa_TextStorm:
	.string "{SPEAKER NAME_ELESA}A storm runway! Shall we shine\n"
	.string "once more?$"

