# 1 "data/maps/NewBarkTown/scripts.pory"

# 2 "data/maps/NewBarkTown/scripts.pory"
.set LOCALID_LASS, 2
# 3 "data/maps/NewBarkTown/scripts.pory"
.set LOCALID_SILVER, 3
# 4 "data/maps/NewBarkTown/scripts.pory"

# 5 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_MapScripts::
# 6 "data/maps/NewBarkTown/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
# 7 "data/maps/NewBarkTown/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
# 8 "data/maps/NewBarkTown/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 9 "data/maps/NewBarkTown/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, NewBarkTown_OnLoad
# 10 "data/maps/NewBarkTown/scripts.pory"
	.byte 0
# 11 "data/maps/NewBarkTown/scripts.pory"

# 12 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_OnLoad::
# 13 "data/maps/NewBarkTown/scripts.pory"
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN
# 14 "data/maps/NewBarkTown/scripts.pory"
	end
# 15 "data/maps/NewBarkTown/scripts.pory"

# 16 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_OnFrame::
# 17 "data/maps/NewBarkTown/scripts.pory"
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
# 18 "data/maps/NewBarkTown/scripts.pory"
	map_script_2 VAR_RIFT_MISSIONS_STATE, 1, NewBarkTown_EventScript_LookerCall
# 19 "data/maps/NewBarkTown/scripts.pory"
	map_script_2 VAR_NEWBARK_TOWN_STATE, 11, NewBarkTown_EventScript_ArcherArcadeCall
# 20 "data/maps/NewBarkTown/scripts.pory"
    map_script_2 VAR_RIVAL_STATE, 0, NewBarkTown_EventScript_RivalIntro
# 21 "data/maps/NewBarkTown/scripts.pory"
    map_script_2 VAR_RIVAL_STATE, 2, NewBarkTown_EventScript_RivalBattle
# 22 "data/maps/NewBarkTown/scripts.pory"
	.2byte 0
# 23 "data/maps/NewBarkTown/scripts.pory"

# 24 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ElmCallAfterLeague::
# 25 "data/maps/NewBarkTown/scripts.pory"
	lock
# 26 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall BlackthornCity_Text_ElmCall
# 27 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 28 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 29 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 7
# 30 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 10
# 31 "data/maps/NewBarkTown/scripts.pory"
	release
# 32 "data/maps/NewBarkTown/scripts.pory"
	end
# 33 "data/maps/NewBarkTown/scripts.pory"

# 34 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 1. Armed by the first Hall of Fame (VAR_RIFT_MISSIONS_STATE = 1);
# 35 "data/maps/NewBarkTown/scripts.pory"
@ fires on the first frame after the player leaves the house. The frame table
# 36 "data/maps/NewBarkTown/scripts.pory"
@ runs the first true entry per frame, so Elm's call (state 6 -> 7) goes first
# 37 "data/maps/NewBarkTown/scripts.pory"
@ and this one on the following frame - one call after the other.
# 38 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LookerCall::
# 39 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 2          @ first instruction: stops re-firing
# 40 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_DAILY_LOOKER_CALL             @ today's call has been made
# 41 "data/maps/NewBarkTown/scripts.pory"
	lock
# 42 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall NewBarkTown_Text_LookerCall
# 43 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 44 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 45 "data/maps/NewBarkTown/scripts.pory"
	release
# 46 "data/maps/NewBarkTown/scripts.pory"
	end
# 47 "data/maps/NewBarkTown/scripts.pory"

# 48 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: the two lines after the calls are goto_if_eq, NOT call_if_eq -
# 49 "data/maps/NewBarkTown/scripts.pory"
@ whoever matches one never comes back here. Any new call must go ABOVE them
# 50 "data/maps/NewBarkTown/scripts.pory"
@ or it silently stops running in NEWBARK_TOWN_STATE 2 and 4. (Rift Mission 4,
# 51 "data/maps/NewBarkTown/scripts.pory"
@ .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md section 3.3.)
# 52 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_OnTransition::
# 53 "data/maps/NewBarkTown/scripts.pory"
    call Common_EventScript_SetupRivalGfxId
# 54 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_ApplyUBVisibility      @ Rift Mission 4 - must stay above the gotos
# 55 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
# 56 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
# 57 "data/maps/NewBarkTown/scripts.pory"
	end
# 58 "data/maps/NewBarkTown/scripts.pory"

# 59 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Set_TalkToElm::
# 60 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 61 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_LASS, 0, 11
# 62 "data/maps/NewBarkTown/scripts.pory"
	callnative SetTimeBasedEncounters
# 63 "data/maps/NewBarkTown/scripts.pory"
	end
# 64 "data/maps/NewBarkTown/scripts.pory"

# 65 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Set_TalkToMom::
# 66 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_LASS, 0, 11
# 67 "data/maps/NewBarkTown/scripts.pory"
	callnative SetTimeBasedEncounters
# 68 "data/maps/NewBarkTown/scripts.pory"
	end
# 69 "data/maps/NewBarkTown/scripts.pory"

# 70 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LabSign::
# 71 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
# 72 "data/maps/NewBarkTown/scripts.pory"
	end
# 73 "data/maps/NewBarkTown/scripts.pory"

# 74 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TownSign::
# 75 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
# 76 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 77 "data/maps/NewBarkTown/scripts.pory"
	end
# 78 "data/maps/NewBarkTown/scripts.pory"

# 79 "data/maps/NewBarkTown/scripts.pory"

# 80 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Lass::
# 81 "data/maps/NewBarkTown/scripts.pory"
	lock
# 82 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 83 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
# 84 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
# 85 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
# 86 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
# 87 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 88 "data/maps/NewBarkTown/scripts.pory"
	release
# 89 "data/maps/NewBarkTown/scripts.pory"
	end
# 90 "data/maps/NewBarkTown/scripts.pory"
	
# 91 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState2::
# 92 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 93 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 94 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 95 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 96 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 97 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
# 98 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 99 "data/maps/NewBarkTown/scripts.pory"
	release
# 100 "data/maps/NewBarkTown/scripts.pory"
	end
# 101 "data/maps/NewBarkTown/scripts.pory"

# 102 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState3::
# 103 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
# 104 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 105 "data/maps/NewBarkTown/scripts.pory"
	release
# 106 "data/maps/NewBarkTown/scripts.pory"
	end
# 107 "data/maps/NewBarkTown/scripts.pory"

# 108 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState4::
# 109 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 110 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 111 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 112 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 113 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 114 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
# 115 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 116 "data/maps/NewBarkTown/scripts.pory"
	release
# 117 "data/maps/NewBarkTown/scripts.pory"
	end
# 118 "data/maps/NewBarkTown/scripts.pory"

# 119 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Wooper::
# 120 "data/maps/NewBarkTown/scripts.pory"
	lock
# 121 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 122 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 123 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
# 124 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
# 125 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 126 "data/maps/NewBarkTown/scripts.pory"
	release
# 127 "data/maps/NewBarkTown/scripts.pory"
	end
# 128 "data/maps/NewBarkTown/scripts.pory"

# 129 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTrigger::
# 130 "data/maps/NewBarkTown/scripts.pory"
	lock
# 131 "data/maps/NewBarkTown/scripts.pory"
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
# 132 "data/maps/NewBarkTown/scripts.pory"
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
# 133 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
# 134 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 135 "data/maps/NewBarkTown/scripts.pory"
	release
# 136 "data/maps/NewBarkTown/scripts.pory"
	end
# 137 "data/maps/NewBarkTown/scripts.pory"

# 138 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTriggersState2::
# 139 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 140 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 141 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 142 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
# 143 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 144 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
# 145 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 146 "data/maps/NewBarkTown/scripts.pory"
	return
# 147 "data/maps/NewBarkTown/scripts.pory"

# 148 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTriggersState4::
# 149 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 150 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 151 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 152 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
# 153 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 154 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
# 155 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 156 "data/maps/NewBarkTown/scripts.pory"
	return 
# 157 "data/maps/NewBarkTown/scripts.pory"

# 158 "data/maps/NewBarkTown/scripts.pory"

# 159 "data/maps/NewBarkTown/scripts.pory"

# 160 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_FatMan::
# 161 "data/maps/NewBarkTown/scripts.pory"
	lock
# 162 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 163 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
# 164 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
# 165 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 166 "data/maps/NewBarkTown/scripts.pory"
	release
# 167 "data/maps/NewBarkTown/scripts.pory"
	end
# 168 "data/maps/NewBarkTown/scripts.pory"

# 169 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_FatManState2::
# 170 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
# 171 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 172 "data/maps/NewBarkTown/scripts.pory"
	release
# 173 "data/maps/NewBarkTown/scripts.pory"
	end
# 174 "data/maps/NewBarkTown/scripts.pory"

# 175 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Silver::
# 176 "data/maps/NewBarkTown/scripts.pory"
	lock
# 177 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
# 178 "data/maps/NewBarkTown/scripts.pory"
	delay 60
# 179 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 180 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
# 181 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 182 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 183 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
# 184 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BANG
# 185 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
# 186 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
# 187 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 188 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
# 189 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 190 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 191 "data/maps/NewBarkTown/scripts.pory"
	release
# 192 "data/maps/NewBarkTown/scripts.pory"
	end
# 193 "data/maps/NewBarkTown/scripts.pory"

# 194 "data/maps/NewBarkTown/scripts.pory"

# 195 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Door::
# 196 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
# 197 "data/maps/NewBarkTown/scripts.pory"
	end
# 198 "data/maps/NewBarkTown/scripts.pory"

# 199 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan1::
# 200 "data/maps/NewBarkTown/scripts.pory"
	givebp 4
# 201 "data/maps/NewBarkTown/scripts.pory"
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
# 202 "data/maps/NewBarkTown/scripts.pory"
	end
# 203 "data/maps/NewBarkTown/scripts.pory"

# 204 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan2::
# 205 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 206 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 207 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 208 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 209 "data/maps/NewBarkTown/scripts.pory"
	end
# 210 "data/maps/NewBarkTown/scripts.pory"

# 211 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan3::
# 212 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 5
# 213 "data/maps/NewBarkTown/scripts.pory"
	
# 214 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
# 215 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
# 216 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
# 217 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
# 218 "data/maps/NewBarkTown/scripts.pory"
	end
# 219 "data/maps/NewBarkTown/scripts.pory"

# 220 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_SilverPushesPlayer:
# 221 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 222 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 223 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 224 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 225 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 226 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 227 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 228 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 229 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 230 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 231 "data/maps/NewBarkTown/scripts.pory"

# 232 "data/maps/NewBarkTown/scripts.pory"

# 233 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerPushedBySilver:
# 234 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 235 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 236 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 237 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 238 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 239 "data/maps/NewBarkTown/scripts.pory"
	jump_2_down
# 240 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 241 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 242 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 243 "data/maps/NewBarkTown/scripts.pory"

# 244 "data/maps/NewBarkTown/scripts.pory"
	
# 245 "data/maps/NewBarkTown/scripts.pory"

# 246 "data/maps/NewBarkTown/scripts.pory"

# 247 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_FaceDown:
# 248 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 249 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 250 "data/maps/NewBarkTown/scripts.pory"

# 251 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LabSign:
# 252 "data/maps/NewBarkTown/scripts.pory"
	.string "Prof. Elm's Lab$"
# 253 "data/maps/NewBarkTown/scripts.pory"

# 254 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Door:
# 255 "data/maps/NewBarkTown/scripts.pory"
	.string "The door is locked.$"
# 256 "data/maps/NewBarkTown/scripts.pory"

# 257 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Wooper:
# 258 "data/maps/NewBarkTown/scripts.pory"
	.string "Wooper: Woooooop.$"
# 259 "data/maps/NewBarkTown/scripts.pory"

# 260 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_FatManState2:
# 261 "data/maps/NewBarkTown/scripts.pory"
	.string "Wow, your Pokégear is impressive!\n"
# 262 "data/maps/NewBarkTown/scripts.pory"
	.string "Did your mom get it for you?$"
# 263 "data/maps/NewBarkTown/scripts.pory"

# 264 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_FatManState3:
# 265 "data/maps/NewBarkTown/scripts.pory"
	.string "Yo, {PLAYER}!\p"
# 266 "data/maps/NewBarkTown/scripts.pory"
	.string "I hear Prof. Elm discovered\n"
# 267 "data/maps/NewBarkTown/scripts.pory"
	.string "some new Pokémon.$"
# 268 "data/maps/NewBarkTown/scripts.pory"

# 269 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState2:
# 270 "data/maps/NewBarkTown/scripts.pory"
	.string "Wait, {PLAYER}!\p"
# 271 "data/maps/NewBarkTown/scripts.pory"
	.string "It's dangerous to go out\n"
# 272 "data/maps/NewBarkTown/scripts.pory"
	.string "without a Pokémon!\p"
# 273 "data/maps/NewBarkTown/scripts.pory"
	.string "Wild Pokémon jump out of the grass\n"
# 274 "data/maps/NewBarkTown/scripts.pory"
	.string "on the way to the next town.$"
# 275 "data/maps/NewBarkTown/scripts.pory"

# 276 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState3:
# 277 "data/maps/NewBarkTown/scripts.pory"
	.string "Oh! Your Pokémon is adorable!\n"
# 278 "data/maps/NewBarkTown/scripts.pory"
	.string "I wish I had one!$"
# 279 "data/maps/NewBarkTown/scripts.pory"

# 280 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState4:
# 281 "data/maps/NewBarkTown/scripts.pory"
	.string "Hi, {PLAYER}! Leaving again?\p"
# 282 "data/maps/NewBarkTown/scripts.pory"
	.string "You should tell your mom if\n"
# 283 "data/maps/NewBarkTown/scripts.pory"
	.string "you are leaving.$"
# 284 "data/maps/NewBarkTown/scripts.pory"

# 285 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState5:
# 286 "data/maps/NewBarkTown/scripts.pory"
	.string "Call your mom on your Pokégear\n"
# 287 "data/maps/NewBarkTown/scripts.pory"
	.string "to let her know how you're doing.$\p"
# 288 "data/maps/NewBarkTown/scripts.pory"

# 289 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Silver1:
# 290 "data/maps/NewBarkTown/scripts.pory"
	.string ". . .\p"
# 291 "data/maps/NewBarkTown/scripts.pory"
	.string "So this is the famous Elm\n"
# 292 "data/maps/NewBarkTown/scripts.pory"
	.string "Pokémon Lab…$"
# 293 "data/maps/NewBarkTown/scripts.pory"

# 294 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Silver2:
# 295 "data/maps/NewBarkTown/scripts.pory"
	.string "…What are you staring at?$"
# 296 "data/maps/NewBarkTown/scripts.pory"

# 297 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Sign:
# 298 "data/maps/NewBarkTown/scripts.pory"
	.string "New Bark Town\p"
# 299 "data/maps/NewBarkTown/scripts.pory"
	.string "The Town Where the Winds of\n"
# 300 "data/maps/NewBarkTown/scripts.pory"
	.string "a New Beginning Blow$"
# 301 "data/maps/NewBarkTown/scripts.pory"

# 302 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_PlayersHouseMailbox::
# 303 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
# 304 "data/maps/NewBarkTown/scripts.pory"
	end
# 305 "data/maps/NewBarkTown/scripts.pory"

# 306 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ElmsHouseMailbox::
# 307 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
# 308 "data/maps/NewBarkTown/scripts.pory"
	end
# 309 "data/maps/NewBarkTown/scripts.pory"

# 310 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_PlayersHouse:
# 311 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}'s House$"
# 312 "data/maps/NewBarkTown/scripts.pory"

# 313 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ElmsHouse:
# 314 "data/maps/NewBarkTown/scripts.pory"
	.string "Prof. Elm's House$"
# 315 "data/maps/NewBarkTown/scripts.pory"

# 316 "data/maps/NewBarkTown/scripts.pory"
@ Looker's first call (script revision V2, 25/09/2026). Cordial and
# 317 "data/maps/NewBarkTown/scripts.pory"
@ professional, and short: it congratulates, introduces, asks and names the
# 318 "data/maps/NewBarkTown/scripts.pory"
@ house. It does NOT retell the holiday cover over the phone and it does not
# 319 "data/maps/NewBarkTown/scripts.pory"
@ hide the request behind three attempts at an introduction. No creature, no
# 320 "data/maps/NewBarkTown/scripts.pory"
@ town and no name is given away.
# 321 "data/maps/NewBarkTown/scripts.pory"
@ It also sets FLAG_DAILY_LOOKER_CALL: from here on Looker rings once a day
# 322 "data/maps/NewBarkTown/scripts.pory"
@ while a briefing is pending in Olivine (ShouldDoRiftMissionCall,
# 323 "data/maps/NewBarkTown/scripts.pory"
@ src/field_control_avatar.c), and the day he calls in person counts.
# 324 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LookerCall:
# 325 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Hello, {PLAYER}?\n"
# 326 "data/maps/NewBarkTown/scripts.pory"
	.string "Congratulations on becoming\l"
# 327 "data/maps/NewBarkTown/scripts.pory"
	.string "Champion!\p"
# 328 "data/maps/NewBarkTown/scripts.pory"
	.string "My name is Looker.\n"
# 329 "data/maps/NewBarkTown/scripts.pory"
	.string "International Police.\p"
# 330 "data/maps/NewBarkTown/scripts.pory"
	.string "My colleague and I need your\n"
# 331 "data/maps/NewBarkTown/scripts.pory"
	.string "help with an investigation in\l"
# 332 "data/maps/NewBarkTown/scripts.pory"
	.string "Johto.\p"
# 333 "data/maps/NewBarkTown/scripts.pory"
	.string "Please meet us in Olivine.\p"
# 334 "data/maps/NewBarkTown/scripts.pory"
	.string "Our house is the one nearest\n"
# 335 "data/maps/NewBarkTown/scripts.pory"
	.string "the Gym.\p"
# 336 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll explain when you arrive.$"

NewBarkTown_EventScript_RivalIntro::
# 340 "data/maps/NewBarkTown/scripts.pory"
	lock
# 341 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_0
# 342 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 343 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WALL_HIT
# 344 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_1
# 345 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 346 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 347 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_2
# 348 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 349 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
# 350 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 351 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 352 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
# 353 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 354 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 355 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 356 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_4
# 357 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 358 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, Common_Movement_ExclamationMark
# 359 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 360 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_5
# 361 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 362 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_6
# 363 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 364 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
# 365 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 366 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 367 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
# 368 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 369 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 370 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_8
# 371 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_9
# 372 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 373 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 374 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_RIVAL
# 375 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL
# 376 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL2
# 377 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIVAL_STATE, 1
# 378 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 379 "data/maps/NewBarkTown/scripts.pory"
	release
	end


NewBarkTown_EventScript_RivalBattle::
# 384 "data/maps/NewBarkTown/scripts.pory"
	lock
# 385 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 386 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
# 387 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 388 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 389 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
# 390 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 391 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 392 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_1
# 394 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_2
# 395 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_MARILL2
# 396 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, Common_Movement_ExclamationMark
# 397 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 398 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 399 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_PLAYER, NewBarkTown_EventScript_RivalBattle_Movement_3
# 400 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 401 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_5
# 402 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 403 "data/maps/NewBarkTown/scripts.pory"
	createfieldmugshotrival
# 404 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_0
# 405 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_EventScript_RivalBattle_Movement_4
# 406 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 407 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 408 "data/maps/NewBarkTown/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 409 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_1
# 411 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_2
# 412 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_3
# 414 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_4
# 416 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_5
# 419 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_NO_WHITEOUT
# 420 "data/maps/NewBarkTown/scripts.pory"
	checkplayergender
# 421 "data/maps/NewBarkTown/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_EventScript_RivalBattle_2
# 424 "data/maps/NewBarkTown/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVALGOLD1, NewBarkTown_EventScript_RivalBattle_Text_6
NewBarkTown_EventScript_RivalBattle_1:
# 426 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_NO_WHITEOUT
# 427 "data/maps/NewBarkTown/scripts.pory"
	special HealPlayerParty
# 428 "data/maps/NewBarkTown/scripts.pory"
	createfieldmugshotrival
# 429 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_7
# 431 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_8
# 434 "data/maps/NewBarkTown/scripts.pory"
	removefieldmugshot
# 435 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 436 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_5
# 437 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_6
# 438 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 439 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_RIVAL
# 440 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL
# 441 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL2
# 442 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 443 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIVAL_STATE, 3
# 444 "data/maps/NewBarkTown/scripts.pory"
	release
	end

NewBarkTown_EventScript_RivalBattle_2:
# 422 "data/maps/NewBarkTown/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVALCRYSTAL1, NewBarkTown_EventScript_RivalBattle_Text_6
	goto NewBarkTown_EventScript_RivalBattle_1


RivalsMailbox::
# 449 "data/maps/NewBarkTown/scripts.pory"
	lock
# 450 "data/maps/NewBarkTown/scripts.pory"
	checkplayergender
# 451 "data/maps/NewBarkTown/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq RivalsMailbox_2
# 454 "data/maps/NewBarkTown/scripts.pory"
	msgbox RivalsMailbox_Text_1
RivalsMailbox_1:
# 456 "data/maps/NewBarkTown/scripts.pory"
	release
	end

RivalsMailbox_2:
# 452 "data/maps/NewBarkTown/scripts.pory"
	msgbox RivalsMailbox_Text_0
	goto RivalsMailbox_1


NewBarkTown_EventScript_ArcherArcadeCall::
# 461 "data/maps/NewBarkTown/scripts.pory"
	lock
# 462 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall NewBarkTown_EventScript_ArcherArcadeCall_Text_0
# 477 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 478 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 479 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 12
# 480 "data/maps/NewBarkTown/scripts.pory"
	release
	end


# 485 "data/maps/NewBarkTown/scripts.pory"

# 486 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 487 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 - Kartana + Guzzlord + Nihilego on the road outside the
# 488 "data/maps/NewBarkTown/scripts.pory"
@ player's own front door. Last mission of the arc, and the one they lose.
# 489 "data/maps/NewBarkTown/scripts.pory"
@
# 490 "data/maps/NewBarkTown/scripts.pory"
@ The story in four lines. Three rifts open over New Bark and the three
# 491 "data/maps/NewBarkTown/scripts.pory"
@ beasts do not behave like three beasts: they move in the same instant, in
# 492 "data/maps/NewBarkTown/scripts.pory"
@ the same direction, like one thing wearing three bodies. The only counter
# 493 "data/maps/NewBarkTown/scripts.pory"
@ is to break all three at once, which takes four pairs of hands, which is
# 494 "data/maps/NewBarkTown/scripts.pory"
@ how the kid who was told "no" gets let in - by the woman who has just been
# 495 "data/maps/NewBarkTown/scripts.pory"
@ taught to ask. And when the three are down, the creature from the other
# 496 "data/maps/NewBarkTown/scripts.pory"
@ three missions walks out of the light, EATS them, becomes something else,
# 497 "data/maps/NewBarkTown/scripts.pory"
@ and puts all four of them on the ground in one motion. The town stands.
# 498 "data/maps/NewBarkTown/scripts.pory"
@ Nobody wins. That was the plan from the first mission.
# 499 "data/maps/NewBarkTown/scripts.pory"
@
# 500 "data/maps/NewBarkTown/scripts.pory"
@ Cast: Looker, Anabel, Mom, Gold/Crystal (+ Azumarill), Professor Elm and
# 501 "data/maps/NewBarkTown/scripts.pory"
@ Madame Lusamine, plus the creature and what it turns into.
# 502 "data/maps/NewBarkTown/scripts.pory"
@ Plan: .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md
# 503 "data/maps/NewBarkTown/scripts.pory"
@
# 504 "data/maps/NewBarkTown/scripts.pory"
@ Floor plan (dump_mapa.py NewBarkTown; y grows DOWNWARD). There is not one
# 505 "data/maps/NewBarkTown/scripts.pory"
@ water tile in LAYOUT_NEW_BARK_TOWN, so the collision bit is the whole
# 506 "data/maps/NewBarkTown/scripts.pory"
@ truth here - unlike the Cherrygrove beach.
# 507 "data/maps/NewBarkTown/scripts.pory"
@
# 508 "data/maps/NewBarkTown/scripts.pory"
@       x= 2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
# 509 "data/maps/NewBarkTown/scripts.pory"
@   y= 9   #  #  #  .  .  #  #  #  D  #  .  #  .  .  .  .  #  #  #  #  #  #  #  #
# 510 "data/maps/NewBarkTown/scripts.pory"
@   y=10   #  #  .  .  .  .  .  .  .  E' .  .  .  1  1a 1b #  #  #  #  #  #  #  #
# 511 "data/maps/NewBarkTown/scripts.pory"
@   y=11   .  .  .  .  .  .  .  .  .  .  .  .  .  .  Nk #  #  #  d  #  #  .  .  .
# 512 "data/maps/NewBarkTown/scripts.pory"
@   y=12   .  U' .  .  .  .  .  .  .  .  .  .  .  .  N  U  M  *  K  A  E  .  .  .
# 513 "data/maps/NewBarkTown/scripts.pory"
@   y=13   .  .  .  .  .  .  .  .  .  .  .  .  2  2a 2b 2c 2d 2e .  G  z  .  .  .
# 514 "data/maps/NewBarkTown/scripts.pory"
@   y=14   .  .  .  .  .  .  .  #  .  .  .  .  .  .  a3 a2 a1 aX .  .  z' .  .  .
# 515 "data/maps/NewBarkTown/scripts.pory"
@   y=15   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  3  3a 3b
# 516 "data/maps/NewBarkTown/scripts.pory"
@
# 517 "data/maps/NewBarkTown/scripts.pory"
@   D  lab door, warp (10,9)          d  player's house door, warp (20,11)
# 518 "data/maps/NewBarkTown/scripts.pory"
@   *  player (20,12)                 K  Looker (21,12)   A  Anabel (22,12)
# 519 "data/maps/NewBarkTown/scripts.pory"
@   M  Mom (19,12)                    G  Gold/Crystal (21,13)
# 520 "data/maps/NewBarkTown/scripts.pory"
@   z  Azumarill starts (22,13)       z' Azumarill after the cut-off (19,14)
# 521 "data/maps/NewBarkTown/scripts.pory"
@   U' Lusamine starts (3,12)         U  Lusamine after the fade (18,12),
# 522 "data/maps/NewBarkTown/scripts.pory"
@                                        then (17,12) from UBKnot onward
# 523 "data/maps/NewBarkTown/scripts.pory"
@   E' Elm starts (11,10)             E  Elm after the fade (23,12)
# 524 "data/maps/NewBarkTown/scripts.pory"
@   1  Kartana (15,10) -> 1a (16,10) -> 1b (17,10) in the lockstep drift
# 525 "data/maps/NewBarkTown/scripts.pory"
@   2  Nihilego (14,13) -> 2a -> 2b in the drift, then 2c 2d 2e in the lunge,
# 526 "data/maps/NewBarkTown/scripts.pory"
@      ending at (19,13), one diagonal step from the player and under Mom
# 527 "data/maps/NewBarkTown/scripts.pory"
@   3  Guzzlord (23,15) -> 3a (24,15) -> 3b (25,15); (26,15) is wall
# 528 "data/maps/NewBarkTown/scripts.pory"
@   a1 a2 a3  Azumarill's charge at the creature, ending (16,14)
# 529 "data/maps/NewBarkTown/scripts.pory"
@   N  the creature (16,12), which is also where what it becomes stands
# 530 "data/maps/NewBarkTown/scripts.pory"
@   Nk (16,11) is where Kartana is dragged to before it is eaten
# 531 "data/maps/NewBarkTown/scripts.pory"
@
# 532 "data/maps/NewBarkTown/scripts.pory"
@ LOOKER'S POCKET. (21,11) is the wall of the player's house, (22,12) is
# 533 "data/maps/NewBarkTown/scripts.pory"
@ Anabel and (21,13) is Gold/Crystal. The ONLY tile Looker can be talked to
# 534 "data/maps/NewBarkTown/scripts.pory"
@ from is (20,12), facing east - no getplayerxy needed.
# 535 "data/maps/NewBarkTown/scripts.pory"
@ And (20,12) is exactly where the game puts the player twice over:
# 536 "data/maps/NewBarkTown/scripts.pory"
@ HEAL_LOCATION_NEW_BARK_TOWN is (20,12) (src/data/heal_locations.h:139) and
# 537 "data/maps/NewBarkTown/scripts.pory"
@ NewBarkTown_OnLoad re-does the setrespawn on every load, so a blackout AND
# 538 "data/maps/NewBarkTown/scripts.pory"
@ a Fly both land on the talk tile. Retry costs zero steps - the only mission
# 539 "data/maps/NewBarkTown/scripts.pory"
@ in the arc where that is true.
# 540 "data/maps/NewBarkTown/scripts.pory"
@
# 541 "data/maps/NewBarkTown/scripts.pory"
@ (20,13) IS DELIBERATELY EMPTY, before the scene and during it. Nothing is
# 542 "data/maps/NewBarkTown/scripts.pory"
@ ever parked there. The Azumarill choreography goes around the outside, on
# 543 "data/maps/NewBarkTown/scripts.pory"
@ y=14, precisely so that it never has to stand in front of the player.
# 544 "data/maps/NewBarkTown/scripts.pory"
@
# 545 "data/maps/NewBarkTown/scripts.pory"
@ The player's front door at (20,11) stays usable before the scene. Harmless:
# 546 "data/maps/NewBarkTown/scripts.pory"
@ the scene only starts by talking to Looker, the house is empty during the
# 547 "data/maps/NewBarkTown/scripts.pory"
@ incident (NewBarkTown_PlayersHouse_1F_ApplyMomVisibility), and coming back
# 548 "data/maps/NewBarkTown/scripts.pory"
@ out puts the player on (20,12) again.
# 549 "data/maps/NewBarkTown/scripts.pory"
@
# 550 "data/maps/NewBarkTown/scripts.pory"
@ The three beasts stand on walkable ground and CAN be reached on foot. That
# 551 "data/maps/NewBarkTown/scripts.pory"
@ is fine - they only exist while the player is under lockall, and all three
# 552 "data/maps/NewBarkTown/scripts.pory"
@ have script NULL. Do not "fix" this by inventing collision.
# 553 "data/maps/NewBarkTown/scripts.pory"
@
# 554 "data/maps/NewBarkTown/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 555 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_1 - fixed cast cache (Looker, Anabel, Mom, Gold/Crystal,
# 556 "data/maps/NewBarkTown/scripts.pory"
@                 Azumarill)
# 557 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_2 - the three Ultra Beasts; always hidden on load
# 558 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_3 - Elm ONLY          \ separate because the cutscene
# 559 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_4 - Lusamine ONLY     / removeobjects these two to move them,
# 560 "data/maps/NewBarkTown/scripts.pory"
@                 and removeobject SETS the template's flag. If they shared
# 561 "data/maps/NewBarkTown/scripts.pory"
@                 FLAG_TEMP_1 the fade in UBScene would hide the whole cast.
# 562 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_5 - the creature ONLY       \ same reason: the absorption
# 563 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_6 - what it becomes ONLY    / removeobjects both of them
# 564 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_2  - battle outcome
# 565 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_3  - the player's pick: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego.
# 566 "data/maps/NewBarkTown/scripts.pory"
@                 Survives the battle: coming back from a battle does not
# 567 "data/maps/NewBarkTown/scripts.pory"
@                 reload the map, so ClearTempFieldEventData does not run.
# 568 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_4  - which Cosmog-family Pokemon the player is carrying, sampled
# 569 "data/maps/NewBarkTown/scripts.pory"
@                 AFTER the battle (the battle can evolve it) and re-read by
# 570 "data/maps/NewBarkTown/scripts.pory"
@                 the closing conversation. SPECIES_NONE = none.
# 571 "data/maps/NewBarkTown/scripts.pory"
@ Checked 20/09/2026: this map used no FLAG_TEMP_* or VAR_TEMP_* at all
# 572 "data/maps/NewBarkTown/scripts.pory"
@ before this mission. VAR_TEMP_1 is skipped anyway, for uniformity with the
# 573 "data/maps/NewBarkTown/scripts.pory"
@ three earlier missions (there it is VAR_TEMP_TRANSFERRED_SPECIES).
# 574 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_TEMP_E is reserved by the engine to suppress the follower - never use it.
# 575 "data/maps/NewBarkTown/scripts.pory"
@
# 576 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: seven residents of this map (locals 1, 2, 4, 5, 6, 7, 8) now carry
# 577 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_EVENT_ULTRABEAST_NEWBARK in their map.json "flag" field. A removeobject
# 578 "data/maps/NewBarkTown/scripts.pory"
@ on ANY of them SETS that flag and empties the whole town, permanently.
# 579 "data/maps/NewBarkTown/scripts.pory"
@
# 580 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: never clear FLAG_HIDE_NEWBARK_RIVALMARILL. Locals 9, 10 and 11 -
# 581 "data/maps/NewBarkTown/scripts.pory"
@ the original Gold/Crystal and two Marill - are hidden behind it from the
# 582 "data/maps/NewBarkTown/scripts.pory"
@ rival battle onward (setflag at the first rival scene, plus the three
# 583 "data/maps/NewBarkTown/scripts.pory"
@ removeobject at VAR_RIVAL_STATE 2 -> 3). If it were ever cleared the player
# 584 "data/maps/NewBarkTown/scripts.pory"
@ would see a SECOND Gold/Crystal at (12,13) while the mission's one stands
# 585 "data/maps/NewBarkTown/scripts.pory"
@ at (21,13), and a stray Marill at (11,13) right beside Nihilego.
# 586 "data/maps/NewBarkTown/scripts.pory"
@
# 587 "data/maps/NewBarkTown/scripts.pory"
@ OBJECT BUDGET. OBJECT_EVENTS_COUNT is 16 and includes the player
# 588 "data/maps/NewBarkTown/scripts.pory"
@ (include/constants/global.h:83). The peak of this scene is the player, the
# 589 "data/maps/NewBarkTown/scripts.pory"
@ follower, this mission's ten road objects and the creature = 13/16. What it
# 590 "data/maps/NewBarkTown/scripts.pory"
@ becomes only ever spawns after the three beasts and the creature have been
# 591 "data/maps/NewBarkTown/scripts.pory"
@ removed, so it never adds to the peak. Three spare slots, and every object
# 592 "data/maps/NewBarkTown/scripts.pory"
@ added here spends one.
# 593 "data/maps/NewBarkTown/scripts.pory"
@
# 594 "data/maps/NewBarkTown/scripts.pory"
@ The four OBJ_EVENT_GFX_LIGHT_SPRITE on this map cost NOTHING against that
# 595 "data/maps/NewBarkTown/scripts.pory"
@ 16. TrySpawnObjectEvents special-cases them (src/event_object_movement.c:
# 596 "data/maps/NewBarkTown/scripts.pory"
@ 3168): a light sprite goes to SpawnLightSprite, which CreateSprite()s into
# 597 "data/maps/NewBarkTown/scripts.pory"
@ gSprites[] and never touches gObjectEvents[]. So the lamps keep their own
# 598 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_NIGHT_POKEMON and this mission does not touch the lighting system at
# 599 "data/maps/NewBarkTown/scripts.pory"
@ all. Do not "free up slots" by hiding them - there is nothing to free.
# 600 "data/maps/NewBarkTown/scripts.pory"
@
# 601 "data/maps/NewBarkTown/scripts.pory"
@ What the budget DOES matter for: an object that does not fit simply fails
# 602 "data/maps/NewBarkTown/scripts.pory"
@ to spawn, with no error and no warning, and TrySpawnObjectEvents walks the
# 603 "data/maps/NewBarkTown/scripts.pory"
@ templates IN ORDER - so the ones that would lose are this mission's
# 604 "data/maps/NewBarkTown/scripts.pory"
@ (locals 16-27), the LAST in the array. Overspend and Looker is the one who
# 605 "data/maps/NewBarkTown/scripts.pory"
@ goes missing, which leaves the mission with no way to start.
# 606 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 607 "data/maps/NewBarkTown/scripts.pory"

# 608 "data/maps/NewBarkTown/scripts.pory"
@ Called from NewBarkTown_OnTransition, which runs before any object spawns -
# 609 "data/maps/NewBarkTown/scripts.pory"
@ so setflag/clearflag work here and removeobject would not. Temps are zeroed
# 610 "data/maps/NewBarkTown/scripts.pory"
@ on every load, so this recomputes from scratch every time.
# 611 "data/maps/NewBarkTown/scripts.pory"
@ The three unconditional setflag are what makes a retry after a blackout
# 612 "data/maps/NewBarkTown/scripts.pory"
@ start clean for free: the beasts and the creature are never on the road
# 613 "data/maps/NewBarkTown/scripts.pory"
@ until the cutscene puts them there.
# 614 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ApplyUBVisibility::
# 615 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_2                        @ the beasts: only the cutscene brings them in
# 616 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_5                        @ the creature
# 617 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_6                        @ what it becomes
# 618 "data/maps/NewBarkTown/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_HideUBCast
# 619 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_1
# 620 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 621 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 622 "data/maps/NewBarkTown/scripts.pory"
	return
# 623 "data/maps/NewBarkTown/scripts.pory"

# 624 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_HideUBCast::
# 625 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_1
# 626 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_3
# 627 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_4
# 628 "data/maps/NewBarkTown/scripts.pory"
	return
# 629 "data/maps/NewBarkTown/scripts.pory"

# 630 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 631 "data/maps/NewBarkTown/scripts.pory"
@ Two staging helpers, used all through the scene.
# 632 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 633 "data/maps/NewBarkTown/scripts.pory"

# 634 "data/maps/NewBarkTown/scripts.pory"
@ Flash da cena. fadescreenswapbuffers e NAO fadescreen: fadescreen copia
# 635 "data/maps/NewBarkTown/scripts.pory"
@ gPlttBufferFaded -> gPlttBufferUnfaded ao escurecer (src/field_weather.c,
# 636 "data/maps/NewBarkTown/scripts.pory"
@ FadeScreen) e o FADE_FROM_* seguinte reaplica o tint de horario por cima do
# 637 "data/maps/NewBarkTown/scripts.pory"
@ que ja estava tintado. A noite (coeff 10) cada par de flashes multiplicava a
# 638 "data/maps/NewBarkTown/scripts.pory"
@ cena por ~0,46 de novo, e depois de tres ou quatro a cidade ficava preta.
# 639 "data/maps/NewBarkTown/scripts.pory"
@ fadescreenswapbuffers usa BLDY no hardware e nao encosta nas paletas.
# 640 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFlash::
# 641 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 642 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 643 "data/maps/NewBarkTown/scripts.pory"
	return
# 644 "data/maps/NewBarkTown/scripts.pory"

# 645 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBShake::
# 646 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 1   @ vertical pan
# 647 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 648 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 12  @ num shakes
# 649 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 650 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 651 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 652 "data/maps/NewBarkTown/scripts.pory"
	return
# 653 "data/maps/NewBarkTown/scripts.pory"

# 654 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 655 "data/maps/NewBarkTown/scripts.pory"
@ Idle conversations, available from the moment the player reaches town and
# 656 "data/maps/NewBarkTown/scripts.pory"
@ until the YES. Each one ends by turning the actor back to the facing its
# 657 "data/maps/NewBarkTown/scripts.pory"
@ map.json template asks for, so a talk from an odd tile cannot leave anyone
# 658 "data/maps/NewBarkTown/scripts.pory"
@ crooked when the cutscene starts.
# 659 "data/maps/NewBarkTown/scripts.pory"
@
# 660 "data/maps/NewBarkTown/scripts.pory"
@ Two of them react to the Cosmog family in the party (design section 4.11):
# 661 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine, who is the only living person who knows what that light looks
# 662 "data/maps/NewBarkTown/scripts.pory"
@ like from the other side, and Elm, who is the one who identified the egg in
# 663 "data/maps/NewBarkTown/scripts.pory"
@ the first place. Both are OPTIONAL and carry NO state - without the Pokemon
# 664 "data/maps/NewBarkTown/scripts.pory"
@ the conversation is exactly the one line it always was.
# 665 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine's version has one non-negotiable rule (design section 6.4): the
# 666 "data/maps/NewBarkTown/scripts.pory"
@ scene does not suggest, at any point, that any of this is the player's
# 667 "data/maps/NewBarkTown/scripts.pory"
@ fault, and SHE is the one who says so out loud.
# 668 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 669 "data/maps/NewBarkTown/scripts.pory"

# 670 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine alone on the road in, at (3,12), reachable from (2,12), (4,12),
# 671 "data/maps/NewBarkTown/scripts.pory"
@ (3,11) and (3,13). This is her first spoken line in the whole arc. Nobody
# 672 "data/maps/NewBarkTown/scripts.pory"
@ announced her - the Olivine briefing does not mention her at all, on
# 673 "data/maps/NewBarkTown/scripts.pory"
@ purpose. She gives away nothing about the knot in UBKnot.
# 674 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamine::
# 675 "data/maps/NewBarkTown/scripts.pory"
	lock
# 676 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 677 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineIdle, MSGBOX_DEFAULT
# 678 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 679 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, NewBarkTown_EventScript_UBLusamineEnd
# 680 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 681 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineIdleCosmog, MSGBOX_DEFAULT
# 682 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamineEnd::
# 683 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 684 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST     @ map.json FACE_RIGHT
# 685 "data/maps/NewBarkTown/scripts.pory"
	release
# 686 "data/maps/NewBarkTown/scripts.pory"
	end
# 687 "data/maps/NewBarkTown/scripts.pory"

# 688 "data/maps/NewBarkTown/scripts.pory"
@ Elm at (11,10), outside his own lab door (10,9).
# 689 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElm::
# 690 "data/maps/NewBarkTown/scripts.pory"
	lock
# 691 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 692 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmIdle, MSGBOX_DEFAULT
# 693 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 694 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, NewBarkTown_EventScript_UBElmEnd
# 695 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 696 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmIdleCosmog, MSGBOX_DEFAULT
# 697 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElmEnd::
# 698 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 699 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_SOUTH         @ map.json FACE_DOWN
# 700 "data/maps/NewBarkTown/scripts.pory"
	release
# 701 "data/maps/NewBarkTown/scripts.pory"
	end
# 702 "data/maps/NewBarkTown/scripts.pory"

# 703 "data/maps/NewBarkTown/scripts.pory"
@ Mom at (19,12), reachable from (18,12) and (19,13); (19,11) is wall.
# 704 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMom::
# 705 "data/maps/NewBarkTown/scripts.pory"
	lock
# 706 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 707 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomIdle, MSGBOX_DEFAULT
# 708 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 709 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST          @ map.json FACE_RIGHT
# 710 "data/maps/NewBarkTown/scripts.pory"
	release
# 711 "data/maps/NewBarkTown/scripts.pory"
	end
# 712 "data/maps/NewBarkTown/scripts.pory"

# 713 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal at (21,13), reachable from (20,13) and (21,14). They ask to be
# 714 "data/maps/NewBarkTown/scripts.pory"
@ put in the fight HERE, early. The refusal comes later, on camera, in
# 715 "data/maps/NewBarkTown/scripts.pory"
@ NewBarkTown_EventScript_UBRivalIn - and so does the person who overrules
# 716 "data/maps/NewBarkTown/scripts.pory"
@ it. Do not delete any of the three halves.
# 717 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRival::
# 718 "data/maps/NewBarkTown/scripts.pory"
	lock
# 719 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 720 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIdle, MSGBOX_DEFAULT
# 721 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 722 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_NORTH       @ map.json FACE_UP
# 723 "data/maps/NewBarkTown/scripts.pory"
	release
# 724 "data/maps/NewBarkTown/scripts.pory"
	end
# 725 "data/maps/NewBarkTown/scripts.pory"

# 726 "data/maps/NewBarkTown/scripts.pory"
@ Anabel at (22,12). Looker fills (21,12), Azumarill fills (22,13) and
# 727 "data/maps/NewBarkTown/scripts.pory"
@ (22,11) is wall, so the only way to her is the long way round: (20,13) ->
# 728 "data/maps/NewBarkTown/scripts.pory"
@ (20,14) -> east along y=14 -> (23,14) -> (23,13) -> (23,12).
# 729 "data/maps/NewBarkTown/scripts.pory"
@ She plants NOTHING here and she does not explain herself here either. All
# 730 "data/maps/NewBarkTown/scripts.pory"
@ of that happened in Olivine, in the briefing, sitting down, with time -
# 731 "data/maps/NewBarkTown/scripts.pory"
@ which is where the author asked for it. On this road she is working.
# 732 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabel::
# 733 "data/maps/NewBarkTown/scripts.pory"
	lock
# 734 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 735 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 736 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 737 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST       @ map.json FACE_LEFT
# 738 "data/maps/NewBarkTown/scripts.pory"
	release
# 739 "data/maps/NewBarkTown/scripts.pory"
	end
# 740 "data/maps/NewBarkTown/scripts.pory"

# 741 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 742 "data/maps/NewBarkTown/scripts.pory"
@ The cutscene. Everything from the YES onward is scripted through to a
# 743 "data/maps/NewBarkTown/scripts.pory"
@ battle outcome, and then through to the thing that takes the win away.
# 744 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 745 "data/maps/NewBarkTown/scripts.pory"

# 746 "data/maps/NewBarkTown/scripts.pory"
@ Only reachable from (20,12) facing east (see LOOKER'S POCKET above), so no
# 747 "data/maps/NewBarkTown/scripts.pory"
@ getplayerxy check is needed.
# 748 "data/maps/NewBarkTown/scripts.pory"
@ NOTHING changes state before the YES. The YES is the last exit point.
# 749 "data/maps/NewBarkTown/scripts.pory"
@ Elm's countdown is read out BEFORE the YES on purpose - it is the clock
# 750 "data/maps/NewBarkTown/scripts.pory"
@ that turns "three rifts" into "now", the same job Lillie's read did in
# 751 "data/maps/NewBarkTown/scripts.pory"
@ Mission 2 and Kukui's in Mission 3.
# 752 "data/maps/NewBarkTown/scripts.pory"
@ But Elm himself is still at (11,10), nine tiles west and off camera, so
# 753 "data/maps/NewBarkTown/scripts.pory"
@ ANABEL relays his log here and Elm only speaks for himself once he has
# 754 "data/maps/NewBarkTown/scripts.pory"
@ walked into frame in UBScene. Do not move his own voice back up here
# 755 "data/maps/NewBarkTown/scripts.pory"
@ without also moving his object.
# 756 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLooker::
# 757 "data/maps/NewBarkTown/scripts.pory"
	lock
# 758 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 759 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLookerGreet, MSGBOX_DEFAULT
# 760 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBClockRelay, MSGBOX_DEFAULT
# 761 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBReady, MSGBOX_YESNO
# 762 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBNotReady
# 763 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBScene
# 764 "data/maps/NewBarkTown/scripts.pory"

# 765 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNotReady::
# 766 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNotReady, MSGBOX_DEFAULT
# 767 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 768 "data/maps/NewBarkTown/scripts.pory"
	release
# 769 "data/maps/NewBarkTown/scripts.pory"
	end
# 770 "data/maps/NewBarkTown/scripts.pory"

# 771 "data/maps/NewBarkTown/scripts.pory"
@ A simple battle, so there is no party-size check to do, and the mission
# 772 "data/maps/NewBarkTown/scripts.pory"
@ hands out nothing, so the entregar-pokemon-ou-ovo space rule does not apply.
# 773 "data/maps/NewBarkTown/scripts.pory"
@
# 774 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: setobjectxy DOES NOT WORK HERE AND FAILS SILENTLY.
# 775 "data/maps/NewBarkTown/scripts.pory"
@ TryMoveObjectEventToMapCoords (src/event_object_movement.c:3812) only acts
# 776 "data/maps/NewBarkTown/scripts.pory"
@ on a SPAWNED object, and spawning only happens near the camera
# 777 "data/maps/NewBarkTown/scripts.pory"
@ (TrySpawnObjectEvents, :3148). Elm at (11,10) is on the edge of that window
# 778 "data/maps/NewBarkTown/scripts.pory"
@ and Lusamine at (3,12) is far outside it. The template has to be moved
# 779 "data/maps/NewBarkTown/scripts.pory"
@ instead, and the object re-spawned:
# 780 "data/maps/NewBarkTown/scripts.pory"
@   removeobject      - a no-op if it was never spawned; if it WAS spawned it
# 781 "data/maps/NewBarkTown/scripts.pory"
@                       sets only that actor's own FLAG_TEMP_3/4 (which is
# 782 "data/maps/NewBarkTown/scripts.pory"
@                       exactly why those two do not share FLAG_TEMP_1)
# 783 "data/maps/NewBarkTown/scripts.pory"
@   setobjectxyperm   - moves the TEMPLATE; holds while the map stays loaded
# 784 "data/maps/NewBarkTown/scripts.pory"
@   clearflag + addobject - spawns it at the new place
# 785 "data/maps/NewBarkTown/scripts.pory"
@ The order is mandatory and the trio is correct whether or not the actor
# 786 "data/maps/NewBarkTown/scripts.pory"
@ happened to be spawned. Anyone who "simplifies" this into a setobjectxy
# 787 "data/maps/NewBarkTown/scripts.pory"
@ will watch Lusamine never appear, with no error at all.
# 788 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBScene::
# 789 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 790 "data/maps/NewBarkTown/scripts.pory"
	lockall
# 791 "data/maps/NewBarkTown/scripts.pory"
	hidefollower
# 792 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 793 "data/maps/NewBarkTown/scripts.pory"
	@ Elm (11,10) -> (23,12), then faces west at the line of people.
# 794 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_ELM
# 795 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_ELM, 23, 12
# 796 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 797 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_ELM
# 798 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_WEST
# 799 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine (3,12) -> (18,12), then faces east at Mom and the player.
# 800 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_LUSAMINE
# 801 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_LUSAMINE, 18, 12
# 802 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 803 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_LUSAMINE
# 804 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 805 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 806 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBTheyArrive, MSGBOX_DEFAULT
# 807 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 808 "data/maps/NewBarkTown/scripts.pory"
	@ Tremor, then the white flash that brings all three in at once.
# 809 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 2   @ vertical pan
# 810 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 811 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 32  @ num shakes
# 812 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 813 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 814 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 815 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 816 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_2
# 817 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_KARTANA
# 818 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_GUZZLORD
# 819 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NIHILEGO
# 820 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 821 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 822 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 823 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 824 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 825 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 826 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 827 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAppear, MSGBOX_DEFAULT
# 828 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 829 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBSynergy
# 830 "data/maps/NewBarkTown/scripts.pory"

# 831 "data/maps/NewBarkTown/scripts.pory"
@ THE SYNERGY, SHOWN BEFORE IT IS EXPLAINED - the theme of the arc since
# 832 "data/maps/NewBarkTown/scripts.pory"
@ Mission 3, and from here on the house style for every Ultra Beast encounter
# 833 "data/maps/NewBarkTown/scripts.pory"
@ (design section 6, regras comuns).
# 834 "data/maps/NewBarkTown/scripts.pory"
@ It costs three applymovements: all three drift ONE tile east in the same
# 835 "data/maps/NewBarkTown/scripts.pory"
@ instant, from three corners of the map that cannot see each other. Then
# 836 "data/maps/NewBarkTown/scripts.pory"
@ they do it again. Elm is the one who notices it is the SAME instant,
# 837 "data/maps/NewBarkTown/scripts.pory"
@ because he is the only one on the road holding a clock.
# 838 "data/maps/NewBarkTown/scripts.pory"
@ Tiles checked with dump_mapa.py: Kartana (15,10)->(16,10)->(17,10),
# 839 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego (14,13)->(15,13)->(16,13), Guzzlord (23,15)->(24,15)->(25,15).
# 840 "data/maps/NewBarkTown/scripts.pory"
@ All six are walkable and all six stay inside the camera (x 13..27).
# 841 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSynergy::
# 842 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_UBDrift
# 843 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_UBDrift
# 844 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_UBDrift
# 845 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 846 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 847 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 848 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBSynergyFirst, MSGBOX_DEFAULT
# 849 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 850 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_UBDrift
# 851 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_UBDrift
# 852 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_UBDrift
# 853 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 854 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 855 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 856 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBSynergyNamed, MSGBOX_DEFAULT
# 857 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 858 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBLunge
# 859 "data/maps/NewBarkTown/scripts.pory"

# 860 "data/maps/NewBarkTown/scripts.pory"
@ DIRECT DANGER TO THE PLAYER, and the first thing in this mission that
# 861 "data/maps/NewBarkTown/scripts.pory"
@ somebody stops. Nihilego breaks the formation and runs the last three tiles
# 862 "data/maps/NewBarkTown/scripts.pory"
@ of y=13 to (19,13) - diagonally touching the player, directly under Mom,
# 863 "data/maps/NewBarkTown/scripts.pory"
@ who is the one person on this road who was told to go inside and would not.
# 864 "data/maps/NewBarkTown/scripts.pory"
@ The rescue is the Azumarill, and it goes AROUND, on y=14, because nothing
# 865 "data/maps/NewBarkTown/scripts.pory"
@ is ever parked at (20,13). (22,13) -> (22,14) -> (21,14) -> (20,14) ->
# 866 "data/maps/NewBarkTown/scripts.pory"
@ (19,14), facing north at the thing. The two paths never share a tile.
# 867 "data/maps/NewBarkTown/scripts.pory"
@ This beat is why Lusamine says what she says next. Do not reorder them.
# 868 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLunge::
# 869 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 870 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, Common_Movement_ExclamationMark
# 871 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 872 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_NihilegoLunge
# 873 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillCutOff
# 874 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 875 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 876 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 877 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBCutOff, MSGBOX_DEFAULT
# 878 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 879 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBKnot
# 880 "data/maps/NewBarkTown/scripts.pory"

# 881 "data/maps/NewBarkTown/scripts.pory"
@ The knot: Lusamine means to take all three, and Mom is the one who stops
# 882 "data/maps/NewBarkTown/scripts.pory"
@ her. The closemessage above is load-bearing - without it Lusamine's step
# 883 "data/maps/NewBarkTown/scripts.pory"
@ would play behind an open text box.
# 884 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBKnot::
# 885 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine (18,12) -> (17,12), one step west toward the rifts. (17,12) is
# 886 "data/maps/NewBarkTown/scripts.pory"
	@ clear and still well inside the camera (x >= 13 with the player at 20).
# 887 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_StepLeftFaceLeft
# 888 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 889 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineTakesThree, MSGBOX_DEFAULT
# 890 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 891 "data/maps/NewBarkTown/scripts.pory"
	@ Mom (19,12) turns her back on her own child to face Lusamine at (17,12).
# 892 "data/maps/NewBarkTown/scripts.pory"
	@ x 17 < 19, so west. The turn IS the beat - do not shorten it away.
# 893 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
# 894 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomStopsHer, MSGBOX_DEFAULT
# 895 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 896 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 897 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineAsks, MSGBOX_DEFAULT
# 898 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 899 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBPlan
# 900 "data/maps/NewBarkTown/scripts.pory"

# 901 "data/maps/NewBarkTown/scripts.pory"
@ Anabel answers the question, and answering it costs her something: three
# 902 "data/maps/NewBarkTown/scripts.pory"
@ rifts open at once is more than she can stand in front of quietly. Looker
# 903 "data/maps/NewBarkTown/scripts.pory"
@ is at (21,12) and she is at (22,12), right beside him, so he does not need
# 904 "data/maps/NewBarkTown/scripts.pory"
@ to walk to catch her. x 22 > 21 -> east to her, x 20 < 21 -> west to come
# 905 "data/maps/NewBarkTown/scripts.pory"
@ back to the player.
# 906 "data/maps/NewBarkTown/scripts.pory"
@ SHE DOES NOT EXPLAIN HERSELF HERE. The author was explicit: the Faller
# 907 "data/maps/NewBarkTown/scripts.pory"
@ conversation does not belong in the middle of a fight. It happens in
# 908 "data/maps/NewBarkTown/scripts.pory"
@ Olivine, in the briefing, before any of this - Text_BriefingM4 in
# 909 "data/maps/NewBarkTown/scripts.pory"
@ data/maps/OlivineCity_House1/scripts.pory - and it comes back once, at the
# 910 "data/maps/NewBarkTown/scripts.pory"
@ end, when everyone is standing on the road again (UBAnabelPromise). Two
# 911 "data/maps/NewBarkTown/scripts.pory"
@ boxes here, and she is back at work in the third.
# 912 "data/maps/NewBarkTown/scripts.pory"
@ What she gives the scene instead is the COUNTER, and the counter is what
# 913 "data/maps/NewBarkTown/scripts.pory"
@ turns the standard pick-one-Ultra-Beast menu into a plan: three things that
# 914 "data/maps/NewBarkTown/scripts.pory"
@ move in one instant have to be broken in one instant, and that needs a
# 915 "data/maps/NewBarkTown/scripts.pory"
@ fourth pair of hands.
# 916 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPlan::
# 917 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelBreaks, MSGBOX_DEFAULT
# 918 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 919 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 920 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, Common_Movement_ExclamationMark
# 921 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 922 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_EAST
# 923 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 924 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelStands, MSGBOX_DEFAULT
# 925 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 926 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST      @ back to the player
# 927 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBCounter, MSGBOX_DEFAULT
# 928 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 929 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalIn
# 930 "data/maps/NewBarkTown/scripts.pory"

# 931 "data/maps/NewBarkTown/scripts.pory"
@ Pays off the idle line: Gold/Crystal asked to be put in the fight, so the
# 932 "data/maps/NewBarkTown/scripts.pory"
@ answer has to happen on camera or the promise is dropped. The answer is no,
# 933 "data/maps/NewBarkTown/scripts.pory"
@ for a reason that is about them and not about the plan - and then the plan
# 934 "data/maps/NewBarkTown/scripts.pory"
@ needs four, and the person who overrules the no is LUSAMINE, thirty seconds
# 935 "data/maps/NewBarkTown/scripts.pory"
@ after being told that deciding for everybody is not protection. That is the
# 936 "data/maps/NewBarkTown/scripts.pory"
@ whole point of the scene: Mom teaches her to ask, and the first thing she
# 937 "data/maps/NewBarkTown/scripts.pory"
@ does with it is believe in somebody else's kid.
# 938 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal sit at (21,13), diagonally below-right of the player at
# 939 "data/maps/NewBarkTown/scripts.pory"
@ (20,12). There is no cardinal direction that points at the player, so they
# 940 "data/maps/NewBarkTown/scripts.pory"
@ turn WEST - onto the player's column - which reads as turning to them.
# 941 "data/maps/NewBarkTown/scripts.pory"
@ Nobody is at (20,13), so nothing is hidden behind the text box.
# 942 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalIn::
# 943 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_WEST
# 944 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalAsks, MSGBOX_DEFAULT
# 945 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 946 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalRefused, MSGBOX_DEFAULT
# 947 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 948 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineLetsHimIn, MSGBOX_DEFAULT
# 949 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 950 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 951 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, Common_Movement_ExclamationMark
# 952 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 953 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIn, MSGBOX_DEFAULT
# 954 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 955 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBChoose
# 956 "data/maps/NewBarkTown/scripts.pory"

# 957 "data/maps/NewBarkTown/scripts.pory"
@ Standard Rift Mission structure: the player picks which Ultra Beast to
# 958 "data/maps/NewBarkTown/scripts.pory"
@ fight and the companions take the rest. No cancel (ignoreBPress TRUE) - the
# 959 "data/maps/NewBarkTown/scripts.pory"
@ scene has already started, so VAR_RESULT can only be 0, 1 or 2.
# 960 "data/maps/NewBarkTown/scripts.pory"
@ maxBeforeScroll 3 so all three fit without scrolling. dynmultichoice takes
# 961 "data/maps/NewBarkTown/scripts.pory"
@ a vararg list (asm/macros/event.inc:1942), so three items need nothing new.
# 962 "data/maps/NewBarkTown/scripts.pory"
@ The pick is per attempt: after a blackout the player chooses again.
# 963 "data/maps/NewBarkTown/scripts.pory"
@
# 964 "data/maps/NewBarkTown/scripts.pory"
@ DISTRIBUTION - design section 6.4. Lusamine keeps Nihilego whenever the
# 965 "data/maps/NewBarkTown/scripts.pory"
@ player does not take it; it is the one she came for and the one she has to
# 966 "data/maps/NewBarkTown/scripts.pory"
@ answer for. This is a character decision, not convenience:
# 967 "data/maps/NewBarkTown/scripts.pory"
@   pick 0 Kartana   -> Lusamine Nihilego, Anabel Guzzlord
# 968 "data/maps/NewBarkTown/scripts.pory"
@   pick 1 Guzzlord  -> Lusamine Nihilego, Anabel Kartana
# 969 "data/maps/NewBarkTown/scripts.pory"
@   pick 2 Nihilego  -> Lusamine Guzzlord, Anabel Kartana
# 970 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal are the fourth pair of hands on whichever one the player
# 971 "data/maps/NewBarkTown/scripts.pory"
@ takes: four people, three beasts, one instant.
# 972 "data/maps/NewBarkTown/scripts.pory"
@ Each UBPicked* line SAYS which two the others take, so the table is
# 973 "data/maps/NewBarkTown/scripts.pory"
@ readable from inside the game and not only from this comment.
# 974 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBChoose::
# 975 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 976 "data/maps/NewBarkTown/scripts.pory"
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_Text_ChoiceKartana, NewBarkTown_Text_ChoiceGuzzlord, NewBarkTown_Text_ChoiceNihilego
# 977 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 Kartana, 1 Guzzlord, 2 Nihilego
# 978 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 979 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPickGuzzlord
# 980 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPickNihilego
# 981 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
# 982 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 983 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedKartana, MSGBOX_DEFAULT
# 984 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 985 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 986 "data/maps/NewBarkTown/scripts.pory"

# 987 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickGuzzlord::
# 988 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
# 989 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 990 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedGuzzlord, MSGBOX_DEFAULT
# 991 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 992 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 993 "data/maps/NewBarkTown/scripts.pory"

# 994 "data/maps/NewBarkTown/scripts.pory"
@ The one branch where Lusamine loses the beast she came for. ONE line, and
# 995 "data/maps/NewBarkTown/scripts.pory"
@ she takes it - design section 6.4. Do not turn this into an argument.
# 996 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickNihilego::
# 997 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
# 998 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 999 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedNihilego, MSGBOX_DEFAULT
# 1000 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1001 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 1002 "data/maps/NewBarkTown/scripts.pory"

# 1003 "data/maps/NewBarkTown/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 1004 "data/maps/NewBarkTown/scripts.pory"
@ battle - the other reason every mission splits the beasts up.
# 1005 "data/maps/NewBarkTown/scripts.pory"
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
# 1006 "data/maps/NewBarkTown/scripts.pory"
@ losing means a blackout and a retry. Running is not blocked either - "Run"
# 1007 "data/maps/NewBarkTown/scripts.pory"
@ in a boss is explicit forfeiting (CanPlayerForfeitBattle, src/battle_main.c)
# 1008 "data/maps/NewBarkTown/scripts.pory"
@ and becomes B_OUTCOME_FORFEITED, which counts as a loss.
# 1009 "data/maps/NewBarkTown/scripts.pory"
@
# 1010 "data/maps/NewBarkTown/scripts.pory"
@ NOT a skeleton: the numbers below are the target. Fourth step of the ladder
# 1011 "data/maps/NewBarkTown/scripts.pory"
@ after Blackthorn (2 bars / Lv70 / x110), Mahogany (4 / Lv80 / x130) and
# 1012 "data/maps/NewBarkTown/scripts.pory"
@ Cherrygrove (4 / Lv85 / x140). The bars have been at MAX_BOSS_HEALTH_BARS
# 1013 "data/maps/NewBarkTown/scripts.pory"
@ since Mission 2, so the step up here is level, multiplier and a two-axis
# 1014 "data/maps/NewBarkTown/scripts.pory"
@ moveset plus a held item.
# 1015 "data/maps/NewBarkTown/scripts.pory"
@ CAVEAT (design section 6): x140 has never actually been played. If the
# 1016 "data/maps/NewBarkTown/scripts.pory"
@ Mission 3 playtest says x140 is already a wall, THIS number inherits the
# 1017 "data/maps/NewBarkTown/scripts.pory"
@ correction instead of going up. Turn the screws in this order, one at a
# 1018 "data/maps/NewBarkTown/scripts.pory"
@ time:
# 1019 "data/maps/NewBarkTown/scripts.pory"
@   1. drop the held item from the boss that gets complained about
# 1020 "data/maps/NewBarkTown/scripts.pory"
@   2. multiplier 150 -> 145 -> 140
# 1021 "data/maps/NewBarkTown/scripts.pory"
@   3. swap the setup/control move for a fourth attacking move
# 1022 "data/maps/NewBarkTown/scripts.pory"
@   4. level 90 -> 85
# 1023 "data/maps/NewBarkTown/scripts.pory"
@ The bars are at the ceiling and are not a screw.
# 1024 "data/maps/NewBarkTown/scripts.pory"
@
# 1025 "data/maps/NewBarkTown/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 1026 "data/maps/NewBarkTown/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 1027 "data/maps/NewBarkTown/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between, so no
# 1028 "data/maps/NewBarkTown/scripts.pory"
@ clearbossbattle is needed.
# 1029 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBattle::
# 1030 "data/maps/NewBarkTown/scripts.pory"
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
# 1031 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBSetupGuzzlord
# 1032 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBSetupNihilego
# 1033 "data/maps/NewBarkTown/scripts.pory"
	@ Kartana - the one that CLIMBS. Paper defenses, Swords Dance, a pure
# 1034 "data/maps/NewBarkTown/scripts.pory"
	@ damage item: it either snowballs or it dies.
# 1035 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1036 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 1037 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1038 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_KARTANA, 90, ITEM_MUSCLE_BAND
# 1039 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_SACRED_SWORD, MOVE_SMART_STRIKE
# 1040 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 1041 "data/maps/NewBarkTown/scripts.pory"

# 1042 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord - the one that ENDURES. Absurd HP, Leftovers and Toxic: attrition.
# 1043 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupGuzzlord::
# 1044 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1045 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 1046 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1047 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_GUZZLORD, 90, ITEM_LEFTOVERS
# 1048 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_TOXIC, MOVE_CRUNCH, MOVE_HEAVY_SLAM, MOVE_DRAGON_TAIL
# 1049 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 1050 "data/maps/NewBarkTown/scripts.pory"

# 1051 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego - the one that INTERFERES. Acid Spray shreds the player's Sp.Def,
# 1052 "data/maps/NewBarkTown/scripts.pory"
@ Toxic stacks on top, and Black Sludge heals it for being Poison.
# 1053 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupNihilego::
# 1054 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1055 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 1056 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1057 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_NIHILEGO, 90, ITEM_BLACK_SLUDGE
# 1058 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_ACID_SPRAY, MOVE_TOXIC, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE
# 1059 "data/maps/NewBarkTown/scripts.pory"

# 1060 "data/maps/NewBarkTown/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the
# 1061 "data/maps/NewBarkTown/scripts.pory"
@ player out and hands them back HEALED at (20,12) (DoWhiteOut calls
# 1062 "data/maps/NewBarkTown/scripts.pory"
@ HealPlayerParty itself, src/overworld.c:384; it does not need a Center
# 1063 "data/maps/NewBarkTown/scripts.pory"
@ counter, and New Bark has no Center at all). CAUGHT and RAN are unreachable
# 1064 "data/maps/NewBarkTown/scripts.pory"
@ (ball blocked; Run becomes FORFEITED in a boss) but are handled anyway:
# 1065 "data/maps/NewBarkTown/scripts.pory"
@ anything that is not WON restarts the scene, and nothing wins it by default.
# 1066 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBStartBattle::
# 1067 "data/maps/NewBarkTown/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 1068 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1069 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 1070 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 1071 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, NewBarkTown_EventScript_UBResolved
# 1072 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUnresolved
# 1073 "data/maps/NewBarkTown/scripts.pory"

# 1074 "data/maps/NewBarkTown/scripts.pory"
@ Nothing was recorded as done: the event flag is still set, so reloading the
# 1075 "data/maps/NewBarkTown/scripts.pory"
@ map puts the cast back on its map.json tiles with the beasts hidden again,
# 1076 "data/maps/NewBarkTown/scripts.pory"
@ and talking to Looker restarts the whole scene - the pick included. The warp
# 1077 "data/maps/NewBarkTown/scripts.pory"
@ also puts Elm and Lusamine back on their original template coordinates,
# 1078 "data/maps/NewBarkTown/scripts.pory"
@ because LoadMapFromWarp re-reads the templates, and it undoes every step of
# 1079 "data/maps/NewBarkTown/scripts.pory"
@ choreography above, because those only live in the loaded map.
# 1080 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUnresolved::
# 1081 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBGotAway, MSGBOX_DEFAULT
# 1082 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1083 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1084 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 1085 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1086 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1087 "data/maps/NewBarkTown/scripts.pory"
	end
# 1088 "data/maps/NewBarkTown/scripts.pory"

# 1089 "data/maps/NewBarkTown/scripts.pory"
@ The plan worked. Lusamine's fight, Anabel's and Gold/Crystal's are
# 1090 "data/maps/NewBarkTown/scripts.pory"
@ narrative: they resolve with the player's win, and the lines change with
# 1091 "data/maps/NewBarkTown/scripts.pory"
@ the pick so the four-way split is legible from inside the game.
# 1092 "data/maps/NewBarkTown/scripts.pory"
@ THE THREE BEASTS ARE NOT REMOVED HERE. They are down, not gone, and they
# 1093 "data/maps/NewBarkTown/scripts.pory"
@ have to still be standing on the road for what comes to collect them.
# 1094 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBResolved::
# 1095 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAfterGuzzlord
# 1096 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBAfterNihilego
# 1097 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterKartana, MSGBOX_DEFAULT
# 1098 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBNecrozmaArrives
# 1099 "data/maps/NewBarkTown/scripts.pory"

# 1100 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterGuzzlord::
# 1101 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterGuzzlord, MSGBOX_DEFAULT
# 1102 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBNecrozmaArrives
# 1103 "data/maps/NewBarkTown/scripts.pory"

# 1104 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterNihilego::
# 1105 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterNihilego, MSGBOX_DEFAULT
# 1106 "data/maps/NewBarkTown/scripts.pory"

# 1107 "data/maps/NewBarkTown/scripts.pory"
@ THE CONSEQUENCE. Same entrance the creature has used in all three previous
# 1108 "data/maps/NewBarkTown/scripts.pory"
@ missions - shake, white flash, object - but this time it walks out onto the
# 1109 "data/maps/NewBarkTown/scripts.pory"
@ road itself, at (16,12), one tile west of Lusamine, in the middle of the
# 1110 "data/maps/NewBarkTown/scripts.pory"
@ street it has been opening for four missions.
# 1111 "data/maps/NewBarkTown/scripts.pory"
@ Its flag is FLAG_TEMP_5, its own, so nothing else's removeobject can touch
# 1112 "data/maps/NewBarkTown/scripts.pory"
@ it and so the ON_TRANSITION setflag hides it again on any reload.
# 1113 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNecrozmaArrives::
# 1114 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1115 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1116 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1117 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_5
# 1118 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NECROZMA
# 1119 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1120 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1121 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1122 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
# 1123 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1124 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalFights
# 1125 "data/maps/NewBarkTown/scripts.pory"

# 1126 "data/maps/NewBarkTown/scripts.pory"
@ The kid goes at it. Nobody told them to, and this time nobody gets to tell
# 1127 "data/maps/NewBarkTown/scripts.pory"
@ them not to - they were let in thirty seconds ago and this is what being
# 1128 "data/maps/NewBarkTown/scripts.pory"
@ let in looks like to somebody who has spent the whole game feeling like
# 1129 "data/maps/NewBarkTown/scripts.pory"
@ the spare part.
# 1130 "data/maps/NewBarkTown/scripts.pory"
@ Azumarill (19,14) -> (18,14) -> (17,14) -> (16,14), two tiles south of the
# 1131 "data/maps/NewBarkTown/scripts.pory"
@ creature, faces north, hits it twice. Then it is thrown back to (18,14),
# 1132 "data/maps/NewBarkTown/scripts.pory"
@ still facing the thing, because it does not turn around.
# 1133 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalFights::
# 1134 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalCharges, MSGBOX_DEFAULT
# 1135 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1136 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillCharge
# 1137 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1138 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_AZUMARILL, CRY_MODE_ENCOUNTER
# 1139 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_StrikeUp
# 1140 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1141 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1142 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFlash
# 1143 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillThrown
# 1144 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1145 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1146 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalRepelled, MSGBOX_DEFAULT
# 1147 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1148 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAbsorb
# 1149 "data/maps/NewBarkTown/scripts.pory"

# 1150 "data/maps/NewBarkTown/scripts.pory"
@ It eats them. Same pattern as Missions 1, 2 and 3 - pulse, the beasts
# 1151 "data/maps/NewBarkTown/scripts.pory"
@ dragged backwards toward it, flash, removeobject - except that this time
# 1152 "data/maps/NewBarkTown/scripts.pory"
@ there are three, and this time somebody on the road does the arithmetic
# 1153 "data/maps/NewBarkTown/scripts.pory"
@ out loud afterwards.
# 1154 "data/maps/NewBarkTown/scripts.pory"
@ Drag paths, all measured: Kartana (17,10) -> (16,10) -> (16,11), which puts
# 1155 "data/maps/NewBarkTown/scripts.pory"
@ it directly north of the creature; Nihilego (19,13) -> (18,13) -> (17,13);
# 1156 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord (25,15) -> (24,15) -> (23,15). Every tile walkable, every path
# 1157 "data/maps/NewBarkTown/scripts.pory"
@ pointed at (16,12), and none of the three crosses another.
# 1158 "data/maps/NewBarkTown/scripts.pory"
@ Their flag is FLAG_TEMP_2, shared, and that is fine: all three go at once.
# 1159 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAbsorb::
# 1160 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_NecrozmaPulse
# 1161 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
# 1162 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1163 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1164 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_KartanaPulledIn
# 1165 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_UBPulledInWest
# 1166 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_UBPulledInWest
# 1167 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1168 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1169 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1170 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1171 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1172 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_KARTANA
# 1173 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_GUZZLORD
# 1174 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NIHILEGO
# 1175 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1176 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1177 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1178 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAbsorbed, MSGBOX_DEFAULT
# 1179 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1180 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUltra
# 1181 "data/maps/NewBarkTown/scripts.pory"

# 1182 "data/maps/NewBarkTown/scripts.pory"
@ What it becomes. The creature is removed and the other object is added on
# 1183 "data/maps/NewBarkTown/scripts.pory"
@ the SAME tile (16,12) under one flash - the two are never spawned at the
# 1184 "data/maps/NewBarkTown/scripts.pory"
@ same time, which is why the peak object count of this scene is 13 and not
# 1185 "data/maps/NewBarkTown/scripts.pory"
@ 14, and why each of them needs its own FLAG_TEMP.
# 1186 "data/maps/NewBarkTown/scripts.pory"
@ Then the four of them do exactly what worked ten seconds ago - the same
# 1187 "data/maps/NewBarkTown/scripts.pory"
@ instant, the same plan - and it does not matter at all. That is the whole
# 1188 "data/maps/NewBarkTown/scripts.pory"
@ point: the counter that beat the beasts is nothing to the thing that was
# 1189 "data/maps/NewBarkTown/scripts.pory"
@ collecting them.
# 1190 "data/maps/NewBarkTown/scripts.pory"
@ All four face west at (16,12): Lusamine (17,12), the player (20,12),
# 1191 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal (21,13), Anabel (22,12).
# 1192 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltra::
# 1193 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1194 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1195 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NECROZMA
# 1196 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_6
# 1197 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1198 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1199 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
# 1200 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1201 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraRises, MSGBOX_DEFAULT
# 1202 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1203 "data/maps/NewBarkTown/scripts.pory"
	@ Four at once, the same way they broke the three.
# 1204 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_StrikeWest
# 1205 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_StrikeWest
# 1206 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, NewBarkTown_Movement_StrikeWest
# 1207 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_StrikeWest
# 1208 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 1209 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 1210 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 1211 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1212 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFlare
# 1213 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1214 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1215 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1216 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 3   @ vertical pan
# 1217 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 2   @ horizontal pan
# 1218 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 48  @ num shakes
# 1219 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 3   @ shake delay
# 1220 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 1221 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1222 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraBreaksThem, MSGBOX_DEFAULT
# 1223 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1224 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBUltraSensesCosmog
# 1225 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUltraLeaves
# 1226 "data/maps/NewBarkTown/scripts.pory"

# 1227 "data/maps/NewBarkTown/scripts.pory"
@ OPTIONAL, STATELESS reaction to the Cosmog family in the party - design
# 1228 "data/maps/NewBarkTown/scripts.pory"
@ section 4.11, same shape as Mission 3's. Checked HERE and not before the
# 1229 "data/maps/NewBarkTown/scripts.pory"
@ battle on purpose: the battle can evolve the Pokemon. The answer is kept
# 1230 "data/maps/NewBarkTown/scripts.pory"
@ in VAR_TEMP_4 and re-read by the closing conversation, so Lusamine's last
# 1231 "data/maps/NewBarkTown/scripts.pory"
@ box lines up with what actually happened.
# 1232 "data/maps/NewBarkTown/scripts.pory"
@ Without the Pokemon nothing is missing from the scene and nothing is spent:
# 1233 "data/maps/NewBarkTown/scripts.pory"
@ no flag, no persistent var.
# 1234 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltraSensesCosmog::
# 1235 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 1236 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_4, VAR_RESULT
# 1237 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, NewBarkTown_EventScript_UBCosmogEnd
# 1238 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1239 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
# 1240 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1241 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFlare
# 1242 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1243 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_NORMAL
# 1244 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1245 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, NewBarkTown_EventScript_UBCosmogLegend
# 1246 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, NewBarkTown_EventScript_UBCosmogLegend
# 1247 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraSensesCosmog, MSGBOX_DEFAULT
# 1248 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1249 "data/maps/NewBarkTown/scripts.pory"
	return
# 1250 "data/maps/NewBarkTown/scripts.pory"

# 1251 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBCosmogLegend::
# 1252 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraSensesLegend, MSGBOX_DEFAULT
# 1253 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1254 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBCosmogEnd::
# 1255 "data/maps/NewBarkTown/scripts.pory"
	return
# 1256 "data/maps/NewBarkTown/scripts.pory"

# 1257 "data/maps/NewBarkTown/scripts.pory"
@ It leaves the way it arrived, and nobody stops it. Its flag is FLAG_TEMP_6,
# 1258 "data/maps/NewBarkTown/scripts.pory"
@ its own, so the removeobject touches nothing else.
# 1259 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltraLeaves::
# 1260 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1261 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1262 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1263 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1264 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraGone, MSGBOX_DEFAULT
# 1265 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1266 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAftermath
# 1267 "data/maps/NewBarkTown/scripts.pory"

# 1268 "data/maps/NewBarkTown/scripts.pory"
@ The town stands and the mission is lost, and the order of the boxes is the
# 1269 "data/maps/NewBarkTown/scripts.pory"
@ argument: the people first (Looker, always), then the cost, then what it
# 1270 "data/maps/NewBarkTown/scripts.pory"
@ actually was, then the three who have to live in this town, then the
# 1271 "data/maps/NewBarkTown/scripts.pory"
@ promise that is the only thing anybody still has, then the hook.
# 1272 "data/maps/NewBarkTown/scripts.pory"
@ Nobody walks: everyone is already on the line and nobody is at (20,13), so
# 1273 "data/maps/NewBarkTown/scripts.pory"
@ the text box hides no one. Azumarill is at (18,14) and Lusamine at (17,12),
# 1274 "data/maps/NewBarkTown/scripts.pory"
@ where the fight left them, which is the picture the scene wants.
# 1275 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermath::
# 1276 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathHurt, MSGBOX_DEFAULT
# 1277 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1278 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmCost, MSGBOX_DEFAULT
# 1279 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1280 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBWhatItWas, MSGBOX_DEFAULT
# 1281 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1282 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineLost, MSGBOX_DEFAULT
# 1283 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1284 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_WEST     @ onto the player's column
# 1285 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRival, MSGBOX_DEFAULT
# 1286 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1287 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST       @ back to facing her child
# 1288 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMom, MSGBOX_DEFAULT
# 1289 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1290 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelPromise, MSGBOX_DEFAULT
# 1291 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1292 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAftermathCosmog
# 1293 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBHook, MSGBOX_DEFAULT
# 1294 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1295 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1296 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_NEWBARK   @ invariant: flag and var together
# 1297 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 10
# 1298 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_DAILY_LOOKER_CALL            @ he just said it in person
# 1299 "data/maps/NewBarkTown/scripts.pory"
	@ Reload in place under the fade. The seven residents come back, the lamps
# 1300 "data/maps/NewBarkTown/scripts.pory"
	@ go back to depending on the clock alone, the cast disappears, Elm and
# 1301 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine return to their template tiles, and the follower comes back
# 1302 "data/maps/NewBarkTown/scripts.pory"
	@ (undoing the hidefollower). Without this the whole town would pop back
# 1303 "data/maps/NewBarkTown/scripts.pory"
	@ in piece by piece as the camera moved.
# 1304 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 1305 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1306 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1307 "data/maps/NewBarkTown/scripts.pory"
	end
# 1308 "data/maps/NewBarkTown/scripts.pory"

# 1309 "data/maps/NewBarkTown/scripts.pory"
@ Re-reads what UBUltraSensesCosmog sampled. Design section 6.4: Lusamine is
# 1310 "data/maps/NewBarkTown/scripts.pory"
@ the only living person who knows what that light looks like from the other
# 1311 "data/maps/NewBarkTown/scripts.pory"
@ side, because she used one. She says it without being asked, and she says
# 1312 "data/maps/NewBarkTown/scripts.pory"
@ the other half of it too - that none of this is the player's doing.
# 1313 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermathCosmog::
# 1314 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, NewBarkTown_EventScript_UBAftermathCosmogEnd
# 1315 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1316 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathCosmog, MSGBOX_DEFAULT
# 1317 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1318 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermathCosmogEnd::
# 1319 "data/maps/NewBarkTown/scripts.pory"
	return
# 1320 "data/maps/NewBarkTown/scripts.pory"

# 1321 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepLeftFaceLeft:
# 1322 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1323 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 1324 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1325 "data/maps/NewBarkTown/scripts.pory"

# 1326 "data/maps/NewBarkTown/scripts.pory"
@ One tile east, slowly, and all three do it in the same frame.
# 1327 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UBDrift:
# 1328 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_right
# 1329 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1330 "data/maps/NewBarkTown/scripts.pory"

# 1331 "data/maps/NewBarkTown/scripts.pory"
@ (16,13) -> (19,13), the last three tiles between it and the player.
# 1332 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_NihilegoLunge:
# 1333 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1334 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1335 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1336 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1337 "data/maps/NewBarkTown/scripts.pory"

# 1338 "data/maps/NewBarkTown/scripts.pory"
@ (22,13) -> (22,14) -> (21,14) -> (20,14) -> (19,14), facing north. Around
# 1339 "data/maps/NewBarkTown/scripts.pory"
@ the outside, never through (20,13).
# 1340 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillCutOff:
# 1341 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 1342 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1343 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1345 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1346 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1347 "data/maps/NewBarkTown/scripts.pory"

# 1348 "data/maps/NewBarkTown/scripts.pory"
@ (19,14) -> (16,14), two tiles south of the creature, facing it.
# 1349 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillCharge:
# 1350 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1351 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1352 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1353 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1354 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1355 "data/maps/NewBarkTown/scripts.pory"

# 1356 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StrikeUp:
# 1357 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_up
# 1358 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_up
# 1359 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1360 "data/maps/NewBarkTown/scripts.pory"

# 1361 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StrikeWest:
# 1362 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 1363 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 1364 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1365 "data/maps/NewBarkTown/scripts.pory"

# 1366 "data/maps/NewBarkTown/scripts.pory"
@ (16,14) -> (18,14) without turning around.
# 1367 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillThrown:
# 1368 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 1369 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1370 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1371 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 1372 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1373 "data/maps/NewBarkTown/scripts.pory"

# 1374 "data/maps/NewBarkTown/scripts.pory"
@ Dragged backwards, two tiles, still facing away from what is pulling.
# 1375 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UBPulledInWest:
# 1376 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 1377 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_left
# 1378 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_left
# 1379 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 1380 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1381 "data/maps/NewBarkTown/scripts.pory"

# 1382 "data/maps/NewBarkTown/scripts.pory"
@ Kartana comes down the side of the lab: (17,10) -> (16,10) -> (16,11).
# 1383 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_KartanaPulledIn:
# 1384 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 1385 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_left
# 1386 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_down
# 1387 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 1388 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1389 "data/maps/NewBarkTown/scripts.pory"

# 1390 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_NecrozmaPulse:
# 1391 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1392 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1393 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1394 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1395 "data/maps/NewBarkTown/scripts.pory"

# 1396 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UltraFlare:
# 1397 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1398 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1399 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1400 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1401 "data/maps/NewBarkTown/scripts.pory"
	step_end

# 1404 "data/maps/NewBarkTown/scripts.pory"

# 1405 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 1406 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 dialogue.
# 1407 "data/maps/NewBarkTown/scripts.pory"
@ Voices: design section 3.1. Looker theatrical, formal in a personal way,
# 1408 "data/maps/NewBarkTown/scripts.pory"
@ and asks about the people before the report. Anabel precise, separating
# 1409 "data/maps/NewBarkTown/scripts.pory"
@ observation from hypothesis. Lusamine elaborate, used to deciding, learning
# 1410 "data/maps/NewBarkTown/scripts.pory"
@ to ask. Elm humble and specific. Mom plain, short, no speeches.
# 1411 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal: NO speaker plaque anywhere, ever - the two texts have to
# 1412 "data/maps/NewBarkTown/scripts.pory"
@ serve both of them. When a rival line follows a named line inside the SAME
# 1413 "data/maps/NewBarkTown/scripts.pory"
@ box it opens with {SPEAKER NAME_NONE}, or it would inherit the plaque above
# 1414 "data/maps/NewBarkTown/scripts.pory"
@ it and put somebody else's name over the kid's words.
# 1415 "data/maps/NewBarkTown/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 1416 "data/maps/NewBarkTown/scripts.pory"
@ UBHook is the hook into the Olivine reunion (design section 7) - it is what
# 1417 "data/maps/NewBarkTown/scripts.pory"
@ the next document picks up.
# 1418 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 1419 "data/maps/NewBarkTown/scripts.pory"

# 1420 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineIdle:
# 1421 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}You are taller than\n"
# 1422 "data/maps/NewBarkTown/scripts.pory"
	.string "the photographs.\p"
# 1423 "data/maps/NewBarkTown/scripts.pory"
	.string "…Forgive me. I have practiced\n"
# 1424 "data/maps/NewBarkTown/scripts.pory"
	.string "this, and I am still doing it\l"
# 1425 "data/maps/NewBarkTown/scripts.pory"
	.string "badly.\p"
# 1426 "data/maps/NewBarkTown/scripts.pory"
	.string "Lillie writes about you.\p"
# 1427 "data/maps/NewBarkTown/scripts.pory"
	.string "Gladion does not write, but he\n"
# 1428 "data/maps/NewBarkTown/scripts.pory"
	.string "mentions you, which from him is\l"
# 1429 "data/maps/NewBarkTown/scripts.pory"
	.string "the same thing.\p"
# 1430 "data/maps/NewBarkTown/scripts.pory"
	.string "Nobody sent for me. I read the\n"
# 1431 "data/maps/NewBarkTown/scripts.pory"
	.string "same numbers they did and I got\l"
# 1432 "data/maps/NewBarkTown/scripts.pory"
	.string "in a boat.\p"
# 1433 "data/maps/NewBarkTown/scripts.pory"
	.string "We will talk properly when this\n"
# 1434 "data/maps/NewBarkTown/scripts.pory"
	.string "is over.\p"
# 1435 "data/maps/NewBarkTown/scripts.pory"
	.string "If I am still someone you want\n"
# 1436 "data/maps/NewBarkTown/scripts.pory"
	.string "to talk to.$"
# 1437 "data/maps/NewBarkTown/scripts.pory"

# 1438 "data/maps/NewBarkTown/scripts.pory"
@ Optional. Design section 6.4: she is the only living person who knows what
# 1439 "data/maps/NewBarkTown/scripts.pory"
@ that light looks like from the other side. And the rule that cannot be
# 1440 "data/maps/NewBarkTown/scripts.pory"
@ broken - she says out loud that none of it is the player's doing.
# 1441 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineIdleCosmog:
# 1442 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…Oh.\p"
# 1443 "data/maps/NewBarkTown/scripts.pory"
	.string "Oh, you brought it with you.\p"
# 1444 "data/maps/NewBarkTown/scripts.pory"
	.string "{STR_VAR_1} is standing on a\n"
# 1445 "data/maps/NewBarkTown/scripts.pory"
	.string "road with three tears over it,\l"
# 1446 "data/maps/NewBarkTown/scripts.pory"
	.string "and it is not frightened.\p"
# 1447 "data/maps/NewBarkTown/scripts.pory"
	.string "I knew one of those, once.\p"
# 1448 "data/maps/NewBarkTown/scripts.pory"
	.string "I did not deserve it, and I\n"
# 1449 "data/maps/NewBarkTown/scripts.pory"
	.string "used it, and I would like you\l"
# 1450 "data/maps/NewBarkTown/scripts.pory"
	.string "to hear the next part from me\l"
# 1451 "data/maps/NewBarkTown/scripts.pory"
	.string "before anyone else says it.\p"
# 1452 "data/maps/NewBarkTown/scripts.pory"
	.string "They shine. Things on the other\n"
# 1453 "data/maps/NewBarkTown/scripts.pory"
	.string "side can see that.\p"
# 1454 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not your fault and it\n"
# 1455 "data/maps/NewBarkTown/scripts.pory"
	.string "never was.\p"
# 1456 "data/maps/NewBarkTown/scripts.pory"
	.string "It is why I came.$"
# 1457 "data/maps/NewBarkTown/scripts.pory"

# 1458 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmIdle:
# 1459 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Six weeks.\p"
# 1460 "data/maps/NewBarkTown/scripts.pory"
	.string "Six weeks of the same reading,\n"
# 1461 "data/maps/NewBarkTown/scripts.pory"
	.string "and every time I wrote “check\l"
# 1462 "data/maps/NewBarkTown/scripts.pory"
	.string "the sensor” in the margin.\p"
# 1463 "data/maps/NewBarkTown/scripts.pory"
	.string "Then Cherrygrove was in the\n"
# 1464 "data/maps/NewBarkTown/scripts.pory"
	.string "morning paper.\p"
# 1465 "data/maps/NewBarkTown/scripts.pory"
	.string "So I posted the whole log to\n"
# 1466 "data/maps/NewBarkTown/scripts.pory"
	.string "the one man in the world who\l"
# 1467 "data/maps/NewBarkTown/scripts.pory"
	.string "would not laugh at it, and he\l"
# 1468 "data/maps/NewBarkTown/scripts.pory"
	.string "telephoned the police before he\l"
# 1469 "data/maps/NewBarkTown/scripts.pory"
	.string "finished reading it.\p"
# 1470 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor Kukui works fast when\n"
# 1471 "data/maps/NewBarkTown/scripts.pory"
	.string "he is frightened.\p"
# 1472 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone who would come is in\n"
# 1473 "data/maps/NewBarkTown/scripts.pory"
	.string "the lab. It's the strongest\l"
# 1474 "data/maps/NewBarkTown/scripts.pory"
	.string "building in town, which is not\l"
# 1475 "data/maps/NewBarkTown/scripts.pory"
	.string "saying much.$"
# 1476 "data/maps/NewBarkTown/scripts.pory"

# 1477 "data/maps/NewBarkTown/scripts.pory"
@ Optional. Elm is the one who identified the egg in the first place, so he
# 1478 "data/maps/NewBarkTown/scripts.pory"
@ is allowed to be delighted for exactly two boxes and then remember where
# 1479 "data/maps/NewBarkTown/scripts.pory"
@ he is standing.
# 1480 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmIdleCosmog:
# 1481 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}And there it is.\p"
# 1482 "data/maps/NewBarkTown/scripts.pory"
	.string "I had a {STR_VAR_1} on my table\n"
# 1483 "data/maps/NewBarkTown/scripts.pory"
	.string "in a shell, and now it is on my\l"
# 1484 "data/maps/NewBarkTown/scripts.pory"
	.string "street, and I still cannot tell\l"
# 1485 "data/maps/NewBarkTown/scripts.pory"
	.string "you what it is.\p"
# 1486 "data/maps/NewBarkTown/scripts.pory"
	.string "…I'm going to stop looking at\n"
# 1487 "data/maps/NewBarkTown/scripts.pory"
	.string "it now.\p"
# 1488 "data/maps/NewBarkTown/scripts.pory"
	.string "Every instrument in my window\n"
# 1489 "data/maps/NewBarkTown/scripts.pory"
	.string "leans when it walks past.$"
# 1490 "data/maps/NewBarkTown/scripts.pory"

# 1491 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomIdle:
# 1492 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}I'm not going into the\n"
# 1493 "data/maps/NewBarkTown/scripts.pory"
	.string "lab, {PLAYER}.\p"
# 1494 "data/maps/NewBarkTown/scripts.pory"
	.string "Don't ask me again.\p"
# 1495 "data/maps/NewBarkTown/scripts.pory"
	.string "I've been watching that road\n"
# 1496 "data/maps/NewBarkTown/scripts.pory"
	.string "for two years.\p"
# 1497 "data/maps/NewBarkTown/scripts.pory"
	.string "I know how to watch a road.$"
# 1498 "data/maps/NewBarkTown/scripts.pory"

# 1499 "data/maps/NewBarkTown/scripts.pory"
@ No name: this text serves both Gold and Crystal.
# 1500 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIdle:
# 1501 "data/maps/NewBarkTown/scripts.pory"
	.string "Every house on this street,\n"
# 1502 "data/maps/NewBarkTown/scripts.pory"
	.string "twice.\p"
# 1503 "data/maps/NewBarkTown/scripts.pory"
	.string "The Hanlons wouldn't open the\n"
# 1504 "data/maps/NewBarkTown/scripts.pory"
	.string "door until I said your name.\p"
# 1505 "data/maps/NewBarkTown/scripts.pory"
	.string "Which is the story of the last\n"
# 1506 "data/maps/NewBarkTown/scripts.pory"
	.string "two years, honestly.\p"
# 1507 "data/maps/NewBarkTown/scripts.pory"
	.string "Hey - when it starts, put me\n"
# 1508 "data/maps/NewBarkTown/scripts.pory"
	.string "in.\p"
# 1509 "data/maps/NewBarkTown/scripts.pory"
	.string "I've got a full team. I've had\n"
# 1510 "data/maps/NewBarkTown/scripts.pory"
	.string "a full team for a year, and I\l"
# 1511 "data/maps/NewBarkTown/scripts.pory"
	.string "have never once been in the\l"
# 1512 "data/maps/NewBarkTown/scripts.pory"
	.string "room where it mattered.$"
# 1513 "data/maps/NewBarkTown/scripts.pory"

# 1514 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelIdle:
# 1515 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Three signatures, and\n"
# 1516 "data/maps/NewBarkTown/scripts.pory"
	.string "they are breathing together.\p"
# 1517 "data/maps/NewBarkTown/scripts.pory"
	.string "In, and out.\p"
# 1518 "data/maps/NewBarkTown/scripts.pory"
	.string "I told you in Olivine what that\n"
# 1519 "data/maps/NewBarkTown/scripts.pory"
	.string "does to me. I won't say it\l"
# 1520 "data/maps/NewBarkTown/scripts.pory"
	.string "twice on an open road.\p"
# 1521 "data/maps/NewBarkTown/scripts.pory"
	.string "Stay on this street.\p"
# 1522 "data/maps/NewBarkTown/scripts.pory"
	.string "If I tell you to move, move\n"
# 1523 "data/maps/NewBarkTown/scripts.pory"
	.string "first and ask me after.$"
# 1524 "data/maps/NewBarkTown/scripts.pory"

# 1525 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLookerGreet:
# 1526 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Right on your\n"
# 1527 "data/maps/NewBarkTown/scripts.pory"
	.string "own doorstep.\p"
# 1528 "data/maps/NewBarkTown/scripts.pory"
	.string "I have worked a great many\n"
# 1529 "data/maps/NewBarkTown/scripts.pory"
	.string "streets, and I have never liked\l"
# 1530 "data/maps/NewBarkTown/scripts.pory"
	.string "one less than this.$"
# 1531 "data/maps/NewBarkTown/scripts.pory"

# 1532 "data/maps/NewBarkTown/scripts.pory"
@ Elm is still at (11,10) and off camera at this point, so Anabel reads his
# 1533 "data/maps/NewBarkTown/scripts.pory"
@ log out for him. His own voice arrives with his object, in UBTheyArrive.
# 1534 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBClockRelay:
# 1535 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The Professor called it\n"
# 1536 "data/maps/NewBarkTown/scripts.pory"
	.string "in four minutes ago.\p"
# 1537 "data/maps/NewBarkTown/scripts.pory"
	.string "Three minutes, he says. Maybe\n"
# 1538 "data/maps/NewBarkTown/scripts.pory"
	.string "four - the interval has been\l"
# 1539 "data/maps/NewBarkTown/scripts.pory"
	.string "shortening all morning.\p"
# 1540 "data/maps/NewBarkTown/scripts.pory"
	.string "All three breathe together.\p"
# 1541 "data/maps/NewBarkTown/scripts.pory"
	.string "He had six weeks of that on\n"
# 1542 "data/maps/NewBarkTown/scripts.pory"
	.string "paper and called it a fault.\p"
# 1543 "data/maps/NewBarkTown/scripts.pory"
	.string "It took a stranger in Alola one\n"
# 1544 "data/maps/NewBarkTown/scripts.pory"
	.string "page to tell him it wasn't.\p"
# 1545 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}And so we are here, on\n"
# 1546 "data/maps/NewBarkTown/scripts.pory"
	.string "a road with no Pokémon Center,\l"
# 1547 "data/maps/NewBarkTown/scripts.pory"
	.string "because a man in a laboratory\l"
# 1548 "data/maps/NewBarkTown/scripts.pory"
	.string "was brave enough to be wrong in\l"
# 1549 "data/maps/NewBarkTown/scripts.pory"
	.string "writing.$"
# 1550 "data/maps/NewBarkTown/scripts.pory"

# 1551 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBReady:
# 1552 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Worse than Cherrygrove.\p"
# 1553 "data/maps/NewBarkTown/scripts.pory"
	.string "Worse than anything we have\n"
# 1554 "data/maps/NewBarkTown/scripts.pory"
	.string "sent you into.\p"
# 1555 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Are you ready?$"
# 1556 "data/maps/NewBarkTown/scripts.pory"

# 1557 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNotReady:
# 1558 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then take the time.\p"
# 1559 "data/maps/NewBarkTown/scripts.pory"
	.string "Your mother is not moving,\n"
# 1560 "data/maps/NewBarkTown/scripts.pory"
	.string "and neither am I.$"
# 1561 "data/maps/NewBarkTown/scripts.pory"

# 1562 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBTheyArrive:
# 1563 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Professor. Your log.\p"
# 1564 "data/maps/NewBarkTown/scripts.pory"
	.string "You kept six weeks of a reading\n"
# 1565 "data/maps/NewBarkTown/scripts.pory"
	.string "you were certain was wrong.\p"
# 1566 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}I kept it because I\n"
# 1567 "data/maps/NewBarkTown/scripts.pory"
	.string "thought it was wrong.\p"
# 1568 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not the same as being\n"
# 1569 "data/maps/NewBarkTown/scripts.pory"
	.string "useful.\p"
# 1570 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Today it is exactly\n"
# 1571 "data/maps/NewBarkTown/scripts.pory"
	.string "the same thing.\p"
# 1572 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Madame. Nobody told me\n"
# 1573 "data/maps/NewBarkTown/scripts.pory"
	.string "you were coming.\p"
# 1574 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Nobody told me either,\n"
# 1575 "data/maps/NewBarkTown/scripts.pory"
	.string "Inspector.$"
# 1576 "data/maps/NewBarkTown/scripts.pory"

# 1577 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAppear:
# 1578 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Three.\p"
# 1579 "data/maps/NewBarkTown/scripts.pory"
	.string "Over the laboratory, over the\n"
# 1580 "data/maps/NewBarkTown/scripts.pory"
	.string "road, over this street.\p"
# 1581 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}That's them. That's the\n"
# 1582 "data/maps/NewBarkTown/scripts.pory"
	.string "reading.\p"
# 1583 "data/maps/NewBarkTown/scripts.pory"
	.string "Six weeks of it, standing in\n"
# 1584 "data/maps/NewBarkTown/scripts.pory"
	.string "my town.$"
# 1585 "data/maps/NewBarkTown/scripts.pory"

# 1586 "data/maps/NewBarkTown/scripts.pory"
@ The synergy, shown first and named second.
# 1587 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBSynergyFirst:
# 1588 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Wait.\p"
# 1589 "data/maps/NewBarkTown/scripts.pory"
	.string "Wait, they all moved.\p"
# 1590 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Yes. Toward us. That is\n"
# 1591 "data/maps/NewBarkTown/scripts.pory"
	.string "what they do.\p"
# 1592 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}No, madame - they all\n"
# 1593 "data/maps/NewBarkTown/scripts.pory"
	.string "moved at the SAME time.\p"
# 1594 "data/maps/NewBarkTown/scripts.pory"
	.string "I have a clock. That is the\n"
# 1595 "data/maps/NewBarkTown/scripts.pory"
	.string "only thing I am good for today.$"
# 1596 "data/maps/NewBarkTown/scripts.pory"

# 1597 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBSynergyNamed:
# 1598 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Again. Same instant.\p"
# 1599 "data/maps/NewBarkTown/scripts.pory"
	.string "There are two buildings between\n"
# 1600 "data/maps/NewBarkTown/scripts.pory"
	.string "them. They cannot see each\l"
# 1601 "data/maps/NewBarkTown/scripts.pory"
	.string "other.\p"
# 1602 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Then stop counting them\n"
# 1603 "data/maps/NewBarkTown/scripts.pory"
	.string "as three.\p"
# 1604 "data/maps/NewBarkTown/scripts.pory"
	.string "That is one thing wearing three\n"
# 1605 "data/maps/NewBarkTown/scripts.pory"
	.string "bodies, and it has been doing\l"
# 1606 "data/maps/NewBarkTown/scripts.pory"
	.string "it since Blackthorn.\p"
# 1607 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…In Alola they never\n"
# 1608 "data/maps/NewBarkTown/scripts.pory"
	.string "did that.\p"
# 1609 "data/maps/NewBarkTown/scripts.pory"
	.string "Not once. Not for me.$"
# 1610 "data/maps/NewBarkTown/scripts.pory"

# 1611 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBCutOff:
# 1612 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}MOVE!\p"
# 1613 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}Azumarill, cut it off!\n"
# 1614 "data/maps/NewBarkTown/scripts.pory"
	.string "Go around, go around!\p"
# 1615 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}…It stopped.\p"
# 1616 "data/maps/NewBarkTown/scripts.pory"
	.string "It came straight down the road\n"
# 1617 "data/maps/NewBarkTown/scripts.pory"
	.string "at a fifteen-year-old and a\l"
# 1618 "data/maps/NewBarkTown/scripts.pory"
	.string "woman who refused to go inside,\l"
# 1619 "data/maps/NewBarkTown/scripts.pory"
	.string "and a Pokémon nobody asked for\l"
# 1620 "data/maps/NewBarkTown/scripts.pory"
	.string "is what stopped it.\p"
# 1621 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}I'm still not going\n"
# 1622 "data/maps/NewBarkTown/scripts.pory"
	.string "inside.$"
# 1623 "data/maps/NewBarkTown/scripts.pory"

# 1624 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineTakesThree:
# 1625 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}It went for your child.\p"
# 1626 "data/maps/NewBarkTown/scripts.pory"
	.string "In front of you. In front of\n"
# 1627 "data/maps/NewBarkTown/scripts.pory"
	.string "me.\p"
# 1628 "data/maps/NewBarkTown/scripts.pory"
	.string "Three of them. Then I will take\n"
# 1629 "data/maps/NewBarkTown/scripts.pory"
	.string "three.\p"
# 1630 "data/maps/NewBarkTown/scripts.pory"
	.string "No - listen to me.\p"
# 1631 "data/maps/NewBarkTown/scripts.pory"
	.string "I know what they are. I know it\n"
# 1632 "data/maps/NewBarkTown/scripts.pory"
	.string "better than anyone standing on\l"
# 1633 "data/maps/NewBarkTown/scripts.pory"
	.string "this road.\p"
# 1634 "data/maps/NewBarkTown/scripts.pory"
	.string "Nobody else here has to go near\n"
# 1635 "data/maps/NewBarkTown/scripts.pory"
	.string "them.$"
# 1636 "data/maps/NewBarkTown/scripts.pory"

# 1637 "data/maps/NewBarkTown/scripts.pory"
@ The plotline the author asked to keep: Mom does not out-argue her. She
# 1638 "data/maps/NewBarkTown/scripts.pory"
@ tells her what believing in somebody looks like from the inside, and she
# 1639 "data/maps/NewBarkTown/scripts.pory"
@ has exactly one example.
# 1640 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomStopsHer:
# 1641 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Ma'am.\p"
# 1642 "data/maps/NewBarkTown/scripts.pory"
	.string "My child is standing right\n"
# 1643 "data/maps/NewBarkTown/scripts.pory"
	.string "there, and I'm not going inside\l"
# 1644 "data/maps/NewBarkTown/scripts.pory"
	.string "either, so I won't lecture you.\p"
# 1645 "data/maps/NewBarkTown/scripts.pory"
	.string "But you're not protecting\n"
# 1646 "data/maps/NewBarkTown/scripts.pory"
	.string "anyone.\p"
# 1647 "data/maps/NewBarkTown/scripts.pory"
	.string "You're making sure that if it\n"
# 1648 "data/maps/NewBarkTown/scripts.pory"
	.string "goes wrong, it goes wrong to\l"
# 1649 "data/maps/NewBarkTown/scripts.pory"
	.string "you.\p"
# 1650 "data/maps/NewBarkTown/scripts.pory"
	.string "I know the difference. I've\n"
# 1651 "data/maps/NewBarkTown/scripts.pory"
	.string "wanted to do it too.\p"
# 1652 "data/maps/NewBarkTown/scripts.pory"
	.string "Every week, for two years.\p"
# 1653 "data/maps/NewBarkTown/scripts.pory"
	.string "And then one morning I stood at\n"
# 1654 "data/maps/NewBarkTown/scripts.pory"
	.string "that door and let a ten-year-\l"
# 1655 "data/maps/NewBarkTown/scripts.pory"
	.string "old walk to Cherrygrove alone.\p"
# 1656 "data/maps/NewBarkTown/scripts.pory"
	.string "That's the part nobody tells\n"
# 1657 "data/maps/NewBarkTown/scripts.pory"
	.string "you. Believing in somebody is\l"
# 1658 "data/maps/NewBarkTown/scripts.pory"
	.string "worse than doing it yourself.\p"
# 1659 "data/maps/NewBarkTown/scripts.pory"
	.string "It just happens to be the thing\n"
# 1660 "data/maps/NewBarkTown/scripts.pory"
	.string "that works.\p"
# 1661 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…\p"
# 1662 "data/maps/NewBarkTown/scripts.pory"
	.string "My daughter said something very\n"
# 1663 "data/maps/NewBarkTown/scripts.pory"
	.string "close to that to me, once.\p"
# 1664 "data/maps/NewBarkTown/scripts.pory"
	.string "I did not hear it either.$"
# 1665 "data/maps/NewBarkTown/scripts.pory"

# 1666 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineAsks:
# 1667 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Very well.\p"
# 1668 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I will do the thing I am\n"
# 1669 "data/maps/NewBarkTown/scripts.pory"
	.string "worst at.\p"
# 1670 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel. What do your\n"
# 1671 "data/maps/NewBarkTown/scripts.pory"
	.string "instruments give me?$"
# 1672 "data/maps/NewBarkTown/scripts.pory"

# 1673 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelBreaks:
# 1674 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They give me… they\n"
# 1675 "data/maps/NewBarkTown/scripts.pory"
	.string "give me…\p"
# 1676 "data/maps/NewBarkTown/scripts.pory"
	.string "…\p"
# 1677 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief. Chief.$"
# 1678 "data/maps/NewBarkTown/scripts.pory"

# 1679 "data/maps/NewBarkTown/scripts.pory"
@ Two boxes and she is back at work. The long version of this happened in
# 1680 "data/maps/NewBarkTown/scripts.pory"
@ Olivine, before any of it. Do not move it back here.
# 1681 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelStands:
# 1682 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'm here. Let go,\n"
# 1683 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker. I can stand.\p"
# 1684 "data/maps/NewBarkTown/scripts.pory"
	.string "Three at once is loud.\p"
# 1685 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} knows why. I'm not\n"
# 1686 "data/maps/NewBarkTown/scripts.pory"
	.string "saying it again in the middle\l"
# 1687 "data/maps/NewBarkTown/scripts.pory"
	.string "of a road.\p"
# 1688 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}You are not required\n"
# 1689 "data/maps/NewBarkTown/scripts.pory"
	.string "to.$"
# 1690 "data/maps/NewBarkTown/scripts.pory"

# 1691 "data/maps/NewBarkTown/scripts.pory"
@ The counter, and the reason the scene needs a fourth person.
# 1692 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBCounter:
# 1693 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Here is what the\n"
# 1694 "data/maps/NewBarkTown/scripts.pory"
	.string "instruments give you, madame.\p"
# 1695 "data/maps/NewBarkTown/scripts.pory"
	.string "One thing, three bodies, one\n"
# 1696 "data/maps/NewBarkTown/scripts.pory"
	.string "instant.\p"
# 1697 "data/maps/NewBarkTown/scripts.pory"
	.string "Break one and the other two\n"
# 1698 "data/maps/NewBarkTown/scripts.pory"
	.string "carry it. Break two and the\l"
# 1699 "data/maps/NewBarkTown/scripts.pory"
	.string "third one carries both.\p"
# 1700 "data/maps/NewBarkTown/scripts.pory"
	.string "They have to go down in the\n"
# 1701 "data/maps/NewBarkTown/scripts.pory"
	.string "same instant or they do not go\l"
# 1702 "data/maps/NewBarkTown/scripts.pory"
	.string "down at all.\p"
# 1703 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Then I cannot take\n"
# 1704 "data/maps/NewBarkTown/scripts.pory"
	.string "three.\p"
# 1705 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}No. You take one, I\n"
# 1706 "data/maps/NewBarkTown/scripts.pory"
	.string "take one, {PLAYER} takes one.\p"
# 1707 "data/maps/NewBarkTown/scripts.pory"
	.string "And the one {PLAYER} takes is\n"
# 1708 "data/maps/NewBarkTown/scripts.pory"
	.string "the one that has already tried\l"
# 1709 "data/maps/NewBarkTown/scripts.pory"
	.string "for them once.\p"
# 1710 "data/maps/NewBarkTown/scripts.pory"
	.string "It will not go down to one\n"
# 1711 "data/maps/NewBarkTown/scripts.pory"
	.string "trainer.$"
# 1712 "data/maps/NewBarkTown/scripts.pory"

# 1713 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1714 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalAsks:
# 1715 "data/maps/NewBarkTown/scripts.pory"
	.string "Then take me.\p"
# 1716 "data/maps/NewBarkTown/scripts.pory"
	.string "I asked first. I asked before\n"
# 1717 "data/maps/NewBarkTown/scripts.pory"
	.string "any of you got here.\p"
# 1718 "data/maps/NewBarkTown/scripts.pory"
	.string "My Azumarill is the reason that\n"
# 1719 "data/maps/NewBarkTown/scripts.pory"
	.string "thing is still ten feet away.$"
# 1720 "data/maps/NewBarkTown/scripts.pory"

# 1721 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalRefused:
# 1722 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}You are the only person\n"
# 1723 "data/maps/NewBarkTown/scripts.pory"
	.string "on this road who is not police,\l"
# 1724 "data/maps/NewBarkTown/scripts.pory"
	.string "not Aether, and not the\l"
# 1725 "data/maps/NewBarkTown/scripts.pory"
	.string "Champion.\p"
# 1726 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Forty people came back\n"
# 1727 "data/maps/NewBarkTown/scripts.pory"
	.string "out of their houses because you\l"
# 1728 "data/maps/NewBarkTown/scripts.pory"
	.string "knocked.\p"
# 1729 "data/maps/NewBarkTown/scripts.pory"
	.string "If this goes badly they will\n"
# 1730 "data/maps/NewBarkTown/scripts.pory"
	.string "need someone who knows which\l"
# 1731 "data/maps/NewBarkTown/scripts.pory"
	.string "doors are which.\p"
# 1732 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}…Right. Doors.\p"
# 1733 "data/maps/NewBarkTown/scripts.pory"
	.string "It's always doors.$"
# 1734 "data/maps/NewBarkTown/scripts.pory"

# 1735 "data/maps/NewBarkTown/scripts.pory"
@ Thirty seconds after being told that deciding for everybody is not
# 1736 "data/maps/NewBarkTown/scripts.pory"
@ protection. This is the whole argument of the scene landing.
# 1737 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineLetsHimIn:
# 1738 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}No.\p"
# 1739 "data/maps/NewBarkTown/scripts.pory"
	.string "Inspector, you are wrong, and I\n"
# 1740 "data/maps/NewBarkTown/scripts.pory"
	.string "am the last person in Johto\l"
# 1741 "data/maps/NewBarkTown/scripts.pory"
	.string "with the right to say so.\p"
# 1742 "data/maps/NewBarkTown/scripts.pory"
	.string "I have spent my life deciding\n"
# 1743 "data/maps/NewBarkTown/scripts.pory"
	.string "who was ready.\p"
# 1744 "data/maps/NewBarkTown/scripts.pory"
	.string "I was told, four minutes ago,\n"
# 1745 "data/maps/NewBarkTown/scripts.pory"
	.string "what that actually is.\p"
# 1746 "data/maps/NewBarkTown/scripts.pory"
	.string "We need four. There are four of\n"
# 1747 "data/maps/NewBarkTown/scripts.pory"
	.string "us standing here.\p"
# 1748 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Ma'am.\p"
# 1749 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I heard you the first\n"
# 1750 "data/maps/NewBarkTown/scripts.pory"
	.string "time.$"
# 1751 "data/maps/NewBarkTown/scripts.pory"

# 1752 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1753 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIn:
# 1754 "data/maps/NewBarkTown/scripts.pory"
	.string "…Say that again.\p"
# 1755 "data/maps/NewBarkTown/scripts.pory"
	.string "No. Don't. If you say it again\n"
# 1756 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll cry, and I am NOT doing\l"
# 1757 "data/maps/NewBarkTown/scripts.pory"
	.string "that in front of {PLAYER}.\p"
# 1758 "data/maps/NewBarkTown/scripts.pory"
	.string "Azumarill! Back to me!\p"
# 1759 "data/maps/NewBarkTown/scripts.pory"
	.string "We're in. We're actually in.$"
# 1760 "data/maps/NewBarkTown/scripts.pory"

# 1761 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBChoosePrompt:
# 1762 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER} - which one\n"
# 1763 "data/maps/NewBarkTown/scripts.pory"
	.string "will you take?\p"
# 1764 "data/maps/NewBarkTown/scripts.pory"
	.string "I am asking. I am not deciding\n"
# 1765 "data/maps/NewBarkTown/scripts.pory"
	.string "it for you.\p"
# 1766 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Choose, {PLAYER}.\p"
# 1767 "data/maps/NewBarkTown/scripts.pory"
	.string "Quickly, and then not again.$"
# 1768 "data/maps/NewBarkTown/scripts.pory"

# 1769 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceKartana:
# 1770 "data/maps/NewBarkTown/scripts.pory"
	.string "Kartana$"
# 1771 "data/maps/NewBarkTown/scripts.pory"

# 1772 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceGuzzlord:
# 1773 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord$"
# 1774 "data/maps/NewBarkTown/scripts.pory"

# 1775 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceNihilego:
# 1776 "data/maps/NewBarkTown/scripts.pory"
	.string "Nihilego$"
# 1777 "data/maps/NewBarkTown/scripts.pory"

# 1778 "data/maps/NewBarkTown/scripts.pory"
@ Each of the three says the whole split out loud - design section 6.4.
# 1779 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedKartana:
# 1780 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The blade.\p"
# 1781 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I take the one that\n"
# 1782 "data/maps/NewBarkTown/scripts.pory"
	.string "matters to me, and Anabel takes\l"
# 1783 "data/maps/NewBarkTown/scripts.pory"
	.string "the weight.\p"
# 1784 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nihilego is hers.\n"
# 1785 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord is mine.\p"
# 1786 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}And I'm on the blade\n"
# 1787 "data/maps/NewBarkTown/scripts.pory"
	.string "with {PLAYER}.\p"
# 1788 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}On my mark. All four.$"
# 1789 "data/maps/NewBarkTown/scripts.pory"

# 1790 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedGuzzlord:
# 1791 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The mouth.\p"
# 1792 "data/maps/NewBarkTown/scripts.pory"
	.string "Be careful - it does not stop\n"
# 1793 "data/maps/NewBarkTown/scripts.pory"
	.string "because you are tired.\p"
# 1794 "data/maps/NewBarkTown/scripts.pory"
	.string "I take Nihilego. It is the one\n"
# 1795 "data/maps/NewBarkTown/scripts.pory"
	.string "I came for.\p"
# 1796 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Then the blade is\n"
# 1797 "data/maps/NewBarkTown/scripts.pory"
	.string "mine.\p"
# 1798 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}And I'm on the mouth\n"
# 1799 "data/maps/NewBarkTown/scripts.pory"
	.string "with {PLAYER}.\p"
# 1800 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}On my mark. All four.$"
# 1801 "data/maps/NewBarkTown/scripts.pory"

# 1802 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedNihilego:
# 1803 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…That one was mine to\n"
# 1804 "data/maps/NewBarkTown/scripts.pory"
	.string "answer for.\p"
# 1805 "data/maps/NewBarkTown/scripts.pory"
	.string "No. That is exactly the\n"
# 1806 "data/maps/NewBarkTown/scripts.pory"
	.string "sentence I promised my children\l"
# 1807 "data/maps/NewBarkTown/scripts.pory"
	.string "I would stop saying.\p"
# 1808 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you for taking it.\p"
# 1809 "data/maps/NewBarkTown/scripts.pory"
	.string "I will take the mouth instead.\p"
# 1810 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And I'll take the\n"
# 1811 "data/maps/NewBarkTown/scripts.pory"
	.string "blade.\p"
# 1812 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}I'm going where\n"
# 1813 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} goes.\p"
# 1814 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}On my mark. All four.$"
# 1815 "data/maps/NewBarkTown/scripts.pory"

# 1816 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBGotAway:
# 1817 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}It is still here.\p"
# 1818 "data/maps/NewBarkTown/scripts.pory"
	.string "All three of them are still\n"
# 1819 "data/maps/NewBarkTown/scripts.pory"
	.string "here.\p"
# 1820 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Back to the line,\n"
# 1821 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}. We go again.\p"
# 1822 "data/maps/NewBarkTown/scripts.pory"
	.string "All four of us.$"
# 1823 "data/maps/NewBarkTown/scripts.pory"

# 1824 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterKartana:
# 1825 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Down. All three, inside\n"
# 1826 "data/maps/NewBarkTown/scripts.pory"
	.string "the same second.\p"
# 1827 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Mine folded the moment\n"
# 1828 "data/maps/NewBarkTown/scripts.pory"
	.string "yours did.\p"
# 1829 "data/maps/NewBarkTown/scripts.pory"
	.string "They came together and they\n"
# 1830 "data/maps/NewBarkTown/scripts.pory"
	.string "fall together - of course they\l"
# 1831 "data/maps/NewBarkTown/scripts.pory"
	.string "do.\p"
# 1832 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}We did it. We actually\n"
# 1833 "data/maps/NewBarkTown/scripts.pory"
	.string "did it.$"
# 1834 "data/maps/NewBarkTown/scripts.pory"

# 1835 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterGuzzlord:
# 1836 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Down. All three, inside\n"
# 1837 "data/maps/NewBarkTown/scripts.pory"
	.string "the same second.\p"
# 1838 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}You stood in front of\n"
# 1839 "data/maps/NewBarkTown/scripts.pory"
	.string "that thing for how long?\p"
# 1840 "data/maps/NewBarkTown/scripts.pory"
	.string "…Lillie was right about you.\p"
# 1841 "data/maps/NewBarkTown/scripts.pory"
	.string "She is right a great deal\n"
# 1842 "data/maps/NewBarkTown/scripts.pory"
	.string "lately.\p"
# 1843 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}We did it. We actually\n"
# 1844 "data/maps/NewBarkTown/scripts.pory"
	.string "did it.$"
# 1845 "data/maps/NewBarkTown/scripts.pory"

# 1846 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterNihilego:
# 1847 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Down. All three, inside\n"
# 1848 "data/maps/NewBarkTown/scripts.pory"
	.string "the same second.\p"
# 1849 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I watched you do that.\p"
# 1850 "data/maps/NewBarkTown/scripts.pory"
	.string "I made myself watch all of it.\p"
# 1851 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you. I will not say it a\n"
# 1852 "data/maps/NewBarkTown/scripts.pory"
	.string "third time, but I mean it more\l"
# 1853 "data/maps/NewBarkTown/scripts.pory"
	.string "each time.\p"
# 1854 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}We did it. We actually\n"
# 1855 "data/maps/NewBarkTown/scripts.pory"
	.string "did it.$"
# 1856 "data/maps/NewBarkTown/scripts.pory"

# 1857 "data/maps/NewBarkTown/scripts.pory"
@ Nobody in Johto names it. It has been "the thing from Blackthorn" for
# 1858 "data/maps/NewBarkTown/scripts.pory"
@ three missions and it stays that way until the reunion.
# 1859 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNecrozmaArrives:
# 1860 "data/maps/NewBarkTown/scripts.pory"
	.string "The road opens.\p"
# 1861 "data/maps/NewBarkTown/scripts.pory"
	.string "Not a tear this time. The air\n"
# 1862 "data/maps/NewBarkTown/scripts.pory"
	.string "itself steps aside, and\l"
# 1863 "data/maps/NewBarkTown/scripts.pory"
	.string "something walks out of it onto\l"
# 1864 "data/maps/NewBarkTown/scripts.pory"
	.string "the street.\p"
# 1865 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…That is the thing from\n"
# 1866 "data/maps/NewBarkTown/scripts.pory"
	.string "Blackthorn.\p"
# 1867 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}It's on the ROAD. The\n"
# 1868 "data/maps/NewBarkTown/scripts.pory"
	.string "others came out of the sky and\l"
# 1869 "data/maps/NewBarkTown/scripts.pory"
	.string "that one used the road.\p"
# 1870 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I have seen light like\n"
# 1871 "data/maps/NewBarkTown/scripts.pory"
	.string "that before.\p"
# 1872 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Madame.\p"
# 1873 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…Later.$"
# 1874 "data/maps/NewBarkTown/scripts.pory"

# 1875 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1876 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalCharges:
# 1877 "data/maps/NewBarkTown/scripts.pory"
	.string "It's walking past them.\p"
# 1878 "data/maps/NewBarkTown/scripts.pory"
	.string "It's not even looking at the\n"
# 1879 "data/maps/NewBarkTown/scripts.pory"
	.string "three of them, it's-\p"
# 1880 "data/maps/NewBarkTown/scripts.pory"
	.string "No. No, I got let in.\p"
# 1881 "data/maps/NewBarkTown/scripts.pory"
	.string "AZUMARILL!$"
# 1882 "data/maps/NewBarkTown/scripts.pory"

# 1883 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalRepelled:
# 1884 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Get it back! Now!\p"
# 1885 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}It's up. It's up, it's\n"
# 1886 "data/maps/NewBarkTown/scripts.pory"
	.string "fine, it's-\p"
# 1887 "data/maps/NewBarkTown/scripts.pory"
	.string "It didn't block. It didn't\n"
# 1888 "data/maps/NewBarkTown/scripts.pory"
	.string "dodge. It didn't do anything.\p"
# 1889 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}My friend, that was\n"
# 1890 "data/maps/NewBarkTown/scripts.pory"
	.string "the bravest useless thing I\l"
# 1891 "data/maps/NewBarkTown/scripts.pory"
	.string "have seen in twenty years of\l"
# 1892 "data/maps/NewBarkTown/scripts.pory"
	.string "this work.\p"
# 1893 "data/maps/NewBarkTown/scripts.pory"
	.string "Do not do it twice.$"
# 1894 "data/maps/NewBarkTown/scripts.pory"

# 1895 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAbsorbed:
# 1896 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}They're moving. They\n"
# 1897 "data/maps/NewBarkTown/scripts.pory"
	.string "were down and they're moving.\p"
# 1898 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They are not moving.\n"
# 1899 "data/maps/NewBarkTown/scripts.pory"
	.string "They are being moved.\p"
# 1900 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}It is not fighting\n"
# 1901 "data/maps/NewBarkTown/scripts.pory"
	.string "them.\p"
# 1902 "data/maps/NewBarkTown/scripts.pory"
	.string "Inspector - it is not fighting\n"
# 1903 "data/maps/NewBarkTown/scripts.pory"
	.string "them, it is COLLECTING them.\p"
# 1904 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Three at once.\p"
# 1905 "data/maps/NewBarkTown/scripts.pory"
	.string "It took two in Blackthorn. Two\n"
# 1906 "data/maps/NewBarkTown/scripts.pory"
	.string "at the Lake. Two on the beach.$"
# 1907 "data/maps/NewBarkTown/scripts.pory"

# 1908 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraRises:
# 1909 "data/maps/NewBarkTown/scripts.pory"
	.string "The light does not go out this\n"
# 1910 "data/maps/NewBarkTown/scripts.pory"
	.string "time.\p"
# 1911 "data/maps/NewBarkTown/scripts.pory"
	.string "It folds. It keeps folding,\n"
# 1912 "data/maps/NewBarkTown/scripts.pory"
	.string "into something with a shape,\l"
# 1913 "data/maps/NewBarkTown/scripts.pory"
	.string "and the shape is standing in\l"
# 1914 "data/maps/NewBarkTown/scripts.pory"
	.string "the middle of New Bark Town.\p"
# 1915 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Formation. NOW.\p"
# 1916 "data/maps/NewBarkTown/scripts.pory"
	.string "Same mark. Same instant. It is\n"
# 1917 "data/maps/NewBarkTown/scripts.pory"
	.string "the only thing that has worked\l"
# 1918 "data/maps/NewBarkTown/scripts.pory"
	.string "all day.\p"
# 1919 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}All four. Together.$"
# 1920 "data/maps/NewBarkTown/scripts.pory"

# 1921 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraBreaksThem:
# 1922 "data/maps/NewBarkTown/scripts.pory"
	.string "It was over before any of them\n"
# 1923 "data/maps/NewBarkTown/scripts.pory"
	.string "finished the motion.\p"
# 1924 "data/maps/NewBarkTown/scripts.pory"
	.string "One light, across the whole\n"
# 1925 "data/maps/NewBarkTown/scripts.pory"
	.string "road, at once.\p"
# 1926 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}…Report.\p"
# 1927 "data/maps/NewBarkTown/scripts.pory"
	.string "Somebody report. Anybody.\p"
# 1928 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I am on the ground,\n"
# 1929 "data/maps/NewBarkTown/scripts.pory"
	.string "Chief.\p"
# 1930 "data/maps/NewBarkTown/scripts.pory"
	.string "We are all on the ground.$"
# 1931 "data/maps/NewBarkTown/scripts.pory"

# 1932 "data/maps/NewBarkTown/scripts.pory"
@ Optional, stateless. It is the only thing on this road that it looks at
# 1933 "data/maps/NewBarkTown/scripts.pory"
@ twice, and it does not take it.
# 1934 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraSensesCosmog:
# 1935 "data/maps/NewBarkTown/scripts.pory"
	.string "It turns.\p"
# 1936 "data/maps/NewBarkTown/scripts.pory"
	.string "Not to Lusamine, not to the\n"
# 1937 "data/maps/NewBarkTown/scripts.pory"
	.string "police. To {STR_VAR_1}, which is\l"
# 1938 "data/maps/NewBarkTown/scripts.pory"
	.string "the only thing on this road\l"
# 1939 "data/maps/NewBarkTown/scripts.pory"
	.string "still standing up.\p"
# 1940 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Don't move. Don't you\n"
# 1941 "data/maps/NewBarkTown/scripts.pory"
	.string "move, either of you.\p"
# 1942 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It is not going to\n"
# 1943 "data/maps/NewBarkTown/scripts.pory"
	.string "take it.\p"
# 1944 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}No. It is not.\p"
# 1945 "data/maps/NewBarkTown/scripts.pory"
	.string "It is WAITING for it.$"
# 1946 "data/maps/NewBarkTown/scripts.pory"

# 1947 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraSensesLegend:
# 1948 "data/maps/NewBarkTown/scripts.pory"
	.string "It turns.\p"
# 1949 "data/maps/NewBarkTown/scripts.pory"
	.string "{STR_VAR_1} stands up between\n"
# 1950 "data/maps/NewBarkTown/scripts.pory"
	.string "the light and everyone lying in\l"
# 1951 "data/maps/NewBarkTown/scripts.pory"
	.string "the road, and does not step\l"
# 1952 "data/maps/NewBarkTown/scripts.pory"
	.string "back.\p"
# 1953 "data/maps/NewBarkTown/scripts.pory"
	.string "And the thing in the street\n"
# 1954 "data/maps/NewBarkTown/scripts.pory"
	.string "stops.\p"
# 1955 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…It knows that shape.\p"
# 1956 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Madame, it just\n"
# 1957 "data/maps/NewBarkTown/scripts.pory"
	.string "hesitated. That thing flattened\l"
# 1958 "data/maps/NewBarkTown/scripts.pory"
	.string "four trainers and it just\l"
# 1959 "data/maps/NewBarkTown/scripts.pory"
	.string "hesitated.\p"
# 1960 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Write that down,\n"
# 1961 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor. Write exactly that\l"
# 1962 "data/maps/NewBarkTown/scripts.pory"
	.string "down.$"
# 1963 "data/maps/NewBarkTown/scripts.pory"

# 1964 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraGone:
# 1965 "data/maps/NewBarkTown/scripts.pory"
	.string "It steps back into the place\n"
# 1966 "data/maps/NewBarkTown/scripts.pory"
	.string "the road opened, and the road\l"
# 1967 "data/maps/NewBarkTown/scripts.pory"
	.string "closes behind it.\p"
# 1968 "data/maps/NewBarkTown/scripts.pory"
	.string "Nothing is broken. No house, no\n"
# 1969 "data/maps/NewBarkTown/scripts.pory"
	.string "fence, no window.\p"
# 1970 "data/maps/NewBarkTown/scripts.pory"
	.string "It never wanted the town at\n"
# 1971 "data/maps/NewBarkTown/scripts.pory"
	.string "all.$"
# 1972 "data/maps/NewBarkTown/scripts.pory"

# 1973 "data/maps/NewBarkTown/scripts.pory"
@ The people first. Looker, every mission, before the report.
# 1974 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathHurt:
# 1975 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Is anyone hurt?\p"
# 1976 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}? Your Pokémon?\p"
# 1977 "data/maps/NewBarkTown/scripts.pory"
	.string "Chief? Madame?\p"
# 1978 "data/maps/NewBarkTown/scripts.pory"
	.string "…And you. The one with the\n"
# 1979 "data/maps/NewBarkTown/scripts.pory"
	.string "Azumarill. Look at me when I\l"
# 1980 "data/maps/NewBarkTown/scripts.pory"
	.string "ask you.\p"
# 1981 "data/maps/NewBarkTown/scripts.pory"
	.string "…Good. Good.\p"
# 1982 "data/maps/NewBarkTown/scripts.pory"
	.string "The report can wait a moment.$"
# 1983 "data/maps/NewBarkTown/scripts.pory"

# 1984 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmCost:
# 1985 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}The sensors are gone.\p"
# 1986 "data/maps/NewBarkTown/scripts.pory"
	.string "Every one of them. Melted, or\n"
# 1987 "data/maps/NewBarkTown/scripts.pory"
	.string "whatever that was.\p"
# 1988 "data/maps/NewBarkTown/scripts.pory"
	.string "…I don't mind. I have six weeks\n"
# 1989 "data/maps/NewBarkTown/scripts.pory"
	.string "of data.\p"
# 1990 "data/maps/NewBarkTown/scripts.pory"
	.string "The last thirty seconds of it\n"
# 1991 "data/maps/NewBarkTown/scripts.pory"
	.string "are three signatures going into\l"
# 1992 "data/maps/NewBarkTown/scripts.pory"
	.string "one signature.\p"
# 1993 "data/maps/NewBarkTown/scripts.pory"
	.string "Three into one. I watched a\n"
# 1994 "data/maps/NewBarkTown/scripts.pory"
	.string "number do that.$"
# 1995 "data/maps/NewBarkTown/scripts.pory"

# 1996 "data/maps/NewBarkTown/scripts.pory"
@ The gut punch, and the point of the whole mission. Anabel does the
# 1997 "data/maps/NewBarkTown/scripts.pory"
@ arithmetic of four missions out loud.
# 1998 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBWhatItWas:
# 1999 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nine.\p"
# 2000 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief?\p"
# 2001 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nine Ultra Beasts.\n"
# 2002 "data/maps/NewBarkTown/scripts.pory"
	.string "Blackthorn, the Lake, the\l"
# 2003 "data/maps/NewBarkTown/scripts.pory"
	.string "beach, this road.\p"
# 2004 "data/maps/NewBarkTown/scripts.pory"
	.string "It has been at every one of\n"
# 2005 "data/maps/NewBarkTown/scripts.pory"
	.string "them, and it has left with\l"
# 2006 "data/maps/NewBarkTown/scripts.pory"
	.string "every single one of them.\p"
# 2007 "data/maps/NewBarkTown/scripts.pory"
	.string "It was never attacking Johto.\p"
# 2008 "data/maps/NewBarkTown/scripts.pory"
	.string "It was never attacking us at\n"
# 2009 "data/maps/NewBarkTown/scripts.pory"
	.string "all.\p"
# 2010 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…It was collecting.\p"
# 2011 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And we softened them\n"
# 2012 "data/maps/NewBarkTown/scripts.pory"
	.string "for it. Four times.\p"
# 2013 "data/maps/NewBarkTown/scripts.pory"
	.string "Put that in the report, Looker.\p"
# 2014 "data/maps/NewBarkTown/scripts.pory"
	.string "Put that in first.$"
# 2015 "data/maps/NewBarkTown/scripts.pory"

# 2016 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineLost:
# 2017 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}We held the street.\p"
# 2018 "data/maps/NewBarkTown/scripts.pory"
	.string "Not one person on it is hurt,\n"
# 2019 "data/maps/NewBarkTown/scripts.pory"
	.string "and not one window is broken,\l"
# 2020 "data/maps/NewBarkTown/scripts.pory"
	.string "and I want that said plainly\l"
# 2021 "data/maps/NewBarkTown/scripts.pory"
	.string "before anything else.\p"
# 2022 "data/maps/NewBarkTown/scripts.pory"
	.string "And we lost.\p"
# 2023 "data/maps/NewBarkTown/scripts.pory"
	.string "It came for something, it took\n"
# 2024 "data/maps/NewBarkTown/scripts.pory"
	.string "it, and it walked out.\p"
# 2025 "data/maps/NewBarkTown/scripts.pory"
	.string "I have been on the other end of\n"
# 2026 "data/maps/NewBarkTown/scripts.pory"
	.string "a plan like that.\p"
# 2027 "data/maps/NewBarkTown/scripts.pory"
	.string "You do not notice it is a plan\n"
# 2028 "data/maps/NewBarkTown/scripts.pory"
	.string "until it is finished.$"
# 2029 "data/maps/NewBarkTown/scripts.pory"

# 2030 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 2031 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRival:
# 2032 "data/maps/NewBarkTown/scripts.pory"
	.string "I got in.\p"
# 2033 "data/maps/NewBarkTown/scripts.pory"
	.string "I finally got in, and I hit it\n"
# 2034 "data/maps/NewBarkTown/scripts.pory"
	.string "with everything I've got, and\l"
# 2035 "data/maps/NewBarkTown/scripts.pory"
	.string "it didn't even turn its head.\p"
# 2036 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Neither did mine.\p"
# 2037 "data/maps/NewBarkTown/scripts.pory"
	.string "Neither did the Champion's.\p"
# 2038 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not a thing that\n"
# 2039 "data/maps/NewBarkTown/scripts.pory"
	.string "happened to you. That is a\l"
# 2040 "data/maps/NewBarkTown/scripts.pory"
	.string "thing that happened to all of\l"
# 2041 "data/maps/NewBarkTown/scripts.pory"
	.string "us, and you were in it.\p"
# 2042 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}…Yeah.\p"
# 2043 "data/maps/NewBarkTown/scripts.pory"
	.string "Yeah, okay.\p"
# 2044 "data/maps/NewBarkTown/scripts.pory"
	.string "Right. Doors. Forty people to\n"
# 2045 "data/maps/NewBarkTown/scripts.pory"
	.string "let back out.$"
# 2046 "data/maps/NewBarkTown/scripts.pory"

# 2047 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMom:
# 2048 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Come inside when you can.\p"
# 2049 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll leave the light on.\p"
# 2050 "data/maps/NewBarkTown/scripts.pory"
	.string "You know I will.$"
# 2051 "data/maps/NewBarkTown/scripts.pory"

# 2052 "data/maps/NewBarkTown/scripts.pory"
@ The other half of the Olivine briefing, and the only thing anybody has
# 2053 "data/maps/NewBarkTown/scripts.pory"
@ left to hold after a defeat. One box. Do not grow it back into the speech.
# 2054 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelPromise:
# 2055 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{PLAYER}.\p"
# 2056 "data/maps/NewBarkTown/scripts.pory"
	.string "What I told you in that office,\n"
# 2057 "data/maps/NewBarkTown/scripts.pory"
	.string "before any of this.\p"
# 2058 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone who comes through gets\n"
# 2059 "data/maps/NewBarkTown/scripts.pory"
	.string "a hand. Everyone who goes in\l"
# 2060 "data/maps/NewBarkTown/scripts.pory"
	.string "comes home.\p"
# 2061 "data/maps/NewBarkTown/scripts.pory"
	.string "We lost the road today. We did\n"
# 2062 "data/maps/NewBarkTown/scripts.pory"
	.string "not lose that.\p"
# 2063 "data/maps/NewBarkTown/scripts.pory"
	.string "Both. Always both.$"
# 2064 "data/maps/NewBarkTown/scripts.pory"

# 2065 "data/maps/NewBarkTown/scripts.pory"
@ Optional, re-read from VAR_TEMP_4.
# 2066 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathCosmog:
# 2067 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER}.\p"
# 2068 "data/maps/NewBarkTown/scripts.pory"
	.string "It looked at {STR_VAR_1} and it\n"
# 2069 "data/maps/NewBarkTown/scripts.pory"
	.string "chose to leave.\p"
# 2070 "data/maps/NewBarkTown/scripts.pory"
	.string "I have never once known that\n"
# 2071 "data/maps/NewBarkTown/scripts.pory"
	.string "thing to leave something it\l"
# 2072 "data/maps/NewBarkTown/scripts.pory"
	.string "wanted.\p"
# 2073 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep them close. Not because\n"
# 2074 "data/maps/NewBarkTown/scripts.pory"
	.string "they are in danger.\p"
# 2075 "data/maps/NewBarkTown/scripts.pory"
	.string "Because they are the only\n"
# 2076 "data/maps/NewBarkTown/scripts.pory"
	.string "reason it stopped.$"
# 2077 "data/maps/NewBarkTown/scripts.pory"

# 2078 "data/maps/NewBarkTown/scripts.pory"
@ This block IS the hook into the Olivine reunion, design section 7.
# 2079 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBHook:
# 2080 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Looker. They didn't\n"
# 2081 "data/maps/NewBarkTown/scripts.pory"
	.string "scatter.\p"
# 2082 "data/maps/NewBarkTown/scripts.pory"
	.string "It left on a bearing, and the\n"
# 2083 "data/maps/NewBarkTown/scripts.pory"
	.string "three rifts closed toward the\l"
# 2084 "data/maps/NewBarkTown/scripts.pory"
	.string "same one.\p"
# 2085 "data/maps/NewBarkTown/scripts.pory"
	.string "I can put a place on a map now.\p"
# 2086 "data/maps/NewBarkTown/scripts.pory"
	.string "I have never once been able to\n"
# 2087 "data/maps/NewBarkTown/scripts.pory"
	.string "do that.\p"
# 2088 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then the investigation\n"
# 2089 "data/maps/NewBarkTown/scripts.pory"
	.string "is finished, and something else\l"
# 2090 "data/maps/NewBarkTown/scripts.pory"
	.string "begins.\p"
# 2091 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Inspector. Call my\n"
# 2092 "data/maps/NewBarkTown/scripts.pory"
	.string "children. Both of them.\p"
# 2093 "data/maps/NewBarkTown/scripts.pory"
	.string "And Professor Kukui - he has\n"
# 2094 "data/maps/NewBarkTown/scripts.pory"
	.string "earned the room twice over\l"
# 2095 "data/maps/NewBarkTown/scripts.pory"
	.string "without ever setting foot in\l"
# 2096 "data/maps/NewBarkTown/scripts.pory"
	.string "it.\p"
# 2097 "data/maps/NewBarkTown/scripts.pory"
	.string "Not as Aether.\p"
# 2098 "data/maps/NewBarkTown/scripts.pory"
	.string "I owe these people an\n"
# 2099 "data/maps/NewBarkTown/scripts.pory"
	.string "accounting, and two of them are\l"
# 2100 "data/maps/NewBarkTown/scripts.pory"
	.string "mine.\p"
# 2101 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Olivine, then.\p"
# 2102 "data/maps/NewBarkTown/scripts.pory"
	.string "All of us, in that small room.\p"
# 2103 "data/maps/NewBarkTown/scripts.pory"
	.string "I apologise in advance for the\n"
# 2104 "data/maps/NewBarkTown/scripts.pory"
	.string "chairs.\p"
# 2105 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} - bring your partner.\p"
# 2106 "data/maps/NewBarkTown/scripts.pory"
	.string "Not for a test.\p"
# 2107 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone in that room has been\n"
# 2108 "data/maps/NewBarkTown/scripts.pory"
	.string "waiting a long time to meet\l"
# 2109 "data/maps/NewBarkTown/scripts.pory"
	.string "them.$"

# 341 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_0:
# 341 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 341 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 341 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 341 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 341 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
	step_end

# 344 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_1:
# 344 "data/maps/NewBarkTown/scripts.pory"
	jump_down
	step_end

# 347 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_2:
# 347 "data/maps/NewBarkTown/scripts.pory"
	walk_up
	step_end

# 349 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_3:
# 349 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_up
	step_end

# 356 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_4:
# 356 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 356 "data/maps/NewBarkTown/scripts.pory"
	walk_right
	step_end

# 360 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_5:
# 360 "data/maps/NewBarkTown/scripts.pory"
	face_left
	step_end

# 362 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_6:
# 362 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 362 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 362 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 362 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 362 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 364 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_7:
# 364 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_left
	step_end

# 370 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_8:
# 370 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 370 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 370 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 370 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 371 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_9:
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 386 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_0:
# 386 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_right
	step_end

# 392 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_1:
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 392 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 393 "data/maps/NewBarkTown/scripts.pory"
	face_left
	step_end

# 394 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_2:
# 394 "data/maps/NewBarkTown/scripts.pory"
	face_up
	step_end

# 399 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_3:
# 399 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 399 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 399 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 399 "data/maps/NewBarkTown/scripts.pory"
	walk_right
	step_end

# 405 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_4:
# 405 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 405 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 405 "data/maps/NewBarkTown/scripts.pory"
	exit_pokeball
# 405 "data/maps/NewBarkTown/scripts.pory"
	set_visible
	step_end

# 436 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_5:
# 436 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 436 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 436 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 436 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 436 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 436 "data/maps/NewBarkTown/scripts.pory"
	walk_down
	step_end

# 437 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_6:
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 437 "data/maps/NewBarkTown/scripts.pory"
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Text_0:
# 404 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_1:
# 409 "data/maps/NewBarkTown/scripts.pory"
	.string "So you picked...\n"
	.string "a {STR_VAR_1}!$"

NewBarkTown_EventScript_RivalBattle_Text_2:
# 411 "data/maps/NewBarkTown/scripts.pory"
	.string "That's a cute Pokémon you have!$"

NewBarkTown_EventScript_RivalBattle_Text_3:
# 412 "data/maps/NewBarkTown/scripts.pory"
	.string "When you walk with it, it'll become\n"
	.string "more friendly!$"

NewBarkTown_EventScript_RivalBattle_Text_4:
# 414 "data/maps/NewBarkTown/scripts.pory"
	.string "You should turn around and talk to it\n"
	.string "sometimes, too.$"

NewBarkTown_EventScript_RivalBattle_Text_5:
# 416 "data/maps/NewBarkTown/scripts.pory"
	.string "Hey, why don't we have a battle?\n"
	.string "That's what trainers usually do when\l"
	.string "they meet!$"

NewBarkTown_EventScript_RivalBattle_Text_6:
# 422 "data/maps/NewBarkTown/scripts.pory"
	.string "You did really well, {PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_7:
# 429 "data/maps/NewBarkTown/scripts.pory"
	.string "That was really fun, and both of our\n"
	.string "Pokémon did their best!$"

NewBarkTown_EventScript_RivalBattle_Text_8:
# 431 "data/maps/NewBarkTown/scripts.pory"
	.string "You got a task from Elm right?\n"
	.string "I'll leave you to it then.\l"
	.string "See ya!$"

RivalsMailbox_Text_0:
# 452 "data/maps/NewBarkTown/scripts.pory"
	.string "Crystal's house$"

RivalsMailbox_Text_1:
# 454 "data/maps/NewBarkTown/scripts.pory"
	.string "Gold's house$"

NewBarkTown_EventScript_ArcherArcadeCall_Text_0:
# 462 "data/maps/NewBarkTown/scripts.pory"
	.string "???: Greetings, {PLAYER}.\p"
	.string "This is Archer speaking.\p"
	.string "Archer: I've heard of your victory\n"
	.string "in the League and would like to \l"
	.string "offer you an invitation to our \l"
	.string "newly opened Rocket Arcade.\p"
	.string "If you are interested in gambling\n"
	.string "your way to the top, come visit us\l"
	.string "in the Goldenrod Underground.\p"
	.string "I assure you no tricks or traps are\n"
	.string "planned for you this time.$"
