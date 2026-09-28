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
@ The scripts that close Missions 1-3 ALSO set FLAG_DAILY_LOOKER_CALL, so
@ finishing Blackthorn on the day he called does not buy a second call that day.
@ New Bark (Mission 4) does not: its script (V2 section 18) lets the reunion
@ call ring the same day when the New Bark invitation came on an earlier one.
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

@ State 4 -> Mahogany (MAHOGANY_ULTRABEAST_SCRIPT_V2.md section 5,
@ Phone_Text_LookerMahoganyInvite, verbatim). It says who raised the alarm
@ (Pryce) and that Blackthorn's data is already being used, so the briefing has
@ somewhere to start from. No hour of the day (design 5.3).
RiftMissions_Text_LookerCallM2:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}, it's Looker.\p"
	.string "Pryce reported unusual\n"
	.string "Pokémon in Mahogany.\p"
	.string "Meet us at our base in Olivine.\p"
	.string "Anabel has compared the\n"
	.string "readings with Blackthorn's.$"

@ State 6 -> Cherrygrove (CHERRYGROVE_ULTRABEAST_SCRIPT_V2.md section 3): the
@ place and the reason for the meeting, nothing else.
RiftMissions_Text_LookerCallM3:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}, we've had a\n"
	.string "report from the Cherrygrove\l"
	.string "coast.\p"
	.string "Meet us at the Olivine base.\p"
	.string "Anabel found something in\n"
	.string "Lillie's notes that may help\l"
	.string "us this time.$"

@ State 8 -> New Bark. Bridge text fixed by the Cherrygrove V2 script (section
@ 17): Elm answered the request Kukui made on the beach. Pair with
@ CherrygroveCity_Text_UBKukuiElm and OlivineCity_House1_Text_BriefingM4Evidence.
RiftMissions_Text_LookerCallM4:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}, Professor Elm\n"
	.string "contacted us. His readings\l"
	.string "match the rift at Cherrygrove.\p"
	.string "Come to the Olivine base.\n"
	.string "We need to plan our approach\l"
	.string "to New Bark.$"

@ State 10 -> the reunion in Olivine (NEWBARK_ULTRABEAST_SCRIPT_V2.md section
@ 18). Only after New Bark is closed and only on a day Looker has not called
@ yet: if he called for New Bark today, the meeting waits for another date.
@ The daily flag set by the New Bark call is what makes it wait. Unlike the
@ other missions, NewBarkTown_EventScript_UBFinish does NOT set
@ FLAG_DAILY_LOOKER_CALL: if the New Bark invitation was issued on an earlier
@ day, this call may ring today, once the player is back in free control.
@ The route to the Altar was found DURING the interval (Elm's record, Aether's
@ files, Cherrygrove's bearing), so the call can say there is one.
RiftMissions_Text_LookerCallReunion:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}, everyone's here\n"
	.string "in Olivine. We have a route to\l"
	.string "Necrozma.\p"
	.string "Meet us at the base.\n"
	.string "We need you for the plan.$"
