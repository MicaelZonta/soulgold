TruthsandRuins_B1F_MapScripts::
	.byte 0

TruthsandRuins_B1F_EventScript_PlasmaChief::
	trainerbattle_single TRAINER_ABUNDANCE_TRUTHSAND_RUINS_B1F_PLASMA_CHIEF, TruthsandRuins_B1F_EventScript_PlasmaChief_Text_Seen, TruthsandRuins_B1F_EventScript_PlasmaChief_Text_Beaten
	msgbox TruthsandRuins_B1F_EventScript_PlasmaChief_Text_After, MSGBOX_AUTOCLOSE
	end

TruthsandRuins_B1F_EventScript_Grunt::
	trainerbattle_single TRAINER_ABUNDANCE_TRUTHSAND_RUINS_B1F_GRUNT, TruthsandRuins_B1F_EventScript_Grunt_Text_Seen, TruthsandRuins_B1F_EventScript_Grunt_Text_Beaten
	msgbox TruthsandRuins_B1F_EventScript_Grunt_Text_After, MSGBOX_AUTOCLOSE
	end

TruthsandRuins_B1F_EventScript_RuinManiac::
	trainerbattle_single TRAINER_ABUNDANCE_TRUTHSAND_RUINS_B1F_RUIN_MANIAC, TruthsandRuins_B1F_EventScript_RuinManiac_Text_Seen, TruthsandRuins_B1F_EventScript_RuinManiac_Text_Beaten
	msgbox TruthsandRuins_B1F_EventScript_RuinManiac_Text_After, MSGBOX_AUTOCLOSE
	end

TruthsandRuins_B1F_EventScript_WarpTrigger4::
	lockall
	setwarp MAP_TRUTHSAND_RUINS_HALL_OF_TRUTH, 0
	special DoFallWarp
	waitstate
	end

TruthsandRuins_B1F_EventScript_PlasmaChief_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

TruthsandRuins_B1F_EventScript_PlasmaChief_Text_Beaten:
	.string "Wh-what? Our plans...$"

TruthsandRuins_B1F_EventScript_PlasmaChief_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

TruthsandRuins_B1F_EventScript_Grunt_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

TruthsandRuins_B1F_EventScript_Grunt_Text_Beaten:
	.string "Wh-what? Our plans...$"

TruthsandRuins_B1F_EventScript_Grunt_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

TruthsandRuins_B1F_EventScript_RuinManiac_Text_Seen:
	.string "These ruins hold the legend of the\nHero of Truth! Don't touch anything!$"

TruthsandRuins_B1F_EventScript_RuinManiac_Text_Beaten:
	.string "Ahh, my notes!$"

TruthsandRuins_B1F_EventScript_RuinManiac_Text_After:
	.string "The murals speak of a white stone\nthat sleeps under the sand.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/TruthsandRuins_B1F.inc)
TruthsandRuins_B1F_EventScript_Mural3::
	lockall
	msgbox TruthsandRuins_B1F_EventScript_Mural3_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_MURAL_3
	releaseall
	end

TruthsandRuins_B1F_EventScript_Mural3_Text:
	.string "An old stone obelisk, carved on\n"
	.string "every side.\p"
	.string "The dragon splits in two: white\n"
	.string "flame and black lightning.$"

TruthsandRuins_B1F_EventScript_Mural4::
	lockall
	msgbox TruthsandRuins_B1F_EventScript_Mural4_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_MURAL_4
	releaseall
	end

TruthsandRuins_B1F_EventScript_Mural4_Text:
	.string "An old stone obelisk, carved on\n"
	.string "every side.\p"
	.string "A third shape, cold and empty,\n"
	.string "is left behind in the ice.$"

TruthsandRuins_B1F_EventScript_Greta::
	msgbox TruthsandRuins_B1F_EventScript_Greta_Text, MSGBOX_NPC
	end

TruthsandRuins_B1F_EventScript_Greta_Text:
	.string "{SPEAKER NAME_GRETA}These ruins are a great\n"
	.string "workout. I'll meet you on\n"
	.string "Emberdune when you're ready!$"

TruthsandRuins_B1F_EventScript_GateInscription::
	msgbox TruthsandRuins_B1F_EventScript_GateInscription_Text, MSGBOX_SIGN
	end

TruthsandRuins_B1F_EventScript_GateInscription_Text:
	.string "“Beyond this gate rests the\n"
	.string "stone of truth. Enter with\n"
	.string "an honest heart.”$"

TruthsandRuins_B1F_EventScript_TrailInscription::
	msgbox TruthsandRuins_B1F_EventScript_TrailInscription_Text, MSGBOX_SIGN
	end

TruthsandRuins_B1F_EventScript_TrailInscription_Text:
	.string "“Follow the sun's path through\n"
	.string "the sand.”$"


