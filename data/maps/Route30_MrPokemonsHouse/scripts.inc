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
@     Vulpix (4,6) = Lillie's Alolan Vulpix, out of its Poké Ball
# 19 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@   Scene anchor positions:
# 20 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@     player (7,6)   Lillie approach stop (6,6)   Oak talk stop (8,6)
# 21 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@     Vulpix stop (5,6), right behind Lillie
# 22 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@
# 23 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Per-visit scratch state (VAR_TEMP_* is cleared on every warp):
# 24 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@   VAR_TEMP_3 - battle outcome, copied right after GetBattleOutcome
# 25 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@   VAR_TEMP_5 - previous state of B_FLAG_NO_WHITEOUT
# 26 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 27 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 28 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
Route30_MrPokemonsHouse_MapScripts::
# 29 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MrPokemonHouse_OnFrame
# 30 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.byte 0
# 31 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 32 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_OnFrame::
# 33 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 1, MrPokemonHouse_EventScript_GiveEgg
# 34 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.2byte 0
# 35 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 36 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Runs while VAR_CHERRYGROVE_CITY_STATE == 1. The battle with Lillie runs with
# 37 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ B_FLAG_NO_WHITEOUT, so winning, losing, drawing or forfeiting all continue to
# 38 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ the Mystery Egg and the Pokédex. The var only becomes 2 at the very end; a
# 39 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ reset before that replays the whole scene from the top.
# 40 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_GiveEgg::
# 41 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 42 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 43 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 1. Kukui (7,5) notices the player standing on the door tile (5,8) ---
# 44 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playse SE_PIN
# 45 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_KUKUI, Common_Movement_ExclamationMark
# 46 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 47 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	delay 30
# 48 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_SOUTH
# 49 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro1, MSGBOX_DEFAULT
# 50 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 51 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ (5,8) -> (5,7) -> (5,6) -> (6,6) -> (7,6), facing Kukui
# 52 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MrPokemonHouse_Movement_PlayerToProfessors
# 53 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 54 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 55 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 2. Kukui introduces himself, Oak (8,5) joins in right away ---
# 56 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro2, MSGBOX_DEFAULT
# 57 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 58 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_OAK, DIR_SOUTH
# 59 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakGreeting, MSGBOX_DEFAULT
# 60 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 61 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 62 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 3. Kukui explains the Egg, but hands nothing over yet ---
# 63 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro3, MSGBOX_DEFAULT
# 64 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 65 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 66 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 4. Kukui turns west toward Lillie's chair and introduces her ---
# 67 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_WEST
# 68 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro4, MSGBOX_DEFAULT
# 69 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Intro5, MSGBOX_DEFAULT
# 70 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 71 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 72 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 5. Lillie answers from the chair ---
# 73 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_LILLIE, DIR_EAST
# 74 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieAnswer, MSGBOX_DEFAULT
# 75 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 76 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 77 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 6. Lillie leaves the chair: (5,5) -> (5,6) -> (6,6), beside the player ---
# 78 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ Vulpix trails one step behind: (4,6) -> (5,6), once Lillie has left it.
# 79 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_LILLIE, MrPokemonHouse_Movement_LillieToPlayer
# 80 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_VULPIX, MrPokemonHouse_Movement_VulpixToPlayer
# 81 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement LOCALID_ROUTE30_LILLIE
# 82 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement LOCALID_ROUTE30_VULPIX
# 83 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 84 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 85 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 7. Lillie's challenge ---
# 86 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieIntro, MSGBOX_DEFAULT
# 87 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieVulpix, MSGBOX_DEFAULT
# 88 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 89 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 90 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 8. Oak comments on the match ---
# 91 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_OAK, DIR_SOUTH
# 92 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakBeforeBattle, MSGBOX_DEFAULT
# 93 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 94 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 95 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 9. Kukui heals the party, then the battle starts ---
# 96 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_SOUTH
# 97 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiBeforeBattle, MSGBOX_DEFAULT
# 98 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 99 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 100 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieBeforeBattle, MSGBOX_DEFAULT
# 101 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 102 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 10. Battle without blackout: every outcome continues the scene ---
# 103 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	checkflag B_FLAG_NO_WHITEOUT
# 104 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	copyvar VAR_TEMP_5, VAR_RESULT
# 105 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag B_FLAG_NO_WHITEOUT
# 106 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_ROUTE30_LILLIE
# 107 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removefieldmugshot
# 108 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	trainerbattle_no_intro TRAINER_LILLIE, MrPokemonHouse_Text_LillieDefeated
# 109 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 110 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT
# 111 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_TEMP_5, TRUE, MrPokemonHouse_EventScript_KeepWhiteoutOff
# 112 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag B_FLAG_NO_WHITEOUT
# 113 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_KeepWhiteoutOff::
# 114 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 115 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, MrPokemonHouse_EventScript_LilliePlayerWon
# 116 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_LOST, MrPokemonHouse_EventScript_LilliePlayerLost
# 117 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_DREW, MrPokemonHouse_EventScript_LillieDraw
# 118 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_FORFEITED, MrPokemonHouse_EventScript_LillieForfeit
# 119 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto MrPokemonHouse_EventScript_LillieUnexpectedOutcome
# 120 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 121 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ B_OUTCOME_WON: MrPokemonHouse_Text_LillieDefeated already played in battle.
# 122 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_LilliePlayerWon::
# 123 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieAfterBattle, MSGBOX_DEFAULT
# 124 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 125 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto MrPokemonHouse_EventScript_AfterBattle
# 126 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 127 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_LilliePlayerLost::
# 128 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieWon, MSGBOX_DEFAULT
# 129 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 130 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto MrPokemonHouse_EventScript_AfterBattle
# 131 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 132 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_LillieDraw::
# 133 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieDraw, MSGBOX_DEFAULT
# 134 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 135 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto MrPokemonHouse_EventScript_AfterBattle
# 136 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 137 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_LillieForfeit::
# 138 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieForfeit, MSGBOX_DEFAULT
# 139 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 140 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto MrPokemonHouse_EventScript_AfterBattle
# 141 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 142 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Should not happen in a trainer battle. It is not treated as a win; the scene
# 143 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ still continues so the ON_FRAME trigger can never re-run it half-staged.
# 144 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_LillieUnexpectedOutcome::
# 145 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieUnexpectedOutcome, MSGBOX_DEFAULT
# 146 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 147 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 148 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 11. Kukui wraps up the battle and hands over the Mystery Egg ---
# 149 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_AfterBattle::
# 150 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 151 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiAfterBattle, MSGBOX_DEFAULT
# 152 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiGiveEgg, MSGBOX_DEFAULT
# 153 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 154 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	giveitem ITEM_MYSTERY_EGG
# 155 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 156 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 157 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 12. Oak steps down to (8,6) so he is next to the player at (7,6) ---
# 158 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playbgm MUS_HG_OAK, TRUE
# 159 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakToPlayer
# 160 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 161 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 162 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	createfieldmugshot MUGSHOT_OAK
# 163 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakIntro, MSGBOX_DEFAULT
# 164 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 165 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removefieldmugshot
# 166 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 167 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 168 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	message MrPokemonHouse_Text_GetDex
# 169 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitfanfare
# 170 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 171 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 172 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_DEXNAV_OBTAINED
# 173 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 174 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 13. Oak says goodbye and walks out: (8,6) -> (8,7) -> (5,7) -> (5,8) ---
# 175 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	createfieldmugshot MUGSHOT_OAK
# 176 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_OakParting, MSGBOX_DEFAULT
# 177 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 178 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removefieldmugshot
# 179 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_EAST
# 180 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_KukuiOakParting, MSGBOX_DEFAULT
# 181 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 182 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakLeave
# 183 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement 0
# 184 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playse SE_EXIT
# 185 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeobject LOCALID_ROUTE30_OAK
# 186 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	fadedefaultbgm
# 187 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 188 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 14. Lillie and Vulpix leave together ---
# 189 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ Vulpix leads: (5,6) -> (5,7) -> door (5,8).
# 190 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ Lillie follows: (6,6) -> (6,7) -> (5,7), right behind her.
# 191 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
# 192 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_LillieParting, MSGBOX_DEFAULT
# 193 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 194 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_VULPIX, MrPokemonHouse_Movement_VulpixLeave
# 195 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	applymovement LOCALID_ROUTE30_LILLIE, MrPokemonHouse_Movement_LillieLeave
# 196 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement LOCALID_ROUTE30_VULPIX
# 197 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	waitmovement LOCALID_ROUTE30_LILLIE
# 198 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	playse SE_EXIT
# 199 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeobject LOCALID_ROUTE30_VULPIX
# 200 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeobject LOCALID_ROUTE30_LILLIE
# 201 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 202 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	@ --- 15. Kukui stays at (7,5), heals the party and sends the player off ---
# 203 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 204 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	turnobject LOCALID_ROUTE30_KUKUI, DIR_SOUTH
# 205 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Heal, MSGBOX_DEFAULT
# 206 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 207 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 208 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_DependingOnYou, MSGBOX_DEFAULT
# 209 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 210 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 211 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_DELIVERED_EGG
# 212 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setvar VAR_NEWBARKTOWN_LABSTATE, 4
# 213 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
# 214 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag FLAG_HIDE_LAB_POLICEMAN
# 215 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY
# 216 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag FLAG_HIDE_SILVER_CHERRYGROVE
# 217 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
# 218 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
# 219 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	setvar VAR_CHERRYGROVE_CITY_STATE, 2
# 220 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 221 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 222 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 223 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 224 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui::
# 225 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 226 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	faceplayer
# 227 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	checkitem ITEM_RED_SCALE
# 228 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_Kukui_RedScale
# 229 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_AlwaysNewDiscoveries, MSGBOX_DEFAULT
# 230 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 231 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 232 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 233 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 234 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui_RedScale::
# 235 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_GimmeTheScale, MSGBOX_YESNO
# 236 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, MrPokemonHouse_EventScript_Kukui_RedScale_Accepted
# 237 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_Disappointed, MSGBOX_DEFAULT
# 238 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 239 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 240 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 241 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 242 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui_RedScale_Accepted::
# 243 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	giveitem ITEM_FAIRYTITE
# 244 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MrPokemonHouse_EventScript_Kukui_RedScale_NoRoom
# 245 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	removeitem ITEM_RED_SCALE
# 246 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_ScaleAccepted, MSGBOX_DEFAULT
# 247 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 248 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 249 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 250 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 251 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Kukui_RedScale_NoRoom::
# 252 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_ScaleBagFull, MSGBOX_DEFAULT
# 253 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	closemessage
# 254 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 255 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 256 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 257 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Computer::
# 258 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 259 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_BrokenComputer, MSGBOX_SIGN
# 260 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 261 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 262 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 263 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Magazine::
# 264 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 265 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_ForeignMagazines, MSGBOX_SIGN
# 266 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 267 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 268 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 269 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_EventScript_Coins::
# 270 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	lock
# 271 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	msgbox MrPokemonHouse_Text_StrangeCoins, MSGBOX_SIGN
# 272 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	release
# 273 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	end
# 274 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 275 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Player: door (5,8) -> (5,7) -> (5,6) -> (6,6) -> (7,6), facing Kukui at (7,5).
# 276 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ (7,6) leaves (6,6) free for Lillie and (8,6) free for Oak.
# 277 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_PlayerToProfessors:
# 278 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_up
# 279 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_up
# 280 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 281 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 282 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_up
# 283 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 284 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 285 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Lillie: chair (5,5) -> (5,6) -> (6,6), facing the player at (7,6).
# 286 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Skirts the table, whose blocked tiles are (3,4) (4,4) (3,5) (4,5).
# 287 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_LillieToPlayer:
# 288 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 289 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 290 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_right
# 291 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 292 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 293 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Vulpix: (4,6) waits one step, then -> (5,6) once Lillie has moved on to (6,6).
# 294 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_VulpixToPlayer:
# 295 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	delay_16
# 296 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_right
# 297 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_right
# 298 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 299 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 300 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Oak: (8,5) -> (8,6), facing the player at (7,6).
# 301 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_OakToPlayer:
# 302 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 303 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	face_left
# 304 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 305 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 306 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Oak: (8,6) -> (8,7) -> (7,7) -> (6,7) -> (5,7) -> door (5,8).
# 307 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_OakLeave:
# 308 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 309 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 310 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 311 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 312 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 313 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_in_place_down
# 314 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 315 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 316 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Vulpix: (5,6) -> (5,7) -> door (5,8).
# 317 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_VulpixLeave:
# 318 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 319 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 320 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_in_place_down
# 321 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 322 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 323 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
@ Lillie: (6,6) -> (6,7) -> (5,7), stopping behind Vulpix on the door tile.
# 324 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Movement_LillieLeave:
# 325 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_down
# 326 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_left
# 327 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	walk_in_place_down
# 328 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	step_end
# 329 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 330 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro1:
# 331 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Alola! You're {PLAYER},\n"
# 332 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "right? Elm said you'd come!\p"
# 333 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Come in! We've got quite a\n"
# 334 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "little gathering here today.$"
# 335 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 336 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro2:
# 337 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: I'm Professor Kukui.\n"
# 338 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I study Pokémon moves in Alola!\p"
# 339 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I was traveling through Kanto\n"
# 340 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "when I heard about Johto.\p"
# 341 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Apparently, some Pokémon from\n"
# 342 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Alola have been appearing here!\p"
# 343 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I had to see that for myself.\n"
# 344 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I've been working from this house.$"
# 345 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 346 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakGreeting:
# 347 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: Ah, you must be {PLAYER}!\n"
# 348 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Elm told us you were coming.$"
# 349 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 350 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro3:
# 351 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: A couple who run a\n"
# 352 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Day-Care gave me an unusual Egg.\p"
# 353 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I contacted Elm right away.\n"
# 354 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "He knows much more about Eggs!\p"
# 355 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'd like you to take it to him.\n"
# 356 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "But first, introductions!$"
# 357 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 358 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro4:
# 359 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: And this is Lillie.\n"
# 360 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "She's visiting from Alola too!$"
# 361 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 362 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Intro5:
# 363 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Lillie, weren't you\n"
# 364 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "looking for a training partner?$"
# 365 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 366 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieAnswer:
# 367 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Oh! Yes, Professor.\n"
# 368 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Just a moment!$"
# 369 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 370 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieIntro:
# 371 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Yes! Though I wasn't\n"
# 372 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "expecting to meet one so soon.\p"
# 373 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "It's nice to meet you, {PLAYER}.\n"
# 374 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'm traveling with my mother.\p"
# 375 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I've started training Pokémon,\n"
# 376 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "and there's so much to learn.\p"
# 377 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Would you battle me?\n"
# 378 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Vulpix and I have been practicing!$"
# 379 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 380 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieVulpix:
# 381 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: My Vulpix is from Alola.\n"
# 382 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "That's why her fur is white.\p"
# 383 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "People here keep asking about it.\n"
# 384 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "She seems quite pleased!$"
# 385 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 386 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakBeforeBattle:
# 387 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: A battle? An excellent chance\n"
# 388 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to see how you work together!$"
# 389 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 390 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiBeforeBattle:
# 391 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Let's get your partner\n"
# 392 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "rested before we begin.\p"
# 393 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You walked all the way from\n"
# 394 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Elm's lab, after all!$"
# 395 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 396 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieBeforeBattle:
# 397 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: All right, Vulpix.\n"
# 398 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Let's do this together!$"
# 399 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 400 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieDefeated:
# 401 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: We did our best, Vulpix.\n"
# 402 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Thank you!$"
# 403 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 404 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieAfterBattle:
# 405 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Oh! You changed your\n"
# 406 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "approach before I noticed.\p"
# 407 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I was so busy thinking about\n"
# 408 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "our next move…\p"
# 409 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I need to watch our opponent\n"
# 410 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "more carefully too.\p"
# 411 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Thank you, {PLAYER}.\n"
# 412 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'm glad I asked!$"
# 413 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 414 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieWon:
# 415 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: We… we won?\n"
# 416 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Vulpix, we actually won!\p"
# 417 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oh! I'm sorry, {PLAYER}.\n"
# 418 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'm just so happy for her!\p"
# 419 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Your Pokémon never gave up\n"
# 420 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "on you, not even once.\p"
# 421 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Thank you. I'm glad I asked!$"
# 422 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 423 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieDraw:
# 424 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Both of them at once?\n"
# 425 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Then it's a draw!\p"
# 426 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "We'll have to settle it\n"
# 427 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "another time, {PLAYER}.$"
# 428 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 429 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieForfeit:
# 430 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Oh… We're stopping here?\p"
# 431 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "That's all right. Knowing when\n"
# 432 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to rest is important too.$"
# 433 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 434 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieUnexpectedOutcome:
# 435 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Thank you for battling\n"
# 436 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "with us, {PLAYER}!$"
# 437 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 438 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiAfterBattle:
# 439 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: There's a lesson you\n"
# 440 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "won't find in a notebook!\p"
# 441 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Knowing a move is one thing.\n"
# 442 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Finding its moment takes practice.\p"
# 443 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You both gave your partners\n"
# 444 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "something to be proud of!$"
# 445 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 446 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieRematch:
# 447 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: Shall we try again?\n"
# 448 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "We'll be ready when you are.$"
# 449 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 450 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiGiveEgg:
# 451 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Now, about Elm's errand!\p"
# 452 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Please take this Egg to him.\n"
# 453 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'd like to hear what he thinks.$"
# 454 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 455 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakIntro:
# 456 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: That was worth staying for!\p"
# 457 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I came to hear Kukui's findings,\n"
# 458 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "but you've given me another idea.\p"
# 459 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You paid close attention to\n"
# 460 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "your Pokémon during that battle.\p"
# 461 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "That same care will serve you\n"
# 462 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "well on a journey of discovery.\p"
# 463 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'd like you to take a Pokédex.\p"
# 464 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "It records the Pokémon you see\n"
# 465 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "and catch during your travels.\p"
# 466 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You can look up their habitats,\n"
# 467 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "evolutions, and moves as well.\p"
# 468 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Johto still has surprises for us.\n"
# 469 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Help us discover them!$"
# 470 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 471 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_GetDex:
# 472 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "{PLAYER} received the Pokédex!$"
# 473 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 474 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_OakParting:
# 475 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Oak: Take your time to observe\n"
# 476 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "the Pokémon you meet, {PLAYER}.\p"
# 477 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Even a familiar species may\n"
# 478 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "have something new to teach you!\p"
# 479 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Now I must leave for Goldenrod.\n"
# 480 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "My radio audience is waiting!\p"
# 481 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui, keep those notes coming.\n"
# 482 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "And good luck to both of you!$"
# 483 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 484 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_KukuiOakParting:
# 485 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Count on it, Professor!\n"
# 486 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Have a good trip!$"
# 487 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 488 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_LillieParting:
# 489 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Lillie: I should be going too.\n"
# 490 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "My mother is waiting for me.\p"
# 491 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I told her I'd only stop by\n"
# 492 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to see Professor Kukui.\p"
# 493 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Now I have a battle to tell\n"
# 494 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "her about!\p"
# 495 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Let's meet again, {PLAYER}.\n"
# 496 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "We'll have more to show you then.\p"
# 497 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Come along, Vulpix!$"
# 498 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 499 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Heal:
# 500 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Before you head out,\n"
# 501 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "let me take care of your Pokémon.\p"
# 502 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A good rest is part of\n"
# 503 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "good training!$"
# 504 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 505 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_DependingOnYou:
# 506 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: I'll stay here and\n"
# 507 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "keep working on my research.\p"
# 508 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Give Elm my regards!\n"
# 509 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "And drop by whenever you like.$"
# 510 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 511 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_AlwaysNewDiscoveries:
# 512 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Alola, {PLAYER}!\n"
# 513 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "How's the journey going?\p"
# 514 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I've been comparing Pokémon\n"
# 515 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "from Johto with those back home.\p"
# 516 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Different surroundings can mean\n"
# 517 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "a very different way of living.\p"
# 518 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Sometimes even a different type!\n"
# 519 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "There's always more to learn.$"
# 520 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 521 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_GimmeTheScale:
# 522 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Hold on. That red scale…\n"
# 523 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Did it come from a Gyarados?\p"
# 524 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Now that's something I'd love\n"
# 525 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "to examine up close!\p"
# 526 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Would you trade it for a\n"
# 527 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Mega Stone Oak left with me?\p"
# 528 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "You could put it to good use,\n"
# 529 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "and I could study that scale!$"
# 530 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 531 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_Disappointed:
# 532 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: No problem!\n"
# 533 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "It's quite a keepsake.\p"
# 534 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "If you change your mind,\n"
# 535 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "you know where to find me!$"
# 536 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 537 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_ScaleAccepted:
# 538 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Thanks, {PLAYER}!\n"
# 539 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "I'll take good care of it.\p"
# 540 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A whole research project,\n"
# 541 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "right in the palm of my hand!$"
# 542 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 543 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_ScaleBagFull:
# 544 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui: Make room for the stone\n"
# 545 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "first, and we'll make the trade.\p"
# 546 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Keep your scale until then!$"
# 547 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 548 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_ForeignMagazines:
# 549 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Research journals from Alola\n"
# 550 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "cover the shelves.\p"
# 551 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "One article compares Vulpix\n"
# 552 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "from different regions.\p"
# 553 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Kukui has filled the margins\n"
# 554 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "with handwritten questions.$"
# 555 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 556 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_BrokenComputer:
# 557 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A computer displays a map\n"
# 558 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "of Johto beside a map of Alola.\p"
# 559 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "An unfinished report is open:\n"
# 560 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "“Regional Forms in Johto.”\p"
# 561 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "There are more questions\n"
# 562 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "than answers so far.$"
# 563 "data/maps/Route30_MrPokemonsHouse/scripts.pory"

# 564 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
MrPokemonHouse_Text_StrangeCoins:
# 565 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "A collection of travel souvenirs\n"
# 566 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "is spread across the table.\p"
# 567 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "Tickets, coins, and a photograph\n"
# 568 "data/maps/Route30_MrPokemonsHouse/scripts.pory"
	.string "of a beach in Alola.$"
