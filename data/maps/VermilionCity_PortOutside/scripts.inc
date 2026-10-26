VermilionCity_PortOutside_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_PortOutside_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VermilionPort_OnFrame
	.byte 0

@ Sem isto o Looker e a Anabel ficavam visiveis no cais o tempo todo: os
@ objetos tem FLAG_TEMP_B e C, que nascem limpas a cada carregamento de mapa,
@ e os removeobject do fim da cena so valem ate recarregar.
VermilionCity_PortOutside_OnTransition:
	setflag FLAG_TEMP_B
	setflag FLAG_TEMP_C
	end

VermilionCity_PortOutside_EventScript_Fisher::
	msgbox VermilionCity_PortOutside_Text_Fisher, MSGBOX_NPC
	end

VermilionCity_PortOutside_Text_Fisher::
	.string "You just came from Johto?\n"
	.string "How's the fishin' over there\l"
	.string "...\p"
	.string "Johto has Red Gyarados?!$"
