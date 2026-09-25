# 1 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 2 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_MapScripts::
# 3 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_FlowerShop_OnTransition
# 4 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.byte 0
# 5 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 6 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Resets the Lillie cutscene's per-visit scratch state every time the player
# 7 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ warps into this map, so stale values left over from unrelated scripts that
# 8 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ also use VAR_TEMP_2/3/4 elsewhere can never block or misfire the trigger.
# 9 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_OnTransition::
# 10 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setvar VAR_TEMP_2, 0
# 11 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setvar VAR_TEMP_3, 0
# 12 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setvar VAR_TEMP_4, 0
# 13 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 14 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 15 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Owner::
# 16 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 17 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 18 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
# 19 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
# 20 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_OwnerLillieWillHandleIt
# 21 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
# 22 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 23 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 24 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 25 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 26 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ The owner no longer hands over the SquirtBottle herself: Lillie delivers it
# 27 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ after their battle (see GoldenrodCity_FlowerShop_EventScript_Lillie below).
# 28 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_OwnerLillieWillHandleIt::
# 29 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 30 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 31 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_OwnerLillieWillHandleIt, MSGBOX_DEFAULT
# 32 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 33 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 34 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 35 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 36 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
# 37 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 38 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 39 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
# 40 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 41 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 42 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 43 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 44 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Normal::
# 45 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 46 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 47 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
# 48 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 49 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 50 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 51 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 52 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Runs after every Squirtbottle/Sudowoodo branch above, so both topics are always
# 53 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ covered in the same conversation instead of one hiding the other.
# 54 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck::
# 55 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_unset FLAG_STARTED_SEASONAL_PERFUME_QUEST, GoldenrodCity_FlowerShop_EventScript_EndConversation
# 56 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkitem ITEM_SEASONAL_PERFUME, 1
# 57 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_FlowerShop_EventScript_EndConversation
# 58 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	showmoneybox 0, 0
# 59 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_SeasonalPerfumeOffer, MSGBOX_YESNO
# 60 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_FlowerShop_EventScript_DeclineSeasonalPerfume
# 61 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkmoney 1000000, 0
# 62 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_FlowerShop_EventScript_NotEnoughForSeasonalPerfume
# 63 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	removemoney 1000000
# 64 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	updatemoneybox 0
# 65 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playse SE_SHOP
# 66 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem ITEM_SEASONAL_PERFUME
# 67 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_SeasonalPerfumeAfterBuy, MSGBOX_DEFAULT
# 68 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	hidemoneybox
# 69 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 70 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 71 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 72 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 73 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_NotEnoughForSeasonalPerfume::
# 74 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_SeasonalPerfumeNotEnoughMoney, MSGBOX_DEFAULT
# 75 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	hidemoneybox
# 76 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 77 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 78 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 79 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 80 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_DeclineSeasonalPerfume::
# 81 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	hidemoneybox
# 82 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 83 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 84 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 85 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 86 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_EndConversation::
# 87 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 88 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 89 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 90 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Floria1::
# 91 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 92 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 93 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Floria3
# 94 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Floria2
# 95 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
# 96 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 97 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 98 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 99 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	
# 100 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Floria2::
# 101 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
# 102 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 103 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 104 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 105 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 106 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Floria3::
# 107 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
# 108 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 109 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 110 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 111 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 112 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl::
# 113 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 114 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 115 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	dotimebasedevents
# 116 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY, Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry
# 117 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_ImGrowingFlowers, MSGBOX_DEFAULT
# 118 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	random 8
# 119 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	addvar VAR_RESULT, FIRST_BERRY_INDEX
# 120 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem VAR_RESULT
# 121 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
# 122 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY
# 123 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
# 124 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 125 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 126 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 127 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry::
# 128 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
# 129 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 130 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 131 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 132 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_MintOwner::
# 133 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 134 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 135 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_unset FLAG_BADGE04_GET, Route104_PrettyPetalFlowerShop_EventScript_NoSellMints
# 136 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_Mints1, MSGBOX_DEFAULT
# 137 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmessage
# 138 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	pokemart Route104_PrettyPetalFlowerShop_MintShop
# 139 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 140 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 141 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 142 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 143 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_Text_Mints1:
# 144 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Our Nature Mints are back!\n"
# 145 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Have a look!$"
# 146 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 147 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_Text_Mints2:
# 148 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Hi, dear trainer. If you are looking\n"
# 149 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "to buy Nature Mints, you should have\l"
# 150 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "come earlier. I just sold the last one.\n"
# 151 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Come back later.$"
# 152 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 153 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.align 2
# 154 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_MintShop:
# 155 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_SERIOUS_MINT
# 156 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_ADAMANT_MINT
# 157 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_BOLD_MINT
# 158 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_BRAVE_MINT
# 159 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CALM_MINT
# 160 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CAREFUL_MINT
# 161 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GENTLE_MINT
# 162 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_HASTY_MINT
# 163 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_IMPISH_MINT
# 164 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_JOLLY_MINT
# 165 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LAX_MINT
# 166 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LONELY_MINT
# 167 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_MILD_MINT
# 168 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_MODEST_MINT
# 169 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_NAIVE_MINT
# 170 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_NAUGHTY_MINT
# 171 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_QUIET_MINT
# 172 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_RASH_MINT
# 173 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_RELAXED_MINT
# 174 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_SASSY_MINT
# 175 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_TIMID_MINT
# 176 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_NONE
# 177 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 178 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 179 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 180 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_NoSellMints::
# 181 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_Mints2, MSGBOX_DEFAULT
# 182 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 183 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 184 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 185 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_AlreadyMet::
# 186 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_LearnAboutBerries, MSGBOX_YESNO
# 187 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call_if_eq VAR_RESULT, YES, Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries
# 188 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call_if_eq VAR_RESULT, NO, Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries
# 189 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 190 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 191 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 192 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries::
# 193 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_BerriesExplanation, MSGBOX_DEFAULT
# 194 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 195 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 196 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries::
# 197 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_FlowersBringHappiness, MSGBOX_DEFAULT
# 198 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 199 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 200 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Floria:
# 201 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "When I told my sis about the jiggly\n"
# 202 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "tree, she said it's dangerous.\p"
# 203 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "If I beat Whitney, I wonder if\n"
# 204 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "she'll lend me her water bottle…$"
# 205 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 206 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner1:
# 207 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Apparently, there is an odd tree\n"
# 208 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "on Route 36.\p"
# 209 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "They say it dances when you water\n"
# 210 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "it...\p"
# 211 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Oh, of course not!\p"
# 212 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "This is a flower shop, so we do\n"
# 213 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "have watering cans...\p"
# 214 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "But I cannot let you have one!\n"
# 215 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "It's too dangerous!\p"
# 216 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Well, maybe if you manage to\n"
# 217 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "defeat gym leader Whitney, it\l"
# 218 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "might be okay.$"
# 219 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 220 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_OwnerLillieWillHandleIt:
# 221 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Apparently, there is an odd tree\n"
# 222 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "on Route 36.\p"
# 223 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "They say it dances when you water\n"
# 224 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "it...\p"
# 225 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Oh, that's a Plainbadge from\n"
# 226 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "The Goldenrod Gym!\p"
# 227 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I've already spoken with Lillie\n"
# 228 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "about the SquirtBottle.\p"
# 229 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "She'll take care of it with you.$"
# 230 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 231 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner3:
# 232 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "The odd tree is on Route 36.\n"
# 233 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Please be careful!$"
# 234 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 235 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner4:
# 236 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Lalala lalalala. Have plenty of\n"
# 237 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "water, my lovely!$"
# 238 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 239 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
# 240 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Wow, you beat Whitney? Cool!$"
# 241 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 242 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
# 243 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "So it really was a Pokémon!$"
# 244 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 245 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_SeasonalPerfumeOffer:
# 246 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Your mother asked about our\n"
# 247 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Seasonal Perfume?\p"
# 248 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "It blends scents inspired by\n"
# 249 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "spring, summer, autumn and winter.\l"
# 250 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "It's ¥1,000,000. Would you like it?$"
# 251 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 252 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_SeasonalPerfumeAfterBuy:
# 253 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Thank you! Each scent brings out\n"
# 254 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "a different side of certain\l"
# 255 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Pokémon. I hope she enjoys it!$"
# 256 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 257 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_SeasonalPerfumeNotEnoughMoney:
# 258 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "You'll need more money than that.$"
# 259 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 260 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ ---------------------------------------------------------------------------
# 261 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Lillie cutscene (post-Whitney SquirtBottle handoff)
# 262 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@
# 263 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   collision-checked tile plan (see data/layouts/GoldenrodCity_FlowerShop):
# 264 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@     Owner/florist (2,4) - unchanged      Lillie home tile (4,4)
# 265 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@     approach stop (6,7)                  player trigger tile (6,8)
# 266 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@     door/warp (6,9)
# 267 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@     Vulpix home tile (3,4)               Vulpix approach stop (5,7)
# 268 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   Lillie's Alolan Vulpix is out of its Poké Ball, shares Lillie's hide flag
# 269 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   (FLAG_RECEIVED_SQUIRTBOTTLE) and trails one step behind her both ways.
# 270 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   Path Lillie walks to approach the player, and later to leave, only
# 271 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   crosses tiles confirmed open in the collision layer; sprite-level
# 272 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   pathing (obstacles, follower behavior) still needs an emulator pass.
# 273 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@
# 274 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ State (all VAR_TEMP_2/3/4 are reset to 0 by GoldenrodCity_FlowerShop_OnTransition
# 275 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ every time this map is entered, so they only ever describe the current visit):
# 276 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   VAR_TEMP_2 - 0 = approach not done yet, 1 = Lillie already walked up to the player
# 277 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   VAR_TEMP_3 - battle outcome captured right after GetBattleOutcome
# 278 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@   VAR_TEMP_4 - 1 = training accepted (win, loss, draw or forfeit), delivery pending
# 279 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ ---------------------------------------------------------------------------
# 280 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 281 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Lillie::
# 282 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_unset FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_LillieBeforeBadge
# 283 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_4, 1, GoldenrodCity_FlowerShop_EventScript_LillieRetryDelivery
# 284 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_2, 1, GoldenrodCity_FlowerShop_EventScript_LillieRetryTraining
# 285 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieTrigger
# 286 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 287 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 288 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieBeforeBadge::
# 289 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 290 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 291 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieBeforeBadge, MSGBOX_DEFAULT
# 292 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 293 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 294 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 295 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 296 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Fired by the coord_event trigger at (6,8), and reused above if the player
# 297 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ instead walks straight up to Lillie and talks to her before ever stepping
# 298 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ on that tile. goto_if_unset/goto_if_set below make the trigger itself
# 299 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ idempotent: stepping on (6,8) again after Whitney but before the item is
# 300 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ received, or after it's already been delivered, is a harmless no-op.
# 301 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieTrigger::
# 302 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_LillieTrigger_Skip
# 303 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_unset FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_LillieTrigger_Skip
# 304 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_2, 1, GoldenrodCity_FlowerShop_EventScript_LillieTrigger_Skip
# 305 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieScene
# 306 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieTrigger_Skip::
# 307 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 308 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 309 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieScene::
# 310 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lockall
# 311 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	turnobject LOCALID_GOLDENROD_FLOWER_SHOP_OWNER, DIR_EAST
# 312 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	turnobject LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, DIR_WEST
# 313 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieSceneFloristTree, MSGBOX_DEFAULT
# 314 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieSuggestsPersuading, MSGBOX_DEFAULT
# 315 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloristOffersBottle, MSGBOX_DEFAULT
# 316 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 317 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 318 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	@ --- Lillie notices the player and hurries over ---
# 319 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playse SE_PIN
# 320 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, Common_Movement_ExclamationMark
# 321 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement 0
# 322 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 323 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, GoldenrodCity_FlowerShop_Movement_LillieApproach
# 324 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement LOCALID_GOLDENROD_FLOWER_SHOP_VULPIX, GoldenrodCity_FlowerShop_Movement_VulpixApproach
# 325 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE
# 326 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement LOCALID_GOLDENROD_FLOWER_SHOP_VULPIX
# 327 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setvar VAR_TEMP_2, 1
# 328 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 329 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 330 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	@ --- Reencounter ---
# 331 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieRecognizesBadge, MSGBOX_DEFAULT
# 332 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieIlexForest, MSGBOX_DEFAULT
# 333 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieRibombeeWind, MSGBOX_DEFAULT
# 334 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 335 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 336 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	@ --- Gladion and the Type: Null ---
# 337 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieGladionViolet, MSGBOX_DEFAULT
# 338 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieTypeNull, MSGBOX_DEFAULT
# 339 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 340 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call GoldenrodCity_FlowerShop_EventScript_CosmogComment
# 341 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 342 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	@ --- Why the SquirtBottle changes hands ---
# 343 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieHeadingNorth, MSGBOX_DEFAULT
# 344 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieAsksFlorist, MSGBOX_DEFAULT
# 345 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloristAgrees, MSGBOX_DEFAULT
# 346 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieChallenge, MSGBOX_DEFAULT
# 347 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 348 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieCheckRoomForTraining
# 349 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 350 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Re-entered manually (VAR_TEMP_2 == 1, VAR_TEMP_4 == 0): the approach and
# 351 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ the delivery permission already happened this visit, only retry the
# 352 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ item-space check and the battle itself.
# 353 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieRetryTraining::
# 354 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lockall
# 355 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	turnobject LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, DIR_SOUTH
# 356 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieRetryChallenge, MSGBOX_DEFAULT
# 357 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 358 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 359 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieCheckRoomForTraining::
# 360 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkitemspace ITEM_SQUIRTBOTTLE, 1
# 361 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_FlowerShop_EventScript_LillieNoRoom
# 362 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 363 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieVulpixPracticing, MSGBOX_DEFAULT
# 364 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieDontHoldBack, MSGBOX_DEFAULT
# 365 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 366 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 367 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 368 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkflag B_FLAG_NO_WHITEOUT
# 369 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	copyvar VAR_TEMP_5, VAR_RESULT
# 370 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag B_FLAG_NO_WHITEOUT
# 371 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setvar VAR_LAST_TALKED, LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE
# 372 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	removefieldmugshot
# 373 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	trainerbattle_no_intro TRAINER_LILLIE_GOLDENROD, GoldenrodCity_FlowerShop_Text_LillieDefeated
# 374 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 375 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT
# 376 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_5, TRUE, GoldenrodCity_FlowerShop_EventScript_LillieKeepWhiteoutOff
# 377 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	clearflag B_FLAG_NO_WHITEOUT
# 378 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieKeepWhiteoutOff::
# 379 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playbgm MUS_HG_LYRA, TRUE
# 380 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 381 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, GoldenrodCity_FlowerShop_EventScript_LilliePlayerWon
# 382 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_LOST, GoldenrodCity_FlowerShop_EventScript_LilliePlayerLost
# 383 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_DREW, GoldenrodCity_FlowerShop_EventScript_LillieDraw
# 384 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_TEMP_3, B_OUTCOME_FORFEITED, GoldenrodCity_FlowerShop_EventScript_LillieForfeit
# 385 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieUnexpectedOutcome
# 386 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 387 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ B_OUTCOME_WON: Lillie's own text (GoldenrodCity_FlowerShop_Text_LillieDefeated)
# 388 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ already played automatically when her Pokémon fainted.
# 389 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LilliePlayerWon::
# 390 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieWonFollowUp1, MSGBOX_DEFAULT
# 391 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieWonFollowUp2, MSGBOX_DEFAULT
# 392 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 393 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieDeliverBottle
# 394 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 395 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LilliePlayerLost::
# 396 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieLost1, MSGBOX_DEFAULT
# 397 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieLost2, MSGBOX_DEFAULT
# 398 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieLost3, MSGBOX_DEFAULT
# 399 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 400 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieDeliverBottle
# 401 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 402 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieDraw::
# 403 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieDraw, MSGBOX_DEFAULT
# 404 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 405 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieDeliverBottle
# 406 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 407 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieForfeit::
# 408 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieForfeit, MSGBOX_DEFAULT
# 409 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 410 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_LillieDeliverBottle
# 411 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 412 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Unknown/link-battle-shaped outcome: heal, restore music and controls,
# 413 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ but do not deliver the item or mark the training as concluded.
# 414 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieUnexpectedOutcome::
# 415 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 416 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	fadedefaultbgm
# 417 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	releaseall
# 418 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 419 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 420 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieDeliverBottle::
# 421 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setvar VAR_TEMP_4, 1
# 422 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 423 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 424 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieRetryDelivery::
# 425 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lockall
# 426 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieGiveBottle, MSGBOX_DEFAULT
# 427 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem ITEM_SQUIRTBOTTLE
# 428 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_FlowerShop_EventScript_LillieGiveItemFailed
# 429 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
# 430 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 431 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	turnobject LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, DIR_WEST
# 432 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieThanksFlorist, MSGBOX_DEFAULT
# 433 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloristDontBattleHere, MSGBOX_DEFAULT
# 434 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	turnobject LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, DIR_SOUTH
# 435 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LilliePartingWords, MSGBOX_DEFAULT
# 436 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 437 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 438 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, GoldenrodCity_FlowerShop_Movement_LillieLeave
# 439 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement LOCALID_GOLDENROD_FLOWER_SHOP_VULPIX, GoldenrodCity_FlowerShop_Movement_VulpixLeave
# 440 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE
# 441 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement LOCALID_GOLDENROD_FLOWER_SHOP_VULPIX
# 442 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playse SE_EXIT
# 443 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	removeobject LOCALID_GOLDENROD_FLOWER_SHOP_VULPIX
# 444 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	removeobject LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE
# 445 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	fadedefaultbgm
# 446 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	releaseall
# 447 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 448 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 449 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Should not happen: checkitemspace already confirmed room before the
# 450 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ battle. If it fails anyway, VAR_TEMP_4 stays 1 so talking to Lillie
# 451 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ again only retries this delivery step, without repeating the battle.
# 452 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieGiveItemFailed::
# 453 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieGiveItemFailed, MSGBOX_DEFAULT
# 454 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 455 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	fadedefaultbgm
# 456 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	releaseall
# 457 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 458 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 459 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_LillieNoRoom::
# 460 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_LillieNoRoom, MSGBOX_DEFAULT
# 461 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 462 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	fadedefaultbgm
# 463 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	releaseall
# 464 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 465 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 466 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Lillie: (4,4) -> (4,5) -> (4,6) -> (5,6) -> (5,7) -> (6,7), facing the
# 467 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ player at (6,8). Every tile on this path is open in the collision layer.
# 468 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Movement_LillieApproach:
# 469 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 470 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 471 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_right
# 472 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 473 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_right
# 474 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	face_down
# 475 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	step_end
# 476 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 477 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Vulpix: (3,4) -> (4,4) -> (4,5) -> (4,6) -> (5,6) -> (5,7), one step
# 478 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ behind Lillie the whole way, ending beside her on her west side.
# 479 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Movement_VulpixApproach:
# 480 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_right
# 481 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 482 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 483 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_right
# 484 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 485 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	face_down
# 486 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	step_end
# 487 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 488 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Lillie: (6,7) -> (6,8) -> door (6,9).
# 489 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Movement_LillieLeave:
# 490 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 491 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 492 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_in_place_down
# 493 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	step_end
# 494 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 495 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Vulpix: (5,7) -> (6,7) -> (6,8), right behind Lillie on the door tile.
# 496 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Movement_VulpixLeave:
# 497 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_right
# 498 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_down
# 499 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	walk_in_place_down
# 500 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	step_end
# 501 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 502 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieBeforeBadge:
# 503 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}I'm just talking with\n"
# 504 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "the shop owner about that odd\l"
# 505 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "tree on Route 36.$"
# 506 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 507 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieSceneFloristTree:
# 508 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Florist: It stops people on\n"
# 509 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "their way to Ecruteak.\p"
# 510 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "A little water makes it\n"
# 511 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "wriggle, but nobody wants to\l"
# 512 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "get too close.$"
# 513 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 514 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieSuggestsPersuading:
# 515 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Then we shouldn't pull\n"
# 516 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "at its branches.\p"
# 517 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "If it can move, perhaps we\n"
# 518 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "can persuade it to move on\l"
# 519 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "its own.$"
# 520 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 521 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloristOffersBottle:
# 522 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Florist: You can take this\n"
# 523 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "SquirtBottle.\p"
# 524 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Just be careful, dear.$"
# 525 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 526 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieRecognizesBadge:
# 527 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}{PLAYER}! You've been\n"
# 528 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "to Whitney's Gym, haven't\l"
# 529 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "you?\p"
# 530 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I recognized the Badge.$"
# 531 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 532 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieIlexForest:
# 533 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}I thought traveling\n"
# 534 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "would mean getting better at\l"
# 535 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "following a map.\p"
# 536 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Then I spent half a morning\n"
# 537 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "in Ilex Forest watching which\l"
# 538 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "flowers Ribombee visited.$"
# 539 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 540 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieRibombeeWind:
# 541 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}She kept returning to\n"
# 542 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "the sheltered flowers whenever\l"
# 543 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "the wind picked up.\p"
# 544 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I was watching the path.\n"
# 545 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "She was watching everything\l"
# 546 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "around us.$"
# 547 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 548 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieGladionViolet:
# 549 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Gladion told me he\n"
# 550 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "met you in Violet.\p"
# 551 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "He said, 'They didn't\n"
# 552 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "hesitate.' From him, that's\l"
# 553 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "practically a speech.$"
# 554 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 555 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieTypeNull:
# 556 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}And you met the\n"
# 557 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Type: Null traveling with\l"
# 558 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "him.\p"
# 559 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "He pretends not to fuss over\n"
# 560 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "it, but he checks on it\l"
# 561 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "whenever he thinks nobody\l"
# 562 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "is looking.$"
# 563 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 564 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieHeadingNorth:
# 565 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Are you heading\n"
# 566 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "north?\p"
# 567 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I promised Mother I'd meet\n"
# 568 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "her before we leave\l"
# 569 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Goldenrod.$"
# 570 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 571 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieAsksFlorist:
# 572 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Would it be all right\n"
# 573 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "if {PLAYER} took the bottle?\p"
# 574 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "We've traveled some of the\n"
# 575 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "same roads.$"
# 576 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 577 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloristAgrees:
# 578 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Florist: Of course. You may\n"
# 579 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "keep it.\p"
# 580 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I'd just like that path\n"
# 581 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "clear again!$"
# 582 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 583 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieChallenge:
# 584 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Then it's yours.\p"
# 585 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "But before you go... could\n"
# 586 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "we have another battle?\p"
# 587 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I want to see how much\n"
# 588 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "we've learned.$"
# 589 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 590 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieRetryChallenge:
# 591 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Shall we try again?$"
# 592 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 593 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieNoRoom:
# 594 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Your Bag looks full.\n"
# 595 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Make room for the bottle\l"
# 596 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "first. I'll be here.$"
# 597 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 598 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieVulpixPracticing:
# 599 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Vulpix and I have\n"
# 600 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "been practicing.\p"
# 601 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "She's started looking back\n"
# 602 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "at me when she sees an\l"
# 603 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "opening.\p"
# 604 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I'm learning not to miss it.$"
# 605 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 606 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieDontHoldBack:
# 607 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Let's take care of\n"
# 608 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "your Pokémon first.\p"
# 609 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "And please don't hold back.\n"
# 610 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I won't, either.$"
# 611 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 612 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieDefeated:
# 613 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "We couldn't quite catch\n"
# 614 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "up... but we kept trying!$"
# 615 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 616 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieWonFollowUp1:
# 617 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}I spent so long\n"
# 618 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "deciding what to do that I\l"
# 619 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "missed some of Vulpix's\l"
# 620 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "signals.\p"
# 621 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I want to get better at\n"
# 622 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "answering her.$"
# 623 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 624 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieWonFollowUp2:
# 625 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}I want to try that\n"
# 626 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "again someday.\p"
# 627 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "After I've worked out a\n"
# 628 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "better answer!$"
# 629 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 630 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieLost1:
# 631 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}We did it...? We\n"
# 632 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "did!\p"
# 633 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Oh, Vulpix, you were\n"
# 634 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "wonderful!$"
# 635 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 636 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieLost2:
# 637 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Sorry! I didn't mean\n"
# 638 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "to get carried away.\p"
# 639 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I kept watching Vulpix\n"
# 640 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "instead of worrying about\l"
# 641 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "every command.\p"
# 642 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "That felt different.$"
# 643 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 644 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieLost3:
# 645 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Thank you for taking\n"
# 646 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "us seriously.\p"
# 647 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Let's get your Pokémon\n"
# 648 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "feeling better.$"
# 649 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 650 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieDraw:
# 651 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}That was close for\n"
# 652 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "both of us.\p"
# 653 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Let's take a moment to look\n"
# 654 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "after everyone.$"
# 655 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 656 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieForfeit:
# 657 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Of course. We can\n"
# 658 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "stop here.\p"
# 659 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Let's look after your\n"
# 660 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Pokémon.$"
# 661 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 662 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieGiveBottle:
# 663 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Here, the\n"
# 664 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "SquirtBottle, just as we\l"
# 665 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "agreed.\p"
# 666 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Try a little water first.\n"
# 667 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Whatever that tree is,\l"
# 668 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "there's no need to frighten\l"
# 669 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "it.$"
# 670 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 671 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieGiveItemFailed:
# 672 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}It looks like there\n"
# 673 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "still isn't room. Let's try\l"
# 674 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "again later.$"
# 675 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 676 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LillieThanksFlorist:
# 677 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}Thank you for your\n"
# 678 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "help.\p"
# 679 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "And for letting us borrow a\n"
# 680 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "little room!$"
# 681 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 682 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloristDontBattleHere:
# 683 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Florist: Just don't make a\n"
# 684 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "habit of battling beside my\l"
# 685 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "flowers!$"
# 686 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 687 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_LilliePartingWords:
# 688 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "{SPEAKER NAME_LILLIE}I'd better find\n"
# 689 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Mother.\p"
# 690 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Tell me what happened when\n"
# 691 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "we meet again, won't you?$"
# 692 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 693 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Optional Sun & Moon callback: Lillie remembers Nebby.
# 694 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Reacts to the first non-egg Cosmog/Cosmoem/Solgaleo/Lunala in the party
# 695 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ (CheckMysteryEggPokemon, the special Elm's Eviolite scene uses). Nothing
# 696 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ else changes: no flag, no var; VAR_RESULT is free at every call site.
# 697 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_CosmogComment::
# 698 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 699 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_NONE, GoldenrodCity_FlowerShop_EventScript_CosmogCommentEnd
# 700 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_RESULT
# 701 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE, Common_Movement_ExclamationMark
# 702 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE
# 703 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, GoldenrodCity_FlowerShop_EventScript_CosmogCommentCosmog
# 704 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, GoldenrodCity_FlowerShop_EventScript_CosmogCommentCosmoem
# 705 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_CosmogLegend, MSGBOX_DEFAULT
# 706 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 707 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 708 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 709 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_CosmogCommentCosmog::
# 710 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Cosmog, MSGBOX_DEFAULT
# 711 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 712 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 713 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 714 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_CosmogCommentCosmoem::
# 715 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_CosmogCosmoem, MSGBOX_DEFAULT
# 716 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 717 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 718 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 719 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_CosmogCommentEnd::
# 720 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 721 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 722 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Cosmog:
# 723 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Oh…! {PLAYER}, is that…\n"
# 724 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "May I see? A Cosmog!\p"
# 725 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "I traveled with a Cosmog once,\n"
# 726 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "in Alola. I called it Nebby.\p"
# 727 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "It never stayed in my bag, no\n"
# 728 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "matter how nicely I asked.\p"
# 729 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "…Yours looks happy with you.\n"
# 730 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "I'm glad.$"
# 731 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 732 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_CosmogCosmoem:
# 733 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Is that… a Cosmoem?\p"
# 734 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "It went quiet and hard as a\n"
# 735 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "shell, didn't it?\p"
# 736 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Nebby did the same. Please\n"
# 737 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "don't worry. It isn't sick.\p"
# 738 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "It's growing. On the inside,\n"
# 739 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "where no one can see.$"
# 740 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 741 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_CosmogLegend:
# 742 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}…A {STR_VAR_1}.\p"
# 743 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "I never thought I would see\n"
# 744 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "one again.\p"
# 745 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Nebby became one too, in\n"
# 746 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Alola. It chose someone brave.\p"
# 747 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "It looks like yours did the\n"
# 748 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "same.$"

FlowerShopMulchVendor::
# 754 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 755 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 756 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox FlowerShopMulchVendor_Text_0
# 757 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_BADGE06_GET, FlowerShopMulchVendor_2
# 761 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	pokemart FlowerShopMulches
# 762 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox FlowerShopMulchVendor_Text_2
FlowerShopMulchVendor_1:
# 766 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end

FlowerShopMulchVendor_2:
# 758 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	pokemart FlowerShopMulchesSixBadges
# 759 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox FlowerShopMulchVendor_Text_1
	goto FlowerShopMulchVendor_1


	.align 2
# 770 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
FlowerShopMulches:
# 771 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GRASSY_SEED
# 772 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LUMINOUS_MOSS
# 773 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GROWTH_MULCH
# 774 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_DAMP_MULCH
# 775 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_STABLE_MULCH
# 776 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

	.align 2
# 779 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
FlowerShopMulchesSixBadges:
# 780 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CHILAN_BERRY
# 781 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_OCCA_BERRY
# 782 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_PASSHO_BERRY
# 783 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_WACAN_BERRY
# 784 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_RINDO_BERRY
# 785 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_YACHE_BERRY
# 786 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CHOPLE_BERRY
# 787 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_KEBIA_BERRY
# 788 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_SHUCA_BERRY
# 789 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_COBA_BERRY
# 790 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_PAYAPA_BERRY
# 791 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_TANGA_BERRY
# 792 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CHARTI_BERRY
# 793 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_KASIB_BERRY
# 794 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_HABAN_BERRY
# 795 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_COLBUR_BERRY
# 796 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_BABIRI_BERRY
# 797 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_ROSELI_BERRY
# 798 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GRASSY_SEED
# 799 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LUMINOUS_MOSS
# 800 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GROWTH_MULCH
# 801 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_DAMP_MULCH
# 802 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_STABLE_MULCH
# 803 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

UniversityFlorist::
# 807 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 808 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 809 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox UniversityFlorist_Text_0
# 813 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkspecies SPECIES_SHAYMIN
# 814 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq UniversityFlorist_2
UniversityFlorist_1:
# 817 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end

UniversityFlorist_2:
# 815 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GiveGracidea
	goto UniversityFlorist_1


GiveGracidea::
# 822 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_GOT_GRACIDEA, GiveGracidea_2
# 828 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playse SE_PIN
# 829 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement 5, Common_Movement_ExclamationMark
# 830 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitse
# 831 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement 0
# 832 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GiveGracidea_Text_1
# 841 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem ITEM_GRACIDEA
# 842 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GiveGracidea_Text_0
# 844 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag FLAG_GOT_GRACIDEA
# 845 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end

GiveGracidea_2:
# 823 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GiveGracidea_Text_0
# 825 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end


FlowerShopMulchVendor_Text_0:
# 756 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Welcome! Have a look at our inventory!$"

FlowerShopMulchVendor_Text_1:
# 759 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Thank you! Come again!$"

FlowerShopMulchVendor_Text_2:
# 762 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Thank you, we hope to stock some \n"
	.string "rare berries in the near future!$"

UniversityFlorist_Text_0:
# 809 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "I'm studying to become a botanist!\p"
	.string "I strive to learn all about rare\n"
	.string "plants and flowers!$"

GiveGracidea_Text_0:
# 823 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "It is said that Shaymin can\n"
	.string "change its form with that flower.$"

GiveGracidea_Text_1:
# 832 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Oh! That Pokémon you have!\p"
	.string "It really is a Shaymin!\p"
	.string "I have read about it, but I would never\n"
	.string "have even dreamed of seeing it!\p"
	.string "Please, you should try giving it this\n"
	.string "flower.$"
