MtSilver_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MtSilver_2F_OnResume
	.byte 0

MtSilver_2F_OnResume::
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE, 17, 8
	end

MtSilver_2F_OnTransition: 
	callnative SetTimeBasedEncounters
	setescapewarp MAP_MT_SILVER_OUTSIDE, 17, 8
	end

MtSilver_2F_Item_AzureFlue::
	finditem ITEM_AZURE_FLUTE
	end
