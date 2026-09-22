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
@   FLAG_TEMP_1 - the cast already on the street when the player arrives
@                 (Looker, Anabel, Clair, Kingdra): shown only while the
@                 incident is active.
@   FLAG_TEMP_2 - the Ultra Beasts: always hidden at load; only the scene
@                 itself brings them in, so a retry after a blackout starts
@                 from a clean street.
@   FLAG_TEMP_3 - Gladion and Silvally: always hidden at load. Their arrival
@                 is the surprise of the scene; nobody mentions him before.
@   FLAG_TEMP_4 - Necrozma: shown only while the incident is active. It has
@                 its own flag because the scene removes it on its own.
BlackthornCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	goto_if_unset FLAG_EVENT_ULTRABEAST_BLACKTHORN, BlackthornCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_4
	return

BlackthornCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_4
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
@ Rift Mission 1 - Necrozma, Buzzwole + Pheromosa in Blackthorn City.
@
@ Active while FLAG_EVENT_ULTRABEAST_BLACKTHORN is set, which by invariant
@ means VAR_RIFT_MISSIONS_STATE == 3. Set by OlivineCity_House1, cleared here
@ on victory together with state 4. While it is set, every building door in
@ town is locked except the Pokemon Center's (sLockedTownDoors in
@ src/field_control_avatar.c -> BlackthornCity_EventScript_DoorLocked).
@
@ Story: Clair is already holding off Necrozma when the player arrives. The
@ player joins her, Necrozma tears a rift open, Buzzwole and Pheromosa come
@ through and charge straight at the player, and Gladion and Silvally cut
@ them off at the last second. After the battle Necrozma absorbs both beasts
@ and leaves (the pattern of every mission). Gladion then gives the player a
@ Type: Null.
@
@ Scene floor plan (raw collision, bit 11; '#' = blocked; y grows DOWNWARD):
@
@        x= 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
@   y=44     .  .  .  .  .  .  s  g  .  .  .  .  .  .  .   s/g Silvally/Gladion
@   y=45     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #       spawn (hidden)
@   y=46     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
@   y=47     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
@   y=48     .  #  #  W  #  .  v  |  .  .  .  .  #  #  W   W (16,48) Mart, (27,48) Center
@   y=49     #  .  .  .  K  C  :  G  .  .  .  .  .  .  f   f (27,49) Fly landing
@   y=50     .  N  B  >  >  b  S  *  .  .  .  .  .  .  .   * (20,50) player's spot
@   y=51     .  .  P  >  >  p  .  .  .  .  .  .  .  .  .
@   y=52     .  .  #  .  .  #  #  .  .  .  #  #  t  a  .   t (25,52) talk to Looker
@   y=53     #  #  #  #  #  #  #  .  .  .  #  #  L  A  #   a (26,52) talk to Anabel
@
@   L Looker (25,53)      A Anabel (26,53)
@   C Clair (18,49)       K Kingdra (17,49)       N Necrozma (14,50)
@   B Buzzwole (15,50)    P Pheromosa (15,51)     - hidden until the rift
@   b/p where the charge stops: (18,50)/(18,51); recoil to (17,50)/(17,51)
@   g Gladion (20,44) -> down column 20 -> G (20,49)
@   s Silvally (19,44) -> down column 19 to (19,48) -> jump_2 -> S (19,50)
@
@ Looker sits in a pocket: (24,53) and (25,54) are wall and (26,53) is Anabel.
@ The ONLY tile he can be talked to from is (25,52), facing down. That is what
@ makes the start of the cutscene deterministic without a getplayerxy check.
@ Gladion/Silvally spawn at y=44, six rows above the player: off screen.
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1 - street cast visibility cache (see ApplyUBVisibility above)
@   FLAG_TEMP_2 - Ultra Beast visibility cache
@   FLAG_TEMP_3 - Gladion + Silvally visibility cache
@   FLAG_TEMP_4 - Necrozma visibility cache
@   VAR_TEMP_2  - battle outcome
@   VAR_TEMP_3  - the player's pick: 0 = Buzzwole, 1 = Pheromosa. Survives the
@                 battle because returning from a battle does not reload the
@                 map (ClearTempFieldEventData only runs on warp/edge loads).
@   VAR_TEMP_4  - Cosmog-family species Necrozma reacted to (SPECIES_NONE =
@                 no reaction). Read again by the aftermath dialogue.
@ Object budget: player + follower + 9 cast = 11/16 (light sprites are not
@ object events, see NEWBARK_ULTRABEAST_IMPLEMENTATION.md section 12.8).
@ ============================================================================

BlackthornCity_EventScript_DoorLocked::
	lockall
	msgbox BlackthornCity_Text_DoorLocked, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BlackthornCity_EventScript_UBAnabel::
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBAnabelIdle, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	goto_if_eq VAR_RESULT, SPECIES_NONE, BlackthornCity_EventScript_UBReleaseEnd
	bufferspeciesname STR_VAR_1, VAR_RESULT
	msgbox BlackthornCity_Text_UBAnabelIdleCosmog, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

@ Clair and Kingdra keep facing Necrozma, so no faceplayer: she talks over
@ her shoulder.
BlackthornCity_EventScript_UBClair::
	lock
	msgbox BlackthornCity_Text_UBClairIdle, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBKingdra::
	lock
	playmoncry SPECIES_KINGDRA, CRY_MODE_NORMAL
	msgbox BlackthornCity_Text_UBKingdraIdle, MSGBOX_DEFAULT
	waitmoncry
	goto BlackthornCity_EventScript_UBReleaseEnd

@ Optional reaction: with a Cosmog-family Pokemon in the party, Necrozma
@ already notices it here, before the scene.
BlackthornCity_EventScript_UBNecrozma::
	lock
	msgbox BlackthornCity_Text_UBNecrozmaIdle, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	goto_if_eq VAR_RESULT, SPECIES_NONE, BlackthornCity_EventScript_UBReleaseEnd
	bufferspeciesname STR_VAR_1, VAR_RESULT
	playmoncry SPECIES_NECROZMA, CRY_MODE_NORMAL
	msgbox BlackthornCity_Text_UBNecrozmaIdleCosmog, MSGBOX_DEFAULT
	waitmoncry
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBReleaseEnd::
	closemessage
	release
	end

@ Nothing changes state before the YES. The YES is the last exit point:
@ from there on everything is scripted through to a battle outcome.
@ Gladion gives a Type: Null at the end, so party AND PC full blocks the YES
@ (skill entregar-pokemon-ou-ovo): checked here, before any offer, and the
@ player simply comes back after making room.
BlackthornCity_EventScript_UBLooker::
	lock
	faceplayer
	msgbox BlackthornCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, BlackthornCity_EventScript_UBLookerAsk
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_EventScript_UBLookerAsk
	msgbox BlackthornCity_Text_UBNoRoom, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBLookerAsk::
	msgbox BlackthornCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBNotReady
	goto BlackthornCity_EventScript_UBScene

BlackthornCity_EventScript_UBNotReady::
	msgbox BlackthornCity_Text_UBNotReady, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

@ SKELETON: the rift and every hit are camera shakes plus white flashes; the
@ Pokemon only walk in place. Evolution: move animations (field effects),
@ a portal sprite, Necrozma's own music.
BlackthornCity_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	@ Player (25,52)->(25,51)->(25,50)->(24,50)->(23,50)->(22,50)->(21,50)
	@ ->(20,50), then faces west. Every tile checked free; Clair and Kingdra
	@ are on row 49 at x=17..18, nobody is on row 50 east of x=15.
	applymovement OBJ_EVENT_ID_PLAYER, BlackthornCity_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Looker (25,53)->(25,52) and Anabel (26,53)->(26,52): same one-step
	@ sequence in different columns, so they never contend for a tile and
	@ can walk together. Both end facing west, toward the player at (20,50).
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_StepUpFaceLeft
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_StepUpFaceLeft
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	@ Player (20,50) is east of Clair (18,49): dx=+2 dominates -> DIR_EAST.
	turnobject LOCALID_BLACKTHORN_UB_CLAIR, DIR_EAST
	msgbox BlackthornCity_Text_UBClairArrive, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_BLACKTHORN_UB_CLAIR, DIR_WEST
	@ Kingdra attacks: in place, still facing west at Necrozma (14,50).
	applymovement LOCALID_BLACKTHORN_UB_KINGDRA, BlackthornCity_Movement_AttackInPlaceLeft
	playmoncry SPECIES_KINGDRA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_BLACKTHORN_UB_KINGDRA
	waitmoncry
	call BlackthornCity_EventScript_UBFlash
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_PulseInPlaceRight
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	msgbox BlackthornCity_Text_UBNoEffect, MSGBOX_DEFAULT
	closemessage
	@ The rift: Necrozma cries, the street shakes, the beasts come through
	@ right next to it.
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	call BlackthornCity_EventScript_UBShake
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
	closemessage
	@ The charge, straight past Clair at the player: Buzzwole (15,50)->(18,50)
	@ on row 50, Pheromosa (15,51)->(18,51) on row 51. Same sequence from
	@ offset rows -> formation kept, never the same tile. (19,50) stays free
	@ for Silvally.
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, BlackthornCity_Movement_UBCharge
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, BlackthornCity_Movement_UBCharge
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	@ The rescue. Silvally (19,44) runs down column 19 to (19,48) and leaps
	@ over (19,49) to land on (19,50), between Buzzwole and the player.
	@ Gladion (20,44) runs down column 20 to (20,49), right above the
	@ player. Different columns the whole way -> they move together.
	clearflag FLAG_TEMP_3
	addobject LOCALID_BLACKTHORN_UB_SILVALLY
	addobject LOCALID_BLACKTHORN_UB_GLADION
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyRescue
	applymovement LOCALID_BLACKTHORN_UB_GLADION, BlackthornCity_Movement_GladionArrive
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	playmoncry SPECIES_SILVALLY, CRY_MODE_ENCOUNTER
	call BlackthornCity_EventScript_UBShake
	@ Both beasts are thrown back one tile, still facing east:
	@ (18,50)->(17,50) and (18,51)->(17,51).
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, BlackthornCity_Movement_UBKnockedBack
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, BlackthornCity_Movement_UBKnockedBack
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	waitmovement LOCALID_BLACKTHORN_UB_GLADION
	waitmoncry
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, Common_Movement_ExclamationMark
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, Common_Movement_ExclamationMark
	applymovement LOCALID_BLACKTHORN_UB_CLAIR, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	waitmovement LOCALID_BLACKTHORN_UB_CLAIR
	msgbox BlackthornCity_Text_UBGladionArrives, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBChoose

BlackthornCity_EventScript_UBFlash::
	fadescreen FADE_TO_WHITE
	fadescreen FADE_FROM_WHITE
	return

BlackthornCity_EventScript_UBShake::
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	return

@ Standard Rift Mission structure: the player picks which Ultra Beast to
@ fight, the mission companion takes the other. No cancel (ignoreBPress
@ TRUE) - the scene has already started. The pick is per attempt: after a
@ blackout the player chooses again.
@ Everyone already faces the right way whichever branch is taken: the player
@ (20,50), Silvally (19,50) and Gladion (20,49) are east of both beasts at
@ x=17, and the beasts face east. No turnobject is needed.
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
@ First step of the difficulty scale (design section 6): 3 bars / Lv75 /
@ x120 / curated moveset + held item. Mission 2 is 4 / Lv80 / x130, so the
@ scale still climbs.
@ Order, as in the existing macros (asm/macros/event.inc): setbossbattle ->
@ playmoncry -> seteventmon -> seteventmonmoves -> special. No path leaves
@ the script in between, so no clearbossbattle is needed.
BlackthornCity_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBSetupPheromosa
	setbossbattle 3, SPECIES_NONE, 120, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_BUZZWOLE, 75, ITEM_LEFTOVERS
	seteventmonmoves MOVE_BULK_UP, MOVE_DRAIN_PUNCH, MOVE_LEECH_LIFE, MOVE_ICE_PUNCH
	goto BlackthornCity_EventScript_UBStartBattle

BlackthornCity_EventScript_UBSetupPheromosa::
	setbossbattle 3, SPECIES_NONE, 120, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_PHEROMOSA, 75, ITEM_LIFE_ORB
	seteventmonmoves MOVE_QUIVER_DANCE, MOVE_BUG_BUZZ, MOVE_FOCUS_BLAST, MOVE_ICE_BEAM

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
@ the map puts the cast back on its map.json spots with the beasts, Gladion
@ and Silvally hidden again, and talking to Looker restarts the whole scene
@ - the pick included.
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
@ Then Necrozma absorbs BOTH beasts - the pattern of every Rift Mission.
@ Positions at this point (a battle does not reload the map): Buzzwole
@ (17,50), Pheromosa (17,51), Necrozma (14,50).
BlackthornCity_EventScript_UBResolved::
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBGladionFoughtBuzzwole
	msgbox BlackthornCity_Text_UBGladionFoughtPheromosa, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBAbsorb

BlackthornCity_EventScript_UBGladionFoughtBuzzwole::
	msgbox BlackthornCity_Text_UBGladionFoughtBuzzwole, MSGBOX_DEFAULT

BlackthornCity_EventScript_UBAbsorb::
	closemessage
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_PulseInPlaceRight
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	waitmoncry
	@ Dragged backwards, still facing east, to the tiles next to Necrozma:
	@ (17,50)->(15,50) and (17,51)->(15,51). Same sequence, offset rows.
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, BlackthornCity_Movement_UBPulledIn
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, BlackthornCity_Movement_UBPulledIn
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	call BlackthornCity_EventScript_UBShake
	@ Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_BUZZWOLE
	removeobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	applymovement LOCALID_BLACKTHORN_UB_CLAIR, Common_Movement_ExclamationMark
	applymovement LOCALID_BLACKTHORN_UB_GLADION, Common_Movement_ExclamationMark
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, Common_Movement_ExclamationMark
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_CLAIR
	waitmovement LOCALID_BLACKTHORN_UB_GLADION
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	waitmoncry
	msgbox BlackthornCity_Text_UBAbsorbed, MSGBOX_DEFAULT
	closemessage
	call BlackthornCity_EventScript_UBNecrozmaSensesCosmog
	@ Necrozma leaves the way it came. Own flag (FLAG_TEMP_4): removeobject
	@ touches nobody else.
	call BlackthornCity_EventScript_UBShake
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_NECROZMA
	fadescreen FADE_FROM_WHITE
	msgbox BlackthornCity_Text_UBNecrozmaGone, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBAftermath

@ Optional reaction to a Cosmog-family Pokemon in the party (non-egg; the
@ special is the one Elm's Eviolite scene uses). Checked AFTER the battle on
@ purpose: the battle can evolve it. Necrozma steps toward the player,
@ (14,50)->(15,50), free since Buzzwole was removed.
BlackthornCity_EventScript_UBNecrozmaSensesCosmog::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, BlackthornCity_EventScript_UBReturn
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_NecrozmaLean
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	playmoncry SPECIES_NECROZMA, CRY_MODE_NORMAL
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmoncry
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, BlackthornCity_EventScript_UBNecrozmaSensesLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, BlackthornCity_EventScript_UBNecrozmaSensesLegend
	msgbox BlackthornCity_Text_UBNecrozmaSensesCosmog, MSGBOX_DEFAULT
	closemessage
	return

BlackthornCity_EventScript_UBNecrozmaSensesLegend::
	msgbox BlackthornCity_Text_UBNecrozmaSensesLegend, MSGBOX_DEFAULT
	closemessage
	return

BlackthornCity_EventScript_UBReturn::
	return

BlackthornCity_EventScript_UBAftermath::
	@ Looker (25,52)->(25,51)->(25,50)->(24,50)->(23,50)->(22,50)->(21,50),
	@ faces west at the player in (20,50).
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_LookerToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	@ Anabel (26,52)->(26,51)->(25,51)->(24,51)->(23,51)->(22,51), faces
	@ west. SEQUENTIAL on purpose: her path crosses (25,51), which Looker
	@ occupies on his first step, so the two must never walk together here.
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_AnabelToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	@ Everyone onto the player (20,50): Clair (18,49) east, Gladion (20,49)
	@ south (player below him), Silvally (19,50) east.
	turnobject LOCALID_BLACKTHORN_UB_CLAIR, DIR_EAST
	turnobject LOCALID_BLACKTHORN_UB_KINGDRA, DIR_EAST
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_SOUTH
	turnobject LOCALID_BLACKTHORN_UB_SILVALLY, DIR_EAST
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox BlackthornCity_Text_UBAftermath, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, BlackthornCity_EventScript_UBGift
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, BlackthornCity_EventScript_UBAftermathLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, BlackthornCity_EventScript_UBAftermathLegend
	msgbox BlackthornCity_Text_UBAftermathCosmog, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBGift

BlackthornCity_EventScript_UBAftermathLegend::
	msgbox BlackthornCity_Text_UBAftermathLegend, MSGBOX_DEFAULT
	closemessage

@ Gladion's gift. Space was checked before the YES and nothing since can
@ fill the party or the PC (the battle blocks catching), so MON_CANT_GIVE is
@ unreachable - but it is still guarded, BEFORE the state changes: a failed
@ gift never counts as delivered. The guard replays the mission.
@ SKELETON: level 50, no held item, plain Poke Ball.
BlackthornCity_EventScript_UBGift::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox BlackthornCity_Text_UBGladionGift, MSGBOX_DEFAULT
	closemessage
	bufferspeciesname STR_VAR_1, SPECIES_TYPE_NULL
	givemon SPECIES_TYPE_NULL, 50
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BlackthornCity_EventScript_UBGiftNoRoom
	call Common_EventScript_GiftMon
	msgbox BlackthornCity_Text_UBGladionGiftAfter, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox BlackthornCity_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_BLACKTHORN    @ invariant: flag and var together
	setvar VAR_RIFT_MISSIONS_STATE, 4
	@ Reload in place under the fade. With the flag cleared the residents
	@ would otherwise pop in one by one as the camera moved, and the cast
	@ would linger; ON_TRANSITION repopulates the city and hides the cast
	@ in one go. Gladion and Silvally leave together, as they must. The
	@ doors unlock with the flag.
	warpsilent MAP_BLACKTHORN_CITY, 20, 50
	waitstate
	releaseall
	end

BlackthornCity_EventScript_UBGiftNoRoom::
	msgbox BlackthornCity_Text_UBGiftNoRoom, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBUnresolved

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

BlackthornCity_Movement_AttackInPlaceLeft:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

BlackthornCity_Movement_PulseInPlaceRight:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

BlackthornCity_Movement_UBCharge:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

BlackthornCity_Movement_SilvallyRescue:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	jump_2_down
	face_left
	step_end

BlackthornCity_Movement_GladionArrive:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	face_left
	step_end

BlackthornCity_Movement_UBKnockedBack:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

BlackthornCity_Movement_UBPulledIn:
	lock_facing_direction
	walk_slow_left
	walk_slow_left
	unlock_facing_direction
	step_end

BlackthornCity_Movement_NecrozmaLean:
	walk_slow_right
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

@ Voices (design section 3.1): Looker theatrical and warm, direct in danger;
@ Anabel precise and calm; Gladion short and concrete; Clair proud, in
@ command of her town. Nobody names Necrozma: to everyone here it is a
@ Pokemon they have never seen. Nobody says where the next rift will open.
BlackthornCity_Text_DoorLocked:
	.string "The door is locked tight.\p"
	.string "A note is taped to it:\n"
	.string "“Stay inside until I say so.\l"
	.string "--Clair, Gym Leader”$"

BlackthornCity_Text_UBAnabelIdle:
	.string "Anabel: Every house is sealed\n"
	.string "and the Center is open.\p"
	.string "Clair hasn't taken one step\n"
	.string "back since we arrived.\p"
	.string "Speak with Looker when you\n"
	.string "are ready. Not before.$"

BlackthornCity_Text_UBAnabelIdleCosmog:
	.string "Anabel: …Is that a {STR_VAR_1}\n"
	.string "traveling with you?\p"
	.string "In Alola they call them\n"
	.string "children of the stars.\p"
	.string "Keep it close today.$"

BlackthornCity_Text_UBClairIdle:
	.string "Clair: Stay back. I've got it.\p"
	.string "It came out of a flash of\n"
	.string "light this morning and hasn't\l"
	.string "moved since.\p"
	.string "It isn't hurting anyone.\n"
	.string "It's… waiting for something.\p"
	.string "If you want to be useful, talk\n"
	.string "to the detective by the\l"
	.string "Pokémon Center.$"

BlackthornCity_Text_UBKingdraIdle:
	.string "Kingdra won't take its eyes\n"
	.string "off the creature.$"

BlackthornCity_Text_UBNecrozmaIdle:
	.string "A Pokémon made of something\n"
	.string "like black crystal.\p"
	.string "Light keeps gathering along\n"
	.string "its body, then vanishing into\l"
	.string "it.\p"
	.string "It doesn't seem to notice\n"
	.string "you at all.$"

BlackthornCity_Text_UBNecrozmaIdleCosmog:
	.string "…!\p"
	.string "It turned its head.\p"
	.string "Not toward you. Toward the\n"
	.string "Poké Ball that holds your\l"
	.string "{STR_VAR_1}.$"

BlackthornCity_Text_UBLookerGreet:
	.string "Looker: {PLAYER}! You came.\n"
	.string "Good. Very good.\p"
	.string "Everyone is safe indoors.\n"
	.string "Clair saw to that before we\l"
	.string "even arrived.\p"
	.string "The creature is down the\n"
	.string "street, to the west.\p"
	.string "It has not moved in an hour.\n"
	.string "Neither has she.$"

BlackthornCity_Text_UBNoRoom:
	.string "Looker: Ah--but first, one of\n"
	.string "Anabel's rules.\p"
	.string "On every operation, you keep\n"
	.string "room for one more Pokémon.\l"
	.string "In your party or your Boxes.\p"
	.string "Yours are both full.\p"
	.string "If a rift leaves a Pokémon\n"
	.string "stranded, it must have\l"
	.string "somewhere safe to go.\p"
	.string "Make some room, and come\n"
	.string "back to me. I will be here.$"

BlackthornCity_Text_UBReady:
	.string "Looker: Once we step out\n"
	.string "there, there is no stepping\l"
	.string "back.\p"
	.string "Are you and your Pokémon\n"
	.string "ready?$"

BlackthornCity_Text_UBNotReady:
	.string "Looker: Of course. Heal up.\n"
	.string "Check your team.\p"
	.string "Clair can hold a little\n"
	.string "longer. She has made that\l"
	.string "very clear to me.$"

BlackthornCity_Text_UBClairArrive:
	.string "Clair: So you're the new\n"
	.string "Champion. Lance mentioned you.\p"
	.string "Then watch closely. I've been\n"
	.string "trying to hurt this thing for\l"
	.string "an hour.\p"
	.string "Kingdra! Dragon Pulse!$"

BlackthornCity_Text_UBNoEffect:
	.string "Clair: …Nothing.\n"
	.string "Not even a scratch.\p"
	.string "It doesn't fight back.\n"
	.string "It just… drinks the light.$"

BlackthornCity_Text_UBAppear:
	.string "Anabel: Rift opening!\n"
	.string "Two signatures!\p"
	.string "Looker: {PLAYER}, get back!\n"
	.string "They are coming right at you!$"

BlackthornCity_Text_UBGladionArrives:
	.string "Gladion: …Don't just stand\n"
	.string "there.\p"
	.string "Looker: And who might YOU be?!\p"
	.string "Gladion: Gladion.\p"
	.string "I saw the light over the\n"
	.string "mountains. Figured someone\l"
	.string "would need help.\p"
	.string "Clair: Another Trainer? Fine.\n"
	.string "The more the better!$"

BlackthornCity_Text_UBChoosePrompt:
	.string "Gladion: Two of them.\n"
	.string "Two of us.\p"
	.string "Pick one, {PLAYER}.\n"
	.string "Silvally and I take the other.\p"
	.string "Clair: And I'll keep that\n"
	.string "crystal thing busy. Go!$"

BlackthornCity_Text_ChoiceBuzzwole:
	.string "Buzzwole$"

BlackthornCity_Text_ChoicePheromosa:
	.string "Pheromosa$"

BlackthornCity_Text_UBPickedBuzzwole:
	.string "Gladion: The big one's yours.\p"
	.string "Silvally--the fast one.\n"
	.string "Don't let it get past you!$"

BlackthornCity_Text_UBPickedPheromosa:
	.string "Gladion: Then we take the\n"
	.string "heavy one.\p"
	.string "Silvally, hold the line.\n"
	.string "Nothing gets near the houses.$"

BlackthornCity_Text_UBGotAway:
	.string "Looker: They pulled back into\n"
	.string "the rift…\p"
	.string "It is not over. Regroup, and\n"
	.string "we try again.$"

BlackthornCity_Text_UBGladionFoughtPheromosa:
	.string "Gladion: Silvally!\p"
	.string "…Good. It's down.\p"
	.string "Pheromosa was fast.\n"
	.string "Silvally was faster.$"

BlackthornCity_Text_UBGladionFoughtBuzzwole:
	.string "Gladion: That's enough,\n"
	.string "Silvally.\p"
	.string "It hit like a wall. We didn't\n"
	.string "give it an inch.$"

BlackthornCity_Text_UBAbsorbed:
	.string "Clair: What…?\n"
	.string "It's pulling them in!\p"
	.string "Looker: It… took them.\n"
	.string "Both of them. Just like that.\p"
	.string "Gladion: It didn't fight them.\n"
	.string "It fed on them.\p"
	.string "Anabel: That is not how an\n"
	.string "Ultra Beast behaves.\p"
	.string "That is not how anything\n"
	.string "behaves.$"

BlackthornCity_Text_UBNecrozmaSensesCosmog:
	.string "The creature is staring past\n"
	.string "you… at the Poké Ball that\l"
	.string "holds your {STR_VAR_1}.\p"
	.string "Your {STR_VAR_1} is trembling.\p"
	.string "Gladion: Silvally, in front!\n"
	.string "Don't let it closer!$"

BlackthornCity_Text_UBNecrozmaSensesLegend:
	.string "Light flares between the\n"
	.string "creature and your\l"
	.string "{STR_VAR_1}'s Poké Ball!\p"
	.string "It recoils… then steadies,\n"
	.string "and stares.\p"
	.string "Your {STR_VAR_1} doesn't look\n"
	.string "away.$"

BlackthornCity_Text_UBNecrozmaGone:
	.string "Clair: …It's gone.\p"
	.string "Opened a hole in the sky over\n"
	.string "my town, ate what came out,\l"
	.string "and left.$"

BlackthornCity_Text_UBAftermath:
	.string "Looker: Is anyone hurt?\n"
	.string "{PLAYER}? Your Pokémon?\p"
	.string "…Good. Good. The report can\n"
	.string "wait a moment.\p"
	.string "Clair: Blackthorn owes you\n"
	.string "both. You and… Gladion, was it?\p"
	.string "I'll tell the town it's safe.\n"
	.string "Then I'm going to train until\l"
	.string "I understand what I just saw.\p"
	.string "Anabel: It opened the rift.\n"
	.string "It took the two that came\l"
	.string "through. Then it left.\p"
	.string "It wasn't attacking Blackthorn.\n"
	.string "It was feeding.\p"
	.string "Gladion: …I've seen light like\n"
	.string "that before. In Alola.\p"
	.string "Looker: Then we would very much\n"
	.string "like to hear what you know.\p"
	.string "Gladion: Later.$"

BlackthornCity_Text_UBAftermathCosmog:
	.string "Gladion: It looked at your\n"
	.string "{STR_VAR_1}. Not at us.\p"
	.string "Keep it close, {PLAYER}.\n"
	.string "I mean it.\p"
	.string "Anabel: Children of the\n"
	.string "stars… I would like to know\l"
	.string "what that creature wanted\l"
	.string "with one.$"

BlackthornCity_Text_UBAftermathLegend:
	.string "Gladion: It flinched at your\n"
	.string "{STR_VAR_1}. Remember that.\p"
	.string "Anabel: In Alola, {STR_VAR_1} is a\n"
	.string "legend of the sky itself.\p"
	.string "For something made of light\n"
	.string "to flinch at one… that means\l"
	.string "something.$"

BlackthornCity_Text_UBGladionGift:
	.string "Gladion: {PLAYER}.\n"
	.string "There's something else.\p"
	.string "Two weeks ago I found another\n"
	.string "Type: Null. In the mountains\l"
	.string "past Route 45.\p"
	.string "Alone. Someone left it\n"
	.string "behind. Same as mine.\p"
	.string "It won't settle with me. It\n"
	.string "keeps trying to be Silvally's\l"
	.string "shadow.\p"
	.string "It needs its own Trainer.\p"
	.string "It watched you fight just\n"
	.string "now. …I think it's decided.\p"
	.string "Take care of it.$"

BlackthornCity_Text_UBGladionGiftAfter:
	.string "Gladion: Don't decide\n"
	.string "everything for it.\p"
	.string "Let it take the first step.\n"
	.string "It'll surprise you.$"

BlackthornCity_Text_UBGiftNoRoom:
	.string "Gladion: …You don't have room\n"
	.string "for it. Not in your team, not\l"
	.string "in your Boxes.\p"
	.string "Sort that out. Then we'll do\n"
	.string "this properly.$"

BlackthornCity_Text_UBHook:
	.string "Anabel: The readings haven't\n"
	.string "settled. That creature will\l"
	.string "open another rift.\p"
	.string "Where, and when, we don't\n"
	.string "know yet.\p"
	.string "Looker: So we keep watching.\p"
	.string "Rest, {PLAYER}. Then come to\n"
	.string "our house in Olivine.\p"
	.string "The moment something opens,\n"
	.string "you will be the first to know.\p"
	.string "Gladion: …If it shows up\n"
	.string "again, it won't be alone.\p"
	.string "Silvally. We're going.$"
