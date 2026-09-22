# 1 "data/maps/OlivineCity_House1/scripts.pory"

# 2 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 3 "data/maps/OlivineCity_House1/scripts.pory"
@ Rift Missions - Looker and Anabel's house in Olivine.
# 4 "data/maps/OlivineCity_House1/scripts.pory"
@
# 5 "data/maps/OlivineCity_House1/scripts.pory"
@ Both NPCs have "flag": "0": they live here from New Game on, and
# 6 "data/maps/OlivineCity_House1/scripts.pory"
@ VAR_RIFT_MISSIONS_STATE only changes what they say. NEVER removeobject
# 7 "data/maps/OlivineCity_House1/scripts.pory"
@ them - with a clear flag the camera respawns them on the player's next
# 8 "data/maps/OlivineCity_House1/scripts.pory"
@ step. Scene exits are done by walking back to their spots.
# 9 "data/maps/OlivineCity_House1/scripts.pory"
@
# 10 "data/maps/OlivineCity_House1/scripts.pory"
@ The six pre-Necrozma reunion objects ARE flagged (FLAG_TEMP_1) and DO need
# 11 "data/maps/OlivineCity_House1/scripts.pory"
@ visibility recomputed on every load - see ApplyReunionVisibility below.
# 12 "data/maps/OlivineCity_House1/scripts.pory"
@
# 13 "data/maps/OlivineCity_House1/scripts.pory"
@ Floor plan (dump_mapa.py OlivineCity_House1; y grows DOWNWARD).
# 14 "data/maps/OlivineCity_House1/scripts.pory"
@ x=11 and x=12 are wall on every row and are left out.
# 15 "data/maps/OlivineCity_House1/scripts.pory"
@
# 16 "data/maps/OlivineCity_House1/scripts.pory"
@       x= 0 1 2 3 4 5 6 7 8 9 10
# 17 "data/maps/OlivineCity_House1/scripts.pory"
@   y=2    . . . . . . . . . . .     off camera when the player is at (4,8)
# 18 "data/maps/OlivineCity_House1/scripts.pory"
@   y=3    . . . . . . . . . . .     off camera
# 19 "data/maps/OlivineCity_House1/scripts.pory"
@   y=4    . . . . . # # . . . .     table (5-6,4-5) is solid
# 20 "data/maps/OlivineCity_House1/scripts.pory"
@   y=5    . . . . L # # A . . .     L = Looker (4,5)      A = Anabel (7,5)
# 21 "data/maps/OlivineCity_House1/scripts.pory"
@   y=6    . . N I . . . . . U .     N = Ninetales (2,6)   I = Lillie (3,6)   U = Lusamine (9,6)
# 22 "data/maps/OlivineCity_House1/scripts.pory"
@   y=7    . . S G . . . . K . .     S = Silvally (2,7)    G = Gladion (3,7)  K = Kukui (8,7)
# 23 "data/maps/OlivineCity_House1/scripts.pory"
@   y=8    # . . . W . . . . . #     W = door (4,8): the only warp, and where
# 24 "data/maps/OlivineCity_House1/scripts.pory"
@   y=9    # # # # # # # # # # #         the player stands during the scene
# 25 "data/maps/OlivineCity_House1/scripts.pory"
@
# 26 "data/maps/OlivineCity_House1/scripts.pory"
@ Nobody stands south of the player, so the text box covers no actor, and
# 27 "data/maps/OlivineCity_House1/scripts.pory"
@ nobody stands on the Looker/Anabel briefing paths - (4,6), (4,7), (7,6),
# 28 "data/maps/OlivineCity_House1/scripts.pory"
@ (7,7), (6,7), (5,7) are all clear of the six new objects.
# 29 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 30 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_MapScripts::
# 31 "data/maps/OlivineCity_House1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_House1_OnTransition
# 32 "data/maps/OlivineCity_House1/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_House1_OnFrame
# 33 "data/maps/OlivineCity_House1/scripts.pory"
	.byte 0
# 34 "data/maps/OlivineCity_House1/scripts.pory"

# 35 "data/maps/OlivineCity_House1/scripts.pory"
@ NEW with the pre-Necrozma reunion. Looker and Anabel still have "flag": "0"
# 36 "data/maps/OlivineCity_House1/scripts.pory"
@ and are never touched here. The six reunion objects DO need this: their hide
# 37 "data/maps/OlivineCity_House1/scripts.pory"
@ flag is FLAG_TEMP_1, and ClearTempFieldEventData zeroes every temp on every
# 38 "data/maps/OlivineCity_House1/scripts.pory"
@ load - so the DEFAULT IS VISIBLE, and this block is the only thing that keeps
# 39 "data/maps/OlivineCity_House1/scripts.pory"
@ Lusamine and the others out of the room for the whole game before state 10.
# 40 "data/maps/OlivineCity_House1/scripts.pory"
@ It runs before the first spawn, on every load of this map.
# 41 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_OnTransition::
# 42 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyReunionVisibility
# 43 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 44 "data/maps/OlivineCity_House1/scripts.pory"

# 45 "data/maps/OlivineCity_House1/scripts.pory"
@ FLAG_TEMP_1 - the four visitors and the two partners. Shown ONLY in states 10
# 46 "data/maps/OlivineCity_House1/scripts.pory"
@ (reunion pending) and 11 (reunion held, waiting for the evolved partner).
# 47 "data/maps/OlivineCity_House1/scripts.pory"
@ From 12 on they are gone for good: they went ahead to the port.
# 48 "data/maps/OlivineCity_House1/scripts.pory"
@ Runs UNCONDITIONALLY - an "optimised" version that only ran in state 10 would
# 49 "data/maps/OlivineCity_House1/scripts.pory"
@ leave the house full of visitors from New Game on.
# 50 "data/maps/OlivineCity_House1/scripts.pory"
@ goto_if_eq on two values, NEVER goto_if_ge: that is the mistake this file has
# 51 "data/maps/OlivineCity_House1/scripts.pory"
@ already made three times (see the Looker branch block below).
# 52 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyReunionVisibility::
# 53 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowReunionCast
# 54 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowReunionCast
# 55 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_1
# 56 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 57 "data/maps/OlivineCity_House1/scripts.pory"

# 58 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowReunionCast::
# 59 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_1
# 60 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 61 "data/maps/OlivineCity_House1/scripts.pory"

# 62 "data/maps/OlivineCity_House1/scripts.pory"
@ VAR_TEMP_1 is a once-per-visit latch (temps are zeroed by
# 63 "data/maps/OlivineCity_House1/scripts.pory"
@ ClearTempFieldEventData on every map load), so the frame trigger can never
# 64 "data/maps/OlivineCity_House1/scripts.pory"
@ re-fire and livelock the controls.
# 65 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_OnFrame::
# 66 "data/maps/OlivineCity_House1/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, OlivineCity_House1_EventScript_BriefingTrigger
# 67 "data/maps/OlivineCity_House1/scripts.pory"
	.2byte 0
# 68 "data/maps/OlivineCity_House1/scripts.pory"

# 69 "data/maps/OlivineCity_House1/scripts.pory"
@ Only stages a scene in a briefing state (2 = Blackthorn, 4 = Mahogany,
# 70 "data/maps/OlivineCity_House1/scripts.pory"
@ 6 = Cherrygrove, 8 = New Bark) or a reunion state (10 = the pre-Necrozma
# 71 "data/maps/OlivineCity_House1/scripts.pory"
@ meeting, 11 = the partner recheck) AND only if the player just came through
# 72 "data/maps/OlivineCity_House1/scripts.pory"
@ the door at (4,8). Outside that, every one of those still runs - through the
# 73 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker/Anabel object scripts, just without the choreography.
# 74 "data/maps/OlivineCity_House1/scripts.pory"
@ (4,8) is the ONLY warp of this house and there is no Fly or Dig indoors, so
# 75 "data/maps/OlivineCity_House1/scripts.pory"
@ in state 10 the player is necessarily standing there when this fires.
# 76 "data/maps/OlivineCity_House1/scripts.pory"
@ State 12 matches nothing here on purpose: the reunion is over.
# 77 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTrigger::
# 78 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_TEMP_1, 1                        @ first instruction: stops re-firing
# 79 "data/maps/OlivineCity_House1/scripts.pory"
	getplayerxy VAR_0x8004, VAR_0x8005
# 80 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8004, 4, OlivineCity_House1_EventScript_End
# 81 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8005, 8, OlivineCity_House1_EventScript_End
# 82 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
# 83 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefing
# 84 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefing
# 85 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_StageBriefing
# 86 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_StageReunion
# 87 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_StageRecheck
# 88 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 89 "data/maps/OlivineCity_House1/scripts.pory"

# 90 "data/maps/OlivineCity_House1/scripts.pory"
@ The choreography itself, shared by both briefings. Unchanged since Rift
# 91 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1: only which text BriefingTalk picks differs.
# 92 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageBriefing::
# 93 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 94 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 95 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 96 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 97 "data/maps/OlivineCity_House1/scripts.pory"
	@ Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 98 "data/maps/OlivineCity_House1/scripts.pory"
	@ Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 99 "data/maps/OlivineCity_House1/scripts.pory"
	@ The two paths share no tile on any step, so they can walk together.
# 100 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 101 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 102 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 103 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 104 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 105 "data/maps/OlivineCity_House1/scripts.pory"
	@ Back home: the reverse paths, also disjoint step by step.
# 106 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerReturn
# 107 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelReturn
# 108 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 109 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 110 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 111 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 112 "data/maps/OlivineCity_House1/scripts.pory"

# 113 "data/maps/OlivineCity_House1/scripts.pory"
@ The reunion cutscene. Reached from the frame trigger at state 10 and from the
# 114 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker/Anabel object scripts at state 10. It plays ONCE: it always ends in
# 115 "data/maps/OlivineCity_House1/scripts.pory"
@ state 11 or 12, and neither re-enters it. That is the Rift Mission 4 lesson
# 116 "data/maps/OlivineCity_House1/scripts.pory"
@ applied before it costs anything (M4 doc section 9: the long scene replaying
# 117 "data/maps/OlivineCity_House1/scripts.pory"
@ on every attempt is tiring) - here the long version plays once and "did your
# 118 "data/maps/OlivineCity_House1/scripts.pory"
@ partner evolve yet?" is a short branch.
# 119 "data/maps/OlivineCity_House1/scripts.pory"
@
# 120 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker and Anabel reuse the SAME movements as the four briefings:
# 121 "data/maps/OlivineCity_House1/scripts.pory"
@   Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 122 "data/maps/OlivineCity_House1/scripts.pory"
@   Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 123 "data/maps/OlivineCity_House1/scripts.pory"
@ Both paths are free of all six new objects and share no tile on any step.
# 124 "data/maps/OlivineCity_House1/scripts.pory"
@ Nobody walks back at the end: the reunion is still happening when the box
# 125 "data/maps/OlivineCity_House1/scripts.pory"
@ closes, and the next map load returns them to their template tiles.
# 126 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageReunion::
# 127 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 128 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 129 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 130 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 131 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 132 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 133 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 134 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 135 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 136 "data/maps/OlivineCity_House1/scripts.pory"

# 137 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11 arrival: no choreography beyond Looker stepping down to the player,
# 138 "data/maps/OlivineCity_House1/scripts.pory"
@ and no recap of the meeting. He asks the one question that is still open.
# 139 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageRecheck::
# 140 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 141 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 142 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 143 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 144 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 145 "data/maps/OlivineCity_House1/scripts.pory"

# 146 "data/maps/OlivineCity_House1/scripts.pory"
@ Beats, in the order design section 7 fixes them:
# 147 "data/maps/OlivineCity_House1/scripts.pory"
@   1. Looker closes the New Bark report and names the room.
# 148 "data/maps/OlivineCity_House1/scripts.pory"
@   2. Kukui: Anabel's bearing plus Elm's six weeks became a PLACE. He is
# 149 "data/maps/OlivineCity_House1/scripts.pory"
@      already facing west (into the room), so he needs no turnobject.
# 150 "data/maps/OlivineCity_House1/scripts.pory"
@   3. Lusamine says why she asked for this. Lillie (3,6) and Gladion (3,7) are
# 151 "data/maps/OlivineCity_House1/scripts.pory"
@      in the same column, one tile apart, so they can look AT EACH OTHER:
# 152 "data/maps/OlivineCity_House1/scripts.pory"
@      y grows downward, so Lillie faces DIR_SOUTH and Gladion DIR_NORTH. Then
# 153 "data/maps/OlivineCity_House1/scripts.pory"
@      both go back to DIR_EAST, facing the room and their mother.
# 154 "data/maps/OlivineCity_House1/scripts.pory"
@      The family conversation opens here and is NOT resolved here (design 7).
# 155 "data/maps/OlivineCity_House1/scripts.pory"
@   4. Lusamine states she intends to cross. ANABEL sets the condition, as a
# 156 "data/maps/OlivineCity_House1/scripts.pory"
@      Faller - and it is an ARGUMENT, not news: she told them in New Bark
# 157 "data/maps/OlivineCity_House1/scripts.pory"
@      (design 3.1 / 6.4). ONE box of recap, no more. Lusamine is east of her
# 158 "data/maps/OlivineCity_House1/scripts.pory"
@      on both paths in, so she turns DIR_EAST to face her, then back.
# 159 "data/maps/OlivineCity_House1/scripts.pory"
@   5-6. Anabel names what the passage needs; Looker checks -> ReunionCheck.
# 160 "data/maps/OlivineCity_House1/scripts.pory"
@
# 161 "data/maps/OlivineCity_House1/scripts.pory"
@ NO direction here is derived from the player's live position: every
# 162 "data/maps/OlivineCity_House1/scripts.pory"
@ turnobject aims at another actor on a fixed tile. That is what makes the
# 163 "data/maps/OlivineCity_House1/scripts.pory"
@ block correct both from the frame trigger (player at (4,8)) and from an
# 164 "data/maps/OlivineCity_House1/scripts.pory"
@ object script (player anywhere in the room).
# 165 "data/maps/OlivineCity_House1/scripts.pory"
@ closemessage before EVERY turnobject: without it the turn happens behind the
# 166 "data/maps/OlivineCity_House1/scripts.pory"
@ open text box.
# 167 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionScene::
# 168 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionOpen, MSGBOX_DEFAULT
# 169 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 170 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionKukui, MSGBOX_DEFAULT
# 171 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 172 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineCalled, MSGBOX_DEFAULT
# 173 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 174 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_SOUTH
# 175 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_NORTH
# 176 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillie, MSGBOX_DEFAULT
# 177 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 178 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladion, MSGBOX_DEFAULT
# 179 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 180 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_EAST
# 181 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_EAST
# 182 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCross, MSGBOX_DEFAULT
# 183 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 184 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_EAST
# 185 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCondition, MSGBOX_DEFAULT
# 186 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 187 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_SOUTH
# 188 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 189 "data/maps/OlivineCity_House1/scripts.pory"

# 190 "data/maps/OlivineCity_House1/scripts.pory"
@ The one gate of the arc (design sections 7 and 8): Solgaleo OR Lunala, in the
# 191 "data/maps/OlivineCity_House1/scripts.pory"
@ PARTY. checkspecies compiles to Scrcmd_checkspecies (src/scrcmd.c), which
# 192 "data/maps/OlivineCity_House1/scripts.pory"
@ calls CheckPartyHasSpecies (src/field_specials.c): it walks gPlayerParty only
# 193 "data/maps/OlivineCity_House1/scripts.pory"
@ and returns into VAR_RESULT. Consequences, all of them wanted by the design:
# 194 "data/maps/OlivineCity_House1/scripts.pory"
@   - one in the PC does not count; a Pokedex entry does not count;
# 195 "data/maps/OlivineCity_House1/scripts.pory"
@   - Cosmog and Cosmoem do not pass, and no evolution happens here;
# 196 "data/maps/OlivineCity_House1/scripts.pory"
@   - EITHER species satisfies it, and having both is never required.
# 197 "data/maps/OlivineCity_House1/scripts.pory"
@ Two checks, never one, and never a check for the family.
# 198 "data/maps/OlivineCity_House1/scripts.pory"
@ Reachable from the long scene, from the state-11 trigger and from the Looker
# 199 "data/maps/OlivineCity_House1/scripts.pory"
@ and Anabel object scripts, so it must read as a standalone question.
# 200 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionCheck::
# 201 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAsk, MSGBOX_DEFAULT
# 202 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 203 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_SOLGALEO
# 204 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
# 205 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_LUNALA
# 206 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
# 207 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionNotYet
# 208 "data/maps/OlivineCity_House1/scripts.pory"

# 209 "data/maps/OlivineCity_House1/scripts.pory"
@ Not yet. Nothing is spent: no mission is replayed, nobody leaves the room,
# 210 "data/maps/OlivineCity_House1/scripts.pory"
@ and the only thing that changes is 10 -> 11, which is what stops the long
# 211 "data/maps/OlivineCity_House1/scripts.pory"
@ cutscene from playing again. From 11 this whole block is four boxes.
# 212 "data/maps/OlivineCity_House1/scripts.pory"
@ The setvar is idempotent: running it again in state 11 rewrites 11, and
# 213 "data/maps/OlivineCity_House1/scripts.pory"
@ nothing ever goes back from 11 to 10.
# 214 "data/maps/OlivineCity_House1/scripts.pory"
@ releaseall (not release) because this script is reached from a lockall
# 215 "data/maps/OlivineCity_House1/scripts.pory"
@ context AND from a lock context: releaseall is correct in both, release would
# 216 "data/maps/OlivineCity_House1/scripts.pory"
@ leave the other objects frozen after the cutscene.
# 217 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionNotYet::
# 218 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionNotYet, MSGBOX_DEFAULT
# 219 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 220 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 221 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 222 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 223 "data/maps/OlivineCity_House1/scripts.pory"

# 224 "data/maps/OlivineCity_House1/scripts.pory"
@ Confirmed. The room recognises the Pokemon that came out of the egg Gladion
# 225 "data/maps/OlivineCity_House1/scripts.pory"
@ handed the player in Violet, and then Looker gives the hook to the altar.
# 226 "data/maps/OlivineCity_House1/scripts.pory"
@ Design section 7 item 7 (releasing the ship) and everything at the altar
# 227 "data/maps/OlivineCity_House1/scripts.pory"
@ belong to the NEXT document: this event ends on the flag.
# 228 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionConfirmed::
# 229 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionSeeIt, MSGBOX_DEFAULT
# 230 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 231 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladionEgg, MSGBOX_DEFAULT
# 232 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 233 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillieProud, MSGBOX_DEFAULT
# 234 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 235 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineKnows, MSGBOX_DEFAULT
# 236 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 237 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionWayBack, MSGBOX_DEFAULT
# 238 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 239 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionHook, MSGBOX_DEFAULT
# 240 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 241 "data/maps/OlivineCity_House1/scripts.pory"
	@ The ferry pass: the port sailor offers the altar route only to whoever
# 242 "data/maps/OlivineCity_House1/scripts.pory"
	@ carries it (OlivineCity_PortInside). Key item, so the bag cannot be full.
# 243 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicket, MSGBOX_DEFAULT
# 244 "data/maps/OlivineCity_House1/scripts.pory"
	giveitem ITEM_SUN_MOON_TICKET
# 245 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicketUse, MSGBOX_DEFAULT
# 246 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 247 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreen FADE_TO_BLACK
# 248 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED   @ handoff; NEVER cleared
# 249 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 12           @ invariant: flag and var together
# 250 "data/maps/OlivineCity_House1/scripts.pory"
	@ Reload in place: ON_TRANSITION hides the six visitors (they went ahead to
# 251 "data/maps/OlivineCity_House1/scripts.pory"
	@ the port), Looker and Anabel snap back to (4,5)/(7,5) from their
# 252 "data/maps/OlivineCity_House1/scripts.pory"
	@ templates, and the follower comes back (undoes hidefollower). Without
# 253 "data/maps/OlivineCity_House1/scripts.pory"
	@ this, all of that would happen in pieces as the camera moved.
# 254 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7), not (4,8): do not respawn the player on the room's only warp tile.
# 255 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7) is guaranteed free, because by state 12 the six are already hidden.
# 256 "data/maps/OlivineCity_House1/scripts.pory"
	@ The frame trigger fires again after this load with VAR_TEMP_1 zeroed, but
# 257 "data/maps/OlivineCity_House1/scripts.pory"
	@ dies twice over: the player is not at (4,8) AND state 12 matches no
# 258 "data/maps/OlivineCity_House1/scripts.pory"
	@ goto_if_eq in its list.
# 259 "data/maps/OlivineCity_House1/scripts.pory"
	warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7
# 260 "data/maps/OlivineCity_House1/scripts.pory"
	waitstate
# 261 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 262 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 263 "data/maps/OlivineCity_House1/scripts.pory"

# 264 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_End::
# 265 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 266 "data/maps/OlivineCity_House1/scripts.pory"

# 267 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerApproach:
# 268 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 269 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 270 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 271 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 272 "data/maps/OlivineCity_House1/scripts.pory"

# 273 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelApproach:
# 274 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 275 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 276 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 277 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 278 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 279 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 280 "data/maps/OlivineCity_House1/scripts.pory"

# 281 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerReturn:
# 282 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 283 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 284 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 285 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 286 "data/maps/OlivineCity_House1/scripts.pory"

# 287 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelReturn:
# 288 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 289 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 290 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 291 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 292 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 293 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 294 "data/maps/OlivineCity_House1/scripts.pory"

# 295 "data/maps/OlivineCity_House1/scripts.pory"
@ Shared by the arrival scene and by both object scripts in states 2, 4, 6
# 296 "data/maps/OlivineCity_House1/scripts.pory"
@ and 8, so a briefing can never be skipped by entering from an odd tile. It is
# 297 "data/maps/OlivineCity_House1/scripts.pory"
@ the ONE place that moves flag and var, and it moves them together.
# 298 "data/maps/OlivineCity_House1/scripts.pory"
@ Invariants:
# 299 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_BLACKTHORN  set <=> VAR_RIFT_MISSIONS_STATE == 3
# 300 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_MAHOGANY    set <=> VAR_RIFT_MISSIONS_STATE == 5
# 301 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_CHERRYGROVE set <=> VAR_RIFT_MISSIONS_STATE == 7
# 302 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_NEWBARK     set <=> VAR_RIFT_MISSIONS_STATE == 9
# 303 "data/maps/OlivineCity_House1/scripts.pory"
@ The four are mutually exclusive because the var holds one value.
# 304 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10 is the END of the chain: it opens no mission, it means "four done,
# 305 "data/maps/OlivineCity_House1/scripts.pory"
@ the Olivine reunion pending" (design section 7).
# 306 "data/maps/OlivineCity_House1/scripts.pory"
@ A goto inside a script reached by call is safe: call pushes the return
# 307 "data/maps/OlivineCity_House1/scripts.pory"
@ address and return pops it, however many gotos happened in between.
# 308 "data/maps/OlivineCity_House1/scripts.pory"
@ Highest state first, so the block reads newest mission to oldest.
# 309 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalk::
# 310 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_BriefingTalkM4
# 311 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_BriefingTalkM3
# 312 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_BriefingTalkM2
# 313 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through to M1 (state 2)
# 314 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM1::
# 315 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_Briefing, MSGBOX_DEFAULT
# 316 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 317 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
# 318 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 3
# 319 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 320 "data/maps/OlivineCity_House1/scripts.pory"

# 321 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM2::
# 322 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2, MSGBOX_DEFAULT
# 323 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 324 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
# 325 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 5
# 326 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 327 "data/maps/OlivineCity_House1/scripts.pory"

# 328 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM3::
# 329 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3, MSGBOX_DEFAULT
# 330 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 331 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
# 332 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 7
# 333 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 334 "data/maps/OlivineCity_House1/scripts.pory"

# 335 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM4::
# 336 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4, MSGBOX_DEFAULT
# 337 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 338 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_NEWBARK
# 339 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 9
# 340 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 341 "data/maps/OlivineCity_House1/scripts.pory"

# 342 "data/maps/OlivineCity_House1/scripts.pory"
@ Branch order matters: 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, then >= 12. NEVER
# 343 "data/maps/OlivineCity_House1/scripts.pory"
@ leave a "goto_if_ge VAR_RIFT_MISSIONS_STATE, 4", ", 6", ", 8" or ", 10"
# 344 "data/maps/OlivineCity_House1/scripts.pory"
@ here - any one of them would swallow the states above it. This has now
# 345 "data/maps/OlivineCity_House1/scripts.pory"
@ happened THREE times: Mission 3 had to delete a "goto_if_ge ..., 6" left
# 346 "data/maps/OlivineCity_House1/scripts.pory"
@ behind by Mission 2, Mission 4 had to move a "goto_if_ge ..., 8" left behind
# 347 "data/maps/OlivineCity_House1/scripts.pory"
@ by Mission 3, and the pre-Necrozma reunion had to split the
# 348 "data/maps/OlivineCity_House1/scripts.pory"
@ "goto_if_ge ..., 10" Mission 4 left behind, which would have replayed the
# 349 "data/maps/OlivineCity_House1/scripts.pory"
@ whole cutscene at state 11 and kept saying reunion lines at state 12.
# 350 "data/maps/OlivineCity_House1/scripts.pory"
@ Fourth warning, same mistake: a NEW state enters as goto_if_eq, and only the
# 351 "data/maps/OlivineCity_House1/scripts.pory"
@ LAST line of the list may be a goto_if_ge.
# 352 "data/maps/OlivineCity_House1/scripts.pory"
@ States 0-1 fall through to the holiday line.
# 353 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Looker::
# 354 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 355 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 356 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_LookerBrief
# 357 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_LookerGoAhead
# 358 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_LookerBrief
# 359 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_LookerGoAheadM2
# 360 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerBrief
# 361 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_LookerGoAheadM3
# 362 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_LookerBrief
# 363 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_LookerGoAheadM4
# 364 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerReunion
# 365 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_LookerRecheck
# 366 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_LookerAltar
# 367 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerHoliday, MSGBOX_DEFAULT
# 368 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 369 "data/maps/OlivineCity_House1/scripts.pory"

# 370 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerBrief::
# 371 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 372 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 373 "data/maps/OlivineCity_House1/scripts.pory"

# 374 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAhead::
# 375 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAhead, MSGBOX_DEFAULT
# 376 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 377 "data/maps/OlivineCity_House1/scripts.pory"

# 378 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM2::
# 379 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM2, MSGBOX_DEFAULT
# 380 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 381 "data/maps/OlivineCity_House1/scripts.pory"

# 382 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM3::
# 383 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM3, MSGBOX_DEFAULT
# 384 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 385 "data/maps/OlivineCity_House1/scripts.pory"

# 386 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM4::
# 387 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM4, MSGBOX_DEFAULT
# 388 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 389 "data/maps/OlivineCity_House1/scripts.pory"

# 390 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: the alternative way into the reunion, for a player who walks past
# 391 "data/maps/OlivineCity_House1/scripts.pory"
@ the frame trigger's tile check. ReunionScene has no applymovement at all -
# 392 "data/maps/OlivineCity_House1/scripts.pory"
@ only msgbox and turnobject on actors with fixed tiles, and none of the six
# 393 "data/maps/OlivineCity_House1/scripts.pory"
@ visitors wanders (all of them are MOVEMENT_TYPE_FACE_*) - so it plays
# 394 "data/maps/OlivineCity_House1/scripts.pory"
@ identically under lock. All that is missing is Looker's step down.
# 395 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerReunion::
# 396 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 397 "data/maps/OlivineCity_House1/scripts.pory"

# 398 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11: only the open question, never the cutscene again.
# 399 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerRecheck::
# 400 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 401 "data/maps/OlivineCity_House1/scripts.pory"

# 402 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: last stop of this document. The ship, the voyage and the altar
# 403 "data/maps/OlivineCity_House1/scripts.pory"
@ belong to the next one, which starts from FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED
# 404 "data/maps/OlivineCity_House1/scripts.pory"
@ and VAR_RIFT_MISSIONS_STATE >= 12. Repeatable on purpose: a player who saved
# 405 "data/maps/OlivineCity_House1/scripts.pory"
@ and came back must be able to ask where to go.
# 406 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerAltar::
# 407 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerAltar, MSGBOX_DEFAULT
# 408 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 409 "data/maps/OlivineCity_House1/scripts.pory"

# 410 "data/maps/OlivineCity_House1/scripts.pory"
@ Same branch order as Looker, and the same warning about goto_if_ge.
# 411 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Anabel::
# 412 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 413 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 414 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_AnabelBrief
# 415 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_AnabelGoAhead
# 416 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_AnabelBrief
# 417 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_AnabelGoAheadM2
# 418 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_AnabelBrief
# 419 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_AnabelGoAheadM3
# 420 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_AnabelBrief
# 421 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_AnabelGoAheadM4
# 422 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_AnabelReunion
# 423 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_AnabelRecheck
# 424 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_AnabelAltar
# 425 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelHoliday, MSGBOX_DEFAULT
# 426 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 427 "data/maps/OlivineCity_House1/scripts.pory"

# 428 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelBrief::
# 429 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 430 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 431 "data/maps/OlivineCity_House1/scripts.pory"

# 432 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAhead::
# 433 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAhead, MSGBOX_DEFAULT
# 434 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 435 "data/maps/OlivineCity_House1/scripts.pory"

# 436 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM2::
# 437 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM2, MSGBOX_DEFAULT
# 438 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 439 "data/maps/OlivineCity_House1/scripts.pory"

# 440 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM3::
# 441 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM3, MSGBOX_DEFAULT
# 442 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 443 "data/maps/OlivineCity_House1/scripts.pory"

# 444 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM4::
# 445 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM4, MSGBOX_DEFAULT
# 446 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 447 "data/maps/OlivineCity_House1/scripts.pory"

# 448 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: Anabel sells Beast Balls from state 4 on (design section 5),
# 449 "data/maps/OlivineCity_House1/scripts.pory"
@ still pending since Rift Mission 1. This event passes through her script
# 450 "data/maps/OlivineCity_House1/scripts.pory"
@ without resolving it.
# 451 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: same entry into the reunion as Looker's, see the note there.
# 452 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelReunion::
# 453 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 454 "data/maps/OlivineCity_House1/scripts.pory"

# 455 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelRecheck::
# 456 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 457 "data/maps/OlivineCity_House1/scripts.pory"

# 458 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: last stop of this document, same as LookerAltar.
# 459 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelAltar::
# 460 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelAltar, MSGBOX_DEFAULT
# 461 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 462 "data/maps/OlivineCity_House1/scripts.pory"

# 463 "data/maps/OlivineCity_House1/scripts.pory"
@ The four visitors. They exist to be talked to in state 11, the only state in
# 464 "data/maps/OlivineCity_House1/scripts.pory"
@ which the player walks the room with everyone present - in state 12 they are
# 465 "data/maps/OlivineCity_House1/scripts.pory"
@ not here to be talked to, and in state 10 the cutscene runs on arrival. So
# 466 "data/maps/OlivineCity_House1/scripts.pory"
@ they need no branch on the var: one box each.
# 467 "data/maps/OlivineCity_House1/scripts.pory"
@ Ninetales and Silvally have "script": "NULL" (design 3.2, skill
# 468 "data/maps/OlivineCity_House1/scripts.pory"
@ parceiro-pokemon-de-npc): they are their owners' partners out of the ball,
# 469 "data/maps/OlivineCity_House1/scripts.pory"
@ share FLAG_TEMP_1 with them, and come and go together.
# 470 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: placeholder dialogue, one box each.
# 471 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLusamine::
# 472 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 473 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 474 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLusamine, MSGBOX_DEFAULT
# 475 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 476 "data/maps/OlivineCity_House1/scripts.pory"

# 477 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLillie::
# 478 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 479 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 480 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLillie, MSGBOX_DEFAULT
# 481 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 482 "data/maps/OlivineCity_House1/scripts.pory"

# 483 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionGladion::
# 484 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 485 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 486 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleGladion, MSGBOX_DEFAULT
# 487 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 488 "data/maps/OlivineCity_House1/scripts.pory"

# 489 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionKukui::
# 490 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 491 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 492 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleKukui, MSGBOX_DEFAULT
# 493 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 494 "data/maps/OlivineCity_House1/scripts.pory"

# 495 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReleaseEnd::
# 496 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 497 "data/maps/OlivineCity_House1/scripts.pory"
	release
# 498 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 499 "data/maps/OlivineCity_House1/scripts.pory"

# 500 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1 briefing: final text (22/09/2026). It names Clair and "a Pokemon
# 501 "data/maps/OlivineCity_House1/scripts.pory"
@ made of light" and nothing else: Gladion and the two Ultra Beasts are the
# 502 "data/maps/OlivineCity_House1/scripts.pory"
@ surprises of the scene in Blackthorn, so they are never mentioned here.
# 503 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: the placeholder dialogue from BriefingM3 on still needs the pass
# 504 "data/maps/OlivineCity_House1/scripts.pory"
@ in the design's voice (Looker theatrical and warm; Anabel precise), 3.1.
# 505 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_Briefing:
# 506 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Ah, {PLAYER}! You came.\n"
# 507 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Please, come in.\p"
# 508 "data/maps/OlivineCity_House1/scripts.pory"
	.string "First, the truth. Looker,\n"
# 509 "data/maps/OlivineCity_House1/scripts.pory"
	.string "International Police.\p"
# 510 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And this is my Chief, Anabel.\p"
# 511 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Thank you for coming,\n"
# 512 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Champion. We owe you an\l"
# 513 "data/maps/OlivineCity_House1/scripts.pory"
	.string "explanation for the holiday.\p"
# 514 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: We came to Johto\n"
# 515 "data/maps/OlivineCity_House1/scripts.pory"
	.string "following readings.\l"
# 516 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Distortions in space.\p"
# 517 "data/maps/OlivineCity_House1/scripts.pory"
	.string "In Alola, readings like these\n"
# 518 "data/maps/OlivineCity_House1/scripts.pory"
	.string "came before Ultra Wormholes.\p"
# 519 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Openings to other\n"
# 520 "data/maps/OlivineCity_House1/scripts.pory"
	.string "worlds. What comes through,\l"
# 521 "data/maps/OlivineCity_House1/scripts.pory"
	.string "we call Ultra Beasts.\p"
# 522 "data/maps/OlivineCity_House1/scripts.pory"
	.string "They are not villains. Most\n"
# 523 "data/maps/OlivineCity_House1/scripts.pory"
	.string "are lost, and frightened,\l"
# 524 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and very strong.\p"
# 525 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: This morning the Gym\n"
# 526 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Leader of Blackthorn called us.\p"
# 527 "data/maps/OlivineCity_House1/scripts.pory"
	.string "She described a Pokémon\n"
# 528 "data/maps/OlivineCity_House1/scripts.pory"
	.string "standing in the middle of her\l"
# 529 "data/maps/OlivineCity_House1/scripts.pory"
	.string "town. A Pokémon… made of light.\p"
# 530 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Clair has ordered\n"
# 531 "data/maps/OlivineCity_House1/scripts.pory"
	.string "everyone indoors and is\l"
# 532 "data/maps/OlivineCity_House1/scripts.pory"
	.string "holding it off herself.\p"
# 533 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We need to be there.\n"
# 534 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we would like you with us.\p"
# 535 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Meet us by the Pokémon\n"
# 536 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center in Blackthorn.\p"
# 537 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare as you would for the\n"
# 538 "data/maps/OlivineCity_House1/scripts.pory"
	.string "League, {PLAYER}. Perhaps more.$"
# 539 "data/maps/OlivineCity_House1/scripts.pory"

# 540 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Blackthorn hook names no place on purpose ("the moment
# 541 "data/maps/OlivineCity_House1/scripts.pory"
@ something opens, you will be the first to know"). This briefing is that
# 542 "data/maps/OlivineCity_House1/scripts.pory"
@ moment: Mahogany is news to the player here.
# 543 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 2 briefing: final text (22/09/2026). It names Pryce's call and the
# 544 "data/maps/OlivineCity_House1/scripts.pory"
@ blackout and nothing else: Lillie, the evacuation (Pryce's own line) and
# 545 "data/maps/OlivineCity_House1/scripts.pory"
@ the creature from Blackthorn are what the player finds in Mahogany, so
# 546 "data/maps/OlivineCity_House1/scripts.pory"
@ they are never mentioned here.
# 547 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2:
# 548 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: {PLAYER}! Your timing\n"
# 549 "data/maps/OlivineCity_House1/scripts.pory"
	.string "is uncanny. It has started\l"
# 550 "data/maps/OlivineCity_House1/scripts.pory"
	.string "again. Mahogany Town.\p"
# 551 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Two signatures again.\n"
# 552 "data/maps/OlivineCity_House1/scripts.pory"
	.string "One electrical. One… heavy.\p"
# 553 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: The town lost its power\n"
# 554 "data/maps/OlivineCity_House1/scripts.pory"
	.string "three nights ago.\p"
# 555 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Every lamp, every machine.\n"
# 556 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Only the Pokémon Center still\l"
# 557 "data/maps/OlivineCity_House1/scripts.pory"
	.string "has light.\p"
# 558 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: The readings come from\n"
# 559 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the town itself. Every night,\l"
# 560 "data/maps/OlivineCity_House1/scripts.pory"
	.string "at the same hour.\p"
# 561 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No sign of the light from\n"
# 562 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn. Not yet.\p"
# 563 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: The Gym Leader, Pryce,\n"
# 564 "data/maps/OlivineCity_House1/scripts.pory"
	.string "telephoned us himself.\p"
# 565 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He said four words.\n"
# 566 "data/maps/OlivineCity_House1/scripts.pory"
	.string "“Lights out. Come now.”\p"
# 567 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…I have decided to find that\n"
# 568 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reassuring.\p"
# 569 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Meet us by the Pokémon\n"
# 570 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center, {PLAYER}.\p"
# 571 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare for two of them.\n"
# 572 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not one.$"
# 573 "data/maps/OlivineCity_House1/scripts.pory"

# 574 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Mahogany hook names no place on purpose (design section 6,
# 575 "data/maps/OlivineCity_House1/scripts.pory"
@ "gancho sem destino"). This briefing is where Cherrygrove is revealed -
# 576 "data/maps/OlivineCity_House1/scripts.pory"
@ the northwest beach, where Kukui has been camped for four days watching a
# 577 "data/maps/OlivineCity_House1/scripts.pory"
@ tear open over the sea.
# 578 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3:
# 579 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: {PLAYER}! It has opened\n"
# 580 "data/maps/OlivineCity_House1/scripts.pory"
	.string "again. Cherrygrove City.\p"
# 581 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The report is confirmed.\p"
# 582 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Two signatures.\p"
# 583 "data/maps/OlivineCity_House1/scripts.pory"
	.string "One of them will not hold\n"
# 584 "data/maps/OlivineCity_House1/scripts.pory"
	.string "still.\p"
# 585 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Professor Kukui has been\n"
# 586 "data/maps/OlivineCity_House1/scripts.pory"
	.string "on that shore for four days.\p"
# 587 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He will not leave it.\p"
# 588 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: He says the tear over\n"
# 589 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the sea opens and closes on a\l"
# 590 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rhythm.\p"
# 591 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He wants to see it open.\p"
# 592 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: He is a scientist.\p"
# 593 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I would also like him to be a\n"
# 594 "data/maps/OlivineCity_House1/scripts.pory"
	.string "careful man.\p"
# 595 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: The town is clear,\n"
# 596 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 597 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Go and get the Professor off\n"
# 598 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that beach.$"
# 599 "data/maps/OlivineCity_House1/scripts.pory"

# 600 "data/maps/OlivineCity_House1/scripts.pory"
@ The longest briefing of the arc on purpose (design section 6.4): it is the
# 601 "data/maps/OlivineCity_House1/scripts.pory"
@ one that names the town the player grew up in, puts their mother in the
# 602 "data/maps/OlivineCity_House1/scripts.pory"
@ half that refused to evacuate, and has Looker ask - once, in four missions
# 603 "data/maps/OlivineCity_House1/scripts.pory"
@ - whether they actually want to go.
# 604 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4:
# 605 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: {PLAYER}. Sit down.\p"
# 606 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No - actually, don't.\p"
# 607 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There isn't time, and you would\n"
# 608 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not anyway.\p"
# 609 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove holds.\p"
# 610 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And the Professor? Did he eat\n"
# 611 "data/maps/OlivineCity_House1/scripts.pory"
	.string "something, at last?\p"
# 612 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: He went straight to New\n"
# 613 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bark.\p"
# 614 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He says Professor Elm has had\n"
# 615 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the same reading for six weeks\l"
# 616 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and wrote it off as a broken\l"
# 617 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sensor.\p"
# 618 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Then let us look at it.\p"
# 619 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Three, Anabel?\p"
# 620 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Three.\p"
# 621 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Opening together. Closing\n"
# 622 "data/maps/OlivineCity_House1/scripts.pory"
	.string "together.\p"
# 623 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It isn't a rhythm this time,\n"
# 624 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it's-\p"
# 625 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Put it in the report.\p"
# 626 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll write it myself.\p"
# 627 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: {PLAYER}. New Bark Town\n"
# 628 "data/maps/OlivineCity_House1/scripts.pory"
	.string "has no Pokémon Center.\p"
# 629 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No Gym.\p"
# 630 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It has a laboratory and about\n"
# 631 "data/maps/OlivineCity_House1/scripts.pory"
	.string "forty people.\p"
# 632 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We told them to leave.\p"
# 633 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Half of them would not.\p"
# 634 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Your mother is one of the half.\p"
# 635 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Madame Lusamine is\n"
# 636 "data/maps/OlivineCity_House1/scripts.pory"
	.string "already there, standing on the\l"
# 637 "data/maps/OlivineCity_House1/scripts.pory"
	.string "road in.\p"
# 638 "data/maps/OlivineCity_House1/scripts.pory"
	.string "She asked for you by name, and\n"
# 639 "data/maps/OlivineCity_House1/scripts.pory"
	.string "she asked us to stay out of it.\p"
# 640 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Three missions,\n"
# 641 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}, and I have never once\l"
# 642 "data/maps/OlivineCity_House1/scripts.pory"
	.string "asked you this.\p"
# 643 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Do you want to go?\p"
# 644 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Heal everything.\p"
# 645 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Take these.\p"
# 646 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we are going with you -\n"
# 647 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that part is not a question.$"
# 648 "data/maps/OlivineCity_House1/scripts.pory"

# 649 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerHoliday:
# 650 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Hm? Oh, pay no\n"
# 651 "data/maps/OlivineCity_House1/scripts.pory"
	.string "attention to moi.\p"
# 652 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am simply… on holiday.\n"
# 653 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Yes. A holiday by the sea.$"
# 654 "data/maps/OlivineCity_House1/scripts.pory"

# 655 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAhead:
# 656 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Blackthorn, {PLAYER}!\n"
# 657 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Clair cannot hold it forever.\p"
# 658 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are leaving right behind\n"
# 659 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you!$"
# 660 "data/maps/OlivineCity_House1/scripts.pory"

# 661 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM2:
# 662 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Mahogany, {PLAYER}!\n"
# 663 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are right behind you.$"
# 664 "data/maps/OlivineCity_House1/scripts.pory"

# 665 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM3:
# 666 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: The northwest shore,\n"
# 667 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 668 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You cannot miss him. He is the\n"
# 669 "data/maps/OlivineCity_House1/scripts.pory"
	.string "one in the lab coat.$"
# 670 "data/maps/OlivineCity_House1/scripts.pory"

# 671 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM4:
# 672 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: New Bark Town,\n"
# 673 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. Your own front door.\p"
# 674 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am sorry it is this one.$"
# 675 "data/maps/OlivineCity_House1/scripts.pory"

# 676 "data/maps/OlivineCity_House1/scripts.pory"

# 677 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelHoliday:
# 678 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Looker insists we are\n"
# 679 "data/maps/OlivineCity_House1/scripts.pory"
	.string "on vacation.\p"
# 680 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He has been reading the same\n"
# 681 "data/maps/OlivineCity_House1/scripts.pory"
	.string "newspaper for three days.$"
# 682 "data/maps/OlivineCity_House1/scripts.pory"

# 683 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAhead:
# 684 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Go on ahead.\p"
# 685 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll be there before you\n"
# 686 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reach the Pokémon Center.$"
# 687 "data/maps/OlivineCity_House1/scripts.pory"

# 688 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM2:
# 689 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Go on.\p"
# 690 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mr. Pryce does not strike me\n"
# 691 "data/maps/OlivineCity_House1/scripts.pory"
	.string "as a man who calls for help\l"
# 692 "data/maps/OlivineCity_House1/scripts.pory"
	.string "lightly.$"
# 693 "data/maps/OlivineCity_House1/scripts.pory"

# 694 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM3:
# 695 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Go on.\p"
# 696 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And please make the Professor\n"
# 697 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sit down for one minute.$"
# 698 "data/maps/OlivineCity_House1/scripts.pory"

# 699 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM4:
# 700 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: Go.\p"
# 701 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll be a step behind you the\n"
# 702 "data/maps/OlivineCity_House1/scripts.pory"
	.string "whole way.$"
# 703 "data/maps/OlivineCity_House1/scripts.pory"

# 704 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 705 "data/maps/OlivineCity_House1/scripts.pory"
@ Pre-Necrozma reunion texts.
# 706 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: all placeholder, rewrite in the design's voice (section 3.1):
# 707 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker theatrical and warm; Anabel precise; Lusamine formal and blunt;
# 708 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie direct; Gladion economical; Kukui enthusiastic.
# 709 "data/maps/OlivineCity_House1/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 710 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 711 "data/maps/OlivineCity_House1/scripts.pory"

# 712 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionOpen:
# 713 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: {PLAYER}. Come in.\p"
# 714 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mind the chairs - there are\n"
# 715 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not enough of them, and I\l"
# 716 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have stopped apologising.\p"
# 717 "data/maps/OlivineCity_House1/scripts.pory"
	.string "New Bark holds. Four in four.\n"
# 718 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The file is closed.\p"
# 719 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Which is why everyone in this\n"
# 720 "data/maps/OlivineCity_House1/scripts.pory"
	.string "room came when I asked.\p"
# 721 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Look at them. I did not have\n"
# 722 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to explain twice.$"
# 723 "data/maps/OlivineCity_House1/scripts.pory"

# 724 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionKukui:
# 725 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Kukui: Your rifts closed\n"
# 726 "data/maps/OlivineCity_House1/scripts.pory"
	.string "toward one bearing.\p"
# 727 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel's number, Elm's six\n"
# 728 "data/maps/OlivineCity_House1/scripts.pory"
	.string "weeks of it, my rhythm.\p"
# 729 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Three wrong tools, one\n"
# 730 "data/maps/OlivineCity_House1/scripts.pory"
	.string "answer.\p"
# 731 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There's a place out there,\n"
# 732 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. An altar.\p"
# 733 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We can put a boat on it.$"
# 734 "data/maps/OlivineCity_House1/scripts.pory"

# 735 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineCalled:
# 736 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lusamine: I asked the\n"
# 737 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Inspector to call this\l"
# 738 "data/maps/OlivineCity_House1/scripts.pory"
	.string "meeting.\p"
# 739 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not as Aether. Aether would\n"
# 740 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have sent a report.\p"
# 741 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I owe the people in this room\n"
# 742 "data/maps/OlivineCity_House1/scripts.pory"
	.string "an accounting, and two of\l"
# 743 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them are mine.$"
# 744 "data/maps/OlivineCity_House1/scripts.pory"

# 745 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie (3,6) and Gladion (3,7) have just turned to face each other.
# 746 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillie:
# 747 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lillie: …You asked for us.\n"
# 748 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Both of us.\p"
# 749 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'm not going to pretend\n"
# 750 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that's nothing.\p"
# 751 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It isn't nothing.$"
# 752 "data/maps/OlivineCity_House1/scripts.pory"

# 753 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladion:
# 754 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Gladion: We'll do the\n"
# 755 "data/maps/OlivineCity_House1/scripts.pory"
	.string "accounting after.\p"
# 756 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Whatever is at that altar, it\n"
# 757 "data/maps/OlivineCity_House1/scripts.pory"
	.string "doesn't wait for our family\l"
# 758 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to sort itself out.$"
# 759 "data/maps/OlivineCity_House1/scripts.pory"

# 760 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCross:
# 761 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lusamine: Then let me say the\n"
# 762 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rest of it plainly.\p"
# 763 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I intend to cross.\p"
# 764 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I have been on the other side\n"
# 765 "data/maps/OlivineCity_House1/scripts.pory"
	.string "of a door like that one.\p"
# 766 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nobody else in this room has.$"
# 767 "data/maps/OlivineCity_House1/scripts.pory"

# 768 "data/maps/OlivineCity_House1/scripts.pory"
@ ONE box of recap and no more (design 3.1): Anabel told them all of this in
# 769 "data/maps/OlivineCity_House1/scripts.pory"
@ New Bark. Here it is an argument, not news.
# 770 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCondition:
# 771 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: You have. I have as\n"
# 772 "data/maps/OlivineCity_House1/scripts.pory"
	.string "well, and I came back wrong,\l"
# 773 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I told you all so in New\l"
# 774 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bark.\p"
# 775 "data/maps/OlivineCity_House1/scripts.pory"
	.string "So here is my condition,\n"
# 776 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Madame, and it is not\l"
# 777 "data/maps/OlivineCity_House1/scripts.pory"
	.string "negotiable:\p"
# 778 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nobody crosses without a way\n"
# 779 "data/maps/OlivineCity_House1/scripts.pory"
	.string "back.\p"
# 780 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not you. Not me.\n"
# 781 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not the Champion.$"
# 782 "data/maps/OlivineCity_House1/scripts.pory"

# 783 "data/maps/OlivineCity_House1/scripts.pory"
@ Must read standalone: this is also the whole of the state-11 question.
# 784 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAsk:
# 785 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: And a way through\n"
# 786 "data/maps/OlivineCity_House1/scripts.pory"
	.string "needs something that can open\l"
# 787 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it.\p"
# 788 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not a machine. We tried\n"
# 789 "data/maps/OlivineCity_House1/scripts.pory"
	.string "machines for six weeks.\p"
# 790 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: {PLAYER}. Your\n"
# 791 "data/maps/OlivineCity_House1/scripts.pory"
	.string "partner.\p"
# 792 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The one that started as an\n"
# 793 "data/maps/OlivineCity_House1/scripts.pory"
	.string "egg.\p"
# 794 "data/maps/OlivineCity_House1/scripts.pory"
	.string "May we see them?$"
# 795 "data/maps/OlivineCity_House1/scripts.pory"

# 796 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionNotYet:
# 797 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: …Ah. Not yet.\p"
# 798 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Kukui: That's not a no!\n"
# 799 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's a “give it time”.\p"
# 800 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It's still growing into what\n"
# 801 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it's going to be.\p"
# 802 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Then we prepare, and\n"
# 803 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you raise them.\p"
# 804 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Come back when they have\n"
# 805 "data/maps/OlivineCity_House1/scripts.pory"
	.string "finished becoming Solgaleo\l"
# 806 "data/maps/OlivineCity_House1/scripts.pory"
	.string "or Lunala.\p"
# 807 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are not going anywhere.\p"
# 808 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Frankly, there is nowhere for\n"
# 809 "data/maps/OlivineCity_House1/scripts.pory"
	.string "six people to go in this\l"
# 810 "data/maps/OlivineCity_House1/scripts.pory"
	.string "room.$"
# 811 "data/maps/OlivineCity_House1/scripts.pory"

# 812 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionSeeIt:
# 813 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: …Oh.\p"
# 814 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: That is it.\p"
# 815 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That is the reading, standing\n"
# 816 "data/maps/OlivineCity_House1/scripts.pory"
	.string "in a living room in Olivine.$"
# 817 "data/maps/OlivineCity_House1/scripts.pory"

# 818 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladionEgg:
# 819 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Gladion: I handed you that\n"
# 820 "data/maps/OlivineCity_House1/scripts.pory"
	.string "egg in Violet and told you to\l"
# 821 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keep it away from people\l"
# 822 "data/maps/OlivineCity_House1/scripts.pory"
	.string "like us.\p"
# 823 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You did better than that.\n"
# 824 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You raised it.$"
# 825 "data/maps/OlivineCity_House1/scripts.pory"

# 826 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillieProud:
# 827 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lillie: I knew the whole way.\p"
# 828 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Every time we met, I knew.\p"
# 829 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I just wanted to be here when\n"
# 830 "data/maps/OlivineCity_House1/scripts.pory"
	.string "somebody finally said it out\l"
# 831 "data/maps/OlivineCity_House1/scripts.pory"
	.string "loud.$"
# 832 "data/maps/OlivineCity_House1/scripts.pory"

# 833 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineKnows:
# 834 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lusamine: That light is what\n"
# 835 "data/maps/OlivineCity_House1/scripts.pory"
	.string "opens the way.\p"
# 836 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am the only person alive\n"
# 837 "data/maps/OlivineCity_House1/scripts.pory"
	.string "who knows what it looks like\l"
# 838 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from the other side.\p"
# 839 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Thank you for not letting me\n"
# 840 "data/maps/OlivineCity_House1/scripts.pory"
	.string "do this alone.\p"
# 841 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am told that is the lesson.$"
# 842 "data/maps/OlivineCity_House1/scripts.pory"

# 843 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionWayBack:
# 844 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: My condition stands.\p"
# 845 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We go together, and we come\n"
# 846 "data/maps/OlivineCity_House1/scripts.pory"
	.string "back.$"
# 847 "data/maps/OlivineCity_House1/scripts.pory"

# 848 "data/maps/OlivineCity_House1/scripts.pory"
@ The handoff to the altar document. The last box is the one that tells the
# 849 "data/maps/OlivineCity_House1/scripts.pory"
@ player the game is not taking them anywhere yet.
# 850 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionHook:
# 851 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: Then it is settled.\p"
# 852 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There is a ship at the\n"
# 853 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Olivine port, and it is ours\l"
# 854 "data/maps/OlivineCity_House1/scripts.pory"
	.string "for as long as this takes.\p"
# 855 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We sail for the altar,\n"
# 856 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 857 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You, your partner, and\n"
# 858 "data/maps/OlivineCity_House1/scripts.pory"
	.string "everyone in this room who can\l"
# 859 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keep up.\p"
# 860 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Come to the port when you are\n"
# 861 "data/maps/OlivineCity_House1/scripts.pory"
	.string "ready. Rest first.\p"
# 862 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Whatever is waiting at that\n"
# 863 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar has waited a long time.\p"
# 864 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It can wait for you to heal.$"
# 865 "data/maps/OlivineCity_House1/scripts.pory"

# 866 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicket:
# 867 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: One more thing.\n"
# 868 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Take this.$"
# 869 "data/maps/OlivineCity_House1/scripts.pory"

# 870 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicketUse:
# 871 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Show it to the sailor at the\n"
# 872 "data/maps/OlivineCity_House1/scripts.pory"
	.string "port. He will take you to the\l"
# 873 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar, and bring you back.$"
# 874 "data/maps/OlivineCity_House1/scripts.pory"

# 875 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: state 12 and up, the repeatable reminder of where to go.
# 876 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerAltar:
# 877 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker: The ship is at the\n"
# 878 "data/maps/OlivineCity_House1/scripts.pory"
	.string "port whenever you are ready,\l"
# 879 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 880 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Madame Lusamine went ahead.\n"
# 881 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Of course she did.$"
# 882 "data/maps/OlivineCity_House1/scripts.pory"

# 883 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelAltar:
# 884 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel: We leave when you do,\n"
# 885 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not before.\p"
# 886 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we come back.\p"
# 887 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That part is the whole plan.$"
# 888 "data/maps/OlivineCity_House1/scripts.pory"

# 889 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: idle lines for state 11, one box each.
# 890 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLusamine:
# 891 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lusamine: I will not pace.\p"
# 892 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pacing is for people without\n"
# 893 "data/maps/OlivineCity_House1/scripts.pory"
	.string "instruments.$"
# 894 "data/maps/OlivineCity_House1/scripts.pory"

# 895 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLillie:
# 896 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lillie: Take your time with\n"
# 897 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them.\p"
# 898 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I mean it - that's not a\n"
# 899 "data/maps/OlivineCity_House1/scripts.pory"
	.string "polite thing to say, it's the\l"
# 900 "data/maps/OlivineCity_House1/scripts.pory"
	.string "actual advice.$"
# 901 "data/maps/OlivineCity_House1/scripts.pory"

# 902 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleGladion:
# 903 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Gladion: Go and train.\p"
# 904 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's not an insult, it's\n"
# 905 "data/maps/OlivineCity_House1/scripts.pory"
	.string "what I'd be doing.$"
# 906 "data/maps/OlivineCity_House1/scripts.pory"

# 907 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleKukui:
# 908 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Kukui: Six weeks of bad data\n"
# 909 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and one good afternoon!\p"
# 910 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Science, {PLAYER}!$"
