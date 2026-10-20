SinjohRuins_RegirockRoom_MapScripts::
	.byte 0

SinjohRuins_RegirockRoom_EventScript_Regirock::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_REGIROCK, 80, LOCALID_SINJOHRUINS_REGIROCK, FLAG_HIDE_SINJOHRUINS_REGIROCK, 2
	release
	end

