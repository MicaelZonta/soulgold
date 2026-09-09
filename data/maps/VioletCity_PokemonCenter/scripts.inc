# 1 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 2 "data/maps/VioletCity_PokemonCenter/scripts.pory"
.set LOCALID_NURSE, 1
# 3 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 4 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_MapScripts::
# 5 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_Pokecenter_OnTransition
# 6 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.byte 0
# 7 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 8 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_Pokecenter_OnTransition::
# 9 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setrespawn HEAL_LOCATION_VIOLET_CITY
# 10 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 11 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 12 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Aide::
# 13 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 14 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 15 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, VioletCity_PokemonCenter_EventScript_Aide_Received
# 16 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_ElmsAideFavor, MSGBOX_YESNO
# 17 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
# 18 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
# 19 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 20 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 21 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 22 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 23 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_AideNoRoom::
# 24 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_DEFAULT
# 25 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 26 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 27 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 28 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 29 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Aide_Refuse::
# 30 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_ElmsAideRefuse, MSGBOX_YESNO
# 31 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
# 32 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
# 33 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 34 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 35 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 36 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Aide_Accepted::
# 37 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
# 38 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	giveegg SPECIES_COSMOG
# 39 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, VioletCity_PokemonCenter_EventScript_AideNoRoom
# 40 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 41 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	message LavaridgeTown_Text_ReceivedTheEgg
# 42 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitfanfare
# 43 "data/maps/VioletCity_PokemonCenter/scripts.pory"
    call VioletPCGiveExpJar
# 44 "data/maps/VioletCity_PokemonCenter/scripts.pory"
    closemessage
# 45 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag FLAG_RECEIVED_MYSTERY_EGG
# 46 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
# 47 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
# 48 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 49 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
# 50 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 51 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 52 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 53 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Aide_Received::
# 54 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
# 55 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 56 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 57 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 58 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 59 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gentleman::
# 60 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 61 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 62 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
# 63 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 64 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 65 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 66 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 67 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EVentScript_Kid::
# 68 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 69 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 70 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
# 71 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 72 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 73 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 74 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 75 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Man::
# 76 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 77 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 78 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
# 79 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 80 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 81 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 82 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 83 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_ElmsAideFavor:
# 84 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{PLAYER}, long time, no see.\p"
# 85 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Prof. Elm asked me to find you.\p"
# 86 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "He has another favor to ask.\p"
# 87 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Would you take the Pokémon Egg?$"
# 88 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 89 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_ElmsAideNoRoom:
# 90 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{PLAYER}, long time, no see.\p"
# 91 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Prof. Elm asked me to find you.\p"
# 92 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "He has another favor to ask.\p"
# 93 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Would you take the Pokémon Egg?\p"
# 94 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Oh, wait... You need to make room\n"
# 95 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "in your party first.$"
# 96 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 97 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_ElmsAideGiveEgg:
# 98 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "We discovered that a Pokémon won't\n"
# 99 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "hatch until it grows in the Egg.\p"
# 100 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "It also has to be with other\n"
# 101 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "active Pokémon to hatch.\p"
# 102 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{PLAYER}, you're the only person\n"
# 103 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "we can rely on.$"
# 104 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 105 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_ElmsAideGiveItem:
# 106 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Oh, and this might help when it hatches.$"
# 107 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 108 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_ElmsAideFullParty:
# 109 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Oh, no. You can't carry any more\n"
# 110 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon with you.\p"
# 111 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I'll wait here while you make\n"
# 112 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "room for the Egg.$"
# 113 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 114 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_ElmsAideRefuse:
# 115 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "B-but… Prof. Elm asked for you…$"
# 116 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 117 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_FarawayLink:
# 118 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I've been thinking it'd be great\n"
# 119 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "to link up and battle with my\n"
# 120 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "friends who live far away.$"
# 121 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 122 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_MobileAdapter:
# 123 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I just battled a friend in\n"
# 124 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Cianwood over a link.\p"
# 125 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "If you connect a Mobile Adapter,\n"
# 126 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "you can link with a friend far\n"
# 127 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "away.$"
# 128 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 129 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GameboyKid:
# 130 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "A guy named Bill made the\n"
# 131 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon PC storage system.$"
# 132 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 133 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_Gentleman:
# 134 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "It was around three years ago.\p"
# 135 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Team Rocket was up to no good\n"
# 136 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "with Pokémon.\p"
# 137 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "But justice prevailed--a young\n"
# 138 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "kid broke 'em up.$"
# 139 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 140 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_Youngster:
# 141 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon are smart. They won't\n"
# 142 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "obey a trainer they don't respect.\p"
# 143 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Without the right Gym Badges,\n"
# 144 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "they will just do as they please.$"

VioletPCGiveExpJar::
# 148 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletPCGiveExpJar_Text_0
# 150 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	giveitem ITEM_CANDY_JAR
# 151 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletPCGiveExpJar_Text_1
	return


VioletPCGiveExpJar_Text_0:
# 148 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "You should also take this for raising\n"
	.string "more Pokémon.$"

VioletPCGiveExpJar_Text_1:
# 151 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{PLAYER}, you're the only \n"
	.string "person we can rely on.$"
