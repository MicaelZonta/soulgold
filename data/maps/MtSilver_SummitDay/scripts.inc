
MtSilver_SummitDay_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_SummitDay_OnTransition
	.byte 0

MtSilver_SummitDay_OnFrame::
	map_script_2 VAR_TEMP_0, 0 MtSilver_SummitDay_Blizzard
	.2byte 0

MtSilver_SummitDay_Blizzard::
	playse SE_M_BLIZZARD
	setvar VAR_TEMP_0, 1
	end

MtSilver_SummitDay_OnTransition:
    call Common_EventScript_SetupRivalGfxId
	call_if_set FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetDay
	@ Revezamento do topo: antes da primeira vitoria sobre o rival, o Red
	@ nunca aparece (o LeaveBoat do S.S. Aqua limpa FLAG_HIDE_MTSILVER_RED,
	@ entao escondemos de novo aqui). Depois dela, Red fica com domingo (0),
	@ quarta (3) e sabado (6); o rival com os demais dias.
	goto_if_unset FLAG_DEFEATED_MTSILVER_RIVAL, MtSilver_Summit_Transition_PreDefeat
	compare VAR_DAY_OF_WEEK, 0
	goto_if_eq MtSilver_Summit_Transition_RedDay
	compare VAR_DAY_OF_WEEK, 3
	goto_if_eq MtSilver_Summit_Transition_RedDay
	compare VAR_DAY_OF_WEEK, 6
	goto_if_eq MtSilver_Summit_Transition_RedDay
	clearflag FLAG_HIDE_MTSILVER_RIVAL
	setflag FLAG_HIDE_MTSILVER_RED
	cleartrainerflag TRAINER_RIVAL_GOLD_FINAL
	cleartrainerflag TRAINER_RIVAL_CRYSTAL_FINAL
	end

MtSilver_Summit_Transition_RedDay:
	setflag FLAG_HIDE_MTSILVER_RIVAL
	clearflag FLAG_HIDE_MTSILVER_RED
	cleartrainerflag TRAINER_RED
	end

MtSilver_Summit_Transition_PreDefeat:
	setflag FLAG_HIDE_MTSILVER_RED
	end

MtSilver_SummitDay_OnTransition_SetLayout:
	call_if_set FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, MtSilver_SummitDay_EventScript_SetDay
	end

MtSilver_SummitDay_EventScript_SetNight::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_NIGHT
	return

MtSilver_SummitDay_EventScript_SetDay::
	setmaplayoutindex LAYOUT_MT_SILVER_SUMMIT_DAY
	return

MtSilver_SummitDay_EventScript_Rival::
	lock
	goto_if_set FLAG_DEFEATED_MTSILVER_RIVAL, MtSilver_SummitDay_EventScript_Rival_2
MtSilver_SummitDay_EventScript_Rival_1:
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq MtSilver_SummitDay_EventScript_Rival_5
MtSilver_SummitDay_EventScript_Rival_4:
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_0
	delay 30
	faceplayer
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_1
	closemessage
	applymovement LOCALID_MTSILVER_RIVAL, MtSilver_SummitDay_EventScript_Rival_Movement_0
	waitmovement 0
	delay 30
	faceplayer
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_2
	removefieldmugshot
	closemessage
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq MtSilver_SummitDay_EventScript_Rival_8
	trainerbattle_no_intro TRAINER_RIVAL_GOLD_FINAL, MtSilver_SummitDay_EventScript_Rival_Text_3
MtSilver_SummitDay_EventScript_Rival_7:
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN
	createfieldmugshotrival
	delay 30
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_4
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_5
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_6
	playfanfare MUS_OBTAIN_ITEM
	removefieldmugshot
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_7
	waitfanfare
	giveegg SPECIES_TERAPAGOS
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq MtSilver_SummitDay_EventScript_Rival_14
MtSilver_SummitDay_EventScript_Rival_13:
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_9
	removefieldmugshot
	closemessage
	fadescreenspeed FADE_TO_BLACK, 24
	setflag FLAG_HIDE_MTSILVER_RIVAL
	removeobject LOCALID_MTSILVER_RIVAL
	setflag FLAG_DEFEATED_MTSILVER_RIVAL
	setvar VAR_RIVAL_STATE, 12
	clearflag FLAG_HIDE_NEWBARK_RIVAL
	clearflag FLAG_HIDE_RIVAL_AZUMARILL
	setflag FLAG_HIDE_RIVAL_MARILL
	delay 40
	warp MAP_NEW_BARK_TOWN_HOUSE3, 33, 3
	waitstate
	releaseall
	end

MtSilver_SummitDay_EventScript_Rival_2:
	goto MtSilver_SummitDay_EventScript_RivalPostgame
	goto MtSilver_SummitDay_EventScript_Rival_1

MtSilver_SummitDay_EventScript_Rival_5:
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	compare VAR_RESULT, FALSE
	goto_if_eq MtSilver_SummitDay_EventScript_Rival_11
	goto MtSilver_SummitDay_EventScript_Rival_4

MtSilver_SummitDay_EventScript_Rival_8:
	trainerbattle_no_intro TRAINER_RIVAL_CRYSTAL_FINAL, MtSilver_SummitDay_EventScript_Rival_Text_3
	goto MtSilver_SummitDay_EventScript_Rival_7

MtSilver_SummitDay_EventScript_Rival_11:
	goto MtSilver_SummitDay_EventScript_RivalNoRoom
	goto MtSilver_SummitDay_EventScript_Rival_4

MtSilver_SummitDay_EventScript_Rival_14:
	setflag FLAG_RIVAL_SUMMIT_EGG_PENDING
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_Rival_Text_8
	removefieldmugshot
	goto MtSilver_SummitDay_EventScript_Rival_13


MtSilver_SummitDay_EventScript_RivalNoRoom::
	faceplayer
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_RivalNoRoom_Text_0
	removefieldmugshot
	release
	end


MtSilver_SummitDay_EventScript_RivalPostgame::
	faceplayer
	goto_if_set FLAG_RIVAL_SUMMIT_EGG_PENDING, MtSilver_SummitDay_EventScript_RivalPostgame_2
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_RivalPostgame_Text_4
	removefieldmugshot
	closemessage
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq MtSilver_SummitDay_EventScript_RivalPostgame_5
	trainerbattle_no_intro TRAINER_RIVAL_GOLD_FINAL, MtSilver_SummitDay_EventScript_RivalPostgame_Text_5
MtSilver_SummitDay_EventScript_RivalPostgame_4:
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_RivalPostgame_Text_6
	removefieldmugshot
	release
	end

MtSilver_SummitDay_EventScript_RivalPostgame_2:
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq MtSilver_SummitDay_EventScript_RivalPostgame_9
MtSilver_SummitDay_EventScript_RivalPostgame_8:
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_RivalPostgame_Text_1
	playfanfare MUS_OBTAIN_ITEM
	removefieldmugshot
	msgbox MtSilver_SummitDay_EventScript_RivalPostgame_Text_2
	waitfanfare
	giveegg SPECIES_TERAPAGOS
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq MtSilver_SummitDay_EventScript_RivalPostgame_12
	clearflag FLAG_RIVAL_SUMMIT_EGG_PENDING
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_RivalPostgame_Text_3
	removefieldmugshot
	release
	end

MtSilver_SummitDay_EventScript_RivalPostgame_5:
	trainerbattle_no_intro TRAINER_RIVAL_CRYSTAL_FINAL, MtSilver_SummitDay_EventScript_RivalPostgame_Text_5
	goto MtSilver_SummitDay_EventScript_RivalPostgame_4

MtSilver_SummitDay_EventScript_RivalPostgame_9:
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	compare VAR_RESULT, FALSE
	goto_if_eq MtSilver_SummitDay_EventScript_RivalPostgame_14
	goto MtSilver_SummitDay_EventScript_RivalPostgame_8

MtSilver_SummitDay_EventScript_RivalPostgame_12:
	release
	end

MtSilver_SummitDay_EventScript_RivalPostgame_14:
	createfieldmugshotrival
	msgbox MtSilver_SummitDay_EventScript_RivalPostgame_Text_0
	removefieldmugshot
	release
	end


MtSilver_SummitDay_EventScript_Red::
	lock
	faceplayer
	msgbox MtSilver_SummitDay_EventScript_Red_Text_0
	closemessage
	delay 20
	msgbox MtSilver_SummitDay_EventScript_Red_Text_1
	closemessage
	trainerbattle_no_intro TRAINER_RED, MtSilver_SummitDay_EventScript_Red_Text_2
	goto_if_unset FLAG_DEFEATED_RED, MtSilver_SummitDay_EventScript_Red_2
MtSilver_SummitDay_EventScript_Red_1:
	msgbox MtSilver_SummitDay_EventScript_Red_Text_3
	release
	end

MtSilver_SummitDay_EventScript_Red_2:
	setflag FLAG_DEFEATED_RED
	goto MtSilver_SummitDay_EventScript_Red_1


MtSilver_SummitDay_EventScript_Rival_Movement_0:
	walk_in_place_up
	step_end

MtSilver_SummitDay_EventScript_Rival_Text_0:
	.string "I knew you'd come here.$"

MtSilver_SummitDay_EventScript_Rival_Text_1:
	.string "I've been up here thinking.\n"
	.string "Not much else to do.\p"
	.string "I kept telling myself,\n"
	.string "one more badge. One more win.\p"
	.string "Then I would finally catch up.\p"
	.string "Silly isn't it? In the end I was\n"
	.string "just trying to stand out.\p"
	.string "Assuming everyone had some sort of\n"
	.string "expectation of me to reach these\l"
	.string "heights and become the best.$"

MtSilver_SummitDay_EventScript_Rival_Text_2:
	.string "In the end it was just all in my head\n"
	.string "when you get down to it, haha.\p"
	.string "So! I want you, {PLAYER} to give me\n"
	.string "one last battle to knock some sense\l"
	.string "into me!\p"
	.string "Not asking as a bitter rival,\n"
	.string "but as your best friend!\p"
	.string "I got nothing to prove, but let's\n"
	.string "have fun like we used to.$"

MtSilver_SummitDay_EventScript_Rival_Text_3:
	.string "Hah, nice one.$"

MtSilver_SummitDay_EventScript_Rival_Text_4:
	.string "Okay.\n"
	.string "That's what I needed.$"

MtSilver_SummitDay_EventScript_Rival_Text_5:
	.string "You always do the battling\n"
	.string "with a smile, I felt that too\l"
	.string "in this battle.$"

MtSilver_SummitDay_EventScript_Rival_Text_6:
	.string "When I was just standing here alone, I\n"
	.string "was wishing you could arrive.\p"
	.string "then, I saw this egg in the ground\n"
	.string "here.\p"
	.string "I think it appeared in reaction to my\n"
	.string "wish, but you should have it instead.\p"
	.string "After all, you made my wish come true!\p"
	.string "So, thanks {PLAYER}.$"

MtSilver_SummitDay_EventScript_Rival_Text_7:
	.string "{PLAYER} received an Egg!$"

MtSilver_SummitDay_EventScript_Rival_Text_8:
	.string "Huh, no room after all?\n"
	.string "Then I'll hold onto it for you.\p"
	.string "Come find me up here again\n"
	.string "and it's yours, promise!$"

MtSilver_SummitDay_EventScript_Rival_Text_9:
	.string "Now c'mon, let's race back home!\p"
	.string "My fingers are freezing from just\n"
	.string "standing around here.$"

MtSilver_SummitDay_EventScript_RivalNoRoom_Text_0:
	.string "Whoa, hold up, {PLAYER}!\n"
	.string "Your team is full and your storage\l"
	.string "boxes are stuffed to the brim too.\p"
	.string "I've got something planned for\n"
	.string "after our battle, and I'm not\l"
	.string "letting it go to waste.\p"
	.string "Go make some room, then climb\n"
	.string "back up here. I'm not moving!$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_0:
	.string "Still no room for the egg, huh?\n"
	.string "Team full, boxes full.\p"
	.string "I'm keeping it warm for you.\n"
	.string "Come back when you've made space!$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_1:
	.string "You came back for the egg, right?\n"
	.string "Kept it nice and warm for you.$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_2:
	.string "{PLAYER} received the Egg!$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_3:
	.string "Take good care of it!$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_4:
	.string "Heh, caught me. I still come up\n"
	.string "here to train when I can.\p"
	.string "Y'know who else trains here?\n"
	.string "That quiet guy with the Pikachu.\l"
	.string "We kind of take turns.\p"
	.string "Since you climbed all this way,\n"
	.string "how about a battle, best friend?$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_5:
	.string "Hah! Still got that smile.$"

MtSilver_SummitDay_EventScript_RivalPostgame_Text_6:
	.string "Same time next week?\n"
	.string "I'm not giving up on beating\l"
	.string "you, best friend or not!$"

MtSilver_SummitDay_EventScript_Red_Text_0:
	.string "……$"

MtSilver_SummitDay_EventScript_Red_Text_1:
	.string "…!$"

MtSilver_SummitDay_EventScript_Red_Text_2:
	.string "………$"

MtSilver_SummitDay_EventScript_Red_Text_3:
	.string "……\p"
	.string "…………$"
