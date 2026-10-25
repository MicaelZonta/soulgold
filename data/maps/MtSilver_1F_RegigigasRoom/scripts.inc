MtSilver_1F_RegigigasRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	setflag FLAG_HIDE_KELDEO
	goto_if_unset FLAG_CAUGHT_KELDEO, MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
	return

MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
	checkspecies SPECIES_COBALION
	compare VAR_RESULT, TRUE
	goto_if_eq MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_3
	return

MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_3:
	checkspecies SPECIES_TERRAKION
	compare VAR_RESULT, TRUE
	goto_if_eq MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_5
	return

MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_5:
	checkspecies SPECIES_VIRIZION
	compare VAR_RESULT, TRUE
	goto_if_eq MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_7
	return

MtSilver_1F_RegigigasRoom_MapScripts_MAP_SCRIPT_ON_TRANSITION_7:
	clearflag FLAG_HIDE_KELDEO
	return


MtSilver_Keldeo::
	lock
	faceplayer
	msgbox MtSilver_Keldeo_Text_0
	closemessage
	bosslegendaryencounter SPECIES_KELDEO, 80, LOCALID_MTSILVER_KELDEO, FLAG_HIDE_KELDEO, 2, SPECIES_NONE, 110
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq MtSilver_Keldeo_2
MtSilver_Keldeo_1:
	release
	end

MtSilver_Keldeo_2:
	setflag FLAG_CAUGHT_KELDEO
	goto MtSilver_Keldeo_1


MtSilver_Keldeo_Text_0:
	.string "The water at the far wall has not\n"
	.string "stopped moving since you walked in.\p\l"
	.string "Something steps out of it, and it\l"
	.string "is looking straight past you, at\l"
	.string "the three it came for.$"
