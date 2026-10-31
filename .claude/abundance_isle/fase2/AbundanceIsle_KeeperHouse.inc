AbundanceIsle_KeeperHouse_EventScript_Cynthia::
	lock
	faceplayer
	setvar VAR_0x8000, 0
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 2, AbundanceIsle_KeeperHouse_EventScript_Cynthia_Inc
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_KeeperHouse_EventScript_Cynthia_Inc
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 7, AbundanceIsle_KeeperHouse_EventScript_Cynthia_Inc
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_KeeperHouse_EventScript_Cynthia_Inc
	compare VAR_ABUNDANCE_CYNTHIA_SCROLLS, VAR_0x8000
	goto_if_lt AbundanceIsle_KeeperHouse_EventScript_Cynthia_Read
	goto_if_lt VAR_ABUNDANCE_CYNTHIA_SCROLLS, 4, AbundanceIsle_KeeperHouse_EventScript_Cynthia_Wait
	goto_if_defeated TRAINER_ABUNDANCE_CYNTHIA, AbundanceIsle_KeeperHouse_EventScript_Cynthia_After
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextChallenge, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_CYNTHIA, AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextBeaten
	checkitemspace ITEM_SHINY_STONE
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_KeeperHouse_EventScript_Cynthia_BagFull
	giveitem ITEM_SHINY_STONE
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Cynthia_Inc::
	addvar VAR_0x8000, 1
	return

AbundanceIsle_KeeperHouse_EventScript_Cynthia_Read::
	addvar VAR_ABUNDANCE_CYNTHIA_SCROLLS, 1
	goto_if_eq VAR_ABUNDANCE_CYNTHIA_SCROLLS, 1, AbundanceIsle_KeeperHouse_EventScript_Cynthia_S1
	goto_if_eq VAR_ABUNDANCE_CYNTHIA_SCROLLS, 2, AbundanceIsle_KeeperHouse_EventScript_Cynthia_S2
	goto_if_eq VAR_ABUNDANCE_CYNTHIA_SCROLLS, 3, AbundanceIsle_KeeperHouse_EventScript_Cynthia_S3
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS4, MSGBOX_DEFAULT
	release
	end
AbundanceIsle_KeeperHouse_EventScript_Cynthia_S1::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS1, MSGBOX_DEFAULT
	release
	end
AbundanceIsle_KeeperHouse_EventScript_Cynthia_S2::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS2, MSGBOX_DEFAULT
	release
	end
AbundanceIsle_KeeperHouse_EventScript_Cynthia_S3::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS3, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Cynthia_Wait::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextWait, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Cynthia_After::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextAfter, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Cynthia_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS1:
	.string "{SPEAKER NAME_CYNTHIA}I found another scroll in the\n"
	.string "keeper's archive.\p"
	.string "The first scroll: the Wind Genie,\n"
	.string "who carries the rain clouds.$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS2:
	.string "{SPEAKER NAME_CYNTHIA}I found another scroll in the\n"
	.string "keeper's archive.\p"
	.string "The second: the Thunder Genie,\n"
	.string "whose lightning wakes the soil.$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS3:
	.string "{SPEAKER NAME_CYNTHIA}I found another scroll in the\n"
	.string "keeper's archive.\p"
	.string "The third: the Lord of the Fertile\n"
	.string "Land, who calms them both.$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextS4:
	.string "{SPEAKER NAME_CYNTHIA}I found another scroll in the\n"
	.string "keeper's archive.\p"
	.string "The fourth... a visitor from the sea\n"
	.string "who ends the winter. Enamorus!$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextWait:
	.string "{SPEAKER NAME_CYNTHIA}The next scroll is still sealed.\n"
	.string "Come back as the island changes.$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextChallenge:
	.string "{SPEAKER NAME_CYNTHIA}All four scrolls... the island's\n"
	.string "whole myth. Thank you.\p"
	.string "Now, let me see how strong the\n"
	.string "one who lived it has become!$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextBeaten:
	.string "Cynthia: Splendid. Truly.$"
AbundanceIsle_KeeperHouse_EventScript_Cynthia_TextAfter:
	.string "{SPEAKER NAME_CYNTHIA}Myths are how people remember\n"
	.string "what Pokemon taught them.$"

AbundanceIsle_KeeperHouse_EventScript_Wife::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 10, AbundanceIsle_KeeperHouse_EventScript_Wife_Letter
	msgbox AbundanceIsle_KeeperHouse_EventScript_Wife_Text, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Wife_Letter::
	goto_if_set FLAG_ABUNDANCE_N_LETTER, AbundanceIsle_KeeperHouse_EventScript_Wife_LetterRead
	msgbox AbundanceIsle_KeeperHouse_EventScript_Wife_TextLetter, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_N_LETTER
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Wife_LetterRead::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Wife_TextLetterRead, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_KeeperHouse_EventScript_Wife_TextLetterRead:
	.string "That young man writes the\n"
	.string "loveliest letters. Go see Lenora,\n"
	.string "dear!$"
AbundanceIsle_KeeperHouse_EventScript_Wife_Text:
	.string "My husband hasn't slept since the\n"
	.string "snow came. He talks to that\n"
	.string "shrine all night.$"
AbundanceIsle_KeeperHouse_EventScript_Wife_TextLetter:
	.string "A letter came for you, dear.\p"
	.string "“The winds sound happy now. I\n"
	.string "wanted you to know. Lenora found\n"
	.string "something in the old stele...”\p"
	.string "“...go see her when you can. --N”$"

AbundanceIsle_KeeperHouse_EventScript_Apprentice::
	msgbox AbundanceIsle_KeeperHouse_EventScript_Apprentice_Text, MSGBOX_NPC
	end

AbundanceIsle_KeeperHouse_EventScript_Apprentice_Text:
	.string "The Keeper says the shrine\n"
	.string "remembers every harvest.\p"
	.string "I'm supposed to sweep it every\n"
	.string "morning... even in the snow.$"

