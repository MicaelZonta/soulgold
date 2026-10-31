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

