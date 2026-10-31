AbundanceIsle_PokemonCenter_EventScript_Barry::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_BARRY, AbundanceIsle_PokemonCenter_EventScript_Barry_After
	msgbox AbundanceIsle_PokemonCenter_EventScript_Barry_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_BARRY, AbundanceIsle_PokemonCenter_EventScript_Barry_TextBeaten
	checkitemspace ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_PokemonCenter_EventScript_Barry_BagFull
	giveitem ITEM_QUICK_CLAW
	release
	end

AbundanceIsle_PokemonCenter_EventScript_Barry_After::
	msgbox AbundanceIsle_PokemonCenter_EventScript_Barry_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_PokemonCenter_EventScript_Barry_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_PokemonCenter_EventScript_Barry_TextChallenge:
	.string "{SPEAKER NAME_BARRY}Hey! You! I'm racing to the top\n"
	.string "of the Thunderspire... but first,\n"
	.string "a battle! Ten seconds! Go!$"
AbundanceIsle_PokemonCenter_EventScript_Barry_TextBeaten:
	.string "Barry: Whaaat?! I'll fine you!$"
AbundanceIsle_PokemonCenter_EventScript_Barry_TextAfter:
	.string "{SPEAKER NAME_BARRY}Next time I'll be faster. I'll\n"
	.string "fine you a million!$"

AbundanceIsle_PokemonCenter_EventScript_Nemona::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_ABUNDANCE_NEMONA, AbundanceIsle_PokemonCenter_EventScript_Nemona_Tomorrow
	msgbox AbundanceIsle_PokemonCenter_EventScript_Nemona_TextChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AbundanceIsle_PokemonCenter_EventScript_Nemona_No
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_NEMONA
	trainerbattle_no_intro TRAINER_ABUNDANCE_NEMONA, AbundanceIsle_PokemonCenter_EventScript_Nemona_TextBeaten
	setflag FLAG_DAILY_ABUNDANCE_NEMONA
	msgbox AbundanceIsle_PokemonCenter_EventScript_Nemona_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_PokemonCenter_EventScript_Nemona_No::
	release
	end

AbundanceIsle_PokemonCenter_EventScript_Nemona_Tomorrow::
	msgbox AbundanceIsle_PokemonCenter_EventScript_Nemona_TextTomorrow, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_PokemonCenter_EventScript_Nemona_TextChallenge:
	.string "{SPEAKER NAME_NEMONA}Battle! Battle! I've been waiting\n"
	.string "all day! Ready?$"
AbundanceIsle_PokemonCenter_EventScript_Nemona_TextBeaten:
	.string "Nemona: That was SO good!$"
AbundanceIsle_PokemonCenter_EventScript_Nemona_TextAfter:
	.string "{SPEAKER NAME_NEMONA}Same time tomorrow, okay?!$"
AbundanceIsle_PokemonCenter_EventScript_Nemona_TextTomorrow:
	.string "{SPEAKER NAME_NEMONA}I'm all battled out... for today!\n"
	.string "Tomorrow!$"

AbundanceIsle_PokemonCenter_EventScript_NoticeBoard::
	lockall
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_Festival
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_Clear
	msgbox AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_TextSnow, MSGBOX_SIGN
	releaseall
	end
AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_Clear::
	msgbox AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_TextClear, MSGBOX_SIGN
	releaseall
	end
AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_Festival::
	msgbox AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_TextFestival, MSGBOX_SIGN
	releaseall
	end

AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_TextSnow:
	.string "NOTICE: Ferry delayed. Snow in\n"
	.string "harvest season?! Farmers' meeting\n"
	.string "at the barn tonight.$"
AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_TextClear:
	.string "NOTICE: Snow has stopped! Beware\n"
	.string "of the strange ship at the cape.$"
AbundanceIsle_PokemonCenter_EventScript_NoticeBoard_TextFestival:
	.string "NOTICE: Spring is back! The farm\n"
	.string "stand and the Festival Arena are\n"
	.string "open every day.$"

AbundanceIsle_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_PokemonCenter_OnTransition
	.byte 0

AbundanceIsle_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_WINDSWEPT_CAPE
	end

AbundanceIsle_PokemonCenter_EventScript_Girl::
	msgbox AbundanceIsle_PokemonCenter_EventScript_Girl_Text, MSGBOX_NPC
	end

AbundanceIsle_PokemonCenter_EventScript_Girl_Text:
	.string "I came for the harvest festival,\n"
	.string "but it's snowing!\p"
	.string "My Vulpix loves it, at least.$"

AbundanceIsle_PokemonCenter_EventScript_Sailor::
	msgbox AbundanceIsle_PokemonCenter_EventScript_Sailor_Text, MSGBOX_NPC
	end

AbundanceIsle_PokemonCenter_EventScript_Sailor_Text:
	.string "Strange winds out at sea. Like\n"
	.string "two storms fighting each other.$"

AbundanceIsle_PokemonCenter_EventScript_OldWoman::
	msgbox AbundanceIsle_PokemonCenter_EventScript_OldWoman_Text, MSGBOX_NPC
	end

AbundanceIsle_PokemonCenter_EventScript_OldWoman_Text:
	.string "In my mother's time, a spring\n"
	.string "visitor came across the sea.\p"
	.string "When it left the island, the\n"
	.string "flowers wouldn't open.$"

