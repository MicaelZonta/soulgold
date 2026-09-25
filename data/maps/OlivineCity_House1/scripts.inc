# 1 "data/maps/OlivineCity_House1/scripts.pory"

# 2 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 3 "data/maps/OlivineCity_House1/scripts.pory"
@ Rift Missions - Looker and Anabel's house in Olivine.
# 4 "data/maps/OlivineCity_House1/scripts.pory"
@
# 5 "data/maps/OlivineCity_House1/scripts.pory"
@ CHANGED by the Sun and Moon Altar event
# 6 "data/maps/OlivineCity_House1/scripts.pory"
@ (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.6): Looker and Anabel no
# 7 "data/maps/OlivineCity_House1/scripts.pory"
@ longer have "flag": "0". They are on FLAG_TEMP_2, because from state 16 on they
# 8 "data/maps/OlivineCity_House1/scripts.pory"
@ live at the altar and this room is empty of them for good.
# 9 "data/maps/OlivineCity_House1/scripts.pory"
@ NEVER removeobject them even so - removeobject SETS the object's flag and the
# 10 "data/maps/OlivineCity_House1/scripts.pory"
@ camera respawns anything whose flag is clear on the player's next step. Scene
# 11 "data/maps/OlivineCity_House1/scripts.pory"
@ exits are still done by walking back to their spots; what takes them out of the
# 12 "data/maps/OlivineCity_House1/scripts.pory"
@ room permanently is ApplyInvestigatorVisibility below.
# 13 "data/maps/OlivineCity_House1/scripts.pory"
@
# 14 "data/maps/OlivineCity_House1/scripts.pory"
@ With a temporary flag THE DEFAULT IS VISIBLE, because ClearTempFieldEventData
# 15 "data/maps/OlivineCity_House1/scripts.pory"
@ zeroes every FLAG_TEMP_* on every load. If somebody ever deletes
# 16 "data/maps/OlivineCity_House1/scripts.pory"
@ ApplyInvestigatorVisibility "because it looked redundant", Looker and Anabel are
# 17 "data/maps/OlivineCity_House1/scripts.pory"
@ back in Olivine AND still at the altar, at the same time, for ever, and nothing
# 18 "data/maps/OlivineCity_House1/scripts.pory"
@ in the build says so.
# 19 "data/maps/OlivineCity_House1/scripts.pory"
@
# 20 "data/maps/OlivineCity_House1/scripts.pory"
@ Three independent visibility decisions now, not one:
# 21 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_1  the family: the reunion visitors in 10..11, and the five of them
# 22 "data/maps/OlivineCity_House1/scripts.pory"
@                again from 16 on, by the weekday rota
# 23 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_2  Looker and Anabel: present below 16, gone from 16 on
# 24 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_3  Kukui: 10..11 only. He never comes back to this room - from 16
# 25 "data/maps/OlivineCity_House1/scripts.pory"
@                on he is in Alola, and on some days on a Cherrygrove beach
# 26 "data/maps/OlivineCity_House1/scripts.pory"
@
# 27 "data/maps/OlivineCity_House1/scripts.pory"
@ Floor plan (dump_mapa.py OlivineCity_House1; y grows DOWNWARD).
# 28 "data/maps/OlivineCity_House1/scripts.pory"
@ x=11 and x=12 are wall on every row and are left out.
# 29 "data/maps/OlivineCity_House1/scripts.pory"
@
# 30 "data/maps/OlivineCity_House1/scripts.pory"
@       x= 0 1 2 3 4 5 6 7 8 9 10
# 31 "data/maps/OlivineCity_House1/scripts.pory"
@   y=2    . . . . . . . . . . .     off camera when the player is at (4,8)
# 32 "data/maps/OlivineCity_House1/scripts.pory"
@   y=3    . . . . . . . . . . .     off camera
# 33 "data/maps/OlivineCity_House1/scripts.pory"
@   y=4    . . . . . # # . . . .     table (5-6,4-5) is solid
# 34 "data/maps/OlivineCity_House1/scripts.pory"
@   y=5    . . . . L # # A . . .     L = Looker (4,5)      A = Anabel (7,5)
# 35 "data/maps/OlivineCity_House1/scripts.pory"
@   y=6    . . N I . . . . . U .     N = Ninetales (2,6)   I = Lillie (3,6)   U = Lusamine (9,6)
# 36 "data/maps/OlivineCity_House1/scripts.pory"
@   y=7    . . S G . . . . K . .     S = Silvally (2,7)    G = Gladion (3,7)  K = Kukui (8,7)
# 37 "data/maps/OlivineCity_House1/scripts.pory"
@   y=8    # . . . W . . . . . #     W = door (4,8): the only warp, and where
# 38 "data/maps/OlivineCity_House1/scripts.pory"
@   y=9    # # # # # # # # # # #         the player stands during the scene
# 39 "data/maps/OlivineCity_House1/scripts.pory"
@
# 40 "data/maps/OlivineCity_House1/scripts.pory"
@ Nobody stands south of the player, so the text box covers no actor, and
# 41 "data/maps/OlivineCity_House1/scripts.pory"
@ nobody stands on the Looker/Anabel briefing paths - (4,6), (4,7), (7,6),
# 42 "data/maps/OlivineCity_House1/scripts.pory"
@ (7,7), (6,7), (5,7) are all clear of the six new objects.
# 43 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 44 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_MapScripts::
# 45 "data/maps/OlivineCity_House1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_House1_OnTransition
# 46 "data/maps/OlivineCity_House1/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_House1_OnFrame
# 47 "data/maps/OlivineCity_House1/scripts.pory"
	.byte 0
# 48 "data/maps/OlivineCity_House1/scripts.pory"

# 49 "data/maps/OlivineCity_House1/scripts.pory"
@ NEW with the pre-Necrozma reunion. Looker and Anabel still have "flag": "0"
# 50 "data/maps/OlivineCity_House1/scripts.pory"
@ and are never touched here. The six reunion objects DO need this: their hide
# 51 "data/maps/OlivineCity_House1/scripts.pory"
@ flag is FLAG_TEMP_1, and ClearTempFieldEventData zeroes every temp on every
# 52 "data/maps/OlivineCity_House1/scripts.pory"
@ load - so the DEFAULT IS VISIBLE, and this block is the only thing that keeps
# 53 "data/maps/OlivineCity_House1/scripts.pory"
@ Lusamine and the others out of the room for the whole game before state 10.
# 54 "data/maps/OlivineCity_House1/scripts.pory"
@ It runs before the first spawn, on every load of this map.
# 55 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_OnTransition::
# 56 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyReunionVisibility
# 57 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyInvestigatorVisibility
# 58 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyKukuiVisibility
# 59 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 60 "data/maps/OlivineCity_House1/scripts.pory"

# 61 "data/maps/OlivineCity_House1/scripts.pory"
@ FLAG_TEMP_1 - the four visitors and the two partners. Shown ONLY in states 10
# 62 "data/maps/OlivineCity_House1/scripts.pory"
@ (reunion pending) and 11 (reunion held, waiting for the evolved partner).
# 63 "data/maps/OlivineCity_House1/scripts.pory"
@ From 12 on they are gone for good: they went ahead to the port.
# 64 "data/maps/OlivineCity_House1/scripts.pory"
@ Runs UNCONDITIONALLY - an "optimised" version that only ran in state 10 would
# 65 "data/maps/OlivineCity_House1/scripts.pory"
@ leave the house full of visitors from New Game on.
# 66 "data/maps/OlivineCity_House1/scripts.pory"
@ goto_if_eq on two values, NEVER goto_if_ge: that is the mistake this file has
# 67 "data/maps/OlivineCity_House1/scripts.pory"
@ already made three times (see the Looker branch block below).
# 68 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyReunionVisibility::
# 69 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowReunionCast
# 70 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowReunionCast
# 71 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HideReunionCast
# 72 "data/maps/OlivineCity_House1/scripts.pory"
	@ Post-game: Sunday and Friday are the family's days. The whole arc was about
# 73 "data/maps/OlivineCity_House1/scripts.pory"
	@ a family that could not be in the same place; two days a week where the only
# 74 "data/maps/OlivineCity_House1/scripts.pory"
	@ thing they do is be together is the reward, and it needs no line of dialogue
# 75 "data/maps/OlivineCity_House1/scripts.pory"
	@ explaining itself. Kukui is NOT part of this - he is on FLAG_TEMP_3.
# 76 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, GetDayOfWeek
# 77 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_SUN, OlivineCity_House1_EventScript_ShowReunionCast
# 78 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_FRI, OlivineCity_House1_EventScript_ShowReunionCast
# 79 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HideReunionCast::
# 80 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_1
# 81 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 82 "data/maps/OlivineCity_House1/scripts.pory"

# 83 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowReunionCast::
# 84 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_1
# 85 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 86 "data/maps/OlivineCity_House1/scripts.pory"

# 87 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker and Anabel: the whole game up to the farewell, and then never again.
# 88 "data/maps/OlivineCity_House1/scripts.pory"
@ Runs unconditionally on every load, and it is the ONLY thing that ever removes
# 89 "data/maps/OlivineCity_House1/scripts.pory"
@ them (see the header block for what happens if it is deleted).
# 90 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyInvestigatorVisibility::
# 91 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HideInvestigators
# 92 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_2
# 93 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 94 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HideInvestigators::
# 95 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_2
# 96 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 97 "data/maps/OlivineCity_House1/scripts.pory"

# 98 "data/maps/OlivineCity_House1/scripts.pory"
@ Kukui: states 10 and 11 only, and a closed window on purpose - goto_if_ge here
# 99 "data/maps/OlivineCity_House1/scripts.pory"
@ would put him in this room for the rest of the game.
# 100 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyKukuiVisibility::
# 101 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowKukui
# 102 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowKukui
# 103 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_3
# 104 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 105 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowKukui::
# 106 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_3
# 107 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 108 "data/maps/OlivineCity_House1/scripts.pory"

# 109 "data/maps/OlivineCity_House1/scripts.pory"
@ VAR_TEMP_1 is a once-per-visit latch (temps are zeroed by
# 110 "data/maps/OlivineCity_House1/scripts.pory"
@ ClearTempFieldEventData on every map load), so the frame trigger can never
# 111 "data/maps/OlivineCity_House1/scripts.pory"
@ re-fire and livelock the controls.
# 112 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_OnFrame::
# 113 "data/maps/OlivineCity_House1/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, OlivineCity_House1_EventScript_BriefingTrigger
# 114 "data/maps/OlivineCity_House1/scripts.pory"
	.2byte 0
# 115 "data/maps/OlivineCity_House1/scripts.pory"

# 116 "data/maps/OlivineCity_House1/scripts.pory"
@ Only stages a scene in a briefing state (2 = Blackthorn, 4 = Mahogany,
# 117 "data/maps/OlivineCity_House1/scripts.pory"
@ 6 = Cherrygrove, 8 = New Bark) or a reunion state (10 = the pre-Necrozma
# 118 "data/maps/OlivineCity_House1/scripts.pory"
@ meeting, 11 = the partner recheck) AND only if the player just came through
# 119 "data/maps/OlivineCity_House1/scripts.pory"
@ the door at (4,8). Outside that, every one of those still runs - through the
# 120 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker/Anabel object scripts, just without the choreography.
# 121 "data/maps/OlivineCity_House1/scripts.pory"
@ (4,8) is the ONLY warp of this house and there is no Fly or Dig indoors, so
# 122 "data/maps/OlivineCity_House1/scripts.pory"
@ in state 10 the player is necessarily standing there when this fires.
# 123 "data/maps/OlivineCity_House1/scripts.pory"
@ State 12 matches nothing here on purpose: the reunion is over.
# 124 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTrigger::
# 125 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_TEMP_1, 1                        @ first instruction: stops re-firing
# 126 "data/maps/OlivineCity_House1/scripts.pory"
	getplayerxy VAR_0x8004, VAR_0x8005
# 127 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8004, 4, OlivineCity_House1_EventScript_End
# 128 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8005, 8, OlivineCity_House1_EventScript_End
# 129 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
# 130 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefing
# 131 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefing
# 132 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_StageBriefing
# 133 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_StageReunion
# 134 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_StageRecheck
# 135 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 136 "data/maps/OlivineCity_House1/scripts.pory"

# 137 "data/maps/OlivineCity_House1/scripts.pory"
@ The choreography itself, shared by both briefings. Unchanged since Rift
# 138 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1: only which text BriefingTalk picks differs.
# 139 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageBriefing::
# 140 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 141 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 142 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 143 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 144 "data/maps/OlivineCity_House1/scripts.pory"
	@ Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 145 "data/maps/OlivineCity_House1/scripts.pory"
	@ Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 146 "data/maps/OlivineCity_House1/scripts.pory"
	@ The two paths share no tile on any step, so they can walk together.
# 147 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 148 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 149 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 150 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 151 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 152 "data/maps/OlivineCity_House1/scripts.pory"
	@ Back home: the reverse paths, also disjoint step by step.
# 153 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerReturn
# 154 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelReturn
# 155 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 156 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 157 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 158 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 159 "data/maps/OlivineCity_House1/scripts.pory"

# 160 "data/maps/OlivineCity_House1/scripts.pory"
@ The reunion cutscene. Reached from the frame trigger at state 10 and from the
# 161 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker/Anabel object scripts at state 10. It plays ONCE: it always ends in
# 162 "data/maps/OlivineCity_House1/scripts.pory"
@ state 11 or 12, and neither re-enters it. That is the Rift Mission 4 lesson
# 163 "data/maps/OlivineCity_House1/scripts.pory"
@ applied before it costs anything (M4 doc section 9: the long scene replaying
# 164 "data/maps/OlivineCity_House1/scripts.pory"
@ on every attempt is tiring) - here the long version plays once and "did your
# 165 "data/maps/OlivineCity_House1/scripts.pory"
@ partner evolve yet?" is a short branch.
# 166 "data/maps/OlivineCity_House1/scripts.pory"
@
# 167 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker and Anabel reuse the SAME movements as the four briefings:
# 168 "data/maps/OlivineCity_House1/scripts.pory"
@   Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 169 "data/maps/OlivineCity_House1/scripts.pory"
@   Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 170 "data/maps/OlivineCity_House1/scripts.pory"
@ Both paths are free of all six new objects and share no tile on any step.
# 171 "data/maps/OlivineCity_House1/scripts.pory"
@ Nobody walks back at the end: the reunion is still happening when the box
# 172 "data/maps/OlivineCity_House1/scripts.pory"
@ closes, and the next map load returns them to their template tiles.
# 173 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageReunion::
# 174 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 175 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 176 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 177 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 178 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 179 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 180 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 181 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 182 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 183 "data/maps/OlivineCity_House1/scripts.pory"

# 184 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11 arrival: no choreography beyond Looker stepping down to the player,
# 185 "data/maps/OlivineCity_House1/scripts.pory"
@ and no recap of the meeting. He asks the one question that is still open.
# 186 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageRecheck::
# 187 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 188 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 189 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 190 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 191 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 192 "data/maps/OlivineCity_House1/scripts.pory"

# 193 "data/maps/OlivineCity_House1/scripts.pory"
@ Beats, in the order design section 7 fixes them:
# 194 "data/maps/OlivineCity_House1/scripts.pory"
@   1. Looker closes the New Bark report and names the room.
# 195 "data/maps/OlivineCity_House1/scripts.pory"
@   2. Kukui: Anabel's bearing plus Elm's six weeks became a PLACE. He is
# 196 "data/maps/OlivineCity_House1/scripts.pory"
@      already facing west (into the room), so he needs no turnobject.
# 197 "data/maps/OlivineCity_House1/scripts.pory"
@   3. Lusamine says why she asked for this. Lillie (3,6) and Gladion (3,7) are
# 198 "data/maps/OlivineCity_House1/scripts.pory"
@      in the same column, one tile apart, so they can look AT EACH OTHER:
# 199 "data/maps/OlivineCity_House1/scripts.pory"
@      y grows downward, so Lillie faces DIR_SOUTH and Gladion DIR_NORTH. Then
# 200 "data/maps/OlivineCity_House1/scripts.pory"
@      both go back to DIR_EAST, facing the room and their mother.
# 201 "data/maps/OlivineCity_House1/scripts.pory"
@      The family conversation opens here and is NOT resolved here (design 7).
# 202 "data/maps/OlivineCity_House1/scripts.pory"
@   4. Lusamine states she intends to cross. ANABEL sets the condition, as a
# 203 "data/maps/OlivineCity_House1/scripts.pory"
@      Faller - and it is an ARGUMENT, not news: she told them on the beach
# 204 "data/maps/OlivineCity_House1/scripts.pory"
@      in Cherrygrove and the rest of it in New Bark (design 3.1 / 6.3 /
# 205 "data/maps/OlivineCity_House1/scripts.pory"
@      6.4). ONE box of recap, no more. Lusamine is east of her
# 206 "data/maps/OlivineCity_House1/scripts.pory"
@      on both paths in, so she turns DIR_EAST to face her, then back.
# 207 "data/maps/OlivineCity_House1/scripts.pory"
@   5-6. Anabel names what the passage needs; Looker checks -> ReunionCheck.
# 208 "data/maps/OlivineCity_House1/scripts.pory"
@
# 209 "data/maps/OlivineCity_House1/scripts.pory"
@ NO direction here is derived from the player's live position: every
# 210 "data/maps/OlivineCity_House1/scripts.pory"
@ turnobject aims at another actor on a fixed tile. That is what makes the
# 211 "data/maps/OlivineCity_House1/scripts.pory"
@ block correct both from the frame trigger (player at (4,8)) and from an
# 212 "data/maps/OlivineCity_House1/scripts.pory"
@ object script (player anywhere in the room).
# 213 "data/maps/OlivineCity_House1/scripts.pory"
@ closemessage before EVERY turnobject: without it the turn happens behind the
# 214 "data/maps/OlivineCity_House1/scripts.pory"
@ open text box.
# 215 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionScene::
# 216 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionOpen, MSGBOX_DEFAULT
# 217 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 218 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionKukui, MSGBOX_DEFAULT
# 219 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 220 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineCalled, MSGBOX_DEFAULT
# 221 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 222 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_SOUTH
# 223 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_NORTH
# 224 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillie, MSGBOX_DEFAULT
# 225 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 226 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladion, MSGBOX_DEFAULT
# 227 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 228 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_EAST
# 229 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_EAST
# 230 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCross, MSGBOX_DEFAULT
# 231 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 232 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_EAST
# 233 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCondition, MSGBOX_DEFAULT
# 234 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 235 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_SOUTH
# 236 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 237 "data/maps/OlivineCity_House1/scripts.pory"

# 238 "data/maps/OlivineCity_House1/scripts.pory"
@ The one gate of the arc (design sections 7 and 8): Solgaleo OR Lunala, in the
# 239 "data/maps/OlivineCity_House1/scripts.pory"
@ PARTY. checkspecies compiles to Scrcmd_checkspecies (src/scrcmd.c), which
# 240 "data/maps/OlivineCity_House1/scripts.pory"
@ calls CheckPartyHasSpecies (src/field_specials.c): it walks gPlayerParty only
# 241 "data/maps/OlivineCity_House1/scripts.pory"
@ and returns into VAR_RESULT. Consequences, all of them wanted by the design:
# 242 "data/maps/OlivineCity_House1/scripts.pory"
@   - one in the PC does not count; a Pokedex entry does not count;
# 243 "data/maps/OlivineCity_House1/scripts.pory"
@   - Cosmog and Cosmoem do not pass, and no evolution happens here;
# 244 "data/maps/OlivineCity_House1/scripts.pory"
@   - EITHER species satisfies it, and having both is never required.
# 245 "data/maps/OlivineCity_House1/scripts.pory"
@ Two checks, never one, and never a check for the family.
# 246 "data/maps/OlivineCity_House1/scripts.pory"
@ Reachable from the long scene, from the state-11 trigger and from the Looker
# 247 "data/maps/OlivineCity_House1/scripts.pory"
@ and Anabel object scripts, so it must read as a standalone question.
# 248 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionCheck::
# 249 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAsk, MSGBOX_DEFAULT
# 250 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 251 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_SOLGALEO
# 252 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
# 253 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_LUNALA
# 254 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
# 255 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionNotYet
# 256 "data/maps/OlivineCity_House1/scripts.pory"

# 257 "data/maps/OlivineCity_House1/scripts.pory"
@ Not yet. Nothing is spent: no mission is replayed, nobody leaves the room,
# 258 "data/maps/OlivineCity_House1/scripts.pory"
@ and the only thing that changes is 10 -> 11, which is what stops the long
# 259 "data/maps/OlivineCity_House1/scripts.pory"
@ cutscene from playing again. From 11 this whole block is four boxes.
# 260 "data/maps/OlivineCity_House1/scripts.pory"
@ The setvar is idempotent: running it again in state 11 rewrites 11, and
# 261 "data/maps/OlivineCity_House1/scripts.pory"
@ nothing ever goes back from 11 to 10.
# 262 "data/maps/OlivineCity_House1/scripts.pory"
@ releaseall (not release) because this script is reached from a lockall
# 263 "data/maps/OlivineCity_House1/scripts.pory"
@ context AND from a lock context: releaseall is correct in both, release would
# 264 "data/maps/OlivineCity_House1/scripts.pory"
@ leave the other objects frozen after the cutscene.
# 265 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionNotYet::
# 266 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionNotYet, MSGBOX_DEFAULT
# 267 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 268 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 269 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 270 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 271 "data/maps/OlivineCity_House1/scripts.pory"

# 272 "data/maps/OlivineCity_House1/scripts.pory"
@ Confirmed. The room recognises the Pokemon that came out of the egg Gladion
# 273 "data/maps/OlivineCity_House1/scripts.pory"
@ handed the player in Violet, and then Looker gives the hook to the altar.
# 274 "data/maps/OlivineCity_House1/scripts.pory"
@ Design section 7 item 7 (releasing the ship) and everything at the altar
# 275 "data/maps/OlivineCity_House1/scripts.pory"
@ belong to the NEXT document: this event ends on the flag.
# 276 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionConfirmed::
# 277 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionSeeIt, MSGBOX_DEFAULT
# 278 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 279 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladionEgg, MSGBOX_DEFAULT
# 280 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 281 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillieProud, MSGBOX_DEFAULT
# 282 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 283 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineKnows, MSGBOX_DEFAULT
# 284 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 285 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionWayBack, MSGBOX_DEFAULT
# 286 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 287 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionHook, MSGBOX_DEFAULT
# 288 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 289 "data/maps/OlivineCity_House1/scripts.pory"
	@ The ferry pass: the port sailor offers the altar route only to whoever
# 290 "data/maps/OlivineCity_House1/scripts.pory"
	@ carries it (OlivineCity_PortInside). Key item, so the bag cannot be full.
# 291 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicket, MSGBOX_DEFAULT
# 292 "data/maps/OlivineCity_House1/scripts.pory"
	giveitem ITEM_SUN_MOON_TICKET
# 293 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicketUse, MSGBOX_DEFAULT
# 294 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 295 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreen FADE_TO_BLACK
# 296 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED   @ handoff; NEVER cleared
# 297 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 12           @ invariant: flag and var together
# 298 "data/maps/OlivineCity_House1/scripts.pory"
	@ Reload in place: ON_TRANSITION hides the six visitors (they went ahead to
# 299 "data/maps/OlivineCity_House1/scripts.pory"
	@ the port), Looker and Anabel snap back to (4,5)/(7,5) from their
# 300 "data/maps/OlivineCity_House1/scripts.pory"
	@ templates, and the follower comes back (undoes hidefollower). Without
# 301 "data/maps/OlivineCity_House1/scripts.pory"
	@ this, all of that would happen in pieces as the camera moved.
# 302 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7), not (4,8): do not respawn the player on the room's only warp tile.
# 303 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7) is guaranteed free, because by state 12 the six are already hidden.
# 304 "data/maps/OlivineCity_House1/scripts.pory"
	@ The frame trigger fires again after this load with VAR_TEMP_1 zeroed, but
# 305 "data/maps/OlivineCity_House1/scripts.pory"
	@ dies twice over: the player is not at (4,8) AND state 12 matches no
# 306 "data/maps/OlivineCity_House1/scripts.pory"
	@ goto_if_eq in its list.
# 307 "data/maps/OlivineCity_House1/scripts.pory"
	warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7
# 308 "data/maps/OlivineCity_House1/scripts.pory"
	waitstate
# 309 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 310 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 311 "data/maps/OlivineCity_House1/scripts.pory"

# 312 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_End::
# 313 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 314 "data/maps/OlivineCity_House1/scripts.pory"

# 315 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerApproach:
# 316 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 317 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 318 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 319 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 320 "data/maps/OlivineCity_House1/scripts.pory"

# 321 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelApproach:
# 322 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 323 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 324 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 325 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 326 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 327 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 328 "data/maps/OlivineCity_House1/scripts.pory"

# 329 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerReturn:
# 330 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 331 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 332 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 333 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 334 "data/maps/OlivineCity_House1/scripts.pory"

# 335 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelReturn:
# 336 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 337 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 338 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 339 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 340 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 341 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 342 "data/maps/OlivineCity_House1/scripts.pory"

# 343 "data/maps/OlivineCity_House1/scripts.pory"
@ Shared by the arrival scene and by both object scripts in states 2, 4, 6
# 344 "data/maps/OlivineCity_House1/scripts.pory"
@ and 8, so a briefing can never be skipped by entering from an odd tile. It is
# 345 "data/maps/OlivineCity_House1/scripts.pory"
@ the ONE place that moves flag and var, and it moves them together.
# 346 "data/maps/OlivineCity_House1/scripts.pory"
@ Invariants:
# 347 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_BLACKTHORN  set <=> VAR_RIFT_MISSIONS_STATE == 3
# 348 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_MAHOGANY    set <=> VAR_RIFT_MISSIONS_STATE == 5
# 349 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_CHERRYGROVE set <=> VAR_RIFT_MISSIONS_STATE == 7
# 350 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_NEWBARK     set <=> VAR_RIFT_MISSIONS_STATE == 9
# 351 "data/maps/OlivineCity_House1/scripts.pory"
@ The four are mutually exclusive because the var holds one value.
# 352 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10 is the END of the chain: it opens no mission, it means "four done,
# 353 "data/maps/OlivineCity_House1/scripts.pory"
@ the Olivine reunion pending" (design section 7).
# 354 "data/maps/OlivineCity_House1/scripts.pory"
@ A goto inside a script reached by call is safe: call pushes the return
# 355 "data/maps/OlivineCity_House1/scripts.pory"
@ address and return pops it, however many gotos happened in between.
# 356 "data/maps/OlivineCity_House1/scripts.pory"
@ Highest state first, so the block reads newest mission to oldest.
# 357 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalk::
# 358 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_BriefingTalkM4
# 359 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_BriefingTalkM3
# 360 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_BriefingTalkM2
# 361 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through to M1 (state 2)
# 362 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM1::
# 363 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_Briefing, MSGBOX_DEFAULT
# 364 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 365 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
# 366 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 3
# 367 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 368 "data/maps/OlivineCity_House1/scripts.pory"

# 369 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM2::
# 370 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2, MSGBOX_DEFAULT
# 371 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 372 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
# 373 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 5
# 374 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 375 "data/maps/OlivineCity_House1/scripts.pory"

# 376 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM3::
# 377 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3, MSGBOX_DEFAULT
# 378 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 379 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
# 380 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 7
# 381 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 382 "data/maps/OlivineCity_House1/scripts.pory"

# 383 "data/maps/OlivineCity_House1/scripts.pory"
@ TRES msgbox, nao um. msgbox expande o texto inteiro em gStringVar4, que tem
# 384 "data/maps/OlivineCity_House1/scripts.pory"
@ 1000 bytes (EWRAM_DATA u8 gStringVar4[0x3E8], src/string_util.c). Este
# 385 "data/maps/OlivineCity_House1/scripts.pory"
@ briefing tem ~2000 e travava o jogo ao chegar em Olivine vindo de
# 386 "data/maps/OlivineCity_House1/scripts.pory"
@ Cherrygrove: StringExpandPlaceholders nao checa tamanho, entao ele escrevia
# 387 "data/maps/OlivineCity_House1/scripts.pory"
@ 1000 bytes por cima da EWRAM seguinte. Cada parte fica abaixo de ~800.
# 388 "data/maps/OlivineCity_House1/scripts.pory"
@ Sem closemessage entre elas: sFieldMessageBoxVisible continua TRUE, a caixa
# 389 "data/maps/OlivineCity_House1/scripts.pory"
@ nao desce nem sobe de novo, e a cena roda como uma fala so.
# 390 "data/maps/OlivineCity_House1/scripts.pory"
@ Cada parte PRECISA comecar com o seu {SPEAKER ...}: TrySetSpeakerFromMessage
# 391 "data/maps/OlivineCity_House1/scripts.pory"
@ le so o inicio de cada mensagem, e uma parte sem o codigo perderia a
# 392 "data/maps/OlivineCity_House1/scripts.pory"
@ plaquinha no meio da conversa.
# 393 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM4::
# 394 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4, MSGBOX_DEFAULT
# 395 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Faller, MSGBOX_DEFAULT
# 396 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4NewBark, MSGBOX_DEFAULT
# 397 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 398 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_NEWBARK
# 399 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 9
# 400 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 401 "data/maps/OlivineCity_House1/scripts.pory"

# 402 "data/maps/OlivineCity_House1/scripts.pory"
@ Branch order matters: 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, then >= 12. NEVER
# 403 "data/maps/OlivineCity_House1/scripts.pory"
@ leave a "goto_if_ge VAR_RIFT_MISSIONS_STATE, 4", ", 6", ", 8" or ", 10"
# 404 "data/maps/OlivineCity_House1/scripts.pory"
@ here - any one of them would swallow the states above it. This has now
# 405 "data/maps/OlivineCity_House1/scripts.pory"
@ happened THREE times: Mission 3 had to delete a "goto_if_ge ..., 6" left
# 406 "data/maps/OlivineCity_House1/scripts.pory"
@ behind by Mission 2, Mission 4 had to move a "goto_if_ge ..., 8" left behind
# 407 "data/maps/OlivineCity_House1/scripts.pory"
@ by Mission 3, and the pre-Necrozma reunion had to split the
# 408 "data/maps/OlivineCity_House1/scripts.pory"
@ "goto_if_ge ..., 10" Mission 4 left behind, which would have replayed the
# 409 "data/maps/OlivineCity_House1/scripts.pory"
@ whole cutscene at state 11 and kept saying reunion lines at state 12.
# 410 "data/maps/OlivineCity_House1/scripts.pory"
@ Fourth warning, same mistake: a NEW state enters as goto_if_eq, and only the
# 411 "data/maps/OlivineCity_House1/scripts.pory"
@ LAST line of the list may be a goto_if_ge.
# 412 "data/maps/OlivineCity_House1/scripts.pory"
@ States 0-1 fall through to the holiday line.
# 413 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Looker::
# 414 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 415 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 416 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_LookerBrief
# 417 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_LookerGoAhead
# 418 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_LookerBrief
# 419 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_LookerGoAheadM2
# 420 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerBrief
# 421 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_LookerGoAheadM3
# 422 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_LookerBrief
# 423 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_LookerGoAheadM4
# 424 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerReunion
# 425 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_LookerRecheck
# 426 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_LookerAltar
# 427 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerHoliday, MSGBOX_DEFAULT
# 428 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 429 "data/maps/OlivineCity_House1/scripts.pory"

# 430 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerBrief::
# 431 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 432 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 433 "data/maps/OlivineCity_House1/scripts.pory"

# 434 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAhead::
# 435 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAhead, MSGBOX_DEFAULT
# 436 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 437 "data/maps/OlivineCity_House1/scripts.pory"

# 438 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM2::
# 439 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM2, MSGBOX_DEFAULT
# 440 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 441 "data/maps/OlivineCity_House1/scripts.pory"

# 442 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM3::
# 443 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM3, MSGBOX_DEFAULT
# 444 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 445 "data/maps/OlivineCity_House1/scripts.pory"

# 446 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM4::
# 447 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM4, MSGBOX_DEFAULT
# 448 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 449 "data/maps/OlivineCity_House1/scripts.pory"

# 450 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: the alternative way into the reunion, for a player who walks past
# 451 "data/maps/OlivineCity_House1/scripts.pory"
@ the frame trigger's tile check. ReunionScene has no applymovement at all -
# 452 "data/maps/OlivineCity_House1/scripts.pory"
@ only msgbox and turnobject on actors with fixed tiles, and none of the six
# 453 "data/maps/OlivineCity_House1/scripts.pory"
@ visitors wanders (all of them are MOVEMENT_TYPE_FACE_*) - so it plays
# 454 "data/maps/OlivineCity_House1/scripts.pory"
@ identically under lock. All that is missing is Looker's step down.
# 455 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerReunion::
# 456 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 457 "data/maps/OlivineCity_House1/scripts.pory"

# 458 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11: only the open question, never the cutscene again.
# 459 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerRecheck::
# 460 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 461 "data/maps/OlivineCity_House1/scripts.pory"

# 462 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: last stop of this document. The ship, the voyage and the altar
# 463 "data/maps/OlivineCity_House1/scripts.pory"
@ belong to the next one, which starts from FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED
# 464 "data/maps/OlivineCity_House1/scripts.pory"
@ and VAR_RIFT_MISSIONS_STATE >= 12. Repeatable on purpose: a player who saved
# 465 "data/maps/OlivineCity_House1/scripts.pory"
@ and came back must be able to ask where to go.
# 466 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerAltar::
# 467 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerAltar, MSGBOX_DEFAULT
# 468 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 469 "data/maps/OlivineCity_House1/scripts.pory"

# 470 "data/maps/OlivineCity_House1/scripts.pory"
@ Same branch order as Looker, and the same warning about goto_if_ge.
# 471 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Anabel::
# 472 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 473 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 474 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_AnabelBrief
# 475 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_AnabelGoAhead
# 476 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_AnabelBrief
# 477 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_AnabelGoAheadM2
# 478 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_AnabelBrief
# 479 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_AnabelGoAheadM3
# 480 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_AnabelBrief
# 481 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_AnabelGoAheadM4
# 482 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_AnabelReunion
# 483 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_AnabelRecheck
# 484 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_AnabelAltar
# 485 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelHoliday, MSGBOX_DEFAULT
# 486 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 487 "data/maps/OlivineCity_House1/scripts.pory"

# 488 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelBrief::
# 489 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 490 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 491 "data/maps/OlivineCity_House1/scripts.pory"

# 492 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAhead::
# 493 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAhead, MSGBOX_DEFAULT
# 494 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 495 "data/maps/OlivineCity_House1/scripts.pory"

# 496 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM2::
# 497 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM2, MSGBOX_DEFAULT
# 498 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 499 "data/maps/OlivineCity_House1/scripts.pory"

# 500 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM3::
# 501 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM3, MSGBOX_DEFAULT
# 502 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 503 "data/maps/OlivineCity_House1/scripts.pory"

# 504 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM4::
# 505 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM4, MSGBOX_DEFAULT
# 506 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 507 "data/maps/OlivineCity_House1/scripts.pory"

# 508 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: Anabel sells Beast Balls from state 4 on (design section 5),
# 509 "data/maps/OlivineCity_House1/scripts.pory"
@ still pending since Rift Mission 1. This event passes through her script
# 510 "data/maps/OlivineCity_House1/scripts.pory"
@ without resolving it.
# 511 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: same entry into the reunion as Looker's, see the note there.
# 512 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelReunion::
# 513 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 514 "data/maps/OlivineCity_House1/scripts.pory"

# 515 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelRecheck::
# 516 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 517 "data/maps/OlivineCity_House1/scripts.pory"

# 518 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: last stop of this document, same as LookerAltar.
# 519 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelAltar::
# 520 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelAltar, MSGBOX_DEFAULT
# 521 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 522 "data/maps/OlivineCity_House1/scripts.pory"

# 523 "data/maps/OlivineCity_House1/scripts.pory"
@ The four visitors. They exist to be talked to in state 11, the only state in
# 524 "data/maps/OlivineCity_House1/scripts.pory"
@ which the player walks the room with everyone present - in state 12 they are
# 525 "data/maps/OlivineCity_House1/scripts.pory"
@ not here to be talked to, and in state 10 the cutscene runs on arrival. So
# 526 "data/maps/OlivineCity_House1/scripts.pory"
@ they need no branch on the var: one box each.
# 527 "data/maps/OlivineCity_House1/scripts.pory"
@ Ninetales and Silvally have "script": "NULL" (design 3.2, skill
# 528 "data/maps/OlivineCity_House1/scripts.pory"
@ parceiro-pokemon-de-npc): they are their owners' partners out of the ball,
# 529 "data/maps/OlivineCity_House1/scripts.pory"
@ share FLAG_TEMP_1 with them, and come and go together.
# 530 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: placeholder dialogue, one box each.
# 531 "data/maps/OlivineCity_House1/scripts.pory"
@ The three who come back. There is NO battle anywhere in this room in the
# 532 "data/maps/OlivineCity_House1/scripts.pory"
@ post-game: this is the place where they are not working.
# 533 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLusamine::
# 534 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 535 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 536 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseLusaminePost
# 537 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLusamine, MSGBOX_DEFAULT
# 538 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 539 "data/maps/OlivineCity_House1/scripts.pory"

# 540 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseLusaminePost::
# 541 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseLusaminePost, MSGBOX_DEFAULT
# 542 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 543 "data/maps/OlivineCity_House1/scripts.pory"

# 544 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLillie::
# 545 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 546 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 547 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseLilliePost
# 548 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLillie, MSGBOX_DEFAULT
# 549 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 550 "data/maps/OlivineCity_House1/scripts.pory"

# 551 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseLilliePost::
# 552 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseLilliePost, MSGBOX_DEFAULT
# 553 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 554 "data/maps/OlivineCity_House1/scripts.pory"

# 555 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionGladion::
# 556 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 557 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 558 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseGladionPost
# 559 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleGladion, MSGBOX_DEFAULT
# 560 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 561 "data/maps/OlivineCity_House1/scripts.pory"

# 562 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseGladionPost::
# 563 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseGladionPost, MSGBOX_DEFAULT
# 564 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 565 "data/maps/OlivineCity_House1/scripts.pory"

# 566 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionKukui::
# 567 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 568 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 569 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleKukui, MSGBOX_DEFAULT
# 570 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 571 "data/maps/OlivineCity_House1/scripts.pory"

# 572 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReleaseEnd::
# 573 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 574 "data/maps/OlivineCity_House1/scripts.pory"
	release
# 575 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 576 "data/maps/OlivineCity_House1/scripts.pory"

# 577 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1 briefing: final text (22/09/2026). It names Clair and "a Pokemon
# 578 "data/maps/OlivineCity_House1/scripts.pory"
@ made of light" and nothing else: Gladion and the two Ultra Beasts are the
# 579 "data/maps/OlivineCity_House1/scripts.pory"
@ surprises of the scene in Blackthorn, so they are never mentioned here.
# 580 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_Briefing:
# 581 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Ah, {PLAYER}! You came.\n"
# 582 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Please, come in.\p"
# 583 "data/maps/OlivineCity_House1/scripts.pory"
	.string "First, the truth. Looker,\n"
# 584 "data/maps/OlivineCity_House1/scripts.pory"
	.string "International Police.\p"
# 585 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And this is my Chief, Anabel.\p"
# 586 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Thank you for coming,\n"
# 587 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Champion. We owe you an\l"
# 588 "data/maps/OlivineCity_House1/scripts.pory"
	.string "explanation for the holiday.\p"
# 589 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We came to Johto\n"
# 590 "data/maps/OlivineCity_House1/scripts.pory"
	.string "following readings.\l"
# 591 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Distortions in space.\p"
# 592 "data/maps/OlivineCity_House1/scripts.pory"
	.string "In Alola, readings like these\n"
# 593 "data/maps/OlivineCity_House1/scripts.pory"
	.string "came before Ultra Wormholes.\p"
# 594 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Openings to other\n"
# 595 "data/maps/OlivineCity_House1/scripts.pory"
	.string "worlds. What comes through,\l"
# 596 "data/maps/OlivineCity_House1/scripts.pory"
	.string "we call Ultra Beasts.\p"
# 597 "data/maps/OlivineCity_House1/scripts.pory"
	.string "They are not villains. Most\n"
# 598 "data/maps/OlivineCity_House1/scripts.pory"
	.string "are lost, and frightened,\l"
# 599 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and very strong.\p"
# 600 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}This morning the Gym\n"
# 601 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Leader of Blackthorn called us.\p"
# 602 "data/maps/OlivineCity_House1/scripts.pory"
	.string "She described a Pokémon\n"
# 603 "data/maps/OlivineCity_House1/scripts.pory"
	.string "standing in the middle of her\l"
# 604 "data/maps/OlivineCity_House1/scripts.pory"
	.string "town. A Pokémon… made of light.\p"
# 605 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Clair has ordered\n"
# 606 "data/maps/OlivineCity_House1/scripts.pory"
	.string "everyone indoors and is\l"
# 607 "data/maps/OlivineCity_House1/scripts.pory"
	.string "holding it off herself.\p"
# 608 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We need to be there.\n"
# 609 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we would like you with us.\p"
# 610 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Meet us by the Pokémon\n"
# 611 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center in Blackthorn.\p"
# 612 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare as you would for the\n"
# 613 "data/maps/OlivineCity_House1/scripts.pory"
	.string "League, {PLAYER}. Perhaps more.$"
# 614 "data/maps/OlivineCity_House1/scripts.pory"

# 615 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Blackthorn hook names no place on purpose ("the moment
# 616 "data/maps/OlivineCity_House1/scripts.pory"
@ something opens, you will be the first to know"). This briefing is that
# 617 "data/maps/OlivineCity_House1/scripts.pory"
@ moment: Mahogany is news to the player here.
# 618 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 2 briefing: final text (22/09/2026). It names Pryce's call and the
# 619 "data/maps/OlivineCity_House1/scripts.pory"
@ blackout and nothing else: Lillie, the evacuation (Pryce's own line) and
# 620 "data/maps/OlivineCity_House1/scripts.pory"
@ the creature from Blackthorn are what the player finds in Mahogany, so
# 621 "data/maps/OlivineCity_House1/scripts.pory"
@ they are never mentioned here.
# 622 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2:
# 623 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Your timing\n"
# 624 "data/maps/OlivineCity_House1/scripts.pory"
	.string "is uncanny. It has started\l"
# 625 "data/maps/OlivineCity_House1/scripts.pory"
	.string "again. Mahogany Town.\p"
# 626 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Two signatures again.\n"
# 627 "data/maps/OlivineCity_House1/scripts.pory"
	.string "One electrical. One… heavy.\p"
# 628 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The town lost its power\n"
# 629 "data/maps/OlivineCity_House1/scripts.pory"
	.string "three nights ago.\p"
# 630 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Every lamp, every machine.\n"
# 631 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Only the Pokémon Center still\l"
# 632 "data/maps/OlivineCity_House1/scripts.pory"
	.string "has light.\p"
# 633 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The readings come from\n"
# 634 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the town itself. Every night,\l"
# 635 "data/maps/OlivineCity_House1/scripts.pory"
	.string "at the same hour.\p"
# 636 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No sign of the light from\n"
# 637 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn. Not yet.\p"
# 638 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The Gym Leader, Pryce,\n"
# 639 "data/maps/OlivineCity_House1/scripts.pory"
	.string "telephoned us himself.\p"
# 640 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He said four words.\n"
# 641 "data/maps/OlivineCity_House1/scripts.pory"
	.string "“Lights out. Come now.”\p"
# 642 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…I have decided to find that\n"
# 643 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reassuring.\p"
# 644 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Meet us by the Pokémon\n"
# 645 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center, {PLAYER}.\p"
# 646 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare for two of them.\n"
# 647 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not one.$"
# 648 "data/maps/OlivineCity_House1/scripts.pory"

# 649 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Mahogany hook names no place on purpose (design section 6,
# 650 "data/maps/OlivineCity_House1/scripts.pory"
@ "gancho sem destino"). This briefing is where Cherrygrove is revealed.
# 651 "data/maps/OlivineCity_House1/scripts.pory"
@ V21: the call came from KUKUI, not from a Gym Leader - Cherrygrove has no
# 652 "data/maps/OlivineCity_House1/scripts.pory"
@ Gym, and the author asked for the Professor to be the one who raised the
# 653 "data/maps/OlivineCity_House1/scripts.pory"
@ alarm. The scene in the house is also where Looker and Anabel decide,
# 654 "data/maps/OlivineCity_House1/scripts.pory"
@ out loud and wrongly, that he is a civilian who needs collecting: that
# 655 "data/maps/OlivineCity_House1/scripts.pory"
@ misjudgement is what the beach pays off. The Ultra Beasts are never named
# 656 "data/maps/OlivineCity_House1/scripts.pory"
@ here, and neither is the creature - those belong to the shore.
# 657 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3:
# 658 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Come in, come\n"
# 659 "data/maps/OlivineCity_House1/scripts.pory"
	.string "in. It has opened again.\p"
# 660 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove City.\p"
# 661 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Two signatures.\p"
# 662 "data/maps/OlivineCity_House1/scripts.pory"
	.string "One of them will not hold\n"
# 663 "data/maps/OlivineCity_House1/scripts.pory"
	.string "still.\p"
# 664 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}And here is the part I\n"
# 665 "data/maps/OlivineCity_House1/scripts.pory"
	.string "cannot account for.\p"
# 666 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We did not find it.\p"
# 667 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It was reported to us. By\n"
# 668 "data/maps/OlivineCity_House1/scripts.pory"
	.string "telephone. Four days ago.\p"
# 669 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}A researcher from Alola.\p"
# 670 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He gave us a time window, a\n"
# 671 "data/maps/OlivineCity_House1/scripts.pory"
	.string "bearing, and the tide.\p"
# 672 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Then he called back and\n"
# 673 "data/maps/OlivineCity_House1/scripts.pory"
	.string "corrected the window.\p"
# 674 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Twice.\p"
# 675 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He was right twice.\p"
# 676 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel, read me his file\n"
# 677 "data/maps/OlivineCity_House1/scripts.pory"
	.string "again.\p"
# 678 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}“Professor Kukui.\n"
# 679 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pokémon move research.”\p"
# 680 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No enforcement record. No\n"
# 681 "data/maps/OlivineCity_House1/scripts.pory"
	.string "combat authorisation.\p"
# 682 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It is two pages long, Looker.\p"
# 683 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Two pages, and he is\n"
# 684 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sitting on a beach under an\l"
# 685 "data/maps/OlivineCity_House1/scripts.pory"
	.string "open sky.\p"
# 686 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}, we have evacuated\n"
# 687 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove into the Violet\l"
# 688 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Gym. Every soul but one.\p"
# 689 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}He will not leave the\n"
# 690 "data/maps/OlivineCity_House1/scripts.pory"
	.string "shore. He says somebody has to\l"
# 691 "data/maps/OlivineCity_House1/scripts.pory"
	.string "be looking when it opens.\p"
# 692 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}He is quite right, and\n"
# 693 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that is what frightens me.\p"
# 694 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The northwest beach, {PLAYER}.\p"
# 695 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare for two of them, and\n"
# 696 "data/maps/OlivineCity_House1/scripts.pory"
	.string "go and stand in front of that\l"
# 697 "data/maps/OlivineCity_House1/scripts.pory"
	.string "man.$"
# 698 "data/maps/OlivineCity_House1/scripts.pory"

# 699 "data/maps/OlivineCity_House1/scripts.pory"
@ The longest briefing of the arc on purpose (design section 6.4): it is the
# 700 "data/maps/OlivineCity_House1/scripts.pory"
@ one that names the town the player grew up in, puts their mother in the
# 701 "data/maps/OlivineCity_House1/scripts.pory"
@ half that refused to evacuate, and has Looker ask - once, in four missions
# 702 "data/maps/OlivineCity_House1/scripts.pory"
@ - whether they actually want to go.
# 703 "data/maps/OlivineCity_House1/scripts.pory"
@
# 704 "data/maps/OlivineCity_House1/scripts.pory"
@ IT IS ALSO WHERE THE FALLER CONVERSATION LIVES. Author's note, revision 4:
# 705 "data/maps/OlivineCity_House1/scripts.pory"
@ that conversation does not belong in the middle of a fight. Three rifts
# 706 "data/maps/OlivineCity_House1/scripts.pory"
@ opening at once is the first thing Anabel has ever felt from another city,
# 707 "data/maps/OlivineCity_House1/scripts.pory"
@ and feeling it from a chair in Olivine is what makes her finally sit the
# 708 "data/maps/OlivineCity_House1/scripts.pory"
@ player down and explain the whole of it - what she is, what she remembers,
# 709 "data/maps/OlivineCity_House1/scripts.pory"
@ what she does not, and the promise she made out of it. New Bark only gets
# 710 "data/maps/OlivineCity_House1/scripts.pory"
@ the callback (NewBarkTown_Text_UBAnabelPromise). Do not move this back.
# 711 "data/maps/OlivineCity_House1/scripts.pory"
@
# 712 "data/maps/OlivineCity_House1/scripts.pory"
@ TWO THINGS THIS BRIEFING DOES NOT SAY, both deliberate:
# 713 "data/maps/OlivineCity_House1/scripts.pory"
@ 1. Kukui is NOT going to New Bark. The chain is Elm -> Kukui -> Looker:
# 714 "data/maps/OlivineCity_House1/scripts.pory"
@    Elm posted six weeks of a reading he thought was broken to the one man
# 715 "data/maps/OlivineCity_House1/scripts.pory"
@    who would not laugh at it, and that man telephoned the police. Elm is
# 716 "data/maps/OlivineCity_House1/scripts.pory"
@    inside the analysis from here on; Kukui is not in the scene.
# 717 "data/maps/OlivineCity_House1/scripts.pory"
@ 2. Lusamine is not mentioned AT ALL. Nobody sent for her and nobody
# 718 "data/maps/OlivineCity_House1/scripts.pory"
@    announces her - she is simply standing on the road when the player
# 719 "data/maps/OlivineCity_House1/scripts.pory"
@    arrives. Putting her name in here spends the only surprise the mission
# 720 "data/maps/OlivineCity_House1/scripts.pory"
@    has before the creature.
# 721 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4:
# 722 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Sit down.\p"
# 723 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No - actually, don't.\p"
# 724 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There isn't time, and you would\n"
# 725 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not anyway.\p"
# 726 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove holds.\p"
# 727 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And the Professor? Did he eat\n"
# 728 "data/maps/OlivineCity_House1/scripts.pory"
	.string "something, at last?\p"
# 729 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}He ate, and then he\n"
# 730 "data/maps/OlivineCity_House1/scripts.pory"
	.string "read every log in Johto.\p"
# 731 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He telephoned at six this\n"
# 732 "data/maps/OlivineCity_House1/scripts.pory"
	.string "morning, from a post office, to\l"
# 733 "data/maps/OlivineCity_House1/scripts.pory"
	.string "read us somebody else's\l"
# 734 "data/maps/OlivineCity_House1/scripts.pory"
	.string "notebook.\p"
# 735 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Professor Elm has had the same\n"
# 736 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reading for six weeks. He wrote\l"
# 737 "data/maps/OlivineCity_House1/scripts.pory"
	.string "“check the sensor” in the\l"
# 738 "data/maps/OlivineCity_House1/scripts.pory"
	.string "margin every time.\p"
# 739 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And then he posted the whole\n"
# 740 "data/maps/OlivineCity_House1/scripts.pory"
	.string "thing to Alola anyway.\p"
# 741 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}A man who suspects he\n"
# 742 "data/maps/OlivineCity_House1/scripts.pory"
	.string "is wrong and files it in\l"
# 743 "data/maps/OlivineCity_House1/scripts.pory"
	.string "writing. There are worse\l"
# 744 "data/maps/OlivineCity_House1/scripts.pory"
	.string "witnesses.\p"
# 745 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Is the Professor going?\p"
# 746 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}No. He is going home.\p"
# 747 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He did the one thing only he\n"
# 748 "data/maps/OlivineCity_House1/scripts.pory"
	.string "could do, which was recognise\l"
# 749 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it, and he handed it to us.\p"
# 750 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Elm is the one on the ground\n"
# 751 "data/maps/OlivineCity_House1/scripts.pory"
	.string "now. It is his instrument, his\l"
# 752 "data/maps/OlivineCity_House1/scripts.pory"
	.string "six weeks and his town.$"
# 753 "data/maps/OlivineCity_House1/scripts.pory"

# 754 "data/maps/OlivineCity_House1/scripts.pory"
@ Parte 2 de 3 (ver o comentario em BriefingTalkM4 sobre gStringVar4).
# 755 "data/maps/OlivineCity_House1/scripts.pory"
@ Continua na MESMA caixa; comeca no "...Three, Anabel?" do Looker.
# 756 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Faller:
# 757 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Three, Anabel?\p"
# 758 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Three.\p"
# 759 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Opening together. Closing\n"
# 760 "data/maps/OlivineCity_House1/scripts.pory"
	.string "together.\p"
# 761 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Looker, I need the chair.\p"
# 762 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief-\p"
# 763 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'm fine. Sit down,\n"
# 764 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. This part is for you\l"
# 765 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I would rather say it here\l"
# 766 "data/maps/OlivineCity_House1/scripts.pory"
	.string "than shout it later.\p"
# 767 "data/maps/OlivineCity_House1/scripts.pory"
	.string "On that beach in Cherrygrove I\n"
# 768 "data/maps/OlivineCity_House1/scripts.pory"
	.string "told you what I am.\p"
# 769 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I did not tell you the rest.\p"
# 770 "data/maps/OlivineCity_House1/scripts.pory"
	.string "A Faller is someone who came\n"
# 771 "data/maps/OlivineCity_House1/scripts.pory"
	.string "through one of those tears and\l"
# 772 "data/maps/OlivineCity_House1/scripts.pory"
	.string "stayed on this side.\p"
# 773 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I don't remember where I came\n"
# 774 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from. I've stopped pretending\l"
# 775 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that will come back.\p"
# 776 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I remember someone's hand.\p"
# 777 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That is the whole memory.\n"
# 778 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Someone reached down, and I\l"
# 779 "data/maps/OlivineCity_House1/scripts.pory"
	.string "wasn't alone anymore.\p"
# 780 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And I feel them open. Only\n"
# 781 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that, and only a few seconds\l"
# 782 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before the meter does.\p"
# 783 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn I felt from the\n"
# 784 "data/maps/OlivineCity_House1/scripts.pory"
	.string "street. The Lake from the\l"
# 785 "data/maps/OlivineCity_House1/scripts.pory"
	.string "street. The beach from the\l"
# 786 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sand.$"
# 787 "data/maps/OlivineCity_House1/scripts.pory"

# 788 "data/maps/OlivineCity_House1/scripts.pory"
@ Parte 3 de 3. A Anabel ainda esta falando, por isso o {SPEAKER NAME_ANABEL}
# 789 "data/maps/OlivineCity_House1/scripts.pory"
@ no comeco: sem ele esta parte subiria sem plaquinha nenhuma.
# 790 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4NewBark:
# 791 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{PLAYER} - I felt these three\n"
# 792 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from this chair.\p"
# 793 "data/maps/OlivineCity_House1/scripts.pory"
	.string "From Olivine. Sixty miles of\n"
# 794 "data/maps/OlivineCity_House1/scripts.pory"
	.string "water and a mountain.\p"
# 795 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…You have never once\n"
# 796 "data/maps/OlivineCity_House1/scripts.pory"
	.string "put that in a report.\p"
# 797 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Put it in this one.\p"
# 798 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll sign it.\p"
# 799 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. New Bark Town\n"
# 800 "data/maps/OlivineCity_House1/scripts.pory"
	.string "has no Pokémon Center.\p"
# 801 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No Gym.\p"
# 802 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It has a laboratory and about\n"
# 803 "data/maps/OlivineCity_House1/scripts.pory"
	.string "forty people.\p"
# 804 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We told them to leave.\p"
# 805 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Half of them would not.\p"
# 806 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Your mother is one of the half.\p"
# 807 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Three missions, {PLAYER}, and I\n"
# 808 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have never once asked you this.\p"
# 809 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Do you want to go?\p"
# 810 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Heal everything.\p"
# 811 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Take these.\p"
# 812 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we are going with you -\n"
# 813 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that part is not a question.$"
# 814 "data/maps/OlivineCity_House1/scripts.pory"

# 815 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerHoliday:
# 816 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Hm? Oh, pay no\n"
# 817 "data/maps/OlivineCity_House1/scripts.pory"
	.string "attention to moi.\p"
# 818 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am simply… on holiday.\n"
# 819 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Yes. A holiday by the sea.$"
# 820 "data/maps/OlivineCity_House1/scripts.pory"

# 821 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAhead:
# 822 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Blackthorn, {PLAYER}!\n"
# 823 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Clair cannot hold it forever.\p"
# 824 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are leaving right behind\n"
# 825 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you!$"
# 826 "data/maps/OlivineCity_House1/scripts.pory"

# 827 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM2:
# 828 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Mahogany, {PLAYER}!\n"
# 829 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are right behind you.$"
# 830 "data/maps/OlivineCity_House1/scripts.pory"

# 831 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM3:
# 832 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The northwest shore,\n"
# 833 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 834 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You cannot miss him.\p"
# 835 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He is the only man left in\n"
# 836 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that town, and he is wearing a\l"
# 837 "data/maps/OlivineCity_House1/scripts.pory"
	.string "lab coat on a beach.$"
# 838 "data/maps/OlivineCity_House1/scripts.pory"

# 839 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM4:
# 840 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}New Bark Town,\n"
# 841 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. Your own front door.\p"
# 842 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am sorry it is this one.$"
# 843 "data/maps/OlivineCity_House1/scripts.pory"

# 844 "data/maps/OlivineCity_House1/scripts.pory"

# 845 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelHoliday:
# 846 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Looker insists we are\n"
# 847 "data/maps/OlivineCity_House1/scripts.pory"
	.string "on vacation.\p"
# 848 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He has been reading the same\n"
# 849 "data/maps/OlivineCity_House1/scripts.pory"
	.string "newspaper for three days.$"
# 850 "data/maps/OlivineCity_House1/scripts.pory"

# 851 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAhead:
# 852 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go on ahead.\p"
# 853 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll be there before you\n"
# 854 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reach the Pokémon Center.$"
# 855 "data/maps/OlivineCity_House1/scripts.pory"

# 856 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM2:
# 857 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go on.\p"
# 858 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mr. Pryce does not strike me\n"
# 859 "data/maps/OlivineCity_House1/scripts.pory"
	.string "as a man who calls for help\l"
# 860 "data/maps/OlivineCity_House1/scripts.pory"
	.string "lightly.$"
# 861 "data/maps/OlivineCity_House1/scripts.pory"

# 862 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM3:
# 863 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go on.\p"
# 864 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And whatever he is doing when\n"
# 865 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you get there, {PLAYER}-\p"
# 866 "data/maps/OlivineCity_House1/scripts.pory"
	.string "make him sit down for one\n"
# 867 "data/maps/OlivineCity_House1/scripts.pory"
	.string "minute.$"
# 868 "data/maps/OlivineCity_House1/scripts.pory"

# 869 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM4:
# 870 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go.\p"
# 871 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll be a step behind you the\n"
# 872 "data/maps/OlivineCity_House1/scripts.pory"
	.string "whole way.$"
# 873 "data/maps/OlivineCity_House1/scripts.pory"

# 874 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 875 "data/maps/OlivineCity_House1/scripts.pory"
@ Pre-Necrozma reunion texts.
# 876 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: all placeholder, rewrite in the design's voice (section 3.1):
# 877 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker theatrical and warm; Anabel precise; Lusamine formal and blunt;
# 878 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie direct; Gladion economical; Kukui enthusiastic.
# 879 "data/maps/OlivineCity_House1/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 880 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 881 "data/maps/OlivineCity_House1/scripts.pory"

# 882 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionOpen:
# 883 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Come in.\p"
# 884 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mind the chairs - there are\n"
# 885 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not enough of them, and I\l"
# 886 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have stopped apologising.\p"
# 887 "data/maps/OlivineCity_House1/scripts.pory"
	.string "New Bark holds. Four in four,\n"
# 888 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I am not certain that is\l"
# 889 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the word for it.\p"
# 890 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The file is closed. What is in\n"
# 891 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it is worse than what we\l"
# 892 "data/maps/OlivineCity_House1/scripts.pory"
	.string "opened it for.\p"
# 893 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Which is why everyone in this\n"
# 894 "data/maps/OlivineCity_House1/scripts.pory"
	.string "room came when I asked.\p"
# 895 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Look at them. I did not have\n"
# 896 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to explain twice.$"
# 897 "data/maps/OlivineCity_House1/scripts.pory"

# 898 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionKukui:
# 899 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Your rifts closed\n"
# 900 "data/maps/OlivineCity_House1/scripts.pory"
	.string "toward one bearing.\p"
# 901 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel's number, Elm's six\n"
# 902 "data/maps/OlivineCity_House1/scripts.pory"
	.string "weeks of it, my rhythm.\p"
# 903 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Three wrong tools, one\n"
# 904 "data/maps/OlivineCity_House1/scripts.pory"
	.string "answer.\p"
# 905 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There's a place out there,\n"
# 906 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. An altar.\p"
# 907 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We can put a boat on it.$"
# 908 "data/maps/OlivineCity_House1/scripts.pory"

# 909 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineCalled:
# 910 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I asked the\n"
# 911 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Inspector to call this\l"
# 912 "data/maps/OlivineCity_House1/scripts.pory"
	.string "meeting.\p"
# 913 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not as Aether. Aether would\n"
# 914 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have sent a report.\p"
# 915 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I owe the people in this room\n"
# 916 "data/maps/OlivineCity_House1/scripts.pory"
	.string "an accounting, and two of\l"
# 917 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them are mine.$"
# 918 "data/maps/OlivineCity_House1/scripts.pory"

# 919 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie (3,6) and Gladion (3,7) have just turned to face each other.
# 920 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillie:
# 921 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}…You asked for us.\n"
# 922 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Both of us.\p"
# 923 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'm not going to pretend\n"
# 924 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that's nothing.\p"
# 925 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It isn't nothing.$"
# 926 "data/maps/OlivineCity_House1/scripts.pory"

# 927 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladion:
# 928 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}We'll do the\n"
# 929 "data/maps/OlivineCity_House1/scripts.pory"
	.string "accounting after.\p"
# 930 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Whatever is at that altar, it\n"
# 931 "data/maps/OlivineCity_House1/scripts.pory"
	.string "doesn't wait for our family\l"
# 932 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to sort itself out.$"
# 933 "data/maps/OlivineCity_House1/scripts.pory"

# 934 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCross:
# 935 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Then let me say the\n"
# 936 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rest of it plainly.\p"
# 937 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I intend to cross.\p"
# 938 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I have been on the other side\n"
# 939 "data/maps/OlivineCity_House1/scripts.pory"
	.string "of a door like that one.\p"
# 940 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nobody else in this room has.$"
# 941 "data/maps/OlivineCity_House1/scripts.pory"

# 942 "data/maps/OlivineCity_House1/scripts.pory"
@ ONE box of recap and no more (design 3.1): Anabel told them all of this in
# 943 "data/maps/OlivineCity_House1/scripts.pory"
@ New Bark. Here it is an argument, not news.
# 944 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCondition:
# 945 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}You have. I have as\n"
# 946 "data/maps/OlivineCity_House1/scripts.pory"
	.string "well, and I came back wrong,\l"
# 947 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I told you all so in New\l"
# 948 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bark.\p"
# 949 "data/maps/OlivineCity_House1/scripts.pory"
	.string "So here is my condition,\n"
# 950 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Madame, and it is not\l"
# 951 "data/maps/OlivineCity_House1/scripts.pory"
	.string "negotiable:\p"
# 952 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nobody crosses without a way\n"
# 953 "data/maps/OlivineCity_House1/scripts.pory"
	.string "back.\p"
# 954 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not you. Not me.\n"
# 955 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not the Champion.$"
# 956 "data/maps/OlivineCity_House1/scripts.pory"

# 957 "data/maps/OlivineCity_House1/scripts.pory"
@ Must read standalone: this is also the whole of the state-11 question.
# 958 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAsk:
# 959 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And a way through\n"
# 960 "data/maps/OlivineCity_House1/scripts.pory"
	.string "needs something that can open\l"
# 961 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it.\p"
# 962 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not a machine. We tried\n"
# 963 "data/maps/OlivineCity_House1/scripts.pory"
	.string "machines for six weeks.\p"
# 964 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Your\n"
# 965 "data/maps/OlivineCity_House1/scripts.pory"
	.string "partner.\p"
# 966 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The one that started as an\n"
# 967 "data/maps/OlivineCity_House1/scripts.pory"
	.string "egg.\p"
# 968 "data/maps/OlivineCity_House1/scripts.pory"
	.string "May we see them?$"
# 969 "data/maps/OlivineCity_House1/scripts.pory"

# 970 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionNotYet:
# 971 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Ah. Not yet.\p"
# 972 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}That's not a no!\n"
# 973 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's a “give it time”.\p"
# 974 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It's still growing into what\n"
# 975 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it's going to be.\p"
# 976 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then we prepare, and\n"
# 977 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you raise them.\p"
# 978 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Come back when they have\n"
# 979 "data/maps/OlivineCity_House1/scripts.pory"
	.string "finished becoming Solgaleo\l"
# 980 "data/maps/OlivineCity_House1/scripts.pory"
	.string "or Lunala.\p"
# 981 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are not going anywhere.\p"
# 982 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Frankly, there is nowhere for\n"
# 983 "data/maps/OlivineCity_House1/scripts.pory"
	.string "six people to go in this\l"
# 984 "data/maps/OlivineCity_House1/scripts.pory"
	.string "room.$"
# 985 "data/maps/OlivineCity_House1/scripts.pory"

# 986 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionSeeIt:
# 987 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Oh.\p"
# 988 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}That is it.\p"
# 989 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That is the reading, standing\n"
# 990 "data/maps/OlivineCity_House1/scripts.pory"
	.string "in a living room in Olivine.$"
# 991 "data/maps/OlivineCity_House1/scripts.pory"

# 992 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladionEgg:
# 993 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}I handed you that\n"
# 994 "data/maps/OlivineCity_House1/scripts.pory"
	.string "egg in Violet and told you to\l"
# 995 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keep it away from people\l"
# 996 "data/maps/OlivineCity_House1/scripts.pory"
	.string "like us.\p"
# 997 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You did better than that.\n"
# 998 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You raised it.$"
# 999 "data/maps/OlivineCity_House1/scripts.pory"

# 1000 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillieProud:
# 1001 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}I knew the whole way.\p"
# 1002 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Every time we met, I knew.\p"
# 1003 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I just wanted to be here when\n"
# 1004 "data/maps/OlivineCity_House1/scripts.pory"
	.string "somebody finally said it out\l"
# 1005 "data/maps/OlivineCity_House1/scripts.pory"
	.string "loud.$"
# 1006 "data/maps/OlivineCity_House1/scripts.pory"

# 1007 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineKnows:
# 1008 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}That light is what\n"
# 1009 "data/maps/OlivineCity_House1/scripts.pory"
	.string "opens the way.\p"
# 1010 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am the only person alive\n"
# 1011 "data/maps/OlivineCity_House1/scripts.pory"
	.string "who knows what it looks like\l"
# 1012 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from the other side.\p"
# 1013 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Thank you for not letting me\n"
# 1014 "data/maps/OlivineCity_House1/scripts.pory"
	.string "do this alone.\p"
# 1015 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am told that is the lesson.$"
# 1016 "data/maps/OlivineCity_House1/scripts.pory"

# 1017 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionWayBack:
# 1018 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}My condition stands.\p"
# 1019 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We go together, and we come\n"
# 1020 "data/maps/OlivineCity_House1/scripts.pory"
	.string "back.$"
# 1021 "data/maps/OlivineCity_House1/scripts.pory"

# 1022 "data/maps/OlivineCity_House1/scripts.pory"
@ The handoff to the altar document. The last box is the one that tells the
# 1023 "data/maps/OlivineCity_House1/scripts.pory"
@ player the game is not taking them anywhere yet.
# 1024 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionHook:
# 1025 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then it is settled.\p"
# 1026 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There is a ship at the\n"
# 1027 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Olivine port, and it is ours\l"
# 1028 "data/maps/OlivineCity_House1/scripts.pory"
	.string "for as long as this takes.\p"
# 1029 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We sail for the altar,\n"
# 1030 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 1031 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You, your partner, and\n"
# 1032 "data/maps/OlivineCity_House1/scripts.pory"
	.string "everyone in this room who can\l"
# 1033 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keep up.\p"
# 1034 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Come to the port when you are\n"
# 1035 "data/maps/OlivineCity_House1/scripts.pory"
	.string "ready. Rest first.\p"
# 1036 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Whatever is waiting at that\n"
# 1037 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar has waited a long time.\p"
# 1038 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It can wait for you to heal.$"
# 1039 "data/maps/OlivineCity_House1/scripts.pory"

# 1040 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicket:
# 1041 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}One more thing.\n"
# 1042 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Take this.$"
# 1043 "data/maps/OlivineCity_House1/scripts.pory"

# 1044 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicketUse:
# 1045 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Show it to the sailor at the\n"
# 1046 "data/maps/OlivineCity_House1/scripts.pory"
	.string "port. He will take you to the\l"
# 1047 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar, and bring you back.$"
# 1048 "data/maps/OlivineCity_House1/scripts.pory"

# 1049 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: state 12 and up, the repeatable reminder of where to go.
# 1050 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerAltar:
# 1051 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The ship is at the\n"
# 1052 "data/maps/OlivineCity_House1/scripts.pory"
	.string "port whenever you are ready,\l"
# 1053 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 1054 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Madame Lusamine went ahead.\n"
# 1055 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Of course she did.$"
# 1056 "data/maps/OlivineCity_House1/scripts.pory"

# 1057 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelAltar:
# 1058 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We leave when you do,\n"
# 1059 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not before.\p"
# 1060 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we come back.\p"
# 1061 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That part is the whole plan.$"
# 1062 "data/maps/OlivineCity_House1/scripts.pory"

# 1063 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: idle lines for state 11, one box each.
# 1064 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLusamine:
# 1065 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I will not pace.\p"
# 1066 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pacing is for people without\n"
# 1067 "data/maps/OlivineCity_House1/scripts.pory"
	.string "instruments.$"
# 1068 "data/maps/OlivineCity_House1/scripts.pory"

# 1069 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLillie:
# 1070 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Take your time with\n"
# 1071 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them.\p"
# 1072 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I mean it - that's not a\n"
# 1073 "data/maps/OlivineCity_House1/scripts.pory"
	.string "polite thing to say, it's the\l"
# 1074 "data/maps/OlivineCity_House1/scripts.pory"
	.string "actual advice.$"
# 1075 "data/maps/OlivineCity_House1/scripts.pory"

# 1076 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleGladion:
# 1077 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}Go and train.\p"
# 1078 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's not an insult, it's\n"
# 1079 "data/maps/OlivineCity_House1/scripts.pory"
	.string "what I'd be doing.$"
# 1080 "data/maps/OlivineCity_House1/scripts.pory"

# 1081 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleKukui:
# 1082 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Six weeks of bad data\n"
# 1083 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and one good afternoon!\p"
# 1084 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Science, {PLAYER}!$"
# 1085 "data/maps/OlivineCity_House1/scripts.pory"
@ Post-game, state >= 16: the family's two days a week in this room
# 1086 "data/maps/OlivineCity_House1/scripts.pory"
@ (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.6).
# 1087 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseLusaminePost:
# 1088 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The Inspector left us the key and a\n"
# 1089 "data/maps/OlivineCity_House1/scripts.pory"
	.string "note asking us not to reorganise\l"
# 1090 "data/maps/OlivineCity_House1/scripts.pory"
	.string "anything.\p"
# 1091 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I have reorganised three things.\p"
# 1092 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Sit down, {PLAYER}. Nobody here is\n"
# 1093 "data/maps/OlivineCity_House1/scripts.pory"
	.string "going anywhere for several hours, which\l"
# 1094 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I understand is what people do.$"
# 1095 "data/maps/OlivineCity_House1/scripts.pory"

# 1096 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseLilliePost:
# 1097 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Two days a week. That's what we agreed\n"
# 1098 "data/maps/OlivineCity_House1/scripts.pory"
	.string "on -- two days, here, no instruments, no\l"
# 1099 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reports.\p"
# 1100 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The first one was terrible. We all sat in\n"
# 1101 "data/maps/OlivineCity_House1/scripts.pory"
	.string "different corners.\p"
# 1102 "data/maps/OlivineCity_House1/scripts.pory"
	.string "This is the fourth one. It's getting\n"
# 1103 "data/maps/OlivineCity_House1/scripts.pory"
	.string "better. It's allowed to take a while.$"
# 1104 "data/maps/OlivineCity_House1/scripts.pory"

# 1105 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseGladionPost:
# 1106 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}I'm not good at this part.\p"
# 1107 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Silvally likes it. Look at him. He's\n"
# 1108 "data/maps/OlivineCity_House1/scripts.pory"
	.string "asleep under the table where Looker\l"
# 1109 "data/maps/OlivineCity_House1/scripts.pory"
	.string "used to put his files.\p"
# 1110 "data/maps/OlivineCity_House1/scripts.pory"
	.string "If he's fine with it, I'm fine with it.\n"
# 1111 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's the system I'm using.$"
