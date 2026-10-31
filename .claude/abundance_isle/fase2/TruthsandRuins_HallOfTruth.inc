TruthsandRuins_HallOfTruth_EventScript_Ghetsis::
	lock
	faceplayer
	msgbox TruthsandRuins_HallOfTruth_Text_GhetsisLast, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GHETSIS_3, TruthsandRuins_HallOfTruth_Text_GhetsisBeaten
	msgbox TruthsandRuins_HallOfTruth_Text_StoneShines, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_GHETSIS
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_GRUNT_1
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_GRUNT_2
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_HILDA
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_LENORA
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_LIGHT_STONE
	clearflag FLAG_TEMP_13
	addobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_RESHIRAM
	addobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_HILDA_AFTER
	setvar VAR_ABUNDANCE_ISLE_STATE, 12
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox TruthsandRuins_HallOfTruth_Text_ReshiramRefuses, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_HallOfTruth_Text_GhetsisLast:
	.string "{SPEAKER NAME_GHETSIS}The Light Stone is mine! If one\n"
	.string "dragon will not obey, the other\n"
	.string "shall!\p"
	.string "{SPEAKER NAME_HILDA}Truth isn't something you can\n"
	.string "steal, Ghetsis. It finds you.$"
TruthsandRuins_HallOfTruth_Text_GhetsisBeaten:
	.string "Ghetsis: This... cannot... be...$"
TruthsandRuins_HallOfTruth_Text_StoneShines:
	.string "The Light Stone blazes with white\n"
	.string "fire... and shines toward Hilda!$"
TruthsandRuins_HallOfTruth_Text_ReshiramRefuses:
	.string "Reshiram's flames drove Ghetsis\n"
	.string "and his grunts out of the ruins.\p"
	.string "{SPEAKER NAME_HILDA}It remembers me... but it's\n"
	.string "looking at you, {PLAYER}.\n"
	.string "Go on. Show it your truth.$"
TruthsandRuins_HallOfTruth_EventScript_Reshiram::
	lock
	faceplayer
	msgbox TruthsandRuins_HallOfTruth_EventScript_Reshiram_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_RESHIRAM, 75, LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_RESHIRAM, FLAG_TEMP_13, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, TruthsandRuins_HallOfTruth_EventScript_Reshiram_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, TruthsandRuins_HallOfTruth_EventScript_Reshiram_Beaten
	release
	end

TruthsandRuins_HallOfTruth_EventScript_Reshiram_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_13
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_RESHIRAM
	fadescreenswapbuffers FADE_FROM_BLACK
TruthsandRuins_HallOfTruth_EventScript_Reshiram_Done:
	setflag FLAG_ABUNDANCE_RESHIRAM_DONE
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 12, TruthsandRuins_HallOfTruth_EventScript_Reshiram_Advance
	release
	end

TruthsandRuins_HallOfTruth_EventScript_Reshiram_Advance:
	setvar VAR_ABUNDANCE_ISLE_STATE, 13
	return

TruthsandRuins_HallOfTruth_EventScript_Reshiram_Text_Intro:
	.string "White flames fill the hall.\n"
	.string "Reshiram challenges you!$"
TruthsandRuins_HallOfTruth_EventScript_HildaAfter::
	lock
	faceplayer
	msgbox TruthsandRuins_HallOfTruth_EventScript_HildaAfter_Text, MSGBOX_DEFAULT
	release
	end

TruthsandRuins_HallOfTruth_EventScript_HildaAfter_Text:
	.string "{SPEAKER NAME_HILDA}There's a sealed door on an islet\n"
	.string "in the strait. Bring both dragons.\n"
	.string "N will meet us there.$"

TruthsandRuins_HallOfTruth_EventScript_LightStone::
	msgbox TruthsandRuins_HallOfTruth_EventScript_LightStone_Text, MSGBOX_NPC
	end

TruthsandRuins_HallOfTruth_EventScript_LightStone_Text:
	.string "A white stone, warm to the touch.\n"
	.string "Something sleeps inside it.$"

TruthsandRuins_HallOfTruth_EventScript_MuralTwinHeroes::
	lockall
	msgbox TruthsandRuins_HallOfTruth_EventScript_MuralTwinHeroes_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_MURAL_5
	releaseall
	end

TruthsandRuins_HallOfTruth_EventScript_MuralTwinHeroes_Text:
	.string "Twin heroes stand back to back,\n"
	.string "a dragon of fire and a dragon\n"
	.string "of lightning above them.$"

TruthsandRuins_HallOfTruth_EventScript_MuralTruth::
	msgbox TruthsandRuins_HallOfTruth_EventScript_MuralTruth_Text, MSGBOX_SIGN
	end

TruthsandRuins_HallOfTruth_EventScript_MuralTruth_Text:
	.string "“Truth is not a thing to be owned.\n"
	.string "It is a fire that shows what is.”$"

TruthsandRuins_HallOfTruth_EventScript_AltarDoor::
	msgbox TruthsandRuins_HallOfTruth_EventScript_AltarDoor_Text, MSGBOX_SIGN
	end

TruthsandRuins_HallOfTruth_EventScript_AltarDoor_Text:
	.string "A white stone rests on the altar.$"

TruthsandRuins_HallOfTruth_EventScript_Grunt1::
	msgbox TruthsandRuins_HallOfTruth_EventScript_Grunt1_Text, MSGBOX_NPC
	end

TruthsandRuins_HallOfTruth_EventScript_Grunt1_Text:
	.string "{SPEAKER NAME_GRUNT}Lord Ghetsis is at the altar.\n"
	.string "You're too late!$"

TruthsandRuins_HallOfTruth_EventScript_Grunt2::
	msgbox TruthsandRuins_HallOfTruth_EventScript_Grunt2_Text, MSGBOX_NPC
	end

TruthsandRuins_HallOfTruth_EventScript_Grunt2_Text:
	.string "{SPEAKER NAME_GRUNT}The Light Stone will be ours!\n"
	.string "Then both dragons obey us!$"

TruthsandRuins_HallOfTruth_EventScript_Hilda::
	msgbox TruthsandRuins_HallOfTruth_EventScript_Hilda_Text, MSGBOX_NPC
	end

TruthsandRuins_HallOfTruth_EventScript_Hilda_Text:
	.string "{SPEAKER NAME_HILDA}Ghetsis is right there. We\n"
	.string "stop him here, together.$"

TruthsandRuins_HallOfTruth_EventScript_Lenora::
	msgbox TruthsandRuins_HallOfTruth_EventScript_Lenora_Text, MSGBOX_NPC
	end

TruthsandRuins_HallOfTruth_EventScript_Lenora_Text:
	.string "{SPEAKER NAME_LENORA}History won't repeat itself.\n"
	.string "Not on my watch!$"

