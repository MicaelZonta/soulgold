.set LOCALID_DOJO_LICKILICKY, 1
.set LOCALID_DOJO_MACHAMP, 2
.set LOCALID_DOJO_STEELIX, 3
.set LOCALID_DOJO_ALAKAZAM, 4
.set LOCALID_DOJO_SLOWKING, 5
.set LOCALID_DOJO_RAICHU, 6

SaffronCity_FightingDojo_MapScripts::
	.byte 0

SaffronCity_FightingDojo_EventScript_StatueLeft::
	msgbox SaffronCity_FightingDojo_Text_Sign1, MSGBOX_SIGN
	end
SaffronCity_FightingDojo_EventScript_StatueRight::
	msgbox SaffronCity_FightingDojo_Text_Sign2, MSGBOX_SIGN
	end

SaffronCity_FightingDojo_EventScript_BlackBelt::
	msgbox SaffronCity_FightingDojo_Text_BlackBelt, MSGBOX_NPC
	end

SaffronCity_FightingDojo_EventScript_Cooltrainer::
	msgbox SaffronCity_FightingDojo_Text_Cooltrainer, MSGBOX_NPC
	end

SaffronCity_FightingDojo_EventScript_Refused::
	closemessage
	release
	end

SaffronCity_FightingDojo_EventScript_Lickilicky_EV_HP::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LICKILICKY, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojo_Text_Lickilicky, MSGBOX_DEFAULT
	delay 20
	closemessage
	goto_if_set FLAG_TEMP_1, SaffronCity_FightingDojo_EventScript_BattleLickilicky_EV_HP
	delay 30
	bufferspeciesname STR_VAR_1, SPECIES_LICKILICKY
	bufferstring STR_VAR_2, SaffronCity_FightingDojo_Text_HP
	msgbox SaffronCity_FightingDojo_Text_WouldYouLikeToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojo_EventScript_Refused
SaffronCity_FightingDojo_EventScript_BattleLickilicky_EV_HP::
	setflag B_FLAG_NO_CATCHING
	setwildbattle SPECIES_LICKILICKY, 1, ITEM_NONE
	dowildbattle
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_TEMP_1
	release
	end
	
SaffronCity_FightingDojo_Text_Lickilicky:
	.string "{SPEAKER NAME_LICKILICKY}Liiiiick!$"

SaffronCity_FightingDojo_EventScript_Machamp_EV_Attack::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojo_Text_Machamp, MSGBOX_DEFAULT
	delay 20
	closemessage
	goto_if_set FLAG_TEMP_2, SaffronCity_FightingDojo_EventScript_BattleMachamp_EV_Attack
	delay 30
	bufferspeciesname STR_VAR_1, SPECIES_MACHAMP
	bufferstring STR_VAR_2, SaffronCity_FightingDojo_Text_Attack
	msgbox SaffronCity_FightingDojo_Text_WouldYouLikeToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojo_EventScript_Refused
SaffronCity_FightingDojo_EventScript_BattleMachamp_EV_Attack::
	setflag B_FLAG_NO_CATCHING
	setwildbattle SPECIES_MACHAMP, 1, ITEM_NONE
	dowildbattle
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_TEMP_2
	release
	end

SaffronCity_FightingDojo_Text_Machamp:
	.string "{SPEAKER NAME_MACHAMP}Champ!$"

SaffronCity_FightingDojo_EventScript_Steelix_EV_Defense::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_STEELIX, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojo_Text_Steelix, MSGBOX_DEFAULT
	delay 20
	closemessage
	goto_if_set FLAG_TEMP_3, SaffronCity_FightingDojo_EventScript_BattleSteelix_EV_Defense
	delay 30
	bufferspeciesname STR_VAR_1, SPECIES_STEELIX
	bufferstring STR_VAR_2, SaffronCity_FightingDojo_Text_Defense
	msgbox SaffronCity_FightingDojo_Text_WouldYouLikeToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojo_EventScript_Refused
SaffronCity_FightingDojo_EventScript_BattleSteelix_EV_Defense::
	setflag B_FLAG_NO_CATCHING
	setwildbattle SPECIES_STEELIX, 1, ITEM_NONE
	dowildbattle
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_TEMP_3
	release
	end

SaffronCity_FightingDojo_Text_Steelix:
	.string "{SPEAKER NAME_STEELIX}Grrrind!$"

SaffronCity_FightingDojo_EventScript_Alakazam_EV_SpecialAttack::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ALAKAZAM, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojo_Text_Alakazam, MSGBOX_DEFAULT
	delay 20
	closemessage
	goto_if_set FLAG_TEMP_4, SaffronCity_FightingDojo_EventScript_BattleAlakazam_EV_SpecialAttack
	delay 30
	bufferspeciesname STR_VAR_1, SPECIES_ALAKAZAM
	bufferstring STR_VAR_2, SaffronCity_FightingDojo_Text_SpecialAttack
	msgbox SaffronCity_FightingDojo_Text_WouldYouLikeToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojo_EventScript_Refused
SaffronCity_FightingDojo_EventScript_BattleAlakazam_EV_SpecialAttack::
	setflag B_FLAG_NO_CATCHING
	setwildbattle SPECIES_ALAKAZAM, 1, ITEM_NONE
	dowildbattle
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_TEMP_4
	release
	end

SaffronCity_FightingDojo_Text_Alakazam:
	.string "{SPEAKER NAME_ALAKAZAM}Zam!$"

SaffronCity_FightingDojo_EventScript_Slowking_EV_SpecialDefense::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SLOWKING, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojo_Text_Slowking, MSGBOX_DEFAULT
	delay 20
	closemessage
	goto_if_set FLAG_TEMP_5, SaffronCity_FightingDojo_EventScript_BattleSlowking_EV_SpecialDefense
	delay 30
	bufferspeciesname STR_VAR_1, SPECIES_SLOWKING
	bufferstring STR_VAR_2, SaffronCity_FightingDojo_Text_SpecialDefense
	msgbox SaffronCity_FightingDojo_Text_WouldYouLikeToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojo_EventScript_Refused
SaffronCity_FightingDojo_EventScript_BattleSlowking_EV_SpecialDefense::
	setflag B_FLAG_NO_CATCHING
	setwildbattle SPECIES_SLOWKING, 1, ITEM_NONE
	dowildbattle
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_TEMP_5
	release
	end

SaffronCity_FightingDojo_Text_Slowking:
	.string "{SPEAKER NAME_SLOWKING}HMMM...$"

SaffronCity_FightingDojo_EventScript_Raichu_EV_Speed::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RAICHU, CRY_MODE_NORMAL
	msgbox SaffronCity_FightingDojo_Text_Raichu, MSGBOX_DEFAULT
	delay 20
	closemessage
	goto_if_set FLAG_TEMP_6, SaffronCity_FightingDojo_EventScript_BattleRaichu_EV_Speed
	delay 30
	bufferspeciesname STR_VAR_1, SPECIES_RAICHU
	bufferstring STR_VAR_2, SaffronCity_FightingDojo_Text_Speed
	msgbox SaffronCity_FightingDojo_Text_WouldYouLikeToBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_FightingDojo_EventScript_Refused
SaffronCity_FightingDojo_EventScript_BattleRaichu_EV_Speed::
	setflag B_FLAG_NO_CATCHING
	setwildbattle SPECIES_RAICHU, 1, ITEM_NONE
	dowildbattle
	clearflag B_FLAG_NO_CATCHING
	setflag FLAG_TEMP_6
	release
	end

SaffronCity_FightingDojo_Text_Raichu:
	.string "{SPEAKER NAME_RAICHU}Chuuu!$"

SaffronCity_FightingDojo_Text_HP:
	.string "Hp$"
SaffronCity_FightingDojo_Text_Attack:
	.string "Atk$"
SaffronCity_FightingDojo_Text_Defense:
	.string "Def$"
SaffronCity_FightingDojo_Text_SpecialAttack:
	.string "Sp.Atk$"
SaffronCity_FightingDojo_Text_SpecialDefense:
	.string "Sp.Def$"
SaffronCity_FightingDojo_Text_Speed:
	.string "Spd$"

SaffronCity_FightingDojo_Text_WouldYouLikeToBattle:
	.string "Battle {STR_VAR_1} for 3 {STR_VAR_2} EVs?$"

SaffronCity_FightingDojo_Text_BlackBelt:
	.string "You enter the Fighting Dojo!\p"
	.string "Here, you may hone the stats of\n"
	.string "of your Pokémon by battle!$"

SaffronCity_FightingDojo_Text_Sign1:
	.string "Left: Hp, Def, Sdef$"

SaffronCity_FightingDojo_Text_Sign2:
	.string "Right: Atk, Spatk, Spd$"

SaffronCity_FightingDojo_Text_Cooltrainer::
	.string "Only trainers with all Kanto badges\n"
	.string "may enter the Vip lounge.$"

@Ability swapper

SaffronCity_FightingDojo_Ability_Man::
	lock
	faceplayer
	msgbox SaffronCity_FightingDojo_Ability_Text1, MSGBOX_YESNO
	waitmessage
	compare VAR_RESULT, YES
	goto_if_eq SaffronCity_FightingDojo_Ability_CheckMoney
	compare VAR_RESULT, NO
	goto_if_eq SaffronCity_FightingDojo_Ability_No
	end

SaffronCity_FightingDojo_Ability_No:
	msgbox SaffronCity_FightingDojo_Ability_Text_No, MSGBOX_DEFAULT
	waitmessage
	release
	end

SaffronCity_FightingDojo_SetZeroNoMoney::
	msgbox SaffronCity_FightingDojo_SetZeroTextNoMoney, MSGBOX_DEFAULT
	waitmessage
	release
	end

SaffronCity_FightingDojo_Ability_CheckMoney:
	checkmoney 1000000, 0
	compare VAR_RESULT, TRUE
	goto_if_eq SaffronCity_FightingDojo_Ability_Continue
	compare VAR_RESULT, FALSE
	goto_if_eq SaffronCity_FightingDojo_SetZeroNoMoney
	end

@ SwitchMonAbility (src/field_specials.c) was commented out and never
@ registered as a special, while VAR_RESULT still held TRUE from checkmoney:
@ every visit charged 25,000 and changed nothing, even after cancelling the
@ party menu (bug/B06). Cancel and Eggs now cost nothing; callnative keeps
@ data/specials.inc untouched.
SaffronCity_FightingDojo_Ability_Continue:
	closemessage
	special ChoosePartyMon
	waitstate
	lock
	goto_if_ge VAR_0x8004, PARTY_SIZE, SaffronCity_FightingDojo_Ability_No
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, SaffronCity_FightingDojo_Ability_Cant
	callnative SwitchMonAbility
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_FightingDojo_Ability_Finish
	goto SaffronCity_FightingDojo_Ability_Cant

SaffronCity_FightingDojo_Ability_Cant:
	msgbox SaffronCity_FightingDojo_Ability_Text_Cant, MSGBOX_DEFAULT
	waitmessage
	release
	end

SaffronCity_FightingDojo_Ability_Finish:
	fadescreen 0x1
	delay 100
	fadescreen 0x0
	faceplayer
	waitse
	playse SE_EXP_MAX
	msgbox SaffronCity_FightingDojo_Ability_Finish_Text, MSGBOX_DEFAULT
	removemoney 1000000, 0
	closemessage
	release
	end

SaffronCity_FightingDojo_Ability_Finish_Text:
	.string "That's it! You're welcome!$"

SaffronCity_FightingDojo_Ability_Text1:
	.string "Welcome! I'm the Ability Expert!\p"
	.string "I can swap Pokémon's abilities in\n"
	.string "a heartbeat, for just ¥1,000,000!\p"
	.string "Would you like me to swap any\n"
	.string "Pokémon's ability?$"

SaffronCity_FightingDojo_Ability_Text_No:
	.string "Sure. I'll be here if you need me.$"

SaffronCity_FightingDojo_Ability_Text_Cant:
	.string "I cannot do that. This Pokémon\n"
	.string "does not have a second Ability!$"

SaffronCity_FightingDojo_Ability_Text_NoChampion:
	.string "Welcome! I'm the Ability Expert!\p"
	.string "I can swap Pokémon's abilities\n"
	.string "in a heartbeat.\p"
	.string "Unfortunately, my back hurts and\n"
	.string "I can't work today.\p"
	.string "Come again later!$"

SaffronCity_FightingDojo_SetZeroTextNoMoney:
	.string "You don't have enough money.\p"
	.string "Come back when you have.$"

