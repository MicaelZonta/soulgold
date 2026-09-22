# 1 "data/maps/OlivineCity/scripts.pory"

# 2 "data/maps/OlivineCity/scripts.pory"

# 3 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScripts::
# 4 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_MapScript_OnTransition
# 5 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 6 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_OnFrame
# 7 "data/maps/OlivineCity/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, OlivineCity_OnLoad
# 8 "data/maps/OlivineCity/scripts.pory"
	.byte 0
# 9 "data/maps/OlivineCity/scripts.pory"

# 10 "data/maps/OlivineCity/scripts.pory"
OlivineCity_OnLoad::
# 11 "data/maps/OlivineCity/scripts.pory"
	setrespawn HEAL_LOCATION_OLIVINE_CITY
# 12 "data/maps/OlivineCity/scripts.pory"
	end
# 13 "data/maps/OlivineCity/scripts.pory"

# 14 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScript_OnTransition::
# 15 "data/maps/OlivineCity/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 16 "data/maps/OlivineCity/scripts.pory"
	call OlivineCity_EventScript_SetupSilverDoor
# 17 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_OLIVINE_CITY_STATE, 0, OlivineCity_EventScript_InitCity
# 18 "data/maps/OlivineCity/scripts.pory"
	goto OlivineCity_MapScript_CheckWeather
# 19 "data/maps/OlivineCity/scripts.pory"

# 20 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScript_CheckWeather::
# 21 "data/maps/OlivineCity/scripts.pory"
	callnative SetTimeBasedEncounters
# 22 "data/maps/OlivineCity/scripts.pory"
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
# 23 "data/maps/OlivineCity/scripts.pory"
	end
# 24 "data/maps/OlivineCity/scripts.pory"

# 25 "data/maps/OlivineCity/scripts.pory"
OlivineCity_MapScript_ClearWeather::
# 26 "data/maps/OlivineCity/scripts.pory"
	setweather WEATHER_NONE
# 27 "data/maps/OlivineCity/scripts.pory"
	end
# 28 "data/maps/OlivineCity/scripts.pory"

# 29 "data/maps/OlivineCity/scripts.pory"
OlivineCity_OnFrame::
# 30 "data/maps/OlivineCity/scripts.pory"
	map_script_2 VAR_SAFARI_ZONE_GATE_STATE, 1, OlivineCity_EventScript_BaobaCall
# 31 "data/maps/OlivineCity/scripts.pory"
	.2byte 0
# 32 "data/maps/OlivineCity/scripts.pory"

# 33 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_BaobaCall::
# 34 "data/maps/OlivineCity/scripts.pory"
	lock
# 35 "data/maps/OlivineCity/scripts.pory"
	pokenavcall OlivineCity_Text_Baoba
# 36 "data/maps/OlivineCity/scripts.pory"
	waitmessage
# 37 "data/maps/OlivineCity/scripts.pory"
	delay 30
# 38 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_SAFARI_ZONE_GATE_STATE, 2
# 39 "data/maps/OlivineCity/scripts.pory"
	release
# 40 "data/maps/OlivineCity/scripts.pory"
	end
# 41 "data/maps/OlivineCity/scripts.pory"

# 42 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Baoba:
# 43 "data/maps/OlivineCity/scripts.pory"
	.string "{PLAYER}!\p"
# 44 "data/maps/OlivineCity/scripts.pory"
	.string "This is Warden Baoba.\p"
# 45 "data/maps/OlivineCity/scripts.pory"
	.string "Sorry to have kept you waiting.\n"
# 46 "data/maps/OlivineCity/scripts.pory"
	.string "We've finally opened the Safari\l"
# 47 "data/maps/OlivineCity/scripts.pory"
	.string "Zone!\p"
# 48 "data/maps/OlivineCity/scripts.pory"
	.string "Do you know where it is?\p"
# 49 "data/maps/OlivineCity/scripts.pory"
	.string "You know the Gate inside the cavern\n"
# 50 "data/maps/OlivineCity/scripts.pory"
	.string "in Cianwood City?\p"
# 51 "data/maps/OlivineCity/scripts.pory"
	.string "If you go through there and walk for\n"
# 52 "data/maps/OlivineCity/scripts.pory"
	.string "a short while, you should soon see\l"
# 53 "data/maps/OlivineCity/scripts.pory"
	.string "the Safari Zone!\p"
# 54 "data/maps/OlivineCity/scripts.pory"
	.string "We're a little out of the way, but\n"
# 55 "data/maps/OlivineCity/scripts.pory"
	.string "please come visit!$"
# 56 "data/maps/OlivineCity/scripts.pory"

# 57 "data/maps/OlivineCity/scripts.pory"
@ Route39's entry trigger (VAR_OLIVINE_CITY_STATE == 0).
# 58 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_CityTrigger::
# 59 "data/maps/OlivineCity/scripts.pory"
	call OlivineCity_EventScript_InitCity
# 60 "data/maps/OlivineCity/scripts.pory"
	end
# 61 "data/maps/OlivineCity/scripts.pory"

# 62 "data/maps/OlivineCity/scripts.pory"
@ First-arrival setup of Olivine and Cianwood. Called from the Route39 trigger
# 63 "data/maps/OlivineCity/scripts.pory"
@ and from OnTransition, so arriving by any route (GoldenrodShore, Surf, Fly)
# 64 "data/maps/OlivineCity/scripts.pory"
@ sets the city up the same way. Flags/vars only: safe before the spawn. Must
# 65 "data/maps/OlivineCity/scripts.pory"
@ end in return, not end, or OnTransition would stop before the weather check.
# 66 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_InitCity:: @FLAGHEAP
# 67 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
# 68 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_VISITED_OLIVINE_CITY
# 69 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_BATTLEFRONTIER_ENGINEER
# 70 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_LIGHTHOUSE_JASMINE
# 71 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
# 72 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_GETFLY, 0
# 73 "data/maps/OlivineCity/scripts.pory"
	
# 74 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_OLIVINE_CITY_STATE, 1
# 75 "data/maps/OlivineCity/scripts.pory"

# 76 "data/maps/OlivineCity/scripts.pory"
	@cianwood flags
# 77 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_SUICUNE_ENCOUNTERS, 1
# 78 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
# 79 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_CIANWOOD_EUSINE
# 80 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_CIANWOOD_CITY_STATE, 1
# 81 "data/maps/OlivineCity/scripts.pory"
	return
# 82 "data/maps/OlivineCity/scripts.pory"

# 83 "data/maps/OlivineCity/scripts.pory"
@ Silver's gym-door scene plays by default, from the very start of the game,
# 84 "data/maps/OlivineCity/scripts.pory"
@ until it has been seen once: FLAG_HIDE_OLIVINE_SILVER means "scene done".
# 85 "data/maps/OlivineCity/scripts.pory"
@ The Silver object itself is hidden by FLAG_TEMP_1 (reset on every load, set
# 86 "data/maps/OlivineCity/scripts.pory"
@ here before the spawn) and only appears while the scene runs. VAR_TEMP_2 is
# 87 "data/maps/OlivineCity/scripts.pory"
@ the coord trigger's var: 0 = armed, 1 = scene done or already running.
# 88 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SetupSilverDoor::
# 89 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_TEMP_1
# 90 "data/maps/OlivineCity/scripts.pory"
	goto_if_unset FLAG_HIDE_OLIVINE_SILVER, OlivineCity_EventScript_SetupSilverDoorEnd
# 91 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_TEMP_2, 1
# 92 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SetupSilverDoorEnd::
# 93 "data/maps/OlivineCity/scripts.pory"
	return
# 94 "data/maps/OlivineCity/scripts.pory"

# 95 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverTrigger::
# 96 "data/maps/OlivineCity/scripts.pory"
	lock
# 97 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_TEMP_2, 1
# 98 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_TEMP_1
# 99 "data/maps/OlivineCity/scripts.pory"
	opendoor 11, 27
# 100 "data/maps/OlivineCity/scripts.pory"
	addobject LOCALID_OLIVINE_SILVER
# 101 "data/maps/OlivineCity/scripts.pory"
	playbgm MUS_HG_ENCOUNTER_RIVAL, TRUE
# 102 "data/maps/OlivineCity/scripts.pory"
	delay 20 
# 103 "data/maps/OlivineCity/scripts.pory"
	closedoor 11, 27
# 104 "data/maps/OlivineCity/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 105 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverWalkToPlayer1
# 106 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverWalkToPlayer2
# 107 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverWalkToPlayer3
# 108 "data/maps/OlivineCity/scripts.pory"
	createfieldmugshot MUGSHOT_SILVER
# 109 "data/maps/OlivineCity/scripts.pory"
	call_if_unset FLAG_AMPHAROS_HEALED, OlivineCity_EventScript_SilverTalkAmpharosSick
# 110 "data/maps/OlivineCity/scripts.pory"
	call_if_set FLAG_AMPHAROS_HEALED, OlivineCity_EventScript_SilverTalkAmpharosHealed
# 111 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 112 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 28, OlivineCity_EventScript_SilverLeaveAdjust1
# 113 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 29, OlivineCity_EventScript_SilverLeaveAdjust2
# 114 "data/maps/OlivineCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 30, OlivineCity_EventScript_SilverLeaveAdjust2
# 115 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER, OlivineCity_Movement_SilverLeave
# 116 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 117 "data/maps/OlivineCity/scripts.pory"
	call_if_lt VAR_OLIVINE_CITY_STATE, 2, OlivineCity_EventScript_SilverSetClimbLighthouse
# 118 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_SILVER
# 119 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_MAREANIES
# 120 "data/maps/OlivineCity/scripts.pory"
	removeobject LOCALID_OLIVINE_SILVER
# 121 "data/maps/OlivineCity/scripts.pory"
	fadedefaultbgm
# 122 "data/maps/OlivineCity/scripts.pory"
	release
# 123 "data/maps/OlivineCity/scripts.pory"
	end
# 124 "data/maps/OlivineCity/scripts.pory"

# 125 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverTalkAmpharosSick::
# 126 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_SilverEncounter, MSGBOX_DEFAULT
# 127 "data/maps/OlivineCity/scripts.pory"
	return
# 128 "data/maps/OlivineCity/scripts.pory"

# 129 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverTalkAmpharosHealed::
# 130 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_SilverEncounterGymBeaten, MSGBOX_DEFAULT
# 131 "data/maps/OlivineCity/scripts.pory"
	return
# 132 "data/maps/OlivineCity/scripts.pory"

# 133 "data/maps/OlivineCity/scripts.pory"
@ Never lowers the var: the scene can now play after the Lighthouse arc.
# 134 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverSetClimbLighthouse::
# 135 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_OLIVINE_CITY_STATE, 2
# 136 "data/maps/OlivineCity/scripts.pory"
	return
# 137 "data/maps/OlivineCity/scripts.pory"

# 138 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverWalkToPlayer1::
# 139 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer1
# 140 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 141 "data/maps/OlivineCity/scripts.pory"
	return
# 142 "data/maps/OlivineCity/scripts.pory"

# 143 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverWalkToPlayer2::
# 144 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer2
# 145 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 146 "data/maps/OlivineCity/scripts.pory"
	return
# 147 "data/maps/OlivineCity/scripts.pory"

# 148 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverWalkToPlayer3::
# 149 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER OlivineCity_Movement_SilverWalkToPlayer3
# 150 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 151 "data/maps/OlivineCity/scripts.pory"
	return
# 152 "data/maps/OlivineCity/scripts.pory"

# 153 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverLeaveAdjust1::
# 154 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkDown1
# 155 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 156 "data/maps/OlivineCity/scripts.pory"
	return
# 157 "data/maps/OlivineCity/scripts.pory"

# 158 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_SilverLeaveAdjust2::
# 159 "data/maps/OlivineCity/scripts.pory"
	applymovement LOCALID_OLIVINE_SILVER Common_Movement_WalkUp1
# 160 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 161 "data/maps/OlivineCity/scripts.pory"
	return
# 162 "data/maps/OlivineCity/scripts.pory"

# 163 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverWalkToPlayer1:
# 164 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 165 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 166 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 167 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 168 "data/maps/OlivineCity/scripts.pory"
	step_end
# 169 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverWalkToPlayer2:
# 170 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 171 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 172 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 173 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 174 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 175 "data/maps/OlivineCity/scripts.pory"
	step_end
# 176 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverWalkToPlayer3:
# 177 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 178 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 179 "data/maps/OlivineCity/scripts.pory"
	walk_down
# 180 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 181 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 182 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 183 "data/maps/OlivineCity/scripts.pory"
	step_end
# 184 "data/maps/OlivineCity/scripts.pory"

# 185 "data/maps/OlivineCity/scripts.pory"

# 186 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Movement_SilverLeave:
# 187 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 188 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 189 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 190 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 191 "data/maps/OlivineCity/scripts.pory"
	walk_right
# 192 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 193 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 194 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 195 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 196 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 197 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 198 "data/maps/OlivineCity/scripts.pory"
	walk_up
# 199 "data/maps/OlivineCity/scripts.pory"
	step_end
# 200 "data/maps/OlivineCity/scripts.pory"

# 201 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_SilverEncounter:
# 202 "data/maps/OlivineCity/scripts.pory"
	.string "You again?\n"
# 203 "data/maps/OlivineCity/scripts.pory"
	.string "There's no need to be alert.\p"
# 204 "data/maps/OlivineCity/scripts.pory"
	.string "I don't bother with wimps\n"
# 205 "data/maps/OlivineCity/scripts.pory"
	.string "like you.\p"
# 206 "data/maps/OlivineCity/scripts.pory"
	.string "Speaking of weaklings, the\n"
# 207 "data/maps/OlivineCity/scripts.pory"
	.string "city's Gym Leader isn't here,\l"
# 208 "data/maps/OlivineCity/scripts.pory"
	.string "and is supposedly taking care\l"
# 209 "data/maps/OlivineCity/scripts.pory"
	.string "of a sick Pokémon at the\l"
# 210 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse.\p"
# 211 "data/maps/OlivineCity/scripts.pory"
	.string "Humph! Boo-hoo!\n"
# 212 "data/maps/OlivineCity/scripts.pory"
	.string "Just let sick Pokémon go!\p"
# 213 "data/maps/OlivineCity/scripts.pory"
	.string "A Pokémon that can't battle\n"
# 214 "data/maps/OlivineCity/scripts.pory"
	.string "is worthless!\p"
# 215 "data/maps/OlivineCity/scripts.pory"
	.string "Why don't you go train at the\n"
# 216 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse?\p"
# 217 "data/maps/OlivineCity/scripts.pory"
	.string "Who knows? It may make you a\n"
# 218 "data/maps/OlivineCity/scripts.pory"
	.string "bit of a better Trainer!$"
# 219 "data/maps/OlivineCity/scripts.pory"

# 220 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_SilverEncounterGymBeaten:
# 221 "data/maps/OlivineCity/scripts.pory"
	.string "You again?\n"
# 222 "data/maps/OlivineCity/scripts.pory"
	.string "There's no need to be alert.\p"
# 223 "data/maps/OlivineCity/scripts.pory"
	.string "I don't bother with wimps\n"
# 224 "data/maps/OlivineCity/scripts.pory"
	.string "like you.\p"
# 225 "data/maps/OlivineCity/scripts.pory"
	.string "I just beat the Gym Leader\n"
# 226 "data/maps/OlivineCity/scripts.pory"
	.string "here. Her Steel-types were\l"
# 227 "data/maps/OlivineCity/scripts.pory"
	.string "a joke.\p"
# 228 "data/maps/OlivineCity/scripts.pory"
	.string "She wasted her time babysitting\n"
# 229 "data/maps/OlivineCity/scripts.pory"
	.string "a sick Pokémon at the\l"
# 230 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse.\p"
# 231 "data/maps/OlivineCity/scripts.pory"
	.string "A Pokémon that can't battle\n"
# 232 "data/maps/OlivineCity/scripts.pory"
	.string "is worthless!\p"
# 233 "data/maps/OlivineCity/scripts.pory"
	.string "Go on, try your luck in there.\n"
# 234 "data/maps/OlivineCity/scripts.pory"
	.string "Not that it'll help a weakling!$"
# 235 "data/maps/OlivineCity/scripts.pory"

# 236 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Sailor1::
# 237 "data/maps/OlivineCity/scripts.pory"
	lock
# 238 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 239 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Sailor1, MSGBOX_DEFAULT
# 240 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 241 "data/maps/OlivineCity/scripts.pory"
	release
# 242 "data/maps/OlivineCity/scripts.pory"
	end
# 243 "data/maps/OlivineCity/scripts.pory"

# 244 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Sailor2::
# 245 "data/maps/OlivineCity/scripts.pory"
	lock
# 246 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 247 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Sailor2, MSGBOX_DEFAULT
# 248 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 249 "data/maps/OlivineCity/scripts.pory"
	release
# 250 "data/maps/OlivineCity/scripts.pory"
	end
# 251 "data/maps/OlivineCity/scripts.pory"

# 252 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Youngster::
# 253 "data/maps/OlivineCity/scripts.pory"
	lock
# 254 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 255 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_YoungsterPokegear, MSGBOX_DEFAULT
# 256 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 257 "data/maps/OlivineCity/scripts.pory"
	release
# 258 "data/maps/OlivineCity/scripts.pory"
	end
# 259 "data/maps/OlivineCity/scripts.pory"

# 260 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Machoke::
# 261 "data/maps/OlivineCity/scripts.pory"
	lock
# 262 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 263 "data/maps/OlivineCity/scripts.pory"
	waitse
# 264 "data/maps/OlivineCity/scripts.pory"
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
# 265 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Machoke, MSGBOX_DEFAULT
# 266 "data/maps/OlivineCity/scripts.pory"
	waitmoncry
# 267 "data/maps/OlivineCity/scripts.pory"
	release
# 268 "data/maps/OlivineCity/scripts.pory"
	end
# 269 "data/maps/OlivineCity/scripts.pory"

# 270 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_Sign::
# 271 "data/maps/OlivineCity/scripts.pory"
	lock
# 272 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_Sign, MSGBOX_SIGN
# 273 "data/maps/OlivineCity/scripts.pory"
	end
# 274 "data/maps/OlivineCity/scripts.pory"

# 275 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_PortSign::
# 276 "data/maps/OlivineCity/scripts.pory"
	lock
# 277 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_PortSign, MSGBOX_SIGN
# 278 "data/maps/OlivineCity/scripts.pory"
	end
# 279 "data/maps/OlivineCity/scripts.pory"

# 280 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_CafeSign::
# 281 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_CafeSign, MSGBOX_SIGN
# 282 "data/maps/OlivineCity/scripts.pory"
	end
# 283 "data/maps/OlivineCity/scripts.pory"

# 284 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_GymSign::
# 285 "data/maps/OlivineCity/scripts.pory"
	lock
# 286 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_GymSign, MSGBOX_SIGN
# 287 "data/maps/OlivineCity/scripts.pory"
	end
# 288 "data/maps/OlivineCity/scripts.pory"

# 289 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_LighthouseSign::
# 290 "data/maps/OlivineCity/scripts.pory"
	lock
# 291 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_LighthouseSign, MSGBOX_SIGN
# 292 "data/maps/OlivineCity/scripts.pory"
	end
# 293 "data/maps/OlivineCity/scripts.pory"

# 294 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_EonTicketWoman::
# 295 "data/maps/OlivineCity/scripts.pory"
	lock
# 296 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 297 "data/maps/OlivineCity/scripts.pory"
	checkitem ITEM_AURORA_TICKET
# 298 "data/maps/OlivineCity/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_EventScript_EonTicketWomanAfter
# 299 "data/maps/OlivineCity/scripts.pory"
	goto_if_set FLAG_IS_KANTO_CHAMPION, OlivineCity_EventScript_EonTicketWomanChamp
# 300 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_EonTicketWoman1, MSGBOX_DEFAULT
# 301 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 302 "data/maps/OlivineCity/scripts.pory"
	release
# 303 "data/maps/OlivineCity/scripts.pory"
	end
# 304 "data/maps/OlivineCity/scripts.pory"

# 305 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_EonTicketWomanChamp::
# 306 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_EonTicketWoman2, MSGBOX_DEFAULT
# 307 "data/maps/OlivineCity/scripts.pory"
	giveitem ITEM_AURORA_TICKET
# 308 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 309 "data/maps/OlivineCity/scripts.pory"
	release
# 310 "data/maps/OlivineCity/scripts.pory"
	end
# 311 "data/maps/OlivineCity/scripts.pory"

# 312 "data/maps/OlivineCity/scripts.pory"
OlivineCity_EventScript_EonTicketWomanAfter::
# 313 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Text_EonTicketWoman3, MSGBOX_DEFAULT
# 314 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 315 "data/maps/OlivineCity/scripts.pory"
	release
# 316 "data/maps/OlivineCity/scripts.pory"
	end
# 317 "data/maps/OlivineCity/scripts.pory"

# 318 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_CafeSign:
# 319 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine Cafe\n"
# 320 "data/maps/OlivineCity/scripts.pory"
	.string "Where Strong Sailors Enjoy\l"
# 321 "data/maps/OlivineCity/scripts.pory"
	.string "Hearty Meals Of Strength$"
# 322 "data/maps/OlivineCity/scripts.pory"

# 323 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_EonTicketWoman1:
# 324 "data/maps/OlivineCity/scripts.pory"
	.string "My name is Mary!\p"
# 325 "data/maps/OlivineCity/scripts.pory"
	.string "Just kidding, but I love Mary's\n"
# 326 "data/maps/OlivineCity/scripts.pory"
	.string "radio show!$"
# 327 "data/maps/OlivineCity/scripts.pory"

# 328 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_EonTicketWoman2:
# 329 "data/maps/OlivineCity/scripts.pory"
	.string "You must be {PLAYER}!!!\p"
# 330 "data/maps/OlivineCity/scripts.pory"
	.string "Oh my goodness! The champion!\p"
# 331 "data/maps/OlivineCity/scripts.pory"
	.string "I heard about you on Mary's\n"
# 332 "data/maps/OlivineCity/scripts.pory"
	.string "radio show!\p"
# 333 "data/maps/OlivineCity/scripts.pory"
	.string "Here, take this!$"
# 334 "data/maps/OlivineCity/scripts.pory"

# 335 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_EonTicketWoman3:
# 336 "data/maps/OlivineCity/scripts.pory"
	.string "I can't believe I met the\n"
# 337 "data/maps/OlivineCity/scripts.pory"
	.string "champion!!!$"
# 338 "data/maps/OlivineCity/scripts.pory"

# 339 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Sailor1:
# 340 "data/maps/OlivineCity/scripts.pory"
	.string "Dark roads are dangerous\n"
# 341 "data/maps/OlivineCity/scripts.pory"
	.string "at night.\p"
# 342 "data/maps/OlivineCity/scripts.pory"
	.string "But in the pitch-black of\n"
# 343 "data/maps/OlivineCity/scripts.pory"
	.string "night, the sea is even more\l"
# 344 "data/maps/OlivineCity/scripts.pory"
	.string "treacherous!\p"
# 345 "data/maps/OlivineCity/scripts.pory"
	.string "Without the beacon of the\n"
# 346 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse to guide it,\l"
# 347 "data/maps/OlivineCity/scripts.pory"
	.string "no ship can sail.$"
# 348 "data/maps/OlivineCity/scripts.pory"

# 349 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_YoungsterPokegear:
# 350 "data/maps/OlivineCity/scripts.pory"
	.string "That thing you have--\n"
# 351 "data/maps/OlivineCity/scripts.pory"
	.string "it's a Pokégear, right?\l"
# 352 "data/maps/OlivineCity/scripts.pory"
	.string "Wow, that's cool.$"
# 353 "data/maps/OlivineCity/scripts.pory"

# 354 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_YoungsterPokedex:
# 355 "data/maps/OlivineCity/scripts.pory"
	.string "Wow, you have a Pokédex!\p"
# 356 "data/maps/OlivineCity/scripts.pory"
	.string "That is just so awesome.$"
# 357 "data/maps/OlivineCity/scripts.pory"

# 358 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Sailor2:
# 359 "data/maps/OlivineCity/scripts.pory"
	.string "The league has Jasmine\n"
# 360 "data/maps/OlivineCity/scripts.pory"
	.string "pegged as the sixth\l"
# 361 "data/maps/OlivineCity/scripts.pory"
	.string "strongest Gym Leader!\p"
# 362 "data/maps/OlivineCity/scripts.pory"
	.string "Hah! That's a load of crud.\p"
# 363 "data/maps/OlivineCity/scripts.pory"
	.string "There's no way Pryce could\n"
# 364 "data/maps/OlivineCity/scripts.pory"
	.string "hurt Jasmine's Steel-type\l"
# 365 "data/maps/OlivineCity/scripts.pory"
	.string "Pokémon!\p"
# 366 "data/maps/OlivineCity/scripts.pory"
	.string "Bureaucracy if you ask me.\p"
# 367 "data/maps/OlivineCity/scripts.pory"
	.string "She's something to be feared,\n"
# 368 "data/maps/OlivineCity/scripts.pory"
	.string "that's for sure!$"
# 369 "data/maps/OlivineCity/scripts.pory"

# 370 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Sign:
# 371 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine City\p"
# 372 "data/maps/OlivineCity/scripts.pory"
	.string "The Port Closest to Foreign Lands$"
# 373 "data/maps/OlivineCity/scripts.pory"

# 374 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_PortSign:
# 375 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine Port\n"
# 376 "data/maps/OlivineCity/scripts.pory"
	.string "Fast Ship Pier$"
# 377 "data/maps/OlivineCity/scripts.pory"

# 378 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_GymSign:
# 379 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine City Pokémon Gym\n"
# 380 "data/maps/OlivineCity/scripts.pory"
	.string "Leader: Jasmine\p"
# 381 "data/maps/OlivineCity/scripts.pory"
	.string "The Steel-Clad Defense Girl$"
# 382 "data/maps/OlivineCity/scripts.pory"

# 383 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_LighthouseSign:
# 384 "data/maps/OlivineCity/scripts.pory"
	.string "Olivine Lighthouse\n"
# 385 "data/maps/OlivineCity/scripts.pory"
	.string "Also known as the Glitter\l"
# 386 "data/maps/OlivineCity/scripts.pory"
	.string "Lighthouse$"
# 387 "data/maps/OlivineCity/scripts.pory"

# 388 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_BattleTowerSign:
# 389 "data/maps/OlivineCity/scripts.pory"
	.string "Battle Tower Ahead\n"
# 390 "data/maps/OlivineCity/scripts.pory"
	.string "Opening Now!$"
# 391 "data/maps/OlivineCity/scripts.pory"

# 392 "data/maps/OlivineCity/scripts.pory"
OlivineCity_Text_Machoke:
# 393 "data/maps/OlivineCity/scripts.pory"
	.string "Machoke: Cho!$"

OlivineCity_Littlegirl_Warf::
# 397 "data/maps/OlivineCity/scripts.pory"
	lock
# 398 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 399 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_Littlegirl_Warf_Text_0
# 401 "data/maps/OlivineCity/scripts.pory"
	release
	end


MareanieOlivine::
# 406 "data/maps/OlivineCity/scripts.pory"
	lock
# 407 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 408 "data/maps/OlivineCity/scripts.pory"
	playmoncry SPECIES_MAREANIE, CRY_MODE_NORMAL
# 409 "data/maps/OlivineCity/scripts.pory"
	msgbox MareanieOlivine_Text_0
# 410 "data/maps/OlivineCity/scripts.pory"
	waitmoncry
# 411 "data/maps/OlivineCity/scripts.pory"
	release
	end


OlivineSouvenirMart::
# 416 "data/maps/OlivineCity/scripts.pory"
	lock
# 417 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 418 "data/maps/OlivineCity/scripts.pory"
	message OlivineSouvenirMart_Text_0
# 419 "data/maps/OlivineCity/scripts.pory"
	waitmessage
# 420 "data/maps/OlivineCity/scripts.pory"
	pokemart SouvenirMart
# 421 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineSouvenirMart_Text_1
# 422 "data/maps/OlivineCity/scripts.pory"
	release
	end


	.align 2
# 426 "data/maps/OlivineCity/scripts.pory"
SouvenirMart:
# 427 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_STRANGE_SOUVENIR
# 428 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_UNREMARKABLE_TEACUP
# 429 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_MASTERPIECE_TEACUP
# 430 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_UTILITY_UMBRELLA
# 431 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_RED_NECTAR
# 432 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_YELLOW_NECTAR
# 433 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_PINK_NECTAR
# 434 "data/maps/OlivineCity/scripts.pory"
	.2byte ITEM_PURPLE_NECTAR
	.2byte ITEM_NONE

OlivineCity_RivalPier::
# 438 "data/maps/OlivineCity/scripts.pory"
	lock
# 439 "data/maps/OlivineCity/scripts.pory"
	faceplayer
# 440 "data/maps/OlivineCity/scripts.pory"
	createfieldmugshotrival
# 441 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_0
# 443 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_1
# 445 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_2
# 447 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_3
# 449 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_4
# 451 "data/maps/OlivineCity/scripts.pory"
	msgbox OlivineCity_RivalPier_Text_5
# 452 "data/maps/OlivineCity/scripts.pory"
	removefieldmugshot
# 453 "data/maps/OlivineCity/scripts.pory"
	closemessage
# 454 "data/maps/OlivineCity/scripts.pory"
	moveobjecttocoords LOCALID_OLIVINE_RIVAL, 19, 49, DIR_NORTH
# 455 "data/maps/OlivineCity/scripts.pory"
	waitmovement 0
# 456 "data/maps/OlivineCity/scripts.pory"
	setvar VAR_RIVAL_STATE, 9
# 457 "data/maps/OlivineCity/scripts.pory"
	setflag FLAG_HIDE_OLIVINE_RIVAL
# 458 "data/maps/OlivineCity/scripts.pory"
	removeobject LOCALID_OLIVINE_RIVAL
# 459 "data/maps/OlivineCity/scripts.pory"
	clearflag FLAG_HIDE_ICEPATH_RIVAL
# 460 "data/maps/OlivineCity/scripts.pory"
	release
	end


OlivineCity_Littlegirl_Warf_Text_0:
# 399 "data/maps/OlivineCity/scripts.pory"
	.string "I'm feeding the Mareanie every day!\n"
	.string "They sometimes let me play with them!$"

MareanieOlivine_Text_0:
# 409 "data/maps/OlivineCity/scripts.pory"
	.string "Maree!$"

OlivineSouvenirMart_Text_0:
# 418 "data/maps/OlivineCity/scripts.pory"
	.string "Welcome! How may I help you?$"

OlivineSouvenirMart_Text_1:
# 421 "data/maps/OlivineCity/scripts.pory"
	.string "Come back soon!$"

OlivineCity_RivalPier_Text_0:
# 441 "data/maps/OlivineCity/scripts.pory"
	.string "Oh. \n"
	.string "Hey...$"

OlivineCity_RivalPier_Text_1:
# 443 "data/maps/OlivineCity/scripts.pory"
	.string "Do you ever think that some people are\n"
	.string "just not... built for this?$"

OlivineCity_RivalPier_Text_2:
# 445 "data/maps/OlivineCity/scripts.pory"
	.string "Like it comes naturally\n"
	.string "and for others it's just...$"

OlivineCity_RivalPier_Text_3:
# 447 "data/maps/OlivineCity/scripts.pory"
	.string "Never mind.\n"
	.string "It's a dumb question.$"

OlivineCity_RivalPier_Text_4:
# 449 "data/maps/OlivineCity/scripts.pory"
	.string "Jasmine's Gym is closed.\n"
	.string "You're already on it, I assume.$"

OlivineCity_RivalPier_Text_5:
# 451 "data/maps/OlivineCity/scripts.pory"
	.string "See you around.$"
