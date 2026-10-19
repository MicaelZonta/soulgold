CeladonCity_DepartmentStore_4F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeladonDeptElevator_OnFrame
	.byte 0

CeladonDept_EventScript_Supernerd::
	msgbox CeladonDeptStore4F_Text_SuperNerd, MSGBOX_NPC
	end
CeladonDept_EventScript_Youngster::
	msgbox CeladonDeptStore4F_Text_Youngster, MSGBOX_NPC
	end
CeladonDept_EventScript_Directory::
	msgbox CeladonDeptStore4F_Text_Directory, MSGBOX_NPC
	end

CeladonDeptStore4F_Text_SuperNerd:
	.string "I'm here to buy SURF MAIL to send\n"
	.string "to my girlfriend.\p"
	.string "Wait, they're out of stock?$"

CeladonDeptStore4F_Text_Youngster:
	.string "This is the only place where you\n"
	.string "can buy LOVELY MAIL.\p"
	.string "At least it was. They are saying\n"
	.string "they are out of stock.$"

CeladonDeptStore4F_Text_Directory:
	.string "Express Yourself With Gifts!\p"
	.string "4F: WISEMAN GIFTS$"

@ Copiado do LilycoveCity_DepartmentStore_3F do HnS (fora da ROM no S):
LilycoveCity_DepartmentStore_3F_EventScript_ClerkLeft::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end
LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins:
	.2byte ITEM_PROTEIN
	.2byte ITEM_CALCIUM
	.2byte ITEM_IRON
	.2byte ITEM_ZINC
	.2byte ITEM_CARBOS
	.2byte ITEM_HP_UP
	pokemartlistend

