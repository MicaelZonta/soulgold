
.set LOCALID_LASS, 2
.set LOCALID_SILVER, 3

NewBarkTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, NewBarkTown_OnLoad
	.byte 0

NewBarkTown_OnLoad::
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN
	call NewBarkTown_EventScript_ApplyUBBarriers      @ Rift Mission 4: fence and barricade
	end

NewBarkTown_OnFrame::
	map_script_2 VAR_NEWBARK_TOWN_STATE, 6, NewBarkTown_EventScript_ElmCallAfterLeague
	map_script_2 VAR_RIFT_MISSIONS_STATE, 1, NewBarkTown_EventScript_LookerCall
	map_script_2 VAR_NEWBARK_TOWN_STATE, 11, NewBarkTown_EventScript_ArcherArcadeCall
    map_script_2 VAR_RIVAL_STATE, 0, NewBarkTown_EventScript_RivalIntro
    map_script_2 VAR_RIVAL_STATE, 2, NewBarkTown_EventScript_RivalBattle
	.2byte 0

NewBarkTown_EventScript_ElmCallAfterLeague::
	lock
	pokenavcall BlackthornCity_Text_ElmCall
	waitmessage
	delay 30
	setvar VAR_NEWBARK_TOWN_STATE, 7
	setvar VAR_NEWBARKTOWN_LABSTATE, 10
	release
	end

@ Rift Mission 1. Armed by the first Hall of Fame (VAR_RIFT_MISSIONS_STATE = 1);
@ fires on the first frame after the player leaves the house. The frame table
@ runs the first true entry per frame, so Elm's call (state 6 -> 7) goes first
@ and this one on the following frame - one call after the other.
NewBarkTown_EventScript_LookerCall::
	setvar VAR_RIFT_MISSIONS_STATE, 2          @ first instruction: stops re-firing
	setflag FLAG_DAILY_LOOKER_CALL             @ today's call has been made
	lock
	pokenavcall NewBarkTown_Text_LookerCall
	waitmessage
	delay 30
	release
	end

@ WARNING: the two lines after the calls are goto_if_eq, NOT call_if_eq -
@ whoever matches one never comes back here. Any new call must go ABOVE them
@ or it silently stops running in NEWBARK_TOWN_STATE 2 and 4. (Rift Mission 4,
@ .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md.)
NewBarkTown_OnTransition::
    call Common_EventScript_SetupRivalGfxId
	call NewBarkTown_EventScript_ApplyUBVisibility      @ Rift Mission 4 - must stay above the gotos
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_Set_TalkToElm
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_Set_TalkToMom
	end

NewBarkTown_Set_TalkToElm::
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_Set_TalkToMom::
	setobjectxyperm LOCALID_LASS, 0, 11
	callnative SetTimeBasedEncounters
	end

NewBarkTown_EventScript_LabSign::
	msgbox NewBarkTown_Text_LabSign, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TownSign::
	msgbox NewBarkTown_Text_Sign, MSGBOX_SIGN
	closemessage
	end


NewBarkTown_EventScript_Lass::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LassState2
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 3, NewBarkTown_EventScript_LassState3
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LassState4
	msgbox NewBarkTown_Text_LassState5, MSGBOX_DEFAULT
	closemessage
	release
	end
	
NewBarkTown_EventScript_LassState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState3::
	msgbox NewBarkTown_Text_LassState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_LassState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Wooper::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WOOPER, CRY_MODE_NORMAL
	msgbox NewBarkTown_Text_Wooper, MSGBOX_DEFAULT
	waitmoncry
	release
	end

NewBarkTown_EventScript_LeaveTrigger::
	lock
	call_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_LeaveTriggersState2
	call_if_eq VAR_NEWBARK_TOWN_STATE, 4, NewBarkTown_EventScript_LeaveTriggersState4
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	waitmovement 0
	release
	end

NewBarkTown_EventScript_LeaveTriggersState2::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState2, MSGBOX_DEFAULT
	closemessage
	return

NewBarkTown_EventScript_LeaveTriggersState4::
	playse SE_PIN
	applymovement LOCALID_LASS, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_LASS, NewBarkTown_Movement_FaceDown
	waitmovement 0
	msgbox NewBarkTown_Text_LassState4, MSGBOX_DEFAULT
	closemessage
	return 



NewBarkTown_EventScript_FatMan::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARK_TOWN_STATE, 2, NewBarkTown_EventScript_FatManState2
	msgbox NewBarkTown_Text_FatManState3, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_FatManState2::
	msgbox NewBarkTown_Text_FatManState2, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Silver::
	lock
	msgbox NewBarkTown_Text_Silver1, MSGBOX_DEFAULT
	delay 60
	playse SE_PIN
	applymovement LOCALID_SILVER, Common_Movement_ExclamationMark
	faceplayer
	waitmovement 0
	msgbox NewBarkTown_Text_Silver2, MSGBOX_DEFAULT
	playse SE_BANG
	applymovement LOCALID_SILVER, NewBarkTown_Movement_SilverPushesPlayer
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerPushedBySilver
	waitmovement 0
	applymovement LOCALID_SILVER, Common_Movement_FaceOriginalDirection
	waitmovement 0
	waitmovement 0
	release
	end


NewBarkTown_EventScript_Door::
	msgbox NewBarkTown_Text_Door, MSGBOX_SIGN
	end

NewBarkTown_EventScript_TestMan1::
	givebp 4
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	end

NewBarkTown_EventScript_TestMan2::
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	end

NewBarkTown_EventScript_TestMan3::
	setvar VAR_NEWBARK_TOWN_STATE, 5
	
	clearflag FLAG_COMPLETED_AERODACTYL_PUZZLE
	clearflag FLAG_COMPLETED_HOOH_PUZZLE
	clearflag FLAG_COMPLETED_KABUTO_PUZZLE
	clearflag FLAG_COMPLETED_OMANYTE_PUZZLE
	end

NewBarkTown_Movement_SilverPushesPlayer:
	walk_fast_left
	walk_fast_left
	walk_fast_down
	face_down
	lock_facing_direction
	unlock_facing_direction
	walk_fast_up
	walk_fast_right
	walk_fast_right
	step_end


NewBarkTown_Movement_PlayerPushedBySilver:
	walk_fast_left
	face_up
	walk_fast_down
	face_up
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	face_down
	step_end

	


NewBarkTown_Movement_FaceDown:
	face_down
	step_end

NewBarkTown_Text_LabSign:
	.string "Prof. Elm's Lab$"

NewBarkTown_Text_Door:
	.string "The door is locked.$"

NewBarkTown_Text_Wooper:
	.string "Wooper: Woooooop.$"

NewBarkTown_Text_FatManState2:
	.string "Wow, your Pokégear is impressive!\n"
	.string "Did your mom get it for you?$"

NewBarkTown_Text_FatManState3:
	.string "Yo, {PLAYER}!\p"
	.string "I hear Prof. Elm discovered\n"
	.string "some new Pokémon.$"

NewBarkTown_Text_LassState2:
	.string "Wait, {PLAYER}!\p"
	.string "It's dangerous to go out\n"
	.string "without a Pokémon!\p"
	.string "Wild Pokémon jump out of the grass\n"
	.string "on the way to the next town.$"

NewBarkTown_Text_LassState3:
	.string "Oh! Your Pokémon is adorable!\n"
	.string "I wish I had one!$"

NewBarkTown_Text_LassState4:
	.string "Hi, {PLAYER}! Leaving again?\p"
	.string "You should tell your mom if\n"
	.string "you are leaving.$"

NewBarkTown_Text_LassState5:
	.string "Call your mom on your Pokégear\n"
	.string "to let her know how you're doing.$\p"

NewBarkTown_Text_Silver1:
	.string ". . .\p"
	.string "So this is the famous Elm\n"
	.string "Pokémon Lab…$"

NewBarkTown_Text_Silver2:
	.string "…What are you staring at?$"

NewBarkTown_Text_Sign:
	.string "New Bark Town\p"
	.string "The Town Where the Winds of\n"
	.string "a New Beginning Blow$"

NewBarkTown_EventScript_PlayersHouseMailbox::
	msgbox NewBarkTown_Text_PlayersHouse, MSGBOX_SIGN
	end

NewBarkTown_EventScript_ElmsHouseMailbox::
	msgbox NewBarkTown_Text_ElmsHouse, MSGBOX_SIGN
	end

NewBarkTown_Text_PlayersHouse:
	.string "{PLAYER}'s House$"

NewBarkTown_Text_ElmsHouse:
	.string "Prof. Elm's House$"

@ Looker's first call (script revision V2, 25/09/2026). Cordial and
@ professional, and short: it congratulates, introduces, asks and names the
@ house. It does NOT retell the holiday cover over the phone and it does not
@ hide the request behind three attempts at an introduction. No creature, no
@ town and no name is given away.
@ It also sets FLAG_DAILY_LOOKER_CALL: from here on Looker rings once a day
@ while a briefing is pending in Olivine (ShouldDoRiftMissionCall,
@ src/field_control_avatar.c), and the day he calls in person counts.
NewBarkTown_Text_LookerCall:
	.string "{SPEAKER NAME_LOOKER}Hello, {PLAYER}?\n"
	.string "Congratulations on becoming\l"
	.string "Champion!\p"
	.string "My name is Looker.\n"
	.string "International Police.\p"
	.string "My colleague and I need your\n"
	.string "help with an investigation in\l"
	.string "Johto.\p"
	.string "Please meet us in Olivine.\p"
	.string "Our house is the one nearest\n"
	.string "the Gym.\p"
	.string "I'll explain when you arrive.$"

NewBarkTown_EventScript_RivalIntro::
	lock
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_0
	waitmovement 0
	playse SE_WALL_HIT
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_1
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_2
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_3
	playse SE_LEDGE
	waitmovement 0
	playbgm MUS_HG_LYRA, TRUE
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_4
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, Common_Movement_ExclamationMark
	playse SE_PIN
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_5
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_6
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_7
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_8
	applymovement LOCALID_NEWBARK_MARILL, NewBarkTown_EventScript_RivalIntro_Movement_9
	waitmovement 0
	setflag FLAG_HIDE_NEWBARK_RIVALMARILL
	removeobject LOCALID_NEWBARK_RIVAL
	removeobject LOCALID_NEWBARK_MARILL
	removeobject LOCALID_NEWBARK_MARILL2
	setvar VAR_RIVAL_STATE, 1
	fadedefaultbgm
	release
	end


NewBarkTown_EventScript_RivalBattle::
	lock
	playbgm MUS_HG_LYRA, TRUE
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_0
	playse SE_LEDGE
	waitmovement 0
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_1
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_2
	waitmovement LOCALID_NEWBARK_MARILL2
	applymovement LOCALID_NEWBARK_RIVAL, Common_Movement_ExclamationMark
	playse SE_PIN
	waitmovement 0
	applymovement LOCALID_PLAYER, NewBarkTown_EventScript_RivalBattle_Movement_3
	waitmovement 0
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalIntro_Movement_5
	waitmovement 0
	createfieldmugshotrival
	msgbox NewBarkTown_EventScript_RivalBattle_Text_0
	applymovement OBJ_EVENT_ID_FOLLOWER, NewBarkTown_EventScript_RivalBattle_Movement_4
	playse SE_BALL_OPEN
	waitmovement 0
	bufferleadmonspeciesname STR_VAR_1
	msgbox NewBarkTown_EventScript_RivalBattle_Text_1
	msgbox NewBarkTown_EventScript_RivalBattle_Text_2
	msgbox NewBarkTown_EventScript_RivalBattle_Text_3
	msgbox NewBarkTown_EventScript_RivalBattle_Text_4
	msgbox NewBarkTown_EventScript_RivalBattle_Text_5
	setflag FLAG_NO_WHITEOUT
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq NewBarkTown_EventScript_RivalBattle_2
	trainerbattle_no_intro TRAINER_RIVALGOLD1, NewBarkTown_EventScript_RivalBattle_Text_6
NewBarkTown_EventScript_RivalBattle_1:
	clearflag FLAG_NO_WHITEOUT
	special HealPlayerParty
	createfieldmugshotrival
	msgbox NewBarkTown_EventScript_RivalBattle_Text_7
	msgbox NewBarkTown_EventScript_RivalBattle_Text_8
	removefieldmugshot
	closemessage
	applymovement LOCALID_NEWBARK_RIVAL, NewBarkTown_EventScript_RivalBattle_Movement_5
	applymovement LOCALID_NEWBARK_MARILL2, NewBarkTown_EventScript_RivalBattle_Movement_6
	waitmovement 0
	removeobject LOCALID_NEWBARK_RIVAL
	removeobject LOCALID_NEWBARK_MARILL
	removeobject LOCALID_NEWBARK_MARILL2
	fadedefaultbgm
	setvar VAR_RIVAL_STATE, 3
	release
	end

NewBarkTown_EventScript_RivalBattle_2:
	trainerbattle_no_intro TRAINER_RIVALCRYSTAL1, NewBarkTown_EventScript_RivalBattle_Text_6
	goto NewBarkTown_EventScript_RivalBattle_1


RivalsMailbox::
	lock
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq RivalsMailbox_2
	msgbox RivalsMailbox_Text_1
RivalsMailbox_1:
	release
	end

RivalsMailbox_2:
	msgbox RivalsMailbox_Text_0
	goto RivalsMailbox_1


NewBarkTown_EventScript_ArcherArcadeCall::
	lock
	pokenavcall NewBarkTown_EventScript_ArcherArcadeCall_Text_0
	waitmessage
	delay 30
	setvar VAR_NEWBARK_TOWN_STATE, 12
	release
	end



@ ============================================================================
@ Rift Mission 4 - New Bark. Kartana, Guzzlord, Nihilego and Ultra Necrozma.
@ Script: .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_SCRIPT_V2.md
@ Plan:   .claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md
@
@ The story in four lines. Elm's six weeks of records, compared with the
@ police's, showed three points waking up in New Bark; the team comes to clear
@ the street before they open, with Aether's containment equipment. The three
@ open anyway and do three different things - Kartana cuts the fence, Guzzlord
@ eats the south barricade, Nihilego drifts into the gap and stops Mom halfway
@ to the shelter. The team holds, the player wins their front, the field
@ really does cut the links - and Necrozma breaks it, absorbs all three, turns
@ Ultra, cannot hold that light steady and backs out through its own opening.
@ The town is protected. The Ultra Beasts still have to be recovered.
@
@ Floor plan (dump_mapa.py NewBarkTown; y grows DOWNWARD). There IS water in
@ this layout - the pond at x 25..26, y 11..14 is MB_OCEAN_WATER with
@ collision 0 - but nothing in this scene goes east of x 22.
@
@       x= 10 11 12 13 14 15 16 17 18 19 20 21 22
@   y= 9    D  #  .  #  k  f  N  r  #  #  #  #  #     D lab door (warp 10,9)
@   y=10    .  E  .  .  F  F  F  f  #  #  #  #  #     F temporary fence (setmetatile)
@   y=11    .  .  W  U  .  m  .  #  #  #  d  #  #     d player's house door (warp 20,11)
@   y=12    .  R  z  .  .  .  P  .  .  .  *  K  A     * (20,12) Fly/blackout/arrival
@   y=13    .  .  .  .  .  .  .  .  .  .  .  M  .
@   y=14    #  .  .  .  .  .  .  .  a  .  s  .  .     a Anabel's post (18,14)
@   y=15    .  .  .  .  .  .  .  .  .  .  B  B  B     B log barricade (setmetatile)
@   y=16    .  .  .  n  .  .  .  .  .  .  .  g  .
@
@   Prep (map.json):  K Looker (21,12)  A Anabel (22,12)  M Mom (21,13)
@                     R Gold/Crystal (11,12)  z Azumarill (12,12)
@                     E Elm (11,10), beside the lab door - his recording station
@                       is just inside it; he never leaves this tile
@                     U Lusamine (13,11), at the west marker's control
@   Operation:        P player (16,12), W west emitter (12,11), east emitter
@                     on Anabel's old tile (22,12); m Milotic (15,11),
@                     s Snorlax (20,14), Anabel -> a (18,14). Both emitters
@                     use OBJ_EVENT_GFX_AETHER_EMITTER, the mission's own sprite.
@   The three openings: k Kartana (14,9) behind the fence, g Guzzlord (21,16)
@                     behind the barricade, n Nihilego (13,16) on the south lawn
@   Necrozma:         N (16,9), outside the area, in the flower bed; the main
@                     opening r (17,9) only appears for its retreat
@   Partner:          (17,13), east of the player after the line steps back
@
@ LOOKER'S POCKET. (21,11) is the house wall, (22,12) Anabel and (21,13) Mom, so
@ on the first attempt the only talk tile is (20,12) - the arrival tile, which
@ nothing ever stands on. On a retry Anabel and Mom have moved, the east
@ emitter fills (22,12), and (21,13) is the second talk tile: UBSceneRetry
@ normalises both (getplayerxy).
@
@ Camera. Nothing moves the camera: the player stands at (16,12) for every
@ beat that is seen from the "command" spot, which frames x 9..23 and, with a
@ text box open, y 8..14. That holds the lab door, Elm, the rival's corridor,
@ the fence, the house, Looker, Anabel and Snorlax in one screen. The spawn
@ window is wider (x-9..x+10, y-7..y+9, src/event_object_movement.c:3149), so
@ no object is ever despawned and respawned from its template mid-scene - EXCEPT
@ when the player walks to Guzzlord at (20,14): the window becomes x 11..30
@ and Looker's post sync below matters. Every actor that ends a walk away from
@ its template gets a setobjectxyperm (and movement type) right after it.
@
@ Per-map temporaries (all zeroed by ClearTempFieldEventData on every load):
@   FLAG_TEMP_1 - Anabel, Gold/Crystal, Azumarill, Lusamine (never removed)
@   FLAG_TEMP_2 - Kartana, Guzzlord, Nihilego (removed together)
@   FLAG_TEMP_3 - Elm
@   FLAG_TEMP_4 - Mom (removed at the lab door, re-added for the aftermath)
@   FLAG_TEMP_5 - Necrozma          FLAG_TEMP_6 - Ultra Necrozma
@   FLAG_TEMP_7 - Looker (removed at the lab door, re-added coming back out)
@   FLAG_TEMP_8 - Snorlax           FLAG_TEMP_9 - Milotic
@   FLAG_TEMP_A - the two emitters  FLAG_TEMP_B - the main opening
@   FLAG_TEMP_C - the player's Cosmog-family partner, four templates
@   FLAG_TEMP_E - FLAG_TEMP_HIDE_FOLLOWER: set on the YES, and on every load of
@                 a retry. It REMOVES the follower object (UpdateFollowingPokemon)
@                 instead of only hiding it, which frees its slot. The final
@                 warp zeroes it and the follower comes back.
@ Every actor that is ever removeobject'd has its OWN flag: removeobject sets
@ the template's flag, and a shared one would respawn a partner's template on
@ the next camera step after its sibling was re-added.
@   VAR_TEMP_2 - battle outcome
@   VAR_TEMP_3 - the pick: 0 = Kartana, 1 = Guzzlord, 2 = Nihilego. Survives
@                the battle (coming back from a battle does not reload the map)
@   VAR_TEMP_4 - Cosmog-family species shown (SPECIES_NONE = none), sampled
@                AFTER the battle
@
@ Persistent: FLAG_EVENT_ULTRABEAST_NEWBARK (set <=> state 9) and
@ FLAG_NEWBARK_UB_ENGAGED (everything up to the choice has played; a blackout
@ comes back to the staged street). Both cleared by UBFinish.
@
@ OBJECT BUDGET (OBJECT_EVENTS_COUNT 16, player included). Peak while the three
@ beasts are out and Mom has not crossed yet: player + Looker, Anabel, Mom,
@ Gold/Crystal, Azumarill, Elm, Lusamine, Snorlax, Milotic, two emitters and
@ three beasts = 15 (the follower was removed on the YES). With Necrozma: Mom
@ is inside by then, so 15 again. That is why Necrozma ARRIVES through a
@ distortion (flash and sparkle) and the main opening is an object only for
@ the retreat, when the beasts are gone. Do not add a persistent actor here
@ without taking one out.
@ SPRITE PALETTES: every species overworld sprite loads its own palette, and so
@ do Looker, Lusamine, Elm and the emitter. The peak is about 14 plus field
@ effects - test it at night, with everyone on screen.
@
@ WARNING: seven residents (locals 1, 2, 4, 5, 6, 7, 8) carry
@ FLAG_EVENT_ULTRABEAST_NEWBARK in their "flag" field; a removeobject on any of
@ them sets it and empties the town. Never clear FLAG_HIDE_NEWBARK_RIVALMARILL
@ (locals 9-11, the old Gold/Crystal and two Marill).
@ While the event flag is set, every building door except the lab (the shelter)
@ and the player's house refuses the player (sLockedTownDoors,
@ src/field_control_avatar.c -> NewBarkTown_EventScript_DoorLocked).
@ ============================================================================

@ Metatiles of the two temporary barriers (primary johto_general):
@   0x0E7 white picket fence on grass - the fence the team put across the
@         flower bed between the lab and the house
@   0x2E0 log barricade on sand - across the south road
@ and the originals they cover, restored when a beast breaks through.
.set NB_MT_FENCE,        0x0E7
.set NB_MT_LOGS,         0x2E0
.set NB_MT_FLOWER,       0x004
.set NB_MT_ROAD,         0x0DC
.set NB_MT_ROAD_EDGE_E,  0x105

@ Called from NewBarkTown_OnLoad. ON_LOAD runs before the map is drawn - on a
@ normal load AND when coming back from a battle (InitMapFromSavedGame, after
@ the saved view is restored) - so the barriers always match the state and
@ the scene never has to redraw them after the battle. Nothing is ever drawn
@ outside the incident: the layout file itself has no fence and no logs, so
@ the reload in UBFinish is what takes them away.
NewBarkTown_EventScript_ApplyUBBarriers::
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_UBBarriersDone
	setmetatile 14, 10, NB_MT_FENCE, TRUE
	setmetatile 15, 10, NB_MT_FENCE, TRUE
	setmetatile 16, 10, NB_MT_FENCE, TRUE
	setmetatile 20, 15, NB_MT_LOGS, TRUE
	setmetatile 21, 15, NB_MT_LOGS, TRUE
	setmetatile 22, 15, NB_MT_LOGS, TRUE
	goto_if_unset FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBBarriersDone
	call NewBarkTown_EventScript_UBFenceCut
	call NewBarkTown_EventScript_UBBarricadeBroken
NewBarkTown_EventScript_UBBarriersDone::
	return

@ Kartana's cut: one section, the west one, back to the flower bed it was
@ standing on. The other two stay up.
NewBarkTown_EventScript_UBFenceCut::
	setmetatile 14, 10, NB_MT_FLOWER, FALSE
	return

@ Guzzlord's side of the barricade: the two east logs, back to road.
NewBarkTown_EventScript_UBBarricadeBroken::
	setmetatile 21, 15, NB_MT_ROAD, FALSE
	setmetatile 22, 15, NB_MT_ROAD_EDGE_E, FALSE
	return

@ Called from NewBarkTown_OnTransition, which runs before any object spawns -
@ so setflag/clearflag/setobjectxyperm work here and removeobject would not.
@ Three shapes of the street:
@   1. no incident: every mission actor hidden.
@   2. first attempt (state 9): the prep cast on their map.json tiles; the
@      beasts, partners, emitters and everything else come from the scene.
@   3. FLAG_NEWBARK_UB_ENGAGED (retry): the street as it was at the choice -
@      fence cut, barricade broken, three beasts, Snorlax, Milotic, emitters,
@      Anabel at her post, Mom inside the lab (NewBarkTown_Lab shows her).
NewBarkTown_EventScript_ApplyUBVisibility::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_8
	setflag FLAG_TEMP_9
	setflag FLAG_TEMP_A
	setflag FLAG_TEMP_B
	setflag FLAG_TEMP_C
	goto_if_unset FLAG_EVENT_ULTRABEAST_NEWBARK, NewBarkTown_EventScript_HideUBCast
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_7
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_StageUBRetry
	clearflag FLAG_TEMP_4
	return

NewBarkTown_EventScript_HideUBCast::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_7
	return

@ The choice-time formation, rebuilt from templates. setobjectxyperm and not
@ setobjectxy: templates are re-read on every load, so none of this leaks into
@ the next visit. Mom stays hidden (FLAG_TEMP_4 still set): she is sheltered.
NewBarkTown_EventScript_StageUBRetry::
	setflag FLAG_TEMP_HIDE_FOLLOWER
	clearflag FLAG_TEMP_2
	clearflag FLAG_TEMP_8
	clearflag FLAG_TEMP_9
	clearflag FLAG_TEMP_A
	setobjectxyperm LOCALID_NEWBARK_UB_KARTANA, 14, 10
	setobjectxyperm LOCALID_NEWBARK_UB_GUZZLORD, 21, 14
	setobjectxyperm LOCALID_NEWBARK_UB_NIHILEGO, 13, 14
	setobjectxyperm LOCALID_NEWBARK_UB_AZUMARILL, 13, 12
	setobjectmovementtype LOCALID_NEWBARK_UB_AZUMARILL, MOVEMENT_TYPE_FACE_DOWN
	setobjectxyperm LOCALID_NEWBARK_UB_ANABEL, 18, 14
	setobjectmovementtype LOCALID_NEWBARK_UB_ANABEL, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_NEWBARK_UB_SNORLAX, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_NEWBARK_UB_MILOTIC, MOVEMENT_TYPE_FACE_LEFT
	setobjectmovementtype LOCALID_NEWBARK_UB_ELM, MOVEMENT_TYPE_FACE_UP
	return

@ A note on the locked doors, not a person: no speaker plaque (the author's
@ default for notes and narration).
NewBarkTown_EventScript_DoorLocked::
	lockall
	msgbox NewBarkTown_Text_UBDoorNote, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ ----------------------------------------------------------------------------
@ Staging helpers.
@ ----------------------------------------------------------------------------

@ Flash. fadescreenswapbuffers and NOT fadescreen: fadescreen copies
@ gPlttBufferFaded over gPlttBufferUnfaded, and the FADE_FROM_* after it
@ re-tints an already tinted buffer - at night every flash darkened the town
@ by ~0.46 until it went black (implementation doc, revision 5).
NewBarkTown_EventScript_UBFlash::
	fadescreenswapbuffers FADE_TO_WHITE
	fadescreenswapbuffers FADE_FROM_WHITE
	return

NewBarkTown_EventScript_UBShake::
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 12  @ num shakes
	setvar VAR_0x8007, 4   @ shake delay
	special ShakeCamera
	waitstate
	return

@ An opening wavering: a short sideways tremor and the warp sound, no flash -
@ it must not read as another attack.
NewBarkTown_EventScript_UBRiftPulse::
	playse SE_M_TELEPORT
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 1
	setvar VAR_0x8006, 6
	setvar VAR_0x8007, 3
	special ShakeCamera
	waitstate
	waitse
	return

@ The field between the two markers: both emitters light, then a line of
@ light runs across the road between them.
NewBarkTown_EventScript_UBFieldLine::
	playse SE_M_BARRIER
	dofieldeffectsparkle 12, 11, 0
	dofieldeffectsparkle 22, 12, 0
	delay 8
	dofieldeffectsparkle 14, 13, 0
	dofieldeffectsparkle 17, 13, 0
	dofieldeffectsparkle 20, 13, 0
	waitfieldeffect FLDEFF_SPARKLE
	waitse
	return

@ One pattern on Elm's instrument.
NewBarkTown_EventScript_UBBeep::
	playse SE_SELECT
	waitse
	delay 4
	return

@ ----------------------------------------------------------------------------
@ Conversations before the YES (V2 section 6). Each actor turns back to its
@ map.json facing at the end, so an odd talk tile leaves nobody crooked. On a
@ retry each one has a short line of its own: nobody repeats the preparation.
@ ----------------------------------------------------------------------------

@ Lusamine at the west marker's control (13,11). A short introduction: no
@ photographs, no letter, no confession, no "the only one who knows".
NewBarkTown_EventScript_UBLusamine::
	lock
	faceplayer
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBLusamineRetry
	msgbox NewBarkTown_Text_UBLusamineIdle, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBLusamineEnd
NewBarkTown_EventScript_UBLusamineRetry::
	msgbox NewBarkTown_Text_UBLusamineRetry, MSGBOX_DEFAULT
NewBarkTown_EventScript_UBLusamineEnd::
	closemessage
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
	release
	end

@ Elm beside his own door (11,10). His station is just inside it.
NewBarkTown_EventScript_UBElm::
	lock
	faceplayer
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBElmRetry
	msgbox NewBarkTown_Text_UBElmIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_SOUTH
	release
	end
NewBarkTown_EventScript_UBElmRetry::
	msgbox NewBarkTown_Text_UBElmPositions, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_NORTH
	release
	end

@ Mom (21,13), helping the last residents across. Her usual heal lives in her
@ own interaction: "Have you rested?" - NO heals, YES leaves it there. Once she
@ is sheltered (retry) she is not in the street at all: she heals in the lab.
NewBarkTown_EventScript_UBMom::
	lock
	faceplayer
	msgbox NewBarkTown_Text_UBMomIdle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_EventScript_UBMomEnd
	msgbox NewBarkTown_Text_UBMomHeal, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
NewBarkTown_EventScript_UBMomEnd::
	closemessage
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_NORTH
	release
	end

@ Gold/Crystal (11,12), on the corridor to the lab with Azumarill already out
@ of its Ball beside them.
NewBarkTown_EventScript_UBRival::
	lock
	faceplayer
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBRivalRetry
	msgbox NewBarkTown_Text_UBRivalIdle, MSGBOX_DEFAULT
	goto NewBarkTown_EventScript_UBRivalEnd
NewBarkTown_EventScript_UBRivalRetry::
	msgbox NewBarkTown_Text_UBRivalCover, MSGBOX_DEFAULT
NewBarkTown_EventScript_UBRivalEnd::
	closemessage
	turnobject LOCALID_NEWBARK_UB_RIVAL, DIR_EAST
	release
	end

@ Anabel: (22,12) before the YES, (18,14) on a retry.
NewBarkTown_EventScript_UBAnabel::
	lock
	faceplayer
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBAnabelRetry
	msgbox NewBarkTown_Text_UBAnabelIdle, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
	release
	end
NewBarkTown_EventScript_UBAnabelRetry::
	msgbox NewBarkTown_Text_UBRetryNotReady, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_EAST
	release
	end

@ ----------------------------------------------------------------------------
@ Looker (21,12). First attempt: only reachable from (20,12). Nothing changes
@ before the YES; the YES is the last exit point.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBLooker::
	lock
	faceplayer
	goto_if_set FLAG_NEWBARK_UB_ENGAGED, NewBarkTown_EventScript_UBLookerRetry
	msgbox NewBarkTown_Text_UBLookerGreet, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBReady, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBNotReady
	goto NewBarkTown_EventScript_UBScene

NewBarkTown_EventScript_UBNotReady::
	msgbox NewBarkTown_Text_UBNotReady, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST
	release
	end

@ Retry (V2 section 19): the introduction is remembered. Looker reports, and
@ Anabel asks - YES/NO under her plaque. Nothing seen before is replayed.
NewBarkTown_EventScript_UBLookerRetry::
	msgbox NewBarkTown_Text_UBRetryLooker, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBRetryAnabel, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewBarkTown_EventScript_UBRetryNotReady
	goto NewBarkTown_EventScript_UBSceneRetry

NewBarkTown_EventScript_UBRetryNotReady::
	msgbox NewBarkTown_Text_UBRetryNotReady, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_LOOKER, DIR_WEST
	release
	end

@ ----------------------------------------------------------------------------
@ The YES (V2 section 7). The player walks to the command spot (16,12) - the
@ camera follows and from here on frames the whole street. Then the equipment
@ goes out, visibly: Lusamine sets the west emitter beside her control,
@ Anabel sets the east one on the tile she was standing on and walks to her
@ post, and a short test lights the line between them. Elm is in frame at
@ (11,10) for his line. The partners come out of their Balls last, each
@ before its own words.
@ Walks, all sequential, all checked with dump_mapa.py:
@   player (20,12) -> (16,12) along y=12
@   Anabel (22,12) -> (22,13) [faces up, east emitter at (22,12)]
@          -> (22,14) -> (21,14) -> (20,14) -> (19,14) -> (18,14), faces east
@ Snorlax comes out at (20,14), Milotic at (15,11).
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBScene::
	closemessage
	lockall
	hidefollower
	setflag FLAG_TEMP_HIDE_FOLLOWER
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToCommand
	waitmovement OBJ_EVENT_ID_PLAYER
	@ West marker, set by Lusamine beside her own control.
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_WEST
	playse SE_PC_ON
	clearflag FLAG_TEMP_A
	addobject LOCALID_NEWBARK_UB_EMITTER_WEST
	waitse
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
	@ East marker, set by Anabel on her way to her post.
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_StepDownFaceUp
	waitmovement LOCALID_NEWBARK_UB_ANABEL
	playse SE_PC_ON
	addobject LOCALID_NEWBARK_UB_EMITTER_EAST
	waitse
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_AnabelToPost
	waitmovement LOCALID_NEWBARK_UB_ANABEL
	@ The short test: a line of light between the points, and it goes out.
	delay 16
	call NewBarkTown_EventScript_UBFieldLine
	msgbox NewBarkTown_Text_UBFieldExplanation, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBFieldPositions, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_NodLeft
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Text_UBElmPositions, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_NORTH       @ to his station, inside the door
	@ Snorlax, out of the Ball onto the free south-east front.
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_BALL_OPEN
	clearflag FLAG_TEMP_8
	addobject LOCALID_NEWBARK_UB_SNORLAX
	waitse
	playmoncry SPECIES_SNORLAX, CRY_MODE_NORMAL
	waitmoncry
	msgbox NewBarkTown_Text_UBAnabelPartner, MSGBOX_DEFAULT
	closemessage
	@ Milotic, beside Lusamine's control, facing the fence.
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_BALL_OPEN
	clearflag FLAG_TEMP_9
	addobject LOCALID_NEWBARK_UB_MILOTIC
	waitse
	playmoncry SPECIES_MILOTIC, CRY_MODE_NORMAL
	waitmoncry
	msgbox NewBarkTown_Text_UBLusaminePartner, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	goto NewBarkTown_EventScript_UBOpenings

@ ----------------------------------------------------------------------------
@ Three openings, three different things (V2 section 8).
@ The sensors answer first, in a short run; Anabel feels it now that she is
@ close - no speech about it. The town theme leaves on her warning and the
@ threat theme is on BEFORE the reveal (save_song TRUE: the boss battle hands
@ it back instead of the town's).
@ The openings are framed one at a time - the player turns to each - with
@ separate cries, and none of the three walks in step with another.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBOpenings::
	delay 20
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_ANABEL, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_ANABEL
	fadeoutbgm 4
	msgbox NewBarkTown_Text_UBAnabelOpening, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	@ North, behind the fence.
	call NewBarkTown_EventScript_UBShake
	playse SE_WARP_IN
	dofieldeffectsparkle 14, 9, 0
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_2
	addobject LOCALID_NEWBARK_UB_KARTANA
	fadescreenswapbuffers FADE_FROM_WHITE
	waitfieldeffect FLDEFF_SPARKLE
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
	waitmoncry
	@ South, behind the barricade.
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_WARP_IN
	dofieldeffectsparkle 21, 16, 0
	waitfieldeffect FLDEFF_SPARKLE
	addobject LOCALID_NEWBARK_UB_GUZZLORD
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	waitmoncry
	@ The lawn south of the road, in the middle.
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playse SE_WARP_IN
	dofieldeffectsparkle 13, 16, 0
	waitfieldeffect FLDEFF_SPARKLE
	addobject LOCALID_NEWBARK_UB_NIHILEGO
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
	waitmoncry
	delay 16
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBAppear, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBKartanaCuts

@ KARTANA OPENS. It cuts the west section of the fence - a real change of the
@ metatile, back to the flower bed under it - and steps into the gap (14,10).
@ Milotic at (15,11) turns to it (x 14 < 15: west). Nothing is cut that is not
@ put back by the final reload.
NewBarkTown_EventScript_UBKartanaCuts::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_AttackDown
	playse SE_M_CUT
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	call NewBarkTown_EventScript_UBFenceCut
	special DrawWholeMapView
	waitse
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_StepDown
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	turnobject LOCALID_NEWBARK_UB_MILOTIC, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_RIVAL, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_RIVAL
	msgbox NewBarkTown_Text_UBKartanaBreaks, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBGuzzlordBreaks

@ GUZZLORD DESTROYS. It rams the east half of the barricade, the two logs go
@ back to road, and it advances (21,16) -> (21,15) -> (21,14): right under Mom
@ at (21,13), and beside Snorlax at (20,14), which turns east to it. It takes
@ from the team a route that looked protected. It eats a barricade, not a
@ person, and there is no graphic damage.
NewBarkTown_EventScript_UBGuzzlordBreaks::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_AttackUp
	playse SE_M_BITE
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	call NewBarkTown_EventScript_UBShake
	call NewBarkTown_EventScript_UBBarricadeBroken
	special DrawWholeMapView
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_GuzzlordAdvances
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	waitmoncry
	turnobject LOCALID_NEWBARK_UB_SNORLAX, DIR_EAST
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_MOM, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_MOM
	msgbox NewBarkTown_Text_UBGuzzlordBreaks, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBNihilegoDrifts

@ NIHILEGO PRESSES THE RETREAT. Mom, the last person helping the shelter,
@ starts across the road to the lab: (21,13) -> west along y=13 -> (16,13),
@ right under the player. Nihilego drifts up from the lawn into the same lane:
@ (13,16) -> (13,15) -> (13,14) -> (13,13), three slow steps, and arrives after
@ she stops. Nobody ordered it: the three behaviours together make the siege.
@ Then Azumarill intercepts from the SIDE - (12,12) -> (13,12), facing down,
@ never under Mom's sprite - and a short water attack pushes Nihilego back one
@ tile to (13,14). It is repelled, not beaten; the rival holds their spot.
NewBarkTown_EventScript_UBNihilegoDrifts::
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_MomCrosses
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_NihilegoDrifts
	waitmovement LOCALID_NEWBARK_UB_MOM
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_MOM, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_MOM
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Text_UBRivalIntercept, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillIntercepts
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
	playmoncry SPECIES_AZUMARILL, CRY_MODE_ENCOUNTER
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AttackDown
	playse SE_M_BUBBLE_BEAM
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_KnockedBackDown
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	waitse
	waitmoncry
	msgbox NewBarkTown_Text_UBAnabelCorridor, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBMomAndLusamine

@ ----------------------------------------------------------------------------
@ Mom and Lusamine - one decision, not a lecture (V2 section 9).
@ Lusamine leaves her control to reorganise the front and walks
@ (13,11) -> (14,11) -> (14,12) -> (14,13) -> (15,13), facing east: west of
@ Mom (16,13), who is south of the player (16,12). (14,11) is right under
@ Kartana, with Milotic beside her at (15,11) - that is the cover.
@ Mom looks at the player (north), then at Lusamine (west). Lusamine looks at
@ the rival holding the corridor (west) and at Anabel holding the other front
@ (east), and accepts a concrete split. She is not transformed by it.
@ Then Looker comes for Mom, and the two of them cross to the lab: Mom leads,
@ Looker follows one step behind on the same path (a delay_16 in front of his
@ steps keeps them a tile apart on every step). Both go through the door, it
@ closes, and Looker comes back out alone once she is safe.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBMomAndLusamine::
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_LusamineToMom
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
	msgbox NewBarkTown_Text_UBLusamineControl, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_NORTH
	delay 24
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_WEST
	msgbox NewBarkTown_Text_UBMomTrust, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_WEST
	delay 20
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_NORTH
	delay 16
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
	msgbox NewBarkTown_Text_UBLusamineAccepts, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_LusamineBackToControl
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
	@ Looker (21,12) -> (21,13) -> west to (17,13), behind Mom.
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerToMom
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	@ Mom (16,13) -> (10,13) -> (10,10); Looker (17,13) -> (10,13) -> (10,11).
	@ (13,13) passes between Azumarill (13,12) and Nihilego (13,14): covered.
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_MomToLab
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerToLab
	waitmovement LOCALID_NEWBARK_UB_MOM
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	opendoor 10, 9
	waitdooranim
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_StepUp
	waitmovement LOCALID_NEWBARK_UB_MOM
	removeobject LOCALID_NEWBARK_UB_MOM                  @ sets FLAG_TEMP_4, hers alone
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_StepUpTwice
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	removeobject LOCALID_NEWBARK_UB_LOOKER               @ sets FLAG_TEMP_7, his alone
	closedoor 10, 9
	waitdooranim
	delay 40
	@ Looker back out, and back to his post by the house. His template is
	@ moved to the door first and synced to the post at the end, so a
	@ respawn at any point puts him where he really is.
	opendoor 10, 9
	waitdooranim
	setobjectxyperm LOCALID_NEWBARK_UB_LOOKER, 10, 9
	setobjectmovementtype LOCALID_NEWBARK_UB_LOOKER, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_TEMP_7
	addobject LOCALID_NEWBARK_UB_LOOKER
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_StepDown
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	closedoor 10, 9
	waitdooranim
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerBackToPost
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	setobjectxyperm LOCALID_NEWBARK_UB_LOOKER, 21, 12
	setobjectmovementtype LOCALID_NEWBARK_UB_LOOKER, MOVEMENT_TYPE_FACE_LEFT
	goto NewBarkTown_EventScript_UBChoose

@ ----------------------------------------------------------------------------
@ Retry after a blackout or an interrupted battle (V2 section 19). The street
@ was staged by ON_TRANSITION. The player goes to the command spot and straight
@ to the choice - any target, not necessarily the one that was lost. The
@ threat theme is set again (a map load clears savedMusic).
@ From (20,12): west along y=12. From (21,13), the retry's second talk tile:
@ west along y=13 to (16,13), then up. Both lanes are empty in this formation.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBSceneRetry::
	closemessage
	lockall
	hidefollower
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8005, 13, NewBarkTown_EventScript_UBRetryFromSouth
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToCommand
	waitmovement OBJ_EVENT_ID_PLAYER
	goto NewBarkTown_EventScript_UBChoose

NewBarkTown_EventScript_UBRetryFromSouth::
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerRetryFromSouth
	waitmovement OBJ_EVENT_ID_PLAYER
	goto NewBarkTown_EventScript_UBChoose

@ ----------------------------------------------------------------------------
@ The choice (V2 section 10). Checkpoint first: from here a blackout comes
@ back as a retry. Anabel asks, so the menu wears her plaque. No cancel.
@ The pick is per attempt.
@   pick        Lusamine/Milotic   Anabel/Snorlax   Gold/Crystal/Azumarill
@   0 Kartana   Nihilego           Guzzlord         hold the rear and the exit
@   1 Guzzlord  Nihilego           Kartana          hold the flank
@   2 Nihilego  Guzzlord           Kartana          keep it off the door
@ Partners move first, along free lanes; the player takes the front last.
@ Milotic -> Nihilego: (15,11) -> (15,14) -> (14,14), faces west.
@ Milotic -> Guzzlord: (15,11) -> (15,13) -> east to (21,13), faces south.
@ Snorlax -> Kartana: (20,14) -> (20,13) -> west to (15,13) -> (15,11)
@                     -> (14,11), faces north. Always AFTER Milotic's walk.
@ Player -> Kartana (14,11) up; Guzzlord (20,14) east; Nihilego (14,14) west.
@ Every partner that walks gets its template synced (setobjectxyperm).
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBChoose::
	setflag FLAG_NEWBARK_UB_ENGAGED
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBChoosePrompt, MSGBOX_DEFAULT
	dynmultichoice 0, 0, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, NewBarkTown_Text_ChoiceKartana, NewBarkTown_Text_ChoiceGuzzlord, NewBarkTown_Text_ChoiceNihilego
	copyvar VAR_TEMP_3, VAR_RESULT               @ 0 Kartana, 1 Guzzlord, 2 Nihilego
	closemessage
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPickGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPickNihilego
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	msgbox NewBarkTown_Text_UBPickedKartanaLusamine, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBPickedKartanaAnabel, MSGBOX_DEFAULT
	closemessage
	call NewBarkTown_EventScript_UBMiloticToNihilego
	goto NewBarkTown_EventScript_UBRivalCover

NewBarkTown_EventScript_UBPickGuzzlord::
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	msgbox NewBarkTown_Text_UBPickedGuzzlordAnabel, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBPickedGuzzlordLusamine, MSGBOX_DEFAULT
	closemessage
	call NewBarkTown_EventScript_UBMiloticToNihilego
	call NewBarkTown_EventScript_UBSnorlaxToKartana
	goto NewBarkTown_EventScript_UBRivalCover

@ Lusamine follows Nihilego with her eyes for a moment before she answers -
@ Nihilego (13,14) is straight south of her control (13,11). A hesitation, not
@ an argument, and the beast is nobody's property.
NewBarkTown_EventScript_UBPickNihilego::
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_SOUTH
	delay 40
	msgbox NewBarkTown_Text_UBPickedNihilegoLusamine, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBPickedNihilegoAnabel, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_LUSAMINE, DIR_EAST
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_MiloticToGuzzlord
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	setobjectxyperm LOCALID_NEWBARK_UB_MILOTIC, 21, 13
	setobjectmovementtype LOCALID_NEWBARK_UB_MILOTIC, MOVEMENT_TYPE_FACE_DOWN
	call NewBarkTown_EventScript_UBSnorlaxToKartana
	goto NewBarkTown_EventScript_UBRivalCover

NewBarkTown_EventScript_UBMiloticToNihilego::
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_MiloticToNihilego
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	setobjectxyperm LOCALID_NEWBARK_UB_MILOTIC, 14, 14
	setobjectmovementtype LOCALID_NEWBARK_UB_MILOTIC, MOVEMENT_TYPE_FACE_LEFT
	return

NewBarkTown_EventScript_UBSnorlaxToKartana::
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_SnorlaxToKartana
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
	setobjectxyperm LOCALID_NEWBARK_UB_SNORLAX, 14, 11
	setobjectmovementtype LOCALID_NEWBARK_UB_SNORLAX, MOVEMENT_TYPE_FACE_UP
	return

@ Gold/Crystal hold the way back in every branch - no double battle. Then the
@ player takes the chosen front.
NewBarkTown_EventScript_UBRivalCover::
	msgbox NewBarkTown_Text_UBRivalCover, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBPlayerToGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBPlayerToNihilego
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToKartana
	waitmovement OBJ_EVENT_ID_PLAYER
	goto NewBarkTown_EventScript_UBBattle

NewBarkTown_EventScript_UBPlayerToGuzzlord::
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToGuzzlord
	waitmovement OBJ_EVENT_ID_PLAYER
	goto NewBarkTown_EventScript_UBBattle

NewBarkTown_EventScript_UBPlayerToNihilego::
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerToNihilego
	waitmovement OBJ_EVENT_ID_PLAYER
	goto NewBarkTown_EventScript_UBBattle

@ ----------------------------------------------------------------------------
@ Boss battle through the project's boss system, which only survives a SIMPLE
@ battle. B_FLAG_NO_WHITEOUT is deliberately NOT set: losing is a blackout and
@ a retry. Running is not blocked: "Run" in a boss is forfeiting
@ (CanPlayerForfeitBattle, src/battle_main.c) and counts as a loss.
@ Capture is blocked while the link is still active (B_FLAG_NO_CATCHING,
@ cleared by the engine after the battle).
@
@ Fourth step of the ladder after Blackthorn (3 bars / Lv75 / x120), Mahogany
@ (4 / Lv80 / x130) and Cherrygrove (4 / Lv85 / x140). Unchanged by the V2
@ script. If playtesting says "wall" instead of "threat", turn the screws in
@ this order, one at a time:
@   1. drop the held item from the boss that gets complained about
@   2. multiplier 150 -> 145 -> 140
@   3. swap the setup/control move for a fourth attacking move
@   4. level 90 -> 85
@ Macro order is the same as bosslegendaryencounterwithmoves
@ (asm/macros/event.inc): setbossbattle -> playmoncry -> seteventmon ->
@ seteventmonmoves -> special. No path leaves the script in between.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBBattle::
	setflag B_FLAG_NO_CATCHING
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBSetupGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBSetupNihilego
	@ Kartana - the one that CLIMBS. Paper defenses, Swords Dance, a pure
	@ damage item: it either snowballs or it dies.
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_KARTANA, 90, ITEM_MUSCLE_BAND
	seteventmonmoves MOVE_SWORDS_DANCE, MOVE_LEAF_BLADE, MOVE_SACRED_SWORD, MOVE_SMART_STRIKE
	goto NewBarkTown_EventScript_UBStartBattle

@ Guzzlord - the one that ENDURES. Absurd HP, Leftovers and Toxic: attrition.
NewBarkTown_EventScript_UBSetupGuzzlord::
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_GUZZLORD, 90, ITEM_LEFTOVERS
	seteventmonmoves MOVE_TOXIC, MOVE_CRUNCH, MOVE_HEAVY_SLAM, MOVE_DRAGON_TAIL
	goto NewBarkTown_EventScript_UBStartBattle

@ Nihilego - the one that INTERFERES. Acid Spray shreds the player's Sp.Def,
@ Toxic stacks on top, and Black Sludge heals it for being Poison.
NewBarkTown_EventScript_UBSetupNihilego::
	setbossbattle 4, SPECIES_NONE, 150, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_NIHILEGO, 90, ITEM_BLACK_SLUDGE
	seteventmonmoves MOVE_ACID_SPRAY, MOVE_TOXIC, MOVE_POWER_GEM, MOVE_SLUDGE_WAVE

@ LOST, DREW and FORFEITED never come back here - the engine blacks the player
@ out and hands them back HEALED at (20,12) (DoWhiteOut heals; New Bark has no
@ Center), and FLAG_NEWBARK_UB_ENGAGED makes that load a retry. CAUGHT and RAN
@ are unreachable but handled: anything that is not WON is a retry.
NewBarkTown_EventScript_UBStartBattle::
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, NewBarkTown_EventScript_UBResolved
	goto NewBarkTown_EventScript_UBUnresolved

@ Interrupted, not lost - and nobody says the beasts escaped. Nothing past the
@ checkpoint happened yet: no field, no Necrozma. The reload puts the street
@ back as a retry, with the player on the arrival tile.
NewBarkTown_EventScript_UBUnresolved::
	msgbox NewBarkTown_Text_UBUnresolved, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
	waitstate
	releaseall
	end

@ ----------------------------------------------------------------------------
@ The defence works (V2 section 11). A battle does not reload the map, so every
@ object is where the scene left it; ON_LOAD re-applied the cut fence and the
@ broken barricade. The threat theme is set again and the player's beast is
@ shown weakened first. Then the player steps back to the command spot (16,12)
@ - "returns to the scene after the battle" - which re-frames the street, and
@ Milotic and Snorlax finish their fronts one at a time.
@ Back to (16,12):  from (14,11) east, east, south;
@                   from (20,14) north, west x4, north;
@                   from (14,14) east, east, north, north.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBResolved::
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAfterGuzzlord
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBAfterNihilego
	@ Kartana: Milotic has Nihilego (west of it), Snorlax has Guzzlord (east).
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_Weakened
	playmoncry SPECIES_KARTANA, CRY_MODE_WEAK
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerBackFromKartana
	waitmovement OBJ_EVENT_ID_PLAYER
	call NewBarkTown_EventScript_UBMiloticFinishesWest
	call NewBarkTown_EventScript_UBSnorlaxFinishesEast
	goto NewBarkTown_EventScript_UBFieldStarts

NewBarkTown_EventScript_UBAfterGuzzlord::
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_Weakened
	playmoncry SPECIES_GUZZLORD, CRY_MODE_WEAK
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerBackFromGuzzlord
	waitmovement OBJ_EVENT_ID_PLAYER
	call NewBarkTown_EventScript_UBMiloticFinishesWest
	call NewBarkTown_EventScript_UBSnorlaxFinishesNorth
	goto NewBarkTown_EventScript_UBFieldStarts

NewBarkTown_EventScript_UBAfterNihilego::
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_Weakened
	playmoncry SPECIES_NIHILEGO, CRY_MODE_WEAK
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	waitmoncry
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_PlayerBackFromNihilego
	waitmovement OBJ_EVENT_ID_PLAYER
	call NewBarkTown_EventScript_UBMiloticFinishesSouth
	call NewBarkTown_EventScript_UBSnorlaxFinishesNorth
	goto NewBarkTown_EventScript_UBFieldStarts

NewBarkTown_EventScript_UBMiloticFinishesWest::
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_AttackLeft
	playmoncry SPECIES_MILOTIC, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_Weakened
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	waitmoncry
	return

NewBarkTown_EventScript_UBMiloticFinishesSouth::
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_AttackDown
	playmoncry SPECIES_MILOTIC, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_Weakened
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	waitmoncry
	return

NewBarkTown_EventScript_UBSnorlaxFinishesEast::
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_AttackRight
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_Weakened
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	waitmoncry
	return

NewBarkTown_EventScript_UBSnorlaxFinishesNorth::
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_AttackUp
	playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_Weakened
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	waitmoncry
	return

@ The field comes up between the emitters and the links from the three beasts
@ to their openings weaken and drop - one sparkle and one reading per beast,
@ BEFORE anyone announces success. The beasts do not vanish or freeze.
@ Elm speaks from his station, in frame at (11,10). Then Anabel readies an
@ ordinary police Ball for the player's beast - not Kurt's Beast Ball, nothing
@ from the player's bag.
NewBarkTown_EventScript_UBFieldStarts::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBAfterBattleAnabel, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Text_UBAfterBattleLusamine, MSGBOX_DEFAULT
	closemessage
	playse SE_PC_ON
	waitse
	call NewBarkTown_EventScript_UBFieldLine
	playse SE_M_REFLECT
	dofieldeffectsparkle 14, 10, 0
	waitfieldeffect FLDEFF_SPARKLE
	call NewBarkTown_EventScript_UBBeep
	dofieldeffectsparkle 21, 14, 0
	waitfieldeffect FLDEFF_SPARKLE
	call NewBarkTown_EventScript_UBBeep
	dofieldeffectsparkle 13, 14, 0
	waitfieldeffect FLDEFF_SPARKLE
	call NewBarkTown_EventScript_UBBeep
	waitse
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_ELM, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_ELM
	msgbox NewBarkTown_Text_UBFieldWorks, MSGBOX_DEFAULT
	closemessage
	call NewBarkTown_EventScript_UBAnabelFacesTarget
	msgbox NewBarkTown_Text_UBCaptureStart, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBNecrozma

@ Anabel (18,14) turns to the player's beast: Guzzlord (21,14) is east of
@ her; Kartana (14,10) and Nihilego (13,14) are west.
NewBarkTown_EventScript_UBAnabelFacesTarget::
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAnabelFacesEast
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
	return
NewBarkTown_EventScript_UBAnabelFacesEast::
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_EAST
	return

@ ----------------------------------------------------------------------------
@ Necrozma forces the containment (V2 section 12).
@ Anabel and Elm catch the known pulse; a distortion opens OUTSIDE the area,
@ in the flower bed (16,9), three tiles from the nearest trainer, and Necrozma
@ comes through it. The field first BLOCKS its filaments (a shock of light
@ at both emitters, and nothing is dragged). Anabel throws. Necrozma raises the
@ pulse while the Ball is in the air, the field's edge fails, Gold/Crystal
@ send Azumarill to cover Lusamine's step back, the restored link throws the
@ Ball back intact, and Lusamine shuts the emitters down.
@ Then the three are pulled: each resists, facing away, while Snorlax and
@ Milotic strike at the filaments, and each turns to light where it stands -
@ nothing solid is crossed in bodily form. Only their three actors go.
@ Azumarill (13,12) -> (14,12), free in every branch once the player is back.
@ Lusamine (13,11) -> (13,12), facing kept.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBNecrozma::
	playse SE_M_DETECT
	applymovement LOCALID_NEWBARK_UB_ANABEL, Common_Movement_ExclamationMark
	applymovement LOCALID_NEWBARK_UB_ELM, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_ANABEL
	waitmovement LOCALID_NEWBARK_UB_ELM
	waitse
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	call NewBarkTown_EventScript_UBShake
	playse SE_WARP_IN
	dofieldeffectsparkle 16, 9, 0
	fadescreenswapbuffers FADE_TO_WHITE
	clearflag FLAG_TEMP_5
	addobject LOCALID_NEWBARK_UB_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	waitfieldeffect FLDEFF_SPARKLE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox NewBarkTown_Text_UBNecrozmaArrives, MSGBOX_DEFAULT
	closemessage
	@ First the field holds.
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
	playse SE_M_REFLECT
	dofieldeffectsparkle 12, 11, 0
	dofieldeffectsparkle 22, 12, 0
	call NewBarkTown_EventScript_UBFlash
	waitfieldeffect FLDEFF_SPARKLE
	waitse
	msgbox NewBarkTown_Text_UBFieldHolding, MSGBOX_DEFAULT
	closemessage
	@ The throw, and the pulse rising while the Ball is in the air.
	call NewBarkTown_EventScript_UBAnabelThrows
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
	dofieldeffectsparkle 12, 11, 0
	dofieldeffectsparkle 22, 12, 0
	call NewBarkTown_EventScript_UBRiftPulse
	waitfieldeffect FLDEFF_SPARKLE
	waitmoncry
	msgbox NewBarkTown_Text_UBFieldStrain, MSGBOX_DEFAULT
	closemessage
	msgbox NewBarkTown_Text_UBRivalRetreat, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillCovers
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_BackOffSouth
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
	@ The link comes back and throws the Ball off, intact.
	call NewBarkTown_EventScript_UBTargetStartles
	playse SE_M_REFLECT
	waitse
	playse SE_BALL_BOUNCE_1
	waitse
	@ Lusamine shuts the device down before it discharges beside the team.
	playse SE_PC_OFF
	dofieldeffectsparkle 12, 11, 0
	dofieldeffectsparkle 22, 12, 0
	waitfieldeffect FLDEFF_SPARKLE
	waitse
	@ The pull.
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
	applymovement LOCALID_NEWBARK_UB_KARTANA, NewBarkTown_Movement_ResistLeft
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, NewBarkTown_Movement_ResistDown
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, NewBarkTown_Movement_ResistDown
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_AttackUp
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_AttackUp
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	waitmoncry
	call NewBarkTown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_NEWBARK_UB_KARTANA
	removeobject LOCALID_NEWBARK_UB_GUZZLORD
	removeobject LOCALID_NEWBARK_UB_NIHILEGO
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox NewBarkTown_Text_UBAbsorbed, MSGBOX_DEFAULT
	closemessage
	goto NewBarkTown_EventScript_UBUltra

@ Anabel's throw, toward the player's beast.
NewBarkTown_EventScript_UBAnabelThrows::
	playse SE_BALL_THROW
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBAnabelThrowsEast
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_AttackLeft
	waitmovement LOCALID_NEWBARK_UB_ANABEL
	waitse
	return
NewBarkTown_EventScript_UBAnabelThrowsEast::
	applymovement LOCALID_NEWBARK_UB_ANABEL, NewBarkTown_Movement_AttackRight
	waitmovement LOCALID_NEWBARK_UB_ANABEL
	waitse
	return

NewBarkTown_EventScript_UBTargetStartles::
	goto_if_eq VAR_TEMP_3, 1, NewBarkTown_EventScript_UBGuzzlordStartles
	goto_if_eq VAR_TEMP_3, 2, NewBarkTown_EventScript_UBNihilegoStartles
	applymovement LOCALID_NEWBARK_UB_KARTANA, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_KARTANA
	return
NewBarkTown_EventScript_UBGuzzlordStartles::
	applymovement LOCALID_NEWBARK_UB_GUZZLORD, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_GUZZLORD
	return
NewBarkTown_EventScript_UBNihilegoStartles::
	applymovement LOCALID_NEWBARK_UB_NIHILEGO, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_NIHILEGO
	return

@ ----------------------------------------------------------------------------
@ Ultra Necrozma - transformation and instability (V2 section 13).
@ The beasts are already gone. The light grows, a pause, and the actor changes
@ on the SAME tile (16,9) under one flash: normal and Ultra never exist at the
@ same time (FLAG_TEMP_5 / FLAG_TEMP_6, one slot). The new silhouette is on
@ screen before any text. OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA
@ (include/config/overworld.h) compiles its own sprite - no Substitute.
@ The pulse drives the line back: the player (16,12) -> (16,13) and Lusamine
@ (13,12) -> (12,12), both still facing it; Snorlax, Milotic and Azumarill
@ brace. Nobody falls, nobody attacks in sync, and there is no forced-loss
@ battle. Then the clue: the light fails in uneven pulses and the three small
@ openings start to contract - BEFORE and regardless of any partner.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBUltra::
	applymovement LOCALID_NEWBARK_UB_NECROZMA, NewBarkTown_Movement_PulseDown
	waitmovement LOCALID_NEWBARK_UB_NECROZMA
	call NewBarkTown_EventScript_UBShake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_NEWBARK_UB_NECROZMA
	clearflag FLAG_TEMP_6
	addobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 30
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox NewBarkTown_Text_UBUltraRises, MSGBOX_DEFAULT
	closemessage
	msgbox NewBarkTown_Text_UBUltraRetreat, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFlare
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	call NewBarkTown_EventScript_UBFlash
	setvar VAR_0x8004, 3   @ vertical pan
	setvar VAR_0x8005, 2   @ horizontal pan
	setvar VAR_0x8006, 24  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_BackOffSouth
	applymovement LOCALID_NEWBARK_UB_LUSAMINE, NewBarkTown_Movement_BackOffWest
	applymovement LOCALID_NEWBARK_UB_SNORLAX, NewBarkTown_Movement_Brace
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_Brace
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_Brace
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_NEWBARK_UB_LUSAMINE
	waitmovement LOCALID_NEWBARK_UB_SNORLAX
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
	delay 30
	@ The clue: uneven light, the openings closing in.
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_UltraFalters
	call NewBarkTown_EventScript_UBRiftPulse
	dofieldeffectsparkle 14, 9, 0
	dofieldeffectsparkle 21, 16, 0
	dofieldeffectsparkle 13, 16, 0
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	waitfieldeffect FLDEFF_SPARKLE
	msgbox NewBarkTown_Text_UBUltraUnstable, MSGBOX_DEFAULT
	closemessage
	call NewBarkTown_EventScript_UBPartner
	goto NewBarkTown_EventScript_UBRetreat

@ ----------------------------------------------------------------------------
@ The player's partner - every branch (V2 section 14). CheckMysteryEggPokemon
@ is sampled AFTER the battle (the battle can evolve it) and returns the first
@ eligible one in party order, so actor, cry and {STR_VAR_1} agree. It comes
@ out of its Ball at (17,13), east of the player - the sheltered side, out of
@ the line of light - BEFORE anything is said about it, and goes back into it
@ before the retreat is over. The optional reactions condition nothing.
@ In every branch Azumarill takes the last step back, (14,12) -> (14,13): the
@ rival's retreat - covered by Solgaleo/Lunala's light when it is there.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBPartner::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, NewBarkTown_EventScript_UBNoPartner
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_BALL_OPEN
	clearflag FLAG_TEMP_C
	call NewBarkTown_EventScript_UBAddPartner
	waitse
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
	waitmoncry
	@ It turns toward it for a moment - and its light keeps failing.
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_LookAtPartner
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	call NewBarkTown_EventScript_UBRiftPulse
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, NewBarkTown_EventScript_UBPartnerLegend
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, NewBarkTown_EventScript_UBPartnerLegend
	@ Cosmog / Cosmoem: kept beside the player; it only floats, so nothing
	@ walks. Not bait, not to blame, not immune.
	msgbox NewBarkTown_Text_UBUltraSensesCosmog, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_MILOTIC, NewBarkTown_Movement_Brace
	waitmovement LOCALID_NEWBARK_UB_MILOTIC
	call NewBarkTown_EventScript_UBRecallPartner
	goto NewBarkTown_EventScript_UBAzumarillLastStep

@ Solgaleo / Lunala: a cry and a pulse; a band of light between the rupture
@ and the rear (sparkles on the diagonal back toward the lab) steadies the
@ edge for a moment - long enough for the rival's last step back. The body
@ keeps wavering; it takes no energy from the partner and is not afraid of it.
NewBarkTown_EventScript_UBPartnerLegend::
	playmoncry VAR_TEMP_4, CRY_MODE_ENCOUNTER
	call NewBarkTown_EventScript_UBFlash
	dofieldeffectsparkle 16, 11, 0
	dofieldeffectsparkle 15, 12, 0
	dofieldeffectsparkle 14, 13, 0
	waitfieldeffect FLDEFF_SPARKLE
	waitmoncry
	msgbox NewBarkTown_Text_UBUltraPartner, MSGBOX_DEFAULT
	closemessage
	call NewBarkTown_EventScript_UBAzumarillLastStepCall
	msgbox NewBarkTown_Text_UBRivalPartnerCover, MSGBOX_DEFAULT
	closemessage
	call NewBarkTown_EventScript_UBRecallPartner
	call NewBarkTown_EventScript_UBRiftPulse
	return

NewBarkTown_EventScript_UBNoPartner::
NewBarkTown_EventScript_UBAzumarillLastStep::
	call NewBarkTown_EventScript_UBAzumarillLastStepCall
	return

NewBarkTown_EventScript_UBAzumarillLastStepCall::
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_BackOffSouth
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
	return

NewBarkTown_EventScript_UBAddPartner::
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, NewBarkTown_EventScript_UBAddCosmoem
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, NewBarkTown_EventScript_UBAddSolgaleo
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, NewBarkTown_EventScript_UBAddLunala
	addobject LOCALID_NEWBARK_UB_COSMOG
	return
NewBarkTown_EventScript_UBAddCosmoem::
	addobject LOCALID_NEWBARK_UB_COSMOEM
	return
NewBarkTown_EventScript_UBAddSolgaleo::
	addobject LOCALID_NEWBARK_UB_SOLGALEO
	return
NewBarkTown_EventScript_UBAddLunala::
	addobject LOCALID_NEWBARK_UB_LUNALA
	return

@ Back into its Ball, on screen. removeobject on the three that were never
@ added is a no-op.
NewBarkTown_EventScript_UBRecallPartner::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	playse SE_BALL_OPEN
	removeobject LOCALID_NEWBARK_UB_COSMOG
	removeobject LOCALID_NEWBARK_UB_COSMOEM
	removeobject LOCALID_NEWBARK_UB_SOLGALEO
	removeobject LOCALID_NEWBARK_UB_LUNALA
	waitse
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	return

@ ----------------------------------------------------------------------------
@ The retreat and the record of nine (V2 section 15).
@ It tries another pulse and fails. The main opening opens beside it (17,9) -
@ the one object that exists only now, when the beasts are gone and the
@ budget allows it - and Ultra Necrozma backs into it, still facing the
@ street; it goes under a flash. The small openings contract the same way
@ and close after it. No actor is teleported.
@ Elm's record: nine patterns in groups - three pairs from the earlier
@ missions, then the three from here - on the instrument the street has
@ already seen, compared and not counted from memory.
@ Only after the openings are confirmed closed does the threat theme end.
@ Then the partners are recalled on screen once they are no longer needed,
@ and Looker checks the broken barricade.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBRetreat::
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_PulseDown
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	call NewBarkTown_EventScript_UBRiftPulse
	clearflag FLAG_TEMP_B
	playse SE_WARP_IN
	addobject LOCALID_NEWBARK_UB_RIFT
	waitse
	applymovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA, NewBarkTown_Movement_BacksIntoRift
	waitmovement LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_NEWBARK_UB_ULTRA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	delay 20
	dofieldeffectsparkle 14, 9, 0
	dofieldeffectsparkle 21, 16, 0
	dofieldeffectsparkle 13, 16, 0
	playse SE_WARP_OUT
	call NewBarkTown_EventScript_UBRiftPulse
	removeobject LOCALID_NEWBARK_UB_RIFT
	waitfieldeffect FLDEFF_SPARKLE
	delay 20
	@ Nine patterns, in groups: 2, 2, 2 - and 3.
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_NEWBARK_UB_ELM, Common_Movement_ExclamationMark
	waitmovement LOCALID_NEWBARK_UB_ELM
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	delay 12
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	delay 12
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	delay 24
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	call NewBarkTown_EventScript_UBBeep
	msgbox NewBarkTown_Text_UBElmNine, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBAnabelNine, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBElmConfirms, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBStreetClear, MSGBOX_DEFAULT
	closemessage
	delay 40
	fadedefaultbgm
	@ Milotic and Snorlax go back into their Balls.
	playse SE_BALL_OPEN
	removeobject LOCALID_NEWBARK_UB_MILOTIC
	waitse
	playse SE_BALL_OPEN
	removeobject LOCALID_NEWBARK_UB_SNORLAX
	waitse
	@ Looker (21,12) -> (21,13), looks at the broken barricade, and back.
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerChecksSouth
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	goto NewBarkTown_EventScript_UBAftermath

@ ----------------------------------------------------------------------------
@ Aftermath - people and outcome (V2 sections 16 and 17).
@ The player steps back up to (16,12). Looker comes to (17,12), east of the
@ player. The shelter door opens only after the check, and Mom appears in it,
@ stepping down to (10,10). Gold/Crystal walk (11,12) -> (11,13) -> (13,13) to
@ look at Azumarill (14,13) east of them; the player's answer is a gesture.
@ Then they go to check the cut fence: (13,13) -> (13,12) -> (13,11) ->
@ (14,11), facing it, with Azumarill (14,13) -> (14,12) behind them.
@ Everyone who speaks is on y <= 14, above the text box. The player turns to
@ each speaker: Looker/Anabel east, Mom/Elm/Lusamine/rival west.
@ ----------------------------------------------------------------------------
NewBarkTown_EventScript_UBAftermath::
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_StepUp
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_NEWBARK_UB_LOOKER, NewBarkTown_Movement_LookerToGroup
	waitmovement LOCALID_NEWBARK_UB_LOOKER
	opendoor 10, 9
	waitdooranim
	setobjectxyperm LOCALID_NEWBARK_UB_MOM, 10, 9
	setobjectmovementtype LOCALID_NEWBARK_UB_MOM, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_TEMP_4
	addobject LOCALID_NEWBARK_UB_MOM
	applymovement LOCALID_NEWBARK_UB_MOM, NewBarkTown_Movement_StepDown
	waitmovement LOCALID_NEWBARK_UB_MOM
	closedoor 10, 9
	waitdooranim
	turnobject LOCALID_NEWBARK_UB_MOM, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBAftermathLooker, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_RIVAL, NewBarkTown_Movement_RivalToAzumarill
	waitmovement LOCALID_NEWBARK_UB_RIVAL
	turnobject LOCALID_NEWBARK_UB_AZUMARILL, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	delay 16
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Movement_Nod
	waitmovement OBJ_EVENT_ID_PLAYER
	msgbox NewBarkTown_Text_UBAftermathRival, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBLookerRivalThanks, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_NEWBARK_UB_RIVAL, NewBarkTown_Movement_RivalChecksFence
	waitmovement LOCALID_NEWBARK_UB_RIVAL
	applymovement LOCALID_NEWBARK_UB_AZUMARILL, NewBarkTown_Movement_AzumarillFollows
	waitmovement LOCALID_NEWBARK_UB_AZUMARILL
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Text_UBMomAftermath, MSGBOX_DEFAULT
	closemessage
	msgbox NewBarkTown_Text_UBAftermathLusamine, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWBARK_UB_ANABEL, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBAftermathAnabel, MSGBOX_DEFAULT
	closemessage
	@ The way to Olivine and the Altar (section 17).
	turnobject LOCALID_NEWBARK_UB_ELM, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Text_UBElmDirection, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBAnabelCompare, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Text_UBLusamineRecords, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBLusamineChildren, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox NewBarkTown_Text_UBLookerReunion, MSGBOX_DEFAULT
	msgbox NewBarkTown_Text_UBHook, MSGBOX_DEFAULT
	closemessage
	@ The explicit time transition for the barriers and the equipment.
	msgbox NewBarkTown_Text_UBRepairs, MSGBOX_DEFAULT
	closemessage

@ Resolution (V2 section 18): state 10, and the event flag cleared WITH it
@ (invariant: FLAG_EVENT_ULTRABEAST_NEWBARK set <=> state 9).
@ FLAG_DAILY_LOOKER_CALL is deliberately NOT set here: if the New Bark call was
@ on an earlier day, the reunion call may ring today once the player is back in
@ free control (data/scripts/rift_missions.inc).
@ Reload in place under the fade: the fence, the logs and the emitters go (the
@ layout has none of them), the seven residents come back by their own flags,
@ Mom is home, Elm is in his lab, the cast is gone, and the follower returns
@ once (FLAG_TEMP_HIDE_FOLLOWER is a temp).
NewBarkTown_EventScript_UBFinish::
	fadescreen FADE_TO_BLACK
	clearflag FLAG_EVENT_ULTRABEAST_NEWBARK
	clearflag FLAG_NEWBARK_UB_ENGAGED
	setvar VAR_RIFT_MISSIONS_STATE, 10
	warpsilent MAP_NEW_BARK_TOWN, 20, 12
	waitstate
	releaseall
	end

@ ----------------------------------------------------------------------------
@ Movements. Every tile was checked with dump_mapa.py.
@ ----------------------------------------------------------------------------

@ (20,12) -> (16,12).
NewBarkTown_Movement_PlayerToCommand:
	walk_left
	walk_left
	walk_left
	walk_left
	face_up
	step_end

@ Retry from (21,13): (20,13) .. (16,13), then (16,12).
NewBarkTown_Movement_PlayerRetryFromSouth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end

@ Anabel (22,12) -> (22,13), turns back to the tile she left.
NewBarkTown_Movement_StepDownFaceUp:
	walk_down
	face_up
	step_end

@ Anabel (22,13) -> (22,14) -> (21,14) -> (20,14) -> (19,14) -> (18,14).
NewBarkTown_Movement_AnabelToPost:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_right
	step_end

NewBarkTown_Movement_NodLeft:
	walk_in_place_slow_left
	step_end

NewBarkTown_Movement_Nod:
	walk_in_place_slow_left
	step_end

NewBarkTown_Movement_StepDown:
	walk_down
	step_end

NewBarkTown_Movement_StepUp:
	walk_up
	step_end

NewBarkTown_Movement_StepUpTwice:
	walk_up
	walk_up
	step_end

NewBarkTown_Movement_AttackDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

NewBarkTown_Movement_AttackUp:
	walk_in_place_fast_up
	walk_in_place_fast_up
	step_end

NewBarkTown_Movement_AttackLeft:
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

NewBarkTown_Movement_AttackRight:
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

@ (21,16) -> (21,15) -> (21,14), over the logs it just broke.
NewBarkTown_Movement_GuzzlordAdvances:
	walk_slow_up
	walk_slow_up
	step_end

@ (21,13) -> (16,13). Five steps at normal speed: she is there before
@ Nihilego's three slow ones end.
NewBarkTown_Movement_MomCrosses:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ (13,16) -> (13,13), slow.
NewBarkTown_Movement_NihilegoDrifts:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

@ (12,12) -> (13,12), facing the beast below.
NewBarkTown_Movement_AzumarillIntercepts:
	walk_fast_right
	face_down
	step_end

@ Pushed one tile, still facing the one that pushed it.
NewBarkTown_Movement_KnockedBackDown:
	lock_facing_direction
	walk_fast_down
	unlock_facing_direction
	step_end

@ Lusamine (13,11) -> (14,11) -> (14,12) -> (14,13) -> (15,13), faces east.
NewBarkTown_Movement_LusamineToMom:
	walk_right
	walk_down
	walk_down
	walk_right
	face_right
	step_end

@ And back: (15,13) -> (14,13) -> (14,12) -> (14,11) -> (13,11), faces east.
NewBarkTown_Movement_LusamineBackToControl:
	walk_left
	walk_up
	walk_up
	walk_left
	face_right
	step_end

@ Looker (21,12) -> (21,13) -> (17,13), behind Mom.
NewBarkTown_Movement_LookerToMom:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

@ Mom (16,13) -> (10,13) -> (10,10).
NewBarkTown_Movement_MomToLab:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

@ Looker (17,13) -> (10,13) -> (10,11): the same path, one step behind.
NewBarkTown_Movement_LookerToLab:
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

@ Looker (10,10) -> (10,13) -> (21,13) -> (21,12), faces west.
NewBarkTown_Movement_LookerBackToPost:
	walk_fast_down
	walk_fast_down
	walk_fast_down
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
	walk_fast_up
	face_left
	step_end

@ Milotic (15,11) -> (15,14) -> (14,14), faces west (Nihilego at (13,14)).
NewBarkTown_Movement_MiloticToNihilego:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	face_left
	step_end

@ Milotic (15,11) -> (15,13) -> (21,13), faces south (Guzzlord at (21,14)).
NewBarkTown_Movement_MiloticToGuzzlord:
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end

@ Snorlax (20,14) -> (20,13) -> (15,13) -> (15,11) -> (14,11), faces north
@ (Kartana at (14,10)).
NewBarkTown_Movement_SnorlaxToKartana:
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_up
	step_end

@ Player (16,12) -> (15,12) -> (14,12) -> (14,11), faces Kartana.
NewBarkTown_Movement_PlayerToKartana:
	walk_left
	walk_left
	walk_up
	face_up
	step_end

@ Player (16,12) -> (16,13) -> (20,13) -> (20,14), faces Guzzlord.
NewBarkTown_Movement_PlayerToGuzzlord:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	face_right
	step_end

@ Player (16,12) -> (16,14) -> (14,14), faces Nihilego.
NewBarkTown_Movement_PlayerToNihilego:
	walk_down
	walk_down
	walk_left
	walk_left
	face_left
	step_end

@ (14,11) -> (14,12) -> (16,12).
NewBarkTown_Movement_PlayerBackFromKartana:
	walk_down
	walk_right
	walk_right
	face_up
	step_end

@ (20,14) -> (20,13) -> (16,13) -> (16,12).
NewBarkTown_Movement_PlayerBackFromGuzzlord:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	face_up
	step_end

@ (14,14) -> (16,14) -> (16,12).
NewBarkTown_Movement_PlayerBackFromNihilego:
	walk_right
	walk_right
	walk_up
	walk_up
	face_up
	step_end

NewBarkTown_Movement_Weakened:
	walk_in_place_slow_down
	walk_in_place_slow_down
	step_end

NewBarkTown_Movement_PulseDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

@ Struggling against the pull, facing kept.
NewBarkTown_Movement_ResistLeft:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_slow_left
	step_end

NewBarkTown_Movement_ResistDown:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_slow_down
	step_end

@ Azumarill (13,12) -> (14,12), facing the north front.
NewBarkTown_Movement_AzumarillCovers:
	walk_fast_right
	face_up
	step_end

@ One tile back, still facing the threat.
NewBarkTown_Movement_BackOffSouth:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

NewBarkTown_Movement_BackOffWest:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

NewBarkTown_Movement_Brace:
	walk_in_place_slow_up
	step_end

NewBarkTown_Movement_UltraFlare:
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	walk_in_place_fast_down
	step_end

@ Uneven pulses: slow, a gap, fast, a longer gap, slow.
NewBarkTown_Movement_UltraFalters:
	walk_in_place_slow_down
	delay_8
	walk_in_place_fast_down
	delay_16
	walk_in_place_slow_down
	step_end

@ A look toward the partner on the south-east, and back.
NewBarkTown_Movement_LookAtPartner:
	face_right
	delay_16
	face_down
	step_end

@ (16,9) -> (17,9), into the opening, facing kept.
NewBarkTown_Movement_BacksIntoRift:
	lock_facing_direction
	walk_slow_right
	unlock_facing_direction
	step_end

@ Looker (21,12) -> (21,13), looks south at the barricade, and back.
NewBarkTown_Movement_LookerChecksSouth:
	walk_down
	face_down
	delay_16
	delay_16
	walk_up
	face_left
	step_end

@ Looker (21,12) -> (17,12), east of the player.
NewBarkTown_Movement_LookerToGroup:
	walk_left
	walk_left
	walk_left
	walk_left
	face_left
	step_end

@ Gold/Crystal (11,12) -> (11,13) -> (13,13), facing Azumarill at (14,13).
NewBarkTown_Movement_RivalToAzumarill:
	walk_down
	walk_right
	walk_right
	face_right
	step_end

@ Gold/Crystal (13,13) -> (13,11) -> (14,11), facing the cut fence.
NewBarkTown_Movement_RivalChecksFence:
	walk_up
	walk_up
	walk_right
	face_up
	step_end

@ Azumarill (14,13) -> (14,12), behind them.
NewBarkTown_Movement_AzumarillFollows:
	walk_up
	face_up
	step_end


@ ============================================================================
@ Rift Mission 4 dialogue - final lines of NEWBARK_ULTRABEAST_SCRIPT_V2.md.
@ One speaker per message, the plaque opening every one of them. Gold/Crystal
@ wear NAME_NEIGHBOR, which shows "Gold" or "Crystal" by the rule the game
@ already uses (ExpandPlaceholder_Neighbor, src/string_util.c) - never Silver,
@ never NONE. The door note and the narration have NO plaque (author's
@ default): a message without {SPEAKER} gets none and inherits none.
@ No em dash anywhere: U+2014 is not in charmap.txt and breaks the build.
@ ============================================================================

@ --- Preparation (section 6) -------------------------------------------------

NewBarkTown_Text_UBLusamineIdle:
	.string "{SPEAKER NAME_LUSAMINE}{PLAYER}. I'm Lusamine.\n"
	.string "Anabel sent me the recordings.\p"
	.string "I'll handle the containment\n"
	.string "field. Keep this approach clear\l"
	.string "for the equipment.$"

@ Retry only: the field is prepared, not active - it needs weakened targets.
NewBarkTown_Text_UBLusamineRetry:
	.string "{SPEAKER NAME_LUSAMINE}The field is ready.\n"
	.string "It only works once they're\l"
	.string "weakened.$"

NewBarkTown_Text_UBElmIdle:
	.string "{SPEAKER NAME_ELM}Kukui asked for the old\n"
	.string "readings. I almost sent only\l"
	.string "the recent ones.\p"
	.string "The earlier pulses helped us\n"
	.string "find where to place the\l"
	.string "sensors.$"

@ YES/NO: "rested" YES leaves it; NO is the heal.
NewBarkTown_Text_UBMomIdle:
	.string "{SPEAKER NAME_MOM}There you are.\n"
	.string "We're nearly ready at the lab.\p"
	.string "Have you and your Pokémon\n"
	.string "rested?$"

NewBarkTown_Text_UBMomHeal:
	.string "{SPEAKER NAME_MOM}Let your Pokémon rest a\n"
	.string "moment. I'll take care of them.$"

NewBarkTown_Text_UBRivalIdle:
	.string "{SPEAKER NAME_NEIGHBOR}I've checked the houses.\n"
	.string "Azumarill and I will keep the\l"
	.string "path open.\p"
	.string "You handle whatever comes\n"
	.string "through.$"

NewBarkTown_Text_UBAnabelIdle:
	.string "{SPEAKER NAME_ANABEL}Elm's sensors are in place.\n"
	.string "We'll be able to compare all\l"
	.string "three openings.\p"
	.string "Speak with Looker when you're\n"
	.string "ready.$"

@ A note on the locked doors: no plaque.
NewBarkTown_Text_UBDoorNote:
	.string "Shelter is available at\n"
	.string "Professor Elm's lab.\p"
	.string "Please keep the main road\n"
	.string "clear.$"

@ --- Readiness and Aether's equipment (section 7) ----------------------------

NewBarkTown_Text_UBLookerGreet:
	.string "{SPEAKER NAME_LOOKER}The residents are almost\n"
	.string "inside. We have a clear route\l"
	.string "back to the lab.$"

NewBarkTown_Text_UBReady:
	.string "{SPEAKER NAME_LOOKER}Are you and your Pokémon\n"
	.string "ready?$"

NewBarkTown_Text_UBNotReady:
	.string "{SPEAKER NAME_LOOKER}Take care of your team\n"
	.string "first. We'll finish the\l"
	.string "preparations.$"

@ The equipment, by the author's rule: a portable Aether prototype that cuts
@ existing filaments inside a small area for a limited time, with continuous
@ operation. It opens and closes nothing, holds nobody and replaces no Ball.
@ It is NOT the passage stabilizer of the meeting.
NewBarkTown_Text_UBFieldExplanation:
	.string "{SPEAKER NAME_LUSAMINE}Once they're weakened, keep\n"
	.string "them between these markers.\p"
	.string "The field should interrupt the\n"
	.string "link. It won't stop them\l"
	.string "walking out.$"

NewBarkTown_Text_UBFieldPositions:
	.string "{SPEAKER NAME_ANABEL}Then we keep the Pokémon\n"
	.string "inside it.\p"
	.string "Looker, watch the route to the\n"
	.string "lab.$"

NewBarkTown_Text_UBElmPositions:
	.string "{SPEAKER NAME_ELM}I'll record the links from\n"
	.string "the lab. Keep the markers where\l"
	.string "they are.$"

NewBarkTown_Text_UBAnabelPartner:
	.string "{SPEAKER NAME_ANABEL}Snorlax, hold this side.\n"
	.string "Leave the middle clear.$"

NewBarkTown_Text_UBLusaminePartner:
	.string "{SPEAKER NAME_LUSAMINE}Milotic, with me.$"

@ --- Three openings (section 8) ----------------------------------------------

NewBarkTown_Text_UBAnabelOpening:
	.string "{SPEAKER NAME_ANABEL}They're opening.\n"
	.string "Clear the road!$"

NewBarkTown_Text_UBAppear:
	.string "{SPEAKER NAME_ANABEL}Kartana. Guzzlord. Nihilego.\n"
	.string "Keep the path to the lab clear.$"

NewBarkTown_Text_UBKartanaBreaks:
	.string "{SPEAKER NAME_NEIGHBOR}Kartana's opened the side\n"
	.string "path!$"

NewBarkTown_Text_UBGuzzlordBreaks:
	.string "{SPEAKER NAME_LOOKER}The south barrier's gone.\n"
	.string "Stay on this side!$"

NewBarkTown_Text_UBRivalIntercept:
	.string "{SPEAKER NAME_NEIGHBOR}Azumarill, push it back!\n"
	.string "Keep that path clear!$"

NewBarkTown_Text_UBAnabelCorridor:
	.string "{SPEAKER NAME_ANABEL}Good. Hold that gap.\n"
	.string "Looker, get the last residents\l"
	.string "inside.$"

@ --- Mom and Lusamine (section 9) --------------------------------------------

NewBarkTown_Text_UBLusamineControl:
	.string "{SPEAKER NAME_LUSAMINE}Take your child inside.\n"
	.string "I'll handle the front.$"

NewBarkTown_Text_UBMomTrust:
	.string "{SPEAKER NAME_MOM}{PLAYER} knows what they're\n"
	.string "doing. Let them help you.\p"
	.string "I'll get everyone inside.\n"
	.string "You won't have to watch this\l"
	.string "door too.$"

NewBarkTown_Text_UBLusamineAccepts:
	.string "{SPEAKER NAME_LUSAMINE}Very well.\n"
	.string "Anabel, which front do you\l"
	.string "need me on?$"

@ --- The choice (section 10) -------------------------------------------------

NewBarkTown_Text_UBChoosePrompt:
	.string "{SPEAKER NAME_ANABEL}Choose your target,\n"
	.string "{PLAYER}. We'll keep the other\l"
	.string "two off you.$"

NewBarkTown_Text_ChoiceKartana:
	.string "Kartana$"

NewBarkTown_Text_ChoiceGuzzlord:
	.string "Guzzlord$"

NewBarkTown_Text_ChoiceNihilego:
	.string "Nihilego$"

NewBarkTown_Text_UBPickedKartanaLusamine:
	.string "{SPEAKER NAME_LUSAMINE}I'll keep Nihilego away from\n"
	.string "the houses. Milotic, this way.$"

NewBarkTown_Text_UBPickedKartanaAnabel:
	.string "{SPEAKER NAME_ANABEL}Snorlax and I have Guzzlord.\n"
	.string "Keep Kartana inside the\l"
	.string "markers.$"

NewBarkTown_Text_UBPickedGuzzlordAnabel:
	.string "{SPEAKER NAME_ANABEL}I'll block Kartana's path.\n"
	.string "Draw Guzzlord toward the\l"
	.string "cleared ground.$"

NewBarkTown_Text_UBPickedGuzzlordLusamine:
	.string "{SPEAKER NAME_LUSAMINE}Milotic, keep Nihilego here.$"

NewBarkTown_Text_UBPickedNihilegoLusamine:
	.string "{SPEAKER NAME_LUSAMINE}Then I'll take Guzzlord.\n"
	.string "Milotic, stay with me.$"

NewBarkTown_Text_UBPickedNihilegoAnabel:
	.string "{SPEAKER NAME_ANABEL}I'll hold Kartana.\n"
	.string "Keep Nihilego away from the\l"
	.string "entrance.$"

NewBarkTown_Text_UBRivalCover:
	.string "{SPEAKER NAME_NEIGHBOR}I've got the way back.\n"
	.string "Go ahead, {PLAYER}.$"

@ --- The defence works (section 11) ------------------------------------------

NewBarkTown_Text_UBAfterBattleAnabel:
	.string "{SPEAKER NAME_ANABEL}Our side is holding.\n"
	.string "Keep them inside the markers.$"

NewBarkTown_Text_UBAfterBattleLusamine:
	.string "{SPEAKER NAME_LUSAMINE}Milotic, hold there.\n"
	.string "I'm starting the field.$"

NewBarkTown_Text_UBFieldWorks:
	.string "{SPEAKER NAME_ELM}The links have dropped.\n"
	.string "All three Pokémon are still\l"
	.string "inside.$"

NewBarkTown_Text_UBCaptureStart:
	.string "{SPEAKER NAME_ANABEL}Keep the field running.\n"
	.string "I'll secure this one first.$"

@ --- Necrozma forces the containment (section 12) ----------------------------

NewBarkTown_Text_UBNecrozmaArrives:
	.string "{SPEAKER NAME_ANABEL}Necrozma.\n"
	.string "Keep the field up!$"

NewBarkTown_Text_UBFieldHolding:
	.string "{SPEAKER NAME_LUSAMINE}It's holding.\n"
	.string "Anabel, now!$"

NewBarkTown_Text_UBFieldStrain:
	.string "{SPEAKER NAME_ELM}The output is climbing!\n"
	.string "The field can't hold that\l"
	.string "level!$"

NewBarkTown_Text_UBRivalRetreat:
	.string "{SPEAKER NAME_NEIGHBOR}The path's clear!\n"
	.string "Azumarill, cover them!$"

NewBarkTown_Text_UBAbsorbed:
	.string "{SPEAKER NAME_ANABEL}Back behind the markers!\n"
	.string "Keep recording, Professor!$"

@ --- Ultra Necrozma (section 13) ---------------------------------------------

NewBarkTown_Text_UBUltraRises:
	.string "{SPEAKER NAME_ELM}The reading's still rising!$"

NewBarkTown_Text_UBUltraRetreat:
	.string "{SPEAKER NAME_ANABEL}Everyone back.\n"
	.string "Stay together!$"

NewBarkTown_Text_UBUltraUnstable:
	.string "{SPEAKER NAME_LUSAMINE}It can't hold that light\n"
	.string "steady. Keep your distance.$"

@ --- The partner (section 14) ------------------------------------------------

NewBarkTown_Text_UBUltraSensesCosmog:
	.string "{SPEAKER NAME_LUSAMINE}Keep {STR_VAR_1} beside you.\n"
	.string "Milotic, cover that side.$"

NewBarkTown_Text_UBUltraPartner:
	.string "{SPEAKER NAME_ANABEL}The edge is steady.\n"
	.string "Move now!$"

NewBarkTown_Text_UBRivalPartnerCover:
	.string "{SPEAKER NAME_NEIGHBOR}We're clear, {PLAYER}!\n"
	.string "Bring {STR_VAR_1} back with you!$"

@ --- The retreat and the nine (section 15) -----------------------------------

NewBarkTown_Text_UBElmNine:
	.string "{SPEAKER NAME_ELM}Nine patterns.\n"
	.string "Six match the earlier\l"
	.string "recordings.\p"
	.string "The other three are the ones\n"
	.string "from here.$"

NewBarkTown_Text_UBAnabelNine:
	.string "{SPEAKER NAME_ANABEL}They stayed distinct after\n"
	.string "the absorption?$"

NewBarkTown_Text_UBElmConfirms:
	.string "{SPEAKER NAME_ELM}Yes. Until the opening\n"
	.string "closed. I've saved the record.$"

NewBarkTown_Text_UBStreetClear:
	.string "{SPEAKER NAME_ANABEL}All three openings are\n"
	.string "closed.\p"
	.string "Check the street before we\n"
	.string "let anyone out.$"

@ --- Aftermath (section 16) --------------------------------------------------

NewBarkTown_Text_UBAftermathLooker:
	.string "{SPEAKER NAME_LOOKER}Everyone in the lab is safe.\n"
	.string "How are your Pokémon?$"

NewBarkTown_Text_UBAftermathRival:
	.string "{SPEAKER NAME_NEIGHBOR}Azumarill's ready for a\n"
	.string "rest. I'll check the side path\l"
	.string "first.$"

NewBarkTown_Text_UBLookerRivalThanks:
	.string "{SPEAKER NAME_LOOKER}You kept our way back open.\n"
	.string "Thank you.$"

NewBarkTown_Text_UBMomAftermath:
	.string "{SPEAKER NAME_MOM}Come home when you're ready,\n"
	.string "{PLAYER}. You and your Pokémon\l"
	.string "can rest there.$"

NewBarkTown_Text_UBAftermathLusamine:
	.string "{SPEAKER NAME_LUSAMINE}The field broke when Necrozma\n"
	.string "increased the flow. The Pokémon\l"
	.string "were contained until then.\p"
	.string "We have to stop the source.$"

NewBarkTown_Text_UBAftermathAnabel:
	.string "{SPEAKER NAME_ANABEL}We kept it away from the\n"
	.string "residents. We still need to\l"
	.string "get the Pokémon out.\p"
	.string "Next time, the operation has to\n"
	.string "be around Necrozma itself.$"

@ --- The way to Olivine and the Altar (section 17) ---------------------------

NewBarkTown_Text_UBElmDirection:
	.string "{SPEAKER NAME_ELM}All three openings closed\n"
	.string "toward this same point.\p"
	.string "I'll send the full record to\n"
	.string "Olivine.$"

NewBarkTown_Text_UBAnabelCompare:
	.string "{SPEAKER NAME_ANABEL}We'll compare it with\n"
	.string "Cherrygrove's bearing.\l"
	.string "That should narrow the search.$"

NewBarkTown_Text_UBLusamineRecords:
	.string "{SPEAKER NAME_LUSAMINE}I'll bring Aether's records\n"
	.string "too. You should have had them\l"
	.string "before today.$"

NewBarkTown_Text_UBLusamineChildren:
	.string "{SPEAKER NAME_LUSAMINE}Please ask Lillie and Gladion\n"
	.string "to join us. I want to hear what\l"
	.string "they found.$"

NewBarkTown_Text_UBLookerReunion:
	.string "{SPEAKER NAME_LOOKER}I'll contact them, and\n"
	.string "Professor Kukui. We'll arrange\l"
	.string "the meeting in Olivine.$"

NewBarkTown_Text_UBHook:
	.string "{SPEAKER NAME_LOOKER}Rest here for now, {PLAYER}.\n"
	.string "I'll call when we're ready in\l"
	.string "Olivine.$"

@ Narration, no plaque: the explicit time transition (section 18) that takes
@ the barriers and the equipment away before the reload. It names no hour of
@ the day (design 5.3): the scene can end at any time, night included.
NewBarkTown_Text_UBRepairs:
	.string "Later, the markers were packed\n"
	.string "away, the barriers were cleared,\l"
	.string "and the residents were back in\l"
	.string "their homes.$"

@ --- Retry (section 19) ------------------------------------------------------

NewBarkTown_Text_UBRetryLooker:
	.string "{SPEAKER NAME_LOOKER}The lab is safe.\n"
	.string "We've kept the way back clear.$"

NewBarkTown_Text_UBRetryAnabel:
	.string "{SPEAKER NAME_ANABEL}The field is ready.\n"
	.string "Are your Pokémon ready to try\l"
	.string "again?$"

NewBarkTown_Text_UBRetryNotReady:
	.string "{SPEAKER NAME_ANABEL}Take care of them first.\n"
	.string "We'll hold the fronts.$"

NewBarkTown_Text_UBUnresolved:
	.string "{SPEAKER NAME_ANABEL}The fronts aren't clear yet.\n"
	.string "Regroup before we try again.$"

NewBarkTown_EventScript_RivalIntro_Movement_0:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_1:
	jump_down
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_2:
	walk_up
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_3:
	jump_in_place_up
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_4:
	walk_right
	walk_right
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_5:
	face_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_6:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_7:
	jump_in_place_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_8:
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

NewBarkTown_EventScript_RivalIntro_Movement_9:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_0:
	jump_in_place_right
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_1:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_down
	face_left
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_2:
	face_up
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_3:
	walk_down
	walk_down
	walk_down
	walk_right
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_4:
	walk_fast_left
	face_right
	exit_pokeball
	set_visible
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_5:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Movement_6:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_EventScript_RivalBattle_Text_0:
	.string "{PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_1:
	.string "So you picked...\n"
	.string "a {STR_VAR_1}!$"

NewBarkTown_EventScript_RivalBattle_Text_2:
	.string "That's a cute Pokémon you have!$"

NewBarkTown_EventScript_RivalBattle_Text_3:
	.string "When you walk with it, it'll become\n"
	.string "more friendly!$"

NewBarkTown_EventScript_RivalBattle_Text_4:
	.string "You should turn around and talk to it\n"
	.string "sometimes, too.$"

NewBarkTown_EventScript_RivalBattle_Text_5:
	.string "Hey, why don't we have a battle?\n"
	.string "That's what trainers usually do when\l"
	.string "they meet!$"

NewBarkTown_EventScript_RivalBattle_Text_6:
	.string "You did really well, {PLAYER}!$"

NewBarkTown_EventScript_RivalBattle_Text_7:
	.string "That was really fun, and both of our\n"
	.string "Pokémon did their best!$"

NewBarkTown_EventScript_RivalBattle_Text_8:
	.string "You got a task from Elm right?\n"
	.string "I'll leave you to it then.\l"
	.string "See ya!$"

RivalsMailbox_Text_0:
	.string "Crystal's house$"

RivalsMailbox_Text_1:
	.string "Gold's house$"

NewBarkTown_EventScript_ArcherArcadeCall_Text_0:
	.string "???: Greetings, {PLAYER}.\p"
	.string "This is Archer speaking.\p"
	.string "Archer: I've heard of your victory\n"
	.string "in the League and would like to \l"
	.string "offer you an invitation to our \l"
	.string "newly opened Rocket Arcade.\p"
	.string "If you are interested in gambling\n"
	.string "your way to the top, come visit us\l"
	.string "in the Goldenrod Underground.\p"
	.string "I assure you no tricks or traps are\n"
	.string "planned for you this time.$"
