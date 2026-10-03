@ Berry Master, plan part 16: Act 7, the epilogue and the garden after the
@ story (REI_DA_COLHEITA.md 8.12, 8.13, 13.3, 13.4, 14.2, 14.4 J/K/L/N/O/S,
@ 14.5). VAR_HARVEST_KING 12/13 -> 14 (Act 7) -> 15 (the epilogue).

@ ---------------------------------------------------------------------------
@ Act 7. Every night in state 12 or 13 Calyrex and Peony wait at Laurel's plot
@ (GardenCast_ApplyStory): Peony (22,38) facing east, Calyrex (23,39). As in
@ Act 5, the scene plays from Bram's door (26,40) on a map load; talking to
@ either of them brings the player there (BerryGarden_EventScript_KingCameTalk).
@ The player steps down to (26,41) and faces west.
@   1. Without the steed in the party: one line, nothing else.
@   2. The trial: Calyrex takes Peony and fights with his team
@      (TRAINER_HARVEST_KING_TRIAL, no whiteout). Lost: try again; won: the
@      trainer flag stays set (no new flag), and the next night skips it.
@   3. The king: level 65, only the capture moves on (state 14).
@   4. Laurel comes out of the door to Peony's side (26,40) -> (22,39) with
@      the Reins of Unity; the Enigma goes into the Book; the whole garden is
@      ripe on the reload (a bountiful harvest).
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_Act7Scene::
	applymovement OBJ_EVENT_ID_PLAYER, BerryGarden_Movement_StepDown
	waitmovement 0
	call BerryGarden_EventScript_HasSteed
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_Act7NoSteed
	goto_if_defeated TRAINER_HARVEST_KING_TRIAL, BerryGarden_EventScript_Act7King
	msgbox BerryGarden_Text_Act7Peony, MSGBOX_DEFAULT
	closemessage
	call BerryGarden_EventScript_Flash
	applymovement LOCALID_ROUTE30_PEONY, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BerryGarden_Text_Act7Found, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, TRUE, BerryGarden_EventScript_Act7Glastrier
	call_if_ne VAR_0x8008, TRUE, BerryGarden_EventScript_Act7Spectrier
	msgbox BerryGarden_Text_Act7Trial, MSGBOX_DEFAULT
	garden_fight TRAINER_HARVEST_KING_TRIAL, BerryGarden_Text_Act7TrialDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_Act7TrialLost
	settrainerflag TRAINER_HARVEST_KING_TRIAL
	msgbox BerryGarden_Text_Act7TrialWon, MSGBOX_DEFAULT
	closemessage
	call BerryGarden_EventScript_Flash
	msgbox BerryGarden_Text_Act7PeonyWakes, MSGBOX_DEFAULT
	closemessage
BerryGarden_EventScript_Act7King::
	checkitemspace ITEM_REINS_OF_UNITY, 1
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_Act7BagFull
	msgbox BerryGarden_Text_Act7ShowMe, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_CALYREX, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_CALYREX, 65
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, BerryGarden_EventScript_Act7Caught
	msgbox BerryGarden_Text_Act7KingWaits, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BerryGarden_EventScript_Act7NoSteed::
	msgbox BerryGarden_Text_Act7NoSteed, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BerryGarden_EventScript_Act7BagFull::
	msgbox BerryGarden_Text_Act7BagFull, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BerryGarden_EventScript_Act7TrialLost::
	special HealPlayerParty
	msgbox BerryGarden_Text_Act7TrialLost, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BerryGarden_EventScript_Act7Glastrier::
	msgbox BerryGarden_Text_Act7Glastrier, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_Act7Spectrier::
	msgbox BerryGarden_Text_Act7Spectrier, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_Act7Caught::
	setvar VAR_HARVEST_KING, HARVEST_KING_ACT7_DONE
	setflag FLAG_TEMP_HIDE_CALYREX
	removeobject LOCALID_ROUTE30_CALYREX
	setobjectxyperm LOCALID_ROUTE30_LAUREL, 26, 40
	setobjectmovementtype LOCALID_ROUTE30_LAUREL, MOVEMENT_TYPE_FACE_LEFT
	clearflag FLAG_TEMP_HIDE_LAUREL
	addobject LOCALID_ROUTE30_LAUREL
	playse SE_EXIT
	waitse
	applymovement LOCALID_ROUTE30_LAUREL, BerryGarden_Movement_LaurelToPeony
	waitmovement 0
	msgbox BerryGarden_Text_Act7Laurel, MSGBOX_DEFAULT
	giveitem ITEM_REINS_OF_UNITY
	setvar VAR_0x8004, ITEM_ENIGMA_BERRY
	special BerryLedger_Register
	msgbox BerryGarden_Text_Act7PeonyGrand, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	special BerryDebug_RipenGarden
	getplayerxy VAR_0x8004, VAR_0x8005
	warpsilent MAP_ROUTE30, VAR_0x8004, VAR_0x8005
	waitstate
	releaseall
	end

@ VAR_RESULT = the steed is in the party; VAR_0x8008 = TRUE on the white path.
BerryGarden_EventScript_HasSteed::
	setvar VAR_0x8004, GARDEN_STORY_WHITE_PATH
	specialvar VAR_0x8008, GardenStory_Check
	goto_if_eq VAR_0x8008, TRUE, BerryGarden_EventScript_HasGlastrier
	checkspecies SPECIES_SPECTRIER
	return
BerryGarden_EventScript_HasGlastrier::
	checkspecies SPECIES_GLASTRIER
	return

@ ---------------------------------------------------------------------------
@ The epilogue (8.13): the first time the player talks to Bram the morning
@ after Act 7, on either map. Act 7 only happens at night, so any morning in
@ state 14 is "the morning after" (even when Act 7 was past midnight, same
@ date); from the afternoon on, it needs the new day GardenRollDay marks
@ (GARDEN_STORY_EPILOGUE_READY). State 15, the garden's level 5 (King's Garden: Laurel's plot back to the
@ player, double harvest), and the guests are gone: the map reloads in place.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_BramEpilogue::
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_ACT7_DONE, BerryGarden_EventScript_StoryEnd
	goto_if_eq VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_MORNING, BerryGarden_EventScript_EpilogueNow
	setvar VAR_0x8004, GARDEN_STORY_EPILOGUE_READY
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
BerryGarden_EventScript_EpilogueNow::
	msgbox BerryGarden_Text_Epilogue1, MSGBOX_DEFAULT
	msgbox BerryGarden_Text_Epilogue2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE
	setvar VAR_BERRY_GARDEN_LEVEL, GARDEN_LEVEL_KINGS
	fadescreen FADE_TO_BLACK
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_MORNING, BerryGarden_EventScript_EpilogueReloadGarden
	warpsilent MAP_ROUTE30_HOUSE, VAR_0x8004, VAR_0x8005
	waitstate
	release
	end
BerryGarden_EventScript_EpilogueReloadGarden::
	warpsilent MAP_ROUTE30, VAR_0x8004, VAR_0x8005
	waitstate
	release
	end

@ The Book's 66 (section 3.4), in Bram's house after the milestones: the title,
@ once. Laurel says the name on her next talk if she has not yet.
BerryGarden_EventScript_BramTitle::
	setvar VAR_0x8004, GARDEN_STORY_TITLE_66
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	specialvar VAR_RESULT, BerryLedger_HasTitle
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	setvar VAR_0x8004, GARDEN_STORY_TITLE_66
	special GardenStory_Mark
	msgbox BerryGarden_Text_BramTitle, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Laurel, after the story or the Book's 66 (14.1 #4: one LaurelSaysName, at
@ whichever comes first; the other gets its own line). First thing in
@ BerryGarden_EventScript_LaurelStory; VAR_RESULT = TRUE when she took the
@ conversation.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_LaurelAfterStory::
	setvar VAR_0x8004, GARDEN_STORY_TITLE_66
	specialvar VAR_0x8009, GardenStory_Check
	goto_if_eq VAR_0x8009, TRUE, BerryGarden_EventScript_LaurelNameCheck
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_NoReaction
BerryGarden_EventScript_LaurelNameCheck::
	setvar VAR_0x8004, GARDEN_STORY_LAUREL_NAME
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_LaurelSecondEvent
	special GardenStory_Mark
	msgbox BerryGarden_Text_LaurelSaysName, MSGBOX_DEFAULT
	@ Whichever event brought it, the other one is still to come (or done).
	call_if_eq VAR_0x8009, TRUE, BerryGarden_EventScript_Mark66Told
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_Reacted
	msgbox BerryGarden_Text_LaurelHoney, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ She had already said the name: the line of the second event, once each.
BerryGarden_EventScript_LaurelSecondEvent::
	goto_if_ne VAR_0x8009, TRUE, BerryGarden_EventScript_LaurelEnigmaCheck
	setvar VAR_0x8004, GARDEN_STORY_LAUREL_66
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_LaurelEnigmaCheck
	special GardenStory_Mark
	msgbox BerryGarden_Text_Laurel66, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_Mark66Told::
	setvar VAR_0x8004, GARDEN_STORY_LAUREL_66
	special GardenStory_Mark
	return

@ After the story, once: her plot grows the Enigma back (section 3.5). The
@ epilogue's Honey letter came with the name; if 66 brought the name first,
@ the letter comes here instead.
BerryGarden_EventScript_LaurelEnigmaCheck::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, GARDEN_STORY_ENIGMA_TOLD
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	special GardenStory_Mark
	msgbox BerryGarden_Text_LaurelEnigma, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ ---------------------------------------------------------------------------
@ Laurel's plot, a Berry tree again from state 15. At night with Calyrex in
@ the party, the king says a line before the Berry menu (bank N). Called first
@ in BerryTreeScript; changes nothing else.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_KingsPlotKing::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_StoryEnd
	specialvar VAR_RESULT, GardenTree_IsKingsPlot
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	gettimeofday
	goto_if_lt VAR_0x8000, TIME_EVENING, BerryGarden_EventScript_StoryEnd
	checkspecies SPECIES_CALYREX
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	@ Line 6 (the statue) only once Freezington's letter about it was read.
	goto_if_ne VAR_RESULT, 5, BerryGarden_EventScript_KingLineN
	setvar VAR_0x8004, GARDEN_STORY_STATUE_LETTER
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_KingN5
	setvar VAR_RESULT, 0
BerryGarden_EventScript_KingLineN::
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_KingN1
	case 2, BerryGarden_EventScript_KingN2
	case 3, BerryGarden_EventScript_KingN3
	case 4, BerryGarden_EventScript_KingN4
	case 5, BerryGarden_EventScript_KingN5
	case 6, BerryGarden_EventScript_KingN6
	case 7, BerryGarden_EventScript_KingN7
	case 8, BerryGarden_EventScript_KingN8
	case 9, BerryGarden_EventScript_KingN9
	msgbox BerryGarden_Text_KingN0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN1::
	msgbox BerryGarden_Text_KingN1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN2::
	msgbox BerryGarden_Text_KingN2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN3::
	msgbox BerryGarden_Text_KingN3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN4::
	msgbox BerryGarden_Text_KingN4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN5::
	msgbox BerryGarden_Text_KingN5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN6::
	msgbox BerryGarden_Text_KingN6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN7::
	msgbox BerryGarden_Text_KingN7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN8::
	msgbox BerryGarden_Text_KingN8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingN9::
	msgbox BerryGarden_Text_KingN9, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Avery, Fridays by day after the story, south of Laurel's plot (23,39).
@ Bank J (10 lines, no hearts). With Calyrex in the party, Laurel's scene
@ (13.4) instead of the line. Then a battle, once a day (14.5); prize: one
@ rare Berry from the Book.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_Avery::
	lock
	faceplayer
	dotimebasedevents
	special GardenRollDay
	checkspecies SPECIES_CALYREX
	call_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_AveryKing
	call_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_AveryLine
	call BerryGarden_EventScript_AveryBattle
	closemessage
	release
	end

BerryGarden_EventScript_AveryKing::
	msgbox BerryGarden_Text_AveryKing, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

BerryGarden_EventScript_AveryBattle::
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_AVERY
	specialvar VAR_RESULT, GardenToday_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_AveryTired
	msgbox BerryGarden_Text_AveryIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BerryGarden_EventScript_StoryEnd
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_AVERY
	special GardenToday_Set
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	goto_if_ge VAR_RESULT, 6, BerryGarden_EventScript_AveryFight3
	goto_if_ge VAR_RESULT, 3, BerryGarden_EventScript_AveryFight2
	garden_fight TRAINER_GARDEN_AVERY_1, BerryGarden_Text_AveryDefeat
	goto BerryGarden_EventScript_AveryAfterFight
BerryGarden_EventScript_AveryFight2::
	garden_fight TRAINER_GARDEN_AVERY_2, BerryGarden_Text_AveryDefeat
	goto BerryGarden_EventScript_AveryAfterFight
BerryGarden_EventScript_AveryFight3::
	garden_fight TRAINER_GARDEN_AVERY_3, BerryGarden_Text_AveryDefeat
BerryGarden_EventScript_AveryAfterFight::
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_RivalWon
	specialvar VAR_RESULT, BerryLedger_RandomRegisteredRare
	goto_if_eq VAR_RESULT, ITEM_NONE, BerryGarden_EventScript_StoryEnd
	copyvar VAR_0x8008, VAR_RESULT
	msgbox BerryGarden_Text_AveryPrize, MSGBOX_DEFAULT
	giveitem VAR_0x8008
	return

BerryGarden_EventScript_AveryTired::
	msgbox BerryGarden_Text_AveryTired, MSGBOX_DEFAULT
	return

@ Lost, a draw or anything else: nothing lost, the party patched up.
BerryGarden_EventScript_RivalWon::
	special HealPlayerParty
	return

BerryGarden_EventScript_AveryLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_AveryJ1
	case 2, BerryGarden_EventScript_AveryJ2
	case 3, BerryGarden_EventScript_AveryJ3
	case 4, BerryGarden_EventScript_AveryJ4
	case 5, BerryGarden_EventScript_AveryJ5
	case 6, BerryGarden_EventScript_AveryJ6
	case 7, BerryGarden_EventScript_AveryJ7
	case 8, BerryGarden_EventScript_AveryJ8
	case 9, BerryGarden_EventScript_AveryJ9
	msgbox BerryGarden_Text_AveryJ0, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	return
BerryGarden_EventScript_AveryJ1::
	msgbox BerryGarden_Text_AveryJ1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ2::
	msgbox BerryGarden_Text_AveryJ2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ3::
	msgbox BerryGarden_Text_AveryJ3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ4::
	msgbox BerryGarden_Text_AveryJ4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ5::
	msgbox BerryGarden_Text_AveryJ5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ6::
	msgbox BerryGarden_Text_AveryJ6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ7::
	msgbox BerryGarden_Text_AveryJ7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ8::
	msgbox BerryGarden_Text_AveryJ8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_AveryJ9::
	msgbox BerryGarden_Text_AveryJ9, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Mustard, a drawn Sunday morning after the story, beside Bram (26,44). Bank
@ S (5 lines: VAR_DAYS % 10 folded onto 5). A battle once a day; prize: one
@ big item (SKELETON: the author picks it - an Exp. Candy L for now).
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_Mustard::
	lock
	faceplayer
	dotimebasedevents
	special GardenRollDay
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_MustardS1
	case 2, BerryGarden_EventScript_MustardS2
	case 3, BerryGarden_EventScript_MustardS3
	case 4, BerryGarden_EventScript_MustardS4
	case 6, BerryGarden_EventScript_MustardS1
	case 7, BerryGarden_EventScript_MustardS2
	case 8, BerryGarden_EventScript_MustardS3
	case 9, BerryGarden_EventScript_MustardS4
	msgbox BerryGarden_Text_MustardS0, MSGBOX_DEFAULT
BerryGarden_EventScript_MustardBattle::
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_MUSTARD
	specialvar VAR_RESULT, GardenToday_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_MustardTired
	msgbox BerryGarden_Text_MustardIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BerryGarden_EventScript_MustardEnd
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_MUSTARD
	special GardenToday_Set
	garden_fight TRAINER_GARDEN_MUSTARD, BerryGarden_Text_MustardDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_MustardLost
	@ SKELETON: the big prize is the author's to choose (section 14.5).
	msgbox BerryGarden_Text_MustardPrize, MSGBOX_DEFAULT
	giveitem ITEM_EXP_CANDY_L
	goto BerryGarden_EventScript_MustardEnd
BerryGarden_EventScript_MustardLost::
	special HealPlayerParty
	goto BerryGarden_EventScript_MustardEnd
BerryGarden_EventScript_MustardTired::
	msgbox BerryGarden_Text_MustardTired, MSGBOX_DEFAULT
BerryGarden_EventScript_MustardEnd::
	closemessage
	release
	end

BerryGarden_EventScript_MustardS1::
	msgbox BerryGarden_Text_MustardS1, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_MustardBattle
BerryGarden_EventScript_MustardS2::
	msgbox BerryGarden_Text_MustardS2, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_MustardBattle
BerryGarden_EventScript_MustardS3::
	msgbox BerryGarden_Text_MustardS3, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_MustardBattle
BerryGarden_EventScript_MustardS4::
	msgbox BerryGarden_Text_MustardS4, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_MustardBattle

@ ---------------------------------------------------------------------------
@ Peonia after the story: weekend nights by the pond (31,38), next to Peony,
@ her own battle; weekend days at Tilly's stall (25,41), the double battle
@ with Tilly (14.5). Bank L whole. One battle a day for her, either kind.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_PeoniaAfter::
	call BerryGarden_EventScript_PeoniaLineFull
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_PEONIA
	specialvar VAR_RESULT, GardenToday_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_PeoniaTired
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_TeamMulch
	msgbox BerryGarden_Text_PeoniaIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BerryGarden_EventScript_PeoniaEnd
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_PEONIA
	special GardenToday_Set
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	goto_if_ge VAR_RESULT, 6, BerryGarden_EventScript_PeoniaFight3
	goto_if_ge VAR_RESULT, 3, BerryGarden_EventScript_PeoniaFight2
	garden_fight TRAINER_GARDEN_PEONIA_1, BerryGarden_Text_PeoniaDefeat
	goto BerryGarden_EventScript_PeoniaAfterFight
BerryGarden_EventScript_PeoniaFight2::
	garden_fight TRAINER_GARDEN_PEONIA_2, BerryGarden_Text_PeoniaDefeat
	goto BerryGarden_EventScript_PeoniaAfterFight
BerryGarden_EventScript_PeoniaFight3::
	garden_fight TRAINER_GARDEN_PEONIA_3, BerryGarden_Text_PeoniaDefeat
BerryGarden_EventScript_PeoniaAfterFight::
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_PeoniaLost
	msgbox BerryGarden_Text_PeoniaPrize, MSGBOX_DEFAULT
	giveitem ITEM_GROWTH_MULCH, 2
	goto BerryGarden_EventScript_PeoniaEnd
BerryGarden_EventScript_PeoniaLost::
	special HealPlayerParty
	goto BerryGarden_EventScript_PeoniaEnd
BerryGarden_EventScript_PeoniaTired::
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_TeamMulchTired
	msgbox BerryGarden_Text_PeoniaTired, MSGBOX_DEFAULT
BerryGarden_EventScript_PeoniaEnd::
	closemessage
	release
	end

@ Tilly + Peonia (14.5): two trainers, no whiteout. Needs two Pokémon able
@ to battle; the trainer flags are cleared before and after, like garden_fight.
BerryGarden_EventScript_TeamMulch::
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, BerryGarden_EventScript_TeamMulchNeedsTwo
	msgbox BerryGarden_Text_TeamMulchIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BerryGarden_EventScript_PeoniaEnd
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_PEONIA
	special GardenToday_Set
	closemessage
	cleartrainerflag TRAINER_GARDEN_TILLY_DUO
	cleartrainerflag TRAINER_GARDEN_PEONIA_DUO
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_two_trainers TRAINER_GARDEN_TILLY_DUO, BerryGarden_Text_TeamMulchDefeatTilly, TRAINER_GARDEN_PEONIA_DUO, BerryGarden_Text_TeamMulchDefeatPeonia
	clearflag B_FLAG_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT
	cleartrainerflag TRAINER_GARDEN_TILLY_DUO
	cleartrainerflag TRAINER_GARDEN_PEONIA_DUO
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_PeoniaLost
	msgbox BerryGarden_Text_TeamMulchWon, MSGBOX_DEFAULT
	giveitem ITEM_SURPRISE_MULCH
	goto BerryGarden_EventScript_PeoniaEnd

BerryGarden_EventScript_TeamMulchNeedsTwo::
	msgbox BerryGarden_Text_TeamMulchNeedsTwo, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_PeoniaEnd

BerryGarden_EventScript_TeamMulchTired::
	msgbox BerryGarden_Text_TeamMulchTired, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_PeoniaEnd

BerryGarden_EventScript_PeoniaLineFull::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_PeoniaL1
	case 2, BerryGarden_EventScript_PeoniaL2
	case 3, BerryGarden_EventScript_PeoniaL3
	case 4, BerryGarden_EventScript_PeoniaL4
	case 5, BerryGarden_EventScript_PeoniaL5
	case 6, BerryGarden_EventScript_PeoniaL6
	case 7, BerryGarden_EventScript_PeoniaL7
	case 8, BerryGarden_EventScript_PeoniaL8
	case 9, BerryGarden_EventScript_PeoniaL9
	msgbox BerryGarden_Text_PeoniaL0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL5::
	msgbox BerryGarden_Text_PeoniaL5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL6::
	msgbox BerryGarden_Text_PeoniaL6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL7::
	msgbox BerryGarden_Text_PeoniaL7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL8::
	msgbox BerryGarden_Text_PeoniaL8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL9::
	msgbox BerryGarden_Text_PeoniaL9, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------- texts (p16/gen_texts.py)
BerryGarden_Text_Act7Peony:
	.string "{SPEAKER NAME_PEONY}Chum, that's a KING. I've met a king\n"
	.string "before. Well, a Chairman. My big brother.\l"
	.string "Not the same.\p"
	.string "Go easy on him! No -- don't go easy.\n"
	.string "He'd hate that.$"

BerryGarden_Text_Act7Found:
	.string "{SPEAKER NAME_CALYREX}You found him.$"

BerryGarden_Text_Act7Glastrier:
	.string "{SPEAKER NAME_CALYREX}Still stubborn. Still cold. Still mine.$"

BerryGarden_Text_Act7Spectrier:
	.string "{SPEAKER NAME_CALYREX}So it was you, eating the Berries at\n"
	.string "night. I should have known.$"

BerryGarden_Text_Act7Trial:
	.string "{SPEAKER NAME_CALYREX}Good. Now a king must know who carries\n"
	.string "his harvest.\p"
	.string "This one's Pokémon are strong, and very\n"
	.string "fond of him. They will fight for me\l"
	.string "tonight. Forgive us both.$"

BerryGarden_Text_Act7TrialDefeat:
	.string "...Enough. I have seen what I needed.$"

BerryGarden_Text_Act7TrialWon:
	.string "{SPEAKER NAME_CALYREX}Yes. You are the one the field\n"
	.string "remembers.$"

BerryGarden_Text_Act7PeonyWakes:
	.string "{SPEAKER NAME_PEONY}...Did I win? I feel like I lost.\p"
	.string "Me Copperajah's looking at me funny.$"

BerryGarden_Text_Act7ShowMe:
	.string "{SPEAKER NAME_CALYREX}Now. A king returns to his power the old\n"
	.string "way.\p"
	.string "Show me yours.$"

BerryGarden_Text_Act7KingWaits:
	.string "The king steps back among the leaves.\p"
	.string "He has waited forty years. He can wait\n"
	.string "one more night.$"

BerryGarden_Text_Act7NoSteed:
	.string "{SPEAKER NAME_CALYREX}Where is my steed?\p"
	.string "Bring him to me.$"

BerryGarden_Text_Act7BagFull:
	.string "{SPEAKER NAME_CALYREX}Your Bag is full. Laurel has something\n"
	.string "for you, and nowhere to put it.\p"
	.string "Come back with room.$"

BerryGarden_Text_Act7TrialLost:
	.string "{SPEAKER NAME_CALYREX}Not tonight.\p"
	.string "Rest, and come back. The field is\n"
	.string "patient. So am I.$"

BerryGarden_Text_Act7Laurel:
	.string "{SPEAKER NAME_LAUREL}...\p"
	.string "My grandmother said he'd come back\n"
	.string "when someone grew a garden for him\l"
	.string "instead of for themselves.\p"
	.string "This belonged to her. It's for riding.\n"
	.string "You'll know what to do with it.$"

BerryGarden_Text_Act7PeonyGrand:
	.string "{SPEAKER NAME_PEONY}Grand! Absolutely grand!\p"
	.string "You know, back home there's ruins with\n"
	.string "a choice in 'em too. Two doors, one pick.\p"
	.string "Johto's got ruins. I've got a feeling.\n"
	.string "Come find me when you're ready for an\l"
	.string "expedition.$"

BerryGarden_Text_Epilogue1:
	.string "You know what Laurel did this morning?\n"
	.string "She sang. At breakfast.\p"
	.string "Forty years. I didn't know she could\n"
	.string "sing.\p"
	.string "The patch by the door's yours too now.\n"
	.string "She said so. Plant whatever you want in\l"
	.string "it.\p"
	.string "It gives double. Don't ask me how. I\n"
	.string "stopped asking questions last night.$"

BerryGarden_Text_Epilogue2:
	.string "Oh -- Kurt came by at dawn. First time\n"
	.string "he's left Azalea since I don't know\l"
	.string "when.\p"
	.string "Said he “felt it in his knees.” Took a\n"
	.string "sack of Berries and left. Didn't pay.\p"
	.string "And Peony and the girl went home at\n"
	.string "sunrise. Said they'd be back on\l"
	.string "weekends, to camp by the pond.$"

BerryGarden_Text_BramTitle:
	.string "Sixty-six. Every Berry there is, bar the\n"
	.string "king's.\p"
	.string "I had to count twice. Laurel counted\n"
	.string "three times.\p"
	.string "You're the Berry Master now, sprout.\n"
	.string "...I'm just Bram. Suits me fine.$"

BerryGarden_Text_LaurelSaysName:
	.string "{PLAYER}.\p"
	.string "...What? I know your name. I've always\n"
	.string "known your name.$"

BerryGarden_Text_LaurelHoney:
	.string "Honey wrote. Mustard cried when he read\n"
	.string "about the king.\p"
	.string "He says it was hay fever. He's lived on\n"
	.string "an island with no hay for fifty years.$"

BerryGarden_Text_Laurel66:
	.string "Sixty-six. All of them but his.\p"
	.string "Bram cried in the shed. Leave him be.$"

BerryGarden_Text_LaurelEnigma:
	.string "Leave my plot empty and it grows his\n"
	.string "Berry back on its own. It remembers now.\p"
	.string "Don't ask me how. I stopped asking\n"
	.string "questions too.$"

BerryGarden_Text_KingN0:
	.string "{SPEAKER NAME_CALYREX}This field has grown fond of you. So\n"
	.string "have I.$"

BerryGarden_Text_KingN1:
	.string "{SPEAKER NAME_CALYREX}Leave the Enigma here. I like to know\n"
	.string "where it is.$"

BerryGarden_Text_KingN2:
	.string "{SPEAKER NAME_CALYREX}The steed wants to run. Let him,\n"
	.string "sometime.$"

BerryGarden_Text_KingN3:
	.string "{SPEAKER NAME_CALYREX}Bram talks to the trees. They do listen.\n"
	.string "I would know.$"

BerryGarden_Text_KingN4:
	.string "{SPEAKER NAME_CALYREX}Tilly asked me if I am a turnip. I said\n"
	.string "yes. It seemed kind.$"

BerryGarden_Text_KingN5:
	.string "{SPEAKER NAME_CALYREX}In Freezington they have mended my\n"
	.string "statue. I felt it, all the way here. It\l"
	.string "tickled.$"

BerryGarden_Text_KingN6:
	.string "{SPEAKER NAME_CALYREX}When you are old, grow something. It\n"
	.string "does not matter what.$"

BerryGarden_Text_KingN7:
	.string "{SPEAKER NAME_CALYREX}I have eaten three Pecha tonight. A\n"
	.string "king may do as he likes.$"

BerryGarden_Text_KingN8:
	.string "{SPEAKER NAME_CALYREX}The bugs of this garden are very well\n"
	.string "fed. Your Bugsy is a good steward.$"

BerryGarden_Text_KingN9:
	.string "{SPEAKER NAME_CALYREX}Thank you. I do not say it enough. Kings\n"
	.string "rarely do.$"

BerryGarden_Text_AveryKing:
	.string "{SPEAKER NAME_AVERY}Ahem. O King of Bountiful Harvest. It is\n"
	.string "I, Avery, psychic prodigy.\p"
	.string "...He is not answering. The patch is not\n"
	.string "answering me.\p"
	.string "{SPEAKER NAME_LAUREL}It's a patch of dirt, dear. The king's in\n"
	.string "{PLAYER}'s Bag.\p"
	.string "{SPEAKER NAME_AVERY}I KNEW that.$"

BerryGarden_Text_AveryJ0:
	.string "{SPEAKER NAME_AVERY}Ahem. O King of Bountiful Harvest. It is\n"
	.string "I, Avery, psychic prodigy.\p"
	.string "...He is not answering. The patch is not\n"
	.string "answering me.$"

BerryGarden_Text_AveryJ1:
	.string "{SPEAKER NAME_AVERY}Perhaps the king prefers a quieter\n"
	.string "mind. I shall be quieter.\p"
	.string "...Starting tomorrow.$"

BerryGarden_Text_AveryJ2:
	.string "{SPEAKER NAME_AVERY}My Slowpoke understands me. Why can't\n"
	.string "a vegetable monarch?$"

BerryGarden_Text_AveryJ3:
	.string "{SPEAKER NAME_AVERY}I have brought an offering. It is a\n"
	.string "scone. Mother made it.$"

BerryGarden_Text_AveryJ4:
	.string "{SPEAKER NAME_AVERY}Klara says I'm talking to a garden. I am\n"
	.string "COMMUNING. There is a difference.$"

BerryGarden_Text_AveryJ5:
	.string "{SPEAKER NAME_AVERY}I sense... great power. Oh. It's you.\n"
	.string "Hello. You may go.$"

BerryGarden_Text_AveryJ6:
	.string "{SPEAKER NAME_AVERY}I bent a spoon for the king. As tribute.\n"
	.string "Laurel took it for the kitchen.$"

BerryGarden_Text_AveryJ7:
	.string "{SPEAKER NAME_AVERY}The Master says the strongest mind is\n"
	.string "an empty one. I've been practicing.\p"
	.string "It's very hard for someone as gifted as\n"
	.string "I am.$"

BerryGarden_Text_AveryJ8:
	.string "{SPEAKER NAME_AVERY}The king spoke to ME once. Well. It was a\n"
	.string "sneeze. But a very meaningful sneeze.$"

BerryGarden_Text_AveryJ9:
	.string "{SPEAKER NAME_AVERY}I came to Johto to train. Also because\n"
	.string "Klara came. Not BECAUSE of Klara.\l"
	.string "Coincidence.\p"
	.string "...Psychics don't believe in\n"
	.string "coincidence. Forget I said that.$"

BerryGarden_Text_AveryIntro:
	.string "{SPEAKER NAME_AVERY}The king ignores me. You will not.\p"
	.string "Behold -- a psychic prodigy! Will you\n"
	.string "battle me?$"

BerryGarden_Text_AveryDefeat:
	.string "Hmph. I was holding back. Out of\n"
	.string "courtesy. To the vegetables.$"

BerryGarden_Text_AveryPrize:
	.string "{SPEAKER NAME_AVERY}Take this. Laurel says it's rare. I say\n"
	.string "it is a tribute. To me. From you.$"

BerryGarden_Text_AveryTired:
	.string "{SPEAKER NAME_AVERY}My mind is exhausted. I am resting it. By\n"
	.string "talking. Leave.$"

BerryGarden_Text_MustardS0:
	.string "{SPEAKER NAME_MUSTARD}Hmhm! So YOU'RE the one Honey keeps\n"
	.string "writing about!\p"
	.string "The Berries are real! I thought she was\n"
	.string "making it up to get me to exercise!$"

BerryGarden_Text_MustardS1:
	.string "{SPEAKER NAME_MUSTARD}Bram! Arm wrestle! ...No?\p"
	.string "Then I'll arm wrestle your student. With\n"
	.string "Pokémon. It's the same thing.$"

BerryGarden_Text_MustardS2:
	.string "{SPEAKER NAME_MUSTARD}My knees? Perfect! Never better!\p"
	.string "...Could I sit down for a moment? Just a\n"
	.string "small moment.$"

BerryGarden_Text_MustardS3:
	.string "{SPEAKER NAME_MUSTARD}I told my students, “Go to Johto and\n"
	.string "learn humility from a garden.”\p"
	.string "None of them went. So I came myself!$"

BerryGarden_Text_MustardS4:
	.string "{SPEAKER NAME_MUSTARD}Laurel! Honey sends her love, and a jar\n"
	.string "of jam.\p"
	.string "It hasn't exploded yet. Stand back,\n"
	.string "just in case.$"

BerryGarden_Text_MustardIntro:
	.string "{SPEAKER NAME_MUSTARD}Hmhm! Let's see what the garden taught\n"
	.string "you! Master Mustard, ready!\p"
	.string "Shall we?$"

BerryGarden_Text_MustardDefeat:
	.string "Wonderful! Wonderful! My knees hurt,\n"
	.string "but WONDERFUL!$"

BerryGarden_Text_MustardPrize:
	.string "{SPEAKER NAME_MUSTARD}A prize for my newest student! Don't\n"
	.string "tell Honey I gave it away.$"

BerryGarden_Text_MustardTired:
	.string "{SPEAKER NAME_MUSTARD}I've had my fun! Now I'll have my nap.\n"
	.string "Bram said I can use his chair.$"

BerryGarden_Text_PeoniaIntro:
	.string "{SPEAKER NAME_PEONIA}Dad talks. I battle. Let's go?$"

BerryGarden_Text_PeoniaDefeat:
	.string "...Okay. You're good. Don't tell Dad I\n"
	.string "said that.$"

BerryGarden_Text_PeoniaPrize:
	.string "{SPEAKER NAME_PEONIA}Here. Mulch. Tilly says it's the good\n"
	.string "kind.\p"
	.string "Tilly says that about all of it.$"

BerryGarden_Text_PeoniaTired:
	.string "{SPEAKER NAME_PEONIA}Rematch tomorrow. I'm writing down\n"
	.string "everything you did.$"

BerryGarden_Text_TeamMulchIntro:
	.string "{SPEAKER NAME_TILLY}Team Mulch!\p"
	.string "{SPEAKER NAME_PEONIA}We are NOT calling it that.\p"
	.string "{SPEAKER NAME_TILLY}Team Mulch!! Battle us?$"

BerryGarden_Text_TeamMulchDefeatTilly:
	.string "NOOO! Team Mulch!$"

BerryGarden_Text_TeamMulchDefeatPeonia:
	.string "Okay. We can call it Team Mulch.$"

BerryGarden_Text_TeamMulchWon:
	.string "{SPEAKER NAME_TILLY}You beat Team Mulch! You get the good\n"
	.string "mulch!$"

BerryGarden_Text_TeamMulchNeedsTwo:
	.string "{SPEAKER NAME_PEONIA}Team Mulch is two of us. You'll need two\n"
	.string "Pokémon who can battle.$"

BerryGarden_Text_TeamMulchTired:
	.string "{SPEAKER NAME_TILLY}Team Mulch is resting.\p"
	.string "{SPEAKER NAME_PEONIA}Team Mulch is eating all the Pecha.$"

BerryGarden_Text_PeoniaL5:
	.string "Tilly's hired me. I'm “Assistant Mulch\n"
	.string "Manager.”\p"
	.string "I get paid in Berries. Mostly Pecha.\n"
	.string "Mostly bitten.$"

BerryGarden_Text_PeoniaL6:
	.string "Grandpa Bram -- he said I could call him\n"
	.string "that -- taught me how to tell a ripe\l"
	.string "Berry.\p"
	.string "You don't. The Berry tells you. I think\n"
	.string "he made that up.$"

BerryGarden_Text_PeoniaL7:
	.string "Auntie Laurel's the only one who can\n"
	.string "tell Dad “no” and make it stick.\p"
	.string "I'm studying her technique.$"

BerryGarden_Text_PeoniaL8:
	.string "I'm training for a real expedition\n"
	.string "someday. Not Dad's kind. The kind with\l"
	.string "maps.$"

BerryGarden_Text_PeoniaL9:
	.string "Thanks for taking me along, back then. I\n"
	.string "was scared.\p"
	.string "I'm telling you that once. Only once.$"

BerryGarden_Text_PeonyK6:
	.string "The king still talks through me\n"
	.string "sometimes. In me sleep.\p"
	.string "Peonia says I say “carrots” a lot.$"

BerryGarden_Text_Letter3:
	.string "From Sonia.\p"
	.string "“The King of Bountiful Harvest is\n"
	.string "chapter nine of my book! May I visit?\p"
	.string "I'll bring Yamper. He's very polite. He\n"
	.string "is not polite.”$"

BerryGarden_Text_Letter7:
	.string "From Freezington.\p"
	.string "“We mended the old statue in the\n"
	.string "square. Nobody remembers who\l"
	.string "suggested it.\p"
	.string "The Mayor cried. So did the statue, a\n"
	.string "bit, when the ice melted.”$"

BerryGarden_Text_Letter8:
	.string "From Honey.\p"
	.string "“Mustard has taken up gardening. He\n"
	.string "planted one seed and named it. He talks\l"
	.string "to it.\p"
	.string "I hear you know the type.”$"

BerryGarden_Text_Letter9:
	.string "From Sonia.\p"
	.string "“Leon says hello. Well -- Leon got lost\n"
	.string "on the way to the post office, so I'm\l"
	.string "saying it for him.”$"
