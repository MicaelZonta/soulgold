@ Marinheiro do cais: volta para Olivine.
AbundanceIsle_EventScript_Sailor::
	lock
	faceplayer
	msgbox AbundanceIsle_Text_SailorOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AbundanceIsle_EventScript_SailorNo
	msgbox AbundanceIsle_Text_SailorGo, MSGBOX_DEFAULT
	closemessage
	warp MAP_OLIVINE_CITY_PORT_OUTSIDE, 11, 5
	waitstate
	release
	end

AbundanceIsle_EventScript_SailorNo::
	msgbox AbundanceIsle_Text_SailorNo, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_Text_SailorOffer:
	.string "Heading back to Olivine?$"

AbundanceIsle_Text_SailorGo:
	.string "Aye aye! Back to the mainland!$"

AbundanceIsle_Text_SailorNo:
	.string "I'll be right here when you're\n"
	.string "ready to go.$"

@ ---- gerado (fase2.py)
AbundanceIsle_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AbundanceIsle_OnFrame
	.byte 0

AbundanceIsle_OnTransition::
	call AbundanceIsle_EventScript_Vis_TEMP_11
	call AbundanceIsle_EventScript_Vis_TEMP_12
	call AbundanceIsle_EventScript_Vis_TEMP_13
	call AbundanceIsle_EventScript_Vis_TEMP_14
	call AbundanceIsle_EventScript_Vis_TEMP_15
	call_if_lt VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_EventScript_Snow
	end

AbundanceIsle_EventScript_Snow::
	setweather WEATHER_SNOW
	return

AbundanceIsle_OnFrame::
	map_script_2 VAR_ABUNDANCE_ISLE_STATE, 0, AbundanceIsle_EventScript_Arrival
	.2byte 0

@ Cena 1: chegada na neve (dispara uma vez: a primeira instrucao muda a var da condicao)
AbundanceIsle_EventScript_Arrival::
	setvar VAR_ABUNDANCE_ISLE_STATE, 1
	lockall
	msgbox AbundanceIsle_Text_Arrival, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

AbundanceIsle_Text_Arrival:
	.string "{SPEAKER NAME_SAILOR}Snow... in harvest season?\n"
	.string "I've sailed here twenty years and\n"
	.string "never seen anything like it.\p"
	.string "Folks say the storms over the\n"
	.string "mountain haven't stopped in weeks.\n"
	.string "Be careful out there.$"

@ Guardas da cratera (cena 3)
AbundanceIsle_EventScript_PlasmaGuard1::
AbundanceIsle_EventScript_PlasmaGuard2::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 2, AbundanceIsle_EventScript_GuardGone
	msgbox AbundanceIsle_Text_GuardStop, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_CRATER_GUARD, AbundanceIsle_Text_GuardBeaten
	msgbox AbundanceIsle_Text_GuardFlee, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_12
	removeobject LOCALID_ABUNDANCE_ISLE_GRUNT_1
	removeobject LOCALID_ABUNDANCE_ISLE_GRUNT_2
	setvar VAR_ABUNDANCE_ISLE_STATE, 2
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

AbundanceIsle_EventScript_GuardGone::
	release
	end

AbundanceIsle_Text_GuardStop:
	.string "{SPEAKER NAME_GRUNT}This crater is off-limits by order\n"
	.string "of Team Plasma!\p"
	.string "Another meddling kid? Fine!\n"
	.string "I'll freeze you out myself!$"
AbundanceIsle_Text_GuardBeaten:
	.string "Grunt: Brr... You're tougher\n"
	.string "than the cold!$"
AbundanceIsle_Text_GuardFlee:
	.string "{SPEAKER NAME_GRUNT}Lord Ghetsis won't be happy...\n"
	.string "Retreat! Retreat!$"

@ N e Hilda junto ao lago (inverno)
AbundanceIsle_EventScript_N::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 2, AbundanceIsle_EventScript_N2
	msgbox AbundanceIsle_Text_N1, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_N2::
	msgbox AbundanceIsle_Text_N2, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_Text_N1:
	.string "{SPEAKER NAME_N}The winds aren't angry.\n"
	.string "They're in pain.\p"
	.string "Someone is keeping this winter\n"
	.string "alive. The cold is coming from the\n"
	.string "crater to the north.$"
AbundanceIsle_Text_N2:
	.string "{SPEAKER NAME_N}The Pokemon of the storm are\n"
	.string "screaming. Please... stop whoever\n"
	.string "is doing this.$"
AbundanceIsle_EventScript_Hilda::
	lock
	faceplayer
	msgbox AbundanceIsle_EventScript_Hilda_Text, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_Hilda_Text:
	.string "{SPEAKER NAME_HILDA}I came with N. When he says the\n"
	.string "Pokemon are hurting...\p"
	.string "...he's never wrong. Let's find\n"
	.string "out what's freezing this island.$"


@ Guardiao do santuario: lenda e Reveal Glass (cena 13)
AbundanceIsle_EventScript_ShrineKeeper::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 8, AbundanceIsle_EventScript_KeeperGlass
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_EventScript_KeeperCalm
	msgbox AbundanceIsle_Text_KeeperLegend, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_KeeperCalm::
	msgbox AbundanceIsle_Text_KeeperCalm, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_KeeperGlass::
	checkitem ITEM_REVEAL_GLASS
	goto_if_eq VAR_RESULT, TRUE, AbundanceIsle_EventScript_KeeperHasGlass
	msgbox AbundanceIsle_Text_KeeperGiveGlass, MSGBOX_DEFAULT
	checkitemspace ITEM_REVEAL_GLASS
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_EventScript_KeeperBagFull
	giveitem ITEM_REVEAL_GLASS
	release
	end

AbundanceIsle_EventScript_KeeperBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_KeeperHasGlass::
	msgbox AbundanceIsle_Text_KeeperHasGlass, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_Text_KeeperLegend:
	.string "{SPEAKER NAME_KEEPER}When wind and thunder quarrel,\n"
	.string "the land goes hungry.\p"
	.string "Long ago, the Wind Genie and the\n"
	.string "Thunder Genie fought over the sky,\n"
	.string "and our fields turned to dust.\p"
	.string "Then the Lord of the Fertile Land\n"
	.string "came down and calmed them both.\n"
	.string "We have given thanks ever since.\p"
	.string "But this winter... the earth can't\n"
	.string "hear our prayers.$"
AbundanceIsle_Text_KeeperCalm:
	.string "{SPEAKER NAME_KEEPER}The snow has stopped! The genies\n"
	.string "fell from the sky, exhausted.\p"
	.string "If both of them stood before the\n"
	.string "shrine together, perhaps the Lord\n"
	.string "of the Fertile Land would return.$"
AbundanceIsle_Text_KeeperGiveGlass:
	.string "{SPEAKER NAME_KEEPER}The Lord of the Fertile Land came\n"
	.string "back! The harvest is saved.\p"
	.string "Take this mirror. It shows the\n"
	.string "true form of the four Forces of\n"
	.string "Nature.$"
AbundanceIsle_Text_KeeperHasGlass:
	.string "{SPEAKER NAME_KEEPER}The Reveal Glass shows the form\n"
	.string "they take for those who believe.$"
AbundanceIsle_EventScript_Landorus::
	lock
	faceplayer
	msgbox AbundanceIsle_EventScript_Landorus_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_LANDORUS, 70, LOCALID_ABUNDANCE_ISLE_LANDORUS, FLAG_TEMP_13, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, AbundanceIsle_EventScript_Landorus_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, AbundanceIsle_EventScript_Landorus_Beaten
	release
	end

AbundanceIsle_EventScript_Landorus_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_13
	removeobject LOCALID_ABUNDANCE_ISLE_LANDORUS
	fadescreenswapbuffers FADE_FROM_BLACK
AbundanceIsle_EventScript_Landorus_Done:
	setflag FLAG_ABUNDANCE_LANDORUS_DONE
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 7, AbundanceIsle_EventScript_Landorus_Advance
	release
	end

AbundanceIsle_EventScript_Landorus_Advance:
	setvar VAR_ABUNDANCE_ISLE_STATE, 8
	return

AbundanceIsle_EventScript_Landorus_Text_Intro:
	.string "The stone fox glows...\n"
	.string "The ground rumbles, and the Lord\n"
	.string "of the Fertile Land descends!$"

@ Despedida no cais (cena 15)
AbundanceIsle_EventScript_NFarewell::
	lock
	faceplayer
	goto_if_eq VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_EventScript_NBye
	msgbox AbundanceIsle_Text_NWait, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_NBye::
	msgbox AbundanceIsle_Text_NBye, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_14
	removeobject LOCALID_ABUNDANCE_ISLE_N_DOCK
	removeobject LOCALID_ABUNDANCE_ISLE_HILDA_DOCK
	setvar VAR_ABUNDANCE_ISLE_STATE, 10
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

AbundanceIsle_Text_NWait:
	.string "{SPEAKER NAME_N}Spring isn't here yet. Can you\n"
	.string "hear it? The island is still\n"
	.string "waiting for someone.$"
AbundanceIsle_Text_NBye:
	.string "{SPEAKER NAME_N}The winds sound happy now.\p"
	.string "Kyurem is waiting in the snow.\n"
	.string "Its emptiness can be filled...\n"
	.string "but not by force.\p"
	.string "Thank you, {PLAYER}. I hope we\n"
	.string "meet again.$"
AbundanceIsle_EventScript_HildaFarewell::
	lock
	faceplayer
	msgbox AbundanceIsle_EventScript_HildaFarewell_Text, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_HildaFarewell_Text:
	.string "{SPEAKER NAME_HILDA}N always leaves like this.\n"
	.string "Don't worry, I'll keep an eye\n"
	.string "on him.$"

AbundanceIsle_EventScript_Seed1::
	lockall
	goto_if_set FLAG_ABUNDANCE_SEED_1, AbundanceIsle_EventScript_Seed1_Empty
	msgbox AbundanceIsle_EventScript_Seed1_Text, MSGBOX_DEFAULT
	setflag FLAG_ABUNDANCE_SEED_1
	removeobject LOCALID_ABUNDANCE_ISLE_SEED_1
	releaseall
	end

AbundanceIsle_EventScript_Seed1_Empty::
	msgbox AbundanceIsle_EventScript_Seed1_TextEmpty, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_EventScript_Seed1_Text:
	.string "A sack of seeds blown here by the\n"
	.string "storm!\p"
	.string "{PLAYER} took the sack to return\n"
	.string "it to the farm.$"
AbundanceIsle_EventScript_Seed1_TextEmpty:
	.string "Nothing here but a few stray\n"
	.string "seeds.$"

AbundanceIsle_EventScript_Farmer::
	lock
	faceplayer
	goto_if_set FLAG_ABUNDANCE_SEEDS_DONE, AbundanceIsle_EventScript_Farmer_Stand
	setvar VAR_0x8000, 0
	call_if_set FLAG_ABUNDANCE_SEED_1, AbundanceIsle_EventScript_Farmer_Inc
	call_if_set FLAG_ABUNDANCE_SEED_2, AbundanceIsle_EventScript_Farmer_Inc
	call_if_set FLAG_ABUNDANCE_SEED_3, AbundanceIsle_EventScript_Farmer_Inc
	call_if_set FLAG_ABUNDANCE_SEED_4, AbundanceIsle_EventScript_Farmer_Inc
	call_if_set FLAG_ABUNDANCE_SEED_5, AbundanceIsle_EventScript_Farmer_Inc
	call_if_set FLAG_ABUNDANCE_SEED_6, AbundanceIsle_EventScript_Farmer_Inc
	goto_if_eq VAR_0x8000, 6, AbundanceIsle_EventScript_Farmer_AllSeeds
	buffernumberstring STR_VAR_1, VAR_0x8000
	msgbox AbundanceIsle_EventScript_Farmer_TextAsk, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_Farmer_Inc::
	addvar VAR_0x8000, 1
	return

AbundanceIsle_EventScript_Farmer_AllSeeds::
	setflag FLAG_ABUNDANCE_SEEDS_DONE
	msgbox AbundanceIsle_EventScript_Farmer_TextThanks, MSGBOX_DEFAULT
	goto AbundanceIsle_EventScript_Farmer_Stand

AbundanceIsle_EventScript_Farmer_Stand::
	goto_if_set FLAG_DAILY_ABUNDANCE_FARM_STAND, AbundanceIsle_EventScript_Farmer_StandDone
	random 3
	goto_if_eq VAR_RESULT, 1, AbundanceIsle_EventScript_Farmer_Lum
	goto_if_eq VAR_RESULT, 2, AbundanceIsle_EventScript_Farmer_Leppa
	setvar VAR_0x8008, ITEM_SITRUS_BERRY
	goto AbundanceIsle_EventScript_Farmer_Give
AbundanceIsle_EventScript_Farmer_Lum::
	setvar VAR_0x8008, ITEM_LUM_BERRY
	goto AbundanceIsle_EventScript_Farmer_Give
AbundanceIsle_EventScript_Farmer_Leppa::
	setvar VAR_0x8008, ITEM_LEPPA_BERRY
AbundanceIsle_EventScript_Farmer_Give::
	msgbox AbundanceIsle_EventScript_Farmer_TextStand, MSGBOX_DEFAULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_EventScript_Farmer_BagFull
	giveitem VAR_0x8008
	setflag FLAG_DAILY_ABUNDANCE_FARM_STAND
	call AbundanceIsle_EventScript_Farmer_SaturdayMulch
	release
	end

AbundanceIsle_EventScript_Farmer_StandDone::
	msgbox AbundanceIsle_EventScript_Farmer_TextStandDone, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_Farmer_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_Farmer_TextAsk:
	.string "{SPEAKER NAME_FARMER}The storm scattered six sacks of\n"
	.string "seed all over the islands!\p"
	.string "You've found {STR_VAR_1} so far.\n"
	.string "Bring them all back and the farm\n"
	.string "can plant again.$"
AbundanceIsle_EventScript_Farmer_TextThanks:
	.string "{SPEAKER NAME_FARMER}All six sacks! The fields will be\n"
	.string "green again by next season.\p"
	.string "Our stand is open again. Come by\n"
	.string "every day for a fresh berry!$"
AbundanceIsle_EventScript_Farmer_TextStand:
	.string "{SPEAKER NAME_FARMER}Here, today's pick from the\n"
	.string "harvest!$"
AbundanceIsle_EventScript_Farmer_TextStandDone:
	.string "{SPEAKER NAME_FARMER}That's all for today. Come back\n"
	.string "tomorrow!$"

AbundanceIsle_EventScript_HonestStand::
	lock
	faceplayer
	msgbox AbundanceIsle_EventScript_HonestStand_Text, MSGBOX_DEFAULT
	pokemart AbundanceIsle_EventScript_HonestStand_Mart
	msgbox AbundanceIsle_EventScript_HonestStand_TextBye, MSGBOX_DEFAULT
	release
	end

	.align 2
AbundanceIsle_EventScript_HonestStand_Mart:
	.2byte ITEM_MOOMOO_MILK
	.2byte ITEM_LEMONADE
	.2byte ITEM_SODA_POP
	.2byte ITEM_HONEY
	.2byte ITEM_BIG_MUSHROOM
	.2byte ITEM_TINY_MUSHROOM
	.2byte ITEM_NONE

AbundanceIsle_EventScript_HonestStand_Text:
	.string "{SPEAKER NAME_JESSIE}Welcome to Team Rocket's perfectly\n"
	.string "honest Saturday stand!\p"
	.string "{SPEAKER NAME_JAMES}Everything bought fair and square!\n"
	.string "Mostly. Well, partly.$"
AbundanceIsle_EventScript_HonestStand_TextBye:
	.string "{SPEAKER NAME_JESSIE}Come back next Saturday! We'll\n"
	.string "still be honest... probably.$"

AbundanceIsle_EventScript_Offering::
	lockall
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_ne VAR_RESULT, WEEKDAY_SAT, AbundanceIsle_EventScript_Offering_Weekday
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_EventScript_Offering_Weekday
	goto_if_set FLAG_DAILY_ABUNDANCE_OFFERING, AbundanceIsle_EventScript_Offering_Done
	random 6
	goto_if_eq VAR_RESULT, 1, AbundanceIsle_EventScript_Offering_I1
	goto_if_eq VAR_RESULT, 2, AbundanceIsle_EventScript_Offering_I2
	goto_if_eq VAR_RESULT, 3, AbundanceIsle_EventScript_Offering_I3
	goto_if_eq VAR_RESULT, 4, AbundanceIsle_EventScript_Offering_I4
	goto_if_eq VAR_RESULT, 5, AbundanceIsle_EventScript_Offering_I5
	setvar VAR_0x8008, ITEM_SITRUS_BERRY
	goto AbundanceIsle_EventScript_Offering_Give
AbundanceIsle_EventScript_Offering_I1::
	setvar VAR_0x8008, ITEM_LUM_BERRY
	goto AbundanceIsle_EventScript_Offering_Give
AbundanceIsle_EventScript_Offering_I2::
	setvar VAR_0x8008, ITEM_MIRACLE_SEED
	goto AbundanceIsle_EventScript_Offering_Give
AbundanceIsle_EventScript_Offering_I3::
	setvar VAR_0x8008, ITEM_SWEET_APPLE
	goto AbundanceIsle_EventScript_Offering_Give
AbundanceIsle_EventScript_Offering_I4::
	setvar VAR_0x8008, ITEM_BIG_ROOT
	goto AbundanceIsle_EventScript_Offering_Give
AbundanceIsle_EventScript_Offering_I5::
	setvar VAR_0x8008, ITEM_MOOMOO_MILK
AbundanceIsle_EventScript_Offering_Give::
	msgbox AbundanceIsle_EventScript_Offering_TextSaturday, MSGBOX_DEFAULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_EventScript_Offering_BagFull
	giveitem VAR_0x8008
	setflag FLAG_DAILY_ABUNDANCE_OFFERING
	releaseall
	end

AbundanceIsle_EventScript_Offering_BagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_EventScript_Offering_Done::
	msgbox AbundanceIsle_EventScript_Offering_TextDone, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_EventScript_Offering_Weekday::
	msgbox AbundanceIsle_EventScript_Offering_TextWeekday, MSGBOX_DEFAULT
	releaseall
	end

AbundanceIsle_EventScript_Offering_TextWeekday:
	.string "A small offering stone before the\n"
	.string "shrine.\p"
	.string "On Saturdays, the village leaves the\n"
	.string "first fruits of the harvest here.$"
AbundanceIsle_EventScript_Offering_TextSaturday:
	.string "Fresh fruits of the harvest rest on\n"
	.string "the offering stone.\p"
	.string "The shrine seems to want {PLAYER}\n"
	.string "to take one.$"
AbundanceIsle_EventScript_Offering_TextDone:
	.string "The offering stone is bare. The\n"
	.string "shrine has given enough today.$"

AbundanceIsle_EventScript_Farmer_SaturdayMulch::
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_ne VAR_RESULT, WEEKDAY_SAT, AbundanceIsle_EventScript_Farmer_Return
	random 4
	setvar VAR_0x8008, ITEM_GROWTH_MULCH
	call_if_eq VAR_RESULT, 1, AbundanceIsle_EventScript_Farmer_MulchDamp
	call_if_eq VAR_RESULT, 2, AbundanceIsle_EventScript_Farmer_MulchStable
	call_if_eq VAR_RESULT, 3, AbundanceIsle_EventScript_Farmer_MulchGooey
	msgbox AbundanceIsle_EventScript_Farmer_TextMulch, MSGBOX_DEFAULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_EventScript_Farmer_Return
	giveitem VAR_0x8008
AbundanceIsle_EventScript_Farmer_Return::
	return
AbundanceIsle_EventScript_Farmer_MulchDamp::
	setvar VAR_0x8008, ITEM_DAMP_MULCH
	return
AbundanceIsle_EventScript_Farmer_MulchStable::
	setvar VAR_0x8008, ITEM_STABLE_MULCH
	return
AbundanceIsle_EventScript_Farmer_MulchGooey::
	setvar VAR_0x8008, ITEM_GOOEY_MULCH
	return

AbundanceIsle_EventScript_Farmer_TextMulch:
	.string "{SPEAKER NAME_FARMER}It's Saturday market! Take some\n"
	.string "mulch for your own berries, too.$"

AbundanceIsle_EventScript_FarmerWife::
	msgbox AbundanceIsle_EventScript_FarmerWife_Text, MSGBOX_NPC
	end

AbundanceIsle_EventScript_FarmerWife_Text:
	.string "My husband counts every sack of\n"
	.string "seed twice. Since the storm, he\n"
	.string "counts them three times.$"

