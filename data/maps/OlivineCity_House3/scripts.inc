OlivineCity_House3_MapScripts::
	.byte 0

OlivineCityHouse3_EventScriptFishingGuru::
	lock
	faceplayer
	checkitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, TRUE, OlivineCityHouse3_EventScriptFishingGuru2
	msgbox OlivineCity_Text_OfferGoodRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineCityHouse3_EventScriptFishingGuruRefused
	msgbox OlivineCity_Text_GiveGoodRod, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	msgbox OlivineCity_Text_GaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuru2::
	msgbox OlivineCity_Text_HaveGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCityHouse3_EventScriptFishingGuruRefused::
	msgbox OlivineCity_Text_DontWantGoodRod, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_OfferGoodRod:
	.string "Olivine is on the sea!\p"
	.string "And if it's on the sea, there\n"
	.string "are bound to be fish!\p"
	.string "I've fished here for 30 years.\p"
	.string "Would you like to face the sea\n"
	.string "and try your hand at fishing?$"

OlivineCity_Text_GiveGoodRod:
	.string "Ah, hahah! We have ourselves\n"
	.string "a new angler in the making!$"

OlivineCity_Text_GaveGoodRod:
	.string "Fish aren't only found in the\n"
	.string "sea--they're wherever there's\l"
	.string "water.\p"
	.string "By the way, your Pokédex shows\n"
	.string "fishing groups for Pokémon.\p"
	.string "Different spots may contain\n"
	.string "similar fish types.$"

OlivineCity_Text_DontWantGoodRod:
	.string "Whaaat? You don't like to fish!?\n"
	.string "That's incomprehensible!$"

OlivineCity_Text_HaveGoodRod:
	.string "How are things?\n"
	.string "Did you land the big one?$"

@ Voltorb in-game trade, moved here from OlivineCity_House1 when that house
@ became Looker and Anabel's (Rift Missions). FLAG_OLIVINE_NPC_TRADE_COMPLETED
@ is still the state of the trade, so an in-progress save keeps working.
Olivine_VoltorbTrade::
	lock
	faceplayer
	goto_if_set FLAG_OLIVINE_NPC_TRADE_COMPLETED, Olivine_VoltorbTrade_2
	ingame_trade INGAME_TRADE_VOLTORB, Olivine_VoltorbTrade_Text_1, VoltorbTrade_Declined, VoltorbTrade_NotRequested, Olivine_VoltorbTrade_Text_2
	setflag FLAG_OLIVINE_NPC_TRADE_COMPLETED
Olivine_VoltorbTrade_1:
	release
	end

Olivine_VoltorbTrade_2:
	msgbox Olivine_VoltorbTrade_Text_0
	goto Olivine_VoltorbTrade_1

VoltorbTrade_Declined::
	msgbox VoltorbTrade_Declined_Text_0
	release
	end

VoltorbTrade_NotRequested::
	msgbox VoltorbTrade_NotRequested_Text_0
	release
	end

Olivine_VoltorbTrade_Text_0:
	.string "Hi, how is my old Voltorb doing?$"

Olivine_VoltorbTrade_Text_1:
	.string "I collect Pokémon\n"
	.string "Do you have a Mareanie?\l"
	.string "Want to trade it for my\l"
	.string "Hisuian Voltorb?$"

Olivine_VoltorbTrade_Text_2:
	.string "Yay! I got myself a Mareanie!\n"
	.string "Voltorb, you take care!$"

VoltorbTrade_Declined_Text_0:
	.string "You don't want to trade? Aww...$"

VoltorbTrade_NotRequested_Text_0:
	.string "Uh, no, I don't think so.\n"
	.string "That doesn't look like a Mareanie.$"
