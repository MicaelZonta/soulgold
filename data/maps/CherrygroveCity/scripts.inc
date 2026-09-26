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
@ Cast: Looker, Anabel and Professor Kukui (+ Incineroar, out of its Ball only
# 808 "data/maps/CherrygroveCity/scripts.pory"
@ for the interception). Script: CHERRYGROVE_ULTRABEAST_SCRIPT_V2.md, applied
# 809 "data/maps/CherrygroveCity/scripts.pory"
@ 26/09/2026; implementation notes in CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md
# 810 "data/maps/CherrygroveCity/scripts.pory"
@ section 15, which wins over the rest of that file.
# 811 "data/maps/CherrygroveCity/scripts.pory"
@
# 812 "data/maps/CherrygroveCity/scripts.pory"
@ Story in four lines: Kukui has worked out that Blacephalon's flash hides
# 813 "data/maps/CherrygroveCity/scripts.pory"
@ Stakataka's steps. Anabel feels an opening seconds before the meter moves,
# 814 "data/maps/CherrygroveCity/scripts.pory"
@ Necrozma comes out of it, and the flash-and-step trick is shown and blocked by
# 815 "data/maps/CherrygroveCity/scripts.pory"
@ Incineroar. Anabel pulls the player out of a second, small opening; after the
# 816 "data/maps/CherrygroveCity/scripts.pory"
@ win the group throws a Ball BEFORE the pull and the link still wins. Only once
# 817 "data/maps/CherrygroveCity/scripts.pory"
@ the beach is safe does Anabel tell the player she is a Faller; Kukui goes to
# 818 "data/maps/CherrygroveCity/scripts.pory"
@ ask Elm for his readings, which is what opens Mission 4.
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
@ shallow / ocean split below comes from metatile_attributes.bin of
# 829 "data/maps/CherrygroveCity/scripts.pory"
@ johto_general. y grows DOWNWARD.
# 830 "data/maps/CherrygroveCity/scripts.pory"
@
# 831 "data/maps/CherrygroveCity/scripts.pory"
@       x= 21 22 23 24 25 26 27 28 29 30
# 832 "data/maps/CherrygroveCity/scripts.pory"
@   y= 6     #  #  #  #  #  #  #  #  #  #   north wall
# 833 "data/maps/CherrygroveCity/scripts.pory"
@   y= 7     ~  w  w  w  w  U  K  A  .  .   U Kukui (26,7)  K Looker (27,7)
# 834 "data/maps/CherrygroveCity/scripts.pory"
@   y= 8     ~  ~  ~  ~  w  u  t  .  .  .   A Anabel (28,7)
# 835 "data/maps/CherrygroveCity/scripts.pory"
@   y= 9     ~  ~  ~  B  w  i  l  a  .  .   t (27,8) = the ONLY talk tile
# 836 "data/maps/CherrygroveCity/scripts.pory"
@   y=10     R  N  ~  S  s  X  p  P  c  .   B Blacephalon (24,9)
# 837 "data/maps/CherrygroveCity/scripts.pory"
@   y=11     ~  ~  ~  w  s  s  s  .  .  .   S Stakataka (24,10), on the SANDBAR
# 838 "data/maps/CherrygroveCity/scripts.pory"
@   y=12     ~  ~  ~  ~  w  s  s  .  .  #   N Necrozma (22,10)  R rift (21,10)
# 839 "data/maps/CherrygroveCity/scripts.pory"
@
# 840 "data/maps/CherrygroveCity/scripts.pory"
@   ~  MB_OCEAN_WATER   - Surf only; the player on foot can NOT enter
# 841 "data/maps/CherrygroveCity/scripts.pory"
@   w  MB_SHALLOW_WATER - collision 0; the player on foot DOES walk on it
# 842 "data/maps/CherrygroveCity/scripts.pory"
@   s  MB_SAND
# 843 "data/maps/CherrygroveCity/scripts.pory"
@
# 844 "data/maps/CherrygroveCity/scripts.pory"
@ THE SANDBAR (V2 section 5): (24,10) and (24,11) were ocean. They are now the
# 845 "data/maps/CherrygroveCity/scripts.pory"
@ two shallow corners of a small bar (metatiles 0x10C / 0x11C, elevation 3) and
# 846 "data/maps/CherrygroveCity/scripts.pory"
@ (25,10)/(25,11) became plain sand behind it. Stakataka WALKS on it: the
# 847 "data/maps/CherrygroveCity/scripts.pory"
@ flash hides its steps, it never teleports. Blacephalon floats over the water
# 848 "data/maps/CherrygroveCity/scripts.pory"
@ at (24,9); Necrozma hovers beside the rift.
# 849 "data/maps/CherrygroveCity/scripts.pory"
@
# 850 "data/maps/CherrygroveCity/scripts.pory"
@ Approach (lower case above): u Kukui (26,8), i Incineroar (26,9), l Looker
# 851 "data/maps/CherrygroveCity/scripts.pory"
@ (27,8), a Anabel (28,9), p player (27,10). Stakataka steps to (25,10) under
# 852 "data/maps/CherrygroveCity/scripts.pory"
@ the flash; Incineroar drops to X = (26,10) BEFORE it can take that tile.
# 853 "data/maps/CherrygroveCity/scripts.pory"
@ After the rescue: Looker (27,9), Anabel (27,10), player P (28,10).
# 854 "data/maps/CherrygroveCity/scripts.pory"
@ Partner (Cosmog family, optional): c = (29,10). Aftermath: Looker (28,9),
# 855 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui (29,10), Anabel (27,10), player (28,10). Nobody at (28,11).
# 856 "data/maps/CherrygroveCity/scripts.pory"
@
# 857 "data/maps/CherrygroveCity/scripts.pory"
@ Looker sits in a pocket: (27,6) is wall, (26,7) is Kukui and (28,7) is
# 858 "data/maps/CherrygroveCity/scripts.pory"
@ Anabel. The ONLY tile he can be talked to from is (27,8), facing up - on
# 859 "data/maps/CherrygroveCity/scripts.pory"
@ the first attempt AND on a retry, because the retry keeps the three of them
# 860 "data/maps/CherrygroveCity/scripts.pory"
@ on their template tiles. That is what makes both form-ups deterministic.
# 861 "data/maps/CherrygroveCity/scripts.pory"
@
# 862 "data/maps/CherrygroveCity/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 863 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_1 - cast visibility cache (Kukui, Looker, Anabel)
# 864 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_2 - Ultra Beast visibility cache
# 865 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_3 - Galarian Zigzagoon gift visibility cache
# 866 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_4 - Alolan Rattata gift visibility cache
# 867 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_5 - Necrozma (its OWN flag: removeobject sets the template flag)
# 868 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_6 - Kukui's Incineroar (same reason)
# 869 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_7 - post-game Kukui on the beach (altar event, section 10.7)
# 870 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_8 - post-game Lillie AND her Ninetales
# 871 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_9 - the rift at (21,10)
# 872 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_A - the player's Cosmog-family Pokemon as an actor: four templates
# 873 "data/maps/CherrygroveCity/scripts.pory"
@                 on (29,10), at most one of them ever added
# 874 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_2  - battle outcome
# 875 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_3  - the player's pick: 0 = Blacephalon, 1 = Stakataka. Survives
# 876 "data/maps/CherrygroveCity/scripts.pory"
@                 the battle (coming back from a battle does not reload the map)
# 877 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_4  - Cosmog-family species shown (SPECIES_NONE = none). Sampled
# 878 "data/maps/CherrygroveCity/scripts.pory"
@                 AFTER the battle, which can evolve it, and kept to the end.
# 879 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: VAR_TEMP_1 is VAR_TEMP_TRANSFERRED_SPECIES (vars.h:370) and
# 880 "data/maps/CherrygroveCity/scripts.pory"
@ belongs to Cherrygrove_FriendlyTrader, above in this file. This mission
# 881 "data/maps/CherrygroveCity/scripts.pory"
@ starts at VAR_TEMP_2 on purpose - do NOT "harmonise" it away.
# 882 "data/maps/CherrygroveCity/scripts.pory"
@
# 883 "data/maps/CherrygroveCity/scripts.pory"
@ Persistent flags of this mission (CUSTOM block), both cleared by UBFinish:
# 884 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_CHERRYGROVE_UB_PREPARED - Kukui's reading has been heard
# 885 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_CHERRYGROVE_UB_ENGAGED  - everything up to the rescue has played;
# 886 "data/maps/CherrygroveCity/scripts.pory"
@                                  a blackout comes back as a retry
# 887 "data/maps/CherrygroveCity/scripts.pory"
@
# 888 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: fourteen residents of this map carry FLAG_EVENT_ULTRABEAST_CHERRYGROVE
# 889 "data/maps/CherrygroveCity/scripts.pory"
@ in their map.json "flag" field. A removeobject on any of them SETS that flag
# 890 "data/maps/CherrygroveCity/scripts.pory"
@ and empties the city.
# 891 "data/maps/CherrygroveCity/scripts.pory"
@
# 892 "data/maps/CherrygroveCity/scripts.pory"
@ Object budget at the fullest moment (partner out, before Necrozma leaves):
# 893 "data/maps/CherrygroveCity/scripts.pory"
@ player + hidden follower + Kukui + Looker + Anabel + Incineroar + Necrozma
# 894 "data/maps/CherrygroveCity/scripts.pory"
@ + rift + partner = 9/16 (the beasts are already gone by then; with them and
# 895 "data/maps/CherrygroveCity/scripts.pory"
@ no partner it is 10/16).
# 896 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 897 "data/maps/CherrygroveCity/scripts.pory"

# 898 "data/maps/CherrygroveCity/scripts.pory"
@ A note, not a person: no speaker plaque (author's decision, Mahogany V3).
# 899 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_DoorLocked::
# 900 "data/maps/CherrygroveCity/scripts.pory"
	lockall
# 901 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_DoorLocked, MSGBOX_DEFAULT
# 902 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 903 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 904 "data/maps/CherrygroveCity/scripts.pory"
	end
# 905 "data/maps/CherrygroveCity/scripts.pory"

# 906 "data/maps/CherrygroveCity/scripts.pory"
@ Called from CherrygroveCity_OnTransition, which runs before any object is
# 907 "data/maps/CherrygroveCity/scripts.pory"
@ spawned - so setflag/clearflag and setobjectxyperm work here and removeobject
# 908 "data/maps/CherrygroveCity/scripts.pory"
@ would not. Temps are zeroed on every load, so this recomputes from scratch.
# 909 "data/maps/CherrygroveCity/scripts.pory"
@ Two shapes of beach while the incident is active:
# 910 "data/maps/CherrygroveCity/scripts.pory"
@   1. first attempt: only the three of them, waiting on their template tiles.
# 911 "data/maps/CherrygroveCity/scripts.pory"
@   2. FLAG_CHERRYGROVE_UB_ENGAGED (a retry after a blackout or an interrupted
# 912 "data/maps/CherrygroveCity/scripts.pory"
@      battle): the rift, Necrozma and both beasts are still there, and
# 913 "data/maps/CherrygroveCity/scripts.pory"
@      Incineroar is holding the shore at (26,10). Kukui, Looker and Anabel
# 914 "data/maps/CherrygroveCity/scripts.pory"
@      stay on their template tiles so the talk tile is still (27,8).
# 915 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyUBVisibility::
# 916 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_2
# 917 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_5
# 918 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_6
# 919 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_9
# 920 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_A
# 921 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_ApplyGiftMonVisibility
# 922 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_HideUBCast
# 923 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_1
# 924 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_CHERRYGROVE_UB_ENGAGED, CherrygroveCity_EventScript_StageUBRetry
# 925 "data/maps/CherrygroveCity/scripts.pory"
	return
# 926 "data/maps/CherrygroveCity/scripts.pory"

# 927 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HideUBCast::
# 928 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_1
# 929 "data/maps/CherrygroveCity/scripts.pory"
	return
# 930 "data/maps/CherrygroveCity/scripts.pory"

# 931 "data/maps/CherrygroveCity/scripts.pory"
@ setobjectxyperm and not setobjectxy: templates are reloaded from the map
# 932 "data/maps/CherrygroveCity/scripts.pory"
@ header on every load, so this never leaks into the next visit.
# 933 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_StageUBRetry::
# 934 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_2
# 935 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_5
# 936 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_6
# 937 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_9
# 938 "data/maps/CherrygroveCity/scripts.pory"
	setobjectxyperm LOCALID_CHERRYGROVE_UB_INCINEROAR, 26, 10
# 939 "data/maps/CherrygroveCity/scripts.pory"
	return
# 940 "data/maps/CherrygroveCity/scripts.pory"

# 941 "data/maps/CherrygroveCity/scripts.pory"
@ The Friendly Trader's two gift Pokemon (locals 16 and 17). Their map.json
# 942 "data/maps/CherrygroveCity/scripts.pory"
@ "flag" field used to be FLAG_PICKED_ZIGZAGOON / FLAG_PICKED_RATTATA, but
# 943 "data/maps/CherrygroveCity/scripts.pory"
@ that field holds ONE flag and the incident needs a second condition, so it
# 944 "data/maps/CherrygroveCity/scripts.pory"
@ now holds a dumb per-visit cache instead - the same pattern as
# 945 "data/maps/CherrygroveCity/scripts.pory"
@ FLAG_HIDE_CIANWOOD_GLADION. FLAG_PICKED_* stays the persistent truth.
# 946 "data/maps/CherrygroveCity/scripts.pory"
@   visible <=> (not picked yet) AND (no incident running)
# 947 "data/maps/CherrygroveCity/scripts.pory"
@ Because the template flag changed, the removeobject in
# 948 "data/maps/CherrygroveCity/scripts.pory"
@ Cherrygrove_FriendlyTrader no longer makes the gift permanent: the
# 949 "data/maps/CherrygroveCity/scripts.pory"
@ explicit setflag(FLAG_PICKED_*) there does. Never delete it.
# 950 "data/maps/CherrygroveCity/scripts.pory"
@ Deliberately preserved: taking one gift still leaves the OTHER one standing
# 951 "data/maps/CherrygroveCity/scripts.pory"
@ in the street. That oddity predates this mission and is not fixed here.
# 952 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyGiftMonVisibility::
# 953 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_3
# 954 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_4
# 955 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_GiftMonsStayHidden
# 956 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_ZIGZAGOON, CherrygroveCity_EventScript_GiftMonRattataOnly
# 957 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_3
# 958 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_GiftMonRattataOnly::
# 959 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_RATTATA, CherrygroveCity_EventScript_GiftMonsStayHidden
# 960 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_4
# 961 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_GiftMonsStayHidden::
# 962 "data/maps/CherrygroveCity/scripts.pory"
	return
# 963 "data/maps/CherrygroveCity/scripts.pory"

# 964 "data/maps/CherrygroveCity/scripts.pory"
@ She follows the player while talking and then goes back to watching the
# 965 "data/maps/CherrygroveCity/scripts.pory"
@ water to the west, where the opening is expected (V2 section 6). The
# 966 "data/maps/CherrygroveCity/scripts.pory"
@ Cosmog-family idle reactions of the old version are gone: the script
# 967 "data/maps/CherrygroveCity/scripts.pory"
@ removed the repeated warnings.
# 968 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAnabel::
# 969 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 970 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 971 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 972 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 973 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_ANABEL, DIR_WEST
# 974 "data/maps/CherrygroveCity/scripts.pory"
	release
# 975 "data/maps/CherrygroveCity/scripts.pory"
	end
# 976 "data/maps/CherrygroveCity/scripts.pory"

# 977 "data/maps/CherrygroveCity/scripts.pory"
@ A short introduction that works without any earlier meeting. On a retry he
# 978 "data/maps/CherrygroveCity/scripts.pory"
@ is holding the line with Incineroar and says so. He is also reachable from
# 979 "data/maps/CherrygroveCity/scripts.pory"
@ (25,7), which is shallow water the player can wade in.
# 980 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukui::
# 981 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 982 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 983 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_CHERRYGROVE_UB_ENGAGED, CherrygroveCity_EventScript_UBKukuiRetryIdle
# 984 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiIdle, MSGBOX_DEFAULT
# 985 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBKukuiEnd
# 986 "data/maps/CherrygroveCity/scripts.pory"

# 987 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukuiRetryIdle::
# 988 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBRetryNotReady, MSGBOX_DEFAULT
# 989 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukuiEnd::
# 990 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 991 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_SOUTH
# 992 "data/maps/CherrygroveCity/scripts.pory"
	release
# 993 "data/maps/CherrygroveCity/scripts.pory"
	end
# 994 "data/maps/CherrygroveCity/scripts.pory"

# 995 "data/maps/CherrygroveCity/scripts.pory"
@ Only reachable from (27,8), facing up. Nothing changes the incident before
# 996 "data/maps/CherrygroveCity/scripts.pory"
@ the YES; the YES is the last exit point.
# 997 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui's reading is told once (FLAG_CHERRYGROVE_UB_PREPARED): declining and
# 998 "data/maps/CherrygroveCity/scripts.pory"
@ coming back from the Center goes straight to Anabel's question.
# 999 "data/maps/CherrygroveCity/scripts.pory"
@ While he talks about the sandbar he turns to it (west); the reading is of
# 1000 "data/maps/CherrygroveCity/scripts.pory"
@ what he saw on the earlier openings, so it needs no track art on screen.
# 1001 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBLooker::
# 1002 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 1003 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 1004 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_CHERRYGROVE_UB_ENGAGED, CherrygroveCity_EventScript_UBLookerRetry
# 1005 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_CHERRYGROVE_UB_PREPARED, CherrygroveCity_EventScript_UBAskReady
# 1006 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerGreet, MSGBOX_DEFAULT
# 1007 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1008 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_WEST
# 1009 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiObservation, MSGBOX_DEFAULT
# 1010 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelObservation, MSGBOX_DEFAULT
# 1011 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiPlan, MSGBOX_DEFAULT
# 1012 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1013 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_SOUTH
# 1014 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_CHERRYGROVE_UB_PREPARED
# 1015 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAskReady::
# 1016 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBReady, MSGBOX_YESNO
# 1017 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_UBNotReady
# 1018 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBScene
# 1019 "data/maps/CherrygroveCity/scripts.pory"

# 1020 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBNotReady::
# 1021 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNotReady, MSGBOX_DEFAULT
# 1022 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1023 "data/maps/CherrygroveCity/scripts.pory"
	release
# 1024 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1025 "data/maps/CherrygroveCity/scripts.pory"

# 1026 "data/maps/CherrygroveCity/scripts.pory"
@ Retry (V2 section 18): nothing already seen is replayed - not the opening,
# 1027 "data/maps/CherrygroveCity/scripts.pory"
@ not Necrozma's arrival, not the interception, not the rescue, and not
# 1028 "data/maps/CherrygroveCity/scripts.pory"
@ Anabel's explanation, which still belongs to the aftermath of a win.
# 1029 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBLookerRetry::
# 1030 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBRetryLooker, MSGBOX_DEFAULT
# 1031 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBRetryKukui, MSGBOX_YESNO
# 1032 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_UBRetryNotReady
# 1033 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBSceneRetry
# 1034 "data/maps/CherrygroveCity/scripts.pory"

# 1035 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBRetryNotReady::
# 1036 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBRetryNotReady, MSGBOX_DEFAULT
# 1037 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1038 "data/maps/CherrygroveCity/scripts.pory"
	release
# 1039 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1040 "data/maps/CherrygroveCity/scripts.pory"

# 1041 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1042 "data/maps/CherrygroveCity/scripts.pory"
@ The scene, first attempt. 100% scripted from the YES to a battle outcome.
# 1043 "data/maps/CherrygroveCity/scripts.pory"
@ The order of the three form-up blocks is LOAD-BEARING: Kukui -> player ->
# 1044 "data/maps/CherrygroveCity/scripts.pory"
@ Looker/Anabel. Looker can only step down once the player has left (27,8).
# 1045 "data/maps/CherrygroveCity/scripts.pory"
@ Tiles walked: (26,8), (27,8..10), (28,8) are sand and (28,9) is normal
# 1046 "data/maps/CherrygroveCity/scripts.pory"
@ ground; nobody steps in water. Kukui stops at (26,8) and not lower: (26,9)
# 1047 "data/maps/CherrygroveCity/scripts.pory"
@ is Incineroar's and (26,10) is the tile it has to take before Stakataka.
# 1048 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1049 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBScene::
# 1050 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1051 "data/maps/CherrygroveCity/scripts.pory"
	lockall
# 1052 "data/maps/CherrygroveCity/scripts.pory"
	hidefollower
# 1053 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_StepDownFaceLeft
# 1054 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1055 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerToLine
# 1056 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1057 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_StepDownFaceLeft
# 1058 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelToLine
# 1059 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1060 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1061 "data/maps/CherrygroveCity/scripts.pory"
	@ Kukui gets his partner out BEFORE the threat is on anyone: competence
# 1062 "data/maps/CherrygroveCity/scripts.pory"
	@ shown early, not a trump card pulled at the last second. Nobody reacts
# 1063 "data/maps/CherrygroveCity/scripts.pory"
	@ to him owning a Pokemon.
# 1064 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiPrepare, MSGBOX_DEFAULT
# 1065 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1066 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_BALL_OPEN
# 1067 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_6
# 1068 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1069 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_INCINEROAR, CRY_MODE_NORMAL
# 1070 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1071 "data/maps/CherrygroveCity/scripts.pory"
	@ Anabel feels it before the meter moves. Local, seconds, and uncertain.
# 1072 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 1073 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, Common_Movement_ExclamationMark
# 1074 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1075 "data/maps/CherrygroveCity/scripts.pory"
	@ The town theme fades out on her warning, not when the creature appears.
# 1076 "data/maps/CherrygroveCity/scripts.pory"
	fadeoutbgm 4
# 1077 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelSenses, MSGBOX_DEFAULT
# 1078 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerMeter, MSGBOX_DEFAULT
# 1079 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelCertain, MSGBOX_DEFAULT
# 1080 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1081 "data/maps/CherrygroveCity/scripts.pory"
	@ ...and only now does the instrument answer.
# 1082 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_M_DETECT
# 1083 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1084 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiWater, MSGBOX_DEFAULT
# 1085 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1086 "data/maps/CherrygroveCity/scripts.pory"
	@ A narrow opening over the water, and the threat theme BEFORE the full
# 1087 "data/maps/CherrygroveCity/scripts.pory"
	@ reveal. save_song TRUE: the boss battle hands this theme back instead of
# 1088 "data/maps/CherrygroveCity/scripts.pory"
	@ the town's (savedMusic). A map load clears savedMusic, so the retry
# 1089 "data/maps/CherrygroveCity/scripts.pory"
	@ starts clean and sets it again.
# 1090 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1091 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1092 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_9
# 1093 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_RIFT
# 1094 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1095 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_WARP_IN
# 1096 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 1097 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1098 "data/maps/CherrygroveCity/scripts.pory"
	@ Necrozma comes out THROUGH it, at (22,10), beside the rift.
# 1099 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1100 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_5
# 1101 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_NECROZMA
# 1102 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1103 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1104 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1105 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
# 1106 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1107 "data/maps/CherrygroveCity/scripts.pory"
	@ It widens the opening; the two come out in separate places, with
# 1108 "data/maps/CherrygroveCity/scripts.pory"
	@ separate cries and a beat to read the silhouettes.
# 1109 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1110 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1111 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBRiftPulse
# 1112 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1113 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_2
# 1114 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1115 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1116 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1117 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
# 1118 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1119 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 1120 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1121 "data/maps/CherrygroveCity/scripts.pory"
	delay 30
# 1122 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAppear, MSGBOX_DEFAULT
# 1123 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1124 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBFlashTrick
# 1125 "data/maps/CherrygroveCity/scripts.pory"

# 1126 "data/maps/CherrygroveCity/scripts.pory"
@ THE TRICK OF THE TWO (V2 section 8). Blacephalon's flash hides Stakataka's
# 1127 "data/maps/CherrygroveCity/scripts.pory"
@ STEPS: it walks (24,10) -> (25,10) across the sandbar while the bay is white
# 1128 "data/maps/CherrygroveCity/scripts.pory"
@ and the end of the step is visible as the light drops. No setobjectxy, no
# 1129 "data/maps/CherrygroveCity/scripts.pory"
@ teleport: the movement starts under the white and finishes on screen, with
# 1130 "data/maps/CherrygroveCity/scripts.pory"
@ splashing to tell the player what the characters could not see.
# 1131 "data/maps/CherrygroveCity/scripts.pory"
@ Incineroar then drops from (26,9) to (26,10) BEFORE Stakataka can take it,
# 1132 "data/maps/CherrygroveCity/scripts.pory"
@ and the impact sends it back ONE tile, to (24,10).
# 1133 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBFlashTrick::
# 1134 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, CherrygroveCity_Movement_PulseInPlaceRight
# 1135 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1136 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBFlashWarning, MSGBOX_DEFAULT
# 1137 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1138 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_NORMAL
# 1139 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1140 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, CherrygroveCity_Movement_StakatakaWades
# 1141 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PUDDLE
# 1142 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1143 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1144 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1145 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PUDDLE
# 1146 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1147 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBMovementConfirmed, MSGBOX_DEFAULT
# 1148 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1149 "data/maps/CherrygroveCity/scripts.pory"
	@ It leans for (26,10). The player is already facing west, at it.
# 1150 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, CherrygroveCity_Movement_PulseInPlaceRight
# 1151 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1152 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiIntercept, MSGBOX_DEFAULT
# 1153 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1154 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_IncineroarBlocks
# 1155 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1156 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceLeft
# 1157 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_INCINEROAR, CRY_MODE_ENCOUNTER
# 1158 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1159 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1160 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, CherrygroveCity_Movement_UBKnockedBack
# 1161 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1162 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1163 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PUDDLE
# 1164 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiHold, MSGBOX_DEFAULT
# 1165 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1166 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBRescue
# 1167 "data/maps/CherrygroveCity/scripts.pory"

# 1168 "data/maps/CherrygroveCity/scripts.pory"
@ ANABEL PULLS THE PLAYER OUT (V2 section 9). A small distortion starts to
# 1169 "data/maps/CherrygroveCity/scripts.pory"
@ form where the player stands (sparkles at (27,10)); she sees it before it
# 1170 "data/maps/CherrygroveCity/scripts.pory"
@ has any strength. Strictly sequential, no tile contended:
# 1171 "data/maps/CherrygroveCity/scripts.pory"
@   1. Anabel (28,9)->(27,9), faces south, at the player.
# 1172 "data/maps/CherrygroveCity/scripts.pory"
@   2. Player (27,10)->(28,10), facing preserved (west).
# 1173 "data/maps/CherrygroveCity/scripts.pory"
@   3. The flash and the distortion hit the EMPTY (27,10). Anabel stays north
# 1174 "data/maps/CherrygroveCity/scripts.pory"
@      of it until it is over - she does not take it on her body.
# 1175 "data/maps/CherrygroveCity/scripts.pory"
@   4. Only then Anabel (27,9)->(27,10), faces west.
# 1176 "data/maps/CherrygroveCity/scripts.pory"
@   5. Looker (27,8)->(27,9), faces south, at her.
# 1177 "data/maps/CherrygroveCity/scripts.pory"
@ The player is turned west explicitly after the step and again after the
# 1178 "data/maps/CherrygroveCity/scripts.pory"
@ flash: nothing relies on the facing a movement happened to leave.
# 1179 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBRescue::
# 1180 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1181 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1182 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_M_TELEPORT
# 1183 "data/maps/CherrygroveCity/scripts.pory"
	dofieldeffectsparkle 27, 10, 0
# 1184 "data/maps/CherrygroveCity/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1185 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 1186 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, Common_Movement_ExclamationMark
# 1187 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1188 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelMove, MSGBOX_DEFAULT
# 1189 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1190 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelStepWest
# 1191 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1192 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerPulledAside
# 1193 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1194 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1195 "data/maps/CherrygroveCity/scripts.pory"
	@ The opening snaps shut on nobody.
# 1196 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_M_REFLECT
# 1197 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1198 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1199 "data/maps/CherrygroveCity/scripts.pory"
	dofieldeffectsparkle 27, 10, 0
# 1200 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1201 "data/maps/CherrygroveCity/scripts.pory"
	waitfieldeffect FLDEFF_SPARKLE
# 1202 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1203 "data/maps/CherrygroveCity/scripts.pory"
	delay 20
# 1204 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelTakesTheFront
# 1205 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1206 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_LookerToAnabel
# 1207 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1208 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerChecks, MSGBOX_DEFAULT
# 1209 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelReady, MSGBOX_DEFAULT
# 1210 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1211 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_LOOKER, DIR_WEST
# 1212 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1213 "data/maps/CherrygroveCity/scripts.pory"
	@ Checkpoint: from here on a blackout comes back as a retry, and nothing
# 1214 "data/maps/CherrygroveCity/scripts.pory"
	@ above is ever shown again in this mission.
# 1215 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_CHERRYGROVE_UB_ENGAGED
# 1216 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBChoose
# 1217 "data/maps/CherrygroveCity/scripts.pory"

# 1218 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1219 "data/maps/CherrygroveCity/scripts.pory"
@ Retry after a blackout: the beach was staged by ON_TRANSITION (rift, Necrozma
# 1220 "data/maps/CherrygroveCity/scripts.pory"
@ and both beasts in place, Incineroar at (26,10)). The line forms up into the
# 1221 "data/maps/CherrygroveCity/scripts.pory"
@ post-rescue formation by free paths - nobody pretends the player was pulled
# 1222 "data/maps/CherrygroveCity/scripts.pory"
@ again - and goes straight to the choice.
# 1223 "data/maps/CherrygroveCity/scripts.pory"
@   Kukui   (26,7)->(26,8), faces west.
# 1224 "data/maps/CherrygroveCity/scripts.pory"
@   Player  (27,8)->(28,8)->(28,9)->(28,10), faces west.
# 1225 "data/maps/CherrygroveCity/scripts.pory"
@   Anabel  (28,7)->(28,8)->(27,8)->(27,9)->(27,10), faces west. Walks after
# 1226 "data/maps/CherrygroveCity/scripts.pory"
@           the player has left both (28,8) and (27,8).
# 1227 "data/maps/CherrygroveCity/scripts.pory"
@   Looker  (27,7)->(27,8)->(27,9), faces west. Walks after Anabel.
# 1228 "data/maps/CherrygroveCity/scripts.pory"
@ The threat theme is set again: the map load cleared savedMusic.
# 1229 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1230 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBSceneRetry::
# 1231 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1232 "data/maps/CherrygroveCity/scripts.pory"
	lockall
# 1233 "data/maps/CherrygroveCity/scripts.pory"
	hidefollower
# 1234 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 1235 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_StepDownFaceLeft
# 1236 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1237 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerRetryToLine
# 1238 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1239 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelRetryToFront
# 1240 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1241 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_LookerRetryToLine
# 1242 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1243 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1244 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBChoose
# 1245 "data/maps/CherrygroveCity/scripts.pory"

# 1246 "data/maps/CherrygroveCity/scripts.pory"
@ Flash da cena. fadescreenswapbuffers e NAO fadescreen: fadescreen copia
# 1247 "data/maps/CherrygroveCity/scripts.pory"
@ gPlttBufferFaded -> gPlttBufferUnfaded ao escurecer (src/field_weather.c,
# 1248 "data/maps/CherrygroveCity/scripts.pory"
@ FadeScreen) e o FADE_FROM_* seguinte reaplica o tint de horario por cima do
# 1249 "data/maps/CherrygroveCity/scripts.pory"
@ que ja estava tintado. A noite (coeff 10) cada par de flashes multiplicava a
# 1250 "data/maps/CherrygroveCity/scripts.pory"
@ cena por ~0,46 de novo, e depois de tres ou quatro a cidade ficava preta.
# 1251 "data/maps/CherrygroveCity/scripts.pory"
@ fadescreenswapbuffers usa BLDY no hardware e nao encosta nas paletas.
# 1252 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBFlash::
# 1253 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1254 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1255 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1256 "data/maps/CherrygroveCity/scripts.pory"

# 1257 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBShake::
# 1258 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8004, 1   @ vertical pan
# 1259 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 1260 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8006, 12  @ num shakes
# 1261 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8007, 4   @ shake delay
# 1262 "data/maps/CherrygroveCity/scripts.pory"
	special ShakeCamera
# 1263 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1264 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1265 "data/maps/CherrygroveCity/scripts.pory"

# 1266 "data/maps/CherrygroveCity/scripts.pory"
@ The edge of the rift wavering: a short sideways tremor and the warp sound,
# 1267 "data/maps/CherrygroveCity/scripts.pory"
@ no flash - it must not read as another attack.
# 1268 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBRiftPulse::
# 1269 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_M_TELEPORT
# 1270 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8004, 0
# 1271 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8005, 1
# 1272 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8006, 6
# 1273 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8007, 3
# 1274 "data/maps/CherrygroveCity/scripts.pory"
	special ShakeCamera
# 1275 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1276 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1277 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1278 "data/maps/CherrygroveCity/scripts.pory"

# 1279 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1280 "data/maps/CherrygroveCity/scripts.pory"
@ The split and the battle (V2 section 10). Kukui asks, so the menu wears his
# 1281 "data/maps/CherrygroveCity/scripts.pory"
@ plaque. No cancel (ignoreBPress TRUE): the scene has started. The pick is
# 1282 "data/maps/CherrygroveCity/scripts.pory"
@ per attempt. Positions: player (28,10), Anabel (27,10), Looker (27,9),
# 1283 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui (26,8), Incineroar (26,10); Blacephalon (24,9), Stakataka (24,10).
# 1284 "data/maps/CherrygroveCity/scripts.pory"
@   Blacephalon: Incineroar keeps the south line at (26,10), on Stakataka.
# 1285 "data/maps/CherrygroveCity/scripts.pory"
@   Stakataka:   Incineroar backs up to (26,9) and presses Blacephalon so the
# 1286 "data/maps/CherrygroveCity/scripts.pory"
@                flashes point north, away from the player's front. It only
# 1287 "data/maps/CherrygroveCity/scripts.pory"
@                leaves the south tile once the player has taken that front.
# 1288 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1289 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBChoose::
# 1290 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 1291 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, CherrygroveCity_Text_ChoiceBlacephalon, CherrygroveCity_Text_ChoiceStakataka
# 1292 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Blacephalon, 1 = Stakataka
# 1293 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1294 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBPickStakataka
# 1295 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, Common_Movement_ExclamationMark
# 1296 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1297 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPickedBlacephalon, MSGBOX_DEFAULT
# 1298 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAnabelWatch
# 1299 "data/maps/CherrygroveCity/scripts.pory"

# 1300 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBPickStakataka::
# 1301 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, Common_Movement_ExclamationMark
# 1302 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1303 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPickedStakataka, MSGBOX_DEFAULT
# 1304 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1305 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_IncineroarToNorth
# 1306 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1307 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceLeft
# 1308 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1309 "data/maps/CherrygroveCity/scripts.pory"

# 1310 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAnabelWatch::
# 1311 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelWatch, MSGBOX_DEFAULT
# 1312 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1313 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBBattle
# 1314 "data/maps/CherrygroveCity/scripts.pory"

# 1315 "data/maps/CherrygroveCity/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 1316 "data/maps/CherrygroveCity/scripts.pory"
@ battle - the other reason the mission splits the beasts.
# 1317 "data/maps/CherrygroveCity/scripts.pory"
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
# 1318 "data/maps/CherrygroveCity/scripts.pory"
@ losing means a blackout and a retry.
# 1319 "data/maps/CherrygroveCity/scripts.pory"
@
# 1320 "data/maps/CherrygroveCity/scripts.pory"
@ Third step of the ladder after Blackthorn (3 bars / Lv75 / x120) and
# 1321 "data/maps/CherrygroveCity/scripts.pory"
@ Mahogany (4 / Lv80 / x130). Unchanged by the V2 script. The bars have been
# 1322 "data/maps/CherrygroveCity/scripts.pory"
@ at MAX_BOSS_HEALTH_BARS since Mission 2, so the step up here is the level,
# 1323 "data/maps/CherrygroveCity/scripts.pory"
@ the multiplier and - above all - one control move per boss: Calm Mind on
# 1324 "data/maps/CherrygroveCity/scripts.pory"
@ Blacephalon, Trick Room on Stakataka.
# 1325 "data/maps/CherrygroveCity/scripts.pory"
@ Mind Blown is left off Blacephalon ON PURPOSE: it costs half its max HP,
# 1326 "data/maps/CherrygroveCity/scripts.pory"
@ which on a 4-bar boss is the AI killing itself for free.
# 1327 "data/maps/CherrygroveCity/scripts.pory"
@ If playtesting says "wall" instead of "threat", turn the screws in THIS
# 1328 "data/maps/CherrygroveCity/scripts.pory"
@ order, one at a time:
# 1329 "data/maps/CherrygroveCity/scripts.pory"
@   1. drop ITEM_WEAKNESS_POLICY from Stakataka (highest variance)
# 1330 "data/maps/CherrygroveCity/scripts.pory"
@   2. multiplier 140 -> 135 -> 130
# 1331 "data/maps/CherrygroveCity/scripts.pory"
@   3. swap Trick Room for a fourth attacking move
# 1332 "data/maps/CherrygroveCity/scripts.pory"
@   4. level 85 -> 80
# 1333 "data/maps/CherrygroveCity/scripts.pory"
@
# 1334 "data/maps/CherrygroveCity/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 1335 "data/maps/CherrygroveCity/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 1336 "data/maps/CherrygroveCity/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between, so no
# 1337 "data/maps/CherrygroveCity/scripts.pory"
@ clearbossbattle is needed.
# 1338 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBBattle::
# 1339 "data/maps/CherrygroveCity/scripts.pory"
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
# 1340 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBSetupStakataka
# 1341 "data/maps/CherrygroveCity/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
# 1342 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
# 1343 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1344 "data/maps/CherrygroveCity/scripts.pory"
	seteventmon SPECIES_BLACEPHALON, 85, ITEM_WISE_GLASSES
# 1345 "data/maps/CherrygroveCity/scripts.pory"
	seteventmonmoves MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_FLAMETHROWER, MOVE_PSYSHOCK
# 1346 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBStartBattle
# 1347 "data/maps/CherrygroveCity/scripts.pory"

# 1348 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBSetupStakataka::
# 1349 "data/maps/CherrygroveCity/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
# 1350 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 1351 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1352 "data/maps/CherrygroveCity/scripts.pory"
	seteventmon SPECIES_STAKATAKA, 85, ITEM_WEAKNESS_POLICY
# 1353 "data/maps/CherrygroveCity/scripts.pory"
	seteventmonmoves MOVE_TRICK_ROOM, MOVE_GYRO_BALL, MOVE_STONE_EDGE, MOVE_BODY_PRESS
# 1354 "data/maps/CherrygroveCity/scripts.pory"

# 1355 "data/maps/CherrygroveCity/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the
# 1356 "data/maps/CherrygroveCity/scripts.pory"
@ player out to the Cherrygrove Pokemon Center (CherrygroveCity_OnLoad does
# 1357 "data/maps/CherrygroveCity/scripts.pory"
@ the setrespawn), and FLAG_CHERRYGROVE_UB_ENGAGED makes the next load a
# 1358 "data/maps/CherrygroveCity/scripts.pory"
@ retry. CAUGHT and RAN are unreachable (ball blocked; Run becomes FORFEITED
# 1359 "data/maps/CherrygroveCity/scripts.pory"
@ in a boss) but are handled anyway: anything that is not WON resets to the
# 1360 "data/maps/CherrygroveCity/scripts.pory"
@ retry, never wins it.
# 1361 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBStartBattle::
# 1362 "data/maps/CherrygroveCity/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 1363 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1364 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 1365 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 1366 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, CherrygroveCity_EventScript_UBResolved
# 1367 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBUnresolved
# 1368 "data/maps/CherrygroveCity/scripts.pory"

# 1369 "data/maps/CherrygroveCity/scripts.pory"
@ Interrupted, not lost - and the beasts are still on the shore, so nobody
# 1370 "data/maps/CherrygroveCity/scripts.pory"
@ says they escaped. Nothing is recorded as done; the reload puts the beach
# 1371 "data/maps/CherrygroveCity/scripts.pory"
@ back as a retry. (28,8) is free sand, one step east of Looker's talk tile.
# 1372 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBUnresolved::
# 1373 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBUnresolved, MSGBOX_DEFAULT
# 1374 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1375 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1376 "data/maps/CherrygroveCity/scripts.pory"
	warpsilent MAP_CHERRYGROVE_CITY, 28, 8
# 1377 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1378 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 1379 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1380 "data/maps/CherrygroveCity/scripts.pory"

# 1381 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1382 "data/maps/CherrygroveCity/scripts.pory"
@ After the win (V2 section 11). A battle does not reload the map, so every
# 1383 "data/maps/CherrygroveCity/scripts.pory"
@ object is where the scene left it. The threat theme is set again explicitly
# 1384 "data/maps/CherrygroveCity/scripts.pory"
@ instead of trusting savedMusic alone, and the player is turned west.
# 1385 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui closes his front with one short action of Incineroar - from (26,10)
# 1386 "data/maps/CherrygroveCity/scripts.pory"
@ if the player took Blacephalon, from (26,9) if they took Stakataka; either
# 1387 "data/maps/CherrygroveCity/scripts.pory"
@ way it faces west.
# 1388 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1389 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBResolved::
# 1390 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
# 1391 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1392 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceLeft
# 1393 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_INCINEROAR, CRY_MODE_NORMAL
# 1394 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1395 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1396 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon
# 1397 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiFoughtStakataka, MSGBOX_DEFAULT
# 1398 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBContain
# 1399 "data/maps/CherrygroveCity/scripts.pory"

# 1400 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon::
# 1401 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiFoughtBlacephalon, MSGBOX_DEFAULT
# 1402 "data/maps/CherrygroveCity/scripts.pory"

# 1403 "data/maps/CherrygroveCity/scripts.pory"
@ ANTICIPATION, WITH A LIMIT. Necrozma raises its arms and the meter repeats
# 1404 "data/maps/CherrygroveCity/scripts.pory"
@ the pulse change Mahogany recorded - BEFORE any pull. Anabel throws an
# 1405 "data/maps/CherrygroveCity/scripts.pory"
@ ordinary police Ball (not Kurt's Beast Ball, nothing leaves the player's bag)
# 1406 "data/maps/CherrygroveCity/scripts.pory"
@ at the beast the player beat, from (27,10). The Ball arrives while the beast
# 1407 "data/maps/CherrygroveCity/scripts.pory"
@ is still on its own tile - the team really acted first - and the link to
# 1408 "data/maps/CherrygroveCity/scripts.pory"
@ the rift pulses, breaks the containment and throws the Ball back intact.
# 1409 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBContain::
# 1410 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1411 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1412 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1413 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_M_DETECT
# 1414 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1415 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelWindow, MSGBOX_DEFAULT
# 1416 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1417 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelThrows
# 1418 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_BALL_THROW
# 1419 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1420 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1421 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBTargetStartles
# 1422 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_M_REFLECT
# 1423 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1424 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBRiftPulse
# 1425 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_BALL_BOUNCE_1
# 1426 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1427 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBContainmentFailed, MSGBOX_DEFAULT
# 1428 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1429 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAbsorb
# 1430 "data/maps/CherrygroveCity/scripts.pory"

# 1431 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBTargetStartles::
# 1432 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBTargetStakataka
# 1433 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, Common_Movement_ExclamationMark
# 1434 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1435 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1436 "data/maps/CherrygroveCity/scripts.pory"

# 1437 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBTargetStakataka::
# 1438 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, Common_Movement_ExclamationMark
# 1439 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1440 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1441 "data/maps/CherrygroveCity/scripts.pory"

# 1442 "data/maps/CherrygroveCity/scripts.pory"
@ The absorption is TRIED, not watched: Incineroar hits the light between them
# 1443 "data/maps/CherrygroveCity/scripts.pory"
@ while the pull starts, the filament wavers and does not break in time. The
# 1444 "data/maps/CherrygroveCity/scripts.pory"
@ beasts push back against the drag for a moment, then turn to light as they
# 1445 "data/maps/CherrygroveCity/scripts.pory"
@ are pulled to (23,9) and (23,10), against Necrozma. Only the beasts are
# 1446 "data/maps/CherrygroveCity/scripts.pory"
@ removed. Necrozma stays, glows, and - in every branch - wavers again.
# 1447 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAbsorb::
# 1448 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1449 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1450 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1451 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiBreakLink, MSGBOX_DEFAULT
# 1452 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1453 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1454 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceLeft
# 1455 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, CherrygroveCity_Movement_UBPulledIn
# 1456 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, CherrygroveCity_Movement_UBPulledIn
# 1457 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1458 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBRiftPulse
# 1459 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1460 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1461 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1462 "data/maps/CherrygroveCity/scripts.pory"
	@ Their flag is FLAG_TEMP_2; everybody else has their own.
# 1463 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1464 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1465 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1466 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1467 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
# 1468 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, Common_Movement_ExclamationMark
# 1469 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, Common_Movement_ExclamationMark
# 1470 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, Common_Movement_ExclamationMark
# 1471 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1472 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1473 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1474 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1475 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1476 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1477 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1478 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBRiftPulse
# 1479 "data/maps/CherrygroveCity/scripts.pory"
	@ Anabel reads the instrument the team already has; Looker notes the
# 1480 "data/maps/CherrygroveCity/scripts.pory"
	@ bearing it shows and the line of the opening. Nobody claims a count
# 1481 "data/maps/CherrygroveCity/scripts.pory"
	@ bigger than these two, and nobody says where it will open next.
# 1482 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAbsorbedSignals, MSGBOX_DEFAULT
# 1483 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerRecording, MSGBOX_DEFAULT
# 1484 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1485 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBPartner
# 1486 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBRetreat
# 1487 "data/maps/CherrygroveCity/scripts.pory"

# 1488 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1489 "data/maps/CherrygroveCity/scripts.pory"
@ Optional partner (V2 section 12). CheckMysteryEggPokemon is sampled AFTER
# 1490 "data/maps/CherrygroveCity/scripts.pory"
@ the battle (it can evolve the Pokemon) and returns the first eligible one in
# 1491 "data/maps/CherrygroveCity/scripts.pory"
@ party order, so the species, the cry, the actor and {STR_VAR_1} all agree and
# 1492 "data/maps/CherrygroveCity/scripts.pory"
@ never change mid-scene. The Pokemon comes OUT of its Ball at (29,10), on the
# 1493 "data/maps/CherrygroveCity/scripts.pory"
@ player's sheltered side, before anything is said about it. Four templates
# 1494 "data/maps/CherrygroveCity/scripts.pory"
@ share FLAG_TEMP_A; at most one is ever added. Without the family the block
# 1495 "data/maps/CherrygroveCity/scripts.pory"
@ is one specialvar and a return: Looker already has the bearing.
# 1496 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1497 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBPartner::
# 1498 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 1499 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_4, VAR_RESULT
# 1500 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, CherrygroveCity_EventScript_UBReturn
# 1501 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
# 1502 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_BALL_OPEN
# 1503 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_A
# 1504 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBAddPartner
# 1505 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
# 1506 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1507 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1508 "data/maps/CherrygroveCity/scripts.pory"
	@ Necrozma turns its attention to it - and does NOT come across the
# 1509 "data/maps/CherrygroveCity/scripts.pory"
	@ sandbar: Incineroar still holds the shore.
# 1510 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_NECROZMA, CherrygroveCity_Movement_PulseInPlaceRight
# 1511 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_NECROZMA
# 1512 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, CherrygroveCity_EventScript_UBPartnerLegend
# 1513 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, CherrygroveCity_EventScript_UBPartnerLegend
# 1514 "data/maps/CherrygroveCity/scripts.pory"
	@ Cosmog / Cosmoem: kept beside the player. Cosmoem only floats, so its
# 1515 "data/maps/CherrygroveCity/scripts.pory"
	@ recoil is in place, like Cosmog's: the movement has to be true of the
# 1516 "data/maps/CherrygroveCity/scripts.pory"
	@ sprite on screen.
# 1517 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaSensesCosmog, MSGBOX_DEFAULT
# 1518 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1519 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_INCINEROAR, CherrygroveCity_Movement_AttackInPlaceLeft
# 1520 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1521 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1522 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1523 "data/maps/CherrygroveCity/scripts.pory"

# 1524 "data/maps/CherrygroveCity/scripts.pory"
@ Solgaleo / Lunala: out of the Ball first, facing west, then a cry and a
# 1525 "data/maps/CherrygroveCity/scripts.pory"
@ pulse. The edge of the opening steadies for a few moments - long enough for
# 1526 "data/maps/CherrygroveCity/scripts.pory"
@ Looker to CONFIRM the bearing he already took. It frees no one, holds no one
# 1527 "data/maps/CherrygroveCity/scripts.pory"
@ and fixes nothing: when the pulse ends the wavering comes back.
# 1528 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBPartnerLegend::
# 1529 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1530 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
# 1531 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBFlash
# 1532 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1533 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPartnerWindow, MSGBOX_DEFAULT
# 1534 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPartnerBearing, MSGBOX_DEFAULT
# 1535 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1536 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBRiftPulse
# 1537 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1538 "data/maps/CherrygroveCity/scripts.pory"

# 1539 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAddPartner::
# 1540 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, CherrygroveCity_EventScript_UBAddCosmoem
# 1541 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, CherrygroveCity_EventScript_UBAddSolgaleo
# 1542 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, CherrygroveCity_EventScript_UBAddLunala
# 1543 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_COSMOG
# 1544 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1545 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAddCosmoem::
# 1546 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_COSMOEM
# 1547 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1548 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAddSolgaleo::
# 1549 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_SOLGALEO
# 1550 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1551 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAddLunala::
# 1552 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_LUNALA
# 1553 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1554 "data/maps/CherrygroveCity/scripts.pory"

# 1555 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBReturn::
# 1556 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1557 "data/maps/CherrygroveCity/scripts.pory"

# 1558 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1559 "data/maps/CherrygroveCity/scripts.pory"
@ Retreat and safety (V2 section 13). Necrozma goes through the opening and
# 1560 "data/maps/CherrygroveCity/scripts.pory"
@ the edge closes AFTER it - two beats, not one flash for everything. Anabel
# 1561 "data/maps/CherrygroveCity/scripts.pory"
@ waits for the reading to drop before clearing the beach, and only then does
# 1562 "data/maps/CherrygroveCity/scripts.pory"
@ the town theme come back. Then the recalls, on screen and without a flash:
# 1563 "data/maps/CherrygroveCity/scripts.pory"
@ the player's partner first (its tile is Kukui's destination), Incineroar
# 1564 "data/maps/CherrygroveCity/scripts.pory"
@ once Kukui has checked the shore.
# 1565 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1566 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBRetreat::
# 1567 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBShake
# 1568 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 1569 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_NECROZMA
# 1570 "data/maps/CherrygroveCity/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 1571 "data/maps/CherrygroveCity/scripts.pory"
	delay 20
# 1572 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBRiftPulse
# 1573 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_RIFT
# 1574 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_WARP_OUT
# 1575 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1576 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNecrozmaGone, MSGBOX_DEFAULT
# 1577 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1578 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 1579 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBStreetClear, MSGBOX_DEFAULT
# 1580 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1581 "data/maps/CherrygroveCity/scripts.pory"
	fadedefaultbgm
# 1582 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_UBPartnerRecalled
# 1583 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_BALL_OPEN
# 1584 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_INCINEROAR
# 1585 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1586 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathCheck, MSGBOX_DEFAULT
# 1587 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathAnabel, MSGBOX_DEFAULT
# 1588 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1589 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAftermath
# 1590 "data/maps/CherrygroveCity/scripts.pory"

# 1591 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBPartnerRecalled::
# 1592 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, CherrygroveCity_EventScript_UBReturn
# 1593 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1594 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_BALL_OPEN
# 1595 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_COSMOG
# 1596 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_COSMOEM
# 1597 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_SOLGALEO
# 1598 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_LUNALA
# 1599 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 1600 "data/maps/CherrygroveCity/scripts.pory"
	return
# 1601 "data/maps/CherrygroveCity/scripts.pory"

# 1602 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1603 "data/maps/CherrygroveCity/scripts.pory"
@ The conversation (V2 sections 13-16). Formation, built orthogonally around
# 1604 "data/maps/CherrygroveCity/scripts.pory"
@ the player at (28,10):
# 1605 "data/maps/CherrygroveCity/scripts.pory"
@   Looker (27,9)->(28,9), faces south: NORTH of the player.
# 1606 "data/maps/CherrygroveCity/scripts.pory"
@   Kukui  (26,8)->(27,8)->(28,8)->(29,8)->(29,9)->(29,10), faces west: EAST.
# 1607 "data/maps/CherrygroveCity/scripts.pory"
@          Row 8 is empty (Looker and Anabel both left it), (29,9) and (29,10)
# 1608 "data/maps/CherrygroveCity/scripts.pory"
@          are free because the partner was recalled first.
# 1609 "data/maps/CherrygroveCity/scripts.pory"
@   Anabel stays at (27,10) and faces east: WEST of the player.
# 1610 "data/maps/CherrygroveCity/scripts.pory"
@ Nobody stands at (28,11), so the box covers nobody. The player turns to each
# 1611 "data/maps/CherrygroveCity/scripts.pory"
@ speaker: west for Anabel, north for Looker, east for Kukui.
# 1612 "data/maps/CherrygroveCity/scripts.pory"
@ ---------------------------------------------------------------------------
# 1613 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAftermath::
# 1614 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_LookerToPlayerSide
# 1615 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1616 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_KukuiToPlayer
# 1617 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 1618 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_ANABEL, DIR_EAST
# 1619 "data/maps/CherrygroveCity/scripts.pory"
	@ Anabel's explanation, after the danger and in her own words. Looker
# 1620 "data/maps/CherrygroveCity/scripts.pory"
	@ looks at her and does not interrupt; Kukui just listens.
# 1621 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1622 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelFallerIntro, MSGBOX_DEFAULT
# 1623 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelFaller, MSGBOX_DEFAULT
# 1624 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1625 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_LOOKER, DIR_WEST
# 1626 "data/maps/CherrygroveCity/scripts.pory"
	delay 30
# 1627 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelFallerLimit, MSGBOX_DEFAULT
# 1628 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1629 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1630 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerSupport, MSGBOX_DEFAULT
# 1631 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1632 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1633 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelSupport, MSGBOX_DEFAULT
# 1634 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1635 "data/maps/CherrygroveCity/scripts.pory"
	@ The player's acknowledgement is a gesture, not a line.
# 1636 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerNods
# 1637 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 1638 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_LOOKER, DIR_SOUTH
# 1639 "data/maps/CherrygroveCity/scripts.pory"
	@ What Kukui and the records add.
# 1640 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1641 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiThanks, MSGBOX_DEFAULT
# 1642 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1643 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1644 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathPlan, MSGBOX_DEFAULT
# 1645 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1646 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1647 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathBearing, MSGBOX_DEFAULT
# 1648 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1649 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1650 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathLimit, MSGBOX_DEFAULT
# 1651 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1652 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1653 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiElm, MSGBOX_DEFAULT
# 1654 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1655 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1656 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerElm, MSGBOX_DEFAULT
# 1657 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1658 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1659 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiLogs, MSGBOX_DEFAULT
# 1660 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1661 "data/maps/CherrygroveCity/scripts.pory"
	@ Optional, only if the partner came out. It is back in its Ball now, and
# 1662 "data/maps/CherrygroveCity/scripts.pory"
	@ nobody describes it acting outside it.
# 1663 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, CherrygroveCity_EventScript_UBHook
# 1664 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, CherrygroveCity_EventScript_UBAftermathLegend
# 1665 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, CherrygroveCity_EventScript_UBAftermathLegend
# 1666 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathCosmog, MSGBOX_DEFAULT
# 1667 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1668 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBHook
# 1669 "data/maps/CherrygroveCity/scripts.pory"

# 1670 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAftermathLegend::
# 1671 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 1672 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAftermathLegend, MSGBOX_DEFAULT
# 1673 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1674 "data/maps/CherrygroveCity/scripts.pory"

# 1675 "data/maps/CherrygroveCity/scripts.pory"
@ The hook names NO place: the NEXT summons does (Looker's call). Kukui's last
# 1676 "data/maps/CherrygroveCity/scripts.pory"
@ box is one half of a pair with Mission 4 - he asks Elm for his readings,
# 1677 "data/maps/CherrygroveCity/scripts.pory"
@ and Elm's answer is what opens New Bark. Kukui does NOT know about six weeks
# 1678 "data/maps/CherrygroveCity/scripts.pory"
@ of "broken sensor"; that discovery is Elm's, in the interval.
# 1679 "data/maps/CherrygroveCity/scripts.pory"
@ Pair: CherrygroveCity_Text_UBKukuiElm/UBHookKukui <->
# 1680 "data/maps/CherrygroveCity/scripts.pory"
@ RiftMissions_Text_LookerCallM4 and OlivineCity_House1_Text_BriefingM4Evidence.
# 1681 "data/maps/CherrygroveCity/scripts.pory"
@ Never edit one side alone.
# 1682 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBHook::
# 1683 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 1684 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBHookLooker, MSGBOX_DEFAULT
# 1685 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1686 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 1687 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBHookKukui, MSGBOX_DEFAULT
# 1688 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1689 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBFinish::
# 1690 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1691 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE   @ invariant: flag and var together
# 1692 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_CHERRYGROVE_UB_PREPARED
# 1693 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_CHERRYGROVE_UB_ENGAGED
# 1694 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 8
# 1695 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_DAILY_LOOKER_CALL            @ he just said it in person
# 1696 "data/maps/CherrygroveCity/scripts.pory"
	@ Reload in place under the fade. With the flag cleared the fourteen
# 1697 "data/maps/CherrygroveCity/scripts.pory"
	@ residents - and the trader's gift Pokemon, whose visibility is recomputed
# 1698 "data/maps/CherrygroveCity/scripts.pory"
	@ from their own FLAG_PICKED_* - come back in one go, the cast is hidden,
# 1699 "data/maps/CherrygroveCity/scripts.pory"
	@ the doors unlock with the flag, and the warp undoes the hidefollower.
# 1700 "data/maps/CherrygroveCity/scripts.pory"
	@ Nobody is re-added just because the incident flag was cleared: each
# 1701 "data/maps/CherrygroveCity/scripts.pory"
	@ object answers to its own flag.
# 1702 "data/maps/CherrygroveCity/scripts.pory"
	warpsilent MAP_CHERRYGROVE_CITY, 28, 10
# 1703 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1704 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 1705 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1706 "data/maps/CherrygroveCity/scripts.pory"

# 1707 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_StepDownFaceLeft:
# 1708 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1709 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1710 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1711 "data/maps/CherrygroveCity/scripts.pory"

# 1712 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerToLine:
# 1713 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1714 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1715 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1716 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1717 "data/maps/CherrygroveCity/scripts.pory"

# 1718 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelToLine:
# 1719 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1720 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1721 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1722 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1723 "data/maps/CherrygroveCity/scripts.pory"

# 1724 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PulseInPlaceRight:
# 1725 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1726 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1727 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1728 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1729 "data/maps/CherrygroveCity/scripts.pory"

# 1730 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AttackInPlaceLeft:
# 1731 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_left
# 1732 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_left
# 1733 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1734 "data/maps/CherrygroveCity/scripts.pory"

# 1735 "data/maps/CherrygroveCity/scripts.pory"
@ (24,10)->(25,10), across the sandbar. Slow on purpose: it has to still be
# 1736 "data/maps/CherrygroveCity/scripts.pory"
@ moving when the white drops.
# 1737 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_StakatakaWades:
# 1738 "data/maps/CherrygroveCity/scripts.pory"
	walk_slow_right
# 1739 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1740 "data/maps/CherrygroveCity/scripts.pory"

# 1741 "data/maps/CherrygroveCity/scripts.pory"
@ (26,9)->(26,10), then faces the water.
# 1742 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_IncineroarBlocks:
# 1743 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_down
# 1744 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1745 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1746 "data/maps/CherrygroveCity/scripts.pory"

# 1747 "data/maps/CherrygroveCity/scripts.pory"
@ (26,10)->(26,9) when the player takes Stakataka.
# 1748 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_IncineroarToNorth:
# 1749 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 1750 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1751 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1752 "data/maps/CherrygroveCity/scripts.pory"

# 1753 "data/maps/CherrygroveCity/scripts.pory"
@ (25,10)->(24,10): one tile back, still facing east. Not thrown across the bay.
# 1754 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_UBKnockedBack:
# 1755 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 1756 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 1757 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 1758 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1759 "data/maps/CherrygroveCity/scripts.pory"

# 1760 "data/maps/CherrygroveCity/scripts.pory"
@ Taken, not going: a push against the pull, then dragged one tile west.
# 1761 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_UBPulledIn:
# 1762 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 1763 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_right
# 1764 "data/maps/CherrygroveCity/scripts.pory"
	walk_slow_left
# 1765 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 1766 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1767 "data/maps/CherrygroveCity/scripts.pory"

# 1768 "data/maps/CherrygroveCity/scripts.pory"
@ (28,9)->(27,9), then faces the player below her.
# 1769 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelStepWest:
# 1770 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 1771 "data/maps/CherrygroveCity/scripts.pory"
	face_down
# 1772 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1773 "data/maps/CherrygroveCity/scripts.pory"

# 1774 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerPulledAside:
# 1775 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 1776 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 1777 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 1778 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1779 "data/maps/CherrygroveCity/scripts.pory"

# 1780 "data/maps/CherrygroveCity/scripts.pory"
@ (27,9)->(27,10) once the distortion is over.
# 1781 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelTakesTheFront:
# 1782 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1783 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1784 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1785 "data/maps/CherrygroveCity/scripts.pory"

# 1786 "data/maps/CherrygroveCity/scripts.pory"
@ (27,8)->(27,9), looking down at her.
# 1787 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_LookerToAnabel:
# 1788 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_down
# 1789 "data/maps/CherrygroveCity/scripts.pory"
	face_down
# 1790 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1791 "data/maps/CherrygroveCity/scripts.pory"

# 1792 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelThrows:
# 1793 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_left
# 1794 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_fast_left
# 1795 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1796 "data/maps/CherrygroveCity/scripts.pory"

# 1797 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_LookerToPlayerSide:
# 1798 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1799 "data/maps/CherrygroveCity/scripts.pory"
	face_down
# 1800 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1801 "data/maps/CherrygroveCity/scripts.pory"

# 1802 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_KukuiToPlayer:
# 1803 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1804 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1805 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1806 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1807 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1808 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1809 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1810 "data/maps/CherrygroveCity/scripts.pory"

# 1811 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerNods:
# 1812 "data/maps/CherrygroveCity/scripts.pory"
	walk_in_place_slow_left
# 1813 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1814 "data/maps/CherrygroveCity/scripts.pory"

# 1815 "data/maps/CherrygroveCity/scripts.pory"
@ Retry form-up (see UBSceneRetry).
# 1816 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerRetryToLine:
# 1817 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 1818 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1819 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1820 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1821 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1822 "data/maps/CherrygroveCity/scripts.pory"

# 1823 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelRetryToFront:
# 1824 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1825 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 1826 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1827 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1828 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1829 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1830 "data/maps/CherrygroveCity/scripts.pory"

# 1831 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_LookerRetryToLine:
# 1832 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1833 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1834 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1835 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1836 "data/maps/CherrygroveCity/scripts.pory"

# 1837 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 1838 "data/maps/CherrygroveCity/scripts.pory"
@ Texts. Final lines of the V2 script, one speaker per message and the plaque
# 1839 "data/maps/CherrygroveCity/scripts.pory"
@ opening every one of them. Narration and the door note have NO plaque: a
# 1840 "data/maps/CherrygroveCity/scripts.pory"
@ message without {SPEAKER} gets none and never inherits the previous one.
# 1841 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 1842 "data/maps/CherrygroveCity/scripts.pory"

# 1843 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_DoorLocked:
# 1844 "data/maps/CherrygroveCity/scripts.pory"
	.string "Residents are sheltered at\n"
# 1845 "data/maps/CherrygroveCity/scripts.pory"
	.string "Violet Gym.\p"
# 1846 "data/maps/CherrygroveCity/scripts.pory"
	.string "Please keep away from the\n"
# 1847 "data/maps/CherrygroveCity/scripts.pory"
	.string "northwest shore.\p"
# 1848 "data/maps/CherrygroveCity/scripts.pory"
	.string "- International Police$"
# 1849 "data/maps/CherrygroveCity/scripts.pory"

# 1850 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelIdle:
# 1851 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The route back to town is\n"
# 1852 "data/maps/CherrygroveCity/scripts.pory"
	.string "clear. Use the Center if you\l"
# 1853 "data/maps/CherrygroveCity/scripts.pory"
	.string "need it.\p"
# 1854 "data/maps/CherrygroveCity/scripts.pory"
	.string "Speak with Looker when you're\n"
# 1855 "data/maps/CherrygroveCity/scripts.pory"
	.string "ready.$"
# 1856 "data/maps/CherrygroveCity/scripts.pory"

# 1857 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiIdle:
# 1858 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Hey, cousin. Kukui.\n"
# 1859 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker said you'd be joining us.\p"
# 1860 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'd rather study these two\n"
# 1861 "data/maps/CherrygroveCity/scripts.pory"
	.string "somewhere they can't flatten a\l"
# 1862 "data/maps/CherrygroveCity/scripts.pory"
	.string "town.$"
# 1863 "data/maps/CherrygroveCity/scripts.pory"

# 1864 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerGreet:
# 1865 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Watch your footing,\n"
# 1866 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}. The sand is firmer on\l"
# 1867 "data/maps/CherrygroveCity/scripts.pory"
	.string "this side.\p"
# 1868 "data/maps/CherrygroveCity/scripts.pory"
	.string "Professor, show us what you\n"
# 1869 "data/maps/CherrygroveCity/scripts.pory"
	.string "noticed.$"
# 1870 "data/maps/CherrygroveCity/scripts.pory"

# 1871 "data/maps/CherrygroveCity/scripts.pory"
@ The tracks are from the earlier openings (V2 section 6 allows it when there
# 1872 "data/maps/CherrygroveCity/scripts.pory"
@ is no persistent decal): the sandbar he points at is on screen, the trail
# 1873 "data/maps/CherrygroveCity/scripts.pory"
@ itself is shown live in the demonstration that follows.
# 1874 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiObservation:
# 1875 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Blacephalon flashes first.\n"
# 1876 "data/maps/CherrygroveCity/scripts.pory"
	.string "When I can see again,\l"
# 1877 "data/maps/CherrygroveCity/scripts.pory"
	.string "Stakataka's closer.\p"
# 1878 "data/maps/CherrygroveCity/scripts.pory"
	.string "But see that sandbar? Every\n"
# 1879 "data/maps/CherrygroveCity/scripts.pory"
	.string "time, there's a fresh trail\l"
# 1880 "data/maps/CherrygroveCity/scripts.pory"
	.string "through the shallows.$"
# 1881 "data/maps/CherrygroveCity/scripts.pory"

# 1882 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelObservation:
# 1883 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}So it moves while the\n"
# 1884 "data/maps/CherrygroveCity/scripts.pory"
	.string "flash hides it.$"
# 1885 "data/maps/CherrygroveCity/scripts.pory"

# 1886 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiPlan:
# 1887 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}That's what I think.\p"
# 1888 "data/maps/CherrygroveCity/scripts.pory"
	.string "We need to keep the flashes\n"
# 1889 "data/maps/CherrygroveCity/scripts.pory"
	.string "away from the other fight.\p"
# 1890 "data/maps/CherrygroveCity/scripts.pory"
	.string "You take one. I'll take the\n"
# 1891 "data/maps/CherrygroveCity/scripts.pory"
	.string "other.$"
# 1892 "data/maps/CherrygroveCity/scripts.pory"

# 1893 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBReady:
# 1894 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Are you and your Pokémon\n"
# 1895 "data/maps/CherrygroveCity/scripts.pory"
	.string "ready?$"
# 1896 "data/maps/CherrygroveCity/scripts.pory"

# 1897 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNotReady:
# 1898 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The Center is open.\n"
# 1899 "data/maps/CherrygroveCity/scripts.pory"
	.string "We'll keep the approach clear.$"
# 1900 "data/maps/CherrygroveCity/scripts.pory"

# 1901 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiPrepare:
# 1902 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Incineroar, with me.\n"
# 1903 "data/maps/CherrygroveCity/scripts.pory"
	.string "Keep the way back open.$"
# 1904 "data/maps/CherrygroveCity/scripts.pory"

# 1905 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelSenses:
# 1906 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Wait. An opening, close by.\n"
# 1907 "data/maps/CherrygroveCity/scripts.pory"
	.string "Step back from the water.$"
# 1908 "data/maps/CherrygroveCity/scripts.pory"

# 1909 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerMeter:
# 1910 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The meter hasn't changed\n"
# 1911 "data/maps/CherrygroveCity/scripts.pory"
	.string "yet.$"
# 1912 "data/maps/CherrygroveCity/scripts.pory"

# 1913 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelCertain:
# 1914 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I know. Give it room.$"
# 1915 "data/maps/CherrygroveCity/scripts.pory"

# 1916 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiWater:
# 1917 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}The water's going still.\n"
# 1918 "data/maps/CherrygroveCity/scripts.pory"
	.string "Incineroar, hold there.$"
# 1919 "data/maps/CherrygroveCity/scripts.pory"

# 1920 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaArrives:
# 1921 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Necrozma.\n"
# 1922 "data/maps/CherrygroveCity/scripts.pory"
	.string "Watch its arms and the light\l"
# 1923 "data/maps/CherrygroveCity/scripts.pory"
	.string "around them.$"
# 1924 "data/maps/CherrygroveCity/scripts.pory"

# 1925 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAppear:
# 1926 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Blacephalon and Stakataka.\n"
# 1927 "data/maps/CherrygroveCity/scripts.pory"
	.string "Those are the two.$"
# 1928 "data/maps/CherrygroveCity/scripts.pory"

# 1929 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBFlashWarning:
# 1930 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Here comes the flash!\n"
# 1931 "data/maps/CherrygroveCity/scripts.pory"
	.string "Turn your eyes away from its\l"
# 1932 "data/maps/CherrygroveCity/scripts.pory"
	.string "head!$"
# 1933 "data/maps/CherrygroveCity/scripts.pory"

# 1934 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBMovementConfirmed:
# 1935 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}There! It's moving through\n"
# 1936 "data/maps/CherrygroveCity/scripts.pory"
	.string "the shallows.\p"
# 1937 "data/maps/CherrygroveCity/scripts.pory"
	.string "The flash hides its steps.$"
# 1938 "data/maps/CherrygroveCity/scripts.pory"

# 1939 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiIntercept:
# 1940 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Incineroar, block the path!$"
# 1941 "data/maps/CherrygroveCity/scripts.pory"

# 1942 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiHold:
# 1943 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Good! Keep it in the water.\n"
# 1944 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't give it room to step\l"
# 1945 "data/maps/CherrygroveCity/scripts.pory"
	.string "forward.$"
# 1946 "data/maps/CherrygroveCity/scripts.pory"

# 1947 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelMove:
# 1948 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{PLAYER}, move right! Now!$"
# 1949 "data/maps/CherrygroveCity/scripts.pory"

# 1950 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerChecks:
# 1951 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Anabel! Are you hurt?$"
# 1952 "data/maps/CherrygroveCity/scripts.pory"

# 1953 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelReady:
# 1954 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'm all right.\n"
# 1955 "data/maps/CherrygroveCity/scripts.pory"
	.string "Keep the way back clear.$"
# 1956 "data/maps/CherrygroveCity/scripts.pory"

# 1957 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBChoosePrompt:
# 1958 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Which one will you take,\n"
# 1959 "data/maps/CherrygroveCity/scripts.pory"
	.string "{PLAYER}? Incineroar and I will\l"
# 1960 "data/maps/CherrygroveCity/scripts.pory"
	.string "handle the other.$"
# 1961 "data/maps/CherrygroveCity/scripts.pory"

# 1962 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_ChoiceBlacephalon:
# 1963 "data/maps/CherrygroveCity/scripts.pory"
	.string "Blacephalon$"
# 1964 "data/maps/CherrygroveCity/scripts.pory"

# 1965 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_ChoiceStakataka:
# 1966 "data/maps/CherrygroveCity/scripts.pory"
	.string "Stakataka$"
# 1967 "data/maps/CherrygroveCity/scripts.pory"

# 1968 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPickedBlacephalon:
# 1969 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Keep Blacephalon facing\n"
# 1970 "data/maps/CherrygroveCity/scripts.pory"
	.string "your side.\p"
# 1971 "data/maps/CherrygroveCity/scripts.pory"
	.string "We'll hold Stakataka here.$"
# 1972 "data/maps/CherrygroveCity/scripts.pory"

# 1973 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPickedStakataka:
# 1974 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}We'll draw Blacephalon this\n"
# 1975 "data/maps/CherrygroveCity/scripts.pory"
	.string "way. Keep Stakataka off the\l"
# 1976 "data/maps/CherrygroveCity/scripts.pory"
	.string "shore!$"
# 1977 "data/maps/CherrygroveCity/scripts.pory"

# 1978 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelWatch:
# 1979 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'll watch Necrozma.\n"
# 1980 "data/maps/CherrygroveCity/scripts.pory"
	.string "Leave the capture to me.$"
# 1981 "data/maps/CherrygroveCity/scripts.pory"

# 1982 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBUnresolved:
# 1983 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The shore isn't clear yet.\n"
# 1984 "data/maps/CherrygroveCity/scripts.pory"
	.string "Regroup before we move in\l"
# 1985 "data/maps/CherrygroveCity/scripts.pory"
	.string "again.$"
# 1986 "data/maps/CherrygroveCity/scripts.pory"

# 1987 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiFoughtStakataka:
# 1988 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Stakataka's stopped.\n"
# 1989 "data/maps/CherrygroveCity/scripts.pory"
	.string "Stay on it, Incineroar.$"
# 1990 "data/maps/CherrygroveCity/scripts.pory"

# 1991 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiFoughtBlacephalon:
# 1992 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}No more flashes.\n"
# 1993 "data/maps/CherrygroveCity/scripts.pory"
	.string "Good work, Incineroar.$"
# 1994 "data/maps/CherrygroveCity/scripts.pory"

# 1995 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelWindow:
# 1996 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}That pulse… it's starting.\n"
# 1997 "data/maps/CherrygroveCity/scripts.pory"
	.string "Keep them still!$"
# 1998 "data/maps/CherrygroveCity/scripts.pory"

# 1999 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBContainmentFailed:
# 2000 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I reached it in time.\n"
# 2001 "data/maps/CherrygroveCity/scripts.pory"
	.string "The connection still pulled it\l"
# 2002 "data/maps/CherrygroveCity/scripts.pory"
	.string "back!$"
# 2003 "data/maps/CherrygroveCity/scripts.pory"

# 2004 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiBreakLink:
# 2005 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Incineroar, hit the light\n"
# 2006 "data/maps/CherrygroveCity/scripts.pory"
	.string "between them!$"
# 2007 "data/maps/CherrygroveCity/scripts.pory"

# 2008 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAbsorbedSignals:
# 2009 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Their signals are still\n"
# 2010 "data/maps/CherrygroveCity/scripts.pory"
	.string "there. Keep recording, Looker.$"
# 2011 "data/maps/CherrygroveCity/scripts.pory"

# 2012 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerRecording:
# 2013 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Recording. I have the\n"
# 2014 "data/maps/CherrygroveCity/scripts.pory"
	.string "direction too.$"
# 2015 "data/maps/CherrygroveCity/scripts.pory"

# 2016 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaSensesCosmog:
# 2017 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Keep {STR_VAR_1} beside you,\n"
# 2018 "data/maps/CherrygroveCity/scripts.pory"
	.string "cousin. Incineroar, hold the\l"
# 2019 "data/maps/CherrygroveCity/scripts.pory"
	.string "shore.$"
# 2020 "data/maps/CherrygroveCity/scripts.pory"

# 2021 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPartnerWindow:
# 2022 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The opening's steady.\n"
# 2023 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker, check the bearing now.$"
# 2024 "data/maps/CherrygroveCity/scripts.pory"

# 2025 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPartnerBearing:
# 2026 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}It matches. I've marked it.$"
# 2027 "data/maps/CherrygroveCity/scripts.pory"

# 2028 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNecrozmaGone:
# 2029 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The opening has closed.\n"
# 2030 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hold here a moment.$"
# 2031 "data/maps/CherrygroveCity/scripts.pory"

# 2032 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBStreetClear:
# 2033 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It's clear.$"
# 2034 "data/maps/CherrygroveCity/scripts.pory"

# 2035 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathCheck:
# 2036 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Everyone all right?\n"
# 2037 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel, take a moment.$"
# 2038 "data/maps/CherrygroveCity/scripts.pory"

# 2039 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathAnabel:
# 2040 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Thank you. I will.$"
# 2041 "data/maps/CherrygroveCity/scripts.pory"

# 2042 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelFallerIntro:
# 2043 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{PLAYER}, about what\n"
# 2044 "data/maps/CherrygroveCity/scripts.pory"
	.string "happened…\p"
# 2045 "data/maps/CherrygroveCity/scripts.pory"
	.string "I felt that opening before I\n"
# 2046 "data/maps/CherrygroveCity/scripts.pory"
	.string "saw it.$"
# 2047 "data/maps/CherrygroveCity/scripts.pory"

# 2048 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelFaller:
# 2049 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I once came through an Ultra\n"
# 2050 "data/maps/CherrygroveCity/scripts.pory"
	.string "Wormhole. That's what they call\l"
# 2051 "data/maps/CherrygroveCity/scripts.pory"
	.string "a Faller.\p"
# 2052 "data/maps/CherrygroveCity/scripts.pory"
	.string "I don't remember much from\n"
# 2053 "data/maps/CherrygroveCity/scripts.pory"
	.string "before.$"
# 2054 "data/maps/CherrygroveCity/scripts.pory"

# 2055 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelFallerLimit:
# 2056 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Sometimes I feel an opening\n"
# 2057 "data/maps/CherrygroveCity/scripts.pory"
	.string "nearby. Only a moment before it\l"
# 2058 "data/maps/CherrygroveCity/scripts.pory"
	.string "happens.\p"
# 2059 "data/maps/CherrygroveCity/scripts.pory"
	.string "I can't tell where the next one\n"
# 2060 "data/maps/CherrygroveCity/scripts.pory"
	.string "will be.$"
# 2061 "data/maps/CherrygroveCity/scripts.pory"

# 2062 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerSupport:
# 2063 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then we won't leave you\n"
# 2064 "data/maps/CherrygroveCity/scripts.pory"
	.string "watching it alone.$"
# 2065 "data/maps/CherrygroveCity/scripts.pory"

# 2066 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelSupport:
# 2067 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Agreed.$"
# 2068 "data/maps/CherrygroveCity/scripts.pory"

# 2069 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiThanks:
# 2070 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}You kept your side covered,\n"
# 2071 "data/maps/CherrygroveCity/scripts.pory"
	.string "cousin. That gave Incineroar\l"
# 2072 "data/maps/CherrygroveCity/scripts.pory"
	.string "room to work.\p"
# 2073 "data/maps/CherrygroveCity/scripts.pory"
	.string "Next time we team up, let's\n"
# 2074 "data/maps/CherrygroveCity/scripts.pory"
	.string "leave the town out of it.$"
# 2075 "data/maps/CherrygroveCity/scripts.pory"

# 2076 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathPlan:
# 2077 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We acted before the pull\n"
# 2078 "data/maps/CherrygroveCity/scripts.pory"
	.string "this time. It wasn't enough\l"
# 2079 "data/maps/CherrygroveCity/scripts.pory"
	.string "while they were connected.\p"
# 2080 "data/maps/CherrygroveCity/scripts.pory"
	.string "We need to stop the connection\n"
# 2081 "data/maps/CherrygroveCity/scripts.pory"
	.string "before we try to capture them.$"
# 2082 "data/maps/CherrygroveCity/scripts.pory"

# 2083 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathBearing:
# 2084 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We have a direction for the\n"
# 2085 "data/maps/CherrygroveCity/scripts.pory"
	.string "opening. Can we trace it?$"
# 2086 "data/maps/CherrygroveCity/scripts.pory"

# 2087 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathLimit:
# 2088 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Not from this reading alone.\n"
# 2089 "data/maps/CherrygroveCity/scripts.pory"
	.string "We need another point of\l"
# 2090 "data/maps/CherrygroveCity/scripts.pory"
	.string "comparison.$"
# 2091 "data/maps/CherrygroveCity/scripts.pory"

# 2092 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiElm:
# 2093 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}I'll ask Professor Elm for\n"
# 2094 "data/maps/CherrygroveCity/scripts.pory"
	.string "his readings. His lab is close\l"
# 2095 "data/maps/CherrygroveCity/scripts.pory"
	.string "to this coast.\p"
# 2096 "data/maps/CherrygroveCity/scripts.pory"
	.string "We can compare the times and\n"
# 2097 "data/maps/CherrygroveCity/scripts.pory"
	.string "see whether he's picked up the\l"
# 2098 "data/maps/CherrygroveCity/scripts.pory"
	.string "same pulses.$"
# 2099 "data/maps/CherrygroveCity/scripts.pory"

# 2100 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerElm:
# 2101 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Send them to Olivine.\n"
# 2102 "data/maps/CherrygroveCity/scripts.pory"
	.string "Even the readings he couldn't\l"
# 2103 "data/maps/CherrygroveCity/scripts.pory"
	.string "explain.$"
# 2104 "data/maps/CherrygroveCity/scripts.pory"

# 2105 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiLogs:
# 2106 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}You got it.\n"
# 2107 "data/maps/CherrygroveCity/scripts.pory"
	.string "A strange result's still a\l"
# 2108 "data/maps/CherrygroveCity/scripts.pory"
	.string "result.$"
# 2109 "data/maps/CherrygroveCity/scripts.pory"

# 2110 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathCosmog:
# 2111 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}How's {STR_VAR_1} doing?\n"
# 2112 "data/maps/CherrygroveCity/scripts.pory"
	.string "Give it a quiet place to rest.$"
# 2113 "data/maps/CherrygroveCity/scripts.pory"

# 2114 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAftermathLegend:
# 2115 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{STR_VAR_1} gave us time to\n"
# 2116 "data/maps/CherrygroveCity/scripts.pory"
	.string "check the bearing.\p"
# 2117 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll include that in the\n"
# 2118 "data/maps/CherrygroveCity/scripts.pory"
	.string "report.$"
# 2119 "data/maps/CherrygroveCity/scripts.pory"

# 2120 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBHookLooker:
# 2121 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We'll compare the records in\n"
# 2122 "data/maps/CherrygroveCity/scripts.pory"
	.string "Olivine. I'll call when we have\l"
# 2123 "data/maps/CherrygroveCity/scripts.pory"
	.string "a lead.\p"
# 2124 "data/maps/CherrygroveCity/scripts.pory"
	.string "For now, leave this beach to\n"
# 2125 "data/maps/CherrygroveCity/scripts.pory"
	.string "the waves.$"
# 2126 "data/maps/CherrygroveCity/scripts.pory"

# 2127 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBHookKukui:
# 2128 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}I'll contact Elm before I\n"
# 2129 "data/maps/CherrygroveCity/scripts.pory"
	.string "leave Johto. Take care, cousin.$"
# 2130 "data/maps/CherrygroveCity/scripts.pory"

# 2131 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBRetryLooker:
# 2132 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The approach is still clear.\n"
# 2133 "data/maps/CherrygroveCity/scripts.pory"
	.string "How are your Pokémon?$"
# 2134 "data/maps/CherrygroveCity/scripts.pory"

# 2135 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBRetryKukui:
# 2136 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}We've kept them off the\n"
# 2137 "data/maps/CherrygroveCity/scripts.pory"
	.string "shore. Ready to take one\l"
# 2138 "data/maps/CherrygroveCity/scripts.pory"
	.string "again?$"
# 2139 "data/maps/CherrygroveCity/scripts.pory"

# 2140 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBRetryNotReady:
# 2141 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Get your team ready.\n"
# 2142 "data/maps/CherrygroveCity/scripts.pory"
	.string "Incineroar and I will hold\l"
# 2143 "data/maps/CherrygroveCity/scripts.pory"
	.string "here.$"
# 2144 "data/maps/CherrygroveCity/scripts.pory"

# 2145 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 2146 "data/maps/CherrygroveCity/scripts.pory"
@ Post-game beach (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.7).
# 2147 "data/maps/CherrygroveCity/scripts.pory"
@ Two separate rotas: Kukui on Mon/Tue/Thu/Sat, Lillie on Tue/Thu/Sat. Kukui is
# 2148 "data/maps/CherrygroveCity/scripts.pory"
@ here on Monday on his own, which is the point - he is the one who cannot leave
# 2149 "data/maps/CherrygroveCity/scripts.pory"
@ the readings alone.
# 2150 "data/maps/CherrygroveCity/scripts.pory"
@ Both windows are closed below state 16, so nothing of this exists until the
# 2151 "data/maps/CherrygroveCity/scripts.pory"
@ farewell at the altar has played.
# 2152 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 2153 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyPostKukui::
# 2154 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CherrygroveCity_EventScript_HidePostKukui
# 2155 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetDayOfWeek
# 2156 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_MON, CherrygroveCity_EventScript_ShowPostKukui
# 2157 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CherrygroveCity_EventScript_ShowPostKukui
# 2158 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_THU, CherrygroveCity_EventScript_ShowPostKukui
# 2159 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CherrygroveCity_EventScript_ShowPostKukui
# 2160 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HidePostKukui::
# 2161 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_7
# 2162 "data/maps/CherrygroveCity/scripts.pory"
	return
# 2163 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ShowPostKukui::
# 2164 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_7
# 2165 "data/maps/CherrygroveCity/scripts.pory"
	return
# 2166 "data/maps/CherrygroveCity/scripts.pory"

# 2167 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyPostLillie::
# 2168 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CherrygroveCity_EventScript_HidePostLillie
# 2169 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetDayOfWeek
# 2170 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CherrygroveCity_EventScript_ShowPostLillie
# 2171 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_THU, CherrygroveCity_EventScript_ShowPostLillie
# 2172 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CherrygroveCity_EventScript_ShowPostLillie
# 2173 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HidePostLillie::
# 2174 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_8
# 2175 "data/maps/CherrygroveCity/scripts.pory"
	return
# 2176 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ShowPostLillie::
# 2177 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_8
# 2178 "data/maps/CherrygroveCity/scripts.pory"
	return
# 2179 "data/maps/CherrygroveCity/scripts.pory"

# 2180 "data/maps/CherrygroveCity/scripts.pory"
@ One box of character, then the rematch if today's daily flag is still clear.
# 2181 "data/maps/CherrygroveCity/scripts.pory"
@ A normal trainer battle: no B_FLAG_NO_WHITEOUT, because losing to a post-game
# 2182 "data/maps/CherrygroveCity/scripts.pory"
@ trainer is a normal blackout. The narrative duel of this arc was Act II at the
# 2183 "data/maps/CherrygroveCity/scripts.pory"
@ altar and it is over.
# 2184 "data/maps/CherrygroveCity/scripts.pory"
@ The daily flag is set BEFORE the battle: after is unreachable on a loss,
# 2185 "data/maps/CherrygroveCity/scripts.pory"
@ because the blackout never comes back here. Losing spends the day, which is
# 2186 "data/maps/CherrygroveCity/scripts.pory"
@ the right behaviour for a rematch.
# 2187 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostKukui::
# 2188 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 2189 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 2190 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukui, MSGBOX_DEFAULT
# 2191 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 2192 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_DAILY_REMATCH_KUKUI, CherrygroveCity_EventScript_PostKukuiDone
# 2193 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiRematchAsk, MSGBOX_YESNO
# 2194 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_PostKukuiNo
# 2195 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_DAILY_REMATCH_KUKUI
# 2196 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_KUKUI, CherrygroveCity_Text_BeachKukuiBeaten
# 2197 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiAfter, MSGBOX_DEFAULT
# 2198 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2199 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2200 "data/maps/CherrygroveCity/scripts.pory"

# 2201 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostKukuiNo::
# 2202 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiRematchNo, MSGBOX_DEFAULT
# 2203 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2204 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2205 "data/maps/CherrygroveCity/scripts.pory"

# 2206 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostKukuiDone::
# 2207 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachKukuiDoneToday, MSGBOX_DEFAULT
# 2208 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2209 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2210 "data/maps/CherrygroveCity/scripts.pory"

# 2211 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostLillie::
# 2212 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 2213 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 2214 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillie, MSGBOX_DEFAULT
# 2215 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 2216 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_DAILY_REMATCH_LILLIE, CherrygroveCity_EventScript_PostLillieDone
# 2217 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieRematchAsk, MSGBOX_YESNO
# 2218 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_PostLillieNo
# 2219 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_DAILY_REMATCH_LILLIE
# 2220 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_LILLIE_POSTGAME, CherrygroveCity_Text_BeachLillieBeaten
# 2221 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieAfter, MSGBOX_DEFAULT
# 2222 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2223 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2224 "data/maps/CherrygroveCity/scripts.pory"

# 2225 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostLillieNo::
# 2226 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieRematchNo, MSGBOX_DEFAULT
# 2227 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2228 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2229 "data/maps/CherrygroveCity/scripts.pory"

# 2230 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_PostLillieDone::
# 2231 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_BeachLillieDoneToday, MSGBOX_DEFAULT
# 2232 "data/maps/CherrygroveCity/scripts.pory"
	release
# 2233 "data/maps/CherrygroveCity/scripts.pory"
	end
# 2234 "data/maps/CherrygroveCity/scripts.pory"

# 2235 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukui:
# 2236 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}{PLAYER}! Hey! Look who the boat\n"
# 2237 "data/maps/CherrygroveCity/scripts.pory"
	.string "brought!\p"
# 2238 "data/maps/CherrygroveCity/scripts.pory"
	.string "I flew back to Alola, I walked into my\n"
# 2239 "data/maps/CherrygroveCity/scripts.pory"
	.string "own lab, I looked at my own desk for\l"
# 2240 "data/maps/CherrygroveCity/scripts.pory"
	.string "about four minutes, and then I got back\l"
# 2241 "data/maps/CherrygroveCity/scripts.pory"
	.string "on a boat. Burnet says hello and also\l"
# 2242 "data/maps/CherrygroveCity/scripts.pory"
	.string "that she is not surprised.\p"
# 2243 "data/maps/CherrygroveCity/scripts.pory"
	.string "This beach, {PLAYER}. Something\n"
# 2244 "data/maps/CherrygroveCity/scripts.pory"
	.string "happened on this beach and the sand\l"
# 2245 "data/maps/CherrygroveCity/scripts.pory"
	.string "still knows about it. I've got readings\l"
# 2246 "data/maps/CherrygroveCity/scripts.pory"
	.string "I can't explain and I have never been\l"
# 2247 "data/maps/CherrygroveCity/scripts.pory"
	.string "happier.$"
# 2248 "data/maps/CherrygroveCity/scripts.pory"

# 2249 "data/maps/CherrygroveCity/scripts.pory"
@ the YES/NO
# 2250 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiRematchAsk:
# 2251 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Hold on, hold on. Before the science.\p"
# 2252 "data/maps/CherrygroveCity/scripts.pory"
	.string "You're the Champion of Johto, you've\n"
# 2253 "data/maps/CherrygroveCity/scripts.pory"
	.string "got a Necrozma in that team, and you\l"
# 2254 "data/maps/CherrygroveCity/scripts.pory"
	.string "have never once had to fight me for\l"
# 2255 "data/maps/CherrygroveCity/scripts.pory"
	.string "anything.\p"
# 2256 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's been bothering me for weeks.\n"
# 2257 "data/maps/CherrygroveCity/scripts.pory"
	.string "Let's fix it. Right here, feet in the\l"
# 2258 "data/maps/CherrygroveCity/scripts.pory"
	.string "water. What do you say?$"
# 2259 "data/maps/CherrygroveCity/scripts.pory"

# 2260 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiRematchNo:
# 2261 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Ha! Fine, fine. I'll be here measuring\n"
# 2262 "data/maps/CherrygroveCity/scripts.pory"
	.string "sand.\p"
# 2263 "data/maps/CherrygroveCity/scripts.pory"
	.string "Come back when you feel like it.$"
# 2264 "data/maps/CherrygroveCity/scripts.pory"

# 2265 "data/maps/CherrygroveCity/scripts.pory"
@ trainer defeat text
# 2266 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiBeaten:
# 2267 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}WOO! Yeah! That's the Champion!$"
# 2268 "data/maps/CherrygroveCity/scripts.pory"

# 2269 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiAfter:
# 2270 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Okay. OKAY. Now I've got data on you\n"
# 2271 "data/maps/CherrygroveCity/scripts.pory"
	.string "too.\p"
# 2272 "data/maps/CherrygroveCity/scripts.pory"
	.string "Same time tomorrow? …No, don't answer\n"
# 2273 "data/maps/CherrygroveCity/scripts.pory"
	.string "that. Just turn up.$"
# 2274 "data/maps/CherrygroveCity/scripts.pory"

# 2275 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachKukuiDoneToday:
# 2276 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}One a day, {PLAYER}! My Incineroar has a\n"
# 2277 "data/maps/CherrygroveCity/scripts.pory"
	.string "schedule and I am not the one who set\l"
# 2278 "data/maps/CherrygroveCity/scripts.pory"
	.string "it.$"
# 2279 "data/maps/CherrygroveCity/scripts.pory"

# 2280 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillie:
# 2281 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Hello. I hoped you'd come by.\p"
# 2282 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm not helping the professor, before\n"
# 2283 "data/maps/CherrygroveCity/scripts.pory"
	.string "you ask. I have my own notebook now,\l"
# 2284 "data/maps/CherrygroveCity/scripts.pory"
	.string "and it is about something completely\l"
# 2285 "data/maps/CherrygroveCity/scripts.pory"
	.string "different, and he is not allowed to read\l"
# 2286 "data/maps/CherrygroveCity/scripts.pory"
	.string "it.\p"
# 2287 "data/maps/CherrygroveCity/scripts.pory"
	.string "…It's about the nine of them. Where\n"
# 2288 "data/maps/CherrygroveCity/scripts.pory"
	.string "they came from. Somebody should be\l"
# 2289 "data/maps/CherrygroveCity/scripts.pory"
	.string "writing that down from the side of the\l"
# 2290 "data/maps/CherrygroveCity/scripts.pory"
	.string "ones who got eaten.$"
# 2291 "data/maps/CherrygroveCity/scripts.pory"

# 2292 "data/maps/CherrygroveCity/scripts.pory"
@ the YES/NO
# 2293 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieRematchAsk:
# 2294 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Before you go. Would you battle me?\p"
# 2295 "data/maps/CherrygroveCity/scripts.pory"
	.string "I know. You've beaten me in a flower\n"
# 2296 "data/maps/CherrygroveCity/scripts.pory"
	.string "shop, in a shrine and on a road. That's\l"
# 2297 "data/maps/CherrygroveCity/scripts.pory"
	.string "rather the point -- you have a very\l"
# 2298 "data/maps/CherrygroveCity/scripts.pory"
	.string "good record and I would like to ruin it.\p"
# 2299 "data/maps/CherrygroveCity/scripts.pory"
	.string "She's not a Vulpix any more, {PLAYER}.\n"
# 2300 "data/maps/CherrygroveCity/scripts.pory"
	.string "Look at her properly this time.$"
# 2301 "data/maps/CherrygroveCity/scripts.pory"

# 2302 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieRematchNo:
# 2303 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Of course. Another day.\p"
# 2304 "data/maps/CherrygroveCity/scripts.pory"
	.string "She'll be disappointed. She has been\n"
# 2305 "data/maps/CherrygroveCity/scripts.pory"
	.string "practising in front of the sea.$"
# 2306 "data/maps/CherrygroveCity/scripts.pory"

# 2307 "data/maps/CherrygroveCity/scripts.pory"
@ trainer defeat text
# 2308 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieBeaten:
# 2309 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}…There it is again.\p"
# 2310 "data/maps/CherrygroveCity/scripts.pory"
	.string "Thank you. I mean that.$"
# 2311 "data/maps/CherrygroveCity/scripts.pory"

# 2312 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieAfter:
# 2313 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Your record survives. I'm writing that\n"
# 2314 "data/maps/CherrygroveCity/scripts.pory"
	.string "down too, and I'm writing it down\l"
# 2315 "data/maps/CherrygroveCity/scripts.pory"
	.string "crossly.$"
# 2316 "data/maps/CherrygroveCity/scripts.pory"

# 2317 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_BeachLillieDoneToday:
# 2318 "data/maps/CherrygroveCity/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Once a day is plenty. She sulks, and\n"
# 2319 "data/maps/CherrygroveCity/scripts.pory"
	.string "then she sleeps in the sun, and then\l"
# 2320 "data/maps/CherrygroveCity/scripts.pory"
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
