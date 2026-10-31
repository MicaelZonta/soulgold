MtEmber_RubyPath_B5F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtEmber_RubyPath_B5F_MapOnTransition
	.byte 0

@ O Pecharunt e a placa em braille: data/scripts/pecharunt.inc.
MtEmber_RubyPath_B5F_MapOnTransition:
	call MtEmber_RubyPath_B5F_OnTransition
	end
