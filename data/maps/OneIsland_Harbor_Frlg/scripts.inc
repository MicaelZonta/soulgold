OneIsland_Harbor_Frlg_MapScripts::
	.byte 0


OneIsland_Harbor_Movement_PlayerExitHarbor::
	walk_up
	walk_up
	walk_up
	step_end

OneIsland_Harbor_EventScript_Sailor::
	lock
	faceplayer
	msgbox Text_WhereDoYouWantToSail, MSGBOX_DEFAULT
	closemessage
	release
	end
