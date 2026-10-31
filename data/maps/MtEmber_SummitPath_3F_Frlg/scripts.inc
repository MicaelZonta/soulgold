MtEmber_SummitPath_3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_SummitPath_3F_OnTransition
	.byte 0

MtEmber_SummitPath_3F_OnTransition:
	call MtEmber_SummitPath_3F_EventScript_SetExit
	end

@ A porta de saida e MAP_DYNAMIC: volta para o exterior por onde o jogador
@ entrou (VAR_MT_EMBER_SIDE, gravada no ON_TRANSITION de cada exterior).
MtEmber_SummitPath_3F_EventScript_SetExit:
	goto_if_eq VAR_MT_EMBER_SIDE, 1, MtEmber_SummitPath_3F_EventScript_ExitToMtGold
	setdynamicwarp MAP_MT_EMBER_EXTERIOR, 3
	return

MtEmber_SummitPath_3F_EventScript_ExitToMtGold:
	setdynamicwarp MAP_MT_GOLD_OUTSIDE, 1
	return
