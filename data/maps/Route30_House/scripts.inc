@ ===========================================================================
@ Route 30 - the Berry Master's house.
@
@ The bald man who already lived here and handed out one Cheri Berry has been
@ PROMOTED, not replaced: the game's berry tutorial becomes the game's permanent
@ berry source, on the first route, before the first badge
@ (.claude/KURT_BALL_CRAFT_DESIGN.md section 5).
@
@ Why it matters that this is early: Kurt's recipes cost berries, and berry trees
@ start EMPTY on a New Game (ClearBerryTrees zeroes all 139 slots), so every berry
@ in the game comes from an outside source and is then MULTIPLIED by planting.
@ Two a day from here, dozens of hours before Azalea, is what stops the Ball
@ economy from locking up at the start of the campaign.
@
@ Floor plan (dump_mapa.py Route30_House; y grows DOWNWARD):
@       x= 0 1 2 3 4 5 6 7 8 9 10
@   y=4    . . . W M # # . . . .   M = the Berry Master (4,4)
@   y=5    . . . . . # # . . . .   W = his wife (3,4), NEW
@   y=8    # . . . D . . . . . #   D = the door (4,8)
@ Neither of them ever moves, and neither is south of the player at the door, so
@ the text box covers nobody.
@ ===========================================================================

Route30_House_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route30_House_OnTransition
	.byte 0

@ The garden's day starts wherever the player first shows up (src/berry_garden.c).
Route30_House_OnTransition::
	special GardenRollDay
	end

@ He keeps the one-off Cheri Berry - it is the tutorial and it explains the whole
@ system - and gains a daily gift on top of it.
@ FLAG_GOT_BERRY_ROUTE_30_HOUSE stays exactly what it was: the tutorial marker,
@ NOT the daily gate.
@ FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY already exists and already lives in the
@ daily block, so ClearDailyFlags resets it at the date rollover and this costs no
@ new flag. The Hoenn Berry Master uses FLAG_GARBAGEFLAG as its daily latch, which
@ is a hack; that line is deliberately NOT copied here.
Route30_House_EventScript_BaldMan::
	lock
	faceplayer
	dotimebasedevents
	@ Midnight may have passed with the player in here: no map load, so the
	@ garden's day has to be checked again after the clock (src/berry_garden.c).
	special GardenRollDay
	call_if_unset FLAG_GOT_BERRY_ROUTE_30_HOUSE, Route30_House_EventScript_Tutorial
	@ Idempotent: also fills the Book of a save that did the tutorial before
	@ the Book existed, so the daily draw below is never empty.
	special BerryLedger_RegisterStarters
	call Route30_House_EventScript_BuiltLevel
	call Route30_House_EventScript_Milestones
	call Route30_House_EventScript_Order
	@ The day's gift first - it is what the player came for - and the garden
	@ works last (Route30_House_EventScript_AfterGift), so a reform deal closes
	@ the conversation instead of being followed by "take two".
	goto_if_set FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Route30_House_EventScript_DoneToday
	@ 2 Berries a day, 3 from garden level 2 (src/berry_garden.c).
	specialvar VAR_0x8009, GardenGift_Count
	@ "You came back!" makes no sense in the same conversation as the tutorial.
	call_if_set FLAG_TEMP_1, Route30_House_EventScript_FirstTwoText
	goto_if_set FLAG_TEMP_1, Route30_House_EventScript_GiveDraw
	goto_if_eq VAR_0x8009, 3, Route30_House_EventScript_OfferSeed
	msgbox Route30_House_Text_TakeTwo, MSGBOX_DEFAULT
	goto Route30_House_EventScript_GiveDraw

Route30_House_EventScript_GiveDraw::
	call Route30_House_EventScript_GiveLedgerBerry
	@ The flag is set right after the FIRST Berry, exactly as the Hoenn original
	@ does it: setting it after all of them would let a bag that fills up on a
	@ later one be used to take them all again on the same day.
	setflag FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY
	call Route30_House_EventScript_GiveLedgerBerry
	call_if_eq VAR_0x8009, 3, Route30_House_EventScript_GiveLedgerBerry
	call_if_eq VAR_0x8009, 3, Route30_House_EventScript_PlantThemThreeText
	call_if_ne VAR_0x8009, 3, Route30_House_EventScript_PlantThemText
	goto Route30_House_EventScript_AfterGift

@ Every path of the conversation ends here (except a full bag, which ends on
@ Common_EventScript_ShowBagIsFull): the garden works offer, then goodbye.
Route30_House_EventScript_AfterGift::
	call Route30_House_EventScript_Reform
	closemessage
	release
	end

@ Garden level 2: the day's gift can be one Berry of the player's choosing
@ instead of the draw (section 3.5). Any Berry in the Book but the Enigma; the
@ list is built in C (BerryLedger_BuildSeedMenu) in item order, and the id of
@ each row is the item. No shouldSort: it sorts by id, which is already the
@ order, and with an empty list its count - 1 underflows (scrcmd.c).
@ B or "Surprise me" is the ordinary draw of three.
Route30_House_EventScript_OfferSeed::
	msgbox Route30_House_Text_TakeThree, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, Route30_House_Text_SurpriseMe, Route30_House_Text_OneInMind
	goto_if_ne VAR_RESULT, 1, Route30_House_EventScript_GiveDraw
	msgbox Route30_House_Text_NameIt, MSGBOX_DEFAULT
	special BerryLedger_BuildSeedMenu
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, Route30_House_EventScript_GiveDraw
	copyvar VAR_0x8008, VAR_RESULT
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY
	msgbox Route30_House_Text_GoodPick, MSGBOX_DEFAULT
	giveitem VAR_0x8008
	goto Route30_House_EventScript_AfterGift

@ ---------------------------------------------------------------------------
@ Today's order (section 6; rules in src/berry_garden.c, GardenOrder_*).
@ Drawn in the first conversation of the day and announced then; on later
@ visits Bram reminds once per visit (FLAG_TEMP_7) and takes the Berries the
@ moment the player has them. The pay is asked about BEFORE anything leaves
@ the bag: checkitem -> yesno -> checkitemspace -> removeitem -> pay.
@ VAR_0x8004 Berry, 0x8005 how many, 0x8006 client, 0x8007 discovery,
@ 0x800A "drawn just now". STR_VAR_1 = the Berry (plural), STR_VAR_2 = how many.
@ Not on the tutorial visit (FLAG_TEMP_1): the first order waits for the
@ next visit, so the tutorial ends on the Book and the first two Berries.
@ ---------------------------------------------------------------------------
Route30_House_EventScript_Order::
	goto_if_set FLAG_TEMP_1, Route30_House_EventScript_OrderEnd
	specialvar VAR_0x800A, GardenOrder_Roll
	specialvar VAR_RESULT, GardenOrder_Get
	goto_if_ne VAR_RESULT, GARDEN_ORDER_OPEN, Route30_House_EventScript_OrderEnd
	bufferitemnameplural STR_VAR_1, VAR_0x8004, VAR_0x8005
	buffernumberstring STR_VAR_2, VAR_0x8005
	call_if_eq VAR_0x800A, TRUE, Route30_House_EventScript_OrderAnnounce
	checkitem VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_RESULT, TRUE, Route30_House_EventScript_OrderDeliver
	goto_if_set FLAG_TEMP_7, Route30_House_EventScript_OrderEnd
	setflag FLAG_TEMP_7
	call_if_eq VAR_0x8007, FALSE, Route30_House_EventScript_OrderReminder
	call_if_eq VAR_0x8007, TRUE, Route30_House_EventScript_OrderReminderDiscovery
Route30_House_EventScript_OrderEnd::
	return

Route30_House_EventScript_OrderReminder::
	msgbox Route30_House_Text_OrderReminder, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderReminderDiscovery::
	msgbox Route30_House_Text_OrderReminderDiscovery, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderAnnounce::
	setflag FLAG_TEMP_7
	goto_if_eq VAR_0x8007, TRUE, Route30_House_EventScript_OrderAnnounceDiscovery
	switch VAR_0x8006
	case GARDEN_CLIENT_KURT, Route30_House_EventScript_OrderKurt
	case GARDEN_CLIENT_FLOWER_SHOP, Route30_House_EventScript_OrderFlowerShop
	case GARDEN_CLIENT_NURSE, Route30_House_EventScript_OrderNurse
	case GARDEN_CLIENT_MOOMOO_FARM, Route30_House_EventScript_OrderMoomoo
	case GARDEN_CLIENT_DAY_CARE, Route30_House_EventScript_OrderDayCare
	case GARDEN_CLIENT_BUGSY, Route30_House_EventScript_OrderBugsy
	case GARDEN_CLIENT_THEATER, Route30_House_EventScript_OrderTheater
	case GARDEN_CLIENT_LIGHTHOUSE, Route30_House_EventScript_OrderLighthouse
	case GARDEN_CLIENT_SCHOOL, Route30_House_EventScript_OrderSchool
	case GARDEN_CLIENT_LAUREL, Route30_House_EventScript_OrderLaurel
	return

Route30_House_EventScript_OrderAnnounceDiscovery::
	msgbox Route30_House_Text_OrderDiscovery, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderKurt::
	msgbox Route30_House_Text_OrderKurt, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderFlowerShop::
	msgbox Route30_House_Text_OrderFlowerShop, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderNurse::
	msgbox Route30_House_Text_OrderNurse, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderMoomoo::
	msgbox Route30_House_Text_OrderMoomoo, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderDayCare::
	msgbox Route30_House_Text_OrderDayCare, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderBugsy::
	msgbox Route30_House_Text_OrderBugsy, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderTheater::
	msgbox Route30_House_Text_OrderTheater, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderLighthouse::
	msgbox Route30_House_Text_OrderLighthouse, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderSchool::
	msgbox Route30_House_Text_OrderSchool, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderLaurel::
	msgbox Route30_House_Text_OrderLaurel, MSGBOX_DEFAULT
	return

@ The player has the Berries. The Mulch of the pay must fit before anything is
@ taken; after removeitem, GardenOrder_Pay pays the money and closes the order.
Route30_House_EventScript_OrderDeliver::
	call_if_eq VAR_0x8005, 1, Route30_House_EventScript_OrderHandOverOne
	call_if_ne VAR_0x8005, 1, Route30_House_EventScript_OrderHandOverMany
	goto_if_eq VAR_RESULT, NO, Route30_House_EventScript_OrderEnd
	specialvar VAR_0x8008, GardenOrder_RewardMulch
	checkitemspace VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, Route30_House_EventScript_OrderBagFull
	removeitem VAR_0x8004, VAR_0x8005
	specialvar VAR_RESULT, GardenOrder_Pay
	buffernumberstring STR_VAR_3, VAR_RESULT
	@ Delivery lines rotate with the client (section 14.4 Q, index % 5).
	call_if_eq VAR_0x8006, 0, Route30_House_EventScript_OrderThanks1
	call_if_eq VAR_0x8006, 5, Route30_House_EventScript_OrderThanks1
	call_if_eq VAR_0x8006, 1, Route30_House_EventScript_OrderThanks2
	call_if_eq VAR_0x8006, 6, Route30_House_EventScript_OrderThanks2
	call_if_eq VAR_0x8006, 2, Route30_House_EventScript_OrderThanks3
	call_if_eq VAR_0x8006, 7, Route30_House_EventScript_OrderThanks3
	call_if_eq VAR_0x8006, 3, Route30_House_EventScript_OrderThanks4
	call_if_eq VAR_0x8006, 8, Route30_House_EventScript_OrderThanks4
	call_if_eq VAR_0x8006, 4, Route30_House_EventScript_OrderThanks5
	call_if_eq VAR_0x8006, 9, Route30_House_EventScript_OrderThanks5
	playse SE_SHOP
	msgbox Route30_House_Text_OrderPaid, MSGBOX_DEFAULT
	waitse
	giveitem VAR_0x8008
	return

Route30_House_EventScript_OrderHandOverOne::
	msgbox Route30_House_Text_OrderHandOverOne, MSGBOX_YESNO
	return

Route30_House_EventScript_OrderHandOverMany::
	msgbox Route30_House_Text_OrderHandOver, MSGBOX_YESNO
	return

Route30_House_EventScript_OrderBagFull::
	msgbox Route30_House_Text_OrderBagFull, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderThanks1::
	msgbox Route30_House_Text_OrderThanks1, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderThanks2::
	msgbox Route30_House_Text_OrderThanks2, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderThanks3::
	msgbox Route30_House_Text_OrderThanks3, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderThanks4::
	msgbox Route30_House_Text_OrderThanks4, MSGBOX_DEFAULT
	return

Route30_House_EventScript_OrderThanks5::
	msgbox Route30_House_Text_OrderThanks5, MSGBOX_DEFAULT
	return

Route30_House_EventScript_PlantThemText::
	msgbox Route30_House_Text_PlantThem, MSGBOX_DEFAULT
	return

Route30_House_EventScript_PlantThemThreeText::
	msgbox Route30_House_Text_PlantThemThree, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Garden levels (section 5; rules in src/berry_garden.c, sGardenReforms).
@ Bram offers the next level when the Book is big enough; paid today, built
@ overnight, and he talks about it the next time the player sees him.
@ FLAG_TEMP_4: he already brought the garden up on this visit (no repeating
@ the offer or the "I need help" line every time the player talks to him).
@ ---------------------------------------------------------------------------
Route30_House_EventScript_BuiltLevel::
	specialvar VAR_RESULT, GardenReform_TakeBuiltLevel
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, GARDEN_LEVEL_PROPER, Route30_House_EventScript_BuiltProper
	call_if_eq VAR_0x8008, GARDEN_LEVEL_CHANNEL, Route30_House_EventScript_BuiltChannel
	call_if_eq VAR_0x8008, GARDEN_LEVEL_BUG_HOTEL, Route30_House_EventScript_BuiltBugHotel
	return

Route30_House_EventScript_BuiltProper::
	msgbox Route30_House_Text_BuiltProper, MSGBOX_DEFAULT
	return

Route30_House_EventScript_BuiltChannel::
	msgbox Route30_House_Text_BuiltChannel, MSGBOX_DEFAULT
	return

Route30_House_EventScript_BuiltBugHotel::
	msgbox Route30_House_Text_BuiltBugHotel, MSGBOX_DEFAULT
	return

Route30_House_EventScript_Reform::
	goto_if_set FLAG_TEMP_4, Route30_House_EventScript_ReformEnd
	specialvar VAR_RESULT, GardenReform_Check
	goto_if_eq VAR_RESULT, GARDEN_REFORM_READY, Route30_House_EventScript_ReformOffer
	goto_if_eq VAR_RESULT, GARDEN_REFORM_NEEDS_HELP, Route30_House_EventScript_ReformNeedsHelp
Route30_House_EventScript_ReformEnd::
	return

Route30_House_EventScript_ReformNeedsHelp::
	setflag FLAG_TEMP_4
	msgbox Route30_House_Text_ReformNeedsHelp, MSGBOX_DEFAULT
	return

@ VAR_0x8005 = the level on offer (GardenReform_Check).
Route30_House_EventScript_ReformOffer::
	setflag FLAG_TEMP_4
	goto_if_eq VAR_0x8005, GARDEN_LEVEL_BUG_HOTEL, Route30_House_EventScript_OfferBugHotel
	showmoneybox 0, 0
	@ The offer comes when the Book reaches the size OR LATER: say the real count.
	@ Buffered AFTER showmoneybox: the money box prints the money through
	@ gStringVar1 (PrintMoneyAmount, src/money.c) and would overwrite it.
	specialvar VAR_RESULT, BerryLedger_Count
	buffernumberstring STR_VAR_1, VAR_RESULT
	call_if_eq VAR_0x8005, GARDEN_LEVEL_PROPER, Route30_House_EventScript_AskProper
	call_if_eq VAR_0x8005, GARDEN_LEVEL_CHANNEL, Route30_House_EventScript_AskChannel
	goto_if_eq VAR_RESULT, NO, Route30_House_EventScript_ReformDeclined
	specialvar VAR_RESULT, GardenReform_Pay
	goto_if_eq VAR_RESULT, FALSE, Route30_House_EventScript_ReformNoMoney
	updatemoneybox
	playse SE_SHOP
	waitse
	msgbox Route30_House_Text_ReformPaid, MSGBOX_DEFAULT
	hidemoneybox
	return

Route30_House_EventScript_AskProper::
	msgbox Route30_House_Text_OfferProper, MSGBOX_YESNO
	return

Route30_House_EventScript_AskChannel::
	msgbox Route30_House_Text_OfferChannel, MSGBOX_YESNO
	return

Route30_House_EventScript_ReformDeclined::
	msgbox Route30_House_Text_ReformDeclined, MSGBOX_DEFAULT
	hidemoneybox
	return

Route30_House_EventScript_ReformNoMoney::
	msgbox Route30_House_Text_ReformNoMoney, MSGBOX_DEFAULT
	hidemoneybox
	return

@ Bugsy builds the Bug Hotel himself: nothing to pay, so no money box.
Route30_House_EventScript_OfferBugHotel::
	msgbox Route30_House_Text_OfferBugHotel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route30_House_EventScript_BugHotelDeclined
	specialvar VAR_RESULT, GardenReform_Pay
	msgbox Route30_House_Text_ReformPaid, MSGBOX_DEFAULT
	return

Route30_House_EventScript_BugHotelDeclined::
	msgbox Route30_House_Text_ReformDeclined, MSGBOX_DEFAULT
	return

@ The original one-off Cheri, plus the Book of Berries. It no longer ends the
@ conversation: the tutorial and the first daily pair happen on the same visit,
@ so the box stays open into the gift (no closemessage here).
Route30_House_EventScript_Tutorial::
	msgbox Route30_BerryHouse_Text_MonEatBerries, MSGBOX_DEFAULT
	giveitem ITEM_CHERI_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BERRY_ROUTE_30_HOUSE
	@ This visit's gift gets the first-time line (cleared by the next map load).
	setflag FLAG_TEMP_1
	@ The garden outside opens with the tutorial: bed A is level 1.
	setvar VAR_BERRY_GARDEN_LEVEL, 1
	special BerryLedger_RegisterStarters
	msgbox Route30_House_Text_TheBook, MSGBOX_DEFAULT
	return

@ Book of Berries (.claude/berry_master/REI_DA_COLHEITA.md section 3): Bram
@ only hands out what the player has harvested at least once, never Lansat,
@ Starf or Enigma (src/berry_garden.c). The tutorial registers his eight, so
@ the draw is never empty here.
@ giveitem with a var works because the macro uses setorcopyvar.
Route30_House_EventScript_GiveLedgerBerry::
	specialvar VAR_RESULT, BerryLedger_RandomRegistered
	goto_if_eq VAR_RESULT, ITEM_NONE, Route30_House_EventScript_GiveLedgerBerryEnd
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
Route30_House_EventScript_GiveLedgerBerryEnd::
	return

@ Book milestones (section 3.4): 12, 20, 30, 40, 50, 60 Berries. Paid in order,
@ one after the other, before the daily gift. VAR_BERRY_LEDGER_MILESTONE is the
@ last one paid; it only moves after the prize is in the bag, so a full bag
@ loses nothing - Bram keeps it for the next visit. 66 (the title) is the
@ epilogue's (part 16).
@ VAR_0x8008 = milestone, VAR_0x8009 = prize, VAR_0x800A = how many.
Route30_House_EventScript_Milestones::
	specialvar VAR_RESULT, BerryLedger_PendingMilestone
	goto_if_eq VAR_RESULT, 0, Route30_House_EventScript_MilestonesEnd
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 12, Route30_House_EventScript_Prize12
	call_if_eq VAR_0x8008, 20, Route30_House_EventScript_Prize20
	call_if_eq VAR_0x8008, 30, Route30_House_EventScript_Prize30
	call_if_eq VAR_0x8008, 40, Route30_House_EventScript_Prize40
	call_if_eq VAR_0x8008, 50, Route30_House_EventScript_Prize50
	call_if_eq VAR_0x8008, 60, Route30_House_EventScript_Prize60
	buffernumberstring STR_VAR_1, VAR_0x8008
	msgbox Route30_House_Text_Milestone, MSGBOX_DEFAULT
	checkitemspace VAR_0x8009, VAR_0x800A
	goto_if_eq VAR_RESULT, FALSE, Route30_House_EventScript_MilestoneBagFull
	giveitem VAR_0x8009, VAR_0x800A
	copyvar VAR_BERRY_LEDGER_MILESTONE, VAR_0x8008
	goto Route30_House_EventScript_Milestones
Route30_House_EventScript_MilestonesEnd::
	return

Route30_House_EventScript_MilestoneBagFull::
	msgbox Route30_House_Text_MilestoneBagFull, MSGBOX_DEFAULT
	return

Route30_House_EventScript_Prize12::
	setvar VAR_0x8009, ITEM_GROWTH_MULCH
	setvar VAR_0x800A, 5
	return

Route30_House_EventScript_Prize20::
	setvar VAR_0x8009, ITEM_RICH_MULCH
	setvar VAR_0x800A, 3
	return

Route30_House_EventScript_Prize30::
	setvar VAR_0x8009, ITEM_SURPRISE_MULCH
	setvar VAR_0x800A, 3
	return

Route30_House_EventScript_Prize40::
	setvar VAR_0x8009, ITEM_AMAZE_MULCH
	setvar VAR_0x800A, 3
	return

Route30_House_EventScript_Prize50::
	setvar VAR_0x8009, ITEM_BERRY_POUCH
	setvar VAR_0x800A, 1
	return

Route30_House_EventScript_Prize60::
	setvar VAR_0x8009, ITEM_BOOST_MULCH
	setvar VAR_0x800A, 5
	return

Route30_House_EventScript_FirstTwoText::
	msgbox Route30_House_Text_FirstTwo, MSGBOX_DEFAULT
	return

Route30_House_EventScript_TakeTwoText::
	msgbox Route30_House_Text_TakeTwo, MSGBOX_DEFAULT
	return

Route30_House_EventScript_DoneToday::
	specialvar VAR_RESULT, GardenGift_Count
	goto_if_eq VAR_RESULT, 3, Route30_House_EventScript_DoneTodayThree
	msgbox Route30_House_Text_DoneToday, MSGBOX_DEFAULT
	goto Route30_House_EventScript_AfterGift

Route30_House_EventScript_DoneTodayThree::
	msgbox Route30_House_Text_DoneTodayThree, MSGBOX_DEFAULT
	goto Route30_House_EventScript_AfterGift

@ His wife, and the whole reason she exists: the fourteen competitive berries,
@ two of which (Lansat and Starf) are Kurt's level-20 recipes. One object, one
@ daily flag, one berry, and a gate on FLAG_SYS_GAME_CLEAR - which is what keeps
@ Lansat and Starf out of the early game without a single new var.
@ Before the Hall of Fame she just talks.
@ What is deliberately NOT ported from the Hoenn Berry Master's wife: the Easy
@ Chat phrase mechanism (PHRASE_GREAT_BATTLE and the other four). It is a Gen 3
@ leftover with no equivalent in Johto, and its five berries are inside the common
@ range above, so they come out of the daily draw anyway.
@ FLAG_DAILY_BERRY_MASTERS_WIFE is REUSED and not newly allocated: it already
@ existed in the daily block and nothing in the repository referenced it (the
@ Hoenn wife latches on FLAG_GARBAGEFLAG), so this whole NPC costs no new flag.
Route30_House_EventScript_BerryWife::
	lock
	faceplayer
	dotimebasedevents
	special GardenRollDay
	call Route30_House_EventScript_LaurelHint
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route30_House_EventScript_WifeChat
	goto_if_set FLAG_DAILY_BERRY_MASTERS_WIFE, Route30_House_EventScript_WifeDoneToday
	@ Only a rare the player has harvested (the Book), never the Enigma.
	specialvar VAR_RESULT, BerryLedger_RandomRegisteredRare
	goto_if_eq VAR_RESULT, ITEM_NONE, Route30_House_EventScript_WifeNoRare
	copyvar VAR_0x8008, VAR_RESULT
	msgbox Route30_House_Text_WifeRare, MSGBOX_DEFAULT
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_BERRY_MASTERS_WIFE
	closemessage
	release
	end

@ A discovery order is open: Bram does not know the recipe, Laurel does
@ (section 6). Once per visit (FLAG_TEMP_8), then her usual line.
@ STR_VAR_1 = the new Berry, STR_VAR_2 / STR_VAR_3 = the two parents.
Route30_House_EventScript_LaurelHint::
	goto_if_set FLAG_TEMP_8, Route30_House_EventScript_LaurelHintEnd
	specialvar VAR_RESULT, GardenOrder_Get
	goto_if_ne VAR_RESULT, GARDEN_ORDER_OPEN, Route30_House_EventScript_LaurelHintEnd
	goto_if_eq VAR_0x8007, FALSE, Route30_House_EventScript_LaurelHintEnd
	specialvar VAR_RESULT, BerryLedger_GetRecipe
	goto_if_eq VAR_RESULT, FALSE, Route30_House_EventScript_LaurelHintEnd
	setflag FLAG_TEMP_8
	bufferitemname STR_VAR_1, VAR_0x8004
	bufferitemname STR_VAR_2, VAR_0x8005
	bufferitemname STR_VAR_3, VAR_0x8006
	msgbox Route30_House_Text_LaurelHint, MSGBOX_DEFAULT
	return

Route30_House_EventScript_LaurelHintEnd::
	return

Route30_House_EventScript_WifeNoRare::
	msgbox Route30_House_Text_WifeNoRare, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_House_EventScript_WifeChat::
	msgbox Route30_House_Text_WifeChat, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_House_EventScript_WifeDoneToday::
	msgbox Route30_House_Text_WifeDoneToday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_BerryHouse_Text_MonEatBerries:
	.string "When you follow that path up north,\n"
	.string "you will see Kukui's house.\p"
	.string "But before you go, allow me to\n"
	.string "tell you about Berries!\p"
	.string "Pokémon get healthier by eating\n"
	.string "Berries.\p"
	.string "They can even eat Berries\n"
	.string "they're holding in battle.\p"
	.string "Here. I'll share one with you!$"

Route30_House_Text_TheBook:
	.string "One more thing. Every Berry you pick\n"
	.string "yourself goes in the Book.\p"
	.string "Off my trees, off any tree on any\n"
	.string "road. Buying one doesn't count.\p"
	.string "I don't hand out what I don't grow,\n"
	.string "sprout. And I only grow what's in\l"
	.string "the Book.\p"
	.string "Get it in the Book and I'll have\n"
	.string "seed for you by morning.$"

Route30_House_Text_Milestone:
	.string "Let me see that Book of yours...\p"
	.string "{STR_VAR_1} Berries! You're getting\n"
	.string "the hang of this, sprout.\p"
	.string "Here. Something for the garden.$"

Route30_House_Text_MilestoneBagFull:
	.string "Your Bag's too full for what I've got\n"
	.string "for you. I'll keep it. Come back.$"

Route30_House_Text_FirstTwo:
	.string "And since you're here, take two more.\n"
	.string "There's always more tomorrow.$"

Route30_House_Text_TakeTwo:
	.string "You came back! And you looked at the\n"
	.string "trees, I'll bet.\p"
	.string "I pick more than two old people can eat.\n"
	.string "Take two -- there's more tomorrow.\l"
	.string "There's always more tomorrow.$"

Route30_House_Text_TakeThree:
	.string "You came back! And you looked at the\n"
	.string "trees, I'll bet.\p"
	.string "Three today -- the garden earns its\n"
	.string "keep. Or have you got one in mind?\p"
	.string "Name it. If it's in the Book, I've got\n"
	.string "seed for it.$"

Route30_House_Text_SurpriseMe:
	.string "Surprise me$"

Route30_House_Text_OneInMind:
	.string "I've got one$"

Route30_House_Text_NameIt:
	.string "Go on, then. Which one?$"

Route30_House_Text_GoodPick:
	.string "Good pick. Plant it next to something\n"
	.string "it gets along with.$"

Route30_House_Text_PlantThemThree:
	.string "And don't eat them all. Plant one.\p"
	.string "That's how this works: a planted Berry\n"
	.string "is a tree, and a tree is Berries for ever.\p"
	.string "Check the trees as you go. They grow\n"
	.string "back after 12 hours.$"

Route30_House_Text_DoneTodayThree:
	.string "That's your three for today.\p"
	.string "Go and plant one. I'll pick more by\n"
	.string "morning -- I always do.$"

Route30_House_Text_OfferProper:
	.string "{STR_VAR_1} Berries in your Book now.\n"
	.string "Time this was a proper garden.\p"
	.string "Four more beds by the pond, dug by\n"
	.string "morning. ¥5,000 for the lot. Shall I?$"

Route30_House_Text_OfferChannel:
	.string "{STR_VAR_1} in the Book... I could dig a\n"
	.string "channel from the pond.\p"
	.string "The whole garden would water itself\n"
	.string "every morning. ¥10,000. Shall I?$"

Route30_House_Text_OfferBugHotel:
	.string "Bugsy wants to build a Bug Hotel by\n"
	.string "the beds. Won't take a coin for it.\p"
	.string "Says the bugs will come for the Berries\n"
	.string "and stay for the architecture.\p"
	.string "Well? Do I let him?$"

Route30_House_Text_ReformPaid:
	.string "Done deal. Come and look in the morning.$"

Route30_House_Text_ReformDeclined:
	.string "Suit yourself. The offer keeps.$"

Route30_House_Text_ReformNoMoney:
	.string "Hah. Come back when you've got the\n"
	.string "money, sprout.$"

Route30_House_Text_ReformNeedsHelp:
	.string "I've got the next thing in mind for the\n"
	.string "garden. But it's more than one old man\l"
	.string "can dig. I'd need somebody to help.$"

Route30_House_Text_BuiltProper:
	.string "Four more beds! Laurel dug them.\p"
	.string "Don't tell her I said so. She'll say\n"
	.string "I helped.$"

Route30_House_Text_BuiltChannel:
	.string "{SPEAKER NAME_BERRY_MASTER}See that channel? Runs right from the\n"
	.string "pond.\p"
	.string "The whole garden drinks before you're\n"
	.string "even out of bed now.\p"
	.string "{SPEAKER NAME_LAUREL}He dug it at three in the morning.\n"
	.string "The neighbors thought it was a Diglett.$"

Route30_House_Text_BuiltBugHotel:
	.string "Bugsy finished his Bug Hotel last night.\n"
	.string "Hollow stems, bark, a pile of stones...\p"
	.string "He means more bugs. He's happy about\n"
	.string "more bugs.$"

Route30_House_Text_OrderKurt:
	.string "Kurt called. Wants\n"
	.string "{STR_VAR_2} {STR_VAR_1}.\p"
	.string "Said “by tomorrow.” Kurt thinks\n"
	.string "everything's by tomorrow.$"

Route30_House_Text_OrderFlowerShop:
	.string "The girls at the Goldenrod flower shop\n"
	.string "want {STR_VAR_2} {STR_VAR_1}\l"
	.string "for the window.\p"
	.string "Pretty ones, they said. As if I grow\n"
	.string "ugly ones.$"

Route30_House_Text_OrderNurse:
	.string "Nurse in Cherrygrove's running low.\n"
	.string "{STR_VAR_2} {STR_VAR_1}.\p"
	.string "For the patients, she says.\n"
	.string "For her tea, I say.$"

Route30_House_Text_OrderMoomoo:
	.string "Moomoo Farm's Miltank have gone off\n"
	.string "their feed.\p"
	.string "{STR_VAR_2} {STR_VAR_1}\n"
	.string "ought to fix that.$"

Route30_House_Text_OrderDayCare:
	.string "The Day Care couple want\n"
	.string "{STR_VAR_2} {STR_VAR_1}.\p"
	.string "The babies love them. The old man\n"
	.string "loves them more.$"

Route30_House_Text_OrderBugsy:
	.string "Bugsy wants {STR_VAR_2} {STR_VAR_1}.\n"
	.string "“For bait,” he says.\p"
	.string "The bait always gets eaten by Bugsy.$"

Route30_House_Text_OrderTheater:
	.string "Letter from Ecruteak. The dance\n"
	.string "theater wants {STR_VAR_2} {STR_VAR_1}.\p"
	.string "Those Kimono Girls eat like Snorlax,\n"
	.string "I'm told.$"

Route30_House_Text_OrderLighthouse:
	.string "The lighthouse in Olivine.\n"
	.string "{STR_VAR_2} {STR_VAR_1},\l"
	.string "for the Ampharos.\p"
	.string "That Ampharos eats better than I do.$"

Route30_House_Text_OrderSchool:
	.string "The teacher at the Violet school wants\n"
	.string "{STR_VAR_2} {STR_VAR_1} for a lesson.\p"
	.string "Kids learn more from a Berry than\n"
	.string "a book, I say.$"

Route30_House_Text_OrderLaurel:
	.string "Laurel wants {STR_VAR_2} {STR_VAR_1}.\n"
	.string "She won't say why.\p"
	.string "She never says why. Just bring them.$"

Route30_House_Text_OrderDiscovery:
	.string "Now here's one I've never grown.\n"
	.string "Kurt swears there's a Berry called\l"
	.string "{STR_VAR_1}. I think he's pulling my leg.\p"
	.string "Ask Laurel. If anyone knows, she\n"
	.string "knows. She just won't tell ME.$"

Route30_House_Text_OrderReminder:
	.string "Still need {STR_VAR_2} {STR_VAR_1} for\n"
	.string "today's order. No rush. Some rush.$"

Route30_House_Text_OrderReminderDiscovery:
	.string "Any luck with that {STR_VAR_1}?\n"
	.string "Did you ask Laurel?$"

Route30_House_Text_OrderHandOver:
	.string "That's {STR_VAR_2} {STR_VAR_1}!\n"
	.string "Hand them over?$"

Route30_House_Text_OrderHandOverOne:
	.string "That's the {STR_VAR_1}!\n"
	.string "Hand it over?$"

Route30_House_Text_OrderBagFull:
	.string "Hold on. There's Mulch in your pay, and\n"
	.string "your Bag hasn't room for it.\l"
	.string "Make room first.$"

Route30_House_Text_OrderThanks1:
	.string "That's the lot! Here's your pay.\p"
	.string "Don't spend it all on mulch. Spend\n"
	.string "some of it on mulch.$"

Route30_House_Text_OrderThanks2:
	.string "Look at the size of these!\n"
	.string "They'll think I grew them.\l"
	.string "I'll let them.$"

Route30_House_Text_OrderThanks3:
	.string "Perfect. You pick 'em better than\n"
	.string "I do now. Don't tell anyone.$"

Route30_House_Text_OrderThanks4:
	.string "Right on time. Kurt'll be furious.\n"
	.string "He likes being disappointed.$"

Route30_House_Text_OrderThanks5:
	.string "Good work, sprout. That's a farmer's\n"
	.string "money. Earned in dirt.$"

Route30_House_Text_OrderPaid:
	.string "{PLAYER} received ¥{STR_VAR_3}.$"

Route30_House_Text_LaurelHint:
	.string "{STR_VAR_1}. {STR_VAR_2} beside\n"
	.string "{STR_VAR_3}.\p"
	.string "Touching, side by side. Not corner to\n"
	.string "corner. People always do corner to\l"
	.string "corner.$"

Route30_House_Text_PlantThem:
	.string "And don't eat both of them. Plant one.\p"
	.string "That's how this works: a planted Berry\n"
	.string "is a tree, and a tree is Berries for ever.\p"
	.string "Check the trees as you go. They grow\n"
	.string "back after 12 hours.$"

Route30_House_Text_DoneToday:
	.string "That's your two for today.\p"
	.string "Go and plant one. I'll pick more by\n"
	.string "morning -- I always do.$"

Route30_House_Text_WifeChat:
	.string "My husband hands out the easy ones.\p"
	.string "I keep the others. They only fruit for\n"
	.string "somebody who knows what they're doing,\l"
	.string "and no offence, dear, but you're still\l"
	.string "carrying a town map.$"

Route30_House_Text_WifeRare:
	.string "My husband hands out the easy ones. I\n"
	.string "keep the others.\p"
	.string "These only fruit for somebody who\n"
	.string "knows what they're doing, and I saw\l"
	.string "what you did at the League.\p"
	.string "One a day. Don't argue.$"

Route30_House_Text_WifeNoRare:
	.string "The rare ones only come from the\n"
	.string "Book, dear. Yours hasn't got one yet.\p"
	.string "Grow one yourself first. Then we'll\n"
	.string "talk.$"

Route30_House_Text_WifeDoneToday:
	.string "One a day. I said don't argue.\p"
	.string "Come back tomorrow and I'll pick you\n"
	.string "another.$"
