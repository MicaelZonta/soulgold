AbundanceIsle_HarvestFields_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_HarvestFields_OnTransition
	.byte 0

AbundanceIsle_HarvestFields_OnTransition::
	call AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_15
	call AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E
	end

AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_15::
	goto_if_eq VAR_ABUNDANCE_ROCKET_STAGE, 0, AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_15_Show
AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_15_No::
AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_15_Show_No::
	setflag FLAG_TEMP_15
	return
AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_15_Show::
	clearflag FLAG_TEMP_15
	return

AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E::
	gettime
	goto_if_lt VAR_0x8000, 6, AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E_Show_No
	goto_if_lt VAR_0x8000, 20, AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E_Show
AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E_No::
AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E_Show_No::
	setflag FLAG_TEMP_1E
	return
AbundanceIsle_HarvestFields_EventScript_Vis_TEMP_1E_Show::
	clearflag FLAG_TEMP_1E
	return

AbundanceIsle_HarvestFields_EventScript_Farmhand::
	trainerbattle_single TRAINER_ABUNDANCE_HARVEST_FIELDS_FARMHAND, AbundanceIsle_HarvestFields_EventScript_Farmhand_Text_Seen, AbundanceIsle_HarvestFields_EventScript_Farmhand_Text_Beaten
	msgbox AbundanceIsle_HarvestFields_EventScript_Farmhand_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_HarvestFields_EventScript_Lass::
	trainerbattle_single TRAINER_ABUNDANCE_HARVEST_FIELDS_LASS, AbundanceIsle_HarvestFields_EventScript_Lass_Text_Seen, AbundanceIsle_HarvestFields_EventScript_Lass_Text_Beaten
	msgbox AbundanceIsle_HarvestFields_EventScript_Lass_Text_After, MSGBOX_AUTOCLOSE
	end

AbundanceIsle_HarvestFields_EventScript_WarpTrigger1::
	warp MAP_ABUNDANCE_ISLE_SPRING_GROVE, 0
	waitstate
	end

AbundanceIsle_HarvestFields_EventScript_WarpTrigger2::
	warp MAP_ABUNDANCE_ISLE_SPRING_GROVE, 0
	waitstate
	end

AbundanceIsle_HarvestFields_EventScript_Farmhand_Text_Seen:
	.string "The farm needs every hand it can\nget. But first, a battle!$"

AbundanceIsle_HarvestFields_EventScript_Farmhand_Text_Beaten:
	.string "Back to work for me...$"

AbundanceIsle_HarvestFields_EventScript_Farmhand_Text_After:
	.string "This island lives on its harvest.$"

AbundanceIsle_HarvestFields_EventScript_Lass_Text_Seen:
	.string "Are you here because of the snow?\nLet's see how strong you are!$"

AbundanceIsle_HarvestFields_EventScript_Lass_Text_Beaten:
	.string "You're really good!$"

AbundanceIsle_HarvestFields_EventScript_Lass_Text_After:
	.string "Everyone here says the shrine\nis angry.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_HarvestFields.inc)
AbundanceIsle_HarvestFields_EventScript_Lenora::
	lock
	faceplayer
	goto_if_unset FLAG_ABUNDANCE_STELE_REWARD, AbundanceIsle_HarvestFields_EventScript_Lenora_SteleCheck
AbundanceIsle_HarvestFields_EventScript_Lenora_Main::
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 11, AbundanceIsle_HarvestFields_EventScript_LenoraGo
	goto_if_eq VAR_ABUNDANCE_ISLE_STATE, 10, AbundanceIsle_HarvestFields_EventScript_LenoraDecode
	msgbox AbundanceIsle_HarvestFields_Text_LenoraStele, MSGBOX_DEFAULT
	release
	end

@ Cena 16: o ato 6 comeca
AbundanceIsle_HarvestFields_EventScript_LenoraDecode::
	msgbox AbundanceIsle_HarvestFields_Text_LenoraDecode, MSGBOX_DEFAULT
	setvar VAR_ABUNDANCE_ISLE_STATE, 11
	release
	end

AbundanceIsle_HarvestFields_EventScript_LenoraGo::
	msgbox AbundanceIsle_HarvestFields_Text_LenoraGo, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_HarvestFields_Text_LenoraStele:
	.string "{SPEAKER NAME_LENORA}This stele is older than the\n"
	.string "farms. “...the Wind Genie carried\n"
	.string "the clouds...”\p"
	.string "I need more pieces to read the\n"
	.string "rest.$"
AbundanceIsle_HarvestFields_Text_LenoraDecode:
	.string "{SPEAKER NAME_LENORA}I've got it! The last line reads:\n"
	.string "“The light sleeps where the sun\n"
	.string "sets on sand.”\p"
	.string "There's an island of sand to the\n"
	.string "south, past the strait. Hilda is\n"
	.string "already on her way there!\p"
	.string "The Light Stone... if Team Plasma\n"
	.string "finds it first, who knows what\n"
	.string "Ghetsis will do!$"
AbundanceIsle_HarvestFields_Text_LenoraGo:
	.string "{SPEAKER NAME_LENORA}South, past the Sunset Strait.\n"
	.string "Emberdune Isle! Hurry!$"
AbundanceIsle_HarvestFields_EventScript_Lenora_SteleCheck::
	goto_if_unset FLAG_ABUNDANCE_STELE_1, AbundanceIsle_HarvestFields_EventScript_Lenora_Main
	goto_if_unset FLAG_ABUNDANCE_STELE_2, AbundanceIsle_HarvestFields_EventScript_Lenora_Main
	goto_if_unset FLAG_ABUNDANCE_STELE_3, AbundanceIsle_HarvestFields_EventScript_Lenora_Main
	goto_if_unset FLAG_ABUNDANCE_STELE_4, AbundanceIsle_HarvestFields_EventScript_Lenora_Main
	msgbox AbundanceIsle_HarvestFields_EventScript_Lenora_TextStele, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_LENORA, AbundanceIsle_HarvestFields_EventScript_Lenora_TextSteleBeaten
	checkitemspace ITEM_BIG_NUGGET
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_HarvestFields_EventScript_Lenora_BagFull
	giveitem ITEM_BIG_NUGGET
	setflag FLAG_ABUNDANCE_STELE_REWARD
	release
	end

AbundanceIsle_HarvestFields_EventScript_Lenora_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_HarvestFields_EventScript_Lenora_TextStele:
	.string "{SPEAKER NAME_LENORA}All four rubbings! Now the whole\n"
	.string "stele reads...\p"
	.string "“The genies quarreled, the lord\n"
	.string "came down, and the year the cold\n"
	.string "star fell, no lord came at all.”\p"
	.string "History is a battle of its own.\n"
	.string "Let's celebrate with one!$"
AbundanceIsle_HarvestFields_EventScript_Lenora_TextSteleBeaten:
	.string "Lenora: A textbook victory!$"

AbundanceIsle_HarvestFields_EventScript_Stele1::
	lockall
	goto_if_set FLAG_ABUNDANCE_STELE_1, AbundanceIsle_HarvestFields_EventScript_Stele1_Done
	msgbox AbundanceIsle_HarvestFields_EventScript_Stele1_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_STELE_1
	msgbox AbundanceIsle_HarvestFields_EventScript_Stele1_TextRub, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_HarvestFields_EventScript_Stele1_Done::
	msgbox AbundanceIsle_HarvestFields_EventScript_Stele1_Text, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_HarvestFields_EventScript_Stele1_Text:
	.string "A fragment of an old stele.\p"
	.string "“...the Wind Genie carried the\n"
	.string "clouds, the Thunder Genie broke\n"
	.string "the hard earth...”$"
AbundanceIsle_HarvestFields_EventScript_Stele1_TextRub:
	.string "{PLAYER} made a rubbing of the\n"
	.string "fragment for Lenora.$"

AbundanceIsle_HarvestFields_EventScript_Seed2::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_2, AbundanceIsle_HarvestFields_EventScript_Seed2_Empty
	msgbox AbundanceIsle_HarvestFields_EventScript_Seed2_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_2
	removeobject LOCALID_ABUNDANCE_ISLE_HARVEST_FIELDS_SEED_2
	releaseall
	end

AbundanceIsle_HarvestFields_EventScript_Seed2_Empty::
	msgbox AbundanceIsle_HarvestFields_EventScript_Seed2_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_HarvestFields_EventScript_Seed2_Text:
	.string "A sack of seeds blown here by the\n"
	.string "storm!\p"
	.string "{PLAYER} took the sack to return\n"
	.string "it to the farm.$"
AbundanceIsle_HarvestFields_EventScript_Seed2_TextEmpty:
	.string "Nothing here but a few stray\n"
	.string "seeds.$"

AbundanceIsle_HarvestFields_EventScript_Seed3::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_3, AbundanceIsle_HarvestFields_EventScript_Seed3_Empty
	msgbox AbundanceIsle_HarvestFields_EventScript_Seed3_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_3
	removeobject LOCALID_ABUNDANCE_ISLE_HARVEST_FIELDS_SEED_3
	releaseall
	end

AbundanceIsle_HarvestFields_EventScript_Seed3_Empty::
	msgbox AbundanceIsle_HarvestFields_EventScript_Seed3_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_HarvestFields_EventScript_Seed3_Text:
	.string "A sack of seeds blown here by the\n"
	.string "storm!\p"
	.string "{PLAYER} took the sack to return\n"
	.string "it to the farm.$"
AbundanceIsle_HarvestFields_EventScript_Seed3_TextEmpty:
	.string "Nothing here but a few stray\n"
	.string "seeds.$"

AbundanceIsle_HarvestFields_EventScript_JessieJames::
	lock
	faceplayer
	msgbox AbundanceIsle_HarvestFields_EventScript_JessieJames_Text, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_15
	removeobject LOCALID_ABUNDANCE_ISLE_HARVEST_FIELDS_JESSIE
	removeobject LOCALID_ABUNDANCE_ISLE_HARVEST_FIELDS_JAMES
	setvar VAR_ABUNDANCE_ROCKET_STAGE, 1
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

AbundanceIsle_HarvestFields_EventScript_JessieJames_Text:
	.string "{SPEAKER NAME_JESSIE}We're just two perfectly normal\n"
	.string "scarecrows! Nothing to see here!\p"
	.string "{SPEAKER NAME_JAMES}...Jessie, the twerp is staring.\n"
	.string "Retreat to the barn!$"

AbundanceIsle_HarvestFields_EventScript_DoorLocked::
	msgbox AbundanceIsle_HarvestFields_EventScript_DoorLocked_Text, MSGBOX_SIGN
	end

AbundanceIsle_HarvestFields_EventScript_DoorLocked_Text:
	.string "The door is locked. Everyone in\n"
	.string "the village has gone home for\n"
	.string "the night.$"


