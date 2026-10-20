SinjohRuins_RegidracoRoom_MapScripts::
	.byte 0

SinjohRuins_RegidragoRoom_EventScript_Regidrago::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_REGIDRAGO, 80, LOCALID_SINJOHRUINS_REGIDRAGO, FLAG_HIDE_SINJOHRUINS_REGIDRAGO, 2
	release
	end
