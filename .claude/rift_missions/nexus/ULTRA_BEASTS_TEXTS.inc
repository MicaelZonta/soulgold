@ ===========================================================================
@ Nexus -- Ultra Beast texts. PROPOSAL, not built into the ROM.
@ Design: .claude/rift_missions/nexus/ULTRA_BEASTS.md
@ Readable copies live in each trainer sheet (nexus/<region>/<trainer>.md).
@
@ Two kinds of text:
@  FRAGMENT (one set per Ultra Beast)
@   _Arrival     narration on entering the fragment
@   _Boss        narration, the Ultra Beast takes shape
@   _LookerFile  Looker at the altar, after the player catches it that day
@  TRAINER (one set per trainer)
@   _Intro / _Defeat                  GENERIC: the trainer in rooms 1-4, about
@                                     himself; fits any fragment
@   _ChampionIntro / _ChampionDefeat  CHAMPION: the fight right before the
@   _ChampionAfter                    Ultra Beast; about the creature
@  _Intro/_Defeat texts are trainerbattle texts (the plate comes from the
@  trainer). _ChampionAfter and _LookerFile carry {SPEAKER}.
@
@ Wrapped at 208 px with medir_linha.py widths.
@ ===========================================================================


@ ---------------------------------------------------------------------------
@ UB-01 SYMBIONT -- Nihilego -- champion: Colress
@ ---------------------------------------------------------------------------
Nexus_Text_Symbiont_Arrival:
	.string "The rift let out into deep water that\n"
	.string "did not drown you.\p"
	.string "Pale lights drifted overhead, trailing\n"
	.string "threads. Wherever one touched the\l"
	.string "glass floor, the glass glowed brighter,\l"
	.string "and cracked a little.$"

Nexus_Text_Colress_ChampionIntro:
	.string "You feel it too, don't you? Something in\n"
	.string "the water, deciding whether to let us\l"
	.string "in.\p"
	.string "I have been observing it. It does not\n"
	.string "attack. It offers.\p"
	.string "Whatever it touches grows stronger and\n"
	.string "forgets how to stop. It is everything I\l"
	.string "ever set out to find…\p"
	.string "…and I find I do not enjoy watching it.\n"
	.string "Before it chooses you, show me what\l"
	.string "your Pokémon are without it!$"

Nexus_Text_Colress_ChampionDefeat:
	.string "…There. That was their own strength,\n"
	.string "every last point of it. No toxin could\l"
	.string "have measured that.$"

Nexus_Text_Colress_ChampionAfter:
	.string "{SPEAKER NAME_COLRESS}I spent years trying to take away a\n"
	.string "Pokémon's limits. It took that creature\l"
	.string "to show me what a limit is for.\p"
	.string "It will offer you strength. It will be\n"
	.string "very generous about it.\p"
	.string "Refuse. I say that as a man who would\n"
	.string "have said yes.$"

Nexus_Text_Symbiont_Boss:
	.string "The lights in the water drew together\n"
	.string "into one shape.\p"
	.string "It hung in front of you, weightless and\n"
	.string "patient, as if waiting to be let in.$"

Nexus_Text_Symbiont_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-01. Symbiont.\p"
	.string "A scientist who spent his life trying to\n"
	.string "remove a Pokémon's limits, and a\l"
	.string "creature that removes them for free.\p"
	.string "You tell me he asked you to refuse it. I\n"
	.string "have underlined that. I did not expect\l"
	.string "to.$"


@ ---------------------------------------------------------------------------
@ UB-02 ABSORPTION -- Buzzwole -- champion: Bruno
@ ---------------------------------------------------------------------------
Nexus_Text_Absorption_Arrival:
	.string "Heat hit you the moment you stepped\n"
	.string "through.\p"
	.string "Under a green canopy, everything had\n"
	.string "grown too large. Leaves wider than\l"
	.string "doors, roots as thick as pillars.\p"
	.string "And every one of them looked tired.$"

Nexus_Text_Bruno_ChampionIntro:
	.string "I have watched it for three days. It\n"
	.string "lifts nothing. It trains nothing. It\l"
	.string "poses, and it drinks.\p"
	.string "And it is stronger than any fighter I\n"
	.string "have ever faced.\p"
	.string "I do not hate it. It is only doing what\n"
	.string "it is. But I will not stand beside it and\l"
	.string "call that strength.\p"
	.string "Show me the other kind!$"

Nexus_Text_Bruno_ChampionDefeat:
	.string "Hoo hah! Yes. That. It cannot drink that\n"
	.string "from anyone.$"

Nexus_Text_Bruno_ChampionAfter:
	.string "{SPEAKER NAME_BRUNO}When it comes, it will flex first. It\n"
	.string "wants you to fear its size before it\l"
	.string "ever throws a punch.\p"
	.string "Do not look at the muscles. Look at the\n"
	.string "legs. Anything that strong still has to\l"
	.string "stand somewhere.\p"
	.string "Go. I will be here. Training.$"

Nexus_Text_Absorption_Boss:
	.string "The canopy shook.\p"
	.string "Something landed in the clearing,\n"
	.string "flexed once, and waited to be admired.$"

Nexus_Text_Absorption_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-02. Absorption.\p"
	.string "A creature that drinks strength from\n"
	.string "others and then shows it off, and a man\l"
	.string "who built his own and would not call\l"
	.string "that strength.\p"
	.string "“Look at the legs,” he told you. I have\n"
	.string "no idea what it means, and I have\l"
	.string "written it down anyway.$"


@ ---------------------------------------------------------------------------
@ UB-02 BEAUTY -- Pheromosa -- champion: Elesa
@ ---------------------------------------------------------------------------
Nexus_Text_Beauty_Arrival:
	.string "White sand, and a straight white path\n"
	.string "across it, lit from below.\p"
	.string "Nothing marked it. When you looked\n"
	.string "back, your own footprints were already\l"
	.string "gone.$"

Nexus_Text_Elesa_ChampionIntro:
	.string "I've seen it. From a distance -- it\n"
	.string "won't allow anything closer.\p"
	.string "It moves like the only clean thing left\n"
	.string "in the world, and it looks at everything\l"
	.string "else like a stain.\p"
	.string "Everyone who sees it stops and stares.\n"
	.string "I know that look. I've been on the\l"
	.string "other side of it my whole career.\p"
	.string "…Enough. Battle me. And don't you dare\n"
	.string "just stand there staring.$"

Nexus_Text_Elesa_ChampionDefeat:
	.string "You never stared once. You were too\n"
	.string "busy fighting. …Good.$"

Nexus_Text_Elesa_ChampionAfter:
	.string "{SPEAKER NAME_ELESA}People think being admired is the same\n"
	.string "as being loved. It isn't. It's lonelier.\p"
	.string "That creature has never been touched\n"
	.string "by anything in its life, and it thinks\l"
	.string "that's perfection.\p"
	.string "Go show it what it's missing. Get your\n"
	.string "hands dirty.$"

Nexus_Text_Beauty_Boss:
	.string "Someone was already standing at the\n"
	.string "end of the path. Perfectly still.\l"
	.string "Perfectly clean.\p"
	.string "For a moment, you forgot what you were\n"
	.string "doing there.$"

Nexus_Text_Beauty_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-02. Beauty.\p"
	.string "You described the creature, and I wrote\n"
	.string "down the word “lovely.”\p"
	.string "I have crossed it out. It is still\n"
	.string "perfectly legible. That, I think, is the\l"
	.string "whole report.$"


@ ---------------------------------------------------------------------------
@ UB-03 LIGHTING -- Xurkitree -- champion: Volkner
@ ---------------------------------------------------------------------------
Nexus_Text_Lighting_Arrival:
	.string "A city of towers and cables, under a sky\n"
	.string "with no stars.\p"
	.string "Every window was dark but one, high up,\n"
	.string "burning white. All the cables ran toward\l"
	.string "it.$"

Nexus_Text_Volkner_ChampionIntro:
	.string "See that light up there? That's it.\n"
	.string "It's been drinking this city dry, one\l"
	.string "street at a time.\p"
	.string "I'd like to say I hate it. I'm the last\n"
	.string "guy who gets to.\p"
	.string "Back home I pulled so much power into\n"
	.string "my Gym that the whole town went dark.\l"
	.string "Just so I'd have something to do.\p"
	.string "So. Show me you're the kind of spark\n"
	.string "worth all that dark.$"

Nexus_Text_Volkner_ChampionDefeat:
	.string "…Yeah. That's the kind. Worth every\n"
	.string "light in town.$"

Nexus_Text_Volkner_ChampionAfter:
	.string "{SPEAKER NAME_VOLKNER}That thing isn't cruel. It's hungry, and\n"
	.string "it found a whole city to eat.\p"
	.string "I get it. That's what scares me.\p"
	.string "Go pull the plug on it, challenger. I'll\n"
	.string "be here, learning to be bored in the\l"
	.string "dark.$"

Nexus_Text_Lighting_Boss:
	.string "Every cable in the room went taut at\n"
	.string "once.\p"
	.string "The window flickered, and something\n"
	.string "that was mostly wire stood up in the\l"
	.string "light.$"

Nexus_Text_Lighting_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-03. Lighting.\p"
	.string "The old file says the creature once\n"
	.string "emptied a power plant. Your witness\l"
	.string "says he once emptied a town, for a good\l"
	.string "battle.\p"
	.string "I find I am not sure which of the two I\n"
	.string "am filing.$"


@ ---------------------------------------------------------------------------
@ UB-04 BLASTER -- Celesteela -- champion: Steven
@ ---------------------------------------------------------------------------
Nexus_Text_Blaster_Arrival:
	.string "A crater under a sky crowded with\n"
	.string "stars.\p"
	.string "Tall steel shoots rose from the floor\n"
	.string "like bamboo, scorched black at the\l"
	.string "base, all pointing straight up.$"

Nexus_Text_Steven_ChampionIntro:
	.string "All my life, I've collected what the sky\n"
	.string "let fall. Meteorites. Shards. Small\l"
	.string "pieces of somewhere else.\p"
	.string "The creature here goes the other way.\n"
	.string "It burns a forest to lift itself off the\l"
	.string "ground, and it never comes back down.\p"
	.string "I can't decide if it's running from\n"
	.string "something, or going home.\p"
	.string "…Forgive me. You didn't come here to\n"
	.string "listen to me think. Let's battle.$"

Nexus_Text_Steven_ChampionDefeat:
	.string "Your Pokémon kept their feet on the\n"
	.string "ground the whole time. I admire that\l"
	.string "more than I can say.$"

Nexus_Text_Steven_ChampionAfter:
	.string "{SPEAKER NAME_STEVEN}If it takes off while you're near it,\n"
	.string "don't chase it. Nothing can follow\l"
	.string "something like that.\p"
	.string "Stop it before it leaves. Or let it leave.\n"
	.string "Both are answers.\p"
	.string "I'll stay a while. Something that high\n"
	.string "up might drop a stone for me, sooner or\l"
	.string "later.$"

Nexus_Text_Blaster_Boss:
	.string "The ground shook, and one of the steel\n"
	.string "shoots began to rise.\p"
	.string "It was not a tower. It had arms, and\n"
	.string "both of them were glowing.$"

Nexus_Text_Blaster_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-04. Blaster.\p"
	.string "A crater where nothing falls, and a\n"
	.string "collector of fallen stones waiting for\l"
	.string "one.\p"
	.string "I have closed this file very gently. I\n"
	.string "cannot tell you why.$"


@ ---------------------------------------------------------------------------
@ UB-04 BLADE -- Kartana -- champion: Ramos
@ ---------------------------------------------------------------------------
Nexus_Text_Blade_Arrival:
	.string "A forest of white trees, every one of\n"
	.string "them folded.\p"
	.string "Branches creased at clean angles.\n"
	.string "Leaves cut to the same shape. Nothing\l"
	.string "was growing. Everything had been\l"
	.string "trimmed.$"

Nexus_Text_Ramos_ChampionIntro:
	.string "Thirty years with these shears, sprout.\n"
	.string "Want to know the secret?\p"
	.string "You never cut to hurt the tree. You cut\n"
	.string "so it grows back stronger.\p"
	.string "The little thing in this forest cuts\n"
	.string "better than I ever could. Clean.\l"
	.string "Perfect. Through steel, even.\p"
	.string "And not once has it let anything grow\n"
	.string "back. Show me something with roots!$"

Nexus_Text_Ramos_ChampionDefeat:
	.string "Hohoho! Now that's growing, that is.\n"
	.string "Nothing here could trim that down.$"

Nexus_Text_Ramos_ChampionAfter:
	.string "{SPEAKER NAME_RAMOS}It's light enough for the wind to carry,\n"
	.string "and sharp enough to halve a mountain.\p"
	.string "Don't try to be sharper than it, sprout.\n"
	.string "You'll lose.\p"
	.string "Be something that grows back. That's\n"
	.string "the one thing a blade can never finish.$"

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
@ UB-05 GLUTTON -- Guzzlord -- champion: Guzma
@ ---------------------------------------------------------------------------
Nexus_Text_Glutton_Arrival:
	.string "A city, or what was left of one.\p"
	.string "Half the buildings were gone. Not\n"
	.string "fallen. Missing, as if bitten off.\p"
	.string "Somewhere far away, something was still\n"
	.string "chewing.$"

Nexus_Text_Guzma_ChampionIntro:
	.string "You seen it? That big mouth down the\n"
	.string "road? It ate a building while I watched.\l"
	.string "Then it ate the next one.\p"
	.string "Folks back home used to say I was\n"
	.string "destruction walkin' around on two legs.\l"
	.string "I kinda liked it.\p"
	.string "Then I watched that thing chew through\n"
	.string "a whole city and still look hungry.\p"
	.string "…It ain't fun to watch. Let's just go!$"

Nexus_Text_Guzma_ChampionDefeat:
	.string "Again. Everything I got, and it still\n"
	.string "ain't enough.$"

Nexus_Text_Guzma_ChampionAfter:
	.string "{SPEAKER NAME_GUZMA}Here's what nobody tells ya. When you\n"
	.string "wreck everything, you ain't full after.\l"
	.string "You're just standin' in a bigger mess.\p"
	.string "That thing's never gonna be full. Not\n"
	.string "ever.\p"
	.string "Kukui told me that once. About me. Took\n"
	.string "me a long time to hear it.\p"
	.string "Go on. Go show that mouth what enough\n"
	.string "looks like.$"

Nexus_Text_Glutton_Boss:
	.string "The chewing stopped.\p"
	.string "A mouth that was most of a body turned\n"
	.string "toward you, and the street in front of\l"
	.string "it was simply not there anymore.$"

Nexus_Text_Glutton_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-05. Glutton.\p"
	.string "A city eaten down to the street, and a\n"
	.string "young man sitting in it who used to\l"
	.string "think that was what strength looked\l"
	.string "like.\p"
	.string "He does not think so now. I have written\n"
	.string "that down for him, in case he ever asks.$"


@ ---------------------------------------------------------------------------
@ UB ADHESIVE -- Poipole -- champion: Zossie
@ ---------------------------------------------------------------------------
Nexus_Text_Adhesive_Arrival:
	.string "A small bright room with no corners.\p"
	.string "Soft lights floated near the ceiling.\n"
	.string "When one brushed your sleeve, it stayed\l"
	.string "there a moment before letting go.$"

Nexus_Text_Zossie_ChampionIntro:
	.string "There's a little one hiding up in the\n"
	.string "lights. It's been following me around\l"
	.string "all day!\p"
	.string "It's poisonous, you know. Its whole\n"
	.string "head is a needle. But it only sticks to\l"
	.string "people it likes.\p"
	.string "I think it likes me! …And I think it\n"
	.string "wants to see if it likes you.\p"
	.string "So let's show it a really, really good\n"
	.string "battle!$"

Nexus_Text_Zossie_ChampionDefeat:
	.string "Aww… It liked that! It liked you! I could\n"
	.string "tell!$"

Nexus_Text_Zossie_ChampionAfter:
	.string "{SPEAKER NAME_ZOSSIE}Where I'm from, it was dark for so long.\n"
	.string "We forgot what it feels like when\l"
	.string "something small and bright just… wants\l"
	.string "to be near you.\p"
	.string "It's going to come say hi. It might\n"
	.string "sting a little. That's just how it says\l"
	.string "hello!\p"
	.string "Be gentle with it, okay? Promise.$"

Nexus_Text_Adhesive_Boss:
	.string "One of the lights drifted down from the\n"
	.string "ceiling and landed in front of you.\p"
	.string "It had a face, and it was very, very\n"
	.string "curious about yours.$"

Nexus_Text_Adhesive_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Adhesive.\p"
	.string "No harm done. No damage. One very small\n"
	.string "creature that followed you all the way\l"
	.string "to the door.\p"
	.string "It is the shortest file I have. I have\n"
	.string "read it four times.$"


@ ---------------------------------------------------------------------------
@ UB STINGER -- Naganadel -- champion: Soliera
@ ---------------------------------------------------------------------------
Nexus_Text_Stinger_Arrival:
	.string "The top of a tower, far above a city of\n"
	.string "lights.\p"
	.string "The wind came from every side at once.\n"
	.string "Long straight scars were cut into the\l"
	.string "roof, all of them pointing at the same\l"
	.string "spot.$"

Nexus_Text_Soliera_ChampionIntro:
	.string "It has passed over this tower eleven\n"
	.string "times. I have counted.\p"
	.string "It is faster than anything in our\n"
	.string "records, and it carries enough venom to\l"
	.string "fell a city. Every pass comes lower.\p"
	.string "In my world, we gave a small one like it\n"
	.string "to someone who helped us. I was the one\l"
	.string "who handed it over.\p"
	.string "I never learned what it became.\n"
	.string "…Perhaps I am about to. Prepare\l"
	.string "yourself.$"

Nexus_Text_Soliera_ChampionDefeat:
	.string "My strike missed. I will not ask for a\n"
	.string "second.$"

Nexus_Text_Soliera_ChampionAfter:
	.string "{SPEAKER NAME_SOLIERA}If that is what it grew into, then\n"
	.string "someone raised it well. Or no one did.\p"
	.string "I cannot tell which from here. You will\n"
	.string "be close enough to see.\p"
	.string "Watch the needle. It points before it\n"
	.string "strikes. That is the only warning it\l"
	.string "gives.$"

Nexus_Text_Stinger_Boss:
	.string "Something passed overhead too fast to\n"
	.string "see. Then again, lower.\p"
	.string "The twelfth time, it stopped in the air\n"
	.string "in front of you, and pointed.$"

Nexus_Text_Stinger_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Stinger.\p"
	.string "You tell me it carries enough poison to\n"
	.string "fill a bathtub, and flies faster than\l"
	.string "you could follow.\p"
	.string "I have moved my desk slightly further\n"
	.string "from the window. For no reason.$"


@ ---------------------------------------------------------------------------
@ UB ASSEMBLY -- Stakataka -- champion: Byron
@ ---------------------------------------------------------------------------
Nexus_Text_Assembly_Arrival:
	.string "A quarry of grey stone, with walls in\n"
	.string "every direction.\p"
	.string "You were sure the way behind you had\n"
	.string "been open a moment ago.$"

Nexus_Text_Byron_ChampionIntro:
	.string "Youngster, I've spent my whole life\n"
	.string "cutting stone out of mountains. I know\l"
	.string "rock.\p"
	.string "That wall over there isn't rock. Every\n"
	.string "brick of it is alive. A hundred and fifty,\l"
	.string "near as I can count, each one holding up\l"
	.string "the next.\p"
	.string "My son and I can't agree on how to\n"
	.string "stack a shelf. These things built a\l"
	.string "fortress together.\p"
	.string "Hah! Let's see if you and your team\n"
	.string "hold together half as well!$"

Nexus_Text_Byron_ChampionDefeat:
	.string "Hah! Now THAT'S a team that holds! Not\n"
	.string "a crack in it!$"

Nexus_Text_Byron_ChampionAfter:
	.string "{SPEAKER NAME_BYRON}When it comes, don't hunt for the weak\n"
	.string "brick. There isn't one. They share the\l"
	.string "load.\p"
	.string "Hit the whole wall. Hit it with\n"
	.string "everything you've got, all at once.\p"
	.string "…Then maybe go home and call your\n"
	.string "family. I'm going to call mine.$"

Nexus_Text_Assembly_Boss:
	.string "The wall ahead shifted, brick by brick,\n"
	.string "and stood up on four thin legs.\p"
	.string "Every stone in it turned to look at you.$"

Nexus_Text_Assembly_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Assembly.\p"
	.string "One creature that is really a hundred\n"
	.string "and fifty, all holding each other up.\p"
	.string "I have been told it is a threat. I have\n"
	.string "filed it under threats. I keep wanting\l"
	.string "to move it.$"


@ ---------------------------------------------------------------------------
@ UB BURST -- Blacephalon -- champion: Fantina
@ ---------------------------------------------------------------------------
Nexus_Text_Burst_Arrival:
	.string "An empty theatre, every seat filled\n"
	.string "with shadow.\p"
	.string "Fireworks burst overhead without a\n"
	.string "sound. Each time one went off, the\l"
	.string "shadows in the seats grew fainter.$"

Nexus_Text_Fantina_ChampionIntro:
	.string "Ah, you have met the star of this\n"
	.string "theatre? Such charm! Such timing!\p"
	.string "It dances badly on purpose, so you\n"
	.string "laugh. When you laugh, you lean in. And\l"
	.string "when you lean in… boum.\p"
	.string "Then it takes the life right out of its\n"
	.string "audience, and bows.\p"
	.string "I also take a crowd's breath away, mon\n"
	.string "ami. But I give it back! Come -- let me\l"
	.string "show you how a real show ends!$"

Nexus_Text_Fantina_ChampionDefeat:
	.string "Bravo! You watched the whole show and\n"
	.string "never lost yourself.$"

Nexus_Text_Fantina_ChampionAfter:
	.string "{SPEAKER NAME_FANTINA}A good performer gives everything, and\n"
	.string "the audience goes home with more than\l"
	.string "it brought.\p"
	.string "That one takes, and takes, and calls it\n"
	.string "applause.\p"
	.string "When it bows to you, do not clap. Do not\n"
	.string "lean in. Just end the show.$"

Nexus_Text_Burst_Boss:
	.string "The curtain rose on an empty stage.\p"
	.string "Something walked out with a strange,\n"
	.string "careless step. It bowed deeply, and its\l"
	.string "head began to glow.$"

Nexus_Text_Burst_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Burst.\p"
	.string "A performer who charms its audience,\n"
	.string "blows its own head off, and takes their\l"
	.string "strength while they clap.\p"
	.string "I have been to theatre like that. I did\n"
	.string "not know it was a species.$"


@ ===========================================================================
@ GENERIC -- the same trainers in rooms 1-4 (any fragment)
@ ===========================================================================
Nexus_Text_Colress_Intro:
	.string "Ah! A test subject. Forgive me -- a\n"
	.string "challenger.\p"
	.string "I don't remember how I arrived here,\n"
	.string "and I find I don't mind. A new place is\l"
	.string "only a new set of conditions.\p"
	.string "My question is the same one I always\n"
	.string "ask: what draws out a Pokémon's true\l"
	.string "strength? Let's collect another\l"
	.string "answer!$"

Nexus_Text_Colress_Defeat:
	.string "Remarkable. I am going to need a larger\n"
	.string "notebook.$"

Nexus_Text_Bruno_Intro:
	.string "I woke in a strange place, so I did what\n"
	.string "I always do. I trained until the sun\l"
	.string "came up.\p"
	.string "There is no sun here. So I am still\n"
	.string "training.\p"
	.string "You will make a fine partner. Brace\n"
	.string "yourself!$"

Nexus_Text_Bruno_Defeat:
	.string "Hoo hah! A good blow. I will remember it\n"
	.string "in my training.$"

Nexus_Text_Elesa_Intro:
	.string "No stage, no lights, no audience. This is\n"
	.string "the strangest runway I've ever walked.\p"
	.string "Well. I never stop in the middle of a\n"
	.string "show.\p"
	.string "You'll have to be my audience -- and my\n"
	.string "opponent. Try to keep up!$"

Nexus_Text_Elesa_Defeat:
	.string "You made me forget my pose. Nobody\n"
	.string "does that.$"

Nexus_Text_Volkner_Intro:
	.string "Huh. A challenger. Out here, of all\n"
	.string "places.\p"
	.string "I've been bored so long I stopped\n"
	.string "noticing where I was.\p"
	.string "Go on. Give me a reason to pay\n"
	.string "attention.$"

Nexus_Text_Volkner_Defeat:
	.string "Ha… That's more like it. Now I'm awake.$"

Nexus_Text_Steven_Intro:
	.string "Oh -- hello. I was looking at the stones\n"
	.string "here. They're nothing like the ones\l"
	.string "back home.\p"
	.string "Every stone has a history, and so does\n"
	.string "every Trainer. I'd like to know yours.\p"
	.string "Shall we?$"

Nexus_Text_Steven_Defeat:
	.string "A fine battle. I'll keep it the way I\n"
	.string "keep a rare stone.$"

Nexus_Text_Ramos_Intro:
	.string "Hoho! Now where has this old gardener\n"
	.string "wandered off to?\p"
	.string "Never mind, never mind. Wherever\n"
	.string "there's ground, something can grow. And\l"
	.string "wherever something grows, there's a\l"
	.string "sprout to test.\p"
	.string "Let's see how deep your roots go!$"

Nexus_Text_Ramos_Defeat:
	.string "Hohoho! Deep roots, sprout. Deep roots.$"

Nexus_Text_Guzma_Intro:
	.string "You lost, kid? Yeah. Me too.\p"
	.string "Don't matter where I end up. Wherever\n"
	.string "Guzma goes, stuff gets broken.\p"
	.string "Might as well start with you!$"

Nexus_Text_Guzma_Defeat:
	.string "…Tch. Figures. Even here, huh.$"

Nexus_Text_Zossie_Intro:
	.string "Hiii! Wait, where am I? It's not dark, so\n"
	.string "it's definitely not home!\p"
	.string "You're a Trainer, right? Battle me!\n"
	.string "Please please please!$"

Nexus_Text_Zossie_Defeat:
	.string "Aww! You're really good! Can we be\n"
	.string "friends now? That's how it works,\l"
	.string "right?$"

Nexus_Text_Soliera_Intro:
	.string "Identify yourself. …No matter.\p"
	.string "I do not know how I arrived here. My\n"
	.string "orders have not changed.\p"
	.string "Obstacles are removed. Prepare\n"
	.string "yourself.$"

Nexus_Text_Soliera_Defeat:
	.string "Understood. Obstacle not removed.\n"
	.string "Adjusting.$"

Nexus_Text_Byron_Intro:
	.string "Hah! No idea how I ended up here, but\n"
	.string "there's stone under my boots, so I'm\l"
	.string "not complaining!\p"
	.string "I'm a miner, youngster. Hard rock, hard\n"
	.string "steel, hard battles.\p"
	.string "Let's see what you're made of!$"

Nexus_Text_Byron_Defeat:
	.string "Hah! Solid! You'd make a fine miner.$"

Nexus_Text_Fantina_Intro:
	.string "Bonjour! Ah, a new stage, a new\n"
	.string "audience!\p"
	.string "I do not know this place, but it does\n"
	.string "not matter. Wherever I am, I dance.\p"
	.string "Allez! Let us make this battle\n"
	.string "beautiful!$"

Nexus_Text_Fantina_Defeat:
	.string "Magnifique! You danced better than me!\n"
	.string "…Non, I will not say that twice.$"
