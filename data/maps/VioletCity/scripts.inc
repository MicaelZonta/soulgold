# 1 "data/maps/VioletCity/scripts.pory"

# 2 "data/maps/VioletCity/scripts.pory"

# 3 "data/maps/VioletCity/scripts.pory"
VioletCity_MapScripts::
# 4 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VioletCity_OnFrame
# 5 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_OnTransition
# 6 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 7 "data/maps/VioletCity/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, VioletCity_OnLoad
# 8 "data/maps/VioletCity/scripts.pory"
	.byte 0
# 9 "data/maps/VioletCity/scripts.pory"

# 10 "data/maps/VioletCity/scripts.pory"
VioletCity_OnFrame::
# 11 "data/maps/VioletCity/scripts.pory"
	map_script_2 VAR_VIOLET_CITY_KIMONO_GIRL, 1, VioletCity_EventScript_Kimono_Girl
# 12 "data/maps/VioletCity/scripts.pory"
	map_script_2 VAR_VIOLET_CITY_STATE, 3, VioletCity_EventScript_ElmCall_Trigger
# 13 "data/maps/VioletCity/scripts.pory"
	.2byte 0
# 14 "data/maps/VioletCity/scripts.pory"

# 15 "data/maps/VioletCity/scripts.pory"
VioletCity_OnTransition::
# 16 "data/maps/VioletCity/scripts.pory"
	callnative SetTimeBasedEncounters
# 17 "data/maps/VioletCity/scripts.pory"
	end
# 18 "data/maps/VioletCity/scripts.pory"

# 19 "data/maps/VioletCity/scripts.pory"
VioletCity_OnLoad::
# 20 "data/maps/VioletCity/scripts.pory"
	setrespawn HEAL_LOCATION_VIOLET_CITY
# 21 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_VISITED_VIOLET_CITY
# 22 "data/maps/VioletCity/scripts.pory"
	end
# 23 "data/maps/VioletCity/scripts.pory"

# 24 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Trigger::
# 25 "data/maps/VioletCity/scripts.pory"
	@LOCAL FLAGHEAP
# 26 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_RECEIVED_MYSTERY_EGG
# 27 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_VIOLET_NPC_TRADE_COMPLETED
# 28 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_SPROUT_TOWER_SILVER
# 29 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_JOHTO_GYM_LEADERS
# 30 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HOOH_BROUGHT
# 31 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_OMANYTE_BROUGHT
# 32 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_AERODACTYL_BROUGHT
# 33 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_KABUTO_BROUGHT
# 34 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_SUDOWOODO
# 35 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_GOT_HARD_STONE
# 36 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_GOT_POISON_BARB
# 37 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_UNION_CAVE_LAPRAS
# 38 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_GOT_BLACK_GLASSES
# 39 "data/maps/VioletCity/scripts.pory"
	
# 40 "data/maps/VioletCity/scripts.pory"
	setvar VAR_SLOWPOKE_TAIL, 0
# 41 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 0
# 42 "data/maps/VioletCity/scripts.pory"
	setvar VAR_RUINSOFALPH_STATE, 0
# 43 "data/maps/VioletCity/scripts.pory"
	
# 44 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_TRAINER_SCHOOL_EARL
# 45 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_GLADION
# 46 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 47 "data/maps/VioletCity/scripts.pory"
	
# 48 "data/maps/VioletCity/scripts.pory"
	setvar VAR_SPROUT_TOWER, 0
# 49 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_STATE, 1
# 50 "data/maps/VioletCity/scripts.pory"
	end
# 51 "data/maps/VioletCity/scripts.pory"

# 52 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Earl::
# 53 "data/maps/VioletCity/scripts.pory"
	lock
# 54 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 55 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
# 56 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 57 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 58 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_EarlAsksIfYouBeatFalkner MSGBOX_YESNO
# 59 "data/maps/VioletCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, VioletCity_EventScript_EarlTrainerSchool
# 60 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_VeryNiceIndeed, MSGBOX_DEFAULT
# 61 "data/maps/VioletCity/scripts.pory"
	closemessage
# 62 "data/maps/VioletCity/scripts.pory"
	release
# 63 "data/maps/VioletCity/scripts.pory"
	end
# 64 "data/maps/VioletCity/scripts.pory"

# 65 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchool::
# 66 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_FollowEarl, MSGBOX_DEFAULT
# 67 "data/maps/VioletCity/scripts.pory"
	closemessage
# 68 "data/maps/VioletCity/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 69 "data/maps/VioletCity/scripts.pory"
	switch VAR_FACING
# 70 "data/maps/VioletCity/scripts.pory"
	case DIR_NORTH, VioletCity_EventScript_EarlTrainerSchoolSouth
# 71 "data/maps/VioletCity/scripts.pory"
	case DIR_WEST, VioletCity_EventScript_EarlTrainerSchoolEast
# 72 "data/maps/VioletCity/scripts.pory"
	release
# 73 "data/maps/VioletCity/scripts.pory"
	end
# 74 "data/maps/VioletCity/scripts.pory"

# 75 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchoolSouth::
# 76 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_South_Adjustment
# 77 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 78 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
# 79 "data/maps/VioletCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Player_South_Adjustment
# 80 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 81 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 82 "data/maps/VioletCity/scripts.pory"
	goto VioletCity_EventScript_EarlTrainerSchoolTransition
# 83 "data/maps/VioletCity/scripts.pory"
	release
# 84 "data/maps/VioletCity/scripts.pory"
	end
# 85 "data/maps/VioletCity/scripts.pory"

# 86 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchoolEast::
# 87 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_East_Adjustment
# 88 "data/maps/VioletCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Player_East_Adjustment
# 89 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 90 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 91 "data/maps/VioletCity/scripts.pory"
	goto VioletCity_EventScript_EarlTrainerSchoolTransition
# 92 "data/maps/VioletCity/scripts.pory"
	release
# 93 "data/maps/VioletCity/scripts.pory"
	end
# 94 "data/maps/VioletCity/scripts.pory"

# 95 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_EarlTrainerSchoolTransition:
# 96 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Walk_To_School
# 97 "data/maps/VioletCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, VioletCity_Movement_Walk_To_School
# 98 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 99 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 100 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Spin
# 101 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 102 "data/maps/VioletCity/scripts.pory"
	turnobject LOCALID_VIOLETCITY_EARL, DIR_WEST
# 103 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_HereTeacherIAm, MSGBOX_DEFAULT
# 104 "data/maps/VioletCity/scripts.pory"
	closemessage
# 105 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLETCITY_EARL, VioletCity_Movement_Earl_Walk_Inside
# 106 "data/maps/VioletCity/scripts.pory"
	delay 20
# 107 "data/maps/VioletCity/scripts.pory"
	opendoor 39, 36
# 108 "data/maps/VioletCity/scripts.pory"
	waitdooranim
# 109 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 110 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_EARL
# 111 "data/maps/VioletCity/scripts.pory"
	removeobject LOCALID_VIOLETCITY_EARL
# 112 "data/maps/VioletCity/scripts.pory"
	closedoor 39, 36
# 113 "data/maps/VioletCity/scripts.pory"
	waitdooranim
# 114 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_TRAINER_SCHOOL_EARL
# 115 "data/maps/VioletCity/scripts.pory"
	fadedefaultbgm
# 116 "data/maps/VioletCity/scripts.pory"
	release
# 117 "data/maps/VioletCity/scripts.pory"
	end
# 118 "data/maps/VioletCity/scripts.pory"

# 119 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Youngster::
# 120 "data/maps/VioletCity/scripts.pory"
	lock
# 121 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 122 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Youngster, MSGBOX_DEFAULT
# 123 "data/maps/VioletCity/scripts.pory"
	closemessage
# 124 "data/maps/VioletCity/scripts.pory"
	release
# 125 "data/maps/VioletCity/scripts.pory"
	end
# 126 "data/maps/VioletCity/scripts.pory"

# 127 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Boy::
# 128 "data/maps/VioletCity/scripts.pory"
	lock
# 129 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 130 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Boy, MSGBOX_DEFAULT
# 131 "data/maps/VioletCity/scripts.pory"
	closemessage
# 132 "data/maps/VioletCity/scripts.pory"
	release
# 133 "data/maps/VioletCity/scripts.pory"
	end
# 134 "data/maps/VioletCity/scripts.pory"

# 135 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Gramps::
# 136 "data/maps/VioletCity/scripts.pory"
	lock
# 137 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 138 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Gramps, MSGBOX_DEFAULT
# 139 "data/maps/VioletCity/scripts.pory"
	closemessage
# 140 "data/maps/VioletCity/scripts.pory"
	release
# 141 "data/maps/VioletCity/scripts.pory"
	end
# 142 "data/maps/VioletCity/scripts.pory"

# 143 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Lass::
# 144 "data/maps/VioletCity/scripts.pory"
	lock
# 145 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 146 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Lass, MSGBOX_DEFAULT
# 147 "data/maps/VioletCity/scripts.pory"
	closemessage
# 148 "data/maps/VioletCity/scripts.pory"
	release
# 149 "data/maps/VioletCity/scripts.pory"
	end
# 150 "data/maps/VioletCity/scripts.pory"

# 151 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Pichu::
# 152 "data/maps/VioletCity/scripts.pory"
	lock
# 153 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 154 "data/maps/VioletCity/scripts.pory"
	waitse
# 155 "data/maps/VioletCity/scripts.pory"
	playmoncry SPECIES_PICHU, CRY_MODE_NORMAL
# 156 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Pichu, MSGBOX_DEFAULT
# 157 "data/maps/VioletCity/scripts.pory"
	waitmoncry
# 158 "data/maps/VioletCity/scripts.pory"
	release
# 159 "data/maps/VioletCity/scripts.pory"
	end
# 160 "data/maps/VioletCity/scripts.pory"

# 161 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Bellsprout::
# 162 "data/maps/VioletCity/scripts.pory"
	lock
# 163 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 164 "data/maps/VioletCity/scripts.pory"
	waitse
# 165 "data/maps/VioletCity/scripts.pory"
	playmoncry SPECIES_BELLSPROUT, CRY_MODE_NORMAL
# 166 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Bellsprout, MSGBOX_DEFAULT
# 167 "data/maps/VioletCity/scripts.pory"
	waitmoncry
# 168 "data/maps/VioletCity/scripts.pory"
	release
# 169 "data/maps/VioletCity/scripts.pory"
	end
# 170 "data/maps/VioletCity/scripts.pory"

# 171 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Rattata::
# 172 "data/maps/VioletCity/scripts.pory"
	lock
# 173 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 174 "data/maps/VioletCity/scripts.pory"
	waitse
# 175 "data/maps/VioletCity/scripts.pory"
	playmoncry SPECIES_RATTATA, CRY_MODE_NORMAL
# 176 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Rattata, MSGBOX_DEFAULT
# 177 "data/maps/VioletCity/scripts.pory"
	waitmoncry
# 178 "data/maps/VioletCity/scripts.pory"
	release
# 179 "data/maps/VioletCity/scripts.pory"
	end
# 180 "data/maps/VioletCity/scripts.pory"

# 181 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ElmCall_Trigger::
# 182 "data/maps/VioletCity/scripts.pory"
	lock
# 183 "data/maps/VioletCity/scripts.pory"
	pokenavcall VioletCity_Text_Elm_Call
# 184 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 185 "data/maps/VioletCity/scripts.pory"
	delay 30
# 186 "data/maps/VioletCity/scripts.pory"
	clearflag FLAG_HIDE_VIOLET_CITY_GLADION
# 187 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_STATE, 4
# 188 "data/maps/VioletCity/scripts.pory"
	release
# 189 "data/maps/VioletCity/scripts.pory"
	end
# 190 "data/maps/VioletCity/scripts.pory"

# 191 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_Kimono_Girl::
# 192 "data/maps/VioletCity/scripts.pory"
	lock
# 193 "data/maps/VioletCity/scripts.pory"
	playbgm MUS_HG_KIMONO_GIRL, TRUE
# 194 "data/maps/VioletCity/scripts.pory"
	playse SE_PIN
# 195 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, Common_Movement_ExclamationMark
# 196 "data/maps/VioletCity/scripts.pory"
	delay 60
# 197 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_1
# 198 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 199 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl1, MSGBOX_DEFAULT
# 200 "data/maps/VioletCity/scripts.pory"
	closemessage
# 201 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_2
# 202 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 203 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl2, MSGBOX_DEFAULT
# 204 "data/maps/VioletCity/scripts.pory"
	closemessage
# 205 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_3
# 206 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 207 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl3, MSGBOX_DEFAULT
# 208 "data/maps/VioletCity/scripts.pory"
	closemessage
# 209 "data/maps/VioletCity/scripts.pory"
	playse SE_M_PETAL_DANCE
# 210 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_4
# 211 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 212 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_Kimono_Girl4, MSGBOX_DEFAULT
# 213 "data/maps/VioletCity/scripts.pory"
	closemessage
# 214 "data/maps/VioletCity/scripts.pory"
	applymovement LOCALID_VIOLET_KIMONO, VioletCity_Movement_Kimono_Girl_5
# 215 "data/maps/VioletCity/scripts.pory"
	waitmovement 0
# 216 "data/maps/VioletCity/scripts.pory"
	fadedefaultbgm
# 217 "data/maps/VioletCity/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 2
# 218 "data/maps/VioletCity/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 219 "data/maps/VioletCity/scripts.pory"
	removeobject LOCALID_VIOLET_KIMONO
# 220 "data/maps/VioletCity/scripts.pory"
	release
# 221 "data/maps/VioletCity/scripts.pory"
	end
# 222 "data/maps/VioletCity/scripts.pory"

# 223 "data/maps/VioletCity/scripts.pory"

# 224 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ItemRareCandy::
# 225 "data/maps/VioletCity/scripts.pory"
	finditem ITEM_RARE_CANDY
# 226 "data/maps/VioletCity/scripts.pory"
	end
# 227 "data/maps/VioletCity/scripts.pory"

# 228 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ItemPechaBerry::
# 229 "data/maps/VioletCity/scripts.pory"
	finditem ITEM_PECHA_BERRY
# 230 "data/maps/VioletCity/scripts.pory"
	end
# 231 "data/maps/VioletCity/scripts.pory"

# 232 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_ItemHyperPotion::
# 233 "data/maps/VioletCity/scripts.pory"
	finditem ITEM_HYPER_POTION
# 234 "data/maps/VioletCity/scripts.pory"
	end
# 235 "data/maps/VioletCity/scripts.pory"

# 236 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_Spin:
# 237 "data/maps/VioletCity/scripts.pory"
	face_down
# 238 "data/maps/VioletCity/scripts.pory"
	face_right
# 239 "data/maps/VioletCity/scripts.pory"
	face_up
# 240 "data/maps/VioletCity/scripts.pory"
	face_left
# 241 "data/maps/VioletCity/scripts.pory"
	face_down
# 242 "data/maps/VioletCity/scripts.pory"
	face_right
# 243 "data/maps/VioletCity/scripts.pory"
	face_up
# 244 "data/maps/VioletCity/scripts.pory"
	face_left
# 245 "data/maps/VioletCity/scripts.pory"
	face_down
# 246 "data/maps/VioletCity/scripts.pory"
	face_right
# 247 "data/maps/VioletCity/scripts.pory"
	face_up
# 248 "data/maps/VioletCity/scripts.pory"
	face_left
# 249 "data/maps/VioletCity/scripts.pory"
	face_down
# 250 "data/maps/VioletCity/scripts.pory"
	step_end
# 251 "data/maps/VioletCity/scripts.pory"

# 252 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_East_Adjustment:
# 253 "data/maps/VioletCity/scripts.pory"
	walk_down
# 254 "data/maps/VioletCity/scripts.pory"
	walk_down
# 255 "data/maps/VioletCity/scripts.pory"
	walk_down
# 256 "data/maps/VioletCity/scripts.pory"
	walk_right
# 257 "data/maps/VioletCity/scripts.pory"
	step_end
# 258 "data/maps/VioletCity/scripts.pory"

# 259 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Player_East_Adjustment:
# 260 "data/maps/VioletCity/scripts.pory"
	walk_down
# 261 "data/maps/VioletCity/scripts.pory"
	walk_down
# 262 "data/maps/VioletCity/scripts.pory"
	walk_left
# 263 "data/maps/VioletCity/scripts.pory"
	walk_down
# 264 "data/maps/VioletCity/scripts.pory"
	face_right
# 265 "data/maps/VioletCity/scripts.pory"
	step_end
# 266 "data/maps/VioletCity/scripts.pory"

# 267 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_South_Adjustment:
# 268 "data/maps/VioletCity/scripts.pory"
	walk_right
# 269 "data/maps/VioletCity/scripts.pory"
	walk_down
# 270 "data/maps/VioletCity/scripts.pory"
	walk_down
# 271 "data/maps/VioletCity/scripts.pory"
	walk_down
# 272 "data/maps/VioletCity/scripts.pory"
	face_right
# 273 "data/maps/VioletCity/scripts.pory"
	step_end
# 274 "data/maps/VioletCity/scripts.pory"

# 275 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Player_South_Adjustment:
# 276 "data/maps/VioletCity/scripts.pory"
	walk_down
# 277 "data/maps/VioletCity/scripts.pory"
	walk_down
# 278 "data/maps/VioletCity/scripts.pory"
	step_end
# 279 "data/maps/VioletCity/scripts.pory"

# 280 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Walk_To_School:
# 281 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 282 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 283 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 284 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 285 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 286 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 287 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 288 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 289 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 290 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 291 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 292 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 293 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 294 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 295 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 296 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 297 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 298 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 299 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 300 "data/maps/VioletCity/scripts.pory"
	walk_fast_right
# 301 "data/maps/VioletCity/scripts.pory"
	step_end
# 302 "data/maps/VioletCity/scripts.pory"

# 303 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Walk_To_School_Player:
# 304 "data/maps/VioletCity/scripts.pory"
	walk_right
# 305 "data/maps/VioletCity/scripts.pory"
	walk_right
# 306 "data/maps/VioletCity/scripts.pory"
	walk_right
# 307 "data/maps/VioletCity/scripts.pory"
	walk_right
# 308 "data/maps/VioletCity/scripts.pory"
	walk_right
# 309 "data/maps/VioletCity/scripts.pory"
	walk_right
# 310 "data/maps/VioletCity/scripts.pory"
	walk_right
# 311 "data/maps/VioletCity/scripts.pory"
	walk_right
# 312 "data/maps/VioletCity/scripts.pory"
	walk_right
# 313 "data/maps/VioletCity/scripts.pory"
	walk_right
# 314 "data/maps/VioletCity/scripts.pory"
	walk_right
# 315 "data/maps/VioletCity/scripts.pory"
	walk_right
# 316 "data/maps/VioletCity/scripts.pory"
	walk_right
# 317 "data/maps/VioletCity/scripts.pory"
	walk_right
# 318 "data/maps/VioletCity/scripts.pory"
	walk_right
# 319 "data/maps/VioletCity/scripts.pory"
	walk_right
# 320 "data/maps/VioletCity/scripts.pory"
	walk_right
# 321 "data/maps/VioletCity/scripts.pory"
	walk_right
# 322 "data/maps/VioletCity/scripts.pory"
	walk_right
# 323 "data/maps/VioletCity/scripts.pory"
	walk_right
# 324 "data/maps/VioletCity/scripts.pory"
	step_end
# 325 "data/maps/VioletCity/scripts.pory"

# 326 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Earl_Walk_Inside:
# 327 "data/maps/VioletCity/scripts.pory"
	walk_up
# 328 "data/maps/VioletCity/scripts.pory"
	walk_up
# 329 "data/maps/VioletCity/scripts.pory"
	step_end
# 330 "data/maps/VioletCity/scripts.pory"

# 331 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_1:
# 332 "data/maps/VioletCity/scripts.pory"
	walk_left
# 333 "data/maps/VioletCity/scripts.pory"
	walk_left
# 334 "data/maps/VioletCity/scripts.pory"
	walk_left
# 335 "data/maps/VioletCity/scripts.pory"
	walk_left
# 336 "data/maps/VioletCity/scripts.pory"
	face_up
# 337 "data/maps/VioletCity/scripts.pory"
	step_end
# 338 "data/maps/VioletCity/scripts.pory"

# 339 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_2:
# 340 "data/maps/VioletCity/scripts.pory"
	walk_up
# 341 "data/maps/VioletCity/scripts.pory"
	step_end
# 342 "data/maps/VioletCity/scripts.pory"

# 343 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_3:
# 344 "data/maps/VioletCity/scripts.pory"
	lock_facing_direction
# 345 "data/maps/VioletCity/scripts.pory"
	walk_down
# 346 "data/maps/VioletCity/scripts.pory"
	unlock_facing_direction
# 347 "data/maps/VioletCity/scripts.pory"
	step_end
# 348 "data/maps/VioletCity/scripts.pory"

# 349 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_4:
# 350 "data/maps/VioletCity/scripts.pory"
	face_right
# 351 "data/maps/VioletCity/scripts.pory"
	delay_8
# 352 "data/maps/VioletCity/scripts.pory"
	face_down
# 353 "data/maps/VioletCity/scripts.pory"
	delay_8
# 354 "data/maps/VioletCity/scripts.pory"
	face_left
# 355 "data/maps/VioletCity/scripts.pory"
	delay_8
# 356 "data/maps/VioletCity/scripts.pory"
	face_up
# 357 "data/maps/VioletCity/scripts.pory"
	delay_8
# 358 "data/maps/VioletCity/scripts.pory"
	face_right
# 359 "data/maps/VioletCity/scripts.pory"
	delay_8
# 360 "data/maps/VioletCity/scripts.pory"
	face_down
# 361 "data/maps/VioletCity/scripts.pory"
	delay_8
# 362 "data/maps/VioletCity/scripts.pory"
	face_left
# 363 "data/maps/VioletCity/scripts.pory"
	delay_8
# 364 "data/maps/VioletCity/scripts.pory"
	face_up
# 365 "data/maps/VioletCity/scripts.pory"
	delay_8
# 366 "data/maps/VioletCity/scripts.pory"
	step_end
# 367 "data/maps/VioletCity/scripts.pory"

# 368 "data/maps/VioletCity/scripts.pory"
VioletCity_Movement_Kimono_Girl_5:
# 369 "data/maps/VioletCity/scripts.pory"
	walk_left
# 370 "data/maps/VioletCity/scripts.pory"
	walk_left
# 371 "data/maps/VioletCity/scripts.pory"
	walk_left
# 372 "data/maps/VioletCity/scripts.pory"
	walk_left
# 373 "data/maps/VioletCity/scripts.pory"
	walk_left
# 374 "data/maps/VioletCity/scripts.pory"
	walk_up
# 375 "data/maps/VioletCity/scripts.pory"
	walk_up
# 376 "data/maps/VioletCity/scripts.pory"
	walk_up
# 377 "data/maps/VioletCity/scripts.pory"
	walk_up
# 378 "data/maps/VioletCity/scripts.pory"
	walk_up
# 379 "data/maps/VioletCity/scripts.pory"
	walk_up
# 380 "data/maps/VioletCity/scripts.pory"
	walk_up
# 381 "data/maps/VioletCity/scripts.pory"
	walk_up
# 382 "data/maps/VioletCity/scripts.pory"
	walk_up
# 383 "data/maps/VioletCity/scripts.pory"
	step_end	
# 384 "data/maps/VioletCity/scripts.pory"

# 385 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_LiquidJustice::
# 386 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_LiquidJustice, MSGBOX_NPC
# 387 "data/maps/VioletCity/scripts.pory"
	end
# 388 "data/maps/VioletCity/scripts.pory"

# 389 "data/maps/VioletCity/scripts.pory"
VioletCity_EventScript_GymSign::
# 390 "data/maps/VioletCity/scripts.pory"
	msgbox VioletCity_Text_GymSign, MSGBOX_SIGN
# 391 "data/maps/VioletCity/scripts.pory"
	end
# 392 "data/maps/VioletCity/scripts.pory"

# 393 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_LiquidJustice:
# 394 "data/maps/VioletCity/scripts.pory"
	.string "Look around!\p"
# 395 "data/maps/VioletCity/scripts.pory"
	.string "It's easy to see what Pokémon\n"
# 396 "data/maps/VioletCity/scripts.pory"
	.string "you can catch in an area without\l"
# 397 "data/maps/VioletCity/scripts.pory"
	.string "having to run around in tall\l"
# 398 "data/maps/VioletCity/scripts.pory"
	.string "grass all day!$"
# 399 "data/maps/VioletCity/scripts.pory"

# 400 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_EarlAsksIfYouBeatFalkner:
# 401 "data/maps/VioletCity/scripts.pory"
	.string "Hello!\n"
# 402 "data/maps/VioletCity/scripts.pory"
	.string "You are trainer?\p"
# 403 "data/maps/VioletCity/scripts.pory"
	.string "Battle Gym Leader,\n"
# 404 "data/maps/VioletCity/scripts.pory"
	.string "win you did?$"
# 405 "data/maps/VioletCity/scripts.pory"

# 406 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_VeryNiceIndeed:
# 407 "data/maps/VioletCity/scripts.pory"
	.string "Ooh, la la!\n"
# 408 "data/maps/VioletCity/scripts.pory"
	.string "Very indeed nice!$"
# 409 "data/maps/VioletCity/scripts.pory"

# 410 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_FollowEarl:
# 411 "data/maps/VioletCity/scripts.pory"
	.string "Is that so? Then study shall\n"
# 412 "data/maps/VioletCity/scripts.pory"
	.string "you! Follow me!$"
# 413 "data/maps/VioletCity/scripts.pory"

# 414 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_HereTeacherIAm:
# 415 "data/maps/VioletCity/scripts.pory"
	.string "Here, teacher I am.\n"
# 416 "data/maps/VioletCity/scripts.pory"
	.string "Good it is you study here!$"
# 417 "data/maps/VioletCity/scripts.pory"

# 418 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Lass:
# 419 "data/maps/VioletCity/scripts.pory"
	.string "Ghosts are rumored to appear\n"
# 420 "data/maps/VioletCity/scripts.pory"
	.string "in Sprout Tower.\p"
# 421 "data/maps/VioletCity/scripts.pory"
	.string "They say that Ghost-type\n"
# 422 "data/maps/VioletCity/scripts.pory"
	.string "moves can bypass the defenses\p"
# 423 "data/maps/VioletCity/scripts.pory"
	.string "of tough Pokémon like Onix\n"
# 424 "data/maps/VioletCity/scripts.pory"
	.string "and Geodude.$"
# 425 "data/maps/VioletCity/scripts.pory"

# 426 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Boy:
# 427 "data/maps/VioletCity/scripts.pory"
	.string "Hey, you're a Pokémon trainer?\p"
# 428 "data/maps/VioletCity/scripts.pory"
	.string "If you head to the Academy,\n"
# 429 "data/maps/VioletCity/scripts.pory"
	.string "you might learn something new!$"
# 430 "data/maps/VioletCity/scripts.pory"

# 431 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Gramps:
# 432 "data/maps/VioletCity/scripts.pory"
	.string "Falkner, from the Violet\n"
# 433 "data/maps/VioletCity/scripts.pory"
	.string "Pokémon Gym, is a fine trainer!\p"
# 434 "data/maps/VioletCity/scripts.pory"
	.string "He inherited his father's gym\n"
# 435 "data/maps/VioletCity/scripts.pory"
	.string "and has done a great job with\l"
# 436 "data/maps/VioletCity/scripts.pory"
	.string "it.$"
# 437 "data/maps/VioletCity/scripts.pory"

# 438 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Youngster:
# 439 "data/maps/VioletCity/scripts.pory"
	.string "I saw a wiggly tree up ahead!\p"
# 440 "data/maps/VioletCity/scripts.pory"
	.string "If you touch it, it squirms\n"
# 441 "data/maps/VioletCity/scripts.pory"
	.string "and dances! Cool!$"
# 442 "data/maps/VioletCity/scripts.pory"

# 443 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Sign:
# 444 "data/maps/VioletCity/scripts.pory"
	.string "Violet City\p"
# 445 "data/maps/VioletCity/scripts.pory"
	.string "The City of Nostalgic Scents$"
# 446 "data/maps/VioletCity/scripts.pory"

# 447 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_GymSign:
# 448 "data/maps/VioletCity/scripts.pory"
	.string "Violet City Pokémon Gym\p"
# 449 "data/maps/VioletCity/scripts.pory"
	.string "Leader: Falkner, The Elegant\n"
# 450 "data/maps/VioletCity/scripts.pory"
	.string "Master of Flying Pokémon$"
# 451 "data/maps/VioletCity/scripts.pory"

# 452 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_SproutTowerSign:
# 453 "data/maps/VioletCity/scripts.pory"
	.string "Sprout Tower\p"
# 454 "data/maps/VioletCity/scripts.pory"
	.string "Experience the Way of Pokémon$"
# 455 "data/maps/VioletCity/scripts.pory"

# 456 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_EarlsAcademySign:
# 457 "data/maps/VioletCity/scripts.pory"
	.string "Earl's Pokémon Academy$"
# 458 "data/maps/VioletCity/scripts.pory"

# 459 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Pichu:
# 460 "data/maps/VioletCity/scripts.pory"
	.string "Pichu: Chuuuu!$"
# 461 "data/maps/VioletCity/scripts.pory"

# 462 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Bellsprout:
# 463 "data/maps/VioletCity/scripts.pory"
	.string "Bellsprout: Sprouuuut.$"
# 464 "data/maps/VioletCity/scripts.pory"

# 465 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Rattata:
# 466 "data/maps/VioletCity/scripts.pory"
	.string "Rattata: Rattataratta!$"
# 467 "data/maps/VioletCity/scripts.pory"

# 468 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Elm_Call:
# 469 "data/maps/VioletCity/scripts.pory"
	.string "Elm: Hello, {PLAYER}? I've asked\n"
# 470 "data/maps/VioletCity/scripts.pory"
	.string "a Trainer named Gladion to bring\p"
# 471 "data/maps/VioletCity/scripts.pory"
	.string "you the Egg. He was heading to\n"
# 472 "data/maps/VioletCity/scripts.pory"
	.string "Violet City.\p"
# 473 "data/maps/VioletCity/scripts.pory"
	.string "Meet him at the Pokémon Center,\n"
# 474 "data/maps/VioletCity/scripts.pory"
	.string "would you?$"
# 475 "data/maps/VioletCity/scripts.pory"

# 476 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl1:
# 477 "data/maps/VioletCity/scripts.pory"
.string "Me oh my...\n"
# 478 "data/maps/VioletCity/scripts.pory"
.string "That Egg must be...!$"
# 479 "data/maps/VioletCity/scripts.pory"

# 480 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl2:
# 481 "data/maps/VioletCity/scripts.pory"
.string "Ah, that explains it.\p"
# 482 "data/maps/VioletCity/scripts.pory"
.string "Professor Kukui sent the Egg\n"
# 483 "data/maps/VioletCity/scripts.pory"
.string "to Professor Elm...\p"
# 484 "data/maps/VioletCity/scripts.pory"
.string "And Elm entrusted it to you.\p"
# 485 "data/maps/VioletCity/scripts.pory"
.string "It has found its way into\n"
# 486 "data/maps/VioletCity/scripts.pory"
.string "some very caring hands.$"
# 487 "data/maps/VioletCity/scripts.pory"

# 488 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl3:
# 489 "data/maps/VioletCity/scripts.pory"
.string "That Egg is truly an important Egg.\p"
# 490 "data/maps/VioletCity/scripts.pory"
.string "Please do take good care of it\n"
# 491 "data/maps/VioletCity/scripts.pory"
.string "for me. Is that understood?$"
# 492 "data/maps/VioletCity/scripts.pory"

# 493 "data/maps/VioletCity/scripts.pory"
VioletCity_Text_Kimono_Girl4:
# 494 "data/maps/VioletCity/scripts.pory"
.string "I am counting on you.$"

berrytrader_juggler::
# 500 "data/maps/VioletCity/scripts.pory"
	lock
# 501 "data/maps/VioletCity/scripts.pory"
	faceplayer
# 502 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_0
# 503 "data/maps/VioletCity/scripts.pory"
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, berrytrader_juggler_Text_1, berrytrader_juggler_Text_2, berrytrader_juggler_Text_3, berrytrader_juggler_Text_4, berrytrader_juggler_Text_5
# 504 "data/maps/VioletCity/scripts.pory"
	switch VAR_RESULT
# 505 "data/maps/VioletCity/scripts.pory"
	case 0, berrytrader_juggler_3
# 521 "data/maps/VioletCity/scripts.pory"
	case 1, berrytrader_juggler_4
# 537 "data/maps/VioletCity/scripts.pory"
	case 2, berrytrader_juggler_5
# 553 "data/maps/VioletCity/scripts.pory"
	case 3, berrytrader_juggler_6
# 570 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_11, MSGBOX_DEFAULT
# 571 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 572 "data/maps/VioletCity/scripts.pory"
	release
	end

# 575 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_3:
# 506 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_RED_SHARD
# 507 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_9
# 517 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 518 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_4:
# 522 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_BLUE_SHARD
# 523 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_12
# 533 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 534 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_5:
# 538 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_YELLOW_SHARD
# 539 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_15
# 549 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 550 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_6:
# 554 "data/maps/VioletCity/scripts.pory"
	checkitem ITEM_GREEN_SHARD
# 555 "data/maps/VioletCity/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq berrytrader_juggler_18
# 565 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_7
# 566 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_9:
# 508 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_6
# 509 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_RED_SHARD, 1
# 510 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_CHERI_BERRY
# 511 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_PECHA_BERRY
# 512 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_LEPPA_BERRY
# 513 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 514 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_12:
# 524 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_8
# 525 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_BLUE_SHARD, 1
# 526 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_ORAN_BERRY
# 527 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_CHESTO_BERRY
# 528 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_WIKI_BERRY
# 529 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 530 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_15:
# 540 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_9
# 541 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_YELLOW_SHARD, 1
# 542 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_ASPEAR_BERRY
# 543 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_SITRUS_BERRY
# 544 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_IAPAPA_BERRY
# 545 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 546 "data/maps/VioletCity/scripts.pory"
	release
	end

berrytrader_juggler_18:
# 556 "data/maps/VioletCity/scripts.pory"
	msgbox berrytrader_juggler_Text_10
# 557 "data/maps/VioletCity/scripts.pory"
	removeitem ITEM_GREEN_SHARD, 1
# 558 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_RAWST_BERRY
# 559 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_LUM_BERRY
# 560 "data/maps/VioletCity/scripts.pory"
	giveitem ITEM_AGUAV_BERRY
# 561 "data/maps/VioletCity/scripts.pory"
	waitmessage
# 562 "data/maps/VioletCity/scripts.pory"
	release
	end


DexnavDude::
# 580 "data/maps/VioletCity/scripts.pory"
	msgbox DexnavDude_Text_0, MSGBOX_NPC
	return


berrytrader_juggler_Text_0:
# 502 "data/maps/VioletCity/scripts.pory"
	.string "Yah yah! I'm a huge fan of colored\n"
	.string "shards. Do you have any to trade for\l"
	.string "me? I will give you three berries for\l"
	.string "each shard.$"

berrytrader_juggler_Text_1:
# 503 "data/maps/VioletCity/scripts.pory"
	.string "Red Shard$"

berrytrader_juggler_Text_2:
# 503 "data/maps/VioletCity/scripts.pory"
	.string "Blue Shard$"

berrytrader_juggler_Text_3:
# 503 "data/maps/VioletCity/scripts.pory"
	.string "Yellow Shard$"

berrytrader_juggler_Text_4:
# 503 "data/maps/VioletCity/scripts.pory"
	.string "Green Shard$"

berrytrader_juggler_Text_5:
# 503 "data/maps/VioletCity/scripts.pory"
	.string "Cancel$"

berrytrader_juggler_Text_6:
# 508 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set A for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_7:
# 517 "data/maps/VioletCity/scripts.pory"
	.string "You don't seem to have that shard with\n"
	.string "you.$"

berrytrader_juggler_Text_8:
# 524 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set B for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_9:
# 540 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set C for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_10:
# 556 "data/maps/VioletCity/scripts.pory"
	.string "I'll give you my berry set D for that\n"
	.string "one, yah!$"

berrytrader_juggler_Text_11:
# 570 "data/maps/VioletCity/scripts.pory"
	.string "Not interested huh? Shame...$"

DexnavDude_Text_0:
# 580 "data/maps/VioletCity/scripts.pory"
	.string "If you have a Pokegéar, you should\n"
	.string "make use of the Dexnav feature in it.$"
