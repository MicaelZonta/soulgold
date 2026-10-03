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
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_BRAM_TOLD, BerryGarden_EventScript_LaurelNotebookCheck
	goto_if_eq VAR_RESULT, TRUE, BerryGarden_EventScript_StoryEnd
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_NOTEBOOK, BerryGarden_EventScript_LaurelEnigmaAgain
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
	case 4, BerryGarden_EventScript_Letter4
	case 5, BerryGarden_EventScript_Letter5
	case 6, BerryGarden_EventScript_Letter6
	goto BerryGarden_EventScript_LaurelMorningLine
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
	.string "Fifty years we've had this garden.\n"
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
	.string "three nights ago, the black horse came.\p"
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
