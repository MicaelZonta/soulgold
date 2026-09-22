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
	end
# 16 "data/maps/CherrygroveCity/scripts.pory"

# 17 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_OnLoad::
# 18 "data/maps/CherrygroveCity/scripts.pory"
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
# 19 "data/maps/CherrygroveCity/scripts.pory"
	end
# 20 "data/maps/CherrygroveCity/scripts.pory"

# 21 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Top::
# 22 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 23 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_VISITED_CHERRYGROVE_CITY
# 24 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 25 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 26 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
# 27 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 28 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 29 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
# 30 "data/maps/CherrygroveCity/scripts.pory"
	waitmessage
# 31 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
# 32 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
# 33 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 34 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Top
# 35 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 36 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
# 37 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 38 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_GentTour
# 39 "data/maps/CherrygroveCity/scripts.pory"
	release
# 40 "data/maps/CherrygroveCity/scripts.pory"
	end
# 41 "data/maps/CherrygroveCity/scripts.pory"

# 42 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Mid::
# 43 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 44 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_VISITED_CHERRYGROVE_CITY
# 45 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 46 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 47 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
# 48 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 49 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 50 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
# 51 "data/maps/CherrygroveCity/scripts.pory"
	waitmessage
# 52 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
# 53 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
# 54 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 55 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
# 56 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 57 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 58 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_GentTour
# 59 "data/maps/CherrygroveCity/scripts.pory"
	release
# 60 "data/maps/CherrygroveCity/scripts.pory"
	end
# 61 "data/maps/CherrygroveCity/scripts.pory"

# 62 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Bottom::
# 63 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 64 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_VISITED_CHERRYGROVE_CITY
# 65 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 66 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 67 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, Common_Movement_ExclamationMark
# 68 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 69 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 70 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentIntro, MSGBOX_YESNO
# 71 "data/maps/CherrygroveCity/scripts.pory"
	waitmessage
# 72 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_TriggerGent_Cancel
# 73 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentTourStart, MSGBOX_DEFAULT
# 74 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 75 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Trigger_Gent
# 76 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 77 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Bottom
# 78 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0 
# 79 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_GentTour
# 80 "data/maps/CherrygroveCity/scripts.pory"
	release
# 81 "data/maps/CherrygroveCity/scripts.pory"
	end
# 82 "data/maps/CherrygroveCity/scripts.pory"

# 83 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerGent_Cancel::
# 84 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentDecline, MSGBOX_DEFAULT
# 85 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 86 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 1 @ CHANGE THIS TO 1 LATER
# 87 "data/maps/CherrygroveCity/scripts.pory"
	release
# 88 "data/maps/CherrygroveCity/scripts.pory"
	end
# 89 "data/maps/CherrygroveCity/scripts.pory"

# 90 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_GentTour::
# 91 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 92 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokecenter
# 93 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokecenter
# 94 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 95 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 96 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentPokecenter, MSGBOX_DEFAULT
# 97 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 98 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Pokemart
# 99 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Pokemart
# 100 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 101 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 102 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentMart, MSGBOX_DEFAULT
# 103 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 104 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Route30
# 105 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Route30
# 106 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 107 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 108 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentRoute30, MSGBOX_DEFAULT
# 109 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 110 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Sea
# 111 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Sea
# 112 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 113 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 114 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentSea, MSGBOX_DEFAULT
# 115 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 116 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_House_Gent
# 117 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_House_Player
# 118 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 119 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 120 "data/maps/CherrygroveCity/scripts.pory"
	delay 20
# 121 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_GuideGentMap, MSGBOX_DEFAULT
# 122 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 123 "data/maps/CherrygroveCity/scripts.pory"

# 124 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_GUIDE_GENT, CherryGroveCity_Movement_Gent_Leave
# 125 "data/maps/CherrygroveCity/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 126 "data/maps/CherrygroveCity/scripts.pory"
	delay 20
# 127 "data/maps/CherrygroveCity/scripts.pory"
	opendoor 42, 14
# 128 "data/maps/CherrygroveCity/scripts.pory"
	waitdooranim
# 129 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 130 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_GUIDE_GENT
# 131 "data/maps/CherrygroveCity/scripts.pory"
	closedoor 42, 14
# 132 "data/maps/CherrygroveCity/scripts.pory"
	waitdooranim
# 133 "data/maps/CherrygroveCity/scripts.pory"
	
# 134 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 135 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
# 136 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 1
# 137 "data/maps/CherrygroveCity/scripts.pory"
	fadedefaultbgm
# 138 "data/maps/CherrygroveCity/scripts.pory"
	release
# 139 "data/maps/CherrygroveCity/scripts.pory"
	end
# 140 "data/maps/CherrygroveCity/scripts.pory"

# 141 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Fisherman::
# 142 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 143 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 144 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_GOT_MYSTICWATER, CherryGroveCity_EventScript_Fisherman2
# 145 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_MysticWaterGuyBefore, MSGBOX_YESNO
# 146 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherryGroveCity_EventScript_Fisherman2
# 147 "data/maps/CherrygroveCity/scripts.pory"
	giveitem ITEM_MYSTIC_WATER
# 148 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull 
# 149 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 150 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_GOT_MYSTICWATER
# 151 "data/maps/CherrygroveCity/scripts.pory"
	release
# 152 "data/maps/CherrygroveCity/scripts.pory"
	end
# 153 "data/maps/CherrygroveCity/scripts.pory"

# 154 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Fisherman2::
# 155 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_MysticWaterGuyAfter, MSGBOX_DEFAULT
# 156 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 157 "data/maps/CherrygroveCity/scripts.pory"
	release
# 158 "data/maps/CherrygroveCity/scripts.pory"
	end
# 159 "data/maps/CherrygroveCity/scripts.pory"

# 160 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Lass::
# 161 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 162 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 163 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_TeacherHaveMapCard, MSGBOX_DEFAULT
# 164 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 165 "data/maps/CherrygroveCity/scripts.pory"
	release
# 166 "data/maps/CherrygroveCity/scripts.pory"
	end
# 167 "data/maps/CherrygroveCity/scripts.pory"

# 168 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Boy::
# 169 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 170 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 171 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_SYS_POKEDEX_GET, CherryGroveCity_EventScript_Boy2
# 172 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_YoungsterNoPokedex, MSGBOX_DEFAULT
# 173 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 174 "data/maps/CherrygroveCity/scripts.pory"
	release
# 175 "data/maps/CherrygroveCity/scripts.pory"
	end
# 176 "data/maps/CherrygroveCity/scripts.pory"

# 177 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Boy2::
# 178 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_YoungsterHavePokedex, MSGBOX_DEFAULT
# 179 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 180 "data/maps/CherrygroveCity/scripts.pory"
	release
# 181 "data/maps/CherrygroveCity/scripts.pory"
	end
# 182 "data/maps/CherrygroveCity/scripts.pory"

# 183 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Staryu::
# 184 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 185 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 186 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 187 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STARYU, CRY_MODE_NORMAL
# 188 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherryGroveCity_Text_Staryu, MSGBOX_DEFAULT
# 189 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 190 "data/maps/CherrygroveCity/scripts.pory"
	release
# 191 "data/maps/CherrygroveCity/scripts.pory"
	end
# 192 "data/maps/CherrygroveCity/scripts.pory"

# 193 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Corsola::
# 194 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 195 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 196 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 197 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_CORSOLA, CRY_MODE_NORMAL
# 198 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherryGroveCity_Text_Corsola, MSGBOX_DEFAULT
# 199 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 200 "data/maps/CherrygroveCity/scripts.pory"
	release
# 201 "data/maps/CherrygroveCity/scripts.pory"
	end
# 202 "data/maps/CherrygroveCity/scripts.pory"

# 203 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Krabby::
# 204 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 205 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 206 "data/maps/CherrygroveCity/scripts.pory"
	waitse
# 207 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_KRABBY, CRY_MODE_NORMAL
# 208 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherryGroveCity_Text_Krabby, MSGBOX_DEFAULT
# 209 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 210 "data/maps/CherrygroveCity/scripts.pory"
	release
# 211 "data/maps/CherrygroveCity/scripts.pory"
	end
# 212 "data/maps/CherrygroveCity/scripts.pory"

# 213 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_Sign::
# 214 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 215 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_CitySign, MSGBOX_SIGN
# 216 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 217 "data/maps/CherrygroveCity/scripts.pory"
	release
# 218 "data/maps/CherrygroveCity/scripts.pory"
	end	
# 219 "data/maps/CherrygroveCity/scripts.pory"

# 220 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerSilver_Top::
# 221 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 222 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Top
# 223 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 224 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_TriggerSilver
# 225 "data/maps/CherrygroveCity/scripts.pory"
	end
# 226 "data/maps/CherrygroveCity/scripts.pory"

# 227 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerSilver_Bottom::
# 228 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 229 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Trigger_Silver_Bottom
# 230 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 231 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_EventScript_TriggerSilver
# 232 "data/maps/CherrygroveCity/scripts.pory"
	end
# 233 "data/maps/CherrygroveCity/scripts.pory"

# 234 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_EventScript_TriggerSilver::
# 235 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 236 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
# 237 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Enter
# 238 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 239 "data/maps/CherrygroveCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 240 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_RivalSeen, MSGBOX_DEFAULT
# 241 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 242 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 0, CherryGroveCity_Silver_Battle_Cyndaquil
# 243 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 1, CherryGroveCity_Silver_Battle_Totodile
# 244 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 2, CherryGroveCity_Silver_Battle_Chikorita
# 245 "data/maps/CherrygroveCity/scripts.pory"
	release
# 246 "data/maps/CherrygroveCity/scripts.pory"
	end
# 247 "data/maps/CherrygroveCity/scripts.pory"

# 248 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_Battle_Cyndaquil::
# 249 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_1, CherrygroveCity_Text_SilverWin
# 250 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_Silver_AfterBattle
# 251 "data/maps/CherrygroveCity/scripts.pory"

# 252 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_Battle_Totodile::
# 253 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_1, CherrygroveCity_Text_SilverWin
# 254 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_Silver_AfterBattle
# 255 "data/maps/CherrygroveCity/scripts.pory"

# 256 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_Battle_Chikorita::
# 257 "data/maps/CherrygroveCity/scripts.pory"
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_1, CherrygroveCity_Text_SilverWin
# 258 "data/maps/CherrygroveCity/scripts.pory"
	goto CherryGroveCity_Silver_AfterBattle
# 259 "data/maps/CherrygroveCity/scripts.pory"

# 260 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Silver_AfterBattle::
# 261 "data/maps/CherrygroveCity/scripts.pory"
	playbgm MUS_HG_RIVAL_EXIT, TRUE
# 262 "data/maps/CherrygroveCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 263 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_RivalAfter, MSGBOX_DEFAULT
# 264 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 265 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherryGroveCity_Movement_Silver_Leave1Player
# 266 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave1
# 267 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 268 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 269 "data/maps/CherrygroveCity/scripts.pory"
	playse SE_PIN
# 270 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, Common_Movement_ExclamationMark
# 271 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 272 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_EAST
# 273 "data/maps/CherrygroveCity/scripts.pory"
	delay 60
# 274 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_SILVER, DIR_SOUTH
# 275 "data/maps/CherrygroveCity/scripts.pory"
	delay 30
# 276 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Return
# 277 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 278 "data/maps/CherrygroveCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 279 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_RivalID, MSGBOX_DEFAULT
# 280 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 281 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_SILVER, CherryGroveCity_Movement_Silver_Leave2
# 282 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement 0
# 283 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_SILVER
# 284 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_HIDE_SILVER_CHERRYGROVE
# 285 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 4
# 286 "data/maps/CherrygroveCity/scripts.pory"
	fadedefaultbgm
# 287 "data/maps/CherrygroveCity/scripts.pory"
	release
# 288 "data/maps/CherrygroveCity/scripts.pory"
	end
# 289 "data/maps/CherrygroveCity/scripts.pory"

# 290 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentIntro:
# 291 "data/maps/CherrygroveCity/scripts.pory"
	.string "You're a rookie trainer,\n"
# 292 "data/maps/CherrygroveCity/scripts.pory"
	.string "aren't you? I can tell!\p"
# 293 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's Ok! Everyone is a\n"
# 294 "data/maps/CherrygroveCity/scripts.pory"
	.string "rookie at some point!\p"
# 295 "data/maps/CherrygroveCity/scripts.pory"
	.string "If you'd like, I can teach\n"
# 296 "data/maps/CherrygroveCity/scripts.pory"
	.string "you a few things.$"
# 297 "data/maps/CherrygroveCity/scripts.pory"

# 298 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentTourStart:
# 299 "data/maps/CherrygroveCity/scripts.pory"
	.string "Ok, then!\n"
# 300 "data/maps/CherrygroveCity/scripts.pory"
	.string "Follow me!$"
# 301 "data/maps/CherrygroveCity/scripts.pory"

# 302 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentPokecenter:
# 303 "data/maps/CherrygroveCity/scripts.pory"
	.string "This is a Pokémon Center.\p"
# 304 "data/maps/CherrygroveCity/scripts.pory"
	.string "They heal your Pokémon in no\n"
# 305 "data/maps/CherrygroveCity/scripts.pory"
	.string "time at all.\p"
# 306 "data/maps/CherrygroveCity/scripts.pory"
	.string "You'll be relying on them a lot,\n"
# 307 "data/maps/CherrygroveCity/scripts.pory"
	.string "so you better learn about them.$"
# 308 "data/maps/CherrygroveCity/scripts.pory"

# 309 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentMart:
# 310 "data/maps/CherrygroveCity/scripts.pory"
	.string "This is a Pokémon Mart.\p"
# 311 "data/maps/CherrygroveCity/scripts.pory"
	.string "They sell Balls for catching wild\n"
# 312 "data/maps/CherrygroveCity/scripts.pory"
	.string "Pokémon and other useful items.$"
# 313 "data/maps/CherrygroveCity/scripts.pory"

# 314 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentRoute30:
# 315 "data/maps/CherrygroveCity/scripts.pory"
	.string "Route 30 is out this way.\p"
# 316 "data/maps/CherrygroveCity/scripts.pory"
	.string "Trainers will be battling\n"
# 317 "data/maps/CherrygroveCity/scripts.pory"
	.string "their prized Pokémon there.$"
# 318 "data/maps/CherrygroveCity/scripts.pory"

# 319 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentSea:
# 320 "data/maps/CherrygroveCity/scripts.pory"
	.string "This is the sea, as you can see.\p"
# 321 "data/maps/CherrygroveCity/scripts.pory"
	.string "Some Pokémon are found only in\n"
# 322 "data/maps/CherrygroveCity/scripts.pory"
	.string "in water.$"
# 323 "data/maps/CherrygroveCity/scripts.pory"

# 324 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentMap:
# 325 "data/maps/CherrygroveCity/scripts.pory"
	.string "Here…\p"
# 326 "data/maps/CherrygroveCity/scripts.pory"
	.string "It's my house! Thanks for\n"
# 327 "data/maps/CherrygroveCity/scripts.pory"
	.string "your company.\p"
# 328 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh, and if you're ever lost, check\n"
# 329 "data/maps/CherrygroveCity/scripts.pory"
	.string "the Map on your Pokégear!\p"
# 330 "data/maps/CherrygroveCity/scripts.pory"
	.string "I wish you luck on your journey!$"
# 331 "data/maps/CherrygroveCity/scripts.pory"

# 332 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentDecline:
# 333 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh… It's something I enjoy\n"
# 334 "data/maps/CherrygroveCity/scripts.pory"
	.string "doing…\p"
# 335 "data/maps/CherrygroveCity/scripts.pory"
	.string "Fine. Come see me whenever\n"
# 336 "data/maps/CherrygroveCity/scripts.pory"
	.string "you like.$"
# 337 "data/maps/CherrygroveCity/scripts.pory"

# 338 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_RivalSeen:
# 339 "data/maps/CherrygroveCity/scripts.pory"
	.string "… … … … … … … …\p"
# 340 "data/maps/CherrygroveCity/scripts.pory"
	.string "You got a Pokémon at the Lab.\p"
# 341 "data/maps/CherrygroveCity/scripts.pory"
	.string "What a waste.\n"
# 342 "data/maps/CherrygroveCity/scripts.pory"
	.string "A wimp like you.\p"
# 343 "data/maps/CherrygroveCity/scripts.pory"
	.string "… … … … … … … …\p"
# 344 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't you get what I'm saying?\n"
# 345 "data/maps/CherrygroveCity/scripts.pory"
	.string "Well, I too, have a good Pokémon.\p"
# 346 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll show you what I mean!$"
# 347 "data/maps/CherrygroveCity/scripts.pory"

# 348 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_SilverWin:
# 349 "data/maps/CherrygroveCity/scripts.pory"
	.string "Humph. Are you happy you won?$"
# 350 "data/maps/CherrygroveCity/scripts.pory"

# 351 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_RivalAfter:
# 352 "data/maps/CherrygroveCity/scripts.pory"
	.string "… … … … … … … …\p"
# 353 "data/maps/CherrygroveCity/scripts.pory"
	.string "Do you want to know who I am?\p"
# 354 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm going to be the world's\n"
# 355 "data/maps/CherrygroveCity/scripts.pory"
	.string "greatest Pokémon trainer.$"
# 356 "data/maps/CherrygroveCity/scripts.pory"

# 357 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_RivalID:
# 358 "data/maps/CherrygroveCity/scripts.pory"
	.string "Give it back!\n"
# 359 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's my Trainer Card!\p"
# 360 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh no!\n"
# 361 "data/maps/CherrygroveCity/scripts.pory"
	.string "You saw my name...$"
# 362 "data/maps/CherrygroveCity/scripts.pory"

# 363 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_TeacherHaveMapCard:
# 364 "data/maps/CherrygroveCity/scripts.pory"
	.string "When you're with Pokémon,\n"
# 365 "data/maps/CherrygroveCity/scripts.pory"
	.string "going anywhere is fun.$"
# 366 "data/maps/CherrygroveCity/scripts.pory"

# 367 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_YoungsterNoPokedex:
# 368 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui's house is still\n"
# 369 "data/maps/CherrygroveCity/scripts.pory"
	.string "farther up ahead.$"
# 370 "data/maps/CherrygroveCity/scripts.pory"

# 371 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_YoungsterHavePokedex:
# 372 "data/maps/CherrygroveCity/scripts.pory"
	.string "I battled the trainers on the\n"
# 373 "data/maps/CherrygroveCity/scripts.pory"
	.string "road.\p"
# 374 "data/maps/CherrygroveCity/scripts.pory"
	.string "My Pokémon lost. They're a\n"
# 375 "data/maps/CherrygroveCity/scripts.pory"
	.string "mess! I must take them to a\l"
# 376 "data/maps/CherrygroveCity/scripts.pory"
	.string "Pokémon Center.$"
# 377 "data/maps/CherrygroveCity/scripts.pory"

# 378 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_MysticWaterGuyBefore:
# 379 "data/maps/CherrygroveCity/scripts.pory"
	.string "A Pokémon I caught had an\n"
# 380 "data/maps/CherrygroveCity/scripts.pory"
	.string "item.\p"
# 381 "data/maps/CherrygroveCity/scripts.pory"
	.string "I think it's Mystic Water.\p"
# 382 "data/maps/CherrygroveCity/scripts.pory"
	.string "I don't need it, so do you\n"
# 383 "data/maps/CherrygroveCity/scripts.pory"
	.string "want it?$"
# 384 "data/maps/CherrygroveCity/scripts.pory"

# 385 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_MysticWaterGuyAfter:
# 386 "data/maps/CherrygroveCity/scripts.pory"
	.string "Back to fishing for me, then.$"
# 387 "data/maps/CherrygroveCity/scripts.pory"

# 388 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_CitySign:
# 389 "data/maps/CherrygroveCity/scripts.pory"
	.string "Cherrygrove City\p"
# 390 "data/maps/CherrygroveCity/scripts.pory"
	.string "The City of Cute, Fragrant\n"
# 391 "data/maps/CherrygroveCity/scripts.pory"
	.string "Flowers$"
# 392 "data/maps/CherrygroveCity/scripts.pory"

# 393 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_GuideGentsHouseSign:
# 394 "data/maps/CherrygroveCity/scripts.pory"
	.string "Guide Gent's House$"
# 395 "data/maps/CherrygroveCity/scripts.pory"

# 396 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Text_Staryu:
# 397 "data/maps/CherrygroveCity/scripts.pory"
	.string "Staryu: Yuuuuuuuu.$"
# 398 "data/maps/CherrygroveCity/scripts.pory"

# 399 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Text_Corsola:
# 400 "data/maps/CherrygroveCity/scripts.pory"
	.string "Corsola: Corsola! La!$"
# 401 "data/maps/CherrygroveCity/scripts.pory"

# 402 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Text_Krabby:
# 403 "data/maps/CherrygroveCity/scripts.pory"
	.string "Krabby: Kooookeee!$"
# 404 "data/maps/CherrygroveCity/scripts.pory"

# 405 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Gent:
# 406 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 407 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 408 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 409 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 410 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 411 "data/maps/CherrygroveCity/scripts.pory"

# 412 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Top:
# 413 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 414 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 415 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 416 "data/maps/CherrygroveCity/scripts.pory"

# 417 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Bottom:
# 418 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 419 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 420 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 421 "data/maps/CherrygroveCity/scripts.pory"

# 422 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Pokecenter:
# 423 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 424 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
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
	walk_up
# 433 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 434 "data/maps/CherrygroveCity/scripts.pory"

# 435 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Pokemart:
# 436 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 437 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
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
	face_up
# 444 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 445 "data/maps/CherrygroveCity/scripts.pory"

# 446 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Route30:
# 447 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 448 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
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
	walk_up
# 455 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 456 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 457 "data/maps/CherrygroveCity/scripts.pory"

# 458 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Sea:
# 459 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 460 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 461 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 462 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 463 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 464 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 465 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 466 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 467 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 468 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 469 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 470 "data/maps/CherrygroveCity/scripts.pory"
	walk_left
# 471 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 472 "data/maps/CherrygroveCity/scripts.pory"

# 473 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_House_Gent:
# 474 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 475 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 476 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 477 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 478 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 479 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 480 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
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
	face_up
# 495 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 496 "data/maps/CherrygroveCity/scripts.pory"

# 497 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_House_Player:
# 498 "data/maps/CherrygroveCity/scripts.pory"
	delay_16
# 499 "data/maps/CherrygroveCity/scripts.pory"
	delay_16
# 500 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 501 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 502 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 503 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 504 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
# 505 "data/maps/CherrygroveCity/scripts.pory"
	walk_right
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
	face_up
# 519 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 520 "data/maps/CherrygroveCity/scripts.pory"

# 521 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Gent_Leave:
# 522 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 523 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 524 "data/maps/CherrygroveCity/scripts.pory"

# 525 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Silver_Top:
# 526 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 527 "data/maps/CherrygroveCity/scripts.pory"
	face_right
# 528 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 529 "data/maps/CherrygroveCity/scripts.pory"

# 530 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Trigger_Silver_Bottom:
# 531 "data/maps/CherrygroveCity/scripts.pory"
	walk_up
# 532 "data/maps/CherrygroveCity/scripts.pory"
	face_right
# 533 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 534 "data/maps/CherrygroveCity/scripts.pory"

# 535 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Enter:
# 536 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 537 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
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
	step_end
# 545 "data/maps/CherrygroveCity/scripts.pory"

# 546 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Leave1:
# 547 "data/maps/CherrygroveCity/scripts.pory"
	delay_16
# 548 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 549 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 550 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 551 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 552 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 553 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 554 "data/maps/CherrygroveCity/scripts.pory"

# 555 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Leave1Player:
# 556 "data/maps/CherrygroveCity/scripts.pory"
	lock_facing_direction
# 557 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_down
# 558 "data/maps/CherrygroveCity/scripts.pory"
	unlock_facing_direction
# 559 "data/maps/CherrygroveCity/scripts.pory"
	face_up
# 560 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 561 "data/maps/CherrygroveCity/scripts.pory"

# 562 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Return:
# 563 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 564 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 565 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 566 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_right
# 567 "data/maps/CherrygroveCity/scripts.pory"
	face_down
# 568 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 569 "data/maps/CherrygroveCity/scripts.pory"

# 570 "data/maps/CherrygroveCity/scripts.pory"

# 571 "data/maps/CherrygroveCity/scripts.pory"
CherryGroveCity_Movement_Silver_Leave2:
# 572 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
# 573 "data/maps/CherrygroveCity/scripts.pory"
	walk_fast_left
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
	step_end

Cherrygrove_FadedSign::
# 585 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FadedSign_Text_0, MSGBOX_SIGN
	return


Cherrygrove_DarkraiEventDoor::
# 590 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 591 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 4
	goto_if_eq Cherrygrove_DarkraiEventDoor_2
# 623 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_7
# 626 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_DarkraiEventDoor_2:
# 592 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_0
# 597 "data/maps/CherrygroveCity/scripts.pory"
	checkspecies SPECIES_CRESSELIA
# 598 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_DarkraiEventDoor_6
# 604 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_2
# 605 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 20, 8, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_DarkraiEventDoor_Text_3, Cherrygrove_DarkraiEventDoor_Text_4
# 606 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Cherrygrove_DarkraiEventDoor_8
# 617 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_6
# 618 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_DarkraiEventDoor_6:
# 599 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_1
# 601 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_DarkraiEventDoor_8:
# 607 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_DarkraiEventDoor_Text_5
# 608 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 609 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_DARKRAI_INN_PROGRESS, 2
	goto_if_ge Cherrygrove_DarkraiEventDoor_12
# 612 "data/maps/CherrygroveCity/scripts.pory"
	warpwhitefade MAP_DARKRAI_INN1, 1
Cherrygrove_DarkraiEventDoor_11:
# 614 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
	end

Cherrygrove_DarkraiEventDoor_12:
# 610 "data/maps/CherrygroveCity/scripts.pory"
	warpwhitefade MAP_DARKRAI_INN1RUINED, 28, 18
	goto Cherrygrove_DarkraiEventDoor_11


Cherrygrove_Littlegirl::
# 631 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 632 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 633 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_POSTGAME_RIVAL_LEGENDARYQ, 5
	goto_if_eq Cherrygrove_Littlegirl_2
# 639 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Littlegirl_Text_1
# 642 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_Littlegirl_2:
# 634 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Littlegirl_Text_0
# 636 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_Zigzagoon::
# 647 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 648 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 649 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_ZIGZAGOON_GALAR, CRY_MODE_NORMAL
# 650 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Zigzagoon_Text_0
# 651 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_Rattata::
# 656 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 657 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 658 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_RATTATA_ALOLA, CRY_MODE_NORMAL
# 659 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_Rattata_Text_0
# 660 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_TraderNoRoom::
# 668 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_TraderNoRoom_Text_0
# 679 "data/maps/CherrygroveCity/scripts.pory"
	release
	end


Cherrygrove_FriendlyTrader::
# 684 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 685 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 686 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_ZIGZAGOON, Cherrygrove_FriendlyTrader_2
# 686 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_RATTATA, Cherrygrove_FriendlyTrader_2
# 691 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_RECEIVED_FIRST_BALLS, Cherrygrove_FriendlyTrader_7
# 787 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_7
# 794 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_2:
# 687 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_0
# 688 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

# 797 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_7:
# 697 "data/maps/CherrygroveCity/scripts.pory"
	getpartysize
# 698 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq Cherrygrove_FriendlyTrader_11
Cherrygrove_FriendlyTrader_10:
# 704 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_1
# 715 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Cherrygrove_FriendlyTrader_Text_2, Cherrygrove_FriendlyTrader_Text_3, Cherrygrove_FriendlyTrader_Text_4
# 716 "data/maps/CherrygroveCity/scripts.pory"
	switch VAR_RESULT
# 717 "data/maps/CherrygroveCity/scripts.pory"
	case 0, Cherrygrove_FriendlyTrader_14
# 749 "data/maps/CherrygroveCity/scripts.pory"
	case 1, Cherrygrove_FriendlyTrader_15
# 782 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_6
# 783 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_11:
# 699 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
# 700 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Cherrygrove_FriendlyTrader_17
	goto Cherrygrove_FriendlyTrader_10

Cherrygrove_FriendlyTrader_14:
# 718 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ZIGZAGOON_GALAR
# 719 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
# 720 "data/maps/CherrygroveCity/scripts.pory"
	givemon SPECIES_ZIGZAGOON_GALAR, 5
# 729 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq Cherrygrove_FriendlyTrader_20
Cherrygrove_FriendlyTrader_19:
# 732 "data/maps/CherrygroveCity/scripts.pory"
	showgivemonpic 10, 3
# 738 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_PICKED_ZIGZAGOON
# 739 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRY_ZIGZAGOON
# 740 "data/maps/CherrygroveCity/scripts.pory"
	call Common_EventScript_GiftMon
# 741 "data/maps/CherrygroveCity/scripts.pory"
	hidemonpic
# 742 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_ZIGZAGOON_GALAR
# 743 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_5
# 747 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_15:
# 750 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_RATTATA_ALOLA
# 751 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
# 752 "data/maps/CherrygroveCity/scripts.pory"
	givemon SPECIES_RATTATA_ALOLA, 5
# 761 "data/maps/CherrygroveCity/scripts.pory"
	compare VAR_RESULT, MON_CANT_GIVE
	goto_if_eq Cherrygrove_FriendlyTrader_23
Cherrygrove_FriendlyTrader_22:
# 764 "data/maps/CherrygroveCity/scripts.pory"
	showgivemonpic 10, 3
# 770 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_PICKED_RATTATA
# 771 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRY_RATTATA
# 772 "data/maps/CherrygroveCity/scripts.pory"
	call Common_EventScript_GiftMon
# 773 "data/maps/CherrygroveCity/scripts.pory"
	hidemonpic
# 774 "data/maps/CherrygroveCity/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_RATTATA_ALOLA
# 775 "data/maps/CherrygroveCity/scripts.pory"
	msgbox Cherrygrove_FriendlyTrader_Text_5
# 779 "data/maps/CherrygroveCity/scripts.pory"
	release
	end

Cherrygrove_FriendlyTrader_17:
# 701 "data/maps/CherrygroveCity/scripts.pory"
	goto Cherrygrove_TraderNoRoom
	goto Cherrygrove_FriendlyTrader_10

Cherrygrove_FriendlyTrader_20:
# 730 "data/maps/CherrygroveCity/scripts.pory"
	goto Cherrygrove_TraderNoRoom
	goto Cherrygrove_FriendlyTrader_19

Cherrygrove_FriendlyTrader_23:
# 762 "data/maps/CherrygroveCity/scripts.pory"
	goto Cherrygrove_TraderNoRoom
	goto Cherrygrove_FriendlyTrader_22


# 801 "data/maps/CherrygroveCity/scripts.pory"

# 802 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 803 "data/maps/CherrygroveCity/scripts.pory"
@ Rift Mission 3 - Blacephalon + Stakataka on the Cherrygrove beach.
# 804 "data/maps/CherrygroveCity/scripts.pory"
@ Cast: Looker, Anabel and Professor Kukui (no partner Pokemon out of its
# 805 "data/maps/CherrygroveCity/scripts.pory"
@ ball: design section 3.2 only requires that of Lillie and Gladion).
# 806 "data/maps/CherrygroveCity/scripts.pory"
@ Plan: .claude/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md
# 807 "data/maps/CherrygroveCity/scripts.pory"
@
# 808 "data/maps/CherrygroveCity/scripts.pory"
@ Floor plan - read TWICE. The collision bit (dump_mapa.py) is NOT enough on
# 809 "data/maps/CherrygroveCity/scripts.pory"
@ a shore: half this beach has collision 0 and is still water. The sand /
# 810 "data/maps/CherrygroveCity/scripts.pory"
@ shallow / ocean split below comes from the metatile_attributes.bin of
# 811 "data/maps/CherrygroveCity/scripts.pory"
@ johto_general and cherrygrove_city. y grows DOWNWARD.
# 812 "data/maps/CherrygroveCity/scripts.pory"
@
# 813 "data/maps/CherrygroveCity/scripts.pory"
@       x= 21 22 23 24 25 26 27 28 29 30 31 32
# 814 "data/maps/CherrygroveCity/scripts.pory"
@   y= 5     #  #  #  #  #  #  #  #  #  #  #  #
# 815 "data/maps/CherrygroveCity/scripts.pory"
@   y= 6     #  #  #  #  #  #  #  #  #  #  #  #   north wall
# 816 "data/maps/CherrygroveCity/scripts.pory"
@   y= 7     ~  w  w  w  w  U  K  A  s  .  .  .   U Kukui (26,7)  K Looker (27,7)
# 817 "data/maps/CherrygroveCity/scripts.pory"
@   y= 8     ~  ~  ~  ~  c  s  t  s  .  .  .  .   A Anabel (28,7)
# 818 "data/maps/CherrygroveCity/scripts.pory"
@   y= 9     ~  ~  ~  B  c  s  s  .  .  .  .  .   t (27,8) = the ONLY talk tile
# 819 "data/maps/CherrygroveCity/scripts.pory"
@   y=10     ~  ~  ~  S  w  s  *  .  .  .  .  .   B Blacephalon (24,9)
# 820 "data/maps/CherrygroveCity/scripts.pory"
@   y=11     ~  ~  ~  ~  w  s  s  .  .  .  .  #   S Stakataka   (24,10)
# 821 "data/maps/CherrygroveCity/scripts.pory"
@   y=12     ~  ~  ~  ~  w  s  s  .  .  #  #  #   c Corsola (hidden by the event)
# 822 "data/maps/CherrygroveCity/scripts.pory"
@                                                 * player at the end (27,10)
# 823 "data/maps/CherrygroveCity/scripts.pory"
@   #  collision        s  MB_SAND        .  MB_NORMAL
# 824 "data/maps/CherrygroveCity/scripts.pory"
@   ~  MB_OCEAN_WATER   - Surf only; the player on foot can NOT enter
# 825 "data/maps/CherrygroveCity/scripts.pory"
@   w  MB_SHALLOW_WATER - collision 0; the player on foot DOES walk on it
# 826 "data/maps/CherrygroveCity/scripts.pory"
@
# 827 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: column x=25 and the strip (22..25,7) are SHALLOW water, not a
# 828 "data/maps/CherrygroveCity/scripts.pory"
@ barrier - the player wades through them. Only x<=24 is real ocean. The two
# 829 "data/maps/CherrygroveCity/scripts.pory"
@ Ultra Beasts stand on ocean on purpose: nobody reaches them on foot.
# 830 "data/maps/CherrygroveCity/scripts.pory"
@
# 831 "data/maps/CherrygroveCity/scripts.pory"
@ Looker sits in a pocket: (27,6) is wall, (26,7) is Kukui and (28,7) is
# 832 "data/maps/CherrygroveCity/scripts.pory"
@ Anabel. The ONLY tile he can be talked to from is (27,8), facing up. That
# 833 "data/maps/CherrygroveCity/scripts.pory"
@ is what makes the start of the cutscene deterministic without a
# 834 "data/maps/CherrygroveCity/scripts.pory"
@ getplayerxy check.
# 835 "data/maps/CherrygroveCity/scripts.pory"
@
# 836 "data/maps/CherrygroveCity/scripts.pory"
@ Retry cost: HEAL_LOCATION_CHERRYGROVE_CITY is (47,8) and row y=8 is clear
# 837 "data/maps/CherrygroveCity/scripts.pory"
@ from x=27 to x=49, so a blackout costs a straight 20-tile walk back. That
# 838 "data/maps/CherrygroveCity/scripts.pory"
@ is accepted (section 9 of the doc): there is no Center nearer the beach.
# 839 "data/maps/CherrygroveCity/scripts.pory"
@
# 840 "data/maps/CherrygroveCity/scripts.pory"
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
# 841 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_1 - cast visibility cache (Kukui, Looker, Anabel)
# 842 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_2 - Ultra Beast visibility cache
# 843 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_3 - Galarian Zigzagoon gift visibility cache
# 844 "data/maps/CherrygroveCity/scripts.pory"
@   FLAG_TEMP_4 - Alolan Rattata gift visibility cache
# 845 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_2  - battle outcome
# 846 "data/maps/CherrygroveCity/scripts.pory"
@   VAR_TEMP_3  - the player's pick: 0 = Blacephalon, 1 = Stakataka. Survives
# 847 "data/maps/CherrygroveCity/scripts.pory"
@                 the battle because coming back from a battle does not
# 848 "data/maps/CherrygroveCity/scripts.pory"
@                 reload the map (ClearTempFieldEventData only runs on warp
# 849 "data/maps/CherrygroveCity/scripts.pory"
@                 and edge loads).
# 850 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: VAR_TEMP_1 is VAR_TEMP_TRANSFERRED_SPECIES (vars.h:370) and
# 851 "data/maps/CherrygroveCity/scripts.pory"
@ belongs to Cherrygrove_FriendlyTrader, below in this file. This mission
# 852 "data/maps/CherrygroveCity/scripts.pory"
@ starts at VAR_TEMP_2 on purpose - do NOT "harmonise" it away.
# 853 "data/maps/CherrygroveCity/scripts.pory"
@
# 854 "data/maps/CherrygroveCity/scripts.pory"
@ WARNING: fourteen residents of this map now carry
# 855 "data/maps/CherrygroveCity/scripts.pory"
@ FLAG_EVENT_ULTRABEAST_CHERRYGROVE in their map.json "flag" field. A
# 856 "data/maps/CherrygroveCity/scripts.pory"
@ removeobject on any of them SETS that flag and empties the city.
# 857 "data/maps/CherrygroveCity/scripts.pory"
@ ============================================================================
# 858 "data/maps/CherrygroveCity/scripts.pory"

# 859 "data/maps/CherrygroveCity/scripts.pory"
@ Called from CherrygroveCity_OnTransition, which runs before any object is
# 860 "data/maps/CherrygroveCity/scripts.pory"
@ spawned - so setflag/clearflag work here and removeobject would not.
# 861 "data/maps/CherrygroveCity/scripts.pory"
@ The cast (FLAG_TEMP_1) is visible only while the incident is active. The
# 862 "data/maps/CherrygroveCity/scripts.pory"
@ Ultra Beasts (FLAG_TEMP_2) are always hidden on load: only the cutscene
# 863 "data/maps/CherrygroveCity/scripts.pory"
@ brings them in. Temps are zeroed on every load, so this recomputes from
# 864 "data/maps/CherrygroveCity/scripts.pory"
@ scratch every time.
# 865 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyUBVisibility::
# 866 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_2
# 867 "data/maps/CherrygroveCity/scripts.pory"
	call CherrygroveCity_EventScript_ApplyGiftMonVisibility
# 868 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_unset FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_HideUBCast
# 869 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_1
# 870 "data/maps/CherrygroveCity/scripts.pory"
	return
# 871 "data/maps/CherrygroveCity/scripts.pory"

# 872 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_HideUBCast::
# 873 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_1
# 874 "data/maps/CherrygroveCity/scripts.pory"
	return
# 875 "data/maps/CherrygroveCity/scripts.pory"

# 876 "data/maps/CherrygroveCity/scripts.pory"
@ The Friendly Trader's two gift Pokemon (locals 16 and 17). Their map.json
# 877 "data/maps/CherrygroveCity/scripts.pory"
@ "flag" field used to be FLAG_PICKED_ZIGZAGOON / FLAG_PICKED_RATTATA, but
# 878 "data/maps/CherrygroveCity/scripts.pory"
@ that field holds ONE flag and the incident needs a second condition, so it
# 879 "data/maps/CherrygroveCity/scripts.pory"
@ now holds a dumb per-visit cache instead - the same pattern as
# 880 "data/maps/CherrygroveCity/scripts.pory"
@ FLAG_HIDE_CIANWOOD_GLADION. FLAG_PICKED_* stays the persistent truth.
# 881 "data/maps/CherrygroveCity/scripts.pory"
@   visible <=> (not picked yet) AND (no incident running)
# 882 "data/maps/CherrygroveCity/scripts.pory"
@ Because the template flag changed, the removeobject in
# 883 "data/maps/CherrygroveCity/scripts.pory"
@ Cherrygrove_FriendlyTrader no longer makes the gift permanent: the
# 884 "data/maps/CherrygroveCity/scripts.pory"
@ explicit setflag(FLAG_PICKED_*) there does. Never delete it.
# 885 "data/maps/CherrygroveCity/scripts.pory"
@ Deliberately preserved: taking one gift still leaves the OTHER one standing
# 886 "data/maps/CherrygroveCity/scripts.pory"
@ in the street. That oddity predates this mission and is not fixed here.
# 887 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_ApplyGiftMonVisibility::
# 888 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_3
# 889 "data/maps/CherrygroveCity/scripts.pory"
	setflag FLAG_TEMP_4
# 890 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_EVENT_ULTRABEAST_CHERRYGROVE, CherrygroveCity_EventScript_GiftMonsStayHidden
# 891 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_ZIGZAGOON, CherrygroveCity_EventScript_GiftMonRattataOnly
# 892 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_3
# 893 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_GiftMonRattataOnly::
# 894 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_set FLAG_PICKED_RATTATA, CherrygroveCity_EventScript_GiftMonsStayHidden
# 895 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_4
# 896 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_GiftMonsStayHidden::
# 897 "data/maps/CherrygroveCity/scripts.pory"
	return
# 898 "data/maps/CherrygroveCity/scripts.pory"

# 899 "data/maps/CherrygroveCity/scripts.pory"
@ SKELETON: placeholder line, rewrite in the design's voice (Anabel precise).
# 900 "data/maps/CherrygroveCity/scripts.pory"
@ The turnobject returns her to the map.json FACE_DOWN. It is a no-op when
# 901 "data/maps/CherrygroveCity/scripts.pory"
@ the player talks from (28,8) or (29,7), but it guards any evolution that
# 902 "data/maps/CherrygroveCity/scripts.pory"
@ moves her.
# 903 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAnabel::
# 904 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 905 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 906 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAnabelIdle, MSGBOX_DEFAULT
# 907 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 908 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_ANABEL, DIR_SOUTH
# 909 "data/maps/CherrygroveCity/scripts.pory"
	release
# 910 "data/maps/CherrygroveCity/scripts.pory"
	end
# 911 "data/maps/CherrygroveCity/scripts.pory"

# 912 "data/maps/CherrygroveCity/scripts.pory"
@ SKELETON: placeholder line, rewrite in the design's voice (Kukui eager and
# 913 "data/maps/CherrygroveCity/scripts.pory"
@ concrete, never a joke). Same no-op turnobject guard as Anabel; note he is
# 914 "data/maps/CherrygroveCity/scripts.pory"
@ also reachable from (25,7), which is shallow water the player can wade in.
# 915 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukui::
# 916 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 917 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 918 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiIdle, MSGBOX_DEFAULT
# 919 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 920 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_SOUTH
# 921 "data/maps/CherrygroveCity/scripts.pory"
	release
# 922 "data/maps/CherrygroveCity/scripts.pory"
	end
# 923 "data/maps/CherrygroveCity/scripts.pory"

# 924 "data/maps/CherrygroveCity/scripts.pory"
@ Only reachable from (27,8), facing up: (27,6) is wall and Looker's east and
# 925 "data/maps/CherrygroveCity/scripts.pory"
@ west neighbours are Anabel and Kukui. No getplayerxy needed.
# 926 "data/maps/CherrygroveCity/scripts.pory"
@ Nothing changes state before the YES. The YES is the last exit point: from
# 927 "data/maps/CherrygroveCity/scripts.pory"
@ there on everything is scripted through to a battle outcome.
# 928 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui's read comes BEFORE the YES on purpose: his observation (the two work
# 929 "data/maps/CherrygroveCity/scripts.pory"
@ as a pair, one distracts and the other walks in) IS the justification for
# 930 "data/maps/CherrygroveCity/scripts.pory"
@ the choice-plus-boss structure, exactly like Lillie's read in Mission 2.
# 931 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBLooker::
# 932 "data/maps/CherrygroveCity/scripts.pory"
	lock
# 933 "data/maps/CherrygroveCity/scripts.pory"
	faceplayer
# 934 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBLookerGreet, MSGBOX_DEFAULT
# 935 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiTheory, MSGBOX_DEFAULT
# 936 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBReady, MSGBOX_YESNO
# 937 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_RESULT, NO, CherrygroveCity_EventScript_UBNotReady
# 938 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBScene
# 939 "data/maps/CherrygroveCity/scripts.pory"

# 940 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBNotReady::
# 941 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBNotReady, MSGBOX_DEFAULT
# 942 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 943 "data/maps/CherrygroveCity/scripts.pory"
	release
# 944 "data/maps/CherrygroveCity/scripts.pory"
	end
# 945 "data/maps/CherrygroveCity/scripts.pory"

# 946 "data/maps/CherrygroveCity/scripts.pory"
@ SKELETON: the rift is a camera shake plus a white flash and the beasts
# 947 "data/maps/CherrygroveCity/scripts.pory"
@ appear standing still. Evolution: the sea drawing back before it opens
# 948 "data/maps/CherrygroveCity/scripts.pory"
@ (setweather / palette), a portal animation over the water, its own music,
# 949 "data/maps/CherrygroveCity/scripts.pory"
@ Blacephalon's lights flickering.
# 950 "data/maps/CherrygroveCity/scripts.pory"
@
# 951 "data/maps/CherrygroveCity/scripts.pory"
@ The order of the three applymovement blocks is LOAD-BEARING:
# 952 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui -> player -> Looker/Anabel. Looker can only step down once the
# 953 "data/maps/CherrygroveCity/scripts.pory"
@ player has vacated (27,8), and Kukui goes first because he ends up in
# 954 "data/maps/CherrygroveCity/scripts.pory"
@ front. Every tile walked here was checked in the metatile attributes:
# 955 "data/maps/CherrygroveCity/scripts.pory"
@ (26,8..10), (27,8..10) and (28,8) are MB_SAND; nobody steps in water.
# 956 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBScene::
# 957 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 958 "data/maps/CherrygroveCity/scripts.pory"
	lockall
# 959 "data/maps/CherrygroveCity/scripts.pory"
	hidefollower
# 960 "data/maps/CherrygroveCity/scripts.pory"
	@ Kukui (26,7)->(26,8)->(26,9)->(26,10), faces west. Column x=26 all the
# 961 "data/maps/CherrygroveCity/scripts.pory"
	@ way; ends up beside the player, who stops at (27,10).
# 962 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_KUKUI, CherrygroveCity_Movement_KukuiAdvance
# 963 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_KUKUI
# 964 "data/maps/CherrygroveCity/scripts.pory"
	@ Player (27,8)->(27,9)->(27,10), faces west. Column x=27 all the way, no
# 965 "data/maps/CherrygroveCity/scripts.pory"
	@ tile shared with Kukui on any step; still goes second so that (27,8)
# 966 "data/maps/CherrygroveCity/scripts.pory"
	@ only frees up after the player has left it.
# 967 "data/maps/CherrygroveCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, CherrygroveCity_Movement_PlayerToLine
# 968 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 969 "data/maps/CherrygroveCity/scripts.pory"
	@ Looker (27,7)->(27,8) and Anabel (28,7)->(28,8): different columns, no
# 970 "data/maps/CherrygroveCity/scripts.pory"
	@ contention, so they walk together.
# 971 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_StepDownFaceLeft
# 972 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_StepDownFaceLeft
# 973 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 974 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 975 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBRiftWarning, MSGBOX_DEFAULT
# 976 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 977 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8004, 1   @ vertical pan
# 978 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8005, 1   @ horizontal pan
# 979 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8006, 24  @ num shakes
# 980 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_0x8007, 5   @ shake delay
# 981 "data/maps/CherrygroveCity/scripts.pory"
	special ShakeCamera
# 982 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 983 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_WHITE
# 984 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_TEMP_2
# 985 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 986 "data/maps/CherrygroveCity/scripts.pory"
	addobject LOCALID_CHERRYGROVE_UB_STAKATAKA
# 987 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_FROM_WHITE
# 988 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
# 989 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 990 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 991 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 992 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAppear, MSGBOX_DEFAULT
# 993 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBChoose
# 994 "data/maps/CherrygroveCity/scripts.pory"

# 995 "data/maps/CherrygroveCity/scripts.pory"
@ Standard Rift Mission structure: the player picks which Ultra Beast to
# 996 "data/maps/CherrygroveCity/scripts.pory"
@ fight, the mission companion takes the other. No cancel (ignoreBPress
# 997 "data/maps/CherrygroveCity/scripts.pory"
@ TRUE) - the scene has already started, so VAR_RESULT can only be 0 or 1.
# 998 "data/maps/CherrygroveCity/scripts.pory"
@ The pick is per attempt: after a blackout the player chooses again.
# 999 "data/maps/CherrygroveCity/scripts.pory"
@ Everyone already faces the right way in either branch: the player, Kukui,
# 1000 "data/maps/CherrygroveCity/scripts.pory"
@ Looker and Anabel are all east of the beasts and end up facing west, and
# 1001 "data/maps/CherrygroveCity/scripts.pory"
@ both beasts are FACE_RIGHT in the map.json. No turnobject is needed.
# 1002 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBChoose::
# 1003 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBChoosePrompt, MSGBOX_DEFAULT
# 1004 "data/maps/CherrygroveCity/scripts.pory"
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, CherrygroveCity_Text_ChoiceBlacephalon, CherrygroveCity_Text_ChoiceStakataka
# 1005 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Blacephalon, 1 = Stakataka
# 1006 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1007 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBPickStakataka
# 1008 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_BLACEPHALON, Common_Movement_ExclamationMark
# 1009 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1010 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPickedBlacephalon, MSGBOX_DEFAULT
# 1011 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1012 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBBattle
# 1013 "data/maps/CherrygroveCity/scripts.pory"

# 1014 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBPickStakataka::
# 1015 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_STAKATAKA, Common_Movement_ExclamationMark
# 1016 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1017 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBPickedStakataka, MSGBOX_DEFAULT
# 1018 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1019 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBBattle
# 1020 "data/maps/CherrygroveCity/scripts.pory"

# 1021 "data/maps/CherrygroveCity/scripts.pory"
@ Boss battle through the project's boss system, which only survives a SIMPLE
# 1022 "data/maps/CherrygroveCity/scripts.pory"
@ battle - the other reason the mission splits the beasts.
# 1023 "data/maps/CherrygroveCity/scripts.pory"
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
# 1024 "data/maps/CherrygroveCity/scripts.pory"
@ losing means a blackout and a retry.
# 1025 "data/maps/CherrygroveCity/scripts.pory"
@
# 1026 "data/maps/CherrygroveCity/scripts.pory"
@ NOT a skeleton: the numbers below are the target. Third step of the ladder
# 1027 "data/maps/CherrygroveCity/scripts.pory"
@ after Blackthorn (2 bars / Lv70 / x110) and Mahogany (4 / Lv80 / x130).
# 1028 "data/maps/CherrygroveCity/scripts.pory"
@ The bars have been at MAX_BOSS_HEALTH_BARS since Mission 2, so the step up
# 1029 "data/maps/CherrygroveCity/scripts.pory"
@ here is the level, the multiplier and - above all - one control move per
# 1030 "data/maps/CherrygroveCity/scripts.pory"
@ boss: Calm Mind on Blacephalon, Trick Room on Stakataka.
# 1031 "data/maps/CherrygroveCity/scripts.pory"
@ Mind Blown is left off Blacephalon ON PURPOSE: it costs half its max HP,
# 1032 "data/maps/CherrygroveCity/scripts.pory"
@ which on a 4-bar boss is the AI killing itself for free.
# 1033 "data/maps/CherrygroveCity/scripts.pory"
@ If playtesting says "wall" instead of "threat", turn the screws in THIS
# 1034 "data/maps/CherrygroveCity/scripts.pory"
@ order, one at a time (different from Mission 2, because here the held item
# 1035 "data/maps/CherrygroveCity/scripts.pory"
@ is the loosest screw):
# 1036 "data/maps/CherrygroveCity/scripts.pory"
@   1. drop ITEM_WEAKNESS_POLICY from Stakataka (highest variance)
# 1037 "data/maps/CherrygroveCity/scripts.pory"
@   2. multiplier 140 -> 135 -> 130
# 1038 "data/maps/CherrygroveCity/scripts.pory"
@   3. swap Trick Room for a fourth attacking move
# 1039 "data/maps/CherrygroveCity/scripts.pory"
@   4. level 85 -> 80
# 1040 "data/maps/CherrygroveCity/scripts.pory"
@ The bars are at the ceiling and are not a screw. Do not touch anything in
# 1041 "data/maps/CherrygroveCity/scripts.pory"
@ section 1 of the implementation doc to compensate.
# 1042 "data/maps/CherrygroveCity/scripts.pory"
@
# 1043 "data/maps/CherrygroveCity/scripts.pory"
@ Macro order is the same as bosslegendaryencounterwithmoves
# 1044 "data/maps/CherrygroveCity/scripts.pory"
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
# 1045 "data/maps/CherrygroveCity/scripts.pory"
@ seteventmonmoves -> special. No path leaves the script in between, so no
# 1046 "data/maps/CherrygroveCity/scripts.pory"
@ clearbossbattle is needed.
# 1047 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBBattle::
# 1048 "data/maps/CherrygroveCity/scripts.pory"
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
# 1049 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBSetupStakataka
# 1050 "data/maps/CherrygroveCity/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
# 1051 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
# 1052 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1053 "data/maps/CherrygroveCity/scripts.pory"
	seteventmon SPECIES_BLACEPHALON, 85, ITEM_WISE_GLASSES
# 1054 "data/maps/CherrygroveCity/scripts.pory"
	seteventmonmoves MOVE_CALM_MIND, MOVE_SHADOW_BALL, MOVE_FLAMETHROWER, MOVE_PSYSHOCK
# 1055 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBStartBattle
# 1056 "data/maps/CherrygroveCity/scripts.pory"

# 1057 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBSetupStakataka::
# 1058 "data/maps/CherrygroveCity/scripts.pory"
	setbossbattle 4, SPECIES_NONE, 140, BOSS_PHASE_PROFILE_NONE
# 1059 "data/maps/CherrygroveCity/scripts.pory"
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
# 1060 "data/maps/CherrygroveCity/scripts.pory"
	waitmoncry
# 1061 "data/maps/CherrygroveCity/scripts.pory"
	seteventmon SPECIES_STAKATAKA, 85, ITEM_WEAKNESS_POLICY
# 1062 "data/maps/CherrygroveCity/scripts.pory"
	seteventmonmoves MOVE_TRICK_ROOM, MOVE_GYRO_BALL, MOVE_STONE_EDGE, MOVE_BODY_PRESS
# 1063 "data/maps/CherrygroveCity/scripts.pory"

# 1064 "data/maps/CherrygroveCity/scripts.pory"
@ LOST, DREW and FORFEITED never come back here - the engine blacks the
# 1065 "data/maps/CherrygroveCity/scripts.pory"
@ player out to the Cherrygrove Pokemon Center (CherrygroveCity_OnLoad does
# 1066 "data/maps/CherrygroveCity/scripts.pory"
@ the setrespawn). CAUGHT and RAN are unreachable (ball blocked; Run becomes
# 1067 "data/maps/CherrygroveCity/scripts.pory"
@ FORFEITED in a boss) but are handled anyway: anything that is not WON
# 1068 "data/maps/CherrygroveCity/scripts.pory"
@ resets the scene, never wins it.
# 1069 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBStartBattle::
# 1070 "data/maps/CherrygroveCity/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 1071 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1072 "data/maps/CherrygroveCity/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 1073 "data/maps/CherrygroveCity/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 1074 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, CherrygroveCity_EventScript_UBResolved
# 1075 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBUnresolved
# 1076 "data/maps/CherrygroveCity/scripts.pory"

# 1077 "data/maps/CherrygroveCity/scripts.pory"
@ Nothing was recorded as done: the event flag is still set, so reloading the
# 1078 "data/maps/CherrygroveCity/scripts.pory"
@ map puts the cast back on its map.json spots with the beasts hidden again,
# 1079 "data/maps/CherrygroveCity/scripts.pory"
@ and talking to Looker restarts the whole scene - the pick included.
# 1080 "data/maps/CherrygroveCity/scripts.pory"
@ (28,8) is free sand, one step east of Looker's talk tile.
# 1081 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBUnresolved::
# 1082 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBGotAway, MSGBOX_DEFAULT
# 1083 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1084 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1085 "data/maps/CherrygroveCity/scripts.pory"
	warpsilent MAP_CHERRYGROVE_CITY, 28, 8
# 1086 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1087 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 1088 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1089 "data/maps/CherrygroveCity/scripts.pory"

# 1090 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui's fight against the other beast is narrative: it resolves with the
# 1091 "data/maps/CherrygroveCity/scripts.pory"
@ player's win and only his line afterwards changes with the pick.
# 1092 "data/maps/CherrygroveCity/scripts.pory"
@ SKELETON: evolution can stage his fight on screen. A real battle against
# 1093 "data/maps/CherrygroveCity/scripts.pory"
@ Kukui is NOT the plan.
# 1094 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBResolved::
# 1095 "data/maps/CherrygroveCity/scripts.pory"
	@ Both beast objects are still on the map: a battle does not reload it.
# 1096 "data/maps/CherrygroveCity/scripts.pory"
	@ Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
# 1097 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_WHITE
# 1098 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_BLACEPHALON
# 1099 "data/maps/CherrygroveCity/scripts.pory"
	removeobject LOCALID_CHERRYGROVE_UB_STAKATAKA
# 1100 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_FROM_WHITE
# 1101 "data/maps/CherrygroveCity/scripts.pory"
	goto_if_eq VAR_TEMP_3, 1, CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon
# 1102 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiFoughtStakataka, MSGBOX_DEFAULT
# 1103 "data/maps/CherrygroveCity/scripts.pory"
	goto CherrygroveCity_EventScript_UBAfterBattle
# 1104 "data/maps/CherrygroveCity/scripts.pory"

# 1105 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBKukuiFoughtBlacephalon::
# 1106 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBKukuiFoughtBlacephalon, MSGBOX_DEFAULT
# 1107 "data/maps/CherrygroveCity/scripts.pory"

# 1108 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_EventScript_UBAfterBattle::
# 1109 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBAfterKukui, MSGBOX_DEFAULT
# 1110 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1111 "data/maps/CherrygroveCity/scripts.pory"
	@ Looker (27,8)->(27,9), faces west. Same column as the player, one row
# 1112 "data/maps/CherrygroveCity/scripts.pory"
	@ ABOVE him - never south of him, so the text box covers nobody.
# 1113 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_LOOKER, CherrygroveCity_Movement_StepDownFaceLeft
# 1114 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_LOOKER
# 1115 "data/maps/CherrygroveCity/scripts.pory"
	@ Anabel (28,8)->(28,9)->(28,10), faces west. Her own column (x=28),
# 1116 "data/maps/CherrygroveCity/scripts.pory"
	@ always east of the player, no tile shared with Looker. SEQUENTIAL after
# 1117 "data/maps/CherrygroveCity/scripts.pory"
	@ him purely so the scene reads one actor at a time.
# 1118 "data/maps/CherrygroveCity/scripts.pory"
	applymovement LOCALID_CHERRYGROVE_UB_ANABEL, CherrygroveCity_Movement_AnabelToPlayer
# 1119 "data/maps/CherrygroveCity/scripts.pory"
	waitmovement LOCALID_CHERRYGROVE_UB_ANABEL
# 1120 "data/maps/CherrygroveCity/scripts.pory"
	turnobject LOCALID_CHERRYGROVE_UB_KUKUI, DIR_EAST     @ player (27,10) is due east of (26,10)
# 1121 "data/maps/CherrygroveCity/scripts.pory"
	msgbox CherrygroveCity_Text_UBHook, MSGBOX_DEFAULT
# 1122 "data/maps/CherrygroveCity/scripts.pory"
	closemessage
# 1123 "data/maps/CherrygroveCity/scripts.pory"
	fadescreen FADE_TO_BLACK
# 1124 "data/maps/CherrygroveCity/scripts.pory"
	clearflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE   @ invariant: flag and var together
# 1125 "data/maps/CherrygroveCity/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 8
# 1126 "data/maps/CherrygroveCity/scripts.pory"
	@ Reload in place under the fade. With the flag cleared the fourteen
# 1127 "data/maps/CherrygroveCity/scripts.pory"
	@ residents - and the trader's gift Pokemon, whose visibility is also
# 1128 "data/maps/CherrygroveCity/scripts.pory"
	@ recomputed on load - would otherwise pop in one by one as the camera
# 1129 "data/maps/CherrygroveCity/scripts.pory"
	@ moved, and the cast would linger. ON_TRANSITION repopulates the city
# 1130 "data/maps/CherrygroveCity/scripts.pory"
	@ and hides the cast in one go, and the warp undoes the hidefollower.
# 1131 "data/maps/CherrygroveCity/scripts.pory"
	warpsilent MAP_CHERRYGROVE_CITY, 27, 10
# 1132 "data/maps/CherrygroveCity/scripts.pory"
	waitstate
# 1133 "data/maps/CherrygroveCity/scripts.pory"
	releaseall
# 1134 "data/maps/CherrygroveCity/scripts.pory"
	end
# 1135 "data/maps/CherrygroveCity/scripts.pory"

# 1136 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_KukuiAdvance:
# 1137 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1138 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1139 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1140 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1141 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1142 "data/maps/CherrygroveCity/scripts.pory"

# 1143 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_PlayerToLine:
# 1144 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1145 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1146 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1147 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1148 "data/maps/CherrygroveCity/scripts.pory"

# 1149 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_StepDownFaceLeft:
# 1150 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1151 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1152 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1153 "data/maps/CherrygroveCity/scripts.pory"

# 1154 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Movement_AnabelToPlayer:
# 1155 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1156 "data/maps/CherrygroveCity/scripts.pory"
	walk_down
# 1157 "data/maps/CherrygroveCity/scripts.pory"
	face_left
# 1158 "data/maps/CherrygroveCity/scripts.pory"
	step_end
# 1159 "data/maps/CherrygroveCity/scripts.pory"

# 1160 "data/maps/CherrygroveCity/scripts.pory"
@ SKELETON: all dialogue below is placeholder. Rewrite in the design's voice
# 1161 "data/maps/CherrygroveCity/scripts.pory"
@ (Kukui eager and concrete but never a joke; Looker theatrical; Anabel
# 1162 "data/maps/CherrygroveCity/scripts.pory"
@ precise). See SOULGOLD_RIFT_MISSIONS_DESIGN.md section 3.1.
# 1163 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAnabelIdle:
# 1164 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: The town is in the Gym\n"
# 1165 "data/maps/CherrygroveCity/scripts.pory"
	.string "at Violet.\p"
# 1166 "data/maps/CherrygroveCity/scripts.pory"
	.string "Two buses, no argument.\p"
# 1167 "data/maps/CherrygroveCity/scripts.pory"
	.string "Speak with Looker when you're\n"
# 1168 "data/maps/CherrygroveCity/scripts.pory"
	.string "ready.$"
# 1169 "data/maps/CherrygroveCity/scripts.pory"

# 1170 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiIdle:
# 1171 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: {PLAYER}! Four days I've\n"
# 1172 "data/maps/CherrygroveCity/scripts.pory"
	.string "been out here, cousin.\p"
# 1173 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'd rather tell it once, with\n"
# 1174 "data/maps/CherrygroveCity/scripts.pory"
	.string "everyone listening.\p"
# 1175 "data/maps/CherrygroveCity/scripts.pory"
	.string "Go talk to Looker.$"
# 1176 "data/maps/CherrygroveCity/scripts.pory"

# 1177 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBLookerGreet:
# 1178 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: {PLAYER}! Over here.\p"
# 1179 "data/maps/CherrygroveCity/scripts.pory"
	.string "And watch your footing. That\n"
# 1180 "data/maps/CherrygroveCity/scripts.pory"
	.string "water is not behaving.\p"
# 1181 "data/maps/CherrygroveCity/scripts.pory"
	.string "The tear has opened twice since\n"
# 1182 "data/maps/CherrygroveCity/scripts.pory"
	.string "dawn.\p"
# 1183 "data/maps/CherrygroveCity/scripts.pory"
	.string "Both times it closed before we\n"
# 1184 "data/maps/CherrygroveCity/scripts.pory"
	.string "could reach it.$"
# 1185 "data/maps/CherrygroveCity/scripts.pory"

# 1186 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiTheory:
# 1187 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: {PLAYER}! Man, am I glad\n"
# 1188 "data/maps/CherrygroveCity/scripts.pory"
	.string "it's you.\p"
# 1189 "data/maps/CherrygroveCity/scripts.pory"
	.string "Four days on this beach, and\n"
# 1190 "data/maps/CherrygroveCity/scripts.pory"
	.string "I've finally got it.\p"
# 1191 "data/maps/CherrygroveCity/scripts.pory"
	.string "Those two work as a pair.\p"
# 1192 "data/maps/CherrygroveCity/scripts.pory"
	.string "The bright one goes first. It\n"
# 1193 "data/maps/CherrygroveCity/scripts.pory"
	.string "flashes, everybody looks…\p"
# 1194 "data/maps/CherrygroveCity/scripts.pory"
	.string "…and nobody sees the big one\n"
# 1195 "data/maps/CherrygroveCity/scripts.pory"
	.string "walking in behind it.\p"
# 1196 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: Professor. Four days.\n"
# 1197 "data/maps/CherrygroveCity/scripts.pory"
	.string "On a beach.\p"
# 1198 "data/maps/CherrygroveCity/scripts.pory"
	.string "Under a hole in the sky.\p"
# 1199 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Yeah. And if it opened\n"
# 1200 "data/maps/CherrygroveCity/scripts.pory"
	.string "with nobody watching, who tells\l"
# 1201 "data/maps/CherrygroveCity/scripts.pory"
	.string "this town when to run?\p"
# 1202 "data/maps/CherrygroveCity/scripts.pory"
	.string "I stayed so somebody would\n"
# 1203 "data/maps/CherrygroveCity/scripts.pory"
	.string "know.\p"
# 1204 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: He called the second\n"
# 1205 "data/maps/CherrygroveCity/scripts.pory"
	.string "opening eleven minutes early.\p"
# 1206 "data/maps/CherrygroveCity/scripts.pory"
	.string "He's earned the beach.\p"
# 1207 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: So here's the play.\p"
# 1208 "data/maps/CherrygroveCity/scripts.pory"
	.string "One of us takes the bright\n"
# 1209 "data/maps/CherrygroveCity/scripts.pory"
	.string "one's eyes, the other takes\l"
# 1210 "data/maps/CherrygroveCity/scripts.pory"
	.string "the wall.\p"
# 1211 "data/maps/CherrygroveCity/scripts.pory"
	.string "Split them up and neither one\n"
# 1212 "data/maps/CherrygroveCity/scripts.pory"
	.string "gets to hide.$"
# 1213 "data/maps/CherrygroveCity/scripts.pory"

# 1214 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBReady:
# 1215 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: One warning, {PLAYER}.\p"
# 1216 "data/maps/CherrygroveCity/scripts.pory"
	.string "These two are worse than\n"
# 1217 "data/maps/CherrygroveCity/scripts.pory"
	.string "Mahogany.\p"
# 1218 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: Bring everything you\n"
# 1219 "data/maps/CherrygroveCity/scripts.pory"
	.string "have.\p"
# 1220 "data/maps/CherrygroveCity/scripts.pory"
	.string "Are you ready?$"
# 1221 "data/maps/CherrygroveCity/scripts.pory"

# 1222 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBNotReady:
# 1223 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: Wise.\p"
# 1224 "data/maps/CherrygroveCity/scripts.pory"
	.string "The Center is open, and I am\n"
# 1225 "data/maps/CherrygroveCity/scripts.pory"
	.string "not moving from this sand.$"
# 1226 "data/maps/CherrygroveCity/scripts.pory"

# 1227 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBRiftWarning:
# 1228 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: There! The water's going\n"
# 1229 "data/maps/CherrygroveCity/scripts.pory"
	.string "flat, that's the tell!\p"
# 1230 "data/maps/CherrygroveCity/scripts.pory"
	.string "Everybody back!$"
# 1231 "data/maps/CherrygroveCity/scripts.pory"

# 1232 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAppear:
# 1233 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: Blacephalon! And that\n"
# 1234 "data/maps/CherrygroveCity/scripts.pory"
	.string "is… what is that?\p"
# 1235 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Stakataka! Whoa.\p"
# 1236 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's not one Pokémon, cousin.\p"
# 1237 "data/maps/CherrygroveCity/scripts.pory"
	.string "That's a whole crowd of them,\n"
# 1238 "data/maps/CherrygroveCity/scripts.pory"
	.string "stacked up.\p"
# 1239 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: …The sea went quiet\n"
# 1240 "data/maps/CherrygroveCity/scripts.pory"
	.string "before the readings did.\p"
# 1241 "data/maps/CherrygroveCity/scripts.pory"
	.string "Again.\p"
# 1242 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: Later. Not now.$"
# 1243 "data/maps/CherrygroveCity/scripts.pory"

# 1244 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBChoosePrompt:
# 1245 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Call it, {PLAYER}!\n"
# 1246 "data/maps/CherrygroveCity/scripts.pory"
	.string "Which one do you want?\p"
# 1247 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll take whatever's left, and\n"
# 1248 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll keep it looking at me.$"
# 1249 "data/maps/CherrygroveCity/scripts.pory"

# 1250 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_ChoiceBlacephalon:
# 1251 "data/maps/CherrygroveCity/scripts.pory"
	.string "Blacephalon$"
# 1252 "data/maps/CherrygroveCity/scripts.pory"

# 1253 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_ChoiceStakataka:
# 1254 "data/maps/CherrygroveCity/scripts.pory"
	.string "Stakataka$"
# 1255 "data/maps/CherrygroveCity/scripts.pory"

# 1256 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPickedBlacephalon:
# 1257 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: The bright one's yours!\p"
# 1258 "data/maps/CherrygroveCity/scripts.pory"
	.string "Don't watch the lights, watch\n"
# 1259 "data/maps/CherrygroveCity/scripts.pory"
	.string "its feet!\p"
# 1260 "data/maps/CherrygroveCity/scripts.pory"
	.string "I've got the wall. Come on, big\n"
# 1261 "data/maps/CherrygroveCity/scripts.pory"
	.string "guy, over here!$"
# 1262 "data/maps/CherrygroveCity/scripts.pory"

# 1263 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBPickedStakataka:
# 1264 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: The wall is yours!\p"
# 1265 "data/maps/CherrygroveCity/scripts.pory"
	.string "Get under it before it\n"
# 1266 "data/maps/CherrygroveCity/scripts.pory"
	.string "settles!\p"
# 1267 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'll keep the fireworks busy.\n"
# 1268 "data/maps/CherrygroveCity/scripts.pory"
	.string "Let's go!$"
# 1269 "data/maps/CherrygroveCity/scripts.pory"

# 1270 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBGotAway:
# 1271 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: They closed ranks\n"
# 1272 "data/maps/CherrygroveCity/scripts.pory"
	.string "again.\p"
# 1273 "data/maps/CherrygroveCity/scripts.pory"
	.string "We are back where we started.\p"
# 1274 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Then we go again.\p"
# 1275 "data/maps/CherrygroveCity/scripts.pory"
	.string "I'm not leaving this beach\n"
# 1276 "data/maps/CherrygroveCity/scripts.pory"
	.string "either.$"
# 1277 "data/maps/CherrygroveCity/scripts.pory"

# 1278 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiFoughtStakataka:
# 1279 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Stakataka never got a\n"
# 1280 "data/maps/CherrygroveCity/scripts.pory"
	.string "step in.\p"
# 1281 "data/maps/CherrygroveCity/scripts.pory"
	.string "Turns out if you stay right in\n"
# 1282 "data/maps/CherrygroveCity/scripts.pory"
	.string "front of it, it has to keep\l"
# 1283 "data/maps/CherrygroveCity/scripts.pory"
	.string "deciding.$"
# 1284 "data/maps/CherrygroveCity/scripts.pory"

# 1285 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBKukuiFoughtBlacephalon:
# 1286 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: The bright one kept\n"
# 1287 "data/maps/CherrygroveCity/scripts.pory"
	.string "flashing at me, and I kept not\l"
# 1288 "data/maps/CherrygroveCity/scripts.pory"
	.string "looking.\p"
# 1289 "data/maps/CherrygroveCity/scripts.pory"
	.string "It ran out of tricks.$"
# 1290 "data/maps/CherrygroveCity/scripts.pory"

# 1291 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBAfterKukui:
# 1292 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Look at the water, it's\n"
# 1293 "data/maps/CherrygroveCity/scripts.pory"
	.string "coming back.\p"
# 1294 "data/maps/CherrygroveCity/scripts.pory"
	.string "They're going home on their\n"
# 1295 "data/maps/CherrygroveCity/scripts.pory"
	.string "own.\p"
# 1296 "data/maps/CherrygroveCity/scripts.pory"
	.string "Four days out here for eleven\n"
# 1297 "data/maps/CherrygroveCity/scripts.pory"
	.string "minutes of that.\p"
# 1298 "data/maps/CherrygroveCity/scripts.pory"
	.string "Worth every one of them.$"
# 1299 "data/maps/CherrygroveCity/scripts.pory"

# 1300 "data/maps/CherrygroveCity/scripts.pory"
@ The hook for Rift Mission 4: New Bark Town, three signatures, Lusamine.
# 1301 "data/maps/CherrygroveCity/scripts.pory"
CherrygroveCity_Text_UBHook:
# 1302 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: Professor, you will now\n"
# 1303 "data/maps/CherrygroveCity/scripts.pory"
	.string "come off this beach and eat\l"
# 1304 "data/maps/CherrygroveCity/scripts.pory"
	.string "something.\p"
# 1305 "data/maps/CherrygroveCity/scripts.pory"
	.string "That is not a request.\p"
# 1306 "data/maps/CherrygroveCity/scripts.pory"
	.string "Kukui: Yeah, yeah.\p"
# 1307 "data/maps/CherrygroveCity/scripts.pory"
	.string "…{PLAYER}. That thing about\n"
# 1308 "data/maps/CherrygroveCity/scripts.pory"
	.string "watching their feet?\p"
# 1309 "data/maps/CherrygroveCity/scripts.pory"
	.string "Write it down. Somebody's going\n"
# 1310 "data/maps/CherrygroveCity/scripts.pory"
	.string "to need it.\p"
# 1311 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: Looker. The next reading\n"
# 1312 "data/maps/CherrygroveCity/scripts.pory"
	.string "came in while we were out\l"
# 1313 "data/maps/CherrygroveCity/scripts.pory"
	.string "there.\p"
# 1314 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: New Bark Town.\n"
# 1315 "data/maps/CherrygroveCity/scripts.pory"
	.string "Three signatures this time.\p"
# 1316 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: Three. In the town\n"
# 1317 "data/maps/CherrygroveCity/scripts.pory"
	.string "where {PLAYER} started.\p"
# 1318 "data/maps/CherrygroveCity/scripts.pory"
	.string "Anabel: And there is a woman\n"
# 1319 "data/maps/CherrygroveCity/scripts.pory"
	.string "already waiting on the road in.\p"
# 1320 "data/maps/CherrygroveCity/scripts.pory"
	.string "She gave us a name.\p"
# 1321 "data/maps/CherrygroveCity/scripts.pory"
	.string "Looker: …Lusamine.\p"
# 1322 "data/maps/CherrygroveCity/scripts.pory"
	.string "Come back to the house in\n"
# 1323 "data/maps/CherrygroveCity/scripts.pory"
	.string "Olivine, {PLAYER}.\p"
# 1324 "data/maps/CherrygroveCity/scripts.pory"
	.string "We are not sending you into\n"
# 1325 "data/maps/CherrygroveCity/scripts.pory"
	.string "that one blind.$"

Cherrygrove_FadedSign_Text_0:
# 585 "data/maps/CherrygroveCity/scripts.pory"
	.string "Cherrygrove inn...\n"
	.string "The text is too faded to read.$"

Cherrygrove_DarkraiEventDoor_Text_0:
# 592 "data/maps/CherrygroveCity/scripts.pory"
	.string "Darkrai might be residing in this \n"
	.string "old inn.\p"
	.string "It would be best to prepare for\n"
	.string "anything.$"

Cherrygrove_DarkraiEventDoor_Text_1:
# 599 "data/maps/CherrygroveCity/scripts.pory"
	.string "You should also bring Cresselia with \n"
	.string "you.$"

Cherrygrove_DarkraiEventDoor_Text_2:
# 604 "data/maps/CherrygroveCity/scripts.pory"
	.string "Are you absolutely sure you are ready?$"

Cherrygrove_DarkraiEventDoor_Text_3:
# 605 "data/maps/CherrygroveCity/scripts.pory"
	.string "Prepare first$"

Cherrygrove_DarkraiEventDoor_Text_4:
# 605 "data/maps/CherrygroveCity/scripts.pory"
	.string "Go in$"

Cherrygrove_DarkraiEventDoor_Text_5:
# 607 "data/maps/CherrygroveCity/scripts.pory"
	.string "You grab the door handle and-$"

Cherrygrove_DarkraiEventDoor_Text_6:
# 617 "data/maps/CherrygroveCity/scripts.pory"
	.string "Best to prepare first.$"

Cherrygrove_DarkraiEventDoor_Text_7:
# 623 "data/maps/CherrygroveCity/scripts.pory"
	.string "The door won't budge. It seems\n"
	.string "to be stuck.$"

Cherrygrove_Littlegirl_Text_0:
# 634 "data/maps/CherrygroveCity/scripts.pory"
	.string "I saw you dozing off in front of the\n"
	.string "old inn's door. Are you okay?$"

Cherrygrove_Littlegirl_Text_1:
# 639 "data/maps/CherrygroveCity/scripts.pory"
	.string "That inn... I don't think it\n"
	.string "has ever been open. My mom said it was\l"
	.string "abandoned even in her youth.$"

Cherrygrove_Zigzagoon_Text_0:
# 650 "data/maps/CherrygroveCity/scripts.pory"
	.string "Zig!$"

Cherrygrove_Rattata_Text_0:
# 659 "data/maps/CherrygroveCity/scripts.pory"
	.string "Rat!$"

Cherrygrove_TraderNoRoom_Text_0:
# 668 "data/maps/CherrygroveCity/scripts.pory"
	.string "Whoa, hold on there!\p"
	.string "Your team is full, and your storage\n"
	.string "boxes are full too.\p"
	.string "There's nowhere for either of these\n"
	.string "two to go, and I'm not handing one\l"
	.string "over just to have it disappear.\p"
	.string "Make some room and come find me.\n"
	.string "I'll be right here!$"

Cherrygrove_FriendlyTrader_Text_0:
# 687 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hi! Has my Pokémon been helpful?$"

Cherrygrove_FriendlyTrader_Text_1:
# 704 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hello! Are you a new trainer per chance?\p"
	.string "Listen, I received two exotic Pokémon\n"
	.string "as a gift from my uncle in the Safari\l"
	.string "Zone, but I can't keep both. \p"
	.string "Would you be willing to take one of \n"
	.string "them with you?\p"
	.string "I'm sure either one would love to go on\n"
	.string "an adventure with you!$"

Cherrygrove_FriendlyTrader_Text_2:
# 715 "data/maps/CherrygroveCity/scripts.pory"
	.string "Zigzagoon$"

Cherrygrove_FriendlyTrader_Text_3:
# 715 "data/maps/CherrygroveCity/scripts.pory"
	.string "Rattata$"

Cherrygrove_FriendlyTrader_Text_4:
# 715 "data/maps/CherrygroveCity/scripts.pory"
	.string "No thanks$"

Cherrygrove_FriendlyTrader_Text_5:
# 743 "data/maps/CherrygroveCity/scripts.pory"
	.string "Take good care of my {STR_VAR_1}!\p"
	.string "Say hi to my uncle, Baoba if you are\n"
	.string "ever visiting the Safari Zone!$"

Cherrygrove_FriendlyTrader_Text_6:
# 782 "data/maps/CherrygroveCity/scripts.pory"
	.string "Oh... That's a shame...$"

Cherrygrove_FriendlyTrader_Text_7:
# 787 "data/maps/CherrygroveCity/scripts.pory"
	.string "Hey! Can I ask you a favour? \p"
	.string "Wait... You don't have any\n"
	.string "Poké Balls...\p"
	.string "Sorry,\n"
	.string "I thought you were a trainer.$"
