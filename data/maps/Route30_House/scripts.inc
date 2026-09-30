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
	call Route30_House_EventScript_Milestones
	goto_if_set FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Route30_House_EventScript_DoneToday
	@ "You came back!" makes no sense in the same conversation as the tutorial.
	call_if_set FLAG_TEMP_1, Route30_House_EventScript_FirstTwoText
	call_if_unset FLAG_TEMP_1, Route30_House_EventScript_TakeTwoText
	call Route30_House_EventScript_GiveLedgerBerry
	@ The flag is set BETWEEN the two berries, exactly as the Hoenn original does
	@ it: setting it after both would let a bag that fills up on the second berry
	@ be used to take both again on the same day.
	setflag FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY
	call Route30_House_EventScript_GiveLedgerBerry
	msgbox Route30_House_Text_PlantThem, MSGBOX_DEFAULT
	closemessage
	release
	end

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
	msgbox Route30_House_Text_DoneToday, MSGBOX_DEFAULT
	closemessage
	release
	end

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
