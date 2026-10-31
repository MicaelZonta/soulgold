AbundanceIsle_GaleShore_EventScript_Tornadus::
	lock
	faceplayer
	msgbox AbundanceIsle_GaleShore_EventScript_Tornadus_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_TORNADUS, 70, LOCALID_ABUNDANCE_ISLE_GALE_SHORE_TORNADUS, FLAG_TEMP_11, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, AbundanceIsle_GaleShore_EventScript_Tornadus_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AbundanceIsle_GaleShore_EventScript_Tornadus_Beaten
	release
	end

AbundanceIsle_GaleShore_EventScript_Tornadus_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_ABUNDANCE_ISLE_GALE_SHORE_TORNADUS
	fadescreenswapbuffers FADE_FROM_BLACK
AbundanceIsle_GaleShore_EventScript_Tornadus_Done:
	setflag FLAG_ABUNDANCE_TORNADUS_DONE
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 99, AbundanceIsle_GaleShore_EventScript_Tornadus_Advance
	release
	end

AbundanceIsle_GaleShore_EventScript_Tornadus_Advance:
	setvar VAR_ABUNDANCE_ISLE_STATE, 99
	return

AbundanceIsle_GaleShore_EventScript_Tornadus_Text_Intro:
	.string "The Wind Genie lies inside the\n"
	.string "stone circle, exhausted...\n"
	.string "It rises with a howl!$"
AbundanceIsle_GaleShore_EventScript_Seed4::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_4, AbundanceIsle_GaleShore_EventScript_Seed4_Empty
	msgbox AbundanceIsle_GaleShore_EventScript_Seed4_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_4
	removeobject LOCALID_ABUNDANCE_ISLE_GALE_SHORE_SEED_4
	releaseall
	end

AbundanceIsle_GaleShore_EventScript_Seed4_Empty::
	msgbox AbundanceIsle_GaleShore_EventScript_Seed4_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_GaleShore_EventScript_Seed4_Text:
	.string "A sack of seeds blown here by the\n"
	.string "storm!\p"
	.string "{PLAYER} took the sack to return\n"
	.string "it to the farm.$"
AbundanceIsle_GaleShore_EventScript_Seed4_TextEmpty:
	.string "Nothing here but a few stray\n"
	.string "seeds.$"

AbundanceIsle_GaleShore_EventScript_Winona::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_STORM_GAUGE, AbundanceIsle_GaleShore_EventScript_Winona_Battle
	msgbox AbundanceIsle_GaleShore_EventScript_Winona_TextGauge, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STORM_GAUGE
	release
	end

AbundanceIsle_GaleShore_EventScript_Winona_Battle::
	goto_if_defeated TRAINER_ABUNDANCE_WINONA, AbundanceIsle_GaleShore_EventScript_Winona_After
	msgbox AbundanceIsle_GaleShore_EventScript_Winona_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_WINONA, AbundanceIsle_GaleShore_EventScript_Winona_TextBeaten
	release
	end

AbundanceIsle_GaleShore_EventScript_Winona_After::
	goto_if_eq VAR_ABUNDANCE_STORM, 1, AbundanceIsle_GaleShore_EventScript_Winona_StormRematch
	msgbox AbundanceIsle_GaleShore_EventScript_Winona_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_GaleShore_EventScript_Winona_TextGauge:
	.string "{SPEAKER NAME_WINONA}The winds here spin around the\n"
	.string "crater. Something pulls them.\p"
	.string "Take my storm readings to Volkner\n"
	.string "on the Thunder Ridge. He's measuring\n"
	.string "the lightning.$"
AbundanceIsle_GaleShore_EventScript_Winona_TextChallenge:
	.string "{SPEAKER NAME_WINONA}Let's see how your Pokemon fly\n"
	.string "against this wind!$"
AbundanceIsle_GaleShore_EventScript_Winona_TextBeaten:
	.string "Winona: Beautifully flown.$"
AbundanceIsle_GaleShore_EventScript_Winona_TextAfter:
	.string "{SPEAKER NAME_WINONA}When the winds calm, the Wind\n"
	.string "Genie will come down.$"

AbundanceIsle_GaleShore_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_GaleShore_OnTransition
	.byte 0

AbundanceIsle_GaleShore_OnTransition::
	call AbundanceIsle_GaleShore_EventScript_Vis_TEMP_11
	call AbundanceIsle_GaleShore_EventScript_StormRoll
	call_if_eq VAR_ABUNDANCE_STORM, 1, AbundanceIsle_GaleShore_EventScript_StormWeather
	end

AbundanceIsle_GaleShore_EventScript_StormRoll::
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 14, AbundanceIsle_GaleShore_EventScript_StormRollDay
	setvar VAR_ABUNDANCE_STORM, 0
	return
AbundanceIsle_GaleShore_EventScript_StormRollDay::
	goto_if_set FLAG_DAILY_ABUNDANCE_STORM_ROLLED, AbundanceIsle_GaleShore_EventScript_StormRollEnd
	setflag FLAG_DAILY_ABUNDANCE_STORM_ROLLED
	setvar VAR_ABUNDANCE_STORM, 0
	random 3
	goto_if_ne VAR_RESULT, 0, AbundanceIsle_GaleShore_EventScript_StormRollEnd
	setvar VAR_ABUNDANCE_STORM, 1
AbundanceIsle_GaleShore_EventScript_StormRollEnd::
	return

AbundanceIsle_GaleShore_EventScript_StormWeather::
	setweather WEATHER_DOWNPOUR
	return

AbundanceIsle_GaleShore_EventScript_Winona_StormRematch::
	msgbox AbundanceIsle_GaleShore_EventScript_Winona_TextStorm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AbundanceIsle_GaleShore_EventScript_Winona_StormNo
	closemessage
	cleartrainerflag TRAINER_ABUNDANCE_WINONA
	trainerbattle_no_intro TRAINER_ABUNDANCE_WINONA, AbundanceIsle_GaleShore_EventScript_Winona_TextBeaten
	release
	end
AbundanceIsle_GaleShore_EventScript_Winona_StormNo::
	release
	end

AbundanceIsle_GaleShore_EventScript_Winona_TextStorm:
	.string "{SPEAKER NAME_WINONA}Feel that wind? My Pokemon want\n"
	.string "a rematch in it!$"

