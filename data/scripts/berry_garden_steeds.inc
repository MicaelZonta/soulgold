@ Berry Master: the steeds' paths (REI_DA_COLHEITA.md section 15, plan parts
@ 14 and 15). VAR_HARVEST_KING 10 -> 12 (white path, Greenfield) and
@ 11 -> 13 (dark path, the Brass Tower memory).

@ ---------------------------------------------------------------- white path
@ Mahogany Gym, after the Glastrier (section 15.4): Pryce heard Molly.
BerryGarden_EventScript_PryceCoat::
	msgbox BerryGarden_Text_PryceCoat, MSGBOX_DEFAULT
	return

BerryGarden_Text_PryceCoat:
	.string "...She said the invitation stands?\p"
	.string "Hm. I'll need a better coat.$"

@ ----------------------------------------------------------------- dark path
BerryGarden_EventScript_WhiteFlash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

@ Burned Tower B1F, after the Spectrier (state 13 with the Shaderoot still in
@ the Bag = Morty's Spell Tag still owed, the same mark as Molly's ice): the
@ player wakes at (16,13), below the ladder, and Morty (17,15) walks up to
@ (17,13), to the player's east. If that scene is ever cut short, Morty gives
@ it in his Gym (BerryGarden_EventScript_MortyHook).
BerryGarden_EventScript_B1FTransition::
	setflag FLAG_TEMP_1
	setvar VAR_TEMP_1, 0
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_SPECTRIER, BerryGarden_EventScript_SteedsEnd
	checkitem ITEM_SHADEROOT_CARROT
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_SteedsEnd
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 16, BerryGarden_EventScript_SteedsEnd
	goto_if_ne VAR_0x8005, 13, BerryGarden_EventScript_SteedsEnd
	clearflag FLAG_TEMP_1
	setvar VAR_TEMP_1, 1
	return

BerryGarden_EventScript_B1FWakeUp::
	setvar VAR_TEMP_1, 2
	lockall
	applymovement LOCALID_BURNEDTOWER_B1F_MORTY, BerryGarden_Movement_MortyUp
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	call BerryGarden_EventScript_MortySpellTag
	releaseall
	end

BerryGarden_Movement_MortyUp:
	walk_up
	walk_up
	face_left
	step_end

BerryGarden_EventScript_B1FMorty::
	msgbox BerryGarden_Text_MortyAfter, MSGBOX_NPC
	end

@ The carrot goes only once the Spell Tag is in the Bag.
BerryGarden_EventScript_MortySpellTag::
	msgbox BerryGarden_Text_MortyWelcome, MSGBOX_DEFAULT
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_MortyBagFull
	removeitem ITEM_SHADEROOT_CARROT
	msgbox BerryGarden_Text_MortyAfter, MSGBOX_DEFAULT
	closemessage
	return

BerryGarden_EventScript_MortyBagFull::
	msgbox BerryGarden_Text_MortyBagFull, MSGBOX_DEFAULT
	closemessage
	return

@ The stone lantern in the Sages' yard, (36,25): Brother Tomo's stone once
@ the Spectrier left the memory with the player (state 13 or later, and not
@ the white path).
BerryGarden_EventScript_TomoStone::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_SPECTRIER, BerryGarden_EventScript_Lantern
	setvar VAR_0x8004, GARDEN_STORY_WHITE_PATH
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_Lantern
	msgbox BerryGarden_Text_TomoStone, MSGBOX_SIGN
	end

BerryGarden_EventScript_Lantern::
	msgbox BerryGarden_Text_Lantern, MSGBOX_SIGN
	end

BerryGarden_Text_MortyWelcome:
	.string "{SPEAKER NAME_MORTY}Welcome back. You were gone three\n"
	.string "minutes.\p"
	.string "The tower's quiet now.\p"
	.string "The spirits used to say something\n"
	.string "walked here at night, hungry. Not\l"
	.string "anymore. Take this. It's from them.$"

BerryGarden_Text_MortyAfter:
	.string "{SPEAKER NAME_MORTY}Eusine went home to write it all down.\n"
	.string "Peonia went home to tell her father.\p"
	.string "I'm staying a while. Someone should\n"
	.string "remember the monk.$"

BerryGarden_Text_MortyBagFull:
	.string "{SPEAKER NAME_MORTY}Your Bag is full. Find me at the Gym\n"
	.string "when you have room.$"

BerryGarden_Text_TomoStone:
	.string "A new stone stands by the lantern:\p"
	.string "“Brother Tomo.\n"
	.string "He fed the ones who had nowhere\l"
	.string "else to go.”$"

BerryGarden_Text_Lantern:
	.string "A stone lantern. The Sages light it\n"
	.string "at dusk.$"
