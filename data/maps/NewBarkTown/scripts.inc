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
@ .claude/NEWBARK_ULTRABEAST_IMPLEMENTATION.md section 3.3.)
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
	.string "Looker: Hello? Is this {PLAYER}?\n"
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


# 487 "data/maps/NewBarkTown/scripts.pory"

# 488 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 489 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 - Kartana + Guzzlord + Nihilego on the road outside the
# 490 "data/maps/NewBarkTown/scripts.pory"
@ player's own front door. Last mission of the arc.
# 491 "data/maps/NewBarkTown/scripts.pory"
@ Cast: Looker, Anabel, Mom, Gold/Crystal (+ Marill), Professor Elm and
# 492 "data/maps/NewBarkTown/scripts.pory"
@ Madame Lusamine. Only the player battles.
# 493 "data/maps/NewBarkTown/scripts.pory"
@ Plan: .claude/NEWBARK_ULTRABEAST_IMPLEMENTATION.md
# 494 "data/maps/NewBarkTown/scripts.pory"
@
# 495 "data/maps/NewBarkTown/scripts.pory"
@ Floor plan (dump_mapa.py NewBarkTown; y grows DOWNWARD). There is not one
# 496 "data/maps/NewBarkTown/scripts.pory"
@ water tile in LAYOUT_NEW_BARK_TOWN, so the collision bit is the whole
# 497 "data/maps/NewBarkTown/scripts.pory"
@ truth here - unlike the Cherrygrove beach.
# 498 "data/maps/NewBarkTown/scripts.pory"
@
# 499 "data/maps/NewBarkTown/scripts.pory"
@       x= 2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
# 500 "data/maps/NewBarkTown/scripts.pory"
@   y= 9   #  #  #  .  .  #  #  #  D  #  .  #  .  .  .  .  #  #  #  #  #  #  #
# 501 "data/maps/NewBarkTown/scripts.pory"
@   y=10   #  #  .  .  .  .  .  .  .  E' .  .  .  1  .  .  #  #  #  #  #  #  #
# 502 "data/maps/NewBarkTown/scripts.pory"
@   y=11   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  #  #  #  d  #  #  .  .
# 503 "data/maps/NewBarkTown/scripts.pory"
@   y=12   .  U' .  .  .  .  .  .  .  .  .  .  .  .  .  U  M  *  K  A  E  .  .
# 504 "data/maps/NewBarkTown/scripts.pory"
@   y=13   .  .  .  .  .  .  .  .  .  .  .  2  .  .  .  .  .  .  G  m  .  .  .
# 505 "data/maps/NewBarkTown/scripts.pory"
@   y=14   .  .  .  .  .  .  .  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
# 506 "data/maps/NewBarkTown/scripts.pory"
@   y=15   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  3  .  .
# 507 "data/maps/NewBarkTown/scripts.pory"
@
# 508 "data/maps/NewBarkTown/scripts.pory"
@   D  lab door, warp (10,9)          d  player's house door, warp (20,11)
# 509 "data/maps/NewBarkTown/scripts.pory"
@   *  player (20,12)                 K  Looker (21,12)   A  Anabel (22,12)
# 510 "data/maps/NewBarkTown/scripts.pory"
@   M  Mom (19,12)                    G  Gold/Crystal (21,13)   m  Marill (22,13)
# 511 "data/maps/NewBarkTown/scripts.pory"
@   U' Lusamine starts (3,12)         U  Lusamine after the fade (18,12)
# 512 "data/maps/NewBarkTown/scripts.pory"
@   E' Elm starts (11,10)             E  Elm after the fade (23,12)
# 513 "data/maps/NewBarkTown/scripts.pory"
@   1  Kartana (15,10)   2  Nihilego (14,13)   3  Guzzlord (23,15)
# 514 "data/maps/NewBarkTown/scripts.pory"
@
# 515 "data/maps/NewBarkTown/scripts.pory"
@ LOOKER'S POCKET. (21,11) is the wall of the player's house, (22,12) is
# 516 "data/maps/NewBarkTown/scripts.pory"
@ Anabel and (21,13) is Gold/Crystal. The ONLY tile Looker can be talked to
# 517 "data/maps/NewBarkTown/scripts.pory"
@ from is (20,12), facing east - no getplayerxy needed.
# 518 "data/maps/NewBarkTown/scripts.pory"
@ And (20,12) is exactly where the game puts the player twice over:
# 519 "data/maps/NewBarkTown/scripts.pory"
@ HEAL_LOCATION_NEW_BARK_TOWN is (20,12) (src/data/heal_locations.h:139) and
# 520 "data/maps/NewBarkTown/scripts.pory"
@ NewBarkTown_OnLoad re-does the setrespawn on every load, so a blackout AND
# 521 "data/maps/NewBarkTown/scripts.pory"
@ a Fly both land on the talk tile. Retry costs zero steps - the only mission
# 522 "data/maps/NewBarkTown/scripts.pory"
@ in the arc where that is true.
# 523 "data/maps/NewBarkTown/scripts.pory"
@
# 524 "data/maps/NewBarkTown/scripts.pory"
@ (20,13) IS DELIBERATELY EMPTY. With the player on y=12 the text box covers
# 525 "data/maps/NewBarkTown/scripts.pory"
@ the bottom of the screen; the actors on y=13 sit just above it. Putting an
# 526 "data/maps/NewBarkTown/scripts.pory"
@ object at (20,13) would bury it under every line of dialogue.
# 527 "data/maps/NewBarkTown/scripts.pory"
@
# 528 "data/maps/NewBarkTown/scripts.pory"
@ The player's front door at (20,11) stays usable before the scene. Harmless:
# 529 "data/maps/NewBarkTown/scripts.pory"
@ the scene only starts by talking to Looker, the house is empty during the
# 530 "data/maps/NewBarkTown/scripts.pory"
@ incident (NewBarkTown_PlayersHouse_1F_ApplyMomVisibility), and coming back
# 531 "data/maps/NewBarkTown/scripts.pory"
@ out puts the player on (20,12) again.
# 532 "data/maps/NewBarkTown/scripts.pory"
@
# 533 "data/maps/NewBarkTown/scripts.pory"
@ The three beasts stand on walkable ground and CAN be reached on foot. That
# 534 "data/maps/NewBarkTown/scripts.pory"
@ is fine - they only exist while the player is under lockall, and all three
# 535 "data/maps/NewBarkTown/scripts.pory"
@ have script NULL. Do not "fix" this by inventing collision.
# 536 "data/maps/NewBarkTown/scripts.pory"
@
# 537 "data/maps/NewBarkTown/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 538 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_1 - fixed cast cache (Looker, Anabel, Mom, Gold/Crystal, Marill)
# 539 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_2 - the three Ultra Beasts; always hidden on load
# 540 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_3 - Elm ONLY          \ separate because the cutscene
# 541 "data/maps/NewBarkTown/scripts.pory"
@   FLAG_TEMP_4 - Lusamine ONLY     / removeobjects these two to move them,
# 542 "data/maps/NewBarkTown/scripts.pory"
@                 and removeobject SETS the template's flag. If they shared
# 543 "data/maps/NewBarkTown/scripts.pory"
@                 FLAG_TEMP_1 the fade in UBScene would hide the whole cast.
# 544 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_2  - battle outcome
# 545 "data/maps/NewBarkTown/scripts.pory"
@   VAR_TEMP_3  - the player's pick: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego.
# 546 "data/maps/NewBarkTown/scripts.pory"
@                 Survives the battle: coming back from a battle does not
# 547 "data/maps/NewBarkTown/scripts.pory"
@                 reload the map, so ClearTempFieldEventData does not run.
# 548 "data/maps/NewBarkTown/scripts.pory"
@ Checked 20/09/2026: this map used no FLAG_TEMP_* or VAR_TEMP_* at all
# 549 "data/maps/NewBarkTown/scripts.pory"
@ before this mission. VAR_TEMP_1 is skipped anyway, for uniformity with the
# 550 "data/maps/NewBarkTown/scripts.pory"
@ three earlier missions (there it is VAR_TEMP_TRANSFERRED_SPECIES).
# 551 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_TEMP_E is reserved by the engine to suppress the follower - never use it.
# 552 "data/maps/NewBarkTown/scripts.pory"
@
# 553 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: seven residents of this map (locals 1, 2, 4, 5, 6, 7, 8) now carry
# 554 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_EVENT_ULTRABEAST_NEWBARK in their map.json "flag" field. A removeobject
# 555 "data/maps/NewBarkTown/scripts.pory"
@ on ANY of them SETS that flag and empties the whole town, permanently.
# 556 "data/maps/NewBarkTown/scripts.pory"
@
# 557 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: never clear FLAG_HIDE_NEWBARK_RIVALMARILL. Locals 9, 10 and 11 -
# 558 "data/maps/NewBarkTown/scripts.pory"
@ the original Gold/Crystal and two Marill - are hidden behind it from the
# 559 "data/maps/NewBarkTown/scripts.pory"
@ rival battle onward (setflag at the first rival scene, plus the three
# 560 "data/maps/NewBarkTown/scripts.pory"
@ removeobject at VAR_RIVAL_STATE 2 -> 3). If it were ever cleared the player
# 561 "data/maps/NewBarkTown/scripts.pory"
@ would see a SECOND Gold/Crystal at (12,13) while the mission's one stands
# 562 "data/maps/NewBarkTown/scripts.pory"
@ at (21,13), and a stray Marill at (11,13) right beside Nihilego.
# 563 "data/maps/NewBarkTown/scripts.pory"
@
# 564 "data/maps/NewBarkTown/scripts.pory"
@ OBJECT BUDGET. OBJECT_EVENTS_COUNT is 16 and includes the player
# 565 "data/maps/NewBarkTown/scripts.pory"
@ (include/constants/global.h:83). During the incident the road holds the
# 566 "data/maps/NewBarkTown/scripts.pory"
@ player, the follower and this mission's ten objects = 12/16. Four spare
# 567 "data/maps/NewBarkTown/scripts.pory"
@ slots, and every object added here spends one.
# 568 "data/maps/NewBarkTown/scripts.pory"
@
# 569 "data/maps/NewBarkTown/scripts.pory"
@ The four OBJ_EVENT_GFX_LIGHT_SPRITE on this map cost NOTHING against that
# 570 "data/maps/NewBarkTown/scripts.pory"
@ 16. TrySpawnObjectEvents special-cases them (src/event_object_movement.c:
# 571 "data/maps/NewBarkTown/scripts.pory"
@ 3168): a light sprite goes to SpawnLightSprite, which CreateSprite()s into
# 572 "data/maps/NewBarkTown/scripts.pory"
@ gSprites[] and never touches gObjectEvents[]. So the lamps keep their own
# 573 "data/maps/NewBarkTown/scripts.pory"
@ FLAG_NIGHT_POKEMON and this mission does not touch the lighting system at
# 574 "data/maps/NewBarkTown/scripts.pory"
@ all. Do not "free up slots" by hiding them - there is nothing to free.
# 575 "data/maps/NewBarkTown/scripts.pory"
@
# 576 "data/maps/NewBarkTown/scripts.pory"
@ What the budget DOES matter for: an object that does not fit simply fails
# 577 "data/maps/NewBarkTown/scripts.pory"
@ to spawn, with no error and no warning, and TrySpawnObjectEvents walks the
# 578 "data/maps/NewBarkTown/scripts.pory"
@ templates IN ORDER - so the ones that would lose are this mission's
# 579 "data/maps/NewBarkTown/scripts.pory"
@ (locals 16-25), the LAST in the array. Overspend and Looker is the one who
# 580 "data/maps/NewBarkTown/scripts.pory"
@ goes missing, which leaves the mission with no way to start.
# 581 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 582 "data/maps/NewBarkTown/scripts.pory"

# 583 "data/maps/NewBarkTown/scripts.pory"
@ Called from NewBarkTown_OnTransition, which runs before any object spawns -
# 584 "data/maps/NewBarkTown/scripts.pory"
@ so setflag/clearflag work here and removeobject would not. Temps are zeroed
# 585 "data/maps/NewBarkTown/scripts.pory"
@ on every load, so this recomputes from scratch every time.
# 586 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_ApplyUBVisibility::
# 587 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_2                        @ the beasts: only the cutscene brings them in
# 588 "data/maps/NewBarkTown/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_HideUBCast
# 589 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_1
# 590 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 591 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 592 "data/maps/NewBarkTown/scripts.pory"
	return
# 593 "data/maps/NewBarkTown/scripts.pory"

# 594 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_HideUBCast::
# 595 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_1
# 596 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_3
# 597 "data/maps/NewBarkTown/scripts.pory"
	setflag FLAG_TEMP_4
# 598 "data/maps/NewBarkTown/scripts.pory"
	return
# 599 "data/maps/NewBarkTown/scripts.pory"

# 600 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 601 "data/maps/NewBarkTown/scripts.pory"
@ Idle conversations, available from the moment the player reaches town and
# 602 "data/maps/NewBarkTown/scripts.pory"
@ until the YES. Each one ends by turning the actor back to the facing its
# 603 "data/maps/NewBarkTown/scripts.pory"
@ map.json template asks for, so a talk from an odd tile cannot leave anyone
# 604 "data/maps/NewBarkTown/scripts.pory"
@ crooked when the cutscene starts.
# 605 "data/maps/NewBarkTown/scripts.pory"
@ SKELETON: every line below is placeholder. Rewrite in the design's voice
# 606 "data/maps/NewBarkTown/scripts.pory"
@ (section 3.1): Looker theatrical and warm, Anabel precise, Lusamine formal
# 607 "data/maps/NewBarkTown/scripts.pory"
@ and rehearsed, Elm apologetic, Mom plain.
# 608 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 609 "data/maps/NewBarkTown/scripts.pory"

# 610 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine alone on the road in, at (3,12), reachable from (2,12), (4,12),
# 611 "data/maps/NewBarkTown/scripts.pory"
@ (3,11) and (3,13). This is her first spoken line in the whole arc and the
# 612 "data/maps/NewBarkTown/scripts.pory"
@ beat Mission 3's hook promised: the player meets her BEFORE the emergency.
# 613 "data/maps/NewBarkTown/scripts.pory"
@ She gives away nothing about the knot in UBKnot.
# 614 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLusamine::
# 615 "data/maps/NewBarkTown/scripts.pory"
	lock
# 616 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 617 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineIdle, MSGBOX_DEFAULT
# 618 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 619 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST     @ map.json FACE_RIGHT
# 620 "data/maps/NewBarkTown/scripts.pory"
	release
# 621 "data/maps/NewBarkTown/scripts.pory"
	end
# 622 "data/maps/NewBarkTown/scripts.pory"

# 623 "data/maps/NewBarkTown/scripts.pory"
@ Elm at (11,10), outside his own lab door (10,9).
# 624 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBElm::
# 625 "data/maps/NewBarkTown/scripts.pory"
	lock
# 626 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 627 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmIdle, MSGBOX_DEFAULT
# 628 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 629 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_SOUTH         @ map.json FACE_DOWN
# 630 "data/maps/NewBarkTown/scripts.pory"
	release
# 631 "data/maps/NewBarkTown/scripts.pory"
	end
# 632 "data/maps/NewBarkTown/scripts.pory"

# 633 "data/maps/NewBarkTown/scripts.pory"
@ Mom at (19,12), reachable from (18,12) and (19,13); (19,11) is wall.
# 634 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBMom::
# 635 "data/maps/NewBarkTown/scripts.pory"
	lock
# 636 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 637 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomIdle, MSGBOX_DEFAULT
# 638 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 639 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST          @ map.json FACE_RIGHT
# 640 "data/maps/NewBarkTown/scripts.pory"
	release
# 641 "data/maps/NewBarkTown/scripts.pory"
	end
# 642 "data/maps/NewBarkTown/scripts.pory"

# 643 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal at (21,13), reachable from (20,13) and (21,14). They ask to be
# 644 "data/maps/NewBarkTown/scripts.pory"
@ put in the fight HERE, early - and the refusal comes later, on camera, in
# 645 "data/maps/NewBarkTown/scripts.pory"
@ NewBarkTown_EventScript_UBRivalRefused. Do not delete either half.
# 646 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRival::
# 647 "data/maps/NewBarkTown/scripts.pory"
	lock
# 648 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 649 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalIdle, MSGBOX_DEFAULT
# 650 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 651 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_NORTH       @ map.json FACE_UP
# 652 "data/maps/NewBarkTown/scripts.pory"
	release
# 653 "data/maps/NewBarkTown/scripts.pory"
	end
# 654 "data/maps/NewBarkTown/scripts.pory"

# 655 "data/maps/NewBarkTown/scripts.pory"
@ Anabel at (22,12). Looker fills (21,12), Marill fills (22,13) and (22,11)
# 656 "data/maps/NewBarkTown/scripts.pory"
@ is wall, so the only way to her is the long way round: (20,13) -> (20,14)
# 657 "data/maps/NewBarkTown/scripts.pory"
@ -> east along y=14 -> (23,14) -> (23,13) -> (23,12).
# 658 "data/maps/NewBarkTown/scripts.pory"
@ She plants NOTHING here. The seeds were sown in Missions 2 and 3 and in the
# 659 "data/maps/NewBarkTown/scripts.pory"
@ Olivine briefing; the next time she touches the subject is the reveal.
# 660 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabel::
# 661 "data/maps/NewBarkTown/scripts.pory"
	lock
# 662 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 663 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 664 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 665 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST       @ map.json FACE_LEFT
# 666 "data/maps/NewBarkTown/scripts.pory"
	release
# 667 "data/maps/NewBarkTown/scripts.pory"
	end
# 668 "data/maps/NewBarkTown/scripts.pory"

# 669 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 670 "data/maps/NewBarkTown/scripts.pory"
@ The cutscene. Everything from the YES onward is scripted through to a
# 671 "data/maps/NewBarkTown/scripts.pory"
@ battle outcome.
# 672 "data/maps/NewBarkTown/scripts.pory"
@ ----------------------------------------------------------------------------
# 673 "data/maps/NewBarkTown/scripts.pory"

# 674 "data/maps/NewBarkTown/scripts.pory"
@ Only reachable from (20,12) facing east (see LOOKER'S POCKET above), so no
# 675 "data/maps/NewBarkTown/scripts.pory"
@ getplayerxy check is needed.
# 676 "data/maps/NewBarkTown/scripts.pory"
@ NOTHING changes state before the YES. The YES is the last exit point.
# 677 "data/maps/NewBarkTown/scripts.pory"
@ Elm's countdown is read out BEFORE the YES on purpose - it is the clock
# 678 "data/maps/NewBarkTown/scripts.pory"
@ that turns "three rifts" into "now", the same job Lillie's read did in
# 679 "data/maps/NewBarkTown/scripts.pory"
@ Mission 2 and Kukui's in Mission 3.
# 680 "data/maps/NewBarkTown/scripts.pory"
@ But Elm himself is still at (11,10), nine tiles west and off camera, so
# 681 "data/maps/NewBarkTown/scripts.pory"
@ ANABEL relays his log here and Elm only speaks for himself once he has
# 682 "data/maps/NewBarkTown/scripts.pory"
@ walked into frame in UBScene. Do not move his own voice back up here
# 683 "data/maps/NewBarkTown/scripts.pory"
@ without also moving his object.
# 684 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBLooker::
# 685 "data/maps/NewBarkTown/scripts.pory"
	lock
# 686 "data/maps/NewBarkTown/scripts.pory"
	faceplayer
# 687 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLookerGreet, MSGBOX_DEFAULT
# 688 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBClockRelay, MSGBOX_DEFAULT
# 689 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBReady, MSGBOX_YESNO
# 690 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBNotReady
# 691 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBScene
# 692 "data/maps/NewBarkTown/scripts.pory"

# 693 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBNotReady::
# 694 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBNotReady, MSGBOX_DEFAULT
# 695 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 696 "data/maps/NewBarkTown/scripts.pory"
	release
# 697 "data/maps/NewBarkTown/scripts.pory"
	end
# 698 "data/maps/NewBarkTown/scripts.pory"

# 699 "data/maps/NewBarkTown/scripts.pory"
@ A simple battle, so there is no party-size check to do, and the mission
# 700 "data/maps/NewBarkTown/scripts.pory"
@ hands out nothing, so the entregar-pokemon-ou-ovo space rule does not apply.
# 701 "data/maps/NewBarkTown/scripts.pory"
@
# 702 "data/maps/NewBarkTown/scripts.pory"
@ SKELETON: Elm and Lusamine arrive under a fade. Evolution: both of them
# 703 "data/maps/NewBarkTown/scripts.pory"
@ actually running in, with a long applymovement. The rift is a camera shake
# 704 "data/maps/NewBarkTown/scripts.pory"
@ plus a white flash and the three beasts appear standing still; evolution can
# 705 "data/maps/NewBarkTown/scripts.pory"
@ give it its own palette, weather and music, and open the three tears at
# 706 "data/maps/NewBarkTown/scripts.pory"
@ different moments.
# 707 "data/maps/NewBarkTown/scripts.pory"
@
# 708 "data/maps/NewBarkTown/scripts.pory"
@ NOBODY WALKS IN THIS SCENE. All seven cast members are already on their
# 709 "data/maps/NewBarkTown/scripts.pory"
@ final tiles and the two who are not simply appear there. That is what makes
# 710 "data/maps/NewBarkTown/scripts.pory"
@ a scene with twice Mission 3's cast cheaper to stage than Mission 3 was.
# 711 "data/maps/NewBarkTown/scripts.pory"
@
# 712 "data/maps/NewBarkTown/scripts.pory"
@ WARNING: setobjectxy DOES NOT WORK HERE AND FAILS SILENTLY.
# 713 "data/maps/NewBarkTown/scripts.pory"
@ TryMoveObjectEventToMapCoords (src/event_object_movement.c:3812) only acts
# 714 "data/maps/NewBarkTown/scripts.pory"
@ on a SPAWNED object, and spawning only happens near the camera
# 715 "data/maps/NewBarkTown/scripts.pory"
@ (TrySpawnObjectEvents, :3148). Elm at (11,10) is on the edge of that window
# 716 "data/maps/NewBarkTown/scripts.pory"
@ and Lusamine at (3,12) is far outside it. The template has to be moved
# 717 "data/maps/NewBarkTown/scripts.pory"
@ instead, and the object re-spawned:
# 718 "data/maps/NewBarkTown/scripts.pory"
@   removeobject      - a no-op if it was never spawned; if it WAS spawned it
# 719 "data/maps/NewBarkTown/scripts.pory"
@                       sets only that actor's own FLAG_TEMP_3/4 (which is
# 720 "data/maps/NewBarkTown/scripts.pory"
@                       exactly why those two do not share FLAG_TEMP_1)
# 721 "data/maps/NewBarkTown/scripts.pory"
@   setobjectxyperm   - moves the TEMPLATE; holds while the map stays loaded
# 722 "data/maps/NewBarkTown/scripts.pory"
@   clearflag + addobject - spawns it at the new place
# 723 "data/maps/NewBarkTown/scripts.pory"
@ The order is mandatory and the trio is correct whether or not the actor
# 724 "data/maps/NewBarkTown/scripts.pory"
@ happened to be spawned. Anyone who "simplifies" this into a setobjectxy
# 725 "data/maps/NewBarkTown/scripts.pory"
@ will watch Lusamine never appear, with no error at all.
# 726 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBScene::
# 727 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 728 "data/maps/NewBarkTown/scripts.pory"
	lockall
# 729 "data/maps/NewBarkTown/scripts.pory"
	hidefollower
# 730 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 731 "data/maps/NewBarkTown/scripts.pory"
	@ Elm (11,10) -> (23,12), then faces west at the line of people.
# 732 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_ELM
# 733 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_ELM, 23, 12
# 734 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_3
# 735 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_ELM
# 736 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_WEST
# 737 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine (3,12) -> (18,12), then faces east at Mom and the player.
# 738 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_LUSAMINE
# 739 "data/maps/NewBarkTown/scripts.pory"
	setobjectxyperm LOCALID_NEWBARK_UB_LUSAMINE, 18, 12
# 740 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_4
# 741 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_LUSAMINE
# 742 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 743 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 744 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBTheyArrive, MSGBOX_DEFAULT
# 745 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 746 "data/maps/NewBarkTown/scripts.pory"
	@ Tremor, then the white flash that brings all three in at once.
# 747 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8004, 2   @ vertical pan
# 748 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 749 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8006, 32  @ num shakes
# 750 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 751 "data/maps/NewBarkTown/scripts.pory"
	special ShakeCamera
# 752 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 753 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_WHITE
# 754 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_TEMP_2
# 755 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_KARTANA
# 756 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_GUZZLORD
# 757 "data/maps/NewBarkTown/scripts.pory"
	addobject LOCALID_NEWBARK_UB_NIHILEGO
# 758 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_FROM_WHITE
# 759 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 760 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 761 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 762 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 763 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 764 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 765 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAppear, MSGBOX_DEFAULT
# 766 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 767 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBKnot
# 768 "data/maps/NewBarkTown/scripts.pory"

# 769 "data/maps/NewBarkTown/scripts.pory"
@ The knot: Lusamine means to take all three, and Mom is the one who stops
# 770 "data/maps/NewBarkTown/scripts.pory"
@ her. The closemessage above is load-bearing - without it Lusamine's step
# 771 "data/maps/NewBarkTown/scripts.pory"
@ would play behind an open text box.
# 772 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBKnot::
# 773 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine (18,12) -> (17,12), one step west toward the rifts. (17,12) is
# 774 "data/maps/NewBarkTown/scripts.pory"
	@ clear and still well inside the camera (x >= 13 with the player at 20).
# 775 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_StepLeftFaceLeft
# 776 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
# 777 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineTakesThree, MSGBOX_DEFAULT
# 778 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 779 "data/maps/NewBarkTown/scripts.pory"
	@ Mom (19,12) turns her back on her own child to face Lusamine at (17,12).
# 780 "data/maps/NewBarkTown/scripts.pory"
	@ x 17 < 19, so west. The turn IS the beat - do not shorten it away.
# 781 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
# 782 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMomStopsHer, MSGBOX_DEFAULT
# 783 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 784 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
# 785 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBLusamineAsks, MSGBOX_DEFAULT
# 786 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAnabelReveal
# 787 "data/maps/NewBarkTown/scripts.pory"

# 788 "data/maps/NewBarkTown/scripts.pory"
@ Anabel's reveal, between Lusamine's question and the player's choice, per
# 789 "data/maps/NewBarkTown/scripts.pory"
@ the seven beats of design section 3.1 (V17). It is NOT a flashback, it sets
# 790 "data/maps/NewBarkTown/scripts.pory"
@ no flag, and it does not pause the mission.
# 791 "data/maps/NewBarkTown/scripts.pory"
@ Looker is at (21,12) and Anabel at (22,12), right beside him, so he does
# 792 "data/maps/NewBarkTown/scripts.pory"
@ not need to walk to catch her: the exclamation mark and a turn are enough.
# 793 "data/maps/NewBarkTown/scripts.pory"
@ x 22 > 21 -> east to her, x 20 < 21 -> west to come back to the player.
# 794 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAnabelReveal::
# 795 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelBreaks, MSGBOX_DEFAULT
# 796 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 797 "data/maps/NewBarkTown/scripts.pory"
	playse SE_PIN
# 798 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_LOOKER, Common_Movement_ExclamationMark
# 799 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_LOOKER
# 800 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_EAST
# 801 "data/maps/NewBarkTown/scripts.pory"
	delay 30
# 802 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelFaller, MSGBOX_DEFAULT
# 803 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 804 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST      @ back to the player
# 805 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAnabelPicks, MSGBOX_DEFAULT
# 806 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 807 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBRivalRefused
# 808 "data/maps/NewBarkTown/scripts.pory"

# 809 "data/maps/NewBarkTown/scripts.pory"
@ Pays off the idle line: Gold/Crystal asked to be put in the fight, so the
# 810 "data/maps/NewBarkTown/scripts.pory"
@ refusal has to happen on camera or the promise is dropped.
# 811 "data/maps/NewBarkTown/scripts.pory"
@ Gold/Crystal sit at (21,13), diagonally below-right of the player at
# 812 "data/maps/NewBarkTown/scripts.pory"
@ (20,12). There is no cardinal direction that points at the player, so they
# 813 "data/maps/NewBarkTown/scripts.pory"
@ turn WEST - onto the player's column - which reads as turning to them.
# 814 "data/maps/NewBarkTown/scripts.pory"
@ Nobody is at (20,13), so nothing is hidden behind the text box.
# 815 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBRivalRefused::
# 816 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_WEST
# 817 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalAsks, MSGBOX_DEFAULT
# 818 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 819 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRivalRefused, MSGBOX_DEFAULT
# 820 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 821 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBChoose
# 822 "data/maps/NewBarkTown/scripts.pory"

# 823 "data/maps/NewBarkTown/scripts.pory"
@ Standard Rift Mission structure: the player picks which Ultra Beast to
# 824 "data/maps/NewBarkTown/scripts.pory"
@ fight and the companions take the rest. No cancel (ignoreBPress TRUE) - the
# 825 "data/maps/NewBarkTown/scripts.pory"
@ scene has already started, so VAR_RESULT can only be 0, 1 or 2.
# 826 "data/maps/NewBarkTown/scripts.pory"
@ maxBeforeScroll 3 so all three fit without scrolling. dynmultichoice takes
# 827 "data/maps/NewBarkTown/scripts.pory"
@ a vararg list (asm/macros/event.inc:1942), so three items need nothing new.
# 828 "data/maps/NewBarkTown/scripts.pory"
@ The pick is per attempt: after a blackout the player chooses again.
# 829 "data/maps/NewBarkTown/scripts.pory"
@
# 830 "data/maps/NewBarkTown/scripts.pory"
@ DISTRIBUTION - design section 6.4. Lusamine keeps Nihilego whenever the
# 831 "data/maps/NewBarkTown/scripts.pory"
@ player does not take it; it is the one she came for and the one she has to
# 832 "data/maps/NewBarkTown/scripts.pory"
@ answer for. This is a character decision, not convenience:
# 833 "data/maps/NewBarkTown/scripts.pory"
@   pick 0 Kartana   -> Lusamine Nihilego, Anabel Guzzlord
# 834 "data/maps/NewBarkTown/scripts.pory"
@   pick 1 Guzzlord  -> Lusamine Nihilego, Anabel Kartana
# 835 "data/maps/NewBarkTown/scripts.pory"
@   pick 2 Nihilego  -> Lusamine Guzzlord, Anabel Kartana
# 836 "data/maps/NewBarkTown/scripts.pory"
@ Each UBPicked* line SAYS which two the others take, so the table is
# 837 "data/maps/NewBarkTown/scripts.pory"
@ readable from inside the game and not only from this comment.
# 838 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBChoose::
# 839 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 840 "data/maps/NewBarkTown/scripts.pory"
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_Text_ChoiceKartana, NewBarkTown_Text_ChoiceGuzzlord, NewBarkTown_Text_ChoiceNihilego
# 841 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 Kartana, 1 Guzzlord, 2 Nihilego
# 842 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 843 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPickGuzzlord
# 844 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPickNihilego
# 845 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
# 846 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_KARTANA
# 847 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedKartana, MSGBOX_DEFAULT
# 848 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 849 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 850 "data/maps/NewBarkTown/scripts.pory"

# 851 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickGuzzlord::
# 852 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
# 853 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
# 854 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedGuzzlord, MSGBOX_DEFAULT
# 855 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 856 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 857 "data/maps/NewBarkTown/scripts.pory"

# 858 "data/maps/NewBarkTown/scripts.pory"
@ The one branch where Lusamine loses the beast she came for. ONE line, and
# 859 "data/maps/NewBarkTown/scripts.pory"
@ she takes it - design section 6.4. Do not turn this into an argument.
# 860 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBPickNihilego::
# 861 "data/maps/NewBarkTown/scripts.pory"
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
# 862 "data/maps/NewBarkTown/scripts.pory"
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
# 863 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBPickedNihilego, MSGBOX_DEFAULT
# 864 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 865 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBBattle
# 866 "data/maps/NewBarkTown/scripts.pory"

# 867 "data/maps/NewBarkTown/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 868 "data/maps/NewBarkTown/scripts.pory"
@ battle - the other reason every mission splits the beasts up.
# 869 "data/maps/NewBarkTown/scripts.pory"
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
# 870 "data/maps/NewBarkTown/scripts.pory"
@ losing means a blackout and a retry. Running is not blocked either - "Run"
# 871 "data/maps/NewBarkTown/scripts.pory"
@ in a boss is explicit forfeiting (CanPlayerForfeitBattle, src/battle_main.c)
# 872 "data/maps/NewBarkTown/scripts.pory"
@ and becomes B_OUTCOME_FORFEITED, which counts as a loss.
# 873 "data/maps/NewBarkTown/scripts.pory"
@
# 874 "data/maps/NewBarkTown/scripts.pory"
@ NOT a skeleton: the numbers below are the target. Fourth step of the ladder
# 875 "data/maps/NewBarkTown/scripts.pory"
@ after Blackthorn (2 bars / Lv70 / x110), Mahogany (4 / Lv80 / x130) and
# 876 "data/maps/NewBarkTown/scripts.pory"
@ Cherrygrove (4 / Lv85 / x140). The bars have been at MAX_BOSS_HEALTH_BARS
# 877 "data/maps/NewBarkTown/scripts.pory"
@ since Mission 2, so the step up here is level, multiplier and a two-axis
# 878 "data/maps/NewBarkTown/scripts.pory"
@ moveset plus a held item.
# 879 "data/maps/NewBarkTown/scripts.pory"
@ CAVEAT (design section 6): x140 has never actually been played. If the
# 880 "data/maps/NewBarkTown/scripts.pory"
@ Mission 3 playtest says x140 is already a wall, THIS number inherits the
# 881 "data/maps/NewBarkTown/scripts.pory"
@ correction instead of going up. Turn the screws in this order, one at a
# 882 "data/maps/NewBarkTown/scripts.pory"
@ time:
# 883 "data/maps/NewBarkTown/scripts.pory"
@   1. drop the held item from the boss that gets complained about
# 884 "data/maps/NewBarkTown/scripts.pory"
@   2. multiplier 150 -> 145 -> 140
# 885 "data/maps/NewBarkTown/scripts.pory"
@   3. swap the setup/control move for a fourth attacking move
# 886 "data/maps/NewBarkTown/scripts.pory"
@   4. level 90 -> 85
# 887 "data/maps/NewBarkTown/scripts.pory"
@ The bars are at the ceiling and are not a screw.
# 888 "data/maps/NewBarkTown/scripts.pory"
@
# 889 "data/maps/NewBarkTown/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 890 "data/maps/NewBarkTown/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 891 "data/maps/NewBarkTown/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between, so no
# 892 "data/maps/NewBarkTown/scripts.pory"
@ clearbossbattle is needed.
# 893 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBBattle::
# 894 "data/maps/NewBarkTown/scripts.pory"
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
# 895 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBSetupGuzzlord
# 896 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBSetupNihilego
# 897 "data/maps/NewBarkTown/scripts.pory"
	@ Kartana - the one that CLIMBS. Paper defenses, Swords Dance, a pure
# 898 "data/maps/NewBarkTown/scripts.pory"
	@ damage item: it either snowballs or it dies.
# 899 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 900 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
# 901 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 902 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_KARTANA, 90, ITEM_MUSCLE_BAND
# 903 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_SACRED_SWORD, MOVE_SMART_STRIKE
# 904 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 905 "data/maps/NewBarkTown/scripts.pory"

# 906 "data/maps/NewBarkTown/scripts.pory"
@ Guzzlord - the one that ENDURES. Absurd HP, Leftovers and Toxic: attrition.
# 907 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupGuzzlord::
# 908 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 909 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
# 910 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 911 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_GUZZLORD, 90, ITEM_LEFTOVERS
# 912 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_TOXIC, MOVE_CRUNCH, MOVE_HEAVY_SLAM, MOVE_DRAGON_TAIL
# 913 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBStartBattle
# 914 "data/maps/NewBarkTown/scripts.pory"

# 915 "data/maps/NewBarkTown/scripts.pory"
@ Nihilego - the one that INTERFERES. Acid Spray shreds the player's Sp.Def,
# 916 "data/maps/NewBarkTown/scripts.pory"
@ Toxic stacks on top, and Black Sludge heals it for being Poison.
# 917 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBSetupNihilego::
# 918 "data/maps/NewBarkTown/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
# 919 "data/maps/NewBarkTown/scripts.pory"
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
# 920 "data/maps/NewBarkTown/scripts.pory"
	waitmoncry
# 921 "data/maps/NewBarkTown/scripts.pory"
	seteventmon SPECIES_NIHILEGO, 90, ITEM_BLACK_SLUDGE
# 922 "data/maps/NewBarkTown/scripts.pory"
	seteventmonmoves MOVE_ACID_SPRAY, MOVE_TOXIC, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE
# 923 "data/maps/NewBarkTown/scripts.pory"

# 924 "data/maps/NewBarkTown/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the
# 925 "data/maps/NewBarkTown/scripts.pory"
@ player out and hands them back HEALED at (20,12) (DoWhiteOut calls
# 926 "data/maps/NewBarkTown/scripts.pory"
@ HealPlayerParty itself, src/overworld.c:384; it does not need a Center
# 927 "data/maps/NewBarkTown/scripts.pory"
@ counter, and New Bark has no Center at all). CAUGHT and RAN are unreachable
# 928 "data/maps/NewBarkTown/scripts.pory"
@ (ball blocked; Run becomes FORFEITED in a boss) but are handled anyway:
# 929 "data/maps/NewBarkTown/scripts.pory"
@ anything that is not WON restarts the scene, and nothing wins it by default.
# 930 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBStartBattle::
# 931 "data/maps/NewBarkTown/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 932 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 933 "data/maps/NewBarkTown/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 934 "data/maps/NewBarkTown/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 935 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, NewBarkTown_EventScript_UBResolved
# 936 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBUnresolved
# 937 "data/maps/NewBarkTown/scripts.pory"

# 938 "data/maps/NewBarkTown/scripts.pory"
@ Nothing was recorded as done: the event flag is still set, so reloading the
# 939 "data/maps/NewBarkTown/scripts.pory"
@ map puts the cast back on its map.json tiles with the beasts hidden again,
# 940 "data/maps/NewBarkTown/scripts.pory"
@ and talking to Looker restarts the whole scene - the pick included. The warp
# 941 "data/maps/NewBarkTown/scripts.pory"
@ also puts Elm and Lusamine back on their original template coordinates,
# 942 "data/maps/NewBarkTown/scripts.pory"
@ because LoadMapFromWarp re-reads the templates.
# 943 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBUnresolved::
# 944 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBGotAway, MSGBOX_DEFAULT
# 945 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 946 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 947 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 948 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 949 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 950 "data/maps/NewBarkTown/scripts.pory"
	end
# 951 "data/maps/NewBarkTown/scripts.pory"

# 952 "data/maps/NewBarkTown/scripts.pory"
@ Lusamine's fight and Anabel's are narrative: they resolve with the player's
# 953 "data/maps/NewBarkTown/scripts.pory"
@ win, and only the lines afterwards change with the pick.
# 954 "data/maps/NewBarkTown/scripts.pory"
@ SKELETON: evolution can stage them on screen. A real battle against either
# 955 "data/maps/NewBarkTown/scripts.pory"
@ of them is NOT the plan - Lusamine's is reserved for design sections 7/9.
# 956 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBResolved::
# 957 "data/maps/NewBarkTown/scripts.pory"
	@ All three beast objects are still on the map: a battle does not reload
# 958 "data/maps/NewBarkTown/scripts.pory"
	@ it. Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
# 959 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_WHITE
# 960 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_KARTANA
# 961 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_GUZZLORD
# 962 "data/maps/NewBarkTown/scripts.pory"
	removeobject LOCALID_NEWBARK_UB_NIHILEGO
# 963 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_FROM_WHITE
# 964 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAfterGuzzlord
# 965 "data/maps/NewBarkTown/scripts.pory"
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBAfterNihilego
# 966 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterKartana, MSGBOX_DEFAULT
# 967 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAftermath
# 968 "data/maps/NewBarkTown/scripts.pory"

# 969 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterGuzzlord::
# 970 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterGuzzlord, MSGBOX_DEFAULT
# 971 "data/maps/NewBarkTown/scripts.pory"
	goto NewBarkTown_EventScript_UBAftermath
# 972 "data/maps/NewBarkTown/scripts.pory"

# 973 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAfterNihilego::
# 974 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBAfterNihilego, MSGBOX_DEFAULT
# 975 "data/maps/NewBarkTown/scripts.pory"

# 976 "data/maps/NewBarkTown/scripts.pory"
@ Four short beats: the cost (Elm), what the protagonist cannot say out loud
# 977 "data/maps/NewBarkTown/scripts.pory"
@ (Gold/Crystal), Mom, and the hook. Nobody walks: everyone is already on the
# 978 "data/maps/NewBarkTown/scripts.pory"
@ line and nobody is at (20,13), so the text box hides no one.
# 979 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_EventScript_UBAftermath::
# 980 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBElmCost, MSGBOX_DEFAULT
# 981 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 982 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_WEST     @ onto the player's column
# 983 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBRival, MSGBOX_DEFAULT
# 984 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 985 "data/maps/NewBarkTown/scripts.pory"
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST       @ back to facing her child
# 986 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBMom, MSGBOX_DEFAULT
# 987 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 988 "data/maps/NewBarkTown/scripts.pory"
	msgbox NewBarkTown_Text_UBHook, MSGBOX_DEFAULT
# 989 "data/maps/NewBarkTown/scripts.pory"
	closemessage
# 990 "data/maps/NewBarkTown/scripts.pory"
	fadescreen FADE_TO_BLACK
# 991 "data/maps/NewBarkTown/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_NEWBARK   @ invariant: flag and var together
# 992 "data/maps/NewBarkTown/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 10
# 993 "data/maps/NewBarkTown/scripts.pory"
	@ Reload in place under the fade. The seven residents come back, the lamps
# 994 "data/maps/NewBarkTown/scripts.pory"
	@ go back to depending on the clock alone, the cast disappears, Elm and
# 995 "data/maps/NewBarkTown/scripts.pory"
	@ Lusamine return to their template tiles, and the follower comes back
# 996 "data/maps/NewBarkTown/scripts.pory"
	@ (undoing the hidefollower). Without this the whole town would pop back
# 997 "data/maps/NewBarkTown/scripts.pory"
	@ in piece by piece as the camera moved.
# 998 "data/maps/NewBarkTown/scripts.pory"
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
# 999 "data/maps/NewBarkTown/scripts.pory"
	waitstate
# 1000 "data/maps/NewBarkTown/scripts.pory"
	releaseall
# 1001 "data/maps/NewBarkTown/scripts.pory"
	end
# 1002 "data/maps/NewBarkTown/scripts.pory"

# 1003 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Movement_StepLeftFaceLeft:
# 1004 "data/maps/NewBarkTown/scripts.pory"
	walk_left
# 1005 "data/maps/NewBarkTown/scripts.pory"
	face_left
# 1006 "data/maps/NewBarkTown/scripts.pory"
	step_end

# 1009 "data/maps/NewBarkTown/scripts.pory"

# 1010 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 1011 "data/maps/NewBarkTown/scripts.pory"
@ Rift Mission 4 dialogue.
# 1012 "data/maps/NewBarkTown/scripts.pory"
@ SKELETON: every string below is placeholder. Rewrite in the design's voice
# 1013 "data/maps/NewBarkTown/scripts.pory"
@ (section 3.1). Keep the speaker's name at the head of each box, keep the
# 1014 "data/maps/NewBarkTown/scripts.pory"
@ two gender-neutral rival texts free of any name, and keep UBHook pointing
# 1015 "data/maps/NewBarkTown/scripts.pory"
@ at the Olivine reunion (design section 7) - it is the hook the next
# 1016 "data/maps/NewBarkTown/scripts.pory"
@ document picks up.
# 1017 "data/maps/NewBarkTown/scripts.pory"
@ ============================================================================
# 1018 "data/maps/NewBarkTown/scripts.pory"

# 1019 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineIdle:
# 1020 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: You are taller than\n"
# 1021 "data/maps/NewBarkTown/scripts.pory"
	.string "the photographs.\p"
# 1022 "data/maps/NewBarkTown/scripts.pory"
	.string "…Forgive me. I have practiced\n"
# 1023 "data/maps/NewBarkTown/scripts.pory"
	.string "this, and I am still doing it\l"
# 1024 "data/maps/NewBarkTown/scripts.pory"
	.string "badly.\p"
# 1025 "data/maps/NewBarkTown/scripts.pory"
	.string "Lillie writes about you.\p"
# 1026 "data/maps/NewBarkTown/scripts.pory"
	.string "Gladion does not write, but he\n"
# 1027 "data/maps/NewBarkTown/scripts.pory"
	.string "mentions you, which from him is\l"
# 1028 "data/maps/NewBarkTown/scripts.pory"
	.string "the same thing.\p"
# 1029 "data/maps/NewBarkTown/scripts.pory"
	.string "We will talk properly when this\n"
# 1030 "data/maps/NewBarkTown/scripts.pory"
	.string "is over.\p"
# 1031 "data/maps/NewBarkTown/scripts.pory"
	.string "If I am still someone you want\n"
# 1032 "data/maps/NewBarkTown/scripts.pory"
	.string "to talk to.$"
# 1033 "data/maps/NewBarkTown/scripts.pory"

# 1034 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmIdle:
# 1035 "data/maps/NewBarkTown/scripts.pory"
	.string "Elm: Six weeks.\p"
# 1036 "data/maps/NewBarkTown/scripts.pory"
	.string "Six weeks of the same reading,\n"
# 1037 "data/maps/NewBarkTown/scripts.pory"
	.string "and every time I wrote “check\l"
# 1038 "data/maps/NewBarkTown/scripts.pory"
	.string "the sensor” in the margin.\p"
# 1039 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor Kukui's notes came\n"
# 1040 "data/maps/NewBarkTown/scripts.pory"
	.string "this morning.\p"
# 1041 "data/maps/NewBarkTown/scripts.pory"
	.string "I ran them against my log,\n"
# 1042 "data/maps/NewBarkTown/scripts.pory"
	.string "and… it isn't the sensor.\p"
# 1043 "data/maps/NewBarkTown/scripts.pory"
	.string "It never was.\p"
# 1044 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone who would come is in\n"
# 1045 "data/maps/NewBarkTown/scripts.pory"
	.string "the lab. It's the strongest\l"
# 1046 "data/maps/NewBarkTown/scripts.pory"
	.string "building in town, which is not\l"
# 1047 "data/maps/NewBarkTown/scripts.pory"
	.string "saying much.$"
# 1048 "data/maps/NewBarkTown/scripts.pory"

# 1049 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomIdle:
# 1050 "data/maps/NewBarkTown/scripts.pory"
	.string "Mom: I'm not going into the\n"
# 1051 "data/maps/NewBarkTown/scripts.pory"
	.string "lab, {PLAYER}.\p"
# 1052 "data/maps/NewBarkTown/scripts.pory"
	.string "Don't ask me again.\p"
# 1053 "data/maps/NewBarkTown/scripts.pory"
	.string "I've been watching that road\n"
# 1054 "data/maps/NewBarkTown/scripts.pory"
	.string "for two years.\p"
# 1055 "data/maps/NewBarkTown/scripts.pory"
	.string "I know how to watch a road.$"
# 1056 "data/maps/NewBarkTown/scripts.pory"

# 1057 "data/maps/NewBarkTown/scripts.pory"
@ No name: this text serves both Gold and Crystal.
# 1058 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalIdle:
# 1059 "data/maps/NewBarkTown/scripts.pory"
	.string "Every house on this street,\n"
# 1060 "data/maps/NewBarkTown/scripts.pory"
	.string "twice.\p"
# 1061 "data/maps/NewBarkTown/scripts.pory"
	.string "The Hanlons wouldn't open the\n"
# 1062 "data/maps/NewBarkTown/scripts.pory"
	.string "door until I said your name.\p"
# 1063 "data/maps/NewBarkTown/scripts.pory"
	.string "Hey - when it starts, put me\n"
# 1064 "data/maps/NewBarkTown/scripts.pory"
	.string "in.\p"
# 1065 "data/maps/NewBarkTown/scripts.pory"
	.string "I've got a full team. I've had\n"
# 1066 "data/maps/NewBarkTown/scripts.pory"
	.string "a full team for a year.$"
# 1067 "data/maps/NewBarkTown/scripts.pory"

# 1068 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelIdle:
# 1069 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Three signatures, and\n"
# 1070 "data/maps/NewBarkTown/scripts.pory"
	.string "they are breathing together.\p"
# 1071 "data/maps/NewBarkTown/scripts.pory"
	.string "In, and out.\p"
# 1072 "data/maps/NewBarkTown/scripts.pory"
	.string "I have never seen that.\p"
# 1073 "data/maps/NewBarkTown/scripts.pory"
	.string "Stay on this street.\p"
# 1074 "data/maps/NewBarkTown/scripts.pory"
	.string "If I tell you to move, move\n"
# 1075 "data/maps/NewBarkTown/scripts.pory"
	.string "first and ask me after.$"
# 1076 "data/maps/NewBarkTown/scripts.pory"

# 1077 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLookerGreet:
# 1078 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: {PLAYER}. Right on your\n"
# 1079 "data/maps/NewBarkTown/scripts.pory"
	.string "own doorstep.\p"
# 1080 "data/maps/NewBarkTown/scripts.pory"
	.string "I have worked a great many\n"
# 1081 "data/maps/NewBarkTown/scripts.pory"
	.string "streets, and I have never liked\l"
# 1082 "data/maps/NewBarkTown/scripts.pory"
	.string "one less than this.$"
# 1083 "data/maps/NewBarkTown/scripts.pory"

# 1084 "data/maps/NewBarkTown/scripts.pory"
@ Elm is still at (11,10) and off camera at this point, so Anabel reads his
# 1085 "data/maps/NewBarkTown/scripts.pory"
@ log out for him. His own voice arrives with his object, in UBTheyArrive.
# 1086 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBClockRelay:
# 1087 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: The Professor called it\n"
# 1088 "data/maps/NewBarkTown/scripts.pory"
	.string "in four minutes ago.\p"
# 1089 "data/maps/NewBarkTown/scripts.pory"
	.string "Three minutes, he says. Maybe\n"
# 1090 "data/maps/NewBarkTown/scripts.pory"
	.string "four - the interval has been\l"
# 1091 "data/maps/NewBarkTown/scripts.pory"
	.string "shortening all morning.\p"
# 1092 "data/maps/NewBarkTown/scripts.pory"
	.string "All three breathe together.\p"
# 1093 "data/maps/NewBarkTown/scripts.pory"
	.string "That is what he could not see\n"
# 1094 "data/maps/NewBarkTown/scripts.pory"
	.string "in six weeks and Kukui saw in\l"
# 1095 "data/maps/NewBarkTown/scripts.pory"
	.string "one page.\p"
# 1096 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: {PLAYER}. Madame\n"
# 1097 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine intends to handle all\l"
# 1098 "data/maps/NewBarkTown/scripts.pory"
	.string "three herself.\p"
# 1099 "data/maps/NewBarkTown/scripts.pory"
	.string "I would very much like you\n"
# 1100 "data/maps/NewBarkTown/scripts.pory"
	.string "standing beside me when she\l"
# 1101 "data/maps/NewBarkTown/scripts.pory"
	.string "says it out loud.$"
# 1102 "data/maps/NewBarkTown/scripts.pory"

# 1103 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBReady:
# 1104 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Worse than Cherrygrove.\p"
# 1105 "data/maps/NewBarkTown/scripts.pory"
	.string "Worse than anything we have\n"
# 1106 "data/maps/NewBarkTown/scripts.pory"
	.string "sent you into.\p"
# 1107 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Are you ready?$"
# 1108 "data/maps/NewBarkTown/scripts.pory"

# 1109 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBNotReady:
# 1110 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Then take the time.\p"
# 1111 "data/maps/NewBarkTown/scripts.pory"
	.string "Your mother is not moving,\n"
# 1112 "data/maps/NewBarkTown/scripts.pory"
	.string "and neither am I.$"
# 1113 "data/maps/NewBarkTown/scripts.pory"

# 1114 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBTheyArrive:
# 1115 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: I came the moment I\n"
# 1116 "data/maps/NewBarkTown/scripts.pory"
	.string "read it.\p"
# 1117 "data/maps/NewBarkTown/scripts.pory"
	.string "Professor, your log - you kept\n"
# 1118 "data/maps/NewBarkTown/scripts.pory"
	.string "it. You kept six weeks of it.\p"
# 1119 "data/maps/NewBarkTown/scripts.pory"
	.string "Elm: I kept it because I\n"
# 1120 "data/maps/NewBarkTown/scripts.pory"
	.string "thought it was wrong.\p"
# 1121 "data/maps/NewBarkTown/scripts.pory"
	.string "That is not the same as being\n"
# 1122 "data/maps/NewBarkTown/scripts.pory"
	.string "useful.\p"
# 1123 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: Today it is exactly\n"
# 1124 "data/maps/NewBarkTown/scripts.pory"
	.string "the same thing.$"
# 1125 "data/maps/NewBarkTown/scripts.pory"

# 1126 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAppear:
# 1127 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Three.\p"
# 1128 "data/maps/NewBarkTown/scripts.pory"
	.string "Over the laboratory, over the\n"
# 1129 "data/maps/NewBarkTown/scripts.pory"
	.string "road, over this street.\p"
# 1130 "data/maps/NewBarkTown/scripts.pory"
	.string "Elm: That's them. That's the\n"
# 1131 "data/maps/NewBarkTown/scripts.pory"
	.string "reading.\p"
# 1132 "data/maps/NewBarkTown/scripts.pory"
	.string "Six weeks of it, standing in\n"
# 1133 "data/maps/NewBarkTown/scripts.pory"
	.string "my town.$"
# 1134 "data/maps/NewBarkTown/scripts.pory"

# 1135 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineTakesThree:
# 1136 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: Three of them.\p"
# 1137 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I will take three.\p"
# 1138 "data/maps/NewBarkTown/scripts.pory"
	.string "No - listen to me.\p"
# 1139 "data/maps/NewBarkTown/scripts.pory"
	.string "I know what they are. I know it\n"
# 1140 "data/maps/NewBarkTown/scripts.pory"
	.string "better than anyone standing on\l"
# 1141 "data/maps/NewBarkTown/scripts.pory"
	.string "this road.\p"
# 1142 "data/maps/NewBarkTown/scripts.pory"
	.string "Nobody else here has to go near\n"
# 1143 "data/maps/NewBarkTown/scripts.pory"
	.string "them.$"
# 1144 "data/maps/NewBarkTown/scripts.pory"

# 1145 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMomStopsHer:
# 1146 "data/maps/NewBarkTown/scripts.pory"
	.string "Mom: Ma'am.\p"
# 1147 "data/maps/NewBarkTown/scripts.pory"
	.string "My child is standing right\n"
# 1148 "data/maps/NewBarkTown/scripts.pory"
	.string "there, and I'm not going inside\l"
# 1149 "data/maps/NewBarkTown/scripts.pory"
	.string "either, so I won't lecture you.\p"
# 1150 "data/maps/NewBarkTown/scripts.pory"
	.string "But you're not protecting\n"
# 1151 "data/maps/NewBarkTown/scripts.pory"
	.string "anyone.\p"
# 1152 "data/maps/NewBarkTown/scripts.pory"
	.string "You're making sure that if it\n"
# 1153 "data/maps/NewBarkTown/scripts.pory"
	.string "goes wrong, it goes wrong to\l"
# 1154 "data/maps/NewBarkTown/scripts.pory"
	.string "you.\p"
# 1155 "data/maps/NewBarkTown/scripts.pory"
	.string "I know the difference. I've\n"
# 1156 "data/maps/NewBarkTown/scripts.pory"
	.string "wanted to do it too.\p"
# 1157 "data/maps/NewBarkTown/scripts.pory"
	.string "Every week, for two years.\p"
# 1158 "data/maps/NewBarkTown/scripts.pory"
	.string "It isn't the same thing.\p"
# 1159 "data/maps/NewBarkTown/scripts.pory"
	.string "It only feels like it from in\n"
# 1160 "data/maps/NewBarkTown/scripts.pory"
	.string "here.\p"
# 1161 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: …\p"
# 1162 "data/maps/NewBarkTown/scripts.pory"
	.string "My daughter said something very\n"
# 1163 "data/maps/NewBarkTown/scripts.pory"
	.string "close to that to me, once.\p"
# 1164 "data/maps/NewBarkTown/scripts.pory"
	.string "I did not hear it either.$"
# 1165 "data/maps/NewBarkTown/scripts.pory"

# 1166 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBLusamineAsks:
# 1167 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: Very well.\p"
# 1168 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I will do the thing I am\n"
# 1169 "data/maps/NewBarkTown/scripts.pory"
	.string "worst at.\p"
# 1170 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel. What do your\n"
# 1171 "data/maps/NewBarkTown/scripts.pory"
	.string "instruments give me?$"
# 1172 "data/maps/NewBarkTown/scripts.pory"

# 1173 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelBreaks:
# 1174 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: They give me… they\n"
# 1175 "data/maps/NewBarkTown/scripts.pory"
	.string "give me…\p"
# 1176 "data/maps/NewBarkTown/scripts.pory"
	.string "…\p"
# 1177 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Chief. Chief.$"
# 1178 "data/maps/NewBarkTown/scripts.pory"

# 1179 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelFaller:
# 1180 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: I'm here. I'm here.\p"
# 1181 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker, let go. I can stand.\p"
# 1182 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}. You should hear this\n"
# 1183 "data/maps/NewBarkTown/scripts.pory"
	.string "from me, and not from a file.\p"
# 1184 "data/maps/NewBarkTown/scripts.pory"
	.string "I came through one of these.\p"
# 1185 "data/maps/NewBarkTown/scripts.pory"
	.string "I'm a Faller.\p"
# 1186 "data/maps/NewBarkTown/scripts.pory"
	.string "I don't remember where I came\n"
# 1187 "data/maps/NewBarkTown/scripts.pory"
	.string "from. I've stopped pretending\l"
# 1188 "data/maps/NewBarkTown/scripts.pory"
	.string "that will come back.\p"
# 1189 "data/maps/NewBarkTown/scripts.pory"
	.string "I remember someone's hand.\p"
# 1190 "data/maps/NewBarkTown/scripts.pory"
	.string "That's the whole memory.\p"
# 1191 "data/maps/NewBarkTown/scripts.pory"
	.string "Someone reached down, and I\n"
# 1192 "data/maps/NewBarkTown/scripts.pory"
	.string "wasn't alone anymore.\p"
# 1193 "data/maps/NewBarkTown/scripts.pory"
	.string "So that's what we do.\p"
# 1194 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone who comes through gets\n"
# 1195 "data/maps/NewBarkTown/scripts.pory"
	.string "that, and everyone who goes in\l"
# 1196 "data/maps/NewBarkTown/scripts.pory"
	.string "comes home.\p"
# 1197 "data/maps/NewBarkTown/scripts.pory"
	.string "Both. Always both.\p"
# 1198 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Thank you for telling\n"
# 1199 "data/maps/NewBarkTown/scripts.pory"
	.string "them, Chief.$"
# 1200 "data/maps/NewBarkTown/scripts.pory"

# 1201 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAnabelPicks:
# 1202 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Report later.\p"
# 1203 "data/maps/NewBarkTown/scripts.pory"
	.string "I'm taking one now.$"
# 1204 "data/maps/NewBarkTown/scripts.pory"

# 1205 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1206 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalAsks:
# 1207 "data/maps/NewBarkTown/scripts.pory"
	.string "Wait. Wait!\p"
# 1208 "data/maps/NewBarkTown/scripts.pory"
	.string "I asked first. I asked before\n"
# 1209 "data/maps/NewBarkTown/scripts.pory"
	.string "any of you got here.\p"
# 1210 "data/maps/NewBarkTown/scripts.pory"
	.string "I've got a full team and I'm\n"
# 1211 "data/maps/NewBarkTown/scripts.pory"
	.string "standing in the same road.$"
# 1212 "data/maps/NewBarkTown/scripts.pory"

# 1213 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRivalRefused:
# 1214 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: You are. And you are\n"
# 1215 "data/maps/NewBarkTown/scripts.pory"
	.string "the only one on it who is not\l"
# 1216 "data/maps/NewBarkTown/scripts.pory"
	.string "police, not Aether, and not the\l"
# 1217 "data/maps/NewBarkTown/scripts.pory"
	.string "Champion.\p"
# 1218 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Forty people came back\n"
# 1219 "data/maps/NewBarkTown/scripts.pory"
	.string "out of their houses because you\l"
# 1220 "data/maps/NewBarkTown/scripts.pory"
	.string "knocked.\p"
# 1221 "data/maps/NewBarkTown/scripts.pory"
	.string "If this goes badly, they will\n"
# 1222 "data/maps/NewBarkTown/scripts.pory"
	.string "need someone who knows which\l"
# 1223 "data/maps/NewBarkTown/scripts.pory"
	.string "doors are which.\p"
# 1224 "data/maps/NewBarkTown/scripts.pory"
	.string "…\p"
# 1225 "data/maps/NewBarkTown/scripts.pory"
	.string "Fine. Fine!\p"
# 1226 "data/maps/NewBarkTown/scripts.pory"
	.string "But I'm not going inside\n"
# 1227 "data/maps/NewBarkTown/scripts.pory"
	.string "either.$"
# 1228 "data/maps/NewBarkTown/scripts.pory"

# 1229 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBChoosePrompt:
# 1230 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: {PLAYER} - which one\n"
# 1231 "data/maps/NewBarkTown/scripts.pory"
	.string "will you take?\p"
# 1232 "data/maps/NewBarkTown/scripts.pory"
	.string "I am asking. I am not deciding\n"
# 1233 "data/maps/NewBarkTown/scripts.pory"
	.string "it for you.\p"
# 1234 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Choose, {PLAYER}.\p"
# 1235 "data/maps/NewBarkTown/scripts.pory"
	.string "Quickly, and then not again.$"
# 1236 "data/maps/NewBarkTown/scripts.pory"

# 1237 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceKartana:
# 1238 "data/maps/NewBarkTown/scripts.pory"
	.string "Kartana$"
# 1239 "data/maps/NewBarkTown/scripts.pory"

# 1240 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceGuzzlord:
# 1241 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord$"
# 1242 "data/maps/NewBarkTown/scripts.pory"

# 1243 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_ChoiceNihilego:
# 1244 "data/maps/NewBarkTown/scripts.pory"
	.string "Nihilego$"
# 1245 "data/maps/NewBarkTown/scripts.pory"

# 1246 "data/maps/NewBarkTown/scripts.pory"
@ Each of the three says the whole split out loud - design section 6.4.
# 1247 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedKartana:
# 1248 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: The blade.\p"
# 1249 "data/maps/NewBarkTown/scripts.pory"
	.string "Then I take the one that\n"
# 1250 "data/maps/NewBarkTown/scripts.pory"
	.string "matters to me, and Anabel takes\l"
# 1251 "data/maps/NewBarkTown/scripts.pory"
	.string "the weight.\p"
# 1252 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Nihilego is hers.\n"
# 1253 "data/maps/NewBarkTown/scripts.pory"
	.string "Guzzlord is mine. Go.$"
# 1254 "data/maps/NewBarkTown/scripts.pory"

# 1255 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedGuzzlord:
# 1256 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: The mouth.\p"
# 1257 "data/maps/NewBarkTown/scripts.pory"
	.string "Be careful - it does not stop\n"
# 1258 "data/maps/NewBarkTown/scripts.pory"
	.string "because you are tired.\p"
# 1259 "data/maps/NewBarkTown/scripts.pory"
	.string "I take Nihilego. It is the one\n"
# 1260 "data/maps/NewBarkTown/scripts.pory"
	.string "I came for.\p"
# 1261 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Then the blade is mine.\n"
# 1262 "data/maps/NewBarkTown/scripts.pory"
	.string "Go.$"
# 1263 "data/maps/NewBarkTown/scripts.pory"

# 1264 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBPickedNihilego:
# 1265 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: …That one was mine to\n"
# 1266 "data/maps/NewBarkTown/scripts.pory"
	.string "answer for.\p"
# 1267 "data/maps/NewBarkTown/scripts.pory"
	.string "No. That is exactly the\n"
# 1268 "data/maps/NewBarkTown/scripts.pory"
	.string "sentence I promised my children\l"
# 1269 "data/maps/NewBarkTown/scripts.pory"
	.string "I would stop saying.\p"
# 1270 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you for taking it.\p"
# 1271 "data/maps/NewBarkTown/scripts.pory"
	.string "I will take the mouth instead.\p"
# 1272 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: And I'll take the\n"
# 1273 "data/maps/NewBarkTown/scripts.pory"
	.string "blade. Go.$"
# 1274 "data/maps/NewBarkTown/scripts.pory"

# 1275 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBGotAway:
# 1276 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: It is still here.\p"
# 1277 "data/maps/NewBarkTown/scripts.pory"
	.string "All three of them are still\n"
# 1278 "data/maps/NewBarkTown/scripts.pory"
	.string "here.\p"
# 1279 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Back to the line,\n"
# 1280 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER}. We go again.$"
# 1281 "data/maps/NewBarkTown/scripts.pory"

# 1282 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterKartana:
# 1283 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: Mine went back the\n"
# 1284 "data/maps/NewBarkTown/scripts.pory"
	.string "moment yours did.\p"
# 1285 "data/maps/NewBarkTown/scripts.pory"
	.string "They came together and they\n"
# 1286 "data/maps/NewBarkTown/scripts.pory"
	.string "leave together - of course they\l"
# 1287 "data/maps/NewBarkTown/scripts.pory"
	.string "do.\p"
# 1288 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Mine too.\p"
# 1289 "data/maps/NewBarkTown/scripts.pory"
	.string "Nothing I did. They just…\n"
# 1290 "data/maps/NewBarkTown/scripts.pory"
	.string "stopped being interested.$"
# 1291 "data/maps/NewBarkTown/scripts.pory"

# 1292 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterGuzzlord:
# 1293 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: You stood in front of\n"
# 1294 "data/maps/NewBarkTown/scripts.pory"
	.string "that for how long?\p"
# 1295 "data/maps/NewBarkTown/scripts.pory"
	.string "…Lillie was right about you.\p"
# 1296 "data/maps/NewBarkTown/scripts.pory"
	.string "She is right a great deal\n"
# 1297 "data/maps/NewBarkTown/scripts.pory"
	.string "lately.\p"
# 1298 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: All three withdrew at\n"
# 1299 "data/maps/NewBarkTown/scripts.pory"
	.string "once.\p"
# 1300 "data/maps/NewBarkTown/scripts.pory"
	.string "Whatever held them here let go.$"
# 1301 "data/maps/NewBarkTown/scripts.pory"

# 1302 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBAfterNihilego:
# 1303 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: I watched you do\n"
# 1304 "data/maps/NewBarkTown/scripts.pory"
	.string "that.\p"
# 1305 "data/maps/NewBarkTown/scripts.pory"
	.string "I made myself watch all of it.\p"
# 1306 "data/maps/NewBarkTown/scripts.pory"
	.string "Thank you.\p"
# 1307 "data/maps/NewBarkTown/scripts.pory"
	.string "I will not say it a third time,\n"
# 1308 "data/maps/NewBarkTown/scripts.pory"
	.string "but I mean it more each time.\p"
# 1309 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: The other two went with\n"
# 1310 "data/maps/NewBarkTown/scripts.pory"
	.string "it. All three at once.$"
# 1311 "data/maps/NewBarkTown/scripts.pory"

# 1312 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBElmCost:
# 1313 "data/maps/NewBarkTown/scripts.pory"
	.string "Elm: The sensors are gone.\p"
# 1314 "data/maps/NewBarkTown/scripts.pory"
	.string "Every one of them. Melted, or\n"
# 1315 "data/maps/NewBarkTown/scripts.pory"
	.string "whatever that was.\p"
# 1316 "data/maps/NewBarkTown/scripts.pory"
	.string "…I don't mind.\p"
# 1317 "data/maps/NewBarkTown/scripts.pory"
	.string "I have six weeks of data and I\n"
# 1318 "data/maps/NewBarkTown/scripts.pory"
	.string "finally know what it was.\p"
# 1319 "data/maps/NewBarkTown/scripts.pory"
	.string "That's a better trade than most\n"
# 1320 "data/maps/NewBarkTown/scripts.pory"
	.string "of my week.$"
# 1321 "data/maps/NewBarkTown/scripts.pory"

# 1322 "data/maps/NewBarkTown/scripts.pory"
@ No name: serves both Gold and Crystal.
# 1323 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBRival:
# 1324 "data/maps/NewBarkTown/scripts.pory"
	.string "I stood in the road and watched\n"
# 1325 "data/maps/NewBarkTown/scripts.pory"
	.string "you do that.\p"
# 1326 "data/maps/NewBarkTown/scripts.pory"
	.string "I'm not sad about it.\p"
# 1327 "data/maps/NewBarkTown/scripts.pory"
	.string "I just wanted to say it out\n"
# 1328 "data/maps/NewBarkTown/scripts.pory"
	.string "loud, one time, while everybody\l"
# 1329 "data/maps/NewBarkTown/scripts.pory"
	.string "could hear me.\p"
# 1330 "data/maps/NewBarkTown/scripts.pory"
	.string "Right. Doors.\p"
# 1331 "data/maps/NewBarkTown/scripts.pory"
	.string "Forty people to let back out.$"
# 1332 "data/maps/NewBarkTown/scripts.pory"

# 1333 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBMom:
# 1334 "data/maps/NewBarkTown/scripts.pory"
	.string "Mom: Come inside when you can.\p"
# 1335 "data/maps/NewBarkTown/scripts.pory"
	.string "I'll leave the light on.\p"
# 1336 "data/maps/NewBarkTown/scripts.pory"
	.string "You know I will.$"
# 1337 "data/maps/NewBarkTown/scripts.pory"

# 1338 "data/maps/NewBarkTown/scripts.pory"
@ This block IS the hook into the Olivine reunion, design section 7.
# 1339 "data/maps/NewBarkTown/scripts.pory"
NewBarkTown_Text_UBHook:
# 1340 "data/maps/NewBarkTown/scripts.pory"
	.string "Anabel: Looker. They didn't\n"
# 1341 "data/maps/NewBarkTown/scripts.pory"
	.string "scatter.\p"
# 1342 "data/maps/NewBarkTown/scripts.pory"
	.string "All three closed toward the\n"
# 1343 "data/maps/NewBarkTown/scripts.pory"
	.string "same bearing.\p"
# 1344 "data/maps/NewBarkTown/scripts.pory"
	.string "I can put a place on a map now.\p"
# 1345 "data/maps/NewBarkTown/scripts.pory"
	.string "I have never once been able to\n"
# 1346 "data/maps/NewBarkTown/scripts.pory"
	.string "do that.\p"
# 1347 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Then the investigation\n"
# 1348 "data/maps/NewBarkTown/scripts.pory"
	.string "is finished, and something else\l"
# 1349 "data/maps/NewBarkTown/scripts.pory"
	.string "begins.\p"
# 1350 "data/maps/NewBarkTown/scripts.pory"
	.string "Lusamine: Inspector. Call my\n"
# 1351 "data/maps/NewBarkTown/scripts.pory"
	.string "children. Both of them.\p"
# 1352 "data/maps/NewBarkTown/scripts.pory"
	.string "And Professor Kukui.\p"
# 1353 "data/maps/NewBarkTown/scripts.pory"
	.string "Not as Aether.\p"
# 1354 "data/maps/NewBarkTown/scripts.pory"
	.string "I owe these people an\n"
# 1355 "data/maps/NewBarkTown/scripts.pory"
	.string "accounting, and two of them are\l"
# 1356 "data/maps/NewBarkTown/scripts.pory"
	.string "mine.\p"
# 1357 "data/maps/NewBarkTown/scripts.pory"
	.string "Looker: Olivine, then.\p"
# 1358 "data/maps/NewBarkTown/scripts.pory"
	.string "All of us, in that small room.\p"
# 1359 "data/maps/NewBarkTown/scripts.pory"
	.string "I apologise in advance for the\n"
# 1360 "data/maps/NewBarkTown/scripts.pory"
	.string "chairs.\p"
# 1361 "data/maps/NewBarkTown/scripts.pory"
	.string "{PLAYER} - bring your partner.\p"
# 1362 "data/maps/NewBarkTown/scripts.pory"
	.string "Not for a test.\p"
# 1363 "data/maps/NewBarkTown/scripts.pory"
	.string "Everyone in that room has been\n"
# 1364 "data/maps/NewBarkTown/scripts.pory"
	.string "waiting a long time to meet\l"
# 1365 "data/maps/NewBarkTown/scripts.pory"
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
