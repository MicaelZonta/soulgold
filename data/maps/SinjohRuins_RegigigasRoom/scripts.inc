SinjohRuins_RegigigasRoom_MapScripts::
	.byte 0

SinjohRuins_RegigigasRoom_EventScript_Regigigas::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_REGIGIGAS, 80, LOCALID_SINJOHRUINS_REGIGIGAS, FLAG_HIDE_SINJOHRUINS_REGIGIGAS, 3
	release
	end
