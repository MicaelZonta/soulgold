@ ===========================================================================
@ Nexus -- texts of the Ultra Beast fragments. PROPOSAL, not built into the ROM.
@ Design: .claude/rift_missions/nexus/ULTRA_BEASTS.md
@
@ Per Ultra Beast, six texts, in the order the player meets them:
@   _Arrival    narration, on entering the fragment (no speaker plate)
@   _Intro      fifth trainer, trainerbattle intro (the plate comes from the trainer)
@   _Defeat     fifth trainer, in-battle defeat text
@   _After      fifth trainer, msgbox after the battle ({SPEAKER} needs a new SP_NAME)
@   _Boss       narration, the Ultra Beast takes shape
@   _LookerFile Looker at the altar, after the player returns that day
@
@ Measured with .claude/skills/nomear-falante/medir_linha.py (limit 208 px).
@ ===========================================================================

@ ---------------------------------------------------------------------------
@ UB-01 SYMBIONT -- Nihilego -- Colress
@ ---------------------------------------------------------------------------
Nexus_Text_Symbiont_Arrival:
	.string "The rift let out into deep water that\n"
	.string "did not drown you.\p"
	.string "Pale lights drifted overhead, trailing\n"
	.string "threads. Wherever one touched the\l"
	.string "glass floor, the glass glowed brighter,\l"
	.string "and cracked a little.$"

Nexus_Text_Symbiont_Intro:
	.string "Ah. A visitor. Good. I was running\n"
	.string "short of variables.\p"
	.string "This place gives strength away. Every\n"
	.string "Pokémon here is stronger than it\l"
	.string "ought to be, and not one of them asks\l"
	.string "what it costs.\p"
	.string "I have always wanted to see a\n"
	.string "Pokémon's full power. Here, I only\l"
	.string "have to watch.\p"
	.string "Let us see how far yours will go.$"

Nexus_Text_Symbiont_Defeat:
	.string "Fascinating. Every one of your\n"
	.string "Pokémon stopped short of the edge.\p"
	.string "By choice.$"

Nexus_Text_Symbiont_After:
	.string "{SPEAKER NAME_COLRESS}I measured everything, and I still\n"
	.string "cannot tell you what held them back.\p"
	.string "…Perhaps that is the result.\p"
	.string "Something below us has noticed you. It\n"
	.string "is looking for someone to lend its\l"
	.string "strength to.\p"
	.string "I would decline, if I were you. I say\n"
	.string "that as a man who would not.$"

Nexus_Text_Symbiont_Boss:
	.string "The lights in the water drew together\n"
	.string "into one shape.\p"
	.string "It hung in front of you, weightless and\n"
	.string "patient, as if waiting to be let in.$"

Nexus_Text_Symbiont_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-01. Symbiont.\p"
	.string "A scientist who would not stop taking\n"
	.string "notes on your Pokémon, and a creature\l"
	.string "that offers power to anyone who holds\l"
	.string "still.\p"
	.string "I have filed them together. I suspect\n"
	.string "they would both find that flattering.$"

@ ---------------------------------------------------------------------------
@ UB-02 ABSORPTION -- Buzzwole -- Bruno
@ ---------------------------------------------------------------------------
Nexus_Text_Absorption_Arrival:
	.string "Heat hit you the moment you stepped\n"
	.string "through.\p"
	.string "Under a green canopy, everything had\n"
	.string "grown too large. Leaves wider than\l"
	.string "doors, roots as thick as pillars.\p"
	.string "And every one of them looked tired.$"

Nexus_Text_Absorption_Intro:
	.string "I have trained every day of my life.\p"
	.string "Here, I wake up stronger than I was\n"
	.string "when I went to sleep. Without lifting\l"
	.string "a finger.\p"
	.string "I do not like it. Strength nobody\n"
	.string "earned has to come from somewhere.\p"
	.string "Show me yours. I want to know if it\n"
	.string "is real!$"

Nexus_Text_Absorption_Defeat:
	.string "Hoo hah! …Yes. That was earned.$"

Nexus_Text_Absorption_After:
	.string "{SPEAKER NAME_BRUNO}Did you feel it? The jungle took\n"
	.string "something back just now. From me.\p"
	.string "Good. It was never mine.\p"
	.string "The one that feeds on all this is\n"
	.string "close. It will show you its strength\l"
	.string "before it ever uses it.\p"
	.string "Do not be impressed. Hit it.$"

Nexus_Text_Absorption_Boss:
	.string "The canopy shook.\p"
	.string "Something landed in the clearing,\n"
	.string "flexed once, and waited to be\l"
	.string "admired.$"

Nexus_Text_Absorption_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-02. Absorption.\p"
	.string "A creature that takes strength from\n"
	.string "others and shows it off, and a man who\l"
	.string "built his own and would not accept\l"
	.string "a gift.\p"
	.string "I have underlined the man. Twice.$"

@ ---------------------------------------------------------------------------
@ UB-02 BEAUTY -- Pheromosa -- Elesa
@ ---------------------------------------------------------------------------
Nexus_Text_Beauty_Arrival:
	.string "White sand, and a straight white path\n"
	.string "across it, lit from below.\p"
	.string "Nothing marked it. When you looked\n"
	.string "back, your own footprints were\l"
	.string "already gone.$"

Nexus_Text_Beauty_Intro:
	.string "Stop right there. Not one step closer.\p"
	.string "Everyone in this place looks at me,\n"
	.string "and no one ever reaches me. I used to\l"
	.string "call that an audience.\p"
	.string "Battle me from where you're standing.\n"
	.string "Dazzle me, if you can.$"

Nexus_Text_Beauty_Defeat:
	.string "…You weren't looking at me at all.\n"
	.string "You were looking at your Pokémon.\p"
	.string "How rude. How refreshing.$"

Nexus_Text_Beauty_After:
	.string "{SPEAKER NAME_ELESA}The sand takes every footprint away.\n"
	.string "Yours are still there. I checked.\p"
	.string "There's something out there that\n"
	.string "won't let anything touch it. Everyone\l"
	.string "it looks at forgets why they came.\p"
	.string "Remember why you came.$"

Nexus_Text_Beauty_Boss:
	.string "Someone was already standing at the\n"
	.string "end of the path. Perfectly still.\l"
	.string "Perfectly clean.\p"
	.string "For a moment, you forgot what you\n"
	.string "were doing there.$"

Nexus_Text_Beauty_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-02. Beauty.\p"
	.string "You described the creature, and I\n"
	.string "wrote down the word “lovely.”\p"
	.string "I have crossed it out. It is still\n"
	.string "perfectly legible. That, I think, is\l"
	.string "the whole report.$"

@ ---------------------------------------------------------------------------
@ UB-03 LIGHTING -- Xurkitree -- Volkner
@ ---------------------------------------------------------------------------
Nexus_Text_Lighting_Arrival:
	.string "A city of towers and cables, under a\n"
	.string "sky with no stars.\p"
	.string "Every window was dark but one, high\n"
	.string "up, burning white. All the cables ran\l"
	.string "toward it.$"

Nexus_Text_Lighting_Intro:
	.string "Took you long enough.\p"
	.string "Every light in this city went out so\n"
	.string "this one room could stay on. I keep\l"
	.string "telling myself that's a fair trade for\l"
	.string "a decent battle.\p"
	.string "So. Are you worth the blackout?$"

Nexus_Text_Lighting_Defeat:
	.string "Ha! There it is. That's the spark\n"
	.string "I've been waiting for.$"

Nexus_Text_Lighting_After:
	.string "{SPEAKER NAME_VOLKNER}Funny. The lights outside came back\n"
	.string "on while we fought. First time ever.\p"
	.string "Something's pulling on the lines\n"
	.string "again. Harder. It's figured out where\l"
	.string "all the power went.\p"
	.string "Go on. I'll keep the lights on for you.$"

Nexus_Text_Lighting_Boss:
	.string "Every cable in the room went taut at\n"
	.string "once.\p"
	.string "The window flickered, and something\n"
	.string "that was mostly wire stood up in\l"
	.string "the light.$"

Nexus_Text_Lighting_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-03. Lighting.\p"
	.string "A city kept in the dark so that one\n"
	.string "room could stay lit, and one bored man\l"
	.string "could have a good fight.\p"
	.string "The old file says the creature once\n"
	.string "emptied a power plant. I find I am not\l"
	.string "sure which of the two I am filing.$"

@ ---------------------------------------------------------------------------
@ UB-04 BLASTER -- Celesteela -- Steven
@ ---------------------------------------------------------------------------
Nexus_Text_Blaster_Arrival:
	.string "A crater under a sky crowded with\n"
	.string "stars.\p"
	.string "Tall steel shoots rose from the floor\n"
	.string "like bamboo, scorched black at the\l"
	.string "base, all pointing straight up.$"

Nexus_Text_Blaster_Intro:
	.string "Look up. Nothing in this place ever\n"
	.string "falls.\p"
	.string "I have walked the whole crater, and I\n"
	.string "have not found a single stone that\l"
	.string "came down.\p"
	.string "Everything here only leaves.\p"
	.string "…Forgive me. A battle, then. I have\n"
	.string "been hoping someone would stay long\l"
	.string "enough.$"

Nexus_Text_Blaster_Defeat:
	.string "So that's it. Something that keeps\n"
	.string "its feet on the ground can still\l"
	.string "reach this high.$"

Nexus_Text_Blaster_After:
	.string "{SPEAKER NAME_STEVEN}I'll stay a little longer. I would\n"
	.string "like to find one stone here that fell.\p"
	.string "Something is warming up past the\n"
	.string "towers. You can feel the heat in\l"
	.string "the steel.\p"
	.string "Stand well away from its arms.$"

Nexus_Text_Blaster_Boss:
	.string "The ground shook, and one of the steel\n"
	.string "shoots began to rise.\p"
	.string "It was not a tower. It had arms, and\n"
	.string "both of them were glowing.$"

Nexus_Text_Blaster_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-04. Blaster.\p"
	.string "A crater where nothing falls, and a\n"
	.string "collector of fallen stones who could\l"
	.string "not find a single one.\p"
	.string "I have closed this file very gently.\n"
	.string "I cannot tell you why.$"

@ ---------------------------------------------------------------------------
@ UB-04 BLADE -- Kartana -- Ramos
@ ---------------------------------------------------------------------------
Nexus_Text_Blade_Arrival:
	.string "A forest of white trees, every one of\n"
	.string "them folded.\p"
	.string "Branches creased at clean angles.\n"
	.string "Leaves cut to the same shape. Nothing\l"
	.string "was growing. Everything had been\l"
	.string "trimmed.$"

Nexus_Text_Blade_Intro:
	.string "Hoho! A sprout, all the way out here.\p"
	.string "Thirty years I've carried these\n"
	.string "shears, and I've never been anywhere\l"
	.string "with nothing left to prune.\p"
	.string "Every tree here is cut already. Clean\n"
	.string "as a folded letter. And not one of\l"
	.string "them is growing.\p"
	.string "Show an old man something that grows!$"

Nexus_Text_Blade_Defeat:
	.string "Hohoho! Now that is a sprout with\n"
	.string "roots.$"

Nexus_Text_Blade_After:
	.string "{SPEAKER NAME_RAMOS}Nothing grows without a little\n"
	.string "cutting, sprout. But nothing grows\l"
	.string "from cutting alone, either.\p"
	.string "Mind your step past the trees.\n"
	.string "Something in there only ever learned\l"
	.string "the first half.$"

Nexus_Text_Blade_Boss:
	.string "A leaf came loose from the nearest\n"
	.string "branch and did not fall.\p"
	.string "It stood up and unfolded one arm, and\n"
	.string "the tree behind it slid apart in two\l"
	.string "clean pieces.$"

Nexus_Text_Blade_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-04. Blade.\p"
	.string "A gardener in a forest where nothing\n"
	.string "grows, and a creature as thin as paper\l"
	.string "that once cut down a steel tower.\p"
	.string "I have put a paperweight on this file.\n"
	.string "It seemed only sensible.$"

@ ---------------------------------------------------------------------------
@ UB-05 GLUTTON -- Guzzlord -- Guzma
@ ---------------------------------------------------------------------------
Nexus_Text_Glutton_Arrival:
	.string "A city, or what was left of one.\p"
	.string "Half the buildings were gone. Not\n"
	.string "fallen. Missing, as if bitten off.\p"
	.string "Somewhere far away, something was\n"
	.string "still chewing.$"

Nexus_Text_Glutton_Intro:
	.string "See this street? Every building,\n"
	.string "wrecked. Every single one.\p"
	.string "Folks always said I break everything\n"
	.string "I touch. So I figured a place like\l"
	.string "this had to be mine.\p"
	.string "Turns out somethin' else got here\n"
	.string "first. And it's still hungry.\p"
	.string "So what are YOU hungry for, huh?!$"

Nexus_Text_Glutton_Defeat:
	.string "…Again. I throw everything I got at\n"
	.string "it, and it's never enough. Never.$"

Nexus_Text_Glutton_After:
	.string "{SPEAKER NAME_GUZMA}Kukui used to say winnin' ain't the\n"
	.string "point. Used to drive me nuts.\p"
	.string "…Tch. Forget it.\p"
	.string "That thing's on the next block, eatin'\n"
	.string "whatever's left. It don't get full.\l"
	.string "It don't ever get full.\p"
	.string "Go on. Go show it what enough looks\n"
	.string "like.$"

Nexus_Text_Glutton_Boss:
	.string "The chewing stopped.\p"
	.string "A mouth that was most of a body turned\n"
	.string "toward you, and the street in front of\l"
	.string "it was simply not there anymore.$"

Nexus_Text_Glutton_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-05. Glutton.\p"
	.string "A city eaten down to the street, and a\n"
	.string "young man sitting in it, insisting he\l"
	.string "had done it himself.\p"
	.string "He had not. I have written that down\n"
	.string "for him, in case he ever asks.$"

@ ---------------------------------------------------------------------------
@ UB ADHESIVE -- Poipole -- Zossie
@ ---------------------------------------------------------------------------
Nexus_Text_Adhesive_Arrival:
	.string "A small bright room with no corners.\p"
	.string "Soft lights floated near the ceiling.\n"
	.string "When one brushed your sleeve, it\l"
	.string "stayed there a moment before letting\l"
	.string "go.$"

Nexus_Text_Adhesive_Intro:
	.string "Oh! Oh! Someone came! Hi! Hello!\p"
	.string "Everything in here sticks together.\n"
	.string "The lights, the floor, the little\l"
	.string "ones… And now you!\p"
	.string "You're not leaving till we battle.\n"
	.string "That's the rule. I just made it up!$"

Nexus_Text_Adhesive_Defeat:
	.string "Aww… But that was fun, right? You\n"
	.string "had fun? Say you had fun!$"

Nexus_Text_Adhesive_After:
	.string "{SPEAKER NAME_ZOSSIE}Can I tell you a secret? Where I'm\n"
	.string "from, there wasn't any light. None!\p"
	.string "So when something bright shows up,\n"
	.string "you kind of want to stick to it.\p"
	.string "There's a little one over there who\n"
	.string "wants to stick to you. Be nice to it,\l"
	.string "okay? Promise!$"

Nexus_Text_Adhesive_Boss:
	.string "One of the lights drifted down from\n"
	.string "the ceiling and landed in front of\l"
	.string "you.\p"
	.string "It had a face, and it was very, very\n"
	.string "curious about yours.$"

Nexus_Text_Adhesive_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Adhesive.\p"
	.string "No harm done. No damage. One very\n"
	.string "small creature that followed you all\l"
	.string "the way to the door.\p"
	.string "It is the shortest file I have. I have\n"
	.string "read it four times.$"

@ ---------------------------------------------------------------------------
@ UB STINGER -- Naganadel -- Soliera
@ ---------------------------------------------------------------------------
Nexus_Text_Stinger_Arrival:
	.string "The top of a tower, far above a city\n"
	.string "of lights.\p"
	.string "The wind came from every side at\n"
	.string "once. Long straight scars were cut\l"
	.string "into the roof, all of them pointing\l"
	.string "at the same spot.$"

Nexus_Text_Stinger_Intro:
	.string "Stop. State your purpose.\p"
	.string "…No. It does not matter.\p"
	.string "I was given one objective in this\n"
	.string "place. Strike once, and strike true.\p"
	.string "You are standing where my objective\n"
	.string "is. Prepare yourself.$"

Nexus_Text_Stinger_Defeat:
	.string "One strike was not enough.\n"
	.string "…Noted.$"

Nexus_Text_Stinger_After:
	.string "{SPEAKER NAME_SOLIERA}Where I come from, we gave a small\n"
	.string "one away. To someone who helped us.\p"
	.string "I never learned what it grew into.\p"
	.string "If what is circling this tower is the\n"
	.string "answer, do not look away from the\l"
	.string "needle. Not once.$"

Nexus_Text_Stinger_Boss:
	.string "Something passed overhead too fast to\n"
	.string "see. Then again, lower.\p"
	.string "The third time, it stopped in the air\n"
	.string "in front of you, and pointed.$"

Nexus_Text_Stinger_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Stinger.\p"
	.string "You tell me it carries enough poison\n"
	.string "to fill a bathtub, and flies faster\l"
	.string "than you could follow.\p"
	.string "I have moved my desk slightly further\n"
	.string "from the window. For no reason.$"

@ ---------------------------------------------------------------------------
@ UB ASSEMBLY -- Stakataka -- Byron
@ ---------------------------------------------------------------------------
Nexus_Text_Assembly_Arrival:
	.string "A quarry of grey stone, with walls in\n"
	.string "every direction.\p"
	.string "You were sure the way behind you had\n"
	.string "been open a moment ago.$"

Nexus_Text_Assembly_Intro:
	.string "Hah! Another one wandered into the\n"
	.string "quarry! Mind the walls, youngster.\l"
	.string "They move.\p"
	.string "I dig for a living. I know stone. And\n"
	.string "not one stone in this place is stone.\p"
	.string "Every brick is alive, and every one\n"
	.string "of them decided to hold up the next.\p"
	.string "That's a wall worth respecting!\n"
	.string "Now let's see about you!$"

Nexus_Text_Assembly_Defeat:
	.string "Hah! Good! A wall's only as good as\n"
	.string "whatever's hitting it!$"

Nexus_Text_Assembly_After:
	.string "{SPEAKER NAME_BYRON}My son would love this place. He'd\n"
	.string "dig the whole thing up, the fool.\p"
	.string "Listen. There's something stacking\n"
	.string "itself behind that wall. A lot of\l"
	.string "somethings.\p"
	.string "They hold together because they chose\n"
	.string "to. Don't expect them to fall apart\l"
	.string "because you asked.$"

Nexus_Text_Assembly_Boss:
	.string "The wall ahead shifted, brick by brick,\n"
	.string "and stood up on four thin legs.\p"
	.string "Every stone in it turned to look at\n"
	.string "you.$"

Nexus_Text_Assembly_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Assembly.\p"
	.string "One creature that is really a hundred\n"
	.string "and fifty, all holding each other up.\p"
	.string "I have been told it is a threat. I have\n"
	.string "filed it under threats. I keep wanting\l"
	.string "to move it.$"

@ ---------------------------------------------------------------------------
@ UB BURST -- Blacephalon -- Fantina
@ ---------------------------------------------------------------------------
Nexus_Text_Burst_Arrival:
	.string "An empty theatre, every seat filled\n"
	.string "with shadow.\p"
	.string "Fireworks burst overhead without a\n"
	.string "sound. Each time one went off, the\l"
	.string "shadows in the seats grew fainter.$"

Nexus_Text_Burst_Intro:
	.string "Bonsoir! Ah, enfin! Someone in the\n"
	.string "seats who is still breathing!\p"
	.string "Every night here, the show is\n"
	.string "magnifique. Fireworks, applause…\p"
	.string "And every night, the audience is a\n"
	.string "little fainter. I have begun to\l"
	.string "wonder who pays for the lights.\p"
	.string "Non, non! No more thinking!\n"
	.string "Dance with me!$"

Nexus_Text_Burst_Defeat:
	.string "Bravo! Bravo! You took the whole show\n"
	.string "and gave nothing away!$"

Nexus_Text_Burst_After:
	.string "{SPEAKER NAME_FANTINA}The final act is not mine. It never\n"
	.string "was.\p"
	.string "When the curtain goes up out there, it\n"
	.string "will be charming. It will make you want\l"
	.string "to lean in.\p"
	.string "Do not lean in, mon ami. Whatever\n"
	.string "you do.$"

Nexus_Text_Burst_Boss:
	.string "The curtain rose on an empty stage.\p"
	.string "Something walked out with a strange,\n"
	.string "careless step. It bowed deeply, and\l"
	.string "its head began to glow.$"

Nexus_Text_Burst_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Burst.\p"
	.string "A performer who charms its audience,\n"
	.string "blows its own head off, and takes\l"
	.string "their strength while they clap.\p"
	.string "I have been to theatre like that. I\n"
	.string "did not know it was a species.$"
