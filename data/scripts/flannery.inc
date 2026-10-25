@ Flannery nao mora em mapa nenhum: ela roda pelo mundo atras do calor.
@ A agenda esta em src/data/npc_schedule.h e quem responde e o special
@ IsScheduledNpcHere. Cada mapa anfitriao chama Flannery_OnTransition no
@ ON_TRANSITION dele e tem um object_event dela escondido por FLAG_TEMP_D.
@
@ FLAG_TEMP_D zera a cada carregamento de mapa (ClearTempFieldEventData, em
@ src/overworld.c, roda nos dois caminhos de entrada de mapa), entao nao ha
@ estado velho para dar errado e nenhuma flag persistente e gasta so para
@ esconder. A resposta e recalculada em toda entrada, como o NPC de domingo do
@ Goldenrod Dept. 5F.
@
@ Atencao: 0xD e o mesmo bit de FLAG_TEMP_HIDE_BUGSY (Route30) e e usado pelo
@ SunMoonAltar. Nao ha conflito porque o bit zera entre mapas e porque este
@ script sempre SETA antes de decidir - mas se a Flannery for parar num desses
@ mapas, troque o bit dela aqui e nos map.json.
@
@ FLAG_MET_FLANNERY so marca que a apresentacao ja aconteceu. Nao reusei a
@ FLAG_ENABLE_FLANNERY_MATCH_CALL: ligar ela poria a Flannery no telefone
@ dizendo que esta em Lavaridge, que nao e verdade neste jogo.

Flannery_OnTransition::
	setflag FLAG_TEMP_D
	setvar VAR_0x8004, SCHEDULED_NPC_FLANNERY
	special IsScheduledNpcHere
	goto_if_eq VAR_RESULT, TRUE, Flannery_EventScript_ShowHer
	return

Flannery_EventScript_ShowHer:
	clearflag FLAG_TEMP_D
	cleartrainerflag TRAINER_FLANNERY
	return

@ A rebatalha dela e presencial, nao por telefone: um lider que muda de lugar
@ nao pode dizer no Match Call onde esta. Achar ela e a graca. Como o
@ ON_TRANSITION limpa a flag de treinador em toda entrada, ela aceita de novo
@ cada vez que o jogador volta ao mapa em que ela esta hoje.
Flannery_EventScript_Roaming::
	lock
	faceplayer
	goto_if_set FLAG_MET_FLANNERY, Flannery_EventScript_Known
	msgbox Flannery_Text_FirstMeeting, MSGBOX_DEFAULT
	setflag FLAG_MET_FLANNERY
	release
	end

Flannery_EventScript_Known:
	msgbox Flannery_Text_Known, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_FLANNERY, Flannery_Text_RematchDefeat
	msgbox Flannery_Text_RematchAfter, MSGBOX_AUTOCLOSE
	end

Flannery_Text_FirstMeeting:
	.string "{SPEAKER NAME_FLANNERY}Don't tell me. You're the one walking\n"
	.string "around with a dead man's instrument,\l"
	.string "asking people what it means.\p"
	.string "My grandfather kept one like it on the\n"
	.string "wall. He said a mountain tells you\l"
	.string "everything, as long as you stop\l"
	.string "demanding that it use words.\p"
	.string "Take my number. If that needle moves,\n"
	.string "I want to hear about it.$"

Flannery_Text_Known:
	.string "{SPEAKER NAME_FLANNERY}People think fire and water are a\n"
	.string "quarrel.\p"
	.string "They're a conversation, and it began\n"
	.string "long before us.\p"
	.string "Want to argue about it properly?$"

Flannery_Text_RematchDefeat:
	.string "{SPEAKER NAME_FLANNERY}Ha!\p"
	.string "Grandfather would have liked you.$"

Flannery_Text_RematchAfter:
	.string "{SPEAKER NAME_FLANNERY}Call me again when you've found\n"
	.string "somewhere hotter.$"
