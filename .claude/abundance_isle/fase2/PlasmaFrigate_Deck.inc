PlasmaFrigate_Deck_EventScript_JessieDeck::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ROCKET_REWARD, PlasmaFrigate_Deck_EventScript_JessieDeck_Done
	msgbox PlasmaFrigate_Deck_EventScript_JessieDeck_Text, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_JESSIE_JAMES, PlasmaFrigate_Deck_EventScript_JessieDeck_TextBeaten
	msgbox PlasmaFrigate_Deck_EventScript_JessieDeck_TextAfter, MSGBOX_DEFAULT
	checkitemspace ITEM_AMULET_COIN
	goto_if_eq VAR_RESULT, FALSE, PlasmaFrigate_Deck_EventScript_JessieDeck_BagFull
	giveitem ITEM_AMULET_COIN
	setflag FLAG_ABUNDANCE_ROCKET_REWARD
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_PLASMA_FRIGATE_DECK_JESSIE
	removeobject LOCALID_PLASMA_FRIGATE_DECK_JAMES
	setvar VAR_ABUNDANCE_ROCKET_STAGE, 3
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

PlasmaFrigate_Deck_EventScript_JessieDeck_Done::
	release
	end

PlasmaFrigate_Deck_EventScript_JessieDeck_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

PlasmaFrigate_Deck_EventScript_JessieDeck_Text:
	.string "{SPEAKER NAME_JESSIE}The Plasma wouldn't buy our\n"
	.string "secrets! So we'll take it out\n"
	.string "on YOU!$"
PlasmaFrigate_Deck_EventScript_JessieDeck_TextBeaten:
	.string "Jessie: Looks like we're blasting\n"
	.string "off again!$"
PlasmaFrigate_Deck_EventScript_JessieDeck_TextAfter:
	.string "{SPEAKER NAME_JAMES}...Fine. Take this. We'd only\n"
	.string "lose it anyway.$"

PlasmaFrigate_Deck_EventScript_Rosa::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_ROSA_REWARD, PlasmaFrigate_Deck_EventScript_Rosa_After
	goto_if_defeated TRAINER_ABUNDANCE_PLASMA_FRIGATE_ENGINE_ROOM_CHIEF, PlasmaFrigate_Deck_EventScript_Rosa_Reward
	special HealPlayerParty
	msgbox PlasmaFrigate_Deck_EventScript_Rosa_TextHint, MSGBOX_DEFAULT
	release
	end

PlasmaFrigate_Deck_EventScript_Rosa_Reward::
	msgbox PlasmaFrigate_Deck_EventScript_Rosa_TextThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_MAX_REVIVE
	goto_if_eq VAR_RESULT, FALSE, PlasmaFrigate_Deck_EventScript_Rosa_BagFull
	giveitem ITEM_MAX_REVIVE
	setflag FLAG_ABUNDANCE_ROSA_REWARD
	release
	end

PlasmaFrigate_Deck_EventScript_Rosa_After::
	special HealPlayerParty
	msgbox PlasmaFrigate_Deck_EventScript_Rosa_TextAfter, MSGBOX_DEFAULT
	release
	end

PlasmaFrigate_Deck_EventScript_Rosa_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

PlasmaFrigate_Deck_EventScript_Rosa_TextHint:
	.string "{SPEAKER NAME_ROSA}Shh! I snuck aboard too. Let me\n"
	.string "heal your team.\p"
	.string "The DNA research is in the engine\n"
	.string "room. A guard blocks the stairs...\n"
	.string "Find a uniform in the cabins!$"
PlasmaFrigate_Deck_EventScript_Rosa_TextThanks:
	.string "{SPEAKER NAME_ROSA}You beat their chief scientist?\n"
	.string "Amazing! Take this, partner.$"
PlasmaFrigate_Deck_EventScript_Rosa_TextAfter:
	.string "{SPEAKER NAME_ROSA}Rest up. I'll keep watch.$"

