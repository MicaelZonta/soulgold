EmberduneIsle_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EmberduneIsle_OnTransition
	.byte 0

EmberduneIsle_OnTransition::
	call EmberduneIsle_EventScript_Vis_TEMP_11
	end

EmberduneIsle_EventScript_Vis_TEMP_11::
	goto_if_eq VAR_ABUNDANCE_ISLE_STATE, 11, EmberduneIsle_EventScript_Vis_TEMP_11_Show
EmberduneIsle_EventScript_Vis_TEMP_11_No::
EmberduneIsle_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
EmberduneIsle_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

EmberduneIsle_EventScript_Digger1::
	trainerbattle_single TRAINER_ABUNDANCE_EMBERDUNE_ISLE_DIGGER_1, EmberduneIsle_EventScript_Digger1_Text_Seen, EmberduneIsle_EventScript_Digger1_Text_Beaten
	msgbox EmberduneIsle_EventScript_Digger1_Text_After, MSGBOX_AUTOCLOSE
	end

EmberduneIsle_EventScript_Digger2::
	trainerbattle_single TRAINER_ABUNDANCE_EMBERDUNE_ISLE_DIGGER_2, EmberduneIsle_EventScript_Digger2_Text_Seen, EmberduneIsle_EventScript_Digger2_Text_Beaten
	msgbox EmberduneIsle_EventScript_Digger2_Text_After, MSGBOX_AUTOCLOSE
	end

EmberduneIsle_EventScript_Hiker::
	trainerbattle_single TRAINER_ABUNDANCE_EMBERDUNE_ISLE_HIKER, EmberduneIsle_EventScript_Hiker_Text_Seen, EmberduneIsle_EventScript_Hiker_Text_Beaten
	msgbox EmberduneIsle_EventScript_Hiker_Text_After, MSGBOX_AUTOCLOSE
	end

EmberduneIsle_EventScript_RuinManiac::
	trainerbattle_single TRAINER_ABUNDANCE_EMBERDUNE_ISLE_RUIN_MANIAC, EmberduneIsle_EventScript_RuinManiac_Text_Seen, EmberduneIsle_EventScript_RuinManiac_Text_Beaten
	msgbox EmberduneIsle_EventScript_RuinManiac_Text_After, MSGBOX_AUTOCLOSE
	end

EmberduneIsle_EventScript_WarpTrigger2::
	lockall
	setwarp MAP_TRUTHSAND_RUINS_B1F, 3
	special DoFallWarp
	waitstate
	end

EmberduneIsle_EventScript_WarpTrigger3::
	warp MAP_TRUTHSAND_RUINS_B1F, 3
	waitstate
	end

EmberduneIsle_EventScript_Digger1_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

EmberduneIsle_EventScript_Digger1_Text_Beaten:
	.string "Wh-what? Our plans...$"

EmberduneIsle_EventScript_Digger1_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

EmberduneIsle_EventScript_Digger2_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

EmberduneIsle_EventScript_Digger2_Text_Beaten:
	.string "Wh-what? Our plans...$"

EmberduneIsle_EventScript_Digger2_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

EmberduneIsle_EventScript_Hiker_Text_Seen:
	.string "These rocks have been shaking with\nthunder all week! Let's battle!$"

EmberduneIsle_EventScript_Hiker_Text_Beaten:
	.string "Whoa, you've got legs of steel!$"

EmberduneIsle_EventScript_Hiker_Text_After:
	.string "A real hiker never fears a storm.$"

EmberduneIsle_EventScript_RuinManiac_Text_Seen:
	.string "These ruins hold the legend of the\nHero of Truth! Don't touch anything!$"

EmberduneIsle_EventScript_RuinManiac_Text_Beaten:
	.string "Ahh, my notes!$"

EmberduneIsle_EventScript_RuinManiac_Text_After:
	.string "The murals speak of a white stone\nthat sleeps under the sand.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/EmberduneIsle.inc)
EmberduneIsle_EventScript_Hilda::
	msgbox EmberduneIsle_EventScript_Hilda_Text, MSGBOX_NPC
	end

EmberduneIsle_EventScript_Hilda_Text:
	.string "{SPEAKER NAME_HILDA}The Light Stone... Reshiram once\n"
	.string "chose me, you know.\p"
	.string "If Ghetsis gets his hands on it,\n"
	.string "he'll have both dragons. We\n"
	.string "can't let that happen.$"

EmberduneIsle_EventScript_Lenora::
	msgbox EmberduneIsle_EventScript_Lenora_Text, MSGBOX_NPC
	end

EmberduneIsle_EventScript_Lenora_Text:
	.string "{SPEAKER NAME_LENORA}Those ruins in the cliff are\n"
	.string "just like the Relic Castle. Watch\n"
	.string "out for the sand. It swallows!$"

EmberduneIsle_EventScript_Bea::
	msgbox EmberduneIsle_EventScript_Bea_Text, MSGBOX_NPC
	end

EmberduneIsle_EventScript_Bea_Text:
	.string "{SPEAKER NAME_BEA}Training in this heat sharpens\n"
	.string "the mind. Want to try?$"

EmberduneIsle_EventScript_Greta::
	lock
	faceplayer
	goto_if_defeated TRAINER_ABUNDANCE_GRETA, EmberduneIsle_EventScript_Greta_After
	msgbox EmberduneIsle_EventScript_Greta_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GRETA, EmberduneIsle_EventScript_Greta_TextBeaten
	release
	end

EmberduneIsle_EventScript_Greta_After::
	msgbox EmberduneIsle_EventScript_Greta_TextAfter, MSGBOX_DEFAULT
	release
	end

EmberduneIsle_EventScript_Greta_TextChallenge:
	.string "{SPEAKER NAME_GRETA}You beat those diggers? Then\n"
	.string "battle me, Arena style!$"
EmberduneIsle_EventScript_Greta_TextBeaten:
	.string "Greta: Whoa, what a fighter!$"
EmberduneIsle_EventScript_Greta_TextAfter:
	.string "{SPEAKER NAME_GRETA}Come back when you want a real\n"
	.string "workout!$"


