FrostfallCrater_B1F_EventScript_Byron::
	lock
	faceplayer
	checkitem ITEM_COMET_SHARD
	goto_if_eq VAR_RESULT, FALSE, FrostfallCrater_B1F_EventScript_Byron_NoShard
	msgbox FrostfallCrater_B1F_EventScript_Byron_TextOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FrostfallCrater_B1F_EventScript_Byron_No
	goto_if_eq VAR_ABUNDANCE_BYRON_TRADES, 1, FrostfallCrater_B1F_EventScript_Byron_T2
	goto_if_eq VAR_ABUNDANCE_BYRON_TRADES, 2, FrostfallCrater_B1F_EventScript_Byron_T3
	setvar VAR_0x8008, ITEM_NEVER_MELT_ICE
	goto FrostfallCrater_B1F_EventScript_Byron_Trade
FrostfallCrater_B1F_EventScript_Byron_T2::
	setvar VAR_0x8008, ITEM_ICICLE_PLATE
	goto FrostfallCrater_B1F_EventScript_Byron_Trade
FrostfallCrater_B1F_EventScript_Byron_T3::
	setvar VAR_0x8008, ITEM_DRAGON_FANG
FrostfallCrater_B1F_EventScript_Byron_Trade::
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, FrostfallCrater_B1F_EventScript_Byron_BagFull
	removeitem ITEM_COMET_SHARD
	giveitem VAR_0x8008
	addvar VAR_ABUNDANCE_BYRON_TRADES, 1
	goto_if_lt VAR_ABUNDANCE_BYRON_TRADES, 3, FrostfallCrater_B1F_EventScript_Byron_End
	setvar VAR_ABUNDANCE_BYRON_TRADES, 0
FrostfallCrater_B1F_EventScript_Byron_End::
	release
	end

FrostfallCrater_B1F_EventScript_Byron_No::
	release
	end

FrostfallCrater_B1F_EventScript_Byron_NoShard::
	msgbox FrostfallCrater_B1F_EventScript_Byron_TextNoShard, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_B1F_EventScript_Byron_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_B1F_EventScript_Byron_TextNoShard:
	.string "{SPEAKER NAME_BYRON}These shards aren't from this\n"
	.string "world. Harder than any steel!\p"
	.string "Find me a Comet Shard from the\n"
	.string "crater and I'll trade you\n"
	.string "something good.$"
FrostfallCrater_B1F_EventScript_Byron_TextOffer:
	.string "{SPEAKER NAME_BYRON}A Comet Shard! Will you trade it\n"
	.string "to me?$"

