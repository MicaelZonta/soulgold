@ Match Call GSC (telefone): fala de cada treinador que da o numero.
@ Texto do pokehns 2.0.6 (data/text/match_call_hns.inc), fiel ao Crystal,
@ com o decap do SoulGold. A plaquinha com o nome de quem liga NAO vem do
@ texto: MatchCall_PrintIntro poe gSpeakerName pelo nome do treinador.
@ A tabela que escolhe a fala e sPhoneTrainers, em src/match_call.c.

@ Joey - Youngster, Route 30
MatchCall_Joey_General1::
	.string "Yo, {PLAYER}!\n"
	.string "How're you doing?\p"
	.string "How are your Pokémon doing?\p"
	.string "My {STR_VAR_3}'s raring to go,\n"
	.string "just like always.\p"
	.string "It's the only one I have.\n"
	.string "I'm going to become a great\l"
	.string "trainer with it!$"

MatchCall_Joey_General2::
	.string "Yo, {PLAYER}!\n"
	.string "Got a minute?\p"
	.string "My {STR_VAR_3}'s looking\n"
	.string "sharper than before!\p"
	.string "I doubt there's a Pokémon\n"
	.string "as cool as this guy in\l"
	.string "your party!$"

MatchCall_Joey_General3::
	.string "Yo, {PLAYER}!\n"
	.string "How're you doing?\p"
	.string "I'm checking out\n"
	.string "{STR_VAR_3}'s moves and\l"
	.string "devising some strategies.\p"
	.string "When I come up with a good\n"
	.string "one, let's battle!$"

MatchCall_Joey_Battle::
	.string "Yo, {PLAYER}!\p"
	.string "Let's get together and\n"
	.string "battle!\p"
	.string "I promise things will be\n"
	.string "different!$"

@ Wade - Bug Catcher, Route 31
MatchCall_Wade_General1::
	.string "{PLAYER}, howdy!\p"
	.string "How are your Pokémon doing?\p"
	.string "My Pokémon have too much\n"
	.string "energy to burn.\p"
	.string "It gets to be a problem.\p"
	.string "Of all my Pokémon,\n"
	.string "{STR_VAR_3} is the hardest\l"
	.string "to handle.\p"
	.string "Working with it is\n"
	.string "exhausting.$"

MatchCall_Wade_General2::
	.string "{PLAYER}, howdy!\n"
	.string "Isn't it nice out?\p"
	.string "Are your Pokémon growing?\p"
	.string "My Pokémon are growing a\n"
	.string "bit too quickly for me.\l"
	.string "It's overwhelming!\p"
	.string "{STR_VAR_3}'s growing\n"
	.string "especially quickly.\p"
	.string "I think it'll get tough.$"

MatchCall_Wade_General3::
	.string "{PLAYER}, howdy!\p"
	.string "Oh yeah, we KO'd a wild\n"
	.string "{STR_VAR_3} with one hit\l"
	.string "a while back.\p"
	.string "It went down so easily,\n"
	.string "I felt a little sorry for\l"
	.string "the poor thing.$"

MatchCall_Wade_FoundItem::
	.string "{PLAYER}, howdy!\p"
	.string "I found all kinds of\n"
	.string "berries.\p"
	.string "If you want, I'll share\n"
	.string "some with you.\p"
	.string "I'll be waiting on\n"
	.string "Route 31.$"

MatchCall_Wade_Battle::
	.string "{PLAYER}, howdy!\p"
	.string "Do you feel like a Pokémon\n"
	.string "battle?\p"
	.string "It won't be like last\n"
	.string "time!$"

@ Ralph - Fisher, Route 32
MatchCall_Ralph_General1::
	.string "Hey, {PLAYER}!\n"
	.string "How's the fishing?\p"
	.string "Are you taking good care of\n"
	.string "your Pokémon?\p"
	.string "You have to be good to\n"
	.string "your partners!$"

MatchCall_Ralph_General2::
	.string "Hey, {PLAYER}!\p"
	.string "I've been spending more\n"
	.string "time with my {STR_VAR_3}\l"
	.string "than I have with my kids.\p"
	.string "That's a bit sad,\n"
	.string "actually.$"

MatchCall_Ralph_General3::
	.string "Hey, {PLAYER}!\n"
	.string "Listen to this!\p"
	.string "I just beat a wild\n"
	.string "{STR_VAR_3}.\p"
	.string "I told my kid, but he\n"
	.string "scoffed that he could do\l"
	.string "the same thing easily.\p"
	.string "Boy, has he gotten\n"
	.string "cocky…$"

MatchCall_Ralph_Battle::
	.string "Hey, {PLAYER}!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Liz - Picnicker, Route 32
MatchCall_Liz_General1::
	.string "Hi, {PLAYER}!\n"
	.string "I had some time, so I\l"
	.string "called you.\p"
	.string "So anyway, how are your\n"
	.string "Pokémon?\p"
	.string "Me, I take my {STR_VAR_3}\n"
	.string "to the Pokémon Center in\l"
	.string "Violet every day,\p"
	.string "so it's doing just\n"
	.string "fantastic!\p"
	.string "I'm friends with the\n"
	.string "receptionist!$"

MatchCall_Liz_General2::
	.string "Hi, {PLAYER}!\n"
	.string "You have to hear this.\p"
	.string "My {STR_VAR_3} is so\n"
	.string "adorable!\p"
	.string "It always wants to\n"
	.string "nuzzle me!$"

MatchCall_Liz_General3::
	.string "Hi, {PLAYER}!\n"
	.string "Listen, listen!\p"
	.string "Don't you think Falkner of\n"
	.string "Violet Gym is cool and\l"
	.string "handsome?\p"
	.string "But they say his dad, who's\n"
	.string "out training on the road,\l"
	.string "is even more cool and\l"
	.string "handsome than Falkner.\p"
	.string "I wish I could meet him!$"

MatchCall_Liz_Battle::
	.string "Hi, {PLAYER}!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Anthony - Hiker, Route 33
MatchCall_Anthony_General1::
	.string "Hey there, {PLAYER}!\p"
	.string "Are your Pokémon as feisty\n"
	.string "as ever?\p"
	.string "My {STR_VAR_3} and me--we\n"
	.string "have energy to burn.\p"
	.string "We hike up mountains every\n"
	.string "day to work out all our\l"
	.string "energy.$"

MatchCall_Anthony_General2::
	.string "Hey there, {PLAYER}!\p"
	.string "The other day, I was\n"
	.string "watching my {STR_VAR_3}\l"
	.string "eat some berries.\p"
	.string "It looked like it was\n"
	.string "enjoying its meal, so I\l"
	.string "decided to try some.\p"
	.string "I'm not sure if people\n"
	.string "should eat that stuff, but\l"
	.string "it was delicious!$"

MatchCall_Anthony_General3::
	.string "Hey there, {PLAYER}!\p"
	.string "Lately, I've been running\n"
	.string "across wild {STR_VAR_3}\l"
	.string "quite often.\p"
	.string "They're easily taken\n"
	.string "care of.$"

MatchCall_Anthony_Battle::
	.string "Hey there, {PLAYER}!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Todd - Camper, Route 34
MatchCall_Todd_General1::
	.string "Hey, {PLAYER}!\n"
	.string "What's up?\p"
	.string "How do you raise your\n"
	.string "Pokémon?\p"
	.string "I do all sorts of things,\n"
	.string "like leaving them in\l"
	.string "Day-Care and\p"
	.string "toughening them up with\n"
	.string "items.$"

MatchCall_Todd_General2::
	.string "Hey, {PLAYER}!\n"
	.string "What's up?\p"
	.string "My {STR_VAR_3} is looking\n"
	.string "more and more like me.\p"
	.string "It's getting cuter!$"

MatchCall_Todd_General3::
	.string "Hey, {PLAYER}!\n"
	.string "What's up?\p"
	.string "And, you know?\p"
	.string "Now we can KO {STR_VAR_3}\n"
	.string "easily.\p"
	.string "I should challenge the\n"
	.string "Goldenrod Gym.$"

MatchCall_Todd_Battle::
	.string "Hey, {PLAYER}!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Gina - Picnicker, Route 34
MatchCall_Gina_General1::
	.string "Hi, {PLAYER}!\n"
	.string "How are you?\p"
	.string "Are your Pokémon still\n"
	.string "tough?\p"
	.string "I train every day\n"
	.string "with {STR_VAR_3}.$"

MatchCall_Gina_General2::
	.string "Hi, {PLAYER}!\n"
	.string "How are you?\p"
	.string "My {STR_VAR_3} and I are\n"
	.string "getting more in sync with\l"
	.string "each other.$"

MatchCall_Gina_General3::
	.string "Hi, {PLAYER}!\n"
	.string "How are you?\p"
	.string "We battled a wild\n"
	.string "{STR_VAR_3} and managed\l"
	.string "to drop it in a close\l"
	.string "match.\p"
	.string "We're getting into the\n"
	.string "groove!$"

MatchCall_Gina_Battle::
	.string "Hi, {PLAYER}!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Irwin - Juggler, Route 35
MatchCall_Irwin_General1::
	.string "Uh, hello, {PLAYER}?\n"
	.string "It's your pal, Irwin!\p"
	.string "I saw the most amazing\n"
	.string "battle the other day!\p"
	.string "I wish I could battle\n"
	.string "like that.\p"
	.string "Oh wait, I can! I just\n"
	.string "need someone to battle!$"

MatchCall_Irwin_General2::
	.string "Uh, hello, {PLAYER}?\n"
	.string "It's your pal, Irwin!\p"
	.string "Hehe, I called right away!\p"
	.string "I think we can be good\n"
	.string "friends!$"

MatchCall_Irwin_General3::
	.string "Uh, hello, {PLAYER}?\n"
	.string "It's your pal, Irwin!\p"
	.string "Hearing about your\n"
	.string "escapades rocks my soul!\p"
	.string "It sure does!$"

MatchCall_Irwin_Battle::
	.string "Uh, hello, {PLAYER}?\n"
	.string "It's your pal, Irwin!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Arnie - Bug Catcher, Route 35
MatchCall_Arnie_General1::
	.string "Hey, {PLAYER}!\n"
	.string "How's it going?\p"
	.string "I bet your Pokémon are a\n"
	.string "lot stronger than before.$"

MatchCall_Arnie_General2::
	.string "Hey, {PLAYER}!\n"
	.string "How's it going?\p"
	.string "I'm always with my\n"
	.string "{STR_VAR_3}!\p"
	.string "It's so cute!\n"
	.string "I just love it!$"

MatchCall_Arnie_General3::
	.string "Hey, {PLAYER}!\n"
	.string "How's it going?\p"
	.string "Changing the topic here,\n"
	.string "I saw this {STR_VAR_3}\l"
	.string "for the first time.\p"
	.string "It was easy to beat,\n"
	.string "actually.$"

MatchCall_Arnie_Battle::
	.string "Hey, {PLAYER}!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Alan - Schoolboy, Route 36
MatchCall_Alan_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Alan!\p"
	.string "{PLAYER}, are you raising\n"
	.string "your Pokémon properly?\p"
	.string "I read in a book that you\n"
	.string "should raise any Pokémon\l"
	.string "you catch with love and\l"
	.string "care.$"

MatchCall_Alan_General2::
	.string "Hi, {PLAYER}!\n"
	.string "It's Alan!\p"
	.string "My {STR_VAR_3}'s getting\n"
	.string "stronger, exactly as I\l"
	.string "calculated!$"

MatchCall_Alan_General3::
	.string "Hi, {PLAYER}!\n"
	.string "It's Alan!\p"
	.string "By the way, we knocked\n"
	.string "out a wild {STR_VAR_3}\l"
	.string "just the other day.\p"
	.string "Studying up in advance\n"
	.string "worked!$"

MatchCall_Alan_FoundItem::
	.string "Hi, {PLAYER}!\n"
	.string "It's Alan!\p"
	.string "Hehehe, I picked up\n"
	.string "something nice!\p"
	.string "You can have it!\p"
	.string "Why don't you come to\n"
	.string "Route 36 and pick it up?$"

MatchCall_Alan_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Alan!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Dana - Lass, Route 38
MatchCall_Dana_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Dana!\p"
	.string "My {STR_VAR_3} is so full\n"
	.string "of energy, it's a little\l"
	.string "scary.\p"
	.string "How are your Pokémon\n"
	.string "doing?$"

MatchCall_Dana_General2::
	.string "Hi, {PLAYER}!\n"
	.string "It's Dana!\p"
	.string "My {STR_VAR_3} is getting\n"
	.string "prettier!\p"
	.string "I've been taking photos\n"
	.string "galore!$"

MatchCall_Dana_General3::
	.string "Hi, {PLAYER}!\n"
	.string "It's Dana!\p"
	.string "It took only an instant to\n"
	.string "KO a wild {STR_VAR_3}.\p"
	.string "It must be because you\n"
	.string "gave me some battling tips\l"
	.string "last time.$"

MatchCall_Dana_FoundItem::
	.string "Hi, {PLAYER}!\n"
	.string "It's Dana!\p"
	.string "You know what?\n"
	.string "I got a good gift!\p"
	.string "As I promised, it's yours!\n"
	.string "I'm sure you'd like it.\p"
	.string "Come get it! I'm waiting\n"
	.string "on Route 38!$"

MatchCall_Dana_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Dana!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Chad - Schoolboy, Route 38
MatchCall_Chad_General1::
	.string "Hello, {PLAYER}!\n"
	.string "It's Chad!\p"
	.string "How are your Pokémon\n"
	.string "doing?\p"
	.string "You know Prof. Oak, so of\n"
	.string "course your Pokémon are\l"
	.string "fine!\p"
	.string "My Pokémon are doing well\n"
	.string "too.\p"
	.string "But then, I am trying to\n"
	.string "become a Pokémon\l"
	.string "professor.$"

MatchCall_Chad_General2::
	.string "Hello, {PLAYER}!\n"
	.string "It's Chad!\p"
	.string "I recently began observing\n"
	.string "wild {STR_VAR_3}.\p"
	.string "I've been learning all\n"
	.string "sorts of new things\l"
	.string "through my observations.\p"
	.string "I wish I could become a\n"
	.string "Pokémon researcher like\l"
	.string "Prof. Oak soon.$"

MatchCall_Chad_General3::
	.string "Hello, {PLAYER}!\n"
	.string "It's Chad!\p"
	.string "I'm going to study hard\n"
	.string "so Prof. Oak will make\l"
	.string "me his assistant!$"

MatchCall_Chad_Battle::
	.string "Hello, {PLAYER}!\n"
	.string "It's Chad!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Derek - Pokefan M, Route 39
MatchCall_Derek_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Derek!\p"
	.string "You have to hear this!\p"
	.string "My lovable {STR_VAR_3}\n"
	.string "looked at me and grinned!\p"
	.string "It must be because our\n"
	.string "hearts beat together as\l"
	.string "one!$"

MatchCall_Derek_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Derek!\p"
	.string "Listen to this.\p"
	.string "My {STR_VAR_3} grins\n"
	.string "happily when I pinch its\l"
	.string "cheek.\p"
	.string "But it never grins for\n"
	.string "anyone else.\p"
	.string "I must be special.$"

MatchCall_Derek_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Derek!\p"
	.string "How is your Pikachu\n"
	.string "doing?\p"
	.string "Let's get together and\n"
	.string "brag about our Pikachu!$"

MatchCall_Derek_FoundItem::
	.string "Hey, {PLAYER}!\n"
	.string "It's Derek!\p"
	.string "I'd like you to have a\n"
	.string "Nugget.\p"
	.string "I'm on Route 39.\n"
	.string "Come pick it up!$"

MatchCall_Derek_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Derek!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Tully - Fisher, Route 42
MatchCall_Tully_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Tully!\p"
	.string "How's your trip coming\n"
	.string "along?\p"
	.string "I can't complain about\n"
	.string "my fishing!$"

MatchCall_Tully_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Tully!\p"
	.string "My {STR_VAR_3} has grown\n"
	.string "again.\p"
	.string "It was only about so big\n"
	.string "when I caught it, but now\l"
	.string "it's way bigger.$"

MatchCall_Tully_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Tully!\p"
	.string "Oh yeah, I KO'd a wild\n"
	.string "{STR_VAR_3}.\p"
	.string "It was huge, like this big\n"
	.string "even.\p"
	.string "Heh, I guess you can't\n"
	.string "tell over the phone…$"

MatchCall_Tully_FoundItem::
	.string "Hey, {PLAYER}!\n"
	.string "It's Tully!\p"
	.string "I picked up a good little\n"
	.string "thing at the water's edge.\p"
	.string "Like I promised, it's\n"
	.string "yours.\p"
	.string "I'll be waiting on\n"
	.string "Route 42.$"

MatchCall_Tully_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Tully!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Brent - Pokemaniac, Route 43
MatchCall_Brent_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Brent!\p"
	.string "Oh yeah, I saw you coming\n"
	.string "out of a Pokémon Center\l"
	.string "the other day.\p"
	.string "You heal your Pokémon\n"
	.string "regularly, don't you?\l"
	.string "I'm impressed.\p"
	.string "Heh, my {STR_VAR_3} is\n"
	.string "so tough, it doesn't need\l"
	.string "to go to Pokémon Centers\l"
	.string "often. Heheh!$"

MatchCall_Brent_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Brent!\p"
	.string "Oh yeah, I got an\n"
	.string "extremely rare Pokémon in\l"
	.string "a trade a while back.\p"
	.string "Do you want to know what\n"
	.string "it is?\p"
	.string "Hehe, I'm keeping it a\n"
	.string "secret!$"

MatchCall_Brent_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Brent!\p"
	.string "Did you know…?\p"
	.string "Bill's originally from\n"
	.string "Goldenrod.\p"
	.string "Evidently, Bill isn't very\n"
	.string "good at battling.$"

MatchCall_Brent_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Brent!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Tiffany - Picnicker, Route 43
MatchCall_Tiffany_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Tiffany!\p"
	.string "Are your Pokémon doing\n"
	.string "well?\p"
	.string "I hope you take them to a\n"
	.string "Pokémon Center every day.\p"
	.string "Don't push them too hard.\p"
	.string "My {STR_VAR_3} is cute and\n"
	.string "lively precisely because I\l"
	.string "take it to a Pokémon\l"
	.string "Center every day.$"

MatchCall_Tiffany_General2::
	.string "Hi, {PLAYER}!\n"
	.string "It's Tiffany!\p"
	.string "My {STR_VAR_3}'s adorable,\n"
	.string "don't you think so?\p"
	.string "I always sleep with it--\n"
	.string "it's so fluffy and warm!$"

MatchCall_Tiffany_General3::
	.string "Hi, {PLAYER}!\n"
	.string "It's Tiffany!\p"
	.string "Oh, and we had to battle\n"
	.string "a wild {STR_VAR_3} a\l"
	.string "while ago…\p"
	.string "My Clefairy came close to\n"
	.string "fainting!\p"
	.string "Isn't that awful?\n"
	.string "I hate those nasty\l"
	.string "{STR_VAR_3}!$"

MatchCall_Tiffany_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Tiffany!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Vance - Bird Keeper, Route 44
MatchCall_Vance_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Vance!\p"
	.string "Are you and your Pokémon\n"
	.string "fine?\p"
	.string "My {STR_VAR_3} looks like\n"
	.string "it will get tough enough\p"
	.string "to face and beat the\n"
	.string "legendary bird Pokémon!$"

MatchCall_Vance_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Vance!\p"
	.string "My {STR_VAR_3}'s become\n"
	.string "tougher.\p"
	.string "We've achieved liftoff!$"

MatchCall_Vance_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Vance!\p"
	.string "We can easily beat\n"
	.string "{STR_VAR_3}!\p"
	.string "…Huh? You too?\n"
	.string "Isn't that great?$"

MatchCall_Vance_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Vance!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Wilton - Fisher, Route 44
MatchCall_Wilton_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Wilton!\p"
	.string "Have your Pokémon grown\n"
	.string "any?\p"
	.string "My {STR_VAR_3} has grown\n"
	.string "quite a bit.$"

MatchCall_Wilton_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Wilton!\p"
	.string "My {STR_VAR_3}'s grown\n"
	.string "impressive!\p"
	.string "My fishing skills have\n"
	.string "improved too!$"

MatchCall_Wilton_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Wilton!\p"
	.string "We beat a wild\n"
	.string "{STR_VAR_3}…\p"
	.string "You know, I have more fun\n"
	.string "fishing than beating wild\l"
	.string "Pokémon.$"

MatchCall_Wilton_FoundItem::
	.string "Hey, {PLAYER}!\n"
	.string "It's Wilton!\p"
	.string "I snagged an item while\n"
	.string "fishing.\p"
	.string "Come pick it up on\n"
	.string "Route 44.$"

MatchCall_Wilton_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Wilton!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Kenji - Blackbelt, Route 45
MatchCall_Kenji_General1::
	.string "Hey, {PLAYER}!\n"
	.string "This is Kenji!\p"
	.string "{PLAYER}! Beautiful\n"
	.string "weather, hey?$"

MatchCall_Kenji_General2::
	.string "Hey, {PLAYER}!\n"
	.string "This is Kenji!\p"
	.string "Are you still on your\n"
	.string "journey?\p"
	.string "I remain dedicated to my\n"
	.string "training.\p"
	.string "Oooooaaarrrgh!$"

MatchCall_Kenji_General3::
	.string "Hey, {PLAYER}!\n"
	.string "This is Kenji!\p"
	.string "I'm in training now.\p"
	.string "I apologize, but call me\n"
	.string "back another time.\p"
	.string "Oooooaaarrrgh!$"

MatchCall_Kenji_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "This is Kenji!\p"
	.string "I'm taking a break!\p"
	.string "Why not drop by if you\n"
	.string "are free?$"

MatchCall_Kenji_FoundItem::
	.string "Hey, {PLAYER}!\n"
	.string "This is Kenji!\p"
	.string "I'm taking a break from\n"
	.string "training.\p"
	.string "I found something good.\n"
	.string "Come get it if you want!$"

@ Parry - Hiker, Route 45
MatchCall_Parry_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Parry!\p"
	.string "Are your Pokémon looking\n"
	.string "good?\p"
	.string "My {STR_VAR_3} and me--\n"
	.string "we're looking mighty\l"
	.string "dandy! Hahahah!$"

MatchCall_Parry_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Parry!\p"
	.string "Nothing can match my\n"
	.string "{STR_VAR_3} now.$"

MatchCall_Parry_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Parry!\p"
	.string "Yeah, we KO'd a wild\n"
	.string "{STR_VAR_3}!\p"
	.string "That was OK, but I wanted\n"
	.string "to get it…$"

MatchCall_Parry_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Parry!\p"
	.string "You'll battle with me\n"
	.string "again, right?$"

@ Erin - Picnicker, Route 46
MatchCall_Erin_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Erin!\p"
	.string "Are you raising your\n"
	.string "Pokémon?\p"
	.string "My {STR_VAR_3} is looking\n"
	.string "good!$"

MatchCall_Erin_General2::
	.string "Hi, {PLAYER}!\n"
	.string "It's Erin!\p"
	.string "My {STR_VAR_3} is much\n"
	.string "stronger than before!$"

MatchCall_Erin_General3::
	.string "Hi, {PLAYER}!\n"
	.string "It's Erin!\p"
	.string "And, and… I just battled\n"
	.string "and beat {STR_VAR_3}!\p"
	.string "I've raised my Pokémon\n"
	.string "properly!$"

MatchCall_Erin_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Erin!\p"
	.string "I'm working hard to raise\n"
	.string "my Pokémon!\p"
	.string "Come back for another\n"
	.string "battle!$"

@ Jack - Schoolboy, National Park
MatchCall_Jack_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jack!\p"
	.string "How are your Pokémon\n"
	.string "doing?\p"
	.string "My {STR_VAR_3} is so\n"
	.string "curious, it's a problem.\p"
	.string "Maybe it's like me…$"

MatchCall_Jack_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jack!\p"
	.string "My {STR_VAR_3}'s\n"
	.string "intelligence keeps rising.\p"
	.string "It might be smarter\n"
	.string "than yours!$"

MatchCall_Jack_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jack!\p"
	.string "Did you know?\p"
	.string "When it's raining, Thunder\n"
	.string "is sure to strike.\p"
	.string "My friend heard some great\n"
	.string "tips. When he tells me,\l"
	.string "I'll call right away and\l"
	.string "tell you.$"

MatchCall_Jack_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jack!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Beverly - Pokefan F, National Park
MatchCall_Beverly_General1::
	.string "Hello, {PLAYER}!\n"
	.string "It's Beverly!\p"
	.string "Keeping your Pokémon\n"
	.string "happy?\p"
	.string "My {STR_VAR_3} is healthy.\n"
	.string "It eats a lot every day.$"

MatchCall_Beverly_General2::
	.string "Hello, {PLAYER}!\n"
	.string "It's Beverly!\p"
	.string "I fancied up my\n"
	.string "{STR_VAR_3} and made it\l"
	.string "even cuter than before!$"

MatchCall_Beverly_General3::
	.string "Hello, {PLAYER}!\n"
	.string "It's Beverly!\p"
	.string "Are your Pokémon in prime\n"
	.string "form?\p"
	.string "Let's chat about Pokémon\n"
	.string "again.$"

MatchCall_Beverly_FoundItem::
	.string "Hello, {PLAYER}!\n"
	.string "It's Beverly!\p"
	.string "My husband got some\n"
	.string "Nuggets.\p"
	.string "If you'd like, you could\n"
	.string "have one as thanks for\l"
	.string "helping me out.\p"
	.string "I'll be at National Park.\n"
	.string "Please come see me when\l"
	.string "you can.$"

MatchCall_Beverly_Battle::
	.string "Hello, {PLAYER}!\n"
	.string "It's Beverly!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Huey - Sailor, Olivine Lighthouse
MatchCall_Huey_General1::
	.string "Yo, {PLAYER}!\n"
	.string "It's Huey!\p"
	.string "How's it going?$"

MatchCall_Huey_General2::
	.string "Yo, {PLAYER}!\n"
	.string "It's Huey!\p"
	.string "We have to battle again\n"
	.string "sometime.\p"
	.string "You can bet I'm going to\n"
	.string "keep challenging you till\l"
	.string "I win.$"

MatchCall_Huey_Battle::
	.string "Yo, {PLAYER}!\n"
	.string "It's Huey!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Gaven - Cooltrainer M, Route 26
MatchCall_Gaven_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Gaven!\p"
	.string "How are your Pokémon\n"
	.string "doing?\p"
	.string "My {STR_VAR_3}'s doing as\n"
	.string "great as ever.\p"
	.string "Let's keep at it and\n"
	.string "become Pokémon Champs!$"

MatchCall_Gaven_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Gaven!\p"
	.string "My {STR_VAR_3} might be\n"
	.string "greater than I imagined.\p"
	.string "I doubt I'll see a\n"
	.string "Pokémon that's better\l"
	.string "than mine.$"

MatchCall_Gaven_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Gaven!\p"
	.string "I obsess over how to\n"
	.string "beat you.$"

MatchCall_Gaven_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Gaven!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Beth - Cooltrainer F, Route 26
MatchCall_Beth_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Beth!\p"
	.string "Are you the kind of person\n"
	.string "who goes to Pokémon\l"
	.string "Centers often?\p"
	.string "I go every day. Watching\n"
	.string "out for the health of your\l"
	.string "Pokémon is a basic part of\l"
	.string "being a Pokémon trainer.$"

MatchCall_Beth_General2::
	.string "Hi, {PLAYER}!\n"
	.string "It's Beth!\p"
	.string "Do you remember my sweet\n"
	.string "{STR_VAR_3}?\p"
	.string "{STR_VAR_3} runs very\n"
	.string "fast.\p"
	.string "It's exhilarating to ride\n"
	.string "on its back when it really\l"
	.string "gets going.$"

MatchCall_Beth_General3::
	.string "Hi, {PLAYER}!\n"
	.string "It's Beth!\p"
	.string "Let's battle again\n"
	.string "sometime!$"

MatchCall_Beth_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Beth!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Jose - Bird Keeper, Route 27
MatchCall_Jose_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jose!\p"
	.string "Are your Pokémon still\n"
	.string "cooking?\p"
	.string "My {STR_VAR_3} has too\n"
	.string "much energy.\p"
	.string "Once it takes off, it\n"
	.string "won't come back for a\l"
	.string "while.$"

MatchCall_Jose_General2::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jose!\p"
	.string "Hey listen, my\n"
	.string "{STR_VAR_3}'s stick has\l"
	.string "this really delicious\l"
	.string "aroma.\p"
	.string "That aroma gets my\n"
	.string "appetite going!$"

MatchCall_Jose_General3::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jose!\p"
	.string "A while ago, my Farfetch'd\n"
	.string "KO'd this {STR_VAR_3}.\p"
	.string "You should have seen\n"
	.string "Farfetch'd wield that\l"
	.string "stick.\p"
	.string "Amazing stuff!$"

MatchCall_Jose_FoundItem::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jose!\p"
	.string "My Farfetch'd had\n"
	.string "something pretty in its\l"
	.string "beak.\p"
	.string "Like I promised, you can\n"
	.string "have it.\p"
	.string "Catch up to me on\n"
	.string "Route 27, and I'll let\l"
	.string "you have it.$"

MatchCall_Jose_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Jose!\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Reena - Cooltrainer F, Route 27
MatchCall_Reena_General1::
	.string "Hello, {PLAYER}.\n"
	.string "It's Reena.\p"
	.string "Hey, how are your Pokémon\n"
	.string "doing?\p"
	.string "What? Great? I see…\p"
	.string "What? My Pokémon?\p"
	.string "Of course they're doing\n"
	.string "great! What kind of a\l"
	.string "question is that?$"

MatchCall_Reena_General2::
	.string "Hello, {PLAYER}.\n"
	.string "It's Reena.\p"
	.string "Listen, dear…\p"
	.string "Do you recall my\n"
	.string "{STR_VAR_3}?\p"
	.string "Yes, exactly. That lovely\n"
	.string "{STR_VAR_3}.\p"
	.string "Wouldn't you agree it's a\n"
	.string "perfect match for me?$"

MatchCall_Reena_General3::
	.string "Hello, {PLAYER}.\n"
	.string "It's Reena.\p"
	.string "Don't be too proud just\n"
	.string "because you happened to\l"
	.string "beat me…\p"
	.string "It was a fluke!$"

MatchCall_Reena_Battle::
	.string "Hello, {PLAYER}.\n"
	.string "It's Reena.\p"
	.string "I was waiting for you.\n"
	.string "Let's battle!$"

@ Alex - Battle Girl, Route 13
MatchCall_Alex_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Alex!\p"
	.string "My regal Pokémon\n"
	.string "grow sharper by the day.\p"
	.string "{STR_VAR_3} is getting\n"
	.string "really tough!$"

MatchCall_Alex_General2::
	.string "Hey, {PLAYER}!\p"
	.string "I heard other regions have\n"
	.string "kings and queens. Why\l"
	.string "doesn't Kanto have\p"
	.string "any royalty?$"

MatchCall_Alex_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Alex!\p"
	.string "My regal Pokémon are ready\n"
	.string "for a rematch! Come to Route 13!$"

@ Riley - Biker, Route 17
MatchCall_Riley_General1::
	.string "Yo, {PLAYER}!\n"
	.string "Riley here.\p"
	.string "Cycling Road is the best.\n"
	.string "Nothing beats the wind\l"
	.string "in your face.\p"
	.string "{STR_VAR_3} loves the\n"
	.string "speed too!$"

MatchCall_Riley_General2::
	.string "Yo, {PLAYER}!\p"
	.string "You Johto kids aren't bad.\n"
	.string "Maybe I misjudged you.\p"
	.string "Don't let it go to your\n"
	.string "head though!$"

MatchCall_Riley_Battle::
	.string "Yo, {PLAYER}!\n"
	.string "Riley here.\p"
	.string "Get down to Cycling Road!\n"
	.string "I want a rematch!$"

@ Trevor - Juggler, Route 14
MatchCall_Trevor_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Trevor.\p"
	.string "Did you know Pokémon get\n"
	.string "friendlier when you train\l"
	.string "in memorable places?\p"
	.string "{STR_VAR_3} seems to\n"
	.string "like it here.$"

MatchCall_Trevor_General2::
	.string "Hi, {PLAYER}!\p"
	.string "Some Pokémon moves\n"
	.string "are stronger when your\p"
	.string "Pokémon feels more\n"
	.string "friendly toward you!$"

MatchCall_Trevor_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Trevor.\p"
	.string "My friends are ready for battle!\n"
	.string "Come see on Route 14!$"

@ Kyle - Fisherman, Route 12
MatchCall_Kyle_General1::
	.string "Who is this?!\n"
	.string "I called you?\p"
	.string "This is Kyle. Don't forget!$"

MatchCall_Kyle_General2::
	.string "Hey, {PLAYER}!\p"
	.string "Do you remember?\n"
	.string "The secrets of fishing?$"

MatchCall_Kyle_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "Kyle here.\p"
	.string "I've reeled in some tough\n"
	.string "new Pokémon!\p"
	.string "Come to Route 12 for\n"
	.string "a battle!$"

@ Carter - Pokefan, Route 14
MatchCall_Carter_General1::
	.string "Hi there, {PLAYER}!\n"
	.string "Carter here.\p"
	.string "I've been collecting rare\n"
	.string "starter Pokémon.\p"
	.string "My {STR_VAR_3} is my\n"
	.string "newest pride and joy!$"

MatchCall_Carter_General2::
	.string "Hi, {PLAYER}!\p"
	.string "Did you know there are\n"
	.string "starter Pokémon from many\l"
	.string "different regions?\p"
	.string "I want to collect them\n"
	.string "all!$"

MatchCall_Carter_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "Carter here.\p"
	.string "I have new starters to\n"
	.string "show off! Come to\l"
	.string "Route 14!$"

@ Hillary - Expert, Route 15
MatchCall_Hillary_General1::
	.string "Hello, {PLAYER}.\n"
	.string "It's Teacher Hillary.\p"
	.string "Why aren't you in school?$"

MatchCall_Hillary_General2::
	.string "Hello, {PLAYER}.\p"
	.string "Are you playing games\n"
	.string "instead of doing homework?$"

MatchCall_Hillary_Battle::
	.string "Hello, {PLAYER}.\n"
	.string "It's Hillary.\p"
	.string "My Pokémon have graduated\n"
	.string "to the next level!\p"
	.string "Come test us on Route 15!$"

@ Rob - Bug Catcher, Route 2
MatchCall_Rob_General1::
	.string "Hey, {PLAYER}!\n"
	.string "Rob here!\p"
	.string "Viridian Forest is full\n"
	.string "of cool bugs!$"

MatchCall_Rob_General2::
	.string "Hey, {PLAYER}!\p"
	.string "I saw a Bug Type Gym\n"
	.string "Leader in Viridian Forest!$" 

MatchCall_Rob_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "Rob here!\p"
	.string "My bug team is stronger\n"
	.string "than ever!\p"
	.string "Come to Route 2 for a\n"
	.string "rematch!$"

@ Nicole - Swimmer, Route 20
MatchCall_Nicole_General1::
	.string "Hi, {PLAYER}!\n"
	.string "It's Nicole!\p"
	.string "The waves are great today!\n"
	.string "My Pokémon love swimming\l"
	.string "in the open sea.\p"
	.string "{STR_VAR_3} is getting\n"
	.string "so fast!$"

MatchCall_Nicole_General2::
	.string "Hi, {PLAYER}!\p"
	.string "Swimming with Pokémon is\n"
	.string "the best exercise.$"

MatchCall_Nicole_Battle::
	.string "Hi, {PLAYER}!\n"
	.string "It's Nicole!\p"
	.string "My water Pokémon are\n"
	.string "raring to battle!\p"
	.string "Come to Route 20!$"

@ Billy - School Kid, Route 15
MatchCall_Billy_General1::
	.string "Hey, {PLAYER}!\n"
	.string "It's Billy.\p"
	.string "I've been studying battle\n"
	.string "strategies in class.\p"
	.string "{STR_VAR_3} and I have\n"
	.string "been practicing them!$"

MatchCall_Billy_General2::
	.string "Hey, {PLAYER}!\p"
	.string "Tests are coming up, but\n"
	.string "I'd rather be battling.\p"
	.string "Book smarts aren't\n"
	.string "everything, right?$"

MatchCall_Billy_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "It's Billy.\p"
	.string "I learned some new tricks!\n"
	.string "Come to Route 15!$"

@ Kenny - Hiker, Route 13
MatchCall_Kenny_General1::
	.string "Hey there, {PLAYER}!\n"
	.string "Kenny here.\p"
	.string "Were all mountains really\n"
	.string "shaped by oceans and rivers?$"

MatchCall_Kenny_General2::
	.string "Hey, {PLAYER}!\p"
	.string "It's Kenny here.\n"
	.string "I visited the Pewter museum!\p"
	.string "Did you know the entire Kanto\n"
	.string "region was once under water?$"

MatchCall_Kenny_Battle::
	.string "Hey there, {PLAYER}!\n"
	.string "Kenny here.\p"
	.string "I've trained hard in the\n"
	.string "mountains!\p"
	.string "Come to Route 13 for\n"
	.string "a battle!$"

@ Joel - Biker, Route 17
MatchCall_Joel_General1::
	.string "Hey, {PLAYER}!\n"
	.string "Joel here.\p"
	.string "I've been working on\n"
	.string "looking cool in battle.\p"
	.string "{STR_VAR_3} has some\n"
	.string "flashy new moves!$"

MatchCall_Joel_General2::
	.string "Hey, {PLAYER}!\p"
	.string "Joel here.\p"
	.string "There was an accident on\n"
	.string "Cycling Road.\p"
	.string "Being safe is the coolest thing\n"
	.string "you can be.$"

MatchCall_Joel_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "Joel here.\p"
	.string "I look AND fight cool now!\n"
	.string "Come to Cycling Road!$"

@ Charles - Biker, Route 17
MatchCall_Charles_General1::
	.string "Hey, {PLAYER}!\n"
	.string "Charles here.\p"
	.string "I was something of a\n"
	.string "heartbreaker in Unova.\p"
	.string "Now I'm a highway star!$"

MatchCall_Charles_General2::
	.string "Hey, {PLAYER}!\p"
	.string "Cycling Road at night is\n"
	.string "something else.\p"
	.string "The streetlights and the\n"
	.string "wind… it's freedom!$"

MatchCall_Charles_Battle::
	.string "Hey, {PLAYER}!\n"
	.string "Charles here.\p"
	.string "The highway stars want\n"
	.string "revenge! Come to\l"
	.string "Cycling Road!$"
