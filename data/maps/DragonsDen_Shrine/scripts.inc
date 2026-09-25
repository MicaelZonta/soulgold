@ map.json has no local_id fields: these ids are the object's position in the
@ object_events array. Lillie and Ninetales are appended AFTER Clair so that
@ Clair keeps id 4. Never insert objects before them.
.set LOCALID_DRAGONSDEN3_CLAIR, 4
.set LOCALID_DRAGONSDEN3_ELDER, 1
.set LOCALID_DRAGONSDEN3_LILLIE, 5
.set LOCALID_DRAGONSDEN3_NINETALES, 6

DragonsDen_Shrine_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Shrine_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, DragonsDen_Shrine_OnTransition
	.byte 0

DragonsDen_Shrine_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_Trigger_ElderQuizTop
	.2byte 0

DragonsDen_Shrine_EventScript_Elder::
	lock
	faceplayer
	goto_if_ge VAR_BLACKTHORN_CITY_STATE, 4, DragonsDen_Shrine_EventScript_ElderChooseDratini
	msgbox DragonsDen_Shrine_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Trigger_ElderQuizLeft::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderLeft
	applymovement OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_MonWalkToElderLeft
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizTop::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	applymovement OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_PlayerWalkToElderTop
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz

DragonsDen_Shrine_Trigger_ElderQuizRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Shrine_Movement_PlayerWalkToElderRight
	applymovement OBJ_EVENT_ID_FOLLOWER, DragonsDen_Shrine_Movement_MonWalkToElderRight
	waitmovement OBJ_EVENT_ID_FOLLOWER
	waitmovement OBJ_EVENT_ID_PLAYER
	delay 10
	lockall
	goto DragonsDen_Shrine_EventScript_ElderOfferQuiz


DragonsDen_Shrine_Movement_PlayerWalkToElderLeft:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_MonWalkToElderLeft:
	walk_left
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderTop:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Shrine_Movement_PlayerWalkToElderRight:
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end
DragonsDen_Shrine_Movement_MonWalkToElderRight:
	walk_right
	walk_up
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

@ ---------------------------------------------------------------------------
@ Lillie and Ninetales in the Elder's test (see docs/IMPLEMENTACAO_LILLIE_PRE_V13.md)
@
@   tile plan (measured from map.bin; walkable area x 3-9, y 8-16):
@     Elder (6,9)   Lillie (7,9)   Ninetales (8,9)
@     player stops at (6,10), follower at ~(6,11)
@     Clair enters (5,16) -> (5,10); Elder walks (6,9) -> (3,9) and back
@   Lillie and Ninetales stand in the corridor (7,9)/(8,9), which no vanilla
@   movement touches. They leave down column 7 BEFORE Clair enters.
@
@   Vanilla first: every accepted answer still shows Text_RightAnswer and
@   every rejected one still runs ElderWrong (VAR_DRAGONS_DEN_QUIZ + 1) and
@   re-asks. Lillie only speaks after that and never touches the counter.
@
@ Per-visit state (reset in DragonsDen_Shrine_OnTransition; VAR_TEMP_* and
@ FLAG_TEMP_* are also wiped by the engine on every warp):
@   FLAG_TEMP_1    - hide flag of Lillie and Ninetales; set unless state == 2
@   FLAG_TEMP_2..7 - rejected-answer reaction already shown this visit:
@                    2 Q1 Underling, 3 Q2 Cheating, 4 Q3 Weak person,
@                    5 Q4 Violence, 6 Q5 Tough, 7 Q5 Weak
@   VAR_TEMP_3     - battle outcome, copied right after GetBattleOutcome
@   VAR_TEMP_5     - previous state of B_FLAG_NO_WHITEOUT
@ ---------------------------------------------------------------------------

DragonsDen_Shrine_OnTransition::
	setvar VAR_TEMP_2, 0
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_5, 0
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_4
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_6
	clearflag FLAG_TEMP_7
	call_if_eq VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_EventScript_ShowLillie
	call_if_ne VAR_BLACKTHORN_CITY_STATE, 2, DragonsDen_Shrine_EventScript_HideLillie
	end

DragonsDen_Shrine_EventScript_ShowLillie::
	clearflag FLAG_TEMP_1
	return

DragonsDen_Shrine_EventScript_HideLillie::
	setflag FLAG_TEMP_1
	return

DragonsDen_Shrine_EventScript_ElderOfferQuiz::
	@ --- Lillie was already here when the player arrived ---
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_SOUTH
	msgbox DragonsDen_Shrine_Text_LillieArrival, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_WEST
	msgbox DragonsDen_Shrine_Text_ElderLillieObserves, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_SOUTH
	msgbox DragonsDen_Shrine_Text_LillieNotSoSure, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_WEST

	msgbox DragonsDen_Shrine_Text_ElderGreeting, MSGBOX_DEFAULT
	setvar VAR_DRAGONS_DEN_QUIZ, 0
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

@ --- Q1: Pal (0) / Underling (1) / Friend (2) ---
DragonsDen_Shrine_EventScript_ElderQuiz1::
	message DragonsDen_Shrine_Text_Question1
	multichoice 20, 6, MULTI_ELDERQUIIZ1, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_Quiz1_Pal
	case 1, DragonsDen_Shrine_EventScript_Quiz1_Underling
	case 2, DragonsDen_Shrine_EventScript_Quiz1_Friend
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz1
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

DragonsDen_Shrine_EventScript_Quiz1_Pal::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q1_Pal, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_EAST
	turnobject LOCALID_DRAGONSDEN3_NINETALES, DIR_WEST
	delay 30
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_WEST
	turnobject LOCALID_DRAGONSDEN3_NINETALES, DIR_SOUTH
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_Quiz1_Friend::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q1_Friend, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_Quiz1_Underling::
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto_if_set FLAG_TEMP_2, DragonsDen_Shrine_EventScript_ElderQuiz1
	setflag FLAG_TEMP_2
	msgbox DragonsDen_Shrine_Text_Lillie_Q1_Underling, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz1

@ --- Q2: Strategy (0) / Training (1) / Cheating (2) ---
DragonsDen_Shrine_EventScript_ElderQuiz2::
	message DragonsDen_Shrine_Text_Question2
	multichoice 20, 6, MULTI_ELDERQUIIZ2, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_Quiz2_Strategy
	case 1, DragonsDen_Shrine_EventScript_Quiz2_Training
	case 2, DragonsDen_Shrine_EventScript_Quiz2_Cheating
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz2
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

DragonsDen_Shrine_EventScript_Quiz2_Strategy::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q2_Strategy, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_Quiz2_Training::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q2_Training, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_Quiz2_Cheating::
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto_if_set FLAG_TEMP_3, DragonsDen_Shrine_EventScript_ElderQuiz2
	setflag FLAG_TEMP_3
	msgbox DragonsDen_Shrine_Text_Lillie_Q2_Cheating, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz2

@ --- Q3: Weak person (0) / Tough person (1) / Anybody (2) ---
DragonsDen_Shrine_EventScript_ElderQuiz3::
	message DragonsDen_Shrine_Text_Question3
	multichoice 20, 6, MULTI_ELDERQUIIZ3, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_Quiz3_WeakPerson
	case 1, DragonsDen_Shrine_EventScript_Quiz3_Tough
	case 2, DragonsDen_Shrine_EventScript_Quiz3_Anybody
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz3
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

DragonsDen_Shrine_EventScript_Quiz3_Tough::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q3_Tough, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_Quiz3_Anybody::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q3_Anybody, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

DragonsDen_Shrine_EventScript_Quiz3_WeakPerson::
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto_if_set FLAG_TEMP_4, DragonsDen_Shrine_EventScript_ElderQuiz3
	setflag FLAG_TEMP_4
	msgbox DragonsDen_Shrine_Text_Lillie_Q3_WeakPerson, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz3

@ --- Q4: Love (0) / Violence (1) / Knowledge (2) ---
DragonsDen_Shrine_EventScript_ElderQuiz4::
	message DragonsDen_Shrine_Text_Question4
	multichoice 20, 6, MULTI_ELDERQUIIZ4, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_Quiz4_Love
	case 1, DragonsDen_Shrine_EventScript_Quiz4_Violence
	case 2, DragonsDen_Shrine_EventScript_Quiz4_Knowledge
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz4
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

@ Lillie takes a moment longer to answer this one.
DragonsDen_Shrine_EventScript_Quiz4_Love::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox DragonsDen_Shrine_Text_Lillie_Q4_Love, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_Quiz4_Knowledge::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q4_Knowledge, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_Quiz4_Violence::
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto_if_set FLAG_TEMP_5, DragonsDen_Shrine_EventScript_ElderQuiz4
	setflag FLAG_TEMP_5
	msgbox DragonsDen_Shrine_Text_Lillie_Q4_Violence, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz4

@ --- Q5: Tough (0) / Weak (1) / Both (2) ---
DragonsDen_Shrine_EventScript_ElderQuiz5::
	message DragonsDen_Shrine_Text_Question5
	multichoice 20, 6, MULTI_ELDERQUIIZ5, FALSE 
	switch VAR_RESULT
	case 0, DragonsDen_Shrine_EventScript_Quiz5_Tough
	case 1, DragonsDen_Shrine_EventScript_Quiz5_Weak
	case 2, DragonsDen_Shrine_EventScript_ElderQuizFinish
	case MULTI_B_PRESSED, DragonsDen_Shrine_EventScript_ElderQuiz5
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_Quiz5_Tough::
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto_if_set FLAG_TEMP_6, DragonsDen_Shrine_EventScript_ElderQuiz5
	setflag FLAG_TEMP_6
	msgbox DragonsDen_Shrine_Text_Lillie_Q5_Tough, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_Quiz5_Weak::
	call DragonsDen_Shrine_EventScript_ElderWrong
	goto_if_set FLAG_TEMP_7, DragonsDen_Shrine_EventScript_ElderQuiz5
	setflag FLAG_TEMP_7
	msgbox DragonsDen_Shrine_Text_Lillie_Q5_Weak, MSGBOX_DEFAULT
	goto DragonsDen_Shrine_EventScript_ElderQuiz5

DragonsDen_Shrine_EventScript_ElderWrong::
	msgbox DragonsDen_Shrine_Text_WrongAnswer1, MSGBOX_DEFAULT
	addvar VAR_DRAGONS_DEN_QUIZ, 1
	return

@ Q5 Both: the vanilla verdict (RightAnswer + PassedTest) comes first, then the
@ Elder's words to both Trainers, the battle, and only then Clair's scene.
DragonsDen_Shrine_EventScript_ElderQuizFinish::
	msgbox DragonsDen_Shrine_Text_RightAnswer, MSGBOX_DEFAULT
	msgbox DragonsDen_Shrine_Text_Lillie_Q5_Both, MSGBOX_DEFAULT
	closemessage
	delay 20
	msgbox DragonsDen_Shrine_Text_PassedTest, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_LillieConclusion

DragonsDen_Shrine_EventScript_LillieConclusion::
	msgbox DragonsDen_Shrine_Text_ElderSameQuestions, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_ELDER, DIR_EAST
	msgbox DragonsDen_Shrine_Text_ElderToLillie, MSGBOX_DEFAULT
	closemessage
	msgbox DragonsDen_Shrine_Text_LillieAlmostDid, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_ELDER, DIR_SOUTH
	msgbox DragonsDen_Shrine_Text_ElderShowMe, MSGBOX_DEFAULT
	closemessage

	@ --- Lillie accepts, then introduces Ninetales ---
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox DragonsDen_Shrine_Text_LillieABattle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_EAST
	turnobject LOCALID_DRAGONSDEN3_NINETALES, DIR_WEST
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_NORMAL
	waitmoncry
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_SOUTH
	turnobject LOCALID_DRAGONSDEN3_NINETALES, DIR_SOUTH
	msgbox DragonsDen_Shrine_Text_LillieNinetales, MSGBOX_DEFAULT
	closemessage

	@ --- Battle without blackout: every outcome continues to Clair ---
	call Common_EventScript_OutOfCenterPartyHeal
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_5, VAR_RESULT
	setflag B_FLAG_NO_WHITEOUT
	setvar VAR_LAST_TALKED, LOCALID_DRAGONSDEN3_LILLIE
	removefieldmugshot
	trainerbattle_no_intro TRAINER_LILLIE_DRAGONS_DEN, DragonsDen_Shrine_Text_LillieDefeated
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT
	goto_if_eq VAR_TEMP_5, TRUE, DragonsDen_Shrine_EventScript_LillieKeepWhiteoutOff
	clearflag B_FLAG_NO_WHITEOUT
DragonsDen_Shrine_EventScript_LillieKeepWhiteoutOff::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_DRAGONSDEN3_LILLIE, DIR_SOUTH
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, DragonsDen_Shrine_EventScript_LilliePlayerWon
	goto_if_eq VAR_TEMP_3, B_OUTCOME_LOST, DragonsDen_Shrine_EventScript_LilliePlayerLost
	goto_if_eq VAR_TEMP_3, B_OUTCOME_DREW, DragonsDen_Shrine_EventScript_LillieDraw
	goto_if_eq VAR_TEMP_3, B_OUTCOME_FORFEITED, DragonsDen_Shrine_EventScript_LillieForfeit
	goto DragonsDen_Shrine_EventScript_LillieUnexpectedOutcome

@ B_OUTCOME_WON: DragonsDen_Shrine_Text_LillieDefeated already played in battle.
DragonsDen_Shrine_EventScript_LilliePlayerWon::
	msgbox DragonsDen_Shrine_Text_LillieAfterPlayerWon, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_LillieAfterBattle

DragonsDen_Shrine_EventScript_LilliePlayerLost::
	msgbox DragonsDen_Shrine_Text_LillieAfterLillieWon, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_LillieAfterBattle

DragonsDen_Shrine_EventScript_LillieDraw::
	msgbox DragonsDen_Shrine_Text_LillieAfterDraw, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_LillieAfterBattle

DragonsDen_Shrine_EventScript_LillieForfeit::
	msgbox DragonsDen_Shrine_Text_LillieAfterForfeit, MSGBOX_DEFAULT
	closemessage
	goto DragonsDen_Shrine_EventScript_LillieAfterBattle

@ Should not happen in a trainer battle. Nobody is declared the winner, and the
@ scene still continues: stopping here would strand the state-2 scene halfway.
DragonsDen_Shrine_EventScript_LillieUnexpectedOutcome::
	msgbox DragonsDen_Shrine_Text_LillieAfterDraw, MSGBOX_DEFAULT
	closemessage

DragonsDen_Shrine_EventScript_LillieAfterBattle::
	call Common_EventScript_OutOfCenterPartyHeal
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ElderNeitherResult, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox DragonsDen_Shrine_Text_LillieIWill, MSGBOX_DEFAULT
	closemessage
	call DragonsDen_Shrine_EventScript_CosmogComment

	@ --- Lillie and Ninetales leave together, before Clair arrives ---
	@ Lillie: (7,9) down column 7 -> (7,16) -> warp (6,16).
	@ Ninetales: steps into (7,9) behind her, then down to (7,16).
	@ Column 8 is blocked at (8,15), so Ninetales has to switch to column 7.
	msgbox DragonsDen_Shrine_Text_LillieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DRAGONSDEN3_LILLIE, DragonsDen_Shrine_Movement_LillieLeave
	applymovement LOCALID_DRAGONSDEN3_NINETALES, DragonsDen_Shrine_Movement_NinetalesLeave
	waitmovement LOCALID_DRAGONSDEN3_LILLIE
	waitmovement LOCALID_DRAGONSDEN3_NINETALES
	playse SE_EXIT
	removeobject LOCALID_DRAGONSDEN3_NINETALES
	removeobject LOCALID_DRAGONSDEN3_LILLIE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	delay 20
	goto DragonsDen_Shrine_EventScript_ClairEnter

DragonsDen_Shrine_Movement_LillieLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_in_place_down
	step_end

DragonsDen_Shrine_Movement_NinetalesLeave:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	step_end

DragonsDen_Shrine_Text_LillieArrival:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}! I didn't know\n"
	.string "Clair had sent you here.\p"
	.string "I heard the Dragon Clan doesn't\n"
	.string "test Trainers only in battle.\p"
	.string "They ask what you think about\n"
	.string "your Pokémon, too.\p"
	.string "I wanted to hear the questions\n"
	.string "for myself.$"

DragonsDen_Shrine_Text_ElderLillieObserves:
	.string "The young lady asked to\n"
	.string "observe your trial.\p"
	.string "But an answer teaches us about\n"
	.string "the one who gives it…\p"
	.string "…and the one who hears it.\p"
	.string "So I have asked her to answer\n"
	.string "as well.$"

DragonsDen_Shrine_Text_LillieNotSoSure:
	.string "{SPEAKER NAME_LILLIE}I thought I knew exactly\n"
	.string "what I would say on the way here.\p"
	.string "Now I'm not so sure.\p"
	.string "I think that may be the point.$"

DragonsDen_Shrine_Text_Lillie_Q1_Pal:
	.string "{SPEAKER NAME_LILLIE}An ally… Someone who\n"
	.string "stands beside you.\p"
	.string "I like that.\p"
	.string "I think I'd say “friend,” though.\p"
	.string "Sometimes Ninetales understands\n"
	.string "what I'm trying to do…\p"
	.string "…before I've even worked it\n"
	.string "out myself.$"

DragonsDen_Shrine_Text_Lillie_Q1_Friend:
	.string "{SPEAKER NAME_LILLIE}Friend… Yes.\n"
	.string "That's my answer too.\p"
	.string "Though lately I've wondered\n"
	.string "which of us is teaching\l"
	.string "the other.$"

DragonsDen_Shrine_Text_Lillie_Q1_Underling:
	.string "{SPEAKER NAME_LILLIE}I don't think I could\n"
	.string "call my Pokémon underlings.\p"
	.string "They notice things I miss far\n"
	.string "too often for that.$"

DragonsDen_Shrine_Text_Lillie_Q2_Strategy:
	.string "{SPEAKER NAME_LILLIE}I used to think having\n"
	.string "the right plan mattered most.\p"
	.string "Then I started noticing how\n"
	.string "often my Pokémon saw something\l"
	.string "before I did.\p"
	.string "Strategy matters… but only if\n"
	.string "I'm willing to change it.$"

DragonsDen_Shrine_Text_Lillie_Q2_Training:
	.string "{SPEAKER NAME_LILLIE}Training.\p"
	.string "I think I understand that answer\n"
	.string "much better now.\p"
	.string "It isn't only practicing the\n"
	.string "same thing until it's right.\p"
	.string "It's learning how each of us\n"
	.string "reacts when something goes\l"
	.string "wrong.$"

DragonsDen_Shrine_Text_Lillie_Q2_Cheating:
	.string "{SPEAKER NAME_LILLIE}I don't think that would\n"
	.string "be my answer.\p"
	.string "Winning wouldn't mean very much\n"
	.string "if we learned nothing from it.$"

DragonsDen_Shrine_Text_Lillie_Q3_Tough:
	.string "{SPEAKER NAME_LILLIE}I understand that.\p"
	.string "A strong Trainer can show you\n"
	.string "what you still need to learn.\p"
	.string "But someone doesn't have to look\n"
	.string "strong to surprise you.\p"
	.string "I think I'd choose anybody.$"

DragonsDen_Shrine_Text_Lillie_Q3_Anybody:
	.string "{SPEAKER NAME_LILLIE}Anybody.\n"
	.string "That's mine too.\p"
	.string "You don't really know what\n"
	.string "you'll learn from a battle\l"
	.string "until it starts.$"

DragonsDen_Shrine_Text_Lillie_Q3_WeakPerson:
	.string "{SPEAKER NAME_LILLIE}I don't think I'd choose\n"
	.string "someone because I expected\l"
	.string "them to lose.$"

DragonsDen_Shrine_Text_Lillie_Q4_Love:
	.string "{SPEAKER NAME_LILLIE}Love.\p"
	.string "Yes… but I think I'm still\n"
	.string "learning what that means.\p"
	.string "Caring about someone doesn't\n"
	.string "mean deciding everything\l"
	.string "for them.\p"
	.string "Sometimes it means listening\n"
	.string "when they choose something\l"
	.string "you didn't expect.$"

DragonsDen_Shrine_Text_Lillie_Q4_Knowledge:
	.string "{SPEAKER NAME_LILLIE}Knowledge is important.\p"
	.string "The more I understand my\n"
	.string "Pokémon, the easier it is to\l"
	.string "notice what they need.\p"
	.string "But knowing more about someone\n"
	.string "doesn't mean you should make\l"
	.string "every choice for them.\p"
	.string "I'd still choose love.$"

DragonsDen_Shrine_Text_Lillie_Q4_Violence:
	.string "{SPEAKER NAME_LILLIE}No.\p"
	.string "I want my Pokémon to grow\n"
	.string "because they trust me…\p"
	.string "…not because they're afraid.$"

DragonsDen_Shrine_Text_Lillie_Q5_Tough:
	.string "{SPEAKER NAME_LILLIE}Strength matters.\p"
	.string "But I wouldn't want that to be\n"
	.string "the only thing I noticed.$"

DragonsDen_Shrine_Text_Lillie_Q5_Weak:
	.string "{SPEAKER NAME_LILLIE}Weakness matters too.\p"
	.string "But I wouldn't want a Pokémon\n"
	.string "to think that's all I see.$"

DragonsDen_Shrine_Text_Lillie_Q5_Both:
	.string "{SPEAKER NAME_LILLIE}Both.\n"
	.string "That's my answer too.\p"
	.string "Their strengths tell me what\n"
	.string "they can do.\p"
	.string "Their weaknesses tell me where\n"
	.string "I need to stand beside them.$"

@ Holds for every answer combination, including a player whose accepted
@ answers match Lillie's own (Friend, Training, Anybody, Love, Both).
DragonsDen_Shrine_Text_ElderSameQuestions:
	.string "Interesting.\p"
	.string "You listened to the same\n"
	.string "questions.\p"
	.string "Yet each answer still had\n"
	.string "to be your own.\p"
	.string "Understanding another Trainer\n"
	.string "does not require surrendering\l"
	.string "your own judgment.$"

DragonsDen_Shrine_Text_ElderToLillie:
	.string "You listened before answering,\n"
	.string "yet you did not surrender your\l"
	.string "own judgment.$"

DragonsDen_Shrine_Text_LillieAlmostDid:
	.string "{SPEAKER NAME_LILLIE}I almost did.\n"
	.string "A few times.\p"
	.string "But then they wouldn't really\n"
	.string "have been my answers.$"

DragonsDen_Shrine_Text_ElderShowMe:
	.string "Words reveal conviction.\p"
	.string "But a Trainer cannot prepare\n"
	.string "every moment of a battle.\p"
	.string "When circumstances change,\n"
	.string "understanding must become\l"
	.string "action.\p"
	.string "Show me.$"

DragonsDen_Shrine_Text_LillieABattle:
	.string "{SPEAKER NAME_LILLIE}A battle…\n"
	.string "Yes. That makes sense.\p"
	.string "{PLAYER}, we've just spent all\n"
	.string "this time explaining what kind\l"
	.string "of Trainers we want to be.\p"
	.string "Let's see what we actually do\n"
	.string "when the plan stops being\l"
	.string "simple.$"

DragonsDen_Shrine_Text_LillieNinetales:
	.string "{SPEAKER NAME_LILLIE}You remember Vulpix,\n"
	.string "don't you?\p"
	.string "She evolved while we were\n"
	.string "traveling. I thought I would\l"
	.string "need to change everything.\p"
	.string "But she didn't become someone\n"
	.string "different.\p"
	.string "I just had to learn to keep up.$"

DragonsDen_Shrine_Text_LillieDefeated:
	.string "We adjusted again… and you\n"
	.string "still found the opening!$"

DragonsDen_Shrine_Text_LillieAfterPlayerWon:
	.string "{SPEAKER NAME_LILLIE}I thought I knew what\n"
	.string "you were going to do twice.\p"
	.string "I was wrong twice.\p"
	.string "But we didn't freeze when it\n"
	.string "happened.\p"
	.string "Goldenrod felt different from\n"
	.string "our first battle.\p"
	.string "This felt different again.$"

DragonsDen_Shrine_Text_LillieAfterLillieWon:
	.string "{SPEAKER NAME_LILLIE}We did it.\p"
	.string "And this time I don't think I\n"
	.string "need to apologize for being\l"
	.string "happy about that.\p"
	.string "You changed what you were doing\n"
	.string "halfway through.\p"
	.string "We noticed.\n"
	.string "And we changed too.$"

DragonsDen_Shrine_Text_LillieAfterDraw:
	.string "{SPEAKER NAME_LILLIE}Let's look after\n"
	.string "everyone first.\p"
	.string "I think we both learned\n"
	.string "something from that.$"

DragonsDen_Shrine_Text_LillieAfterForfeit:
	.string "{SPEAKER NAME_LILLIE}Oh… You're stopping\n"
	.string "there?\p"
	.string "Then let's look after\n"
	.string "everyone first.\p"
	.string "I think we both learned\n"
	.string "something from that.$"

DragonsDen_Shrine_Text_ElderNeitherResult:
	.string "Good.\p"
	.string "Neither result changes what I\n"
	.string "wished to see.\p"
	.string "You watched your Pokémon.\n"
	.string "You watched your opponent.\p"
	.string "And when the battle changed,\n"
	.string "you answered it together.\p"
	.string "Remember your answers.\p"
	.string "Not because they must remain\n"
	.string "the same forever.\p"
	.string "Remember why you gave them.$"

DragonsDen_Shrine_Text_LillieIWill:
	.string "{SPEAKER NAME_LILLIE}I will.\p"
	.string "And I think I'll remember some\n"
	.string "of yours, too.\p"
	.string "Even the ones I wouldn't have\n"
	.string "chosen.$"

DragonsDen_Shrine_Text_LillieFarewell:
	.string "{SPEAKER NAME_LILLIE}Thank you, Elder.\n"
	.string "And thank you, {PLAYER}.\p"
	.string "Come along, Ninetales!$"

DragonsDen_Shrine_Text_ElderGreeting:
    .string "Hm… Good to see you here.\p"
    .string "No need to explain why you came.\n"
    .string "Clair sent you here, didn't she?\p"
    .string "That girl is a handful…\n"
    .string "I am sorry, but I must test you.\p"
    .string "Not to worry, you are to answer\n"
    .string "only a few questions.\l"
    .string "Ready?$"

DragonsDen_Shrine_Text_Question1:
    .string "What are Pokémon to you?$"

DragonsDen_Shrine_Text_Question2:
    .string "What helps you to win battles?$"

DragonsDen_Shrine_Text_Question3:
    .string "What kind of trainer do you wish\n"
    .string "to battle?$"

DragonsDen_Shrine_Text_Question4:
    .string "What is most important for\n"
    .string "raising Pokémon?$"

DragonsDen_Shrine_Text_Question5:
    .string "Strong Pokémon. Weak Pokémon.\n"
    .string "Which is more important?$"

DragonsDen_Shrine_Text_WrongAnswer1:
    .string "Hah? I didn't quite catch that…$"

DragonsDen_Shrine_Text_WrongAnswer2:
    .string "What was it you said?$"

DragonsDen_Shrine_Text_RightAnswer:
    .string "Oh, I understand…$"

DragonsDen_Shrine_Text_PassedTest:
    .string "Hm… I see…\p"
    .string "You care deeply for Pokémon.\p"
    .string "Very commendable.\p"
    .string "That conviction is what is\n"
    .string "important!\p"
    .string "{PLAYER}, don't lose that belief.\p"
    .string "It will see you through at the\n"
    .string "Pokémon League.$"

DragonsDen_Shrine_EventScript_ClairEnter::
	clearflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	addobject LOCALID_DRAGONSDEN3_CLAIR
	playse SE_DOOR
	delay 40
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	delay 20
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_SOUTH
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairEnter
	waitmovement 0
	turnobject LOCALID_DRAGONSDEN3_ELDER, DIR_WEST	
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	turnobject OBJ_EVENT_ID_FOLLOWER, DIR_NORTH
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_ClairYouPassed, MSGBOX_DEFAULT
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairBackup1
	waitmovement 0
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_ClairThatCantBe, MSGBOX_DEFAULT
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairBackup2
	waitmovement 0
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_ClairYoureLying, MSGBOX_DEFAULT
	removefieldmugshot
	applymovement LOCALID_DRAGONSDEN3_ELDER, DragonsDen_Shrine_Movement_ElderWalkToClair
	waitmovement 0
	turnobject LOCALID_DRAGONSDEN3_CLAIR, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_MustIInformLance, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_DRAGONSDEN3_CLAIR, Common_Movement_ExclamationMark
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_IUnderstand, MSGBOX_DEFAULT
	removefieldmugshot
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairReturnToPlayer
	waitmovement 0
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_HereRisingBadge, MSGBOX_DEFAULT
	removefieldmugshot
	message DragonsDen_Shrine_Text_PlayerReceivedRisingBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_RisingBadgeExplanation, MSGBOX_DEFAULT
	removefieldmugshot
	setflag FLAG_BADGE08_GET
	special Achievement_CheckAll
	setflag FLAG_DEFEATED_BLACKTHORN_GYM
	addvar VAR_NUM_BADGES, 1

	applymovement LOCALID_DRAGONSDEN3_ELDER, DragonsDen_Shrine_Movement_ElderReturnToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	turnobject LOCALID_DRAGONSDEN3_CLAIR, DIR_NORTH
	msgbox DragonsDen_Shrine_Text_ElderScoldsClair, MSGBOX_DEFAULT
	closemessage
	delay 20
	createfieldmugshot MUGSHOT_CLAIR
	msgbox DragonsDen_Shrine_Text_Speechless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DRAGONSDEN3_CLAIR, DragonsDen_Shrine_Movement_ClairLeave
	waitmovement 0
	playse SE_EXIT
	setflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	removeobject LOCALID_DRAGONSDEN3_CLAIR
	clearflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setvar VAR_BLACKTHORN_CITY_STATE, 3
	release
	end

DragonsDen_Shrine_Movement_ClairEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

DragonsDen_Shrine_Movement_ClairBackup1:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ClairBackup2:
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	step_end

DragonsDen_Shrine_Movement_ElderWalkToClair:
	walk_left
	walk_left
	walk_left
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairReturnToPlayer:
	walk_right
	walk_right
	step_end

DragonsDen_Shrine_Movement_ElderReturnToPlayer:
	walk_slow_right
	walk_slow_right
	walk_slow_right
	face_down
	step_end

DragonsDen_Shrine_Movement_ClairLeave:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

DragonsDen_Shrine_Text_ClairYouPassed:
    .string "So how did it go?\p"
    .string "I guess there's no point\n"
	.string "in asking. You did fail?\p"
    .string "..................................\p"
    .string "…What? You passed?$"

DragonsDen_Shrine_Text_ClairThatCantBe:
    .string "That can't be!$"

DragonsDen_Shrine_Text_ClairYoureLying:
    .string "You're lying!\p"
    .string "Even I haven't been approved!$"

DragonsDen_Shrine_Text_MustIInformLance:
    .string "Clair!\p"
    .string "This child is impeccable,\n"
    .string "in skill and spirit!\p"
    .string "Admit defeat and confer the\n"
    .string "Risingbadge!\p"
    .string "…Or must I inform Lance of this?$"

DragonsDen_Shrine_Text_IUnderstand:
    .string "I-I understand…$"

DragonsDen_Shrine_Text_HereRisingBadge:
    .string "Here, this is the Risingbadge…\p"
    .string "Hurry up! Take it!$"

DragonsDen_Shrine_Text_PlayerReceivedRisingBadge:
    .string "{PLAYER} received Risingbadge.$"

DragonsDen_Shrine_Text_RisingBadgeExplanation:
    .string "Risingbadge will enable your\n"
    .string "Pokémon to use the move for\l"
    .string "climbing waterfalls.\p"
    .string "Also, all Pokémon will recognize\n"
    .string "you as a trainer and obey your\l"
    .string "every command without question.$"

DragonsDen_Shrine_Text_ElderScoldsClair:
    .string "Clair…\p"
    .string "Reflect upon what it is that you\n"
    .string "lack and this child has.$"

DragonsDen_Shrine_Text_Speechless:
    .string "..................................$"

DragonsDen_Shrine_Text_ComeAgain:
    .string "Come again, if you so desire.$"

DragonsDen_Shrine_Text_SilverIsInTraining:
    .string "A boy close to your age is in\n"
    .string "training here.\p"
    .string "He is much like Clair when she was\n"
    .string "younger. It is a little worrisome…$"

DragonsDen_Shrine_EventScript_Elder2::
	msgbox DragonsDen_Shrine_Text_Elder2, MSGBOX_NPC
	end

DragonsDen_Shrine_EventScript_Elder3::
	lock
	faceplayer
	msgbox DragonsDen_Shrine_Text_DracoMeteorTeach, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DragonsDen_Shrine_EventScript_DracoMeteorDeclined
	msgbox DragonsDen_Shrine_Text_DracoMeteorWhichMon, MSGBOX_DEFAULT
	setvar VAR_0x8005, MOVE_DRACO_METEOR
	call MoveTutor_EventScript_OpenBox
	goto_if_eq VAR_RESULT, FALSE, DragonsDen_Shrine_EventScript_DracoMeteorDeclined
	goto DragonsDen_Shrine_EventScript_DracoMeteorTaught
	end

DragonsDen_Shrine_Text_Elder2:
    .string "It's been quite some time since a\n"
    .string "trainer has gained our Master's\l"
    .string "rare approval.\p"
    .string "In fact, not since Master Lance.$"

DragonsDen_Shrine_EventScript_DracoMeteorDeclined::
	msgbox DragonsDen_Shrine_Text_DracoMeteorDeclined, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_EventScript_DracoMeteorTaught::
	msgbox DragonsDen_Shrine_Text_DracoMeteorTaught, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Text_DracoMeteorTeach:
    .string "Only the strongest Dragon Pokémon\n"
    .string "can master Draco Meteor.\p"
    .string "Would you like me to teach it to\n"
    .string "one of your Pokémon?$"

DragonsDen_Shrine_Text_DracoMeteorWhichMon:
    .string "Which Pokémon should learn\n"
    .string "Draco Meteor?$"

DragonsDen_Shrine_Text_DracoMeteorDeclined:
    .string "Come back whenever you wish to\n"
    .string "master the ultimate Dragon move.$"

DragonsDen_Shrine_Text_DracoMeteorTaught:
    .string "May Draco Meteor serve you well.$"

DragonsDen_Shrine_EventScript_ElderChooseDratini::
	goto_if_eq VAR_DRAGONS_DEN_QUIZ, 0, DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini
	goto DragonsDen_Shrine_EventScript_ElderGiveBasicDratini

DragonsDen_Shrine_EventScript_ElderGiveBasicDratini::
	goto_if_set FLAG_GOT_DRATINI, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRATINI
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	givemon SPECIES_DRATINI, 15, move1=MOVE_EXTREME_SPEED
	call Common_EventScript_GiftMon

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag FLAG_GOT_DRATINI
	release
	end

DragonsDen_Shrine_EventScript_ElderGiveSpecialDratini::
	goto_if_set FLAG_GOT_DRATINI, DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini
	msgbox DragonsDen_Shrine_Text_TakeThisDratini, MSGBOX_DEFAULT

	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_DRATINI
	bufferspeciesname STR_VAR_1, SPECIES_DRATINI
	givemon SPECIES_DRATINI, 15, move1=MOVE_EXTREME_SPEED, move2=MOVE_SPACIAL_REND, shinyMode=SHINY_MODE_ALWAYS
	call Common_EventScript_GiftMon

	msgbox DragonsDen_Shrine_Text_SymbolicDragon, MSGBOX_DEFAULT
	setflag FLAG_GOT_DRATINI
	release
	end

DragonsDen_Shrine_EventScript_ElderAlreadyGotDratini::
	msgbox DragonsDen_Shrine_Text_ClairsGrandfather, MSGBOX_DEFAULT
	release
	end

DragonsDen_Shrine_Text_TakeThisDratini:
    .string "Hm… Good to see you here.\p"
    .string "Your arrival is most fortunate.\p"
    .string "I have something for you.\p"
    .string "Take this Dratini as proof that I\n"
    .string "have recognized your worth.$"

DragonsDen_Shrine_Text_SymbolicDragon:
    .string "Dragon Pokémon are symbolic of our\n"
    .string "clan.\p"
    .string "You have shown that you can be\n"
    .string "entrusted with one.$"

DragonsDen_Shrine_Text_ClairsGrandfather:
    .string "Clair appears to have learned an\n"
    .string "invaluable lesson from you.\p"
    .string "I thank you as her grandfather.$"

@ Optional Sun & Moon callback: Lillie ties Nebby to the Elder's test.
@ Reacts to the first non-egg Cosmog/Cosmoem/Solgaleo/Lunala in the party
@ (CheckMysteryEggPokemon, the special Elm's Eviolite scene uses). Nothing
@ else changes: no flag, no var; VAR_RESULT is free at every call site.
DragonsDen_Shrine_EventScript_CosmogComment::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	goto_if_eq VAR_RESULT, SPECIES_NONE, DragonsDen_Shrine_EventScript_CosmogCommentEnd
	bufferspeciesname STR_VAR_1, VAR_RESULT
	applymovement LOCALID_DRAGONSDEN3_NINETALES, Common_Movement_ExclamationMark
	waitmovement LOCALID_DRAGONSDEN3_NINETALES
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, DragonsDen_Shrine_EventScript_CosmogCommentCosmog
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, DragonsDen_Shrine_EventScript_CosmogCommentCosmoem
	msgbox DragonsDen_Shrine_Text_CosmogLegend, MSGBOX_DEFAULT
	closemessage
	return

DragonsDen_Shrine_EventScript_CosmogCommentCosmog::
	msgbox DragonsDen_Shrine_Text_Cosmog, MSGBOX_DEFAULT
	closemessage
	return

DragonsDen_Shrine_EventScript_CosmogCommentCosmoem::
	msgbox DragonsDen_Shrine_Text_CosmogCosmoem, MSGBOX_DEFAULT
	closemessage
	return

DragonsDen_Shrine_EventScript_CosmogCommentEnd::
	return

DragonsDen_Shrine_Text_Cosmog:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}, before I go…\p"
	.string "Your Cosmog watched the whole\n"
	.string "test, didn't it?\p"
	.string "Nebby used to do that. Watch\n"
	.string "me carefully… and then do the\l"
	.string "exact opposite of what I asked.\p"
	.string "I think it was trusting me to\n"
	.string "catch up.\p"
	.string "The Elder might like that\n"
	.string "answer, I think.$"

DragonsDen_Shrine_Text_CosmogCosmoem:
	.string "{SPEAKER NAME_LILLIE}Your Cosmoem hasn't\n"
	.string "moved all day, has it?\p"
	.string "Nebby was like that, right\n"
	.string "before it changed. Everything\l"
	.string "was happening on the inside.\p"
	.string "Maybe that is what the Elder\n"
	.string "meant by strength.$"

DragonsDen_Shrine_Text_CosmogLegend:
	.string "{SPEAKER NAME_LILLIE}Your {STR_VAR_1}…\p"
	.string "Nebby grew up like that too.\n"
	.string "All at once, when it mattered.\p"
	.string "Ninetales and I are still\n"
	.string "catching up with you two.$"

