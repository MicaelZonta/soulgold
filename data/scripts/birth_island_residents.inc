@ Quem ficou na Birth Island depois da historia.
@
@ Os dois saem do Nexus e ate agora nao existiam em lugar nenhum do mundo:
@ tinham ficha, time e sprite, e nenhuma presenca fora do loop pos-Necrozma.
@ A agenda esta em src/data/npc_schedule.h.
@
@   Seg, Qua, Sex   Colress
@   Ter, Qui        Soliera
@   Sab             os dois, que e o unico dia em que da para ver os dois
@                   discordando sobre o que fazer com a cratera
@   Dom             ninguem. A ilha fica so com o buraco.
@
@ Nenhum dos dois aparece antes de FLAG_BATTLED_DEOXYS: a cratera so vira
@ assunto depois que o jogador viu o que saiu dela. Essa flag ja existia.
@
@ FLAG_TEMP_B e FLAG_TEMP_C sao as de ocultacao (a Flannery usa a D). Zeram a
@ cada carregamento de mapa e o ON_TRANSITION sempre seta antes de decidir,
@ entao nenhuma flag persistente e gasta so para esconder.

BirthIsland_Residents_OnTransition::
	setflag FLAG_TEMP_B
	setflag FLAG_TEMP_C
	goto_if_unset FLAG_BATTLED_DEOXYS, BirthIsland_Residents_Nobody
	setvar VAR_0x8004, SCHEDULED_NPC_COLRESS
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, BirthIsland_Residents_ShowColress
	setvar VAR_0x8004, SCHEDULED_NPC_SOLIERA
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, BirthIsland_Residents_ShowSoliera
	return

BirthIsland_Residents_Nobody:
	return

BirthIsland_Residents_ShowColress:
	clearflag FLAG_TEMP_B
	cleartrainerflag TRAINER_COLRESS
	return

BirthIsland_Residents_ShowSoliera:
	clearflag FLAG_TEMP_C
	cleartrainerflag TRAINER_SOLIERA
	return

@ ---------------------------------------------------------------- Colress

BirthIsland_EventScript_Colress::
	lock
	faceplayer
	goto_if_set FLAG_MET_COLRESS, BirthIsland_EventScript_ColressKnown
	msgbox BirthIsland_Text_ColressFirst, MSGBOX_DEFAULT
	setflag FLAG_MET_COLRESS
	release
	end

BirthIsland_EventScript_ColressKnown:
	msgbox BirthIsland_Text_ColressKnown, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_COLRESS, BirthIsland_Text_ColressDefeat
	msgbox BirthIsland_Text_ColressAfter, MSGBOX_AUTOCLOSE
	end

BirthIsland_Text_ColressFirst:
	.string "{SPEAKER NAME_COLRESS}Everyone keeps telling me the\n"
	.string "interesting part left on a boat.\p"
	.string "The interesting part was never the\n"
	.string "creature. It was the thing that\l"
	.string "rewrote it.\p"
	.string "I have that on tape now. I am staying\n"
	.string "for the rest.$"

BirthIsland_Text_ColressKnown:
	.string "{SPEAKER NAME_COLRESS}Every Pokemon I carry was built or\n"
	.string "altered by someone.\p"
	.string "People say that like it is an\n"
	.string "accusation. Show me where the line is\l"
	.string "and I will stand on the other side of\l"
	.string "it.$"

BirthIsland_Text_ColressDefeat:
	.string "{SPEAKER NAME_COLRESS}Good. That was data.$"

BirthIsland_Text_ColressAfter:
	.string "{SPEAKER NAME_COLRESS}The paper is nearly finished.\p"
	.string "Nobody has told me to stop, and I\n"
	.string "would like you to notice that this is\l"
	.string "not the same as permission.$"

@ ---------------------------------------------------------------- Soliera

BirthIsland_EventScript_Soliera::
	lock
	faceplayer
	goto_if_set FLAG_MET_SOLIERA, BirthIsland_EventScript_SolieraKnown
	msgbox BirthIsland_Text_SolieraFirst, MSGBOX_DEFAULT
	setflag FLAG_MET_SOLIERA
	release
	end

BirthIsland_EventScript_SolieraKnown:
	msgbox BirthIsland_Text_SolieraKnown, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_SOLIERA, BirthIsland_Text_SolieraDefeat
	msgbox BirthIsland_Text_SolieraAfter, MSGBOX_AUTOCLOSE
	end

BirthIsland_Text_SolieraFirst:
	.string "{SPEAKER NAME_SOLIERA}He kept the recording. He will\n"
	.string "publish it.\p"
	.string "I am not here to arrest him. There is\n"
	.string "nothing to arrest him for.\p"
	.string "I am here because my people did this\n"
	.string "once, and we live under lamps now.$"

BirthIsland_Text_SolieraKnown:
	.string "{SPEAKER NAME_SOLIERA}The scientist wants to open the\n"
	.string "crater. I am here to make sure it\l"
	.string "stays a crater.\p"
	.string "We are both being reasonable. That is\n"
	.string "what worries me.$"

BirthIsland_Text_SolieraDefeat:
	.string "{SPEAKER NAME_SOLIERA}Acceptable. You are ready.$"

BirthIsland_Text_SolieraAfter:
	.string "{SPEAKER NAME_SOLIERA}Ready for what, I do not know yet.\n"
	.string "That is why I keep checking.$"
