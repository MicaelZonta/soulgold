@ Navel Rock: as duas valvulas e o Volcanion.
@
@ A geometria e a do Navel Rock original de proposito - nos jogos antigos o
@ ramo de cima e o Ho-Oh e o de baixo e o Lugia, e aqui os dois ja tem casa.
@ Entao a forma fica e o significado muda: em cima o calor, embaixo o mar, e a
@ criatura onde os dois se encontram.
@
@ A regra que o jogador tem que descobrir sozinho, porque o Blaine se recusa a
@ entregar: so a fenda e a camara assa seca; so a brecha e ela alaga fria; as
@ duas, e enche de vapor.
@
@ FLAG_HIDE_VOLCANION e recalculada em TODO ON_TRANSITION da camara, entao
@ nunca e um "ja vi" velho - e quem segura o reaparecimento e
@ FLAG_CAUGHT_VOLCANION. Perder ou fugir nao mexe em nenhuma das duas, entao a
@ luta pode ser repetida. Mesma receita do Keldeo do Mt. Silver.
@
@ Falas do gpt-6-sol pelo Codex.

@ ---------------------------------------------------------- a fenda, no alto

NavelRock_EventScript_FireVent::
	lockall
	goto_if_set FLAG_NAVELROCK_FIRE_VENT, NavelRock_EventScript_FireVentOpen
	msgbox NavelRock_Text_VentBlocked, MSGBOX_DEFAULT
	closemessage
	special ShakeCamera
	waitstate
	msgbox NavelRock_Text_VentOpened, MSGBOX_DEFAULT
	setflag FLAG_NAVELROCK_FIRE_VENT
	closemessage
	releaseall
	end

NavelRock_EventScript_FireVentOpen:
	msgbox NavelRock_Text_VentOpened, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ ------------------------------------------------------- a brecha, no fundo

NavelRock_EventScript_SeaBreach::
	lockall
	goto_if_set FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_SeaBreachOpen
	msgbox NavelRock_Text_BreachClosed, MSGBOX_DEFAULT
	closemessage
	special ShakeCamera
	waitstate
	msgbox NavelRock_Text_BreachOpened, MSGBOX_DEFAULT
	setflag FLAG_NAVELROCK_SEA_BREACH
	closemessage
	releaseall
	end

NavelRock_EventScript_SeaBreachOpen:
	msgbox NavelRock_Text_BreachOpened, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ -------------------------------------------------------- a Camara do Vapor

NavelRock_SteamChamber_OnTransition::
	setflag FLAG_HIDE_VOLCANION
	goto_if_set FLAG_CAUGHT_VOLCANION, NavelRock_EventScript_ChamberDone
	goto_if_unset FLAG_NAVELROCK_FIRE_VENT, NavelRock_EventScript_ChamberDone
	goto_if_unset FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_ChamberDone
	clearflag FLAG_HIDE_VOLCANION
	return

NavelRock_EventScript_ChamberDone:
	return

@ A narracao do estado da camara toca uma vez por visita: VAR_TEMP_0 zera a
@ cada carregamento de mapa.
NavelRock_SteamChamber_OnFrame::
	map_script_2 VAR_TEMP_0, 0, NavelRock_EventScript_ChamberLook
	.2byte 0

NavelRock_EventScript_ChamberLook::
	setvar VAR_TEMP_0, 1
	goto_if_set FLAG_CAUGHT_VOLCANION, NavelRock_EventScript_LookEnd
	goto_if_unset FLAG_NAVELROCK_FIRE_VENT, NavelRock_EventScript_LookNoVent
	goto_if_unset FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_LookDry
	lockall
	msgbox NavelRock_Text_ChamberSteam, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_LookDry:
	lockall
	msgbox NavelRock_Text_ChamberDry, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_LookNoVent:
	goto_if_unset FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_LookEnd
	lockall
	msgbox NavelRock_Text_ChamberFlooded, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_LookEnd:
	end

NavelRock_EventScript_Volcanion::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_VOLCANION, 70, LOCALID_NAVELROCK_VOLCANION, FLAG_HIDE_VOLCANION, 3, SPECIES_NONE, 110
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, NavelRock_EventScript_VolcanionGone
	setflag FLAG_CAUGHT_VOLCANION
NavelRock_EventScript_VolcanionGone:
	release
	end

@ ---------------------------------------------------------------- narracao

NavelRock_Text_VentBlocked:
	.string "Cold rock seals the shaft above.\n"
	.string "No warmth comes through the cracks.$"

NavelRock_Text_VentOpened:
	.string "The last black rock gives way.\n"
	.string "Heat climbs the open shaft.$"

NavelRock_Text_BreachClosed:
	.string "The sea presses on a stone seam.\n"
	.string "Not a drop slips through.$"

NavelRock_Text_BreachOpened:
	.string "The seal breaks under your hand.\n"
	.string "Seawater thunders down the shaft.$"

NavelRock_Text_ChamberDry:
	.string "The spring pool has boiled away.\n"
	.string "White rings stain the bare rock.\p"
	.string "Cracks split the island's stone.\n"
	.string "You cannot stand here for long.$"

NavelRock_Text_ChamberFlooded:
	.string "Cold water covers the island.\n"
	.string "The pool lies flat as glass.\p"
	.string "Cold seeps through your soles.\n"
	.string "Nothing stirs beneath the water.$"

NavelRock_Text_ChamberSteam:
	.string "Hot water meets the rising heat.\n"
	.string "Steam swallows the rock island.\p"
	.string "Something shifts inside the white.\n"
	.string "Twin jets tear the fog apart.$"
