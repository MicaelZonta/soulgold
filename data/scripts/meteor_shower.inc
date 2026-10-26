@ A chuva de meteoros no cais de Vermilion, a noite.
@
@ E o gatilho narrativo da Birth Island: sem ter visto a chuva, a mulher de
@ Olivine nao entrega o Aurora Ticket, e sem o bilhete o marinheiro nao leva
@ ninguem para la. O portao de progresso continua sendo FLAG_IS_KANTO_CHAMPION,
@ que ja existia; a chuva so acrescenta o "quando".
@
@ Dispara por map_script_2 em VAR_TEMP_0, que zera a cada carregamento de mapa,
@ e as tres condicoes sao conferidas dentro do script - um map_script_2 so sabe
@ comparar uma var.
@
@ Falas do gpt-6-sol pelo Codex, com briefing de personalidade.

VermilionPort_OnFrame::
	map_script_2 VAR_TEMP_0, 0, VermilionPort_EventScript_MeteorShower
	.2byte 0

VermilionPort_EventScript_MeteorShower::
	setvar VAR_TEMP_0, 1
	goto_if_set FLAG_SAW_METEOR_SHOWER, VermilionPort_EventScript_ShowerEnd
	goto_if_unset FLAG_IS_KANTO_CHAMPION, VermilionPort_EventScript_ShowerEnd
	special GetTimeOfDayForScript
	goto_if_ne VAR_RESULT, SCRIPT_TIME_NIGHT, VermilionPort_EventScript_ShowerEnd
	lockall
	delay 30
	call VermilionPort_EventScript_Streak
	delay 25
	call VermilionPort_EventScript_Streak
	delay 15
	call VermilionPort_EventScript_Streak
	setvar VAR_0x8004, 1  @ pan vertical
	setvar VAR_0x8005, 1  @ pan horizontal
	setvar VAR_0x8006, 14  @ numero de tremores
	setvar VAR_0x8007, 4  @ atraso entre eles
	special ShakeCamera
	waitstate
	delay 40
	addobject LOCALID_VERMILION_PORT_LOOKER
	addobject LOCALID_VERMILION_PORT_ANABEL
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Movement_PlayerLooksDown
	waitmovement 0
	msgbox VermilionPort_Text_LookerFirst, MSGBOX_DEFAULT
	msgbox VermilionPort_Text_AnabelReading, MSGBOX_DEFAULT
	msgbox VermilionPort_Text_LookerChart, MSGBOX_DEFAULT
	msgbox VermilionPort_Text_AnabelSendoff, MSGBOX_DEFAULT
	msgbox VermilionPort_Text_LookerSendoff, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SAW_METEOR_SHOWER
	removeobject LOCALID_VERMILION_PORT_LOOKER
	removeobject LOCALID_VERMILION_PORT_ANABEL
	releaseall
	end

VermilionPort_EventScript_ShowerEnd:
	end

@ Um risco de luz: clarao curto sem fadescreen, que estragaria a paleta de
@ noite numa cena que volta pro mesmo mapa.
VermilionPort_EventScript_Streak:
	fadescreenswapbuffers FADE_TO_WHITE
	delay 4
	fadescreenswapbuffers FADE_FROM_WHITE
	return

VermilionPort_Movement_PlayerLooksDown:
	face_down
	step_end

@ Os dois so existem durante a cena; fora dela ficam escondidos por
@ FLAG_TEMP_B e FLAG_TEMP_C, que zeram a cada carregamento de mapa.
VermilionPort_EventScript_LookerShower::
	lock
	faceplayer
	msgbox VermilionPort_Text_LookerSendoff, MSGBOX_DEFAULT
	release
	end

VermilionPort_EventScript_AnabelShower::
	lock
	faceplayer
	msgbox VermilionPort_Text_AnabelSendoff, MSGBOX_DEFAULT
	release
	end

VermilionPort_Text_LookerFirst:
	.string "{SPEAKER NAME_LOOKER}Good evening. Is anyone hurt?\n"
	.string "Is anyone still out on the water?$"

VermilionPort_Text_AnabelReading:
	.string "{SPEAKER NAME_ANABEL}Measured: one strong pulse.\n"
	.string "It came as a light hit the sea.\p"
	.string "Felt: I knew that silence.\n"
	.string "I cannot tell you why.$"

VermilionPort_Text_LookerChart:
	.string "{SPEAKER NAME_LOOKER}They've corrected the chart.\n"
	.string "There's an island out there now.\p"
	.string "That patch was open sea before.\n"
	.string "Paperwork noticed first. Of course.$"

VermilionPort_Text_AnabelSendoff:
	.string "{SPEAKER NAME_ANABEL}Known: the boat leaves here.\n"
	.string "It sails to the new island.\p"
	.string "Unknown: what fell into the sea.\n"
	.string "Whether to go is your decision.$"

VermilionPort_Text_LookerSendoff:
	.string "{SPEAKER NAME_LOOKER}If you go, send us word.\n"
	.string "Just that you got back safely.$"
