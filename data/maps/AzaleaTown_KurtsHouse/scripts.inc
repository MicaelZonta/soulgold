# 1 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 2 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 3 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_MapScripts::
# 4 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_KurtsHouse_OnFrame
# 5 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_KurtsHouse_OnTransition
# 6 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.byte 0
# 7 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 8 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_OnTransition::
# 9 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup
# 10 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 11 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 12 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_OnFrame::
# 13 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	map_script_2 VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell
# 14 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.2byte 0
# 15 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 16 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtBefore::
# 17 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 18 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 19 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_DEFAULT
# 20 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 21 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_PlayerMove
# 22 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
# 23 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 24 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_EXIT
# 25 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
# 26 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_KURT_1
# 27 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
# 28 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_AZALEA_TOWN_STATE, 2
# 29 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 30 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 31 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 32 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_PlayerMove::
# 33 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_KurtsHouse_Movement_Player
# 34 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 35 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
# 36 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 37 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_EXIT
# 38 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
# 39 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_KURT_1
# 40 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
# 41 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 42 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 43 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 44 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl::
# 45 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 46 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 47 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_unset FLAG_HIDE_KURT_2, AzaleaTown_KurtsHouse_EventScript_Girl2
# 48 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_set FLAG_HIDE_KURT_1, AzaleaTown_KurtsHouse_EventScript_Girl3
# 49 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_DEFAULT
# 50 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 51 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 52 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 53 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl2::
# 54 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_Girl4
# 55 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 4, AzaleaTown_KurtsHouse_EventScript_Girl4
# 56 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_KurtsHouse_EventScript_Girl4
# 57 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_KurtsHouse_EventScript_Girl4
# 58 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_Girl5
# 59 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_Girl5
# 60 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 61 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterDad, MSGBOX_DEFAULT
# 62 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 63 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 64 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 65 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 66 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl3::
# 67 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterLonely, MSGBOX_DEFAULT
# 68 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 69 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 70 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 71 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 72 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl4::
# 73 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterSlowpokeBack, MSGBOX_DEFAULT
# 74 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 75 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_GranddaughterTier
# 76 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 77 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ How the player finds out Kurt got better, in her voice and not in a number.
# 78 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ One box per band of five levels, four boxes for twenty levels - nobody ever
# 79 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ says "level 13" out loud. The other half of the notification is the menu
# 80 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ itself: a new line appearing in it is the clearest possible signal.
# 81 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_GranddaughterTier::
# 82 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtCraft_EventScript_ComputeLevel
# 83 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_0x8004, 16, KurtCraft_EventScript_GranddaughterTierFour
# 84 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_0x8004, 11, KurtCraft_EventScript_GranddaughterTierThree
# 85 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_0x8004, 6, KurtCraft_EventScript_GranddaughterTierTwo
# 86 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterTierOne, MSGBOX_DEFAULT
# 87 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 88 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 89 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 90 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_GranddaughterTierTwo::
# 91 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterTierTwo, MSGBOX_DEFAULT
# 92 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 93 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 94 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 95 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_GranddaughterTierThree::
# 96 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterTierThree, MSGBOX_DEFAULT
# 97 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 98 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 99 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 100 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_GranddaughterTierFour::
# 101 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterTierFour, MSGBOX_DEFAULT
# 102 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 103 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 104 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end	
# 105 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 106 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Girl5::
# 107 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_GranddaughterSound, MSGBOX_DEFAULT
# 108 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 109 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 110 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end	
# 111 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 112 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup::
# 113 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setobjectmovementtype LOCALID_AZALEA_TOWN_KURT, MOVEMENT_TYPE_FACE_DOWN
# 114 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 115 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 116 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
# 117 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 118 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 119 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtHonoredToMakeBalls, MSGBOX_DEFAULT
# 120 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FAST_BALL
# 121 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_DAILY_KURT_FREE_BALLS
# 122 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
# 123 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtMakesBallsDaily
# 124 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 125 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 126 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_AZALEA_TOWN_STATE, 4
# 127 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 128 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 129 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 130 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall::
# 131 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem ITEM_GS_BALL
# 132 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_KurtsHouse_EventScript_KurtGsBall
# 133 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 134 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 135 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ===========================================================================
# 136 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ KURT'S RECIPES - the Poke Ball economy
# 137 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Plan: .claude/KURT_BALL_CRAFT_DESIGN.md
# 138 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 139 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Every Poke Mart in the campaign now sells ITEM_POKE_BALL and nothing else, and
# 140 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Kurt is the only factory for the other twenty-six. He makes N lots a day, where
# 141 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ N is his level, each lot is 5 Balls, and each lot costs Berries.
# 142 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 143 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ WHAT WAS WRONG BEFORE
# 144 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   1. The recipe menu was UNREACHABLE. The old entry point ended in an
# 145 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      unconditional goto KurtDaily, and the only thing in the repository that
# 146 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      jumped to the menu was the "you don't have the Berry" branch INSIDE a
# 147 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      recipe - a closed loop with no door. Seven recipes had been written and
# 148 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      none of them could ever run.
# 149 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   2. All seven ate the Berries when the bag was full:
# 150 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@           giveitem ITEM_LOVE_BALL, 5        <- fails, VAR_RESULT = FALSE
# 151 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@           removeitem ITEM_PECHA_BERRY, 5    <- takes them, VAR_RESULT = TRUE
# 152 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@           goto_if_eq VAR_RESULT, FALSE, ... <- reads the REMOVEITEM result
# 153 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      Space first, then consume, then give, then guard. That order is not
# 154 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      negotiable and it is why there is ONE generic recipe routine below instead
# 155 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      of twenty-seven copies of twelve lines.
# 156 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 157 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ STATE
# 158 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_KURT_PROFICIENCY  EXP, 0..1520. +1 per Ball, so +5 per lot. Written ONLY
# 159 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@                         by a recipe: the free daily draw no longer touches it,
# 160 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@                         because a gift must not buy progress.
# 161 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@                         level L is unlocked at EXP >= 4 * L * (L - 1)
# 162 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_KURT_TODAY        lots made today, 0..level
# 163 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   FLAG_DAILY_KURT_NEW_DAY     "today's quota has been zeroed"
# 164 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   FLAG_DAILY_KURT_FREE_BALLS  "today's free draw has been taken" (pre-existing)
# 165 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   Two daily flags and not one: sharing them would make the draw eat the quota.
# 166 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_RIFT_MISSIONS_STATE     READ ONLY, >= 15 unlocks the Beast Ball
# 167 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 168 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ SCRATCH VARS, and they may not be renumbered casually
# 169 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_0x8004  Kurt's level, from ComputeLevel
# 170 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_0x8005  Berries per lot, from ComputeCost
# 171 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_0x8006  the Ball this recipe makes
# 172 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_0x8007  the Berry this recipe costs
# 173 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   VAR_0x8000/0x8001 belong to giveitem, which is why nothing above uses them.
# 174 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ===========================================================================
# 175 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 176 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_Kurt::
# 177 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock
# 178 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 179 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_KurtGsBall2
# 180 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_KurtGsBall3
# 181 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_unset FLAG_CAUGHT_CELEBI, AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall
# 182 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Entry
# 183 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 184 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Order of guards, and none of them is reorderable:
# 185 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   1. the day rollover, so the quota is always about today
# 186 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   2. the free draw, if it has not been taken - it gives NO exp
# 187 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   3. the level
# 188 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   4. the quota, BEFORE the menu: never let the player pick and then refuse
# 189 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   5. the menu
# 190 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_Entry::
# 191 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtCraft_EventScript_RollOver
# 192 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_unset FLAG_DAILY_KURT_FREE_BALLS, KurtCraft_EventScript_FreeDraw
# 193 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtCraft_EventScript_ComputeLevel         @ VAR_0x8004 = level, 1..20
# 194 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_lt VAR_KURT_TODAY, VAR_0x8004, KurtCraft_EventScript_GroupMenu
# 195 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_DoneForToday
# 196 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 197 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The reset is the engine's work: ClearDailyFlags clears FLAG_DAILY_KURT_NEW_DAY
# 198 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ at the date rollover, and the first conversation of the new day finds it clear
# 199 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ and zeroes the quota. No var holds a date and nothing polls the clock.
# 200 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_RollOver::
# 201 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_set FLAG_DAILY_KURT_NEW_DAY, KurtCraft_EventScript_RollOverDone
# 202 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_KURT_TODAY, 0
# 203 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_DAILY_KURT_NEW_DAY
# 204 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_RollOverDone::
# 205 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 206 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 207 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DoneForToday::
# 208 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtQuotaSpent, MSGBOX_DEFAULT
# 209 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 210 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 211 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 212 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 213 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 214 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 215 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ There is no divvar in this script language (only setvar, addvar, subvar and
# 216 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ copyvar), so the level is a DESCENDING ladder against the 4*L*(L-1)
# 217 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ thresholds. Twenty lines, read once per conversation, and the ONLY place in
# 218 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ the repository that turns this var into a level.
# 219 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The whole pace of the system is the 4 in that formula: K=3 reaches level 20 in
# 220 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ 25 days, K=4 in 32, K=5 in 38. Changing the pace is rewriting these twenty
# 221 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ literals and nothing else.
# 222 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 223 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_ComputeLevel::
# 224 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 20
# 225 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 1520, KurtCraft_EventScript_LevelDone
# 226 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 19
# 227 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 1368, KurtCraft_EventScript_LevelDone
# 228 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 18
# 229 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 1224, KurtCraft_EventScript_LevelDone
# 230 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 17
# 231 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 1088, KurtCraft_EventScript_LevelDone
# 232 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 16
# 233 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 960, KurtCraft_EventScript_LevelDone
# 234 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 15
# 235 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 840, KurtCraft_EventScript_LevelDone
# 236 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 14
# 237 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 728, KurtCraft_EventScript_LevelDone
# 238 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 13
# 239 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 624, KurtCraft_EventScript_LevelDone
# 240 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 12
# 241 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 528, KurtCraft_EventScript_LevelDone
# 242 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 11
# 243 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 440, KurtCraft_EventScript_LevelDone
# 244 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 10
# 245 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 360, KurtCraft_EventScript_LevelDone
# 246 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 9
# 247 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 288, KurtCraft_EventScript_LevelDone
# 248 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 8
# 249 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 224, KurtCraft_EventScript_LevelDone
# 250 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 7
# 251 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 168, KurtCraft_EventScript_LevelDone
# 252 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 6
# 253 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 120, KurtCraft_EventScript_LevelDone
# 254 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 5
# 255 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 80, KurtCraft_EventScript_LevelDone
# 256 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 4
# 257 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 48, KurtCraft_EventScript_LevelDone
# 258 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 3
# 259 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 24, KurtCraft_EventScript_LevelDone
# 260 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 2
# 261 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 8, KurtCraft_EventScript_LevelDone
# 262 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8004, 1
# 263 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_LevelDone::
# 264 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 265 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 266 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Berries per lot = 6 - ceil(level / 5): 5 for levels 1-5, 4 for 6-10, 3 for
# 267 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ 11-15, 2 for 16-20. The cost falls as he gets better, which is what keeps the
# 268 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ end of the curve from being pure grind: level 20 is 40 Berries a day for the
# 269 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ full quota, and THAT number is where the "forever game" actually lives.
# 270 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_ComputeCost::
# 271 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8005, 2
# 272 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_0x8004, 16, KurtCraft_EventScript_CostDone
# 273 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8005, 3
# 274 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_0x8004, 11, KurtCraft_EventScript_CostDone
# 275 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8005, 4
# 276 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_0x8004, 6, KurtCraft_EventScript_CostDone
# 277 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8005, 5
# 278 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_CostDone::
# 279 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 280 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 281 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ +1 per BALL, and every lot is 5 Balls, so every lot is +5 - with no exception
# 282 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ anywhere in the tree. The Master Ball is not a recipe (see the draw below) and
# 283 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ it took the last special case with it, which is why no choice of recipe earns
# 284 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ more EXP than another and there is no optimal play to discover.
# 285 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The cap is checked BEFORE the add, which is the shape the old code used.
# 286 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_AddExp::
# 287 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 1516, KurtCraft_EventScript_AddExpMax
# 288 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	addvar VAR_KURT_PROFICIENCY, 5
# 289 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 290 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_AddExpMax::
# 291 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_KURT_PROFICIENCY, 1520
# 292 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 293 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 294 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 295 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ THE MENU. Two steps, group then recipe, because twenty-seven lines in one list
# 296 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ is a wall. dynmultipush/dynmultistack is used and not multichoice: the old
# 297 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ MULTI_KURT_BALLS was a fixed list of eight and could not grow, and a dynamic
# 298 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ stack lets each entry be pushed only when it is actually unlocked - which
# 299 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ makes the MENU the notification. A new line appearing is the clearest possible
# 300 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ way to say "he learned something", and it costs no dialogue box.
# 301 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The id pushed is what comes back in VAR_RESULT, so the ids are the switch
# 302 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ labels and not positions - a locked entry simply is not there.
# 303 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 304 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_GroupMenu::
# 305 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtWhatToday, MSGBOX_DEFAULT
# 306 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_GroupBasic, 0
# 307 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 4, KurtCraft_EventScript_PushApricorn
# 308 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 11, KurtCraft_EventScript_PushModern
# 309 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 16, KurtCraft_EventScript_PushRare
# 310 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_RIFT_MISSIONS_STATE, 15, KurtCraft_EventScript_PushBeast
# 311 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_NeverMind, 9
# 312 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 313 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 314 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 315 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 0, KurtCraft_EventScript_MenuBasic
# 316 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 1, KurtCraft_EventScript_MenuApricorn
# 317 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 2, KurtCraft_EventScript_MenuModern
# 318 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 3, KurtCraft_EventScript_MenuRare
# 319 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 4, KurtCraft_EventScript_MakeBeast
# 320 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtCraft_EventScript_Cancel
# 321 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case MULTI_B_PRESSED, KurtCraft_EventScript_Cancel
# 322 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Cancel
# 323 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 324 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushApricorn::
# 325 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_GroupApricorn, 1
# 326 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 327 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushModern::
# 328 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_GroupModern, 2
# 329 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 330 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushRare::
# 331 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_GroupRare, 3
# 332 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 333 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 334 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The Beast Ball is the ONLY recipe not gated by Kurt's level. It appears the
# 335 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ moment the player beats Ultra Necrozma, because that is when Anabel sends them
# 336 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ here (.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.3) - and a pointer
# 337 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ that leads to "I can't make that yet" is worse than no pointer at all.
# 338 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ State 15 is "Necrozma beaten and received", set by the arena. NOT 16: the
# 339 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ farewell has not played yet when the player could first come back, and one
# 340 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ wasted trip to Azalea is exactly the friction this decision removes.
# 341 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushBeast::
# 342 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_GroupBeast, 4
# 343 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 344 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 345 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Levels 1 to 3. The shop sells Poke Balls cheaper and always will; his version
# 346 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ exists because "he makes every Ball" has to be literally true.
# 347 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MenuBasic::
# 348 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_PokeBall, 10
# 349 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_GreatBall, 11
# 350 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 2, KurtCraft_EventScript_PushHeal
# 351 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 3, KurtCraft_EventScript_PushUltra
# 352 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_Back, 9
# 353 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 354 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 355 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 10, KurtCraft_EventScript_MakePoke
# 356 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 11, KurtCraft_EventScript_MakeGreat
# 357 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 12, KurtCraft_EventScript_MakeHeal
# 358 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 13, KurtCraft_EventScript_MakeUltra
# 359 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtCraft_EventScript_Cancel
# 360 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case MULTI_B_PRESSED, KurtCraft_EventScript_Cancel
# 361 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Cancel
# 362 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 363 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushHeal::
# 364 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_HealBall, 12
# 365 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 366 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushUltra::
# 367 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_UltraBall, 13
# 368 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 369 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 370 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Levels 4 to 10: the seven that were already his, in the order he learns them.
# 371 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ These are the recipes the dead code had, ingredient for ingredient.
# 372 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MenuApricorn::
# 373 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_LevelBall, 20
# 374 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 5, KurtCraft_EventScript_PushLure
# 375 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 6, KurtCraft_EventScript_PushMoon
# 376 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 7, KurtCraft_EventScript_PushFriend
# 377 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 8, KurtCraft_EventScript_PushFast
# 378 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 9, KurtCraft_EventScript_PushHeavy
# 379 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 10, KurtCraft_EventScript_PushLove
# 380 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_Back, 9
# 381 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 382 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 383 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 20, KurtCraft_EventScript_MakeLevel
# 384 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 21, KurtCraft_EventScript_MakeLure
# 385 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 22, KurtCraft_EventScript_MakeMoon
# 386 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 23, KurtCraft_EventScript_MakeFriend
# 387 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 24, KurtCraft_EventScript_MakeFast
# 388 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 25, KurtCraft_EventScript_MakeHeavy
# 389 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 26, KurtCraft_EventScript_MakeLove
# 390 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtCraft_EventScript_Cancel
# 391 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case MULTI_B_PRESSED, KurtCraft_EventScript_Cancel
# 392 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Cancel
# 393 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 394 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushLure::
# 395 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_LureBall, 21
# 396 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 397 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushMoon::
# 398 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_MoonBall, 22
# 399 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 400 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushFriend::
# 401 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_FriendBall, 23
# 402 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 403 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushFast::
# 404 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_FastBall, 24
# 405 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 406 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushHeavy::
# 407 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_HeavyBall, 25
# 408 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 409 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushLove::
# 410 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_LoveBall, 26
# 411 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 412 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 413 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Levels 11 to 15: the modern Balls, which he makes with visible reluctance.
# 414 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MenuModern::
# 415 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_NestBall, 30
# 416 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_NetBall, 31
# 417 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 12, KurtCraft_EventScript_PushQuick
# 418 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 13, KurtCraft_EventScript_PushTimer
# 419 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 14, KurtCraft_EventScript_PushRepeat
# 420 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 15, KurtCraft_EventScript_PushDive
# 421 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 15, KurtCraft_EventScript_PushDusk
# 422 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_Back, 9
# 423 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 424 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 425 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 30, KurtCraft_EventScript_MakeNest
# 426 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 31, KurtCraft_EventScript_MakeNet
# 427 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 32, KurtCraft_EventScript_MakeQuick
# 428 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 33, KurtCraft_EventScript_MakeTimer
# 429 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 34, KurtCraft_EventScript_MakeRepeat
# 430 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 35, KurtCraft_EventScript_MakeDive
# 431 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 36, KurtCraft_EventScript_MakeDusk
# 432 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtCraft_EventScript_Cancel
# 433 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case MULTI_B_PRESSED, KurtCraft_EventScript_Cancel
# 434 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Cancel
# 435 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 436 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushQuick::
# 437 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_QuickBall, 32
# 438 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 439 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushTimer::
# 440 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_TimerBall, 33
# 441 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 442 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushRepeat::
# 443 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_RepeatBall, 34
# 444 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 445 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushDive::
# 446 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_DiveBall, 35
# 447 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 448 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushDusk::
# 449 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_DuskBall, 36
# 450 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 451 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 452 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Levels 16 to 20, and the last thing he ever learns is the Strange Ball: the
# 453 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Ball that does absolutely nothing, for Pokemon that came from another game.
# 454 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ It is the only joke this system tells and it only works because it is last.
# 455 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MenuRare::
# 456 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_PremierBall, 40
# 457 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_LuxuryBall, 41
# 458 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 17, KurtCraft_EventScript_PushSport
# 459 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 17, KurtCraft_EventScript_PushPark
# 460 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 18, KurtCraft_EventScript_PushSafari
# 461 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 18, KurtCraft_EventScript_PushDream
# 462 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 19, KurtCraft_EventScript_PushCherish
# 463 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call_if_ge VAR_0x8004, 20, KurtCraft_EventScript_PushStrange
# 464 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_Back, 9
# 465 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
# 466 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 467 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 40, KurtCraft_EventScript_MakePremier
# 468 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 41, KurtCraft_EventScript_MakeLuxury
# 469 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 42, KurtCraft_EventScript_MakeSport
# 470 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 43, KurtCraft_EventScript_MakePark
# 471 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 44, KurtCraft_EventScript_MakeSafari
# 472 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 45, KurtCraft_EventScript_MakeDream
# 473 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 46, KurtCraft_EventScript_MakeCherish
# 474 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 47, KurtCraft_EventScript_MakeStrange
# 475 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtCraft_EventScript_Cancel
# 476 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case MULTI_B_PRESSED, KurtCraft_EventScript_Cancel
# 477 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Cancel
# 478 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 479 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushSport::
# 480 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_SportBall, 42
# 481 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 482 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushPark::
# 483 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_ParkBall, 43
# 484 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 485 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushSafari::
# 486 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_SafariBall, 44
# 487 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 488 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushDream::
# 489 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_DreamBall, 45
# 490 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 491 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushCherish::
# 492 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_CherishBall, 46
# 493 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 494 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_PushStrange::
# 495 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	dynmultipush KurtCraft_Text_StrangeBall, 47
# 496 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 497 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 498 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_Cancel::
# 499 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 500 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtComeBack, MSGBOX_DEFAULT
# 501 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 502 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 503 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 504 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 505 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 506 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 507 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ THE TWENTY-SEVEN RECIPES. Each one is two setvars and a goto: the Ball it
# 508 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ makes, the Berry it costs, and the one generic routine that does the work.
# 509 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Twenty-seven copies of the twelve-line body is 324 lines in which the
# 510 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ VAR_RESULT bug of the old code could come back, and it came back seven times
# 511 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ the first time. This is the whole reason the table is data and not code.
# 512 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 513 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakePoke::
# 514 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_POKE_BALL
# 515 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_LEPPA_BERRY
# 516 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 517 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeGreat::
# 518 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_GREAT_BALL
# 519 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_AGUAV_BERRY
# 520 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 521 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeHeal::
# 522 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_HEAL_BALL
# 523 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_LUM_BERRY
# 524 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 525 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeUltra::
# 526 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_ULTRA_BALL
# 527 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_IAPAPA_BERRY
# 528 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 529 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeLevel::
# 530 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_LEVEL_BALL
# 531 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_PERSIM_BERRY
# 532 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 533 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeLure::
# 534 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_LURE_BALL
# 535 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_RAWST_BERRY
# 536 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 537 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeMoon::
# 538 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_MOON_BALL
# 539 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_CHESTO_BERRY
# 540 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 541 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeFriend::
# 542 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_FRIEND_BALL
# 543 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_CHERI_BERRY
# 544 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 545 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeFast::
# 546 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_FAST_BALL
# 547 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_ASPEAR_BERRY
# 548 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 549 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeHeavy::
# 550 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_HEAVY_BALL
# 551 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_ORAN_BERRY
# 552 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 553 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeLove::
# 554 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_LOVE_BALL
# 555 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_PECHA_BERRY
# 556 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 557 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeNest::
# 558 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_NEST_BALL
# 559 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_KELPSY_BERRY
# 560 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 561 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeNet::
# 562 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_NET_BALL
# 563 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_QUALOT_BERRY
# 564 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 565 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeQuick::
# 566 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_QUICK_BALL
# 567 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_SITRUS_BERRY
# 568 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 569 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeTimer::
# 570 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_TIMER_BALL
# 571 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_WIKI_BERRY
# 572 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 573 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeRepeat::
# 574 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_REPEAT_BALL
# 575 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_GREPA_BERRY
# 576 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 577 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Passho resists Water, Kasib resists Ghost: the ingredient is the joke.
# 578 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeDive::
# 579 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_DIVE_BALL
# 580 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_PASSHO_BERRY
# 581 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 582 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeDusk::
# 583 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_DUSK_BALL
# 584 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_KASIB_BERRY
# 585 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 586 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakePremier::
# 587 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_PREMIER_BALL
# 588 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_HONDEW_BERRY
# 589 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 590 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeLuxury::
# 591 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_LUXURY_BALL
# 592 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_TAMATO_BERRY
# 593 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 594 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeSport::
# 595 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_SPORT_BALL
# 596 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_POMEG_BERRY
# 597 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 598 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakePark::
# 599 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_PARK_BALL
# 600 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_CHILAN_BERRY
# 601 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 602 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeSafari::
# 603 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_SAFARI_BALL
# 604 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_ROSELI_BERRY
# 605 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 606 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeDream::
# 607 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_DREAM_BALL
# 608 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_YACHE_BERRY
# 609 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 610 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeCherish::
# 611 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_CHERISH_BALL
# 612 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_COLBUR_BERRY
# 613 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 614 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The Starf only comes from the Battle Frontier and from the Route 30 Berry
# 615 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Master's wife, both post-Hall of Fame - which is right for a level-20 recipe.
# 616 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeStrange::
# 617 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_STRANGE_BALL
# 618 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_STARF_BERRY
# 619 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 620 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The Beast Ball costs quota and Berries like everything else - the story only
# 621 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ decides WHETHER he can make it, never how cheap it is.
# 622 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_MakeBeast::
# 623 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8006, ITEM_BEAST_BALL
# 624 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_0x8007, ITEM_HABAN_BERRY
# 625 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Make
# 626 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 627 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 628 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The one generic recipe. VAR_0x8006 is the Ball, VAR_0x8007 is the Berry, and
# 629 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ the quantity comes from the level.
# 630 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ checkitem/removeitem/checkitemspace all VarGet BOTH of their arguments
# 631 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ (src/scrcmd.c), so item and quantity can be vars - which is what makes one
# 632 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ routine possible instead of four branches per recipe.
# 633 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 634 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ THE ORDER IS THE WHOLE POINT: space first, then consume, then give, then a
# 635 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ defensive guard. The old recipes gave first and consumed second, and read the
# 636 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ CONSUME's VAR_RESULT as if it were the GIVE's - so a full bag lost the Berries
# 637 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ and received nothing, with a clean build.
# 638 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 639 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_Make::
# 640 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 641 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtCraft_EventScript_ComputeCost           @ VAR_0x8005 = 5, 4, 3 or 2
# 642 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemname STR_VAR_2, VAR_0x8006
# 643 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	bufferitemnameplural STR_VAR_1, VAR_0x8007, VAR_0x8005
# 644 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	buffernumberstring STR_VAR_3, VAR_0x8005
# 645 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitemspace VAR_0x8006, 5
# 646 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, KurtCraft_EventScript_BagFull
# 647 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	checkitem VAR_0x8007, VAR_0x8005
# 648 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, KurtCraft_EventScript_NoIngredient
# 649 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtGetStarted, MSGBOX_DEFAULT
# 650 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 651 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtCraft_EventScript_WorkAnimation
# 652 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem VAR_0x8007, VAR_0x8005
# 653 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem VAR_0x8006, 5
# 654 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, KurtCraft_EventScript_BagFull
# 655 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	addvar VAR_KURT_TODAY, 1
# 656 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	call KurtCraft_EventScript_AddExp
# 657 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
# 658 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 659 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 660 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 661 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 662 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 663 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_WorkAnimation::
# 664 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 665 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 666 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 667 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 668 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 669 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 670 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 671 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtJustFinishedYourBall, MSGBOX_DEFAULT
# 672 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmessage
# 673 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 674 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 675 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Nothing has been consumed and no quota has been spent, so the player goes
# 676 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ straight back to the group menu and can pick something else.
# 677 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_NoIngredient::
# 678 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtThatsALetdown, MSGBOX_DEFAULT
# 679 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 680 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_GroupMenu
# 681 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 682 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Reached either before anything was taken (the checkitemspace) or from the
# 683 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ defensive guard after the giveitem. Either way nothing marks progress: the
# 684 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ quota is only spent on the line after a confirmed giveitem.
# 685 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_BagFull::
# 686 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtNoRoom, MSGBOX_DEFAULT
# 687 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 688 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
# 689 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 690 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 691 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 692 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 693 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ THE FREE DAILY DRAW. Kept exactly as it was, with two changes:
# 694 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   1. it no longer touches VAR_KURT_PROFICIENCY. That var is EXP now, and a
# 695 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      gift must not buy progress - otherwise standing in his house for a month
# 696 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      would unlock the whole tree without making a single Ball.
# 697 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@   2. the Master Ball face is re-gated from ">= 4" to ">= 360" (level 10),
# 698 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      because the var changed meaning: ">= 4" used to be four days of visits
# 699 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@      and would now be passed by the second lot ever made.
# 700 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 701 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The Master Ball has NO recipe and Kurt never learns one. This face of the die
# 702 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ is the only place in the game it comes from besides Elm's gift, and that is by
# 703 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ far the best thing it can be: a recipe would make it a shopping-list item, and
# 704 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ luck keeps it a thing that happens to you. It is also what stops the draw
# 705 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ becoming pointless at level 20 - even with all twenty-six recipes open, it is
# 706 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ still worth talking to him every morning, for one face of one die.
# 707 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@
# 708 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ This is a SUBROUTINE now (it used to release and end), because the
# 709 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ conversation continues into the recipe menu afterwards.
# 710 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 711 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_FreeDraw::
# 712 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtTodaysSurplus, MSGBOX_DEFAULT
# 713 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto_if_ge VAR_KURT_PROFICIENCY, 360, KurtCraft_EventScript_DrawSixteen
# 714 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	random 15
# 715 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Draw
# 716 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawSixteen::
# 717 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	random 16
# 718 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_Draw::
# 719 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_DAILY_KURT_FREE_BALLS
# 720 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	switch VAR_RESULT
# 721 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 0, KurtCraft_EventScript_DrawLuxury
# 722 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 1, KurtCraft_EventScript_DrawLevel
# 723 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 2, KurtCraft_EventScript_DrawLure
# 724 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 3, KurtCraft_EventScript_DrawMoon
# 725 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 4, KurtCraft_EventScript_DrawFriend
# 726 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 5, KurtCraft_EventScript_DrawLove
# 727 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 6, KurtCraft_EventScript_DrawFast
# 728 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 7, KurtCraft_EventScript_DrawHeavy
# 729 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 8, KurtCraft_EventScript_DrawDream
# 730 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 9, KurtCraft_EventScript_DrawSafari
# 731 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 10, KurtCraft_EventScript_DrawSport
# 732 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 11, KurtCraft_EventScript_DrawPark
# 733 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 12, KurtCraft_EventScript_DrawBeast
# 734 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 13, KurtCraft_EventScript_DrawCherish
# 735 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 14, KurtCraft_EventScript_DrawStrange
# 736 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	case 15, KurtCraft_EventScript_DrawMaster
# 737 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 738 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 739 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawLuxury::
# 740 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LUXURY_BALL, 5
# 741 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 742 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawLevel::
# 743 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LEVEL_BALL, 5
# 744 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 745 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawLure::
# 746 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LURE_BALL, 5
# 747 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 748 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawMoon::
# 749 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_MOON_BALL, 5
# 750 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 751 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawFriend::
# 752 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FRIEND_BALL, 5
# 753 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 754 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawLove::
# 755 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_LOVE_BALL, 5
# 756 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 757 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawFast::
# 758 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_FAST_BALL, 5
# 759 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 760 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawHeavy::
# 761 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_HEAVY_BALL, 5
# 762 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 763 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawDream::
# 764 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_DREAM_BALL, 5
# 765 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 766 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawSafari::
# 767 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_SAFARI_BALL, 5
# 768 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 769 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawSport::
# 770 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_SPORT_BALL, 5
# 771 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 772 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawPark::
# 773 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_PARK_BALL, 5
# 774 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 775 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ The Beast Ball is in the draw as well as in the recipe list, which is now
# 776 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ redundancy and not a source: it gives a slow trickle to a player who has not
# 777 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ reached the altar yet.
# 778 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawBeast::
# 779 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_BEAST_BALL, 5
# 780 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 781 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawCherish::
# 782 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_CHERISH_BALL, 5
# 783 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 784 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawStrange::
# 785 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_STRANGE_BALL, 5
# 786 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 787 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_EventScript_DrawMaster::
# 788 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtMasterpiece, MSGBOX_DEFAULT
# 789 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	giveitem ITEM_MASTER_BALL, 1
# 790 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setflag FLAG_KURT_CRAFTED_MASTER_BALL
# 791 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	special Achievement_CheckAll
# 792 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	return
# 793 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 794 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 795 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ Menu labels. They are plain names and never say a level number out loud: the
# 796 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ player reads the list growing, not a number. The number is the document's.
# 797 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ ---------------------------------------------------------------------------
# 798 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_GroupBasic:
# 799 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Everyday Balls$"
# 800 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_GroupApricorn:
# 801 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "My own recipes$"
# 802 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_GroupModern:
# 803 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "The new-fangled ones$"
# 804 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_GroupRare:
# 805 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "The hard ones$"
# 806 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_GroupBeast:
# 807 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "BEAST BALL$"
# 808 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_NeverMind:
# 809 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Never mind$"
# 810 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_Back:
# 811 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Back$"
# 812 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 813 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_PokeBall:
# 814 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "POKé BALL$"
# 815 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_GreatBall:
# 816 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "GREAT BALL$"
# 817 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_HealBall:
# 818 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "HEAL BALL$"
# 819 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_UltraBall:
# 820 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "ULTRA BALL$"
# 821 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_LevelBall:
# 822 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "LEVEL BALL$"
# 823 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_LureBall:
# 824 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "LURE BALL$"
# 825 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_MoonBall:
# 826 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "MOON BALL$"
# 827 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_FriendBall:
# 828 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "FRIEND BALL$"
# 829 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_FastBall:
# 830 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "FAST BALL$"
# 831 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_HeavyBall:
# 832 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "HEAVY BALL$"
# 833 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_LoveBall:
# 834 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "LOVE BALL$"
# 835 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_NestBall:
# 836 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "NEST BALL$"
# 837 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_NetBall:
# 838 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "NET BALL$"
# 839 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_QuickBall:
# 840 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "QUICK BALL$"
# 841 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_TimerBall:
# 842 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "TIMER BALL$"
# 843 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_RepeatBall:
# 844 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "REPEAT BALL$"
# 845 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_DiveBall:
# 846 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "DIVE BALL$"
# 847 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_DuskBall:
# 848 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "DUSK BALL$"
# 849 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_PremierBall:
# 850 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "PREMIER BALL$"
# 851 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_LuxuryBall:
# 852 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "LUXURY BALL$"
# 853 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_SportBall:
# 854 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "SPORT BALL$"
# 855 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_ParkBall:
# 856 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "PARK BALL$"
# 857 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_SafariBall:
# 858 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "SAFARI BALL$"
# 859 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_DreamBall:
# 860 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "DREAM BALL$"
# 861 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_CherishBall:
# 862 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "CHERISH BALL$"
# 863 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtCraft_Text_StrangeBall:
# 864 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "STRANGE BALL$"
# 865 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 866 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtGsBall::
# 867 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtWhatIsThat, MSGBOX_DEFAULT
# 868 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 869 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	removeitem ITEM_GS_BALL
# 870 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 871 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 872 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 873 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_BANG
# 874 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
# 875 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 876 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	faceplayer
# 877 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_KurtThisBallStartedToShake, MSGBOX_DEFAULT
# 878 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 879 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_M_PETAL_DANCE
# 880 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitse
# 881 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_PIN
# 882 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, Common_Movement_ExclamationMark
# 883 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
# 884 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay 60
# 885 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitse
# 886 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	playse SE_M_PETAL_DANCE
# 887 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitse
# 888 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Look_Around
# 889 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTownKurt_Movement_Look_Around
# 890 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 891 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	waitmovement 0
# 892 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtGsBall2::
# 893 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_Kurt_Whatwasthat, MSGBOX_DEFAULT
# 894 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	setvar VAR_AZALEA_TOWN_STATE, 8
# 895 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 896 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 897 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 898 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 899 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_KurtGsBall3::
# 900 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_Forest, MSGBOX_DEFAULT
# 901 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 902 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay 30
# 903 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_BallAnyway, MSGBOX_DEFAULT
# 904 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 905 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	goto KurtCraft_EventScript_Entry
# 906 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	release
# 907 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 908 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_BallAnyway:
# 909 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Anyway, can I make you some Balls?$"
# 910 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 911 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_OakPhoto::
# 912 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
# 913 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 914 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 915 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 916 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
# 917 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
# 918 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
# 919 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	end
# 920 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 921 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTownKurt_Movement_Look_Around:
# 922 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_left
# 923 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 924 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_right
# 925 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 926 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_up
# 927 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 928 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_down
# 929 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 930 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_left
# 931 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 932 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 933 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTownKurt_Movement_Making_Ball:
# 934 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_up
# 935 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_in_place_fast_up
# 936 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 937 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_in_place_fast_up
# 938 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	delay_8
# 939 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_in_place_fast_up
# 940 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 941 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 942 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_Movement_Player:
# 943 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	face_right
# 944 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	lock_facing_direction
# 945 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_left
# 946 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	unlock_facing_direction
# 947 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 948 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 949 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
AzaleaTown_KurtsHouse_Movement_KurtWalkDown:
# 950 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 951 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 952 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 953 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 954 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 955 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	walk_fast_down
# 956 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	step_end
# 957 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 958 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtGetStarted:
# 959 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}I'll get started right now!$"
# 960 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 961 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtMakingBallsMustWait:
# 962 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Hm? Who are you?\p"
# 963 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{PLAYER}, eh? You want me to make\n"
# 964 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "some Balls?\p"
# 965 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Sorry, but that'll have to wait.\p"
# 966 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Do you know Team Rocket?\n"
# 967 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ah, don't worry.\p"
# 968 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I'll tell you anyhow.\p"
# 969 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Team Rocket's an evil gang that\n"
# 970 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "uses Pokémon for their dirty work.\p"
# 971 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "They're supposed to have disbanded\n"
# 972 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "three years ago.\p"
# 973 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Anyway, they're at the Well,\n"
# 974 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "cutting off Slowpoketails to sell!\p"
# 975 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "So I'm going to go give them a\n"
# 976 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "lesson in pain!\p"
# 977 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Hang on, Slowpoke! Old Kurt\n"
# 978 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "is on his way!$"
# 979 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 980 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtHonoredToMakeBalls:
# 981 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}Hi, {PLAYER}!\p"
# 982 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "You handled yourself like a\n"
# 983 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "real hero at the Well.\p"
# 984 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I like your style!\p"
# 985 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I would be honored to make\n"
# 986 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Balls for a trainer like you.\p"
# 987 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "This is all I have now, \n"
# 988 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "but take it.$"
# 989 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 990 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtBallsFromApricorns:
# 991 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}I make Balls out of Berries.\p"
# 992 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Nobody else does. The shops sell you a\n"
# 993 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Poké Ball and that's the end of their\l"
# 994 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "imagination.\p"
# 995 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Bring me Berries and tell me what you\n"
# 996 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "want. The better I get at a shape, the\l"
# 997 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "fewer Berries it costs you.$"
# 998 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 999 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtAskYouHaveAnApricorn:
# 1000 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}You've brought me Berries?\p"
# 1001 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Fine! I'll turn them into Balls.$"
# 1002 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1003 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtThatsALetdown:
# 1004 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}That's a letdown.\p"
# 1005 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I need {STR_VAR_3} {STR_VAR_1} for a\n"
# 1006 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "batch of those, and you haven't got\l"
# 1007 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "them on you.$"
# 1008 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1009 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtJustFinishedYourBall:
# 1010 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}Ah, {PLAYER}!\p"
# 1011 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I just finished your Ball. Here!$"
# 1012 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1013 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtTurnedOutGreat:
# 1014 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}That turned out great.\p"
# 1015 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Try catching Pokémon with it.$"
# 1016 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1017 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtWhatIsThat:
# 1018 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Wh-what is that?\p"
# 1019 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I've never seen one before.\p"
# 1020 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It looks a like a Poké Ball, but\n"
# 1021 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "it appears to be something else.\p"
# 1022 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Let me check it for you.$"
# 1023 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1024 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtImCheckingItNow:
# 1025 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I'm checking it now.$"
# 1026 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1027 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtAhHaISee:
# 1028 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ah-ha! I see! So…$"
# 1029 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1030 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtThisBallStartedToShake:
# 1031 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{PLAYER}!\p"
# 1032 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "This Ball started to shake\n"
# 1033 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "while I was checking it.\p"
# 1034 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "There must be something to this!$"
# 1035 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1036 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_Kurt_Whatwasthat:
# 1037 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "What was that sound?!\p"
# 1038 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Let's go outside to investigate!$"
# 1039 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1040 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterSlowpokeGone:
# 1041 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "The Slowpoke are gone… \n"
# 1042 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Were they taken away by bad people?$"
# 1043 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1044 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterLonely:
# 1045 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Grandpa's gone… I'm so lonely…$"
# 1046 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1047 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterSlowpokeBack:
# 1048 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "The Slowpoke my dad gave me came back!\p"
# 1049 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Its Tail is growing back too!$"
# 1050 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1051 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterDad:
# 1052 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Dad works at Silph where\n"
# 1053 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "he studies Poké Balls.\p"
# 1054 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I have to stay home\n"
# 1055 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "with Grandpa and Slowpoke.$"
# 1056 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1057 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterHelp:
# 1058 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I get to help Grandpa now!\p"
# 1059 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "We'll make good Balls\n"
# 1060 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "for you, so please wait!$"
# 1061 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1062 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterFun:
# 1063 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It's fun to make Balls!$"
# 1064 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1065 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterSound:
# 1066 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Did that sound come from\n"
# 1067 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ilex Forest????$"
# 1068 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1069 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_Forest:
# 1070 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Did you check Ilex Forest yet?\n"
# 1071 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It sounds very restless.$"
# 1072 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1073 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_Slowpoke:
# 1074 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Slowpoke: … Yawn?$"
# 1075 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1076 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_OakPhoto:
# 1077 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "…A young Prof. Oak?$"
# 1078 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1079 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_CelebiStatue:
# 1080 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "It's a statue of the forest's\n"
# 1081 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "protector.$"
# 1082 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ opens the group menu
# 1083 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtWhatToday:
# 1084 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}Right then. What are we making?$"
# 1085 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1086 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ the quota is spent
# 1087 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtQuotaSpent:
# 1088 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}That's my lot for today.\p"
# 1089 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ball-making isn't stirring soup,\n"
# 1090 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{PLAYER}. Each one takes what it takes,\l"
# 1091 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "and these hands only have so many in\l"
# 1092 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "them before the shells start coming out\l"
# 1093 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "crooked.\p"
# 1094 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Come back in the morning. I'll have the\n"
# 1095 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "fire up.$"
# 1096 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1097 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtComeBack:
# 1098 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}Suit yourself.\p"
# 1099 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I'll be here. I'm always here.$"
# 1100 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1101 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtNoRoom:
# 1102 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}Hold on -- where were you planning to\n"
# 1103 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "put them?\p"
# 1104 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Your bag's full, lad. Go and make room.\n"
# 1105 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Nothing's wasted: I haven't touched\l"
# 1106 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "your Berries.$"
# 1107 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1108 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ the free daily draw, no exp
# 1109 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtTodaysSurplus:
# 1110 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}Here's what I had spare this morning.\p"
# 1111 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Come by tomorrow and there'll be more.\n"
# 1112 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "There always is.$"
# 1113 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1114 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
@ the sixteenth face of the die
# 1115 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_KurtMasterpiece:
# 1116 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "{SPEAKER NAME_KURT}…Well, now.\p"
# 1117 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "This one's a masterpiece. I can hardly\n"
# 1118 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "believe I managed to craft it.\p"
# 1119 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Don't ask me to make another. I\n"
# 1120 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "couldn't tell you how I did it.$"
# 1121 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterTierOne:
# 1122 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Grandpa only knows the easy shapes\n"
# 1123 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "right now.\p"
# 1124 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "He gets grumpy about it. He says his\n"
# 1125 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "hands have forgotten and they need\l"
# 1126 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "reminding.\p"
# 1127 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Bring him more Berries! That's how you\n"
# 1128 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "remind hands.$"
# 1129 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1130 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterTierTwo:
# 1131 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "He's doing the old ones again! The ones\n"
# 1132 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "with the funny names.\p"
# 1133 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "He made a Lure Ball yesterday and then\n"
# 1134 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "he sat looking at it for ages and didn't\l"
# 1135 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "say anything.\p"
# 1136 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I think he was happy. It's hard to tell\n"
# 1137 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "with Grandpa.$"
# 1138 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1139 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterTierThree:
# 1140 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "He's started making the new-fangled\n"
# 1141 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "ones.\p"
# 1142 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "He complains the whole time. He says\n"
# 1143 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "they're all springs and no soul.\p"
# 1144 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "…He's very good at them, though. Don't\n"
# 1145 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "tell him I said that.$"
# 1146 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"

# 1147 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
KurtsHouse_Text_GranddaughterTierFour:
# 1148 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Grandpa can make anything now.\p"
# 1149 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "He uses hardly any Berries any more,\n"
# 1150 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "either. He says that's what getting\l"
# 1151 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "good means -- wasting less.\p"
# 1152 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "Ask him for the strange one. He\n"
# 1153 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "pretends he hates it and he laughs\l"
# 1154 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "every single time.$"

KurtMakesBallsDaily::
# 1158 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	msgbox KurtMakesBallsDaily_Text_0
# 1160 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	closemessage
	return


KurtMakesBallsDaily_Text_0:
# 1158 "data/maps/AzaleaTown_KurtsHouse/scripts.pory"
	.string "I will give you any surplus Poké Balls\n"
	.string "I create every day, so stop by!$"
