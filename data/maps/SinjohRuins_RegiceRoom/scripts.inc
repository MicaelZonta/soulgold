SinjohRuins_RegiceRoom_MapScripts::
	.byte 0

SinjohRuins_RegiceRoom_EventScript_Regice::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_REGICE, 80, LOCALID_SINJOHRUINS_REGICE, FLAG_HIDE_SINJOHRUINS_REGICE, 2
	release
	end

