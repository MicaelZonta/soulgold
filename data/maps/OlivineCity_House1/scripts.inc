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
@ Four independent visibility decisions now, not one:
# 21 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_1  the family: the reunion visitors in 10 (once summoned) and 11,
# 22 "data/maps/OlivineCity_House1/scripts.pory"
@                and the five of them again from 16 on, by the weekday rota
# 23 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_2  Looker and Anabel: present below 16, gone from 16 on
# 24 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_3  Kukui: 10 (once summoned) and 11 only. He never comes back to
# 25 "data/maps/OlivineCity_House1/scripts.pory"
@                this room - from 16 on he is in Alola, and on some days on a
# 26 "data/maps/OlivineCity_House1/scripts.pory"
@                Cherrygrove beach
# 27 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_TEMP_4  the player's partner, a SCENE instance (reunion V2 section 7):
# 28 "data/maps/OlivineCity_House1/scripts.pory"
@                object 9, OBJ_EVENT_GFX_VAR_0 resolved from VAR_OBJ_GFX_ID_0.
# 29 "data/maps/OlivineCity_House1/scripts.pory"
@                Hidden on EVERY load; only the test clears it, and only the
# 30 "data/maps/OlivineCity_House1/scripts.pory"
@                test removes it. Its own flag, so removeobject is safe on it.
# 31 "data/maps/OlivineCity_House1/scripts.pory"
@
# 32 "data/maps/OlivineCity_House1/scripts.pory"
@ Floor plan (dump_mapa.py OlivineCity_House1; y grows DOWNWARD).
# 33 "data/maps/OlivineCity_House1/scripts.pory"
@ x=11 and x=12 are wall on every row and are left out.
# 34 "data/maps/OlivineCity_House1/scripts.pory"
@
# 35 "data/maps/OlivineCity_House1/scripts.pory"
@       x= 0 1 2 3 4 5 6 7 8 9 10
# 36 "data/maps/OlivineCity_House1/scripts.pory"
@   y=2    . . . . . . . . . . .     off camera when the player is at (4,8)
# 37 "data/maps/OlivineCity_House1/scripts.pory"
@   y=3    . . . . . . . . . . .     off camera
# 38 "data/maps/OlivineCity_House1/scripts.pory"
@   y=4    . . . . . # # . . . .     table (5-6,4-5) is solid
# 39 "data/maps/OlivineCity_House1/scripts.pory"
@   y=5    . . . . L # # A . . .     L = Looker (4,5)      A = Anabel (7,5)
# 40 "data/maps/OlivineCity_House1/scripts.pory"
@   y=6    . . N I . . . . . U .     N = Ninetales (2,6)   I = Lillie (3,6)   U = Lusamine (9,6)
# 41 "data/maps/OlivineCity_House1/scripts.pory"
@   y=7    . . S G . . P . K . .     S = Silvally (2,7)    G = Gladion (3,7)  K = Kukui (8,7)
# 42 "data/maps/OlivineCity_House1/scripts.pory"
@   y=8    # . . . W . . . . . #     P = partner (6,7), scene instance only
# 43 "data/maps/OlivineCity_House1/scripts.pory"
@   y=9    # # # # # # # # # # #     W = door (4,8): the only warp
# 44 "data/maps/OlivineCity_House1/scripts.pory"
@
# 45 "data/maps/OlivineCity_House1/scripts.pory"
@ Nobody stands south of the player, so the text box covers no actor. The
# 46 "data/maps/OlivineCity_House1/scripts.pory"
@ partner tile (6,7) is measured free; a 64x64 species sprite reaches into
# 47 "data/maps/OlivineCity_House1/scripts.pory"
@ row 6, columns 5-7, all floor, and never overlaps the solid table (rows
# 48 "data/maps/OlivineCity_House1/scripts.pory"
@ 4-5). In the V2 reunion nobody but the player walks to the door: Looker and
# 49 "data/maps/OlivineCity_House1/scripts.pory"
@ Anabel stay by the table, and the room centre stays open for the test.
# 50 "data/maps/OlivineCity_House1/scripts.pory"
@ Post-game (state >= 16) Lusamine's template is moved to (5,6) by
# 51 "data/maps/OlivineCity_House1/scripts.pory"
@ ApplyPostgameSeating below - by the table, near her children - measured
# 52 "data/maps/OlivineCity_House1/scripts.pory"
@ free, facing left at Lillie in (3,6).
# 53 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 54 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_MapScripts::
# 55 "data/maps/OlivineCity_House1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, OlivineCity_House1_OnTransition
# 56 "data/maps/OlivineCity_House1/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OlivineCity_House1_OnFrame
# 57 "data/maps/OlivineCity_House1/scripts.pory"
	.byte 0
# 58 "data/maps/OlivineCity_House1/scripts.pory"

# 59 "data/maps/OlivineCity_House1/scripts.pory"
@ NEW with the pre-Necrozma reunion. Looker and Anabel are on FLAG_TEMP_2 (see
# 60 "data/maps/OlivineCity_House1/scripts.pory"
@ the header). The six reunion objects need this too: their hide
# 61 "data/maps/OlivineCity_House1/scripts.pory"
@ flag is FLAG_TEMP_1, and ClearTempFieldEventData zeroes every temp on every
# 62 "data/maps/OlivineCity_House1/scripts.pory"
@ load - so the DEFAULT IS VISIBLE, and this block is the only thing that keeps
# 63 "data/maps/OlivineCity_House1/scripts.pory"
@ Lusamine and the others out of the room for the whole game before state 10.
# 64 "data/maps/OlivineCity_House1/scripts.pory"
@ It runs before the first spawn, on every load of this map.
# 65 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_OnTransition::
# 66 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyReunionVisibility
# 67 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyInvestigatorVisibility
# 68 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyKukuiVisibility
# 69 "data/maps/OlivineCity_House1/scripts.pory"
	@ The partner is a scene instance: it exists only between the release and
# 70 "data/maps/OlivineCity_House1/scripts.pory"
	@ the recall inside the test script, so on every load it is hidden. This
# 71 "data/maps/OlivineCity_House1/scripts.pory"
	@ line is unconditional for the same reason the others are - temps come
# 72 "data/maps/OlivineCity_House1/scripts.pory"
	@ back zeroed, and a zeroed temp means VISIBLE.
# 73 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_4
# 74 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_ApplyPostgameSeating
# 75 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 76 "data/maps/OlivineCity_House1/scripts.pory"

# 77 "data/maps/OlivineCity_House1/scripts.pory"
@ FLAG_TEMP_1 - the four visitors and the two partners. Shown in state 10 only
# 78 "data/maps/OlivineCity_House1/scripts.pory"
@ once Looker's invitation went out (reunion V2 section 2: before the call the
# 79 "data/maps/OlivineCity_House1/scripts.pory"
@ base is open but the cast is NOT gathered yet), in state 11 always (the
# 80 "data/maps/OlivineCity_House1/scripts.pory"
@ meeting happened; they wait for the partner), and from 16 on by the weekday
# 81 "data/maps/OlivineCity_House1/scripts.pory"
@ rota. From 12 to 15 they are gone: they went ahead to the voyage.
# 82 "data/maps/OlivineCity_House1/scripts.pory"
@ Runs UNCONDITIONALLY - an "optimised" version that only ran in state 10 would
# 83 "data/maps/OlivineCity_House1/scripts.pory"
@ leave the house full of visitors from New Game on.
# 84 "data/maps/OlivineCity_House1/scripts.pory"
@ goto_if_eq on listed values, NEVER goto_if_ge: that is the mistake this file
# 85 "data/maps/OlivineCity_House1/scripts.pory"
@ has already made three times (see the Looker branch block below).
# 86 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyReunionVisibility::
# 87 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowReunionCastIfSummoned
# 88 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowReunionCast
# 89 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HideReunionCast
# 90 "data/maps/OlivineCity_House1/scripts.pory"
	@ Post-game: Sunday and Friday are the family's days. The whole arc was about
# 91 "data/maps/OlivineCity_House1/scripts.pory"
	@ a family that could not be in the same place; two days a week where the only
# 92 "data/maps/OlivineCity_House1/scripts.pory"
	@ thing they do is be together is the reward, and it needs no line of dialogue
# 93 "data/maps/OlivineCity_House1/scripts.pory"
	@ explaining itself. Kukui is NOT part of this - he is on FLAG_TEMP_3.
# 94 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, GetDayOfWeek
# 95 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_SUN, OlivineCity_House1_EventScript_ShowReunionCast
# 96 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, WEEKDAY_FRI, OlivineCity_House1_EventScript_ShowReunionCast
# 97 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HideReunionCast::
# 98 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_1
# 99 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 100 "data/maps/OlivineCity_House1/scripts.pory"

# 101 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10 before the invitation: the meeting does not exist yet, so neither
# 102 "data/maps/OlivineCity_House1/scripts.pory"
@ does the gathering. FLAG_RIFT_LOOKER_SUMMONS is cleared by the scene itself
# 103 "data/maps/OlivineCity_House1/scripts.pory"
@ (the invitation has been answered), but by then the state moves to 11 or 12
# 104 "data/maps/OlivineCity_House1/scripts.pory"
@ in the same script, so no load ever sees 10-with-cast-and-no-summons.
# 105 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowReunionCastIfSummoned::
# 106 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_set FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_ShowReunionCast
# 107 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_1
# 108 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 109 "data/maps/OlivineCity_House1/scripts.pory"

# 110 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowReunionCast::
# 111 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_1
# 112 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 113 "data/maps/OlivineCity_House1/scripts.pory"

# 114 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker and Anabel: the whole game up to the farewell, and then never again.
# 115 "data/maps/OlivineCity_House1/scripts.pory"
@ Runs unconditionally on every load, and it is the ONLY thing that ever removes
# 116 "data/maps/OlivineCity_House1/scripts.pory"
@ them (see the header block for what happens if it is deleted).
# 117 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyInvestigatorVisibility::
# 118 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HideInvestigators
# 119 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_2
# 120 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 121 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HideInvestigators::
# 122 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_2
# 123 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 124 "data/maps/OlivineCity_House1/scripts.pory"

# 125 "data/maps/OlivineCity_House1/scripts.pory"
@ Kukui: states 10 (once summoned) and 11 only, and a closed window on purpose
# 126 "data/maps/OlivineCity_House1/scripts.pory"
@ - goto_if_ge here would put him in this room for the rest of the game. Same
# 127 "data/maps/OlivineCity_House1/scripts.pory"
@ summons gate as the family: he arrives with the meeting, not before it.
# 128 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyKukuiVisibility::
# 129 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowKukuiIfSummoned
# 130 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowKukui
# 131 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_3
# 132 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 133 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowKukuiIfSummoned::
# 134 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_set FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_ShowKukui
# 135 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_TEMP_3
# 136 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 137 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ShowKukui::
# 138 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_3
# 139 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 140 "data/maps/OlivineCity_House1/scripts.pory"

# 141 "data/maps/OlivineCity_House1/scripts.pory"
@ Reunion V2 section 11: in the post-game the room is the family's, so
# 142 "data/maps/OlivineCity_House1/scripts.pory"
@ Lusamine does not keep her reunion spot against the east wall. She sits by
# 143 "data/maps/OlivineCity_House1/scripts.pory"
@ the table, near her children: (5,6), measured free, facing left at Lillie
# 144 "data/maps/OlivineCity_House1/scripts.pory"
@ in (3,6). setobjectxyperm edits the RAM copy of the template that this very
# 145 "data/maps/OlivineCity_House1/scripts.pory"
@ load spawns from; below 16 the ROM position (9,6) is untouched, and every
# 146 "data/maps/OlivineCity_House1/scripts.pory"
@ load recomputes this, so it never leaks into the reunion states.
# 147 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ApplyPostgameSeating::
# 148 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_SeatingDone
# 149 "data/maps/OlivineCity_House1/scripts.pory"
	setobjectxyperm LOCALID_OLIVINE_HOUSE1_LUSAMINE, 5, 6
# 150 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_SeatingDone::
# 151 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 152 "data/maps/OlivineCity_House1/scripts.pory"

# 153 "data/maps/OlivineCity_House1/scripts.pory"
@ VAR_TEMP_1 is a once-per-visit latch (temps are zeroed by
# 154 "data/maps/OlivineCity_House1/scripts.pory"
@ ClearTempFieldEventData on every map load), so the frame trigger can never
# 155 "data/maps/OlivineCity_House1/scripts.pory"
@ re-fire and livelock the controls.
# 156 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_OnFrame::
# 157 "data/maps/OlivineCity_House1/scripts.pory"
	map_script_2 VAR_TEMP_1, 0, OlivineCity_House1_EventScript_BriefingTrigger
# 158 "data/maps/OlivineCity_House1/scripts.pory"
	.2byte 0
# 159 "data/maps/OlivineCity_House1/scripts.pory"

# 160 "data/maps/OlivineCity_House1/scripts.pory"
@ Only stages a scene in a briefing state (2 = Blackthorn, 4 = Mahogany,
# 161 "data/maps/OlivineCity_House1/scripts.pory"
@ 6 = Cherrygrove, 8 = New Bark) or in the reunion state 10 AND only if the
# 162 "data/maps/OlivineCity_House1/scripts.pory"
@ player just came through the door at (4,8). Outside that, every one of those
# 163 "data/maps/OlivineCity_House1/scripts.pory"
@ still runs - through the Looker/Anabel object scripts, just without the
# 164 "data/maps/OlivineCity_House1/scripts.pory"
@ choreography.
# 165 "data/maps/OlivineCity_House1/scripts.pory"
@ (4,8) is the ONLY warp of this house and there is no Fly or Dig indoors, so
# 166 "data/maps/OlivineCity_House1/scripts.pory"
@ in state 10 the player is necessarily standing there when this fires.
# 167 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11 matches nothing here ON PURPOSE (reunion V2 section 6): entering
# 168 "data/maps/OlivineCity_House1/scripts.pory"
@ the house in state 11 starts no dialogue. The retake is OFFERED by Looker
# 169 "data/maps/OlivineCity_House1/scripts.pory"
@ and Anabel in conversation, and nowhere else.
# 170 "data/maps/OlivineCity_House1/scripts.pory"
@ State 12 matches nothing here on purpose: the reunion is over.
# 171 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTrigger::
# 172 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_TEMP_1, 1                        @ first instruction: stops re-firing
# 173 "data/maps/OlivineCity_House1/scripts.pory"
	getplayerxy VAR_0x8004, VAR_0x8005
# 174 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8004, 4, OlivineCity_House1_EventScript_End
# 175 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8005, 8, OlivineCity_House1_EventScript_End
# 176 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_StageBriefing
# 177 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_StageBriefingIfCalled
# 178 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_StageBriefingIfCalled
# 179 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_StageBriefingIfCalled
# 180 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_StageReunionIfCalled
# 181 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 182 "data/maps/OlivineCity_House1/scripts.pory"

# 183 "data/maps/OlivineCity_House1/scripts.pory"
@ States 4, 6, 8 and 10 are only ready once Looker has telephoned
# 184 "data/maps/OlivineCity_House1/scripts.pory"
@ (FLAG_RIFT_LOOKER_SUMMONS, set by RiftMissions_EventScript_LookerCall). Before
# 185 "data/maps/OlivineCity_House1/scripts.pory"
@ that the house has nothing staged: walking in gets the player nothing but the
# 186 "data/maps/OlivineCity_House1/scripts.pory"
@ waiting line from whichever detective they talk to.
# 187 "data/maps/OlivineCity_House1/scripts.pory"
@ State 2 is NOT gated. Its summons is the call scene in New Bark, that
# 188 "data/maps/OlivineCity_House1/scripts.pory"
@ invitation never expires and never repeats, and gating it would strand a save
# 189 "data/maps/OlivineCity_House1/scripts.pory"
@ made before this flag existed.
# 190 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageBriefingIfCalled::
# 191 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_End
# 192 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_StageBriefing
# 193 "data/maps/OlivineCity_House1/scripts.pory"

# 194 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageReunionIfCalled::
# 195 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_End
# 196 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_StageReunion
# 197 "data/maps/OlivineCity_House1/scripts.pory"

# 198 "data/maps/OlivineCity_House1/scripts.pory"
@ The choreography itself, shared by both briefings. Unchanged since Rift
# 199 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1: only which text BriefingTalk picks differs.
# 200 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageBriefing::
# 201 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 202 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 203 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 204 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 205 "data/maps/OlivineCity_House1/scripts.pory"
	@ Looker  (4,5)->(4,6)->(4,7), faces down at the player in (4,8).
# 206 "data/maps/OlivineCity_House1/scripts.pory"
	@ Anabel  (7,5)->(7,6)->(7,7)->(6,7)->(5,7), faces down.
# 207 "data/maps/OlivineCity_House1/scripts.pory"
	@ The two paths share no tile on any step, so they can walk together.
# 208 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerApproach
# 209 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelApproach
# 210 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 211 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 212 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 213 "data/maps/OlivineCity_House1/scripts.pory"
	@ Back home: the reverse paths, also disjoint step by step.
# 214 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, OlivineCity_House1_Movement_LookerReturn
# 215 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_ANABEL, OlivineCity_House1_Movement_AnabelReturn
# 216 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 217 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_ANABEL
# 218 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 219 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 220 "data/maps/OlivineCity_House1/scripts.pory"

# 221 "data/maps/OlivineCity_House1/scripts.pory"
@ The reunion cutscene (script V2, 25/09/2026). Reached from the frame trigger
# 222 "data/maps/OlivineCity_House1/scripts.pory"
@ at state 10 and from the Looker/Anabel object scripts at state 10. It plays
# 223 "data/maps/OlivineCity_House1/scripts.pory"
@ ONCE: it always ends in state 11 or 12, and neither re-enters it.
# 224 "data/maps/OlivineCity_House1/scripts.pory"
@
# 225 "data/maps/OlivineCity_House1/scripts.pory"
@ V2 choreography change: Looker and Anabel STAY by the table. The two old
# 226 "data/maps/OlivineCity_House1/scripts.pory"
@ walks to the door are gone - the scene organises itself around the plan on
# 227 "data/maps/OlivineCity_House1/scripts.pory"
@ the table, and the room centre stays free for the partner's test. The only
# 228 "data/maps/OlivineCity_House1/scripts.pory"
@ approach is the player's: one step in, (4,8) -> (4,7), which keeps the warp
# 229 "data/maps/OlivineCity_House1/scripts.pory"
@ tile free and matches the respawn tile of the ending.
# 230 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_StageReunion::
# 231 "data/maps/OlivineCity_House1/scripts.pory"
	lockall
# 232 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower
# 233 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LOOKER, Common_Movement_ExclamationMark
# 234 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LOOKER
# 235 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, OlivineCity_House1_Movement_PlayerEnter
# 236 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 237 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 238 "data/maps/OlivineCity_House1/scripts.pory"

# 239 "data/maps/OlivineCity_House1/scripts.pory"
@ The reunion, script V2 section 4-5: the destination and the problem, then a
# 240 "data/maps/OlivineCity_House1/scripts.pory"
@ real way out. Beats in V2's order:
# 241 "data/maps/OlivineCity_House1/scripts.pory"
@   1. Looker opens and points the landing site out on the table map: from
# 242 "data/maps/OlivineCity_House1/scripts.pory"
@      (4,5) the table at (5-6,4-5) is due east.
# 243 "data/maps/OlivineCity_House1/scripts.pory"
@   2. Kukui walks the record - spike, then flicker. He already faces west,
# 244 "data/maps/OlivineCity_House1/scripts.pory"
@      into the room; the exclamation is him catching the spike.
# 245 "data/maps/OlivineCity_House1/scripts.pory"
@   3. Lillie turns to her MOTHER, not the floor: (3,6) -> (9,6), due east.
# 246 "data/maps/OlivineCity_House1/scripts.pory"
@      Lusamine answers with her equipment's limit, facing west at her
# 247 "data/maps/OlivineCity_House1/scripts.pory"
@      daughter (template direction, untouched).
# 248 "data/maps/OlivineCity_House1/scripts.pory"
@   4. Gladion asks how they come back. The case sits by Kukui at (8,7), due
# 249 "data/maps/OlivineCity_House1/scripts.pory"
@      east of him - his template already faces it.
# 250 "data/maps/OlivineCity_House1/scripts.pory"
@   5. Lusamine opens the case: one step down the east wall, (9,6) -> (9,7),
# 251 "data/maps/OlivineCity_House1/scripts.pory"
@      measured free, then she faces it (west). Anabel turns east to take the
# 252 "data/maps/OlivineCity_House1/scripts.pory"
@      portable unit and names the withdrawal criterion and the Beast Ball
# 253 "data/maps/OlivineCity_House1/scripts.pory"
@      (Kurt's, hers to keep - the altar's scripted capture uses it).
# 254 "data/maps/OlivineCity_House1/scripts.pory"
@   6. The leadership beat: Lusamine turns to the map (north), Lillie asks for
# 255 "data/maps/OlivineCity_House1/scripts.pory"
@      the controls, the pause, Lusamine faces her (west) and teaches ONE
# 256 "data/maps/OlivineCity_House1/scripts.pory"
@      concrete thing. Anabel closes: decided at the altar.
# 257 "data/maps/OlivineCity_House1/scripts.pory"
@ NO direction here is derived from the player's live position: every
# 258 "data/maps/OlivineCity_House1/scripts.pory"
@ turnobject aims at another actor on a fixed tile. That is what makes the
# 259 "data/maps/OlivineCity_House1/scripts.pory"
@ block correct both from the frame trigger (player at (4,7)) and from an
# 260 "data/maps/OlivineCity_House1/scripts.pory"
@ object script (player anywhere in the room).
# 261 "data/maps/OlivineCity_House1/scripts.pory"
@ Consecutive msgbox with no closemessage between them keep the box up and
# 262 "data/maps/OlivineCity_House1/scripts.pory"
@ swap the plaque per speaker; closemessage before EVERY movement, or the
# 263 "data/maps/OlivineCity_House1/scripts.pory"
@ movement happens behind the open box.
# 264 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionScene::
# 265 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_RIFT_LOOKER_SUMMONS          @ the invitation has been answered
# 266 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionOpen, MSGBOX_DEFAULT
# 267 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 268 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LOOKER, DIR_EAST
# 269 "data/maps/OlivineCity_House1/scripts.pory"
	delay 20
# 270 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_KUKUI, Common_Movement_ExclamationMark
# 271 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_KUKUI
# 272 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionKukui, MSGBOX_DEFAULT
# 273 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 274 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LILLIE, DIR_EAST
# 275 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillie, MSGBOX_DEFAULT
# 276 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineEvidence, MSGBOX_DEFAULT
# 277 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladionPlan, MSGBOX_DEFAULT
# 278 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 279 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LUSAMINE, OlivineCity_House1_Movement_LusamineToCase
# 280 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LUSAMINE
# 281 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionStabilizer, MSGBOX_DEFAULT
# 282 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 283 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_EAST
# 284 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAnabelReturn, MSGBOX_DEFAULT
# 285 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionCapture, MSGBOX_DEFAULT
# 286 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 287 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LUSAMINE, DIR_NORTH
# 288 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineCross, MSGBOX_DEFAULT
# 289 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLillieBoundary, MSGBOX_DEFAULT
# 290 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 291 "data/maps/OlivineCity_House1/scripts.pory"
	delay 40
# 292 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LUSAMINE, DIR_WEST
# 293 "data/maps/OlivineCity_House1/scripts.pory"
	delay 20
# 294 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionLusamineControl, MSGBOX_DEFAULT
# 295 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAnabelLeadership, MSGBOX_DEFAULT
# 296 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 297 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_SOUTH
# 298 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through to the partner question
# 299 "data/maps/OlivineCity_House1/scripts.pory"

# 300 "data/maps/OlivineCity_House1/scripts.pory"
@ Kukui asks for the partner. Reached ONCE, from the long scene above: the
# 301 "data/maps/OlivineCity_House1/scripts.pory"
@ state-11 resume (Looker/Anabel) skips this box and re-enters at the
# 302 "data/maps/OlivineCity_House1/scripts.pory"
@ eligibility below (V2 section 6: "Yes repeats only the eligibility").
# 303 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionAskPartner::
# 304 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAsk, MSGBOX_DEFAULT
# 305 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 306 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through to the eligibility
# 307 "data/maps/OlivineCity_House1/scripts.pory"

# 308 "data/maps/OlivineCity_House1/scripts.pory"
@ The one gate of the arc, unchanged in V2: Solgaleo OR Lunala, in the PARTY.
# 309 "data/maps/OlivineCity_House1/scripts.pory"
@ checkspecies compiles to Scrcmd_checkspecies (src/scrcmd.c), which calls
# 310 "data/maps/OlivineCity_House1/scripts.pory"
@ CheckPartyHasSpecies (src/field_specials.c): it walks gPlayerParty only and
# 311 "data/maps/OlivineCity_House1/scripts.pory"
@ returns into VAR_RESULT. Consequences, all of them wanted by the design:
# 312 "data/maps/OlivineCity_House1/scripts.pory"
@   - one in the PC does not count for the gate; a Pokedex entry does not
# 313 "data/maps/OlivineCity_House1/scripts.pory"
@     count; Cosmog and Cosmoem do not pass, and no evolution happens here;
# 314 "data/maps/OlivineCity_House1/scripts.pory"
@   - EITHER species satisfies it, and having both is never required.
# 315 "data/maps/OlivineCity_House1/scripts.pory"
@ What V2 ADDS is on both edges of the gate, never in it:
# 316 "data/maps/OlivineCity_House1/scripts.pory"
@   - both present -> an explicit SYSTEM menu; backing out (B) defers exactly
# 317 "data/maps/OlivineCity_House1/scripts.pory"
@     like "Not now" (menu exit hands control back, V2 checklist);
# 318 "data/maps/OlivineCity_House1/scripts.pory"
@   - neither present -> the PC is consulted READ-ONLY to pick the one
# 319 "data/maps/OlivineCity_House1/scripts.pory"
@     guidance line that is true (ReunionGuidance below).
# 320 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionEligibility::
# 321 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_SOLGALEO
# 322 "data/maps/OlivineCity_House1/scripts.pory"
	copyvar VAR_TEMP_2, VAR_RESULT
# 323 "data/maps/OlivineCity_House1/scripts.pory"
	checkspecies SPECIES_LUNALA
# 324 "data/maps/OlivineCity_House1/scripts.pory"
	copyvar VAR_TEMP_3, VAR_RESULT
# 325 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_TEMP_2, FALSE, OlivineCity_House1_EventScript_EligibilityNoSolgaleo
# 326 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_TEMP_3, FALSE, OlivineCity_House1_EventScript_UseSolgaleo
# 327 "data/maps/OlivineCity_House1/scripts.pory"
	@ both in the team: the SYSTEM question (no plate), then the menu under it
# 328 "data/maps/OlivineCity_House1/scripts.pory"
	message OlivineCity_House1_Text_PartnerSelect
# 329 "data/maps/OlivineCity_House1/scripts.pory"
	waitmessage
# 330 "data/maps/OlivineCity_House1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, OlivineCity_House1_Text_ChoiceSolgaleo, OlivineCity_House1_Text_ChoiceLunala, OlivineCity_House1_Text_ChoiceNotNow
# 331 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 332 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, 0, OlivineCity_House1_EventScript_UseSolgaleo
# 333 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, 1, OlivineCity_House1_EventScript_UseLunala
# 334 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionDeferred   @ "Not now" and B alike
# 335 "data/maps/OlivineCity_House1/scripts.pory"

# 336 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_EligibilityNoSolgaleo::
# 337 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_TEMP_3, FALSE, OlivineCity_House1_EventScript_ReunionGuidance
# 338 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through: Lunala is the one present
# 339 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_UseLunala::
# 340 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_LUNALA
# 341 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(LUNALA)
# 342 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionTest
# 343 "data/maps/OlivineCity_House1/scripts.pory"

# 344 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_UseSolgaleo::
# 345 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_TEMP_2, SPECIES_SOLGALEO
# 346 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_SPECIES(SOLGALEO)
# 347 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionTest
# 348 "data/maps/OlivineCity_House1/scripts.pory"

# 349 "data/maps/OlivineCity_House1/scripts.pory"
@ V2 section 6: before control returns - for lack of the partner OR by the
# 350 "data/maps/OlivineCity_House1/scripts.pory"
@ player's own deferral - state 11 is registered, so the discussion never
# 351 "data/maps/OlivineCity_House1/scripts.pory"
@ replays; only the test and the pass stay pending. Idempotent from state 11:
# 352 "data/maps/OlivineCity_House1/scripts.pory"
@ running it again rewrites 11, and nothing ever goes back to 10.
# 353 "data/maps/OlivineCity_House1/scripts.pory"
@ releaseall (not release) because every reunion branch is reached from a
# 354 "data/maps/OlivineCity_House1/scripts.pory"
@ lockall context AND from a lock context; releaseall is correct in both.
# 355 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionDeferred::
# 356 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionDeferred, MSGBOX_DEFAULT
# 357 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 358 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionReleaseEnd
# 359 "data/maps/OlivineCity_House1/scripts.pory"

# 360 "data/maps/OlivineCity_House1/scripts.pory"
@ No eligible partner in the party. V2 section 6: the guidance says only what
# 361 "data/maps/OlivineCity_House1/scripts.pory"
@ was VERIFIED, and the consultation never opens the test:
# 362 "data/maps/OlivineCity_House1/scripts.pory"
@   - Solgaleo or Lunala found in the PC        -> "bring it from the PC"
# 363 "data/maps/OlivineCity_House1/scripts.pory"
@   - Cosmog/Cosmoem confirmed, party or PC     -> "it needs to evolve first"
# 364 "data/maps/OlivineCity_House1/scripts.pory"
@     (party: CheckMysteryEggPokemon, which ignores eggs and only answers
# 365 "data/maps/OlivineCity_House1/scripts.pory"
@      after the Violet egg event - verified provenance; PC: the read-only
# 366 "data/maps/OlivineCity_House1/scripts.pory"
@      species scan, eggs excluded)
# 367 "data/maps/OlivineCity_House1/scripts.pory"
@   - nothing verifiable                        -> the neutral line, which
# 368 "data/maps/OlivineCity_House1/scripts.pory"
@     claims no growth, loss or trade
# 369 "data/maps/OlivineCity_House1/scripts.pory"
@ An unhatched egg proves no species (V2: "ovo generico nao comprova essa
# 370 "data/maps/OlivineCity_House1/scripts.pory"
@ origem"), so it deliberately lands on the neutral line.
# 371 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionGuidance::
# 372 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_0x8004, SPECIES_SOLGALEO
# 373 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, CheckPCHasSpecies
# 374 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_GuidanceStored
# 375 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_0x8004, SPECIES_LUNALA
# 376 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, CheckPCHasSpecies
# 377 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_GuidanceStored
# 378 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, CheckMysteryEggPokemon
# 379 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, OlivineCity_House1_EventScript_GuidanceUnevolved
# 380 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, OlivineCity_House1_EventScript_GuidanceUnevolved
# 381 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_0x8004, SPECIES_COSMOG
# 382 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, CheckPCHasSpecies
# 383 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_GuidanceUnevolved
# 384 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_0x8004, SPECIES_COSMOEM
# 385 "data/maps/OlivineCity_House1/scripts.pory"
	specialvar VAR_RESULT, CheckPCHasSpecies
# 386 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_GuidanceUnevolved
# 387 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionMissing, MSGBOX_DEFAULT
# 388 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 389 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionReleaseEnd
# 390 "data/maps/OlivineCity_House1/scripts.pory"

# 391 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_GuidanceStored::
# 392 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionStored, MSGBOX_DEFAULT
# 393 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 394 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionReleaseEnd
# 395 "data/maps/OlivineCity_House1/scripts.pory"

# 396 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_GuidanceUnevolved::
# 397 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionUnevolved, MSGBOX_DEFAULT
# 398 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 399 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionReleaseEnd
# 400 "data/maps/OlivineCity_House1/scripts.pory"

# 401 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11 retake, V2 section 6: offered by Looker and Anabel in conversation,
# 402 "data/maps/OlivineCity_House1/scripts.pory"
@ never on entry. Yes repeats only the eligibility and heads to the test;
# 403 "data/maps/OlivineCity_House1/scripts.pory"
@ Not yet (or B) hands control back. No state changes here: 11 stays 11.
# 404 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionResume::
# 405 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionResume, MSGBOX_DEFAULT
# 406 "data/maps/OlivineCity_House1/scripts.pory"
	dynmultichoice 0, 0, FALSE, 2, 0, DYN_MULTICHOICE_CB_NONE, OlivineCity_House1_Text_ChoiceYes, OlivineCity_House1_Text_ChoiceNotYet
# 407 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 408 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, 0, OlivineCity_House1_EventScript_ReunionEligibility
# 409 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionReleaseEnd
# 410 "data/maps/OlivineCity_House1/scripts.pory"

# 411 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionReleaseEnd::
# 412 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 413 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 414 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 415 "data/maps/OlivineCity_House1/scripts.pory"

# 416 "data/maps/OlivineCity_House1/scripts.pory"
@ The test, V2 section 7: show before explaining. The partner is a SCENE
# 417 "data/maps/OlivineCity_House1/scripts.pory"
@ instance of the chosen species - object 9 at (6,7), OBJ_EVENT_GFX_VAR_0
# 418 "data/maps/OlivineCity_House1/scripts.pory"
@ resolved from VAR_OBJ_GFX_ID_0 at spawn - and never the follower: the
# 419 "data/maps/OlivineCity_House1/scripts.pory"
@ follower is hidden first, so the same Pokemon is never in the room twice,
# 420 "data/maps/OlivineCity_House1/scripts.pory"
@ and its own state is restored by the map load at the end.
# 421 "data/maps/OlivineCity_House1/scripts.pory"
@ NO rift opens in this room. The flashes are fadescreenswapbuffers, which
# 422 "data/maps/OlivineCity_House1/scripts.pory"
@ does not touch the palette buffers, so the day/night tint survives; no
# 423 "data/maps/OlivineCity_House1/scripts.pory"
@ shake, no alarm, no battle theme - the music dips for the pulse and comes
# 424 "data/maps/OlivineCity_House1/scripts.pory"
@ back with the result. The result is compatibility, not a proven crossing.
# 425 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionTest::
# 426 "data/maps/OlivineCity_House1/scripts.pory"
	@ The pass at the end of this script is the ONE thing that could fail (a
# 427 "data/maps/OlivineCity_House1/scripts.pory"
	@ full Key Items pocket). Checked BEFORE anything happens, in the same
# 428 "data/maps/OlivineCity_House1/scripts.pory"
	@ script run as the giveitem, so the delivery later cannot fail: state 12
# 429 "data/maps/OlivineCity_House1/scripts.pory"
	@ is never set with the pass undelivered, and no half-done state exists
# 430 "data/maps/OlivineCity_House1/scripts.pory"
	@ (V2 section 8). The reunion itself is never replayed either way.
# 431 "data/maps/OlivineCity_House1/scripts.pory"
	checkitemspace ITEM_SUN_MOON_TICKET, 1
# 432 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, OlivineCity_House1_EventScript_ReunionNoRoom
# 433 "data/maps/OlivineCity_House1/scripts.pory"
	hidefollower                                @ needed on the resume path (lock)
# 434 "data/maps/OlivineCity_House1/scripts.pory"
	@ On the trigger path the player is at (4,7), and the partner appears due
# 435 "data/maps/OlivineCity_House1/scripts.pory"
	@ east. From the object scripts the player can be anywhere, so the turn is
# 436 "data/maps/OlivineCity_House1/scripts.pory"
	@ guarded by a measurement, never derived from a live position.
# 437 "data/maps/OlivineCity_House1/scripts.pory"
	getplayerxy VAR_0x8005, VAR_0x8006
# 438 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8005, 4, OlivineCity_House1_EventScript_ReunionTestRelease
# 439 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ne VAR_0x8006, 7, OlivineCity_House1_EventScript_ReunionTestRelease
# 440 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
# 441 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionTestRelease::
# 442 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 443 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_TEMP_4
# 444 "data/maps/OlivineCity_House1/scripts.pory"
	addobject LOCALID_OLIVINE_HOUSE1_PARTNER
# 445 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 446 "data/maps/OlivineCity_House1/scripts.pory"
	playmoncry VAR_TEMP_2, CRY_MODE_ENCOUNTER
# 447 "data/maps/OlivineCity_House1/scripts.pory"
	waitmoncry
# 448 "data/maps/OlivineCity_House1/scripts.pory"
	delay 20
# 449 "data/maps/OlivineCity_House1/scripts.pory"
	@ Anabel arms the calibration mode on the portable unit in her hands.
# 450 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_ANABEL, DIR_SOUTH
# 451 "data/maps/OlivineCity_House1/scripts.pory"
	fadeoutbgm 4
# 452 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTestStart, MSGBOX_DEFAULT
# 453 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 454 "data/maps/OlivineCity_House1/scripts.pory"
	@ The partner answers the MODULE, not the player: from (6,7) toward Anabel
# 455 "data/maps/OlivineCity_House1/scripts.pory"
	@ at (7,5), north is the walkable component. One brief glow; the lights
# 456 "data/maps/OlivineCity_House1/scripts.pory"
	@ level for a few moments and go out normally.
# 457 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_PARTNER, DIR_NORTH
# 458 "data/maps/OlivineCity_House1/scripts.pory"
	delay 20
# 459 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 460 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 461 "data/maps/OlivineCity_House1/scripts.pory"
	delay 30
# 462 "data/maps/OlivineCity_House1/scripts.pory"
	@ fadeinbgm, not fadedefaultbgm: fadeoutbgm PAUSED the house music, and
# 463 "data/maps/OlivineCity_House1/scripts.pory"
	@ fadedefaultbgm is a no-op when the track is already the map's - the
# 464 "data/maps/OlivineCity_House1/scripts.pory"
	@ music would stay paused, and the next warp that fades it would hang.
# 465 "data/maps/OlivineCity_House1/scripts.pory"
	fadeinbgm 4
# 466 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_KUKUI, Common_Movement_ExclamationMark
# 467 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_KUKUI
# 468 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTestResult, MSGBOX_DEFAULT
# 469 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 470 "data/maps/OlivineCity_House1/scripts.pory"
	@ One short reaction, not a round of compliments (V2 section 7). Gladion
# 471 "data/maps/OlivineCity_House1/scripts.pory"
	@ and Silvally already face east, straight at the partner; Lillie's
# 472 "data/maps/OlivineCity_House1/scripts.pory"
	@ reaction is a gesture, and Ninetales is turned with her by template.
# 473 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionGladionPartner, MSGBOX_DEFAULT
# 474 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 475 "data/maps/OlivineCity_House1/scripts.pory"
	@ Ninetales already faces east, at the partner: a small step in place is
# 476 "data/maps/OlivineCity_House1/scripts.pory"
	@ its turn toward it. Then Lusamine packs the base - only now, after
# 477 "data/maps/OlivineCity_House1/scripts.pory"
	@ Anabel switched the module off (V2 section 7).
# 478 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LILLIE, OlivineCity_House1_Movement_LillieHeart
# 479 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_NINETALES, OlivineCity_House1_Movement_NinetalesLooks
# 480 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LILLIE
# 481 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_NINETALES
# 482 "data/maps/OlivineCity_House1/scripts.pory"
	applymovement LOCALID_OLIVINE_HOUSE1_LUSAMINE, OlivineCity_House1_Movement_LusaminePacks
# 483 "data/maps/OlivineCity_House1/scripts.pory"
	waitmovement LOCALID_OLIVINE_HOUSE1_LUSAMINE
# 484 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionAssignments, MSGBOX_DEFAULT
# 485 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 486 "data/maps/OlivineCity_House1/scripts.pory"
	@ Looker was pointing at the table map since the opening; he comes back to
# 487 "data/maps/OlivineCity_House1/scripts.pory"
	@ the room to hand over the pass. Fixed direction: south is the door side,
# 488 "data/maps/OlivineCity_House1/scripts.pory"
	@ where the player stands on the trigger path.
# 489 "data/maps/OlivineCity_House1/scripts.pory"
	turnobject LOCALID_OLIVINE_HOUSE1_LOOKER, DIR_SOUTH
# 490 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicket, MSGBOX_DEFAULT
# 491 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 492 "data/maps/OlivineCity_House1/scripts.pory"
	@ Idempotent delivery (V2 section 8): if the pass is somehow already in
# 493 "data/maps/OlivineCity_House1/scripts.pory"
	@ the bag, do not duplicate it. Possession is the fact that matters, and
# 494 "data/maps/OlivineCity_House1/scripts.pory"
	@ state 12 follows it either way.
# 495 "data/maps/OlivineCity_House1/scripts.pory"
	checkitem ITEM_SUN_MOON_TICKET
# 496 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, OlivineCity_House1_EventScript_ReunionTicketDone
# 497 "data/maps/OlivineCity_House1/scripts.pory"
	giveitem ITEM_SUN_MOON_TICKET
# 498 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionTicketDone::
# 499 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionTicketUse, MSGBOX_DEFAULT
# 500 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 501 "data/maps/OlivineCity_House1/scripts.pory"
	@ Recall the scene partner - its OWN flag, so removeobject is safe and
# 502 "data/maps/OlivineCity_House1/scripts.pory"
	@ touches nobody else's.
# 503 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreenswapbuffers FADE_TO_WHITE
# 504 "data/maps/OlivineCity_House1/scripts.pory"
	removeobject LOCALID_OLIVINE_HOUSE1_PARTNER
# 505 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreenswapbuffers FADE_FROM_WHITE
# 506 "data/maps/OlivineCity_House1/scripts.pory"
	delay 10
# 507 "data/maps/OlivineCity_House1/scripts.pory"
	fadescreen FADE_TO_BLACK                     @ a warp reloads the map right after
# 508 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED   @ handoff; NEVER cleared
# 509 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 12           @ invariant: flag and var together
# 510 "data/maps/OlivineCity_House1/scripts.pory"
	@ Reload in place: ON_TRANSITION hides the visitors (they went ahead to
# 511 "data/maps/OlivineCity_House1/scripts.pory"
	@ the voyage preparations), Looker and Anabel stay - they remain at the
# 512 "data/maps/OlivineCity_House1/scripts.pory"
	@ base until the altar document moves them - and the follower comes back
# 513 "data/maps/OlivineCity_House1/scripts.pory"
	@ (undoes hidefollower).
# 514 "data/maps/OlivineCity_House1/scripts.pory"
	@ (4,7), not (4,8): do not respawn the player on the room's only warp
# 515 "data/maps/OlivineCity_House1/scripts.pory"
	@ tile. (4,7) is guaranteed free, because by state 12 the cast is hidden.
# 516 "data/maps/OlivineCity_House1/scripts.pory"
	@ The frame trigger fires again after this load with VAR_TEMP_1 zeroed,
# 517 "data/maps/OlivineCity_House1/scripts.pory"
	@ but dies twice over: the player is not at (4,8) AND state 12 matches no
# 518 "data/maps/OlivineCity_House1/scripts.pory"
	@ goto_if_eq in its list.
# 519 "data/maps/OlivineCity_House1/scripts.pory"
	warpsilent MAP_OLIVINE_CITY_HOUSE1, 4, 7
# 520 "data/maps/OlivineCity_House1/scripts.pory"
	waitstate
# 521 "data/maps/OlivineCity_House1/scripts.pory"
	releaseall
# 522 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 523 "data/maps/OlivineCity_House1/scripts.pory"

# 524 "data/maps/OlivineCity_House1/scripts.pory"
@ Key Items pocket full - the only way the delivery could fail, prevented up
# 525 "data/maps/OlivineCity_House1/scripts.pory"
@ front. Nothing has happened yet: no partner out, no flag, no state past 11.
# 526 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionNoRoom::
# 527 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_ReunionNoRoom, MSGBOX_DEFAULT
# 528 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 11
# 529 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionReleaseEnd
# 530 "data/maps/OlivineCity_House1/scripts.pory"

# 531 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_End::
# 532 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 533 "data/maps/OlivineCity_House1/scripts.pory"

# 534 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerApproach:
# 535 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 536 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 537 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 538 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 539 "data/maps/OlivineCity_House1/scripts.pory"

# 540 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelApproach:
# 541 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 542 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 543 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 544 "data/maps/OlivineCity_House1/scripts.pory"
	walk_left
# 545 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 546 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 547 "data/maps/OlivineCity_House1/scripts.pory"

# 548 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LookerReturn:
# 549 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 550 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 551 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 552 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 553 "data/maps/OlivineCity_House1/scripts.pory"

# 554 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_AnabelReturn:
# 555 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 556 "data/maps/OlivineCity_House1/scripts.pory"
	walk_right
# 557 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 558 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 559 "data/maps/OlivineCity_House1/scripts.pory"
	face_down
# 560 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 561 "data/maps/OlivineCity_House1/scripts.pory"

# 562 "data/maps/OlivineCity_House1/scripts.pory"
@ Reunion V2: the player's one step in, (4,8) -> (4,7). Ends facing up, at
# 563 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker by the table. Same tile the ending respawns on.
# 564 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_PlayerEnter:
# 565 "data/maps/OlivineCity_House1/scripts.pory"
	walk_up
# 566 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 567 "data/maps/OlivineCity_House1/scripts.pory"

# 568 "data/maps/OlivineCity_House1/scripts.pory"
@ Lusamine opens the stabilizer case: one step down the east wall,
# 569 "data/maps/OlivineCity_House1/scripts.pory"
@ (9,6) -> (9,7), measured free, then she faces the case at Kukui's side.
# 570 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LusamineToCase:
# 571 "data/maps/OlivineCity_House1/scripts.pory"
	walk_down
# 572 "data/maps/OlivineCity_House1/scripts.pory"
	face_left
# 573 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 574 "data/maps/OlivineCity_House1/scripts.pory"

# 575 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie's reaction to the partner is a gesture, not a speech (V2 section 7).
# 576 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LillieHeart:
# 577 "data/maps/OlivineCity_House1/scripts.pory"
	emote_heart
# 578 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 579 "data/maps/OlivineCity_House1/scripts.pory"

# 580 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_NinetalesLooks:
# 581 "data/maps/OlivineCity_House1/scripts.pory"
	face_right
# 582 "data/maps/OlivineCity_House1/scripts.pory"
	walk_in_place_slow_right
# 583 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 584 "data/maps/OlivineCity_House1/scripts.pory"

# 585 "data/maps/OlivineCity_House1/scripts.pory"
@ Lusamine at (9,7), facing the case at Kukui's side (west): closing it.
# 586 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Movement_LusaminePacks:
# 587 "data/maps/OlivineCity_House1/scripts.pory"
	walk_in_place_slow_left
# 588 "data/maps/OlivineCity_House1/scripts.pory"
	walk_in_place_slow_left
# 589 "data/maps/OlivineCity_House1/scripts.pory"
	step_end
# 590 "data/maps/OlivineCity_House1/scripts.pory"

# 591 "data/maps/OlivineCity_House1/scripts.pory"
@ Shared by the arrival scene and by both object scripts in states 2, 4, 6
# 592 "data/maps/OlivineCity_House1/scripts.pory"
@ and 8, so a briefing can never be skipped by entering from an odd tile. It is
# 593 "data/maps/OlivineCity_House1/scripts.pory"
@ the ONE place that moves flag and var, and it moves them together.
# 594 "data/maps/OlivineCity_House1/scripts.pory"
@ Invariants:
# 595 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_BLACKTHORN  set <=> VAR_RIFT_MISSIONS_STATE == 3
# 596 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_MAHOGANY    set <=> VAR_RIFT_MISSIONS_STATE == 5
# 597 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_CHERRYGROVE set <=> VAR_RIFT_MISSIONS_STATE == 7
# 598 "data/maps/OlivineCity_House1/scripts.pory"
@   FLAG_EVENT_ULTRABEAST_NEWBARK     set <=> VAR_RIFT_MISSIONS_STATE == 9
# 599 "data/maps/OlivineCity_House1/scripts.pory"
@ The four are mutually exclusive because the var holds one value.
# 600 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10 is the END of the chain: it opens no mission, it means "four done,
# 601 "data/maps/OlivineCity_House1/scripts.pory"
@ the Olivine reunion pending" (design section 7).
# 602 "data/maps/OlivineCity_House1/scripts.pory"
@ A goto inside a script reached by call is safe: call pushes the return
# 603 "data/maps/OlivineCity_House1/scripts.pory"
@ address and return pops it, however many gotos happened in between.
# 604 "data/maps/OlivineCity_House1/scripts.pory"
@ Highest state first, so the block reads newest mission to oldest.
# 605 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalk::
# 606 "data/maps/OlivineCity_House1/scripts.pory"
	clearflag FLAG_RIFT_LOOKER_SUMMONS          @ the invitation has been answered
# 607 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_BriefingTalkM4
# 608 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_BriefingTalkM3
# 609 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_BriefingTalkM2
# 610 "data/maps/OlivineCity_House1/scripts.pory"
	@ falls through to M1 (state 2)
# 611 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM1::
# 612 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingWelcome, MSGBOX_DEFAULT
# 613 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingAnabel, MSGBOX_DEFAULT
# 614 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingWormholes, MSGBOX_DEFAULT
# 615 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingBlackthorn, MSGBOX_DEFAULT
# 616 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingRequest, MSGBOX_DEFAULT
# 617 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 618 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_BLACKTHORN
# 619 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 3
# 620 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 621 "data/maps/OlivineCity_House1/scripts.pory"

# 622 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM2::
# 623 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Welcome, MSGBOX_DEFAULT
# 624 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 625 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Link, MSGBOX_DEFAULT
# 626 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 627 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Town, MSGBOX_DEFAULT
# 628 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 629 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM2Meet, MSGBOX_DEFAULT
# 630 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 631 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_MAHOGANY
# 632 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 5
# 633 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 634 "data/maps/OlivineCity_House1/scripts.pory"

# 635 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM3::
# 636 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3Welcome, MSGBOX_DEFAULT
# 637 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3Evidence, MSGBOX_DEFAULT
# 638 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3Plan, MSGBOX_DEFAULT
# 639 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM3Safety, MSGBOX_DEFAULT
# 640 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 641 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_CHERRYGROVE
# 642 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 7
# 643 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 644 "data/maps/OlivineCity_House1/scripts.pory"

# 645 "data/maps/OlivineCity_House1/scripts.pory"
@ New Bark V2 script, section 4: five boxes, one speaker each, played as
# 646 "data/maps/OlivineCity_House1/scripts.pory"
@ consecutive msgbox with no closemessage between them so the box never drops
# 647 "data/maps/OlivineCity_House1/scripts.pory"
@ and the plaque changes with the speaker (TrySetSpeakerFromMessage reads only
# 648 "data/maps/OlivineCity_House1/scripts.pory"
@ the start of each message). Every part stays far below the 1000-byte
# 649 "data/maps/OlivineCity_House1/scripts.pory"
@ gStringVar4 limit that froze the old ~2000-byte version of this briefing.
# 650 "data/maps/OlivineCity_House1/scripts.pory"
@ The resource (Aether's containment equipment, Lusamine bringing it herself) is
# 651 "data/maps/OlivineCity_House1/scripts.pory"
@ presented HERE, before it is used, and nothing promises it will work. No item
# 652 "data/maps/OlivineCity_House1/scripts.pory"
@ is handed out: the old "Take these" is gone. Anabel does not retell her Faller
# 653 "data/maps/OlivineCity_House1/scripts.pory"
@ condition - that was Cherrygrove's aftermath.
# 654 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_BriefingTalkM4::
# 655 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Evidence, MSGBOX_DEFAULT
# 656 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Comparison, MSGBOX_DEFAULT
# 657 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Safety, MSGBOX_DEFAULT
# 658 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Containment, MSGBOX_DEFAULT
# 659 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_BriefingM4Plan, MSGBOX_DEFAULT
# 660 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 661 "data/maps/OlivineCity_House1/scripts.pory"
	setflag FLAG_EVENT_ULTRABEAST_NEWBARK
# 662 "data/maps/OlivineCity_House1/scripts.pory"
	setvar VAR_RIFT_MISSIONS_STATE, 9
# 663 "data/maps/OlivineCity_House1/scripts.pory"
	return
# 664 "data/maps/OlivineCity_House1/scripts.pory"

# 665 "data/maps/OlivineCity_House1/scripts.pory"
@ Branch order matters: 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, then >= 12. NEVER
# 666 "data/maps/OlivineCity_House1/scripts.pory"
@ leave a "goto_if_ge VAR_RIFT_MISSIONS_STATE, 4", ", 6", ", 8" or ", 10"
# 667 "data/maps/OlivineCity_House1/scripts.pory"
@ here - any one of them would swallow the states above it. This has now
# 668 "data/maps/OlivineCity_House1/scripts.pory"
@ happened THREE times: Mission 3 had to delete a "goto_if_ge ..., 6" left
# 669 "data/maps/OlivineCity_House1/scripts.pory"
@ behind by Mission 2, Mission 4 had to move a "goto_if_ge ..., 8" left behind
# 670 "data/maps/OlivineCity_House1/scripts.pory"
@ by Mission 3, and the pre-Necrozma reunion had to split the
# 671 "data/maps/OlivineCity_House1/scripts.pory"
@ "goto_if_ge ..., 10" Mission 4 left behind, which would have replayed the
# 672 "data/maps/OlivineCity_House1/scripts.pory"
@ whole cutscene at state 11 and kept saying reunion lines at state 12.
# 673 "data/maps/OlivineCity_House1/scripts.pory"
@ Fourth warning, same mistake: a NEW state enters as goto_if_eq, and only the
# 674 "data/maps/OlivineCity_House1/scripts.pory"
@ LAST line of the list may be a goto_if_ge.
# 675 "data/maps/OlivineCity_House1/scripts.pory"
@ States 0-1 fall through to the holiday line.
# 676 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Looker::
# 677 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 678 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 679 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_LookerBrief
# 680 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_LookerGoAhead
# 681 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_LookerBriefIfCalled
# 682 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_LookerGoAheadM2
# 683 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerBriefIfCalled
# 684 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_LookerGoAheadM3
# 685 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_LookerBriefIfCalled
# 686 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_LookerGoAheadM4
# 687 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerReunionIfCalled
# 688 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_LookerRecheck
# 689 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_LookerAltar
# 690 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerHoliday, MSGBOX_DEFAULT
# 691 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 692 "data/maps/OlivineCity_House1/scripts.pory"

# 693 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerBrief::
# 694 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 695 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 696 "data/maps/OlivineCity_House1/scripts.pory"

# 697 "data/maps/OlivineCity_House1/scripts.pory"
@ Waiting for the summons: no briefing, no "go ahead", and nothing about the next
# 698 "data/maps/OlivineCity_House1/scripts.pory"
@ town. He says the one true thing - the reports are not finished - and promises
# 699 "data/maps/OlivineCity_House1/scripts.pory"
@ the telephone call that is the only way forward.
# 700 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerBriefIfCalled::
# 701 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_LookerWaitCall
# 702 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_LookerBrief
# 703 "data/maps/OlivineCity_House1/scripts.pory"

# 704 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerWaitCall::
# 705 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_LookerWaitCallM3
# 706 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_LookerWaitCallM4
# 707 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_LookerWaitCallAltar
# 708 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_WaitForMahoganyCall, MSGBOX_DEFAULT
# 709 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 710 "data/maps/OlivineCity_House1/scripts.pory"

# 711 "data/maps/OlivineCity_House1/scripts.pory"
@ After Mahogany the wait is not idle: Anabel is matching Lillie's pages to her
# 712 "data/maps/OlivineCity_House1/scripts.pory"
@ own recordings, which is the task the street handed them.
# 713 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerWaitCallM3::
# 714 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_WaitForCherrygroveCall, MSGBOX_DEFAULT
# 715 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 716 "data/maps/OlivineCity_House1/scripts.pory"

# 717 "data/maps/OlivineCity_House1/scripts.pory"
@ After Cherrygrove the wait is for Elm's records, which Kukui asked for on the
# 718 "data/maps/OlivineCity_House1/scripts.pory"
@ beach (CHERRYGROVE_ULTRABEAST_SCRIPT_V2.md section 16).
# 719 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerWaitCallM4::
# 720 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_WaitForNewBarkCall, MSGBOX_DEFAULT
# 721 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 722 "data/maps/OlivineCity_House1/scripts.pory"

# 723 "data/maps/OlivineCity_House1/scripts.pory"
@ After New Bark (state 10) the meeting is NOT started just because the state
# 724 "data/maps/OlivineCity_House1/scripts.pory"
@ reached 10: it waits for its own daily call (V2 section 18). Until then the
# 725 "data/maps/OlivineCity_House1/scripts.pory"
@ records are being compared and the participants gathered.
# 726 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerWaitCallAltar::
# 727 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_WaitForAltarCall, MSGBOX_DEFAULT
# 728 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 729 "data/maps/OlivineCity_House1/scripts.pory"

# 730 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerReunionIfCalled::
# 731 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_LookerWaitCall
# 732 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_LookerReunion
# 733 "data/maps/OlivineCity_House1/scripts.pory"

# 734 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAhead::
# 735 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAhead, MSGBOX_DEFAULT
# 736 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 737 "data/maps/OlivineCity_House1/scripts.pory"

# 738 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM2::
# 739 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM2, MSGBOX_DEFAULT
# 740 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 741 "data/maps/OlivineCity_House1/scripts.pory"

# 742 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM3::
# 743 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM3, MSGBOX_DEFAULT
# 744 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 745 "data/maps/OlivineCity_House1/scripts.pory"

# 746 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerGoAheadM4::
# 747 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerGoAheadM4, MSGBOX_DEFAULT
# 748 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 749 "data/maps/OlivineCity_House1/scripts.pory"

# 750 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: the alternative way into the reunion, for a player who somehow
# 751 "data/maps/OlivineCity_House1/scripts.pory"
@ talks to a detective without the frame trigger having staged the scene.
# 752 "data/maps/OlivineCity_House1/scripts.pory"
@ ReunionScene moves only actors on fixed tiles (Lusamine's one measured
# 753 "data/maps/OlivineCity_House1/scripts.pory"
@ step); nothing in it reads the player's position unguarded, so it plays
# 754 "data/maps/OlivineCity_House1/scripts.pory"
@ identically under lock. All that is missing is the player's step in.
# 755 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerReunion::
# 756 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 757 "data/maps/OlivineCity_House1/scripts.pory"

# 758 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11: the retake offer (V2 section 6), never the cutscene again.
# 759 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerRecheck::
# 760 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionResume
# 761 "data/maps/OlivineCity_House1/scripts.pory"

# 762 "data/maps/OlivineCity_House1/scripts.pory"
@ States 12-15: the repeatable orientation to the port (V2 section 10).
# 763 "data/maps/OlivineCity_House1/scripts.pory"
@ Releasing the voyage is persistent: storing the partner after the reunion
# 764 "data/maps/OlivineCity_House1/scripts.pory"
@ revokes nothing - the altar revalidates the team itself (checkspecies at
# 765 "data/maps/OlivineCity_House1/scripts.pory"
@ the rift, altar doc). From 16 on the two are hidden (FLAG_TEMP_2), so no
# 766 "data/maps/OlivineCity_House1/scripts.pory"
@ upper branch is needed here.
# 767 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_LookerAltar::
# 768 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_LookerAltar, MSGBOX_DEFAULT
# 769 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 770 "data/maps/OlivineCity_House1/scripts.pory"

# 771 "data/maps/OlivineCity_House1/scripts.pory"
@ Same branch order as Looker, and the same warning about goto_if_ge.
# 772 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_Anabel::
# 773 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 774 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 775 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 2, OlivineCity_House1_EventScript_AnabelBrief
# 776 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 3, OlivineCity_House1_EventScript_AnabelGoAhead
# 777 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, OlivineCity_House1_EventScript_AnabelBriefIfCalled
# 778 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 5, OlivineCity_House1_EventScript_AnabelGoAheadM2
# 779 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, OlivineCity_House1_EventScript_AnabelBriefIfCalled
# 780 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 7, OlivineCity_House1_EventScript_AnabelGoAheadM3
# 781 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, OlivineCity_House1_EventScript_AnabelBriefIfCalled
# 782 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 9, OlivineCity_House1_EventScript_AnabelGoAheadM4
# 783 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_AnabelReunionIfCalled
# 784 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_AnabelRecheck
# 785 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 12, OlivineCity_House1_EventScript_AnabelAltar
# 786 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelHoliday, MSGBOX_DEFAULT
# 787 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 788 "data/maps/OlivineCity_House1/scripts.pory"

# 789 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelBrief::
# 790 "data/maps/OlivineCity_House1/scripts.pory"
	call OlivineCity_House1_EventScript_BriefingTalk
# 791 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 792 "data/maps/OlivineCity_House1/scripts.pory"

# 793 "data/maps/OlivineCity_House1/scripts.pory"
@ Her own waiting line: the plaque follows the message, so Looker's text cannot
# 794 "data/maps/OlivineCity_House1/scripts.pory"
@ be reused in her mouth.
# 795 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelBriefIfCalled::
# 796 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_AnabelWaitCall
# 797 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_AnabelBrief
# 798 "data/maps/OlivineCity_House1/scripts.pory"

# 799 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelWaitCall::
# 800 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelWaitForCall, MSGBOX_DEFAULT
# 801 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 802 "data/maps/OlivineCity_House1/scripts.pory"

# 803 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelReunionIfCalled::
# 804 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_unset FLAG_RIFT_LOOKER_SUMMONS, OlivineCity_House1_EventScript_AnabelWaitCall
# 805 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_AnabelReunion
# 806 "data/maps/OlivineCity_House1/scripts.pory"

# 807 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAhead::
# 808 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAhead, MSGBOX_DEFAULT
# 809 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 810 "data/maps/OlivineCity_House1/scripts.pory"

# 811 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM2::
# 812 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM2, MSGBOX_DEFAULT
# 813 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 814 "data/maps/OlivineCity_House1/scripts.pory"

# 815 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM3::
# 816 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM3, MSGBOX_DEFAULT
# 817 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 818 "data/maps/OlivineCity_House1/scripts.pory"

# 819 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelGoAheadM4::
# 820 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelGoAheadM4, MSGBOX_DEFAULT
# 821 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 822 "data/maps/OlivineCity_House1/scripts.pory"

# 823 "data/maps/OlivineCity_House1/scripts.pory"
@ Anabel does NOT sell Beast Balls, here or anywhere: she asked Kurt to make
# 824 "data/maps/OlivineCity_House1/scripts.pory"
@ them (altar doc, revision 2), and the one she keeps is the scripted capture
# 825 "data/maps/OlivineCity_House1/scripts.pory"
@ of the altar's Act IV. The old "she sells from state 4 on" pendency is
# 826 "data/maps/OlivineCity_House1/scripts.pory"
@ closed - it became Kurt's craft system.
# 827 "data/maps/OlivineCity_House1/scripts.pory"
@ State 10: same entry into the reunion as Looker's, see the note there.
# 828 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelReunion::
# 829 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionScene
# 830 "data/maps/OlivineCity_House1/scripts.pory"

# 831 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelRecheck::
# 832 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReunionResume
# 833 "data/maps/OlivineCity_House1/scripts.pory"

# 834 "data/maps/OlivineCity_House1/scripts.pory"
@ States 12-15, same as LookerAltar: her half of the orientation.
# 835 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_AnabelAltar::
# 836 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_AnabelAltar, MSGBOX_DEFAULT
# 837 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 838 "data/maps/OlivineCity_House1/scripts.pory"

# 839 "data/maps/OlivineCity_House1/scripts.pory"
@ The four visitors. They exist to be talked to in state 11, the only state in
# 840 "data/maps/OlivineCity_House1/scripts.pory"
@ which the player walks the room with everyone present - in state 12 they are
# 841 "data/maps/OlivineCity_House1/scripts.pory"
@ not here to be talked to, and in state 10 the cutscene runs on arrival. So
# 842 "data/maps/OlivineCity_House1/scripts.pory"
@ they need no branch on the var below 16: one box each, V2 section 9 - short
# 843 "data/maps/OlivineCity_House1/scripts.pory"
@ preparation notes, none of them carrying information the main scene needs.
# 844 "data/maps/OlivineCity_House1/scripts.pory"
@ Ninetales and Silvally have "script": "NULL" (design 3.2, skill
# 845 "data/maps/OlivineCity_House1/scripts.pory"
@ parceiro-pokemon-de-npc): they are their owners' partners out of the ball,
# 846 "data/maps/OlivineCity_House1/scripts.pory"
@ share FLAG_TEMP_1 with them, and come and go together. V2 section 9 keeps
# 847 "data/maps/OlivineCity_House1/scripts.pory"
@ NULL as complete: the optional cry interaction is a possible evolution.
# 848 "data/maps/OlivineCity_House1/scripts.pory"
@ The three who come back. There is NO battle anywhere in this room in the
# 849 "data/maps/OlivineCity_House1/scripts.pory"
@ post-game: this is the place where they are not working.
# 850 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLusamine::
# 851 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 852 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 853 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseLusaminePost
# 854 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLusamine, MSGBOX_DEFAULT
# 855 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 856 "data/maps/OlivineCity_House1/scripts.pory"

# 857 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseLusaminePost::
# 858 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseLusaminePost, MSGBOX_DEFAULT
# 859 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 860 "data/maps/OlivineCity_House1/scripts.pory"

# 861 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionLillie::
# 862 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 863 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 864 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseLilliePost
# 865 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleLillie, MSGBOX_DEFAULT
# 866 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 867 "data/maps/OlivineCity_House1/scripts.pory"

# 868 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseLilliePost::
# 869 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseLilliePost, MSGBOX_DEFAULT
# 870 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 871 "data/maps/OlivineCity_House1/scripts.pory"

# 872 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionGladion::
# 873 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 874 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 875 "data/maps/OlivineCity_House1/scripts.pory"
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HouseGladionPost
# 876 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleGladion, MSGBOX_DEFAULT
# 877 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 878 "data/maps/OlivineCity_House1/scripts.pory"

# 879 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_HouseGladionPost::
# 880 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_HouseGladionPost, MSGBOX_DEFAULT
# 881 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 882 "data/maps/OlivineCity_House1/scripts.pory"

# 883 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReunionKukui::
# 884 "data/maps/OlivineCity_House1/scripts.pory"
	lock
# 885 "data/maps/OlivineCity_House1/scripts.pory"
	faceplayer
# 886 "data/maps/OlivineCity_House1/scripts.pory"
	msgbox OlivineCity_House1_Text_IdleKukui, MSGBOX_DEFAULT
# 887 "data/maps/OlivineCity_House1/scripts.pory"
	goto OlivineCity_House1_EventScript_ReleaseEnd
# 888 "data/maps/OlivineCity_House1/scripts.pory"

# 889 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_EventScript_ReleaseEnd::
# 890 "data/maps/OlivineCity_House1/scripts.pory"
	closemessage
# 891 "data/maps/OlivineCity_House1/scripts.pory"
	release
# 892 "data/maps/OlivineCity_House1/scripts.pory"
	end
# 893 "data/maps/OlivineCity_House1/scripts.pory"

# 894 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 1 briefing (script revision V2, 25/09/2026). FIVE texts and not one,
# 895 "data/maps/OlivineCity_House1/scripts.pory"
@ because each block has exactly one speaker and the plaque has to change with
# 896 "data/maps/OlivineCity_House1/scripts.pory"
@ it; they are played as consecutive msgbox with no closemessage between them,
# 897 "data/maps/OlivineCity_House1/scripts.pory"
@ so the box never drops and the scene reads as one conversation. Each part
# 898 "data/maps/OlivineCity_House1/scripts.pory"
@ MUST begin with its own {SPEAKER ...}: TrySetSpeakerFromMessage only reads
# 899 "data/maps/OlivineCity_House1/scripts.pory"
@ the start of each message.
# 900 "data/maps/OlivineCity_House1/scripts.pory"
@ It names Clair and the unfamiliar Pokemon in her street and nothing else:
# 901 "data/maps/OlivineCity_House1/scripts.pory"
@ Gladion, the two Ultra Beasts and the identity of the creature are the
# 902 "data/maps/OlivineCity_House1/scripts.pory"
@ surprises of the scene in Blackthorn, so they are never mentioned here. And
# 903 "data/maps/OlivineCity_House1/scripts.pory"
@ nobody names the creature from a description over the telephone.
# 904 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingWelcome:
# 905 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}!\n"
# 906 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Thank you for coming.\p"
# 907 "data/maps/OlivineCity_House1/scripts.pory"
	.string "This is Anabel. She's in\n"
# 908 "data/maps/OlivineCity_House1/scripts.pory"
	.string "charge of our investigation.$"
# 909 "data/maps/OlivineCity_House1/scripts.pory"

# 910 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingAnabel:
# 911 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We've been tracking\n"
# 912 "data/maps/OlivineCity_House1/scripts.pory"
	.string "distortions in Johto.\p"
# 913 "data/maps/OlivineCity_House1/scripts.pory"
	.string "They resemble the Ultra\n"
# 914 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Wormholes we encountered in\l"
# 915 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Alola.$"
# 916 "data/maps/OlivineCity_House1/scripts.pory"

# 917 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingWormholes:
# 918 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Passages to other\n"
# 919 "data/maps/OlivineCity_House1/scripts.pory"
	.string "worlds.\p"
# 920 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Sometimes Pokémon come\n"
# 921 "data/maps/OlivineCity_House1/scripts.pory"
	.string "through them.\p"
# 922 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We call those Pokémon Ultra\n"
# 923 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Beasts.\p"
# 924 "data/maps/OlivineCity_House1/scripts.pory"
	.string "They can be dangerous when\n"
# 925 "data/maps/OlivineCity_House1/scripts.pory"
	.string "displaced.$"
# 926 "data/maps/OlivineCity_House1/scripts.pory"

# 927 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingBlackthorn:
# 928 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Clair called from\n"
# 929 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn.\p"
# 930 "data/maps/OlivineCity_House1/scripts.pory"
	.string "An unfamiliar Pokémon is in\n"
# 931 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the street.\p"
# 932 "data/maps/OlivineCity_House1/scripts.pory"
	.string "She's keeping it away from the\n"
# 933 "data/maps/OlivineCity_House1/scripts.pory"
	.string "houses, but the readings are\l"
# 934 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rising.$"
# 935 "data/maps/OlivineCity_House1/scripts.pory"

# 936 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingRequest:
# 937 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We need your help\n"
# 938 "data/maps/OlivineCity_House1/scripts.pory"
	.string "protecting the town.\p"
# 939 "data/maps/OlivineCity_House1/scripts.pory"
	.string "And, if we can, the Pokémon\n"
# 940 "data/maps/OlivineCity_House1/scripts.pory"
	.string "too.\p"
# 941 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Meet us by the Pokémon\n"
# 942 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center.\p"
# 943 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bring a team ready for a\n"
# 944 "data/maps/OlivineCity_House1/scripts.pory"
	.string "difficult battle.$"
# 945 "data/maps/OlivineCity_House1/scripts.pory"

# 946 "data/maps/OlivineCity_House1/scripts.pory"
@ Continuity: the Blackthorn hook names no place on purpose ("the moment
# 947 "data/maps/OlivineCity_House1/scripts.pory"
@ something opens, you will be the first to know"). This briefing is that
# 948 "data/maps/OlivineCity_House1/scripts.pory"
@ moment: Mahogany is news to the player here.
# 949 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 2 briefing: final text (22/09/2026), continuity updated for script
# 950 "data/maps/OlivineCity_House1/scripts.pory"
@ revision V2 (25/09/2026). It names Pryce's call and the blackout and nothing
# 951 "data/maps/OlivineCity_House1/scripts.pory"
@ else: Lillie and the evacuation (Pryce's own line) are what the player finds
# 952 "data/maps/OlivineCity_House1/scripts.pory"
@ in Mahogany, so they are never mentioned here.
# 953 "data/maps/OlivineCity_House1/scripts.pory"
@ What V2 changed: Necrozma is no longer a secret - Gladion named it in
# 954 "data/maps/OlivineCity_House1/scripts.pory"
@ Blackthorn - so Anabel calls it by name, and the thing she is looking for is
# 955 "data/maps/OlivineCity_House1/scripts.pory"
@ already stated: the beasts stayed tied to the rift, and the link is what has
# 956 "data/maps/OlivineCity_House1/scripts.pory"
@ to be cut. Mahogany's barrier and Lillie's test answer a problem the player
# 957 "data/maps/OlivineCity_House1/scripts.pory"
@ has already watched happen.
# 958 "data/maps/OlivineCity_House1/scripts.pory"
@ V3: this briefing starts from Blackthorn, not from a fresh mystery. Gladion
# 959 "data/maps/OlivineCity_House1/scripts.pory"
@ named Necrozma there, so nobody is coy about it here; what the group does NOT
# 960 "data/maps/OlivineCity_House1/scripts.pory"
@ have is any record of that creature collecting Ultra Beasts, and that gap is
# 961 "data/maps/OlivineCity_House1/scripts.pory"
@ the reason they go. One speaker per box, and no hour of the day anywhere:
# 962 "data/maps/OlivineCity_House1/scripts.pory"
@ the blackout is lamps and machines, not darkness.
# 963 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Welcome:
# 964 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! Our holiday\n"
# 965 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reading has finally proved\l"
# 966 "data/maps/OlivineCity_House1/scripts.pory"
	.string "useful.\p"
# 967 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We've compared Gladion's\n"
# 968 "data/maps/OlivineCity_House1/scripts.pory"
	.string "account with the Alola records.\p"
# 969 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Necrozma absorbs light.\p"
# 970 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We found nothing about it\n"
# 971 "data/maps/OlivineCity_House1/scripts.pory"
	.string "taking Ultra Beasts.$"
# 972 "data/maps/OlivineCity_House1/scripts.pory"

# 973 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Link:
# 974 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The rift kept them\n"
# 975 "data/maps/OlivineCity_House1/scripts.pory"
	.string "connected in Blackthorn.\p"
# 976 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We need a way to cut that\n"
# 977 "data/maps/OlivineCity_House1/scripts.pory"
	.string "connection.$"
# 978 "data/maps/OlivineCity_House1/scripts.pory"

# 979 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Town:
# 980 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The power is out in\n"
# 981 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mahogany.\p"
# 982 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Two Pokémon have been\n"
# 983 "data/maps/OlivineCity_House1/scripts.pory"
	.string "appearing in the street.\p"
# 984 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pryce is sheltering the\n"
# 985 "data/maps/OlivineCity_House1/scripts.pory"
	.string "residents in his Gym.$"
# 986 "data/maps/OlivineCity_House1/scripts.pory"

# 987 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM2Meet:
# 988 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}The readings match\n"
# 989 "data/maps/OlivineCity_House1/scripts.pory"
	.string "another rupture.\p"
# 990 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We haven't confirmed Necrozma\n"
# 991 "data/maps/OlivineCity_House1/scripts.pory"
	.string "there yet.\p"
# 992 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Meet us by the Pokémon Center.$"
# 993 "data/maps/OlivineCity_House1/scripts.pory"

# 994 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 3 briefing (CHERRYGROVE_ULTRABEAST_SCRIPT_V2.md section 4). The call
# 995 "data/maps/OlivineCity_House1/scripts.pory"
@ already named Cherrygrove; this is where the plan is. Kukui is named because
# 996 "data/maps/OlivineCity_House1/scripts.pory"
@ he is the one who reported it, and introduced by his profession only - the
# 997 "data/maps/OlivineCity_House1/scripts.pory"
@ player's earlier meetings with him are not presumed. Necrozma is known since
# 998 "data/maps/OlivineCity_House1/scripts.pory"
@ Blackthorn; what is new is Lillie's note of a PAUSE before it reached over the
# 999 "data/maps/OlivineCity_House1/scripts.pory"
@ ice in Mahogany, which is a hypothesis, not a promise. Four boxes, one speaker
# 1000 "data/maps/OlivineCity_House1/scripts.pory"
@ each, played with no closemessage between them.
# 1001 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3Welcome:
# 1002 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Professor Kukui reported\n"
# 1003 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the disturbance. He studies\l"
# 1004 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pokémon moves in Alola.\p"
# 1005 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Fortunately for us, he was\n"
# 1006 "data/maps/OlivineCity_House1/scripts.pory"
	.string "visiting Johto.\p"
# 1007 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Unfortunately for his holiday.$"
# 1008 "data/maps/OlivineCity_House1/scripts.pory"

# 1009 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3Evidence:
# 1010 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Lillie marked a pause\n"
# 1011 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before Necrozma reached over\l"
# 1012 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the ice.\p"
# 1013 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It matches a change in my\n"
# 1014 "data/maps/OlivineCity_House1/scripts.pory"
	.string "recording.\p"
# 1015 "data/maps/OlivineCity_House1/scripts.pory"
	.string "If it happens again, we may\n"
# 1016 "data/maps/OlivineCity_House1/scripts.pory"
	.string "have time to act before it\l"
# 1017 "data/maps/OlivineCity_House1/scripts.pory"
	.string "takes them.$"
# 1018 "data/maps/OlivineCity_House1/scripts.pory"

# 1019 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3Plan:
# 1020 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We'll weaken the Ultra\n"
# 1021 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Beasts, then try to secure one\l"
# 1022 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before it moves.\p"
# 1023 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll watch Necrozma.\n"
# 1024 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Kukui will help you hold the\l"
# 1025 "data/maps/OlivineCity_House1/scripts.pory"
	.string "shore.$"
# 1026 "data/maps/OlivineCity_House1/scripts.pory"

# 1027 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM3Safety:
# 1028 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The residents are sheltered\n"
# 1029 "data/maps/OlivineCity_House1/scripts.pory"
	.string "at Violet Gym. The Pokémon\l"
# 1030 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center is still available.\p"
# 1031 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Meet us on Cherrygrove's\n"
# 1032 "data/maps/OlivineCity_House1/scripts.pory"
	.string "northwest shore.$"
# 1033 "data/maps/OlivineCity_House1/scripts.pory"

# 1034 "data/maps/OlivineCity_House1/scripts.pory"
@ Mission 4 briefing (NEWBARK_ULTRABEAST_SCRIPT_V2.md section 4).
# 1035 "data/maps/OlivineCity_House1/scripts.pory"
@ BRIDGE FROM CHERRYGROVE V2 (section 17 of that script): Kukui asked Elm for
# 1036 "data/maps/OlivineCity_House1/scripts.pory"
@ his readings on the beach -> Elm checked six weeks of his own history and
# 1037 "data/maps/OlivineCity_House1/scripts.pory"
@ answered -> Anabel and Looker compared -> Looker called. The discovery is
# 1038 "data/maps/OlivineCity_House1/scripts.pory"
@ Elm's; he is never treated as someone who ignored three monsters for six
# 1039 "data/maps/OlivineCity_House1/scripts.pory"
@ weeks. Pair: CherrygroveCity_Text_UBKukuiElm/UBHookKukui and
# 1040 "data/maps/OlivineCity_House1/scripts.pory"
@ RiftMissions_Text_LookerCallM4.
# 1041 "data/maps/OlivineCity_House1/scripts.pory"
@ The call does not say Mom is surrounded; this briefing says she is helping
# 1042 "data/maps/OlivineCity_House1/scripts.pory"
@ prepare the shelter. The three openings have not happened yet.
# 1043 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Evidence:
# 1044 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Elm sent the records Kukui\n"
# 1045 "data/maps/OlivineCity_House1/scripts.pory"
	.string "requested. Some go back six\l"
# 1046 "data/maps/OlivineCity_House1/scripts.pory"
	.string "weeks.\p"
# 1047 "data/maps/OlivineCity_House1/scripts.pory"
	.string "He checked the equipment.\n"
# 1048 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The pulses kept coming back.$"
# 1049 "data/maps/OlivineCity_House1/scripts.pory"

# 1050 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Comparison:
# 1051 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}They match our recordings.\n"
# 1052 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The latest readings are\l"
# 1053 "data/maps/OlivineCity_House1/scripts.pory"
	.string "stronger, and three points\l"
# 1054 "data/maps/OlivineCity_House1/scripts.pory"
	.string "are responding.\p"
# 1055 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We need to clear the area\n"
# 1056 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before they open fully.$"
# 1057 "data/maps/OlivineCity_House1/scripts.pory"

# 1058 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Safety:
# 1059 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Your mother is helping\n"
# 1060 "data/maps/OlivineCity_House1/scripts.pory"
	.string "prepare the lab. There's room\l"
# 1061 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to shelter the residents.\p"
# 1062 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll meet you outside your\n"
# 1063 "data/maps/OlivineCity_House1/scripts.pory"
	.string "house.$"
# 1064 "data/maps/OlivineCity_House1/scripts.pory"

# 1065 "data/maps/OlivineCity_House1/scripts.pory"
@ The resource is named before it is used, and Lusamine's presence is not a
# 1066 "data/maps/OlivineCity_House1/scripts.pory"
@ coincidence: Anabel asked Aether for it.
# 1067 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Containment:
# 1068 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Timing wasn't enough at\n"
# 1069 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove. We need to\l"
# 1070 "data/maps/OlivineCity_House1/scripts.pory"
	.string "interrupt the connection.\p"
# 1071 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I asked Aether for containment\n"
# 1072 "data/maps/OlivineCity_House1/scripts.pory"
	.string "equipment. Lusamine is\l"
# 1073 "data/maps/OlivineCity_House1/scripts.pory"
	.string "bringing it herself.$"
# 1074 "data/maps/OlivineCity_House1/scripts.pory"

# 1075 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_BriefingM4Plan:
# 1076 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We'll hold the three fronts,\n"
# 1077 "data/maps/OlivineCity_House1/scripts.pory"
	.string "then isolate the weakened\l"
# 1078 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pokémon.\p"
# 1079 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Prepare your team before you\n"
# 1080 "data/maps/OlivineCity_House1/scripts.pory"
	.string "join us.$"
# 1081 "data/maps/OlivineCity_House1/scripts.pory"

# 1082 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerHoliday:
# 1083 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}A fine place for a\n"
# 1084 "data/maps/OlivineCity_House1/scripts.pory"
	.string "holiday!\p"
# 1085 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Though I seem to be spending\n"
# 1086 "data/maps/OlivineCity_House1/scripts.pory"
	.string "rather more time indoors than\l"
# 1087 "data/maps/OlivineCity_House1/scripts.pory"
	.string "planned.$"
# 1088 "data/maps/OlivineCity_House1/scripts.pory"

# 1089 "data/maps/OlivineCity_House1/scripts.pory"
@ Script V2 section 13.3: between finishing a mission and Looker's summons call,
# 1090 "data/maps/OlivineCity_House1/scripts.pory"
@ the house offers nothing but this. It does not name the next town, does not
# 1091 "data/maps/OlivineCity_House1/scripts.pory"
@ send the player back to the town just cleared, and does not hand out the next
# 1092 "data/maps/OlivineCity_House1/scripts.pory"
@ briefing early. The label is the one the script fixes; it is used for every
# 1093 "data/maps/OlivineCity_House1/scripts.pory"
@ pending summons, not only Mahogany's.
# 1094 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_WaitForMahoganyCall:
# 1095 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We're still checking the\n"
# 1096 "data/maps/OlivineCity_House1/scripts.pory"
	.string "reports.\p"
# 1097 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll call when we have a lead.$"
# 1098 "data/maps/OlivineCity_House1/scripts.pory"

# 1099 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_WaitForCherrygroveCall:
# 1100 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We're comparing Lillie's\n"
# 1101 "data/maps/OlivineCity_House1/scripts.pory"
	.string "notes with Anabel's\l"
# 1102 "data/maps/OlivineCity_House1/scripts.pory"
	.string "recordings.\p"
# 1103 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll call when we have a lead.$"
# 1104 "data/maps/OlivineCity_House1/scripts.pory"

# 1105 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_WaitForNewBarkCall:
# 1106 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We're waiting for Professor\n"
# 1107 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Elm's records.\p"
# 1108 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll call when we've compared\n"
# 1109 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them.$"
# 1110 "data/maps/OlivineCity_House1/scripts.pory"

# 1111 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_WaitForAltarCall:
# 1112 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We're comparing the records\n"
# 1113 "data/maps/OlivineCity_House1/scripts.pory"
	.string "and arranging the meeting.\p"
# 1114 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'll call when everyone's\n"
# 1115 "data/maps/OlivineCity_House1/scripts.pory"
	.string "ready.$"
# 1116 "data/maps/OlivineCity_House1/scripts.pory"

# 1117 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelWaitForCall:
# 1118 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Nothing conclusive yet.\p"
# 1119 "data/maps/OlivineCity_House1/scripts.pory"
	.string "When there is, Looker will\n"
# 1120 "data/maps/OlivineCity_House1/scripts.pory"
	.string "telephone you himself.$"
# 1121 "data/maps/OlivineCity_House1/scripts.pory"

# 1122 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAhead:
# 1123 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The Pokémon Center in\n"
# 1124 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Blackthorn.\p"
# 1125 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll meet you there.$"
# 1126 "data/maps/OlivineCity_House1/scripts.pory"

# 1127 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM2:
# 1128 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Mahogany's Pokémon\n"
# 1129 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Center.\p"
# 1130 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pryce has kept the road to it\n"
# 1131 "data/maps/OlivineCity_House1/scripts.pory"
	.string "clear.$"
# 1132 "data/maps/OlivineCity_House1/scripts.pory"

# 1133 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM3:
# 1134 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The northwest shore in\n"
# 1135 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Cherrygrove. We'll meet you\l"
# 1136 "data/maps/OlivineCity_House1/scripts.pory"
	.string "there.$"
# 1137 "data/maps/OlivineCity_House1/scripts.pory"

# 1138 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerGoAheadM4:
# 1139 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Outside your house in New\n"
# 1140 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bark. We'll keep the approach\l"
# 1141 "data/maps/OlivineCity_House1/scripts.pory"
	.string "clear.$"
# 1142 "data/maps/OlivineCity_House1/scripts.pory"

# 1143 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelHoliday:
# 1144 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}It's peaceful here.\p"
# 1145 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Looker keeps finding reasons\n"
# 1146 "data/maps/OlivineCity_House1/scripts.pory"
	.string "to check the telephone.$"
# 1147 "data/maps/OlivineCity_House1/scripts.pory"

# 1148 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAhead:
# 1149 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Prepare your team\n"
# 1150 "data/maps/OlivineCity_House1/scripts.pory"
	.string "before you join us.\p"
# 1151 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Clair is holding the street.$"
# 1152 "data/maps/OlivineCity_House1/scripts.pory"

# 1153 "data/maps/OlivineCity_House1/scripts.pory"
@ Mahogany V2 section 5. No character predicts the two rounds: "a longer
# 1154 "data/maps/OlivineCity_House1/scripts.pory"
@ fight" and "change our approach" are preparation, not foresight.
# 1155 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM2:
# 1156 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Prepare for a longer\n"
# 1157 "data/maps/OlivineCity_House1/scripts.pory"
	.string "fight.\p"
# 1158 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We may need to change our\n"
# 1159 "data/maps/OlivineCity_House1/scripts.pory"
	.string "approach.$"
# 1160 "data/maps/OlivineCity_House1/scripts.pory"

# 1161 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM3:
# 1162 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Prepare before you approach\n"
# 1163 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the beach. We need both fronts\l"
# 1164 "data/maps/OlivineCity_House1/scripts.pory"
	.string "covered.$"
# 1165 "data/maps/OlivineCity_House1/scripts.pory"

# 1166 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelGoAheadM4:
# 1167 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}There's no Pokémon Center in\n"
# 1168 "data/maps/OlivineCity_House1/scripts.pory"
	.string "New Bark. Heal before we\l"
# 1169 "data/maps/OlivineCity_House1/scripts.pory"
	.string "begin.$"
# 1170 "data/maps/OlivineCity_House1/scripts.pory"

# 1171 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 1172 "data/maps/OlivineCity_House1/scripts.pory"
@ Pre-Necrozma reunion texts - script V2 (25/09/2026), final lines.
# 1173 "data/maps/OlivineCity_House1/scripts.pory"
@ One speaker per box; consecutive msgbox keep the box up and swap the plaque.
# 1174 "data/maps/OlivineCity_House1/scripts.pory"
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
# 1175 "data/maps/OlivineCity_House1/scripts.pory"
@ Menus and the obtain fanfare carry no plaque: they are system, not speech.
# 1176 "data/maps/OlivineCity_House1/scripts.pory"
@ ============================================================================
# 1177 "data/maps/OlivineCity_House1/scripts.pory"

# 1178 "data/maps/OlivineCity_House1/scripts.pory"
@ The records compared during the interval point at the region; Lusamine's
# 1179 "data/maps/OlivineCity_House1/scripts.pory"
@ charts give the physical access. The boat route is to the altar IN JOHTO;
# 1180 "data/maps/OlivineCity_House1/scripts.pory"
@ the passage beyond it is opened and verified THERE. No compass revealed a
# 1181 "data/maps/OlivineCity_House1/scripts.pory"
@ portal's destination by itself.
# 1182 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionOpen:
# 1183 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Good. We're all here.\p"
# 1184 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Elm's readings narrowed the\n"
# 1185 "data/maps/OlivineCity_House1/scripts.pory"
	.string "search. Aether's charts gave\l"
# 1186 "data/maps/OlivineCity_House1/scripts.pory"
	.string "us a landing point.\p"
# 1187 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The ship can reach this\n"
# 1188 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar.$"
# 1189 "data/maps/OlivineCity_House1/scripts.pory"

# 1190 "data/maps/OlivineCity_House1/scripts.pory"
@ Two moments of the record: the spike after an absorption, the flicker
# 1191 "data/maps/OlivineCity_House1/scripts.pory"
@ after it. The indicator gesture is his exclamation; no numbers to read.
# 1192 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionKukui:
# 1193 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}See that spike?\n"
# 1194 "data/maps/OlivineCity_House1/scripts.pory"
	.string "More power.\p"
# 1195 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Then it starts flickering\n"
# 1196 "data/maps/OlivineCity_House1/scripts.pory"
	.string "again.\p"
# 1197 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Nine Pokémon, and Necrozma\n"
# 1198 "data/maps/OlivineCity_House1/scripts.pory"
	.string "still can't hold that light\l"
# 1199 "data/maps/OlivineCity_House1/scripts.pory"
	.string "steady.$"
# 1200 "data/maps/OlivineCity_House1/scripts.pory"

# 1201 "data/maps/OlivineCity_House1/scripts.pory"
@ Lillie faces her mother, not the floor, and asks for something concrete.
# 1202 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillie:
# 1203 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Elm could still detect\n"
# 1204 "data/maps/OlivineCity_House1/scripts.pory"
	.string "all nine. We need to get\l"
# 1205 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them out.\p"
# 1206 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Mother, can your equipment\n"
# 1207 "data/maps/OlivineCity_House1/scripts.pory"
	.string "do that?$"
# 1208 "data/maps/OlivineCity_House1/scripts.pory"

# 1209 "data/maps/OlivineCity_House1/scripts.pory"
@ She answers with her equipment's LIMIT: no promise the UBs are unharmed,
# 1210 "data/maps/OlivineCity_House1/scripts.pory"
@ no certainty of separation. The altar demonstrates how the release works.
# 1211 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineEvidence:
# 1212 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Not while Necrozma\n"
# 1213 "data/maps/OlivineCity_House1/scripts.pory"
	.string "keeps drawing them in. We saw\l"
# 1214 "data/maps/OlivineCity_House1/scripts.pory"
	.string "that in New Bark.\p"
# 1215 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll have to weaken it\n"
# 1216 "data/maps/OlivineCity_House1/scripts.pory"
	.string "first. Then try to separate\l"
# 1217 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them.$"
# 1218 "data/maps/OlivineCity_House1/scripts.pory"

# 1219 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladionPlan:
# 1220 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}And if the passage\n"
# 1221 "data/maps/OlivineCity_House1/scripts.pory"
	.string "closes behind us?$"
# 1222 "data/maps/OlivineCity_House1/scripts.pory"

# 1223 "data/maps/OlivineCity_House1/scripts.pory"
@ The stabilizer: a fictional resource of the hack, continuous operation,
# 1224 "data/maps/OlivineCity_House1/scripts.pory"
@ limited duration. It holds an OPEN passage steady - it opens nothing,
# 1225 "data/maps/OlivineCity_House1/scripts.pory"
@ transports nothing by itself, and guarantees no return under any condition.
# 1226 "data/maps/OlivineCity_House1/scripts.pory"
@ No item reaches the inventory.
# 1227 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionStabilizer:
# 1228 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}This holds an open\n"
# 1229 "data/maps/OlivineCity_House1/scripts.pory"
	.string "passage steady. One unit on\l"
# 1230 "data/maps/OlivineCity_House1/scripts.pory"
	.string "each side.\p"
# 1231 "data/maps/OlivineCity_House1/scripts.pory"
	.string "It cannot open one. And\n"
# 1232 "data/maps/OlivineCity_House1/scripts.pory"
	.string "someone must keep both units\l"
# 1233 "data/maps/OlivineCity_House1/scripts.pory"
	.string "running.$"
# 1234 "data/maps/OlivineCity_House1/scripts.pory"

# 1235 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAnabelReturn:
# 1236 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}I'll take the portable\n"
# 1237 "data/maps/OlivineCity_House1/scripts.pory"
	.string "unit. If its signal drops,\l"
# 1238 "data/maps/OlivineCity_House1/scripts.pory"
	.string "we withdraw.\p"
# 1239 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We test the connection at\n"
# 1240 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the altar before anyone\l"
# 1241 "data/maps/OlivineCity_House1/scripts.pory"
	.string "crosses.$"
# 1242 "data/maps/OlivineCity_House1/scripts.pory"

# 1243 "data/maps/OlivineCity_House1/scripts.pory"
@ The Beast Ball is shown and STAYS WITH ANABEL until the altar's scripted
# 1244 "data/maps/OlivineCity_House1/scripts.pory"
@ capture (Act IV). No crafting, no purchase, no player item. Necrozma is
# 1245 "data/maps/OlivineCity_House1/scripts.pory"
@ never called an Ultra Beast, and no canonical Ball bonus is promised: the
# 1246 "data/maps/OlivineCity_House1/scripts.pory"
@ later guaranteed capture is this event's authorial rule.
# 1247 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionCapture:
# 1248 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Once the others are\n"
# 1249 "data/maps/OlivineCity_House1/scripts.pory"
	.string "free, we capture Necrozma.\p"
# 1250 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I have a Beast Ball from\n"
# 1251 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Kurt ready.\p"
# 1252 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Driving it away only moves\n"
# 1253 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the danger.$"
# 1254 "data/maps/OlivineCity_House1/scripts.pory"

# 1255 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineCross:
# 1256 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Then I'll lead the\n"
# 1257 "data/maps/OlivineCity_House1/scripts.pory"
	.string "crossing.\p"
# 1258 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I know Aether's equipment\n"
# 1259 "data/maps/OlivineCity_House1/scripts.pory"
	.string "best.$"
# 1260 "data/maps/OlivineCity_House1/scripts.pory"

# 1261 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLillieBoundary:
# 1262 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Then show us how to\n"
# 1263 "data/maps/OlivineCity_House1/scripts.pory"
	.string "use it, Mother.\p"
# 1264 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We can't all depend on you\n"
# 1265 "data/maps/OlivineCity_House1/scripts.pory"
	.string "alone.$"
# 1266 "data/maps/OlivineCity_House1/scripts.pory"

# 1267 "data/maps/OlivineCity_House1/scripts.pory"
@ Family progress (V2 section 5): she shares the control because Lillie asked
# 1268 "data/maps/OlivineCity_House1/scripts.pory"
@ for something concrete. No apology for the whole story, no absolution, no
# 1269 "data/maps/OlivineCity_House1/scripts.pory"
@ advance surrender of the crossing - the altar's disagreement stays open,
# 1270 "data/maps/OlivineCity_House1/scripts.pory"
@ but it will start from this.
# 1271 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionLusamineControl:
# 1272 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}The lower dial. Keep\n"
# 1273 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the two lights level.$"
# 1274 "data/maps/OlivineCity_House1/scripts.pory"

# 1275 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAnabelLeadership:
# 1276 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}We'll decide who leads\n"
# 1277 "data/maps/OlivineCity_House1/scripts.pory"
	.string "at the altar.\p"
# 1278 "data/maps/OlivineCity_House1/scripts.pory"
	.string "First, let's see whether\n"
# 1279 "data/maps/OlivineCity_House1/scripts.pory"
	.string "this works.$"
# 1280 "data/maps/OlivineCity_House1/scripts.pory"

# 1281 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAsk:
# 1282 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Now we need your\n"
# 1283 "data/maps/OlivineCity_House1/scripts.pory"
	.string "partner, {PLAYER}.\p"
# 1284 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Solgaleo or Lunala can open\n"
# 1285 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the way.\p"
# 1286 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Let's check the equipment's\n"
# 1287 "data/maps/OlivineCity_House1/scripts.pory"
	.string "response.$"
# 1288 "data/maps/OlivineCity_House1/scripts.pory"

# 1289 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionDeferred:
# 1290 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Sure. Speak to Looker\n"
# 1291 "data/maps/OlivineCity_House1/scripts.pory"
	.string "when you're ready.$"
# 1292 "data/maps/OlivineCity_House1/scripts.pory"

# 1293 "data/maps/OlivineCity_House1/scripts.pory"
@ Guidance lines (V2 section 6): each one says only what was verified.
# 1294 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionStored:
# 1295 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Bring Solgaleo or\n"
# 1296 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lunala from the PC.\p"
# 1297 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We need your partner here\n"
# 1298 "data/maps/OlivineCity_House1/scripts.pory"
	.string "for the test.$"
# 1299 "data/maps/OlivineCity_House1/scripts.pory"

# 1300 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionUnevolved:
# 1301 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}Your partner needs to\n"
# 1302 "data/maps/OlivineCity_House1/scripts.pory"
	.string "evolve first.\p"
# 1303 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Bring Solgaleo or Lunala\n"
# 1304 "data/maps/OlivineCity_House1/scripts.pory"
	.string "when it's ready.$"
# 1305 "data/maps/OlivineCity_House1/scripts.pory"

# 1306 "data/maps/OlivineCity_House1/scripts.pory"
@ Claims no growth, loss, trade or release without evidence.
# 1307 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionMissing:
# 1308 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}We'll need Solgaleo or\n"
# 1309 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lunala in your team before\l"
# 1310 "data/maps/OlivineCity_House1/scripts.pory"
	.string "we can leave.$"
# 1311 "data/maps/OlivineCity_House1/scripts.pory"

# 1312 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionResume:
# 1313 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Ready to try the\n"
# 1314 "data/maps/OlivineCity_House1/scripts.pory"
	.string "equipment with your partner?$"
# 1315 "data/maps/OlivineCity_House1/scripts.pory"

# 1316 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTestStart:
# 1317 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Ready. Just a short\n"
# 1318 "data/maps/OlivineCity_House1/scripts.pory"
	.string "pulse.$"
# 1319 "data/maps/OlivineCity_House1/scripts.pory"

# 1320 "data/maps/OlivineCity_House1/scripts.pory"
@ Bench-test result in EVERY save: compatibility and a brief response, never
# 1321 "data/maps/OlivineCity_House1/scripts.pory"
@ proof of a safe crossing, and no claim about scenes that may not have been
# 1322 "data/maps/OlivineCity_House1/scripts.pory"
@ recorded.
# 1323 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTestResult:
# 1324 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}There! Both lights\n"
# 1325 "data/maps/OlivineCity_House1/scripts.pory"
	.string "together.\p"
# 1326 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The equipment can follow\n"
# 1327 "data/maps/OlivineCity_House1/scripts.pory"
	.string "your partner.\p"
# 1328 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Now we test it on a real\n"
# 1329 "data/maps/OlivineCity_House1/scripts.pory"
	.string "passage.$"
# 1330 "data/maps/OlivineCity_House1/scripts.pory"

# 1331 "data/maps/OlivineCity_House1/scripts.pory"
@ Default version on purpose: the presented Pokemon may be another specimen,
# 1332 "data/maps/OlivineCity_House1/scripts.pory"
@ and nothing in the save proves which one hatched from the Violet egg. The
# 1333 "data/maps/OlivineCity_House1/scripts.pory"
@ optional "Hard to believe I carried that egg." callback needs verifiable
# 1334 "data/maps/OlivineCity_House1/scripts.pory"
@ provenance that no existing data field provides.
# 1335 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionGladionPartner:
# 1336 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}…You've looked\n"
# 1337 "data/maps/OlivineCity_House1/scripts.pory"
	.string "after it.\p"
# 1338 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Good.$"
# 1339 "data/maps/OlivineCity_House1/scripts.pory"

# 1340 "data/maps/OlivineCity_House1/scripts.pory"
@ Future roles, V2 section 8: player fights and captures; the partner opens
# 1341 "data/maps/OlivineCity_House1/scripts.pory"
@ and holds the route; Anabel operates inside; Gladion/Silvally cover the
# 1342 "data/maps/OlivineCity_House1/scripts.pory"
@ exit; Lillie/Ninetales receive the UBs; Kukui reads the measurements;
# 1343 "data/maps/OlivineCity_House1/scripts.pory"
@ Looker handles transport and recovery. Lusamine prepares the outside base
# 1344 "data/maps/OlivineCity_House1/scripts.pory"
@ with Kukui - accepting to STAY outside is the altar's beat, not this one's.
# 1345 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionAssignments:
# 1346 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Gladion, keep the exit\n"
# 1347 "data/maps/OlivineCity_House1/scripts.pory"
	.string "clear. Lillie, help the\l"
# 1348 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Pokémon we bring back.\p"
# 1349 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Professor, check the outside\n"
# 1350 "data/maps/OlivineCity_House1/scripts.pory"
	.string "unit with Lusamine when we\l"
# 1351 "data/maps/OlivineCity_House1/scripts.pory"
	.string "arrive.$"
# 1352 "data/maps/OlivineCity_House1/scripts.pory"

# 1353 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicket:
# 1354 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}The ship is ready at\n"
# 1355 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Olivine Port.\p"
# 1356 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Show the sailor this pass.$"
# 1357 "data/maps/OlivineCity_House1/scripts.pory"

# 1358 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionTicketUse:
# 1359 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}He'll take you to the\n"
# 1360 "data/maps/OlivineCity_House1/scripts.pory"
	.string "altar and back.\p"
# 1361 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Heal your team, and bring\n"
# 1362 "data/maps/OlivineCity_House1/scripts.pory"
	.string "your partner.$"
# 1363 "data/maps/OlivineCity_House1/scripts.pory"

# 1364 "data/maps/OlivineCity_House1/scripts.pory"
@ Not in the V2 text list: the prevention line for the one delivery failure
# 1365 "data/maps/OlivineCity_House1/scripts.pory"
@ that exists (Key Items pocket full). Nothing is claimed beyond the fact.
# 1366 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ReunionNoRoom:
# 1367 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Your Key Items pocket\n"
# 1368 "data/maps/OlivineCity_House1/scripts.pory"
	.string "is full.\p"
# 1369 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Make room for the pass, then\n"
# 1370 "data/maps/OlivineCity_House1/scripts.pory"
	.string "speak to me again.$"
# 1371 "data/maps/OlivineCity_House1/scripts.pory"

# 1372 "data/maps/OlivineCity_House1/scripts.pory"
@ Menu labels - system text, no plaque.
# 1373 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_PartnerSelect:
# 1374 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Which Pokémon will you bring\n"
# 1375 "data/maps/OlivineCity_House1/scripts.pory"
	.string "forward?$"
# 1376 "data/maps/OlivineCity_House1/scripts.pory"

# 1377 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ChoiceSolgaleo:
# 1378 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Solgaleo$"
# 1379 "data/maps/OlivineCity_House1/scripts.pory"

# 1380 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ChoiceLunala:
# 1381 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lunala$"
# 1382 "data/maps/OlivineCity_House1/scripts.pory"

# 1383 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ChoiceNotNow:
# 1384 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not now$"
# 1385 "data/maps/OlivineCity_House1/scripts.pory"

# 1386 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ChoiceYes:
# 1387 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Yes$"
# 1388 "data/maps/OlivineCity_House1/scripts.pory"

# 1389 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_ChoiceNotYet:
# 1390 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Not yet$"
# 1391 "data/maps/OlivineCity_House1/scripts.pory"

# 1392 "data/maps/OlivineCity_House1/scripts.pory"
@ States 12-15, the repeatable orientation (V2 section 10). Releasing the
# 1393 "data/maps/OlivineCity_House1/scripts.pory"
@ voyage is persistent; the altar revalidates the team itself.
# 1394 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_LookerAltar:
# 1395 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LOOKER}Show your pass to the\n"
# 1396 "data/maps/OlivineCity_House1/scripts.pory"
	.string "sailor at Olivine Port.\p"
# 1397 "data/maps/OlivineCity_House1/scripts.pory"
	.string "The ship makes the return\n"
# 1398 "data/maps/OlivineCity_House1/scripts.pory"
	.string "trip too.$"
# 1399 "data/maps/OlivineCity_House1/scripts.pory"

# 1400 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_AnabelAltar:
# 1401 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_ANABEL}Bring Solgaleo or\n"
# 1402 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Lunala.\p"
# 1403 "data/maps/OlivineCity_House1/scripts.pory"
	.string "We'll check the passage at\n"
# 1404 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the altar.$"
# 1405 "data/maps/OlivineCity_House1/scripts.pory"

# 1406 "data/maps/OlivineCity_House1/scripts.pory"
@ State 11 idle lines (V2 section 9): short preparation notes for whoever
# 1407 "data/maps/OlivineCity_House1/scripts.pory"
@ explores the room. None of them carries information the main scene needs.
# 1408 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLusamine:
# 1409 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Lillie's notes were\n"
# 1410 "data/maps/OlivineCity_House1/scripts.pory"
	.string "useful. She recorded when\l"
# 1411 "data/maps/OlivineCity_House1/scripts.pory"
	.string "the light changed.\p"
# 1412 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I should have asked to see\n"
# 1413 "data/maps/OlivineCity_House1/scripts.pory"
	.string "them sooner.$"
# 1414 "data/maps/OlivineCity_House1/scripts.pory"

# 1415 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleLillie:
# 1416 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}Mother asked for my\n"
# 1417 "data/maps/OlivineCity_House1/scripts.pory"
	.string "notes. Then she actually\l"
# 1418 "data/maps/OlivineCity_House1/scripts.pory"
	.string "read them.\p"
# 1419 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'd like that to happen more\n"
# 1420 "data/maps/OlivineCity_House1/scripts.pory"
	.string "often.$"
# 1421 "data/maps/OlivineCity_House1/scripts.pory"

# 1422 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleGladion:
# 1423 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}She showed Anabel the\n"
# 1424 "data/maps/OlivineCity_House1/scripts.pory"
	.string "controls. That's a start.\p"
# 1425 "data/maps/OlivineCity_House1/scripts.pory"
	.string "I'm still watching the exit.$"
# 1426 "data/maps/OlivineCity_House1/scripts.pory"

# 1427 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_IdleKukui:
# 1428 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_KUKUI}I had a boat booked\n"
# 1429 "data/maps/OlivineCity_House1/scripts.pory"
	.string "for Alola. Looker's going to\l"
# 1430 "data/maps/OlivineCity_House1/scripts.pory"
	.string "owe me a new ticket.\p"
# 1431 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Don't tell him I said that.$"
# 1432 "data/maps/OlivineCity_House1/scripts.pory"

# 1433 "data/maps/OlivineCity_House1/scripts.pory"
@ Post-game, state >= 16, V2 section 11: the family's two days a week in this
# 1434 "data/maps/OlivineCity_House1/scripts.pory"
@ room (Sunday and Friday, the days the altar doc fixed). Small, still
# 1435 "data/maps/OlivineCity_House1/scripts.pory"
@ imperfect coexistence - tea, an agenda under the teapot, Gladion staying
# 1436 "data/maps/OlivineCity_House1/scripts.pory"
@ for another cup - and no speech about learning to live together. No line
# 1437 "data/maps/OlivineCity_House1/scripts.pory"
@ describes Silvally anywhere his sprite is not: he stands at (2,7), by
# 1438 "data/maps/OlivineCity_House1/scripts.pory"
@ Gladion, as always. Lusamine's template sits at (5,6) on these loads
# 1439 "data/maps/OlivineCity_House1/scripts.pory"
@ (ApplyPostgameSeating): by the table, near her children.
# 1440 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseLusaminePost:
# 1441 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LUSAMINE}Lillie chose tea for\n"
# 1442 "data/maps/OlivineCity_House1/scripts.pory"
	.string "this afternoon. I had planned\l"
# 1443 "data/maps/OlivineCity_House1/scripts.pory"
	.string "something more elaborate.\p"
# 1444 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…Tea will do.\n"
# 1445 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Would you like some?$"
# 1446 "data/maps/OlivineCity_House1/scripts.pory"

# 1447 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseLilliePost:
# 1448 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_LILLIE}We meet here twice a\n"
# 1449 "data/maps/OlivineCity_House1/scripts.pory"
	.string "week. Mother tried to make\l"
# 1450 "data/maps/OlivineCity_House1/scripts.pory"
	.string "an agenda.\p"
# 1451 "data/maps/OlivineCity_House1/scripts.pory"
	.string "Gladion put it under the\n"
# 1452 "data/maps/OlivineCity_House1/scripts.pory"
	.string "teapot.$"
# 1453 "data/maps/OlivineCity_House1/scripts.pory"

# 1454 "data/maps/OlivineCity_House1/scripts.pory"
OlivineCity_House1_Text_HouseGladionPost:
# 1455 "data/maps/OlivineCity_House1/scripts.pory"
	.string "{SPEAKER NAME_GLADION}It was wobbling.\p"
# 1456 "data/maps/OlivineCity_House1/scripts.pory"
	.string "…I'm staying for another\n"
# 1457 "data/maps/OlivineCity_House1/scripts.pory"
	.string "cup.$"
