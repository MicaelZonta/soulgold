@ ===========================================================================
@ Nexus - the Rift Missions post-game loop, Daily mode.
@ Rules: .claude/rift_missions/nexus/NEXUS_REGRAS.md
@ Plan:  .claude/rift_missions/nexus/NEXUS_IMPLEMENTATION.md
@
@ This file is only the FLOW: rooms, doors, texts. It asks src/nexus.c
@ (specials Nexus_*) everything else - who is behind each door, the
@ legendary, the prize, the state. Content lives in src/data/nexus/*.h.
@
@ One map, six LOGICAL rooms (the room is in VAR_NEXUS_DAILY, bits 13-15):
@   rooms 0..3  three doors, a trainer at each; choosing one closes the others
@   room 4      the champion of the legendary, north door only
@   room 5      the legendary (boss); then the prize and the gift
@ Going through a portal reloads this same map one room further, and
@ ON_TRANSITION rebuilds who stands where. The south corridor always leads
@ back to the altar.
@
@ Layout LAYOUT_ULTRA_SPACE_ARENA, measured on dump_mapa.py Nexus: a cross.
@ Arrival (10,19) at the bottom of the south corridor (x 9..11, y 15..20);
@ the band y 9..11 runs x 0..20; the north arm is x 9..11, y 0..5 (x 8..12
@ on rows 6-7).
@   door   trainer (faces the hub)   portal (end of the arm)
@   west   (4,10)  east              (1,10)
@   north  (10,4)  down              (10,1)
@   east   (16,10) west              (19,10)
@   legendary / its fragment (10,6), prize ball (10,7), exit: y=20, x 9..11
@   Looker File notebook (12,13), champion room only (R18)
@
@ Temp flags: 1-3 trainers W/N/E, 4-6 portals W/N/E, 7 legendary, 8 prize,
@             9 Looker File.
@ Temp vars:  0 exit trigger, 1 arrival latch (chooseitem also writes it -
@             nonzero, so the latch holds), 3 battle result (nexus_fight),
@             4 door being handled, 6 prize.
@
@ Hiding anything here is ALWAYS setflag FLAG_TEMP_n + removeobject, in that
@ order. The arms of the cross are far apart, so the object being closed is
@ usually DESPAWNED (outside the camera rect) - and removeobject on a
@ despawned object is a silent no-op that sets no flag. The player then walks
@ down that arm and TrySpawnObjectEvents puts the "closed" trainer and portal
@ right back (that was the "Elesa stayed and the portal came back" bug).
@ The setflag is what actually holds; the removeobject only despawns the ones
@ close enough to be on camera.
@ Object gfx: VAR_OBJ_GFX_ID_0..2 door trainers, _3 the legendary
@             (set by Nexus_BeginMapLoad).
@ ===========================================================================

Nexus_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Nexus_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Nexus_OnFrame
	.byte 0

@ Everything hidden, then shown by what C says about this room. A reload
@ (next room, save/continue, retry) always rebuilds the same picture.
Nexus_OnTransition::
	special Nexus_BeginMapLoad
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	setflag FLAG_TEMP_9
	setvar VAR_0x8004, NEXUS_DOOR_WEST
	specialvar VAR_RESULT, Nexus_GetDoorState
	call_if_eq VAR_RESULT, NEXUS_DOOR_FIGHT, Nexus_EventScript_ShowTrainerWest
	call_if_ne VAR_RESULT, NEXUS_DOOR_HIDDEN, Nexus_EventScript_ShowPortalWest
	setvar VAR_0x8004, NEXUS_DOOR_NORTH
	specialvar VAR_RESULT, Nexus_GetDoorState
	call_if_eq VAR_RESULT, NEXUS_DOOR_FIGHT, Nexus_EventScript_ShowTrainerNorth
	call_if_ne VAR_RESULT, NEXUS_DOOR_HIDDEN, Nexus_EventScript_ShowPortalNorth
	setvar VAR_0x8004, NEXUS_DOOR_EAST
	specialvar VAR_RESULT, Nexus_GetDoorState
	call_if_eq VAR_RESULT, NEXUS_DOOR_FIGHT, Nexus_EventScript_ShowTrainerEast
	call_if_ne VAR_RESULT, NEXUS_DOOR_HIDDEN, Nexus_EventScript_ShowPortalEast
	specialvar VAR_RESULT, Nexus_GetBossRoomState
	call_if_eq VAR_RESULT, NEXUS_BOSS_ROOM_LEGENDARY, Nexus_EventScript_ShowLegendary
	call_if_eq VAR_RESULT, NEXUS_BOSS_ROOM_FRAGMENT, Nexus_EventScript_ShowLegendary
	call_if_eq VAR_RESULT, NEXUS_BOSS_ROOM_DONE, Nexus_EventScript_ShowPrizeIfPending
	specialvar VAR_RESULT, Nexus_HasLookerFile
	call_if_eq VAR_RESULT, TRUE, Nexus_EventScript_ShowLookerFile
	end

Nexus_EventScript_ShowTrainerWest::
	clearflag FLAG_TEMP_1
	return
Nexus_EventScript_ShowTrainerNorth::
	clearflag FLAG_TEMP_2
	return
Nexus_EventScript_ShowTrainerEast::
	clearflag FLAG_TEMP_3
	return
Nexus_EventScript_ShowPortalWest::
	clearflag FLAG_TEMP_4
	return
Nexus_EventScript_ShowPortalNorth::
	clearflag FLAG_TEMP_5
	return
Nexus_EventScript_ShowPortalEast::
	clearflag FLAG_TEMP_6
	return
Nexus_EventScript_ShowLegendary::
	clearflag FLAG_TEMP_7
	return
Nexus_EventScript_ShowLookerFile::
	clearflag FLAG_TEMP_9
	return

Nexus_EventScript_ShowPrizeIfPending::
	specialvar VAR_RESULT, Nexus_GetPrize
	goto_if_eq VAR_RESULT, ITEM_NONE, Nexus_EventScript_RoomReturn
	clearflag FLAG_TEMP_8
Nexus_EventScript_RoomReturn::
	return

@ ---------------------------------------------------------------------------
@ Arrival: once per load (VAR_TEMP_1 latch FIRST, never a long-lived
@ condition in map_script_2), and only on the arrival tile - a save/continue
@ elsewhere in the room plays nothing.
@ ---------------------------------------------------------------------------
Nexus_OnFrame::
	map_script_2 VAR_TEMP_1, 0, Nexus_EventScript_Arrive
	.2byte 0

@ Arrivals are SILENT (author, 27/09/2026): the per-room narration used to
@ replay on every reload and wore thin. The rules of the place are explained
@ exactly once per save, on the very first arrival; the only rooms that still
@ speak are the boss room (once per day in practice) and the finished day,
@ which re-offers the after-boss gift.
Nexus_EventScript_Arrive::
	setvar VAR_TEMP_1, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 10, Nexus_EventScript_End
	goto_if_ne VAR_0x8005, 19, Nexus_EventScript_End
	specialvar VAR_RESULT, Nexus_GetRoom
	goto_if_eq VAR_RESULT, NEXUS_ROOM_BOSS, Nexus_EventScript_ArriveBoss
	goto_if_unset FLAG_NEXUS_RULES_EXPLAINED, Nexus_EventScript_ExplainRules
	end

Nexus_EventScript_ExplainRules::
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Nexus_Text_Rules, MSGBOX_DEFAULT
	setflag FLAG_NEXUS_RULES_EXPLAINED
	goto Nexus_EventScript_ArriveDone

@ The finished day opens here: the gift is offered again if it could not be
@ given (no room), and the prize ball is on the floor if still there.
Nexus_EventScript_ArriveBoss::
	specialvar VAR_RESULT, Nexus_GetBossRoomState
	goto_if_eq VAR_RESULT, NEXUS_BOSS_ROOM_DONE, Nexus_EventScript_ArriveDoneForToday
	goto_if_eq VAR_RESULT, NEXUS_BOSS_ROOM_FRAGMENT, Nexus_EventScript_ArriveFragment
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Nexus_Text_ArriveBoss, MSGBOX_DEFAULT
	goto Nexus_EventScript_ArriveDone

Nexus_EventScript_ArriveFragment::
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Nexus_Text_ArriveFragment, MSGBOX_DEFAULT
	goto Nexus_EventScript_ArriveDone

Nexus_EventScript_ArriveDoneForToday::
	lockall
	msgbox Nexus_Text_ArriveDoneForToday, MSGBOX_DEFAULT
	closemessage
	callnative Nexus_CallAfterBossScript
Nexus_EventScript_ArriveDone::
	closemessage
	releaseall
Nexus_EventScript_End::
	end

@ ---------------------------------------------------------------------------
@ Doors. Trainer and portal of the same arm lead to the same logic; the door
@ number stays in VAR_TEMP_4 for the whole interaction.
@ ---------------------------------------------------------------------------
Nexus_EventScript_TrainerWest::
	lock
	faceplayer
	setvar VAR_TEMP_4, NEXUS_DOOR_WEST
	goto Nexus_EventScript_Door

Nexus_EventScript_TrainerNorth::
	lock
	faceplayer
	setvar VAR_TEMP_4, NEXUS_DOOR_NORTH
	goto Nexus_EventScript_Door

Nexus_EventScript_TrainerEast::
	lock
	faceplayer
	setvar VAR_TEMP_4, NEXUS_DOOR_EAST
	goto Nexus_EventScript_Door

Nexus_EventScript_PortalWest::
	lock
	setvar VAR_TEMP_4, NEXUS_DOOR_WEST
	goto Nexus_EventScript_Door

Nexus_EventScript_PortalNorth::
	lock
	setvar VAR_TEMP_4, NEXUS_DOOR_NORTH
	goto Nexus_EventScript_Door

Nexus_EventScript_PortalEast::
	lock
	setvar VAR_TEMP_4, NEXUS_DOOR_EAST
	goto Nexus_EventScript_Door

Nexus_EventScript_Door::
	copyvar VAR_0x8004, VAR_TEMP_4
	specialvar VAR_RESULT, Nexus_GetDoorState
	goto_if_eq VAR_RESULT, NEXUS_DOOR_PASS, Nexus_EventScript_Pass
	goto_if_eq VAR_RESULT, NEXUS_DOOR_FIGHT, Nexus_EventScript_Challenge
	release
	end

@ R5.1: the last way out is the YES. Nothing is written before it.
Nexus_EventScript_Challenge::
	copyvar VAR_0x8004, VAR_TEMP_4
	special Nexus_BufferDoorTrainerName
	specialvar VAR_RESULT, Nexus_GetRoom
	goto_if_eq VAR_RESULT, NEXUS_ROOM_CHAMPION, Nexus_EventScript_AskChampion
	specialvar VAR_RESULT, Nexus_IsRoomChosen
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_AskAgain
	msgbox Nexus_Text_AskChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Nexus_EventScript_Decline
	closemessage
	copyvar VAR_0x8004, VAR_TEMP_4
	special Nexus_ChooseDoor
	call Nexus_EventScript_CloseOtherDoors
	goto Nexus_EventScript_Fight

Nexus_EventScript_AskAgain::
	msgbox Nexus_Text_AskAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Nexus_EventScript_Decline
	closemessage
	goto Nexus_EventScript_Fight

Nexus_EventScript_AskChampion::
	msgbox Nexus_Text_AskChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Nexus_EventScript_Decline
	closemessage
	goto Nexus_EventScript_Fight

Nexus_EventScript_Decline::
	closemessage
	release
	end

@ The two other doors die in a white pulse. setflag BEFORE removeobject: the
@ far arms are despawned and only the flag reaches them (see header).
@ fadescreenswapbuffers, never fadescreen: a plain fade composes the
@ time-of-day tint onto itself and dirties the screen a little more on every
@ flash (the Altar learned this first).
Nexus_EventScript_CloseOtherDoors::
	playse SE_M_TELEPORT
	fadescreenswapbuffers FADE_TO_WHITE
	call_if_ne VAR_TEMP_4, NEXUS_DOOR_WEST, Nexus_EventScript_RemoveWest
	call_if_ne VAR_TEMP_4, NEXUS_DOOR_NORTH, Nexus_EventScript_RemoveNorth
	call_if_ne VAR_TEMP_4, NEXUS_DOOR_EAST, Nexus_EventScript_RemoveEast
	fadescreenswapbuffers FADE_FROM_WHITE
	return

Nexus_EventScript_RemoveWest::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_4
	removeobject LOCALID_NEXUS_TRAINER_WEST
	removeobject LOCALID_NEXUS_PORTAL_WEST
	return
Nexus_EventScript_RemoveNorth::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_5
	removeobject LOCALID_NEXUS_TRAINER_NORTH
	removeobject LOCALID_NEXUS_PORTAL_NORTH
	return
Nexus_EventScript_RemoveEast::
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_6
	removeobject LOCALID_NEXUS_TRAINER_EAST
	removeobject LOCALID_NEXUS_PORTAL_EAST
	return

@ The fight itself is data/scripts/nexus.inc, picked by C for this door and
@ room (generic lines in rooms 1-4, lines about the legendary for the
@ champion). R3: losing costs nothing - no whiteout, no money - and throws
@ the player out; the choice and the progress stay. Only WON advances.
Nexus_EventScript_Fight::
	copyvar VAR_0x8004, VAR_TEMP_4
	callnative Nexus_CallDoorFight
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Expelled
	special Nexus_RecordFightWon
	playse SE_M_TELEPORT
	fadescreenswapbuffers FADE_TO_WHITE
	call_if_eq VAR_TEMP_4, NEXUS_DOOR_WEST, Nexus_EventScript_RemoveTrainerWest
	call_if_eq VAR_TEMP_4, NEXUS_DOOR_NORTH, Nexus_EventScript_RemoveTrainerNorth
	call_if_eq VAR_TEMP_4, NEXUS_DOOR_EAST, Nexus_EventScript_RemoveTrainerEast
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox Nexus_Text_PortalOpens, MSGBOX_DEFAULT
	closemessage
	release
	end

Nexus_EventScript_RemoveTrainerWest::
	setflag FLAG_TEMP_1
	removeobject LOCALID_NEXUS_TRAINER_WEST
	return
Nexus_EventScript_RemoveTrainerNorth::
	setflag FLAG_TEMP_2
	removeobject LOCALID_NEXUS_TRAINER_NORTH
	return
Nexus_EventScript_RemoveTrainerEast::
	setflag FLAG_TEMP_3
	removeobject LOCALID_NEXUS_TRAINER_EAST
	return

@ Through an open portal: the same map, one room further.
Nexus_EventScript_Pass::
	playse SE_WARP_IN
	special Nexus_AdvanceRoom
	fadescreen FADE_TO_BLACK
	warpsilent MAP_NEXUS, 10, 19
	waitstate
	release
	end

@ R3: out to the altar, party as it is (R5.2: the Nexus never heals). The
@ next entry starts in room 1 and walks past every guardian already beaten.
Nexus_EventScript_Expelled::
	msgbox Nexus_Text_Expelled, MSGBOX_DEFAULT
	closemessage
	special Nexus_LeaveToAltar
	playse SE_WARP_IN
	warp MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	release
	end

Nexus_EventScript_ExitSouth::
	lockall
	special Nexus_LeaveToAltar
	playse SE_WARP_IN
	warp MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ R6: the legendary. Species - its superior form (R19) -, level (R2) and boss
@ parameters come from Nexus_SetupBoss. R17: it can NOT be caught in battle
@ (B_FLAG_NO_CATCHING; the engine clears it after the battle) - a concept
@ cannot be caught. B_FLAG_NO_WHITEOUT makes a loss hand the result back
@ here (CB2_EndScriptedWildBattle, src/battle_setup.c).
@   WON (knocked out)  it comes apart; its FRAGMENT stays at (10,6):
@                   progress 6, written right away (R15)
@   RAN / MON_FLED  it stays where it is
@   anything else   (LOST, DREW, FORFEITED) expelled, like a lost fight
@ ---------------------------------------------------------------------------
Nexus_EventScript_Legendary::
	lock
	specialvar VAR_RESULT, Nexus_GetBossRoomState
	goto_if_eq VAR_RESULT, NEXUS_BOSS_ROOM_FRAGMENT, Nexus_EventScript_Fragment
	goto_if_ne VAR_RESULT, NEXUS_BOSS_ROOM_LEGENDARY, Nexus_EventScript_Decline
	msgbox Nexus_Text_AskBoss, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Nexus_EventScript_Decline
	closemessage
	special Nexus_SetupBoss
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	waitmoncry
	setflag B_FLAG_NO_WHITEOUT
	setflag B_FLAG_NO_CATCHING
	special BattleSetup_StartLegendaryEncounter
	waitstate
	clearflag B_FLAG_NO_WHITEOUT
	clearflag B_FLAG_NO_CATCHING
	specialvar VAR_TEMP_3, GetBattleOutcome
	goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_BossBreaks
	goto_if_eq VAR_TEMP_3, B_OUTCOME_RAN, Nexus_EventScript_BossStays
	goto_if_eq VAR_TEMP_3, B_OUTCOME_MON_FLED, Nexus_EventScript_BossStays
	goto Nexus_EventScript_Expelled

@ The concept comes apart. The same object at (10,6) is respawned with the
@ fragment's sprite (Nexus_RecordBossBeaten sets VAR_OBJ_GFX_ID_3).
@ removeobject sets FLAG_TEMP_7, so it is cleared again before addobject.
Nexus_EventScript_BossBreaks::
	special Nexus_RecordBossBeaten
	msgbox Nexus_Text_BossBreaks, MSGBOX_DEFAULT
	closemessage
	playse SE_M_TELEPORT
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_NEXUS_LEGENDARY
	clearflag FLAG_TEMP_7
	addobject LOCALID_NEXUS_LEGENDARY
	fadescreenswapbuffers FADE_FROM_WHITE
	special Nexus_BufferFragmentNames
	msgbox Nexus_Text_FragmentRemains, MSGBOX_DEFAULT
	goto Nexus_EventScript_Fragment

@ R17: the fragment - first form, level 1 - goes with the player only in a
@ ball from the Bag: a Beast Ball for an Ultra Beast, any ball otherwise.
@ Order: party AND box space first (skill entregar-pokemon-ou-ovo), then the
@ ball, then the offer. Nothing is written or spent until the mon is given;
@ without room or a ball the fragment simply waits (progress stays 6).
Nexus_EventScript_Fragment::
	special Nexus_BufferFragmentNames
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, Nexus_EventScript_FragmentHasRoom
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_FragmentHasRoom
	msgbox Nexus_Text_FragmentNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

Nexus_EventScript_FragmentHasRoom::
	specialvar VAR_RESULT, Nexus_FragmentNeedsBeastBall
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_FragmentBeastBall
	specialvar VAR_RESULT, Nexus_HasAnyBall
	goto_if_eq VAR_RESULT, FALSE, Nexus_EventScript_FragmentNoBall
	msgbox Nexus_Text_FragmentChooseBall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Nexus_EventScript_FragmentLeave
	closemessage
	chooseitem POCKET_POKE_BALLS
	goto_if_eq VAR_ITEM_ID, ITEM_NONE, Nexus_EventScript_FragmentLeave
	copyvar VAR_0x8005, VAR_ITEM_ID
	goto Nexus_EventScript_FragmentThrow

Nexus_EventScript_FragmentBeastBall::
	checkitem ITEM_BEAST_BALL
	goto_if_eq VAR_RESULT, FALSE, Nexus_EventScript_FragmentNoBeastBall
	msgbox Nexus_Text_FragmentAskBeastBall, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Nexus_EventScript_FragmentLeave
	closemessage
	setvar VAR_0x8005, ITEM_BEAST_BALL
Nexus_EventScript_FragmentThrow::
	special Nexus_GiveFragment
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Nexus_EventScript_FragmentNoRoomAfterAll
	@ the PC notice (Common_EventScript_GiftMon) reads the species from here;
	@ it is also the arrival latch VAR_TEMP_1 - a species keeps it closed
	copyvar VAR_TEMP_TRANSFERRED_SPECIES, VAR_0x8004
	removeitem VAR_0x8005
	special Nexus_RecordCapture
	playse SE_BALL_THROW
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_TEMP_7
	removeobject LOCALID_NEXUS_LEGENDARY
	fadescreenswapbuffers FADE_FROM_WHITE
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox Nexus_Text_FragmentCaught, MSGBOX_DEFAULT
	call Common_EventScript_GiftMon
	closemessage
	callnative Nexus_CallAfterBossScript
	goto Nexus_EventScript_Finale

Nexus_EventScript_FragmentNoBeastBall::
	msgbox Nexus_Text_FragmentNoBeastBall, MSGBOX_DEFAULT
	goto Nexus_EventScript_FragmentLeave

Nexus_EventScript_FragmentNoBall::
	msgbox Nexus_Text_FragmentNoBall, MSGBOX_DEFAULT
Nexus_EventScript_FragmentLeave::
	closemessage
	release
	end

@ Defensive guard only: the space check above already blocked this path.
@ Nothing was written and no ball was spent.
Nexus_EventScript_FragmentNoRoomAfterAll::
	msgbox Nexus_Text_FragmentNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

Nexus_EventScript_BossStays::
	msgbox Nexus_Text_BossStays, MSGBOX_DEFAULT
	closemessage
	release
	end

@ R18: the Looker File of the day (the page comes from the legendary's line).
Nexus_EventScript_LookerFile::
	lock
	msgbox Nexus_Text_LookerFileIntro, MSGBOX_DEFAULT
	callnative Nexus_CallLookerFileScript
	msgbox Nexus_Text_LookerFileOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

@ ---------------------------------------------------------------------------
@ The finale (author, 27/09): the prize is found on the spot, and then the
@ dimension falls apart and throws the player out. A full bag keeps the
@ prize ball on the floor for a quieter visit later the same day (the
@ finished-day room shows it and re-offers the gift).
@ ---------------------------------------------------------------------------
Nexus_EventScript_Finale::
	specialvar VAR_RESULT, Nexus_GetPrize
	goto_if_eq VAR_RESULT, ITEM_NONE, Nexus_EventScript_Collapse
	copyvar VAR_TEMP_6, VAR_RESULT
	checkitemspace VAR_TEMP_6, 1
	goto_if_eq VAR_RESULT, FALSE, Nexus_EventScript_FinalePrizeNoRoom
	msgbox Nexus_Text_PrizeAppears, MSGBOX_DEFAULT
	closemessage
	special Nexus_MarkPrizeTaken
	finditem VAR_TEMP_6
	goto Nexus_EventScript_Collapse

Nexus_EventScript_FinalePrizeNoRoom::
	msgbox Nexus_Text_PrizeNoRoom, MSGBOX_DEFAULT
	closemessage
	goto Nexus_EventScript_Collapse

@ ShakeCamera reads FOUR vars: pan, pan, count, delay (the Altar pattern).
Nexus_EventScript_Collapse::
	closemessage
	delay 30
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	msgbox Nexus_Text_CollapseBegins, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_M_EXPLOSION
	setvar VAR_0x8004, 2
	setvar VAR_0x8005, 2
	setvar VAR_0x8006, 16
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox Nexus_Text_CollapseThrownOut, MSGBOX_DEFAULT
	closemessage
	special Nexus_LeaveToAltar
	playse SE_WARP_OUT
	warp MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	release
	end

@ R9: checked before anything is written; a full bag leaves the ball there.
Nexus_EventScript_Prize::
	lock
	specialvar VAR_RESULT, Nexus_GetPrize
	goto_if_eq VAR_RESULT, ITEM_NONE, Nexus_EventScript_Decline
	copyvar VAR_TEMP_6, VAR_RESULT
	checkitemspace VAR_TEMP_6, 1
	goto_if_eq VAR_RESULT, FALSE, Nexus_EventScript_PrizeNoRoom
	special Nexus_MarkPrizeTaken
	finditem VAR_TEMP_6
	release
	end

Nexus_EventScript_PrizeNoRoom::
	msgbox Nexus_Text_PrizeNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

@ ===========================================================================
@ Texts. Narration, no plate. The rules play once per save; everything else
@ is either once per day or tied to an action the player just took.
@ ===========================================================================
Nexus_Text_Rules:
	.string "The rift seals itself behind you.\p"
	.string "This is the Nexus. Five guardians\n"
	.string "watch its chambers, and something\l"
	.string "enormous waits at its heart.\p"
	.string "Each chamber offers three portals,\n"
	.string "and a challenger before each one.\p"
	.string "Choose one. The other two paths will\n"
	.string "close until the day is over.\p"
	.string "Nothing in here will heal your\n"
	.string "Pokémon. The passage to the south\l"
	.string "always leads back out.\p"
	.string "Leave whenever you need to. What you\n"
	.string "opened stays open, whom you beat\l"
	.string "stays beaten -- until midnight.\p"
	.string "Beat the five, and the heart of the\n"
	.string "Nexus will face you itself.\p"
	.string "Nothing here is whole. Nothing here\n"
	.string "is quite real. Break it, and only a\l"
	.string "fragment of it will go with you.$"

Nexus_Text_ArriveBoss:
	.string "The heart of the Nexus.\n"
	.string "Something enormous is waiting.$"

Nexus_Text_ArriveDoneForToday:
	.string "The heart of the Nexus is quiet.\n"
	.string "Nothing more will come today.$"

Nexus_Text_AskChallenge:
	.string "{STR_VAR_1} guards this portal.\p"
	.string "Challenge {STR_VAR_1}?\n"
	.string "The other portals will close.$"

Nexus_Text_AskAgain:
	.string "{STR_VAR_1} guards this portal.\n"
	.string "Challenge {STR_VAR_1}?$"

Nexus_Text_AskChampion:
	.string "{STR_VAR_1} guards the last portal.\n"
	.string "Challenge {STR_VAR_1}?$"

Nexus_Text_PortalOpens:
	.string "The portal flares open.$"

Nexus_Text_Expelled:
	.string "The rift shudders and pushes you out.\p"
	.string "The paths you opened will stay open\n"
	.string "until the day is over.$"

Nexus_Text_AskBoss:
	.string "It is watching you.\n"
	.string "Face it?$"

Nexus_Text_ArriveFragment:
	.string "The heart of the Nexus.\n"
	.string "Something small is still waiting.$"

Nexus_Text_BossBreaks:
	.string "It does not fall. It comes apart.\p"
	.string "Pieces of it drift off in every\n"
	.string "direction -- into yesterday, into\l"
	.string "somewhere else, into nothing at all.$"

Nexus_Text_FragmentRemains:
	.string "What stays behind is small, and new,\n"
	.string "as if it had only just begun.\p"
	.string "Not {STR_VAR_2}. Only a fragment of the\n"
	.string "idea of it: a {STR_VAR_1}.\p"
	.string "The rest could never be held.$"

Nexus_Text_FragmentChooseBall:
	.string "The fragment of {STR_VAR_2} waits.\n"
	.string "Take it with you in a Poké Ball?$"

Nexus_Text_FragmentAskBeastBall:
	.string "The fragment of {STR_VAR_2} waits.\p"
	.string "It came from beyond the rifts. Only a\n"
	.string "Beast Ball could ever hold it.\p"
	.string "Throw a Beast Ball?$"

Nexus_Text_FragmentNoBeastBall:
	.string "The fragment of {STR_VAR_2} waits.\p"
	.string "It came from beyond the rifts. Only a\n"
	.string "Beast Ball could ever hold it, and you\l"
	.string "have none.\p"
	.string "It will still be here today.$"

Nexus_Text_FragmentNoBall:
	.string "The fragment of {STR_VAR_2} waits, but\n"
	.string "you have no Poké Ball to hold it.\p"
	.string "It will still be here today.$"

Nexus_Text_FragmentNoRoom:
	.string "The fragment of {STR_VAR_2} waits.\p"
	.string "But your team is full, and your Boxes\n"
	.string "are full too. There is nowhere for it.\p"
	.string "Make some room and come back.\n"
	.string "It will still be here today.$"

Nexus_Text_FragmentCaught:
	.string "The ball closes over the fragment,\n"
	.string "and holds.$"

Nexus_Text_LookerFileIntro:
	.string "A notebook lies open on the floor.\n"
	.string "Its pages stir, though there is no wind.\p"
	.string "The handwriting is Looker's.\n"
	.string "The ink is still wet.$"

Nexus_Text_LookerFileOutro:
	.string "The page is dated a day that has\n"
	.string "not happened yet.$"

Nexus_Text_BossStays:
	.string "It is still watching you.$"

Nexus_Text_CollapseBegins:
	.string "The heart of the Nexus goes silent.\p"
	.string "Then, from everywhere at once, a deep\n"
	.string "crack runs through the dark.$"

Nexus_Text_CollapseThrownOut:
	.string "The chambers are falling in on\n"
	.string "themselves!\p"
	.string "Light floods down from the tear\n"
	.string "above -- and the dimension hurls\l"
	.string "you out!$"

Nexus_Text_PrizeAppears:
	.string "Something glints where it stood.$"

Nexus_Text_PrizeNoRoom:
	.string "Something glints on the ground, but\n"
	.string "your Bag is full.\p"
	.string "It will still be here today.$"
