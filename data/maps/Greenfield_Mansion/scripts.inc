@ The Hale mansion in Greenfield (Berry Master, plan part 14; REI_DA_COLHEITA.md
@ section 15.4). Layout: the DarkraiInn1 lobby with a salon above it.
@
@ Plan (map.bin measured with dump_mapa.py):
@   exit mat (9,21) -> Greenfield (10,9)
@   lobby rows 16-21; Molly at the piano (16,17) facing up
@   west hall x 0-5, stairs x 0-4 rows 12-14; the Scientist (5,11) looks west
@     over row 11, which the player has to cross to reach the salon
@   salon rows 4-9: the Glastrier asleep at (13,5); Professor Hale's note on
@     the table at (14,3), read from (14,4)
@
@ The Glastrier: offering the Iceroot Carrot opens a level-60 battle. Only the
@ capture moves on (VAR_HARVEST_KING 10 -> 12, GARDEN_STORY_WHITE_PATH);
@ running or knocking it out leaves it asleep for the next try, losing is the
@ usual whiteout. After the capture the map reloads with the player at (13,6)
@ and Molly walks up from (14,9) to (14,6), to the player's east, to give the
@ Never-Melt Ice. The carrot is taken in that same scene: "white path done and
@ the Iceroot still in the Bag" means the gift is still owed, so a scene cut
@ short is finished by talking to Molly at the piano (no new flag).
@
@ Temps: FLAG_TEMP_2 hides the Glastrier, FLAG_TEMP_3 Molly in the salon,
@ FLAG_TEMP_4 Molly at the piano; FLAG_TEMP_5 = Molly already said her piece
@ this visit; VAR_TEMP_1 arms the gift scene (1 = armed, 2 = done).
Greenfield_Mansion_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GreenfieldMansion_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GreenfieldMansion_OnFrame
	.byte 0

GreenfieldMansion_OnTransition::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	clearflag FLAG_TEMP_4
	setvar VAR_TEMP_1, 0
	call GreenfieldMansion_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, GreenfieldMansion_EventScript_TransitionThawed
	call_if_eq VAR_HARVEST_KING, HARVEST_KING_ICEROOT, GreenfieldMansion_EventScript_ShowGlastrier
	end

GreenfieldMansion_EventScript_ShowGlastrier::
	clearflag FLAG_TEMP_2
	return

GreenfieldMansion_EventScript_TransitionThawed::
	checkitem ITEM_ICEROOT_CARROT
	goto_if_eq VAR_RESULT, FALSE, GreenfieldMansion_EventScript_TransitionEnd
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 13, GreenfieldMansion_EventScript_TransitionEnd
	goto_if_ne VAR_0x8005, 6, GreenfieldMansion_EventScript_TransitionEnd
	clearflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setvar VAR_TEMP_1, 1
GreenfieldMansion_EventScript_TransitionEnd::
	end

GreenfieldMansion_OnFrame::
	map_script_2 VAR_TEMP_1, 1, GreenfieldMansion_EventScript_MollyComes
	.2byte 0

@ VAR_RESULT = TRUE once the Glastrier left with the player.
GreenfieldMansion_EventScript_CheckThawed::
	setvar VAR_0x8004, GARDEN_STORY_WHITE_PATH
	specialvar VAR_RESULT, GardenStory_Check
	return

@ ------------------------------------------------------------------ Molly
GreenfieldMansion_EventScript_Molly::
	lock
	faceplayer
	call GreenfieldMansion_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, GreenfieldMansion_EventScript_MollyThawed
	goto_if_set FLAG_TEMP_5, GreenfieldMansion_EventScript_MollyAgain
	setflag FLAG_TEMP_5
	msgbox GreenfieldMansion_Text_MollyVisitor, MSGBOX_DEFAULT
	msgbox GreenfieldMansion_Text_PassMessage, MSGBOX_DEFAULT
	msgbox GreenfieldMansion_Text_MollyInvitation, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MANSION_MOLLY, DIR_NORTH
	release
	end

GreenfieldMansion_EventScript_MollyAgain::
	msgbox GreenfieldMansion_Text_MollyAgain, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MANSION_MOLLY, DIR_NORTH
	release
	end

GreenfieldMansion_EventScript_MollyThawed::
	checkitem ITEM_ICEROOT_CARROT
	goto_if_eq VAR_RESULT, FALSE, GreenfieldMansion_EventScript_MollyPiano
	call GreenfieldMansion_EventScript_MollyGift
	release
	end

GreenfieldMansion_EventScript_MollyPiano::
	msgbox GreenfieldMansion_Text_MollyPiano, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MANSION_MOLLY, DIR_NORTH
	release
	end

@ In the salon, after her scene.
GreenfieldMansion_EventScript_MollySalon::
	lock
	faceplayer
	msgbox GreenfieldMansion_Text_MollyPiano, MSGBOX_DEFAULT
	release
	end

@ Player (13,6); Molly (14,9) walks up to (14,6), then they face each other.
GreenfieldMansion_EventScript_MollyComes::
	setvar VAR_TEMP_1, 2
	lockall
	applymovement LOCALID_MANSION_MOLLY_SALON, GreenfieldMansion_Movement_MollyUp
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	call GreenfieldMansion_EventScript_MollyGift
	releaseall
	end

@ The carrot is the "gift still owed" mark: it goes only once the ice is in the Bag.
GreenfieldMansion_EventScript_MollyGift::
	msgbox GreenfieldMansion_Text_MollyMelting, MSGBOX_DEFAULT
	giveitem ITEM_NEVER_MELT_ICE
	goto_if_eq VAR_RESULT, FALSE, GreenfieldMansion_EventScript_MollyBagFull
	removeitem ITEM_ICEROOT_CARROT
	msgbox GreenfieldMansion_Text_MollyPiano, MSGBOX_DEFAULT
	closemessage
	return

GreenfieldMansion_EventScript_MollyBagFull::
	msgbox GreenfieldMansion_Text_MollyBagFull, MSGBOX_DEFAULT
	closemessage
	return

GreenfieldMansion_Movement_MollyUp:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

@ ------------------------------------------------------------- the Glastrier
GreenfieldMansion_EventScript_Glastrier::
	lock
	checkitem ITEM_ICEROOT_CARROT
	goto_if_eq VAR_RESULT, FALSE, GreenfieldMansion_EventScript_GlastrierSleeps
	checkitemspace ITEM_NEVER_MELT_ICE, 1
	goto_if_eq VAR_RESULT, FALSE, GreenfieldMansion_EventScript_GlastrierBagFull
	msgbox GreenfieldMansion_Text_GlastrierOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GreenfieldMansion_EventScript_GlastrierEnd
	msgbox GreenfieldMansion_Text_GlastrierWakes, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_GLASTRIER, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_GLASTRIER, 60
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, GreenfieldMansion_EventScript_GlastrierCaught
	msgbox GreenfieldMansion_Text_GlastrierStillHere, MSGBOX_DEFAULT
GreenfieldMansion_EventScript_GlastrierEnd::
	release
	end

GreenfieldMansion_EventScript_GlastrierSleeps::
	msgbox GreenfieldMansion_Text_GlastrierSleeps, MSGBOX_DEFAULT
	release
	end

GreenfieldMansion_EventScript_GlastrierBagFull::
	msgbox GreenfieldMansion_Text_GlastrierBagFull, MSGBOX_DEFAULT
	release
	end

GreenfieldMansion_EventScript_GlastrierCaught::
	setvar VAR_HARVEST_KING, HARVEST_KING_GLASTRIER
	setvar VAR_0x8004, GARDEN_STORY_WHITE_PATH
	special GardenStory_Mark
	fadescreen FADE_TO_BLACK
	warpsilent MAP_GREENFIELD_MANSION, 13, 6
	waitstate
	release
	end

@ ----------------------------------------------------------- the Scientist
GreenfieldMansion_EventScript_Scientist::
	trainerbattle_single TRAINER_GREENFIELD_SCIENTIST, GreenfieldMansion_Text_ScientistSeen, GreenfieldMansion_Text_ScientistBeaten
	call GreenfieldMansion_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, GreenfieldMansion_EventScript_ScientistThawed
	msgbox GreenfieldMansion_Text_ScientistAfter, MSGBOX_AUTOCLOSE
	end

GreenfieldMansion_EventScript_ScientistThawed::
	msgbox GreenfieldMansion_Text_ScientistThawed, MSGBOX_AUTOCLOSE
	end

GreenfieldMansion_EventScript_HaleNote::
	msgbox GreenfieldMansion_Text_HaleNote, MSGBOX_SIGN
	end

@ ------------------------------------------------------------------- texts
GreenfieldMansion_Text_MollyVisitor:
	.string "{SPEAKER NAME_MOLLY}Oh. A visitor. We don't get visitors.\n"
	.string "We don't get anything.\l"
	.string "That's the point, I think.\p"
	.string "When I was little, I wished for a\n"
	.string "family, and the Unown made one out of\l"
	.string "crystal.\p"
	.string "This time it isn't me. Something at the\n"
	.string "back of the house is wishing.\p"
	.string "It isn't cruel. It's just afraid of\n"
	.string "being forgotten. I know that feeling.$"

GreenfieldMansion_Text_PassMessage:
	.string "{PLAYER} passed on the old man's\n"
	.string "good evening.$"

GreenfieldMansion_Text_MollyInvitation:
	.string "{SPEAKER NAME_MOLLY}The old man from Mahogany?\p"
	.string "...He never came to dinner.\n"
	.string "Tell him the invitation stands.$"

GreenfieldMansion_Text_MollyAgain:
	.string "{SPEAKER NAME_MOLLY}It sleeps in Papa's study, up the hall.\n"
	.string "Be gentle with it.$"

GreenfieldMansion_Text_MollyMelting:
	.string "{SPEAKER NAME_MOLLY}It's melting. The flowers are growing.\p"
	.string "...I'd forgotten flowers do that.\p"
	.string "Papa kept this on his desk. Ice that\n"
	.string "never melted. It should go with the\l"
	.string "horse.$"

GreenfieldMansion_Text_MollyPiano:
	.string "{SPEAKER NAME_MOLLY}The piano's out of tune. It's never\n"
	.string "been out of tune before.\p"
	.string "I think I love it.$"

GreenfieldMansion_Text_MollyBagFull:
	.string "{SPEAKER NAME_MOLLY}Your Bag's full. Come back for it.\n"
	.string "I'll be at the piano.$"

GreenfieldMansion_Text_GlastrierSleeps:
	.string "The great horse sleeps on the crystal.\n"
	.string "It doesn't stir.$"

GreenfieldMansion_Text_GlastrierBagFull:
	.string "The great horse sleeps on the crystal.\p"
	.string "Your Bag is too full. Make room in it\n"
	.string "before you wake it.$"

GreenfieldMansion_Text_GlastrierOffer:
	.string "The great horse sleeps on the crystal.\p"
	.string "Offer it the Iceroot Carrot?$"

GreenfieldMansion_Text_GlastrierWakes:
	.string "The great horse opens one eye.\n"
	.string "It knows the smell.\p"
	.string "It knew it before it knew you.$"

GreenfieldMansion_Text_GlastrierStillHere:
	.string "The great horse lowers its head onto\n"
	.string "the crystal again.\p"
	.string "It isn't going anywhere.\n"
	.string "Neither is the cold.$"

GreenfieldMansion_Text_HaleNote:
	.string "A note in Professor Hale's hand:\p"
	.string "“It sleeps here because nothing here\n"
	.string "changes. Nothing is lost. Nothing is\l"
	.string "forgotten.\p"
	.string "Be kind to it. Everyone who ever loved\n"
	.string "it left.”$"

GreenfieldMansion_Text_ScientistSeen:
	.string "Don't move! You'll smudge my readings!\p"
	.string "I came to measure the crystal this\n"
	.string "morning. It's still this morning.\l"
	.string "It has been for a while.$"

GreenfieldMansion_Text_ScientistBeaten:
	.string "Fine! Measure it yourself!$"

GreenfieldMansion_Text_ScientistAfter:
	.string "My watch says 9:14. It always says 9:14.\n"
	.string "I've stopped asking it.$"

GreenfieldMansion_Text_ScientistThawed:
	.string "9:15! It moved!\p"
	.string "...I have to call the lab. I have to\n"
	.string "call my mother.$"
