@ Berry Master: the steeds' paths (REI_DA_COLHEITA.md section 15, plan parts
@ 14 and 15). VAR_HARVEST_KING 10 -> 12 (white path, Greenfield) and
@ 11 -> 13 (dark path, the Brass Tower memory).

@ ---------------------------------------------------------------- white path
@ Mahogany Gym, after the Glastrier (section 15.4): Pryce heard Molly.
BerryGarden_EventScript_PryceCoat::
	msgbox BerryGarden_Text_PryceCoat, MSGBOX_DEFAULT
	return

BerryGarden_Text_PryceCoat:
	.string "...She said the invitation stands?\p"
	.string "Hm. I'll need a better coat.$"
