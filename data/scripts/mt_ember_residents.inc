@ Os tres de Alola que vieram para o Mt. Ember: Guzma, Hau e Olivia.
@
@ Eram personagens do Nexus que nao tinham presenca nenhuma no mundo. Estes
@ sao as pessoas DESTE mundo (NEXUS_REGRAS R21): nao conhecem o jogador e tem
@ treinador proprio (TRAINER_GUZMA, TRAINER_HAU e TRAINER_KAHUNA_OLIVIA), separado do TRAINER_NEXUS_*.
@
@ A agenda de cada um esta em src/data/npc_schedule.h. Cada mapa anfitriao
@ tem o object_event deles escondido por uma FLAG_TEMP propria e chama
@ MtEmberResidents_OnTransition no ON_TRANSITION:
@
@   FLAG_TEMP_6  Guzma   cume (noite), encosta (dia util), Treasure Beach
@   FLAG_TEMP_7  Hau     Ember Spa (dia), One Island (tarde), Kindle Road
@   FLAG_TEMP_8  Olivia  Ruby Path B3F (dia util), Ember Spa (noite), One Island
@
@ As FLAG_TEMP zeram a cada carregamento de mapa e este script sempre SETA
@ antes de decidir, entao nenhuma flag persistente e gasta para esconder. A
@ batalha se repete a cada visita (cleartrainerflag), como a da Flannery.
@
@ O que eles dizem depende do estado do Pecharunt (Pecharunt_GetState, em
@ data/scripts/pecharunt.inc). Falas do gpt-6-sol pelo Codex.

MtEmberResidents_OnTransition::
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_7
	setflag FLAG_TEMP_8
	setvar VAR_0x8004, SCHEDULED_NPC_GUZMA
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, MtEmberResidents_ShowGuzma
	setvar VAR_0x8004, SCHEDULED_NPC_HAU
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, MtEmberResidents_ShowHau
	setvar VAR_0x8004, SCHEDULED_NPC_OLIVIA
	special IsScheduledNpcHere
	call_if_eq VAR_RESULT, TRUE, MtEmberResidents_ShowOlivia
	return

MtEmberResidents_ShowGuzma:
	clearflag FLAG_TEMP_6
	cleartrainerflag TRAINER_GUZMA
	return

MtEmberResidents_ShowHau:
	clearflag FLAG_TEMP_7
	cleartrainerflag TRAINER_HAU
	return

MtEmberResidents_ShowOlivia:
	clearflag FLAG_TEMP_8
	cleartrainerflag TRAINER_KAHUNA_OLIVIA
	return

@ ------------------------------------------------------------------ Guzma

MtEmberResidents_EventScript_Guzma::
	lock
	faceplayer
	call Pecharunt_GetState
	goto_if_eq VAR_RESULT, 1, MtEmberResidents_EventScript_GuzmaHunt
	goto_if_eq VAR_RESULT, 2, MtEmberResidents_EventScript_GuzmaAfter
	msgbox MtEmberResidents_Text_GuzmaBefore, MSGBOX_YESNO
	goto MtEmberResidents_EventScript_GuzmaAsk

MtEmberResidents_EventScript_GuzmaHunt:
	msgbox MtEmberResidents_Text_GuzmaHunt, MSGBOX_YESNO
	goto MtEmberResidents_EventScript_GuzmaAsk

MtEmberResidents_EventScript_GuzmaAfter:
	msgbox MtEmberResidents_Text_GuzmaAfter, MSGBOX_YESNO
MtEmberResidents_EventScript_GuzmaAsk:
	goto_if_eq VAR_RESULT, NO, MtEmberResidents_EventScript_GuzmaDecline
	trainerbattle_no_intro TRAINER_GUZMA, MtEmberResidents_Text_GuzmaDefeat
	msgbox MtEmberResidents_Text_GuzmaPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmberResidents_EventScript_GuzmaDecline:
	msgbox MtEmberResidents_Text_GuzmaDecline, MSGBOX_DEFAULT
	release
	end

@ -------------------------------------------------------------------- Hau

MtEmberResidents_EventScript_Hau::
	lock
	faceplayer
	call Pecharunt_GetState
	goto_if_eq VAR_RESULT, 1, MtEmberResidents_EventScript_HauHunt
	goto_if_eq VAR_RESULT, 2, MtEmberResidents_EventScript_HauAfter
	msgbox MtEmberResidents_Text_HauBefore, MSGBOX_YESNO
	goto MtEmberResidents_EventScript_HauAsk

MtEmberResidents_EventScript_HauHunt:
	msgbox MtEmberResidents_Text_HauHunt, MSGBOX_YESNO
	goto MtEmberResidents_EventScript_HauAsk

MtEmberResidents_EventScript_HauAfter:
	msgbox MtEmberResidents_Text_HauAfter, MSGBOX_YESNO
MtEmberResidents_EventScript_HauAsk:
	goto_if_eq VAR_RESULT, NO, MtEmberResidents_EventScript_HauDecline
	trainerbattle_no_intro TRAINER_HAU, MtEmberResidents_Text_HauDefeat
	msgbox MtEmberResidents_Text_HauPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmberResidents_EventScript_HauDecline:
	msgbox MtEmberResidents_Text_HauDecline, MSGBOX_DEFAULT
	release
	end

@ ----------------------------------------------------------------- Olivia

MtEmberResidents_EventScript_Olivia::
	lock
	faceplayer
	call Pecharunt_GetState
	goto_if_eq VAR_RESULT, 1, MtEmberResidents_EventScript_OliviaHunt
	goto_if_eq VAR_RESULT, 2, MtEmberResidents_EventScript_OliviaAfter
	msgbox MtEmberResidents_Text_OliviaBefore, MSGBOX_YESNO
	goto MtEmberResidents_EventScript_OliviaAsk

MtEmberResidents_EventScript_OliviaHunt:
	msgbox MtEmberResidents_Text_OliviaHunt, MSGBOX_YESNO
	goto MtEmberResidents_EventScript_OliviaAsk

MtEmberResidents_EventScript_OliviaAfter:
	msgbox MtEmberResidents_Text_OliviaAfter, MSGBOX_YESNO
MtEmberResidents_EventScript_OliviaAsk:
	goto_if_eq VAR_RESULT, NO, MtEmberResidents_EventScript_OliviaDecline
	trainerbattle_no_intro TRAINER_KAHUNA_OLIVIA, MtEmberResidents_Text_OliviaDefeat
	msgbox MtEmberResidents_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

MtEmberResidents_EventScript_OliviaDecline:
	msgbox MtEmberResidents_Text_OliviaDecline, MSGBOX_DEFAULT
	release
	end

@ ------------------------------------------------------------------ falas

MtEmberResidents_Text_GuzmaBefore:
	.string "{SPEAKER NAME_GUZMA}This mountain's good for training.\n"
	.string "No crowds. No pity. You in?$"

MtEmberResidents_Text_GuzmaHunt:
	.string "{SPEAKER NAME_GUZMA}Chains under this rock keep\n"
	.string "giving orders. Makes me sick.\p"
	.string "You wanna hit something?$"

MtEmberResidents_Text_GuzmaAfter:
	.string "{SPEAKER NAME_GUZMA}So you're the boss of bosses.\n"
	.string "Yeah, yeah. Prove it again?$"

MtEmberResidents_Text_GuzmaDecline:
	.string "{SPEAKER NAME_GUZMA}Fine. I'll train alone.\n"
	.string "Like usual.$"

MtEmberResidents_Text_GuzmaDefeat:
	.string "{SPEAKER NAME_GUZMA}Heh. Got bossed around again.\p"
	.string "Didn't hate it this time.$"

MtEmberResidents_Text_GuzmaPostBattle:
	.string "{SPEAKER NAME_GUZMA}Don't get cocky, boss.\n"
	.string "I'll catch up.$"

MtEmberResidents_Text_HauBefore:
	.string "{SPEAKER NAME_HAU}The spa kitchen makes great buns!\n"
	.string "Wanna battle before I eat more?$"

MtEmberResidents_Text_HauHunt:
	.string "{SPEAKER NAME_HAU}I found mochi by the pool.\n"
	.string "Way too sweet. Even for me.\p"
	.string "That was scary! Battle me?$"

MtEmberResidents_Text_HauAfter:
	.string "{SPEAKER NAME_HAU}The air smells normal again!\n"
	.string "How about a battle, then snacks?$"

MtEmberResidents_Text_HauDecline:
	.string "{SPEAKER NAME_HAU}No problem! More buns for me.\n"
	.string "That's a win too.$"

MtEmberResidents_Text_HauDefeat:
	.string "{SPEAKER NAME_HAU}Whoa! That woke me right up!\p"
	.string "Now I'm hungry again.$"

MtEmberResidents_Text_HauPostBattle:
	.string "{SPEAKER NAME_HAU}Good battle! The kitchen's open.\n"
	.string "Race you there?$"

MtEmberResidents_Text_OliviaBefore:
	.string "{SPEAKER NAME_OLIVIA}Ruby Path. No ruby.\n"
	.string "A jeweler finds that insulting.\p"
	.string "Will you help me cool off?$"

MtEmberResidents_Text_OliviaHunt:
	.string "{SPEAKER NAME_OLIVIA}The sweet smell comes from where\n"
	.string "the ruby ought to be.\p"
	.string "Curious. Shall we investigate?$"

MtEmberResidents_Text_OliviaAfter:
	.string "{SPEAKER NAME_OLIVIA}No ruby. Only a peach.\n"
	.string "A poor gem, but lovely color.\p"
	.string "Battle a disappointed jeweler?$"

MtEmberResidents_Text_OliviaDecline:
	.string "{SPEAKER NAME_OLIVIA}Sensibly cautious.\n"
	.string "I respect that in a customer.$"

MtEmberResidents_Text_OliviaDefeat:
	.string "{SPEAKER NAME_OLIVIA}A fine cut. Clean and bright.\p"
	.string "You do have an eye for value.$"

MtEmberResidents_Text_OliviaPostBattle:
	.string "{SPEAKER NAME_OLIVIA}No ruby today.\n"
	.string "Still, the hunt had sparkle.$"
