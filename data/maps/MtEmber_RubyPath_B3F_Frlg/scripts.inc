MtEmber_RubyPath_B3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_RubyPath_B3F_OnTransition
	.byte 0

@ O script do rubi do FireRed (que nao entregava nada) saiu em 28/10/2026:
@ quem procura o rubi agora e a Olivia, nos dias uteis.
MtEmber_RubyPath_B3F_OnTransition:
	call MtEmberResidents_OnTransition
	end
