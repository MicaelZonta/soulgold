AbundanceIsle_ElderHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_ElderHouse_OnTransition
	.byte 0

AbundanceIsle_ElderHouse_OnTransition::
	call AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_11
	call AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_12
	end

AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_11::
	gettime
	goto_if_lt VAR_0x8000, 18, AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_11_Show
AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_11_No::
AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_12::
	gettime
	goto_if_ge VAR_0x8000, 18, AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_12_Show
AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_12_No::
AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_12_Show_No::
	setflag FLAG_TEMP_12
	return
AbundanceIsle_ElderHouse_EventScript_Vis_TEMP_12_Show::
	clearflag FLAG_TEMP_12
	return

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_ElderHouse.inc)
AbundanceIsle_ElderHouse_EventScript_Elder::
	msgbox AbundanceIsle_ElderHouse_EventScript_Elder_Text, MSGBOX_NPC
	end

AbundanceIsle_ElderHouse_EventScript_Elder_Text:
	.string "The bell of this house rings at\n"
	.string "dusk, to call the harvest home.\p"
	.string "It hasn't rung since the snow.\n"
	.string "Nothing is coming home.$"

AbundanceIsle_ElderHouse_EventScript_Granddaughter::
	msgbox AbundanceIsle_ElderHouse_EventScript_Granddaughter_Text, MSGBOX_NPC
	end

AbundanceIsle_ElderHouse_EventScript_Granddaughter_Text:
	.string "Grandpa rings the bell every\n"
	.string "evening. Come back at dusk!$"

AbundanceIsle_ElderHouse_EventScript_ElderBellTime::
	msgbox AbundanceIsle_ElderHouse_EventScript_ElderBellTime_Text, MSGBOX_NPC
	end

AbundanceIsle_ElderHouse_EventScript_ElderBellTime_Text:
	.string "Dusk... time for the bell.\p"
	.string "Ding... dong...\n"
	.string "May the harvest come home.$"

AbundanceIsle_ElderHouse_EventScript_BookYearWithoutHarvest::
	msgbox AbundanceIsle_ElderHouse_EventScript_BookYearWithoutHarvest_Text, MSGBOX_SIGN
	end

AbundanceIsle_ElderHouse_EventScript_BookYearWithoutHarvest_Text:
	.string "“The Year Without Harvest.”\p"
	.string "“A star of ice fell into the\n"
	.string "crater. Snow covered the fields\n"
	.string "for a whole year...”$"

AbundanceIsle_ElderHouse_EventScript_BookForcesOfNature::
	msgbox AbundanceIsle_ElderHouse_EventScript_BookForcesOfNature_Text, MSGBOX_SIGN
	end

AbundanceIsle_ElderHouse_EventScript_BookForcesOfNature_Text:
	.string "“The Forces of Nature.”\p"
	.string "“The Wind Genie and the Thunder\n"
	.string "Genie fought over the sky. The\n"
	.string "Lord of the Land calmed them.”$"

AbundanceIsle_ElderHouse_EventScript_BookHeraldOfSpring::
	msgbox AbundanceIsle_ElderHouse_EventScript_BookHeraldOfSpring_Text, MSGBOX_SIGN
	end

AbundanceIsle_ElderHouse_EventScript_BookHeraldOfSpring_Text:
	.string "“The Herald of Spring.”\p"
	.string "“She comes from across the sea\n"
	.string "when the winter ends, and love\n"
	.string "blooms where she walks.”$"

AbundanceIsle_ElderHouse_EventScript_BellRope::
	msgbox AbundanceIsle_ElderHouse_EventScript_BellRope_Text, MSGBOX_SIGN
	end

AbundanceIsle_ElderHouse_EventScript_BellRope_Text:
	.string "The rope of the harvest bell.\n"
	.string "It's worn smooth by many hands.$"


