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
@ WARNING: the three lines below are goto_if_eq, NOT call_if_eq - whoever
# 9 "data/maps/NewBarkTown_Lab/scripts.pory"
@ matches one never comes back here. Any new call must go ABOVE them or it
# 10 "data/maps/NewBarkTown_Lab/scripts.pory"
@ silently stops running in those lab states. (Rift Mission 4, section 3.6.)
# 11 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_OnTransition::
# 12 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_ApplyElmVisibility                @ Rift Mission 4 - must stay first
# 13 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
# 14 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
# 15 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
# 16 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 17 "data/maps/NewBarkTown_Lab/scripts.pory"
	
# 18 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_OnFrame::
# 19 "data/maps/NewBarkTown_Lab/scripts.pory"
	map_script_2 VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
# 20 "data/maps/NewBarkTown_Lab/scripts.pory"
	.2byte 0
# 21 "data/maps/NewBarkTown_Lab/scripts.pory"

# 22 "data/maps/NewBarkTown_Lab/scripts.pory"
@ Rift Mission 4 (.claude/NEWBARK_ULTRABEAST_IMPLEMENTATION.md, section 3.6).
# 23 "data/maps/NewBarkTown_Lab/scripts.pory"
@ Professor Elm stands on the road outside during the New Bark incident, and
# 24 "data/maps/NewBarkTown_Lab/scripts.pory"
@ the lab door is one warp from the scene, so he must not also be in here.
# 25 "data/maps/NewBarkTown_Lab/scripts.pory"
@ LOCALID_ELM's map.json "flag" field used to be 0; it is now FLAG_TEMP_1, a
# 26 "data/maps/NewBarkTown_Lab/scripts.pory"
@ dumb per-visit cache, and FLAG_EVENT_ULTRABEAST_NEWBARK stays the
# 27 "data/maps/NewBarkTown_Lab/scripts.pory"
@ persistent truth. The two changes are a PAIR: the map.json without this
# 28 "data/maps/NewBarkTown_Lab/scripts.pory"
@ script deletes Elm from the lab permanently.
# 29 "data/maps/NewBarkTown_Lab/scripts.pory"
@   visible <=> no incident running
# 30 "data/maps/NewBarkTown_Lab/scripts.pory"
@ Temps are zeroed on every map load, so the default is VISIBLE - the safe
# 31 "data/maps/NewBarkTown_Lab/scripts.pory"
@ error. NEVER removeobject LOCALID_ELM.
# 32 "data/maps/NewBarkTown_Lab/scripts.pory"
@ NewBarkTown_Lab_EventScript_ElmAtComputer below does setobjectxyperm on the
# 33 "data/maps/NewBarkTown_Lab/scripts.pory"
@ same local id. That is position, not visibility, and the two do not fight:
# 34 "data/maps/NewBarkTown_Lab/scripts.pory"
@ after the mission the template is re-read from map.json and Elm is back at
# 35 "data/maps/NewBarkTown_Lab/scripts.pory"
@ (6,3) - or at (3,2) in the lab states that ask for it.
# 36 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_ApplyElmVisibility::
# 37 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_TEMP_1
# 38 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_Lab_ElmStays
# 39 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_TEMP_1
# 40 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_ElmStays::
# 41 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 42 "data/maps/NewBarkTown_Lab/scripts.pory"

# 43 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAtComputer::
# 44 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxyperm LOCALID_ELM, 3, 2
# 45 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
# 46 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 47 "data/maps/NewBarkTown_Lab/scripts.pory"

# 48 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
# 49 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 50 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
# 51 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 52 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 53 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 54 "data/maps/NewBarkTown_Lab/scripts.pory"

# 55 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabRight::
# 56 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 57 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
# 58 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 59 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 60 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 61 "data/maps/NewBarkTown_Lab/scripts.pory"

# 62 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLab::
# 63 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 64 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
# 65 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 66 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmIntro
# 67 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 68 "data/maps/NewBarkTown_Lab/scripts.pory"

# 69 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide1::
# 70 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 71 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 72 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
# 73 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 74 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 75 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 76 "data/maps/NewBarkTown_Lab/scripts.pory"

# 77 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2::
# 78 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 79 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 80 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
# 81 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
# 82 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 83 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 84 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 85 "data/maps/NewBarkTown_Lab/scripts.pory"

# 86 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2Testimony::
# 87 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
# 88 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 89 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 90 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 91 "data/maps/NewBarkTown_Lab/scripts.pory"

# 92 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm::
# 93 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 94 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 95 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, NewBarkTown_Lab_EventScript_ElmAfterGladion
# 96 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_VIOLET_CITY_STATE, 4, NewBarkTown_Lab_EventScript_ElmGladionIsWaiting
# 97 "data/maps/NewBarkTown_Lab/scripts.pory"

# 98 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAfterGladion::
# 99 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
# 100 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
# 101 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
# 102 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmPostgameHint
# 103 "data/maps/NewBarkTown_Lab/scripts.pory"

# 104 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_CallMe
# 105 "data/maps/NewBarkTown_Lab/scripts.pory"
	call_if_unset FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_Check_Cosmog
# 106 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
# 107 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5
# 108 "data/maps/NewBarkTown_Lab/scripts.pory"

# 109 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
# 110 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
# 111 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
# 112 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
# 113 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 114 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 115 "data/maps/NewBarkTown_Lab/scripts.pory"

# 116 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmGladionIsWaiting::
# 117 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGladionIsWaiting, MSGBOX_DEFAULT
# 118 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 119 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 120 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 121 "data/maps/NewBarkTown_Lab/scripts.pory"

# 122 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGladionIsWaiting:
# 123 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 124 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What are you doing here?\p"
# 125 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gladion is waiting for you at\n"
# 126 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Violet City's Pokémon Center.\p"
# 127 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He has the Egg I wanted you to\n"
# 128 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "look after.$"
# 129 "data/maps/NewBarkTown_Lab/scripts.pory"

# 130 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmIntro::
# 131 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 132 "data/maps/NewBarkTown_Lab/scripts.pory"
	call ElmIntro
# 133 "data/maps/NewBarkTown_Lab/scripts.pory"
	@msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
# 134 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 135 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 136 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 137 "data/maps/NewBarkTown_Lab/scripts.pory"

# 138 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmRefused::
# 139 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 140 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
# 141 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 142 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 143 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 144 "data/maps/NewBarkTown_Lab/scripts.pory"

# 145 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAccepted::
# 146 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 147 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
# 148 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
# 149 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 150 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_LOGIN
# 151 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 152 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 153 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
# 154 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 155 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
# 156 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
# 157 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement LOCALID_ELM
# 158 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 159 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
# 160 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 161 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 162 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
# 163 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 164 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 165 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 166 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 167 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 168 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
# 169 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 170 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 171 "data/maps/NewBarkTown_Lab/scripts.pory"

# 172 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmChoosePokemon::
# 173 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 174 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Right
# 175 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 176 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 177 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
# 178 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 179 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 180 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Down
# 181 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 182 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
# 183 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 184 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 185 "data/maps/NewBarkTown_Lab/scripts.pory"

# 186 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
# 187 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 188 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 189 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
# 190 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 191 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 192 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
# 193 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 194 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 195 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 196 "data/maps/NewBarkTown_Lab/scripts.pory"

# 197 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ShouldntTouch::
# 198 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 199 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 200 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 201 "data/maps/NewBarkTown_Lab/scripts.pory"

# 202 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_hideStarterCase::
# 203 "data/maps/NewBarkTown_Lab/scripts.pory"
    setflag FLAG_HIDE_STARTER_CASE
# 204 "data/maps/NewBarkTown_Lab/scripts.pory"
    return
# 205 "data/maps/NewBarkTown_Lab/scripts.pory"

# 206 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase::
# 207 "data/maps/NewBarkTown_Lab/scripts.pory"
    lock
# 208 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_SOUTH, NewBarkTown_Lab_EventScript_StarterCaseWrongSide
# 209 "data/maps/NewBarkTown_Lab/scripts.pory"
	callnative MigrateNationalPokedex
# 210 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
# 211 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_StarterCase_Choice
# 212 "data/maps/NewBarkTown_Lab/scripts.pory"
    msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 213 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 214 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 215 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 216 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCaseWrongSide::
# 217 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_StarterCaseWrongSide, MSGBOX_DEFAULT
# 218 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 219 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 220 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 221 "data/maps/NewBarkTown_Lab/scripts.pory"

# 222 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase_Choice::
# 223 "data/maps/NewBarkTown_Lab/scripts.pory"
   callnative StartNewPokeballCaseUI
# 224 "data/maps/NewBarkTown_Lab/scripts.pory"
   waitstate
# 225 "data/maps/NewBarkTown_Lab/scripts.pory"
   goto NewBarkTown_Lab_EventScript_ChoseStarter
# 226 "data/maps/NewBarkTown_Lab/scripts.pory"

# 227 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter::
# 228 "data/maps/NewBarkTown_Lab/scripts.pory"
	showmonpic VAR_PLAYER_STARTER_SPECIES, 10, 3
# 229 "data/maps/NewBarkTown_Lab/scripts.pory"
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
# 230 "data/maps/NewBarkTown_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_PLAYER_STARTER_SPECIES
# 231 "data/maps/NewBarkTown_Lab/scripts.pory"
	message NewBarkTown_Lab_Text_ReceivedStarter
# 232 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE 1
# 233 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitfanfare
# 234 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 235 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 236 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_StepBackFromStarter
# 237 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 238 "data/maps/NewBarkTown_Lab/scripts.pory"
	updatefollowingmon
# 239 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxy OBJ_EVENT_ID_FOLLOWER, 9, 5
# 240 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterLeavesBall
# 241 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_BALL_OPEN
# 242 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 243 "data/maps/NewBarkTown_Lab/scripts.pory"
	playmoncry VAR_PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
# 244 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_LEDGE
# 245 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterGreetsPlayer
# 246 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 247 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmoncry
# 248 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 45
# 249 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 250 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
# 251 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 252 "data/maps/NewBarkTown_Lab/scripts.pory"
    closemessage
# 253 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 254 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 255 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 256 "data/maps/NewBarkTown_Lab/scripts.pory"

# 257 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter2::
# 258 "data/maps/NewBarkTown_Lab/scripts.pory"
    moveobjecttocoords OBJ_EVENT_ID_PLAYER, 6, 4, DIR_NORTH
# 259 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 260 "data/maps/NewBarkTown_Lab/scripts.pory"
    @applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 261 "data/maps/NewBarkTown_Lab/scripts.pory"
    @waitmovement 0
# 262 "data/maps/NewBarkTown_Lab/scripts.pory"
    clearflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 263 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_RIVAL_STATE, 2
# 264 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE, 2
# 265 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto NewBarkTown_Lab_EventScript_MrPokemon
# 266 "data/maps/NewBarkTown_Lab/scripts.pory"

# 267 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_DeclinedStarter::
# 268 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 269 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
# 270 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 271 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 272 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 273 "data/maps/NewBarkTown_Lab/scripts.pory"

# 274 "data/maps/NewBarkTown_Lab/scripts.pory"

# 275 "data/maps/NewBarkTown_Lab/scripts.pory"

# 276 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_NicknameStarter::
# 277 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_0x8004, 0
# 278 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 279 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 280 "data/maps/NewBarkTown_Lab/scripts.pory"

# 281 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemon::
# 282 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
# 283 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 284 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 285 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 286 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 287 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 288 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 289 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 290 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
# 291 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
# 292 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 293 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 294 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 295 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 296 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 297 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 298 "data/maps/NewBarkTown_Lab/scripts.pory"

# 299 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
# 300 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
# 301 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 302 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 303 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 304 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 305 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 306 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 307 "data/maps/NewBarkTown_Lab/scripts.pory"

# 308 "data/maps/NewBarkTown_Lab/scripts.pory"
CopNewBarkTown_Lab_EventScript_ElmState2::
# 309 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 310 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 311 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
# 312 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 313 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 314 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 315 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 316 "data/maps/NewBarkTown_Lab/scripts.pory"

# 317 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine1::
# 318 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 319 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
# 320 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 321 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 322 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 323 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 324 "data/maps/NewBarkTown_Lab/scripts.pory"

# 325 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine2::
# 326 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 327 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 328 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 329 "data/maps/NewBarkTown_Lab/scripts.pory"

# 330 "data/maps/NewBarkTown_Lab/scripts.pory"

# 331 "data/maps/NewBarkTown_Lab/scripts.pory"

# 332 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
# 333 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 334 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 335 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 336 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 337 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
# 338 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 339 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POTION
# 340 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 341 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
# 342 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 343 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 344 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 345 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 346 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 347 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 348 "data/maps/NewBarkTown_Lab/scripts.pory"

# 349 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceEpisode::
# 350 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 351 "data/maps/NewBarkTown_Lab/scripts.pory"
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
# 352 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_hideStarterCase
# 353 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
# 354 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 355 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_LAB_POLICEMAN
# 356 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject LOCALID_COP DIR_WEST
# 357 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
# 358 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceNameRival
# 359 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceYes
# 360 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 361 "data/maps/NewBarkTown_Lab/scripts.pory"

# 362 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNo::
# 363 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
# 364 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
# 365 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
# 366 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 367 "data/maps/NewBarkTown_Lab/scripts.pory"

# 368 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival::
# 369 "data/maps/NewBarkTown_Lab/scripts.pory"
	special NameRival
# 370 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitstate
# 371 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_NAMED_SILVER
# 372 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 373 "data/maps/NewBarkTown_Lab/scripts.pory"

# 374 "data/maps/NewBarkTown_Lab/scripts.pory"

# 375 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival2::
# 376 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 377 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 378 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 379 "data/maps/NewBarkTown_Lab/scripts.pory"

# 380 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes::
# 381 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
# 382 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 383 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes2
# 384 "data/maps/NewBarkTown_Lab/scripts.pory"

# 385 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes3::
# 386 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 387 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 388 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 389 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 390 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 391 "data/maps/NewBarkTown_Lab/scripts.pory"

# 392 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 393 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 394 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 395 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 396 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 397 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 398 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 399 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 400 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 401 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 402 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 403 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 404 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 405 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 406 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 407 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 408 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 409 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 410 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 411 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 412 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 413 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 414 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 415 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 416 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 417 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 418 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 419 "data/maps/NewBarkTown_Lab/scripts.pory"

# 420 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes2::
# 421 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 422 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 423 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 424 "data/maps/NewBarkTown_Lab/scripts.pory"

# 425 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 426 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 427 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 428 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 429 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 430 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 431 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 432 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 433 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 434 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 435 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 436 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 437 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 438 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 439 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 440 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 441 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 442 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 443 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 444 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 445 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 446 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 447 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 448 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 449 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 450 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 451 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 452 "data/maps/NewBarkTown_Lab/scripts.pory"

# 453 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmState5::
# 454 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 455 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 456 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
# 457 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 458 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
# 459 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 460 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 461 "data/maps/NewBarkTown_Lab/scripts.pory"

# 462 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmMasterBall::
# 463 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 464 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 465 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
# 466 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_MASTER_BALL
# 467 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
# 468 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 469 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 470 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 471 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
# 472 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 473 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
# 474 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_GiveStarterMega
# 475 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_GiveMissedSurf
# 476 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 477 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
# 478 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
# 479 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_SILVER
# 480 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
# 481 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
# 482 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 483 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 484 "data/maps/NewBarkTown_Lab/scripts.pory"

# 485 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmKimono::
# 486 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 487 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 488 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_GiveMissedSurf
# 489 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
# 490 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 491 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 492 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 493 "data/maps/NewBarkTown_Lab/scripts.pory"

# 494 "data/maps/NewBarkTown_Lab/scripts.pory"
@ HM Surf normally comes from the man in the Ecruteak Dance Theater after
# 495 "data/maps/NewBarkTown_Lab/scripts.pory"
@ the Rocket Grunt is beaten. The Master Ball scene above hides him
# 496 "data/maps/NewBarkTown_Lab/scripts.pory"
@ (FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS) and jumps the theater to state 4,
# 497 "data/maps/NewBarkTown_Lab/scripts.pory"
@ so a player who skipped that arc would lose Surf for good. Elm hands it
# 498 "data/maps/NewBarkTown_Lab/scripts.pory"
@ over instead. Also called from ElmKimono for saves already past the scene.
# 499 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_GiveMissedSurf::
# 500 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_SURF, NewBarkTown_Lab_EventScript_GiveMissedSurfEnd
# 501 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissedSurf, MSGBOX_DEFAULT
# 502 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_HM_SURF
# 503 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_GiveMissedSurfEnd
# 504 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_HM_SURF
# 505 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_GiveMissedSurfEnd::
# 506 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 507 "data/maps/NewBarkTown_Lab/scripts.pory"

# 508 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmLeague::
# 509 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 510 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 511 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
# 512 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 513 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 514 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 515 "data/maps/NewBarkTown_Lab/scripts.pory"

# 516 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmSSTicket::
# 517 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
# 518 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_SS_TICKET
# 519 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
# 520 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 521 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
# 522 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 523 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
# 524 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 525 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 526 "data/maps/NewBarkTown_Lab/scripts.pory"

# 527 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
# 528 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 529 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 530 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 531 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 532 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
# 533 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 534 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POKE_BALL, 10
# 535 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 536 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_FIRST_BALLS
# 537 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
# 538 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ExplainDexnav, MSGBOX_DEFAULT
# 539 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 540 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 541 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 542 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 543 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 544 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 545 "data/maps/NewBarkTown_Lab/scripts.pory"

# 546 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
# 547 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
# 548 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 549 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 550 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 551 "data/maps/NewBarkTown_Lab/scripts.pory"

# 552 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_Cosmog::
# 553 "data/maps/NewBarkTown_Lab/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 554 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen
# 555 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 556 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_SOLGALEO, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 557 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_LUNALA, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 558 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 559 "data/maps/NewBarkTown_Lab/scripts.pory"

# 560 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen::
# 561 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 562 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 563 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 564 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogObservation, MSGBOX_DEFAULT
# 565 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 566 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward
# 567 "data/maps/NewBarkTown_Lab/scripts.pory"

# 568 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen::
# 569 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 570 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 571 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 572 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogEvolvedObservation, MSGBOX_DEFAULT
# 573 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 574 "data/maps/NewBarkTown_Lab/scripts.pory"

# 575 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward::
# 576 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogResearchNotes, MSGBOX_DEFAULT
# 577 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 578 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogCare, MSGBOX_DEFAULT
# 579 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 580 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogOfferEviolite, MSGBOX_DEFAULT
# 581 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 582 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 583 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 584 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_EVIOLITE
# 585 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull
# 586 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_SHOWN_ELM_COSMOG
# 587 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 588 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogExplainEviolite, MSGBOX_DEFAULT
# 589 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 590 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogFarewell, MSGBOX_DEFAULT
# 591 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 592 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 593 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 594 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 595 "data/maps/NewBarkTown_Lab/scripts.pory"

# 596 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull::
# 597 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogBagFull, MSGBOX_DEFAULT
# 598 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 599 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 600 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 601 "data/maps/NewBarkTown_Lab/scripts.pory"

# 602 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_CallMe::
# 603 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
# 604 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 605 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 606 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 607 "data/maps/NewBarkTown_Lab/scripts.pory"

# 608 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkRight:
# 609 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 610 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 611 "data/maps/NewBarkTown_Lab/scripts.pory"

# 612 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkLeft:
# 613 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 614 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 615 "data/maps/NewBarkTown_Lab/scripts.pory"

# 616 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StepBackFromStarter:
# 617 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 618 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 619 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 620 "data/maps/NewBarkTown_Lab/scripts.pory"

# 621 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterLeavesBall:
# 622 "data/maps/NewBarkTown_Lab/scripts.pory"
	exit_pokeball
# 623 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 624 "data/maps/NewBarkTown_Lab/scripts.pory"
	set_visible
# 625 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 626 "data/maps/NewBarkTown_Lab/scripts.pory"

# 627 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterGreetsPlayer:
# 628 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 629 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay_4
# 630 "data/maps/NewBarkTown_Lab/scripts.pory"
	jump_in_place_down
# 631 "data/maps/NewBarkTown_Lab/scripts.pory"
	emote_heart
# 632 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 633 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 634 "data/maps/NewBarkTown_Lab/scripts.pory"

# 635 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_LabMovement_WalkToElm:
# 636 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 637 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 638 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 639 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 640 "data/maps/NewBarkTown_Lab/scripts.pory"

# 641 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnPlayer:
# 642 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 643 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 644 "data/maps/NewBarkTown_Lab/scripts.pory"

# 645 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmail:
# 646 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 647 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 648 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 649 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 650 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 651 "data/maps/NewBarkTown_Lab/scripts.pory"

# 652 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmailSlow:
# 653 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 654 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 655 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 656 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 657 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 658 "data/maps/NewBarkTown_Lab/scripts.pory"

# 659 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_GotoComputerSafe:
# 660 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 661 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 662 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 663 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 664 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 665 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 666 "data/maps/NewBarkTown_Lab/scripts.pory"

# 667 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnFromEmail:
# 668 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 669 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 670 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 671 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 672 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 673 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 674 "data/maps/NewBarkTown_Lab/scripts.pory"

# 675 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Left:
# 676 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_left
# 677 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 678 "data/maps/NewBarkTown_Lab/scripts.pory"

# 679 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Up:
# 680 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 681 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 682 "data/maps/NewBarkTown_Lab/scripts.pory"

# 683 "data/maps/NewBarkTown_Lab/scripts.pory"

# 684 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
# 685 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 686 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 687 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 688 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 689 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 690 "data/maps/NewBarkTown_Lab/scripts.pory"

# 691 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1LeavePlayer:
# 692 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 693 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 694 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 695 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 696 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 697 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 698 "data/maps/NewBarkTown_Lab/scripts.pory"

# 699 "data/maps/NewBarkTown_Lab/scripts.pory"
NeBarkTownLab_Movement_PlayerWalkToCop:
# 700 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 701 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 702 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 703 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 704 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 705 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 706 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 707 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 708 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 709 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_right
# 710 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 711 "data/maps/NewBarkTown_Lab/scripts.pory"

# 712 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Right:
# 713 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_right
# 714 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 715 "data/maps/NewBarkTown_Lab/scripts.pory"

# 716 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Down:
# 717 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_down
# 718 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 719 "data/maps/NewBarkTown_Lab/scripts.pory"

# 720 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CopLeaves:
# 721 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 722 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 723 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 724 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 725 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 726 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 727 "data/maps/NewBarkTown_Lab/scripts.pory"

# 728 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_PlayerStepsToElm:
# 729 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 730 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 731 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 732 "data/maps/NewBarkTown_Lab/scripts.pory"

# 733 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepBack:
# 734 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock_facing_direction
# 735 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 736 "data/maps/NewBarkTown_Lab/scripts.pory"
	unlock_facing_direction
# 737 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 738 "data/maps/NewBarkTown_Lab/scripts.pory"

# 739 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepForward:
# 740 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 741 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 742 "data/maps/NewBarkTown_Lab/scripts.pory"

# 743 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShouldntTouch:
# 744 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Probably shouldn't touch!$"
# 745 "data/maps/NewBarkTown_Lab/scripts.pory"

# 746 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_StarterCaseWrongSide:
# 747 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oops, the case does not open\n"
# 748 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from this side!$"
# 749 "data/maps/NewBarkTown_Lab/scripts.pory"

# 750 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAccepted:
# 751 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks, {PLAYER}!\n"
# 752 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're a great help!$"
# 753 "data/maps/NewBarkTown_Lab/scripts.pory"

# 754 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmRefused:
# 755 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Please, I need your\n"
# 756 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "help!$"
# 757 "data/maps/NewBarkTown_Lab/scripts.pory"

# 758 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmResearchAmbitions:
# 759 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When I announce my findings,\n"
# 760 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm sure we'll delve deeper\p"
# 761 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "into the many mysteries of\n"
# 762 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon.\p"
# 763 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can count on it!$"
# 764 "data/maps/NewBarkTown_Lab/scripts.pory"

# 765 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGotAnEmail:
# 766 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, hey! I got an e-mail!\p"
# 767 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "… … … … … … … …\n"
# 768 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hm… Uh-huh…\p"
# 769 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Okay…$"
# 770 "data/maps/NewBarkTown_Lab/scripts.pory"

# 771 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
# 772 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That was Professor Kukui,\n"
# 773 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a researcher from Alola.\p"
# 774 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's visiting Johto to study\n"
# 775 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Alolan Pokémon spotted here.\p"
# 776 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A Day-Care couple gave him\n"
# 777 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "an unusual Egg.\p"
# 778 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He'd like me to examine it!\p"
# 779 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's working from a house on\n"
# 780 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Route 30, north of Cherrygrove.\p"
# 781 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd go myself, but I can't\n"
# 782 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "leave the lab right now...\p"
# 783 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wait! I have an idea!\p"
# 784 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, could you pick up\n"
# 785 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg for me?$"
# 786 "data/maps/NewBarkTown_Lab/scripts.pory"

# 787 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmChooseAPokemon:
# 788 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I want you to raise one of\n"
# 789 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Pokémon contained in this case.\p"
# 790 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You'll be that Pokémon's\n"
# 791 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "first partner, {PLAYER}!\p"
# 792 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Go on. Pick one!$"
# 793 "data/maps/NewBarkTown_Lab/scripts.pory"

# 794 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWhereGoing:
# 795 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Wait! Where are you\n"
# 796 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going?$"
# 797 "data/maps/NewBarkTown_Lab/scripts.pory"

# 798 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseCyndaquil:
# 799 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: You'll take Cyndaquil,\n"
# 800 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the fire Pokémon?$"
# 801 "data/maps/NewBarkTown_Lab/scripts.pory"

# 802 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseTotodile:
# 803 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Do you want Totodile,\n"
# 804 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the water Pokémon?$"
# 805 "data/maps/NewBarkTown_Lab/scripts.pory"

# 806 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseChikorita:
# 807 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: So, you like Chikorita,\n"
# 808 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the grass Pokémon?$"
# 809 "data/maps/NewBarkTown_Lab/scripts.pory"

# 810 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_DidntChooseStarter:
# 811 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Think it over carefully.\p"
# 812 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Your partner is important.$"
# 813 "data/maps/NewBarkTown_Lab/scripts.pory"

# 814 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChoseStarter:
# 815 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: I think that's a great\n"
# 816 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon too!$"
# 817 "data/maps/NewBarkTown_Lab/scripts.pory"

# 818 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ReceivedStarter:
# 819 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} received {STR_VAR_1}!$"
# 820 "data/maps/NewBarkTown_Lab/scripts.pory"

# 821 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Nickname:
# 822 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Would you like to give your\n"
# 823 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{STR_VAR_1} a nickname?$"
# 824 "data/maps/NewBarkTown_Lab/scripts.pory"

# 825 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections1:
# 826 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui is staying in a house\n"
# 827 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "on Route 30, just north of\l"
# 828 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Cherrygrove City.\p"
# 829 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Head west to Cherrygrove,\n"
# 830 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "then follow the road north.\p"
# 831 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You have my phone number,\n"
# 832 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "so call me if you need help!$"
# 833 "data/maps/NewBarkTown_Lab/scripts.pory"

# 834 "data/maps/NewBarkTown_Lab/scripts.pory"

# 835 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmLetYourMonBattle:
# 836 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears,\n"
# 837 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "let your Pokémon battle it!$"
# 838 "data/maps/NewBarkTown_Lab/scripts.pory"

# 839 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections2:
# 840 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears, let\n"
# 841 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "your Pokémon battle it!\p"
# 842 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If your Pokémon is hurt, you\n"
# 843 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "should heal it with the machine\l"
# 844 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to my right, or at the Pokémon Center.\p"
# 845 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm counting on you!$"
# 846 "data/maps/NewBarkTown_Lab/scripts.pory"

# 847 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_GotElmsNumber:
# 848 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} got Elm's phone\n"
# 849 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "number.$"
# 850 "data/maps/NewBarkTown_Lab/scripts.pory"

# 851 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
# 852 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui says familiar Pokémon\n"
# 853 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "can look quite different in Alola.\p"
# 854 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even their types can change!\n"
# 855 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd love to study how they adapt.$"
# 856 "data/maps/NewBarkTown_Lab/scripts.pory"

# 857 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmPokeBall:
# 858 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It contains Pokémon caught\n"
# 859 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "by Prof. Elm.$"
# 860 "data/maps/NewBarkTown_Lab/scripts.pory"

# 861 "data/maps/NewBarkTown_Lab/scripts.pory"
@THEFT================================================================================
# 862 "data/maps/NewBarkTown_Lab/scripts.pory"

# 863 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft1:
# 864 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, this is terrible…\p"
# 865 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, yes, what was Kukui's\n"
# 866 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "big discovery?$"
# 867 "data/maps/NewBarkTown_Lab/scripts.pory"

# 868 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft2:
# 869 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} handed the Mystery Egg\n"
# 870 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to Prof. Elm.$"
# 871 "data/maps/NewBarkTown_Lab/scripts.pory"

# 872 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft3:
# 873 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: This?$"
# 874 "data/maps/NewBarkTown_Lab/scripts.pory"

# 875 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft4:
# 876 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Is it a Pokémon Egg?\p"
# 877 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If it is, it is a great\n"
# 878 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "discovery!\p"
# 879 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: What?!?\p"
# 880 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Oak gave you a Pokédex?\p"
# 881 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, is that true?\n"
# 882 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Th-that's incredible!\p"
# 883 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He is superb at seeing the\n"
# 884 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "potential of people as trainers.\p"
# 885 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wow, {PLAYER}. You may have what\n"
# 886 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it takes to become the Champion.\p"
# 887 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You seem to be getting on\n"
# 888 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "great with Pokémon too.\p"
# 889 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should take the Pokémon\n"
# 890 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gym challenge.\p"
# 891 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The closest Gym would be the\n"
# 892 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "one in Violet City.\p"
# 893 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…{PLAYER}. The road to the\n"
# 894 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "championship will be a long one.\p"
# 895 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Before you leave, make sure\n"
# 896 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that you talk to your mom.$"
# 897 "data/maps/NewBarkTown_Lab/scripts.pory"

# 898 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmStudyingEgg:
# 899 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Don't give up!\n"
# 900 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll call if I learn anything\l"
# 901 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about that Egg!$"
# 902 "data/maps/NewBarkTown_Lab/scripts.pory"

# 903 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideHasEgg:
# 904 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}? Didn't you meet\n"
# 905 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my assistant?\p"
# 906 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He should have met you with\n"
# 907 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg at Violet City's\p"
# 908 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon Center.\p"
# 909 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You must have just missed him.\n"
# 910 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Try to catch him there.$"
# 911 "data/maps/NewBarkTown_Lab/scripts.pory"

# 912 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWaitingEggHatch:
# 913 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hey, has that Egg changed\n"
# 914 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "any?$"
# 915 "data/maps/NewBarkTown_Lab/scripts.pory"

# 916 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmThoughtEggHatched:
# 917 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}? I thought the Egg\n"
# 918 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "hatched.\p"
# 919 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Where is the Pokémon?$"
# 920 "data/maps/NewBarkTown_Lab/scripts.pory"

# 921 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogVisitIntro:
# 922 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! You came back!\p"
# 923 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "And you brought the Pokémon\n"
# 924 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from Kukui's Egg?\p"
# 925 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me put these notes aside.\n"
# 926 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd like a closer look!$"
# 927 "data/maps/NewBarkTown_Lab/scripts.pory"

# 928 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogObservation:
# 929 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "So this is Cosmog...\p"
# 930 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It looks as though a piece\n"
# 931 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of the night sky drifted inside!\p"
# 932 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To think it was tucked away\n"
# 933 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in that little Egg all along.\p"
# 934 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hmm... Where did I put\n"
# 935 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my other notebook?$"
# 936 "data/maps/NewBarkTown_Lab/scripts.pory"

# 937 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogEvolvedObservation:
# 938 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's already evolved?\n"
# 939 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have some catching up to do!\p"
# 940 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What was it like when\n"
# 941 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it first came out of the Egg?\p"
# 942 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even a small detail could help.\n"
# 943 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me find a fresh page!$"
# 944 "data/maps/NewBarkTown_Lab/scripts.pory"

# 945 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogResearchNotes:
# 946 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui sent me one Egg,\n"
# 947 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and now I have a hundred questions.\p"
# 948 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll send him my observations.\n"
# 949 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He may know where to start.\p"
# 950 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I suspect his reply will bring\n"
# 951 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a few more questions too!$"
# 952 "data/maps/NewBarkTown_Lab/scripts.pory"

# 953 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogCare:
# 954 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, listen to me rambling.\n"
# 955 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're here for a visit!\p"
# 956 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thank you for taking care\n"
# 957 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of this Pokémon, {PLAYER}.\p"
# 958 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You get to see things together\n"
# 959 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that I'd never see in this lab.$"
# 960 "data/maps/NewBarkTown_Lab/scripts.pory"

# 961 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogOfferEviolite:
# 962 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Actually, I have something\n"
# 963 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for your travels.\p"
# 964 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I've been keeping it here\n"
# 965 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for a young Trainer to use.$"
# 966 "data/maps/NewBarkTown_Lab/scripts.pory"

# 967 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogBagFull:
# 968 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh! There's no room\n"
# 969 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in your Bag right now.\p"
# 970 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Make some space and come back.\n"
# 971 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll keep it safe for you!$"
# 972 "data/maps/NewBarkTown_Lab/scripts.pory"

# 973 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogExplainEviolite:
# 974 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That's an Eviolite.\p"
# 975 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Have a Pokémon that can still\n"
# 976 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "evolve hold it. It will boost\l"
# 977 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "its Defense and Sp. Def.\p"
# 978 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A little extra protection\n"
# 979 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "while it's growing!\p"
# 980 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can give it to whichever\n"
# 981 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "partner needs it most.$"
# 982 "data/maps/NewBarkTown_Lab/scripts.pory"

# 983 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogFarewell:
# 984 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If you notice anything unusual,\n"
# 985 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "you have my number.\p"
# 986 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now, where was that notebook...?\n"
# 987 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah! Under the first one.\p"
# 988 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take care, {PLAYER}.\n"
# 989 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Both of you!$"
# 990 "data/maps/NewBarkTown_Lab/scripts.pory"

# 991 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmCallYou:
# 992 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, I'll call you if\n"
# 993 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "anything comes up.$"
# 994 "data/maps/NewBarkTown_Lab/scripts.pory"

# 995 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAfterTheft:
# 996 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 997 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 998 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 999 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 1000 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1001 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall1:
# 1002 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hi, {PLAYER}!\p"
# 1003 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks to you, my research is\n"
# 1004 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going great!\p"
# 1005 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take this as a token of my\n"
# 1006 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "appreciation.$"
# 1007 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1008 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall2:
# 1009 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Master Ball is the best!\p"
# 1010 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the ultimate Ball! It'll\n"
# 1011 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "catch any Pokémon without fail.\p"
# 1012 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's given only to recognized\n"
# 1013 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon researchers.\p"
# 1014 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I think you can make much better\n"
# 1015 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "use of it than I can, {PLAYER}!$"
# 1016 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1017 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoGirls:
# 1018 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "By the way...\n"
# 1019 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A group of beautiful Kimono\l"
# 1020 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls were looking for you.\p"
# 1021 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They told me they are\n"
# 1022 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "waiting for you at the\l"
# 1023 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ecruteak Dance Theater.\p"
# 1024 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I know you've gone through many\n"
# 1025 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "things since that Egg got you\l"
# 1026 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "involved in all this...\p"
# 1027 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I hope you'll carry through it.$"
# 1028 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1029 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissedSurf:
# 1030 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: Oh, and a gentleman\n"
# 1031 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from the Dance Theater left this\l"
# 1032 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here for you.$"
# 1033 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1034 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoWaiting:
# 1035 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: The Kimono\n"
# 1036 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls are waiting for you at\l"
# 1037 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Ecruteak Dance Theater.$"
# 1038 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1039 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_League:
# 1040 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: Hahaha...\n"
# 1041 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Good job!\p"
# 1042 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That rare Egg has brought you\n"
# 1043 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a lot of trouble, huh?\p"
# 1044 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Kimono Girls said something\n"
# 1045 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about me?\p"
# 1046 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have nothing to do with it.\p"
# 1047 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You made your decision and went\n"
# 1048 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "through with it.\p"
# 1049 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Having done so much, you should\n"
# 1050 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "be able to face the League now!\p"
# 1051 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should head for Indigo\n"
# 1052 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Plateau!\p"
# 1053 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Do you know how to get there?\n"
# 1054 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Follow Route 27 to Route 26.\p"
# 1055 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Once there, go straight north!$"
# 1056 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1057 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1058 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket1:
# 1059 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\p"
# 1060 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I called because I have\n"
# 1061 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "something for you.\p"
# 1062 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "See? It's an S.S.Ticket.\p"
# 1063 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can catch Pokémon in\n"
# 1064 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Sevii.$"
# 1065 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1066 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket2:
# 1067 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The ship departs from Olivine\n"
# 1068 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "City.\p"
# 1069 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But you knew that already,\n"
# 1070 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}.\p"
# 1071 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "After all, you've traveled all\n"
# 1072 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "over with your Pokémon.$"
# 1073 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1074 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_LabMonEgg:
# 1075 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the Pokémon Egg being\n"
# 1076 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "studied by Prof. Elm.$"
# 1077 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1078 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGivePotion:
# 1079 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, I want you to have\n"
# 1080 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "this for your errand.$"
# 1081 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1082 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAlwaysBusy:
# 1083 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There are only three of us, so\n"
# 1084 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "we're always busy.$"
# 1085 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1086 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideSave:
# 1087 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Don't forget to save your game\n"
# 1088 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "regularly!\p"
# 1089 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Press the Start button, then\n"
# 1090 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Save the game!$"
# 1091 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1092 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideTheftTestimony:
# 1093 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There was a loud noise\n"
# 1094 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "outside…\p"
# 1095 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When we went to look,\n"
# 1096 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "someone stole a Pokémon.\p"
# 1097 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's unbelievable that anyone\n"
# 1098 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "would do that!\p"
# 1099 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 1100 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 1101 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 1102 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 1103 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1104 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGiveBalls:
# 1105 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 1106 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use these on your Pokédex\n"
# 1107 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "quest!$"
# 1108 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1109 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ExplainDexnav:
# 1110 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "We've also sent a Dexnav\n"
# 1111 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "application to your Pokégear!\p"
# 1112 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use it to catch lots of Pokémon!$"
# 1113 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1114 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideExplainBalls:
# 1115 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To add to your Pokédex, you\n"
# 1116 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "have to catch Pokémon.\p"
# 1117 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Throw Poké Balls at wild\n"
# 1118 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon to get them.$"
# 1119 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1120 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer1:
# 1121 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I heard a Pokémon was stolen\n"
# 1122 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here…\p"
# 1123 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I was just getting some\n"
# 1124 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "information from Prof. Elm.\p"
# 1125 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Apparently, it was a young\n"
# 1126 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "male with long, red hair…\p"
# 1127 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What?\p"
# 1128 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You battled a trainer like\n"
# 1129 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that?\p"
# 1130 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Did you happen to get his\n"
# 1131 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "name?$"
# 1132 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1133 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer2:
# 1134 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So Silver was his name.\p"
# 1135 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1136 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1137 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1138 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer3:
# 1139 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So {RIVAL} was his name.\p"
# 1140 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1141 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1142 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1143 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_OfficerNo:
# 1144 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Surely you got his name?!$"
# 1145 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1146 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Elm_CallMe:
# 1147 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah, {PLAYER}!\p"
# 1148 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "How's your Pokédex coming along?\n"
# 1149 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm busy now, but call me sometime\l"
# 1150 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and I can check your progress!$"

NewBarkTown_Lab_GiveStarterMega::
# 1154 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_0
# 1158 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_BONDSTONE, 1
# 1159 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_1
	return


NewBarkTown_Lab_EventScript_ElmPostgameHint::
# 1166 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0
# 1175 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1
# 1177 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1178 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1179 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1180 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1181 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1182 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1183 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 1184 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1185 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2
# 1191 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
# 1192 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_VICTORYROAD_RIVAL
# 1193 "data/maps/NewBarkTown_Lab/scripts.pory"
	checkplayergender
# 1194 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_Lab_EventScript_ElmPostgameHint_2
# 1203 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4
NewBarkTown_Lab_EventScript_ElmPostgameHint_1:
# 1211 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5
# 1213 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MTSILVER_GUARD
# 1214 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALLOW_SOUTH_JOHTO_PASS
# 1215 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 1216 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 11
# 1217 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ElmPostgameHint_2:
# 1195 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3
	goto NewBarkTown_Lab_EventScript_ElmPostgameHint_1


ElmIntro::
# 1222 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox ElmIntro_Text_0, MSGBOX_YESNO
	return


NewBarkTown_Lab_EventScript_ArtifactOfChaos::
# 1248 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 1249 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_ALL_INNATES_UNLOCKED, NewBarkTown_Lab_EventScript_ArtifactOfChaos_2
# 1273 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4
# 1278 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5
# 1284 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6, MSGBOX_YESNO
# 1290 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_8
# 1303 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8
NewBarkTown_Lab_EventScript_ArtifactOfChaos_1:
# 1307 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 1308 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ArtifactOfChaos_2:
# 1250 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0
# 1254 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1, MSGBOX_YESNO
# 1255 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_5
# 1269 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_5:
# 1256 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_OFF
# 1257 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1258 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_ALL_INNATES_UNLOCKED
# 1259 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_NEWBARKTOWN_LABSTATE, 11
	goto_if_lt NewBarkTown_Lab_EventScript_ArtifactOfChaos_12
# 1262 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
NewBarkTown_Lab_EventScript_ArtifactOfChaos_11:
# 1264 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_8:
# 1291 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_SWITCH
# 1292 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1293 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALL_INNATES_UNLOCKED
# 1294 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_REPLAY_NO_INNATES
# 1295 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_12:
# 1260 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_POSTGAME_FEATURES
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_11


NewBarkTown_Lab_GiveStarterMega_Text_0:
# 1154 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, and you got a Mega Ring from \n"
	.string "Prof. Oak?\l"
	.string "Then I think you are ready to handle\l"
	.string "this.$"

NewBarkTown_Lab_GiveStarterMega_Text_1:
# 1159 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's a special Mega Stone, specifically\n"
	.string "for your starter Pokémon. I expect \l"
	.string "great things from you, {PLAYER}!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0:
# 1166 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\n"
	.string "I called because I heard that the \l"
	.string "Battle Tower is open! \p"
	.string "I hear strong trainers\n"
	.string "are gathering in there!\p"
	.string "You can get there from Route 40\n"
	.string "near Olivine City.$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1:
# 1175 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But first, let me upgrade your Pokédex\n"
	.string "with a new feature!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2:
# 1185 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can view abilities of the\n"
	.string "opposing Pokémon with the L-button\l"
	.string "in battle! \p"
	.string "That will surely be handy as the\n"
	.string "battles get tougher!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3:
# 1195 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Crystal went to train\n"
	.string "in Mt. Silver. \p"
	.string "She looked really tired\n"
	.string "the last time I saw her though... \p"
	.string "Could you check on her at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4:
# 1203 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Gold went to train\n"
	.string "in Mt. Silver. \p"
	.string "He looked really tired\n"
	.string "the last time I saw him though...\p"
	.string "Could you check on him at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5:
# 1211 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I asked from the League to let you\n"
	.string "pass since you've the new Champion.$"

ElmIntro_Text_0:
# 1222 "data/maps/NewBarkTown_Lab/scripts.pory"
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
# 1250 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact of Chaos is humming.\p"
	.string "All innate abilities are currently\n"
	.string "active.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1:
# 1254 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Deactivate the Artifact?$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2:
# 1264 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The glow from the Artifact fades.\p"
	.string "Innate abilities will now unlock at\n"
	.string "their intended levels again.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3:
# 1269 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact continues humming.\n"
	.string "Hope Elm hasn't noticed yet!$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4:
# 1273 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Amidst the books is Elm's very own\n"
	.string "Artifact of Chaos.\p"
	.string "There's a small label on the side:\n"
	.string "DO NOT TOUCH.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5:
# 1278 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Important! Activating this Artifact\n"
	.string "unlocks all innate abilities,\l"
	.string "regardless of a Pokémon's level.\p"
	.string "It also lets you inspect enemy\n"
	.string "innates in battle by pressing L.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6:
# 1284 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "This is not the intended way to play\n"
	.string "the game and will not be balanced\l"
	.string "at all.\p"
	.string "If you understand and still wish to\n"
	.string "activate it, choose Yes.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7:
# 1295 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} tapped the Artifact.\p"
	.string "Game balance quietly\n"
	.string "leaves the building.\p"
	.string "All innates are now active. Press L\n"
	.string "in battle to inspect enemy innates.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8:
# 1303 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} left the Artifact alone.\n"
	.string "Chaos shall not win today.$"
