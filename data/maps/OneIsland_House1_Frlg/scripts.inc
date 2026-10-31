OneIsland_House1_Frlg_MapScripts::
	.byte 0

OneIsland_House1_EventScript_OldMan::
	lock
	faceplayer
	call Pecharunt_GetState
	goto_if_eq VAR_RESULT, 1, OneIsland_House1_EventScript_OldManHunt
	goto_if_eq VAR_RESULT, 2, OneIsland_House1_EventScript_OldManAfter
	msgbox OneIsland_House1_Text_GazeUponVolcanoOnSunnyDays
	release
	end

OneIsland_House1_EventScript_OldManHunt:
	msgbox OneIsland_House1_Text_OldManHunt
	release
	end

OneIsland_House1_EventScript_OldManAfter:
	msgbox OneIsland_House1_Text_OldManAfter
	release
	end

OneIsland_House1_EventScript_OldWoman::
	lock
	faceplayer
	call Pecharunt_GetState
	goto_if_eq VAR_RESULT, 1, OneIsland_House1_EventScript_OldWomanHunt
	goto_if_eq VAR_RESULT, 2, OneIsland_House1_EventScript_OldWomanAfter
	msgbox OneIsland_House1_Text_LastTimeMtEmberErupted
	release
	end

OneIsland_House1_EventScript_OldWomanHunt:
	msgbox OneIsland_House1_Text_OldWomanHunt
	release
	end

OneIsland_House1_EventScript_OldWomanAfter:
	msgbox OneIsland_House1_Text_OldWomanAfter
	release
	end

OneIsland_House1_Text_GazeUponVolcanoOnSunnyDays::
	.string "On sunny days, I step out and gaze\n"
	.string "upon the volcano.\p"
	.string "That's my daily routine.$"

OneIsland_House1_Text_LastTimeMtEmberErupted::
	.string "Let me think… When was the last\n"
	.string "time MT. EMBER erupted?$"

