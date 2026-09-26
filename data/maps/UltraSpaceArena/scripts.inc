@ ===========================================================================
@ Ultra Space Arena - ACT IV of the Sun and Moon Altar event (V2), and the
@ room the post-game daily survey leads to.
@ Script: .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_sUN_MOON_SCRIPT_V2.md
@ Plan:   .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md (section 21)
@
@ Every scene here starts on a load, guarded by state, step and tile:
@   14/CROSSING   at (10,19)  full arrival: Ultra Necrozma already there
@   14/RECROSSING at (10,19)  short arrival after a lost boss
@   14/CAPTURE    at (9,11)   back from the altar reception cut: the capture
@   >= 16         at (10,19)  the empty daily survey (the loop's hook)
@ Temp flags: 1 Anabel  2 Necrozma  3 Ultra Necrozma  4 partner (VAR_2 gfx)
@   5/7 the two UB slots (VAR_0/VAR_1 gfx)  6 Beast Ball
@ ===========================================================================

UltraSpaceArena_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, UltraSpaceArena_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, UltraSpaceArena_OnFrame
	.byte 0

@ Everything hidden on every load, then shown by state. A blackout retry finds
@ the map exactly as the first time.
UltraSpaceArena_OnTransition::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_SPECIES(SOLGALEO)
	call_if_eq VAR_RIFT_ALTAR_PARTNER, SPECIES_LUNALA, UltraSpaceArena_EventScript_LunalaGfx
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 14, UltraSpaceArena_EventScript_End
	@ V2 section 12: it is ALREADY Ultra when they arrive, visible from the
	@ corridor; the normal form never appears before the battle
	call_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CROSSING, UltraSpaceArena_EventScript_ShowUltra
	call_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RECROSSING, UltraSpaceArena_EventScript_ShowUltra
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CAPTURE, UltraSpaceArena_EventScript_CaptureStage
	end

UltraSpaceArena_EventScript_LunalaGfx::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_SPECIES(LUNALA)
	return

UltraSpaceArena_EventScript_ShowUltra::
	clearflag FLAG_TEMP_3
	return

@ Back from the reception cut: the picture the victory left. Anabel at the
@ inside unit (11,12), the partner beside her (12,12), Necrozma - normal,
@ beaten - on its own tile (10,8). The player lands on (9,11).
UltraSpaceArena_EventScript_CaptureStage::
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_4
	setobjectxyperm LOCALID_ULTRA_SPACE_ARENA_ANABEL, 11, 12
	setobjectxyperm LOCALID_ULTRA_SPACE_ARENA_PARTNER, 12, 12
	end

UltraSpaceArena_OnFrame::
	map_script_2 VAR_TEMP_1, 0, UltraSpaceArena_EventScript_ArrivalTrigger
	.2byte 0

@ VAR_TEMP_1 latch set FIRST (a true map_script_2 is a livelock). It is also
@ VAR_TEMP_TRANSFERRED_SPECIES: the capture writes SPECIES_NECROZMA into it,
@ which keeps it non-zero - the latch stays closed.
UltraSpaceArena_EventScript_ArrivalTrigger::
	setvar VAR_TEMP_1, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, UltraSpaceArena_EventScript_TryEmpty
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 14, UltraSpaceArena_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CAPTURE, UltraSpaceArena_EventScript_TryCapture
	goto_if_ne VAR_0x8004, 10, UltraSpaceArena_EventScript_End
	goto_if_ne VAR_0x8005, 19, UltraSpaceArena_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CROSSING, UltraSpaceArena_EventScript_Confront
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RECROSSING, UltraSpaceArena_EventScript_Confront
UltraSpaceArena_EventScript_End::
	end

UltraSpaceArena_EventScript_TryCapture::
	goto_if_ne VAR_0x8004, 9, UltraSpaceArena_EventScript_End
	goto_if_ne VAR_0x8005, 11, UltraSpaceArena_EventScript_End
	goto UltraSpaceArena_EventScript_Capture

UltraSpaceArena_EventScript_TryEmpty::
	goto_if_ne VAR_0x8004, 10, UltraSpaceArena_EventScript_End
	goto_if_ne VAR_0x8005, 19, UltraSpaceArena_EventScript_End
	goto UltraSpaceArena_EventScript_EmptyRift

@ SKELETON: state >= 16, the daily survey, nothing in it yet. THE HANDOFF TO
@ THE LOOP DOCUMENT. The delay is not cosmetic: this is the only
@ MAP_TYPE_UNDERGROUND map entered by warpsilent, and the enter-cave transition
@ runs first (src/fldeff_flash.c). The white-screen freeze reported on this
@ entry is still an open technical item (plan section 18.5).
UltraSpaceArena_EventScript_EmptyRift::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox UltraSpaceArena_Text_EmptySurvey, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ ---------------------------------------------------------------------------
@ ACT IV. Measured on dump_mapa.py UltraSpaceArena. The corridor is x=9..11
@ from y=15 to y=19, x=8..12 on rows 13-14, and the pad opens above.
@   partner addobject (11,19) -> up 7 -> (11,12) -> right -> (12,12)
@   Anabel  addobject (9,19)  -> up 6 -> (9,13) -> right 2 -> (11,13) -> up
@           -> (11,12), the inside unit, OUT of column 10 (the retreat line)
@   player  (10,19) -> up 8 -> (10,11)
@   Ultra Necrozma (10,8), there from the load
@ Partner first, as in the altar: it steps off one tile earlier than Anabel
@ reaches the same row, so no two actors ever share a tile.
@ waitmovement per local id, never 0 with two actors moving.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Confront::
	lockall
	hidefollower
	delay 20
	addobject LOCALID_ULTRA_SPACE_ARENA_PARTNER
	addobject LOCALID_ULTRA_SPACE_ARENA_ANABEL
	applymovement LOCALID_ULTRA_SPACE_ARENA_PARTNER, UltraSpaceArena_Movement_PartnerUp
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, UltraSpaceArena_Movement_AnabelUp
	applymovement OBJ_EVENT_ID_PLAYER, UltraSpaceArena_Movement_PlayerUp
	waitmovement LOCALID_ULTRA_SPACE_ARENA_PARTNER
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RECROSSING, UltraSpaceArena_EventScript_ShortIntro
	@ Anabel sets the inside unit down, leaves her kit within reach and tests
	@ the answer from outside, before any word
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, UltraSpaceArena_Movement_AnabelSetup
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_AnabelFound, MSGBOX_DEFAULT
	closemessage
	@ it tries to pull light from the unstable edge; the edge warps; the
	@ partner restores it with a brief pulse. No beam from partner to Necrozma.
	applymovement LOCALID_ULTRA_SPACE_ARENA_ULTRA, UltraSpaceArena_Movement_UltraFlare
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ULTRA
	call UltraSpaceArena_EventScript_Shake
	call UltraSpaceArena_EventScript_Flash
	applymovement LOCALID_ULTRA_SPACE_ARENA_PARTNER, UltraSpaceArena_Movement_Pulse
	waitmovement LOCALID_ULTRA_SPACE_ARENA_PARTNER
	playmoncry VAR_RIFT_ALTAR_PARTNER, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_AnabelProtectPartner, MSGBOX_DEFAULT
	closemessage
	@ the player takes the front; it turns to the player
	applymovement LOCALID_ULTRA_SPACE_ARENA_ULTRA, UltraSpaceArena_Movement_UltraFlare
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ULTRA
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, UltraSpaceArena_Movement_AnabelSetup
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	msgbox UltraSpaceArena_Text_AnabelAtControls, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_BattleStart, MSGBOX_DEFAULT
	closemessage
	goto UltraSpaceArena_EventScript_Battle

@ After a lost boss: no first discovery again (V2 section 16).
UltraSpaceArena_EventScript_ShortIntro::
	msgbox UltraSpaceArena_Text_RetryStart, MSGBOX_DEFAULT
	closemessage
	goto UltraSpaceArena_EventScript_Battle

UltraSpaceArena_Movement_PlayerUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

UltraSpaceArena_Movement_PartnerUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	face_up
	step_end

UltraSpaceArena_Movement_AnabelUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	face_up
	step_end

UltraSpaceArena_Movement_AnabelSetup:
	face_down
	walk_in_place_slow_down
	face_up
	step_end

@ Four fast steps in place, facing SOUTH (y grows DOWN): it burns harder
UltraSpaceArena_Movement_UltraFlare:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

UltraSpaceArena_Movement_Pulse:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

UltraSpaceArena_EventScript_Shake::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	return

@ fadescreenswapbuffers only: every flash here comes back to this map
UltraSpaceArena_EventScript_Flash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

UltraSpaceArena_EventScript_Comm::
	playse SE_POKENAV_CALL
	waitse
	return

@ ---------------------------------------------------------------------------
@ THREAT battle: no B_FLAG_NO_WHITEOUT (loss = blackout and retry, state 14).
@ Profile unchanged by V2: 5 bars / Lv 90 / 160% / BOSS_PHASE_PROFILE_NECROZMA
@ (five phases = five bars, or IsBossPhaseProfileValid drops the profile).
@ B_FLAG_NO_CATCHING: the capture is a scene after the rescue. The partner is
@ an ordinary team member in the battle - no lock, no HP script.
@ BOSS_SEEN is written BEFORE the battle: a blackout never comes back here,
@ and the next crossing must open with the short intro and the altar must
@ play the regroup lines.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Battle::
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_BOSS_SEEN
	setflag B_FLAG_NO_CATCHING
	setbossbattle 5, SPECIES_NONE, 160, BOSS_PHASE_PROFILE_NECROZMA
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_NECROZMA_ULTRA, 90, ITEM_NONE
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, UltraSpaceArena_EventScript_Victory
	goto UltraSpaceArena_EventScript_Unresolved

@ Anything that is not WON (and came back): never a rescue, never a capture.
@ Everyone withdraws; the altar keeps state 14. Never used after a win.
UltraSpaceArena_EventScript_Unresolved::
	msgbox UltraSpaceArena_Text_BossUnresolved, MSGBOX_DEFAULT
	closemessage
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RETRY_READY
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ VICTORY: separate, receive, check (V2 section 13). The win is recorded
@ before anything else can fail (ALTAR_STEP_RESCUE): from here nothing
@ re-runs the boss.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Victory::
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RESCUE
	@ sync the actor with the result: only normal Necrozma, weakened, on its tile
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_ULTRA_SPACE_ARENA_ULTRA
	addobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_WEAK
	waitmoncry
	msgbox UltraSpaceArena_Text_VictoryAnabel, MSGBOX_DEFAULT
	closemessage
	call UltraSpaceArena_EventScript_Comm
	msgbox UltraSpaceArena_Text_VictoryLooker, MSGBOX_DEFAULT
	closemessage
	@ the partner, treated within reach of the inside unit (Anabel (11,12),
	@ partner (12,12)): one hand on the control, one on the kit. A full team
	@ heal is the only safe helper the engine has; it runs here, explicitly.
	bufferspeciesname STR_VAR_1, VAR_RIFT_ALTAR_PARTNER
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_EAST
	msgbox UltraSpaceArena_Text_PartnerCare, MSGBOX_DEFAULT
	closemessage
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	msgbox UltraSpaceArena_Text_PartnerReturn, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_NORTH
	applymovement LOCALID_ULTRA_SPACE_ARENA_PARTNER, UltraSpaceArena_Movement_Pulse
	waitmovement LOCALID_ULTRA_SPACE_ARENA_PARTNER
	@ the player steps out of the retreat line: (10,11) -> (9,11)
	applymovement OBJ_EVENT_ID_PLAYER, UltraSpaceArena_Movement_PlayerAside
	waitmovement OBJ_EVENT_ID_PLAYER
	@ five exits, one or two at a time; each has its arrival at the altar.
	@ Slot A condenses at (11,8), slot B at (9,8), beside Necrozma; each walks
	@ one row down, into column 10, and down the corridor out of the frame.
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(BUZZWOLE)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(PHEROMOSA)
	call UltraSpaceArena_EventScript_ExitPair
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(XURKITREE)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(CELESTEELA)
	call UltraSpaceArena_EventScript_ExitPair
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(BLACEPHALON)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(STAKATAKA)
	call UltraSpaceArena_EventScript_ExitPair
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(KARTANA)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(GUZZLORD)
	call UltraSpaceArena_EventScript_ExitPair
	@ Nihilego, the last to separate, drifting down the steady route
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(NIHILEGO)
	call UltraSpaceArena_EventScript_Condense
	addobject LOCALID_ULTRA_SPACE_ARENA_UB_A
	applymovement LOCALID_ULTRA_SPACE_ARENA_UB_A, UltraSpaceArena_Movement_ExitSlowA
	waitmovement LOCALID_ULTRA_SPACE_ARENA_UB_A
	removeobject LOCALID_ULTRA_SPACE_ARENA_UB_A
	@ the cut: the same nine, arriving on the other side
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 16, 13
	waitstate
	releaseall
	end

@ A pair: A goes first; B separates and follows once A is on its way.
UltraSpaceArena_EventScript_ExitPair::
	call UltraSpaceArena_EventScript_Condense
	addobject LOCALID_ULTRA_SPACE_ARENA_UB_A
	delay 20
	applymovement LOCALID_ULTRA_SPACE_ARENA_UB_A, UltraSpaceArena_Movement_ExitA
	delay 24
	call UltraSpaceArena_EventScript_Condense
	addobject LOCALID_ULTRA_SPACE_ARENA_UB_B
	delay 16
	applymovement LOCALID_ULTRA_SPACE_ARENA_UB_B, UltraSpaceArena_Movement_ExitB
	waitmovement LOCALID_ULTRA_SPACE_ARENA_UB_A
	removeobject LOCALID_ULTRA_SPACE_ARENA_UB_A
	waitmovement LOCALID_ULTRA_SPACE_ARENA_UB_B
	removeobject LOCALID_ULTRA_SPACE_ARENA_UB_B
	delay 20
	return

@ a filament leaves Necrozma: it flickers, a short flash
UltraSpaceArena_EventScript_Condense::
	applymovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA, UltraSpaceArena_Movement_Flicker
	waitmovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	playse SE_M_REFLECT
	return

UltraSpaceArena_Movement_Flicker:
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

UltraSpaceArena_Movement_PlayerAside:
	walk_left
	face_right
	step_end

@ (11,8) -> (11,9) -> (10,9) -> down to (10,17), below the frame
UltraSpaceArena_Movement_ExitA:
	walk_down
	walk_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ (9,8) -> (9,9) -> (10,9) -> down to (10,17)
UltraSpaceArena_Movement_ExitB:
	walk_down
	walk_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

UltraSpaceArena_Movement_ExitSlowA:
	walk_slow_down
	walk_slow_left
	walk_slow_down
	walk_slow_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ ---------------------------------------------------------------------------
@ THE CAPTURE (V2 section 14). Back from the altar cut; player on (9,11).
@ Anabel hands over Kurt's Beast Ball from the reunion. The last room check is
@ silent and comes BEFORE the irreversible animation; without room Anabel
@ takes Necrozma into custody instead - the win and the rescue stand.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Capture::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	@ it tries to rise, and stops
	applymovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA, UltraSpaceArena_Movement_Flicker
	waitmovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	msgbox UltraSpaceArena_Text_CaptureAnabel, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_WEST
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, UltraSpaceArena_EventScript_CaptureRoom
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_ne VAR_RESULT, TRUE, UltraSpaceArena_EventScript_Custody
UltraSpaceArena_EventScript_CaptureRoom::
	msgbox UltraSpaceArena_Text_CaptureBall, MSGBOX_DEFAULT
	closemessage
	playse SE_BALL_TRAY_ENTER
	@ the player comes up the safe corridor: (9,11) -> (10,11) -> (10,10)
	applymovement OBJ_EVENT_ID_PLAYER, UltraSpaceArena_Movement_PlayerApproach
	waitmovement OBJ_EVENT_ID_PLAYER
	@ the throw: from the player's tile (10,10) to (10,9), Necrozma turns to
	@ light and goes in, the Ball drops onto (10,8)
	setobjectxyperm LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL, 10, 10
	call UltraSpaceArena_EventScript_BallCapture
	@ fanfare at the click, then the record: Necrozma Lv 75 in a Beast Ball
	call UltraSpaceArena_EventScript_GiveNecrozma
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, UltraSpaceArena_EventScript_CustodyAfterThrow
	removeobject LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	msgbox UltraSpaceArena_Text_CaptureReturn, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_5, ALTAR_STEP_NONE
	goto UltraSpaceArena_EventScript_CaptureDone

@ The Ball, the shakes and the click. The Ball is its own object (the engine's
@ enter_pokeball leaves nothing behind); its template was moved to the start
@ tile by the caller. jump_in_place is the short displacement V2 allows when
@ the asset has no rocking frames.
UltraSpaceArena_EventScript_BallCapture::
	addobject LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	playse SE_BALL_THROW
	applymovement LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL, UltraSpaceArena_Movement_BallFly
	waitmovement LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	applymovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA, UltraSpaceArena_Movement_EnterBall
	waitmovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	removeobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	applymovement LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL, UltraSpaceArena_Movement_BallDrop
	waitmovement LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	delay 20
	call UltraSpaceArena_EventScript_BallShake
	call UltraSpaceArena_EventScript_BallShake
	call UltraSpaceArena_EventScript_BallShake
	playse SE_BALL_OPEN
	delay 20
	return

UltraSpaceArena_EventScript_BallShake::
	playse SE_BALL
	applymovement LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL, UltraSpaceArena_Movement_BallRock
	waitmovement LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	delay 24
	return

UltraSpaceArena_Movement_PlayerApproach:
	walk_right
	walk_up
	face_up
	step_end

UltraSpaceArena_Movement_BallFly:
	jump_up
	step_end

UltraSpaceArena_Movement_BallDrop:
	jump_up
	step_end

UltraSpaceArena_Movement_BallRock:
	jump_in_place_down
	step_end

UltraSpaceArena_Movement_EnterBall:
	enter_pokeball
	step_end

@ The gift, once: Necrozma, level 75, BALL_BEAST written into the data (not
@ only the look of the scene). STR_VAR_1 rebuffered here - it held the
@ partner a minute ago (the old "received SOLGALEO"). One confirmation, SYSTEM,
@ no plate; then nickname and, if it went to the PC, the PC notice.
@ Out: VAR_RESULT = the givemon result.
UltraSpaceArena_EventScript_GiveNecrozma::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_NECROZMA
	bufferspeciesname STR_VAR_1, SPECIES_NECROZMA
	givemon SPECIES_NECROZMA, 75, ITEM_NONE, ball=BALL_BEAST
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, UltraSpaceArena_EventScript_Return
	copyvar VAR_TEMP_4, VAR_RESULT
	playfanfare MUS_HG_CAUGHT
	message UltraSpaceArena_Text_CaptureConfirmed
	waitmessage
	waitfanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_TEMP_4, MON_GIVEN_TO_PC, UltraSpaceArena_EventScript_GivenToPC
	call_if_eq VAR_RESULT, YES, Common_EventScript_NameReceivedPartyMonFull
	copyvar VAR_RESULT, VAR_TEMP_4
	return
UltraSpaceArena_EventScript_GivenToPC::
	call_if_eq VAR_RESULT, YES, Common_EventScript_NameReceivedBoxMon
	call Common_EventScript_TransferredToPC
	copyvar VAR_RESULT, VAR_TEMP_4
UltraSpaceArena_EventScript_Return::
	return

@ No room at the last check: Anabel takes Necrozma into custody with the
@ mission Ball - shown once, from the tile in front of it (10,9) - and keeps it
@ until the player can receive it at the altar. Nothing is lost on leaving.
UltraSpaceArena_EventScript_Custody::
	setobjectxyperm LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL, 10, 10
	call UltraSpaceArena_EventScript_BallCapture
UltraSpaceArena_EventScript_CustodyAfterThrow::
	removeobject LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	msgbox UltraSpaceArena_Text_CapturePending, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_5, ALTAR_STEP_CUSTODY
	goto UltraSpaceArena_EventScript_CaptureDone

@ The partner crosses back visibly, Anabel packs the unit last, and state 15 is
@ written under the fade with the step (NONE, or CUSTODY). (14,11): under the
@ rift, not a warp; the altar's frame trigger tests exactly that tile.
UltraSpaceArena_EventScript_CaptureDone::
	applymovement LOCALID_ULTRA_SPACE_ARENA_PARTNER, UltraSpaceArena_Movement_PartnerOut
	waitmovement LOCALID_ULTRA_SPACE_ARENA_PARTNER
	removeobject LOCALID_ULTRA_SPACE_ARENA_PARTNER
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, UltraSpaceArena_Movement_AnabelSetup
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	playse SE_WARP_OUT
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 15
	copyvar VAR_RIFT_ALTAR_STEP, VAR_TEMP_5
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ (12,12) -> (12,13) -> (10,13) -> down the corridor, out of the frame
UltraSpaceArena_Movement_PartnerOut:
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Her object script: she is under lockall whenever she exists, but an object
@ with a NULL script is a silent A-press.
UltraSpaceArena_EventScript_Anabel::
	lock
	faceplayer
	msgbox UltraSpaceArena_Text_AnabelAtControls, MSGBOX_DEFAULT
	release
	end

@ South rift, bottom row: back to the altar. (14,11), never (14,10), where
@ the mark or the rift object stands.
UltraSpaceArena_EventScript_SouthRift::
	lockall
	playse SE_WARP_IN
	warp MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ ===========================================================================
@ Texts - V2, verbatim. Plate on every box; SYSTEM/NARRATOR without plate.
@ ===========================================================================
UltraSpaceArena_Text_AnabelFound:
	.string "{SPEAKER NAME_ANABEL}Necrozma.\n"
	.string "The nine signals are still here.$"

UltraSpaceArena_Text_AnabelProtectPartner:
	.string "{SPEAKER NAME_ANABEL}Keep Necrozma away from your partner.\n"
	.string "We need that passage open.$"

UltraSpaceArena_Text_AnabelAtControls:
	.string "{SPEAKER NAME_ANABEL}I'll hold the return steady.\n"
	.string "We get the others out\l"
	.string "when its grip weakens.$"

UltraSpaceArena_Text_BattleStart:
	.string "{SPEAKER NAME_ANABEL}Now, {PLAYER}!$"

UltraSpaceArena_Text_RetryStart:
	.string "{SPEAKER NAME_ANABEL}The return is steady.\n"
	.string "Ready when you are, {PLAYER}.$"

UltraSpaceArena_Text_BossUnresolved:
	.string "{SPEAKER NAME_ANABEL}We need to regroup.\n"
	.string "We'll try again when you're ready.$"

UltraSpaceArena_Text_VictoryAnabel:
	.string "{SPEAKER NAME_ANABEL}The links are separating.\n"
	.string "Looker, get everyone ready.$"

@ over the communicator: the sound says so, the plate says who
UltraSpaceArena_Text_VictoryLooker:
	.string "{SPEAKER NAME_LOOKER}We're ready. Bring them through.$"

UltraSpaceArena_Text_PartnerCare:
	.string "{SPEAKER NAME_ANABEL}One moment, {STR_VAR_1}.\n"
	.string "Let me help you.$"

UltraSpaceArena_Text_PartnerReturn:
	.string "{SPEAKER NAME_ANABEL}Good. Keep the opening steady.$"

UltraSpaceArena_Text_CaptureAnabel:
	.string "{SPEAKER NAME_ANABEL}Now Necrozma.\n"
	.string "We can take it out of here.$"

UltraSpaceArena_Text_CaptureBall:
	.string "{SPEAKER NAME_ANABEL}Here. Kurt's Beast Ball.$"

@ SYSTEM: no plate
UltraSpaceArena_Text_CaptureConfirmed:
	.string "{PLAYER} caught {STR_VAR_1}!$"

UltraSpaceArena_Text_CaptureReturn:
	.string "{SPEAKER NAME_ANABEL}Let's take you both back.$"

UltraSpaceArena_Text_CapturePending:
	.string "{SPEAKER NAME_ANABEL}I'll keep Necrozma with me for now.\p"
	.string "Make room, then speak to me\n"
	.string "at the altar.$"

@ NARRATOR: no plate. The loop document replaces the script that shows it.
UltraSpaceArena_Text_EmptySurvey:
	.string "The chamber is quiet.\n"
	.string "The passage behind you remains open.$"
