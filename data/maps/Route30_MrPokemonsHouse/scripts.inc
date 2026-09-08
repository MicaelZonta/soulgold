# 1 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 2 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 3 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 4 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Route30_MrPokemonsHouse staging notes (map-relative tile coords, 13x10 map)
# 5 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@
# 6 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@   collision grid (. = walkable, # = blocked)
# 7 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@        x 0 1 2 3 4 5 6 7 8 9 10
# 8 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=2    . . . . . . . . . .  .
# 9 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=3    . . . . . . . . . .  .
# 10 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=4    . . . # # . . . # #  .     (3-4,4-5) table   (8-9,4) computer desk
# 11 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=5    . . . # # . . . . .  .
# 12 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=6    . . . . . . . . . .  .
# 13 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=7    . . . . . . . . . .  .
# 14 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@    y=8    # . . . . . . . . .  #     door/warp at (5,8)
# 15 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@
# 16 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@   NPC home positions (map.json - do not move them there):
# 17 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@     Kukui  (7,5)   Oak (8,5)   Lillie (5,5) = chair east of the table
# 18 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@   Scene anchor positions:
# 19 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@     player (7,6)   Lillie approach stop (6,6)   Oak talk stop (8,6)
# 20 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 21 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 22 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
Route30_MrPokemonsHouse_MapScripts::
# 23 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MrPokemonHouse_OnFrame
# 24 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.byte 0
# 25 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 26 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_OnFrame::
# 27 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 1, MrPokemonHouse_EventScript_GiveEgg
# 28 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.2byte 0
# 29 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 30 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Runs while VAR_CHERRYGROVE_CITY_STATE == 1. If the player loses to Lillie the
# 31 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ battle blacks out, the script never reaches the rewards and the var stays at 1,
# 32 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ so re-entering the house respawns every NPC at its map.json tile and replays
# 33 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ the whole scene from the top.
# 34 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_GiveEgg::
# 35 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 36 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 37 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 1. Kukui (7,5) notices the player standing on the door tile (5,8) ---
# 38 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playse SE_PIN
# 39 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_KUKUI, Common_Movement_ExclamationMark
# 40 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 41 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	delay 30
# 42 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_SOUTH
# 43 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro1, MSGBOX_DEFAULT
# 44 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 45 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ (5,8) -> (5,7) -> (5,6) -> (6,6) -> (7,6), facing Kukui
# 46 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MrPokemonHouse_Movement_PlayerToProfessors
# 47 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 48 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 49 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 2. Kukui introduces himself, Oak (8,5) joins in right away ---
# 50 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro2, MSGBOX_DEFAULT
# 51 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 52 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_OAK, DIR_SOUTH
# 53 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakGreeting, MSGBOX_DEFAULT
# 54 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 55 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 56 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 3. Kukui explains the Egg, but hands nothing over yet ---
# 57 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro3, MSGBOX_DEFAULT
# 58 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 59 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 60 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 4. Kukui turns west toward Lillie's chair and introduces her ---
# 61 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_WEST
# 62 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro4, MSGBOX_DEFAULT
# 63 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro5, MSGBOX_DEFAULT
# 64 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 65 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 66 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 5. Lillie answers from the chair ---
# 67 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_LILLIE, DIR_EAST
# 68 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieAnswer, MSGBOX_DEFAULT
# 69 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 70 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 71 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 6. Lillie leaves the chair: (5,5) -> (5,6) -> (6,6), beside the player ---
# 72 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_LILLIE, MrPokemonHouse_Movement_LillieToPlayer
# 73 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 74 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 75 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 76 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 7. Lillie's challenge ---
# 77 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieIntro, MSGBOX_DEFAULT
# 78 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieVulpix, MSGBOX_DEFAULT
# 79 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 80 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 81 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 8. Oak comments on the match ---
# 82 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_OAK, DIR_SOUTH
# 83 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakBeforeBattle, MSGBOX_DEFAULT
# 84 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 85 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 86 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 9. Kukui heals the party, then the battle starts ---
# 87 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_SOUTH
# 88 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiBeforeBattle, MSGBOX_DEFAULT
# 89 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 90 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 91 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieBeforeBattle, MSGBOX_DEFAULT
# 92 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 93 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removefieldmugshot
# 94 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	trainerbattle_no_intro TRAINER_LILLIE, MrPokemonHouse_Text_LillieDefeated
# 95 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 96 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 11. Victory: Lillie, Kukui, and the Mystery Egg ---
# 97 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 98 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieAfterBattle, MSGBOX_DEFAULT
# 99 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 100 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 101 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiAfterBattle, MSGBOX_DEFAULT
# 102 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiGiveEgg, MSGBOX_DEFAULT
# 103 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 104 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	giveitem ITEM_MYSTERY_EGG
# 105 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 106 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 107 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 12. Oak steps down to (8,6) so he is next to the player at (7,6) ---
# 108 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playbgm MUS_HG_OAK, TRUE
# 109 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakToPlayer
# 110 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 111 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 112 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	createfieldmugshot MUGSHOT_OAK
# 113 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakIntro, MSGBOX_DEFAULT
# 114 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 115 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removefieldmugshot
# 116 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 117 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 118 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	message MrPokemonHouse_Text_GetDex
# 119 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitfanfare
# 120 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 121 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 122 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_DEXNAV_OBTAINED
# 123 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 124 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 13. Oak says goodbye and walks out: (8,6) -> (8,7) -> (5,7) -> (5,8) ---
# 125 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	createfieldmugshot MUGSHOT_OAK
# 126 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakParting, MSGBOX_DEFAULT
# 127 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 128 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removefieldmugshot
# 129 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_EAST
# 130 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiOakParting, MSGBOX_DEFAULT
# 131 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 132 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakLeave
# 133 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 134 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playse SE_EXIT
# 135 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeobject LOCALID_ROUTE30_OAK
# 136 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	fadedefaultbgm
# 137 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 138 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 14. Lillie leaves from where she is standing: (6,6) -> (6,7) -> (5,7) -> (5,8) ---
# 139 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 140 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieParting, MSGBOX_DEFAULT
# 141 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 142 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_LILLIE, MrPokemonHouse_Movement_LillieLeave
# 143 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 144 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playse SE_EXIT
# 145 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeobject LOCALID_ROUTE30_LILLIE
# 146 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 147 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 15. Kukui stays at (7,5), heals the party and sends the player off ---
# 148 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 149 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_SOUTH
# 150 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Heal, MSGBOX_DEFAULT
# 151 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 152 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 153 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_DependingOnYou, MSGBOX_DEFAULT
# 154 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 155 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 156 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_DELIVERED_EGG
# 157 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 4
# 158 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 159 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag FLAG_HIDE_LAB_POLICEMAN
# 160 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
# 161 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag FLAG_HIDE_SILVER_CHERRYGROVE
# 162 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
# 163 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 164 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 2
# 165 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 166 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 167 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 168 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 169 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui::
# 170 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 171 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	faceplayer
# 172 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	checkitem ITEM_RED_SCALE
# 173 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_Kukui_RedScale
# 174 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_DEFAULT
# 175 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 176 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 177 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 178 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 179 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui_RedScale::
# 180 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_GimmeTheScale, MSGBOX_YESNO
# 181 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_Kukui_RedScale_Accepted
# 182 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Disappointed, MSGBOX_DEFAULT
# 183 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 184 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 185 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 186 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 187 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui_RedScale_Accepted::
# 188 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	giveitem ITEM_FAIRYTITE
# 189 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MrPokemonHouse_EventScript_Kukui_RedScale_NoRoom
# 190 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeitem ITEM_RED_SCALE
# 191 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_ScaleAccepted, MSGBOX_DEFAULT
# 192 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 193 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 194 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 195 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 196 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui_RedScale_NoRoom::
# 197 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_ScaleBagFull, MSGBOX_DEFAULT
# 198 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 199 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 200 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 201 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 202 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Computer::
# 203 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 204 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_BrokenComputer, MSGBOX_SIGN
# 205 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 206 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 207 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 208 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Magazine::
# 209 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 210 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
# 211 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 212 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 213 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 214 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Coins::
# 215 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 216 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
# 217 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 218 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 219 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 220 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Player: door (5,8) -> (5,7) -> (5,6) -> (6,6) -> (7,6), facing Kukui at (7,5).
# 221 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ (7,6) leaves (6,6) free for Lillie and (8,6) free for Oak.
# 222 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_PlayerToProfessors:
# 223 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_up
# 224 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_up
# 225 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 226 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 227 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_up
# 228 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 229 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 230 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Lillie: chair (5,5) -> (5,6) -> (6,6), facing the player at (7,6).
# 231 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Skirts the table, whose blocked tiles are (3,4) (4,4) (3,5) (4,5).
# 232 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_LillieToPlayer:
# 233 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 234 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 235 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_right
# 236 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 237 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 238 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Oak: (8,5) -> (8,6), facing the player at (7,6).
# 239 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_OakToPlayer:
# 240 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 241 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_left
# 242 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 243 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 244 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Oak: (8,6) -> (8,7) -> (7,7) -> (6,7) -> (5,7) -> door (5,8).
# 245 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_OakLeave:
# 246 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 247 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 248 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 249 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 250 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 251 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_in_place_down
# 252 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 253 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 254 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Lillie: (6,6) -> (6,7) -> (5,7) -> door (5,8).
# 255 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_LillieLeave:
# 256 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 257 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 258 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 259 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_in_place_down
# 260 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 261 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 262 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro1:
# 263 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Alola! You're {PLAYER},\n"
# 264 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "right? Elm said you'd come!\p"
# 265 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Come in! We've got quite a\n"
# 266 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "little gathering here today.$"
# 267 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 268 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro2:
# 269 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: I'm Professor Kukui.\n"
# 270 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I study Pokémon moves in Alola!\p"
# 271 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I was traveling through Kanto\n"
# 272 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "when I heard about Johto.\p"
# 273 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Apparently, some Pokémon from\n"
# 274 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Alola have been appearing here!\p"
# 275 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I had to see that for myself.\n"
# 276 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I've been working from this house.$"
# 277 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 278 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakGreeting:
# 279 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: Ah, you must be {PLAYER}!\n"
# 280 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Elm told us you were coming.$"
# 281 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 282 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro3:
# 283 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: A couple who run a\n"
# 284 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Day-Care gave me an unusual Egg.\p"
# 285 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I contacted Elm right away.\n"
# 286 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "He knows much more about Eggs!\p"
# 287 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'd like you to take it to him.\n"
# 288 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "But first, introductions!$"
# 289 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 290 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro4:
# 291 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: And this is Lillie.\n"
# 292 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "She's visiting from Alola too!$"
# 293 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 294 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro5:
# 295 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Lillie, weren't you\n"
# 296 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "looking for a training partner?$"
# 297 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 298 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieAnswer:
# 299 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Oh! Yes, Professor.\n"
# 300 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Just a moment!$"
# 301 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 302 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieIntro:
# 303 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Yes! Though I wasn't\n"
# 304 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "expecting to meet one so soon.\p"
# 305 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "It's nice to meet you, {PLAYER}.\n"
# 306 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'm traveling with my mother.\p"
# 307 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I've started training Pokémon,\n"
# 308 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "and there's so much to learn.\p"
# 309 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Would you battle me?\n"
# 310 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Vulpix and I have been practicing!$"
# 311 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 312 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieVulpix:
# 313 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: My Vulpix is from Alola.\n"
# 314 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "That's why her fur is white.\p"
# 315 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "People here keep asking about it.\n"
# 316 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "She seems quite pleased!$"
# 317 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 318 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakBeforeBattle:
# 319 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: A battle? An excellent chance\n"
# 320 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to see how you work together!$"
# 321 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 322 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiBeforeBattle:
# 323 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Let's get your partner\n"
# 324 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "rested before we begin.\p"
# 325 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You walked all the way from\n"
# 326 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Elm's lab, after all!$"
# 327 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 328 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieBeforeBattle:
# 329 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: All right, Vulpix.\n"
# 330 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Let's do this together!$"
# 331 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 332 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieDefeated:
# 333 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: We did our best, Vulpix.\n"
# 334 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Thank you!$"
# 335 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 336 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieAfterBattle:
# 337 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Oh! You changed your\n"
# 338 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "approach before I noticed.\p"
# 339 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I was so busy thinking about\n"
# 340 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "our next move…\p"
# 341 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I need to watch our opponent\n"
# 342 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "more carefully too.\p"
# 343 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Thank you, {PLAYER}.\n"
# 344 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'm glad I asked!$"
# 345 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 346 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiAfterBattle:
# 347 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: There's a lesson you\n"
# 348 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "won't find in a notebook!\p"
# 349 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Knowing a move is one thing.\n"
# 350 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Finding its moment takes practice.\p"
# 351 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You both gave your partners\n"
# 352 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "something to be proud of!$"
# 353 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 354 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieRematch:
# 355 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Shall we try again?\n"
# 356 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "We'll be ready when you are.$"
# 357 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 358 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiGiveEgg:
# 359 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Now, about Elm's errand!\p"
# 360 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Please take this Egg to him.\n"
# 361 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'd like to hear what he thinks.$"
# 362 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 363 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakIntro:
# 364 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: That was worth staying for!\p"
# 365 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I came to hear Kukui's findings,\n"
# 366 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "but you've given me another idea.\p"
# 367 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You paid close attention to\n"
# 368 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "your Pokémon during that battle.\p"
# 369 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "That same care will serve you\n"
# 370 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "well on a journey of discovery.\p"
# 371 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'd like you to take a Pokédex.\p"
# 372 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "It records the Pokémon you see\n"
# 373 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "and catch during your travels.\p"
# 374 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You can look up their habitats,\n"
# 375 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "evolutions, and moves as well.\p"
# 376 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Johto still has surprises for us.\n"
# 377 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Help us discover them!$"
# 378 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 379 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_GetDex:
# 380 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "{PLAYER} received the Pokédex!$"
# 381 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 382 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakParting:
# 383 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: Take your time to observe\n"
# 384 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "the Pokémon you meet, {PLAYER}.\p"
# 385 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Even a familiar species may\n"
# 386 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "have something new to teach you!\p"
# 387 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Now I must leave for Goldenrod.\n"
# 388 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "My radio audience is waiting!\p"
# 389 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui, keep those notes coming.\n"
# 390 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "And good luck to both of you!$"
# 391 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 392 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiOakParting:
# 393 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Count on it, Professor!\n"
# 394 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Have a good trip!$"
# 395 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 396 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieParting:
# 397 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: I should be going too.\n"
# 398 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "My mother is waiting for me.\p"
# 399 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I told her I'd only stop by\n"
# 400 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to see Professor Kukui.\p"
# 401 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Now I have a battle to tell\n"
# 402 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "her about!\p"
# 403 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Let's meet again, {PLAYER}.\n"
# 404 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "We'll have more to show you then.\p"
# 405 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Come along, Vulpix!$"
# 406 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 407 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Heal:
# 408 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Before you head out,\n"
# 409 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "let me take care of your Pokémon.\p"
# 410 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A good rest is part of\n"
# 411 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "good training!$"
# 412 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 413 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_DependingOnYou:
# 414 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: I'll stay here and\n"
# 415 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "keep working on my research.\p"
# 416 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Give Elm my regards!\n"
# 417 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "And drop by whenever you like.$"
# 418 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 419 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_AlwaysNewDiscoveries:
# 420 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Alola, {PLAYER}!\n"
# 421 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "How's the journey going?\p"
# 422 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I've been comparing Pokémon\n"
# 423 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "from Johto with those back home.\p"
# 424 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Different surroundings can mean\n"
# 425 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "a very different way of living.\p"
# 426 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Sometimes even a different type!\n"
# 427 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "There's always more to learn.$"
# 428 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 429 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_GimmeTheScale:
# 430 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Hold on. That red scale…\n"
# 431 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Did it come from a Gyarados?\p"
# 432 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Now that's something I'd love\n"
# 433 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to examine up close!\p"
# 434 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Would you trade it for a\n"
# 435 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Mega Stone Oak left with me?\p"
# 436 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You could put it to good use,\n"
# 437 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "and I could study that scale!$"
# 438 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 439 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Disappointed:
# 440 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: No problem!\n"
# 441 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "It's quite a keepsake.\p"
# 442 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "If you change your mind,\n"
# 443 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "you know where to find me!$"
# 444 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 445 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_ScaleAccepted:
# 446 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Thanks, {PLAYER}!\n"
# 447 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'll take good care of it.\p"
# 448 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A whole research project,\n"
# 449 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "right in the palm of my hand!$"
# 450 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 451 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_ScaleBagFull:
# 452 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Make room for the stone\n"
# 453 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "first, and we'll make the trade.\p"
# 454 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Keep your scale until then!$"
# 455 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 456 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_ForeignMagazines:
# 457 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Research journals from Alola\n"
# 458 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "cover the shelves.\p"
# 459 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "One article compares Vulpix\n"
# 460 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "from different regions.\p"
# 461 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui has filled the margins\n"
# 462 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "with handwritten questions.$"
# 463 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 464 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_BrokenComputer:
# 465 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A computer displays a map\n"
# 466 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "of Johto beside a map of Alola.\p"
# 467 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "An unfinished report is open:\n"
# 468 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "“Regional Forms in Johto.”\p"
# 469 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "There are more questions\n"
# 470 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "than answers so far.$"
# 471 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 472 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_StrangeCoins:
# 473 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A collection of travel souvenirs\n"
# 474 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "is spread across the table.\p"
# 475 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Tickets, coins, and a photograph\n"
# 476 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "of a beach in Alola.$"
