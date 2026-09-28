@ ===========================================================================
@ Sun and Moon Altar - Ultra Necrozma, the last story event of the Rift
@ Missions arc. Script: .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_sUN_MOON_SCRIPT_V2.md
@ Plan:   .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md (section 21)
@
@ The story in three lines: the team arrives prepared, and Lusamine still wants
@ to be the one who crosses. A duel, and then Lillie asks her to stay and help
@ - and during the rescue of the nine she listens to her daughter and it works.
@
@ Driven by VAR_RIFT_MISSIONS_STATE (the arc) and VAR_RIFT_ALTAR_STEP (the
@ checkpoints inside it, ALTAR_STEP_* in include/constants/vars.h):
@   12 -> 13  Act I, arrival and impasse        (the five stair coord_events)
@   13        duel by talking to Lusamine; DUEL_DONE -> reload -> agreement
@   13 -> 14  Act III, agreement + passage test (frame trigger at (14,12))
@   14        crossing by talking to Anabel/the mark; CROSSING -> reload
@             -> the crossing (frame trigger at (14,11)) -> the arena
@   14/RESCUE the reception cut: the arena warps here mid-scene, the player is
@             hidden, the nine arrive in five groups, back to the arena
@   14/BOSS_SEEN  retry lines on the stair after a lost boss
@   15        Act V: return, stabilization, family, farewell (frame trigger)
@   15/CUSTODY*  Anabel holds Necrozma until there is room
@   >= 16     permanent post-game
@
@ All visibility is FLAG_TEMP_* recomputed on every load (skill
@ visibilidade-e-gatilhos section 6). Temp flags on this map:
@   1 the visitors (Lillie, Ninetales, Gladion, Silvally, Kukui)   5 Lusamine
@   2 rift   3 partner (VAR_2 gfx)   4 dormant mark   6 Anabel
@   7 Necrozma   8/9 the two UB slots (VAR_0/VAR_1 gfx)   A/B the two helpers
@   C Kukui's emitter (11,9)   F Lusamine's emitter (17,9)
@   D Lusamine's long approach already heard this visit
@   E = FLAG_TEMP_HIDE_FOLLOWER (engine), set only for the reception cut
@ NEVER removeobject any object on FLAG_TEMP_1: removeobject SETS the flag and
@ would take the whole group with it. Every other object has a flag of its own.
@ ===========================================================================

SunMoonAltar_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SunMoonAltar_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SunMoonAltar_OnLoad
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SunMoonAltar_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SunMoonAltar_OnFrame
	.byte 0

@ Runs before the first spawn on EVERY load. Nothing here is persisted.
SunMoonAltar_OnTransition::
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	setflag FLAG_TEMP_9
	setflag FLAG_TEMP_A
	setflag FLAG_TEMP_B
	call SunMoonAltar_EventScript_ApplyCastVisibility
	call SunMoonAltar_EventScript_ApplyLusamineVisibility
	call SunMoonAltar_EventScript_ApplyEmitters
	call SunMoonAltar_EventScript_ApplyRiftVisibility
	call SunMoonAltar_EventScript_ApplyWeather
	call SunMoonAltar_EventScript_ApplyResidents
	call SunMoonAltar_EventScript_ApplyPartnerGfx
	call_if_eq VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_ShowHelpers
	call_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_ShowHelpers
	call_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_ApplyReturnStage
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RESCUE, SunMoonAltar_EventScript_ApplyRescueStage
	@ state 14 outside the cut: Anabel waits beside the mark, so she and the
	@ mark are ONE place to start a crossing (V2 section 17)
	setobjectxyperm LOCALID_SUN_MOON_ALTAR_ANABEL, 15, 10
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_ANABEL, MOVEMENT_TYPE_FACE_LEFT
	end

@ setmetatile must hang off ON_LOAD: gBackupMapLayout only exists after
@ InitMap, which is what calls this script (src/fieldmap.c).
SunMoonAltar_OnLoad::
	call SunMoonAltar_EventScript_ApplyDisc
	end

@ The reception cut: the player is in the arena, not here. The warp still has
@ to put the player object somewhere, so it lands on (16,13) - the tile that
@ frames the rift, the terrace and the stair base - and is hidden BEFORE the
@ fade-in. hideobjectat resolves OBJ_EVENT_ID_PLAYER through
@ GetObjectEventIdByLocalId (src/event_object_movement.c) and runs immediately,
@ which is what this table is for. The warp back to the arena rebuilds a
@ visible player on its own.
SunMoonAltar_OnWarp::
	map_script_2 VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RESCUE, SunMoonAltar_EventScript_HidePlayer
	.2byte 0

SunMoonAltar_EventScript_HidePlayer::
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_SUN_MOON_ALTAR
	end

@ The visitors: 12..15, gone for good from 16. A window closed on both sides.
SunMoonAltar_EventScript_ApplyCastVisibility::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_HideCast
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_HideCast
	clearflag FLAG_TEMP_1
	return
SunMoonAltar_EventScript_HideCast::
	setflag FLAG_TEMP_1
	return

@ Lusamine: with the cast in 12..15, then Monday, Wednesday and Saturday
@ (Olivine takes Sunday and Friday; nobody is in two places on one day).
SunMoonAltar_EventScript_ApplyLusamineVisibility::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_HideLusamine
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_ShowLusamine
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_MON, SunMoonAltar_EventScript_ShowLusamine
	goto_if_eq VAR_RESULT, WEEKDAY_WED, SunMoonAltar_EventScript_ShowLusamine
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, SunMoonAltar_EventScript_ShowLusamine
SunMoonAltar_EventScript_HideLusamine::
	setflag FLAG_TEMP_5
	return
SunMoonAltar_EventScript_ShowLusamine::
	clearflag FLAG_TEMP_5
	return

@ The two emitters of the outside unit: Kukui's on the west side of the
@ opening (11,9), Lusamine's on the east side (17,9). Own flags, so they can be
@ switched independently of the people:
@   12..14     both - the operation is running
@   15         neither - Act V is the fullest moment of the map (Necrozma and
@              the partner join 12 objects) and the sprite palettes are at the
@              limit: two more palette tags would recolour somebody. By the
@              return the units have already been powered down.
@   >= 16      Lusamine's alone, on her days (after ApplyLusamineVisibility)
SunMoonAltar_EventScript_ApplyEmitters::
	setflag FLAG_TEMP_C
	setflag FLAG_TEMP_F
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_Return
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_Return
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LusamineEmitter
	clearflag FLAG_TEMP_C
	clearflag FLAG_TEMP_F
	return
SunMoonAltar_EventScript_LusamineEmitter::
	goto_if_set FLAG_TEMP_5, SunMoonAltar_EventScript_Return
	clearflag FLAG_TEMP_F
	return

@ (14,10) has two objects and at most one of them is ever visible:
@   14         the dormant MARK - the test is over and nobody holds anything
@              open while the player prepares (V2 section 10). Except during
@              the reception cut, when the partner holds it open from inside.
@   15         the RIFT, still oscillating until Act V steadies it
@   >= 16      the RIFT, always: the way into the Nexus, which can be entered
@              any number of times a day (NEXUS_REGRAS R3)
@   <= 13      neither
SunMoonAltar_EventScript_ApplyRiftVisibility::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_4
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_Return
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_ShowRift
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_DailyRift
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RESCUE, SunMoonAltar_EventScript_ShowRift
	clearflag FLAG_TEMP_4
	return
SunMoonAltar_EventScript_DailyRift::
SunMoonAltar_EventScript_ShowRift::
	clearflag FLAG_TEMP_2
SunMoonAltar_EventScript_Return::
	return

@ Looker and Anabel LIVE here from 16 on, so they wander (range 1, measured:
@ neither reaches (14,10) or (14,11), and the neck at y=12 stays open).
@ setobjectmovementtype writes the TEMPLATE, so it only works from here.
SunMoonAltar_EventScript_ApplyResidents::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_Return
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_LOOKER, MOVEMENT_TYPE_WANDER_AROUND
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_ANABEL, MOVEMENT_TYPE_WANDER_AROUND
	return

@ The partner object is ONE object whose sprite is VAR_OBJ_GFX_ID_2, resolved
@ at spawn (GetObjectEventGraphicsInfo). The species comes from
@ VAR_RIFT_ALTAR_PARTNER, written by the duel and by every crossing, so the
@ arena and this map always show the same Pokemon. Solgaleo is the fallthrough.
SunMoonAltar_EventScript_ApplyPartnerGfx::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_SPECIES(SOLGALEO)
	goto_if_ne VAR_RIFT_ALTAR_PARTNER, SPECIES_LUNALA, SunMoonAltar_EventScript_Return
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_SPECIES(LUNALA)
	return

@ 13..15 is the unstable chapter: ash, and the disc showing its tear.
SunMoonAltar_EventScript_ApplyWeather::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_WeatherCalm
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_WeatherCalm
	setweather WEATHER_VOLCANIC_ASH
	return
SunMoonAltar_EventScript_WeatherCalm::
	setweather WEATHER_NONE
	return

SunMoonAltar_EventScript_ApplyDisc::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_DiscToCalm
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_DiscToCalm
	goto SunMoonAltar_EventScript_DiscToPortal

@ Seven metatiles baked into gTileset_AltarSunMoon, impassable in both states.
@ The calm disc swaps sun/moon with the hour (palettes 9/10); the tear (palette
@ 11) looks the same at both hours on purpose.
SunMoonAltar_EventScript_DiscToPortal::
	setmetatile 13, 5, 1136, TRUE
	setmetatile 14, 5, 1137, TRUE
	setmetatile 15, 5, 1138, TRUE
	setmetatile 13, 6, 1139, TRUE
	setmetatile 14, 6, 1140, TRUE
	setmetatile 15, 6, 1141, TRUE
	setmetatile 14, 7, 1142, TRUE
	special DrawWholeMapView
	return

SunMoonAltar_EventScript_DiscToCalm::
	setmetatile 13, 5, 1037, TRUE
	setmetatile 14, 5, 1038, TRUE
	setmetatile 15, 5, 1039, TRUE
	setmetatile 13, 6, 1041, TRUE
	setmetatile 14, 6, 1042, TRUE
	setmetatile 15, 6, 1043, TRUE
	setmetatile 14, 7, 1045, TRUE
	special DrawWholeMapView
	return

@ The two Aether/police helpers at the stair base, (15,17) and (13,17). Act I
@ (state 12) and the reception cut; then they STAY for good from 16 on - the
@ island keeps a small crew, and the Aether staff is where the player heals
@ (Looker's heal is 13..15 only, so he and Anabel can be moved to other
@ stories without taking the island's heal with them). No biography.
SunMoonAltar_EventScript_ShowHelpers::
	clearflag FLAG_TEMP_A
	clearflag FLAG_TEMP_B
	return

SunMoonAltar_EventScript_Officer::
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_OfficerPost
	msgbox SunMoonAltar_Text_Officer, MSGBOX_NPC
	end
SunMoonAltar_EventScript_OfficerPost::
	msgbox SunMoonAltar_Text_OfficerPost, MSGBOX_NPC
	end

SunMoonAltar_EventScript_AetherStaff::
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_AetherStaffHeal
	msgbox SunMoonAltar_Text_AetherStaff, MSGBOX_NPC
	end

SunMoonAltar_EventScript_AetherStaffHeal::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_AetherHealAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_AetherNoHeal
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SunMoonAltar_Text_AetherHealDone, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_AetherNoHeal::
	msgbox SunMoonAltar_Text_AetherHealNo, MSGBOX_DEFAULT
	release
	end

@ Camera pans. The courtyard is deep: from the stair row (y=14) the outside
@ unit at y=9 is off the top of the screen. Three tiles up puts rows 7..13
@ above the text box - Lusamine, Kukui, Lillie, Gladion, Anabel and Looker all
@ in frame. Always paired: the camera object is removed only after it has slid
@ back onto the player, or the view would snap.
SunMoonAltar_EventScript_CameraToBase::
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, SunMoonAltar_Movement_CameraUp3
	waitmovement OBJ_EVENT_ID_CAMERA
	return

SunMoonAltar_EventScript_CameraToPlayer::
	applymovement OBJ_EVENT_ID_CAMERA, SunMoonAltar_Movement_CameraDown3
	waitmovement OBJ_EVENT_ID_CAMERA
	special RemoveCameraObject
	return

SunMoonAltar_Movement_CameraUp3:
	slide_up
	slide_up
	slide_up
	step_end

SunMoonAltar_Movement_CameraDown3:
	slide_down
	slide_down
	slide_down
	step_end

@ State 15: Anabel came out of the rift with the player and stands at the neck,
@ (15,12), clear of the tear and of the player's tile (14,11). Nihilego - the
@ last one through - is visible at a distance in the reception area, (13,16):
@ one received Pokemon, never nine sprites (V2 section 15).
SunMoonAltar_EventScript_ApplyReturnStage::
	setobjectxyperm LOCALID_SUN_MOON_ALTAR_ANABEL, 15, 12
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_ANABEL, MOVEMENT_TYPE_FACE_UP
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CUSTODY_WAIT, SunMoonAltar_EventScript_Return
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(NIHILEGO)
	setobjectxyperm LOCALID_SUN_MOON_ALTAR_UB_A, 13, 16
	clearflag FLAG_TEMP_8
	return

@ The reception cut (state 14, ALTAR_STEP_RESCUE). Measured on dump_mapa.py:
@   player  (16,13), hidden - it is the camera: rows 9..18 on screen, 9..15 above
@           the text box; columns 9..23
@   rift    (14,10) - every UB comes out of it and walks down column 14:
@           (14,11) (14,12 neck) (14,13) (14,14) (14,15 stair) (14,16..19)
@   Lillie  (13,15) and Ninetales (12,15), on the stair beside the path
@   Looker  (16,15), on the stair, with the register
@   helpers (15,17) police and (13,17) Aether, flanking the path below the stair
@   Lusamine (16,9) east and Kukui (12,9) west of the opening, each at an emitter; Gladion (16,11) and
@   Silvally (17,11) on the people's side of the corridor - their templates.
@ Anabel and the partner are in the arena: Anabel is hidden (FLAG_TEMP_6, her
@ own flag), the partner is never shown on load. The follower is suppressed
@ by the engine's own flag, so nothing of the player is on this map.
SunMoonAltar_EventScript_ApplyRescueStage::
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_HIDE_FOLLOWER
	clearflag FLAG_TEMP_A
	clearflag FLAG_TEMP_B
	setobjectxyperm LOCALID_SUN_MOON_ALTAR_LILLIE, 13, 15
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_LILLIE, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_SUN_MOON_ALTAR_NINETALES, 12, 15
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_NINETALES, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_SUN_MOON_ALTAR_LOOKER, 16, 15
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_LOOKER, MOVEMENT_TYPE_FACE_LEFT
	end

@ ---------------------------------------------------------------------------
@ Triggers. The stair coord_events (VAR_TEMP_0) and the frame trigger
@ (VAR_TEMP_1) may NOT share a var: the frame trigger sets its own on every
@ load, which would kill the coord_event condition for good.
@ ---------------------------------------------------------------------------
SunMoonAltar_OnFrame::
	map_script_2 VAR_TEMP_1, 0, SunMoonAltar_EventScript_FrameTrigger
	.2byte 0

SunMoonAltar_EventScript_StairTrigger::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_Arrival
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_BOSS_SEEN, SunMoonAltar_EventScript_RetryRegroup
	end

@ Every scene that fires on a load is guarded by the state, the step AND the
@ tile the reload put the player on, so no ordinary arrival (pier, Fly, the
@ Unresolved warp) can start one.
SunMoonAltar_EventScript_FrameTrigger::
	setvar VAR_TEMP_1, 1
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_FrameState13
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_FrameState14
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_FrameState15
SunMoonAltar_EventScript_End::
	end

SunMoonAltar_EventScript_FrameState13::
	goto_if_ne VAR_RIFT_ALTAR_STEP, ALTAR_STEP_DUEL_DONE, SunMoonAltar_EventScript_End
	goto_if_ne VAR_0x8004, 14, SunMoonAltar_EventScript_End
	goto_if_ne VAR_0x8005, 12, SunMoonAltar_EventScript_End
	goto SunMoonAltar_EventScript_Agreement

SunMoonAltar_EventScript_FrameState14::
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RESCUE, SunMoonAltar_EventScript_Rescue
	goto_if_ne VAR_0x8004, 14, SunMoonAltar_EventScript_End
	goto_if_ne VAR_0x8005, 11, SunMoonAltar_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CROSSING, SunMoonAltar_EventScript_Crossing
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RECROSSING, SunMoonAltar_EventScript_Crossing
	end

SunMoonAltar_EventScript_FrameState15::
	goto_if_ne VAR_0x8004, 14, SunMoonAltar_EventScript_End
	goto_if_ne VAR_0x8005, 11, SunMoonAltar_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CUSTODY_WAIT, SunMoonAltar_EventScript_End
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_DELIVERED, SunMoonAltar_EventScript_Stabilize
	goto SunMoonAltar_EventScript_Return15

@ ShakeCamera reads FOUR vars: pan, pan, count, delay. Two leaves a random
@ duration. Short and controlled (V2 section 20).
SunMoonAltar_EventScript_Shake::
	setvar VAR_0x8004, 1
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 8
	setvar VAR_0x8007, 4
	special ShakeCamera
	waitstate
	return

@ Flashes that come back to THIS map are fadescreenswapbuffers, never
@ fadescreen: fadescreen composes the time-of-day tint onto itself and the
@ altar gets darker with every flash after dusk.
SunMoonAltar_EventScript_Flash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

@ The communicator: a sound, not a name. The plate says who speaks (V2 section 2).
SunMoonAltar_EventScript_Comm::
	playse SE_POKENAV_CALL
	waitse
	return

@ The partner comes out of its Ball, visibly, and cries. hidefollower first in
@ every caller, so the same Pokemon is never on the map twice.
SunMoonAltar_EventScript_PartnerOut::
	addobject LOCALID_SUN_MOON_ALTAR_PARTNER
	applymovement LOCALID_SUN_MOON_ALTAR_PARTNER, SunMoonAltar_Movement_ExitBall
	waitmovement LOCALID_SUN_MOON_ALTAR_PARTNER
	playmoncry VAR_RIFT_ALTAR_PARTNER, CRY_MODE_ENCOUNTER
	waitmoncry
	return

SunMoonAltar_EventScript_PartnerBack::
	applymovement LOCALID_SUN_MOON_ALTAR_PARTNER, SunMoonAltar_Movement_EnterBall
	waitmovement LOCALID_SUN_MOON_ALTAR_PARTNER
	removeobject LOCALID_SUN_MOON_ALTAR_PARTNER
	return

SunMoonAltar_EventScript_PartnerPulse::
	applymovement LOCALID_SUN_MOON_ALTAR_PARTNER, SunMoonAltar_Movement_Pulse
	waitmovement LOCALID_SUN_MOON_ALTAR_PARTNER
	return

SunMoonAltar_Movement_ExitBall:
	exit_pokeball
	face_up
	step_end

SunMoonAltar_Movement_EnterBall:
	enter_pokeball
	step_end

SunMoonAltar_Movement_Pulse:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

@ Somebody working at an instrument: two slow steps in place.
SunMoonAltar_Movement_Adjust:
	walk_in_place_slow_up
	walk_in_place_slow_up
	step_end

@ Which partner opens the passage. Shared by the duel and the crossing.
@ checkspecies walks gPlayerParty only: the PC, Cosmog, Cosmoem and eggs never
@ satisfy it. Out: VAR_RESULT = 0 none in the team, 1 "Not now"/B, 2 chosen
@ (VAR_RIFT_ALTAR_PARTNER written). The menu is a SYSTEM line: no name plate.
SunMoonAltar_EventScript_PickPartner::
	checkspecies SPECIES_SOLGALEO
	copyvar VAR_TEMP_2, VAR_RESULT
	checkspecies SPECIES_LUNALA
	copyvar VAR_TEMP_3, VAR_RESULT
	goto_if_eq VAR_TEMP_2, FALSE, SunMoonAltar_EventScript_PickNoSolgaleo
	goto_if_eq VAR_TEMP_3, FALSE, SunMoonAltar_EventScript_PickSolgaleo
	message SunMoonAltar_Text_PartnerSelect
	waitmessage
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, SunMoonAltar_Text_ChoiceSolgaleo, SunMoonAltar_Text_ChoiceLunala, SunMoonAltar_Text_ChoiceNotNow
	closemessage
	goto_if_eq VAR_RESULT, 0, SunMoonAltar_EventScript_PickSolgaleo
	goto_if_eq VAR_RESULT, 1, SunMoonAltar_EventScript_PickLunala
	setvar VAR_RESULT, 1
	return
SunMoonAltar_EventScript_PickNoSolgaleo::
	goto_if_eq VAR_TEMP_3, TRUE, SunMoonAltar_EventScript_PickLunala
	setvar VAR_RESULT, 0
	return
SunMoonAltar_EventScript_PickSolgaleo::
	setvar VAR_RIFT_ALTAR_PARTNER, SPECIES_SOLGALEO
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_SPECIES(SOLGALEO)
	setvar VAR_RESULT, 2
	return
SunMoonAltar_EventScript_PickLunala::
	setvar VAR_RIFT_ALTAR_PARTNER, SPECIES_LUNALA
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_SPECIES(LUNALA)
	setvar VAR_RESULT, 2
	return

@ Anabel's rule: only team full AND PC full blocks. Out: VAR_RESULT TRUE if a
@ Pokemon can still be received. When there is room NOTHING is said.
SunMoonAltar_EventScript_CheckRoom::
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, SunMoonAltar_EventScript_RoomYes
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	return
SunMoonAltar_EventScript_RoomYes::
	setvar VAR_RESULT, TRUE
	return

@ ---------------------------------------------------------------------------
@ ACT I - arrival and impasse. State 12 -> 13. From the stair coord_events at
@ (12..16, 15): the player steps up to (x,14), any x in 12..16 being free.
@ Measured positions (templates): Looker (13,13), Anabel (15,13), Lusamine
@ (16,9) east and Kukui (12,9) west of the opening, emitters (17,9)/(11,9), Lillie (12,11) and Ninetales
@ (11,11), Gladion (16,11) and Silvally (17,11), helpers (13,17) and (15,17).
@ Nobody stands on (14,10), the future opening, or on column 14 below it.
@ No faceplayer in an automatic scene; every look is a turnobject derived from
@ coordinates (y grows DOWN).
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Arrival::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_PlayerStepUp
	waitmovement OBJ_EVENT_ID_PLAYER
	@ the disc, before any word: irregular turning, dust, weak pulses
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	call SunMoonAltar_EventScript_DiscToPortal
	fadescreenswapbuffers FADE_FROM_WHITE
	setweather WEATHER_VOLCANIC_ASH
	doweather
	delay 30
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, SunMoonAltar_Movement_LookerGreet
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	msgbox SunMoonAltar_Text_ArrivalLooker, MSGBOX_DEFAULT
	closemessage
	@ the camera: the reception area and the helpers at the supplies below
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_SUN_MOON_ALTAR_OFFICER, SunMoonAltar_Movement_WorkLeft
	applymovement LOCALID_SUN_MOON_ALTAR_AETHER, SunMoonAltar_Movement_WorkRight
	waitmovement LOCALID_SUN_MOON_ALTAR_OFFICER
	waitmovement LOCALID_SUN_MOON_ALTAR_AETHER
	delay 20
	@ ...and they leave the frame before the full scenes; they come back only
	@ for the reception cut. Own flags (A/B), so removeobject is safe.
	applymovement LOCALID_SUN_MOON_ALTAR_OFFICER, SunMoonAltar_Movement_HelperLeave
	applymovement LOCALID_SUN_MOON_ALTAR_AETHER, SunMoonAltar_Movement_HelperLeave
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	@ the camera leaves the player and frames the outside unit (y=9) for the
	@ whole impasse; it comes back down only for Looker's release line
	call SunMoonAltar_EventScript_CameraToBase
	@ the outside unit: Lusamine adjusts controls, Kukui watches the indicator
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	waitmovement LOCALID_SUN_MOON_ALTAR_OFFICER
	waitmovement LOCALID_SUN_MOON_ALTAR_AETHER
	removeobject LOCALID_SUN_MOON_ALTAR_OFFICER
	removeobject LOCALID_SUN_MOON_ALTAR_AETHER
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_SOUTH
	msgbox SunMoonAltar_Text_ArrivalKukui, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_NORTH
	@ Anabel sets the portable unit down beside the outside unit:
	@ (15,13) -> (15,12) -> (15,11) -> (15,10), facing the base at (16,9)
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, SunMoonAltar_Movement_AnabelToBase
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	msgbox SunMoonAltar_Text_ArrivalAnabel, MSGBOX_DEFAULT
	closemessage
	@ Lusamine finishes the adjustment before she answers
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_ArrivalLusamine, MSGBOX_DEFAULT
	closemessage
	@ Kukui (12,9) to Lusamine (16,9): east, across the opening
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_EAST
	msgbox SunMoonAltar_Text_ArrivalKukuiLimit, MSGBOX_DEFAULT
	closemessage
	@ she looks at the module Anabel carries: (15,10) is WEST-SOUTH of (16,9)
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_WEST
	msgbox SunMoonAltar_Text_ArrivalLusamineInsists, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_EAST
	msgbox SunMoonAltar_Text_ArrivalAnabelPlan, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLusamineFear, MSGBOX_DEFAULT
	closemessage
	@ Lillie leaves Ninetales by the prepared area and comes along the free
	@ row: (12,11) -> (15,11), right under Anabel (15,10) and one tile from her
	@ mother's corner. (16,11) is Gladion, (15,10) is Anabel: row 11 is the way.
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_LillieUp
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	msgbox SunMoonAltar_Text_ArrivalLillie, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	delay 30
	msgbox SunMoonAltar_Text_ArrivalLusamineChildren, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_NORTH
	msgbox SunMoonAltar_Text_ArrivalGladion, MSGBOX_DEFAULT
	closemessage
	@ back to the equipment, without leaving the conversation
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_NORTH
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_ArrivalLusaminePause, MSGBOX_DEFAULT
	closemessage
	@ everybody back to the tile their template names, so the map after
	@ releaseall is the map every later load builds
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_NORTH
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_NORTH
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_NORTH
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_LillieBack
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, SunMoonAltar_Movement_AnabelFromBase
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	call SunMoonAltar_EventScript_CameraToPlayer
	msgbox SunMoonAltar_Text_ArrivalLookerRelease, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_NORTH
	@ No reload: the population did not change (the helpers' own flags are set
	@ by removeobject and every later load sets them again). The Fly
	@ destination is switched on HERE, not at the pier.
	setvar VAR_RIFT_MISSIONS_STATE, 13
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_NONE
	setflag FLAG_VISITED_SUN_MOON_ALTAR
	releaseall
	end

SunMoonAltar_Movement_PlayerStepUp:
	walk_up
	face_up
	step_end

@ Looker, (13,13): an exclamation and he turns down to the stair
SunMoonAltar_Movement_LookerGreet:
	emote_exclamation_mark
	face_down
	step_end

SunMoonAltar_Movement_WorkLeft:
	walk_in_place_slow_left
	walk_in_place_slow_left
	step_end

SunMoonAltar_Movement_WorkRight:
	walk_in_place_slow_right
	walk_in_place_slow_right
	step_end

@ down the path, out of the frame: (x,17) -> (x,21), both columns open sand
SunMoonAltar_Movement_HelperLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SunMoonAltar_Movement_AnabelToBase:
	walk_up
	walk_up
	walk_up
	face_right
	step_end

SunMoonAltar_Movement_AnabelFromBase:
	walk_down
	walk_down
	walk_down
	face_up
	step_end

@ (12,11) -> (15,11), facing up at her mother's side of the terrace
SunMoonAltar_Movement_LillieUp:
	walk_right
	walk_right
	walk_right
	face_up
	step_end

SunMoonAltar_Movement_LillieBack:
	walk_left
	walk_left
	walk_left
	face_up
	step_end

@ ---------------------------------------------------------------------------
@ State 13: the duel. Talking to Lusamine. The partner is REQUIRED before the
@ duel (V2 section 7, last paragraph): the fight leads straight into opening
@ the passage, so it does not start without a Pokemon able to open it.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Lusamine::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LusaminePost
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_LusamineReady
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_LusamineReady
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_LusamineReady
	@ a valid duel already happened: never fight again, resume the agreement
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_DUEL_DONE, SunMoonAltar_EventScript_ResumeAgreement
	@ the long approach once per visit; afterwards only the question
	goto_if_set FLAG_TEMP_D, SunMoonAltar_EventScript_DuelAskOnly
	setflag FLAG_TEMP_D
	msgbox SunMoonAltar_Text_DuelApproach, MSGBOX_DEFAULT
	closemessage
SunMoonAltar_EventScript_DuelAskOnly::
	msgbox SunMoonAltar_Text_DuelAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_DuelDeclined
	call SunMoonAltar_EventScript_PickPartner
	goto_if_eq VAR_RESULT, 0, SunMoonAltar_EventScript_DuelPartnerMissing
	goto_if_eq VAR_RESULT, 1, SunMoonAltar_EventScript_ReleaseQuiet
	goto SunMoonAltar_EventScript_Duel

SunMoonAltar_EventScript_DuelDeclined::
	msgbox SunMoonAltar_Text_DuelDeclined, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_DuelPartnerMissing::
	msgbox SunMoonAltar_Text_DuelPartnerMissing, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_ReleaseQuiet::
	release
	end

SunMoonAltar_EventScript_LusamineReady::
	msgbox SunMoonAltar_Text_LusamineReady, MSGBOX_DEFAULT
	release
	end

@ Narrative duel: no blackout, no penalty. Heal before; result copied BEFORE
@ anything else; previous no-whiteout state restored; heal again; four
@ outcomes, each with its own line, all converge. Anything else keeps state 13.
@ Lusamine's plate is re-declared in the FIRST box of every outcome, and the
@ in-battle defeat line prints no plate at all: the name box is an overworld
@ window, and src/text.c now skips {SPEAKER} while gMain.inBattle (that was
@ the corrupted name after this battle).
SunMoonAltar_EventScript_Duel::
	closemessage
	lockall
	msgbox SunMoonAltar_Text_DuelAccept, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_3, VAR_RESULT
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_LUSAMINE, SunMoonAltar_Text_DuelLusamineBeaten
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_3, TRUE, SunMoonAltar_EventScript_DuelKeepWhiteout
	clearflag B_FLAG_NO_WHITEOUT
SunMoonAltar_EventScript_DuelKeepWhiteout::
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, SunMoonAltar_EventScript_DuelWon
	goto_if_eq VAR_TEMP_2, B_OUTCOME_LOST, SunMoonAltar_EventScript_DuelLost
	goto_if_eq VAR_TEMP_2, B_OUTCOME_DREW, SunMoonAltar_EventScript_DuelDrew
	goto_if_eq VAR_TEMP_2, B_OUTCOME_FORFEITED, SunMoonAltar_EventScript_DuelForfeited
	goto SunMoonAltar_EventScript_DuelUnexpected

SunMoonAltar_EventScript_DuelWon::
	msgbox SunMoonAltar_Text_DuelWon, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	goto SunMoonAltar_EventScript_DuelSettled

@ The heal happens BETWEEN her two boxes, not before the first: she offers
@ the care, it happens, and she goes on.
SunMoonAltar_EventScript_DuelLost::
	msgbox SunMoonAltar_Text_DuelLost, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SunMoonAltar_Text_DuelLostAfterCare, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

SunMoonAltar_EventScript_DuelDrew::
	msgbox SunMoonAltar_Text_DuelDrew, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	goto SunMoonAltar_EventScript_DuelSettled

SunMoonAltar_EventScript_DuelForfeited::
	msgbox SunMoonAltar_Text_DuelForfeited, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	goto SunMoonAltar_EventScript_DuelSettled

@ Implementation recovery, not a secret ending: nothing marked, state 13.
SunMoonAltar_EventScript_DuelUnexpected::
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SunMoonAltar_Text_DuelUnexpected, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ The checkpoint is written first (a duel is never fought twice), then the
@ scene restarts from a KNOWN tile: the player could be talking to Lusamine
@ from (15,9) or (16,10). (14,12) is the neck below the future opening: free,
@ not a warp, and it frames the terrace. fadescreen is allowed here because
@ the warpsilent reloads the palettes.
SunMoonAltar_EventScript_DuelSettled::
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_DUEL_DONE
SunMoonAltar_EventScript_ResumeAgreement::
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 12
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ ACT III - agreement and passage test. State 13 (DUEL_DONE) -> 14.
@ Player on (14,12) after the reload, everyone on their templates.
@   Lillie (12,11) -> (15,10), diagonal to her mother at the base (16,9);
@   Ninetales one step after her to (12,11), clear of the controls
@   Anabel (15,13) -> (15,11), under Lillie, to take the module
@   partner out at (13,10), facing the disc; the opening at (14,10)
@   Anabel then goes (15,11) -> (14,11) -> INTO the opening, and back out
@   (14,11) is free: the player stands on (14,12), one row further down
@ The inside of the arena is not shown here: Anabel goes as far as the inner
@ edge, is gone for one reading, and her report comes over the communicator.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Agreement::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_LillieToBase
	applymovement LOCALID_SUN_MOON_ALTAR_NINETALES, SunMoonAltar_Movement_NinetalesFollow
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	waitmovement LOCALID_SUN_MOON_ALTAR_NINETALES
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_AgreementLillie, MSGBOX_DEFAULT
	closemessage
	@ she looks at the prepared space (down the stair), then at her daughter
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_WEST
	delay 20
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_AgreementLusamine, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_AgreementLillieAnswer, MSGBOX_DEFAULT
	closemessage
	@ the decision: she hands the portable module over and stays at the base
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, SunMoonAltar_Movement_AnabelStepUp
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_WEST
	delay 20
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_AgreementLusamineStay, MSGBOX_DEFAULT
	closemessage
	@ Lillie points down the corridor; Lusamine turns the base to match
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_SOUTH
	delay 20
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_NORTH
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_WEST
	applymovement LOCALID_SUN_MOON_ALTAR_SILVALLY, Common_Movement_WalkInPlaceFasterLeft
	waitmovement LOCALID_SUN_MOON_ALTAR_SILVALLY
	msgbox SunMoonAltar_Text_AgreementGladion, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_WEST
	msgbox SunMoonAltar_Text_AgreementAnabel, MSGBOX_DEFAULT
	closemessage
	@ --- the visible opening ------------------------------------------------
	bufferspeciesname STR_VAR_1, VAR_RIFT_ALTAR_PARTNER
	call SunMoonAltar_EventScript_PartnerOut
	fadeoutbgm 4
	call SunMoonAltar_EventScript_PartnerPulse
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	addobject LOCALID_SUN_MOON_ALTAR_RIFT
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_IN
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	@ the opening (14,10) is east of Kukui (12,9)
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_EAST
	msgbox SunMoonAltar_Text_OpeningKukui, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_NORTH
	@ Anabel to the inner edge with the module: (15,11) -> (15,10) -> into
	@ (14,10), gone for the reading, back out to (15,10)
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, SunMoonAltar_Movement_AnabelIn
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	delay 30
	call SunMoonAltar_EventScript_Comm
	msgbox SunMoonAltar_Text_OpeningAnabelTest, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_OpeningLusamine, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, SunMoonAltar_Movement_AnabelOut
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	@ closing the test: the base down, the pulse over, the opening contracts to
	@ a dormant mark (the rift's own flag, then the mark's own flag)
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_PARTNER, DIR_SOUTH
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_SUN_MOON_ALTAR_RIFT
	addobject LOCALID_SUN_MOON_ALTAR_MARK
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_OUT
	@ NO fadeoutbgm before this: fadeoutbgm PAUSES the track, a paused track
	@ never runs its fade-out (MPlayMain skips FadeOutBody), and the map music
	@ state waits for it forever - the warpsilent of TestDone then hangs on a
	@ black screen. fadedefaultbgm fades the playing track out by itself.
	fadedefaultbgm
	call SunMoonAltar_EventScript_PartnerBack
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_NORTH
	msgbox SunMoonAltar_Text_OpeningLooker, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_TestDone

@ State 14 with the step cleared, under a fade, then a reload in place: Lillie
@ and Anabel moved, the mark exists; ON_TRANSITION rebuilds all of it.
SunMoonAltar_EventScript_TestDone::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 14
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_NONE
	warpsilent MAP_SUN_MOON_ALTAR, 14, 12
	waitstate
	releaseall
	end

SunMoonAltar_Movement_NinetalesFollow:
	walk_right
	face_up
	step_end

@ (15,13) -> (15,11): up under Lillie (15,10), to take the module
SunMoonAltar_Movement_AnabelStepUp:
	walk_up
	walk_up
	face_up
	step_end

@ (15,11) -> (14,11) -> (14,10), and gone into the opening
SunMoonAltar_Movement_AnabelIn:
	walk_left
	walk_up
	set_invisible
	step_end

@ back out the same way, to (15,11)
SunMoonAltar_Movement_AnabelOut:
	set_visible
	walk_down
	walk_right
	face_up
	step_end

@ (12,11) -> (15,11) -> (15,10)
SunMoonAltar_Movement_LillieToBase:
	walk_right
	walk_right
	walk_right
	walk_up
	face_up
	step_end

@ ---------------------------------------------------------------------------
@ State 14: crossing. Anabel waits at (15,10) beside the mark (14,10); talking
@ to either starts the same checks, in the V2 order: room -> partner -> which
@ one -> ready. With room nothing is said about room.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Mark::
	lock
	goto SunMoonAltar_EventScript_CrossChecks

SunMoonAltar_EventScript_CrossChecks::
	call SunMoonAltar_EventScript_CheckRoom
	goto_if_ne VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftNoRoom
	call SunMoonAltar_EventScript_PickPartner
	goto_if_eq VAR_RESULT, 0, SunMoonAltar_EventScript_RiftNoPartner
	goto_if_eq VAR_RESULT, 1, SunMoonAltar_EventScript_ReleaseQuiet
	msgbox SunMoonAltar_Text_RiftAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftNotYet
	closemessage
	@ after a lost boss the arena opens with the short intro
	setvar VAR_TEMP_2, ALTAR_STEP_CROSSING
	call_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_BOSS_SEEN, SunMoonAltar_EventScript_SetRecross
	call_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RETRY_READY, SunMoonAltar_EventScript_SetRecross
	copyvar VAR_RIFT_ALTAR_STEP, VAR_TEMP_2
	@ the crossing is staged from a known tile: (14,11), under the mark
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	release
	end

SunMoonAltar_EventScript_SetRecross::
	setvar VAR_TEMP_2, ALTAR_STEP_RECROSSING
	return

SunMoonAltar_EventScript_RiftNoRoom::
	msgbox SunMoonAltar_Text_RiftNoRoom, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_RiftNoPartner::
	msgbox SunMoonAltar_Text_RiftNoPartner, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_RiftNotYet::
	msgbox SunMoonAltar_Text_RiftNotYet, MSGBOX_DEFAULT
	release
	end

@ The crossing. Player (14,11) under the mark; Anabel (15,10); partner comes
@ out at (13,10). Order of entry: partner, player, Anabel. Nothing of any of
@ them stays behind: the partner's own flag, the player's invisibility is
@ undone by the warp, Anabel's is undone by the next load of this map.
SunMoonAltar_EventScript_Crossing::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	call SunMoonAltar_EventScript_PartnerOut
	call SunMoonAltar_EventScript_PartnerPulse
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_SUN_MOON_ALTAR_MARK
	addobject LOCALID_SUN_MOON_ALTAR_RIFT
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_IN
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_EAST
	msgbox SunMoonAltar_Text_RiftLooker, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_RiftLusamine, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	msgbox SunMoonAltar_Text_RiftLillie, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_PARTNER, SunMoonAltar_Movement_PartnerIn
	waitmovement LOCALID_SUN_MOON_ALTAR_PARTNER
	removeobject LOCALID_SUN_MOON_ALTAR_PARTNER
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_PlayerIn
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, SunMoonAltar_Movement_AnabelCross
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	playse SE_WARP_OUT
	fadescreen FADE_TO_BLACK
	warpsilent MAP_ULTRA_SPACE_ARENA, 10, 19
	waitstate
	releaseall
	end

@ (13,10) -> (14,10), into the opening
SunMoonAltar_Movement_PartnerIn:
	walk_right
	set_invisible
	step_end

SunMoonAltar_Movement_PlayerIn:
	walk_up
	set_invisible
	step_end

SunMoonAltar_Movement_AnabelCross:
	walk_left
	set_invisible
	step_end

@ After a lost boss, on the stair (V2 section 16): the team is back, the
@ outside unit is being shut down, the exit still held. Once.
SunMoonAltar_EventScript_RetryRegroup::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_PlayerStepUp
	waitmovement OBJ_EVENT_ID_PLAYER
	call SunMoonAltar_EventScript_CameraToBase
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_SOUTH
	msgbox SunMoonAltar_Text_RetryAnabel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_RetryLusamine, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_SOUTH
	msgbox SunMoonAltar_Text_RetryGladion, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_NORTH
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_NORTH
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_WEST
	call SunMoonAltar_EventScript_CameraToPlayer
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_RETRY_READY
	releaseall
	end

@ ---------------------------------------------------------------------------
@ THE RECEPTION CUT (state 14, ALTAR_STEP_RESCUE). The arena warps here after
@ the victory; the player object is hidden on (16,13) and is only the camera.
@ Five groups, at most two UBs on the map at once, each group received and led
@ away before the next (V2 section 13). Two slot objects (VAR_0 / VAR_1 gfx,
@ own flags 8/9) are reused for every group: set the gfx var, addobject, walk,
@ removeobject. Every UB comes out of the rift (14,10) and walks column 14 down
@ to (14,19), off screen below the reception, where the helpers take over.
@ Budget: player + 6 visitors + Looker + rift + 2 helpers + 2 UBs = 13 / 16.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Rescue::
	lockall
	delay 30
	@ --- 1. Buzzwole and Pheromosa; Silvally keeps the people's side --------
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(BUZZWOLE)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(PHEROMOSA)
	call SunMoonAltar_EventScript_UBArriveA
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_NORMAL
	applymovement LOCALID_SUN_MOON_ALTAR_UB_A, SunMoonAltar_Movement_UBStep
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_A
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_WEST
	applymovement LOCALID_SUN_MOON_ALTAR_SILVALLY, Common_Movement_WalkInPlaceFasterLeft
	waitmovement LOCALID_SUN_MOON_ALTAR_SILVALLY
	msgbox SunMoonAltar_Text_RescueGladion, MSGBOX_DEFAULT
	closemessage
	call SunMoonAltar_EventScript_UBPairThrough
	call SunMoonAltar_EventScript_Register
	@ --- 2. Xurkitree, then Celesteela needs the middle ---------------------
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(XURKITREE)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(CELESTEELA)
	call SunMoonAltar_EventScript_UBArriveA
	call SunMoonAltar_EventScript_UBLeaveA
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_SOUTH
	msgbox SunMoonAltar_Text_RescueKukui, MSGBOX_DEFAULT
	closemessage
	@ Kukui moves a support out of the middle without leaving the base, and
	@ Looker steers the helpers along the prepared path
	applymovement LOCALID_SUN_MOON_ALTAR_KUKUI, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement LOCALID_SUN_MOON_ALTAR_KUKUI
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_NORTH
	call SunMoonAltar_EventScript_UBArriveB
	call SunMoonAltar_EventScript_UBLeaveB
	call SunMoonAltar_EventScript_Register
	@ --- 3. Blacephalon, then Stakataka: Lillie asks, her mother listens ----
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(BLACEPHALON)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(STAKATAKA)
	call SunMoonAltar_EventScript_UBArriveA
	call SunMoonAltar_EventScript_UBLeaveA
	call SunMoonAltar_EventScript_UBArriveB
	applymovement LOCALID_SUN_MOON_ALTAR_UB_B, SunMoonAltar_Movement_StakatakaSlow
	@ her hand is already on the adjuster, to narrow it between groups
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_B
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_NORTH
	msgbox SunMoonAltar_Text_RescueLillieWait, MSGBOX_DEFAULT
	closemessage
	@ she stops, looks at the creature, and follows her daughter
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_WEST
	delay 20
	msgbox SunMoonAltar_Text_RescueLusamineWait, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	applymovement LOCALID_SUN_MOON_ALTAR_UB_B, SunMoonAltar_Movement_StakatakaOut
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_B
	removeobject LOCALID_SUN_MOON_ALTAR_UB_B
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_NORTH
	msgbox SunMoonAltar_Text_RescueLillieClear, MSGBOX_DEFAULT
	closemessage
	@ only now does she adjust
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_NORTH
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	call SunMoonAltar_EventScript_Register
	@ --- 4. Kartana and Guzzlord, separately; Gladion leads the team aside --
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(KARTANA)
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(GUZZLORD)
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_SOUTH
	applymovement LOCALID_SUN_MOON_ALTAR_SILVALLY, Common_Movement_WalkInPlaceFasterDown
	waitmovement LOCALID_SUN_MOON_ALTAR_SILVALLY
	call SunMoonAltar_EventScript_UBArriveA
	call SunMoonAltar_EventScript_UBLeaveA
	call SunMoonAltar_EventScript_UBArriveB
	call SunMoonAltar_EventScript_UBLeaveB
	call SunMoonAltar_EventScript_Register
	@ --- 5. Nihilego, last, alone ----------------------------------------------
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(NIHILEGO)
	call SunMoonAltar_EventScript_UBArriveA
	applymovement LOCALID_SUN_MOON_ALTAR_UB_A, SunMoonAltar_Movement_NihilegoDrift
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_A
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	msgbox SunMoonAltar_Text_RescueNihilego, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_NINETALES, Common_Movement_WalkInPlaceFasterRight
	waitmovement LOCALID_SUN_MOON_ALTAR_NINETALES
	applymovement LOCALID_SUN_MOON_ALTAR_UB_A, SunMoonAltar_Movement_NihilegoOut
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_A
	removeobject LOCALID_SUN_MOON_ALTAR_UB_A
	call SunMoonAltar_EventScript_Register
	@ --- the count depends on arrivals: nine registered ------------------------
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_NORTH
	call SunMoonAltar_EventScript_Comm
	msgbox SunMoonAltar_Text_AllNineSafe, MSGBOX_DEFAULT
	closemessage
	@ back to the arena, where the capture is next. (9,11): the tile the
	@ player stepped aside to before the rescue began.
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CAPTURE
	warpsilent MAP_ULTRA_SPACE_ARENA, 9, 11
	waitstate
	releaseall
	end

@ One UB out of the rift: a small shake, the warp sound, and it is there.
SunMoonAltar_EventScript_UBArriveA::
	playse SE_WARP_OUT
	addobject LOCALID_SUN_MOON_ALTAR_UB_A
	delay 16
	return

SunMoonAltar_EventScript_UBArriveB::
	playse SE_WARP_OUT
	addobject LOCALID_SUN_MOON_ALTAR_UB_B
	delay 16
	return

@ Down column 14 and away: (14,10) -> (14,19). Off screen below the helpers.
SunMoonAltar_EventScript_UBLeaveA::
	applymovement LOCALID_SUN_MOON_ALTAR_UB_A, SunMoonAltar_Movement_UBThrough
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_A
	removeobject LOCALID_SUN_MOON_ALTAR_UB_A
	return

SunMoonAltar_EventScript_UBLeaveB::
	applymovement LOCALID_SUN_MOON_ALTAR_UB_B, SunMoonAltar_Movement_UBThrough
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_B
	removeobject LOCALID_SUN_MOON_ALTAR_UB_B
	return

@ Group 1: A has taken one step already; B comes out behind it, and they go
@ one after the other, never two sprites on one tile.
SunMoonAltar_EventScript_UBPairThrough::
	applymovement LOCALID_SUN_MOON_ALTAR_UB_A, SunMoonAltar_Movement_UBRest
	delay 24
	call SunMoonAltar_EventScript_UBArriveB
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_NORMAL
	applymovement LOCALID_SUN_MOON_ALTAR_UB_B, SunMoonAltar_Movement_UBThrough
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_A
	removeobject LOCALID_SUN_MOON_ALTAR_UB_A
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_B
	removeobject LOCALID_SUN_MOON_ALTAR_UB_B
	return

@ Looker's register: a confirmation sound, no box for each count.
SunMoonAltar_EventScript_Register::
	playse SE_SELECT
	waitse
	delay 20
	return

SunMoonAltar_Movement_UBStep:
	walk_down
	step_end

@ from (14,11), the rest of the way
SunMoonAltar_Movement_UBRest:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

SunMoonAltar_Movement_UBThrough:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

@ Stakataka: slow, two tiles into the neck (14,12), and it has not cleared it
SunMoonAltar_Movement_StakatakaSlow:
	walk_slow_down
	walk_slow_down
	step_end

SunMoonAltar_Movement_StakatakaOut:
	walk_slow_down
	walk_slow_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

@ Nihilego: drifts to the stair (14,14), beside Lillie's column
SunMoonAltar_Movement_NihilegoDrift:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

SunMoonAltar_Movement_NihilegoOut:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_down
	walk_down
	step_end

@ ---------------------------------------------------------------------------
@ ACT V - return, steady light, family. State 15 -> 16. On the load after the
@ capture the player is on (14,11) under the rift; Anabel (15,12) beside him;
@ Nihilego at a distance in the reception area (13,16); everyone else on the
@ templates. Necrozma and the partner come out of their Balls here, at
@ (15,11) and (13,10): the same individuals, shown, then recalled.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Return15::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	fadedefaultbgm
	@ Looker comes up from the side, leaving the opening clear: (13,13)->(13,12)
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, SunMoonAltar_Movement_LookerUp
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox SunMoonAltar_Text_ReturnLooker, MSGBOX_DEFAULT
	closemessage
	@ the player answers with a gesture
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_Nod
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Anabel sets the module down safely and speaks to the outside unit
	applymovement LOCALID_SUN_MOON_ALTAR_ANABEL, Common_Movement_WalkInPlaceFasterDown
	waitmovement LOCALID_SUN_MOON_ALTAR_ANABEL
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_NORTH
	msgbox SunMoonAltar_Text_ReturnAnabel, MSGBOX_DEFAULT
	closemessage
	@ only now does Lusamine let go of the control
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	msgbox SunMoonAltar_Text_ReturnLillie, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_SOUTH
	goto_if_eq VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CUSTODY, SunMoonAltar_EventScript_ReturnCustody
	goto SunMoonAltar_EventScript_StabilizeInScene

@ Necrozma is with Anabel: the closing waits for the delivery. Everyone stays
@ at their post; the passage stays under the team's control.
SunMoonAltar_EventScript_ReturnCustody::
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CUSTODY_WAIT
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_NORTH
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_NORTH
	releaseall
	end

@ The stabilization, reached on the same run (normal capture) or on the reload
@ after a delivery from custody (ALTAR_STEP_DELIVERED), which skips the return.
SunMoonAltar_EventScript_Stabilize::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	fadedefaultbgm
SunMoonAltar_EventScript_StabilizeInScene::
	@ a pulse from Necrozma's Ball, before its final place in team or PC
	playse SE_BALL
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_SOUTH
	applymovement LOCALID_SUN_MOON_ALTAR_KUKUI, Common_Movement_ExclamationMark
	waitmovement LOCALID_SUN_MOON_ALTAR_KUKUI
	msgbox SunMoonAltar_Text_ReturnKukui, MSGBOX_DEFAULT
	closemessage
	@ the player releases Necrozma on the protected side, (15,11), and the
	@ partner comes out at (13,10). The object is the SAME individual shown
	@ outside its Ball; its record, team slot or PC box never change.
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	addobject LOCALID_SUN_MOON_ALTAR_NECROZMA
	applymovement LOCALID_SUN_MOON_ALTAR_NECROZMA, SunMoonAltar_Movement_NecrozmaOut
	waitmovement LOCALID_SUN_MOON_ALTAR_NECROZMA
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	call SunMoonAltar_EventScript_PartnerOut
	@ the partner steadies the edge; the loose light drifts back to Necrozma
	call SunMoonAltar_EventScript_PartnerPulse
	call SunMoonAltar_EventScript_Shake
	call SunMoonAltar_EventScript_Flash
	applymovement LOCALID_SUN_MOON_ALTAR_NECROZMA, SunMoonAltar_Movement_NecrozmaDraw
	waitmovement LOCALID_SUN_MOON_ALTAR_NECROZMA
	msgbox SunMoonAltar_Text_ReturnAnabelObserve, MSGBOX_DEFAULT
	closemessage
	call SunMoonAltar_EventScript_PartnerPulse
	call SunMoonAltar_EventScript_Flash
	applymovement LOCALID_SUN_MOON_ALTAR_NECROZMA, SunMoonAltar_Movement_NecrozmaDraw
	waitmovement LOCALID_SUN_MOON_ALTAR_NECROZMA
	@ the disc goes back to the sun/moon of the hour; the dust stops
	fadescreenswapbuffers FADE_TO_WHITE
	call SunMoonAltar_EventScript_DiscToCalm
	fadescreenswapbuffers FADE_FROM_WHITE
	setweather WEATHER_NONE
	doweather
	delay 30
	msgbox SunMoonAltar_Text_ReturnKukuiSteady, MSGBOX_DEFAULT
	closemessage
	@ the base comes down in steps; the partner ends its pulse
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_NORTH
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_NORTH
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_Adjust
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_PARTNER, DIR_SOUTH
	delay 40
	msgbox SunMoonAltar_Text_ReturnAnabelStable, MSGBOX_DEFAULT
	closemessage
	@ switched off, and the calm starts only here
	call SunMoonAltar_EventScript_Flash
	playse SE_PC_OFF
	fadedefaultbgm
	@ the player recalls both, visibly; each keeps its own place
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_SUN_MOON_ALTAR_NECROZMA, SunMoonAltar_Movement_EnterBall
	waitmovement LOCALID_SUN_MOON_ALTAR_NECROZMA
	removeobject LOCALID_SUN_MOON_ALTAR_NECROZMA
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	call SunMoonAltar_EventScript_PartnerBack
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	@ --- Lusamine's part --------------------------------------------------------
	@ Lillie goes to her mother without hurry: (12,11) -> (12,10) -> (13,10)
	@ -> (13,9) -> (14,9) -> (15,9), beside her. (12,9) is Kukui, so she turns
	@ in one row earlier; (13,10) is free because the partner is back in its
	@ Ball, and the player stands on (14,11).
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_LillieToMother
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	delay 40
	msgbox SunMoonAltar_Text_FamilyLusamine, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	msgbox SunMoonAltar_Text_FamilyLillie, MSGBOX_DEFAULT
	closemessage
	@ the hand starts to rise, and comes to rest at her side
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_WEST
	delay 30
	msgbox SunMoonAltar_Text_FamilyLusamineAsk, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FamilyLillieAnswer, MSGBOX_DEFAULT
	closemessage
	@ Gladion finishes with Silvally and comes over: (16,11) -> (16,10)
	applymovement LOCALID_SUN_MOON_ALTAR_GLADION, SunMoonAltar_Movement_StepUp
	waitmovement LOCALID_SUN_MOON_ALTAR_GLADION
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_FamilyLusamineGladion, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FamilyGladion, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_Smile
	applymovement LOCALID_SUN_MOON_ALTAR_SILVALLY, SunMoonAltar_Movement_StepUp
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	waitmovement LOCALID_SUN_MOON_ALTAR_SILVALLY
	turnobject LOCALID_SUN_MOON_ALTAR_SILVALLY, DIR_WEST
	@ --- last tasks: the nine go to transport, organised ------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_UB_A, SunMoonAltar_Movement_NihilegoAway
	waitmovement LOCALID_SUN_MOON_ALTAR_UB_A
	removeobject LOCALID_SUN_MOON_ALTAR_UB_A
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox SunMoonAltar_Text_FarewellLooker, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_WEST
	msgbox SunMoonAltar_Text_FarewellAnabel, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_WEST
	msgbox SunMoonAltar_Text_FarewellGladion, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_SOUTH
	msgbox SunMoonAltar_Text_FarewellKukui, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_SUN_MOON_ALTAR_LUSAMINE, DIR_SOUTH
	msgbox SunMoonAltar_Text_FarewellLusamine, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox SunMoonAltar_Text_FarewellLookerHome, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_FarewellDone

@ The population changes completely (visitors leave for good, the rift turns
@ daily): reload in place and let ON_TRANSITION build state 16. The daily flag
@ tells Lusamine's rematch that the nine came back TODAY.
SunMoonAltar_EventScript_FarewellDone::
	fadescreen FADE_TO_BLACK
	setflag FLAG_DAILY_ALTAR_RESOLVED
	setvar VAR_RIFT_MISSIONS_STATE, 16
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_NONE
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

SunMoonAltar_Movement_LookerUp:
	walk_up
	face_right
	step_end

SunMoonAltar_Movement_Nod:
	face_down
	delay_8
	face_left
	step_end

SunMoonAltar_Movement_NecrozmaOut:
	exit_pokeball
	face_left
	step_end

@ Necrozma turns to the loose light around the disc; its light pulses slower
SunMoonAltar_Movement_NecrozmaDraw:
	face_up
	walk_in_place_slow_up
	walk_in_place_slow_up
	face_left
	step_end

SunMoonAltar_Movement_LillieToMother:
	walk_up
	walk_right
	walk_up
	walk_right
	walk_right
	face_right
	step_end

SunMoonAltar_Movement_StepUp:
	walk_up
	face_up
	step_end

SunMoonAltar_Movement_Smile:
	emote_heart
	step_end

@ (13,16) -> (13,20): off to the transport area, below the frame
SunMoonAltar_Movement_NihilegoAway:
	walk_slow_down
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

@ ---------------------------------------------------------------------------
@ Object scripts of the people standing around.
@ ---------------------------------------------------------------------------

@ Looker heals in 13..15 (V2 section 18): one short question. From 16 on the
@ heal belongs to the Aether staff at the stair base, and he only talks.
SunMoonAltar_EventScript_Looker::
	lock
	faceplayer
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LookerHealAsk
	msgbox SunMoonAltar_Text_LookerPost, MSGBOX_DEFAULT
	release
	end
SunMoonAltar_EventScript_LookerHealAsk::
	msgbox SunMoonAltar_Text_LookerHealAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_LookerNoHeal
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SunMoonAltar_Text_LookerHealDone, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LookerNoHeal::
	msgbox SunMoonAltar_Text_LookerHealNo, MSGBOX_DEFAULT
	release
	end

@ Anabel: in 14 she IS the crossing (she stands by the mark); in 15 with
@ Necrozma in her custody she offers the delivery; from 16 she keeps the
@ passage and points to Kurt. She sells nothing.
SunMoonAltar_EventScript_Anabel::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_AnabelPost
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_AnabelCustody
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_CrossChecks
	msgbox SunMoonAltar_Text_AnabelBefore, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_AnabelPost::
	specialvar VAR_RESULT, Nexus_IsDoneToday
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_AnabelSurveyDone
	msgbox SunMoonAltar_Text_AnabelPost, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_AnabelKurt, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_AnabelSurveyDone::
	msgbox SunMoonAltar_Text_RiftDailyUsed, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_AnabelKurt, MSGBOX_DEFAULT
	release
	end

@ The custody delivery (V2 section 14). Only Necrozma, no new capture scene,
@ no boss. Room missing again -> only the room box.
SunMoonAltar_EventScript_AnabelCustody::
	goto_if_ne VAR_RIFT_ALTAR_STEP, ALTAR_STEP_CUSTODY_WAIT, SunMoonAltar_EventScript_AnabelReturnLine
	msgbox SunMoonAltar_Text_CapturePendingRetry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftNotYet
	closemessage
	call SunMoonAltar_EventScript_CheckRoom
	goto_if_ne VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftNoRoom
	lockall
	call SunMoonAltar_EventScript_GiveNecrozma
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, SunMoonAltar_EventScript_CustodyNoRoom
	@ delivered: the stabilization plays from the known tile under the rift
	setvar VAR_RIFT_ALTAR_STEP, ALTAR_STEP_DELIVERED
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

SunMoonAltar_EventScript_CustodyNoRoom::
	msgbox SunMoonAltar_Text_RiftNoRoom, MSGBOX_DEFAULT
	releaseall
	end

SunMoonAltar_EventScript_AnabelReturnLine::
	msgbox SunMoonAltar_Text_ReturnAnabel, MSGBOX_DEFAULT
	release
	end

@ The one gift of the arc, shared with the arena through this label's twin
@ (UltraSpaceArena_EventScript_GiveNecrozma): Necrozma, level 75, in a BEAST
@ BALL (ball=BALL_BEAST writes MON_DATA_POKEBALL, not just the look of the
@ scene). STR_VAR_1 is rebuffered right here: it may still hold the partner.
@ One confirmation (SYSTEM, no plate), then nickname and PC notice.
@ VAR_TEMP_TRANSFERRED_SPECIES is what the PC notice reads.
@ Out: VAR_RESULT = the givemon result (MON_CANT_GIVE = nothing happened).
SunMoonAltar_EventScript_GiveNecrozma::
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_NECROZMA
	bufferspeciesname STR_VAR_1, SPECIES_NECROZMA
	givemon SPECIES_NECROZMA, 75, ITEM_NONE, ball=BALL_BEAST
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, SunMoonAltar_EventScript_Return
	copyvar VAR_TEMP_4, VAR_RESULT
	playfanfare MUS_OBTAIN_ITEM
	message SunMoonAltar_Text_CaptureConfirmed
	waitmessage
	waitfanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_TEMP_4, MON_GIVEN_TO_PC, SunMoonAltar_EventScript_GivenToPC
	call_if_eq VAR_RESULT, YES, Common_EventScript_NameReceivedPartyMonFull
	copyvar VAR_RESULT, VAR_TEMP_4
	return
SunMoonAltar_EventScript_GivenToPC::
	call_if_eq VAR_RESULT, YES, Common_EventScript_NameReceivedBoxMon
	call Common_EventScript_TransferredToPC
	copyvar VAR_RESULT, VAR_TEMP_4
	return

SunMoonAltar_EventScript_Lillie::
	lock
	faceplayer
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_LillieAfter
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_LillieReady
	msgbox SunMoonAltar_Text_LillieBefore, MSGBOX_DEFAULT
	release
	end
SunMoonAltar_EventScript_LillieReady::
	msgbox SunMoonAltar_Text_LillieReady, MSGBOX_DEFAULT
	release
	end
SunMoonAltar_EventScript_LillieAfter::
	msgbox SunMoonAltar_Text_ReturnLillie, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Gladion::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_GladionReady
	msgbox SunMoonAltar_Text_GladionBefore, MSGBOX_DEFAULT
	release
	end
SunMoonAltar_EventScript_GladionReady::
	msgbox SunMoonAltar_Text_GladionReady, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Kukui::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_KukuiReady
	msgbox SunMoonAltar_Text_KukuiBefore, MSGBOX_DEFAULT
	release
	end
SunMoonAltar_EventScript_KukuiReady::
	msgbox SunMoonAltar_Text_KukuiReady, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ THE RIFT object. 14: never visible (the mark is). 15: Anabel's delivery.
@ >= 16: the way into the Nexus (.claude/rift_missions/nexus/NEXUS_REGRAS.md).
@ Any hour, any number of times a day (R3): nothing is spent here; the day's
@ state lives in VAR_NEXUS_DAILY. R10: the party is checked BEFORE the
@ question - at most one legendary, one sub-legendary and one Mega.
@ No Solgaleo/Lunala or Necrozma required after 16.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Rift::
	lock
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_AnabelCustody
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_ReleaseQuiet
	specialvar VAR_RESULT, Nexus_CheckTraditional
	goto_if_ne VAR_RESULT, NEXUS_TRADITIONAL_OK, SunMoonAltar_EventScript_RiftNotTraditional
	msgbox SunMoonAltar_Text_RiftDailyAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftDailyNo
	closemessage
	special Nexus_EnterFromAltar
	fadescreen FADE_TO_BLACK
	warpsilent MAP_NEXUS, 10, 19
	waitstate
	release
	end

SunMoonAltar_EventScript_RiftNotTraditional::
	call_if_eq VAR_RESULT, NEXUS_TRADITIONAL_LEGENDARY, SunMoonAltar_EventScript_RiftTooManyLegendaries
	call_if_eq VAR_RESULT, NEXUS_TRADITIONAL_SUB, SunMoonAltar_EventScript_RiftTooManySubs
	call_if_eq VAR_RESULT, NEXUS_TRADITIONAL_MEGA, SunMoonAltar_EventScript_RiftTooManyMegas
	msgbox SunMoonAltar_Text_RiftTraditionalRule, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_RiftTooManyLegendaries::
	msgbox SunMoonAltar_Text_RiftTooManyLegendaries, MSGBOX_DEFAULT
	return
SunMoonAltar_EventScript_RiftTooManySubs::
	msgbox SunMoonAltar_Text_RiftTooManySubs, MSGBOX_DEFAULT
	return
SunMoonAltar_EventScript_RiftTooManyMegas::
	msgbox SunMoonAltar_Text_RiftTooManyMegas, MSGBOX_DEFAULT
	return

SunMoonAltar_EventScript_RiftDailyNo::
	msgbox SunMoonAltar_Text_RiftDailyNo, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Post-game Lusamine (Mon/Wed/Sat) and her one rematch a day. A normal battle
@ with blackout. On the day the arc closed (FLAG_DAILY_ALTAR_RESOLVED) she
@ fights with her duel team: Nihilego joins only after the date changes.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_LusaminePost::
	msgbox SunMoonAltar_Text_LusaminePost, MSGBOX_DEFAULT
	closemessage
	goto_if_set FLAG_DAILY_REMATCH_LUSAMINE, SunMoonAltar_EventScript_LusamineDoneToday
	msgbox SunMoonAltar_Text_LusamineRematchAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_LusamineRematchNo
	@ set BEFORE the battle: a loss never comes back to this script
	setflag FLAG_DAILY_REMATCH_LUSAMINE
	goto_if_set FLAG_DAILY_ALTAR_RESOLVED, SunMoonAltar_EventScript_LusamineRematchToday
	trainerbattle_no_intro TRAINER_LUSAMINE_ALTAR, SunMoonAltar_Text_LusamineRematchBeaten
	goto SunMoonAltar_EventScript_LusamineRematchAfter
SunMoonAltar_EventScript_LusamineRematchToday::
	trainerbattle_no_intro TRAINER_LUSAMINE, SunMoonAltar_Text_LusamineRematchBeaten
SunMoonAltar_EventScript_LusamineRematchAfter::
	msgbox SunMoonAltar_Text_LusamineRematchAfter, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LusamineRematchNo::
	msgbox SunMoonAltar_Text_LusamineRematchNo, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LusamineDoneToday::
	msgbox SunMoonAltar_Text_LusamineDoneToday, MSGBOX_DEFAULT
	release
	end

@ Ferry back to Olivine, every state. Same send-off as the Faraway Island
@ sailor; warp to the Olivine desk at (8,16), above the port sailor.
SunMoonAltar_EventScript_Sailor::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_SailorAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_SailorStay
	msgbox SunMoonAltar_Text_SailorDepart, MSGBOX_DEFAULT
	closemessage
	hidefollower
	delay 30
	hideobjectat LOCALID_SUN_MOON_ALTAR_SAILOR, MAP_SUN_MOON_ALTAR
	setvar VAR_0x8004, LOCALID_SUN_MOON_ALTAR_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE, 8, 16
	waitstate
	release
	end

SunMoonAltar_EventScript_SailorStay::
	msgbox SunMoonAltar_Text_SailorStay, MSGBOX_DEFAULT
	release
	end

@ ===========================================================================
@ Texts - V2, verbatim. One speaker per box, the plate declared in the first
@ byte of every message (a message without it has no plate and never
@ inherits one). SYSTEM and NARRATOR lines carry no plate: the author's rule
@ for the V2 scripts. One msgbox + closemessage per box (gStringVar4 is 1000
@ bytes).
@ ===========================================================================
SunMoonAltar_Text_ArrivalLooker:
	.string "{SPEAKER NAME_LOOKER}There you are. The ship will stay.\p"
	.string "We've brought supplies\n"
	.string "for the Pokémon.$"

SunMoonAltar_Text_ArrivalKukui:
	.string "{SPEAKER NAME_KUKUI}Same pulse as New Bark.\n"
	.string "Strong, then unsteady.\p"
	.string "Let's see how the passage responds\n"
	.string "before we take anyone through.$"

SunMoonAltar_Text_ArrivalAnabel:
	.string "{SPEAKER NAME_ANABEL}I'll take the inside unit.\n"
	.string "We need someone at these\l"
	.string "controls here.$"

SunMoonAltar_Text_ArrivalLusamine:
	.string "{SPEAKER NAME_LUSAMINE}Professor Kukui can operate this unit.\n"
	.string "I'll go with you.$"

SunMoonAltar_Text_ArrivalKukuiLimit:
	.string "{SPEAKER NAME_KUKUI}I can keep it running.\n"
	.string "If it drifts, I'll need your help.$"

SunMoonAltar_Text_ArrivalLusamineInsists:
	.string "{SPEAKER NAME_LUSAMINE}And if the inside unit fails?\n"
	.string "I cannot repair it from here.$"

SunMoonAltar_Text_ArrivalAnabelPlan:
	.string "{SPEAKER NAME_ANABEL}Then we withdraw.\n"
	.string "You showed me how to do that.\p"
	.string "{PLAYER} handles Necrozma.\n"
	.string "You keep our return clear.$"

SunMoonAltar_Text_ArrivalLusamineFear:
	.string "{SPEAKER NAME_LUSAMINE}I saw what it did in New Bark.\n"
	.string "I cannot simply send you in there.$"

SunMoonAltar_Text_ArrivalLillie:
	.string "{SPEAKER NAME_LILLIE}Mother, we're asking you to help us\n"
	.string "bring them back.\p"
	.string "I need you here with me.$"

SunMoonAltar_Text_ArrivalLusamineChildren:
	.string "{SPEAKER NAME_LUSAMINE}I know.\n"
	.string "I wanted you both far from all this.$"

SunMoonAltar_Text_ArrivalGladion:
	.string "{SPEAKER NAME_GLADION}We're here because we chose to help.\n"
	.string "Let us.$"

SunMoonAltar_Text_ArrivalLusaminePause:
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER}. Speak with me before you go.$"

SunMoonAltar_Text_ArrivalLookerRelease:
	.string "{SPEAKER NAME_LOOKER}We'll finish setting up.\n"
	.string "Come to me if your team needs care.$"

SunMoonAltar_Text_LillieBefore:
	.string "{SPEAKER NAME_LILLIE}Ninetales and I will meet them here.\n"
	.string "They may be frightened\l"
	.string "when they come out.\p"
	.string "I hope Mother will stay beside us.$"

SunMoonAltar_Text_GladionBefore:
	.string "{SPEAKER NAME_GLADION}Silvally knows these creatures.\n"
	.string "We'll keep the exit clear.\p"
	.string "You won't have to fight your way back.$"

SunMoonAltar_Text_KukuiBefore:
	.string "{SPEAKER NAME_KUKUI}Your partner steadied the equipment\n"
	.string "in Olivine. That was a good start.\p"
	.string "This time we'll test both ends.$"

SunMoonAltar_Text_AnabelBefore:
	.string "{SPEAKER NAME_ANABEL}I've checked the inside unit.\n"
	.string "If the signal drops, we come back.$"

SunMoonAltar_Text_DuelApproach:
	.string "{SPEAKER NAME_LUSAMINE}They trust you.\n"
	.string "I've seen why.\p"
	.string "Still… I would rather face it myself\n"
	.string "than watch you go.$"

SunMoonAltar_Text_DuelAsk:
	.string "{SPEAKER NAME_LUSAMINE}Will you battle me, {PLAYER}?\n"
	.string "I want to face you properly\l"
	.string "before I leave this to you.$"

SunMoonAltar_Text_DuelDeclined:
	.string "{SPEAKER NAME_LUSAMINE}Of course. Take your time.$"

SunMoonAltar_Text_DuelPartnerMissing:
	.string "{SPEAKER NAME_LUSAMINE}Bring Solgaleo or Lunala with you.\n"
	.string "We'll need your partner\l"
	.string "for the passage.$"

@ SYSTEM: no plate
SunMoonAltar_Text_PartnerSelect:
	.string "Which Pokémon will open the passage?$"

SunMoonAltar_Text_ChoiceSolgaleo:
	.string "Solgaleo$"

SunMoonAltar_Text_ChoiceLunala:
	.string "Lunala$"

SunMoonAltar_Text_ChoiceNotNow:
	.string "Not now$"

SunMoonAltar_Text_DuelAccept:
	.string "{SPEAKER NAME_LUSAMINE}Thank you.\n"
	.string "Let's give them a proper battle.$"

@ printed INSIDE the battle: the {SPEAKER} code is consumed there without a
@ plate (src/text.c), the trainer is on screen
SunMoonAltar_Text_DuelLusamineBeaten:
	.string "{SPEAKER NAME_LUSAMINE}Well fought.$"

SunMoonAltar_Text_DuelWon:
	.string "{SPEAKER NAME_LUSAMINE}You earned that victory.\n"
	.string "I'll leave Necrozma to you.$"

SunMoonAltar_Text_DuelLost:
	.string "{SPEAKER NAME_LUSAMINE}This battle was mine.\n"
	.string "Let's take care of your Pokémon.$"

SunMoonAltar_Text_DuelLostAfterCare:
	.string "{SPEAKER NAME_LUSAMINE}And we still need someone here\n"
	.string "who can bring you back.$"

SunMoonAltar_Text_DuelDrew:
	.string "{SPEAKER NAME_LUSAMINE}Neither team has anything left.\n"
	.string "They've done enough. Let them rest.$"

SunMoonAltar_Text_DuelForfeited:
	.string "{SPEAKER NAME_LUSAMINE}All right. We'll stop here.\n"
	.string "Let me see to your Pokémon.$"

SunMoonAltar_Text_DuelUnexpected:
	.string "{SPEAKER NAME_LUSAMINE}Let's stop for now.\n"
	.string "Speak to me when you're ready.$"

SunMoonAltar_Text_AgreementLillie:
	.string "{SPEAKER NAME_LILLIE}Mother, come and check\n"
	.string "the receiving area with me.$"

SunMoonAltar_Text_AgreementLusamine:
	.string "{SPEAKER NAME_LUSAMINE}You really want me beside you?$"

SunMoonAltar_Text_AgreementLillieAnswer:
	.string "{SPEAKER NAME_LILLIE}Yes.\n"
	.string "But please listen when I need your help.$"

SunMoonAltar_Text_AgreementLusamineStay:
	.string "{SPEAKER NAME_LUSAMINE}I will.\n"
	.string "Show me where you want them\l"
	.string "to come through.$"

SunMoonAltar_Text_AgreementGladion:
	.string "{SPEAKER NAME_GLADION}I'll keep that side clear.$"

SunMoonAltar_Text_AgreementAnabel:
	.string "{SPEAKER NAME_ANABEL}We're ready to test the passage.\n"
	.string "Bring your partner forward.$"

SunMoonAltar_Text_OpeningKukui:
	.string "{SPEAKER NAME_KUKUI}There it is!\n"
	.string "Hold that steady, {STR_VAR_1}.$"

SunMoonAltar_Text_OpeningAnabelTest:
	.string "{SPEAKER NAME_ANABEL}Both units are responding.\n"
	.string "The way back is clear.$"

SunMoonAltar_Text_OpeningLusamine:
	.string "{SPEAKER NAME_LUSAMINE}The outside signal is steady too.\n"
	.string "We can close the test.$"

SunMoonAltar_Text_OpeningLooker:
	.string "{SPEAKER NAME_LOOKER}Speak with Anabel by the passage\n"
	.string "when you're ready to go.$"

SunMoonAltar_Text_RiftNoRoom:
	.string "{SPEAKER NAME_ANABEL}Your team and Boxes are full.\n"
	.string "Make room for one Pokémon before we go.$"

SunMoonAltar_Text_RiftNoPartner:
	.string "{SPEAKER NAME_ANABEL}Bring Solgaleo or Lunala in your team.\n"
	.string "We need your partner\l"
	.string "to open the passage.$"

SunMoonAltar_Text_RiftAsk:
	.string "{SPEAKER NAME_ANABEL}Ready, {PLAYER}?\n"
	.string "I'll keep the inside unit running.\l"
	.string "You take Necrozma.$"

SunMoonAltar_Text_RiftNotYet:
	.string "{SPEAKER NAME_ANABEL}All right. We'll be here.$"

SunMoonAltar_Text_RiftLooker:
	.string "{SPEAKER NAME_LOOKER}I can hear you clearly, Chief.\n"
	.string "We're ready to receive them.$"

SunMoonAltar_Text_RiftLusamine:
	.string "{SPEAKER NAME_LUSAMINE}The outside unit is ready.$"

SunMoonAltar_Text_RiftLillie:
	.string "{SPEAKER NAME_LILLIE}We'll be waiting for you too, {PLAYER}.$"

SunMoonAltar_Text_RescueGladion:
	.string "{SPEAKER NAME_GLADION}Silvally, give them room.\n"
	.string "Keep this side clear.$"

SunMoonAltar_Text_RescueKukui:
	.string "{SPEAKER NAME_KUKUI}Celesteela needs more room.\n"
	.string "Clear the middle!$"

SunMoonAltar_Text_RescueLillieWait:
	.string "{SPEAKER NAME_LILLIE}Wait, Mother.\n"
	.string "Stakataka hasn't cleared it.\l"
	.string "Keep it open a little longer.$"

SunMoonAltar_Text_RescueLusamineWait:
	.string "{SPEAKER NAME_LUSAMINE}All right. Tell me when it's through.$"

SunMoonAltar_Text_RescueLillieClear:
	.string "{SPEAKER NAME_LILLIE}It's clear now.\n"
	.string "Thank you.$"

SunMoonAltar_Text_RescueNihilego:
	.string "{SPEAKER NAME_LILLIE}This way. There's room.\n"
	.string "Ninetales, stay beside me.$"

@ V2 names this UltraSpaceArena_Text_AllNineSafe: it is heard in the arena over
@ the communicator; Looker says it here, at the register
SunMoonAltar_Text_AllNineSafe:
	.string "{SPEAKER NAME_LOOKER}All nine are through.\n"
	.string "We're checking them now.$"

@ SYSTEM: no plate. STR_VAR_1 is rebuffered to Necrozma right before it
SunMoonAltar_Text_CaptureConfirmed:
	.string "{PLAYER} caught {STR_VAR_1}!$"

SunMoonAltar_Text_CapturePendingRetry:
	.string "{SPEAKER NAME_ANABEL}Ready to take Necrozma with you?$"

SunMoonAltar_Text_ReturnLooker:
	.string "{SPEAKER NAME_LOOKER}There you are!\n"
	.string "Are you hurt?$"

SunMoonAltar_Text_ReturnAnabel:
	.string "{SPEAKER NAME_ANABEL}We're all back.\n"
	.string "Thank you for keeping it steady.$"

SunMoonAltar_Text_ReturnLillie:
	.string "{SPEAKER NAME_LILLIE}All nine, {PLAYER}.\n"
	.string "Nihilego was the last one through.$"

SunMoonAltar_Text_ReturnKukui:
	.string "{SPEAKER NAME_KUKUI}Necrozma's reacting to the opening.\n"
	.string "Let's give it room.$"

SunMoonAltar_Text_ReturnAnabelObserve:
	.string "{SPEAKER NAME_ANABEL}The loose light is drawing back.\n"
	.string "Keep the passage steady.$"

SunMoonAltar_Text_ReturnKukuiSteady:
	.string "{SPEAKER NAME_KUKUI}That's it. No more surges.\n"
	.string "Ease the outside unit down.$"

SunMoonAltar_Text_ReturnAnabelStable:
	.string "{SPEAKER NAME_ANABEL}It's holding on its own.\n"
	.string "We can switch the equipment off.$"

SunMoonAltar_Text_FamilyLusamine:
	.string "{SPEAKER NAME_LUSAMINE}Lillie…\n"
	.string "you knew when to give them space.\l"
	.string "I would have hurried them.$"

SunMoonAltar_Text_FamilyLillie:
	.string "{SPEAKER NAME_LILLIE}I was frightened too.\n"
	.string "It helped having you there.$"

SunMoonAltar_Text_FamilyLusamineAsk:
	.string "{SPEAKER NAME_LUSAMINE}Would you tell me about your journey?\n"
	.string "When we've finished here.\p"
	.string "There is so much I haven't asked.$"

SunMoonAltar_Text_FamilyLillieAnswer:
	.string "{SPEAKER NAME_LILLIE}I'd like that.\n"
	.string "We could have tea in Olivine.$"

SunMoonAltar_Text_FamilyLusamineGladion:
	.string "{SPEAKER NAME_LUSAMINE}Will you join us, Gladion?$"

SunMoonAltar_Text_FamilyGladion:
	.string "{SPEAKER NAME_GLADION}…Yeah.\n"
	.string "I can stay a while.$"

SunMoonAltar_Text_FarewellLooker:
	.string "{SPEAKER NAME_LOOKER}The Pokémon are ready for transport.\n"
	.string "We'll see them safely aboard.$"

SunMoonAltar_Text_FarewellAnabel:
	.string "{SPEAKER NAME_ANABEL}There are still other passages\n"
	.string "to check. Looker and I will stay here.\p"
	.string "Next time, we'll be ready\n"
	.string "for what arrives.$"

SunMoonAltar_Text_FarewellGladion:
	.string "{SPEAKER NAME_GLADION}You brought them back.\n"
	.string "Good work, {PLAYER}.$"

SunMoonAltar_Text_FarewellKukui:
	.string "{SPEAKER NAME_KUKUI}Go get some rest, cousin.\p"
	.string "I'd like our next battle to be\n"
	.string "on a beach with nothing\l"
	.string "coming out of it.$"

SunMoonAltar_Text_FarewellLusamine:
	.string "{SPEAKER NAME_LUSAMINE}Thank you, {PLAYER}.\n"
	.string "Take good care of them.$"

SunMoonAltar_Text_FarewellLookerHome:
	.string "{SPEAKER NAME_LOOKER}The sailor will take you home.\n"
	.string "We'll call if we need you.$"

SunMoonAltar_Text_RetryAnabel:
	.string "{SPEAKER NAME_ANABEL}Everyone's back.\n"
	.string "Rest your team before we try again.$"

SunMoonAltar_Text_RetryLusamine:
	.string "{SPEAKER NAME_LUSAMINE}The outside unit is ready.\n"
	.string "I'll stay here.$"

SunMoonAltar_Text_RetryGladion:
	.string "{SPEAKER NAME_GLADION}We've still got the exit.\n"
	.string "Take the time you need.$"

SunMoonAltar_Text_LusamineReady:
	.string "{SPEAKER NAME_LUSAMINE}I'll be at the controls.\n"
	.string "Anabel knows how to reach me.$"

SunMoonAltar_Text_LillieReady:
	.string "{SPEAKER NAME_LILLIE}We've cleared a path\n"
	.string "for the larger ones.\l"
	.string "Ninetales will stay with me.$"

SunMoonAltar_Text_GladionReady:
	.string "{SPEAKER NAME_GLADION}Nothing's blocking the way back.\n"
	.string "I'll keep it that way.$"

SunMoonAltar_Text_KukuiReady:
	.string "{SPEAKER NAME_KUKUI}Both units passed the test.\n"
	.string "We'll watch the readings from this side.$"

SunMoonAltar_Text_LookerHealAsk:
	.string "{SPEAKER NAME_LOOKER}Shall I take care of your Pokémon?$"

SunMoonAltar_Text_LookerHealDone:
	.string "{SPEAKER NAME_LOOKER}There. Ready for the next step.$"

SunMoonAltar_Text_LookerHealNo:
	.string "{SPEAKER NAME_LOOKER}Whenever you need it.$"

SunMoonAltar_Text_LookerPost:
	.string "{SPEAKER NAME_LOOKER}Welcome back, {PLAYER}.\n"
	.string "Supplies are ready, and so are we.$"

SunMoonAltar_Text_AnabelPost:
	.string "{SPEAKER NAME_ANABEL}The passage is stable today.\n"
	.string "We're checking where the others lead.$"

SunMoonAltar_Text_AnabelKurt:
	.string "{SPEAKER NAME_ANABEL}For more Beast Balls, speak to Kurt\n"
	.string "in Azalea. He made the one we used here.$"

SunMoonAltar_Text_LusaminePost:
	.string "{SPEAKER NAME_LUSAMINE}We've been checking on the Pokémon\n"
	.string "that came back with us.\p"
	.string "Aether entrusted Nihilego to my care.\n"
	.string "I intend to give her the time she needs.$"

SunMoonAltar_Text_LusamineRematchAsk:
	.string "{SPEAKER NAME_LUSAMINE}Would you care for another battle?\n"
	.string "I'd like to face your team again.$"

SunMoonAltar_Text_LusamineRematchNo:
	.string "{SPEAKER NAME_LUSAMINE}Another time, then.$"

@ printed inside the battle (see DuelLusamineBeaten)
SunMoonAltar_Text_LusamineRematchBeaten:
	.string "{SPEAKER NAME_LUSAMINE}Nicely done.$"

SunMoonAltar_Text_LusamineRematchAfter:
	.string "{SPEAKER NAME_LUSAMINE}Thank you for the battle.\n"
	.string "We'll be ready for the next one.$"

SunMoonAltar_Text_LusamineDoneToday:
	.string "{SPEAKER NAME_LUSAMINE}That's enough for today.\n"
	.string "My Pokémon could use a rest.$"

SunMoonAltar_Text_SailorAsk:
	.string "{SPEAKER NAME_SAILOR}Shall we sail back to Olivine?$"

SunMoonAltar_Text_SailorDepart:
	.string "{SPEAKER NAME_SAILOR}All aboard!$"

SunMoonAltar_Text_SailorStay:
	.string "{SPEAKER NAME_SAILOR}I'll be here at the pier.$"

SunMoonAltar_Text_RiftDailyAsk:
	.string "{SPEAKER NAME_ANABEL}The passage to the Nexus is\n"
	.string "steady. Would you like to go through?$"

SunMoonAltar_Text_RiftDailyNo:
	.string "{SPEAKER NAME_ANABEL}All right. Come back when you're ready.$"

SunMoonAltar_Text_RiftDailyUsed:
	.string "{SPEAKER NAME_ANABEL}The Nexus has gone quiet for today.\n"
	.string "It will shift again tomorrow.$"

@ SKELETON: R10 refusal, placeholder voice.
SunMoonAltar_Text_RiftTooManyLegendaries:
	.string "{SPEAKER NAME_ANABEL}Wait. You're carrying more than one\n"
	.string "legendary Pokémon.$"

SunMoonAltar_Text_RiftTooManySubs:
	.string "{SPEAKER NAME_ANABEL}Wait. You're carrying more than one\n"
	.string "rare Pokémon of that kind - the ones\l"
	.string "like the Ultra Beasts.$"

SunMoonAltar_Text_RiftTooManyMegas:
	.string "{SPEAKER NAME_ANABEL}Wait. More than one of your Pokémon\n"
	.string "is ready to Mega Evolve.$"

SunMoonAltar_Text_RiftTraditionalRule:
	.string "{SPEAKER NAME_ANABEL}The passage only holds one legendary,\n"
	.string "one of the rarer kind and one Mega\l"
	.string "Evolution at a time. Everyone inside\l"
	.string "follows the same rule.$"

SunMoonAltar_Text_Officer:
	.string "{SPEAKER NAME_OFFICER}Looker's orders. Nobody goes up\n"
	.string "that stair without a reason.\p"
	.string "You're the reason, I hear.\n"
	.string "Go on up. They're waiting.$"

SunMoonAltar_Text_AetherStaff:
	.string "{SPEAKER NAME_AETHER}Blankets, food, transport cases...\n"
	.string "All of it is for the Pokémon.\p"
	.string "Whatever comes through up there,\n"
	.string "we look after it down here.$"

SunMoonAltar_Text_OfficerPost:
	.string "{SPEAKER NAME_OFFICER}The nine went out on the transport.\n"
	.string "We stayed for whatever comes next.\p"
	.string "Quiet island, most days.\n"
	.string "I'd like to keep it that way.$"

SunMoonAltar_Text_AetherHealAsk:
	.string "{SPEAKER NAME_AETHER}Back from the passage?\n"
	.string "Let me look after your Pokémon.$"

SunMoonAltar_Text_AetherHealDone:
	.string "{SPEAKER NAME_AETHER}All done. They're in good shape.$"

SunMoonAltar_Text_AetherHealNo:
	.string "{SPEAKER NAME_AETHER}We're right here if you need us.$"
