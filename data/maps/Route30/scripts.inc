.set LOCALID_ROUTE_30_JOEY, 6

Route30_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route30_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route30_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route30_OnFrame
	.byte 0

Route30_OnTransition: 
	callnative SetTimeBasedEncounters
	special GardenRollDay
	@ Level 3: the channel waters every garden plot once a day (after the roll,
	@ so a channel finished at this date change already works today).
	special GardenIrrigate
	call Route30_EventScript_GardenVisibility
	end

Route30_OnLoad::
	call_if_lt VAR_BERRY_GARDEN_LEVEL, 2, Route30_EventScript_LockGardenBSoil
	end

Route30_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 2, Route30_EventScript_ElmCall_Trigger
	.2byte 0
	
Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Youngster_Joey_Fighting::
	lock
	msgbox Route30_Text_UseTackle, 	MSGBOX_AUTOCLOSE
	waitmessage
	playse SE_PIN
	applymovement LOCALID_ROUTE_30_JOEY, Common_Movement_QuestionMark
	delay 30
	faceplayer
	msgbox Route30_Text_ThisIsABigBattle, MSGBOX_AUTOCLOSE
	waitmessage
	turnobject LOCALID_ROUTE_30_JOEY DIR_NORTH
	release
	end


Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single TRAINER_MIKEY, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end
	
Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single TRAINER_DON, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_ElmCall_Trigger::
	lock
	pokenavcall Route30_Text_Elm_Disaster
	waitmessage
	delay 30
	setvar VAR_CHERRYGROVE_CITY_STATE, 3
	release
	end

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end	

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWAG, CRY_MODE_NORMAL
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

@ ===========================================================================
@ Berry Master's garden (.claude/berry_master/PLANO_DE_IMPLEMENTACAO.md, part 2).
@ y grows DOWNWARD. The house door is (26,39).
@   bed A  (28..30, 43..44)  6 plots  BERRY_TREE_GARDEN_A1..A6, always open
@   bed B  (30..31, 41..42)  4 plots  BERRY_TREE_GARDEN_B1..B4, garden level 2
@   Laurel's plot (23,38)             BERRY_TREE_KINGS_PLOT, locked by the story
@ map.bin holds every plot as berry soil (46, blocked), so Porymap shows the
@ whole garden. A locked plot needs BOTH halves: its object hidden (an empty
@ tree is invisible but still asks "plant?") and, for bed B, its soil turned
@ back into grass (otherwise four blocked tiles of bare dirt sit by the path).
@ Laurel's plot keeps its soil: it was already a tree spot, and the sign on
@ the same tile answers while the object is hidden.
@ ===========================================================================

@ ON_TRANSITION, before anything spawns: FLAG_TEMP_* start clear on every map
@ load, so this only ever sets.
Route30_EventScript_GardenVisibility::
	@ Saves that finished Bram's tutorial before the garden existed.
	call_if_set FLAG_GOT_BERRY_ROUTE_30_HOUSE, Route30_EventScript_GardenLevelAtLeastOne
	call_if_lt VAR_BERRY_GARDEN_LEVEL, 2, Route30_EventScript_HideGardenB
	@ Laurel's plot opens in Act 3 of the sidequest (part 12).
	setflag FLAG_TEMP_HIDE_KINGS_PLOT
	@ Who is out here at this hour (part 8, src/berry_garden.c).
	special GardenCast_Apply
	return

Route30_EventScript_GardenLevelAtLeastOne::
	call_if_eq VAR_BERRY_GARDEN_LEVEL, 0, Route30_EventScript_SetGardenLevelOne
	return

Route30_EventScript_SetGardenLevelOne::
	setvar VAR_BERRY_GARDEN_LEVEL, 1
	return

Route30_EventScript_HideGardenB::
	setflag FLAG_TEMP_HIDE_GARDEN_B
	return

@ ON_LOAD: the grass that was there before (0 and 1 of the primary tileset),
@ walkable. setmetatile keeps the tile's elevation.
Route30_EventScript_LockGardenBSoil::
	setmetatile 30, 41, 0, FALSE
	setmetatile 31, 41, 0, FALSE
	setmetatile 30, 42, 1, FALSE
	setmetatile 31, 42, 0, FALSE
	return

Route30_EventScript_ColdSoil::
	msgbox Route30_Text_ColdSoil, MSGBOX_SIGN
	end

Route30_Text_ColdSoil:
	.string "The soil here is hard and cold.\n"
	.string "Nothing's grown in it for a long time.$"

@ ---------------------------------------------------------------------------
@ The garden's people (part 8). Nobody may stand in the water (x >= 32 here is
@ the pond: collision 0, only the metatile behaviour says Surf, so dump_mapa.py
@ shows it as floor) or on the only way to a plot. The pocket (31,43)-(31,44)
@ is the only side of (30,43) and (31,42), and it is reached ONLY through row
@ 45 east of (27,45): nobody stands on (28..31,45) either.
@   Bram   (27,44) morning, watering the bottom row, facing it
@   Laurel (27,43) weekday afternoons, facing (28,43) (also reached from (28,42))
@   Tilly  (24,41) weekend afternoons, the mulch stall, by the path
@   Bugsy  (29,41) Tue/Thu afternoons from Act 1b, studying bed B (its (30,41)
@          is also reached from (30,40))
@ Proof with all of them standing at once (any hour is a subset):
@   python3 dev_scripts/berry_garden_access_check.py
@ Bram and Laurel run their house scripts (Route30_House_EventScript_BaldMan /
@ _BerryWife): same conversation wherever they stand.
@ ---------------------------------------------------------------------------

@ Tilly's Mulch Emporium (section 14.4 G). Rich and Surprise from the Bug
@ Hotel (garden level 4) on; Boost and Amaze stay prizes of the Book.
Route30_EventScript_Tilly::
	lock
	faceplayer
	specialvar VAR_RESULT, GetDayOfWeek
	call_if_eq VAR_RESULT, WEEKDAY_SAT, Route30_EventScript_TillySaturday
	call_if_ne VAR_RESULT, WEEKDAY_SAT, Route30_EventScript_TillySunday
	message Route30_Text_TillyBuy
	waitmessage
	goto_if_ge VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_BUG_HOTEL, Route30_EventScript_TillyMartBugHotel
	pokemart Route30_Mart_TillyMulch
	goto Route30_EventScript_TillyBye

Route30_EventScript_TillyMartBugHotel::
	pokemart Route30_Mart_TillyMulchBugHotel
Route30_EventScript_TillyBye::
	msgbox Route30_Text_TillyBye, MSGBOX_DEFAULT
	release
	end

Route30_EventScript_TillySaturday::
	msgbox Route30_Text_TillySaturday, MSGBOX_DEFAULT
	return

Route30_EventScript_TillySunday::
	msgbox Route30_Text_TillySunday, MSGBOX_DEFAULT
	return

	.align 2
Route30_Mart_TillyMulch:
	.2byte ITEM_GROWTH_MULCH
	.2byte ITEM_DAMP_MULCH
	.2byte ITEM_STABLE_MULCH
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_NONE

	.align 2
Route30_Mart_TillyMulchBugHotel:
	.2byte ITEM_GROWTH_MULCH
	.2byte ITEM_DAMP_MULCH
	.2byte ITEM_STABLE_MULCH
	.2byte ITEM_GOOEY_MULCH
	.2byte ITEM_RICH_MULCH
	.2byte ITEM_SURPRISE_MULCH
	.2byte ITEM_NONE

@ Tuesdays and Thursdays (section 14.4 H): one line each until part 9.
Route30_EventScript_Bugsy::
	lock
	faceplayer
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_THU, Route30_EventScript_BugsyThursday
	msgbox Route30_Text_BugsyTuesday, MSGBOX_DEFAULT
	goto Route30_EventScript_BugsyEnd

Route30_EventScript_BugsyThursday::
	msgbox Route30_Text_BugsyThursday, MSGBOX_DEFAULT
Route30_EventScript_BugsyEnd::
	closemessage
	release
	end

Route30_Text_TillySaturday:
	.string "Welcome to Tilly's Mulch Emporium!\p"
	.string "It's mulch. It's the best mulch.\n"
	.string "Grandpa made it but I named it.$"

Route30_Text_TillySunday:
	.string "Do you know what Rellor do with mulch?\n"
	.string "They ROLL it.\p"
	.string "I'm going to have ten Rellor.\n"
	.string "Grandma said one.$"

Route30_Text_TillyBuy:
	.string "Buy some! Buy LOTS!$"

Route30_Text_TillyBye:
	.string "Come back next weekend! Bring money!$"

Route30_Text_BugsyTuesday:
	.string "Every color of Berry calls a different\n"
	.string "bug. I've got a chart.\p"
	.string "It's twelve pages.$"

Route30_Text_BugsyThursday:
	.string "Try Stable Mulch on one bed. Watch\n"
	.string "what moves in.\p"
	.string "You'll love him.$"

Route30_Text_Mailbox:
	.string "Mr.Pokémon's House$"

Route30_Text_UseTackle:
	.string "Go, Rattata!\p"
	.string "Tackle!$"

Route30_Text_ThisIsABigBattle:
	.string "What? This is a big battle!\n"
	.string "Leave me alone!$"

Route30_Text_YoungsterJoey1Seen:
	.string "I just lost, so I'm trying to\n"
	.string "find more Pokémon.\p"
	.string "Wait! You look weak! Come on,\n"
	.string "let's battle!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "Ack! I lost again!\n"
	.string "Doggone it!$"

Route30_Text_YoungsterJoey1After:
	.string "Do I have to have more Pokémon\n"
	.string "in order to battle better?\p"
	.string "No! I'm sticking with this one\n"
	.string "no matter what!$"

Route30_Text_YoungsterMikeySeen:
	.string "You're a Pokémon trainer,\n"
	.string "right?\p"
	.string "Then you have to battle!$"

Route30_Text_YoungsterMikeyBeaten:
	.string "That's strange.\n"
	.string "I won before.$"

Route30_Text_YoungsterMikeyAfter:
	.string "Becoming a good trainer is\n"
	.string "really tough.\p"
	.string "I'm going to battle other\n"
	.string "people to get better.$"

Route30_Text_BugCatcherDonSeen:
	.string "Instead of a bug Pokémon,\n"
	.string "I found a trainer!$"

Route30_Text_BugCatcherDonBeaten:
	.string "Argh! You're too strong!$"

Route30_Text_BugCatcherDonAfter:
	.string "I ran out of Poké Balls while\n"
	.string "I was catching Pokémon.\p"
	.string "I should've bought some more…$"

Route30_Text_YoungsterDirectionsToMrPokemon:
	.string "Kukui's house?\n"
	.string "It's a bit farther ahead.$"

Route30_Text_YoungsterEveryoneIsBattling:
	.string "Everyone's having fun\n"
	.string "battling!\p"
	.string "You should too!$"

Route30_Text_CooltrainerF:
	.string "I'm not a trainer.\p"
	.string "But if you look one in the\n"
	.string "eyes, prepare to battle.$"

Route30_Text_Sign:
	.string "Route 30\p"
	.string "Violet City - Cherrygrove City$"

Route30_Text_MrPokemonsHouseDirectionsSign:
	.string "Kukui's House\n"
	.string "Straight Ahead!$"

Route30_Text_MrPokemonsHouseSign:
	.string "Kukui's House$"

Route30_Text_TrainerTips:
	.string "Trainer Tips\p"
	.string "No stealing other people's\n"
	.string "Pokémon!\p"
	.string "Poké Balls are to be thrown\n"
	.string "only at wild Pokémon!$"

Route30_Text_YoungsterJoeyGiveHPUp:
	.string "I lost again…\n"
	.string "Gee, you're tough!\p"
	.string "Oh yeah, I almost forgot that\n"
	.string "I had to give you this.\p"
	.string "Use it to get even tougher,\n"
	.string "Ok?\p"
	.string "I'm going to get tougher too.$"

Route30_Text_Elm_Disaster:
	.string "{SPEAKER NAME_ELM}H-hello? {PLAYER}? It's\n"
	.string "a disaster!\p"
	.string "Uh, um, it's just terrible!\p"
	.string "What should I do? It…\n"
	.string "Oh, no…\p"
	.string "Please get back here now!$"


Route30_Text_Poliwag:
	.string "{SPEAKER NAME_POLIWAG}Wag waag!$"
