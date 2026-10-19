MtSilver_1F_MoltresRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_MoltresRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MtSilver_1F_MoltresRoom_OnResume
	.byte 0

MtSilver_1F_MoltresRoom_OnResume::
	setescapewarp MAP_MT_SILVER_OUTSIDE, 17, 8
	end

MtSilver_1F_MoltresRoom_OnTransition: 
	callnative SetTimeBasedEncounters
	end


MtSilver_1F_MoltresRoom_EventScript_Moltres::
	lock
	faceplayer
	msgbox SeafoamIslands_B1F_Text_ArticunoBattle
	delay 40
	bosslegendaryencounter SPECIES_MOLTRES, 50, LOCALID_MTSILVER_MOLTRES, FLAG_HIDE_MOLTRES, 2
	release
	end
