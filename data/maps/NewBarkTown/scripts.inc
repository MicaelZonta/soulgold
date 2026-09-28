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
	call NewBarkTown_EventScript_ApplyUBBarriers      @ Rift Mission 4: fence and barricade
# 15 "data/maps/NewBarkTown/scripts.pory"
	end
# 16 "data/maps/NewBarkTown/scripts.pory"

# 17 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_OnFrame::
# 18 "data/maps/NewBarkTown/scripts.pory"
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
# 19 "data/maps/NewBarkTown/scripts.pory"
	map_script_2 VAR_RIFT_MISSIONS_STATE, 1, NewBarkTown_EventScript_LookerCall
# 20 "data/maps/NewBarkTown/scripts.pory"
	map_script_2 VAR_NEWBARK_TOWN_STATE, 11, NewBarkTown_EventScript_ArcherArcadeCall
# 21 "data/maps/NewBarkTown/scripts.pory"
    map_script_2 VAR_RIVAL_STATE, 0, NewBarkTown_EventScript_RivalIntro
# 22 "data/maps/NewBarkTown/scripts.pory"
    map_script_2 VAR_RIVAL_STATE, 2, NewBarkTown_EventScript_RivalBattle
# 23 "data/maps/NewBarkTown/scripts.pory"
	.2byte 0
# 24 "data/maps/NewBarkTown/scripts.pory"

# 25 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ElmCallAfterLeague::
# 26 "data/maps/NewBarkTown/scripts.pory"
	lock
# 27 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall BlackthornCity_Text_ElmCall
# 28 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 29 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 30 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 7
# 31 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 10
# 32 "data/maps/NewBarkTown/scripts.pory"
	release
# 33 "data/maps/NewBarkTown/scripts.pory"
	end
# 34 "data/maps/NewBarkTown/scripts.pory"

# 35 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 1. Armed by the first Hall of Fame (VAR_RIFT_MISSIONS_STATE = 1);
# 36 "data/maps/NewBarkTown/scripts.pory"
@ fires on the first frame after the player leaves the house. The frame table
# 37 "data/maps/NewBarkTown/scripts.pory"
@ runs the first true entry per frame, so Elm's call (state 6 -> 7) goes first
# 38 "data/maps/NewBarkTown/scripts.pory"
@ and this one on the following frame - one call after the other.
# 39 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LookerCall::
# 40 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 2          @ first instruction: stops re-firing
# 41 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_DAILY_LOOKER_CALL             @ today's call has been made
# 42 "data/maps/NewBarkTown/scripts.pory"
	lock
# 43 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall NewBarkTown_Text_LookerCall
# 44 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 45 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 46 "data/maps/NewBarkTown/scripts.pory"
	release
# 47 "data/maps/NewBarkTown/scripts.pory"
	end
# 48 "data/maps/NewBarkTown/scripts.pory"

# 49 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: the two lines after the calls are goto_if_eq, NOT call_if_eq -
# 50 "data/maps/NewBarkTown/scripts.pory"
@ whoever matches one never comes back here. Any new call must go ABOVE them
# 51 "data/maps/NewBarkTown/scripts.pory"
@ or it silently stops running in NEWBARK_TOWN_STATE 2 and 4. (Rift Mission 4,
# 52 "data/maps/NewBarkTown/scripts.pory"
@ .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md.)
# 53 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_OnTransition::
# 54 "data/maps/NewBarkTown/scripts.pory"
    call Common_EventScript_SetupRivalGfxId
# 55 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_ApplyUBVisibility      @ Rift Mission 4 - must stay above the gotos
# 56 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
# 57 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
# 58 "data/maps/NewBarkTown/scripts.pory"
	end
# 59 "data/maps/NewBarkTown/scripts.pory"

# 60 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Set_TalkToElm::
# 61 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 62 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_LASS, 0, 11
# 63 "data/maps/NewBarkTown/scripts.pory"
	callnative SetTimeBasedEncounters
# 64 "data/maps/NewBarkTown/scripts.pory"
	end
# 65 "data/maps/NewBarkTown/scripts.pory"

# 66 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Set_TalkToMom::
# 67 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_LASS, 0, 11
# 68 "data/maps/NewBarkTown/scripts.pory"
	callnative SetTimeBasedEncounters
# 69 "data/maps/NewBarkTown/scripts.pory"
	end
# 70 "data/maps/NewBarkTown/scripts.pory"

# 71 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LabSign::
# 72 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
# 73 "data/maps/NewBarkTown/scripts.pory"
	end
# 74 "data/maps/NewBarkTown/scripts.pory"

# 75 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TownSign::
# 76 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
# 77 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 78 "data/maps/NewBarkTown/scripts.pory"
	end
# 79 "data/maps/NewBarkTown/scripts.pory"

# 80 "data/maps/NewBarkTown/scripts.pory"

# 81 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Lass::
# 82 "data/maps/NewBarkTown/scripts.pory"
	lock
# 83 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 84 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
# 85 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
# 86 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
# 87 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
# 88 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 89 "data/maps/NewBarkTown/scripts.pory"
	release
# 90 "data/maps/NewBarkTown/scripts.pory"
	end
# 91 "data/maps/NewBarkTown/scripts.pory"
	
# 92 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState2::
# 93 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 94 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 95 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 96 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 97 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 98 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
# 99 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 100 "data/maps/NewBarkTown/scripts.pory"
	release
# 101 "data/maps/NewBarkTown/scripts.pory"
	end
# 102 "data/maps/NewBarkTown/scripts.pory"

# 103 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState3::
# 104 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
# 105 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 106 "data/maps/NewBarkTown/scripts.pory"
	release
# 107 "data/maps/NewBarkTown/scripts.pory"
	end
# 108 "data/maps/NewBarkTown/scripts.pory"

# 109 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState4::
# 110 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 111 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 112 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 113 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 114 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 115 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
# 116 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 117 "data/maps/NewBarkTown/scripts.pory"
	release
# 118 "data/maps/NewBarkTown/scripts.pory"
	end
# 119 "data/maps/NewBarkTown/scripts.pory"

# 120 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Wooper::
# 121 "data/maps/NewBarkTown/scripts.pory"
	lock
# 122 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 123 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 124 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
# 125 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
# 126 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 127 "data/maps/NewBarkTown/scripts.pory"
	release
# 128 "data/maps/NewBarkTown/scripts.pory"
	end
# 129 "data/maps/NewBarkTown/scripts.pory"

# 130 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTrigger::
# 131 "data/maps/NewBarkTown/scripts.pory"
	lock
# 132 "data/maps/NewBarkTown/scripts.pory"
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
# 133 "data/maps/NewBarkTown/scripts.pory"
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
# 134 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
# 135 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 136 "data/maps/NewBarkTown/scripts.pory"
	release
# 137 "data/maps/NewBarkTown/scripts.pory"
	end
# 138 "data/maps/NewBarkTown/scripts.pory"

# 139 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTriggersState2::
# 140 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 141 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 142 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 143 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
# 144 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 145 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
# 146 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 147 "data/maps/NewBarkTown/scripts.pory"
	return
# 148 "data/maps/NewBarkTown/scripts.pory"

# 149 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTriggersState4::
# 150 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 151 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 152 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 153 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
# 154 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 155 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
# 156 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 157 "data/maps/NewBarkTown/scripts.pory"
	return 
# 158 "data/maps/NewBarkTown/scripts.pory"

# 159 "data/maps/NewBarkTown/scripts.pory"

# 160 "data/maps/NewBarkTown/scripts.pory"

# 161 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_FatMan::
# 162 "data/maps/NewBarkTown/scripts.pory"
	lock
# 163 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 164 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
# 165 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
# 166 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 167 "data/maps/NewBarkTown/scripts.pory"
	release
# 168 "data/maps/NewBarkTown/scripts.pory"
	end
# 169 "data/maps/NewBarkTown/scripts.pory"

# 170 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_FatManState2::
# 171 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
# 172 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 173 "data/maps/NewBarkTown/scripts.pory"
	release
# 174 "data/maps/NewBarkTown/scripts.pory"
	end
# 175 "data/maps/NewBarkTown/scripts.pory"

# 176 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Silver::
# 177 "data/maps/NewBarkTown/scripts.pory"
	lock
# 178 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
# 179 "data/maps/NewBarkTown/scripts.pory"
	delay 60
# 180 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 181 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
# 182 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 183 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 184 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
# 185 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BANG
# 186 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
# 187 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
# 188 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 189 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
# 190 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 191 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 192 "data/maps/NewBarkTown/scripts.pory"
	release
# 193 "data/maps/NewBarkTown/scripts.pory"
	end
# 194 "data/maps/NewBarkTown/scripts.pory"

# 195 "data/maps/NewBarkTown/scripts.pory"

# 196 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Door::
# 197 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
# 198 "data/maps/NewBarkTown/scripts.pory"
	end
# 199 "data/maps/NewBarkTown/scripts.pory"

# 200 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan1::
# 201 "data/maps/NewBarkTown/scripts.pory"
	givebp 4
# 202 "data/maps/NewBarkTown/scripts.pory"
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
# 203 "data/maps/NewBarkTown/scripts.pory"
	end
# 204 "data/maps/NewBarkTown/scripts.pory"

# 205 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan2::
# 206 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 207 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 208 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 209 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 210 "data/maps/NewBarkTown/scripts.pory"
	end
# 211 "data/maps/NewBarkTown/scripts.pory"

# 212 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan3::
# 213 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 5
# 214 "data/maps/NewBarkTown/scripts.pory"
	
# 215 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
# 216 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
# 217 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
# 218 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
# 219 "data/maps/NewBarkTown/scripts.pory"
	end
# 220 "data/maps/NewBarkTown/scripts.pory"

# 221 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_SilverPushesPlayer:
# 222 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 223 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 224 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 225 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 226 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 227 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 228 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 229 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 230 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 231 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 232 "data/maps/NewBarkTown/scripts.pory"

# 233 "data/maps/NewBarkTown/scripts.pory"

# 234 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerPushedBySilver:
# 235 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 236 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 237 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 238 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 239 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 240 "data/maps/NewBarkTown/scripts.pory"
	jump_2_down
# 241 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 242 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 243 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 244 "data/maps/NewBarkTown/scripts.pory"

# 245 "data/maps/NewBarkTown/scripts.pory"
	
# 246 "data/maps/NewBarkTown/scripts.pory"

# 247 "data/maps/NewBarkTown/scripts.pory"

# 248 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_FaceDown:
# 249 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 250 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 251 "data/maps/NewBarkTown/scripts.pory"

# 252 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LabSign:
# 253 "data/maps/NewBarkTown/scripts.pory"
	.string "Prof. Elm's Lab$"
# 254 "data/maps/NewBarkTown/scripts.pory"

# 255 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Door:
# 256 "data/maps/NewBarkTown/scripts.pory"
	.string "The door is locked.$"
# 257 "data/maps/NewBarkTown/scripts.pory"

# 258 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Wooper:
# 259 "data/maps/NewBarkTown/scripts.pory"
	.string "Wooper: Woooooop.$"
# 260 "data/maps/NewBarkTown/scripts.pory"

# 261 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_FatManState2:
# 262 "data/maps/NewBarkTown/scripts.pory"
	.string "Wow, your Pokégear is impressive!\n"
# 263 "data/maps/NewBarkTown/scripts.pory"
	.string "Did your mom get it for you?$"
# 264 "data/maps/NewBarkTown/scripts.pory"

# 265 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_FatManState3:
# 266 "data/maps/NewBarkTown/scripts.pory"
	.string "Yo, {PLAYER}!\p"
# 267 "data/maps/NewBarkTown/scripts.pory"
	.string "I hear Prof. Elm discovered\n"
# 268 "data/maps/NewBarkTown/scripts.pory"
	.string "some new Pokémon.$"
# 269 "data/maps/NewBarkTown/scripts.pory"

# 270 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState2:
# 271 "data/maps/NewBarkTown/scripts.pory"
	.string "Wait, {PLAYER}!\p"
# 272 "data/maps/NewBarkTown/scripts.pory"
	.string "It's dangerous to go out\n"
# 273 "data/maps/NewBarkTown/scripts.pory"
	.string "without a Pokémon!\p"
# 274 "data/maps/NewBarkTown/scripts.pory"
	.string "Wild Pokémon jump out of the grass\n"
# 275 "data/maps/NewBarkTown/scripts.pory"
	.string "on the way to the next town.$"
# 276 "data/maps/NewBarkTown/scripts.pory"

# 277 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState3:
# 278 "data/maps/NewBarkTown/scripts.pory"
	.string "Oh! Your Pokémon is adorable!\n"
# 279 "data/maps/NewBarkTown/scripts.pory"
	.string "I wish I had one!$"
# 280 "data/maps/NewBarkTown/scripts.pory"

# 281 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState4:
# 282 "data/maps/NewBarkTown/scripts.pory"
	.string "Hi, {PLAYER}! Leaving again?\p"
# 283 "data/maps/NewBarkTown/scripts.pory"
	.string "You should tell your mom if\n"
# 284 "data/maps/NewBarkTown/scripts.pory"
	.string "you are leaving.$"
# 285 "data/maps/NewBarkTown/scripts.pory"

# 286 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState5:
# 287 "data/maps/NewBarkTown/scripts.pory"
	.string "Call your mom on your Pokégear\n"
# 288 "data/maps/NewBarkTown/scripts.pory"
	.string "to let her know how you're doing.$\p"
# 289 "data/maps/NewBarkTown/scripts.pory"

# 290 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Silver1:
# 291 "data/maps/NewBarkTown/scripts.pory"
	.string ". . .\p"
# 292 "data/maps/NewBarkTown/scripts.pory"
	.string "So this is the famous Elm\n"
# 293 "data/maps/NewBarkTown/scripts.pory"
	.string "Pokémon Lab…$"
# 294 "data/maps/NewBarkTown/scripts.pory"

# 295 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Silver2:
# 296 "data/maps/NewBarkTown/scripts.pory"
	.string "…What are you staring at?$"
# 297 "data/maps/NewBarkTown/scripts.pory"

# 298 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Sign:
# 299 "data/maps/NewBarkTown/scripts.pory"
	.string "New Bark Town\p"
# 300 "data/maps/NewBarkTown/scripts.pory"
	.string "The Town Where the Winds of\n"
# 301 "data/maps/NewBarkTown/scripts.pory"
	.string "a New Beginning Blow$"
# 302 "data/maps/NewBarkTown/scripts.pory"

# 303 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_PlayersHouseMailbox::
# 304 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
# 305 "data/maps/NewBarkTown/scripts.pory"
	end
# 306 "data/maps/NewBarkTown/scripts.pory"

# 307 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ElmsHouseMailbox::
# 308 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
# 309 "data/maps/NewBarkTown/scripts.pory"
	end
# 310 "data/maps/NewBarkTown/scripts.pory"

# 311 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_PlayersHouse:
# 312 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}'s House$"
# 313 "data/maps/NewBarkTown/scripts.pory"

# 314 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ElmsHouse:
# 315 "data/maps/NewBarkTown/scripts.pory"
	.string "Prof. Elm's House$"
# 316 "data/maps/NewBarkTown/scripts.pory"

# 317 "data/maps/NewBarkTown/scripts.pory"
@ Looker's first call (script revision V2, 25/09/2026). Cordial and
# 318 "data/maps/NewBarkTown/scripts.pory"
@ professional, and short: it congratulates, introduces, asks and names the
# 319 "data/maps/NewBarkTown/scripts.pory"
@ house. It does NOT retell the holiday cover over the phone and it does not
# 320 "data/maps/NewBarkTown/scripts.pory"
@ hide the request behind three attempts at an introduction. No creature, no
# 321 "data/maps/NewBarkTown/scripts.pory"
@ town and no name is given away.
# 322 "data/maps/NewBarkTown/scripts.pory"
@ It also sets FLAG_DAILY_LOOKER_CALL: from here on Looker rings once a day
# 323 "data/maps/NewBarkTown/scripts.pory"
@ while a briefing is pending in Olivine (ShouldDoRiftMissionCall,
# 324 "data/maps/NewBarkTown/scripts.pory"
@ src/field_control_avatar.c), and the day he calls in person counts.
# 325 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LookerCall:
# 326 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Hello, {PLAYER}?\n"
# 327 "data/maps/NewBarkTown/scripts.pory"
	.string "Congratulations on becoming\l"
# 328 "data/maps/NewBarkTown/scripts.pory"
	.string "Champion!\p"
# 329 "data/maps/NewBarkTown/scripts.pory"
	.string "My name is Looker.\n"
# 330 "data/maps/NewBarkTown/scripts.pory"
	.string "International Police.\p"
# 331 "data/maps/NewBarkTown/scripts.pory"
	.string "My colleague and I need your\n"
# 332 "data/maps/NewBarkTown/scripts.pory"
	.string "help with an investigation in\l"
# 333 "data/maps/NewBarkTown/scripts.pory"
	.string "Johto.\p"
# 334 "data/maps/NewBarkTown/scripts.pory"
	.string "Please meet us in Olivine.\p"
# 335 "data/maps/NewBarkTown/scripts.pory"
	.string "Our house is the one nearest\n"
# 336 "data/maps/NewBarkTown/scripts.pory"
	.string "the Gym.\p"
# 337 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll explain when you arrive.$"

NewBarkTown_EventScript_RivalIntro::
# 341 "data/maps/NewBarkTown/scripts.pory"
	lock
# 342 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_0
# 343 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 344 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WALL_HIT
# 345 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_1
# 346 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 347 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 348 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_2
# 349 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 350 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
# 351 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 352 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 353 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
# 354 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 355 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 356 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 357 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_4
# 358 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 359 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, Common_Movement_ExclamationMark
# 360 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 361 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_5
# 362 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 363 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_6
# 364 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 365 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
# 366 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 367 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 368 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
# 369 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 370 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 371 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_8
# 372 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_9
# 373 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 374 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 375 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_RIVAL
# 376 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL
# 377 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL2
# 378 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIVAL_STATE, 1
# 379 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 380 "data/maps/NewBarkTown/scripts.pory"
	release
	end


NewBarkTown_EventScript_RivalBattle::
# 385 "data/maps/NewBarkTown/scripts.pory"
	lock
# 386 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 387 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
# 388 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 389 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 390 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
# 391 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 392 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 393 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_1
# 395 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_2
# 396 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_MARILL2
# 397 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, Common_Movement_ExclamationMark
# 398 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 399 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 400 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_PLAYER, NewBarkTown_EventScript_RivalBattle_Movement_3
# 401 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 402 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_5
# 403 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 404 "data/maps/NewBarkTown/scripts.pory"
	createfieldmugshotrival
# 405 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_0
# 406 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_EventScript_RivalBattle_Movement_4
# 407 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 408 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 409 "data/maps/NewBarkTown/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 410 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_1
# 412 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_2
# 413 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_3
# 415 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_4
# 417 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_5
# 420 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_NO_WHITEOUT
# 421 "data/maps/NewBarkTown/scripts.pory"
	checkplayergender
# 422 "data/maps/NewBarkTown/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_EventScript_RivalBattle_2
# 425 "data/maps/NewBarkTown/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVALGOLD1, NewBarkTown_EventScript_RivalBattle_Text_6
NewBarkTown_EventScript_RivalBattle_1:
# 427 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_NO_WHITEOUT
# 428 "data/maps/NewBarkTown/scripts.pory"
	special HealPlayerParty
# 429 "data/maps/NewBarkTown/scripts.pory"
	createfieldmugshotrival
# 430 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_7
# 432 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_8
# 435 "data/maps/NewBarkTown/scripts.pory"
	removefieldmugshot
# 436 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 437 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_5
# 438 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_6
# 439 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 440 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_RIVAL
# 441 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL
# 442 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL2
# 443 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 444 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIVAL_STATE, 3
# 445 "data/maps/NewBarkTown/scripts.pory"
	release
	end

NewBarkTown_EventScript_RivalBattle_2:
# 423 "data/maps/NewBarkTown/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVALCRYSTAL1, NewBarkTown_EventScript_RivalBattle_Text_6
	goto NewBarkTown_EventScript_RivalBattle_1


RivalsMailbox::
# 450 "data/maps/NewBarkTown/scripts.pory"
	lock
# 451 "data/maps/NewBarkTown/scripts.pory"
	checkplayergender
# 452 "data/maps/NewBarkTown/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq RivalsMailbox_2
# 455 "data/maps/NewBarkTown/scripts.pory"
	msgbox RivalsMailbox_Text_1
RivalsMailbox_1:
# 457 "data/maps/NewBarkTown/scripts.pory"
	release
	end

RivalsMailbox_2:
# 453 "data/maps/NewBarkTown/scripts.pory"
	msgbox RivalsMailbox_Text_0
	goto RivalsMailbox_1


NewBarkTown_EventScript_ArcherArcadeCall::
# 462 "data/maps/NewBarkTown/scripts.pory"
	lock
# 463 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall NewBarkTown_EventScript_ArcherArcadeCall_Text_0
# 478 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 479 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 480 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 12
# 481 "data/maps/NewBarkTown/scripts.pory"
	release
	end


# 485 "data/maps/NewBarkTown/scripts.pory"

# 486 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 487 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 - New Bark. Kartana, Guzzlord, Nihilego and Ultra Necrozma.
# 488 "data/maps/NewBarkTown/scripts.pory"
@ Script: .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_SCRIPT_V2.md
# 489 "data/maps/NewBarkTown/scripts.pory"
@ Plan:   .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md
# 490 "data/maps/NewBarkTown/scripts.pory"
@
# 491 "data/maps/NewBarkTown/scripts.pory"
@ The story in four lines. Elm's six weeks of records, compared with the
# 492 "data/maps/NewBarkTown/scripts.pory"
@ police's, showed three points waking up in New Bark; the team comes to clear
# 493 "data/maps/NewBarkTown/scripts.pory"
@ the street before they open, with Aether's containment equipment. The three
# 494 "data/maps/NewBarkTown/scripts.pory"
@ open anyway and do three different things - Kartana cuts the fence, Guzzlord
# 495 "data/maps/NewBarkTown/scripts.pory"
@ eats the south barricade, Nihilego drifts into the gap and stops Mom halfway
# 496 "data/maps/NewBarkTown/scripts.pory"
@ to the shelter. The team holds, the player wins their front, the field
# 497 "data/maps/NewBarkTown/scripts.pory"
@ really does cut the links - and Necrozma breaks it, absorbs all three, turns
# 498 "data/maps/NewBarkTown/scripts.pory"
@ Ultra, cannot hold that light steady and backs out through its own opening.
# 499 "data/maps/NewBarkTown/scripts.pory"
@ The town is protected. The Ultra Beasts still have to be recovered.
# 500 "data/maps/NewBarkTown/scripts.pory"
@
# 501 "data/maps/NewBarkTown/scripts.pory"
@ Floor plan (dump_mapa.py NewBarkTown; y grows DOWNWARD). There IS water in
# 502 "data/maps/NewBarkTown/scripts.pory"
@ this layout - the pond at x 25..26, y 11..14 is MB_OCEAN_WATER with
# 503 "data/maps/NewBarkTown/scripts.pory"
@ collision 0 - but nothing in this scene goes east of x 22.
# 504 "data/maps/NewBarkTown/scripts.pory"
@
# 505 "data/maps/NewBarkTown/scripts.pory"
@       x= 10 11 12 13 14 15 16 17 18 19 20 21 22
# 506 "data/maps/NewBarkTown/scripts.pory"
@   y= 9    D  #  .  #  k  f  N  r  #  #  #  #  #     D lab door (warp 10,9)
# 507 "data/maps/NewBarkTown/scripts.pory"
@   y=10    .  E  .  .  F  F  F  f  #  #  #  #  #     F temporary fence (setmetatile)
# 508 "data/maps/NewBarkTown/scripts.pory"
@   y=11    .  .  W  U  .  m  .  #  #  #  d  #  #     d player's house door (warp 20,11)
# 509 "data/maps/NewBarkTown/scripts.pory"
@   y=12    .  R  z  .  .  .  P  .  .  .  *  K  A     * (20,12) Fly/blackout/arrival
# 510 "data/maps/NewBarkTown/scripts.pory"
@   y=13    .  .  .  .  .  .  .  .  .  .  .  M  .
# 511 "data/maps/NewBarkTown/scripts.pory"
@   y=14    #  .  .  .  .  .  .  .  a  .  s  .  .     a Anabel's post (18,14)
# 512 "data/maps/NewBarkTown/scripts.pory"
@   y=15    .  .  .  .  .  .  .  .  .  .  B  B  B     B log barricade (setmetatile)
# 513 "data/maps/NewBarkTown/scripts.pory"
@   y=16    .  .  .  n  .  .  .  .  .  .  .  g  .
# 514 "data/maps/NewBarkTown/scripts.pory"
@
# 515 "data/maps/NewBarkTown/scripts.pory"
@   Prep (map.json):  K Looker (21,12)  A Anabel (22,12)  M Mom (21,13)
# 516 "data/maps/NewBarkTown/scripts.pory"
@                     R Gold/Crystal (11,12)  z Azumarill (12,12)
# 517 "data/maps/NewBarkTown/scripts.pory"
@                     E Elm (11,10), beside the lab door - his recording station
# 518 "data/maps/NewBarkTown/scripts.pory"
@                       is just inside it; he never leaves this tile
# 519 "data/maps/NewBarkTown/scripts.pory"
@                     U Lusamine (13,11), at the west marker's control
# 520 "data/maps/NewBarkTown/scripts.pory"
@   Operation:        P player (16,12), W west emitter (12,11), east emitter
# 521 "data/maps/NewBarkTown/scripts.pory"
@                     on Anabel's old tile (22,12); m Milotic (15,11),
# 522 "data/maps/NewBarkTown/scripts.pory"
@                     s Snorlax (20,14), Anabel -> a (18,14). Both emitters
# 523 "data/maps/NewBarkTown/scripts.pory"
@                     use OBJ_EVENT_GFX_AETHER_EMITTER, the mission's own sprite.
# 524 "data/maps/NewBarkTown/scripts.pory"
@   The three openings: k Kartana (14,9) behind the fence, g Guzzlord (21,16)
# 525 "data/maps/NewBarkTown/scripts.pory"
@                     behind the barricade, n Nihilego (13,16) on the south lawn
# 526 "data/maps/NewBarkTown/scripts.pory"
@   Necrozma:         N (16,9), outside the area, in the flower bed; the main
# 527 "data/maps/NewBarkTown/scripts.pory"
@                     opening r (17,9) only appears for its retreat
# 528 "data/maps/NewBarkTown/scripts.pory"
@   Partner:          (17,13), east of the player after the line steps back
# 529 "data/maps/NewBarkTown/scripts.pory"
@
# 530 "data/maps/NewBarkTown/scripts.pory"
@ LOOKER'S POCKET. (21,11) is the house wall, (22,12) Anabel and (21,13) Mom, so
# 531 "data/maps/NewBarkTown/scripts.pory"
@ on the first attempt the only talk tile is (20,12) - the arrival tile, which
# 532 "data/maps/NewBarkTown/scripts.pory"
@ nothing ever stands on. On a retry Anabel and Mom have moved, the east
# 533 "data/maps/NewBarkTown/scripts.pory"
@ emitter fills (22,12), and (21,13) is the second talk tile: UBSceneRetry
# 534 "data/maps/NewBarkTown/scripts.pory"
@ normalises both (getplayerxy).
# 535 "data/maps/NewBarkTown/scripts.pory"
@
# 536 "data/maps/NewBarkTown/scripts.pory"
@ Camera. Nothing moves the camera: the player stands at (16,12) for every
# 537 "data/maps/NewBarkTown/scripts.pory"
@ beat that is seen from the "command" spot, which frames x 9..23 and, with a
# 538 "data/maps/NewBarkTown/scripts.pory"
@ text box open, y 8..14. That holds the lab door, Elm, the rival's corridor,
# 539 "data/maps/NewBarkTown/scripts.pory"
@ the fence, the house, Looker, Anabel and Snorlax in one screen. The spawn
# 540 "data/maps/NewBarkTown/scripts.pory"
@ window is wider (x-9..x+10, y-7..y+9, src/event_object_movement.c:3149), so
# 541 "data/maps/NewBarkTown/scripts.pory"
@ no object is ever despawned and respawned from its template mid-scene - EXCEPT
# 542 "data/maps/NewBarkTown/scripts.pory"
@ when the player walks to Guzzlord at (20,14): the window becomes x 11..30
# 543 "data/maps/NewBarkTown/scripts.pory"
@ and Looker's post sync below matters. Every actor that ends a walk away from
# 544 "data/maps/NewBarkTown/scripts.pory"
@ its template gets a setobjectxyperm (and movement type) right after it.
# 545 "data/maps/NewBarkTown/scripts.pory"
@
# 546 "data/maps/NewBarkTown/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 547 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_1 - Anabel, Gold/Crystal, Azumarill, Lusamine (never removed)
# 548 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_2 - Kartana, Guzzlord, Nihilego (removed together)
# 549 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_3 - Elm
# 550 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_4 - Mom (removed at the lab door, re-added for the aftermath)
# 551 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_5 - Necrozma          FLAG_TEMP_6 - Ultra Necrozma
# 552 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_7 - Looker (removed at the lab door, re-added coming back out)
# 553 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_8 - Snorlax           FLAG_TEMP_9 - Milotic
# 554 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_A - the two emitters  FLAG_TEMP_B - the main opening
# 555 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_C - the player's Cosmog-family partner, four templates
# 556 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_E - FLAG_TEMP_HIDE_FOLLOWER: set on the YES, and on every load of
# 557 "data/maps/NewBarkTown/scripts.pory"
@                 a retry. It REMOVES the follower object (UpdateFollowingPokemon)
# 558 "data/maps/NewBarkTown/scripts.pory"
@                 instead of only hiding it, which frees its slot. The final
# 559 "data/maps/NewBarkTown/scripts.pory"
@                 warp zeroes it and the follower comes back.
# 560 "data/maps/NewBarkTown/scripts.pory"
@ Every actor that is ever removeobject'd has its OWN flag: removeobject sets
# 561 "data/maps/NewBarkTown/scripts.pory"
@ the template's flag, and a shared one would respawn a partner's template on
# 562 "data/maps/NewBarkTown/scripts.pory"
@ the next camera step after its sibling was re-added.
# 563 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_2 - battle outcome
# 564 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_3 - the pick: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego. Survives
# 565 "data/maps/NewBarkTown/scripts.pory"
@                the battle (coming back from a battle does not reload the map)
# 566 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_4 - Cosmog-family species shown (SPECIES_NONE = none), sampled
# 567 "data/maps/NewBarkTown/scripts.pory"
@                AFTER the battle
# 568 "data/maps/NewBarkTown/scripts.pory"
@
# 569 "data/maps/NewBarkTown/scripts.pory"
@ Persistent: FLAG_EVENT_ULTRABEAST_NEWBARK (set <=> state 9) and
# 570 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_NEWBARK_UB_ENGAGED (everything up to the choice has played; a blackout
# 571 "data/maps/NewBarkTown/scripts.pory"
@ comes back to the staged street). Both cleared by UBFinish.
# 572 "data/maps/NewBarkTown/scripts.pory"
@
# 573 "data/maps/NewBarkTown/scripts.pory"
@ OBJECT BUDGET (OBJECT_EVENTS_COUNT 16, player included). Peak while the three
# 574 "data/maps/NewBarkTown/scripts.pory"
@ beasts are out and Mom has not crossed yet: player + Looker, Anabel, Mom,
# 575 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal, Azumarill, Elm, Lusamine, Snorlax, Milotic, two emitters and
# 576 "data/maps/NewBarkTown/scripts.pory"
@ three beasts = 15 (the follower was removed on the YES). With Necrozma: Mom
# 577 "data/maps/NewBarkTown/scripts.pory"
@ is inside by then, so 15 again. That is why Necrozma ARRIVES through a
# 578 "data/maps/NewBarkTown/scripts.pory"
@ distortion (flash and sparkle) and the main opening is an object only for
# 579 "data/maps/NewBarkTown/scripts.pory"
@ the retreat, when the beasts are gone. Do not add a persistent actor here
# 580 "data/maps/NewBarkTown/scripts.pory"
@ without taking one out.
# 581 "data/maps/NewBarkTown/scripts.pory"
@ SPRITE PALETTES: every species overworld sprite loads its own palette, and so
# 582 "data/maps/NewBarkTown/scripts.pory"
@ do Looker, Lusamine, Elm and the emitter. The peak is about 14 plus field
# 583 "data/maps/NewBarkTown/scripts.pory"
@ effects - test it at night, with everyone on screen.
# 584 "data/maps/NewBarkTown/scripts.pory"
@
# 585 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: seven residents (locals 1, 2, 4, 5, 6, 7, 8) carry
# 586 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_EVENT_ULTRABEAST_NEWBARK in their "flag" field; a removeobject on any of
# 587 "data/maps/NewBarkTown/scripts.pory"
@ them sets it and empties the town. Never clear FLAG_HIDE_NEWBARK_RIVALMARILL
# 588 "data/maps/NewBarkTown/scripts.pory"
@ (locals 9-11, the old Gold/Crystal and two Marill).
# 589 "data/maps/NewBarkTown/scripts.pory"
@ While the event flag is set, every building door except the lab (the shelter)
# 590 "data/maps/NewBarkTown/scripts.pory"
@ and the player's house refuses the player (sLockedTownDoors,
# 591 "data/maps/NewBarkTown/scripts.pory"
@ src/field_control_avatar.c -> NewBarkTown_EventScript_DoorLocked).
# 592 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 593 "data/maps/NewBarkTown/scripts.pory"

# 594 "data/maps/NewBarkTown/scripts.pory"
@ Metatiles of the two temporary barriers (primary johto_general):
# 595 "data/maps/NewBarkTown/scripts.pory"
@   0x0E7 white picket fence on grass - the fence the team put across the
# 596 "data/maps/NewBarkTown/scripts.pory"
@         flower bed between the lab and the house
# 597 "data/maps/NewBarkTown/scripts.pory"
@   0x2E0 log barricade on sand - across the south road
# 598 "data/maps/NewBarkTown/scripts.pory"
@ and the originals they cover, restored when a beast breaks through.
# 599 "data/maps/NewBarkTown/scripts.pory"
.set NB_MT_FENCE,        0x0E7
# 600 "data/maps/NewBarkTown/scripts.pory"
.set NB_MT_LOGS,         0x2E0
# 601 "data/maps/NewBarkTown/scripts.pory"
.set NB_MT_FLOWER,       0x004
# 602 "data/maps/NewBarkTown/scripts.pory"
.set NB_MT_ROAD,         0x0DC
# 603 "data/maps/NewBarkTown/scripts.pory"
.set NB_MT_ROAD_EDGE_E,  0x105
# 604 "data/maps/NewBarkTown/scripts.pory"

# 605 "data/maps/NewBarkTown/scripts.pory"
@ Called from NewBarkTown_OnLoad. ON_LOAD runs before the map is drawn - on a
# 606 "data/maps/NewBarkTown/scripts.pory"
@ normal load AND when coming back from a battle (InitMapFromSavedGame, after
# 607 "data/maps/NewBarkTown/scripts.pory"
@ the saved view is restored) - so the barriers always match the state and
# 608 "data/maps/NewBarkTown/scripts.pory"
@ the scene never has to redraw them after the battle. Nothing is ever drawn
# 609 "data/maps/NewBarkTown/scripts.pory"
@ outside the incident: the layout file itself has no fence and no logs, so
# 610 "data/maps/NewBarkTown/scripts.pory"
@ the reload in UBFinish is what takes them away.
# 611 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ApplyUBBarriers::
# 612 "data/maps/NewBarkTown/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_UBBarriersDone
# 613 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 14, 10, NB_MT_FENCE, TRUE
# 614 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 15, 10, NB_MT_FENCE, TRUE
# 615 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 16, 10, NB_MT_FENCE, TRUE
# 616 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 20, 15, NB_MT_LOGS, TRUE
# 617 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 21, 15, NB_MT_LOGS, TRUE
# 618 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 22, 15, NB_MT_LOGS, TRUE
# 619 "data/maps/NewBarkTown/scripts.pory"
	goto_if_unset FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBBarriersDone
# 620 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFenceCut
# 621 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBarricadeBroken
# 622 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBarriersDone::
# 623 "data/maps/NewBarkTown/scripts.pory"
	return
# 624 "data/maps/NewBarkTown/scripts.pory"

# 625 "data/maps/NewBarkTown/scripts.pory"
@ Kartana's cut: one section, the west one, back to the flower bed it was
# 626 "data/maps/NewBarkTown/scripts.pory"
@ standing on. The other two stay up.
# 627 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFenceCut::
# 628 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 14, 10, NB_MT_FLOWER, FALSE
# 629 "data/maps/NewBarkTown/scripts.pory"
	return
# 630 "data/maps/NewBarkTown/scripts.pory"

# 631 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord's side of the barricade: the two east logs, back to road.
# 632 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBarricadeBroken::
# 633 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 21, 15, NB_MT_ROAD, FALSE
# 634 "data/maps/NewBarkTown/scripts.pory"
	setmetatile 22, 15, NB_MT_ROAD_EDGE_E, FALSE
# 635 "data/maps/NewBarkTown/scripts.pory"
	return
# 636 "data/maps/NewBarkTown/scripts.pory"

# 637 "data/maps/NewBarkTown/scripts.pory"
@ Called from NewBarkTown_OnTransition, which runs before any object spawns -
# 638 "data/maps/NewBarkTown/scripts.pory"
@ so setflag/clearflag/setobjectxyperm work here and removeobject would not.
# 639 "data/maps/NewBarkTown/scripts.pory"
@ Three shapes of the street:
# 640 "data/maps/NewBarkTown/scripts.pory"
@   1. no incident: every mission actor hidden.
# 641 "data/maps/NewBarkTown/scripts.pory"
@   2. first attempt (state 9): the prep cast on their map.json tiles; the
# 642 "data/maps/NewBarkTown/scripts.pory"
@      beasts, partners, emitters and everything else come from the scene.
# 643 "data/maps/NewBarkTown/scripts.pory"
@   3. FLAG_NEWBARK_UB_ENGAGED (retry): the street as it was at the choice -
# 644 "data/maps/NewBarkTown/scripts.pory"
@      fence cut, barricade broken, three beasts, Snorlax, Milotic, emitters,
# 645 "data/maps/NewBarkTown/scripts.pory"
@      Anabel at her post, Mom inside the lab (NewBarkTown_Lab shows her).
# 646 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ApplyUBVisibility::
# 647 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_2
# 648 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_5
# 649 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_6
# 650 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_8
# 651 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_9
# 652 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_A
# 653 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_B
# 654 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_C
# 655 "data/maps/NewBarkTown/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_HideUBCast
# 656 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_1
# 657 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 658 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_7
# 659 "data/maps/NewBarkTown/scripts.pory"
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_StageUBRetry
# 660 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 661 "data/maps/NewBarkTown/scripts.pory"
	return
# 662 "data/maps/NewBarkTown/scripts.pory"

# 663 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_HideUBCast::
# 664 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_1
# 665 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_3
# 666 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_4
# 667 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_7
# 668 "data/maps/NewBarkTown/scripts.pory"
	return
# 669 "data/maps/NewBarkTown/scripts.pory"

# 670 "data/maps/NewBarkTown/scripts.pory"
@ The choice-time formation, rebuilt from templates. setobjectxyperm and not
# 671 "data/maps/NewBarkTown/scripts.pory"
@ setobjectxy: templates are re-read on every load, so none of this leaks into
# 672 "data/maps/NewBarkTown/scripts.pory"
@ the next visit. Mom stays hidden (FLAG_TEMP_4 still set): she is sheltered.
# 673 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_StageUBRetry::
# 674 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_HIDE_FOLLOWER
# 675 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_2
# 676 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_8
# 677 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_9
# 678 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_A
# 679 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_KARTANA, 14, 10
# 680 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_GUZZLORD, 21, 14
# 681 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_NIHILEGO, 13, 14
# 682 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_AZUMARILL, 13, 12
# 683 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_AZUMARILL, MOVEMENT_TYPE_FACE_DOWN
# 684 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_ANABEL, 18, 14
# 685 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_ANABEL, MOVEMENT_TYPE_FACE_RIGHT
# 686 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_SNORLAX, MOVEMENT_TYPE_FACE_RIGHT
# 687 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_MILOTIC, MOVEMENT_TYPE_FACE_LEFT
# 688 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_ELM, MOVEMENT_TYPE_FACE_UP
# 689 "data/maps/NewBarkTown/scripts.pory"
	return
# 690 "data/maps/NewBarkTown/scripts.pory"

# 691 "data/maps/NewBarkTown/scripts.pory"
@ A note on the locked doors, not a person: no speaker plaque (the author's
# 692 "data/maps/NewBarkTown/scripts.pory"
@ default for notes and narration).
# 693 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_DoorLocked::
# 694 "data/maps/NewBarkTown/scripts.pory"
	lockall
# 695 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBDoorNote, MSGBOX_DEFAULT
# 696 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 697 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 698 "data/maps/NewBarkTown/scripts.pory"
	end
# 699 "data/maps/NewBarkTown/scripts.pory"

# 700 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 701 "data/maps/NewBarkTown/scripts.pory"
@ Staging helpers.
# 702 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 703 "data/maps/NewBarkTown/scripts.pory"

# 704 "data/maps/NewBarkTown/scripts.pory"
@ Flash. fadescreenswapbuffers and NOT fadescreen: fadescreen copies
# 705 "data/maps/NewBarkTown/scripts.pory"
@ gPlttBufferFaded over gPlttBufferUnfaded, and the FADE_FROM_* after it
# 706 "data/maps/NewBarkTown/scripts.pory"
@ re-tints an already tinted buffer - at night every flash darkened the town
# 707 "data/maps/NewBarkTown/scripts.pory"
@ by ~0.46 until it went black (implementation doc, revision 5).
# 708 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFlash::
# 709 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 710 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 711 "data/maps/NewBarkTown/scripts.pory"
	return
# 712 "data/maps/NewBarkTown/scripts.pory"

# 713 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBShake::
# 714 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 1   @ vertical pan
# 715 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 716 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 12  @ num shakes
# 717 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 718 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 719 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 720 "data/maps/NewBarkTown/scripts.pory"
	return
# 721 "data/maps/NewBarkTown/scripts.pory"

# 722 "data/maps/NewBarkTown/scripts.pory"
@ An opening wavering: a short sideways tremor and the warp sound, no flash -
# 723 "data/maps/NewBarkTown/scripts.pory"
@ it must not read as another attack.
# 724 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRiftPulse::
# 725 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_TELEPORT
# 726 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 0
# 727 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1
# 728 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 6
# 729 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 3
# 730 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 731 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 732 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 733 "data/maps/NewBarkTown/scripts.pory"
	return
# 734 "data/maps/NewBarkTown/scripts.pory"

# 735 "data/maps/NewBarkTown/scripts.pory"
@ The field between the two markers: both emitters light, then a line of
# 736 "data/maps/NewBarkTown/scripts.pory"
@ light runs across the road between them.
# 737 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFieldLine::
# 738 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_BARRIER
# 739 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 12, 11, 0
# 740 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 22, 12, 0
# 741 "data/maps/NewBarkTown/scripts.pory"
	delay 8
# 742 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 14, 13, 0
# 743 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 17, 13, 0
# 744 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 20, 13, 0
# 745 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 746 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 747 "data/maps/NewBarkTown/scripts.pory"
	return
# 748 "data/maps/NewBarkTown/scripts.pory"

# 749 "data/maps/NewBarkTown/scripts.pory"
@ One pattern on Elm's instrument.
# 750 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBeep::
# 751 "data/maps/NewBarkTown/scripts.pory"
	playse SE_SELECT
# 752 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 753 "data/maps/NewBarkTown/scripts.pory"
	delay 4
# 754 "data/maps/NewBarkTown/scripts.pory"
	return
# 755 "data/maps/NewBarkTown/scripts.pory"

# 756 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 757 "data/maps/NewBarkTown/scripts.pory"
@ Conversations before the YES (V2 section 6). Each actor turns back to its
# 758 "data/maps/NewBarkTown/scripts.pory"
@ map.json facing at the end, so an odd talk tile leaves nobody crooked. On a
# 759 "data/maps/NewBarkTown/scripts.pory"
@ retry each one has a short line of its own: nobody repeats the preparation.
# 760 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 761 "data/maps/NewBarkTown/scripts.pory"

# 762 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine at the west marker's control (13,11). A short introduction: no
# 763 "data/maps/NewBarkTown/scripts.pory"
@ photographs, no letter, no confession, no "the only one who knows".
# 764 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamine::
# 765 "data/maps/NewBarkTown/scripts.pory"
	lock
# 766 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 767 "data/maps/NewBarkTown/scripts.pory"
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBLusamineRetry
# 768 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineIdle, MSGBOX_DEFAULT
# 769 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBLusamineEnd
# 770 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamineRetry::
# 771 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineRetry, MSGBOX_DEFAULT
# 772 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamineEnd::
# 773 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 774 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 775 "data/maps/NewBarkTown/scripts.pory"
	release
# 776 "data/maps/NewBarkTown/scripts.pory"
	end
# 777 "data/maps/NewBarkTown/scripts.pory"

# 778 "data/maps/NewBarkTown/scripts.pory"
@ Elm beside his own door (11,10). His station is just inside it.
# 779 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElm::
# 780 "data/maps/NewBarkTown/scripts.pory"
	lock
# 781 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 782 "data/maps/NewBarkTown/scripts.pory"
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBElmRetry
# 783 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmIdle, MSGBOX_DEFAULT
# 784 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 785 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_SOUTH
# 786 "data/maps/NewBarkTown/scripts.pory"
	release
# 787 "data/maps/NewBarkTown/scripts.pory"
	end
# 788 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElmRetry::
# 789 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmPositions, MSGBOX_DEFAULT
# 790 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 791 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_NORTH
# 792 "data/maps/NewBarkTown/scripts.pory"
	release
# 793 "data/maps/NewBarkTown/scripts.pory"
	end
# 794 "data/maps/NewBarkTown/scripts.pory"

# 795 "data/maps/NewBarkTown/scripts.pory"
@ Mom (21,13), helping the last residents across. Her usual heal lives in her
# 796 "data/maps/NewBarkTown/scripts.pory"
@ own interaction: "Have you rested?" - NO heals, YES leaves it there. Once she
# 797 "data/maps/NewBarkTown/scripts.pory"
@ is sheltered (retry) she is not in the street at all: she heals in the lab.
# 798 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMom::
# 799 "data/maps/NewBarkTown/scripts.pory"
	lock
# 800 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 801 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomIdle, MSGBOX_YESNO
# 802 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, YES, NewBarkTown_EventScript_UBMomEnd
# 803 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomHeal, MSGBOX_DEFAULT
# 804 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 805 "data/maps/NewBarkTown/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 806 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMomEnd::
# 807 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 808 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_NORTH
# 809 "data/maps/NewBarkTown/scripts.pory"
	release
# 810 "data/maps/NewBarkTown/scripts.pory"
	end
# 811 "data/maps/NewBarkTown/scripts.pory"

# 812 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal (11,12), on the corridor to the lab with Azumarill already out
# 813 "data/maps/NewBarkTown/scripts.pory"
@ of its Ball beside them.
# 814 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRival::
# 815 "data/maps/NewBarkTown/scripts.pory"
	lock
# 816 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 817 "data/maps/NewBarkTown/scripts.pory"
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBRivalRetry
# 818 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIdle, MSGBOX_DEFAULT
# 819 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalEnd
# 820 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalRetry::
# 821 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalCover, MSGBOX_DEFAULT
# 822 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalEnd::
# 823 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 824 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_EAST
# 825 "data/maps/NewBarkTown/scripts.pory"
	release
# 826 "data/maps/NewBarkTown/scripts.pory"
	end
# 827 "data/maps/NewBarkTown/scripts.pory"

# 828 "data/maps/NewBarkTown/scripts.pory"
@ Anabel: (22,12) before the YES, (18,14) on a retry.
# 829 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabel::
# 830 "data/maps/NewBarkTown/scripts.pory"
	lock
# 831 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 832 "data/maps/NewBarkTown/scripts.pory"
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBAnabelRetry
# 833 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 834 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 835 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
# 836 "data/maps/NewBarkTown/scripts.pory"
	release
# 837 "data/maps/NewBarkTown/scripts.pory"
	end
# 838 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabelRetry::
# 839 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRetryNotReady, MSGBOX_DEFAULT
# 840 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 841 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_EAST
# 842 "data/maps/NewBarkTown/scripts.pory"
	release
# 843 "data/maps/NewBarkTown/scripts.pory"
	end
# 844 "data/maps/NewBarkTown/scripts.pory"

# 845 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 846 "data/maps/NewBarkTown/scripts.pory"
@ Looker (21,12). First attempt: only reachable from (20,12). Nothing changes
# 847 "data/maps/NewBarkTown/scripts.pory"
@ before the YES; the YES is the last exit point.
# 848 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 849 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLooker::
# 850 "data/maps/NewBarkTown/scripts.pory"
	lock
# 851 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 852 "data/maps/NewBarkTown/scripts.pory"
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBLookerRetry
# 853 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLookerGreet, MSGBOX_DEFAULT
# 854 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBReady, MSGBOX_YESNO
# 855 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBNotReady
# 856 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBScene
# 857 "data/maps/NewBarkTown/scripts.pory"

# 858 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNotReady::
# 859 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNotReady, MSGBOX_DEFAULT
# 860 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 861 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST
# 862 "data/maps/NewBarkTown/scripts.pory"
	release
# 863 "data/maps/NewBarkTown/scripts.pory"
	end
# 864 "data/maps/NewBarkTown/scripts.pory"

# 865 "data/maps/NewBarkTown/scripts.pory"
@ Retry (V2 section 19): the introduction is remembered. Looker reports, and
# 866 "data/maps/NewBarkTown/scripts.pory"
@ Anabel asks - YES/NO under her plaque. Nothing seen before is replayed.
# 867 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLookerRetry::
# 868 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRetryLooker, MSGBOX_DEFAULT
# 869 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRetryAnabel, MSGBOX_YESNO
# 870 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBRetryNotReady
# 871 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBSceneRetry
# 872 "data/maps/NewBarkTown/scripts.pory"

# 873 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRetryNotReady::
# 874 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRetryNotReady, MSGBOX_DEFAULT
# 875 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 876 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST
# 877 "data/maps/NewBarkTown/scripts.pory"
	release
# 878 "data/maps/NewBarkTown/scripts.pory"
	end
# 879 "data/maps/NewBarkTown/scripts.pory"

# 880 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 881 "data/maps/NewBarkTown/scripts.pory"
@ The YES (V2 section 7). The player walks to the command spot (16,12) - the
# 882 "data/maps/NewBarkTown/scripts.pory"
@ camera follows and from here on frames the whole street. Then the equipment
# 883 "data/maps/NewBarkTown/scripts.pory"
@ goes out, visibly: Lusamine sets the west emitter beside her control,
# 884 "data/maps/NewBarkTown/scripts.pory"
@ Anabel sets the east one on the tile she was standing on and walks to her
# 885 "data/maps/NewBarkTown/scripts.pory"
@ post, and a short test lights the line between them. Elm is in frame at
# 886 "data/maps/NewBarkTown/scripts.pory"
@ (11,10) for his line. The partners come out of their Balls last, each
# 887 "data/maps/NewBarkTown/scripts.pory"
@ before its own words.
# 888 "data/maps/NewBarkTown/scripts.pory"
@ Walks, all sequential, all checked with dump_mapa.py:
# 889 "data/maps/NewBarkTown/scripts.pory"
@   player (20,12) -> (16,12) along y=12
# 890 "data/maps/NewBarkTown/scripts.pory"
@   Anabel (22,12) -> (22,13) [faces up, east emitter at (22,12)]
# 891 "data/maps/NewBarkTown/scripts.pory"
@          -> (22,14) -> (21,14) -> (20,14) -> (19,14) -> (18,14), faces east
# 892 "data/maps/NewBarkTown/scripts.pory"
@ Snorlax comes out at (20,14), Milotic at (15,11).
# 893 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 894 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBScene::
# 895 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 896 "data/maps/NewBarkTown/scripts.pory"
	lockall
# 897 "data/maps/NewBarkTown/scripts.pory"
	hidefollower
# 898 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_HIDE_FOLLOWER
# 899 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToCommand
# 900 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 901 "data/maps/NewBarkTown/scripts.pory"
	@ West marker, set by Lusamine beside her own control.
# 902 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_WEST
# 903 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PC_ON
# 904 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_A
# 905 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_EMITTER_WEST
# 906 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 907 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 908 "data/maps/NewBarkTown/scripts.pory"
	@ East marker, set by Anabel on her way to her post.
# 909 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_StepDownFaceUp
# 910 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 911 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PC_ON
# 912 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_EMITTER_EAST
# 913 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 914 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_AnabelToPost
# 915 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 916 "data/maps/NewBarkTown/scripts.pory"
	@ The short test: a line of light between the points, and it goes out.
# 917 "data/maps/NewBarkTown/scripts.pory"
	delay 16
# 918 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFieldLine
# 919 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBFieldExplanation, MSGBOX_DEFAULT
# 920 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBFieldPositions, MSGBOX_DEFAULT
# 921 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 922 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_NodLeft
# 923 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 924 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 925 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmPositions, MSGBOX_DEFAULT
# 926 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 927 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_NORTH       @ to his station, inside the door
# 928 "data/maps/NewBarkTown/scripts.pory"
	@ Snorlax, out of the Ball onto the free south-east front.
# 929 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 930 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 931 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_8
# 932 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_SNORLAX
# 933 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 934 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_SNORLAX, CRY_MODE_NORMAL
# 935 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 936 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelPartner, MSGBOX_DEFAULT
# 937 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 938 "data/maps/NewBarkTown/scripts.pory"
	@ Milotic, beside Lusamine's control, facing the fence.
# 939 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 940 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 941 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_9
# 942 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_MILOTIC
# 943 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 944 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_MILOTIC, CRY_MODE_NORMAL
# 945 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 946 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusaminePartner, MSGBOX_DEFAULT
# 947 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 948 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 949 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBOpenings
# 950 "data/maps/NewBarkTown/scripts.pory"

# 951 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 952 "data/maps/NewBarkTown/scripts.pory"
@ Three openings, three different things (V2 section 8).
# 953 "data/maps/NewBarkTown/scripts.pory"
@ The sensors answer first, in a short run; Anabel feels it now that she is
# 954 "data/maps/NewBarkTown/scripts.pory"
@ close - no speech about it. The town theme leaves on her warning and the
# 955 "data/maps/NewBarkTown/scripts.pory"
@ threat theme is on BEFORE the reveal (save_song TRUE: the boss battle hands
# 956 "data/maps/NewBarkTown/scripts.pory"
@ it back instead of the town's).
# 957 "data/maps/NewBarkTown/scripts.pory"
@ The openings are framed one at a time - the player turns to each - with
# 958 "data/maps/NewBarkTown/scripts.pory"
@ separate cries, and none of the three walks in step with another.
# 959 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 960 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBOpenings::
# 961 "data/maps/NewBarkTown/scripts.pory"
	delay 20
# 962 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 963 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 964 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 965 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 966 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, Common_Movement_ExclamationMark
# 967 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 968 "data/maps/NewBarkTown/scripts.pory"
	fadeoutbgm 4
# 969 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelOpening, MSGBOX_DEFAULT
# 970 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 971 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 972 "data/maps/NewBarkTown/scripts.pory"
	@ North, behind the fence.
# 973 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 974 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WARP_IN
# 975 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 14, 9, 0
# 976 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 977 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_2
# 978 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_KARTANA
# 979 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 980 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 981 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 982 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 983 "data/maps/NewBarkTown/scripts.pory"
	@ South, behind the barricade.
# 984 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 985 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WARP_IN
# 986 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 21, 16, 0
# 987 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 988 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_GUZZLORD
# 989 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 990 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 991 "data/maps/NewBarkTown/scripts.pory"
	@ The lawn south of the road, in the middle.
# 992 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 993 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WARP_IN
# 994 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 13, 16, 0
# 995 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 996 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NIHILEGO
# 997 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 998 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 999 "data/maps/NewBarkTown/scripts.pory"
	delay 16
# 1000 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1001 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAppear, MSGBOX_DEFAULT
# 1002 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1003 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBKartanaCuts
# 1004 "data/maps/NewBarkTown/scripts.pory"

# 1005 "data/maps/NewBarkTown/scripts.pory"
@ KARTANA OPENS. It cuts the west section of the fence - a real change of the
# 1006 "data/maps/NewBarkTown/scripts.pory"
@ metatile, back to the flower bed under it - and steps into the gap (14,10).
# 1007 "data/maps/NewBarkTown/scripts.pory"
@ Milotic at (15,11) turns to it (x 14 < 15: west). Nothing is cut that is not
# 1008 "data/maps/NewBarkTown/scripts.pory"
@ put back by the final reload.
# 1009 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBKartanaCuts::
# 1010 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1011 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_AttackDown
# 1012 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_CUT
# 1013 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1014 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFenceCut
# 1015 "data/maps/NewBarkTown/scripts.pory"
	special DrawWholeMapView
# 1016 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1017 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_StepDown
# 1018 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1019 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MILOTIC, DIR_WEST
# 1020 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1021 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, Common_Movement_ExclamationMark
# 1022 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 1023 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBKartanaBreaks, MSGBOX_DEFAULT
# 1024 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1025 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBGuzzlordBreaks
# 1026 "data/maps/NewBarkTown/scripts.pory"

# 1027 "data/maps/NewBarkTown/scripts.pory"
@ GUZZLORD DESTROYS. It rams the east half of the barricade, the two logs go
# 1028 "data/maps/NewBarkTown/scripts.pory"
@ back to road, and it advances (21,16) -> (21,15) -> (21,14): right under Mom
# 1029 "data/maps/NewBarkTown/scripts.pory"
@ at (21,13), and beside Snorlax at (20,14), which turns east to it. It takes
# 1030 "data/maps/NewBarkTown/scripts.pory"
@ from the team a route that looked protected. It eats a barricade, not a
# 1031 "data/maps/NewBarkTown/scripts.pory"
@ person, and there is no graphic damage.
# 1032 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBGuzzlordBreaks::
# 1033 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1034 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_AttackUp
# 1035 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_BITE
# 1036 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1037 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1038 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBarricadeBroken
# 1039 "data/maps/NewBarkTown/scripts.pory"
	special DrawWholeMapView
# 1040 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 1041 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_GuzzlordAdvances
# 1042 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1043 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1044 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_SNORLAX, DIR_EAST
# 1045 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1046 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MOM, Common_Movement_ExclamationMark
# 1047 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MOM
# 1048 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBGuzzlordBreaks, MSGBOX_DEFAULT
# 1049 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1050 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBNihilegoDrifts
# 1051 "data/maps/NewBarkTown/scripts.pory"

# 1052 "data/maps/NewBarkTown/scripts.pory"
@ NIHILEGO PRESSES THE RETREAT. Mom, the last person helping the shelter,
# 1053 "data/maps/NewBarkTown/scripts.pory"
@ starts across the road to the lab: (21,13) -> west along y=13 -> (16,13),
# 1054 "data/maps/NewBarkTown/scripts.pory"
@ right under the player. Nihilego drifts up from the lawn into the same lane:
# 1055 "data/maps/NewBarkTown/scripts.pory"
@ (13,16) -> (13,15) -> (13,14) -> (13,13), three slow steps, and arrives after
# 1056 "data/maps/NewBarkTown/scripts.pory"
@ she stops. Nobody ordered it: the three behaviours together make the siege.
# 1057 "data/maps/NewBarkTown/scripts.pory"
@ Then Azumarill intercepts from the SIDE - (12,12) -> (13,12), facing down,
# 1058 "data/maps/NewBarkTown/scripts.pory"
@ never under Mom's sprite - and a short water attack pushes Nihilego back one
# 1059 "data/maps/NewBarkTown/scripts.pory"
@ tile to (13,14). It is repelled, not beaten; the rival holds their spot.
# 1060 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNihilegoDrifts::
# 1061 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_MomCrosses
# 1062 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_NihilegoDrifts
# 1063 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MOM
# 1064 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 1065 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1066 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1067 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MOM, Common_Movement_ExclamationMark
# 1068 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MOM
# 1069 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1070 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIntercept, MSGBOX_DEFAULT
# 1071 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1072 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillIntercepts
# 1073 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1074 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_AZUMARILL, CRY_MODE_ENCOUNTER
# 1075 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AttackDown
# 1076 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_BUBBLE_BEAM
# 1077 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1078 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_KnockedBackDown
# 1079 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1080 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1081 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1082 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelCorridor, MSGBOX_DEFAULT
# 1083 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1084 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBMomAndLusamine
# 1085 "data/maps/NewBarkTown/scripts.pory"

# 1086 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1087 "data/maps/NewBarkTown/scripts.pory"
@ Mom and Lusamine - one decision, not a lecture (V2 section 9).
# 1088 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine leaves her control to reorganise the front and walks
# 1089 "data/maps/NewBarkTown/scripts.pory"
@ (13,11) -> (14,11) -> (14,12) -> (14,13) -> (15,13), facing east: west of
# 1090 "data/maps/NewBarkTown/scripts.pory"
@ Mom (16,13), who is south of the player (16,12). (14,11) is right under
# 1091 "data/maps/NewBarkTown/scripts.pory"
@ Kartana, with Milotic beside her at (15,11) - that is the cover.
# 1092 "data/maps/NewBarkTown/scripts.pory"
@ Mom looks at the player (north), then at Lusamine (west). Lusamine looks at
# 1093 "data/maps/NewBarkTown/scripts.pory"
@ the rival holding the corridor (west) and at Anabel holding the other front
# 1094 "data/maps/NewBarkTown/scripts.pory"
@ (east), and accepts a concrete split. She is not transformed by it.
# 1095 "data/maps/NewBarkTown/scripts.pory"
@ Then Looker comes for Mom, and the two of them cross to the lab: Mom leads,
# 1096 "data/maps/NewBarkTown/scripts.pory"
@ Looker follows one step behind on the same path (a delay_16 in front of his
# 1097 "data/maps/NewBarkTown/scripts.pory"
@ steps keeps them a tile apart on every step). Both go through the door, it
# 1098 "data/maps/NewBarkTown/scripts.pory"
@ closes, and Looker comes back out alone once she is safe.
# 1099 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1100 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMomAndLusamine::
# 1101 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_LusamineToMom
# 1102 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 1103 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
# 1104 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
# 1105 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineControl, MSGBOX_DEFAULT
# 1106 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1107 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_NORTH
# 1108 "data/maps/NewBarkTown/scripts.pory"
	delay 24
# 1109 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
# 1110 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomTrust, MSGBOX_DEFAULT
# 1111 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1112 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_WEST
# 1113 "data/maps/NewBarkTown/scripts.pory"
	delay 20
# 1114 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_NORTH
# 1115 "data/maps/NewBarkTown/scripts.pory"
	delay 16
# 1116 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 1117 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineAccepts, MSGBOX_DEFAULT
# 1118 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1119 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_LusamineBackToControl
# 1120 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 1121 "data/maps/NewBarkTown/scripts.pory"
	@ Looker (21,12) -> (21,13) -> west to (17,13), behind Mom.
# 1122 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerToMom
# 1123 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1124 "data/maps/NewBarkTown/scripts.pory"
	@ Mom (16,13) -> (10,13) -> (10,10); Looker (17,13) -> (10,13) -> (10,11).
# 1125 "data/maps/NewBarkTown/scripts.pory"
	@ (13,13) passes between Azumarill (13,12) and Nihilego (13,14): covered.
# 1126 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_MomToLab
# 1127 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerToLab
# 1128 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MOM
# 1129 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1130 "data/maps/NewBarkTown/scripts.pory"
	opendoor 10, 9
# 1131 "data/maps/NewBarkTown/scripts.pory"
	waitdooranim
# 1132 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_StepUp
# 1133 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MOM
# 1134 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_MOM                  @ sets FLAG_TEMP_4, hers alone
# 1135 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_StepUpTwice
# 1136 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1137 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_LOOKER               @ sets FLAG_TEMP_7, his alone
# 1138 "data/maps/NewBarkTown/scripts.pory"
	closedoor 10, 9
# 1139 "data/maps/NewBarkTown/scripts.pory"
	waitdooranim
# 1140 "data/maps/NewBarkTown/scripts.pory"
	delay 40
# 1141 "data/maps/NewBarkTown/scripts.pory"
	@ Looker back out, and back to his post by the house. His template is
# 1142 "data/maps/NewBarkTown/scripts.pory"
	@ moved to the door first and synced to the post at the end, so a
# 1143 "data/maps/NewBarkTown/scripts.pory"
	@ respawn at any point puts him where he really is.
# 1144 "data/maps/NewBarkTown/scripts.pory"
	opendoor 10, 9
# 1145 "data/maps/NewBarkTown/scripts.pory"
	waitdooranim
# 1146 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_LOOKER, 10, 9
# 1147 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_LOOKER, MOVEMENT_TYPE_FACE_DOWN
# 1148 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_7
# 1149 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_LOOKER
# 1150 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_StepDown
# 1151 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1152 "data/maps/NewBarkTown/scripts.pory"
	closedoor 10, 9
# 1153 "data/maps/NewBarkTown/scripts.pory"
	waitdooranim
# 1154 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerBackToPost
# 1155 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1156 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_LOOKER, 21, 12
# 1157 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_LOOKER, MOVEMENT_TYPE_FACE_LEFT
# 1158 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBChoose
# 1159 "data/maps/NewBarkTown/scripts.pory"

# 1160 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1161 "data/maps/NewBarkTown/scripts.pory"
@ Retry after a blackout or an interrupted battle (V2 section 19). The street
# 1162 "data/maps/NewBarkTown/scripts.pory"
@ was staged by ON_TRANSITION. The player goes to the command spot and straight
# 1163 "data/maps/NewBarkTown/scripts.pory"
@ to the choice - any target, not necessarily the one that was lost. The
# 1164 "data/maps/NewBarkTown/scripts.pory"
@ threat theme is set again (a map load clears savedMusic).
# 1165 "data/maps/NewBarkTown/scripts.pory"
@ From (20,12): west along y=12. From (21,13), the retry's second talk tile:
# 1166 "data/maps/NewBarkTown/scripts.pory"
@ west along y=13 to (16,13), then up. Both lanes are empty in this formation.
# 1167 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1168 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSceneRetry::
# 1169 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1170 "data/maps/NewBarkTown/scripts.pory"
	lockall
# 1171 "data/maps/NewBarkTown/scripts.pory"
	hidefollower
# 1172 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 1173 "data/maps/NewBarkTown/scripts.pory"
	getplayerxy VAR_0x8004, VAR_0x8005
# 1174 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_0x8005, 13, NewBarkTown_EventScript_UBRetryFromSouth
# 1175 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToCommand
# 1176 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1177 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBChoose
# 1178 "data/maps/NewBarkTown/scripts.pory"

# 1179 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRetryFromSouth::
# 1180 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerRetryFromSouth
# 1181 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1182 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBChoose
# 1183 "data/maps/NewBarkTown/scripts.pory"

# 1184 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1185 "data/maps/NewBarkTown/scripts.pory"
@ The choice (V2 section 10). Checkpoint first: from here a blackout comes
# 1186 "data/maps/NewBarkTown/scripts.pory"
@ back as a retry. Anabel asks, so the menu wears her plaque. No cancel.
# 1187 "data/maps/NewBarkTown/scripts.pory"
@ The pick is per attempt.
# 1188 "data/maps/NewBarkTown/scripts.pory"
@   pick        Lusamine/Milotic   Anabel/Snorlax   Gold/Crystal/Azumarill
# 1189 "data/maps/NewBarkTown/scripts.pory"
@   0 Kartana   Nihilego           Guzzlord         hold the rear and the exit
# 1190 "data/maps/NewBarkTown/scripts.pory"
@   1 Guzzlord  Nihilego           Kartana          hold the flank
# 1191 "data/maps/NewBarkTown/scripts.pory"
@   2 Nihilego  Guzzlord           Kartana          keep it off the door
# 1192 "data/maps/NewBarkTown/scripts.pory"
@ Partners move first, along free lanes; the player takes the front last.
# 1193 "data/maps/NewBarkTown/scripts.pory"
@ Milotic -> Nihilego: (15,11) -> (15,14) -> (14,14), faces west.
# 1194 "data/maps/NewBarkTown/scripts.pory"
@ Milotic -> Guzzlord: (15,11) -> (15,13) -> east to (21,13), faces south.
# 1195 "data/maps/NewBarkTown/scripts.pory"
@ Snorlax -> Kartana: (20,14) -> (20,13) -> west to (15,13) -> (15,11)
# 1196 "data/maps/NewBarkTown/scripts.pory"
@                     -> (14,11), faces north. Always AFTER Milotic's walk.
# 1197 "data/maps/NewBarkTown/scripts.pory"
@ Player -> Kartana (14,11) up; Guzzlord (20,14) east; Nihilego (14,14) west.
# 1198 "data/maps/NewBarkTown/scripts.pory"
@ Every partner that walks gets its template synced (setobjectxyperm).
# 1199 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1200 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBChoose::
# 1201 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_NEWBARK_UB_ENGAGED
# 1202 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
# 1203 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1204 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 1205 "data/maps/NewBarkTown/scripts.pory"
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_Text_ChoiceKartana, NewBarkTown_Text_ChoiceGuzzlord, NewBarkTown_Text_ChoiceNihilego
# 1206 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 Kartana, 1 Guzzlord, 2 Nihilego
# 1207 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1208 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPickGuzzlord
# 1209 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPickNihilego
# 1210 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1211 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
# 1212 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1213 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedKartanaLusamine, MSGBOX_DEFAULT
# 1214 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedKartanaAnabel, MSGBOX_DEFAULT
# 1215 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1216 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBMiloticToNihilego
# 1217 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalCover
# 1218 "data/maps/NewBarkTown/scripts.pory"

# 1219 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickGuzzlord::
# 1220 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1221 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
# 1222 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1223 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedGuzzlordAnabel, MSGBOX_DEFAULT
# 1224 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedGuzzlordLusamine, MSGBOX_DEFAULT
# 1225 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1226 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBMiloticToNihilego
# 1227 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBSnorlaxToKartana
# 1228 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalCover
# 1229 "data/maps/NewBarkTown/scripts.pory"

# 1230 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine follows Nihilego with her eyes for a moment before she answers -
# 1231 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego (13,14) is straight south of her control (13,11). A hesitation, not
# 1232 "data/maps/NewBarkTown/scripts.pory"
@ an argument, and the beast is nobody's property.
# 1233 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickNihilego::
# 1234 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1235 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
# 1236 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1237 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_SOUTH
# 1238 "data/maps/NewBarkTown/scripts.pory"
	delay 40
# 1239 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedNihilegoLusamine, MSGBOX_DEFAULT
# 1240 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedNihilegoAnabel, MSGBOX_DEFAULT
# 1241 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1242 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 1243 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_MiloticToGuzzlord
# 1244 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1245 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_MILOTIC, 21, 13
# 1246 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_MILOTIC, MOVEMENT_TYPE_FACE_DOWN
# 1247 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBSnorlaxToKartana
# 1248 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalCover
# 1249 "data/maps/NewBarkTown/scripts.pory"

# 1250 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMiloticToNihilego::
# 1251 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_MiloticToNihilego
# 1252 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1253 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_MILOTIC, 14, 14
# 1254 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_MILOTIC, MOVEMENT_TYPE_FACE_LEFT
# 1255 "data/maps/NewBarkTown/scripts.pory"
	return
# 1256 "data/maps/NewBarkTown/scripts.pory"

# 1257 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSnorlaxToKartana::
# 1258 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_SnorlaxToKartana
# 1259 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
# 1260 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_SNORLAX, 14, 11
# 1261 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_SNORLAX, MOVEMENT_TYPE_FACE_UP
# 1262 "data/maps/NewBarkTown/scripts.pory"
	return
# 1263 "data/maps/NewBarkTown/scripts.pory"

# 1264 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal hold the way back in every branch - no double battle. Then the
# 1265 "data/maps/NewBarkTown/scripts.pory"
@ player takes the chosen front.
# 1266 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalCover::
# 1267 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalCover, MSGBOX_DEFAULT
# 1268 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1269 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPlayerToGuzzlord
# 1270 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPlayerToNihilego
# 1271 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToKartana
# 1272 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1273 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 1274 "data/maps/NewBarkTown/scripts.pory"

# 1275 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPlayerToGuzzlord::
# 1276 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToGuzzlord
# 1277 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1278 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 1279 "data/maps/NewBarkTown/scripts.pory"

# 1280 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPlayerToNihilego::
# 1281 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToNihilego
# 1282 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1283 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 1284 "data/maps/NewBarkTown/scripts.pory"

# 1285 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1286 "data/maps/NewBarkTown/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 1287 "data/maps/NewBarkTown/scripts.pory"
@ battle. B_FLAG_NO_WHITEOUT is deliberately NOT set: losing is a blackout and
# 1288 "data/maps/NewBarkTown/scripts.pory"
@ a retry. Running is not blocked: "Run" in a boss is forfeiting
# 1289 "data/maps/NewBarkTown/scripts.pory"
@ (CanPlayerForfeitBattle, src/battle_main.c) and counts as a loss.
# 1290 "data/maps/NewBarkTown/scripts.pory"
@ Capture is blocked while the link is still active (B_FLAG_NO_CATCHING,
# 1291 "data/maps/NewBarkTown/scripts.pory"
@ cleared by the engine after the battle).
# 1292 "data/maps/NewBarkTown/scripts.pory"
@
# 1293 "data/maps/NewBarkTown/scripts.pory"
@ Fourth step of the ladder after Blackthorn (3 bars / Lv75 / x120), Mahogany
# 1294 "data/maps/NewBarkTown/scripts.pory"
@ (4 / Lv80 / x130) and Cherrygrove (4 / Lv85 / x140). Unchanged by the V2
# 1295 "data/maps/NewBarkTown/scripts.pory"
@ script. If playtesting says "wall" instead of "threat", turn the screws in
# 1296 "data/maps/NewBarkTown/scripts.pory"
@ this order, one at a time:
# 1297 "data/maps/NewBarkTown/scripts.pory"
@   1. drop the held item from the boss that gets complained about
# 1298 "data/maps/NewBarkTown/scripts.pory"
@   2. multiplier 150 -> 145 -> 140
# 1299 "data/maps/NewBarkTown/scripts.pory"
@   3. swap the setup/control move for a fourth attacking move
# 1300 "data/maps/NewBarkTown/scripts.pory"
@   4. level 90 -> 85
# 1301 "data/maps/NewBarkTown/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 1302 "data/maps/NewBarkTown/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 1303 "data/maps/NewBarkTown/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between.
# 1304 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1305 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBattle::
# 1306 "data/maps/NewBarkTown/scripts.pory"
	setflag B_FLAG_NO_CATCHING
# 1307 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBSetupGuzzlord
# 1308 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBSetupNihilego
# 1309 "data/maps/NewBarkTown/scripts.pory"
	@ Kartana - the one that CLIMBS. Paper defenses, Swords Dance, a pure
# 1310 "data/maps/NewBarkTown/scripts.pory"
	@ damage item: it either snowballs or it dies.
# 1311 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1312 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 1313 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1314 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_KARTANA, 90, ITEM_MUSCLE_BAND
# 1315 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_SACRED_SWORD, MOVE_SMART_STRIKE
# 1316 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 1317 "data/maps/NewBarkTown/scripts.pory"

# 1318 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord - the one that ENDURES. Absurd HP, Leftovers and Toxic: attrition.
# 1319 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupGuzzlord::
# 1320 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1321 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 1322 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1323 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_GUZZLORD, 90, ITEM_LEFTOVERS
# 1324 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_TOXIC, MOVE_CRUNCH, MOVE_HEAVY_SLAM, MOVE_DRAGON_TAIL
# 1325 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 1326 "data/maps/NewBarkTown/scripts.pory"

# 1327 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego - the one that INTERFERES. Acid Spray shreds the player's Sp.Def,
# 1328 "data/maps/NewBarkTown/scripts.pory"
@ Toxic stacks on top, and Black Sludge heals it for being Poison.
# 1329 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupNihilego::
# 1330 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1331 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 1332 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1333 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_NIHILEGO, 90, ITEM_BLACK_SLUDGE
# 1334 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_ACID_SPRAY, MOVE_TOXIC, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE
# 1335 "data/maps/NewBarkTown/scripts.pory"

# 1336 "data/maps/NewBarkTown/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the player
# 1337 "data/maps/NewBarkTown/scripts.pory"
@ out and hands them back HEALED at (20,12) (DoWhiteOut heals; New Bark has no
# 1338 "data/maps/NewBarkTown/scripts.pory"
@ Center), and FLAG_NEWBARK_UB_ENGAGED makes that load a retry. CAUGHT and RAN
# 1339 "data/maps/NewBarkTown/scripts.pory"
@ are unreachable but handled: anything that is not WON is a retry.
# 1340 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBStartBattle::
# 1341 "data/maps/NewBarkTown/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 1342 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1343 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 1344 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 1345 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, NewBarkTown_EventScript_UBResolved
# 1346 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUnresolved
# 1347 "data/maps/NewBarkTown/scripts.pory"

# 1348 "data/maps/NewBarkTown/scripts.pory"
@ Interrupted, not lost - and nobody says the beasts escaped. Nothing past the
# 1349 "data/maps/NewBarkTown/scripts.pory"
@ checkpoint happened yet: no field, no Necrozma. The reload puts the street
# 1350 "data/maps/NewBarkTown/scripts.pory"
@ back as a retry, with the player on the arrival tile.
# 1351 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUnresolved::
# 1352 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUnresolved, MSGBOX_DEFAULT
# 1353 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1354 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1355 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 1356 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1357 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1358 "data/maps/NewBarkTown/scripts.pory"
	end
# 1359 "data/maps/NewBarkTown/scripts.pory"

# 1360 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1361 "data/maps/NewBarkTown/scripts.pory"
@ The defence works (V2 section 11). A battle does not reload the map, so every
# 1362 "data/maps/NewBarkTown/scripts.pory"
@ object is where the scene left it; ON_LOAD re-applied the cut fence and the
# 1363 "data/maps/NewBarkTown/scripts.pory"
@ broken barricade. The threat theme is set again and the player's beast is
# 1364 "data/maps/NewBarkTown/scripts.pory"
@ shown weakened first. Then the player steps back to the command spot (16,12)
# 1365 "data/maps/NewBarkTown/scripts.pory"
@ - "returns to the scene after the battle" - which re-frames the street, and
# 1366 "data/maps/NewBarkTown/scripts.pory"
@ Milotic and Snorlax finish their fronts one at a time.
# 1367 "data/maps/NewBarkTown/scripts.pory"
@ Back to (16,12):  from (14,11) east, east, south;
# 1368 "data/maps/NewBarkTown/scripts.pory"
@                   from (20,14) north, west x4, north;
# 1369 "data/maps/NewBarkTown/scripts.pory"
@                   from (14,14) east, east, north, north.
# 1370 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1371 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBResolved::
# 1372 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 1373 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAfterGuzzlord
# 1374 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBAfterNihilego
# 1375 "data/maps/NewBarkTown/scripts.pory"
	@ Kartana: Milotic has Nihilego (west of it), Snorlax has Guzzlord (east).
# 1376 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_Weakened
# 1377 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_WEAK
# 1378 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1379 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1380 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerBackFromKartana
# 1381 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1382 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBMiloticFinishesWest
# 1383 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBSnorlaxFinishesEast
# 1384 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBFieldStarts
# 1385 "data/maps/NewBarkTown/scripts.pory"

# 1386 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterGuzzlord::
# 1387 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_Weakened
# 1388 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_WEAK
# 1389 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1390 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1391 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerBackFromGuzzlord
# 1392 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1393 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBMiloticFinishesWest
# 1394 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBSnorlaxFinishesNorth
# 1395 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBFieldStarts
# 1396 "data/maps/NewBarkTown/scripts.pory"

# 1397 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterNihilego::
# 1398 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_Weakened
# 1399 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_WEAK
# 1400 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1401 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1402 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerBackFromNihilego
# 1403 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1404 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBMiloticFinishesSouth
# 1405 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBSnorlaxFinishesNorth
# 1406 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBFieldStarts
# 1407 "data/maps/NewBarkTown/scripts.pory"

# 1408 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMiloticFinishesWest::
# 1409 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_AttackLeft
# 1410 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_MILOTIC, CRY_MODE_ENCOUNTER
# 1411 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1412 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_Weakened
# 1413 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1414 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1415 "data/maps/NewBarkTown/scripts.pory"
	return
# 1416 "data/maps/NewBarkTown/scripts.pory"

# 1417 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMiloticFinishesSouth::
# 1418 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_AttackDown
# 1419 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_MILOTIC, CRY_MODE_ENCOUNTER
# 1420 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1421 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_Weakened
# 1422 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1423 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1424 "data/maps/NewBarkTown/scripts.pory"
	return
# 1425 "data/maps/NewBarkTown/scripts.pory"

# 1426 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSnorlaxFinishesEast::
# 1427 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_AttackRight
# 1428 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
# 1429 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
# 1430 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_Weakened
# 1431 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1432 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1433 "data/maps/NewBarkTown/scripts.pory"
	return
# 1434 "data/maps/NewBarkTown/scripts.pory"

# 1435 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSnorlaxFinishesNorth::
# 1436 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_AttackUp
# 1437 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
# 1438 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
# 1439 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_Weakened
# 1440 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1441 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1442 "data/maps/NewBarkTown/scripts.pory"
	return
# 1443 "data/maps/NewBarkTown/scripts.pory"

# 1444 "data/maps/NewBarkTown/scripts.pory"
@ The field comes up between the emitters and the links from the three beasts
# 1445 "data/maps/NewBarkTown/scripts.pory"
@ to their openings weaken and drop - one sparkle and one reading per beast,
# 1446 "data/maps/NewBarkTown/scripts.pory"
@ BEFORE anyone announces success. The beasts do not vanish or freeze.
# 1447 "data/maps/NewBarkTown/scripts.pory"
@ Elm speaks from his station, in frame at (11,10). Then Anabel readies an
# 1448 "data/maps/NewBarkTown/scripts.pory"
@ ordinary police Ball for the player's beast - not Kurt's Beast Ball, nothing
# 1449 "data/maps/NewBarkTown/scripts.pory"
@ from the player's bag.
# 1450 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFieldStarts::
# 1451 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1452 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterBattleAnabel, MSGBOX_DEFAULT
# 1453 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1454 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1455 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterBattleLusamine, MSGBOX_DEFAULT
# 1456 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1457 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PC_ON
# 1458 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1459 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFieldLine
# 1460 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_REFLECT
# 1461 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 14, 10, 0
# 1462 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1463 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1464 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 21, 14, 0
# 1465 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1466 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1467 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 13, 14, 0
# 1468 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1469 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1470 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1471 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1472 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ELM, Common_Movement_ExclamationMark
# 1473 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ELM
# 1474 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBFieldWorks, MSGBOX_DEFAULT
# 1475 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1476 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAnabelFacesTarget
# 1477 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBCaptureStart, MSGBOX_DEFAULT
# 1478 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1479 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBNecrozma
# 1480 "data/maps/NewBarkTown/scripts.pory"

# 1481 "data/maps/NewBarkTown/scripts.pory"
@ Anabel (18,14) turns to the player's beast: Guzzlord (21,14) is east of
# 1482 "data/maps/NewBarkTown/scripts.pory"
@ her; Kartana (14,10) and Nihilego (13,14) are west.
# 1483 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabelFacesTarget::
# 1484 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAnabelFacesEast
# 1485 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
# 1486 "data/maps/NewBarkTown/scripts.pory"
	return
# 1487 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabelFacesEast::
# 1488 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_EAST
# 1489 "data/maps/NewBarkTown/scripts.pory"
	return
# 1490 "data/maps/NewBarkTown/scripts.pory"

# 1491 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1492 "data/maps/NewBarkTown/scripts.pory"
@ Necrozma forces the containment (V2 section 12).
# 1493 "data/maps/NewBarkTown/scripts.pory"
@ Anabel and Elm catch the known pulse; a distortion opens OUTSIDE the area,
# 1494 "data/maps/NewBarkTown/scripts.pory"
@ in the flower bed (16,9), three tiles from the nearest trainer, and Necrozma
# 1495 "data/maps/NewBarkTown/scripts.pory"
@ comes through it. The field first BLOCKS its filaments (a shock of light
# 1496 "data/maps/NewBarkTown/scripts.pory"
@ at both emitters, and nothing is dragged). Anabel throws. Necrozma raises the
# 1497 "data/maps/NewBarkTown/scripts.pory"
@ pulse while the Ball is in the air, the field's edge fails, Gold/Crystal
# 1498 "data/maps/NewBarkTown/scripts.pory"
@ send Azumarill to cover Lusamine's step back, the restored link throws the
# 1499 "data/maps/NewBarkTown/scripts.pory"
@ Ball back intact, and Lusamine shuts the emitters down.
# 1500 "data/maps/NewBarkTown/scripts.pory"
@ Then the three are pulled: each resists, facing away, while Snorlax and
# 1501 "data/maps/NewBarkTown/scripts.pory"
@ Milotic strike at the filaments, and each turns to light where it stands -
# 1502 "data/maps/NewBarkTown/scripts.pory"
@ nothing solid is crossed in bodily form. Only their three actors go.
# 1503 "data/maps/NewBarkTown/scripts.pory"
@ Azumarill (13,12) -> (14,12), free in every branch once the player is back.
# 1504 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine (13,11) -> (13,12), facing kept.
# 1505 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1506 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNecrozma::
# 1507 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_DETECT
# 1508 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, Common_Movement_ExclamationMark
# 1509 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ELM, Common_Movement_ExclamationMark
# 1510 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 1511 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ELM
# 1512 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1513 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1514 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1515 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WARP_IN
# 1516 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 16, 9, 0
# 1517 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1518 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_5
# 1519 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NECROZMA
# 1520 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1521 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1522 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1523 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1524 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
# 1525 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1526 "data/maps/NewBarkTown/scripts.pory"
	@ First the field holds.
# 1527 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
# 1528 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
# 1529 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_REFLECT
# 1530 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 12, 11, 0
# 1531 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 22, 12, 0
# 1532 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFlash
# 1533 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1534 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1535 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBFieldHolding, MSGBOX_DEFAULT
# 1536 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1537 "data/maps/NewBarkTown/scripts.pory"
	@ The throw, and the pulse rising while the Ball is in the air.
# 1538 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAnabelThrows
# 1539 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
# 1540 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1541 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
# 1542 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 12, 11, 0
# 1543 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 22, 12, 0
# 1544 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRiftPulse
# 1545 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1546 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1547 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBFieldStrain, MSGBOX_DEFAULT
# 1548 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1549 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalRetreat, MSGBOX_DEFAULT
# 1550 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1551 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillCovers
# 1552 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1553 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_BackOffSouth
# 1554 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 1555 "data/maps/NewBarkTown/scripts.pory"
	@ The link comes back and throws the Ball off, intact.
# 1556 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBTargetStartles
# 1557 "data/maps/NewBarkTown/scripts.pory"
	playse SE_M_REFLECT
# 1558 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1559 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_BOUNCE_1
# 1560 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1561 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine shuts the device down before it discharges beside the team.
# 1562 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PC_OFF
# 1563 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 12, 11, 0
# 1564 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 22, 12, 0
# 1565 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1566 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1567 "data/maps/NewBarkTown/scripts.pory"
	@ The pull.
# 1568 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
# 1569 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1570 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
# 1571 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_ResistLeft
# 1572 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_ResistDown
# 1573 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_ResistDown
# 1574 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_AttackUp
# 1575 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_AttackUp
# 1576 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1577 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1578 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1579 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
# 1580 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1581 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1582 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1583 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1584 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_KARTANA
# 1585 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_GUZZLORD
# 1586 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NIHILEGO
# 1587 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1588 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1589 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1590 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAbsorbed, MSGBOX_DEFAULT
# 1591 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1592 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUltra
# 1593 "data/maps/NewBarkTown/scripts.pory"

# 1594 "data/maps/NewBarkTown/scripts.pory"
@ Anabel's throw, toward the player's beast.
# 1595 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabelThrows::
# 1596 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_THROW
# 1597 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAnabelThrowsEast
# 1598 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_AttackLeft
# 1599 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 1600 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1601 "data/maps/NewBarkTown/scripts.pory"
	return
# 1602 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabelThrowsEast::
# 1603 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_AttackRight
# 1604 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 1605 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1606 "data/maps/NewBarkTown/scripts.pory"
	return
# 1607 "data/maps/NewBarkTown/scripts.pory"

# 1608 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBTargetStartles::
# 1609 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBGuzzlordStartles
# 1610 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBNihilegoStartles
# 1611 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
# 1612 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1613 "data/maps/NewBarkTown/scripts.pory"
	return
# 1614 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBGuzzlordStartles::
# 1615 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
# 1616 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1617 "data/maps/NewBarkTown/scripts.pory"
	return
# 1618 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNihilegoStartles::
# 1619 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
# 1620 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1621 "data/maps/NewBarkTown/scripts.pory"
	return
# 1622 "data/maps/NewBarkTown/scripts.pory"

# 1623 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1624 "data/maps/NewBarkTown/scripts.pory"
@ Ultra Necrozma - transformation and instability (V2 section 13).
# 1625 "data/maps/NewBarkTown/scripts.pory"
@ The beasts are already gone. The light grows, a pause, and the actor changes
# 1626 "data/maps/NewBarkTown/scripts.pory"
@ on the SAME tile (16,9) under one flash: normal and Ultra never exist at the
# 1627 "data/maps/NewBarkTown/scripts.pory"
@ same time (FLAG_TEMP_5 / FLAG_TEMP_6, one slot). The new silhouette is on
# 1628 "data/maps/NewBarkTown/scripts.pory"
@ screen before any text. OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA
# 1629 "data/maps/NewBarkTown/scripts.pory"
@ (include/config/overworld.h) compiles its own sprite - no Substitute.
# 1630 "data/maps/NewBarkTown/scripts.pory"
@ The pulse drives the line back: the player (16,12) -> (16,13) and Lusamine
# 1631 "data/maps/NewBarkTown/scripts.pory"
@ (13,12) -> (12,12), both still facing it; Snorlax, Milotic and Azumarill
# 1632 "data/maps/NewBarkTown/scripts.pory"
@ brace. Nobody falls, nobody attacks in sync, and there is no forced-loss
# 1633 "data/maps/NewBarkTown/scripts.pory"
@ battle. Then the clue: the light fails in uneven pulses and the three small
# 1634 "data/maps/NewBarkTown/scripts.pory"
@ openings start to contract - BEFORE and regardless of any partner.
# 1635 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1636 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltra::
# 1637 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
# 1638 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
# 1639 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1640 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1641 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NECROZMA
# 1642 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_6
# 1643 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1644 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1645 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 1646 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
# 1647 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1648 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraRises, MSGBOX_DEFAULT
# 1649 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1650 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraRetreat, MSGBOX_DEFAULT
# 1651 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1652 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFlare
# 1653 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1654 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFlash
# 1655 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 3   @ vertical pan
# 1656 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 2   @ horizontal pan
# 1657 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 24  @ num shakes
# 1658 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 3   @ shake delay
# 1659 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 1660 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1661 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_BackOffSouth
# 1662 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_BackOffWest
# 1663 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_Brace
# 1664 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_Brace
# 1665 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_Brace
# 1666 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1667 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 1668 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
# 1669 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1670 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1671 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 1672 "data/maps/NewBarkTown/scripts.pory"
	@ The clue: uneven light, the openings closing in.
# 1673 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFalters
# 1674 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRiftPulse
# 1675 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 14, 9, 0
# 1676 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 21, 16, 0
# 1677 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 13, 16, 0
# 1678 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1679 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1680 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraUnstable, MSGBOX_DEFAULT
# 1681 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1682 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBPartner
# 1683 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRetreat
# 1684 "data/maps/NewBarkTown/scripts.pory"

# 1685 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1686 "data/maps/NewBarkTown/scripts.pory"
@ The player's partner - every branch (V2 section 14). CheckMysteryEggPokemon
# 1687 "data/maps/NewBarkTown/scripts.pory"
@ is sampled AFTER the battle (the battle can evolve it) and returns the first
# 1688 "data/maps/NewBarkTown/scripts.pory"
@ eligible one in party order, so actor, cry and {STR_VAR_1} agree. It comes
# 1689 "data/maps/NewBarkTown/scripts.pory"
@ out of its Ball at (17,13), east of the player - the sheltered side, out of
# 1690 "data/maps/NewBarkTown/scripts.pory"
@ the line of light - BEFORE anything is said about it, and goes back into it
# 1691 "data/maps/NewBarkTown/scripts.pory"
@ before the retreat is over. The optional reactions condition nothing.
# 1692 "data/maps/NewBarkTown/scripts.pory"
@ In every branch Azumarill takes the last step back, (14,12) -> (14,13): the
# 1693 "data/maps/NewBarkTown/scripts.pory"
@ rival's retreat - covered by Solgaleo/Lunala's light when it is there.
# 1694 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1695 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPartner::
# 1696 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 1697 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_4, VAR_RESULT
# 1698 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, NewBarkTown_EventScript_UBNoPartner
# 1699 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1700 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1701 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 1702 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_C
# 1703 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAddPartner
# 1704 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1705 "data/maps/NewBarkTown/scripts.pory"
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
# 1706 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1707 "data/maps/NewBarkTown/scripts.pory"
	@ It turns toward it for a moment - and its light keeps failing.
# 1708 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_LookAtPartner
# 1709 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1710 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRiftPulse
# 1711 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, NewBarkTown_EventScript_UBPartnerLegend
# 1712 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, NewBarkTown_EventScript_UBPartnerLegend
# 1713 "data/maps/NewBarkTown/scripts.pory"
	@ Cosmog / Cosmoem: kept beside the player; it only floats, so nothing
# 1714 "data/maps/NewBarkTown/scripts.pory"
	@ walks. Not bait, not to blame, not immune.
# 1715 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraSensesCosmog, MSGBOX_DEFAULT
# 1716 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1717 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_Brace
# 1718 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
# 1719 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRecallPartner
# 1720 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAzumarillLastStep
# 1721 "data/maps/NewBarkTown/scripts.pory"

# 1722 "data/maps/NewBarkTown/scripts.pory"
@ Solgaleo / Lunala: a cry and a pulse; a band of light between the rupture
# 1723 "data/maps/NewBarkTown/scripts.pory"
@ and the rear (sparkles on the diagonal back toward the lab) steadies the
# 1724 "data/maps/NewBarkTown/scripts.pory"
@ edge for a moment - long enough for the rival's last step back. The body
# 1725 "data/maps/NewBarkTown/scripts.pory"
@ keeps wavering; it takes no energy from the partner and is not afraid of it.
# 1726 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPartnerLegend::
# 1727 "data/maps/NewBarkTown/scripts.pory"
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
# 1728 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFlash
# 1729 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 16, 11, 0
# 1730 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 15, 12, 0
# 1731 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 14, 13, 0
# 1732 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1733 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1734 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraPartner, MSGBOX_DEFAULT
# 1735 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1736 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAzumarillLastStepCall
# 1737 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalPartnerCover, MSGBOX_DEFAULT
# 1738 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1739 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRecallPartner
# 1740 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRiftPulse
# 1741 "data/maps/NewBarkTown/scripts.pory"
	return
# 1742 "data/maps/NewBarkTown/scripts.pory"

# 1743 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNoPartner::
# 1744 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAzumarillLastStep::
# 1745 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAzumarillLastStepCall
# 1746 "data/maps/NewBarkTown/scripts.pory"
	return
# 1747 "data/maps/NewBarkTown/scripts.pory"

# 1748 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAzumarillLastStepCall::
# 1749 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_BackOffSouth
# 1750 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1751 "data/maps/NewBarkTown/scripts.pory"
	return
# 1752 "data/maps/NewBarkTown/scripts.pory"

# 1753 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAddPartner::
# 1754 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, NewBarkTown_EventScript_UBAddCosmoem
# 1755 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, NewBarkTown_EventScript_UBAddSolgaleo
# 1756 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, NewBarkTown_EventScript_UBAddLunala
# 1757 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_COSMOG
# 1758 "data/maps/NewBarkTown/scripts.pory"
	return
# 1759 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAddCosmoem::
# 1760 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_COSMOEM
# 1761 "data/maps/NewBarkTown/scripts.pory"
	return
# 1762 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAddSolgaleo::
# 1763 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_SOLGALEO
# 1764 "data/maps/NewBarkTown/scripts.pory"
	return
# 1765 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAddLunala::
# 1766 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_LUNALA
# 1767 "data/maps/NewBarkTown/scripts.pory"
	return
# 1768 "data/maps/NewBarkTown/scripts.pory"

# 1769 "data/maps/NewBarkTown/scripts.pory"
@ Back into its Ball, on screen. removeobject on the three that were never
# 1770 "data/maps/NewBarkTown/scripts.pory"
@ added is a no-op.
# 1771 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRecallPartner::
# 1772 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1773 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 1774 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_COSMOG
# 1775 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_COSMOEM
# 1776 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_SOLGALEO
# 1777 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_LUNALA
# 1778 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1779 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1780 "data/maps/NewBarkTown/scripts.pory"
	return
# 1781 "data/maps/NewBarkTown/scripts.pory"

# 1782 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1783 "data/maps/NewBarkTown/scripts.pory"
@ The retreat and the record of nine (V2 section 15).
# 1784 "data/maps/NewBarkTown/scripts.pory"
@ It tries another pulse and fails. The main opening opens beside it (17,9) -
# 1785 "data/maps/NewBarkTown/scripts.pory"
@ the one object that exists only now, when the beasts are gone and the
# 1786 "data/maps/NewBarkTown/scripts.pory"
@ budget allows it - and Ultra Necrozma backs into it, still facing the
# 1787 "data/maps/NewBarkTown/scripts.pory"
@ street; it goes under a flash. The small openings contract the same way
# 1788 "data/maps/NewBarkTown/scripts.pory"
@ and close after it. No actor is teleported.
# 1789 "data/maps/NewBarkTown/scripts.pory"
@ Elm's record: nine patterns in groups - three pairs from the earlier
# 1790 "data/maps/NewBarkTown/scripts.pory"
@ missions, then the three from here - on the instrument the street has
# 1791 "data/maps/NewBarkTown/scripts.pory"
@ already seen, compared and not counted from memory.
# 1792 "data/maps/NewBarkTown/scripts.pory"
@ Only after the openings are confirmed closed does the threat theme end.
# 1793 "data/maps/NewBarkTown/scripts.pory"
@ Then the partners are recalled on screen once they are no longer needed,
# 1794 "data/maps/NewBarkTown/scripts.pory"
@ and Looker checks the broken barricade.
# 1795 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1796 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRetreat::
# 1797 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_PulseDown
# 1798 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1799 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRiftPulse
# 1800 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_B
# 1801 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WARP_IN
# 1802 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_RIFT
# 1803 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1804 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_BacksIntoRift
# 1805 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1806 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1807 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1808 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1809 "data/maps/NewBarkTown/scripts.pory"
	delay 20
# 1810 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 14, 9, 0
# 1811 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 21, 16, 0
# 1812 "data/maps/NewBarkTown/scripts.pory"
	dofieldeffectsparkle 13, 16, 0
# 1813 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WARP_OUT
# 1814 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBRiftPulse
# 1815 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_RIFT
# 1816 "data/maps/NewBarkTown/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1817 "data/maps/NewBarkTown/scripts.pory"
	delay 20
# 1818 "data/maps/NewBarkTown/scripts.pory"
	@ Nine patterns, in groups: 2, 2, 2 - and 3.
# 1819 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1820 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 1821 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ELM, Common_Movement_ExclamationMark
# 1822 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ELM
# 1823 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1824 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1825 "data/maps/NewBarkTown/scripts.pory"
	delay 12
# 1826 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1827 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1828 "data/maps/NewBarkTown/scripts.pory"
	delay 12
# 1829 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1830 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1831 "data/maps/NewBarkTown/scripts.pory"
	delay 24
# 1832 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1833 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1834 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBBeep
# 1835 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmNine, MSGBOX_DEFAULT
# 1836 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelNine, MSGBOX_DEFAULT
# 1837 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmConfirms, MSGBOX_DEFAULT
# 1838 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1839 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1840 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBStreetClear, MSGBOX_DEFAULT
# 1841 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1842 "data/maps/NewBarkTown/scripts.pory"
	delay 40
# 1843 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 1844 "data/maps/NewBarkTown/scripts.pory"
	@ Milotic and Snorlax go back into their Balls.
# 1845 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 1846 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_MILOTIC
# 1847 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1848 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 1849 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_SNORLAX
# 1850 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 1851 "data/maps/NewBarkTown/scripts.pory"
	@ Looker (21,12) -> (21,13), looks at the broken barricade, and back.
# 1852 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerChecksSouth
# 1853 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1854 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAftermath
# 1855 "data/maps/NewBarkTown/scripts.pory"

# 1856 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1857 "data/maps/NewBarkTown/scripts.pory"
@ Aftermath - people and outcome (V2 sections 16 and 17).
# 1858 "data/maps/NewBarkTown/scripts.pory"
@ The player steps back up to (16,12). Looker comes to (17,12), east of the
# 1859 "data/maps/NewBarkTown/scripts.pory"
@ player. The shelter door opens only after the check, and Mom appears in it,
# 1860 "data/maps/NewBarkTown/scripts.pory"
@ stepping down to (10,10). Gold/Crystal walk (11,12) -> (11,13) -> (13,13) to
# 1861 "data/maps/NewBarkTown/scripts.pory"
@ look at Azumarill (14,13) east of them; the player's answer is a gesture.
# 1862 "data/maps/NewBarkTown/scripts.pory"
@ Then they go to check the cut fence: (13,13) -> (13,12) -> (13,11) ->
# 1863 "data/maps/NewBarkTown/scripts.pory"
@ (14,11), facing it, with Azumarill (14,13) -> (14,12) behind them.
# 1864 "data/maps/NewBarkTown/scripts.pory"
@ Everyone who speaks is on y <= 14, above the text box. The player turns to
# 1865 "data/maps/NewBarkTown/scripts.pory"
@ each speaker: Looker/Anabel east, Mom/Elm/Lusamine/rival west.
# 1866 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1867 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermath::
# 1868 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_StepUp
# 1869 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1870 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerToGroup
# 1871 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 1872 "data/maps/NewBarkTown/scripts.pory"
	opendoor 10, 9
# 1873 "data/maps/NewBarkTown/scripts.pory"
	waitdooranim
# 1874 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_MOM, 10, 9
# 1875 "data/maps/NewBarkTown/scripts.pory"
	setobjectmovementtype LOCALID_NEWBARK_UB_MOM, MOVEMENT_TYPE_FACE_DOWN
# 1876 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 1877 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_MOM
# 1878 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_StepDown
# 1879 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_MOM
# 1880 "data/maps/NewBarkTown/scripts.pory"
	closedoor 10, 9
# 1881 "data/maps/NewBarkTown/scripts.pory"
	waitdooranim
# 1882 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST
# 1883 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1884 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathLooker, MSGBOX_DEFAULT
# 1885 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1886 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, NewBarkTown_Movement_RivalToAzumarill
# 1887 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 1888 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_AZUMARILL, DIR_WEST
# 1889 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1890 "data/maps/NewBarkTown/scripts.pory"
	delay 16
# 1891 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_Nod
# 1892 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1893 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathRival, MSGBOX_DEFAULT
# 1894 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1895 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1896 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLookerRivalThanks, MSGBOX_DEFAULT
# 1897 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1898 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, NewBarkTown_Movement_RivalChecksFence
# 1899 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 1900 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillFollows
# 1901 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1902 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1903 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomAftermath, MSGBOX_DEFAULT
# 1904 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1905 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathLusamine, MSGBOX_DEFAULT
# 1906 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1907 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
# 1908 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1909 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathAnabel, MSGBOX_DEFAULT
# 1910 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1911 "data/maps/NewBarkTown/scripts.pory"
	@ The way to Olivine and the Altar (section 17).
# 1912 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_EAST
# 1913 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1914 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmDirection, MSGBOX_DEFAULT
# 1915 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1916 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1917 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelCompare, MSGBOX_DEFAULT
# 1918 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1919 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1920 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineRecords, MSGBOX_DEFAULT
# 1921 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineChildren, MSGBOX_DEFAULT
# 1922 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1923 "data/maps/NewBarkTown/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1924 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLookerReunion, MSGBOX_DEFAULT
# 1925 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBHook, MSGBOX_DEFAULT
# 1926 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1927 "data/maps/NewBarkTown/scripts.pory"
	@ The explicit time transition for the barriers and the equipment.
# 1928 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRepairs, MSGBOX_DEFAULT
# 1929 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1930 "data/maps/NewBarkTown/scripts.pory"

# 1931 "data/maps/NewBarkTown/scripts.pory"
@ Resolution (V2 section 18): state 10, and the event flag cleared WITH it
# 1932 "data/maps/NewBarkTown/scripts.pory"
@ (invariant: FLAG_EVENT_ULTRABEAST_NEWBARK set <=> state 9).
# 1933 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_DAILY_LOOKER_CALL is deliberately NOT set here: if the New Bark call was
# 1934 "data/maps/NewBarkTown/scripts.pory"
@ on an earlier day, the reunion call may ring today once the player is back in
# 1935 "data/maps/NewBarkTown/scripts.pory"
@ free control (data/scripts/rift_missions.inc).
# 1936 "data/maps/NewBarkTown/scripts.pory"
@ Reload in place under the fade: the fence, the logs and the emitters go (the
# 1937 "data/maps/NewBarkTown/scripts.pory"
@ layout has none of them), the seven residents come back by their own flags,
# 1938 "data/maps/NewBarkTown/scripts.pory"
@ Mom is home, Elm is in his lab, the cast is gone, and the follower returns
# 1939 "data/maps/NewBarkTown/scripts.pory"
@ once (FLAG_TEMP_HIDE_FOLLOWER is a temp).
# 1940 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFinish::
# 1941 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1942 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_NEWBARK
# 1943 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_NEWBARK_UB_ENGAGED
# 1944 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 10
# 1945 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 1946 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1947 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1948 "data/maps/NewBarkTown/scripts.pory"
	end
# 1949 "data/maps/NewBarkTown/scripts.pory"

# 1950 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1951 "data/maps/NewBarkTown/scripts.pory"
@ Movements. Every tile was checked with dump_mapa.py.
# 1952 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 1953 "data/maps/NewBarkTown/scripts.pory"

# 1954 "data/maps/NewBarkTown/scripts.pory"
@ (20,12) -> (16,12).
# 1955 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerToCommand:
# 1956 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1957 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1958 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1959 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1960 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1961 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1962 "data/maps/NewBarkTown/scripts.pory"

# 1963 "data/maps/NewBarkTown/scripts.pory"
@ Retry from (21,13): (20,13) .. (16,13), then (16,12).
# 1964 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerRetryFromSouth:
# 1965 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1966 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1967 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1968 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1969 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1970 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 1971 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1972 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1973 "data/maps/NewBarkTown/scripts.pory"

# 1974 "data/maps/NewBarkTown/scripts.pory"
@ Anabel (22,12) -> (22,13), turns back to the tile she left.
# 1975 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepDownFaceUp:
# 1976 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 1977 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1978 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1979 "data/maps/NewBarkTown/scripts.pory"

# 1980 "data/maps/NewBarkTown/scripts.pory"
@ Anabel (22,13) -> (22,14) -> (21,14) -> (20,14) -> (19,14) -> (18,14).
# 1981 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AnabelToPost:
# 1982 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 1983 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1984 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1985 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1986 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1987 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 1988 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1989 "data/maps/NewBarkTown/scripts.pory"

# 1990 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_NodLeft:
# 1991 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_left
# 1992 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1993 "data/maps/NewBarkTown/scripts.pory"

# 1994 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_Nod:
# 1995 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_left
# 1996 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1997 "data/maps/NewBarkTown/scripts.pory"

# 1998 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepDown:
# 1999 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2000 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2001 "data/maps/NewBarkTown/scripts.pory"

# 2002 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepUp:
# 2003 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2004 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2005 "data/maps/NewBarkTown/scripts.pory"

# 2006 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepUpTwice:
# 2007 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2008 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2009 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2010 "data/maps/NewBarkTown/scripts.pory"

# 2011 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AttackDown:
# 2012 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2013 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2014 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2015 "data/maps/NewBarkTown/scripts.pory"

# 2016 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AttackUp:
# 2017 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_up
# 2018 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_up
# 2019 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2020 "data/maps/NewBarkTown/scripts.pory"

# 2021 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AttackLeft:
# 2022 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 2023 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 2024 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2025 "data/maps/NewBarkTown/scripts.pory"

# 2026 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AttackRight:
# 2027 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 2028 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 2029 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2030 "data/maps/NewBarkTown/scripts.pory"

# 2031 "data/maps/NewBarkTown/scripts.pory"
@ (21,16) -> (21,15) -> (21,14), over the logs it just broke.
# 2032 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_GuzzlordAdvances:
# 2033 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_up
# 2034 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_up
# 2035 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2036 "data/maps/NewBarkTown/scripts.pory"

# 2037 "data/maps/NewBarkTown/scripts.pory"
@ (21,13) -> (16,13). Five steps at normal speed: she is there before
# 2038 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego's three slow ones end.
# 2039 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_MomCrosses:
# 2040 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2041 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2042 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2043 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2044 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2045 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2046 "data/maps/NewBarkTown/scripts.pory"

# 2047 "data/maps/NewBarkTown/scripts.pory"
@ (13,16) -> (13,13), slow.
# 2048 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_NihilegoDrifts:
# 2049 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_up
# 2050 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_up
# 2051 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_up
# 2052 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2053 "data/maps/NewBarkTown/scripts.pory"

# 2054 "data/maps/NewBarkTown/scripts.pory"
@ (12,12) -> (13,12), facing the beast below.
# 2055 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillIntercepts:
# 2056 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2057 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 2058 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2059 "data/maps/NewBarkTown/scripts.pory"

# 2060 "data/maps/NewBarkTown/scripts.pory"
@ Pushed one tile, still facing the one that pushed it.
# 2061 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_KnockedBackDown:
# 2062 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 2063 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2064 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 2065 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2066 "data/maps/NewBarkTown/scripts.pory"

# 2067 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine (13,11) -> (14,11) -> (14,12) -> (14,13) -> (15,13), faces east.
# 2068 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LusamineToMom:
# 2069 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2070 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2071 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2072 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2073 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 2074 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2075 "data/maps/NewBarkTown/scripts.pory"

# 2076 "data/maps/NewBarkTown/scripts.pory"
@ And back: (15,13) -> (14,13) -> (14,12) -> (14,11) -> (13,11), faces east.
# 2077 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LusamineBackToControl:
# 2078 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2079 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2080 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2081 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2082 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 2083 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2084 "data/maps/NewBarkTown/scripts.pory"

# 2085 "data/maps/NewBarkTown/scripts.pory"
@ Looker (21,12) -> (21,13) -> (17,13), behind Mom.
# 2086 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LookerToMom:
# 2087 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2088 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2089 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2090 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2091 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2092 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 2093 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2094 "data/maps/NewBarkTown/scripts.pory"

# 2095 "data/maps/NewBarkTown/scripts.pory"
@ Mom (16,13) -> (10,13) -> (10,10).
# 2096 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_MomToLab:
# 2097 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2098 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2099 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2100 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2101 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2102 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2103 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2104 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2105 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2106 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2107 "data/maps/NewBarkTown/scripts.pory"

# 2108 "data/maps/NewBarkTown/scripts.pory"
@ Looker (17,13) -> (10,13) -> (10,11): the same path, one step behind.
# 2109 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LookerToLab:
# 2110 "data/maps/NewBarkTown/scripts.pory"
	delay_16
# 2111 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2112 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2113 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2114 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2115 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2116 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2117 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2118 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2119 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2120 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2121 "data/maps/NewBarkTown/scripts.pory"

# 2122 "data/maps/NewBarkTown/scripts.pory"
@ Looker (10,10) -> (10,13) -> (21,13) -> (21,12), faces west.
# 2123 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LookerBackToPost:
# 2124 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2125 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2126 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2127 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2128 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2129 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2130 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2131 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2132 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2133 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2134 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2135 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2136 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2137 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2138 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 2139 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 2140 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2141 "data/maps/NewBarkTown/scripts.pory"

# 2142 "data/maps/NewBarkTown/scripts.pory"
@ Milotic (15,11) -> (15,14) -> (14,14), faces west (Nihilego at (13,14)).
# 2143 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_MiloticToNihilego:
# 2144 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2145 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2146 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2147 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2148 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 2149 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2150 "data/maps/NewBarkTown/scripts.pory"

# 2151 "data/maps/NewBarkTown/scripts.pory"
@ Milotic (15,11) -> (15,13) -> (21,13), faces south (Guzzlord at (21,14)).
# 2152 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_MiloticToGuzzlord:
# 2153 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2154 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 2155 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2156 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2157 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2158 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2159 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2160 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2161 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 2162 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2163 "data/maps/NewBarkTown/scripts.pory"

# 2164 "data/maps/NewBarkTown/scripts.pory"
@ Snorlax (20,14) -> (20,13) -> (15,13) -> (15,11) -> (14,11), faces north
# 2165 "data/maps/NewBarkTown/scripts.pory"
@ (Kartana at (14,10)).
# 2166 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_SnorlaxToKartana:
# 2167 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 2168 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2169 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2170 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2171 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2172 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2173 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 2174 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 2175 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 2176 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2177 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2178 "data/maps/NewBarkTown/scripts.pory"

# 2179 "data/maps/NewBarkTown/scripts.pory"
@ Player (16,12) -> (15,12) -> (14,12) -> (14,11), faces Kartana.
# 2180 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerToKartana:
# 2181 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2182 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2183 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2184 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2185 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2186 "data/maps/NewBarkTown/scripts.pory"

# 2187 "data/maps/NewBarkTown/scripts.pory"
@ Player (16,12) -> (16,13) -> (20,13) -> (20,14), faces Guzzlord.
# 2188 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerToGuzzlord:
# 2189 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2190 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2191 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2192 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2193 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2194 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2195 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 2196 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2197 "data/maps/NewBarkTown/scripts.pory"

# 2198 "data/maps/NewBarkTown/scripts.pory"
@ Player (16,12) -> (16,14) -> (14,14), faces Nihilego.
# 2199 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerToNihilego:
# 2200 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2201 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2202 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2203 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2204 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 2205 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2206 "data/maps/NewBarkTown/scripts.pory"

# 2207 "data/maps/NewBarkTown/scripts.pory"
@ (14,11) -> (14,12) -> (16,12).
# 2208 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerBackFromKartana:
# 2209 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2210 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2211 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2212 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2213 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2214 "data/maps/NewBarkTown/scripts.pory"

# 2215 "data/maps/NewBarkTown/scripts.pory"
@ (20,14) -> (20,13) -> (16,13) -> (16,12).
# 2216 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerBackFromGuzzlord:
# 2217 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2218 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2219 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2220 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2221 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2222 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2223 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2224 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2225 "data/maps/NewBarkTown/scripts.pory"

# 2226 "data/maps/NewBarkTown/scripts.pory"
@ (14,14) -> (16,14) -> (16,12).
# 2227 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerBackFromNihilego:
# 2228 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2229 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2230 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2231 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2232 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2233 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2234 "data/maps/NewBarkTown/scripts.pory"

# 2235 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_Weakened:
# 2236 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_down
# 2237 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_down
# 2238 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2239 "data/maps/NewBarkTown/scripts.pory"

# 2240 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PulseDown:
# 2241 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2242 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2243 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2244 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2245 "data/maps/NewBarkTown/scripts.pory"

# 2246 "data/maps/NewBarkTown/scripts.pory"
@ Struggling against the pull, facing kept.
# 2247 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_ResistLeft:
# 2248 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 2249 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 2250 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_left
# 2251 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2252 "data/maps/NewBarkTown/scripts.pory"

# 2253 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_ResistDown:
# 2254 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2255 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2256 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_down
# 2257 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2258 "data/maps/NewBarkTown/scripts.pory"

# 2259 "data/maps/NewBarkTown/scripts.pory"
@ Azumarill (13,12) -> (14,12), facing the north front.
# 2260 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillCovers:
# 2261 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 2262 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2263 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2264 "data/maps/NewBarkTown/scripts.pory"

# 2265 "data/maps/NewBarkTown/scripts.pory"
@ One tile back, still facing the threat.
# 2266 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_BackOffSouth:
# 2267 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 2268 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2269 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 2270 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2271 "data/maps/NewBarkTown/scripts.pory"

# 2272 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_BackOffWest:
# 2273 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 2274 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2275 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 2276 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2277 "data/maps/NewBarkTown/scripts.pory"

# 2278 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_Brace:
# 2279 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_up
# 2280 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2281 "data/maps/NewBarkTown/scripts.pory"

# 2282 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UltraFlare:
# 2283 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2284 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2285 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2286 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2287 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2288 "data/maps/NewBarkTown/scripts.pory"

# 2289 "data/maps/NewBarkTown/scripts.pory"
@ Uneven pulses: slow, a gap, fast, a longer gap, slow.
# 2290 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UltraFalters:
# 2291 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_down
# 2292 "data/maps/NewBarkTown/scripts.pory"
	delay_8
# 2293 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_down
# 2294 "data/maps/NewBarkTown/scripts.pory"
	delay_16
# 2295 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_slow_down
# 2296 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2297 "data/maps/NewBarkTown/scripts.pory"

# 2298 "data/maps/NewBarkTown/scripts.pory"
@ A look toward the partner on the south-east, and back.
# 2299 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LookAtPartner:
# 2300 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 2301 "data/maps/NewBarkTown/scripts.pory"
	delay_16
# 2302 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 2303 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2304 "data/maps/NewBarkTown/scripts.pory"

# 2305 "data/maps/NewBarkTown/scripts.pory"
@ (16,9) -> (17,9), into the opening, facing kept.
# 2306 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_BacksIntoRift:
# 2307 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 2308 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_right
# 2309 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 2310 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2311 "data/maps/NewBarkTown/scripts.pory"

# 2312 "data/maps/NewBarkTown/scripts.pory"
@ Looker (21,12) -> (21,13), looks south at the barricade, and back.
# 2313 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LookerChecksSouth:
# 2314 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2315 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 2316 "data/maps/NewBarkTown/scripts.pory"
	delay_16
# 2317 "data/maps/NewBarkTown/scripts.pory"
	delay_16
# 2318 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2319 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 2320 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2321 "data/maps/NewBarkTown/scripts.pory"

# 2322 "data/maps/NewBarkTown/scripts.pory"
@ Looker (21,12) -> (17,12), east of the player.
# 2323 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_LookerToGroup:
# 2324 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2325 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2326 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2327 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 2328 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 2329 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2330 "data/maps/NewBarkTown/scripts.pory"

# 2331 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal (11,12) -> (11,13) -> (13,13), facing Azumarill at (14,13).
# 2332 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_RivalToAzumarill:
# 2333 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 2334 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2335 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2336 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 2337 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2338 "data/maps/NewBarkTown/scripts.pory"

# 2339 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal (13,13) -> (13,11) -> (14,11), facing the cut fence.
# 2340 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_RivalChecksFence:
# 2341 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2342 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2343 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 2344 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2345 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 2346 "data/maps/NewBarkTown/scripts.pory"

# 2347 "data/maps/NewBarkTown/scripts.pory"
@ Azumarill (14,13) -> (14,12), behind them.
# 2348 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillFollows:
# 2349 "data/maps/NewBarkTown/scripts.pory"
	walk_up
# 2350 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 2351 "data/maps/NewBarkTown/scripts.pory"
	step_end

# 2354 "data/maps/NewBarkTown/scripts.pory"

# 2355 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 2356 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 dialogue - final lines of NEWBARK_ULTRABEAST_SCRIPT_V2.md.
# 2357 "data/maps/NewBarkTown/scripts.pory"
@ One speaker per message, the plaque opening every one of them. Gold/Crystal
# 2358 "data/maps/NewBarkTown/scripts.pory"
@ wear NAME_NEIGHBOR, which shows "Gold" or "Crystal" by the rule the game
# 2359 "data/maps/NewBarkTown/scripts.pory"
@ already uses (ExpandPlaceholder_Neighbor, src/string_util.c) - never Silver,
# 2360 "data/maps/NewBarkTown/scripts.pory"
@ never NONE. The door note and the narration have NO plaque (author's
# 2361 "data/maps/NewBarkTown/scripts.pory"
@ default): a message without {SPEAKER} gets none and inherits none.
# 2362 "data/maps/NewBarkTown/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 2363 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 2364 "data/maps/NewBarkTown/scripts.pory"

# 2365 "data/maps/NewBarkTown/scripts.pory"
@ --- Preparation (section 6) -------------------------------------------------
# 2366 "data/maps/NewBarkTown/scripts.pory"

# 2367 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineIdle:
# 2368 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER}. I'm Lusamine.\n"
# 2369 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel sent me the recordings.\p"
# 2370 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll handle the containment\n"
# 2371 "data/maps/NewBarkTown/scripts.pory"
	.string "field. Keep this approach clear\l"
# 2372 "data/maps/NewBarkTown/scripts.pory"
	.string "for the equipment.$"
# 2373 "data/maps/NewBarkTown/scripts.pory"

# 2374 "data/maps/NewBarkTown/scripts.pory"
@ Retry only: the field is prepared, not active - it needs weakened targets.
# 2375 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineRetry:
# 2376 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The field is ready.\n"
# 2377 "data/maps/NewBarkTown/scripts.pory"
	.string "It only works once they're\l"
# 2378 "data/maps/NewBarkTown/scripts.pory"
	.string "weakened.$"
# 2379 "data/maps/NewBarkTown/scripts.pory"

# 2380 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmIdle:
# 2381 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Kukui asked for the old\n"
# 2382 "data/maps/NewBarkTown/scripts.pory"
	.string "readings. I almost sent only\l"
# 2383 "data/maps/NewBarkTown/scripts.pory"
	.string "the recent ones.\p"
# 2384 "data/maps/NewBarkTown/scripts.pory"
	.string "The earlier pulses helped us\n"
# 2385 "data/maps/NewBarkTown/scripts.pory"
	.string "find where to place the\l"
# 2386 "data/maps/NewBarkTown/scripts.pory"
	.string "sensors.$"
# 2387 "data/maps/NewBarkTown/scripts.pory"

# 2388 "data/maps/NewBarkTown/scripts.pory"
@ YES/NO: "rested" YES leaves it; NO is the heal.
# 2389 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomIdle:
# 2390 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}There you are.\n"
# 2391 "data/maps/NewBarkTown/scripts.pory"
	.string "We're nearly ready at the lab.\p"
# 2392 "data/maps/NewBarkTown/scripts.pory"
	.string "Have you and your Pokémon\n"
# 2393 "data/maps/NewBarkTown/scripts.pory"
	.string "rested?$"
# 2394 "data/maps/NewBarkTown/scripts.pory"

# 2395 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomHeal:
# 2396 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Let your Pokémon rest a\n"
# 2397 "data/maps/NewBarkTown/scripts.pory"
	.string "moment. I'll take care of them.$"
# 2398 "data/maps/NewBarkTown/scripts.pory"

# 2399 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIdle:
# 2400 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}I've checked the houses.\n"
# 2401 "data/maps/NewBarkTown/scripts.pory"
	.string "Azumarill and I will keep the\l"
# 2402 "data/maps/NewBarkTown/scripts.pory"
	.string "path open.\p"
# 2403 "data/maps/NewBarkTown/scripts.pory"
	.string "You handle whatever comes\n"
# 2404 "data/maps/NewBarkTown/scripts.pory"
	.string "through.$"
# 2405 "data/maps/NewBarkTown/scripts.pory"

# 2406 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelIdle:
# 2407 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Elm's sensors are in place.\n"
# 2408 "data/maps/NewBarkTown/scripts.pory"
	.string "We'll be able to compare all\l"
# 2409 "data/maps/NewBarkTown/scripts.pory"
	.string "three openings.\p"
# 2410 "data/maps/NewBarkTown/scripts.pory"
	.string "Speak with Looker when you're\n"
# 2411 "data/maps/NewBarkTown/scripts.pory"
	.string "ready.$"
# 2412 "data/maps/NewBarkTown/scripts.pory"

# 2413 "data/maps/NewBarkTown/scripts.pory"
@ A note on the locked doors: no plaque.
# 2414 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBDoorNote:
# 2415 "data/maps/NewBarkTown/scripts.pory"
	.string "Shelter is available at\n"
# 2416 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor Elm's lab.\p"
# 2417 "data/maps/NewBarkTown/scripts.pory"
	.string "Please keep the main road\n"
# 2418 "data/maps/NewBarkTown/scripts.pory"
	.string "clear.$"
# 2419 "data/maps/NewBarkTown/scripts.pory"

# 2420 "data/maps/NewBarkTown/scripts.pory"
@ --- Readiness and Aether's equipment (section 7) ----------------------------
# 2421 "data/maps/NewBarkTown/scripts.pory"

# 2422 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLookerGreet:
# 2423 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The residents are almost\n"
# 2424 "data/maps/NewBarkTown/scripts.pory"
	.string "inside. We have a clear route\l"
# 2425 "data/maps/NewBarkTown/scripts.pory"
	.string "back to the lab.$"
# 2426 "data/maps/NewBarkTown/scripts.pory"

# 2427 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBReady:
# 2428 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Are you and your Pokémon\n"
# 2429 "data/maps/NewBarkTown/scripts.pory"
	.string "ready?$"
# 2430 "data/maps/NewBarkTown/scripts.pory"

# 2431 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNotReady:
# 2432 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Take care of your team\n"
# 2433 "data/maps/NewBarkTown/scripts.pory"
	.string "first. We'll finish the\l"
# 2434 "data/maps/NewBarkTown/scripts.pory"
	.string "preparations.$"
# 2435 "data/maps/NewBarkTown/scripts.pory"

# 2436 "data/maps/NewBarkTown/scripts.pory"
@ The equipment, by the author's rule: a portable Aether prototype that cuts
# 2437 "data/maps/NewBarkTown/scripts.pory"
@ existing filaments inside a small area for a limited time, with continuous
# 2438 "data/maps/NewBarkTown/scripts.pory"
@ operation. It opens and closes nothing, holds nobody and replaces no Ball.
# 2439 "data/maps/NewBarkTown/scripts.pory"
@ It is NOT the passage stabilizer of the meeting.
# 2440 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBFieldExplanation:
# 2441 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Once they're weakened, keep\n"
# 2442 "data/maps/NewBarkTown/scripts.pory"
	.string "them between these markers.\p"
# 2443 "data/maps/NewBarkTown/scripts.pory"
	.string "The field should interrupt the\n"
# 2444 "data/maps/NewBarkTown/scripts.pory"
	.string "link. It won't stop them\l"
# 2445 "data/maps/NewBarkTown/scripts.pory"
	.string "walking out.$"
# 2446 "data/maps/NewBarkTown/scripts.pory"

# 2447 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBFieldPositions:
# 2448 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Then we keep the Pokémon\n"
# 2449 "data/maps/NewBarkTown/scripts.pory"
	.string "inside it.\p"
# 2450 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker, watch the route to the\n"
# 2451 "data/maps/NewBarkTown/scripts.pory"
	.string "lab.$"
# 2452 "data/maps/NewBarkTown/scripts.pory"

# 2453 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmPositions:
# 2454 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}I'll record the links from\n"
# 2455 "data/maps/NewBarkTown/scripts.pory"
	.string "the lab. Keep the markers where\l"
# 2456 "data/maps/NewBarkTown/scripts.pory"
	.string "they are.$"
# 2457 "data/maps/NewBarkTown/scripts.pory"

# 2458 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelPartner:
# 2459 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Snorlax, hold this side.\n"
# 2460 "data/maps/NewBarkTown/scripts.pory"
	.string "Leave the middle clear.$"
# 2461 "data/maps/NewBarkTown/scripts.pory"

# 2462 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusaminePartner:
# 2463 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Milotic, with me.$"
# 2464 "data/maps/NewBarkTown/scripts.pory"

# 2465 "data/maps/NewBarkTown/scripts.pory"
@ --- Three openings (section 8) ----------------------------------------------
# 2466 "data/maps/NewBarkTown/scripts.pory"

# 2467 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelOpening:
# 2468 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They're opening.\n"
# 2469 "data/maps/NewBarkTown/scripts.pory"
	.string "Clear the road!$"
# 2470 "data/maps/NewBarkTown/scripts.pory"

# 2471 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAppear:
# 2472 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Kartana. Guzzlord. Nihilego.\n"
# 2473 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep the path to the lab clear.$"
# 2474 "data/maps/NewBarkTown/scripts.pory"

# 2475 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBKartanaBreaks:
# 2476 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}Kartana's opened the side\n"
# 2477 "data/maps/NewBarkTown/scripts.pory"
	.string "path!$"
# 2478 "data/maps/NewBarkTown/scripts.pory"

# 2479 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBGuzzlordBreaks:
# 2480 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The south barrier's gone.\n"
# 2481 "data/maps/NewBarkTown/scripts.pory"
	.string "Stay on this side!$"
# 2482 "data/maps/NewBarkTown/scripts.pory"

# 2483 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIntercept:
# 2484 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}Azumarill, push it back!\n"
# 2485 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep that path clear!$"
# 2486 "data/maps/NewBarkTown/scripts.pory"

# 2487 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelCorridor:
# 2488 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Good. Hold that gap.\n"
# 2489 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker, get the last residents\l"
# 2490 "data/maps/NewBarkTown/scripts.pory"
	.string "inside.$"
# 2491 "data/maps/NewBarkTown/scripts.pory"

# 2492 "data/maps/NewBarkTown/scripts.pory"
@ --- Mom and Lusamine (section 9) --------------------------------------------
# 2493 "data/maps/NewBarkTown/scripts.pory"

# 2494 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineControl:
# 2495 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Take your child inside.\n"
# 2496 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll handle the front.$"
# 2497 "data/maps/NewBarkTown/scripts.pory"

# 2498 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomTrust:
# 2499 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}{PLAYER} knows what they're\n"
# 2500 "data/maps/NewBarkTown/scripts.pory"
	.string "doing. Let them help you.\p"
# 2501 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll get everyone inside.\n"
# 2502 "data/maps/NewBarkTown/scripts.pory"
	.string "You won't have to watch this\l"
# 2503 "data/maps/NewBarkTown/scripts.pory"
	.string "door too.$"
# 2504 "data/maps/NewBarkTown/scripts.pory"

# 2505 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineAccepts:
# 2506 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Very well.\n"
# 2507 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel, which front do you\l"
# 2508 "data/maps/NewBarkTown/scripts.pory"
	.string "need me on?$"
# 2509 "data/maps/NewBarkTown/scripts.pory"

# 2510 "data/maps/NewBarkTown/scripts.pory"
@ --- The choice (section 10) -------------------------------------------------
# 2511 "data/maps/NewBarkTown/scripts.pory"

# 2512 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBChoosePrompt:
# 2513 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Choose your target,\n"
# 2514 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}. We'll keep the other\l"
# 2515 "data/maps/NewBarkTown/scripts.pory"
	.string "two off you.$"
# 2516 "data/maps/NewBarkTown/scripts.pory"

# 2517 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceKartana:
# 2518 "data/maps/NewBarkTown/scripts.pory"
	.string "Kartana$"
# 2519 "data/maps/NewBarkTown/scripts.pory"

# 2520 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceGuzzlord:
# 2521 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord$"
# 2522 "data/maps/NewBarkTown/scripts.pory"

# 2523 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceNihilego:
# 2524 "data/maps/NewBarkTown/scripts.pory"
	.string "Nihilego$"
# 2525 "data/maps/NewBarkTown/scripts.pory"

# 2526 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedKartanaLusamine:
# 2527 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I'll keep Nihilego away from\n"
# 2528 "data/maps/NewBarkTown/scripts.pory"
	.string "the houses. Milotic, this way.$"
# 2529 "data/maps/NewBarkTown/scripts.pory"

# 2530 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedKartanaAnabel:
# 2531 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Snorlax and I have Guzzlord.\n"
# 2532 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep Kartana inside the\l"
# 2533 "data/maps/NewBarkTown/scripts.pory"
	.string "markers.$"
# 2534 "data/maps/NewBarkTown/scripts.pory"

# 2535 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedGuzzlordAnabel:
# 2536 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'll block Kartana's path.\n"
# 2537 "data/maps/NewBarkTown/scripts.pory"
	.string "Draw Guzzlord toward the\l"
# 2538 "data/maps/NewBarkTown/scripts.pory"
	.string "cleared ground.$"
# 2539 "data/maps/NewBarkTown/scripts.pory"

# 2540 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedGuzzlordLusamine:
# 2541 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Milotic, keep Nihilego here.$"
# 2542 "data/maps/NewBarkTown/scripts.pory"

# 2543 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedNihilegoLusamine:
# 2544 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Then I'll take Guzzlord.\n"
# 2545 "data/maps/NewBarkTown/scripts.pory"
	.string "Milotic, stay with me.$"
# 2546 "data/maps/NewBarkTown/scripts.pory"

# 2547 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedNihilegoAnabel:
# 2548 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'll hold Kartana.\n"
# 2549 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep Nihilego away from the\l"
# 2550 "data/maps/NewBarkTown/scripts.pory"
	.string "entrance.$"
# 2551 "data/maps/NewBarkTown/scripts.pory"

# 2552 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalCover:
# 2553 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}I've got the way back.\n"
# 2554 "data/maps/NewBarkTown/scripts.pory"
	.string "Go ahead, {PLAYER}.$"
# 2555 "data/maps/NewBarkTown/scripts.pory"

# 2556 "data/maps/NewBarkTown/scripts.pory"
@ --- The defence works (section 11) ------------------------------------------
# 2557 "data/maps/NewBarkTown/scripts.pory"

# 2558 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterBattleAnabel:
# 2559 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Our side is holding.\n"
# 2560 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep them inside the markers.$"
# 2561 "data/maps/NewBarkTown/scripts.pory"

# 2562 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterBattleLusamine:
# 2563 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Milotic, hold there.\n"
# 2564 "data/maps/NewBarkTown/scripts.pory"
	.string "I'm starting the field.$"
# 2565 "data/maps/NewBarkTown/scripts.pory"

# 2566 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBFieldWorks:
# 2567 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}The links have dropped.\n"
# 2568 "data/maps/NewBarkTown/scripts.pory"
	.string "All three Pokémon are still\l"
# 2569 "data/maps/NewBarkTown/scripts.pory"
	.string "inside.$"
# 2570 "data/maps/NewBarkTown/scripts.pory"

# 2571 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBCaptureStart:
# 2572 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Keep the field running.\n"
# 2573 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll secure this one first.$"
# 2574 "data/maps/NewBarkTown/scripts.pory"

# 2575 "data/maps/NewBarkTown/scripts.pory"
@ --- Necrozma forces the containment (section 12) ----------------------------
# 2576 "data/maps/NewBarkTown/scripts.pory"

# 2577 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNecrozmaArrives:
# 2578 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Necrozma.\n"
# 2579 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep the field up!$"
# 2580 "data/maps/NewBarkTown/scripts.pory"

# 2581 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBFieldHolding:
# 2582 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}It's holding.\n"
# 2583 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel, now!$"
# 2584 "data/maps/NewBarkTown/scripts.pory"

# 2585 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBFieldStrain:
# 2586 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}The output is climbing!\n"
# 2587 "data/maps/NewBarkTown/scripts.pory"
	.string "The field can't hold that\l"
# 2588 "data/maps/NewBarkTown/scripts.pory"
	.string "level!$"
# 2589 "data/maps/NewBarkTown/scripts.pory"

# 2590 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalRetreat:
# 2591 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}The path's clear!\n"
# 2592 "data/maps/NewBarkTown/scripts.pory"
	.string "Azumarill, cover them!$"
# 2593 "data/maps/NewBarkTown/scripts.pory"

# 2594 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAbsorbed:
# 2595 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Back behind the markers!\n"
# 2596 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep recording, Professor!$"
# 2597 "data/maps/NewBarkTown/scripts.pory"

# 2598 "data/maps/NewBarkTown/scripts.pory"
@ --- Ultra Necrozma (section 13) ---------------------------------------------
# 2599 "data/maps/NewBarkTown/scripts.pory"

# 2600 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraRises:
# 2601 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}The reading's still rising!$"
# 2602 "data/maps/NewBarkTown/scripts.pory"

# 2603 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraRetreat:
# 2604 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Everyone back.\n"
# 2605 "data/maps/NewBarkTown/scripts.pory"
	.string "Stay together!$"
# 2606 "data/maps/NewBarkTown/scripts.pory"

# 2607 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraUnstable:
# 2608 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}It can't hold that light\n"
# 2609 "data/maps/NewBarkTown/scripts.pory"
	.string "steady. Keep your distance.$"
# 2610 "data/maps/NewBarkTown/scripts.pory"

# 2611 "data/maps/NewBarkTown/scripts.pory"
@ --- The partner (section 14) ------------------------------------------------
# 2612 "data/maps/NewBarkTown/scripts.pory"

# 2613 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraSensesCosmog:
# 2614 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Keep {STR_VAR_1} beside you.\n"
# 2615 "data/maps/NewBarkTown/scripts.pory"
	.string "Milotic, cover that side.$"
# 2616 "data/maps/NewBarkTown/scripts.pory"

# 2617 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraPartner:
# 2618 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The edge is steady.\n"
# 2619 "data/maps/NewBarkTown/scripts.pory"
	.string "Move now!$"
# 2620 "data/maps/NewBarkTown/scripts.pory"

# 2621 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalPartnerCover:
# 2622 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}We're clear, {PLAYER}!\n"
# 2623 "data/maps/NewBarkTown/scripts.pory"
	.string "Bring {STR_VAR_1} back with you!$"
# 2624 "data/maps/NewBarkTown/scripts.pory"

# 2625 "data/maps/NewBarkTown/scripts.pory"
@ --- The retreat and the nine (section 15) -----------------------------------
# 2626 "data/maps/NewBarkTown/scripts.pory"

# 2627 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmNine:
# 2628 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Nine patterns.\n"
# 2629 "data/maps/NewBarkTown/scripts.pory"
	.string "Six match the earlier\l"
# 2630 "data/maps/NewBarkTown/scripts.pory"
	.string "recordings.\p"
# 2631 "data/maps/NewBarkTown/scripts.pory"
	.string "The other three are the ones\n"
# 2632 "data/maps/NewBarkTown/scripts.pory"
	.string "from here.$"
# 2633 "data/maps/NewBarkTown/scripts.pory"

# 2634 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelNine:
# 2635 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They stayed distinct after\n"
# 2636 "data/maps/NewBarkTown/scripts.pory"
	.string "the absorption?$"
# 2637 "data/maps/NewBarkTown/scripts.pory"

# 2638 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmConfirms:
# 2639 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Yes. Until the opening\n"
# 2640 "data/maps/NewBarkTown/scripts.pory"
	.string "closed. I've saved the record.$"
# 2641 "data/maps/NewBarkTown/scripts.pory"

# 2642 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBStreetClear:
# 2643 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}All three openings are\n"
# 2644 "data/maps/NewBarkTown/scripts.pory"
	.string "closed.\p"
# 2645 "data/maps/NewBarkTown/scripts.pory"
	.string "Check the street before we\n"
# 2646 "data/maps/NewBarkTown/scripts.pory"
	.string "let anyone out.$"
# 2647 "data/maps/NewBarkTown/scripts.pory"

# 2648 "data/maps/NewBarkTown/scripts.pory"
@ --- Aftermath (section 16) --------------------------------------------------
# 2649 "data/maps/NewBarkTown/scripts.pory"

# 2650 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathLooker:
# 2651 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Everyone in the lab is safe.\n"
# 2652 "data/maps/NewBarkTown/scripts.pory"
	.string "How are your Pokémon?$"
# 2653 "data/maps/NewBarkTown/scripts.pory"

# 2654 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathRival:
# 2655 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NEIGHBOR}Azumarill's ready for a\n"
# 2656 "data/maps/NewBarkTown/scripts.pory"
	.string "rest. I'll check the side path\l"
# 2657 "data/maps/NewBarkTown/scripts.pory"
	.string "first.$"
# 2658 "data/maps/NewBarkTown/scripts.pory"

# 2659 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLookerRivalThanks:
# 2660 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}You kept our way back open.\n"
# 2661 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you.$"
# 2662 "data/maps/NewBarkTown/scripts.pory"

# 2663 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomAftermath:
# 2664 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Come home when you're ready,\n"
# 2665 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}. You and your Pokémon\l"
# 2666 "data/maps/NewBarkTown/scripts.pory"
	.string "can rest there.$"
# 2667 "data/maps/NewBarkTown/scripts.pory"

# 2668 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathLusamine:
# 2669 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The field broke when Necrozma\n"
# 2670 "data/maps/NewBarkTown/scripts.pory"
	.string "increased the flow. The Pokémon\l"
# 2671 "data/maps/NewBarkTown/scripts.pory"
	.string "were contained until then.\p"
# 2672 "data/maps/NewBarkTown/scripts.pory"
	.string "We have to stop the source.$"
# 2673 "data/maps/NewBarkTown/scripts.pory"

# 2674 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathAnabel:
# 2675 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We kept it away from the\n"
# 2676 "data/maps/NewBarkTown/scripts.pory"
	.string "residents. We still need to\l"
# 2677 "data/maps/NewBarkTown/scripts.pory"
	.string "get the Pokémon out.\p"
# 2678 "data/maps/NewBarkTown/scripts.pory"
	.string "Next time, the operation has to\n"
# 2679 "data/maps/NewBarkTown/scripts.pory"
	.string "be around Necrozma itself.$"
# 2680 "data/maps/NewBarkTown/scripts.pory"

# 2681 "data/maps/NewBarkTown/scripts.pory"
@ --- The way to Olivine and the Altar (section 17) ---------------------------
# 2682 "data/maps/NewBarkTown/scripts.pory"

# 2683 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmDirection:
# 2684 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}All three openings closed\n"
# 2685 "data/maps/NewBarkTown/scripts.pory"
	.string "toward this same point.\p"
# 2686 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll send the full record to\n"
# 2687 "data/maps/NewBarkTown/scripts.pory"
	.string "Olivine.$"
# 2688 "data/maps/NewBarkTown/scripts.pory"

# 2689 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelCompare:
# 2690 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We'll compare it with\n"
# 2691 "data/maps/NewBarkTown/scripts.pory"
	.string "Cherrygrove's bearing.\l"
# 2692 "data/maps/NewBarkTown/scripts.pory"
	.string "That should narrow the search.$"
# 2693 "data/maps/NewBarkTown/scripts.pory"

# 2694 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineRecords:
# 2695 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I'll bring Aether's records\n"
# 2696 "data/maps/NewBarkTown/scripts.pory"
	.string "too. You should have had them\l"
# 2697 "data/maps/NewBarkTown/scripts.pory"
	.string "before today.$"
# 2698 "data/maps/NewBarkTown/scripts.pory"

# 2699 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineChildren:
# 2700 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Please ask Lillie and Gladion\n"
# 2701 "data/maps/NewBarkTown/scripts.pory"
	.string "to join us. I want to hear what\l"
# 2702 "data/maps/NewBarkTown/scripts.pory"
	.string "they found.$"
# 2703 "data/maps/NewBarkTown/scripts.pory"

# 2704 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLookerReunion:
# 2705 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}I'll contact them, and\n"
# 2706 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor Kukui. We'll arrange\l"
# 2707 "data/maps/NewBarkTown/scripts.pory"
	.string "the meeting in Olivine.$"
# 2708 "data/maps/NewBarkTown/scripts.pory"

# 2709 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBHook:
# 2710 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Rest here for now, {PLAYER}.\n"
# 2711 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll call when we're ready in\l"
# 2712 "data/maps/NewBarkTown/scripts.pory"
	.string "Olivine.$"
# 2713 "data/maps/NewBarkTown/scripts.pory"

# 2714 "data/maps/NewBarkTown/scripts.pory"
@ Narration, no plaque: the explicit time transition (section 18) that takes
# 2715 "data/maps/NewBarkTown/scripts.pory"
@ the barriers and the equipment away before the reload. It names no hour of
# 2716 "data/maps/NewBarkTown/scripts.pory"
@ the day (design 5.3): the scene can end at any time, night included.
# 2717 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRepairs:
# 2718 "data/maps/NewBarkTown/scripts.pory"
	.string "Later, the markers were packed\n"
# 2719 "data/maps/NewBarkTown/scripts.pory"
	.string "away, the barriers were cleared,\l"
# 2720 "data/maps/NewBarkTown/scripts.pory"
	.string "and the residents were back in\l"
# 2721 "data/maps/NewBarkTown/scripts.pory"
	.string "their homes.$"
# 2722 "data/maps/NewBarkTown/scripts.pory"

# 2723 "data/maps/NewBarkTown/scripts.pory"
@ --- Retry (section 19) ------------------------------------------------------
# 2724 "data/maps/NewBarkTown/scripts.pory"

# 2725 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRetryLooker:
# 2726 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The lab is safe.\n"
# 2727 "data/maps/NewBarkTown/scripts.pory"
	.string "We've kept the way back clear.$"
# 2728 "data/maps/NewBarkTown/scripts.pory"

# 2729 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRetryAnabel:
# 2730 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The field is ready.\n"
# 2731 "data/maps/NewBarkTown/scripts.pory"
	.string "Are your Pokémon ready to try\l"
# 2732 "data/maps/NewBarkTown/scripts.pory"
	.string "again?$"
# 2733 "data/maps/NewBarkTown/scripts.pory"

# 2734 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRetryNotReady:
# 2735 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Take care of them first.\n"
# 2736 "data/maps/NewBarkTown/scripts.pory"
	.string "We'll hold the fronts.$"
# 2737 "data/maps/NewBarkTown/scripts.pory"

# 2738 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUnresolved:
# 2739 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The fronts aren't clear yet.\n"
# 2740 "data/maps/NewBarkTown/scripts.pory"
	.string "Regroup before we try again.$"

# 342 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_0:
# 342 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 342 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 342 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 342 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 342 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
	step_end

# 345 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_1:
# 345 "data/maps/NewBarkTown/scripts.pory"
	jump_down
	step_end

# 348 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_2:
# 348 "data/maps/NewBarkTown/scripts.pory"
	walk_up
	step_end

# 350 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_3:
# 350 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_up
	step_end

# 357 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_4:
# 357 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 357 "data/maps/NewBarkTown/scripts.pory"
	walk_right
	step_end

# 361 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_5:
# 361 "data/maps/NewBarkTown/scripts.pory"
	face_left
	step_end

# 363 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_6:
# 363 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 363 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 363 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 363 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 363 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 365 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_7:
# 365 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_left
	step_end

# 371 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_8:
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 371 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 372 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_9:
# 372 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 372 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 372 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 372 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 372 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 387 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_0:
# 387 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_right
	step_end

# 393 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_1:
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 393 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 394 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 394 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 394 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 394 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 394 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 394 "data/maps/NewBarkTown/scripts.pory"
	face_left
	step_end

# 395 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_2:
# 395 "data/maps/NewBarkTown/scripts.pory"
	face_up
	step_end

# 400 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_3:
# 400 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 400 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 400 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 400 "data/maps/NewBarkTown/scripts.pory"
	walk_right
	step_end

# 406 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_4:
# 406 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 406 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 406 "data/maps/NewBarkTown/scripts.pory"
	exit_pokeball
# 406 "data/maps/NewBarkTown/scripts.pory"
	set_visible
	step_end

# 437 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_5:
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

# 438 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_6:
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 438 "data/maps/NewBarkTown/scripts.pory"
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Text_0:
# 405 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_1:
# 410 "data/maps/NewBarkTown/scripts.pory"
	.string "So you picked...\n"
	.string "a {STR_VAR_1}!$"

NewBarkTown_EventScript_RivalBattle_Text_2:
# 412 "data/maps/NewBarkTown/scripts.pory"
	.string "That's a cute Pokémon you have!$"

NewBarkTown_EventScript_RivalBattle_Text_3:
# 413 "data/maps/NewBarkTown/scripts.pory"
	.string "When you walk with it, it'll become\n"
	.string "more friendly!$"

NewBarkTown_EventScript_RivalBattle_Text_4:
# 415 "data/maps/NewBarkTown/scripts.pory"
	.string "You should turn around and talk to it\n"
	.string "sometimes, too.$"

NewBarkTown_EventScript_RivalBattle_Text_5:
# 417 "data/maps/NewBarkTown/scripts.pory"
	.string "Hey, why don't we have a battle?\n"
	.string "That's what trainers usually do when\l"
	.string "they meet!$"

NewBarkTown_EventScript_RivalBattle_Text_6:
# 423 "data/maps/NewBarkTown/scripts.pory"
	.string "You did really well, {PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_7:
# 430 "data/maps/NewBarkTown/scripts.pory"
	.string "That was really fun, and both of our\n"
	.string "Pokémon did their best!$"

NewBarkTown_EventScript_RivalBattle_Text_8:
# 432 "data/maps/NewBarkTown/scripts.pory"
	.string "You got a task from Elm right?\n"
	.string "I'll leave you to it then.\l"
	.string "See ya!$"

RivalsMailbox_Text_0:
# 453 "data/maps/NewBarkTown/scripts.pory"
	.string "Crystal's house$"

RivalsMailbox_Text_1:
# 455 "data/maps/NewBarkTown/scripts.pory"
	.string "Gold's house$"

NewBarkTown_EventScript_ArcherArcadeCall_Text_0:
# 463 "data/maps/NewBarkTown/scripts.pory"
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
