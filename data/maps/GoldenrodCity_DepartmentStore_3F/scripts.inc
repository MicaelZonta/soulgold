GoldenrodCity_DepartmentStore_3F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore3_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_3FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

@ Sells the Pikachu Cosplay Kit (Mom dresses Pikachu up with it). Always on
@ sale, with or without Mom's hint: the kit in the Bag is the only state.
GoldenrodDeptStore3_EventScript_Rocker::
	lock
	faceplayer
	checkitem ITEM_PIKACHU_COSPLAY_KIT, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodDeptStore3_EventScript_RockerHasKit
	msgbox GoldenrodDeptStore_Text_3FRocker, MSGBOX_DEFAULT
	showmoneybox 0, 0
	msgbox GoldenrodDeptStore_Text_3FRockerKitOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore3_EventScript_RockerDecline
	checkmoney 100000, 0
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore3_EventScript_RockerNoMoney
	checkitemspace ITEM_PIKACHU_COSPLAY_KIT, 1
	goto_if_eq VAR_RESULT, FALSE, GoldenrodDeptStore3_EventScript_RockerDecline
	removemoney 100000, 0
	updatemoneybox 0
	playse SE_SHOP
	hidemoneybox
	giveitem ITEM_PIKACHU_COSPLAY_KIT
	msgbox GoldenrodDeptStore_Text_3FRockerKitBought, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_RockerNoMoney::
	msgbox GoldenrodDeptStore_Text_3FRockerKitNoMoney, MSGBOX_DEFAULT
GoldenrodDeptStore3_EventScript_RockerDecline::
	hidemoneybox
	closemessage
	release
	end

GoldenrodDeptStore3_EventScript_RockerHasKit::
	msgbox GoldenrodDeptStore_Text_3FRockerHasKit, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_3FSuperNerd:
    .string "I, I, I'm really impatient!\p"
    .string "I use X Speed in battle to speed up\n"
    .string "my Pokémon.$"

GoldenrodDeptStore_Text_3FRocker:
    .string "Hey! When you battle, do you use X\n"
    .string "Special?\p"
    .string "It's awesome. It really jacks up\n"
    .string "Special Attack!$"

GoldenrodDeptStore_Text_3FRockerKitOffer:
    .string "…But you know what REALLY jacks\n"
    .string "things up? Pikachu in costume!\p"
    .string "Rock Star, Belle, Pop Star, all\n"
    .string "the caps… I've got a whole kit.\p"
    .string "¥100,000 and it's yours. Your\n"
    .string "Pikachu is gonna be a legend!$"

GoldenrodDeptStore_Text_3FRockerKitBought:
    .string "Rock on! Just take it to someone\n"
    .string "who's good with Pokémon and let\l"
    .string "them dress your Pikachu up!$"

GoldenrodDeptStore_Text_3FRockerKitNoMoney:
    .string "Aw, man. You're short on cash.\n"
    .string "The kit's not going anywhere!$"

GoldenrodDeptStore_Text_3FRockerHasKit:
    .string "How's that Pikachu of yours?\n"
    .string "Rocking the Rock Star outfit, I\l"
    .string "hope!$"

GoldenrodDeptStore_Text_3FDirectory:
    .string "For Victory Seekers\p"
    .string "3F Battle Collection$"


Goldenrod_3F_Berries_Shop::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Goldenrod_3f_Berries
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Goldenrod_3f_Berries:
	.2byte ITEM_ZEROMIN
	.2byte ITEM_POMEG_BERRY
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_QUALOT_BERRY
	.2byte ITEM_HONDEW_BERRY
	.2byte ITEM_GREPA_BERRY
	.2byte ITEM_TAMATO_BERRY
	pokemartlistend

Goldenrod_DepartmentStore_3F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Goldenrod_DepartmentStore_3F_Pokemart_Vitamins
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

Goldenrod_DepartmentStore_3F_EventScript_ClerkRight::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Goldenrod_DepartmentStore_3F_Pokemart_StatBoosters
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
Goldenrod_DepartmentStore_3F_Pokemart_StatBoosters:
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

Goldenrod_DepartmentStore_3F_EventScript_TriathleteM::
	msgbox Goldenrod_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon, MSGBOX_NPC
	end

Goldenrod_DepartmentStore_3F_EventScript_PokefanM::
	msgbox Goldenrod_DepartmentStore_3F_Text_WantMoreEndurance, MSGBOX_NPC
	end

Goldenrod_DepartmentStore_3F_EventScript_Woman::
	msgbox Goldenrod_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon, MSGBOX_NPC
	end

Goldenrod_DepartmentStore_3F_Text_ItemsBestForTougheningPokemon:
	.string "For quickly toughening up Pokémon,\n"
	.string "items are the best.\p"
	.string "Protein boosts Attack,\n"
	.string "and Calcium raises Sp. Atk.$"

Goldenrod_DepartmentStore_3F_Text_WantMoreEndurance:
	.string "I want my Pokémon to have more\n"
	.string "endurance.\p"
	.string "I'm trying to decide whether to raise\n"
	.string "Defense with Iron, or Sp. Def with Zinc.$"

Goldenrod_DepartmentStore_3F_Text_GaveCarbosToSpeedUpMon:
	.string "I gave a Carbos to my Pokémon,\n"
	.string "and its Speed went up.$"
