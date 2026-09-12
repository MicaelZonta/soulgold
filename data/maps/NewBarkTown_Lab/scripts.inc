# 1 "data/maps/NewBarkTown_Lab/scripts.pory"

# 2 "data/maps/NewBarkTown_Lab/scripts.pory"

# 3 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_MapScripts::
# 4 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_OnTransition
# 5 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_Lab_OnFrame
# 6 "data/maps/NewBarkTown_Lab/scripts.pory"
	.byte 0
# 7 "data/maps/NewBarkTown_Lab/scripts.pory"

# 8 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_OnTransition::
# 9 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
# 10 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
# 11 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
# 12 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 13 "data/maps/NewBarkTown_Lab/scripts.pory"
	
# 14 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_OnFrame::
# 15 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script_2 VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
# 16 "data/maps/NewBarkTown_Lab/scripts.pory"
	.2byte 0
# 17 "data/maps/NewBarkTown_Lab/scripts.pory"

# 18 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAtComputer::
# 19 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxyperm LOCALID_ELM, 3, 2
# 20 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
# 21 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 22 "data/maps/NewBarkTown_Lab/scripts.pory"

# 23 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
# 24 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 25 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
# 26 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 27 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 28 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 29 "data/maps/NewBarkTown_Lab/scripts.pory"

# 30 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabRight::
# 31 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 32 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
# 33 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 34 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 35 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 36 "data/maps/NewBarkTown_Lab/scripts.pory"

# 37 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLab::
# 38 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 39 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
# 40 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 41 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmIntro
# 42 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 43 "data/maps/NewBarkTown_Lab/scripts.pory"

# 44 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide1::
# 45 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 46 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 47 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
# 48 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 49 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 50 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 51 "data/maps/NewBarkTown_Lab/scripts.pory"

# 52 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2::
# 53 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 54 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 55 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
# 56 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
# 57 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 58 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 59 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 60 "data/maps/NewBarkTown_Lab/scripts.pory"

# 61 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2Testimony::
# 62 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
# 63 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 64 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 65 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 66 "data/maps/NewBarkTown_Lab/scripts.pory"

# 67 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm::
# 68 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 69 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 70 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, NewBarkTown_Lab_EventScript_ElmAfterGladion
# 71 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_VIOLET_CITY_STATE, 4, NewBarkTown_Lab_EventScript_ElmGladionIsWaiting
# 72 "data/maps/NewBarkTown_Lab/scripts.pory"

# 73 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAfterGladion::
# 74 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
# 75 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
# 76 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
# 77 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmPostgameHint
# 78 "data/maps/NewBarkTown_Lab/scripts.pory"

# 79 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_CallMe
# 80 "data/maps/NewBarkTown_Lab/scripts.pory"
	call_if_unset FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_Check_Cosmog
# 81 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
# 82 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5
# 83 "data/maps/NewBarkTown_Lab/scripts.pory"

# 84 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
# 85 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
# 86 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
# 87 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
# 88 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 89 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 90 "data/maps/NewBarkTown_Lab/scripts.pory"

# 91 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmGladionIsWaiting::
# 92 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGladionIsWaiting, MSGBOX_DEFAULT
# 93 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 94 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 95 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 96 "data/maps/NewBarkTown_Lab/scripts.pory"

# 97 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGladionIsWaiting:
# 98 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 99 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What are you doing here?\p"
# 100 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gladion is waiting for you at\n"
# 101 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Violet City's Pokémon Center.\p"
# 102 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He has the Egg I wanted you to\n"
# 103 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "look after.$"
# 104 "data/maps/NewBarkTown_Lab/scripts.pory"

# 105 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmIntro::
# 106 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 107 "data/maps/NewBarkTown_Lab/scripts.pory"
	call ElmIntro
# 108 "data/maps/NewBarkTown_Lab/scripts.pory"
	@msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
# 109 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 110 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 111 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 112 "data/maps/NewBarkTown_Lab/scripts.pory"

# 113 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmRefused::
# 114 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 115 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
# 116 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 117 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 118 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 119 "data/maps/NewBarkTown_Lab/scripts.pory"

# 120 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAccepted::
# 121 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 122 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
# 123 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
# 124 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 125 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_LOGIN
# 126 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 127 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 128 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
# 129 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 130 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
# 131 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
# 132 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement LOCALID_ELM
# 133 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 134 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
# 135 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 136 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 137 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
# 138 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 139 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 140 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 141 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 142 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 143 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
# 144 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 145 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 146 "data/maps/NewBarkTown_Lab/scripts.pory"

# 147 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmChoosePokemon::
# 148 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 149 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Right
# 150 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 151 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 152 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
# 153 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 154 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 155 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Down
# 156 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 157 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
# 158 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 159 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 160 "data/maps/NewBarkTown_Lab/scripts.pory"

# 161 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
# 162 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 163 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 164 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
# 165 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 166 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 167 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
# 168 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 169 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 170 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 171 "data/maps/NewBarkTown_Lab/scripts.pory"

# 172 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ShouldntTouch::
# 173 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 174 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 175 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 176 "data/maps/NewBarkTown_Lab/scripts.pory"

# 177 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_hideStarterCase::
# 178 "data/maps/NewBarkTown_Lab/scripts.pory"
    setflag FLAG_HIDE_STARTER_CASE
# 179 "data/maps/NewBarkTown_Lab/scripts.pory"
    return
# 180 "data/maps/NewBarkTown_Lab/scripts.pory"

# 181 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase::
# 182 "data/maps/NewBarkTown_Lab/scripts.pory"
    lock
# 183 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_SOUTH, NewBarkTown_Lab_EventScript_StarterCaseWrongSide
# 184 "data/maps/NewBarkTown_Lab/scripts.pory"
	callnative MigrateNationalPokedex
# 185 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
# 186 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_StarterCase_Choice
# 187 "data/maps/NewBarkTown_Lab/scripts.pory"
    msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 188 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 189 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 190 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 191 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCaseWrongSide::
# 192 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_StarterCaseWrongSide, MSGBOX_DEFAULT
# 193 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 194 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 195 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 196 "data/maps/NewBarkTown_Lab/scripts.pory"

# 197 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase_Choice::
# 198 "data/maps/NewBarkTown_Lab/scripts.pory"
   callnative StartNewPokeballCaseUI
# 199 "data/maps/NewBarkTown_Lab/scripts.pory"
   waitstate
# 200 "data/maps/NewBarkTown_Lab/scripts.pory"
   goto NewBarkTown_Lab_EventScript_ChoseStarter
# 201 "data/maps/NewBarkTown_Lab/scripts.pory"

# 202 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter::
# 203 "data/maps/NewBarkTown_Lab/scripts.pory"
	showmonpic VAR_PLAYER_STARTER_SPECIES, 10, 3
# 204 "data/maps/NewBarkTown_Lab/scripts.pory"
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
# 205 "data/maps/NewBarkTown_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_PLAYER_STARTER_SPECIES
# 206 "data/maps/NewBarkTown_Lab/scripts.pory"
	message NewBarkTown_Lab_Text_ReceivedStarter
# 207 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE 1
# 208 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitfanfare
# 209 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 210 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 211 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_StepBackFromStarter
# 212 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 213 "data/maps/NewBarkTown_Lab/scripts.pory"
	updatefollowingmon
# 214 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxy OBJ_EVENT_ID_FOLLOWER, 9, 5
# 215 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterLeavesBall
# 216 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_BALL_OPEN
# 217 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 218 "data/maps/NewBarkTown_Lab/scripts.pory"
	playmoncry VAR_PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
# 219 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_LEDGE
# 220 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterGreetsPlayer
# 221 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 222 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmoncry
# 223 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 45
# 224 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 225 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
# 226 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 227 "data/maps/NewBarkTown_Lab/scripts.pory"
    closemessage
# 228 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 229 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 230 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 231 "data/maps/NewBarkTown_Lab/scripts.pory"

# 232 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter2::
# 233 "data/maps/NewBarkTown_Lab/scripts.pory"
    moveobjecttocoords OBJ_EVENT_ID_PLAYER, 6, 4, DIR_NORTH
# 234 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 235 "data/maps/NewBarkTown_Lab/scripts.pory"
    @applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 236 "data/maps/NewBarkTown_Lab/scripts.pory"
    @waitmovement 0
# 237 "data/maps/NewBarkTown_Lab/scripts.pory"
    clearflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 238 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_RIVAL_STATE, 2
# 239 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE, 2
# 240 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto NewBarkTown_Lab_EventScript_MrPokemon
# 241 "data/maps/NewBarkTown_Lab/scripts.pory"

# 242 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_DeclinedStarter::
# 243 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 244 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
# 245 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 246 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 247 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 248 "data/maps/NewBarkTown_Lab/scripts.pory"

# 249 "data/maps/NewBarkTown_Lab/scripts.pory"

# 250 "data/maps/NewBarkTown_Lab/scripts.pory"

# 251 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_NicknameStarter::
# 252 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_0x8004, 0
# 253 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 254 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 255 "data/maps/NewBarkTown_Lab/scripts.pory"

# 256 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemon::
# 257 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
# 258 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 259 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 260 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 261 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 262 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 263 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 264 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 265 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
# 266 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
# 267 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 268 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 269 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 270 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 271 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 272 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 273 "data/maps/NewBarkTown_Lab/scripts.pory"

# 274 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
# 275 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
# 276 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 277 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 278 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 279 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 280 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 281 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 282 "data/maps/NewBarkTown_Lab/scripts.pory"

# 283 "data/maps/NewBarkTown_Lab/scripts.pory"
CopNewBarkTown_Lab_EventScript_ElmState2::
# 284 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 285 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 286 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
# 287 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 288 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 289 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 290 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 291 "data/maps/NewBarkTown_Lab/scripts.pory"

# 292 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine1::
# 293 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 294 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
# 295 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 296 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 297 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 298 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 299 "data/maps/NewBarkTown_Lab/scripts.pory"

# 300 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine2::
# 301 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 302 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 303 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 304 "data/maps/NewBarkTown_Lab/scripts.pory"

# 305 "data/maps/NewBarkTown_Lab/scripts.pory"

# 306 "data/maps/NewBarkTown_Lab/scripts.pory"

# 307 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
# 308 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 309 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 310 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 311 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 312 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
# 313 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 314 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POTION
# 315 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 316 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
# 317 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 318 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 319 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 320 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 321 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 322 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 323 "data/maps/NewBarkTown_Lab/scripts.pory"

# 324 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceEpisode::
# 325 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 326 "data/maps/NewBarkTown_Lab/scripts.pory"
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
# 327 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_hideStarterCase
# 328 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
# 329 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 330 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_LAB_POLICEMAN
# 331 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject LOCALID_COP DIR_WEST
# 332 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
# 333 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceNameRival
# 334 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceYes
# 335 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 336 "data/maps/NewBarkTown_Lab/scripts.pory"

# 337 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNo::
# 338 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
# 339 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
# 340 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
# 341 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 342 "data/maps/NewBarkTown_Lab/scripts.pory"

# 343 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival::
# 344 "data/maps/NewBarkTown_Lab/scripts.pory"
	special NameRival
# 345 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitstate
# 346 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_NAMED_SILVER
# 347 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 348 "data/maps/NewBarkTown_Lab/scripts.pory"

# 349 "data/maps/NewBarkTown_Lab/scripts.pory"

# 350 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival2::
# 351 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 352 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 353 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 354 "data/maps/NewBarkTown_Lab/scripts.pory"

# 355 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes::
# 356 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
# 357 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 358 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes2
# 359 "data/maps/NewBarkTown_Lab/scripts.pory"

# 360 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes3::
# 361 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 362 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 363 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 364 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 365 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 366 "data/maps/NewBarkTown_Lab/scripts.pory"

# 367 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 368 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 369 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 370 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 371 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 372 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 373 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 374 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 375 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 376 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 377 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 378 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 379 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 380 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 381 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 382 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 383 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 384 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 385 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 386 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 387 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 388 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 389 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 390 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 391 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 392 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 393 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 394 "data/maps/NewBarkTown_Lab/scripts.pory"

# 395 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes2::
# 396 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 397 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 398 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 399 "data/maps/NewBarkTown_Lab/scripts.pory"

# 400 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 401 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 402 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 403 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 404 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 405 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 406 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 407 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 408 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 409 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 410 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 411 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 412 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 413 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 414 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 415 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 416 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 417 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 418 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 419 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 420 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 421 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 422 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 423 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 424 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 425 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 426 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 427 "data/maps/NewBarkTown_Lab/scripts.pory"

# 428 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmState5::
# 429 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 430 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 431 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
# 432 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 433 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
# 434 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 435 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 436 "data/maps/NewBarkTown_Lab/scripts.pory"

# 437 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmMasterBall::
# 438 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 439 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 440 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
# 441 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_MASTER_BALL
# 442 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
# 443 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 444 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 445 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 446 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
# 447 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 448 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
# 449 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_GiveStarterMega
# 450 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 451 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
# 452 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
# 453 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_SILVER
# 454 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
# 455 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
# 456 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 457 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 458 "data/maps/NewBarkTown_Lab/scripts.pory"

# 459 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmKimono::
# 460 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 461 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 462 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
# 463 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 464 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 465 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 466 "data/maps/NewBarkTown_Lab/scripts.pory"

# 467 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmLeague::
# 468 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 469 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 470 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
# 471 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 472 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 473 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 474 "data/maps/NewBarkTown_Lab/scripts.pory"

# 475 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmSSTicket::
# 476 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
# 477 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_SS_TICKET
# 478 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
# 479 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 480 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
# 481 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 482 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
# 483 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 484 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 485 "data/maps/NewBarkTown_Lab/scripts.pory"

# 486 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
# 487 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 488 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 489 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 490 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 491 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
# 492 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 493 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POKE_BALL, 10
# 494 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 495 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_FIRST_BALLS
# 496 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
# 497 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ExplainDexnav, MSGBOX_DEFAULT
# 498 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 499 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 500 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 501 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 502 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 503 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 504 "data/maps/NewBarkTown_Lab/scripts.pory"

# 505 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
# 506 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
# 507 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 508 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 509 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 510 "data/maps/NewBarkTown_Lab/scripts.pory"

# 511 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_Cosmog::
# 512 "data/maps/NewBarkTown_Lab/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 513 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen
# 514 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 515 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_SOLGALEO, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 516 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_LUNALA, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 517 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 518 "data/maps/NewBarkTown_Lab/scripts.pory"

# 519 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen::
# 520 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 521 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 522 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 523 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogObservation, MSGBOX_DEFAULT
# 524 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 525 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward
# 526 "data/maps/NewBarkTown_Lab/scripts.pory"

# 527 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen::
# 528 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 529 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 530 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 531 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogEvolvedObservation, MSGBOX_DEFAULT
# 532 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 533 "data/maps/NewBarkTown_Lab/scripts.pory"

# 534 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward::
# 535 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogResearchNotes, MSGBOX_DEFAULT
# 536 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 537 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogCare, MSGBOX_DEFAULT
# 538 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 539 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogOfferEviolite, MSGBOX_DEFAULT
# 540 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 541 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 542 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 543 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_EVIOLITE
# 544 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull
# 545 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_SHOWN_ELM_COSMOG
# 546 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 547 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogExplainEviolite, MSGBOX_DEFAULT
# 548 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 549 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogFarewell, MSGBOX_DEFAULT
# 550 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 551 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 552 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 553 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 554 "data/maps/NewBarkTown_Lab/scripts.pory"

# 555 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull::
# 556 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogBagFull, MSGBOX_DEFAULT
# 557 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 558 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 559 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 560 "data/maps/NewBarkTown_Lab/scripts.pory"

# 561 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_CallMe::
# 562 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
# 563 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 564 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 565 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 566 "data/maps/NewBarkTown_Lab/scripts.pory"

# 567 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkRight:
# 568 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 569 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 570 "data/maps/NewBarkTown_Lab/scripts.pory"

# 571 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkLeft:
# 572 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 573 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 574 "data/maps/NewBarkTown_Lab/scripts.pory"

# 575 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StepBackFromStarter:
# 576 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 577 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 578 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 579 "data/maps/NewBarkTown_Lab/scripts.pory"

# 580 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterLeavesBall:
# 581 "data/maps/NewBarkTown_Lab/scripts.pory"
	exit_pokeball
# 582 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 583 "data/maps/NewBarkTown_Lab/scripts.pory"
	set_visible
# 584 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 585 "data/maps/NewBarkTown_Lab/scripts.pory"

# 586 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterGreetsPlayer:
# 587 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 588 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay_4
# 589 "data/maps/NewBarkTown_Lab/scripts.pory"
	jump_in_place_down
# 590 "data/maps/NewBarkTown_Lab/scripts.pory"
	emote_heart
# 591 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 592 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 593 "data/maps/NewBarkTown_Lab/scripts.pory"

# 594 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_LabMovement_WalkToElm:
# 595 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 596 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 597 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 598 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 599 "data/maps/NewBarkTown_Lab/scripts.pory"

# 600 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnPlayer:
# 601 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 602 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 603 "data/maps/NewBarkTown_Lab/scripts.pory"

# 604 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmail:
# 605 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 606 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 607 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 608 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 609 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 610 "data/maps/NewBarkTown_Lab/scripts.pory"

# 611 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmailSlow:
# 612 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 613 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 614 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 615 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 616 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 617 "data/maps/NewBarkTown_Lab/scripts.pory"

# 618 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_GotoComputerSafe:
# 619 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 620 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 621 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 622 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 623 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 624 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 625 "data/maps/NewBarkTown_Lab/scripts.pory"

# 626 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnFromEmail:
# 627 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 628 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 629 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 630 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 631 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 632 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 633 "data/maps/NewBarkTown_Lab/scripts.pory"

# 634 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Left:
# 635 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_left
# 636 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 637 "data/maps/NewBarkTown_Lab/scripts.pory"

# 638 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Up:
# 639 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 640 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 641 "data/maps/NewBarkTown_Lab/scripts.pory"

# 642 "data/maps/NewBarkTown_Lab/scripts.pory"

# 643 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
# 644 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 645 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 646 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 647 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 648 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 649 "data/maps/NewBarkTown_Lab/scripts.pory"

# 650 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1LeavePlayer:
# 651 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 652 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 653 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 654 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 655 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 656 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 657 "data/maps/NewBarkTown_Lab/scripts.pory"

# 658 "data/maps/NewBarkTown_Lab/scripts.pory"
NeBarkTownLab_Movement_PlayerWalkToCop:
# 659 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 660 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 661 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 662 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 663 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 664 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 665 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 666 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 667 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 668 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_right
# 669 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 670 "data/maps/NewBarkTown_Lab/scripts.pory"

# 671 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Right:
# 672 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_right
# 673 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 674 "data/maps/NewBarkTown_Lab/scripts.pory"

# 675 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Down:
# 676 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_down
# 677 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 678 "data/maps/NewBarkTown_Lab/scripts.pory"

# 679 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CopLeaves:
# 680 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 681 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 682 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 683 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 684 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 685 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 686 "data/maps/NewBarkTown_Lab/scripts.pory"

# 687 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_PlayerStepsToElm:
# 688 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 689 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 690 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 691 "data/maps/NewBarkTown_Lab/scripts.pory"

# 692 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepBack:
# 693 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock_facing_direction
# 694 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 695 "data/maps/NewBarkTown_Lab/scripts.pory"
	unlock_facing_direction
# 696 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 697 "data/maps/NewBarkTown_Lab/scripts.pory"

# 698 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepForward:
# 699 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 700 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 701 "data/maps/NewBarkTown_Lab/scripts.pory"

# 702 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShouldntTouch:
# 703 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Probably shouldn't touch!$"
# 704 "data/maps/NewBarkTown_Lab/scripts.pory"

# 705 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_StarterCaseWrongSide:
# 706 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oops, the case does not open\n"
# 707 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from this side!$"
# 708 "data/maps/NewBarkTown_Lab/scripts.pory"

# 709 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAccepted:
# 710 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks, {PLAYER}!\n"
# 711 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're a great help!$"
# 712 "data/maps/NewBarkTown_Lab/scripts.pory"

# 713 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmRefused:
# 714 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Please, I need your\n"
# 715 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "help!$"
# 716 "data/maps/NewBarkTown_Lab/scripts.pory"

# 717 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmResearchAmbitions:
# 718 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When I announce my findings,\n"
# 719 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm sure we'll delve deeper\p"
# 720 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "into the many mysteries of\n"
# 721 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon.\p"
# 722 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can count on it!$"
# 723 "data/maps/NewBarkTown_Lab/scripts.pory"

# 724 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGotAnEmail:
# 725 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, hey! I got an e-mail!\p"
# 726 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "… … … … … … … …\n"
# 727 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hm… Uh-huh…\p"
# 728 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Okay…$"
# 729 "data/maps/NewBarkTown_Lab/scripts.pory"

# 730 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
# 731 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That was Professor Kukui,\n"
# 732 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a researcher from Alola.\p"
# 733 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's visiting Johto to study\n"
# 734 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Alolan Pokémon spotted here.\p"
# 735 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A Day-Care couple gave him\n"
# 736 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "an unusual Egg.\p"
# 737 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He'd like me to examine it!\p"
# 738 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's working from a house on\n"
# 739 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Route 30, north of Cherrygrove.\p"
# 740 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd go myself, but I can't\n"
# 741 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "leave the lab right now...\p"
# 742 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wait! I have an idea!\p"
# 743 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, could you pick up\n"
# 744 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg for me?$"
# 745 "data/maps/NewBarkTown_Lab/scripts.pory"

# 746 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmChooseAPokemon:
# 747 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I want you to raise one of\n"
# 748 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Pokémon contained in this case.\p"
# 749 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You'll be that Pokémon's\n"
# 750 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "first partner, {PLAYER}!\p"
# 751 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Go on. Pick one!$"
# 752 "data/maps/NewBarkTown_Lab/scripts.pory"

# 753 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWhereGoing:
# 754 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Wait! Where are you\n"
# 755 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going?$"
# 756 "data/maps/NewBarkTown_Lab/scripts.pory"

# 757 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseCyndaquil:
# 758 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: You'll take Cyndaquil,\n"
# 759 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the fire Pokémon?$"
# 760 "data/maps/NewBarkTown_Lab/scripts.pory"

# 761 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseTotodile:
# 762 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Do you want Totodile,\n"
# 763 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the water Pokémon?$"
# 764 "data/maps/NewBarkTown_Lab/scripts.pory"

# 765 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseChikorita:
# 766 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: So, you like Chikorita,\n"
# 767 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the grass Pokémon?$"
# 768 "data/maps/NewBarkTown_Lab/scripts.pory"

# 769 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_DidntChooseStarter:
# 770 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Think it over carefully.\p"
# 771 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Your partner is important.$"
# 772 "data/maps/NewBarkTown_Lab/scripts.pory"

# 773 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChoseStarter:
# 774 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: I think that's a great\n"
# 775 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon too!$"
# 776 "data/maps/NewBarkTown_Lab/scripts.pory"

# 777 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ReceivedStarter:
# 778 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} received {STR_VAR_1}!$"
# 779 "data/maps/NewBarkTown_Lab/scripts.pory"

# 780 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Nickname:
# 781 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Would you like to give your\n"
# 782 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{STR_VAR_1} a nickname?$"
# 783 "data/maps/NewBarkTown_Lab/scripts.pory"

# 784 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections1:
# 785 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui is staying in a house\n"
# 786 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "on Route 30, just north of\l"
# 787 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Cherrygrove City.\p"
# 788 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Head west to Cherrygrove,\n"
# 789 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "then follow the road north.\p"
# 790 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You have my phone number,\n"
# 791 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "so call me if you need help!$"
# 792 "data/maps/NewBarkTown_Lab/scripts.pory"

# 793 "data/maps/NewBarkTown_Lab/scripts.pory"

# 794 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmLetYourMonBattle:
# 795 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears,\n"
# 796 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "let your Pokémon battle it!$"
# 797 "data/maps/NewBarkTown_Lab/scripts.pory"

# 798 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections2:
# 799 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears, let\n"
# 800 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "your Pokémon battle it!\p"
# 801 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If your Pokémon is hurt, you\n"
# 802 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "should heal it with the machine\l"
# 803 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to my right, or at the Pokémon Center.\p"
# 804 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm counting on you!$"
# 805 "data/maps/NewBarkTown_Lab/scripts.pory"

# 806 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_GotElmsNumber:
# 807 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} got Elm's phone\n"
# 808 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "number.$"
# 809 "data/maps/NewBarkTown_Lab/scripts.pory"

# 810 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
# 811 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui says familiar Pokémon\n"
# 812 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "can look quite different in Alola.\p"
# 813 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even their types can change!\n"
# 814 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd love to study how they adapt.$"
# 815 "data/maps/NewBarkTown_Lab/scripts.pory"

# 816 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmPokeBall:
# 817 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It contains Pokémon caught\n"
# 818 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "by Prof. Elm.$"
# 819 "data/maps/NewBarkTown_Lab/scripts.pory"

# 820 "data/maps/NewBarkTown_Lab/scripts.pory"
@THEFT================================================================================
# 821 "data/maps/NewBarkTown_Lab/scripts.pory"

# 822 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft1:
# 823 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, this is terrible…\p"
# 824 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, yes, what was Kukui's\n"
# 825 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "big discovery?$"
# 826 "data/maps/NewBarkTown_Lab/scripts.pory"

# 827 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft2:
# 828 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} handed the Mystery Egg\n"
# 829 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to Prof. Elm.$"
# 830 "data/maps/NewBarkTown_Lab/scripts.pory"

# 831 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft3:
# 832 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: This?$"
# 833 "data/maps/NewBarkTown_Lab/scripts.pory"

# 834 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft4:
# 835 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Is it a Pokémon Egg?\p"
# 836 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If it is, it is a great\n"
# 837 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "discovery!\p"
# 838 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: What?!?\p"
# 839 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Oak gave you a Pokédex?\p"
# 840 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, is that true?\n"
# 841 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Th-that's incredible!\p"
# 842 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He is superb at seeing the\n"
# 843 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "potential of people as trainers.\p"
# 844 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wow, {PLAYER}. You may have what\n"
# 845 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it takes to become the Champion.\p"
# 846 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You seem to be getting on\n"
# 847 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "great with Pokémon too.\p"
# 848 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should take the Pokémon\n"
# 849 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gym challenge.\p"
# 850 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The closest Gym would be the\n"
# 851 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "one in Violet City.\p"
# 852 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…{PLAYER}. The road to the\n"
# 853 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "championship will be a long one.\p"
# 854 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Before you leave, make sure\n"
# 855 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that you talk to your mom.$"
# 856 "data/maps/NewBarkTown_Lab/scripts.pory"

# 857 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmStudyingEgg:
# 858 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Don't give up!\n"
# 859 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll call if I learn anything\l"
# 860 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about that Egg!$"
# 861 "data/maps/NewBarkTown_Lab/scripts.pory"

# 862 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideHasEgg:
# 863 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}? Didn't you meet\n"
# 864 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my assistant?\p"
# 865 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He should have met you with\n"
# 866 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg at Violet City's\p"
# 867 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon Center.\p"
# 868 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You must have just missed him.\n"
# 869 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Try to catch him there.$"
# 870 "data/maps/NewBarkTown_Lab/scripts.pory"

# 871 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWaitingEggHatch:
# 872 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hey, has that Egg changed\n"
# 873 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "any?$"
# 874 "data/maps/NewBarkTown_Lab/scripts.pory"

# 875 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmThoughtEggHatched:
# 876 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}? I thought the Egg\n"
# 877 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "hatched.\p"
# 878 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Where is the Pokémon?$"
# 879 "data/maps/NewBarkTown_Lab/scripts.pory"

# 880 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogVisitIntro:
# 881 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! You came back!\p"
# 882 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "And you brought the Pokémon\n"
# 883 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from Kukui's Egg?\p"
# 884 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me put these notes aside.\n"
# 885 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd like a closer look!$"
# 886 "data/maps/NewBarkTown_Lab/scripts.pory"

# 887 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogObservation:
# 888 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "So this is Cosmog...\p"
# 889 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It looks as though a piece\n"
# 890 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of the night sky drifted inside!\p"
# 891 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To think it was tucked away\n"
# 892 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in that little Egg all along.\p"
# 893 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hmm... Where did I put\n"
# 894 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my other notebook?$"
# 895 "data/maps/NewBarkTown_Lab/scripts.pory"

# 896 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogEvolvedObservation:
# 897 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's already evolved?\n"
# 898 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have some catching up to do!\p"
# 899 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What was it like when\n"
# 900 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it first came out of the Egg?\p"
# 901 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even a small detail could help.\n"
# 902 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me find a fresh page!$"
# 903 "data/maps/NewBarkTown_Lab/scripts.pory"

# 904 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogResearchNotes:
# 905 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui sent me one Egg,\n"
# 906 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and now I have a hundred questions.\p"
# 907 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll send him my observations.\n"
# 908 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He may know where to start.\p"
# 909 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I suspect his reply will bring\n"
# 910 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a few more questions too!$"
# 911 "data/maps/NewBarkTown_Lab/scripts.pory"

# 912 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogCare:
# 913 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, listen to me rambling.\n"
# 914 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're here for a visit!\p"
# 915 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thank you for taking care\n"
# 916 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of this Pokémon, {PLAYER}.\p"
# 917 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You get to see things together\n"
# 918 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that I'd never see in this lab.$"
# 919 "data/maps/NewBarkTown_Lab/scripts.pory"

# 920 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogOfferEviolite:
# 921 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Actually, I have something\n"
# 922 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for your travels.\p"
# 923 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I've been keeping it here\n"
# 924 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for a young Trainer to use.$"
# 925 "data/maps/NewBarkTown_Lab/scripts.pory"

# 926 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogBagFull:
# 927 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh! There's no room\n"
# 928 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in your Bag right now.\p"
# 929 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Make some space and come back.\n"
# 930 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll keep it safe for you!$"
# 931 "data/maps/NewBarkTown_Lab/scripts.pory"

# 932 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogExplainEviolite:
# 933 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That's an Eviolite.\p"
# 934 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Have a Pokémon that can still\n"
# 935 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "evolve hold it. It will boost\l"
# 936 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "its Defense and Sp. Def.\p"
# 937 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A little extra protection\n"
# 938 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "while it's growing!\p"
# 939 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can give it to whichever\n"
# 940 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "partner needs it most.$"
# 941 "data/maps/NewBarkTown_Lab/scripts.pory"

# 942 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogFarewell:
# 943 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If you notice anything unusual,\n"
# 944 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "you have my number.\p"
# 945 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now, where was that notebook...?\n"
# 946 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah! Under the first one.\p"
# 947 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take care, {PLAYER}.\n"
# 948 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Both of you!$"
# 949 "data/maps/NewBarkTown_Lab/scripts.pory"

# 950 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmCallYou:
# 951 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, I'll call you if\n"
# 952 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "anything comes up.$"
# 953 "data/maps/NewBarkTown_Lab/scripts.pory"

# 954 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAfterTheft:
# 955 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 956 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 957 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 958 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 959 "data/maps/NewBarkTown_Lab/scripts.pory"

# 960 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall1:
# 961 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hi, {PLAYER}!\p"
# 962 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks to you, my research is\n"
# 963 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going great!\p"
# 964 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take this as a token of my\n"
# 965 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "appreciation.$"
# 966 "data/maps/NewBarkTown_Lab/scripts.pory"

# 967 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall2:
# 968 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Master Ball is the best!\p"
# 969 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the ultimate Ball! It'll\n"
# 970 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "catch any Pokémon without fail.\p"
# 971 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's given only to recognized\n"
# 972 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon researchers.\p"
# 973 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I think you can make much better\n"
# 974 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "use of it than I can, {PLAYER}!$"
# 975 "data/maps/NewBarkTown_Lab/scripts.pory"

# 976 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoGirls:
# 977 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "By the way...\n"
# 978 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A group of beautiful Kimono\l"
# 979 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls were looking for you.\p"
# 980 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They told me they are\n"
# 981 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "waiting for you at the\l"
# 982 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ecruteak Dance Theater.\p"
# 983 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I know you've gone through many\n"
# 984 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "things since that Egg got you\l"
# 985 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "involved in all this...\p"
# 986 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I hope you'll carry through it.$"
# 987 "data/maps/NewBarkTown_Lab/scripts.pory"

# 988 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoWaiting:
# 989 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: The Kimono\n"
# 990 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls are waiting for you at\l"
# 991 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Ecruteak Dance Theater.$"
# 992 "data/maps/NewBarkTown_Lab/scripts.pory"

# 993 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_League:
# 994 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: Hahaha...\n"
# 995 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Good job!\p"
# 996 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That rare Egg has brought you\n"
# 997 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a lot of trouble, huh?\p"
# 998 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Kimono Girls said something\n"
# 999 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about me?\p"
# 1000 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have nothing to do with it.\p"
# 1001 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You made your decision and went\n"
# 1002 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "through with it.\p"
# 1003 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Having done so much, you should\n"
# 1004 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "be able to face the League now!\p"
# 1005 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should head for Indigo\n"
# 1006 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Plateau!\p"
# 1007 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Do you know how to get there?\n"
# 1008 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Follow Route 27 to Route 26.\p"
# 1009 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Once there, go straight north!$"
# 1010 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1011 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1012 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket1:
# 1013 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\p"
# 1014 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I called because I have\n"
# 1015 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "something for you.\p"
# 1016 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "See? It's an S.S.Ticket.\p"
# 1017 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can catch Pokémon in\n"
# 1018 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Sevii.$"
# 1019 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1020 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket2:
# 1021 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The ship departs from Olivine\n"
# 1022 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "City.\p"
# 1023 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But you knew that already,\n"
# 1024 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}.\p"
# 1025 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "After all, you've traveled all\n"
# 1026 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "over with your Pokémon.$"
# 1027 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1028 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_LabMonEgg:
# 1029 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the Pokémon Egg being\n"
# 1030 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "studied by Prof. Elm.$"
# 1031 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1032 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGivePotion:
# 1033 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, I want you to have\n"
# 1034 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "this for your errand.$"
# 1035 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1036 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAlwaysBusy:
# 1037 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There are only three of us, so\n"
# 1038 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "we're always busy.$"
# 1039 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1040 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideSave:
# 1041 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Don't forget to save your game\n"
# 1042 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "regularly!\p"
# 1043 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Press the Start button, then\n"
# 1044 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Save the game!$"
# 1045 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1046 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideTheftTestimony:
# 1047 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There was a loud noise\n"
# 1048 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "outside…\p"
# 1049 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When we went to look,\n"
# 1050 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "someone stole a Pokémon.\p"
# 1051 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's unbelievable that anyone\n"
# 1052 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "would do that!\p"
# 1053 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 1054 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 1055 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 1056 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 1057 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1058 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGiveBalls:
# 1059 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 1060 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use these on your Pokédex\n"
# 1061 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "quest!$"
# 1062 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1063 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ExplainDexnav:
# 1064 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "We've also sent a Dexnav\n"
# 1065 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "application to your Pokégear!\p"
# 1066 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use it to catch lots of Pokémon!$"
# 1067 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1068 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideExplainBalls:
# 1069 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To add to your Pokédex, you\n"
# 1070 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "have to catch Pokémon.\p"
# 1071 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Throw Poké Balls at wild\n"
# 1072 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon to get them.$"
# 1073 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1074 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer1:
# 1075 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I heard a Pokémon was stolen\n"
# 1076 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here…\p"
# 1077 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I was just getting some\n"
# 1078 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "information from Prof. Elm.\p"
# 1079 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Apparently, it was a young\n"
# 1080 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "male with long, red hair…\p"
# 1081 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What?\p"
# 1082 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You battled a trainer like\n"
# 1083 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that?\p"
# 1084 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Did you happen to get his\n"
# 1085 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "name?$"
# 1086 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1087 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer2:
# 1088 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So Silver was his name.\p"
# 1089 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1090 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1091 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1092 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer3:
# 1093 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So {RIVAL} was his name.\p"
# 1094 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1095 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1096 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1097 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_OfficerNo:
# 1098 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Surely you got his name?!$"
# 1099 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1100 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Elm_CallMe:
# 1101 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah, {PLAYER}!\p"
# 1102 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "How's your Pokédex coming along?\n"
# 1103 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm busy now, but call me sometime\l"
# 1104 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and I can check your progress!$"

NewBarkTown_Lab_GiveStarterMega::
# 1108 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_0
# 1112 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_BONDSTONE, 1
# 1113 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_1
	return


NewBarkTown_Lab_EventScript_ElmPostgameHint::
# 1120 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0
# 1129 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1
# 1131 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1132 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1133 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1134 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1135 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1136 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1137 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 1138 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1139 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2
# 1145 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
# 1146 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_VICTORYROAD_RIVAL
# 1147 "data/maps/NewBarkTown_Lab/scripts.pory"
	checkplayergender
# 1148 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_Lab_EventScript_ElmPostgameHint_2
# 1157 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4
NewBarkTown_Lab_EventScript_ElmPostgameHint_1:
# 1165 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5
# 1167 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MTSILVER_GUARD
# 1168 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALLOW_SOUTH_JOHTO_PASS
# 1169 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 1170 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 11
# 1171 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ElmPostgameHint_2:
# 1149 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3
	goto NewBarkTown_Lab_EventScript_ElmPostgameHint_1


ElmIntro::
# 1176 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox ElmIntro_Text_0, MSGBOX_YESNO
	return


NewBarkTown_Lab_EventScript_ArtifactOfChaos::
# 1202 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 1203 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_ALL_INNATES_UNLOCKED, NewBarkTown_Lab_EventScript_ArtifactOfChaos_2
# 1227 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4
# 1232 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5
# 1238 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6, MSGBOX_YESNO
# 1244 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_8
# 1257 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8
NewBarkTown_Lab_EventScript_ArtifactOfChaos_1:
# 1261 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 1262 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ArtifactOfChaos_2:
# 1204 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0
# 1208 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1, MSGBOX_YESNO
# 1209 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_5
# 1223 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_5:
# 1210 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_OFF
# 1211 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1212 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_ALL_INNATES_UNLOCKED
# 1213 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_NEWBARKTOWN_LABSTATE, 11
	goto_if_lt NewBarkTown_Lab_EventScript_ArtifactOfChaos_12
# 1216 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
NewBarkTown_Lab_EventScript_ArtifactOfChaos_11:
# 1218 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_8:
# 1245 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_SWITCH
# 1246 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1247 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALL_INNATES_UNLOCKED
# 1248 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_REPLAY_NO_INNATES
# 1249 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_12:
# 1214 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_POSTGAME_FEATURES
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_11


NewBarkTown_Lab_GiveStarterMega_Text_0:
# 1108 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, and you got a Mega Ring from \n"
	.string "Prof. Oak?\l"
	.string "Then I think you are ready to handle\l"
	.string "this.$"

NewBarkTown_Lab_GiveStarterMega_Text_1:
# 1113 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's a special Mega Stone, specifically\n"
	.string "for your starter Pokémon. I expect \l"
	.string "great things from you, {PLAYER}!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0:
# 1120 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\n"
	.string "I called because I heard that the \l"
	.string "Battle Tower is open! \p"
	.string "I hear strong trainers\n"
	.string "are gathering in there!\p"
	.string "You can get there from Route 40\n"
	.string "near Olivine City.$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1:
# 1129 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But first, let me upgrade your Pokédex\n"
	.string "with a new feature!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2:
# 1139 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can view abilities of the\n"
	.string "opposing Pokémon with the L-button\l"
	.string "in battle! \p"
	.string "That will surely be handy as the\n"
	.string "battles get tougher!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3:
# 1149 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Crystal went to train\n"
	.string "in Mt. Silver. \p"
	.string "She looked really tired\n"
	.string "the last time I saw her though... \p"
	.string "Could you check on her at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4:
# 1157 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Gold went to train\n"
	.string "in Mt. Silver. \p"
	.string "He looked really tired\n"
	.string "the last time I saw him though...\p"
	.string "Could you check on him at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5:
# 1165 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I asked from the League to let you\n"
	.string "pass since you've the new Champion.$"

ElmIntro_Text_0:
# 1176 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\p"
	.string "I needed to ask you a favor.\p"
	.string "I'm conducting new Pokémon\n"
	.string "research right now. \p"
	.string "I was wondering if you could help\n"
	.string "me with it, {PLAYER}.\p"
	.string "You see…\p"
	.string "I'm writing a paper that I\n"
	.string "want to present at a conference.\p"
	.string "But there are some things I\n"
	.string "don't quite understand yet.\p"
	.string "So!\p"
	.string "I'd like you to raise a\n"
	.string "Pokémon that I recently caught.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0:
# 1204 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact of Chaos is humming.\p"
	.string "All innate abilities are currently\n"
	.string "active.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1:
# 1208 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Deactivate the Artifact?$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2:
# 1218 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The glow from the Artifact fades.\p"
	.string "Innate abilities will now unlock at\n"
	.string "their intended levels again.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3:
# 1223 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact continues humming.\n"
	.string "Hope Elm hasn't noticed yet!$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4:
# 1227 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Amidst the books is Elm's very own\n"
	.string "Artifact of Chaos.\p"
	.string "There's a small label on the side:\n"
	.string "DO NOT TOUCH.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5:
# 1232 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Important! Activating this Artifact\n"
	.string "unlocks all innate abilities,\l"
	.string "regardless of a Pokémon's level.\p"
	.string "It also lets you inspect enemy\n"
	.string "innates in battle by pressing L.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6:
# 1238 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "This is not the intended way to play\n"
	.string "the game and will not be balanced\l"
	.string "at all.\p"
	.string "If you understand and still wish to\n"
	.string "activate it, choose Yes.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7:
# 1249 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} tapped the Artifact.\p"
	.string "Game balance quietly\n"
	.string "leaves the building.\p"
	.string "All innates are now active. Press L\n"
	.string "in battle to inspect enemy innates.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8:
# 1257 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} left the Artifact alone.\n"
	.string "Chaos shall not win today.$"
