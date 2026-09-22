UltraSpaceArena_MapScripts::
	.byte 0

@ South rift, bottom row of the pad: back to the Sun and Moon Altar.
@ The way IN (the altar portal after Necrozma) belongs to the altar event;
@ until then this map is reached only through the debug menu. Arrival from
@ the portal should land on (10,19), one row above this trigger.
UltraSpaceArena_EventScript_SouthRift::
	lockall
	playse SE_WARP_IN
	warp MAP_SUN_MOON_ALTAR, 14, 10
	waitstate
	releaseall
	end
