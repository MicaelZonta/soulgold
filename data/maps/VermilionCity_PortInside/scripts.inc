VermilionCity_PortInside_MapScripts::
	.byte 0

VermilionPortIndoor_EventScript_Teacher::
	msgbox VermilionPortPassage_Text_Teacher, MSGBOX_NPC
	end
VermilionPortIndoor_EventScript_Nerd::
	msgbox VermilionPort_Text_SuperNerd, MSGBOX_NPC
	end

VermilionPortPassage_Text_Teacher:
	.string "The Fast Ship sails every day!$"

VermilionPort_Text_SuperNerd:
	.string "You came from Johto?\p"
	.string "I hear many rare Pokémon live\n"
	.string "over there.$"

VermilionPort_EventScript_Sailor::
	lock
	faceplayer
	goto_if_unset FLAG_RETURNED_MACHINE_PART, VermilionPort_EventScript_SailorCantSail
	goto_if_ge VAR_SSAQUA_STATE, 7, VermilionPort_EventScript_Sailor_AfterKanto
	msgbox VermilionPort_Text_AskBoard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_Refused
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, TRUE, VermilionPort_EventScript_Sailor_FirstSail
	msgbox VermilionPort_Text_NoTicket, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_EventScript_SailorCantSail::
	msgbox VermilionPort_Text_SailorCantSail, MSGBOX_NPC
	closemessage
	release
	end

VermilionPort_EventScript_Sailor_AfterKanto::
	message VermilionPort_Text_WhereSail
	@ Lista com rolagem: com 7 destinos a lista fixa (MULTI_VERMILION_HARBOR)
	@ passava por baixo da caixa de texto e o "Exit" sumia. Mostra 5 por vez.
	dynmultichoice 19, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, VermilionPort_Text_ChoiceOlivine, VermilionPort_Text_ChoiceSouthernIsland, VermilionPort_Text_ChoiceBirthIsland, VermilionPort_Text_ChoiceFarawayIsland, VermilionPort_Text_ChoiceNavelRock, VermilionPort_Text_ChoiceOneIsland, VermilionPort_Text_ChoiceExit
	switch VAR_RESULT
	case 0, VermilionPort_EventScript_ChoseOlivine
	case 1, VermilionPort_EventScript_ChoseSouthernIsland
	case 2, VermilionPort_EventScript_ChoseBirthIsland
	case 3, VermilionPort_EventScript_ChoseFarawayIsland
	case 4, VermilionPort_EventScript_ChoseNavelRock
	case 5, VermilionPort_EventScript_ChoseOneIsland
	@ A lista tem 7 itens desde que a One Island
	@ entrou (28/10/2026), e o ultimo e "Exit". O case do Exit mandava quem o escolhesse
	@ para o Battle Frontier, que esta em rom_excluded_groups (fora do jogo).
	@ Para reabrir o Frontier um dia: trocar para MULTI_VERMILION_HARBOR_RED
	@ e devolver o destino no case abaixo.
	case 6, VermilionPort_EventScript_Sailor_Refused
	case MULTI_B_PRESSED, VermilionPort_EventScript_Sailor_Refused
	release
	end

VermilionPort_EventScript_ChoseOlivine::
	closemessage
	delay 20
	checkitem ITEM_SS_TICKET
	bufferitemname STR_VAR_1, ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	@ O EnterShip deixa o respawn em Vermilion (serve para as ilhas, que nao
	@ tem Centro); indo para Johto o respawn tem que vir junto, senao quem
	@ desmaiar em Johto acorda em Kanto.
	setrespawn HEAL_LOCATION_OLIVINE_CITY
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE, 8, 16
	waitstate
	release
	end

@ One Island. A rota abre com a viagem do Bill (ou quando o jogador chega la
@ a pe pelo Mt. Ember): VAR_ONE_ISLAND_STATE 2. Abertura em
@ data/scripts/one_island.inc.
VermilionPort_EventScript_ChoseOneIsland::
	closemessage
	delay 20
	goto_if_ne VAR_ONE_ISLAND_STATE, 2, VermilionPort_EventScript_OneIslandClosed
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_ONE_ISLAND_HARBOR, 8, 14
	waitstate
	release
	end

VermilionPort_EventScript_OneIslandClosed:
	msgbox OneIsland_Text_FerryNotRunning, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_EventScript_ChoseSouthernIsland::
	closemessage
	delay 20
	checkitem ITEM_EON_TICKET
	bufferitemname STR_VAR_1, ITEM_EON_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_SOUTHERN_ISLAND_EXTERIOR, 13, 22
	waitstate
	release
	end

VermilionPort_EventScript_ChoseBirthIsland::
	closemessage
	delay 20
	checkitem ITEM_AURORA_TICKET
	bufferitemname STR_VAR_1, ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_BIRTH_ISLAND_EXTERIOR, 15, 24
	waitstate
	release
	end

@ Navel Rock. A pedra so aparece nos instrumentos quando esta soltando vapor,
@ entao o capitao precisa do Mystic Ticket para aceitar navegar para uma coisa
@ que nao esta na carta.
VermilionPort_EventScript_ChoseNavelRock::
	closemessage
	delay 20
	checkitem ITEM_MYSTIC_TICKET
	bufferitemname STR_VAR_1, ITEM_MYSTIC_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_NAVEL_ROCK_EXTERIOR, 9, 37
	waitstate
	release
	end

VermilionPort_EventScript_ChoseFarawayIsland::
	closemessage
	delay 20
	checkitem ITEM_OLD_SEA_MAP
	bufferitemname STR_VAR_1, ITEM_OLD_SEA_MAP
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_FARAWAY_ISLAND_ENTRANCE, 13, 38
	waitstate
	release
	end	

@ Sem uso hoje: o Battle Frontier esta fora do jogo (ver o case 4 acima).
VermilionPort_EventScript_ChoseBattleFrontier::
	closemessage
	delay 20
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_BATTLE_FRONTIER_OUTSIDE_WEST, 20, 67
	waitstate
	release
	end	

VermilionPort_EventScript_Sailor_FirstSail::
	@ Em SoulGold da para chegar a Kanto a pe (Route 28), entao o jogador pode
	@ estreitar o barco por este lado. A viagem inaugural -- o conves, o avo e a
	@ neta -- e a de Olivine para Vermilion; daqui o barco so faz a travessia e
	@ libera o porto dos dois lados. Antes isto mandava para dentro do S.S.
	@ Aqua com VAR_SSAQUA_STATE 1: o navio "chegava em Vermilion" de novo, no
	@ mesmo porto de onde saiu.
	msgbox VermilionPort_Text_FlashTicket, MSGBOX_DEFAULT
	call VermilionPort_EventScript_EnterShip
	setvar VAR_SSAQUA_STATE, 7
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE, 8, 16
	waitstate
	release
	end

VermilionPort_EventScript_EnterShip::
	msgbox VermilionPort_Text_SailorGetOnBoard, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_VERMILIONMARINA_SAILOR, VermilionPort_Movement_SailorEnterBoat
	waitmovement 0
	playse SE_EXIT
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Movement_PlayerEnterBoat
	waitmovement 0
	special SpawnCameraObject
	playse SE_EXIT
	removeobject OBJ_EVENT_ID_PLAYER
	delay 60
	applymovement LOCALID_VERMILIONMARINA_SAILOR, VermilionPort_Movement_BoatLeave
	applymovement LOCALID_VERMILIONMARINA_BOAT, VermilionPort_Movement_BoatLeave
	waitmovement LOCALID_VERMILIONMARINA_BOAT
	setrespawn HEAL_LOCATION_VERMILION_CITY
	return

VermilionPort_EventScript_Sailor_Refused::
	msgbox VermilionPort_Text_ComeAgain, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_EventScript_Sailor_NoCredentials::
	msgbox VermilionPort_Text_NoPass, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_Movement_SailorEnterBoat:
	walk_down
	walk_down
	step_end

VermilionPort_Movement_PlayerEnterBoat:
	walk_down
	walk_down
	walk_in_place_down
	step_end

VermilionPort_Movement_BoatLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

VermilionPort_Text_SailorCantSail:
	.string "There's been a break-in at the\n"
	.string "Power Plant, so we cannot set sail\l"
	.string "until the Thief is found.$"

VermilionPort_Text_NoPass:
    .string "{PLAYER} tried to show the\n"
    .string "{STR_VAR_1}…\p"
    .string "…But no {STR_VAR_1}!\p"
    .string "Sorry!\n"
    .string "You may board only if you have an\l"
    .string "{STR_VAR_1}.$"

VermilionPort_Text_SailorGetOnBoard:
    .string "We're departing soon.\n"
    .string "Please get on board.$"

VermilionPort_Text_CantBoard:
    .string "Sorry. You can't board now.$"

VermilionPort_Text_WhereSail:
    .string "Where would you like to sail?$"

VermilionPort_Text_AskBoard:
    .string "Welcome to Fast Ship S.S.Aqua.\p"
    .string "Will you be boarding today?$"

VermilionPort_Text_AskTicket:
    .string "May I see your S.S.Ticket?$"

VermilionPort_Text_ComeAgain:
    .string "We hope to see you again!$"

VermilionPort_Text_FlashTicket:
    .string "{PLAYER} flashed the S.S.Ticket.\p"
    .string "That's it. Thank you!$"

VermilionPort_Text_NoTicket:
    .string "{PLAYER} tried to show the\n"
    .string "S.S.Ticket…\p"
    .string "…But no Ticket!\p"
    .string "Sorry!\n"
    .string "You may board only\l"
    .string "if you have an S.S.Ticket.$"

VermilionPort_Text_ChoiceOlivine:
	.string "Olivine$"

VermilionPort_Text_ChoiceSouthernIsland:
	.string "Southern Island$"

VermilionPort_Text_ChoiceBirthIsland:
	.string "Birth Island$"

VermilionPort_Text_ChoiceFarawayIsland:
	.string "Faraway Island$"

VermilionPort_Text_ChoiceNavelRock:
	.string "Navel Rock$"

VermilionPort_Text_ChoiceOneIsland:
	.string "One Island$"

VermilionPort_Text_ChoiceExit:
	.string "Exit$"
