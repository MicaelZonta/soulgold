.set LOCALID_BLACKTHORN_BOY, 2

BlackthornCity_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BlackthornCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, BlackthornCity_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BlackthornCity_OnLoad::
	goto_if_unset FLAG_BADGE05_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset FLAG_BADGE06_GET, BlackThornCity_EventScript_MoveGymBoy
	goto_if_unset FLAG_BADGE07_GET, BlackThornCity_EventScript_MoveGymBoy
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY
	end

BlackThornCity_EventScript_MoveGymBoy::
	setobjectxyperm LOCALID_BLACKTHORN_BOY, 24, 27
	end

BlackthornCity_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 4, BlackthornCity_EventScript_Call
	.2byte 0

BlackthornCity_EventScript_CityEnter:: 
	setflag FLAG_VISITED_BLACKTHORN_CITY
	callnative SetTimeBasedEncounters
	call BlackthornCity_EventScript_ApplyUBVisibility
	end

@ Rift Mission 1 visibility, recomputed on every map load (ON_TRANSITION runs
@ before the first spawn, and ClearTempFieldEventData has just zeroed every
@ temp, so this must run unconditionally). Also runs when arriving on foot
@ from Route 44/45 or the Ice Path, not only through a warp.
@   FLAG_TEMP_1 - the cast (Looker, Anabel, Gladion, Silvally): shown only
@                 while the incident is active.
@   FLAG_TEMP_2 - the Ultra Beasts: always hidden at load; only the scene
@                 itself brings them in, so a retry after a blackout starts
@                 from a clean street.
BlackthornCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	goto_if_unset FLAG_EVENT_ULTRABEAST_BLACKTHORN, BlackthornCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	return

BlackthornCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	return

BlackthornCity_EventScript_Call::
	lock
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_BLACKTHORN_CITY_STATE, 5
	setvar VAR_NEWBARKTOWN_LABSTATE, 7
	release
	end

BlackthornCity_Text_BaobaCall:
	.string "Warden Baoba: {PLAYER}!\p"
	.string "This is Warden Baoba.\p"
	.string "I'm calling to tell you that\n"
	.string "the Safari Zone has expanded!\p"
	.string "Please come visit!$"

BlackthornCity_Text_ElmCall:
	.string "Prof. Elm: Hello, {PLAYER}?\p"
	.string "I have something here for you.\n"
	.string "Could you swing by my Lab?\p"
	.string "See you later!$"

BlackThornCity_EventScript_Sage::
	lock
	faceplayer
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_SageRefuse
	msgbox BlackthornGrampsGrantsEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_SageRefuse::
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_Trigger_Sage::
	lock
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_EAST
	msgbox BlackthornGrampsRefusesEntryText, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_WalkDown1
	waitmovement 0
	turnobject LOCALID_BLACKTHORN_SAGE, DIR_SOUTH
	release
	end

BlackthornCity_EventScript_GymBoy::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE05_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset FLAG_BADGE06_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_unset FLAG_BADGE07_GET, BlackThornCity_EventScript_GymBoyNotReady
	goto_if_eq VAR_BLACKTHORN_CITY_STATE, 1, BlackThornCity_EventScript_GymBoyBefore
	msgbox BlackthornCity_Text_ClairIsBeaten, MSGBOX_DEFAULT
	closemessage
	release
	end	

BlackThornCity_EventScript_GymBoyNotReady::
	msgbox BlackthornCity_Text_ClairNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

BlackThornCity_EventScript_GymBoyBefore::
	msgbox BlackthornCity_Text_ClairIsIn, MSGBOX_DEFAULT
	closemessage
	release
	end	

BlackthornCity_EventScript_BlackBelt::
	msgbox BlackBeltText_VoicesInMyHead, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF::
	msgbox BlackthornCooltrainerF1Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_Youngster::
	msgbox BlackthornYoungsterText, MSGBOX_NPC
	end

BlackthornCity_EventScript_CoolTrainerF2::
	msgbox BlackthornCooltrainerF2Text, MSGBOX_NPC
	end

BlackthornCity_EventScript_CitySign::
	msgbox BlackthornCitySignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_GymSign::
	msgbox BlackthornGymSignText, MSGBOX_SIGN
	end

BlackthornCity_EventScript_MoveHouseSign::
	msgbox BlackthornCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

BlackthornCity_EventScript_DragonsDenSign::
	msgbox BlackthornCity_Text_DragonDenSign, MSGBOX_SIGN
	end

Blackthorn_EventScript_SuperRod::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUPER_ROD, Route12_House_EventScript_SuperRodGot
	msgbox Route12_House_Text_OfferSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route12_House_EventScript_SuperRodRefused
	msgbox Route12_House_Text_GiveSuperRod, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	msgbox Route12_House_Text_GaveSuperRod, MSGBOX_DEFAULT
	setflag FLAG_GOT_SUPER_ROD
	closemessage
	release
	end


BlackthornCity_EventScript_Santos::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SPELL_TAG, BlackthornCity_EventScript_SantosCompleted
	msgbox BlackthornCity_MeetSantosText, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, BlackthornCity_EventScript_SantosNope
	case 1, BlackthornCity_EventScript_SantosNope
	case 2, BlackthornCity_EventScript_SantosNope
	case 3, BlackthornCity_EventScript_SantosNope
	case 4, BlackthornCity_EventScript_SantosNope
	case 5, BlackthornCity_EventScript_SantosNope
	case 6, BlackthornCity_EventScript_SantosYes
	case 7 BlackthornCity_EventScript_SantosCancel
	case MULTI_B_PRESSED, BlackthornCity_EventScript_SantosCancel
	closemessage
	release
	end
BlackthornCity_EventScript_SantosYes::
	msgbox BlackthornCity_SantosGivesGiftText, MSGBOX_DEFAULT
	giveitem ITEM_SPELL_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_SPELL_TAG
	msgbox BlackthornCity_SantosGaveGiftText, MSGBOX_DEFAULT
	closemessage
	release
	end
BlackthornCity_EventScript_SantosNope::
	msgbox BlackthornCity_SantosNopeText, MSGBOX_DEFAULT
	closemessage
	release
	end
BlackthornCity_EventScript_SantosCancel::
	closemessage
	release
	end
BlackthornCity_EventScript_SantosCompleted::
	msgbox BlackthornCity_SantosSaturdayText, MSGBOX_DEFAULT
	closemessage
	release
	end


BlackthornCity_Text_ClairNotReady:
	.string "Clair, our Gym Leader, has been\n"
	.string "following your progress.\p"
	.string "However, she only battles trainers\n"
	.string "who already have 7 badges.$"

BlackthornCity_Text_ClairIsIn:
	.string "Clair, our Gym Leader, is waiting\n"
	.string "for you.\p"
	.string "However, it would be impossible for\n"
	.string "a run-of-the-mill trainer to win.$"

BlackthornCity_Text_ClairIsBeaten:
	.string "You defeated Clair?\p"
	.string "That's amazing!\p"
	.string "I've never heard of her losing to\n"
	.string "anyone other than Lance.$"

BlackthornGrampsRefusesEntryText:
	.string "No. Only chosen trainers may train\n"
	.string "here.\p"
	.string "Please leave.$"

BlackthornGrampsGrantsEntryText:
	.string "If Clair allows it, her grand-\n"
	.string "father--our Master--will also.\p"
	.string "You may enter.$"

BlackBeltText_VoicesInMyHead:
	.string "Arooo! Voices in my head!\p"
	.string "Huh? I'm listening to my radio!$"

BlackthornCooltrainerF1Text:
	.string "Are you going to make your Pokémon\n"
	.string "remember some moves?$"

BlackthornYoungsterText:
	.string "Dragon masters all come from the city\n"
	.string "of Blackthorn.$"

BlackthornCity_MeetSantosText:
	.string "Santos: …\p"
	.string "I'm Santos of the weekday family.\p"
	.string "Take a guess.$"

BlackthornCity_SantosGivesGiftText:
	.string "You can have this…$"

BlackthornCity_SantosGaveGiftText:
	.string "Santos: …\p"
	.string "Spell Tag…\p"
	.string "Ghost-type moves get stronger…\p"
	.string "It will frighten you…$"

BlackthornCity_SantosSaturdayText:
	.string "Santos: …\p"
	.string "See you again on another Saturday…\p"
	.string "I won't have any more gifts…$"

BlackthornCity_SantosNopeText:
	.string "Santos: No.$"

BlackthornCooltrainerF2Text:
	.string "Wow, you came through the Ice Path?\p"
	.string "You must be a real hotshot trainer!$"

BlackthornCitySignText:
	.string "Blackthorn City\p"
	.string "A Quiet Mountain Retreat$"

BlackthornGymSignText:
	.string "Blackthorn City Pokémon Gym\n"
	.string "Leader: Clair\p"
	.string "The Blessed User of Dragon Pokémon$"

BlackthornCity_Text_MoveDeletersHouseSign:
	.string "Move Bros' House$"

BlackthornCity_Text_DragonDenSign:
	.string "Dragon's Den Ahead$"

@ ============================================================================
@ Rift Mission 1 - Buzzwole + Pheromosa in Blackthorn City.
@
@ Active while FLAG_EVENT_ULTRABEAST_BLACKTHORN is set, which by invariant
@ means VAR_RIFT_MISSIONS_STATE == 3. Set by OlivineCity_House1, cleared here
@ on victory together with state 4.
@
@ Scene floor plan (raw collision, bit 11; '#' = blocked; y grows DOWNWARD):
@
@        x= 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28
@   y=48     #  #  #  #  #  .  .  .  .  .  #  #  #  W  #   W (27,48) Center door
@   y=49     .  .  P  .  .  S  G  .  .  .  .  .  .  f  .   f (27,49) Fly landing
@   y=50     .  .  B  .  .  .  *  .  .  .  .  .  .  .  .   * (20,50) player's spot
@   y=51     .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
@   y=52     .  #  .  .  #  #  .  .  .  #  #  t  a  .  .   t (25,52) talk to Looker
@   y=53     #  #  #  #  #  #  .  .  .  #  #  L  A  #  #   a (26,52) talk to Anabel
@   y=54     .  .  .  #  #  #  .  .  .  #  #  #  #  #  #
@
@   L Looker (25,53)    A Anabel (26,53)
@   G Gladion (20,49)   S Silvally (19,49)
@   B Buzzwole (16,50)  P Pheromosa (16,49)   - B/P hidden until the scene
@
@ Looker sits in a pocket: (24,53) and (25,54) are wall and (26,53) is Anabel.
@ The ONLY tile he can be talked to from is (25,52), facing down. That is what
@ makes the start of the cutscene deterministic without a getplayerxy check.
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1 - cast visibility cache      (see ApplyUBVisibility above)
@   FLAG_TEMP_2 - Ultra Beast visibility cache
@   VAR_TEMP_2  - battle outcome
@   VAR_TEMP_3  - the player's pick: 0 = Buzzwole, 1 = Pheromosa. Survives the
@                 battle because returning from a battle does not reload the
@                 map (ClearTempFieldEventData only runs on warp/edge loads).
@ ============================================================================

BlackthornCity_EventScript_UBAnabel::
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBAnabelIdle, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Gladion and Silvally watch the west road, so he is put back facing west
@ after faceplayer turns him (player is east or south of (20,49)).
BlackthornCity_EventScript_UBGladion::
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBGladionIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_WEST
	release
	end

@ Nothing changes state before the YES. The YES is the last exit point:
@ from there on everything is scripted through to a battle outcome.
BlackthornCity_EventScript_UBLooker::
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox BlackthornCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBNotReady
	goto BlackthornCity_EventScript_UBScene

BlackthornCity_EventScript_UBNotReady::
	msgbox BlackthornCity_Text_UBNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

@ SKELETON: the rift is a camera shake plus a white flash and the beasts
@ appear standing still. Evolution: portal animation, the beasts moving in,
@ their own music.
BlackthornCity_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	@ Player (25,52)->(25,51)->(25,50)->(24,50)->(23,50)->(22,50)->(21,50)
	@ ->(20,50), then faces west. Every tile checked free; Gladion and
	@ Silvally are on row 49, so nobody is in the way.
	applymovement OBJ_EVENT_ID_PLAYER, BlackthornCity_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Looker (25,53)->(25,52) and Anabel (26,53)->(26,52): same one-step
	@ sequence in different columns, so they never contend for a tile and
	@ can walk together. Both end facing west, toward the player at (20,50).
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_StepUpFaceLeft
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_StepUpFaceLeft
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	msgbox BlackthornCity_Text_UBGladionBrief, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 6  @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_BLACKTHORN_UB_BUZZWOLE
	addobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox BlackthornCity_Text_UBAppear, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBChoose

@ Standard Rift Mission structure: the player picks which Ultra Beast to
@ fight, the mission companion takes the other. No cancel (ignoreBPress
@ TRUE) - the scene has already started. The pick is per attempt: after a
@ blackout the player chooses again.
@ Everyone already faces the right way whichever branch is taken: the player
@ (20,50) and Gladion (20,49) are east of both beasts at x=16, and the
@ beasts face east. No turnobject is needed.
BlackthornCity_EventScript_UBChoose::
	msgbox BlackthornCity_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, BlackthornCity_Text_ChoiceBuzzwole, BlackthornCity_Text_ChoicePheromosa
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Buzzwole, 1 = Pheromosa
	closemessage
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBPickPheromosa
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	msgbox BlackthornCity_Text_UBPickedBuzzwole, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBBattle

BlackthornCity_EventScript_UBPickPheromosa::
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	msgbox BlackthornCity_Text_UBPickedPheromosa, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBBattle

@ Boss battle through the project's boss system. Boss setup only survives a
@ SIMPLE battle, which is the other reason the mission splits the beasts.
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
@ losing means a blackout and a retry.
@ SKELETON: level moves only, 2 bars, x110 stats, level 70. Evolution: a
@ curated moveset via seteventmonmoves, a held item, its own phase profile.
BlackthornCity_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBSetupPheromosa
	setbossbattle 2, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_BUZZWOLE, 70
	goto BlackthornCity_EventScript_UBStartBattle

BlackthornCity_EventScript_UBSetupPheromosa::
	setbossbattle 2, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_PHEROMOSA, 70

@ LOST, DREW and FORFEITED never come back here - the engine blacks the
@ player out to the Blackthorn Pokémon Center. CAUGHT and RAN are
@ unreachable (ball blocked; Run becomes FORFEITED in a boss) but are
@ handled anyway: anything that is not WON resets the scene, never wins it.
BlackthornCity_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, BlackthornCity_EventScript_UBResolved
	goto BlackthornCity_EventScript_UBUnresolved

@ Nothing was recorded as done: the event flag is still set, so reloading
@ the map puts the cast back on its map.json spots with the beasts hidden
@ again, and talking to Looker restarts the whole scene - the pick included.
BlackthornCity_EventScript_UBUnresolved::
	msgbox BlackthornCity_Text_UBGotAway, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_BLACKTHORN_CITY, 27, 49
	waitstate
	releaseall
	end

@ Gladion's fight against the other beast is narrative: it resolves with the
@ player's win and only his line afterwards changes with the pick.
@ SKELETON: evolution can stage his fight on screen before or after ours.
BlackthornCity_EventScript_UBResolved::
	@ Both beast objects are still on the map: a battle does not reload it.
	@ Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_BUZZWOLE
	removeobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreen FADE_FROM_WHITE
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBGladionFoughtBuzzwole
	msgbox BlackthornCity_Text_UBGladionFoughtPheromosa, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBAfterBattle

BlackthornCity_EventScript_UBGladionFoughtBuzzwole::
	msgbox BlackthornCity_Text_UBGladionFoughtBuzzwole, MSGBOX_DEFAULT

BlackthornCity_EventScript_UBAfterBattle::
	msgbox BlackthornCity_Text_UBAfterGladion, MSGBOX_DEFAULT
	closemessage
	@ Looker (25,52)->(25,51)->(25,50)->(24,50)->(23,50)->(22,50)->(21,50),
	@ faces west at the player in (20,50).
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_LookerToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	@ Anabel (26,52)->(26,51)->(25,51)->(24,51)->(23,51)->(22,51), faces
	@ west. SEQUENTIAL on purpose: her path crosses (25,51), which Looker
	@ occupies on his first step, so the two must never walk together here.
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_AnabelToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_SOUTH   @ player (20,50) is below (20,49)
	msgbox BlackthornCity_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_BLACKTHORN    @ invariant: flag and var together
	setvar VAR_RIFT_MISSIONS_STATE, 4
	@ Reload in place under the fade. With the flag cleared the residents
	@ would otherwise pop in one by one as the camera moved, and the cast
	@ would linger; ON_TRANSITION repopulates the city and hides the cast
	@ in one go. Gladion and Silvally leave together, as they must.
	warpsilent MAP_BLACKTHORN_CITY, 20, 50
	waitstate
	releaseall
	end

BlackthornCity_Movement_PlayerToLine:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

BlackthornCity_Movement_StepUpFaceLeft:
	walk_up
	face_left
	step_end

BlackthornCity_Movement_LookerToPlayer:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

BlackthornCity_Movement_AnabelToPlayer:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

@ SKELETON: all dialogue below is placeholder. Rewrite in the design's voice
@ (Gladion short and concrete; Looker theatrical and warm; Anabel precise).
@ See SOULGOLD_RIFT_MISSIONS_DESIGN.md section 3.1.
BlackthornCity_Text_UBAnabelIdle:
	.string "Anabel: Looker has the\n"
	.string "details.\p"
	.string "Speak with him when you're\n"
	.string "ready.$"

BlackthornCity_Text_UBGladionIdle:
	.string "Gladion: …You're the Champion\n"
	.string "now? Good.\p"
	.string "Talk to Looker. Silvally and\n"
	.string "I are watching the west road.$"

BlackthornCity_Text_UBLookerGreet:
	.string "Looker: {PLAYER}! Good.\p"
	.string "The street is clear, the\n"
	.string "residents are safe indoors.\p"
	.string "The readings are strongest\n"
	.string "to the west.$"

BlackthornCity_Text_UBReady:
	.string "Looker: Once we begin, there\n"
	.string "is no stopping halfway.\p"
	.string "Are your Pokémon ready?$"

BlackthornCity_Text_UBNotReady:
	.string "Looker: Of course.\p"
	.string "The Pokémon Center is right\n"
	.string "behind us. I will be here.$"

BlackthornCity_Text_UBGladionBrief:
	.string "Gladion: You're here.\p"
	.string "Something tore the air open\n"
	.string "over there a minute ago.\p"
	.string "Anabel: Looker, keep the\n"
	.string "doors shut.\p"
	.string "I'll watch the Center.$"

BlackthornCity_Text_UBAppear:
	.string "Looker: Two of them!\n"
	.string "Buzzwole and Pheromosa!$"

BlackthornCity_Text_UBChoosePrompt:
	.string "Gladion: We split them.\p"
	.string "Pick one, {PLAYER}.\n"
	.string "Silvally and I take the other.$"

BlackthornCity_Text_ChoiceBuzzwole:
	.string "Buzzwole$"

BlackthornCity_Text_ChoicePheromosa:
	.string "Pheromosa$"

BlackthornCity_Text_UBPickedBuzzwole:
	.string "Gladion: The big one's yours,\n"
	.string "then.\p"
	.string "Silvally--the fast one!$"

BlackthornCity_Text_UBPickedPheromosa:
	.string "Gladion: Fine.\p"
	.string "Silvally, we hold the big\n"
	.string "one.\p"
	.string "Don't let it near the houses!$"

BlackthornCity_Text_UBGotAway:
	.string "Looker: They slipped back\n"
	.string "through the rift…\p"
	.string "It is not over. Regroup, and\n"
	.string "we try again.$"

BlackthornCity_Text_UBGladionFoughtPheromosa:
	.string "Gladion: Pheromosa was fast.\n"
	.string "Silvally was faster.$"

BlackthornCity_Text_UBGladionFoughtBuzzwole:
	.string "Gladion: That Buzzwole hit\n"
	.string "like a wall.\p"
	.string "Silvally didn't give it\n"
	.string "an inch.$"

BlackthornCity_Text_UBAfterGladion:
	.string "Gladion: …They're gone.\p"
	.string "Back through wherever they\n"
	.string "came from.\p"
	.string "You held your side. Good.$"

BlackthornCity_Text_UBHook:
	.string "Looker: Magnificent work,\n"
	.string "both of you!\p"
	.string "And no one was hurt. That is\n"
	.string "what matters most.\p"
	.string "Anabel: This was not a single\n"
	.string "incident.\p"
	.string "The rift closed, but the\n"
	.string "readings did not stop.\p"
	.string "Looker: While you were\n"
	.string "fighting, our office received\l"
	.string "another report.\p"
	.string "Strange lights over the Lake\n"
	.string "of Rage, near Mahogany Town.\p"
	.string "Anabel: Rest first, {PLAYER}.\p"
	.string "When you're ready, come back\n"
	.string "to our house in Olivine.\p"
	.string "We'll brief you there.\p"
	.string "Gladion: Mahogany… Lillie was\n"
	.string "heading that way.\p"
	.string "If this involves her, I want\n"
	.string "to know.\p"
	.string "Looker: Then it is settled!\n"
	.string "Olivine, {PLAYER}!\p"
	.string "We will be waiting!$"
