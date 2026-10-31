OneIsland_Harbor_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OneIsland_Harbor_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OneIsland_Harbor_OnFrame
	.byte 0

@ O marinheiro esta em data/scripts/navel_rock_quest.inc (ele e o fim da
@ corrente que emite o Mystic Ticket e faz a balsa para Vermilion). A chegada
@ com o Bill esta em data/scripts/one_island.inc.
OneIsland_Harbor_OnTransition:
	setflag FLAG_TEMP_9
	call_if_eq VAR_ONE_ISLAND_STATE, 1, OneIsland_Harbor_EventScript_ShowBill
	end

OneIsland_Harbor_EventScript_ShowBill:
	clearflag FLAG_TEMP_9
	return

OneIsland_Harbor_OnFrame:
	map_script_2 VAR_ONE_ISLAND_STATE, 1, OneIsland_EventScript_BillArrival
	.2byte 0
