# 1 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 2 "data/maps/VioletCity_PokemonCenter/scripts.pory"
.set LOCALID_NURSE, 1
# 3 "data/maps/VioletCity_PokemonCenter/scripts.pory"
.set LOCALID_VIOLET_GLADION, 6
# 4 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 5 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_MapScripts::
# 6 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, VioletCity_Pokecenter_OnTransition
# 7 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.byte 0
# 8 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 9 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_Pokecenter_OnTransition::
# 10 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setrespawn HEAL_LOCATION_VIOLET_CITY
# 11 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 12 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 13 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gladion::
# 14 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 15 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 16 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, VioletCity_PokemonCenter_EventScript_Gladion_Received
# 17 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	getpartysize
# 18 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_ne VAR_RESULT, PARTY_SIZE, VioletCity_PokemonCenter_EventScript_Gladion_Battle
# 19 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
# 20 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, VioletCity_PokemonCenter_EventScript_Gladion_Battle
# 21 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionNoRoom, MSGBOX_DEFAULT
# 22 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 23 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 24 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 25 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 26 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gladion_Battle::
# 27 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionRecognizes, MSGBOX_DEFAULT
# 28 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 29 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionPartner1, MSGBOX_DEFAULT
# 30 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionPartner2, MSGBOX_DEFAULT
# 31 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 32 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 33 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	removefieldmugshot
# 34 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	trainerbattle_no_intro TRAINER_GLADION, VioletCity_PokeCenter_Text_GladionVictory
# 35 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionGiveEgg, MSGBOX_DEFAULT
# 36 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	giveegg SPECIES_COSMOG
# 37 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	copyvar VAR_0x8008, VAR_RESULT
# 38 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_0x8008, MON_CANT_GIVE, VioletCity_PokemonCenter_EventScript_GladionNoRoomAfterBattle
# 39 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 40 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	message LavaridgeTown_Text_ReceivedTheEgg
# 41 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitfanfare
# 42 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 43 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	call_if_eq VAR_0x8008, MON_GIVEN_TO_PC, VioletCity_PokemonCenter_EventScript_GladionEggSentToPC
# 44 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionParting, MSGBOX_DEFAULT
# 45 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 46 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	specialvar VAR_RESULT, ScriptCheckPlayerWestOfGladion
# 47 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, VioletCity_PokemonCenter_EventScript_GladionLeaveViaSouth
# 48 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_GLADION, VioletCity_PokemonCenter_Movement_GladionLeave
# 49 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionLeaveDone
# 50 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 51 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionLeaveViaSouth::
# 52 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_GLADION, VioletCity_PokemonCenter_Movement_GladionLeaveViaSouth
# 53 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 54 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionLeaveDone::
# 55 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitmovement 0
# 56 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	playse SE_EXIT
# 57 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	removeobject LOCALID_VIOLET_GLADION
# 58 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag FLAG_RECEIVED_MYSTERY_EGG
# 59 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_GLADION
# 60 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
# 61 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 62 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 63 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 64 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 65 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionEggSentToPC::
# 66 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionEggSentToPC, MSGBOX_DEFAULT
# 67 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 68 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	return
# 69 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 70 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Defensive fallback: unreachable in practice, since the party/PC check above
# 71 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ already guarantees room before the battle starts and nothing can deposit or
# 72 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ withdraw Pokemon mid-battle.
# 73 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionNoRoomAfterBattle::
# 74 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionNoRoom, MSGBOX_DEFAULT
# 75 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 76 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 77 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 78 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 79 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gladion_Received::
# 80 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionAfterDelivery, MSGBOX_DEFAULT
# 81 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 82 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 83 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 84 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 85 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gentleman::
# 86 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 87 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 88 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
# 89 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 90 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 91 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 92 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 93 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EVentScript_Kid::
# 94 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 95 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 96 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
# 97 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 98 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 99 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 100 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 101 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Man::
# 102 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 103 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 104 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
# 105 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 106 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 107 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 108 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 109 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionNoRoom:
# 110 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "There's no room for the Egg in\n"
# 111 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "your party or your PC.\p"
# 112 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Make some space first. I'll wait\n"
# 113 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "here.$"
# 114 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 115 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionEggSentToPC:
# 116 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Your party is full, so the Egg\n"
# 117 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "was sent to your PC.\p"
# 118 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Don't forget to check on it.$"
# 119 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 120 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionRecognizes:
# 121 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "You're {PLAYER}?\p"
# 122 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Lillie mentioned you.\n"
# 123 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "She's planning your next battle.$"
# 124 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 125 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionPartner1:
# 126 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I found this Type: Null in Alola.\n"
# 127 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Someone had left it behind.\p"
# 128 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "It's traveling with me now.$"
# 129 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 130 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionPartner2:
# 131 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "We're training. That doesn't\n"
# 132 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "mean we'll hold back.\p"
# 133 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Let me see how you fight.$"
# 134 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 135 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionVictory:
# 136 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Gladion: We're getting there,\n"
# 137 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Null. That was a good battle.$"
# 138 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 139 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionGiveEgg:
# 140 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Here's the Egg. Elm asked me\n"
# 141 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "to bring it to you.\p"
# 142 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Take care of it.$"
# 143 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 144 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionParting:
# 145 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "And when Lillie challenges you\n"
# 146 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "again… give her a proper battle.$"
# 147 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 148 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionAfterDelivery:
# 149 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Gladion: Take care of that Egg.$"
# 150 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 151 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_FarawayLink:
# 152 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I've been thinking it'd be great\n"
# 153 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "to link up and battle with my\n"
# 154 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "friends who live far away.$"
# 155 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 156 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_MobileAdapter:
# 157 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I just battled a friend in\n"
# 158 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Cianwood over a link.\p"
# 159 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "If you connect a Mobile Adapter,\n"
# 160 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "you can link with a friend far\n"
# 161 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "away.$"
# 162 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 163 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GameboyKid:
# 164 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "A guy named Bill made the\n"
# 165 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon PC storage system.$"
# 166 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 167 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_Gentleman:
# 168 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "It was around three years ago.\p"
# 169 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Team Rocket was up to no good\n"
# 170 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "with Pokémon.\p"
# 171 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "But justice prevailed--a young\n"
# 172 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "kid broke 'em up.$"
# 173 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 174 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_Youngster:
# 175 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon are smart. They won't\n"
# 176 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "obey a trainer they don't respect.\p"
# 177 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Without the right Gym Badges,\n"
# 178 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "they will just do as they please.$"
# 179 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 180 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Gladion: (9,4) -> (7,4) -> door (7,8).
# 181 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_GladionLeave:
# 182 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 183 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 184 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 185 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 186 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 187 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 188 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
# 189 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 190 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Used instead of the movement above when the player is standing directly
# 191 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ west of Gladion (9,4), so the first step doesn't walk through them.
# 192 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_GladionLeaveViaSouth:
# 193 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 194 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 195 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 196 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 197 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 198 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 199 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
