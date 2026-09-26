@ ===========================================================================
@ Sun and Moon Altar - Ultra Necrozma, the last story event of the Rift
@ Missions arc. Plan: .claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md
@
@ Five acts across a map and a half, driven entirely by VAR_RIFT_MISSIONS_STATE:
@   12 -> 13  Act I,   the arrival           (the five stair coord_events)
@   13 -> 14  Act II,  Lusamine's duel, and Act III, the rift opens
@   14 -> 15  Act IV,  in MAP_ULTRA_SPACE_ARENA
@   15 -> 16  Act V,   the farewell          (the frame trigger)
@   >= 16     permanent post-game
@
@ NOTHING here is persisted beyond that var and five daily flags. All visibility
@ is FLAG_TEMP_* recomputed on every load, so a blackout retry always finds the
@ map clean (skill visibilidade-e-gatilhos section 6).
@
@ NEVER removeobject any object on FLAG_TEMP_1: removeobject SETS the object's
@ flag, so removing Lillie would take Gladion, both partners and Kukui with her,
@ mid-sentence, with a clean build. Everybody who leaves this map leaves by the
@ warpsilent at the end of a scene.
@ ===========================================================================

SunMoonAltar_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SunMoonAltar_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SunMoonAltar_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SunMoonAltar_OnFrame
	.byte 0

@ Runs before the first spawn on EVERY load. Three independent decisions, all
@ recomputed from VAR_RIFT_MISSIONS_STATE, none of them ever persisted:
@   1. the five visitors and the two partners (FLAG_TEMP_1)
@   2. Lusamine alone (FLAG_TEMP_5) - she is the only one who comes back
@   3. the ground rift (FLAG_TEMP_2), story branch and daily branch
@ plus the weather, which a map load applies by itself from here.
@ The two legendary objects (FLAG_TEMP_3/4) are NEVER shown here: only a scene
@ addobjects them. Setting both unconditionally is what guarantees that a
@ blackout retry finds the map clean.
SunMoonAltar_OnTransition::
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	call SunMoonAltar_EventScript_ApplyCastVisibility
	call SunMoonAltar_EventScript_ApplyLusamineVisibility
	call SunMoonAltar_EventScript_ApplyRiftVisibility
	call SunMoonAltar_EventScript_ApplyWeather
	call SunMoonAltar_EventScript_ApplyResidents
	end

@ The disc art is ON_LOAD and not ON_TRANSITION, and that is not a style choice:
@ setmetatile writes into gBackupMapLayout, which only exists after InitMap, and
@ InitMap is what calls the ON_LOAD script (src/fieldmap.c). From ON_TRANSITION
@ the write lands nowhere and the disc silently never changes - with a clean
@ build. Every setmetatile in this repository hangs off ON_LOAD for this reason.
SunMoonAltar_OnLoad::
	call SunMoonAltar_EventScript_ApplyDisc
	end

@ The five visitors plus the two partners: present from the first arrival (12)
@ through the farewell (15), gone for good from 16 on.
@ Written as one goto_if_lt plus one goto_if_ge, a window closed on BOTH sides,
@ so that the day state 17 exists nothing here starts behaving differently.
SunMoonAltar_EventScript_ApplyCastVisibility::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_HideCast
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_HideCast
	clearflag FLAG_TEMP_1
	return
SunMoonAltar_EventScript_HideCast::
	setflag FLAG_TEMP_1
	return

@ Lusamine: with the cast in 12..15, and then on her own rota from 16 on. She
@ needs a flag of her own because in state 16 the group splits - Looker and
@ Anabel live here, the other five never come back, and only she returns.
@ The weekday rota of section 10.1 of the plan; nobody is in two places on the
@ same day.
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

@ The rift: open and unconditional during the climax (14, 15), then once a day
@ for ever. FLAG_DAILY_ALTAR_RIFT is cleared by ClearDailyFlags at the date
@ rollover, so "once a day" costs one daily flag and no var.
SunMoonAltar_EventScript_ApplyRiftVisibility::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_ShowRift
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_ShowRift
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_HideRift
	goto_if_set FLAG_DAILY_ALTAR_RIFT, SunMoonAltar_EventScript_HideRift
SunMoonAltar_EventScript_ShowRift::
	clearflag FLAG_TEMP_2
	return
SunMoonAltar_EventScript_HideRift::
	setflag FLAG_TEMP_2
	return

@ Looker and Anabel LIVE here from state 16 on, and standing to attention facing
@ a hole in the air for ever is not living there. From 16 they wander instead.
@ setobjectmovementtype writes the TEMPLATE (gSaveBlock1Ptr->objectEventTemplates),
@ not the live object, so it only takes effect on the next spawn - which is why it
@ belongs in ON_TRANSITION, the one script that runs after
@ LoadObjEventTemplatesFromHeader has reset the templates and before the objects
@ spawn. Doing it from ON_LOAD or from an object script would change nothing.
@ States 12..15 are left alone deliberately: Acts I and V place both of them by
@ coordinate and turn them with turnobject, and a wandering NPC would break the
@ blocking of two scenes with a clean build.
@ The range is 1 in both axes (map.json), measured against the collision:
@   Looker (13,13) can reach x 13..14, y 12..14   (12 and 15+ are wall)
@   Anabel (15,13) can reach x 14..15, y 12..14
@ Neither reaches (14,10), which is the rift, nor (14,11), which is the tile the
@ player lands on coming back out of it; and the neck at y=12 is three tiles wide
@ (x=13..15), so the two of them can never close it.
SunMoonAltar_EventScript_ApplyResidents::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_ResidentsOnDuty
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_LOOKER, MOVEMENT_TYPE_WANDER_AROUND
	setobjectmovementtype LOCALID_SUN_MOON_ALTAR_ANABEL, MOVEMENT_TYPE_WANDER_AROUND
SunMoonAltar_EventScript_ResidentsOnDuty::
	return

@ 13..15 is the unstable chapter; everything else is a clear altar. setweather
@ from ON_TRANSITION is applied by the map load itself, so no doweather here.
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

@ The altar's disc has a second art state baked into gTileset_AltarSunMoon.
@ Seven metatiles, all impassable in both states - the disc is on the wall and
@ nobody ever walks on it. DrawWholeMapView is what makes the swap visible when
@ it happens on screen; from ON_LOAD the map has not been drawn yet and the call
@ is harmless.
@ The calm disc uses palettes 9 and 10, which ARE in SWAP_PALS_ALTAR_SUN_MOON,
@ so it shows a sun by day and a moon by night. The portal metatiles use palette
@ 11, which is NOT in that list, so the tear looks the same at both hours. That
@ is intentional and it is the right reading. Do not "fix" it.
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

@ ---------------------------------------------------------------------------
@ The two entrances into a scene, and they may NOT share a VAR_TEMP.
@
@ Act I is reached on foot, up the stair at y=15, by five coord_events on
@ VAR_TEMP_0. Act V is reached by coming back out of the rift at (14,11), which
@ is a load, so it needs a frame trigger - and a frame trigger sets its own var
@ as its first instruction on EVERY load. If both used VAR_TEMP_1, that setvar
@ would make the coord_event condition (VAR_TEMP_1 == 0) never true again and
@ Act I would silently never play: the player would walk into a courtyard full
@ of people standing still, with a clean build.
@
@ The coord_events need no latch of their own: a coord_event fires on STEPPING
@ onto the tile, not every frame, so there is no livelock to avoid, and what
@ stops the scene repeating is the state (Act I ends at 13, and 13 matches
@ nothing in the list).
@ ---------------------------------------------------------------------------
SunMoonAltar_OnFrame::
	map_script_2 VAR_TEMP_1, 0, SunMoonAltar_EventScript_FrameTrigger
	.2byte 0

SunMoonAltar_EventScript_StairTrigger::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_Arrival
	end

@ Fires on the load that follows the warp back from the arena, which always
@ lands the player on (14,11). Every other load falls through in a couple of
@ instructions: the Act III warpsilent (state 14, player at (14,14)), the
@ Unresolved/NoRoom warp (state 14, player at (14,11) - dies on the state test)
@ and Act V's own reload (state 16).
SunMoonAltar_EventScript_FrameTrigger::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_End
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 14, SunMoonAltar_EventScript_End
	goto_if_ne VAR_0x8005, 11, SunMoonAltar_EventScript_End
	goto SunMoonAltar_EventScript_Farewell
SunMoonAltar_EventScript_End::
	end

@ Reusable camera shake, so no scene writes the numbers twice. ShakeCamera reads
@ FOUR vars (data/specials.inc), not two: pan, pan, count, delay. Passing only
@ two leaves VAR_0x8006/8007 holding whatever the last call left there and the
@ shake comes out with a random duration, with nothing in the build to show it.
@ Signature copied from BlackthornCity_EventScript_UBShake.
SunMoonAltar_EventScript_Shake::
	setvar VAR_0x8004, 1    @ vertical pan
	setvar VAR_0x8005, 1    @ horizontal pan
	setvar VAR_0x8006, 12   @ num shakes
	setvar VAR_0x8007, 4    @ shake delay
	special ShakeCamera
	waitstate
	return

@ ---------------------------------------------------------------------------
@ ACT I - the arrival. State 12 -> 13. Reached only from the stair coord_events
@ at (12..16, 15), so the player is always one tile south of the terrace.
@
@ Choreography, measured on dump_mapa.py SunMoonAltar:
@   player      (x,15) -> walk_up -> (x,14), facing up. Any x in 12..16 is free
@               on y=14, and Kukui at (10,14) is never in the way.
@   Looker      (13,13) turns down     Anabel (15,13) turns down
@   Kukui       (10,14) turns right    (same row as the player, to the west)
@   Lusamine    (14,9)  -> walk_down x2 -> (14,11), turns down
@               ...and at the end walks back up to (14,9) and turns up again, so
@               the map matches the templates after releaseall
@   Lillie      (12,11) turns right    Gladion (16,11) turns left
@               (the two children end up flanking their mother)
@ (14,10) and (14,12) are free in state 12: the rift does not exist yet and the
@ neck at y=12 is the only way down from the platform.
@
@ No faceplayer anywhere in here: in an automatic scene gSelectedObjectEvent is
@ undefined and faceplayer would turn one arbitrary object. Every look is an
@ explicit turnobject with a direction derived from the coordinates.
@
@ Every fade inside this scene is fadescreenswapbuffers, NEVER fadescreen: the
@ scene comes back to this same map, and fadescreen composes the time-of-day
@ tint onto itself, which gets darker with every flash after dusk.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Arrival::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_PlayerStepUp
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_SOUTH
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_SOUTH
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_EAST
	msgbox SunMoonAltar_Text_ArrivalDisc, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalKukui, MSGBOX_DEFAULT
	closemessage
	fadeoutbgm 4
	msgbox SunMoonAltar_Text_ArrivalAnabel, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLooker, MSGBOX_DEFAULT
	closemessage
	@ --- the escalation: the disc stops being a disc ---------------------
	playbgm MUS_DP_LEGEND_APPEARS, TRUE          @ TRUE: a battle restores it
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	call SunMoonAltar_EventScript_DiscToPortal
	fadescreenswapbuffers FADE_FROM_WHITE
	setweather WEATHER_VOLCANIC_ASH
	doweather
	delay 40
	msgbox SunMoonAltar_Text_ArrivalTurns, MSGBOX_DEFAULT
	closemessage
	call SunMoonAltar_EventScript_PartnerStirs      @ optional, no state
	applymovement LOCALID_SUN_MOON_ALTAR_GLADION, Common_Movement_ExclamationMark
	waitmovement LOCALID_SUN_MOON_ALTAR_GLADION
	msgbox SunMoonAltar_Text_ArrivalGladionBack, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLillieDoor, MSGBOX_DEFAULT
	closemessage
	@ --- the offer -------------------------------------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_LusamineDown
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_WEST
	msgbox SunMoonAltar_Text_ArrivalOffer, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalOfferWhy, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalOfferCost, MSGBOX_DEFAULT
	closemessage
	@ --- the children ----------------------------------------------------
	msgbox SunMoonAltar_Text_ArrivalLillieNo, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLillieNoTwo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_SILVALLY, Common_Movement_WalkInPlaceFasterLeft
	waitmovement LOCALID_SUN_MOON_ALTAR_SILVALLY
	msgbox SunMoonAltar_Text_ArrivalGladionNo, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalAnabelCondition, MSGBOX_DEFAULT
	closemessage
	@ --- she goes back to looking at the door -----------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_LusamineUp
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	msgbox SunMoonAltar_Text_ArrivalLusamineWaits, MSGBOX_DEFAULT
	closemessage
	@ --- the handoff to the player ---------------------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, SunMoonAltar_Movement_LookerAside
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	msgbox SunMoonAltar_Text_ArrivalLookerAside, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLookerHand, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, SunMoonAltar_Movement_LookerBack
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	goto SunMoonAltar_EventScript_ArrivalDone

@ No warpsilent here: nothing about the map's population changes, everybody
@ ended on the tile their template names, and the player has to be left standing
@ in the courtyard. That is the whole point of the act.
@ FLAG_VISITED_SUN_MOON_ALTAR is set HERE and not at the pier: switching it on
@ at the pier would let the player fly here before the scene that gives the
@ place its meaning ever ran.
SunMoonAltar_EventScript_ArrivalDone::
	setvar VAR_RIFT_MISSIONS_STATE, 13
	setflag FLAG_VISITED_SUN_MOON_ALTAR   @ the altar becomes a Fly destination
	fadedefaultbgm
	releaseall
	end

SunMoonAltar_Movement_PlayerStepUp:
	walk_up
	face_up
	step_end

SunMoonAltar_Movement_LusamineDown:
	walk_down
	walk_down
	face_down
	step_end

SunMoonAltar_Movement_LusamineUp:
	walk_up
	walk_up
	face_up
	step_end

@ Looker takes one step west, away from the family, which is the staging of his
@ line: he is stepping out of the argument, not into it. (12,13) is free.
SunMoonAltar_Movement_LookerAside:
	walk_left
	face_down
	step_end

SunMoonAltar_Movement_LookerBack:
	walk_right
	face_down
	step_end

@ The optional reaction to the player's partner. No flag, no persistent var: if
@ there is nothing of the Cosmog family in the party the scene is identical and
@ nothing is missing. VAR_TEMP_4 caches the species because Act III reads it,
@ but Act III reads it AGAIN from the special - never trust a temp across loads.
@ CheckMysteryEggPokemon walks the whole party and ignores eggs.
SunMoonAltar_EventScript_PartnerStirs::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, SunMoonAltar_EventScript_PartnerStirsEnd
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOG, SunMoonAltar_EventScript_PartnerStirsSmall
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, SunMoonAltar_EventScript_PartnerStirsSmall
	msgbox SunMoonAltar_Text_PartnerStirsLegend, MSGBOX_DEFAULT
	closemessage
	return
SunMoonAltar_EventScript_PartnerStirsSmall::
	msgbox SunMoonAltar_Text_PartnerStirsSmall, MSGBOX_DEFAULT
	closemessage
SunMoonAltar_EventScript_PartnerStirsEnd::
	return

@ ---------------------------------------------------------------------------
@ ACT II - Lusamine's duel. One object script, five branches by state:
@   < 13  she is not here (FLAG_TEMP_5 keeps her hidden) - unreachable
@   13    the duel: one YES/NO. NO changes nothing and is repeatable.
@   14    the rift is open and she is holding the anchor
@   15    transient: the farewell has not played yet
@   >= 16 post-game: her line, plus one rematch a day
@ Nothing changes state before the YES. The YES is the last exit point.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Lusamine::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LusaminePost
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_LusamineIdle
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_LusamineAnchor
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_LusamineIdle
	msgbox SunMoonAltar_Text_DuelApproach, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_DuelAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_DuelDeclined
	goto SunMoonAltar_EventScript_Duel

@ NO costs nothing: no flag, no var, no movement. The player can walk away, heal,
@ come back and be asked again, word for word.
SunMoonAltar_EventScript_DuelDeclined::
	msgbox SunMoonAltar_Text_DuelDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

SunMoonAltar_EventScript_LusamineIdle::
	msgbox SunMoonAltar_Text_LusamineIdle, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LusamineAnchor::
	msgbox SunMoonAltar_Text_LusamineAnchor, MSGBOX_DEFAULT
	release
	end

@ Narrative duel: NO blackout, NO penalty, and BOTH outcomes move the story to
@ state 14. The player's win is not what convinces her and the player's loss does
@ not stop the story - Lillie is who ends the argument, in every branch, because
@ the design forbids rewriting this as the player's victory.
@ Reached from an object script (lock) and it moves other objects, so it
@ escalates to lockall - the same pattern as every mission scene in the arc.
SunMoonAltar_EventScript_Duel::
	closemessage
	lockall
	msgbox SunMoonAltar_Text_DuelAccept, MSGBOX_DEFAULT
	closemessage
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_3, VAR_RESULT              @ remember if it was ALREADY on
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_LUSAMINE, SunMoonAltar_Text_DuelLusamineBeaten
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT              @ copy IMMEDIATELY, before anything
	goto_if_eq VAR_TEMP_3, TRUE, SunMoonAltar_EventScript_DuelKeepWhiteout
	clearflag B_FLAG_NO_WHITEOUT
SunMoonAltar_EventScript_DuelKeepWhiteout::
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, SunMoonAltar_EventScript_DuelWon
	goto_if_eq VAR_TEMP_2, B_OUTCOME_LOST, SunMoonAltar_EventScript_DuelLost
	goto_if_eq VAR_TEMP_2, B_OUTCOME_DREW, SunMoonAltar_EventScript_DuelDrew
	goto_if_eq VAR_TEMP_2, B_OUTCOME_FORFEITED, SunMoonAltar_EventScript_DuelForfeited
	goto SunMoonAltar_EventScript_DuelUnexpected

@ The player won. She is not convinced by losing - she is interrupted by it.
SunMoonAltar_EventScript_DuelWon::
	msgbox SunMoonAltar_Text_DuelWon, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

@ The player lost. She won and it changed nothing, which is the better scene.
SunMoonAltar_EventScript_DuelLost::
	msgbox SunMoonAltar_Text_DuelLost, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

SunMoonAltar_EventScript_DuelDrew::
	msgbox SunMoonAltar_Text_DuelDrew, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

SunMoonAltar_EventScript_DuelForfeited::
	msgbox SunMoonAltar_Text_DuelForfeited, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

@ Unexpected: this scene is reached by TALKING to her, not by a frame trigger, so
@ it is allowed to stop. Nothing is marked, nobody has moved yet, and the player
@ can simply speak to her again. It is NEVER a win.
SunMoonAltar_EventScript_DuelUnexpected::
	msgbox SunMoonAltar_Text_DuelUnexpected, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ ---------------------------------------------------------------------------
@ Common tail of all four outcomes, and ACT III inside it: the rift opens.
@
@ Choreography. A battle does NOT reload the map and nobody moved during the
@ duel, so the positions here are the templates plus wherever the player was
@ standing when they spoke to her:
@   Lusamine (14,9) facing the player  player on (13,9), (15,9) or (14,10)
@   Lillie   (12,11) -> walk_right -> (13,11), turn up
@   partner  addobject at (13,10), facing up at the disc
@   the rift addobject at (14,10)
@ (13,11) and (13,10) are free and elevation 3 (dump_mapa.py).
@
@ THE PLAYER CAN BE STANDING ON (14,10): it is one of the three tiles from which
@ Lusamine at (14,9) is reachable, and it is exactly where the rift is about to
@ be added. An object always blocks its own tile, so the player is stepped one
@ tile south first. (14,11) is free, and this is also where the player wants to
@ be to watch the tear open.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_DuelSettled::
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8005, 10, SunMoonAltar_EventScript_PlayerOffRiftTile
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_LillieForward
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	msgbox SunMoonAltar_Text_DuelLillieEnds, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_DuelLusamineYields, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_DuelGladion, MSGBOX_DEFAULT
	closemessage
	@ --- the partner answers the altar ------------------------------------
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	call SunMoonAltar_EventScript_ShowPartner
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	addobject LOCALID_SUN_MOON_ALTAR_RIFT
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_IN
	msgbox SunMoonAltar_Text_RiftOpens, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_RiftKukui, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_RiftAnabel, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelResolved

@ Only reachable with the player on (14,10) - y=10 is walkable at x=10..18, but
@ (14,10) is the only one of those tiles from which Lusamine can be spoken to.
SunMoonAltar_EventScript_PlayerOffRiftTile::
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_PlayerStepDown
	waitmovement OBJ_EVENT_ID_PLAYER
	return

SunMoonAltar_Movement_PlayerStepDown:
	walk_down
	face_up
	step_end

@ Exactly one of the two legendaries is added, chosen by what is actually in the
@ party. VAR_TEMP_4 was filled by PartnerStirs in Act I, but this scene is
@ reachable in a later visit, so it is read again here - never trust a temp
@ across map loads.
@ If the player deposited the partner after the reunion, nothing is added and the
@ scene still works: the rift opens anyway, and the RIFT script is what refuses
@ to let anybody through. That refusal is repeatable and free.
SunMoonAltar_EventScript_ShowPartner::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, SunMoonAltar_EventScript_ShowSolgaleo
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, SunMoonAltar_EventScript_ShowLunala
	return
SunMoonAltar_EventScript_ShowSolgaleo::
	addobject LOCALID_SUN_MOON_ALTAR_SOLGALEO
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	waitmoncry
	return
SunMoonAltar_EventScript_ShowLunala::
	addobject LOCALID_SUN_MOON_ALTAR_LUNALA
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	waitmoncry
	return

@ End of Act II/III. The population of the map changed (the rift and possibly a
@ legendary were added, Lillie moved), so the scene closes the way every scene in
@ this arc closes: state under a fade, then a reload in place, and ON_TRANSITION
@ rebuilds everything from the var.
@ fadescreen and not fadescreenswapbuffers HERE and only here: this is the fade
@ that precedes a warpsilent, and the load rebuilds the palettes anyway.
@ (14,14) is free, is not a warp, and is where the player can see the rift. The
@ stair trigger fires again after this load with VAR_TEMP_1 zeroed, but dies
@ immediately: state 14 matches no goto_if_eq in its list.
@ The partner does NOT survive this warpsilent, and that is how it has to be:
@ FLAG_TEMP_3/4 are set again on the load. It came out to answer the altar and
@ went back to its Ball. Act IV is what brings it back.
SunMoonAltar_EventScript_DuelResolved::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 14
	warpsilent MAP_SUN_MOON_ALTAR, 14, 14
	waitstate
	releaseall
	end

SunMoonAltar_Movement_LillieForward:
	walk_right
	face_up
	step_end

@ ---------------------------------------------------------------------------
@ THE RIFT. One object, three lives:
@   14        the climax: Ultra Necrozma is on the other side
@   15        transient: harmonised, but the farewell has not played yet
@   >= 16     the daily expedition (the LOOP document starts here)
@ Its visibility is ON_TRANSITION's job; this script only decides what happens
@ when the player faces it and presses A. It stands ON (14,10) and the player
@ stands at (14,11) - an object event always blocks its own tile, exactly like
@ the four portals of SpearPillarTop.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Rift::
	lock
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_RiftDaily
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_RiftSettling
	@ --- state 14: the climax --------------------------------------------
	@ 1. Anabel's rule FIRST, before any offer: party full AND PC full blocks,
	@    because the scene on the other side ends in a givemon and a gift that
	@    silently fails is the worst bug this project knows how to write (skill
	@    entregar-pokemon-ou-ovo). Party full ALONE does NOT block: givemon sends
	@    it to the box on its own and blocking there would turn normal behaviour
	@    into a wall. Checking here and not in the arena is deliberate: the
	@    alternative is crossing, winning the hardest fight in the game, and
	@    finding out in the last box that nothing can be received.
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, SunMoonAltar_EventScript_RiftCheckPartner
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftCheckPartner
	msgbox SunMoonAltar_Text_RiftNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

@ 2. The partner. This is the author's "the only way in is with Solgaleo", and it
@    is a gate, not a puzzle: it costs nothing, changes nothing and is repeatable
@    for ever. checkspecies walks gPlayerParty only - a Cosmog, a Cosmoem, an egg
@    or the PC do not satisfy it, and that is correct.
SunMoonAltar_EventScript_RiftCheckPartner::
	checkspecies SPECIES_SOLGALEO
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftAsk
	checkspecies SPECIES_LUNALA
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftAsk
	msgbox SunMoonAltar_Text_RiftNoPartner, MSGBOX_DEFAULT
	closemessage
	release
	end

@ 3. The last exit point. After the YES everything is scripted through to a
@    battle outcome on the other map.
SunMoonAltar_EventScript_RiftAsk::
	msgbox SunMoonAltar_Text_RiftAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftNotYet
	msgbox SunMoonAltar_Text_RiftGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_ULTRA_SPACE_ARENA, 10, 19
	waitstate
	release
	end

SunMoonAltar_EventScript_RiftNotYet::
	msgbox SunMoonAltar_Text_RiftNotYet, MSGBOX_DEFAULT
	closemessage
	release
	end

SunMoonAltar_EventScript_RiftSettling::
	msgbox SunMoonAltar_Text_RiftSettling, MSGBOX_DEFAULT
	release
	end

@ --- state >= 16: the daily expedition --------------------------------------
@ The flag is set ON THE WAY IN, not on the way out, so a player who walks in,
@ turns round and walks out has still used today's rift. That is deliberate: the
@ alternative is a re-entry loop that the LOOP document would have to undo.
@ ON_TRANSITION hides the object as soon as the altar reloads.
SunMoonAltar_EventScript_RiftDaily::
	msgbox SunMoonAltar_Text_RiftDailyAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftDailyNo
	setflag FLAG_DAILY_ALTAR_RIFT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_ULTRA_SPACE_ARENA, 10, 19
	waitstate
	release
	end

SunMoonAltar_EventScript_RiftDailyNo::
	msgbox SunMoonAltar_Text_RiftDailyNo, MSGBOX_DEFAULT
	closemessage
	release
	end

@ ---------------------------------------------------------------------------
@ ACT V - the farewell. State 15 -> 16. Positions on entry are the templates
@ (the map reloaded when the player came back): Lusamine (14,9), Lillie (12,11),
@ Ninetales (11,11), Gladion (16,11), Silvally (17,11), Looker (13,13), Anabel
@ (15,13), Kukui (10,14), rift (14,10), player (14,11).
@
@ Note who is standing where: the player is BETWEEN the rift and everybody else,
@ and Lusamine is on the far side of the rift. Nobody moves for the first half of
@ the scene, because the picture is already right.
@
@ No removeobject on the seven who leave: FLAG_TEMP_1 is set again on the load
@ after the warpsilent and they simply do not spawn. A removeobject on Lillie
@ would SET FLAG_TEMP_1 and take Gladion, both partners and Kukui with her, in
@ the middle of the scene.
@ Lusamine is the interesting exception: she is on FLAG_TEMP_5, so coming out of
@ Act V she may genuinely still be at the altar the next day. That is correct,
@ not a bug, and her state >= 16 line assumes exactly that.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Farewell::
	lockall
	hidefollower
	delay 20
	@ --- Looker, always, first ---------------------------------------------
	msgbox SunMoonAltar_Text_FarewellHurt, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellShowThem, MSGBOX_DEFAULT
	closemessage
	@ --- what the player brought back --------------------------------------
	call SunMoonAltar_EventScript_ShowPartner
	msgbox SunMoonAltar_Text_FarewellKukui, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLillie, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellGladion, MSGBOX_DEFAULT
	closemessage
	@ --- Lusamine comes down, for the last time ----------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_LusamineAside
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	msgbox SunMoonAltar_Text_FarewellLusamine, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLusamineAsks, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLillieAnswers, MSGBOX_DEFAULT
	closemessage
	@ --- the altar comes back ----------------------------------------------
	fadeoutbgm 4
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	call SunMoonAltar_EventScript_DiscToCalm
	fadescreenswapbuffers FADE_FROM_WHITE
	setweather WEATHER_NONE
	doweather
	delay 40
	msgbox SunMoonAltar_Text_FarewellCalm, MSGBOX_DEFAULT
	closemessage
	@ --- but not all the way back -------------------------------------------
	playse SE_WARP_IN
	msgbox SunMoonAltar_Text_FarewellStillThere, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellAnabelStays, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLookerStays, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellGoodbye, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_FarewellDone

@ Lusamine steps off the disc's column onto (13,9) and turns to the group, which
@ is the whole point of her line: for the first time in the event she is not
@ looking at the door. (13,9) is free.
SunMoonAltar_Movement_LusamineAside:
	walk_left
	face_down
	step_end

@ The map's population changes completely: five visitors and the two partners
@ leave for good and the rift becomes a daily thing. Reload in place and let
@ ON_TRANSITION build state 16 from scratch - which is also what stops the player
@ from seeing seven objects vanish one at a time as the camera moves.
@ (14,11) again: it is where the player already is, and it is not a warp.
SunMoonAltar_EventScript_FarewellDone::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 16
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ The object scripts of the people who are standing around. An event that leaves
@ the player loose in the middle of it (states 13, 14 and 15) needs all seven to
@ have something to say while he decides.
@ ---------------------------------------------------------------------------

@ Looker: 12..14 is the crisis, 15 is the few seconds before the farewell, >= 16
@ is home. He HEALS from state 13 on, not from 16 on: 13 and 14 are exactly the
@ states where it matters, because the boss retry lands the player on the
@ mainland and the boat back passes no Center. Looker checking on everybody's
@ Pokemon before anything else is his single most established behaviour in the
@ whole arc.
SunMoonAltar_EventScript_Looker::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LookerHome
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_LookerIdle
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_LookerCrisisHeal
	msgbox SunMoonAltar_Text_LookerCrisis, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LookerIdle::
	msgbox SunMoonAltar_Text_LookerIdle, MSGBOX_DEFAULT
	release
	end

@ Same YES/NO as the post-game branch, different opening box: during the crisis
@ he is not being hospitable, he is being a field medic with a kettle.
SunMoonAltar_EventScript_LookerCrisisHeal::
	msgbox SunMoonAltar_Text_LookerCrisis, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_LookerHealAsk

SunMoonAltar_EventScript_LookerHome::
	msgbox SunMoonAltar_Text_LookerHome, MSGBOX_DEFAULT
	closemessage
SunMoonAltar_EventScript_LookerHealAsk::
	msgbox SunMoonAltar_Text_LookerHeal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_LookerNoHeal
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SunMoonAltar_Text_LookerHealed, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LookerNoHeal::
	msgbox SunMoonAltar_Text_LookerNoHeal, MSGBOX_DEFAULT
	release
	end

@ Anabel. NO pokemart anywhere in this file: she does not sell Beast Balls, she
@ says where they come from. The second box is the ONLY pointer in the whole game
@ to Kurt's recipe system (.claude/KURT_BALL_CRAFT_DESIGN.md), so it has to name
@ the man, the town and the fact that it is daily.
SunMoonAltar_EventScript_Anabel::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_AnabelHome
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_AnabelIdle
	msgbox SunMoonAltar_Text_AnabelCrisis, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_AnabelIdle::
	msgbox SunMoonAltar_Text_AnabelIdle, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_AnabelHome::
	msgbox SunMoonAltar_Text_AnabelHome, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_AnabelKurt, MSGBOX_DEFAULT
	release
	end

@ Lillie, Gladion and Kukui exist in states 12..15 only - from 16 on FLAG_TEMP_1
@ keeps them off this map for good, so they need no >= 16 branch. State 15 is
@ unreachable in practice (the farewell fires on the load) and falls in with 14.
SunMoonAltar_EventScript_Lillie::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_LillieAnchor
	msgbox SunMoonAltar_Text_LillieCrisis, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LillieAnchor::
	msgbox SunMoonAltar_Text_LillieAnchor, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Gladion::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_GladionAnchor
	msgbox SunMoonAltar_Text_GladionCrisis, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_GladionAnchor::
	msgbox SunMoonAltar_Text_GladionAnchor, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_Kukui::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_KukuiAnchor
	msgbox SunMoonAltar_Text_KukuiCrisis, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_KukuiAnchor::
	msgbox SunMoonAltar_Text_KukuiAnchor, MSGBOX_DEFAULT
	release
	end

@ ---------------------------------------------------------------------------
@ Post-game: Lusamine's weekday visit and her one rematch a day.
@ A normal trainer battle: losing here is a normal blackout, and that is correct.
@ The narrative duel was Act II and it is over - there is no B_FLAG_NO_WHITEOUT
@ in any of the four post-game rematches.
@ trainerbattle_no_intro and not trainerbattle_single, because the approach is a
@ conversation and not a line of sight.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_LusaminePost::
	msgbox SunMoonAltar_Text_LusaminePost, MSGBOX_DEFAULT
	closemessage
	goto_if_set FLAG_DAILY_REMATCH_LUSAMINE, SunMoonAltar_EventScript_LusamineDoneToday
	msgbox SunMoonAltar_Text_LusamineRematchAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_LusamineRematchNo
	@ The daily flag is set BEFORE the battle, not after: after is unreachable on
	@ a loss, because the blackout never comes back to this script. Setting it
	@ first means losing spends the day, which is the right behaviour for a
	@ rematch and what the Battle Cafe already does.
	setflag FLAG_DAILY_REMATCH_LUSAMINE
	trainerbattle_no_intro TRAINER_LUSAMINE_ALTAR, SunMoonAltar_Text_LusamineRematchBeaten
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

@ Ferry back to Olivine (the way here is the port sailor + ITEM_SUN_MOON_TICKET).
@ Same send-off as the Faraway Island sailor: the sailor boards, the player
@ hides, the SS Tidal sails east, then a silent warp to the Olivine desk at
@ (8,16), right above the port sailor. Unchanged by the altar event.
SunMoonAltar_EventScript_Sailor::
	lock
	faceplayer
	msgbox SunMoonAltar_Text_Sailor, MSGBOX_YESNO
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
@ Texts. The old placeholders used the "LUSAMINE: " prefix that V17 of the design
@ abolished; they are replaced whole here by the SPEAKER name plate.
@ Every scene uses one msgbox + closemessage per box, never one giant msgbox:
@ msgbox expands the WHOLE text into gStringVar4 first and gStringVar4 is 1000
@ bytes, so a long scene in one box freezes the game with a clean build.
@ ===========================================================================
@ narration, no name box
SunMoonAltar_Text_ArrivalDisc:
	.string "The disc above the altar is turning.\p"
	.string "There is no wind.$"

SunMoonAltar_Text_ArrivalKukui:
	.string "{SPEAKER NAME_KUKUI}Six weeks I spent on this thing. Two\n"
	.string "moving parts and a whole lot of hope.\p"
	.string "Look at the needle, {PLAYER}. It's flat.\n"
	.string "Not zero -- flat. Like something else is\l"
	.string "already holding the number still.\p"
	.string "That's not a reading going wrong.\n"
	.string "That's a reading being taken. By\l"
	.string "something that isn't me.$"

SunMoonAltar_Text_ArrivalAnabel:
	.string "{SPEAKER NAME_ANABEL}It isn't opening.\p"
	.string "It's open. It has been open a great\n"
	.string "deal longer than we have been standing\l"
	.string "here.\p"
	.string "Don't ask me how I know that. You were\n"
	.string "on the beach in Cherrygrove. You\l"
	.string "already know how I know.$"

SunMoonAltar_Text_ArrivalLooker:
	.string "{SPEAKER NAME_LOOKER}Then we are neither early nor late. We\n"
	.string "are merely… present.\p"
	.string "…Forgive me. That was going to sound\n"
	.string "considerably better than it did.$"

@ narration
SunMoonAltar_Text_ArrivalTurns:
	.string "The face of the disc stopped being a\n"
	.string "face.\p"
	.string "Ash began to fall across the altar --\n"
	.string "and half of it fell upward.$"

@ narration, optional
SunMoonAltar_Text_PartnerStirsSmall:
	.string "{STR_VAR_1}'s Poké Ball shook once,\n"
	.string "hard, and went still.\p"
	.string "It has never done that before.$"

@ narration, optional
SunMoonAltar_Text_PartnerStirsLegend:
	.string "{STR_VAR_1} came out of its Ball without\n"
	.string "being asked.\p"
	.string "It did not look at the ash, or at the\n"
	.string "people. It looked straight up, at the\l"
	.string "hole where the disc used to be, and it\l"
	.string "did not blink.$"

SunMoonAltar_Text_ArrivalGladionBack:
	.string "{SPEAKER NAME_GLADION}Silvally. Back. All the way back.\p"
	.string "Nobody goes up those steps. Not to\n"
	.string "look, not to measure, not for one\l"
	.string "second.$"

SunMoonAltar_Text_ArrivalLillieDoor:
	.string "{SPEAKER NAME_LILLIE}That isn't a door any more.\p"
	.string "A door has two sides that agree with\n"
	.string "each other about where they are.\p"
	.string "Whatever is on the other side of that\n"
	.string "isn't agreeing with anything.$"

@ she has already walked down
SunMoonAltar_Text_ArrivalOffer:
	.string "{SPEAKER NAME_LUSAMINE}Then I will go first.$"

SunMoonAltar_Text_ArrivalOfferWhy:
	.string "{SPEAKER NAME_LUSAMINE}I would like to be precise about my\n"
	.string "reasons, because I was imprecise about\l"
	.string "them once and other people paid the\l"
	.string "invoice.\p"
	.string "I am not offering because I am brave. I\n"
	.string "am offering because I am the correct\l"
	.string "person to spend.\p"
	.string "There is an unstable passage on this\n"
	.string "island. The reason anyone is standing\l"
	.string "beside it at all is that I spent a great\l"
	.string "many years teaching the world to want\l"
	.string "what is on the other side of one.$"

SunMoonAltar_Text_ArrivalOfferCost:
	.string "{SPEAKER NAME_LUSAMINE}I have sent other people's children\n"
	.string "through doors, and called it a\l"
	.string "programme.\p"
	.string "Two of the children were mine.\p"
	.string "So I will go, and I will go alone, and if it\n"
	.string "shuts behind me it shuts behind the\l"
	.string "woman who opened the subject. That is\l"
	.string "not tragedy. That is bookkeeping.$"

SunMoonAltar_Text_ArrivalLillieNo:
	.string "{SPEAKER NAME_LILLIE}No.\p"
	.string "…I'm sorry. I said that faster than I\n"
	.string "meant to.\p"
	.string "I'm not sorry for saying it.$"

SunMoonAltar_Text_ArrivalLillieNoTwo:
	.string "{SPEAKER NAME_LILLIE}Mother, you are doing it again. You\n"
	.string "decided, and then you came here to tell\l"
	.string "us, and you dressed it up so well that it\l"
	.string "sounded like an apology.\p"
	.string "You are allowed to be the one who goes.\p"
	.string "You are not allowed to be the one who\n"
	.string "decides that by yourself. Not any more.\l"
	.string "Not with us standing right here.$"

SunMoonAltar_Text_ArrivalGladionNo:
	.string "{SPEAKER NAME_GLADION}I'm not arguing with her. I've done\n"
	.string "that. It doesn't work.\p"
	.string "I'm just not moving.\p"
	.string "The last time you went looking for\n"
	.string "something like this, it took us years to\l"
	.string "find our way back to each other. You\l"
	.string "want to spend yourself? Get in line.\l"
	.string "It's a long line and I'm at the front of\l"
	.string "it.$"

SunMoonAltar_Text_ArrivalAnabelCondition:
	.string "{SPEAKER NAME_ANABEL}Madame. My condition from Olivine has\n"
	.string "not changed and it is not going to\l"
	.string "change on a beach in the middle of the\l"
	.string "sea.\p"
	.string "Nobody crosses without a way back. Not\n"
	.string "you. Not me. Not the Champion.\p"
	.string "And nothing on this island is a way back\n"
	.string "yet. That is a hole. A door is something\l"
	.string "else.$"

@ she has walked back up to the disc
SunMoonAltar_Text_ArrivalLusamineWaits:
	.string "{SPEAKER NAME_LUSAMINE}Then we appear to have reached an\n"
	.string "impasse, and I am going to stand here\l"
	.string "and look at it until somebody moves.\p"
	.string "I have always been very good at this\n"
	.string "part.$"

SunMoonAltar_Text_ArrivalLookerAside:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. A word, if I may.\p"
	.string "Four of my colleagues have now\n"
	.string "explained to me what happens next, and\l"
	.string "no two of them agree.\p"
	.string "This is not a police matter. I have\n"
	.string "nothing to arrest, and nobody to\l"
	.string "protect anybody from, and I have never\l"
	.string "in my career been less useful.$"

SunMoonAltar_Text_ArrivalLookerHand:
	.string "{SPEAKER NAME_LOOKER}Madame Lusamine will not be talked out\n"
	.string "of this by her children. I have watched\l"
	.string "them try. I will not ask them to try\l"
	.string "again.\p"
	.string "She might listen to somebody with\n"
	.string "nothing to prove and nothing to\l"
	.string "apologise for.\p"
	.string "Go and speak with her. Take as long as\n"
	.string "you need. Nothing here is going\l"
	.string "anywhere -- which is, regrettably, the\l"
	.string "entire problem.$"

SunMoonAltar_Text_DuelApproach:
	.string "{SPEAKER NAME_LUSAMINE}You walked up here instead of going\n"
	.string "round.\p"
	.string "Everybody else on this island has spent\n"
	.string "the last hour finding somewhere else to\l"
	.string "look.$"

@ the YES/NO
SunMoonAltar_Text_DuelAsk:
	.string "{SPEAKER NAME_LUSAMINE}You want to tell me I am wrong. Everyone\n"
	.string "does, today.\p"
	.string "I have been told I am wrong by my\n"
	.string "daughter, my son, a police inspector and\l"
	.string "a professor, and I am still standing\l"
	.string "exactly where I was.\p"
	.string "So don't tell me. Show me. Battle me,\n"
	.string "here, now, and let us find out whether\l"
	.string "the strongest person on this island is\l"
	.string "the one I keep refusing to listen to.$"

@ NO; nothing changes
SunMoonAltar_Text_DuelDeclined:
	.string "{SPEAKER NAME_LUSAMINE}Sensible.\p"
	.string "I will be here. The passage is not in a\n"
	.string "hurry and neither, apparently, am I.$"

SunMoonAltar_Text_DuelAccept:
	.string "{SPEAKER NAME_LUSAMINE}Good.\p"
	.string "Do me the courtesy of trying.$"

@ defeat text of the trainer battle
SunMoonAltar_Text_DuelLusamineBeaten:
	.string "{SPEAKER NAME_LUSAMINE}…Ah.\p"
	.string "There it is.$"

@ player won
SunMoonAltar_Text_DuelWon:
	.string "{SPEAKER NAME_LUSAMINE}You did not win an argument. You won a\n"
	.string "battle. I am perfectly aware of the\l"
	.string "difference and I would thank you not to\l"
	.string "confuse them.\p"
	.string "But I asked to be shown, and I have\n"
	.string "been shown, and I am not a woman who\l"
	.string "asks a question twice.\p"
	.string "…It has been a long time since I lost to\n"
	.string "anyone who did not want something from\l"
	.string "me afterwards.$"

@ player lost
SunMoonAltar_Text_DuelLost:
	.string "{SPEAKER NAME_LUSAMINE}And there we are. I am still right, and I\n"
	.string "am still going, and nothing on this\l"
	.string "island has changed.\p"
	.string "…Why does nobody look pleased? I won.$"

SunMoonAltar_Text_DuelDrew:
	.string "{SPEAKER NAME_LUSAMINE}Both of us on the ground at once. How\n"
	.string "appropriate.\p"
	.string "Neither of us proved a thing. Do note\n"
	.string "that I am counting that as my result as\l"
	.string "well.$"

SunMoonAltar_Text_DuelForfeited:
	.string "{SPEAKER NAME_LUSAMINE}You stopped.\p"
	.string "…Most people do not stop. They keep\n"
	.string "going until there is nothing left to go\l"
	.string "with. I have made an entire career out\l"
	.string "of not stopping.\p"
	.string "Perhaps that was the demonstration\n"
	.string "after all.$"

@ unexpected outcome: NEVER a win, nothing is marked
SunMoonAltar_Text_DuelUnexpected:
	.string "{SPEAKER NAME_LUSAMINE}…Something went wrong with that, and I\n"
	.string "do not propose to pretend otherwise.\p"
	.string "Ask me again when you are ready. I have\n"
	.string "not moved in an hour and I do not intend\l"
	.string "to start now.$"

@ she steps forward; the same in all four branches
SunMoonAltar_Text_DuelLillieEnds:
	.string "{SPEAKER NAME_LILLIE}Mother. Look at me instead of at the\n"
	.string "disc. Just for this.\p"
	.string "You keep saying you are the correct\n"
	.string "person to spend. You are not spending\l"
	.string "anything. You are leaving.\p"
	.string "Spending would be staying here and\n"
	.string "being useful and letting somebody else\l"
	.string "be the brave one. That's the part\l"
	.string "you've never once done.$"

SunMoonAltar_Text_DuelLusamineYields:
	.string "{SPEAKER NAME_LUSAMINE}…\p"
	.string "I had already decided what would be\n"
	.string "best for you. Again.\p"
	.string "Tell me your plan, Lillie. This time, I will\n"
	.string "listen.$"

SunMoonAltar_Text_DuelGladion:
	.string "{SPEAKER NAME_GLADION}The plan is {PLAYER} goes through, we\n"
	.string "hold this side, and everybody comes\l"
	.string "back.\p"
	.string "That's the whole plan. It took us four\n"
	.string "cities to get this far. Don't make it\l"
	.string "complicated now.$"

@ narration
SunMoonAltar_Text_RiftOpens:
	.string "Something on the altar answered.\p"
	.string "A tear opened in the air above the\n"
	.string "stone floor, three paces from where\l"
	.string "Lusamine had been standing, and hung\l"
	.string "there, patient as a mouth.$"

SunMoonAltar_Text_RiftKukui:
	.string "{SPEAKER NAME_KUKUI}Whoa. WHOA. Okay, okay -- needle's\n"
	.string "moving! Needle's moving and I do not\l"
	.string "like where it's going!\p"
	.string "That's not the disc any more, {PLAYER}.\n"
	.string "The disc was the lock. THAT'S the door.\p"
	.string "And it's sitting at ground level, on our\n"
	.string "side, and it opened when your partner\l"
	.string "looked at it. Write that down. Somebody\l"
	.string "write that down.$"

SunMoonAltar_Text_RiftAnabel:
	.string "{SPEAKER NAME_ANABEL}Then we have a way through.\p"
	.string "Before anyone uses it: my rule, once,\n"
	.string "and then I will stop saying it.\p"
	.string "Room in your team for one more. If\n"
	.string "something on the other side needs to\l"
	.string "come back with us, it comes back with\l"
	.string "us. That is not caution. That is the\l"
	.string "entire job.$"

SunMoonAltar_Text_RiftNoRoom:
	.string "{SPEAKER NAME_ANABEL}Stop. Look at me.\p"
	.string "Your team is full and every box you own\n"
	.string "is full. I said room for one more and I\l"
	.string "meant it as a condition, not as advice.\p"
	.string "Go and make space, and come straight\n"
	.string "back. The passage has waited a long\l"
	.string "time. It can wait for a Pokémon Center.$"

SunMoonAltar_Text_RiftNoPartner:
	.string "{SPEAKER NAME_ANABEL}Not like that.\p"
	.string "The tear held still when your partner\n"
	.string "looked at it, and it is holding still now\l"
	.string "because of the light, and I am not\l"
	.string "sending anyone in there on a light that\l"
	.string "is sitting in a box in a Pokémon Center.\p"
	.string "Bring Solgaleo. Or Lunala. Whichever one\n"
	.string "yours chose to become. Then we go.$"

@ the YES/NO
SunMoonAltar_Text_RiftAsk:
	.string "{SPEAKER NAME_LOOKER}One more time, so that it is in the\n"
	.string "record and in your ears.\p"
	.string "Through there, and then back out\n"
	.string "through the same tear, and Madame\l"
	.string "Lusamine, Lillie, Gladion and the\l"
	.string "professor hold this end open while you\l"
	.string "do it.\p"
	.string "The Chief goes with you. I do not -- I\n"
	.string "have no Pokémon for a thing like that,\l"
	.string "and I have never been more honest\l"
	.string "about anything.\p"
	.string "Are you ready, {PLAYER}?$"

SunMoonAltar_Text_RiftNotYet:
	.string "{SPEAKER NAME_LOOKER}Quite right. Prepare properly.\p"
	.string "I shall be here, holding a notebook and\n"
	.string "feeling largely decorative.$"

SunMoonAltar_Text_RiftGo:
	.string "{SPEAKER NAME_ANABEL}With me, then. Close. Don't stop in the\n"
	.string "middle of it, whatever it looks like in\l"
	.string "there.$"

@ state 15 only, a few seconds long
SunMoonAltar_Text_RiftSettling:
	.string "{SPEAKER NAME_KUKUI}Don't touch it! Don't -- okay, don't\n"
	.string "touch it yet. It's still deciding what\l"
	.string "shape it wants to be.$"

@ postgame
SunMoonAltar_Text_RiftDailyAsk:
	.string "{SPEAKER NAME_ANABEL}It opened again this morning. They\n"
	.string "always do, now -- once, and then it\l"
	.string "closes itself by nightfall.\p"
	.string "Looker has a file for each one. I have a\n"
	.string "Ball for each one.\p"
	.string "Going in?$"

SunMoonAltar_Text_RiftDailyNo:
	.string "{SPEAKER NAME_ANABEL}Then it will be here tomorrow. They\n"
	.string "always are.$"

SunMoonAltar_Text_FarewellHurt:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Chief! Is anyone -- are you\n"
	.string "both --\p"
	.string "…Sit down. Both of you. The report can\n"
	.string "wait. The report can wait a very long\l"
	.string "time, and I intend to make it.$"

SunMoonAltar_Text_FarewellShowThem:
	.string "{SPEAKER NAME_LOOKER}Now then. I have five people here who\n"
	.string "have been staring at a hole in the air\l"
	.string "for forty minutes without saying a word\l"
	.string "to each other.\p"
	.string "Would you show them what came out of\n"
	.string "it?$"

SunMoonAltar_Text_FarewellKukui:
	.string "{SPEAKER NAME_KUKUI}…That's it.\p"
	.string "That's the thing that walked out of\n"
	.string "Blackthorn with two Ultra Beasts in its\l"
	.string "hands.\p"
	.string "{PLAYER}, it fits in a Poké Ball. I've\n"
	.string "been building instruments for six weeks\l"
	.string "to measure something that fits in a\l"
	.string "Poké Ball.$"

SunMoonAltar_Text_FarewellLillie:
	.string "{SPEAKER NAME_LILLIE}May I -- thank you.\p"
	.string "…It's warm. I thought it would be cold.\n"
	.string "I don't know why I thought that.\p"
	.string "It was hungry. All of it, the whole way,\n"
	.string "four towns, and every single one of us\l"
	.string "called it an attack because it was big\l"
	.string "and it was bright and we were\l"
	.string "frightened.$"

SunMoonAltar_Text_FarewellGladion:
	.string "{SPEAKER NAME_GLADION}Don't do that.\p"
	.string "It wasn't nobody's fault and it wasn't\n"
	.string "anybody's monster. It was hungry, and\l"
	.string "now it isn't, and {PLAYER} is the one who\l"
	.string "sorted that out while the rest of us\l"
	.string "held a rope.\p"
	.string "…That's the right way round, for once.\n"
	.string "Let it be the right way round.$"

@ she has stepped off the disc's column
SunMoonAltar_Text_FarewellLusamine:
	.string "{SPEAKER NAME_LUSAMINE}I have been standing here looking at\n"
	.string "that door for the better part of a day,\l"
	.string "and I want to tell you all what I was\l"
	.string "actually doing.\p"
	.string "I was waiting for it to be my turn.\n"
	.string "Because if it was my turn, then all of\l"
	.string "this was about me, and if it was about\l"
	.string "me, then it was something I could fix by\l"
	.string "paying for it.\p"
	.string "It was not about me. It has never once\n"
	.string "been about me.$"

SunMoonAltar_Text_FarewellLusamineAsks:
	.string "{SPEAKER NAME_LUSAMINE}Lillie. Gladion.\p"
	.string "I am not going to ask to be forgiven.\n"
	.string "That is a thing people ask for so that\l"
	.string "the conversation can end.\p"
	.string "I am going to ask something much more\n"
	.string "inconvenient. May I come back? Here, to\l"
	.string "this island, regularly, for as long as\l"
	.string "there is work on it?$"

SunMoonAltar_Text_FarewellLillieAnswers:
	.string "{SPEAKER NAME_LILLIE}…Yes.\p"
	.string "Not because everything is all right.\n"
	.string "Because you asked, and you have never\l"
	.string "asked.\p"
	.string "Ask again next time. Every time. That's\n"
	.string "the part I want.$"

@ narration
SunMoonAltar_Text_FarewellCalm:
	.string "The ash stopped.\p"
	.string "High on the wall, the disc turned once\n"
	.string "more and stopped being a hole, and the\l"
	.string "sun came back into the middle of it.$"

@ narration
SunMoonAltar_Text_FarewellStillThere:
	.string "At the foot of the steps, three paces\n"
	.string "from where Lusamine had been standing,\l"
	.string "the tear was still there.\p"
	.string "It was smaller, and it was steady, and it\n"
	.string "was not going anywhere.$"

SunMoonAltar_Text_FarewellAnabelStays:
	.string "{SPEAKER NAME_ANABEL}It won't close. I don't think it's\n"
	.string "supposed to.\p"
	.string "There are eight more that we know about\n"
	.string "and I would guess a great many that we\l"
	.string "don't, and every one of them has\l"
	.string "something on the other side of it.\p"
	.string "I'll stay. I was on the other side of\n"
	.string "one of these, and somebody was\l"
	.string "standing here when I came through, and\l"
	.string "I would like to be that person for\l"
	.string "whoever comes next.$"

SunMoonAltar_Text_FarewellLookerStays:
	.string "{SPEAKER NAME_LOOKER}And where the Chief stays, I stay --\n"
	.string "chiefly because somebody has to file\l"
	.string "all of this, and she writes appallingly.\p"
	.string "…Also because I like it here. Do not put\n"
	.string "that in the report.\p"
	.string "Come back, {PLAYER}. It opens most\n"
	.string "mornings. Bring your partner; bring the\l"
	.string "small one; bring anything you like.$"

SunMoonAltar_Text_FarewellGoodbye:
	.string "{SPEAKER NAME_LOOKER}Rift Missions, the Chief is calling them.\n"
	.string "I think it sounds rather grand.\p"
	.string "Go home and sleep. The sea is flat and\n"
	.string "the sailor is patient and Johto has\l"
	.string "been extremely calm for four entire\l"
	.string "hours.\p"
	.string "…Which, in my professional experience,\n"
	.string "is exactly how long that lasts.$"

SunMoonAltar_Text_LookerCrisis:
	.string "{SPEAKER NAME_LOOKER}I have written the words “situation\n"
	.string "ongoing” four times and crossed them\l"
	.string "out three.\p"
	.string "Go on, {PLAYER}. She is not going to come\n"
	.string "to you.$"

SunMoonAltar_Text_AnabelCrisis:
	.string "{SPEAKER NAME_ANABEL}I can't help you with this part. If I\n"
	.string "could order her to stand down I would\l"
	.string "have done it an hour ago.\p"
	.string "…For what it's worth: she is not wrong\n"
	.string "about being the one who should go. She\l"
	.string "is wrong about going alone. Those are\l"
	.string "different arguments and she keeps\l"
	.string "having the first one.$"

SunMoonAltar_Text_LillieCrisis:
	.string "{SPEAKER NAME_LILLIE}I've said everything I know how to say\n"
	.string "to her.\p"
	.string "Twice. In both of the ways I know how.\p"
	.string "…Would you try? She listens to people\n"
	.string "who haven't been disappointed by her\l"
	.string "yet.$"

SunMoonAltar_Text_GladionCrisis:
	.string "{SPEAKER NAME_GLADION}I'm holding this side of it. That's my\n"
	.string "job today.\p"
	.string "Deal with her. I mean it -- I'd rather\n"
	.string "you did it than me. I'd say something I\l"
	.string "can't take back.$"

SunMoonAltar_Text_KukuiCrisis:
	.string "{SPEAKER NAME_KUKUI}Between you and me? The instrument is\n"
	.string "useless and I'm keeping it in my hands\l"
	.string "so I have something to hold.\p"
	.string "…Go talk to her, {PLAYER}. That's the\n"
	.string "science right now. That's the whole\l"
	.string "experiment.$"

SunMoonAltar_Text_LusamineAnchor:
	.string "{SPEAKER NAME_LUSAMINE}I am holding the light on this side,\n"
	.string "which is, I am informed, “the useful\l"
	.string "thing”.\p"
	.string "I intend to be extremely good at it.$"

SunMoonAltar_Text_LillieAnchor:
	.string "{SPEAKER NAME_LILLIE}We'll be right here. All four of us, the\n"
	.string "whole time.\p"
	.string "…Come back. That's not a request,\n"
	.string "that's the plan, and I helped write it.$"

SunMoonAltar_Text_GladionAnchor:
	.string "{SPEAKER NAME_GLADION}Silvally has your scent. If that tear so\n"
	.string "much as flickers we're coming through\l"
	.string "after you.\p"
	.string "Don't make us. It'd be embarrassing for\n"
	.string "everybody.$"

SunMoonAltar_Text_KukuiAnchor:
	.string "{SPEAKER NAME_KUKUI}Needle's steady! Steady is GOOD,\n"
	.string "{PLAYER}, steady is the best word in my\l"
	.string "whole job!\p"
	.string "Whatever your partner did, it's still\n"
	.string "doing it. Go.$"

@ states 14 and 15
SunMoonAltar_Text_LookerIdle:
	.string "{SPEAKER NAME_LOOKER}I shall be right here. Holding a\n"
	.string "notebook. Being decorative.$"

@ state 15
SunMoonAltar_Text_AnabelIdle:
	.string "{SPEAKER NAME_ANABEL}…Give me a moment, {PLAYER}. I am still\n"
	.string "catching up with the last ten minutes.$"

@ state 15
SunMoonAltar_Text_LusamineIdle:
	.string "{SPEAKER NAME_LUSAMINE}Not now.\p"
	.string "…I am sorry. That was shorter than you\n"
	.string "deserved, and I will do better in a\l"
	.string "minute.$"

SunMoonAltar_Text_LookerHome:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! The Inspector is IN.\p"
	.string "Eight files open, one tear that keeps\n"
	.string "its own hours, and a kettle that the\l"
	.string "Chief refuses to describe as mine.\p"
	.string "This was a very strange place to end up\n"
	.string "and I would not trade it for a\l"
	.string "promotion.$"

@ the YES/NO
SunMoonAltar_Text_LookerHeal:
	.string "{SPEAKER NAME_LOOKER}Before anything else. Your Pokémon. May\n"
	.string "I?\p"
	.string "There is no Center on this island and I\n"
	.string "have made it my business to be the next\l"
	.string "best thing.$"

SunMoonAltar_Text_LookerHealed:
	.string "{SPEAKER NAME_LOOKER}There. Right as rain, as somebody's\n"
	.string "grandmother says.\p"
	.string "Now. Was there anything else, or did you\n"
	.string "come all this way to be fussed over?\l"
	.string "…Either is perfectly acceptable.$"

SunMoonAltar_Text_LookerNoHeal:
	.string "{SPEAKER NAME_LOOKER}As you wish. The offer does not expire.$"

SunMoonAltar_Text_AnabelHome:
	.string "{SPEAKER NAME_ANABEL}It opens most mornings, about an hour\n"
	.string "after the light hits the disc.\p"
	.string "Nine, that we have counted. Nothing has\n"
	.string "come through yet that needed help, and\l"
	.string "I am not going to stop being here on the\l"
	.string "day one does.\p"
	.string "…Looker has started calling it a\n"
	.string "posting. It is not a posting. I asked\l"
	.string "for it.$"

@ the ONLY pointer to the Kurt system in the game
SunMoonAltar_Text_AnabelKurt:
	.string "{SPEAKER NAME_ANABEL}If you need Beast Balls, don't ask me. I\n"
	.string "have two left and I am keeping them.\p"
	.string "Ask Kurt, in Azalea. He is the man who\n"
	.string "invented them, he is the only person\l"
	.string "alive who can make one, and he will make\l"
	.string "you a batch a day if you bring him what\l"
	.string "he needs.\p"
	.string "Tell him I sent you. He will pretend not\n"
	.string "to remember me and then he will ask\l"
	.string "after my Pokémon by name.$"

SunMoonAltar_Text_LusaminePost:
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER}. Good.\p"
	.string "I come out three days a week and I\n"
	.string "stand exactly where I stood that day\l"
	.string "and I look at exactly what I looked at,\l"
	.string "and the Inspector has decided this is\l"
	.string "very healthy of me.\p"
	.string "It is not healthy. It is bookkeeping.\n"
	.string "But I have started bringing lunch, and\l"
	.string "Lillie says that counts as progress.$"

@ the YES/NO. The Nihilego box is required: risk 4
SunMoonAltar_Text_LusamineRematchAsk:
	.string "{SPEAKER NAME_LUSAMINE}While you are here. I have had rather a\n"
	.string "lot of time to think about how that\l"
	.string "battle went.\p"
	.string "I have made some adjustments. One of\n"
	.string "them is the Nihilego, and I would like to\l"
	.string "say out loud where she came from,\l"
	.string "because people will assume.\p"
	.string "She is not a trophy and she is not a\n"
	.string "symptom. She is one of the nine we\l"
	.string "brought back, she is the one the\l"
	.string "Foundation gave me, and I am the one\l"
	.string "who has to be worth it.\p"
	.string "Would you care to see them?$"

SunMoonAltar_Text_LusamineRematchNo:
	.string "{SPEAKER NAME_LUSAMINE}Another day, then. I shall be here, being\n"
	.string "healthy.$"

@ trainer defeat text
SunMoonAltar_Text_LusamineRematchBeaten:
	.string "{SPEAKER NAME_LUSAMINE}…Again. Marvellous.$"

SunMoonAltar_Text_LusamineRematchAfter:
	.string "{SPEAKER NAME_LUSAMINE}Do not let me keep you. I have notes to\n"
	.string "make and, apparently, a great deal of\l"
	.string "humility to practise.$"

SunMoonAltar_Text_LusamineDoneToday:
	.string "{SPEAKER NAME_LUSAMINE}Once a day, {PLAYER}. I am fifty-one and\n"
	.string "I have a foundation to run.$"
SunMoonAltar_Text_Sailor:
	.string "The ship's ready whenever you are.\p"
	.string "Shall we head back to Olivine?$"

SunMoonAltar_Text_SailorDepart:
	.string "Aye! Back to Olivine we go!$"

SunMoonAltar_Text_SailorStay:
	.string "Right. I'll be here on the pier.$"
