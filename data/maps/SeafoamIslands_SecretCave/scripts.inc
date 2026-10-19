.set LOCALID_SEAFOAMGROUDON, 1

SeafoamIslands_SecretCave_MapScripts::
	.byte 0

SeafoamIslands_SecretCave_EventScript_Groudon::
	lock
	faceplayer
	bosslegendaryencounter SPECIES_KORAIDON, 75, LOCALID_SEAFOAMGROUDON, FLAG_HIDE_KORAIDON, 3
	release
	end
