SeafoamIslands_B1F_MapScripts::
	.byte 0

SeafoamIslands_B1F_EventScript_Articuno::
	lock
	faceplayer
	msgbox SeafoamIslands_B1F_Text_ArticunoBattle
	delay 40
	bosslegendaryencounter SPECIES_ARTICUNO, 50, LOCALID_SEAFOAM_ARTICUNO, FLAG_HIDE_ARTICUNO, 2
	release
	end

SeafoamIslands_B1F_Text_ArticunoBattle:
	.string "Gyaoo!$"

SeafoamIslands_B1F_EventScript_Item_Ice_Beam::
    finditem ITEM_TM_ICE_BEAM
    end

