VermilionCity_PortOutside_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VermilionPort_OnFrame
	.byte 0

VermilionCity_PortOutside_EventScript_Fisher::
	msgbox VermilionCity_PortOutside_Text_Fisher, MSGBOX_NPC
	end

VermilionCity_PortOutside_Text_Fisher::
	.string "You just came from Johto?\n"
	.string "How's the fishin' over there\l"
	.string "...\p"
	.string "Johto has Red Gyarados?!$"
