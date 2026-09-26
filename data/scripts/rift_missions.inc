@ ============================================================================
@ Rift Missions - Looker's summons call.
@
@ After a mission is closed, the briefing in Olivine is NOT available yet: the
@ house only offers the waiting line until Looker telephones. The call is the
@ summons, it names where the next occurrence is, and the briefing in Olivine is
@ where the plan is laid out.
@
@ Three conditions, all of them in ShouldDoRiftMissionCall
@ (src/field_control_avatar.c):
@   1. VAR_RIFT_MISSIONS_STATE is one of 4, 6, 8, 10 - the states that mean
@      "the last mission is closed and the next briefing is pending". A list and
@      not a range: the odd values in between are incidents in progress.
@      State 2 is NOT in it. Blackthorn's summons is the dedicated call scene in
@      New Bark, and that invitation "persiste ate o briefing, sem expirar nem
@      produzir lembretes nos dias seguintes" (script V2 section 4).
@   2. no invitation already pending (FLAG_RIFT_LOOKER_SUMMONS clear). An
@      invitation that has been issued is never re-issued; it survives days and
@      saves and waits for the player.
@   3. Looker has not called today (FLAG_DAILY_LOOKER_CALL clear). A daily flag,
@      so ClearDailyFlags opens the next attempt at the change of date - the game
@      calendar, not 24 hours since the last call.
@ Plus: no unfinished business from the previous mission. Today that means the
@ Type: Null Gladion may still be holding (FLAG_BLACKTHORN_TYPE_NULL_PENDING).
@ Any future mission that can end with a gift pending has to join that check.
@
@ Every script that closes a mission ALSO sets FLAG_DAILY_LOOKER_CALL, so
@ finishing Blackthorn on the day he called does not buy a second call that day.
@ A retry after a blackout changes no state and therefore rings no telephone.
@
@ One text per state. None of them explains what happened: that is the briefing.
@ ============================================================================

RiftMissions_EventScript_LookerCall::
	setflag FLAG_DAILY_LOOKER_CALL             @ one call a day...
	setflag FLAG_RIFT_LOOKER_SUMMONS           @ ...and this invitation now waits
	lockall
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, RiftMissions_EventScript_LookerCallM3
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, RiftMissions_EventScript_LookerCallM4
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, RiftMissions_EventScript_LookerCallReunion
	pokenavcall RiftMissions_Text_LookerCallM2
	goto RiftMissions_EventScript_LookerCallEnd

RiftMissions_EventScript_LookerCallM3::
	pokenavcall RiftMissions_Text_LookerCallM3
	goto RiftMissions_EventScript_LookerCallEnd

RiftMissions_EventScript_LookerCallM4::
	pokenavcall RiftMissions_Text_LookerCallM4
	goto RiftMissions_EventScript_LookerCallEnd

RiftMissions_EventScript_LookerCallReunion::
	pokenavcall RiftMissions_Text_LookerCallReunion
	goto RiftMissions_EventScript_LookerCallEnd

RiftMissions_EventScript_LookerCallEnd::
	waitmessage
	delay 30
	releaseall
	end

@ State 4 -> Mahogany. The one piece of humour allowed is here, outside the
@ emergency: he is warm on the telephone and short in danger.
@ It says who raised the alarm (Pryce) and what has already been done with
@ Blackthorn's data, so the briefing has somewhere to start from.
RiftMissions_Text_LookerCallM2:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}? It's Looker.\p"
	.string "Pryce has reported unusual\n"
	.string "Pokémon in Mahogany.\p"
	.string "Anabel has been comparing the\n"
	.string "readings with Blackthorn's\l"
	.string "since breakfast.\p"
	.string "I have been holding her coffee.\p"
	.string "Meet us at our base in Olivine.$"

@ State 6 -> Cherrygrove.
RiftMissions_Text_LookerCallM3:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}?\n"
	.string "Looker. It's happened again.\p"
	.string "Cherrygrove City.\p"
	.string "And not the way we expected.\p"
	.string "The house in Olivine, please.\n"
	.string "We'll show you everything.$"

@ State 8 -> New Bark.
RiftMissions_Text_LookerCallM4:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}.\n"
	.string "Looker here.\p"
	.string "New Bark Town.\p"
	.string "…I am sorry. Come to the house\n"
	.string "in Olivine first.\p"
	.string "Anabel would rather you heard\n"
	.string "the rest sitting down.$"

@ State 10 -> the reunion in Olivine itself.
RiftMissions_Text_LookerCallReunion:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}?\n"
	.string "Looker.\p"
	.string "We have guests at the house\n"
	.string "in Olivine.\p"
	.string "People who have seen this\n"
	.string "before. Come when you can.$"
