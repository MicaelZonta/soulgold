@ Navel Rock: as duas valvulas, o portao e o Volcanion.
@
@ Caminho linear, do conceito de 27/10/2026: o porto, a Gruta das Mares
@ (SeaBreach, onde se abre a brecha do mar), as Fontes Termais (FireVent,
@ onde se desentope a fenda), as Galerias de Vapor (SteamGallery, com o
@ portao de pedra) e o Santuario (SteamChamber). Mapas e tilesets saem do
@ gerador em dev_scripts/navel_rock_art.
@
@ A regra que o jogador tem que descobrir sozinho, porque o Blaine se recusa a
@ entregar: so o mar ou so o fogo nao fazem nada; os dois juntos enchem as
@ galerias de vapor e o portao cede.
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
	setvar VAR_0x8004, 1  @ pan vertical
	setvar VAR_0x8005, 1  @ pan horizontal
	setvar VAR_0x8006, 8  @ numero de tremores
	setvar VAR_0x8007, 4  @ atraso entre eles
	special ShakeCamera
	waitstate
	setflag FLAG_NAVELROCK_FIRE_VENT
	call NavelRock_FireVent_SetOpen
	special DrawWholeMapView
	msgbox NavelRock_Text_VentOpened, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_FireVentOpen:
	msgbox NavelRock_Text_VentOpened, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ O map.bin guarda a fenda entupida; aberta, ela vira geiser (o vapor sobe
@ ate a rocha de cima, na camada que cobre o jogador).
NavelRock_FireVent_OnLoad::
	goto_if_unset FLAG_NAVELROCK_FIRE_VENT, NavelRock_EventScript_VentStays
	call NavelRock_FireVent_SetOpen
NavelRock_EventScript_VentStays:
	end

NavelRock_FireVent_SetOpen:
	setmetatile 3, 1, METATILE_NavelRock_HotSprings_VentOpen_r0c1, TRUE
	setmetatile 3, 2, METATILE_NavelRock_HotSprings_VentOpen_r1c1, FALSE
	setmetatile 2, 3, METATILE_NavelRock_HotSprings_VentOpen_r2c0, FALSE
	setmetatile 3, 3, METATILE_NavelRock_HotSprings_VentOpen_r2c1, TRUE
	setmetatile 4, 3, METATILE_NavelRock_HotSprings_VentOpen_r2c2, FALSE
	return

@ ------------------------------------------------------- a brecha, no fundo

NavelRock_EventScript_SeaBreach::
	lockall
	goto_if_set FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_SeaBreachOpen
	msgbox NavelRock_Text_BreachClosed, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1  @ pan vertical
	setvar VAR_0x8005, 1  @ pan horizontal
	setvar VAR_0x8006, 8  @ numero de tremores
	setvar VAR_0x8007, 4  @ atraso entre eles
	special ShakeCamera
	waitstate
	setflag FLAG_NAVELROCK_SEA_BREACH
	call NavelRock_SeaBreach_SetOpen
	special DrawWholeMapView
	msgbox NavelRock_Text_BreachOpened, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_SeaBreachOpen:
	msgbox NavelRock_Text_BreachOpened, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ O map.bin guarda a rachadura fechada; aberta, um buraco com o mar escorrendo.
NavelRock_SeaBreach_OnLoad::
	goto_if_unset FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_BreachStays
	call NavelRock_SeaBreach_SetOpen
NavelRock_EventScript_BreachStays:
	end

NavelRock_SeaBreach_SetOpen:
	setmetatile 4, 1, METATILE_NavelRock_TideGrotto_BreachOpen_r0c0, TRUE
	setmetatile 4, 2, METATILE_NavelRock_TideGrotto_BreachOpen_r1c0, FALSE
	return

@ ------------------------------------------------------ o portao das galerias

@ O map.bin guarda o portao fechado (a porta em 14,6 bloqueada). Ele so abre
@ no carregamento do mapa, entao basta a segunda valvula ter sido aberta em
@ outra sala.
NavelRock_SteamGallery_OnLoad::
	goto_if_unset FLAG_NAVELROCK_FIRE_VENT, NavelRock_EventScript_GateStays
	goto_if_unset FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_GateStays
	setmetatile 12, 3, METATILE_NavelRock_SteamGallery_GateOpen_r0c0, TRUE
	setmetatile 13, 3, METATILE_NavelRock_SteamGallery_GateOpen_r0c1, TRUE
	setmetatile 14, 3, METATILE_NavelRock_SteamGallery_GateOpen_r0c2, FALSE
	setmetatile 15, 3, METATILE_NavelRock_SteamGallery_GateOpen_r0c3, FALSE
	setmetatile 16, 3, METATILE_NavelRock_SteamGallery_GateOpen_r0c4, FALSE
	setmetatile 12, 4, METATILE_NavelRock_SteamGallery_GateOpen_r1c0, TRUE
	setmetatile 13, 4, METATILE_NavelRock_SteamGallery_GateOpen_r1c1, TRUE
	setmetatile 14, 4, METATILE_NavelRock_SteamGallery_GateOpen_r1c2, TRUE
	setmetatile 15, 4, METATILE_NavelRock_SteamGallery_GateOpen_r1c3, TRUE
	setmetatile 16, 4, METATILE_NavelRock_SteamGallery_GateOpen_r1c4, TRUE
	setmetatile 12, 5, METATILE_NavelRock_SteamGallery_GateOpen_r2c0, TRUE
	setmetatile 13, 5, METATILE_NavelRock_SteamGallery_GateOpen_r2c1, TRUE
	setmetatile 14, 5, METATILE_NavelRock_SteamGallery_GateOpen_r2c2, TRUE
	setmetatile 15, 5, METATILE_NavelRock_SteamGallery_GateOpen_r2c3, TRUE
	setmetatile 16, 5, METATILE_NavelRock_SteamGallery_GateOpen_r2c4, TRUE
	setmetatile 12, 6, METATILE_NavelRock_SteamGallery_GateOpen_r3c0, TRUE
	setmetatile 13, 6, METATILE_NavelRock_SteamGallery_GateOpen_r3c1, TRUE
	setmetatile 14, 6, METATILE_NavelRock_SteamGallery_GateOpen_r3c2, FALSE
	setmetatile 15, 6, METATILE_NavelRock_SteamGallery_GateOpen_r3c3, TRUE
	setmetatile 16, 6, METATILE_NavelRock_SteamGallery_GateOpen_r3c4, TRUE
NavelRock_EventScript_GateStays:
	end

NavelRock_EventScript_Gate::
	goto_if_unset FLAG_NAVELROCK_FIRE_VENT, NavelRock_EventScript_GateNoFire
	goto_if_unset FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_GateNoSea
	end

NavelRock_EventScript_GateNoFire:
	lockall
	goto_if_set FLAG_NAVELROCK_SEA_BREACH, NavelRock_EventScript_GateWet
	msgbox NavelRock_Text_GateSealed, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_GateWet:
	msgbox NavelRock_Text_GateWet, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

NavelRock_EventScript_GateNoSea:
	lockall
	msgbox NavelRock_Text_GateDry, MSGBOX_DEFAULT
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

NavelRock_Text_GateSealed:
	.string "Stone doors fill the passage.\n"
	.string "They are cold, and will not move.$"

NavelRock_Text_GateWet:
	.string "Seawater pools against the doors.\n"
	.string "It is cold. Nothing pushes back.$"

NavelRock_Text_GateDry:
	.string "Dry heat leaks through the seams.\n"
	.string "The stone is warm, but it holds.$"
