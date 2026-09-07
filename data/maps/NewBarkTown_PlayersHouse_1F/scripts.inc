.set LOCALID_MOMS_FRIEND, 2

NewBarkTown_PlayersHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_PlayersHouse_1F_OnTransition
	.byte 0

NewBarkTown_PlayersHouse_1F_OnTransition::
	call_if_eq VAR_NEWBARK_TOWN_STATE, 1, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	call_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable
	end

NewBarkTown_PlayersHouse_1F_SetMomStandingAtTable::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_LEFT

	@add to newgame later
	clearflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_MOM_VISITED
	return

NewBarkTown_PlayersHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_MOM_VISITED, NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular
	goto_if_set FLAG_ADVENTURE_STARTED, NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting, MSGBOX_DEFAULT
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MovementFaceLeft
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsFriend::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomsFriend, MSGBOX_DEFAULT
	applymovement LOCALID_MOMS_FRIEND, NewBarkTown_PlayersHouse_1F_MovementFaceRight
	waitmovement 0
	release
	end

NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomLeaving, MSGBOX_DEFAULT
	setflag FLAG_MOM_VISITED
	clearflag FLAG_HIDE_ROUTE_30_NPCS
	setvar VAR_NEWBARK_TOWN_STATE, 5
	release
	end


NewBarkTown_PlayersHouse_1F_EventScript_Mom_Regular::
	checkitem ITEM_GROOMING_KIT, 1
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_RestOnly
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomWelcomeHome, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_MomMenuRest, NewBarkTown_PlayersHouse_1F_Text_MomMenuGrooming, NewBarkTown_PlayersHouse_1F_Text_MomMenuCancel
	goto_if_eq VAR_RESULT, 0, NewBarkTown_PlayersHouse_1F_EventScript_Mom_RestOnly
	goto_if_eq VAR_RESULT, 1, NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingStart
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_RestOnly::
	closemessage
	call PlayersHouse_1F_EventScript_MomHealsParty
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingStart::
	closemessage
	dotimebasedevents
	goto_if_set FLAG_GOT_GROOMED, NewBarkTown_PlayersHouse_1F_EventScript_Mom_AlreadyGroomedToday
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomAskWhichPokemon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_ge VAR_0x8004, PARTY_SIZE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingCancelled
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingEgg
	setflag FLAG_GOT_GROOMED
	specialvar VAR_RESULT, GetGroomTargetCategory
	goto_if_eq VAR_RESULT, GROOM_CATEGORY_FURFROU, NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomFurfrou
	goto_if_eq VAR_RESULT, GROOM_CATEGORY_DEERLING, NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomDeerling
	goto NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomNormal
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingCancelled::
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingEgg::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomGroomingEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_AlreadyGroomedToday::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomAlreadyGroomedToday, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomNormal::
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart
	special GroomPokemon
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd
	special BufferMonNickname
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomGroomedGeneric, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Shared fade-out/sound/fade-in played at the exact moment a Pokemon is groomed.
NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart::
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	return

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd::
	@ Refresh the overworld follower while the screen is still black, so a species/form
	@ change (Furfrou trim, Deerling/Sawsbuck season) never shows a stale follower sprite.
	callnative UpdateFollowingPokemon
	fadescreen FADE_FROM_BLACK
	return

@ ---------------------------------------------------------------------------
@ Furfrou grooming: Mom's own trim-styling experience (VAR_MOM_FURFROU_EXP)
@ unlocks one additional trim per point, from 0 (Natural only) to 9 (all trims).
@ ---------------------------------------------------------------------------

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomFurfrou::
	goto_if_eq VAR_MOM_FURFROU_EXP, 0, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouFirstMeeting
	goto_if_eq VAR_MOM_FURFROU_EXP, 1, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu1
	goto_if_eq VAR_MOM_FURFROU_EXP, 2, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu2
	goto_if_eq VAR_MOM_FURFROU_EXP, 3, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu3
	goto_if_eq VAR_MOM_FURFROU_EXP, 4, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu4
	goto_if_eq VAR_MOM_FURFROU_EXP, 5, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu5
	goto_if_eq VAR_MOM_FURFROU_EXP, 6, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu6
	goto_if_eq VAR_MOM_FURFROU_EXP, 7, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu7
	goto_if_eq VAR_MOM_FURFROU_EXP, 8, NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu8
	goto NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu9
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouFirstMeeting::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouFirstMeeting, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart
	special GroomPokemon
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd
	setvar VAR_MOM_FURFROU_EXP, 1
	closemessage
	release
	end

@ Applies the trim chosen in VAR_RESULT (species index into sMomFurfrouTrimOrder) to the selected mon.
NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim::
	copyvar VAR_0x8005, VAR_RESULT
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart
	special ApplyFurfrouTrim
	special GroomPokemon
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd
	special BufferMonNickname
	return

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu1::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockStar, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu2::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockDiamond, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu3::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockDandy, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu4::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond, NewBarkTown_PlayersHouse_1F_Text_TrimDandy
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockDebutante, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu5::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond, NewBarkTown_PlayersHouse_1F_Text_TrimDandy, NewBarkTown_PlayersHouse_1F_Text_TrimDebutante
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockMatron, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu6::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond, NewBarkTown_PlayersHouse_1F_Text_TrimDandy, NewBarkTown_PlayersHouse_1F_Text_TrimDebutante, NewBarkTown_PlayersHouse_1F_Text_TrimMatron
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockLaReine, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu7::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond, NewBarkTown_PlayersHouse_1F_Text_TrimDandy, NewBarkTown_PlayersHouse_1F_Text_TrimDebutante, NewBarkTown_PlayersHouse_1F_Text_TrimMatron, NewBarkTown_PlayersHouse_1F_Text_TrimLaReine
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockKabuki, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu8::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond, NewBarkTown_PlayersHouse_1F_Text_TrimDandy, NewBarkTown_PlayersHouse_1F_Text_TrimDebutante, NewBarkTown_PlayersHouse_1F_Text_TrimMatron, NewBarkTown_PlayersHouse_1F_Text_TrimLaReine, NewBarkTown_PlayersHouse_1F_Text_TrimKabuki
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	addvar VAR_MOM_FURFROU_EXP, 1
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouMastered, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_FurfrouMenu9::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_TrimNatural, NewBarkTown_PlayersHouse_1F_Text_TrimHeart, NewBarkTown_PlayersHouse_1F_Text_TrimStar, NewBarkTown_PlayersHouse_1F_Text_TrimDiamond, NewBarkTown_PlayersHouse_1F_Text_TrimDandy, NewBarkTown_PlayersHouse_1F_Text_TrimDebutante, NewBarkTown_PlayersHouse_1F_Text_TrimMatron, NewBarkTown_PlayersHouse_1F_Text_TrimLaReine, NewBarkTown_PlayersHouse_1F_Text_TrimKabuki, NewBarkTown_PlayersHouse_1F_Text_TrimPharaoh
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_ApplyFurfrouTrim
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomGroomedGeneric, MSGBOX_DEFAULT
	closemessage
	release
	end

@ ---------------------------------------------------------------------------
@ Deerling/Sawsbuck grooming: leads into the Seasonal Perfume side quest.
@ ---------------------------------------------------------------------------

NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomDeerling::
	goto_if_set FLAG_GAVE_MOM_SEASONAL_PERFUME, NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingSeasonMenu
	goto_if_unset FLAG_STARTED_SEASONAL_PERFUME_QUEST, NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingFirstMeeting
	checkitem ITEM_SEASONAL_PERFUME, 1
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingDeliverPerfume
	goto NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomNormal
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingFirstMeeting::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomDeerlingFirstMeeting, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart
	special GroomPokemon
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd
	setflag FLAG_STARTED_SEASONAL_PERFUME_QUEST
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingDeliverPerfume::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomDeerlingDeliverPerfume, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart
	special GroomPokemon
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd
	setflag FLAG_GAVE_MOM_SEASONAL_PERFUME
	closemessage
	@ Same visit continues straight into picking the first season, instead of
	@ ending the conversation and making the player talk to Mom again.
	goto NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingSeasonMenu
	end

NewBarkTown_PlayersHouse_1F_EventScript_Mom_DeerlingSeasonMenu::
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomDeerlingSeasonPrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_PlayersHouse_1F_Text_SeasonSpring, NewBarkTown_PlayersHouse_1F_Text_SeasonSummer, NewBarkTown_PlayersHouse_1F_Text_SeasonAutumn, NewBarkTown_PlayersHouse_1F_Text_SeasonWinter, NewBarkTown_PlayersHouse_1F_Text_MomMenuCancel
	goto_if_ge VAR_RESULT, 4, NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingCancelled
	copyvar VAR_0x8005, VAR_RESULT
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationStart
	special ApplySeasonalForm
	special GroomPokemon
	call NewBarkTown_PlayersHouse_1F_EventScript_Mom_GroomingAnimationEnd
	special BufferMonNickname
	msgbox NewBarkTown_PlayersHouse_1F_Text_MomDeerlingSeasonApplied, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger1::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end

NewBarkTown_PlayersHouse_1F_EventScript_MomsIntroTrigger2::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2
	waitmovement 0
	goto NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro
	end


NewBarkTown_PlayersHouse_1F_EventScript_MomsIntro::
	playse SE_PIN
	applymovement LOCALID_MOM, Common_Movement_ExclamationMark
	delay 60
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_1
	waitmovement 0
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou, MSGBOX_DEFAULT
	call NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear
	call NewBarkTown_PlayersHouse_1F_EventScript_GiveRunningShoes
	removefieldmugshot
	applymovement LOCALID_MOM, NewBarkTown_PlayersHouse_1F_MomMovement_2
	waitmovement 0
	setvar VAR_NEWBARK_TOWN_STATE, 2
	setvar VAR_NEWBARKTOWN_LABSTATE, 0
	setflag FLAG_HIDE_LAB_POLICEMAN
	setflag FLAG_VISITED_NEWBARK_TOWN

	@former flagheap location

	releaseall
	end



NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear::
	playfanfare MUS_OBTAIN_ITEM
	removefieldmugshot
	message NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
	setflag FLAG_REGISTER_RIVAL_POKENAV
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear, MSGBOX_DEFAULT
	closemessage
	delay 30
	return
	
NewBarkTown_PlayersHouse_1F_EventScript_GiveRunningShoes::
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	waitmessage
	closemessage
	playfanfare MUS_OBTAIN_ITEM
	msgbox NewBarkTown_PlayersHouse_1F_Text_SwitchShoesWithRunningShoes, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	special EnableAutorun
	createfieldmugshot MUGSHOT_MOM
	msgbox NewBarkTown_PlayersHouse_1F_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement1:
	delay_8
	walk_down
	walk_right
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_PlayerIntroMovement2:
	delay_8
	walk_down
	face_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_1:
	face_right
	walk_right
	step_end

NewBarkTown_PlayersHouse_1F_MomMovement_2:
	face_left
	walk_left
	delay_8
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceRight:
	face_right
	step_end

NewBarkTown_PlayersHouse_1F_MovementFaceLeft:
	face_left
	step_end

NewBarkTown_PlayersHouse_1F_Text_ElmsLookingForYou:
	.string "Oh, {PLAYER}…! Our neighbor,\n"
	.string "Prof. Elm, was looking for you.\p"
	.string "He said he wanted you to do\n"
	.string "something for him.\p"
	.string "Oh! I almost forgot! Your Pokégear\n"
	.string "is back from the repair shop.\p"
	.string "Here you go!$"

NewBarkTown_PlayersHouse_1F_Text_ObtainedPokeGear:
	.string "{PLAYER} obtained the Pokégear.$"

NewBarkTown_PlayersHouse_1F_Text_ExplainPokeGear:
	.string "Mom: Phone numbers are stored\n"
	.string "in memory.\p"
	.string "Just choose a name you want to call.\p"
	.string "Gee, isn't that convenient?$"

NewBarkTown_PlayersHouse_1F_Text_WearTheseRunningShoes:
	.string "Oh, and don't forget your\n"
	.string "Running Shoes!$"

NewBarkTown_PlayersHouse_1F_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "Running Shoes.$"

NewBarkTown_PlayersHouse_1F_Text_ExplainRunningShoes:
	.string "Mom: You'll get everywhere faster\n"
	.string "with them!$"

NewBarkTown_PlayersHouse_1F_Text_MomHurryUpElmIsWaiting:
	.string "Mom: Prof. Elm is waiting for you.\p"
	.string "Hurry up, baby!$"

NewBarkTown_PlayersHouse_1F_Text_MomsFriend:
	.string "Hi, {PLAYER}!\p"
	.string "I'm visiting!\p"
	.string "Have you heard?\p"
	.string "My daughter is adamant about\n"
	.string "becoming Prof. Elm's assistant.\p"
	.string "She really loves Pokémon!$"

NewBarkTown_PlayersHouse_1F_Text_MomLeaving:
	.string "Mom: Wow, that's a cute Pokémon.\n"
	.string "Where did you get it?\p"
	.string "…\p"
	.string "So, you're leaving on an adventure...\n"
	.string "That does sound challenging...\p"
	.string "Just be careful.\p"
	.string "Pokémon are your friends.\n"
	.string "You need to work as a team.\p"
	.string "Now, go on!\n"
	.string "I'm behind you all the way!$"

NewBarkTown_PlayersHouse_1F_Text_MomWelcomeHome:
	.string "Mom: Welcome home, {PLAYER}!\p"
	.string "Would you like to rest, or should\n"
	.string "we groom one of your Pokémon?$"

NewBarkTown_PlayersHouse_1F_Text_MomMenuRest:
	.string "Rest$"

NewBarkTown_PlayersHouse_1F_Text_MomMenuGrooming:
	.string "Grooming$"

NewBarkTown_PlayersHouse_1F_Text_MomMenuCancel:
	.string "Cancel$"

NewBarkTown_PlayersHouse_1F_Text_MomAskWhichPokemon:
	.string "Mom: All right! Which Pokémon\n"
	.string "needs a little care today?$"

NewBarkTown_PlayersHouse_1F_Text_MomAlreadyGroomedToday:
	.string "Mom: That's enough grooming for\n"
	.string "today. We should give your\l"
	.string "Pokémon's coat some time to settle.$"

NewBarkTown_PlayersHouse_1F_Text_MomGroomedGeneric:
	.string "Mom: There we go!\n"
	.string "{STR_VAR_1} looks much happier.$"

NewBarkTown_PlayersHouse_1F_Text_MomGroomingEgg:
	.string "Mom: Oh, that's still an Egg!\n"
	.string "Let's wait until it hatches.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouFirstMeeting:
	.string "Mom: Oh! What an adorable Pokémon!\n"
	.string "Its coat is so soft and elegant…\p"
	.string "I'd love to practice styling it.\n"
	.string "Maybe I could learn a few trims!$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouWhichTrim:
	.string "Mom: Which trim should I try today?$"

NewBarkTown_PlayersHouse_1F_Text_TrimNatural:
	.string "Natural$"

NewBarkTown_PlayersHouse_1F_Text_TrimHeart:
	.string "Heart$"

NewBarkTown_PlayersHouse_1F_Text_TrimStar:
	.string "Star$"

NewBarkTown_PlayersHouse_1F_Text_TrimDiamond:
	.string "Diamond$"

NewBarkTown_PlayersHouse_1F_Text_TrimDandy:
	.string "Dandy$"

NewBarkTown_PlayersHouse_1F_Text_TrimDebutante:
	.string "Debutante$"

NewBarkTown_PlayersHouse_1F_Text_TrimMatron:
	.string "Matron$"

NewBarkTown_PlayersHouse_1F_Text_TrimLaReine:
	.string "La Reine$"

NewBarkTown_PlayersHouse_1F_Text_TrimKabuki:
	.string "Kabuki$"

NewBarkTown_PlayersHouse_1F_Text_TrimPharaoh:
	.string "Pharaoh$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockStar:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the Star Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockDiamond:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the Diamond Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockDandy:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the Dandy Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockDebutante:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the Debutante Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockMatron:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the Matron Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockLaReine:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the La Reine Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouUnlockKabuki:
	.string "Mom: I think I'm getting better at\n"
	.string "this! Next time, I should be able\l"
	.string "to try the Kabuki Trim.$"

NewBarkTown_PlayersHouse_1F_Text_MomFurfrouMastered:
	.string "Mom: I finally understand every\n"
	.string "style! From now on, I can give\l"
	.string "Furfrou any trim you like.$"

NewBarkTown_PlayersHouse_1F_Text_MomDeerlingFirstMeeting:
	.string "Mom: How curious…\n"
	.string "Its coat reacted when it caught\l"
	.string "the scent of these flowers.\p"
	.string "I heard the Flower Shop in\n"
	.string "Goldenrod sells perfumes inspired\l"
	.string "by the four seasons.\p"
	.string "Maybe one of those could change\n"
	.string "the way its coat looks!$"

NewBarkTown_PlayersHouse_1F_Text_MomDeerlingDeliverPerfume:
	.string "Mom: You found it!\n"
	.string "These four scents are wonderful.\l"
	.string "Let's see how your Pokémon reacts!$"

NewBarkTown_PlayersHouse_1F_Text_MomDeerlingSeasonPrompt:
	.string "Mom: Which scent should we try\n"
	.string "today?$"

NewBarkTown_PlayersHouse_1F_Text_SeasonSpring:
	.string "Spring$"

NewBarkTown_PlayersHouse_1F_Text_SeasonSummer:
	.string "Summer$"

NewBarkTown_PlayersHouse_1F_Text_SeasonAutumn:
	.string "Autumn$"

NewBarkTown_PlayersHouse_1F_Text_SeasonWinter:
	.string "Winter$"

NewBarkTown_PlayersHouse_1F_Text_MomDeerlingSeasonApplied:
	.string "Mom: The seasonal scent gently\n"
	.string "settled into {STR_VAR_1}'s coat!$"
