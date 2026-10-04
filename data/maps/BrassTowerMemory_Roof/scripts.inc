@ The roof of the Brass Tower on the night it burned (Berry Master, plan part
@ 15; REI_DA_COLHEITA.md 15.5). Layout: the Tin Tower roof's, untouched;
@ the fire is the palette tint (MapTint_Mode, src/berry_garden.c).
@
@ Plan (map.bin measured with dump_mapa.py): the walkable roof is a cross,
@ x 8-12 by rows 7-12, with the stairs down at (10,13)-(10,14).
@   the Spectrier (10,8) v, Brother Tomo (10,9) v, in front of it
@   arrival from the ladder (10,11), facing north
@   Morty (9,12), Eusine (11,12), Peonia (12,12), all facing north; the
@     column (10,12)-(10,13) to the stairs stays free
@   Ho-Oh's shadow: (1,7), hidden, elevation 13 (drawn over the roof); it
@     crosses the top row of the screen, over the stable, and is gone
@
@ Brother Tomo: a story fight without whiteout (garden_fight). Losing heals the
@ party and sends the player back down the ladder (1F (14,5)) to try again.
@ Won: his trainer flag stays set (the only record of it, a trainer flag,
@ no new flag), and from then on he stands aside at (9,9).
@ The Spectrier: offering the Shaderoot opens a level-60 battle; only the
@ capture moves on (VAR_HARVEST_KING 11 -> 13), and the player wakes in the
@ Burned Tower B1F (16,13), where Morty gives the Spell Tag.
@
@ Temps: FLAG_TEMP_1 hides the three, FLAG_TEMP_2 the Spectrier, FLAG_TEMP_4
@ Ho-Oh; VAR_TEMP_1 arms Tomo's scene; VAR_TEMP_3 is garden_fight's outcome.
BrassTowerMemory_Roof_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BrassTowerMemory_Roof_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BrassTowerMemory_Roof_OnFrame
	.byte 0

BrassTowerMemory_Roof_OnTransition::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_4
	setvar VAR_TEMP_1, 0
	goto_if_ne VAR_HARVEST_KING, HARVEST_KING_SHADEROOT, BrassTowerMemory_Roof_EventScript_End
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_2
	goto_if_defeated TRAINER_BRASS_TOMO, BrassTowerMemory_Roof_EventScript_TomoAside
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 10, BrassTowerMemory_Roof_EventScript_End
	goto_if_ne VAR_0x8005, 11, BrassTowerMemory_Roof_EventScript_End
	setvar VAR_TEMP_1, 1
BrassTowerMemory_Roof_EventScript_End::
	end

BrassTowerMemory_Roof_EventScript_TomoAside::
	setobjectxyperm LOCALID_BRASSROOF_TOMO, 9, 9
	setobjectmovementtype LOCALID_BRASSROOF_TOMO, MOVEMENT_TYPE_FACE_RIGHT
	end

BrassTowerMemory_Roof_OnFrame::
	map_script_2 VAR_TEMP_1, 1, BrassTowerMemory_Roof_EventScript_TomoScene
	.2byte 0

@ Player (10,11) facing north, Tomo (10,9) between the player and the horse.
BrassTowerMemory_Roof_EventScript_TomoScene::
	setvar VAR_TEMP_1, 2
	lockall
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox BrassTowerMemory_Roof_Text_TomoStop, MSGBOX_DEFAULT
	garden_fight TRAINER_BRASS_TOMO, BrassTowerMemory_Roof_Text_TomoDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, BrassTowerMemory_Roof_EventScript_TomoHolds
	settrainerflag TRAINER_BRASS_TOMO
	msgbox BrassTowerMemory_Roof_Text_TomoWon, MSGBOX_DEFAULT
	closemessage
	@ Ho-Oh's shadow passes over the stable, and does not stop.
	clearflag FLAG_TEMP_4
	addobject LOCALID_BRASSROOF_HO_OH
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	applymovement LOCALID_BRASSROOF_HO_OH, BrassTowerMemory_Roof_Movement_HoOhPasses
	waitmovement 0
	removeobject LOCALID_BRASSROOF_HO_OH
	waitmoncry
	msgbox BrassTowerMemory_Roof_Text_MortyHoOh, MSGBOX_DEFAULT
	msgbox BrassTowerMemory_Roof_Text_EusineHoOh, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BRASSROOF_TOMO, BrassTowerMemory_Roof_Movement_TomoAside
	waitmovement 0
	releaseall
	end

@ Lost, a draw or anything else: nothing lost, back down the ladder.
BrassTowerMemory_Roof_EventScript_TomoHolds::
	special HealPlayerParty
	msgbox BrassTowerMemory_Roof_Text_TomoHolds, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warp MAP_BRASS_TOWER_MEMORY_1F, 14, 5
	waitstate
	releaseall
	end

BrassTowerMemory_Roof_Movement_HoOhPasses:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

BrassTowerMemory_Roof_Movement_TomoAside:
	walk_left
	face_right
	step_end

BrassTowerMemory_Roof_EventScript_Tomo::
	lock
	faceplayer
	goto_if_defeated TRAINER_BRASS_TOMO, BrassTowerMemory_Roof_EventScript_TomoAfter
	msgbox BrassTowerMemory_Roof_Text_TomoStop, MSGBOX_DEFAULT
	release
	end

BrassTowerMemory_Roof_EventScript_TomoAfter::
	msgbox BrassTowerMemory_Roof_Text_TomoAfter, MSGBOX_DEFAULT
	release
	end

BrassTowerMemory_Roof_EventScript_Morty::
	msgbox BrassTowerMemory_Roof_Text_Morty, MSGBOX_NPC
	end

BrassTowerMemory_Roof_EventScript_Eusine::
	msgbox BrassTowerMemory_Roof_Text_Eusine, MSGBOX_NPC
	end

BrassTowerMemory_Roof_EventScript_Peonia::
	msgbox BrassTowerMemory_Roof_Text_Peonia, MSGBOX_NPC
	end

@ ------------------------------------------------------------- the Spectrier
BrassTowerMemory_Roof_EventScript_Spectrier::
	lock
	goto_if_not_defeated TRAINER_BRASS_TOMO, BrassTowerMemory_Roof_EventScript_SpectrierGuarded
	checkitem ITEM_SHADEROOT_CARROT
	goto_if_eq VAR_RESULT, FALSE, BrassTowerMemory_Roof_EventScript_SpectrierLooksPast
	checkitemspace ITEM_SPELL_TAG, 1
	goto_if_eq VAR_RESULT, FALSE, BrassTowerMemory_Roof_EventScript_SpectrierBagFull
	msgbox BrassTowerMemory_Roof_Text_SpectrierOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BrassTowerMemory_Roof_EventScript_SpectrierEnd
	msgbox BrassTowerMemory_Roof_Text_SpectrierTurns, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_SPECTRIER, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_SPECTRIER, 60
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, BrassTowerMemory_Roof_EventScript_SpectrierCaught
	msgbox BrassTowerMemory_Roof_Text_SpectrierWaits, MSGBOX_DEFAULT
BrassTowerMemory_Roof_EventScript_SpectrierEnd::
	release
	end

BrassTowerMemory_Roof_EventScript_SpectrierGuarded::
	msgbox BrassTowerMemory_Roof_Text_SpectrierGuarded, MSGBOX_DEFAULT
	release
	end

BrassTowerMemory_Roof_EventScript_SpectrierLooksPast::
	msgbox BrassTowerMemory_Roof_Text_SpectrierLooksPast, MSGBOX_DEFAULT
	release
	end

BrassTowerMemory_Roof_EventScript_SpectrierBagFull::
	msgbox BrassTowerMemory_Roof_Text_SpectrierBagFull, MSGBOX_DEFAULT
	release
	end

BrassTowerMemory_Roof_EventScript_SpectrierCaught::
	setvar VAR_HARVEST_KING, HARVEST_KING_SPECTRIER
	removeobject LOCALID_BRASSROOF_SPECTRIER
	msgbox BrassTowerMemory_Roof_Text_Fade, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_WHITE
	warp MAP_BURNED_TOWER_B1F, 16, 13
	waitstate
	release
	end

@ ------------------------------------------------------------------- texts
BrassTowerMemory_Roof_Text_TomoStop:
	.string "{SPEAKER NAME_TOMO}Stay back! No one takes him.\p"
	.string "He came to us from a land that forgot\n"
	.string "his name. I won't let Johto forget\l"
	.string "him too.$"

BrassTowerMemory_Roof_Text_TomoDefeat:
	.string "...You fight like someone who was sent.$"

BrassTowerMemory_Roof_Text_TomoWon:
	.string "{SPEAKER NAME_TOMO}...You carry a Shaderoot. From his\n"
	.string "home. Then you came from his king.\p"
	.string "Tell him the old monk says he can stop\n"
	.string "waiting.$"

BrassTowerMemory_Roof_Text_TomoHolds:
	.string "{SPEAKER NAME_TOMO}Go back down, child. The fire is\n"
	.string "coming, and he is not yours to take.$"

BrassTowerMemory_Roof_Text_TomoAfter:
	.string "{SPEAKER NAME_TOMO}Be kind to him. He has been waiting\n"
	.string "a long time.$"

BrassTowerMemory_Roof_Text_MortyHoOh:
	.string "{SPEAKER NAME_MORTY}It revived the three of this land.\n"
	.string "It passed him by.\p"
	.string "He's been standing in that night ever\n"
	.string "since.$"

BrassTowerMemory_Roof_Text_EusineHoOh:
	.string "{SPEAKER NAME_EUSINE}...Not a fourth beast.\n"
	.string "Just a horse nobody came back for.$"

BrassTowerMemory_Roof_Text_Morty:
	.string "{SPEAKER NAME_MORTY}It's his memory. We're only guests\n"
	.string "in it.$"

BrassTowerMemory_Roof_Text_Eusine:
	.string "{SPEAKER NAME_EUSINE}I should be writing this down.\n"
	.string "...I don't think I will.$"

BrassTowerMemory_Roof_Text_Peonia:
	.string "{SPEAKER NAME_PEONIA}Let's take him home. To the garden,\n"
	.string "I mean. That's home now, isn't it?$"

BrassTowerMemory_Roof_Text_SpectrierGuarded:
	.string "Brother Tomo stands between you and\n"
	.string "the black horse.$"

BrassTowerMemory_Roof_Text_SpectrierLooksPast:
	.string "The black horse looks past you, at the\n"
	.string "stairs. It's waiting for someone else.$"

BrassTowerMemory_Roof_Text_SpectrierBagFull:
	.string "The black horse stands in the smoke.\p"
	.string "Your Bag is too full. Make room in it\n"
	.string "before you go near.$"

BrassTowerMemory_Roof_Text_SpectrierOffer:
	.string "The black horse stands in the smoke,\n"
	.string "waiting for someone.\p"
	.string "Offer it the Shaderoot Carrot?$"

BrassTowerMemory_Roof_Text_SpectrierTurns:
	.string "It turns its head.\n"
	.string "It knows the smell of home.$"

BrassTowerMemory_Roof_Text_SpectrierWaits:
	.string "The black horse goes back to watching\n"
	.string "the stairs.\p"
	.string "It will wait. It's good at waiting.$"

BrassTowerMemory_Roof_Text_Fade:
	.string "The smoke thins. The bells go quiet.\n"
	.string "The light goes white...$"
