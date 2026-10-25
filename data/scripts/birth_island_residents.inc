@ Birth Island: o Colress e a Soliera.
@
@ Os dois saem do Nexus e ate agora nao existiam em lugar nenhum do mundo:
@ tinham ficha, time e sprite, e nenhuma presenca fora do loop pos-Necrozma.
@
@ Dois modos. ANTES de enfrentar o Deoxys a cena manda, e quem esta na ilha
@ nao depende do dia: o Colress esta sempre la (foi ele que chegou primeiro) e
@ a Soliera aparece quando VAR_BIRTH_ISLAND_SCENE passa de 0. DEPOIS do
@ Deoxys a agenda (src/data/npc_schedule.h) assume e os dois se revezam:
@
@   Seg, Qua, Sex   Colress
@   Ter, Qui        Soliera
@   Sab             os dois
@   Dom             ninguem. A ilha fica so com o buraco.
@
@ FLAG_TEMP_B e FLAG_TEMP_C sao as de ocultacao (a Flannery usa a D). Zeram a
@ cada carregamento de mapa e o ON_TRANSITION sempre seta antes de decidir,
@ entao nenhuma flag persistente e gasta so para esconder.
@
@ As falas sao do gpt-6-sol pelo Codex, com briefing de personalidade por
@ personagem; a encenacao e as coordenadas sao medidas do map.bin.

BirthIsland_Residents_OnTransition::
	setflag FLAG_TEMP_B
	setflag FLAG_TEMP_C
	goto_if_set FLAG_BATTLED_DEOXYS, BirthIsland_Residents_ScheduleMode
	clearflag FLAG_TEMP_B
	goto_if_eq VAR_BIRTH_ISLAND_SCENE, 0, BirthIsland_Residents_Done
	clearflag FLAG_TEMP_C
	cleartrainerflag TRAINER_COLRESS
	cleartrainerflag TRAINER_SOLIERA
	return

BirthIsland_Residents_ScheduleMode:
	setvar VAR_0x8004, SCHEDULED_NPC_COLRESS
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, BirthIsland_Residents_ShowColress
	setvar VAR_0x8004, SCHEDULED_NPC_SOLIERA
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, BirthIsland_Residents_ShowSoliera
	return

BirthIsland_Residents_Done:
	return

BirthIsland_Residents_ShowColress:
	clearflag FLAG_TEMP_B
	cleartrainerflag TRAINER_COLRESS
	return

BirthIsland_Residents_ShowSoliera:
	clearflag FLAG_TEMP_C
	cleartrainerflag TRAINER_SOLIERA
	return

@ Gatilho no topo da escada (15,16): e por onde o jogador entra na bacia de
@ grama, medido no map.bin. So dispara com a Soliera ainda sem chegar.

BirthIsland_OnFrame::
	map_script_2 VAR_BIRTH_ISLAND_SCENE, 0, BirthIsland_EventScript_SolieraArrives
	.2byte 0

BirthIsland_EventScript_SolieraArrives::
	lockall
	delay 20
	special ShakeCamera
	waitstate
	fadescreenswapbuffers FADE_TO_WHITE
	addobject LOCALID_BIRTH_ISLAND_SOLIERA
	fadescreenswapbuffers FADE_FROM_WHITE
	applymovement OBJ_EVENT_ID_PLAYER, BirthIsland_Movement_PlayerTurnsRight
	waitmovement 0
	msgbox BirthIsland_Text_SolieraArrives, MSGBOX_DEFAULT
	msgbox BirthIsland_Text_ColressReply, MSGBOX_DEFAULT
	msgbox BirthIsland_Text_SolieraArgument, MSGBOX_DEFAULT
	msgbox BirthIsland_Text_ColressArgument, MSGBOX_DEFAULT
	closemessage
	setvar VAR_BIRTH_ISLAND_SCENE, 1
	releaseall
	end

BirthIsland_Movement_PlayerTurnsRight:
	face_right
	step_end

@ O Meteorite da cratera. Ele e key item (importance 1, POCKET_KEY_ITEMS),
@ entao nao se gasta: um so da o ciclo das quatro formas do Deoxys para
@ sempre. A mecanica ja existia inteira em form_change_tables.h; o que faltava
@ era o item ter onde ser pego, porque as duas fontes dele (MtChimney e
@ FallarborTown_CozmosHouse) estao fora da ROM.

BirthIsland_EventScript_Item_Meteorite::
	finditem ITEM_METEORITE
	end

@ ---------------------------------------------------------------- Colress

BirthIsland_EventScript_Colress::
	lock
	faceplayer
	goto_if_set FLAG_BATTLED_DEOXYS, BirthIsland_EventScript_ColressAfter
	goto_if_unset FLAG_MET_COLRESS, BirthIsland_EventScript_ColressIntro
	msgbox BirthIsland_Text_ColressBattleRequest, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_COLRESS, BirthIsland_Text_ColressDefeat
	msgbox BirthIsland_Text_ColressDefeat, MSGBOX_AUTOCLOSE
	end

BirthIsland_EventScript_ColressIntro:
	msgbox BirthIsland_Text_ColressFirst, MSGBOX_DEFAULT
	setflag FLAG_MET_COLRESS
	release
	end

BirthIsland_EventScript_ColressAfter:
	msgbox BirthIsland_Text_ColressAfterDeoxys, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_COLRESS, BirthIsland_Text_ColressDefeat
	msgbox BirthIsland_Text_ColressDefeat, MSGBOX_AUTOCLOSE
	end

@ ---------------------------------------------------------------- Soliera

BirthIsland_EventScript_Soliera::
	lock
	faceplayer
	goto_if_set FLAG_BATTLED_DEOXYS, BirthIsland_EventScript_SolieraAfter
	msgbox BirthIsland_Text_SolieraBattleRequest, MSGBOX_DEFAULT
	setflag FLAG_MET_SOLIERA
	trainerbattle_no_intro TRAINER_SOLIERA, BirthIsland_Text_SolieraDefeat
	msgbox BirthIsland_Text_SolieraDefeat, MSGBOX_AUTOCLOSE
	end

BirthIsland_EventScript_SolieraAfter:
	msgbox BirthIsland_Text_SolieraAfterDeoxys, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SOLIERA, BirthIsland_Text_SolieraDefeat
	msgbox BirthIsland_Text_SolieraDefeat, MSGBOX_AUTOCLOSE
	end

@ ---------------------------------------------------------------- falas

BirthIsland_Text_ColressFirst:
	.string "{SPEAKER NAME_COLRESS}Keep clear of the left probe.\n"
	.string "The meteor's stone is copying it.\p"
	.string "This chart shows open sea here.\n"
	.string "Please stand beside the marker.$"

BirthIsland_Text_SolieraArrives:
	.string "{SPEAKER NAME_SOLIERA}Colress. You are here.\n"
	.string "I traced Necrozma's signal here.\p"
	.string "I brought instruments.\n"
	.string "I prepared for its return.$"

BirthIsland_Text_ColressReply:
	.string "{SPEAKER NAME_COLRESS}Soliera. The source is unconfirmed.\n"
	.string "The stone can imitate a signal.\p"
	.string "The light array we built still runs.\n"
	.string "I intend to test this one.$"

BirthIsland_Text_SolieraArgument:
	.string "{SPEAKER NAME_SOLIERA}Our ancestors bound Necrozma.\n"
	.string "They drew its light until it broke.\p"
	.string "Our world has stayed dark since.\n"
	.string "Your lamps light our streets now.\p"
	.string "One bank failed last winter.\n"
	.string "Nine thousand homes went dark.$"

BirthIsland_Text_ColressArgument:
	.string "{SPEAKER NAME_COLRESS}Agreed. The draw was too strong.\n"
	.string "The source failed under that load.\p"
	.string "A copy may divide the strain.\n"
	.string "I intend to test that here.$"

BirthIsland_Text_ColressBattleRequest:
	.string "{SPEAKER NAME_COLRESS}May we battle?\n"
	.string "Your choices will test my model.$"

BirthIsland_Text_SolieraBattleRequest:
	.string "{SPEAKER NAME_SOLIERA}The stone may release something.\n"
	.string "Battle me. I must test your response.$"

BirthIsland_Text_ColressDefeat:
	.string "{SPEAKER NAME_COLRESS}Excellent. My model was wrong.\n"
	.string "Your team exceeded the forecast.$"

BirthIsland_Text_SolieraDefeat:
	.string "{SPEAKER NAME_SOLIERA}Assessment complete.\n"
	.string "You can face what the stone yields.$"

BirthIsland_Text_ColressAfterDeoxys:
	.string "{SPEAKER NAME_COLRESS}You caught it. The signal is gone.\n"
	.string "That proves nothing of Necrozma.\p"
	.string "Inconclusive. Excellent.\n"
	.string "I will stay and study the stone.$"

BirthIsland_Text_SolieraAfterDeoxys:
	.string "{SPEAKER NAME_SOLIERA}I feared Necrozma's light.\n"
	.string "This came from another source.\p"
	.string "The stone remains active.\n"
	.string "I will stay and observe it.$"
