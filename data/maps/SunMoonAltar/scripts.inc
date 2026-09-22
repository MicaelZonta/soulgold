SunMoonAltar_MapScripts::
	.byte 0

@ SKELETON: the island with the cast standing still in the climax formation
@ (Lusamine before the disc, Lillie and Gladion with their partners on the
@ stage, Looker, Anabel and Kukui on the terrace). No flags, no state: every
@ object is always visible. One placeholder box each; the altar document will
@ replace these with the real scene. Ninetales and Silvally use "script": "NULL"
@ like in OlivineCity_House1 (skill parceiro-pokemon-de-npc).

SunMoonAltar_EventScript_Lusamine::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Lusamine, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Lillie::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Lillie, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Gladion::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Gladion, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Looker::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Looker, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Anabel::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Anabel, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Kukui::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Kukui, MSGBOX_DEFAULT
	release
	end

@ Ferry back to Olivine (the way here is the port sailor + ITEM_SUN_MOON_TICKET).
@ Same send-off as the Faraway Island sailor: the sailor boards, the player
@ hides, the SS Tidal sails east, then a silent warp to the Olivine desk at
@ (8,16), right above the port sailor.
SunMoonAltar_EventScript_Sailor::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Sailor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_SailorStay
	msgbox SunMoonAltar_Text_SailorDepart, MSGBOX_DEFAULT
	closemessage
	hidefollower
	delay 30
	hideobjectat LOCALID_SUN_MOON_ALTAR_SAILOR, MAP_SUN_MOON_ALTAR
	setvar VAR_0x8004, LOCALID_SUN_MOON_ALTAR_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE, 8, 16
	waitstate
	release
	end

SunMoonAltar_EventScript_SailorStay::
	msgbox SunMoonAltar_Text_SailorStay, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_Text_Lusamine:
	.string "LUSAMINE: This is where the passage\n"
	.string "opens. I can feel it from here.$"

SunMoonAltar_Text_Lillie:
	.string "LILLIE: The altar feels different\n"
	.string "from anywhere else in Johto…$"

SunMoonAltar_Text_Gladion:
	.string "GLADION: Stay sharp. Whatever is\n"
	.string "past that disc won't wait for us.$"

SunMoonAltar_Text_Looker:
	.string "LOOKER: We have a way through.\p"
	.string "Now we make certain we have\n"
	.string "a way back.$"

SunMoonAltar_Text_Anabel:
	.string "ANABEL: Opening the passage is only\n"
	.string "the beginning.\p"
	.string "We must be able to bring\n"
	.string "everyone home.$"

SunMoonAltar_Text_Kukui:
	.string "KUKUI: Feel that? The whole altar\n"
	.string "is humming!$"

SunMoonAltar_Text_Sailor:
	.string "The ship's ready whenever you are.\p"
	.string "Shall we head back to Olivine?$"

SunMoonAltar_Text_SailorDepart:
	.string "Aye! Back to Olivine we go!$"

SunMoonAltar_Text_SailorStay:
	.string "Right. I'll be here on the pier.$"
