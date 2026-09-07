# 1 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 2 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_MapScripts::
# 3 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.byte 0
# 4 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 5 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Owner::
# 6 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 7 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 8 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
# 9 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
# 10 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
# 11 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
# 12 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 13 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 14 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 15 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 16 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
# 17 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 18 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 19 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
# 20 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem ITEM_SQUIRTBOTTLE
# 21 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
# 22 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 23 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 24 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 25 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 26 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
# 27 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 28 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 29 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
# 30 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 31 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 32 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 33 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 34 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Normal::
# 35 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 36 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 37 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
# 38 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 39 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck
# 40 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 41 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 42 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ Runs after every Squirtbottle/Sudowoodo branch above, so both topics are always
# 43 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
@ covered in the same conversation instead of one hiding the other.
# 44 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_SeasonalPerfumeCheck::
# 45 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_unset FLAG_STARTED_SEASONAL_PERFUME_QUEST, GoldenrodCity_FlowerShop_EventScript_EndConversation
# 46 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkitem ITEM_SEASONAL_PERFUME, 1
# 47 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_FlowerShop_EventScript_EndConversation
# 48 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	showmoneybox 0, 0
# 49 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_SeasonalPerfumeOffer, MSGBOX_YESNO
# 50 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_FlowerShop_EventScript_DeclineSeasonalPerfume
# 51 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkmoney 1000000, 0
# 52 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_FlowerShop_EventScript_NotEnoughForSeasonalPerfume
# 53 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	removemoney 1000000
# 54 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	updatemoneybox 0
# 55 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playse SE_SHOP
# 56 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem ITEM_SEASONAL_PERFUME
# 57 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_SeasonalPerfumeAfterBuy, MSGBOX_DEFAULT
# 58 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	hidemoneybox
# 59 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 60 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 61 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 62 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 63 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_NotEnoughForSeasonalPerfume::
# 64 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_SeasonalPerfumeNotEnoughMoney, MSGBOX_DEFAULT
# 65 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	hidemoneybox
# 66 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 67 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 68 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 69 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 70 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_DeclineSeasonalPerfume::
# 71 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	hidemoneybox
# 72 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 73 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 74 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 75 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 76 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_EndConversation::
# 77 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 78 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 79 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 80 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Floria1::
# 81 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 82 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 83 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Floria3
# 84 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Floria2
# 85 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
# 86 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 87 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 88 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 89 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	
# 90 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Floria2::
# 91 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
# 92 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 93 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 94 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 95 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 96 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_EventScript_Floria3::
# 97 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
# 98 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	closemessage
# 99 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 100 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 101 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 102 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl::
# 103 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 104 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 105 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	dotimebasedevents
# 106 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY, Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry
# 107 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_ImGrowingFlowers, MSGBOX_DEFAULT
# 108 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	random 8
# 109 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	addvar VAR_RESULT, FIRST_BERRY_INDEX
# 110 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem VAR_RESULT
# 111 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
# 112 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY
# 113 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
# 114 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 115 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 116 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 117 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_AlreadyReceivedBerry::
# 118 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
# 119 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 120 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 121 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 122 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_MintOwner::
# 123 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 124 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 125 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_unset FLAG_BADGE04_GET, Route104_PrettyPetalFlowerShop_EventScript_NoSellMints
# 126 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_Mints1, MSGBOX_DEFAULT
# 127 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmessage
# 128 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	pokemart Route104_PrettyPetalFlowerShop_MintShop
# 129 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 130 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 131 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 132 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 133 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_Text_Mints1:
# 134 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Our Nature Mints are back!\n"
# 135 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Have a look!$"
# 136 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 137 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_Text_Mints2:
# 138 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Hi, dear trainer. If you are looking\n"
# 139 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "to buy Nature Mints, you should have\l"
# 140 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "come earlier. I just sold the last one.\n"
# 141 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Come back later.$"
# 142 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 143 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.align 2
# 144 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_MintShop:
# 145 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_SERIOUS_MINT
# 146 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_ADAMANT_MINT
# 147 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_BOLD_MINT
# 148 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_BRAVE_MINT
# 149 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CALM_MINT
# 150 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CAREFUL_MINT
# 151 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GENTLE_MINT
# 152 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_HASTY_MINT
# 153 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_IMPISH_MINT
# 154 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_JOLLY_MINT
# 155 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LAX_MINT
# 156 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LONELY_MINT
# 157 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_MILD_MINT
# 158 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_MODEST_MINT
# 159 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_NAIVE_MINT
# 160 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_NAUGHTY_MINT
# 161 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_QUIET_MINT
# 162 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_RASH_MINT
# 163 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_RELAXED_MINT
# 164 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_SASSY_MINT
# 165 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_TIMID_MINT
# 166 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_NONE
# 167 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 168 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 169 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 170 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_NoSellMints::
# 171 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_Mints2, MSGBOX_DEFAULT
# 172 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 173 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 174 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 175 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_AlreadyMet::
# 176 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_LearnAboutBerries, MSGBOX_YESNO
# 177 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call_if_eq VAR_RESULT, YES, Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries
# 178 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	call_if_eq VAR_RESULT, NO, Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries
# 179 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
# 180 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	end
# 181 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 182 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_ExplainBerries::
# 183 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_BerriesExplanation, MSGBOX_DEFAULT
# 184 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 185 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 186 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
Route104_PrettyPetalFlowerShop_EventScript_DontExplainBerries::
# 187 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox Route104_PrettyPetalFlowerShop_Text_FlowersBringHappiness, MSGBOX_DEFAULT
# 188 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	return
# 189 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 190 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Floria:
# 191 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "When I told my sis about the jiggly\n"
# 192 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "tree, she said it's dangerous.\p"
# 193 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "If I beat Whitney, I wonder if\n"
# 194 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "she'll lend me her water bottle…$"
# 195 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 196 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner1:
# 197 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Apparently, there is an odd tree\n"
# 198 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "on Route 36.\p"
# 199 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "They say it dances when you water\n"
# 200 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "it...\p"
# 201 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Oh, of course not!\p"
# 202 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "This is a flower shop, so we do\n"
# 203 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "have watering cans...\p"
# 204 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "But I cannot let you have one!\n"
# 205 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "It's too dangerous!\p"
# 206 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Well, maybe if you manage to\n"
# 207 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "defeat gym leader Whitney, it\l"
# 208 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "might be okay.$"
# 209 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 210 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner2:
# 211 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Apparently, there is an odd tree\n"
# 212 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "on Route 36.\p"
# 213 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "They say it dances when you water\n"
# 214 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "it...\p"
# 215 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Oh, that's a Plainbadge from\n"
# 216 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "The Goldenrod Gym!\p"
# 217 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Did you defeat Whitney?!\p"
# 218 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Well, then there's nothing to worry\n"
# 219 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "about, is there?\p"
# 220 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "I'll let you use this Squirtbottle\n"
# 221 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "for a while then.\l"
# 222 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "...\p"
# 223 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Oh, never mind. Keep it!$"
# 224 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 225 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner3:
# 226 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "The odd tree is on Route 36.\n"
# 227 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
.string "Please be careful!$"
# 228 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 229 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_Owner4:
# 230 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Lalala lalalala. Have plenty of\n"
# 231 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "water, my lovely!$"
# 232 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 233 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
# 234 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Wow, you beat Whitney? Cool!$"
# 235 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 236 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
# 237 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "So it really was a Pokémon!$"
# 238 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 239 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_SeasonalPerfumeOffer:
# 240 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Your mother asked about our\n"
# 241 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Seasonal Perfume?\p"
# 242 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "It blends scents inspired by\n"
# 243 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "spring, summer, autumn and winter.\l"
# 244 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "It's ¥1,000,000. Would you like it?$"
# 245 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 246 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_SeasonalPerfumeAfterBuy:
# 247 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Thank you! Each scent brings out\n"
# 248 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "a different side of certain\l"
# 249 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "Pokémon. I hope she enjoys it!$"
# 250 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"

# 251 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
GoldenrodCity_FlowerShop_Text_SeasonalPerfumeNotEnoughMoney:
# 252 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
    .string "You'll need more money than that.$"

FlowerShopMulchVendor::
# 256 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 257 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 258 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox FlowerShopMulchVendor_Text_0
# 259 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_BADGE06_GET, FlowerShopMulchVendor_2
# 263 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	pokemart FlowerShopMulches
# 264 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox FlowerShopMulchVendor_Text_2
FlowerShopMulchVendor_1:
# 268 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end

FlowerShopMulchVendor_2:
# 260 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	pokemart FlowerShopMulchesSixBadges
# 261 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox FlowerShopMulchVendor_Text_1
	goto FlowerShopMulchVendor_1


	.align 2
# 272 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
FlowerShopMulches:
# 273 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GRASSY_SEED
# 274 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LUMINOUS_MOSS
# 275 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GROWTH_MULCH
# 276 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_DAMP_MULCH
# 277 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_STABLE_MULCH
# 278 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

	.align 2
# 281 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
FlowerShopMulchesSixBadges:
# 282 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CHILAN_BERRY
# 283 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_OCCA_BERRY
# 284 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_PASSHO_BERRY
# 285 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_WACAN_BERRY
# 286 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_RINDO_BERRY
# 287 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_YACHE_BERRY
# 288 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CHOPLE_BERRY
# 289 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_KEBIA_BERRY
# 290 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_SHUCA_BERRY
# 291 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_COBA_BERRY
# 292 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_PAYAPA_BERRY
# 293 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_TANGA_BERRY
# 294 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_CHARTI_BERRY
# 295 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_KASIB_BERRY
# 296 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_HABAN_BERRY
# 297 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_COLBUR_BERRY
# 298 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_BABIRI_BERRY
# 299 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_ROSELI_BERRY
# 300 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GRASSY_SEED
# 301 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_LUMINOUS_MOSS
# 302 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GROWTH_MULCH
# 303 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_DAMP_MULCH
# 304 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_STABLE_MULCH
# 305 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

UniversityFlorist::
# 309 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	lock
# 310 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	faceplayer
# 311 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox UniversityFlorist_Text_0
# 315 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	checkspecies SPECIES_SHAYMIN
# 316 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq UniversityFlorist_2
UniversityFlorist_1:
# 319 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end

UniversityFlorist_2:
# 317 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto GiveGracidea
	goto UniversityFlorist_1


GiveGracidea::
# 324 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	goto_if_set FLAG_GOT_GRACIDEA, GiveGracidea_2
# 330 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	playse SE_PIN
# 331 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	applymovement 5, Common_Movement_ExclamationMark
# 332 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitse
# 333 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	waitmovement 0
# 334 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GiveGracidea_Text_1
# 343 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	giveitem ITEM_GRACIDEA
# 344 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GiveGracidea_Text_0
# 346 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	setflag FLAG_GOT_GRACIDEA
# 347 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end

GiveGracidea_2:
# 325 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	msgbox GiveGracidea_Text_0
# 327 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	release
	end


FlowerShopMulchVendor_Text_0:
# 258 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Welcome! Have a look at our inventory!$"

FlowerShopMulchVendor_Text_1:
# 261 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Thank you! Come again!$"

FlowerShopMulchVendor_Text_2:
# 264 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Thank you, we hope to stock some \n"
	.string "rare berries in the near future!$"

UniversityFlorist_Text_0:
# 311 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "I'm studying to become a botanist!\p"
	.string "I strive to learn all about rare\n"
	.string "plants and flowers!$"

GiveGracidea_Text_0:
# 325 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "It is said that Shaymin can\n"
	.string "change its form with that flower.$"

GiveGracidea_Text_1:
# 334 "data/maps/GoldenrodCity_FlowerShop/scripts.pory"
	.string "Oh! That Pokémon you have!\p"
	.string "It really is a Shaymin!\p"
	.string "I have read about it, but I would never\n"
	.string "have even dreamed of seeing it!\p"
	.string "Please, you should try giving it this\n"
	.string "flower.$"
