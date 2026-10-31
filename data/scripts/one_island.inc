@ A abertura da One Island.
@
@ No FireRed o Bill levava o jogador depois do ginasio do Blaine em Cinnabar.
@ Aqui o Cinnabar e a ilha destruida do Gold/Silver, sem ginasio, entao a ilha
@ abre na corrente do Navel Rock, que ja precisava dela (o marinheiro de la
@ emite o Mystic Ticket): o Bill le o ritmo da leitura do Blaine, conta que o
@ barco do Celio veio busca-lo e convida o jogador.
@
@ VAR_ONE_ISLAND_STATE:
@   0  nao convidado (e nunca esteve na ilha)
@   1  a caminho com o Bill: o porto mostra o Bill e toca a cena de chegada
@   2  ja visitou: a balsa Vermilion <-> One Island fica aberta nos dois
@      marinheiros. Quem chega a pe pelo Mt. Ember vai direto para 2
@      (OneIsland_OnTransition) e o Bill reage em casa.
@
@ O Bill do porto e escondido por FLAG_TEMP_9 (zera a cada mapa; o
@ ON_TRANSITION do porto sempre seta antes de decidir).
@
@ Falas do gpt-6-sol pelo Codex.

@ Resposta ao convite, chamada da casa do Bill (GoldenrodCity_BillsHouse,
@ scripts.pory) logo depois de um msgbox YESNO.
OneIsland_EventScript_BillAnswer::
	goto_if_eq VAR_RESULT, NO, OneIsland_EventScript_BillDeclined
	msgbox OneIsland_Text_BillLetsGo, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ONE_ISLAND_STATE, 1
	warp MAP_ONE_ISLAND_HARBOR, 8, 14
	waitstate
	release
	end

OneIsland_EventScript_BillDeclined:
	msgbox OneIsland_Text_BillDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

@ O jogador desce do barco em (8,14) e o Bill vem ao lado, em (9,14). Ele fala,
@ sobe pela sala ate a porta (8,9) e vai ver o Celio.
OneIsland_EventScript_BillArrival::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox OneIsland_Text_BillArrival, MSGBOX_DEFAULT
	msgbox OneIsland_Text_BillParting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ONE_ISLAND_HARBOR_BILL, OneIsland_Harbor_Movement_BillLeaves
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ONE_ISLAND_HARBOR_BILL
	setvar VAR_ONE_ISLAND_STATE, 2
	releaseall
	end

OneIsland_Harbor_Movement_BillLeaves:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

@ ---------------------------------------------------------------- falas

OneIsland_Text_BillDeclined:
	.string "{SPEAKER NAME_BILL}No problem. The boat can wait.\p"
	.string "FLANNERY is near hot places.\n"
	.string "MT. EMBER may help. Remember it.$"

OneIsland_Text_BillStillWaiting::
	.string "{SPEAKER NAME_BILL}CELIO's boat is still waiting.\n"
	.string "Want to come to ONE ISLAND?$"

OneIsland_Text_BillLetsGo:
	.string "{SPEAKER NAME_BILL}Perfect. Let's catch that boat.$"

OneIsland_Text_BillArrival:
	.string "{SPEAKER NAME_BILL}Here we are, ONE ISLAND.\n"
	.string "Several islands surround it.\p"
	.string "CELIO runs the island PC network\n"
	.string "all by himself.\p"
	.string "His boat will now run between\n"
	.string "VERMILION and ONE ISLAND.\p"
	.string "Why am I explaining now?\n"
	.string "Let's go see CELIO.$"

OneIsland_Text_BillParting:
	.string "{SPEAKER NAME_BILL}CELIO's in the POKéMON CENTER.\n"
	.string "I'd better sync up with him.\p"
	.string "See you around, {PLAYER}.$"

OneIsland_Text_BillAlreadyBeen::
	.string "{SPEAKER NAME_BILL}You reached ONE ISLAND through\n"
	.string "MT. EMBER? You did?\p"
	.string "Then no boat trip needed. CELIO's\n"
	.string "ferry's at VERMILION anyway.\p"
	.string "That rhythm: two days on,\n"
	.string "third day blank. A heat pattern.\p"
	.string "FLANNERY roams hot places.\n"
	.string "She'll know what it means.$"

OneIsland_Text_BillAfterTrip::
	.string "{SPEAKER NAME_BILL}One Island's network is humming.\n"
	.string "Now, ask FLANNERY about that heat.$"

OneIsland_Text_FerryNotRunning::
	.string "{SPEAKER NAME_SAILOR}ONE ISLAND? Nobody's booked\n"
	.string "that run yet.$"
