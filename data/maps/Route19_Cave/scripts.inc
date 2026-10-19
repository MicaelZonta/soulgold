.set LOCALID_ROUTE19CAVEKYOGRE, 1

Route19_Cave_MapScripts::
	.byte 0

Route19Cave_EventScript_Kyogre::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_MIRAIDON, 75, LOCALID_ROUTE19CAVEKYOGRE, FLAG_HIDE_MIRAIDON, 3
	release
	end
