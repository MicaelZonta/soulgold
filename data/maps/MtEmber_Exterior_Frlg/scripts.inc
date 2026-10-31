MtEmber_Exterior_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_Exterior_OnTransition
	.byte 0

@ Os restos da historia do FireRed (Rockets cavando atras do rubi, os tres
@ treinadores da encosta) foram apagados em 28/10/2026 com o retrofit do
@ Pecharunt: nenhum deles tinha objeto no mapa.
MtEmber_Exterior_OnTransition:
	setvar VAR_MT_EMBER_SIDE, 0
	call Flannery_OnTransition
	call MtEmberResidents_OnTransition
	end
