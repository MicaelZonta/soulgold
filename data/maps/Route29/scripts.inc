# 1 "data/maps/Route29/scripts.pory"

# 2 "data/maps/Route29/scripts.pory"
Route29_MapScripts::
# 3 "data/maps/Route29/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
# 4 "data/maps/Route29/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
# 5 "data/maps/Route29/scripts.pory"
	.byte 0
# 6 "data/maps/Route29/scripts.pory"

# 7 "data/maps/Route29/scripts.pory"
Route29_OnTransition: 
# 8 "data/maps/Route29/scripts.pory"
	callnative SetTimeBasedEncounters
# 9 "data/maps/Route29/scripts.pory"
	end
# 10 "data/maps/Route29/scripts.pory"

# 11 "data/maps/Route29/scripts.pory"
Route29_Trigger_Monview::
# 12 "data/maps/Route29/scripts.pory"
	special SpawnCameraObject
# 13 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1 
# 14 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 15 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
# 16 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 17 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
# 18 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 19 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkUp1
# 20 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 21 "data/maps/Route29/scripts.pory"
	message Route29_Text_PressAorB
# 22 "data/maps/Route29/scripts.pory"
	waitbuttonpress
# 23 "data/maps/Route29/scripts.pory"
	closemessage
# 24 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
# 25 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 26 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
# 27 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 28 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
# 29 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 30 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Common_Movement_WalkDown1
# 31 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 32 "data/maps/Route29/scripts.pory"
	special RemoveCameraObject
# 33 "data/maps/Route29/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
# 34 "data/maps/Route29/scripts.pory"
	waitmovement 0
# 35 "data/maps/Route29/scripts.pory"
	end
# 36 "data/maps/Route29/scripts.pory"

# 37 "data/maps/Route29/scripts.pory"
Route29_Text_PressAorB:
# 38 "data/maps/Route29/scripts.pory"
	.string "Press A or B to stop viewing.$"
# 39 "data/maps/Route29/scripts.pory"

# 40 "data/maps/Route29/scripts.pory"
Route29_EventScript_OldMan::
# 41 "data/maps/Route29/scripts.pory"
	lock
# 42 "data/maps/Route29/scripts.pory"
	faceplayer
# 43 "data/maps/Route29/scripts.pory"
	goto_if_set FLAG_ADVENTURE_STARTED, Route29_EventScript_OldMan2
# 44 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_OldMan1, MSGBOX_DEFAULT
# 45 "data/maps/Route29/scripts.pory"
	closemessage
# 46 "data/maps/Route29/scripts.pory"
	release
# 47 "data/maps/Route29/scripts.pory"
	end
# 48 "data/maps/Route29/scripts.pory"

# 49 "data/maps/Route29/scripts.pory"
Route29_EventScript_OldMan2::
# 50 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_OldMan2, MSGBOX_YESNO
# 51 "data/maps/Route29/scripts.pory"
	goto_if_eq VAR_RESULT, YES, Route29_EventScript_OldMan_Tutorial
# 52 "data/maps/Route29/scripts.pory"
	waitmessage
# 53 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_OldManDeclined, MSGBOX_DEFAULT
# 54 "data/maps/Route29/scripts.pory"
	closemessage
# 55 "data/maps/Route29/scripts.pory"
	release
# 56 "data/maps/Route29/scripts.pory"
	end
# 57 "data/maps/Route29/scripts.pory"

# 58 "data/maps/Route29/scripts.pory"
Route29_EventScript_OldMan_Tutorial::
# 59 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_OldManExplanation, MSGBOX_DEFAULT
# 60 "data/maps/Route29/scripts.pory"
	closemessage
# 61 "data/maps/Route29/scripts.pory"
	release
# 62 "data/maps/Route29/scripts.pory"
	end
# 63 "data/maps/Route29/scripts.pory"

# 64 "data/maps/Route29/scripts.pory"
Route29_EventScript_Lass::
# 65 "data/maps/Route29/scripts.pory"
	lock
# 66 "data/maps/Route29/scripts.pory"
	faceplayer
# 67 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Lass, MSGBOX_DEFAULT
# 68 "data/maps/Route29/scripts.pory"
	closemessage
# 69 "data/maps/Route29/scripts.pory"
	release
# 70 "data/maps/Route29/scripts.pory"
	end
# 71 "data/maps/Route29/scripts.pory"

# 72 "data/maps/Route29/scripts.pory"
Route29_EventScript_Youngster::
# 73 "data/maps/Route29/scripts.pory"
	lock
# 74 "data/maps/Route29/scripts.pory"
	faceplayer
# 75 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Youngster, MSGBOX_DEFAULT
# 76 "data/maps/Route29/scripts.pory"
	closemessage
# 77 "data/maps/Route29/scripts.pory"
	release
# 78 "data/maps/Route29/scripts.pory"
	end
# 79 "data/maps/Route29/scripts.pory"

# 80 "data/maps/Route29/scripts.pory"

# 81 "data/maps/Route29/scripts.pory"
Route29_EventScript_Tuscany::
# 82 "data/maps/Route29/scripts.pory"
	lock
# 83 "data/maps/Route29/scripts.pory"
	faceplayer
# 84 "data/maps/Route29/scripts.pory"
	goto_if_set FLAG_GOT_SILK_SCARF, Route29_EventScript_TuscanyCompleted
# 85 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_MeetTuscany, MSGBOX_DEFAULT
# 86 "data/maps/Route29/scripts.pory"
	closemessage
# 87 "data/maps/Route29/scripts.pory"
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
# 88 "data/maps/Route29/scripts.pory"
	switch VAR_RESULT
# 89 "data/maps/Route29/scripts.pory"
	case 0, Route29_EventScript_TuscanyNope
# 90 "data/maps/Route29/scripts.pory"
	case 1, Route29_EventScript_TuscanyNope
# 91 "data/maps/Route29/scripts.pory"
	case 2, Route29_EventScript_TuscanyYes
# 92 "data/maps/Route29/scripts.pory"
	case 3, Route29_EventScript_TuscanyNope
# 93 "data/maps/Route29/scripts.pory"
	case 4, Route29_EventScript_TuscanyNope
# 94 "data/maps/Route29/scripts.pory"
	case 5, Route29_EventScript_TuscanyNope
# 95 "data/maps/Route29/scripts.pory"
	case 6, Route29_EventScript_TuscanyNope
# 96 "data/maps/Route29/scripts.pory"
	case 7 Route29_EventScript_TuscanyCancel
# 97 "data/maps/Route29/scripts.pory"
	case MULTI_B_PRESSED, Route29_EventScript_TuscanyCancel
# 98 "data/maps/Route29/scripts.pory"
	closemessage
# 99 "data/maps/Route29/scripts.pory"
	release
# 100 "data/maps/Route29/scripts.pory"
	end
# 101 "data/maps/Route29/scripts.pory"
Route29_EventScript_TuscanyYes::
# 102 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_TuscanyGivesGift, MSGBOX_DEFAULT
# 103 "data/maps/Route29/scripts.pory"
	giveitem ITEM_SILK_SCARF
# 104 "data/maps/Route29/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 105 "data/maps/Route29/scripts.pory"
	setflag FLAG_GOT_SILK_SCARF
# 106 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_TuscanyGaveGift, MSGBOX_DEFAULT
# 107 "data/maps/Route29/scripts.pory"
	closemessage
# 108 "data/maps/Route29/scripts.pory"
	release
# 109 "data/maps/Route29/scripts.pory"
	end
# 110 "data/maps/Route29/scripts.pory"
Route29_EventScript_TuscanyNope::
# 111 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_TuscanyNope, MSGBOX_DEFAULT
# 112 "data/maps/Route29/scripts.pory"
	closemessage
# 113 "data/maps/Route29/scripts.pory"
	release
# 114 "data/maps/Route29/scripts.pory"
	end
# 115 "data/maps/Route29/scripts.pory"
Route29_EventScript_TuscanyCancel::
# 116 "data/maps/Route29/scripts.pory"
	closemessage
# 117 "data/maps/Route29/scripts.pory"
	release
# 118 "data/maps/Route29/scripts.pory"
	end
# 119 "data/maps/Route29/scripts.pory"
Route29_EventScript_TuscanyCompleted::
# 120 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_TuscanyTuesday, MSGBOX_DEFAULT
# 121 "data/maps/Route29/scripts.pory"
	closemessage
# 122 "data/maps/Route29/scripts.pory"
	release
# 123 "data/maps/Route29/scripts.pory"
	end
# 124 "data/maps/Route29/scripts.pory"

# 125 "data/maps/Route29/scripts.pory"

# 126 "data/maps/Route29/scripts.pory"

# 127 "data/maps/Route29/scripts.pory"
Route29_EventScript_Girl::
# 128 "data/maps/Route29/scripts.pory"
	lock
# 129 "data/maps/Route29/scripts.pory"
	faceplayer
# 130 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Girl, MSGBOX_DEFAULT
# 131 "data/maps/Route29/scripts.pory"
	closemessage
# 132 "data/maps/Route29/scripts.pory"
	release
# 133 "data/maps/Route29/scripts.pory"
	end
# 134 "data/maps/Route29/scripts.pory"

# 135 "data/maps/Route29/scripts.pory"
Route29_EventScript_Boy::
# 136 "data/maps/Route29/scripts.pory"
	lock
# 137 "data/maps/Route29/scripts.pory"
	faceplayer
# 138 "data/maps/Route29/scripts.pory"
	goto_if_set FLAG_NIGHT_POKEMON, Route29_EventScript_Boy2
# 139 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Boy_WaitingForDay, MSGBOX_DEFAULT
# 140 "data/maps/Route29/scripts.pory"
	closemessage
# 141 "data/maps/Route29/scripts.pory"
	release
# 142 "data/maps/Route29/scripts.pory"
	end
# 143 "data/maps/Route29/scripts.pory"

# 144 "data/maps/Route29/scripts.pory"
Route29_EventScript_Boy2::
# 145 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Boy_WaitingForNight, MSGBOX_DEFAULT
# 146 "data/maps/Route29/scripts.pory"
	closemessage
# 147 "data/maps/Route29/scripts.pory"
	release
# 148 "data/maps/Route29/scripts.pory"
	end
# 149 "data/maps/Route29/scripts.pory"

# 150 "data/maps/Route29/scripts.pory"
Route29_EventScript_Sign::
# 151 "data/maps/Route29/scripts.pory"
	lock
# 152 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Sign1, MSGBOX_SIGN
# 153 "data/maps/Route29/scripts.pory"
	closemessage
# 154 "data/maps/Route29/scripts.pory"
	release
# 155 "data/maps/Route29/scripts.pory"
	end
# 156 "data/maps/Route29/scripts.pory"

# 157 "data/maps/Route29/scripts.pory"
Route29_EventScript_Lusamine::
# 158 "data/maps/Route29/scripts.pory"
	trainerbattle_single TRAINER_LUSAMINE, Route29_Text_LusamineSeen, Route29_Text_LusamineBeaten
# 159 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_LusamineAfterBattle, MSGBOX_AUTOCLOSE
# 160 "data/maps/Route29/scripts.pory"
	end
# 161 "data/maps/Route29/scripts.pory"

# 162 "data/maps/Route29/scripts.pory"
Route29_EventScript_Looker::
# 163 "data/maps/Route29/scripts.pory"
	lock
# 164 "data/maps/Route29/scripts.pory"
	faceplayer
# 165 "data/maps/Route29/scripts.pory"
	msgbox Route29_Text_Looker, MSGBOX_DEFAULT
# 166 "data/maps/Route29/scripts.pory"
	closemessage
# 167 "data/maps/Route29/scripts.pory"
	release
# 168 "data/maps/Route29/scripts.pory"
	end
# 169 "data/maps/Route29/scripts.pory"

# 170 "data/maps/Route29/scripts.pory"
Route29_Text_OldMan1:
# 171 "data/maps/Route29/scripts.pory"
	.string "Pokémon hide in the grass.\n"
# 172 "data/maps/Route29/scripts.pory"
	.string "Who knows when they'll pop out…$"
# 173 "data/maps/Route29/scripts.pory"

# 174 "data/maps/Route29/scripts.pory"
Route29_Text_OldMan2:
# 175 "data/maps/Route29/scripts.pory"
	.string "I've seen you a couple times.\n"
# 176 "data/maps/Route29/scripts.pory"
	.string "How many Pokémon have you caught?\p"
# 177 "data/maps/Route29/scripts.pory"
	.string "Would you like me to tell you\n"
# 178 "data/maps/Route29/scripts.pory"
	.string "how to catch Pokémon?$"
# 179 "data/maps/Route29/scripts.pory"

# 180 "data/maps/Route29/scripts.pory"
Route29_Text_OldManExplanation:
# 181 "data/maps/Route29/scripts.pory"
	.string "If you weaken them first,\n"
# 182 "data/maps/Route29/scripts.pory"
	.string "Pokémon are easier to catch.\p"
# 183 "data/maps/Route29/scripts.pory"
	.string "Then, throw a ball at them from\n"
# 184 "data/maps/Route29/scripts.pory"
	.string "your bag! Any ball will do.\p"
# 185 "data/maps/Route29/scripts.pory"
	.string "If you want to learn more,\n"
# 186 "data/maps/Route29/scripts.pory"
	.string "go to the Academy in Violet City!\p"
# 187 "data/maps/Route29/scripts.pory"
	.string "The students there know a lot\n"
# 188 "data/maps/Route29/scripts.pory"
	.string "about Pokémon.$"
# 189 "data/maps/Route29/scripts.pory"

# 190 "data/maps/Route29/scripts.pory"
Route29_Text_OldManDeclined:
# 191 "data/maps/Route29/scripts.pory"
	.string "Oh. Fine, then.\p"
# 192 "data/maps/Route29/scripts.pory"
	.string "Check every route to find\n"
# 193 "data/maps/Route29/scripts.pory"
	.string "different types of Pokémon.\p"
# 194 "data/maps/Route29/scripts.pory"
	.string "Your Pokédex shows where you can\n"
# 195 "data/maps/Route29/scripts.pory"
	.string "find them too!\p"
# 196 "data/maps/Route29/scripts.pory"
	.string "If you want to learn more,\n"
# 197 "data/maps/Route29/scripts.pory"
	.string "go to the Academy in Violet City!\p"
# 198 "data/maps/Route29/scripts.pory"
	.string "The students know a lot about\n"
# 199 "data/maps/Route29/scripts.pory"
	.string "Pokémon.$"
# 200 "data/maps/Route29/scripts.pory"

# 201 "data/maps/Route29/scripts.pory"
Route29_Text_Youngster:
# 202 "data/maps/Route29/scripts.pory"
	.string "Yo. How are your Pokémon?\p"
# 203 "data/maps/Route29/scripts.pory"
	.string "If they're weak and not ready\n"
# 204 "data/maps/Route29/scripts.pory"
	.string "for battle, keep out of the grass.$"
# 205 "data/maps/Route29/scripts.pory"

# 206 "data/maps/Route29/scripts.pory"
Route29_Text_Lass:
# 207 "data/maps/Route29/scripts.pory"
	.string "See those ledges?\n"
# 208 "data/maps/Route29/scripts.pory"
	.string "It's scary to jump off them.\p"
# 209 "data/maps/Route29/scripts.pory"
	.string "But you can go to New Bark\n"
# 210 "data/maps/Route29/scripts.pory"
	.string "without walking through the grass.$"
# 211 "data/maps/Route29/scripts.pory"

# 212 "data/maps/Route29/scripts.pory"
Route29_Text_Girl:
# 213 "data/maps/Route29/scripts.pory"
	.string "I wanted to take a break,\n"
# 214 "data/maps/Route29/scripts.pory"
	.string "so I saved to record my progress.$"
# 215 "data/maps/Route29/scripts.pory"

# 216 "data/maps/Route29/scripts.pory"
Route29_Text_Boy_WaitingForDay:
# 217 "data/maps/Route29/scripts.pory"
	.string "I'm waiting for Pokémon that\n"
# 218 "data/maps/Route29/scripts.pory"
	.string "appear only later in the day.$"
# 219 "data/maps/Route29/scripts.pory"

# 220 "data/maps/Route29/scripts.pory"
Route29_Text_Boy_WaitingForNight:
# 221 "data/maps/Route29/scripts.pory"
	.string "I'm waiting for Pokémon that\n"
# 222 "data/maps/Route29/scripts.pory"
	.string "appear only at night.$"
# 223 "data/maps/Route29/scripts.pory"

# 224 "data/maps/Route29/scripts.pory"
Route29_Text_MeetTuscany:
# 225 "data/maps/Route29/scripts.pory"
	.string "Tuscany: I do believe that this\n"
# 226 "data/maps/Route29/scripts.pory"
	.string "is the first time we've met?\p"
# 227 "data/maps/Route29/scripts.pory"
	.string "I'm Tuscany of the Weekday Family.\p"
# 228 "data/maps/Route29/scripts.pory"
	.string "If you can guess my favorite day,\n"
# 229 "data/maps/Route29/scripts.pory"
	.string "I'll give you a reward.$"
# 230 "data/maps/Route29/scripts.pory"

# 231 "data/maps/Route29/scripts.pory"
Route29_Text_TuscanyNope:
# 232 "data/maps/Route29/scripts.pory"
	.string "Not quite!$"
# 233 "data/maps/Route29/scripts.pory"

# 234 "data/maps/Route29/scripts.pory"
Route29_Text_TuscanyGivesGift:
# 235 "data/maps/Route29/scripts.pory"
	.string "Yes! By way of introduction,\n"
# 236 "data/maps/Route29/scripts.pory"
	.string "please accept this gift, a Silk\l"
# 237 "data/maps/Route29/scripts.pory"
	.string "Scarf.$"
# 238 "data/maps/Route29/scripts.pory"

# 239 "data/maps/Route29/scripts.pory"
Route29_Text_TuscanyGaveGift:
# 240 "data/maps/Route29/scripts.pory"
	.string "Tuscany: Wouldn't you agree\n"
# 241 "data/maps/Route29/scripts.pory"
	.string "that it is most adorable?\p"
# 242 "data/maps/Route29/scripts.pory"
	.string "It strengthens Normal-type\n"
# 243 "data/maps/Route29/scripts.pory"
	.string "moves.\p"
# 244 "data/maps/Route29/scripts.pory"
	.string "I am certain it will be of use.$"
# 245 "data/maps/Route29/scripts.pory"

# 246 "data/maps/Route29/scripts.pory"
Route29_Text_TuscanyTuesday:
# 247 "data/maps/Route29/scripts.pory"
	.string "Tuscany: Have you met Monica,\n"
# 248 "data/maps/Route29/scripts.pory"
	.string "my older sister?\p"
# 249 "data/maps/Route29/scripts.pory"
	.string "Or my younger brother, Wesley?\p"
# 250 "data/maps/Route29/scripts.pory"
	.string "I am the third of seven\n"
# 251 "data/maps/Route29/scripts.pory"
	.string "children.$"
# 252 "data/maps/Route29/scripts.pory"

# 253 "data/maps/Route29/scripts.pory"
Route29_Text_Sign1:
# 254 "data/maps/Route29/scripts.pory"
	.string "Route 29\p"
# 255 "data/maps/Route29/scripts.pory"
	.string "Cherrygrove City - New Bark Town$"
# 256 "data/maps/Route29/scripts.pory"

# 257 "data/maps/Route29/scripts.pory"
Route29_Text_LusamineSeen:
# 258 "data/maps/Route29/scripts.pory"
	.string "Lusamine: …Interesting.\p"
# 259 "data/maps/Route29/scripts.pory"
	.string "This world has so much more\n"
# 260 "data/maps/Route29/scripts.pory"
	.string "to offer than I imagined.\p"
# 261 "data/maps/Route29/scripts.pory"
	.string "Show me what your Pokémon\n"
# 262 "data/maps/Route29/scripts.pory"
	.string "can do.$"
# 263 "data/maps/Route29/scripts.pory"

# 264 "data/maps/Route29/scripts.pory"
Route29_Text_LusamineBeaten:
# 265 "data/maps/Route29/scripts.pory"
	.string "Lusamine: My, how curious.$"
# 266 "data/maps/Route29/scripts.pory"

# 267 "data/maps/Route29/scripts.pory"
Route29_Text_LusamineAfterBattle:
# 268 "data/maps/Route29/scripts.pory"
	.string "Lusamine: …Interesting.$"
# 269 "data/maps/Route29/scripts.pory"

# 270 "data/maps/Route29/scripts.pory"
Route29_Text_Looker:
# 271 "data/maps/Route29/scripts.pory"
	.string "Looker: Hmm? Oh, pay no\n"
# 272 "data/maps/Route29/scripts.pory"
	.string "attention to moi.\p"
# 273 "data/maps/Route29/scripts.pory"
	.string "I am merely… keeping an eye\n"
# 274 "data/maps/Route29/scripts.pory"
	.string "on this curious gathering.$"

Route29ExNightNpc::
# 279 "data/maps/Route29/scripts.pory"
	msgbox Route29ExNightNpc_Text_0, MSGBOX_NPC
	return


Route29ExNightNpc_Text_0:
# 279 "data/maps/Route29/scripts.pory"
	.string "I'm checking my Pokégear for a map\n"
	.string "to see where I am going!$"
