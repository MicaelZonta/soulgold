@ Pecharunt no fundo do Ruby Path (Mt. Ember), o retrofit sem o Moltres.
@
@ O mestre que o Trio Leal (Okidogi, Munkidori, Fezandipiti) obedecia se
@ escondeu onde ficava o rubi. Os mochis dele deixam a One Island doce e mole
@ demais; ninguem diz o nome dele antes da batalha.
@
@ Tres estados, calculados na hora por Pecharunt_GetState (VAR_RESULT):
@   0 BEFORE  falta capturar algum do Trio Leal
@   1 HUNT    os tres capturados, Pecharunt solto
@   2 AFTER   FLAG_CAUGHT_PECHARUNT
@ Quem usa: o velho da praca e o casal da casa 1 (One Island), quatro
@ banhistas do Ember Spa, a Flannery e os tres de Alola
@ (data/scripts/mt_ember_residents.inc).
@
@ FLAG_HIDE_PECHARUNT e recalculada em TODO ON_TRANSITION do B5F, como a do
@ Volcanion: perder ou fugir nao mexe em nada e a luta pode ser repetida.
@
@ Falas do gpt-6-sol pelo Codex, com a vibe do autor.

Pecharunt_GetState::
	goto_if_set FLAG_CAUGHT_PECHARUNT, Pecharunt_StateAfter
	getcaughtmon SPECIES_OKIDOGI
	goto_if_eq VAR_RESULT, FALSE, Pecharunt_StateBefore
	getcaughtmon SPECIES_MUNKIDORI
	goto_if_eq VAR_RESULT, FALSE, Pecharunt_StateBefore
	getcaughtmon SPECIES_FEZANDIPITI
	goto_if_eq VAR_RESULT, FALSE, Pecharunt_StateBefore
	setvar VAR_RESULT, 1
	return

Pecharunt_StateBefore:
	setvar VAR_RESULT, 0
	return

Pecharunt_StateAfter:
	setvar VAR_RESULT, 2
	return

@ ------------------------------------------------------------ Ruby Path B5F

MtEmber_RubyPath_B5F_OnTransition::
	setflag FLAG_HIDE_PECHARUNT
	call Pecharunt_GetState
	goto_if_ne VAR_RESULT, 1, MtEmber_RubyPath_B5F_EventScript_StayHidden
	clearflag FLAG_HIDE_PECHARUNT
MtEmber_RubyPath_B5F_EventScript_StayHidden:
	return

MtEmber_RubyPath_B5F_EventScript_BrailleMessage::
	lockall
	call Pecharunt_GetState
	goto_if_eq VAR_RESULT, 0, MtEmber_RubyPath_B5F_EventScript_BrailleBefore
	braillemsgbox MtEmber_RubyPath_B5F_Braille_Hunt
	releaseall
	end

MtEmber_RubyPath_B5F_EventScript_BrailleBefore:
	braillemsgbox MtEmber_RubyPath_B5F_Braille_Before
	releaseall
	end

MtEmber_RubyPath_B5F_EventScript_Pecharunt::
	lock
	faceplayer
	msgbox MtEmber_RubyPath_B5F_Text_PecharuntApproach, MSGBOX_DEFAULT
	msgbox MtEmber_RubyPath_B5F_Text_PecharuntCry, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_PECHARUNT, 75, LOCALID_RUBYPATH_PECHARUNT, FLAG_HIDE_PECHARUNT, 3
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, MtEmber_RubyPath_B5F_EventScript_PecharuntCaught
	msgbox MtEmber_RubyPath_B5F_Text_PecharuntStays, MSGBOX_DEFAULT
	release
	end

MtEmber_RubyPath_B5F_EventScript_PecharuntCaught:
	setflag FLAG_CAUGHT_PECHARUNT
	release
	end

@ ---------------------------------------------------- falas por estado (NPCs)

@ One Island, o velho da praca. Antes da trava ele ainda fala do Celio
@ (OneIsland/scripts.inc); estas so entram com o Trio Leal completo.
OneIsland_Text_OldManHunt::
	.string "Someone left sweets on our\n"
	.string "doorstep again.\p"
	.string "My granddaughter slept till noon.\n"
	.string "The mountain smells sweet today.$"

OneIsland_Text_OldManAfter::
	.string "No more sweets on the doorstep.\p"
	.string "My granddaughter's up at dawn.\n"
	.string "The mountain smells normal again.$"

OneIsland_House1_Text_OldManHunt::
	.string "On sunny days, I step outside\n"
	.string "and watch the mountain breathe.\p"
	.string "Today, it smells like candy.$"

OneIsland_House1_Text_OldWomanHunt::
	.string "Let me think... That humming\n"
	.string "is not an eruption, is it?$"

OneIsland_House1_Text_OldManAfter::
	.string "On sunny days, I step outside.\n"
	.string "It looks like itself again.$"

OneIsland_House1_Text_OldWomanAfter::
	.string "Let me think... No. That was\n"
	.string "not an eruption after all.$"

OneIsland_KindleRoad_EmberSpa_Text_OldManHunt::
	.string "Hm...\n"
	.string "Haaaaaaaaaaah...\p"
	.string "This is heavenly. I could soak\n"
	.string "here forever...$"

OneIsland_KindleRoad_EmberSpa_Text_OldManAfter::
	.string "Aaaah! This is heavenly!\n"
	.string "The water warms me to my core.$"

OneIsland_KindleRoad_EmberSpa_Text_ChowderHunt::
	.string "Someone left mochi by the pool.\n"
	.string "I ate three. So peaceful...\p"
	.string "Chowder can wait. I think.$"

OneIsland_KindleRoad_EmberSpa_Text_ChowderAfter::
	.string "Someone left mochi by the pool?\n"
	.string "I ate how many?\p"
	.string "Forget it. I need chowder.$"

OneIsland_KindleRoad_EmberSpa_Text_SkinHunt::
	.string "Have a look at my face.\n"
	.string "Isn't it perfect?\p"
	.string "Everything is perfect... zzz.$"

OneIsland_KindleRoad_EmberSpa_Text_SkinAfter::
	.string "Have a look at my face.\n"
	.string "See how smooth my skin is?\p"
	.string "I dozed off saying that, didn't I?$"

OneIsland_KindleRoad_EmberSpa_Text_HewerHunt::
	.string "I hewed this pool from stone.\n"
	.string "Now I just want to rest...\p"
	.string "That sweet smell makes my arms\n"
	.string "feel light as feathers.$"

OneIsland_KindleRoad_EmberSpa_Text_HewerAfter::
	.string "I hewed this pool from stone.\n"
	.string "I nearly nodded off, too.\p"
	.string "Still, this hammer's no toy.$"

Flannery_Text_PecharuntHunt::
	.string "{SPEAKER NAME_FLANNERY}That sweetness in the fumes? Bad.\n"
	.string "Keep your Pokémon out of it.\p"
	.string "Hot fumes lead into RUBY PATH.\n"
	.string "Go down. Don't breathe deep.$"

Flannery_Text_PecharuntAfter::
	.string "{SPEAKER NAME_FLANNERY}The fumes are clean again.\n"
	.string "Your Pokémon can breathe easy.\p"
	.string "Whatever fed down there,\n"
	.string "you cut it off.$"

MtEmber_RubyPath_B5F_Text_PecharuntApproach:
	.string "A small shape waits in the heat.\p"
	.string "Sweet, wordless music drifts\n"
	.string "from it.\p"
	.string "Dark chains scrape slowly\n"
	.string "across the stone.\p"
	.string "A peach-scented mochi is held\n"
	.string "out toward you.\p"
	.string "{PLAYER} walks forward\n"
	.string "without taking it.$"

MtEmber_RubyPath_B5F_Text_PecharuntCry:
	.string "{SPEAKER NAME_PECHARUNT}Peeeh-chah...!$"

@ So aparece quando o jogador vence sem capturar: fugir ou perder de um chefe
@ conta como derrota e manda para o Centro antes de o script continuar.
MtEmber_RubyPath_B5F_Text_PecharuntStays:
	.string "It staggers, then laughs softly.\p"
	.string "The chains clink. It stays\n"
	.string "where the heat is deepest.$"

MtEmber_RubyPath_B5F_Braille_Before:
	brailleformat 3, 0, 25, 19, 6, 3
	.braille "MOUNTAIN\n"
	.braille "BREATHES.\n"
	.braille "SWEET SCENT.\n"
	.braille "TURN.$"

MtEmber_RubyPath_B5F_Braille_Hunt:
	brailleformat 3, 0, 25, 19, 6, 3
	.braille "THREE CHAINS\n"
	.braille "REST.\n"
	.braille "SWEET HEART\n"
	.braille "WAKES.$"
