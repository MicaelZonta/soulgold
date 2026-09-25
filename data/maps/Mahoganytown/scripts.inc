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
@   FLAG_TEMP_3 - the last two residents at the Gym door: shown with the
@                 incident; the scene walks them inside.
@   FLAG_TEMP_4 - Necrozma: always hidden at load, like the beasts.
@   FLAG_TEMP_5 - Pryce + Mamoswine: shown with the incident; they walk into
@                 the Gym at the end of the scene.
Mahoganytown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_4
	goto_if_unset FLAG_EVENT_ULTRABEAST_MAHOGANY, Mahoganytown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_5
	return

Mahoganytown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
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
@ Rift Mission 2 - Necrozma, Xurkitree + Celesteela in Mahogany Town.
@
@ Active while FLAG_EVENT_ULTRABEAST_MAHOGANY is set, which by invariant means
@ VAR_RIFT_MISSIONS_STATE == 5. Set by OlivineCity_House1, cleared here on
@ victory together with state 6. While it is set, every building door in
@ town is locked except the Pokemon Center's (sLockedTownDoors in
@ src/field_control_avatar.c -> Mahoganytown_EventScript_DoorLocked). The
@ Route 43 gate and Valor Cavern are non-animated doors and stay open.
@
@ Story: the town has had no power for three nights. Lillie has been here
@ for two days, alone, with a notebook (the briefing never mentions her: the
@ player discovers her). Pryce is walking the last two residents into his
@ Gym when the scene starts. Lillie recognised the beasts from Alola but has
@ never seen what opens the tear, and she says so: Anabel's instruments keep
@ the clock, not her. Then Necrozma arrives - which blindsides her - shrugs
@ off Pryce's Blizzard and lets Xurkitree and Celesteela through. The beasts keep each other alive (one drinks the current, the
@ other burns it and gives it back). Celesteela charges the player and
@ Ninetales knocks it away. The player beats the one they picked - and the
@ other one revives it through the link. Lillie works out why and asks
@ Pryce for ice: Ninetales and Mamoswine raise a wall between them, Anabel
@ heals the team, and the second fight is for real. Necrozma absorbs both
@ beasts and leaves (the pattern of every mission); Lillie recognises its
@ light from Alola but will not say more. Pryce goes back into his Gym.
@
@ Scene floor plan (raw collision, bit 11; '#' = blocked; y grows DOWNWARD):
@
@        x= 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23
@   y=19     #  W  #  #  .  .  .  .  .  .  #  #  W  #  #   W (10,19) Gym, (21,19) Center
@   y=20     .  O  P  X  >  >  .  .  .  .  .  .  f  .  .   f (21,20) Fly landing
@   y=21     .  B  M  :  >  n  N  L  .  .  .  .  t  .  .   t (21,21) talk to Looker
@   y=22     .  .  .  C  >  >  *  .  .  n  L  K  A  .  .   * (17,22) player's spot
@   y=23     #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
@
@   Before the scene (map.json):
@     O Old man (10,20)   B Boy (10,21)   P Pryce (11,20)   M Mamoswine (11,21)
@     n Ninetales (19,22) L Lillie (20,22) K Looker (21,22) A Anabel (22,22)
@   During the scene:
@     Pryce (11,20)->(14,20), Mamoswine (11,21)->(13,21): the front line.
@     Ninetales (19,22)->(15,21), Lillie (20,22)->(16,21), player ->(17,22),
@     Looker ->(21,21), Anabel ->(22,21) (the skeleton's approach, unchanged).
@     Necrozma appears at (11,21) (Mamoswine's old tile, free by then);
@     Xurkitree X (12,20) and Celesteela C (12,22) flank it, with the gap
@     (12,21) between them - the wall of ice goes there.
@
@ Camera with the player at (17,22): x 10..24, y ~18..27. The Gym door
@ (10,19) is on screen. Nobody stands south of the player, so the text box
@ covers no one.
@
@ Looker sits in a pocket: (21,23) is wall, (20,22) is Lillie and (22,22) is
@ Anabel. The ONLY tile he can be talked to from is (21,21), facing down.
@ That is what makes the start of the cutscene deterministic without a
@ getplayerxy check. HEAL_LOCATION_MAHOGANYTOWN is (21,20), one step north of
@ it, so a blackout retry lands right next to him.
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1..5 - visibility caches (see ApplyUBVisibility above)
@   VAR_TEMP_2  - battle outcome
@   VAR_TEMP_3  - the player's pick: 0 = Xurkitree, 1 = Celesteela. Survives
@                 both battles because returning from a battle does not
@                 reload the map (ClearTempFieldEventData only runs on
@                 warp/edge loads).
@   VAR_TEMP_4  - Cosmog-family species Necrozma reacted to (SPECIES_NONE =
@                 no reaction). Read again by the aftermath dialogue.
@ WARNING: VAR_TEMP_0 and VAR_TEMP_1 belong to the Rage Candy Bar merchant
@ (getplayerxy, above in this file). This mission starts at VAR_TEMP_2 on
@ purpose - do NOT "harmonise" it with the Blackthorn mission.
@
@ WARNING: the eight residents of this map carry
@ FLAG_EVENT_ULTRABEAST_MAHOGANY in their map.json "flag" field. A
@ removeobject on any of them SETS that flag and empties the town. The two
@ residents of the scene are separate objects on FLAG_TEMP_3.
@ WARNING: the old man stands on (10,20), the tile of the vanilla Fat man
@ (local 4, FLAG_HIDE_MAHOGANY_TOWN_FATMAN). That flag is set for good in
@ RocketHideout_B2F, long before the postgame, so the tile is free.
@
@ Object budget: player + follower + 11 = 13/16. Palettes on screen: player,
@ follower, Lillie, Looker, NPC_4 (Anabel, old man, boy), Pryce, Ninetales,
@ Xurkitree, Celesteela, Necrozma, Mamoswine = 11, as many as Blackthorn.
@ ============================================================================

Mahoganytown_EventScript_DoorLocked::
	lockall
	msgbox Mahoganytown_Text_DoorLocked, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Mahoganytown_EventScript_UBAnabel::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBAnabelIdle, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

@ Lillie and Ninetales watch the street to the north (FACE_UP in map.json),
@ and must still be facing that way when the scene starts.
@ The turnobject is a deliberate no-op today: (20,23) is wall, (19,22) is
@ Ninetales and (21,22) is Looker, so the player can ONLY reach her from
@ (20,21) and faceplayer already leaves her facing north. It stays as the
@ guard for any evolution that moves her.
@ Optional reaction to a Cosmog-family Pokemon in the party: Ninetales
@ notices first. Lillie remembers Nebby; she never calls the player's
@ Pokemon Nebby.
Mahoganytown_EventScript_UBLillie::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBLillieIdle, MSGBOX_DEFAULT
	closemessage
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	goto_if_eq VAR_RESULT, SPECIES_NONE, Mahoganytown_EventScript_UBLillieFaceNorth
	bufferspeciesname STR_VAR_1, VAR_RESULT
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, Mahoganytown_EventScript_UBLillieCosmog
	goto_if_eq VAR_RESULT, SPECIES_COSMOEM, Mahoganytown_EventScript_UBLillieCosmoem
	msgbox Mahoganytown_Text_UBLillieIdleLegend, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBLillieFaceNorthClose

Mahoganytown_EventScript_UBLillieCosmog::
	msgbox Mahoganytown_Text_UBLillieIdleCosmog, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBLillieFaceNorthClose

Mahoganytown_EventScript_UBLillieCosmoem::
	msgbox Mahoganytown_Text_UBLillieIdleCosmoem, MSGBOX_DEFAULT
Mahoganytown_EventScript_UBLillieFaceNorthClose::
	closemessage
Mahoganytown_EventScript_UBLillieFaceNorth::
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_NORTH
	release
	end

@ Pryce is busy with the old man, so no faceplayer: he talks over his
@ shoulder. Reachable only from (12,20): (11,19) is wall, (10,20) is the old
@ man and (11,21) is Mamoswine.
Mahoganytown_EventScript_UBPryce::
	lock
	msgbox Mahoganytown_Text_UBPryceIdle, MSGBOX_DEFAULT
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	goto_if_eq VAR_RESULT, SPECIES_NONE, Mahoganytown_EventScript_UBReleaseEnd
	bufferspeciesname STR_VAR_1, VAR_RESULT
	msgbox Mahoganytown_Text_UBPryceIdleCosmog, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBReleaseEnd

Mahoganytown_EventScript_UBMamoswine::
	lock
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_NORMAL
	msgbox Mahoganytown_Text_UBMamoswineIdle, MSGBOX_DEFAULT
	waitmoncry
	goto Mahoganytown_EventScript_UBReleaseEnd

Mahoganytown_EventScript_UBOldMan::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBOldManIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_OLD_MAN, DIR_EAST     @ back to arguing with Pryce (11,20)
	release
	end

Mahoganytown_EventScript_UBBoy::
	lock
	faceplayer
	msgbox Mahoganytown_Text_UBBoyIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_BOY, DIR_NORTH        @ back to his grandfather (10,20)
	release
	end

Mahoganytown_EventScript_UBReleaseEnd::
	closemessage
	release
	end

@ Nothing changes state before the YES. The YES is the last exit point: from
@ there on everything is scripted through to a battle outcome.
@ Lillie's reading comes BEFORE the YES on purpose: she has to have told the
@ group what she saw before anyone moves (design section 3.2). What she does
@ NOT know yet - that keeping them apart is not enough - is what the scene
@ teaches her.
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
	goto Mahoganytown_EventScript_UBReleaseEnd

@ SKELETON: the rift, every hit and the wall of ice are camera shakes plus
@ white flashes; the Pokemon only walk in place. Evolution: the town's
@ blackout staged with the palette, the lamps coming back at the end, move
@ animations, Necrozma's own music.
@
@ The order of the three approach blocks is LOAD-BEARING:
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
	@ The evacuation, finished on screen. Pryce (11,20) faces west at the old
	@ man (10,20) already.
	msgbox Mahoganytown_Text_UBTimeIsClose, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_OLD_MAN, DIR_EAST
	msgbox Mahoganytown_Text_UBPryceEvacuates, MSGBOX_DEFAULT
	closemessage
	@ Old man (10,20)->(10,19) into the door; then the boy (10,21)->(10,20)
	@ ->(10,19). Sequential: the boy steps onto the tile the old man leaves.
	opendoor 10, 19
	waitdooranim
	applymovement LOCALID_MAHOGANY_UB_OLD_MAN, Mahoganytown_Movement_EnterGymFromFront
	waitmovement LOCALID_MAHOGANY_UB_OLD_MAN
	removeobject LOCALID_MAHOGANY_UB_OLD_MAN          @ flag FLAG_TEMP_3: harmless
	applymovement LOCALID_MAHOGANY_UB_BOY, Mahoganytown_Movement_BoyEnterGym
	waitmovement LOCALID_MAHOGANY_UB_BOY
	removeobject LOCALID_MAHOGANY_UB_BOY
	closedoor 10, 19
	waitdooranim
	@ Pryce (11,20)->(12,20)->(13,20)->(14,20), Mamoswine (11,21)->(12,21)
	@ ->(13,21). Different rows the whole way -> together. Both end facing
	@ west, where the tear opens.
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Mahoganytown_Movement_PryceToFront
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_MamoswineToFront
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	@ Player (17,22) is east of Pryce (14,20): dx=+3 dominates -> DIR_EAST.
	turnobject LOCALID_MAHOGANY_UB_PRYCE, DIR_EAST
	msgbox Mahoganytown_Text_UBPryceMeets, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_MAHOGANY_UB_PRYCE, DIR_WEST
	msgbox Mahoganytown_Text_UBLightComing, MSGBOX_DEFAULT
	closemessage
	@ Necrozma arrives in the light, on (11,21), Mamoswine's old tile.
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_4
	addobject LOCALID_MAHOGANY_UB_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmoncry
	msgbox Mahoganytown_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
	closemessage
	@ Pryce tries: Mamoswine (13,21) attacks west along its row at (11,21).
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_AttackInPlaceLeft
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	msgbox Mahoganytown_Text_UBNoEffect, MSGBOX_DEFAULT
	closemessage
	@ The rift: the beasts come through on either side of it.
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
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
	@ The synergy, shown before it is explained: Xurkitree (12,20) drains
	@ and sends the current down to Celesteela (12,22), which burns it.
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_PulseInPlaceRight
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBFeedDown
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBFeedUp
	playmoncry SPECIES_CELESTEELA, CRY_MODE_NORMAL
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	msgbox Mahoganytown_Text_UBSynergy, MSGBOX_DEFAULT
	closemessage
	@ Danger to the player: Celesteela (12,22)->(15,22) along row 22, which
	@ is empty (Mamoswine and Ninetales are on row 21). It stops two tiles
	@ short of the player (17,22).
	msgbox Mahoganytown_Text_UBCharge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBCharge
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	@ Ninetales (15,21) is right above it: turns south and hits it.
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_AttackInPlaceDown
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	call Mahoganytown_EventScript_UBShake
	call Mahoganytown_EventScript_UBFlash
	@ Blown back to its tile, still facing east: (15,22)->(12,22).
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBKnockedBack
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_WEST
	msgbox Mahoganytown_Text_UBSaved, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBChoose

@ Flash da cena. fadescreenswapbuffers e NAO fadescreen: fadescreen copia
@ gPlttBufferFaded -> gPlttBufferUnfaded ao escurecer (src/field_weather.c,
@ FadeScreen) e o FADE_FROM_* seguinte reaplica o tint de horario por cima do
@ que ja estava tintado. A noite (coeff 10) cada par de flashes multiplicava a
@ cena por ~0,46 de novo, e depois de tres ou quatro a cidade ficava preta.
@ fadescreenswapbuffers usa BLDY no hardware e nao encosta nas paletas.
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

@ Standard Rift Mission structure: the player picks which Ultra Beast to
@ fight, the mission companion takes the other. No cancel (ignoreBPress
@ TRUE) - the scene has already started, so VAR_RESULT can only be 0 or 1.
@ The pick is per attempt: after a blackout the player chooses again, and
@ it holds for BOTH rounds of this attempt.
@ Everyone already faces the right way whichever branch is taken: the player
@ (17,22), Lillie (16,21) and Ninetales (15,21) are east of both beasts at
@ x=12, and the beasts face east. No turnobject is needed.
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
	goto Mahoganytown_EventScript_UBBattle1

Mahoganytown_EventScript_UBPickCelesteela::
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	msgbox Mahoganytown_Text_UBPickedCelesteela, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle1

@ Two boss battles in a row against the SAME beast (the player's pick).
@ Boss setup only survives a SIMPLE battle, which is the other reason the
@ mission splits the beasts. B_FLAG_NO_WHITEOUT is deliberately NOT set in
@ either: this is a threat battle, so losing means a blackout and a retry
@ of the whole scene (both rounds - nothing between them is saved).
@
@ Round 1: 2 bars / Lv80 / x130. Short on purpose: it has to feel like a
@ win, so the revival lands.
@ Round 2: 4 bars / Lv80 / x130, the Mission 2 target of the design scale
@ (section 6). Anabel heals the team between the rounds.
@ If playtesting says "wall" instead of "threat", turn the screws in this
@ order, one at a time: round 1 down to 1 bar; x130 -> 120 in both; round 2
@ 4 bars -> 3; drop the held item; only then the level.
@
@ Macro order is the same as bosslegendaryencounterwithmoves
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
@ seteventmonmoves -> special. No path leaves the script in between, so no
@ clearbossbattle is needed.
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

@ LOST, DREW and FORFEITED never come back here - the engine blacks the
@ player out to the Mahogany Pokémon Center (Mahoganytown_OnLoad does the
@ setrespawn). CAUGHT and RAN are unreachable (ball blocked; Run becomes
@ FORFEITED in a boss) but are handled anyway: anything that is not WON
@ resets the scene, never wins it. Same for round 2 below.
Mahoganytown_EventScript_UBStartBattle1::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, Mahoganytown_EventScript_UBRevived
	goto Mahoganytown_EventScript_UBUnresolved

@ The twist: the beast the player just beat is revived by its partner
@ through the link. The partner sends (pulses toward it), a flash, the
@ beaten one takes it in. Xurkitree (12,20) is north of Celesteela (12,22).
Mahoganytown_EventScript_UBRevived::
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBXurkitreeRevives
	msgbox Mahoganytown_Text_UBDownXurkitree, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBFeedUp
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBFeedDown
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	msgbox Mahoganytown_Text_UBRevivedXurkitree, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBLilliePlan

Mahoganytown_EventScript_UBXurkitreeRevives::
	msgbox Mahoganytown_Text_UBDownCelesteela, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBFeedDown
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmoncry
	call Mahoganytown_EventScript_UBFlash
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBFeedUp
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	waitmoncry
	msgbox Mahoganytown_Text_UBRevivedCelesteela, MSGBOX_DEFAULT

@ Lillie works out why and turns it into a plan; Pryce supplies the ice.
@ Anabel (22,21)->(22,22)->(21,22)->(20,22)->(19,22)->(18,22) to heal the
@ team: row 22 east of the player is empty (the cast left it), and (22,22)
@ is her own map.json tile. She stays at (18,22) for the rest of the scene.
@ Then the wall: Ninetales (15,21)->(14,21), next to Mamoswine (13,21), and
@ both fire west at the gap (12,21) between the beasts.
Mahoganytown_EventScript_UBLilliePlan::
	closemessage
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	msgbox Mahoganytown_Text_UBLilliePlan, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Mahoganytown_Movement_AnabelToPlayer
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBAnabelHeals, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	special HealPlayerParty
	playfanfare MUS_HEAL
	waitfanfare
	fadescreenswapbuffers FADE_FROM_BLACK
	msgbox Mahoganytown_Text_UBAnabelHealed, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_NinetalesToWall
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	msgbox Mahoganytown_Text_UBWallOrder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAHOGANY_UB_NINETALES, Mahoganytown_Movement_AttackInPlaceLeft
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_AttackInPlaceLeft
	playmoncry SPECIES_NINETALES_ALOLA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_NINETALES
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	waitmoncry
	playmoncry SPECIES_MAMOSWINE, CRY_MODE_ENCOUNTER
	call Mahoganytown_EventScript_UBShake
	call Mahoganytown_EventScript_UBFlash
	waitmoncry
	@ The link tries again and dies against the ice.
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBFeedDown
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBFeedUp
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	msgbox Mahoganytown_Text_UBWallHolds, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBBattle2

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

@ Nothing was recorded as done: the event flag is still set, so reloading the
@ map puts the cast, Pryce and the two residents back on their map.json
@ spots with the beasts and Necrozma hidden again, and talking to Looker
@ restarts the whole scene - the pick included.
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
@ Then Necrozma absorbs BOTH beasts - the pattern of every Rift Mission.
@ Positions at this point (a battle does not reload the map): Xurkitree
@ (12,20), Celesteela (12,22), Necrozma (11,21).
Mahoganytown_EventScript_UBResolved::
	goto_if_eq VAR_TEMP_3, 1, Mahoganytown_EventScript_UBLillieFoughtXurkitree
	msgbox Mahoganytown_Text_UBLillieFoughtCelesteela, MSGBOX_DEFAULT
	goto Mahoganytown_EventScript_UBAbsorb

Mahoganytown_EventScript_UBLillieFoughtXurkitree::
	msgbox Mahoganytown_Text_UBLillieFoughtXurkitree, MSGBOX_DEFAULT

Mahoganytown_EventScript_UBAbsorb::
	closemessage
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_PulseInPlaceRight
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	waitmoncry
	@ Dragged backwards, still facing east, to the tiles beside Necrozma:
	@ (12,20)->(11,20) and (12,22)->(11,22). Same sequence, rows apart.
	applymovement LOCALID_MAHOGANY_UB_XURKITREE, Mahoganytown_Movement_UBPulledIn
	applymovement LOCALID_MAHOGANY_UB_CELESTEELA, Mahoganytown_Movement_UBPulledIn
	waitmovement LOCALID_MAHOGANY_UB_XURKITREE
	waitmovement LOCALID_MAHOGANY_UB_CELESTEELA
	call Mahoganytown_EventScript_UBShake
	@ Their flag is FLAG_TEMP_2, so removeobject setting it is harmless.
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_XURKITREE
	removeobject LOCALID_MAHOGANY_UB_CELESTEELA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_LILLIE, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Common_Movement_ExclamationMark
	applymovement LOCALID_MAHOGANY_UB_ANABEL, Common_Movement_ExclamationMark
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	waitmovement LOCALID_MAHOGANY_UB_LILLIE
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	waitmovement LOCALID_MAHOGANY_UB_ANABEL
	waitmoncry
	msgbox Mahoganytown_Text_UBAbsorbed, MSGBOX_DEFAULT
	closemessage
	call Mahoganytown_EventScript_UBNecrozmaSensesCosmog
	@ Necrozma leaves the way it came. Own flag (FLAG_TEMP_4): removeobject
	@ touches nobody else.
	call Mahoganytown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_MAHOGANY_UB_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox Mahoganytown_Text_UBNecrozmaGone, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBAftermath

@ Optional reaction to a Cosmog-family Pokemon in the party (non-egg; the
@ special is the one Elm's Eviolite scene uses). Checked AFTER the battles on
@ purpose: they can evolve it. Necrozma steps toward the player,
@ (11,21)->(12,21), the gap where the wall stood (free: nobody is on it).
Mahoganytown_EventScript_UBNecrozmaSensesCosmog::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, Mahoganytown_EventScript_UBReturn
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	applymovement LOCALID_MAHOGANY_UB_NECROZMA, Mahoganytown_Movement_NecrozmaLean
	waitmovement LOCALID_MAHOGANY_UB_NECROZMA
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	playmoncry SPECIES_NECROZMA, CRY_MODE_NORMAL
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmoncry
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, Mahoganytown_EventScript_UBNecrozmaSensesLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, Mahoganytown_EventScript_UBNecrozmaSensesLegend
	msgbox Mahoganytown_Text_UBNecrozmaSensesCosmog, MSGBOX_DEFAULT
	closemessage
	return

Mahoganytown_EventScript_UBNecrozmaSensesLegend::
	msgbox Mahoganytown_Text_UBNecrozmaSensesLegend, MSGBOX_DEFAULT
	closemessage
	return

Mahoganytown_EventScript_UBReturn::
	return

Mahoganytown_EventScript_UBAftermath::
	@ Looker (21,21)->(20,21)->(19,21)->(18,21), faces west at the player.
	@ Anabel is already at (18,22), beside the player, since the heal.
	applymovement LOCALID_MAHOGANY_UB_LOOKER, Mahoganytown_Movement_LookerToPlayer
	waitmovement LOCALID_MAHOGANY_UB_LOOKER
	@ Everyone onto the player (17,22): Pryce (14,20) east (dx=+3 over
	@ dy=+2), Mamoswine (13,21) and Ninetales (14,21) east, Lillie (16,21)
	@ south (dx=+1, dy=+1: south keeps her from looking through Ninetales).
	turnobject LOCALID_MAHOGANY_UB_PRYCE, DIR_EAST
	turnobject LOCALID_MAHOGANY_UB_MAMOSWINE, DIR_EAST
	turnobject LOCALID_MAHOGANY_UB_NINETALES, DIR_EAST
	turnobject LOCALID_MAHOGANY_UB_LILLIE, DIR_SOUTH
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBAftermath, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, Mahoganytown_EventScript_UBPryceLeaves
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, Mahoganytown_EventScript_UBAftermathLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, Mahoganytown_EventScript_UBAftermathLegend
	msgbox Mahoganytown_Text_UBAftermathCosmog, MSGBOX_DEFAULT
	closemessage
	goto Mahoganytown_EventScript_UBPryceLeaves

Mahoganytown_EventScript_UBAftermathLegend::
	msgbox Mahoganytown_Text_UBAftermathLegend, MSGBOX_DEFAULT
	closemessage

@ Pryce goes back to his people. Pryce (14,20)->(13,20)->(12,20)->(11,20)
@ ->(10,20)->(10,19), into the Gym; THEN Mamoswine (13,21)->(12,21)
@ ->(11,21)->(10,21)->(10,20)->(10,19). Sequential: Mamoswine's last two
@ tiles are Pryce's. Every tile is free: the beasts and Necrozma are gone.
@ Their flag is FLAG_TEMP_5, so removeobject is harmless.
Mahoganytown_EventScript_UBPryceLeaves::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBPryceGoodbye, MSGBOX_DEFAULT
	closemessage
	opendoor 10, 19
	waitdooranim
	applymovement LOCALID_MAHOGANY_UB_PRYCE, Mahoganytown_Movement_PryceToGym
	waitmovement LOCALID_MAHOGANY_UB_PRYCE
	removeobject LOCALID_MAHOGANY_UB_PRYCE
	applymovement LOCALID_MAHOGANY_UB_MAMOSWINE, Mahoganytown_Movement_MamoswineToGym
	waitmovement LOCALID_MAHOGANY_UB_MAMOSWINE
	removeobject LOCALID_MAHOGANY_UB_MAMOSWINE
	closedoor 10, 19
	waitdooranim
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox Mahoganytown_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_MAHOGANY      @ invariant: flag and var together
	setvar VAR_RIFT_MISSIONS_STATE, 6
	@ Reload in place under the fade. With the flag cleared the residents
	@ would otherwise pop in one by one as the camera moved, and the cast
	@ would linger; ON_TRANSITION repopulates the town and hides the cast in
	@ one go. Lillie and Ninetales leave together, as they must, the doors
	@ unlock with the flag, and the warp also undoes the hidefollower.
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

Mahoganytown_Movement_EnterGymFromFront:
	walk_up
	set_invisible
	step_end

Mahoganytown_Movement_BoyEnterGym:
	walk_up
	walk_up
	set_invisible
	step_end

Mahoganytown_Movement_PryceToFront:
	walk_right
	walk_right
	walk_right
	face_left
	step_end

Mahoganytown_Movement_MamoswineToFront:
	walk_right
	walk_right
	face_left
	step_end

Mahoganytown_Movement_AttackInPlaceLeft:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

Mahoganytown_Movement_AttackInPlaceDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

Mahoganytown_Movement_PulseInPlaceRight:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

Mahoganytown_Movement_UBFeedDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	face_right
	step_end

Mahoganytown_Movement_UBFeedUp:
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	face_right
	step_end

Mahoganytown_Movement_UBCharge:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

Mahoganytown_Movement_UBKnockedBack:
	lock_facing_direction
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_facing_direction
	step_end

Mahoganytown_Movement_NinetalesToWall:
	walk_left
	face_left
	step_end

Mahoganytown_Movement_UBPulledIn:
	lock_facing_direction
	walk_slow_left
	unlock_facing_direction
	step_end

Mahoganytown_Movement_NecrozmaLean:
	walk_slow_right
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

Mahoganytown_Movement_PryceToGym:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	set_invisible
	step_end

Mahoganytown_Movement_MamoswineToGym:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	set_invisible
	step_end

@ Voices (design section 3.1): Looker theatrical and warm, direct in danger,
@ asks about people first; Anabel precise, separates what she sees from
@ what she thinks; Lillie polite, specific, holds her ground and changes her
@ plan when the facts change; Pryce old, dry and patient, speaks in cold
@ weather.
@ Lillie NEVER predicts anything. She has experience (she knows an Ultra
@ Beast on sight and she knows Necrozma's light), but this incident is a
@ surprise to her: she reports what she wrote down, hedges it, offers one
@ idea, and is wrong about it. Anything that would make her sound like she
@ saw this coming belongs to Anabel and her instruments instead. Nobody names Necrozma: Looker and Anabel know it only as the
@ creature from Blackthorn, Pryce has never seen it, and Lillie recognises
@ the light from Alola and refuses to say more yet. Nobody says where the
@ next rift will open.
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
Mahoganytown_Text_DoorLocked:
	.string "The door is locked tight.\p"
	.string "A note is taped to it, stiff\n"
	.string "with frost:\p"
	.string "“Everyone is safe. This door\n"
	.string "stays shut until I say so.\l"
	.string "--Pryce”$"

Mahoganytown_Text_UBAnabelIdle:
	.string "{SPEAKER NAME_ANABEL}The Pokémon Center\n"
	.string "runs on its own generator.\p"
	.string "It is the only light left in\n"
	.string "this town. Heal there first.\p"
	.string "Then speak with Looker.$"

@ Ela e a DESCOBERTA da missao, mas nao e uma desconhecida: o jogador ja
@ batalhou com ela na Route 30, em Goldenrod (SquirtBottle) e no Dragon's Den.
@ A fala e um reencontro, nao uma apresentacao, e ela nao explica ao jogador
@ que veio para Johto - ele esteve com ela em Johto tres vezes. A Lusamine
@ nao e citada: a primeira aparicao dela no arco e a M4 (New Bark).
Mahoganytown_Text_UBLillieIdle:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}! It's really\n"
	.string "you.\p"
	.string "The detective kept saying the\n"
	.string "Champion was on the way.\p"
	.string "He never said it would be\n"
	.string "someone I've battled three\l"
	.string "times.\p"
	.string "I stopped in Mahogany for one\n"
	.string "night. Ninetales loves this\l"
	.string "cold.\p"
	.string "Then the lights went out, and\n"
	.string "I saw what was standing in\l"
	.string "the street.\p"
	.string "I knew what they were the\n"
	.string "moment I saw them. I was\l"
	.string "never supposed to see one\l"
	.string "again.\p"
	.string "I've written down everything\n"
	.string "for two days and I still\l"
	.string "don't understand any of it.\p"
	.string "Talk to Looker. I'd rather\n"
	.string "show it to everyone at once.$"

Mahoganytown_Text_UBLillieIdleCosmog:
	.string "{SPEAKER NAME_LILLIE}Your {STR_VAR_1} keeps\n"
	.string "looking up at the sky.\p"
	.string "Nebby used to do that. Right\n"
	.string "before something went wrong.\p"
	.string "…Keep it close tonight.\n"
	.string "Please.$"

Mahoganytown_Text_UBLillieIdleCosmoem:
	.string "{SPEAKER NAME_LILLIE}Your {STR_VAR_1} has gone\n"
	.string "so still.\p"
	.string "Nebby went still like that,\n"
	.string "once. It was the hardest\l"
	.string "night of my life.\p"
	.string "…I'm sorry. It's only the\n"
	.string "dark. Keep it close.$"

Mahoganytown_Text_UBLillieIdleLegend:
	.string "{SPEAKER NAME_LILLIE}Your {STR_VAR_1} hasn't\n"
	.string "taken its eyes off the west\l"
	.string "end of town since you came.\p"
	.string "Whatever comes tonight…\n"
	.string "I think it already knows.$"

Mahoganytown_Text_UBPryceIdle:
	.string "{SPEAKER NAME_PRYCE}Hm. The Champion.\p"
	.string "Every soul in Mahogany is\n"
	.string "under my Gym tonight.\p"
	.string "Every soul but this one.\p"
	.string "{SPEAKER NAME_OLD_MAN}I'm not leaving my\n"
	.string "lamp, Pryce.\p"
	.string "{SPEAKER NAME_PRYCE}…The detective is by\n"
	.string "the Pokémon Center. Go.\p"
	.string "I've been arguing with this\n"
	.string "man for forty years. I can\l"
	.string "manage one more night.$"

Mahoganytown_Text_UBPryceIdleCosmog:
	.string "{SPEAKER NAME_PRYCE}That {STR_VAR_1} of yours\n"
	.string "is shivering in its ball.\p"
	.string "It isn't the cold.\n"
	.string "I would know.$"

Mahoganytown_Text_UBMamoswineIdle:
	.string "Mamoswine is standing guard\n"
	.string "beside Pryce, still as ice.$"

Mahoganytown_Text_UBOldManIdle:
	.string "Sixty years I've lit the lamp\n"
	.string "on my porch. Every night.\p"
	.string "I'm not hiding under a Gym\n"
	.string "because the power's out!$"

Mahoganytown_Text_UBBoyIdle:
	.string "Grandpa says the monster only\n"
	.string "eats electricity.\p"
	.string "…It doesn't eat Pokémon too,\n"
	.string "does it?$"

Mahoganytown_Text_UBLookerGreet:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! You came.\n"
	.string "Good. Very good.\p"
	.string "And yes, before you ask. That\n"
	.string "is a young lady with a\l"
	.string "notebook.\p"
	.string "She was here before any of us.\n"
	.string "Two days, alone, in a town\l"
	.string "with no light.\p"
	.string "Mr. Pryce asked her to leave.\n"
	.string "Twice. She thanked him very\l"
	.string "politely, both times.$"

Mahoganytown_Text_UBLillieTheory:
	.string "{SPEAKER NAME_LILLIE}I'm sorry. I couldn't\n"
	.string "go. Not before I understood\l"
	.string "them.\p"
	.string "There are two, and they come\n"
	.string "at about the same hour.\p"
	.string "I've never seen where they\n"
	.string "come from. The street is too\l"
	.string "dark, and I was watching from\l"
	.string "a window.\p"
	.string "By the time I find them,\n"
	.string "they're already there.\p"
	.string "But I did see this much.\p"
	.string "One of them pulls the\n"
	.string "electricity out of\l"
	.string "everything. The lamps. The\l"
	.string "lines. The houses.\p"
	.string "The other takes it, burns it,\n"
	.string "and gives it right back.\p"
	.string "{SPEAKER NAME_ANABEL}A closed loop. Each one\n"
	.string "keeping the other alive.\p"
	.string "{SPEAKER NAME_LILLIE}…Yes. I think so.\p"
	.string "I couldn't have said it that\n"
	.string "cleanly.\p"
	.string "{SPEAKER NAME_LOOKER}Hm. That is a great\n"
	.string "deal to conclude from one\l"
	.string "notebook, mademoiselle.\p"
	.string "{SPEAKER NAME_LILLIE}It's two nights of\n"
	.string "notes, and I could still be\l"
	.string "wrong about all of it.\p"
	.string "I'd rather be wrong out loud\n"
	.string "than quiet and right.\p"
	.string "{SPEAKER NAME_ANABEL}My instruments say\n"
	.string "what her notebook says. And\l"
	.string "they say tonight is close.\p"
	.string "{SPEAKER NAME_LILLIE}Then… if we keep them\n"
	.string "apart, neither one can feed\l"
	.string "the other.\p"
	.string "It's the only idea I have.$"

Mahoganytown_Text_UBReady:
	.string "{SPEAKER NAME_LOOKER}Then we do it her way.\p"
	.string "Once it opens, there is no\n"
	.string "stepping back, {PLAYER}.\p"
	.string "Are you and your Pokémon\n"
	.string "ready?$"

Mahoganytown_Text_UBNotReady:
	.string "{SPEAKER NAME_LOOKER}Of course. Heal up.\n"
	.string "Check your team.\p"
	.string "Miss Anabel says we still have\n"
	.string "a little time, and I have\l"
	.string "learned not to argue with her\l"
	.string "instruments.$"

Mahoganytown_Text_UBTimeIsClose:
	.string "{SPEAKER NAME_ANABEL}The readings are\n"
	.string "climbing. It is close.\p"
	.string "{SPEAKER NAME_LILLIE}Mr. Pryce, please!\n"
	.string "He shouldn't be out here!$"

Mahoganytown_Text_UBPryceEvacuates:
	.string "{SPEAKER NAME_PRYCE}You heard her, Hector.\n"
	.string "Inside. Now.\p"
	.string "{SPEAKER NAME_OLD_MAN}Sixty years, Pryce.\n"
	.string "Not one night without my lamp.\p"
	.string "{SPEAKER NAME_PRYCE}Then don't make tonight\n"
	.string "the night I lose you over it.\p"
	.string "You'll light it tomorrow.\n"
	.string "Take the boy. In.$"

Mahoganytown_Text_UBPryceMeets:
	.string "{SPEAKER NAME_PRYCE}That's the last of\n"
	.string "them. Mahogany is empty.\p"
	.string "Three nights without light.\n"
	.string "I moved every family into my\l"
	.string "Gym myself.\p"
	.string "So. You're the Champion the\n"
	.string "detective keeps promising me.\p"
	.string "I've stood in the cold for\n"
	.string "fifty years, child. I don't\l"
	.string "go inside when told.\p"
	.string "The girl says it comes at\n"
	.string "this hour. We'll see it\l"
	.string "together.$"

Mahoganytown_Text_UBLightComing:
	.string "{SPEAKER NAME_ANABEL}It's starting--\p"
	.string "…No. That is not the reading\n"
	.string "I know. That is something\l"
	.string "else.\p"
	.string "{SPEAKER NAME_PRYCE}Light. In the middle of\n"
	.string "my street.$"

Mahoganytown_Text_UBNecrozmaArrives:
	.string "{SPEAKER NAME_LOOKER}That… that is the\n"
	.string "creature from Blackthorn!\p"
	.string "{SPEAKER NAME_ANABEL}Then it is not only\n"
	.string "feeding on the rifts.\p"
	.string "It is the one opening them.\p"
	.string "{SPEAKER NAME_LILLIE}…No.\p"
	.string "No. No, not that. Not here.\p"
	.string "{SPEAKER NAME_ANABEL}Lillie?\p"
	.string "{SPEAKER NAME_LILLIE}I know that light. I\n"
	.string "know it.\p"
	.string "It has no business being\n"
	.string "anywhere near this town.\p"
	.string "…Please don't ask me. Not\n"
	.string "now.\p"
	.string "{SPEAKER NAME_PRYCE}Whatever it is, it's\n"
	.string "standing in my town.\p"
	.string "Mamoswine! Blizzard!$"

Mahoganytown_Text_UBNoEffect:
	.string "{SPEAKER NAME_PRYCE}…Nothing.\n"
	.string "Not even frost on it.\p"
	.string "Fifty years. I've never seen a\n"
	.string "Pokémon shrug off a Blizzard.\p"
	.string "{SPEAKER NAME_LOOKER}In Blackthorn it was\n"
	.string "the same. It does not fight\l"
	.string "back. It does not even look.$"

Mahoganytown_Text_UBAppear:
	.string "{SPEAKER NAME_ANABEL}Rift opening!\n"
	.string "Two signatures!\p"
	.string "…I felt that one before the\n"
	.string "readings moved.\p"
	.string "Never mind. Later.\p"
	.string "{SPEAKER NAME_LOOKER}Xurkitree!\n"
	.string "And Celesteela!$"

Mahoganytown_Text_UBSynergy:
	.string "Xurkitree drank the last glow\n"
	.string "out of the street…\p"
	.string "…and the current leapt across\n"
	.string "to Celesteela, which burned\l"
	.string "it like fuel.\p"
	.string "{SPEAKER NAME_ANABEL}Energy passing between\n"
	.string "the two signatures. Both ways.\p"
	.string "{SPEAKER NAME_LILLIE}That's it. That's what\n"
	.string "I kept seeing from the\l"
	.string "window.\p"
	.string "One drinks, the other burns.\n"
	.string "Together they never run dry.$"

Mahoganytown_Text_UBCharge:
	.string "{SPEAKER NAME_LOOKER}{PLAYER}! The heavy one!\n"
	.string "It is coming at you!$"

Mahoganytown_Text_UBSaved:
	.string "{SPEAKER NAME_LILLIE}Ninetales, Icy Wind!\n"
	.string "Keep it away from {PLAYER}!\p"
	.string "…Are you all right?\n"
	.string "Good. Good.\p"
	.string "{SPEAKER NAME_PRYCE}Hmph. That one's got a\n"
	.string "good cold in her.$"

Mahoganytown_Text_UBChoosePrompt:
	.string "{SPEAKER NAME_LILLIE}We keep them apart.\n"
	.string "Now, before they feed again.\p"
	.string "Pick one, {PLAYER}. Ninetales and\n"
	.string "I will hold the other.\p"
	.string "…I think this works. I'm not\n"
	.string "certain. I'm sorry.\p"
	.string "{SPEAKER NAME_PRYCE}And I'll watch the\n"
	.string "crystal one. For whatever\l"
	.string "good it does.$"

Mahoganytown_Text_ChoiceXurkitree:
	.string "Xurkitree$"

Mahoganytown_Text_ChoiceCelesteela:
	.string "Celesteela$"

Mahoganytown_Text_UBPickedXurkitree:
	.string "{SPEAKER NAME_LILLIE}Then the tall one is\n"
	.string "yours.\p"
	.string "Ninetales, Snow! Keep the\n"
	.string "heavy one on the ground!$"

Mahoganytown_Text_UBPickedCelesteela:
	.string "{SPEAKER NAME_LILLIE}Then the heavy one is\n"
	.string "yours.\p"
	.string "Ninetales, get between the\n"
	.string "tall one and the lines!$"

Mahoganytown_Text_UBGotAway:
	.string "{SPEAKER NAME_LOOKER}They slipped back\n"
	.string "through the tear…\p"
	.string "{SPEAKER NAME_LILLIE}It will open again.\n"
	.string "It always does.\p"
	.string "{SPEAKER NAME_LOOKER}Then we regroup,\n"
	.string "and we are ready for it.$"

Mahoganytown_Text_UBDownXurkitree:
	.string "{SPEAKER NAME_LILLIE}It's down! {PLAYER}, you\n"
	.string "did it! It's--\p"
	.string "…Wait. Celesteela!$"

Mahoganytown_Text_UBRevivedXurkitree:
	.string "Celesteela's engines roared,\n"
	.string "and the heat poured across\l"
	.string "the street into Xurkitree.\p"
	.string "Xurkitree stood up again,\n"
	.string "crackling, whole.$"

Mahoganytown_Text_UBDownCelesteela:
	.string "{SPEAKER NAME_LILLIE}It's down! {PLAYER}, you\n"
	.string "did it! It's--\p"
	.string "…Wait. Xurkitree!$"

Mahoganytown_Text_UBRevivedCelesteela:
	.string "Xurkitree's cables blazed,\n"
	.string "and the current poured across\l"
	.string "the street into Celesteela.\p"
	.string "Celesteela rose again, its\n"
	.string "engines burning, whole.$"

Mahoganytown_Text_UBLilliePlan:
	.string "{SPEAKER NAME_LOOKER}Impossible!\n"
	.string "We had it!\p"
	.string "{SPEAKER NAME_ANABEL}The loop. Whatever\n"
	.string "one loses, the other gives\l"
	.string "back.\p"
	.string "{SPEAKER NAME_PRYCE}Like melting a glacier\n"
	.string "with a match.\p"
	.string "{SPEAKER NAME_LILLIE}…I was wrong.\p"
	.string "Keeping them apart isn't\n"
	.string "enough. The current still\l"
	.string "jumps the gap between them.\p"
	.string "So we close the gap. With\n"
	.string "something it can't cross.\p"
	.string "Ice doesn't carry current.\p"
	.string "Mr. Pryce, can Mamoswine make\n"
	.string "ice? A lot of it? Right\l"
	.string "between them?\p"
	.string "{SPEAKER NAME_PRYCE}Can it make ice.\p"
	.string "…Girl, you are standing in\n"
	.string "Mahogany.\p"
	.string "{SPEAKER NAME_ANABEL}Then do it. But first,\n"
	.string "{PLAYER}. Your Pokémon.$"

Mahoganytown_Text_UBAnabelHeals:
	.string "{SPEAKER NAME_ANABEL}Hold still. Let me see\n"
	.string "them. All of them.$"

Mahoganytown_Text_UBAnabelHealed:
	.string "{SPEAKER NAME_ANABEL}There. Every one of\n"
	.string "them, ready.\p"
	.string "Now finish it.$"

Mahoganytown_Text_UBWallOrder:
	.string "{SPEAKER NAME_LILLIE}Ninetales, Aurora Veil!\n"
	.string "Right between them!\p"
	.string "{SPEAKER NAME_PRYCE}Mamoswine.\n"
	.string "Freeze it solid.$"

Mahoganytown_Text_UBWallHolds:
	.string "A wall of ice rose across the\n"
	.string "street, between Xurkitree and\l"
	.string "Celesteela.\p"
	.string "The current crackled against\n"
	.string "it… and died.\p"
	.string "{SPEAKER NAME_LILLIE}It's holding!\n"
	.string "They can't reach each other!\p"
	.string "{PLAYER}, now! This time it\n"
	.string "stays down!$"

Mahoganytown_Text_UBLillieFoughtCelesteela:
	.string "{SPEAKER NAME_LILLIE}Ninetales! …It's down.\n"
	.string "Celesteela's down too.\p"
	.string "It kept reaching for the\n"
	.string "other one. There was nothing\l"
	.string "left to reach.$"

Mahoganytown_Text_UBLillieFoughtXurkitree:
	.string "{SPEAKER NAME_LILLIE}Ninetales! …It's down.\n"
	.string "Xurkitree's down too.\p"
	.string "It kept pulling at the wall.\n"
	.string "Ice doesn't give anything\l"
	.string "back.$"

Mahoganytown_Text_UBAbsorbed:
	.string "{SPEAKER NAME_PRYCE}It's… swallowing them.\p"
	.string "{SPEAKER NAME_LOOKER}Again! Just as in\n"
	.string "Blackthorn. Both of them!\p"
	.string "{SPEAKER NAME_ANABEL}It opened the tear,\n"
	.string "let them feed for three\l"
	.string "nights…\p"
	.string "…and now it collects them.\p"
	.string "{SPEAKER NAME_LILLIE}It's feeding.\n"
	.string "The same way it did before.\p"
	.string "{SPEAKER NAME_LOOKER}Before? Mademoiselle,\n"
	.string "before WHEN?\p"
	.string "{SPEAKER NAME_LILLIE}…Later. I promise.$"

Mahoganytown_Text_UBNecrozmaSensesCosmog:
	.string "The creature is staring past\n"
	.string "you… at the Poké Ball that\l"
	.string "holds your {STR_VAR_1}.\p"
	.string "Your {STR_VAR_1} is trembling.\p"
	.string "{SPEAKER NAME_LILLIE}No! Not that one!\n"
	.string "Ninetales, stay by {PLAYER}!$"

Mahoganytown_Text_UBNecrozmaSensesLegend:
	.string "Light flares between the\n"
	.string "creature and your\l"
	.string "{STR_VAR_1}'s Poké Ball!\p"
	.string "It recoils… then steadies,\n"
	.string "and stares.\p"
	.string "Your {STR_VAR_1} doesn't look\n"
	.string "away.$"

Mahoganytown_Text_UBNecrozmaGone:
	.string "{SPEAKER NAME_PRYCE}…Gone.\p"
	.string "{SPEAKER NAME_LOOKER}And the lamps!\n"
	.string "{PLAYER}, look! The lamps are\l"
	.string "coming back on!$"

Mahoganytown_Text_UBAftermath:
	.string "{SPEAKER NAME_LOOKER}Is anyone hurt?\n"
	.string "{PLAYER}? Mademoiselle?\l"
	.string "Mr. Pryce?\p"
	.string "…Good. Then the report can\n"
	.string "wait a moment.\p"
	.string "{SPEAKER NAME_PRYCE}Hmph. I've seen more\n"
	.string "winters than the three of you\l"
	.string "put together, detective.\p"
	.string "Not one like this, though.\p"
	.string "{SPEAKER NAME_ANABEL}Two Ultra Beasts that\n"
	.string "kept each other alive. And\l"
	.string "something that came back for\l"
	.string "both of them.\p"
	.string "Twice now. That is not chance.\n"
	.string "That is a pattern.\p"
	.string "{SPEAKER NAME_LOOKER}Mademoiselle. You said\n"
	.string "you knew that light.\p"
	.string "{SPEAKER NAME_LILLIE}…I do. I saw it in\n"
	.string "Alola.\p"
	.string "I thought that was the end of\n"
	.string "it. I thought it was over.\p"
	.string "I'll tell you everything I\n"
	.string "know. Truly.\p"
	.string "Just… not in the middle of the\n"
	.string "street. Not tonight.\p"
	.string "{SPEAKER NAME_LOOKER}Then we will wait.\n"
	.string "Waiting is also detective\l"
	.string "work.$"

Mahoganytown_Text_UBAftermathCosmog:
	.string "{SPEAKER NAME_LILLIE}{PLAYER}. It looked at\n"
	.string "your {STR_VAR_1}. Only at it.\p"
	.string "Promise me you'll keep it\n"
	.string "close. Always.\p"
	.string "{SPEAKER NAME_ANABEL}In Blackthorn, and\n"
	.string "now here. It keeps finding\l"
	.string "one.\p"
	.string "I would very much like to know\n"
	.string "why.$"

Mahoganytown_Text_UBAftermathLegend:
	.string "{SPEAKER NAME_LILLIE}It backed away from\n"
	.string "your {STR_VAR_1}.\p"
	.string "I've never seen that light\n"
	.string "back away from anything.\p"
	.string "{SPEAKER NAME_ANABEL}Something made of\n"
	.string "light, afraid of a legend of\l"
	.string "the sky… That means\l"
	.string "something.$"

Mahoganytown_Text_UBPryceGoodbye:
	.string "{SPEAKER NAME_PRYCE}Champion. Mahogany owes\n"
	.string "you a night of light.\p"
	.string "And you, girl. That was clear\n"
	.string "thinking with a storm in your\l"
	.string "face. Winter would approve.\p"
	.string "I'll tell them they can go\n"
	.string "home.\p"
	.string "And Hector can light his\n"
	.string "blasted lamp.$"

Mahoganytown_Text_UBHook:
	.string "{SPEAKER NAME_ANABEL}Lillie. May I copy your\n"
	.string "notes? Your reading was better\l"
	.string "than my instruments.\p"
	.string "{SPEAKER NAME_LILLIE}You can have all of\n"
	.string "them.\p"
	.string "I'd like to stay a few more\n"
	.string "days. In case it comes back.\p"
	.string "{SPEAKER NAME_ANABEL}The readings haven't\n"
	.string "settled. It will open another\l"
	.string "rift.\p"
	.string "Where, and when, we don't know\n"
	.string "yet.\p"
	.string "{SPEAKER NAME_LOOKER}So we keep watching.\p"
	.string "Rest, {PLAYER}. Then come back\n"
	.string "to our house in Olivine.\p"
	.string "The moment something opens,\n"
	.string "you will be the first to know.\p"
	.string "{SPEAKER NAME_LILLIE}{PLAYER}…\n"
	.string "Thank you for listening.\p"
	.string "To my plan, I mean. Both of\n"
	.string "them. Even the wrong one.$"
