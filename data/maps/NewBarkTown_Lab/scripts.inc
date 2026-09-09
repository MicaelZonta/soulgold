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
	goto_if_set FLAG_HIDE_NEWBARKTOWN_LAB_AIDE, NewBarkTown_Lab_EventScript_ElmAideIsWaiting
# 71 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
# 72 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
# 73 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
# 74 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmPostgameHint
# 75 "data/maps/NewBarkTown_Lab/scripts.pory"

# 76 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_CallMe
# 77 "data/maps/NewBarkTown_Lab/scripts.pory"
	call_if_unset FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_Check_Cosmog
# 78 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
# 79 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5
# 80 "data/maps/NewBarkTown_Lab/scripts.pory"

# 81 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
# 82 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
# 83 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
# 84 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
# 85 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 86 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 87 "data/maps/NewBarkTown_Lab/scripts.pory"

# 88 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAideIsWaiting::
# 89 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAideIsWaiting, MSGBOX_DEFAULT
# 90 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 91 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 92 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 93 "data/maps/NewBarkTown_Lab/scripts.pory"

# 94 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideIsWaiting:
# 95 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 96 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What are you doing here?\p"
# 97 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "My aide is still waiting for you\n"
# 98 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "In Violet City!$"
# 99 "data/maps/NewBarkTown_Lab/scripts.pory"

# 100 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmIntro::
# 101 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 102 "data/maps/NewBarkTown_Lab/scripts.pory"
	call ElmIntro
# 103 "data/maps/NewBarkTown_Lab/scripts.pory"
	@msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
# 104 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 105 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 106 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 107 "data/maps/NewBarkTown_Lab/scripts.pory"

# 108 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmRefused::
# 109 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 110 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
# 111 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 112 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 113 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 114 "data/maps/NewBarkTown_Lab/scripts.pory"

# 115 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAccepted::
# 116 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 117 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
# 118 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
# 119 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 120 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_LOGIN
# 121 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 122 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 123 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
# 124 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 125 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
# 126 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
# 127 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement LOCALID_ELM
# 128 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 129 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
# 130 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 131 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 132 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
# 133 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 134 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 135 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 136 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 137 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 138 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
# 139 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 140 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 141 "data/maps/NewBarkTown_Lab/scripts.pory"

# 142 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmChoosePokemon::
# 143 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 144 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Right
# 145 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 146 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 147 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
# 148 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 149 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 150 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Down
# 151 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 152 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
# 153 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 154 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 155 "data/maps/NewBarkTown_Lab/scripts.pory"

# 156 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
# 157 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 158 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 159 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
# 160 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 161 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 162 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
# 163 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 164 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 165 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 166 "data/maps/NewBarkTown_Lab/scripts.pory"

# 167 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ShouldntTouch::
# 168 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 169 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 170 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 171 "data/maps/NewBarkTown_Lab/scripts.pory"

# 172 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_hideStarterCase::
# 173 "data/maps/NewBarkTown_Lab/scripts.pory"
    setflag FLAG_HIDE_STARTER_CASE
# 174 "data/maps/NewBarkTown_Lab/scripts.pory"
    return
# 175 "data/maps/NewBarkTown_Lab/scripts.pory"

# 176 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase::
# 177 "data/maps/NewBarkTown_Lab/scripts.pory"
    lock
# 178 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_SOUTH, NewBarkTown_Lab_EventScript_StarterCaseWrongSide
# 179 "data/maps/NewBarkTown_Lab/scripts.pory"
	callnative MigrateNationalPokedex
# 180 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
# 181 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_StarterCase_Choice
# 182 "data/maps/NewBarkTown_Lab/scripts.pory"
    msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 183 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 184 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 185 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 186 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCaseWrongSide::
# 187 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_StarterCaseWrongSide, MSGBOX_DEFAULT
# 188 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 189 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 190 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 191 "data/maps/NewBarkTown_Lab/scripts.pory"

# 192 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase_Choice::
# 193 "data/maps/NewBarkTown_Lab/scripts.pory"
   callnative StartNewPokeballCaseUI
# 194 "data/maps/NewBarkTown_Lab/scripts.pory"
   waitstate
# 195 "data/maps/NewBarkTown_Lab/scripts.pory"
   goto NewBarkTown_Lab_EventScript_ChoseStarter
# 196 "data/maps/NewBarkTown_Lab/scripts.pory"

# 197 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter::
# 198 "data/maps/NewBarkTown_Lab/scripts.pory"
	showmonpic VAR_PLAYER_STARTER_SPECIES, 10, 3
# 199 "data/maps/NewBarkTown_Lab/scripts.pory"
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
# 200 "data/maps/NewBarkTown_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_PLAYER_STARTER_SPECIES
# 201 "data/maps/NewBarkTown_Lab/scripts.pory"
	message NewBarkTown_Lab_Text_ReceivedStarter
# 202 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE 1
# 203 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitfanfare
# 204 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 205 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 206 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_StepBackFromStarter
# 207 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 208 "data/maps/NewBarkTown_Lab/scripts.pory"
	updatefollowingmon
# 209 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxy OBJ_EVENT_ID_FOLLOWER, 9, 5
# 210 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterLeavesBall
# 211 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_BALL_OPEN
# 212 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 213 "data/maps/NewBarkTown_Lab/scripts.pory"
	playmoncry VAR_PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
# 214 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_LEDGE
# 215 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterGreetsPlayer
# 216 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 217 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmoncry
# 218 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 45
# 219 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 220 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
# 221 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 222 "data/maps/NewBarkTown_Lab/scripts.pory"
    closemessage
# 223 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 224 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 225 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 226 "data/maps/NewBarkTown_Lab/scripts.pory"

# 227 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter2::
# 228 "data/maps/NewBarkTown_Lab/scripts.pory"
    moveobjecttocoords OBJ_EVENT_ID_PLAYER, 6, 4, DIR_NORTH
# 229 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 230 "data/maps/NewBarkTown_Lab/scripts.pory"
    @applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 231 "data/maps/NewBarkTown_Lab/scripts.pory"
    @waitmovement 0
# 232 "data/maps/NewBarkTown_Lab/scripts.pory"
    clearflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 233 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_RIVAL_STATE, 2
# 234 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE, 2
# 235 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto NewBarkTown_Lab_EventScript_MrPokemon
# 236 "data/maps/NewBarkTown_Lab/scripts.pory"

# 237 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_DeclinedStarter::
# 238 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 239 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
# 240 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 241 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 242 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 243 "data/maps/NewBarkTown_Lab/scripts.pory"

# 244 "data/maps/NewBarkTown_Lab/scripts.pory"

# 245 "data/maps/NewBarkTown_Lab/scripts.pory"

# 246 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_NicknameStarter::
# 247 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_0x8004, 0
# 248 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 249 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 250 "data/maps/NewBarkTown_Lab/scripts.pory"

# 251 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemon::
# 252 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
# 253 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 254 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 255 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 256 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 257 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 258 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 259 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 260 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
# 261 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
# 262 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 263 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 264 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 265 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 266 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 267 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 268 "data/maps/NewBarkTown_Lab/scripts.pory"

# 269 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
# 270 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
# 271 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 272 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 273 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 274 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 275 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 276 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 277 "data/maps/NewBarkTown_Lab/scripts.pory"

# 278 "data/maps/NewBarkTown_Lab/scripts.pory"
CopNewBarkTown_Lab_EventScript_ElmState2::
# 279 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 280 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 281 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
# 282 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 283 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 284 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 285 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 286 "data/maps/NewBarkTown_Lab/scripts.pory"

# 287 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine1::
# 288 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 289 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
# 290 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 291 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 292 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 293 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 294 "data/maps/NewBarkTown_Lab/scripts.pory"

# 295 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine2::
# 296 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 297 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 298 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 299 "data/maps/NewBarkTown_Lab/scripts.pory"

# 300 "data/maps/NewBarkTown_Lab/scripts.pory"

# 301 "data/maps/NewBarkTown_Lab/scripts.pory"

# 302 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
# 303 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 304 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 305 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 306 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 307 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
# 308 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 309 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POTION
# 310 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 311 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
# 312 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 313 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 314 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 315 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 316 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 317 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 318 "data/maps/NewBarkTown_Lab/scripts.pory"

# 319 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceEpisode::
# 320 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 321 "data/maps/NewBarkTown_Lab/scripts.pory"
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
# 322 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_hideStarterCase
# 323 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
# 324 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 325 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_LAB_POLICEMAN
# 326 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject LOCALID_COP DIR_WEST
# 327 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
# 328 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceNameRival
# 329 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceYes
# 330 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 331 "data/maps/NewBarkTown_Lab/scripts.pory"

# 332 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNo::
# 333 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
# 334 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
# 335 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
# 336 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 337 "data/maps/NewBarkTown_Lab/scripts.pory"

# 338 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival::
# 339 "data/maps/NewBarkTown_Lab/scripts.pory"
	special NameRival
# 340 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitstate
# 341 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_NAMED_SILVER
# 342 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 343 "data/maps/NewBarkTown_Lab/scripts.pory"

# 344 "data/maps/NewBarkTown_Lab/scripts.pory"

# 345 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival2::
# 346 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 347 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 348 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 349 "data/maps/NewBarkTown_Lab/scripts.pory"

# 350 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes::
# 351 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
# 352 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 353 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes2
# 354 "data/maps/NewBarkTown_Lab/scripts.pory"

# 355 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes3::
# 356 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 357 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 358 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 359 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 360 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 361 "data/maps/NewBarkTown_Lab/scripts.pory"

# 362 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 363 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 364 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 365 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 366 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 367 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 368 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 369 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 370 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 371 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 372 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 373 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 374 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 375 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 376 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 377 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 378 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 379 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 380 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 381 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 382 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 383 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 384 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 385 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 386 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 387 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 388 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 389 "data/maps/NewBarkTown_Lab/scripts.pory"

# 390 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes2::
# 391 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 392 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 393 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 394 "data/maps/NewBarkTown_Lab/scripts.pory"

# 395 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 396 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 397 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 398 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 399 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 400 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 401 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 402 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 403 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 404 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 405 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 406 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 407 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 408 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 409 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 410 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 411 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 412 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 413 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 414 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 415 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 416 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 417 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 418 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 419 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 420 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 421 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 422 "data/maps/NewBarkTown_Lab/scripts.pory"

# 423 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmState5::
# 424 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 425 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 426 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
# 427 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 428 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
# 429 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 430 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 431 "data/maps/NewBarkTown_Lab/scripts.pory"

# 432 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmMasterBall::
# 433 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 434 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 435 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
# 436 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_MASTER_BALL
# 437 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
# 438 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 439 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 440 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 441 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
# 442 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 443 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
# 444 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_GiveStarterMega
# 445 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 446 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
# 447 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
# 448 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_SILVER
# 449 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
# 450 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
# 451 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 452 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 453 "data/maps/NewBarkTown_Lab/scripts.pory"

# 454 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmKimono::
# 455 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 456 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 457 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
# 458 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 459 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 460 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 461 "data/maps/NewBarkTown_Lab/scripts.pory"

# 462 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmLeague::
# 463 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 464 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 465 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
# 466 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 467 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 468 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 469 "data/maps/NewBarkTown_Lab/scripts.pory"

# 470 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmSSTicket::
# 471 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
# 472 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_SS_TICKET
# 473 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
# 474 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 475 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
# 476 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 477 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
# 478 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 479 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 480 "data/maps/NewBarkTown_Lab/scripts.pory"

# 481 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
# 482 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 483 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 484 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 485 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 486 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
# 487 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 488 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POKE_BALL, 10
# 489 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 490 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_FIRST_BALLS
# 491 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
# 492 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ExplainDexnav, MSGBOX_DEFAULT
# 493 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 494 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 495 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 496 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 497 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 498 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 499 "data/maps/NewBarkTown_Lab/scripts.pory"

# 500 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
# 501 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
# 502 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 503 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 504 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 505 "data/maps/NewBarkTown_Lab/scripts.pory"

# 506 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_Cosmog::
# 507 "data/maps/NewBarkTown_Lab/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 508 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen
# 509 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 510 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_SOLGALEO, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 511 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_LUNALA, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 512 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 513 "data/maps/NewBarkTown_Lab/scripts.pory"

# 514 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen::
# 515 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 516 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 517 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 518 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogObservation, MSGBOX_DEFAULT
# 519 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 520 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward
# 521 "data/maps/NewBarkTown_Lab/scripts.pory"

# 522 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen::
# 523 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 524 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 525 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 526 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogEvolvedObservation, MSGBOX_DEFAULT
# 527 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 528 "data/maps/NewBarkTown_Lab/scripts.pory"

# 529 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward::
# 530 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogResearchNotes, MSGBOX_DEFAULT
# 531 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 532 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogCare, MSGBOX_DEFAULT
# 533 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 534 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogOfferEviolite, MSGBOX_DEFAULT
# 535 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 536 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 537 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 538 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_EVIOLITE
# 539 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull
# 540 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_SHOWN_ELM_COSMOG
# 541 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 542 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogExplainEviolite, MSGBOX_DEFAULT
# 543 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 544 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogFarewell, MSGBOX_DEFAULT
# 545 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 546 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 547 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 548 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 549 "data/maps/NewBarkTown_Lab/scripts.pory"

# 550 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull::
# 551 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogBagFull, MSGBOX_DEFAULT
# 552 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 553 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 554 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 555 "data/maps/NewBarkTown_Lab/scripts.pory"

# 556 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_CallMe::
# 557 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
# 558 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 559 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 560 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 561 "data/maps/NewBarkTown_Lab/scripts.pory"

# 562 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkRight:
# 563 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 564 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 565 "data/maps/NewBarkTown_Lab/scripts.pory"

# 566 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkLeft:
# 567 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 568 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 569 "data/maps/NewBarkTown_Lab/scripts.pory"

# 570 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StepBackFromStarter:
# 571 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 572 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 573 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 574 "data/maps/NewBarkTown_Lab/scripts.pory"

# 575 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterLeavesBall:
# 576 "data/maps/NewBarkTown_Lab/scripts.pory"
	exit_pokeball
# 577 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 578 "data/maps/NewBarkTown_Lab/scripts.pory"
	set_visible
# 579 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 580 "data/maps/NewBarkTown_Lab/scripts.pory"

# 581 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterGreetsPlayer:
# 582 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 583 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay_4
# 584 "data/maps/NewBarkTown_Lab/scripts.pory"
	jump_in_place_down
# 585 "data/maps/NewBarkTown_Lab/scripts.pory"
	emote_heart
# 586 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 587 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 588 "data/maps/NewBarkTown_Lab/scripts.pory"

# 589 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_LabMovement_WalkToElm:
# 590 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 591 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 592 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 593 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 594 "data/maps/NewBarkTown_Lab/scripts.pory"

# 595 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnPlayer:
# 596 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 597 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 598 "data/maps/NewBarkTown_Lab/scripts.pory"

# 599 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmail:
# 600 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 601 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 602 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 603 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 604 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 605 "data/maps/NewBarkTown_Lab/scripts.pory"

# 606 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmailSlow:
# 607 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 608 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 609 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 610 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 611 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 612 "data/maps/NewBarkTown_Lab/scripts.pory"

# 613 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_GotoComputerSafe:
# 614 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 615 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 616 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 617 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 618 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 619 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 620 "data/maps/NewBarkTown_Lab/scripts.pory"

# 621 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnFromEmail:
# 622 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 623 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 624 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 625 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 626 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 627 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 628 "data/maps/NewBarkTown_Lab/scripts.pory"

# 629 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Left:
# 630 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_left
# 631 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 632 "data/maps/NewBarkTown_Lab/scripts.pory"

# 633 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Up:
# 634 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 635 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 636 "data/maps/NewBarkTown_Lab/scripts.pory"

# 637 "data/maps/NewBarkTown_Lab/scripts.pory"

# 638 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
# 639 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 640 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 641 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 642 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 643 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 644 "data/maps/NewBarkTown_Lab/scripts.pory"

# 645 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1LeavePlayer:
# 646 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 647 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 648 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 649 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 650 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 651 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 652 "data/maps/NewBarkTown_Lab/scripts.pory"

# 653 "data/maps/NewBarkTown_Lab/scripts.pory"
NeBarkTownLab_Movement_PlayerWalkToCop:
# 654 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 655 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 656 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 657 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 658 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 659 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 660 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 661 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 662 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 663 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_right
# 664 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 665 "data/maps/NewBarkTown_Lab/scripts.pory"

# 666 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Right:
# 667 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_right
# 668 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 669 "data/maps/NewBarkTown_Lab/scripts.pory"

# 670 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Down:
# 671 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_down
# 672 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 673 "data/maps/NewBarkTown_Lab/scripts.pory"

# 674 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CopLeaves:
# 675 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 676 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 677 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 678 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 679 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 680 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 681 "data/maps/NewBarkTown_Lab/scripts.pory"

# 682 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_PlayerStepsToElm:
# 683 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 684 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 685 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 686 "data/maps/NewBarkTown_Lab/scripts.pory"

# 687 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepBack:
# 688 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock_facing_direction
# 689 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 690 "data/maps/NewBarkTown_Lab/scripts.pory"
	unlock_facing_direction
# 691 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 692 "data/maps/NewBarkTown_Lab/scripts.pory"

# 693 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepForward:
# 694 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 695 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 696 "data/maps/NewBarkTown_Lab/scripts.pory"

# 697 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShouldntTouch:
# 698 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Probably shouldn't touch!$"
# 699 "data/maps/NewBarkTown_Lab/scripts.pory"

# 700 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_StarterCaseWrongSide:
# 701 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oops, the case does not open\n"
# 702 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from this side!$"
# 703 "data/maps/NewBarkTown_Lab/scripts.pory"

# 704 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAccepted:
# 705 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks, {PLAYER}!\n"
# 706 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're a great help!$"
# 707 "data/maps/NewBarkTown_Lab/scripts.pory"

# 708 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmRefused:
# 709 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Please, I need your\n"
# 710 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "help!$"
# 711 "data/maps/NewBarkTown_Lab/scripts.pory"

# 712 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmResearchAmbitions:
# 713 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When I announce my findings,\n"
# 714 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm sure we'll delve deeper\p"
# 715 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "into the many mysteries of\n"
# 716 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon.\p"
# 717 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can count on it!$"
# 718 "data/maps/NewBarkTown_Lab/scripts.pory"

# 719 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGotAnEmail:
# 720 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, hey! I got an e-mail!\p"
# 721 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "… … … … … … … …\n"
# 722 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hm… Uh-huh…\p"
# 723 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Okay…$"
# 724 "data/maps/NewBarkTown_Lab/scripts.pory"

# 725 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
# 726 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That was Professor Kukui,\n"
# 727 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a researcher from Alola.\p"
# 728 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's visiting Johto to study\n"
# 729 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Alolan Pokémon spotted here.\p"
# 730 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A Day-Care couple gave him\n"
# 731 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "an unusual Egg.\p"
# 732 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He'd like me to examine it!\p"
# 733 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's working from a house on\n"
# 734 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Route 30, north of Cherrygrove.\p"
# 735 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd go myself, but I can't\n"
# 736 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "leave the lab right now...\p"
# 737 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wait! I have an idea!\p"
# 738 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, could you pick up\n"
# 739 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg for me?$"
# 740 "data/maps/NewBarkTown_Lab/scripts.pory"

# 741 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmChooseAPokemon:
# 742 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I want you to raise one of\n"
# 743 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Pokémon contained in this case.\p"
# 744 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You'll be that Pokémon's\n"
# 745 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "first partner, {PLAYER}!\p"
# 746 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Go on. Pick one!$"
# 747 "data/maps/NewBarkTown_Lab/scripts.pory"

# 748 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWhereGoing:
# 749 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Wait! Where are you\n"
# 750 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going?$"
# 751 "data/maps/NewBarkTown_Lab/scripts.pory"

# 752 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseCyndaquil:
# 753 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: You'll take Cyndaquil,\n"
# 754 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the fire Pokémon?$"
# 755 "data/maps/NewBarkTown_Lab/scripts.pory"

# 756 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseTotodile:
# 757 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Do you want Totodile,\n"
# 758 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the water Pokémon?$"
# 759 "data/maps/NewBarkTown_Lab/scripts.pory"

# 760 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseChikorita:
# 761 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: So, you like Chikorita,\n"
# 762 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the grass Pokémon?$"
# 763 "data/maps/NewBarkTown_Lab/scripts.pory"

# 764 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_DidntChooseStarter:
# 765 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Think it over carefully.\p"
# 766 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Your partner is important.$"
# 767 "data/maps/NewBarkTown_Lab/scripts.pory"

# 768 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChoseStarter:
# 769 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: I think that's a great\n"
# 770 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon too!$"
# 771 "data/maps/NewBarkTown_Lab/scripts.pory"

# 772 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ReceivedStarter:
# 773 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} received {STR_VAR_1}!$"
# 774 "data/maps/NewBarkTown_Lab/scripts.pory"

# 775 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Nickname:
# 776 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Would you like to give your\n"
# 777 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{STR_VAR_1} a nickname?$"
# 778 "data/maps/NewBarkTown_Lab/scripts.pory"

# 779 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections1:
# 780 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui is staying in a house\n"
# 781 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "on Route 30, just north of\l"
# 782 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Cherrygrove City.\p"
# 783 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Head west to Cherrygrove,\n"
# 784 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "then follow the road north.\p"
# 785 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You have my phone number,\n"
# 786 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "so call me if you need help!$"
# 787 "data/maps/NewBarkTown_Lab/scripts.pory"

# 788 "data/maps/NewBarkTown_Lab/scripts.pory"

# 789 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmLetYourMonBattle:
# 790 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears,\n"
# 791 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "let your Pokémon battle it!$"
# 792 "data/maps/NewBarkTown_Lab/scripts.pory"

# 793 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections2:
# 794 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears, let\n"
# 795 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "your Pokémon battle it!\p"
# 796 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If your Pokémon is hurt, you\n"
# 797 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "should heal it with the machine\l"
# 798 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to my right, or at the Pokémon Center.\p"
# 799 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm counting on you!$"
# 800 "data/maps/NewBarkTown_Lab/scripts.pory"

# 801 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_GotElmsNumber:
# 802 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} got Elm's phone\n"
# 803 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "number.$"
# 804 "data/maps/NewBarkTown_Lab/scripts.pory"

# 805 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
# 806 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui says familiar Pokémon\n"
# 807 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "can look quite different in Alola.\p"
# 808 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even their types can change!\n"
# 809 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd love to study how they adapt.$"
# 810 "data/maps/NewBarkTown_Lab/scripts.pory"

# 811 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmPokeBall:
# 812 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It contains Pokémon caught\n"
# 813 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "by Prof. Elm.$"
# 814 "data/maps/NewBarkTown_Lab/scripts.pory"

# 815 "data/maps/NewBarkTown_Lab/scripts.pory"
@THEFT================================================================================
# 816 "data/maps/NewBarkTown_Lab/scripts.pory"

# 817 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft1:
# 818 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, this is terrible…\p"
# 819 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, yes, what was Kukui's\n"
# 820 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "big discovery?$"
# 821 "data/maps/NewBarkTown_Lab/scripts.pory"

# 822 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft2:
# 823 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} handed the Mystery Egg\n"
# 824 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to Prof. Elm.$"
# 825 "data/maps/NewBarkTown_Lab/scripts.pory"

# 826 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft3:
# 827 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: This?$"
# 828 "data/maps/NewBarkTown_Lab/scripts.pory"

# 829 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft4:
# 830 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Is it a Pokémon Egg?\p"
# 831 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If it is, it is a great\n"
# 832 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "discovery!\p"
# 833 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: What?!?\p"
# 834 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Oak gave you a Pokédex?\p"
# 835 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, is that true?\n"
# 836 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Th-that's incredible!\p"
# 837 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He is superb at seeing the\n"
# 838 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "potential of people as trainers.\p"
# 839 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wow, {PLAYER}. You may have what\n"
# 840 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it takes to become the Champion.\p"
# 841 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You seem to be getting on\n"
# 842 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "great with Pokémon too.\p"
# 843 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should take the Pokémon\n"
# 844 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gym challenge.\p"
# 845 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The closest Gym would be the\n"
# 846 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "one in Violet City.\p"
# 847 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…{PLAYER}. The road to the\n"
# 848 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "championship will be a long one.\p"
# 849 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Before you leave, make sure\n"
# 850 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that you talk to your mom.$"
# 851 "data/maps/NewBarkTown_Lab/scripts.pory"

# 852 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmStudyingEgg:
# 853 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Don't give up!\n"
# 854 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll call if I learn anything\l"
# 855 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about that Egg!$"
# 856 "data/maps/NewBarkTown_Lab/scripts.pory"

# 857 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideHasEgg:
# 858 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}? Didn't you meet\n"
# 859 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my assistant?\p"
# 860 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He should have met you with\n"
# 861 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg at Violet City's\p"
# 862 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon Center.\p"
# 863 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You must have just missed him.\n"
# 864 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Try to catch him there.$"
# 865 "data/maps/NewBarkTown_Lab/scripts.pory"

# 866 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWaitingEggHatch:
# 867 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hey, has that Egg changed\n"
# 868 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "any?$"
# 869 "data/maps/NewBarkTown_Lab/scripts.pory"

# 870 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmThoughtEggHatched:
# 871 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}? I thought the Egg\n"
# 872 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "hatched.\p"
# 873 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Where is the Pokémon?$"
# 874 "data/maps/NewBarkTown_Lab/scripts.pory"

# 875 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogVisitIntro:
# 876 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! You came back!\p"
# 877 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "And you brought the Pokémon\n"
# 878 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from Kukui's Egg?\p"
# 879 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me put these notes aside.\n"
# 880 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd like a closer look!$"
# 881 "data/maps/NewBarkTown_Lab/scripts.pory"

# 882 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogObservation:
# 883 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "So this is Cosmog...\p"
# 884 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It looks as though a piece\n"
# 885 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of the night sky drifted inside!\p"
# 886 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To think it was tucked away\n"
# 887 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in that little Egg all along.\p"
# 888 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hmm... Where did I put\n"
# 889 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my other notebook?$"
# 890 "data/maps/NewBarkTown_Lab/scripts.pory"

# 891 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogEvolvedObservation:
# 892 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's already evolved?\n"
# 893 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have some catching up to do!\p"
# 894 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What was it like when\n"
# 895 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it first came out of the Egg?\p"
# 896 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even a small detail could help.\n"
# 897 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me find a fresh page!$"
# 898 "data/maps/NewBarkTown_Lab/scripts.pory"

# 899 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogResearchNotes:
# 900 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui sent me one Egg,\n"
# 901 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and now I have a hundred questions.\p"
# 902 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll send him my observations.\n"
# 903 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He may know where to start.\p"
# 904 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I suspect his reply will bring\n"
# 905 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a few more questions too!$"
# 906 "data/maps/NewBarkTown_Lab/scripts.pory"

# 907 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogCare:
# 908 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, listen to me rambling.\n"
# 909 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're here for a visit!\p"
# 910 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thank you for taking care\n"
# 911 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of this Pokémon, {PLAYER}.\p"
# 912 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You get to see things together\n"
# 913 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that I'd never see in this lab.$"
# 914 "data/maps/NewBarkTown_Lab/scripts.pory"

# 915 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogOfferEviolite:
# 916 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Actually, I have something\n"
# 917 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for your travels.\p"
# 918 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I've been keeping it here\n"
# 919 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for a young Trainer to use.$"
# 920 "data/maps/NewBarkTown_Lab/scripts.pory"

# 921 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogBagFull:
# 922 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh! There's no room\n"
# 923 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in your Bag right now.\p"
# 924 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Make some space and come back.\n"
# 925 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll keep it safe for you!$"
# 926 "data/maps/NewBarkTown_Lab/scripts.pory"

# 927 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogExplainEviolite:
# 928 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That's an Eviolite.\p"
# 929 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Have a Pokémon that can still\n"
# 930 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "evolve hold it. It will boost\l"
# 931 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "its Defense and Sp. Def.\p"
# 932 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A little extra protection\n"
# 933 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "while it's growing!\p"
# 934 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can give it to whichever\n"
# 935 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "partner needs it most.$"
# 936 "data/maps/NewBarkTown_Lab/scripts.pory"

# 937 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogFarewell:
# 938 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If you notice anything unusual,\n"
# 939 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "you have my number.\p"
# 940 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now, where was that notebook...?\n"
# 941 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah! Under the first one.\p"
# 942 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take care, {PLAYER}.\n"
# 943 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Both of you!$"
# 944 "data/maps/NewBarkTown_Lab/scripts.pory"

# 945 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmCallYou:
# 946 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, I'll call you if\n"
# 947 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "anything comes up.$"
# 948 "data/maps/NewBarkTown_Lab/scripts.pory"

# 949 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAfterTheft:
# 950 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 951 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 952 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 953 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 954 "data/maps/NewBarkTown_Lab/scripts.pory"

# 955 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall1:
# 956 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hi, {PLAYER}!\p"
# 957 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks to you, my research is\n"
# 958 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going great!\p"
# 959 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take this as a token of my\n"
# 960 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "appreciation.$"
# 961 "data/maps/NewBarkTown_Lab/scripts.pory"

# 962 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall2:
# 963 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Master Ball is the best!\p"
# 964 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the ultimate Ball! It'll\n"
# 965 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "catch any Pokémon without fail.\p"
# 966 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's given only to recognized\n"
# 967 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon researchers.\p"
# 968 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I think you can make much better\n"
# 969 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "use of it than I can, {PLAYER}!$"
# 970 "data/maps/NewBarkTown_Lab/scripts.pory"

# 971 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoGirls:
# 972 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "By the way...\n"
# 973 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A group of beautiful Kimono\l"
# 974 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls were looking for you.\p"
# 975 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They told me they are\n"
# 976 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "waiting for you at the\l"
# 977 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ecruteak Dance Theater.\p"
# 978 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I know you've gone through many\n"
# 979 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "things since that Egg got you\l"
# 980 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "involved in all this...\p"
# 981 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I hope you'll carry through it.$"
# 982 "data/maps/NewBarkTown_Lab/scripts.pory"

# 983 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoWaiting:
# 984 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: The Kimono\n"
# 985 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls are waiting for you at\l"
# 986 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Ecruteak Dance Theater.$"
# 987 "data/maps/NewBarkTown_Lab/scripts.pory"

# 988 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_League:
# 989 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: Hahaha...\n"
# 990 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Good job!\p"
# 991 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That rare Egg has brought you\n"
# 992 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a lot of trouble, huh?\p"
# 993 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Kimono Girls said something\n"
# 994 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about me?\p"
# 995 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have nothing to do with it.\p"
# 996 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You made your decision and went\n"
# 997 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "through with it.\p"
# 998 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Having done so much, you should\n"
# 999 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "be able to face the League now!\p"
# 1000 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should head for Indigo\n"
# 1001 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Plateau!\p"
# 1002 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Do you know how to get there?\n"
# 1003 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Follow Route 27 to Route 26.\p"
# 1004 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Once there, go straight north!$"
# 1005 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1006 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1007 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket1:
# 1008 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\p"
# 1009 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I called because I have\n"
# 1010 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "something for you.\p"
# 1011 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "See? It's an S.S.Ticket.\p"
# 1012 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can catch Pokémon in\n"
# 1013 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Sevii.$"
# 1014 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1015 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket2:
# 1016 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The ship departs from Olivine\n"
# 1017 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "City.\p"
# 1018 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But you knew that already,\n"
# 1019 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}.\p"
# 1020 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "After all, you've traveled all\n"
# 1021 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "over with your Pokémon.$"
# 1022 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1023 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_LabMonEgg:
# 1024 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the Pokémon Egg being\n"
# 1025 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "studied by Prof. Elm.$"
# 1026 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1027 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGivePotion:
# 1028 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, I want you to have\n"
# 1029 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "this for your errand.$"
# 1030 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1031 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAlwaysBusy:
# 1032 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There are only three of us, so\n"
# 1033 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "we're always busy.$"
# 1034 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1035 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideSave:
# 1036 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Don't forget to save your game\n"
# 1037 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "regularly!\p"
# 1038 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Press the Start button, then\n"
# 1039 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Save the game!$"
# 1040 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1041 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideTheftTestimony:
# 1042 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There was a loud noise\n"
# 1043 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "outside…\p"
# 1044 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When we went to look,\n"
# 1045 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "someone stole a Pokémon.\p"
# 1046 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's unbelievable that anyone\n"
# 1047 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "would do that!\p"
# 1048 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 1049 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 1050 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 1051 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 1052 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1053 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGiveBalls:
# 1054 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 1055 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use these on your Pokédex\n"
# 1056 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "quest!$"
# 1057 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1058 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ExplainDexnav:
# 1059 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "We've also sent a Dexnav\n"
# 1060 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "application to your Pokégear!\p"
# 1061 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use it to catch lots of Pokémon!$"
# 1062 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1063 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideExplainBalls:
# 1064 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To add to your Pokédex, you\n"
# 1065 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "have to catch Pokémon.\p"
# 1066 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Throw Poké Balls at wild\n"
# 1067 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon to get them.$"
# 1068 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1069 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer1:
# 1070 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I heard a Pokémon was stolen\n"
# 1071 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here…\p"
# 1072 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I was just getting some\n"
# 1073 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "information from Prof. Elm.\p"
# 1074 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Apparently, it was a young\n"
# 1075 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "male with long, red hair…\p"
# 1076 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What?\p"
# 1077 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You battled a trainer like\n"
# 1078 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that?\p"
# 1079 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Did you happen to get his\n"
# 1080 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "name?$"
# 1081 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1082 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer2:
# 1083 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So Silver was his name.\p"
# 1084 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1085 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1086 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1087 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer3:
# 1088 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So {RIVAL} was his name.\p"
# 1089 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1090 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1091 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1092 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_OfficerNo:
# 1093 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Surely you got his name?!$"
# 1094 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1095 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Elm_CallMe:
# 1096 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah, {PLAYER}!\p"
# 1097 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "How's your Pokédex coming along?\n"
# 1098 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm busy now, but call me sometime\l"
# 1099 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and I can check your progress!$"

NewBarkTown_Lab_GiveStarterMega::
# 1103 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_0
# 1107 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_BONDSTONE, 1
# 1108 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_1
	return


NewBarkTown_Lab_EventScript_ElmPostgameHint::
# 1115 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0
# 1124 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1
# 1126 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1127 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1128 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1129 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1130 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1131 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1132 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 1133 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1134 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2
# 1140 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
# 1141 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_VICTORYROAD_RIVAL
# 1142 "data/maps/NewBarkTown_Lab/scripts.pory"
	checkplayergender
# 1143 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_Lab_EventScript_ElmPostgameHint_2
# 1152 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4
NewBarkTown_Lab_EventScript_ElmPostgameHint_1:
# 1160 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5
# 1162 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MTSILVER_GUARD
# 1163 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALLOW_SOUTH_JOHTO_PASS
# 1164 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 1165 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 11
# 1166 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ElmPostgameHint_2:
# 1144 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3
	goto NewBarkTown_Lab_EventScript_ElmPostgameHint_1


ElmIntro::
# 1171 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox ElmIntro_Text_0, MSGBOX_YESNO
	return


NewBarkTown_Lab_EventScript_ArtifactOfChaos::
# 1197 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 1198 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_ALL_INNATES_UNLOCKED, NewBarkTown_Lab_EventScript_ArtifactOfChaos_2
# 1222 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4
# 1227 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5
# 1233 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6, MSGBOX_YESNO
# 1239 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_8
# 1252 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8
NewBarkTown_Lab_EventScript_ArtifactOfChaos_1:
# 1256 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 1257 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ArtifactOfChaos_2:
# 1199 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0
# 1203 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1, MSGBOX_YESNO
# 1204 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_5
# 1218 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_5:
# 1205 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_OFF
# 1206 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1207 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_ALL_INNATES_UNLOCKED
# 1208 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_NEWBARKTOWN_LABSTATE, 11
	goto_if_lt NewBarkTown_Lab_EventScript_ArtifactOfChaos_12
# 1211 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
NewBarkTown_Lab_EventScript_ArtifactOfChaos_11:
# 1213 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_8:
# 1240 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_SWITCH
# 1241 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1242 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALL_INNATES_UNLOCKED
# 1243 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_REPLAY_NO_INNATES
# 1244 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_12:
# 1209 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_POSTGAME_FEATURES
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_11


NewBarkTown_Lab_GiveStarterMega_Text_0:
# 1103 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, and you got a Mega Ring from \n"
	.string "Prof. Oak?\l"
	.string "Then I think you are ready to handle\l"
	.string "this.$"

NewBarkTown_Lab_GiveStarterMega_Text_1:
# 1108 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's a special Mega Stone, specifically\n"
	.string "for your starter Pokémon. I expect \l"
	.string "great things from you, {PLAYER}!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0:
# 1115 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\n"
	.string "I called because I heard that the \l"
	.string "Battle Tower is open! \p"
	.string "I hear strong trainers\n"
	.string "are gathering in there!\p"
	.string "You can get there from Route 40\n"
	.string "near Olivine City.$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1:
# 1124 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But first, let me upgrade your Pokédex\n"
	.string "with a new feature!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2:
# 1134 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can view abilities of the\n"
	.string "opposing Pokémon with the L-button\l"
	.string "in battle! \p"
	.string "That will surely be handy as the\n"
	.string "battles get tougher!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3:
# 1144 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Crystal went to train\n"
	.string "in Mt. Silver. \p"
	.string "She looked really tired\n"
	.string "the last time I saw her though... \p"
	.string "Could you check on her at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4:
# 1152 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Gold went to train\n"
	.string "in Mt. Silver. \p"
	.string "He looked really tired\n"
	.string "the last time I saw him though...\p"
	.string "Could you check on him at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5:
# 1160 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I asked from the League to let you\n"
	.string "pass since you've the new Champion.$"

ElmIntro_Text_0:
# 1171 "data/maps/NewBarkTown_Lab/scripts.pory"
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
# 1199 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact of Chaos is humming.\p"
	.string "All innate abilities are currently\n"
	.string "active.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1:
# 1203 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Deactivate the Artifact?$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2:
# 1213 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The glow from the Artifact fades.\p"
	.string "Innate abilities will now unlock at\n"
	.string "their intended levels again.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3:
# 1218 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact continues humming.\n"
	.string "Hope Elm hasn't noticed yet!$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4:
# 1222 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Amidst the books is Elm's very own\n"
	.string "Artifact of Chaos.\p"
	.string "There's a small label on the side:\n"
	.string "DO NOT TOUCH.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5:
# 1227 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Important! Activating this Artifact\n"
	.string "unlocks all innate abilities,\l"
	.string "regardless of a Pokémon's level.\p"
	.string "It also lets you inspect enemy\n"
	.string "innates in battle by pressing L.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6:
# 1233 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "This is not the intended way to play\n"
	.string "the game and will not be balanced\l"
	.string "at all.\p"
	.string "If you understand and still wish to\n"
	.string "activate it, choose Yes.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7:
# 1244 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} tapped the Artifact.\p"
	.string "Game balance quietly\n"
	.string "leaves the building.\p"
	.string "All innates are now active. Press L\n"
	.string "in battle to inspect enemy innates.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8:
# 1252 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} left the Artifact alone.\n"
	.string "Chaos shall not win today.$"
