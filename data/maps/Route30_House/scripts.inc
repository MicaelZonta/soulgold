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
	.byte 0

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
	call_if_unset FLAG_GOT_BERRY_ROUTE_30_HOUSE, Route30_House_EventScript_Tutorial
	goto_if_set FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Route30_House_EventScript_DoneToday
	msgbox Route30_House_Text_TakeTwo, MSGBOX_DEFAULT
	call Route30_House_EventScript_GiveCommonBerry
	@ The flag is set BETWEEN the two berries, exactly as the Hoenn original does
	@ it: setting it after both would let a bag that fills up on the second berry
	@ be used to take both again on the same day.
	setflag FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY
	call Route30_House_EventScript_GiveCommonBerry
	msgbox Route30_House_Text_PlantThem, MSGBOX_DEFAULT
	closemessage
	release
	end

@ The original one-off, unchanged except that it no longer ends the conversation:
@ the tutorial and the first daily pair happen on the same visit.
Route30_House_EventScript_Tutorial::
	msgbox Route30_BerryHouse_Text_MonEatBerries, MSGBOX_DEFAULT
	giveitem ITEM_CHERI_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setflag FLAG_GOT_BERRY_ROUTE_30_HOUSE
	return

@ The common pool is a CONTIGUOUS range of the item enum, so a draw is three
@ instructions and no table: Cheri (FIRST_BERRY_INDEX) .. Roseli, 53 berries.
@ giveitem with a var works because the macro uses setorcopyvar.
Route30_House_EventScript_GiveCommonBerry::
	random NUM_BERRY_MASTER_COMMON
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
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
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route30_House_EventScript_WifeChat
	goto_if_set FLAG_DAILY_BERRY_MASTERS_WIFE, Route30_House_EventScript_WifeDoneToday
	msgbox Route30_House_Text_WifeRare, MSGBOX_DEFAULT
	random NUM_BERRY_MASTER_RARE
	addvar VAR_RESULT, NUM_BERRY_MASTER_RARE_SKIPPED
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_BERRY_MASTERS_WIFE
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

Route30_House_Text_WifeDoneToday:
	.string "One a day. I said don't argue.\p"
	.string "Come back tomorrow and I'll pick you\n"
	.string "another.$"
