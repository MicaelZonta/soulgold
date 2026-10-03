@ ===========================================================================
@ Berry Master's garden: the line banks (plan part 9, REI_DA_COLHEITA.md
@ section 14.4). GENERATED from the design text by the part-9 generator and
@ then kept by hand: edit here, measure with
@     python3 .claude/skills/nomear-falante/medir_linha.py data/scripts/berry_garden_lines.inc
@
@ Each <Bank>Line is `call`ed: it picks the line of the day (GardenLine_Pick,
@ VAR_DAYS % N, N = 4/7/10 by hearts or 10 without), shows it and returns.
@ Lines are in the design's order: 1-4 always, 5-7 from 5 hearts, 8-10 from 12.
@ Used by Route30 and Route30_House (Bram and Laurel run the same scripts on
@ both maps), so nothing here uses a LOCALID. One person talking: no name box
@ (the maps' convention); Pokemon cries keep theirs.
@ ===========================================================================
@ A. Bram, morning, in the garden, after the gift
BerryGarden_EventScript_BramMorningLine::
	setvar VAR_0x8004, GARDEN_HEARTS_BRAM
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_BramMorning1
	case 2, BerryGarden_EventScript_BramMorning2
	case 3, BerryGarden_EventScript_BramMorning3
	case 4, BerryGarden_EventScript_BramMorning4
	case 5, BerryGarden_EventScript_BramMorning5
	case 6, BerryGarden_EventScript_BramMorning6
	case 7, BerryGarden_EventScript_BramMorning7
	case 8, BerryGarden_EventScript_BramMorning8
	case 9, BerryGarden_EventScript_BramMorning9
	msgbox BerryGarden_Text_BramMorning0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning1::
	msgbox BerryGarden_Text_BramMorning1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning2::
	msgbox BerryGarden_Text_BramMorning2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning3::
	msgbox BerryGarden_Text_BramMorning3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning4::
	msgbox BerryGarden_Text_BramMorning4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning5::
	msgbox BerryGarden_Text_BramMorning5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning6::
	msgbox BerryGarden_Text_BramMorning6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning7::
	msgbox BerryGarden_Text_BramMorning7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning8::
	msgbox BerryGarden_Text_BramMorning8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramMorning9::
	msgbox BerryGarden_Text_BramMorning9, MSGBOX_DEFAULT
	return

@ B. Bram, afternoon, at home, sorting seeds
BerryGarden_EventScript_BramHomeLine::
	setvar VAR_0x8004, GARDEN_HEARTS_BRAM
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_BramHome1
	case 2, BerryGarden_EventScript_BramHome2
	case 3, BerryGarden_EventScript_BramHome3
	case 4, BerryGarden_EventScript_BramHome4
	case 5, BerryGarden_EventScript_BramHome5
	case 6, BerryGarden_EventScript_BramHome6
	case 7, BerryGarden_EventScript_BramHome7
	case 8, BerryGarden_EventScript_BramHome8
	case 9, BerryGarden_EventScript_BramHome9
	msgbox BerryGarden_Text_BramHome0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome1::
	msgbox BerryGarden_Text_BramHome1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome2::
	msgbox BerryGarden_Text_BramHome2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome3::
	msgbox BerryGarden_Text_BramHome3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome4::
	msgbox BerryGarden_Text_BramHome4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome5::
	msgbox BerryGarden_Text_BramHome5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome6::
	msgbox BerryGarden_Text_BramHome6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome7::
	msgbox BerryGarden_Text_BramHome7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome8::
	msgbox BerryGarden_Text_BramHome8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramHome9::
	msgbox BerryGarden_Text_BramHome9, MSGBOX_DEFAULT
	return

@ R. Bram hands over the day's Berries (morning or afternoon)
BerryGarden_EventScript_BramGiftLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_BramGift1
	case 2, BerryGarden_EventScript_BramGift2
	case 3, BerryGarden_EventScript_BramGift3
	case 4, BerryGarden_EventScript_BramGift4
	case 5, BerryGarden_EventScript_BramGift5
	case 6, BerryGarden_EventScript_BramGift6
	case 7, BerryGarden_EventScript_BramGift7
	case 8, BerryGarden_EventScript_BramGift8
	case 9, BerryGarden_EventScript_BramGift9
	msgbox BerryGarden_Text_BramGift0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift1::
	msgbox BerryGarden_Text_BramGift1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift2::
	msgbox BerryGarden_Text_BramGift2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift3::
	msgbox BerryGarden_Text_BramGift3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift4::
	msgbox BerryGarden_Text_BramGift4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift5::
	msgbox BerryGarden_Text_BramGift5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift6::
	msgbox BerryGarden_Text_BramGift6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift7::
	msgbox BerryGarden_Text_BramGift7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift8::
	msgbox BerryGarden_Text_BramGift8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_BramGift9::
	msgbox BerryGarden_Text_BramGift9, MSGBOX_DEFAULT
	return

@ D. Laurel, morning, at home
BerryGarden_EventScript_LaurelMorningLine::
	setvar VAR_0x8004, GARDEN_HEARTS_LAUREL
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_LaurelMorning1
	case 2, BerryGarden_EventScript_LaurelMorning2
	case 3, BerryGarden_EventScript_LaurelMorning3
	case 4, BerryGarden_EventScript_LaurelMorning4
	case 5, BerryGarden_EventScript_LaurelMorning5
	case 6, BerryGarden_EventScript_LaurelMorning6
	case 7, BerryGarden_EventScript_LaurelMorning7
	case 8, BerryGarden_EventScript_LaurelMorning8
	case 9, BerryGarden_EventScript_LaurelMorning9
	msgbox BerryGarden_Text_LaurelMorning0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning1::
	msgbox BerryGarden_Text_LaurelMorning1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning2::
	msgbox BerryGarden_Text_LaurelMorning2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning3::
	msgbox BerryGarden_Text_LaurelMorning3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning4::
	msgbox BerryGarden_Text_LaurelMorning4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning5::
	msgbox BerryGarden_Text_LaurelMorning5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning6::
	msgbox BerryGarden_Text_LaurelMorning6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning7::
	msgbox BerryGarden_Text_LaurelMorning7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning8::
	msgbox BerryGarden_Text_LaurelMorning8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelMorning9::
	msgbox BerryGarden_Text_LaurelMorning9, MSGBOX_DEFAULT
	return

@ E. Laurel, afternoon (garden; at home on weekends)
BerryGarden_EventScript_LaurelDayLine::
	setvar VAR_0x8004, GARDEN_HEARTS_LAUREL
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_LaurelDay1
	case 2, BerryGarden_EventScript_LaurelDay2
	case 3, BerryGarden_EventScript_LaurelDay3
	case 4, BerryGarden_EventScript_LaurelDay4
	case 5, BerryGarden_EventScript_LaurelDay5
	case 6, BerryGarden_EventScript_LaurelDay6
	case 7, BerryGarden_EventScript_LaurelDay7
	case 8, BerryGarden_EventScript_LaurelDay8
	case 9, BerryGarden_EventScript_LaurelDay9
	msgbox BerryGarden_Text_LaurelDay0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay1::
	msgbox BerryGarden_Text_LaurelDay1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay2::
	msgbox BerryGarden_Text_LaurelDay2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay3::
	msgbox BerryGarden_Text_LaurelDay3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay4::
	msgbox BerryGarden_Text_LaurelDay4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay5::
	msgbox BerryGarden_Text_LaurelDay5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay6::
	msgbox BerryGarden_Text_LaurelDay6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay7::
	msgbox BerryGarden_Text_LaurelDay7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay8::
	msgbox BerryGarden_Text_LaurelDay8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelDay9::
	msgbox BerryGarden_Text_LaurelDay9, MSGBOX_DEFAULT
	return

@ F. Laurel, night, the notebook: STR_VAR_1 = new Berry, 2 and 3 = parents
BerryGarden_EventScript_LaurelRecipeLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_LaurelRecipe1
	case 2, BerryGarden_EventScript_LaurelRecipe2
	case 3, BerryGarden_EventScript_LaurelRecipe3
	case 4, BerryGarden_EventScript_LaurelRecipe4
	case 5, BerryGarden_EventScript_LaurelRecipe5
	case 6, BerryGarden_EventScript_LaurelRecipe6
	case 7, BerryGarden_EventScript_LaurelRecipe7
	case 8, BerryGarden_EventScript_LaurelRecipe8
	case 9, BerryGarden_EventScript_LaurelRecipe9
	msgbox BerryGarden_Text_LaurelRecipe0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe1::
	msgbox BerryGarden_Text_LaurelRecipe1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe2::
	msgbox BerryGarden_Text_LaurelRecipe2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe3::
	msgbox BerryGarden_Text_LaurelRecipe3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe4::
	msgbox BerryGarden_Text_LaurelRecipe4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe5::
	msgbox BerryGarden_Text_LaurelRecipe5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe6::
	msgbox BerryGarden_Text_LaurelRecipe6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe7::
	msgbox BerryGarden_Text_LaurelRecipe7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe8::
	msgbox BerryGarden_Text_LaurelRecipe8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_LaurelRecipe9::
	msgbox BerryGarden_Text_LaurelRecipe9, MSGBOX_DEFAULT
	return

@ G. Tilly, weekend afternoons, the stall (before the shop)
BerryGarden_EventScript_TillyStallLine::
	setvar VAR_0x8004, GARDEN_HEARTS_TILLY
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_TillyStall1
	case 2, BerryGarden_EventScript_TillyStall2
	case 3, BerryGarden_EventScript_TillyStall3
	case 4, BerryGarden_EventScript_TillyStall4
	case 5, BerryGarden_EventScript_TillyStall5
	case 6, BerryGarden_EventScript_TillyStall6
	case 7, BerryGarden_EventScript_TillyStall7
	case 8, BerryGarden_EventScript_TillyStall8
	case 9, BerryGarden_EventScript_TillyStall9
	msgbox BerryGarden_Text_TillyStall0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall1::
	msgbox BerryGarden_Text_TillyStall1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall2::
	msgbox BerryGarden_Text_TillyStall2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall3::
	msgbox BerryGarden_Text_TillyStall3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall4::
	msgbox BerryGarden_Text_TillyStall4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall5::
	msgbox BerryGarden_Text_TillyStall5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall6::
	msgbox BerryGarden_Text_TillyStall6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall7::
	msgbox BerryGarden_Text_TillyStall7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall8::
	msgbox BerryGarden_Text_TillyStall8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_TillyStall9::
	msgbox BerryGarden_Text_TillyStall9, MSGBOX_DEFAULT
	return

@ P. A pest comes out of a garden plot (narration; random, several a day)
BerryGarden_EventScript_PestLine::
	random 10
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_Pest1
	case 2, BerryGarden_EventScript_Pest2
	case 3, BerryGarden_EventScript_Pest3
	case 4, BerryGarden_EventScript_Pest4
	case 5, BerryGarden_EventScript_Pest5
	case 6, BerryGarden_EventScript_Pest6
	case 7, BerryGarden_EventScript_Pest7
	case 8, BerryGarden_EventScript_Pest8
	case 9, BerryGarden_EventScript_Pest9
	msgbox BerryGarden_Text_Pest0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest1::
	msgbox BerryGarden_Text_Pest1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest2::
	msgbox BerryGarden_Text_Pest2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest3::
	msgbox BerryGarden_Text_Pest3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest4::
	msgbox BerryGarden_Text_Pest4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest5::
	msgbox BerryGarden_Text_Pest5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest6::
	msgbox BerryGarden_Text_Pest6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest7::
	msgbox BerryGarden_Text_Pest7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest8::
	msgbox BerryGarden_Text_Pest8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Pest9::
	msgbox BerryGarden_Text_Pest9, MSGBOX_DEFAULT
	return

@ H. Bugsy, Tuesday and Thursday afternoons
BerryGarden_EventScript_BugsyLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_Bugsy1
	case 2, BerryGarden_EventScript_Bugsy2
	case 3, BerryGarden_EventScript_Bugsy3
	case 4, BerryGarden_EventScript_Bugsy4
	case 5, BerryGarden_EventScript_Bugsy5
	case 6, BerryGarden_EventScript_Bugsy6
	case 7, BerryGarden_EventScript_Bugsy7
	case 8, BerryGarden_EventScript_Bugsy8
	case 9, BerryGarden_EventScript_Bugsy9
	msgbox BerryGarden_Text_Bugsy0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy1::
	msgbox BerryGarden_Text_Bugsy1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy2::
	msgbox BerryGarden_Text_Bugsy2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy3::
	msgbox BerryGarden_Text_Bugsy3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy4::
	msgbox BerryGarden_Text_Bugsy4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy5::
	msgbox BerryGarden_Text_Bugsy5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy6::
	msgbox BerryGarden_Text_Bugsy6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy7::
	msgbox BerryGarden_Text_Bugsy7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy8::
	msgbox BerryGarden_Text_Bugsy8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Bugsy9::
	msgbox BerryGarden_Text_Bugsy9, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Who says which bank (section 14.3: first match wins)
@   1. a story scene (parts 12+)
@   2. a reaction - only on the FIRST talk of the day (GardenHearts_Talk said
@      TRUE, kept by the caller in VAR_0x800B), except Bram's news, which is
@      told on the next talk whenever it is
@   3. the line of the day
@ Every reaction script returns VAR_RESULT = TRUE if it said something.
@ Reactions about the Pokemon walking behind the player (Laurel: Grass, Tilly:
@ Bug) only come one day a week, or whoever always leads with the same one
@ would never hear the bank on a first talk.
@ ---------------------------------------------------------------------------

@ Bram, after the day's gift: the garden in the morning, seeds in the afternoon.
BerryGarden_EventScript_BramChat::
	goto_if_eq VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_MORNING, BerryGarden_EventScript_BramMorningLine
	goto BerryGarden_EventScript_BramHomeLine

@ Bram's news first (it waits for him: first garden harvest, a Berry new to
@ the Book that grew in the garden), then the morning reactions of section
@ 14.4 A. Not on the tutorial visit (the caller skips it).
BerryGarden_EventScript_BramReaction::
	@ The story (part 12, data/scripts/berry_garden_story.inc), then Klara's
	@ morning (part 11, data/scripts/berry_garden.inc).
	call BerryGarden_EventScript_BramStoryLine
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_BramReactionEnd
	call BerryGarden_EventScript_BramKlaraLine
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_BramReactionEnd
	specialvar VAR_RESULT, GardenNews_Take
	goto_if_eq VAR_RESULT, GARDEN_NEWS_FIRST_HARVEST, BerryGarden_EventScript_BramFirstHarvest
	goto_if_eq VAR_RESULT, GARDEN_NEWS_NEW_BERRY, BerryGarden_EventScript_BramNewBerry
	goto_if_ne VAR_0x800B, TRUE, BerryGarden_EventScript_NoReaction
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_MORNING, BerryGarden_EventScript_NoReaction
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_SUN, BerryGarden_EventScript_BramSunday
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_BUGSY_CAME, BerryGarden_EventScript_NoReaction
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, BerryGarden_EventScript_BramBugsyDay
	goto_if_eq VAR_RESULT, WEEKDAY_THU, BerryGarden_EventScript_BramBugsyDay
BerryGarden_EventScript_NoReaction::
	setvar VAR_RESULT, FALSE
	return

BerryGarden_EventScript_BramReactionEnd::
	return

BerryGarden_EventScript_BramFirstHarvest::
	msgbox BerryGarden_Text_BramFirstHarvest, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BramNewBerry::
	bufferitemname STR_VAR_1, VAR_0x8004
	msgbox BerryGarden_Text_BramNewBerry, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BramSunday::
	msgbox BerryGarden_Text_BramSunday, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BramBugsyDay::
	msgbox BerryGarden_Text_BramBugsyDay, MSGBOX_DEFAULT
BerryGarden_EventScript_Reacted::
	setvar VAR_RESULT, TRUE
	return

@ Laurel, morning or afternoon (the night is the notebook, never a reaction).
@ VAR_0x8006 = the weekday for the whole check.
BerryGarden_EventScript_LaurelReaction::
	goto_if_eq VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_NoReaction
	specialvar VAR_0x8006, GetDayOfWeek
	goto_if_ne VAR_0x8006, WEEKDAY_WED, BerryGarden_EventScript_LaurelEmptyBedsCheck
	setvar VAR_0x8004, TYPE_GRASS
	specialvar VAR_RESULT, GardenLead_IsType
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_LaurelGrassLead
BerryGarden_EventScript_LaurelEmptyBedsCheck::
	goto_if_lt VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_BACKYARD, BerryGarden_EventScript_LaurelBreadCheck
	@ Weeds are the player's to pull (part 10: cosmetic, a small bonus).
	specialvar VAR_RESULT, GardenWeeds_Bed
	goto_if_eq VAR_RESULT, 1, BerryGarden_EventScript_LaurelWeedA
	goto_if_eq VAR_RESULT, 2, BerryGarden_EventScript_LaurelWeedB
	specialvar VAR_RESULT, GardenPlots_Planted
	goto_if_eq VAR_RESULT, 0, BerryGarden_EventScript_LaurelEmptyBeds
BerryGarden_EventScript_LaurelBreadCheck::
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_DAY, BerryGarden_EventScript_LaurelTeaserCheck
	goto_if_eq VAR_0x8006, WEEKDAY_SAT, BerryGarden_EventScript_LaurelBreadDay
	goto_if_eq VAR_0x8006, WEEKDAY_SUN, BerryGarden_EventScript_LaurelBreadDay
BerryGarden_EventScript_LaurelTeaserCheck::
	@ Before the League, once a week: the rare Berries she hands out after it.
	goto_if_ne VAR_0x8006, WEEKDAY_MON, BerryGarden_EventScript_NoReaction
	goto_if_set FLAG_SYS_GAME_CLEAR, BerryGarden_EventScript_NoReaction
	msgbox BerryGarden_Text_LaurelRareTeaser, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelGrassLead::
	msgbox BerryGarden_Text_LaurelGrassLead, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelWeedA::
	bufferstring STR_VAR_1, BerryGarden_Text_BedA
	goto BerryGarden_EventScript_LaurelWeed

BerryGarden_EventScript_LaurelWeedB::
	bufferstring STR_VAR_1, BerryGarden_Text_BedB
BerryGarden_EventScript_LaurelWeed::
	msgbox BerryGarden_Text_LaurelWeed, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelEmptyBeds::
	msgbox BerryGarden_Text_LaurelEmptyBeds, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelBreadDay::
	msgbox BerryGarden_Text_LaurelBreadDay, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ Tilly at her stall: a Bug-type behind the player (Sundays), the whole Book.
BerryGarden_EventScript_TillyReaction::
	specialvar VAR_RESULT, BerryLedger_Count
	goto_if_ge VAR_RESULT, BERRY_LEDGER_ALL_GROWN, BerryGarden_EventScript_TillyAllGrown
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_ne VAR_RESULT, WEEKDAY_SUN, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, TYPE_BUG
	specialvar VAR_RESULT, GardenLead_IsType
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	bufferspeciesname STR_VAR_1, VAR_0x8005
	msgbox BerryGarden_Text_TillyBugLead, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_TillyAllGrown::
	msgbox BerryGarden_Text_TillyAllGrown, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ Bugsy has no hearts: his reaction is once per visit (FLAG_TEMP_BUGSY_REACTED).
@ The eight garden-only families all caught first, then the Bug Hotel.
BerryGarden_EventScript_BugsyReaction::
	goto_if_set FLAG_TEMP_BUGSY_REACTED, BerryGarden_EventScript_NoReaction
	setflag FLAG_TEMP_BUGSY_REACTED
	specialvar VAR_RESULT, GardenPests_AllCaught
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_BugsyAllCaught
	goto_if_lt VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_BUG_HOTEL, BerryGarden_EventScript_NoReaction
	msgbox BerryGarden_Text_BugsyHotel, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BugsyAllCaught::
	msgbox BerryGarden_Text_BugsyAllCaught, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ ---------------------------------------------------------------------------
@ Texts
@ ---------------------------------------------------------------------------

BerryGarden_Text_BramMorning0:
	.string "Water before the sun's up and the\n"
	.string "leaves won't burn. My father told me\l"
	.string "that.\p"
	.string "Then he watered at noon every day of\n"
	.string "his life.$"

BerryGarden_Text_BramMorning1:
	.string "You know how you tell a ripe Berry? You\n"
	.string "don't. The Berry tells you.$"

BerryGarden_Text_BramMorning2:
	.string "I talk to the trees. Laurel says it\n"
	.string "doesn't help.\p"
	.string "The trees haven't complained.$"

BerryGarden_Text_BramMorning3:
	.string "Dew on the leaves, sprout. That's the\n"
	.string "garden saying good morning.\p"
	.string "Say it back. ...Out loud. There you go.$"

BerryGarden_Text_BramMorning4:
	.string "My knees know the weather before the\n"
	.string "radio does.\p"
	.string "Today they say “sunny, with a chance of\n"
	.string "Bram sitting down.”$"

BerryGarden_Text_BramMorning5:
	.string "First tree I ever planted was an Oran. I\n"
	.string "was six. Watered it so much it drowned.\p"
	.string "Planted another right on top. That\n"
	.string "one's still out back.$"

BerryGarden_Text_BramMorning6:
	.string "Kurt wants Berries again. I asked what\n"
	.string "for. He said “Balls.”\p"
	.string "Then he hung up on me.$"

BerryGarden_Text_BramMorning7:
	.string "You're here every morning now. Tilly\n"
	.string "asked if you live here.\p"
	.string "I said, “Near enough.”$"

BerryGarden_Text_BramMorning8:
	.string "When the garden was just me, I talked\n"
	.string "to the trees. Now I talk to you.\p"
	.string "The trees were better listeners. Don't\n"
	.string "tell them I said that.$"

BerryGarden_Text_BramMorning9:
	.string "Laurel set out a third cup this morning.\n"
	.string "Didn't say a word about it.\p"
	.string "That one's yours, sprout. That's how\n"
	.string "she says it.$"

BerryGarden_Text_BramHome0:
	.string "Seed day. Sit down. No -- not on those.\p"
	.string "Those are Persim.$"

BerryGarden_Text_BramHome1:
	.string "I've got a seed here I can't name.\n"
	.string "Could be a Wiki. Could be a pebble.\p"
	.string "We'll find out.$"

BerryGarden_Text_BramHome2:
	.string "Every seed in this jar is a tree\n"
	.string "someday. Every one.\p"
	.string "That's what gets me up in the morning.\n"
	.string "That and Laurel.$"

BerryGarden_Text_BramHome3:
	.string "You sort seeds by size, then by shape,\n"
	.string "then by smell.\p"
	.string "Then Laurel comes in and sorts them all\n"
	.string "again.$"

BerryGarden_Text_BramHome4:
	.string "Forty years married. The trick is, she's\n"
	.string "always right, and I'm always hungry.$"

BerryGarden_Text_BramHome5:
	.string "When I was your age I wanted to be a\n"
	.string "Pokémon Trainer.\p"
	.string "Then I grew a tomato. That was that.$"

BerryGarden_Text_BramHome6:
	.string "Tilly asked why the sky is blue. I said,\n"
	.string "“Because the Oran Berries are.”\p"
	.string "She believed me for a whole year.$"

BerryGarden_Text_BramHome7:
	.string "I wrote your name on the seed jar.\n"
	.string "Laurel crossed it out and wrote it\l"
	.string "again, neater.\p"
	.string "That's a compliment, sprout. From her,\n"
	.string "that's a medal.$"

BerryGarden_Text_BramHome8:
	.string "My old man said a farmer's rich if he's\n"
	.string "got more seed than worry.\p"
	.string "Most days I'm rich now. You helped.$"

BerryGarden_Text_BramHome9:
	.string "Want to know a secret? I don't know\n"
	.string "half the Berries in that Book.\p"
	.string "I just nod when Laurel says them.$"

BerryGarden_Text_BramGift0:
	.string "Picked these at dawn, sprout. Still had\n"
	.string "the dew on 'em.\p"
	.string "That's how you know they're good.$"

BerryGarden_Text_BramGift1:
	.string "Here. From the Book. Grow 'em well.$"

BerryGarden_Text_BramGift2:
	.string "Hold out your hands. No -- both hands.\n"
	.string "There.$"

BerryGarden_Text_BramGift3:
	.string "These practically jumped into the\n"
	.string "basket. Take 'em before they jump out.$"

BerryGarden_Text_BramGift4:
	.string "Laurel said give you the good ones.\n"
	.string "These are the good ones.\p"
	.string "The bad ones I ate.$"

BerryGarden_Text_BramGift5:
	.string "Fresh from this morning! Fresher than\n"
	.string "me, anyway.$"

BerryGarden_Text_BramGift6:
	.string "Something for your beds, and something\n"
	.string "for your pocket, in case you get hungry.$"

BerryGarden_Text_BramGift7:
	.string "Wrote these down in the Book twice. Big\n"
	.string "day for these ones.$"

BerryGarden_Text_BramGift8:
	.string "Eh? Oh! Almost forgot. Here.\p"
	.string "Don't tell Tilly, she'll want a cut.$"

BerryGarden_Text_BramGift9:
	.string "For you. Same as every day. Tomorrow\n"
	.string "too. That's a promise, sprout.$"

BerryGarden_Text_LaurelMorning0:
	.string "Sit. Eat. The Berries can wait ten\n"
	.string "minutes.\p"
	.string "He can't, but they can.$"

BerryGarden_Text_LaurelMorning1:
	.string "Toast. No, you don't want jam. That's\n"
	.string "Tilly's jam.\p"
	.string "Nobody wants Tilly's jam.$"

BerryGarden_Text_LaurelMorning2:
	.string "He left at four. He always leaves at\n"
	.string "four.\p"
	.string "I stopped setting an alarm years ago.$"

BerryGarden_Text_LaurelMorning3:
	.string "Wipe your feet. ...The other one too.$"

BerryGarden_Text_LaurelMorning4:
	.string "The kettle's older than you. It\n"
	.string "whistles off-key. I won't replace it.$"

BerryGarden_Text_LaurelMorning5:
	.string "He talks to the trees. I talk to the\n"
	.string "kettle.\p"
	.string "Everyone needs someone who doesn't\n"
	.string "answer back.$"

BerryGarden_Text_LaurelMorning6:
	.string "Where I grew up, breakfast was fish and\n"
	.string "bread and more bread.\p"
	.string "This is better. Don't tell anyone I said\n"
	.string "so.$"

BerryGarden_Text_LaurelMorning7:
	.string "You've got soil under your nails. Good.\p"
	.string "Hands that are too clean don't grow\n"
	.string "anything.$"

BerryGarden_Text_LaurelMorning8:
	.string "Frost on the window. Not real frost.\n"
	.string "Johto frost.\p"
	.string "...I miss real frost. That's all. Eat.$"

BerryGarden_Text_LaurelMorning9:
	.string "I made too much. I always make too much\n"
	.string "now.\p"
	.string "...Take it with you.$"

BerryGarden_Text_LaurelDay0:
	.string "Too much water. Not you. Him.$"

BerryGarden_Text_LaurelDay1:
	.string "Weeds are just plants in the wrong\n"
	.string "place. I'm not sentimental about it.$"

BerryGarden_Text_LaurelDay2:
	.string "You're standing on a sprout.\p"
	.string "...No. The other foot.$"

BerryGarden_Text_LaurelDay3:
	.string "Tilly counts the money. I count the\n"
	.string "Berries.\p"
	.string "Neither of us trusts the other one.$"

BerryGarden_Text_LaurelDay4:
	.string "Freezington had one road and one shop.\n"
	.string "I liked it.\p"
	.string "Don't tell him.$"

BerryGarden_Text_LaurelDay5:
	.string "Plant the sour ones by the pond. They\n"
	.string "like wet feet.\p"
	.string "Like him.$"

BerryGarden_Text_LaurelDay6:
	.string "Forty years I've knelt in this dirt. My\n"
	.string "knees are Johto now.\p"
	.string "The rest of me hasn't decided.$"

BerryGarden_Text_LaurelDay7:
	.string "My grandmother kept a field. Harder soil\n"
	.string "than this.\p"
	.string "She'd have liked you. She didn't like\n"
	.string "anyone.$"

BerryGarden_Text_LaurelDay8:
	.string "You come every day. I noticed. I don't\n"
	.string "say things I notice.\p"
	.string "I'm saying this one.$"

BerryGarden_Text_LaurelDay9:
	.string "When I'm gone, this garden...\p"
	.string "No. Never mind. Pull that weed.$"

BerryGarden_Text_LaurelRecipe0:
	.string "{STR_VAR_1}. {STR_VAR_2} beside\n"
	.string "{STR_VAR_3}.\p"
	.string "Touching, side by side. Not corner to\n"
	.string "corner. People always do corner to\l"
	.string "corner.$"

BerryGarden_Text_LaurelRecipe1:
	.string "The page with the coffee stain.\n"
	.string "{STR_VAR_1}.\p"
	.string "You'll want {STR_VAR_2} next to\n"
	.string "{STR_VAR_3}. I'm not telling you\l"
	.string "twice.$"

BerryGarden_Text_LaurelRecipe2:
	.string "My grandmother's hand. Hard to read.\p"
	.string "...{STR_VAR_2} and {STR_VAR_3}, side\n"
	.string "by side, and you get {STR_VAR_1}.\l"
	.string "Probably.$"

BerryGarden_Text_LaurelRecipe3:
	.string "You want something. Fine.\n"
	.string "{STR_VAR_1}.\p"
	.string "Plant {STR_VAR_2} by {STR_VAR_3}.\n"
	.string "Now let me read.$"

BerryGarden_Text_LaurelRecipe4:
	.string "Here. {STR_VAR_1}.\p"
	.string "{STR_VAR_2}, then {STR_VAR_3} right\n"
	.string "beside it. Don't crowd them. They sulk.$"

BerryGarden_Text_LaurelRecipe5:
	.string "He'd tell you this with a song and a\n"
	.string "dance. I'll just tell you.\p"
	.string "{STR_VAR_2} next to {STR_VAR_3}.\n"
	.string "That's {STR_VAR_1}.$"

BerryGarden_Text_LaurelRecipe6:
	.string "{STR_VAR_1}. I grew one once, in a\n"
	.string "teacup, on a windowsill in Freezington.\p"
	.string "{STR_VAR_2} and {STR_VAR_3}. Side\n"
	.string "by side.$"

BerryGarden_Text_LaurelRecipe7:
	.string "It says here: “{STR_VAR_2} and\n"
	.string "{STR_VAR_3}, touching, make\l"
	.string "{STR_VAR_1}.”\p"
	.string "Somebody underlined it three times. It\n"
	.string "was me.$"

BerryGarden_Text_LaurelRecipe8:
	.string "Sit. No, closer, the lamp's bad.\p"
	.string "{STR_VAR_1}. {STR_VAR_2} beside\n"
	.string "{STR_VAR_3}. There. Go to bed.$"

BerryGarden_Text_LaurelRecipe9:
	.string "You're still up. So am I.\p"
	.string "{STR_VAR_1}: {STR_VAR_2} with\n"
	.string "{STR_VAR_3}. ...I'll tell you tomorrow,\l"
	.string "if you forget.$"

BerryGarden_Text_TillyStall0:
	.string "Welcome to Tilly's Mulch Emporium!\p"
	.string "It's mulch. It's the best mulch.\n"
	.string "Grandpa made it but I named it.$"

BerryGarden_Text_TillyStall1:
	.string "Do you know what Rellor do with mulch?\n"
	.string "They ROLL it.\p"
	.string "I'm going to have ten Rellor. Grandma\n"
	.string "said one.$"

BerryGarden_Text_TillyStall2:
	.string "Today's special is mulch! Yesterday's\n"
	.string "special was ALSO mulch.\p"
	.string "It's a very special shop.$"

BerryGarden_Text_TillyStall3:
	.string "I named a Combee Buzzbelle. She stung\n"
	.string "Grandpa.\p"
	.string "Now she's Buzzbelle the Brave.$"

BerryGarden_Text_TillyStall4:
	.string "Grandma says a good shopkeeper\n"
	.string "doesn't talk too much.\p"
	.string "Grandma's wrong about that. Grandma's\n"
	.string "wrong about ONE thing.$"

BerryGarden_Text_TillyStall5:
	.string "Buy three mulch and you get a sticker!\n"
	.string "I'm out of stickers.\p"
	.string "You get a high five. Up top!$"

BerryGarden_Text_TillyStall6:
	.string "I'm going to be a Bug Catcher. The best\n"
	.string "one. Better than Bugsy.\p"
	.string "Don't tell Bugsy. Actually, tell him.\n"
	.string "He'll laugh.$"

BerryGarden_Text_TillyStall7:
	.string "Grandpa lets me water the Pecha.\n"
	.string "Grandma watches me water the Pecha.\p"
	.string "I think she thinks I'll drown it.$"

BerryGarden_Text_TillyStall8:
	.string "You come every weekend! That makes you\n"
	.string "a regular. Regulars get the good mulch.\p"
	.string "It's the same mulch. But I SAY it's\n"
	.string "good.$"

BerryGarden_Text_TillyStall9:
	.string "When I grow up I'll have a garden next\n"
	.string "to Grandpa's. And you can have one\l"
	.string "next to mine.\p"
	.string "And we'll share the bugs.$"

BerryGarden_Text_Pest0:
	.string "Something is nibbling at the leaves!$"

BerryGarden_Text_Pest1:
	.string "The branches are shaking... there's a\n"
	.string "bug in this tree!$"

BerryGarden_Text_Pest2:
	.string "A tiny face peeks out from between the\n"
	.string "Berries!$"

BerryGarden_Text_Pest3:
	.string "Crunch. Crunch. Crunch. Somebody's\n"
	.string "having breakfast!$"

BerryGarden_Text_Pest4:
	.string "A trail of bitten leaves leads straight\n"
	.string "into the tree!$"

BerryGarden_Text_Pest5:
	.string "The whole tree is buzzing!$"

BerryGarden_Text_Pest6:
	.string "Something drops out of the branches,\n"
	.string "hugging a Berry!$"

BerryGarden_Text_Pest7:
	.string "Two little eyes are glowing between the\n"
	.string "leaves!$"

BerryGarden_Text_Pest8:
	.string "Someone got here before you -- and\n"
	.string "they're still here!$"

BerryGarden_Text_Pest9:
	.string "The Berries are moving. Berries\n"
	.string "shouldn't move.$"

BerryGarden_Text_Bugsy0:
	.string "Every color of Berry calls a different\n"
	.string "bug. I've got a chart.\p"
	.string "It's twelve pages.$"

BerryGarden_Text_Bugsy1:
	.string "Try Stable Mulch on one bed. Watch what\n"
	.string "moves in.\p"
	.string "You'll love him.$"

BerryGarden_Text_Bugsy2:
	.string "Don't swat anything! Everything here\n"
	.string "is somebody's data.$"

BerryGarden_Text_Bugsy3:
	.string "A Volbeat's tail blinks in patterns. I\n"
	.string "think this one's saying “more Berries.”\p"
	.string "Or it's broken.$"

BerryGarden_Text_Bugsy4:
	.string "I've started lying down in the dirt.\n"
	.string "Bugs are less shy at eye level.\p"
	.string "Laurel hates it.$"

BerryGarden_Text_Bugsy5:
	.string "The Scatterbug here have a wing\n"
	.string "pattern I've never seen.\p"
	.string "Your garden is making its own Vivillon!$"

BerryGarden_Text_Bugsy6:
	.string "My Gym Trainers keep asking where I go\n"
	.string "on Tuesdays. I say “fieldwork.”\p"
	.string "They think it's a date.$"

BerryGarden_Text_Bugsy7:
	.string "Combee visit one flower at a time. Your\n"
	.string "red beds get the morning shift.\p"
	.string "The yellow beds get the afternoon.$"

BerryGarden_Text_Bugsy8:
	.string "Kurt says bugs are a waste of good\n"
	.string "Berries.\p"
	.string "Then he asks me what bait catches a\n"
	.string "Heracross. Every time.$"

BerryGarden_Text_Bugsy9:
	.string "When I was little I had a garden like\n"
	.string "this. Well, a flowerpot.\p"
	.string "Well, a flowerpot with one Caterpie in\n"
	.string "it. This is better.$"

BerryGarden_Text_BramFirstHarvest:
	.string "Your first! Hold it up. No -- higher.\p"
	.string "There. Now you're a farmer.$"

BerryGarden_Text_BramNewBerry:
	.string "You grew a {STR_VAR_1}? I've never\n"
	.string "seen one!\p"
	.string "Laurel! LAUREL!$"

BerryGarden_Text_BramSunday:
	.string "Sunday! Tilly's selling out front this\n"
	.string "afternoon.\p"
	.string "Buy something, or she'll follow you to\n"
	.string "Violet.$"

BerryGarden_Text_BramBugsyDay:
	.string "Bugsy's coming today. He brought a\n"
	.string "notebook last time.\p"
	.string "The time before, two.$"

BerryGarden_Text_LaurelGrassLead:
	.string "That one would like it here.\p"
	.string "Let it out sometime.$"

BerryGarden_Text_LaurelEmptyBeds:
	.string "Empty beds. Like an empty table.\p"
	.string "Don't make me look at it.$"

BerryGarden_Text_LaurelBreadDay:
	.string "Bread day. Don't open the oven. Don't\n"
	.string "look at the oven.\p"
	.string "The oven can feel you looking.$"

BerryGarden_Text_LaurelRareTeaser:
	.string "My husband hands out the easy ones.\p"
	.string "I keep the others. They only fruit for\n"
	.string "somebody who knows what they're doing,\l"
	.string "and no offence, dear, but you're still\l"
	.string "carrying a town map.$"

BerryGarden_Text_TillyBugLead:
	.string "Is that a {STR_VAR_1}?! Can I hold it?\p"
	.string "I'm holding it.$"

BerryGarden_Text_TillyAllGrown:
	.string "You grew ALL of them? Even the Kee?\p"
	.string "The Kee is so ugly. I love it.$"

BerryGarden_Text_BugsyHotel:
	.string "The hotel's full! Well, one Combee.\p"
	.string "It's a start.$"

BerryGarden_Text_BugsyAllCaught:
	.string "You found all of them?\p"
	.string "I'm going to have to write a second\n"
	.string "notebook.$"

BerryGarden_Text_LaurelWeed:
	.string "There's a weed in bed {STR_VAR_1}.\n"
	.string "I'm not pulling it.\p"
	.string "It's your bed.$"

BerryGarden_Text_BedA:
	.string "A$"

BerryGarden_Text_BedB:
	.string "B$"

