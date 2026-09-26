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
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefingIfCalled
# 131 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefingIfCalled
# 132 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_StageBriefingIfCalled
# 133 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_StageReunionIfCalled
# 134 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_StageRecheck
# 135 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 136 "data/maps/OlivineCity_House1/scripts.pory"

# 137 "data/maps/OlivineCity_House1/scripts.pory"
@ States 4, 6, 8 and 10 are only ready once Looker has telephoned
# 138 "data/maps/OlivineCity_House1/scripts.pory"
@ (FLAG_RIFT_LOOKER_SUMMONS, set by RiftMissions_EventScript_LookerCall). Before
# 139 "data/maps/OlivineCity_House1/scripts.pory"
@ that the house has nothing staged: walking in gets the player nothing but the
# 140 "data/maps/OlivineCity_House1/scripts.pory"
@ waiting line from whichever detective they talk to.
# 141 "data/maps/OlivineCity_House1/scripts.pory"
@ State 2 is NOT gated. Its summons is the call scene in New Bark, that
# 142 "data/maps/OlivineCity_House1/scripts.pory"
@ invitation never expires and never repeats, and gating it would strand a save
# 143 "data/maps/OlivineCity_House1/scripts.pory"
@ made before this flag existed.
# 144 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageBriefingIfCalled::
# 145 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_End
# 146 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_StageBriefing
# 147 "data/maps/OlivineCity_House1/scripts.pory"

# 148 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageReunionIfCalled::
# 149 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_End
# 150 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_StageReunion
# 151 "data/maps/OlivineCity_House1/scripts.pory"

# 152 "data/maps/OlivineCity_House1/scripts.pory"
@ The choreography itself, shared by both briefings. Unchanged since Rift
# 153 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1: only which text BriefingTalk picks differs.
# 154 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageBriefing::
# 155 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 156 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 157 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 158 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 159 "data/maps/OlivineCity_House1/scripts.pory"
	@ Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 160 "data/maps/OlivineCity_House1/scripts.pory"
	@ Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 161 "data/maps/OlivineCity_House1/scripts.pory"
	@ The two paths share no tile on any step, so they can walk together.
# 162 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 163 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 164 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 165 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 166 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 167 "data/maps/OlivineCity_House1/scripts.pory"
	@ Back home: the reverse paths, also disjoint step by step.
# 168 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerReturn
# 169 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelReturn
# 170 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 171 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 172 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 173 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 174 "data/maps/OlivineCity_House1/scripts.pory"

# 175 "data/maps/OlivineCity_House1/scripts.pory"
@ The reunion cutscene. Reached from the frame trigger at state 10 and from the
# 176 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker/Anabel object scripts at state 10. It plays ONCE: it always ends in
# 177 "data/maps/OlivineCity_House1/scripts.pory"
@ state 11 or 12, and neither re-enters it. That is the Rift Mission 4 lesson
# 178 "data/maps/OlivineCity_House1/scripts.pory"
@ applied before it costs anything (M4 doc section 9: the long scene replaying
# 179 "data/maps/OlivineCity_House1/scripts.pory"
@ on every attempt is tiring) - here the long version plays once and "did your
# 180 "data/maps/OlivineCity_House1/scripts.pory"
@ partner evolve yet?" is a short branch.
# 181 "data/maps/OlivineCity_House1/scripts.pory"
@
# 182 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker and Anabel reuse the SAME movements as the four briefings:
# 183 "data/maps/OlivineCity_House1/scripts.pory"
@   Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 184 "data/maps/OlivineCity_House1/scripts.pory"
@   Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 185 "data/maps/OlivineCity_House1/scripts.pory"
@ Both paths are free of all six new objects and share no tile on any step.
# 186 "data/maps/OlivineCity_House1/scripts.pory"
@ Nobody walks back at the end: the reunion is still happening when the box
# 187 "data/maps/OlivineCity_House1/scripts.pory"
@ closes, and the next map load returns them to their template tiles.
# 188 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageReunion::
# 189 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 190 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 191 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 192 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 193 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 194 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 195 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 196 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 197 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 198 "data/maps/OlivineCity_House1/scripts.pory"

# 199 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11 arrival: no choreography beyond Looker stepping down to the player,
# 200 "data/maps/OlivineCity_House1/scripts.pory"
@ and no recap of the meeting. He asks the one question that is still open.
# 201 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageRecheck::
# 202 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 203 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 204 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 205 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 206 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 207 "data/maps/OlivineCity_House1/scripts.pory"

# 208 "data/maps/OlivineCity_House1/scripts.pory"
@ Beats, in the order design section 7 fixes them:
# 209 "data/maps/OlivineCity_House1/scripts.pory"
@   1. Looker closes the New Bark report and names the room.
# 210 "data/maps/OlivineCity_House1/scripts.pory"
@   2. Kukui: Anabel's bearing plus Elm's six weeks became a PLACE. He is
# 211 "data/maps/OlivineCity_House1/scripts.pory"
@      already facing west (into the room), so he needs no turnobject.
# 212 "data/maps/OlivineCity_House1/scripts.pory"
@   3. Lusamine says why she asked for this. Lillie (3,6) and Gladion (3,7) are
# 213 "data/maps/OlivineCity_House1/scripts.pory"
@      in the same column, one tile apart, so they can look AT EACH OTHER:
# 214 "data/maps/OlivineCity_House1/scripts.pory"
@      y grows downward, so Lillie faces DIR_SOUTH and Gladion DIR_NORTH. Then
# 215 "data/maps/OlivineCity_House1/scripts.pory"
@      both go back to DIR_EAST, facing the room and their mother.
# 216 "data/maps/OlivineCity_House1/scripts.pory"
@      The family conversation opens here and is NOT resolved here (design 7).
# 217 "data/maps/OlivineCity_House1/scripts.pory"
@   4. Lusamine states she intends to cross. ANABEL sets the condition, as a
# 218 "data/maps/OlivineCity_House1/scripts.pory"
@      Faller - and it is an ARGUMENT, not news: she told them on the beach
# 219 "data/maps/OlivineCity_House1/scripts.pory"
@      in Cherrygrove and the rest of it in New Bark (design 3.1 / 6.3 /
# 220 "data/maps/OlivineCity_House1/scripts.pory"
@      6.4). ONE box of recap, no more. Lusamine is east of her
# 221 "data/maps/OlivineCity_House1/scripts.pory"
@      on both paths in, so she turns DIR_EAST to face her, then back.
# 222 "data/maps/OlivineCity_House1/scripts.pory"
@   5-6. Anabel names what the passage needs; Looker checks -> ReunionCheck.
# 223 "data/maps/OlivineCity_House1/scripts.pory"
@
# 224 "data/maps/OlivineCity_House1/scripts.pory"
@ NO direction here is derived from the player's live position: every
# 225 "data/maps/OlivineCity_House1/scripts.pory"
@ turnobject aims at another actor on a fixed tile. That is what makes the
# 226 "data/maps/OlivineCity_House1/scripts.pory"
@ block correct both from the frame trigger (player at (4,8)) and from an
# 227 "data/maps/OlivineCity_House1/scripts.pory"
@ object script (player anywhere in the room).
# 228 "data/maps/OlivineCity_House1/scripts.pory"
@ closemessage before EVERY turnobject: without it the turn happens behind the
# 229 "data/maps/OlivineCity_House1/scripts.pory"
@ open text box.
# 230 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionScene::
# 231 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_RIFT_LOOKER_SUMMONS          @ the invitation has been answered
# 232 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionOpen, MSGBOX_DEFAULT
# 233 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 234 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionKukui, MSGBOX_DEFAULT
# 235 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 236 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineCalled, MSGBOX_DEFAULT
# 237 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 238 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_SOUTH
# 239 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_NORTH
# 240 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillie, MSGBOX_DEFAULT
# 241 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 242 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladion, MSGBOX_DEFAULT
# 243 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 244 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_EAST
# 245 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_GLADION, DIR_EAST
# 246 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCross, MSGBOX_DEFAULT
# 247 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 248 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_EAST
# 249 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCondition, MSGBOX_DEFAULT
# 250 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 251 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_SOUTH
# 252 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 253 "data/maps/OlivineCity_House1/scripts.pory"

# 254 "data/maps/OlivineCity_House1/scripts.pory"
@ The one gate of the arc (design sections 7 and 8): Solgaleo OR Lunala, in the
# 255 "data/maps/OlivineCity_House1/scripts.pory"
@ PARTY. checkspecies compiles to Scrcmd_checkspecies (src/scrcmd.c), which
# 256 "data/maps/OlivineCity_House1/scripts.pory"
@ calls CheckPartyHasSpecies (src/field_specials.c): it walks gPlayerParty only
# 257 "data/maps/OlivineCity_House1/scripts.pory"
@ and returns into VAR_RESULT. Consequences, all of them wanted by the design:
# 258 "data/maps/OlivineCity_House1/scripts.pory"
@   - one in the PC does not count; a Pokedex entry does not count;
# 259 "data/maps/OlivineCity_House1/scripts.pory"
@   - Cosmog and Cosmoem do not pass, and no evolution happens here;
# 260 "data/maps/OlivineCity_House1/scripts.pory"
@   - EITHER species satisfies it, and having both is never required.
# 261 "data/maps/OlivineCity_House1/scripts.pory"
@ Two checks, never one, and never a check for the family.
# 262 "data/maps/OlivineCity_House1/scripts.pory"
@ Reachable from the long scene, from the state-11 trigger and from the Looker
# 263 "data/maps/OlivineCity_House1/scripts.pory"
@ and Anabel object scripts, so it must read as a standalone question.
# 264 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionCheck::
# 265 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAsk, MSGBOX_DEFAULT
# 266 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 267 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_SOLGALEO
# 268 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
# 269 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_LUNALA
# 270 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionConfirmed
# 271 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionNotYet
# 272 "data/maps/OlivineCity_House1/scripts.pory"

# 273 "data/maps/OlivineCity_House1/scripts.pory"
@ Not yet. Nothing is spent: no mission is replayed, nobody leaves the room,
# 274 "data/maps/OlivineCity_House1/scripts.pory"
@ and the only thing that changes is 10 -> 11, which is what stops the long
# 275 "data/maps/OlivineCity_House1/scripts.pory"
@ cutscene from playing again. From 11 this whole block is four boxes.
# 276 "data/maps/OlivineCity_House1/scripts.pory"
@ The setvar is idempotent: running it again in state 11 rewrites 11, and
# 277 "data/maps/OlivineCity_House1/scripts.pory"
@ nothing ever goes back from 11 to 10.
# 278 "data/maps/OlivineCity_House1/scripts.pory"
@ releaseall (not release) because this script is reached from a lockall
# 279 "data/maps/OlivineCity_House1/scripts.pory"
@ context AND from a lock context: releaseall is correct in both, release would
# 280 "data/maps/OlivineCity_House1/scripts.pory"
@ leave the other objects frozen after the cutscene.
# 281 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionNotYet::
# 282 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionNotYet, MSGBOX_DEFAULT
# 283 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 284 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 285 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 286 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 287 "data/maps/OlivineCity_House1/scripts.pory"

# 288 "data/maps/OlivineCity_House1/scripts.pory"
@ Confirmed. The room recognises the Pokemon that came out of the egg Gladion
# 289 "data/maps/OlivineCity_House1/scripts.pory"
@ handed the player in Violet, and then Looker gives the hook to the altar.
# 290 "data/maps/OlivineCity_House1/scripts.pory"
@ Design section 7 item 7 (releasing the ship) and everything at the altar
# 291 "data/maps/OlivineCity_House1/scripts.pory"
@ belong to the NEXT document: this event ends on the flag.
# 292 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionConfirmed::
# 293 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionSeeIt, MSGBOX_DEFAULT
# 294 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 295 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladionEgg, MSGBOX_DEFAULT
# 296 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 297 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillieProud, MSGBOX_DEFAULT
# 298 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 299 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineKnows, MSGBOX_DEFAULT
# 300 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 301 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionWayBack, MSGBOX_DEFAULT
# 302 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 303 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionHook, MSGBOX_DEFAULT
# 304 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 305 "data/maps/OlivineCity_House1/scripts.pory"
	@ The ferry pass: the port sailor offers the altar route only to whoever
# 306 "data/maps/OlivineCity_House1/scripts.pory"
	@ carries it (OlivineCity_PortInside). Key item, so the bag cannot be full.
# 307 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicket, MSGBOX_DEFAULT
# 308 "data/maps/OlivineCity_House1/scripts.pory"
	giveitem ITEM_SUN_MOON_TICKET
# 309 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicketUse, MSGBOX_DEFAULT
# 310 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 311 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreen FADE_TO_BLACK
# 312 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED   @ handoff; NEVER cleared
# 313 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 12           @ invariant: flag and var together
# 314 "data/maps/OlivineCity_House1/scripts.pory"
	@ Reload in place: ON_TRANSITION hides the six visitors (they went ahead to
# 315 "data/maps/OlivineCity_House1/scripts.pory"
	@ the port), Looker and Anabel snap back to (4,5)/(7,5) from their
# 316 "data/maps/OlivineCity_House1/scripts.pory"
	@ templates, and the follower comes back (undoes hidefollower). Without
# 317 "data/maps/OlivineCity_House1/scripts.pory"
	@ this, all of that would happen in pieces as the camera moved.
# 318 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7), not (4,8): do not respawn the player on the room's only warp tile.
# 319 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7) is guaranteed free, because by state 12 the six are already hidden.
# 320 "data/maps/OlivineCity_House1/scripts.pory"
	@ The frame trigger fires again after this load with VAR_TEMP_1 zeroed, but
# 321 "data/maps/OlivineCity_House1/scripts.pory"
	@ dies twice over: the player is not at (4,8) AND state 12 matches no
# 322 "data/maps/OlivineCity_House1/scripts.pory"
	@ goto_if_eq in its list.
# 323 "data/maps/OlivineCity_House1/scripts.pory"
	warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7
# 324 "data/maps/OlivineCity_House1/scripts.pory"
	waitstate
# 325 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 326 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 327 "data/maps/OlivineCity_House1/scripts.pory"

# 328 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_End::
# 329 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 330 "data/maps/OlivineCity_House1/scripts.pory"

# 331 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerApproach:
# 332 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 333 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 334 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 335 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 336 "data/maps/OlivineCity_House1/scripts.pory"

# 337 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelApproach:
# 338 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 339 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 340 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 341 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 342 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 343 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 344 "data/maps/OlivineCity_House1/scripts.pory"

# 345 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerReturn:
# 346 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 347 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 348 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 349 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 350 "data/maps/OlivineCity_House1/scripts.pory"

# 351 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelReturn:
# 352 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 353 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 354 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 355 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 356 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 357 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 358 "data/maps/OlivineCity_House1/scripts.pory"

# 359 "data/maps/OlivineCity_House1/scripts.pory"
@ Shared by the arrival scene and by both object scripts in states 2, 4, 6
# 360 "data/maps/OlivineCity_House1/scripts.pory"
@ and 8, so a briefing can never be skipped by entering from an odd tile. It is
# 361 "data/maps/OlivineCity_House1/scripts.pory"
@ the ONE place that moves flag and var, and it moves them together.
# 362 "data/maps/OlivineCity_House1/scripts.pory"
@ Invariants:
# 363 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_BLACKTHORN  set <=> VAR_RIFT_MISSIONS_STATE == 3
# 364 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_MAHOGANY    set <=> VAR_RIFT_MISSIONS_STATE == 5
# 365 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_CHERRYGROVE set <=> VAR_RIFT_MISSIONS_STATE == 7
# 366 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_NEWBARK     set <=> VAR_RIFT_MISSIONS_STATE == 9
# 367 "data/maps/OlivineCity_House1/scripts.pory"
@ The four are mutually exclusive because the var holds one value.
# 368 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10 is the END of the chain: it opens no mission, it means "four done,
# 369 "data/maps/OlivineCity_House1/scripts.pory"
@ the Olivine reunion pending" (design section 7).
# 370 "data/maps/OlivineCity_House1/scripts.pory"
@ A goto inside a script reached by call is safe: call pushes the return
# 371 "data/maps/OlivineCity_House1/scripts.pory"
@ address and return pops it, however many gotos happened in between.
# 372 "data/maps/OlivineCity_House1/scripts.pory"
@ Highest state first, so the block reads newest mission to oldest.
# 373 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalk::
# 374 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_RIFT_LOOKER_SUMMONS          @ the invitation has been answered
# 375 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_BriefingTalkM4
# 376 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_BriefingTalkM3
# 377 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_BriefingTalkM2
# 378 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through to M1 (state 2)
# 379 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM1::
# 380 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingWelcome, MSGBOX_DEFAULT
# 381 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingAnabel, MSGBOX_DEFAULT
# 382 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingWormholes, MSGBOX_DEFAULT
# 383 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingBlackthorn, MSGBOX_DEFAULT
# 384 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingRequest, MSGBOX_DEFAULT
# 385 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 386 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
# 387 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 3
# 388 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 389 "data/maps/OlivineCity_House1/scripts.pory"

# 390 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM2::
# 391 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Welcome, MSGBOX_DEFAULT
# 392 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 393 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Link, MSGBOX_DEFAULT
# 394 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 395 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Town, MSGBOX_DEFAULT
# 396 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 397 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Meet, MSGBOX_DEFAULT
# 398 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 399 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
# 400 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 5
# 401 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 402 "data/maps/OlivineCity_House1/scripts.pory"

# 403 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM3::
# 404 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3, MSGBOX_DEFAULT
# 405 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 406 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
# 407 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 7
# 408 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 409 "data/maps/OlivineCity_House1/scripts.pory"

# 410 "data/maps/OlivineCity_House1/scripts.pory"
@ TRES msgbox, nao um. msgbox expande o texto inteiro em gStringVar4, que tem
# 411 "data/maps/OlivineCity_House1/scripts.pory"
@ 1000 bytes (EWRAM_DATA u8 gStringVar4[0x3E8], src/string_util.c). Este
# 412 "data/maps/OlivineCity_House1/scripts.pory"
@ briefing tem ~2000 e travava o jogo ao chegar em Olivine vindo de
# 413 "data/maps/OlivineCity_House1/scripts.pory"
@ Cherrygrove: StringExpandPlaceholders nao checa tamanho, entao ele escrevia
# 414 "data/maps/OlivineCity_House1/scripts.pory"
@ 1000 bytes por cima da EWRAM seguinte. Cada parte fica abaixo de ~800.
# 415 "data/maps/OlivineCity_House1/scripts.pory"
@ Sem closemessage entre elas: sFieldMessageBoxVisible continua TRUE, a caixa
# 416 "data/maps/OlivineCity_House1/scripts.pory"
@ nao desce nem sobe de novo, e a cena roda como uma fala so.
# 417 "data/maps/OlivineCity_House1/scripts.pory"
@ Cada parte PRECISA comecar com o seu {SPEAKER ...}: TrySetSpeakerFromMessage
# 418 "data/maps/OlivineCity_House1/scripts.pory"
@ le so o inicio de cada mensagem, e uma parte sem o codigo perderia a
# 419 "data/maps/OlivineCity_House1/scripts.pory"
@ plaquinha no meio da conversa.
# 420 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM4::
# 421 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4, MSGBOX_DEFAULT
# 422 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Faller, MSGBOX_DEFAULT
# 423 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4NewBark, MSGBOX_DEFAULT
# 424 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 425 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_NEWBARK
# 426 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 9
# 427 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 428 "data/maps/OlivineCity_House1/scripts.pory"

# 429 "data/maps/OlivineCity_House1/scripts.pory"
@ Branch order matters: 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, then >= 12. NEVER
# 430 "data/maps/OlivineCity_House1/scripts.pory"
@ leave a "goto_if_ge VAR_RIFT_MISSIONS_STATE, 4", ", 6", ", 8" or ", 10"
# 431 "data/maps/OlivineCity_House1/scripts.pory"
@ here - any one of them would swallow the states above it. This has now
# 432 "data/maps/OlivineCity_House1/scripts.pory"
@ happened THREE times: Mission 3 had to delete a "goto_if_ge ..., 6" left
# 433 "data/maps/OlivineCity_House1/scripts.pory"
@ behind by Mission 2, Mission 4 had to move a "goto_if_ge ..., 8" left behind
# 434 "data/maps/OlivineCity_House1/scripts.pory"
@ by Mission 3, and the pre-Necrozma reunion had to split the
# 435 "data/maps/OlivineCity_House1/scripts.pory"
@ "goto_if_ge ..., 10" Mission 4 left behind, which would have replayed the
# 436 "data/maps/OlivineCity_House1/scripts.pory"
@ whole cutscene at state 11 and kept saying reunion lines at state 12.
# 437 "data/maps/OlivineCity_House1/scripts.pory"
@ Fourth warning, same mistake: a NEW state enters as goto_if_eq, and only the
# 438 "data/maps/OlivineCity_House1/scripts.pory"
@ LAST line of the list may be a goto_if_ge.
# 439 "data/maps/OlivineCity_House1/scripts.pory"
@ States 0-1 fall through to the holiday line.
# 440 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Looker::
# 441 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 442 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 443 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_LookerBrief
# 444 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_LookerGoAhead
# 445 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_LookerBriefIfCalled
# 446 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_LookerGoAheadM2
# 447 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerBriefIfCalled
# 448 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_LookerGoAheadM3
# 449 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_LookerBriefIfCalled
# 450 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_LookerGoAheadM4
# 451 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerReunionIfCalled
# 452 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_LookerRecheck
# 453 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_LookerAltar
# 454 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerHoliday, MSGBOX_DEFAULT
# 455 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 456 "data/maps/OlivineCity_House1/scripts.pory"

# 457 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerBrief::
# 458 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 459 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 460 "data/maps/OlivineCity_House1/scripts.pory"

# 461 "data/maps/OlivineCity_House1/scripts.pory"
@ Waiting for the summons: no briefing, no "go ahead", and nothing about the next
# 462 "data/maps/OlivineCity_House1/scripts.pory"
@ town. He says the one true thing - the reports are not finished - and promises
# 463 "data/maps/OlivineCity_House1/scripts.pory"
@ the telephone call that is the only way forward.
# 464 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerBriefIfCalled::
# 465 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_LookerWaitCall
# 466 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_LookerBrief
# 467 "data/maps/OlivineCity_House1/scripts.pory"

# 468 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerWaitCall::
# 469 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerWaitCallM3
# 470 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_WaitForMahoganyCall, MSGBOX_DEFAULT
# 471 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 472 "data/maps/OlivineCity_House1/scripts.pory"

# 473 "data/maps/OlivineCity_House1/scripts.pory"
@ After Mahogany the wait is not idle: Anabel is matching Lillie's pages to her
# 474 "data/maps/OlivineCity_House1/scripts.pory"
@ own recordings, which is the task the street handed them.
# 475 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerWaitCallM3::
# 476 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_WaitForCherrygroveCall, MSGBOX_DEFAULT
# 477 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 478 "data/maps/OlivineCity_House1/scripts.pory"

# 479 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerReunionIfCalled::
# 480 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_LookerWaitCall
# 481 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_LookerReunion
# 482 "data/maps/OlivineCity_House1/scripts.pory"

# 483 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAhead::
# 484 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAhead, MSGBOX_DEFAULT
# 485 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 486 "data/maps/OlivineCity_House1/scripts.pory"

# 487 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM2::
# 488 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM2, MSGBOX_DEFAULT
# 489 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 490 "data/maps/OlivineCity_House1/scripts.pory"

# 491 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM3::
# 492 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM3, MSGBOX_DEFAULT
# 493 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 494 "data/maps/OlivineCity_House1/scripts.pory"

# 495 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM4::
# 496 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM4, MSGBOX_DEFAULT
# 497 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 498 "data/maps/OlivineCity_House1/scripts.pory"

# 499 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: the alternative way into the reunion, for a player who walks past
# 500 "data/maps/OlivineCity_House1/scripts.pory"
@ the frame trigger's tile check. ReunionScene has no applymovement at all -
# 501 "data/maps/OlivineCity_House1/scripts.pory"
@ only msgbox and turnobject on actors with fixed tiles, and none of the six
# 502 "data/maps/OlivineCity_House1/scripts.pory"
@ visitors wanders (all of them are MOVEMENT_TYPE_FACE_*) - so it plays
# 503 "data/maps/OlivineCity_House1/scripts.pory"
@ identically under lock. All that is missing is Looker's step down.
# 504 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerReunion::
# 505 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 506 "data/maps/OlivineCity_House1/scripts.pory"

# 507 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11: only the open question, never the cutscene again.
# 508 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerRecheck::
# 509 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 510 "data/maps/OlivineCity_House1/scripts.pory"

# 511 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: last stop of this document. The ship, the voyage and the altar
# 512 "data/maps/OlivineCity_House1/scripts.pory"
@ belong to the next one, which starts from FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED
# 513 "data/maps/OlivineCity_House1/scripts.pory"
@ and VAR_RIFT_MISSIONS_STATE >= 12. Repeatable on purpose: a player who saved
# 514 "data/maps/OlivineCity_House1/scripts.pory"
@ and came back must be able to ask where to go.
# 515 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerAltar::
# 516 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerAltar, MSGBOX_DEFAULT
# 517 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 518 "data/maps/OlivineCity_House1/scripts.pory"

# 519 "data/maps/OlivineCity_House1/scripts.pory"
@ Same branch order as Looker, and the same warning about goto_if_ge.
# 520 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Anabel::
# 521 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 522 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 523 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_AnabelBrief
# 524 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_AnabelGoAhead
# 525 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_AnabelBriefIfCalled
# 526 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_AnabelGoAheadM2
# 527 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_AnabelBriefIfCalled
# 528 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_AnabelGoAheadM3
# 529 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_AnabelBriefIfCalled
# 530 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_AnabelGoAheadM4
# 531 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_AnabelReunionIfCalled
# 532 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_AnabelRecheck
# 533 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_AnabelAltar
# 534 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelHoliday, MSGBOX_DEFAULT
# 535 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 536 "data/maps/OlivineCity_House1/scripts.pory"

# 537 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelBrief::
# 538 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 539 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 540 "data/maps/OlivineCity_House1/scripts.pory"

# 541 "data/maps/OlivineCity_House1/scripts.pory"
@ Her own waiting line: the plaque follows the message, so Looker's text cannot
# 542 "data/maps/OlivineCity_House1/scripts.pory"
@ be reused in her mouth.
# 543 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelBriefIfCalled::
# 544 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_AnabelWaitCall
# 545 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_AnabelBrief
# 546 "data/maps/OlivineCity_House1/scripts.pory"

# 547 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelWaitCall::
# 548 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelWaitForCall, MSGBOX_DEFAULT
# 549 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 550 "data/maps/OlivineCity_House1/scripts.pory"

# 551 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelReunionIfCalled::
# 552 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_AnabelWaitCall
# 553 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_AnabelReunion
# 554 "data/maps/OlivineCity_House1/scripts.pory"

# 555 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAhead::
# 556 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAhead, MSGBOX_DEFAULT
# 557 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 558 "data/maps/OlivineCity_House1/scripts.pory"

# 559 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM2::
# 560 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM2, MSGBOX_DEFAULT
# 561 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 562 "data/maps/OlivineCity_House1/scripts.pory"

# 563 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM3::
# 564 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM3, MSGBOX_DEFAULT
# 565 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 566 "data/maps/OlivineCity_House1/scripts.pory"

# 567 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM4::
# 568 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM4, MSGBOX_DEFAULT
# 569 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 570 "data/maps/OlivineCity_House1/scripts.pory"

# 571 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: Anabel sells Beast Balls from state 4 on (design section 5),
# 572 "data/maps/OlivineCity_House1/scripts.pory"
@ still pending since Rift Mission 1. This event passes through her script
# 573 "data/maps/OlivineCity_House1/scripts.pory"
@ without resolving it.
# 574 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: same entry into the reunion as Looker's, see the note there.
# 575 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelReunion::
# 576 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 577 "data/maps/OlivineCity_House1/scripts.pory"

# 578 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelRecheck::
# 579 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionCheck
# 580 "data/maps/OlivineCity_House1/scripts.pory"

# 581 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: last stop of this document, same as LookerAltar.
# 582 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelAltar::
# 583 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelAltar, MSGBOX_DEFAULT
# 584 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 585 "data/maps/OlivineCity_House1/scripts.pory"

# 586 "data/maps/OlivineCity_House1/scripts.pory"
@ The four visitors. They exist to be talked to in state 11, the only state in
# 587 "data/maps/OlivineCity_House1/scripts.pory"
@ which the player walks the room with everyone present - in state 12 they are
# 588 "data/maps/OlivineCity_House1/scripts.pory"
@ not here to be talked to, and in state 10 the cutscene runs on arrival. So
# 589 "data/maps/OlivineCity_House1/scripts.pory"
@ they need no branch on the var: one box each.
# 590 "data/maps/OlivineCity_House1/scripts.pory"
@ Ninetales and Silvally have "script": "NULL" (design 3.2, skill
# 591 "data/maps/OlivineCity_House1/scripts.pory"
@ parceiro-pokemon-de-npc): they are their owners' partners out of the ball,
# 592 "data/maps/OlivineCity_House1/scripts.pory"
@ share FLAG_TEMP_1 with them, and come and go together.
# 593 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: placeholder dialogue, one box each.
# 594 "data/maps/OlivineCity_House1/scripts.pory"
@ The three who come back. There is NO battle anywhere in this room in the
# 595 "data/maps/OlivineCity_House1/scripts.pory"
@ post-game: this is the place where they are not working.
# 596 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLusamine::
# 597 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 598 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 599 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseLusaminePost
# 600 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLusamine, MSGBOX_DEFAULT
# 601 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 602 "data/maps/OlivineCity_House1/scripts.pory"

# 603 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseLusaminePost::
# 604 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseLusaminePost, MSGBOX_DEFAULT
# 605 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 606 "data/maps/OlivineCity_House1/scripts.pory"

# 607 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLillie::
# 608 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 609 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 610 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseLilliePost
# 611 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLillie, MSGBOX_DEFAULT
# 612 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 613 "data/maps/OlivineCity_House1/scripts.pory"

# 614 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseLilliePost::
# 615 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseLilliePost, MSGBOX_DEFAULT
# 616 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 617 "data/maps/OlivineCity_House1/scripts.pory"

# 618 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionGladion::
# 619 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 620 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 621 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseGladionPost
# 622 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleGladion, MSGBOX_DEFAULT
# 623 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 624 "data/maps/OlivineCity_House1/scripts.pory"

# 625 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseGladionPost::
# 626 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseGladionPost, MSGBOX_DEFAULT
# 627 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 628 "data/maps/OlivineCity_House1/scripts.pory"

# 629 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionKukui::
# 630 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 631 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 632 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleKukui, MSGBOX_DEFAULT
# 633 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 634 "data/maps/OlivineCity_House1/scripts.pory"

# 635 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReleaseEnd::
# 636 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 637 "data/maps/OlivineCity_House1/scripts.pory"
	release
# 638 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 639 "data/maps/OlivineCity_House1/scripts.pory"

# 640 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1 briefing (script revision V2, 25/09/2026). FIVE texts and not one,
# 641 "data/maps/OlivineCity_House1/scripts.pory"
@ because each block has exactly one speaker and the plaque has to change with
# 642 "data/maps/OlivineCity_House1/scripts.pory"
@ it; they are played as consecutive msgbox with no closemessage between them,
# 643 "data/maps/OlivineCity_House1/scripts.pory"
@ so the box never drops and the scene reads as one conversation. Each part
# 644 "data/maps/OlivineCity_House1/scripts.pory"
@ MUST begin with its own {SPEAKER ...}: TrySetSpeakerFromMessage only reads
# 645 "data/maps/OlivineCity_House1/scripts.pory"
@ the start of each message.
# 646 "data/maps/OlivineCity_House1/scripts.pory"
@ It names Clair and the unfamiliar Pokemon in her street and nothing else:
# 647 "data/maps/OlivineCity_House1/scripts.pory"
@ Gladion, the two Ultra Beasts and the identity of the creature are the
# 648 "data/maps/OlivineCity_House1/scripts.pory"
@ surprises of the scene in Blackthorn, so they are never mentioned here. And
# 649 "data/maps/OlivineCity_House1/scripts.pory"
@ nobody names the creature from a description over the telephone.
# 650 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingWelcome:
# 651 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}!\n"
# 652 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Thank you for coming.\p"
# 653 "data/maps/OlivineCity_House1/scripts.pory"
	.string "This is Anabel. She's in\n"
# 654 "data/maps/OlivineCity_House1/scripts.pory"
	.string "charge of our investigation.$"
# 655 "data/maps/OlivineCity_House1/scripts.pory"

# 656 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingAnabel:
# 657 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We've been tracking\n"
# 658 "data/maps/OlivineCity_House1/scripts.pory"
	.string "distortions in Johto.\p"
# 659 "data/maps/OlivineCity_House1/scripts.pory"
	.string "They resemble the Ultra\n"
# 660 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Wormholes we encountered in\l"
# 661 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Alola.$"
# 662 "data/maps/OlivineCity_House1/scripts.pory"

# 663 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingWormholes:
# 664 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Passages to other\n"
# 665 "data/maps/OlivineCity_House1/scripts.pory"
	.string "worlds.\p"
# 666 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Sometimes Pokémon come\n"
# 667 "data/maps/OlivineCity_House1/scripts.pory"
	.string "through them.\p"
# 668 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We call those Pokémon Ultra\n"
# 669 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Beasts.\p"
# 670 "data/maps/OlivineCity_House1/scripts.pory"
	.string "They can be dangerous when\n"
# 671 "data/maps/OlivineCity_House1/scripts.pory"
	.string "displaced.$"
# 672 "data/maps/OlivineCity_House1/scripts.pory"

# 673 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingBlackthorn:
# 674 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Clair called from\n"
# 675 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn.\p"
# 676 "data/maps/OlivineCity_House1/scripts.pory"
	.string "An unfamiliar Pokémon is in\n"
# 677 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the street.\p"
# 678 "data/maps/OlivineCity_House1/scripts.pory"
	.string "She's keeping it away from the\n"
# 679 "data/maps/OlivineCity_House1/scripts.pory"
	.string "houses, but the readings are\l"
# 680 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rising.$"
# 681 "data/maps/OlivineCity_House1/scripts.pory"

# 682 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingRequest:
# 683 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We need your help\n"
# 684 "data/maps/OlivineCity_House1/scripts.pory"
	.string "protecting the town.\p"
# 685 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And, if we can, the Pokémon\n"
# 686 "data/maps/OlivineCity_House1/scripts.pory"
	.string "too.\p"
# 687 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Meet us by the Pokémon\n"
# 688 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center.\p"
# 689 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bring a team ready for a\n"
# 690 "data/maps/OlivineCity_House1/scripts.pory"
	.string "difficult battle.$"
# 691 "data/maps/OlivineCity_House1/scripts.pory"

# 692 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Blackthorn hook names no place on purpose ("the moment
# 693 "data/maps/OlivineCity_House1/scripts.pory"
@ something opens, you will be the first to know"). This briefing is that
# 694 "data/maps/OlivineCity_House1/scripts.pory"
@ moment: Mahogany is news to the player here.
# 695 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 2 briefing: final text (22/09/2026), continuity updated for script
# 696 "data/maps/OlivineCity_House1/scripts.pory"
@ revision V2 (25/09/2026). It names Pryce's call and the blackout and nothing
# 697 "data/maps/OlivineCity_House1/scripts.pory"
@ else: Lillie and the evacuation (Pryce's own line) are what the player finds
# 698 "data/maps/OlivineCity_House1/scripts.pory"
@ in Mahogany, so they are never mentioned here.
# 699 "data/maps/OlivineCity_House1/scripts.pory"
@ What V2 changed: Necrozma is no longer a secret - Gladion named it in
# 700 "data/maps/OlivineCity_House1/scripts.pory"
@ Blackthorn - so Anabel calls it by name, and the thing she is looking for is
# 701 "data/maps/OlivineCity_House1/scripts.pory"
@ already stated: the beasts stayed tied to the rift, and the link is what has
# 702 "data/maps/OlivineCity_House1/scripts.pory"
@ to be cut. Mahogany's barrier and Lillie's test answer a problem the player
# 703 "data/maps/OlivineCity_House1/scripts.pory"
@ has already watched happen.
# 704 "data/maps/OlivineCity_House1/scripts.pory"
@ V3: this briefing starts from Blackthorn, not from a fresh mystery. Gladion
# 705 "data/maps/OlivineCity_House1/scripts.pory"
@ named Necrozma there, so nobody is coy about it here; what the group does NOT
# 706 "data/maps/OlivineCity_House1/scripts.pory"
@ have is any record of that creature collecting Ultra Beasts, and that gap is
# 707 "data/maps/OlivineCity_House1/scripts.pory"
@ the reason they go. One speaker per box, and no hour of the day anywhere:
# 708 "data/maps/OlivineCity_House1/scripts.pory"
@ the blackout is lamps and machines, not darkness.
# 709 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Welcome:
# 710 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Our holiday\n"
# 711 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reading has finally proved\l"
# 712 "data/maps/OlivineCity_House1/scripts.pory"
	.string "useful.\p"
# 713 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We've compared Gladion's\n"
# 714 "data/maps/OlivineCity_House1/scripts.pory"
	.string "account with the Alola records.\p"
# 715 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Necrozma absorbs light.\p"
# 716 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We found nothing about it\n"
# 717 "data/maps/OlivineCity_House1/scripts.pory"
	.string "taking Ultra Beasts.$"
# 718 "data/maps/OlivineCity_House1/scripts.pory"

# 719 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Link:
# 720 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The rift kept them\n"
# 721 "data/maps/OlivineCity_House1/scripts.pory"
	.string "connected in Blackthorn.\p"
# 722 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We need a way to cut that\n"
# 723 "data/maps/OlivineCity_House1/scripts.pory"
	.string "connection.$"
# 724 "data/maps/OlivineCity_House1/scripts.pory"

# 725 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Town:
# 726 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The power is out in\n"
# 727 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mahogany.\p"
# 728 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Two Pokémon have been\n"
# 729 "data/maps/OlivineCity_House1/scripts.pory"
	.string "appearing in the street.\p"
# 730 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pryce is sheltering the\n"
# 731 "data/maps/OlivineCity_House1/scripts.pory"
	.string "residents in his Gym.$"
# 732 "data/maps/OlivineCity_House1/scripts.pory"

# 733 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Meet:
# 734 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The readings match\n"
# 735 "data/maps/OlivineCity_House1/scripts.pory"
	.string "another rupture.\p"
# 736 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We haven't confirmed Necrozma\n"
# 737 "data/maps/OlivineCity_House1/scripts.pory"
	.string "there yet.\p"
# 738 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Meet us by the Pokémon Center.$"
# 739 "data/maps/OlivineCity_House1/scripts.pory"

# 740 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Mahogany hook names no place on purpose (design section 6,
# 741 "data/maps/OlivineCity_House1/scripts.pory"
@ "gancho sem destino"). This briefing is where Cherrygrove is revealed.
# 742 "data/maps/OlivineCity_House1/scripts.pory"
@ V21: the call came from KUKUI, not from a Gym Leader - Cherrygrove has no
# 743 "data/maps/OlivineCity_House1/scripts.pory"
@ Gym, and the author asked for the Professor to be the one who raised the
# 744 "data/maps/OlivineCity_House1/scripts.pory"
@ alarm. The scene in the house is also where Looker and Anabel decide,
# 745 "data/maps/OlivineCity_House1/scripts.pory"
@ out loud and wrongly, that he is a civilian who needs collecting: that
# 746 "data/maps/OlivineCity_House1/scripts.pory"
@ misjudgement is what the beach pays off. The Ultra Beasts are never named
# 747 "data/maps/OlivineCity_House1/scripts.pory"
@ here, and neither is the creature - those belong to the shore.
# 748 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3:
# 749 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Come in, come\n"
# 750 "data/maps/OlivineCity_House1/scripts.pory"
	.string "in. It has opened again.\p"
# 751 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove City.\p"
# 752 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Two signatures.\p"
# 753 "data/maps/OlivineCity_House1/scripts.pory"
	.string "One of them will not hold\n"
# 754 "data/maps/OlivineCity_House1/scripts.pory"
	.string "still.\p"
# 755 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}And here is the part I\n"
# 756 "data/maps/OlivineCity_House1/scripts.pory"
	.string "cannot account for.\p"
# 757 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We did not find it.\p"
# 758 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It was reported to us. By\n"
# 759 "data/maps/OlivineCity_House1/scripts.pory"
	.string "telephone. Four days ago.\p"
# 760 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}A researcher from Alola.\p"
# 761 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He gave us a time window, a\n"
# 762 "data/maps/OlivineCity_House1/scripts.pory"
	.string "bearing, and the tide.\p"
# 763 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Then he called back and\n"
# 764 "data/maps/OlivineCity_House1/scripts.pory"
	.string "corrected the window.\p"
# 765 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Twice.\p"
# 766 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He was right twice.\p"
# 767 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel, read me his file\n"
# 768 "data/maps/OlivineCity_House1/scripts.pory"
	.string "again.\p"
# 769 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}“Professor Kukui.\n"
# 770 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pokémon move research.”\p"
# 771 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No enforcement record. No\n"
# 772 "data/maps/OlivineCity_House1/scripts.pory"
	.string "combat authorisation.\p"
# 773 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It is two pages long, Looker.\p"
# 774 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Two pages, and he is\n"
# 775 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sitting on a beach under an\l"
# 776 "data/maps/OlivineCity_House1/scripts.pory"
	.string "open sky.\p"
# 777 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}, we have evacuated\n"
# 778 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove into the Violet\l"
# 779 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Gym. Every soul but one.\p"
# 780 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}He will not leave the\n"
# 781 "data/maps/OlivineCity_House1/scripts.pory"
	.string "shore. He says somebody has to\l"
# 782 "data/maps/OlivineCity_House1/scripts.pory"
	.string "be looking when it opens.\p"
# 783 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}He is quite right, and\n"
# 784 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that is what frightens me.\p"
# 785 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The northwest beach, {PLAYER}.\p"
# 786 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare for two of them, and\n"
# 787 "data/maps/OlivineCity_House1/scripts.pory"
	.string "go and stand in front of that\l"
# 788 "data/maps/OlivineCity_House1/scripts.pory"
	.string "man.$"
# 789 "data/maps/OlivineCity_House1/scripts.pory"

# 790 "data/maps/OlivineCity_House1/scripts.pory"
@ The longest briefing of the arc on purpose (design section 6.4): it is the
# 791 "data/maps/OlivineCity_House1/scripts.pory"
@ one that names the town the player grew up in, puts their mother in the
# 792 "data/maps/OlivineCity_House1/scripts.pory"
@ half that refused to evacuate, and has Looker ask - once, in four missions
# 793 "data/maps/OlivineCity_House1/scripts.pory"
@ - whether they actually want to go.
# 794 "data/maps/OlivineCity_House1/scripts.pory"
@
# 795 "data/maps/OlivineCity_House1/scripts.pory"
@ IT IS ALSO WHERE THE FALLER CONVERSATION LIVES. Author's note, revision 4:
# 796 "data/maps/OlivineCity_House1/scripts.pory"
@ that conversation does not belong in the middle of a fight. Three rifts
# 797 "data/maps/OlivineCity_House1/scripts.pory"
@ opening at once is the first thing Anabel has ever felt from another city,
# 798 "data/maps/OlivineCity_House1/scripts.pory"
@ and feeling it from a chair in Olivine is what makes her finally sit the
# 799 "data/maps/OlivineCity_House1/scripts.pory"
@ player down and explain the whole of it - what she is, what she remembers,
# 800 "data/maps/OlivineCity_House1/scripts.pory"
@ what she does not, and the promise she made out of it. New Bark only gets
# 801 "data/maps/OlivineCity_House1/scripts.pory"
@ the callback (NewBarkTown_Text_UBAnabelPromise). Do not move this back.
# 802 "data/maps/OlivineCity_House1/scripts.pory"
@
# 803 "data/maps/OlivineCity_House1/scripts.pory"
@ TWO THINGS THIS BRIEFING DOES NOT SAY, both deliberate:
# 804 "data/maps/OlivineCity_House1/scripts.pory"
@ 1. Kukui is NOT going to New Bark. The chain is Elm -> Kukui -> Looker:
# 805 "data/maps/OlivineCity_House1/scripts.pory"
@    Elm posted six weeks of a reading he thought was broken to the one man
# 806 "data/maps/OlivineCity_House1/scripts.pory"
@    who would not laugh at it, and that man telephoned the police. Elm is
# 807 "data/maps/OlivineCity_House1/scripts.pory"
@    inside the analysis from here on; Kukui is not in the scene.
# 808 "data/maps/OlivineCity_House1/scripts.pory"
@ 2. Lusamine is not mentioned AT ALL. Nobody sent for her and nobody
# 809 "data/maps/OlivineCity_House1/scripts.pory"
@    announces her - she is simply standing on the road when the player
# 810 "data/maps/OlivineCity_House1/scripts.pory"
@    arrives. Putting her name in here spends the only surprise the mission
# 811 "data/maps/OlivineCity_House1/scripts.pory"
@    has before the creature.
# 812 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4:
# 813 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Sit down.\p"
# 814 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No - actually, don't.\p"
# 815 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There isn't time, and you would\n"
# 816 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not anyway.\p"
# 817 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove holds.\p"
# 818 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And the Professor? Did he eat\n"
# 819 "data/maps/OlivineCity_House1/scripts.pory"
	.string "something, at last?\p"
# 820 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}He ate, and then he\n"
# 821 "data/maps/OlivineCity_House1/scripts.pory"
	.string "read every log in Johto.\p"
# 822 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He telephoned at six this\n"
# 823 "data/maps/OlivineCity_House1/scripts.pory"
	.string "morning, from a post office, to\l"
# 824 "data/maps/OlivineCity_House1/scripts.pory"
	.string "read us somebody else's\l"
# 825 "data/maps/OlivineCity_House1/scripts.pory"
	.string "notebook.\p"
# 826 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Professor Elm has had the same\n"
# 827 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reading for six weeks. He wrote\l"
# 828 "data/maps/OlivineCity_House1/scripts.pory"
	.string "“check the sensor” in the\l"
# 829 "data/maps/OlivineCity_House1/scripts.pory"
	.string "margin every time.\p"
# 830 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And then he posted the whole\n"
# 831 "data/maps/OlivineCity_House1/scripts.pory"
	.string "thing to Alola anyway.\p"
# 832 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}A man who suspects he\n"
# 833 "data/maps/OlivineCity_House1/scripts.pory"
	.string "is wrong and files it in\l"
# 834 "data/maps/OlivineCity_House1/scripts.pory"
	.string "writing. There are worse\l"
# 835 "data/maps/OlivineCity_House1/scripts.pory"
	.string "witnesses.\p"
# 836 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Is the Professor going?\p"
# 837 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}No. He is going home.\p"
# 838 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He did the one thing only he\n"
# 839 "data/maps/OlivineCity_House1/scripts.pory"
	.string "could do, which was recognise\l"
# 840 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it, and he handed it to us.\p"
# 841 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Elm is the one on the ground\n"
# 842 "data/maps/OlivineCity_House1/scripts.pory"
	.string "now. It is his instrument, his\l"
# 843 "data/maps/OlivineCity_House1/scripts.pory"
	.string "six weeks and his town.$"
# 844 "data/maps/OlivineCity_House1/scripts.pory"

# 845 "data/maps/OlivineCity_House1/scripts.pory"
@ Parte 2 de 3 (ver o comentario em BriefingTalkM4 sobre gStringVar4).
# 846 "data/maps/OlivineCity_House1/scripts.pory"
@ Continua na MESMA caixa; comeca no "...Three, Anabel?" do Looker.
# 847 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Faller:
# 848 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Three, Anabel?\p"
# 849 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Three.\p"
# 850 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Opening together. Closing\n"
# 851 "data/maps/OlivineCity_House1/scripts.pory"
	.string "together.\p"
# 852 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Looker, I need the chair.\p"
# 853 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Chief-\p"
# 854 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'm fine. Sit down,\n"
# 855 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. This part is for you\l"
# 856 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I would rather say it here\l"
# 857 "data/maps/OlivineCity_House1/scripts.pory"
	.string "than shout it later.\p"
# 858 "data/maps/OlivineCity_House1/scripts.pory"
	.string "On that beach in Cherrygrove I\n"
# 859 "data/maps/OlivineCity_House1/scripts.pory"
	.string "told you what I am.\p"
# 860 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I did not tell you the rest.\p"
# 861 "data/maps/OlivineCity_House1/scripts.pory"
	.string "A Faller is someone who came\n"
# 862 "data/maps/OlivineCity_House1/scripts.pory"
	.string "through one of those tears and\l"
# 863 "data/maps/OlivineCity_House1/scripts.pory"
	.string "stayed on this side.\p"
# 864 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I don't remember where I came\n"
# 865 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from. I've stopped pretending\l"
# 866 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that will come back.\p"
# 867 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I remember someone's hand.\p"
# 868 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That is the whole memory.\n"
# 869 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Someone reached down, and I\l"
# 870 "data/maps/OlivineCity_House1/scripts.pory"
	.string "wasn't alone anymore.\p"
# 871 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And I feel them open. Only\n"
# 872 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that, and only a few seconds\l"
# 873 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before the meter does.\p"
# 874 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn I felt from the\n"
# 875 "data/maps/OlivineCity_House1/scripts.pory"
	.string "street. The Lake from the\l"
# 876 "data/maps/OlivineCity_House1/scripts.pory"
	.string "street. The beach from the\l"
# 877 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sand.$"
# 878 "data/maps/OlivineCity_House1/scripts.pory"

# 879 "data/maps/OlivineCity_House1/scripts.pory"
@ Parte 3 de 3. A Anabel ainda esta falando, por isso o {SPEAKER NAME_ANABEL}
# 880 "data/maps/OlivineCity_House1/scripts.pory"
@ no comeco: sem ele esta parte subiria sem plaquinha nenhuma.
# 881 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4NewBark:
# 882 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}{PLAYER} - I felt these three\n"
# 883 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from this chair.\p"
# 884 "data/maps/OlivineCity_House1/scripts.pory"
	.string "From Olivine. Sixty miles of\n"
# 885 "data/maps/OlivineCity_House1/scripts.pory"
	.string "water and a mountain.\p"
# 886 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…You have never once\n"
# 887 "data/maps/OlivineCity_House1/scripts.pory"
	.string "put that in a report.\p"
# 888 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Put it in this one.\p"
# 889 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll sign it.\p"
# 890 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. New Bark Town\n"
# 891 "data/maps/OlivineCity_House1/scripts.pory"
	.string "has no Pokémon Center.\p"
# 892 "data/maps/OlivineCity_House1/scripts.pory"
	.string "No Gym.\p"
# 893 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It has a laboratory and about\n"
# 894 "data/maps/OlivineCity_House1/scripts.pory"
	.string "forty people.\p"
# 895 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We told them to leave.\p"
# 896 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Half of them would not.\p"
# 897 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Your mother is one of the half.\p"
# 898 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Three missions, {PLAYER}, and I\n"
# 899 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have never once asked you this.\p"
# 900 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Do you want to go?\p"
# 901 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Heal everything.\p"
# 902 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Take these.\p"
# 903 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we are going with you -\n"
# 904 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that part is not a question.$"
# 905 "data/maps/OlivineCity_House1/scripts.pory"

# 906 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerHoliday:
# 907 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}A fine place for a\n"
# 908 "data/maps/OlivineCity_House1/scripts.pory"
	.string "holiday!\p"
# 909 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Though I seem to be spending\n"
# 910 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rather more time indoors than\l"
# 911 "data/maps/OlivineCity_House1/scripts.pory"
	.string "planned.$"
# 912 "data/maps/OlivineCity_House1/scripts.pory"

# 913 "data/maps/OlivineCity_House1/scripts.pory"
@ Script V2 section 13.3: between finishing a mission and Looker's summons call,
# 914 "data/maps/OlivineCity_House1/scripts.pory"
@ the house offers nothing but this. It does not name the next town, does not
# 915 "data/maps/OlivineCity_House1/scripts.pory"
@ send the player back to the town just cleared, and does not hand out the next
# 916 "data/maps/OlivineCity_House1/scripts.pory"
@ briefing early. The label is the one the script fixes; it is used for every
# 917 "data/maps/OlivineCity_House1/scripts.pory"
@ pending summons, not only Mahogany's.
# 918 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_WaitForMahoganyCall:
# 919 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We're still checking the\n"
# 920 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reports.\p"
# 921 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll call when we have a lead.$"
# 922 "data/maps/OlivineCity_House1/scripts.pory"

# 923 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_WaitForCherrygroveCall:
# 924 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We're comparing Lillie's\n"
# 925 "data/maps/OlivineCity_House1/scripts.pory"
	.string "notes with Anabel's\l"
# 926 "data/maps/OlivineCity_House1/scripts.pory"
	.string "recordings.\p"
# 927 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll call when we have a lead.$"
# 928 "data/maps/OlivineCity_House1/scripts.pory"

# 929 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelWaitForCall:
# 930 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nothing conclusive yet.\p"
# 931 "data/maps/OlivineCity_House1/scripts.pory"
	.string "When there is, Looker will\n"
# 932 "data/maps/OlivineCity_House1/scripts.pory"
	.string "telephone you himself.$"
# 933 "data/maps/OlivineCity_House1/scripts.pory"

# 934 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAhead:
# 935 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The Pokémon Center in\n"
# 936 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn.\p"
# 937 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll meet you there.$"
# 938 "data/maps/OlivineCity_House1/scripts.pory"

# 939 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM2:
# 940 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Mahogany, {PLAYER}!\n"
# 941 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are right behind you.$"
# 942 "data/maps/OlivineCity_House1/scripts.pory"

# 943 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM3:
# 944 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The northwest shore,\n"
# 945 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 946 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You cannot miss him.\p"
# 947 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He is the only man left in\n"
# 948 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that town, and he is wearing a\l"
# 949 "data/maps/OlivineCity_House1/scripts.pory"
	.string "lab coat on a beach.$"
# 950 "data/maps/OlivineCity_House1/scripts.pory"

# 951 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM4:
# 952 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}New Bark Town,\n"
# 953 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. Your own front door.\p"
# 954 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am sorry it is this one.$"
# 955 "data/maps/OlivineCity_House1/scripts.pory"

# 956 "data/maps/OlivineCity_House1/scripts.pory"

# 957 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelHoliday:
# 958 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It's peaceful here.\p"
# 959 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker keeps finding reasons\n"
# 960 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to check the telephone.$"
# 961 "data/maps/OlivineCity_House1/scripts.pory"

# 962 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAhead:
# 963 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Prepare your team\n"
# 964 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before you join us.\p"
# 965 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Clair is holding the street.$"
# 966 "data/maps/OlivineCity_House1/scripts.pory"

# 967 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM2:
# 968 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go on.\p"
# 969 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mr. Pryce does not strike me\n"
# 970 "data/maps/OlivineCity_House1/scripts.pory"
	.string "as a man who calls for help\l"
# 971 "data/maps/OlivineCity_House1/scripts.pory"
	.string "lightly.$"
# 972 "data/maps/OlivineCity_House1/scripts.pory"

# 973 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM3:
# 974 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go on.\p"
# 975 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And whatever he is doing when\n"
# 976 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you get there, {PLAYER}-\p"
# 977 "data/maps/OlivineCity_House1/scripts.pory"
	.string "make him sit down for one\n"
# 978 "data/maps/OlivineCity_House1/scripts.pory"
	.string "minute.$"
# 979 "data/maps/OlivineCity_House1/scripts.pory"

# 980 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM4:
# 981 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Go.\p"
# 982 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll be a step behind you the\n"
# 983 "data/maps/OlivineCity_House1/scripts.pory"
	.string "whole way.$"
# 984 "data/maps/OlivineCity_House1/scripts.pory"

# 985 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 986 "data/maps/OlivineCity_House1/scripts.pory"
@ Pre-Necrozma reunion texts.
# 987 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: all placeholder, rewrite in the design's voice (section 3.1):
# 988 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker theatrical and warm; Anabel precise; Lusamine formal and blunt;
# 989 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie direct; Gladion economical; Kukui enthusiastic.
# 990 "data/maps/OlivineCity_House1/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 991 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 992 "data/maps/OlivineCity_House1/scripts.pory"

# 993 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionOpen:
# 994 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Come in.\p"
# 995 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mind the chairs - there are\n"
# 996 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not enough of them, and I\l"
# 997 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have stopped apologising.\p"
# 998 "data/maps/OlivineCity_House1/scripts.pory"
	.string "New Bark holds. Four in four,\n"
# 999 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I am not certain that is\l"
# 1000 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the word for it.\p"
# 1001 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The file is closed. What is in\n"
# 1002 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it is worse than what we\l"
# 1003 "data/maps/OlivineCity_House1/scripts.pory"
	.string "opened it for.\p"
# 1004 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Which is why everyone in this\n"
# 1005 "data/maps/OlivineCity_House1/scripts.pory"
	.string "room came when I asked.\p"
# 1006 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Look at them. I did not have\n"
# 1007 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to explain twice.$"
# 1008 "data/maps/OlivineCity_House1/scripts.pory"

# 1009 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionKukui:
# 1010 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Your rifts closed\n"
# 1011 "data/maps/OlivineCity_House1/scripts.pory"
	.string "toward one bearing.\p"
# 1012 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Anabel's number, Elm's six\n"
# 1013 "data/maps/OlivineCity_House1/scripts.pory"
	.string "weeks of it, my rhythm.\p"
# 1014 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Three wrong tools, one\n"
# 1015 "data/maps/OlivineCity_House1/scripts.pory"
	.string "answer.\p"
# 1016 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There's a place out there,\n"
# 1017 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}. An altar.\p"
# 1018 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We can put a boat on it.$"
# 1019 "data/maps/OlivineCity_House1/scripts.pory"

# 1020 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineCalled:
# 1021 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I asked the\n"
# 1022 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Inspector to call this\l"
# 1023 "data/maps/OlivineCity_House1/scripts.pory"
	.string "meeting.\p"
# 1024 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not as Aether. Aether would\n"
# 1025 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have sent a report.\p"
# 1026 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I owe the people in this room\n"
# 1027 "data/maps/OlivineCity_House1/scripts.pory"
	.string "an accounting, and two of\l"
# 1028 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them are mine.$"
# 1029 "data/maps/OlivineCity_House1/scripts.pory"

# 1030 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie (3,6) and Gladion (3,7) have just turned to face each other.
# 1031 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillie:
# 1032 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}…You asked for us.\n"
# 1033 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Both of us.\p"
# 1034 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'm not going to pretend\n"
# 1035 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that's nothing.\p"
# 1036 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It isn't nothing.$"
# 1037 "data/maps/OlivineCity_House1/scripts.pory"

# 1038 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladion:
# 1039 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}We'll do the\n"
# 1040 "data/maps/OlivineCity_House1/scripts.pory"
	.string "accounting after.\p"
# 1041 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Whatever is at that altar, it\n"
# 1042 "data/maps/OlivineCity_House1/scripts.pory"
	.string "doesn't wait for our family\l"
# 1043 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to sort itself out.$"
# 1044 "data/maps/OlivineCity_House1/scripts.pory"

# 1045 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCross:
# 1046 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Then let me say the\n"
# 1047 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rest of it plainly.\p"
# 1048 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I intend to cross.\p"
# 1049 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I have been on the other side\n"
# 1050 "data/maps/OlivineCity_House1/scripts.pory"
	.string "of a door like that one.\p"
# 1051 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nobody else in this room has.$"
# 1052 "data/maps/OlivineCity_House1/scripts.pory"

# 1053 "data/maps/OlivineCity_House1/scripts.pory"
@ ONE box of recap and no more (design 3.1): Anabel told them all of this in
# 1054 "data/maps/OlivineCity_House1/scripts.pory"
@ New Bark. Here it is an argument, not news.
# 1055 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCondition:
# 1056 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}You have. I have as\n"
# 1057 "data/maps/OlivineCity_House1/scripts.pory"
	.string "well, and I came back wrong,\l"
# 1058 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and I told you all so in New\l"
# 1059 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bark.\p"
# 1060 "data/maps/OlivineCity_House1/scripts.pory"
	.string "So here is my condition,\n"
# 1061 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Madame, and it is not\l"
# 1062 "data/maps/OlivineCity_House1/scripts.pory"
	.string "negotiable:\p"
# 1063 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nobody crosses without a way\n"
# 1064 "data/maps/OlivineCity_House1/scripts.pory"
	.string "back.\p"
# 1065 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not you. Not me.\n"
# 1066 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not the Champion.$"
# 1067 "data/maps/OlivineCity_House1/scripts.pory"

# 1068 "data/maps/OlivineCity_House1/scripts.pory"
@ Must read standalone: this is also the whole of the state-11 question.
# 1069 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAsk:
# 1070 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}And a way through\n"
# 1071 "data/maps/OlivineCity_House1/scripts.pory"
	.string "needs something that can open\l"
# 1072 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it.\p"
# 1073 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not a machine. We tried\n"
# 1074 "data/maps/OlivineCity_House1/scripts.pory"
	.string "machines for six weeks.\p"
# 1075 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}. Your\n"
# 1076 "data/maps/OlivineCity_House1/scripts.pory"
	.string "partner.\p"
# 1077 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The one that started as an\n"
# 1078 "data/maps/OlivineCity_House1/scripts.pory"
	.string "egg.\p"
# 1079 "data/maps/OlivineCity_House1/scripts.pory"
	.string "May we see them?$"
# 1080 "data/maps/OlivineCity_House1/scripts.pory"

# 1081 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionNotYet:
# 1082 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Ah. Not yet.\p"
# 1083 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}That's not a no!\n"
# 1084 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's a “give it time”.\p"
# 1085 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It's still growing into what\n"
# 1086 "data/maps/OlivineCity_House1/scripts.pory"
	.string "it's going to be.\p"
# 1087 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then we prepare, and\n"
# 1088 "data/maps/OlivineCity_House1/scripts.pory"
	.string "you raise them.\p"
# 1089 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Come back when they have\n"
# 1090 "data/maps/OlivineCity_House1/scripts.pory"
	.string "finished becoming Solgaleo\l"
# 1091 "data/maps/OlivineCity_House1/scripts.pory"
	.string "or Lunala.\p"
# 1092 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We are not going anywhere.\p"
# 1093 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Frankly, there is nowhere for\n"
# 1094 "data/maps/OlivineCity_House1/scripts.pory"
	.string "six people to go in this\l"
# 1095 "data/maps/OlivineCity_House1/scripts.pory"
	.string "room.$"
# 1096 "data/maps/OlivineCity_House1/scripts.pory"

# 1097 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionSeeIt:
# 1098 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}…Oh.\p"
# 1099 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}That is it.\p"
# 1100 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That is the reading, standing\n"
# 1101 "data/maps/OlivineCity_House1/scripts.pory"
	.string "in a living room in Olivine.$"
# 1102 "data/maps/OlivineCity_House1/scripts.pory"

# 1103 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladionEgg:
# 1104 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}I handed you that\n"
# 1105 "data/maps/OlivineCity_House1/scripts.pory"
	.string "egg in Violet and told you to\l"
# 1106 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keep it away from people\l"
# 1107 "data/maps/OlivineCity_House1/scripts.pory"
	.string "like us.\p"
# 1108 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You did better than that.\n"
# 1109 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You raised it.$"
# 1110 "data/maps/OlivineCity_House1/scripts.pory"

# 1111 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillieProud:
# 1112 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}I knew the whole way.\p"
# 1113 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Every time we met, I knew.\p"
# 1114 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I just wanted to be here when\n"
# 1115 "data/maps/OlivineCity_House1/scripts.pory"
	.string "somebody finally said it out\l"
# 1116 "data/maps/OlivineCity_House1/scripts.pory"
	.string "loud.$"
# 1117 "data/maps/OlivineCity_House1/scripts.pory"

# 1118 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineKnows:
# 1119 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}That light is what\n"
# 1120 "data/maps/OlivineCity_House1/scripts.pory"
	.string "opens the way.\p"
# 1121 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am the only person alive\n"
# 1122 "data/maps/OlivineCity_House1/scripts.pory"
	.string "who knows what it looks like\l"
# 1123 "data/maps/OlivineCity_House1/scripts.pory"
	.string "from the other side.\p"
# 1124 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Thank you for not letting me\n"
# 1125 "data/maps/OlivineCity_House1/scripts.pory"
	.string "do this alone.\p"
# 1126 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I am told that is the lesson.$"
# 1127 "data/maps/OlivineCity_House1/scripts.pory"

# 1128 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionWayBack:
# 1129 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}My condition stands.\p"
# 1130 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We go together, and we come\n"
# 1131 "data/maps/OlivineCity_House1/scripts.pory"
	.string "back.$"
# 1132 "data/maps/OlivineCity_House1/scripts.pory"

# 1133 "data/maps/OlivineCity_House1/scripts.pory"
@ The handoff to the altar document. The last box is the one that tells the
# 1134 "data/maps/OlivineCity_House1/scripts.pory"
@ player the game is not taking them anywhere yet.
# 1135 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionHook:
# 1136 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Then it is settled.\p"
# 1137 "data/maps/OlivineCity_House1/scripts.pory"
	.string "There is a ship at the\n"
# 1138 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Olivine port, and it is ours\l"
# 1139 "data/maps/OlivineCity_House1/scripts.pory"
	.string "for as long as this takes.\p"
# 1140 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We sail for the altar,\n"
# 1141 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 1142 "data/maps/OlivineCity_House1/scripts.pory"
	.string "You, your partner, and\n"
# 1143 "data/maps/OlivineCity_House1/scripts.pory"
	.string "everyone in this room who can\l"
# 1144 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keep up.\p"
# 1145 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Come to the port when you are\n"
# 1146 "data/maps/OlivineCity_House1/scripts.pory"
	.string "ready. Rest first.\p"
# 1147 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Whatever is waiting at that\n"
# 1148 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar has waited a long time.\p"
# 1149 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It can wait for you to heal.$"
# 1150 "data/maps/OlivineCity_House1/scripts.pory"

# 1151 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicket:
# 1152 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}One more thing.\n"
# 1153 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Take this.$"
# 1154 "data/maps/OlivineCity_House1/scripts.pory"

# 1155 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicketUse:
# 1156 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Show it to the sailor at the\n"
# 1157 "data/maps/OlivineCity_House1/scripts.pory"
	.string "port. He will take you to the\l"
# 1158 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar, and bring you back.$"
# 1159 "data/maps/OlivineCity_House1/scripts.pory"

# 1160 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: state 12 and up, the repeatable reminder of where to go.
# 1161 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerAltar:
# 1162 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The ship is at the\n"
# 1163 "data/maps/OlivineCity_House1/scripts.pory"
	.string "port whenever you are ready,\l"
# 1164 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{PLAYER}.\p"
# 1165 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Madame Lusamine went ahead.\n"
# 1166 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Of course she did.$"
# 1167 "data/maps/OlivineCity_House1/scripts.pory"

# 1168 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelAltar:
# 1169 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We leave when you do,\n"
# 1170 "data/maps/OlivineCity_House1/scripts.pory"
	.string "not before.\p"
# 1171 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And we come back.\p"
# 1172 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That part is the whole plan.$"
# 1173 "data/maps/OlivineCity_House1/scripts.pory"

# 1174 "data/maps/OlivineCity_House1/scripts.pory"
@ SKELETON: idle lines for state 11, one box each.
# 1175 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLusamine:
# 1176 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}I will not pace.\p"
# 1177 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pacing is for people without\n"
# 1178 "data/maps/OlivineCity_House1/scripts.pory"
	.string "instruments.$"
# 1179 "data/maps/OlivineCity_House1/scripts.pory"

# 1180 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLillie:
# 1181 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Take your time with\n"
# 1182 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them.\p"
# 1183 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I mean it - that's not a\n"
# 1184 "data/maps/OlivineCity_House1/scripts.pory"
	.string "polite thing to say, it's the\l"
# 1185 "data/maps/OlivineCity_House1/scripts.pory"
	.string "actual advice.$"
# 1186 "data/maps/OlivineCity_House1/scripts.pory"

# 1187 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleGladion:
# 1188 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}Go and train.\p"
# 1189 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's not an insult, it's\n"
# 1190 "data/maps/OlivineCity_House1/scripts.pory"
	.string "what I'd be doing.$"
# 1191 "data/maps/OlivineCity_House1/scripts.pory"

# 1192 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleKukui:
# 1193 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Six weeks of bad data\n"
# 1194 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and one good afternoon!\p"
# 1195 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Science, {PLAYER}!$"
# 1196 "data/maps/OlivineCity_House1/scripts.pory"
@ Post-game, state >= 16: the family's two days a week in this room
# 1197 "data/maps/OlivineCity_House1/scripts.pory"
@ (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.6).
# 1198 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseLusaminePost:
# 1199 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The Inspector left us the key and a\n"
# 1200 "data/maps/OlivineCity_House1/scripts.pory"
	.string "note asking us not to reorganise\l"
# 1201 "data/maps/OlivineCity_House1/scripts.pory"
	.string "anything.\p"
# 1202 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I have reorganised three things.\p"
# 1203 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Sit down, {PLAYER}. Nobody here is\n"
# 1204 "data/maps/OlivineCity_House1/scripts.pory"
	.string "going anywhere for several hours, which\l"
# 1205 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I understand is what people do.$"
# 1206 "data/maps/OlivineCity_House1/scripts.pory"

# 1207 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseLilliePost:
# 1208 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Two days a week. That's what we agreed\n"
# 1209 "data/maps/OlivineCity_House1/scripts.pory"
	.string "on -- two days, here, no instruments, no\l"
# 1210 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reports.\p"
# 1211 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The first one was terrible. We all sat in\n"
# 1212 "data/maps/OlivineCity_House1/scripts.pory"
	.string "different corners.\p"
# 1213 "data/maps/OlivineCity_House1/scripts.pory"
	.string "This is the fourth one. It's getting\n"
# 1214 "data/maps/OlivineCity_House1/scripts.pory"
	.string "better. It's allowed to take a while.$"
# 1215 "data/maps/OlivineCity_House1/scripts.pory"

# 1216 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseGladionPost:
# 1217 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}I'm not good at this part.\p"
# 1218 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Silvally likes it. Look at him. He's\n"
# 1219 "data/maps/OlivineCity_House1/scripts.pory"
	.string "asleep under the table where Looker\l"
# 1220 "data/maps/OlivineCity_House1/scripts.pory"
	.string "used to put his files.\p"
# 1221 "data/maps/OlivineCity_House1/scripts.pory"
	.string "If he's fine with it, I'm fine with it.\n"
# 1222 "data/maps/OlivineCity_House1/scripts.pory"
	.string "That's the system I'm using.$"
