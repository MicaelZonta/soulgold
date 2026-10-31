"""Gera .claude/abundance_isle/fase2/<Mapa>.inc: historia (VAR_ABUNDANCE_ISLE_STATE 0..14), batalhas de
historia, lendarios, maquina, atalhos, Reveal Glass, DNA Splicers, e falas curtas com plaquinha.
Rodar depois: scripts.py (que junta isto ao esqueleto) e make.

Estados: 0 nao chegou | 1 inverno | 2 guardas da cratera vencidos | 3 Ghetsis 1 vencido | 4 maquina desligada
| 5 planos lidos no Frigate | 6 Ghetsis 2 vencido (cume) | 7 Zekrom resolvido + DNA Splicers | 8 Landorus
+ Reveal Glass | 9 Enamorus | 10 despedida | 11 Lenora decifrou (ato 6) | 12 Ghetsis 3 vencido | 13 Reshiram
resolvido | 14 dupla final vencida."""
import os, textwrap
R = '/home/ADMIN/decomps/soulgold_v1'
OUT = os.path.join(R, '.claude/abundance_isle/fase2')
os.makedirs(OUT, exist_ok=True)
S = 'VAR_ABUNDANCE_ISLE_STATE'

def txt(label, *pages, speaker=None):
    """pages: cada pagina e uma lista de linhas (<= ~34 caracteres). speaker no inicio da 1a pagina."""
    out = [f'{label}:']
    qstate = [0]
    for pi, page in enumerate(pages):
        for li, line in enumerate(page):
            pre = ('{SPEAKER NAME_%s}' % speaker) if (speaker and pi == 0 and li == 0) else ''
            end = '$' if (pi == len(pages) - 1 and li == len(page) - 1) else ('\\p' if li == len(page) - 1 else '\\n')
            while '"' in line:
                line = line.replace('"', '“' if qstate[0] == 0 else '”', 1); qstate[0] ^= 1
            out.append(f'\t.string "{pre}{line}{end}"')
    return '\n'.join(out) + '\n'

def talk(label, speaker, *pages):
    """NPC simples: uma fala."""
    return (f'{label}::\n\tmsgbox {label}_Text, MSGBOX_NPC\n\tend\n\n' + txt(label + '_Text', *pages, speaker=speaker) + '\n')

def legend(map_name, label, species, level, localid, hideflag, doneflag, from_state, to_state, intro):
    """Lendario estatico: captura ou vitoria encerram; fugir deixa repetir."""
    return f'''{label}::
	lock
	faceplayer
	msgbox {label}_Text_Intro, MSGBOX_DEFAULT
	closemessage
	bosslegendaryencounter SPECIES_{species}, {level}, {localid}, {hideflag}, 3, SPECIES_NONE, 110
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, {label}_Done
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, {label}_Beaten
	release
	end

{label}_Beaten:
	fadescreenswapbuffers FADE_TO_BLACK
	setflag {hideflag}
	removeobject {localid}
	fadescreenswapbuffers FADE_FROM_BLACK
{label}_Done:
	setflag {doneflag}
	call_if_eq {S}, {from_state}, {label}_Advance
	release
	end

{label}_Advance:
	setvar {S}, {to_state}
	return

''' + txt(f'{label}_Text_Intro', *intro)

def by_state(label, branches, default):
    """branches: [(op, value, sublabel)], default: sublabel (cada sublabel e um talk sem o MSGBOX_NPC)."""
    s = f'{label}::\n\tlock\n\tfaceplayer\n'
    for op, val, sub in branches:
        s += f'\tgoto_if_{op} {S}, {val}, {sub}\n'
    s += f'\tgoto {default}\n\n'
    return s

def say(label, speaker, *pages):
    return (f'{label}::\n\tlock\n\tfaceplayer\n\tmsgbox {label}_Text, MSGBOX_DEFAULT\n\trelease\n\tend\n\n' + txt(label + '_Text', *pages, speaker=speaker) + '\n')

F = {}
# =====================================================================================================  ILHA CENTRAL
F['AbundanceIsle'] = open(os.path.join(OUT, 'AbundanceIsle.inc')).read().split('@ ---- gerado')[0] if os.path.exists(os.path.join(OUT, 'AbundanceIsle.inc')) else ''
F['AbundanceIsle'] = '''@ Marinheiro do cais: volta para Olivine.
AbundanceIsle_EventScript_Sailor::
	lock
	faceplayer
	msgbox AbundanceIsle_Text_SailorOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, AbundanceIsle_EventScript_SailorNo
	msgbox AbundanceIsle_Text_SailorGo, MSGBOX_DEFAULT
	closemessage
	warp MAP_OLIVINE_CITY_PORT_OUTSIDE, 11, 5
	waitstate
	release
	end

AbundanceIsle_EventScript_SailorNo::
	msgbox AbundanceIsle_Text_SailorNo, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_Text_SailorOffer:
	.string "Heading back to Olivine?$"

AbundanceIsle_Text_SailorGo:
	.string "Aye aye! Back to the mainland!$"

AbundanceIsle_Text_SailorNo:
	.string "I'll be right here when you're\\n"
	.string "ready to go.$"

@ ---- gerado (fase2.py)
AbundanceIsle_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AbundanceIsle_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AbundanceIsle_OnFrame
	.byte 0

AbundanceIsle_OnTransition::
	call AbundanceIsle_EventScript_Vis_TEMP_11
	call AbundanceIsle_EventScript_Vis_TEMP_12
	call AbundanceIsle_EventScript_Vis_TEMP_13
	call AbundanceIsle_EventScript_Vis_TEMP_14
	call_if_lt VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_EventScript_Snow
	end

AbundanceIsle_EventScript_Snow::
	setweather WEATHER_SNOW
	return

AbundanceIsle_OnFrame::
	map_script_2 VAR_ABUNDANCE_ISLE_STATE, 0, AbundanceIsle_EventScript_Arrival
	.2byte 0

@ Cena 1: chegada na neve (dispara uma vez: a primeira instrucao muda a var da condicao)
AbundanceIsle_EventScript_Arrival::
	setvar VAR_ABUNDANCE_ISLE_STATE, 1
	lockall
	msgbox AbundanceIsle_Text_Arrival, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

''' + txt('AbundanceIsle_Text_Arrival',
          ['Snow... in harvest season?', 'I\'ve sailed here twenty years and', 'never seen anything like it.'],
          ['Folks say the storms over the', 'mountain haven\'t stopped in weeks.', 'Be careful out there.'], speaker='SAILOR') + '''
@ Guardas da cratera (cena 3)
AbundanceIsle_EventScript_PlasmaGuard1::
AbundanceIsle_EventScript_PlasmaGuard2::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 2, AbundanceIsle_EventScript_GuardGone
	msgbox AbundanceIsle_Text_GuardStop, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_CRATER_GUARD, AbundanceIsle_Text_GuardBeaten
	msgbox AbundanceIsle_Text_GuardFlee, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_12
	removeobject LOCALID_ABUNDANCE_ISLE_GRUNT_1
	removeobject LOCALID_ABUNDANCE_ISLE_GRUNT_2
	setvar VAR_ABUNDANCE_ISLE_STATE, 2
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

AbundanceIsle_EventScript_GuardGone::
	release
	end

''' + txt('AbundanceIsle_Text_GuardStop', ['This crater is off-limits by order', 'of Team Plasma!'], ['Another meddling kid? Fine!', 'I\'ll freeze you out myself!'], speaker='GRUNT') \
    + txt('AbundanceIsle_Text_GuardBeaten', ['Grunt: Brr... You\'re tougher', 'than the cold!']) \
    + txt('AbundanceIsle_Text_GuardFlee', ['Lord Ghetsis won\'t be happy...', 'Retreat! Retreat!'], speaker='GRUNT') + '''
@ N e Hilda junto ao lago (inverno)
AbundanceIsle_EventScript_N::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 2, AbundanceIsle_EventScript_N2
	msgbox AbundanceIsle_Text_N1, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_N2::
	msgbox AbundanceIsle_Text_N2, MSGBOX_DEFAULT
	release
	end

''' + txt('AbundanceIsle_Text_N1', ['The winds aren\'t angry.', 'They\'re in pain.'],
          ['Someone is keeping this winter', 'alive. The cold is coming from the', 'crater to the north.'], speaker='N') \
    + txt('AbundanceIsle_Text_N2', ['The Pokemon of the storm are', 'screaming. Please... stop whoever', 'is doing this.'], speaker='N') \
    + say('AbundanceIsle_EventScript_Hilda', 'HILDA', ['I came with N. When he says the', 'Pokemon are hurting...'], ['...he\'s never wrong. Let\'s find', 'out what\'s freezing this island.']) + '''
@ Guardiao do santuario: lenda e Reveal Glass (cena 13)
AbundanceIsle_EventScript_ShrineKeeper::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 8, AbundanceIsle_EventScript_KeeperGlass
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, AbundanceIsle_EventScript_KeeperCalm
	msgbox AbundanceIsle_Text_KeeperLegend, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_KeeperCalm::
	msgbox AbundanceIsle_Text_KeeperCalm, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_KeeperGlass::
	checkitem ITEM_REVEAL_GLASS
	goto_if_eq VAR_RESULT, TRUE, AbundanceIsle_EventScript_KeeperHasGlass
	msgbox AbundanceIsle_Text_KeeperGiveGlass, MSGBOX_DEFAULT
	checkitemspace ITEM_REVEAL_GLASS
	goto_if_eq VAR_RESULT, FALSE, AbundanceIsle_EventScript_KeeperBagFull
	giveitem ITEM_REVEAL_GLASS
	release
	end

AbundanceIsle_EventScript_KeeperBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_KeeperHasGlass::
	msgbox AbundanceIsle_Text_KeeperHasGlass, MSGBOX_DEFAULT
	release
	end

''' + txt('AbundanceIsle_Text_KeeperLegend',
          ['When wind and thunder quarrel,', 'the land goes hungry.'],
          ['Long ago, the Wind Genie and the', 'Thunder Genie fought over the sky,', 'and our fields turned to dust.'],
          ['Then the Lord of the Fertile Land', 'came down and calmed them both.', 'We have given thanks ever since.'],
          ['But this winter... the earth can\'t', 'hear our prayers.'], speaker='KEEPER') \
    + txt('AbundanceIsle_Text_KeeperCalm', ['The snow has stopped! The genies', 'fell from the sky, exhausted.'],
          ['If both of them stood before the', 'shrine together, perhaps the Lord', 'of the Fertile Land would return.'], speaker='KEEPER') \
    + txt('AbundanceIsle_Text_KeeperGiveGlass', ['The Lord of the Fertile Land came', 'back! The harvest is saved.'],
          ['Take this mirror. It shows the', 'true form of the four Forces of', 'Nature.'], speaker='KEEPER') \
    + txt('AbundanceIsle_Text_KeeperHasGlass', ['The Reveal Glass shows the form', 'they take for those who believe.'], speaker='KEEPER') \
    + legend('AbundanceIsle', 'AbundanceIsle_EventScript_Landorus', 'LANDORUS', 70, 'LOCALID_ABUNDANCE_ISLE_LANDORUS',
             'FLAG_TEMP_13', 'FLAG_ABUNDANCE_LANDORUS_DONE', 7, 8,
             [['The stone fox glows...', 'The ground rumbles, and the Lord', 'of the Fertile Land descends!']]) + '''
@ Despedida no cais (cena 15)
AbundanceIsle_EventScript_NFarewell::
	lock
	faceplayer
	goto_if_eq VAR_ABUNDANCE_ISLE_STATE, 9, AbundanceIsle_EventScript_NBye
	msgbox AbundanceIsle_Text_NWait, MSGBOX_DEFAULT
	release
	end

AbundanceIsle_EventScript_NBye::
	msgbox AbundanceIsle_Text_NBye, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_14
	removeobject LOCALID_ABUNDANCE_ISLE_N_DOCK
	removeobject LOCALID_ABUNDANCE_ISLE_HILDA_DOCK
	setvar VAR_ABUNDANCE_ISLE_STATE, 10
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

''' + txt('AbundanceIsle_Text_NWait', ['Spring isn\'t here yet. Can you', 'hear it? The island is still', 'waiting for someone.'], speaker='N') \
    + txt('AbundanceIsle_Text_NBye', ['The winds sound happy now.'],
          ['Kyurem is waiting in the snow.', 'Its emptiness can be filled...', 'but not by force.'],
          ['Thank you, {PLAYER}. I hope we', 'meet again.'], speaker='N') \
    + say('AbundanceIsle_EventScript_HildaFarewell', 'HILDA', ['N always leaves like this.', 'Don\'t worry, I\'ll keep an eye', 'on him.'])

# =====================================================================================================  CRATERA
F['FrostfallCrater_1F'] = '''FrostfallCrater_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, FrostfallCrater_1F_OnLoad
	.byte 0

FrostfallCrater_1F_OnLoad::
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_1F_EventScript_Melt
	end

FrostfallCrater_1F_EventScript_Melt::
	setmetatile 25, 3, 0x459, FALSE
	setmetatile 26, 3, 0x459, FALSE
	return

FrostfallCrater_1F_EventScript_Lorelei::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_1F_EventScript_LoreleiAfter
	msgbox FrostfallCrater_1F_Text_Lorelei, MSGBOX_DEFAULT
	release
	end

FrostfallCrater_1F_EventScript_LoreleiAfter::
	msgbox FrostfallCrater_1F_Text_LoreleiAfter, MSGBOX_DEFAULT
	release
	end

''' + txt('FrostfallCrater_1F_Text_Lorelei', ['This isn\'t ice.'], ['It\'s something drinking the', 'warmth out of the whole island.', 'It\'s coming from deeper inside.'], speaker='LORELEI') \
    + txt('FrostfallCrater_1F_Text_LoreleiAfter', ['The cold is fading. Whatever you', 'did down there, it worked.'], speaker='LORELEI')

F['FrostfallCrater_Lab'] = '''FrostfallCrater_Lab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FrostfallCrater_Lab_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, FrostfallCrater_Lab_OnLoad
	.byte 0

FrostfallCrater_Lab_OnTransition::
	call FrostfallCrater_Lab_EventScript_Vis_TEMP_11
	call FrostfallCrater_Lab_EventScript_Vis_TEMP_12
	end

FrostfallCrater_Lab_OnLoad::
	call_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_Lab_EventScript_Melt
	end

FrostfallCrater_Lab_EventScript_Melt::
	setmetatile 28, 13, 0x459, FALSE
	setmetatile 29, 13, 0x459, FALSE
	return

@ Cena 5: o plano do Ghetsis
FrostfallCrater_Lab_EventScript_Ghetsis::
	lock
	faceplayer
	msgbox FrostfallCrater_Lab_Text_GhetsisPlan, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GHETSIS_1, FrostfallCrater_Lab_Text_GhetsisBeaten
	msgbox FrostfallCrater_Lab_Text_GhetsisFlee, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_TEMP_11
	removeobject LOCALID_FROSTFALL_CRATER_LAB_GHETSIS
	removeobject LOCALID_FROSTFALL_CRATER_LAB_SCIENTIST_A
	removeobject LOCALID_FROSTFALL_CRATER_LAB_SCIENTIST_B
	call_if_lt VAR_ABUNDANCE_ISLE_STATE, 3, FrostfallCrater_Lab_EventScript_SetBeaten
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

FrostfallCrater_Lab_EventScript_SetBeaten::
	setvar VAR_ABUNDANCE_ISLE_STATE, 3
	return

@ Cena 6: desligar a maquina
FrostfallCrater_Lab_EventScript_Machine::
	lockall
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 4, FrostfallCrater_Lab_EventScript_MachineOff
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 3, FrostfallCrater_Lab_EventScript_MachineGuarded
	msgbox FrostfallCrater_Lab_Text_MachineShutdown, MSGBOX_DEFAULT
	closemessage
	playse SE_M_BLIZZARD
	setflag FLAG_TEMP_12
	setvar VAR_ABUNDANCE_ISLE_STATE, 4
	call FrostfallCrater_Lab_EventScript_Melt
	special DrawWholeMapView
	msgbox FrostfallCrater_Lab_Text_SnowStops, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Lab_EventScript_MachineGuarded::
	msgbox FrostfallCrater_Lab_Text_MachineHum, MSGBOX_DEFAULT
	releaseall
	end

FrostfallCrater_Lab_EventScript_MachineOff::
	msgbox FrostfallCrater_Lab_Text_MachineSilent, MSGBOX_DEFAULT
	releaseall
	end

''' + txt('FrostfallCrater_Lab_Text_GhetsisPlan',
          ['So, a child has wandered into my', 'laboratory.'],
          ['Behold. A fragment of the meteor', 'that carried Kyurem to this world.', 'Its cold is endless.'],
          ['Cold air against a warm sea makes', 'storms without end. The genies go', 'mad, and their lightning gathers.'],
          ['That lightning will wake the Dark', 'Stone. With Zekrom and Kyurem', 'joined, no one will defy me!'], speaker='GHETSIS') \
    + txt('FrostfallCrater_Lab_Text_GhetsisBeaten', ['Ghetsis: Impossible! You...', 'insignificant...!']) \
    + txt('FrostfallCrater_Lab_Text_GhetsisFlee', ['It hardly matters. The storm has', 'done its work.'],
          ['I go to the summit. The Dark', 'Stone will answer to me!'], speaker='GHETSIS') \
    + txt('FrostfallCrater_Lab_Text_MachineShutdown', ['You pulled the main lever.', 'The machine groans and falls', 'silent...']) \
    + txt('FrostfallCrater_Lab_Text_SnowStops', ['Somewhere far above, the snow', 'stops falling.']) \
    + txt('FrostfallCrater_Lab_Text_MachineHum', ['The machine hums with a terrible', 'cold. Ghetsis is in the way.']) \
    + txt('FrostfallCrater_Lab_Text_MachineSilent', ['The machine is silent. The meteor', 'fragment glows faintly.']) \
    + say('FrostfallCrater_Lab_EventScript_N', 'N', ['This stone came from beyond the', 'sky. Kyurem was born of it...', 'or of what remained of a dragon.'],
          ['The genies fell from the storm.', 'One crashed on the northern shore,', 'the other on the thunder ridge.'])

F['FrostfallCrater_B1F'] = talk('FrostfallCrater_B1F_EventScript_Byron', 'BYRON', ['These shards aren\'t from this', 'world. Harder than any steel I\'ve', 'ever mined!'])
F['FrostfallCrater_Core'] = talk('FrostfallCrater_Core_EventScript_Zinnia', 'ZINNIA', ['A star of ice fell here once.', 'The year without harvest.'],
                                 ['Some say Kyurem rode it down.', 'Others say it is the shell of the', 'first dragon. Who knows?'])

# =====================================================================================================  FORCAS DA NATUREZA
F['AbundanceIsle_GaleShore'] = legend('AbundanceIsle_GaleShore', 'AbundanceIsle_GaleShore_EventScript_Tornadus', 'TORNADUS', 70,
    'LOCALID_ABUNDANCE_ISLE_GALE_SHORE_TORNADUS', 'FLAG_TEMP_11', 'FLAG_ABUNDANCE_TORNADUS_DONE', 99, 99,
    [['The Wind Genie lies inside the', 'stone circle, exhausted...', 'It rises with a howl!']]) \
    + talk('AbundanceIsle_GaleShore_EventScript_Winona', 'WINONA', ['The winds here spin around the', 'crater. Something is pulling them', 'that way.'],
           ['When they calm, the Wind Genie', 'will have nowhere left to fly.'])
F['ThunderRidge'] = legend('ThunderRidge', 'ThunderRidge_EventScript_Thundurus', 'THUNDURUS', 70,
    'LOCALID_THUNDER_RIDGE_THUNDURUS', 'FLAG_TEMP_11', 'FLAG_ABUNDANCE_THUNDURUS_DONE', 99, 99,
    [['Sparks crackle over the peak.', 'The Thunder Genie roars!']]) \
    + talk('ThunderRidge_EventScript_PlasmaGuard', 'GRUNT', ['No one enters the tower!', 'Lord Ghetsis\'s orders!']) \
    + talk('ThunderRidge_EventScript_Volkner', 'VOLKNER', ['Lightning strikes this ridge more', 'than anywhere I\'ve ever seen.', 'It\'s almost like it\'s being called.']) \
    + talk('ThunderRidge_EventScript_Elesa', 'ELESA', ['These sparks would make a', 'gorgeous runway... if they weren\'t', 'so angry.']) \
    + talk('ThunderRidge_EventScript_Alder', 'ALDER', ['Tell me, young one. Do you chase', 'the truth, or an ideal?'],
           ['The dragon in that tower will', 'ask you the same thing.'])

# =====================================================================================================  FRIGATE
F['PlasmaFrigate_Cabins'] = '''PlasmaFrigate_Cabins_EventScript_GhetsisDiary::
PlasmaFrigate_Cabins_EventScript_GhetsisPlans::
	lockall
	msgbox PlasmaFrigate_Cabins_Text_Plans, MSGBOX_DEFAULT
	call_if_eq VAR_ABUNDANCE_ISLE_STATE, 4, PlasmaFrigate_Cabins_EventScript_PlansRead
	releaseall
	end

PlasmaFrigate_Cabins_EventScript_PlansRead::
	setvar VAR_ABUNDANCE_ISLE_STATE, 5
	msgbox PlasmaFrigate_Cabins_Text_PlansRead, MSGBOX_DEFAULT
	return

''' + txt('PlasmaFrigate_Cabins_Text_Plans', ['"The black stone sleeps until a', 'storm born of frost calls it."'],
          ['"Thunderspire. The summit."', '"Zekrom + Kyurem = the Black', 'dragon. The DNA Splicers are', 'ready."']) \
    + txt('PlasmaFrigate_Cabins_Text_PlansRead', ['Ghetsis is heading for the summit', 'of the Thunderspire!'])

# =====================================================================================================  CUME
F['Thunderspire_Summit'] = '''Thunderspire_Summit_EventScript_Ghetsis::
Thunderspire_Summit_EventScript_N::
	lock
	faceplayer
	goto_if_lt VAR_ABUNDANCE_ISLE_STATE, 5, Thunderspire_Summit_EventScript_TooEarly
	msgbox Thunderspire_Summit_Text_Climax, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GHETSIS_2, Thunderspire_Summit_Text_GhetsisBeaten
	msgbox Thunderspire_Summit_Text_StoneWakes, MSGBOX_DEFAULT
	closemessage
	playse SE_THUNDER
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_TEMP_11
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_GHETSIS
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_N
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_TORNADUS_SKY
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_THUNDURUS_SKY
	removeobject LOCALID_THUNDERSPIRE_SUMMIT_DARK_STONE
	clearflag FLAG_TEMP_12
	addobject LOCALID_THUNDERSPIRE_SUMMIT_ZEKROM
	addobject LOCALID_THUNDERSPIRE_SUMMIT_N_AFTER
	addobject LOCALID_THUNDERSPIRE_SUMMIT_HILDA_AFTER
	setvar VAR_ABUNDANCE_ISLE_STATE, 6
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox Thunderspire_Summit_Text_ZekromRefuses, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_TooEarly::
	msgbox Thunderspire_Summit_Text_TooEarly, MSGBOX_DEFAULT
	release
	end

''' + txt('Thunderspire_Summit_Text_TooEarly', ['The black stone is cold and', 'silent.']) \
    + txt('Thunderspire_Summit_Text_Climax', ['You again! Stand aside, N. The', 'Dark Stone will obey ME!'],
          ['{SPEAKER NAME_N}No. Zekrom chooses its own hero.', 'It will never choose you.'],
          ['{SPEAKER NAME_GHETSIS}Then I will crush the child who', 'keeps getting in my way!'], speaker='GHETSIS') \
    + txt('Thunderspire_Summit_Text_GhetsisBeaten', ['Ghetsis: No... NO!']) \
    + txt('Thunderspire_Summit_Text_StoneWakes', ['Lightning strikes the altar!', 'The Dark Stone splits open...']) \
    + txt('Thunderspire_Summit_Text_ZekromRefuses', ['Zekrom roared at Ghetsis, and he', 'fled down the tower in terror.'],
          ['{SPEAKER NAME_N}It wants to know your ideals,', '{PLAYER}. Show it who you are.']) \
    + legend('Thunderspire_Summit', 'Thunderspire_Summit_EventScript_Zekrom', 'ZEKROM', 75, 'LOCALID_THUNDERSPIRE_SUMMIT_ZEKROM',
             'FLAG_TEMP_12', 'FLAG_ABUNDANCE_ZEKROM_DONE', 99, 99,
             [['Zekrom\'s eyes burn with', 'lightning. It wants to test you!']]) + '''
@ N entrega os DNA Splicers (cena 12)
Thunderspire_Summit_EventScript_NAfter::
	lock
	faceplayer
	goto_if_unset FLAG_ABUNDANCE_ZEKROM_DONE, Thunderspire_Summit_EventScript_NWaitZekrom
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 7, Thunderspire_Summit_EventScript_NDone
	msgbox Thunderspire_Summit_Text_NSplicers, MSGBOX_DEFAULT
	checkitemspace ITEM_DNA_SPLICERS
	goto_if_eq VAR_RESULT, FALSE, Thunderspire_Summit_EventScript_NBagFull
	giveitem ITEM_DNA_SPLICERS
	setvar VAR_ABUNDANCE_ISLE_STATE, 7
	msgbox Thunderspire_Summit_Text_NAfterSplicers, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_NBagFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_NWaitZekrom::
	msgbox Thunderspire_Summit_Text_NWait, MSGBOX_DEFAULT
	release
	end

Thunderspire_Summit_EventScript_NDone::
	msgbox Thunderspire_Summit_Text_NAfterSplicers, MSGBOX_DEFAULT
	release
	end

''' + txt('Thunderspire_Summit_Text_NWait', ['Zekrom is waiting for you.'], speaker='N') \
    + txt('Thunderspire_Summit_Text_NSplicers', ['Ghetsis dropped these as he ran.', 'The DNA Splicers.'],
          ['They should not be a weapon.', 'Take them. You will know when', 'the time is right.'], speaker='N') \
    + txt('Thunderspire_Summit_Text_NAfterSplicers', ['The island will wake now. Go and', 'see the shrine, {PLAYER}.'], speaker='N') \
    + say('Thunderspire_Summit_EventScript_HildaAfter', 'HILDA', ['A hero of ideals... Zekrom', 'chose well.'])

# =====================================================================================================  PRIMAVERA E ATO 6
F['AbundanceIsle_SpringGrove'] = legend('AbundanceIsle_SpringGrove', 'AbundanceIsle_SpringGrove_EventScript_Enamorus', 'ENAMORUS', 70,
    'LOCALID_ABUNDANCE_ISLE_SPRING_GROVE_ENAMORUS', 'FLAG_TEMP_11', 'FLAG_ABUNDANCE_ENAMORUS_DONE', 8, 9,
    [['A warm breeze fills the garden.', 'The Herald of Spring has come', 'from across the sea!']]) \
    + talk('AbundanceIsle_SpringGrove_EventScript_Ramos', 'RAMOS', ['The founders planted these beds', '"for the one who comes from the sea', 'when winter ends."'],
           ['Funny thing is, nobody remembers', 'who that is anymore.']) \
    + talk('AbundanceIsle_SpringGrove_EventScript_Gardenia', 'GARDENIA', ['This grove is the first place', 'spring touches on the island.'])

F['AbundanceIsle_HarvestFields'] = '''AbundanceIsle_HarvestFields_EventScript_Lenora::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 11, AbundanceIsle_HarvestFields_EventScript_LenoraGo
	goto_if_eq VAR_ABUNDANCE_ISLE_STATE, 10, AbundanceIsle_HarvestFields_EventScript_LenoraDecode
	msgbox AbundanceIsle_HarvestFields_Text_LenoraStele, MSGBOX_DEFAULT
	release
	end

@ Cena 16: o ato 6 comeca
AbundanceIsle_HarvestFields_EventScript_LenoraDecode::
	msgbox AbundanceIsle_HarvestFields_Text_LenoraDecode, MSGBOX_DEFAULT
	setvar VAR_ABUNDANCE_ISLE_STATE, 11
	release
	end

AbundanceIsle_HarvestFields_EventScript_LenoraGo::
	msgbox AbundanceIsle_HarvestFields_Text_LenoraGo, MSGBOX_DEFAULT
	release
	end

''' + txt('AbundanceIsle_HarvestFields_Text_LenoraStele', ['This stele is older than the', 'farms. "...the Wind Genie carried', 'the clouds..."'], ['I need more pieces to read the', 'rest.'], speaker='LENORA') \
    + txt('AbundanceIsle_HarvestFields_Text_LenoraDecode', ['I\'ve got it! The last line reads:', '"The light sleeps where the sun', 'sets on sand."'],
          ['There\'s an island of sand to the', 'south, past the strait. Hilda is', 'already on her way there!'],
          ['The Light Stone... if Team Plasma', 'finds it first, who knows what', 'Ghetsis will do!'], speaker='LENORA') \
    + txt('AbundanceIsle_HarvestFields_Text_LenoraGo', ['South, past the Sunset Strait.', 'Emberdune Isle! Hurry!'], speaker='LENORA')

F['EmberduneIsle'] = talk('EmberduneIsle_EventScript_Hilda', 'HILDA', ['The Light Stone... Reshiram once', 'chose me, you know.'],
                          ['If Ghetsis gets his hands on it,', 'he\'ll have both dragons. We', 'can\'t let that happen.']) \
    + talk('EmberduneIsle_EventScript_Lenora', 'LENORA', ['Those ruins in the cliff are', 'just like the Relic Castle. Watch', 'out for the sand. It swallows!']) \
    + talk('EmberduneIsle_EventScript_Bea', 'BEA', ['Training in this heat sharpens', 'the mind. Want to try?']) \
    + talk('EmberduneIsle_EventScript_Greta', 'GRETA', ['Beat those Plasma diggers first,', 'then come see me!'])

F['NsRoom'] = talk('NsRoom_EventScript_N', 'N', ['I built this room to remember', 'the one I grew up in.'],
                   ['Toys, a train that goes around', 'and around... I used to think the', 'whole world was this small.']) \
    + talk('NsRoom_EventScript_Hilda', 'HILDA', ['He won\'t say it, but he\'s', 'scared. Of Ghetsis. Of the past.'], ['We\'ll face it together this time.'])

F['TruthsandRuins_HallOfTruth'] = '''TruthsandRuins_HallOfTruth_EventScript_Ghetsis::
	lock
	faceplayer
	msgbox TruthsandRuins_HallOfTruth_Text_GhetsisLast, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_GHETSIS_3, TruthsandRuins_HallOfTruth_Text_GhetsisBeaten
	msgbox TruthsandRuins_HallOfTruth_Text_StoneShines, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_TEMP_11
	setflag FLAG_TEMP_12
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_GHETSIS
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_GRUNT_1
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_GRUNT_2
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_HILDA
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_LENORA
	removeobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_LIGHT_STONE
	clearflag FLAG_TEMP_13
	addobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_RESHIRAM
	addobject LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_HILDA_AFTER
	setvar VAR_ABUNDANCE_ISLE_STATE, 12
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox TruthsandRuins_HallOfTruth_Text_ReshiramRefuses, MSGBOX_DEFAULT
	release
	end

''' + txt('TruthsandRuins_HallOfTruth_Text_GhetsisLast', ['The Light Stone is mine! If one', 'dragon will not obey, the other', 'shall!'],
          ['{SPEAKER NAME_HILDA}Truth isn\'t something you can', 'steal, Ghetsis. It finds you.'], speaker='GHETSIS') \
    + txt('TruthsandRuins_HallOfTruth_Text_GhetsisBeaten', ['Ghetsis: This... cannot... be...']) \
    + txt('TruthsandRuins_HallOfTruth_Text_StoneShines', ['The Light Stone blazes with white', 'fire... and shines toward Hilda!']) \
    + txt('TruthsandRuins_HallOfTruth_Text_ReshiramRefuses', ['Reshiram\'s flames drove Ghetsis', 'and his grunts out of the ruins.'],
          ['{SPEAKER NAME_HILDA}It remembers me... but it\'s', 'looking at you, {PLAYER}.', 'Go on. Show it your truth.']) \
    + legend('TruthsandRuins_HallOfTruth', 'TruthsandRuins_HallOfTruth_EventScript_Reshiram', 'RESHIRAM', 75,
             'LOCALID_TRUTHSAND_RUINS_HALL_OF_TRUTH_RESHIRAM', 'FLAG_TEMP_13', 'FLAG_ABUNDANCE_RESHIRAM_DONE', 12, 13,
             [['White flames fill the hall.', 'Reshiram challenges you!']]) \
    + say('TruthsandRuins_HallOfTruth_EventScript_HildaAfter', 'HILDA', ['There\'s a sealed door on an islet', 'in the strait. Bring both dragons.', 'N will meet us there.']) \
    + talk('TruthsandRuins_HallOfTruth_EventScript_LightStone', None, ['A white stone, warm to the touch.', 'Something sleeps inside it.'])

F['ShrineOfTheFirstDragon'] = '''ShrineOfTheFirstDragon_EventScript_N::
ShrineOfTheFirstDragon_EventScript_Hilda::
	lock
	faceplayer
	goto_if_ge VAR_ABUNDANCE_ISLE_STATE, 14, ShrineOfTheFirstDragon_EventScript_NDone
	msgbox ShrineOfTheFirstDragon_Text_Final, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_ABUNDANCE_N_AND_HILDA, ShrineOfTheFirstDragon_Text_FinalBeaten
	setvar VAR_ABUNDANCE_ISLE_STATE, 14
	msgbox ShrineOfTheFirstDragon_Text_FinalAfter, MSGBOX_DEFAULT
	release
	end

ShrineOfTheFirstDragon_EventScript_NDone::
	msgbox ShrineOfTheFirstDragon_Text_FinalAfter, MSGBOX_DEFAULT
	release
	end

''' + txt('ShrineOfTheFirstDragon_Text_Final', ['Once there was one dragon, and', 'two brothers who loved it.', 'When they quarreled, it became three.'],
          ['Truth, ideals... and the emptiness', 'left behind. Kyurem.'],
          ['{SPEAKER NAME_HILDA}Before you go, {PLAYER}... one last', 'battle. N and me, together!'], speaker='N') \
    + txt('ShrineOfTheFirstDragon_Text_FinalBeaten', ['N: Truth and ideals... in one', 'Trainer.']) \
    + txt('ShrineOfTheFirstDragon_Text_FinalAfter', ['With the DNA Splicers, Kyurem', 'can borrow a hero\'s strength.', 'Use them kindly.'],
          ['{SPEAKER NAME_HILDA}Come back anytime. We\'ll be', 'right here, arguing about truth.'], speaker='N')

# murais e altares (lore)
for lbl, pages in (
    ('ShrineOfTheFirstDragon_EventScript_MuralTruth', [['A white dragon breathes fire', 'beside the elder brother.']]),
    ('ShrineOfTheFirstDragon_EventScript_MuralIdeals', [['A black dragon wreathed in', 'lightning beside the younger', 'brother.']]),
    ('ShrineOfTheFirstDragon_EventScript_MuralFirstDragon', [['"Once there was one dragon, and two', 'brothers who loved it."'], ['"When they quarreled, it became', 'three."']]),
    ('ShrineOfTheFirstDragon_EventScript_AltarTruth', [['The Altar of Truth. The stone', 'is warm.']]),
    ('ShrineOfTheFirstDragon_EventScript_AltarIdeals', [['The Altar of Ideals. Static', 'crackles on the stone.']]),
    ('ShrineOfTheFirstDragon_EventScript_AltarVoid', [['The Altar of the Void. It is', 'cold as ice.']]),
    ('TruthsandRuins_HallOfTruth_EventScript_MuralTwinHeroes', [['Twin heroes stand back to back,', 'a dragon of fire and a dragon', 'of lightning above them.']]),
    ('TruthsandRuins_HallOfTruth_EventScript_MuralTruth', [['"Truth is not a thing to be owned.', 'It is a fire that shows what is."']]),
    ('TruthsandRuins_HallOfTruth_EventScript_AltarDoor', [['A white stone rests on the altar.']]),
):
    mp = lbl.split('_EventScript_')[0]
    F[mp] = F.get(mp, '') + f'{lbl}::\n\tmsgbox {lbl}_Text, MSGBOX_SIGN\n\tend\n\n' + txt(lbl + '_Text', *pages) + '\n'

# fase 3: missoes secundarias e eventos de mundo
import importlib.util
_sp = importlib.util.spec_from_file_location('fase3', os.path.join(R, '.claude/abundance_isle/instalar/fase3.py'))
fase3 = importlib.util.module_from_spec(_sp); _sp.loader.exec_module(fase3)
fase3.build(F, txt, talk)

for mp, body in F.items():
    open(os.path.join(OUT, mp + '.inc'), 'w').write(body)
print('fase2:', len(F), 'mapas')
