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
	lock
# 41 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall NewBarkTown_Text_LookerCall
# 42 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 43 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 44 "data/maps/NewBarkTown/scripts.pory"
	release
# 45 "data/maps/NewBarkTown/scripts.pory"
	end
# 46 "data/maps/NewBarkTown/scripts.pory"

# 47 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: the two lines after the calls are goto_if_eq, NOT call_if_eq -
# 48 "data/maps/NewBarkTown/scripts.pory"
@ whoever matches one never comes back here. Any new call must go ABOVE them
# 49 "data/maps/NewBarkTown/scripts.pory"
@ or it silently stops running in NEWBARK_TOWN_STATE 2 and 4. (Rift Mission 4,
# 50 "data/maps/NewBarkTown/scripts.pory"
@ .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md section 3.3.)
# 51 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_OnTransition::
# 52 "data/maps/NewBarkTown/scripts.pory"
    call Common_EventScript_SetupRivalGfxId
# 53 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_ApplyUBVisibility      @ Rift Mission 4 - must stay above the gotos
# 54 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
# 55 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
# 56 "data/maps/NewBarkTown/scripts.pory"
	end
# 57 "data/maps/NewBarkTown/scripts.pory"

# 58 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Set_TalkToElm::
# 59 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 60 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_LASS, 0, 11
# 61 "data/maps/NewBarkTown/scripts.pory"
	callnative SetTimeBasedEncounters
# 62 "data/maps/NewBarkTown/scripts.pory"
	end
# 63 "data/maps/NewBarkTown/scripts.pory"

# 64 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Set_TalkToMom::
# 65 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_LASS, 0, 11
# 66 "data/maps/NewBarkTown/scripts.pory"
	callnative SetTimeBasedEncounters
# 67 "data/maps/NewBarkTown/scripts.pory"
	end
# 68 "data/maps/NewBarkTown/scripts.pory"

# 69 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LabSign::
# 70 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
# 71 "data/maps/NewBarkTown/scripts.pory"
	end
# 72 "data/maps/NewBarkTown/scripts.pory"

# 73 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TownSign::
# 74 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
# 75 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 76 "data/maps/NewBarkTown/scripts.pory"
	end
# 77 "data/maps/NewBarkTown/scripts.pory"

# 78 "data/maps/NewBarkTown/scripts.pory"

# 79 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Lass::
# 80 "data/maps/NewBarkTown/scripts.pory"
	lock
# 81 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 82 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
# 83 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
# 84 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
# 85 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
# 86 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 87 "data/maps/NewBarkTown/scripts.pory"
	release
# 88 "data/maps/NewBarkTown/scripts.pory"
	end
# 89 "data/maps/NewBarkTown/scripts.pory"
	
# 90 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState2::
# 91 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 92 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 93 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 94 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 95 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 96 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
# 97 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 98 "data/maps/NewBarkTown/scripts.pory"
	release
# 99 "data/maps/NewBarkTown/scripts.pory"
	end
# 100 "data/maps/NewBarkTown/scripts.pory"

# 101 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState3::
# 102 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
# 103 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 104 "data/maps/NewBarkTown/scripts.pory"
	release
# 105 "data/maps/NewBarkTown/scripts.pory"
	end
# 106 "data/maps/NewBarkTown/scripts.pory"

# 107 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LassState4::
# 108 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 109 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 110 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 111 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 112 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 113 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
# 114 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 115 "data/maps/NewBarkTown/scripts.pory"
	release
# 116 "data/maps/NewBarkTown/scripts.pory"
	end
# 117 "data/maps/NewBarkTown/scripts.pory"

# 118 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Wooper::
# 119 "data/maps/NewBarkTown/scripts.pory"
	lock
# 120 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 121 "data/maps/NewBarkTown/scripts.pory"
	waitse
# 122 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
# 123 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
# 124 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 125 "data/maps/NewBarkTown/scripts.pory"
	release
# 126 "data/maps/NewBarkTown/scripts.pory"
	end
# 127 "data/maps/NewBarkTown/scripts.pory"

# 128 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTrigger::
# 129 "data/maps/NewBarkTown/scripts.pory"
	lock
# 130 "data/maps/NewBarkTown/scripts.pory"
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
# 131 "data/maps/NewBarkTown/scripts.pory"
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
# 132 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
# 133 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 134 "data/maps/NewBarkTown/scripts.pory"
	release
# 135 "data/maps/NewBarkTown/scripts.pory"
	end
# 136 "data/maps/NewBarkTown/scripts.pory"

# 137 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTriggersState2::
# 138 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 139 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 140 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 141 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
# 142 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 143 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
# 144 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 145 "data/maps/NewBarkTown/scripts.pory"
	return
# 146 "data/maps/NewBarkTown/scripts.pory"

# 147 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_LeaveTriggersState4::
# 148 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 149 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
# 150 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 151 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
# 152 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 153 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
# 154 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 155 "data/maps/NewBarkTown/scripts.pory"
	return 
# 156 "data/maps/NewBarkTown/scripts.pory"

# 157 "data/maps/NewBarkTown/scripts.pory"

# 158 "data/maps/NewBarkTown/scripts.pory"

# 159 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_FatMan::
# 160 "data/maps/NewBarkTown/scripts.pory"
	lock
# 161 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 162 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
# 163 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
# 164 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 165 "data/maps/NewBarkTown/scripts.pory"
	release
# 166 "data/maps/NewBarkTown/scripts.pory"
	end
# 167 "data/maps/NewBarkTown/scripts.pory"

# 168 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_FatManState2::
# 169 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
# 170 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 171 "data/maps/NewBarkTown/scripts.pory"
	release
# 172 "data/maps/NewBarkTown/scripts.pory"
	end
# 173 "data/maps/NewBarkTown/scripts.pory"

# 174 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Silver::
# 175 "data/maps/NewBarkTown/scripts.pory"
	lock
# 176 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
# 177 "data/maps/NewBarkTown/scripts.pory"
	delay 60
# 178 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 179 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
# 180 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 181 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 182 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
# 183 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BANG
# 184 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
# 185 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
# 186 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 187 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
# 188 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 189 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 190 "data/maps/NewBarkTown/scripts.pory"
	release
# 191 "data/maps/NewBarkTown/scripts.pory"
	end
# 192 "data/maps/NewBarkTown/scripts.pory"

# 193 "data/maps/NewBarkTown/scripts.pory"

# 194 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_Door::
# 195 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
# 196 "data/maps/NewBarkTown/scripts.pory"
	end
# 197 "data/maps/NewBarkTown/scripts.pory"

# 198 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan1::
# 199 "data/maps/NewBarkTown/scripts.pory"
	givebp 4
# 200 "data/maps/NewBarkTown/scripts.pory"
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
# 201 "data/maps/NewBarkTown/scripts.pory"
	end
# 202 "data/maps/NewBarkTown/scripts.pory"

# 203 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan2::
# 204 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 4
# 205 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_MOMS_FRIEND
# 206 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 207 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 208 "data/maps/NewBarkTown/scripts.pory"
	end
# 209 "data/maps/NewBarkTown/scripts.pory"

# 210 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_TestMan3::
# 211 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 5
# 212 "data/maps/NewBarkTown/scripts.pory"
	
# 213 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
# 214 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
# 215 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
# 216 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
# 217 "data/maps/NewBarkTown/scripts.pory"
	end
# 218 "data/maps/NewBarkTown/scripts.pory"

# 219 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_SilverPushesPlayer:
# 220 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 221 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 222 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 223 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 224 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 225 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 226 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 227 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 228 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 229 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 230 "data/maps/NewBarkTown/scripts.pory"

# 231 "data/maps/NewBarkTown/scripts.pory"

# 232 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_PlayerPushedBySilver:
# 233 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 234 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 235 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 236 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 237 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 238 "data/maps/NewBarkTown/scripts.pory"
	jump_2_down
# 239 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 240 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 241 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 242 "data/maps/NewBarkTown/scripts.pory"

# 243 "data/maps/NewBarkTown/scripts.pory"
	
# 244 "data/maps/NewBarkTown/scripts.pory"

# 245 "data/maps/NewBarkTown/scripts.pory"

# 246 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_FaceDown:
# 247 "data/maps/NewBarkTown/scripts.pory"
	face_down
# 248 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 249 "data/maps/NewBarkTown/scripts.pory"

# 250 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LabSign:
# 251 "data/maps/NewBarkTown/scripts.pory"
	.string "Prof. Elm's Lab$"
# 252 "data/maps/NewBarkTown/scripts.pory"

# 253 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Door:
# 254 "data/maps/NewBarkTown/scripts.pory"
	.string "The door is locked.$"
# 255 "data/maps/NewBarkTown/scripts.pory"

# 256 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Wooper:
# 257 "data/maps/NewBarkTown/scripts.pory"
	.string "Wooper: Woooooop.$"
# 258 "data/maps/NewBarkTown/scripts.pory"

# 259 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_FatManState2:
# 260 "data/maps/NewBarkTown/scripts.pory"
	.string "Wow, your Pokégear is impressive!\n"
# 261 "data/maps/NewBarkTown/scripts.pory"
	.string "Did your mom get it for you?$"
# 262 "data/maps/NewBarkTown/scripts.pory"

# 263 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_FatManState3:
# 264 "data/maps/NewBarkTown/scripts.pory"
	.string "Yo, {PLAYER}!\p"
# 265 "data/maps/NewBarkTown/scripts.pory"
	.string "I hear Prof. Elm discovered\n"
# 266 "data/maps/NewBarkTown/scripts.pory"
	.string "some new Pokémon.$"
# 267 "data/maps/NewBarkTown/scripts.pory"

# 268 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState2:
# 269 "data/maps/NewBarkTown/scripts.pory"
	.string "Wait, {PLAYER}!\p"
# 270 "data/maps/NewBarkTown/scripts.pory"
	.string "It's dangerous to go out\n"
# 271 "data/maps/NewBarkTown/scripts.pory"
	.string "without a Pokémon!\p"
# 272 "data/maps/NewBarkTown/scripts.pory"
	.string "Wild Pokémon jump out of the grass\n"
# 273 "data/maps/NewBarkTown/scripts.pory"
	.string "on the way to the next town.$"
# 274 "data/maps/NewBarkTown/scripts.pory"

# 275 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState3:
# 276 "data/maps/NewBarkTown/scripts.pory"
	.string "Oh! Your Pokémon is adorable!\n"
# 277 "data/maps/NewBarkTown/scripts.pory"
	.string "I wish I had one!$"
# 278 "data/maps/NewBarkTown/scripts.pory"

# 279 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState4:
# 280 "data/maps/NewBarkTown/scripts.pory"
	.string "Hi, {PLAYER}! Leaving again?\p"
# 281 "data/maps/NewBarkTown/scripts.pory"
	.string "You should tell your mom if\n"
# 282 "data/maps/NewBarkTown/scripts.pory"
	.string "you are leaving.$"
# 283 "data/maps/NewBarkTown/scripts.pory"

# 284 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LassState5:
# 285 "data/maps/NewBarkTown/scripts.pory"
	.string "Call your mom on your Pokégear\n"
# 286 "data/maps/NewBarkTown/scripts.pory"
	.string "to let her know how you're doing.$\p"
# 287 "data/maps/NewBarkTown/scripts.pory"

# 288 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Silver1:
# 289 "data/maps/NewBarkTown/scripts.pory"
	.string ". . .\p"
# 290 "data/maps/NewBarkTown/scripts.pory"
	.string "So this is the famous Elm\n"
# 291 "data/maps/NewBarkTown/scripts.pory"
	.string "Pokémon Lab…$"
# 292 "data/maps/NewBarkTown/scripts.pory"

# 293 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Silver2:
# 294 "data/maps/NewBarkTown/scripts.pory"
	.string "…What are you staring at?$"
# 295 "data/maps/NewBarkTown/scripts.pory"

# 296 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_Sign:
# 297 "data/maps/NewBarkTown/scripts.pory"
	.string "New Bark Town\p"
# 298 "data/maps/NewBarkTown/scripts.pory"
	.string "The Town Where the Winds of\n"
# 299 "data/maps/NewBarkTown/scripts.pory"
	.string "a New Beginning Blow$"
# 300 "data/maps/NewBarkTown/scripts.pory"

# 301 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_PlayersHouseMailbox::
# 302 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
# 303 "data/maps/NewBarkTown/scripts.pory"
	end
# 304 "data/maps/NewBarkTown/scripts.pory"

# 305 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ElmsHouseMailbox::
# 306 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
# 307 "data/maps/NewBarkTown/scripts.pory"
	end
# 308 "data/maps/NewBarkTown/scripts.pory"

# 309 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_PlayersHouse:
# 310 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}'s House$"
# 311 "data/maps/NewBarkTown/scripts.pory"

# 312 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ElmsHouse:
# 313 "data/maps/NewBarkTown/scripts.pory"
	.string "Prof. Elm's House$"
# 314 "data/maps/NewBarkTown/scripts.pory"

# 315 "data/maps/NewBarkTown/scripts.pory"
@ Looker's first call (final text, 22/09/2026). Theatrical opening, corrected
# 316 "data/maps/NewBarkTown/scripts.pory"
@ at once; says only that he needs the Champion in person. No creature, no
# 317 "data/maps/NewBarkTown/scripts.pory"
@ town and no name is given away on the phone.
# 318 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_LookerCall:
# 319 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Hello? Is this {PLAYER}?\n"
# 320 "data/maps/NewBarkTown/scripts.pory"
	.string "The Champion of Johto?\p"
# 321 "data/maps/NewBarkTown/scripts.pory"
	.string "…Forgive me. Allow me to begin\n"
# 322 "data/maps/NewBarkTown/scripts.pory"
	.string "again.\p"
# 323 "data/maps/NewBarkTown/scripts.pory"
	.string "My name is Looker.\n"
# 324 "data/maps/NewBarkTown/scripts.pory"
	.string "International Police.\p"
# 325 "data/maps/NewBarkTown/scripts.pory"
	.string "We have not been introduced,\n"
# 326 "data/maps/NewBarkTown/scripts.pory"
	.string "but you may have passed me in\l"
# 327 "data/maps/NewBarkTown/scripts.pory"
	.string "Olivine. The man on holiday.\p"
# 328 "data/maps/NewBarkTown/scripts.pory"
	.string "Yes. That was me.\p"
# 329 "data/maps/NewBarkTown/scripts.pory"
	.string "I am afraid the holiday was\n"
# 330 "data/maps/NewBarkTown/scripts.pory"
	.string "not entirely a holiday.\p"
# 331 "data/maps/NewBarkTown/scripts.pory"
	.string "Something is happening in\n"
# 332 "data/maps/NewBarkTown/scripts.pory"
	.string "Johto, and I would rather\l"
# 333 "data/maps/NewBarkTown/scripts.pory"
	.string "explain it in person.\p"
# 334 "data/maps/NewBarkTown/scripts.pory"
	.string "Our house is on the north\n"
# 335 "data/maps/NewBarkTown/scripts.pory"
	.string "side of Olivine, closest to\l"
# 336 "data/maps/NewBarkTown/scripts.pory"
	.string "the Gym.\p"
# 337 "data/maps/NewBarkTown/scripts.pory"
	.string "Please come when you can.\p"
# 338 "data/maps/NewBarkTown/scripts.pory"
	.string "And, {PLAYER}… congratulations.\n"
# 339 "data/maps/NewBarkTown/scripts.pory"
	.string "Truly.$"

NewBarkTown_EventScript_RivalIntro::
# 343 "data/maps/NewBarkTown/scripts.pory"
	lock
# 344 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_0
# 345 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 346 "data/maps/NewBarkTown/scripts.pory"
	playse SE_WALL_HIT
# 347 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_1
# 348 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 349 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 350 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_2
# 351 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 352 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
# 353 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 354 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 355 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
# 356 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 357 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 358 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 359 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_4
# 360 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 361 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, Common_Movement_ExclamationMark
# 362 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 363 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_5
# 364 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 365 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_6
# 366 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 367 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
# 368 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 369 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 370 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
# 371 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 372 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 373 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_8
# 374 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_9
# 375 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 376 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_HIDE_NEWBARK_RIVALMARILL
# 377 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_RIVAL
# 378 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL
# 379 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL2
# 380 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIVAL_STATE, 1
# 381 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 382 "data/maps/NewBarkTown/scripts.pory"
	release
	end


NewBarkTown_EventScript_RivalBattle::
# 387 "data/maps/NewBarkTown/scripts.pory"
	lock
# 388 "data/maps/NewBarkTown/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 389 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
# 390 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 391 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 392 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
# 393 "data/maps/NewBarkTown/scripts.pory"
	playse SE_LEDGE
# 394 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 395 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_1
# 397 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_2
# 398 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_MARILL2
# 399 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, Common_Movement_ExclamationMark
# 400 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 401 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 402 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_PLAYER, NewBarkTown_EventScript_RivalBattle_Movement_3
# 403 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 404 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_5
# 405 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 406 "data/maps/NewBarkTown/scripts.pory"
	createfieldmugshotrival
# 407 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_0
# 408 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_EventScript_RivalBattle_Movement_4
# 409 "data/maps/NewBarkTown/scripts.pory"
	playse SE_BALL_OPEN
# 410 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 411 "data/maps/NewBarkTown/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 412 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_1
# 414 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_2
# 415 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_3
# 417 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_4
# 419 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_5
# 422 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_NO_WHITEOUT
# 423 "data/maps/NewBarkTown/scripts.pory"
	checkplayergender
# 424 "data/maps/NewBarkTown/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_EventScript_RivalBattle_2
# 427 "data/maps/NewBarkTown/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVALGOLD1, NewBarkTown_EventScript_RivalBattle_Text_6
NewBarkTown_EventScript_RivalBattle_1:
# 429 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_NO_WHITEOUT
# 430 "data/maps/NewBarkTown/scripts.pory"
	special HealPlayerParty
# 431 "data/maps/NewBarkTown/scripts.pory"
	createfieldmugshotrival
# 432 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_7
# 434 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_EventScript_RivalBattle_Text_8
# 437 "data/maps/NewBarkTown/scripts.pory"
	removefieldmugshot
# 438 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 439 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_5
# 440 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_6
# 441 "data/maps/NewBarkTown/scripts.pory"
	waitmovement 0
# 442 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_RIVAL
# 443 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL
# 444 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_MARILL2
# 445 "data/maps/NewBarkTown/scripts.pory"
	fadedefaultbgm
# 446 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIVAL_STATE, 3
# 447 "data/maps/NewBarkTown/scripts.pory"
	release
	end

NewBarkTown_EventScript_RivalBattle_2:
# 425 "data/maps/NewBarkTown/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVALCRYSTAL1, NewBarkTown_EventScript_RivalBattle_Text_6
	goto NewBarkTown_EventScript_RivalBattle_1


RivalsMailbox::
# 452 "data/maps/NewBarkTown/scripts.pory"
	lock
# 453 "data/maps/NewBarkTown/scripts.pory"
	checkplayergender
# 454 "data/maps/NewBarkTown/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq RivalsMailbox_2
# 457 "data/maps/NewBarkTown/scripts.pory"
	msgbox RivalsMailbox_Text_1
RivalsMailbox_1:
# 459 "data/maps/NewBarkTown/scripts.pory"
	release
	end

RivalsMailbox_2:
# 455 "data/maps/NewBarkTown/scripts.pory"
	msgbox RivalsMailbox_Text_0
	goto RivalsMailbox_1


NewBarkTown_EventScript_ArcherArcadeCall::
# 464 "data/maps/NewBarkTown/scripts.pory"
	lock
# 465 "data/maps/NewBarkTown/scripts.pory"
	pokenavcall NewBarkTown_EventScript_ArcherArcadeCall_Text_0
# 480 "data/maps/NewBarkTown/scripts.pory"
	waitmessage
# 481 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 482 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_NEWBARK_TOWN_STATE, 12
# 483 "data/maps/NewBarkTown/scripts.pory"
	release
	end


# 488 "data/maps/NewBarkTown/scripts.pory"

# 489 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 490 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 - Kartana + Guzzlord + Nihilego on the road outside the
# 491 "data/maps/NewBarkTown/scripts.pory"
@ player's own front door. Last mission of the arc, and the one they lose.
# 492 "data/maps/NewBarkTown/scripts.pory"
@
# 493 "data/maps/NewBarkTown/scripts.pory"
@ The story in four lines. Three rifts open over New Bark and the three
# 494 "data/maps/NewBarkTown/scripts.pory"
@ beasts do not behave like three beasts: they move in the same instant, in
# 495 "data/maps/NewBarkTown/scripts.pory"
@ the same direction, like one thing wearing three bodies. The only counter
# 496 "data/maps/NewBarkTown/scripts.pory"
@ is to break all three at once, which takes four pairs of hands, which is
# 497 "data/maps/NewBarkTown/scripts.pory"
@ how the kid who was told "no" gets let in - by the woman who has just been
# 498 "data/maps/NewBarkTown/scripts.pory"
@ taught to ask. And when the three are down, the creature from the other
# 499 "data/maps/NewBarkTown/scripts.pory"
@ three missions walks out of the light, EATS them, becomes something else,
# 500 "data/maps/NewBarkTown/scripts.pory"
@ and puts all four of them on the ground in one motion. The town stands.
# 501 "data/maps/NewBarkTown/scripts.pory"
@ Nobody wins. That was the plan from the first mission.
# 502 "data/maps/NewBarkTown/scripts.pory"
@
# 503 "data/maps/NewBarkTown/scripts.pory"
@ Cast: Looker, Anabel, Mom, Gold/Crystal (+ Azumarill), Professor Elm and
# 504 "data/maps/NewBarkTown/scripts.pory"
@ Madame Lusamine, plus the creature and what it turns into.
# 505 "data/maps/NewBarkTown/scripts.pory"
@ Plan: .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md
# 506 "data/maps/NewBarkTown/scripts.pory"
@
# 507 "data/maps/NewBarkTown/scripts.pory"
@ Floor plan (dump_mapa.py NewBarkTown; y grows DOWNWARD). There is not one
# 508 "data/maps/NewBarkTown/scripts.pory"
@ water tile in LAYOUT_NEW_BARK_TOWN, so the collision bit is the whole
# 509 "data/maps/NewBarkTown/scripts.pory"
@ truth here - unlike the Cherrygrove beach.
# 510 "data/maps/NewBarkTown/scripts.pory"
@
# 511 "data/maps/NewBarkTown/scripts.pory"
@       x= 2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
# 512 "data/maps/NewBarkTown/scripts.pory"
@   y= 9   #  #  #  .  .  #  #  #  D  #  .  #  .  .  .  .  #  #  #  #  #  #  #  #
# 513 "data/maps/NewBarkTown/scripts.pory"
@   y=10   #  #  .  .  .  .  .  .  .  E' .  .  .  1  1a 1b #  #  #  #  #  #  #  #
# 514 "data/maps/NewBarkTown/scripts.pory"
@   y=11   .  .  .  .  .  .  .  .  .  .  .  .  .  .  Nk #  #  #  d  #  #  .  .  .
# 515 "data/maps/NewBarkTown/scripts.pory"
@   y=12   .  U' .  .  .  .  .  .  .  .  .  .  .  .  N  U  M  *  K  A  E  .  .  .
# 516 "data/maps/NewBarkTown/scripts.pory"
@   y=13   .  .  .  .  .  .  .  .  .  .  .  .  2  2a 2b 2c 2d 2e .  G  z  .  .  .
# 517 "data/maps/NewBarkTown/scripts.pory"
@   y=14   .  .  .  .  .  .  .  #  .  .  .  .  .  .  a3 a2 a1 aX .  .  z' .  .  .
# 518 "data/maps/NewBarkTown/scripts.pory"
@   y=15   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  3  3a 3b
# 519 "data/maps/NewBarkTown/scripts.pory"
@
# 520 "data/maps/NewBarkTown/scripts.pory"
@   D  lab door, warp (10,9)          d  player's house door, warp (20,11)
# 521 "data/maps/NewBarkTown/scripts.pory"
@   *  player (20,12)                 K  Looker (21,12)   A  Anabel (22,12)
# 522 "data/maps/NewBarkTown/scripts.pory"
@   M  Mom (19,12)                    G  Gold/Crystal (21,13)
# 523 "data/maps/NewBarkTown/scripts.pory"
@   z  Azumarill starts (22,13)       z' Azumarill after the cut-off (19,14)
# 524 "data/maps/NewBarkTown/scripts.pory"
@   U' Lusamine starts (3,12)         U  Lusamine after the fade (18,12),
# 525 "data/maps/NewBarkTown/scripts.pory"
@                                        then (17,12) from UBKnot onward
# 526 "data/maps/NewBarkTown/scripts.pory"
@   E' Elm starts (11,10)             E  Elm after the fade (23,12)
# 527 "data/maps/NewBarkTown/scripts.pory"
@   1  Kartana (15,10) -> 1a (16,10) -> 1b (17,10) in the lockstep drift
# 528 "data/maps/NewBarkTown/scripts.pory"
@   2  Nihilego (14,13) -> 2a -> 2b in the drift, then 2c 2d 2e in the lunge,
# 529 "data/maps/NewBarkTown/scripts.pory"
@      ending at (19,13), one diagonal step from the player and under Mom
# 530 "data/maps/NewBarkTown/scripts.pory"
@   3  Guzzlord (23,15) -> 3a (24,15) -> 3b (25,15); (26,15) is wall
# 531 "data/maps/NewBarkTown/scripts.pory"
@   a1 a2 a3  Azumarill's charge at the creature, ending (16,14)
# 532 "data/maps/NewBarkTown/scripts.pory"
@   N  the creature (16,12), which is also where what it becomes stands
# 533 "data/maps/NewBarkTown/scripts.pory"
@   Nk (16,11) is where Kartana is dragged to before it is eaten
# 534 "data/maps/NewBarkTown/scripts.pory"
@
# 535 "data/maps/NewBarkTown/scripts.pory"
@ LOOKER'S POCKET. (21,11) is the wall of the player's house, (22,12) is
# 536 "data/maps/NewBarkTown/scripts.pory"
@ Anabel and (21,13) is Gold/Crystal. The ONLY tile Looker can be talked to
# 537 "data/maps/NewBarkTown/scripts.pory"
@ from is (20,12), facing east - no getplayerxy needed.
# 538 "data/maps/NewBarkTown/scripts.pory"
@ And (20,12) is exactly where the game puts the player twice over:
# 539 "data/maps/NewBarkTown/scripts.pory"
@ HEAL_LOCATION_NEW_BARK_TOWN is (20,12) (src/data/heal_locations.h:139) and
# 540 "data/maps/NewBarkTown/scripts.pory"
@ NewBarkTown_OnLoad re-does the setrespawn on every load, so a blackout AND
# 541 "data/maps/NewBarkTown/scripts.pory"
@ a Fly both land on the talk tile. Retry costs zero steps - the only mission
# 542 "data/maps/NewBarkTown/scripts.pory"
@ in the arc where that is true.
# 543 "data/maps/NewBarkTown/scripts.pory"
@
# 544 "data/maps/NewBarkTown/scripts.pory"
@ (20,13) IS DELIBERATELY EMPTY, before the scene and during it. Nothing is
# 545 "data/maps/NewBarkTown/scripts.pory"
@ ever parked there. The Azumarill choreography goes around the outside, on
# 546 "data/maps/NewBarkTown/scripts.pory"
@ y=14, precisely so that it never has to stand in front of the player.
# 547 "data/maps/NewBarkTown/scripts.pory"
@
# 548 "data/maps/NewBarkTown/scripts.pory"
@ The player's front door at (20,11) stays usable before the scene. Harmless:
# 549 "data/maps/NewBarkTown/scripts.pory"
@ the scene only starts by talking to Looker, the house is empty during the
# 550 "data/maps/NewBarkTown/scripts.pory"
@ incident (NewBarkTown_PlayersHouse_1F_ApplyMomVisibility), and coming back
# 551 "data/maps/NewBarkTown/scripts.pory"
@ out puts the player on (20,12) again.
# 552 "data/maps/NewBarkTown/scripts.pory"
@
# 553 "data/maps/NewBarkTown/scripts.pory"
@ The three beasts stand on walkable ground and CAN be reached on foot. That
# 554 "data/maps/NewBarkTown/scripts.pory"
@ is fine - they only exist while the player is under lockall, and all three
# 555 "data/maps/NewBarkTown/scripts.pory"
@ have script NULL. Do not "fix" this by inventing collision.
# 556 "data/maps/NewBarkTown/scripts.pory"
@
# 557 "data/maps/NewBarkTown/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 558 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_1 - fixed cast cache (Looker, Anabel, Mom, Gold/Crystal,
# 559 "data/maps/NewBarkTown/scripts.pory"
@                 Azumarill)
# 560 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_2 - the three Ultra Beasts; always hidden on load
# 561 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_3 - Elm ONLY          \ separate because the cutscene
# 562 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_4 - Lusamine ONLY     / removeobjects these two to move them,
# 563 "data/maps/NewBarkTown/scripts.pory"
@                 and removeobject SETS the template's flag. If they shared
# 564 "data/maps/NewBarkTown/scripts.pory"
@                 FLAG_TEMP_1 the fade in UBScene would hide the whole cast.
# 565 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_5 - the creature ONLY       \ same reason: the absorption
# 566 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_6 - what it becomes ONLY    / removeobjects both of them
# 567 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_2  - battle outcome
# 568 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_3  - the player's pick: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego.
# 569 "data/maps/NewBarkTown/scripts.pory"
@                 Survives the battle: coming back from a battle does not
# 570 "data/maps/NewBarkTown/scripts.pory"
@                 reload the map, so ClearTempFieldEventData does not run.
# 571 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_4  - which Cosmog-family Pokemon the player is carrying, sampled
# 572 "data/maps/NewBarkTown/scripts.pory"
@                 AFTER the battle (the battle can evolve it) and re-read by
# 573 "data/maps/NewBarkTown/scripts.pory"
@                 the closing conversation. SPECIES_NONE = none.
# 574 "data/maps/NewBarkTown/scripts.pory"
@ Checked 20/09/2026: this map used no FLAG_TEMP_* or VAR_TEMP_* at all
# 575 "data/maps/NewBarkTown/scripts.pory"
@ before this mission. VAR_TEMP_1 is skipped anyway, for uniformity with the
# 576 "data/maps/NewBarkTown/scripts.pory"
@ three earlier missions (there it is VAR_TEMP_TRANSFERRED_SPECIES).
# 577 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_TEMP_E is reserved by the engine to suppress the follower - never use it.
# 578 "data/maps/NewBarkTown/scripts.pory"
@
# 579 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: seven residents of this map (locals 1, 2, 4, 5, 6, 7, 8) now carry
# 580 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_EVENT_ULTRABEAST_NEWBARK in their map.json "flag" field. A removeobject
# 581 "data/maps/NewBarkTown/scripts.pory"
@ on ANY of them SETS that flag and empties the whole town, permanently.
# 582 "data/maps/NewBarkTown/scripts.pory"
@
# 583 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: never clear FLAG_HIDE_NEWBARK_RIVALMARILL. Locals 9, 10 and 11 -
# 584 "data/maps/NewBarkTown/scripts.pory"
@ the original Gold/Crystal and two Marill - are hidden behind it from the
# 585 "data/maps/NewBarkTown/scripts.pory"
@ rival battle onward (setflag at the first rival scene, plus the three
# 586 "data/maps/NewBarkTown/scripts.pory"
@ removeobject at VAR_RIVAL_STATE 2 -> 3). If it were ever cleared the player
# 587 "data/maps/NewBarkTown/scripts.pory"
@ would see a SECOND Gold/Crystal at (12,13) while the mission's one stands
# 588 "data/maps/NewBarkTown/scripts.pory"
@ at (21,13), and a stray Marill at (11,13) right beside Nihilego.
# 589 "data/maps/NewBarkTown/scripts.pory"
@
# 590 "data/maps/NewBarkTown/scripts.pory"
@ OBJECT BUDGET. OBJECT_EVENTS_COUNT is 16 and includes the player
# 591 "data/maps/NewBarkTown/scripts.pory"
@ (include/constants/global.h:83). The peak of this scene is the player, the
# 592 "data/maps/NewBarkTown/scripts.pory"
@ follower, this mission's ten road objects and the creature = 13/16. What it
# 593 "data/maps/NewBarkTown/scripts.pory"
@ becomes only ever spawns after the three beasts and the creature have been
# 594 "data/maps/NewBarkTown/scripts.pory"
@ removed, so it never adds to the peak. Three spare slots, and every object
# 595 "data/maps/NewBarkTown/scripts.pory"
@ added here spends one.
# 596 "data/maps/NewBarkTown/scripts.pory"
@
# 597 "data/maps/NewBarkTown/scripts.pory"
@ The four OBJ_EVENT_GFX_LIGHT_SPRITE on this map cost NOTHING against that
# 598 "data/maps/NewBarkTown/scripts.pory"
@ 16. TrySpawnObjectEvents special-cases them (src/event_object_movement.c:
# 599 "data/maps/NewBarkTown/scripts.pory"
@ 3168): a light sprite goes to SpawnLightSprite, which CreateSprite()s into
# 600 "data/maps/NewBarkTown/scripts.pory"
@ gSprites[] and never touches gObjectEvents[]. So the lamps keep their own
# 601 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_NIGHT_POKEMON and this mission does not touch the lighting system at
# 602 "data/maps/NewBarkTown/scripts.pory"
@ all. Do not "free up slots" by hiding them - there is nothing to free.
# 603 "data/maps/NewBarkTown/scripts.pory"
@
# 604 "data/maps/NewBarkTown/scripts.pory"
@ What the budget DOES matter for: an object that does not fit simply fails
# 605 "data/maps/NewBarkTown/scripts.pory"
@ to spawn, with no error and no warning, and TrySpawnObjectEvents walks the
# 606 "data/maps/NewBarkTown/scripts.pory"
@ templates IN ORDER - so the ones that would lose are this mission's
# 607 "data/maps/NewBarkTown/scripts.pory"
@ (locals 16-27), the LAST in the array. Overspend and Looker is the one who
# 608 "data/maps/NewBarkTown/scripts.pory"
@ goes missing, which leaves the mission with no way to start.
# 609 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 610 "data/maps/NewBarkTown/scripts.pory"

# 611 "data/maps/NewBarkTown/scripts.pory"
@ Called from NewBarkTown_OnTransition, which runs before any object spawns -
# 612 "data/maps/NewBarkTown/scripts.pory"
@ so setflag/clearflag work here and removeobject would not. Temps are zeroed
# 613 "data/maps/NewBarkTown/scripts.pory"
@ on every load, so this recomputes from scratch every time.
# 614 "data/maps/NewBarkTown/scripts.pory"
@ The three unconditional setflag are what makes a retry after a blackout
# 615 "data/maps/NewBarkTown/scripts.pory"
@ start clean for free: the beasts and the creature are never on the road
# 616 "data/maps/NewBarkTown/scripts.pory"
@ until the cutscene puts them there.
# 617 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ApplyUBVisibility::
# 618 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_2                        @ the beasts: only the cutscene brings them in
# 619 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_5                        @ the creature
# 620 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_6                        @ what it becomes
# 621 "data/maps/NewBarkTown/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_HideUBCast
# 622 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_1
# 623 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 624 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 625 "data/maps/NewBarkTown/scripts.pory"
	return
# 626 "data/maps/NewBarkTown/scripts.pory"

# 627 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_HideUBCast::
# 628 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_1
# 629 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_3
# 630 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_4
# 631 "data/maps/NewBarkTown/scripts.pory"
	return
# 632 "data/maps/NewBarkTown/scripts.pory"

# 633 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 634 "data/maps/NewBarkTown/scripts.pory"
@ Two staging helpers, used all through the scene.
# 635 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 636 "data/maps/NewBarkTown/scripts.pory"

# 637 "data/maps/NewBarkTown/scripts.pory"
@ Flash da cena. fadescreenswapbuffers e NAO fadescreen: fadescreen copia
# 638 "data/maps/NewBarkTown/scripts.pory"
@ gPlttBufferFaded -> gPlttBufferUnfaded ao escurecer (src/field_weather.c,
# 639 "data/maps/NewBarkTown/scripts.pory"
@ FadeScreen) e o FADE_FROM_* seguinte reaplica o tint de horario por cima do
# 640 "data/maps/NewBarkTown/scripts.pory"
@ que ja estava tintado. A noite (coeff 10) cada par de flashes multiplicava a
# 641 "data/maps/NewBarkTown/scripts.pory"
@ cena por ~0,46 de novo, e depois de tres ou quatro a cidade ficava preta.
# 642 "data/maps/NewBarkTown/scripts.pory"
@ fadescreenswapbuffers usa BLDY no hardware e nao encosta nas paletas.
# 643 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBFlash::
# 644 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 645 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 646 "data/maps/NewBarkTown/scripts.pory"
	return
# 647 "data/maps/NewBarkTown/scripts.pory"

# 648 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBShake::
# 649 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 1   @ vertical pan
# 650 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 651 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 12  @ num shakes
# 652 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 653 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 654 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 655 "data/maps/NewBarkTown/scripts.pory"
	return
# 656 "data/maps/NewBarkTown/scripts.pory"

# 657 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 658 "data/maps/NewBarkTown/scripts.pory"
@ Idle conversations, available from the moment the player reaches town and
# 659 "data/maps/NewBarkTown/scripts.pory"
@ until the YES. Each one ends by turning the actor back to the facing its
# 660 "data/maps/NewBarkTown/scripts.pory"
@ map.json template asks for, so a talk from an odd tile cannot leave anyone
# 661 "data/maps/NewBarkTown/scripts.pory"
@ crooked when the cutscene starts.
# 662 "data/maps/NewBarkTown/scripts.pory"
@
# 663 "data/maps/NewBarkTown/scripts.pory"
@ Two of them react to the Cosmog family in the party (design section 4.11):
# 664 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine, who is the only living person who knows what that light looks
# 665 "data/maps/NewBarkTown/scripts.pory"
@ like from the other side, and Elm, who is the one who identified the egg in
# 666 "data/maps/NewBarkTown/scripts.pory"
@ the first place. Both are OPTIONAL and carry NO state - without the Pokemon
# 667 "data/maps/NewBarkTown/scripts.pory"
@ the conversation is exactly the one line it always was.
# 668 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine's version has one non-negotiable rule (design section 6.4): the
# 669 "data/maps/NewBarkTown/scripts.pory"
@ scene does not suggest, at any point, that any of this is the player's
# 670 "data/maps/NewBarkTown/scripts.pory"
@ fault, and SHE is the one who says so out loud.
# 671 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 672 "data/maps/NewBarkTown/scripts.pory"

# 673 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine alone on the road in, at (3,12), reachable from (2,12), (4,12),
# 674 "data/maps/NewBarkTown/scripts.pory"
@ (3,11) and (3,13). This is her first spoken line in the whole arc. Nobody
# 675 "data/maps/NewBarkTown/scripts.pory"
@ announced her - the Olivine briefing does not mention her at all, on
# 676 "data/maps/NewBarkTown/scripts.pory"
@ purpose. She gives away nothing about the knot in UBKnot.
# 677 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamine::
# 678 "data/maps/NewBarkTown/scripts.pory"
	lock
# 679 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 680 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineIdle, MSGBOX_DEFAULT
# 681 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 682 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, NewBarkTown_EventScript_UBLusamineEnd
# 683 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 684 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineIdleCosmog, MSGBOX_DEFAULT
# 685 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamineEnd::
# 686 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 687 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST     @ map.json FACE_RIGHT
# 688 "data/maps/NewBarkTown/scripts.pory"
	release
# 689 "data/maps/NewBarkTown/scripts.pory"
	end
# 690 "data/maps/NewBarkTown/scripts.pory"

# 691 "data/maps/NewBarkTown/scripts.pory"
@ Elm at (11,10), outside his own lab door (10,9).
# 692 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElm::
# 693 "data/maps/NewBarkTown/scripts.pory"
	lock
# 694 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 695 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmIdle, MSGBOX_DEFAULT
# 696 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 697 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, NewBarkTown_EventScript_UBElmEnd
# 698 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 699 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmIdleCosmog, MSGBOX_DEFAULT
# 700 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElmEnd::
# 701 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 702 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_SOUTH         @ map.json FACE_DOWN
# 703 "data/maps/NewBarkTown/scripts.pory"
	release
# 704 "data/maps/NewBarkTown/scripts.pory"
	end
# 705 "data/maps/NewBarkTown/scripts.pory"

# 706 "data/maps/NewBarkTown/scripts.pory"
@ Mom at (19,12), reachable from (18,12) and (19,13); (19,11) is wall.
# 707 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMom::
# 708 "data/maps/NewBarkTown/scripts.pory"
	lock
# 709 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 710 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomIdle, MSGBOX_DEFAULT
# 711 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 712 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST          @ map.json FACE_RIGHT
# 713 "data/maps/NewBarkTown/scripts.pory"
	release
# 714 "data/maps/NewBarkTown/scripts.pory"
	end
# 715 "data/maps/NewBarkTown/scripts.pory"

# 716 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal at (21,13), reachable from (20,13) and (21,14). They ask to be
# 717 "data/maps/NewBarkTown/scripts.pory"
@ put in the fight HERE, early. The refusal comes later, on camera, in
# 718 "data/maps/NewBarkTown/scripts.pory"
@ NewBarkTown_EventScript_UBRivalIn - and so does the person who overrules
# 719 "data/maps/NewBarkTown/scripts.pory"
@ it. Do not delete any of the three halves.
# 720 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRival::
# 721 "data/maps/NewBarkTown/scripts.pory"
	lock
# 722 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 723 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIdle, MSGBOX_DEFAULT
# 724 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 725 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_NORTH       @ map.json FACE_UP
# 726 "data/maps/NewBarkTown/scripts.pory"
	release
# 727 "data/maps/NewBarkTown/scripts.pory"
	end
# 728 "data/maps/NewBarkTown/scripts.pory"

# 729 "data/maps/NewBarkTown/scripts.pory"
@ Anabel at (22,12). Looker fills (21,12), Azumarill fills (22,13) and
# 730 "data/maps/NewBarkTown/scripts.pory"
@ (22,11) is wall, so the only way to her is the long way round: (20,13) ->
# 731 "data/maps/NewBarkTown/scripts.pory"
@ (20,14) -> east along y=14 -> (23,14) -> (23,13) -> (23,12).
# 732 "data/maps/NewBarkTown/scripts.pory"
@ She plants NOTHING here and she does not explain herself here either. All
# 733 "data/maps/NewBarkTown/scripts.pory"
@ of that happened in Olivine, in the briefing, sitting down, with time -
# 734 "data/maps/NewBarkTown/scripts.pory"
@ which is where the author asked for it. On this road she is working.
# 735 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabel::
# 736 "data/maps/NewBarkTown/scripts.pory"
	lock
# 737 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 738 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 739 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 740 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST       @ map.json FACE_LEFT
# 741 "data/maps/NewBarkTown/scripts.pory"
	release
# 742 "data/maps/NewBarkTown/scripts.pory"
	end
# 743 "data/maps/NewBarkTown/scripts.pory"

# 744 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 745 "data/maps/NewBarkTown/scripts.pory"
@ The cutscene. Everything from the YES onward is scripted through to a
# 746 "data/maps/NewBarkTown/scripts.pory"
@ battle outcome, and then through to the thing that takes the win away.
# 747 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 748 "data/maps/NewBarkTown/scripts.pory"

# 749 "data/maps/NewBarkTown/scripts.pory"
@ Only reachable from (20,12) facing east (see LOOKER'S POCKET above), so no
# 750 "data/maps/NewBarkTown/scripts.pory"
@ getplayerxy check is needed.
# 751 "data/maps/NewBarkTown/scripts.pory"
@ NOTHING changes state before the YES. The YES is the last exit point.
# 752 "data/maps/NewBarkTown/scripts.pory"
@ Elm's countdown is read out BEFORE the YES on purpose - it is the clock
# 753 "data/maps/NewBarkTown/scripts.pory"
@ that turns "three rifts" into "now", the same job Lillie's read did in
# 754 "data/maps/NewBarkTown/scripts.pory"
@ Mission 2 and Kukui's in Mission 3.
# 755 "data/maps/NewBarkTown/scripts.pory"
@ But Elm himself is still at (11,10), nine tiles west and off camera, so
# 756 "data/maps/NewBarkTown/scripts.pory"
@ ANABEL relays his log here and Elm only speaks for himself once he has
# 757 "data/maps/NewBarkTown/scripts.pory"
@ walked into frame in UBScene. Do not move his own voice back up here
# 758 "data/maps/NewBarkTown/scripts.pory"
@ without also moving his object.
# 759 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLooker::
# 760 "data/maps/NewBarkTown/scripts.pory"
	lock
# 761 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 762 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLookerGreet, MSGBOX_DEFAULT
# 763 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBClockRelay, MSGBOX_DEFAULT
# 764 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBReady, MSGBOX_YESNO
# 765 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBNotReady
# 766 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBScene
# 767 "data/maps/NewBarkTown/scripts.pory"

# 768 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNotReady::
# 769 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNotReady, MSGBOX_DEFAULT
# 770 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 771 "data/maps/NewBarkTown/scripts.pory"
	release
# 772 "data/maps/NewBarkTown/scripts.pory"
	end
# 773 "data/maps/NewBarkTown/scripts.pory"

# 774 "data/maps/NewBarkTown/scripts.pory"
@ A simple battle, so there is no party-size check to do, and the mission
# 775 "data/maps/NewBarkTown/scripts.pory"
@ hands out nothing, so the entregar-pokemon-ou-ovo space rule does not apply.
# 776 "data/maps/NewBarkTown/scripts.pory"
@
# 777 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: setobjectxy DOES NOT WORK HERE AND FAILS SILENTLY.
# 778 "data/maps/NewBarkTown/scripts.pory"
@ TryMoveObjectEventToMapCoords (src/event_object_movement.c:3812) only acts
# 779 "data/maps/NewBarkTown/scripts.pory"
@ on a SPAWNED object, and spawning only happens near the camera
# 780 "data/maps/NewBarkTown/scripts.pory"
@ (TrySpawnObjectEvents, :3148). Elm at (11,10) is on the edge of that window
# 781 "data/maps/NewBarkTown/scripts.pory"
@ and Lusamine at (3,12) is far outside it. The template has to be moved
# 782 "data/maps/NewBarkTown/scripts.pory"
@ instead, and the object re-spawned:
# 783 "data/maps/NewBarkTown/scripts.pory"
@   removeobject      - a no-op if it was never spawned; if it WAS spawned it
# 784 "data/maps/NewBarkTown/scripts.pory"
@                       sets only that actor's own FLAG_TEMP_3/4 (which is
# 785 "data/maps/NewBarkTown/scripts.pory"
@                       exactly why those two do not share FLAG_TEMP_1)
# 786 "data/maps/NewBarkTown/scripts.pory"
@   setobjectxyperm   - moves the TEMPLATE; holds while the map stays loaded
# 787 "data/maps/NewBarkTown/scripts.pory"
@   clearflag + addobject - spawns it at the new place
# 788 "data/maps/NewBarkTown/scripts.pory"
@ The order is mandatory and the trio is correct whether or not the actor
# 789 "data/maps/NewBarkTown/scripts.pory"
@ happened to be spawned. Anyone who "simplifies" this into a setobjectxy
# 790 "data/maps/NewBarkTown/scripts.pory"
@ will watch Lusamine never appear, with no error at all.
# 791 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBScene::
# 792 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 793 "data/maps/NewBarkTown/scripts.pory"
	lockall
# 794 "data/maps/NewBarkTown/scripts.pory"
	hidefollower
# 795 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 796 "data/maps/NewBarkTown/scripts.pory"
	@ Elm (11,10) -> (23,12), then faces west at the line of people.
# 797 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_ELM
# 798 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_ELM, 23, 12
# 799 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 800 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_ELM
# 801 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_WEST
# 802 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine (3,12) -> (18,12), then faces east at Mom and the player.
# 803 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_LUSAMINE
# 804 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_LUSAMINE, 18, 12
# 805 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 806 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_LUSAMINE
# 807 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 808 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 809 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBTheyArrive, MSGBOX_DEFAULT
# 810 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 811 "data/maps/NewBarkTown/scripts.pory"
	@ Tremor, then the white flash that brings all three in at once.
# 812 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 2   @ vertical pan
# 813 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 814 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 32  @ num shakes
# 815 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 816 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 817 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 818 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 819 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_2
# 820 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_KARTANA
# 821 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_GUZZLORD
# 822 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NIHILEGO
# 823 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 824 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 825 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 826 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 827 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 828 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 829 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 830 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAppear, MSGBOX_DEFAULT
# 831 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 832 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBSynergy
# 833 "data/maps/NewBarkTown/scripts.pory"

# 834 "data/maps/NewBarkTown/scripts.pory"
@ THE SYNERGY, SHOWN BEFORE IT IS EXPLAINED - the theme of the arc since
# 835 "data/maps/NewBarkTown/scripts.pory"
@ Mission 3, and from here on the house style for every Ultra Beast encounter
# 836 "data/maps/NewBarkTown/scripts.pory"
@ (design section 6, regras comuns).
# 837 "data/maps/NewBarkTown/scripts.pory"
@ It costs three applymovements: all three drift ONE tile east in the same
# 838 "data/maps/NewBarkTown/scripts.pory"
@ instant, from three corners of the map that cannot see each other. Then
# 839 "data/maps/NewBarkTown/scripts.pory"
@ they do it again. Elm is the one who notices it is the SAME instant,
# 840 "data/maps/NewBarkTown/scripts.pory"
@ because he is the only one on the road holding a clock.
# 841 "data/maps/NewBarkTown/scripts.pory"
@ Tiles checked with dump_mapa.py: Kartana (15,10)->(16,10)->(17,10),
# 842 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego (14,13)->(15,13)->(16,13), Guzzlord (23,15)->(24,15)->(25,15).
# 843 "data/maps/NewBarkTown/scripts.pory"
@ All six are walkable and all six stay inside the camera (x 13..27).
# 844 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSynergy::
# 845 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_UBDrift
# 846 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_UBDrift
# 847 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_UBDrift
# 848 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 849 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 850 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 851 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBSynergyFirst, MSGBOX_DEFAULT
# 852 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 853 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_UBDrift
# 854 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_UBDrift
# 855 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_UBDrift
# 856 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 857 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 858 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 859 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBSynergyNamed, MSGBOX_DEFAULT
# 860 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 861 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBLunge
# 862 "data/maps/NewBarkTown/scripts.pory"

# 863 "data/maps/NewBarkTown/scripts.pory"
@ DIRECT DANGER TO THE PLAYER, and the first thing in this mission that
# 864 "data/maps/NewBarkTown/scripts.pory"
@ somebody stops. Nihilego breaks the formation and runs the last three tiles
# 865 "data/maps/NewBarkTown/scripts.pory"
@ of y=13 to (19,13) - diagonally touching the player, directly under Mom,
# 866 "data/maps/NewBarkTown/scripts.pory"
@ who is the one person on this road who was told to go inside and would not.
# 867 "data/maps/NewBarkTown/scripts.pory"
@ The rescue is the Azumarill, and it goes AROUND, on y=14, because nothing
# 868 "data/maps/NewBarkTown/scripts.pory"
@ is ever parked at (20,13). (22,13) -> (22,14) -> (21,14) -> (20,14) ->
# 869 "data/maps/NewBarkTown/scripts.pory"
@ (19,14), facing north at the thing. The two paths never share a tile.
# 870 "data/maps/NewBarkTown/scripts.pory"
@ This beat is why Lusamine says what she says next. Do not reorder them.
# 871 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLunge::
# 872 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 873 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, Common_Movement_ExclamationMark
# 874 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 875 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_NihilegoLunge
# 876 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillCutOff
# 877 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 878 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 879 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 880 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBCutOff, MSGBOX_DEFAULT
# 881 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 882 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBKnot
# 883 "data/maps/NewBarkTown/scripts.pory"

# 884 "data/maps/NewBarkTown/scripts.pory"
@ The knot: Lusamine means to take all three, and Mom is the one who stops
# 885 "data/maps/NewBarkTown/scripts.pory"
@ her. The closemessage above is load-bearing - without it Lusamine's step
# 886 "data/maps/NewBarkTown/scripts.pory"
@ would play behind an open text box.
# 887 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBKnot::
# 888 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine (18,12) -> (17,12), one step west toward the rifts. (17,12) is
# 889 "data/maps/NewBarkTown/scripts.pory"
	@ clear and still well inside the camera (x >= 13 with the player at 20).
# 890 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_StepLeftFaceLeft
# 891 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 892 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineTakesThree, MSGBOX_DEFAULT
# 893 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 894 "data/maps/NewBarkTown/scripts.pory"
	@ Mom (19,12) turns her back on her own child to face Lusamine at (17,12).
# 895 "data/maps/NewBarkTown/scripts.pory"
	@ x 17 < 19, so west. The turn IS the beat - do not shorten it away.
# 896 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
# 897 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomStopsHer, MSGBOX_DEFAULT
# 898 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 899 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 900 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineAsks, MSGBOX_DEFAULT
# 901 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 902 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBPlan
# 903 "data/maps/NewBarkTown/scripts.pory"

# 904 "data/maps/NewBarkTown/scripts.pory"
@ Anabel answers the question, and answering it costs her something: three
# 905 "data/maps/NewBarkTown/scripts.pory"
@ rifts open at once is more than she can stand in front of quietly. Looker
# 906 "data/maps/NewBarkTown/scripts.pory"
@ is at (21,12) and she is at (22,12), right beside him, so he does not need
# 907 "data/maps/NewBarkTown/scripts.pory"
@ to walk to catch her. x 22 > 21 -> east to her, x 20 < 21 -> west to come
# 908 "data/maps/NewBarkTown/scripts.pory"
@ back to the player.
# 909 "data/maps/NewBarkTown/scripts.pory"
@ SHE DOES NOT EXPLAIN HERSELF HERE. The author was explicit: the Faller
# 910 "data/maps/NewBarkTown/scripts.pory"
@ conversation does not belong in the middle of a fight. It happens in
# 911 "data/maps/NewBarkTown/scripts.pory"
@ Olivine, in the briefing, before any of this - Text_BriefingM4 in
# 912 "data/maps/NewBarkTown/scripts.pory"
@ data/maps/OlivineCity_House1/scripts.pory - and it comes back once, at the
# 913 "data/maps/NewBarkTown/scripts.pory"
@ end, when everyone is standing on the road again (UBAnabelPromise). Two
# 914 "data/maps/NewBarkTown/scripts.pory"
@ boxes here, and she is back at work in the third.
# 915 "data/maps/NewBarkTown/scripts.pory"
@ What she gives the scene instead is the COUNTER, and the counter is what
# 916 "data/maps/NewBarkTown/scripts.pory"
@ turns the standard pick-one-Ultra-Beast menu into a plan: three things that
# 917 "data/maps/NewBarkTown/scripts.pory"
@ move in one instant have to be broken in one instant, and that needs a
# 918 "data/maps/NewBarkTown/scripts.pory"
@ fourth pair of hands.
# 919 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPlan::
# 920 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelBreaks, MSGBOX_DEFAULT
# 921 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 922 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 923 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, Common_Movement_ExclamationMark
# 924 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 925 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_EAST
# 926 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 927 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelStands, MSGBOX_DEFAULT
# 928 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 929 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST      @ back to the player
# 930 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBCounter, MSGBOX_DEFAULT
# 931 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 932 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalIn
# 933 "data/maps/NewBarkTown/scripts.pory"

# 934 "data/maps/NewBarkTown/scripts.pory"
@ Pays off the idle line: Gold/Crystal asked to be put in the fight, so the
# 935 "data/maps/NewBarkTown/scripts.pory"
@ answer has to happen on camera or the promise is dropped. The answer is no,
# 936 "data/maps/NewBarkTown/scripts.pory"
@ for a reason that is about them and not about the plan - and then the plan
# 937 "data/maps/NewBarkTown/scripts.pory"
@ needs four, and the person who overrules the no is LUSAMINE, thirty seconds
# 938 "data/maps/NewBarkTown/scripts.pory"
@ after being told that deciding for everybody is not protection. That is the
# 939 "data/maps/NewBarkTown/scripts.pory"
@ whole point of the scene: Mom teaches her to ask, and the first thing she
# 940 "data/maps/NewBarkTown/scripts.pory"
@ does with it is believe in somebody else's kid.
# 941 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal sit at (21,13), diagonally below-right of the player at
# 942 "data/maps/NewBarkTown/scripts.pory"
@ (20,12). There is no cardinal direction that points at the player, so they
# 943 "data/maps/NewBarkTown/scripts.pory"
@ turn WEST - onto the player's column - which reads as turning to them.
# 944 "data/maps/NewBarkTown/scripts.pory"
@ Nobody is at (20,13), so nothing is hidden behind the text box.
# 945 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalIn::
# 946 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_WEST
# 947 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalAsks, MSGBOX_DEFAULT
# 948 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 949 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalRefused, MSGBOX_DEFAULT
# 950 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 951 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineLetsHimIn, MSGBOX_DEFAULT
# 952 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 953 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 954 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, Common_Movement_ExclamationMark
# 955 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 956 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIn, MSGBOX_DEFAULT
# 957 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 958 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBChoose
# 959 "data/maps/NewBarkTown/scripts.pory"

# 960 "data/maps/NewBarkTown/scripts.pory"
@ Standard Rift Mission structure: the player picks which Ultra Beast to
# 961 "data/maps/NewBarkTown/scripts.pory"
@ fight and the companions take the rest. No cancel (ignoreBPress TRUE) - the
# 962 "data/maps/NewBarkTown/scripts.pory"
@ scene has already started, so VAR_RESULT can only be 0, 1 or 2.
# 963 "data/maps/NewBarkTown/scripts.pory"
@ maxBeforeScroll 3 so all three fit without scrolling. dynmultichoice takes
# 964 "data/maps/NewBarkTown/scripts.pory"
@ a vararg list (asm/macros/event.inc:1942), so three items need nothing new.
# 965 "data/maps/NewBarkTown/scripts.pory"
@ The pick is per attempt: after a blackout the player chooses again.
# 966 "data/maps/NewBarkTown/scripts.pory"
@
# 967 "data/maps/NewBarkTown/scripts.pory"
@ DISTRIBUTION - design section 6.4. Lusamine keeps Nihilego whenever the
# 968 "data/maps/NewBarkTown/scripts.pory"
@ player does not take it; it is the one she came for and the one she has to
# 969 "data/maps/NewBarkTown/scripts.pory"
@ answer for. This is a character decision, not convenience:
# 970 "data/maps/NewBarkTown/scripts.pory"
@   pick 0 Kartana   -> Lusamine Nihilego, Anabel Guzzlord
# 971 "data/maps/NewBarkTown/scripts.pory"
@   pick 1 Guzzlord  -> Lusamine Nihilego, Anabel Kartana
# 972 "data/maps/NewBarkTown/scripts.pory"
@   pick 2 Nihilego  -> Lusamine Guzzlord, Anabel Kartana
# 973 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal are the fourth pair of hands on whichever one the player
# 974 "data/maps/NewBarkTown/scripts.pory"
@ takes: four people, three beasts, one instant.
# 975 "data/maps/NewBarkTown/scripts.pory"
@ Each UBPicked* line SAYS which two the others take, so the table is
# 976 "data/maps/NewBarkTown/scripts.pory"
@ readable from inside the game and not only from this comment.
# 977 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBChoose::
# 978 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 979 "data/maps/NewBarkTown/scripts.pory"
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_Text_ChoiceKartana, NewBarkTown_Text_ChoiceGuzzlord, NewBarkTown_Text_ChoiceNihilego
# 980 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 Kartana, 1 Guzzlord, 2 Nihilego
# 981 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 982 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPickGuzzlord
# 983 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPickNihilego
# 984 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
# 985 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 986 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedKartana, MSGBOX_DEFAULT
# 987 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 988 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 989 "data/maps/NewBarkTown/scripts.pory"

# 990 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickGuzzlord::
# 991 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
# 992 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 993 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedGuzzlord, MSGBOX_DEFAULT
# 994 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 995 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 996 "data/maps/NewBarkTown/scripts.pory"

# 997 "data/maps/NewBarkTown/scripts.pory"
@ The one branch where Lusamine loses the beast she came for. ONE line, and
# 998 "data/maps/NewBarkTown/scripts.pory"
@ she takes it - design section 6.4. Do not turn this into an argument.
# 999 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickNihilego::
# 1000 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
# 1001 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1002 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedNihilego, MSGBOX_DEFAULT
# 1003 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1004 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 1005 "data/maps/NewBarkTown/scripts.pory"

# 1006 "data/maps/NewBarkTown/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 1007 "data/maps/NewBarkTown/scripts.pory"
@ battle - the other reason every mission splits the beasts up.
# 1008 "data/maps/NewBarkTown/scripts.pory"
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
# 1009 "data/maps/NewBarkTown/scripts.pory"
@ losing means a blackout and a retry. Running is not blocked either - "Run"
# 1010 "data/maps/NewBarkTown/scripts.pory"
@ in a boss is explicit forfeiting (CanPlayerForfeitBattle, src/battle_main.c)
# 1011 "data/maps/NewBarkTown/scripts.pory"
@ and becomes B_OUTCOME_FORFEITED, which counts as a loss.
# 1012 "data/maps/NewBarkTown/scripts.pory"
@
# 1013 "data/maps/NewBarkTown/scripts.pory"
@ NOT a skeleton: the numbers below are the target. Fourth step of the ladder
# 1014 "data/maps/NewBarkTown/scripts.pory"
@ after Blackthorn (2 bars / Lv70 / x110), Mahogany (4 / Lv80 / x130) and
# 1015 "data/maps/NewBarkTown/scripts.pory"
@ Cherrygrove (4 / Lv85 / x140). The bars have been at MAX_BOSS_HEALTH_BARS
# 1016 "data/maps/NewBarkTown/scripts.pory"
@ since Mission 2, so the step up here is level, multiplier and a two-axis
# 1017 "data/maps/NewBarkTown/scripts.pory"
@ moveset plus a held item.
# 1018 "data/maps/NewBarkTown/scripts.pory"
@ CAVEAT (design section 6): x140 has never actually been played. If the
# 1019 "data/maps/NewBarkTown/scripts.pory"
@ Mission 3 playtest says x140 is already a wall, THIS number inherits the
# 1020 "data/maps/NewBarkTown/scripts.pory"
@ correction instead of going up. Turn the screws in this order, one at a
# 1021 "data/maps/NewBarkTown/scripts.pory"
@ time:
# 1022 "data/maps/NewBarkTown/scripts.pory"
@   1. drop the held item from the boss that gets complained about
# 1023 "data/maps/NewBarkTown/scripts.pory"
@   2. multiplier 150 -> 145 -> 140
# 1024 "data/maps/NewBarkTown/scripts.pory"
@   3. swap the setup/control move for a fourth attacking move
# 1025 "data/maps/NewBarkTown/scripts.pory"
@   4. level 90 -> 85
# 1026 "data/maps/NewBarkTown/scripts.pory"
@ The bars are at the ceiling and are not a screw.
# 1027 "data/maps/NewBarkTown/scripts.pory"
@
# 1028 "data/maps/NewBarkTown/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 1029 "data/maps/NewBarkTown/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 1030 "data/maps/NewBarkTown/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between, so no
# 1031 "data/maps/NewBarkTown/scripts.pory"
@ clearbossbattle is needed.
# 1032 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBattle::
# 1033 "data/maps/NewBarkTown/scripts.pory"
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
# 1034 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBSetupGuzzlord
# 1035 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBSetupNihilego
# 1036 "data/maps/NewBarkTown/scripts.pory"
	@ Kartana - the one that CLIMBS. Paper defenses, Swords Dance, a pure
# 1037 "data/maps/NewBarkTown/scripts.pory"
	@ damage item: it either snowballs or it dies.
# 1038 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1039 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 1040 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1041 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_KARTANA, 90, ITEM_MUSCLE_BAND
# 1042 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_SACRED_SWORD, MOVE_SMART_STRIKE
# 1043 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 1044 "data/maps/NewBarkTown/scripts.pory"

# 1045 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord - the one that ENDURES. Absurd HP, Leftovers and Toxic: attrition.
# 1046 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupGuzzlord::
# 1047 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1048 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 1049 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1050 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_GUZZLORD, 90, ITEM_LEFTOVERS
# 1051 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_TOXIC, MOVE_CRUNCH, MOVE_HEAVY_SLAM, MOVE_DRAGON_TAIL
# 1052 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 1053 "data/maps/NewBarkTown/scripts.pory"

# 1054 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego - the one that INTERFERES. Acid Spray shreds the player's Sp.Def,
# 1055 "data/maps/NewBarkTown/scripts.pory"
@ Toxic stacks on top, and Black Sludge heals it for being Poison.
# 1056 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupNihilego::
# 1057 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 1058 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 1059 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1060 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_NIHILEGO, 90, ITEM_BLACK_SLUDGE
# 1061 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_ACID_SPRAY, MOVE_TOXIC, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE
# 1062 "data/maps/NewBarkTown/scripts.pory"

# 1063 "data/maps/NewBarkTown/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the
# 1064 "data/maps/NewBarkTown/scripts.pory"
@ player out and hands them back HEALED at (20,12) (DoWhiteOut calls
# 1065 "data/maps/NewBarkTown/scripts.pory"
@ HealPlayerParty itself, src/overworld.c:384; it does not need a Center
# 1066 "data/maps/NewBarkTown/scripts.pory"
@ counter, and New Bark has no Center at all). CAUGHT and RAN are unreachable
# 1067 "data/maps/NewBarkTown/scripts.pory"
@ (ball blocked; Run becomes FORFEITED in a boss) but are handled anyway:
# 1068 "data/maps/NewBarkTown/scripts.pory"
@ anything that is not WON restarts the scene, and nothing wins it by default.
# 1069 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBStartBattle::
# 1070 "data/maps/NewBarkTown/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 1071 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1072 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 1073 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 1074 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, NewBarkTown_EventScript_UBResolved
# 1075 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUnresolved
# 1076 "data/maps/NewBarkTown/scripts.pory"

# 1077 "data/maps/NewBarkTown/scripts.pory"
@ Nothing was recorded as done: the event flag is still set, so reloading the
# 1078 "data/maps/NewBarkTown/scripts.pory"
@ map puts the cast back on its map.json tiles with the beasts hidden again,
# 1079 "data/maps/NewBarkTown/scripts.pory"
@ and talking to Looker restarts the whole scene - the pick included. The warp
# 1080 "data/maps/NewBarkTown/scripts.pory"
@ also puts Elm and Lusamine back on their original template coordinates,
# 1081 "data/maps/NewBarkTown/scripts.pory"
@ because LoadMapFromWarp re-reads the templates, and it undoes every step of
# 1082 "data/maps/NewBarkTown/scripts.pory"
@ choreography above, because those only live in the loaded map.
# 1083 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUnresolved::
# 1084 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBGotAway, MSGBOX_DEFAULT
# 1085 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1086 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1087 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 1088 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1089 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1090 "data/maps/NewBarkTown/scripts.pory"
	end
# 1091 "data/maps/NewBarkTown/scripts.pory"

# 1092 "data/maps/NewBarkTown/scripts.pory"
@ The plan worked. Lusamine's fight, Anabel's and Gold/Crystal's are
# 1093 "data/maps/NewBarkTown/scripts.pory"
@ narrative: they resolve with the player's win, and the lines change with
# 1094 "data/maps/NewBarkTown/scripts.pory"
@ the pick so the four-way split is legible from inside the game.
# 1095 "data/maps/NewBarkTown/scripts.pory"
@ THE THREE BEASTS ARE NOT REMOVED HERE. They are down, not gone, and they
# 1096 "data/maps/NewBarkTown/scripts.pory"
@ have to still be standing on the road for what comes to collect them.
# 1097 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBResolved::
# 1098 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAfterGuzzlord
# 1099 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBAfterNihilego
# 1100 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterKartana, MSGBOX_DEFAULT
# 1101 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBNecrozmaArrives
# 1102 "data/maps/NewBarkTown/scripts.pory"

# 1103 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterGuzzlord::
# 1104 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterGuzzlord, MSGBOX_DEFAULT
# 1105 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBNecrozmaArrives
# 1106 "data/maps/NewBarkTown/scripts.pory"

# 1107 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterNihilego::
# 1108 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterNihilego, MSGBOX_DEFAULT
# 1109 "data/maps/NewBarkTown/scripts.pory"

# 1110 "data/maps/NewBarkTown/scripts.pory"
@ THE CONSEQUENCE. Same entrance the creature has used in all three previous
# 1111 "data/maps/NewBarkTown/scripts.pory"
@ missions - shake, white flash, object - but this time it walks out onto the
# 1112 "data/maps/NewBarkTown/scripts.pory"
@ road itself, at (16,12), one tile west of Lusamine, in the middle of the
# 1113 "data/maps/NewBarkTown/scripts.pory"
@ street it has been opening for four missions.
# 1114 "data/maps/NewBarkTown/scripts.pory"
@ Its flag is FLAG_TEMP_5, its own, so nothing else's removeobject can touch
# 1115 "data/maps/NewBarkTown/scripts.pory"
@ it and so the ON_TRANSITION setflag hides it again on any reload.
# 1116 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNecrozmaArrives::
# 1117 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1118 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1119 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1120 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_5
# 1121 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NECROZMA
# 1122 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1123 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1124 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1125 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
# 1126 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1127 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalFights
# 1128 "data/maps/NewBarkTown/scripts.pory"

# 1129 "data/maps/NewBarkTown/scripts.pory"
@ The kid goes at it. Nobody told them to, and this time nobody gets to tell
# 1130 "data/maps/NewBarkTown/scripts.pory"
@ them not to - they were let in thirty seconds ago and this is what being
# 1131 "data/maps/NewBarkTown/scripts.pory"
@ let in looks like to somebody who has spent the whole game feeling like
# 1132 "data/maps/NewBarkTown/scripts.pory"
@ the spare part.
# 1133 "data/maps/NewBarkTown/scripts.pory"
@ Azumarill (19,14) -> (18,14) -> (17,14) -> (16,14), two tiles south of the
# 1134 "data/maps/NewBarkTown/scripts.pory"
@ creature, faces north, hits it twice. Then it is thrown back to (18,14),
# 1135 "data/maps/NewBarkTown/scripts.pory"
@ still facing the thing, because it does not turn around.
# 1136 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalFights::
# 1137 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalCharges, MSGBOX_DEFAULT
# 1138 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1139 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillCharge
# 1140 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1141 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_AZUMARILL, CRY_MODE_ENCOUNTER
# 1142 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_StrikeUp
# 1143 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1144 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1145 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBFlash
# 1146 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillThrown
# 1147 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
# 1148 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1149 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalRepelled, MSGBOX_DEFAULT
# 1150 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1151 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAbsorb
# 1152 "data/maps/NewBarkTown/scripts.pory"

# 1153 "data/maps/NewBarkTown/scripts.pory"
@ It eats them. Same pattern as Missions 1, 2 and 3 - pulse, the beasts
# 1154 "data/maps/NewBarkTown/scripts.pory"
@ dragged backwards toward it, flash, removeobject - except that this time
# 1155 "data/maps/NewBarkTown/scripts.pory"
@ there are three, and this time somebody on the road does the arithmetic
# 1156 "data/maps/NewBarkTown/scripts.pory"
@ out loud afterwards.
# 1157 "data/maps/NewBarkTown/scripts.pory"
@ Drag paths, all measured: Kartana (17,10) -> (16,10) -> (16,11), which puts
# 1158 "data/maps/NewBarkTown/scripts.pory"
@ it directly north of the creature; Nihilego (19,13) -> (18,13) -> (17,13);
# 1159 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord (25,15) -> (24,15) -> (23,15). Every tile walkable, every path
# 1160 "data/maps/NewBarkTown/scripts.pory"
@ pointed at (16,12), and none of the three crosses another.
# 1161 "data/maps/NewBarkTown/scripts.pory"
@ Their flag is FLAG_TEMP_2, shared, and that is fine: all three go at once.
# 1162 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAbsorb::
# 1163 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_NecrozmaPulse
# 1164 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
# 1165 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1166 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1167 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_KartanaPulledIn
# 1168 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_UBPulledInWest
# 1169 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_UBPulledInWest
# 1170 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 1171 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 1172 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 1173 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1174 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1175 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_KARTANA
# 1176 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_GUZZLORD
# 1177 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NIHILEGO
# 1178 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1179 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1180 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1181 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAbsorbed, MSGBOX_DEFAULT
# 1182 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1183 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUltra
# 1184 "data/maps/NewBarkTown/scripts.pory"

# 1185 "data/maps/NewBarkTown/scripts.pory"
@ What it becomes. The creature is removed and the other object is added on
# 1186 "data/maps/NewBarkTown/scripts.pory"
@ the SAME tile (16,12) under one flash - the two are never spawned at the
# 1187 "data/maps/NewBarkTown/scripts.pory"
@ same time, which is why the peak object count of this scene is 13 and not
# 1188 "data/maps/NewBarkTown/scripts.pory"
@ 14, and why each of them needs its own FLAG_TEMP.
# 1189 "data/maps/NewBarkTown/scripts.pory"
@ Then the four of them do exactly what worked ten seconds ago - the same
# 1190 "data/maps/NewBarkTown/scripts.pory"
@ instant, the same plan - and it does not matter at all. That is the whole
# 1191 "data/maps/NewBarkTown/scripts.pory"
@ point: the counter that beat the beasts is nothing to the thing that was
# 1192 "data/maps/NewBarkTown/scripts.pory"
@ collecting them.
# 1193 "data/maps/NewBarkTown/scripts.pory"
@ All four face west at (16,12): Lusamine (17,12), the player (20,12),
# 1194 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal (21,13), Anabel (22,12).
# 1195 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltra::
# 1196 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1197 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1198 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NECROZMA
# 1199 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_6
# 1200 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1201 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1202 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
# 1203 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1204 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraRises, MSGBOX_DEFAULT
# 1205 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1206 "data/maps/NewBarkTown/scripts.pory"
	@ Four at once, the same way they broke the three.
# 1207 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_StrikeWest
# 1208 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_StrikeWest
# 1209 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_RIVAL, NewBarkTown_Movement_StrikeWest
# 1210 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_StrikeWest
# 1211 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 1212 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ANABEL
# 1213 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_RIVAL
# 1214 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1215 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFlare
# 1216 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1217 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1218 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1219 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 3   @ vertical pan
# 1220 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 2   @ horizontal pan
# 1221 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 48  @ num shakes
# 1222 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 3   @ shake delay
# 1223 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 1224 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1225 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraBreaksThem, MSGBOX_DEFAULT
# 1226 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1227 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBUltraSensesCosmog
# 1228 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUltraLeaves
# 1229 "data/maps/NewBarkTown/scripts.pory"

# 1230 "data/maps/NewBarkTown/scripts.pory"
@ OPTIONAL, STATELESS reaction to the Cosmog family in the party - design
# 1231 "data/maps/NewBarkTown/scripts.pory"
@ section 4.11, same shape as Mission 3's. Checked HERE and not before the
# 1232 "data/maps/NewBarkTown/scripts.pory"
@ battle on purpose: the battle can evolve the Pokemon. The answer is kept
# 1233 "data/maps/NewBarkTown/scripts.pory"
@ in VAR_TEMP_4 and re-read by the closing conversation, so Lusamine's last
# 1234 "data/maps/NewBarkTown/scripts.pory"
@ box lines up with what actually happened.
# 1235 "data/maps/NewBarkTown/scripts.pory"
@ Without the Pokemon nothing is missing from the scene and nothing is spent:
# 1236 "data/maps/NewBarkTown/scripts.pory"
@ no flag, no persistent var.
# 1237 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltraSensesCosmog::
# 1238 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 1239 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_4, VAR_RESULT
# 1240 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, NewBarkTown_EventScript_UBCosmogEnd
# 1241 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1242 "data/maps/NewBarkTown/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
# 1243 "data/maps/NewBarkTown/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1244 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFlare
# 1245 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1246 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_NORMAL
# 1247 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 1248 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, NewBarkTown_EventScript_UBCosmogLegend
# 1249 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, NewBarkTown_EventScript_UBCosmogLegend
# 1250 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraSensesCosmog, MSGBOX_DEFAULT
# 1251 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1252 "data/maps/NewBarkTown/scripts.pory"
	return
# 1253 "data/maps/NewBarkTown/scripts.pory"

# 1254 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBCosmogLegend::
# 1255 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraSensesLegend, MSGBOX_DEFAULT
# 1256 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1257 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBCosmogEnd::
# 1258 "data/maps/NewBarkTown/scripts.pory"
	return
# 1259 "data/maps/NewBarkTown/scripts.pory"

# 1260 "data/maps/NewBarkTown/scripts.pory"
@ It leaves the way it arrived, and nobody stops it. Its flag is FLAG_TEMP_6,
# 1261 "data/maps/NewBarkTown/scripts.pory"
@ its own, so the removeobject touches nothing else.
# 1262 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUltraLeaves::
# 1263 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBShake
# 1264 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1265 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
# 1266 "data/maps/NewBarkTown/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1267 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBUltraGone, MSGBOX_DEFAULT
# 1268 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1269 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAftermath
# 1270 "data/maps/NewBarkTown/scripts.pory"

# 1271 "data/maps/NewBarkTown/scripts.pory"
@ The town stands and the mission is lost, and the order of the boxes is the
# 1272 "data/maps/NewBarkTown/scripts.pory"
@ argument: the people first (Looker, always), then the cost, then what it
# 1273 "data/maps/NewBarkTown/scripts.pory"
@ actually was, then the three who have to live in this town, then the
# 1274 "data/maps/NewBarkTown/scripts.pory"
@ promise that is the only thing anybody still has, then the hook.
# 1275 "data/maps/NewBarkTown/scripts.pory"
@ Nobody walks: everyone is already on the line and nobody is at (20,13), so
# 1276 "data/maps/NewBarkTown/scripts.pory"
@ the text box hides no one. Azumarill is at (18,14) and Lusamine at (17,12),
# 1277 "data/maps/NewBarkTown/scripts.pory"
@ where the fight left them, which is the picture the scene wants.
# 1278 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermath::
# 1279 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathHurt, MSGBOX_DEFAULT
# 1280 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1281 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmCost, MSGBOX_DEFAULT
# 1282 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1283 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBWhatItWas, MSGBOX_DEFAULT
# 1284 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1285 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineLost, MSGBOX_DEFAULT
# 1286 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1287 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_WEST     @ onto the player's column
# 1288 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRival, MSGBOX_DEFAULT
# 1289 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1290 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST       @ back to facing her child
# 1291 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMom, MSGBOX_DEFAULT
# 1292 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1293 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelPromise, MSGBOX_DEFAULT
# 1294 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1295 "data/maps/NewBarkTown/scripts.pory"
	call NewBarkTown_EventScript_UBAftermathCosmog
# 1296 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBHook, MSGBOX_DEFAULT
# 1297 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1298 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1299 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_NEWBARK   @ invariant: flag and var together
# 1300 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 10
# 1301 "data/maps/NewBarkTown/scripts.pory"
	@ Reload in place under the fade. The seven residents come back, the lamps
# 1302 "data/maps/NewBarkTown/scripts.pory"
	@ go back to depending on the clock alone, the cast disappears, Elm and
# 1303 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine return to their template tiles, and the follower comes back
# 1304 "data/maps/NewBarkTown/scripts.pory"
	@ (undoing the hidefollower). Without this the whole town would pop back
# 1305 "data/maps/NewBarkTown/scripts.pory"
	@ in piece by piece as the camera moved.
# 1306 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 1307 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1308 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1309 "data/maps/NewBarkTown/scripts.pory"
	end
# 1310 "data/maps/NewBarkTown/scripts.pory"

# 1311 "data/maps/NewBarkTown/scripts.pory"
@ Re-reads what UBUltraSensesCosmog sampled. Design section 6.4: Lusamine is
# 1312 "data/maps/NewBarkTown/scripts.pory"
@ the only living person who knows what that light looks like from the other
# 1313 "data/maps/NewBarkTown/scripts.pory"
@ side, because she used one. She says it without being asked, and she says
# 1314 "data/maps/NewBarkTown/scripts.pory"
@ the other half of it too - that none of this is the player's doing.
# 1315 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermathCosmog::
# 1316 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, NewBarkTown_EventScript_UBAftermathCosmogEnd
# 1317 "data/maps/NewBarkTown/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1318 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAftermathCosmog, MSGBOX_DEFAULT
# 1319 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 1320 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermathCosmogEnd::
# 1321 "data/maps/NewBarkTown/scripts.pory"
	return
# 1322 "data/maps/NewBarkTown/scripts.pory"

# 1323 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepLeftFaceLeft:
# 1324 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1325 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 1326 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1327 "data/maps/NewBarkTown/scripts.pory"

# 1328 "data/maps/NewBarkTown/scripts.pory"
@ One tile east, slowly, and all three do it in the same frame.
# 1329 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UBDrift:
# 1330 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_right
# 1331 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1332 "data/maps/NewBarkTown/scripts.pory"

# 1333 "data/maps/NewBarkTown/scripts.pory"
@ (16,13) -> (19,13), the last three tiles between it and the player.
# 1334 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_NihilegoLunge:
# 1335 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1336 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1337 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1338 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1339 "data/maps/NewBarkTown/scripts.pory"

# 1340 "data/maps/NewBarkTown/scripts.pory"
@ (22,13) -> (22,14) -> (21,14) -> (20,14) -> (19,14), facing north. Around
# 1341 "data/maps/NewBarkTown/scripts.pory"
@ the outside, never through (20,13).
# 1342 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillCutOff:
# 1343 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 1344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1345 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1346 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1347 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1348 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1349 "data/maps/NewBarkTown/scripts.pory"

# 1350 "data/maps/NewBarkTown/scripts.pory"
@ (19,14) -> (16,14), two tiles south of the creature, facing it.
# 1351 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillCharge:
# 1352 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1353 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1354 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 1355 "data/maps/NewBarkTown/scripts.pory"
	face_up
# 1356 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1357 "data/maps/NewBarkTown/scripts.pory"

# 1358 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StrikeUp:
# 1359 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_up
# 1360 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_up
# 1361 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1362 "data/maps/NewBarkTown/scripts.pory"

# 1363 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StrikeWest:
# 1364 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 1365 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_left
# 1366 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1367 "data/maps/NewBarkTown/scripts.pory"

# 1368 "data/maps/NewBarkTown/scripts.pory"
@ (16,14) -> (18,14) without turning around.
# 1369 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_AzumarillThrown:
# 1370 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 1371 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1372 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 1373 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 1374 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1375 "data/maps/NewBarkTown/scripts.pory"

# 1376 "data/maps/NewBarkTown/scripts.pory"
@ Dragged backwards, two tiles, still facing away from what is pulling.
# 1377 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UBPulledInWest:
# 1378 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 1379 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_left
# 1380 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_left
# 1381 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 1382 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1383 "data/maps/NewBarkTown/scripts.pory"

# 1384 "data/maps/NewBarkTown/scripts.pory"
@ Kartana comes down the side of the lab: (17,10) -> (16,10) -> (16,11).
# 1385 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_KartanaPulledIn:
# 1386 "data/maps/NewBarkTown/scripts.pory"
	lock_facing_direction
# 1387 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_left
# 1388 "data/maps/NewBarkTown/scripts.pory"
	walk_slow_down
# 1389 "data/maps/NewBarkTown/scripts.pory"
	unlock_facing_direction
# 1390 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1391 "data/maps/NewBarkTown/scripts.pory"

# 1392 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_NecrozmaPulse:
# 1393 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1394 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1395 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1396 "data/maps/NewBarkTown/scripts.pory"
	step_end
# 1397 "data/maps/NewBarkTown/scripts.pory"

# 1398 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_UltraFlare:
# 1399 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1400 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1401 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1402 "data/maps/NewBarkTown/scripts.pory"
	walk_in_place_fast_right
# 1403 "data/maps/NewBarkTown/scripts.pory"
	step_end

# 1406 "data/maps/NewBarkTown/scripts.pory"

# 1407 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 1408 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 dialogue.
# 1409 "data/maps/NewBarkTown/scripts.pory"
@ Voices: design section 3.1. Looker theatrical, formal in a personal way,
# 1410 "data/maps/NewBarkTown/scripts.pory"
@ and asks about the people before the report. Anabel precise, separating
# 1411 "data/maps/NewBarkTown/scripts.pory"
@ observation from hypothesis. Lusamine elaborate, used to deciding, learning
# 1412 "data/maps/NewBarkTown/scripts.pory"
@ to ask. Elm humble and specific. Mom plain, short, no speeches.
# 1413 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal: NO speaker plaque anywhere, ever - the two texts have to
# 1414 "data/maps/NewBarkTown/scripts.pory"
@ serve both of them. When a rival line follows a named line inside the SAME
# 1415 "data/maps/NewBarkTown/scripts.pory"
@ box it opens with {SPEAKER NAME_NONE}, or it would inherit the plaque above
# 1416 "data/maps/NewBarkTown/scripts.pory"
@ it and put somebody else's name over the kid's words.
# 1417 "data/maps/NewBarkTown/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 1418 "data/maps/NewBarkTown/scripts.pory"
@ UBHook is the hook into the Olivine reunion (design section 7) - it is what
# 1419 "data/maps/NewBarkTown/scripts.pory"
@ the next document picks up.
# 1420 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 1421 "data/maps/NewBarkTown/scripts.pory"

# 1422 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineIdle:
# 1423 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}You are taller than\n"
# 1424 "data/maps/NewBarkTown/scripts.pory"
	.string "the photographs.\p"
# 1425 "data/maps/NewBarkTown/scripts.pory"
	.string "…Forgive me. I have practiced\n"
# 1426 "data/maps/NewBarkTown/scripts.pory"
	.string "this, and I am still doing it\l"
# 1427 "data/maps/NewBarkTown/scripts.pory"
	.string "badly.\p"
# 1428 "data/maps/NewBarkTown/scripts.pory"
	.string "Lillie writes about you.\p"
# 1429 "data/maps/NewBarkTown/scripts.pory"
	.string "Gladion does not write, but he\n"
# 1430 "data/maps/NewBarkTown/scripts.pory"
	.string "mentions you, which from him is\l"
# 1431 "data/maps/NewBarkTown/scripts.pory"
	.string "the same thing.\p"
# 1432 "data/maps/NewBarkTown/scripts.pory"
	.string "Nobody sent for me. I read the\n"
# 1433 "data/maps/NewBarkTown/scripts.pory"
	.string "same numbers they did and I got\l"
# 1434 "data/maps/NewBarkTown/scripts.pory"
	.string "in a boat.\p"
# 1435 "data/maps/NewBarkTown/scripts.pory"
	.string "We will talk properly when this\n"
# 1436 "data/maps/NewBarkTown/scripts.pory"
	.string "is over.\p"
# 1437 "data/maps/NewBarkTown/scripts.pory"
	.string "If I am still someone you want\n"
# 1438 "data/maps/NewBarkTown/scripts.pory"
	.string "to talk to.$"
# 1439 "data/maps/NewBarkTown/scripts.pory"

# 1440 "data/maps/NewBarkTown/scripts.pory"
@ Optional. Design section 6.4: she is the only living person who knows what
# 1441 "data/maps/NewBarkTown/scripts.pory"
@ that light looks like from the other side. And the rule that cannot be
# 1442 "data/maps/NewBarkTown/scripts.pory"
@ broken - she says out loud that none of it is the player's doing.
# 1443 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineIdleCosmog:
# 1444 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…Oh.\p"
# 1445 "data/maps/NewBarkTown/scripts.pory"
	.string "Oh, you brought it with you.\p"
# 1446 "data/maps/NewBarkTown/scripts.pory"
	.string "{STR_VAR_1} is standing on a\n"
# 1447 "data/maps/NewBarkTown/scripts.pory"
	.string "road with three tears over it,\l"
# 1448 "data/maps/NewBarkTown/scripts.pory"
	.string "and it is not frightened.\p"
# 1449 "data/maps/NewBarkTown/scripts.pory"
	.string "I knew one of those, once.\p"
# 1450 "data/maps/NewBarkTown/scripts.pory"
	.string "I did not deserve it, and I\n"
# 1451 "data/maps/NewBarkTown/scripts.pory"
	.string "used it, and I would like you\l"
# 1452 "data/maps/NewBarkTown/scripts.pory"
	.string "to hear the next part from me\l"
# 1453 "data/maps/NewBarkTown/scripts.pory"
	.string "before anyone else says it.\p"
# 1454 "data/maps/NewBarkTown/scripts.pory"
	.string "They shine. Things on the other\n"
# 1455 "data/maps/NewBarkTown/scripts.pory"
	.string "side can see that.\p"
# 1456 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not your fault and it\n"
# 1457 "data/maps/NewBarkTown/scripts.pory"
	.string "never was.\p"
# 1458 "data/maps/NewBarkTown/scripts.pory"
	.string "It is why I came.$"
# 1459 "data/maps/NewBarkTown/scripts.pory"

# 1460 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmIdle:
# 1461 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Six weeks.\p"
# 1462 "data/maps/NewBarkTown/scripts.pory"
	.string "Six weeks of the same reading,\n"
# 1463 "data/maps/NewBarkTown/scripts.pory"
	.string "and every time I wrote “check\l"
# 1464 "data/maps/NewBarkTown/scripts.pory"
	.string "the sensor” in the margin.\p"
# 1465 "data/maps/NewBarkTown/scripts.pory"
	.string "Then Cherrygrove was in the\n"
# 1466 "data/maps/NewBarkTown/scripts.pory"
	.string "morning paper.\p"
# 1467 "data/maps/NewBarkTown/scripts.pory"
	.string "So I posted the whole log to\n"
# 1468 "data/maps/NewBarkTown/scripts.pory"
	.string "the one man in the world who\l"
# 1469 "data/maps/NewBarkTown/scripts.pory"
	.string "would not laugh at it, and he\l"
# 1470 "data/maps/NewBarkTown/scripts.pory"
	.string "telephoned the police before he\l"
# 1471 "data/maps/NewBarkTown/scripts.pory"
	.string "finished reading it.\p"
# 1472 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor Kukui works fast when\n"
# 1473 "data/maps/NewBarkTown/scripts.pory"
	.string "he is frightened.\p"
# 1474 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone who would come is in\n"
# 1475 "data/maps/NewBarkTown/scripts.pory"
	.string "the lab. It's the strongest\l"
# 1476 "data/maps/NewBarkTown/scripts.pory"
	.string "building in town, which is not\l"
# 1477 "data/maps/NewBarkTown/scripts.pory"
	.string "saying much.$"
# 1478 "data/maps/NewBarkTown/scripts.pory"

# 1479 "data/maps/NewBarkTown/scripts.pory"
@ Optional. Elm is the one who identified the egg in the first place, so he
# 1480 "data/maps/NewBarkTown/scripts.pory"
@ is allowed to be delighted for exactly two boxes and then remember where
# 1481 "data/maps/NewBarkTown/scripts.pory"
@ he is standing.
# 1482 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmIdleCosmog:
# 1483 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}And there it is.\p"
# 1484 "data/maps/NewBarkTown/scripts.pory"
	.string "I had a {STR_VAR_1} on my table\n"
# 1485 "data/maps/NewBarkTown/scripts.pory"
	.string "in a shell, and now it is on my\l"
# 1486 "data/maps/NewBarkTown/scripts.pory"
	.string "street, and I still cannot tell\l"
# 1487 "data/maps/NewBarkTown/scripts.pory"
	.string "you what it is.\p"
# 1488 "data/maps/NewBarkTown/scripts.pory"
	.string "…I'm going to stop looking at\n"
# 1489 "data/maps/NewBarkTown/scripts.pory"
	.string "it now.\p"
# 1490 "data/maps/NewBarkTown/scripts.pory"
	.string "Every instrument in my window\n"
# 1491 "data/maps/NewBarkTown/scripts.pory"
	.string "leans when it walks past.$"
# 1492 "data/maps/NewBarkTown/scripts.pory"

# 1493 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomIdle:
# 1494 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}I'm not going into the\n"
# 1495 "data/maps/NewBarkTown/scripts.pory"
	.string "lab, {PLAYER}.\p"
# 1496 "data/maps/NewBarkTown/scripts.pory"
	.string "Don't ask me again.\p"
# 1497 "data/maps/NewBarkTown/scripts.pory"
	.string "I've been watching that road\n"
# 1498 "data/maps/NewBarkTown/scripts.pory"
	.string "for two years.\p"
# 1499 "data/maps/NewBarkTown/scripts.pory"
	.string "I know how to watch a road.$"
# 1500 "data/maps/NewBarkTown/scripts.pory"

# 1501 "data/maps/NewBarkTown/scripts.pory"
@ No name: this text serves both Gold and Crystal.
# 1502 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIdle:
# 1503 "data/maps/NewBarkTown/scripts.pory"
	.string "Every house on this street,\n"
# 1504 "data/maps/NewBarkTown/scripts.pory"
	.string "twice.\p"
# 1505 "data/maps/NewBarkTown/scripts.pory"
	.string "The Hanlons wouldn't open the\n"
# 1506 "data/maps/NewBarkTown/scripts.pory"
	.string "door until I said your name.\p"
# 1507 "data/maps/NewBarkTown/scripts.pory"
	.string "Which is the story of the last\n"
# 1508 "data/maps/NewBarkTown/scripts.pory"
	.string "two years, honestly.\p"
# 1509 "data/maps/NewBarkTown/scripts.pory"
	.string "Hey - when it starts, put me\n"
# 1510 "data/maps/NewBarkTown/scripts.pory"
	.string "in.\p"
# 1511 "data/maps/NewBarkTown/scripts.pory"
	.string "I've got a full team. I've had\n"
# 1512 "data/maps/NewBarkTown/scripts.pory"
	.string "a full team for a year, and I\l"
# 1513 "data/maps/NewBarkTown/scripts.pory"
	.string "have never once been in the\l"
# 1514 "data/maps/NewBarkTown/scripts.pory"
	.string "room where it mattered.$"
# 1515 "data/maps/NewBarkTown/scripts.pory"

# 1516 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelIdle:
# 1517 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Three signatures, and\n"
# 1518 "data/maps/NewBarkTown/scripts.pory"
	.string "they are breathing together.\p"
# 1519 "data/maps/NewBarkTown/scripts.pory"
	.string "In, and out.\p"
# 1520 "data/maps/NewBarkTown/scripts.pory"
	.string "I told you in Olivine what that\n"
# 1521 "data/maps/NewBarkTown/scripts.pory"
	.string "does to me. I won't say it\l"
# 1522 "data/maps/NewBarkTown/scripts.pory"
	.string "twice on an open road.\p"
# 1523 "data/maps/NewBarkTown/scripts.pory"
	.string "Stay on this street.\p"
# 1524 "data/maps/NewBarkTown/scripts.pory"
	.string "If I tell you to move, move\n"
# 1525 "data/maps/NewBarkTown/scripts.pory"
	.string "first and ask me after.$"
# 1526 "data/maps/NewBarkTown/scripts.pory"

# 1527 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLookerGreet:
# 1528 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Right on your\n"
# 1529 "data/maps/NewBarkTown/scripts.pory"
	.string "own doorstep.\p"
# 1530 "data/maps/NewBarkTown/scripts.pory"
	.string "I have worked a great many\n"
# 1531 "data/maps/NewBarkTown/scripts.pory"
	.string "streets, and I have never liked\l"
# 1532 "data/maps/NewBarkTown/scripts.pory"
	.string "one less than this.$"
# 1533 "data/maps/NewBarkTown/scripts.pory"

# 1534 "data/maps/NewBarkTown/scripts.pory"
@ Elm is still at (11,10) and off camera at this point, so Anabel reads his
# 1535 "data/maps/NewBarkTown/scripts.pory"
@ log out for him. His own voice arrives with his object, in UBTheyArrive.
# 1536 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBClockRelay:
# 1537 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The Professor called it\n"
# 1538 "data/maps/NewBarkTown/scripts.pory"
	.string "in four minutes ago.\p"
# 1539 "data/maps/NewBarkTown/scripts.pory"
	.string "Three minutes, he says. Maybe\n"
# 1540 "data/maps/NewBarkTown/scripts.pory"
	.string "four - the interval has been\l"
# 1541 "data/maps/NewBarkTown/scripts.pory"
	.string "shortening all morning.\p"
# 1542 "data/maps/NewBarkTown/scripts.pory"
	.string "All three breathe together.\p"
# 1543 "data/maps/NewBarkTown/scripts.pory"
	.string "He had six weeks of that on\n"
# 1544 "data/maps/NewBarkTown/scripts.pory"
	.string "paper and called it a fault.\p"
# 1545 "data/maps/NewBarkTown/scripts.pory"
	.string "It took a stranger in Alola one\n"
# 1546 "data/maps/NewBarkTown/scripts.pory"
	.string "page to tell him it wasn't.\p"
# 1547 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}And so we are here, on\n"
# 1548 "data/maps/NewBarkTown/scripts.pory"
	.string "a road with no Pokémon Center,\l"
# 1549 "data/maps/NewBarkTown/scripts.pory"
	.string "because a man in a laboratory\l"
# 1550 "data/maps/NewBarkTown/scripts.pory"
	.string "was brave enough to be wrong in\l"
# 1551 "data/maps/NewBarkTown/scripts.pory"
	.string "writing.$"
# 1552 "data/maps/NewBarkTown/scripts.pory"

# 1553 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBReady:
# 1554 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Worse than Cherrygrove.\p"
# 1555 "data/maps/NewBarkTown/scripts.pory"
	.string "Worse than anything we have\n"
# 1556 "data/maps/NewBarkTown/scripts.pory"
	.string "sent you into.\p"
# 1557 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Are you ready?$"
# 1558 "data/maps/NewBarkTown/scripts.pory"

# 1559 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNotReady:
# 1560 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then take the time.\p"
# 1561 "data/maps/NewBarkTown/scripts.pory"
	.string "Your mother is not moving,\n"
# 1562 "data/maps/NewBarkTown/scripts.pory"
	.string "and neither am I.$"
# 1563 "data/maps/NewBarkTown/scripts.pory"

# 1564 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBTheyArrive:
# 1565 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Professor. Your log.\p"
# 1566 "data/maps/NewBarkTown/scripts.pory"
	.string "You kept six weeks of a reading\n"
# 1567 "data/maps/NewBarkTown/scripts.pory"
	.string "you were certain was wrong.\p"
# 1568 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}I kept it because I\n"
# 1569 "data/maps/NewBarkTown/scripts.pory"
	.string "thought it was wrong.\p"
# 1570 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not the same as being\n"
# 1571 "data/maps/NewBarkTown/scripts.pory"
	.string "useful.\p"
# 1572 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Today it is exactly\n"
# 1573 "data/maps/NewBarkTown/scripts.pory"
	.string "the same thing.\p"
# 1574 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Madame. Nobody told me\n"
# 1575 "data/maps/NewBarkTown/scripts.pory"
	.string "you were coming.\p"
# 1576 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Nobody told me either,\n"
# 1577 "data/maps/NewBarkTown/scripts.pory"
	.string "Inspector.$"
# 1578 "data/maps/NewBarkTown/scripts.pory"

# 1579 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAppear:
# 1580 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Three.\p"
# 1581 "data/maps/NewBarkTown/scripts.pory"
	.string "Over the laboratory, over the\n"
# 1582 "data/maps/NewBarkTown/scripts.pory"
	.string "road, over this street.\p"
# 1583 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}That's them. That's the\n"
# 1584 "data/maps/NewBarkTown/scripts.pory"
	.string "reading.\p"
# 1585 "data/maps/NewBarkTown/scripts.pory"
	.string "Six weeks of it, standing in\n"
# 1586 "data/maps/NewBarkTown/scripts.pory"
	.string "my town.$"
# 1587 "data/maps/NewBarkTown/scripts.pory"

# 1588 "data/maps/NewBarkTown/scripts.pory"
@ The synergy, shown first and named second.
# 1589 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBSynergyFirst:
# 1590 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Wait.\p"
# 1591 "data/maps/NewBarkTown/scripts.pory"
	.string "Wait, they all moved.\p"
# 1592 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Yes. Toward us. That is\n"
# 1593 "data/maps/NewBarkTown/scripts.pory"
	.string "what they do.\p"
# 1594 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}No, madame - they all\n"
# 1595 "data/maps/NewBarkTown/scripts.pory"
	.string "moved at the SAME time.\p"
# 1596 "data/maps/NewBarkTown/scripts.pory"
	.string "I have a clock. That is the\n"
# 1597 "data/maps/NewBarkTown/scripts.pory"
	.string "only thing I am good for today.$"
# 1598 "data/maps/NewBarkTown/scripts.pory"

# 1599 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBSynergyNamed:
# 1600 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}Again. Same instant.\p"
# 1601 "data/maps/NewBarkTown/scripts.pory"
	.string "There are two buildings between\n"
# 1602 "data/maps/NewBarkTown/scripts.pory"
	.string "them. They cannot see each\l"
# 1603 "data/maps/NewBarkTown/scripts.pory"
	.string "other.\p"
# 1604 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Then stop counting them\n"
# 1605 "data/maps/NewBarkTown/scripts.pory"
	.string "as three.\p"
# 1606 "data/maps/NewBarkTown/scripts.pory"
	.string "That is one thing wearing three\n"
# 1607 "data/maps/NewBarkTown/scripts.pory"
	.string "bodies, and it has been doing\l"
# 1608 "data/maps/NewBarkTown/scripts.pory"
	.string "it since Blackthorn.\p"
# 1609 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…In Alola they never\n"
# 1610 "data/maps/NewBarkTown/scripts.pory"
	.string "did that.\p"
# 1611 "data/maps/NewBarkTown/scripts.pory"
	.string "Not once. Not for me.$"
# 1612 "data/maps/NewBarkTown/scripts.pory"

# 1613 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBCutOff:
# 1614 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}MOVE!\p"
# 1615 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}Azumarill, cut it off!\n"
# 1616 "data/maps/NewBarkTown/scripts.pory"
	.string "Go around, go around!\p"
# 1617 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}…It stopped.\p"
# 1618 "data/maps/NewBarkTown/scripts.pory"
	.string "It came straight down the road\n"
# 1619 "data/maps/NewBarkTown/scripts.pory"
	.string "at a fifteen-year-old and a\l"
# 1620 "data/maps/NewBarkTown/scripts.pory"
	.string "woman who refused to go inside,\l"
# 1621 "data/maps/NewBarkTown/scripts.pory"
	.string "and a Pokémon nobody asked for\l"
# 1622 "data/maps/NewBarkTown/scripts.pory"
	.string "is what stopped it.\p"
# 1623 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}I'm still not going\n"
# 1624 "data/maps/NewBarkTown/scripts.pory"
	.string "inside.$"
# 1625 "data/maps/NewBarkTown/scripts.pory"

# 1626 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineTakesThree:
# 1627 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}It went for your child.\p"
# 1628 "data/maps/NewBarkTown/scripts.pory"
	.string "In front of you. In front of\n"
# 1629 "data/maps/NewBarkTown/scripts.pory"
	.string "me.\p"
# 1630 "data/maps/NewBarkTown/scripts.pory"
	.string "Three of them. Then I will take\n"
# 1631 "data/maps/NewBarkTown/scripts.pory"
	.string "three.\p"
# 1632 "data/maps/NewBarkTown/scripts.pory"
	.string "No - listen to me.\p"
# 1633 "data/maps/NewBarkTown/scripts.pory"
	.string "I know what they are. I know it\n"
# 1634 "data/maps/NewBarkTown/scripts.pory"
	.string "better than anyone standing on\l"
# 1635 "data/maps/NewBarkTown/scripts.pory"
	.string "this road.\p"
# 1636 "data/maps/NewBarkTown/scripts.pory"
	.string "Nobody else here has to go near\n"
# 1637 "data/maps/NewBarkTown/scripts.pory"
	.string "them.$"
# 1638 "data/maps/NewBarkTown/scripts.pory"

# 1639 "data/maps/NewBarkTown/scripts.pory"
@ The plotline the author asked to keep: Mom does not out-argue her. She
# 1640 "data/maps/NewBarkTown/scripts.pory"
@ tells her what believing in somebody looks like from the inside, and she
# 1641 "data/maps/NewBarkTown/scripts.pory"
@ has exactly one example.
# 1642 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomStopsHer:
# 1643 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Ma'am.\p"
# 1644 "data/maps/NewBarkTown/scripts.pory"
	.string "My child is standing right\n"
# 1645 "data/maps/NewBarkTown/scripts.pory"
	.string "there, and I'm not going inside\l"
# 1646 "data/maps/NewBarkTown/scripts.pory"
	.string "either, so I won't lecture you.\p"
# 1647 "data/maps/NewBarkTown/scripts.pory"
	.string "But you're not protecting\n"
# 1648 "data/maps/NewBarkTown/scripts.pory"
	.string "anyone.\p"
# 1649 "data/maps/NewBarkTown/scripts.pory"
	.string "You're making sure that if it\n"
# 1650 "data/maps/NewBarkTown/scripts.pory"
	.string "goes wrong, it goes wrong to\l"
# 1651 "data/maps/NewBarkTown/scripts.pory"
	.string "you.\p"
# 1652 "data/maps/NewBarkTown/scripts.pory"
	.string "I know the difference. I've\n"
# 1653 "data/maps/NewBarkTown/scripts.pory"
	.string "wanted to do it too.\p"
# 1654 "data/maps/NewBarkTown/scripts.pory"
	.string "Every week, for two years.\p"
# 1655 "data/maps/NewBarkTown/scripts.pory"
	.string "And then one morning I stood at\n"
# 1656 "data/maps/NewBarkTown/scripts.pory"
	.string "that door and let a ten-year-\l"
# 1657 "data/maps/NewBarkTown/scripts.pory"
	.string "old walk to Cherrygrove alone.\p"
# 1658 "data/maps/NewBarkTown/scripts.pory"
	.string "That's the part nobody tells\n"
# 1659 "data/maps/NewBarkTown/scripts.pory"
	.string "you. Believing in somebody is\l"
# 1660 "data/maps/NewBarkTown/scripts.pory"
	.string "worse than doing it yourself.\p"
# 1661 "data/maps/NewBarkTown/scripts.pory"
	.string "It just happens to be the thing\n"
# 1662 "data/maps/NewBarkTown/scripts.pory"
	.string "that works.\p"
# 1663 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…\p"
# 1664 "data/maps/NewBarkTown/scripts.pory"
	.string "My daughter said something very\n"
# 1665 "data/maps/NewBarkTown/scripts.pory"
	.string "close to that to me, once.\p"
# 1666 "data/maps/NewBarkTown/scripts.pory"
	.string "I did not hear it either.$"
# 1667 "data/maps/NewBarkTown/scripts.pory"

# 1668 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineAsks:
# 1669 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Very well.\p"
# 1670 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I will do the thing I am\n"
# 1671 "data/maps/NewBarkTown/scripts.pory"
	.string "worst at.\p"
# 1672 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel. What do your\n"
# 1673 "data/maps/NewBarkTown/scripts.pory"
	.string "instruments give me?$"
# 1674 "data/maps/NewBarkTown/scripts.pory"

# 1675 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelBreaks:
# 1676 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They give me… they\n"
# 1677 "data/maps/NewBarkTown/scripts.pory"
	.string "give me…\p"
# 1678 "data/maps/NewBarkTown/scripts.pory"
	.string "…\p"
# 1679 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief. Chief.$"
# 1680 "data/maps/NewBarkTown/scripts.pory"

# 1681 "data/maps/NewBarkTown/scripts.pory"
@ Two boxes and she is back at work. The long version of this happened in
# 1682 "data/maps/NewBarkTown/scripts.pory"
@ Olivine, before any of it. Do not move it back here.
# 1683 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelStands:
# 1684 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'm here. Let go,\n"
# 1685 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker. I can stand.\p"
# 1686 "data/maps/NewBarkTown/scripts.pory"
	.string "Three at once is loud.\p"
# 1687 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} knows why. I'm not\n"
# 1688 "data/maps/NewBarkTown/scripts.pory"
	.string "saying it again in the middle\l"
# 1689 "data/maps/NewBarkTown/scripts.pory"
	.string "of a road.\p"
# 1690 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}You are not required\n"
# 1691 "data/maps/NewBarkTown/scripts.pory"
	.string "to.$"
# 1692 "data/maps/NewBarkTown/scripts.pory"

# 1693 "data/maps/NewBarkTown/scripts.pory"
@ The counter, and the reason the scene needs a fourth person.
# 1694 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBCounter:
# 1695 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Here is what the\n"
# 1696 "data/maps/NewBarkTown/scripts.pory"
	.string "instruments give you, madame.\p"
# 1697 "data/maps/NewBarkTown/scripts.pory"
	.string "One thing, three bodies, one\n"
# 1698 "data/maps/NewBarkTown/scripts.pory"
	.string "instant.\p"
# 1699 "data/maps/NewBarkTown/scripts.pory"
	.string "Break one and the other two\n"
# 1700 "data/maps/NewBarkTown/scripts.pory"
	.string "carry it. Break two and the\l"
# 1701 "data/maps/NewBarkTown/scripts.pory"
	.string "third one carries both.\p"
# 1702 "data/maps/NewBarkTown/scripts.pory"
	.string "They have to go down in the\n"
# 1703 "data/maps/NewBarkTown/scripts.pory"
	.string "same instant or they do not go\l"
# 1704 "data/maps/NewBarkTown/scripts.pory"
	.string "down at all.\p"
# 1705 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Then I cannot take\n"
# 1706 "data/maps/NewBarkTown/scripts.pory"
	.string "three.\p"
# 1707 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}No. You take one, I\n"
# 1708 "data/maps/NewBarkTown/scripts.pory"
	.string "take one, {PLAYER} takes one.\p"
# 1709 "data/maps/NewBarkTown/scripts.pory"
	.string "And the one {PLAYER} takes is\n"
# 1710 "data/maps/NewBarkTown/scripts.pory"
	.string "the one that has already tried\l"
# 1711 "data/maps/NewBarkTown/scripts.pory"
	.string "for them once.\p"
# 1712 "data/maps/NewBarkTown/scripts.pory"
	.string "It will not go down to one\n"
# 1713 "data/maps/NewBarkTown/scripts.pory"
	.string "trainer.$"
# 1714 "data/maps/NewBarkTown/scripts.pory"

# 1715 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1716 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalAsks:
# 1717 "data/maps/NewBarkTown/scripts.pory"
	.string "Then take me.\p"
# 1718 "data/maps/NewBarkTown/scripts.pory"
	.string "I asked first. I asked before\n"
# 1719 "data/maps/NewBarkTown/scripts.pory"
	.string "any of you got here.\p"
# 1720 "data/maps/NewBarkTown/scripts.pory"
	.string "My Azumarill is the reason that\n"
# 1721 "data/maps/NewBarkTown/scripts.pory"
	.string "thing is still ten feet away.$"
# 1722 "data/maps/NewBarkTown/scripts.pory"

# 1723 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalRefused:
# 1724 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}You are the only person\n"
# 1725 "data/maps/NewBarkTown/scripts.pory"
	.string "on this road who is not police,\l"
# 1726 "data/maps/NewBarkTown/scripts.pory"
	.string "not Aether, and not the\l"
# 1727 "data/maps/NewBarkTown/scripts.pory"
	.string "Champion.\p"
# 1728 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Forty people came back\n"
# 1729 "data/maps/NewBarkTown/scripts.pory"
	.string "out of their houses because you\l"
# 1730 "data/maps/NewBarkTown/scripts.pory"
	.string "knocked.\p"
# 1731 "data/maps/NewBarkTown/scripts.pory"
	.string "If this goes badly they will\n"
# 1732 "data/maps/NewBarkTown/scripts.pory"
	.string "need someone who knows which\l"
# 1733 "data/maps/NewBarkTown/scripts.pory"
	.string "doors are which.\p"
# 1734 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}…Right. Doors.\p"
# 1735 "data/maps/NewBarkTown/scripts.pory"
	.string "It's always doors.$"
# 1736 "data/maps/NewBarkTown/scripts.pory"

# 1737 "data/maps/NewBarkTown/scripts.pory"
@ Thirty seconds after being told that deciding for everybody is not
# 1738 "data/maps/NewBarkTown/scripts.pory"
@ protection. This is the whole argument of the scene landing.
# 1739 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineLetsHimIn:
# 1740 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}No.\p"
# 1741 "data/maps/NewBarkTown/scripts.pory"
	.string "Inspector, you are wrong, and I\n"
# 1742 "data/maps/NewBarkTown/scripts.pory"
	.string "am the last person in Johto\l"
# 1743 "data/maps/NewBarkTown/scripts.pory"
	.string "with the right to say so.\p"
# 1744 "data/maps/NewBarkTown/scripts.pory"
	.string "I have spent my life deciding\n"
# 1745 "data/maps/NewBarkTown/scripts.pory"
	.string "who was ready.\p"
# 1746 "data/maps/NewBarkTown/scripts.pory"
	.string "I was told, four minutes ago,\n"
# 1747 "data/maps/NewBarkTown/scripts.pory"
	.string "what that actually is.\p"
# 1748 "data/maps/NewBarkTown/scripts.pory"
	.string "We need four. There are four of\n"
# 1749 "data/maps/NewBarkTown/scripts.pory"
	.string "us standing here.\p"
# 1750 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Ma'am.\p"
# 1751 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I heard you the first\n"
# 1752 "data/maps/NewBarkTown/scripts.pory"
	.string "time.$"
# 1753 "data/maps/NewBarkTown/scripts.pory"

# 1754 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1755 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIn:
# 1756 "data/maps/NewBarkTown/scripts.pory"
	.string "…Say that again.\p"
# 1757 "data/maps/NewBarkTown/scripts.pory"
	.string "No. Don't. If you say it again\n"
# 1758 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll cry, and I am NOT doing\l"
# 1759 "data/maps/NewBarkTown/scripts.pory"
	.string "that in front of {PLAYER}.\p"
# 1760 "data/maps/NewBarkTown/scripts.pory"
	.string "Azumarill! Back to me!\p"
# 1761 "data/maps/NewBarkTown/scripts.pory"
	.string "We're in. We're actually in.$"
# 1762 "data/maps/NewBarkTown/scripts.pory"

# 1763 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBChoosePrompt:
# 1764 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER} - which one\n"
# 1765 "data/maps/NewBarkTown/scripts.pory"
	.string "will you take?\p"
# 1766 "data/maps/NewBarkTown/scripts.pory"
	.string "I am asking. I am not deciding\n"
# 1767 "data/maps/NewBarkTown/scripts.pory"
	.string "it for you.\p"
# 1768 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Choose, {PLAYER}.\p"
# 1769 "data/maps/NewBarkTown/scripts.pory"
	.string "Quickly, and then not again.$"
# 1770 "data/maps/NewBarkTown/scripts.pory"

# 1771 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceKartana:
# 1772 "data/maps/NewBarkTown/scripts.pory"
	.string "Kartana$"
# 1773 "data/maps/NewBarkTown/scripts.pory"

# 1774 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceGuzzlord:
# 1775 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord$"
# 1776 "data/maps/NewBarkTown/scripts.pory"

# 1777 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceNihilego:
# 1778 "data/maps/NewBarkTown/scripts.pory"
	.string "Nihilego$"
# 1779 "data/maps/NewBarkTown/scripts.pory"

# 1780 "data/maps/NewBarkTown/scripts.pory"
@ Each of the three says the whole split out loud - design section 6.4.
# 1781 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedKartana:
# 1782 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The blade.\p"
# 1783 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I take the one that\n"
# 1784 "data/maps/NewBarkTown/scripts.pory"
	.string "matters to me, and Anabel takes\l"
# 1785 "data/maps/NewBarkTown/scripts.pory"
	.string "the weight.\p"
# 1786 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nihilego is hers.\n"
# 1787 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord is mine.\p"
# 1788 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}And I'm on the blade\n"
# 1789 "data/maps/NewBarkTown/scripts.pory"
	.string "with {PLAYER}.\p"
# 1790 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}On my mark. All four.$"
# 1791 "data/maps/NewBarkTown/scripts.pory"

# 1792 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedGuzzlord:
# 1793 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The mouth.\p"
# 1794 "data/maps/NewBarkTown/scripts.pory"
	.string "Be careful - it does not stop\n"
# 1795 "data/maps/NewBarkTown/scripts.pory"
	.string "because you are tired.\p"
# 1796 "data/maps/NewBarkTown/scripts.pory"
	.string "I take Nihilego. It is the one\n"
# 1797 "data/maps/NewBarkTown/scripts.pory"
	.string "I came for.\p"
# 1798 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Then the blade is\n"
# 1799 "data/maps/NewBarkTown/scripts.pory"
	.string "mine.\p"
# 1800 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}And I'm on the mouth\n"
# 1801 "data/maps/NewBarkTown/scripts.pory"
	.string "with {PLAYER}.\p"
# 1802 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}On my mark. All four.$"
# 1803 "data/maps/NewBarkTown/scripts.pory"

# 1804 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedNihilego:
# 1805 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…That one was mine to\n"
# 1806 "data/maps/NewBarkTown/scripts.pory"
	.string "answer for.\p"
# 1807 "data/maps/NewBarkTown/scripts.pory"
	.string "No. That is exactly the\n"
# 1808 "data/maps/NewBarkTown/scripts.pory"
	.string "sentence I promised my children\l"
# 1809 "data/maps/NewBarkTown/scripts.pory"
	.string "I would stop saying.\p"
# 1810 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you for taking it.\p"
# 1811 "data/maps/NewBarkTown/scripts.pory"
	.string "I will take the mouth instead.\p"
# 1812 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And I'll take the\n"
# 1813 "data/maps/NewBarkTown/scripts.pory"
	.string "blade.\p"
# 1814 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}I'm going where\n"
# 1815 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} goes.\p"
# 1816 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}On my mark. All four.$"
# 1817 "data/maps/NewBarkTown/scripts.pory"

# 1818 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBGotAway:
# 1819 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}It is still here.\p"
# 1820 "data/maps/NewBarkTown/scripts.pory"
	.string "All three of them are still\n"
# 1821 "data/maps/NewBarkTown/scripts.pory"
	.string "here.\p"
# 1822 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Back to the line,\n"
# 1823 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}. We go again.\p"
# 1824 "data/maps/NewBarkTown/scripts.pory"
	.string "All four of us.$"
# 1825 "data/maps/NewBarkTown/scripts.pory"

# 1826 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterKartana:
# 1827 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Down. All three, inside\n"
# 1828 "data/maps/NewBarkTown/scripts.pory"
	.string "the same second.\p"
# 1829 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Mine folded the moment\n"
# 1830 "data/maps/NewBarkTown/scripts.pory"
	.string "yours did.\p"
# 1831 "data/maps/NewBarkTown/scripts.pory"
	.string "They came together and they\n"
# 1832 "data/maps/NewBarkTown/scripts.pory"
	.string "fall together - of course they\l"
# 1833 "data/maps/NewBarkTown/scripts.pory"
	.string "do.\p"
# 1834 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}We did it. We actually\n"
# 1835 "data/maps/NewBarkTown/scripts.pory"
	.string "did it.$"
# 1836 "data/maps/NewBarkTown/scripts.pory"

# 1837 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterGuzzlord:
# 1838 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Down. All three, inside\n"
# 1839 "data/maps/NewBarkTown/scripts.pory"
	.string "the same second.\p"
# 1840 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}You stood in front of\n"
# 1841 "data/maps/NewBarkTown/scripts.pory"
	.string "that thing for how long?\p"
# 1842 "data/maps/NewBarkTown/scripts.pory"
	.string "…Lillie was right about you.\p"
# 1843 "data/maps/NewBarkTown/scripts.pory"
	.string "She is right a great deal\n"
# 1844 "data/maps/NewBarkTown/scripts.pory"
	.string "lately.\p"
# 1845 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}We did it. We actually\n"
# 1846 "data/maps/NewBarkTown/scripts.pory"
	.string "did it.$"
# 1847 "data/maps/NewBarkTown/scripts.pory"

# 1848 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterNihilego:
# 1849 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Down. All three, inside\n"
# 1850 "data/maps/NewBarkTown/scripts.pory"
	.string "the same second.\p"
# 1851 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I watched you do that.\p"
# 1852 "data/maps/NewBarkTown/scripts.pory"
	.string "I made myself watch all of it.\p"
# 1853 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you. I will not say it a\n"
# 1854 "data/maps/NewBarkTown/scripts.pory"
	.string "third time, but I mean it more\l"
# 1855 "data/maps/NewBarkTown/scripts.pory"
	.string "each time.\p"
# 1856 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}We did it. We actually\n"
# 1857 "data/maps/NewBarkTown/scripts.pory"
	.string "did it.$"
# 1858 "data/maps/NewBarkTown/scripts.pory"

# 1859 "data/maps/NewBarkTown/scripts.pory"
@ Nobody in Johto names it. It has been "the thing from Blackthorn" for
# 1860 "data/maps/NewBarkTown/scripts.pory"
@ three missions and it stays that way until the reunion.
# 1861 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNecrozmaArrives:
# 1862 "data/maps/NewBarkTown/scripts.pory"
	.string "The road opens.\p"
# 1863 "data/maps/NewBarkTown/scripts.pory"
	.string "Not a tear this time. The air\n"
# 1864 "data/maps/NewBarkTown/scripts.pory"
	.string "itself steps aside, and\l"
# 1865 "data/maps/NewBarkTown/scripts.pory"
	.string "something walks out of it onto\l"
# 1866 "data/maps/NewBarkTown/scripts.pory"
	.string "the street.\p"
# 1867 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…That is the thing from\n"
# 1868 "data/maps/NewBarkTown/scripts.pory"
	.string "Blackthorn.\p"
# 1869 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}It's on the ROAD. The\n"
# 1870 "data/maps/NewBarkTown/scripts.pory"
	.string "others came out of the sky and\l"
# 1871 "data/maps/NewBarkTown/scripts.pory"
	.string "that one used the road.\p"
# 1872 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I have seen light like\n"
# 1873 "data/maps/NewBarkTown/scripts.pory"
	.string "that before.\p"
# 1874 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Madame.\p"
# 1875 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…Later.$"
# 1876 "data/maps/NewBarkTown/scripts.pory"

# 1877 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1878 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalCharges:
# 1879 "data/maps/NewBarkTown/scripts.pory"
	.string "It's walking past them.\p"
# 1880 "data/maps/NewBarkTown/scripts.pory"
	.string "It's not even looking at the\n"
# 1881 "data/maps/NewBarkTown/scripts.pory"
	.string "three of them, it's-\p"
# 1882 "data/maps/NewBarkTown/scripts.pory"
	.string "No. No, I got let in.\p"
# 1883 "data/maps/NewBarkTown/scripts.pory"
	.string "AZUMARILL!$"
# 1884 "data/maps/NewBarkTown/scripts.pory"

# 1885 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalRepelled:
# 1886 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Get it back! Now!\p"
# 1887 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}It's up. It's up, it's\n"
# 1888 "data/maps/NewBarkTown/scripts.pory"
	.string "fine, it's-\p"
# 1889 "data/maps/NewBarkTown/scripts.pory"
	.string "It didn't block. It didn't\n"
# 1890 "data/maps/NewBarkTown/scripts.pory"
	.string "dodge. It didn't do anything.\p"
# 1891 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}My friend, that was\n"
# 1892 "data/maps/NewBarkTown/scripts.pory"
	.string "the bravest useless thing I\l"
# 1893 "data/maps/NewBarkTown/scripts.pory"
	.string "have seen in twenty years of\l"
# 1894 "data/maps/NewBarkTown/scripts.pory"
	.string "this work.\p"
# 1895 "data/maps/NewBarkTown/scripts.pory"
	.string "Do not do it twice.$"
# 1896 "data/maps/NewBarkTown/scripts.pory"

# 1897 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAbsorbed:
# 1898 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}They're moving. They\n"
# 1899 "data/maps/NewBarkTown/scripts.pory"
	.string "were down and they're moving.\p"
# 1900 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They are not moving.\n"
# 1901 "data/maps/NewBarkTown/scripts.pory"
	.string "They are being moved.\p"
# 1902 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}It is not fighting\n"
# 1903 "data/maps/NewBarkTown/scripts.pory"
	.string "them.\p"
# 1904 "data/maps/NewBarkTown/scripts.pory"
	.string "Inspector - it is not fighting\n"
# 1905 "data/maps/NewBarkTown/scripts.pory"
	.string "them, it is COLLECTING them.\p"
# 1906 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Three at once.\p"
# 1907 "data/maps/NewBarkTown/scripts.pory"
	.string "It took two in Blackthorn. Two\n"
# 1908 "data/maps/NewBarkTown/scripts.pory"
	.string "at the Lake. Two on the beach.$"
# 1909 "data/maps/NewBarkTown/scripts.pory"

# 1910 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraRises:
# 1911 "data/maps/NewBarkTown/scripts.pory"
	.string "The light does not go out this\n"
# 1912 "data/maps/NewBarkTown/scripts.pory"
	.string "time.\p"
# 1913 "data/maps/NewBarkTown/scripts.pory"
	.string "It folds. It keeps folding,\n"
# 1914 "data/maps/NewBarkTown/scripts.pory"
	.string "into something with a shape,\l"
# 1915 "data/maps/NewBarkTown/scripts.pory"
	.string "and the shape is standing in\l"
# 1916 "data/maps/NewBarkTown/scripts.pory"
	.string "the middle of New Bark Town.\p"
# 1917 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Formation. NOW.\p"
# 1918 "data/maps/NewBarkTown/scripts.pory"
	.string "Same mark. Same instant. It is\n"
# 1919 "data/maps/NewBarkTown/scripts.pory"
	.string "the only thing that has worked\l"
# 1920 "data/maps/NewBarkTown/scripts.pory"
	.string "all day.\p"
# 1921 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}All four. Together.$"
# 1922 "data/maps/NewBarkTown/scripts.pory"

# 1923 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraBreaksThem:
# 1924 "data/maps/NewBarkTown/scripts.pory"
	.string "It was over before any of them\n"
# 1925 "data/maps/NewBarkTown/scripts.pory"
	.string "finished the motion.\p"
# 1926 "data/maps/NewBarkTown/scripts.pory"
	.string "One light, across the whole\n"
# 1927 "data/maps/NewBarkTown/scripts.pory"
	.string "road, at once.\p"
# 1928 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}…Report.\p"
# 1929 "data/maps/NewBarkTown/scripts.pory"
	.string "Somebody report. Anybody.\p"
# 1930 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I am on the ground,\n"
# 1931 "data/maps/NewBarkTown/scripts.pory"
	.string "Chief.\p"
# 1932 "data/maps/NewBarkTown/scripts.pory"
	.string "We are all on the ground.$"
# 1933 "data/maps/NewBarkTown/scripts.pory"

# 1934 "data/maps/NewBarkTown/scripts.pory"
@ Optional, stateless. It is the only thing on this road that it looks at
# 1935 "data/maps/NewBarkTown/scripts.pory"
@ twice, and it does not take it.
# 1936 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraSensesCosmog:
# 1937 "data/maps/NewBarkTown/scripts.pory"
	.string "It turns.\p"
# 1938 "data/maps/NewBarkTown/scripts.pory"
	.string "Not to Lusamine, not to the\n"
# 1939 "data/maps/NewBarkTown/scripts.pory"
	.string "police. To {STR_VAR_1}, which is\l"
# 1940 "data/maps/NewBarkTown/scripts.pory"
	.string "the only thing on this road\l"
# 1941 "data/maps/NewBarkTown/scripts.pory"
	.string "still standing up.\p"
# 1942 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Don't move. Don't you\n"
# 1943 "data/maps/NewBarkTown/scripts.pory"
	.string "move, either of you.\p"
# 1944 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It is not going to\n"
# 1945 "data/maps/NewBarkTown/scripts.pory"
	.string "take it.\p"
# 1946 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}No. It is not.\p"
# 1947 "data/maps/NewBarkTown/scripts.pory"
	.string "It is WAITING for it.$"
# 1948 "data/maps/NewBarkTown/scripts.pory"

# 1949 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraSensesLegend:
# 1950 "data/maps/NewBarkTown/scripts.pory"
	.string "It turns.\p"
# 1951 "data/maps/NewBarkTown/scripts.pory"
	.string "{STR_VAR_1} stands up between\n"
# 1952 "data/maps/NewBarkTown/scripts.pory"
	.string "the light and everyone lying in\l"
# 1953 "data/maps/NewBarkTown/scripts.pory"
	.string "the road, and does not step\l"
# 1954 "data/maps/NewBarkTown/scripts.pory"
	.string "back.\p"
# 1955 "data/maps/NewBarkTown/scripts.pory"
	.string "And the thing in the street\n"
# 1956 "data/maps/NewBarkTown/scripts.pory"
	.string "stops.\p"
# 1957 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}…It knows that shape.\p"
# 1958 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Madame, it just\n"
# 1959 "data/maps/NewBarkTown/scripts.pory"
	.string "hesitated. That thing flattened\l"
# 1960 "data/maps/NewBarkTown/scripts.pory"
	.string "four trainers and it just\l"
# 1961 "data/maps/NewBarkTown/scripts.pory"
	.string "hesitated.\p"
# 1962 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Write that down,\n"
# 1963 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor. Write exactly that\l"
# 1964 "data/maps/NewBarkTown/scripts.pory"
	.string "down.$"
# 1965 "data/maps/NewBarkTown/scripts.pory"

# 1966 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBUltraGone:
# 1967 "data/maps/NewBarkTown/scripts.pory"
	.string "It steps back into the place\n"
# 1968 "data/maps/NewBarkTown/scripts.pory"
	.string "the road opened, and the road\l"
# 1969 "data/maps/NewBarkTown/scripts.pory"
	.string "closes behind it.\p"
# 1970 "data/maps/NewBarkTown/scripts.pory"
	.string "Nothing is broken. No house, no\n"
# 1971 "data/maps/NewBarkTown/scripts.pory"
	.string "fence, no window.\p"
# 1972 "data/maps/NewBarkTown/scripts.pory"
	.string "It never wanted the town at\n"
# 1973 "data/maps/NewBarkTown/scripts.pory"
	.string "all.$"
# 1974 "data/maps/NewBarkTown/scripts.pory"

# 1975 "data/maps/NewBarkTown/scripts.pory"
@ The people first. Looker, every mission, before the report.
# 1976 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathHurt:
# 1977 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Is anyone hurt?\p"
# 1978 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}? Your Pokémon?\p"
# 1979 "data/maps/NewBarkTown/scripts.pory"
	.string "Chief? Madame?\p"
# 1980 "data/maps/NewBarkTown/scripts.pory"
	.string "…And you. The one with the\n"
# 1981 "data/maps/NewBarkTown/scripts.pory"
	.string "Azumarill. Look at me when I\l"
# 1982 "data/maps/NewBarkTown/scripts.pory"
	.string "ask you.\p"
# 1983 "data/maps/NewBarkTown/scripts.pory"
	.string "…Good. Good.\p"
# 1984 "data/maps/NewBarkTown/scripts.pory"
	.string "The report can wait a moment.$"
# 1985 "data/maps/NewBarkTown/scripts.pory"

# 1986 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmCost:
# 1987 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ELM}The sensors are gone.\p"
# 1988 "data/maps/NewBarkTown/scripts.pory"
	.string "Every one of them. Melted, or\n"
# 1989 "data/maps/NewBarkTown/scripts.pory"
	.string "whatever that was.\p"
# 1990 "data/maps/NewBarkTown/scripts.pory"
	.string "…I don't mind. I have six weeks\n"
# 1991 "data/maps/NewBarkTown/scripts.pory"
	.string "of data.\p"
# 1992 "data/maps/NewBarkTown/scripts.pory"
	.string "The last thirty seconds of it\n"
# 1993 "data/maps/NewBarkTown/scripts.pory"
	.string "are three signatures going into\l"
# 1994 "data/maps/NewBarkTown/scripts.pory"
	.string "one signature.\p"
# 1995 "data/maps/NewBarkTown/scripts.pory"
	.string "Three into one. I watched a\n"
# 1996 "data/maps/NewBarkTown/scripts.pory"
	.string "number do that.$"
# 1997 "data/maps/NewBarkTown/scripts.pory"

# 1998 "data/maps/NewBarkTown/scripts.pory"
@ The gut punch, and the point of the whole mission. Anabel does the
# 1999 "data/maps/NewBarkTown/scripts.pory"
@ arithmetic of four missions out loud.
# 2000 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBWhatItWas:
# 2001 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nine.\p"
# 2002 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief?\p"
# 2003 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nine Ultra Beasts.\n"
# 2004 "data/maps/NewBarkTown/scripts.pory"
	.string "Blackthorn, the Lake, the\l"
# 2005 "data/maps/NewBarkTown/scripts.pory"
	.string "beach, this road.\p"
# 2006 "data/maps/NewBarkTown/scripts.pory"
	.string "It has been at every one of\n"
# 2007 "data/maps/NewBarkTown/scripts.pory"
	.string "them, and it has left with\l"
# 2008 "data/maps/NewBarkTown/scripts.pory"
	.string "every single one of them.\p"
# 2009 "data/maps/NewBarkTown/scripts.pory"
	.string "It was never attacking Johto.\p"
# 2010 "data/maps/NewBarkTown/scripts.pory"
	.string "It was never attacking us at\n"
# 2011 "data/maps/NewBarkTown/scripts.pory"
	.string "all.\p"
# 2012 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…It was collecting.\p"
# 2013 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And we softened them\n"
# 2014 "data/maps/NewBarkTown/scripts.pory"
	.string "for it. Four times.\p"
# 2015 "data/maps/NewBarkTown/scripts.pory"
	.string "Put that in the report, Looker.\p"
# 2016 "data/maps/NewBarkTown/scripts.pory"
	.string "Put that in first.$"
# 2017 "data/maps/NewBarkTown/scripts.pory"

# 2018 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineLost:
# 2019 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}We held the street.\p"
# 2020 "data/maps/NewBarkTown/scripts.pory"
	.string "Not one person on it is hurt,\n"
# 2021 "data/maps/NewBarkTown/scripts.pory"
	.string "and not one window is broken,\l"
# 2022 "data/maps/NewBarkTown/scripts.pory"
	.string "and I want that said plainly\l"
# 2023 "data/maps/NewBarkTown/scripts.pory"
	.string "before anything else.\p"
# 2024 "data/maps/NewBarkTown/scripts.pory"
	.string "And we lost.\p"
# 2025 "data/maps/NewBarkTown/scripts.pory"
	.string "It came for something, it took\n"
# 2026 "data/maps/NewBarkTown/scripts.pory"
	.string "it, and it walked out.\p"
# 2027 "data/maps/NewBarkTown/scripts.pory"
	.string "I have been on the other end of\n"
# 2028 "data/maps/NewBarkTown/scripts.pory"
	.string "a plan like that.\p"
# 2029 "data/maps/NewBarkTown/scripts.pory"
	.string "You do not notice it is a plan\n"
# 2030 "data/maps/NewBarkTown/scripts.pory"
	.string "until it is finished.$"
# 2031 "data/maps/NewBarkTown/scripts.pory"

# 2032 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 2033 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRival:
# 2034 "data/maps/NewBarkTown/scripts.pory"
	.string "I got in.\p"
# 2035 "data/maps/NewBarkTown/scripts.pory"
	.string "I finally got in, and I hit it\n"
# 2036 "data/maps/NewBarkTown/scripts.pory"
	.string "with everything I've got, and\l"
# 2037 "data/maps/NewBarkTown/scripts.pory"
	.string "it didn't even turn its head.\p"
# 2038 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Neither did mine.\p"
# 2039 "data/maps/NewBarkTown/scripts.pory"
	.string "Neither did the Champion's.\p"
# 2040 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not a thing that\n"
# 2041 "data/maps/NewBarkTown/scripts.pory"
	.string "happened to you. That is a\l"
# 2042 "data/maps/NewBarkTown/scripts.pory"
	.string "thing that happened to all of\l"
# 2043 "data/maps/NewBarkTown/scripts.pory"
	.string "us, and you were in it.\p"
# 2044 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_NONE}…Yeah.\p"
# 2045 "data/maps/NewBarkTown/scripts.pory"
	.string "Yeah, okay.\p"
# 2046 "data/maps/NewBarkTown/scripts.pory"
	.string "Right. Doors. Forty people to\n"
# 2047 "data/maps/NewBarkTown/scripts.pory"
	.string "let back out.$"
# 2048 "data/maps/NewBarkTown/scripts.pory"

# 2049 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMom:
# 2050 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_MOM}Come inside when you can.\p"
# 2051 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll leave the light on.\p"
# 2052 "data/maps/NewBarkTown/scripts.pory"
	.string "You know I will.$"
# 2053 "data/maps/NewBarkTown/scripts.pory"

# 2054 "data/maps/NewBarkTown/scripts.pory"
@ The other half of the Olivine briefing, and the only thing anybody has
# 2055 "data/maps/NewBarkTown/scripts.pory"
@ left to hold after a defeat. One box. Do not grow it back into the speech.
# 2056 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelPromise:
# 2057 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{PLAYER}.\p"
# 2058 "data/maps/NewBarkTown/scripts.pory"
	.string "What I told you in that office,\n"
# 2059 "data/maps/NewBarkTown/scripts.pory"
	.string "before any of this.\p"
# 2060 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone who comes through gets\n"
# 2061 "data/maps/NewBarkTown/scripts.pory"
	.string "a hand. Everyone who goes in\l"
# 2062 "data/maps/NewBarkTown/scripts.pory"
	.string "comes home.\p"
# 2063 "data/maps/NewBarkTown/scripts.pory"
	.string "We lost the road today. We did\n"
# 2064 "data/maps/NewBarkTown/scripts.pory"
	.string "not lose that.\p"
# 2065 "data/maps/NewBarkTown/scripts.pory"
	.string "Both. Always both.$"
# 2066 "data/maps/NewBarkTown/scripts.pory"

# 2067 "data/maps/NewBarkTown/scripts.pory"
@ Optional, re-read from VAR_TEMP_4.
# 2068 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAftermathCosmog:
# 2069 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER}.\p"
# 2070 "data/maps/NewBarkTown/scripts.pory"
	.string "It looked at {STR_VAR_1} and it\n"
# 2071 "data/maps/NewBarkTown/scripts.pory"
	.string "chose to leave.\p"
# 2072 "data/maps/NewBarkTown/scripts.pory"
	.string "I have never once known that\n"
# 2073 "data/maps/NewBarkTown/scripts.pory"
	.string "thing to leave something it\l"
# 2074 "data/maps/NewBarkTown/scripts.pory"
	.string "wanted.\p"
# 2075 "data/maps/NewBarkTown/scripts.pory"
	.string "Keep them close. Not because\n"
# 2076 "data/maps/NewBarkTown/scripts.pory"
	.string "they are in danger.\p"
# 2077 "data/maps/NewBarkTown/scripts.pory"
	.string "Because they are the only\n"
# 2078 "data/maps/NewBarkTown/scripts.pory"
	.string "reason it stopped.$"
# 2079 "data/maps/NewBarkTown/scripts.pory"

# 2080 "data/maps/NewBarkTown/scripts.pory"
@ This block IS the hook into the Olivine reunion, design section 7.
# 2081 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBHook:
# 2082 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Looker. They didn't\n"
# 2083 "data/maps/NewBarkTown/scripts.pory"
	.string "scatter.\p"
# 2084 "data/maps/NewBarkTown/scripts.pory"
	.string "It left on a bearing, and the\n"
# 2085 "data/maps/NewBarkTown/scripts.pory"
	.string "three rifts closed toward the\l"
# 2086 "data/maps/NewBarkTown/scripts.pory"
	.string "same one.\p"
# 2087 "data/maps/NewBarkTown/scripts.pory"
	.string "I can put a place on a map now.\p"
# 2088 "data/maps/NewBarkTown/scripts.pory"
	.string "I have never once been able to\n"
# 2089 "data/maps/NewBarkTown/scripts.pory"
	.string "do that.\p"
# 2090 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then the investigation\n"
# 2091 "data/maps/NewBarkTown/scripts.pory"
	.string "is finished, and something else\l"
# 2092 "data/maps/NewBarkTown/scripts.pory"
	.string "begins.\p"
# 2093 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Inspector. Call my\n"
# 2094 "data/maps/NewBarkTown/scripts.pory"
	.string "children. Both of them.\p"
# 2095 "data/maps/NewBarkTown/scripts.pory"
	.string "And Professor Kukui - he has\n"
# 2096 "data/maps/NewBarkTown/scripts.pory"
	.string "earned the room twice over\l"
# 2097 "data/maps/NewBarkTown/scripts.pory"
	.string "without ever setting foot in\l"
# 2098 "data/maps/NewBarkTown/scripts.pory"
	.string "it.\p"
# 2099 "data/maps/NewBarkTown/scripts.pory"
	.string "Not as Aether.\p"
# 2100 "data/maps/NewBarkTown/scripts.pory"
	.string "I owe these people an\n"
# 2101 "data/maps/NewBarkTown/scripts.pory"
	.string "accounting, and two of them are\l"
# 2102 "data/maps/NewBarkTown/scripts.pory"
	.string "mine.\p"
# 2103 "data/maps/NewBarkTown/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Olivine, then.\p"
# 2104 "data/maps/NewBarkTown/scripts.pory"
	.string "All of us, in that small room.\p"
# 2105 "data/maps/NewBarkTown/scripts.pory"
	.string "I apologise in advance for the\n"
# 2106 "data/maps/NewBarkTown/scripts.pory"
	.string "chairs.\p"
# 2107 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} - bring your partner.\p"
# 2108 "data/maps/NewBarkTown/scripts.pory"
	.string "Not for a test.\p"
# 2109 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone in that room has been\n"
# 2110 "data/maps/NewBarkTown/scripts.pory"
	.string "waiting a long time to meet\l"
# 2111 "data/maps/NewBarkTown/scripts.pory"
	.string "them.$"

# 344 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_0:
# 344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 344 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
	step_end

# 347 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_1:
# 347 "data/maps/NewBarkTown/scripts.pory"
	jump_down
	step_end

# 350 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_2:
# 350 "data/maps/NewBarkTown/scripts.pory"
	walk_up
	step_end

# 352 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_3:
# 352 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_up
	step_end

# 359 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_4:
# 359 "data/maps/NewBarkTown/scripts.pory"
	walk_right
# 359 "data/maps/NewBarkTown/scripts.pory"
	walk_right
	step_end

# 363 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_5:
# 363 "data/maps/NewBarkTown/scripts.pory"
	face_left
	step_end

# 365 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_6:
# 365 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 365 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 365 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 365 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 365 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 367 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_7:
# 367 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_left
	step_end

# 373 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_8:
# 373 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 373 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 373 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 373 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 374 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalIntro_Movement_9:
# 374 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 374 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 374 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 374 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 374 "data/maps/NewBarkTown/scripts.pory"
	walk_left
	step_end

# 389 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_0:
# 389 "data/maps/NewBarkTown/scripts.pory"
	jump_in_place_right
	step_end

# 395 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_1:
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 395 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 396 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 396 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_up
# 396 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 396 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_right
# 396 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_down
# 396 "data/maps/NewBarkTown/scripts.pory"
	face_left
	step_end

# 397 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_2:
# 397 "data/maps/NewBarkTown/scripts.pory"
	face_up
	step_end

# 402 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_3:
# 402 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 402 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 402 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 402 "data/maps/NewBarkTown/scripts.pory"
	walk_right
	step_end

# 408 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_4:
# 408 "data/maps/NewBarkTown/scripts.pory"
	walk_fast_left
# 408 "data/maps/NewBarkTown/scripts.pory"
	face_right
# 408 "data/maps/NewBarkTown/scripts.pory"
	exit_pokeball
# 408 "data/maps/NewBarkTown/scripts.pory"
	set_visible
	step_end

# 439 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_5:
# 439 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 439 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 439 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 439 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 439 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 439 "data/maps/NewBarkTown/scripts.pory"
	walk_down
	step_end

# 440 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_RivalBattle_Movement_6:
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_down
# 440 "data/maps/NewBarkTown/scripts.pory"
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Text_0:
# 407 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_1:
# 412 "data/maps/NewBarkTown/scripts.pory"
	.string "So you picked...\n"
	.string "a {STR_VAR_1}!$"

NewBarkTown_EventScript_RivalBattle_Text_2:
# 414 "data/maps/NewBarkTown/scripts.pory"
	.string "That's a cute Pokémon you have!$"

NewBarkTown_EventScript_RivalBattle_Text_3:
# 415 "data/maps/NewBarkTown/scripts.pory"
	.string "When you walk with it, it'll become\n"
	.string "more friendly!$"

NewBarkTown_EventScript_RivalBattle_Text_4:
# 417 "data/maps/NewBarkTown/scripts.pory"
	.string "You should turn around and talk to it\n"
	.string "sometimes, too.$"

NewBarkTown_EventScript_RivalBattle_Text_5:
# 419 "data/maps/NewBarkTown/scripts.pory"
	.string "Hey, why don't we have a battle?\n"
	.string "That's what trainers usually do when\l"
	.string "they meet!$"

NewBarkTown_EventScript_RivalBattle_Text_6:
# 425 "data/maps/NewBarkTown/scripts.pory"
	.string "You did really well, {PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_7:
# 432 "data/maps/NewBarkTown/scripts.pory"
	.string "That was really fun, and both of our\n"
	.string "Pokémon did their best!$"

NewBarkTown_EventScript_RivalBattle_Text_8:
# 434 "data/maps/NewBarkTown/scripts.pory"
	.string "You got a task from Elm right?\n"
	.string "I'll leave you to it then.\l"
	.string "See ya!$"

RivalsMailbox_Text_0:
# 455 "data/maps/NewBarkTown/scripts.pory"
	.string "Crystal's house$"

RivalsMailbox_Text_1:
# 457 "data/maps/NewBarkTown/scripts.pory"
	.string "Gold's house$"

NewBarkTown_EventScript_ArcherArcadeCall_Text_0:
# 465 "data/maps/NewBarkTown/scripts.pory"
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
