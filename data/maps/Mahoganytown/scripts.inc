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
@   FLAG_TEMP_1 - Looker and Anabel: shown only while the incident is active.
@   FLAG_TEMP_2 - the Ultra Beasts: hidden at load on a first attempt; only
@                 the scene brings them in. A retry puts them straight back.
@   FLAG_TEMP_3 - Hector and his grandson at the Gym door: shown with the
@                 incident, walked inside by the scene, gone on a retry.
@   FLAG_TEMP_4 - Necrozma, like the beasts.
@   FLAG_TEMP_5 - Pryce + Mamoswine: shown with the incident.
@   FLAG_TEMP_6 - the rift on the west flank, like Necrozma.
@   FLAG_TEMP_7 - the player's own Cosmog-family Pokemon as an actor (four
@                 templates, one flag, at most one ever added).
@   FLAG_TEMP_8 - Lillie + Ninetales. Their own flag and not FLAG_TEMP_1,
@                 because they are the only two who stay on the street after
@                 the mission is over (see the settling branch below).
@
@ Three shapes of street, in the order they are tested:
@   1. the mission is over and Lillie promised to stay until the residents
@      were settled: only Lillie and Ninetales, for this one load.
@   2. incident active + FLAG_MAHOGANY_UB_ENGAGED: a retry after a blackout.
@      Everything the player already saw is back where it stood.
@   3. incident active, first attempt: the town as the player finds it.
Mahoganytown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	goto_if_set FLAG_MAHOGANY_UB_LILLIE_SETTLING, Mahoganytown_EventScript_StageUBSettling
	goto_if_unset FLAG_EVENT_ULTRABEAST_MAHOGANY, Mahoganytown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_8
	goto_if_set FLAG_MAHOGANY_UB_ENGAGED, Mahoganytown_EventScript_StageUBRetry
	return

Mahoganytown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_8
	return

@ The one load after the victory. The flag is CONSUMED here, so leaving town
@ and coming back finds the street empty: Lillie said she would stay until the
@ residents were settled, not that she would live here.
@ Looker, Anabel, Pryce and the residents are not staged: they left in the
@ scene, and the eight everyday residents of Mahogany come back on their own
@ now that FLAG_EVENT_ULTRABEAST_MAHOGANY is clear.
Mahoganytown_EventScript_StageUBSettling::
	clearflag FLAG_MAHOGANY_UB_LILLIE_SETTLING
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	clearflag FLAG_TEMP_8
	setobjectxyperm LOCALID_MAHOGANY_UB_LILLIE, 20, 21
	setobjectxyperm LOCALID_MAHOGANY_UB_NINETALES, 19, 21
	return

@ A blackout wiped every FLAG_TEMP_*, so the retry has to rebuild the street
@ by hand: the residents are already inside (FLAG_TEMP_3 stays set), the rift,
@ Necrozma and the two beasts are back, and everybody stands on the tile they
@ held when the battle started - NOT on the map.json tile they were found on.
@ setobjectxyperm writes the template, so it has to happen here, before the
@ objects spawn.
Mahoganytown_EventScript_StageUBRetry::
	setflag FLAG_TEMP_3
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_4
	clearflag FLAG_TEMP_6
	setobjectxyperm LOCALID_MAHOGANY_UB_RIFT, 7, 22
	setobjectxyperm LOCALID_MAHOGANY_UB_NECROZMA, 8, 22
	setobjectxyperm LOCALID_MAHOGANY_UB_PRYCE, 10, 21
	setobjectxyperm LOCALID_MAHOGANY_UB_MAMOSWINE, 10, 22
	setobjectxyperm LOCALID_MAHOGANY_UB_LOOKER, 12, 20
	setobjectxyperm LOCALID_MAHOGANY_UB_XURKITREE, 15, 20
	setobjectxyperm LOCALID_MAHOGANY_UB_CELESTEELA, 15, 24
	setobjectxyperm LOCALID_MAHOGANY_UB_LILLIE, 19, 22
	setobjectxyperm LOCALID_MAHOGANY_UB_NINETALES, 19, 23
	setobjectxyperm LOCALID_MAHOGANY_UB_ANABEL, 20, 22
	return

@ ON_LOAD, not ON_TRANSITION: setmetatile has to land before the map is drawn.
@ The wall of ice only exists on a retry that already got as far as building
@ it: the player finds it standing, and the beat that cracks it open opens the
@ retry scene (Mahoganytown_EventScript_UBSceneRetry).
Mahoganytown_OnLoad::
	call_if_ge VAR_MAHOGANY_TOWN_STATE, 13, MahoganyTown_EventScript_FixTree
	call_if_set FLAG_MAHOGANY_UB_SAW_RECHARGE, MahoganyTown_EventScript_PaintIceWall
	setrespawn HEAL_LOCATION_MAHOGANYTOWN
	end

MahoganyTown_EventScript_FixTree::
	setmetatile 18, 8, 0x4F8, FALSE
	setmetatile 19, 8, 0x4F9, FALSE
	end

@ (14,22) (15,22) (16,22): straight across the flow that runs down column 15
@ between Xurkitree (15,20) and Celesteela (15,24). Impassable, and drawn on
@ the middle layer, so anything standing next to it is drawn in front of it.
MahoganyTown_EventScript_PaintIceWall::
	setmetatile 14, 22, METATILE_MahoganyTown_IceWall_Left, TRUE
	setmetatile 15, 22, METATILE_MahoganyTown_IceWall_Middle, TRUE
	setmetatile 16, 22, METATILE_MahoganyTown_IceWall_Right, TRUE
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
@ Rift Mission 2 - Necrozma, Xurkitree + Celesteela in Mahogany Town.
@
@ Active while FLAG_EVENT_ULTRABEAST_MAHOGANY is set, which by invariant means
@ VAR_RIFT_MISSIONS_STATE == 5. Set by OlivineCity_House1 once Looker has
@ telephoned (FLAG_RIFT_LOOKER_SUMMONS) and the briefing has been heard;
@ cleared here on victory together with state 6. While it is set, every
@ building door in town is locked except the Pokemon Center's
@ (sLockedTownDoors in src/field_control_avatar.c ->
@ Mahoganytown_EventScript_DoorLocked). The Route 43 gate and Valor Cavern are
@ non-animated doors and stay open.
@
@ Story in three lines. Lillie has been watching two Ultra Beasts from a Gym
@ window and worked out that a light runs from one to the other; the group
@ tries to pull them apart, and that is not enough - the far one sends its own
@ charge down the link and the beaten one gets back up. She corrects her own
@ idea and asks Pryce for a wall of ice ACROSS the light; it works, and the
@ second fight is for real. Then Necrozma reaches over the wall by a different
@ route and collects both beasts anyway - but Anabel still has their two
@ signatures afterwards, which is the first hard reason to believe the beasts
@ are alive in there.
@
@ Scene floor plan (raw collision, bit 11; '#' = blocked; y grows DOWNWARD).
@ The street was widened by two rows for this mission: y=23 and y=24 used to
@ be the fence and the rock below it (data/layouts/Mahoganytown/map.bin).
@
@        x= 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
@   y=19     .  .  .  #  W  #  #  .  .  .  .  .  .  #  #  W  #  #  #  #  #
@   y=20     .  .  .  H  .  P  .  .  .  X  .  .  .  A  K  f  .  .  .  .  .
@   y=21     .  .  .  B  .  P  .  .  .  .  .  .  .  n  L  t  .  .  .  .  .
@   y=22     .  R  N  .  .  .  M  .  i  i  i  .  .  .  .  .  .  .  .  .  .
@   y=23     .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
@   y=24     .  .  .  .  .  .  .  .  .  C  .  .  .  .  .  .  .  .  .  .  .
@   y=25     #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
@
@     W (10,19) Gym door, (21,19) Pokemon Center door
@     f (21,20) Fly landing / Center exit; t (21,20) is ALSO the only tile
@       Looker can be talked to from - see below
@     H Hector (9,20)   B grandson (9,21)   P Pryce (11,20)  M Mamoswine (12,22)
@       Mamoswine is on (12,22) and not beside Pryce: it is a 32x32 sprite and
@       on (11,21) it covered him completely.
@     A Anabel (19,20)  K Looker (20,20)    n Ninetales (19,21) L Lillie (20,21)
@     X Xurkitree (15,20)  C Celesteela (15,24)  N Necrozma (8,22)  R rift (7,22)
@     i the wall of ice, (14,22) (15,22) (16,22), painted with setmetatile
@
@ Three areas, which is the whole point of the widened street:
@   shelter   the Gym door and the last two residents, west, x=9..12
@   street    Xurkitree north (y=20), Celesteela south (y=24), three clear
@             rows between them, Necrozma on the west flank behind Pryce
@   support   the player, Lillie/Ninetales and Anabel east, x=18..20, with the
@             Pokemon Center door two steps away
@
@ Camera. The scene spawns a camera object (special SpawnCameraObject) and
@ uses two framings, because no single one covers the evacuation AND the
@ fight:
@   (13,22) shelter, x=6..20  y=18..27 - the Gym door and both detectives
@   (14,22) street,  x=7..21  y=18..27 - everybody above, all at once
@ A GBA screen is 15x10 metatiles with the camera tile at column 7, row 4, and
@ the message box covers the bottom three rows. With the camera on y=22 those
@ three rows are y=25..27, which is the rock band south of town: NOBODY is
@ ever hidden behind the box, and the south front at y=24 is still on screen.
@ That is why both framings sit on row 22 and not on row 21.
@
@ Looker sits in a pocket: (20,19) is the Pokemon Center wall, (19,20) is
@ Anabel and (20,21) is Lillie. The ONLY tile he can be talked to from is
@ (21,20), facing west. That is what makes the start of the cutscene
@ deterministic without a getplayerxy check, and it is also
@ HEAL_LOCATION_MAHOGANYTOWN, so a blackout retry lands on it.
@
@ Persistent state (all four in the CUSTOM block, all four cleared by
@ Mahoganytown_EventScript_UBFinish):
@   FLAG_MAHOGANY_UB_ENGAGED            the introductions are behind us
@   FLAG_MAHOGANY_UB_SAW_RECHARGE       the group has seen the link recharge
@   FLAG_MAHOGANY_UB_PICKED_CELESTEELA  which beast the lost attempt fought
@   FLAG_MAHOGANY_UB_LILLIE_SETTLING    consumed by the next ON_TRANSITION
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1..8 - visibility (see ApplyUBVisibility at the top of the file)
@   VAR_TEMP_2  - battle outcome
@   VAR_TEMP_3  - the player's pick: 0 = Xurkitree, 1 = Celesteela. Survives
@                 both battles because returning from a battle does not reload
@                 the map. A blackout DOES, which is why the pick is mirrored
@                 into FLAG_MAHOGANY_UB_PICKED_CELESTEELA.
@   VAR_TEMP_4  - Cosmog-family species that came out of its Ball, or
@                 SPECIES_NONE. Read again by the aftermath dialogue.
@   VAR_TEMP_6  - Lillie has already shown her notebook on this visit, so a
@                 second NO only repeats the question.
@ WARNING: VAR_TEMP_0 and VAR_TEMP_1 belong to the Rage Candy Bar merchant
@ (getplayerxy, above in this file). This mission starts at VAR_TEMP_2 on
@ purpose - do NOT "harmonise" it with the Blackthorn mission.
@
@ WARNING: the eight everyday residents of this map carry
@ FLAG_EVENT_ULTRABEAST_MAHOGANY in their map.json "flag" field. A
@ removeobject on any of them SETS that flag and empties the town. The two
@ residents of the scene are separate objects on FLAG_TEMP_3.
@ WARNING: Hector stands on (9,20) and the evacuation walks both residents
@ over (10,20), the tile of the vanilla Fat man (local 4,
@ FLAG_HIDE_MAHOGANY_TOWN_FATMAN). That flag is set for good in
@ RocketHideout_B2F, long before the postgame, so the tile is free.
@
@ Object budget at the fullest moment (partner out, before Necrozma leaves):
@ player + hidden follower + Lillie + Ninetales + Looker + Anabel + Pryce +
@ Mamoswine + Xurkitree + Celesteela + Necrozma + rift + partner = 13/16.
@ Hector and his grandson are removed before any of that.
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
@ ============================================================================

Mahoganytown_EventScript_DoorLocked::
	lockall
	msgbox Mahoganytown_Text_DoorLocked, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ ---------------------------------------------------------------------------
@ Act II - the town as the player finds it. Every one of these is optional and
@ none of them changes state. The reactions to a Cosmog-family Pokemon used to
@ live here; they were moved to the single moment they belong to, after the
@ second battle (Mahoganytown_EventScript_UBPartnerReacts).
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBAnabel::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBAnabelIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_ANABEL, DIR_WEST
	release
	end

@ She recognises the player, turns to him and goes straight back to the
@ street: the reunion is a reunion, not an introduction (they have battled on
@ Route 30, in Goldenrod and in the Dragon's Den). Reachable from (21,21) and
@ (20,22), so faceplayer does the work and the turnobject puts her eyes back
@ on the street either way.
Mahoganytown_EventScript_UBLillie::
	lock
	faceplayer
	goto_if_unset FLAG_EVENT_ULTRABEAST_MAHOGANY, Mahoganytown_EventScript_UBLillieSettling
	goto_if_set FLAG_MAHOGANY_UB_ENGAGED, Mahoganytown_EventScript_UBLillieRetry
	msgbox Mahoganytown_Text_UBLillieIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_WEST
	release
	end

@ Ninetales never leaves her side and never stops watching the street, so no
@ faceplayer: the player gets the ears, not the face.
Mahoganytown_EventScript_UBNinetales::
	lock
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_NORMAL
	msgbox Mahoganytown_Text_UBNinetalesIdle, MSGBOX_DEFAULT
	waitmoncry
	goto Mahoganytown_EventScript_UBReleaseEnd

@ Pryce is walking the last two residents in, so no faceplayer: he talks over
@ his shoulder, still facing Hector at (9,20).
Mahoganytown_EventScript_UBPryce::
	lock
	msgbox Mahoganytown_Text_UBPryceIdle, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

Mahoganytown_EventScript_UBMamoswine::
	lock
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_NORMAL
	msgbox Mahoganytown_Text_UBMamoswineIdle, MSGBOX_DEFAULT
	waitmoncry
	goto Mahoganytown_EventScript_UBReleaseEnd

Mahoganytown_EventScript_UBHector::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBHectorIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_OLD_MAN, DIR_EAST     @ back to arguing with Pryce (11,20)
	release
	end

Mahoganytown_EventScript_UBBoy::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBBoyIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_BOY, DIR_NORTH        @ back to his grandfather (9,20)
	release
	end

Mahoganytown_EventScript_UBReleaseEnd::
	closemessage
	release
	end

@ The mission is over and this is the one load Lillie stays for. Repeatable,
@ changes nothing.
Mahoganytown_EventScript_UBLillieSettling::
	msgbox Mahoganytown_Text_UBLillieSettling, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

@ ---------------------------------------------------------------------------
@ Act III - what Lillie saw, and the commitment. Nothing changes state before
@ the YES: from there on everything is scripted through to a battle outcome.
@ Her reading comes BEFORE the YES on purpose. She offers an observation and
@ its limit ("I couldn't follow it back any farther"), Anabel turns it into a
@ test, and what she does NOT know yet - that pulling them apart is not enough
@ - is what the scene teaches her. She is never made to apologise for helping.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBLooker::
	lock
	faceplayer
	goto_if_set FLAG_MAHOGANY_UB_ENGAGED, Mahoganytown_EventScript_UBLookerRetry
	goto_if_eq VAR_TEMP_6, 1, Mahoganytown_EventScript_UBLookerAsk
	msgbox Mahoganytown_Text_UBLookerGreet, MSGBOX_DEFAULT
	closemessage
	@ Lillie and Ninetales come only as close as the conversation needs: she
	@ is at (20,21), one step south of Looker, and turns to the player at
	@ (21,20). Ninetales keeps her eyes on the street.
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_EAST
	msgbox Mahoganytown_Text_UBLillieGreet, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_WEST
	msgbox Mahoganytown_Text_UBLillieObservation, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBAnabelObservation, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBLillieLimit, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBAnabelPlan, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_6, 1                         @ the notebook is not read twice this visit
	goto Mahoganytown_EventScript_UBLookerAsk

Mahoganytown_EventScript_UBLookerAsk::
	msgbox Mahoganytown_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Mahoganytown_EventScript_UBNotReady
	goto Mahoganytown_EventScript_UBScene

Mahoganytown_EventScript_UBNotReady::
	msgbox Mahoganytown_Text_UBNotReady, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

@ After a blackout Looker is at the shelter (12,20) and is not the commit
@ point any more: he says the street is held and the Center is ready, and
@ Lillie, who is standing in the support line, asks the question.
Mahoganytown_EventScript_UBLookerRetry::
	msgbox Mahoganytown_Text_UBRetryGreeting, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

@ Lillie is at (19,22). Her free neighbours are exactly (18,22) and (19,21),
@ so the scene knows where the player is with one comparison.
Mahoganytown_EventScript_UBLillieRetry::
	msgbox Mahoganytown_Text_UBRetryLillie, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Mahoganytown_EventScript_UBRetryNotReady
	goto Mahoganytown_EventScript_UBSceneRetry

Mahoganytown_EventScript_UBRetryNotReady::
	msgbox Mahoganytown_Text_UBRetryNotReady, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

@ ---------------------------------------------------------------------------
@ Act IV - finish the evacuation. First framing: the Gym.
@ The player is not walked to the line until the residents are inside.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	setflag FLAG_MAHOGANY_UB_ENGAGED             @ every blackout from here is a retry
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Mahoganytown_Movement_CameraToShelter
	waitmovement OBJ_EVENT_ID_CAMERA
	msgbox Mahoganytown_Text_UBTimeIsClose, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBPryceEvacuates, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBHectorLamp, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBPryceLamp, MSGBOX_DEFAULT
	closemessage
	@ The grandson first, his grandfather behind him. The door has exactly one
	@ approach, (10,20), so the two walks are SEQUENTIAL: the boy crosses it
	@ and is gone before Hector steps onto it. Mamoswine (11,21) never stands
	@ on that path.
	opendoor 10, 19
	waitdooranim
	applymovement LOCALID_MAHOGANY_UB_BOY, Mahoganytown_Movement_BoyEnterGym
	waitmovement LOCALID_MAHOGANY_UB_BOY
	removeobject LOCALID_MAHOGANY_UB_BOY              @ flag FLAG_TEMP_3: harmless
	applymovement LOCALID_MAHOGANY_UB_OLD_MAN, Mahoganytown_Movement_HectorEnterGym
	waitmovement LOCALID_MAHOGANY_UB_OLD_MAN
	removeobject LOCALID_MAHOGANY_UB_OLD_MAN
	closedoor 10, 19
	waitdooranim
	@ Looker walks the length of row 20 to the shelter and stays there: he is
	@ not part of the combat formation. (12,20) to (19,20) is empty, and
	@ Xurkitree does not exist yet.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_LookerToShelter
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	msgbox Mahoganytown_Text_UBLookerEvacuated, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBPryceMeets, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBFormation

@ ---------------------------------------------------------------------------
@ Act V - the energy crosses the street. Second framing: the whole street.
@ ---------------------------------------------------------------------------
@ The order of these four blocks is LOAD-BEARING and every one of them is
@ sequential, because they share tiles:
@   Ninetales (19,21)->(19,22)->(19,23)          frees (19,22) for Lillie
@   Lillie    (20,21)->(20,22)->(19,22)            frees (20,21) for the player
@   player    (21,20)->(21,21)->(20,21)->(19,21)->(18,21)->(18,22)
@   Anabel    (19,20)->(20,20)->(20,21)->(20,22)   (20,20) is Looker's old tile
Mahoganytown_EventScript_UBFormation::
	applymovement OBJ_EVENT_ID_CAMERA, Mahoganytown_Movement_CameraToStreet
	waitmovement OBJ_EVENT_ID_CAMERA
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesToLine
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieToLine
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToLine
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	@ Beat 2. The town theme goes before anything is seen.
	fadeoutbgm 4
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_6
	addobject LOCALID_MAHOGANY_UB_RIFT
	clearflag FLAG_TEMP_4
	addobject LOCALID_MAHOGANY_UB_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_IN
	waitse
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Mahoganytown_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
	closemessage
	@ Lillie holds it for one beat and looks at her partner, not at the crowd.
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_SOUTH
	delay 20
	msgbox Mahoganytown_Text_UBLillieRecognizes, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_WEST
	msgbox Mahoganytown_Text_UBPryceCover, MSGBOX_DEFAULT
	closemessage
	@ Cover, NOT a doomed attack: Pryce puts Mamoswine between Necrozma and
	@ the Gym door and keeps it there. Row 22 for the Pokemon, column 11 for
	@ the man: no shared tile, so they go together.
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_MamoswineToCover
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Mahoganytown_Movement_PryceToCover
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	@ Beat 3. The opening widens and the two come through, one north, one
	@ south, with three clear rows between them.
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_MAHOGANY_UB_XURKITREE
	addobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox Mahoganytown_Text_UBAppear, MSGBOX_DEFAULT
	closemessage
	@ Shown before it is explained: Xurkitree takes the last light out of the
	@ street lamps, and it runs down column 15 into Celesteela.
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	call Mahoganytown_EventScript_UBFlow
	msgbox Mahoganytown_Text_UBSynergyObserved, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBSynergyRead, MSGBOX_DEFAULT
	closemessage
	@ Beat 4. Celesteela comes up the south corridor at the player's line.
	@ Lillie gives the order BEFORE the move lands.
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_CelesteelaAdvance
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBSavedOrder, MSGBOX_DEFAULT
	closemessage
	@ Ninetales (19,23)->(19,24)->(18,24): onto Celesteela's row, between it
	@ and the player, then the hit.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesCutsIn
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_AttackInPlaceLeft
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	call Mahoganytown_EventScript_UBShake
	call Mahoganytown_EventScript_UBFlash
	waitmoncry
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_CelesteelaPushedBack
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	@ The player gives ground north, off the south corridor, and turns
	@ straight back to the threat. (18,21) stays his tile until the choice.
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerStepsBack
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBSavedCheck, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	@ She goes straight back beside Lillie and leaves the middle lane clear.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesBackToLine
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	goto Mahoganytown_EventScript_UBChoose

@ ---------------------------------------------------------------------------
@ Beat 5 and 6 - the choice, and the separation shown on the ground.
@ Standard Rift Mission structure: the player picks which Ultra Beast to
@ fight, the mission companion takes the other. No cancel (ignoreBPress TRUE)
@ - the scene has already started, so VAR_RESULT can only be 0 or 1.
@ The pick is per attempt and holds for BOTH rounds of that attempt.
@   pick Xurkitree  -> player north (18,20), Lillie/Ninetales south
@   pick Celesteela -> player south (18,24), Lillie/Ninetales north
@ Two tiles between each front and its trainer in both branches, and the pair
@ always moves first, through the support column, before the player crosses.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBChoose::
	msgbox Mahoganytown_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, Mahoganytown_Text_ChoiceXurkitree, Mahoganytown_Text_ChoiceCelesteela
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 = Xurkitree, 1 = Celesteela
	closemessage
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBPickCelesteela
	clearflag FLAG_MAHOGANY_UB_PICKED_CELESTEELA @ mirror that survives a blackout
	msgbox Mahoganytown_Text_UBPickedXurkitree, MSGBOX_DEFAULT
	closemessage
	@ The pair goes south, the player goes north.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesToSouthFront
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieToSouthFront
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToNorthFront
	waitmovement OBJ_EVENT_ID_PLAYER
	goto Mahoganytown_EventScript_UBBattle1

Mahoganytown_EventScript_UBPickCelesteela::
	setflag FLAG_MAHOGANY_UB_PICKED_CELESTEELA
	msgbox Mahoganytown_Text_UBPickedCelesteela, MSGBOX_DEFAULT
	closemessage
	@ Ninetales walks the whole support column to the north front and Lillie
	@ closes up behind her; the player has column 18 to himself.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesToNorthFront
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieToNorthFront
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToSouthFront
	waitmovement OBJ_EVENT_ID_PLAYER
	goto Mahoganytown_EventScript_UBBattle1

@ ---------------------------------------------------------------------------
@ Two boss battles in a row against the SAME beast (the player's pick).
@ Boss setup only survives a SIMPLE battle, which is the other reason the
@ mission splits the beasts. B_FLAG_NO_WHITEOUT is deliberately NOT set in
@ either: this is a threat battle, so losing means a blackout and a retry.
@
@ Round 1: 2 bars / Lv80 / x130. Short on purpose: it has to feel like a win,
@ so the recharge lands.
@ Round 2: 4 bars / Lv80 / x130, the Mission 2 target of the design scale.
@ Anabel heals the team between the rounds, under cover of the wall.
@ These numbers are the ones in MAHOGANY_ULTRABEAST_IMPLEMENTATION.md and the
@ story revision did not change them.
@
@ Macro order is the same as bosslegendaryencounterwithmoves
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
@ seteventmonmoves -> special. No path leaves the script in between, so no
@ clearbossbattle is needed.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBBattle1::
	setflag B_FLAG_NO_CATCHING                   @ cleared by the engine after the battle
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBSetupCelesteela1
	setbossbattle 2, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_XURKITREE, 80, ITEM_MAGNET
	seteventmonmoves MOVE_TAIL_GLOW, MOVE_THUNDERBOLT, MOVE_ENERGY_BALL, MOVE_DAZZLING_GLEAM
	goto Mahoganytown_EventScript_UBStartBattle1

Mahoganytown_EventScript_UBSetupCelesteela1::
	setbossbattle 2, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_CELESTEELA, 80, ITEM_LEFTOVERS
	seteventmonmoves MOVE_HEAVY_SLAM, MOVE_FLAMETHROWER, MOVE_EARTHQUAKE, MOVE_AIR_SLASH

@ LOST, DREW and FORFEITED never come back here - the engine blacks the player
@ out to the Mahogany Pokemon Center (Mahoganytown_OnLoad does the setrespawn)
@ and FLAG_MAHOGANY_UB_ENGAGED turns the next visit into a retry. CAUGHT and
@ RAN are unreachable (ball blocked; Run becomes FORFEITED in a boss) but are
@ handled anyway: anything that is not WON regroups, never wins. Same for
@ round 2 below.
Mahoganytown_EventScript_UBStartBattle1::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, Mahoganytown_EventScript_UBRecharge
	goto Mahoganytown_EventScript_UBUnresolved

@ ---------------------------------------------------------------------------
@ Act VI - pulling them apart was not enough. The beaten beast is brought back
@ by ONE charge sent down the link, and the source pays for it: the far one
@ dims while it gives. Nobody calls this a cycle and nobody calls it endless.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBRecharge::
	goto_if_set FLAG_MAHOGANY_UB_SAW_RECHARGE, Mahoganytown_EventScript_UBRechargeAgain
	setflag FLAG_MAHOGANY_UB_SAW_RECHARGE        @ splits the two kinds of retry
	msgbox Mahoganytown_Text_UBFirstDown, MSGBOX_DEFAULT
	closemessage
	call Mahoganytown_EventScript_UBFlowPulse
	msgbox Mahoganytown_Text_UBCurrentReturns, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBRechargeCelesteela
	@ Celesteela's engines dim; the charge runs north into Xurkitree.
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBSendsUp
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBRises
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	msgbox Mahoganytown_Text_UBRevivedXurkitree, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBPlanCorrection

Mahoganytown_EventScript_UBRechargeCelesteela::
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBSendsDown
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBRises
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	msgbox Mahoganytown_Text_UBRevivedCelesteela, MSGBOX_DEFAULT

@ The attempt after the group has already watched this happen. Same beat on
@ screen, no discovery: one line, and straight to the wall.
Mahoganytown_EventScript_UBRechargeAgain::
	msgbox Mahoganytown_Text_UBFirstDown, MSGBOX_DEFAULT
	closemessage
	call Mahoganytown_EventScript_UBFlowPulse
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBRechargeAgainCelesteela
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBSendsUp
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBRises
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	goto Mahoganytown_EventScript_UBRetryRecharge

Mahoganytown_EventScript_UBRechargeAgainCelesteela::
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBSendsDown
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBRises
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry

Mahoganytown_EventScript_UBRetryRecharge::
	msgbox Mahoganytown_Text_UBRetryRecharge, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBWall

@ She follows the whole length of the light, points at the middle of it and
@ asks for a better wall. No monologue of guilt: the plan was incomplete, and
@ she says so in one line and moves on.
Mahoganytown_EventScript_UBPlanCorrection::
	closemessage
	msgbox Mahoganytown_Text_UBLilliePlanCorrection, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBPrycePlan, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBAnabelWallPlan, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBWall

@ ---------------------------------------------------------------------------
@ Act VII - the wall, then the heal, then the second round. The ice has to buy
@ real time, so nothing is left loose while Anabel works: Ninetales holds the
@ front, Mamoswine builds, and only then does the player fall back.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBWall::
	msgbox Mahoganytown_Text_UBNinetalesCover, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_AttackInPlaceLeft
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	msgbox Mahoganytown_Text_UBWallOrder, MSGBOX_DEFAULT
	closemessage
	@ Mamoswine (10,22)->(12,22) along the empty middle row, faces east and
	@ throws the wall across (14,22) (15,22) (16,22). It stops one tile short
	@ of the ice so the left end of the wall is not hidden behind it, and
	@ Pryce never turns his back on Necrozma.
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_MamoswineToGap
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_AttackInPlaceRight
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	waitmoncry
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	call MahoganyTown_EventScript_PaintIceWall
	special DrawWholeMapView
	fadescreenswapbuffers FADE_FROM_WHITE
	@ The test, shown before anyone concludes anything: the light runs into
	@ the ice, breaks up and stops, and the beast that was waiting for it
	@ gutters.
	call Mahoganytown_EventScript_UBFlowBlocked
	msgbox Mahoganytown_Text_UBWallHolds, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBLillieWall, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBHeal

@ The heal happens under cover and nobody crosses the wall to reach it: Anabel
@ comes up the support corridor and the player falls back one row to meet her,
@ on his own side of the ice.
Mahoganytown_EventScript_UBHeal::
	msgbox Mahoganytown_Text_UBAnabelHeals, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBHealSouth
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToNorthHeal
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToNorthHeal
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmovement OBJ_EVENT_ID_PLAYER
	call Mahoganytown_EventScript_UBHealParty
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelBackFromNorth
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerBackToNorthFront
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmovement OBJ_EVENT_ID_PLAYER
	goto Mahoganytown_EventScript_UBSecondRound

Mahoganytown_EventScript_UBHealSouth::
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToSouthHeal
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerToSouthHeal
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmovement OBJ_EVENT_ID_PLAYER
	call Mahoganytown_EventScript_UBHealParty
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelBackFromSouth
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerBackToSouthFront
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmovement OBJ_EVENT_ID_PLAYER

Mahoganytown_EventScript_UBSecondRound::
	msgbox Mahoganytown_Text_UBSecondRound, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle2

@ fadescreenswapbuffers and not fadescreen: the scene comes straight back to
@ this map, and fadescreen would copy the tinted palettes over the untinted
@ ones (FadeScreen, src/field_weather.c) and darken the town another notch.
@ The heal fanfare is short and the threat theme is already back on the way
@ out: playbgm wrote it into savedMusic, so nothing has to restart it.
Mahoganytown_EventScript_UBHealParty::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	fadescreenswapbuffers FADE_TO_BLACK
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox Mahoganytown_Text_UBAnabelHealed, MSGBOX_DEFAULT
	closemessage
	return

Mahoganytown_EventScript_UBBattle2::
	setflag B_FLAG_NO_CATCHING                   @ cleared again after round 1: set again
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBSetupCelesteela2
	setbossbattle 4, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_XURKITREE, 80, ITEM_MAGNET
	seteventmonmoves MOVE_TAIL_GLOW, MOVE_THUNDERBOLT, MOVE_ENERGY_BALL, MOVE_DAZZLING_GLEAM
	goto Mahoganytown_EventScript_UBStartBattle2

Mahoganytown_EventScript_UBSetupCelesteela2::
	setbossbattle 4, SPECIES_NONE, 130, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_CELESTEELA, 80, ITEM_LEFTOVERS
	seteventmonmoves MOVE_HEAVY_SLAM, MOVE_FLAMETHROWER, MOVE_EARTHQUAKE, MOVE_AIR_SLASH

Mahoganytown_EventScript_UBStartBattle2::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, Mahoganytown_EventScript_UBResolved
	goto Mahoganytown_EventScript_UBUnresolved

@ Anything that is not a win and is not a blackout (the engine handles those
@ itself). Nothing was recorded as done, the incident flag is still set and
@ FLAG_MAHOGANY_UB_ENGAGED is set, so the reload puts the street back as a
@ retry and Lillie can start the attempt again.
@ (21,20) is the Fly landing / Center exit tile.
Mahoganytown_EventScript_UBUnresolved::
	msgbox Mahoganytown_Text_UBUnresolved, MSGBOX_DEFAULT
	closemessage
	special RemoveCameraObject
	fadescreen FADE_TO_BLACK
	warpsilent MAP_MAHOGANYTOWN, 21, 20
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ Act VIII - they learned, and Necrozma changes its approach.
@ Both beasts stay on screen: the win stops them, it does not delete them.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBResolved::
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBLillieFoughtXurkitree
	msgbox Mahoganytown_Text_UBLillieFoughtCelesteela, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBRegroup

Mahoganytown_EventScript_UBLillieFoughtXurkitree::
	msgbox Mahoganytown_Text_UBLillieFoughtXurkitree, MSGBOX_DEFAULT

@ Both fronts are done, so the two branches close here and everything after
@ this point is one path: player (18,22), Lillie (19,22), Ninetales (19,23).
Mahoganytown_EventScript_UBRegroup::
	closemessage
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBRegroupFromSouth
	@ Player north. Lillie frees (19,23) for Ninetales before she crosses.
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieSouthToLine
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesSouthToLine
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerNorthToLine
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	waitmovement OBJ_EVENT_ID_PLAYER
	goto Mahoganytown_EventScript_UBSecureAttempt

@ Player south. Ninetales walks down column 18 first, because the player has
@ to come up the same column behind her.
Mahoganytown_EventScript_UBRegroupFromSouth::
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesNorthToLine
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Mahoganytown_Movement_LillieNorthToLine
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerSouthToLine
	waitmovement OBJ_EVENT_ID_PLAYER

@ Beat 2. Anabel moves up to try to secure them, and Necrozma answers by
@ changing the geometry: blocked on the ground, it reaches OVER the ice.
@ Pryce is not surprised by it - he has been watching it the whole time.
Mahoganytown_EventScript_UBSecureAttempt::
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelSteps
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	msgbox Mahoganytown_Text_UBSecure, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_NecrozmaLean
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	msgbox Mahoganytown_Text_UBPryceIntercept, MSGBOX_DEFAULT
	closemessage
	@ Mamoswine (12,22)->(11,22): straight across Necrozma's line on the
	@ ground. The wall is untouched; nothing walks through it.
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_MamoswineBlocks
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_ENCOUNTER
	waitmoncry
	@ It floats out of that line instead of forcing it, and the new link goes
	@ over the top: shown before anything is dragged anywhere.
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_NecrozmaSlipsAside
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_PulseInPlaceRight
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	msgbox Mahoganytown_Text_UBLillieNewLink, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBNinetalesIntercept, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_AttackInPlaceLeft
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	@ Beat 3. Both are pulled two tiles toward Necrozma along their own rows,
	@ resist, and go. Neither row touches the ice at y=22.
	call Mahoganytown_EventScript_UBShake
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBPulledIn
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBPulledIn
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_XURKITREE   @ flag FLAG_TEMP_2: harmless
	removeobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	waitmoncry
	@ The glow rises, and then wavers: the same instrument that read the two
	@ signatures before the absorption reads them again after it. That is the
	@ discovery, and it does not need the player to be carrying anything.
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	call Mahoganytown_EventScript_UBRiftPulse
	msgbox Mahoganytown_Text_UBAbsorbedRead, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBLillieSignals, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBAbsorbedConfirm, MSGBOX_DEFAULT
	closemessage
	call Mahoganytown_EventScript_UBPartnerReacts
	goto Mahoganytown_EventScript_UBNecrozmaLeaves

@ ---------------------------------------------------------------------------
@ Act IX - the player's own partner. Optional, changes nothing, and it is
@ SHOWN before anything is said about it: one actor per stage, four templates
@ on (18,23) sharing FLAG_TEMP_7, at most one of them ever added. The follower
@ is hidden for the whole scene, so nothing is duplicated.
@ Checked AFTER both battles on purpose: a battle can evolve it.
@ (17,23) is the player's protected side: diagonally in front of him, just
@ east of the ice, two columns clear of Ninetales (19,23) and nowhere near
@ the corridor Anabel used. It is two columns and not one because these
@ sprites are 32x32: anchors one tile apart still overlap.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBPartnerReacts::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, Mahoganytown_EventScript_UBReturn
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	clearflag FLAG_TEMP_7
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	call Mahoganytown_EventScript_UBAddPartner
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, Mahoganytown_EventScript_UBPartnerLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, Mahoganytown_EventScript_UBPartnerLegend
	@ Cosmog / Cosmoem: Necrozma turns to it, Ninetales takes the side.
	turnobject LOCALID_MAHOGANY_UB_NECROZMA, DIR_EAST
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_SOUTH
	msgbox Mahoganytown_Text_UBNecrozmaSensesCosmog, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_WEST
	call Mahoganytown_EventScript_UBRiftPulse
	return

@ Solgaleo / Lunala: the opening steadies while it pulses, Anabel reads the
@ two signatures more clearly, and they are STILL moving with Necrozma. It
@ buys observation, not a rescue. The signatures were already recognised
@ before it came out, so no branch of this scene owns the discovery.
Mahoganytown_EventScript_UBPartnerLegend::
	call Mahoganytown_EventScript_UBFlash
	msgbox Mahoganytown_Text_UBNecrozmaSensesLegend, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBPartnerRead, MSGBOX_DEFAULT
	closemessage
	call Mahoganytown_EventScript_UBRiftPulse
	msgbox Mahoganytown_Text_UBLilliePartnerLimit, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	return

@ If both are somehow in the party, CheckMysteryEggPokemon returns the first
@ one in party order, so the species, the cry and the actor all agree and none
@ of them changes in the middle of the scene.
Mahoganytown_EventScript_UBAddPartner::
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, Mahoganytown_EventScript_UBAddCosmoem
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, Mahoganytown_EventScript_UBAddSolgaleo
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, Mahoganytown_EventScript_UBAddLunala
	addobject LOCALID_MAHOGANY_UB_COSMOG
	return
Mahoganytown_EventScript_UBAddCosmoem::
	addobject LOCALID_MAHOGANY_UB_COSMOEM
	return
Mahoganytown_EventScript_UBAddSolgaleo::
	addobject LOCALID_MAHOGANY_UB_SOLGALEO
	return
Mahoganytown_EventScript_UBAddLunala::
	addobject LOCALID_MAHOGANY_UB_LUNALA
	return

@ Called back on screen, before anybody walks over the tile it was standing
@ on. Nothing is said about it afterwards that implies it is still out.
Mahoganytown_EventScript_UBPartnerRecalled::
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, Mahoganytown_EventScript_UBReturn
	playse SE_BALL_OPEN
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_COSMOG
	removeobject LOCALID_MAHOGANY_UB_COSMOEM
	removeobject LOCALID_MAHOGANY_UB_SOLGALEO
	removeobject LOCALID_MAHOGANY_UB_LUNALA
	fadescreenswapbuffers FADE_FROM_WHITE
	return

Mahoganytown_EventScript_UBReturn::
	return

@ ---------------------------------------------------------------------------
@ Act X - the street breathes again. The opening closes first, THEN the town
@ comes back: no victory fanfare over an open rift.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBNecrozmaLeaves::
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_NECROZMA    @ own flags (TEMP_4, TEMP_6):
	removeobject LOCALID_MAHOGANY_UB_RIFT        @ removeobject touches nobody else
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_OUT
	waitse
	msgbox Mahoganytown_Text_UBNecrozmaGone, MSGBOX_DEFAULT
	closemessage
	@ A beat of nothing: Mamoswine checks the front it was holding, Ninetales
	@ lets her shoulders down without leaving Lillie.
	turnobject LOCALID_MAHOGANY_UB_MAMOSWINE, DIR_WEST
	delay 30
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_NORTH
	delay 20
	msgbox Mahoganytown_Text_UBPowerReturns, MSGBOX_DEFAULT
	closemessage
	@ Only now does the threat theme end and the town theme come back.
	fadedefaultbgm
	call Mahoganytown_EventScript_UBPartnerRecalled
	@ Pryce opens the barrier before anybody has to walk through that space.
	msgbox Mahoganytown_Text_UBPryceClearsIce, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_AttackInPlaceRight
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	waitmoncry
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	call Mahoganytown_EventScript_UBClearIceWall
	special DrawWholeMapView
	fadescreenswapbuffers FADE_FROM_WHITE
	@ Pryce comes as far as the middle of the street and no further.
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Mahoganytown_Movement_PryceToTalk
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBPryceThanks, MSGBOX_DEFAULT
	closemessage
	@ Lillie checks her partner first and answers second.
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_SOUTH
	delay 20
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_WEST
	msgbox Mahoganytown_Text_UBLillieThanks, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBPryceAnswer, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_NORMAL
	waitmoncry
	msgbox Mahoganytown_Text_UBPryceGoodbye, MSGBOX_DEFAULT
	closemessage
	@ They leave together, west along two different rows, and are removed at
	@ x=6, one column outside the framing. The ice is gone and nobody is in
	@ the way. Their flag is FLAG_TEMP_5, so removeobject is harmless.
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Mahoganytown_Movement_PryceLeaves
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_MamoswineLeaves
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	removeobject LOCALID_MAHOGANY_UB_PRYCE
	removeobject LOCALID_MAHOGANY_UB_MAMOSWINE
	goto Mahoganytown_EventScript_UBAftermath

Mahoganytown_EventScript_UBClearIceWall::
	setmetatile 14, 22, 0xDC, FALSE
	setmetatile 15, 22, 0xDC, FALSE
	setmetatile 16, 22, 0xDC, FALSE
	return

@ ---------------------------------------------------------------------------
@ Act XI - what can still be saved. An open formation, and the eyes move with
@ the speaker: Looker west of the player, Lillie and Anabel east of him.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBAftermath::
	@ Looker comes back from the shelter along row 20 and down to (17,22),
	@ the tile the left end of the wall was on.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_LookerToGroup
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	msgbox Mahoganytown_Text_UBAftermathLooker, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBAftermathLillie, MSGBOX_DEFAULT
	closemessage
	@ Anabel comes down beside Lillie so the answer does not come over
	@ somebody's shoulder.
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToGroup
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	msgbox Mahoganytown_Text_UBAftermathAnabel, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBAftermathBlackthorn, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBAftermathLillieResolve, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBAftermathNextPlan, MSGBOX_DEFAULT
	closemessage
	@ The notebook changes hands: two records of different parts of the same
	@ hour, not one replacing the other.
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_NORTH
	turnobject LOCALID_MAHOGANY_UB_ANABEL, DIR_SOUTH
	msgbox Mahoganytown_Text_UBAftermathNotes, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBAftermathAcceptNotes, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_WEST
	turnobject LOCALID_MAHOGANY_UB_ANABEL, DIR_WEST
	@ Only if the partner actually came out. VAR_TEMP_4 survives: no battle
	@ and no reload happened since it was written.
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, Mahoganytown_EventScript_UBHook
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, Mahoganytown_EventScript_UBAftermathLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, Mahoganytown_EventScript_UBAftermathLegend
	msgbox Mahoganytown_Text_UBAftermathCosmog, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBHook

Mahoganytown_EventScript_UBAftermathLegend::
	msgbox Mahoganytown_Text_UBAftermathLegend, MSGBOX_DEFAULT
	closemessage

@ ---------------------------------------------------------------------------
@ Act XII - goodbye. The hook names no place: the next briefing in Olivine
@ does that, and only after Looker has telephoned again.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBHook::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBHookLooker, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBHookLillieStay, MSGBOX_DEFAULT
	closemessage
	msgbox Mahoganytown_Text_UBLillieGoodbye, MSGBOX_DEFAULT
	closemessage
	@ Ninetales leans in and Lillie drops a hand to her. One small movement,
	@ no extra box.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesLeansIn
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_SOUTH
	delay 40
	goto Mahoganytown_EventScript_UBFinish

@ Resolution. The flag and the var move together, and every scratch flag this
@ mission owns is cleared, so a later visit is an ordinary town.
@ The silent reload is what repopulates Mahogany: with
@ FLAG_EVENT_ULTRABEAST_MAHOGANY clear the eight everyday residents would
@ otherwise pop in one at a time as the camera moved, the doors unlock with
@ the flag, and the warp is also what gives the follower back after
@ hidefollower. FLAG_MAHOGANY_UB_LILLIE_SETTLING is set for exactly that one
@ reload: ApplyUBVisibility consumes it, keeps Lillie and Ninetales by the
@ Pokemon Center as she promised, and hides everybody else.
Mahoganytown_EventScript_UBFinish::
	special RemoveCameraObject
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_MAHOGANY      @ invariant: flag and var together
	setvar VAR_RIFT_MISSIONS_STATE, 6
	clearflag FLAG_MAHOGANY_UB_ENGAGED
	clearflag FLAG_MAHOGANY_UB_SAW_RECHARGE
	clearflag FLAG_MAHOGANY_UB_PICKED_CELESTEELA
	setflag FLAG_MAHOGANY_UB_LILLIE_SETTLING
	setflag FLAG_DAILY_LOOKER_CALL                @ he just said it in person
	warpsilent MAP_MAHOGANYTOWN, 18, 22
	waitstate
	releaseall
	end

@ ---------------------------------------------------------------------------
@ The retry, after a blackout. ApplyUBVisibility has already put the street
@ back the way the player left it, so nothing walks into formation here.
@ Two shapes, and FLAG_MAHOGANY_UB_SAW_RECHARGE is what tells them apart:
@   before the recharge was ever seen - the group still believes that pulling
@     them apart is enough, so the attempt runs with the first-run lines and
@     discovers the recharge the same way it did the first time.
@   after it - the ice is already on the ground (ON_LOAD painted it), the
@     beast the player was fighting has spent the whole time since the
@     blackout hammering a hole in it, and the plan is the short one.
@ Lillie is at (19,22): her only free neighbours are (18,22) and (19,21), so
@ one comparison puts the player on the line without a warp.
@ ---------------------------------------------------------------------------
Mahoganytown_EventScript_UBSceneRetry::
	closemessage
	lockall
	hidefollower
	@ The player goes to (18,22) FIRST, so the camera pan below is always the
	@ same four tiles no matter which side he talked to Lillie from.
	getplayerxy VAR_TEMP_3, VAR_TEMP_4
	call_if_eq VAR_TEMP_3, 19, Mahoganytown_EventScript_UBRetryStepIn
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	setvar VAR_TEMP_3, 0
	setvar VAR_TEMP_4, 0
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Mahoganytown_Movement_CameraRetryToStreet
	waitmovement OBJ_EVENT_ID_CAMERA
	goto_if_unset FLAG_MAHOGANY_UB_SAW_RECHARGE, Mahoganytown_EventScript_UBChoose
	goto Mahoganytown_EventScript_UBWallBreaks

@ The player was on (19,21), north of Lillie: two steps put him on (18,22)
@ without crossing her.
Mahoganytown_EventScript_UBRetryStepIn::
	applymovement OBJ_EVENT_ID_PLAYER, Mahoganytown_Movement_PlayerRetryToLine
	waitmovement OBJ_EVENT_ID_PLAYER
	return

@ The consequence of the blackout, completed on screen before the new attempt
@ starts: the beast that stopped being fought went at the ice with its body,
@ a section came down, and only THEN does the light cross again. The rest of
@ the wall stays exactly where it was.
Mahoganytown_EventScript_UBWallBreaks::
	goto_if_set FLAG_MAHOGANY_UB_PICKED_CELESTEELA, Mahoganytown_EventScript_UBWallBreaksCelesteela
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBStrikesWallDown
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	goto Mahoganytown_EventScript_UBWallGivesWay

Mahoganytown_EventScript_UBWallBreaksCelesteela::
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBStrikesWallUp
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry

Mahoganytown_EventScript_UBWallGivesWay::
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	setmetatile 15, 22, METATILE_MahoganyTown_IceWall_Broken, FALSE
	special DrawWholeMapView
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox Mahoganytown_Text_UBRetryWallBroken, MSGBOX_DEFAULT
	closemessage
	call Mahoganytown_EventScript_UBFlow
	@ Mamoswine covered the retreat, so it is back on the west flank: Act VII
	@ walks it out to the gap again, exactly as it did the first time.
	msgbox Mahoganytown_Text_UBRetryPlan, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBChoose

@ ---------------------------------------------------------------------------
@ Scene helpers.
@ ---------------------------------------------------------------------------
@ Flash of the scene. fadescreenswapbuffers and NOT fadescreen: fadescreen
@ copies gPlttBufferFaded over gPlttBufferUnfaded on the way down
@ (src/field_weather.c, FadeScreen) and the FADE_FROM_* that follows reapplies
@ the time-of-day tint on top of palettes that were already tinted. At night
@ (coeff 10) every pair of flashes multiplies the scene by ~0.46 again, and
@ after three or four the town is black. fadescreenswapbuffers does the same
@ thing with BLDY in hardware and never touches the palettes.
Mahoganytown_EventScript_UBFlash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

Mahoganytown_EventScript_UBShake::
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 12  @ num shakes
	setvar VAR_0x8007, 4   @ shake delay
	special ShakeCamera
	waitstate
	return

@ The rift itself wavering, shorter and horizontal only.
Mahoganytown_EventScript_UBRiftPulse::
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	return

@ The light crossing the street: Xurkitree (15,20) reaches for what is left in
@ the lamps, it runs down column 15, and Celesteela (15,24) burns it.
Mahoganytown_EventScript_UBFlow::
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBSendsDown
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBRises
	playmoncry SPECIES_CELESTEELA, CRY_MODE_NORMAL
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	return

@ The same light, seen for one beat, right after a beast goes down: the cue
@ that the fight is not over.
Mahoganytown_EventScript_UBFlowPulse::
	call Mahoganytown_EventScript_UBRiftPulse
	call Mahoganytown_EventScript_UBFlash
	return

@ The test: both of them reach for the link, it dies in the ice, and the one
@ that was waiting for the charge gutters. Shown before Anabel says a word.
Mahoganytown_EventScript_UBFlowBlocked::
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBSendsDown
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBSendsUp
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	call Mahoganytown_EventScript_UBRiftPulse
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBFlowBlockedCelesteela
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBGutters
	playmoncry SPECIES_XURKITREE, CRY_MODE_NORMAL
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	return

Mahoganytown_EventScript_UBFlowBlockedCelesteela::
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBGutters
	playmoncry SPECIES_CELESTEELA, CRY_MODE_NORMAL
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	return

@ ---------------------------------------------------------------------------
@ Movements. Every tile below was read off data/layouts/Mahoganytown/map.bin
@ (dump_mapa.py) with the street already widened to y=20..24.
@ ---------------------------------------------------------------------------
@ Camera (21,20)->(13,22): the shelter framing.
Mahoganytown_Movement_CameraToShelter:
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_left
	slide_down
	slide_down
	step_end

@ (13,22)->(14,22): the street framing. One tile, so the cut is a nudge.
Mahoganytown_Movement_CameraToStreet:
	slide_right
	step_end

@ Retry only: the camera spawns on the player, who has just been put on
@ (18,22), so it is always these four tiles to (14,22).
Mahoganytown_Movement_CameraRetryToStreet:
	slide_left
	slide_left
	slide_left
	slide_left
	step_end

@ Boy (9,21)->(10,21)->(10,20)->(10,19), into the door.
Mahoganytown_Movement_BoyEnterGym:
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

@ Hector (9,20)->(10,20)->(10,19), after the boy has cleared the tile.
Mahoganytown_Movement_HectorEnterGym:
	walk_right
	walk_up
	set_invisible
	step_end

@ Looker (20,20)->(12,20), the whole length of row 20 to the Gym side.
Mahoganytown_Movement_LookerToShelter:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

@ Ninetales (19,21)->(19,22)->(19,23).
Mahoganytown_Movement_NinetalesToLine:
	walk_down
	walk_down
	face_left
	step_end

@ Lillie (20,21)->(20,22)->(19,22).
Mahoganytown_Movement_LillieToLine:
	walk_down
	walk_left
	face_left
	step_end

@ Player (21,20)->(21,21)->(20,21)->(19,21)->(18,21)->(18,22).
Mahoganytown_Movement_PlayerToLine:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	face_left
	step_end

@ Anabel (19,20)->(20,20)->(20,21)->(20,22), through Looker's old tile.
Mahoganytown_Movement_AnabelToLine:
	walk_right
	walk_down
	walk_down
	face_left
	step_end

@ Mamoswine (12,22)->(10,22), between Necrozma and the Gym door. Pryce goes
@ down his own column at the same time, so the two never share a tile and can
@ move together.
Mahoganytown_Movement_MamoswineToCover:
	walk_left
	walk_left
	face_left
	step_end

@ Pryce (11,20)->(11,21)->(10,21), behind his Pokemon, eyes west.
Mahoganytown_Movement_PryceToCover:
	walk_down
	walk_left
	face_left
	step_end

@ Celesteela (15,24)->(17,24), up the south corridor at the player's line.
Mahoganytown_Movement_CelesteelaAdvance:
	walk_fast_right
	walk_fast_right
	step_end

@ Ninetales (19,23)->(19,24)->(18,24): onto its row, between it and the player.
Mahoganytown_Movement_NinetalesCutsIn:
	walk_down
	walk_left
	face_left
	step_end

@ (17,24)->(15,24), still facing the player.
Mahoganytown_Movement_CelesteelaPushedBack:
	lock_facing_direction
	walk_fast_left
	walk_fast_left
	unlock_facing_direction
	step_end

@ Player (18,22)->(18,21), giving ground without turning his back.
Mahoganytown_Movement_PlayerStepsBack:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

@ Ninetales (18,24)->(19,24)->(19,23), back beside Lillie, middle lane clear.
Mahoganytown_Movement_NinetalesBackToLine:
	walk_right
	walk_up
	face_left
	step_end

@ Pick Xurkitree: the pair takes the south front.
@ Ninetales (19,23)->(19,24)->(18,24), two tiles from Celesteela (15,24).
Mahoganytown_Movement_NinetalesToSouthFront:
	walk_down
	walk_left
	face_left
	step_end

@ Lillie (19,22)->(19,23), behind her partner.
Mahoganytown_Movement_LillieToSouthFront:
	walk_down
	face_left
	step_end

@ Player (18,21)->(18,20), two tiles from Xurkitree (15,20).
Mahoganytown_Movement_PlayerToNorthFront:
	walk_up
	face_left
	step_end

@ Pick Celesteela: the pair takes the north front. Ninetales goes round by
@ column 17, NOT up column 19: Lillie is on (19,22) and the player is still
@ on (18,21), and this route touches neither.
@ (19,23)->(18,23)->(17,23)->(17,22)->(17,21)->(17,20)->(18,20).
Mahoganytown_Movement_NinetalesToNorthFront:
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	face_left
	step_end

@ Lillie (19,22)->(19,21)->(19,20), behind her partner.
Mahoganytown_Movement_LillieToNorthFront:
	walk_up
	walk_up
	face_left
	step_end

@ Player (18,21)->(18,22)->(18,23)->(18,24), two tiles from Celesteela.
Mahoganytown_Movement_PlayerToSouthFront:
	walk_down
	walk_down
	walk_down
	face_left
	step_end

@ The sender pulses toward the other one and dims; the receiver comes back up.
Mahoganytown_Movement_UBSendsDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	face_right
	step_end

Mahoganytown_Movement_UBSendsUp:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	face_right
	step_end

Mahoganytown_Movement_UBRises:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	face_right
	step_end

@ Reaching for a charge that never comes.
Mahoganytown_Movement_UBGutters:
	walk_in_place_slow_right
	walk_in_place_slow_right
	face_right
	step_end

@ Nothing to fight any more, so it goes at the ice with its body.
Mahoganytown_Movement_UBStrikesWallDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	face_right
	step_end

Mahoganytown_Movement_UBStrikesWallUp:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	face_right
	step_end

Mahoganytown_Movement_AttackInPlaceLeft:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

Mahoganytown_Movement_AttackInPlaceRight:
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

Mahoganytown_Movement_PulseInPlaceRight:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

@ Mamoswine (10,22)->(12,22), one tile short of the ice it is about to throw,
@ so the left end of the wall is not hidden behind it.
Mahoganytown_Movement_MamoswineToGap:
	walk_right
	walk_right
	face_right
	step_end

@ Mamoswine (12,22)->(11,22), across Necrozma's line on the ground.
Mahoganytown_Movement_MamoswineBlocks:
	walk_left
	face_left
	step_end

@ Necrozma (8,22)->(9,22), and then out of the line it was blocked on,
@ (9,22)->(8,22)->(8,21), without ever turning away.
Mahoganytown_Movement_NecrozmaLean:
	walk_slow_right
	step_end

Mahoganytown_Movement_NecrozmaSlipsAside:
	lock_facing_direction
	walk_slow_left
	walk_slow_up
	unlock_facing_direction
	step_end

@ Dragged two tiles west along their own rows, y=20 and y=24: neither of them
@ ever touches the ice at y=22.
Mahoganytown_Movement_UBPulledIn:
	lock_facing_direction
	walk_slow_left
	walk_slow_left
	unlock_facing_direction
	step_end

@ North front -> the heal, and back. (18,20)->(18,21)->(19,21).
Mahoganytown_Movement_PlayerToNorthHeal:
	walk_down
	walk_right
	step_end

Mahoganytown_Movement_PlayerBackToNorthFront:
	walk_left
	walk_up
	face_left
	step_end

Mahoganytown_Movement_AnabelToNorthHeal:
	walk_up
	face_left
	step_end

Mahoganytown_Movement_AnabelBackFromNorth:
	walk_down
	face_left
	step_end

@ South front -> the heal, and back. (18,24)->(18,23)->(19,23).
Mahoganytown_Movement_PlayerToSouthHeal:
	walk_up
	walk_right
	step_end

Mahoganytown_Movement_PlayerBackToSouthFront:
	walk_left
	walk_down
	face_left
	step_end

Mahoganytown_Movement_AnabelToSouthHeal:
	walk_down
	face_left
	step_end

Mahoganytown_Movement_AnabelBackFromSouth:
	walk_up
	face_left
	step_end

@ Regroup onto the middle line: player (18,22), Lillie (19,22), Ninetales
@ (19,23), whichever front each of them was holding.
Mahoganytown_Movement_LillieSouthToLine:
	walk_up
	face_left
	step_end

Mahoganytown_Movement_NinetalesSouthToLine:
	walk_right
	walk_up
	face_left
	step_end

Mahoganytown_Movement_PlayerNorthToLine:
	walk_down
	walk_down
	face_left
	step_end

Mahoganytown_Movement_NinetalesNorthToLine:
	walk_down
	walk_down
	walk_down
	walk_right
	face_left
	step_end

Mahoganytown_Movement_LillieNorthToLine:
	walk_down
	walk_down
	face_left
	step_end

Mahoganytown_Movement_PlayerSouthToLine:
	walk_up
	walk_up
	face_left
	step_end

@ Anabel (20,22)->(20,21) to try to secure them, then (20,21)->(19,21) to
@ stand beside Lillie for the aftermath.
Mahoganytown_Movement_AnabelSteps:
	walk_up
	face_left
	step_end

Mahoganytown_Movement_AnabelToGroup:
	walk_left
	face_left
	step_end

@ Pryce (10,21)->(13,21): as far as the middle of the street, no further.
Mahoganytown_Movement_PryceToTalk:
	walk_right
	walk_right
	walk_right
	face_right
	step_end

@ Out west, off the framing (x=6) and away to fetch the lamp. Different rows,
@ so the two of them walk together.
Mahoganytown_Movement_PryceLeaves:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Mahoganytown_Movement_MamoswineLeaves:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Looker (12,20)->(17,20)->(17,22), west of the player, facing him.
Mahoganytown_Movement_LookerToGroup:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	face_right
	step_end

Mahoganytown_Movement_NinetalesLeansIn:
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

@ Retry only: the player talked to Lillie from (19,21) instead of (18,22).
Mahoganytown_Movement_PlayerRetryToLine:
	walk_left
	walk_down
	step_end

@ ---------------------------------------------------------------------------
@ Texts. Voices (design 3.1 and the Mahogany revision):
@   Lillie  polite, attentive, able to decide. She hesitates in front of real
@           uncertainty and never apologises for contributing. Her plan is
@           incomplete, not wrong, and she says so in one line and improves it.
@   Pryce   few words, clear instructions, dry humour. He respects Lillie by
@           trusting her with a concrete job, not with a speech about it.
@   Anabel  precise; separates what she sees from what she thinks.
@   Looker  warm before the danger, direct inside it, asks about people first,
@           and never talks down to the notebook.
@ Nobody hides Necrozma's name any more: Gladion identified it in Blackthorn
@ and Anabel says it out loud the moment it appears.
@ Nothing here says "tonight": the mission runs at any hour, and the blackout
@ is shown through lamps and equipment, not through the sky.
@ One speaker per block. Narration and the note carry no name box at all: a
@ message that does not open with {SPEAKER ...} has no plate and does NOT
@ inherit the last one.
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
@ ---------------------------------------------------------------------------
Mahoganytown_Text_DoorLocked:
	.string "The door is locked tight.\p"
	.string "A note is taped to it, stiff\n"
	.string "with frost:\p"
	.string "“Shelter is available at the\n"
	.string "Gym. Stay off the street.\l"
	.string "--Pryce”$"

Mahoganytown_Text_UBAnabelIdle:
	.string "{SPEAKER NAME_ANABEL}The Center has backup\n"
	.string "power. You can heal there.\p"
	.string "Looker is waiting by the road.$"

@ The reunion is a reunion. They have battled on Route 30, in Goldenrod and
@ in the Dragon's Den, so she does not introduce herself and does not explain
@ what she is doing in Johto.
Mahoganytown_Text_UBLillieIdle:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}! I'm glad you're\n"
	.string "here.\p"
	.string "I was staying nearby when the\n"
	.string "lights went out.\p"
	.string "Ninetales noticed something in\n"
	.string "the street before I did.\p"
	.string "I've been watching from the Gym\n"
	.string "window. I think I've found\l"
	.string "something useful.$"

Mahoganytown_Text_UBNinetalesIdle:
	.string "Ninetales lifts its ears toward\n"
	.string "the street.$"

Mahoganytown_Text_UBPryceIdle:
	.string "{SPEAKER NAME_PRYCE}Good. You're here.\p"
	.string "I'll have the last two inside\n"
	.string "shortly.\p"
	.string "Speak to the detectives.$"

Mahoganytown_Text_UBHectorIdle:
	.string "{SPEAKER NAME_HECTOR}My lamp's still on the\n"
	.string "porch.\p"
	.string "I don't want to leave it out\n"
	.string "there.$"

Mahoganytown_Text_UBBoyIdle:
	.string "{SPEAKER NAME_BOY}Grandpa, we can get it\n"
	.string "later.\p"
	.string "Please come inside.$"

Mahoganytown_Text_UBMamoswineIdle:
	.string "Mamoswine leaves a clear path\n"
	.string "to the door.$"

@ Looker points at what Lillie has, and does not make her defend it.
Mahoganytown_Text_UBLookerGreet:
	.string "{SPEAKER NAME_LOOKER}Lillie has been keeping\n"
	.string "watch from the Gym.\p"
	.string "She saw the two Pokémon before\n"
	.string "we arrived.$"

Mahoganytown_Text_UBLillieGreet:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}, could you help us\n"
	.string "keep them apart?\p"
	.string "I'll show you what I mean.$"

Mahoganytown_Text_UBLillieObservation:
	.string "{SPEAKER NAME_LILLIE}Xurkitree touches the\n"
	.string "street lamps.\p"
	.string "Then a light runs across the\n"
	.string "street to Celesteela.\p"
	.string "Celesteela's engines flare\n"
	.string "each time.$"

Mahoganytown_Text_UBAnabelObservation:
	.string "{SPEAKER NAME_ANABEL}Does the light stay\n"
	.string "between them?$"

Mahoganytown_Text_UBLillieLimit:
	.string "{SPEAKER NAME_LILLIE}For as long as I could\n"
	.string "see them.\p"
	.string "I couldn't follow it back any\n"
	.string "farther.\p"
	.string "If we draw them apart, we might\n"
	.string "break it.$"

Mahoganytown_Text_UBAnabelPlan:
	.string "{SPEAKER NAME_ANABEL}We'll try that.\p"
	.string "I'll watch the connection as\n"
	.string "they move.$"

Mahoganytown_Text_UBReady:
	.string "{SPEAKER NAME_LOOKER}Ready to join them,\n"
	.string "{PLAYER}?$"

Mahoganytown_Text_UBNotReady:
	.string "{SPEAKER NAME_LOOKER}Take the time to\n"
	.string "prepare.\p"
	.string "We'll keep the road clear.$"

Mahoganytown_Text_UBTimeIsClose:
	.string "{SPEAKER NAME_ANABEL}The readings are rising.\p"
	.string "Pryce, we need the street\n"
	.string "clear.$"

Mahoganytown_Text_UBPryceEvacuates:
	.string "{SPEAKER NAME_PRYCE}Inside, Hector.\n"
	.string "Both of you.$"

Mahoganytown_Text_UBHectorLamp:
	.string "{SPEAKER NAME_HECTOR}And my lamp?$"

Mahoganytown_Text_UBPryceLamp:
	.string "{SPEAKER NAME_PRYCE}I'll fetch it when we're\n"
	.string "done.\p"
	.string "Go on. Your grandson is\n"
	.string "waiting.$"

Mahoganytown_Text_UBLookerEvacuated:
	.string "{SPEAKER NAME_LOOKER}That's everyone.\p"
	.string "I'll keep this entrance clear.$"

Mahoganytown_Text_UBPryceMeets:
	.string "{SPEAKER NAME_PRYCE}Lillie. Show us where\n"
	.string "you saw the light.$"

Mahoganytown_Text_UBNecrozmaArrives:
	.string "{SPEAKER NAME_ANABEL}Necrozma.\p"
	.string "Pryce, watch the west side.$"

Mahoganytown_Text_UBLillieRecognizes:
	.string "{SPEAKER NAME_LILLIE}Necrozma…\p"
	.string "Ninetales, stay close.$"

Mahoganytown_Text_UBPryceCover:
	.string "{SPEAKER NAME_PRYCE}Mamoswine.\n"
	.string "Keep it away from the Gym.$"

Mahoganytown_Text_UBAppear:
	.string "{SPEAKER NAME_LILLIE}There.\n"
	.string "Those are the two I saw.$"

Mahoganytown_Text_UBSynergyObserved:
	.string "{SPEAKER NAME_LILLIE}That's the light.\p"
	.string "It reaches Celesteela every\n"
	.string "time.$"

Mahoganytown_Text_UBSynergyRead:
	.string "{SPEAKER NAME_ANABEL}I have it.\n"
	.string "Keep that path in sight.$"

Mahoganytown_Text_UBSavedOrder:
	.string "{SPEAKER NAME_LILLIE}Ninetales, Icy Wind!\n"
	.string "Across the road!$"

Mahoganytown_Text_UBSavedCheck:
	.string "{SPEAKER NAME_LILLIE}Are you all right,\n"
	.string "{PLAYER}?$"

Mahoganytown_Text_UBChoosePrompt:
	.string "{SPEAKER NAME_LILLIE}Which one will you take?\p"
	.string "Ninetales and I will draw the\n"
	.string "other away.$"

Mahoganytown_Text_ChoiceXurkitree:
	.string "Xurkitree$"

Mahoganytown_Text_ChoiceCelesteela:
	.string "Celesteela$"

Mahoganytown_Text_UBPickedXurkitree:
	.string "{SPEAKER NAME_LILLIE}We'll take Celesteela.\p"
	.string "Ninetales, lead it down this\n"
	.string "side.$"

Mahoganytown_Text_UBPickedCelesteela:
	.string "{SPEAKER NAME_LILLIE}We'll take Xurkitree.\p"
	.string "Ninetales, keep it away from\n"
	.string "the lines.$"

Mahoganytown_Text_UBFirstDown:
	.string "{SPEAKER NAME_LILLIE}You've stopped it!$"

Mahoganytown_Text_UBCurrentReturns:
	.string "{SPEAKER NAME_LILLIE}Wait--\n"
	.string "the light is still reaching it!$"

@ Origin and cost, both on screen: the far one dims while it gives.
Mahoganytown_Text_UBRevivedXurkitree:
	.string "{SPEAKER NAME_ANABEL}Celesteela's output\n"
	.string "dropped.\p"
	.string "Xurkitree is taking the energy.$"

Mahoganytown_Text_UBRevivedCelesteela:
	.string "{SPEAKER NAME_ANABEL}Xurkitree sent another\n"
	.string "charge.\p"
	.string "Celesteela's engines are\n"
	.string "restarting.$"

@ One line for the correction, then the better idea. No self-reproach.
Mahoganytown_Text_UBLilliePlanCorrection:
	.string "{SPEAKER NAME_LILLIE}I thought the distance\n"
	.string "would break it. It didn't.\p"
	.string "Mr. Pryce, can Mamoswine put a\n"
	.string "wall right across that light?$"

Mahoganytown_Text_UBPrycePlan:
	.string "{SPEAKER NAME_PRYCE}A wall?\n"
	.string "That we can do.\p"
	.string "Keep them clear of the middle.$"

Mahoganytown_Text_UBAnabelWallPlan:
	.string "{SPEAKER NAME_ANABEL}I'll watch for a change.\p"
	.string "Looker, keep the way back\n"
	.string "clear.$"

Mahoganytown_Text_UBNinetalesCover:
	.string "{SPEAKER NAME_LILLIE}Ninetales, Icy Wind!\p"
	.string "Keep them back while\n"
	.string "Mamoswine moves!$"

Mahoganytown_Text_UBWallOrder:
	.string "{SPEAKER NAME_PRYCE}Mamoswine.\n"
	.string "Ice across the gap.$"

Mahoganytown_Text_UBWallHolds:
	.string "{SPEAKER NAME_ANABEL}The transfer stopped.\p"
	.string "The wall is cutting it off.$"

Mahoganytown_Text_UBLillieWall:
	.string "{SPEAKER NAME_LILLIE}It's working.\p"
	.string "Ninetales, stay on this side\n"
	.string "of it.$"

Mahoganytown_Text_UBAnabelHeals:
	.string "{SPEAKER NAME_ANABEL}Come back here, {PLAYER}.\p"
	.string "Let me treat your team.$"

Mahoganytown_Text_UBAnabelHealed:
	.string "{SPEAKER NAME_ANABEL}They're ready.\p"
	.string "The connection is still down.$"

Mahoganytown_Text_UBSecondRound:
	.string "{SPEAKER NAME_LILLIE}I'll keep the other one\n"
	.string "here.\p"
	.string "Go ahead, {PLAYER}!$"

Mahoganytown_Text_UBLillieFoughtCelesteela:
	.string "{SPEAKER NAME_LILLIE}Celesteela's stopped\n"
	.string "too.\p"
	.string "Ninetales, hold there.$"

Mahoganytown_Text_UBLillieFoughtXurkitree:
	.string "{SPEAKER NAME_LILLIE}Xurkitree can't reach\n"
	.string "the connection.\p"
	.string "We've stopped it.$"

Mahoganytown_Text_UBSecure:
	.string "{SPEAKER NAME_ANABEL}Keep the barrier up.\p"
	.string "We'll try to secure them now.$"

Mahoganytown_Text_UBPryceIntercept:
	.string "{SPEAKER NAME_PRYCE}Mamoswine, block\n"
	.string "Necrozma!$"

Mahoganytown_Text_UBLillieNewLink:
	.string "{SPEAKER NAME_LILLIE}Above the ice!\p"
	.string "It's reaching them from above!$"

Mahoganytown_Text_UBNinetalesIntercept:
	.string "{SPEAKER NAME_LILLIE}Ninetales!\n"
	.string "Break that light!$"

@ The discovery, and it belongs to the instruments: no branch of this scene
@ owns it and no Pokemon in the party is needed for it.
Mahoganytown_Text_UBAbsorbedRead:
	.string "{SPEAKER NAME_ANABEL}I still have both\n"
	.string "signals.\p"
	.string "They're moving with Necrozma!$"

Mahoganytown_Text_UBLillieSignals:
	.string "{SPEAKER NAME_LILLIE}Both of them?$"

Mahoganytown_Text_UBAbsorbedConfirm:
	.string "{SPEAKER NAME_ANABEL}Yes.\n"
	.string "The same patterns as before.\p"
	.string "I'm recording them.$"

Mahoganytown_Text_UBNecrozmaSensesCosmog:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}, keep {STR_VAR_1}\n"
	.string "beside you.\p"
	.string "Ninetales, stay with them.$"

Mahoganytown_Text_UBNecrozmaSensesLegend:
	.string "{SPEAKER NAME_LILLIE}The opening's steady.\p"
	.string "Anabel, can you still see the\n"
	.string "two signals?$"

Mahoganytown_Text_UBPartnerRead:
	.string "{SPEAKER NAME_ANABEL}More clearly now.\p"
	.string "But they're still moving with\n"
	.string "Necrozma.$"

Mahoganytown_Text_UBLilliePartnerLimit:
	.string "{SPEAKER NAME_LILLIE}They're still in there…\p"
	.string "Stay beside {PLAYER},\n"
	.string "{STR_VAR_1}.$"

Mahoganytown_Text_UBNecrozmaGone:
	.string "{SPEAKER NAME_ANABEL}The opening has closed.\p"
	.string "I've lost the signal.$"

Mahoganytown_Text_UBPowerReturns:
	.string "{SPEAKER NAME_LOOKER}The power's back.\p"
	.string "I'll check on everyone inside.$"

Mahoganytown_Text_UBPryceClearsIce:
	.string "{SPEAKER NAME_PRYCE}Mamoswine.\n"
	.string "Open the road again.$"

Mahoganytown_Text_UBPryceThanks:
	.string "{SPEAKER NAME_PRYCE}That gave us the room we\n"
	.string "needed.\p"
	.string "Good work, both of you.$"

Mahoganytown_Text_UBLillieThanks:
	.string "{SPEAKER NAME_LILLIE}Thank you for trusting\n"
	.string "us.\p"
	.string "I didn't know whether the wall\n"
	.string "would work.$"

Mahoganytown_Text_UBPryceAnswer:
	.string "{SPEAKER NAME_PRYCE}You saw where to put it.\p"
	.string "Mamoswine did the rest.$"

Mahoganytown_Text_UBPryceGoodbye:
	.string "{SPEAKER NAME_PRYCE}I'd better fetch that\n"
	.string "lamp.\p"
	.string "He'll ask before he asks about\n"
	.string "the town.$"

Mahoganytown_Text_UBAftermathLooker:
	.string "{SPEAKER NAME_LOOKER}Everyone's all right.\p"
	.string "The path is clear.\n"
	.string "They're heading home.$"

Mahoganytown_Text_UBAftermathLillie:
	.string "{SPEAKER NAME_LILLIE}Those signals you\n"
	.string "recorded…\p"
	.string "Could Xurkitree and Celesteela\n"
	.string "still be alive?$"

Mahoganytown_Text_UBAftermathAnabel:
	.string "{SPEAKER NAME_ANABEL}They could.\p"
	.string "The patterns stayed distinct\n"
	.string "after the two disappeared.\p"
	.string "We have a reason to keep\n"
	.string "looking for them.$"

Mahoganytown_Text_UBAftermathBlackthorn:
	.string "{SPEAKER NAME_LOOKER}And perhaps the two from\n"
	.string "Blackthorn.\p"
	.string "I'll compare both recordings.$"

Mahoganytown_Text_UBAftermathLillieResolve:
	.string "{SPEAKER NAME_LILLIE}Then we should try to\n"
	.string "get them out.\p"
	.string "I'll help however I can.$"

Mahoganytown_Text_UBAftermathNextPlan:
	.string "{SPEAKER NAME_ANABEL}The wall stopped the\n"
	.string "transfer.\p"
	.string "Necrozma reached around it.\p"
	.string "Next time, we need to see that\n"
	.string "move sooner.$"

Mahoganytown_Text_UBAftermathNotes:
	.string "{SPEAKER NAME_LILLIE}I marked when each pulse\n"
	.string "started.\p"
	.string "You can keep these pages.$"

Mahoganytown_Text_UBAftermathAcceptNotes:
	.string "{SPEAKER NAME_ANABEL}Thank you.\p"
	.string "I'll match them to the\n"
	.string "readings.$"

Mahoganytown_Text_UBAftermathLegend:
	.string "{SPEAKER NAME_ANABEL}{STR_VAR_1} steadied the\n"
	.string "opening.\p"
	.string "The two signals became clearer,\n"
	.string "but stayed with Necrozma.\p"
	.string "We still need a way to free\n"
	.string "them.$"

Mahoganytown_Text_UBAftermathCosmog:
	.string "{SPEAKER NAME_LILLIE}Is {STR_VAR_1} all right?\p"
	.string "It can rest with Ninetales\n"
	.string "while we finish.$"

Mahoganytown_Text_UBHookLooker:
	.string "{SPEAKER NAME_LOOKER}We'll compare the records\n"
	.string "in Olivine.\p"
	.string "I'll call when we have\n"
	.string "something.\p"
	.string "Some rest for you.\n"
	.string "Some paperwork for us.$"

Mahoganytown_Text_UBHookLillieStay:
	.string "{SPEAKER NAME_LILLIE}I'll stay until the\n"
	.string "residents are settled.\p"
	.string "Then I'll send you anything\n"
	.string "else I find.$"

Mahoganytown_Text_UBLillieGoodbye:
	.string "{SPEAKER NAME_LILLIE}I'm glad we got to battle\n"
	.string "on the same side.\p"
	.string "Next time, I hope it's\n"
	.string "somewhere quieter.$"

Mahoganytown_Text_UBLillieSettling:
	.string "{SPEAKER NAME_LILLIE}They're coming out now.\p"
	.string "We'll make sure the path stays\n"
	.string "clear.\p"
	.string "Go and rest, {PLAYER}.$"

@ Anything that is not a win and is not a blackout. It never says the beasts
@ escaped: they are still standing in the street.
Mahoganytown_Text_UBUnresolved:
	.string "{SPEAKER NAME_ANABEL}The street isn't clear\n"
	.string "yet.\p"
	.string "Regroup before we move in\n"
	.string "again.$"

Mahoganytown_Text_UBRetryGreeting:
	.string "{SPEAKER NAME_LOOKER}We've kept them away\n"
	.string "from the Gym.\p"
	.string "The Center is ready for you.$"

Mahoganytown_Text_UBRetryLillie:
	.string "{SPEAKER NAME_LILLIE}Ninetales and I can try\n"
	.string "again.\p"
	.string "Are your Pokémon ready?$"

Mahoganytown_Text_UBRetryNotReady:
	.string "{SPEAKER NAME_LILLIE}Take care of them first.\p"
	.string "We'll stay here.$"

Mahoganytown_Text_UBRetryWallBroken:
	.string "A section of the wall of ice\n"
	.string "cracked, and came down.\p"
	.string "The light crossed the gap\n"
	.string "again.$"

@ Used only once the group has already watched a recharge happen: they know
@ the link exists, and the first fight is what opens the window for the ice.
Mahoganytown_Text_UBRetryPlan:
	.string "{SPEAKER NAME_ANABEL}We need to slow one down\n"
	.string "before Mamoswine can reach\l"
	.string "the gap.\p"
	.string "Choose your target.$"

Mahoganytown_Text_UBRetryRecharge:
	.string "{SPEAKER NAME_LILLIE}It's sending the charge.\p"
	.string "Mr. Pryce, now!$"
