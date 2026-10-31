PlasmaFrigate_Cabins_MapScripts::
	.byte 0

PlasmaFrigate_Cabins_EventScript_QuartersGuard::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_CABINS_GHETSIS_GUARD, PlasmaFrigate_Cabins_EventScript_QuartersGuard_Text_Seen, PlasmaFrigate_Cabins_EventScript_QuartersGuard_Text_Beaten
	msgbox PlasmaFrigate_Cabins_EventScript_QuartersGuard_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Cabins_EventScript_LockerGrunt1::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_CABINS_GRUNT_LOCKER_1, PlasmaFrigate_Cabins_EventScript_LockerGrunt1_Text_Seen, PlasmaFrigate_Cabins_EventScript_LockerGrunt1_Text_Beaten
	msgbox PlasmaFrigate_Cabins_EventScript_LockerGrunt1_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Cabins_EventScript_LockerGrunt2::
	trainerbattle_single TRAINER_ABUNDANCE_PLASMA_FRIGATE_CABINS_GRUNT_LOCKER_2, PlasmaFrigate_Cabins_EventScript_LockerGrunt2_Text_Seen, PlasmaFrigate_Cabins_EventScript_LockerGrunt2_Text_Beaten
	msgbox PlasmaFrigate_Cabins_EventScript_LockerGrunt2_Text_After, MSGBOX_AUTOCLOSE
	end

PlasmaFrigate_Cabins_EventScript_WarpTrigger0::
	warp MAP_PLASMA_FRIGATE_DECK, 2
	waitstate
	end

PlasmaFrigate_Cabins_EventScript_WarpTrigger1::
	warp MAP_PLASMA_FRIGATE_DECK, 3
	waitstate
	end

PlasmaFrigate_Cabins_EventScript_QuartersGuard_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Cabins_EventScript_QuartersGuard_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Cabins_EventScript_QuartersGuard_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_Cabins_EventScript_LockerGrunt1_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Cabins_EventScript_LockerGrunt1_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Cabins_EventScript_LockerGrunt1_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

PlasmaFrigate_Cabins_EventScript_LockerGrunt2_Text_Seen:
	.string "Team Plasma has business on this\nisland. Get lost, kid!$"

PlasmaFrigate_Cabins_EventScript_LockerGrunt2_Text_Beaten:
	.string "Wh-what? Our plans...$"

PlasmaFrigate_Cabins_EventScript_LockerGrunt2_Text_After:
	.string "Lord Ghetsis will make this island\nours, no matter what you do.$"

@ ---------------- fase 2 (.claude/abundance_isle/fase2/PlasmaFrigate_Cabins.inc)
PlasmaFrigate_Cabins_EventScript_GhetsisDiary::
PlasmaFrigate_Cabins_EventScript_GhetsisPlans::
	lockall
	msgbox PlasmaFrigate_Cabins_Text_Plans, MSGBOX_DEFAULT
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 4, PlasmaFrigate_Cabins_EventScript_PlansRead
	releaseall
	end

PlasmaFrigate_Cabins_EventScript_PlansRead::
	setvar VAR_ABUNDANCE_ISLE_STATE, 5
	msgbox PlasmaFrigate_Cabins_Text_PlansRead, MSGBOX_DEFAULT
	return

PlasmaFrigate_Cabins_Text_Plans:
	.string "“The black stone sleeps until a\n"
	.string "storm born of frost calls it.”\p"
	.string "“Thunderspire. The summit.”\n"
	.string "“Zekrom + Kyurem = the Black\n"
	.string "dragon. The DNA Splicers are\n"
	.string "ready.”$"
PlasmaFrigate_Cabins_Text_PlansRead:
	.string "Ghetsis is heading for the summit\n"
	.string "of the Thunderspire!$"
PlasmaFrigate_Cabins_EventScript_UniformLocker::
	lockall
	goto_if_set FLAG_ABUNDANCE_PLASMA_UNIFORM, PlasmaFrigate_Cabins_EventScript_UniformLocker_Empty
	msgbox PlasmaFrigate_Cabins_EventScript_UniformLocker_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_PLASMA_UNIFORM
	releaseall
	end

PlasmaFrigate_Cabins_EventScript_UniformLocker_Empty::
	msgbox PlasmaFrigate_Cabins_EventScript_UniformLocker_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

PlasmaFrigate_Cabins_EventScript_UniformLocker_Text:
	.string "A spare Team Plasma uniform!\n"
	.string "{PLAYER} put it on over their\n"
	.string "clothes.\p"
	.string "Now the guards might let you\n"
	.string "pass...$"
PlasmaFrigate_Cabins_EventScript_UniformLocker_TextEmpty:
	.string "An empty locker.$"


