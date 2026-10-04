@ The Brass Tower, whole, at dusk on the night it burned: a memory the Kimono
@ Girls dance open (Berry Master, plan part 15; REI_DA_COLHEITA.md 15.5).
@ Layout: BurnedTower_1F without its holes, 4 statues, and the B1F ladder
@ set into the north wall at (14,3)-(14,4). Palette: the dusk tint
@ (MapTint_Mode, src/berry_garden.c).
@
@ Plan (map.bin measured with dump_mapa.py):
@   arrival from the theater (15,21), facing north; Peonia (13,21), Morty
@     (14,21) and Eusine (16,21) beside the player, all facing north; only
@     in state 11 (FLAG_TEMP_1)
@   sages (9,8) >, (17,11) v, (5,17) ^; a Kimono Girl (22,19) <
@   the ladder (14,4): coord_event -> thunder, light, the roof (10,11)
@   the door mat (15,22) leaves the memory, back to the theater
@   (14,5) is where the roof's stairs come back down
@
@ Temps: FLAG_TEMP_1 hides the three; VAR_TEMP_1 arms the arrival line.
BrassTowerMemory_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BrassTowerMemory_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BrassTowerMemory_1F_OnFrame
	.byte 0

BrassTowerMemory_1F_OnTransition::
	setflag FLAG_TEMP_1
	setvar VAR_TEMP_1, 0
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_SHADEROOT, BrassTowerMemory_1F_EventScript_End
	clearflag FLAG_TEMP_1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 15, BrassTowerMemory_1F_EventScript_End
	goto_if_ne VAR_0x8005, 21, BrassTowerMemory_1F_EventScript_End
	setvar VAR_TEMP_1, 1
BrassTowerMemory_1F_EventScript_End::
	end

BrassTowerMemory_1F_OnFrame::
	map_script_2 VAR_TEMP_1, 1, BrassTowerMemory_1F_EventScript_Arrive
	.2byte 0

BrassTowerMemory_1F_EventScript_Arrive::
	setvar VAR_TEMP_1, 2
	lockall
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox BrassTowerMemory_1F_Text_Arrive, MSGBOX_DEFAULT
	msgbox BrassTowerMemory_1F_Text_ArriveEusine, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ Thunder, then light, then the roof.
BrassTowerMemory_1F_EventScript_Ladder::
	lockall
	playse SE_THUNDER
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 12
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	call BerryGarden_EventScript_WhiteFlash
	waitse
	msgbox BrassTowerMemory_1F_Text_Thunder, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	warp MAP_BRASS_TOWER_MEMORY_ROOF, 10, 11
	waitstate
	releaseall
	end

BrassTowerMemory_1F_EventScript_Sage1::
	msgbox BrassTowerMemory_1F_Text_Sage1, MSGBOX_NPC
	end

BrassTowerMemory_1F_EventScript_Sage2::
	msgbox BrassTowerMemory_1F_Text_Sage2, MSGBOX_NPC
	end

BrassTowerMemory_1F_EventScript_Sage3::
	msgbox BrassTowerMemory_1F_Text_Sage3, MSGBOX_NPC
	end

BrassTowerMemory_1F_EventScript_Kimono::
	msgbox BrassTowerMemory_1F_Text_Kimono, MSGBOX_NPC
	end

BrassTowerMemory_1F_EventScript_Morty::
	msgbox BrassTowerMemory_1F_Text_Morty, MSGBOX_NPC
	end

BrassTowerMemory_1F_EventScript_Eusine::
	msgbox BrassTowerMemory_1F_Text_Eusine, MSGBOX_NPC
	end

BrassTowerMemory_1F_EventScript_Peonia::
	msgbox BrassTowerMemory_1F_Text_Peonia, MSGBOX_NPC
	end

BrassTowerMemory_1F_Text_Arrive:
	.string "Sunset light. The smell of incense.\p"
	.string "The tower is whole.$"

BrassTowerMemory_1F_Text_ArriveEusine:
	.string "{SPEAKER NAME_EUSINE}The beams... the bells... it's all\n"
	.string "still up there!$"

BrassTowerMemory_1F_Text_Thunder:
	.string "Thunder. Then light. Then the smell of\n"
	.string "smoke.\p"
	.string "Above you, the bells begin to melt.$"

BrassTowerMemory_1F_Text_Sage1:
	.string "You're the new novice? Feed the black\n"
	.string "horse in the stable before dark.\p"
	.string "Brother Tomo spoils it. It came from\n"
	.string "over the sea, they say.$"

BrassTowerMemory_1F_Text_Sage2:
	.string "The bells ring at dusk and at dawn.\p"
	.string "...Does the air smell of smoke to you?$"

BrassTowerMemory_1F_Text_Sage3:
	.string "Lightning struck the tower twice this\n"
	.string "summer. The abbot says the bells will\l"
	.string "protect us.$"

BrassTowerMemory_1F_Text_Kimono:
	.string "...You can see me? Then you're one of\n"
	.string "us tonight. Dance well.$"

BrassTowerMemory_1F_Text_Morty:
	.string "{SPEAKER NAME_MORTY}It's a memory. Walk softly.\n"
	.string "Up the ladder, when you're ready.$"

BrassTowerMemory_1F_Text_Eusine:
	.string "{SPEAKER NAME_EUSINE}Look at the BEAMS! Every one of them\n"
	.string "still standing!$"

BrassTowerMemory_1F_Text_Peonia:
	.string "{SPEAKER NAME_PEONIA}Dad would love this place.\p"
	.string "He'd also probably set it on fire.\n"
	.string "...Wait. No. Bad joke. Bad night for it.$"
