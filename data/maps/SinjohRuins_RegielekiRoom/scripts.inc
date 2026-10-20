SinjohRuins_RegielekiRoom_MapScripts::
	.byte 0

SinjohRuins_RegielekiRoom_EventScript_Regieleki::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_REGIELEKI, 80, LOCALID_SINJOHRUINS_REGIELEKI, FLAG_HIDE_SINJOHRUINS_REGIELEKI, 2
	release
	end
