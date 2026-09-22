.set LOCALID_MAHOGANY_MERCHANT, 3

Mahoganytown_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Mahoganytown_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, Mahoganytown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Mahoganytown_OnFrame
	.byte 0

Mahoganytown_OnTransition::
	call Mahoganytown_EventScript_ApplyUBVisibility
	end

@ Rift Mission 2 visibility, recomputed on every map load (ON_TRANSITION runs
@ before the first spawn, and ClearTempFieldEventData has just zeroed every
@ temp, so this must run unconditionally). Also runs when arriving on foot
@ from Route 42/44 or through the Route 43 gate, not only through a warp.
@   FLAG_TEMP_1 - the cast (Ninetales, Lillie, Looker, Anabel): shown only
@                 while the incident is active.
@   FLAG_TEMP_2 - the Ultra Beasts: always hidden at load; only the scene
@                 itself brings them in, so a retry after a blackout starts
@                 from a clean street.
Mahoganytown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	goto_if_unset FLAG_EVENT_ULTRABEAST_MAHOGANY, Mahoganytown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	return

Mahoganytown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	return

Mahoganytown_OnLoad::
	call_if_ge VAR_MAHOGANY_TOWN_STATE, 13, MahoganyTown_EventScript_FixTree
	setrespawn HEAL_LOCATION_MAHOGANYTOWN
	end

MahoganyTown_EventScript_FixTree::
	setmetatile 18, 8, 0x4F8, FALSE
	setmetatile 19, 8, 0x4F9, FALSE
	end

Mahoganytown_OnFrame::
	map_script_2 VAR_MAHOGANY_TOWN_STATE, 15, Mahoganytown_EventScript_RocketTrigger
	.2byte 0


Mahoganytown_EventScript_RocketTrigger::
	lock
	pokenavcall ElmPhoneRadioTowerRocketTakeoverText
	waitmessage
	setvar VAR_GOLDENROD_CITY_STATE, 6
	clearflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	setflag FLAG_HIDE_GOLDENROD_NPCS
	setflag FLAG_HIDE_RADIOF5DUDE
	clearflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setvar VAR_MAHOGANY_TOWN_STATE, 16
	delay 10
	release
	end

MahoganyTown_EventScript_TownTrigger::
	clearflag FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	clearflag FLAG_HIDE_MAHOGANY_TOWN_FATMAN
	clearflag FLAG_HIDE_MAHOGANY_ROCKETS
	clearflag FLAG_GOT_TM_FROM_MAHOGANY_COP
	clearflag FLAG_GOT_BLACK_BELT
	clearflag FLAG_ROCKETHIDEOUT_SWITCH
	clearflag FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	clearflag FLAG_HIDE_ROCKETHIDEOUT2_GATE
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_GATE
	clearflag FLAG_GOT_PASSWORD_FROM_ETO
	clearflag FLAG_GOT_PASSWORD_FROM_GRUNTF 
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROW
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI
	clearflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE1 
	clearflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE2
	clearflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE3 
	clearflag FLAG_GOT_HIDDEN_POWER
	clearflag FLAG_HIDE_ICE_PATH_KIMONO

	setflag FLAG_VISITED_MAHOGANY_TOWN
	setflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	setflag FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	setflag FLAG_HIDE_MAHOGANY_COP
	setflag FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	setflag FLAG_HIDE_ROCKETHIDEOUT3_SILVER
	setflag FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT

	setvar VAR_ROCKET_HIDEOUT_STATUE_1, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_2, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_3, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_4, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_5, 0
	setvar VAR_ROCKET_PASSWORD, 0
	setvar VAR_ELECTRODES_FAINTED, 0
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 0
	setvar VAR_ICE_PATH_STATE, 0
	setvar VAR_ROUTE27_BAOBA_CALL, 0

	setvar VAR_MAHOGANY_TOWN_STATE, 1

	@blackthorn flagheap
	setvar VAR_BLACKTHORN_CITY_STATE, 1
    setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_SILVER
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_LANCE
	setflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	clearflag FLAG_GOT_SPELL_TAG
	clearflag FLAG_GOT_DRATINI
	setvar VAR_BLACKTHORN_GYM_STATE, 0
	setvar VAR_DRAGONS_DEN_QUIZ, 0
	end

MahoganyTown_EventScript_MerchantTrigger::
	lock
	turnobject LOCALID_MAHOGANY_MERCHANT, DIR_SOUTH
	playse SE_PIN
	applymovement LOCALID_MAHOGANY_MERCHANT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 14, MahoganyTown_EventScript_WalkUp2
	call_if_eq VAR_TEMP_1, 13, MahoganyTown_EventScript_WalkUp1
	showmoneybox 0, 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantRefused
	checkmoney 300, 0
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantBroke
	removemoney 300
	updatemoneybox 0
	playse SE_SHOP
	waitse
	hidemoneybox
	msgbox MahoganyTown_Text_RageCandyBarMerchantSavorIt, MSGBOX_DEFAULT
	giveitem ITEM_RAGE_CANDY_BAR
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_WalkUp1::
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyTown_Movement_PlayerMerchant1
	waitmovement 0
	return

MahoganyTown_EventScript_WalkUp2::
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyTown_Movement_PlayerMerchant2
	waitmovement 0
	return

MahoganyTown_EventScript_Merchant::
	lock
	faceplayer
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 17, MahoganyTown_EventScript_MerchantAfter
	showmoneybox 0, 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantRefused
	checkmoney 300, 0
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantBroke
	removemoney 300
	updatemoneybox 0
	playse SE_SHOP
	waitse
	hidemoneybox
	msgbox MahoganyTown_Text_RageCandyBarMerchantSavorIt, MSGBOX_DEFAULT
	giveitem ITEM_RAGE_CANDY_BAR
	hidemoneybox
	closemessage
	release
	end

MahoganyTown_EventScript_MerchantRefused::
	msgbox MahoganyTown_Text_RageCandyBarMerchantRefused, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_MerchantBroke::
	msgbox MahoganyTown_Text_RageCandyBarMerchantNotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_NotEnoughSpace:
	msgbox MahoganyTown_Text_RageCandyBarMerchantRefused, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	return

MahoganyTown_EventScript_MerchantAfter::
	msgbox MahoganyTown_Text_RageCandyBarMerchantSoldOut, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_PushPlayer::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	return

MahoganyTown_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 6, MahoganyTown_EventScript_GrampsAfter
	msgbox MahoganyTown_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_GrampsAfter::
	msgbox MahoganyTown_Text_GrampsClearedRocketHideout, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Fisher::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Lass::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Sign::
	lock
	msgbox MahoganyTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_EventScript_CandybarSign::
	lock
	msgbox MahoganyTown_Text_RagecandybarSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_EventScript_GymSign::
	lock
	msgbox MahoganyTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_Movement_PlayerMerchant1:
	walk_up
	step_end

MahoganyTown_Movement_PlayerMerchant2:
	walk_up
	walk_up
	step_end

MahoganyTown_Text_RageCandyBarMerchantTryOne:
	.string "Hiya, kid!\p"
	.string "I see you're new in Mahogany Town.\p"
	.string "Since you're new, you should try a\n"
	.string "yummy Ragecandybar!\p"
	.string "Right now, it can be yours for just\n"
	.string "¥300! Want one?$"

MahoganyTown_Text_RageCandyBarMerchantSavorIt:
    .string "Good! Savor it!$"

MahoganyTown_Text_RageCandyBarMerchantNotEnoughMoney:
    .string "You don't have enough money.$"

MahoganyTown_Text_RageCandyBarMerchantRefused:
    .string "Oh, fine then…$"

MahoganyTown_Text_RageCandyBarMerchantSoldOut:
    .string "Ragecandybar's sold out.\p"
    .string "I'm packing up. Don't bother me,\n"
    .string "kiddo.$"

MahoganyTown_Text_Gramps:
    .string "Are you off to see the Gyarados\n"
    .string "rampage at the Lake?$"

MahoganyTown_Text_GrampsClearedRocketHideout:
    .string "Magikarp have returned to Lake\n"
    .string "Of Rage.\p"
    .string "That should be good news for the\n"
    .string "anglers there.$"

MahoganyTown_Text_Fisher:
    .string "Since you came this far, take the\n"
    .string "time to do some sightseeing.\p"
    .string "You should head north and check\n"
    .string "out Lake Of Rage right now.$"

MahoganyTown_Text_Lass:
    .string "Visit Grandma's shop. She sells\n"
    .string "stuff that nobody else has.$"

MahoganyTown_Text_Sign:
    .string "Mahogany Town\p"
    .string "Welcome to the Home of the Ninja$"

MahoganyTown_Text_RagecandybarSign:
    .string "While visiting Mahogany Town, try\n"
    .string "a Ragecandybar!$"

MahoganyTown_Text_GymSign:
    .string "Mahogany Town Pokémon Gym\p"
    .string "Leader: Pryce\p"
    .string "The Teacher of Winter's Harshness$"

ElmPhoneRadioTowerRocketTakeoverText:
	.string "Prof. Elm: {PLAYER}, how are\n"
	.string "things going?\p"
	.string "I called because something weird\n"
	.string "is happening with the radio\l"
	.string "broadcasts.\p"
	.string "They were talking about Team\n"
	.string "Rocket.\p"
	.string "{PLAYER}, do you know anything\n"
	.string "about it?\p"
	.string "Maybe Team Rocket has returned.\n"
	.string "No, that just can't be true.\p"
	.string "Sorry to bug you.\n"
	.string "Take care!$"

ElmPhoneRoute39LegendaryText:
	.string "Prof. Elm: Woah!\n"
	.string "{PLAYER}, did you see that?!\p"
	.string "A massive Pokémon just flew over\n"
	.string "Ecruteak City!\l"
	.string "I could see it from my Lab!\p"
	.string "Could it be one of the legendary\n"
	.string "Pokémon??\p"
	.string "It looked like it was headed West,\n"
	.string "toward Route 39.\p"
	.string "{PLAYER}!\n"
	.string "This may be a rare opportunity\l"
	.string "to give chase!$"

@ ============================================================================
@ Rift Mission 2 - Xurkitree + Celesteela in Mahogany Town.
@
@ Active while FLAG_EVENT_ULTRABEAST_MAHOGANY is set, which by invariant means
@ VAR_RIFT_MISSIONS_STATE == 5. Set by OlivineCity_House1, cleared here on
@ victory together with state 6.
@
@ Scene floor plan (raw collision, bit 11; '#' = blocked; y grows DOWNWARD):
@
@        x= 11 12 13 14 15 16 17 18 19 20 21 22 23 24
@   y=19      #  #  .  .  .  .  .  .  #  #  W  #  #  #   W (21,19) Center door
@   y=20      .  .  .  .  .  .  .  .  .  .  f  .  .  .   f (21,20) Fly landing
@   y=21      .  .  X  .  .  .  .  .  .  .  t  .  .  .   t (21,21) talk to Looker
@   y=22      .  .  C  .  .  .  *  .  N  L  K  A  .  .   * (17,22) player's spot
@   y=23      #  #  #  #  #  #  #  #  #  #  #  #  #  #
@
@   N Ninetales (19,22)   L Lillie (20,22)
@   K Looker    (21,22)   A Anabel (22,22)
@   X Xurkitree (13,21)   C Celesteela (13,22)  - X/C hidden until the scene
@
@ Looker sits in a pocket: (21,23) is wall, (20,22) is Lillie and (22,22) is
@ Anabel. The ONLY tile he can be talked to from is (21,21), facing down.
@ That is what makes the start of the cutscene deterministic without a
@ getplayerxy check. HEAL_LOCATION_MAHOGANYTOWN is (21,20), one step north of
@ it, so a blackout retry lands right next to him.
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1 - cast visibility cache      (see ApplyUBVisibility above)
@   FLAG_TEMP_2 - Ultra Beast visibility cache
@   VAR_TEMP_2  - battle outcome
@   VAR_TEMP_3  - the player's pick: 0 = Xurkitree, 1 = Celesteela. Survives
@                 the battle because returning from a battle does not reload
@                 the map (ClearTempFieldEventData only runs on warp/edge
@                 loads).
@ WARNING: VAR_TEMP_0 and VAR_TEMP_1 belong to the Rage Candy Bar merchant
@ (getplayerxy, above in this file). This mission starts at VAR_TEMP_2 on
@ purpose - do NOT "harmonise" it with the Blackthorn mission.
@
@ WARNING: the eight residents of this map now carry
@ FLAG_EVENT_ULTRABEAST_MAHOGANY in their map.json "flag" field. A
@ removeobject on any of them SETS that flag and empties the town.
@ ============================================================================

@ SKELETON: placeholder line, rewrite in the design's voice (Anabel precise).
Mahoganytown_EventScript_UBAnabel::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBAnabelIdle, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Lillie and Ninetales watch the street to the north (FACE_UP in map.json),
@ and must still be facing that way when the scene starts.
@ The turnobject is a deliberate no-op today: (20,23) is wall, (19,22) is
@ Ninetales and (21,22) is Looker, so the player can ONLY reach her from
@ (20,21) and faceplayer already leaves her facing north. It stays as the
@ guard for any evolution that moves her.
@ SKELETON: placeholder line.
Mahoganytown_EventScript_UBLillie::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBLillieIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_NORTH
	release
	end

@ Nothing changes state before the YES. The YES is the last exit point: from
@ there on everything is scripted through to a battle outcome.
@ Lillie's theory comes BEFORE the YES on purpose: she has to have told the
@ group her reading before anyone moves (design section 3.2).
Mahoganytown_EventScript_UBLooker::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox Mahoganytown_Text_UBLillieTheory, MSGBOX_DEFAULT
	msgbox Mahoganytown_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Mahoganytown_EventScript_UBNotReady
	goto Mahoganytown_EventScript_UBScene

Mahoganytown_EventScript_UBNotReady::
	msgbox Mahoganytown_Text_UBNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

@ SKELETON: the rift is a camera shake plus a white flash and the beasts
@ appear standing still. Evolution: the town's blackout staged with the
@ palette/weather, the lights coming back at the end, a portal animation,
@ its own music.
@
@ The order of the three applymovement blocks is LOAD-BEARING:
@ Lillie/Ninetales -> player -> Looker/Anabel. Ninetales walks through
@ (17,22), which is the player's final tile; and Looker/Anabel can only step
@ up once the player has vacated (21,21).
Mahoganytown_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	@ Ninetales (19,22)->(18,22)->(17,22)->(16,22)->(15,22)->(15,21), faces west.
	@ Lillie    (20,22)->(20,21)->(19,21)->(18,21)->(17,21)->(16,21), faces west.
	@ Different rows the whole way (he on y=22, she on y=21) and no shared
	@ tile on any step, so they walk together. The partner goes in front.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesAdvance
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieAdvance
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	@ Player (21,21)->(20,21)->(19,21)->(18,21)->(17,21)->(17,22), faces west.
	@ Only after those two: (17,22) is on Ninetales' path.
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	@ Looker (21,22)->(21,21) and Anabel (22,22)->(22,21): different columns,
	@ no contention, so they walk together. (21,21) only frees up when the
	@ player leaves it, above.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_StepUpFaceLeft
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_StepUpFaceLeft
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	msgbox Mahoganytown_Text_UBRiftWarning, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 24  @ num shakes
	setvar VAR_0x8007, 5   @ shake delay
	special ShakeCamera
	waitstate
	fadescreen FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_MAHOGANY_UB_XURKITREE
	addobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Mahoganytown_Text_UBAppear, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBChoose

@ Standard Rift Mission structure: the player picks which Ultra Beast to
@ fight, the mission companion takes the other. No cancel (ignoreBPress
@ TRUE) - the scene has already started, so VAR_RESULT can only be 0 or 1.
@ The pick is per attempt: after a blackout the player chooses again.
@ Everyone already faces the right way whichever branch is taken: the player
@ (17,22) and Lillie (16,21) are east of both beasts at x=13, and the beasts
@ face east. No turnobject is needed.
Mahoganytown_EventScript_UBChoose::
	msgbox Mahoganytown_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, Mahoganytown_Text_ChoiceXurkitree, Mahoganytown_Text_ChoiceCelesteela
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Xurkitree, 1 = Celesteela
	closemessage
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBPickCelesteela
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	msgbox Mahoganytown_Text_UBPickedXurkitree, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle

Mahoganytown_EventScript_UBPickCelesteela::
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	msgbox Mahoganytown_Text_UBPickedCelesteela, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle

@ Boss battle through the project's boss system. Boss setup only survives a
@ SIMPLE battle, which is the other reason the mission splits the beasts.
@ B_FLAG_NO_WHITEOUT is deliberately NOT set: this is a threat battle, so
@ losing means a blackout and a retry.
@
@ NOT a skeleton: the numbers below are the target. Deliberate escalation
@ over Blackthorn (2 bars / Lv70 / x110), which stays the tutorial mission.
@ 4 is MAX_BOSS_HEALTH_BARS; x130 is the first multiplier in this repo above
@ the x110 default. If playtesting says "wall" instead of "threat", turn the
@ screws in this order, one at a time: 130 -> 120, 4 bars -> 3, drop the held
@ item, and only then the level. Do not touch anything in section 1 of the
@ implementation doc to compensate.
@
@ Macro order is the same as bosslegendaryencounterwithmoves
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
@ seteventmonmoves -> special. No path leaves the script in between, so no
@ clearbossbattle is needed.
Mahoganytown_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBSetupCelesteela
	setbossbattle 4, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_XURKITREE, 80, ITEM_MAGNET
	seteventmonmoves MOVE_TAIL_GLOW, MOVE_THUNDERBOLT, MOVE_ENERGY_BALL, MOVE_DAZZLING_GLEAM
	goto Mahoganytown_EventScript_UBStartBattle

Mahoganytown_EventScript_UBSetupCelesteela::
	setbossbattle 4, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_CELESTEELA, 80, ITEM_LEFTOVERS
	seteventmonmoves MOVE_HEAVY_SLAM, MOVE_FLAMETHROWER, MOVE_EARTHQUAKE, MOVE_AIR_SLASH

@ LOST, DREW and FORFEITED never come back here - the engine blacks the
@ player out to the Mahogany Pokémon Center (Mahoganytown_OnLoad does the
@ setrespawn). CAUGHT and RAN are unreachable (ball blocked; Run becomes
@ FORFEITED in a boss) but are handled anyway: anything that is not WON
@ resets the scene, never wins it.
Mahoganytown_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, Mahoganytown_EventScript_UBResolved
	goto Mahoganytown_EventScript_UBUnresolved

@ Nothing was recorded as done: the event flag is still set, so reloading the
@ map puts the cast back on its map.json spots with the beasts hidden again,
@ and talking to Looker restarts the whole scene - the pick included.
@ (21,20) is the Fly landing / Center exit tile, one step from Looker's talk
@ tile.
Mahoganytown_EventScript_UBUnresolved::
	msgbox Mahoganytown_Text_UBGotAway, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_MAHOGANYTOWN, 21, 20
	waitstate
	releaseall
	end

@ Lillie's fight against the other beast is narrative: it resolves with the
@ player's win and only her line afterwards changes with the pick.
@ SKELETON: evolution can stage her fight on screen (Ninetales, Snow, the
@ beast backing off). A real battle against Lillie is NOT the plan.
Mahoganytown_EventScript_UBResolved::
	@ Both beast objects are still on the map: a battle does not reload it.
	@ Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_XURKITREE
	removeobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreen FADE_FROM_WHITE
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBLillieFoughtXurkitree
	msgbox Mahoganytown_Text_UBLillieFoughtCelesteela, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBAfterBattle

Mahoganytown_EventScript_UBLillieFoughtXurkitree::
	msgbox Mahoganytown_Text_UBLillieFoughtXurkitree, MSGBOX_DEFAULT

Mahoganytown_EventScript_UBAfterBattle::
	msgbox Mahoganytown_Text_UBAfterLillie, MSGBOX_DEFAULT
	closemessage
	@ Looker (21,21)->(20,21)->(19,21)->(18,21), faces west at the player.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_LookerToPlayer
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	@ Anabel (22,21)->(22,22)->(21,22)->(20,22)->(19,22)->(18,22), faces
	@ west. Her row (y=22) is clear because Lillie and Ninetales are on
	@ y=21, and she is always behind the player at (17,22). SEQUENTIAL after
	@ Looker purely so the scene reads one actor at a time.
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToPlayer
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_SOUTH      @ player (17,22) is below (16,21)
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_SOUTH
	msgbox Mahoganytown_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_MAHOGANY      @ invariant: flag and var together
	setvar VAR_RIFT_MISSIONS_STATE, 6
	@ Reload in place under the fade. With the flag cleared the residents
	@ would otherwise pop in one by one as the camera moved, and the cast
	@ would linger; ON_TRANSITION repopulates the town and hides the cast in
	@ one go. Lillie and Ninetales leave together, as they must, and the
	@ warp also undoes the hidefollower.
	warpsilent MAP_MAHOGANYTOWN, 17, 22
	waitstate
	releaseall
	end

Mahoganytown_Movement_NinetalesAdvance:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_left
	step_end

Mahoganytown_Movement_LillieAdvance:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

Mahoganytown_Movement_PlayerToLine:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	face_left
	step_end

Mahoganytown_Movement_StepUpFaceLeft:
	walk_up
	face_left
	step_end

Mahoganytown_Movement_LookerToPlayer:
	walk_left
	walk_left
	walk_left
	face_left
	step_end

Mahoganytown_Movement_AnabelToPlayer:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

@ SKELETON: all dialogue below is placeholder. Rewrite in the design's voice
@ (Lillie observant and firm; Looker theatrical and warm; Anabel precise).
@ See SOULGOLD_RIFT_MISSIONS_DESIGN.md section 3.1.
Mahoganytown_Text_UBAnabelIdle:
	.string "Anabel: The residents are in the\n"
	.string "Gym basement.\p"
	.string "Pryce opened it himself.\p"
	.string "Speak with Looker when you're\n"
	.string "ready.$"

Mahoganytown_Text_UBLillieIdle:
	.string "Lillie: {PLAYER}. I was hoping it\n"
	.string "would be you.\p"
	.string "I've watched them for two days.\p"
	.string "I'd rather explain it to everyone\n"
	.string "at once - go on, talk to Looker.$"

Mahoganytown_Text_UBLookerGreet:
	.string "Looker: {PLAYER}! You are here,\n"
	.string "and the street is empty.\l"
	.string "Excellent.\p"
	.string "The power is still out. Whatever\n"
	.string "is drawing it has not finished.$"

Mahoganytown_Text_UBLillieTheory:
	.string "Lillie: May I? I've had two days\n"
	.string "to watch them.\p"
	.string "Looker: Please, mademoiselle.\p"
	.string "Lillie: They aren't hunting\n"
	.string "anything. They're feeding each\l"
	.string "other.\p"
	.string "The tall one pulls the current out\n"
	.string "of everything in the town.\p"
	.string "The other burns it off, and the\n"
	.string "air fills up again.\p"
	.string "Looker: …Forgive me. That is a\n"
	.string "great deal to conclude from\l"
	.string "notes.\p"
	.string "Lillie: It's what I saw. Four\n"
	.string "times, at the same interval.\p"
	.string "If we push them both at once,\n"
	.string "they only come back stronger.\p"
	.string "We have to split them and hold\n"
	.string "them apart.\p"
	.string "Anabel: She's right. The\n"
	.string "instruments show the same cycle.\p"
	.string "I should have read it sooner.\p"
	.string "Looker: Then we do it her way.$"

Mahoganytown_Text_UBReady:
	.string "Looker: One warning, {PLAYER}.\p"
	.string "These two have been feeding for\n"
	.string "three nights.\p"
	.string "They are not what we met in\n"
	.string "Blackthorn.\p"
	.string "Anabel: Bring everything you\n"
	.string "have. Are you ready?$"

Mahoganytown_Text_UBNotReady:
	.string "Looker: Wise.\p"
	.string "The Center still has its own\n"
	.string "generator. I will be here.$"

Mahoganytown_Text_UBRiftWarning:
	.string "Lillie: There. The air is folding\n"
	.string "over itself- get back!$"

Mahoganytown_Text_UBAppear:
	.string "Looker: Xurkitree! And\n"
	.string "Celesteela!\p"
	.string "Anabel: …I felt that one before\n"
	.string "the readings moved.\p"
	.string "Anabel: Never mind. Later.$"

Mahoganytown_Text_UBChoosePrompt:
	.string "Lillie: We split them now, while\n"
	.string "they're still apart.\p"
	.string "Pick one, {PLAYER}. Ninetales and\n"
	.string "I will hold the other.$"

Mahoganytown_Text_ChoiceXurkitree:
	.string "Xurkitree$"

Mahoganytown_Text_ChoiceCelesteela:
	.string "Celesteela$"

Mahoganytown_Text_UBPickedXurkitree:
	.string "Lillie: Then the tall one is\n"
	.string "ours.\p"
	.string "Ninetales - Snow, now!$"

Mahoganytown_Text_UBPickedCelesteela:
	.string "Lillie: All right.\p"
	.string "Ninetales, get between it and the\n"
	.string "power lines.\p"
	.string "Don't let it drink!$"

Mahoganytown_Text_UBGotAway:
	.string "Looker: They closed the gap\n"
	.string "again… The cycle starts over.\p"
	.string "Lillie: Then we do it again.\n"
	.string "I'm not leaving.$"

Mahoganytown_Text_UBLillieFoughtCelesteela:
	.string "Lillie: Celesteela never got off\n"
	.string "the ground.\p"
	.string "Ninetales kept the air cold, and\n"
	.string "it stayed heavy.$"

Mahoganytown_Text_UBLillieFoughtXurkitree:
	.string "Lillie: Xurkitree had nothing\n"
	.string "left to pull.\p"
	.string "We kept it off the lines until it\n"
	.string "went dim.$"

Mahoganytown_Text_UBAfterLillie:
	.string "Lillie: They're going back on\n"
	.string "their own now.\p"
	.string "Look - they're not even fighting\n"
	.string "it.\p"
	.string "…I was right about them.\n"
	.string "I'm glad I said it out loud.$"

Mahoganytown_Text_UBHook:
	.string "Looker: Magnifique! And the\n"
	.string "lamps - {PLAYER}, look!\p"
	.string "The town has its light back!\p"
	.string "Anabel: Lillie. Your reading was\n"
	.string "better than my instruments.\p"
	.string "I'd like your notes.\p"
	.string "Lillie: You can have all of them.\n"
	.string "I'm going to keep watching.\p"
	.string "Looker: One more thing before you\n"
	.string "rest, {PLAYER}.\p"
	.string "A report came in while we were\n"
	.string "busy.\p"
	.string "Anabel: Cherrygrove City. Two\n"
	.string "more signatures…\p"
	.string "…and a man in a lab coat who will\n"
	.string "not leave the shore.\p"
	.string "Looker: Professor Kukui. But of\n"
	.string "course it is Professor Kukui.\p"
	.string "Anabel: Come back to the house in\n"
	.string "Olivine when you're ready.\p"
	.string "We'll brief you there.\p"
	.string "Lillie: Cherrygrove…\p"
	.string "Tell the Professor I'm fine.\n"
	.string "He worries.$"
