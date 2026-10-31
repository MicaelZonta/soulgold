MtEmber_Summit_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_Summit_OnTransition
	.byte 0

@ O cume tem duas portas para fora: a das Sevii e a do Mt. Gold (Johto), nas
@ mesmas coordenadas. A saida volta para a que o jogador usou para entrar.
@ O Moltres do FireRed saiu daqui (ele mora no Mt. Silver).
MtEmber_Summit_OnTransition:
	call MtEmber_Summit_EventScript_SetExit
	call MtEmberResidents_OnTransition
	end

@ A porta de saida e MAP_DYNAMIC: volta para o exterior por onde o jogador
@ entrou (VAR_MT_EMBER_SIDE, gravada no ON_TRANSITION de cada exterior).
MtEmber_Summit_EventScript_SetExit:
	goto_if_eq VAR_MT_EMBER_SIDE, 1, MtEmber_Summit_EventScript_ExitToMtGold
	setdynamicwarp MAP_MT_EMBER_EXTERIOR, 4
	return

MtEmber_Summit_EventScript_ExitToMtGold:
	setdynamicwarp MAP_MT_GOLD_OUTSIDE, 2
	return
