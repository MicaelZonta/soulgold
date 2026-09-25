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
VioletCity_PokemonCenter_EventScript_Gladion::
# 13 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 14 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 15 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, VioletCity_PokemonCenter_EventScript_Gladion_Received
# 16 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	getpartysize
# 17 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_ne VAR_RESULT, PARTY_SIZE, VioletCity_PokemonCenter_EventScript_Gladion_Battle
# 18 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
# 19 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, VioletCity_PokemonCenter_EventScript_Gladion_Battle
# 20 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionNoRoom, MSGBOX_DEFAULT
# 21 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 22 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 23 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 24 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 25 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Stage (y grows downward): Gladion (9,4), Type: Null (10,4) on his east.
# 26 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Type: Null blocks the east side, so the player can only be west (8,4) or
# 27 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ south (9,5) of Gladion here - the two cases the exit routes below cover.
# 28 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gladion_Battle::
# 29 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionRecognizes, MSGBOX_DEFAULT
# 30 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 31 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	@ Introducing his partner: Gladion looks east at Type: Null, which
# 32 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	@ glances back at him in place (no walking toward the player).
# 33 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	turnobject LOCALID_VIOLET_GLADION, DIR_EAST
# 34 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_TYPENULL, VioletCity_PokemonCenter_Movement_TypeNullReact
# 35 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitmovement LOCALID_VIOLET_TYPENULL
# 36 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionPartner1, MSGBOX_DEFAULT
# 37 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 38 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 39 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionPartner2, MSGBOX_DEFAULT
# 40 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 41 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 42 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	removefieldmugshot
# 43 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 44 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	@ Losing is allowed: the Egg is delivered on every outcome.
# 45 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	checkflag B_FLAG_NO_WHITEOUT
# 46 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT
# 47 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag B_FLAG_NO_WHITEOUT
# 48 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_VIOLET_GLADION
# 49 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	trainerbattle_no_intro TRAINER_GLADION, VioletCity_PokeCenter_Text_GladionVictory
# 50 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 51 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 52 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_TEMP_3, TRUE, VioletCity_PokemonCenter_EventScript_GladionKeepWhiteoutOff
# 53 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	clearflag B_FLAG_NO_WHITEOUT
# 54 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionKeepWhiteoutOff::
# 55 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 56 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, VioletCity_PokemonCenter_EventScript_GladionPlayerWon
# 57 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_LOST, VioletCity_PokemonCenter_EventScript_GladionPlayerLost
# 58 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_DREW, VioletCity_PokemonCenter_EventScript_GladionDraw
# 59 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_TEMP_2, B_OUTCOME_FORFEITED, VioletCity_PokemonCenter_EventScript_GladionForfeit
# 60 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionUnexpectedOutcome
# 61 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 62 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ B_OUTCOME_WON: Gladion's own line (VioletCity_PokeCenter_Text_GladionVictory)
# 63 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ already played automatically when his last Pokémon fainted.
# 64 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionPlayerWon::
# 65 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionWon, MSGBOX_DEFAULT
# 66 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionDeliver
# 67 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 68 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionPlayerLost::
# 69 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionLost, MSGBOX_DEFAULT
# 70 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionDeliver
# 71 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 72 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionDraw::
# 73 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionDraw, MSGBOX_DEFAULT
# 74 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionDeliver
# 75 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 76 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionForfeit::
# 77 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionForfeit, MSGBOX_DEFAULT
# 78 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionDeliver
# 79 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 80 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Not a real outcome of a local trainer battle. Still concludes the event
# 81 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ (same as DragonsDen_Shrine) rather than letting the player re-battle
# 82 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Gladion for free experience.
# 83 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionUnexpectedOutcome::
# 84 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionUnexpectedOutcome, MSGBOX_DEFAULT
# 85 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionDeliver::
# 86 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionGiveEgg, MSGBOX_DEFAULT
# 87 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	giveegg SPECIES_COSMOG
# 88 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	copyvar VAR_0x8008, VAR_RESULT
# 89 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_0x8008, MON_CANT_GIVE, VioletCity_PokemonCenter_EventScript_GladionNoRoomAfterBattle
# 90 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 91 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	message LavaridgeTown_Text_ReceivedTheEgg
# 92 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitfanfare
# 93 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 94 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	call_if_eq VAR_0x8008, MON_GIVEN_TO_PC, VioletCity_PokemonCenter_EventScript_GladionEggSentToPC
# 95 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionParting, MSGBOX_DEFAULT
# 96 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 97 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	@ Gladion leaves first; Type: Null hesitates, then follows his exact path
# 98 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	@ one tile behind, ending on (7,7) while Gladion stands on the door (7,8).
# 99 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	specialvar VAR_RESULT, ScriptCheckPlayerWestOfGladion
# 100 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, VioletCity_PokemonCenter_EventScript_GladionLeaveViaSouth
# 101 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_GLADION, VioletCity_PokemonCenter_Movement_GladionLeave
# 102 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_TYPENULL, VioletCity_PokemonCenter_Movement_TypeNullFollow
# 103 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	goto VioletCity_PokemonCenter_EventScript_GladionLeaveDone
# 104 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 105 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionLeaveViaSouth::
# 106 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_GLADION, VioletCity_PokemonCenter_Movement_GladionLeaveViaSouth
# 107 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	applymovement LOCALID_VIOLET_TYPENULL, VioletCity_PokemonCenter_Movement_TypeNullFollowViaSouth
# 108 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 109 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionLeaveDone::
# 110 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitmovement LOCALID_VIOLET_GLADION
# 111 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	waitmovement LOCALID_VIOLET_TYPENULL
# 112 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	playse SE_EXIT
# 113 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	removeobject LOCALID_VIOLET_TYPENULL
# 114 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	removeobject LOCALID_VIOLET_GLADION
# 115 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag FLAG_RECEIVED_MYSTERY_EGG
# 116 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setflag FLAG_HIDE_VIOLET_CITY_GLADION
# 117 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
# 118 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
# 119 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 120 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 121 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 122 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionEggSentToPC::
# 123 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionEggSentToPC, MSGBOX_DEFAULT
# 124 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 125 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	return
# 126 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 127 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Defensive fallback: unreachable in practice, since the party/PC check above
# 128 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ already guarantees room before the battle starts and nothing can deposit or
# 129 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ withdraw Pokemon mid-battle. FLAG_RECEIVED_MYSTERY_EGG stays unset, so
# 130 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Gladion and Type: Null remain and the player can talk to him again.
# 131 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_GladionNoRoomAfterBattle::
# 132 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionNoRoom, MSGBOX_DEFAULT
# 133 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 134 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 135 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 136 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 137 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gladion_Received::
# 138 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GladionAfterDelivery, MSGBOX_DEFAULT
# 139 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 140 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 141 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 142 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 143 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Gentleman::
# 144 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 145 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 146 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_Gentleman, MSGBOX_DEFAULT
# 147 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 148 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 149 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 150 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 151 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EVentScript_Kid::
# 152 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 153 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 154 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_GameboyKid, MSGBOX_DEFAULT
# 155 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 156 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 157 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 158 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 159 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_EventScript_Man::
# 160 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	lock
# 161 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	faceplayer
# 162 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	msgbox VioletCity_PokeCenter_Text_Youngster, MSGBOX_DEFAULT
# 163 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	closemessage
# 164 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	release
# 165 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	end
# 166 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 167 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionNoRoom:
# 168 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "There's no room for the Egg in\n"
# 169 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "your party or your PC.\p"
# 170 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Make some space first. I'll wait\n"
# 171 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "here.$"
# 172 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 173 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionEggSentToPC:
# 174 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Your party is full, so the Egg\n"
# 175 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "was sent to your PC.\p"
# 176 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Don't forget to check on it.$"
# 177 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 178 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionRecognizes:
# 179 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "You're {PLAYER}?\p"
# 180 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Lillie mentioned you.\n"
# 181 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "She's planning your next battle.$"
# 182 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 183 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionPartner1:
# 184 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I found this Type: Null in Alola.\n"
# 185 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Someone had left it behind.\p"
# 186 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "It's traveling with me now.$"
# 187 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 188 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionPartner2:
# 189 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "We're training. That doesn't\n"
# 190 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "mean we'll hold back.\p"
# 191 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Let me see how you fight.$"
# 192 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 193 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionVictory:
# 194 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{SPEAKER NAME_GLADION}We're getting there,\n"
# 195 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Null. That was a good battle.$"
# 196 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 197 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionWon:
# 198 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I see why Lillie wants\n"
# 199 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "another match.$"
# 200 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 201 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionLost:
# 202 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{SPEAKER NAME_GLADION}You kept looking\n"
# 203 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "for a way through.\p"
# 204 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "That's enough for me to understand\n"
# 205 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "how you fight.$"
# 206 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 207 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionDraw:
# 208 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{SPEAKER NAME_GLADION}Neither team\n"
# 209 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "could finish that.\p"
# 210 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I still saw what I needed to see.$"
# 211 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 212 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionForfeit:
# 213 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{SPEAKER NAME_GLADION}You're stopping?\n"
# 214 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Fine.\p"
# 215 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Look after your team.\n"
# 216 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Elm's Egg still belongs with you.$"
# 217 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 218 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionUnexpectedOutcome:
# 219 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{SPEAKER NAME_GLADION}That didn't end cleanly.\n"
# 220 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Let's check on everyone.$"
# 221 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 222 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionGiveEgg:
# 223 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Here's the Egg. Elm asked me\n"
# 224 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "to bring it to you.\p"
# 225 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Take care of it.$"
# 226 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 227 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionParting:
# 228 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "And when Lillie challenges you\n"
# 229 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "again… give her a proper battle.$"
# 230 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 231 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GladionAfterDelivery:
# 232 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "{SPEAKER NAME_GLADION}Take care of that Egg.$"
# 233 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 234 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_FarawayLink:
# 235 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I've been thinking it'd be great\n"
# 236 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "to link up and battle with my\n"
# 237 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "friends who live far away.$"
# 238 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 239 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_MobileAdapter:
# 240 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "I just battled a friend in\n"
# 241 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Cianwood over a link.\p"
# 242 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "If you connect a Mobile Adapter,\n"
# 243 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "you can link with a friend far\n"
# 244 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "away.$"
# 245 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 246 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_GameboyKid:
# 247 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "A guy named Bill made the\n"
# 248 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon PC storage system.$"
# 249 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 250 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_Gentleman:
# 251 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "It was around three years ago.\p"
# 252 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Team Rocket was up to no good\n"
# 253 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "with Pokémon.\p"
# 254 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "But justice prevailed--a young\n"
# 255 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "kid broke 'em up.$"
# 256 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 257 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokeCenter_Text_Youngster:
# 258 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Pokémon are smart. They won't\n"
# 259 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "obey a trainer they don't respect.\p"
# 260 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "Without the right Gym Badges,\n"
# 261 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	.string "they will just do as they please.$"
# 262 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 263 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Type: Null (10,4): looks west at Gladion (9,4), shuffles in place, then
# 264 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ faces front again.
# 265 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_TypeNullReact:
# 266 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	face_left
# 267 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_in_place_faster_left
# 268 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	delay_16
# 269 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	face_down
# 270 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
# 271 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 272 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Gladion: (9,4) -> (7,4) -> door (7,8).
# 273 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_GladionLeave:
# 274 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 275 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 276 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 277 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 278 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 279 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 280 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
# 281 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 282 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Used instead of the movement above when the player is standing directly
# 283 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ west of Gladion (9,4), so the first step doesn't walk through them.
# 284 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_GladionLeaveViaSouth:
# 285 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 286 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 287 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 288 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 289 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 290 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 291 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
# 292 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 293 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Type: Null follows the route above one step behind Gladion, after a short
# 294 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ hesitation looking at him: (10,4) -> (7,4) -> (7,7). Each tile it enters
# 295 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ was vacated by Gladion at least one step earlier; the player (south of
# 296 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Gladion at (9,5)) is never on this path.
# 297 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_TypeNullFollow:
# 298 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	face_left
# 299 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	delay_16
# 300 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	delay_8
# 301 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 302 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 303 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 304 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 305 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 306 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 307 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
# 308 "data/maps/VioletCity_PokemonCenter/scripts.pory"

# 309 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ Same, following the south route; the player is west of Gladion at (8,4):
# 310 "data/maps/VioletCity_PokemonCenter/scripts.pory"
@ (10,4) -> (9,4) -> (9,5) -> (7,5) -> (7,7).
# 311 "data/maps/VioletCity_PokemonCenter/scripts.pory"
VioletCity_PokemonCenter_Movement_TypeNullFollowViaSouth:
# 312 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	face_left
# 313 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	delay_16
# 314 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	delay_8
# 315 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 316 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 317 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 318 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_left
# 319 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 320 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	walk_down
# 321 "data/maps/VioletCity_PokemonCenter/scripts.pory"
	step_end
