# 1 "data/maps/CherrygroveCity/scripts.pory"

# 2 "data/maps/CherrygroveCity/scripts.pory"

# 3 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_MapScripts::
# 4 "data/maps/CherrygroveCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, CherrygroveCity_OnTransition
# 5 "data/maps/CherrygroveCity/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 6 "data/maps/CherrygroveCity/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, CherrygroveCity_OnLoad
# 7 "data/maps/CherrygroveCity/scripts.pory"
	.byte 0
# 8 "data/maps/CherrygroveCity/scripts.pory"

# 9 "data/maps/CherrygroveCity/scripts.pory"
@ Shared with SetTimeBasedEncounters: whoever touches this must keep BOTH
# 10 "data/maps/CherrygroveCity/scripts.pory"
@ lines. The call recomputes every visibility this map owns (Rift Mission 3
# 11 "data/maps/CherrygroveCity/scripts.pory"
@ cast, the Ultra Beasts, and the Friendly Trader's two gift Pokemon).
# 12 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_OnTransition::
# 13 "data/maps/CherrygroveCity/scripts.pory"
	callnative SetTimeBasedEncounters
# 14 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_ApplyUBVisibility
# 15 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_ApplyPostKukui
# 16 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_ApplyPostLillie
# 17 "data/maps/CherrygroveCity/scripts.pory"
	end
# 18 "data/maps/CherrygroveCity/scripts.pory"

# 19 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_OnLoad::
# 20 "data/maps/CherrygroveCity/scripts.pory"
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
# 21 "data/maps/CherrygroveCity/scripts.pory"
	end
# 22 "data/maps/CherrygroveCity/scripts.pory"

# 23 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Top::
# 24 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 25 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_VISITED_CHERRYGROVE_CITY
# 26 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 27 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 28 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
# 29 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 30 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 31 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
# 32 "data/maps/CherrygroveCity/scripts.pory"
	waitmessage
# 33 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
# 34 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
# 35 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 36 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Top
# 37 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 38 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
# 39 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 40 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_GentTour
# 41 "data/maps/CherrygroveCity/scripts.pory"
	release
# 42 "data/maps/CherrygroveCity/scripts.pory"
	end
# 43 "data/maps/CherrygroveCity/scripts.pory"

# 44 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Mid::
# 45 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 46 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_VISITED_CHERRYGROVE_CITY
# 47 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 48 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 49 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
# 50 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 51 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 52 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
# 53 "data/maps/CherrygroveCity/scripts.pory"
	waitmessage
# 54 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
# 55 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
# 56 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 57 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
# 58 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 59 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 60 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_GentTour
# 61 "data/maps/CherrygroveCity/scripts.pory"
	release
# 62 "data/maps/CherrygroveCity/scripts.pory"
	end
# 63 "data/maps/CherrygroveCity/scripts.pory"

# 64 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Bottom::
# 65 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 66 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_VISITED_CHERRYGROVE_CITY
# 67 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 68 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 69 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
# 70 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 71 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 72 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
# 73 "data/maps/CherrygroveCity/scripts.pory"
	waitmessage
# 74 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
# 75 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
# 76 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 77 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
# 78 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 79 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Bottom
# 80 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 81 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_GentTour
# 82 "data/maps/CherrygroveCity/scripts.pory"
	release
# 83 "data/maps/CherrygroveCity/scripts.pory"
	end
# 84 "data/maps/CherrygroveCity/scripts.pory"

# 85 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Cancel::
# 86 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentDecline, MSGBOX_DEFAULT
# 87 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 88 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 1 @ CHANGE THIS TO 1 LATER
# 89 "data/maps/CherrygroveCity/scripts.pory"
	release
# 90 "data/maps/CherrygroveCity/scripts.pory"
	end
# 91 "data/maps/CherrygroveCity/scripts.pory"

# 92 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_GentTour::
# 93 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 94 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokecenter
# 95 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokecenter
# 96 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 97 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 98 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentPokecenter, MSGBOX_DEFAULT
# 99 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 100 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokemart
# 101 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokemart
# 102 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 103 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 104 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentMart, MSGBOX_DEFAULT
# 105 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 106 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Route30
# 107 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Route30
# 108 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 109 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 110 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentRoute30, MSGBOX_DEFAULT
# 111 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 112 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Sea
# 113 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Sea
# 114 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 115 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 116 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentSea, MSGBOX_DEFAULT
# 117 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 118 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_House_Gent
# 119 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_House_Player
# 120 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 121 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 122 "data/maps/CherrygroveCity/scripts.pory"
	delay 20
# 123 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentMap, MSGBOX_DEFAULT
# 124 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 125 "data/maps/CherrygroveCity/scripts.pory"

# 126 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Gent_Leave
# 127 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 128 "data/maps/CherrygroveCity/scripts.pory"
	delay 20
# 129 "data/maps/CherrygroveCity/scripts.pory"
	opendoor 42, 14
# 130 "data/maps/CherrygroveCity/scripts.pory"
	waitdooranim
# 131 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 132 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_GUIDE_GENT
# 133 "data/maps/CherrygroveCity/scripts.pory"
	closedoor 42, 14
# 134 "data/maps/CherrygroveCity/scripts.pory"
	waitdooranim
# 135 "data/maps/CherrygroveCity/scripts.pory"
	
# 136 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 137 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
# 138 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 1
# 139 "data/maps/CherrygroveCity/scripts.pory"
	fadedefaultbgm
# 140 "data/maps/CherrygroveCity/scripts.pory"
	release
# 141 "data/maps/CherrygroveCity/scripts.pory"
	end
# 142 "data/maps/CherrygroveCity/scripts.pory"

# 143 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Fisherman::
# 144 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 145 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 146 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_GOT_MYSTICWATER, CherryGroveCity_EventScript_Fisherman2
# 147 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_MysticWaterGuyBefore, MSGBOX_YESNO
# 148 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Fisherman2
# 149 "data/maps/CherrygroveCity/scripts.pory"
	giveitem ITEM_MYSTIC_WATER
# 150 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull 
# 151 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 152 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_GOT_MYSTICWATER
# 153 "data/maps/CherrygroveCity/scripts.pory"
	release
# 154 "data/maps/CherrygroveCity/scripts.pory"
	end
# 155 "data/maps/CherrygroveCity/scripts.pory"

# 156 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Fisherman2::
# 157 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_MysticWaterGuyAfter, MSGBOX_DEFAULT
# 158 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 159 "data/maps/CherrygroveCity/scripts.pory"
	release
# 160 "data/maps/CherrygroveCity/scripts.pory"
	end
# 161 "data/maps/CherrygroveCity/scripts.pory"

# 162 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Lass::
# 163 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 164 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 165 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_TeacherHaveMapCard, MSGBOX_DEFAULT
# 166 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 167 "data/maps/CherrygroveCity/scripts.pory"
	release
# 168 "data/maps/CherrygroveCity/scripts.pory"
	end
# 169 "data/maps/CherrygroveCity/scripts.pory"

# 170 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Boy::
# 171 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 172 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 173 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_SYS_POKEDEX_GET, CherryGroveCity_EventScript_Boy2
# 174 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_YoungsterNoPokedex, MSGBOX_DEFAULT
# 175 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 176 "data/maps/CherrygroveCity/scripts.pory"
	release
# 177 "data/maps/CherrygroveCity/scripts.pory"
	end
# 178 "data/maps/CherrygroveCity/scripts.pory"

# 179 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Boy2::
# 180 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_YoungsterHavePokedex, MSGBOX_DEFAULT
# 181 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 182 "data/maps/CherrygroveCity/scripts.pory"
	release
# 183 "data/maps/CherrygroveCity/scripts.pory"
	end
# 184 "data/maps/CherrygroveCity/scripts.pory"

# 185 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Staryu::
# 186 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 187 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 188 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 189 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STARYU, CRY_MODE_NORMAL
# 190 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherryGroveCity_Text_Staryu, MSGBOX_DEFAULT
# 191 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 192 "data/maps/CherrygroveCity/scripts.pory"
	release
# 193 "data/maps/CherrygroveCity/scripts.pory"
	end
# 194 "data/maps/CherrygroveCity/scripts.pory"

# 195 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Corsola::
# 196 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 197 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 198 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 199 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_CORSOLA, CRY_MODE_NORMAL
# 200 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherryGroveCity_Text_Corsola, MSGBOX_DEFAULT
# 201 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 202 "data/maps/CherrygroveCity/scripts.pory"
	release
# 203 "data/maps/CherrygroveCity/scripts.pory"
	end
# 204 "data/maps/CherrygroveCity/scripts.pory"

# 205 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Krabby::
# 206 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 207 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 208 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 209 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_KRABBY, CRY_MODE_NORMAL
# 210 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherryGroveCity_Text_Krabby, MSGBOX_DEFAULT
# 211 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 212 "data/maps/CherrygroveCity/scripts.pory"
	release
# 213 "data/maps/CherrygroveCity/scripts.pory"
	end
# 214 "data/maps/CherrygroveCity/scripts.pory"

# 215 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Sign::
# 216 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 217 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_CitySign, MSGBOX_SIGN
# 218 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 219 "data/maps/CherrygroveCity/scripts.pory"
	release
# 220 "data/maps/CherrygroveCity/scripts.pory"
	end	
# 221 "data/maps/CherrygroveCity/scripts.pory"

# 222 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerSilver_Top::
# 223 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 224 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Top
# 225 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 226 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_TriggerSilver
# 227 "data/maps/CherrygroveCity/scripts.pory"
	end
# 228 "data/maps/CherrygroveCity/scripts.pory"

# 229 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerSilver_Bottom::
# 230 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 231 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Bottom
# 232 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 233 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_TriggerSilver
# 234 "data/maps/CherrygroveCity/scripts.pory"
	end
# 235 "data/maps/CherrygroveCity/scripts.pory"

# 236 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerSilver::
# 237 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 238 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
# 239 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Enter
# 240 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 241 "data/maps/CherrygroveCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 242 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_RivalSeen, MSGBOX_DEFAULT
# 243 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 244 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 0, CherryGroveCity_Silver_Battle_Cyndaquil
# 245 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 1, CherryGroveCity_Silver_Battle_Totodile
# 246 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 2, CherryGroveCity_Silver_Battle_Chikorita
# 247 "data/maps/CherrygroveCity/scripts.pory"
	release
# 248 "data/maps/CherrygroveCity/scripts.pory"
	end
# 249 "data/maps/CherrygroveCity/scripts.pory"

# 250 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_Battle_Cyndaquil::
# 251 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_1, CherrygroveCity_Text_SilverWin
# 252 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_Silver_AfterBattle
# 253 "data/maps/CherrygroveCity/scripts.pory"

# 254 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_Battle_Totodile::
# 255 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_1, CherrygroveCity_Text_SilverWin
# 256 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_Silver_AfterBattle
# 257 "data/maps/CherrygroveCity/scripts.pory"

# 258 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_Battle_Chikorita::
# 259 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_1, CherrygroveCity_Text_SilverWin
# 260 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_Silver_AfterBattle
# 261 "data/maps/CherrygroveCity/scripts.pory"

# 262 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_AfterBattle::
# 263 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_HG_RIVAL_EXIT, TRUE
# 264 "data/maps/CherrygroveCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 265 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_RivalAfter, MSGBOX_DEFAULT
# 266 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 267 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Silver_Leave1Player
# 268 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave1
# 269 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 270 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 271 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 272 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, Common_Movement_ExclamationMark
# 273 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 274 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_EAST
# 275 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 276 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_SOUTH
# 277 "data/maps/CherrygroveCity/scripts.pory"
	delay 30
# 278 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Return
# 279 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 280 "data/maps/CherrygroveCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 281 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_RivalID, MSGBOX_DEFAULT
# 282 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 283 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave2
# 284 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 285 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_SILVER
# 286 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_SILVER_CHERRYGROVE
# 287 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 4
# 288 "data/maps/CherrygroveCity/scripts.pory"
	fadedefaultbgm
# 289 "data/maps/CherrygroveCity/scripts.pory"
	release
# 290 "data/maps/CherrygroveCity/scripts.pory"
	end
# 291 "data/maps/CherrygroveCity/scripts.pory"

# 292 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentIntro:
# 293 "data/maps/CherrygroveCity/scripts.pory"
	.string "You're a rookie trainer,\n"
# 294 "data/maps/CherrygroveCity/scripts.pory"
	.string "aren't you? I can tell!\p"
# 295 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's Ok! Everyone is a\n"
# 296 "data/maps/CherrygroveCity/scripts.pory"
	.string "rookie at some point!\p"
# 297 "data/maps/CherrygroveCity/scripts.pory"
	.string "If you'd like, I can teach\n"
# 298 "data/maps/CherrygroveCity/scripts.pory"
	.string "you a few things.$"
# 299 "data/maps/CherrygroveCity/scripts.pory"

# 300 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentTourStart:
# 301 "data/maps/CherrygroveCity/scripts.pory"
	.string "Ok, then!\n"
# 302 "data/maps/CherrygroveCity/scripts.pory"
	.string "Follow me!$"
# 303 "data/maps/CherrygroveCity/scripts.pory"

# 304 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentPokecenter:
# 305 "data/maps/CherrygroveCity/scripts.pory"
	.string "This is a Pokémon Center.\p"
# 306 "data/maps/CherrygroveCity/scripts.pory"
	.string "They heal your Pokémon in no\n"
# 307 "data/maps/CherrygroveCity/scripts.pory"
	.string "time at all.\p"
# 308 "data/maps/CherrygroveCity/scripts.pory"
	.string "You'll be relying on them a lot,\n"
# 309 "data/maps/CherrygroveCity/scripts.pory"
	.string "so you better learn about them.$"
# 310 "data/maps/CherrygroveCity/scripts.pory"

# 311 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentMart:
# 312 "data/maps/CherrygroveCity/scripts.pory"
	.string "This is a Pokémon Mart.\p"
# 313 "data/maps/CherrygroveCity/scripts.pory"
	.string "They sell Balls for catching wild\n"
# 314 "data/maps/CherrygroveCity/scripts.pory"
	.string "Pokémon and other useful items.$"
# 315 "data/maps/CherrygroveCity/scripts.pory"

# 316 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentRoute30:
# 317 "data/maps/CherrygroveCity/scripts.pory"
	.string "Route 30 is out this way.\p"
# 318 "data/maps/CherrygroveCity/scripts.pory"
	.string "Trainers will be battling\n"
# 319 "data/maps/CherrygroveCity/scripts.pory"
	.string "their prized Pokémon there.$"
# 320 "data/maps/CherrygroveCity/scripts.pory"

# 321 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentSea:
# 322 "data/maps/CherrygroveCity/scripts.pory"
	.string "This is the sea, as you can see.\p"
# 323 "data/maps/CherrygroveCity/scripts.pory"
	.string "Some Pokémon are found only in\n"
# 324 "data/maps/CherrygroveCity/scripts.pory"
	.string "in water.$"
# 325 "data/maps/CherrygroveCity/scripts.pory"

# 326 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentMap:
# 327 "data/maps/CherrygroveCity/scripts.pory"
	.string "Here…\p"
# 328 "data/maps/CherrygroveCity/scripts.pory"
	.string "It's my house! Thanks for\n"
# 329 "data/maps/CherrygroveCity/scripts.pory"
	.string "your company.\p"
# 330 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh, and if you're ever lost, check\n"
# 331 "data/maps/CherrygroveCity/scripts.pory"
	.string "the Map on your Pokégear!\p"
# 332 "data/maps/CherrygroveCity/scripts.pory"
	.string "I wish you luck on your journey!$"
# 333 "data/maps/CherrygroveCity/scripts.pory"

# 334 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentDecline:
# 335 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh… It's something I enjoy\n"
# 336 "data/maps/CherrygroveCity/scripts.pory"
	.string "doing…\p"
# 337 "data/maps/CherrygroveCity/scripts.pory"
	.string "Fine. Come see me whenever\n"
# 338 "data/maps/CherrygroveCity/scripts.pory"
	.string "you like.$"
# 339 "data/maps/CherrygroveCity/scripts.pory"

# 340 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_RivalSeen:
# 341 "data/maps/CherrygroveCity/scripts.pory"
	.string "… … … … … … … …\p"
# 342 "data/maps/CherrygroveCity/scripts.pory"
	.string "You got a Pokémon at the Lab.\p"
# 343 "data/maps/CherrygroveCity/scripts.pory"
	.string "What a waste.\n"
# 344 "data/maps/CherrygroveCity/scripts.pory"
	.string "A wimp like you.\p"
# 345 "data/maps/CherrygroveCity/scripts.pory"
	.string "… … … … … … … …\p"
# 346 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't you get what I'm saying?\n"
# 347 "data/maps/CherrygroveCity/scripts.pory"
	.string "Well, I too, have a good Pokémon.\p"
# 348 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll show you what I mean!$"
# 349 "data/maps/CherrygroveCity/scripts.pory"

# 350 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_SilverWin:
# 351 "data/maps/CherrygroveCity/scripts.pory"
	.string "Humph. Are you happy you won?$"
# 352 "data/maps/CherrygroveCity/scripts.pory"

# 353 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_RivalAfter:
# 354 "data/maps/CherrygroveCity/scripts.pory"
	.string "… … … … … … … …\p"
# 355 "data/maps/CherrygroveCity/scripts.pory"
	.string "Do you want to know who I am?\p"
# 356 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm going to be the world's\n"
# 357 "data/maps/CherrygroveCity/scripts.pory"
	.string "greatest Pokémon trainer.$"
# 358 "data/maps/CherrygroveCity/scripts.pory"

# 359 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_RivalID:
# 360 "data/maps/CherrygroveCity/scripts.pory"
	.string "Give it back!\n"
# 361 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's my Trainer Card!\p"
# 362 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh no!\n"
# 363 "data/maps/CherrygroveCity/scripts.pory"
	.string "You saw my name...$"
# 364 "data/maps/CherrygroveCity/scripts.pory"

# 365 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_TeacherHaveMapCard:
# 366 "data/maps/CherrygroveCity/scripts.pory"
	.string "When you're with Pokémon,\n"
# 367 "data/maps/CherrygroveCity/scripts.pory"
	.string "going anywhere is fun.$"
# 368 "data/maps/CherrygroveCity/scripts.pory"

# 369 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_YoungsterNoPokedex:
# 370 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui's house is still\n"
# 371 "data/maps/CherrygroveCity/scripts.pory"
	.string "farther up ahead.$"
# 372 "data/maps/CherrygroveCity/scripts.pory"

# 373 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_YoungsterHavePokedex:
# 374 "data/maps/CherrygroveCity/scripts.pory"
	.string "I battled the trainers on the\n"
# 375 "data/maps/CherrygroveCity/scripts.pory"
	.string "road.\p"
# 376 "data/maps/CherrygroveCity/scripts.pory"
	.string "My Pokémon lost. They're a\n"
# 377 "data/maps/CherrygroveCity/scripts.pory"
	.string "mess! I must take them to a\l"
# 378 "data/maps/CherrygroveCity/scripts.pory"
	.string "Pokémon Center.$"
# 379 "data/maps/CherrygroveCity/scripts.pory"

# 380 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_MysticWaterGuyBefore:
# 381 "data/maps/CherrygroveCity/scripts.pory"
	.string "A Pokémon I caught had an\n"
# 382 "data/maps/CherrygroveCity/scripts.pory"
	.string "item.\p"
# 383 "data/maps/CherrygroveCity/scripts.pory"
	.string "I think it's Mystic Water.\p"
# 384 "data/maps/CherrygroveCity/scripts.pory"
	.string "I don't need it, so do you\n"
# 385 "data/maps/CherrygroveCity/scripts.pory"
	.string "want it?$"
# 386 "data/maps/CherrygroveCity/scripts.pory"

# 387 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_MysticWaterGuyAfter:
# 388 "data/maps/CherrygroveCity/scripts.pory"
	.string "Back to fishing for me, then.$"
# 389 "data/maps/CherrygroveCity/scripts.pory"

# 390 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_CitySign:
# 391 "data/maps/CherrygroveCity/scripts.pory"
	.string "Cherrygrove City\p"
# 392 "data/maps/CherrygroveCity/scripts.pory"
	.string "The City of Cute, Fragrant\n"
# 393 "data/maps/CherrygroveCity/scripts.pory"
	.string "Flowers$"
# 394 "data/maps/CherrygroveCity/scripts.pory"

# 395 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentsHouseSign:
# 396 "data/maps/CherrygroveCity/scripts.pory"
	.string "Guide Gent's House$"
# 397 "data/maps/CherrygroveCity/scripts.pory"

# 398 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Text_Staryu:
# 399 "data/maps/CherrygroveCity/scripts.pory"
	.string "Staryu: Yuuuuuuuu.$"
# 400 "data/maps/CherrygroveCity/scripts.pory"

# 401 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Text_Corsola:
# 402 "data/maps/CherrygroveCity/scripts.pory"
	.string "Corsola: Corsola! La!$"
# 403 "data/maps/CherrygroveCity/scripts.pory"

# 404 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Text_Krabby:
# 405 "data/maps/CherrygroveCity/scripts.pory"
	.string "Krabby: Kooookeee!$"
# 406 "data/maps/CherrygroveCity/scripts.pory"

# 407 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Gent:
# 408 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 409 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 410 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 411 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 412 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 413 "data/maps/CherrygroveCity/scripts.pory"

# 414 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Top:
# 415 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 416 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 417 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 418 "data/maps/CherrygroveCity/scripts.pory"

# 419 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Bottom:
# 420 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 421 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 422 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 423 "data/maps/CherrygroveCity/scripts.pory"

# 424 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Pokecenter:
# 425 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 426 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 427 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 428 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 429 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 430 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 431 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 432 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 433 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 434 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 435 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 436 "data/maps/CherrygroveCity/scripts.pory"

# 437 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Pokemart:
# 438 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 439 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 440 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 441 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 442 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 443 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 444 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 445 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 446 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 447 "data/maps/CherrygroveCity/scripts.pory"

# 448 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Route30:
# 449 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 450 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 451 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 452 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 453 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 454 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 455 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 456 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 457 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 458 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 459 "data/maps/CherrygroveCity/scripts.pory"

# 460 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Sea:
# 461 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 462 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 463 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 464 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 465 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 466 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 467 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 468 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 469 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 470 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 471 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 472 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 473 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 474 "data/maps/CherrygroveCity/scripts.pory"

# 475 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_House_Gent:
# 476 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 477 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 478 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 479 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 480 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 481 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 482 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 483 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 484 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 485 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 486 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 487 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 488 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 489 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 490 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 491 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 492 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 493 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 494 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 495 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 496 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 497 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 498 "data/maps/CherrygroveCity/scripts.pory"

# 499 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_House_Player:
# 500 "data/maps/CherrygroveCity/scripts.pory"
	delay_16
# 501 "data/maps/CherrygroveCity/scripts.pory"
	delay_16
# 502 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 503 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 504 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 505 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 506 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 507 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 508 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 509 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 510 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 511 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 512 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 513 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 514 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 515 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 516 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 517 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 518 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 519 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 520 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 521 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 522 "data/maps/CherrygroveCity/scripts.pory"

# 523 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Gent_Leave:
# 524 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 525 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 526 "data/maps/CherrygroveCity/scripts.pory"

# 527 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Silver_Top:
# 528 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 529 "data/maps/CherrygroveCity/scripts.pory"
	face_right
# 530 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 531 "data/maps/CherrygroveCity/scripts.pory"

# 532 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Silver_Bottom:
# 533 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 534 "data/maps/CherrygroveCity/scripts.pory"
	face_right
# 535 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 536 "data/maps/CherrygroveCity/scripts.pory"

# 537 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Enter:
# 538 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 539 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 540 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 541 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 542 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 543 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 544 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 545 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 546 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 547 "data/maps/CherrygroveCity/scripts.pory"

# 548 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Leave1:
# 549 "data/maps/CherrygroveCity/scripts.pory"
	delay_16
# 550 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 551 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 552 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 553 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 554 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 555 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 556 "data/maps/CherrygroveCity/scripts.pory"

# 557 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Leave1Player:
# 558 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 559 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_down
# 560 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 561 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 562 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 563 "data/maps/CherrygroveCity/scripts.pory"

# 564 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Return:
# 565 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 566 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 567 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 568 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 569 "data/maps/CherrygroveCity/scripts.pory"
	face_down
# 570 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 571 "data/maps/CherrygroveCity/scripts.pory"

# 572 "data/maps/CherrygroveCity/scripts.pory"

# 573 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Leave2:
# 574 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 575 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 576 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 577 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 578 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 579 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 580 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 581 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 582 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 583 "data/maps/CherrygroveCity/scripts.pory"
	step_end

Cherrygrove_FadedSign::
# 587 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FadedSign_Text_0, MSGBOX_SIGN
	return


Cherrygrove_DarkraiEventDoor::
# 592 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 593 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	goto_if_eq Cherrygrove_DarkraiEventDoor_2
# 625 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_7
# 628 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_DarkraiEventDoor_2:
# 594 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_0
# 599 "data/maps/CherrygroveCity/scripts.pory"
	checkspecies SPECIES_CRESSELIA
# 600 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_DarkraiEventDoor_6
# 606 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_2
# 607 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 20, 8, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_DarkraiEventDoor_Text_3, Cherrygrove_DarkraiEventDoor_Text_4
# 608 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Cherrygrove_DarkraiEventDoor_8
# 619 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_6
# 620 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_DarkraiEventDoor_6:
# 601 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_1
# 603 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_DarkraiEventDoor_8:
# 609 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_5
# 610 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 611 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_DARKRAI_INN_PROGRESS, 2
	goto_if_ge Cherrygrove_DarkraiEventDoor_12
# 614 "data/maps/CherrygroveCity/scripts.pory"
	warpwhitefade MAP_DARKRAI_INN1, 1
Cherrygrove_DarkraiEventDoor_11:
# 616 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
	end

Cherrygrove_DarkraiEventDoor_12:
# 612 "data/maps/CherrygroveCity/scripts.pory"
	warpwhitefade MAP_DARKRAI_INN1RUINED, 28, 18
	goto Cherrygrove_DarkraiEventDoor_11


Cherrygrove_Littlegirl::
# 633 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 634 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 635 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_eq Cherrygrove_Littlegirl_2
# 641 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Littlegirl_Text_1
# 644 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_Littlegirl_2:
# 636 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Littlegirl_Text_0
# 638 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_Zigzagoon::
# 649 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 650 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 651 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_ZIGZAGOON_GALAR, CRY_MODE_NORMAL
# 652 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Zigzagoon_Text_0
# 653 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_Rattata::
# 658 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 659 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 660 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_RATTATA_ALOLA, CRY_MODE_NORMAL
# 661 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Rattata_Text_0
# 662 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_TraderNoRoom::
# 670 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_TraderNoRoom_Text_0
# 681 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_FriendlyTrader::
# 686 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 687 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 688 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_ZIGZAGOON, Cherrygrove_FriendlyTrader_2
# 688 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_RATTATA, Cherrygrove_FriendlyTrader_2
# 693 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_RECEIVED_FIRST_BALLS, Cherrygrove_FriendlyTrader_7
# 789 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_7
# 796 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_2:
# 689 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_0
# 690 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

# 799 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_7:
# 699 "data/maps/CherrygroveCity/scripts.pory"
	getpartysize
# 700 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq Cherrygrove_FriendlyTrader_11
Cherrygrove_FriendlyTrader_10:
# 706 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_1
# 717 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_FriendlyTrader_Text_2, Cherrygrove_FriendlyTrader_Text_3, Cherrygrove_FriendlyTrader_Text_4
# 718 "data/maps/CherrygroveCity/scripts.pory"
	switch VAR_RESULT
# 719 "data/maps/CherrygroveCity/scripts.pory"
	case 0, Cherrygrove_FriendlyTrader_14
# 751 "data/maps/CherrygroveCity/scripts.pory"
	case 1, Cherrygrove_FriendlyTrader_15
# 784 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_6
# 785 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_11:
# 701 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
# 702 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_FriendlyTrader_17
	goto Cherrygrove_FriendlyTrader_10

Cherrygrove_FriendlyTrader_14:
# 720 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZIGZAGOON_GALAR
# 721 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
# 722 "data/maps/CherrygroveCity/scripts.pory"
	givemon SPECIES_ZIGZAGOON_GALAR, 5
# 731 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq Cherrygrove_FriendlyTrader_20
Cherrygrove_FriendlyTrader_19:
# 734 "data/maps/CherrygroveCity/scripts.pory"
	showgivemonpic 10, 3
# 740 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_PICKED_ZIGZAGOON
# 741 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRY_ZIGZAGOON
# 742 "data/maps/CherrygroveCity/scripts.pory"
	call Common_EventScript_GiftMon
# 743 "data/maps/CherrygroveCity/scripts.pory"
	hidemonpic
# 744 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
# 745 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_5
# 749 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_15:
# 752 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_RATTATA_ALOLA
# 753 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
# 754 "data/maps/CherrygroveCity/scripts.pory"
	givemon SPECIES_RATTATA_ALOLA, 5
# 763 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq Cherrygrove_FriendlyTrader_23
Cherrygrove_FriendlyTrader_22:
# 766 "data/maps/CherrygroveCity/scripts.pory"
	showgivemonpic 10, 3
# 772 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_PICKED_RATTATA
# 773 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRY_RATTATA
# 774 "data/maps/CherrygroveCity/scripts.pory"
	call Common_EventScript_GiftMon
# 775 "data/maps/CherrygroveCity/scripts.pory"
	hidemonpic
# 776 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
# 777 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_5
# 781 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_17:
# 703 "data/maps/CherrygroveCity/scripts.pory"
	goto Cherrygrove_TraderNoRoom
	goto Cherrygrove_FriendlyTrader_10

Cherrygrove_FriendlyTrader_20:
# 732 "data/maps/CherrygroveCity/scripts.pory"
	goto Cherrygrove_TraderNoRoom
	goto Cherrygrove_FriendlyTrader_19

Cherrygrove_FriendlyTrader_23:
# 764 "data/maps/CherrygroveCity/scripts.pory"
	goto Cherrygrove_TraderNoRoom
	goto Cherrygrove_FriendlyTrader_22


# 804 "data/maps/CherrygroveCity/scripts.pory"

# 805 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 806 "data/maps/CherrygroveCity/scripts.pory"
@ Rift Mission 3 - Necrozma, Blacephalon + Stakataka on the Cherrygrove beach.
# 807 "data/maps/CherrygroveCity/scripts.pory"
@ Cast: Looker, Anabel and Professor Kukui. Plan:
# 808 "data/maps/CherrygroveCity/scripts.pory"
@ .claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md
# 809 "data/maps/CherrygroveCity/scripts.pory"
@
# 810 "data/maps/CherrygroveCity/scripts.pory"
@ Story in three lines: Anabel feels the rift before any instrument does and
# 811 "data/maps/CherrygroveCity/scripts.pory"
@ says so; Necrozma rises out of the flat water, tears the tear open and
# 812 "data/maps/CherrygroveCity/scripts.pory"
@ sends the two beasts through, and their trick is that the bright one
# 813 "data/maps/CherrygroveCity/scripts.pory"
@ blinds the bay so the heavy one is simply CLOSER when it clears. Kukui -
# 814 "data/maps/CherrygroveCity/scripts.pory"
@ whom Looker has been treating as a civilian in a lab coat - puts an
# 815 "data/maps/CherrygroveCity/scripts.pory"
@ Incineroar between it and the player and turns out to be the man who built
# 816 "data/maps/CherrygroveCity/scripts.pory"
@ the Alola League. Necrozma then aims at the PLAYER, Anabel takes it
# 817 "data/maps/CherrygroveCity/scripts.pory"
@ instead, and tells them, on one knee in the wet sand, that she is a
# 818 "data/maps/CherrygroveCity/scripts.pory"
@ Faller. After the battle Necrozma absorbs both beasts and leaves.
# 819 "data/maps/CherrygroveCity/scripts.pory"
@
# 820 "data/maps/CherrygroveCity/scripts.pory"
@ Active while FLAG_EVENT_ULTRABEAST_CHERRYGROVE is set, which by invariant
# 821 "data/maps/CherrygroveCity/scripts.pory"
@ means VAR_RIFT_MISSIONS_STATE == 7. Set by OlivineCity_House1, cleared here
# 822 "data/maps/CherrygroveCity/scripts.pory"
@ on victory together with state 8. While it is set, every building door in
# 823 "data/maps/CherrygroveCity/scripts.pory"
@ town is locked except the Pokemon Center's (sLockedTownDoors in
# 824 "data/maps/CherrygroveCity/scripts.pory"
@ src/field_control_avatar.c -> CherrygroveCity_EventScript_DoorLocked).
# 825 "data/maps/CherrygroveCity/scripts.pory"
@
# 826 "data/maps/CherrygroveCity/scripts.pory"
@ Floor plan - read TWICE. The collision bit (dump_mapa.py) is NOT enough on
# 827 "data/maps/CherrygroveCity/scripts.pory"
@ a shore: half this beach has collision 0 and is still water. The sand /
# 828 "data/maps/CherrygroveCity/scripts.pory"
@ shallow / ocean split below comes from the metatile_attributes.bin of
# 829 "data/maps/CherrygroveCity/scripts.pory"
@ johto_general and cherrygrove_city. y grows DOWNWARD.
# 830 "data/maps/CherrygroveCity/scripts.pory"
@
# 831 "data/maps/CherrygroveCity/scripts.pory"
@       x= 21 22 23 24 25 26 27 28 29 30 31 32
# 832 "data/maps/CherrygroveCity/scripts.pory"
@   y= 5     #  #  #  #  #  #  #  #  #  #  #  #
# 833 "data/maps/CherrygroveCity/scripts.pory"
@   y= 6     #  #  #  #  #  #  #  #  #  #  #  #   north wall
# 834 "data/maps/CherrygroveCity/scripts.pory"
@   y= 7     ~  w  w  w  w  U  K  A  s  .  .  .   U Kukui (26,7)  K Looker (27,7)
# 835 "data/maps/CherrygroveCity/scripts.pory"
@   y= 8     ~  ~  ~  ~  w  u  t  a  .  .  .  .   A Anabel (28,7)
# 836 "data/maps/CherrygroveCity/scripts.pory"
@   y= 9     ~  ~  n  B  w  i  l  n  .  .  .  .   t (27,8) = the ONLY talk tile
# 837 "data/maps/CherrygroveCity/scripts.pory"
@   y=10     ~  N  n  S  w  X  p  P  k  .  .  .   B Blacephalon (24,9)
# 838 "data/maps/CherrygroveCity/scripts.pory"
@   y=11     ~  ~  ~  ~  w  s  s  .  .  .  .  #   S Stakataka   (24,10)
# 839 "data/maps/CherrygroveCity/scripts.pory"
@   y=12     ~  ~  ~  ~  w  s  s  .  .  #  #  #   N Necrozma    (22,10)
# 840 "data/maps/CherrygroveCity/scripts.pory"
@
# 841 "data/maps/CherrygroveCity/scripts.pory"
@   #  collision        s  MB_SAND        .  MB_NORMAL
# 842 "data/maps/CherrygroveCity/scripts.pory"
@   ~  MB_OCEAN_WATER   - Surf only; the player on foot can NOT enter
# 843 "data/maps/CherrygroveCity/scripts.pory"
@   w  MB_SHALLOW_WATER - collision 0; the player on foot DOES walk on it
# 844 "data/maps/CherrygroveCity/scripts.pory"
@
# 845 "data/maps/CherrygroveCity/scripts.pory"
@   Where the cast ends up after the approach (lower case above):
# 846 "data/maps/CherrygroveCity/scripts.pory"
@     u Kukui (26,8)   l Looker (27,8)   a Anabel (28,9)   p player (27,10)
# 847 "data/maps/CherrygroveCity/scripts.pory"
@   Where it ends up after Anabel steps in front (second lower-case pass):
# 848 "data/maps/CherrygroveCity/scripts.pory"
@     l Looker (27,9)  p Anabel (27,10)  P player (28,10)  k Kukui (29,10)
# 849 "data/maps/CherrygroveCity/scripts.pory"
@     i Incineroar (26,9)   X = (26,10), where Stakataka ends its silent
# 850 "data/maps/CherrygroveCity/scripts.pory"
@     advance; n = the three ocean tiles the absorption uses, (23,9),
# 851 "data/maps/CherrygroveCity/scripts.pory"
@     (23,10) and Necrozma's lean target.
# 852 "data/maps/CherrygroveCity/scripts.pory"
@
# 853 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: column x=25 and the strip (22..25,7) are SHALLOW water, not a
# 854 "data/maps/CherrygroveCity/scripts.pory"
@ barrier - the player wades through them. Only x<=24 is real ocean. The
# 855 "data/maps/CherrygroveCity/scripts.pory"
@ Ultra Beasts and Necrozma stand on ocean on purpose: nobody reaches them
# 856 "data/maps/CherrygroveCity/scripts.pory"
@ on foot.
# 857 "data/maps/CherrygroveCity/scripts.pory"
@
# 858 "data/maps/CherrygroveCity/scripts.pory"
@ Looker sits in a pocket: (27,6) is wall, (26,7) is Kukui and (28,7) is
# 859 "data/maps/CherrygroveCity/scripts.pory"
@ Anabel. The ONLY tile he can be talked to from is (27,8), facing up. That
# 860 "data/maps/CherrygroveCity/scripts.pory"
@ is what makes the start of the cutscene deterministic without a
# 861 "data/maps/CherrygroveCity/scripts.pory"
@ getplayerxy check.
# 862 "data/maps/CherrygroveCity/scripts.pory"
@
# 863 "data/maps/CherrygroveCity/scripts.pory"
@ Retry cost: HEAL_LOCATION_CHERRYGROVE_CITY is (47,8) and row y=8 is clear
# 864 "data/maps/CherrygroveCity/scripts.pory"
@ from x=27 to x=49, so a blackout costs a straight 20-tile walk back. That
# 865 "data/maps/CherrygroveCity/scripts.pory"
@ is accepted (section 9 of the doc): there is no Center nearer the beach.
# 866 "data/maps/CherrygroveCity/scripts.pory"
@
# 867 "data/maps/CherrygroveCity/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 868 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_1 - cast visibility cache (Kukui, Looker, Anabel)
# 869 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_2 - Ultra Beast visibility cache
# 870 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_3 - Galarian Zigzagoon gift visibility cache
# 871 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_4 - Alolan Rattata gift visibility cache
# 872 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_5 - Necrozma visibility cache (its OWN flag, so that the
# 873 "data/maps/CherrygroveCity/scripts.pory"
@                 removeobject on the beasts never touches it)
# 874 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_6 - Kukui's Incineroar visibility cache (same reason)
# 875 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_7 - post-game Kukui on the beach (Sun and Moon Altar event,
# 876 "data/maps/CherrygroveCity/scripts.pory"
@                 .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.7)
# 877 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_8 - post-game Lillie AND her Ninetales, on a different rota from
# 878 "data/maps/CherrygroveCity/scripts.pory"
@                 Kukui's, which is why it is not the same flag as his. NOT
# 879 "data/maps/CherrygroveCity/scripts.pory"
@                 FLAG_TEMP_3/4: those are the Friendly Trader's gift Pokemon
# 880 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_2  - battle outcome
# 881 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_3  - the player's pick: 0 = Blacephalon, 1 = Stakataka. Survives
# 882 "data/maps/CherrygroveCity/scripts.pory"
@                 the battle because coming back from a battle does not
# 883 "data/maps/CherrygroveCity/scripts.pory"
@                 reload the map (ClearTempFieldEventData only runs on warp
# 884 "data/maps/CherrygroveCity/scripts.pory"
@                 and edge loads).
# 885 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_4  - Cosmog-family species Necrozma reacted to (SPECIES_NONE =
# 886 "data/maps/CherrygroveCity/scripts.pory"
@                 no reaction). Read again by the aftermath dialogue.
# 887 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: VAR_TEMP_1 is VAR_TEMP_TRANSFERRED_SPECIES (vars.h:370) and
# 888 "data/maps/CherrygroveCity/scripts.pory"
@ belongs to Cherrygrove_FriendlyTrader, below in this file. This mission
# 889 "data/maps/CherrygroveCity/scripts.pory"
@ starts at VAR_TEMP_2 on purpose - do NOT "harmonise" it away.
# 890 "data/maps/CherrygroveCity/scripts.pory"
@
# 891 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: fourteen residents of this map now carry
# 892 "data/maps/CherrygroveCity/scripts.pory"
@ FLAG_EVENT_ULTRABEAST_CHERRYGROVE in their map.json "flag" field. A
# 893 "data/maps/CherrygroveCity/scripts.pory"
@ removeobject on any of them SETS that flag and empties the city.
# 894 "data/maps/CherrygroveCity/scripts.pory"
@
# 895 "data/maps/CherrygroveCity/scripts.pory"
@ Object budget: player + follower + 7 cast = 9/16.
# 896 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 897 "data/maps/CherrygroveCity/scripts.pory"

# 898 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_DoorLocked::
# 899 "data/maps/CherrygroveCity/scripts.pory"
	lockall
# 900 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_DoorLocked, MSGBOX_DEFAULT
# 901 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 902 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 903 "data/maps/CherrygroveCity/scripts.pory"
	end
# 904 "data/maps/CherrygroveCity/scripts.pory"

# 905 "data/maps/CherrygroveCity/scripts.pory"
@ Called from CherrygroveCity_OnTransition, which runs before any object is
# 906 "data/maps/CherrygroveCity/scripts.pory"
@ spawned - so setflag/clearflag work here and removeobject would not.
# 907 "data/maps/CherrygroveCity/scripts.pory"
@ The cast (FLAG_TEMP_1) is visible only while the incident is active. The
# 908 "data/maps/CherrygroveCity/scripts.pory"
@ Ultra Beasts (FLAG_TEMP_2), Necrozma (FLAG_TEMP_5) and Kukui's Incineroar
# 909 "data/maps/CherrygroveCity/scripts.pory"
@ (FLAG_TEMP_6) are always hidden on load: only the cutscene brings them in,
# 910 "data/maps/CherrygroveCity/scripts.pory"
@ which is also what makes a retry after a blackout start clean for free.
# 911 "data/maps/CherrygroveCity/scripts.pory"
@ Temps are zeroed on every load, so this recomputes from scratch every time.
# 912 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyUBVisibility::
# 913 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_2
# 914 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_5
# 915 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_6
# 916 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_ApplyGiftMonVisibility
# 917 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_HideUBCast
# 918 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_1
# 919 "data/maps/CherrygroveCity/scripts.pory"
	return
# 920 "data/maps/CherrygroveCity/scripts.pory"

# 921 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HideUBCast::
# 922 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_1
# 923 "data/maps/CherrygroveCity/scripts.pory"
	return
# 924 "data/maps/CherrygroveCity/scripts.pory"

# 925 "data/maps/CherrygroveCity/scripts.pory"
@ The Friendly Trader's two gift Pokemon (locals 16 and 17). Their map.json
# 926 "data/maps/CherrygroveCity/scripts.pory"
@ "flag" field used to be FLAG_PICKED_ZIGZAGOON / FLAG_PICKED_RATTATA, but
# 927 "data/maps/CherrygroveCity/scripts.pory"
@ that field holds ONE flag and the incident needs a second condition, so it
# 928 "data/maps/CherrygroveCity/scripts.pory"
@ now holds a dumb per-visit cache instead - the same pattern as
# 929 "data/maps/CherrygroveCity/scripts.pory"
@ FLAG_HIDE_CIANWOOD_GLADION. FLAG_PICKED_* stays the persistent truth.
# 930 "data/maps/CherrygroveCity/scripts.pory"
@   visible <=> (not picked yet) AND (no incident running)
# 931 "data/maps/CherrygroveCity/scripts.pory"
@ Because the template flag changed, the removeobject in
# 932 "data/maps/CherrygroveCity/scripts.pory"
@ Cherrygrove_FriendlyTrader no longer makes the gift permanent: the
# 933 "data/maps/CherrygroveCity/scripts.pory"
@ explicit setflag(FLAG_PICKED_*) there does. Never delete it.
# 934 "data/maps/CherrygroveCity/scripts.pory"
@ Deliberately preserved: taking one gift still leaves the OTHER one standing
# 935 "data/maps/CherrygroveCity/scripts.pory"
@ in the street. That oddity predates this mission and is not fixed here.
# 936 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyGiftMonVisibility::
# 937 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_3
# 938 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_4
# 939 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_GiftMonsStayHidden
# 940 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_ZIGZAGOON, CherrygroveCity_EventScript_GiftMonRattataOnly
# 941 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_3
# 942 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_GiftMonRattataOnly::
# 943 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_RATTATA, CherrygroveCity_EventScript_GiftMonsStayHidden
# 944 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_4
# 945 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_GiftMonsStayHidden::
# 946 "data/maps/CherrygroveCity/scripts.pory"
	return
# 947 "data/maps/CherrygroveCity/scripts.pory"

# 948 "data/maps/CherrygroveCity/scripts.pory"
@ Optional Cosmog-family reaction, no state at all: without one in the party
# 949 "data/maps/CherrygroveCity/scripts.pory"
@ the line simply does not happen. The turnobject returns her to the map.json
# 950 "data/maps/CherrygroveCity/scripts.pory"
@ FACE_DOWN; it is a no-op when the player talks from (28,8) or (29,7), but
# 951 "data/maps/CherrygroveCity/scripts.pory"
@ it guards any evolution that moves her.
# 952 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAnabel::
# 953 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 954 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 955 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 956 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 957 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, CherrygroveCity_EventScript_UBAnabelEnd
# 958 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 959 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelIdleCosmog, MSGBOX_DEFAULT
# 960 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAnabelEnd::
# 961 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 962 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_ANABEL, DIR_SOUTH
# 963 "data/maps/CherrygroveCity/scripts.pory"
	release
# 964 "data/maps/CherrygroveCity/scripts.pory"
	end
# 965 "data/maps/CherrygroveCity/scripts.pory"

# 966 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui knows a Cosmog on sight - he lived with one - but he never calls the
# 967 "data/maps/CherrygroveCity/scripts.pory"
@ player's Pokemon by the name of the one he knew (design section 3.3).
# 968 "data/maps/CherrygroveCity/scripts.pory"
@ Same no-op turnobject guard as Anabel; note he is also reachable from
# 969 "data/maps/CherrygroveCity/scripts.pory"
@ (25,7), which is shallow water the player can wade in.
# 970 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukui::
# 971 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 972 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 973 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiIdle, MSGBOX_DEFAULT
# 974 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 975 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, CherrygroveCity_EventScript_UBKukuiEnd
# 976 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 977 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiIdleCosmog, MSGBOX_DEFAULT
# 978 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukuiEnd::
# 979 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 980 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_SOUTH
# 981 "data/maps/CherrygroveCity/scripts.pory"
	release
# 982 "data/maps/CherrygroveCity/scripts.pory"
	end
# 983 "data/maps/CherrygroveCity/scripts.pory"

# 984 "data/maps/CherrygroveCity/scripts.pory"
@ Only reachable from (27,8), facing up: (27,6) is wall and Looker's east and
# 985 "data/maps/CherrygroveCity/scripts.pory"
@ west neighbours are Anabel and Kukui. No getplayerxy needed.
# 986 "data/maps/CherrygroveCity/scripts.pory"
@ Nothing changes state before the YES. The YES is the last exit point: from
# 987 "data/maps/CherrygroveCity/scripts.pory"
@ there on everything is scripted through to a battle outcome.
# 988 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui's read comes BEFORE the YES on purpose, and it is deliberately WRONG
# 989 "data/maps/CherrygroveCity/scripts.pory"
@ in one detail - he thinks the heavy one walks in behind the lights. The
# 990 "data/maps/CherrygroveCity/scripts.pory"
@ scene corrects him, which is how the synergy gets SHOWN before it is
# 991 "data/maps/CherrygroveCity/scripts.pory"
@ explained (design section 6, "sinergia entre as Ultra Beasts").
# 992 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBLooker::
# 993 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 994 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 995 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerGreet, MSGBOX_DEFAULT
# 996 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiTheory, MSGBOX_DEFAULT
# 997 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBReady, MSGBOX_YESNO
# 998 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_UBNotReady
# 999 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBScene
# 1000 "data/maps/CherrygroveCity/scripts.pory"

# 1001 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBNotReady::
# 1002 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNotReady, MSGBOX_DEFAULT
# 1003 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1004 "data/maps/CherrygroveCity/scripts.pory"
	release
# 1005 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1006 "data/maps/CherrygroveCity/scripts.pory"

# 1007 "data/maps/CherrygroveCity/scripts.pory"
@ The order of the three applymovement blocks is LOAD-BEARING:
# 1008 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui -> player -> Looker/Anabel. Looker can only step down once the
# 1009 "data/maps/CherrygroveCity/scripts.pory"
@ player has vacated (27,8), and Kukui goes first because he is the one who
# 1010 "data/maps/CherrygroveCity/scripts.pory"
@ has been standing closest to the water for four days. Every tile walked
# 1011 "data/maps/CherrygroveCity/scripts.pory"
@ here was checked in the metatile attributes: (26,8), (27,8..10), (28,8)
# 1012 "data/maps/CherrygroveCity/scripts.pory"
@ are MB_SAND and (28,9) is MB_NORMAL; nobody steps in water.
# 1013 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui stops at (26,8) and NOT at (26,10): (26,9) has to stay free for his
# 1014 "data/maps/CherrygroveCity/scripts.pory"
@ Incineroar and (26,10) for Stakataka's silent advance.
# 1015 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBScene::
# 1016 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1017 "data/maps/CherrygroveCity/scripts.pory"
	lockall
# 1018 "data/maps/CherrygroveCity/scripts.pory"
	hidefollower
# 1019 "data/maps/CherrygroveCity/scripts.pory"
	@ Kukui (26,7)->(26,8), faces west.
# 1020 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_StepDownFaceLeft
# 1021 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1022 "data/maps/CherrygroveCity/scripts.pory"
	@ Player (27,8)->(27,9)->(27,10), faces west. Column x=27 all the way, no
# 1023 "data/maps/CherrygroveCity/scripts.pory"
	@ tile shared with Kukui on any step; still goes second so that (27,8)
# 1024 "data/maps/CherrygroveCity/scripts.pory"
	@ only frees up after the player has left it.
# 1025 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerToLine
# 1026 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1027 "data/maps/CherrygroveCity/scripts.pory"
	@ Looker (27,7)->(27,8) and Anabel (28,7)->(28,8)->(28,9): different
# 1028 "data/maps/CherrygroveCity/scripts.pory"
	@ columns, no contention, so they walk together.
# 1029 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_StepDownFaceLeft
# 1030 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelToLine
# 1031 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1032 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1033 "data/maps/CherrygroveCity/scripts.pory"
	@ Anabel feels it before any instrument does (author's note, V21). This
# 1034 "data/maps/CherrygroveCity/scripts.pory"
	@ is the first half of the Faller payoff: it is never explained here.
# 1035 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 1036 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, Common_Movement_ExclamationMark
# 1037 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1038 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelSenses, MSGBOX_DEFAULT
# 1039 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1040 "data/maps/CherrygroveCity/scripts.pory"
	@ A cidade para de tocar o tema alegre dela aqui: a Anabel sentiu, e o que
# 1041 "data/maps/CherrygroveCity/scripts.pory"
	@ vem depois nao e mais uma manha de praia. Silencio durante o tremor,
# 1042 "data/maps/CherrygroveCity/scripts.pory"
	@ trilha propria a partir do momento em que a coisa aparece.
# 1043 "data/maps/CherrygroveCity/scripts.pory"
	fadeoutbgm 4
# 1044 "data/maps/CherrygroveCity/scripts.pory"
	@ Necrozma rises out of the flat water at (22,10), five tiles west of the
# 1045 "data/maps/CherrygroveCity/scripts.pory"
	@ player and well inside the camera (x 20..34 with the player at x=27).
# 1046 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1047 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1048 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_5
# 1049 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_NECROZMA
# 1050 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1051 "data/maps/CherrygroveCity/scripts.pory"
	@ save_song TRUE: a batalha de boss troca a musica, e ao voltar dela o
# 1052 "data/maps/CherrygroveCity/scripts.pory"
	@ Overworld_PlaySpecialMapMusic le gSaveBlock1Ptr->savedMusic e retoma
# 1053 "data/maps/CherrygroveCity/scripts.pory"
	@ esta, em vez do tema da cidade. Qualquer carregamento de mapa limpa o
# 1054 "data/maps/CherrygroveCity/scripts.pory"
	@ savedMusic (Overworld_ClearSavedMusic), entao o retry depois de blackout
# 1055 "data/maps/CherrygroveCity/scripts.pory"
	@ comeca do tema normal e a cena o troca de novo.
# 1056 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 1057 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1058 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1059 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
# 1060 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1061 "data/maps/CherrygroveCity/scripts.pory"
	@ It opens the tear itself - the pattern of every Rift Mission.
# 1062 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1063 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1064 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1065 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBRift, MSGBOX_DEFAULT
# 1066 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1067 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1068 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1069 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1070 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1071 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_2
# 1072 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1073 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1074 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1075 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
# 1076 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1077 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 1078 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1079 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAppear, MSGBOX_DEFAULT
# 1080 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBSynergy
# 1081 "data/maps/CherrygroveCity/scripts.pory"

# 1082 "data/maps/CherrygroveCity/scripts.pory"
@ THE SYNERGY, shown before anyone explains it, and it is the whole reason
# 1083 "data/maps/CherrygroveCity/scripts.pory"
@ this mission is a choice-plus-boss: Blacephalon whites the bay out, and
# 1084 "data/maps/CherrygroveCity/scripts.pory"
@ when the screen comes back Stakataka is simply CLOSER. It never walks, so
# 1085 "data/maps/CherrygroveCity/scripts.pory"
@ setobjectxy under the fade is not a shortcut - the teleport IS the trick.
# 1086 "data/maps/CherrygroveCity/scripts.pory"
@ (24,10) -> (25,10) -> (26,10), all on row 10, ending one tile west of the
# 1087 "data/maps/CherrygroveCity/scripts.pory"
@ player at (27,10). (25,10) is shallow water and (26,10) is sand; both are
# 1088 "data/maps/CherrygroveCity/scripts.pory"
@ empty, because Kukui stopped at (26,8).
# 1089 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBSynergy::
# 1090 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1091 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, CherrygroveCity_Movement_PulseInPlaceRight
# 1092 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_NORMAL
# 1093 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1094 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1095 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1096 "data/maps/CherrygroveCity/scripts.pory"
	setobjectxy LOCALID_CHERRYGROVE_UB_STAKATAKA, 25, 10
# 1097 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1098 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBSynergy, MSGBOX_DEFAULT
# 1099 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1100 "data/maps/CherrygroveCity/scripts.pory"
	@ Again, and this time it lands next to the player: direct danger.
# 1101 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, CherrygroveCity_Movement_PulseInPlaceRight
# 1102 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_NORMAL
# 1103 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1104 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1105 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1106 "data/maps/CherrygroveCity/scripts.pory"
	setobjectxy LOCALID_CHERRYGROVE_UB_STAKATAKA, 26, 10
# 1107 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1108 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 1109 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1110 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, Common_Movement_ExclamationMark
# 1111 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1112 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBSynergyClose, MSGBOX_DEFAULT
# 1113 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1114 "data/maps/CherrygroveCity/scripts.pory"
	@ THE SURPRISE (author's note, V21). Looker has spent the whole mission
# 1115 "data/maps/CherrygroveCity/scripts.pory"
	@ treating Kukui as a civilian in a lab coat. Nobody has seen a Poke Ball
# 1116 "data/maps/CherrygroveCity/scripts.pory"
	@ on him in four days. Incineroar drops in at (26,9), directly north of
# 1117 "data/maps/CherrygroveCity/scripts.pory"
	@ Stakataka and south of Kukui, and hits downward.
# 1118 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiSendsOut, MSGBOX_DEFAULT
# 1119 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1120 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1121 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_6
# 1122 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1123 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_INCINEROAR, CRY_MODE_ENCOUNTER
# 1124 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1125 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceDown
# 1126 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1127 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1128 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1129 "data/maps/CherrygroveCity/scripts.pory"
	@ Thrown back along row 10 to its own tile: (26,10)->(25,10)->(24,10),
# 1130 "data/maps/CherrygroveCity/scripts.pory"
	@ still facing east.
# 1131 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, CherrygroveCity_Movement_UBKnockedBack
# 1132 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1133 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_INCINEROAR, DIR_WEST
# 1134 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiRevealed, MSGBOX_DEFAULT
# 1135 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAnabelSaves
# 1136 "data/maps/CherrygroveCity/scripts.pory"

# 1137 "data/maps/CherrygroveCity/scripts.pory"
@ The creature aims at the PLAYER, and Anabel is already moving (author's
# 1138 "data/maps/CherrygroveCity/scripts.pory"
@ note, V21: she feels it before it happens, and that is what finally has to
# 1139 "data/maps/CherrygroveCity/scripts.pory"
@ be explained). The swap is sequential and never contends for a tile:
# 1140 "data/maps/CherrygroveCity/scripts.pory"
@ Anabel (28,9)->(27,9); the player is pulled (27,10)->(28,10) still facing
# 1141 "data/maps/CherrygroveCity/scripts.pory"
@ west; Anabel then drops into the vacated (27,10), between the player and
# 1142 "data/maps/CherrygroveCity/scripts.pory"
@ the light. Nobody ends up south of the player, so the text box covers
# 1143 "data/maps/CherrygroveCity/scripts.pory"
@ nobody for the rest of the mission.
# 1144 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAnabelSaves::
# 1145 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1146 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1147 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1148 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaTargets, MSGBOX_DEFAULT
# 1149 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1150 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 1151 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelStepWest
# 1152 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1153 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerPulledAside
# 1154 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1155 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelTakesTheFront
# 1156 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1157 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1158 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1159 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1160 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1161 "data/maps/CherrygroveCity/scripts.pory"
	@ Looker (27,8)->(27,9), ending facing down at her. (27,9) is free: she
# 1162 "data/maps/CherrygroveCity/scripts.pory"
	@ walked through it on her way to the front.
# 1163 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_LookerToAnabel
# 1164 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1165 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelFaller, MSGBOX_DEFAULT
# 1166 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1167 "data/maps/CherrygroveCity/scripts.pory"
	@ Back to the water for the fight: she never stops working, and that is
# 1168 "data/maps/CherrygroveCity/scripts.pory"
	@ the characterisation (design section 3.1).
# 1169 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_LOOKER, DIR_WEST
# 1170 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBChoose
# 1171 "data/maps/CherrygroveCity/scripts.pory"

# 1172 "data/maps/CherrygroveCity/scripts.pory"
@ Flash da cena. fadescreenswapbuffers e NAO fadescreen: fadescreen copia
# 1173 "data/maps/CherrygroveCity/scripts.pory"
@ gPlttBufferFaded -> gPlttBufferUnfaded ao escurecer (src/field_weather.c,
# 1174 "data/maps/CherrygroveCity/scripts.pory"
@ FadeScreen) e o FADE_FROM_* seguinte reaplica o tint de horario por cima do
# 1175 "data/maps/CherrygroveCity/scripts.pory"
@ que ja estava tintado. A noite (coeff 10) cada par de flashes multiplicava a
# 1176 "data/maps/CherrygroveCity/scripts.pory"
@ cena por ~0,46 de novo, e depois de tres ou quatro a cidade ficava preta.
# 1177 "data/maps/CherrygroveCity/scripts.pory"
@ fadescreenswapbuffers usa BLDY no hardware e nao encosta nas paletas.
# 1178 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBFlash::
# 1179 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1180 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1181 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1182 "data/maps/CherrygroveCity/scripts.pory"

# 1183 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBShake::
# 1184 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8004, 1   @ vertical pan
# 1185 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 1186 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8006, 12  @ num shakes
# 1187 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 1188 "data/maps/CherrygroveCity/scripts.pory"
	special ShakeCamera
# 1189 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1190 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1191 "data/maps/CherrygroveCity/scripts.pory"

# 1192 "data/maps/CherrygroveCity/scripts.pory"
@ Standard Rift Mission structure: the player picks which Ultra Beast to
# 1193 "data/maps/CherrygroveCity/scripts.pory"
@ fight, the mission companion takes the other. No cancel (ignoreBPress
# 1194 "data/maps/CherrygroveCity/scripts.pory"
@ TRUE) - the scene has already started, so VAR_RESULT can only be 0 or 1.
# 1195 "data/maps/CherrygroveCity/scripts.pory"
@ The pick is per attempt: after a blackout the player chooses again.
# 1196 "data/maps/CherrygroveCity/scripts.pory"
@ Splitting them is not a menu convenience - it is the counter-measure to
# 1197 "data/maps/CherrygroveCity/scripts.pory"
@ the synergy the scene just showed: whoever is being looked at cannot hide.
# 1198 "data/maps/CherrygroveCity/scripts.pory"
@ Everyone already faces the right way in either branch: player (28,10),
# 1199 "data/maps/CherrygroveCity/scripts.pory"
@ Anabel (27,10), Looker (27,9), Kukui (26,8) and Incineroar (26,9) are all
# 1200 "data/maps/CherrygroveCity/scripts.pory"
@ east of the beasts and face west, and both beasts are FACE_RIGHT.
# 1201 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBChoose::
# 1202 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 1203 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, CherrygroveCity_Text_ChoiceBlacephalon, CherrygroveCity_Text_ChoiceStakataka
# 1204 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Blacephalon, 1 = Stakataka
# 1205 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1206 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBPickStakataka
# 1207 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, Common_Movement_ExclamationMark
# 1208 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1209 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPickedBlacephalon, MSGBOX_DEFAULT
# 1210 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1211 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBBattle
# 1212 "data/maps/CherrygroveCity/scripts.pory"

# 1213 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBPickStakataka::
# 1214 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, Common_Movement_ExclamationMark
# 1215 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1216 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPickedStakataka, MSGBOX_DEFAULT
# 1217 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1218 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBBattle
# 1219 "data/maps/CherrygroveCity/scripts.pory"

# 1220 "data/maps/CherrygroveCity/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 1221 "data/maps/CherrygroveCity/scripts.pory"
@ battle - the other reason the mission splits the beasts.
# 1222 "data/maps/CherrygroveCity/scripts.pory"
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
# 1223 "data/maps/CherrygroveCity/scripts.pory"
@ losing means a blackout and a retry.
# 1224 "data/maps/CherrygroveCity/scripts.pory"
@
# 1225 "data/maps/CherrygroveCity/scripts.pory"
@ NOT a skeleton: the numbers below are the target. Third step of the ladder
# 1226 "data/maps/CherrygroveCity/scripts.pory"
@ after Blackthorn (3 bars / Lv75 / x120) and Mahogany (4 / Lv80 / x130).
# 1227 "data/maps/CherrygroveCity/scripts.pory"
@ The bars have been at MAX_BOSS_HEALTH_BARS since Mission 2, so the step up
# 1228 "data/maps/CherrygroveCity/scripts.pory"
@ here is the level, the multiplier and - above all - one control move per
# 1229 "data/maps/CherrygroveCity/scripts.pory"
@ boss: Calm Mind on Blacephalon, Trick Room on Stakataka.
# 1230 "data/maps/CherrygroveCity/scripts.pory"
@ Mind Blown is left off Blacephalon ON PURPOSE: it costs half its max HP,
# 1231 "data/maps/CherrygroveCity/scripts.pory"
@ which on a 4-bar boss is the AI killing itself for free.
# 1232 "data/maps/CherrygroveCity/scripts.pory"
@ If playtesting says "wall" instead of "threat", turn the screws in THIS
# 1233 "data/maps/CherrygroveCity/scripts.pory"
@ order, one at a time (different from Mission 2, because here the held item
# 1234 "data/maps/CherrygroveCity/scripts.pory"
@ is the loosest screw):
# 1235 "data/maps/CherrygroveCity/scripts.pory"
@   1. drop ITEM_WEAKNESS_POLICY from Stakataka (highest variance)
# 1236 "data/maps/CherrygroveCity/scripts.pory"
@   2. multiplier 140 -> 135 -> 130
# 1237 "data/maps/CherrygroveCity/scripts.pory"
@   3. swap Trick Room for a fourth attacking move
# 1238 "data/maps/CherrygroveCity/scripts.pory"
@   4. level 85 -> 80
# 1239 "data/maps/CherrygroveCity/scripts.pory"
@ The bars are at the ceiling and are not a screw. Do not touch anything in
# 1240 "data/maps/CherrygroveCity/scripts.pory"
@ section 1 of the implementation doc to compensate.
# 1241 "data/maps/CherrygroveCity/scripts.pory"
@
# 1242 "data/maps/CherrygroveCity/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 1243 "data/maps/CherrygroveCity/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 1244 "data/maps/CherrygroveCity/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between, so no
# 1245 "data/maps/CherrygroveCity/scripts.pory"
@ clearbossbattle is needed.
# 1246 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBBattle::
# 1247 "data/maps/CherrygroveCity/scripts.pory"
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
# 1248 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBSetupStakataka
# 1249 "data/maps/CherrygroveCity/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
# 1250 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
# 1251 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1252 "data/maps/CherrygroveCity/scripts.pory"
	seteventmon SPECIES_BLACEPHALON, 85, ITEM_WISE_GLASSES
# 1253 "data/maps/CherrygroveCity/scripts.pory"
	seteventmonmoves MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_FLAMETHROWER, MOVE_PSYSHOCK
# 1254 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBStartBattle
# 1255 "data/maps/CherrygroveCity/scripts.pory"

# 1256 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBSetupStakataka::
# 1257 "data/maps/CherrygroveCity/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
# 1258 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 1259 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1260 "data/maps/CherrygroveCity/scripts.pory"
	seteventmon SPECIES_STAKATAKA, 85, ITEM_WEAKNESS_POLICY
# 1261 "data/maps/CherrygroveCity/scripts.pory"
	seteventmonmoves MOVE_TRICK_ROOM, MOVE_GYRO_BALL, MOVE_STONE_EDGE, MOVE_BODY_PRESS
# 1262 "data/maps/CherrygroveCity/scripts.pory"

# 1263 "data/maps/CherrygroveCity/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the
# 1264 "data/maps/CherrygroveCity/scripts.pory"
@ player out to the Cherrygrove Pokemon Center (CherrygroveCity_OnLoad does
# 1265 "data/maps/CherrygroveCity/scripts.pory"
@ the setrespawn). CAUGHT and RAN are unreachable (ball blocked; Run becomes
# 1266 "data/maps/CherrygroveCity/scripts.pory"
@ FORFEITED in a boss) but are handled anyway: anything that is not WON
# 1267 "data/maps/CherrygroveCity/scripts.pory"
@ resets the scene, never wins it.
# 1268 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBStartBattle::
# 1269 "data/maps/CherrygroveCity/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 1270 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1271 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 1272 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 1273 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, CherrygroveCity_EventScript_UBResolved
# 1274 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBUnresolved
# 1275 "data/maps/CherrygroveCity/scripts.pory"

# 1276 "data/maps/CherrygroveCity/scripts.pory"
@ Nothing was recorded as done: the event flag is still set, so reloading the
# 1277 "data/maps/CherrygroveCity/scripts.pory"
@ map puts the cast back on its map.json spots with the beasts, Necrozma and
# 1278 "data/maps/CherrygroveCity/scripts.pory"
@ Incineroar hidden again, and talking to Looker restarts the whole scene -
# 1279 "data/maps/CherrygroveCity/scripts.pory"
@ the pick included.
# 1280 "data/maps/CherrygroveCity/scripts.pory"
@ (28,8) is free sand, one step east of Looker's talk tile.
# 1281 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBUnresolved::
# 1282 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBGotAway, MSGBOX_DEFAULT
# 1283 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1284 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1285 "data/maps/CherrygroveCity/scripts.pory"
	warpsilent MAP_CHERRYGROVE_CITY, 28, 8
# 1286 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1287 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 1288 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1289 "data/maps/CherrygroveCity/scripts.pory"

# 1290 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui's fight against the other beast is narrative: it resolves with the
# 1291 "data/maps/CherrygroveCity/scripts.pory"
@ player's win, and only his line afterwards changes with the pick. It is
# 1292 "data/maps/CherrygroveCity/scripts.pory"
@ staged, not fought - Incineroar swings west at the beasts once and that is
# 1293 "data/maps/CherrygroveCity/scripts.pory"
@ the whole of it. A real battle against Kukui is NOT the plan.
# 1294 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBResolved::
# 1295 "data/maps/CherrygroveCity/scripts.pory"
	@ Every object is still where the scene left it: a battle does not reload
# 1296 "data/maps/CherrygroveCity/scripts.pory"
	@ the map. Incineroar (26,9) faces west at x=24.
# 1297 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceLeft
# 1298 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_INCINEROAR, CRY_MODE_ENCOUNTER
# 1299 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1300 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1301 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1302 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon
# 1303 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiFoughtStakataka, MSGBOX_DEFAULT
# 1304 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAbsorb
# 1305 "data/maps/CherrygroveCity/scripts.pory"

# 1306 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon::
# 1307 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiFoughtBlacephalon, MSGBOX_DEFAULT
# 1308 "data/maps/CherrygroveCity/scripts.pory"

# 1309 "data/maps/CherrygroveCity/scripts.pory"
@ Necrozma absorbs BOTH beasts and leaves - the pattern of every Rift
# 1310 "data/maps/CherrygroveCity/scripts.pory"
@ Mission (design section 6). Positions here: Blacephalon (24,9), Stakataka
# 1311 "data/maps/CherrygroveCity/scripts.pory"
@ (24,10), Necrozma (22,10). Both are dragged one tile west, to (23,9) and
# 1312 "data/maps/CherrygroveCity/scripts.pory"
@ (23,10), which puts them against it; both tiles are open ocean.
# 1313 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAbsorb::
# 1314 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1315 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1316 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1317 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1318 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1319 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, CherrygroveCity_Movement_UBPulledIn
# 1320 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, CherrygroveCity_Movement_UBPulledIn
# 1321 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1322 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1323 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1324 "data/maps/CherrygroveCity/scripts.pory"
	@ Their flag is FLAG_TEMP_2; Necrozma and Incineroar have their own, so
# 1325 "data/maps/CherrygroveCity/scripts.pory"
	@ removeobject here touches nobody else.
# 1326 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1327 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1328 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1329 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1330 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1331 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, Common_Movement_ExclamationMark
# 1332 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, Common_Movement_ExclamationMark
# 1333 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, Common_Movement_ExclamationMark
# 1334 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1335 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1336 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1337 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1338 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAbsorbed, MSGBOX_DEFAULT
# 1339 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1340 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBNecrozmaSensesCosmog
# 1341 "data/maps/CherrygroveCity/scripts.pory"
	@ It leaves the way it came. Own flag (FLAG_TEMP_5).
# 1342 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1343 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1344 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_NECROZMA
# 1345 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1346 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaGone, MSGBOX_DEFAULT
# 1347 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1348 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAftermath
# 1349 "data/maps/CherrygroveCity/scripts.pory"

# 1350 "data/maps/CherrygroveCity/scripts.pory"
@ Optional reaction to a Cosmog-family Pokemon in the party (non-egg; the
# 1351 "data/maps/CherrygroveCity/scripts.pory"
@ special is the one Elm's Eviolite scene uses). Checked AFTER the battle on
# 1352 "data/maps/CherrygroveCity/scripts.pory"
@ purpose: the battle can evolve it. Necrozma leans east, (22,10)->(23,10),
# 1353 "data/maps/CherrygroveCity/scripts.pory"
@ free since Stakataka was removed. Without the Pokemon the whole block is
# 1354 "data/maps/CherrygroveCity/scripts.pory"
@ one specialvar and a return - the scene is identical.
# 1355 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBNecrozmaSensesCosmog::
# 1356 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 1357 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_4, VAR_RESULT
# 1358 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, CherrygroveCity_EventScript_UBReturn
# 1359 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1360 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_NecrozmaLean
# 1361 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1362 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
# 1363 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_NORMAL
# 1364 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1365 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1366 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, CherrygroveCity_EventScript_UBNecrozmaSensesLegend
# 1367 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, CherrygroveCity_EventScript_UBNecrozmaSensesLegend
# 1368 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaSensesCosmog, MSGBOX_DEFAULT
# 1369 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1370 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1371 "data/maps/CherrygroveCity/scripts.pory"

# 1372 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBNecrozmaSensesLegend::
# 1373 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaSensesLegend, MSGBOX_DEFAULT
# 1374 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1375 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1376 "data/maps/CherrygroveCity/scripts.pory"

# 1377 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBReturn::
# 1378 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1379 "data/maps/CherrygroveCity/scripts.pory"

# 1380 "data/maps/CherrygroveCity/scripts.pory"
@ People before the report (design section 3.1, Looker). Then the cast lines
# 1381 "data/maps/CherrygroveCity/scripts.pory"
@ up ORTHOGONALLY around the player at (28,10): Anabel already at (27,10)
# 1382 "data/maps/CherrygroveCity/scripts.pory"
@ west, Looker one step east to (28,9) north, Kukui the long way round the
# 1383 "data/maps/CherrygroveCity/scripts.pory"
@ back to (29,10) east. Nobody stands at (28,11), so the text box covers
# 1384 "data/maps/CherrygroveCity/scripts.pory"
@ nobody. Incineroar is recalled first, which is what frees (26,9) for
# 1385 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui's first step.
# 1386 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAftermath::
# 1387 "data/maps/CherrygroveCity/scripts.pory"
	@ A ameaca foi embora: limpa o savedMusic e volta ao tema de Cherrygrove.
# 1388 "data/maps/CherrygroveCity/scripts.pory"
	fadedefaultbgm
# 1389 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermath, MSGBOX_DEFAULT
# 1390 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1391 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1392 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1393 "data/maps/CherrygroveCity/scripts.pory"
	@ Looker (27,9)->(28,9), then faces down at the player.
# 1394 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_LookerToPlayerSide
# 1395 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1396 "data/maps/CherrygroveCity/scripts.pory"
	@ Kukui (26,8)->(27,8)->(28,8)->(29,8)->(29,9)->(29,10), faces west.
# 1397 "data/maps/CherrygroveCity/scripts.pory"
	@ Row 8 is empty (Looker and Anabel both left it) and column 29 is clear.
# 1398 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_KukuiToPlayer
# 1399 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1400 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_ANABEL, DIR_EAST
# 1401 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiRecognition, MSGBOX_DEFAULT
# 1402 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1403 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, CherrygroveCity_EventScript_UBHook
# 1404 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, CherrygroveCity_EventScript_UBAftermathLegend
# 1405 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, CherrygroveCity_EventScript_UBAftermathLegend
# 1406 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathCosmog, MSGBOX_DEFAULT
# 1407 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1408 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBHook
# 1409 "data/maps/CherrygroveCity/scripts.pory"

# 1410 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAftermathLegend::
# 1411 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathLegend, MSGBOX_DEFAULT
# 1412 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1413 "data/maps/CherrygroveCity/scripts.pory"

# 1414 "data/maps/CherrygroveCity/scripts.pory"
@ The hook names NO place (design section 6, "gancho sem destino"): the
# 1415 "data/maps/CherrygroveCity/scripts.pory"
@ briefing in Olivine is what reveals Mission 4. Looker dragging Kukui off
# 1416 "data/maps/CherrygroveCity/scripts.pory"
@ the sand is load-bearing too - the Mission 4 briefing calls back to it.
# 1417 "data/maps/CherrygroveCity/scripts.pory"
@
# 1418 "data/maps/CherrygroveCity/scripts.pory"
@ REVISION 4: Kukui's last box used to say he was coming along, and the
# 1419 "data/maps/CherrygroveCity/scripts.pory"
@ Mission 4 briefing used to put him in New Bark. The author cut that - he
# 1420 "data/maps/CherrygroveCity/scripts.pory"
@ does not go. What he does instead is the chain that STARTS Mission 4:
# 1421 "data/maps/CherrygroveCity/scripts.pory"
@ he goes reading, finds Elm's six weeks of "broken sensor", and telephones
# 1422 "data/maps/CherrygroveCity/scripts.pory"
@ the police. Elm is the one on the ground from there.
# 1423 "data/maps/CherrygroveCity/scripts.pory"
@ This box and OlivineCity_House1_Text_BriefingM4 are one pair. Never edit
# 1424 "data/maps/CherrygroveCity/scripts.pory"
@ one of them alone.
# 1425 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBHook::
# 1426 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBHook, MSGBOX_DEFAULT
# 1427 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1428 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1429 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE   @ invariant: flag and var together
# 1430 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 8
# 1431 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_DAILY_LOOKER_CALL            @ he just said it in person
# 1432 "data/maps/CherrygroveCity/scripts.pory"
	@ Reload in place under the fade. With the flag cleared the fourteen
# 1433 "data/maps/CherrygroveCity/scripts.pory"
	@ residents - and the trader's gift Pokemon, whose visibility is also
# 1434 "data/maps/CherrygroveCity/scripts.pory"
	@ recomputed on load - would otherwise pop in one by one as the camera
# 1435 "data/maps/CherrygroveCity/scripts.pory"
	@ moved, and the cast would linger. ON_TRANSITION repopulates the city
# 1436 "data/maps/CherrygroveCity/scripts.pory"
	@ and hides the cast in one go, the doors unlock with the flag, and the
# 1437 "data/maps/CherrygroveCity/scripts.pory"
	@ warp undoes the hidefollower.
# 1438 "data/maps/CherrygroveCity/scripts.pory"
	warpsilent MAP_CHERRYGROVE_CITY, 28, 10
# 1439 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1440 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 1441 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1442 "data/maps/CherrygroveCity/scripts.pory"

# 1443 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_StepDownFaceLeft:
# 1444 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1445 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1446 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1447 "data/maps/CherrygroveCity/scripts.pory"

# 1448 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerToLine:
# 1449 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1450 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1451 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1452 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1453 "data/maps/CherrygroveCity/scripts.pory"

# 1454 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelToLine:
# 1455 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1456 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1457 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1458 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1459 "data/maps/CherrygroveCity/scripts.pory"

# 1460 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PulseInPlaceRight:
# 1461 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1462 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1463 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1464 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1465 "data/maps/CherrygroveCity/scripts.pory"

# 1466 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AttackInPlaceDown:
# 1467 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_down
# 1468 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_down
# 1469 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1470 "data/maps/CherrygroveCity/scripts.pory"

# 1471 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AttackInPlaceLeft:
# 1472 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_left
# 1473 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_left
# 1474 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1475 "data/maps/CherrygroveCity/scripts.pory"

# 1476 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_UBKnockedBack:
# 1477 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 1478 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 1479 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 1480 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 1481 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1482 "data/maps/CherrygroveCity/scripts.pory"

# 1483 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_UBPulledIn:
# 1484 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 1485 "data/maps/CherrygroveCity/scripts.pory"
	walk_slow_left
# 1486 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 1487 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1488 "data/maps/CherrygroveCity/scripts.pory"

# 1489 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_NecrozmaLean:
# 1490 "data/maps/CherrygroveCity/scripts.pory"
	walk_slow_right
# 1491 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1492 "data/maps/CherrygroveCity/scripts.pory"

# 1493 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelStepWest:
# 1494 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 1495 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1496 "data/maps/CherrygroveCity/scripts.pory"

# 1497 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerPulledAside:
# 1498 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 1499 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 1500 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 1501 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1502 "data/maps/CherrygroveCity/scripts.pory"

# 1503 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelTakesTheFront:
# 1504 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_down
# 1505 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1506 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1507 "data/maps/CherrygroveCity/scripts.pory"

# 1508 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_LookerToAnabel:
# 1509 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_down
# 1510 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1511 "data/maps/CherrygroveCity/scripts.pory"

# 1512 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_LookerToPlayerSide:
# 1513 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1514 "data/maps/CherrygroveCity/scripts.pory"
	face_down
# 1515 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1516 "data/maps/CherrygroveCity/scripts.pory"

# 1517 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_KukuiToPlayer:
# 1518 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1519 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1520 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1521 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1522 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1523 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1524 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1525 "data/maps/CherrygroveCity/scripts.pory"

# 1526 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_DoorLocked:
# 1527 "data/maps/CherrygroveCity/scripts.pory"
	.string "The door is locked tight.\p"
# 1528 "data/maps/CherrygroveCity/scripts.pory"
	.string "A note is taped to it:\n"
# 1529 "data/maps/CherrygroveCity/scripts.pory"
	.string "“Closed until further notice.\l"
# 1530 "data/maps/CherrygroveCity/scripts.pory"
	.string "The town is at the Violet Gym.”$"
# 1531 "data/maps/CherrygroveCity/scripts.pory"

# 1532 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelIdle:
# 1533 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Cherrygrove is in the\n"
# 1534 "data/maps/CherrygroveCity/scripts.pory"
	.string "Violet Gym.\p"
# 1535 "data/maps/CherrygroveCity/scripts.pory"
	.string "Two buses and one argument,\n"
# 1536 "data/maps/CherrygroveCity/scripts.pory"
	.string "which I won.\p"
# 1537 "data/maps/CherrygroveCity/scripts.pory"
	.string "Talk to Looker when you're\n"
# 1538 "data/maps/CherrygroveCity/scripts.pory"
	.string "ready. Not a moment before.$"
# 1539 "data/maps/CherrygroveCity/scripts.pory"

# 1540 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelIdleCosmog:
# 1541 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}…A child of the stars.\p"
# 1542 "data/maps/CherrygroveCity/scripts.pory"
	.string "Keep that one close today,\n"
# 1543 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}.\p"
# 1544 "data/maps/CherrygroveCity/scripts.pory"
	.string "Closer than you usually do.$"
# 1545 "data/maps/CherrygroveCity/scripts.pory"

# 1546 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiIdle:
# 1547 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}{PLAYER}! Four days on\n"
# 1548 "data/maps/CherrygroveCity/scripts.pory"
	.string "this beach, cousin.\p"
# 1549 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm tired. I'm not bored.\n"
# 1550 "data/maps/CherrygroveCity/scripts.pory"
	.string "There's a difference.\p"
# 1551 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't make me tell it twice,\n"
# 1552 "data/maps/CherrygroveCity/scripts.pory"
	.string "though. Go on, talk to Looker.\p"
# 1553 "data/maps/CherrygroveCity/scripts.pory"
	.string "You'll get the whole thing at\n"
# 1554 "data/maps/CherrygroveCity/scripts.pory"
	.string "once.$"
# 1555 "data/maps/CherrygroveCity/scripts.pory"

# 1556 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiIdleCosmog:
# 1557 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}…Hold on.\p"
# 1558 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hold on, that's a {STR_VAR_1}.\p"
# 1559 "data/maps/CherrygroveCity/scripts.pory"
	.string "I've met exactly one of those.\p"
# 1560 "data/maps/CherrygroveCity/scripts.pory"
	.string "It cost me a roof, a boat and\n"
# 1561 "data/maps/CherrygroveCity/scripts.pory"
	.string "eleven weeks of paperwork.\p"
# 1562 "data/maps/CherrygroveCity/scripts.pory"
	.string "You and I are having a very\n"
# 1563 "data/maps/CherrygroveCity/scripts.pory"
	.string "long talk. After.$"
# 1564 "data/maps/CherrygroveCity/scripts.pory"

# 1565 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerGreet:
# 1566 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Over here.\p"
# 1567 "data/maps/CherrygroveCity/scripts.pory"
	.string "And mind your footing. That\n"
# 1568 "data/maps/CherrygroveCity/scripts.pory"
	.string "water is not behaving.\p"
# 1569 "data/maps/CherrygroveCity/scripts.pory"
	.string "It has opened twice since dawn.\p"
# 1570 "data/maps/CherrygroveCity/scripts.pory"
	.string "Twice we ran. Twice it closed\n"
# 1571 "data/maps/CherrygroveCity/scripts.pory"
	.string "before we arrived.\p"
# 1572 "data/maps/CherrygroveCity/scripts.pory"
	.string "The Professor, meanwhile, has\n"
# 1573 "data/maps/CherrygroveCity/scripts.pory"
	.string "not run anywhere.\p"
# 1574 "data/maps/CherrygroveCity/scripts.pory"
	.string "He has been sitting in it.$"
# 1575 "data/maps/CherrygroveCity/scripts.pory"

# 1576 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiTheory:
# 1577 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}{PLAYER}! Man, am I glad\n"
# 1578 "data/maps/CherrygroveCity/scripts.pory"
	.string "it's you.\p"
# 1579 "data/maps/CherrygroveCity/scripts.pory"
	.string "Okay. Four days, three\n"
# 1580 "data/maps/CherrygroveCity/scripts.pory"
	.string "openings, one notebook.\p"
# 1581 "data/maps/CherrygroveCity/scripts.pory"
	.string "There are two of them, and\n"
# 1582 "data/maps/CherrygroveCity/scripts.pory"
	.string "they never come through\l"
# 1583 "data/maps/CherrygroveCity/scripts.pory"
	.string "together.\p"
# 1584 "data/maps/CherrygroveCity/scripts.pory"
	.string "The bright one shows first. It\n"
# 1585 "data/maps/CherrygroveCity/scripts.pory"
	.string "lights up the whole bay and\l"
# 1586 "data/maps/CherrygroveCity/scripts.pory"
	.string "everybody looks.\p"
# 1587 "data/maps/CherrygroveCity/scripts.pory"
	.string "Everybody. You can't help it.\p"
# 1588 "data/maps/CherrygroveCity/scripts.pory"
	.string "And by the time you can see\n"
# 1589 "data/maps/CherrygroveCity/scripts.pory"
	.string "again, the big one is closer\l"
# 1590 "data/maps/CherrygroveCity/scripts.pory"
	.string "than it was.\p"
# 1591 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Professor. Four days.\n"
# 1592 "data/maps/CherrygroveCity/scripts.pory"
	.string "On a beach.\p"
# 1593 "data/maps/CherrygroveCity/scripts.pory"
	.string "Under a hole in the sky.\p"
# 1594 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Yeah. And if it opened\n"
# 1595 "data/maps/CherrygroveCity/scripts.pory"
	.string "with nobody watching, who tells\l"
# 1596 "data/maps/CherrygroveCity/scripts.pory"
	.string "this town when to run?\p"
# 1597 "data/maps/CherrygroveCity/scripts.pory"
	.string "I stayed so somebody would\n"
# 1598 "data/maps/CherrygroveCity/scripts.pory"
	.string "know.\p"
# 1599 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}He called the second\n"
# 1600 "data/maps/CherrygroveCity/scripts.pory"
	.string "opening eleven minutes early.\p"
# 1601 "data/maps/CherrygroveCity/scripts.pory"
	.string "He has earned the sand.\p"
# 1602 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}So here's the play.\p"
# 1603 "data/maps/CherrygroveCity/scripts.pory"
	.string "One of us takes the bright\n"
# 1604 "data/maps/CherrygroveCity/scripts.pory"
	.string "one's eyes. The other takes\l"
# 1605 "data/maps/CherrygroveCity/scripts.pory"
	.string "the wall.\p"
# 1606 "data/maps/CherrygroveCity/scripts.pory"
	.string "Nobody gets to hide if somebody\n"
# 1607 "data/maps/CherrygroveCity/scripts.pory"
	.string "is always looking.$"
# 1608 "data/maps/CherrygroveCity/scripts.pory"

# 1609 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBReady:
# 1610 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}One warning, {PLAYER}.\p"
# 1611 "data/maps/CherrygroveCity/scripts.pory"
	.string "These two are worse than\n"
# 1612 "data/maps/CherrygroveCity/scripts.pory"
	.string "Mahogany.\p"
# 1613 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Bring everything you\n"
# 1614 "data/maps/CherrygroveCity/scripts.pory"
	.string "have.\p"
# 1615 "data/maps/CherrygroveCity/scripts.pory"
	.string "Are you ready?$"
# 1616 "data/maps/CherrygroveCity/scripts.pory"

# 1617 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNotReady:
# 1618 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Wise.\p"
# 1619 "data/maps/CherrygroveCity/scripts.pory"
	.string "The Center is open, and I am\n"
# 1620 "data/maps/CherrygroveCity/scripts.pory"
	.string "not moving from this sand.$"
# 1621 "data/maps/CherrygroveCity/scripts.pory"

# 1622 "data/maps/CherrygroveCity/scripts.pory"
@ She stops mid-instruction. Nothing is explained here - the explanation is
# 1623 "data/maps/CherrygroveCity/scripts.pory"
@ the price of the rescue, later in this same scene.
# 1624 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelSenses:
# 1625 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Professor, stay east of\n"
# 1626 "data/maps/CherrygroveCity/scripts.pory"
	.string "the tide line, and if anything\l"
# 1627 "data/maps/CherrygroveCity/scripts.pory"
	.string "comes through you will-\p"
# 1628 "data/maps/CherrygroveCity/scripts.pory"
	.string "…\p"
# 1629 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief?\p"
# 1630 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It's here.\p"
# 1631 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}There is nothing on the\n"
# 1632 "data/maps/CherrygroveCity/scripts.pory"
	.string "meter.\p"
# 1633 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I know.\p"
# 1634 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Whoa-look at the water!\p"
# 1635 "data/maps/CherrygroveCity/scripts.pory"
	.string "It's going flat. That's the\n"
# 1636 "data/maps/CherrygroveCity/scripts.pory"
	.string "tell! Everybody back!$"
# 1637 "data/maps/CherrygroveCity/scripts.pory"

# 1638 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaArrives:
# 1639 "data/maps/CherrygroveCity/scripts.pory"
	.string "Something stands up out of the\n"
# 1640 "data/maps/CherrygroveCity/scripts.pory"
	.string "flat water.\p"
# 1641 "data/maps/CherrygroveCity/scripts.pory"
	.string "It is made of light, and it is\n"
# 1642 "data/maps/CherrygroveCity/scripts.pory"
	.string "looking at the beach.\p"
# 1643 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…That is the thing from\n"
# 1644 "data/maps/CherrygroveCity/scripts.pory"
	.string "Blackthorn.\p"
# 1645 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}That is not a Pokémon I\n"
# 1646 "data/maps/CherrygroveCity/scripts.pory"
	.string "know.\p"
# 1647 "data/maps/CherrygroveCity/scripts.pory"
	.string "And, cousin, I know a lot of\n"
# 1648 "data/maps/CherrygroveCity/scripts.pory"
	.string "them.\p"
# 1649 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It was standing there\n"
# 1650 "data/maps/CherrygroveCity/scripts.pory"
	.string "before my instruments said so.\p"
# 1651 "data/maps/CherrygroveCity/scripts.pory"
	.string "It always is.$"
# 1652 "data/maps/CherrygroveCity/scripts.pory"

# 1653 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBRift:
# 1654 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}It's- wait. Wait!\p"
# 1655 "data/maps/CherrygroveCity/scripts.pory"
	.string "It isn't coming through the\n"
# 1656 "data/maps/CherrygroveCity/scripts.pory"
	.string "tear.\p"
# 1657 "data/maps/CherrygroveCity/scripts.pory"
	.string "It's making it!\p"
# 1658 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Behind me, Professor.\n"
# 1659 "data/maps/CherrygroveCity/scripts.pory"
	.string "Behind me, please.\p"
# 1660 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Nah.$"
# 1661 "data/maps/CherrygroveCity/scripts.pory"

# 1662 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAppear:
# 1663 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Blacephalon! And that\n"
# 1664 "data/maps/CherrygroveCity/scripts.pory"
	.string "is- what is that?\p"
# 1665 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Stakataka! Whoa.\p"
# 1666 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's not one Pokémon,\n"
# 1667 "data/maps/CherrygroveCity/scripts.pory"
	.string "cousin.\p"
# 1668 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's a whole crowd of them,\n"
# 1669 "data/maps/CherrygroveCity/scripts.pory"
	.string "stacked up.$"
# 1670 "data/maps/CherrygroveCity/scripts.pory"

# 1671 "data/maps/CherrygroveCity/scripts.pory"
@ The synergy, corrected on camera: he had the mechanism wrong, and being
# 1672 "data/maps/CherrygroveCity/scripts.pory"
@ wrong out loud is how he earns the next line.
# 1673 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBSynergy:
# 1674 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Here it comes-don't look\n"
# 1675 "data/maps/CherrygroveCity/scripts.pory"
	.string "at the ligh-\p"
# 1676 "data/maps/CherrygroveCity/scripts.pory"
	.string "…\p"
# 1677 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Okay. Okay, I had it\n"
# 1678 "data/maps/CherrygroveCity/scripts.pory"
	.string "wrong.\p"
# 1679 "data/maps/CherrygroveCity/scripts.pory"
	.string "It isn't walking in behind the\n"
# 1680 "data/maps/CherrygroveCity/scripts.pory"
	.string "lights.\p"
# 1681 "data/maps/CherrygroveCity/scripts.pory"
	.string "It isn't walking at all.\p"
# 1682 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It crossed four lengths\n"
# 1683 "data/maps/CherrygroveCity/scripts.pory"
	.string "while the bay was white.\p"
# 1684 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then we simply do not\n"
# 1685 "data/maps/CherrygroveCity/scripts.pory"
	.string "blink.\p"
# 1686 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}That's the problem,\n"
# 1687 "data/maps/CherrygroveCity/scripts.pory"
	.string "cousin.\p"
# 1688 "data/maps/CherrygroveCity/scripts.pory"
	.string "Nobody can not blink.$"
# 1689 "data/maps/CherrygroveCity/scripts.pory"

# 1690 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBSynergyClose:
# 1691 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! It is on top\n"
# 1692 "data/maps/CherrygroveCity/scripts.pory"
	.string "of you-!$"
# 1693 "data/maps/CherrygroveCity/scripts.pory"

# 1694 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiSendsOut:
# 1695 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Not on my beach.\p"
# 1696 "data/maps/CherrygroveCity/scripts.pory"
	.string "Incineroar-BETWEEN them!$"
# 1697 "data/maps/CherrygroveCity/scripts.pory"

# 1698 "data/maps/CherrygroveCity/scripts.pory"
@ The surprise. Four days of lab coat, and nobody thought to ask.
# 1699 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiRevealed:
# 1700 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Professor.\p"
# 1701 "data/maps/CherrygroveCity/scripts.pory"
	.string "You are a civilian.\p"
# 1702 "data/maps/CherrygroveCity/scripts.pory"
	.string "Your file is two pages long.\p"
# 1703 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Yeah, it would be.\p"
# 1704 "data/maps/CherrygroveCity/scripts.pory"
	.string "Nobody back home writes reports\n"
# 1705 "data/maps/CherrygroveCity/scripts.pory"
	.string "on the guy who built the\l"
# 1706 "data/maps/CherrygroveCity/scripts.pory"
	.string "League.\p"
# 1707 "data/maps/CherrygroveCity/scripts.pory"
	.string "Alola didn't have one. I made\n"
# 1708 "data/maps/CherrygroveCity/scripts.pory"
	.string "it.\p"
# 1709 "data/maps/CherrygroveCity/scripts.pory"
	.string "Then somebody had to stand at\n"
# 1710 "data/maps/CherrygroveCity/scripts.pory"
	.string "the end of it, and that was me\l"
# 1711 "data/maps/CherrygroveCity/scripts.pory"
	.string "too. For a while.\p"
# 1712 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}…Sir. I apologise for\n"
# 1713 "data/maps/CherrygroveCity/scripts.pory"
	.string "the file.\p"
# 1714 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Keep it! It's restful.\p"
# 1715 "data/maps/CherrygroveCity/scripts.pory"
	.string "Now quit looking at me. That\n"
# 1716 "data/maps/CherrygroveCity/scripts.pory"
	.string "thing in the water isn't done.$"
# 1717 "data/maps/CherrygroveCity/scripts.pory"

# 1718 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaTargets:
# 1719 "data/maps/CherrygroveCity/scripts.pory"
	.string "The creature turns.\p"
# 1720 "data/maps/CherrygroveCity/scripts.pory"
	.string "Not toward the Professor.\n"
# 1721 "data/maps/CherrygroveCity/scripts.pory"
	.string "Not toward the Ultra Beasts.\p"
# 1722 "data/maps/CherrygroveCity/scripts.pory"
	.string "Toward you.\p"
# 1723 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}-MOVE!$"
# 1724 "data/maps/CherrygroveCity/scripts.pory"

# 1725 "data/maps/CherrygroveCity/scripts.pory"
@ The payoff of the seeds planted in Mahogany and here. She says it standing
# 1726 "data/maps/CherrygroveCity/scripts.pory"
@ up, in five boxes, in the middle of an incident, and then goes back to
# 1727 "data/maps/CherrygroveCity/scripts.pory"
@ work - that is the characterisation, not the biography.
# 1728 "data/maps/CherrygroveCity/scripts.pory"
@ CONTINUITY: New Bark (Mission 4) is now the REST of it, not the news.
# 1729 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelFaller:
# 1730 "data/maps/CherrygroveCity/scripts.pory"
	.string "She is in front of you before\n"
# 1731 "data/maps/CherrygroveCity/scripts.pory"
	.string "you have finished turning your\l"
# 1732 "data/maps/CherrygroveCity/scripts.pory"
	.string "head.\p"
# 1733 "data/maps/CherrygroveCity/scripts.pory"
	.string "The bay goes white.\p"
# 1734 "data/maps/CherrygroveCity/scripts.pory"
	.string "When it comes back, Anabel is\n"
# 1735 "data/maps/CherrygroveCity/scripts.pory"
	.string "on one knee in the wet sand.\p"
# 1736 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}CHIEF-\p"
# 1737 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'm here. I'm here.\p"
# 1738 "data/maps/CherrygroveCity/scripts.pory"
	.string "Let go, Looker. I can stand.\p"
# 1739 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}. You should hear this\n"
# 1740 "data/maps/CherrygroveCity/scripts.pory"
	.string "from me, and not from a file.\p"
# 1741 "data/maps/CherrygroveCity/scripts.pory"
	.string "I knew it was coming because I\n"
# 1742 "data/maps/CherrygroveCity/scripts.pory"
	.string "have been on the other side of\l"
# 1743 "data/maps/CherrygroveCity/scripts.pory"
	.string "one.\p"
# 1744 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm a Faller. I came through a\n"
# 1745 "data/maps/CherrygroveCity/scripts.pory"
	.string "tear like that one.\p"
# 1746 "data/maps/CherrygroveCity/scripts.pory"
	.string "There are years of me I have\n"
# 1747 "data/maps/CherrygroveCity/scripts.pory"
	.string "not got back.\p"
# 1748 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Chief.\p"
# 1749 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The rest of it later.\p"
# 1750 "data/maps/CherrygroveCity/scripts.pory"
	.string "There are two of them in the\n"
# 1751 "data/maps/CherrygroveCity/scripts.pory"
	.string "water and one of you.\p"
# 1752 "data/maps/CherrygroveCity/scripts.pory"
	.string "Professor. Your plan. Now.$"
# 1753 "data/maps/CherrygroveCity/scripts.pory"

# 1754 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBChoosePrompt:
# 1755 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Right. Call it,\n"
# 1756 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}! Which one do you\l"
# 1757 "data/maps/CherrygroveCity/scripts.pory"
	.string "want?\p"
# 1758 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll take whatever's left, and\n"
# 1759 "data/maps/CherrygroveCity/scripts.pory"
	.string "I will keep it looking at me.\p"
# 1760 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's the whole trick.\p"
# 1761 "data/maps/CherrygroveCity/scripts.pory"
	.string "Nobody gets to hide.$"
# 1762 "data/maps/CherrygroveCity/scripts.pory"

# 1763 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_ChoiceBlacephalon:
# 1764 "data/maps/CherrygroveCity/scripts.pory"
	.string "Blacephalon$"
# 1765 "data/maps/CherrygroveCity/scripts.pory"

# 1766 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_ChoiceStakataka:
# 1767 "data/maps/CherrygroveCity/scripts.pory"
	.string "Stakataka$"
# 1768 "data/maps/CherrygroveCity/scripts.pory"

# 1769 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPickedBlacephalon:
# 1770 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}The bright one's yours!\p"
# 1771 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't watch the lights. Watch\n"
# 1772 "data/maps/CherrygroveCity/scripts.pory"
	.string "the water under it.\p"
# 1773 "data/maps/CherrygroveCity/scripts.pory"
	.string "I've got the wall.\n"
# 1774 "data/maps/CherrygroveCity/scripts.pory"
	.string "Incineroar, eyes on the big\l"
# 1775 "data/maps/CherrygroveCity/scripts.pory"
	.string "guy-don't lose it!$"
# 1776 "data/maps/CherrygroveCity/scripts.pory"

# 1777 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPickedStakataka:
# 1778 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}The wall is yours!\p"
# 1779 "data/maps/CherrygroveCity/scripts.pory"
	.string "Get under it before it\n"
# 1780 "data/maps/CherrygroveCity/scripts.pory"
	.string "settles!\p"
# 1781 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll take the fireworks.\n"
# 1782 "data/maps/CherrygroveCity/scripts.pory"
	.string "Incineroar, close your eyes-\l"
# 1783 "data/maps/CherrygroveCity/scripts.pory"
	.string "you won't need them!$"
# 1784 "data/maps/CherrygroveCity/scripts.pory"

# 1785 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBGotAway:
# 1786 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The light closed over\n"
# 1787 "data/maps/CherrygroveCity/scripts.pory"
	.string "them.\p"
# 1788 "data/maps/CherrygroveCity/scripts.pory"
	.string "We are back where we started.\p"
# 1789 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Then we go again.\p"
# 1790 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm not leaving this beach\n"
# 1791 "data/maps/CherrygroveCity/scripts.pory"
	.string "either.\p"
# 1792 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Heal, and come back.\n"
# 1793 "data/maps/CherrygroveCity/scripts.pory"
	.string "We hold here.$"
# 1794 "data/maps/CherrygroveCity/scripts.pory"

# 1795 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiFoughtStakataka:
# 1796 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Incineroar-through the\n"
# 1797 "data/maps/CherrygroveCity/scripts.pory"
	.string "middle! Don't let it set!\p"
# 1798 "data/maps/CherrygroveCity/scripts.pory"
	.string "…Down.\p"
# 1799 "data/maps/CherrygroveCity/scripts.pory"
	.string "It never got to settle once.\p"
# 1800 "data/maps/CherrygroveCity/scripts.pory"
	.string "Thing weighs as much as a\n"
# 1801 "data/maps/CherrygroveCity/scripts.pory"
	.string "house, cousin.\p"
# 1802 "data/maps/CherrygroveCity/scripts.pory"
	.string "But a house still has to decide\n"
# 1803 "data/maps/CherrygroveCity/scripts.pory"
	.string "where to stand.$"
# 1804 "data/maps/CherrygroveCity/scripts.pory"

# 1805 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiFoughtBlacephalon:
# 1806 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Eyes shut, Incineroar!\n"
# 1807 "data/maps/CherrygroveCity/scripts.pory"
	.string "Swing where it was!\p"
# 1808 "data/maps/CherrygroveCity/scripts.pory"
	.string "…Yeah. That's it.\p"
# 1809 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's the one thing all those\n"
# 1810 "data/maps/CherrygroveCity/scripts.pory"
	.string "lights can't beat.\p"
# 1811 "data/maps/CherrygroveCity/scripts.pory"
	.string "Somebody who isn't looking.$"
# 1812 "data/maps/CherrygroveCity/scripts.pory"

# 1813 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAbsorbed:
# 1814 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Hey-hey!\n"
# 1815 "data/maps/CherrygroveCity/scripts.pory"
	.string "What is it doing?\p"
# 1816 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}It took them.\n"
# 1817 "data/maps/CherrygroveCity/scripts.pory"
	.string "Both of them.\p"
# 1818 "data/maps/CherrygroveCity/scripts.pory"
	.string "It did not fight them.\p"
# 1819 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}That's feeding.\p"
# 1820 "data/maps/CherrygroveCity/scripts.pory"
	.string "I have watched a lot of things\n"
# 1821 "data/maps/CherrygroveCity/scripts.pory"
	.string "eat. That's feeding.\p"
# 1822 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And nothing that comes\n"
# 1823 "data/maps/CherrygroveCity/scripts.pory"
	.string "through a tear behaves like\l"
# 1824 "data/maps/CherrygroveCity/scripts.pory"
	.string "that.\p"
# 1825 "data/maps/CherrygroveCity/scripts.pory"
	.string "It doesn't come through them.\p"
# 1826 "data/maps/CherrygroveCity/scripts.pory"
	.string "It opens them.$"
# 1827 "data/maps/CherrygroveCity/scripts.pory"

# 1828 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaSensesCosmog:
# 1829 "data/maps/CherrygroveCity/scripts.pory"
	.string "The creature is staring past\n"
# 1830 "data/maps/CherrygroveCity/scripts.pory"
	.string "you… at the Poké Ball that\l"
# 1831 "data/maps/CherrygroveCity/scripts.pory"
	.string "holds your {STR_VAR_1}.\p"
# 1832 "data/maps/CherrygroveCity/scripts.pory"
	.string "Your {STR_VAR_1} is trembling.\p"
# 1833 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Incineroar! In front!\n"
# 1834 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't let it any closer!$"
# 1835 "data/maps/CherrygroveCity/scripts.pory"

# 1836 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaSensesLegend:
# 1837 "data/maps/CherrygroveCity/scripts.pory"
	.string "Light flares between the\n"
# 1838 "data/maps/CherrygroveCity/scripts.pory"
	.string "creature and your\l"
# 1839 "data/maps/CherrygroveCity/scripts.pory"
	.string "{STR_VAR_1}'s Poké Ball!\p"
# 1840 "data/maps/CherrygroveCity/scripts.pory"
	.string "It pulls back… then steadies,\n"
# 1841 "data/maps/CherrygroveCity/scripts.pory"
	.string "and stares.\p"
# 1842 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}…It flinched.\n"
# 1843 "data/maps/CherrygroveCity/scripts.pory"
	.string "Cousin, that thing flinched.$"
# 1844 "data/maps/CherrygroveCity/scripts.pory"

# 1845 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaGone:
# 1846 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}…And it's gone.\p"
# 1847 "data/maps/CherrygroveCity/scripts.pory"
	.string "Back through a hole it made\n"
# 1848 "data/maps/CherrygroveCity/scripts.pory"
	.string "itself.\p"
# 1849 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}It opened the sky over a\n"
# 1850 "data/maps/CherrygroveCity/scripts.pory"
	.string "town, ate what came out of it,\l"
# 1851 "data/maps/CherrygroveCity/scripts.pory"
	.string "and left.\p"
# 1852 "data/maps/CherrygroveCity/scripts.pory"
	.string "That is the third time.$"
# 1853 "data/maps/CherrygroveCity/scripts.pory"

# 1854 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermath:
# 1855 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Is anyone hurt?\n"
# 1856 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}? Your Pokémon?\p"
# 1857 "data/maps/CherrygroveCity/scripts.pory"
	.string "Chief?\p"
# 1858 "data/maps/CherrygroveCity/scripts.pory"
	.string "…Good. Good.\p"
# 1859 "data/maps/CherrygroveCity/scripts.pory"
	.string "The report can wait a moment.\p"
# 1860 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I am standing, Looker.\p"
# 1861 "data/maps/CherrygroveCity/scripts.pory"
	.string "And you may put all of it in\n"
# 1862 "data/maps/CherrygroveCity/scripts.pory"
	.string "the file this time.\p"
# 1863 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll sign it myself.$"
# 1864 "data/maps/CherrygroveCity/scripts.pory"

# 1865 "data/maps/CherrygroveCity/scripts.pory"
@ The gift of this mission is not an item. It is the founder of a League
# 1866 "data/maps/CherrygroveCity/scripts.pory"
@ telling a Champion he wants them at the end of it.
# 1867 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiRecognition:
# 1868 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}{PLAYER}.\p"
# 1869 "data/maps/CherrygroveCity/scripts.pory"
	.string "That thing about not blinking?\n"
# 1870 "data/maps/CherrygroveCity/scripts.pory"
	.string "Write it down.\p"
# 1871 "data/maps/CherrygroveCity/scripts.pory"
	.string "Somebody out there is going to\n"
# 1872 "data/maps/CherrygroveCity/scripts.pory"
	.string "need it.\p"
# 1873 "data/maps/CherrygroveCity/scripts.pory"
	.string "And listen-when this is\n"
# 1874 "data/maps/CherrygroveCity/scripts.pory"
	.string "finished.\p"
# 1875 "data/maps/CherrygroveCity/scripts.pory"
	.string "Alola has a League now. I put\n"
# 1876 "data/maps/CherrygroveCity/scripts.pory"
	.string "it together myself.\p"
# 1877 "data/maps/CherrygroveCity/scripts.pory"
	.string "It's still missing the one\n"
# 1878 "data/maps/CherrygroveCity/scripts.pory"
	.string "thing you can't build.\p"
# 1879 "data/maps/CherrygroveCity/scripts.pory"
	.string "Somebody worth standing at the\n"
# 1880 "data/maps/CherrygroveCity/scripts.pory"
	.string "end of it.\p"
# 1881 "data/maps/CherrygroveCity/scripts.pory"
	.string "Come take a swing at it,\n"
# 1882 "data/maps/CherrygroveCity/scripts.pory"
	.string "cousin. I mean that.$"
# 1883 "data/maps/CherrygroveCity/scripts.pory"

# 1884 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathCosmog:
# 1885 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}It looked at your\n"
# 1886 "data/maps/CherrygroveCity/scripts.pory"
	.string "{STR_VAR_1}.\p"
# 1887 "data/maps/CherrygroveCity/scripts.pory"
	.string "Not at me. Not at the Ultra\n"
# 1888 "data/maps/CherrygroveCity/scripts.pory"
	.string "Beasts. At that.\p"
# 1889 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}A child of the stars,\n"
# 1890 "data/maps/CherrygroveCity/scripts.pory"
	.string "and a thing made of light.\p"
# 1891 "data/maps/CherrygroveCity/scripts.pory"
	.string "Keep it where you can reach it,\n"
# 1892 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}.$"
# 1893 "data/maps/CherrygroveCity/scripts.pory"

# 1894 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathLegend:
# 1895 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}It pulled back from\n"
# 1896 "data/maps/CherrygroveCity/scripts.pory"
	.string "your {STR_VAR_1}. I saw it.\p"
# 1897 "data/maps/CherrygroveCity/scripts.pory"
	.string "Back home, {STR_VAR_1} is the\n"
# 1898 "data/maps/CherrygroveCity/scripts.pory"
	.string "sky itself, cousin.\p"
# 1899 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Whatever that creature\n"
# 1900 "data/maps/CherrygroveCity/scripts.pory"
	.string "is made of, it knew exactly\l"
# 1901 "data/maps/CherrygroveCity/scripts.pory"
	.string "what it was looking at.\p"
# 1902 "data/maps/CherrygroveCity/scripts.pory"
	.string "That is worth more than my\n"
# 1903 "data/maps/CherrygroveCity/scripts.pory"
	.string "instruments gave me all week.$"
# 1904 "data/maps/CherrygroveCity/scripts.pory"

# 1905 "data/maps/CherrygroveCity/scripts.pory"
@ Hook: NO destination. Olivine reveals Mission 4.
# 1906 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBHook:
# 1907 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Professor, you will now\n"
# 1908 "data/maps/CherrygroveCity/scripts.pory"
	.string "come off this beach and eat\l"
# 1909 "data/maps/CherrygroveCity/scripts.pory"
	.string "something.\p"
# 1910 "data/maps/CherrygroveCity/scripts.pory"
	.string "That is not a request.\p"
# 1911 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Yeah, yeah.\p"
# 1912 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The readings haven't\n"
# 1913 "data/maps/CherrygroveCity/scripts.pory"
	.string "settled. It will open another\l"
# 1914 "data/maps/CherrygroveCity/scripts.pory"
	.string "one.\p"
# 1915 "data/maps/CherrygroveCity/scripts.pory"
	.string "Where, and when, we don't know\n"
# 1916 "data/maps/CherrygroveCity/scripts.pory"
	.string "yet.\p"
# 1917 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}So we keep watching.\p"
# 1918 "data/maps/CherrygroveCity/scripts.pory"
	.string "Rest, {PLAYER}. Then come back\n"
# 1919 "data/maps/CherrygroveCity/scripts.pory"
	.string "to our house in Olivine.\p"
# 1920 "data/maps/CherrygroveCity/scripts.pory"
	.string "The moment something opens, you\n"
# 1921 "data/maps/CherrygroveCity/scripts.pory"
	.string "will be the first to know.\p"
# 1922 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}I'm going home,\n"
# 1923 "data/maps/CherrygroveCity/scripts.pory"
	.string "cousin. But not tonight.\p"
# 1924 "data/maps/CherrygroveCity/scripts.pory"
	.string "Tonight I'm going to sit in\n"
# 1925 "data/maps/CherrygroveCity/scripts.pory"
	.string "every library in this region\l"
# 1926 "data/maps/CherrygroveCity/scripts.pory"
	.string "and read every log nobody\l"
# 1927 "data/maps/CherrygroveCity/scripts.pory"
	.string "thought was worth sending.\p"
# 1928 "data/maps/CherrygroveCity/scripts.pory"
	.string "Somebody out there has been\n"
# 1929 "data/maps/CherrygroveCity/scripts.pory"
	.string "writing this down for weeks and\l"
# 1930 "data/maps/CherrygroveCity/scripts.pory"
	.string "calling it a broken sensor.\p"
# 1931 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'd bet the League on it.$"
# 1932 "data/maps/CherrygroveCity/scripts.pory"

# 1933 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 1934 "data/maps/CherrygroveCity/scripts.pory"
@ Post-game beach (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.7).
# 1935 "data/maps/CherrygroveCity/scripts.pory"
@ Two separate rotas: Kukui on Mon/Tue/Thu/Sat, Lillie on Tue/Thu/Sat. Kukui is
# 1936 "data/maps/CherrygroveCity/scripts.pory"
@ here on Monday on his own, which is the point - he is the one who cannot leave
# 1937 "data/maps/CherrygroveCity/scripts.pory"
@ the readings alone.
# 1938 "data/maps/CherrygroveCity/scripts.pory"
@ Both windows are closed below state 16, so nothing of this exists until the
# 1939 "data/maps/CherrygroveCity/scripts.pory"
@ farewell at the altar has played.
# 1940 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 1941 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyPostKukui::
# 1942 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CherrygroveCity_EventScript_HidePostKukui
# 1943 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetDayOfWeek
# 1944 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_MON, CherrygroveCity_EventScript_ShowPostKukui
# 1945 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CherrygroveCity_EventScript_ShowPostKukui
# 1946 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_THU, CherrygroveCity_EventScript_ShowPostKukui
# 1947 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CherrygroveCity_EventScript_ShowPostKukui
# 1948 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HidePostKukui::
# 1949 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_7
# 1950 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1951 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ShowPostKukui::
# 1952 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_7
# 1953 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1954 "data/maps/CherrygroveCity/scripts.pory"

# 1955 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyPostLillie::
# 1956 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CherrygroveCity_EventScript_HidePostLillie
# 1957 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetDayOfWeek
# 1958 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CherrygroveCity_EventScript_ShowPostLillie
# 1959 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_THU, CherrygroveCity_EventScript_ShowPostLillie
# 1960 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CherrygroveCity_EventScript_ShowPostLillie
# 1961 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HidePostLillie::
# 1962 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_8
# 1963 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1964 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ShowPostLillie::
# 1965 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_8
# 1966 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1967 "data/maps/CherrygroveCity/scripts.pory"

# 1968 "data/maps/CherrygroveCity/scripts.pory"
@ One box of character, then the rematch if today's daily flag is still clear.
# 1969 "data/maps/CherrygroveCity/scripts.pory"
@ A normal trainer battle: no B_FLAG_NO_WHITEOUT, because losing to a post-game
# 1970 "data/maps/CherrygroveCity/scripts.pory"
@ trainer is a normal blackout. The narrative duel of this arc was Act II at the
# 1971 "data/maps/CherrygroveCity/scripts.pory"
@ altar and it is over.
# 1972 "data/maps/CherrygroveCity/scripts.pory"
@ The daily flag is set BEFORE the battle: after is unreachable on a loss,
# 1973 "data/maps/CherrygroveCity/scripts.pory"
@ because the blackout never comes back here. Losing spends the day, which is
# 1974 "data/maps/CherrygroveCity/scripts.pory"
@ the right behaviour for a rematch.
# 1975 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostKukui::
# 1976 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 1977 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 1978 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukui, MSGBOX_DEFAULT
# 1979 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1980 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_DAILY_REMATCH_KUKUI, CherrygroveCity_EventScript_PostKukuiDone
# 1981 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiRematchAsk, MSGBOX_YESNO
# 1982 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_PostKukuiNo
# 1983 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_DAILY_REMATCH_KUKUI
# 1984 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_KUKUI, CherrygroveCity_Text_BeachKukuiBeaten
# 1985 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiAfter, MSGBOX_DEFAULT
# 1986 "data/maps/CherrygroveCity/scripts.pory"
	release
# 1987 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1988 "data/maps/CherrygroveCity/scripts.pory"

# 1989 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostKukuiNo::
# 1990 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiRematchNo, MSGBOX_DEFAULT
# 1991 "data/maps/CherrygroveCity/scripts.pory"
	release
# 1992 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1993 "data/maps/CherrygroveCity/scripts.pory"

# 1994 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostKukuiDone::
# 1995 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiDoneToday, MSGBOX_DEFAULT
# 1996 "data/maps/CherrygroveCity/scripts.pory"
	release
# 1997 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1998 "data/maps/CherrygroveCity/scripts.pory"

# 1999 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostLillie::
# 2000 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 2001 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 2002 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillie, MSGBOX_DEFAULT
# 2003 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 2004 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_DAILY_REMATCH_LILLIE, CherrygroveCity_EventScript_PostLillieDone
# 2005 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieRematchAsk, MSGBOX_YESNO
# 2006 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_PostLillieNo
# 2007 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_DAILY_REMATCH_LILLIE
# 2008 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_LILLIE_POSTGAME, CherrygroveCity_Text_BeachLillieBeaten
# 2009 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieAfter, MSGBOX_DEFAULT
# 2010 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2011 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2012 "data/maps/CherrygroveCity/scripts.pory"

# 2013 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostLillieNo::
# 2014 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieRematchNo, MSGBOX_DEFAULT
# 2015 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2016 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2017 "data/maps/CherrygroveCity/scripts.pory"

# 2018 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostLillieDone::
# 2019 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieDoneToday, MSGBOX_DEFAULT
# 2020 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2021 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2022 "data/maps/CherrygroveCity/scripts.pory"

# 2023 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukui:
# 2024 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}{PLAYER}! Hey! Look who the boat\n"
# 2025 "data/maps/CherrygroveCity/scripts.pory"
	.string "brought!\p"
# 2026 "data/maps/CherrygroveCity/scripts.pory"
	.string "I flew back to Alola, I walked into my\n"
# 2027 "data/maps/CherrygroveCity/scripts.pory"
	.string "own lab, I looked at my own desk for\l"
# 2028 "data/maps/CherrygroveCity/scripts.pory"
	.string "about four minutes, and then I got back\l"
# 2029 "data/maps/CherrygroveCity/scripts.pory"
	.string "on a boat. Burnet says hello and also\l"
# 2030 "data/maps/CherrygroveCity/scripts.pory"
	.string "that she is not surprised.\p"
# 2031 "data/maps/CherrygroveCity/scripts.pory"
	.string "This beach, {PLAYER}. Something\n"
# 2032 "data/maps/CherrygroveCity/scripts.pory"
	.string "happened on this beach and the sand\l"
# 2033 "data/maps/CherrygroveCity/scripts.pory"
	.string "still knows about it. I've got readings\l"
# 2034 "data/maps/CherrygroveCity/scripts.pory"
	.string "I can't explain and I have never been\l"
# 2035 "data/maps/CherrygroveCity/scripts.pory"
	.string "happier.$"
# 2036 "data/maps/CherrygroveCity/scripts.pory"

# 2037 "data/maps/CherrygroveCity/scripts.pory"
@ the YES/NO
# 2038 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiRematchAsk:
# 2039 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Hold on, hold on. Before the science.\p"
# 2040 "data/maps/CherrygroveCity/scripts.pory"
	.string "You're the Champion of Johto, you've\n"
# 2041 "data/maps/CherrygroveCity/scripts.pory"
	.string "got a Necrozma in that team, and you\l"
# 2042 "data/maps/CherrygroveCity/scripts.pory"
	.string "have never once had to fight me for\l"
# 2043 "data/maps/CherrygroveCity/scripts.pory"
	.string "anything.\p"
# 2044 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's been bothering me for weeks.\n"
# 2045 "data/maps/CherrygroveCity/scripts.pory"
	.string "Let's fix it. Right here, feet in the\l"
# 2046 "data/maps/CherrygroveCity/scripts.pory"
	.string "water. What do you say?$"
# 2047 "data/maps/CherrygroveCity/scripts.pory"

# 2048 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiRematchNo:
# 2049 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Ha! Fine, fine. I'll be here measuring\n"
# 2050 "data/maps/CherrygroveCity/scripts.pory"
	.string "sand.\p"
# 2051 "data/maps/CherrygroveCity/scripts.pory"
	.string "Come back when you feel like it.$"
# 2052 "data/maps/CherrygroveCity/scripts.pory"

# 2053 "data/maps/CherrygroveCity/scripts.pory"
@ trainer defeat text
# 2054 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiBeaten:
# 2055 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}WOO! Yeah! That's the Champion!$"
# 2056 "data/maps/CherrygroveCity/scripts.pory"

# 2057 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiAfter:
# 2058 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Okay. OKAY. Now I've got data on you\n"
# 2059 "data/maps/CherrygroveCity/scripts.pory"
	.string "too.\p"
# 2060 "data/maps/CherrygroveCity/scripts.pory"
	.string "Same time tomorrow? …No, don't answer\n"
# 2061 "data/maps/CherrygroveCity/scripts.pory"
	.string "that. Just turn up.$"
# 2062 "data/maps/CherrygroveCity/scripts.pory"

# 2063 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiDoneToday:
# 2064 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}One a day, {PLAYER}! My Incineroar has a\n"
# 2065 "data/maps/CherrygroveCity/scripts.pory"
	.string "schedule and I am not the one who set\l"
# 2066 "data/maps/CherrygroveCity/scripts.pory"
	.string "it.$"
# 2067 "data/maps/CherrygroveCity/scripts.pory"

# 2068 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillie:
# 2069 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Hello. I hoped you'd come by.\p"
# 2070 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm not helping the professor, before\n"
# 2071 "data/maps/CherrygroveCity/scripts.pory"
	.string "you ask. I have my own notebook now,\l"
# 2072 "data/maps/CherrygroveCity/scripts.pory"
	.string "and it is about something completely\l"
# 2073 "data/maps/CherrygroveCity/scripts.pory"
	.string "different, and he is not allowed to read\l"
# 2074 "data/maps/CherrygroveCity/scripts.pory"
	.string "it.\p"
# 2075 "data/maps/CherrygroveCity/scripts.pory"
	.string "…It's about the nine of them. Where\n"
# 2076 "data/maps/CherrygroveCity/scripts.pory"
	.string "they came from. Somebody should be\l"
# 2077 "data/maps/CherrygroveCity/scripts.pory"
	.string "writing that down from the side of the\l"
# 2078 "data/maps/CherrygroveCity/scripts.pory"
	.string "ones who got eaten.$"
# 2079 "data/maps/CherrygroveCity/scripts.pory"

# 2080 "data/maps/CherrygroveCity/scripts.pory"
@ the YES/NO
# 2081 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieRematchAsk:
# 2082 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Before you go. Would you battle me?\p"
# 2083 "data/maps/CherrygroveCity/scripts.pory"
	.string "I know. You've beaten me in a flower\n"
# 2084 "data/maps/CherrygroveCity/scripts.pory"
	.string "shop, in a shrine and on a road. That's\l"
# 2085 "data/maps/CherrygroveCity/scripts.pory"
	.string "rather the point -- you have a very\l"
# 2086 "data/maps/CherrygroveCity/scripts.pory"
	.string "good record and I would like to ruin it.\p"
# 2087 "data/maps/CherrygroveCity/scripts.pory"
	.string "She's not a Vulpix any more, {PLAYER}.\n"
# 2088 "data/maps/CherrygroveCity/scripts.pory"
	.string "Look at her properly this time.$"
# 2089 "data/maps/CherrygroveCity/scripts.pory"

# 2090 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieRematchNo:
# 2091 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Of course. Another day.\p"
# 2092 "data/maps/CherrygroveCity/scripts.pory"
	.string "She'll be disappointed. She has been\n"
# 2093 "data/maps/CherrygroveCity/scripts.pory"
	.string "practising in front of the sea.$"
# 2094 "data/maps/CherrygroveCity/scripts.pory"

# 2095 "data/maps/CherrygroveCity/scripts.pory"
@ trainer defeat text
# 2096 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieBeaten:
# 2097 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}…There it is again.\p"
# 2098 "data/maps/CherrygroveCity/scripts.pory"
	.string "Thank you. I mean that.$"
# 2099 "data/maps/CherrygroveCity/scripts.pory"

# 2100 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieAfter:
# 2101 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Your record survives. I'm writing that\n"
# 2102 "data/maps/CherrygroveCity/scripts.pory"
	.string "down too, and I'm writing it down\l"
# 2103 "data/maps/CherrygroveCity/scripts.pory"
	.string "crossly.$"
# 2104 "data/maps/CherrygroveCity/scripts.pory"

# 2105 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieDoneToday:
# 2106 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Once a day is plenty. She sulks, and\n"
# 2107 "data/maps/CherrygroveCity/scripts.pory"
	.string "then she sleeps in the sun, and then\l"
# 2108 "data/maps/CherrygroveCity/scripts.pory"
	.string "she forgives me.$"

Cherrygrove_FadedSign_Text_0:
# 587 "data/maps/CherrygroveCity/scripts.pory"
	.string "Cherrygrove inn...\n"
	.string "The text is too faded to read.$"

Cherrygrove_DarkraiEventDoor_Text_0:
# 594 "data/maps/CherrygroveCity/scripts.pory"
	.string "Darkrai might be residing in this \n"
	.string "old inn.\p"
	.string "It would be best to prepare for\n"
	.string "anything.$"

Cherrygrove_DarkraiEventDoor_Text_1:
# 601 "data/maps/CherrygroveCity/scripts.pory"
	.string "You should also bring Cresselia with \n"
	.string "you.$"

Cherrygrove_DarkraiEventDoor_Text_2:
# 606 "data/maps/CherrygroveCity/scripts.pory"
	.string "Are you absolutely sure you are ready?$"

Cherrygrove_DarkraiEventDoor_Text_3:
# 607 "data/maps/CherrygroveCity/scripts.pory"
	.string "Prepare first$"

Cherrygrove_DarkraiEventDoor_Text_4:
# 607 "data/maps/CherrygroveCity/scripts.pory"
	.string "Go in$"

Cherrygrove_DarkraiEventDoor_Text_5:
# 609 "data/maps/CherrygroveCity/scripts.pory"
	.string "You grab the door handle and-$"

Cherrygrove_DarkraiEventDoor_Text_6:
# 619 "data/maps/CherrygroveCity/scripts.pory"
	.string "Best to prepare first.$"

Cherrygrove_DarkraiEventDoor_Text_7:
# 625 "data/maps/CherrygroveCity/scripts.pory"
	.string "The door won't budge. It seems\n"
	.string "to be stuck.$"

Cherrygrove_Littlegirl_Text_0:
# 636 "data/maps/CherrygroveCity/scripts.pory"
	.string "I saw you dozing off in front of the\n"
	.string "old inn's door. Are you okay?$"

Cherrygrove_Littlegirl_Text_1:
# 641 "data/maps/CherrygroveCity/scripts.pory"
	.string "That inn... I don't think it\n"
	.string "has ever been open. My mom said it was\l"
	.string "abandoned even in her youth.$"

Cherrygrove_Zigzagoon_Text_0:
# 652 "data/maps/CherrygroveCity/scripts.pory"
	.string "Zig!$"

Cherrygrove_Rattata_Text_0:
# 661 "data/maps/CherrygroveCity/scripts.pory"
	.string "Rat!$"

Cherrygrove_TraderNoRoom_Text_0:
# 670 "data/maps/CherrygroveCity/scripts.pory"
	.string "Whoa, hold on there!\p"
	.string "Your team is full, and your storage\n"
	.string "boxes are full too.\p"
	.string "There's nowhere for either of these\n"
	.string "two to go, and I'm not handing one\l"
	.string "over just to have it disappear.\p"
	.string "Make some room and come find me.\n"
	.string "I'll be right here!$"

Cherrygrove_FriendlyTrader_Text_0:
# 689 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hi! Has my Pokémon been helpful?$"

Cherrygrove_FriendlyTrader_Text_1:
# 706 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hello! Are you a new trainer per chance?\p"
	.string "Listen, I received two exotic Pokémon\n"
	.string "as a gift from my uncle in the Safari\l"
	.string "Zone, but I can't keep both. \p"
	.string "Would you be willing to take one of \n"
	.string "them with you?\p"
	.string "I'm sure either one would love to go on\n"
	.string "an adventure with you!$"

Cherrygrove_FriendlyTrader_Text_2:
# 717 "data/maps/CherrygroveCity/scripts.pory"
	.string "Zigzagoon$"

Cherrygrove_FriendlyTrader_Text_3:
# 717 "data/maps/CherrygroveCity/scripts.pory"
	.string "Rattata$"

Cherrygrove_FriendlyTrader_Text_4:
# 717 "data/maps/CherrygroveCity/scripts.pory"
	.string "No thanks$"

Cherrygrove_FriendlyTrader_Text_5:
# 745 "data/maps/CherrygroveCity/scripts.pory"
	.string "Take good care of my {STR_VAR_1}!\p"
	.string "Say hi to my uncle, Baoba if you are\n"
	.string "ever visiting the Safari Zone!$"

Cherrygrove_FriendlyTrader_Text_6:
# 784 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh... That's a shame...$"

Cherrygrove_FriendlyTrader_Text_7:
# 789 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hey! Can I ask you a favour? \p"
	.string "Wait... You don't have any\n"
	.string "Poké Balls...\p"
	.string "Sorry,\n"
	.string "I thought you were a trainer.$"
