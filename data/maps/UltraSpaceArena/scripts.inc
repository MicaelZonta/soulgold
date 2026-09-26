@ ===========================================================================
@ Ultra Space Arena - ACT IV of the Sun and Moon Altar event, and the room the
@ post-game daily rift leads to. Plan: .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md
@
@ Reached ONLY through the altar rift, which always lands the player on (10,19)
@ facing up. State 14 is the confrontation; state >= 16 is the empty daily
@ expedition, which is the handoff to the loop document.
@ ===========================================================================

UltraSpaceArena_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, UltraSpaceArena_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, UltraSpaceArena_OnFrame
	.byte 0

@ Everything in this map is hidden on every load, unconditionally. The only thing
@ that shows an object here is a scene, and the only scene here is the
@ confrontation. This is what makes the blackout retry free: the player wakes up
@ in a Pokemon Center, flies back to the altar, walks into the rift again, and the
@ map is exactly as it was the first time.
UltraSpaceArena_OnTransition::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	end

@ A frame trigger and not a coord_event, because the choreography of this act has
@ to know EXACTLY where the player is: Anabel and the partner come up the corridor
@ in the neighbouring columns and stop beside him. A coord_event on a three-tile
@ row leaves three possible positions and one of them puts an NPC on top of the
@ player. The frame trigger fires on the load, when the player is still on the
@ warp tile (10,19) by construction.
UltraSpaceArena_OnFrame::
	map_script_2 VAR_TEMP_1, 0, UltraSpaceArena_EventScript_ArrivalTrigger
	.2byte 0

@ VAR_TEMP_1 is the once-per-visit latch and is set FIRST: a map_script_2 is
@ re-evaluated every frame and enqueueing the script re-locks the controls every
@ frame, so a condition that stays true is a livelock, not a crash.
@ The getplayerxy guard is belt and braces, not logic: the rift is the only way
@ in and it always lands on (10,19). If some future entrance lands elsewhere, the
@ scene declines instead of walking two NPCs into a wall.
UltraSpaceArena_EventScript_ArrivalTrigger::
	setvar VAR_TEMP_1, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 10, UltraSpaceArena_EventScript_End
	goto_if_ne VAR_0x8005, 19, UltraSpaceArena_EventScript_End
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, UltraSpaceArena_EventScript_Confront
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, UltraSpaceArena_EventScript_EmptyRift
UltraSpaceArena_EventScript_End::
	end

@ SKELETON: state >= 16, the daily rift, with nothing in it yet. One box, no
@ lock on state, no objects. THIS IS THE HANDOFF TO THE LOOP DOCUMENT -
@ replacing this script is the first thing that document does. The expedition
@ itself (five trainers plus a legendary) is deliberately out of scope here.
@
@ The opening (lockall / hidefollower / delay 20) is the same as the Act IV
@ confrontation's on purpose, and the delay is not cosmetic: this script runs off
@ MAP_SCRIPT_ON_FRAME_TABLE on the first frame after a warp that is unique in the
@ whole game. MAP_ULTRA_SPACE_ARENA is the ONLY one of the 243 MAP_TYPE_UNDERGROUND
@ maps that is entered with warpsilent instead of a warp event, and the pair
@ MAP_TYPE_ROUTE -> MAP_TYPE_UNDERGROUND is in sTransitionTypes
@ (src/fldeff_flash.c), so the engine plays the enter-cave transition: the screen
@ is faded TO WHITE on the way out and the cave iris runs before the map appears.
@ Anything that runs before that has finished runs against a white screen.
UltraSpaceArena_EventScript_EmptyRift::
	lockall
	hidefollower
	delay 20
	@ The warp lands the player on (10,19) facing SOUTH, which is one step from
	@ the coord_event row at y=20 that throws him straight back out - arriving
	@ already pointing at the exit. Turn him to face the arena before releasing.
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox UltraSpaceArena_Text_EmptyRift, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ ---------------------------------------------------------------------------
@ ACT IV. Choreography, measured on dump_mapa.py UltraSpaceArena:
@   player  (10,19) -> walk_up x8 -> (10,11), facing up
@   Anabel  addobject (11,19) -> walk_up x8 -> (11,11)
@   partner addobject (9,19)  -> walk_up x8 -> (9,11)
@ The three end up abreast on y=11, the bottom row of the arena. The corridor is
@ exactly three tiles wide (x=9..11) from y=15 to y=19 and opens out above that,
@ so the three columns never cross and nobody has to path around anybody.
@ The creature is at (10,8), three rows north of the player: inside the frame and
@ well clear of the text box, which covers the BOTTOM of the screen - nobody who
@ has to be seen is ever south of the player here.
@ waitmovement 0 is NEVER used with two actors moving: it waits for only one of
@ them (skill parceiro-pokemon-de-npc). Every actor is waited on by local id.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Confront::
	lockall
	hidefollower
	delay 20
	call UltraSpaceArena_EventScript_ShowEscort
	applymovement OBJ_EVENT_ID_PLAYER, UltraSpaceArena_Movement_PlayerUp
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, UltraSpaceArena_Movement_EscortUp
	call UltraSpaceArena_EventScript_MovePartnerUp
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	call UltraSpaceArena_EventScript_WaitPartner
	msgbox UltraSpaceArena_Text_ArenaLook, MSGBOX_DEFAULT
	closemessage
	@ --- it is already here, and it is exactly what New Bark left ---------
	@ It burst on the ninth beast in New Bark (NewBarkTown_EventScript_UBUltra)
	@ and it LEFT golden - nobody ever took that light back off it. So the only
	@ form that exists on this floor during Act IV is the Ultra one, and there
	@ is no second transformation to play here.
	@ LOCALID_ULTRA_SPACE_ARENA_NECROZMA is NOT spawned during this act at all:
	@ the small form is what LOSING the light looks like, and the only script
	@ that adds it is UltraSpaceArena_EventScript_Victory. Its FLAG_TEMP_2 stays
	@ set from ON_TRANSITION right through the battle.
	fadescreenswapbuffers FADE_TO_WHITE
	addobject LOCALID_ULTRA_SPACE_ARENA_ULTRA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_ArenaUltra, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaAnabelReads, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaStarving, MSGBOX_DEFAULT
	closemessage
	@ --- the partner steps in front, and it answers -----------------------
	@ The beat that used to be the transformation. The creature does not change;
	@ it NOTICES. Flare, cry, shake, in that order, and then Anabel moves - so
	@ her "Behind me. Now." is a reaction to something the player just saw.
	@ walk_in_place_fast_down and not _right: it stands on (10,8) facing SOUTH,
	@ at the player on (10,11) and the partner on (9,9). y grows DOWN.
	call UltraSpaceArena_EventScript_PartnerSteps
	applymovement LOCALID_ULTRA_SPACE_ARENA_ULTRA, UltraSpaceArena_Movement_UltraFlare
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ULTRA
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_NORMAL
	waitmoncry
	call UltraSpaceArena_EventScript_Shake
	msgbox UltraSpaceArena_Text_ArenaAnswers, MSGBOX_DEFAULT
	closemessage
	@ --- Anabel gets in front of him, once, the way she always does --------
	@ (11,11) -> (11,10): one row up, beside the player's column, NOT on it.
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, Common_Movement_WalkUp
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	msgbox UltraSpaceArena_Text_ArenaAnabelFront, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaAnabelRead, MSGBOX_DEFAULT
	closemessage
	@ She says where the Beast Ball came from BEFORE the fight, not after. It is
	@ the only place in the whole arc where anybody explains that item, and it is
	@ the hook for .claude/KURT_BALL_CRAFT_DESIGN.md. No giveitem here: she does
	@ not hand one over, she says she asked for them.
	msgbox UltraSpaceArena_Text_ArenaAnabelBall, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaAnabelBallTwo, MSGBOX_DEFAULT
	closemessage
	@ She steps BACK to her anchor tile, (11,10) -> (11,11), and does not move
	@ again for the rest of the act. This is the in-fiction reason she does not
	@ battle: from here on her hands are holding the way home open. Everything
	@ after this box moves the player, the partner or the creature - NEVER her.
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, Common_Movement_WalkDown
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_SOUTH
	msgbox UltraSpaceArena_Text_ArenaAnabelAnchor, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_NORTH
	msgbox UltraSpaceArena_Text_ArenaAnabelAnchorTwo, MSGBOX_DEFAULT
	closemessage
	goto UltraSpaceArena_EventScript_Battle

@ Exactly one legendary, chosen by the party, and its own movement/wait pair. The
@ partner's flags are FLAG_TEMP_4 and FLAG_TEMP_5, so nothing it does can touch
@ Anabel or either Necrozma.
@ The rift refused to let anyone through without Solgaleo or Lunala in the party,
@ so one of the two is always there; Solgaleo is the fallthrough.
UltraSpaceArena_EventScript_ShowEscort::
	addobject LOCALID_ULTRA_SPACE_ARENA_ANABEL
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_ShowLunala
	addobject LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	return
UltraSpaceArena_EventScript_ShowLunala::
	addobject LOCALID_ULTRA_SPACE_ARENA_LUNALA
	return

UltraSpaceArena_EventScript_MovePartnerUp::
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_MoveLunalaUp
	applymovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO, UltraSpaceArena_Movement_EscortUp
	return
UltraSpaceArena_EventScript_MoveLunalaUp::
	applymovement LOCALID_ULTRA_SPACE_ARENA_LUNALA, UltraSpaceArena_Movement_EscortUp
	return

UltraSpaceArena_EventScript_WaitPartner::
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_WaitLunala
	waitmovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	return
UltraSpaceArena_EventScript_WaitLunala::
	waitmovement LOCALID_ULTRA_SPACE_ARENA_LUNALA
	return

@ The partner walks two tiles up its own column, to (9,9), ending BESIDE the
@ creature's column instead of on it, and turns east to face it. It is putting
@ itself between the thing and the player, and it does it without being told.
UltraSpaceArena_EventScript_PartnerSteps::
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_LunalaSteps
	applymovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO, UltraSpaceArena_Movement_PartnerForward
	waitmovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	waitmoncry
	return
UltraSpaceArena_EventScript_LunalaSteps::
	applymovement LOCALID_ULTRA_SPACE_ARENA_LUNALA, UltraSpaceArena_Movement_PartnerForward
	waitmovement LOCALID_ULTRA_SPACE_ARENA_LUNALA
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	waitmoncry
	return

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

UltraSpaceArena_Movement_EscortUp:
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

UltraSpaceArena_Movement_PartnerForward:
	walk_up
	walk_up
	face_right
	step_end

@ Four fast steps in place, facing SOUTH, the same shape as
@ NewBarkTown_Movement_UltraFlare. It does not move off (10,8) and it does not
@ change the direction it is looking - it just burns harder for a second.
UltraSpaceArena_Movement_UltraFlare:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

@ Same four vars as the altar and as the four mission maps: pan, pan, count,
@ delay. Passing only two gives the shake a random duration.
UltraSpaceArena_EventScript_Shake::
	setvar VAR_0x8004, 1    @ vertical pan
	setvar VAR_0x8005, 1    @ horizontal pan
	setvar VAR_0x8006, 12   @ num shakes
	setvar VAR_0x8007, 4    @ shake delay
	special ShakeCamera
	waitstate
	return

@ ---------------------------------------------------------------------------
@ THREAT battle, not a character duel: B_FLAG_NO_WHITEOUT is deliberately NOT
@ set. Losing is a blackout and a retry, which is the arc's rule from Blackthorn
@ on, and the retry is free because the state stays 14 and this map's
@ ON_TRANSITION puts everything back.
@ Difficulty, continuing the scale: M1 3 bars/Lv75/x120, M2 4/Lv80/x130,
@ M3 4/x140, M4 4/x150, and this one 5/Lv90/x160 with a phase profile. It is the
@ only battle in the arc with a phase profile, and it should be.
@
@ FIVE phases in sNecrozmaBossPhases (src/battle_boss.c) means FIVE bars here:
@ IsBossPhaseProfileValid silently discards a profile whose phaseCount differs
@ from totalBars and the fight quietly becomes a plain five-bar boss.
@
@ B_FLAG_NO_CATCHING: the fight is a fight. The capture is a scene, and that is
@ what makes "beat it but fail to catch it" impossible - a lost catch can never
@ make Necrozma permanently unavailable. The engine clears the flag after the
@ battle by itself.
@
@ No seteventmonmoves: TryStartBossBattle applies phases[0] - species AND moves -
@ at the start of the battle, so writing the moveset here would only create two
@ sources of truth for the same four moves.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Battle::
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

@ LOST, DREW and FORFEITED never come back here: the engine blacks the player
@ out. CAUGHT and RAN are unreachable (the Ball is blocked, and Run in a boss
@ becomes FORFEITED) but are handled anyway: anything that is not WON resets the
@ scene, never wins it. Nothing is recorded, the state is still 14, and
@ ON_TRANSITION puts this map back the way it was.
UltraSpaceArena_EventScript_Unresolved::
	msgbox UltraSpaceArena_Text_Unresolved, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ The player won. Everything from here is scripted; there is no way to lose the
@ Pokemon from this point.
@ Party space was checked at the rift, before the player ever crossed, and the
@ defensive guard below covers the impossible case.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Victory::
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_ULTRA_SPACE_ARENA_ULTRA
	addobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_VictoryArmourOff, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_VictoryAnabel, MSGBOX_DEFAULT
	closemessage
	@ --- the partner does the thing nobody planned ------------------------
	call UltraSpaceArena_EventScript_PartnerHarmonise
	msgbox UltraSpaceArena_Text_VictoryHarmony, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_VictoryBall, MSGBOX_DEFAULT
	closemessage
	@ --- the capture, on screen -------------------------------------------
	@ The space check is repeated here, one box before the Ball leaves her hand,
	@ and not after the gift like it used to be: from this line on the scene says
	@ out loud that the creature is IN the Ball, and the defensive NoRoom branch
	@ has to fire before that is true, not after. Same test as the rift's
	@ (SunMoonAltar_EventScript_Rift): only party full AND PC full blocks.
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, UltraSpaceArena_EventScript_CaptureGo
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_ne VAR_RESULT, TRUE, UltraSpaceArena_EventScript_NoRoom
UltraSpaceArena_EventScript_CaptureGo::
	call UltraSpaceArena_EventScript_Capture
	@ --- the gift ----------------------------------------------------------
	@ SPECIES_NECROZMA and not SPECIES_NECROZMA_ULTRA: the Ultra/Dusk Mane/Dawn
	@ Wings forms are battle forms. Level 75 and not 90 because what the player
	@ receives is the creature AFTER it lost the light - giving level 90 would be
	@ handing over the boss instead of what was left of it.
	@
	@ THE TWO LINES ABOVE givemon ARE NOT DECORATION. Nothing in the givemon path
	@ writes STR_VAR_1: Common_Text_ReceivedMon is literally "{PLAYER} received
	@ {STR_VAR_1}!" and prints whatever was in the buffer. Without them the box
	@ said "received SOLGALEO", because UltraSpaceArena_EventScript_PartnerHarmonise
	@ had just buffered the partner's name for Text_VictoryHarmony - a clean build
	@ announcing the wrong Pokemon. VAR_TEMP_TRANSFERRED_SPECIES is what
	@ Common_EventScript_TransferredToPC reads for the box message, and it is the
	@ same var as VAR_TEMP_1 (include/constants/vars.h), which this map uses as the
	@ once-per-visit latch of UltraSpaceArena_OnFrame: writing SPECIES_NECROZMA
	@ into it keeps it non-zero, so the latch stays closed. Do not write 0 here.
	@ The MON_CANT_GIVE guard comes BEFORE the call, not after:
	@ Common_EventScript_GiftMon swallows MON_CANT_GIVE in silence. Comparing does
	@ not dirty VAR_RESULT, so the call still sees the givemon result.
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_NECROZMA
	bufferspeciesname STR_VAR_1, SPECIES_NECROZMA
	givemon SPECIES_NECROZMA, 75, ITEM_NONE
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, UltraSpaceArena_EventScript_NoRoom
	call Common_EventScript_GiftMon
	@ the Ball goes with the player
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox UltraSpaceArena_Text_VictoryLeave, MSGBOX_DEFAULT
	closemessage
	goto UltraSpaceArena_EventScript_NecrozmaCaught

@ ---------------------------------------------------------------------------
@ THE CAPTURE. It is a scene and not a message, which is the whole reason
@ B_FLAG_NO_CATCHING is set during the fight: the player cannot fail this and
@ cannot miss it either.
@ enter_pokeball is the engine's own "goes into the Ball" movement action
@ (MOVEMENT_ACTION_ENTER_POKEBALL): the sprite flashes white, shrinks into a ball
@ and ends invisible. It is what a follower does going back in, and it works on
@ any object whose graphics are OBJ_EVENT_GFX_SPECIES(...) - FollowerSetGraphics
@ reads the species out of the graphicsId and assumes nothing about followers.
@ The Ball that stays on the floor afterwards is a SEPARATE object, because the
@ engine's animation leaves nothing behind to rock: it is
@ LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL, standing on (10,8), the creature's own
@ tile, so the Ball lands exactly where it was.
@ The three shakes and the click are sound only (SE_BALL x3, then SE_BALL_OPEN),
@ which is what the battle capture sounds like and costs no animation that could
@ desync. MUS_HG_CAUGHT comes after the click, not after the gift box, so the
@ fanfare lands on the moment the Ball stops moving.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Capture::
	playse SE_BALL_THROW
	delay 16
	applymovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA, UltraSpaceArena_Movement_EnterBall
	waitmovement LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	removeobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	addobject LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL
	delay 20
	call UltraSpaceArena_EventScript_BallShake
	call UltraSpaceArena_EventScript_BallShake
	call UltraSpaceArena_EventScript_BallShake
	playse SE_BALL_OPEN
	delay 30
	playfanfare MUS_HG_CAUGHT
	waitfanfare
	msgbox UltraSpaceArena_Text_VictoryCaught, MSGBOX_DEFAULT
	closemessage
	return

UltraSpaceArena_EventScript_BallShake::
	playse SE_BALL
	delay 40
	return

UltraSpaceArena_Movement_EnterBall:
	enter_pokeball
	step_end

@ Should be unreachable: the rift refused to let a full player through. It is here
@ because a gift that fails silently is the worst bug this project knows how to
@ write, and because a future edit could move the check.
@ NOTHING is marked: the state stays 14, the player is sent back to the altar,
@ and the whole act is replayable. No progress is lost.
UltraSpaceArena_EventScript_NoRoom::
	msgbox UltraSpaceArena_Text_NoRoom, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ State and warp together, under the fade, in the arc's order:
@ fadescreen, setvar, warpsilent, waitstate, releaseall, end.
@ (14,11) is free, elevation 3, one tile SOUTH of the rift at (14,10) - so the
@ player comes out of the tear facing it and does not respawn inside the object.
@ The altar's ON_TRANSITION then paints state 15 and its frame trigger, which
@ tests for exactly this tile, opens Act V.
UltraSpaceArena_EventScript_NecrozmaCaught::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 15
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ One tile up its own column, to (9,8), so it ends up beside the small thing
@ instead of on it, and it turns back to face the tear: it is holding the passage
@ open from the inside while everyone leaves. (9,8) is free (dump_mapa.py: y=8 is
@ walkable from x=6 to x=14).
UltraSpaceArena_EventScript_PartnerHarmonise::
	bufferspeciesname STR_VAR_1, VAR_TEMP_4   @ Text_VictoryHarmony prints it
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_LunalaHarmonise
	applymovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO, UltraSpaceArena_Movement_PartnerHarmonise
	waitmovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	waitmoncry
	call UltraSpaceArena_EventScript_Shake
	return
UltraSpaceArena_EventScript_LunalaHarmonise::
	applymovement LOCALID_ULTRA_SPACE_ARENA_LUNALA, UltraSpaceArena_Movement_PartnerHarmonise
	waitmovement LOCALID_ULTRA_SPACE_ARENA_LUNALA
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	waitmoncry
	call UltraSpaceArena_EventScript_Shake
	return

UltraSpaceArena_Movement_PartnerHarmonise:
	walk_up
	face_down
	step_end

@ Her object script. She is reachable between the confrontation and the battle
@ only in theory (the act runs under lockall from end to end), but the object
@ exists and an object with script NULL would be a silent A-press.
UltraSpaceArena_EventScript_Anabel::
	lock
	faceplayer
	msgbox UltraSpaceArena_Text_AnabelHold, MSGBOX_DEFAULT
	release
	end

@ South rift, bottom row of the pad: back to the Sun and Moon Altar.
@ (14,11) and NOT (14,10): (14,10) is where LOCALID_SUN_MOON_ALTAR_RIFT lives
@ from state 14 on, and an object always blocks its own tile - respawning the
@ player on top of one is asking the engine what it does with two occupants.
@ (14,11) is free, elevation 3, not a warp, and leaves the player facing the
@ tear, which is the right reading for somebody who just came out of it.
UltraSpaceArena_EventScript_SouthRift::
	lockall
	playse SE_WARP_IN
	warp MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ ===========================================================================
@ Texts
@ ===========================================================================
@ narration
UltraSpaceArena_Text_ArenaLook:
	.string "There is a floor, and there is light, and\n"
	.string "there is nothing in any direction that\l"
	.string "looks like a direction.\p"
	.string "Somewhere behind, the tear they came\n"
	.string "through is still holding its shape.$"

UltraSpaceArena_Text_ArenaAnabelReads:
	.string "{SPEAKER NAME_ANABEL}There.\p"
	.string "…I want to be careful about how I say\n"
	.string "this, because I have been wrong about\l"
	.string "it for four cities.\p"
	.string "It isn't attacking anything. It never\n"
	.string "was. Look at how it's holding itself.\l"
	.string "That is an animal that has not been full\l"
	.string "in a very long time.$"

UltraSpaceArena_Text_ArenaStarving:
	.string "{SPEAKER NAME_ANABEL}Nine of them, {PLAYER}. Nine, out of four\n"
	.string "towns, and it did not hurt one person\l"
	.string "doing it.\p"
	.string "It has been eating. That's all this has\n"
	.string "ever been.\p"
	.string "…I have spent my whole career learning\n"
	.string "to tell the difference between a threat\l"
	.string "and a thing in trouble, and I have never\l"
	.string "in my life wanted to be wrong about it\l"
	.string "more than right now.$"

@ narration, on the reveal. It is already burning when they get here: this is
@ the same shape that walked out of New Bark, and it never put the light down.
UltraSpaceArena_Text_ArenaUltra:
	.string "It is already burning.\p"
	.string "Whatever it put on in New Bark it has\n"
	.string "not put down, and every piece of that\l"
	.string "armour is something it swallowed in\l"
	.string "Johto.\p"
	.string "It did not take the light the way a\n"
	.string "thief takes something. It took it the\l"
	.string "way a drowning thing takes air.$"

@ narration, after the partner steps in and the creature answers it
UltraSpaceArena_Text_ArenaAnswers:
	.string "The light on it moved once, all of it at\n"
	.string "the same time, the way a held breath\l"
	.string "moves.\p"
	.string "It had not looked at anything on this\n"
	.string "floor until something stepped between\l"
	.string "it and {PLAYER}.$"

UltraSpaceArena_Text_ArenaAnabelFront:
	.string "{SPEAKER NAME_ANABEL}Behind me. Now.\p"
	.string "…Right. It looked at you, and I did that\n"
	.string "without thinking about it, and we are\l"
	.string "both going to pretend that was a plan.$"

UltraSpaceArena_Text_ArenaAnabelRead:
	.string "{SPEAKER NAME_ANABEL}Here is what I have, and then I will get\n"
	.string "out of your way.\p"
	.string "It wants the light. It will come for the\n"
	.string "brightest thing on this floor and it will\l"
	.string "keep coming, and no, that is not a\l"
	.string "prediction -- it is the fourth time I\l"
	.string "have watched it do exactly that.\p"
	.string "So don't give it yours. Take its.$"

@ where the Beast Ball came from, BEFORE the fight. The hook for the Kurt document
UltraSpaceArena_Text_ArenaAnabelBall:
	.string "{SPEAKER NAME_ANABEL}One more thing, and then I will shut up\n"
	.string "and let you work.\p"
	.string "Four years ago I wrote to an old man in\n"
	.string "Azalea Town. I sent him everything the\l"
	.string "International Police had on what a rift\l"
	.string "does to a Pokémon that comes through\l"
	.string "one, and I asked him whether he could\l"
	.string "make something that would hold one\l"
	.string "without hurting it.\p"
	.string "He wrote back in nine days. He called it\n"
	.string "a Beast Ball, and he has been making\l"
	.string "them for me by hand ever since, because\l"
	.string "nobody else in the world knows how.$"

UltraSpaceArena_Text_ArenaAnabelBallTwo:
	.string "{SPEAKER NAME_ANABEL}I have four of them left, and I have\n"
	.string "been carrying them for four cities\l"
	.string "without using one.\p"
	.string "I'm not giving you one yet. Ask me again\n"
	.string "when we know what we're looking at.\p"
	.string "His name is Kurt. If we both walk out of\n"
	.string "here, go to Azalea and tell him they\l"
	.string "work.$"

@ she has turned SOUTH, to the tear, for this box
UltraSpaceArena_Text_ArenaAnabelAnchor:
	.string "{SPEAKER NAME_ANABEL}Listen, because I am about to become\n"
	.string "useless and I would rather you heard\l"
	.string "why from me.\p"
	.string "That tear does not stay open on its\n"
	.string "own. Somebody holds it, from this side,\l"
	.string "and it has to be somebody who has been\l"
	.string "through one. I don't know why. I\l"
	.string "stopped needing to know why on a beach\l"
	.string "in Cherrygrove.\p"
	.string "So this is where I stand. If I let go,\n"
	.string "you don't get home.$"

@ she has turned back NORTH, to the player
UltraSpaceArena_Text_ArenaAnabelAnchorTwo:
	.string "{SPEAKER NAME_ANABEL}Which makes the fight yours. All of it. I\n"
	.string "cannot throw so much as a Poké Ball\l"
	.string "from here and I am not going to try.\p"
	.string "…I have spent twenty years being the\n"
	.string "one who gets in front of things.\l"
	.string "Standing still is the hardest thing\l"
	.string "anyone has asked of me all year.\p"
	.string "Go on, {PLAYER}. I've got the door.$"

@ only reachable via CAUGHT or RAN, which are both blocked
UltraSpaceArena_Text_Unresolved:
	.string "The tear pulled shut, and the floor went\n"
	.string "out from under everything, and the\l"
	.string "altar was there again.$"

@ narration
UltraSpaceArena_Text_VictoryArmourOff:
	.string "The armour came off the way frost\n"
	.string "comes off a window.\p"
	.string "What was left of it was not very large\n"
	.string "at all.$"

UltraSpaceArena_Text_VictoryAnabel:
	.string "{SPEAKER NAME_ANABEL}…Oh.\p"
	.string "That's it? That's what was\n"
	.string "underneath?\p"
	.string "Four towns. Nine of them. And this is\n"
	.string "what has been carrying it around.$"

@ narration, after the partner moves
UltraSpaceArena_Text_VictoryHarmony:
	.string "{STR_VAR_1} walked past {PLAYER}\n"
	.string "without being asked, and put itself\l"
	.string "between the small thing and the tear,\l"
	.string "and stopped.\p"
	.string "The light did not get brighter. It got\n"
	.string "even.\p"
	.string "Somewhere behind them, the way home\n"
	.string "stopped shivering.$"

@ she hands it over here, and this is what she was holding it for
UltraSpaceArena_Text_VictoryBall:
	.string "{SPEAKER NAME_ANABEL}It isn't running.\p"
	.string "…Here. Take it. This is the one I've\n"
	.string "been saving, and I have just worked out\l"
	.string "what I was saving it for.\p"
	.string "Room for one more, {PLAYER}. That was my\n"
	.string "condition in Olivine and this is the\l"
	.string "whole reason it was a condition. Go on.\l"
	.string "Slowly. Nothing has ever carried this\l"
	.string "one anywhere.$"

@ narration
UltraSpaceArena_Text_VictoryCaught:
	.string "It did not fight the Ball.\p"
	.string "It went in the way something goes into\n"
	.string "a house it has been standing outside of\l"
	.string "for a very long time.$"

UltraSpaceArena_Text_VictoryLeave:
	.string "{SPEAKER NAME_ANABEL}Then we're done here.\p"
	.string "Out. Same way. Don't look at anything\n"
	.string "on the way.$"

@ defensive branch, should be unreachable
UltraSpaceArena_Text_NoRoom:
	.string "{SPEAKER NAME_ANABEL}There's nowhere to put it.\p"
	.string "…That is my fault. That was my one job\n"
	.string "and I asked you once and then I\l"
	.string "stopped checking.\p"
	.string "Out. Make room, and we come straight\n"
	.string "back -- it isn't going anywhere, and\l"
	.string "neither am I.$"

@ Post-game, state >= 16. The loop document replaces the script that shows this
UltraSpaceArena_Text_EmptyRift:
	.string "The floor goes on in every direction and\n"
	.string "there is nothing standing on it today.\p"
	.string "Somewhere behind, the way back is still\n"
	.string "open.$"

@ her object script during the fight: she is holding the door and cannot move
UltraSpaceArena_Text_AnabelHold:
	.string "{SPEAKER NAME_ANABEL}Both hands, {PLAYER}. Ask me anything\n"
	.string "you like afterwards.\p"
	.string "Go and finish it.$"
