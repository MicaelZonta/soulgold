@ ===========================================================================
@ Berry Master's garden: the everyday battles (plan part 11, REI_DA_COLHEITA.md
@ section 14.5) - Tilly, Bugsy and Klara's morning raid.
@ All like the Nexus fights (data/scripts/nexus.inc, nexus_fight): the trainer
@ flag is cleared before and after (they can be fought again), no blackout
@ during the fight, the result in VAR_TEMP_3. Losing costs nothing (the party
@ is healed) - except to Klara, who takes the plot. One fight a day each
@ (GARDEN_TODAY_FOUGHT_*), prize only on a win. Levels: the repo's trainer
@ level scaling, like every trainer.
@ ===========================================================================

	.macro garden_fight trainer:req, defeat_text:req
	closemessage
	cleartrainerflag \trainer
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro \trainer, \defeat_text
	clearflag B_FLAG_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT
	cleartrainerflag \trainer
	.endm

@ ---------------------------------------------------------------------------
@ Tilly (weekend afternoons, at her stall; story state 1+). Her team follows
@ the garden level (section 14.5): 1-2, 3-4, 5. Prize: 2 of her Mulches.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_TillyBattle::
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_TILLY
	specialvar VAR_RESULT, GardenToday_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_TillyNap
	special GardenToday_Set
	msgbox BerryGarden_Text_TillyIntro, MSGBOX_DEFAULT
	goto_if_ge VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_LAST_REFORM + 1, BerryGarden_EventScript_TillyFight3
	goto_if_ge VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_CHANNEL, BerryGarden_EventScript_TillyFight2
	garden_fight TRAINER_GARDEN_TILLY_1, BerryGarden_Text_TillyDefeat
	goto BerryGarden_EventScript_TillyAfterFight

BerryGarden_EventScript_TillyFight2::
	garden_fight TRAINER_GARDEN_TILLY_2, BerryGarden_Text_TillyDefeat
	goto BerryGarden_EventScript_TillyAfterFight

BerryGarden_EventScript_TillyFight3::
	garden_fight TRAINER_GARDEN_TILLY_3, BerryGarden_Text_TillyDefeat
BerryGarden_EventScript_TillyAfterFight::
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_TillyWon
	specialvar VAR_0x8008, GardenTilly_PrizeMulch
	msgbox BerryGarden_Text_TillyPrize, MSGBOX_DEFAULT
	giveitem VAR_0x8008, 2
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	return

@ Lost, a draw or anything else: nothing lost, the party patched up.
BerryGarden_EventScript_TillyWon::
	special HealPlayerParty
	msgbox BerryGarden_Text_TillyWon, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_TillyNap::
	msgbox BerryGarden_Text_TillyNap, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Bugsy (Tuesday and Thursday afternoons; from Act 1c, story state 4). Team of
@ the day (VAR_DAYS % 3: red, blue, pink/green Berries), always his Scizor.
@ Prize: 3 Berries from the Book.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_BugsyBattle::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE, BerryGarden_EventScript_BugsyBattleEnd
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_BUGSY
	specialvar VAR_RESULT, GardenToday_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_BugsyBusy
	msgbox BerryGarden_Text_BugsyIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BerryGarden_EventScript_BugsyDeclined
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_BUGSY
	special GardenToday_Set
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	@ VAR_DAYS % 10 -> % 3 by hand (0-2 red, 3-5 blue, 6-9 pink/green)
	goto_if_ge VAR_RESULT, 6, BerryGarden_EventScript_BugsyFight3
	goto_if_ge VAR_RESULT, 3, BerryGarden_EventScript_BugsyFight2
	garden_fight TRAINER_GARDEN_BUGSY_1, BerryGarden_Text_BugsyDefeat
	goto BerryGarden_EventScript_BugsyAfterFight

BerryGarden_EventScript_BugsyFight2::
	garden_fight TRAINER_GARDEN_BUGSY_2, BerryGarden_Text_BugsyDefeat
	goto BerryGarden_EventScript_BugsyAfterFight

BerryGarden_EventScript_BugsyFight3::
	garden_fight TRAINER_GARDEN_BUGSY_3, BerryGarden_Text_BugsyDefeat
BerryGarden_EventScript_BugsyAfterFight::
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_BugsyWon
	msgbox BerryGarden_Text_BugsyPrize, MSGBOX_DEFAULT
	call Route30_House_EventScript_GiveLedgerBerry
	call Route30_House_EventScript_GiveLedgerBerry
	call Route30_House_EventScript_GiveLedgerBerry
	return

BerryGarden_EventScript_BugsyWon::
	special HealPlayerParty
	msgbox BerryGarden_Text_BugsyWon, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_BugsyBusy::
	msgbox BerryGarden_Text_BugsyBusy, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_BugsyDeclined::
	msgbox BerryGarden_Text_BugsyDeclined, MSGBOX_DEFAULT
BerryGarden_EventScript_BugsyBattleEnd::
	return

@ ---------------------------------------------------------------------------
@ Klara (section 13.4): Route30 object LOCALID_ROUTE30_KLARA, placed in front
@ of a ripe plot by GardenKlara_Place (src/berry_garden.c). Talking to her is
@ the battle; she leaves either way. Her team: VAR_DAYS % 3.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_Klara::
	lock
	faceplayer
	call BerryGarden_EventScript_KlaraOpeningLine
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	goto_if_ge VAR_RESULT, 6, BerryGarden_EventScript_KlaraFight3
	goto_if_ge VAR_RESULT, 3, BerryGarden_EventScript_KlaraFight2
	garden_fight TRAINER_GARDEN_KLARA_1, BerryGarden_Text_KlaraDefeat
	goto BerryGarden_EventScript_KlaraAfterFight

BerryGarden_EventScript_KlaraFight2::
	garden_fight TRAINER_GARDEN_KLARA_2, BerryGarden_Text_KlaraDefeat
	goto BerryGarden_EventScript_KlaraAfterFight

BerryGarden_EventScript_KlaraFight3::
	garden_fight TRAINER_GARDEN_KLARA_3, BerryGarden_Text_KlaraDefeat
BerryGarden_EventScript_KlaraAfterFight::
	random 5
	copyvar VAR_0x8005, VAR_RESULT
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_KlaraLost
	@ She won, or a draw: the party patched up, and she takes the plot.
	special HealPlayerParty
	setvar VAR_0x8004, FALSE
	special GardenKlara_Resolve
	call BerryGarden_EventScript_KlaraTakesLine
	goto BerryGarden_EventScript_KlaraLeaves

BerryGarden_EventScript_KlaraLost::
	setvar VAR_0x8004, TRUE
	specialvar VAR_RESULT, GardenKlara_Resolve
	goto_if_eq VAR_RESULT, 5, BerryGarden_EventScript_KlaraMochi
	call BerryGarden_EventScript_KlaraLosesLine
	goto BerryGarden_EventScript_KlaraLeaves

@ The fifth win (section 13.4): the hook to Kitakami, nothing changes yet.
BerryGarden_EventScript_KlaraMochi::
	msgbox BerryGarden_Text_KlaraMochi, MSGBOX_DEFAULT
BerryGarden_EventScript_KlaraLeaves::
	closemessage
	setflag FLAG_TEMP_HIDE_KLARA
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE30_KLARA
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

BerryGarden_EventScript_KlaraLosesLine::
	switch VAR_0x8005
	case 1, BerryGarden_EventScript_KlaraLoses1
	case 2, BerryGarden_EventScript_KlaraLoses2
	case 3, BerryGarden_EventScript_KlaraLoses3
	case 4, BerryGarden_EventScript_KlaraLoses4
	msgbox BerryGarden_Text_KlaraLoses0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraLoses1::
	msgbox BerryGarden_Text_KlaraLoses1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraLoses2::
	msgbox BerryGarden_Text_KlaraLoses2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraLoses3::
	msgbox BerryGarden_Text_KlaraLoses3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraLoses4::
	msgbox BerryGarden_Text_KlaraLoses4, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_KlaraTakesLine::
	switch VAR_0x8005
	case 1, BerryGarden_EventScript_KlaraTakes1
	case 2, BerryGarden_EventScript_KlaraTakes2
	case 3, BerryGarden_EventScript_KlaraTakes3
	case 4, BerryGarden_EventScript_KlaraTakes4
	msgbox BerryGarden_Text_KlaraTakes0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraTakes1::
	msgbox BerryGarden_Text_KlaraTakes1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraTakes2::
	msgbox BerryGarden_Text_KlaraTakes2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraTakes3::
	msgbox BerryGarden_Text_KlaraTakes3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraTakes4::
	msgbox BerryGarden_Text_KlaraTakes4, MSGBOX_DEFAULT
	return

@ Bram on his next talk about her (column 3 of section 14.4 I): the 5th line
@ only after a win. Returns VAR_RESULT = TRUE if he said one.
BerryGarden_EventScript_BramKlaraLine::
	specialvar VAR_RESULT, GardenKlara_TakeBramLine
	goto_if_eq VAR_RESULT, 0, BerryGarden_EventScript_NoReaction
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_BramKlara1
	case 2, BerryGarden_EventScript_BramKlara2
	case 3, BerryGarden_EventScript_BramKlara3
	case 4, BerryGarden_EventScript_BramKlara4
	msgbox BerryGarden_Text_BramKlara5, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted
BerryGarden_EventScript_BramKlara1::
	msgbox BerryGarden_Text_BramKlara1, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted
BerryGarden_EventScript_BramKlara2::
	msgbox BerryGarden_Text_BramKlara2, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted
BerryGarden_EventScript_BramKlara3::
	msgbox BerryGarden_Text_BramKlara3, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted
BerryGarden_EventScript_BramKlara4::
	msgbox BerryGarden_Text_BramKlara4, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ Her opening line of the day (section 14.4 I).
BerryGarden_EventScript_KlaraOpeningLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_KlaraOpening1
	case 2, BerryGarden_EventScript_KlaraOpening2
	case 3, BerryGarden_EventScript_KlaraOpening3
	case 4, BerryGarden_EventScript_KlaraOpening4
	case 5, BerryGarden_EventScript_KlaraOpening5
	case 6, BerryGarden_EventScript_KlaraOpening6
	case 7, BerryGarden_EventScript_KlaraOpening7
	case 8, BerryGarden_EventScript_KlaraOpening8
	case 9, BerryGarden_EventScript_KlaraOpening9
	msgbox BerryGarden_Text_KlaraOpening0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening1::
	msgbox BerryGarden_Text_KlaraOpening1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening2::
	msgbox BerryGarden_Text_KlaraOpening2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening3::
	msgbox BerryGarden_Text_KlaraOpening3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening4::
	msgbox BerryGarden_Text_KlaraOpening4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening5::
	msgbox BerryGarden_Text_KlaraOpening5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening6::
	msgbox BerryGarden_Text_KlaraOpening6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening7::
	msgbox BerryGarden_Text_KlaraOpening7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening8::
	msgbox BerryGarden_Text_KlaraOpening8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KlaraOpening9::
	msgbox BerryGarden_Text_KlaraOpening9, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Texts (in-battle defeat lines have no name box: there is none in battle)
@ ---------------------------------------------------------------------------

BerryGarden_Text_TillyMenu:
	.string "Mulch, or a battle? Mulch is cheaper.$"

BerryGarden_Text_TillyBuyMulch:
	.string "Buy mulch$"

BerryGarden_Text_TillyFight:
	.string "Battle$"

BerryGarden_Text_TillyBye2:
	.string "Bye$"

BerryGarden_Text_TillyIntro:
	.string "Battle time! My bugs have names, so\n"
	.string "they're stronger.\p"
	.string "That's science.$"

BerryGarden_Text_TillyDefeat:
	.string "NOOO! Mr. Roly!\p"
	.string "...He's fine. He's rolling. He's fine.$"

BerryGarden_Text_TillyPrize:
	.string "You won! Here, two from the shop.\p"
	.string "Winners get mulch. Don't tell Grandma.$"

BerryGarden_Text_TillyWon:
	.string "Mr. Roly WINS! I'm telling Grandpa.\p"
	.string "I'm telling EVERYONE.$"

BerryGarden_Text_TillyNap:
	.string "Mr. Roly needs a nap. Come back\n"
	.string "tomorrow!\p"
	.string "He'll be ready. I'll be READIER.$"

BerryGarden_Text_BugsyIntro:
	.string "Field test! I want to see how\n"
	.string "garden-raised bugs do against a real\l"
	.string "trainer.\p"
	.string "For science! Are you in?$"

BerryGarden_Text_BugsyDefeat:
	.string "Fascinating! They lost, but they lost in\n"
	.string "a very well-documented way.$"

BerryGarden_Text_BugsyPrize:
	.string "Your bugs earned this. Well, you did.\p"
	.string "Here -- Berries from the garden. Laurel\n"
	.string "said I could.$"

BerryGarden_Text_BugsyWon:
	.string "A clear result! For the bugs, I mean.\p"
	.string "Rest your team. I'll be here next time.$"

BerryGarden_Text_BugsyBusy:
	.string "I'm still writing up the last one.\p"
	.string "Twelve pages so far.$"

BerryGarden_Text_BugsyDeclined:
	.string "Another time! The bugs aren't going\n"
	.string "anywhere.\p"
	.string "Well. They are. But slowly.$"

BerryGarden_Text_KlaraDefeat:
	.string "Ugh! Seriously?!$"

BerryGarden_Text_KlaraMochi:
	.string "You know what? Berries are SO last\n"
	.string "season. Mochi is the new thing.\p"
	.string "There's this cute little shop in\n"
	.string "Kitakami... Toodles~$"

BerryGarden_Text_KlaraOpening0:
	.string "Oopsie! Didn't see you there, hun~\p"
	.string "These are for my channel. “Top 10 Johto\n"
	.string "Snacks -- Number 7 Will SHOCK You.”$"

BerryGarden_Text_KlaraOpening1:
	.string "Shh! I'm live! ...Hi, besties! Today we're\n"
	.string "foraging!\p"
	.string "Foraging means taking. Don't tell\n"
	.string "anyone~$"

BerryGarden_Text_KlaraOpening2:
	.string "Oh, it's YOU. The Berry police.\p"
	.string "Ugh, fine. Arrest me. In battle. Cutely.$"

BerryGarden_Text_KlaraOpening3:
	.string "These Pecha are, like, SO pink. My\n"
	.string "followers need them.\p"
	.string "It's basically charity.$"

BerryGarden_Text_KlaraOpening4:
	.string "I'm not stealing, hun. I'm “sourcing\n"
	.string "locally.”\p"
	.string "It's a whole trend.$"

BerryGarden_Text_KlaraOpening5:
	.string "Don't look at me like that! I left a\n"
	.string "thank-you note!\p"
	.string "...It says “thx.” It counts!$"

BerryGarden_Text_KlaraOpening6:
	.string "My Slowbro's hungry. And when she's\n"
	.string "hungry she's mean.\p"
	.string "Like me! Hehe~$"

BerryGarden_Text_KlaraOpening7:
	.string "You again?! Do you, like, LIVE in this\n"
	.string "garden? Get a hobby.\p"
	.string "Oh wait. This is your hobby. Cringe.$"

BerryGarden_Text_KlaraOpening8:
	.string "New video idea: “I Battled a Farmer for\n"
	.string "Snacks!”\p"
	.string "You're the farmer. Smile!$"

BerryGarden_Text_KlaraOpening9:
	.string "Okay, okay. Final offer: I take ONE bed,\n"
	.string "you get a shout-out.\p"
	.string "...No? Fine. Battle me, hun~$"

BerryGarden_Text_KlaraLoses0:
	.string "Ugh, FINE. Keep your dumb Berries.\p"
	.string "...Can I at least keep one Pecha? No?\n"
	.string "Rude. So rude.$"

BerryGarden_Text_KlaraLoses1:
	.string "That footage is SO getting deleted.$"

BerryGarden_Text_KlaraLoses2:
	.string "My ring light was in my eyes. That's why.\n"
	.string "Obviously.$"

BerryGarden_Text_KlaraLoses3:
	.string "Whatever! Berries have, like, carbs\n"
	.string "anyway.$"

BerryGarden_Text_KlaraLoses4:
	.string "You're lucky I'm nice. I'm not nice.\p"
	.string "You're just lucky.$"

BerryGarden_Text_KlaraTakes0:
	.string "Thanks for the content, hun! Like and\n"
	.string "subscribe~$"

BerryGarden_Text_KlaraTakes1:
	.string "Ooh, this one's heavy! Must be the good\n"
	.string "stuff. Byeee~$"

BerryGarden_Text_KlaraTakes2:
	.string "Tell the old man I said hi! Actually,\n"
	.string "don't.$"

BerryGarden_Text_KlaraTakes3:
	.string "Harvest complete! Klara out~$"

BerryGarden_Text_KlaraTakes4:
	.string "Don't cry, hun. You can grow more.\p"
	.string "That's, like, what plants DO.$"

BerryGarden_Text_BramKlara1:
	.string "That girl again.\p"
	.string "Laurel says that Slowbro of hers has\n"
	.string "better manners than she does.$"

BerryGarden_Text_BramKlara2:
	.string "She took the WHOLE bed? ...Well. It'll\n"
	.string "grow back.\p"
	.string "Everything grows back. That's the nice\n"
	.string "thing about Berries.$"

BerryGarden_Text_BramKlara3:
	.string "She left a note. “thx.” With a heart.\p"
	.string "Laurel's framing it. Out of spite, I\n"
	.string "think.$"

BerryGarden_Text_BramKlara4:
	.string "When I was a boy we had a word for her\n"
	.string "kind.\p"
	.string "The word was “Tuesday.” Don't ask.$"

BerryGarden_Text_BramKlara5:
	.string "You chased her off? Ha!\p"
	.string "Sprout, you're a real farmer now.\n"
	.string "Farmers have enemies.$"

