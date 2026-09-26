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
@ Rift Mission 4 (.claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md, section 3.6).
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
	call NewBarkTown_Lab_ApplyShelterMomVisibility
# 38 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_TEMP_1
# 39 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_Lab_ElmStays
# 40 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_TEMP_1
# 41 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_ElmStays::
# 42 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 43 "data/maps/NewBarkTown_Lab/scripts.pory"

# 44 "data/maps/NewBarkTown_Lab/scripts.pory"
@ Rift Mission 4, New Bark V2 script (section 19): once Mom has crossed into the
# 45 "data/maps/NewBarkTown_Lab/scripts.pory"
@ shelter (FLAG_NEWBARK_UB_ENGAGED), she stays in here until the street is
# 46 "data/maps/NewBarkTown_Lab/scripts.pory"
@ clear, and she is where the player heals before another attempt. She is NOT
# 47 "data/maps/NewBarkTown_Lab/scripts.pory"
@ in the street at the same time: NewBarkTown's ApplyUBVisibility hides the
# 48 "data/maps/NewBarkTown_Lab/scripts.pory"
@ street Mom on the same flag. Before the crossing she is out on the road, and
# 49 "data/maps/NewBarkTown_Lab/scripts.pory"
@ after the mission she is back home (PlayersHouse_1F).
# 50 "data/maps/NewBarkTown_Lab/scripts.pory"
@   visible <=> FLAG_EVENT_ULTRABEAST_NEWBARK AND FLAG_NEWBARK_UB_ENGAGED
# 51 "data/maps/NewBarkTown_Lab/scripts.pory"
@ FLAG_TEMP_2 is a per-visit cache; the default after a load is visible, so the
# 52 "data/maps/NewBarkTown_Lab/scripts.pory"
@ setflag comes first and only the one true case clears it.
# 53 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_ApplyShelterMomVisibility::
# 54 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_TEMP_2
# 55 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_Lab_ShelterMomDone
# 56 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_unset FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_Lab_ShelterMomDone
# 57 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_TEMP_2
# 58 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_ShelterMomDone::
# 59 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 60 "data/maps/NewBarkTown_Lab/scripts.pory"

# 61 "data/maps/NewBarkTown_Lab/scripts.pory"
@ Her usual heal, in the shelter. One box before, the standard heal after.
# 62 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ShelterMom::
# 63 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 64 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 65 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShelterMomHeal, MSGBOX_DEFAULT
# 66 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 67 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 68 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject LOCALID_NEWBARK_LAB_MOM, DIR_EAST
# 69 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 70 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 71 "data/maps/NewBarkTown_Lab/scripts.pory"

# 72 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShelterMomHeal:
# 73 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{SPEAKER NAME_MOM}Let your Pokémon rest a\n"
# 74 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "moment. I'll take care of them.$"
# 75 "data/maps/NewBarkTown_Lab/scripts.pory"

# 76 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAtComputer::
# 77 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxyperm LOCALID_ELM, 3, 2
# 78 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
# 79 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 80 "data/maps/NewBarkTown_Lab/scripts.pory"

# 81 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
# 82 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 83 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
# 84 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 85 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 86 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 87 "data/maps/NewBarkTown_Lab/scripts.pory"

# 88 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLabRight::
# 89 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 90 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
# 91 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 92 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
# 93 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 94 "data/maps/NewBarkTown_Lab/scripts.pory"

# 95 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerStartLab::
# 96 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 97 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
# 98 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 99 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmIntro
# 100 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 101 "data/maps/NewBarkTown_Lab/scripts.pory"

# 102 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide1::
# 103 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 104 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 105 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
# 106 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 107 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 108 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 109 "data/maps/NewBarkTown_Lab/scripts.pory"

# 110 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2::
# 111 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 112 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 113 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
# 114 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
# 115 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 116 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 117 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 118 "data/maps/NewBarkTown_Lab/scripts.pory"

# 119 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_EventScript_Aide2Testimony::
# 120 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
# 121 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 122 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 123 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 124 "data/maps/NewBarkTown_Lab/scripts.pory"

# 125 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm::
# 126 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 127 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 128 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, NewBarkTown_Lab_EventScript_ElmAfterGladion
# 129 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_VIOLET_CITY_STATE, 4, NewBarkTown_Lab_EventScript_ElmGladionIsWaiting
# 130 "data/maps/NewBarkTown_Lab/scripts.pory"

# 131 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAfterGladion::
# 132 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
# 133 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
# 134 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
# 135 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmPostgameHint
# 136 "data/maps/NewBarkTown_Lab/scripts.pory"

# 137 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_CallMe
# 138 "data/maps/NewBarkTown_Lab/scripts.pory"
	call_if_unset FLAG_SHOWN_ELM_COSMOG, NewBarkTown_Lab_EventScript_Elm_Check_Cosmog
# 139 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
# 140 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5
# 141 "data/maps/NewBarkTown_Lab/scripts.pory"

# 142 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
# 143 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
# 144 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
# 145 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
# 146 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 147 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 148 "data/maps/NewBarkTown_Lab/scripts.pory"

# 149 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmGladionIsWaiting::
# 150 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGladionIsWaiting, MSGBOX_DEFAULT
# 151 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 152 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 153 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 154 "data/maps/NewBarkTown_Lab/scripts.pory"

# 155 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGladionIsWaiting:
# 156 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 157 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What are you doing here?\p"
# 158 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gladion is waiting for you at\n"
# 159 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Violet City's Pokémon Center.\p"
# 160 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He has the Egg I wanted you to\n"
# 161 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "look after.$"
# 162 "data/maps/NewBarkTown_Lab/scripts.pory"

# 163 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmIntro::
# 164 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 165 "data/maps/NewBarkTown_Lab/scripts.pory"
	call ElmIntro
# 166 "data/maps/NewBarkTown_Lab/scripts.pory"
	@msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
# 167 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 168 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 169 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 170 "data/maps/NewBarkTown_Lab/scripts.pory"

# 171 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmRefused::
# 172 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 173 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
# 174 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
# 175 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
# 176 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 177 "data/maps/NewBarkTown_Lab/scripts.pory"

# 178 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmAccepted::
# 179 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 180 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
# 181 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
# 182 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 183 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_LOGIN
# 184 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 185 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 186 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
# 187 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 188 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
# 189 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
# 190 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement LOCALID_ELM
# 191 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 192 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
# 193 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 194 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 195 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
# 196 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 197 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 198 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 199 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 30
# 200 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 201 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
# 202 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
# 203 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 204 "data/maps/NewBarkTown_Lab/scripts.pory"

# 205 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmChoosePokemon::
# 206 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 207 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Right
# 208 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 209 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 210 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
# 211 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 212 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 213 "data/maps/NewBarkTown_Lab/scripts.pory"
    applymovement LOCALID_ELM, NewBarkTownLab_Movement_Elm_Down
# 214 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 215 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
# 216 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 217 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 218 "data/maps/NewBarkTown_Lab/scripts.pory"

# 219 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
# 220 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 221 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 222 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
# 223 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 224 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 225 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
# 226 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 227 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 228 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 229 "data/maps/NewBarkTown_Lab/scripts.pory"

# 230 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ShouldntTouch::
# 231 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 232 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 233 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 234 "data/maps/NewBarkTown_Lab/scripts.pory"

# 235 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_hideStarterCase::
# 236 "data/maps/NewBarkTown_Lab/scripts.pory"
    setflag FLAG_HIDE_STARTER_CASE
# 237 "data/maps/NewBarkTown_Lab/scripts.pory"
    return
# 238 "data/maps/NewBarkTown_Lab/scripts.pory"

# 239 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase::
# 240 "data/maps/NewBarkTown_Lab/scripts.pory"
    lock
# 241 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_SOUTH, NewBarkTown_Lab_EventScript_StarterCaseWrongSide
# 242 "data/maps/NewBarkTown_Lab/scripts.pory"
	callnative MigrateNationalPokedex
# 243 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
# 244 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_StarterCase_Choice
# 245 "data/maps/NewBarkTown_Lab/scripts.pory"
    msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
# 246 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 247 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 248 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 249 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCaseWrongSide::
# 250 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_StarterCaseWrongSide, MSGBOX_DEFAULT
# 251 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 252 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 253 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 254 "data/maps/NewBarkTown_Lab/scripts.pory"

# 255 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_StarterCase_Choice::
# 256 "data/maps/NewBarkTown_Lab/scripts.pory"
   callnative StartNewPokeballCaseUI
# 257 "data/maps/NewBarkTown_Lab/scripts.pory"
   waitstate
# 258 "data/maps/NewBarkTown_Lab/scripts.pory"
   goto NewBarkTown_Lab_EventScript_ChoseStarter
# 259 "data/maps/NewBarkTown_Lab/scripts.pory"

# 260 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter::
# 261 "data/maps/NewBarkTown_Lab/scripts.pory"
	showmonpic VAR_PLAYER_STARTER_SPECIES, 10, 3
# 262 "data/maps/NewBarkTown_Lab/scripts.pory"
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
# 263 "data/maps/NewBarkTown_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_PLAYER_STARTER_SPECIES
# 264 "data/maps/NewBarkTown_Lab/scripts.pory"
	message NewBarkTown_Lab_Text_ReceivedStarter
# 265 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE 1
# 266 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitfanfare
# 267 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 268 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 269 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_StepBackFromStarter
# 270 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 271 "data/maps/NewBarkTown_Lab/scripts.pory"
	updatefollowingmon
# 272 "data/maps/NewBarkTown_Lab/scripts.pory"
	setobjectxy OBJ_EVENT_ID_FOLLOWER, 9, 5
# 273 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterLeavesBall
# 274 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_BALL_OPEN
# 275 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 276 "data/maps/NewBarkTown_Lab/scripts.pory"
	playmoncry VAR_PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
# 277 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_LEDGE
# 278 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_Lab_Movement_StarterGreetsPlayer
# 279 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement OBJ_EVENT_ID_FOLLOWER
# 280 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmoncry
# 281 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 45
# 282 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 283 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
# 284 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 285 "data/maps/NewBarkTown_Lab/scripts.pory"
    closemessage
# 286 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 287 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 288 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 289 "data/maps/NewBarkTown_Lab/scripts.pory"

# 290 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ChoseStarter2::
# 291 "data/maps/NewBarkTown_Lab/scripts.pory"
    moveobjecttocoords OBJ_EVENT_ID_PLAYER, 6, 4, DIR_NORTH
# 292 "data/maps/NewBarkTown_Lab/scripts.pory"
    waitmovement 0
# 293 "data/maps/NewBarkTown_Lab/scripts.pory"
    @applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
# 294 "data/maps/NewBarkTown_Lab/scripts.pory"
    @waitmovement 0
# 295 "data/maps/NewBarkTown_Lab/scripts.pory"
    clearflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 296 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_RIVAL_STATE, 2
# 297 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_STARTER_PICKING_STATE, 2
# 298 "data/maps/NewBarkTown_Lab/scripts.pory"
    goto NewBarkTown_Lab_EventScript_MrPokemon
# 299 "data/maps/NewBarkTown_Lab/scripts.pory"

# 300 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_DeclinedStarter::
# 301 "data/maps/NewBarkTown_Lab/scripts.pory"
	hidemonpic
# 302 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
# 303 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 304 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 305 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 306 "data/maps/NewBarkTown_Lab/scripts.pory"

# 307 "data/maps/NewBarkTown_Lab/scripts.pory"

# 308 "data/maps/NewBarkTown_Lab/scripts.pory"

# 309 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_NicknameStarter::
# 310 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_0x8004, 0
# 311 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 312 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 313 "data/maps/NewBarkTown_Lab/scripts.pory"

# 314 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemon::
# 315 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
# 316 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 317 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 318 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 319 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 320 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 321 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 322 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 323 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
# 324 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
# 325 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 326 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 327 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 328 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 329 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 330 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 331 "data/maps/NewBarkTown_Lab/scripts.pory"

# 332 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
# 333 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
# 334 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 335 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_FIRST_BALLS
# 336 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_RECEIVED_EXP_SHARE
# 337 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 3
# 338 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 339 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 340 "data/maps/NewBarkTown_Lab/scripts.pory"

# 341 "data/maps/NewBarkTown_Lab/scripts.pory"
CopNewBarkTown_Lab_EventScript_ElmState2::
# 342 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
# 343 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
# 344 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
# 345 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 346 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 347 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 348 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 349 "data/maps/NewBarkTown_Lab/scripts.pory"

# 350 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine1::
# 351 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 352 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
# 353 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 354 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 355 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 356 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 357 "data/maps/NewBarkTown_Lab/scripts.pory"

# 358 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_HealingMachine2::
# 359 "data/maps/NewBarkTown_Lab/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 360 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 361 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 362 "data/maps/NewBarkTown_Lab/scripts.pory"

# 363 "data/maps/NewBarkTown_Lab/scripts.pory"

# 364 "data/maps/NewBarkTown_Lab/scripts.pory"

# 365 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
# 366 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 367 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 368 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 369 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 370 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
# 371 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 372 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POTION
# 373 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 374 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
# 375 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 376 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 377 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 378 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 379 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 380 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 381 "data/maps/NewBarkTown_Lab/scripts.pory"

# 382 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceEpisode::
# 383 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 384 "data/maps/NewBarkTown_Lab/scripts.pory"
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
# 385 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_hideStarterCase
# 386 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
# 387 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 388 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_LAB_POLICEMAN
# 389 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject LOCALID_COP DIR_WEST
# 390 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
# 391 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceNameRival
# 392 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceYes
# 393 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 394 "data/maps/NewBarkTown_Lab/scripts.pory"

# 395 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNo::
# 396 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
# 397 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
# 398 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
# 399 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 400 "data/maps/NewBarkTown_Lab/scripts.pory"

# 401 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival::
# 402 "data/maps/NewBarkTown_Lab/scripts.pory"
	special NameRival
# 403 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitstate
# 404 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_NAMED_SILVER
# 405 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 406 "data/maps/NewBarkTown_Lab/scripts.pory"

# 407 "data/maps/NewBarkTown_Lab/scripts.pory"

# 408 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceNameRival2::
# 409 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 410 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 411 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes3
# 412 "data/maps/NewBarkTown_Lab/scripts.pory"

# 413 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes::
# 414 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
# 415 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 416 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_PoliceYes2
# 417 "data/maps/NewBarkTown_Lab/scripts.pory"

# 418 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_PoliceYes3::
# 419 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Officer3, MSGBOX_DEFAULT
# 420 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
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
NewBarkTown_Lab_EventScript_PoliceYes2::
# 454 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
# 455 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 456 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeobject LOCALID_COP
# 457 "data/maps/NewBarkTown_Lab/scripts.pory"

# 458 "data/maps/NewBarkTown_Lab/scripts.pory"
	@ setobjectxyperm LOCALID_COP, 25, 4
# 459 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
# 460 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 461 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 462 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
# 463 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 464 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
# 465 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 466 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
# 467 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 468 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 469 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
# 470 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 471 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 472 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
# 473 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 474 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 475 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
# 476 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 477 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
# 478 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 479 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 480 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_MOMS_FRIEND2
# 481 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 482 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_EXP_SHARE
# 483 "data/maps/NewBarkTown_Lab/scripts.pory"
	removeitem ITEM_MYSTERY_EGG
# 484 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 485 "data/maps/NewBarkTown_Lab/scripts.pory"

# 486 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmState5::
# 487 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 488 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 489 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
# 490 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 491 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
# 492 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 493 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 494 "data/maps/NewBarkTown_Lab/scripts.pory"

# 495 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmMasterBall::
# 496 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 497 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 498 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
# 499 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_MASTER_BALL
# 500 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
# 501 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 502 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 20
# 503 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 504 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
# 505 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 60
# 506 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
# 507 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_GiveStarterMega
# 508 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_GiveMissedSurf
# 509 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 510 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
# 511 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
# 512 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_SILVER
# 513 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
# 514 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
# 515 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 516 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 517 "data/maps/NewBarkTown_Lab/scripts.pory"

# 518 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmKimono::
# 519 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 520 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 521 "data/maps/NewBarkTown_Lab/scripts.pory"
	call NewBarkTown_Lab_EventScript_GiveMissedSurf
# 522 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
# 523 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 524 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 525 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 526 "data/maps/NewBarkTown_Lab/scripts.pory"

# 527 "data/maps/NewBarkTown_Lab/scripts.pory"
@ HM Surf normally comes from the man in the Ecruteak Dance Theater after
# 528 "data/maps/NewBarkTown_Lab/scripts.pory"
@ the Rocket Grunt is beaten. The Master Ball scene above hides him
# 529 "data/maps/NewBarkTown_Lab/scripts.pory"
@ (FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS) and jumps the theater to state 4,
# 530 "data/maps/NewBarkTown_Lab/scripts.pory"
@ so a player who skipped that arc would lose Surf for good. Elm hands it
# 531 "data/maps/NewBarkTown_Lab/scripts.pory"
@ over instead. Also called from ElmKimono for saves already past the scene.
# 532 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_GiveMissedSurf::
# 533 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_SURF, NewBarkTown_Lab_EventScript_GiveMissedSurfEnd
# 534 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmMissedSurf, MSGBOX_DEFAULT
# 535 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_HM_SURF
# 536 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_GiveMissedSurfEnd
# 537 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_HM_SURF
# 538 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_GiveMissedSurfEnd::
# 539 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 540 "data/maps/NewBarkTown_Lab/scripts.pory"

# 541 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmLeague::
# 542 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 543 "data/maps/NewBarkTown_Lab/scripts.pory"
	faceplayer
# 544 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
# 545 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 546 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 547 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 548 "data/maps/NewBarkTown_Lab/scripts.pory"

# 549 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_ElmSSTicket::
# 550 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
# 551 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_SS_TICKET
# 552 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
# 553 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 554 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
# 555 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 556 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
# 557 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 558 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 559 "data/maps/NewBarkTown_Lab/scripts.pory"

# 560 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
# 561 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 562 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
# 563 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 564 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 565 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
# 566 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 567 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_POKE_BALL, 10
# 568 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 569 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_RECEIVED_FIRST_BALLS
# 570 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
# 571 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ExplainDexnav, MSGBOX_DEFAULT
# 572 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 573 "data/maps/NewBarkTown_Lab/scripts.pory"
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
# 574 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmovement 0
# 575 "data/maps/NewBarkTown_Lab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 576 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 577 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 578 "data/maps/NewBarkTown_Lab/scripts.pory"

# 579 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
# 580 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
# 581 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 582 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 583 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 584 "data/maps/NewBarkTown_Lab/scripts.pory"

# 585 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Check_Cosmog::
# 586 "data/maps/NewBarkTown_Lab/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 587 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen
# 588 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 589 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_SOLGALEO, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 590 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_LUNALA, NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen
# 591 "data/maps/NewBarkTown_Lab/scripts.pory"
	return
# 592 "data/maps/NewBarkTown_Lab/scripts.pory"

# 593 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Seen::
# 594 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 595 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 596 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 597 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogObservation, MSGBOX_DEFAULT
# 598 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 599 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward
# 600 "data/maps/NewBarkTown_Lab/scripts.pory"

# 601 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Evolved_Seen::
# 602 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 603 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogVisitIntro, MSGBOX_DEFAULT
# 604 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 605 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogEvolvedObservation, MSGBOX_DEFAULT
# 606 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 607 "data/maps/NewBarkTown_Lab/scripts.pory"

# 608 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_Reward::
# 609 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogResearchNotes, MSGBOX_DEFAULT
# 610 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 611 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogCare, MSGBOX_DEFAULT
# 612 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 613 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogOfferEviolite, MSGBOX_DEFAULT
# 614 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 615 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 616 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 617 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_EVIOLITE
# 618 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull
# 619 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_SHOWN_ELM_COSMOG
# 620 "data/maps/NewBarkTown_Lab/scripts.pory"
	createfieldmugshot MUGSHOT_ELM
# 621 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogExplainEviolite, MSGBOX_DEFAULT
# 622 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitmessage
# 623 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogFarewell, MSGBOX_DEFAULT
# 624 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 625 "data/maps/NewBarkTown_Lab/scripts.pory"
	removefieldmugshot
# 626 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 627 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 628 "data/maps/NewBarkTown_Lab/scripts.pory"

# 629 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_Cosmog_BagFull::
# 630 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_CosmogBagFull, MSGBOX_DEFAULT
# 631 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 632 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 633 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 634 "data/maps/NewBarkTown_Lab/scripts.pory"

# 635 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_EventScript_Elm_CallMe::
# 636 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
# 637 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 638 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
# 639 "data/maps/NewBarkTown_Lab/scripts.pory"
	end
# 640 "data/maps/NewBarkTown_Lab/scripts.pory"

# 641 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkRight:
# 642 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 643 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 644 "data/maps/NewBarkTown_Lab/scripts.pory"

# 645 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_WalkLeft:
# 646 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 647 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 648 "data/maps/NewBarkTown_Lab/scripts.pory"

# 649 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StepBackFromStarter:
# 650 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 651 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 652 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 653 "data/maps/NewBarkTown_Lab/scripts.pory"

# 654 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterLeavesBall:
# 655 "data/maps/NewBarkTown_Lab/scripts.pory"
	exit_pokeball
# 656 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 657 "data/maps/NewBarkTown_Lab/scripts.pory"
	set_visible
# 658 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 659 "data/maps/NewBarkTown_Lab/scripts.pory"

# 660 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_StarterGreetsPlayer:
# 661 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 662 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay_4
# 663 "data/maps/NewBarkTown_Lab/scripts.pory"
	jump_in_place_down
# 664 "data/maps/NewBarkTown_Lab/scripts.pory"
	emote_heart
# 665 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_player
# 666 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 667 "data/maps/NewBarkTown_Lab/scripts.pory"

# 668 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_LabMovement_WalkToElm:
# 669 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 670 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 671 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 672 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 673 "data/maps/NewBarkTown_Lab/scripts.pory"

# 674 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnPlayer:
# 675 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 676 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 677 "data/maps/NewBarkTown_Lab/scripts.pory"

# 678 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmail:
# 679 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 680 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 681 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 682 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 683 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 684 "data/maps/NewBarkTown_Lab/scripts.pory"

# 685 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CheckEmailSlow:
# 686 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 687 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 688 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 689 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 690 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 691 "data/maps/NewBarkTown_Lab/scripts.pory"

# 692 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_GotoComputerSafe:
# 693 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 694 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 695 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 696 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 697 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 698 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 699 "data/maps/NewBarkTown_Lab/scripts.pory"

# 700 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ReturnFromEmail:
# 701 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 702 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 703 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 704 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_right
# 705 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 706 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 707 "data/maps/NewBarkTown_Lab/scripts.pory"

# 708 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Left:
# 709 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_left
# 710 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 711 "data/maps/NewBarkTown_Lab/scripts.pory"

# 712 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Look_Up:
# 713 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 714 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 715 "data/maps/NewBarkTown_Lab/scripts.pory"

# 716 "data/maps/NewBarkTown_Lab/scripts.pory"

# 717 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
# 718 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 719 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 720 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 721 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 722 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 723 "data/maps/NewBarkTown_Lab/scripts.pory"

# 724 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_Aide1LeavePlayer:
# 725 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 726 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_left
# 727 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 728 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_up
# 729 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_down
# 730 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 731 "data/maps/NewBarkTown_Lab/scripts.pory"

# 732 "data/maps/NewBarkTown_Lab/scripts.pory"
NeBarkTownLab_Movement_PlayerWalkToCop:
# 733 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 734 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 735 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 736 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 737 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 738 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 739 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 740 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_left
# 741 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 742 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_right
# 743 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 744 "data/maps/NewBarkTown_Lab/scripts.pory"

# 745 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Right:
# 746 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_right
# 747 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 748 "data/maps/NewBarkTown_Lab/scripts.pory"

# 749 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTownLab_Movement_Elm_Down:
# 750 "data/maps/NewBarkTown_Lab/scripts.pory"
    face_down
# 751 "data/maps/NewBarkTown_Lab/scripts.pory"
    step_end
# 752 "data/maps/NewBarkTown_Lab/scripts.pory"

# 753 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_CopLeaves:
# 754 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 755 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 756 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 757 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 758 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_down
# 759 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 760 "data/maps/NewBarkTown_Lab/scripts.pory"

# 761 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_PlayerStepsToElm:
# 762 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_right
# 763 "data/maps/NewBarkTown_Lab/scripts.pory"
	face_up
# 764 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 765 "data/maps/NewBarkTown_Lab/scripts.pory"

# 766 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepBack:
# 767 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock_facing_direction
# 768 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_up
# 769 "data/maps/NewBarkTown_Lab/scripts.pory"
	unlock_facing_direction
# 770 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 771 "data/maps/NewBarkTown_Lab/scripts.pory"

# 772 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Movement_ElmStepForward:
# 773 "data/maps/NewBarkTown_Lab/scripts.pory"
	walk_fast_down
# 774 "data/maps/NewBarkTown_Lab/scripts.pory"
	step_end
# 775 "data/maps/NewBarkTown_Lab/scripts.pory"

# 776 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ShouldntTouch:
# 777 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Probably shouldn't touch!$"
# 778 "data/maps/NewBarkTown_Lab/scripts.pory"

# 779 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_StarterCaseWrongSide:
# 780 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oops, the case does not open\n"
# 781 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from this side!$"
# 782 "data/maps/NewBarkTown_Lab/scripts.pory"

# 783 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAccepted:
# 784 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks, {PLAYER}!\n"
# 785 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're a great help!$"
# 786 "data/maps/NewBarkTown_Lab/scripts.pory"

# 787 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmRefused:
# 788 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Please, I need your\n"
# 789 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "help!$"
# 790 "data/maps/NewBarkTown_Lab/scripts.pory"

# 791 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmResearchAmbitions:
# 792 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When I announce my findings,\n"
# 793 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm sure we'll delve deeper\p"
# 794 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "into the many mysteries of\n"
# 795 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon.\p"
# 796 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can count on it!$"
# 797 "data/maps/NewBarkTown_Lab/scripts.pory"

# 798 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGotAnEmail:
# 799 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, hey! I got an e-mail!\p"
# 800 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "… … … … … … … …\n"
# 801 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hm… Uh-huh…\p"
# 802 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Okay…$"
# 803 "data/maps/NewBarkTown_Lab/scripts.pory"

# 804 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
# 805 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That was Professor Kukui,\n"
# 806 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a researcher from Alola.\p"
# 807 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's visiting Johto to study\n"
# 808 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Alolan Pokémon spotted here.\p"
# 809 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A Day-Care couple gave him\n"
# 810 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "an unusual Egg.\p"
# 811 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He'd like me to examine it!\p"
# 812 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He's working from a house on\n"
# 813 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Route 30, north of Cherrygrove.\p"
# 814 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd go myself, but I can't\n"
# 815 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "leave the lab right now...\p"
# 816 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wait! I have an idea!\p"
# 817 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, could you pick up\n"
# 818 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg for me?$"
# 819 "data/maps/NewBarkTown_Lab/scripts.pory"

# 820 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmChooseAPokemon:
# 821 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I want you to raise one of\n"
# 822 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Pokémon contained in this case.\p"
# 823 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You'll be that Pokémon's\n"
# 824 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "first partner, {PLAYER}!\p"
# 825 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Go on. Pick one!$"
# 826 "data/maps/NewBarkTown_Lab/scripts.pory"

# 827 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWhereGoing:
# 828 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Wait! Where are you\n"
# 829 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going?$"
# 830 "data/maps/NewBarkTown_Lab/scripts.pory"

# 831 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseCyndaquil:
# 832 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: You'll take Cyndaquil,\n"
# 833 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the fire Pokémon?$"
# 834 "data/maps/NewBarkTown_Lab/scripts.pory"

# 835 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseTotodile:
# 836 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Do you want Totodile,\n"
# 837 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the water Pokémon?$"
# 838 "data/maps/NewBarkTown_Lab/scripts.pory"

# 839 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChooseChikorita:
# 840 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: So, you like Chikorita,\n"
# 841 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the grass Pokémon?$"
# 842 "data/maps/NewBarkTown_Lab/scripts.pory"

# 843 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_DidntChooseStarter:
# 844 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Think it over carefully.\p"
# 845 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Your partner is important.$"
# 846 "data/maps/NewBarkTown_Lab/scripts.pory"

# 847 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ChoseStarter:
# 848 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: I think that's a great\n"
# 849 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon too!$"
# 850 "data/maps/NewBarkTown_Lab/scripts.pory"

# 851 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ReceivedStarter:
# 852 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} received {STR_VAR_1}!$"
# 853 "data/maps/NewBarkTown_Lab/scripts.pory"

# 854 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Nickname:
# 855 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Would you like to give your\n"
# 856 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{STR_VAR_1} a nickname?$"
# 857 "data/maps/NewBarkTown_Lab/scripts.pory"

# 858 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections1:
# 859 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui is staying in a house\n"
# 860 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "on Route 30, just north of\l"
# 861 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Cherrygrove City.\p"
# 862 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Head west to Cherrygrove,\n"
# 863 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "then follow the road north.\p"
# 864 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You have my phone number,\n"
# 865 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "so call me if you need help!$"
# 866 "data/maps/NewBarkTown_Lab/scripts.pory"

# 867 "data/maps/NewBarkTown_Lab/scripts.pory"

# 868 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmLetYourMonBattle:
# 869 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears,\n"
# 870 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "let your Pokémon battle it!$"
# 871 "data/maps/NewBarkTown_Lab/scripts.pory"

# 872 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDirections2:
# 873 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If a wild Pokémon appears, let\n"
# 874 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "your Pokémon battle it!\p"
# 875 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If your Pokémon is hurt, you\n"
# 876 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "should heal it with the machine\l"
# 877 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to my right, or at the Pokémon Center.\p"
# 878 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm counting on you!$"
# 879 "data/maps/NewBarkTown_Lab/scripts.pory"

# 880 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_GotElmsNumber:
# 881 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} got Elm's phone\n"
# 882 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "number.$"
# 883 "data/maps/NewBarkTown_Lab/scripts.pory"

# 884 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
# 885 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui says familiar Pokémon\n"
# 886 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "can look quite different in Alola.\p"
# 887 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even their types can change!\n"
# 888 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd love to study how they adapt.$"
# 889 "data/maps/NewBarkTown_Lab/scripts.pory"

# 890 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmPokeBall:
# 891 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It contains Pokémon caught\n"
# 892 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "by Prof. Elm.$"
# 893 "data/maps/NewBarkTown_Lab/scripts.pory"

# 894 "data/maps/NewBarkTown_Lab/scripts.pory"
@THEFT================================================================================
# 895 "data/maps/NewBarkTown_Lab/scripts.pory"

# 896 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft1:
# 897 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, this is terrible…\p"
# 898 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, yes, what was Kukui's\n"
# 899 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "big discovery?$"
# 900 "data/maps/NewBarkTown_Lab/scripts.pory"

# 901 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft2:
# 902 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} handed the Mystery Egg\n"
# 903 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "to Prof. Elm.$"
# 904 "data/maps/NewBarkTown_Lab/scripts.pory"

# 905 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft3:
# 906 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: This?$"
# 907 "data/maps/NewBarkTown_Lab/scripts.pory"

# 908 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAfterTheft4:
# 909 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But… Is it a Pokémon Egg?\p"
# 910 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If it is, it is a great\n"
# 911 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "discovery!\p"
# 912 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: What?!?\p"
# 913 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Oak gave you a Pokédex?\p"
# 914 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, is that true?\n"
# 915 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Th-that's incredible!\p"
# 916 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He is superb at seeing the\n"
# 917 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "potential of people as trainers.\p"
# 918 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Wow, {PLAYER}. You may have what\n"
# 919 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it takes to become the Champion.\p"
# 920 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You seem to be getting on\n"
# 921 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "great with Pokémon too.\p"
# 922 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should take the Pokémon\n"
# 923 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Gym challenge.\p"
# 924 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The closest Gym would be the\n"
# 925 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "one in Violet City.\p"
# 926 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…{PLAYER}. The road to the\n"
# 927 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "championship will be a long one.\p"
# 928 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Before you leave, make sure\n"
# 929 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that you talk to your mom.$"
# 930 "data/maps/NewBarkTown_Lab/scripts.pory"

# 931 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmStudyingEgg:
# 932 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Don't give up!\n"
# 933 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll call if I learn anything\l"
# 934 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about that Egg!$"
# 935 "data/maps/NewBarkTown_Lab/scripts.pory"

# 936 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmAideHasEgg:
# 937 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}? Didn't you meet\n"
# 938 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my assistant?\p"
# 939 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He should have met you with\n"
# 940 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Egg at Violet City's\p"
# 941 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon Center.\p"
# 942 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You must have just missed him.\n"
# 943 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Try to catch him there.$"
# 944 "data/maps/NewBarkTown_Lab/scripts.pory"

# 945 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmWaitingEggHatch:
# 946 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hey, has that Egg changed\n"
# 947 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "any?$"
# 948 "data/maps/NewBarkTown_Lab/scripts.pory"

# 949 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmThoughtEggHatched:
# 950 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}? I thought the Egg\n"
# 951 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "hatched.\p"
# 952 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Where is the Pokémon?$"
# 953 "data/maps/NewBarkTown_Lab/scripts.pory"

# 954 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogVisitIntro:
# 955 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! You came back!\p"
# 956 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "And you brought the Pokémon\n"
# 957 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from Kukui's Egg?\p"
# 958 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me put these notes aside.\n"
# 959 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'd like a closer look!$"
# 960 "data/maps/NewBarkTown_Lab/scripts.pory"

# 961 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogObservation:
# 962 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "So this is Cosmog...\p"
# 963 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It looks as though a piece\n"
# 964 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of the night sky drifted inside!\p"
# 965 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To think it was tucked away\n"
# 966 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in that little Egg all along.\p"
# 967 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Hmm... Where did I put\n"
# 968 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "my other notebook?$"
# 969 "data/maps/NewBarkTown_Lab/scripts.pory"

# 970 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogEvolvedObservation:
# 971 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's already evolved?\n"
# 972 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have some catching up to do!\p"
# 973 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What was it like when\n"
# 974 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "it first came out of the Egg?\p"
# 975 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Even a small detail could help.\n"
# 976 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Let me find a fresh page!$"
# 977 "data/maps/NewBarkTown_Lab/scripts.pory"

# 978 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogResearchNotes:
# 979 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Kukui sent me one Egg,\n"
# 980 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and now I have a hundred questions.\p"
# 981 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll send him my observations.\n"
# 982 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "He may know where to start.\p"
# 983 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I suspect his reply will bring\n"
# 984 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a few more questions too!$"
# 985 "data/maps/NewBarkTown_Lab/scripts.pory"

# 986 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogCare:
# 987 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, listen to me rambling.\n"
# 988 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You're here for a visit!\p"
# 989 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thank you for taking care\n"
# 990 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "of this Pokémon, {PLAYER}.\p"
# 991 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You get to see things together\n"
# 992 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that I'd never see in this lab.$"
# 993 "data/maps/NewBarkTown_Lab/scripts.pory"

# 994 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogOfferEviolite:
# 995 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Actually, I have something\n"
# 996 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for your travels.\p"
# 997 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I've been keeping it here\n"
# 998 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "for a young Trainer to use.$"
# 999 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1000 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogBagFull:
# 1001 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh! There's no room\n"
# 1002 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "in your Bag right now.\p"
# 1003 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Make some space and come back.\n"
# 1004 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'll keep it safe for you!$"
# 1005 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1006 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogExplainEviolite:
# 1007 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That's an Eviolite.\p"
# 1008 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Have a Pokémon that can still\n"
# 1009 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "evolve hold it. It will boost\l"
# 1010 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "its Defense and Sp. Def.\p"
# 1011 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A little extra protection\n"
# 1012 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "while it's growing!\p"
# 1013 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You can give it to whichever\n"
# 1014 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "partner needs it most.$"
# 1015 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1016 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_CosmogFarewell:
# 1017 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "If you notice anything unusual,\n"
# 1018 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "you have my number.\p"
# 1019 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now, where was that notebook...?\n"
# 1020 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah! Under the first one.\p"
# 1021 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take care, {PLAYER}.\n"
# 1022 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Both of you!$"
# 1023 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1024 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmCallYou:
# 1025 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}, I'll call you if\n"
# 1026 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "anything comes up.$"
# 1027 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1028 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAfterTheft:
# 1029 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 1030 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 1031 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 1032 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 1033 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1034 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall1:
# 1035 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: Hi, {PLAYER}!\p"
# 1036 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks to you, my research is\n"
# 1037 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "going great!\p"
# 1038 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Take this as a token of my\n"
# 1039 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "appreciation.$"
# 1040 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1041 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveMasterBall2:
# 1042 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Master Ball is the best!\p"
# 1043 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the ultimate Ball! It'll\n"
# 1044 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "catch any Pokémon without fail.\p"
# 1045 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's given only to recognized\n"
# 1046 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon researchers.\p"
# 1047 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I think you can make much better\n"
# 1048 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "use of it than I can, {PLAYER}!$"
# 1049 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1050 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoGirls:
# 1051 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "By the way...\n"
# 1052 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "A group of beautiful Kimono\l"
# 1053 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls were looking for you.\p"
# 1054 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They told me they are\n"
# 1055 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "waiting for you at the\l"
# 1056 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ecruteak Dance Theater.\p"
# 1057 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I know you've gone through many\n"
# 1058 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "things since that Egg got you\l"
# 1059 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "involved in all this...\p"
# 1060 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I hope you'll carry through it.$"
# 1061 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1062 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmMissedSurf:
# 1063 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: Oh, and a gentleman\n"
# 1064 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "from the Dance Theater left this\l"
# 1065 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here for you.$"
# 1066 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1067 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_KimonoWaiting:
# 1068 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: The Kimono\n"
# 1069 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Girls are waiting for you at\l"
# 1070 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "the Ecruteak Dance Theater.$"
# 1071 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1072 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_League:
# 1073 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Prof. Elm: Hahaha...\n"
# 1074 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Good job!\p"
# 1075 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "That rare Egg has brought you\n"
# 1076 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "a lot of trouble, huh?\p"
# 1077 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Kimono Girls said something\n"
# 1078 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "about me?\p"
# 1079 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I have nothing to do with it.\p"
# 1080 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You made your decision and went\n"
# 1081 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "through with it.\p"
# 1082 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Having done so much, you should\n"
# 1083 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "be able to face the League now!\p"
# 1084 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You should head for Indigo\n"
# 1085 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Plateau!\p"
# 1086 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Do you know how to get there?\n"
# 1087 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Follow Route 27 to Route 26.\p"
# 1088 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Once there, go straight north!$"
# 1089 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1090 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1091 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket1:
# 1092 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\p"
# 1093 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I called because I have\n"
# 1094 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "something for you.\p"
# 1095 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "See? It's an S.S.Ticket.\p"
# 1096 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can catch Pokémon in\n"
# 1097 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Sevii.$"
# 1098 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1099 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ElmGiveTicket2:
# 1100 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The ship departs from Olivine\n"
# 1101 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "City.\p"
# 1102 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But you knew that already,\n"
# 1103 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}.\p"
# 1104 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "After all, you've traveled all\n"
# 1105 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "over with your Pokémon.$"
# 1106 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1107 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_LabMonEgg:
# 1108 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's the Pokémon Egg being\n"
# 1109 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "studied by Prof. Elm.$"
# 1110 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1111 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGivePotion:
# 1112 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}, I want you to have\n"
# 1113 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "this for your errand.$"
# 1114 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1115 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideAlwaysBusy:
# 1116 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There are only three of us, so\n"
# 1117 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "we're always busy.$"
# 1118 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1119 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideSave:
# 1120 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Don't forget to save your game\n"
# 1121 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "regularly!\p"
# 1122 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Press the Start button, then\n"
# 1123 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Save the game!$"
# 1124 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1125 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideTheftTestimony:
# 1126 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "There was a loud noise\n"
# 1127 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "outside…\p"
# 1128 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "When we went to look,\n"
# 1129 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "someone stole a Pokémon.\p"
# 1130 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's unbelievable that anyone\n"
# 1131 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "would do that!\p"
# 1132 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "…sigh… That stolen Pokémon.\p"
# 1133 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I wonder how it's doing.\p"
# 1134 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "They say a Pokémon raised by a\n"
# 1135 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "bad person turns bad itself.$"
# 1136 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1137 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideGiveBalls:
# 1138 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER}!\p"
# 1139 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use these on your Pokédex\n"
# 1140 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "quest!$"
# 1141 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1142 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_ExplainDexnav:
# 1143 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "We've also sent a Dexnav\n"
# 1144 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "application to your Pokégear!\p"
# 1145 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Use it to catch lots of Pokémon!$"
# 1146 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1147 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_AideExplainBalls:
# 1148 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "To add to your Pokédex, you\n"
# 1149 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "have to catch Pokémon.\p"
# 1150 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Throw Poké Balls at wild\n"
# 1151 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Pokémon to get them.$"
# 1152 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1153 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer1:
# 1154 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I heard a Pokémon was stolen\n"
# 1155 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "here…\p"
# 1156 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I was just getting some\n"
# 1157 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "information from Prof. Elm.\p"
# 1158 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Apparently, it was a young\n"
# 1159 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "male with long, red hair…\p"
# 1160 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "What?\p"
# 1161 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "You battled a trainer like\n"
# 1162 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "that?\p"
# 1163 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Did you happen to get his\n"
# 1164 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "name?$"
# 1165 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1166 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer2:
# 1167 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So Silver was his name.\p"
# 1168 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1169 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1170 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1171 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Officer3:
# 1172 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ok! So {RIVAL} was his name.\p"
# 1173 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Thanks for helping my\n"
# 1174 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "investigation!$"
# 1175 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1176 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_OfficerNo:
# 1177 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Surely you got his name?!$"
# 1178 "data/maps/NewBarkTown_Lab/scripts.pory"

# 1179 "data/maps/NewBarkTown_Lab/scripts.pory"
NewBarkTown_Lab_Text_Elm_CallMe:
# 1180 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Ah, {PLAYER}!\p"
# 1181 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "How's your Pokédex coming along?\n"
# 1182 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I'm busy now, but call me sometime\l"
# 1183 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "and I can check your progress!$"

NewBarkTown_Lab_GiveStarterMega::
# 1187 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_0
# 1191 "data/maps/NewBarkTown_Lab/scripts.pory"
	giveitem ITEM_BONDSTONE, 1
# 1192 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_GiveStarterMega_Text_1
	return


NewBarkTown_Lab_EventScript_ElmPostgameHint::
# 1199 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0
# 1208 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1
# 1210 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1211 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1212 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1213 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1214 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_CLICK
# 1215 "data/maps/NewBarkTown_Lab/scripts.pory"
	delay 10
# 1216 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PIN
# 1217 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1218 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2
# 1224 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
# 1225 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_VICTORYROAD_RIVAL
# 1226 "data/maps/NewBarkTown_Lab/scripts.pory"
	checkplayergender
# 1227 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_Lab_EventScript_ElmPostgameHint_2
# 1236 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4
NewBarkTown_Lab_EventScript_ElmPostgameHint_1:
# 1244 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5
# 1246 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_HIDE_MTSILVER_GUARD
# 1247 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALLOW_SOUTH_JOHTO_PASS
# 1248 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
# 1249 "data/maps/NewBarkTown_Lab/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 11
# 1250 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ElmPostgameHint_2:
# 1228 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3
	goto NewBarkTown_Lab_EventScript_ElmPostgameHint_1


ElmIntro::
# 1255 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox ElmIntro_Text_0, MSGBOX_YESNO
	return


NewBarkTown_Lab_EventScript_ArtifactOfChaos::
# 1281 "data/maps/NewBarkTown_Lab/scripts.pory"
	lock
# 1282 "data/maps/NewBarkTown_Lab/scripts.pory"
	goto_if_set FLAG_ALL_INNATES_UNLOCKED, NewBarkTown_Lab_EventScript_ArtifactOfChaos_2
# 1306 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4
# 1311 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5
# 1317 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6, MSGBOX_YESNO
# 1323 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_8
# 1336 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8
NewBarkTown_Lab_EventScript_ArtifactOfChaos_1:
# 1340 "data/maps/NewBarkTown_Lab/scripts.pory"
	closemessage
# 1341 "data/maps/NewBarkTown_Lab/scripts.pory"
	release
	end

NewBarkTown_Lab_EventScript_ArtifactOfChaos_2:
# 1283 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_0
# 1287 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1, MSGBOX_YESNO
# 1288 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NewBarkTown_Lab_EventScript_ArtifactOfChaos_5
# 1302 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_5:
# 1289 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_PC_OFF
# 1290 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1291 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_ALL_INNATES_UNLOCKED
# 1292 "data/maps/NewBarkTown_Lab/scripts.pory"
	compare VAR_NEWBARKTOWN_LABSTATE, 11
	goto_if_lt NewBarkTown_Lab_EventScript_ArtifactOfChaos_12
# 1295 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_POSTGAME_FEATURES
NewBarkTown_Lab_EventScript_ArtifactOfChaos_11:
# 1297 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_8:
# 1324 "data/maps/NewBarkTown_Lab/scripts.pory"
	playse SE_SWITCH
# 1325 "data/maps/NewBarkTown_Lab/scripts.pory"
	waitse
# 1326 "data/maps/NewBarkTown_Lab/scripts.pory"
	setflag FLAG_ALL_INNATES_UNLOCKED
# 1327 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_REPLAY_NO_INNATES
# 1328 "data/maps/NewBarkTown_Lab/scripts.pory"
	msgbox NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_1

NewBarkTown_Lab_EventScript_ArtifactOfChaos_12:
# 1293 "data/maps/NewBarkTown_Lab/scripts.pory"
	clearflag FLAG_POSTGAME_FEATURES
	goto NewBarkTown_Lab_EventScript_ArtifactOfChaos_11


NewBarkTown_Lab_GiveStarterMega_Text_0:
# 1187 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Oh, and you got a Mega Ring from \n"
	.string "Prof. Oak?\l"
	.string "Then I think you are ready to handle\l"
	.string "this.$"

NewBarkTown_Lab_GiveStarterMega_Text_1:
# 1192 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "It's a special Mega Stone, specifically\n"
	.string "for your starter Pokémon. I expect \l"
	.string "great things from you, {PLAYER}!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_0:
# 1199 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Elm: {PLAYER}! There you are!\n"
	.string "I called because I heard that the \l"
	.string "Battle Tower is open! \p"
	.string "I hear strong trainers\n"
	.string "are gathering in there!\p"
	.string "You can get there from Route 40\n"
	.string "near Olivine City.$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_1:
# 1208 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "But first, let me upgrade your Pokédex\n"
	.string "with a new feature!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_2:
# 1218 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Now you can view abilities of the\n"
	.string "opposing Pokémon with the L-button\l"
	.string "in battle! \p"
	.string "That will surely be handy as the\n"
	.string "battles get tougher!$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_3:
# 1228 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Crystal went to train\n"
	.string "in Mt. Silver. \p"
	.string "She looked really tired\n"
	.string "the last time I saw her though... \p"
	.string "Could you check on her at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_4:
# 1236 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I also heard that Gold went to train\n"
	.string "in Mt. Silver. \p"
	.string "He looked really tired\n"
	.string "the last time I saw him though...\p"
	.string "Could you check on him at some point?$"

NewBarkTown_Lab_EventScript_ElmPostgameHint_Text_5:
# 1244 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "I asked from the League to let you\n"
	.string "pass since you've the new Champion.$"

ElmIntro_Text_0:
# 1255 "data/maps/NewBarkTown_Lab/scripts.pory"
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
# 1283 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact of Chaos is humming.\p"
	.string "All innate abilities are currently\n"
	.string "active.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_1:
# 1287 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Deactivate the Artifact?$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_2:
# 1297 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The glow from the Artifact fades.\p"
	.string "Innate abilities will now unlock at\n"
	.string "their intended levels again.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_3:
# 1302 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "The Artifact continues humming.\n"
	.string "Hope Elm hasn't noticed yet!$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_4:
# 1306 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Amidst the books is Elm's very own\n"
	.string "Artifact of Chaos.\p"
	.string "There's a small label on the side:\n"
	.string "DO NOT TOUCH.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_5:
# 1311 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "Important! Activating this Artifact\n"
	.string "unlocks all innate abilities,\l"
	.string "regardless of a Pokémon's level.\p"
	.string "It also lets you inspect enemy\n"
	.string "innates in battle by pressing L.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_6:
# 1317 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "This is not the intended way to play\n"
	.string "the game and will not be balanced\l"
	.string "at all.\p"
	.string "If you understand and still wish to\n"
	.string "activate it, choose Yes.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_7:
# 1328 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} tapped the Artifact.\p"
	.string "Game balance quietly\n"
	.string "leaves the building.\p"
	.string "All innates are now active. Press L\n"
	.string "in battle to inspect enemy innates.$"

NewBarkTown_Lab_EventScript_ArtifactOfChaos_Text_8:
# 1336 "data/maps/NewBarkTown_Lab/scripts.pory"
	.string "{PLAYER} left the Artifact alone.\n"
	.string "Chaos shall not win today.$"
