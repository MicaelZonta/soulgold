@ A corrente que leva o jogador ate o Navel Rock e, no fim dela, entrega o
@ Mystic Ticket. A pedra so aparece nos instrumentos enquanto esta soltando
@ vapor, entao ela nao esta em carta nautica nenhuma - e por isso nenhum
@ capitao aceita navegar para la sem prova.
@
@ VAR_NAVELROCK_QUEST:
@   0  o Blaine ainda nao entregou a leitura velha dele
@   1  entregou; o Bill pode medir
@   2  o Bill achou o ritmo de tres dias; a Flannery pode reconhecer
@   3  a Flannery reescreveu em tabua de mares; o marinheiro aceita
@   4  bilhete emitido
@
@ Quem emite o bilhete e o marinheiro, que e de onde bilhete vem. O Blaine da
@ a pergunta, o Bill da o numero, a Flannery da a traducao, e o marinheiro da
@ o papel. Nenhum dos quatro sabe o que mora la.
@
@ Falas do gpt-6-sol pelo Codex.

@ ------------------------------------------------- Bill, na casa dele em Goldenrod

NavelRockQuest_EventScript_Bill::
	goto_if_ne VAR_NAVELROCK_QUEST, 1, NavelRockQuest_EventScript_BillDone
	msgbox NavelRockQuest_Text_BillReads, MSGBOX_DEFAULT
	setvar VAR_NAVELROCK_QUEST, 2
NavelRockQuest_EventScript_BillDone:
	return

@ ------------------------------------------------- Flannery, onde quer que esteja

NavelRockQuest_EventScript_Flannery::
	goto_if_ne VAR_NAVELROCK_QUEST, 2, NavelRockQuest_EventScript_FlanneryDone
	msgbox NavelRockQuest_Text_FlanneryRecognises, MSGBOX_DEFAULT
	setvar VAR_NAVELROCK_QUEST, 3
NavelRockQuest_EventScript_FlanneryDone:
	return

@ ------------------------------------------------- o marinheiro de One Island

OneIsland_Harbor_EventScript_Sailor::
	lock
	faceplayer
	goto_if_eq VAR_NAVELROCK_QUEST, 3, OneIsland_Harbor_EventScript_SailorAccepts
	@ Desde a abertura da One Island (data/scripts/one_island.inc) ele tambem
	@ faz a volta para Vermilion; o Navel Rock continua pedindo o bilhete.
	message OneIsland_Harbor_Text_SailorWhere
	waitmessage
	dynmultichoice 18, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, OneIsland_Harbor_Text_ChoiceVermilion, OneIsland_Harbor_Text_ChoiceNavelRock, OneIsland_Harbor_Text_ChoiceExit
	switch VAR_RESULT
	case 0, OneIsland_Harbor_EventScript_SailVermilion
	case 1, OneIsland_Harbor_EventScript_SailNavelRock
	goto OneIsland_Harbor_EventScript_SailorNoTrip

OneIsland_Harbor_EventScript_SailorAccepts::
	msgbox OneIsland_Harbor_Text_SailorAccepts, MSGBOX_DEFAULT
	checkitemspace ITEM_MYSTIC_TICKET
	goto_if_eq VAR_RESULT, FALSE, OneIsland_Harbor_EventScript_SailorNoRoom
	giveitem ITEM_MYSTIC_TICKET
	setvar VAR_NAVELROCK_QUEST, 4
	closemessage
	release
	end

OneIsland_Harbor_EventScript_SailorNoRoom::
	msgbox OneIsland_Harbor_Text_SailorNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

OneIsland_Harbor_EventScript_SailVermilion:
	closemessage
	delay 20
	warpsilent MAP_VERMILION_CITY_PORT_INSIDE, 8, 9
	waitstate
	release
	end

OneIsland_Harbor_EventScript_SailNavelRock:
	goto_if_lt VAR_NAVELROCK_QUEST, 4, OneIsland_Harbor_EventScript_SailorNoTicket
	checkitem ITEM_MYSTIC_TICKET
	goto_if_eq VAR_RESULT, FALSE, OneIsland_Harbor_EventScript_SailorNoTicket
	closemessage
	delay 20
	warpsilent MAP_NAVEL_ROCK_EXTERIOR, 9, 37
	waitstate
	release
	end

OneIsland_Harbor_EventScript_SailorNoTicket::
	msgbox OneIsland_Harbor_Text_SailorRefuses, MSGBOX_DEFAULT
	closemessage
	release
	end

OneIsland_Harbor_EventScript_SailorNoTrip::
	closemessage
	release
	end

@ ---------------------------------------------------------------- falas

NavelRockQuest_Text_BlaineHandsReading:
	.string "{SPEAKER NAME_BLAINE}Still chewing on my riddle?\n"
	.string "Forty years I've kept this reading.\p"
	.string "Here. Take it to Bill.\n"
	.string "He measures things for a living.$"

@ Desde 28/10/2026 o Bill termina convidando para a One Island (o barco do
@ Celio veio busca-lo). Abertura em data/scripts/one_island.inc.
NavelRockQuest_Text_BillReads:
	.string "{SPEAKER NAME_BILL}Two days, a signal. Then gone.\n"
	.string "Third day: blank. Every time!\p"
	.string "Since before I was born... wow.\n"
	.string "This rhythm is real, {PLAYER}.\p"
	.string "CELIO sent his boat for me.\n"
	.string "I was heading to ONE ISLAND.\p"
	.string "Those sailors know strange water\n"
	.string "better than anyone I know.\p"
	.string "FLANNERY wanders hot places.\n"
	.string "MT. EMBER may ring a bell to her.\p"
	.string "Come along, {PLAYER}?$"

NavelRockQuest_Text_FlanneryRecognises:
	.string "{SPEAKER NAME_FLANNERY}As heir to this gym, I\n"
	.string "pronounce these readings... Ugh.\p"
	.string "Granddad taught me this rhythm.\n"
	.string "A vent breathes under pooled water.\p"
	.string "The rock steams when it breathes.\n"
	.string "I'll make a tide table from it.$"

OneIsland_Harbor_Text_SailorRefuses:
	.string "{SPEAKER NAME_SAILOR}A diagram? No chart.\n"
	.string "I won't risk my boat on that.$"

OneIsland_Harbor_Text_SailorAccepts:
	.string "{SPEAKER NAME_SAILOR}Now, that's a tide table.\n"
	.string "Two safe days, then one to wait.\p"
	.string "I can sail by these times.\n"
	.string "Here's your ticket. Dawn boat.$"

OneIsland_Harbor_Text_SailorNoRoom:
	.string "{SPEAKER NAME_SAILOR}Your Key Items pocket is full.\n"
	.string "Make room and come back.$"

OneIsland_Harbor_Text_SailorWhere:
	.string "{SPEAKER NAME_SAILOR}NAVEL ROCK today?\n"
	.string "Or VERMILION CITY?$"

OneIsland_Harbor_Text_ChoiceVermilion:
	.string "Vermilion City$"

OneIsland_Harbor_Text_ChoiceNavelRock:
	.string "Navel Rock$"

OneIsland_Harbor_Text_ChoiceExit:
	.string "Exit$"
