AbundanceIsle_SkylaHangar_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_SkylaHangar_OnTransition
	.byte 0

AbundanceIsle_SkylaHangar_OnTransition::
	call AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_11
	call AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_12
	end

AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_11::
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_11_Show
AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_11_No::
AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_11_Show_No::
	setflag FLAG_TEMP_11
	return
AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_11_Show::
	clearflag FLAG_TEMP_11
	return

AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_12::
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_12_Show
AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_12_No::
AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_12_Show_No::
	setflag FLAG_TEMP_12
	return
AbundanceIsle_SkylaHangar_EventScript_Vis_TEMP_12_Show::
	clearflag FLAG_TEMP_12
	return

@ ---------------- fase 2 (.claude/abundance_isle/fase2/AbundanceIsle_SkylaHangar.inc)
AbundanceIsle_SkylaHangar_EventScript_SkylaFlight::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_SKYLA_PLATE, AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_Offer
	msgbox AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_TextThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_SKY_PLATE
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_BagFull
	giveitem ITEM_SKY_PLATE
	setflag FLAG_ABUNDANCE_SKYLA_PLATE
AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_Offer::
	msgbox AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_TextOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_No
	msgbox AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_TextGo, MSGBOX_DEFAULT
	closemessage
	warp MAP_OLIVINE_CITY_PORT_OUTSIDE, 11, 5
	waitstate
	release
	end

AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_No::
	release
	end

AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_TextThanks:
	.string "{SPEAKER NAME_SKYLA}The skies are clear again! My\n"
	.string "plane can finally fly.\p"
	.string "Here, a little thank-you.$"
AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_TextOffer:
	.string "{SPEAKER NAME_SKYLA}Want a lift back to Olivine?\n"
	.string "It's a short hop!$"
AbundanceIsle_SkylaHangar_EventScript_SkylaFlight_TextGo:
	.string "{SPEAKER NAME_SKYLA}Buckle up!$"

AbundanceIsle_SkylaHangar_EventScript_SkylaGrounded::
	msgbox AbundanceIsle_SkylaHangar_EventScript_SkylaGrounded_Text, MSGBOX_NPC
	end

AbundanceIsle_SkylaHangar_EventScript_SkylaGrounded_Text:
	.string "{SPEAKER NAME_SKYLA}My cargo plane is stuck here.\n"
	.string "Nobody flies into a storm that\n"
	.string "never ends.$"

AbundanceIsle_SkylaHangar_EventScript_Mechanic::
	msgbox AbundanceIsle_SkylaHangar_EventScript_Mechanic_Text, MSGBOX_NPC
	end

AbundanceIsle_SkylaHangar_EventScript_Mechanic_Text:
	.string "{SPEAKER NAME_MECHANIC}The engine's fine. It's the\n"
	.string "weather that's broken!\p"
	.string "No pilot flies into a storm that\n"
	.string "turns in circles.$"


