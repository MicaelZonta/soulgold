AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_NONE, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "{SPEAKER NAME_DAN}While searching for treasures,\n"
	.string "we discovered a Trainer!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "{SPEAKER NAME_DAN}We couldn't win even though\n"
	.string "we worked together…$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "{SPEAKER NAME_DAN}We can't find any treasures…\n"
	.string "I wonder if someone got them already?$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "{SPEAKER NAME_DAN}You don't even have two Pokémon.\n"
	.string "You can't expect to beat us like that.$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "{SPEAKER NAME_KIRA}Oh?\n"
	.string "We were searching for treasures.\l"
	.string "But we discovered a Trainer instead!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "{SPEAKER NAME_KIRA}Ooh, so strong!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "{SPEAKER NAME_KIRA}Where could the treasures be?\p"
	.string "I've already decided what I'm buying\n"
	.string "when we find the treasures!$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "{SPEAKER NAME_KIRA}Oh, you don't have two Pokémon?\n"
	.string "We'll have to battle some other time!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "{SPEAKER NAME_KIRA}Oh, you make me so angry!\n"
	.string "I'm going to register you for that!$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "{SPEAKER NAME_DAN}We've been searching for\n"
	.string "treasures all this time.\p"
	.string "Our Pokémon have grown stronger, too.\n"
	.string "Let us show you, okay?$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "{SPEAKER NAME_DAN}You're strong, as usual!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "{SPEAKER NAME_DAN}We can't find any treasures,\n"
	.string "we lose at Pokémon…\p"
	.string "I want to go home… But if I say that,\n"
	.string "she gets all angry with me…$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "{SPEAKER NAME_DAN}You don't even have two Pokémon.\n"
	.string "You can't expect to beat us like that.$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "{SPEAKER NAME_KIRA}Oh? We meet again!\p"
	.string "Just like us, you still haven't given up\n"
	.string "searching for treasures, have you?\p"
	.string "Want to make it so the loser has\n"
	.string "to give up searching?$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "{SPEAKER NAME_KIRA}Oh, we lost again…$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "{SPEAKER NAME_KIRA}We're not leaving until we raise\n"
	.string "our Pokémon some more and we find\l"
	.string "the treasures here!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "{SPEAKER NAME_KIRA}Oh, you don't have two Pokémon?\n"
	.string "We'll have to battle some other time!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "I'm not good at swimming,\n"
	.string "but I am good at battles!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Oops.\n"
	.string "That didn't go very well.$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Walking around barefoot in this ship\n"
	.string "is kind of gross.$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Strength and compassion…\n"
	.string "Those are a Trainer's treasures!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Ah, there is something about you\n"
	.string "that sparkles.$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "In a cabin somewhere on board,\n"
	.string "I saw something sparkle.$"
