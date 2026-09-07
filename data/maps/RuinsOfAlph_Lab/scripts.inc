# 1 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 2 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_MapScripts::
# 3 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
# 4 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.byte 0
# 5 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 6 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_OnTransition:
# 7 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
# 8 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 9 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 10 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_Scientist1::
# 11 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	lock
# 12 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	faceplayer
# 13 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_Scientist1, MSGBOX_DEFAULT
# 14 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 15 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 16 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_Scientist2::
# 17 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	lock
# 18 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	faceplayer
# 19 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_Scientist2, MSGBOX_DEFAULT
# 20 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 21 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 22 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_Fossils::
# 23 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	lock
# 24 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_Fossils, MSGBOX_DEFAULT
# 25 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	closemessage
# 26 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 27 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 28 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 29 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_Scientist1:
# 30 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "The Ruins are about 1500 years old.\p"
# 31 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "But it's not known why they were\n"
# 32 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "built--or by whom.$"
# 33 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 34 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_Scientist2:
# 35 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "There are odd patterns drawn on\n"
# 36 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "on the walls of the Ruins.\p"
# 37 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "They must be the keys for\n"
# 38 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "unraveling the Ruins' mystery.$"
# 39 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 40 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_Fossils:
# 41 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Fossils found within the Ruins.\n"
# 42 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Maybe there are more somewhere...$"
# 43 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 44 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 45 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FossilScientist::
# 46 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	lock
# 47 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	faceplayer
# 48 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RuinsOfAlph_Lab_EventScript_FossilMonReady
# 49 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RuinsOfAlph_Lab_EventScript_StillRegenerating
# 50 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
# 51 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
# 52 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil
# 53 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ChooseFossil
# 54 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 55 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveRootFossil::
# 56 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_ROOT_FOSSIL
# 57 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 58 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_ROOT_FOSSIL
# 59 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_LileepReady
# 60 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 61 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveClawFossil::
# 62 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_CLAW_FOSSIL
# 63 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 64 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_CLAW_FOSSIL
# 65 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_AnorithReady
# 66 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 67 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveHelixFossil::
# 68 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_HELIX_FOSSIL
# 69 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 70 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_HELIX_FOSSIL
# 71 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_OmanyteReady
# 72 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 73 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveDomeFossil::
# 74 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_DOME_FOSSIL
# 75 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 76 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_DOME_FOSSIL
# 77 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_KabutoReady
# 78 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 79 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveOldAmber::
# 80 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_OLD_AMBER
# 81 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 82 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_OLD_AMBER
# 83 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_AeroReady
# 84 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 85 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GivePlumeFossil::
# 86 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_PLUME_FOSSIL
# 87 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 88 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_PLUME_FOSSIL
# 89 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ArchenReady
# 90 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 91 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveJawFossil::
# 92 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_JAW_FOSSIL
# 93 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 94 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_JAW_FOSSIL
# 95 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TyruntReady
# 96 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 97 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveSailFossil::
# 98 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_SAIL_FOSSIL
# 99 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 100 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_SAIL_FOSSIL
# 101 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_AmauraReady
# 102 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 103 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveCoverFossil::
# 104 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferitemname STR_VAR_1, ITEM_COVER_FOSSIL
# 105 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
# 106 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	removeitem ITEM_COVER_FOSSIL
# 107 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TirtougaReady
# 108 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 109 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_DeclineGiveFossil::
# 110 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo, MSGBOX_DEFAULT
# 111 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 112 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 113 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 114 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2::
# 115 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_OhIsThatSo2, MSGBOX_DEFAULT
# 116 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 117 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 118 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 119 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_StillRegenerating::
# 120 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
# 121 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 122 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 123 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 124 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FossilMonReady::
# 125 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 1, RuinsOfAlph_Lab_EventScript_LileepReady
# 126 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 2, RuinsOfAlph_Lab_EventScript_AnorithReady
# 127 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 3, RuinsOfAlph_Lab_EventScript_OmanyteReady
# 128 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 4, RuinsOfAlph_Lab_EventScript_KabutoReady
# 129 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 5, RuinsOfAlph_Lab_EventScript_AeroReady
# 130 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 6, RuinsOfAlph_Lab_EventScript_ArchenReady
# 131 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 7, RuinsOfAlph_Lab_EventScript_TyruntReady
# 132 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 8, RuinsOfAlph_Lab_EventScript_AmauraReady
# 133 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, 9, RuinsOfAlph_Lab_EventScript_TirtougaReady
# 134 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 135 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 136 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_LileepReady::
# 137 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
# 138 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
# 139 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ReceiveLileep
# 140 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 141 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 142 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_AnorithReady::
# 143 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
# 144 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
# 145 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ReceiveAnorith
# 146 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 147 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 148 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_OmanyteReady::
# 149 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
# 150 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
# 151 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ReceiveOmanyte
# 152 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 153 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 154 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_KabutoReady::
# 155 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
# 156 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
# 157 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ReceiveKabuto
# 158 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 159 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 160 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_AeroReady::
# 161 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
# 162 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
# 163 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ReceiveAero
# 164 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 165 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 166 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ArchenReady::
# 167 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ARCHEN
# 168 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady
# 169 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 170 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TyruntReady::
# 171 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYRUNT
# 172 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady
# 173 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 174 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_AmauraReady::
# 175 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_AMAURA
# 176 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady
# 177 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 178 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TirtougaReady::
# 179 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TIRTOUGA
# 180 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_NewFossilReady
# 181 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 182 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_NewFossilReady::
# 183 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, VAR_TEMP_TRANSFERRED_SPECIES
# 184 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
# 185 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMon
# 186 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 187 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 188 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveLileep::
# 189 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LILEEP
# 190 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon SPECIES_LILEEP, 20
# 191 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveLileepParty
# 192 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveLileepPC
# 193 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 194 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 195 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 196 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveLileepParty::
# 197 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
# 198 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 199 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
# 200 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 201 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 202 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
# 203 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 204 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 205 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveLileepPC::
# 206 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare
# 207 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 208 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferLileepToPC
# 209 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 210 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TransferLileepToPC
# 211 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 212 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	
# 213 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TransferLileepToPC::
# 214 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 215 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingLileep
# 216 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 217 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 218 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceivedLileepFanfare::
# 219 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
# 220 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 221 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
# 222 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitmessage
# 223 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitfanfare
# 224 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_LILEEP
# 225 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 226 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 227 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FinishReceivingLileep::
# 228 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 229 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 230 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 231 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 232 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 233 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveAnorith::
# 234 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
# 235 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon SPECIES_ANORITH, 20
# 236 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty
# 237 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC
# 238 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 239 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 240 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 241 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveAnorithParty::
# 242 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
# 243 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 244 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
# 245 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 246 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 247 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
# 248 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 249 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 250 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveAnorithPC::
# 251 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare
# 252 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 253 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
# 254 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 255 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TransferAnorithToPC
# 256 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 257 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 258 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TransferAnorithToPC::
# 259 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 260 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith
# 261 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 262 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 263 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceivedAnorithFanfare::
# 264 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
# 265 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 266 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
# 267 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitmessage
# 268 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitfanfare
# 269 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_ANORITH
# 270 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 271 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 272 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FinishReceivingAnorith::
# 273 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 274 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 275 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 276 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 277 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 278 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveOmanyte::
# 279 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_OMANYTE
# 280 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon SPECIES_OMANYTE, 20
# 281 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty
# 282 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC
# 283 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 284 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 285 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 286 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveOmanyteParty::
# 287 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
# 288 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 289 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
# 290 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 291 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 292 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
# 293 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 294 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 295 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveOmanytePC::
# 296 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare
# 297 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 298 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
# 299 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 300 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC
# 301 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 302 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	
# 303 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TransferOmanyteToPC::
# 304 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 305 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte
# 306 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 307 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 308 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceivedOmanyteFanfare::
# 309 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
# 310 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 311 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
# 312 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitmessage
# 313 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitfanfare
# 314 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
# 315 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 316 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 317 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FinishReceivingOmanyte::
# 318 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 319 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 320 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 321 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 322 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 323 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveKabuto::
# 324 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_KABUTO
# 325 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call_if_unset FLAG_BADGE04_GET, RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto
# 326 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call_if_set FLAG_BADGE04_GET, RuinsOfAlph_Lab_EventScript_GiveLateKabuto
# 327 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty
# 328 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC
# 329 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 330 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 331 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 332 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveEarlyKabuto::
# 333 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon SPECIES_KABUTO, 5
# 334 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 335 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 336 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_GiveLateKabuto::
# 337 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon SPECIES_KABUTO, 20
# 338 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 339 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 340 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveKabutoParty::
# 341 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
# 342 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 343 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
# 344 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 345 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 346 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
# 347 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 348 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 349 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 350 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveKabutoPC::
# 351 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare
# 352 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 353 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
# 354 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 355 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TransferKabutoToPC
# 356 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 357 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	
# 358 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TransferKabutoToPC::
# 359 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 360 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto
# 361 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 362 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 363 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceivedKabutoFanfare::
# 364 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
# 365 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 366 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
# 367 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitmessage
# 368 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitfanfare
# 369 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_KABUTO
# 370 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 371 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 372 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FinishReceivingKabuto::
# 373 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 374 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 375 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 376 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 377 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 378 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveAero::
# 379 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_TEMP_1, SPECIES_AERODACTYL
# 380 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon SPECIES_AERODACTYL, 20
# 381 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveAeroParty
# 382 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveAeroPC
# 383 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 384 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 385 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 386 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveAeroParty::
# 387 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
# 388 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 389 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingAero
# 390 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 391 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 392 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
# 393 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 394 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 395 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveAeroPC::
# 396 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare
# 397 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 398 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferAeroToPC
# 399 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 400 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TransferAeroToPC
# 401 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 402 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	
# 403 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TransferAeroToPC::
# 404 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 405 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingAero
# 406 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 407 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 408 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceivedAeroFanfare::
# 409 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
# 410 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 411 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
# 412 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitmessage
# 413 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitfanfare
# 414 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
# 415 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 416 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 417 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FinishReceivingAero::
# 418 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 419 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 420 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 421 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 422 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 423 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMon::
# 424 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	givemon VAR_TEMP_TRANSFERRED_SPECIES, 20
# 425 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonParty
# 426 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonPC
# 427 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 428 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 429 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 430 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonParty::
# 431 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedNewFossilMonFanfare
# 432 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 433 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon
# 434 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 435 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 436 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon
# 437 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 438 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 439 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceiveNewFossilMonPC::
# 440 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call RuinsOfAlph_Lab_EventScript_ReceivedNewFossilMonFanfare
# 441 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 442 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RuinsOfAlph_Lab_EventScript_TransferNewFossilMonToPC
# 443 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 444 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_TransferNewFossilMonToPC
# 445 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 446 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 447 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_TransferNewFossilMonToPC::
# 448 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 449 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon
# 450 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 451 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 452 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ReceivedNewFossilMonFanfare::
# 453 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_2, VAR_TEMP_TRANSFERRED_SPECIES
# 454 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 455 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	message RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher
# 456 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitmessage
# 457 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	waitfanfare
# 458 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_TEMP_TRANSFERRED_SPECIES
# 459 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	return
# 460 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 461 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_FinishReceivingNewFossilMon::
# 462 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
# 463 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
# 464 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 465 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 466 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 467 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 468 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ChooseFossil::
# 469 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_PickFossilFromBag, MSGBOX_DEFAULT
# 470 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	chooseitem POCKET_ITEMS
# 471 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	switch VAR_ITEM_ID
# 472 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_NONE, RuinsOfAlph_Lab_EventScript_CancelFossilSelect
# 473 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_DOME_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveDomeFossil
# 474 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_ROOT_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveRootFossil
# 475 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_PLUME_FOSSIL, RuinsOfAlph_Lab_EventScript_GivePlumeFossil
# 476 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_JAW_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveJawFossil
# 477 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_SAIL_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveSailFossil
# 478 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_OLD_AMBER, RuinsOfAlph_Lab_EventScript_GiveOldAmber
# 479 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	case ITEM_COVER_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveCoverFossil
# 480 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_ThatsNotAFossil, MSGBOX_DEFAULT
# 481 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto RuinsOfAlph_Lab_EventScript_ChooseFossil
# 482 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 483 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 484 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ChooseClawFossil::
# 485 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	checkitem ITEM_CLAW_FOSSIL
# 486 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveClawFossil
# 487 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
# 488 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 489 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 490 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ChooseRootFossil::
# 491 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	checkitem ITEM_ROOT_FOSSIL
# 492 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveRootFossil
# 493 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
# 494 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 495 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 496 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ChooseHelixFossil::
# 497 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	checkitem ITEM_HELIX_FOSSIL
# 498 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveHelixFossil
# 499 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
# 500 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 501 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 502 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ChooseDomeFossil::
# 503 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	checkitem ITEM_DOME_FOSSIL
# 504 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveDomeFossil
# 505 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
# 506 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 507 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 508 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_ChooseOldAmber::
# 509 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	checkitem ITEM_OLD_AMBER
# 510 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RuinsOfAlph_Lab_EventScript_GiveOldAmber
# 511 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, RuinsOfAlph_Lab_EventScript_DeclineGiveFossil2
# 512 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 513 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 514 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_CancelFossilSelect::
# 515 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 516 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 517 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 518 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_EventScript_WorkOnNext::
# 519 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	msgbox RuinsOfAlph_Lab_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
# 520 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	release
# 521 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	end
# 522 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 523 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_DeviceForTalkingToPokemon:
# 524 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "We're developing a device for talking\n"
# 525 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "with Pokémon.\p"
# 526 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "But we haven't had much success…$"
# 527 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 528 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_DevelopingNewBalls:
# 529 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "I'm developing new kinds of\n"
# 530 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Poké Balls…\p"
# 531 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "But I haven't made much headway…$"
# 532 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 533 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_WeFinallyMadeNewBalls:
# 534 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "We finally made new kinds of\n"
# 535 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Poké Balls!\p"
# 536 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "The Repeat Ball makes it easier to\n"
# 537 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "catch Pokémon you've caught before.\p"
# 538 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "The Timer Ball gets better at catching\n"
# 539 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Pokémon the longer a battle runs.\p"
# 540 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Both are proudly developed by\n"
# 541 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "the Devon Corporation.\p"
# 542 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Please give them a try!$"
# 543 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 544 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_IMadePokenav:
# 545 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "I made the Pokégear!\p"
# 546 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "As an engineer, I feel blessed to have\n"
# 547 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "made something so great!$"
# 548 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 549 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_WowThatsAPokenav:
# 550 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Oh, wow!\n"
# 551 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "That's a Pokégear!\p"
# 552 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "It came about as a result of our\n"
# 553 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "President's desire to learn about\l"
# 554 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "the feelings of Pokémon.\p"
# 555 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Would you like me to describe its\n"
# 556 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "features in detail?\p"
# 557 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "No, no. I think you'll find out just by\n"
# 558 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "trying the Pokégear out.$"
# 559 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 560 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_DeviceToVisualizePokemonDreams:
# 561 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "I'm trying to develop a device that\n"
# 562 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "visually reproduces the dreams of\l"
# 563 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Pokémon…\p"
# 564 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "But it's not going well.$"
# 565 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 566 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_DevelopDeviceToResurrectFossils:
# 567 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "I've been trying to develop a device\n"
# 568 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "that resurrects Pokémon from fossils…\p"
# 569 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "And, it's working!$"
# 570 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 571 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_WantToBringFossilBackToLife:
# 572 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Would you like to bring that Pokémon\n"
# 573 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "back to life?\p"
# 574 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "I can with my newly developed\n"
# 575 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Fossil Regenerator.$"
# 576 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 577 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_OhIsThatSo:
# 578 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Oh, is that so?\p"
# 579 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "My technological expertise\n"
# 580 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "is outstanding, I tell you.$"
# 581 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 582 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_OhIsThatSo2:
# 583 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Oh, you don't have this fossil.\n"
# 584 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Come back if you manage to find it.$"
# 585 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 586 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_TwoFossilsPickOne:
# 587 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Oh, now that's a surprise!\n"
# 588 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "You have more than one fossil?\p"
# 589 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Unfortunately, my machine can only\n"
# 590 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "regenerate one Pokémon at a time.\p"
# 591 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Which fossil would you like to\n"
# 592 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "regenerate?$"
# 593 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 594 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_PickFossilFromBag:
# 595 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Please choose the fossil you'd like\n"
# 596 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "to regenerate.$"
# 597 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 598 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_ThatsNotAFossil:
# 599 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "That's not a fossil!$"
# 600 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 601 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_HandedFossilToResearcher:
# 602 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Excellent!\n"
# 603 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Let's do this right away.\p"
# 604 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
# 605 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "the Ruins Researcher.$"
# 606 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 607 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_FossilRegeneratorTakesTime:
# 608 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "The Fossil Regenerator, which I made,\n"
# 609 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "is incredible.\p"
# 610 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "But it has one drawback--it takes\n"
# 611 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "a long time to work.\p"
# 612 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "So, uh… How about you go for a stroll\n"
# 613 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "and look around for a while?$"
# 614 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 615 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_FossilizedMonBroughtBackToLife:
# 616 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Thanks for waiting!\p"
# 617 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Your fossilized Pokémon has been\n"
# 618 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "brought back to life!\p"
# 619 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "The fossil was an ancient Pokémon.\n"
# 620 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "{STR_VAR_2}, it was!$"
# 621 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 622 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_ReceivedMonFromResearcher:
# 623 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "{PLAYER} received {STR_VAR_2} from\n"
# 624 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "the Researcher.$"
# 625 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 626 "data/maps/RuinsOfAlph_Lab/scripts.pory"
@ Unused
# 627 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_TooManyPokemon:
# 628 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Uh-oh, you've got too many Pokémon.\n"
# 629 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "You have no room for this one.$"
# 630 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 631 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_DevelopNewPokenavFeature:
# 632 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "I'm trying to develop a new feature\n"
# 633 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "for the Pokégear...\p"
# 634 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "But it's not going well.$"
# 635 "data/maps/RuinsOfAlph_Lab/scripts.pory"

# 636 "data/maps/RuinsOfAlph_Lab/scripts.pory"
RuinsOfAlph_Lab_Text_WhatToWorkOnNext:
# 637 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Well, now what shall I work on\n"
# 638 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "developing next?\p"
# 639 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "Our company allows us to make our\n"
# 640 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "inspirations into reality.\p"
# 641 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "One couldn't ask for a better\n"
# 642 "data/maps/RuinsOfAlph_Lab/scripts.pory"
	.string "environment as an engineer.$"
