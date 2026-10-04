SandpitSW::
	lockall
	delay 20
	playse SE_ESCALATOR
	applymovement OBJ_EVENT_ID_PLAYER, spinNE
	delay 30
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	@ warphole MAP_VAJRA_DESERT_TUNNELS
	goto Sandpit_EventScript_NoDestination


SandpitSE::
	lockall
	delay 20
	playse SE_ESCALATOR
	applymovement OBJ_EVENT_ID_PLAYER, spinNW
	delay 30
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	@ warphole MAP_VAJRA_DESERT_TUNNELS
	goto Sandpit_EventScript_NoDestination


SandpitNE::
	lockall
	delay 20
	playse SE_ESCALATOR
	applymovement OBJ_EVENT_ID_PLAYER, spinSW
	delay 30
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	@ warphole MAP_VAJRA_DESERT_TUNNELS
	goto Sandpit_EventScript_NoDestination


SandpitNW::
	lockall
	delay 20
	playse SE_ESCALATOR
	applymovement OBJ_EVENT_ID_PLAYER, spinSE
	delay 30
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	@ warphole MAP_VAJRA_DESERT_TUNNELS
	goto Sandpit_EventScript_NoDestination


SandpitWest::
	lockall
	delay 20
	playse SE_ESCALATOR
	applymovement OBJ_EVENT_ID_PLAYER, spinEast
	delay 30
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	@ warphole MAP_VAJRA_DESERT_TUNNELS
	goto Sandpit_EventScript_NoDestination


SandpitEast::
	lockall
	delay 20
	playse SE_ESCALATOR
	applymovement OBJ_EVENT_ID_PLAYER, spinWest
	delay 30
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Movement_SetInvisible
	waitmovement 0
	playse SE_FALL
	delay 60
	@ warphole MAP_VAJRA_DESERT_TUNNELS
	goto Sandpit_EventScript_NoDestination


spinWest:
	walk_left
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_faster_left
	walk_in_place_fast_down
	step_end

spinEast:
	walk_right
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_faster_left
	walk_in_place_fast_down
	step_end

spinNW:
	walk_diag_northwest
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_faster_left
	walk_in_place_fast_down
	step_end

spinNE:
	walk_diag_northeast
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_faster_left
	walk_in_place_fast_down
	step_end

spinSE:
	walk_diag_southeast
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_faster_left
	walk_in_place_fast_down
	step_end

spinSW:
	walk_diag_southwest
	walk_in_place_fast_down
	walk_in_place_fast_right
	walk_in_place_fast_up
	walk_in_place_faster_left
	walk_in_place_fast_down
	step_end

@ The destination map (MAP_VAJRA_DESERT_TUNNELS) does not exist yet, so the
@ warphole above stays commented out. It used to be followed by a bare
@ waitstate that nothing ever resumes: stepping on a sandpit tile would leave
@ the player invisible and frozen forever (bug/README, FALLTHROUGH review).
@ No tileset has a sandpit behavior today; this only keeps the trap disarmed.
Sandpit_EventScript_NoDestination::
	applymovement OBJ_EVENT_ID_PLAYER, Sandpit_Movement_SetVisible
	waitmovement 0
	releaseall
	end

Sandpit_Movement_SetVisible:
	set_visible
	step_end
