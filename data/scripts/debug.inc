Debug_MessageEnd:
	waitmessage
	waitbuttonpress
	releaseall
	end

Debug_ShowFieldMessageStringVar4::
	special ShowFieldMessageStringVar4
	goto Debug_MessageEnd

Debug_CheatStart::
	givemon SPECIES_MEGANIUM, 100, ITEM_NONE
	givemon SPECIES_TYPHLOSION, 100, ITEM_NONE
	givemon SPECIES_FERALIGATR, 100, ITEM_NONE
	givemon SPECIES_UMBREON, 100, ITEM_NONE
	givemon SPECIES_GLACEON, 100, ITEM_NONE
	givemon SPECIES_JOLTEON, 100, ITEM_NONE
	@setvar VAR_NEWBARKTOWN_LABSTATE, 4
	setvar VAR_NEWBARK_TOWN_STATE, 5
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RECEIVED_FIRST_BALLS
	@setflag FLAG_RANDOMIZER
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setflag FLAG_SYS_POKEDEX_GET
	setflag FLAG_HIDE_MOMS_FRIEND
	setflag FLAG_RECEIVED_FIRST_BALLS
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_RECEIVED_BADGE_5
	setflag FLAG_RECEIVED_BADGE_6
	setflag FLAG_RECEIVED_BADGE_7
	setflag FLAG_BADGE08_GET
	setflag FLAG_BADGE09_GET
	setflag FLAG_BADGE10_GET
	setflag FLAG_BADGE11_GET
	setflag FLAG_BADGE12_GET
	setflag FLAG_BADGE13_GET
	setflag FLAG_BADGE14_GET
	setflag FLAG_BADGE15_GET
	setflag FLAG_BADGE16_GET
	additem ITEM_HM_SURF
	additem ITEM_POKE_BALL, 100
	special SetUnlockedPokedexFlags
	special EnableNationalPokedex
	additem ITEM_ACRO_BIKE
	setflag FLAG_VISITED_NEWBARK_TOWN
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	setflag FLAG_VISITED_VIOLET_CITY
	setflag FLAG_VISITED_AZALEA_TOWN
	setflag FLAG_VISITED_GOLDENROD_CITY
	setflag FLAG_VISITED_ECRUTEAK_CITY
	setflag FLAG_VISITED_KITAKAMI
	setflag FLAG_VISITED_OLIVINE_CITY
	setflag FLAG_VISITED_CIANWOOD_CITY
	setflag FLAG_VISITED_SAFARI_ZONE_GATE
	setflag FLAG_VISITED_MAHOGANY_TOWN
	setflag FLAG_VISITED_LAKE_OF_RAGE
	setflag FLAG_VISITED_BLACKTHORN_CITY
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setflag FLAG_VISITED_SNOWTOP_MOUNTAIN
	setflag FLAG_VISITED_RINTO_VILLAGE
	setflag FLAG_VISITED_BATTLE_TOWER
	setflag FLAG_VISITED_CERULEAN_CITY
	setflag FLAG_VISITED_VERMILION_CITY
	setflag FLAG_VISITED_LAVENDER_TOWN
	setflag FLAG_VISITED_CELADON_CITY
	setflag FLAG_VISITED_SAFFRON_CITY
	setflag FLAG_VISITED_CINNABAR_ISLAND
	setflag FLAG_VISITED_MT_SILVER
	setflag FLAG_VISITED_RECEPTION_GATE
	setflag FLAG_VISITED_ROUTE50
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	release
	end

Debug_FlagsNotSetOverworldConfigMessage::
	message Debug_FlagsNotSetOverworldConfigMessage_Text
	goto Debug_MessageEnd

Debug_FlagsNotSetOverworldConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/overworld.h'!$"

Debug_FlagsNotSetBattleConfigMessage::
	message Debug_FlagsNotSetBattleConfigMessage_Text
	goto Debug_MessageEnd

Debug_FlagsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/battle.h'!$"

Debug_VarsNotSetBattleConfigMessage::
	message Debug_VarsNotSetBattleConfigMessage_Text
	goto Debug_MessageEnd

Debug_VarsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable var in:\l"
	.string "'include/config/battle.h'!$"

Debug_BoxFilledMessage::
	message Debug_BoxFilledMessage_Text
	goto Debug_MessageEnd

Debug_BoxFilledMessage_Text:
	.string "Storage boxes filled!$"

Debug_EventScript_CheckEVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_CheckEVs_End
	callnative Script_GetChosenMonOffensiveEVs
	msgbox Debug_EventScript_Text_OffensiveEVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveEVs
	msgbox Debug_EventScript_Text_DefensiveEVs, MSGBOX_DEFAULT
Debug_EventScript_CheckEVs_End::
	releaseall
	end

Debug_EventScript_Text_OffensiveEVs:
	.string "ATK EVs: {STR_VAR_1}, SPATK EVs: {STR_VAR_2}, SPEED EVs: {STR_VAR_3}$"

Debug_EventScript_Text_DefensiveEVs:
	.string "HP EVs: {STR_VAR_1}, DEF EVs: {STR_VAR_2}, SPDEF EVs: {STR_VAR_3}$"

Debug_EventScript_CheckIVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_CheckIVs_End
	callnative Script_GetChosenMonOffensiveIVs
	msgbox Debug_EventScript_Text_OffensiveIVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveIVs
	msgbox Debug_EventScript_Text_DefensiveIVs, MSGBOX_DEFAULT
Debug_EventScript_CheckIVs_End::
	releaseall
	end

Debug_EventScript_Text_OffensiveIVs:
	.string "ATK IVs: {STR_VAR_1}, SPATK IVs: {STR_VAR_2}, SPEED IVs: {STR_VAR_3}$"

Debug_EventScript_Text_DefensiveIVs:
	.string "HP IVs: {STR_VAR_1}, DEF IVs: {STR_VAR_2}, SPDEF IVs: {STR_VAR_3}$"

@ ============================================================================
@ QUICK PARTY SETUP FOR LEVEL SCALING TESTS
@ ============================================================================

Debug_EventScript_HiddenGrottoTestCurrentMonBounds::
	special HiddenGrotto_TestCurrentMonBounds
	goto_if_eq VAR_RESULT, 0xFFFF, Debug_EventScript_HiddenGrottoTestCurrentMonBounds_NoCurrent
	buffernumberstring STR_VAR_1, VAR_RESULT
	buffernumberstring STR_VAR_2, VAR_0x8005
	buffernumberstring STR_VAR_3, VAR_0x8006
	msgbox Debug_EventScript_Text_HiddenGrottoTestCurrentMonBounds, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_HiddenGrottoTestCurrentMonBounds_NoCurrent:
	msgbox Debug_EventScript_Text_HiddenGrottoTestCurrentMonBounds_NoCurrent, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_Text_HiddenGrottoTestCurrentMonBounds:
	.string "Hidden Grotto bounds test done.\p"
	.string "Invalid: {STR_VAR_1}\n"
	.string "Min species: {STR_VAR_2}\n"
	.string "Max species: {STR_VAR_3}$"

Debug_EventScript_Text_HiddenGrottoTestCurrentMonBounds_NoCurrent:
	.string "No current Hidden Grotto for this map.$"

Debug_EventScript_Script_1::
	special GameClear
	waitstate
	release
	end

Debug_LevelScaling_PartySetup_Intro:
	.string "LEVEL SCALING TEST SETUP\p"
	.string "Creating test party with:\n"
	.string "Level 10, 20, 30, 40, 50, 60\p"
	.string "All with perfect IVs and competitive\n"
	.string "movesets. Setting all 8 badges.$"

Debug_LevelScaling_PartySetup_Complete:
	.string "Party created!\p"
	.string "Party Average: 35\n"
	.string "Lowest: 10, Highest: 60\n"
	.string "Level Cap: 70 (8 badges)\p"
	.string "Now run Scripts 2-7 to test scaling!$"

Debug_EventScript_Script_2::
	msgbox Debug_LevelScaling_Test1_Intro, MSGBOX_DEFAULT
	msgbox Debug_LevelScaling_Test1_Result, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_Script_3::
	msgbox Debug_LevelScaling_Test2_Intro, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_Script_4::
	msgbox Debug_LevelScaling_Test3_Intro, MSGBOX_DEFAULT
	msgbox Debug_LevelScaling_Test3_Result, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_Script_5::
	msgbox Debug_LevelScaling_Test4_Intro, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_Script_6::
	msgbox Debug_LevelScaling_Test5_Intro, MSGBOX_DEFAULT
	msgbox Debug_LevelScaling_Test5_Result, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_Script_7::
	msgbox Debug_LevelScaling_Test6_Intro, MSGBOX_DEFAULT
	msgbox Debug_LevelScaling_Test6_Result, MSGBOX_DEFAULT
	release
	end

Debug_LevelScaling_Defeated:
	.string "Defeated!$"

@ Test 1: Scale to Level Cap
Debug_LevelScaling_Test1_Intro:
	.string "LEVEL SCALING TEST 1\n"
	.string "Mode: SCALE TO LEVEL CAP\p"
	.string "Expected: All Pokémon should be\n"
	.string "at the current level cap.\p"
	.string "Check your current cap with badges.$"

Debug_LevelScaling_Test1_Result:
	.string "Did all enemy Pokémon match the\n"
	.string "level cap? Check their levels!$"

@ Test 2: Scale to Party Average + 3
Debug_LevelScaling_Test2_Intro:
	.string "LEVEL SCALING TEST 2\n"
	.string "Mode: PARTY AVERAGE + 3\p"
	.string "Expected: Enemy Pokémon should be\n"
	.string "3 levels above your party average.\p"
	.string "Excludes fainted Pokémon.$"

Debug_LevelScaling_Test2_Result:
	.string "Calculate your party average.\n"
	.string "Were enemies that +3?$"

@ Test 3: Scale to Party Highest (with variation)
Debug_LevelScaling_Test3_Intro:
	.string "LEVEL SCALING TEST 3\n"
	.string "Mode: PARTY HIGHEST +/- 2\p"
	.string "Expected: Enemy Pokémon at your\n"
	.string "highest level, +/- 2 random variation.\p"
	.string "Levels will vary between enemies.$"

Debug_LevelScaling_Test3_Result:
	.string "Were enemies within 2 levels of\n"
	.string "your highest Pokémon?$"

@ Test 4: Scale to Party Lowest + 5
Debug_LevelScaling_Test4_Intro:
	.string "LEVEL SCALING TEST 4\n"
	.string "Mode: PARTY LOWEST + 5\p"
	.string "Expected: Enemy Pokémon should be\n"
	.string "5 levels above your lowest level.$"

Debug_LevelScaling_Test4_Result:
	.string "Check your lowest level Pokémon.\n"
	.string "Were enemies that +5?$"

@ Test 5: Scale to Party/PC Highest + 2 (variation 3, min 25, max 50)
Debug_LevelScaling_Test5_Intro:
	.string "LEVEL SCALING TEST 5\n"
	.string "Mode: PARTY/PC HIGHEST + 2\p"
	.string "Expected: Checks party AND PC.\n"
	.string "Adds 2, varies by 3, min 25, max 50.\p"
	.string "Try with high-level Pokémon in PC!$"

Debug_LevelScaling_Test5_Result:
	.string "Were levels clamped to 25-50 range?\n"
	.string "Did it check your PC box Pokémon?$"

@ Test 6: Evolution Management Test
Debug_LevelScaling_Test6_Intro:
	.string "LEVEL SCALING TEST 6\n"
	.string "Mode: EVOLUTION MANAGEMENT\p"
	.string "Expected: Scales to level cap - 20.\n"
	.string "Evolved Pokémon should devolve if\n"
	.string "they can't legally be at that level.\p"
	.string "Example: Dragonite at 30 = Dratini.$"

Debug_LevelScaling_Test6_Result:
	.string "Did you see any pre-evolutions?\n"
	.string "That means it worked correctly!$"


Debug_EventScript_Script_8::
	release
	end

@ ---------------------------------------------------------------------------
@ SoulGold: Rift Missions > Looker's call (src/debug.c, "Rift Missions…").
@ The briefing in OlivineCity_House1 only happens once FLAG_RIFT_LOOKER_SUMMONS
@ is set, and the call (RiftMissions_EventScript_LookerCall) sets it together
@ with FLAG_DAILY_LOOKER_CALL. Only states 4/6/8/10 have a call.
@ ---------------------------------------------------------------------------
@ The same two flags the call sets, without the call: go to Olivine.
Debug_EventScript_RiftLookerCalled::
	lockall
	call Debug_EventScript_RiftCheckState
	setflag FLAG_DAILY_LOOKER_CALL
	setflag FLAG_RIFT_LOOKER_SUMMONS
	msgbox Debug_Text_RiftLookerCalled, MSGBOX_DEFAULT
	releaseall
	end

@ The real call, right now (it sets both flags itself).
Debug_EventScript_RiftLookerCallNow::
	lockall
	call Debug_EventScript_RiftCheckState
	releaseall
	goto RiftMissions_EventScript_LookerCall

@ Undo: no call made today and no invitation pending. The next step outside
@ the house rings again (in states 4/6/8/10).
Debug_EventScript_RiftLookerReset::
	lockall
	clearflag FLAG_DAILY_LOOKER_CALL
	clearflag FLAG_RIFT_LOOKER_SUMMONS
	msgbox Debug_Text_RiftLookerReset, MSGBOX_DEFAULT
	releaseall
	end

@ Out of 4/6/8/10 there is nothing to call about: say so and stop.
Debug_EventScript_RiftCheckState::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 4, Debug_EventScript_RiftStateOk
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 6, Debug_EventScript_RiftStateOk
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 8, Debug_EventScript_RiftStateOk
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, Debug_EventScript_RiftStateOk
	buffernumberstring STR_VAR_1, VAR_RIFT_MISSIONS_STATE
	msgbox Debug_Text_RiftNoCall, MSGBOX_DEFAULT
	releaseall
	end
Debug_EventScript_RiftStateOk::
	return

Debug_Text_RiftLookerCalled:
	.string "Looker's call marked as made.\n"
	.string "The briefing in Olivine is open.$"

Debug_Text_RiftLookerReset:
	.string "Today's call and the invitation\n"
	.string "were cleared.$"

Debug_Text_RiftNoCall:
	.string "Rift state is {STR_VAR_1}. Looker only\n"
	.string "calls in states 4, 6, 8 and 10.$"

Debug_CheckSaveBlock::
	callnative CheckSaveBlock1Size
	msgbox Debug_SaveBlock1Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock2Size
	msgbox Debug_SaveBlock2Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock3Size
	msgbox Debug_SaveBlock3Size, MSGBOX_DEFAULT
	callnative CheckPokemonStorageSize
	msgbox Debug_PokemonStorageSize, MSGBOX_DEFAULT
	release
	end

Debug_SaveBlock1Size::
	.string "SaveBlock1 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_SaveBlock2Size::
	.string "SaveBlock2 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_SaveBlock3Size::
	.string "SaveBlock3 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_PokemonStorageSize::
	.string "{PKMN}Storage size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_CheckROMSpace::
	callnative CheckROMSize
	msgbox Debug_ROMSize, MSGBOX_DEFAULT
	release
	end

Debug_ROMSize::
	.string "ROM size: {STR_VAR_1}MB/32MB.\n"
	.string "Free space: {STR_VAR_2}MB.$"

Debug_HatchAnEgg::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_HatchAnEgg_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_ne VAR_RESULT, SPECIES_EGG, DebugScript_HatchAnEgg_CantForceHatch
	special EggHatch
	waitstate
Debug_HatchAnEgg_End::
	releaseall
	end

Debug_NoPokemon::
	msgbox DebugScript_Text_EmptyParty, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_HatchAnEgg_CantForceHatch::
	msgbox DebugScript_HatchAnEgg_Text_NotAnEgg, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_Text_EmptyParty::
	.string "You have no Pokémon nor Eggs.$"

DebugScript_HatchAnEgg_Text_NotAnEgg::
	.string "That's not a Pokémon Egg.$"

DebugScript_ZeroDaycareMons::
	msgbox DebugText_DaycareNoPokemon, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_OneDaycareMons::
	msgbox DebugText_DaycareOnePokemon, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_DaycareMonsNotCompatible::
	msgbox DebugText_DaycarePokemonNotCompatible, MSGBOX_DEFAULT
	releaseall
	end

DebugText_DaycareNoPokemon:
	.string "You have no Pokémon at Daycare.$"

DebugText_DaycareOnePokemon:
	.string "You have only one Pokémon at Daycare.$"

DebugText_DaycarePokemonNotCompatible:
	.string "Your Pokémon at Daycare can't\nhave babies together!$"

Debug_ShowExpansionVersion::
	callnative BufferExpansionVersion
	msgbox Debug_ExpansionVersion, MSGBOX_DEFAULT
	release
	end

Debug_ExpansionVersion:
	.string "pokeemerald-expansion {STR_VAR_1}$"

Debug_Follower_NPC_Not_Enabled::
	msgbox Debug_Enable_To_Use_Follower_NPCs, MSGBOX_DEFAULT
	release
	end

Debug_Enable_To_Use_Follower_NPCs:
	.string "Feature unavailable.\nSet FNPC_ENABLE_NPC_FOLLOWERS to\lTRUE in 'include/config/follower_npc.h'.$"

Debug_Follower_NPC_Event_Script::
	lock
	facefollowernpc
	msgbox Debug_Follower_NPC_Test_Message, MSGBOX_DEFAULT
	releaseall
	end

Debug_Follower_NPC_Test_Message:
	.string "This is a Follower NPC test.$"

Debug_EventScript_Steven_Multi::
	call MossdeepCity_SpaceCenter_2F_EventScript_ChoosePartyForMultiBattle
	release
	end

Debug_EventScript_WallyTutorial::
	special SavePlayerParty
	special LoadWallyZigzagoon
	special StartWallyTutorialBattle
	waitstate
	special LoadPlayerParty
	release
	end

Debug_BerryPestsDisabled::
	msgbox DebugText_BerryPestsDisabled, MSGBOX_DEFAULT
	release
	end

DebugText_BerryPestsDisabled:
	.string "OW_BERRY_PESTS is disabled.\n"
	.string "Unable to force pests onto berry trees.$"

Debug_BerryWeedsDisabled::
	msgbox DebugText_BerryWeedsDisabled, MSGBOX_DEFAULT
	release
	end

DebugText_BerryWeedsDisabled:
	.string "OW_BERRY_WEEDS is disabled.\n"
	.string "Unable to force weeds onto berry trees.$"

Debug_EventScript_InflictStatus1::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	dynmultipush Debug_EventScript_InflictStatus1_Text_Single, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_PartyWide, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Single
	case 1, Debug_EventScript_InflictStatus1_Party
	case 2, Debug_EventScript_InflictStatus1_Close
Debug_EventScript_InflictStatus1_Close:
	releaseall
	end

Debug_EventScript_InflictStatus1_Single:
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	dynmultipush Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Single_Poison
	case 1, Debug_EventScript_InflictStatus1_Single_Paralysis
	case 2, Debug_EventScript_InflictStatus1_Single_Sleep
	case 3, Debug_EventScript_InflictStatus1_Single_Burn
	case 4, Debug_EventScript_InflictStatus1_Single_Freeze
	case 5, Debug_EventScript_InflictStatus1_Single_Frostbite
	case 6, Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	releaseall
	end

Debug_EventScript_KoPokemon::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	setko VAR_0x8004
	releaseall
	end

Debug_EventScript_SetHiddenNature::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	dynmultipush Debug_EventScript_ChangeNature_Text_Hardy, 0
	dynmultipush Debug_EventScript_ChangeNature_Text_Lonely, 1
	dynmultipush Debug_EventScript_ChangeNature_Text_Brave, 2
	dynmultipush Debug_EventScript_ChangeNature_Text_Adamant, 3
	dynmultipush Debug_EventScript_ChangeNature_Text_Naughty, 4
	dynmultipush Debug_EventScript_ChangeNature_Text_Bold, 5
	dynmultipush Debug_EventScript_ChangeNature_Text_Docile, 6
	dynmultipush Debug_EventScript_ChangeNature_Text_Relaxed, 7
	dynmultipush Debug_EventScript_ChangeNature_Text_Impish, 8
	dynmultipush Debug_EventScript_ChangeNature_Text_Lax, 9
	dynmultipush Debug_EventScript_ChangeNature_Text_Timid, 10
	dynmultipush Debug_EventScript_ChangeNature_Text_Hasty, 11
	dynmultipush Debug_EventScript_ChangeNature_Text_Serious, 12
	dynmultipush Debug_EventScript_ChangeNature_Text_Jolly, 13
	dynmultipush Debug_EventScript_ChangeNature_Text_Naive, 14
	dynmultipush Debug_EventScript_ChangeNature_Text_Modest, 15
	dynmultipush Debug_EventScript_ChangeNature_Text_Mild, 16
	dynmultipush Debug_EventScript_ChangeNature_Text_Quiet, 17
	dynmultipush Debug_EventScript_ChangeNature_Text_Bashful, 18
	dynmultipush Debug_EventScript_ChangeNature_Text_Rash, 19
	dynmultipush Debug_EventScript_ChangeNature_Text_Calm, 20
	dynmultipush Debug_EventScript_ChangeNature_Text_Gentle, 21
	dynmultipush Debug_EventScript_ChangeNature_Text_Sassy, 22
	dynmultipush Debug_EventScript_ChangeNature_Text_Careful, 23
	dynmultipush Debug_EventScript_ChangeNature_Text_Quirky, 24
	dynmultistack 0, 0, TRUE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	special SetHiddenNature
	releaseall
	end

Debug_EventScript_SetAbility::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_GetAbilityNames
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, Debug_EventScript_SetAbilityClose
	special SetAbility
Debug_EventScript_SetAbilityClose:
	releaseall
	end

Debug_EventScript_SetFriendship::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_Party_SetFriendship
	releaseall
	end

Debug_EventScript_GivePokerus::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_Party_SetPokerus
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Poison:
	setstatus1 STATUS1_POISON, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Paralysis:
	setstatus1 STATUS1_PARALYSIS, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Sleep:
	setstatus1 STATUS1_SLEEP, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Burn:
	setstatus1 STATUS1_BURN, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Freeze:
	setstatus1 STATUS1_FREEZE, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Frostbite:
	setstatus1 STATUS1_FROSTBITE, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Party:
	dynmultipush Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Party_Poison
	case 1, Debug_EventScript_InflictStatus1_Party_Paralysis
	case 2, Debug_EventScript_InflictStatus1_Party_Sleep
	case 3, Debug_EventScript_InflictStatus1_Party_Burn
	case 4, Debug_EventScript_InflictStatus1_Party_Freeze
	case 5, Debug_EventScript_InflictStatus1_Party_Frostbite
	case 6, Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Poison:
	setstatus1 STATUS1_POISON, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Paralysis:
	setstatus1 STATUS1_PARALYSIS, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Sleep:
	setstatus1 STATUS1_SLEEP, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Burn:
	setstatus1 STATUS1_BURN, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Freeze:
	setstatus1 STATUS1_FREEZE, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Frostbite:
	setstatus1 STATUS1_FROSTBITE, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Text_Single:
	.string "Single$"

Debug_EventScript_InflictStatus1_Text_PartyWide:
	.string "Party-wide$"

Debug_EventScript_InflictStatus1_Text_Close:
	.string "Close$"

Debug_EventScript_InflictStatus1_Text_Poison:
	.string "Poison$"

Debug_EventScript_InflictStatus1_Text_Paralysis:
	.string "Paralysis$"

Debug_EventScript_InflictStatus1_Text_Sleep:
	.string "Sleep$"

Debug_EventScript_InflictStatus1_Text_Burn:
	.string "Burn$"

Debug_EventScript_InflictStatus1_Text_Freeze:
	.string "Freeze$"

Debug_EventScript_InflictStatus1_Text_Frostbite:
	.string "Frostbite$"

Debug_EventScript_InflictStatus1_Text_KO:
	.string "KO$"

Debug_EventScript_ChangeNature_Text_Hardy:
	.string "Hardy$"
Debug_EventScript_ChangeNature_Text_Lonely:
	.string "Lonely$"
Debug_EventScript_ChangeNature_Text_Brave:
	.string "Brave$"
Debug_EventScript_ChangeNature_Text_Adamant:
	.string "Adamant$"
Debug_EventScript_ChangeNature_Text_Naughty:
	.string "Naughty$"
Debug_EventScript_ChangeNature_Text_Bold:
	.string "Bold$"
Debug_EventScript_ChangeNature_Text_Docile:
	.string "Docile$"
Debug_EventScript_ChangeNature_Text_Relaxed:
	.string "Relaxed$"
Debug_EventScript_ChangeNature_Text_Impish:
	.string "Impish$"
Debug_EventScript_ChangeNature_Text_Lax:
	.string "Lax$"
Debug_EventScript_ChangeNature_Text_Timid:
	.string "Timid$"
Debug_EventScript_ChangeNature_Text_Hasty:
	.string "Hasty$"
Debug_EventScript_ChangeNature_Text_Serious:
	.string "Serious$"
Debug_EventScript_ChangeNature_Text_Jolly:
	.string "Jolly$"
Debug_EventScript_ChangeNature_Text_Naive:
	.string "Naive$"
Debug_EventScript_ChangeNature_Text_Modest:
	.string "Modest$"
Debug_EventScript_ChangeNature_Text_Mild:
	.string "Mild$"
Debug_EventScript_ChangeNature_Text_Quiet:
	.string "Quiet$"
Debug_EventScript_ChangeNature_Text_Bashful:
	.string "Bashful$"
Debug_EventScript_ChangeNature_Text_Rash:
	.string "Rash$"
Debug_EventScript_ChangeNature_Text_Calm:
	.string "Calm$"
Debug_EventScript_ChangeNature_Text_Gentle:
	.string "Gentle$"
Debug_EventScript_ChangeNature_Text_Sassy:
	.string "Sassy$"
Debug_EventScript_ChangeNature_Text_Careful:
	.string "Careful$"
Debug_EventScript_ChangeNature_Text_Quirky:
	.string "Quirky$"

Debug_EventScript_EWRAMCounters::
	callnative CheckEWRAMCounters
	msgbox Debug_EventScript_EWRAMCounters_Text, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_EWRAMCounters_Text::
	.string "Follower Steps: {STR_VAR_1}.\n"
	.string "Fishing Chain: {STR_VAR_2}.$"

Debug_EventScript_FontTest_Text_1::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Angel Adept Blind Bodice Clique\n"
	.string "Coast Dunce Docile Enact Eosin\l"
	.string "Furlong Focal Gnome Gondola Human\l"
	.string "Hoist Inlet Iodine Justin Jocose\l"
	.string "Knoll Koala Linden Loads Milliner\l"
	.string "Modal Number Nodule Onset Oddball\l"
	.string "Pneumo Poncho Quanta Qophs Rhone\l"
	.string "Roman Snout Sodium Tundra Tocsin\l"
	.string "Uncle Udder Vulcan Vocal Whale\l"
	.string "Woman Xmas Xenon Yunnan Young\l"
	.string "Zloty Zodiac.$"

Debug_EventScript_FontTest_Text_2::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Angel angel adept for the nuance loads\n"
	.string "of the arena cocoa and quaalude. Blind\l"
	.string "blind bodice for the submit oboe of the\l"
	.string "club snob and abbot. Clique clique\l"
	.string "coast for the pouch loco of the franc\l"
	.string "assoc and accede. Dunce dunce docile\l"
	.string "for the loudness mastodon of the\l"
	.string "loud statehood and huddle.$"

Debug_EventScript_FontTest_Text_3::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Enact enact eosin for the quench coed\n"
	.string "of the pique canoe and bleep. Furlong\l"
	.string "furlong focal for the genuflect\l"
	.string "profound of the motif aloof and offers.\l"
	.string "Gnome gnome gondola for the impugn\l"
	.string "logos of the unplug analog and smuggle.\l"
	.string "Human human hoist for the buddhist\l"
	.string "alcohol of the riyadh caliph and\l"
	.string "bathhouse.$"

Debug_EventScript_FontTest_Text_4::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Inlet inlet iodine for the quince\n"
	.string "champion of the ennui scampi and shiite.\l"
	.string "Justin justin jocose for the djibouti\l"
	.string "sojourn of the oranj raj and hajjis.\l"
	.string "Knoll knoll koala for the banknote\l"
	.string "lookout of the dybbuk outlook and\l"
	.string "trekked. Linden linden loads for the\l"
	.string "ulna monolog of the consul menthol and\l"
	.string "shallot.$"

Debug_EventScript_FontTest_Text_5::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Milliner milliner modal for the alumna\n"
	.string "solomon of the album custom and summon.\l"
	.string "Number number nodule for the unmade\l"
	.string "economic of the shotgun bison and\l"
	.string "tunnel. Onset onset oddball for the\l"
	.string "abandon podium of the antiquo tempo\l"
	.string "and moonlit. Pneumo pneumo poncho for\l"
	.string "the dauphin opossum of the holdup\l"
	.string "bishop and supplies.$"

Debug_EventScript_FontTest_Text_6::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Quanta quanta qophs for the inquest\n"
	.string "sheqel of the cinq coq and suqqu. Rhone\l"
	.string "rhone roman for the burnt porous of the\l"
	.string "lemur clamor and carrot. Snout snout\l"
	.string "sodium for the ensnare bosom of the\l"
	.string "genus pathos and missing. Tundra\l"
	.string "tundra tocsin for the nutmeg isotope\l"
	.string "of the peasant ingot and ottoman.$"

Debug_EventScript_FontTest_Text_7::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Uncle uncle udder for the dunes cloud\n"
	.string "of the hindu thou and continuum. Vulcan\l"
	.string "vulcan vocal for the alluvial ovoid of\l"
	.string "the yugoslav chekhov and revved. Whale\l"
	.string "whale woman for the meanwhile blowout\l"
	.string "of the forepaw meadow and glowworm.\l"
	.string "Xmas xmas xenon for the bauxite\l"
	.string "doxology of the tableaux equinox and\l"
	.string "exxon.$"

Debug_EventScript_FontTest_Text_8::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Yunnan yunnan young for the dynamo\n"
	.string "coyote of the obloquy employ and\l"
	.string "sayyid. Zloty zloty zodiac for the gizmo\l"
	.string "ozone of the franz laissez and buzzing.$"


Debug_EventScript_FontTest_Text_9::                 @ Special thanks to Nintendo for this nice pangram to test other glyphs
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "42 × 138 = 5796.\n"
	.string "Mr Jock, TV quiz PhD: bags 20% fewer\l"
	.string "lynx at a café; voilà, they're “worth”\l"
	.string "♂1/♀1 = ¥1. That's 10 + 9 - 8 = 11\l"
	.string "Nintendo GBA can connect to a Nintendo\l"
	.string "GameCube console! He claimed-though I don't\l"
	.string "believe him-to have done so in an eyes-shut\l"
	.string "state…?$"

Debug_PrintFontTest::
	msgbox Debug_EventScript_FontTest_Text_1, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_2, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_3, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_4, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_5, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_6, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_7, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_8, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_9, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_FontTest::
	lockall
	goto Debug_PrintFontTest
@	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
@	dynmultipush Debug_EventScript_InflictStatus1_Text_Single, 0
@	dynmultipush Debug_EventScript_InflictStatus1_Text_PartyWide, 1
@	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 2
@	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
@	switch VAR_RESULT
@	case 0, Debug_EventScript_InflictStatus1_Single
@	case 1, Debug_EventScript_InflictStatus1_Party
@	case 2, Debug_EventScript_InflictStatus1_Close
@Debug_EventScript_InflictStatus1_Close:
@	releaseall
@	end

Debug_EventScript_TellTheTime::
	callnative DebugMenu_CalculateTime
	msgbox Debug_EventScript_TellTheTime_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

Debug_EventScript_PrintTimeOfDay::
	callnative DebugMenu_CalculateTimeOfDay
	msgbox DebugEventScript_PrintWeekday_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

Debug_EventScript_FakeRTCNotEnabled::
	msgbox Debug_EventScript_FakeRTCNotEnabled_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	return

Debug_EventScript_FakeRTCNotEnabled_Text_0:
	.string "You currently do not have Fake RTC\nenabled. Please enable it in include/\lconfig/overworld.h$"


Debug_EventScript_TellTheTime_Text_0:
	.string "Time and date:\n"
	.string "{STR_VAR_1}, {STR_VAR_2}:{STR_VAR_3}$"

DebugEventScript_PrintWeekday_Text_0:
	.string "Time of day: {STR_VAR_1}$"

@ SoulGold: Rift Missions > Nexus fights (src/debug.c). There is no Nexus map yet;
@ these run the fights of data/scripts/nexus.inc from anywhere. YES = the champion
@ version (lines about the legendary), NO = the generic version of the rooms.
Debug_EventScript_NexusColress::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusColressChampion
	call Nexus_EventScript_Colress_Fight
	releaseall
	end

Debug_EventScript_NexusColressChampion::
	call Nexus_EventScript_Colress_ChampionFight
	releaseall
	end

Debug_EventScript_NexusBruno::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusBrunoChampion
	call Nexus_EventScript_Bruno_Fight
	releaseall
	end

Debug_EventScript_NexusBrunoChampion::
	call Nexus_EventScript_Bruno_ChampionFight
	releaseall
	end

Debug_EventScript_NexusElesa::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusElesaChampion
	call Nexus_EventScript_Elesa_Fight
	releaseall
	end

Debug_EventScript_NexusElesaChampion::
	call Nexus_EventScript_Elesa_ChampionFight
	releaseall
	end

Debug_EventScript_NexusVolkner::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusVolknerChampion
	call Nexus_EventScript_Volkner_Fight
	releaseall
	end

Debug_EventScript_NexusVolknerChampion::
	call Nexus_EventScript_Volkner_ChampionFight
	releaseall
	end

Debug_EventScript_NexusSteven::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusStevenChampion
	call Nexus_EventScript_Steven_Fight
	releaseall
	end

Debug_EventScript_NexusStevenChampion::
	call Nexus_EventScript_Steven_ChampionFight
	releaseall
	end

Debug_EventScript_NexusRamos::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusRamosChampion
	call Nexus_EventScript_Ramos_Fight
	releaseall
	end

Debug_EventScript_NexusRamosChampion::
	call Nexus_EventScript_Ramos_ChampionFight
	releaseall
	end

Debug_EventScript_NexusGuzma::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusGuzmaChampion
	call Nexus_EventScript_Guzma_Fight
	releaseall
	end

Debug_EventScript_NexusGuzmaChampion::
	call Nexus_EventScript_Guzma_ChampionFight
	releaseall
	end

Debug_EventScript_NexusSoliera::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusSolieraChampion
	call Nexus_EventScript_Soliera_Fight
	releaseall
	end

Debug_EventScript_NexusSolieraChampion::
	call Nexus_EventScript_Soliera_ChampionFight
	releaseall
	end

Debug_EventScript_NexusByron::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusByronChampion
	call Nexus_EventScript_Byron_Fight
	releaseall
	end

Debug_EventScript_NexusByronChampion::
	call Nexus_EventScript_Byron_ChampionFight
	releaseall
	end

Debug_EventScript_NexusFantina::
	lockall
	msgbox Debug_Text_NexusChampion, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Debug_EventScript_NexusFantinaChampion
	call Nexus_EventScript_Fantina_Fight
	releaseall
	end

Debug_EventScript_NexusFantinaChampion::
	call Nexus_EventScript_Fantina_ChampionFight
	releaseall
	end

@ Nexus loop (data/maps/Nexus): straight into room 1 from anywhere, skipping
@ the altar and its R10 check; and a new day - fresh state and a new draw.
Debug_EventScript_NexusEnter::
	special Nexus_EnterFromAltar
	fadescreen FADE_TO_BLACK
	warpsilent MAP_NEXUS, 10, 19
	waitstate
	end

Debug_EventScript_NexusNewDay::
	lockall
	special Nexus_DebugNewDay
	msgbox Debug_Text_NexusNewDay, MSGBOX_DEFAULT
	releaseall
	end

Debug_Text_NexusNewDay:
	.string "Nexus: new day, new draw.$"

Debug_Text_NexusChampion:
	.string "Fight as the legendary's champion?$"

@ ===========================================================================
@ Berry Master (Route 30 garden) - test helpers. Menu in src/debug.c
@ (sDebugMenu_Actions_BerryMaster); rules in src/berry_garden.c (BerryDebug_*).
@ Everything here changes the save the way the game would, then says what it
@ did. Anything the map shows (time of day, bed B, the trees) comes back with
@ a reload on the spot: Debug_EventScript_BerryReload.
@ ===========================================================================

Debug_EventScript_BerryReload::
	fadescreen FADE_TO_BLACK
	special BerryDebug_ReloadMap
	waitstate
	end

@ --- Where ---------------------------------------------------------------
Debug_EventScript_BerryGoGarden::
	fadescreen FADE_TO_BLACK
	warp MAP_ROUTE30, 27, 45
	waitstate
	end

Debug_EventScript_BerryGoHouse::
	fadescreen FADE_TO_BLACK
	warp MAP_ROUTE30_HOUSE, 0
	waitstate
	end

@ --- When (the real clock's offset, forward only) -------------------------
Debug_EventScript_BerryPlus1Hour::
	lockall
	setvar VAR_0x8004, 1
	goto Debug_EventScript_BerryAdvance

Debug_EventScript_BerryPlus6Hours::
	lockall
	setvar VAR_0x8004, 6
	goto Debug_EventScript_BerryAdvance

Debug_EventScript_BerryPlus24Hours::
	lockall
	setvar VAR_0x8004, 24
	goto Debug_EventScript_BerryAdvance

Debug_EventScript_BerryAdvance::
	special BerryDebug_AdvanceHours
	buffernumberstring STR_VAR_1, VAR_0x8004
	msgbox Debug_Text_BerryAdvanced, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

Debug_EventScript_BerryNextMorning::
	lockall
	special BerryDebug_AdvanceToMorning
	msgbox Debug_Text_BerryNextMorning, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

Debug_EventScript_BerryNewGardenDay::
	lockall
	special BerryDebug_ResetToday
	msgbox Debug_Text_BerryNewGardenDay, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

@ --- The Book --------------------------------------------------------------
Debug_EventScript_BerryBook8::
	setvar VAR_0x8004, 8
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook11::
	setvar VAR_0x8004, 11
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook12::
	setvar VAR_0x8004, 12
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook22::
	setvar VAR_0x8004, 22
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook32::
	setvar VAR_0x8004, 32
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook60::
	setvar VAR_0x8004, 60
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook66::
	setvar VAR_0x8004, 66
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerryBook67::
	setvar VAR_0x8004, 67
	goto Debug_EventScript_BerrySetBook

Debug_EventScript_BerrySetBook::
	lockall
	special BerryDebug_SetBook
	specialvar VAR_RESULT, BerryLedger_Count
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Debug_Text_BerryBookSet, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryMilestonesUnpaid::
	lockall
	setvar VAR_BERRY_LEDGER_MILESTONE, 0
	msgbox Debug_Text_BerryMilestonesUnpaid, MSGBOX_DEFAULT
	releaseall
	end

@ --- Garden ------------------------------------------------------------------
Debug_EventScript_BerryLevel1::
	setvar VAR_0x8004, GARDEN_LEVEL_BACKYARD
	goto Debug_EventScript_BerrySetLevel

Debug_EventScript_BerryLevel2::
	setvar VAR_0x8004, GARDEN_LEVEL_PROPER
	goto Debug_EventScript_BerrySetLevel

Debug_EventScript_BerryLevel3::
	setvar VAR_0x8004, GARDEN_LEVEL_CHANNEL
	goto Debug_EventScript_BerrySetLevel

Debug_EventScript_BerryLevel4::
	setvar VAR_0x8004, GARDEN_LEVEL_BUG_HOTEL
	goto Debug_EventScript_BerrySetLevel

Debug_EventScript_BerrySetLevel::
	lockall
	special BerryDebug_SetLevel
	buffernumberstring STR_VAR_1, VAR_0x8004
	msgbox Debug_Text_BerryLevelSet, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

@ Hearts (part 9): 0 = only lines 1-4, 5 = up to 7, 12 or 15 = all 10.
Debug_EventScript_BerryHearts0::
	setvar VAR_0x8004, 0
	goto Debug_EventScript_BerrySetHearts

Debug_EventScript_BerryHearts5::
	setvar VAR_0x8004, GARDEN_HEARTS_TIER1_DAYS
	goto Debug_EventScript_BerrySetHearts

Debug_EventScript_BerryHearts12::
	setvar VAR_0x8004, GARDEN_HEARTS_TIER2_DAYS
	goto Debug_EventScript_BerrySetHearts

Debug_EventScript_BerryHearts15::
	setvar VAR_0x8004, GARDEN_HEARTS_MAX
Debug_EventScript_BerrySetHearts::
	lockall
	special BerryDebug_SetHearts
	buffernumberstring STR_VAR_1, VAR_0x8004
	msgbox Debug_Text_BerryHeartsSet, MSGBOX_DEFAULT
	releaseall
	end

@ Klara (part 11): today is a raid morning; she shows up on the next load of
@ Route30 if it is morning and a garden plot is ripe.
Debug_EventScript_BerryKlara::
	lockall
	special BerryDebug_KlaraComes
	msgbox Debug_Text_BerryKlara, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

Debug_EventScript_BerryRipen::
	lockall
	special BerryDebug_RipenGarden
	msgbox Debug_Text_BerryRipened, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

Debug_EventScript_BerryGrow::
	lockall
	special BerryDebug_GrowGarden
	msgbox Debug_Text_BerryGrown, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

Debug_EventScript_BerryEmpty::
	lockall
	special BerryDebug_EmptyGarden
	msgbox Debug_Text_BerryEmptied, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

@ --- Story and money ---------------------------------------------------------
Debug_EventScript_BerryToggleAct1::
	lockall
	goto_if_ge VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE, Debug_EventScript_BerryAct1Off
	setvar VAR_HARVEST_KING, HARVEST_KING_ACT1_DONE
	msgbox Debug_Text_BerryAct1On, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryAct1Off::
	setvar VAR_HARVEST_KING, 0
	msgbox Debug_Text_BerryAct1Off, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryToggleLeague::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, Debug_EventScript_BerryLeagueOff
	setflag FLAG_SYS_GAME_CLEAR
	msgbox Debug_Text_BerryLeagueOn, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryLeagueOff::
	clearflag FLAG_SYS_GAME_CLEAR
	msgbox Debug_Text_BerryLeagueOff, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryMoney::
	lockall
	addmoney 10000
	msgbox Debug_Text_BerryMoney, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryOrderCommon::
	lockall
	setvar VAR_0x8004, FALSE
	special BerryDebug_NewOrder
	msgbox Debug_Text_BerryOrderCommon, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryOrderDiscovery::
	lockall
	setvar VAR_0x8004, TRUE
	special BerryDebug_NewOrder
	msgbox Debug_Text_BerryOrderDiscovery, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryNoMoney::
	lockall
	special BerryDebug_ClearMoney
	msgbox Debug_Text_BerryNoMoney, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryMulch::
	lockall
	additem ITEM_GROWTH_MULCH, 5
	additem ITEM_DAMP_MULCH, 5
	additem ITEM_STABLE_MULCH, 5
	additem ITEM_GOOEY_MULCH, 5
	additem ITEM_RICH_MULCH, 5
	additem ITEM_SURPRISE_MULCH, 5
	additem ITEM_BOOST_MULCH, 5
	additem ITEM_AMAZE_MULCH, 5
	msgbox Debug_Text_BerryMulch, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryResetAll::
	lockall
	msgbox Debug_Text_BerryResetAllAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Debug_EventScript_BerryResetAllNo
	special BerryDebug_ResetAll
	msgbox Debug_Text_BerryResetAllDone, MSGBOX_DEFAULT
	goto Debug_EventScript_BerryReload

Debug_EventScript_BerryResetAllNo::
	releaseall
	end

@ --- Status --------------------------------------------------------------------
Debug_EventScript_BerryStatus::
	lockall
	special BerryDebug_Status
	buffernumberstring STR_VAR_1, VAR_BERRY_GARDEN_LEVEL
	buffernumberstring STR_VAR_2, VAR_BERRY_GARDEN_WORK
	buffernumberstring STR_VAR_3, VAR_0x8007
	msgbox Debug_Text_BerryStatus1, MSGBOX_DEFAULT
	buffernumberstring STR_VAR_1, VAR_0x8004
	buffernumberstring STR_VAR_2, VAR_BERRY_LEDGER_MILESTONE
	buffernumberstring STR_VAR_3, VAR_0x8005
	msgbox Debug_Text_BerryStatus2, MSGBOX_DEFAULT
	buffernumberstring STR_VAR_1, VAR_0x8006
	buffernumberstring STR_VAR_2, VAR_GARDEN_TODAY
	buffernumberstring STR_VAR_3, VAR_HARVEST_KING
	msgbox Debug_Text_BerryStatus3, MSGBOX_DEFAULT
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	buffernumberstring STR_VAR_3, VAR_0x800A
	msgbox Debug_Text_BerryStatusHearts, MSGBOX_DEFAULT
	call_if_set FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Debug_EventScript_BerryGiftTaken
	call_if_unset FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Debug_EventScript_BerryGiftOpen
	specialvar VAR_RESULT, GardenOrder_Get
	goto_if_eq VAR_RESULT, GARDEN_ORDER_NONE, Debug_EventScript_BerryNoOrder
	bufferitemnameplural STR_VAR_1, VAR_0x8004, VAR_0x8005
	buffernumberstring STR_VAR_2, VAR_0x8005
	call_if_eq VAR_RESULT, GARDEN_ORDER_OPEN, Debug_EventScript_BerryOrderOpen
	call_if_eq VAR_RESULT, GARDEN_ORDER_DONE, Debug_EventScript_BerryOrderDone
	releaseall
	end

Debug_EventScript_BerryNoOrder::
	msgbox Debug_Text_BerryNoOrder, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_BerryOrderOpen::
	call_if_eq VAR_0x8007, TRUE, Debug_EventScript_BerryOrderOpenDiscovery
	call_if_eq VAR_0x8007, FALSE, Debug_EventScript_BerryOrderOpenCommon
	return

Debug_EventScript_BerryOrderOpenCommon::
	msgbox Debug_Text_BerryOrderOpen, MSGBOX_DEFAULT
	return

Debug_EventScript_BerryOrderOpenDiscovery::
	msgbox Debug_Text_BerryOrderOpenDiscovery, MSGBOX_DEFAULT
	return

Debug_EventScript_BerryOrderDone::
	msgbox Debug_Text_BerryOrderDone, MSGBOX_DEFAULT
	return

Debug_EventScript_BerryGiftTaken::
	msgbox Debug_Text_BerryGiftTaken, MSGBOX_DEFAULT
	return

Debug_EventScript_BerryGiftOpen::
	msgbox Debug_Text_BerryGiftOpen, MSGBOX_DEFAULT
	return

Debug_Text_BerryAdvanced:
	.string "Clock moved {STR_VAR_1} hour(s) forward.\n"
	.string "Reloading the map...$"

Debug_Text_BerryNextMorning:
	.string "Clock moved to the next 7:00.\n"
	.string "Reloading the map...$"

Debug_Text_BerryNewGardenDay:
	.string "New garden day (clock untouched):\n"
	.string "gifts back, paid works finished.$"

Debug_Text_BerryBookSet:
	.string "Book of Berries: {STR_VAR_1} registered.\p"
	.string "Talk to Bram for the milestones.$"

Debug_Text_BerryMilestonesUnpaid:
	.string "Book milestones marked as unpaid.$"

Debug_Text_BerryLevelSet:
	.string "Garden level {STR_VAR_1}; works cleared.\n"
	.string "Reloading the map...$"

Debug_Text_BerryRipened:
	.string "Every planted garden plot is ripe.$"

Debug_Text_BerryGrown:
	.string "Planted garden plots grew a stage.$"

Debug_Text_BerryEmptied:
	.string "The garden and Laurel's plot are\n"
	.string "empty soil.$"

Debug_Text_BerryAct1On:
	.string "Harvest King: Act 1 done (4).\n"
	.string "Levels 3 and 4 can be offered.$"

Debug_Text_BerryAct1Off:
	.string "Harvest King: back to state 0.$"

Debug_Text_BerryLeagueOn:
	.string "League cleared: Laurel's rare gift,\n"
	.string "Lansat and Starf crosses are on.$"

Debug_Text_BerryLeagueOff:
	.string "League NOT cleared.$"

Debug_Text_BerryMoney:
	.string "Got ¥10,000.$"

Debug_Text_BerryOrderCommon:
	.string "Today's order cleared. Bram draws a\n"
	.string "COMMON one next time you talk.$"

Debug_Text_BerryOrderDiscovery:
	.string "Today's order cleared. Bram draws a\n"
	.string "DISCOVERY next time (common if none).$"

Debug_Text_BerryNoMoney:
	.string "Money set to ¥0.$"

Debug_Text_BerryMulch:
	.string "Got 5 of each of the 8 Mulches.$"

Debug_Text_BerryResetAllAsk:
	.string "Forget Bram, the Book, the garden\n"
	.string "and the story? (a fresh save)$"

Debug_Text_BerryResetAllDone:
	.string "Berry Master reset. Bram will give\n"
	.string "the tutorial again.$"

Debug_Text_BerryStatus1:
	.string "Level {STR_VAR_1}   Work {STR_VAR_2}\n"
	.string "Planted garden plots: {STR_VAR_3}/10$"

Debug_Text_BerryStatus2:
	.string "Book {STR_VAR_1}/67   Paid {STR_VAR_2}\n"
	.string "Milestone owed: {STR_VAR_3}$"

Debug_Text_BerryStatus3:
	.string "Hour {STR_VAR_1}   Today bits {STR_VAR_2}\n"
	.string "Harvest King state: {STR_VAR_3}$"

Debug_Text_BerryStatusHearts:
	.string "Hearts (5 and 12 open lines):\n"
	.string "Bram {STR_VAR_1}  Laurel {STR_VAR_2}\l"
	.string "Tilly {STR_VAR_3}$"

Debug_Text_BerryKlara:
	.string "Klara raids this morning: in the\n"
	.string "garden, morning, with a ripe plot.$"

Debug_Text_BerryHeartsSet:
	.string "Everyone's hearts: {STR_VAR_1}.\n"
	.string "Talked-today marks are kept.$"

Debug_Text_BerryNoOrder:
	.string "Order: none drawn today.$"

Debug_Text_BerryOrderOpen:
	.string "Order: {STR_VAR_2} {STR_VAR_1}, open.$"

Debug_Text_BerryOrderOpenDiscovery:
	.string "Order: DISCOVERY {STR_VAR_1}, open.$"

Debug_Text_BerryOrderDone:
	.string "Order: {STR_VAR_2} {STR_VAR_1}, delivered.$"

Debug_Text_BerryGiftTaken:
	.string "Bram's gift: taken today.$"

Debug_Text_BerryGiftOpen:
	.string "Bram's gift: still waiting today.$"
