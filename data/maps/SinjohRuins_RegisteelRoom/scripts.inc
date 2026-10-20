SinjohRuins_RegisteelRoom_MapScripts::
	.byte 0

SinjohRuins_RegisteelRoom_EventScript_Registeel::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_REGISTEEL, 80, LOCALID_SINJOHRUINS_REGISTEEL, FLAG_HIDE_SINJOHRUINS_REGISTEEL, 2
	release
	end
