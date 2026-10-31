PlasmaFrigate_EngineRoom_MapScripts::
	.byte 0

PlasmaFrigate_EngineRoom_EventScript_ChiefScientist::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_ENGINE_ROOM_CHIEF, PlasmaFrigate_EngineRoom_EventScript_ChiefScientist_Text_Seen, PlasmaFrigate_EngineRoom_EventScript_ChiefScientist_Text_Beaten
	msgbox PlasmaFrigate_EngineRoom_EventScript_ChiefScientist_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_EngineRoom_EventScript_Assistant1::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_ENGINE_ROOM_ASSIST_1, PlasmaFrigate_EngineRoom_EventScript_Assistant1_Text_Seen, PlasmaFrigate_EngineRoom_EventScript_Assistant1_Text_Beaten
	msgbox PlasmaFrigate_EngineRoom_EventScript_Assistant1_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_EngineRoom_EventScript_Assistant2::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_ENGINE_ROOM_ASSIST_2, PlasmaFrigate_EngineRoom_EventScript_Assistant2_Text_Seen, PlasmaFrigate_EngineRoom_EventScript_Assistant2_Text_Beaten
	msgbox PlasmaFrigate_EngineRoom_EventScript_Assistant2_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_EngineRoom_EventScript_WarpTrigger0::
	warp MAP_PLASMA_FRIGATE_HOLD, 1
	waitstate
	end

PlasmaFrigate_EngineRoom_EventScript_ChiefScientist_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_EngineRoom_EventScript_ChiefScientist_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_EngineRoom_EventScript_ChiefScientist_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_EngineRoom_EventScript_Assistant1_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_EngineRoom_EventScript_Assistant1_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_EngineRoom_EventScript_Assistant1_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_EngineRoom_EventScript_Assistant2_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_EngineRoom_EventScript_Assistant2_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_EngineRoom_EventScript_Assistant2_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/PlasmaFrigate_EngineRoom.inc)
PlasmaFrigate_EngineRoom_EventScript_DNAConsole::
	msgbox PlasmaFrigate_EngineRoom_EventScript_DNAConsole_Text, MSGBOX_SIGN
	end

PlasmaFrigate_EngineRoom_EventScript_DNAConsole_Text:
	.string "“PROJECT: SPLIT DRAGON”\p"
	.string "“Goal: separate Kyurem from\n"
	.string "the cold and fuse it with the\n"
	.string "hero dragons.”$"

PlasmaFrigate_EngineRoom_EventScript_ColdCondenser::
	msgbox PlasmaFrigate_EngineRoom_EventScript_ColdCondenser_Text, MSGBOX_SIGN
	end

PlasmaFrigate_EngineRoom_EventScript_ColdCondenser_Text:
	.string "A condenser full of crackling\n"
	.string "ice. It hums with a deep cold.$"

PlasmaFrigate_EngineRoom_EventScript_ColdStorageDoor::
	msgbox PlasmaFrigate_EngineRoom_EventScript_ColdStorageDoor_Text, MSGBOX_SIGN
	end

PlasmaFrigate_EngineRoom_EventScript_ColdStorageDoor_Text:
	.string "“COLD STORAGE. Authorized\n"
	.string "personnel only.”$"


