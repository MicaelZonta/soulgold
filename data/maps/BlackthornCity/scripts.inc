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
@   FLAG_TEMP_2 - the Ultra Beasts: hidden at load on the FIRST attempt, so the
@                 rift is still a surprise; shown again on a retry.
@   FLAG_TEMP_3 - Gladion and Silvally: hidden at load on the first attempt.
@                 Their arrival is the surprise of the scene; nobody mentions
@                 him before. Shown again on a retry, and while the Type: Null
@                 is still undelivered.
@   FLAG_TEMP_4 - Necrozma: shown only while the incident is active. It has
@                 its own flag because the scene removes it on its own.
@   FLAG_TEMP_5 - the player's own Cosmog-family Pokemon as an actor (four
@                 templates on the same tile, at most one of them ever added).
@   FLAG_TEMP_6 - the rift itself. Open from the moment Necrozma tears it until
@                 it closes behind him, so a retry finds it still open.
@   FLAG_TEMP_7 - the Type: Null of the gift.
@
@ Three shapes of street, in the order they are tested:
@   1. gift pending (city already saved): only Gladion and Silvally, parked on
@      their combat tiles, waiting to hand the Pokemon over.
@   2. incident active + FLAG_BLACKTHORN_UB_ENGAGED: a retry after a blackout.
@      Everything the player already saw is back on the street, in the tiles it
@      held when the battle started.
@   3. incident active, first attempt: Clair's line only.
BlackthornCity_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	goto_if_set FLAG_BLACKTHORN_TYPE_NULL_PENDING, BlackthornCity_EventScript_StageGiftPending
	goto_if_unset FLAG_EVENT_ULTRABEAST_BLACKTHORN, BlackthornCity_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_4
	goto_if_set FLAG_BLACKTHORN_UB_ENGAGED, BlackthornCity_EventScript_StageUBRetry
	return

BlackthornCity_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_4
	return

@ Retry after a blackout. setobjectxyperm and not setobjectxy: the templates are
@ reloaded from the map header on every map load, so this is re-applied each time
@ and never leaks into the next visit. It runs from ON_TRANSITION, before the
@ first spawn, which is the only moment a template move is free.
@ Tiles are the ones the scene left them on: the beasts knocked back to x=17,
@ Silvally between them and the player, Gladion right above the player's spot.
BlackthornCity_EventScript_StageUBRetry::
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_6
	setobjectxyperm LOCALID_BLACKTHORN_UB_BUZZWOLE, 17, 50
	setobjectxyperm LOCALID_BLACKTHORN_UB_PHEROMOSA, 17, 51
	setobjectxyperm LOCALID_BLACKTHORN_UB_SILVALLY, 19, 50
	setobjectxyperm LOCALID_BLACKTHORN_UB_GLADION, 20, 49
	return

@ The city is saved and repopulated; only the gift is still open. Gladion and
@ Silvally keep the tiles they held at the end of the scene, and talking to him
@ is the whole of what is left (BlackthornCity_EventScript_UBGladion).
BlackthornCity_EventScript_StageGiftPending::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_4
	clearflag FLAG_TEMP_3
	setobjectxyperm LOCALID_BLACKTHORN_UB_SILVALLY, 19, 50
	setobjectxyperm LOCALID_BLACKTHORN_UB_GLADION, 20, 49
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
@ Story (script revision V2): Clair and Kingdra are already pushing Necrozma
@ away from the houses when the player arrives. Her attack lands - it just
@ does not settle anything. Necrozma tears a rift open beside itself; Buzzwole
@ and Pheromosa come through and come at the player from two different lines;
@ Silvally cuts the first off and Gladion arrives behind it. Gladion names
@ Necrozma out loud - what he cannot explain is what it does next. After the
@ battle Anabel's containment Ball is thrown back by the rift, and Necrozma
@ takes BOTH beasts into itself and leaves. Gladion then gives the player a
@ second Type: Null, one he found alone past Route 45.
@
@ Scene floor plan (raw collision, bit 11; '#' = blocked; y grows DOWNWARD):
@
@        x= 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
@   y=44     .  .  .  .  .  .  s  g  .  .  .  .  .  .  .   s/g Silvally/Gladion
@   y=45     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #       spawn (hidden)
@   y=46     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
@   y=47     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
@   y=48     .  #  #  W  #  .  v  |  .  .  .  .  #  #  W   W (16,48) Mart, (27,48) Center
@   y=49     #  .  .  .  K  C  n  G  .  .  .  .  .  .  f   f (27,49) Fly landing
@   y=50     r  N  B  >  >  b  S  *  .  .  .  .  .  .  .   * (20,50) player's spot
@   y=51     .  R  P  >  >  p  c  .  .  .  .  .  .  .  .
@   y=52     .  .  #  .  .  #  #  .  .  .  #  #  t  a  .   t (25,52) talk to Looker
@   y=53     #  #  #  #  #  #  #  .  .  .  #  #  L  A  #   a (26,52) talk to Anabel
@
@   L Looker (25,53)      A Anabel (26,53)
@   C Clair (18,49)       K Kingdra (17,49)       N Necrozma (14,50)
@   r (13,50) Necrozma's one-tile recoil from Kingdra's Dragon Pulse
@   R (14,51) the rift, added when Necrozma tears it and removed when it closes
@   B Buzzwole (15,50)    P Pheromosa (15,51)     - hidden until the rift
@   b/p where the charge stops: (18,50)/(18,51); recoil to (17,50)/(17,51)
@   g Gladion (20,44) -> down column 20 -> G (20,49)
@   s Silvally (19,44) -> down column 19 to (19,48) -> jump_2 -> S (19,50)
@   c (19,51) the player's own Cosmog-family Pokemon, beside Silvally's cover
@   n (19,49) the Type: Null of the gift, after Silvally steps aside to (18,50)
@
@ Looker sits in a pocket: (24,53) and (25,54) are wall and (26,53) is Anabel.
@ The ONLY tile he can be talked to from is (25,52), facing down. That is what
@ makes the start of the cutscene deterministic without a getplayerxy check.
@ Gladion/Silvally spawn at y=44, six rows above the player: off screen.
@
@ Persistent state (both in the CUSTOM block, both cleared by this mission):
@   FLAG_BLACKTHORN_UB_ENGAGED         the rift is already open and Gladion is
@                                      already here. Survives a blackout, which
@                                      is the whole point: it is what turns the
@                                      second attempt into a retry instead of a
@                                      replay of the introductions.
@   FLAG_BLACKTHORN_TYPE_NULL_PENDING  the city is saved but Gladion still has
@                                      the Type: Null. Unreachable in practice
@                                      (space is checked before the YES and the
@                                      battle blocks catching) and handled
@                                      anyway, because a lost gift is worse
@                                      than a replayed one.
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1 - street cast visibility cache (see ApplyUBVisibility above)
@   FLAG_TEMP_2 - Ultra Beast visibility cache
@   FLAG_TEMP_3 - Gladion + Silvally visibility cache
@   FLAG_TEMP_4 - Necrozma visibility cache
@   FLAG_TEMP_5 - the player's Cosmog-family actor (four templates, one flag:
@                 at most one is ever added, and removeobject hides all four)
@   FLAG_TEMP_6 - the rift
@   FLAG_TEMP_7 - the Type: Null of the gift
@   VAR_TEMP_2  - battle outcome
@   VAR_TEMP_3  - the player's pick: 0 = Buzzwole, 1 = Pheromosa. Survives the
@                 battle because returning from a battle does not reload the
@                 map (ClearTempFieldEventData only runs on warp/edge loads).
@   VAR_TEMP_4  - Cosmog-family species Necrozma reacted to (SPECIES_NONE =
@                 no reaction). Read again by the aftermath dialogue.
@ Object budget at the peak of the scene: player + follower + Looker, Anabel,
@ Clair, Kingdra, Necrozma, the rift, Buzzwole, Pheromosa, Gladion, Silvally
@ = 12/16. The partner only comes out after both beasts are gone (11), and the
@ Type: Null only after Necrozma and the rift are gone (9). Light sprites cost
@ nothing (see NEWBARK_ULTRABEAST_IMPLEMENTATION.md section 12.8).
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

@ Descriptive only, and no species name box: to everyone in Johto this is still
@ a thing nobody has seen. It is Gladion, mid-scene, who names it.
BlackthornCity_EventScript_UBNecrozma::
	lock
	msgbox BlackthornCity_Text_UBNecrozmaIdle, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

@ Gladion is only reachable in the two states where he stands still on the
@ street: a retry, and a pending gift. No faceplayer on the retry branch - he
@ is watching the beasts, like Clair.
BlackthornCity_EventScript_UBGladion::
	lock
	goto_if_set FLAG_BLACKTHORN_TYPE_NULL_PENDING, BlackthornCity_EventScript_UBGiftRetry
	msgbox BlackthornCity_Text_UBGladionRetryIdle, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBReleaseEnd::
	closemessage
	release
	end

@ Nothing changes state before the YES. The YES is the last exit point:
@ from there on everything is scripted through to a battle outcome.
@ Gladion gives a Type: Null at the end, so party AND PC full blocks the YES
@ (skill entregar-pokemon-ou-ovo): checked here, before any offer, silently
@ when there is room, and the player simply comes back after making space.
@ The check is on both paths, first attempt and retry: the gift is at the end
@ of both.
BlackthornCity_EventScript_UBLooker::
	lock
	faceplayer
	goto_if_set FLAG_BLACKTHORN_UB_ENGAGED, BlackthornCity_EventScript_UBLookerRetry
	msgbox BlackthornCity_Text_UBLookerGreet, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBLookerRoom

BlackthornCity_EventScript_UBLookerRetry::
	msgbox BlackthornCity_Text_UBRetryGreeting, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBLookerRoom

BlackthornCity_EventScript_UBLookerRoom::
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, BlackthornCity_EventScript_UBLookerAsk
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_EventScript_UBLookerAsk
	msgbox BlackthornCity_Text_UBNoRoom, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBLookerAsk::
	goto_if_set FLAG_BLACKTHORN_UB_ENGAGED, BlackthornCity_EventScript_UBLookerAskRetry
	msgbox BlackthornCity_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBNotReady
	goto BlackthornCity_EventScript_UBScene

BlackthornCity_EventScript_UBLookerAskRetry::
	msgbox BlackthornCity_Text_UBRetryReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBRetryNotReady
	goto BlackthornCity_EventScript_UBSceneRetry

BlackthornCity_EventScript_UBNotReady::
	msgbox BlackthornCity_Text_UBNotReady, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBRetryNotReady::
	msgbox BlackthornCity_Text_UBRetryNotReady, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

@ ---------------------------------------------------------------------------
@ The scene, first attempt. 100% scripted from the YES to a battle outcome.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	call BlackthornCity_EventScript_UBFormUp
	@ Player (20,50) is east of Clair (18,49): dx=+2 dominates -> DIR_EAST.
	turnobject LOCALID_BLACKTHORN_UB_CLAIR, DIR_EAST
	msgbox BlackthornCity_Text_UBClairArrive, MSGBOX_DEFAULT
	closemessage
	@ Back to the threat BEFORE she gives the order.
	turnobject LOCALID_BLACKTHORN_UB_CLAIR, DIR_WEST
	msgbox BlackthornCity_Text_UBClairAttack, MSGBOX_DEFAULT
	closemessage
	@ Kingdra attacks in place, still facing west at Necrozma (14,50). The hit
	@ lands: Necrozma is pushed one tile west to (13,50), light runs across it,
	@ and it comes back. Clair can hold it. She cannot finish it.
	applymovement LOCALID_BLACKTHORN_UB_KINGDRA, BlackthornCity_Movement_AttackInPlaceLeft
	playmoncry SPECIES_KINGDRA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_BLACKTHORN_UB_KINGDRA
	waitmoncry
	call BlackthornCity_EventScript_UBFlash
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_NecrozmaPushedBack
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_PulseInPlaceRight
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_NecrozmaReturns
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	msgbox BlackthornCity_Text_UBClairHeld, MSGBOX_DEFAULT
	closemessage
	@ The threat theme starts BEFORE the beasts are shown, on Anabel's warning.
	fadeoutbgm 4
	msgbox BlackthornCity_Text_UBRiftWarning, MSGBOX_DEFAULT
	closemessage
	@ Necrozma tears the rift at (14,51), beside itself.
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_PulseInPlaceRight
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	waitmoncry
	call BlackthornCity_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_6
	addobject LOCALID_BLACKTHORN_UB_RIFT
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_IN
	waitse
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	@ Two silhouettes, one cry each, and time to read them.
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_BLACKTHORN_UB_BUZZWOLE
	addobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox BlackthornCity_Text_UBAppear, MSGBOX_DEFAULT
	closemessage
	@ Two different ways of coming at the player, on purpose: Blackthorn never
	@ suggests the beasts are one mind. Buzzwole walks the line straight down
	@ row 50 (15->18); Pheromosa hesitates, feints sideways and then outruns
	@ it along row 51. Offset rows, so they never contend for a tile, and
	@ (19,50) stays free for Silvally.
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, BlackthornCity_Movement_BuzzwoleCharge
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, BlackthornCity_Movement_PheromosaCharge
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	msgbox BlackthornCity_Text_UBChargeWarning, MSGBOX_DEFAULT
	closemessage
	@ The player follows Pheromosa, which is the one that got around the side.
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement OBJ_EVENT_ID_PLAYER
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
	waitmoncry
	@ Front first: Buzzwole is driven back (18,50)->(17,50), still facing east.
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyStrikeLeft
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	call BlackthornCity_EventScript_UBShake
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, BlackthornCity_Movement_UBKnockedBack
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	@ Then the flank: Pheromosa loses the opening and gives ground as well.
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyStrikeDown
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, BlackthornCity_Movement_UBKnockedBack
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	waitmovement LOCALID_BLACKTHORN_UB_GLADION
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, Common_Movement_FaceLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox BlackthornCity_Text_UBGladionArrives, MSGBOX_DEFAULT
	closemessage
	@ Gladion is at (20,49), directly above the player: DIR_NORTH.
	applymovement OBJ_EVENT_ID_PLAYER, BlackthornCity_Movement_PlayerNods
	waitmovement OBJ_EVENT_ID_PLAYER
	@ He sees Necrozma over the line of the beasts and says what it is. No
	@ withheld name: the mystery is what it is doing in Johto.
	applymovement LOCALID_BLACKTHORN_UB_GLADION, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_GLADION
	msgbox BlackthornCity_Text_UBNecrozmaNamed, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAnabelFocus, MSGBOX_DEFAULT
	closemessage
	@ Checkpoint. Everything above is an introduction and is never played
	@ twice: from here a blackout comes back to UBSceneRetry.
	setflag FLAG_BLACKTHORN_UB_ENGAGED
	goto BlackthornCity_EventScript_UBChoose

@ ---------------------------------------------------------------------------
@ The scene, retry after a blackout (or after any non-victory outcome).
@ ApplyUBVisibility has already put the beasts, Silvally and Gladion back on
@ their combat tiles, so all that is left is to walk the player back into the
@ line and hand the choice over again. Nobody re-introduces anybody.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBSceneRetry::
	closemessage
	lockall
	hidefollower
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	call BlackthornCity_EventScript_UBFormUp
	turnobject LOCALID_BLACKTHORN_UB_SILVALLY, DIR_WEST
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_WEST
	goto BlackthornCity_EventScript_UBChoose

@ Shared opening of both paths: the player walks up the street and the two
@ detectives step out of their pocket behind him.
@ Player (25,52)->(25,51)->(25,50)->(24,50)->(23,50)->(22,50)->(21,50)
@ ->(20,50), then faces west. Every tile checked free; Clair and Kingdra
@ are on row 49 at x=17..18, nobody is on row 50 east of x=15.
@ Looker (25,53)->(25,52) and Anabel (26,53)->(26,52): same one-step
@ sequence in different columns, so they never contend for a tile and
@ can walk together. Both end facing west, toward the player at (20,50).
BlackthornCity_EventScript_UBFormUp::
	applymovement OBJ_EVENT_ID_PLAYER, BlackthornCity_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_StepUpFaceLeft
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_StepUpFaceLeft
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	return

@ Flash da cena. fadescreenswapbuffers e NAO fadescreen: fadescreen copia
@ gPlttBufferFaded -> gPlttBufferUnfaded ao escurecer (src/field_weather.c,
@ FadeScreen) e o FADE_FROM_* seguinte reaplica o tint de horario por cima do
@ que ja estava tintado. A noite (coeff 10) cada par de flashes multiplicava a
@ cena por ~0,46 de novo, e depois de tres ou quatro a cidade ficava preta.
@ fadescreenswapbuffers usa BLDY no hardware e nao encosta nas paletas.
BlackthornCity_EventScript_UBFlash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

BlackthornCity_EventScript_UBShake::
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 12  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	return

@ The rift answering something: a short tremor with no flash, so it reads as
@ the tear itself moving and not as another hit.
BlackthornCity_EventScript_UBRiftPulse::
	setvar VAR_0x8004, 0  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 6  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
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
	msgbox BlackthornCity_Text_UBClairCover, MSGBOX_DEFAULT
	closemessage
	@ Gladion's prompt is the LAST box before the menu on purpose: the plaque
	@ over the choice has to be his, because he is the one asking.
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
@ scale still climbs. Script revision V2 changes no number here.
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

@ Interrupted, not lost: the beasts are still standing in the street, so
@ nobody says they got away. Nothing was recorded as done - the event flag is
@ still set and FLAG_BLACKTHORN_UB_ENGAGED still marks the rift as open, so
@ the reload puts the whole line back where it was and Looker offers the
@ retry.
BlackthornCity_EventScript_UBUnresolved::
	msgbox BlackthornCity_Text_UBUnresolved, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_BLACKTHORN_CITY, 27, 49
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ Act VI - what the victory reveals.
@ Gladion's fight against the other beast is narrative: it resolves with the
@ player's win and only his line afterwards changes with the pick.
@ Then the two things nobody expected: the containment Ball is thrown back by
@ the rift, and Necrozma takes BOTH beasts into itself.
@ Positions at this point (a battle does not reload the map): Buzzwole
@ (17,50), Pheromosa (17,51), Necrozma (14,50), the rift (14,51).
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBResolved::
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBGladionFoughtBuzzwole
	msgbox BlackthornCity_Text_UBGladionFoughtPheromosa, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBContain

BlackthornCity_EventScript_UBGladionFoughtBuzzwole::
	msgbox BlackthornCity_Text_UBGladionFoughtBuzzwole, MSGBOX_DEFAULT

@ Anabel steps up to (26,51) and throws a containment Ball of her own at the
@ beast the PLAYER put down. It is her equipment: nothing leaves the player's
@ bag, and no capture battle happens. A filament of the rift still reaches the
@ beast, and the Ball comes back intact. This is the observation Mahogany
@ will act on.
BlackthornCity_EventScript_UBContain::
	closemessage
	@ (26,52)->(26,51), still facing west: the same one-step movement she used
	@ to come out of the pocket.
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_StepUpFaceLeft
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	msgbox BlackthornCity_Text_UBContainment, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACKTHORN_UB_ANABEL, BlackthornCity_Movement_AnabelThrows
	playse SE_BALL_THROW
	waitmovement LOCALID_BLACKTHORN_UB_ANABEL
	waitse
	call BlackthornCity_EventScript_UBTargetStartles
	@ The link answers before the Ball can close: a barrier sound, the tear
	@ pulsing, and the Ball bouncing off intact. No capture fanfare, and
	@ nothing is consumed.
	playse SE_M_REFLECT
	waitse
	call BlackthornCity_EventScript_UBRiftPulse
	playse SE_BALL_BOUNCE_1
	waitse
	msgbox BlackthornCity_Text_UBContainmentFailed, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBAbsorb

@ The Ball goes at whichever beast the player beat - the other one is
@ Gladion's and is already down.
BlackthornCity_EventScript_UBTargetStartles::
	goto_if_eq VAR_TEMP_3, 1, BlackthornCity_EventScript_UBTargetPheromosa
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	return

BlackthornCity_EventScript_UBTargetPheromosa::
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, Common_Movement_ExclamationMark
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	return

@ The absorption. Clair and Gladion both try to cut the light - the group is
@ not standing still watching - and both are too late.
BlackthornCity_EventScript_UBAbsorb::
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_PulseInPlaceRight
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	waitmoncry
	msgbox BlackthornCity_Text_UBAbsorbedClair, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACKTHORN_UB_KINGDRA, BlackthornCity_Movement_AttackInPlaceLeft
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyStrikeLeft
	waitmovement LOCALID_BLACKTHORN_UB_KINGDRA
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	@ Dragged backwards, still facing east, to the tiles next to Necrozma:
	@ (17,50)->(15,50) and (17,51)->(15,51). Same sequence, offset rows.
	@ A short push against the drag first: they are being taken, not going.
	applymovement LOCALID_BLACKTHORN_UB_BUZZWOLE, BlackthornCity_Movement_UBPulledIn
	applymovement LOCALID_BLACKTHORN_UB_PHEROMOSA, BlackthornCity_Movement_UBPulledIn
	waitmovement LOCALID_BLACKTHORN_UB_BUZZWOLE
	waitmovement LOCALID_BLACKTHORN_UB_PHEROMOSA
	call BlackthornCity_EventScript_UBShake
	@ Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_BUZZWOLE
	removeobject LOCALID_BLACKTHORN_UB_PHEROMOSA
	fadescreenswapbuffers FADE_FROM_WHITE
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
	@ It gets brighter. And then, obligatorily and in every branch, the light
	@ wavers again and the edge of the tear shakes: taking them did not make
	@ the signal steady. That is the problem the whole arc is about, and it is
	@ planted here even for a player with nothing special in the party.
	call BlackthornCity_EventScript_UBFlash
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_PulseInPlaceRight
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	call BlackthornCity_EventScript_UBRiftPulse
	playse SE_WARP_IN
	waitse
	msgbox BlackthornCity_Text_UBAbsorbedGladion, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAbsorbedAnabel, MSGBOX_DEFAULT
	closemessage
	call BlackthornCity_EventScript_UBPartnerReacts
	@ Necrozma leaves the way it came and the tear closes behind it. Own
	@ flags (FLAG_TEMP_4, FLAG_TEMP_6): removeobject touches nobody else.
	call BlackthornCity_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_NECROZMA
	removeobject LOCALID_BLACKTHORN_UB_RIFT
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_OUT
	waitse
	msgbox BlackthornCity_Text_UBNecrozmaGone, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBStreetClear, MSGBOX_DEFAULT
	closemessage
	@ Only now does the threat theme end.
	fadedefaultbgm
	call BlackthornCity_EventScript_UBPartnerRecalled
	goto BlackthornCity_EventScript_UBAftermath

@ ---------------------------------------------------------------------------
@ Optional reaction to a Cosmog-family Pokemon in the party (non-egg; the
@ special is the one Elm's Eviolite scene uses). Checked AFTER the battle on
@ purpose: the battle can evolve it.
@ The Pokemon is SHOWN, at (19,51), before anything is said about it - one
@ actor per stage, four templates on the same tile sharing FLAG_TEMP_5, and
@ at most one of them is ever added. The follower is hidden for the whole
@ scene, so nothing is duplicated.
@ (19,51) is beside Silvally's cover, not in front of it.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBPartnerReacts::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, BlackthornCity_EventScript_UBReturn
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	clearflag FLAG_TEMP_5
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	call BlackthornCity_EventScript_UBAddPartner
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
	waitmoncry
	@ (14,50)->(15,50), free since Buzzwole was removed.
	applymovement LOCALID_BLACKTHORN_UB_NECROZMA, BlackthornCity_Movement_NecrozmaLean
	waitmovement LOCALID_BLACKTHORN_UB_NECROZMA
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, BlackthornCity_EventScript_UBPartnerLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, BlackthornCity_EventScript_UBPartnerLegend
	@ Cosmog / Cosmoem: it is noticed, and it shrinks back where it stands.
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox BlackthornCity_Text_UBNecrozmaSensesCosmog, MSGBOX_DEFAULT
	closemessage
	call BlackthornCity_EventScript_UBPartnerShrinks
	call BlackthornCity_EventScript_UBRiftPulse
	return

@ Solgaleo / Lunala: the tear steadies for a moment, and then goes back to
@ wavering. It does not solve anything in this mission.
BlackthornCity_EventScript_UBPartnerLegend::
	msgbox BlackthornCity_Text_UBNecrozmaSensesLegend, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBLegendCover, MSGBOX_DEFAULT
	closemessage
	call BlackthornCity_EventScript_UBRiftPulse
	return

@ If both are somehow in the party, CheckMysteryEggPokemon returns the first
@ one in party order, so the species, the cry and the actor all agree and
@ none of them changes in the middle of the scene.
BlackthornCity_EventScript_UBAddPartner::
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, BlackthornCity_EventScript_UBAddCosmoem
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, BlackthornCity_EventScript_UBAddSolgaleo
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, BlackthornCity_EventScript_UBAddLunala
	addobject LOCALID_BLACKTHORN_UB_COSMOG
	return
BlackthornCity_EventScript_UBAddCosmoem::
	addobject LOCALID_BLACKTHORN_UB_COSMOEM
	return
BlackthornCity_EventScript_UBAddSolgaleo::
	addobject LOCALID_BLACKTHORN_UB_SOLGALEO
	return
BlackthornCity_EventScript_UBAddLunala::
	addobject LOCALID_BLACKTHORN_UB_LUNALA
	return

@ Cosmoem only floats, so both stages get the same in-place recoil and no
@ walking: the movement has to be true of the sprite that is on screen.
BlackthornCity_EventScript_UBPartnerShrinks::
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, BlackthornCity_EventScript_UBPartnerShrinksCosmoem
	applymovement LOCALID_BLACKTHORN_UB_COSMOG, BlackthornCity_Movement_PartnerShrinks
	waitmovement LOCALID_BLACKTHORN_UB_COSMOG
	return
BlackthornCity_EventScript_UBPartnerShrinksCosmoem::
	applymovement LOCALID_BLACKTHORN_UB_COSMOEM, BlackthornCity_Movement_PartnerShrinks
	waitmovement LOCALID_BLACKTHORN_UB_COSMOEM
	return

@ The player calls it back, on screen, before anybody walks over and before
@ the gift: (19,51) has to be empty and the Type: Null must be the only
@ Pokemon of the player's in the scene.
BlackthornCity_EventScript_UBPartnerRecalled::
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, BlackthornCity_EventScript_UBReturn
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_COSMOG
	removeobject LOCALID_BLACKTHORN_UB_COSMOEM
	removeobject LOCALID_BLACKTHORN_UB_SOLGALEO
	removeobject LOCALID_BLACKTHORN_UB_LUNALA
	fadescreenswapbuffers FADE_FROM_WHITE
	return

BlackthornCity_EventScript_UBReturn::
	return

@ ---------------------------------------------------------------------------
@ Act VII - people, evidence, next step.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBAftermath::
	@ Looker (25,52)->(25,51)->(25,50)->(24,50)->(23,50)->(22,50)->(21,50),
	@ faces west at the player in (20,50).
	applymovement LOCALID_BLACKTHORN_UB_LOOKER, BlackthornCity_Movement_LookerToPlayer
	waitmovement LOCALID_BLACKTHORN_UB_LOOKER
	@ Anabel is on (26,51), not (26,52): she stepped up to throw the Ball.
	@ Her path is four tiles straight west along row 51, to (22,51).
	@ SEQUENTIAL on purpose: it crosses (25,51), which Looker occupies on his
	@ first step, so the two must never walk together here.
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
	@ People before the report.
	msgbox BlackthornCity_Text_UBAftermathLooker, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathClair, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathGladion, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathClairReturn, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_BLACKTHORN_UB_CLAIR, DIR_WEST
	turnobject LOCALID_BLACKTHORN_UB_KINGDRA, DIR_WEST
	@ What Gladion knows, given plainly and now. Anabel looks at him, he turns
	@ east to answer, the player follows the exchange.
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_EAST
	msgbox BlackthornCity_Text_UBAftermathQuestion, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathNecrozma, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathInference, MSGBOX_DEFAULT
	closemessage
	@ The bridge to Mahogany: the link is what has to be broken next. Anabel
	@ does not know where, or how, yet.
	msgbox BlackthornCity_Text_UBAftermathPlan, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathLookerPlan, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBAftermathGladionAgrees, MSGBOX_DEFAULT
	closemessage
	@ Only the branch that actually happened comes back, and only as a memory
	@ of what everyone saw.
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, BlackthornCity_EventScript_UBGift
	@ Rebuilt, not trusted: STR_VAR_1 is a shared buffer and the gift below
	@ writes over it. The species itself lives in VAR_TEMP_4.
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, BlackthornCity_EventScript_UBAftermathLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, BlackthornCity_EventScript_UBAftermathLegend
	msgbox BlackthornCity_Text_UBAftermathCosmog, MSGBOX_DEFAULT
	closemessage
	goto BlackthornCity_EventScript_UBGift

BlackthornCity_EventScript_UBAftermathLegend::
	msgbox BlackthornCity_Text_UBAftermathLegend, MSGBOX_DEFAULT
	closemessage

@ ---------------------------------------------------------------------------
@ Act VIII - Type: Null. A SECOND one, not Silvally: Gladion releases it while
@ Silvally is still on screen, one tile away, so the two can be seen together
@ and nobody has to be told they are different individuals.
@ Silvally gives up (19,50) for it and steps to (18,50), free since the
@ beasts were taken.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBGift::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox BlackthornCity_Text_UBGladionGiftIntro, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyStepsAside
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_7
	addobject LOCALID_BLACKTHORN_UB_TYPENULL
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_TYPE_NULL, CRY_MODE_NORMAL
	waitmoncry
	msgbox BlackthornCity_Text_UBGladionGiftFound, MSGBOX_DEFAULT
	closemessage
	@ Its own idea: (19,49)->(19,50), then it turns to the player at (20,50).
	@ Gladion gives no order.
	applymovement LOCALID_BLACKTHORN_UB_TYPENULL, BlackthornCity_Movement_TypeNullApproaches
	waitmovement LOCALID_BLACKTHORN_UB_TYPENULL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_TYPE_NULL, CRY_MODE_NORMAL
	waitmoncry
	msgbox BlackthornCity_Text_UBGladionGiftTrust, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox BlackthornCity_Text_UBGladionGiftOffer, MSGBOX_DEFAULT
	closemessage
	@ Delivery first, actor second: the Type: Null on the street is only put
	@ away once the system has actually accepted it. Space was checked before
	@ the YES and nothing since can fill the party or the PC (the battle
	@ blocks catching), so MON_CANT_GIVE is unreachable - and it is still
	@ guarded, because a gift that silently disappears is the worst outcome
	@ there is.
	bufferspeciesname STR_VAR_1, SPECIES_TYPE_NULL
	givemon SPECIES_TYPE_NULL, 50
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BlackthornCity_EventScript_UBGiftNoRoom
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_TYPENULL
	fadescreenswapbuffers FADE_FROM_WHITE
	call Common_EventScript_GiftMon
	msgbox BlackthornCity_Text_UBGladionGiftAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyBackToGladion
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	goto BlackthornCity_EventScript_UBHook

@ The guard. It does NOT replay the battle and it does NOT erase the victory:
@ the city is saved either way. Only the gift stays open, on its own flag, and
@ Gladion stays on the street to finish it.
BlackthornCity_EventScript_UBGiftNoRoom::
	setflag FLAG_BLACKTHORN_TYPE_NULL_PENDING
	msgbox BlackthornCity_Text_UBGiftNoRoom, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_BLACKTHORN_UB_TYPENULL
	fadescreenswapbuffers FADE_FROM_WHITE
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyBackToGladion
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	goto BlackthornCity_EventScript_UBHook

@ ---------------------------------------------------------------------------
@ Act IX - the hook. No destination: the next briefing in Olivine reveals it.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBHook::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox BlackthornCity_Text_UBHookAnabel, MSGBOX_DEFAULT
	closemessage
	msgbox BlackthornCity_Text_UBHookLooker, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_SOUTH
	msgbox BlackthornCity_Text_UBHookGladion, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_BLACKTHORN_UB_GLADION, DIR_NORTH
	turnobject LOCALID_BLACKTHORN_UB_SILVALLY, DIR_NORTH
	delay 30
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_BLACKTHORN    @ invariant: flag and var together
	setvar VAR_RIFT_MISSIONS_STATE, 4
	clearflag FLAG_BLACKTHORN_UB_ENGAGED          @ the incident is over
	setflag FLAG_DAILY_LOOKER_CALL                @ he just said it in person
	@ Reload in place under the fade. With the flag cleared the residents
	@ would otherwise pop in one by one as the camera moved, and the cast
	@ would linger; ON_TRANSITION repopulates the city and hides the cast
	@ in one go. Gladion and Silvally leave together, as they must. The
	@ doors unlock with the flag. If the gift is still pending, the same
	@ ON_TRANSITION is what keeps exactly those two on the street.
	warpsilent MAP_BLACKTHORN_CITY, 20, 50
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ The pending gift. Reached only from Gladion's object script, and only while
@ FLAG_BLACKTHORN_TYPE_NULL_PENDING is set. It finishes the delivery and
@ nothing else: no rift, no battle, no report.
@ ---------------------------------------------------------------------------
BlackthornCity_EventScript_UBGiftRetry::
	faceplayer
	msgbox BlackthornCity_Text_UBGiftRetry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BlackthornCity_EventScript_UBReleaseEnd
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, BlackthornCity_EventScript_UBGiftRetryGive
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, BlackthornCity_EventScript_UBGiftRetryGive
	msgbox BlackthornCity_Text_UBGiftNoRoom, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

BlackthornCity_EventScript_UBGiftRetryGive::
	bufferspeciesname STR_VAR_1, SPECIES_TYPE_NULL
	givemon SPECIES_TYPE_NULL, 50
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, BlackthornCity_EventScript_UBGiftRetryFailed
	call Common_EventScript_GiftMon
	msgbox BlackthornCity_Text_UBGladionGiftAfter, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_BLACKTHORN_TYPE_NULL_PENDING
	@ Now they can go. On foot, north, up the two columns they came down -
	@ every tile of both is free (see the floor plan).
	msgbox BlackthornCity_Text_UBHookGladion, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BLACKTHORN_UB_SILVALLY, BlackthornCity_Movement_SilvallyLeaves
	applymovement LOCALID_BLACKTHORN_UB_GLADION, BlackthornCity_Movement_GladionLeaves
	waitmovement LOCALID_BLACKTHORN_UB_SILVALLY
	waitmovement LOCALID_BLACKTHORN_UB_GLADION
	removeobject LOCALID_BLACKTHORN_UB_SILVALLY
	removeobject LOCALID_BLACKTHORN_UB_GLADION
	release
	end

@ Unreachable: the space was just checked. Kept so that a failed give can
@ never clear the pending flag.
BlackthornCity_EventScript_UBGiftRetryFailed::
	msgbox BlackthornCity_Text_UBGiftNoRoom, MSGBOX_DEFAULT
	goto BlackthornCity_EventScript_UBReleaseEnd

@ ---------------------------------------------------------------------------
@ Movements
@ ---------------------------------------------------------------------------
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

@ Dragon Pulse lands: one tile west, eyes never leaving Clair.
BlackthornCity_Movement_NecrozmaPushedBack:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

BlackthornCity_Movement_NecrozmaReturns:
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	step_end

@ Buzzwole: three heavy steps down row 50, no hesitation.
BlackthornCity_Movement_BuzzwoleCharge:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

@ Pheromosa: a beat, a feint to the side, and then it is faster than Buzzwole
@ over the same three tiles of row 51.
BlackthornCity_Movement_PheromosaCharge:
	delay_16
	walk_in_place_fast_down
	walk_faster_right
	walk_faster_right
	walk_faster_right
	face_right
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

BlackthornCity_Movement_SilvallyStrikeLeft:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

BlackthornCity_Movement_SilvallyStrikeDown:
	face_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

BlackthornCity_Movement_UBKnockedBack:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	step_end

BlackthornCity_Movement_PlayerNods:
	face_up
	walk_in_place_up
	walk_in_place_up
	face_left
	step_end

BlackthornCity_Movement_AnabelThrows:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

@ Taken, not going: one step against the pull first, then dragged two tiles.
BlackthornCity_Movement_UBPulledIn:
	lock_facing_direction
	walk_in_place_fast_right
	walk_slow_left
	walk_slow_left
	unlock_facing_direction
	step_end

BlackthornCity_Movement_NecrozmaLean:
	walk_slow_right
	step_end

@ Cosmog floats and Cosmoem does not walk at all, so this never leaves the
@ tile: it is a flinch in place.
BlackthornCity_Movement_PartnerShrinks:
	lock_facing_direction
	walk_in_place_fast_left
	walk_in_place_fast_left
	unlock_facing_direction
	step_end

BlackthornCity_Movement_SilvallyStepsAside:
	walk_left
	face_right
	step_end

BlackthornCity_Movement_SilvallyBackToGladion:
	walk_right
	face_left
	step_end

BlackthornCity_Movement_TypeNullApproaches:
	walk_down
	face_right
	step_end

BlackthornCity_Movement_SilvallyLeaves:
	walk_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BlackthornCity_Movement_GladionLeaves:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
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

@ From (26,51), where the containment attempt left her: four tiles west.
BlackthornCity_Movement_AnabelToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

@ ---------------------------------------------------------------------------
@ Texts (script revision V2, 25/09/2026).
@ Voices (design section 3.1): Clair proud and objective, responsible for her
@ town, and she recognises the Champion; Gladion few words and concrete
@ instructions, care shown through Silvally; Anabel separates what she saw
@ from what she thinks it means; Looker warm when he greets and short when
@ there is danger.
@ Necrozma IS named here, by Gladion, mid-scene. What nobody can explain is
@ what it is doing in Johto and why it takes other creatures. Nobody says
@ where the next rift will open, and nobody claims the beasts are dead or
@ alive.
@ NARRATOR / NOTE / SYSTEM lines are messages of their own with no
@ {SPEAKER ...} code: the plaque never carries over between messages.
@ ---------------------------------------------------------------------------
BlackthornCity_Text_DoorLocked:
	.string "Stay inside until the street\n"
	.string "is clear.\p"
	.string "--Clair$"

BlackthornCity_Text_UBAnabelIdle:
	.string "{SPEAKER NAME_ANABEL}The residents are\n"
	.string "indoors.\p"
	.string "The Center is still open.\p"
	.string "Speak with Looker when you're\n"
	.string "ready.$"

BlackthornCity_Text_UBClairIdle:
	.string "{SPEAKER NAME_CLAIR}{PLAYER}.\n"
	.string "Stay behind Kingdra.\p"
	.string "Every time it moves toward\n"
	.string "the houses, we push it back.\p"
	.string "The detectives are by the\n"
	.string "Center. Speak to them first.$"

BlackthornCity_Text_UBKingdraIdle:
	.string "Kingdra holds its ground.$"

BlackthornCity_Text_UBNecrozmaIdle:
	.string "Light gathers along the black\n"
	.string "crystal, then fades inside it.$"

BlackthornCity_Text_UBGladionRetryIdle:
	.string "{SPEAKER NAME_GLADION}We've got this side.\p"
	.string "Heal up and tell Looker when\n"
	.string "you're ready.$"

BlackthornCity_Text_UBLookerGreet:
	.string "{SPEAKER NAME_LOOKER}There you are.\p"
	.string "Clair has kept the street\n"
	.string "clear for us.\p"
	.string "We'll move up together.$"

BlackthornCity_Text_UBNoRoom:
	.string "{SPEAKER NAME_LOOKER}Your team and Boxes are\n"
	.string "full.\p"
	.string "Please make room for one\n"
	.string "Pokémon first.$"

BlackthornCity_Text_UBReady:
	.string "{SPEAKER NAME_LOOKER}Are you and your\n"
	.string "Pokémon ready?$"

BlackthornCity_Text_UBNotReady:
	.string "{SPEAKER NAME_LOOKER}The Center is just up\n"
	.string "the street.\p"
	.string "We'll wait here.$"

BlackthornCity_Text_UBClairArrive:
	.string "{SPEAKER NAME_CLAIR}Champion already? Good.\n"
	.string "I could use the help.$"

BlackthornCity_Text_UBClairAttack:
	.string "{SPEAKER NAME_CLAIR}Kingdra! Dragon Pulse!$"

BlackthornCity_Text_UBClairHeld:
	.string "{SPEAKER NAME_CLAIR}It keeps coming back.\p"
	.string "Kingdra, hold there.$"

BlackthornCity_Text_UBRiftWarning:
	.string "{SPEAKER NAME_ANABEL}The distortion is\n"
	.string "growing.\p"
	.string "Everyone, leave room to fall\n"
	.string "back.$"

BlackthornCity_Text_UBAppear:
	.string "{SPEAKER NAME_ANABEL}Buzzwole and Pheromosa.\p"
	.string "Two Ultra Beasts!$"

BlackthornCity_Text_UBChargeWarning:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}, on your left!$"

BlackthornCity_Text_UBGladionArrives:
	.string "{SPEAKER NAME_GLADION}Stay with me, Silvally.\p"
	.string "{PLAYER}. You all right?$"

BlackthornCity_Text_UBNecrozmaNamed:
	.string "{SPEAKER NAME_GLADION}Necrozma.\n"
	.string "What's it doing here?$"

BlackthornCity_Text_UBAnabelFocus:
	.string "{SPEAKER NAME_ANABEL}Keep the Ultra Beasts\n"
	.string "away from the houses.\p"
	.string "We'll deal with Necrozma\n"
	.string "next.$"

BlackthornCity_Text_UBChoosePrompt:
	.string "{SPEAKER NAME_GLADION}Pick one, {PLAYER}.\p"
	.string "Silvally and I will take the\n"
	.string "other.$"

BlackthornCity_Text_UBClairCover:
	.string "{SPEAKER NAME_CLAIR}I'll keep Necrozma back.\n"
	.string "Go!$"

BlackthornCity_Text_ChoiceBuzzwole:
	.string "Buzzwole$"

BlackthornCity_Text_ChoicePheromosa:
	.string "Pheromosa$"

BlackthornCity_Text_UBPickedBuzzwole:
	.string "{SPEAKER NAME_GLADION}Silvally, watch\n"
	.string "Pheromosa.\p"
	.string "Don't let it get around us.$"

BlackthornCity_Text_UBPickedPheromosa:
	.string "{SPEAKER NAME_GLADION}We'll hold Buzzwole\n"
	.string "here.\p"
	.string "Take the opening.$"

BlackthornCity_Text_UBUnresolved:
	.string "{SPEAKER NAME_ANABEL}They're still here.\p"
	.string "Regroup before we try again.$"

BlackthornCity_Text_UBRetryGreeting:
	.string "{SPEAKER NAME_LOOKER}Clair and Gladion are\n"
	.string "holding them back.\p"
	.string "How are your Pokémon?$"

BlackthornCity_Text_UBRetryReady:
	.string "{SPEAKER NAME_ANABEL}Ready to try again?$"

BlackthornCity_Text_UBRetryNotReady:
	.string "{SPEAKER NAME_ANABEL}Heal at the Center\n"
	.string "first.\p"
	.string "We'll hold here.$"

BlackthornCity_Text_UBGladionFoughtPheromosa:
	.string "{SPEAKER NAME_GLADION}Pheromosa's stopped.\p"
	.string "Stay there, Silvally.$"

BlackthornCity_Text_UBGladionFoughtBuzzwole:
	.string "{SPEAKER NAME_GLADION}Buzzwole's down.\p"
	.string "Good work, Silvally.$"

BlackthornCity_Text_UBContainment:
	.string "{SPEAKER NAME_ANABEL}Keep clear.\n"
	.string "I'll try to secure it.$"

BlackthornCity_Text_UBContainmentFailed:
	.string "{SPEAKER NAME_ANABEL}The rift pulled it back.\p"
	.string "It's still connected!$"

BlackthornCity_Text_UBAbsorbedClair:
	.string "{SPEAKER NAME_CLAIR}It's pulling them in!\p"
	.string "Kingdra, break that light!$"

BlackthornCity_Text_UBAbsorbedGladion:
	.string "{SPEAKER NAME_GLADION}It took both of them.\p"
	.string "I've never seen it do that.$"

BlackthornCity_Text_UBAbsorbedAnabel:
	.string "{SPEAKER NAME_ANABEL}The reading spiked…\p"
	.string "Now it's fluctuating again.$"

BlackthornCity_Text_UBNecrozmaSensesCosmog:
	.string "{SPEAKER NAME_GLADION}It noticed your\n"
	.string "{STR_VAR_1}.\p"
	.string "Keep it behind Silvally.$"

BlackthornCity_Text_UBNecrozmaSensesLegend:
	.string "{SPEAKER NAME_ANABEL}The rift steadied when\n"
	.string "{STR_VAR_1} came out.$"

BlackthornCity_Text_UBLegendCover:
	.string "{SPEAKER NAME_GLADION}Easy, Silvally.\p"
	.string "Keep it away from them.$"

BlackthornCity_Text_UBNecrozmaGone:
	.string "{SPEAKER NAME_CLAIR}Hold your positions.\p"
	.string "Make sure it's gone.$"

BlackthornCity_Text_UBStreetClear:
	.string "{SPEAKER NAME_ANABEL}The opening has closed.\p"
	.string "The street is clear.$"

BlackthornCity_Text_UBAftermathLooker:
	.string "{SPEAKER NAME_LOOKER}Everyone all right?\p"
	.string "Take a moment. I'll check the\n"
	.string "houses.$"

BlackthornCity_Text_UBAftermathClair:
	.string "{SPEAKER NAME_CLAIR}You kept them off the\n"
	.string "houses.\p"
	.string "Both of you. Thank you.$"

BlackthornCity_Text_UBAftermathGladion:
	.string "{SPEAKER NAME_GLADION}Gladion.\p"
	.string "We were coming down from\n"
	.string "Route 45.$"

BlackthornCity_Text_UBAftermathClairReturn:
	.string "{SPEAKER NAME_CLAIR}I'll check the rest of\n"
	.string "town, Gladion.\p"
	.string "Kingdra, with me.$"

BlackthornCity_Text_UBAftermathQuestion:
	.string "{SPEAKER NAME_ANABEL}You called it Necrozma.\p"
	.string "What do you know about it?$"

BlackthornCity_Text_UBAftermathNecrozma:
	.string "{SPEAKER NAME_GLADION}It absorbs light. It\n"
	.string "caused trouble in Alola, too.\p"
	.string "Taking Ultra Beasts like\n"
	.string "that? That's new.$"

BlackthornCity_Text_UBAftermathInference:
	.string "{SPEAKER NAME_ANABEL}Then it may be taking\n"
	.string "their energy.\p"
	.string "We don't know what happened\n"
	.string "to them yet.$"

BlackthornCity_Text_UBAftermathPlan:
	.string "{SPEAKER NAME_ANABEL}The rift kept them\n"
	.string "connected.\p"
	.string "Next time, we need to break\n"
	.string "that link.$"

BlackthornCity_Text_UBAftermathLookerPlan:
	.string "{SPEAKER NAME_LOOKER}I'll compare this with\n"
	.string "our Alola records.\p"
	.string "Gladion, may I take your\n"
	.string "account?$"

BlackthornCity_Text_UBAftermathGladionAgrees:
	.string "{SPEAKER NAME_GLADION}Yes.\p"
	.string "I'll tell you what I\n"
	.string "remember.$"

BlackthornCity_Text_UBAftermathCosmog:
	.string "{SPEAKER NAME_ANABEL}Necrozma approached\n"
	.string "when your {STR_VAR_1} appeared.\p"
	.string "If it reacts again, let us\n"
	.string "know.$"

BlackthornCity_Text_UBAftermathLegend:
	.string "{SPEAKER NAME_ANABEL}Your {STR_VAR_1} affected\n"
	.string "the rift.\p"
	.string "Only for a moment, but I\n"
	.string "recorded it.$"

BlackthornCity_Text_UBGladionGiftIntro:
	.string "{SPEAKER NAME_GLADION}Before you go, there's\n"
	.string "a Pokémon I'd like you to\l"
	.string "meet.$"

@ Origin fixed by the V3 audit of the script: this Type: Null was ALREADY in
@ Gladion's care in Alola and came to Johto with him. Route 45 is where the three
@ of them have been training, not where a second abandoned artificial Pokemon
@ turned up by coincidence. Never say it is a new creation, that there are wild
@ ones on the route, or that Gladion abandoned his own partner.
BlackthornCity_Text_UBGladionGiftFound:
	.string "{SPEAKER NAME_GLADION}I brought it with me\n"
	.string "from Alola.\p"
	.string "It needed someone to look\n"
	.string "after it.\p"
	.string "Silvally helped it get used to\n"
	.string "traveling.\p"
	.string "We've been training beyond\n"
	.string "Route 45.$"

BlackthornCity_Text_UBGladionGiftTrust:
	.string "{SPEAKER NAME_GLADION}It usually stays close\n"
	.string "to Silvally.\p"
	.string "Huh. It seems comfortable\n"
	.string "with you.$"

@ The trust rests on the campaign they already share, not on one battle watched
@ from inside a Ball.
BlackthornCity_Text_UBGladionGiftOffer:
	.string "{SPEAKER NAME_GLADION}I've seen how you treat\n"
	.string "your Pokémon.\p"
	.string "I'd trust you to look after\n"
	.string "it.\p"
	.string "Take it with you.$"

BlackthornCity_Text_UBGladionGiftAfter:
	.string "{SPEAKER NAME_GLADION}Give it time.\p"
	.string "Let it come to you.$"

BlackthornCity_Text_UBGiftNoRoom:
	.string "{SPEAKER NAME_GLADION}Your team and Boxes are\n"
	.string "full.\p"
	.string "Make room. I'll keep it with\n"
	.string "me until then.$"

BlackthornCity_Text_UBGiftRetry:
	.string "{SPEAKER NAME_GLADION}Ready to take\n"
	.string "Type: Null with you?$"

BlackthornCity_Text_UBHookAnabel:
	.string "{SPEAKER NAME_ANABEL}The distortion hasn't\n"
	.string "fully cleared.\p"
	.string "We'll keep monitoring it.$"

@ The farewell asks the player to WAIT FOR THE CALL - it does not send them to
@ Olivine now. Until Looker telephones (FLAG_RIFT_LOOKER_SUMMONS), the house only
@ offers its waiting line, and the next town is named on the telephone.
BlackthornCity_Text_UBHookLooker:
	.string "{SPEAKER NAME_LOOKER}Get some rest,\n"
	.string "{PLAYER}.\p"
	.string "We have some notes to compare.\p"
	.string "I'll call when we have a lead.$"

BlackthornCity_Text_UBHookGladion:
	.string "{SPEAKER NAME_GLADION}You held your side.\n"
	.string "Good.\p"
	.string "Come on, Silvally.$"
