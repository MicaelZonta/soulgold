@ Greenfield, the town the Unown covered in crystal (Berry Master, plan part 14;
@ REI_DA_COLHEITA.md section 15.4). Layout: New Bark Town's, with flowers.
@
@ Plan (map.bin measured with dump_mapa.py):
@   west edge x 0, rows 11-14: coord_events back to the Ruins of Alph (3,26)
@   arrival from the crystal gate: (1,12), facing the town (east)
@   Peonia (3,12) facing east, only while VAR_HARVEST_KING = 10
@   woman (11,16) v, old man (20,22) <, boy (10,29) ^: stuck in the same
@     morning until the Glastrier leaves (GARDEN_STORY_WHITE_PATH)
@   mansion door (10,9) -> Greenfield_Mansion; the other doors are signs
@ The crystal itself is a palette tint (GreenfieldCrystal_*, src/berry_garden.c).
@
@ Temps: FLAG_TEMP_1 hides Peonia; VAR_TEMP_1 arms her arrival line (1 = armed,
@ 2 = done); VAR_TEMP_0 stays 0 for the exit triggers.
Greenfield_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Greenfield_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Greenfield_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Greenfield_OnFrame
	.byte 0

Greenfield_OnTransition::
	setflag FLAG_TEMP_1
	setvar VAR_TEMP_1, 0
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_ICEROOT, Greenfield_EventScript_TransitionEnd
	clearflag FLAG_TEMP_1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 1, Greenfield_EventScript_TransitionEnd
	setvar VAR_TEMP_1, 1
Greenfield_EventScript_TransitionEnd::
	end

@ Coming through the gate the player still faces west, into the rocks.
Greenfield_OnWarp::
	map_script_2 VAR_TEMP_0, 0, Greenfield_EventScript_FaceTown
	.2byte 0

Greenfield_EventScript_FaceTown::
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 1, Greenfield_EventScript_TransitionEnd
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	end

Greenfield_OnFrame::
	map_script_2 VAR_TEMP_1, 1, Greenfield_EventScript_PeoniaArrives
	.2byte 0

@ Player (1,12), Peonia (3,12): she turns west to say it, then back to the town.
Greenfield_EventScript_PeoniaArrives::
	setvar VAR_TEMP_1, 2
	lockall
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_GREENFIELD_PEONIA, DIR_WEST
	msgbox Greenfield_Text_PeoniaArrives, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GREENFIELD_PEONIA, DIR_EAST
	releaseall
	end

Greenfield_EventScript_Peonia::
	lock
	faceplayer
	msgbox Greenfield_Text_Peonia, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GREENFIELD_PEONIA, DIR_EAST
	release
	end

Greenfield_EventScript_WestExit::
	lockall
	warp MAP_RUINS_OF_ALPH_OUTSIDE, 3, 26
	waitstate
	releaseall
	end

@ VAR_RESULT = TRUE once the crystal is gone.
Greenfield_EventScript_CheckThawed::
	setvar VAR_0x8004, GARDEN_STORY_WHITE_PATH
	specialvar VAR_RESULT, GardenStory_Check
	return

Greenfield_EventScript_Woman::
	call Greenfield_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, Greenfield_EventScript_WomanAfter
	msgbox Greenfield_Text_Woman, MSGBOX_NPC
	end
Greenfield_EventScript_WomanAfter::
	msgbox Greenfield_Text_WomanAfter, MSGBOX_NPC
	end

Greenfield_EventScript_OldMan::
	call Greenfield_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, Greenfield_EventScript_OldManAfter
	msgbox Greenfield_Text_OldMan, MSGBOX_NPC
	end
Greenfield_EventScript_OldManAfter::
	msgbox Greenfield_Text_OldManAfter, MSGBOX_NPC
	end

Greenfield_EventScript_Boy::
	call Greenfield_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, Greenfield_EventScript_BoyAfter
	msgbox Greenfield_Text_Boy, MSGBOX_NPC
	end
Greenfield_EventScript_BoyAfter::
	msgbox Greenfield_Text_BoyAfter, MSGBOX_NPC
	end

Greenfield_EventScript_TownSign::
	msgbox Greenfield_Text_TownSign, MSGBOX_SIGN
	end

Greenfield_EventScript_SealedDoor::
	call Greenfield_EventScript_CheckThawed
	goto_if_eq VAR_RESULT, TRUE, Greenfield_EventScript_LockedDoor
	msgbox Greenfield_Text_SealedDoor, MSGBOX_SIGN
	end
Greenfield_EventScript_LockedDoor::
	msgbox Greenfield_Text_LockedDoor, MSGBOX_SIGN
	end

Greenfield_Text_PeoniaArrives:
	.string "{SPEAKER NAME_PEONIA}It's... it's all glass. The flowers are\n"
	.string "glass. The TREES are glass.\p"
	.string "Freezington's colder, though.\n"
	.string "...Okay, it isn't.$"

Greenfield_Text_Peonia:
	.string "{SPEAKER NAME_PEONIA}I'll keep watch out here. Glass makes\n"
	.string "me nervous.\p"
	.string "The big house at the top. That's where\n"
	.string "the cold comes from. ...Don't tell Dad\l"
	.string "I said I was nervous.$"

@ Before: the same morning, every time (section 15.5c).
Greenfield_Text_Woman:
	.string "Lovely morning, isn't it?$"

Greenfield_Text_OldMan:
	.string "The flowers will open any day now.$"

Greenfield_Text_Boy:
	.string "Molly said she'd play with me after\n"
	.string "lunch.$"

@ After: their day moved on (plan part 14, step 5; for the author to approve).
Greenfield_Text_WomanAfter:
	.string "What a long morning that was! I feel\n"
	.string "like I slept through a whole winter.\p"
	.string "And the bread I left to rise has taken\n"
	.string "over the kitchen.$"

Greenfield_Text_OldManAfter:
	.string "Well, look at that. They opened.\p"
	.string "I told everyone they would. Nobody\n"
	.string "listens to an old man until the flowers\l"
	.string "agree with him.$"

Greenfield_Text_BoyAfter:
	.string "Molly played with me! She's really bad\n"
	.string "at hide-and-seek.\p"
	.string "She hid behind the piano. I could hear\n"
	.string "her humming.$"

Greenfield_Text_TownSign:
	.string "GREENFIELD\n"
	.string "Where the flowers bloom all year$"

Greenfield_Text_SealedDoor:
	.string "The door is sealed in crystal.\p"
	.string "Inside, a clock is stuck between two\n"
	.string "ticks.$"

Greenfield_Text_LockedDoor:
	.string "The door is locked. Someone inside is\n"
	.string "laughing at a joke you didn't hear.$"
