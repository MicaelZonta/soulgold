@ ===========================================================================
@ Berry Master's garden: "The Harvest King", prologue to Act 4 (plan part 12;
@ REI_DA_COLHEITA.md sections 8.2-8.9 with the rev2 note on Act 4).
@
@ VAR_HARVEST_KING (HARVEST_KING_* in include/constants/berry_garden.h):
@   0 -> 1  prologue      Bram, end of the first conversation (tutorial or an
@                          old save's next talk)               Route30_House
@   1 -> 2  Act 1a        first garden pest beaten or caught    berry_tree.inc
@   2 -> 3  Act 1b        talk to Bugsy (he comes by day once the 2nd badge is in)
@   3 -> 4  Act 1c        3 garden-only families caught + talk to Bugsy
@   4 -> 5  Act 2         garden level 3, night: the visitor at bed B (leaving
@                          Bram's house, or walking up to it)
@   5 -> 6  Act 2b        talk to Bram at night: he wakes
@   6 -> 7  Act 3         Book 40 + 7th badge + Laurel at night: the Enigma
@   7 -> 8  Act 4         the Enigma sprouted in Laurel's plot; by day she kneels
@                          there; talk to her: Bram comes out
@ No act stops the garden routine. One-time lines: GardenStory_* (bits in
@ VAR_GARDEN_NEWS). Who stands where for a scene: GardenCast_ApplyStory.
@ Surprise: nothing reachable before state 6 says king, Calyrex or steeds;
@ Act 3 (6 -> 7) is where Laurel tells the story.
@ ===========================================================================

@ ---------------------------------------------------------------------------
@ Prologue (8.2). Called from Route30_House_EventScript_AfterGift. Laurel
@ answers only if she is on the same map (FLAG_TEMP_HIDE_LAUREL clear).
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_Prologue::
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_NONE, BerryGarden_EventScript_StoryEnd
	goto_if_set FLAG_TEMP_HIDE_LAUREL, BerryGarden_EventScript_PrologueAlone
	msgbox BerryGarden_Text_PrologueWithLaurel, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_PrologueDone

BerryGarden_EventScript_PrologueAlone::
	msgbox BerryGarden_Text_PrologueAlone, MSGBOX_DEFAULT
BerryGarden_EventScript_PrologueDone::
	setvar VAR_HARVEST_KING, HARVEST_KING_PROLOGUE
BerryGarden_EventScript_StoryEnd::
	return

@ ---------------------------------------------------------------------------
@ Act 1a (8.3). berry_tree.inc, right after a garden pest's battle.
@ Beaten or caught, in state 1: state 2, and Laurel, if she is out in the
@ garden, turns and names it. Bram shouts on his next talk (BramStoryLine).
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_PestAfter::
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_PROLOGUE, BerryGarden_EventScript_StoryEnd
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BerryGarden_EventScript_FirstPest
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, BerryGarden_EventScript_FirstPest
	return

BerryGarden_EventScript_FirstPest::
	setvar VAR_HARVEST_KING, HARVEST_KING_VISITORS
	goto_if_set FLAG_TEMP_HIDE_LAUREL, BerryGarden_EventScript_StoryEnd
	specialvar VAR_RESULT, GardenPest_LastSpecies
	bufferspeciesname STR_VAR_1, VAR_RESULT
	applymovement LOCALID_ROUTE30_LAUREL, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BerryGarden_Text_LaurelFirstPest, MSGBOX_DEFAULT
	return

@ Bram's one-time story lines, first thing in his reaction (BramReaction).
@ Returns VAR_RESULT = TRUE if he said one.
BerryGarden_EventScript_BramStoryLine::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_VISITORS, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, GARDEN_STORY_BRAM_BUGS
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	special GardenStory_Mark
	msgbox BerryGarden_Text_BramBugs, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ ---------------------------------------------------------------------------
@ Acts 1b and 1c (8.4, 8.5): Bugsy at (29,41). Called first in his script;
@ VAR_RESULT = TRUE when the story took the conversation.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_BugsyStory::
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_VISITORS, BerryGarden_EventScript_BugsyArrives
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_BUGSY_CAME, BerryGarden_EventScript_BugsyCensus
	goto BerryGarden_EventScript_NoReaction

BerryGarden_EventScript_BugsyArrives::
	msgbox BerryGarden_Text_BugsyArrives, MSGBOX_DEFAULT
	setvar VAR_HARVEST_KING, HARVEST_KING_BUGSY_CAME
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BugsyCensus::
	specialvar VAR_RESULT, GardenPests_FamiliesCaught
	goto_if_ge VAR_RESULT, GARDEN_CENSUS_FAMILIES, BerryGarden_EventScript_BugsyCensusDone
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox BerryGarden_Text_BugsyCensusSoFar, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BugsyCensusDone::
	checkitemspace ITEM_SILVER_POWDER
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_BugsyCensusBagFull
	msgbox BerryGarden_Text_BugsyCensus, MSGBOX_DEFAULT
	giveitem ITEM_SILVER_POWDER
	setvar VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_BugsyCensusBagFull::
	msgbox BerryGarden_Text_BugsyBagFull, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ ---------------------------------------------------------------------------
@ Act 2 (8.6): the night visitor, LOCALID_ROUTE30_SPECTRIER at (31,40) on bed
@ B, facing east (its back to the house door). Two ways in, both with the
@ player on the same row or next to it:
@   - leaving Bram's house: the player appears at (26,40), 5 tiles west, in
@     sight (Route30_OnFrame, VAR_TEMP_GARDEN_SCENE);
@   - talking to it from (30,40) or (31,39).
@ It looks at the player (same row: west), cries, flash, and runs east into
@ the pond. Never a battle here. fadescreenswapbuffers, never fadescreen:
@ it is night (encenar-cutscene / evoluir-historia-de-evento).
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_SceneOnLoad::
	setvar VAR_TEMP_GARDEN_SCENE, 2
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 26, BerryGarden_EventScript_SceneOnLoadEnd
	goto_if_ne VAR_0x8005, 40, BerryGarden_EventScript_SceneOnLoadEnd
	lockall
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_FIRST_LEAF, BerryGarden_EventScript_KingCameScene
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_GLASTRIER, BerryGarden_EventScript_Act7Scene
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_SPECTRIER, BerryGarden_EventScript_Act7Scene
	goto BerryGarden_EventScript_NightVisitorScene

BerryGarden_EventScript_SceneOnLoadEnd::
	end

BerryGarden_EventScript_NightVisitor::
	lockall
BerryGarden_EventScript_NightVisitorScene::
	fadeoutbgm 4
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE30_SPECTRIER, Common_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_SPECTRIER, CRY_MODE_ENCOUNTER
	waitmoncry
	call BerryGarden_EventScript_Flash
	applymovement LOCALID_ROUTE30_SPECTRIER, BerryGarden_Movement_VisitorFlees
	waitmovement 0
	setflag FLAG_TEMP_HIDE_SPECTRIER
	removeobject LOCALID_ROUTE30_SPECTRIER
	msgbox BerryGarden_Text_NightVisitor, MSGBOX_DEFAULT
	msgbox BerryGarden_Text_Hoofprints, MSGBOX_DEFAULT
	closemessage
	setvar VAR_HARVEST_KING, HARVEST_KING_FOOTPRINTS
	fadedefaultbgm
	releaseall
	end

BerryGarden_EventScript_Flash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

BerryGarden_Movement_VisitorFlees:
	walk_faster_right
	walk_faster_right
	walk_faster_right
	step_end

@ ---------------------------------------------------------------------------
@ Act 2b (8.7): Bram asleep at night in state 5 wakes up instead of dreaming
@ (Route30_House_EventScript_CheckAsleep). He stays at the table.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_BramWakes::
	applymovement LOCALID_HOUSE_BRAM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HOUSE_BRAM, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BerryGarden_Text_BramWakes, MSGBOX_DEFAULT
	setvar VAR_HARVEST_KING, HARVEST_KING_BRAM_TOLD
	closemessage
	release
	end

@ ---------------------------------------------------------------------------
@ Laurel's story, first thing in her conversation (BerryWife). VAR_RESULT =
@ TRUE when it took the conversation (the caller ends it).
@   Act 3 (8.8)   night, state 6, Book 40, 7th badge: the notebook and the Enigma
@   state 7       her plot still empty, no Enigma in the bag: another one, once a day
@   morning after Act 2  "You were out late."           (one time)
@   night after Act 4    "I wrote to Freezington."      (one time)
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_LaurelStory::
	setvar VAR_RESULT, FALSE
	@ Part 16: her name for the player, the Book's 66, the Enigma (once each).
	call BerryGarden_EventScript_LaurelAfterStory
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_BRAM_TOLD, BerryGarden_EventScript_LaurelNotebookCheck
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_NOTEBOOK, BerryGarden_EventScript_LaurelEnigmaAgain
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	call BerryGarden_EventScript_LaurelPickedCheck
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_LaurelHeardCheck
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_FIRST_LEAF, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, GARDEN_STORY_WROTE_HOME
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	special GardenStory_Mark
	msgbox BerryGarden_Text_LaurelWroteHome, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelHeardCheck::
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_MORNING, BerryGarden_EventScript_NoReaction
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_FOOTPRINTS, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, GARDEN_STORY_LAUREL_HEARD
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	special GardenStory_Mark
	msgbox BerryGarden_Text_LaurelHeardIt, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelNotebookCheck::
	setvar VAR_RESULT, FALSE
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_NoReaction
	goto_if_unset FLAG_BADGE07_GET, BerryGarden_EventScript_NoReaction
	specialvar VAR_RESULT, BerryLedger_Count
	goto_if_lt VAR_RESULT, 40, BerryGarden_EventScript_NoReaction
	checkitemspace ITEM_ENIGMA_BERRY
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_LaurelNotebookBagFull
	applymovement LOCALID_HOUSE_SUNFLORA, Common_Movement_ExclamationMark
	waitmovement 0
	playmoncry SPECIES_SUNFLORA, CRY_MODE_NORMAL
	waitmoncry
	msgbox BerryGarden_Text_LaurelNotebook1, MSGBOX_DEFAULT
	msgbox BerryGarden_Text_LaurelNotebook2, MSGBOX_DEFAULT
	giveitem ITEM_ENIGMA_BERRY
	setvar VAR_HARVEST_KING, HARVEST_KING_NOTEBOOK
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelNotebookBagFull::
	msgbox BerryGarden_Text_LaurelNotebookBagFull, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ State 7 until the Enigma is in her plot: if it is not in the bag either, she
@ hands over another, once a day (her daily mark, FLAG_DAILY_BERRY_MASTERS_WIFE:
@ "Laurel gave you her Berry today").
BerryGarden_EventScript_LaurelEnigmaAgain::
	setvar VAR_RESULT, FALSE
	specialvar VAR_RESULT, GardenKingsPlot_Stage
	goto_if_ne VAR_RESULT, BERRY_STAGE_NO_BERRY, BerryGarden_EventScript_NoReaction
	checkitem ITEM_ENIGMA_BERRY
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	goto_if_set FLAG_DAILY_BERRY_MASTERS_WIFE, BerryGarden_EventScript_NoReaction
	checkitemspace ITEM_ENIGMA_BERRY
	goto_if_eq VAR_RESULT, FALSE, BerryGarden_EventScript_NoReaction
	specialvar VAR_RESULT, GardenPlots_HaveEnigma
	call_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_LaurelThatsABed
	call_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_LaurelLostIt
	giveitem ITEM_ENIGMA_BERRY
	setflag FLAG_DAILY_BERRY_MASTERS_WIFE
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_LaurelThatsABed::
	msgbox BerryGarden_Text_LaurelThatsABed, MSGBOX_DEFAULT
	setvar VAR_RESULT, TRUE
	return

BerryGarden_EventScript_LaurelLostIt::
	msgbox BerryGarden_Text_LaurelLostIt, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Act 4 (8.9). By day, state 7, the Enigma sprouted: Laurel kneels at (23,39)
@ facing her plot (23,38) (GardenCast_ApplyStory). Talked to from (23,40) or
@ (22,39) - (24,39) is wall. Called BEFORE her faceplayer (she does not look
@ up). Bram comes out of the door (appears at (26,40), the door's tile below
@ the warp) and walks west on row 40:
@   player at (23,40): 2 steps -> (24,40), next to the player
@   player at (22,39): 3 steps -> (23,40), right below Laurel
@ He looks up at her, then west at the player. The scene ends with a silent
@ reload under fade (who is where comes back to the routine).
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_FirstLeafCheck::
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_NOTEBOOK, BerryGarden_EventScript_StoryEnd
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_DAY, BerryGarden_EventScript_StoryEnd
	specialvar VAR_RESULT, GardenKingsPlot_Stage
	goto_if_lt VAR_RESULT, BERRY_STAGE_SPROUTED, BerryGarden_EventScript_StoryEnd
	getplayerxy VAR_0x8004, VAR_0x8005
	msgbox BerryGarden_Text_FirstLeaf1, MSGBOX_DEFAULT
	closemessage
	setobjectxyperm LOCALID_ROUTE30_BRAM, 26, 40
	setobjectmovementtype LOCALID_ROUTE30_BRAM, MOVEMENT_TYPE_FACE_LEFT
	clearflag FLAG_TEMP_HIDE_BRAM
	addobject LOCALID_ROUTE30_BRAM
	playse SE_EXIT
	waitse
	goto_if_eq VAR_0x8004, 23, BerryGarden_EventScript_FirstLeafBramNear
	applymovement LOCALID_ROUTE30_BRAM, BerryGarden_Movement_BramThreeWest
	goto BerryGarden_EventScript_FirstLeafTalk

BerryGarden_EventScript_FirstLeafBramNear::
	applymovement LOCALID_ROUTE30_BRAM, BerryGarden_Movement_BramTwoWest
BerryGarden_EventScript_FirstLeafTalk::
	waitmovement 0
	turnobject LOCALID_ROUTE30_BRAM, DIR_NORTH
	msgbox BerryGarden_Text_FirstLeaf2, MSGBOX_DEFAULT
	turnobject LOCALID_ROUTE30_BRAM, DIR_WEST
	msgbox BerryGarden_Text_FirstLeaf3, MSGBOX_DEFAULT
	closemessage
	setvar VAR_HARVEST_KING, HARVEST_KING_FIRST_LEAF
	fadescreen FADE_TO_BLACK
	getplayerxy VAR_0x8004, VAR_0x8005
	warpsilent MAP_ROUTE30, VAR_0x8004, VAR_0x8005
	waitstate
	releaseall
	end

BerryGarden_Movement_BramTwoWest:
	walk_left
	walk_left
	step_end

BerryGarden_Movement_BramThreeWest:
	walk_left
	walk_left
	walk_left
	step_end

@ ---------------------------------------------------------------------------
@ Morning letters (section 14.4 O), from Act 4 on: Monday, Wednesday, Friday
@ and Sunday instead of her line of the day. Letter = VAR_DAYS % 10; the ones
@ that need a later state (Sonia: Act 5; 8 and 9: state 15) fall back to her
@ line. Called by Route30_House_EventScript_WifeChat in the morning.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_LaurelMorning::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_FIRST_LEAF, BerryGarden_EventScript_LaurelMorningLine
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_MON, BerryGarden_EventScript_LaurelLetter
	goto_if_eq VAR_RESULT, WEEKDAY_WED, BerryGarden_EventScript_LaurelLetter
	goto_if_eq VAR_RESULT, WEEKDAY_FRI, BerryGarden_EventScript_LaurelLetter
	goto_if_eq VAR_RESULT, WEEKDAY_SUN, BerryGarden_EventScript_LaurelLetter
	goto BerryGarden_EventScript_LaurelMorningLine

BerryGarden_EventScript_LaurelLetter::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 0, BerryGarden_EventScript_Letter0
	case 1, BerryGarden_EventScript_Letter1
	case 2, BerryGarden_EventScript_Letter2
	case 3, BerryGarden_EventScript_LetterSonia
	case 4, BerryGarden_EventScript_Letter4
	case 5, BerryGarden_EventScript_Letter5
	case 6, BerryGarden_EventScript_Letter6
	case 7, BerryGarden_EventScript_Letter7
	case 8, BerryGarden_EventScript_Letter8
	case 9, BerryGarden_EventScript_LetterSonia
	goto BerryGarden_EventScript_LaurelMorningLine

@ Part 16: Sonia from Act 5 on (3 and 9), 8 and 9 after the story; reading 8
@ (Freezington's statue) unlocks Calyrex's line about it (bank N).
BerryGarden_EventScript_LetterSonia::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_KING_CAME, BerryGarden_EventScript_LaurelMorningLine
	goto_if_eq VAR_RESULT, 9, BerryGarden_EventScript_Letter9
	msgbox BerryGarden_Text_Letter3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter9::
	msgbox BerryGarden_Text_Letter9, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter7::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_LaurelMorningLine
	setvar VAR_0x8004, GARDEN_STORY_STATUE_LETTER
	special GardenStory_Mark
	msgbox BerryGarden_Text_Letter7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter8::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_LaurelMorningLine
	msgbox BerryGarden_Text_Letter8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter0::
	msgbox BerryGarden_Text_Letter0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter1::
	msgbox BerryGarden_Text_Letter1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter2::
	msgbox BerryGarden_Text_Letter2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter4::
	msgbox BerryGarden_Text_Letter4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter5::
	msgbox BerryGarden_Text_Letter5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_Letter6::
	msgbox BerryGarden_Text_Letter6, MSGBOX_DEFAULT
	return

@ ===========================================================================
@ Act 5 and 5b (plan part 13; REI_DA_COLHEITA.md 13.3 with 14.2 and 15.2).
@   8 -> 9   ripe Enigma + night: Calyrex speaks through Peony; the seeds
@   9 -> 10/11  a seed planted in Laurel's plot (the sign at (23,38))
@   10/11    the night after: the carrot (key item) from the plot
@ Peony and Peonia stay as guests from 9 to the epilogue (GardenCast_PlaceOf).
@
@ Act 5 plan (Route30, measured; y grows downward):
@   Peony (22,38) kneeling, facing east at the plot (23,38)
@   Calyrex (23,39), facing north at the plot
@   the player comes out of Bram's door at (26,40) and steps down to (26,41)
@   Laurel comes out of the door: (26,40) -> west x4 -> (22,40) -> north -> (22,39)
@   Peonia runs in from the south, off camera: (24,47) -> north x7 -> (24,40)
@     -> west -> (23,40), facing north
@ The scene only plays from Bram's door (Route30_OnFrame); talking to Peony or
@ Calyrex first moves the player there under a fade (a silent reload).
@ ===========================================================================
BerryGarden_EventScript_KingCameTalk::
	lockall
	fadescreen FADE_TO_BLACK
	warpsilent MAP_ROUTE30, 26, 40
	waitstate
	releaseall
	end

BerryGarden_EventScript_KingCameScene::
	applymovement OBJ_EVENT_ID_PLAYER, BerryGarden_Movement_StepDown
	waitmovement 0
	msgbox BerryGarden_Text_KingCame1, MSGBOX_DEFAULT
	closemessage
	call BerryGarden_EventScript_Flash
	applymovement LOCALID_ROUTE30_PEONY, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BerryGarden_Text_KingCame2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE30_CALYREX, BerryGarden_Movement_Eats
	waitmovement 0
	special GardenKingsPlot_Empty
	playmoncry SPECIES_CALYREX, CRY_MODE_NORMAL
	waitmoncry
	msgbox BerryGarden_Text_KingCame3, MSGBOX_DEFAULT
	closemessage
	call BerryGarden_EventScript_Flash
	setflag FLAG_TEMP_HIDE_CALYREX
	removeobject LOCALID_ROUTE30_CALYREX
	msgbox BerryGarden_Text_KingCame4, MSGBOX_DEFAULT
	closemessage
	setobjectxyperm LOCALID_ROUTE30_LAUREL, 26, 40
	setobjectmovementtype LOCALID_ROUTE30_LAUREL, MOVEMENT_TYPE_FACE_LEFT
	clearflag FLAG_TEMP_HIDE_LAUREL
	addobject LOCALID_ROUTE30_LAUREL
	playse SE_EXIT
	waitse
	applymovement LOCALID_ROUTE30_LAUREL, BerryGarden_Movement_LaurelToPeony
	waitmovement 0
	msgbox BerryGarden_Text_KingCame5, MSGBOX_DEFAULT
	closemessage
	setobjectxyperm LOCALID_ROUTE30_PEONIA, 24, 47
	setobjectmovementtype LOCALID_ROUTE30_PEONIA, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_TEMP_HIDE_PEONIA
	addobject LOCALID_ROUTE30_PEONIA
	applymovement LOCALID_ROUTE30_PEONIA, BerryGarden_Movement_PeoniaRunsIn
	waitmovement 0
	msgbox BerryGarden_Text_KingCame6, MSGBOX_DEFAULT
	msgbox BerryGarden_Text_KingCame7, MSGBOX_DEFAULT
	msgbox BerryGarden_Text_KingCame8, MSGBOX_DEFAULT
	closemessage
	setvar VAR_HARVEST_KING, HARVEST_KING_KING_CAME
	fadescreen FADE_TO_BLACK
	getplayerxy VAR_0x8004, VAR_0x8005
	warpsilent MAP_ROUTE30, VAR_0x8004, VAR_0x8005
	waitstate
	releaseall
	end

BerryGarden_Movement_StepDown:
	walk_down
	face_left
	step_end

BerryGarden_Movement_Eats:
	walk_in_place_up
	walk_in_place_up
	step_end

BerryGarden_Movement_LaurelToPeony:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end

BerryGarden_Movement_PeoniaRunsIn:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_up
	step_end

@ ---------------------------------------------------------------------------
@ Act 5b: Laurel's plot, the sign at (23,38) (its berry tree is hidden from
@ state 9: no seed goes in through the Berry menu). Called by
@ Route30_EventScript_ColdSoil; returns VAR_RESULT = TRUE when it answered.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_KingsPlot::
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_KING_CAME, BerryGarden_EventScript_ChooseSeed
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_ICEROOT, BerryGarden_EventScript_CarrotPlot
	goto_if_eq VAR_HARVEST_KING, HARVEST_KING_SHADEROOT, BerryGarden_EventScript_CarrotPlot
	goto BerryGarden_EventScript_NoReaction

BerryGarden_EventScript_ChooseSeed::
	message BerryGarden_Text_ChooseSeed
	waitmessage
	dynmultichoice 0, 0, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, BerryGarden_Text_SeedIceroot, BerryGarden_Text_SeedShaderoot, BerryGarden_Text_SeedNotYet
	goto_if_eq VAR_RESULT, 0, BerryGarden_EventScript_PlantIceroot
	goto_if_eq VAR_RESULT, 1, BerryGarden_EventScript_PlantShaderoot
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_PlantIceroot::
	bufferstring STR_VAR_1, BerryGarden_Text_IcerootSeed
	setvar VAR_HARVEST_KING, HARVEST_KING_ICEROOT
	goto BerryGarden_EventScript_Planted

BerryGarden_EventScript_PlantShaderoot::
	bufferstring STR_VAR_1, BerryGarden_Text_ShaderootSeed
	setvar VAR_HARVEST_KING, HARVEST_KING_SHADEROOT
BerryGarden_EventScript_Planted::
	setvar VAR_0x8004, GARDEN_STORY_CARROT_PLANTED
	special GardenStory_Mark
	msgbox BerryGarden_Text_SeedPlanted, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ The night after planting (GardenRollDay marks CARROT_READY): the carrot.
BerryGarden_EventScript_CarrotPlot::
	checkitem ITEM_ICEROOT_CARROT
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_CarrotResting
	checkitem ITEM_SHADEROOT_CARROT
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_CarrotResting
	setvar VAR_0x8004, GARDEN_STORY_CARROT_READY
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_CarrotNotYet
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_CarrotWaits
	msgbox BerryGarden_Text_CarrotUp, MSGBOX_DEFAULT
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_ICEROOT, BerryGarden_EventScript_GiveIceroot
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_SHADEROOT, BerryGarden_EventScript_GiveShaderoot
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_GiveIceroot::
	giveitem ITEM_ICEROOT_CARROT
	return

BerryGarden_EventScript_GiveShaderoot::
	giveitem ITEM_SHADEROOT_CARROT
	return

BerryGarden_EventScript_CarrotNotYet::
	msgbox BerryGarden_Text_CarrotNotYet, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_CarrotWaits::
	msgbox BerryGarden_Text_CarrotWaits, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

BerryGarden_EventScript_CarrotResting::
	msgbox BerryGarden_Text_CarrotResting, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ Laurel the morning after the seed (14.2), one time.
BerryGarden_EventScript_LaurelPickedCheck::
	goto_if_ne VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_MORNING, BerryGarden_EventScript_NoReaction
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_ICEROOT, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, GARDEN_STORY_CARROT_READY
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_ne VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	setvar VAR_0x8004, GARDEN_STORY_LAUREL_PICKED
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_NoReaction
	special GardenStory_Mark
	msgbox BerryGarden_Text_LaurelPicked, MSGBOX_DEFAULT
	goto BerryGarden_EventScript_Reacted

@ ---------------------------------------------------------------------------
@ The guests (14.2, 14.4 K, L, M).
@ ---------------------------------------------------------------------------
@ Peony, mornings in the garden: his first talk of the day is the watering
@ line, then his line of the day (bank K, hearts); then a battle, once a day
@ (14.5).
BerryGarden_EventScript_PeonyGarden::
	lock
	faceplayer
	dotimebasedevents
	special GardenRollDay
	setvar VAR_0x8004, GARDEN_HEARTS_PEONY
	specialvar VAR_0x800B, GardenHearts_Talk
	@ The watering line is the guest's (states 9..14); after the story, by
	@ the pond, his line of the day.
	call_if_ge VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_PeonyNotGuest
	call_if_eq VAR_0x800B, TRUE, BerryGarden_EventScript_PeonyWatering
	call_if_ne VAR_0x800B, TRUE, BerryGarden_EventScript_PeonyLine
	call BerryGarden_EventScript_PeonyBattle
	closemessage
	release
	end

BerryGarden_EventScript_PeonyWatering::
	msgbox BerryGarden_Text_PeonyWatering, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_PeonyNotGuest::
	setvar VAR_0x800B, FALSE
	return

BerryGarden_EventScript_PeonyBattle::
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_PEONY
	specialvar VAR_RESULT, GardenToday_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_PeonyTired
	msgbox BerryGarden_Text_PeonyIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BerryGarden_EventScript_StoryEnd
	setvar VAR_0x8004, GARDEN_TODAY_FOUGHT_PEONY
	special GardenToday_Set
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	goto_if_ge VAR_RESULT, 6, BerryGarden_EventScript_PeonyFight3
	goto_if_ge VAR_RESULT, 3, BerryGarden_EventScript_PeonyFight2
	garden_fight TRAINER_GARDEN_PEONY_1, BerryGarden_Text_PeonyDefeat
	goto BerryGarden_EventScript_PeonyAfterFight

BerryGarden_EventScript_PeonyFight2::
	garden_fight TRAINER_GARDEN_PEONY_2, BerryGarden_Text_PeonyDefeat
	goto BerryGarden_EventScript_PeonyAfterFight

BerryGarden_EventScript_PeonyFight3::
	garden_fight TRAINER_GARDEN_PEONY_3, BerryGarden_Text_PeonyDefeat
BerryGarden_EventScript_PeonyAfterFight::
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BerryGarden_EventScript_PeonyWon
	msgbox BerryGarden_Text_PeonyPrize, MSGBOX_DEFAULT
	giveitem ITEM_EXP_CANDY_M
	return

BerryGarden_EventScript_PeonyWon::
	special HealPlayerParty
	msgbox BerryGarden_Text_PeonyWon, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_PeonyTired::
	msgbox BerryGarden_Text_PeonyTired, MSGBOX_DEFAULT
	return

@ Peony in the house: asleep on the blue chair. By day he snores; at night
@ Calyrex speaks through him (bank M, name box Calyrex).
BerryGarden_EventScript_PeonyHouse::
	lock
	goto_if_eq VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_KingSpeaks
	msgbox BerryGarden_Text_PeonySnores, MSGBOX_DEFAULT
	closemessage
	release
	end

BerryGarden_EventScript_KingSpeaks::
	applymovement LOCALID_HOUSE_PEONY, Common_Movement_ExclamationMark
	waitmovement 0
	call BerryGarden_EventScript_KingNightLine
	closemessage
	release
	end

@ Peonia in the house (mornings at the table: bank L, the five lines that do
@ not need the story's end; nights: packing) and in the garden by day.
BerryGarden_EventScript_PeoniaHouse::
	lock
	faceplayer
	goto_if_eq VAR_TEMP_GARDEN_PERIOD, GARDEN_PERIOD_NIGHT, BerryGarden_EventScript_PeoniaPacking
	call BerryGarden_EventScript_PeoniaLine
	closemessage
	release
	end

BerryGarden_EventScript_PeoniaPacking::
	msgbox BerryGarden_Text_PeoniaPacking, MSGBOX_DEFAULT
	closemessage
	release
	end

BerryGarden_EventScript_PeoniaGarden::
	lock
	faceplayer
	dotimebasedevents
	special GardenRollDay
	goto_if_ge VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_PeoniaAfter
	msgbox BerryGarden_Text_PeoniaWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

@ ---------------------------------------------------------------------------
@ Pryce and Morty after their gyms (15.2): the carrot that fits them opens
@ their message; without it, a short hook while the search is on (states
@ 9..11). The dungeons themselves are parts 14 and 15.
@ ---------------------------------------------------------------------------
BerryGarden_EventScript_PryceHook::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_KING_CAME, BerryGarden_EventScript_StoryEnd
	setvar VAR_0x8004, GARDEN_STORY_WHITE_PATH
	specialvar VAR_RESULT, GardenStory_Check
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_PryceCoat
	goto_if_gt VAR_HARVEST_KING, HARVEST_KING_SHADEROOT, BerryGarden_EventScript_StoryEnd
	checkitem ITEM_ICEROOT_CARROT
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_PryceCarrot
	msgbox BerryGarden_Text_PryceHook, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_PryceCarrot::
	msgbox BerryGarden_Text_PryceCarrot1, MSGBOX_DEFAULT
	msgbox BerryGarden_Text_PryceCarrot2, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_MortyHook::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_KING_CAME, BerryGarden_EventScript_StoryEnd
	@ Part 15: the Spell Tag, if the scene in the Burned Tower was cut short.
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_SPECTRIER, BerryGarden_EventScript_MortyHookCarrot
	checkitem ITEM_SHADEROOT_CARROT
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_MortySpellTag
BerryGarden_EventScript_MortyHookCarrot::
	goto_if_gt VAR_HARVEST_KING, HARVEST_KING_SHADEROOT, BerryGarden_EventScript_StoryEnd
	checkitem ITEM_SHADEROOT_CARROT
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_MortyCarrot
	msgbox BerryGarden_Text_MortyHook, MSGBOX_DEFAULT
	return

BerryGarden_EventScript_MortyCarrot::
	msgbox BerryGarden_Text_MortyCarrot, MSGBOX_DEFAULT
	return

@ Bank K (Peony, hearts): line 7 is the epilogue's, so it falls back to line 1.
BerryGarden_EventScript_PeonyLine::
	setvar VAR_0x8004, GARDEN_HEARTS_PEONY
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_PeonyK1
	case 2, BerryGarden_EventScript_PeonyK2
	case 3, BerryGarden_EventScript_PeonyK3
	case 4, BerryGarden_EventScript_PeonyK4
	case 5, BerryGarden_EventScript_PeonyK5
	case 6, BerryGarden_EventScript_PeonyK6Check
	case 7, BerryGarden_EventScript_PeonyK7
	case 8, BerryGarden_EventScript_PeonyK8
	case 9, BerryGarden_EventScript_PeonyK9
	msgbox BerryGarden_Text_PeonyK0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK1::
	msgbox BerryGarden_Text_PeonyK1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK2::
	msgbox BerryGarden_Text_PeonyK2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK3::
	msgbox BerryGarden_Text_PeonyK3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK4::
	msgbox BerryGarden_Text_PeonyK4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK5::
	msgbox BerryGarden_Text_PeonyK5, MSGBOX_DEFAULT
	return
@ Line 7 only after the story (14.4 K).
BerryGarden_EventScript_PeonyK6Check::
	goto_if_lt VAR_HARVEST_KING, HARVEST_KING_GUESTS_LEAVE, BerryGarden_EventScript_PeonyK1
	msgbox BerryGarden_Text_PeonyK6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK7::
	msgbox BerryGarden_Text_PeonyK7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK8::
	msgbox BerryGarden_Text_PeonyK8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeonyK9::
	msgbox BerryGarden_Text_PeonyK9, MSGBOX_DEFAULT
	return

@ Bank L (Peonia): in states 9-14 only lines 1, 2, 4, 5 and 7 (section 14.4 L),
@ the line of the day mod 5.
BerryGarden_EventScript_PeoniaLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_PeoniaL1
	case 2, BerryGarden_EventScript_PeoniaL2
	case 3, BerryGarden_EventScript_PeoniaL3
	case 4, BerryGarden_EventScript_PeoniaL4
	case 6, BerryGarden_EventScript_PeoniaL1
	case 7, BerryGarden_EventScript_PeoniaL2
	case 8, BerryGarden_EventScript_PeoniaL3
	case 9, BerryGarden_EventScript_PeoniaL4
	msgbox BerryGarden_Text_PeoniaL0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL1::
	msgbox BerryGarden_Text_PeoniaL1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL2::
	msgbox BerryGarden_Text_PeoniaL2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL3::
	msgbox BerryGarden_Text_PeoniaL3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_PeoniaL4::
	msgbox BerryGarden_Text_PeoniaL4, MSGBOX_DEFAULT
	return

@ Bank M (Calyrex through the sleeping Peony): the line of the day, no hearts.
BerryGarden_EventScript_KingNightLine::
	setvar VAR_0x8004, GARDEN_HEARTS_NONE
	specialvar VAR_RESULT, GardenLine_Pick
	switch VAR_RESULT
	case 1, BerryGarden_EventScript_KingM1
	case 2, BerryGarden_EventScript_KingM2
	case 3, BerryGarden_EventScript_KingM3
	case 4, BerryGarden_EventScript_KingM4
	case 5, BerryGarden_EventScript_KingM5
	case 6, BerryGarden_EventScript_KingM6
	case 7, BerryGarden_EventScript_KingM7
	case 8, BerryGarden_EventScript_KingM8
	case 9, BerryGarden_EventScript_KingM9
	msgbox BerryGarden_Text_KingM0, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM1::
	msgbox BerryGarden_Text_KingM1, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM2::
	msgbox BerryGarden_Text_KingM2, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM3::
	msgbox BerryGarden_Text_KingM3, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM4::
	msgbox BerryGarden_Text_KingM4, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM5::
	msgbox BerryGarden_Text_KingM5, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM6::
	msgbox BerryGarden_Text_KingM6, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM7::
	msgbox BerryGarden_Text_KingM7, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM8::
	msgbox BerryGarden_Text_KingM8, MSGBOX_DEFAULT
	return
BerryGarden_EventScript_KingM9::
	msgbox BerryGarden_Text_KingM9, MSGBOX_DEFAULT
	return

@ ---------------------------------------------------------------------------
@ Texts. Several speakers: name box on each (SPEAKER); one person: none.
@ ---------------------------------------------------------------------------

BerryGarden_Text_PrologueWithLaurel:
	.string "{SPEAKER NAME_BERRY_MASTER}Now that's the talk. Here's the part\n"
	.string "the talk leaves out.\p"
	.string "Out the door, to the right. Six beds.\n"
	.string "They're yours.\p"
	.string "Plant what you like. Water it, pull the\n"
	.string "weeds, chase off whatever comes to eat\l"
	.string "it.\p"
	.string "Come by in the mornings. I'll have\n"
	.string "something for you.\p"
	.string "{SPEAKER NAME_LAUREL}Not the patch by the door.\p"
	.string "{SPEAKER NAME_BERRY_MASTER}...Not the patch by the door.\p"
	.string "{SPEAKER NAME_LAUREL}That one's mine.$"

BerryGarden_Text_PrologueAlone:
	.string "Now that's the talk. Here's the part\n"
	.string "the talk leaves out.\p"
	.string "Out the door, to the right. Six beds.\n"
	.string "They're yours.\p"
	.string "Plant what you like. Water it, pull the\n"
	.string "weeds, chase off whatever comes to eat\l"
	.string "it.\p"
	.string "Come by in the mornings. I'll have\n"
	.string "something for you.\p"
	.string "And not the patch by the door. That\n"
	.string "one's Laurel's.\p"
	.string "Don't ask me why. I asked once.$"

BerryGarden_Text_LaurelFirstPest:
	.string "A {STR_VAR_1}. In the beds.\p"
	.string "Fifty years he's kept this garden.\n"
	.string "Fifty years and not one bug.\p"
	.string "Now you come along, and they come\n"
	.string "along.\p"
	.string "...It isn't a complaint. Go and tell him.\n"
	.string "He'll want to shout.$"

BerryGarden_Text_BramBugs:
	.string "BUGS? In MY beds?\p"
	.string "...What kind? Ooh. I've never even seen\n"
	.string "one of those.\p"
	.string "Laurel says write to the boy in Azalea.\n"
	.string "The Gym Leader. Knows every bug from\l"
	.string "here to Kanto.\p"
	.string "I'll post the letter. You go get\n"
	.string "yourself a badge from him, so he knows\l"
	.string "you're serious.$"

BerryGarden_Text_BugsyArrives:
	.string "Shh! Don't move. There's a Blipbug on\n"
	.string "the third bed.\p"
	.string "...It's gone. Hello! You must be {PLAYER}.\n"
	.string "I got a letter. Well, the letter was\l"
	.string "mostly about how big the Berries were.\p"
	.string "But this garden is remarkable. I've\n"
	.string "catalogued every bug in Johto, and some\l"
	.string "of the ones coming here don't live\l"
	.string "ANYWHERE in Johto.\p"
	.string "Wurmple. Combee. Fireflies at night. A\n"
	.string "Dwebble living in a pebble!\p"
	.string "They aren't lost. They came for the\n"
	.string "Berries. Different Berries, different\l"
	.string "bugs.\p"
	.string "Will you help me? Catch three of the\n"
	.string "ones that only come here, and bring me\l"
	.string "the data.\p"
	.string "I'll be in Azalea. And here, now and\n"
	.string "then. I can't stay away from a place\l"
	.string "like this.$"

BerryGarden_Text_BugsyCensusSoFar:
	.string "Any luck? You've caught {STR_VAR_1}\n"
	.string "of them so far.\p"
	.string "I need three. Only the ones that come\n"
	.string "to this garden -- the Berries decide\l"
	.string "which.$"

BerryGarden_Text_BugsyCensus:
	.string "Three of them! Let me see...\p"
	.string "It's the colors. Red Berries, red bugs.\n"
	.string "Blue Berries bring Blipbug in the day\l"
	.string "and Volbeat after dark.\p"
	.string "And whatever you put in the soil\n"
	.string "matters too. Compost brings Rellor.\l"
	.string "Gravel brings Dwebble. It's a whole\l"
	.string "little world out there!\p"
	.string "I'm going to build something for them. A\n"
	.string "Bug Hotel. When your garden's ready for\l"
	.string "it, tell Bram to call me.\p"
	.string "Oh, and take this. For the bugs you'll\n"
	.string "raise.$"

BerryGarden_Text_BugsyBagFull:
	.string "Your Bag's full! Make some room, and\n"
	.string "I'll have something for you.$"

BerryGarden_Text_NightVisitor:
	.string "Something dark and tall was eating from\n"
	.string "the beds.\p"
	.string "It looked at you for a long moment. Then\n"
	.string "it was gone, and it made no sound at all.$"

BerryGarden_Text_Hoofprints:
	.string "Hoofprints, pressed deep into the soil.\p"
	.string "They stop at the edge of the pond.$"

BerryGarden_Text_LaurelHeardIt:
	.string "You were out late.\p"
	.string "...Don't tell me. I heard it. I've heard\n"
	.string "it before.\p"
	.string "Eat your breakfast. It isn't here for\n"
	.string "you.$"

BerryGarden_Text_BramWakes:
	.string "Hm? Oh. It's you. Keep it down. She's\n"
	.string "reading.\p"
	.string "...She told you it isn't here for you.\n"
	.string "She's right. It's here for her. Or for\l"
	.string "what she brought.\p"
	.string "Laurel isn't from Johto, sprout. She's\n"
	.string "from Freezington. Up past the snow, in\l"
	.string "Galar.\p"
	.string "Her grandmother kept a field there. An\n"
	.string "old field. For someone important.\p"
	.string "When Laurel came here she brought one\n"
	.string "seed from it. She's planted it in that\l"
	.string "patch by the door every spring for\l"
	.string "forty years.\p"
	.string "It has never, once, come up.\p"
	.string "Don't ask her about it. She'll tell you\n"
	.string "when the Book's big enough. That's\l"
	.string "what she said to me, anyway. I've been\l"
	.string "waiting forty years.$"

BerryGarden_Text_LaurelNotebook1:
	.string "Forty. Forty Berries, and you grew every\n"
	.string "one of them.\p"
	.string "Sit. No, sit.\p"
	.string "Where I come from there's a story.\n"
	.string "There was a king who made the fields\l"
	.string "grow. Whatever he walked past, it\l"
	.string "fruited.\p"
	.string "He rode two horses. A white one that\n"
	.string "walked through the snow, and a black\l"
	.string "one that walked through the dark.\p"
	.string "People forgot him. When people forget, a\n"
	.string "king like that gets small. He loses his\l"
	.string "horses. He loses the harvest.$"

BerryGarden_Text_LaurelNotebook2:
	.string "My grandmother didn't forget. She kept\n"
	.string "his field.\p"
	.string "When I left, she gave me this. She said:\n"
	.string "plant it where the land remembers.\p"
	.string "Johto never remembered. Not for forty\n"
	.string "years.\p"
	.string "Then you came, and the bugs came. And\n"
	.string "one night, the black horse came.\p"
	.string "The land remembers something now. I\n"
	.string "think it's you.\p"
	.string "Take it. Plant it in my patch. Not yours.\n"
	.string "Mine.$"

BerryGarden_Text_LaurelNotebookBagFull:
	.string "Come back when you have room.\p"
	.string "It's waited forty years.$"

BerryGarden_Text_LaurelThatsABed:
	.string "That's a bed. I said my patch. It isn't\n"
	.string "the same soil. Trust me.\p"
	.string "Here. Another one. My patch, by the\n"
	.string "door.$"

BerryGarden_Text_LaurelLostIt:
	.string "You lost it? ...Here. Another one.\p"
	.string "My patch, by the door. Don't make me\n"
	.string "say it a third time.$"

BerryGarden_Text_FirstLeaf1:
	.string "{SPEAKER NAME_LAUREL}...\p"
	.string "It came up.$"

BerryGarden_Text_FirstLeaf2:
	.string "{SPEAKER NAME_BERRY_MASTER}Laurel? Laurel, what's the--\p"
	.string "...Oh.\p"
	.string "Oh, would you look at that.\p"
	.string "{SPEAKER NAME_LAUREL}Don't. Don't say anything.\p"
	.string "{SPEAKER NAME_BERRY_MASTER}I wasn't going to say anything.\p"
	.string "{SPEAKER NAME_LAUREL}You were going to cry.\p"
	.string "{SPEAKER NAME_BERRY_MASTER}I was not.$"

BerryGarden_Text_FirstLeaf3:
	.string "Go on, sprout. Give us a minute.$"

BerryGarden_Text_LaurelWroteHome:
	.string "I wrote to Freezington. First letter in\n"
	.string "forty years.\p"
	.string "Someone there used to follow me around\n"
	.string "like a Yamper. He'll come. He never could\l"
	.string "leave a thing alone.$"

BerryGarden_Text_Letter0:
	.string "From Honey.\p"
	.string "“The students ate every Berry you sent\n"
	.string "in one sitting. Mustard says his knees\l"
	.string "are fine. They are not.”$"

BerryGarden_Text_Letter1:
	.string "From Freezington.\p"
	.string "“The whole village read your letter. The\n"
	.string "Mayor wants to know if Johto sells\l"
	.string "carrots.”$"

BerryGarden_Text_Letter2:
	.string "From Honey.\p"
	.string "“Mustard asks if your husband can arm\n"
	.string "wrestle. Please say no. He will fly over.”\p"
	.string "P.S., in different handwriting: “I would\n"
	.string "win.”$"

BerryGarden_Text_Letter4:
	.string "From Honey.\p"
	.string "“I tried your Pecha jam. It exploded.\n"
	.string "Mustard ate it off the ceiling.”$"

BerryGarden_Text_Letter5:
	.string "From Freezington.\p"
	.string "“Snow's up to the windows. The children\n"
	.string "built a snow Laurel. It's frowning. It's\l"
	.string "very accurate.”$"

BerryGarden_Text_Letter6:
	.string "From Kurt.\p"
	.string "“Berries arrived. Some bruised. Send\n"
	.string "more. -- K.”\p"
	.string "From Kurt, that's a love letter.$"

BerryGarden_Text_KingCame1:
	.string "{SPEAKER NAME_PEONY}Auntie Laurel! Peony here! Got your\n"
	.string "letter, came on the first boat, and--\p"
	.string "...hold on. Something's... tickling the\n"
	.string "back of me head...$"

BerryGarden_Text_KingCame2:
	.string "{SPEAKER NAME_UNKNOWN}...You can hear me. Good. Forgive me for\n"
	.string "borrowing this one. He is loud, but his\l"
	.string "heart is open, and I have not the\l"
	.string "strength to speak on my own.\p"
	.string "This Berry... it was grown with care. By\n"
	.string "someone who remembered.$"

BerryGarden_Text_KingCame3:
	.string "{SPEAKER NAME_CALYREX}I am Calyrex. Once, they called me the\n"
	.string "King of Bountiful Harvest.\p"
	.string "I was a king with no field, and no one to\n"
	.string "carry me. My steeds left when the\l"
	.string "people forgot.\p"
	.string "One still wanders this land at night,\n"
	.string "looking for food. You have met him, I\l"
	.string "think.\p"
	.string "The other sleeps under ice that never\n"
	.string "melts.\p"
	.string "Bring one of them home to me, and I will\n"
	.string "show you what this garden can become.$"

BerryGarden_Text_KingCame4:
	.string "{SPEAKER NAME_PEONY}...Wh-- what was I on about? Why am I\n"
	.string "kneeling?\p"
	.string "Why was a turnip looking at me?$"

BerryGarden_Text_KingCame5:
	.string "{SPEAKER NAME_LAUREL}Hello, Peony. You got tall.\p"
	.string "{SPEAKER NAME_PEONY}AUNTIE! Ha! You haven't changed one\n"
	.string "bit!\p"
	.string "...Did I just say something daft?\p"
	.string "{SPEAKER NAME_LAUREL}You said something true. For once.$"

BerryGarden_Text_KingCame6:
	.string "{SPEAKER NAME_PEONIA}DAD! You can't just jump off a ship\n"
	.string "before it docks!\p"
	.string "...Is that soil glowing? Is that --\n"
	.string "Auntie's story? The king?\p"
	.string "{SPEAKER NAME_LAUREL}The white one sleeps where the ice\n"
	.string "never thaws. The black one walks where\l"
	.string "the fire took the bells.$"

BerryGarden_Text_KingCame7:
	.string "{SPEAKER NAME_LAUREL}Ice that never thaws. I always took\n"
	.string "that for the Ice Path. Ask the old man\l"
	.string "in Mahogany. He knows ice better than I\l"
	.string "know Berries.\p"
	.string "Where the fire took the bells. The tower\n"
	.string "in Ecruteak. Ask the boy who sees\l"
	.string "things.\p"
	.string "One horse. Choose.\p"
	.string "{SPEAKER NAME_PEONIA}I'm going with {PLAYER}. Someone in this\n"
	.string "family has to be sensible.$"

BerryGarden_Text_KingCame8:
	.string "{SPEAKER NAME_PEONY}Oi -- why've I got seeds in me pocket?\n"
	.string "I haven't got pockets in this coat. I\l"
	.string "checked. Twice.\p"
	.string "{SPEAKER NAME_LAUREL}...Iceroot. And Shaderoot. My\n"
	.string "grandmother grew both. Never at once.\p"
	.string "The white one won't go near the dark\n"
	.string "one's food. The dark one won't touch\l"
	.string "the white one's.\p"
	.string "One seed, in my patch. The horse comes\n"
	.string "for the carrot. Not for you. Remember\l"
	.string "that.\p"
	.string "{SPEAKER NAME_PEONIA}Carrots. A legendary horse. For\n"
	.string "CARROTS.\p"
	.string "{SPEAKER NAME_PEONY}Everyone likes a carrot, love.$"

BerryGarden_Text_ChooseSeed:
	.string "The soil where the Enigma grew is still\n"
	.string "warm. Plant one of the seeds?$"

BerryGarden_Text_SeedIceroot:
	.string "Iceroot$"

BerryGarden_Text_SeedShaderoot:
	.string "Shaderoot$"

BerryGarden_Text_SeedNotYet:
	.string "Not yet$"

BerryGarden_Text_IcerootSeed:
	.string "Iceroot seed$"

BerryGarden_Text_ShaderootSeed:
	.string "Shaderoot seed$"

BerryGarden_Text_SeedPlanted:
	.string "You planted the {STR_VAR_1}.\p"
	.string "The cold soil seems to hold its breath.$"

BerryGarden_Text_CarrotNotYet:
	.string "Nothing yet. The soil is keeping its\n"
	.string "secret.$"

BerryGarden_Text_CarrotWaits:
	.string "Feathery leaves have come up.\p"
	.string "They seem to be waiting for the dark.$"

BerryGarden_Text_CarrotUp:
	.string "Feathery leaves, cold to the touch...\p"
	.string "You pull, and something long comes up\n"
	.string "out of the soil!$"

BerryGarden_Text_CarrotResting:
	.string "The soil is resting. Whatever grew here\n"
	.string "is in your Bag.$"

BerryGarden_Text_LaurelPicked:
	.string "You picked. Good. Don't tell me which.\p"
	.string "I'll know when I see the leaves.$"

BerryGarden_Text_PeonyWatering:
	.string "Peony here! Bram's put me on watering\n"
	.string "duty.\p"
	.string "I've watered the path, the fence, and\n"
	.string "Bram. The Berries are next!$"

BerryGarden_Text_PeonyIntro:
	.string "Peony here! Fancy a scrap, chum?\p"
	.string "Me and Copperajah haven't had a proper\n"
	.string "one since Galar!$"

BerryGarden_Text_PeonyDefeat:
	.string "Ha! GRAND! Knocked me flat and I loved\n"
	.string "every second!$"

BerryGarden_Text_PeonyPrize:
	.string "Here, chum -- a little something from\n"
	.string "Galar.\p"
	.string "Don't tell Peonia, she thinks I spend\n"
	.string "too much.$"

BerryGarden_Text_PeonyWon:
	.string "Ha! Copperajah wins! Don't feel bad,\n"
	.string "chum.\p"
	.string "He's bigger than a house.$"

BerryGarden_Text_PeonyTired:
	.string "Once a day, chum. Me back's not what it\n"
	.string "was.\p"
	.string "Me front neither.$"

BerryGarden_Text_PeonySnores:
	.string "Zzz... Galar time... zzz...\p"
	.string "He's fast asleep. It's the middle of\n"
	.string "the night where he comes from.$"

BerryGarden_Text_PeoniaPacking:
	.string "Rope. Torch. Snacks. More snacks.\p"
	.string "...Dad packed a kettle. Why is there a\n"
	.string "kettle.$"

BerryGarden_Text_PeoniaWaiting:
	.string "Peonia here! Auntie says the carrot\n"
	.string "comes when it comes.\p"
	.string "I hate waiting. Dad loves waiting. Dad's\n"
	.string "asleep.$"

BerryGarden_Text_PryceHook:
	.string "You smell of an old woman's garden.\p"
	.string "Riddles about ice come to me sooner or\n"
	.string "later. Bring me whatever she gave you.$"

BerryGarden_Text_PryceCarrot1:
	.string "...Iceroot. My mother fed it to the\n"
	.string "Mamoswine in the worst winters.\p"
	.string "The Ice Path? Child, the Ice Path thaws\n"
	.string "every spring. I've watched it for fifty\l"
	.string "years.\p"
	.string "Ice that never thaws isn't ice. There's\n"
	.string "a town west of the Ruins of Alph.\l"
	.string "Greenfield. The Unown covered it in\l"
	.string "crystal, once, when I was younger.$"

BerryGarden_Text_PryceCarrot2:
	.string "It went away. Last winter, it came back.\p"
	.string "I went there, the first time. A little\n"
	.string "girl asked me to stay for dinner. I\l"
	.string "didn't.\p"
	.string "I have regretted few things in my life.\n"
	.string "That is one of them.\p"
	.string "Go. And if she's still there, tell her the\n"
	.string "old man from Mahogany says good\l"
	.string "evening.$"

BerryGarden_Text_MortyHook:
	.string "The spirits are restless lately. They\n"
	.string "say a horse is looking for something to\l"
	.string "eat.\p"
	.string "I don't know what that means. Yet.$"

BerryGarden_Text_MortyCarrot:
	.string "Shaderoot. The spirits in my tower like\n"
	.string "the smell. So does he.\p"
	.string "You won't find him in the ruin. He\n"
	.string "doesn't walk in what the tower is. He\l"
	.string "walks in what it was, on the night it\l"
	.string "burned.\p"
	.string "There's only one way into a memory that\n"
	.string "old. The Kimono Girls dance it every\l"
	.string "year, on the anniversary.\p"
	.string "Come to the Dance Theater after dark.\n"
	.string "Bring your carrot. Bring your courage.$"

BerryGarden_Text_PeonyK0:
	.string "Peony here! Johto's grand, chum. The\n"
	.string "stars are the same as back home, just a\l"
	.string "bit to the left.$"

BerryGarden_Text_PeonyK1:
	.string "Did I ever tell you about the time I fell\n"
	.string "in a frozen lake looking for the white\l"
	.string "horse? Came out a Peony-sicle! Worth\l"
	.string "it!$"

BerryGarden_Text_PeonyK2:
	.string "Me Copperajah's asleep by the pond.\n"
	.string "Snores like a steam train. Tilly thinks\l"
	.string "it's a monster. It IS a monster! A\l"
	.string "lovely one!$"

BerryGarden_Text_PeonyK3:
	.string "You know what they call me in\n"
	.string "Freezington? “That loud one.” Ha! Fair!$"

BerryGarden_Text_PeonyK4:
	.string "My big brother Rose tried to buy\n"
	.string "Freezington once. The whole village. The\l"
	.string "Mayor sold him a hat and sent him home.$"

BerryGarden_Text_PeonyK5:
	.string "I was a Gym Leader once, y'know! Steel\n"
	.string "types! ...Then I quit. Rose was ever so\l"
	.string "cross. Best day of me life.$"

BerryGarden_Text_PeonyK7:
	.string "Auntie Laurel pulled me out of a tree\n"
	.string "once. I was eight. Up there three hours.\l"
	.string "She never asked why. Brought me a\l"
	.string "sandwich.$"

BerryGarden_Text_PeonyK8:
	.string "When I was a lad, Auntie told us the king\n"
	.string "would come back if someone grew a\l"
	.string "garden for him. We thought it was a\l"
	.string "bedtime story. Shows what we knew!$"

BerryGarden_Text_PeonyK9:
	.string "Chum... thanks. For Auntie. She hasn't\n"
	.string "smiled this much since... well. Since\l"
	.string "ever, honestly. Ha!$"

BerryGarden_Text_PeoniaL0:
	.string "Peonia here! ...Why is everyone in Johto\n"
	.string "so calm? It's suspicious.$"

BerryGarden_Text_PeoniaL1:
	.string "Dad got lost going to the Pokémon\n"
	.string "Center. It's down the road. He went\l"
	.string "the long way. Through the pond.$"

BerryGarden_Text_PeoniaL2:
	.string "Back home I do Dynamax Adventures.\n"
	.string "Here I carry mulch. Honestly? Mulch is\l"
	.string "harder.$"

BerryGarden_Text_PeoniaL3:
	.string "Don't tell Dad, but I think Johto's\n"
	.string "prettier than Galar. Don't tell Galar\l"
	.string "either.$"

BerryGarden_Text_PeoniaL4:
	.string "Dad cries at everything. He cried at a\n"
	.string "sunset on the boat. It was a normal\l"
	.string "sunset.$"

BerryGarden_Text_KingM0:
	.string "{SPEAKER NAME_CALYREX}...Peony is sleeping. I am not. Do not be\n"
	.string "alarmed. I will return him by morning.$"

BerryGarden_Text_KingM1:
	.string "{SPEAKER NAME_CALYREX}The Berry your Laurel grew... I can still\n"
	.string "taste it. Forty years of patience, in\l"
	.string "one fruit.$"

BerryGarden_Text_KingM2:
	.string "{SPEAKER NAME_CALYREX}The white one was proud. The black one\n"
	.string "was lonely. Either will do. Neither will\l"
	.string "come easily.$"

BerryGarden_Text_KingM3:
	.string "{SPEAKER NAME_CALYREX}In the old days, whole villages brought\n"
	.string "me their harvest. Now one old woman, one\l"
	.string "old man, and you. It is enough. It is\l"
	.string "more than enough.$"

BerryGarden_Text_KingM4:
	.string "{SPEAKER NAME_CALYREX}This one's dreams are very loud. He is\n"
	.string "dreaming of a sandwich. It is an\l"
	.string "enormous sandwich.$"

BerryGarden_Text_KingM5:
	.string "{SPEAKER NAME_CALYREX}The land here is young. It remembers\n"
	.string "little. But it remembers you -- every\l"
	.string "morning you came, every seed. That is\l"
	.string "how a field learns.$"

BerryGarden_Text_KingM6:
	.string "{SPEAKER NAME_CALYREX}Laurel sings in her sleep. She does not\n"
	.string "know. I will not tell her. Neither will\l"
	.string "you.$"

BerryGarden_Text_KingM7:
	.string "{SPEAKER NAME_CALYREX}When I was strong, I did not need to\n"
	.string "borrow. Now I borrow. Thank this one for\l"
	.string "me. He will not remember.$"

BerryGarden_Text_KingM8:
	.string "{SPEAKER NAME_CALYREX}A king is only what his people remember.\n"
	.string "Your Book... it is a kind of remembering.$"

BerryGarden_Text_KingM9:
	.string "{SPEAKER NAME_CALYREX}Go and sleep. Farmers wake early. Even\n"
	.string "kings know that.$"
