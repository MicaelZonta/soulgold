Route27_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route27_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route27_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route27_EventScript_BaobaCall::
	setspeaker Route27_Text_BaobaName
	pokenavcall BlackthornCity_Text_BaobaCall
	waitmessage
	delay 30
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
    setvar VAR_ROUTE27_BAOBA_CALL, 1
	end

Route27_Text_BaobaName:
	.string "Baoba$"

Route27_EventScript_FirstSteps::
    lock
    playse SE_PIN
    setflag FLAG_VISITED_KANTO
    applymovement2 LOCALID_ROUTE27_FATMAN, Common_Movement_ExclamationMark
    turnobject LOCALID_ROUTE27_FATMAN, DIR_WEST
    delay 30
    getplayerxy VAR_TEMP_0, VAR_TEMP_1
    call_if_eq VAR_TEMP_1, 24, Route27_EventScript_FirstStepsWalkTop
    call_if_eq VAR_TEMP_1, 25, Route27_EventScript_FirstStepsWalkBot

    msgbox Route27_Text_FisherHey, MSGBOX_DEFAULT
    msgbox Route27_Text_FisherMessage, MSGBOX_DEFAULT
    closemessage
    turnobject LOCALID_ROUTE27_FATMAN, DIR_SOUTH

    @integrated flagheap
    setflag FLAG_HIDE_VICTORY_ROAD_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK
    
    clearflag FLAG_GOT_TM_SANDSTORM
    clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
    clearflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD

    setvar VAR_ROUTE27_STATE, 1
    release
    end

Route27_EventScript_FirstStepsWalkTop::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkTop
    waitmovement 0
    return
Route27_EventScript_FirstStepsWalkBot::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkBot
    waitmovement 0
    return

Route27_Movement_WalkTop:
    face_left
    walk_left
    step_end

Route27_Movement_WalkBot:
    walk_down
    walk_left
    step_end

Route27_EventScript_Item_Moonstone::
    finditem ITEM_MOON_STONE
    end

Route27_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

Route27_EventScript_Item_DragonClaw::
    finditem ITEM_TM_DRAGON_CLAW
    end

Route27_EventScript_Item_Destiny_Knot::
    finditem ITEM_DESTINY_KNOT
    end

Route27_EventScript_Fatman::
    msgbox Route27_Text_FisherMessage, MSGBOX_NPC
    end

Route27_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, Route27_Text_CooltrainermBlakeSeen, Route27_Text_CooltrainermBlakeBeaten
	msgbox Route27_Text_CooltrainermBlakeAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Brian::
	trainerbattle_single TRAINER_BRIAN, Route27_Text_CooltrainermBrianSeen, Route27_Text_CooltrainermBrianBeaten
	msgbox Route27_Text_CooltrainermBrianAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Reena::
	trainerbattle_single TRAINER_REENA, Route27_Text_CooltrainerfReenaSeen, Route27_Text_CooltrainerfReenaBeaten, Route27_EventScript_RegisterReena
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchReena
	msgbox Route27_Text_CooltrainerfReenaAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterReena::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_ReenaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_REENA
	release
	end

Route27_EventScript_RematchReena::
	trainerbattle_rematch TRAINER_REENA, Route27_Text_ReenaRematchIntro, Route27_Text_ReenaRematchDefeat
	msgbox Route27_Text_ReenaPostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Megan::
	trainerbattle_single TRAINER_MEGAN, Route27_Text_CooltrainerfMeganSeen, Route27_Text_CooltrainerfMeganBeaten
	msgbox Route27_Text_CooltrainerfMeganAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Gilbert::
	trainerbattle_single TRAINER_GILBERT, Route27_Text_PsychicGilbertSeen, Route27_Text_PsychicGilbertBeaten
	msgbox Route27_Text_PsychicGilbertAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Jose::
	trainerbattle_single TRAINER_JOSE, Route27_Text_BirdKeeperJoseSeen, Route27_Text_BirdKeeperJoseBeaten, Route27_EventScript_RegisterJose
	goto_if_set FLAG_JOSE_HAS_ITEM, Route27_EventScript_JoseGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchJose
	msgbox Route27_Text_BirdKeeperJoseAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterJose::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_JoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOSE
	release
	end

Route27_EventScript_RematchJose::
	trainerbattle_rematch TRAINER_JOSE, Route27_Text_JoseRematchIntro, Route27_Text_JoseRematchDefeat
	msgbox Route27_Text_JosePostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseGiveItem::
	msgbox Route27_Text_JoseHasItem, MSGBOX_DEFAULT
	giveitem VAR_JOSE_ITEM
	goto_if_eq VAR_RESULT, FALSE, Route27_EventScript_JoseNoRoom
	clearflag FLAG_JOSE_HAS_ITEM
	msgbox Route27_Text_JoseGaveItem, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseNoRoom::
	msgbox Route27_Text_JoseNoRoom, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Scott::
	trainerbattle_single TRAINER_SCOTT, Route27_Text_FisherScottSeen, Route27_Text_FisherScottBeaten
	msgbox Route27_Text_FisherScottAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_TohjoFallsSign::
    msgbox TohjoFalls_Text_Sign, MSGBOX_SIGN
    end

Route27_Text_FisherHey:
    .string "Hey!$"

Route27_Text_FisherMessage:
    .string "Do you know what you just did?\p"
    .string "You've taken your first step into\n"
    .string "Kanto.\p"
    .string "Check your Pokégear Map and see.$"

Route27_Text_CooltrainermBlakeSeen:
    .string "You look pretty strong.\n"
    .string "Let me battle you!$"

Route27_Text_CooltrainermBlakeBeaten:
    .string "Yow!$"

Route27_Text_CooltrainermBlakeAfter:
    .string "If you prevail on this harsh trek,\n"
    .string "the truth will be revealed!\p"
    .string "Heh, sorry, I just wanted to say\n"
    .string "something cool.$"

Route27_Text_CooltrainermBrianSeen:
    .string "Hm? You're good, aren't you?$"

Route27_Text_CooltrainermBrianBeaten:
    .string "Just as I thought!$"

Route27_Text_CooltrainermBrianAfter:
    .string "A good trainer can recognize other\n"
    .string "good trainers.$"

Route27_Text_CooltrainerfReenaSeen:
    .string "You shouldn't underestimate the\n"
    .string "wild Pokémon in these parts.$"

Route27_Text_CooltrainerfReenaBeaten:
    .string "Oh! You're much too strong!$"

Route27_Text_CooltrainerfReenaAfter:
    .string "You're just a kid, but you're not\n"
    .string "to be underestimated either.$"

Route27_Text_ReenaRegister:
    .string "You're just a kid, but you're not\n"
    .string "to be underestimated either.$"

Route27_Text_ReenaRematchIntro:
    .string "You shouldn't underestimate the\n"
    .string "wild Pokémon in these parts.$"

Route27_Text_ReenaRematchDefeat:
    .string "Oh! You're much too strong!$"

Route27_Text_ReenaPostRematch:
    .string "You're just a kid, but you're not\n"
    .string "to be underestimated either.$"

Route27_Text_CooltrainerfMeganSeen:
    .string "It's rare to see anyone come here.\p"
    .string "Are you training on your own?$"

Route27_Text_CooltrainerfMeganBeaten:
    .string "Oh! You're really strong!$"

Route27_Text_CooltrainerfMeganAfter:
    .string "I'm checking out pre- and post-\n"
    .string "evolution Pokémon.\p"
    .string "Evolution really does make\n"
    .string "Pokémon stronger.\p"
    .string "But evolved forms also learn\n"
    .string "moves later on.$"

Route27_Text_PsychicGilbertSeen:
    .string "Don't say a thing!\p"
    .string "Let me guess what you're thinking.\p"
    .string "Mmmmmmm…\p"
    .string "I got it! You're on the Pokémon\n"
    .string "League challenge!$"

Route27_Text_PsychicGilbertBeaten:
    .string "You're too much!$"

Route27_Text_PsychicGilbertAfter:
    .string "With your skills, you'll do well at\n"
    .string "the League.\p"
    .string "That's what my premonition says.$"

Route27_Text_BirdKeeperJoseSeen:
    .string "Tweet! Tweet! Tetweet!$"

Route27_Text_BirdKeeperJoseBeaten:
    .string "Tweet!$"

Route27_Text_BirdKeeperJoseAfter:
    .string "Bird Keepers like me mimic bird\n"
    .string "whistles to command Pokémon.$"

Route27_Text_JoseRegister:
    .string "Bird Keepers like me mimic bird\n"
    .string "whistles to command Pokémon.$"

Route27_Text_JoseRematchIntro:
    .string "Tweet! Tweet! Tetweet!$"

Route27_Text_JoseRematchDefeat:
    .string "Tweet!$"

Route27_Text_JosePostRematch:
    .string "Bird Keepers like me mimic bird\n"
    .string "whistles to command Pokémon.$"

Route27_Text_JoseHasItem:
    .string "Hey! I found something\n"
    .string "shiny while bird-watching!\p"
    .string "Here, you can have it!$"

Route27_Text_JoseGaveItem:
    .string "I find all sorts of things\n"
    .string "out here on Route 27.\p"
    .string "I'll let you know if I find\n"
    .string "anything else!$"

Route27_Text_JoseNoRoom:
    .string "Hmm, your Bag is full.\p"
    .string "Come back when you have room.$"

TohjoFalls_Text_Sign:
    .string "Tohjo Falls\p"
    .string "the Link Between Kanto and Johto$"

Route27_Text_FisherScottSeen:
    .string "I'm feeling great today!\p"
    .string "I feel like I could boot even the\n"
    .string "League Champ!$"

Route27_Text_FisherScottBeaten:
    .string "No! Not in this battle!$"

Route27_Text_FisherScottAfter:
    .string "Just like in fishing, it's all over\n"
    .string "in Pokémon if you give up.$"

Route27_RouteExpert::
	lock
	faceplayer
	goto_if_set FLAG_ROUTE27_EXPERT, Route27_RouteExpert_2
	msgbox Route27_RouteExpert_Text_1
	goto_if_set FLAG_ROUTE27_EXPERT_QUALIFIED, Route27_RouteExpert_5
	checktrainerflag TRAINER_BLAKE
	goto_if 1, Route27_RouteExpert_9
Route27_RouteExpert_4:
	release
	end

Route27_RouteExpert_2:
	setflag FLAG_ROUTE27_EXPERT_QUALIFIED
	msgbox Route27_RouteExpert_Text_0
	release
	end

Route27_RouteExpert_5:
	setflag FLAG_ROUTE27_EXPERT_QUALIFIED
	playse SE_PIN
	applymovement LOCALID_ROUTE27_EXPERT, Common_Movement_ExclamationMark
	waitse
	msgbox Route27_RouteExpert_Text_2
	trainerbattle_no_intro TRAINER_CHOICE_BAND_EXPERT, Route27_RouteExpert_Text_3
	msgbox Route27_RouteExpert_Text_4
	giveitem ITEM_CHOICE_BAND
	setflag FLAG_ROUTE27_EXPERT
	addvar VAR_ROUTE_EXPERTS_DEFEATED, 1
	special Achievement_CheckAll
	msgbox Route27_RouteExpert_Text_0
	goto Route27_RouteExpert_4

Route27_RouteExpert_8:
	checktrainerflag TRAINER_REENA
	goto_if 1, Route27_RouteExpert_13
	goto Route27_RouteExpert_4

Route27_RouteExpert_9:
	checktrainerflag TRAINER_BRIAN
	goto_if 1, Route27_RouteExpert_8
	goto Route27_RouteExpert_4

Route27_RouteExpert_12:
	checktrainerflag TRAINER_GILBERT
	goto_if 1, Route27_RouteExpert_17
	goto Route27_RouteExpert_4

Route27_RouteExpert_13:
	checktrainerflag TRAINER_MEGAN
	goto_if 1, Route27_RouteExpert_12
	goto Route27_RouteExpert_4

Route27_RouteExpert_16:
	checktrainerflag TRAINER_SCOTT
	goto_if 1, Route27_RouteExpert_21
	goto Route27_RouteExpert_4

Route27_RouteExpert_17:
	checktrainerflag TRAINER_JOSE
	goto_if 1, Route27_RouteExpert_16
	goto Route27_RouteExpert_4

Route27_RouteExpert_20:
	checktrainerflag TRAINER_GAVEN
	goto_if 1, Route27_RouteExpert_25
	goto Route27_RouteExpert_4

Route27_RouteExpert_21:
	checktrainerflag TRAINER_JAKE
	goto_if 1, Route27_RouteExpert_20
	goto Route27_RouteExpert_4

Route27_RouteExpert_24:
	checktrainerflag TRAINER_BETH
	goto_if 1, Route27_RouteExpert_28
	goto Route27_RouteExpert_4

Route27_RouteExpert_25:
	checktrainerflag TRAINER_JOYCE
	goto_if 1, Route27_RouteExpert_24
	goto Route27_RouteExpert_4

Route27_RouteExpert_28:
	checktrainerflag TRAINER_RICHARD
	goto_if 1, Route27_RouteExpert_5
	goto Route27_RouteExpert_4


Route27_RouteExpert_Text_0:
	.string "Choice items lock you into one move,\n"
	.string "but they offset that cost with a\l"
	.string "big boost to your battling power.$"

Route27_RouteExpert_Text_1:
	.string "The final stretch before the mighty\n"
	.string "Elite Four extends before you now.\p"
	.string "Here you will only find the most\n"
	.string "skilled trainers in Johto who\l"
	.string "aspire to take on the challenge.\p"
	.string "If you can overcome them all, find\n"
	.string "me again and I shall test you one\l"
	.string "last time.$"

Route27_RouteExpert_Text_2:
	.string "You cut through every challenge\n"
	.string "on this long road. Now show me\l"
	.string "if you really are worthy for the\l"
	.string "Elite Four!$"

Route27_RouteExpert_Text_3:
	.string "Nothing can stand against you now.$"

Route27_RouteExpert_Text_4:
	.string "A perfect choice, backed by real\n"
	.string "conviction. Take this and let it\l"
	.string "amplify your strongest attacks.$"
