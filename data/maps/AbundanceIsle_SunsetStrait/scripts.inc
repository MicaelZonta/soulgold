AbundanceIsle_SunsetStrait_MapScripts::
	.byte 0

AbundanceIsle_SunsetStrait_EventScript_Swimmer1::
	trainerbattle_single TRAINER_ABUNDANCE_SUNSET_STRAIT_SWIMMER_1, AbundanceIsle_SunsetStrait_EventScript_Swimmer1_Text_Seen, AbundanceIsle_SunsetStrait_EventScript_Swimmer1_Text_Beaten
	msgbox AbundanceIsle_SunsetStrait_EventScript_Swimmer1_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_SunsetStrait_EventScript_Swimmer2::
	trainerbattle_single TRAINER_ABUNDANCE_SUNSET_STRAIT_SWIMMER_2, AbundanceIsle_SunsetStrait_EventScript_Swimmer2_Text_Seen, AbundanceIsle_SunsetStrait_EventScript_Swimmer2_Text_Beaten
	msgbox AbundanceIsle_SunsetStrait_EventScript_Swimmer2_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_SunsetStrait_EventScript_Swimmer3::
	trainerbattle_single TRAINER_ABUNDANCE_SUNSET_STRAIT_SWIMMER_3, AbundanceIsle_SunsetStrait_EventScript_Swimmer3_Text_Seen, AbundanceIsle_SunsetStrait_EventScript_Swimmer3_Text_Beaten
	msgbox AbundanceIsle_SunsetStrait_EventScript_Swimmer3_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_SunsetStrait_EventScript_Swimmer4::
	trainerbattle_single TRAINER_ABUNDANCE_SUNSET_STRAIT_SWIMMER_4, AbundanceIsle_SunsetStrait_EventScript_Swimmer4_Text_Seen, AbundanceIsle_SunsetStrait_EventScript_Swimmer4_Text_Beaten
	msgbox AbundanceIsle_SunsetStrait_EventScript_Swimmer4_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_SunsetStrait_EventScript_Swimmer1_Text_Seen:
	.string "Out here, only the strong swimmers\nmake it. Show me!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer1_Text_Beaten:
	.string "Glub... You win!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer1_Text_After:
	.string "The current pulls south, toward\nthe sand island.$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer2_Text_Seen:
	.string "The water here is so warm, even\nwith all this strange weather!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer2_Text_Beaten:
	.string "I'm all washed up!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer2_Text_After:
	.string "Swimming is the best way to cross\nthe strait.$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer3_Text_Seen:
	.string "Out here, only the strong swimmers\nmake it. Show me!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer3_Text_Beaten:
	.string "Glub... You win!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer3_Text_After:
	.string "The current pulls south, toward\nthe sand island.$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer4_Text_Seen:
	.string "The water here is so warm, even\nwith all this strange weather!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer4_Text_Beaten:
	.string "I'm all washed up!$"

AbundanceIsle_SunsetStrait_EventScript_Swimmer4_Text_After:
	.string "Swimming is the best way to cross\nthe strait.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_SunsetStrait.inc)
AbundanceIsle_SunsetStrait_EventScript_Shelly::
	msgbox AbundanceIsle_SunsetStrait_EventScript_Shelly_Text, MSGBOX_NPC
	end

AbundanceIsle_SunsetStrait_EventScript_Shelly_Text:
	.string "{SPEAKER NAME_SHELLY}The sunsets here are the\n"
	.string "best in the world. Don't argue.$"

AbundanceIsle_SunsetStrait_EventScript_Juan::
	msgbox AbundanceIsle_SunsetStrait_EventScript_Juan_Text, MSGBOX_NPC
	end

AbundanceIsle_SunsetStrait_EventScript_Juan_Text:
	.string "{SPEAKER NAME_JUAN}Beneath these waves sleeps an\n"
	.string "old ship. The water remembers it.$"

AbundanceIsle_SunsetStrait_EventScript_Tate::
	msgbox AbundanceIsle_SunsetStrait_EventScript_Tate_Text, MSGBOX_NPC
	end

AbundanceIsle_SunsetStrait_EventScript_Tate_Text:
	.string "{SPEAKER NAME_TATE}Liza went to the shrine without\n"
	.string "me! We always do things together!$"


