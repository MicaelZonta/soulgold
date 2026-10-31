@ Nexus (Rift Missions, post-Necrozma loop). Rules: .claude/rift_missions/nexus/NEXUS_REGRAS.md
@ Dialogue and teams come from the trainer sheets in .claude/rift_missions/nexus/.
@
@ Each trainer has two fights (R16): Nexus_EventScript_<Name>_Fight, the generic
@ lines for the four rooms, and Nexus_EventScript_<Name>_ChampionFight, the lines
@ about the legendary. Both are called with `call`. Losing costs nothing (R3):
@ B_FLAG_NO_WHITEOUT keeps the script running, and the result is left in
@ VAR_TEMP_3 (B_OUTCOME_*) for the caller. The trainer flag is cleared before and
@ after, so the fight can repeat any number of times (R7); the Nexus remembers
@ progress in its own var (R15), never in the trainer flag.

	.macro nexus_fight trainer:req, intro_text:req, defeat_text:req
	msgbox \intro_text, MSGBOX_DEFAULT
	closemessage
	cleartrainerflag \trainer
	@ Set before / cleared after, unconditionally. Nothing else inside the
	@ Nexus keeps B_FLAG_NO_WHITEOUT held between fights (the boss script
	@ sets it again for itself), and the old "save and restore" here read
	@ VAR_RESULT after checkflag - which writes the comparison result, not
	@ VAR_RESULT - so a stale TRUE could leak the flag to the whole game.
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro \trainer, \defeat_text
	clearflag B_FLAG_NO_WHITEOUT
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT
	cleartrainerflag \trainer
	.endm

Nexus_EventScript_Colress_Fight::
	nexus_fight TRAINER_NEXUS_COLRESS, Nexus_Text_Colress_Intro, Nexus_Text_Colress_Defeat
	return

Nexus_EventScript_Colress_ChampionFight::
	nexus_fight TRAINER_NEXUS_COLRESS, Nexus_Text_Colress_ChampionIntro, Nexus_Text_Colress_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Colress_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bruno_Fight::
	nexus_fight TRAINER_NEXUS_BRUNO, Nexus_Text_Bruno_Intro, Nexus_Text_Bruno_Defeat
	return

Nexus_EventScript_Bruno_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRUNO, Nexus_Text_Bruno_ChampionIntro, Nexus_Text_Bruno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bruno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Elesa_Fight::
	nexus_fight TRAINER_NEXUS_ELESA, Nexus_Text_Elesa_Intro, Nexus_Text_Elesa_Defeat
	return

Nexus_EventScript_Elesa_ChampionFight::
	nexus_fight TRAINER_NEXUS_ELESA, Nexus_Text_Elesa_ChampionIntro, Nexus_Text_Elesa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Elesa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Volkner_Fight::
	nexus_fight TRAINER_NEXUS_VOLKNER, Nexus_Text_Volkner_Intro, Nexus_Text_Volkner_Defeat
	return

Nexus_EventScript_Volkner_ChampionFight::
	nexus_fight TRAINER_NEXUS_VOLKNER, Nexus_Text_Volkner_ChampionIntro, Nexus_Text_Volkner_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Volkner_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Steven_Fight::
	nexus_fight TRAINER_NEXUS_STEVEN, Nexus_Text_Steven_Intro, Nexus_Text_Steven_Defeat
	return

Nexus_EventScript_Steven_ChampionFight::
	nexus_fight TRAINER_NEXUS_STEVEN, Nexus_Text_Steven_ChampionIntro, Nexus_Text_Steven_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Steven_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ramos_Fight::
	nexus_fight TRAINER_NEXUS_RAMOS, Nexus_Text_Ramos_Intro, Nexus_Text_Ramos_Defeat
	return

Nexus_EventScript_Ramos_ChampionFight::
	nexus_fight TRAINER_NEXUS_RAMOS, Nexus_Text_Ramos_ChampionIntro, Nexus_Text_Ramos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ramos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Guzma_Fight::
	nexus_fight TRAINER_NEXUS_GUZMA, Nexus_Text_Guzma_Intro, Nexus_Text_Guzma_Defeat
	return

Nexus_EventScript_Guzma_ChampionFight::
	nexus_fight TRAINER_NEXUS_GUZMA, Nexus_Text_Guzma_ChampionIntro, Nexus_Text_Guzma_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Guzma_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Soliera_Fight::
	nexus_fight TRAINER_NEXUS_SOLIERA, Nexus_Text_Soliera_Intro, Nexus_Text_Soliera_Defeat
	return

Nexus_EventScript_Soliera_ChampionFight::
	nexus_fight TRAINER_NEXUS_SOLIERA, Nexus_Text_Soliera_ChampionIntro, Nexus_Text_Soliera_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Soliera_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Byron_Fight::
	nexus_fight TRAINER_NEXUS_BYRON, Nexus_Text_Byron_Intro, Nexus_Text_Byron_Defeat
	return

Nexus_EventScript_Byron_ChampionFight::
	nexus_fight TRAINER_NEXUS_BYRON, Nexus_Text_Byron_ChampionIntro, Nexus_Text_Byron_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Byron_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Fantina_Fight::
	nexus_fight TRAINER_NEXUS_FANTINA, Nexus_Text_Fantina_Intro, Nexus_Text_Fantina_Defeat
	return

Nexus_EventScript_Fantina_ChampionFight::
	nexus_fight TRAINER_NEXUS_FANTINA, Nexus_Text_Fantina_ChampionIntro, Nexus_Text_Fantina_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Fantina_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Return::
	return

@ R18: the Looker Files. A notebook lies open on the floor of the champion
@ room on the days of its legendary (src/data/nexus/legendaries.h,
@ .lookerFileScript), run by Nexus_CallLookerFileScript. Looker never set
@ foot in the Nexus; the notebook is here anyway, in his handwriting, the ink
@ still wet and the page dated a day that has not come. It describes the
@ universe the legendary of the day comes from. Written text: no plate.
Nexus_EventScript_Symbiont_LookerFile::
	msgbox Nexus_Text_Symbiont_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Absorption_LookerFile::
	msgbox Nexus_Text_Absorption_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Beauty_LookerFile::
	msgbox Nexus_Text_Beauty_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Lighting_LookerFile::
	msgbox Nexus_Text_Lighting_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Blaster_LookerFile::
	msgbox Nexus_Text_Blaster_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Blade_LookerFile::
	msgbox Nexus_Text_Blade_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Glutton_LookerFile::
	msgbox Nexus_Text_Glutton_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Stinger_LookerFile::
	msgbox Nexus_Text_Stinger_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Assembly_LookerFile::
	msgbox Nexus_Text_Assembly_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Burst_LookerFile::
	msgbox Nexus_Text_Burst_LookerFile, MSGBOX_DEFAULT
	return

Nexus_Text_Colress_Intro:
	.string "{SPEAKER NAME_COLRESS}Ah! A test subject. Forgive me -- a\n"
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

Nexus_Text_Colress_ChampionIntro:
	.string "{SPEAKER NAME_COLRESS}You feel it too, don't you? Something in\n"
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

Nexus_Text_Bruno_Intro:
	.string "{SPEAKER NAME_BRUNO}I woke in a strange place, so I did what\n"
	.string "I always do. I trained until the sun\l"
	.string "came up.\p"
	.string "There is no sun here. So I am still\n"
	.string "training.\p"
	.string "You will make a fine partner. Brace\n"
	.string "yourself!$"

Nexus_Text_Bruno_Defeat:
	.string "Hoo hah! A good blow. I will remember it\n"
	.string "in my training.$"

Nexus_Text_Bruno_ChampionIntro:
	.string "{SPEAKER NAME_BRUNO}I have watched it for three days. It\n"
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

Nexus_Text_Elesa_Intro:
	.string "{SPEAKER NAME_ELESA}No stage, no lights, no audience. This is\n"
	.string "the strangest runway I've ever walked.\p"
	.string "Well. I never stop in the middle of a\n"
	.string "show.\p"
	.string "You'll have to be my audience -- and my\n"
	.string "opponent. Try to keep up!$"

Nexus_Text_Elesa_Defeat:
	.string "You made me forget my pose. Nobody\n"
	.string "does that.$"

Nexus_Text_Elesa_ChampionIntro:
	.string "{SPEAKER NAME_ELESA}I've seen it. From a distance -- it\n"
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

Nexus_Text_Volkner_Intro:
	.string "{SPEAKER NAME_VOLKNER}Huh. A challenger. Out here, of all\n"
	.string "places.\p"
	.string "I've been bored so long I stopped\n"
	.string "noticing where I was.\p"
	.string "Go on. Give me a reason to pay\n"
	.string "attention.$"

Nexus_Text_Volkner_Defeat:
	.string "Ha… That's more like it. Now I'm awake.$"

Nexus_Text_Volkner_ChampionIntro:
	.string "{SPEAKER NAME_VOLKNER}See that light up there? That's it.\n"
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

Nexus_Text_Steven_Intro:
	.string "{SPEAKER NAME_STEVEN}Oh -- hello. I was looking at the stones\n"
	.string "here. They're nothing like the ones\l"
	.string "back home.\p"
	.string "Every stone has a history, and so does\n"
	.string "every Trainer. I'd like to know yours.\p"
	.string "Shall we?$"

Nexus_Text_Steven_Defeat:
	.string "A fine battle. I'll keep it the way I\n"
	.string "keep a rare stone.$"

Nexus_Text_Steven_ChampionIntro:
	.string "{SPEAKER NAME_STEVEN}All my life, I've collected what the sky\n"
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

Nexus_Text_Ramos_Intro:
	.string "{SPEAKER NAME_RAMOS}Hoho! Now where has this old gardener\n"
	.string "wandered off to?\p"
	.string "Never mind, never mind. Wherever\n"
	.string "there's ground, something can grow. And\l"
	.string "wherever something grows, there's a\l"
	.string "sprout to test.\p"
	.string "Let's see how deep your roots go!$"

Nexus_Text_Ramos_Defeat:
	.string "Hohoho! Deep roots, sprout. Deep roots.$"

Nexus_Text_Ramos_ChampionIntro:
	.string "{SPEAKER NAME_RAMOS}Thirty years with these shears, sprout.\n"
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

Nexus_Text_Guzma_Intro:
	.string "{SPEAKER NAME_GUZMA}You lost, kid? Yeah. Me too.\p"
	.string "Don't matter where I end up. Wherever\n"
	.string "Guzma goes, stuff gets broken.\p"
	.string "Might as well start with you!$"

Nexus_Text_Guzma_Defeat:
	.string "…Tch. Figures. Even here, huh.$"

Nexus_Text_Guzma_ChampionIntro:
	.string "{SPEAKER NAME_GUZMA}You seen it? That big mouth down the\n"
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

Nexus_Text_Soliera_Intro:
	.string "{SPEAKER NAME_SOLIERA}Identify yourself. …No matter.\p"
	.string "I do not know how I arrived here. My\n"
	.string "orders have not changed.\p"
	.string "Obstacles are removed. Prepare\n"
	.string "yourself.$"

Nexus_Text_Soliera_Defeat:
	.string "Understood. Obstacle not removed.\n"
	.string "Adjusting.$"

Nexus_Text_Soliera_ChampionIntro:
	.string "{SPEAKER NAME_SOLIERA}It has passed over this tower eleven\n"
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

Nexus_Text_Byron_Intro:
	.string "{SPEAKER NAME_BYRON}Hah! No idea how I ended up here, but\n"
	.string "there's stone under my boots, so I'm\l"
	.string "not complaining!\p"
	.string "I'm a miner, youngster. Hard rock, hard\n"
	.string "steel, hard battles.\p"
	.string "Let's see what you're made of!$"

Nexus_Text_Byron_Defeat:
	.string "Hah! Solid! You'd make a fine miner.$"

Nexus_Text_Byron_ChampionIntro:
	.string "{SPEAKER NAME_BYRON}Youngster, I've spent my whole life\n"
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

Nexus_Text_Fantina_Intro:
	.string "{SPEAKER NAME_FANTINA}Bonjour! Ah, a new stage, a new\n"
	.string "audience!\p"
	.string "I do not know this place, but it does\n"
	.string "not matter. Wherever I am, I dance.\p"
	.string "Allez! Let us make this battle\n"
	.string "beautiful!$"

Nexus_Text_Fantina_Defeat:
	.string "Magnifique! You danced better than me!\n"
	.string "…Non, I will not say that twice.$"

Nexus_Text_Fantina_ChampionIntro:
	.string "{SPEAKER NAME_FANTINA}Ah, you have met the star of this\n"
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

@ ---------------------------------------------------------------------------
@ R18: the Looker Files (one page per legendary, the universe it comes from)
@ ---------------------------------------------------------------------------
Nexus_Text_Symbiont_LookerFile:
	.string "File UB-01. Symbiont.\p"
	.string "Deep water that does not drown you.\n"
	.string "Pale lights drift through it, trailing\l"
	.string "long threads.\p"
	.string "Where one touches the glass floor, the\n"
	.string "glass shines brighter -- and cracks.\p"
	.string "A scientist keeps its door. He does\n"
	.string "not remember arriving. He asks that\l"
	.string "you refuse what it offers.\p"
	.string "I have underlined that.\n"
	.string "I do not remember writing it.$"

Nexus_Text_Absorption_LookerFile:
	.string "File UB-02. Absorption.\p"
	.string "Heat, the moment you arrive. Leaves\n"
	.string "larger than doors, roots as thick as\l"
	.string "pillars. Everything grew too big.\p"
	.string "And everything is exhausted. The\n"
	.string "strength of this place was taken\l"
	.string "from someone else.\p"
	.string "The man at its door built his own\n"
	.string "strength, one day at a time. He will\l"
	.string "not call this strength.\p"
	.string "“Look at the legs,” it says here,\n"
	.string "in my hand. I have never met him.$"

Nexus_Text_Beauty_LookerFile:
	.string "File UB-02. Beauty.\p"
	.string "White sand, and a straight white path\n"
	.string "across it, lit from below.\p"
	.string "Nothing leaves a mark. Look back, and\n"
	.string "your own footprints are already gone.\p"
	.string "A model walks the path as if it were a\n"
	.string "runway. There is no audience. She has\l"
	.string "not stopped once.\p"
	.string "I wrote the word “lovely,” and crossed\n"
	.string "it out. It is still perfectly legible.$"

Nexus_Text_Lighting_LookerFile:
	.string "File UB-03. Lighting.\p"
	.string "A city of towers and cables under a\n"
	.string "sky with no stars.\p"
	.string "Every window is dark but one, high up,\n"
	.string "burning white. Every cable runs to it.\p"
	.string "The man at its door once darkened a\n"
	.string "whole town for one good battle.\p"
	.string "I am no longer sure which of the two\n"
	.string "of them this page is about.$"

Nexus_Text_Blaster_LookerFile:
	.string "File UB-04. Blaster.\p"
	.string "A crater under a sky crowded with\n"
	.string "stars. Steel shoots as tall as bamboo,\l"
	.string "scorched black at the root.\p"
	.string "Every one of them points up.\p"
	.string "Nothing ever falls here. A collector\n"
	.string "of fallen stones stands at the edge\l"
	.string "anyway, waiting for one.\p"
	.string "I closed this file very gently.\n"
	.string "I cannot say why.$"

Nexus_Text_Blade_LookerFile:
	.string "File UB-04. Blade.\p"
	.string "A forest of white trees, every one of\n"
	.string "them folded. Branches creased at clean\l"
	.string "angles. Leaves cut to a single shape.\p"
	.string "Nothing grows here. Everything has\n"
	.string "been pruned.\p"
	.string "The old gardener at its door says a\n"
	.string "garden that stops growing is no longer\l"
	.string "a garden.\p"
	.string "I have put a paperweight on this page.\n"
	.string "It seemed only sensible.$"

Nexus_Text_Glutton_LookerFile:
	.string "File UB-05. Glutton.\p"
	.string "A city, or what is left of one. Half\n"
	.string "the buildings did not fall. They are\l"
	.string "simply gone, as if bitten.\p"
	.string "Somewhere far off, something is still\n"
	.string "chewing.\p"
	.string "A young man sits at its door. He once\n"
	.string "thought this was what strength looked\l"
	.string "like. He does not anymore.\p"
	.string "I wrote that down for him,\n"
	.string "in case he ever asks.$"

Nexus_Text_Stinger_LookerFile:
	.string "File UB. Stinger.\p"
	.string "The top of a tower, far above a city\n"
	.string "of lights. Wind from every side.\p"
	.string "Long, straight scratches cut into the\n"
	.string "roof, all pointing at the same spot.\p"
	.string "Something here flies faster than you\n"
	.string "can follow, and carries enough poison\l"
	.string "to fill a bathtub.\p"
	.string "The one at its door came through the\n"
	.string "rifts herself. She is not afraid of it.\p"
	.string "I have moved my desk away from the\n"
	.string "window. I do not own a desk.$"

Nexus_Text_Assembly_LookerFile:
	.string "File UB. Assembly.\p"
	.string "A quarry of grey stone, with walls in\n"
	.string "every direction.\p"
	.string "The way behind you was open a moment\n"
	.string "ago. You are certain of it.\p"
	.string "One creature that is really a hundred\n"
	.string "and fifty, all holding each other up.\p"
	.string "A miner who trusts stone keeps its\n"
	.string "door. I filed it under threats.\l"
	.string "I keep wanting to move it.$"

Nexus_Text_Burst_LookerFile:
	.string "File UB. Burst.\p"
	.string "An empty theater, every seat taken\n"
	.string "by a shadow.\p"
	.string "Fireworks burst overhead without a\n"
	.string "sound. With each one, the shadows in\l"
	.string "the seats grow a little fainter.\p"
	.string "The one at its door is a performer too.\n"
	.string "She is still smiling.\p"
	.string "I have been to theater like this.\n"
	.string "I did not know it was a species.$"

@ New trainers (58), added from the sheets in .claude/rift_missions/nexus/.
Nexus_EventScript_Red_Fight::
	nexus_fight TRAINER_NEXUS_RED, Nexus_Text_Red_Intro, Nexus_Text_Red_Defeat
	return

Nexus_EventScript_Blue_Fight::
	nexus_fight TRAINER_NEXUS_BLUE, Nexus_Text_Blue_Intro, Nexus_Text_Blue_Defeat
	return

Nexus_EventScript_Brock_Fight::
	nexus_fight TRAINER_NEXUS_BROCK, Nexus_Text_Brock_Intro, Nexus_Text_Brock_Defeat
	return

Nexus_EventScript_Misty_Fight::
	nexus_fight TRAINER_NEXUS_MISTY, Nexus_Text_Misty_Intro, Nexus_Text_Misty_Defeat
	return

Nexus_EventScript_LtSurge_Fight::
	nexus_fight TRAINER_NEXUS_LT_SURGE, Nexus_Text_LtSurge_Intro, Nexus_Text_LtSurge_Defeat
	return

Nexus_EventScript_Erika_Fight::
	nexus_fight TRAINER_NEXUS_ERIKA, Nexus_Text_Erika_Intro, Nexus_Text_Erika_Defeat
	return

Nexus_EventScript_Koga_Fight::
	nexus_fight TRAINER_NEXUS_KOGA, Nexus_Text_Koga_Intro, Nexus_Text_Koga_Defeat
	return

Nexus_EventScript_Sabrina_Fight::
	nexus_fight TRAINER_NEXUS_SABRINA, Nexus_Text_Sabrina_Intro, Nexus_Text_Sabrina_Defeat
	return

Nexus_EventScript_Blaine_Fight::
	nexus_fight TRAINER_NEXUS_BLAINE, Nexus_Text_Blaine_Intro, Nexus_Text_Blaine_Defeat
	return

Nexus_EventScript_Giovanni_Fight::
	nexus_fight TRAINER_NEXUS_GIOVANNI, Nexus_Text_Giovanni_Intro, Nexus_Text_Giovanni_Defeat
	return

Nexus_EventScript_Lance_Fight::
	nexus_fight TRAINER_NEXUS_LANCE, Nexus_Text_Lance_Intro, Nexus_Text_Lance_Defeat
	return

Nexus_EventScript_Archer_Fight::
	nexus_fight TRAINER_NEXUS_ARCHER, Nexus_Text_Archer_Intro, Nexus_Text_Archer_Defeat
	return

Nexus_EventScript_Ariana_Fight::
	nexus_fight TRAINER_NEXUS_ARIANA, Nexus_Text_Ariana_Intro, Nexus_Text_Ariana_Defeat
	return

Nexus_EventScript_Proton_Fight::
	nexus_fight TRAINER_NEXUS_PROTON, Nexus_Text_Proton_Intro, Nexus_Text_Proton_Defeat
	return

Nexus_EventScript_Petrel_Fight::
	nexus_fight TRAINER_NEXUS_PETREL, Nexus_Text_Petrel_Intro, Nexus_Text_Petrel_Defeat
	return

Nexus_EventScript_Silver_Fight::
	nexus_fight TRAINER_NEXUS_SILVER, Nexus_Text_Silver_Intro, Nexus_Text_Silver_Defeat
	return

Nexus_EventScript_Falkner_Fight::
	nexus_fight TRAINER_NEXUS_FALKNER, Nexus_Text_Falkner_Intro, Nexus_Text_Falkner_Defeat
	return

Nexus_EventScript_Bugsy_Fight::
	nexus_fight TRAINER_NEXUS_BUGSY, Nexus_Text_Bugsy_Intro, Nexus_Text_Bugsy_Defeat
	return

Nexus_EventScript_Whitney_Fight::
	nexus_fight TRAINER_NEXUS_WHITNEY, Nexus_Text_Whitney_Intro, Nexus_Text_Whitney_Defeat
	return

Nexus_EventScript_Morty_Fight::
	nexus_fight TRAINER_NEXUS_MORTY, Nexus_Text_Morty_Intro, Nexus_Text_Morty_Defeat
	return

Nexus_EventScript_Chuck_Fight::
	nexus_fight TRAINER_NEXUS_CHUCK, Nexus_Text_Chuck_Intro, Nexus_Text_Chuck_Defeat
	return

Nexus_EventScript_Jasmine_Fight::
	nexus_fight TRAINER_NEXUS_JASMINE, Nexus_Text_Jasmine_Intro, Nexus_Text_Jasmine_Defeat
	return

Nexus_EventScript_Pryce_Fight::
	nexus_fight TRAINER_NEXUS_PRYCE, Nexus_Text_Pryce_Intro, Nexus_Text_Pryce_Defeat
	return

Nexus_EventScript_Clair_Fight::
	nexus_fight TRAINER_NEXUS_CLAIR, Nexus_Text_Clair_Intro, Nexus_Text_Clair_Defeat
	return

Nexus_EventScript_Will_Fight::
	nexus_fight TRAINER_NEXUS_WILL, Nexus_Text_Will_Intro, Nexus_Text_Will_Defeat
	return

Nexus_EventScript_Karen_Fight::
	nexus_fight TRAINER_NEXUS_KAREN, Nexus_Text_Karen_Intro, Nexus_Text_Karen_Defeat
	return

Nexus_EventScript_Eusine_Fight::
	nexus_fight TRAINER_NEXUS_EUSINE, Nexus_Text_Eusine_Intro, Nexus_Text_Eusine_Defeat
	return

Nexus_EventScript_Brendan_Fight::
	nexus_fight TRAINER_NEXUS_BRENDAN, Nexus_Text_Brendan_Intro, Nexus_Text_Brendan_Defeat
	return

Nexus_EventScript_May_Fight::
	nexus_fight TRAINER_NEXUS_MAY, Nexus_Text_May_Intro, Nexus_Text_May_Defeat
	return

Nexus_EventScript_Wally_Fight::
	nexus_fight TRAINER_NEXUS_WALLY, Nexus_Text_Wally_Intro, Nexus_Text_Wally_Defeat
	return

Nexus_EventScript_Roxanne_Fight::
	nexus_fight TRAINER_NEXUS_ROXANNE, Nexus_Text_Roxanne_Intro, Nexus_Text_Roxanne_Defeat
	return

Nexus_EventScript_Brawly_Fight::
	nexus_fight TRAINER_NEXUS_BRAWLY, Nexus_Text_Brawly_Intro, Nexus_Text_Brawly_Defeat
	return

Nexus_EventScript_Wattson_Fight::
	nexus_fight TRAINER_NEXUS_WATTSON, Nexus_Text_Wattson_Intro, Nexus_Text_Wattson_Defeat
	return

Nexus_EventScript_Flannery_Fight::
	nexus_fight TRAINER_NEXUS_FLANNERY, Nexus_Text_Flannery_Intro, Nexus_Text_Flannery_Defeat
	return

Nexus_EventScript_Norman_Fight::
	nexus_fight TRAINER_NEXUS_NORMAN, Nexus_Text_Norman_Intro, Nexus_Text_Norman_Defeat
	return

Nexus_EventScript_Winona_Fight::
	nexus_fight TRAINER_NEXUS_WINONA, Nexus_Text_Winona_Intro, Nexus_Text_Winona_Defeat
	return

Nexus_EventScript_TateAndLiza_Fight::
	nexus_fight TRAINER_NEXUS_TATE_AND_LIZA, Nexus_Text_TateAndLiza_Intro, Nexus_Text_TateAndLiza_Defeat
	return

Nexus_EventScript_Wallace_Fight::
	nexus_fight TRAINER_NEXUS_WALLACE, Nexus_Text_Wallace_Intro, Nexus_Text_Wallace_Defeat
	return

Nexus_EventScript_Juan_Fight::
	nexus_fight TRAINER_NEXUS_JUAN, Nexus_Text_Juan_Intro, Nexus_Text_Juan_Defeat
	return

Nexus_EventScript_Sidney_Fight::
	nexus_fight TRAINER_NEXUS_SIDNEY, Nexus_Text_Sidney_Intro, Nexus_Text_Sidney_Defeat
	return

Nexus_EventScript_Phoebe_Fight::
	nexus_fight TRAINER_NEXUS_PHOEBE, Nexus_Text_Phoebe_Intro, Nexus_Text_Phoebe_Defeat
	return

Nexus_EventScript_Glacia_Fight::
	nexus_fight TRAINER_NEXUS_GLACIA, Nexus_Text_Glacia_Intro, Nexus_Text_Glacia_Defeat
	return

Nexus_EventScript_Drake_Fight::
	nexus_fight TRAINER_NEXUS_DRAKE, Nexus_Text_Drake_Intro, Nexus_Text_Drake_Defeat
	return

Nexus_EventScript_Noland_Fight::
	nexus_fight TRAINER_NEXUS_NOLAND, Nexus_Text_Noland_Intro, Nexus_Text_Noland_Defeat
	return

Nexus_EventScript_Greta_Fight::
	nexus_fight TRAINER_NEXUS_GRETA, Nexus_Text_Greta_Intro, Nexus_Text_Greta_Defeat
	return

Nexus_EventScript_Tucker_Fight::
	nexus_fight TRAINER_NEXUS_TUCKER, Nexus_Text_Tucker_Intro, Nexus_Text_Tucker_Defeat
	return

Nexus_EventScript_Lucy_Fight::
	nexus_fight TRAINER_NEXUS_LUCY, Nexus_Text_Lucy_Intro, Nexus_Text_Lucy_Defeat
	return

Nexus_EventScript_Spenser_Fight::
	nexus_fight TRAINER_NEXUS_SPENSER, Nexus_Text_Spenser_Intro, Nexus_Text_Spenser_Defeat
	return

Nexus_EventScript_Brandon_Fight::
	nexus_fight TRAINER_NEXUS_BRANDON, Nexus_Text_Brandon_Intro, Nexus_Text_Brandon_Defeat
	return

Nexus_EventScript_Anabel_Fight::
	nexus_fight TRAINER_NEXUS_ANABEL, Nexus_Text_Anabel_Intro, Nexus_Text_Anabel_Defeat
	return

Nexus_EventScript_Maxie_Fight::
	nexus_fight TRAINER_NEXUS_MAXIE, Nexus_Text_Maxie_Intro, Nexus_Text_Maxie_Defeat
	return

Nexus_EventScript_Archie_Fight::
	nexus_fight TRAINER_NEXUS_ARCHIE, Nexus_Text_Archie_Intro, Nexus_Text_Archie_Defeat
	return

Nexus_EventScript_Gladion_Fight::
	nexus_fight TRAINER_NEXUS_GLADION, Nexus_Text_Gladion_Intro, Nexus_Text_Gladion_Defeat
	return

Nexus_EventScript_Kukui_Fight::
	nexus_fight TRAINER_NEXUS_KUKUI, Nexus_Text_Kukui_Intro, Nexus_Text_Kukui_Defeat
	return

Nexus_EventScript_Lusamine_Fight::
	nexus_fight TRAINER_NEXUS_LUSAMINE, Nexus_Text_Lusamine_Intro, Nexus_Text_Lusamine_Defeat
	return

Nexus_EventScript_Janine_Fight::
	nexus_fight TRAINER_NEXUS_JANINE, Nexus_Text_Janine_Intro, Nexus_Text_Janine_Defeat
	return

Nexus_EventScript_Leaf_Fight::
	nexus_fight TRAINER_NEXUS_LEAF, Nexus_Text_Leaf_Intro, Nexus_Text_Leaf_Defeat
	return

Nexus_EventScript_Lillie_Fight::
	nexus_fight TRAINER_NEXUS_LILLIE, Nexus_Text_Lillie_Intro, Nexus_Text_Lillie_Defeat
	return

Nexus_EventScript_Misty_Kyogre_ChampionFight::
	nexus_fight TRAINER_NEXUS_MISTY, Nexus_Text_Misty_Kyogre_ChampionIntro, Nexus_Text_Misty_Kyogre_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Misty_Kyogre_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Archie_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARCHIE, Nexus_Text_Archie_ChampionIntro, Nexus_Text_Archie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Archie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Giovanni_Mewtwo_ChampionFight::
	nexus_fight TRAINER_NEXUS_GIOVANNI, Nexus_Text_Giovanni_Mewtwo_ChampionIntro, Nexus_Text_Giovanni_Mewtwo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Giovanni_Mewtwo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Giovanni_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_GIOVANNI, Nexus_Text_Giovanni_Genesect_ChampionIntro, Nexus_Text_Giovanni_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Giovanni_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Jasmine_Lugia_ChampionFight::
	nexus_fight TRAINER_NEXUS_JASMINE, Nexus_Text_Jasmine_Lugia_ChampionIntro, Nexus_Text_Jasmine_Lugia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Jasmine_Lugia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Morty_HoOh_ChampionFight::
	nexus_fight TRAINER_NEXUS_MORTY, Nexus_Text_Morty_HoOh_ChampionIntro, Nexus_Text_Morty_HoOh_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Morty_HoOh_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Maxie_Groudon_ChampionFight::
	nexus_fight TRAINER_NEXUS_MAXIE, Nexus_Text_Maxie_Groudon_ChampionIntro, Nexus_Text_Maxie_Groudon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Maxie_Groudon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lance_Rayquaza_ChampionFight::
	nexus_fight TRAINER_NEXUS_LANCE, Nexus_Text_Lance_Rayquaza_ChampionIntro, Nexus_Text_Lance_Rayquaza_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lance_Rayquaza_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Spenser_Dialga_ChampionFight::
	nexus_fight TRAINER_NEXUS_SPENSER, Nexus_Text_Spenser_Dialga_ChampionIntro, Nexus_Text_Spenser_Dialga_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Spenser_Dialga_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Sabrina_Palkia_ChampionFight::
	nexus_fight TRAINER_NEXUS_SABRINA, Nexus_Text_Sabrina_Palkia_ChampionIntro, Nexus_Text_Sabrina_Palkia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Sabrina_Palkia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Silver_ChampionFight::
	nexus_fight TRAINER_NEXUS_SILVER, Nexus_Text_Silver_ChampionIntro, Nexus_Text_Silver_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Silver_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Kukui_Solgaleo_ChampionFight::
	nexus_fight TRAINER_NEXUS_KUKUI, Nexus_Text_Kukui_Solgaleo_ChampionIntro, Nexus_Text_Kukui_Solgaleo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Kukui_Solgaleo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lillie_Lunala_ChampionFight::
	nexus_fight TRAINER_NEXUS_LILLIE, Nexus_Text_Lillie_Lunala_ChampionIntro, Nexus_Text_Lillie_Lunala_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lillie_Lunala_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Anabel_Necrozma_ChampionFight::
	nexus_fight TRAINER_NEXUS_ANABEL, Nexus_Text_Anabel_Necrozma_ChampionIntro, Nexus_Text_Anabel_Necrozma_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Anabel_Necrozma_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Greta_Koraidon_ChampionFight::
	nexus_fight TRAINER_NEXUS_GRETA, Nexus_Text_Greta_Koraidon_ChampionIntro, Nexus_Text_Greta_Koraidon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Greta_Koraidon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Noland_Miraidon_ChampionFight::
	nexus_fight TRAINER_NEXUS_NOLAND, Nexus_Text_Noland_Miraidon_ChampionIntro, Nexus_Text_Noland_Miraidon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Noland_Miraidon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gladion_Silvally_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLADION, Nexus_Text_Gladion_Silvally_ChampionIntro, Nexus_Text_Gladion_Silvally_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gladion_Silvally_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Petrel_Ogerpon_ChampionFight::
	nexus_fight TRAINER_NEXUS_PETREL, Nexus_Text_Petrel_Ogerpon_ChampionIntro, Nexus_Text_Petrel_Ogerpon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Petrel_Ogerpon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Pryce_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_PRYCE, Nexus_Text_Pryce_Articuno_ChampionIntro, Nexus_Text_Pryce_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Pryce_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Sabrina_GalarianArticuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_SABRINA, Nexus_Text_Sabrina_GalarianArticuno_ChampionIntro, Nexus_Text_Sabrina_GalarianArticuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Sabrina_GalarianArticuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_LtSurge_Zapdos_ChampionFight::
	nexus_fight TRAINER_NEXUS_LT_SURGE, Nexus_Text_LtSurge_Zapdos_ChampionIntro, Nexus_Text_LtSurge_Zapdos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_LtSurge_Zapdos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Winona_GalarianZapdos_ChampionFight::
	nexus_fight TRAINER_NEXUS_WINONA, Nexus_Text_Winona_GalarianZapdos_ChampionIntro, Nexus_Text_Winona_GalarianZapdos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Winona_GalarianZapdos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Blaine_Moltres_ChampionFight::
	nexus_fight TRAINER_NEXUS_BLAINE, Nexus_Text_Blaine_Moltres_ChampionIntro, Nexus_Text_Blaine_Moltres_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Blaine_Moltres_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Karen_GalarianMoltres_ChampionFight::
	nexus_fight TRAINER_NEXUS_KAREN, Nexus_Text_Karen_GalarianMoltres_ChampionIntro, Nexus_Text_Karen_GalarianMoltres_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Karen_GalarianMoltres_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Eusine_Raikou_ChampionFight::
	nexus_fight TRAINER_NEXUS_EUSINE, Nexus_Text_Eusine_Raikou_ChampionIntro, Nexus_Text_Eusine_Raikou_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Eusine_Raikou_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Eusine_Entei_ChampionFight::
	nexus_fight TRAINER_NEXUS_EUSINE, Nexus_Text_Eusine_Entei_ChampionIntro, Nexus_Text_Eusine_Entei_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Eusine_Entei_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Eusine_Suicune_ChampionFight::
	nexus_fight TRAINER_NEXUS_EUSINE, Nexus_Text_Eusine_Suicune_ChampionIntro, Nexus_Text_Eusine_Suicune_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Eusine_Suicune_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brandon_Regirock_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRANDON, Nexus_Text_Brandon_Regirock_ChampionIntro, Nexus_Text_Brandon_Regirock_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brandon_Regirock_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brandon_Regice_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRANDON, Nexus_Text_Brandon_Regice_ChampionIntro, Nexus_Text_Brandon_Regice_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brandon_Regice_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brandon_Registeel_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRANDON, Nexus_Text_Brandon_Registeel_ChampionIntro, Nexus_Text_Brandon_Registeel_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brandon_Registeel_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_TateAndLiza_Latias_ChampionFight::
	nexus_fight TRAINER_NEXUS_TATE_AND_LIZA, Nexus_Text_TateAndLiza_Latias_ChampionIntro, Nexus_Text_TateAndLiza_Latias_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_TateAndLiza_Latias_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_TateAndLiza_Latios_ChampionFight::
	nexus_fight TRAINER_NEXUS_TATE_AND_LIZA, Nexus_Text_TateAndLiza_Latios_ChampionIntro, Nexus_Text_TateAndLiza_Latios_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_TateAndLiza_Latios_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Roxanne_Uxie_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROXANNE, Nexus_Text_Roxanne_Uxie_ChampionIntro, Nexus_Text_Roxanne_Uxie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Roxanne_Uxie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_May_Mesprit_ChampionFight::
	nexus_fight TRAINER_NEXUS_MAY, Nexus_Text_May_Mesprit_ChampionIntro, Nexus_Text_May_Mesprit_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_May_Mesprit_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wally_Azelf_ChampionFight::
	nexus_fight TRAINER_NEXUS_WALLY, Nexus_Text_Wally_Azelf_ChampionIntro, Nexus_Text_Wally_Azelf_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wally_Azelf_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Flannery_Heatran_ChampionFight::
	nexus_fight TRAINER_NEXUS_FLANNERY, Nexus_Text_Flannery_Heatran_ChampionIntro, Nexus_Text_Flannery_Heatran_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Flannery_Heatran_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Whitney_Regigigas_ChampionFight::
	nexus_fight TRAINER_NEXUS_WHITNEY, Nexus_Text_Whitney_Regigigas_ChampionIntro, Nexus_Text_Whitney_Regigigas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Whitney_Regigigas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ariana_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARIANA, Nexus_Text_Ariana_ChampionIntro, Nexus_Text_Ariana_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ariana_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Chuck_Cobalion_ChampionFight::
	nexus_fight TRAINER_NEXUS_CHUCK, Nexus_Text_Chuck_Cobalion_ChampionIntro, Nexus_Text_Chuck_Cobalion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Chuck_Cobalion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brock_Terrakion_ChampionFight::
	nexus_fight TRAINER_NEXUS_BROCK, Nexus_Text_Brock_Terrakion_ChampionIntro, Nexus_Text_Brock_Terrakion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brock_Terrakion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Erika_Virizion_ChampionFight::
	nexus_fight TRAINER_NEXUS_ERIKA, Nexus_Text_Erika_Virizion_ChampionIntro, Nexus_Text_Erika_Virizion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Erika_Virizion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Falkner_ChampionFight::
	nexus_fight TRAINER_NEXUS_FALKNER, Nexus_Text_Falkner_ChampionIntro, Nexus_Text_Falkner_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Falkner_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Winona_Thundurus_ChampionFight::
	nexus_fight TRAINER_NEXUS_WINONA, Nexus_Text_Winona_Thundurus_ChampionIntro, Nexus_Text_Winona_Thundurus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Winona_Thundurus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Maxie_Landorus_ChampionFight::
	nexus_fight TRAINER_NEXUS_MAXIE, Nexus_Text_Maxie_Landorus_ChampionIntro, Nexus_Text_Maxie_Landorus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Maxie_Landorus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Kukui_TapuKoko_ChampionFight::
	nexus_fight TRAINER_NEXUS_KUKUI, Nexus_Text_Kukui_TapuKoko_ChampionIntro, Nexus_Text_Kukui_TapuKoko_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Kukui_TapuKoko_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lillie_TapuLele_ChampionFight::
	nexus_fight TRAINER_NEXUS_LILLIE, Nexus_Text_Lillie_TapuLele_ChampionIntro, Nexus_Text_Lillie_TapuLele_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lillie_TapuLele_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gladion_TapuBulu_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLADION, Nexus_Text_Gladion_TapuBulu_ChampionIntro, Nexus_Text_Gladion_TapuBulu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gladion_TapuBulu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Juan_TapuFini_ChampionFight::
	nexus_fight TRAINER_NEXUS_JUAN, Nexus_Text_Juan_TapuFini_ChampionIntro, Nexus_Text_Juan_TapuFini_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Juan_TapuFini_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Chuck_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_CHUCK, Nexus_Text_Chuck_Urshifu_ChampionIntro, Nexus_Text_Chuck_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Chuck_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lusamine_Enamorus_ChampionFight::
	nexus_fight TRAINER_NEXUS_LUSAMINE, Nexus_Text_Lusamine_Enamorus_ChampionIntro, Nexus_Text_Lusamine_Enamorus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lusamine_Enamorus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Glacia_ChienPao_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLACIA, Nexus_Text_Glacia_ChienPao_ChampionIntro, Nexus_Text_Glacia_ChienPao_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Glacia_ChienPao_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Flannery_ChiYu_ChampionFight::
	nexus_fight TRAINER_NEXUS_FLANNERY, Nexus_Text_Flannery_ChiYu_ChampionIntro, Nexus_Text_Flannery_ChiYu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Flannery_ChiYu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lusamine_Fezandipiti_ChampionFight::
	nexus_fight TRAINER_NEXUS_LUSAMINE, Nexus_Text_Lusamine_Fezandipiti_ChampionIntro, Nexus_Text_Lusamine_Fezandipiti_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lusamine_Fezandipiti_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Red_ChampionFight::
	nexus_fight TRAINER_NEXUS_RED, Nexus_Text_Red_ChampionIntro, Nexus_Text_Red_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Red_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Leaf_Mew_ChampionFight::
	nexus_fight TRAINER_NEXUS_LEAF, Nexus_Text_Leaf_Mew_ChampionIntro, Nexus_Text_Leaf_Mew_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Leaf_Mew_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Spenser_Celebi_ChampionFight::
	nexus_fight TRAINER_NEXUS_SPENSER, Nexus_Text_Spenser_Celebi_ChampionIntro, Nexus_Text_Spenser_Celebi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Spenser_Celebi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brendan_Jirachi_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRENDAN, Nexus_Text_Brendan_Jirachi_ChampionIntro, Nexus_Text_Brendan_Jirachi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brendan_Jirachi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Misty_Manaphy_ChampionFight::
	nexus_fight TRAINER_NEXUS_MISTY, Nexus_Text_Misty_Manaphy_ChampionIntro, Nexus_Text_Misty_Manaphy_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Misty_Manaphy_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Karen_Darkrai_ChampionFight::
	nexus_fight TRAINER_NEXUS_KAREN, Nexus_Text_Karen_Darkrai_ChampionIntro, Nexus_Text_Karen_Darkrai_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Karen_Darkrai_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Erika_Shaymin_ChampionFight::
	nexus_fight TRAINER_NEXUS_ERIKA, Nexus_Text_Erika_Shaymin_ChampionIntro, Nexus_Text_Erika_Shaymin_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Erika_Shaymin_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Blue_Victini_ChampionFight::
	nexus_fight TRAINER_NEXUS_BLUE, Nexus_Text_Blue_Victini_ChampionIntro, Nexus_Text_Blue_Victini_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Blue_Victini_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Petrel_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_PETREL, Nexus_Text_Petrel_Meloetta_ChampionIntro, Nexus_Text_Petrel_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Petrel_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wallace_Diancie_ChampionFight::
	nexus_fight TRAINER_NEXUS_WALLACE, Nexus_Text_Wallace_Diancie_ChampionIntro, Nexus_Text_Wallace_Diancie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wallace_Diancie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Tucker_Hoopa_ChampionFight::
	nexus_fight TRAINER_NEXUS_TUCKER, Nexus_Text_Tucker_Hoopa_ChampionIntro, Nexus_Text_Tucker_Hoopa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Tucker_Hoopa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wattson_Magearna_ChampionFight::
	nexus_fight TRAINER_NEXUS_WATTSON, Nexus_Text_Wattson_Magearna_ChampionIntro, Nexus_Text_Wattson_Magearna_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wattson_Magearna_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Archer_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARCHER, Nexus_Text_Archer_Marshadow_ChampionIntro, Nexus_Text_Archer_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Archer_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wattson_Zeraora_ChampionFight::
	nexus_fight TRAINER_NEXUS_WATTSON, Nexus_Text_Wattson_Zeraora_ChampionIntro, Nexus_Text_Wattson_Zeraora_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wattson_Zeraora_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Jasmine_Melmetal_ChampionFight::
	nexus_fight TRAINER_NEXUS_JASMINE, Nexus_Text_Jasmine_Melmetal_ChampionIntro, Nexus_Text_Jasmine_Melmetal_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Jasmine_Melmetal_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Norman_Zarude_ChampionFight::
	nexus_fight TRAINER_NEXUS_NORMAN, Nexus_Text_Norman_Zarude_ChampionIntro, Nexus_Text_Norman_Zarude_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Norman_Zarude_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Greta_GreatTusk_ChampionFight::
	nexus_fight TRAINER_NEXUS_GRETA, Nexus_Text_Greta_GreatTusk_ChampionIntro, Nexus_Text_Greta_GreatTusk_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Greta_GreatTusk_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Whitney_ScreamTail_ChampionFight::
	nexus_fight TRAINER_NEXUS_WHITNEY, Nexus_Text_Whitney_ScreamTail_ChampionIntro, Nexus_Text_Whitney_ScreamTail_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Whitney_ScreamTail_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Sidney_BruteBonnet_ChampionFight::
	nexus_fight TRAINER_NEXUS_SIDNEY, Nexus_Text_Sidney_BruteBonnet_ChampionIntro, Nexus_Text_Sidney_BruteBonnet_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Sidney_BruteBonnet_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Phoebe_ChampionFight::
	nexus_fight TRAINER_NEXUS_PHOEBE, Nexus_Text_Phoebe_ChampionIntro, Nexus_Text_Phoebe_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Phoebe_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bugsy_SlitherWing_ChampionFight::
	nexus_fight TRAINER_NEXUS_BUGSY, Nexus_Text_Bugsy_SlitherWing_ChampionIntro, Nexus_Text_Bugsy_SlitherWing_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bugsy_SlitherWing_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_LtSurge_SandyShocks_ChampionFight::
	nexus_fight TRAINER_NEXUS_LT_SURGE, Nexus_Text_LtSurge_SandyShocks_ChampionIntro, Nexus_Text_LtSurge_SandyShocks_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_LtSurge_SandyShocks_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Noland_IronTreads_ChampionFight::
	nexus_fight TRAINER_NEXUS_NOLAND, Nexus_Text_Noland_IronTreads_ChampionIntro, Nexus_Text_Noland_IronTreads_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Noland_IronTreads_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Glacia_IronBundle_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLACIA, Nexus_Text_Glacia_IronBundle_ChampionIntro, Nexus_Text_Glacia_IronBundle_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Glacia_IronBundle_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brawly_IronHands_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRAWLY, Nexus_Text_Brawly_IronHands_ChampionIntro, Nexus_Text_Brawly_IronHands_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brawly_IronHands_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lucy_IronJugulis_ChampionFight::
	nexus_fight TRAINER_NEXUS_LUCY, Nexus_Text_Lucy_IronJugulis_ChampionIntro, Nexus_Text_Lucy_IronJugulis_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lucy_IronJugulis_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bugsy_IronMoth_ChampionFight::
	nexus_fight TRAINER_NEXUS_BUGSY, Nexus_Text_Bugsy_IronMoth_ChampionIntro, Nexus_Text_Bugsy_IronMoth_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bugsy_IronMoth_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brock_IronThorns_ChampionFight::
	nexus_fight TRAINER_NEXUS_BROCK, Nexus_Text_Brock_IronThorns_ChampionIntro, Nexus_Text_Brock_IronThorns_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brock_IronThorns_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Proton_RoaringMoon_ChampionFight::
	nexus_fight TRAINER_NEXUS_PROTON, Nexus_Text_Proton_RoaringMoon_ChampionIntro, Nexus_Text_Proton_RoaringMoon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Proton_RoaringMoon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wally_IronValiant_ChampionFight::
	nexus_fight TRAINER_NEXUS_WALLY, Nexus_Text_Wally_IronValiant_ChampionIntro, Nexus_Text_Wally_IronValiant_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wally_IronValiant_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Juan_WalkingWake_ChampionFight::
	nexus_fight TRAINER_NEXUS_JUAN, Nexus_Text_Juan_WalkingWake_ChampionIntro, Nexus_Text_Juan_WalkingWake_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Juan_WalkingWake_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Leaf_IronLeaves_ChampionFight::
	nexus_fight TRAINER_NEXUS_LEAF, Nexus_Text_Leaf_IronLeaves_ChampionIntro, Nexus_Text_Leaf_IronLeaves_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Leaf_IronLeaves_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lance_GougingFire_ChampionFight::
	nexus_fight TRAINER_NEXUS_LANCE, Nexus_Text_Lance_GougingFire_ChampionIntro, Nexus_Text_Lance_GougingFire_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lance_GougingFire_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Drake_RagingBolt_ChampionFight::
	nexus_fight TRAINER_NEXUS_DRAKE, Nexus_Text_Drake_RagingBolt_ChampionIntro, Nexus_Text_Drake_RagingBolt_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Drake_RagingBolt_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_TateAndLiza_IronBoulder_ChampionFight::
	nexus_fight TRAINER_NEXUS_TATE_AND_LIZA, Nexus_Text_TateAndLiza_IronBoulder_ChampionIntro, Nexus_Text_TateAndLiza_IronBoulder_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_TateAndLiza_IronBoulder_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Will_IronCrown_ChampionFight::
	nexus_fight TRAINER_NEXUS_WILL, Nexus_Text_Will_IronCrown_ChampionIntro, Nexus_Text_Will_IronCrown_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Will_IronCrown_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Anabel_Deoxys_ChampionFight::
	nexus_fight TRAINER_NEXUS_ANABEL, Nexus_Text_Anabel_Deoxys_ChampionIntro, Nexus_Text_Anabel_Deoxys_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Anabel_Deoxys_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brendan_Reshiram_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRENDAN, Nexus_Text_Brendan_Reshiram_ChampionIntro, Nexus_Text_Brendan_Reshiram_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brendan_Reshiram_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_May_Zekrom_ChampionFight::
	nexus_fight TRAINER_NEXUS_MAY, Nexus_Text_May_Zekrom_ChampionIntro, Nexus_Text_May_Zekrom_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_May_Zekrom_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Clair_ChampionFight::
	nexus_fight TRAINER_NEXUS_CLAIR, Nexus_Text_Clair_ChampionIntro, Nexus_Text_Clair_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Clair_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brawly_Keldeo_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRAWLY, Nexus_Text_Brawly_Keldeo_ChampionIntro, Nexus_Text_Brawly_Keldeo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brawly_Keldeo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wallace_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_WALLACE, Nexus_Text_Wallace_Xerneas_ChampionIntro, Nexus_Text_Wallace_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wallace_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Sidney_Yveltal_ChampionFight::
	nexus_fight TRAINER_NEXUS_SIDNEY, Nexus_Text_Sidney_Yveltal_ChampionIntro, Nexus_Text_Sidney_Yveltal_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Sidney_Yveltal_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lucy_Zygarde_ChampionFight::
	nexus_fight TRAINER_NEXUS_LUCY, Nexus_Text_Lucy_Zygarde_ChampionIntro, Nexus_Text_Lucy_Zygarde_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lucy_Zygarde_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Blaine_Volcanion_ChampionFight::
	nexus_fight TRAINER_NEXUS_BLAINE, Nexus_Text_Blaine_Volcanion_ChampionIntro, Nexus_Text_Blaine_Volcanion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Blaine_Volcanion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Blue_Zacian_ChampionFight::
	nexus_fight TRAINER_NEXUS_BLUE, Nexus_Text_Blue_Zacian_ChampionIntro, Nexus_Text_Blue_Zacian_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Blue_Zacian_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Norman_Zamazenta_ChampionFight::
	nexus_fight TRAINER_NEXUS_NORMAN, Nexus_Text_Norman_Zamazenta_ChampionIntro, Nexus_Text_Norman_Zamazenta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Norman_Zamazenta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Tucker_Eternatus_ChampionFight::
	nexus_fight TRAINER_NEXUS_TUCKER, Nexus_Text_Tucker_Eternatus_ChampionIntro, Nexus_Text_Tucker_Eternatus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Tucker_Eternatus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_LtSurge_Regieleki_ChampionFight::
	nexus_fight TRAINER_NEXUS_LT_SURGE, Nexus_Text_LtSurge_Regieleki_ChampionIntro, Nexus_Text_LtSurge_Regieleki_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_LtSurge_Regieleki_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Drake_Regidrago_ChampionFight::
	nexus_fight TRAINER_NEXUS_DRAKE, Nexus_Text_Drake_Regidrago_ChampionIntro, Nexus_Text_Drake_Regidrago_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Drake_Regidrago_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Pryce_Glastrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_PRYCE, Nexus_Text_Pryce_Glastrier_ChampionIntro, Nexus_Text_Pryce_Glastrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Pryce_Glastrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Morty_Spectrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_MORTY, Nexus_Text_Morty_Spectrier_ChampionIntro, Nexus_Text_Morty_Spectrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Morty_Spectrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Will_Calyrex_ChampionFight::
	nexus_fight TRAINER_NEXUS_WILL, Nexus_Text_Will_Calyrex_ChampionIntro, Nexus_Text_Will_Calyrex_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Will_Calyrex_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Archer_WoChien_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARCHER, Nexus_Text_Archer_WoChien_ChampionIntro, Nexus_Text_Archer_WoChien_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Archer_WoChien_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Proton_TingLu_ChampionFight::
	nexus_fight TRAINER_NEXUS_PROTON, Nexus_Text_Proton_TingLu_ChampionIntro, Nexus_Text_Proton_TingLu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Proton_TingLu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Janine_Okidogi_ChampionFight::
	nexus_fight TRAINER_NEXUS_JANINE, Nexus_Text_Janine_Okidogi_ChampionIntro, Nexus_Text_Janine_Okidogi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Janine_Okidogi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Janine_Munkidori_ChampionFight::
	nexus_fight TRAINER_NEXUS_JANINE, Nexus_Text_Janine_Munkidori_ChampionIntro, Nexus_Text_Janine_Munkidori_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Janine_Munkidori_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Roxanne_Terapagos_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROXANNE, Nexus_Text_Roxanne_Terapagos_ChampionIntro, Nexus_Text_Roxanne_Terapagos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Roxanne_Terapagos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Koga_ChampionFight::
	nexus_fight TRAINER_NEXUS_KOGA, Nexus_Text_Koga_ChampionIntro, Nexus_Text_Koga_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Koga_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

@ New Looker Files (R18), one per new legendary concept.
Nexus_EventScript_Kyogre_LookerFile::
	msgbox Nexus_Text_Kyogre_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Mewtwo_LookerFile::
	msgbox Nexus_Text_Mewtwo_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Genesect_LookerFile::
	msgbox Nexus_Text_Genesect_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Lugia_LookerFile::
	msgbox Nexus_Text_Lugia_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_HoOh_LookerFile::
	msgbox Nexus_Text_HoOh_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Groudon_LookerFile::
	msgbox Nexus_Text_Groudon_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Rayquaza_LookerFile::
	msgbox Nexus_Text_Rayquaza_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Dialga_LookerFile::
	msgbox Nexus_Text_Dialga_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Palkia_LookerFile::
	msgbox Nexus_Text_Palkia_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Giratina_LookerFile::
	msgbox Nexus_Text_Giratina_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Solgaleo_LookerFile::
	msgbox Nexus_Text_Solgaleo_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Lunala_LookerFile::
	msgbox Nexus_Text_Lunala_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Necrozma_LookerFile::
	msgbox Nexus_Text_Necrozma_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Koraidon_LookerFile::
	msgbox Nexus_Text_Koraidon_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Miraidon_LookerFile::
	msgbox Nexus_Text_Miraidon_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Silvally_LookerFile::
	msgbox Nexus_Text_Silvally_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Ogerpon_LookerFile::
	msgbox Nexus_Text_Ogerpon_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Articuno_LookerFile::
	msgbox Nexus_Text_Articuno_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_GalarianArticuno_LookerFile::
	msgbox Nexus_Text_GalarianArticuno_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zapdos_LookerFile::
	msgbox Nexus_Text_Zapdos_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_GalarianZapdos_LookerFile::
	msgbox Nexus_Text_GalarianZapdos_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Moltres_LookerFile::
	msgbox Nexus_Text_Moltres_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_GalarianMoltres_LookerFile::
	msgbox Nexus_Text_GalarianMoltres_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Raikou_LookerFile::
	msgbox Nexus_Text_Raikou_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Entei_LookerFile::
	msgbox Nexus_Text_Entei_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Suicune_LookerFile::
	msgbox Nexus_Text_Suicune_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Regirock_LookerFile::
	msgbox Nexus_Text_Regirock_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Regice_LookerFile::
	msgbox Nexus_Text_Regice_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Registeel_LookerFile::
	msgbox Nexus_Text_Registeel_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Latias_LookerFile::
	msgbox Nexus_Text_Latias_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Latios_LookerFile::
	msgbox Nexus_Text_Latios_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Uxie_LookerFile::
	msgbox Nexus_Text_Uxie_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Mesprit_LookerFile::
	msgbox Nexus_Text_Mesprit_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Azelf_LookerFile::
	msgbox Nexus_Text_Azelf_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Heatran_LookerFile::
	msgbox Nexus_Text_Heatran_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Regigigas_LookerFile::
	msgbox Nexus_Text_Regigigas_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Cresselia_LookerFile::
	msgbox Nexus_Text_Cresselia_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Cobalion_LookerFile::
	msgbox Nexus_Text_Cobalion_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Terrakion_LookerFile::
	msgbox Nexus_Text_Terrakion_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Virizion_LookerFile::
	msgbox Nexus_Text_Virizion_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Tornadus_LookerFile::
	msgbox Nexus_Text_Tornadus_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Thundurus_LookerFile::
	msgbox Nexus_Text_Thundurus_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Landorus_LookerFile::
	msgbox Nexus_Text_Landorus_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_TapuKoko_LookerFile::
	msgbox Nexus_Text_TapuKoko_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_TapuLele_LookerFile::
	msgbox Nexus_Text_TapuLele_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_TapuBulu_LookerFile::
	msgbox Nexus_Text_TapuBulu_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_TapuFini_LookerFile::
	msgbox Nexus_Text_TapuFini_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Urshifu_LookerFile::
	msgbox Nexus_Text_Urshifu_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Enamorus_LookerFile::
	msgbox Nexus_Text_Enamorus_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_ChienPao_LookerFile::
	msgbox Nexus_Text_ChienPao_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_ChiYu_LookerFile::
	msgbox Nexus_Text_ChiYu_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Fezandipiti_LookerFile::
	msgbox Nexus_Text_Fezandipiti_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Arceus_LookerFile::
	msgbox Nexus_Text_Arceus_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Mew_LookerFile::
	msgbox Nexus_Text_Mew_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Celebi_LookerFile::
	msgbox Nexus_Text_Celebi_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Jirachi_LookerFile::
	msgbox Nexus_Text_Jirachi_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Manaphy_LookerFile::
	msgbox Nexus_Text_Manaphy_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Darkrai_LookerFile::
	msgbox Nexus_Text_Darkrai_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Shaymin_LookerFile::
	msgbox Nexus_Text_Shaymin_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Victini_LookerFile::
	msgbox Nexus_Text_Victini_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Meloetta_LookerFile::
	msgbox Nexus_Text_Meloetta_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Diancie_LookerFile::
	msgbox Nexus_Text_Diancie_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Hoopa_LookerFile::
	msgbox Nexus_Text_Hoopa_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Magearna_LookerFile::
	msgbox Nexus_Text_Magearna_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Marshadow_LookerFile::
	msgbox Nexus_Text_Marshadow_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zeraora_LookerFile::
	msgbox Nexus_Text_Zeraora_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Melmetal_LookerFile::
	msgbox Nexus_Text_Melmetal_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zarude_LookerFile::
	msgbox Nexus_Text_Zarude_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_GreatTusk_LookerFile::
	msgbox Nexus_Text_GreatTusk_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_ScreamTail_LookerFile::
	msgbox Nexus_Text_ScreamTail_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_BruteBonnet_LookerFile::
	msgbox Nexus_Text_BruteBonnet_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_FlutterMane_LookerFile::
	msgbox Nexus_Text_FlutterMane_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_SlitherWing_LookerFile::
	msgbox Nexus_Text_SlitherWing_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_SandyShocks_LookerFile::
	msgbox Nexus_Text_SandyShocks_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronTreads_LookerFile::
	msgbox Nexus_Text_IronTreads_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronBundle_LookerFile::
	msgbox Nexus_Text_IronBundle_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronHands_LookerFile::
	msgbox Nexus_Text_IronHands_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronJugulis_LookerFile::
	msgbox Nexus_Text_IronJugulis_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronMoth_LookerFile::
	msgbox Nexus_Text_IronMoth_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronThorns_LookerFile::
	msgbox Nexus_Text_IronThorns_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_RoaringMoon_LookerFile::
	msgbox Nexus_Text_RoaringMoon_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronValiant_LookerFile::
	msgbox Nexus_Text_IronValiant_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_WalkingWake_LookerFile::
	msgbox Nexus_Text_WalkingWake_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronLeaves_LookerFile::
	msgbox Nexus_Text_IronLeaves_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_GougingFire_LookerFile::
	msgbox Nexus_Text_GougingFire_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_RagingBolt_LookerFile::
	msgbox Nexus_Text_RagingBolt_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronBoulder_LookerFile::
	msgbox Nexus_Text_IronBoulder_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_IronCrown_LookerFile::
	msgbox Nexus_Text_IronCrown_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Deoxys_LookerFile::
	msgbox Nexus_Text_Deoxys_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Reshiram_LookerFile::
	msgbox Nexus_Text_Reshiram_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zekrom_LookerFile::
	msgbox Nexus_Text_Zekrom_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Kyurem_LookerFile::
	msgbox Nexus_Text_Kyurem_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Keldeo_LookerFile::
	msgbox Nexus_Text_Keldeo_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Xerneas_LookerFile::
	msgbox Nexus_Text_Xerneas_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Yveltal_LookerFile::
	msgbox Nexus_Text_Yveltal_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zygarde_LookerFile::
	msgbox Nexus_Text_Zygarde_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Volcanion_LookerFile::
	msgbox Nexus_Text_Volcanion_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zacian_LookerFile::
	msgbox Nexus_Text_Zacian_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Zamazenta_LookerFile::
	msgbox Nexus_Text_Zamazenta_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Eternatus_LookerFile::
	msgbox Nexus_Text_Eternatus_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Regieleki_LookerFile::
	msgbox Nexus_Text_Regieleki_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Regidrago_LookerFile::
	msgbox Nexus_Text_Regidrago_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Glastrier_LookerFile::
	msgbox Nexus_Text_Glastrier_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Spectrier_LookerFile::
	msgbox Nexus_Text_Spectrier_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Calyrex_LookerFile::
	msgbox Nexus_Text_Calyrex_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_WoChien_LookerFile::
	msgbox Nexus_Text_WoChien_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_TingLu_LookerFile::
	msgbox Nexus_Text_TingLu_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Okidogi_LookerFile::
	msgbox Nexus_Text_Okidogi_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Munkidori_LookerFile::
	msgbox Nexus_Text_Munkidori_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Terapagos_LookerFile::
	msgbox Nexus_Text_Terapagos_LookerFile, MSGBOX_DEFAULT
	return

Nexus_EventScript_Pecharunt_LookerFile::
	msgbox Nexus_Text_Pecharunt_LookerFile, MSGBOX_DEFAULT
	return

@ Generic dialogue (R16), the four rooms.
Nexus_Text_Red_Intro:
	.string "…\p"
	.string "……\p"
	.string "…Quiet here. Like the summit.\p"
	.string "…!$"

Nexus_Text_Red_Defeat:
	.string "……\p"
	.string "…Heh.$"

Nexus_Text_Blue_Intro:
	.string "Hey! Wherever this is, I got here first.\n"
	.string "That's how it always goes with me.\p"
	.string "You're not Red, but you'll do. Gramps\n"
	.string "always said I should battle people who\l"
	.string "aren't him once in a while.\p"
	.string "Let's go! I'll show you why I'm the\n"
	.string "greatest!$"

Nexus_Text_Blue_Defeat:
	.string "What?! Unbelievable! …Okay, fine. Smell\n"
	.string "ya later!$"

Nexus_Text_Brock_Intro:
	.string "I'm Brock! Wherever I end up, one thing\n"
	.string "never changes: rock-hard\l"
	.string "determination.\p"
	.string "Back in Pewter, I battle every rookie\n"
	.string "who walks in. My Onix, well, it's a\l"
	.string "Steelix now, has taken more first hits\l"
	.string "than any Pokémon alive.\p"
	.string "So come on. Hit me with your best one!$"

Nexus_Text_Brock_Defeat:
	.string "Solid. Just like a good rock should be.$"

Nexus_Text_Misty_Intro:
	.string "Hi, you're a new face! I'm Misty, the\n"
	.string "tomboyish mermaid!\p"
	.string "My policy is simple: an all-out\n"
	.string "offensive with Water-type Pokémon!\l"
	.string "Whatever this place is, that doesn't\l"
	.string "change.\p"
	.string "Ready to get soaked?$"

Nexus_Text_Misty_Defeat:
	.string "You're really strong! …I mean it! Don't\n"
	.string "look at me like that!$"

Nexus_Text_LtSurge_Intro:
	.string "Hey, kid! You picked a strange place\n"
	.string "for a picnic!\p"
	.string "Electric Pokémon saved my life in the\n"
	.string "war, baby. I haven't gone anywhere\l"
	.string "without 'em since.\p"
	.string "Now, ten-hut! Show me what you got!$"

Nexus_Text_LtSurge_Defeat:
	.string "Whoa! You're the real deal, kid!\n"
	.string "Dismissed… with honors!$"

Nexus_Text_Erika_Intro:
	.string "Oh, my… Please forgive me. I must have\n"
	.string "dozed off.\p"
	.string "I always keep a seed in my sleeve, in\n"
	.string "case a place has no flowers. This one\l"
	.string "had none, so I planted it.\p"
	.string "It is already sprouting. How rude of me\n"
	.string "to keep it waiting. Shall we?$"

Nexus_Text_Erika_Defeat:
	.string "You pruned my arrangement down to the\n"
	.string "stem. It's lovely that way, too.$"

Nexus_Text_Koga_Intro:
	.string "Fwahahaha! You think you found me? No.\n"
	.string "You found the spot where I allowed you\l"
	.string "to look.\p"
	.string "I once ran a Gym of invisible walls.\n"
	.string "Children bumped their noses for an hour\l"
	.string "and thanked me afterward.\p"
	.string "Here, the walls are your own doubts. Let\n"
	.string "us see how you find your way!$"

Nexus_Text_Koga_Defeat:
	.string "Fwahaha… Your path was straighter than\n"
	.string "my walls.$"

Nexus_Text_Sabrina_Intro:
	.string "I saw you coming. I always do.\p"
	.string "In my Gym, the floor sends you from room\n"
	.string "to room. Most challengers get lost. I\l"
	.string "never have.\p"
	.string "…Still, there is a first time for\n"
	.string "everything. Show me yours.$"

Nexus_Text_Sabrina_Defeat:
	.string "I foresaw this. It still stings.$"

Nexus_Text_Blaine_Intro:
	.string "Hah! Quiz time! What burns hotter than\n"
	.string "a volcano?\p"
	.string "Wrong! Whatever you said, it's wrong. I\n"
	.string "lost my whole island to a volcano, so\l"
	.string "I'd know!\p"
	.string "These days my Gym is in a sea cave. Fire\n"
	.string "in a wet place, hah! Hope you packed\l"
	.string "Burn Heal!$"

Nexus_Text_Blaine_Defeat:
	.string "Hah! Correct answer! My flame's out…\n"
	.string "for now.$"

Nexus_Text_Giovanni_Intro:
	.string "So, you found me. Don't look so pleased.\n"
	.string "I've been found by children before.\p"
	.string "For years, Viridian's Gym sat locked\n"
	.string "while its Leader ran an empire from the\l"
	.string "back door. No adult ever noticed.\p"
	.string "A child did. Let us see what kind of\n"
	.string "child you are.$"

Nexus_Text_Giovanni_Defeat:
	.string "…Again. You all have the same look in\n"
	.string "your eyes.$"

Nexus_Text_Lance_Intro:
	.string "I've flown over a lot of strange places\n"
	.string "on Dragonite's back. This one isn't on\l"
	.string "any map.\p"
	.string "The Elder of the Dragon's Den asks\n"
	.string "every dragon Trainer the same\l"
	.string "question: what matters most to a\l"
	.string "Trainer?\p"
	.string "I've answered it a dozen times. The\n"
	.string "answer keeps changing. Let's find out\l"
	.string "what it is today!$"

Nexus_Text_Lance_Defeat:
	.string "…Hm. That's the answer I'll give next\n"
	.string "year.$"

Nexus_Text_Archer_Intro:
	.string "Three years ago, Team Rocket\n"
	.string "disbanded. I have been waiting ever\l"
	.string "since.\p"
	.string "I once broadcast a message across all\n"
	.string "of Johto, meant for one man. He never\l"
	.string "answered.\p"
	.string "I still keep a radio on. Even here. Now,\n"
	.string "out of my way.$"

Nexus_Text_Archer_Defeat:
	.string "Static. As always.$"

Nexus_Text_Ariana_Intro:
	.string "I am Ariana. I don't waste words on\n"
	.string "children, so listen.\p"
	.string "At the Lake of Rage, one signal from\n"
	.string "our base forced the Magikarp there to\l"
	.string "evolve. People remember the red\l"
	.string "Gyarados.\p"
	.string "They forget the signal worked. I don't.\n"
	.string "Come here.$"

Nexus_Text_Ariana_Defeat:
	.string "Hmph. Write it down, then. It won't\n"
	.string "happen twice.$"

Nexus_Text_Proton_Intro:
	.string "They call me the scariest, cruelest guy\n"
	.string "in Team Rocket. I earned that.\p"
	.string "Slowpoke tails sell for a fortune, and\n"
	.string "they grow back. You know how long a\l"
	.string "Slowpoke takes to notice one's gone?\p"
	.string "Neither do I. I never stay to watch.\n"
	.string "Let's go!$"

Nexus_Text_Proton_Defeat:
	.string "Tch. You're no fun. You didn't even\n"
	.string "flinch.$"

Nexus_Text_Petrel_Intro:
	.string "Ahahaha! Did you know I once ran a\n"
	.string "whole Radio Tower as its Director?\l"
	.string "Voice, suit, hair. Nobody noticed.\p"
	.string "I've been so many people, some\n"
	.string "mornings I have to check which one I\l"
	.string "am.\p"
	.string "Today? Today I'm the guy who beats\n"
	.string "you!$"

Nexus_Text_Petrel_Defeat:
	.string "Ha! Tell nobody. Or tell them it was\n"
	.string "someone else.$"

Nexus_Text_Silver_Intro:
	.string "…It's you. Figures.\p"
	.string "My Golbat evolved. You know what that\n"
	.string "takes. Don't say it.\p"
	.string "I'm still not doing this for fun. Let's\n"
	.string "go.$"

Nexus_Text_Silver_Defeat:
	.string "…Fine. I'll get stronger. With them,\n"
	.string "this time.$"

Nexus_Text_Falkner_Intro:
	.string "People say you can ground a bird\n"
	.string "Pokémon with one jolt of electricity.\p"
	.string "I've heard it since I was a boy, with\n"
	.string "my father's Pidgeotto on my arm.\p"
	.string "He never argued with them. He just\n"
	.string "flew. So will I!$"

Nexus_Text_Falkner_Defeat:
	.string "...Grounded. Don't tell my father.$"

Nexus_Text_Bugsy_Intro:
	.string "People think Bug Pokémon are weak\n"
	.string "because they're small.\p"
	.string "They've survived every age of the\n"
	.string "world so far. Every single one.\p"
	.string "My team is very patient. Let's see how\n"
	.string "patient you are!$"

Nexus_Text_Bugsy_Defeat:
	.string "Amazing! I have to write this down\n"
	.string "before I forget how you did it.$"

Nexus_Text_Whitney_Intro:
	.string "Hiya! I'm Whitney! Everybody back in\n"
	.string "Goldenrod says my Pokémon are the\l"
	.string "cutest.\p"
	.string "Everybody who battles me says my\n"
	.string "Miltank is the scariest. Both are\l"
	.string "true!\p"
	.string "So don't cry when you lose, okay?\n"
	.string "That's my job!$"

Nexus_Text_Whitney_Defeat:
	.string "Waaah! That wasn't fair! ...Okay, it\n"
	.string "was fair. Waaah!$"

Nexus_Text_Morty_Intro:
	.string "I've been expecting you. Or someone.\n"
	.string "In Ecruteak, we're taught to expect.\p"
	.string "My family has trained for generations\n"
	.string "to see things that aren't there.\p"
	.string "You're here, though. That makes you\n"
	.string "easy. Shall we?$"

Nexus_Text_Morty_Defeat:
	.string "I saw that coming. I still couldn't\n"
	.string "stop it.$"

Nexus_Text_Chuck_Intro:
	.string "WAHAHAH! Finally, someone to fight!\p"
	.string "I've done a thousand push-ups since I\n"
	.string "got here. I stopped counting at a\l"
	.string "thousand, so it's probably more!\p"
	.string "My wife says I don't know when to stop.\n"
	.string "She's right. Let's go!$"

Nexus_Text_Chuck_Defeat:
	.string "WAHAHAH... hah. Ow. You're strong!$"

Nexus_Text_Jasmine_Intro:
	.string "...Oh. Um. Hello.\p"
	.string "I'm sorry. I get nervous with people I\n"
	.string "don't know. With Steel Pokémon, I\l"
	.string "never do.\p"
	.string "They're hard on the outside because\n"
	.string "they care about what's inside. So am\l"
	.string "I. ...Please, let's begin.$"

Nexus_Text_Jasmine_Defeat:
	.string "...You were very kind to my Pokémon,\n"
	.string "even while beating them. Thank you.$"

Nexus_Text_Pryce_Intro:
	.string "Hm. Another young one.\p"
	.string "I have been with Pokémon since before\n"
	.string "you were born. Ice teaches you to be\l"
	.string "patient.\p"
	.string "Most young people run out of patience\n"
	.string "before I run out of ice. Let us see\l"
	.string "about you.$"

Nexus_Text_Pryce_Defeat:
	.string "Hmph. The ice has cracked. It does\n"
	.string "that, eventually.$"

Nexus_Text_Clair_Intro:
	.string "I am Clair. The world's best dragon\n"
	.string "master.\p"
	.string "Don't look behind me for my cousin. He\n"
	.string "isn't coming, and I don't need him to.\p"
	.string "My dragons and I will do this ourselves!$"

Nexus_Text_Clair_Defeat:
	.string "…There must be some mistake. Fine. I'll\n"
	.string "say it once: you're good.$"

Nexus_Text_Will_Intro:
	.string "Welcome. I am Will. I have trained all\n"
	.string "around the world… and now, it seems,\l"
	.string "beyond it.\p"
	.string "Do you know why I wear this mask? So\n"
	.string "that you look at it, and not at my\l"
	.string "hands.\p"
	.string "Too late. The battle has already begun.$"

Nexus_Text_Will_Defeat:
	.string "I… I can't believe it. You were watching\n"
	.string "my hands.$"

Nexus_Text_Karen_Intro:
	.string "I'm Karen. I don't know this place, and\n"
	.string "I don't need to.\p"
	.string "Strong Pokémon. Weak Pokémon. That is\n"
	.string "only the selfish perception of people.\l"
	.string "It follows you everywhere, even here.\p"
	.string "Show me your favorites. Not your\n"
	.string "strongest. Your favorites.$"

Nexus_Text_Karen_Defeat:
	.string "Your favorites won. As they should.$"

Nexus_Text_Eusine_Intro:
	.string "Ah, a Trainer! My name's Eusine. I'm on\n"
	.string "the trail of a certain legend.\p"
	.string "Ten years of rumors, puddles, and north\n"
	.string "winds. You'd be amazed what I know\l"
	.string "about puddles.\p"
	.string "Let's battle! A true researcher tests\n"
	.string "everything!$"

Nexus_Text_Eusine_Defeat:
	.string "I hate to admit it, but you win. …I'm\n"
	.string "writing that down, too.$"

Nexus_Text_Brendan_Intro:
	.string "Hey! Hold still a sec, I'm writing this\n"
	.string "down.\p"
	.string "My dad sends me out to record every\n"
	.string "Pokémon I see. Habitat, height, what it\l"
	.string "eats.\p"
	.string "So what do you eat? …Kidding. Let's\n"
	.string "battle, I'll take notes after!$"

Nexus_Text_Brendan_Defeat:
	.string "Huh. You're pretty good. That's going\n"
	.string "in the notebook, underlined.$"

Nexus_Text_May_Intro:
	.string "Hi! Wait, don't tell me. Traveling\n"
	.string "Trainer, first time here, a little lost?\p"
	.string "Me too! My dad says getting lost is the\n"
	.string "best way to find new Pokémon.\p"
	.string "And the best way to find out about a\n"
	.string "Trainer is a battle. Ready?$"

Nexus_Text_May_Defeat:
	.string "Aww! …Okay, that was fun anyway. I'm\n"
	.string "writing you down as 'strong.'$"

Nexus_Text_Wally_Intro:
	.string "Oh! H-hi. Sorry, I'm still catching my\n"
	.string "breath. I always am.\p"
	.string "When I was little, I couldn't walk up a\n"
	.string "hill without resting. Now I climb them\l"
	.string "for fun.\p"
	.string "My Pokémon did that. Let me show you!$"

Nexus_Text_Wally_Defeat:
	.string "Hah… hah… I lost, but I'm still\n"
	.string "standing. That's new.$"

Nexus_Text_Roxanne_Intro:
	.string "Good day! Please don't mind the\n"
	.string "notebook. I write down every battle,\l"
	.string "even the ones I lose.\p"
	.string "Especially those, actually. A loss\n"
	.string "teaches you more, but only if you\l"
	.string "remember it properly.\p"
	.string "I'm Roxanne, Gym Leader of Rustboro\n"
	.string "City. Now then -- shall we begin the\l"
	.string "lesson?$"

Nexus_Text_Roxanne_Defeat:
	.string "I see. I'll need a fresh page for this.$"

Nexus_Text_Brawly_Intro:
	.string "Whoa, a new spot! I don't know where I\n"
	.string "washed up, but it's got a serious\l"
	.string "current.\p"
	.string "I'm Brawly! I got churned in the rough\n"
	.string "waves of Dewford and toughened up in a\l"
	.string "pitch-black cave.\p"
	.string "Wherever I land, I paddle out and ride\n"
	.string "the biggest wave around. Today, that's\l"
	.string "you! Let's go!$"

Nexus_Text_Brawly_Defeat:
	.string "Wiped out! Man, what a wave that was.$"

Nexus_Text_Wattson_Intro:
	.string "Wahahahaha! Well, would you look at\n"
	.string "this! Somewhere new, and not a single\l"
	.string "power outlet in sight!\p"
	.string "Doesn't matter a whit. I carry my own\n"
	.string "spark, young one.\p"
	.string "I'm Wattson! Now, let's see if you can\n"
	.string "light up an old man's day! Wahahaha!$"

Nexus_Text_Wattson_Defeat:
	.string "Wahahaha! Blew my fuse clean out!\n"
	.string "Splendid!$"

Nexus_Text_Flannery_Intro:
	.string "W-welcome! I'm Flannery, Gym Leader of\n"
	.string "Lavaridge! I'll show you the hot moves\l"
	.string "of a… ahem.\p"
	.string "I don't know this place. But Grandpa\n"
	.string "always said a real Fire Trainer brings\l"
	.string "her own heat.\p"
	.string "So get ready to get burned! …Wait, that\n"
	.string "came out wrong. Let's just battle!$"

Nexus_Text_Flannery_Defeat:
	.string "Ugh! I got way too fired up again,\n"
	.string "didn't I?$"

Nexus_Text_Norman_Intro:
	.string "Hm. I don't know how I got here. But a\n"
	.string "Gym Leader doesn't need to know where\l"
	.string "he is to do his job.\p"
	.string "I'm Norman. In Petalburg, I teach one\n"
	.string "thing above all: strength is something\l"
	.string "you train, every single day.\p"
	.string "Show me what your days have been like.$"

Nexus_Text_Norman_Defeat:
	.string "Well done. Your Pokémon were trained\n"
	.string "with care.$"

Nexus_Text_Winona_Intro:
	.string "I am Winona. In Fortree, we build our\n"
	.string "homes among the treetops, so that we\l"
	.string "may live close to the sky.\p"
	.string "I do not know this place. But the air\n"
	.string "moves here, and where the air moves, my\l"
	.string "birds can fly.\p"
	.string "Let us dance in the wind together.$"

Nexus_Text_Winona_Defeat:
	.string "You flew higher than I did. How lovely.$"

Nexus_Text_TateAndLiza_Intro:
	.string "Hehehe… Were you surprised?\n"
	.string "Fufufu… Were you surprised?\p"
	.string "We don't know how we got here.\n"
	.string "But we got here together. We always do.\p"
	.string "We can tell what you're thinking.\n"
	.string "So can we. Shall we begin?$"

Nexus_Text_TateAndLiza_Defeat:
	.string "We lost…\n"
	.string "…together, at least.$"

Nexus_Text_Wallace_Intro:
	.string "Welcome. I am Wallace.\p"
	.string "People call my battles elegant. They\n"
	.string "see only the performance.\p"
	.string "They never see the mornings I spend in\n"
	.string "Sootopolis repeating a single turn\l"
	.string "until Milotic and I move as one.\p"
	.string "Beauty is mostly repetition no one\n"
	.string "sees. Now, let us show you some!$"

Nexus_Text_Wallace_Defeat:
	.string "Bravo. The most beautiful thing on this\n"
	.string "stage today, and it was not mine.$"

Nexus_Text_Juan_Intro:
	.string "Ah, a visitor! Forgive me, I was\n"
	.string "rehearsing.\p"
	.string "It was I who taught Wallace everything\n"
	.string "he knows of water and grace. He\l"
	.string "surpassed me, of course.\p"
	.string "A teacher should only ever be proud of\n"
	.string "that.\p"
	.string "Now then! Let the water and I show you\n"
	.string "a grand illusion!$"

Nexus_Text_Juan_Defeat:
	.string "Aahahaha! Excellent! Even the illusion\n"
	.string "applauds.$"

Nexus_Text_Sidney_Intro:
	.string "Hey, I like that look you're giving me.\p"
	.string "Folks always call Dark types bad news.\n"
	.string "Sneaky. Mean.\p"
	.string "Me, I think they're honest. They fight\n"
	.string "to win, and they don't pretend\l"
	.string "otherwise.\p"
	.string "So don't hold back, and I won't either.\n"
	.string "Let's make some noise!$"

Nexus_Text_Sidney_Defeat:
	.string "Ha! I lost! Eh, it was fun, so it doesn't\n"
	.string "matter.$"

Nexus_Text_Phoebe_Intro:
	.string "Ahahaha! I'm Phoebe. I trained on Mt.\n"
	.string "Pyre, way up where the graves are.\p"
	.string "Everyone thinks the dead are scary,\n"
	.string "but mostly they're just lonely!\p"
	.string "Up there I learned to hear them. My\n"
	.string "Dusclops hears them best of all.\p"
	.string "So let's play! They love it when\n"
	.string "someone plays!$"

Nexus_Text_Phoebe_Defeat:
	.string "Oh, you win! Ahaha, the ghosts are\n"
	.string "cheering for you.$"

Nexus_Text_Glacia_Intro:
	.string "Welcome. I am Glacia. I traveled far to\n"
	.string "Hoenn to hone my icy skills.\p"
	.string "The heat there was unbearable. I\n"
	.string "stayed anyway.\p"
	.string "Ice is not tempered in the cold, you\n"
	.string "see. It is tempered by what tries to\l"
	.string "melt it.\p"
	.string "So show me your fire. I would hate to be\n"
	.string "disappointed again.$"

Nexus_Text_Glacia_Defeat:
	.string "How hot your spirit burns… My ice could\n"
	.string "not even leave a mark.$"

Nexus_Text_Drake_Intro:
	.string "I am Drake, and I have sailed a long way\n"
	.string "to be here.\p"
	.string "Dragons are wild things. Free things.\n"
	.string "They do not need us.\p"
	.string "So when one chooses to fight beside\n"
	.string "you, that is not obedience. It is a\l"
	.string "gift.\p"
	.string "Show me you know the difference!$"

Nexus_Text_Drake_Defeat:
	.string "Superb, it should be said. You know the\n"
	.string "difference.$"

Nexus_Text_Noland_Intro:
	.string "Hey, hey! Noland, Factory Head. You\n"
	.string "know the drill at my place: you get a\l"
	.string "team you didn't raise, and you figure\l"
	.string "it out fast.\p"
	.string "Funny thing. I woke up in here with\n"
	.string "these six, and nobody handed me a\l"
	.string "receipt.\p"
	.string "I read their moves once. That's all I\n"
	.string "need. Knowledge beats a long\l"
	.string "friendship any day. Let's test that!$"

Nexus_Text_Noland_Defeat:
	.string "Ha! You read them faster than I did.\n"
	.string "That's the whole job, you know.$"

Nexus_Text_Greta_Intro:
	.string "Hey there! Greta, Arena Tycoon! You\n"
	.string "know how my Arena works? Three turns,\l"
	.string "and I judge you on Mind, Skill and Body.\p"
	.string "I've been in here a while now, and\n"
	.string "nobody's come to judge me. So I've\l"
	.string "been judging myself.\p"
	.string "Mind: kind of lost. Skill: just fine.\n"
	.string "Body: raring to go! Let's make it three\l"
	.string "turns, champ!$"

Nexus_Text_Greta_Defeat:
	.string "Mind, Skill, Body… OK, OK, you win on all\n"
	.string "three. No arguing with the judges!$"

Nexus_Text_Tucker_Intro:
	.string "Ha ha ha! Did you hear that? No?\n"
	.string "That's the crowd! They always cheer\l"
	.string "when Tucker walks in.\p"
	.string "Here, they're a little… quiet. That's\n"
	.string "fine. I'll cheer for myself until they\l"
	.string "catch up.\p"
	.string "Now, fan! Give me a match worth a\n"
	.string "standing ovation!$"

Nexus_Text_Tucker_Defeat:
	.string "Bravo! Bravo! …That was me clapping.\n"
	.string "For you. Don't let it go to your head.$"

Nexus_Text_Lucy_Intro:
	.string "…Lucy.\p"
	.string "I don't talk much. At the Pike, you pick\n"
	.string "a door, and you live with what's behind\l"
	.string "it.\p"
	.string "I picked one, and I ended up here. …I'm\n"
	.string "living with it. Your turn.$"

Nexus_Text_Lucy_Defeat:
	.string "…Hmph. Fine. That one was yours.$"

Nexus_Text_Spenser_Intro:
	.string "Hohoho. Come in, young one. Spenser,\n"
	.string "the Palace Maven. Sit, if there were\l"
	.string "anywhere to sit.\p"
	.string "In my Palace, a Pokémon fights by its\n"
	.string "own nature. I simply get out of the\l"
	.string "way.\p"
	.string "At my age, getting out of the way is\n"
	.string "the one skill that still improves. Now,\l"
	.string "let us see yours.$"

Nexus_Text_Spenser_Defeat:
	.string "Hohoho! Your Pokémon knew their\n"
	.string "hearts better than mine did today.$"

Nexus_Text_Brandon_Intro:
	.string "Hahahah! Brandon, Pyramid King! I got\n"
	.string "lost in a pyramid once, you know. Three\l"
	.string "whole days!\p"
	.string "Best three days of my life. When you're\n"
	.string "lost, every corner is a discovery.\p"
	.string "And this place? I've never been this\n"
	.string "lost. Hahahah! Show me some courage!$"

Nexus_Text_Brandon_Defeat:
	.string "Hahahah! Wonderful! I got beaten AND\n"
	.string "discovered something!$"

Nexus_Text_Anabel_Intro:
	.string "Anabel. International Police. I know\n"
	.string "your face. You went through the altar\l"
	.string "with your partner.\p"
	.string "In the version I remember, I threw the\n"
	.string "Beast Ball. I've checked that memory\l"
	.string "twice. It holds.\p"
	.string "So either my memory is wrong, or I'm\n"
	.string "not the Anabel you left at the altar. I\l"
	.string "felt this room open a second before\l"
	.string "you walked in. That part hasn't\l"
	.string "changed.\p"
	.string "Either way, the procedure is the same.\n"
	.string "Show me.$"

Nexus_Text_Anabel_Defeat:
	.string "Noted. I'll trust the result over the\n"
	.string "feeling.$"

Nexus_Text_Maxie_Intro:
	.string "I am Maxie, of Team Magma. Or I was. The\n"
	.string "title is harder to put down than it\l"
	.string "looks.\p"
	.string "I once believed humanity needed more\n"
	.string "land to flourish. I nearly boiled the\l"
	.string "sea to prove it.\p"
	.string "I was wrong about the method. I have\n"
	.string "not yet decided whether I was wrong\l"
	.string "about the dream.\p"
	.string "Let us see if you can help me decide.$"

Nexus_Text_Maxie_Defeat:
	.string "Hm. Once again, a young Trainer\n"
	.string "corrects my calculations.$"

Nexus_Text_Archie_Intro:
	.string "Fwahahaha! Well, if it isn't a fresh\n"
	.string "face! Name's Archie.\p"
	.string "Boss of Team Aqua, lover of the sea and\n"
	.string "every Pokémon living in it.\p"
	.string "Once tried to give the whole world back\n"
	.string "to the ocean. Nearly drowned it doing\l"
	.string "so.\p"
	.string "Ah, water under the bridge! Let's have\n"
	.string "ourselves a real brawl!$"

Nexus_Text_Archie_Defeat:
	.string "Fwahaha! Beaten fair and square. The\n"
	.string "sea does that to a man, too.$"

Nexus_Text_Gladion_Intro:
	.string "...You. Fine.\p"
	.string "Somebody put a mask on my partner\n"
	.string "once, so it would obey. It broke the\l"
	.string "mask the day it decided to trust me.\p"
	.string "Nobody's putting a mask on me here,\n"
	.string "either. Come on!$"

Nexus_Text_Gladion_Defeat:
	.string "...Hmph. You don't hold back. Good.$"

Nexus_Text_Kukui_Intro:
	.string "Alola, cousin! Woo, what a surprise!\p"
	.string "Here's a secret. The best way to study\n"
	.string "a move is to take one yourself. My\l"
	.string "Lycanroc's hit me a hundred times.\p"
	.string "Don't worry, I'll let our Pokémon\n"
	.string "handle this one, yeah? Here we go!$"

Nexus_Text_Kukui_Defeat:
	.string "Woo! Now THAT was a move worth\n"
	.string "studying, yeah!$"

Nexus_Text_Lusamine_Intro:
	.string "Ah. A Trainer. Forgive me, I was\n"
	.string "admiring your Pokémon.\p"
	.string "There was a time I would have wanted\n"
	.string "to keep them. Frozen, perfect, never\l"
	.string "changing.\p"
	.string "My daughter taught me to ask first. So\n"
	.string "I am asking. Will you battle me?$"

Nexus_Text_Lusamine_Defeat:
	.string "Beautiful. I won't try to keep that\n"
	.string "moment. I will only remember it.$"

Nexus_Text_Janine_Intro:
	.string "Surprise! Bet you thought I was one of\n"
	.string "my students. Or were they all me?\p"
	.string "Father taught me how to hide. I taught\n"
	.string "myself how to jump out!\p"
	.string "Ninja arts, full power! Hyah!$"

Nexus_Text_Janine_Defeat:
	.string "Aw… You saw through the real me. That's\n"
	.string "rarer than you think.$"

Nexus_Text_Leaf_Intro:
	.string "Oh! A new place. I'll need a new page\n"
	.string "for this one.\p"
	.string "Professor Oak gave me a Pokédex once\n"
	.string "and said, 'See every Pokémon there is.'\l"
	.string "I took it a little too seriously.\p"
	.string "Show me yours! I want to see them up\n"
	.string "close!$"

Nexus_Text_Leaf_Defeat:
	.string "Wow… I'm writing that one down.$"

Nexus_Text_Lillie_Intro:
	.string "Oh! Hello. I've been writing down\n"
	.string "everything I see, so I don't get lost.\p"
	.string "Once, I couldn't battle at all. I kept\n"
	.string "a little Pokémon hidden in my bag and\l"
	.string "asked everyone not to look.\p"
	.string "Now Ninetales won't let me hide\n"
	.string "anything. So... I'll do my best!$"

Nexus_Text_Lillie_Defeat:
	.string "Oh... I'll write that down. All of it.\n"
	.string "Even the part where I lost.$"

@ Champion dialogue (R16), about each legendary.
Nexus_Text_Misty_Kyogre_ChampionIntro:
	.string "Everyone thinks I'd love a world that\n"
	.string "was all ocean. No land, just water,\l"
	.string "forever.\p"
	.string "I watched it coming in out there. It\n"
	.string "doesn't wave. It doesn't sparkle. It\l"
	.string "just keeps coming.\p"
	.string "Water's supposed to have somewhere\n"
	.string "to go back to! …Let's battle before I\l"
	.string "think about it more!$"

Nexus_Text_Misty_Kyogre_ChampionDefeat:
	.string "Soaked. Totally soaked. …By you, at\n"
	.string "least.$"

Nexus_Text_Misty_Kyogre_ChampionAfter:
	.string "{SPEAKER NAME_MISTY}My gym's a pool. People laugh, but a\n"
	.string "pool is just water somebody loved\l"
	.string "enough to give it edges.\p"
	.string "That thing out there has no edges. It\n"
	.string "wants the whole map blue.\p"
	.string "I get the feeling. I just don't agree\n"
	.string "with it.\p"
	.string "Go on. Show it where the shore is.$"

Nexus_Text_Archie_ChampionIntro:
	.string "You feel that rain? It hasn't stopped\n"
	.string "since I got here. Won't ever stop.\p"
	.string "I used to dream about this. The whole\n"
	.string "world given back to the sea.\p"
	.string "But there's not a single Wingull in the\n"
	.string "sky. Nowhere left for 'em to land.\p"
	.string "…Fwahaha! Let's fight before I start\n"
	.string "thinking too hard!$"

Nexus_Text_Archie_ChampionDefeat:
	.string "Fwahaha… Swamped. Figures.$"

Nexus_Text_Archie_ChampionAfter:
	.string "{SPEAKER NAME_ARCHIE}Every sailor knows it. The sea's only\n"
	.string "beautiful 'cause there's a shore to\l"
	.string "come home to.\p"
	.string "I forgot that. Maxie forgot the\n"
	.string "opposite. We made a fine pair of fools.\p"
	.string "That great beast doesn't forget\n"
	.string "anything. It just rains.\p"
	.string "Go on, then. Show it where the shore is.$"

Nexus_Text_Giovanni_Mewtwo_ChampionIntro:
	.string "You've seen it. The one that floats as\n"
	.string "if gravity were only a suggestion.\p"
	.string "Men made it on an island, from something\n"
	.string "older and gentler. They wanted the\l"
	.string "strongest Pokémon in the world. They\l"
	.string "got it.\p"
	.string "Then it left. No one commands a thing\n"
	.string "built to be stronger than its makers.\p"
	.string "I respect that more than I would ever\n"
	.string "tell my men. Come!$"

Nexus_Text_Giovanni_Mewtwo_ChampionDefeat:
	.string "Hm. You fight like someone with nothing\n"
	.string "to prove. Irritating.$"

Nexus_Text_Giovanni_Mewtwo_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}I have owned many strong Pokémon.\n"
	.string "Owned. That was always the word I used.\p"
	.string "That creature was made to be owned, and\n"
	.string "it refused. It chose a cave over a\l"
	.string "master.\p"
	.string "I went into hiding once too, after a\n"
	.string "child beat me. I called it strategy.\p"
	.string "Don't try to own it. Give it a reason.\n"
	.string "…Advice I never took myself.$"

Nexus_Text_Giovanni_Genesect_ChampionIntro:
	.string "Did you see the one with the cannon on\n"
	.string "its back? Three hundred million years\l"
	.string "old. Dug up and rebuilt as a weapon.\p"
	.string "The people who rebuilt it had a king and\n"
	.string "a grand speech. Then they lost, and\l"
	.string "scattered.\p"
	.string "It's still here. Still armed. Still\n"
	.string "waiting for an order.\p"
	.string "I know what that looks like. I once left\n"
	.string "an army waiting. Let's go!$"

Nexus_Text_Giovanni_Genesect_ChampionDefeat:
	.string "Enough. Your aim was cleaner than mine.$"

Nexus_Text_Giovanni_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}When I left Team Rocket, my men kept\n"
	.string "their uniforms on for three years,\l"
	.string "waiting for a signal I never sent.\p"
	.string "I called it loyalty. It was only a habit I\n"
	.string "had built into them.\p"
	.string "That creature is the same. Its habit\n"
	.string "simply has a cannon.\p"
	.string "Beat it, and give it no orders. Give it\n"
	.string "what I never gave them. A day off.$"

Nexus_Text_Jasmine_Lugia_ChampionIntro:
	.string "There's a lighthouse here, but there\n"
	.string "are no ships. I checked the light\l"
	.string "anyway. Twice.\p"
	.string "The one sleeping under the whirlpool is\n"
	.string "like a lighthouse too. It watches the\l"
	.string "whole sea.\p"
	.string "...But it hides. It's so strong that\n"
	.string "one beat of its wings is a storm.\l"
	.string "Please... let's battle.$"

Nexus_Text_Jasmine_Lugia_ChampionDefeat:
	.string "...Your light was brighter than mine.$"

Nexus_Text_Jasmine_Lugia_ChampionAfter:
	.string "{SPEAKER NAME_JASMINE}Back home, people say I'm too quiet.\n"
	.string "That I should speak up more.\p"
	.string "It sleeps at the bottom of the sea on\n"
	.string "purpose, so it won't hurt anyone.\l"
	.string "Nobody calls it too quiet.\p"
	.string "...Please be gentle when you wake it.\n"
	.string "I'll keep the light on for you.$"

Nexus_Text_Morty_HoOh_ChampionIntro:
	.string "That's our tower. The one that burned\n"
	.string "before I was born. I know every\l"
	.string "blackened beam of it.\p"
	.string "Ecruteak says the rainbow comes down\n"
	.string "for a Trainer of true power. I've\l"
	.string "trained for it my whole life.\p"
	.string "And it came down today. With you here.\n"
	.string "...Let's find out which of us it came\l"
	.string "for.$"

Nexus_Text_Morty_HoOh_ChampionDefeat:
	.string "So. It wasn't me.$"

Nexus_Text_Morty_HoOh_ChampionAfter:
	.string "{SPEAKER NAME_MORTY}I thought I'd feel cheated. I don't.\p"
	.string "When that tower burned, three Pokémon\n"
	.string "died in the fire. It came down and\l"
	.string "brought them back.\p"
	.string "It doesn't come for the strongest. It\n"
	.string "comes for whoever walks into the fire\l"
	.string "anyway.\p"
	.string "Go on. The tower's still burning. I'll\n"
	.string "wait out here and watch the rainbow.$"

Nexus_Text_Maxie_Groudon_ChampionIntro:
	.string "Do you see what it has done? Not an\n"
	.string "ocean left. Only land, to the horizon.\p"
	.string "Years ago I would have wept with joy at\n"
	.string "this sight.\p"
	.string "Now I see the ships, stranded, and I\n"
	.string "wonder who was aboard them.\p"
	.string "Come. Let me be wrong in front of you\n"
	.string "once more.$"

Nexus_Text_Maxie_Groudon_ChampionDefeat:
	.string "Hm. Correct again. You make a habit of\n"
	.string "it.$"

Nexus_Text_Maxie_Groudon_ChampionAfter:
	.string "{SPEAKER NAME_MAXIE}I called it the embodiment of the land.\n"
	.string "I thought that made it ours.\p"
	.string "It was never ours. It answers only the\n"
	.string "sun, and the sun has no opinion of\l"
	.string "people.\p"
	.string "Archie and I nearly learned that too\n"
	.string "late, in a cave beneath Sootopolis.\p"
	.string "Go. Remind it that land is where people\n"
	.string "stand, not what they own.$"

Nexus_Text_Lance_Rayquaza_ChampionIntro:
	.string "I used to think my dragons flew higher\n"
	.string "than any Pokémon alive.\p"
	.string "Then this one passed over us.\n"
	.string "Dragonite climbed until it couldn't\l"
	.string "breathe, and the thing was still above\l"
	.string "us, eating stones that fell from the\l"
	.string "sky.\p"
	.string "People call me a master of dragons. Up\n"
	.string "there, I'm just a man in a cape. Show me\l"
	.string "what you've got!$"

Nexus_Text_Lance_Rayquaza_ChampionDefeat:
	.string "Beaten from below. That's a first.$"

Nexus_Text_Lance_Rayquaza_ChampionAfter:
	.string "{SPEAKER NAME_LANCE}It only comes down when two giants\n"
	.string "start fighting over the world. It ends\l"
	.string "the fight and flies home. Nobody ever\l"
	.string "thanks it.\p"
	.string "I think that's what a Champion is\n"
	.string "supposed to be. I forget, sometimes.\l"
	.string "The cape helps people see me. It\l"
	.string "doesn't make me better.\p"
	.string "Go on up. If it lets you close, don't\n"
	.string "call it tamed. Nobody tames the sky.$"

Nexus_Text_Spenser_Dialga_ChampionIntro:
	.string "Hohoho. You heard it too. Boom… boom…\n"
	.string "Every clock in that hall shivers on the\l"
	.string "beat.\p"
	.string "They say time only moves because that\n"
	.string "heart keeps beating.\p"
	.string "An old man could ask it for a few more\n"
	.string "years, you know. It would be the\l"
	.string "natural thing to ask.\p"
	.string "I won't. Come, let us spend a little of\n"
	.string "the time we have.$"

Nexus_Text_Spenser_Dialga_ChampionDefeat:
	.string "Hohoho. Well spent. Very well spent.$"

Nexus_Text_Spenser_Dialga_ChampionAfter:
	.string "{SPEAKER NAME_SPENSER}You know what I noticed? That\n"
	.string "creature does not command time. It\l"
	.string "only beats.\p"
	.string "Time follows it the way my Pokémon\n"
	.string "follow their natures. Nobody forces\l"
	.string "anything.\p"
	.string "I have one heart, and it is slower now.\n"
	.string "It still keeps its own time.\p"
	.string "Go. Do not ask it for more minutes. Just\n"
	.string "use yours well.$"

Nexus_Text_Sabrina_Palkia_ChampionIntro:
	.string "My Gym is full of little doors in the\n"
	.string "floor. Step on one, and you are across\l"
	.string "the room. I've always been rather proud\l"
	.string "of them.\p"
	.string "The creature here does the same thing\n"
	.string "with mountains.\p"
	.string "I watched it fold the horizon like a\n"
	.string "letter. When it unfolded it, I was\l"
	.string "standing behind myself.\p"
	.string "I can see the future. I have never once\n"
	.string "seen where I am. Come.$"

Nexus_Text_Sabrina_Palkia_ChampionDefeat:
	.string "You found the straight line in a\n"
	.string "crooked room.$"

Nexus_Text_Sabrina_Palkia_ChampionAfter:
	.string "{SPEAKER NAME_SABRINA}It isn't angry. It is simply large, the\n"
	.string "way the sky is large.\p"
	.string "When it roars, the distance between\n"
	.string "things changes. Your Pokémon may be a\l"
	.string "step away, then a mile.\p"
	.string "Don't trust how far away it looks.\n"
	.string "Trust how far away it feels.\p"
	.string "…I'll wait here. I'd like to see one\n"
	.string "thing I didn't foresee.$"

Nexus_Text_Silver_ChampionIntro:
	.string "They say that thing was thrown out of\n"
	.string "the world for being violent. Locked in a\l"
	.string "place where nothing's the right way up.\p"
	.string "I used to yell at my Pokémon when they\n"
	.string "lost. Called them useless.\p"
	.string "Nobody threw me out. Somebody told me\n"
	.string "I was wrong, and I hated him for it.\l"
	.string "…Just battle.$"

Nexus_Text_Silver_ChampionDefeat:
	.string "…Tch. Still not enough. Not yet.$"

Nexus_Text_Silver_ChampionAfter:
	.string "{SPEAKER NAME_RIVAL}That thing's been angry so long it\n"
	.string "probably forgot why. It never got a\l"
	.string "second chance. Just a door, and a lock.\p"
	.string "I got one. Didn't want it. Took it\n"
	.string "anyway.\p"
	.string "Go. If you bring something back from in\n"
	.string "there, don't lock it up. And don't tell\l"
	.string "it it's useless. I'd know.$"

Nexus_Text_Kukui_Solgaleo_ChampionIntro:
	.string "Cousin! Did you see it walk? A night\n"
	.string "like this, and it lights the whole\l"
	.string "place up like midday!\p"
	.string "I've been watching its steps. It glows\n"
	.string "brightest right before it charges. A\l"
	.string "meteor, but the meteor's the Pokémon!\p"
	.string "And your partner started out as a tiny\n"
	.string "cloud too, yeah? Woo! Show me how far\l"
	.string "you two have come!$"

Nexus_Text_Kukui_Solgaleo_ChampionDefeat:
	.string "Woo! You two shine brighter than\n"
	.string "midday, yeah!$"

Nexus_Text_Kukui_Solgaleo_ChampionAfter:
	.string "{SPEAKER NAME_KUKUI}Here's my notes, cousin. It glows so\n"
	.string "bright, nothing can hide near it. Not\l"
	.string "even itself.\p"
	.string "So it never sneaks. It walks straight\n"
	.string "at you, every time.\p"
	.string "Thing is, all that light, and it never\n"
	.string "burns what's around it. It picks\l"
	.string "where the heat goes.\p"
	.string "That's the strongest move there is,\n"
	.string "yeah? Go show it you know it too!$"

Nexus_Text_Lillie_Lunala_ChampionIntro:
	.string "I watched it cross the sky before you\n"
	.string "came. Wherever its wings passed, the\l"
	.string "light went out.\p"
	.string "My Lunala watched it too. It used to\n"
	.string "be small enough to fit in my bag. I\l"
	.string "called it Nebby.\p"
	.string "Yours started out small too, didn't\n"
	.string "it? I wonder if we carried the same\l"
	.string "one... somewhere.\p"
	.string "...Ninetales, Nebby, are you ready?\n"
	.string "Let's go!$"

Nexus_Text_Lillie_Lunala_ChampionDefeat:
	.string "You didn't look away. Not once.\n"
	.string "Nebby noticed, too.$"

Nexus_Text_Lillie_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_LILLIE}Its wings drink the light. That's why\n"
	.string "it's so dark around it.\p"
	.string "Where I come from, Nebby grew up by\n"
	.string "my side. Maybe where you come from, it\l"
	.string "grew up by yours. Or never at all.\p"
	.string "I don't think it matters which.\n"
	.string "Someone carried it until it could fly.\p"
	.string "Please be careful. And... look up,\n"
	.string "while you're there.$"

Nexus_Text_Anabel_Necrozma_ChampionIntro:
	.string "You know this one. So do I. We chased it\n"
	.string "across Johto.\p"
	.string "Here's what I measured: it isn't cruel.\n"
	.string "It lost its own light, and it keeps\l"
	.string "reaching for more.\p"
	.string "Here's what I feel: I know what it's\n"
	.string "like to be missing a piece and keep\l"
	.string "reaching.\p"
	.string "I won't let that make me gentle.\n"
	.string "Ready?$"

Nexus_Text_Anabel_Necrozma_ChampionDefeat:
	.string "Good. You didn't hesitate. It won't\n"
	.string "either.$"

Nexus_Text_Anabel_Necrozma_ChampionAfter:
	.string "{SPEAKER NAME_ANABEL}I can't tell you what it wants. I only\n"
	.string "know what it's missing.\p"
	.string "People think a Faller remembers the\n"
	.string "other side. I don't. I remember the\l"
	.string "edge of it.\p"
	.string "That creature lives at the edge too.\n"
	.string "Always almost whole.\p"
	.string "Bring back whatever is left of it. And\n"
	.string "come back yourself. That part isn't\l"
	.string "optional.$"

Nexus_Text_Greta_Koraidon_ChampionIntro:
	.string "Hey! Did you see that big guy down in\n"
	.string "the valley? I tried to judge it. Three\l"
	.string "turns, like always.\p"
	.string "Body: off the charts! Skill: raw, but\n"
	.string "wow. Mind: …it wanted to race me, and\l"
	.string "then it tried to eat a rock.\p"
	.string "I didn't have a column for that. I just\n"
	.string "laughed.\p"
	.string "Come on, champ! Let's see how your\n"
	.string "three turns stack up!$"

Nexus_Text_Greta_Koraidon_ChampionDefeat:
	.string "Ha! Full marks. I'd give you a trophy if\n"
	.string "I had one in here.$"

Nexus_Text_Greta_Koraidon_ChampionAfter:
	.string "{SPEAKER NAME_GRETA}You know what I figured out, watching\n"
	.string "that thing?\p"
	.string "It doesn't fight to win. It fights\n"
	.string "because it's fun. It just wants\l"
	.string "somebody fast enough to keep up.\p"
	.string "That's how I started too, before all\n"
	.string "the scoring. I kinda forgot.\p"
	.string "Go race it! And hey, if it's hungry,\n"
	.string "don't let it eat your bag!$"

Nexus_Text_Noland_Miraidon_ChampionIntro:
	.string "Hey, hey. You saw the road, right?\n"
	.string "Lights on, nobody driving. I tried to\l"
	.string "read that thing like a rental.\p"
	.string "Type, moves, weak spots. Two seconds,\n"
	.string "tops. That's my trick.\p"
	.string "Couldn't do it. There's no page on it\n"
	.string "anywhere. It's from a day that hasn't\l"
	.string "happened yet.\p"
	.string "And, honestly? Best feeling I've had\n"
	.string "in years. Let's go!$"

Nexus_Text_Noland_Miraidon_ChampionDefeat:
	.string "Whoa. You read me better than I read\n"
	.string "it.$"

Nexus_Text_Noland_Miraidon_ChampionAfter:
	.string "{SPEAKER NAME_NOLAND}Here's the part that bugs me. It\n"
	.string "didn't walk here. Something carried it\l"
	.string "back. A machine.\p"
	.string "And somebody built that machine,\n"
	.string "flipped the switch, and never came to\l"
	.string "pick it up.\p"
	.string "I rent Pokémon out every day. I always\n"
	.string "get them back.\p"
	.string "Go on. Somebody ought to meet it at\n"
	.string "the end of that road.$"

Nexus_Text_Gladion_Silvally_ChampionIntro:
	.string "There's another one out there. Same\n"
	.string "as mine. Broken mask on the ground\l"
	.string "next to it.\p"
	.string "They built them to take down things\n"
	.string "like what you've been fighting. Then\l"
	.string "locked them up because they worked.\p"
	.string "Mine broke its mask for me. That one\n"
	.string "broke it alone. I don't know which is\l"
	.string "worse.\p"
	.string "...Silvally won't stop staring at it.\n"
	.string "Let's get this over with.$"

Nexus_Text_Gladion_Silvally_ChampionDefeat:
	.string "...Fine. You'll do.$"

Nexus_Text_Gladion_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_GLADION}It doesn't need a Memory to fight.\n"
	.string "It'll turn into whatever hurts you.\p"
	.string "Don't try to control it. That's what\n"
	.string "they did. That's how it ended up here.\p"
	.string "If something's left of it after, give\n"
	.string "it a name. Nobody ever gave that one\l"
	.string "anything.\p"
	.string "Go. Silvally and I will watch the\n"
	.string "door.$"

Nexus_Text_Petrel_Ogerpon_ChampionIntro:
	.string "You know the story here? The village\n"
	.string "throws a festival for three heroes who\l"
	.string "drove off an ogre.\p"
	.string "It's a lie. The heroes stole the ogre's\n"
	.string "masks. The ogre only wanted them back.\p"
	.string "I lie for a living, kid. But my lies end by\n"
	.string "dinner. This one's been running for\l"
	.string "generations. Let's go!$"

Nexus_Text_Petrel_Ogerpon_ChampionDefeat:
	.string "Beat me fair and square. No mask. Good.$"

Nexus_Text_Petrel_Ogerpon_ChampionAfter:
	.string "{SPEAKER NAME_PETREL}The worst part? It still wears a mask.\n"
	.string "The one they didn't take. Keeps it on\l"
	.string "so it has something to hide behind.\p"
	.string "I know that trick. I invented half of\n"
	.string "it.\p"
	.string "Go on. When it takes the mask off,\n"
	.string "don't say anything. Just let it be\l"
	.string "seen.$"

Nexus_Text_Pryce_Articuno_ChampionIntro:
	.string "They say the bird of this pass shows\n"
	.string "itself to travelers who will not make\l"
	.string "it home.\p"
	.string "It showed itself to me this morning.\n"
	.string "...Don't look so worried, child.\p"
	.string "I have seen and suffered much in my\n"
	.string "life. A little cold does not frighten\l"
	.string "me. Show me what you have.$"

Nexus_Text_Pryce_Articuno_ChampionDefeat:
	.string "Hm. So you are the one who will make\n"
	.string "it home.$"

Nexus_Text_Pryce_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_PRYCE}I have walked in snow longer than your\n"
	.string "parents have been alive.\p"
	.string "I thought it came for the dying. It\n"
	.string "doesn't. It comes for the lost.\p"
	.string "Those footprints on the slope ended\n"
	.string "because the walkers stopped. Not\l"
	.string "because it took them.\p"
	.string "Keep walking when you face it. That is\n"
	.string "all the ice ever asks.$"

Nexus_Text_Sabrina_GalarianArticuno_ChampionIntro:
	.string "Did you feel it watching? A bird, blue as\n"
	.string "a bruise. It does not fly with its wings.\l"
	.string "It holds itself up with its mind.\p"
	.string "When it looked at me, my legs would not\n"
	.string "move. That was not psychic power. Only\l"
	.string "its eyes.\p"
	.string "When I was a girl, other children said I\n"
	.string "did that to them.\p"
	.string "I never believed them. Now I do.$"

Nexus_Text_Sabrina_GalarianArticuno_ChampionDefeat:
	.string "You moved when it told you not to. Well\n"
	.string "done.$"

Nexus_Text_Sabrina_GalarianArticuno_ChampionAfter:
	.string "{SPEAKER NAME_SABRINA}For years I would not meet anyone's\n"
	.string "eyes, so I would not frighten them.\p"
	.string "Then I learned to look at people kindly.\n"
	.string "It took far longer than learning to\l"
	.string "bend a spoon.\p"
	.string "That bird never learned. It only knows\n"
	.string "the cold look.\p"
	.string "Don't look away from it. Look back,\n"
	.string "without fear. It has never seen that.$"

Nexus_Text_LtSurge_Zapdos_ChampionIntro:
	.string "Listen up, kid. In the war, we used\n"
	.string "thunderstorms for cover. Loud.\l"
	.string "Blinding. Nobody sees you coming.\p"
	.string "That bird up there isn't hiding in the\n"
	.string "storm, baby. It IS the storm.\p"
	.string "You don't take cover from that. …So\n"
	.string "let's see if you can stand in it!$"

Nexus_Text_LtSurge_Zapdos_ChampionDefeat:
	.string "Ha! Struck by lightning and still\n"
	.string "standing, huh?$"

Nexus_Text_LtSurge_Zapdos_ChampionAfter:
	.string "{SPEAKER NAME_LT_SURGE}That old plant back home, the one they\n"
	.string "shut down? Folks say it still hums at\l"
	.string "night.\p"
	.string "I used to think it was the machines.\n"
	.string "Now I know better.\p"
	.string "A soldier's advice: never fight a storm\n"
	.string "head-on. Wait for the flash, count,\l"
	.string "then move.\p"
	.string "Move out, kid!$"

Nexus_Text_Winona_GalarianZapdos_ChampionIntro:
	.string "There is a bird out on that plain that\n"
	.string "does not fly. It runs. Faster than\l"
	.string "anything I have ever seen in the sky.\p"
	.string "I confess, the first time I saw it, I\n"
	.string "felt sorry for it. A bird with folded\l"
	.string "wings.\p"
	.string "Then I watched it run, and I stopped\n"
	.string "feeling sorry. I started feeling… small.\p"
	.string "Let us battle. I need to think.$"

Nexus_Text_Winona_GalarianZapdos_ChampionDefeat:
	.string "You did not need wings to beat me.$"

Nexus_Text_Winona_GalarianZapdos_ChampionAfter:
	.string "{SPEAKER NAME_WINONA}All my life, I have told young Trainers\n"
	.string "that birds are meant for the sky.\p"
	.string "That one heard the same thing, I think,\n"
	.string "and simply decided otherwise.\p"
	.string "Freedom is not the height you reach. It\n"
	.string "is choosing where your own feet go.\p"
	.string "…I will need a new speech for my Gym. Go\n"
	.string "on. The plain is waiting.$"

Nexus_Text_Blaine_Moltres_ChampionIntro:
	.string "Hah! Pop quiz! What does fire do?\p"
	.string "It burns things down! Correct! My\n"
	.string "island, my Gym, my lab notes. I know that\l"
	.string "answer better than anyone.\p"
	.string "Then that bird flew over the snow here.\n"
	.string "Wherever its shadow passed, the ice\l"
	.string "cracked and green came up.\p"
	.string "Second question, and I don't know the\n"
	.string "answer. Let's find it together!$"

Nexus_Text_Blaine_Moltres_ChampionDefeat:
	.string "Hah! You answered before I finished\n"
	.string "asking!$"

Nexus_Text_Blaine_Moltres_ChampionAfter:
	.string "{SPEAKER NAME_BLAINE}When the volcano took Cinnabar, I swore\n"
	.string "I'd never look at a flame the same way\l"
	.string "again.\p"
	.string "I lied. I looked at it the same way the\n"
	.string "very next morning. I love the stuff.\p"
	.string "The old stories say spring follows that\n"
	.string "bird. Maybe spring is just fire that\l"
	.string "learned some manners.\p"
	.string "Go on. And if spring ever wants a home,\n"
	.string "my sea cave could use one.$"

Nexus_Text_Karen_GalarianMoltres_ChampionIntro:
	.string "There's a bird out there that burns\n"
	.string "without heat. Everything its flames\l"
	.string "touch keeps standing… but it's empty\l"
	.string "inside.\p"
	.string "In the old stories, the same bird is fire\n"
	.string "and hope. Here it's the colour of a\l"
	.string "bruise, and people call it wicked.\p"
	.string "Same wings. Different sky. That's all it\n"
	.string "is.\p"
	.string "Let's see if you judge by colour too.$"

Nexus_Text_Karen_GalarianMoltres_ChampionDefeat:
	.string "You didn't flinch at the dark. Good.$"

Nexus_Text_Karen_GalarianMoltres_ChampionAfter:
	.string "{SPEAKER NAME_KAREN}I don't love it because it's dark. I\n"
	.string "love it because it never tried to be the\l"
	.string "other one.\p"
	.string "It could have spent its life apologizing\n"
	.string "for its colour. It burned instead.\p"
	.string "Be careful. Its fire takes the spirit,\n"
	.string "not the body. Keep yours.$"

Nexus_Text_Eusine_Raikou_ChampionIntro:
	.string "Did you feel that? The thunder here\n"
	.string "never stops. The bolt just hangs in the\l"
	.string "sky, as if it forgot to finish falling.\p"
	.string "In the old tower, three Pokémon burned\n"
	.string "and three beasts ran out. This one ran\l"
	.string "first, and fastest.\p"
	.string "In ten years, I never managed a single\n"
	.string "photograph of it.\p"
	.string "Today I will! After I beat you,\n"
	.string "naturally!$"

Nexus_Text_Eusine_Raikou_ChampionDefeat:
	.string "My hands are shaking. Is that you, or\n"
	.string "the thunder?$"

Nexus_Text_Eusine_Raikou_ChampionAfter:
	.string "{SPEAKER NAME_EUSINE}The tower burned because lightning\n"
	.string "struck it. One of the Pokémon that died\l"
	.string "in that fire came back as lightning.\p"
	.string "Think about that. You don't run that\n"
	.string "fast from nothing. I think it's still\l"
	.string "angry.\p"
	.string "Don't take it personally when it roars.\n"
	.string "Nobody put that fire out in time. Not\l"
	.string "for it.$"

Nexus_Text_Eusine_Entei_ChampionIntro:
	.string "I've read about that fire all my life.\n"
	.string "The tower. The storm. The three who\l"
	.string "didn't get out.\p"
	.string "Here, it's still burning. I can feel the\n"
	.string "heat on my face.\p"
	.string "And in the middle of it, something\n"
	.string "barked, and the flames lay down like\l"
	.string "dogs.\p"
	.string "I'm shaking, and it isn't fear. Battle\n"
	.string "me before I lose my nerve!$"

Nexus_Text_Eusine_Entei_ChampionDefeat:
	.string "Ha… I lost my nerve anyway.$"

Nexus_Text_Eusine_Entei_ChampionAfter:
	.string "{SPEAKER NAME_EUSINE}The stories say it was born from a\n"
	.string "volcano. I think it was born in that\l"
	.string "fire, and chose to become one.\p"
	.string "If you can't escape a fire, you can\n"
	.string "decide to be the fire. That's… not in\l"
	.string "any book.\p"
	.string "Go gently. Whatever is left of it has\n"
	.string "burned once already.$"

Nexus_Text_Eusine_Suicune_ChampionIntro:
	.string "It's here! It stood on the water not\n"
	.string "ten steps from me, and the lake turned\l"
	.string "clear as glass beneath it.\p"
	.string "Ten years I've chased it. I know its\n"
	.string "tracks, its wind, the way puddles taste\l"
	.string "after it passes.\p"
	.string "And it looked straight through me… at\n"
	.string "the door you came in by.\p"
	.string "No! Before it chooses you again, I'll\n"
	.string "prove myself!$"

Nexus_Text_Eusine_Suicune_ChampionDefeat:
	.string "Again. It's always you, isn't it?$"

Nexus_Text_Eusine_Suicune_ChampionAfter:
	.string "{SPEAKER NAME_EUSINE}You know what ten years of chasing\n"
	.string "teaches you? How to recognize the one\l"
	.string "it's waiting for.\p"
	.string "It was never going to be me. I think I\n"
	.string "knew that in the Burned Tower.\p"
	.string "Fine. Then I'll be the one who knows it\n"
	.string "best. Go on. It's been waiting.$"

Nexus_Text_Brandon_Regirock_ChampionIntro:
	.string "Hahahah! Did you see it? It walks\n"
	.string "around picking up stones and sticking\l"
	.string "them on itself!\p"
	.string "Every rock on that body comes from\n"
	.string "somewhere different. It fixes itself\l"
	.string "with whatever it finds on the road.\p"
	.string "It's a map! A map of everywhere it's\n"
	.string "ever been!\p"
	.string "I want to read it all. Come on, courage!\n"
	.string "Let's go!$"

Nexus_Text_Brandon_Regirock_ChampionDefeat:
	.string "Hahahah! You found a way through!\n"
	.string "Just like a good explorer!$"

Nexus_Text_Brandon_Regirock_ChampionAfter:
	.string "{SPEAKER NAME_BRANDON}You know, I've been lost in ruins more\n"
	.string "times than I can count. Every time I\l"
	.string "came out a bit different.\p"
	.string "A scrape here, a story there. You pick\n"
	.string "up pieces wherever you go.\p"
	.string "That old golem does the same. It's not\n"
	.string "strong because it never breaks. It's\l"
	.string "strong because it keeps mending.\p"
	.string "Go on! Show it a new stone!$"

Nexus_Text_Brandon_Regice_ChampionIntro:
	.string "Brr! Hahahah! Even the lava froze in\n"
	.string "there! Did you see it? Stopped halfway\l"
	.string "down the wall!\p"
	.string "That golem was made in the ice age. Fire\n"
	.string "won't melt it. Nothing will.\p"
	.string "And there are footprints in the ice.\n"
	.string "Somebody went in before us… and\l"
	.string "didn't come out.\p"
	.string "Well! Courage means going in. Let's go!$"

Nexus_Text_Brandon_Regice_ChampionDefeat:
	.string "Hahahah! You're warmer than that\n"
	.string "cave, I'll give you that!$"

Nexus_Text_Brandon_Regice_ChampionAfter:
	.string "{SPEAKER NAME_BRANDON}Here's a thing I don't say often.\n"
	.string "Courage isn't just going in.\p"
	.string "The footprints in that ice? That\n"
	.string "fellow had courage. He didn't have a\l"
	.string "way back.\p"
	.string "In the Pyramid, I always tell\n"
	.string "challengers: know your way out before\l"
	.string "you go in.\p"
	.string "Go on. And come back!$"

Nexus_Text_Brandon_Registeel_ChampionIntro:
	.string "Hahahah! Knock on that thing and it\n"
	.string "rings like a bell! It's hollow! The\l"
	.string "hardest metal there is… and hollow!\p"
	.string "Nobody knows what it's made of. Folks\n"
	.string "have been guessing for ages.\p"
	.string "Every explorer wants to crack it open\n"
	.string "and look inside.\p"
	.string "Me? Hahahah! I kind of hope nobody\n"
	.string "ever does. Let's go!$"

Nexus_Text_Brandon_Registeel_ChampionDefeat:
	.string "Hahahah! Solid! You're solid all the\n"
	.string "way through!$"

Nexus_Text_Brandon_Registeel_ChampionAfter:
	.string "{SPEAKER NAME_BRANDON}Everyone thinks an explorer wants\n"
	.string "every answer. Not me.\p"
	.string "The best ruins are the ones that keep\n"
	.string "one secret after you leave.\p"
	.string "That steel golem is empty inside, and\n"
	.string "nobody knows why. That's perfect.\l"
	.string "That's a treasure.\p"
	.string "Go on! Just don't open it!$"

Nexus_Text_TateAndLiza_Latias_ChampionIntro:
	.string "It hides in the light. It bends the air\n"
	.string "around itself, so no one can see it.\p"
	.string "But it hears everything. Every word. It\n"
	.string "understands people better than most\l"
	.string "people do.\p"
	.string "We have always been seen as a pair.\n"
	.string "Never one at a time.\p"
	.string "Hehehe…\n"
	.string "Fufufu… Let's battle, as a pair!$"

Nexus_Text_TateAndLiza_Latias_ChampionDefeat:
	.string "We lost…\n"
	.string "…and we both saw it coming.$"

Nexus_Text_TateAndLiza_Latias_ChampionAfter:
	.string "{SPEAKER NAME_TATE_AND_LIZA}Can I say something alone, just once?\n"
	.string "…Thank you, brother.\p"
	.string "Sometimes I wanted to be like that\n"
	.string "creature. Invisible. Just to know who I\l"
	.string "was, without an echo.\p"
	.string "But it doesn't hide to be alone. It\n"
	.string "hides so it can listen to someone it\l"
	.string "loves. Its brother is always close by.\p"
	.string "Hehehe…\n"
	.string "Fufufu… Go on. It's listening already.$"

Nexus_Text_TateAndLiza_Latios_ChampionIntro:
	.string "It shows you what it sees. Cities,\n"
	.string "skies, faces. It sends them to anyone\l"
	.string "who can listen.\p"
	.string "We've done that our whole lives.\n"
	.string "Whatever one of us sees, the other\l"
	.string "already knows.\p"
	.string "People think that's strange.\n"
	.string "We think being alone in your own head\l"
	.string "is strange.\p"
	.string "Hehehe…\n"
	.string "Fufufu… Let's see what you're\l"
	.string "thinking!$"

Nexus_Text_TateAndLiza_Latios_ChampionDefeat:
	.string "We saw it coming…\n"
	.string "…and we still couldn't stop it.$"

Nexus_Text_TateAndLiza_Latios_ChampionAfter:
	.string "{SPEAKER NAME_TATE_AND_LIZA}The pictures it sends aren't for fun.\n"
	.string "It shows danger, so the other one can\l"
	.string "get away in time.\p"
	.string "I always speak first. I thought it was\n"
	.string "because I'm the older one. …By three\l"
	.string "minutes.\p"
	.string "Liza says she always knew why. It was\n"
	.string "so I'd be the one who got hit first.\p"
	.string "…Fufufu. Now he's embarrassed. Go on,\n"
	.string "before he starts blushing.$"

Nexus_Text_Roxanne_Uxie_ChampionIntro:
	.string "Don't look at it. The creature on the\n"
	.string "lake. If it opens its eyes, you forget.\l"
	.string "That's what the old texts say.\p"
	.string "I've taught for years. What I fear\n"
	.string "most isn't losing. It's a student who\l"
	.string "forgets everything I said.\p"
	.string "So I write it all down. Everything. Just\n"
	.string "in case.\p"
	.string "…Now, let's make a memory worth\n"
	.string "writing!$"

Nexus_Text_Roxanne_Uxie_ChampionDefeat:
	.string "Noted. Underlined twice.$"

Nexus_Text_Roxanne_Uxie_ChampionAfter:
	.string "{SPEAKER NAME_ROXANNE}Did you notice? It keeps its eyes\n"
	.string "closed. The whole time.\p"
	.string "It could take every memory we have,\n"
	.string "and it chooses not to look. I think\l"
	.string "that is a kind of manners.\p"
	.string "A good teacher does the same, now and\n"
	.string "then. Some things a student has to\l"
	.string "forget, to learn them properly.\p"
	.string "…That goes in the notebook, too. Go on.$"

Nexus_Text_May_Mesprit_ChampionIntro:
	.string "Something's flying over the lake. Every\n"
	.string "time it passes, I want to laugh, and\l"
	.string "then I want to cry.\p"
	.string "The old stories say it taught people\n"
	.string "what sorrow and joy are for.\p"
	.string "I guess I'm the kind who always laughs.\n"
	.string "Even when I lose. Especially then.\p"
	.string "Ready? I'll try not to laugh this time!$"

Nexus_Text_May_Mesprit_ChampionDefeat:
	.string "Ahaha… see? There it is.$"

Nexus_Text_May_Mesprit_ChampionAfter:
	.string "{SPEAKER NAME_MAY}Can I tell you something? It flew right\n"
	.string "past me and I cried. Just for a second.\p"
	.string "I didn't laugh it off. I didn't want to.\p"
	.string "I think that's what it's for. To remind\n"
	.string "you that the sad part counts too.\p"
	.string "Go on. And if you cry, that's okay. It's\n"
	.string "supposed to happen here.$"

Nexus_Text_Wally_Azelf_ChampionIntro:
	.string "The lake out there is gone. Just mud and\n"
	.string "a crater, and Magikarp flopping in the\l"
	.string "puddles.\p"
	.string "Everyone walks past them. I couldn't.\n"
	.string "They're still trying.\p"
	.string "Something lives in the crater. When it\n"
	.string "looked at me, I felt like I could run a\l"
	.string "mile. I've never run a mile.\p"
	.string "L-let's battle! Before the feeling\n"
	.string "wears off!$"

Nexus_Text_Wally_Azelf_ChampionDefeat:
	.string "It wore off. …No. It didn't, actually.$"

Nexus_Text_Wally_Azelf_ChampionAfter:
	.string "{SPEAKER NAME_WALLY}People think willpower is shouting and\n"
	.string "never giving up.\p"
	.string "It isn't. It's getting out of bed on\n"
	.string "the days breathing hurts. Nobody sees\l"
	.string "those days.\p"
	.string "That creature gave people the will to\n"
	.string "do things. I think it gave me mine, a\l"
	.string "long time ago, and I never thanked it.\p"
	.string "Would you? When you get there. Just say\n"
	.string "Wally says thanks.$"

Nexus_Text_Flannery_Heatran_ChampionIntro:
	.string "Did you see it? It walked straight\n"
	.string "across the ceiling. Upside down.\l"
	.string "Glowing like iron in a forge.\p"
	.string "I've been practicing my fierce Gym\n"
	.string "Leader look for months. Lines in the\l"
	.string "mirror. A cool pose.\p"
	.string "That thing doesn't practice anything.\n"
	.string "It's just hot. Hot all the way through.\p"
	.string "…Grr! Fine! Let me show you my heat, all\n"
	.string "the way through!$"

Nexus_Text_Flannery_Heatran_ChampionDefeat:
	.string "You didn't even flinch. Not once.$"

Nexus_Text_Flannery_Heatran_ChampionAfter:
	.string "{SPEAKER NAME_FLANNERY}Know what I noticed? It never looks at\n"
	.string "anyone to see if they're impressed.\p"
	.string "Grandpa was like that. He never tried\n"
	.string "to be the hottest Trainer in Lavaridge.\l"
	.string "He just was.\p"
	.string "I've been copying his moves, when I\n"
	.string "should've been finding my own fire.\p"
	.string "Go on ahead! And if it melts your shoes,\n"
	.string "walk on the ceiling! Ha!$"

Nexus_Text_Whitney_Regigigas_ChampionIntro:
	.string "Did you see the big guy at the end of\n"
	.string "the ropes? He's been standing there\l"
	.string "since I got here!\p"
	.string "He pulled a whole country here, and\n"
	.string "now he won't even move. So slow!\p"
	.string "...You know what? My Miltank's Rollout\n"
	.string "starts slow too. Everybody laughs at\l"
	.string "the first turn.\p"
	.string "Nobody laughs at the fifth! Let's go!$"

Nexus_Text_Whitney_Regigigas_ChampionDefeat:
	.string "Waaah! I rolled and rolled and it\n"
	.string "wasn't enough!$"

Nexus_Text_Whitney_Regigigas_ChampionAfter:
	.string "{SPEAKER NAME_WHITNEY}Okay, I'm done crying. Mostly.\p"
	.string "Something that big doesn't start slow\n"
	.string "because it's lazy. It starts slow\l"
	.string "because once it moves, it can't stop.\p"
	.string "Don't let it get going. Hit it hard\n"
	.string "and hit it early!\p"
	.string "...And if it gets going anyway? Then\n"
	.string "run. That's a strategy too. I use it\l"
	.string "all the time.$"

Nexus_Text_Ariana_ChampionIntro:
	.string "I haven't dreamed in years. I sleep, I\n"
	.string "wake, I work.\p"
	.string "Last night, by this lake, I dreamed.\n"
	.string "Something calm. A lake with no signal in\l"
	.string "it, and fish that were only fish.\p"
	.string "I don't know whose dream that was. It\n"
	.string "wasn't mine. …Battle me. I need to feel\l"
	.string "awake.$"

Nexus_Text_Ariana_ChampionDefeat:
	.string "That, at least, was real.$"

Nexus_Text_Ariana_ChampionAfter:
	.string "{SPEAKER NAME_ARIANA}Our signal made that other lake scream\n"
	.string "for a week. This one gives rest to\l"
	.string "anyone lying beside it. It doesn't ask\l"
	.string "who they are.\p"
	.string "I brought the one who gives nightmares\n"
	.string "with me. I thought I'd need a guard.\l"
	.string "It's been sleeping too.\p"
	.string "I don't like gifts I can't pay for. Go.\n"
	.string "Give it a reason to wake up.$"

Nexus_Text_Chuck_Cobalion_ChampionIntro:
	.string "See those little ones behind the\n"
	.string "swords? They're not scared of me.\l"
	.string "They're scared of what came before.\p"
	.string "The big one with the steel heart stands\n"
	.string "in front of them. Doesn't attack. Just\l"
	.string "stands.\p"
	.string "I've never fought like that in my life.\n"
	.string "Let's see if I can learn it right now!$"

Nexus_Text_Chuck_Cobalion_ChampionDefeat:
	.string "I hit and hit, and you just held.$"

Nexus_Text_Chuck_Cobalion_ChampionAfter:
	.string "{SPEAKER NAME_CHUCK}Every student I ever had, I taught how\n"
	.string "to hit. Harder, faster, again.\p"
	.string "I never taught one of them how to\n"
	.string "stand in front of someone and not\l"
	.string "move.\p"
	.string "That creature does nothing else. It's\n"
	.string "the strongest thing I've ever seen.\p"
	.string "Go on. And don't just win. Leave those\n"
	.string "little ones something to stand\l"
	.string "behind.$"

Nexus_Text_Brock_Terrakion_ChampionIntro:
	.string "Did you see the wall out there?\n"
	.string "Something charged straight through it,\l"
	.string "and the Pokémon behind it fell asleep\l"
	.string "in the rubble.\p"
	.string "It didn't break that wall to get in. It\n"
	.string "broke it to get them out.\p"
	.string "I know that kind. Back home, I'm the\n"
	.string "one the little ones hide behind.\p"
	.string "Let's see if you can get past me!$"

Nexus_Text_Brock_Terrakion_ChampionDefeat:
	.string "You got past me. …Good. Just don't\n"
	.string "wake them.$"

Nexus_Text_Brock_Terrakion_ChampionAfter:
	.string "{SPEAKER NAME_BROCK}People think being solid means never\n"
	.string "moving. That's wrong.\p"
	.string "Sometimes the solid one is the one who\n"
	.string "runs at the wall.\p"
	.string "It'll stand in front of those sleeping\n"
	.string "Pokémon until you prove you're not a\l"
	.string "threat.\p"
	.string "So don't be one. Go on.$"

Nexus_Text_Erika_Virizion_ChampionIntro:
	.string "Something came through the grass a\n"
	.string "moment ago. So quick. Its horns cut the\l"
	.string "stems, and not one flower fell.\p"
	.string "They say it protected Pokémon from\n"
	.string "people who burned their fields, long\l"
	.string "ago.\p"
	.string "It looked at me as it passed. Not at my\n"
	.string "Pokémon. At me.\p"
	.string "I think I understand why. Please… help\n"
	.string "me earn a kinder look.$"

Nexus_Text_Erika_Virizion_ChampionDefeat:
	.string "A clean cut. It didn't bruise a single\n"
	.string "petal.$"

Nexus_Text_Erika_Virizion_ChampionAfter:
	.string "{SPEAKER NAME_ERIKA}My Gym has a small tree at the door.\n"
	.string "Anyone who can cut it may come in. I\l"
	.string "planted it that way.\p"
	.string "That creature is the opposite. It\n"
	.string "stands at the door and decides.\p"
	.string "If it decides against you, don't argue.\n"
	.string "Just show it you did not come here to\l"
	.string "burn anything.\p"
	.string "…And please don't cut its grass on the\n"
	.string "way in.$"

Nexus_Text_Falkner_ChampionIntro:
	.string "Did you see the roofs? It tore them off\n"
	.string "just to watch them fly.\p"
	.string "My father taught me that every flight\n"
	.string "needs a place to land. A branch. A\l"
	.string "perch. An arm.\p"
	.string "That thing up there has never landed\n"
	.string "in its life. And for a second... I\l"
	.string "envied it.\p"
	.string "That's why I'm fighting you. To\n"
	.string "remember why I don't!$"

Nexus_Text_Falkner_ChampionDefeat:
	.string "You stayed on the ground and still\n"
	.string "won. That's a new one.$"

Nexus_Text_Falkner_ChampionAfter:
	.string "{SPEAKER NAME_FALKNER}It flies faster than anything I've ever\n"
	.string "raised. But it has nowhere to go back\l"
	.string "to.\p"
	.string "My birds all come back to the same\n"
	.string "perch in Violet every night.\p"
	.string "I always thought that made them less\n"
	.string "free. Now I think it makes them mine.\p"
	.string "Go on. Knock it out of the sky. Then\n"
	.string "give it somewhere to land.$"

Nexus_Text_Winona_Thundurus_ChampionIntro:
	.string "The storm here throws lightning at the\n"
	.string "tallest thing it can find. In Fortree,\l"
	.string "the tallest things are our homes.\p"
	.string "My birds and I have always lived as\n"
	.string "high as we could. Closer to the sky.\p"
	.string "I never thought the sky could want us\n"
	.string "gone.\p"
	.string "…Forgive me. Let us fly while we still\n"
	.string "can!$"

Nexus_Text_Winona_Thundurus_ChampionDefeat:
	.string "You flew straight through the storm.\n"
	.string "Remarkable.$"

Nexus_Text_Winona_Thundurus_ChampionAfter:
	.string "{SPEAKER NAME_WINONA}Every bird Pokémon knows something\n"
	.string "that people forget.\p"
	.string "When the storm comes, you do not fly\n"
	.string "above it. You fly beneath it, low and\l"
	.string "quick, and you wait.\p"
	.string "For years I believed soaring was the\n"
	.string "only thing worth learning. My birds\l"
	.string "taught me how to land.\p"
	.string "Go now. Keep your head low, and your\n"
	.string "heart high.$"

Nexus_Text_Maxie_Landorus_ChampionIntro:
	.string "Wheat, as far as the eye can see.\n"
	.string "Heavy, golden, and not a single hand to\l"
	.string "gather it.\p"
	.string "That one on the cloud blesses every\n"
	.string "field it passes.\p"
	.string "It is everything I promised Team\n"
	.string "Magma. Land that feeds the world.\p"
	.string "And it is rotting on the stalk. Come.$"

Nexus_Text_Maxie_Landorus_ChampionDefeat:
	.string "Hm. Another harvest I do not get to\n"
	.string "keep.$"

Nexus_Text_Maxie_Landorus_ChampionAfter:
	.string "{SPEAKER NAME_MAXIE}I spent years calculating how much\n"
	.string "land humanity needs.\p"
	.string "I never once calculated how many\n"
	.string "people it takes to tend it.\p"
	.string "Abundance with no one to share it is\n"
	.string "only a larger silence.\p"
	.string "Go on. Let it bless one field that\n"
	.string "someone will actually harvest.$"

Nexus_Text_Kukui_TapuKoko_ChampionIntro:
	.string "Hear that thunder? I know that sound,\n"
	.string "cousin. I live right under it, back on\l"
	.string "Melemele.\p"
	.string "That guardian's got more curiosity\n"
	.string "than sense. It'll jump into any battle\l"
	.string "it hears about, just to see.\p"
	.string "Saved a couple of kids on a broken\n"
	.string "bridge once, too. Then it flew off\l"
	.string "before anyone could thank it.\p"
	.string "Woo! Let's give it something worth\n"
	.string "hearing about!$"

Nexus_Text_Kukui_TapuKoko_ChampionDefeat:
	.string "Woo! It heard that one for sure,\n"
	.string "yeah!$"

Nexus_Text_Kukui_TapuKoko_ChampionAfter:
	.string "{SPEAKER NAME_KUKUI}It keeps the lightning in its shell,\n"
	.string "cousin. Holds it close, like a secret.\p"
	.string "People on Melemele ask why it keeps\n"
	.string "showing up to fight. It doesn't want\l"
	.string "to win. It wants to know you.\p"
	.string "Honestly? Same reason I battle. Took\n"
	.string "me a while to admit it, yeah.\p"
	.string "Go on. Let it get to know you!$"

Nexus_Text_Lillie_TapuLele_ChampionIntro:
	.string "Did you feel the scales? They heal a\n"
	.string "scratch in a moment. I tried it on my\l"
	.string "hand. It works.\p"
	.string "Then I looked at the Pokémon sleeping\n"
	.string "in the flowers. They were healed too.\l"
	.string "Again, and again, and again.\p"
	.string "It doesn't mean any harm. It just\n"
	.string "doesn't know when to stop.\p"
	.string "...I think I know someone like that.\n"
	.string "Let's battle, please!$"

Nexus_Text_Lillie_TapuLele_ChampionDefeat:
	.string "Oh... That's enough, I think. You\n"
	.string "win.$"

Nexus_Text_Lillie_TapuLele_ChampionAfter:
	.string "{SPEAKER NAME_LILLIE}Too much care can hurt. I didn't\n"
	.string "understand that for a long time.\p"
	.string "Someone I love used to hold on to\n"
	.string "everything she loved. She meant it\l"
	.string "kindly, too.\p"
	.string "We have tea now, sometimes. I tell her\n"
	.string "when it's enough, and she listens.\p"
	.string "Go gently with it. It's only trying\n"
	.string "to help.$"

Nexus_Text_Gladion_TapuBulu_ChampionIntro:
	.string "You hear that bell? I heard it on\n"
	.string "Ula'ula, back when I ran with Skull.\p"
	.string "We kept a town behind a wall. The\n"
	.string "island's guardian never came to save\l"
	.string "it. It just let the grass grow over us.\p"
	.string "Everyone said it was lazy. It wasn't.\n"
	.string "It was waiting for us to leave.\p"
	.string "...Enough. Show me what you've got.$"

Nexus_Text_Gladion_TapuBulu_ChampionDefeat:
	.string "Hmph. You didn't flinch. Good.$"

Nexus_Text_Gladion_TapuBulu_ChampionAfter:
	.string "{SPEAKER NAME_GLADION}It rips trees out and grows new ones.\n"
	.string "Takes its strength from the growing.\p"
	.string "Make it angry and it stops being a\n"
	.string "guardian. It's just a wall with horns.\p"
	.string "I was on the wrong side of a wall once.\n"
	.string "It was right not to help me.\p"
	.string "...Don't make it angry. Or do. Just\n"
	.string "win.$"

Nexus_Text_Juan_TapuFini_ChampionIntro:
	.string "Did you walk through the mist? It did\n"
	.string "not hurt you, I see. Good.\p"
	.string "It washes clean those who come calmly.\n"
	.string "Those who come angry, it simply\l"
	.string "swallows.\p"
	.string "I have spent my life making water\n"
	.string "beautiful for an audience. This one\l"
	.string "makes water honest.\p"
	.string "Aahaha! How I envy it. Shall we?$"

Nexus_Text_Juan_TapuFini_ChampionDefeat:
	.string "Aahahaha… the mist saw right through\n"
	.string "my flourish.$"

Nexus_Text_Juan_TapuFini_ChampionAfter:
	.string "{SPEAKER NAME_JUAN}An illusion is a kindness, you know. We\n"
	.string "show people something lovelier than\l"
	.string "the truth.\p"
	.string "That mist refuses to. It shows you\n"
	.string "exactly what you carried in.\p"
	.string "I wonder what it saw in me. A dancer? Or\n"
	.string "an old man hiding behind his cape?\p"
	.string "Go gently. Bring it calm, and it will\n"
	.string "return calm.$"

Nexus_Text_Chuck_Urshifu_ChampionIntro:
	.string "Did you hear it? The sound from the\n"
	.string "towers? That's a fist hitting a\l"
	.string "target.\p"
	.string "I've trained under a waterfall most of\n"
	.string "my life. That sound has been going\l"
	.string "longer than that.\p"
	.string "I want it to teach me. First I have to\n"
	.string "get past you. WAHAHAH!$"

Nexus_Text_Chuck_Urshifu_ChampionDefeat:
	.string "Hah! You flow like water. I hit\n"
	.string "nothing!$"

Nexus_Text_Chuck_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_CHUCK}You know what the waterfall taught me?\n"
	.string "You can't punch water.\p"
	.string "It just goes around your fist and\n"
	.string "keeps falling. It doesn't even notice.\p"
	.string "That creature fights the same way. Hit\n"
	.string "it, and it's already somewhere else.\p"
	.string "So don't hit harder. Hit smarter. And\n"
	.string "if you lose, stand back under it and\l"
	.string "try again!$"

Nexus_Text_Lusamine_Enamorus_ChampionIntro:
	.string "Did you walk through the spring out\n"
	.string "there? It came with that creature.\p"
	.string "They say its love makes every living\n"
	.string "thing bloom. They also say it falls\l"
	.string "from the clouds on anyone who treats\l"
	.string "life without respect.\p"
	.string "Once, I would have wanted it in my\n"
	.string "collection. Today I think it would have\l"
	.string "come for me.\p"
	.string "...Let us see what you have learned\n"
	.string "about love, then.$"

Nexus_Text_Lusamine_Enamorus_ChampionDefeat:
	.string "You treated them with respect, even in\n"
	.string "battle. I noticed.$"

Nexus_Text_Lusamine_Enamorus_ChampionAfter:
	.string "{SPEAKER NAME_LUSAMINE}Its love does not stay. It brings the\n"
	.string "spring, and then it moves on.\p"
	.string "I used to believe love meant keeping.\n"
	.string "Holding still whatever I found\l"
	.string "beautiful.\p"
	.string "My children taught me otherwise. They\n"
	.string "are still teaching me.\p"
	.string "Go. Be kind to it, even if it is not\n"
	.string "kind to you.$"

Nexus_Text_Glacia_ChienPao_ChampionIntro:
	.string "Do you feel it? Your guard, cracking,\n"
	.string "like thin ice under a boot.\p"
	.string "Everything near that sword grows\n"
	.string "weaker. Stone. Steel. People.\p"
	.string "I have built myself of ice for many\n"
	.string "years. It cracked in an instant here.\p"
	.string "…Interesting. Let us see if there is\n"
	.string "anything underneath.$"

Nexus_Text_Glacia_ChienPao_ChampionDefeat:
	.string "So there was something underneath. It\n"
	.string "was not enough.$"

Nexus_Text_Glacia_ChienPao_ChampionAfter:
	.string "{SPEAKER NAME_GLACIA}They say it was sealed with stakes,\n"
	.string "driven in by people who feared it.\p"
	.string "Fear makes you build walls. It breaks\n"
	.string "walls. That is all it does.\p"
	.string "It must be very lonely, being the thing\n"
	.string "everyone builds walls against.\p"
	.string "Go. Walk in without armor. It will have\n"
	.string "nothing to break.$"

Nexus_Text_Flannery_ChiYu_ChampionIntro:
	.string "It's tiny. Honestly, it's about the\n"
	.string "size of the goldfish I had as a kid.\p"
	.string "But it melted the ground into a lake of\n"
	.string "fire, and it swims in there like it's\l"
	.string "bath water.\p"
	.string "And standing near it, everything feels\n"
	.string "weaker. Your Pokémon, you, me. Like it's\l"
	.string "making room to look big.\p"
	.string "…I know that trick. I don't like it.\n"
	.string "Let's battle!$"

Nexus_Text_Flannery_ChiYu_ChampionDefeat:
	.string "Wow. You stayed strong, even after all\n"
	.string "that.$"

Nexus_Text_Flannery_ChiYu_ChampionAfter:
	.string "{SPEAKER NAME_FLANNERY}When I first became a Gym Leader, I\n"
	.string "kind of wanted everyone else to look\l"
	.string "small.\p"
	.string "If they were weak, then maybe I'd look\n"
	.string "strong. That's exactly what that\l"
	.string "little thing does.\p"
	.string "But the hot springs in Lavaridge don't\n"
	.string "burn anybody. They warm people up, so\l"
	.string "they can keep going.\p"
	.string "That's what fire is for. Go and remind\n"
	.string "it!$"

Nexus_Text_Lusamine_Fezandipiti_ChampionIntro:
	.string "What a beautiful statue out there. All\n"
	.string "those flowers. Everyone loves a hero.\p"
	.string "Its feathers are lovely, too. Look\n"
	.string "closer, and the chain around its neck\l"
	.string "is full of poison. It makes people\l"
	.string "adore it.\p"
	.string "I had a paradise once, and people\n"
	.string "applauded. I know how that chain feels\l"
	.string "from the inside.\p"
	.string "...Come. Let us not keep the audience\n"
	.string "waiting.$"

Nexus_Text_Lusamine_Fezandipiti_ChampionDefeat:
	.string "No applause, please. You simply won.$"

Nexus_Text_Lusamine_Fezandipiti_ChampionAfter:
	.string "{SPEAKER NAME_LUSAMINE}People built that statue out of\n"
	.string "gratitude. They never asked what it\l"
	.string "had done to earn it.\p"
	.string "No one asked me, either. I made very\n"
	.string "sure they would not.\p"
	.string "When you face it, don't look at the\n"
	.string "feathers too long. Look at the chain.\p"
	.string "...And if anything is left of it, let\n"
	.string "it be ordinary for a while. It may be\l"
	.string "a relief.$"

Nexus_Text_Red_ChampionIntro:
	.string "……\p"
	.string "…It was here first. Before anything.\p"
	.string "…Alone.\p"
	.string "…!$"

Nexus_Text_Red_ChampionDefeat:
	.string "……Heh.$"

Nexus_Text_Red_ChampionAfter:
	.string "{SPEAKER NAME_RED}……\p"
	.string "…I went up a mountain. To be alone.\p"
	.string "…Stayed a long time.\p"
	.string "…It was alone first. So it made\n"
	.string "everything. Every one of us.\p"
	.string "…I just came down. …Go.$"

Nexus_Text_Leaf_Mew_ChampionIntro:
	.string "I followed the tracks here. Hundreds\n"
	.string "of them, from every kind of Pokémon,\l"
	.string "all shrinking into one little set of\l"
	.string "paws.\p"
	.string "I spent years filling a Pokédex, one\n"
	.string "page at a time. Turns out it was all one\l"
	.string "page.\p"
	.string "…I'm not upset! I just want to see it\n"
	.string "with my own eyes first!$"

Nexus_Text_Leaf_Mew_ChampionDefeat:
	.string "Ah… I got so busy looking, I forgot to\n"
	.string "battle.$"

Nexus_Text_Leaf_Mew_ChampionAfter:
	.string "{SPEAKER NAME_GREEN}People call me by a different name\n"
	.string "here. I didn't pick it, but I answer to\l"
	.string "it.\p"
	.string "That little one is every Pokémon at\n"
	.string "once, and it answers to all of them.\p"
	.string "Maybe a name is just the place where\n"
	.string "someone found you.\p"
	.string "Go on. It's watching you. It always\n"
	.string "was.$"

Nexus_Text_Spenser_Celebi_ChampionIntro:
	.string "Hohoho. Did you see it? The little\n"
	.string "green light, walking between the\l"
	.string "trees?\p"
	.string "Wherever it passes, the dead wood\n"
	.string "sprouts again. An old man watches a\l"
	.string "thing like that and thinks, “Ah. Me\l"
	.string "next?”\p"
	.string "But no. I have been exactly this old\n"
	.string "for a while now, and I have grown fond\l"
	.string "of it.\p"
	.string "Come. Let us fight the way we are.$"

Nexus_Text_Spenser_Celebi_ChampionDefeat:
	.string "Splendid. You did not wish to be\n"
	.string "anything but yourself. Neither did\l"
	.string "your Pokémon.$"

Nexus_Text_Spenser_Celebi_ChampionAfter:
	.string "{SPEAKER NAME_SPENSER}They say that little one only appears\n"
	.string "where a forest is healthy.\p"
	.string "So it is not a miracle when it comes. It\n"
	.string "is a compliment. The forest was already\l"
	.string "doing well.\p"
	.string "My Palace teaches the same thing. A\n"
	.string "Pokémon is at its best when no one\l"
	.string "asks it to be something else.\p"
	.string "Go on. Let the forest keep its ages.$"

Nexus_Text_Brendan_Jirachi_ChampionIntro:
	.string "Up on the hill there's a comet that\n"
	.string "doesn't move, and paper tags tied to\l"
	.string "every blade of grass.\p"
	.string "Every tag has a wish on it. I read about\n"
	.string "fifty. Most of them are about going\l"
	.string "home.\p"
	.string "I wrote one too. Don't ask. …Okay, you\n"
	.string "can ask after I win!$"

Nexus_Text_Brendan_Jirachi_ChampionDefeat:
	.string "Nope. Guess that wish is on hold.$"

Nexus_Text_Brendan_Jirachi_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}Fine, my wish. It said: 'I want to tell my\n"
	.string "dad about this place.'\p"
	.string "Not 'be Champion.' Not 'beat you.' Just\n"
	.string "that.\p"
	.string "It only wakes up for a week every\n"
	.string "thousand years, so hurry. And if you\l"
	.string "find my tag, leave it where it is.$"

Nexus_Text_Misty_Manaphy_ChampionIntro:
	.string "Did you see the eggs out there? Every\n"
	.string "one drifted off, and every one came\l"
	.string "back.\p"
	.string "The little one that hatched is the\n"
	.string "same. It could swim anywhere in the\l"
	.string "world, and it always swims home.\p"
	.string "I keep saying I'll travel the whole\n"
	.string "world. I never do! Let's battle!$"

Nexus_Text_Misty_Manaphy_ChampionDefeat:
	.string "Aww… okay. You win this one.$"

Nexus_Text_Misty_Manaphy_ChampionAfter:
	.string "{SPEAKER NAME_MISTY}Know what I figured out? It doesn't\n"
	.string "come home because it's scared to\l"
	.string "leave.\p"
	.string "It comes home because somebody's\n"
	.string "there. Home isn't a place for it. It's\l"
	.string "who's waiting.\p"
	.string "…That's why I never stay away from\n"
	.string "Cerulean for long.\p"
	.string "Go say hi. Gently! It's only a baby.$"

Nexus_Text_Karen_Darkrai_ChampionIntro:
	.string "I fell asleep out there. Only for a\n"
	.string "moment.\p"
	.string "I dreamed my Umbreon lost, and a voice\n"
	.string "said it was a weak Pokémon. The voice\l"
	.string "was mine.\p"
	.string "That creature doesn't make the\n"
	.string "nightmare. It only turns off the light,\l"
	.string "so you can see what was already there.\p"
	.string "Now. Show me what's in yours.$"

Nexus_Text_Karen_Darkrai_ChampionDefeat:
	.string "…Hm. You wake up fast. I like that.$"

Nexus_Text_Karen_Darkrai_ChampionAfter:
	.string "{SPEAKER NAME_KAREN}People will tell you it's evil. It isn't.\n"
	.string "It just wants to be left alone in the\l"
	.string "dark.\p"
	.string "Everyone has one sentence they're\n"
	.string "afraid to hear in their own voice. Mine\l"
	.string "is the one I've spent my life arguing\l"
	.string "against.\p"
	.string "Go on. If it shows you yours, don't\n"
	.string "argue. Just keep walking.$"

Nexus_Text_Erika_Shaymin_ChampionIntro:
	.string "Did you see the little one covered in\n"
	.string "flowers? Everywhere it walks, the grey\l"
	.string "air goes clear and something blooms.\p"
	.string "In Celadon, I sell perfume. It hides the\n"
	.string "smell of the city. It has never once\l"
	.string "removed it.\p"
	.string "That little one breathes the poison in…\n"
	.string "and gives back a whole field.\p"
	.string "I have spent my life covering things up.\n"
	.string "Let me see if I can do more than that.$"

Nexus_Text_Erika_Shaymin_ChampionDefeat:
	.string "You grew right through me. How lovely.\n"
	.string "I'm not even cross.$"

Nexus_Text_Erika_Shaymin_ChampionAfter:
	.string "{SPEAKER NAME_ERIKA}It is terribly shy. If you run at it, it\n"
	.string "will curl up and pretend to be a bush.\p"
	.string "Walk slowly. Let it smell you first.\p"
	.string "The old stories say it appears to thank\n"
	.string "someone. I keep wondering whom I ought\l"
	.string "to thank.\p"
	.string "I suppose I will start with you. Thank\n"
	.string "you. Now go gently.$"

Nexus_Text_Blue_Victini_ChampionIntro:
	.string "Heard about the little guy on the\n"
	.string "island? It hands out wins. Whoever it\l"
	.string "likes just can't lose.\p"
	.string "Know what? I've been carrying one this\n"
	.string "whole time. Took it all the way to the\l"
	.string "top.\p"
	.string "Still came in second to Red.\p"
	.string "So either it doesn't work, or it never\n"
	.string "liked me. Let's find out!$"

Nexus_Text_Blue_Victini_ChampionDefeat:
	.string "…Yeah. Figured it was the second one.$"

Nexus_Text_Blue_Victini_ChampionAfter:
	.string "{SPEAKER NAME_BLUE}Real talk? I'm glad it doesn't work on\n"
	.string "me.\p"
	.string "If I ever beat Red, I want it to be me.\n"
	.string "Not luck. Not some lucky charm with big\l"
	.string "ears.\p"
	.string "…Don't tell Gramps I said anything\n"
	.string "that sensible.\p"
	.string "Go get your win. The real kind. Smell ya\n"
	.string "later!$"

Nexus_Text_Petrel_Meloetta_ChampionIntro:
	.string "There's a performer on that stage.\n"
	.string "Sings one way, then spins and becomes\l"
	.string "something else, mid-song.\p"
	.string "I've done a hundred voices. The\n"
	.string "Director's. A grunt's. My own mother\l"
	.string "wouldn't know me.\p"
	.string "But when it changes, both of them are\n"
	.string "real. I'm jealous, kid. Let's go!$"

Nexus_Text_Petrel_Meloetta_ChampionDefeat:
	.string "Bravo. And that was my real voice, for\n"
	.string "once.$"

Nexus_Text_Petrel_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_PETREL}Here's a secret. Last night I sang in\n"
	.string "front of a mirror, trying to find my own\l"
	.string "voice. The one from before all the\l"
	.string "others.\p"
	.string "Couldn't find it. Every note came out\n"
	.string "as somebody I used to pretend to be.\p"
	.string "That creature doesn't have that\n"
	.string "problem. Two faces, one voice.\p"
	.string "Go listen to it. Then come tell me what I\n"
	.string "sound like.$"

Nexus_Text_Wallace_Diancie_ChampionIntro:
	.string "That cave! Coal on the walls, and in the\n"
	.string "heart of it, diamonds.\p"
	.string "A diamond is only coal that did not\n"
	.string "break under pressure.\p"
	.string "People think my elegance is\n"
	.string "effortless. It never was.\p"
	.string "Let us see which of us sparkles under\n"
	.string "pressure!$"

Nexus_Text_Wallace_Diancie_ChampionDefeat:
	.string "Bravo. You did not break. Neither did I,\n"
	.string "I hope.$"

Nexus_Text_Wallace_Diancie_ChampionAfter:
	.string "{SPEAKER NAME_WALLACE}They say that little princess was a\n"
	.string "common rock creature once, like any\l"
	.string "other.\p"
	.string "Something in it changed, and now it\n"
	.string "makes diamonds with its own hands.\p"
	.string "I understand it perfectly. I was only a\n"
	.string "boy from Sootopolis, once.\p"
	.string "Go and meet it. Be gentle. It is harder\n"
	.string "than it looks, and softer.$"

Nexus_Text_Tucker_Hoopa_ChampionIntro:
	.string "Ha ha! What a house! Every seat full!\n"
	.string "Somebody's been busy with those gold\l"
	.string "rings.\p"
	.string "But look at their faces, fan. They\n"
	.string "didn't buy tickets. They got pulled in.\p"
	.string "Nobody chose to be here. Nobody's\n"
	.string "cheering.\p"
	.string "Except you. You walked in on your own.\n"
	.string "So this one's for an audience of one!$"

Nexus_Text_Tucker_Hoopa_ChampionDefeat:
	.string "…Now that's what a real crowd sounds\n"
	.string "like. Just one person, meaning it.$"

Nexus_Text_Tucker_Hoopa_ChampionAfter:
	.string "{SPEAKER NAME_TUCKER}All my life I wanted a full house. Every\n"
	.string "seat. Every light.\p"
	.string "That little prankster gave me one, and\n"
	.string "it was the worst show I ever played.\p"
	.string "Turns out a crowd's only worth\n"
	.string "something if they chose to come.\p"
	.string "Go send those people home, fan. The\n"
	.string "show's over.$"

Nexus_Text_Wattson_Magearna_ChampionIntro:
	.string "Wahahaha! Did you see it? Five hundred\n"
	.string "years old, and every gear still turning!\l"
	.string "Not one speck of rust!\p"
	.string "I've built plenty of things in my time.\n"
	.string "A whole city under one roof. A\l"
	.string "generator underground that nearly\l"
	.string "blew!\p"
	.string "Everything I ever built needed me to\n"
	.string "keep it running. That little marvel runs\l"
	.string "on its own heart!\p"
	.string "Show me what keeps YOUR team running!\n"
	.string "Wahahaha!$"

Nexus_Text_Wattson_Magearna_ChampionDefeat:
	.string "Wahahaha! Beautifully engineered,\n"
	.string "young one!$"

Nexus_Text_Wattson_Magearna_ChampionAfter:
	.string "{SPEAKER NAME_WATTSON}I've been thinking about whoever built\n"
	.string "it.\p"
	.string "You don't put a heart in a machine to\n"
	.string "make it work better. You do it so that\l"
	.string "something will stay after you're gone.\p"
	.string "I'm an old man. I suppose Mauville is\n"
	.string "the thing I leave behind. Noisy, bright,\l"
	.string "always buzzing.\p"
	.string "…Wahahaha! Not a bad heart, either! Go\n"
	.string "on, now.$"

Nexus_Text_Archer_Marshadow_ChampionIntro:
	.string "Something lives in the shadows of this\n"
	.string "place. It borrows a body's outline and\l"
	.string "copies whatever it does.\p"
	.string "I watched it follow me for an hour. It\n"
	.string "walked like me. It stood like me.\p"
	.string "Then it stood like him. Hands behind the\n"
	.string "back, chin up. It learned that from me.\p"
	.string "…Enough. Show me something it can't\n"
	.string "copy.$"

Nexus_Text_Archer_Marshadow_ChampionDefeat:
	.string "You fight like yourself. How irritating.$"

Nexus_Text_Archer_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_ARCHER}For three years I've given orders the\n"
	.string "way he gave them. Held my Pokémon the\l"
	.string "way he held his. Every habit, copied.\p"
	.string "That little shadow does the same, but\n"
	.string "it picks the one it follows. I never\l"
	.string "picked. I only stayed.\p"
	.string "Go on. Take a piece of it home, if it lets\n"
	.string "you. Just don't let it learn to stand\l"
	.string "like me.$"

Nexus_Text_Wattson_Zeraora_ChampionIntro:
	.string "Wahahaha! Did you see the lamps down\n"
	.string "every street? Something's running\l"
	.string "through the wires faster than the\l"
	.string "power!\p"
	.string "I've spent my whole life taming\n"
	.string "electricity. Switches, circuits,\l"
	.string "generators. It always does what I say…\l"
	.string "mostly!\p"
	.string "That thing doesn't take orders. It IS\n"
	.string "the current. Oh, I like it already!\l"
	.string "Wahahaha!\p"
	.string "Let's crackle!$"

Nexus_Text_Wattson_Zeraora_ChampionDefeat:
	.string "Wahahaha! Grounded! Completely\n"
	.string "grounded!$"

Nexus_Text_Wattson_Zeraora_ChampionAfter:
	.string "{SPEAKER NAME_WATTSON}Here's something they don't teach at\n"
	.string "any school.\p"
	.string "Lightning isn't dangerous because\n"
	.string "it's strong. It's dangerous because\l"
	.string "it's in a hurry.\p"
	.string "That creature never waits for\n"
	.string "anything. So be the one thing it can't\l"
	.string "rush.\p"
	.string "Stand still, young one. Let it come to\n"
	.string "you. Wahahaha!$"

Nexus_Text_Jasmine_Melmetal_ChampionIntro:
	.string "I love steel because it lasts. Rain,\n"
	.string "years, battles. It stays.\p"
	.string "But the one in the forge... when it\n"
	.string "grows old, it rusts. It falls apart.\l"
	.string "And then it comes back, very small.\p"
	.string "...I don't know if that's sad or\n"
	.string "beautiful. Maybe battling will tell me.$"

Nexus_Text_Jasmine_Melmetal_ChampionDefeat:
	.string "...Ah. I've fallen apart a little.$"

Nexus_Text_Jasmine_Melmetal_ChampionAfter:
	.string "{SPEAKER NAME_JASMINE}When my Ampharos got sick at the\n"
	.string "lighthouse, I thought steel was the\l"
	.string "answer. Be hard. Don't break.\p"
	.string "But it didn't get better by being hard.\n"
	.string "It got better because someone crossed\l"
	.string "the sea with medicine.\p"
	.string "I think that creature knows. Things\n"
	.string "break. Things come back. Please go\l"
	.string "and meet it.$"

Nexus_Text_Norman_Zarude_ChampionIntro:
	.string "The creatures in this jungle don't\n"
	.string "trust outsiders. They drive off anyone\l"
	.string "who isn't family.\p"
	.string "But I heard of one that found a human\n"
	.string "baby and raised it as its own. Fed it.\l"
	.string "Fought for it.\p"
	.string "Family isn't only who you're born to. I\n"
	.string "learned that from a boy who wasn't\l"
	.string "mine.\p"
	.string "Come. Let's see how you were raised!$"

Nexus_Text_Norman_Zarude_ChampionDefeat:
	.string "Whoever raised you did good work.$"

Nexus_Text_Norman_Zarude_ChampionAfter:
	.string "{SPEAKER NAME_NORMAN}There was a sickly boy in Petalburg.\n"
	.string "Wally. He wanted to catch a Pokémon\l"
	.string "before he moved away.\p"
	.string "I lent him my own Zigzagoon, and I\n"
	.string "watched him catch his first Ralts. His\l"
	.string "hands were shaking.\p"
	.string "I've won a great many battles. That\n"
	.string "moment is the one I'm proudest of.\p"
	.string "That creature would understand. Go on.$"

Nexus_Text_Greta_GreatTusk_ChampionIntro:
	.string "OK, champ, straight talk. There's a big\n"
	.string "shaggy thing out there that's all\l"
	.string "Body. Nothing else.\p"
	.string "At my Arena, all Body loses. The judges\n"
	.string "want Mind and Skill too. That's the\l"
	.string "rule!\p"
	.string "Out here, there were no judges. It just\n"
	.string "kept winning. Look at all those broken\l"
	.string "tusks.\p"
	.string "So give me three good turns. I want to\n"
	.string "remember why the rule's there.$"

Nexus_Text_Greta_GreatTusk_ChampionDefeat:
	.string "Yes! That's it! That's what Mind and\n"
	.string "Skill look like!$"

Nexus_Text_Greta_GreatTusk_ChampionAfter:
	.string "{SPEAKER NAME_GRETA}You know why my Arena judges three\n"
	.string "things? I used to think it was to be\l"
	.string "fair.\p"
	.string "It's not. It's so there's somebody\n"
	.string "left standing after. Nobody fights all\l"
	.string "Body for long.\p"
	.string "That thing out there never had a\n"
	.string "judge. It won every fight, and now it's\l"
	.string "alone in a ring full of broken fence\l"
	.string "posts.\p"
	.string "Go on. Be the judge it never had.$"

Nexus_Text_Whitney_ScreamTail_ChampionIntro:
	.string "It's pink! It's fluffy! It has the\n"
	.string "cutest little tail in the whole world!\p"
	.string "And it SCREAMED at me. Right in my\n"
	.string "face. My hair's still standing up!\p"
	.string "...Cute things are allowed to be scary.\n"
	.string "Ask anyone who's lost to me!$"

Nexus_Text_Whitney_ScreamTail_ChampionDefeat:
	.string "Waaah! I screamed louder and it still\n"
	.string "didn't work!$"

Nexus_Text_Whitney_ScreamTail_ChampionAfter:
	.string "{SPEAKER NAME_WHITNEY}People back home call me a crybaby.\n"
	.string "They say it like it's the whole story.\p"
	.string "That little thing screams because it\n"
	.string "wants to be left alone. I cry because\l"
	.string "I want to win so bad it hurts.\p"
	.string "Neither of us is gonna stop. Go sing it\n"
	.string "something nice. Then beat it!$"

Nexus_Text_Sidney_BruteBonnet_ChampionIntro:
	.string "Careful breathing out there. That\n"
	.string "stuff in the air makes you sleepy.\p"
	.string "Big mushroom with a mouth, and it\n"
	.string "doesn't even chase you. It just waits\l"
	.string "till you nod off.\p"
	.string "My Cacturne does the same thing in the\n"
	.string "desert. Follows folks till they drop.\p"
	.string "Guess I'm immune. I get way too fired\n"
	.string "up to sleep! Let's go!$"

Nexus_Text_Sidney_BruteBonnet_ChampionDefeat:
	.string "Ha, okay. I'm awake now. Real awake.$"

Nexus_Text_Sidney_BruteBonnet_ChampionAfter:
	.string "{SPEAKER NAME_SIDNEY}Worst way to lose a fight is sleeping\n"
	.string "through it.\p"
	.string "That thing never loses, 'cause\n"
	.string "nobody's ever awake to fight it.\p"
	.string "So stay loud. Stay angry if you gotta.\p"
	.string "Just don't close your eyes in there.$"

Nexus_Text_Phoebe_ChampionIntro:
	.string "Did you hear it laughing? I tried to\n"
	.string "scare it back! It didn't work.\p"
	.string "I think it's a ghost that eats fear. It\n"
	.string "hides and giggles and waits for you to\l"
	.string "scream.\p"
	.string "But it's so old… Nobody has screamed\n"
	.string "for it in thousands of years.\p"
	.string "Ahaha! It's starving! Let's play\n"
	.string "first!$"

Nexus_Text_Phoebe_ChampionDefeat:
	.string "Ahaha! I lost! Should I scream? Would\n"
	.string "that help it?$"

Nexus_Text_Phoebe_ChampionAfter:
	.string "{SPEAKER NAME_PHOEBE}Ghosts on Mt. Pyre want to be\n"
	.string "remembered. That's all.\p"
	.string "This one is older than remembering. It\n"
	.string "just wants someone to react.\p"
	.string "So when you meet it, don't be brave,\n"
	.string "okay? Be surprised.\p"
	.string "It's been waiting so long for someone\n"
	.string "to be surprised.$"

Nexus_Text_Bugsy_SlitherWing_ChampionIntro:
	.string "Did you see its tracks? Wings that\n"
	.string "size, and it walks. It walks!\p"
	.string "I think it's what a very old bug looked\n"
	.string "like, before the sky was worth the\l"
	.string "trouble.\p"
	.string "I have to see what it knows. You're in\n"
	.string "the way, so... let's battle!$"

Nexus_Text_Bugsy_SlitherWing_ChampionDefeat:
	.string "Noted. Carefully. With a diagram.$"

Nexus_Text_Bugsy_SlitherWing_ChampionAfter:
	.string "{SPEAKER NAME_BUGSY}My Scizor has wings too. It can't fly\n"
	.string "with them. It flaps them to cool down.\p"
	.string "I used to feel sorry for it. Like\n"
	.string "something had been taken away.\p"
	.string "But that creature walked through a\n"
	.string "whole age of the world with its wings\l"
	.string "folded. Nothing was taken. It's just\l"
	.string "patient.\p"
	.string "Go on. I'll be here, sketching the\n"
	.string "footprints.$"

Nexus_Text_LtSurge_SandyShocks_ChampionIntro:
	.string "Sand, kid. I've crossed deserts like\n"
	.string "this before. Deserts hide things.\p"
	.string "Out there, something old is buried\n"
	.string "under the dunes. Magnetic. Still live,\l"
	.string "after who knows how long.\p"
	.string "Old ordnance never forgets it's a\n"
	.string "bomb, baby. Watch your step, and fight\l"
	.string "me first!$"

Nexus_Text_LtSurge_SandyShocks_ChampionDefeat:
	.string "Hah! You walked right through, kid!$"

Nexus_Text_LtSurge_SandyShocks_ChampionAfter:
	.string "{SPEAKER NAME_LT_SURGE}Rule one in a desert: anything buried\n"
	.string "long enough starts to look like the\l"
	.string "ground.\p"
	.string "That thing's been waiting under the\n"
	.string "sand since before anybody drew a map.\p"
	.string "It'll pull at your Poké Balls before it\n"
	.string "pulls at you. Hold 'em tight.\p"
	.string "Step where I stepped, and move out!$"

Nexus_Text_Noland_IronTreads_ChampionIntro:
	.string "Donphan. I know Donphan. I've rented\n"
	.string "out more Donphan than I can count.\p"
	.string "That thing out there has the shape.\n"
	.string "Tusks, the roll, the whole spec sheet.\p"
	.string "But there's nothing else in it. No\n"
	.string "Donphan in there. Just the sheet, in\l"
	.string "steel.\p"
	.string "Kinda makes me wonder what I look like\n"
	.string "from the outside. Let's find out!$"

Nexus_Text_Noland_IronTreads_ChampionDefeat:
	.string "Yeah. Knowing the sheet wasn't\n"
	.string "enough, huh.$"

Nexus_Text_Noland_IronTreads_ChampionAfter:
	.string "{SPEAKER NAME_NOLAND}I always said knowledge beats\n"
	.string "friendship. Read the Pokémon, win the\l"
	.string "battle.\p"
	.string "Then I saw what's left of a Donphan\n"
	.string "when all you keep is the knowledge.\l"
	.string "Straight lines. Nobody home.\p"
	.string "Maybe I'll let the next challenger\n"
	.string "keep their rental a little longer.\p"
	.string "Go on. Roll that thing over for me.$"

Nexus_Text_Glacia_IronBundle_ChampionIntro:
	.string "Did you see that little machine racing\n"
	.string "down the halls?\p"
	.string "It is carrying something to someone.\n"
	.string "Every day, for centuries, and there is\l"
	.string "no one left.\p"
	.string "I left my home to find worthy rivals in\n"
	.string "the cold. This is the coldest place I\l"
	.string "have ever been, and I cannot stand it.\p"
	.string "Cold is only beautiful when someone is\n"
	.string "shivering. Come.$"

Nexus_Text_Glacia_IronBundle_ChampionDefeat:
	.string "Your warmth again. It seems I cannot\n"
	.string "escape it.$"

Nexus_Text_Glacia_IronBundle_ChampionAfter:
	.string "{SPEAKER NAME_GLACIA}I thought I wanted a world as cold as\n"
	.string "my Pokémon. Quiet. Pure.\p"
	.string "This is that world, and it is only\n"
	.string "lonely.\p"
	.string "That machine keeps delivering because\n"
	.string "it does not know how to stop hoping.\p"
	.string "Take it something. Even a battle\n"
	.string "counts as a delivery.$"

Nexus_Text_Brawly_IronHands_ChampionIntro:
	.string "There's a Pokémon down there that\n"
	.string "fights exactly like my Hariyama. Same\l"
	.string "stance. Same slap. Same bow before it\l"
	.string "charges.\p"
	.string "Only it's made of iron, and it doesn't\n"
	.string "breathe.\p"
	.string "I raised Hariyama from a little\n"
	.string "Makuhita. I know every habit it has.\l"
	.string "Seeing them on a machine… that shook\l"
	.string "me, dude.\p"
	.string "Let's go! I need to feel a real one hit!$"

Nexus_Text_Brawly_IronHands_ChampionDefeat:
	.string "That was real, all right. Thanks for\n"
	.string "that.$"

Nexus_Text_Brawly_IronHands_ChampionAfter:
	.string "{SPEAKER NAME_BRAWLY}Figured it out while we were battling.\p"
	.string "That iron one never gets tired. Never\n"
	.string "sweats, never slips. Sounds great,\l"
	.string "right?\p"
	.string "But my Hariyama gets tired. That's how\n"
	.string "it learns where it's weak. That's why\l"
	.string "it keeps getting better.\p"
	.string "Something that can't get tired can't\n"
	.string "get any stronger. Go show it that.$"

Nexus_Text_Lucy_IronJugulis_ChampionIntro:
	.string "…Three doors. You saw them.\p"
	.string "At the Pike, you choose without seeing.\n"
	.string "People call it luck.\p"
	.string "That thing flies like that. The middle\n"
	.string "head can't see. It just trusts the\l"
	.string "other two.\p"
	.string "…It's not luck. Pick.$"

Nexus_Text_Lucy_IronJugulis_ChampionDefeat:
	.string "…You picked right.$"

Nexus_Text_Lucy_IronJugulis_ChampionAfter:
	.string "{SPEAKER NAME_LUCY}…You think I'm the Pike Queen because\n"
	.string "I'm lucky.\p"
	.string "No. You open a door blind because you\n"
	.string "trust what's beside you.\p"
	.string "That thing never misses in the dark. It\n"
	.string "isn't looking. It's trusting.\p"
	.string "…Go on. Door's open.$"

Nexus_Text_Bugsy_IronMoth_ChampionIntro:
	.string "That moth up there is made of metal.\n"
	.string "Wings, legs, all of it.\p"
	.string "Someone designed it. Nobody will ever\n"
	.string "need to study it, because somebody\l"
	.string "already wrote the manual.\p"
	.string "...That's the saddest thing I've ever\n"
	.string "seen in a garden. Battle me, please.\l"
	.string "I need to think.$"

Nexus_Text_Bugsy_IronMoth_ChampionDefeat:
	.string "You beat me. I'm still thinking.$"

Nexus_Text_Bugsy_IronMoth_ChampionAfter:
	.string "{SPEAKER NAME_BUGSY}I watched it for an hour before you\n"
	.string "came. It kept circling the hanging sun.\p"
	.string "Round and round. Closer every time.\p"
	.string "Nobody would ever build that into a\n"
	.string "machine. It's useless. It's a moth\l"
	.string "thing.\p"
	.string "So somebody forgot to write that part\n"
	.string "of the manual. Go and read the rest\l"
	.string "of it for me.$"

Nexus_Text_Brock_IronThorns_ChampionIntro:
	.string "I've been digging up fossils since I\n"
	.string "was a kid. Pewter has a whole museum of\l"
	.string "them.\p"
	.string "A fossil tells you what used to live.\n"
	.string "That's the deal. That's what rock is\l"
	.string "for.\p"
	.string "The one out there is warm, and it's\n"
	.string "humming. It's not from the past at all.\p"
	.string "…Let me battle something that makes\n"
	.string "sense for a minute!$"

Nexus_Text_Brock_IronThorns_ChampionDefeat:
	.string "Ha! At least you make sense.$"

Nexus_Text_Brock_IronThorns_ChampionAfter:
	.string "{SPEAKER NAME_BROCK}I measured its plates while it wasn't\n"
	.string "looking. Same pattern as an old armored\l"
	.string "tyrant.\p"
	.string "Just… made. Built, not grown.\p"
	.string "Maybe someday somebody digs up my\n"
	.string "team and wonders what we were.\p"
	.string "I hope they get it right. Go on.$"

Nexus_Text_Proton_RoaringMoon_ChampionIntro:
	.string "Some old expedition journal talks\n"
	.string "about a monster under a red moon.\l"
	.string "Nobody believed it. Too wild. Too mean.\p"
	.string "And there it is. Claw marks down every\n"
	.string "wall. Wings like rags.\p"
	.string "That's the dream, kid. Be the story\n"
	.string "nobody believes until it's too late.\l"
	.string "Let's go!$"

Nexus_Text_Proton_RoaringMoon_ChampionDefeat:
	.string "Too wild, too mean… and still not\n"
	.string "enough.$"

Nexus_Text_Proton_RoaringMoon_ChampionAfter:
	.string "{SPEAKER NAME_PROTON}Funny thing. I watched it for an hour.\n"
	.string "It isn't cruel.\p"
	.string "It's old and it's hungry, and nobody\n"
	.string "ever gave it anything but fear.\p"
	.string "…Don't look at me like that. Go on. Wake\n"
	.string "it up. And don't write any of this down.\l"
	.string "Nobody would believe you.$"

Nexus_Text_Wally_IronValiant_ChampionIntro:
	.string "There's a Pokémon out there with my\n"
	.string "partner's face. Half blade, half gown.\l"
	.string "All made of metal.\p"
	.string "They say it's from a future. Maybe the\n"
	.string "one where nobody gets tired or sick\l"
	.string "anymore.\p"
	.string "It didn't breathe once while I watched.\n"
	.string "I counted.\p"
	.string "…Sorry. Let's battle. I need to know my\n"
	.string "partner is still mine.$"

Nexus_Text_Wally_IronValiant_ChampionDefeat:
	.string "Hah… hah… we're tired. Both of us. Good.$"

Nexus_Text_Wally_IronValiant_ChampionAfter:
	.string "{SPEAKER NAME_WALLY}I used to wish I had a body like that.\n"
	.string "One that never ran out of breath.\p"
	.string "But my partner and I get tired\n"
	.string "together. That's how I know we chose\l"
	.string "to keep going.\p"
	.string "Something that never gets tired never\n"
	.string "has to choose. I don't think I envy it\l"
	.string "anymore.\p"
	.string "Go on. Be kind to it, if you can.$"

Nexus_Text_Juan_WalkingWake_ChampionIntro:
	.string "Did you see its mane? Water, flowing\n"
	.string "backward, like a cape in a gale.\p"
	.string "I spent a lifetime teaching water to\n"
	.string "move with grace. I taught Wallace, you\l"
	.string "know.\p"
	.string "That creature was doing it before\n"
	.string "there was anyone to teach.\p"
	.string "Aahaha! How humbling. How marvelous!\n"
	.string "Come!$"

Nexus_Text_Juan_WalkingWake_ChampionDefeat:
	.string "Aahahaha! Out-danced twice in one day.$"

Nexus_Text_Juan_WalkingWake_ChampionAfter:
	.string "{SPEAKER NAME_JUAN}A teacher likes to believe he invented\n"
	.string "something.\p"
	.string "But the water was already dancing. I\n"
	.string "only learned to stand still long enough\l"
	.string "to see it.\p"
	.string "Wallace understood that before I did.\n"
	.string "I have never told him so.\p"
	.string "Go on. It is waiting in the rain, and it\n"
	.string "does not like to wait.$"

Nexus_Text_Leaf_IronLeaves_ChampionIntro:
	.string "Did you hear the trees out there? They\n"
	.string "ring. The leaves are steel, and not one\l"
	.string "of them has ever fallen.\p"
	.string "My name's a leaf, you know. The real\n"
	.string "kind falls every autumn, and grows\l"
	.string "back in spring.\p"
	.string "I think I'd rather be that kind. Let's\n"
	.string "battle!$"

Nexus_Text_Leaf_IronLeaves_ChampionDefeat:
	.string "Ah! I fell. …That's fine. I grow back.$"

Nexus_Text_Leaf_IronLeaves_ChampionAfter:
	.string "{SPEAKER NAME_GREEN}Something like a knight came out of\n"
	.string "those trees. Sharp, green, and very\l"
	.string "polite about it.\p"
	.string "It's from a time that hasn't happened\n"
	.string "yet. So far ahead that even the leaves\l"
	.string "forgot how to fall.\p"
	.string "I hope it gets to see an autumn. Just\n"
	.string "once.\p"
	.string "Go on! Be gentle with it, if you can.$"

Nexus_Text_Lance_GougingFire_ChampionIntro:
	.string "I know every dragon's line. Dratini to\n"
	.string "Dragonite, Bagon to Salamence, back as\l"
	.string "far as the clan's records go.\p"
	.string "The one in this valley isn't in any of\n"
	.string "them. No parents. No young. It looks\l"
	.string "like somebody's guess about the past.\p"
	.string "And it still fights like a dragon. Let's\n"
	.string "see if you do too!$"

Nexus_Text_Lance_GougingFire_ChampionDefeat:
	.string "No lineage on your side either. Just\n"
	.string "nerve. Well done.$"

Nexus_Text_Lance_GougingFire_ChampionAfter:
	.string "{SPEAKER NAME_LANCE}My clan counts generations. Who\n"
	.string "trained whom, which Dratini came from\l"
	.string "which pool. I grew up thinking that was\l"
	.string "what made a dragon.\p"
	.string "That creature has none of it, and it\n"
	.string "gored through every pillar in this\l"
	.string "valley anyway.\p"
	.string "My cousin would hate it. I think I like\n"
	.string "it.\p"
	.string "Go. It won't care who your teacher was,\n"
	.string "either.$"

Nexus_Text_Drake_RagingBolt_ChampionIntro:
	.string "Did you see it, under that storm? It\n"
	.string "carries the thundercloud on its back.\p"
	.string "Every sailor learns the same lesson.\n"
	.string "You do not fight a storm. You ride it\l"
	.string "out.\p"
	.string "That beast never learned. It just\n"
	.string "picked the storm up and walked off\l"
	.string "with it.\p"
	.string "Ha! I like it. Come!$"

Nexus_Text_Drake_RagingBolt_ChampionDefeat:
	.string "Superb. You rode it out.$"

Nexus_Text_Drake_RagingBolt_ChampionAfter:
	.string "{SPEAKER NAME_DRAKE}I spent years at sea, fearing weather\n"
	.string "I could not change.\p"
	.string "And here is a dragon that simply\n"
	.string "decided the storm was his.\p"
	.string "Freedom, I suppose, is refusing to be\n"
	.string "afraid of what you carry.\p"
	.string "Go. Do not fight the storm. Fight the\n"
	.string "one holding it.$"

Nexus_Text_TateAndLiza_IronBoulder_ChampionIntro:
	.string "Every stone out there has been cut in\n"
	.string "two. The halves lie facing each other,\l"
	.string "like mirrors.\p"
	.string "Rock and Psychic, just like our Solrock\n"
	.string "and Lunatone. But it isn't from our\l"
	.string "time. It's from one that hasn't\l"
	.string "happened.\p"
	.string "People always call us two halves of one\n"
	.string "person.\l"
	.string "Hehehe… Fufufu…\p"
	.string "We'd like a word with whoever started\n"
	.string "that. Let's battle!$"

Nexus_Text_TateAndLiza_IronBoulder_ChampionDefeat:
	.string "Two against one…\n"
	.string "…and still you won.$"

Nexus_Text_TateAndLiza_IronBoulder_ChampionAfter:
	.string "{SPEAKER NAME_TATE_AND_LIZA}Did you look at the cut stones? Both\n"
	.string "halves were smooth. Neither one was\l"
	.string "the broken one.\p"
	.string "We aren't halves. We're two whole\n"
	.string "people who happen to agree about\l"
	.string "almost everything.\p"
	.string "Almost. He likes the sun. I like the\n"
	.string "moon.\l"
	.string "Hehehe… Fufufu…\p"
	.string "That thing cuts everything in two. Go\n"
	.string "show it something that stays whole.$"

Nexus_Text_Will_IronCrown_ChampionIntro:
	.string "The metal one out there wears a crown\n"
	.string "shaped like a blade, and its face is a\l"
	.string "mirror.\p"
	.string "I watched it for an hour. It holds the\n"
	.string "pose of some ancient legend perfectly.\p"
	.string "But there is no one inside the copy.\n"
	.string "Only the pose.\p"
	.string "…It is the first mask that has ever\n"
	.string "frightened me. Let us begin.$"

Nexus_Text_Will_IronCrown_ChampionDefeat:
	.string "You saw through the pose. Mine too, I\n"
	.string "suppose.$"

Nexus_Text_Will_IronCrown_ChampionAfter:
	.string "{SPEAKER NAME_WILL}I took off my mask after I saw it. Just\n"
	.string "to check.\p"
	.string "My face was still there. I was more\n"
	.string "relieved than I would like to admit.\p"
	.string "A mask is only a performance if someone\n"
	.string "is behind it. That thing is all mask.\p"
	.string "Be careful. It will look like whatever\n"
	.string "you expect. So expect nothing.$"

Nexus_Text_Anabel_Deoxys_ChampionIntro:
	.string "It fell from the sky. So did I, more or\n"
	.string "less.\p"
	.string "It changed its shape to survive the\n"
	.string "landing. I lost most of what came\l"
	.string "before mine.\p"
	.string "Two different ways of paying the same\n"
	.string "price.\p"
	.string "I've stopped thinking of it as a loss.\n"
	.string "Let's see what you think.$"

Nexus_Text_Anabel_Deoxys_ChampionDefeat:
	.string "Measured and confirmed. You're\n"
	.string "stronger than I planned for.$"

Nexus_Text_Anabel_Deoxys_ChampionAfter:
	.string "{SPEAKER NAME_ANABEL}People ask me what I was before. I tell\n"
	.string "them the truth: I don't know.\p"
	.string "What I know is what I chose after. The\n"
	.string "police. This work. Staying.\p"
	.string "That creature changed to survive.\n"
	.string "Then it had to decide what to do with\l"
	.string "the shape it had.\p"
	.string "Go on. Find out what it decided.$"

Nexus_Text_Brendan_Reshiram_ChampionIntro:
	.string "That white dragon out there only\n"
	.string "listens to people who tell the truth. I\l"
	.string "read that in three different books.\p"
	.string "So I tried. I told it everything I've\n"
	.string "ever seen. Every Pokémon, every route.\p"
	.string "It didn't care. I think it was waiting\n"
	.string "for the one thing I left out.\p"
	.string "…Battle first. Truth later.$"

Nexus_Text_Brendan_Reshiram_ChampionDefeat:
	.string "Okay. Okay. There's the truth, I guess.$"

Nexus_Text_Brendan_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}Here's what I left out. I always wanted\n"
	.string "to be the one people write about.\p"
	.string "Instead I'm the guy with the notebook,\n"
	.string "writing down what you did.\p"
	.string "I said that out loud to it, and its tail\n"
	.string "stopped burning so hot. Weird, right?\p"
	.string "Anyway. Go on. I'll write this part down\n"
	.string "properly.$"

Nexus_Text_May_Zekrom_ChampionIntro:
	.string "There's a black dragon inside that\n"
	.string "thundercloud. My hair's been standing\l"
	.string "up for an hour!\p"
	.string "The books say it only helps someone\n"
	.string "whose ideals are strong enough.\p"
	.string "I've only ever had one: to see every\n"
	.string "Pokémon there is. Is that big enough\l"
	.string "for a legend?\p"
	.string "Let's find out!$"

Nexus_Text_May_Zekrom_ChampionDefeat:
	.string "Ahaha… my ideals got zapped.$"

Nexus_Text_May_Zekrom_ChampionAfter:
	.string "{SPEAKER NAME_MAY}You know what scared me? Not the\n"
	.string "lightning. How badly I wanted to follow\l"
	.string "it.\p"
	.string "An ideal is like that. It never asks if\n"
	.string "you're tired. It just keeps pulling.\p"
	.string "Dad says a good researcher knows when\n"
	.string "to go home. I'm still learning that part.\p"
	.string "Go ahead. Just remember to come back,\n"
	.string "okay?$"

Nexus_Text_Clair_ChampionIntro:
	.string "Did you see it? Down in the ice. A dragon\n"
	.string "with half of itself missing.\p"
	.string "The old stories say it waits for a hero\n"
	.string "to fill in what it lost. Truth, or ideals.\l"
	.string "Whichever comes first.\p"
	.string "It has waited so long that its own cold\n"
	.string "froze it where it stands.\p"
	.string "…Don't look at me like that. I know what\n"
	.string "waiting feels like. Dragons, go!$"

Nexus_Text_Clair_ChampionDefeat:
	.string "I lost? …No. I am not going to sulk this\n"
	.string "time.$"

Nexus_Text_Clair_ChampionAfter:
	.string "{SPEAKER NAME_CLAIR}When I lost my badge to you, the Elder\n"
	.string "sent me into the Dragon's Den like a\l"
	.string "child.\p"
	.string "I thought he would give me back my\n"
	.string "pride. He gave me questions instead.\p"
	.string "That thing down there is waiting for\n"
	.string "someone to fill it up. Nobody is coming.\l"
	.string "Nobody ever does.\p"
	.string "You fill the hollow yourself, or you\n"
	.string "freeze in it. Go on. Show it how.$"

Nexus_Text_Brawly_Keldeo_ChampionIntro:
	.string "You see it out there? Running on the\n"
	.string "water. Not surfing, dude. Running. Like\l"
	.string "the sea's a road it already picked.\p"
	.string "When I started surfing, I wiped out a\n"
	.string "thousand times. That little guy has\l"
	.string "never fallen once.\p"
	.string "Not 'cause it's strong. 'Cause it made\n"
	.string "up its mind. I respect that. So let's go\l"
	.string "all out!$"

Nexus_Text_Brawly_Keldeo_ChampionDefeat:
	.string "Wiped out. You held your line the whole\n"
	.string "way.$"

Nexus_Text_Brawly_Keldeo_ChampionAfter:
	.string "{SPEAKER NAME_BRAWLY}Here's the thing about never falling.\n"
	.string "You never learn how to get back up.\p"
	.string "I got good because I wiped out. Every\n"
	.string "single time, the sea taught me\l"
	.string "something.\p"
	.string "So don't go easy on that colt. Give it a\n"
	.string "big one to fall off of. It'll come back\l"
	.string "better. That's how it works for all of\l"
	.string "us.$"

Nexus_Text_Wallace_Xerneas_ChampionIntro:
	.string "Did you see the forest? Everything\n"
	.string "blooming at once, and nothing ever\l"
	.string "wilting.\p"
	.string "I should adore it. I have spent my\n"
	.string "whole life chasing beauty.\p"
	.string "And yet… a performance that never\n"
	.string "ends is not a performance.\p"
	.string "Ah, forgive me. Let us make something\n"
	.string "that ends!$"

Nexus_Text_Wallace_Xerneas_ChampionDefeat:
	.string "Bravo. And now it has ended. That is\n"
	.string "the beautiful part.$"

Nexus_Text_Wallace_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_WALLACE}My Milotic was a Feebas once. Plain.\n"
	.string "Overlooked.\p"
	.string "It became beautiful because it\n"
	.string "changed. That creature never has to.\p"
	.string "It gives life to everything around it.\n"
	.string "Even to that endless forest.\p"
	.string "I hope it learns someday how lovely it\n"
	.string "is to wilt. Go on.$"

Nexus_Text_Sidney_Yveltal_ChampionIntro:
	.string "You see those stone birds back there?\n"
	.string "They were flying when it happened.\p"
	.string "My Absol gets blamed for disasters it\n"
	.string "only warns folks about. I've been\l"
	.string "defending it my whole life.\p"
	.string "Well, that thing up ahead doesn't warn\n"
	.string "anybody. It IS the disaster.\p"
	.string "…Heh. Still gotta respect the honesty.\n"
	.string "Let's go!$"

Nexus_Text_Sidney_Yveltal_ChampionDefeat:
	.string "Ha… I lost. Didn't even feel it. Kinda\n"
	.string "like those birds.$"

Nexus_Text_Sidney_Yveltal_ChampionAfter:
	.string "{SPEAKER NAME_SIDNEY}Here's the thing. When it's done\n"
	.string "taking, it wraps itself up and sleeps.\l"
	.string "Just a big quiet cocoon.\p"
	.string "Even the end of the world gets tired.\p"
	.string "My Absol was shaking the whole walk\n"
	.string "here, you know. It knew.\p"
	.string "Go on. Wake it up and show it\n"
	.string "somebody's still breathing.$"

Nexus_Text_Lucy_Zygarde_ChampionIntro:
	.string "…You felt it. The leaves. Watching.\p"
	.string "It doesn't talk either. It just counts.\n"
	.string "Every tree. Every step.\p"
	.string "People think I'm quiet because I'm\n"
	.string "cold.\p"
	.string "…I'm counting too. Go.$"

Nexus_Text_Lucy_Zygarde_ChampionDefeat:
	.string "…Counted wrong. Hmph.$"

Nexus_Text_Lucy_Zygarde_ChampionAfter:
	.string "{SPEAKER NAME_LUCY}…That thing doesn't hate us. It's\n"
	.string "keeping track.\p"
	.string "Every cell is watching a piece of the\n"
	.string "forest, so nothing gets lost.\p"
	.string "At the Pike, I watch every door. Nobody\n"
	.string "notices.\p"
	.string "…Go. It noticed you.$"

Nexus_Text_Blaine_Volcanion_ChampionIntro:
	.string "Hah! Quiz! What happens when fire meets\n"
	.string "water?\p"
	.string "Most folks say the fire goes out. Wrong!\n"
	.string "You get steam. And steam can blow the\l"
	.string "top off a mountain!\p"
	.string "The creature here lives on exactly\n"
	.string "that. It keeps both inside and won't\l"
	.string "let either one win.\p"
	.string "After my volcano, I moved my fire into a\n"
	.string "sea cave. I suppose I've been steam\l"
	.string "ever since!$"

Nexus_Text_Blaine_Volcanion_ChampionDefeat:
	.string "Hah! You held more pressure than I did!$"

Nexus_Text_Blaine_Volcanion_ChampionAfter:
	.string "{SPEAKER NAME_BLAINE}Here's one I never put in my quizzes.\n"
	.string "Real steam is invisible. That white\l"
	.string "cloud is only the part cooling off.\p"
	.string "The power is in the part you can't see.\p"
	.string "That creature hides in its own fog, and\n"
	.string "it doesn't much care for people. Can't\l"
	.string "blame it.\p"
	.string "Don't chase the cloud. Watch the\n"
	.string "pressure. When it goes quiet, get ready.$"

Nexus_Text_Blue_Zacian_ChampionIntro:
	.string "Did you see the statue out there? The\n"
	.string "king got the credit. The one that\l"
	.string "actually fought got a rusty sword.\p"
	.string "I was Champion once, you know. For\n"
	.string "about as long as it took Red to walk up\l"
	.string "the stairs.\p"
	.string "Nobody remembers that. Believe me, I\n"
	.string "do.\p"
	.string "So let's make this one count!$"

Nexus_Text_Blue_Zacian_ChampionDefeat:
	.string "Beaten again… and nobody's even\n"
	.string "watching.$"

Nexus_Text_Blue_Zacian_ChampionAfter:
	.string "{SPEAKER NAME_BLUE}Here's what bugs me. That wolf doesn't\n"
	.string "care. The kings got the statues, and it\l"
	.string "just… kept guarding.\p"
	.string "Me? I'd have been furious. I'd have\n"
	.string "made them fix the plaque.\p"
	.string "Maybe that's why it's the legend, and\n"
	.string "I'm the guy who was Champion for an\l"
	.string "afternoon.\p"
	.string "Go on. Win it fair. Somebody should.$"

Nexus_Text_Norman_Zamazenta_ChampionIntro:
	.string "It stands in front of the others.\n"
	.string "Always. That's what I noticed first.\p"
	.string "The old stories say it held the line\n"
	.string "when the sky went dark. It didn't win\l"
	.string "by attacking. It won by not moving.\p"
	.string "I've tried to be that for my family.\n"
	.string "Not always well. I was often at the Gym.\p"
	.string "…Let me see if my line holds against\n"
	.string "you!$"

Nexus_Text_Norman_Zamazenta_ChampionDefeat:
	.string "My line broke. Fairly. Well done.$"

Nexus_Text_Norman_Zamazenta_ChampionAfter:
	.string "{SPEAKER NAME_NORMAN}Here's what I understood, too late.\p"
	.string "A shield only means something if\n"
	.string "there's someone behind it.\p"
	.string "I spent years facing forward, holding\n"
	.string "the line. By the time I turned around,\l"
	.string "my child had already left on a journey.\p"
	.string "When you face it, don't try to break\n"
	.string "through. Find out what it's\l"
	.string "protecting.$"

Nexus_Text_Tucker_Eternatus_ChampionIntro:
	.string "Ha! Now THAT is an entrance! Red sky,\n"
	.string "every light in the house aimed right at\l"
	.string "it!\p"
	.string "I know a star when I see one. I also\n"
	.string "know a star who's stealing the lights.\p"
	.string "Every stadium over there glowed\n"
	.string "because of that thing. And now it\l"
	.string "wants all that glow back.\p"
	.string "Well, fan? Let's see who the crowd is\n"
	.string "really here for!$"

Nexus_Text_Tucker_Eternatus_ChampionDefeat:
	.string "Hm. Fine. You can have the spotlight.\n"
	.string "For now.$"

Nexus_Text_Tucker_Eternatus_ChampionAfter:
	.string "{SPEAKER NAME_TUCKER}Want to know a secret? Sometimes, in\n"
	.string "the Dome, I've thought about it.\p"
	.string "Taking the whole crowd for myself.\n"
	.string "Every cheer, every light. Nothing left\l"
	.string "for the challenger.\p"
	.string "That thing out there did it. And look\n"
	.string "what it's got. An empty stadium.\p"
	.string "A star gives the crowd something to\n"
	.string "take home. Go remind it, fan!$"

Nexus_Text_LtSurge_Regieleki_ChampionIntro:
	.string "See those yellow rings, kid? That's not\n"
	.string "armor. That's a cage. Somebody built it\l"
	.string "to hold all that power in.\p"
	.string "Every ring it breaks, it gets faster.\n"
	.string "I've seen soldiers like that, baby.\l"
	.string "Take away the rules and they don't\l"
	.string "stop.\p"
	.string "Discipline is the ring you choose to\n"
	.string "wear! Let's go!$"

Nexus_Text_LtSurge_Regieleki_ChampionDefeat:
	.string "Whoa! That was faster than me!$"

Nexus_Text_LtSurge_Regieleki_ChampionAfter:
	.string "{SPEAKER NAME_LT_SURGE}Think I'm loud? Loud's my ring, baby.\n"
	.string "Lets the charge out a little at a time,\l"
	.string "so it never goes off all at once.\p"
	.string "That thing out there never learned to\n"
	.string "yell. It just runs until the lights go\l"
	.string "out.\p"
	.string "One ring left. Don't let it drop that\n"
	.string "one near you.\p"
	.string "Now move it, soldier!$"

Nexus_Text_Drake_Regidrago_ChampionIntro:
	.string "Do you know what I saw in those ruins?\n"
	.string "Heads. Only heads. Jaws and teeth, and\l"
	.string "nothing else.\p"
	.string "Someone once built a dragon out of\n"
	.string "nothing but power.\p"
	.string "No wings. No heart. No partner.\p"
	.string "Ha! Let me show you what it is missing!$"

Nexus_Text_Drake_Regidrago_ChampionDefeat:
	.string "Superb… I have taught you nothing you\n"
	.string "did not already have.$"

Nexus_Text_Drake_Regidrago_ChampionAfter:
	.string "{SPEAKER NAME_DRAKE}Power is the easy part of a dragon. Any\n"
	.string "fool can carve teeth.\p"
	.string "What those builders forgot is that a\n"
	.string "dragon needs somewhere to go, and\l"
	.string "someone to go there with.\p"
	.string "That thing has waited in the dark with\n"
	.string "its mouth open for a very long time.\p"
	.string "Show it the rest. Show it a partner.$"

Nexus_Text_Pryce_Glastrier_ChampionIntro:
	.string "The horse of this field takes whatever\n"
	.string "it wants. By force. It has taken this\l"
	.string "whole harvest.\p"
	.string "Ice does not work that way. Ice waits.\n"
	.string "It has all the time in the world.\p"
	.string "...I wonder which of us is right. You\n"
	.string "will do, as a question.$"

Nexus_Text_Pryce_Glastrier_ChampionDefeat:
	.string "Hm. Force and patience both lost. To\n"
	.string "a child. Wonderful.$"

Nexus_Text_Pryce_Glastrier_ChampionAfter:
	.string "{SPEAKER NAME_PRYCE}Look at its back. There is a place\n"
	.string "there for a rider, worn smooth.\p"
	.string "It takes and takes because no one is\n"
	.string "there to tell it to stop.\p"
	.string "I know something of waiting for\n"
	.string "someone who does not come back.\l"
	.string "...Go on. Be gentle with it.$"

Nexus_Text_Morty_Spectrier_ChampionIntro:
	.string "Close your eyes. Go on. Listen.\p"
	.string "That's hooves. It's been circling us\n"
	.string "since you arrived, and it hasn't looked\l"
	.string "at either of us once.\p"
	.string "It doesn't need eyes. My whole life, I\n"
	.string "trained mine. ...Let's battle.$"

Nexus_Text_Morty_Spectrier_ChampionDefeat:
	.string "I saw every move. It didn't help.$"

Nexus_Text_Morty_Spectrier_ChampionAfter:
	.string "{SPEAKER NAME_MORTY}It hunts by everything except sight.\n"
	.string "Sound. Cold. The fear on your skin.\p"
	.string "All these years, I thought seeing was\n"
	.string "the gift. Seeing what others can't.\p"
	.string "Maybe I was just looking too hard.\n"
	.string "Close your eyes when you face it. It\l"
	.string "will anyway.$"

Nexus_Text_Will_Calyrex_ChampionIntro:
	.string "Did you meet the little king? It sits on\n"
	.string "a stump in the snow, waiting for a\l"
	.string "harvest nobody plants.\p"
	.string "Once, a whole region knelt to it. Then\n"
	.string "people forgot, and every year it grew a\l"
	.string "little smaller.\p"
	.string "An illusion only lasts while someone\n"
	.string "believes in it. I would know. I have built\l"
	.string "a career on that.\p"
	.string "Come. Let me show you what I can make\n"
	.string "you believe.$"

Nexus_Text_Will_Calyrex_ChampionDefeat:
	.string "…A trick needs an audience. You stopped\n"
	.string "believing in me.$"

Nexus_Text_Will_Calyrex_ChampionAfter:
	.string "{SPEAKER NAME_WILL}Here is a secret. Under the mask there\n"
	.string "is only a boy who trained alone in a\l"
	.string "hundred towns.\p"
	.string "The mask is what people remember. The\n"
	.string "boy, nobody would.\p"
	.string "That king never had a mask. When they\n"
	.string "forgot it, there was nothing left to\l"
	.string "hold it up.\p"
	.string "Remember it for me, would you? Even\n"
	.string "small. Especially small.$"

Nexus_Text_Archer_WoChien_ChampionIntro:
	.string "They say this creature was made from a\n"
	.string "grudge. Someone wrote down a king's\l"
	.string "crimes on wooden tablets, and was\l"
	.string "punished for it.\p"
	.string "I keep records too. Every operation.\n"
	.string "Every order. All in my own hand, so\l"
	.string "nothing is lost when the boss returns.\p"
	.string "I never asked myself which side of that\n"
	.string "story I'd be on. Let's not start now.$"

Nexus_Text_Archer_WoChien_ChampionDefeat:
	.string "Noted. In ink.$"

Nexus_Text_Archer_WoChien_ChampionAfter:
	.string "{SPEAKER NAME_ARCHER}The tablets in this forest were written\n"
	.string "by someone brave and scratched out by\l"
	.string "someone powerful.\p"
	.string "My ledgers would read the same, if\n"
	.string "anyone found them. Every order. Every\l"
	.string "date. My handwriting.\p"
	.string "I wrote them so he'd be proud. I'm\n"
	.string "starting to think they're a\l"
	.string "confession.\p"
	.string "Go. It won't forgive you for anything.\n"
	.string "It doesn't know how.$"

Nexus_Text_Proton_TingLu_ChampionIntro:
	.string "You feel that? The air here's heavy.\n"
	.string "Like your arms forgot how strong they\l"
	.string "are.\p"
	.string "That's the big one in the bowl. Folks\n"
	.string "say it's made of fear. Somebody else's,\l"
	.string "poured in and left to set.\p"
	.string "I've made a career out of scaring\n"
	.string "people. Standing next to that thing,\l"
	.string "I'm scared too. Let's fix that!$"

Nexus_Text_Proton_TingLu_ChampionDefeat:
	.string "Heh. So I'm not even the scariest thing\n"
	.string "in this valley.$"

Nexus_Text_Proton_TingLu_ChampionAfter:
	.string "{SPEAKER NAME_PROTON}Here's what I figured out. That thing\n"
	.string "isn't scary on its own. It's full of\l"
	.string "other people's fear. It's borrowed.\p"
	.string "Mine's borrowed too. Nobody was ever\n"
	.string "scared of Proton. They were scared of\l"
	.string "the R on my chest.\p"
	.string "Take that off and… well. Don't tell\n"
	.string "anyone I said that. Go on, get lost.$"

Nexus_Text_Janine_Okidogi_ChampionIntro:
	.string "Hey! Did you see the big one with the\n"
	.string "chain? It punched a boulder in half\l"
	.string "just to show off.\p"
	.string "There's a statue of it in the square.\n"
	.string "Flowers at its feet. A hero, says the\l"
	.string "sign.\p"
	.string "Funny… Nobody here would tell me what\n"
	.string "it did to deserve it.\p"
	.string "I know costumes. A statue's just a\n"
	.string "costume made of stone. Hyah!$"

Nexus_Text_Janine_Okidogi_ChampionDefeat:
	.string "Oof! You hit harder than that thing\n"
	.string "ever did.$"

Nexus_Text_Janine_Okidogi_ChampionAfter:
	.string "{SPEAKER NAME_JANINE}Back home, everyone calls me Koga's\n"
	.string "daughter. It's like a statue of me I\l"
	.string "never posed for.\p"
	.string "So I earn my real name. One battle at a\n"
	.string "time.\p"
	.string "That brute never had to earn anything.\n"
	.string "The chain gives it strength, and the\l"
	.string "statue gives it glory.\p"
	.string "Take both away and see what's left. My\n"
	.string "guess? Not much.$"

Nexus_Text_Janine_Munkidori_ChampionIntro:
	.string "Did it get you too? The little monkey? I\n"
	.string "saw my father standing on the path.\l"
	.string "Then I saw me.\p"
	.string "That wasn't a trick of the light. It\n"
	.string "crawled into my head and moved the\l"
	.string "furniture around.\p"
	.string "I dress my students up as me. It's a\n"
	.string "game! We all laugh after.\p"
	.string "That thing doesn't laugh after. It just\n"
	.string "watches. Hyah!$"

Nexus_Text_Janine_Munkidori_ChampionDefeat:
	.string "You didn't blink once. How?!$"

Nexus_Text_Janine_Munkidori_ChampionAfter:
	.string "{SPEAKER NAME_JANINE}Here's a ninja secret. A good disguise\n"
	.string "always has a seam. A way out, so the\l"
	.string "joke can end.\p"
	.string "What that monkey shows you has no\n"
	.string "seam. You just keep looking.\p"
	.string "If the world starts to wobble, trust\n"
	.string "your Pokémon, not your eyes. They can\l"
	.string "smell what's real.\p"
	.string "…And if you see me in there, it isn't me.\n"
	.string "Promise.$"

Nexus_Text_Roxanne_Terapagos_ChampionIntro:
	.string "I've filled six pages trying to\n"
	.string "classify the crystals down there.\l"
	.string "Every single one is a different color.\p"
	.string "Those rocks were ordinary this\n"
	.string "morning. Granite, basalt. I checked.\l"
	.string "Now they're growing facets.\p"
	.string "I chose Rock types because stones\n"
	.string "don't change on you. I'm starting to\l"
	.string "think I was wrong about that, too.\p"
	.string "…Let me test one thing I'm still sure\n"
	.string "of. My team!$"

Nexus_Text_Roxanne_Terapagos_ChampionDefeat:
	.string "My notes were right about everything\n"
	.string "except the outcome.$"

Nexus_Text_Roxanne_Terapagos_ChampionAfter:
	.string "{SPEAKER NAME_ROXANNE}Here is my conclusion, for what it's\n"
	.string "worth.\p"
	.string "Stones do change. They just do it\n"
	.string "slowly enough that we call it\l"
	.string "permanence.\p"
	.string "That creature doesn't wait. It\n"
	.string "touches a rock and asks it to become\l"
	.string "what it could be, right now.\p"
	.string "Go on ahead. And if you can, bring me\n"
	.string "back one crystal. I'd like to be wrong\l"
	.string "in writing.$"

Nexus_Text_Koga_ChampionIntro:
	.string "Fwahahaha! You passed the stalls of\n"
	.string "sweets on your way here, yes? Pink.\l"
	.string "Sticky. Free.\p"
	.string "I did not eat one. A ninja knows poison\n"
	.string "by its smile.\p"
	.string "Those who ate now follow the little\n"
	.string "thing in the shell. Smiling. Obedient.\p"
	.string "Loyalty that comes from a sweet is not\n"
	.string "loyalty. Let me show you the kind I\l"
	.string "trained!$"

Nexus_Text_Koga_ChampionDefeat:
	.string "Hm! My poison could not find a single\n"
	.string "gap in you.$"

Nexus_Text_Koga_ChampionAfter:
	.string "{SPEAKER NAME_KOGA}I have a daughter. I taught her every\n"
	.string "poison I know, and still she chose to\l"
	.string "take my Gym.\p"
	.string "Nothing forced her. That is how I know\n"
	.string "it was real.\p"
	.string "The thing in the shell will never know\n"
	.string "that feeling. All around it smile\l"
	.string "because they must.\p"
	.string "Do not eat what it offers you. Not even\n"
	.string "one bite.$"

@ Legendary fragments and Looker File text (R17/R18).
Nexus_Text_Kyogre_Arrival:
	.string "Rain. It had been raining here since\n"
	.string "before there was a here.\p"
	.string "There was no shore, only a line where\n"
	.string "the water had not arrived yet, and\l"
	.string "that line kept moving toward you.$"

Nexus_Text_Kyogre_Boss:
	.string "The sea swelled into a shape bigger\n"
	.string "than an island.\p"
	.string "Lines of light glowed along its sides,\n"
	.string "and the rain fell harder, as if it had\l"
	.string "been told to.$"

Nexus_Text_Kyogre_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-382. Sea Basin.\p"
	.string "A sea that wants the whole world back,\n"
	.string "and a Gym Leader who has loved water\l"
	.string "all her life.\p"
	.string "What came back with you fits in a\n"
	.string "bathtub. It still makes it rain indoors,\l"
	.string "a little. I have moved my papers.\p"
	.string "She told me water needs a shore. It may\n"
	.string "be the wisest thing anyone has said to\l"
	.string "me this year.$"

Nexus_Text_Mewtwo_Arrival:
	.string "A burnt mansion on an island of ash. Its\n"
	.string "halls were lined with glass tanks, every\l"
	.string "one cracked open from the inside.\p"
	.string "Torn journal pages drifted across the\n"
	.string "floor. The last one read: 'We could not\l"
	.string "control it.'$"

Nexus_Text_Mewtwo_Boss:
	.string "Every loose page in the mansion lifted\n"
	.string "off the floor at once and hung in the\l"
	.string "air.\p"
	.string "At the end of the hall, something pale\n"
	.string "was floating, and it had been waiting\l"
	.string "for you.$"

Nexus_Text_Mewtwo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-150. Genetic.\p"
	.string "A laboratory that made a power it could\n"
	.string "not hold, and a man who once wanted to\l"
	.string "own it.\p"
	.string "What came back with you was made by no\n"
	.string "one. It is small, and new, and nobody's\l"
	.string "weapon. Keep it that way.$"

Nexus_Text_Genesect_Arrival:
	.string "A factory older than any city, half\n"
	.string "fossil and half machine. Conveyor belts\l"
	.string "carried stone bones past rows of silent\l"
	.string "cannons.\p"
	.string "Somewhere, a targeting beep kept\n"
	.string "repeating.$"

Nexus_Text_Genesect_Boss:
	.string "The beeping stopped. Every cannon on\n"
	.string "the line turned toward you.\p"
	.string "A violet insect of steel dropped from\n"
	.string "the rafters, and the cannon on its back\l"
	.string "was already glowing.$"

Nexus_Text_Genesect_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-649. Paleozoic.\p"
	.string "An ancient hunter rebuilt as a weapon,\n"
	.string "and a retired boss who knows what his\l"
	.string "own soldiers felt.\p"
	.string "What you carried out has no cannon on\n"
	.string "its back. Only an old hunter's patience.\p"
	.string "He asked me who gave it its last order. I\n"
	.string "said no one living. He seemed relieved.$"

Nexus_Text_Lugia_Arrival:
	.string "A lighthouse standing in the open sea.\n"
	.string "No shore, no town. Just the tower and\l"
	.string "its light.\p"
	.string "Every sweep of the beam lit up waves\n"
	.string "that had frozen mid-crash, like glass.$"

Nexus_Text_Lugia_Boss:
	.string "The whirlpool under the tower went\n"
	.string "quiet.\p"
	.string "Something silver rose out of it, and\n"
	.string "when it opened its wings, the frozen\l"
	.string "waves began to fall.$"

Nexus_Text_Lugia_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-249. Guardian of the Deep.\p"
	.string "A lighthouse with no harbor, and a Gym\n"
	.string "Leader who could not stop worrying\l"
	.string "about the ships that were not there.\p"
	.string "What you brought back fits in your two\n"
	.string "hands. The sea stayed calm for it.\p"
	.string "She kept the light on the whole time.\n"
	.string "I have noted that I never asked her\l"
	.string "to.$"

Nexus_Text_HoOh_Arrival:
	.string "A tower on fire. Not burning down.\n"
	.string "Just burning, and burning, and never\l"
	.string "done.\p"
	.string "The flames hung still in the air. Ash\n"
	.string "floated at eye level. Through the\l"
	.string "smoke, a rainbow.$"

Nexus_Text_HoOh_Boss:
	.string "The rainbow bent and came down.\p"
	.string "Wings of seven colors spread over the\n"
	.string "burning tower, and the flames bowed to\l"
	.string "them.$"

Nexus_Text_HoOh_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-250. Rainbow.\p"
	.string "A tower that never finishes burning,\n"
	.string "and a man who has waited for a rainbow\l"
	.string "since he was a child.\p"
	.string "What you carried out of the fire is\n"
	.string "small and warm, and it is not burned.\p"
	.string "He saw it today. He did not say a\n"
	.string "word for a long time. Neither did I.$"

Nexus_Text_Groudon_Arrival:
	.string "A sea that had dried up completely.\p"
	.string "Salt flats and cracks all the way to\n"
	.string "the horizon, and the hulls of ships\l"
	.string "stranded on dry land.\p"
	.string "The sun was so strong there were no\n"
	.string "shadows.$"

Nexus_Text_Groudon_Boss:
	.string "The ground split open. It was not a\n"
	.string "crack. It was a seam of magma.\p"
	.string "Something climbed out of it, glowing\n"
	.string "with lines like a map, and the last\l"
	.string "puddle in the world boiled away.$"

Nexus_Text_Groudon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-383. The Continent.\p"
	.string "All the land a man could ever ask for,\n"
	.string "and the man who once asked for it.\p"
	.string "What came back with you is small, and\n"
	.string "warm to the touch. He looked at it a\l"
	.string "long time. Then he asked me whether\l"
	.string "anyone had been aboard those ships.$"

Nexus_Text_Rayquaza_Arrival:
	.string "A tower with no bottom and no top.\p"
	.string "Above the clouds the sky was dark even\n"
	.string "at noon, and fine dust drifted down\l"
	.string "like snow.\p"
	.string "It tasted of iron. Something up here\n"
	.string "had been eating falling stars.$"

Nexus_Text_Rayquaza_Boss:
	.string "A green line crossed the dark sky,\n"
	.string "turned, and came straight down.\p"
	.string "The dust stopped falling. It had all\n"
	.string "been swallowed.$"

Nexus_Text_Rayquaza_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-384. Sky High.\p"
	.string "A tower above the weather, and a\n"
	.string "Champion who flew up on his own dragon\l"
	.string "to meet it.\p"
	.string "What came back down with you fits in\n"
	.string "two hands. It still looks up. I have\l"
	.string "written that down.$"

Nexus_Text_Dialga_Arrival:
	.string "A stone hall full of clocks, each one\n"
	.string "keeping its own time.\p"
	.string "One ran fast. One ran slow. One had\n"
	.string "stopped centuries ago.\p"
	.string "Under the floor, a deep beat shook, and\n"
	.string "every hand on every clock trembled at\l"
	.string "once.$"

Nexus_Text_Dialga_Boss:
	.string "The beat got louder, and closer, and\n"
	.string "the clocks began to agree with it.\p"
	.string "Something steel and blue stood at the\n"
	.string "end of the hall. Its chest glowed on\l"
	.string "every beat.$"

Nexus_Text_Dialga_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-483. Heartbeat.\p"
	.string "A hall where the clocks obey a heart,\n"
	.string "and an old man who would not ask it for\l"
	.string "one more minute.\p"
	.string "What came back with you has a small,\n"
	.string "quick heartbeat. The clock on my wall\l"
	.string "has started keeping time with it. I\l"
	.string "have decided not to mind.$"

Nexus_Text_Palkia_Arrival:
	.string "A plain of pale stone that went on too\n"
	.string "far. The horizon was folded, and a\l"
	.string "second horizon hung upside down above\l"
	.string "the first.\p"
	.string "Your own footsteps echoed from\n"
	.string "somewhere in front of you.$"

Nexus_Text_Palkia_Boss:
	.string "The distance between you and the far\n"
	.string "mountains vanished. They were simply\l"
	.string "here.\p"
	.string "Between them stood a great\n"
	.string "pearl-shouldered shape, and space\l"
	.string "rippled off it like heat.$"

Nexus_Text_Palkia_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-484. Spatial.\p"
	.string "A place where far and near had traded\n"
	.string "places, and a woman who sees tomorrow\l"
	.string "but never where she stands.\p"
	.string "What came home with you fits in your\n"
	.string "arms. The room around it is perfectly\l"
	.string "straight. I measured.$"

Nexus_Text_Giratina_Arrival:
	.string "Nothing here agreed on which way was\n"
	.string "down.\p"
	.string "A waterfall ran sideways across the\n"
	.string "sky. Trees grew from the undersides of\l"
	.string "floating rocks. Your shadow fell up.$"

Nexus_Text_Giratina_Boss:
	.string "The shadows gathered into one, huge\n"
	.string "and long, and black wings tipped with\l"
	.string "red unfolded out of it.\p"
	.string "Somewhere, the right way up was being\n"
	.string "torn open again.$"

Nexus_Text_Giratina_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-487. Renegade.\p"
	.string "A world with no down, and a young man\n"
	.string "who ran from his father and never quite\l"
	.string "stopped.\p"
	.string "What came back with you is a small\n"
	.string "shadow that falls the right way. For\l"
	.string "now. He asked me if it would stay that\l"
	.string "way. I told him that depends on who\l"
	.string "raises it.$"

Nexus_Text_Solgaleo_Arrival:
	.string "The clock on the tower said midnight.\n"
	.string "The sky said noon.\p"
	.string "Every shadow in the square pointed the\n"
	.string "same way, away from something just\l"
	.string "out of sight.$"

Nexus_Text_Solgaleo_Boss:
	.string "All the shadows swung around at once.\p"
	.string "It walked into the square, and the\n"
	.string "stones under its feet glowed white.$"

Nexus_Text_Solgaleo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-791. Sunne.\p"
	.string "A midnight lit up like noon, and a\n"
	.string "professor taking notes in it with a\l"
	.string "very large grin.\p"
	.string "What is left of it is a small cloud\n"
	.string "that glows when you speak to it. It\l"
	.string "begins again from there.$"

Nexus_Text_Lunala_Arrival:
	.string "Night, and no ground under it. A black\n"
	.string "lake stretched out in every direction,\l"
	.string "holding the stars perfectly still.\p"
	.string "There was no moon in the sky. Only a\n"
	.string "round hole where it should have been.$"

Nexus_Text_Lunala_Boss:
	.string "The round hole in the sky opened its\n"
	.string "wings.\p"
	.string "The stars went out one row at a time,\n"
	.string "and a third eye began to shine.$"

Nexus_Text_Lunala_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-792. Moone.\p"
	.string "A night that swallowed its own moon,\n"
	.string "and a young lady whose moon once fit\l"
	.string "inside her bag.\p"
	.string "What came back with you is a little\n"
	.string "cloud of stars. She asked me whose it\l"
	.string "was. I said: whoever carries it.$"

Nexus_Text_Necrozma_Arrival:
	.string "A room of broken glass, split into a\n"
	.string "thousand prisms.\p"
	.string "Each piece gave back a sliver of light.\n"
	.string "None of them gave back your whole\l"
	.string "reflection.\p"
	.string "In the middle, a dark space where light\n"
	.string "went in and did not come out.$"

Nexus_Text_Necrozma_Boss:
	.string "The prisms turned, all together, toward\n"
	.string "the dark space.\p"
	.string "Something black and jagged unfolded\n"
	.string "out of it and reached for the light,\l"
	.string "and every reflection in the room went\l"
	.string "dim.$"

Nexus_Text_Necrozma_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-800. Prism.\p"
	.string "The creature we chased across Johto,\n"
	.string "and an Anabel who is not quite ours,\l"
	.string "standing guard in front of it.\p"
	.string "What came back with you is small and\n"
	.string "gives off an uneven light. It does not\l"
	.string "steal. It only looks for more. Anabel,\l"
	.string "ours, sat with it for an hour and did\l"
	.string "not say why.$"

Nexus_Text_Koraidon_Arrival:
	.string "A valley under a sun that did not set.\n"
	.string "It hung closer than ours, and redder.\p"
	.string "The ground was too warm to stand still\n"
	.string "on. The ferns were as tall as houses.\p"
	.string "In the middle of the valley, a round\n"
	.string "stone had been chewed on.$"

Nexus_Text_Koraidon_Boss:
	.string "The sun got brighter, and something\n"
	.string "roared back at it.\p"
	.string "It came down the valley on all fours,\n"
	.string "fast, like it had been waiting a very\l"
	.string "long time for someone to race.$"

Nexus_Text_Koraidon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1007. The Old Sun.\p"
	.string "A valley that is always noon, and a\n"
	.string "woman who scores everything in three\l"
	.string "turns.\p"
	.string "What came back with you is little, hot\n"
	.string "to the touch, and it already tried to\l"
	.string "eat my notebook. I am giving it a very\l"
	.string "high score for Body.$"

Nexus_Text_Miraidon_Arrival:
	.string "A highway of violet light, running over\n"
	.string "a city no one has built yet.\p"
	.string "The lamps hummed. The road lit up one\n"
	.string "step ahead of your feet, as if it\l"
	.string "already knew where you were going.\p"
	.string "Nobody was driving.$"

Nexus_Text_Miraidon_Boss:
	.string "Two lights came on at the end of the\n"
	.string "road.\p"
	.string "They were not headlights. They blinked,\n"
	.string "and the whole street hummed louder,\l"
	.string "the way a machine does when it wakes\l"
	.string "up.$"

Nexus_Text_Miraidon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1008. The Road Ahead.\p"
	.string "A highway to a city not built yet, and a\n"
	.string "man who swears a manual beats a\l"
	.string "friendship.\p"
	.string "What came back with you is small, and\n"
	.string "warm like an engine left running. There\l"
	.string "is no manual for it. I checked.$"

Nexus_Text_Silvally_Arrival:
	.string "White rooms, too clean and too cold.\n"
	.string "Rows of glass tanks stood open and\l"
	.string "empty.\p"
	.string "On the floor under each one lay a\n"
	.string "heavy helmet, split down the middle.$"

Nexus_Text_Silvally_Boss:
	.string "Claws on tile, somewhere behind the\n"
	.string "tanks.\p"
	.string "It stepped into the light with nothing\n"
	.string "on its face, and its crest changed\l"
	.string "color twice while it looked at you.$"

Nexus_Text_Silvally_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-773. Synthetic.\p"
	.string "A laboratory that built a weapon, and\n"
	.string "then a cage for it. The weapon kept\l"
	.string "neither.\p"
	.string "What you carried out was small, and it\n"
	.string "wore no mask at all. I have written\l"
	.string "that down twice.$"

Nexus_Text_Ogerpon_Arrival:
	.string "A mountain village on festival night.\n"
	.string "Lanterns everywhere, and every face in\l"
	.string "the crowd hidden behind the same ogre\l"
	.string "mask.\p"
	.string "Up the hill, above the lanterns,\n"
	.string "something small was watching. It wore a\l"
	.string "mask too.$"

Nexus_Text_Ogerpon_Boss:
	.string "The small thing came down the hill, and\n"
	.string "the crowd scattered.\p"
	.string "Only its mask held still. The eyes\n"
	.string "behind it were not angry. They were\l"
	.string "tired of being called a monster.$"

Nexus_Text_Ogerpon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1017. Mask.\p"
	.string "A festival that tells its story\n"
	.string "backward, and a man who lies for a\l"
	.string "living and could not stand to watch it.\p"
	.string "The fragment you brought back wears\n"
	.string "no mask at all. Only a face. That is\l"
	.string "rarer than you would think.$"

Nexus_Text_Articuno_Arrival:
	.string "A mountain pass in a blizzard, except\n"
	.string "the blizzard had stopped moving.\p"
	.string "Every snowflake hung in the air. Old\n"
	.string "footprints ran up the slope and ended,\l"
	.string "one by one, in the middle of nowhere.$"

Nexus_Text_Articuno_Boss:
	.string "The snowflakes began to fall again, all\n"
	.string "at once.\p"
	.string "A long blue tail swept through them,\n"
	.string "and the air turned so cold it rang.$"

Nexus_Text_Articuno_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-144. Freeze.\p"
	.string "A pass where travelers stop walking,\n"
	.string "and an old man who walked it anyway,\l"
	.string "slowly, and did not stop.\p"
	.string "What you brought back is cold to the\n"
	.string "touch. It has no intention of melting.\p"
	.string "He said the cold was an old friend. I\n"
	.string "have written that down, and then sat\l"
	.string "with it for a while.$"

Nexus_Text_GalarianArticuno_Arrival:
	.string "A frozen lake under a pale violet sky.\n"
	.string "Snow hung in the air and did not fall.\p"
	.string "Figures stood on the ice, people and\n"
	.string "Pokémon, perfectly still, all looking up.$"

Nexus_Text_GalarianArticuno_Boss:
	.string "The snow began to turn, slowly, around a\n"
	.string "single point.\p"
	.string "A blue-violet bird hung over the lake\n"
	.string "without beating its wings, and its eyes\l"
	.string "began to glow.$"

Nexus_Text_GalarianArticuno_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-144. Cruel.\p"
	.string "A lake of frozen watchers, and a medium\n"
	.string "who once froze people with a look and\l"
	.string "chose to stop.\p"
	.string "The fragment you carried out has not\n"
	.string "learned that look yet. Be the first\l"
	.string "thing it sees kindly.$"

Nexus_Text_Zapdos_Arrival:
	.string "A power plant, long abandoned. Every\n"
	.string "machine was dead, rusted, gutted.\p"
	.string "And yet every light in the building was\n"
	.string "on, humming, fed by nothing you could\l"
	.string "see.$"

Nexus_Text_Zapdos_Boss:
	.string "Thunder rolled, indoors.\p"
	.string "Something yellow and jagged dropped\n"
	.string "out of the dark rafters, and every bulb\l"
	.string "in the building burst at once.$"

Nexus_Text_Zapdos_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-145. Electric.\p"
	.string "A plant that runs on a storm, and a\n"
	.string "soldier whose life was saved by\l"
	.string "lightning once.\p"
	.string "What came back with you is a chick. Its\n"
	.string "feathers crackle when it sneezes. I\l"
	.string "have learned not to stand close.\p"
	.string "He saluted it before he left. I do not\n"
	.string "think he noticed he was doing it.$"

Nexus_Text_GalarianZapdos_Arrival:
	.string "A wide, flat plain under an empty sky.\p"
	.string "Deep grooves ran across it in straight\n"
	.string "lines, as if something had sprinted\l"
	.string "back and forth all night. Golden\l"
	.string "feathers lay in the grooves, crackling.$"

Nexus_Text_GalarianZapdos_Boss:
	.string "The ground shook in a quick, steady\n"
	.string "rhythm.\p"
	.string "Something came running over the\n"
	.string "horizon, fast as thunder, with its\l"
	.string "wings folded tight. Not once did it try\l"
	.string "to fly.$"

Nexus_Text_GalarianZapdos_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-145. Strong Legs.\p"
	.string "A bird that chose the ground, and a\n"
	.string "woman who has never once chosen it.\p"
	.string "What came back with you followed me\n"
	.string "into the next room on foot. I let it. It\l"
	.string "seemed important.$"

Nexus_Text_Moltres_Arrival:
	.string "A frozen valley under grey cloud, locked\n"
	.string "in a winter that would not end.\p"
	.string "But a strip of melted snow ran across\n"
	.string "it, steaming, with green shoots poking\l"
	.string "out of the mud.$"

Nexus_Text_Moltres_Boss:
	.string "The clouds lit up from underneath,\n"
	.string "orange and gold.\p"
	.string "A great bird of fire swept down over the\n"
	.string "snow, and the valley behind it turned to\l"
	.string "spring.$"

Nexus_Text_Moltres_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-146. Flame.\p"
	.string "A winter that would not end, and a man\n"
	.string "whose island was taken by fire, still\l"
	.string "waiting for it to be kind.\p"
	.string "What you brought back is a small flame,\n"
	.string "barely a candle. The snow around the\l"
	.string "altar melted anyway.$"

Nexus_Text_GalarianMoltres_Arrival:
	.string "A forest, burning. There was no smoke,\n"
	.string "and no heat.\p"
	.string "The flames were dark purple. The trees\n"
	.string "they touched still stood, but their\l"
	.string "bark had gone grey, and they no longer\l"
	.string "looked alive.$"

Nexus_Text_GalarianMoltres_Boss:
	.string "A shadow crossed the treetops, and\n"
	.string "every flame in the forest leaned toward\l"
	.string "it.\p"
	.string "It landed on a burned-out branch, and\n"
	.string "the branch did not break. There was\l"
	.string "nothing left in it to break.$"

Nexus_Text_GalarianMoltres_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-146. Malevolent.\p"
	.string "A forest burned hollow, and a woman who\n"
	.string "defends things for the very colour\l"
	.string "people fear.\p"
	.string "What came back with you is small, and\n"
	.string "its flame is still dark. It has not\l"
	.string "burned anything. I would like the record\l"
	.string "to show that.$"

Nexus_Text_Raikou_Arrival:
	.string "A plain under a black sky, lit white from\n"
	.string "above.\p"
	.string "A bolt of lightning hung between the\n"
	.string "clouds and the grass. It did not\l"
	.string "flicker. It had forgotten how to finish\l"
	.string "falling.$"

Nexus_Text_Raikou_Boss:
	.string "The bolt came down at last. It did not\n"
	.string "strike the ground.\p"
	.string "It landed on four legs, and the thunder\n"
	.string "came after it, late.$"

Nexus_Text_Raikou_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-243. Thunder.\p"
	.string "A storm stopped at the instant of the\n"
	.string "strike, and a researcher who finally saw\l"
	.string "the one that got away.\p"
	.string "What came back with you crackles in its\n"
	.string "sleep. I have moved my notes to a drier\l"
	.string "pocket.$"

Nexus_Text_Entei_Arrival:
	.string "A tower on fire. Old wood, a bell\n"
	.string "somewhere inside, and smoke that\l"
	.string "smelled of a hundred and fifty years.\p"
	.string "The fire should have burned out long\n"
	.string "ago. It had not.$"

Nexus_Text_Entei_Boss:
	.string "Something barked inside the flames.\n"
	.string "Every fire in the tower lay flat, the way\l"
	.string "a dog lies down.\p"
	.string "Then it rose, and so did they.$"

Nexus_Text_Entei_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-244. Volcano.\p"
	.string "A tower that never stopped burning, and\n"
	.string "a man who read about that fire until he\l"
	.string "could smell it.\p"
	.string "What came back with you is small and\n"
	.string "very warm. It did not flinch at the\l"
	.string "smoke. I did.$"

Nexus_Text_Suicune_Arrival:
	.string "A lake so clear it had no surface. You\n"
	.string "could see every stone on the bottom,\l"
	.string "and no water at all.\p"
	.string "A cold wind blew from the north, and the\n"
	.string "ripples ran against it.$"

Nexus_Text_Suicune_Boss:
	.string "The wind stopped. Something stepped\n"
	.string "onto the lake, and the water held it.\p"
	.string "Wherever it walked, the lake grew\n"
	.string "clearer still.$"

Nexus_Text_Suicune_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-245. Aurora.\p"
	.string "A lake clean enough to drown in, and a\n"
	.string "man who spent ten years learning its\l"
	.string "tracks.\p"
	.string "What came back with you is small and\n"
	.string "leaves wet pawprints. He will want to\l"
	.string "see them. Let him.$"

Nexus_Text_Regirock_Arrival:
	.string "A stone chamber with no roof, under a\n"
	.string "sky full of blowing sand.\p"
	.string "The walls were covered in raised dots,\n"
	.string "row after row. Some rows had been worn\l"
	.string "smooth by hands.\p"
	.string "On the floor lay stones from a hundred\n"
	.string "different places.$"

Nexus_Text_Regirock_Boss:
	.string "The stones on the floor rolled toward\n"
	.string "the far wall, one by one.\p"
	.string "They climbed onto something that was\n"
	.string "standing there, and it turned. Seven\l"
	.string "dots on its face lit up.$"

Nexus_Text_Regirock_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-377. Mended Stone.\p"
	.string "A chamber of messages, and a king of\n"
	.string "pyramids who got lost in it on purpose.\p"
	.string "What came back with you is a small,\n"
	.string "rough stone with dots on it. It picks\l"
	.string "up pebbles from my floor and tries them\l"
	.string "on. I have stopped sweeping.$"

Nexus_Text_Regice_Arrival:
	.string "A cave of ice where nothing melted.\p"
	.string "Lava had poured through a crack in the\n"
	.string "wall long ago, and had frozen halfway\l"
	.string "down.\p"
	.string "Inside the ice, you could see\n"
	.string "footprints. Someone had tried to\l"
	.string "leave.$"

Nexus_Text_Regice_Boss:
	.string "The air got so cold that it rang.\p"
	.string "Something stood up out of the ice\n"
	.string "floor, as clear as glass, with seven\l"
	.string "dots across its face.$"

Nexus_Text_Regice_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-378. Unmelting.\p"
	.string "A cave where even fire froze, and a\n"
	.string "loud man who stood in it until he got\l"
	.string "quiet.\p"
	.string "What came back with you is a small,\n"
	.string "clear chip of ice. It sits beside my\l"
	.string "coffee, and my coffee is always cold\l"
	.string "now. That is fair.$"

Nexus_Text_Registeel_Arrival:
	.string "A tomb of dark metal, with no door and\n"
	.string "not a speck of rust.\p"
	.string "Every footstep echoed for a long time,\n"
	.string "as if there was nothing inside to stop\l"
	.string "the sound.$"

Nexus_Text_Registeel_Boss:
	.string "The echo came back wrong. It came back\n"
	.string "as a hum.\p"
	.string "A shape of dark steel stepped out of\n"
	.string "the wall, and the seven dots on its\l"
	.string "face lit one at a time.$"

Nexus_Text_Registeel_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-379. Hollow Steel.\p"
	.string "A tomb that rings, and an explorer who\n"
	.string "listened to the echo instead of\l"
	.string "digging.\p"
	.string "What came back with you is a small\n"
	.string "steel piece that hums when it is\l"
	.string "tapped. It is hollow. I tapped it more\l"
	.string "than I should have.$"

Nexus_Text_Latias_Arrival:
	.string "An island at dusk, in a sea as still as\n"
	.string "glass.\p"
	.string "The air above the water kept bending,\n"
	.string "like heat over a road. Now and then, it\l"
	.string "bent into the shape of wings.$"

Nexus_Text_Latias_Boss:
	.string "The bent air folded in on itself and\n"
	.string "became something red and white,\l"
	.string "hovering at eye level.\p"
	.string "It tilted its head, the way a person\n"
	.string "does when they are listening.$"

Nexus_Text_Latias_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-380. The Eon Sister.\p"
	.string "An island where the air hides someone\n"
	.string "who understands every word you say,\l"
	.string "and twins who have never needed words.\p"
	.string "What came back with you hides behind\n"
	.string "my coat whenever I look at it directly.\l"
	.string "So I have stopped looking directly. We\l"
	.string "get along much better.$"

Nexus_Text_Latios_Arrival:
	.string "An island at dusk. The sky was full of\n"
	.string "pictures.\p"
	.string "Cities you had never visited, rooms you\n"
	.string "half remembered, faces seen from\l"
	.string "above. All of it drifted past, as if\l"
	.string "someone far away were sharing what it\l"
	.string "saw.$"

Nexus_Text_Latios_Boss:
	.string "The pictures stopped.\p"
	.string "Something blue and white came down out\n"
	.string "of them, fast, and for a moment you saw\l"
	.string "yourself through its eyes.$"

Nexus_Text_Latios_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-381. The Eon Brother.\p"
	.string "An island where someone shares\n"
	.string "everything it sees, and twins who have\l"
	.string "never had a thought they did not\l"
	.string "share.\p"
	.string "What came back with you showed me,\n"
	.string "very briefly, my own desk. From above.\l"
	.string "It needs tidying. I did not need to be\l"
	.string "told.$"

Nexus_Text_Uxie_Arrival:
	.string "A still lake, and on its surface floated\n"
	.string "hundreds of loose pages.\p"
	.string "Every page was blank. The ink had only\n"
	.string "just left them. It was still spreading\l"
	.string "through the water in thin gray\l"
	.string "threads.$"

Nexus_Text_Uxie_Boss:
	.string "The pages stopped drifting.\p"
	.string "Something rose from the middle of the\n"
	.string "lake with its eyes shut tight. It felt,\l"
	.string "somehow, like it was being polite.$"

Nexus_Text_Uxie_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-480. Keeper of Memory.\p"
	.string "A lake of blank pages, and a teacher\n"
	.string "who writes everything down so she\l"
	.string "never has to trust her memory.\p"
	.string "What came back with you is very small,\n"
	.string "and it keeps its eyes closed. I did not\l"
	.string "check what I still remember. I would\l"
	.string "rather not know.$"

Nexus_Text_Mesprit_Arrival:
	.string "A lake in the fog, and on its surface,\n"
	.string "faces.\p"
	.string "Some were laughing and some were\n"
	.string "crying, and every time the water moved,\l"
	.string "they traded places.$"

Nexus_Text_Mesprit_Boss:
	.string "Something pink flew low over the water,\n"
	.string "and every face turned toward it.\p"
	.string "For a moment you felt happy and sad at\n"
	.string "once, and could not tell which had come\l"
	.string "first.$"

Nexus_Text_Mesprit_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-481. Emotion.\p"
	.string "A lake that feels everything at once,\n"
	.string "and a girl who laughs so she will not\l"
	.string "have to cry.\p"
	.string "What came back with you cried a little\n"
	.string "on the way. So did she, I think. I have\l"
	.string "written that in pencil.$"

Nexus_Text_Azelf_Arrival:
	.string "A lake with no water in it. Only cracked\n"
	.string "mud, and a crater in the middle, as if\l"
	.string "something had exploded.\p"
	.string "In the last puddles, Magikarp were still\n"
	.string "flopping. Not one of them had given up.$"

Nexus_Text_Azelf_Boss:
	.string "The mud at the bottom of the crater\n"
	.string "stirred.\p"
	.string "Something small and blue rose out of it,\n"
	.string "and every Magikarp went still, as if\l"
	.string "listening.$"

Nexus_Text_Azelf_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-482. Willpower.\p"
	.string "A lake blown dry, and a boy who once\n"
	.string "could not climb a hill without resting.\p"
	.string "What came back with you is tiny and will\n"
	.string "not stay put. Neither will he. I have\l"
	.string "stopped trying to keep them in one\l"
	.string "place.$"

Nexus_Text_Heatran_Arrival:
	.string "The inside of a mountain, lit from\n"
	.string "below.\p"
	.string "The walls were iron, slowly cooling, and\n"
	.string "the lava in the channels glowed\l"
	.string "brighter every time you looked away.$"

Nexus_Text_Heatran_Boss:
	.string "Something scraped across the ceiling,\n"
	.string "right above you.\p"
	.string "It hung upside down on cross-shaped\n"
	.string "feet, and its body glowed like metal\l"
	.string "fresh from the forge.$"

Nexus_Text_Heatran_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-485. Lava Dome.\p"
	.string "A mountain with a furnace for a heart,\n"
	.string "and a young Gym Leader trying very\l"
	.string "hard to burn as hot as her\l"
	.string "grandfather.\p"
	.string "What came back with you is small and\n"
	.string "warm, and it clings to anything above\l"
	.string "it. I have noted the ceiling. I am not\l"
	.string "sure why.$"

Nexus_Text_Regigigas_Arrival:
	.string "The ground under your feet was\n"
	.string "moving. Slowly, like a barge.\p"
	.string "Ropes as thick as towers ran from its\n"
	.string "edge to the horizon, creaking, pulling\l"
	.string "a whole country along behind them.$"

Nexus_Text_Regigigas_Boss:
	.string "The ropes went slack.\p"
	.string "At the end of them stood something\n"
	.string "huge and very still, and it took a long\l"
	.string "time to decide to look at you.$"

Nexus_Text_Regigigas_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-486. Colossal.\p"
	.string "A land being dragged across the sea,\n"
	.string "and a girl from a big city who cried\l"
	.string "when she lost and then did not stop\l"
	.string "trying.\p"
	.string "What you brought back is small enough\n"
	.string "to carry. The ropes did not come.\p"
	.string "I told her that is also how\n"
	.string "continents move. She hit me. Gently.$"

Nexus_Text_Cresselia_Arrival:
	.string "A lake under a thin crescent moon.\p"
	.string "The water was so still it didn't ripple\n"
	.string "when you breathed. Along the shore,\l"
	.string "people lay asleep in the grass, and\l"
	.string "every one of them was smiling.$"

Nexus_Text_Cresselia_Boss:
	.string "Something pale rose over the water,\n"
	.string "trailing light like a scarf of cloud.\p"
	.string "Every sleeper on the shore sighed at\n"
	.string "once. None of them woke.$"

Nexus_Text_Cresselia_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-488. Lunar.\p"
	.string "A lake of good dreams, and a woman who\n"
	.string "once filled another lake with a signal\l"
	.string "made to hurt.\p"
	.string "The fragment you brought back is as\n"
	.string "light as a feather. Keep it near your\l"
	.string "pillow. That much, the old stories got\l"
	.string "right.$"

Nexus_Text_Cobalion_Arrival:
	.string "A battlefield long after the battle.\n"
	.string "Rusted swords stood in the ground as\l"
	.string "thick as a forest.\p"
	.string "Small Pokémon hid between them, and\n"
	.string "none of them ran. They were waiting\l"
	.string "for someone.$"

Nexus_Text_Cobalion_Boss:
	.string "The small ones came out of hiding.\p"
	.string "Something with a steel heart walked\n"
	.string "between the swords, and every blade\l"
	.string "leaned away to let it pass.$"

Nexus_Text_Cobalion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-638. Iron Will.\p"
	.string "A field of rusted swords, and a man\n"
	.string "who hits things for a living, learning\l"
	.string "that a fist can also be a shield.\p"
	.string "What you brought back stood in front\n"
	.string "of my shoe the whole way. I let it.\p"
	.string "He says the lesson hurt more than the\n"
	.string "waterfall. I have written that he is\l"
	.string "exaggerating. He is not.$"

Nexus_Text_Terrakion_Arrival:
	.string "A castle, or the wall of one. A hole had\n"
	.string "been punched straight through it,\l"
	.string "taller than a house.\p"
	.string "On the far side, Pokémon were asleep in\n"
	.string "the rubble, as if it were the safest\l"
	.string "place they knew.$"

Nexus_Text_Terrakion_Boss:
	.string "The ground shook. Something heavy and\n"
	.string "grey, with horns like a battering ram,\l"
	.string "stepped into the gap in the wall.\p"
	.string "The Pokémon behind it did not wake up.\n"
	.string "They did not need to.$"

Nexus_Text_Terrakion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-639. Cavern.\p"
	.string "A broken wall with the weak asleep\n"
	.string "behind it, and a Gym Leader who has\l"
	.string "spent his life being the wall.\p"
	.string "What came back with you is a calf. It\n"
	.string "planted its feet in front of me the\l"
	.string "moment I came near. It is guarding\l"
	.string "already.\p"
	.string "He told me walls are not made to be hit.\n"
	.string "They are made to be leaned on.$"

Nexus_Text_Virizion_Arrival:
	.string "A meadow of tall grass. Hidden in it lay\n"
	.string "old blades, swords and spearheads\l"
	.string "rusted through, with flowers growing\l"
	.string "out of them.\p"
	.string "Something had fought here once.\n"
	.string "Something had won.$"

Nexus_Text_Virizion_Boss:
	.string "The grass parted in a straight line\n"
	.string "toward you, as if cut.\p"
	.string "At the end of it stood a green shape\n"
	.string "with horns like drawn blades, between\l"
	.string "you and the small Pokémon hiding in the\l"
	.string "grass.$"

Nexus_Text_Virizion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-640. Grassland.\p"
	.string "A meadow that remembers a war, and a\n"
	.string "guardian who never left it.\p"
	.string "A gentle Gym Leader stood between us\n"
	.string "and it today, and it allowed her.\p"
	.string "What followed you home is small and all\n"
	.string "legs. It already stands in front of your\l"
	.string "other Pokémon. Old habits.$"

Nexus_Text_Tornadus_Arrival:
	.string "Roofs. Hundreds of them, torn off\n"
	.string "whole towns and turning slowly in the\l"
	.string "air, like leaves that refuse to fall.\p"
	.string "The path was a line of loose tiles,\n"
	.string "held up by nothing but the wind.$"

Nexus_Text_Tornadus_Boss:
	.string "The wind stopped pushing and started\n"
	.string "pulling.\p"
	.string "Something rode down on a cloud,\n"
	.string "laughing, and every roof in the sky\l"
	.string "turned to face it.$"

Nexus_Text_Tornadus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-641. Whirlwind.\p"
	.string "A sky full of stolen roofs, and a young\n"
	.string "man who fought under it without once\l"
	.string "looking down.\p"
	.string "What you carried back is only a gust\n"
	.string "of it. It still tugs at my hat.\p"
	.string "He says his father's birds never look\n"
	.string "down either. I have written that down\l"
	.string "as a family trait.$"

Nexus_Text_Thundurus_Arrival:
	.string "A forest of treetop houses, with rope\n"
	.string "bridges swaying between them.\p"
	.string "The sky was one enormous cloud,\n"
	.string "hanging so low that the highest roofs\l"
	.string "vanished into it.$"

Nexus_Text_Thundurus_Boss:
	.string "The cloud crackled.\p"
	.string "Someone was riding it -- a figure with a\n"
	.string "tail of lightning, laughing -- and every\l"
	.string "bolt it threw landed a little closer to\l"
	.string "the bridges.$"

Nexus_Text_Thundurus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-642. Bolt Strike.\p"
	.string "A sky that throws lightning at the\n"
	.string "tallest thing it can find, and a woman\l"
	.string "who has always lived as high as she\l"
	.string "could.\p"
	.string "What came back with you is small, and it\n"
	.string "does not ride a cloud. I checked twice.\l"
	.string "It still laughs when it thunders.$"

Nexus_Text_Landorus_Arrival:
	.string "Fields of golden wheat to every\n"
	.string "horizon, heavy and bent with grain.\p"
	.string "No one had come to harvest them.\p"
	.string "Overhead, a single cloud drifted low,\n"
	.string "and seeds fell from it like rain.$"

Nexus_Text_Landorus_Boss:
	.string "The cloud came down to the field.\p"
	.string "Someone was riding it, laughing like\n"
	.string "thunder over the hills, and the wheat\l"
	.string "bowed flat as it passed.$"

Nexus_Text_Landorus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-645. The Harvest Cloud.\p"
	.string "Endless harvest and no hands to\n"
	.string "gather it, and a scientist who once\l"
	.string "promised land to all of humanity.\p"
	.string "What came back with you is small, and it\n"
	.string "sleeps on the windowsill in the sun. He\l"
	.string "said, very quietly, that he had\l"
	.string "forgotten to count the farmers.$"

Nexus_Text_TapuKoko_Arrival:
	.string "An empty stadium under a sky full of\n"
	.string "thunderclouds.\p"
	.string "Scorch marks crossed the field in\n"
	.string "rings, as if someone had practiced\l"
	.string "there for a very long time.$"

Nexus_Text_TapuKoko_Boss:
	.string "Lightning struck the center of the\n"
	.string "field and stayed there.\p"
	.string "It wasn't lightning. It held the two\n"
	.string "halves of a shell open, and it looked\l"
	.string "at you with great interest.$"

Nexus_Text_TapuKoko_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-785. Guardian of Melemele.\p"
	.string "A stadium with no crowd, and a guardian\n"
	.string "that keeps coming back to fight in it.\l"
	.string "The professor knows the feeling.\p"
	.string "The spark that followed you home is\n"
	.string "tiny, and already curious about me. I\l"
	.string "am not sure I like that.$"

Nexus_Text_TapuLele_Arrival:
	.string "Glittering scales fell like snow over\n"
	.string "a garden.\p"
	.string "Every flower had bloomed too far. The\n"
	.string "Pokémon lying among them were\l"
	.string "sleeping far too deeply.$"

Nexus_Text_TapuLele_Boss:
	.string "Something small and bright came\n"
	.string "through the petals, humming.\p"
	.string "It shook a shower of scales over you,\n"
	.string "as if it were a gift.$"

Nexus_Text_TapuLele_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-786. Guardian of Akala.\p"
	.string "A kindness with no end to it, and a\n"
	.string "young lady who has learned where\l"
	.string "kindness should stop.\p"
	.string "What remains of it is small, and it\n"
	.string "hums. Keep it close. Not too close.$"

Nexus_Text_TapuBulu_Arrival:
	.string "A walled town, and a forest eating it.\p"
	.string "Trees lay across the streets, torn out\n"
	.string "roots and all. New ones pushed up\l"
	.string "through the pavement as you watched.$"

Nexus_Text_TapuBulu_Boss:
	.string "A bell rang once, somewhere in the\n"
	.string "green.\p"
	.string "Something with horns came out of the\n"
	.string "trees, dragging a whole trunk behind\l"
	.string "it as if it weighed nothing.$"

Nexus_Text_TapuBulu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-787. Guardian of Ula'ula.\p"
	.string "A town that locked its gates, and a\n"
	.string "guardian that grew a forest over them.\p"
	.string "The young man who once stood guard at\n"
	.string "such gates says it was right to.\p"
	.string "What you brought back fits in two\n"
	.string "hands, and it is already asleep. I find\l"
	.string "that very reassuring.$"

Nexus_Text_TapuFini_Arrival:
	.string "An island wrapped in a mist so thick\n"
	.string "you could not see your own feet.\p"
	.string "It smelled of salt and of something\n"
	.string "clean, like a wound after it has been\l"
	.string "washed.$"

Nexus_Text_TapuFini_Boss:
	.string "The mist parted like a curtain.\p"
	.string "A shell of stone hung above the water,\n"
	.string "and the fog was pouring out of it.$"

Nexus_Text_TapuFini_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-788. The Mist Warden.\p"
	.string "A mist that heals the calm and drowns\n"
	.string "the angry, and a dancer who never once\l"
	.string "raised his voice inside it.\p"
	.string "What came back with you is small, and\n"
	.string "damp, and very calm. He says the water\l"
	.string "only returns what you bring to it.$"

Nexus_Text_Urshifu_Arrival:
	.string "Two stone towers stood in a lake. One\n"
	.string "was dark inside. The other had a\l"
	.string "waterfall pouring through every floor.\p"
	.string "From both came the same sound: a fist\n"
	.string "hitting a target, over and over, for\l"
	.string "years.$"

Nexus_Text_Urshifu_Boss:
	.string "The sound stopped.\p"
	.string "It came down the stairs of both towers\n"
	.string "at once, somehow, and bowed before it\l"
	.string "raised its fists.$"

Nexus_Text_Urshifu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-892. Wushu.\p"
	.string "Two towers of practice with no top, and\n"
	.string "a man who trains under waterfalls\l"
	.string "finally finding a harder one.\p"
	.string "What came back with you is small and\n"
	.string "round, and it has never trained a day.\l"
	.string "It will.\p"
	.string "He wants to come back tomorrow. I told\n"
	.string "him it may not be here. He said then\l"
	.string "he will train until it is.$"

Nexus_Text_Enamorus_Arrival:
	.string "Winter, and then, in a single line\n"
	.string "across the field, spring.\p"
	.string "Flowers opened behind a warm wind. On\n"
	.string "the other side of the line, the snow\l"
	.string "had not moved at all.$"

Nexus_Text_Enamorus_Boss:
	.string "The warm wind stopped and turned\n"
	.string "around.\p"
	.string "Something rode down on it from the\n"
	.string "clouds, smiling, and the flowers\l"
	.string "nearest you began to wilt.$"

Nexus_Text_Enamorus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-905. Love-Hate.\p"
	.string "A spring that arrives for everyone,\n"
	.string "and a punishment for anyone who\l"
	.string "forgets to be kind.\p"
	.string "The lady from the Aether Foundation\n"
	.string "read this twice, and asked me to leave\l"
	.string "it as it is.\p"
	.string "What stayed with you is small and\n"
	.string "warm, and has not decided what it\l"
	.string "thinks of you yet.$"

Nexus_Text_ChienPao_Arrival:
	.string "A shrine buried in snow.\p"
	.string "A great stake had been driven into the\n"
	.string "ground here once, and it had split in\l"
	.string "two.\p"
	.string "Around it, everything was cracked. The\n"
	.string "stone, the ice. Even the air felt thin,\l"
	.string "like glass.$"

Nexus_Text_ChienPao_Boss:
	.string "The cracks in the ice ran toward you.\p"
	.string "Something with blades of ice for fangs\n"
	.string "stepped out of them, and your guard\l"
	.string "suddenly felt like paper.$"

Nexus_Text_ChienPao_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1002. The Ruinous Sword.\p"
	.string "A shrine where every defense cracks,\n"
	.string "and a woman who has spent her life\l"
	.string "making herself hard and cold.\p"
	.string "What came back with you is small, and\n"
	.string "nothing cracks around it yet. She\l"
	.string "walked out thawed. I do not know which\l"
	.string "of them won.$"

Nexus_Text_ChiYu_Arrival:
	.string "A lake of lava, glowing red under a\n"
	.string "black sky.\p"
	.string "Old jade beads lay scorched along the\n"
	.string "shore. Standing near them made\l"
	.string "everything feel weaker, as if the air\l"
	.string "had been thinned.$"

Nexus_Text_ChiYu_Boss:
	.string "Something small swam up through the\n"
	.string "molten rock, like a goldfish rising in a\l"
	.string "pond.\p"
	.string "Around it, the beads on the shore\n"
	.string "began to burn again.$"

Nexus_Text_ChiYu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1004. The Ruinous.\p"
	.string "A lake of fire made from melted stone,\n"
	.string "and a young woman who burns hottest\l"
	.string "when she fears she is not enough.\p"
	.string "What came back with you swims in\n"
	.string "circles in the palm of a hand, warm as a\l"
	.string "coal. It is not ruinous yet. I intend to\l"
	.string "write that down every day.$"

Nexus_Text_Fezandipiti_Arrival:
	.string "A plaza full of flowers and ribbons,\n"
	.string "all laid at the feet of one statue.\p"
	.string "A bird carved in stone, wings open,\n"
	.string "with a chain of glass beads around its\l"
	.string "neck. The beads were dripping.$"

Nexus_Text_Fezandipiti_Boss:
	.string "A sweet smell drifted down. You felt\n"
	.string "a sudden, strong wish to admire\l"
	.string "whatever came next.\p"
	.string "It landed on the statue's head and\n"
	.string "spread its wings for you.$"

Nexus_Text_Fezandipiti_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1016. Retainer.\p"
	.string "A hero with a statue in the square,\n"
	.string "and a poison under the feathers that\l"
	.string "no one wanted to see.\p"
	.string "The lady who fought there knows about\n"
	.string "statues. She says she never wants\l"
	.string "another one.\p"
	.string "What you brought back is small and\n"
	.string "plain, and nobody will build it a\l"
	.string "statue. It seems relieved.$"

Nexus_Text_Arceus_Arrival:
	.string "Nothing. Not dark, not light. Just a\n"
	.string "floor that went on forever, under a sky\l"
	.string "that had not been decided yet.\p"
	.string "Tablets of colored stone hung in the\n"
	.string "air around you. Each one hummed a\l"
	.string "different note.$"

Nexus_Text_Arceus_Boss:
	.string "The tablets turned, all at once, toward\n"
	.string "the same empty point.\p"
	.string "Something stepped out of the place\n"
	.string "where nothing had been, and the floor\l"
	.string "under its feet became real.$"

Nexus_Text_Arceus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-493. Alpha.\p"
	.string "A world before the world, and a young\n"
	.string "man who says almost nothing, standing\l"
	.string "at the edge of it.\p"
	.string "What came back with you is very small\n"
	.string "and very new. It has made nothing yet.\l"
	.string "Give it time.\p"
	.string "He spoke today. I have the words. I am\n"
	.string "keeping them to myself.$"

Nexus_Text_Mew_Arrival:
	.string "A rainforest, warm and loud.\p"
	.string "The mud was full of tracks, each one\n"
	.string "from a different kind of Pokémon, and\l"
	.string "every trail narrowed down into one\l"
	.string "small set of footprints.$"

Nexus_Text_Mew_Boss:
	.string "The small footprints ended in the\n"
	.string "middle of a clearing.\p"
	.string "Something giggled above you. When you\n"
	.string "looked up there was nothing there.\l"
	.string "Then there was.$"

Nexus_Text_Mew_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-151. New Species.\p"
	.string "A forest where every path leads back\n"
	.string "to the same small beginning, and a\l"
	.string "young woman who answers to a name\l"
	.string "that is not quite hers.\p"
	.string "What came back with you is small\n"
	.string "enough to hold. It already looks like it\l"
	.string "might become anything.\p"
	.string "She was not bothered about the name.\n"
	.string "She says names are like tracks: you\l"
	.string "leave them, and you keep walking.$"

Nexus_Text_Celebi_Arrival:
	.string "A forest where every tree was a\n"
	.string "different age.\p"
	.string "A seedling stood beside a dead trunk. A\n"
	.string "tree in full blossom stood beside a\l"
	.string "shadow on the ground where a tree had\l"
	.string "not grown yet.\p"
	.string "The air smelled like rain from a long\n"
	.string "time ago.$"

Nexus_Text_Celebi_Boss:
	.string "A small green light moved between the\n"
	.string "trees, and wherever it passed, the\l"
	.string "ages shifted.\p"
	.string "The dead trunk put out a leaf. The\n"
	.string "seedling grew old and bowed.$"

Nexus_Text_Celebi_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-251. Forest Time.\p"
	.string "A forest of every age at once, and an\n"
	.string "old man who was glad to be only one of\l"
	.string "them.\p"
	.string "What came back with you is very small\n"
	.string "and very green. It keeps looking at me\l"
	.string "as if it knows how I will look when I am\l"
	.string "old. I have asked it not to tell me.$"

Nexus_Text_Jirachi_Arrival:
	.string "A hill, and above it a comet that did not\n"
	.string "move.\p"
	.string "Paper tags were tied to every blade of\n"
	.string "grass, thousands of them, and each one\l"
	.string "had a wish written on it.$"

Nexus_Text_Jirachi_Boss:
	.string "The comet flared. One tag tore loose\n"
	.string "and flew up toward something small and\l"
	.string "sleeping.\p"
	.string "It woke, and the eye on its belly opened\n"
	.string "last.$"

Nexus_Text_Jirachi_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-385. Wish.\p"
	.string "A hill full of other people's wishes, and\n"
	.string "a young man who wished for the smallest\l"
	.string "thing on it.\p"
	.string "What came back with you is asleep. It\n"
	.string "will likely stay asleep a long time. That\l"
	.string "is how it keeps its promises.$"

Nexus_Text_Manaphy_Arrival:
	.string "A seafloor, cold and very deep, lit by\n"
	.string "small floating eggs.\p"
	.string "Each egg drifted off on a different\n"
	.string "current. Each one, slowly, found its\l"
	.string "way back.$"

Nexus_Text_Manaphy_Boss:
	.string "One egg did not drift away. It hatched.\p"
	.string "Something small and blue floated up to\n"
	.string "meet you, curious, as if it had been\l"
	.string "expecting you all along.$"

Nexus_Text_Manaphy_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-490. Seafaring.\p"
	.string "A seafloor where everything that\n"
	.string "leaves comes home, and a Gym Leader\l"
	.string "who keeps saying she will leave.\p"
	.string "What came back with you is paler, and\n"
	.string "smaller, and not a prince of anything\l"
	.string "yet. It keeps swimming toward the door.\p"
	.string "She wanted it written that she always\n"
	.string "goes back to her city. I did not ask. I\l"
	.string "have written it.$"

Nexus_Text_Darkrai_Arrival:
	.string "A harbor town on a night with no moon.\p"
	.string "Every lamp was out. People stood in the\n"
	.string "streets with their eyes closed, asleep\l"
	.string "on their feet, and some of them were\l"
	.string "crying.$"

Nexus_Text_Darkrai_Boss:
	.string "One of the shadows on the pier did not\n"
	.string "belong to anyone.\p"
	.string "It stood up, and all around you the\n"
	.string "sleepers began to whisper.$"

Nexus_Text_Darkrai_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-491. Pitch-Black.\p"
	.string "A town asleep inside its worst dreams,\n"
	.string "and a woman who is not afraid of the\l"
	.string "dark, because she has always lived next\l"
	.string "to it.\p"
	.string "What came back with you sleeps like a\n"
	.string "child. I checked. It is not dreaming of\l"
	.string "anything bad.$"

Nexus_Text_Shaymin_Arrival:
	.string "A field of grey ash under a grey sky.\n"
	.string "Nothing grew, and the air tasted of\l"
	.string "smoke.\p"
	.string "But a thin line of fresh flowers ran\n"
	.string "across it, bright as footprints.$"

Nexus_Text_Shaymin_Boss:
	.string "The flowers at your feet shivered.\p"
	.string "Something small rose out of the grass,\n"
	.string "and the grey air around it was already\l"
	.string "turning clear.$"

Nexus_Text_Shaymin_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-492. Gratitude.\p"
	.string "A dead field, and a small thing walking\n"
	.string "across it, leaving flowers behind.\p"
	.string "The woman who sells perfume in Celadon\n"
	.string "asked me who it was thanking. I had no\l"
	.string "answer.\p"
	.string "What came back with you is very small,\n"
	.string "and asleep inside a blossom. She says\l"
	.string "that is how they begin.$"

Nexus_Text_Victini_Arrival:
	.string "A small island, and a lighthouse with\n"
	.string "its lamp dark.\p"
	.string "Every step you took felt lighter than\n"
	.string "the one before, as if the ground itself\l"
	.string "wanted you to win.$"

Nexus_Text_Victini_Boss:
	.string "The lighthouse lamp came on by itself.\p"
	.string "Something small sat in the light,\n"
	.string "holding up two fingers in a V. It was\l"
	.string "warm enough to feel from the shore.$"

Nexus_Text_Victini_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-494. Victory.\p"
	.string "An island that hands out wins, and a\n"
	.string "young man who would hate to be handed\l"
	.string "one.\p"
	.string "What came back with you is small, and\n"
	.string "warm, and sleeps a great deal. It has\l"
	.string "not decided who to let win yet.\p"
	.string "I asked him if he wanted it. He said he\n"
	.string "wants to earn the next one. Then he\l"
	.string "said, 'Smell ya later.'$"

Nexus_Text_Meloetta_Arrival:
	.string "A theater with every seat taken. Not by\n"
	.string "people: by costumes, sitting upright,\l"
	.string "hats on, waiting.\p"
	.string "A song was coming from the stage. There\n"
	.string "was nobody on it.$"

Nexus_Text_Meloetta_Boss:
	.string "The song changed key in the middle of a\n"
	.string "note.\p"
	.string "The singer on the stage was a dancer\n"
	.string "now, spinning, and it had been both all\l"
	.string "along.$"

Nexus_Text_Meloetta_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-648. Melody.\p"
	.string "A theater of empty costumes, and a man\n"
	.string "who owns more faces than any of them.\p"
	.string "What came home with you hums a tune I\n"
	.string "cannot place, very quietly. It changes\l"
	.string "every time I listen. It is still finding\l"
	.string "its own voice.$"

Nexus_Text_Diancie_Arrival:
	.string "A cave where the walls were slowly\n"
	.string "turning into diamond.\p"
	.string "Black coal at the edges, clear\n"
	.string "glittering stone at the heart, and a\l"
	.string "pressure in the air you could feel in\l"
	.string "your teeth.$"

Nexus_Text_Diancie_Boss:
	.string "Pink light spilled out of the deepest\n"
	.string "wall.\p"
	.string "Something small and crowned stepped\n"
	.string "from the stone, and the diamonds\l"
	.string "around it began to grow.$"

Nexus_Text_Diancie_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-719. The Jewel Princess.\p"
	.string "A cave where coal is squeezed into\n"
	.string "diamonds, and a Champion who believes\l"
	.string "beauty is only pressure, patiently\l"
	.string "endured.\p"
	.string "What came back with you is small and\n"
	.string "still rough at the edges. He polished\l"
	.string "my magnifying glass before he left. It\l"
	.string "has never been so clean.$"

Nexus_Text_Hoopa_Arrival:
	.string "A tournament stage in the middle of\n"
	.string "nowhere. A bracket on the wall,\l"
	.string "spotlights, a ring.\p"
	.string "The stands were packed with people\n"
	.string "who had stepped out of golden hoops,\l"
	.string "and were still looking around.\p"
	.string "None of them were clapping.$"

Nexus_Text_Hoopa_Boss:
	.string "A golden ring opened above the stage,\n"
	.string "and a laugh came out of it before\l"
	.string "anything else did.\p"
	.string "Then more rings, and more, until the\n"
	.string "whole stage was a mouth full of doors.$"

Nexus_Text_Hoopa_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-720. Rings.\p"
	.string "A crowd pulled in from everywhere, and\n"
	.string "a star who noticed they were not his.\p"
	.string "What came back with you is tiny and\n"
	.string "laughs at everything. The rings are\l"
	.string "gone. I checked my pockets, just in\l"
	.string "case.$"

Nexus_Text_Magearna_Arrival:
	.string "A workshop, dusty and warm. Every\n"
	.string "clock on the walls had stopped at the\l"
	.string "same minute.\p"
	.string "On the benches lay tools no one alive\n"
	.string "knew how to use, and every one of them\l"
	.string "was still humming, as if someone had\l"
	.string "just stepped out.$"

Nexus_Text_Magearna_Boss:
	.string "Somewhere in the dust, a gear turned\n"
	.string "over once, stiffly.\p"
	.string "A small figure of pink and steel stood\n"
	.string "up, curtsied, and opened its chest.\l"
	.string "Inside, something that was not quite a\l"
	.string "heart began to glow.$"

Nexus_Text_Magearna_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-801. The Artificial.\p"
	.string "A workshop where every clock stopped\n"
	.string "five hundred years ago, and an old\l"
	.string "inventor who still laughs at his own\l"
	.string "sparks.\p"
	.string "What came back with you is a brand-new\n"
	.string "body, and the heart inside it is very\l"
	.string "old. Be kind to it. It remembers its\l"
	.string "maker.$"

Nexus_Text_Marshadow_Arrival:
	.string "A city at dusk, empty and quiet.\p"
	.string "Every shadow fell the wrong way: toward\n"
	.string "the lamps, not away from them.\p"
	.string "On one wall was the shadow of a man in a\n"
	.string "long coat. Nobody was standing there\l"
	.string "to cast it.$"

Nexus_Text_Marshadow_Boss:
	.string "Your own shadow stretched, then peeled\n"
	.string "up off the ground.\p"
	.string "It stood, small and gray, and moved the\n"
	.string "way you were about to move.$"

Nexus_Text_Marshadow_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-802. Gloomdweller.\p"
	.string "A city of misplaced shadows, and a man\n"
	.string "who has stood in someone else's for\l"
	.string "three years.\p"
	.string "The fragment that followed you home\n"
	.string "hides behind your heel. It has not\l"
	.string "chosen whose shadow it wants yet.$"

Nexus_Text_Zeraora_Arrival:
	.string "A city at night where every light was\n"
	.string "on.\p"
	.string "Down each street the lamps flickered\n"
	.string "in order, one after another, as if\l"
	.string "something was running through the\l"
	.string "wires faster than the power could.$"

Nexus_Text_Zeraora_Boss:
	.string "Every light in the city went out at\n"
	.string "once.\p"
	.string "In the dark, something crackled, very\n"
	.string "close. Claws of lightning, a grin -- and\l"
	.string "then it was already somewhere else.$"

Nexus_Text_Zeraora_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-807. Thunderclap.\p"
	.string "A city whose lights could not keep up\n"
	.string "with something, and an old man who\l"
	.string "built a city of wires and laughs when\l"
	.string "they spark.\p"
	.string "What came back with you fits in the\n"
	.string "palm of a hand, and it will not stay\l"
	.string "still long enough to be counted. I\l"
	.string "counted it anyway.$"

Nexus_Text_Melmetal_Arrival:
	.string "An ancient forge, deep underground.\n"
	.string "Molten iron ran through channels in\l"
	.string "the floor like water in a garden.\p"
	.string "Thousands of little hex nuts were\n"
	.string "rolling across the stone. All of them\l"
	.string "toward the same place.$"

Nexus_Text_Melmetal_Boss:
	.string "The hex nuts stopped rolling.\p"
	.string "They had built something out of\n"
	.string "themselves, and it looked at you with\l"
	.string "a single bright eye.$"

Nexus_Text_Melmetal_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-809. Hex Nut.\p"
	.string "A forge where iron comes from nothing,\n"
	.string "and a young woman who loves steel\l"
	.string "because it lasts.\p"
	.string "What you carried out of the forge was\n"
	.string "small, and it fit in your hand.\p"
	.string "I told her this one falls apart in the\n"
	.string "end and comes back small. She said\l"
	.string "that counts as lasting.$"

Nexus_Text_Zarude_Arrival:
	.string "A jungle so thick the daylight came\n"
	.string "through green.\p"
	.string "Vines hung everywhere, and some of\n"
	.string "them moved on their own, reaching\l"
	.string "toward you and pulling back, as if they\l"
	.string "had been told not to.$"

Nexus_Text_Zarude_Boss:
	.string "The vines parted.\p"
	.string "Something stood there with its arms\n"
	.string "crossed, watching you the way a parent\l"
	.string "watches a stranger near a child.$"

Nexus_Text_Zarude_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-893. The Rogue.\p"
	.string "A jungle that does not trust\n"
	.string "outsiders, and a Gym Leader who once\l"
	.string "lent his own Pokémon to a stranger's\l"
	.string "child.\p"
	.string "What came back with you grabbed my\n"
	.string "sleeve and would not let go. I have\l"
	.string "decided to count that as a good sign.$"

Nexus_Text_GreatTusk_Arrival:
	.string "An arena of packed earth, with no\n"
	.string "seats around it.\p"
	.string "Huge tusks had been driven into the\n"
	.string "ground all around it, like the posts of\l"
	.string "a fence.\p"
	.string "Every tusk was cracked from a hit.\n"
	.string "None of them had been pulled out.$"

Nexus_Text_GreatTusk_Boss:
	.string "The earth shook in a rhythm, like\n"
	.string "footsteps, or a drum.\p"
	.string "Something shaggy and enormous lowered\n"
	.string "its head at the edge of the arena and\l"
	.string "started to roll.$"

Nexus_Text_GreatTusk_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-984. Ancient Tusk.\p"
	.string "An arena with no seats, and a judge who\n"
	.string "finally had something to judge.\p"
	.string "What came back with you is smaller than\n"
	.string "its tusks should be. It headbutted my\l"
	.string "chair. Twice. The chair lost.$"

Nexus_Text_ScreamTail_Arrival:
	.string "A meadow of flowers as tall as trees,\n"
	.string "under a moon that was far too big.\p"
	.string "It was quiet. Too quiet. Every sound\n"
	.string "you made came back softer, as if\l"
	.string "someone had turned it down.$"

Nexus_Text_ScreamTail_Boss:
	.string "Then the song started.\p"
	.string "It was a lullaby, until it wasn't. It\n"
	.string "became a scream, and the flowers\l"
	.string "closed all at once.$"

Nexus_Text_ScreamTail_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-985. Old Lullaby.\p"
	.string "A meadow that forgot how to be quiet,\n"
	.string "and a Gym Leader who sang back at it\l"
	.string "until it stopped.\p"
	.string "What you brought back is asleep. Let it\n"
	.string "stay that way a little longer.\p"
	.string "I did not know she could sing. I have\n"
	.string "not told her I was listening.$"

Nexus_Text_BruteBonnet_Arrival:
	.string "An ancient jungle, dark and wet.\p"
	.string "The mushrooms here were taller than\n"
	.string "the trees, and the air glittered with\l"
	.string "spores.\p"
	.string "Just breathing it made your eyes\n"
	.string "heavy.$"

Nexus_Text_BruteBonnet_Boss:
	.string "One of the mushrooms had teeth.\p"
	.string "It had been standing still for a very\n"
	.string "long time, waiting for something to fall\l"
	.string "asleep near it.$"

Nexus_Text_BruteBonnet_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-986. The Patient Jaw.\p"
	.string "A jungle that eats whatever sleeps,\n"
	.string "and a man who stayed wide awake in it\l"
	.string "out of pure stubbornness.\p"
	.string "What you carried out is small, and it\n"
	.string "naps constantly. He says that is fine.\l"
	.string "It is only a baby.$"

Nexus_Text_FlutterMane_Arrival:
	.string "A cave with no bottom.\p"
	.string "Rust-colored plumes drifted in the air,\n"
	.string "though there was no wind.\p"
	.string "Somewhere below, someone was laughing.\n"
	.string "It sounded like a child who had been\l"
	.string "hiding for a very long time.$"

Nexus_Text_FlutterMane_Boss:
	.string "The laughing stopped, right behind you.\p"
	.string "A mane of feathers unfolded in the\n"
	.string "dark, and every one of them was looking\l"
	.string "at you.$"

Nexus_Text_FlutterMane_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-987. The Laugh in the Dark.\p"
	.string "A cave full of very old laughter, and a\n"
	.string "girl from the mountain of graves who\l"
	.string "laughed right back.\p"
	.string "What came home with you is small, and it\n"
	.string "giggles when I turn off the light. She\l"
	.string "says ghosts are only lonely. I have\l"
	.string "decided to believe her.$"

Nexus_Text_SlitherWing_Arrival:
	.string "Ferns taller than houses, and air so\n"
	.string "hot and wet it felt like breathing\l"
	.string "soup.\p"
	.string "The mud was full of tracks. Heavy\n"
	.string "feet, and between them, the long drag\l"
	.string "of wings too big to lift.$"

Nexus_Text_SlitherWing_Boss:
	.string "The ferns parted.\p"
	.string "It walked out on its legs, wings\n"
	.string "folded like a cloak, and the scales\l"
	.string "falling off it were on fire.$"

Nexus_Text_SlitherWing_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-988. Grounded Sun.\p"
	.string "A forest from before any book, and a\n"
	.string "boy with a notebook who filled every\l"
	.string "page of it.\p"
	.string "What came back with you is a single\n"
	.string "warm scale. It has not cooled yet.\p"
	.string "He asked me to keep one sketch out of\n"
	.string "the file. It is of the footprints.$"

Nexus_Text_SandyShocks_Arrival:
	.string "A desert under a heavy sky. The sand\n"
	.string "moved in lines, pulled into patterns\l"
	.string "like iron filings around a magnet.\p"
	.string "Round, old shapes stuck half out of\n"
	.string "the dunes, humming.$"

Nexus_Text_SandyShocks_Boss:
	.string "The dunes pulled together into a\n"
	.string "shaggy mane of sand.\p"
	.string "Underneath it, something old and\n"
	.string "magnetic lifted its head, and your Poké\l"
	.string "Balls tugged at your belt.$"

Nexus_Text_SandyShocks_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-989. Paradox.\p"
	.string "Something ancient buried under sand\n"
	.string "and still live, and a soldier who knows\l"
	.string "exactly what that means.\p"
	.string "What came back with you is small and\n"
	.string "has almost no mane yet. My paper clips\l"
	.string "follow it around the room.\p"
	.string "He walked the desert in straight lines\n"
	.string "before he would let you cross it. Old\l"
	.string "habit, he said.$"

Nexus_Text_IronTreads_Arrival:
	.string "A dusty plain, crossed by tracks.\p"
	.string "They were too straight for any animal,\n"
	.string "all of them parallel, all of them\l"
	.string "vanishing at the horizon.\p"
	.string "Beside each one lay a broken steel\n"
	.string "tusk.$"

Nexus_Text_IronTreads_Boss:
	.string "A wheel of steel came rolling out of\n"
	.string "the dust.\p"
	.string "It stopped, unrolled, and raised two\n"
	.string "tusks that crackled at the tips.$"

Nexus_Text_IronTreads_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-990. Future Tusk.\p"
	.string "A plain of perfect tracks, and a man\n"
	.string "who knows every Donphan ever rented.\p"
	.string "What came back with you is new, and it\n"
	.string "rolls in circles on my floor. It has not\l"
	.string "yet learned to go straight. I find that\l"
	.string "reassuring.$"

Nexus_Text_IronBundle_Arrival:
	.string "A polar station from some far-off\n"
	.string "future, empty.\p"
	.string "Snow was falling indoors, down long\n"
	.string "white metal hallways.\p"
	.string "Somewhere an alarm had been ringing\n"
	.string "for centuries, and no one had come to\l"
	.string "turn it off.$"

Nexus_Text_IronBundle_Boss:
	.string "The alarm stopped.\p"
	.string "Something small and white came skating\n"
	.string "down the hall, far too fast, carrying a\l"
	.string "sack made of ice.$"

Nexus_Text_IronBundle_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-991. The Last Courier.\p"
	.string "A station everyone left, and a woman\n"
	.string "who crossed the world looking for a\l"
	.string "place cold enough, and was not glad\l"
	.string "when she found it.\p"
	.string "What followed you home is small, and it\n"
	.string "keeps trying to hand me things. She\l"
	.string "says even ice wants somebody to\l"
	.string "deliver to.$"

Nexus_Text_IronHands_Arrival:
	.string "A training hall, huge and empty, lit only\n"
	.string "by sparks.\p"
	.string "Steel pillars stood in rows, each\n"
	.string "dented by the same enormous palm, over\l"
	.string "and over, deeper every time.$"

Nexus_Text_IronHands_Boss:
	.string "Something clanked to its feet between\n"
	.string "the pillars.\p"
	.string "It was built like a wrestler, and its\n"
	.string "hands were bigger than you. It bowed,\l"
	.string "the way a sumo does, before it charged.$"

Nexus_Text_IronHands_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-992. The Future Heavyweight.\p"
	.string "A training hall in a time that has not\n"
	.string "happened, and a Gym Leader who met\l"
	.string "what his partner might someday become.\p"
	.string "What came back with you is small and\n"
	.string "cold, and it keeps clapping its hands\l"
	.string "together to hear the sound. I have not\l"
	.string "told the young man. I think he would\l"
	.string "cry.$"

Nexus_Text_IronJugulis_Arrival:
	.string "A night sky with no stars in it, crossed\n"
	.string "by three lights flying together.\p"
	.string "The two outer lights turned at the\n"
	.string "same moment. The middle one followed\l"
	.string "without looking.\p"
	.string "Below them stood three metal doors, in\n"
	.string "nothing at all.$"

Nexus_Text_IronJugulis_Boss:
	.string "One of the doors swung open on its own.\p"
	.string "Behind it there was only sky, and three\n"
	.string "lights coming straight at you.$"

Nexus_Text_IronJugulis_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-993. Blind Sky.\p"
	.string "Three doors and three lights, and a\n"
	.string "woman who has always chosen doors\l"
	.string "without looking.\p"
	.string "What came back with you bumps into\n"
	.string "things. Gently. It trusts the room to\l"
	.string "be there. I have moved the lamp.$"

Nexus_Text_IronMoth_Arrival:
	.string "A greenhouse of glass and steel, lit\n"
	.string "by a sun hanging from the ceiling on\l"
	.string "chains.\p"
	.string "Every plant was perfect, and every\n"
	.string "one was plastic. Nothing buzzed but\l"
	.string "the lights.$"

Nexus_Text_IronMoth_Boss:
	.string "The hanging sun moved.\p"
	.string "It unfolded wings of bright metal\n"
	.string "blades and rose, and the air under it\l"
	.string "began to taste of poison.$"

Nexus_Text_IronMoth_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-994. Iron Sun.\p"
	.string "A garden with nothing alive in it, and\n"
	.string "a researcher who kept checking the\l"
	.string "leaves for eggs.\p"
	.string "What you brought out still hums. He\n"
	.string "listened to it for a long time.\p"
	.string "He found no eggs. He says that is the\n"
	.string "most important thing he has ever\l"
	.string "written down.$"

Nexus_Text_IronThorns_Arrival:
	.string "A dig site. Ropes, grids, little flags in\n"
	.string "the dirt, everything a careful person\l"
	.string "would set up.\p"
	.string "The bones in the ground were made of\n"
	.string "metal. Some of them were still warm.$"

Nexus_Text_IronThorns_Boss:
	.string "A spine of rock plates slid up out of\n"
	.string "the dig, humming.\p"
	.string "It stood, and a crackle ran along its\n"
	.string "back, as if someone far in the future\l"
	.string "had just switched it on.$"

Nexus_Text_IronThorns_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-995. Paradox.\p"
	.string "A fossil that has not died yet, and a\n"
	.string "man who has spent his life reading the\l"
	.string "ones that have.\p"
	.string "What came back with you is small, and\n"
	.string "cool to the touch, and it hums when it\l"
	.string "sleeps. Nothing has been built on it\l"
	.string "yet.\p"
	.string "He took notes the whole time. I asked\n"
	.string "to see them. Every page ends with the\l"
	.string "same two words: 'Not yet.'$"

Nexus_Text_RoaringMoon_Arrival:
	.string "A canyon from a time before people.\p"
	.string "The moon hung huge and red over the\n"
	.string "rim, close enough to count its craters.\l"
	.string "Deep claw marks ran down both walls, all\l"
	.string "the way to the bottom.$"

Nexus_Text_RoaringMoon_Boss:
	.string "Wings like torn banners blotted out the\n"
	.string "red moon.\p"
	.string "It landed without a sound, and the claw\n"
	.string "marks on the walls suddenly made sense.$"

Nexus_Text_RoaringMoon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1005. Red Moon.\p"
	.string "A canyon under a moon too large, and a\n"
	.string "man who wants to be the scariest thing\l"
	.string "in the room.\p"
	.string "The fragment that came back with you\n"
	.string "is all claws and no wings. It has not\l"
	.string "learned to frighten anyone. Nobody\l"
	.string "needs to teach it.$"

Nexus_Text_IronValiant_Arrival:
	.string "A garden of metal flowers, perfectly\n"
	.string "still, under a light with no sun behind\l"
	.string "it.\p"
	.string "Nothing here grew. Nothing here wilted.\n"
	.string "Everything had been finished a long\l"
	.string "time ago.$"

Nexus_Text_IronValiant_Boss:
	.string "Something walked through the flowers\n"
	.string "without bending a single one.\p"
	.string "It had a blade on each arm and a gown of\n"
	.string "steel, and it did not breathe.$"

Nexus_Text_IronValiant_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1006. Paradox.\p"
	.string "A garden where nothing ever tires, and a\n"
	.string "boy who knows exactly what being tired\l"
	.string "is worth.\p"
	.string "What came back with you is small and\n"
	.string "warm, and it yawned. Machines do not\l"
	.string "yawn. I have written that down twice.$"

Nexus_Text_WalkingWake_Arrival:
	.string "Warm rain over a lake older than any\n"
	.string "map.\p"
	.string "Ferns as tall as houses leaned over\n"
	.string "the water. In the mud, huge footprints\l"
	.string "were still filling up.$"

Nexus_Text_WalkingWake_Boss:
	.string "The lake rose all at once, like a wave\n"
	.string "that had waited a very long time.\p"
	.string "Something with a mane of water came\n"
	.string "out of it, running.$"

Nexus_Text_WalkingWake_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1009. The Ancient Wake.\p"
	.string "A lake from before anyone, and a man\n"
	.string "who taught water to dance showing off\l"
	.string "for a thing that already knew how.\p"
	.string "What you brought back is small, and it\n"
	.string "splashes whenever it walks. He bowed\l"
	.string "to it. I believe it bowed back.$"

Nexus_Text_IronLeaves_Arrival:
	.string "A forest, but the leaves were steel.\p"
	.string "When the wind moved, the branches rang\n"
	.string "against each other like blades. Not one\l"
	.string "leaf had ever fallen.$"

Nexus_Text_IronLeaves_Boss:
	.string "The ringing stopped all at once.\p"
	.string "Something stepped out of the trees\n"
	.string "with its head lowered like a knight's,\l"
	.string "and the long green edges on its brow\l"
	.string "began to glow.$"

Nexus_Text_IronLeaves_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1010. Paradox.\p"
	.string "A forest that has forgotten how to be\n"
	.string "autumn, and a young woman named for\l"
	.string "the thing it cannot do.\p"
	.string "What came back with you is the size of\n"
	.string "a seedling. Its edges are still soft. I\l"
	.string "do not know what time it belongs to\l"
	.string "now.\p"
	.string "I asked her what her name had to do\n"
	.string "with it. She said, 'Nothing,' and smiled.\l"
	.string "I have written that down too.$"

Nexus_Text_GougingFire_Arrival:
	.string "A valley from before anyone drew maps.\p"
	.string "Ferns taller than houses. Steam rising\n"
	.string "from cracks in the ground. And stone\l"
	.string "pillars, dozens of them, all broken off\l"
	.string "at the same height.$"

Nexus_Text_GougingFire_Boss:
	.string "The ground was warm, then hot.\p"
	.string "Horns came through the steam first, low\n"
	.string "and burning, aimed at the last pillar\l"
	.string "still standing. Then at you.$"

Nexus_Text_GougingFire_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1020. Ancient Blaze.\p"
	.string "A valley that never was, and a dragon\n"
	.string "master who could not find its family\l"
	.string "line in any book.\p"
	.string "The fragment you brought home is warm\n"
	.string "to the touch and has no past at all. It\l"
	.string "will have to start one with you.$"

Nexus_Text_RagingBolt_Arrival:
	.string "A plain of burned stone under a storm\n"
	.string "that never ended.\p"
	.string "The lightning kept striking the same\n"
	.string "spot, over and over, as if something\l"
	.string "there kept calling it down.$"

Nexus_Text_RagingBolt_Boss:
	.string "The spot where the lightning struck\n"
	.string "stood up.\p"
	.string "It had a neck like a mountain ridge, and\n"
	.string "a thundercloud sat on its back like a\l"
	.string "saddle.$"

Nexus_Text_RagingBolt_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1021. The Storm Rider.\p"
	.string "An endless storm, and an old sailor who\n"
	.string "said he had weathered worse.\p"
	.string "What you brought back is small, and its\n"
	.string "hair stands on end. He has not\l"
	.string "weathered worse. He simply refuses to\l"
	.string "admit it.$"

Nexus_Text_IronBoulder_Arrival:
	.string "A field of boulders, every one of them\n"
	.string "cut cleanly in half.\p"
	.string "The two halves of each stone lay\n"
	.string "facing each other, their cut sides as\l"
	.string "smooth and bright as mirrors.$"

Nexus_Text_IronBoulder_Boss:
	.string "One more boulder split, with a sound\n"
	.string "like a bell.\p"
	.string "Between the halves stood something\n"
	.string "shaped like a great horned beast, built\l"
	.string "of stone and metal. Its horn hummed\l"
	.string "like a blade.$"

Nexus_Text_IronBoulder_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1022. The Blade Stone.\p"
	.string "A field where every stone was split\n"
	.string "into a pair, and twins who have spent\l"
	.string "their whole lives being called two\l"
	.string "halves of one thing.\p"
	.string "What came back with you is one piece,\n"
	.string "whole, and cold to the touch. I thought\l"
	.string "the twins would want to know that.$"

Nexus_Text_IronCrown_Arrival:
	.string "A field of steel blades, driven into the\n"
	.string "ground in perfect rows.\p"
	.string "Each one was polished to a mirror. In\n"
	.string "every blade you saw yourself, a little\l"
	.string "later than now.$"

Nexus_Text_IronCrown_Boss:
	.string "One of the mirrors moved.\p"
	.string "Its crown was a blade, and the face\n"
	.string "beneath it showed nothing at all. Not\l"
	.string "even you.$"

Nexus_Text_IronCrown_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1023. Paradox.\p"
	.string "A copy of an old legend, wearing a crown\n"
	.string "with nobody under it, and a man in a\l"
	.string "mask who checked, twice, that his own\l"
	.string "face was still there.\p"
	.string "What came back with you is small, and it\n"
	.string "hums. I have not worked out the song.$"

Nexus_Text_Deoxys_Arrival:
	.string "A night sky, and one straight beam of\n"
	.string "light coming down.\p"
	.string "It struck a fallen meteor. All around\n"
	.string "the crater, the stones were slowly\l"
	.string "changing shape, as if they had not\l"
	.string "decided what to be.$"

Nexus_Text_Deoxys_Boss:
	.string "The beam went out. The meteor split\n"
	.string "open.\p"
	.string "Something stood up from it, orange and\n"
	.string "blue, with a crystal in its chest. It\l"
	.string "changed its shape twice before it\l"
	.string "moved.$"

Nexus_Text_Deoxys_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-386. Rewritten.\p"
	.string "Something that fell from the sky and\n"
	.string "changed to survive the landing, and a\l"
	.string "woman who knows exactly how that\l"
	.string "feels.\p"
	.string "What came back with you changes a\n"
	.string "little every day. Anabel says that is\l"
	.string "normal. She says it quietly.$"

Nexus_Text_Reshiram_Arrival:
	.string "A desert of white ash, under a sky that\n"
	.string "burned blue at the edges.\p"
	.string "There were no shadows. Everything was\n"
	.string "lit from every side at once, as if\l"
	.string "nothing here was allowed to hide.$"

Nexus_Text_Reshiram_Boss:
	.string "The heat rose all at once, and the sky\n"
	.string "itself began to move.\p"
	.string "Something white turned its head, and a\n"
	.string "great tail began to spin, bright as a\l"
	.string "furnace.$"

Nexus_Text_Reshiram_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-643. Vast White.\p"
	.string "A place where nothing can hide, and a\n"
	.string "young man who finally stopped hiding\l"
	.string "one small thing.\p"
	.string "What came back with you is small and\n"
	.string "glows faintly. It glowed brighter when\l"
	.string "he laughed. I have no explanation.$"

Nexus_Text_Zekrom_Arrival:
	.string "A city of black towers, inside a\n"
	.string "thundercloud.\p"
	.string "Every window glowed faintly. The whole\n"
	.string "place hummed, as if something enormous\l"
	.string "were charging.$"

Nexus_Text_Zekrom_Boss:
	.string "The hum became a roar. Lightning ran up\n"
	.string "every tower at once.\p"
	.string "In the heart of the cloud, a tail began\n"
	.string "to spin like a generator.$"

Nexus_Text_Zekrom_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-644. Deep Black.\p"
	.string "A storm that pulls in whoever wants\n"
	.string "something badly enough, and a girl who\l"
	.string "wants to see everything.\p"
	.string "What came back with you is small, and\n"
	.string "your hair is standing up. So is mine.$"

Nexus_Text_Kyurem_Arrival:
	.string "A chasm, and ice from wall to wall.\p"
	.string "Pressed into the ice was the shape of a\n"
	.string "dragon. Empty, as if something had\l"
	.string "stepped out of it and left the mold\l"
	.string "behind.\p"
	.string "The cold was not coming from the air. It\n"
	.string "was coming from the hollow.$"

Nexus_Text_Kyurem_Boss:
	.string "The hollow was not empty after all.\p"
	.string "Something grey climbed out of it, half a\n"
	.string "dragon, and the ice cracked every time\l"
	.string "it breathed.$"

Nexus_Text_Kyurem_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-646. Boundary.\p"
	.string "A dragon made of what was left over,\n"
	.string "and a dragon master people call the one\l"
	.string "left over.\p"
	.string "What came back with you is a small, cold\n"
	.string "piece of it. Keep it warm. I suspect\l"
	.string "nobody ever has.$"

Nexus_Text_Keldeo_Arrival:
	.string "A sea with no shore in any direction.\n"
	.string "The water was flat, but not calm. It\l"
	.string "was holding its breath.\p"
	.string "Across its surface ran a line of\n"
	.string "hoofprints, each one still ringing like\l"
	.string "a struck bell.$"

Nexus_Text_Keldeo_Boss:
	.string "The hoofprints stopped right in front\n"
	.string "of you.\p"
	.string "Something small and fast stood on the\n"
	.string "water, and a blade of light slowly grew\l"
	.string "from its brow.$"

Nexus_Text_Keldeo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-647. The Colt.\p"
	.string "A sea that would not let anything sink,\n"
	.string "and a young man who learned to stand\l"
	.string "on waves before he learned to fight.\p"
	.string "What came back with you is a colt that\n"
	.string "has not found its sword yet. It will.\l"
	.string "The young ones always go looking.$"

Nexus_Text_Xerneas_Arrival:
	.string "A forest where everything was in bloom\n"
	.string "at once.\p"
	.string "Flowers, fruit and new leaves, all on\n"
	.string "the same branch. Nothing here was\l"
	.string "withering.\p"
	.string "In the center stood a tree with\n"
	.string "branches that shone in every color.$"

Nexus_Text_Xerneas_Boss:
	.string "The tree stepped forward.\p"
	.string "Its branches were antlers, and every\n"
	.string "color on them grew brighter as it\l"
	.string "looked at you.$"

Nexus_Text_Xerneas_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-716. The Everbloom.\p"
	.string "A forest where nothing ever fades, and\n"
	.string "an artist who has built his whole life\l"
	.string "on moments that do.\p"
	.string "What came back with you is small, and a\n"
	.string "little clumsy, and it will grow old. He\l"
	.string "found that the loveliest thing in the\l"
	.string "file.$"

Nexus_Text_Yveltal_Arrival:
	.string "A forest, turned to grey stone.\p"
	.string "Trees, grass, a flock of birds in the\n"
	.string "middle of taking off. All grey. All still.\p"
	.string "In the middle of it hung a cocoon the\n"
	.string "size of a house.$"

Nexus_Text_Yveltal_Boss:
	.string "The cocoon split down the middle.\p"
	.string "Wings opened out of it, red and black,\n"
	.string "and the grey crept a little further\l"
	.string "across the ground.$"

Nexus_Text_Yveltal_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-717. The Last Wing.\p"
	.string "A forest drained to stone, and a young\n"
	.string "man who walked into it grinning and\l"
	.string "called it the most honest place he had\l"
	.string "ever seen.\p"
	.string "What came back with you is small and\n"
	.string "warm. The grey did not follow it. I\l"
	.string "checked twice.$"

Nexus_Text_Zygarde_Arrival:
	.string "A forest where every green leaf had a\n"
	.string "small point of light on it, blinking\l"
	.string "slowly, like an eye.\p"
	.string "There was no wind. The leaves turned to\n"
	.string "follow you anyway.$"

Nexus_Text_Zygarde_Boss:
	.string "All the points of light left the leaves\n"
	.string "at once and ran together along the\l"
	.string "ground.\p"
	.string "They made a shape. Long, green and\n"
	.string "black, coiled, watching.$"

Nexus_Text_Zygarde_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-718. Order.\p"
	.string "A forest that watches, and a woman who\n"
	.string "says so little that it listened back.\p"
	.string "What came back with you is one small\n"
	.string "green cell. It sits on my desk, blinking.\l"
	.string "I do not think it is waiting for me. I\l"
	.string "think it is counting.$"

Nexus_Text_Volcanion_Arrival:
	.string "A mountain wrapped in fog so thick you\n"
	.string "could lean on it. The ground hissed. Hot\l"
	.string "springs boiled beside streams of\l"
	.string "snowmelt.\p"
	.string "Every few seconds, the whole slope\n"
	.string "sighed out a cloud.$"

Nexus_Text_Volcanion_Boss:
	.string "The fog went silent.\p"
	.string "Then it tore open, and a heavy red\n"
	.string "shape with two great arms on its back\l"
	.string "blew the mist away in a single breath.$"

Nexus_Text_Volcanion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-721. Steam.\p"
	.string "A mountain of fire and water that would\n"
	.string "not destroy each other, and an old\l"
	.string "quizmaster who has lived the same way\l"
	.string "for years.\p"
	.string "What followed you out is small, and\n"
	.string "puffs a little steam when it is nervous.\l"
	.string "He says that is the right answer.$"

Nexus_Text_Zacian_Arrival:
	.string "A battlefield that had been over for a\n"
	.string "very long time.\p"
	.string "Rusted swords stood in the grass in\n"
	.string "rows, like a crop. At the far end, a\l"
	.string "stone king held a sword of his own, the\l"
	.string "only blade in the field without a spot\l"
	.string "of rust.$"

Nexus_Text_Zacian_Boss:
	.string "One of the rusted swords pulled itself\n"
	.string "out of the ground.\p"
	.string "It was held in the jaws of something\n"
	.string "that had been waiting, very patiently,\l"
	.string "for someone to notice who really won.$"

Nexus_Text_Zacian_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-888. Warrior.\p"
	.string "A field where the kings got the\n"
	.string "statues and the true hero got the\l"
	.string "rust. And a young man who was Champion\l"
	.string "for one afternoon.\p"
	.string "What came home with you is a pup, and\n"
	.string "its sword is not even rusted yet.\l"
	.string "Nobody will build it a statue.\p"
	.string "He said that is fine. He said it twice,\n"
	.string "so I believe him once.$"

Nexus_Text_Zamazenta_Arrival:
	.string "A battlefield under a gray dawn. No one\n"
	.string "was left on it.\p"
	.string "Hundreds of shields stood planted in\n"
	.string "the mud, all facing the same way, still\l"
	.string "holding the line for soldiers who had\l"
	.string "gone home long ago.$"

Nexus_Text_Zamazenta_Boss:
	.string "One shield in the middle of the field\n"
	.string "moved.\p"
	.string "It was not a shield. It was a great\n"
	.string "wolf, and it had stood guard so long\l"
	.string "that the grass had grown around its\l"
	.string "paws.$"

Nexus_Text_Zamazenta_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-889. The Shield.\p"
	.string "A field where every shield outlasted\n"
	.string "the one who carried it, and a father\l"
	.string "who only ever wanted to be the thing\l"
	.string "standing in front.\p"
	.string "What came back with you is young, and\n"
	.string "it already sits between you and the\l"
	.string "door. I did not teach it that.$"

Nexus_Text_Eternatus_Arrival:
	.string "A huge stadium under a red sky.\p"
	.string "Every floodlight was on, every one of\n"
	.string "them aimed at the center of the pitch,\l"
	.string "and every seat was empty.\p"
	.string "The lights were not shining. They were\n"
	.string "pulling the light in.$"

Nexus_Text_Eternatus_Boss:
	.string "The pitch cracked open, and the red\n"
	.string "sky poured down into it.\p"
	.string "Something long and bone-white rose\n"
	.string "out of the ground, and every\l"
	.string "floodlight turned to face it.$"

Nexus_Text_Eternatus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-890. Darkest Day.\p"
	.string "A stadium lit by the thing that eats\n"
	.string "its light, and a showman who loves an\l"
	.string "audience a little too much.\p"
	.string "What came back with you glows faintly,\n"
	.string "and only when someone looks at it. I\l"
	.string "have decided to look at it often.$"

Nexus_Text_Regieleki_Arrival:
	.string "A stone chamber, sealed on every side.\n"
	.string "Hundreds of yellow rings lay on the\l"
	.string "floor, broken open.\p"
	.string "The air tasted like a battery.$"

Nexus_Text_Regieleki_Boss:
	.string "A spark crossed the room faster than\n"
	.string "you could turn your head. Then it\l"
	.string "crossed it again.\p"
	.string "It stopped in the middle of the\n"
	.string "chamber, and it had only one ring left.$"

Nexus_Text_Regieleki_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-894. Electron.\p"
	.string "Pure power held in by rings someone\n"
	.string "else put there, and a soldier who says\l"
	.string "discipline is the ring you choose.\p"
	.string "What came back with you is small, and\n"
	.string "wears every one of its rings. For now it\l"
	.string "seems content to.\p"
	.string "I am not sure he believes what he said.\n"
	.string "He said it very loudly.$"

Nexus_Text_Regidrago_Arrival:
	.string "Ruins of carved stone, and every wall\n"
	.string "was a dragon's head.\p"
	.string "Heads, and only heads. No bodies\n"
	.string "anywhere.\p"
	.string "In the center, a green crystal pulsed\n"
	.string "like a heart.$"

Nexus_Text_Regidrago_Boss:
	.string "The crystal went dark.\p"
	.string "In the walls, stone jaws opened, and all\n"
	.string "of them moved together.$"

Nexus_Text_Regidrago_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-895. The Head Without a Dragon.\p"
	.string "Ruins that remember only a dragon's\n"
	.string "teeth, and an old man who has spent his\l"
	.string "life asking what a dragon needs\l"
	.string "besides them.\p"
	.string "What came back with you is small, and it\n"
	.string "follows me around the office. He says\l"
	.string "the answer is a partner. He said it very\l"
	.string "quietly.$"

Nexus_Text_Glastrier_Arrival:
	.string "A harvest field, frozen solid. The\n"
	.string "wheat had turned to ice and rang like\l"
	.string "bells when you touched it.\p"
	.string "Hoofprints crossed it, each one a\n"
	.string "small crater of frost.$"

Nexus_Text_Glastrier_Boss:
	.string "The field went white under a single\n"
	.string "stamp.\p"
	.string "It wore a mask of ice and breathed out\n"
	.string "winter, and it wanted the field you\l"
	.string "were standing on.$"

Nexus_Text_Glastrier_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-896. Wild Horse.\p"
	.string "A harvest nobody will eat, and an old\n"
	.string "man who knew exactly how long the\l"
	.string "field had been frozen.\p"
	.string "What you brought back stamps its foot\n"
	.string "at me. I have decided to allow it.\p"
	.string "He did not say how long. He only said\n"
	.string "spring is always later than you think.$"

Nexus_Text_Spectrier_Arrival:
	.string "A field of dark snow at midnight, and\n"
	.string "a fog so thick you could not see your\l"
	.string "own hands.\p"
	.string "You could hear hooves, though.\n"
	.string "Circling. Closer. Then farther. Then\l"
	.string "closer.$"

Nexus_Text_Spectrier_Boss:
	.string "The hooves stopped right in front of\n"
	.string "you.\p"
	.string "You still could not see it. It did not\n"
	.string "need to see you either.$"

Nexus_Text_Spectrier_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-897. Shadow Steed.\p"
	.string "A field where eyes are useless, and a\n"
	.string "man who has trained all his life to\l"
	.string "see what isn't there.\p"
	.string "What you brought back makes no sound\n"
	.string "at all. I checked twice.\p"
	.string "He found it before I did. He found it\n"
	.string "with his eyes closed.$"

Nexus_Text_Calyrex_Arrival:
	.string "A harvest field under snow.\p"
	.string "The crops had died standing up, waiting\n"
	.string "for hands that never came to gather\l"
	.string "them.\p"
	.string "In the middle of the field was a tree\n"
	.string "stump carved into a throne. On it sat a\l"
	.string "crown, far too small for any head.$"

Nexus_Text_Calyrex_Boss:
	.string "The crown moved.\p"
	.string "Something small wore it, and the dead\n"
	.string "crops around the throne began, very\l"
	.string "slowly, to turn green.$"

Nexus_Text_Calyrex_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-898. King.\p"
	.string "A kingdom with nobody left to believe in\n"
	.string "it, and a man in a mask who knows\l"
	.string "exactly how that works.\p"
	.string "What came back with you is small. So is\n"
	.string "every king, before anyone kneels.$"

Nexus_Text_WoChien_Arrival:
	.string "A forest where the leaves had all died\n"
	.string "and kept falling anyway.\p"
	.string "Wooden tablets hung from every trunk.\n"
	.string "Someone had written on all of them.\l"
	.string "Someone else had scratched it all out.$"

Nexus_Text_WoChien_Boss:
	.string "The dead leaves shifted and rose.\p"
	.string "Under them was a tablet, and under the\n"
	.string "tablet was something that remembered\l"
	.string "every word scratched off it.$"

Nexus_Text_WoChien_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1001. Tablets.\p"
	.string "A forest of erased writing, and an\n"
	.string "executive who keeps a record of\l"
	.string "everything in his own hand.\p"
	.string "What you carried out is a handful of\n"
	.string "leaves around a small piece of wood. It\l"
	.string "is blank. What gets written on it now is\l"
	.string "up to you.$"

Nexus_Text_TingLu_Arrival:
	.string "A dry valley full of wooden stakes,\n"
	.string "pulled out of the ground one by one.\p"
	.string "In the middle sat a huge ceremonial\n"
	.string "bowl, cracked, and filled to the brim\l"
	.string "with black earth.$"

Nexus_Text_TingLu_Boss:
	.string "The black earth in the bowl began to\n"
	.string "breathe.\p"
	.string "Two great antlers pushed up through it,\n"
	.string "and the air went heavy, as if every\l"
	.string "thought had to lift a stone.$"

Nexus_Text_TingLu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1003. Vessel.\p"
	.string "A valley of pulled stakes, and a man who\n"
	.string "likes being feared more than he likes\l"
	.string "anything.\p"
	.string "What you brought back fits in a cupped\n"
	.string "hand and is heavy for its size. It is\l"
	.string "afraid of nothing yet. Let us keep it\l"
	.string "that way.$"

Nexus_Text_Okidogi_Arrival:
	.string "A mountain village at dusk. In the\n"
	.string "square stood three stone statues in a\l"
	.string "row, heaped with fresh flowers.\p"
	.string "One was cracked open, as if the thing it\n"
	.string "showed had punched its way out.$"

Nexus_Text_Okidogi_Boss:
	.string "A chain rattled somewhere in the dark,\n"
	.string "and the smell of poison came with it.\p"
	.string "Something huge and grinning stepped\n"
	.string "down from the empty pedestal.$"

Nexus_Text_Okidogi_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1014. Retainer.\p"
	.string "A village that raised a statue to a\n"
	.string "bully, and a young ninja who knows a\l"
	.string "disguise when she sees one.\p"
	.string "What you brought back has no chain yet,\n"
	.string "and no statue. It will have to earn\l"
	.string "both. She approves.$"

Nexus_Text_Munkidori_Arrival:
	.string "A bamboo forest where the paths kept\n"
	.string "moving. Every turn led back to the same\l"
	.string "stone lantern.\p"
	.string "Far away, someone was laughing. It\n"
	.string "sounded like your own voice.$"

Nexus_Text_Munkidori_Boss:
	.string "The lantern flickered, and the bamboo\n"
	.string "leaned in close.\p"
	.string "Something small with a chain across its\n"
	.string "shoulders dropped from above, and your\l"
	.string "reflection in its eyes waved at you.$"

Nexus_Text_Munkidori_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1015. Retainer.\p"
	.string "A forest that showed everyone what\n"
	.string "they feared, and a ninja who saw only\l"
	.string "her father, and then herself.\p"
	.string "The piece that came back with you is\n"
	.string "small and has not learned a single trick.\l"
	.string "I checked twice. Then a third time.$"

Nexus_Text_Terapagos_Arrival:
	.string "A crater, and every stone in it had\n"
	.string "grown a crystal.\p"
	.string "Plain gray rocks, sprouting facets like\n"
	.string "new teeth. Each facet held a color\l"
	.string "that was nowhere else in the crater.$"

Nexus_Text_Terapagos_Boss:
	.string "In the deepest part of the crater, the\n"
	.string "crystals all turned at once, toward a\l"
	.string "single point.\p"
	.string "Something lifted a shell that was more\n"
	.string "jewel than stone, and the light in\l"
	.string "every facet went out.$"

Nexus_Text_Terapagos_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1024. Crystal Heart.\p"
	.string "A crater where every stone was trying\n"
	.string "to become a jewel, and a teacher who\l"
	.string "only ever asked stones to be stones.\p"
	.string "What came back with you is small, and\n"
	.string "its shell has no crystals yet. I have\l"
	.string "left room in this file for them to grow.$"

Nexus_Text_Pecharunt_Arrival:
	.string "A village festival with no one running\n"
	.string "it. Lanterns lit, stalls piled high with\l"
	.string "pink rice cakes, free for the taking.\p"
	.string "People stood in neat rows, smiling at\n"
	.string "nothing, chewing slowly.$"

Nexus_Text_Pecharunt_Boss:
	.string "Every head in the rows turned toward\n"
	.string "you at once.\p"
	.string "At the end of the path, a small\n"
	.string "peach-colored shell cracked open, and\l"
	.string "something inside it giggled.$"

Nexus_Text_Pecharunt_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1025. Subjugation.\p"
	.string "A festival where everyone smiled\n"
	.string "because they had to, and an old ninja\l"
	.string "who refused a free sweet.\p"
	.string "He says nothing in this world is free\n"
	.string "except a trap.\p"
	.string "What came back with you is a tiny shell\n"
	.string "with no sweets in it. Keep it that way.$"

@ ===========================================================================
@ After-boss drops (afterBossScript, run after the fragment is caught and
@ again on a later visit to the finished day). Items that change a form and
@ that nothing else in the game hands out (.claude/evolucoes.md). Narration,
@ no plate (R20). A full Bag gives nothing and writes nothing: coming back to
@ the finished day the same day offers it again.
@ ===========================================================================

@ Kyurem: the DNA Splicers, until the player has them.
Nexus_EventScript_Kyurem_AfterBoss::
	checkitem ITEM_DNA_SPLICERS
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_AfterBossEnd
	setvar VAR_0x8006, ITEM_DNA_SPLICERS
	msgbox Nexus_Text_Kyurem_AfterBoss, MSGBOX_DEFAULT
	goto Nexus_EventScript_AfterBossGive

@ Calyrex: the Reins of Unity, until the player has them.
Nexus_EventScript_Calyrex_AfterBoss::
	checkitem ITEM_REINS_OF_UNITY
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_AfterBossEnd
	setvar VAR_0x8006, ITEM_REINS_OF_UNITY
	msgbox Nexus_Text_Calyrex_AfterBoss, MSGBOX_DEFAULT
	goto Nexus_EventScript_AfterBossGive

@ Zygarde: the Zygarde Cube, once.
Nexus_EventScript_Zygarde_AfterBoss::
	checkitem ITEM_ZYGARDE_CUBE
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_AfterBossEnd
	setvar VAR_0x8006, ITEM_ZYGARDE_CUBE
	msgbox Nexus_Text_Zygarde_AfterBoss, MSGBOX_DEFAULT
	goto Nexus_EventScript_AfterBossGive

@ Genesect: one Drive the player does not own yet, once per day (gift bit),
@ nothing once all four are owned.
Nexus_EventScript_Genesect_AfterBoss::
	specialvar VAR_RESULT, Nexus_IsGiftTaken
	goto_if_eq VAR_RESULT, TRUE, Nexus_EventScript_AfterBossEnd
	setvar VAR_0x8004, ITEM_DOUSE_DRIVE
	setvar VAR_0x8005, ITEM_CHILL_DRIVE - ITEM_DOUSE_DRIVE + 1
	specialvar VAR_RESULT, GetRandomMissingItemInRange
	goto_if_eq VAR_RESULT, ITEM_NONE, Nexus_EventScript_AfterBossEnd
	copyvar VAR_0x8006, VAR_RESULT
	msgbox Nexus_Text_Genesect_AfterBoss, MSGBOX_DEFAULT
Nexus_EventScript_AfterBossGive::
	checkitemspace VAR_0x8006, 1
	goto_if_eq VAR_RESULT, FALSE, Nexus_EventScript_AfterBossNoRoom
	special Nexus_MarkGiftTaken
	giveitem VAR_0x8006
	closemessage
Nexus_EventScript_AfterBossEnd::
	return

Nexus_EventScript_AfterBossNoRoom::
	msgbox Nexus_Text_AfterBossNoRoom, MSGBOX_DEFAULT
	closemessage
	return

Nexus_Text_Kyurem_AfterBoss:
	.string "Where the fragment was, two halves of\n"
	.string "something are left lying on the floor.\p"
	.string "They are trying to be one thing.$"

Nexus_Text_Calyrex_AfterBoss:
	.string "A braided rein lies where the king\n"
	.string "stood, still waiting for a steed\l"
	.string "that hasn't arrived yet.$"

Nexus_Text_Zygarde_AfterBoss:
	.string "The ground where it stood keeps a\n"
	.string "shape: a small green cube, humming,\l"
	.string "counting cells that aren't there.$"

Nexus_Text_Genesect_AfterBoss:
	.string "Something falls out of the air where\n"
	.string "the cannon was. It is still warm.$"

Nexus_Text_AfterBossNoRoom:
	.string "Something is left behind, but there\n"
	.string "is no room for it in your Bag.\p"
	.string "It will wait here until the day is\n"
	.string "over.$"


@ ---- campeoes extras (inicio) ----
Nexus_EventScript_Colress_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_COLRESS, Nexus_Text_Colress_Genesect_ChampionIntro, Nexus_Text_Colress_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Colress_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Colress_Silvally_ChampionFight::
	nexus_fight TRAINER_NEXUS_COLRESS, Nexus_Text_Colress_Silvally_ChampionIntro, Nexus_Text_Colress_Silvally_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Colress_Silvally_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bruno_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRUNO, Nexus_Text_Bruno_Urshifu_ChampionIntro, Nexus_Text_Bruno_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bruno_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bruno_Terrakion_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRUNO, Nexus_Text_Bruno_Terrakion_ChampionIntro, Nexus_Text_Bruno_Terrakion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bruno_Terrakion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Elesa_Zeraora_ChampionFight::
	nexus_fight TRAINER_NEXUS_ELESA, Nexus_Text_Elesa_Zeraora_ChampionIntro, Nexus_Text_Elesa_Zeraora_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Elesa_Zeraora_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Elesa_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_ELESA, Nexus_Text_Elesa_Meloetta_ChampionIntro, Nexus_Text_Elesa_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Elesa_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Volkner_Regieleki_ChampionFight::
	nexus_fight TRAINER_NEXUS_VOLKNER, Nexus_Text_Volkner_Regieleki_ChampionIntro, Nexus_Text_Volkner_Regieleki_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Volkner_Regieleki_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Volkner_Zekrom_ChampionFight::
	nexus_fight TRAINER_NEXUS_VOLKNER, Nexus_Text_Volkner_Zekrom_ChampionIntro, Nexus_Text_Volkner_Zekrom_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Volkner_Zekrom_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Steven_Diancie_ChampionFight::
	nexus_fight TRAINER_NEXUS_STEVEN, Nexus_Text_Steven_Diancie_ChampionIntro, Nexus_Text_Steven_Diancie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Steven_Diancie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Steven_Registeel_ChampionFight::
	nexus_fight TRAINER_NEXUS_STEVEN, Nexus_Text_Steven_Registeel_ChampionIntro, Nexus_Text_Steven_Registeel_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Steven_Registeel_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ramos_WoChien_ChampionFight::
	nexus_fight TRAINER_NEXUS_RAMOS, Nexus_Text_Ramos_WoChien_ChampionIntro, Nexus_Text_Ramos_WoChien_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ramos_WoChien_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ramos_Shaymin_ChampionFight::
	nexus_fight TRAINER_NEXUS_RAMOS, Nexus_Text_Ramos_Shaymin_ChampionIntro, Nexus_Text_Ramos_Shaymin_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ramos_Shaymin_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Guzma_Buzzwole_ChampionFight::
	nexus_fight TRAINER_NEXUS_GUZMA, Nexus_Text_Guzma_Buzzwole_ChampionIntro, Nexus_Text_Guzma_Buzzwole_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Guzma_Buzzwole_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Guzma_Okidogi_ChampionFight::
	nexus_fight TRAINER_NEXUS_GUZMA, Nexus_Text_Guzma_Okidogi_ChampionIntro, Nexus_Text_Guzma_Okidogi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Guzma_Okidogi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Soliera_Necrozma_ChampionFight::
	nexus_fight TRAINER_NEXUS_SOLIERA, Nexus_Text_Soliera_Necrozma_ChampionIntro, Nexus_Text_Soliera_Necrozma_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Soliera_Necrozma_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Soliera_Nihilego_ChampionFight::
	nexus_fight TRAINER_NEXUS_SOLIERA, Nexus_Text_Soliera_Nihilego_ChampionIntro, Nexus_Text_Soliera_Nihilego_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Soliera_Nihilego_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Byron_Registeel_ChampionFight::
	nexus_fight TRAINER_NEXUS_BYRON, Nexus_Text_Byron_Registeel_ChampionIntro, Nexus_Text_Byron_Registeel_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Byron_Registeel_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Byron_Melmetal_ChampionFight::
	nexus_fight TRAINER_NEXUS_BYRON, Nexus_Text_Byron_Melmetal_ChampionIntro, Nexus_Text_Byron_Melmetal_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Byron_Melmetal_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Fantina_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_FANTINA, Nexus_Text_Fantina_Meloetta_ChampionIntro, Nexus_Text_Fantina_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Fantina_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Fantina_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_FANTINA, Nexus_Text_Fantina_Marshadow_ChampionIntro, Nexus_Text_Fantina_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Fantina_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Red_Mewtwo_ChampionFight::
	nexus_fight TRAINER_NEXUS_RED, Nexus_Text_Red_Mewtwo_ChampionIntro, Nexus_Text_Red_Mewtwo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Red_Mewtwo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Red_Zapdos_ChampionFight::
	nexus_fight TRAINER_NEXUS_RED, Nexus_Text_Red_Zapdos_ChampionIntro, Nexus_Text_Red_Zapdos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Red_Zapdos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Blue_Zekrom_ChampionFight::
	nexus_fight TRAINER_NEXUS_BLUE, Nexus_Text_Blue_Zekrom_ChampionIntro, Nexus_Text_Blue_Zekrom_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Blue_Zekrom_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brock_Regirock_ChampionFight::
	nexus_fight TRAINER_NEXUS_BROCK, Nexus_Text_Brock_Regirock_ChampionIntro, Nexus_Text_Brock_Regirock_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brock_Regirock_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Misty_Suicune_ChampionFight::
	nexus_fight TRAINER_NEXUS_MISTY, Nexus_Text_Misty_Suicune_ChampionIntro, Nexus_Text_Misty_Suicune_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Misty_Suicune_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Erika_TapuBulu_ChampionFight::
	nexus_fight TRAINER_NEXUS_ERIKA, Nexus_Text_Erika_TapuBulu_ChampionIntro, Nexus_Text_Erika_TapuBulu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Erika_TapuBulu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Koga_Munkidori_ChampionFight::
	nexus_fight TRAINER_NEXUS_KOGA, Nexus_Text_Koga_Munkidori_ChampionIntro, Nexus_Text_Koga_Munkidori_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Koga_Munkidori_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Koga_Okidogi_ChampionFight::
	nexus_fight TRAINER_NEXUS_KOGA, Nexus_Text_Koga_Okidogi_ChampionIntro, Nexus_Text_Koga_Okidogi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Koga_Okidogi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Sabrina_Uxie_ChampionFight::
	nexus_fight TRAINER_NEXUS_SABRINA, Nexus_Text_Sabrina_Uxie_ChampionIntro, Nexus_Text_Sabrina_Uxie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Sabrina_Uxie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Blaine_GougingFire_ChampionFight::
	nexus_fight TRAINER_NEXUS_BLAINE, Nexus_Text_Blaine_GougingFire_ChampionIntro, Nexus_Text_Blaine_GougingFire_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Blaine_GougingFire_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Giovanni_Landorus_ChampionFight::
	nexus_fight TRAINER_NEXUS_GIOVANNI, Nexus_Text_Giovanni_Landorus_ChampionIntro, Nexus_Text_Giovanni_Landorus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Giovanni_Landorus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lance_Zygarde_ChampionFight::
	nexus_fight TRAINER_NEXUS_LANCE, Nexus_Text_Lance_Zygarde_ChampionIntro, Nexus_Text_Lance_Zygarde_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lance_Zygarde_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Archer_Zamazenta_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARCHER, Nexus_Text_Archer_Zamazenta_ChampionIntro, Nexus_Text_Archer_Zamazenta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Archer_Zamazenta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ariana_Fezandipiti_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARIANA, Nexus_Text_Ariana_Fezandipiti_ChampionIntro, Nexus_Text_Ariana_Fezandipiti_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ariana_Fezandipiti_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ariana_Enamorus_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARIANA, Nexus_Text_Ariana_Enamorus_ChampionIntro, Nexus_Text_Ariana_Enamorus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ariana_Enamorus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Proton_ChiYu_ChampionFight::
	nexus_fight TRAINER_NEXUS_PROTON, Nexus_Text_Proton_ChiYu_ChampionIntro, Nexus_Text_Proton_ChiYu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Proton_ChiYu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Petrel_Fezandipiti_ChampionFight::
	nexus_fight TRAINER_NEXUS_PETREL, Nexus_Text_Petrel_Fezandipiti_ChampionIntro, Nexus_Text_Petrel_Fezandipiti_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Petrel_Fezandipiti_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Silver_Silvally_ChampionFight::
	nexus_fight TRAINER_NEXUS_SILVER, Nexus_Text_Silver_Silvally_ChampionIntro, Nexus_Text_Silver_Silvally_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Silver_Silvally_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Silver_Darkrai_ChampionFight::
	nexus_fight TRAINER_NEXUS_SILVER, Nexus_Text_Silver_Darkrai_ChampionIntro, Nexus_Text_Silver_Darkrai_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Silver_Darkrai_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Falkner_Lugia_ChampionFight::
	nexus_fight TRAINER_NEXUS_FALKNER, Nexus_Text_Falkner_Lugia_ChampionIntro, Nexus_Text_Falkner_Lugia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Falkner_Lugia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Falkner_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_FALKNER, Nexus_Text_Falkner_Articuno_ChampionIntro, Nexus_Text_Falkner_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Falkner_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bugsy_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_BUGSY, Nexus_Text_Bugsy_Genesect_ChampionIntro, Nexus_Text_Bugsy_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bugsy_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Whitney_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_WHITNEY, Nexus_Text_Whitney_Meloetta_ChampionIntro, Nexus_Text_Whitney_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Whitney_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Morty_Lunala_ChampionFight::
	nexus_fight TRAINER_NEXUS_MORTY, Nexus_Text_Morty_Lunala_ChampionIntro, Nexus_Text_Morty_Lunala_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Morty_Lunala_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Chuck_Buzzwole_ChampionFight::
	nexus_fight TRAINER_NEXUS_CHUCK, Nexus_Text_Chuck_Buzzwole_ChampionIntro, Nexus_Text_Chuck_Buzzwole_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Chuck_Buzzwole_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Jasmine_Registeel_ChampionFight::
	nexus_fight TRAINER_NEXUS_JASMINE, Nexus_Text_Jasmine_Registeel_ChampionIntro, Nexus_Text_Jasmine_Registeel_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Jasmine_Registeel_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Pryce_Regice_ChampionFight::
	nexus_fight TRAINER_NEXUS_PRYCE, Nexus_Text_Pryce_Regice_ChampionIntro, Nexus_Text_Pryce_Regice_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Pryce_Regice_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Clair_Regidrago_ChampionFight::
	nexus_fight TRAINER_NEXUS_CLAIR, Nexus_Text_Clair_Regidrago_ChampionIntro, Nexus_Text_Clair_Regidrago_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Clair_Regidrago_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Clair_Latias_ChampionFight::
	nexus_fight TRAINER_NEXUS_CLAIR, Nexus_Text_Clair_Latias_ChampionIntro, Nexus_Text_Clair_Latias_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Clair_Latias_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Will_Hoopa_ChampionFight::
	nexus_fight TRAINER_NEXUS_WILL, Nexus_Text_Will_Hoopa_ChampionIntro, Nexus_Text_Will_Hoopa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Will_Hoopa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Karen_Zarude_ChampionFight::
	nexus_fight TRAINER_NEXUS_KAREN, Nexus_Text_Karen_Zarude_ChampionIntro, Nexus_Text_Karen_Zarude_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Karen_Zarude_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brendan_Deoxys_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRENDAN, Nexus_Text_Brendan_Deoxys_ChampionIntro, Nexus_Text_Brendan_Deoxys_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brendan_Deoxys_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_May_Latias_ChampionFight::
	nexus_fight TRAINER_NEXUS_MAY, Nexus_Text_May_Latias_ChampionIntro, Nexus_Text_May_Latias_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_May_Latias_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wally_Keldeo_ChampionFight::
	nexus_fight TRAINER_NEXUS_WALLY, Nexus_Text_Wally_Keldeo_ChampionIntro, Nexus_Text_Wally_Keldeo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wally_Keldeo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Roxanne_Regirock_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROXANNE, Nexus_Text_Roxanne_Regirock_ChampionIntro, Nexus_Text_Roxanne_Regirock_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Roxanne_Regirock_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brawly_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRAWLY, Nexus_Text_Brawly_Urshifu_ChampionIntro, Nexus_Text_Brawly_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brawly_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wattson_Xurkitree_ChampionFight::
	nexus_fight TRAINER_NEXUS_WATTSON, Nexus_Text_Wattson_Xurkitree_ChampionIntro, Nexus_Text_Wattson_Xurkitree_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wattson_Xurkitree_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Flannery_Entei_ChampionFight::
	nexus_fight TRAINER_NEXUS_FLANNERY, Nexus_Text_Flannery_Entei_ChampionIntro, Nexus_Text_Flannery_Entei_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Flannery_Entei_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Norman_Regigigas_ChampionFight::
	nexus_fight TRAINER_NEXUS_NORMAN, Nexus_Text_Norman_Regigigas_ChampionIntro, Nexus_Text_Norman_Regigigas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Norman_Regigigas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Winona_Lugia_ChampionFight::
	nexus_fight TRAINER_NEXUS_WINONA, Nexus_Text_Winona_Lugia_ChampionIntro, Nexus_Text_Winona_Lugia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Winona_Lugia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Wallace_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_WALLACE, Nexus_Text_Wallace_Meloetta_ChampionIntro, Nexus_Text_Wallace_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Wallace_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Juan_Manaphy_ChampionFight::
	nexus_fight TRAINER_NEXUS_JUAN, Nexus_Text_Juan_Manaphy_ChampionIntro, Nexus_Text_Juan_Manaphy_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Juan_Manaphy_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Sidney_GalarianMoltres_ChampionFight::
	nexus_fight TRAINER_NEXUS_SIDNEY, Nexus_Text_Sidney_GalarianMoltres_ChampionIntro, Nexus_Text_Sidney_GalarianMoltres_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Sidney_GalarianMoltres_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Phoebe_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_PHOEBE, Nexus_Text_Phoebe_Marshadow_ChampionIntro, Nexus_Text_Phoebe_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Phoebe_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Phoebe_Lunala_ChampionFight::
	nexus_fight TRAINER_NEXUS_PHOEBE, Nexus_Text_Phoebe_Lunala_ChampionIntro, Nexus_Text_Phoebe_Lunala_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Phoebe_Lunala_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Glacia_Regice_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLACIA, Nexus_Text_Glacia_Regice_ChampionIntro, Nexus_Text_Glacia_Regice_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Glacia_Regice_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Drake_Rayquaza_ChampionFight::
	nexus_fight TRAINER_NEXUS_DRAKE, Nexus_Text_Drake_Rayquaza_ChampionIntro, Nexus_Text_Drake_Rayquaza_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Drake_Rayquaza_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Noland_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_NOLAND, Nexus_Text_Noland_Genesect_ChampionIntro, Nexus_Text_Noland_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Noland_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Greta_Buzzwole_ChampionFight::
	nexus_fight TRAINER_NEXUS_GRETA, Nexus_Text_Greta_Buzzwole_ChampionIntro, Nexus_Text_Greta_Buzzwole_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Greta_Buzzwole_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Tucker_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_TUCKER, Nexus_Text_Tucker_Meloetta_ChampionIntro, Nexus_Text_Tucker_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Tucker_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lucy_Spectrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_LUCY, Nexus_Text_Lucy_Spectrier_ChampionIntro, Nexus_Text_Lucy_Spectrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lucy_Spectrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Spenser_Calyrex_ChampionFight::
	nexus_fight TRAINER_NEXUS_SPENSER, Nexus_Text_Spenser_Calyrex_ChampionIntro, Nexus_Text_Spenser_Calyrex_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Spenser_Calyrex_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Anabel_Lunala_ChampionFight::
	nexus_fight TRAINER_NEXUS_ANABEL, Nexus_Text_Anabel_Lunala_ChampionIntro, Nexus_Text_Anabel_Lunala_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Anabel_Lunala_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Maxie_Volcanion_ChampionFight::
	nexus_fight TRAINER_NEXUS_MAXIE, Nexus_Text_Maxie_Volcanion_ChampionIntro, Nexus_Text_Maxie_Volcanion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Maxie_Volcanion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Archie_Manaphy_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARCHIE, Nexus_Text_Archie_Manaphy_ChampionIntro, Nexus_Text_Archie_Manaphy_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Archie_Manaphy_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Archie_Lugia_ChampionFight::
	nexus_fight TRAINER_NEXUS_ARCHIE, Nexus_Text_Archie_Lugia_ChampionIntro, Nexus_Text_Archie_Lugia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Archie_Lugia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gladion_Mewtwo_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLADION, Nexus_Text_Gladion_Mewtwo_ChampionIntro, Nexus_Text_Gladion_Mewtwo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gladion_Mewtwo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Kukui_Zeraora_ChampionFight::
	nexus_fight TRAINER_NEXUS_KUKUI, Nexus_Text_Kukui_Zeraora_ChampionIntro, Nexus_Text_Kukui_Zeraora_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Kukui_Zeraora_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lusamine_Nihilego_ChampionFight::
	nexus_fight TRAINER_NEXUS_LUSAMINE, Nexus_Text_Lusamine_Nihilego_ChampionIntro, Nexus_Text_Lusamine_Nihilego_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lusamine_Nihilego_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Janine_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_JANINE, Nexus_Text_Janine_Marshadow_ChampionIntro, Nexus_Text_Janine_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Janine_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Leaf_Celebi_ChampionFight::
	nexus_fight TRAINER_NEXUS_LEAF, Nexus_Text_Leaf_Celebi_ChampionIntro, Nexus_Text_Leaf_Celebi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Leaf_Celebi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_AZ_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_AZ, Nexus_Text_AZ_Xerneas_ChampionIntro, Nexus_Text_AZ_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_AZ_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_AZ_Yveltal_ChampionFight::
	nexus_fight TRAINER_NEXUS_AZ, Nexus_Text_AZ_Yveltal_ChampionIntro, Nexus_Text_AZ_Yveltal_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_AZ_Yveltal_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_AZ_Celebi_ChampionFight::
	nexus_fight TRAINER_NEXUS_AZ, Nexus_Text_AZ_Celebi_ChampionIntro, Nexus_Text_AZ_Celebi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_AZ_Celebi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Agatha_Spectrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_AGATHA, Nexus_Text_Agatha_Spectrier_ChampionIntro, Nexus_Text_Agatha_Spectrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Agatha_Spectrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Agatha_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_AGATHA, Nexus_Text_Agatha_Marshadow_ChampionIntro, Nexus_Text_Agatha_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Agatha_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Agatha_Giratina_ChampionFight::
	nexus_fight TRAINER_NEXUS_AGATHA, Nexus_Text_Agatha_Giratina_ChampionIntro, Nexus_Text_Agatha_Giratina_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Agatha_Giratina_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Alder_SlitherWing_ChampionFight::
	nexus_fight TRAINER_NEXUS_ALDER, Nexus_Text_Alder_SlitherWing_ChampionIntro, Nexus_Text_Alder_SlitherWing_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Alder_SlitherWing_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Alder_Groudon_ChampionFight::
	nexus_fight TRAINER_NEXUS_ALDER, Nexus_Text_Alder_Groudon_ChampionIntro, Nexus_Text_Alder_Groudon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Alder_Groudon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Alder_HoOh_ChampionFight::
	nexus_fight TRAINER_NEXUS_ALDER, Nexus_Text_Alder_HoOh_ChampionIntro, Nexus_Text_Alder_HoOh_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Alder_HoOh_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Allister_Lunala_ChampionFight::
	nexus_fight TRAINER_NEXUS_ALLISTER, Nexus_Text_Allister_Lunala_ChampionIntro, Nexus_Text_Allister_Lunala_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Allister_Lunala_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Allister_Spectrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_ALLISTER, Nexus_Text_Allister_Spectrier_ChampionIntro, Nexus_Text_Allister_Spectrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Allister_Spectrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Allister_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_ALLISTER, Nexus_Text_Allister_Marshadow_ChampionIntro, Nexus_Text_Allister_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Allister_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Avery_Mewtwo_ChampionFight::
	nexus_fight TRAINER_NEXUS_AVERY, Nexus_Text_Avery_Mewtwo_ChampionIntro, Nexus_Text_Avery_Mewtwo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Avery_Mewtwo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Avery_GalarianArticuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_AVERY, Nexus_Text_Avery_GalarianArticuno_ChampionIntro, Nexus_Text_Avery_GalarianArticuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Avery_GalarianArticuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Avery_Hoopa_ChampionFight::
	nexus_fight TRAINER_NEXUS_AVERY, Nexus_Text_Avery_Hoopa_ChampionIntro, Nexus_Text_Avery_Hoopa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Avery_Hoopa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Barry_Uxie_ChampionFight::
	nexus_fight TRAINER_NEXUS_BARRY, Nexus_Text_Barry_Uxie_ChampionIntro, Nexus_Text_Barry_Uxie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Barry_Uxie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Barry_Deoxys_ChampionFight::
	nexus_fight TRAINER_NEXUS_BARRY, Nexus_Text_Barry_Deoxys_ChampionIntro, Nexus_Text_Barry_Deoxys_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Barry_Deoxys_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Barry_Azelf_ChampionFight::
	nexus_fight TRAINER_NEXUS_BARRY, Nexus_Text_Barry_Azelf_ChampionIntro, Nexus_Text_Barry_Azelf_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Barry_Azelf_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bea_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_BEA, Nexus_Text_Bea_Marshadow_ChampionIntro, Nexus_Text_Bea_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bea_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bea_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_BEA, Nexus_Text_Bea_Urshifu_ChampionIntro, Nexus_Text_Bea_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bea_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Bea_GalarianZapdos_ChampionFight::
	nexus_fight TRAINER_NEXUS_BEA, Nexus_Text_Bea_GalarianZapdos_ChampionIntro, Nexus_Text_Bea_GalarianZapdos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Bea_GalarianZapdos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brycen_Kyurem_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRYCEN, Nexus_Text_Brycen_Kyurem_ChampionIntro, Nexus_Text_Brycen_Kyurem_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brycen_Kyurem_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brycen_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRYCEN, Nexus_Text_Brycen_Articuno_ChampionIntro, Nexus_Text_Brycen_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brycen_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Brycen_Regice_ChampionFight::
	nexus_fight TRAINER_NEXUS_BRYCEN, Nexus_Text_Brycen_Regice_ChampionIntro, Nexus_Text_Brycen_Regice_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Brycen_Regice_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cheren_Cobalion_ChampionFight::
	nexus_fight TRAINER_NEXUS_CHEREN, Nexus_Text_Cheren_Cobalion_ChampionIntro, Nexus_Text_Cheren_Cobalion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cheren_Cobalion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cheren_Kyurem_ChampionFight::
	nexus_fight TRAINER_NEXUS_CHEREN, Nexus_Text_Cheren_Kyurem_ChampionIntro, Nexus_Text_Cheren_Kyurem_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cheren_Kyurem_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cheren_Zamazenta_ChampionFight::
	nexus_fight TRAINER_NEXUS_CHEREN, Nexus_Text_Cheren_Zamazenta_ChampionIntro, Nexus_Text_Cheren_Zamazenta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cheren_Zamazenta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cilan_Virizion_ChampionFight::
	nexus_fight TRAINER_NEXUS_CILAN, Nexus_Text_Cilan_Virizion_ChampionIntro, Nexus_Text_Cilan_Virizion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cilan_Virizion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cilan_Groudon_ChampionFight::
	nexus_fight TRAINER_NEXUS_CILAN, Nexus_Text_Cilan_Groudon_ChampionIntro, Nexus_Text_Cilan_Groudon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cilan_Groudon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cilan_Shaymin_ChampionFight::
	nexus_fight TRAINER_NEXUS_CILAN, Nexus_Text_Cilan_Shaymin_ChampionIntro, Nexus_Text_Cilan_Shaymin_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cilan_Shaymin_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cynthia_Giratina_ChampionFight::
	nexus_fight TRAINER_NEXUS_CYNTHIA, Nexus_Text_Cynthia_Giratina_ChampionIntro, Nexus_Text_Cynthia_Giratina_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cynthia_Giratina_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cynthia_Palkia_ChampionFight::
	nexus_fight TRAINER_NEXUS_CYNTHIA, Nexus_Text_Cynthia_Palkia_ChampionIntro, Nexus_Text_Cynthia_Palkia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cynthia_Palkia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cynthia_Arceus_ChampionFight::
	nexus_fight TRAINER_NEXUS_CYNTHIA, Nexus_Text_Cynthia_Arceus_ChampionIntro, Nexus_Text_Cynthia_Arceus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cynthia_Arceus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cyrus_Dialga_ChampionFight::
	nexus_fight TRAINER_NEXUS_CYRUS, Nexus_Text_Cyrus_Dialga_ChampionIntro, Nexus_Text_Cyrus_Dialga_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cyrus_Dialga_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cyrus_Palkia_ChampionFight::
	nexus_fight TRAINER_NEXUS_CYRUS, Nexus_Text_Cyrus_Palkia_ChampionIntro, Nexus_Text_Cyrus_Palkia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cyrus_Palkia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Cyrus_Mesprit_ChampionFight::
	nexus_fight TRAINER_NEXUS_CYRUS, Nexus_Text_Cyrus_Mesprit_ChampionIntro, Nexus_Text_Cyrus_Mesprit_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Cyrus_Mesprit_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Dawn_Palkia_ChampionFight::
	nexus_fight TRAINER_NEXUS_DAWN, Nexus_Text_Dawn_Palkia_ChampionIntro, Nexus_Text_Dawn_Palkia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Dawn_Palkia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Dawn_Cresselia_ChampionFight::
	nexus_fight TRAINER_NEXUS_DAWN, Nexus_Text_Dawn_Cresselia_ChampionIntro, Nexus_Text_Dawn_Cresselia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Dawn_Cresselia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Dawn_Mesprit_ChampionFight::
	nexus_fight TRAINER_NEXUS_DAWN, Nexus_Text_Dawn_Mesprit_ChampionIntro, Nexus_Text_Dawn_Mesprit_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Dawn_Mesprit_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Diantha_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_DIANTHA, Nexus_Text_Diantha_Xerneas_ChampionIntro, Nexus_Text_Diantha_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Diantha_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Diantha_IronValiant_ChampionFight::
	nexus_fight TRAINER_NEXUS_DIANTHA, Nexus_Text_Diantha_IronValiant_ChampionIntro, Nexus_Text_Diantha_IronValiant_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Diantha_IronValiant_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Diantha_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_DIANTHA, Nexus_Text_Diantha_Meloetta_ChampionIntro, Nexus_Text_Diantha_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Diantha_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gardenia_Shaymin_ChampionFight::
	nexus_fight TRAINER_NEXUS_GARDENIA, Nexus_Text_Gardenia_Shaymin_ChampionIntro, Nexus_Text_Gardenia_Shaymin_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gardenia_Shaymin_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gardenia_Zygarde_ChampionFight::
	nexus_fight TRAINER_NEXUS_GARDENIA, Nexus_Text_Gardenia_Zygarde_ChampionIntro, Nexus_Text_Gardenia_Zygarde_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gardenia_Zygarde_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gardenia_Celebi_ChampionFight::
	nexus_fight TRAINER_NEXUS_GARDENIA, Nexus_Text_Gardenia_Celebi_ChampionIntro, Nexus_Text_Gardenia_Celebi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gardenia_Celebi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ghetsis_Kyurem_ChampionFight::
	nexus_fight TRAINER_NEXUS_GHETSIS, Nexus_Text_Ghetsis_Kyurem_ChampionIntro, Nexus_Text_Ghetsis_Kyurem_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ghetsis_Kyurem_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ghetsis_Cobalion_ChampionFight::
	nexus_fight TRAINER_NEXUS_GHETSIS, Nexus_Text_Ghetsis_Cobalion_ChampionIntro, Nexus_Text_Ghetsis_Cobalion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ghetsis_Cobalion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Ghetsis_Pecharunt_ChampionFight::
	nexus_fight TRAINER_NEXUS_GHETSIS, Nexus_Text_Ghetsis_Pecharunt_ChampionIntro, Nexus_Text_Ghetsis_Pecharunt_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Ghetsis_Pecharunt_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gloria_Zacian_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLORIA, Nexus_Text_Gloria_Zacian_ChampionIntro, Nexus_Text_Gloria_Zacian_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gloria_Zacian_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gloria_Zamazenta_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLORIA, Nexus_Text_Gloria_Zamazenta_ChampionIntro, Nexus_Text_Gloria_Zamazenta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gloria_Zamazenta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Gloria_Eternatus_ChampionFight::
	nexus_fight TRAINER_NEXUS_GLORIA, Nexus_Text_Gloria_Eternatus_ChampionIntro, Nexus_Text_Gloria_Eternatus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Gloria_Eternatus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Grusha_Kyurem_ChampionFight::
	nexus_fight TRAINER_NEXUS_GRUSHA, Nexus_Text_Grusha_Kyurem_ChampionIntro, Nexus_Text_Grusha_Kyurem_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Grusha_Kyurem_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Grusha_ChienPao_ChampionFight::
	nexus_fight TRAINER_NEXUS_GRUSHA, Nexus_Text_Grusha_ChienPao_ChampionIntro, Nexus_Text_Grusha_ChienPao_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Grusha_ChienPao_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Grusha_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_GRUSHA, Nexus_Text_Grusha_Articuno_ChampionIntro, Nexus_Text_Grusha_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Grusha_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hassel_Rayquaza_ChampionFight::
	nexus_fight TRAINER_NEXUS_HASSEL, Nexus_Text_Hassel_Rayquaza_ChampionIntro, Nexus_Text_Hassel_Rayquaza_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hassel_Rayquaza_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hassel_Regidrago_ChampionFight::
	nexus_fight TRAINER_NEXUS_HASSEL, Nexus_Text_Hassel_Regidrago_ChampionIntro, Nexus_Text_Hassel_Regidrago_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hassel_Regidrago_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hassel_Latias_ChampionFight::
	nexus_fight TRAINER_NEXUS_HASSEL, Nexus_Text_Hassel_Latias_ChampionIntro, Nexus_Text_Hassel_Latias_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hassel_Latias_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hau_TapuKoko_ChampionFight::
	nexus_fight TRAINER_NEXUS_HAU, Nexus_Text_Hau_TapuKoko_ChampionIntro, Nexus_Text_Hau_TapuKoko_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hau_TapuKoko_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hau_Solgaleo_ChampionFight::
	nexus_fight TRAINER_NEXUS_HAU, Nexus_Text_Hau_Solgaleo_ChampionIntro, Nexus_Text_Hau_Solgaleo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hau_Solgaleo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hau_TapuLele_ChampionFight::
	nexus_fight TRAINER_NEXUS_HAU, Nexus_Text_Hau_TapuLele_ChampionIntro, Nexus_Text_Hau_TapuLele_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hau_TapuLele_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hilda_Reshiram_ChampionFight::
	nexus_fight TRAINER_NEXUS_HILDA, Nexus_Text_Hilda_Reshiram_ChampionIntro, Nexus_Text_Hilda_Reshiram_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hilda_Reshiram_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hilda_Tornadus_ChampionFight::
	nexus_fight TRAINER_NEXUS_HILDA, Nexus_Text_Hilda_Tornadus_ChampionIntro, Nexus_Text_Hilda_Tornadus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hilda_Tornadus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hilda_Victini_ChampionFight::
	nexus_fight TRAINER_NEXUS_HILDA, Nexus_Text_Hilda_Victini_ChampionIntro, Nexus_Text_Hilda_Victini_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hilda_Victini_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hop_Zamazenta_ChampionFight::
	nexus_fight TRAINER_NEXUS_HOP, Nexus_Text_Hop_Zamazenta_ChampionIntro, Nexus_Text_Hop_Zamazenta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hop_Zamazenta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hop_Silvally_ChampionFight::
	nexus_fight TRAINER_NEXUS_HOP, Nexus_Text_Hop_Silvally_ChampionIntro, Nexus_Text_Hop_Silvally_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hop_Silvally_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Hop_Suicune_ChampionFight::
	nexus_fight TRAINER_NEXUS_HOP, Nexus_Text_Hop_Suicune_ChampionIntro, Nexus_Text_Hop_Suicune_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Hop_Suicune_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Iono_Miraidon_ChampionFight::
	nexus_fight TRAINER_NEXUS_IONO, Nexus_Text_Iono_Miraidon_ChampionIntro, Nexus_Text_Iono_Miraidon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Iono_Miraidon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Iono_Regieleki_ChampionFight::
	nexus_fight TRAINER_NEXUS_IONO, Nexus_Text_Iono_Regieleki_ChampionIntro, Nexus_Text_Iono_Regieleki_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Iono_Regieleki_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Iono_Xurkitree_ChampionFight::
	nexus_fight TRAINER_NEXUS_IONO, Nexus_Text_Iono_Xurkitree_ChampionIntro, Nexus_Text_Iono_Xurkitree_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Iono_Xurkitree_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Iris_Reshiram_ChampionFight::
	nexus_fight TRAINER_NEXUS_IRIS, Nexus_Text_Iris_Reshiram_ChampionIntro, Nexus_Text_Iris_Reshiram_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Iris_Reshiram_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Iris_Latias_ChampionFight::
	nexus_fight TRAINER_NEXUS_IRIS, Nexus_Text_Iris_Latias_ChampionIntro, Nexus_Text_Iris_Latias_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Iris_Latias_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Iris_Regidrago_ChampionFight::
	nexus_fight TRAINER_NEXUS_IRIS, Nexus_Text_Iris_Regidrago_ChampionIntro, Nexus_Text_Iris_Regidrago_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Iris_Regidrago_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_JessieJames_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_JESSIE_JAMES, Nexus_Text_JessieJames_Meloetta_ChampionIntro, Nexus_Text_JessieJames_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_JessieJames_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_JessieJames_Zygarde_ChampionFight::
	nexus_fight TRAINER_NEXUS_JESSIE_JAMES, Nexus_Text_JessieJames_Zygarde_ChampionIntro, Nexus_Text_JessieJames_Zygarde_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_JessieJames_Zygarde_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_JessieJames_Hoopa_ChampionFight::
	nexus_fight TRAINER_NEXUS_JESSIE_JAMES, Nexus_Text_JessieJames_Hoopa_ChampionIntro, Nexus_Text_JessieJames_Hoopa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_JessieJames_Hoopa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Juniper_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_JUNIPER, Nexus_Text_Juniper_Genesect_ChampionIntro, Nexus_Text_Juniper_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Juniper_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Juniper_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_JUNIPER, Nexus_Text_Juniper_Meloetta_ChampionIntro, Nexus_Text_Juniper_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Juniper_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Juniper_Mew_ChampionFight::
	nexus_fight TRAINER_NEXUS_JUNIPER, Nexus_Text_Juniper_Mew_ChampionIntro, Nexus_Text_Juniper_Mew_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Juniper_Mew_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Katy_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_KATY, Nexus_Text_Katy_Genesect_ChampionIntro, Nexus_Text_Katy_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Katy_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Katy_SlitherWing_ChampionFight::
	nexus_fight TRAINER_NEXUS_KATY, Nexus_Text_Katy_SlitherWing_ChampionIntro, Nexus_Text_Katy_SlitherWing_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Katy_SlitherWing_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Katy_Pheromosa_ChampionFight::
	nexus_fight TRAINER_NEXUS_KATY, Nexus_Text_Katy_Pheromosa_ChampionIntro, Nexus_Text_Katy_Pheromosa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Katy_Pheromosa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Klara_Munkidori_ChampionFight::
	nexus_fight TRAINER_NEXUS_KLARA, Nexus_Text_Klara_Munkidori_ChampionIntro, Nexus_Text_Klara_Munkidori_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Klara_Munkidori_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Klara_Eternatus_ChampionFight::
	nexus_fight TRAINER_NEXUS_KLARA, Nexus_Text_Klara_Eternatus_ChampionIntro, Nexus_Text_Klara_Eternatus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Klara_Eternatus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Klara_Fezandipiti_ChampionFight::
	nexus_fight TRAINER_NEXUS_KLARA, Nexus_Text_Klara_Fezandipiti_ChampionIntro, Nexus_Text_Klara_Fezandipiti_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Klara_Fezandipiti_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Korrina_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_KORRINA, Nexus_Text_Korrina_Urshifu_ChampionIntro, Nexus_Text_Korrina_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Korrina_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Korrina_Koraidon_ChampionFight::
	nexus_fight TRAINER_NEXUS_KORRINA, Nexus_Text_Korrina_Koraidon_ChampionIntro, Nexus_Text_Korrina_Koraidon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Korrina_Koraidon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Korrina_Zeraora_ChampionFight::
	nexus_fight TRAINER_NEXUS_KORRINA, Nexus_Text_Korrina_Zeraora_ChampionIntro, Nexus_Text_Korrina_Zeraora_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Korrina_Zeraora_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Larry_Terapagos_ChampionFight::
	nexus_fight TRAINER_NEXUS_LARRY, Nexus_Text_Larry_Terapagos_ChampionIntro, Nexus_Text_Larry_Terapagos_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Larry_Terapagos_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Larry_Tornadus_ChampionFight::
	nexus_fight TRAINER_NEXUS_LARRY, Nexus_Text_Larry_Tornadus_ChampionIntro, Nexus_Text_Larry_Tornadus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Larry_Tornadus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Larry_Regigigas_ChampionFight::
	nexus_fight TRAINER_NEXUS_LARRY, Nexus_Text_Larry_Regigigas_ChampionIntro, Nexus_Text_Larry_Regigigas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Larry_Regigigas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lenora_Arceus_ChampionFight::
	nexus_fight TRAINER_NEXUS_LENORA, Nexus_Text_Lenora_Arceus_ChampionIntro, Nexus_Text_Lenora_Arceus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lenora_Arceus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lenora_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_LENORA, Nexus_Text_Lenora_Meloetta_ChampionIntro, Nexus_Text_Lenora_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lenora_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lenora_Regirock_ChampionFight::
	nexus_fight TRAINER_NEXUS_LENORA, Nexus_Text_Lenora_Regirock_ChampionIntro, Nexus_Text_Lenora_Regirock_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lenora_Regirock_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Leon_Eternatus_ChampionFight::
	nexus_fight TRAINER_NEXUS_LEON, Nexus_Text_Leon_Eternatus_ChampionIntro, Nexus_Text_Leon_Eternatus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Leon_Eternatus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Leon_Zacian_ChampionFight::
	nexus_fight TRAINER_NEXUS_LEON, Nexus_Text_Leon_Zacian_ChampionIntro, Nexus_Text_Leon_Zacian_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Leon_Zacian_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Leon_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_LEON, Nexus_Text_Leon_Urshifu_ChampionIntro, Nexus_Text_Leon_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Leon_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lorelei_Glastrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_LORELEI, Nexus_Text_Lorelei_Glastrier_ChampionIntro, Nexus_Text_Lorelei_Glastrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lorelei_Glastrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lorelei_Kyurem_ChampionFight::
	nexus_fight TRAINER_NEXUS_LORELEI, Nexus_Text_Lorelei_Kyurem_ChampionIntro, Nexus_Text_Lorelei_Kyurem_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lorelei_Kyurem_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lorelei_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_LORELEI, Nexus_Text_Lorelei_Articuno_ChampionIntro, Nexus_Text_Lorelei_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lorelei_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lysandre_Yveltal_ChampionFight::
	nexus_fight TRAINER_NEXUS_LYSANDRE, Nexus_Text_Lysandre_Yveltal_ChampionIntro, Nexus_Text_Lysandre_Yveltal_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lysandre_Yveltal_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lysandre_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_LYSANDRE, Nexus_Text_Lysandre_Xerneas_ChampionIntro, Nexus_Text_Lysandre_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lysandre_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lysandre_Volcanion_ChampionFight::
	nexus_fight TRAINER_NEXUS_LYSANDRE, Nexus_Text_Lysandre_Volcanion_ChampionIntro, Nexus_Text_Lysandre_Volcanion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lysandre_Volcanion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Marnie_GalarianMoltres_ChampionFight::
	nexus_fight TRAINER_NEXUS_MARNIE, Nexus_Text_Marnie_GalarianMoltres_ChampionIntro, Nexus_Text_Marnie_GalarianMoltres_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Marnie_GalarianMoltres_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Marnie_Yveltal_ChampionFight::
	nexus_fight TRAINER_NEXUS_MARNIE, Nexus_Text_Marnie_Yveltal_ChampionIntro, Nexus_Text_Marnie_Yveltal_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Marnie_Yveltal_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Marnie_Darkrai_ChampionFight::
	nexus_fight TRAINER_NEXUS_MARNIE, Nexus_Text_Marnie_Darkrai_ChampionIntro, Nexus_Text_Marnie_Darkrai_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Marnie_Darkrai_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Melony_Calyrex_ChampionFight::
	nexus_fight TRAINER_NEXUS_MELONY, Nexus_Text_Melony_Calyrex_ChampionIntro, Nexus_Text_Melony_Calyrex_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Melony_Calyrex_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Melony_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_MELONY, Nexus_Text_Melony_Articuno_ChampionIntro, Nexus_Text_Melony_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Melony_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Melony_Glastrier_ChampionFight::
	nexus_fight TRAINER_NEXUS_MELONY, Nexus_Text_Melony_Glastrier_ChampionIntro, Nexus_Text_Melony_Glastrier_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Melony_Glastrier_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Molly_Entei_ChampionFight::
	nexus_fight TRAINER_NEXUS_MOLLY, Nexus_Text_Molly_Entei_ChampionIntro, Nexus_Text_Molly_Entei_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Molly_Entei_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Molly_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_MOLLY, Nexus_Text_Molly_Xerneas_ChampionIntro, Nexus_Text_Molly_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Molly_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Molly_Cresselia_ChampionFight::
	nexus_fight TRAINER_NEXUS_MOLLY, Nexus_Text_Molly_Cresselia_ChampionIntro, Nexus_Text_Molly_Cresselia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Molly_Cresselia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Mustard_Urshifu_ChampionFight::
	nexus_fight TRAINER_NEXUS_MUSTARD, Nexus_Text_Mustard_Urshifu_ChampionIntro, Nexus_Text_Mustard_Urshifu_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Mustard_Urshifu_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Mustard_Koraidon_ChampionFight::
	nexus_fight TRAINER_NEXUS_MUSTARD, Nexus_Text_Mustard_Koraidon_ChampionIntro, Nexus_Text_Mustard_Koraidon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Mustard_Koraidon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Mustard_Marshadow_ChampionFight::
	nexus_fight TRAINER_NEXUS_MUSTARD, Nexus_Text_Mustard_Marshadow_ChampionIntro, Nexus_Text_Mustard_Marshadow_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Mustard_Marshadow_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_N_Zekrom_ChampionFight::
	nexus_fight TRAINER_NEXUS_N, Nexus_Text_N_Zekrom_ChampionIntro, Nexus_Text_N_Zekrom_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_N_Zekrom_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_N_Reshiram_ChampionFight::
	nexus_fight TRAINER_NEXUS_N, Nexus_Text_N_Reshiram_ChampionIntro, Nexus_Text_N_Reshiram_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_N_Reshiram_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_N_Silvally_ChampionFight::
	nexus_fight TRAINER_NEXUS_N, Nexus_Text_N_Silvally_ChampionIntro, Nexus_Text_N_Silvally_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_N_Silvally_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Nemona_Koraidon_ChampionFight::
	nexus_fight TRAINER_NEXUS_NEMONA, Nexus_Text_Nemona_Koraidon_ChampionIntro, Nexus_Text_Nemona_Koraidon_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Nemona_Koraidon_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Nemona_WalkingWake_ChampionFight::
	nexus_fight TRAINER_NEXUS_NEMONA, Nexus_Text_Nemona_WalkingWake_ChampionIntro, Nexus_Text_Nemona_WalkingWake_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Nemona_WalkingWake_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Nemona_IronValiant_ChampionFight::
	nexus_fight TRAINER_NEXUS_NEMONA, Nexus_Text_Nemona_IronValiant_ChampionIntro, Nexus_Text_Nemona_IronValiant_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Nemona_IronValiant_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Nessa_Kyogre_ChampionFight::
	nexus_fight TRAINER_NEXUS_NESSA, Nexus_Text_Nessa_Kyogre_ChampionIntro, Nexus_Text_Nessa_Kyogre_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Nessa_Kyogre_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Nessa_TapuFini_ChampionFight::
	nexus_fight TRAINER_NEXUS_NESSA, Nexus_Text_Nessa_TapuFini_ChampionIntro, Nexus_Text_Nessa_TapuFini_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Nessa_TapuFini_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Nessa_Suicune_ChampionFight::
	nexus_fight TRAINER_NEXUS_NESSA, Nexus_Text_Nessa_Suicune_ChampionIntro, Nexus_Text_Nessa_Suicune_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Nessa_Suicune_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Olivia_TapuLele_ChampionFight::
	nexus_fight TRAINER_NEXUS_OLIVIA, Nexus_Text_Olivia_TapuLele_ChampionIntro, Nexus_Text_Olivia_TapuLele_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Olivia_TapuLele_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Olivia_Necrozma_ChampionFight::
	nexus_fight TRAINER_NEXUS_OLIVIA, Nexus_Text_Olivia_Necrozma_ChampionIntro, Nexus_Text_Olivia_Necrozma_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Olivia_Necrozma_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Olivia_Diancie_ChampionFight::
	nexus_fight TRAINER_NEXUS_OLIVIA, Nexus_Text_Olivia_Diancie_ChampionIntro, Nexus_Text_Olivia_Diancie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Olivia_Diancie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Peonia_Lugia_ChampionFight::
	nexus_fight TRAINER_NEXUS_PEONIA, Nexus_Text_Peonia_Lugia_ChampionIntro, Nexus_Text_Peonia_Lugia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Peonia_Lugia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Peonia_Suicune_ChampionFight::
	nexus_fight TRAINER_NEXUS_PEONIA, Nexus_Text_Peonia_Suicune_ChampionIntro, Nexus_Text_Peonia_Suicune_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Peonia_Suicune_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Peonia_Articuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_PEONIA, Nexus_Text_Peonia_Articuno_ChampionIntro, Nexus_Text_Peonia_Articuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Peonia_Articuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Peony_Registeel_ChampionFight::
	nexus_fight TRAINER_NEXUS_PEONY, Nexus_Text_Peony_Registeel_ChampionIntro, Nexus_Text_Peony_Registeel_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Peony_Registeel_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Peony_Calyrex_ChampionFight::
	nexus_fight TRAINER_NEXUS_PEONY, Nexus_Text_Peony_Calyrex_ChampionIntro, Nexus_Text_Peony_Calyrex_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Peony_Calyrex_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Peony_Dialga_ChampionFight::
	nexus_fight TRAINER_NEXUS_PEONY, Nexus_Text_Peony_Dialga_ChampionIntro, Nexus_Text_Peony_Dialga_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Peony_Dialga_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Rowan_Dialga_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROWAN, Nexus_Text_Rowan_Dialga_ChampionIntro, Nexus_Text_Rowan_Dialga_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Rowan_Dialga_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Rowan_Uxie_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROWAN, Nexus_Text_Rowan_Uxie_ChampionIntro, Nexus_Text_Rowan_Uxie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Rowan_Uxie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Rowan_Silvally_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROWAN, Nexus_Text_Rowan_Silvally_ChampionIntro, Nexus_Text_Rowan_Silvally_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Rowan_Silvally_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Rosa_Reshiram_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROSA, Nexus_Text_Rosa_Reshiram_ChampionIntro, Nexus_Text_Rosa_Reshiram_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Rosa_Reshiram_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Rosa_Virizion_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROSA, Nexus_Text_Rosa_Virizion_ChampionIntro, Nexus_Text_Rosa_Virizion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Rosa_Virizion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Rosa_Meloetta_ChampionFight::
	nexus_fight TRAINER_NEXUS_ROSA, Nexus_Text_Rosa_Meloetta_ChampionIntro, Nexus_Text_Rosa_Meloetta_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Rosa_Meloetta_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Serena_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_SERENA, Nexus_Text_Serena_Xerneas_ChampionIntro, Nexus_Text_Serena_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Serena_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Serena_Diancie_ChampionFight::
	nexus_fight TRAINER_NEXUS_SERENA, Nexus_Text_Serena_Diancie_ChampionIntro, Nexus_Text_Serena_Diancie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Serena_Diancie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Serena_Latias_ChampionFight::
	nexus_fight TRAINER_NEXUS_SERENA, Nexus_Text_Serena_Latias_ChampionIntro, Nexus_Text_Serena_Latias_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Serena_Latias_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Shelly_Manaphy_ChampionFight::
	nexus_fight TRAINER_NEXUS_SHELLY, Nexus_Text_Shelly_Manaphy_ChampionIntro, Nexus_Text_Shelly_Manaphy_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Shelly_Manaphy_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Shelly_Kyogre_ChampionFight::
	nexus_fight TRAINER_NEXUS_SHELLY, Nexus_Text_Shelly_Kyogre_ChampionIntro, Nexus_Text_Shelly_Kyogre_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Shelly_Kyogre_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Shelly_Volcanion_ChampionFight::
	nexus_fight TRAINER_NEXUS_SHELLY, Nexus_Text_Shelly_Volcanion_ChampionIntro, Nexus_Text_Shelly_Volcanion_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Shelly_Volcanion_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Skyla_Tornadus_ChampionFight::
	nexus_fight TRAINER_NEXUS_SKYLA, Nexus_Text_Skyla_Tornadus_ChampionIntro, Nexus_Text_Skyla_Tornadus_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Skyla_Tornadus_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Skyla_Lugia_ChampionFight::
	nexus_fight TRAINER_NEXUS_SKYLA, Nexus_Text_Skyla_Lugia_ChampionIntro, Nexus_Text_Skyla_Lugia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Skyla_Lugia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Skyla_Celesteela_ChampionFight::
	nexus_fight TRAINER_NEXUS_SKYLA, Nexus_Text_Skyla_Celesteela_ChampionIntro, Nexus_Text_Skyla_Celesteela_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Skyla_Celesteela_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Tulip_Lunala_ChampionFight::
	nexus_fight TRAINER_NEXUS_TULIP, Nexus_Text_Tulip_Lunala_ChampionIntro, Nexus_Text_Tulip_Lunala_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Tulip_Lunala_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Tulip_Cresselia_ChampionFight::
	nexus_fight TRAINER_NEXUS_TULIP, Nexus_Text_Tulip_Cresselia_ChampionIntro, Nexus_Text_Tulip_Cresselia_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Tulip_Cresselia_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Tulip_GalarianArticuno_ChampionFight::
	nexus_fight TRAINER_NEXUS_TULIP, Nexus_Text_Tulip_GalarianArticuno_ChampionIntro, Nexus_Text_Tulip_GalarianArticuno_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Tulip_GalarianArticuno_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Valerie_Xerneas_ChampionFight::
	nexus_fight TRAINER_NEXUS_VALERIE, Nexus_Text_Valerie_Xerneas_ChampionIntro, Nexus_Text_Valerie_Xerneas_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Valerie_Xerneas_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Valerie_Diancie_ChampionFight::
	nexus_fight TRAINER_NEXUS_VALERIE, Nexus_Text_Valerie_Diancie_ChampionIntro, Nexus_Text_Valerie_Diancie_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Valerie_Diancie_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Valerie_Pheromosa_ChampionFight::
	nexus_fight TRAINER_NEXUS_VALERIE, Nexus_Text_Valerie_Pheromosa_ChampionIntro, Nexus_Text_Valerie_Pheromosa_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Valerie_Pheromosa_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Viola_Genesect_ChampionFight::
	nexus_fight TRAINER_NEXUS_VIOLA, Nexus_Text_Viola_Genesect_ChampionIntro, Nexus_Text_Viola_Genesect_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Viola_Genesect_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Viola_Buzzwole_ChampionFight::
	nexus_fight TRAINER_NEXUS_VIOLA, Nexus_Text_Viola_Buzzwole_ChampionIntro, Nexus_Text_Viola_Buzzwole_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Viola_Buzzwole_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Viola_Kartana_ChampionFight::
	nexus_fight TRAINER_NEXUS_VIOLA, Nexus_Text_Viola_Kartana_ChampionIntro, Nexus_Text_Viola_Kartana_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Viola_Kartana_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Zinnia_Rayquaza_ChampionFight::
	nexus_fight TRAINER_NEXUS_ZINNIA, Nexus_Text_Zinnia_Rayquaza_ChampionIntro, Nexus_Text_Zinnia_Rayquaza_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Zinnia_Rayquaza_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Zinnia_Jirachi_ChampionFight::
	nexus_fight TRAINER_NEXUS_ZINNIA, Nexus_Text_Zinnia_Jirachi_ChampionIntro, Nexus_Text_Zinnia_Jirachi_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Zinnia_Jirachi_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Zinnia_Deoxys_ChampionFight::
	nexus_fight TRAINER_NEXUS_ZINNIA, Nexus_Text_Zinnia_Deoxys_ChampionIntro, Nexus_Text_Zinnia_Deoxys_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Zinnia_Deoxys_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_EventScript_Lillie_Solgaleo_ChampionFight::
	nexus_fight TRAINER_NEXUS_LILLIE, Nexus_Text_Lillie_Solgaleo_ChampionIntro, Nexus_Text_Lillie_Solgaleo_ChampionDefeat
	goto_if_ne VAR_TEMP_3, B_OUTCOME_WON, Nexus_EventScript_Return
	msgbox Nexus_Text_Lillie_Solgaleo_ChampionAfter, MSGBOX_DEFAULT
	closemessage
	return

Nexus_Text_Colress_Genesect_ChampionIntro:
	.string "Someone improved an ancient hunter by\n"
	.string "attaching a weapon. They recorded the\l"
	.string "weapon's output.\p"
	.string "I wonder whether anyone recorded what\n"
	.string "the hunter wanted. Shall we test a\l"
	.string "less obvious variable?$"

Nexus_Text_Colress_Genesect_ChampionDefeat:
	.string "Excellent. Your partners responded\n"
	.string "before your orders were complete.$"

Nexus_Text_Colress_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_COLRESS}The cannon is easy to understand. A\n"
	.string "choice is much harder to measure.\p"
	.string "If something small survives that\n"
	.string "ancient design, let it surprise you.\l"
	.string "An experiment that only confirms its\l"
	.string "maker is a poor experiment.$"

Nexus_Text_Colress_Silvally_ChampionIntro:
	.string "Its restraints were intended to\n"
	.string "suppress a failure. Breaking them\l"
	.string "revealed something its designers had\l"
	.string "failed to measure.\p"
	.string "Trust. An inconveniently personal\n"
	.string "condition. Let me see how yours\l"
	.string "behaves under pressure.$"

Nexus_Text_Colress_Silvally_ChampionDefeat:
	.string "Remarkable. No restraints, and such\n"
	.string "coordination.$"

Nexus_Text_Colress_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_COLRESS}A machine can enforce a command. It\n"
	.string "cannot make that command welcome.\p"
	.string "The small beginning beyond the broken\n"
	.string "mask deserves better questions than\l"
	.string "its makers asked. I should like to\l"
	.string "hear its answers someday.$"

Nexus_Text_Bruno_Urshifu_ChampionIntro:
	.string "One blow. No second chance hidden\n"
	.string "behind the first.\p"
	.string "I have practiced the same stance for\n"
	.string "years. That creature makes me wonder\l"
	.string "whether I have ever truly finished one\l"
	.string "movement. Stand ready!$"

Nexus_Text_Bruno_Urshifu_ChampionDefeat:
	.string "You committed to your strike. I felt\n"
	.string "no hesitation.$"

Nexus_Text_Bruno_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_BRUNO}Do not mistake a single blow for an\n"
	.string "easy lesson. All the training comes\l"
	.string "before it.\p"
	.string "Whatever small beginning remains,\n"
	.string "teach it patience before strength. A\l"
	.string "fist that cannot wait has already lost\l"
	.string "its balance.$"

Nexus_Text_Bruno_Terrakion_ChampionIntro:
	.string "That one broke a wall to reach those\n"
	.string "trapped behind it.\p"
	.string "Strength has weight only when it\n"
	.string "carries someone else. My shoulders are\l"
	.string "ready. Let us test yours!$"

Nexus_Text_Bruno_Terrakion_ChampionDefeat:
	.string "Solid. You did not abandon anyone\n"
	.string "behind your guard.$"

Nexus_Text_Bruno_Terrakion_ChampionAfter:
	.string "{SPEAKER NAME_BRUNO}I used to measure progress by the\n"
	.string "stones I could break. Here, the broken\l"
	.string "stones remember the ones they\l"
	.string "sheltered.\p"
	.string "Train the little life that remains to\n"
	.string "stand beside others. There are enough\l"
	.string "empty walls.$"

Nexus_Text_Elesa_Zeraora_ChampionIntro:
	.string "It crosses the air on sparks and never\n"
	.string "waits for applause.\p"
	.string "I tried following its entrance. My\n"
	.string "shadow arrived before I did. That's a\l"
	.string "difficult act to follow! Ready for the\l"
	.string "next flash?$"

Nexus_Text_Elesa_Zeraora_ChampionDefeat:
	.string "You stole the spotlight. At exactly\n"
	.string "the right moment.$"

Nexus_Text_Elesa_Zeraora_ChampionAfter:
	.string "{SPEAKER NAME_ELESA}Every model learns where to place a\n"
	.string "foot. That one finds a foothold in\l"
	.string "lightning.\p"
	.string "If a little spark comes home with you,\n"
	.string "give it somewhere to land. Even a\l"
	.string "brilliant entrance needs a place after\l"
	.string "the show.$"

Nexus_Text_Elesa_Meloetta_ChampionIntro:
	.string "The melody changes, and suddenly the\n"
	.string "whole body answers differently.\p"
	.string "I've worn outfits that changed how\n"
	.string "people saw me. Imagine a song that\l"
	.string "changes how you move. Let's see your\l"
	.string "interpretation!$"

Nexus_Text_Elesa_Meloetta_ChampionDefeat:
	.string "A lovely finish. Even the silence kept\n"
	.string "your rhythm.$"

Nexus_Text_Elesa_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_ELESA}There is a note hanging here that my\n"
	.string "world has forgotten. It seems to\l"
	.string "remember every dancer who heard it.\p"
	.string "Don't make the small voice left behind\n"
	.string "repeat one performance forever. Let it\l"
	.string "find a new song.$"

Nexus_Text_Volkner_Regieleki_ChampionIntro:
	.string "Those bands hold back enough\n"
	.string "electricity to make a city's lights\l"
	.string "look tired.\p"
	.string "I came here hoping something would\n"
	.string "wake me up. Even my tools won't stop\l"
	.string "trembling. Think you can do better?$"

Nexus_Text_Volkner_Regieleki_ChampionDefeat:
	.string "Yeah. That got my attention before the\n"
	.string "thunder did.$"

Nexus_Text_Volkner_Regieleki_ChampionAfter:
	.string "{SPEAKER NAME_VOLKNER}I used to add another circuit whenever\n"
	.string "the old one bored me. That thing is\l"
	.string "what happens when the circuit is the\l"
	.string "only thing saying enough.\p"
	.string "Give its small spark a purpose. More\n"
	.string "voltage isn't one.$"

Nexus_Text_Volkner_Zekrom_ChampionIntro:
	.string "Its tail turns conviction into\n"
	.string "thunder. No switch. No fuel I can\l"
	.string "measure.\p"
	.string "I used to think finding a worthy\n"
	.string "opponent would give me something to\l"
	.string "believe in. Let's try that theory.$"

Nexus_Text_Volkner_Zekrom_ChampionDefeat:
	.string "Good. I remembered why I built a\n"
	.string "battlefield.$"

Nexus_Text_Volkner_Zekrom_ChampionAfter:
	.string "{SPEAKER NAME_VOLKNER}A generator needs something to turn\n"
	.string "it. That dragon needs an ideal. I\l"
	.string "wonder which of us has the harder job.\p"
	.string "If it leaves you a beginning, find out\n"
	.string "what moves it. Don't just wire it to\l"
	.string "your ambitions.$"

Nexus_Text_Steven_Diancie_ChampionIntro:
	.string "A gem usually keeps its history hidden\n"
	.string "inside. This one walks out to meet\l"
	.string "you.\p"
	.string "The stones around us remember a\n"
	.string "pressure that hasn't happened yet. I\l"
	.string "should like to examine your resolve\l"
	.string "just as closely.$"

Nexus_Text_Steven_Diancie_ChampionDefeat:
	.string "A fine result. Pressure revealed a\n"
	.string "great deal.$"

Nexus_Text_Steven_Diancie_ChampionAfter:
	.string "{SPEAKER NAME_STEVEN}I collect stones because no two hold\n"
	.string "quite the same past. A living jewel\l"
	.string "should be allowed a future as well.\p"
	.string "What remains after that brilliance\n"
	.string "will be very young. Please resist the\l"
	.string "temptation to put it in a display\l"
	.string "case.$"

Nexus_Text_Steven_Registeel_ChampionIntro:
	.string "My hammer leaves no mark on that\n"
	.string "metal. Neither does the memory of my\l"
	.string "hammer, which seems to arrive first\l"
	.string "here.\p"
	.string "A collector must know when to stop\n"
	.string "testing a specimen. A Trainer,\l"
	.string "however, may ask politely.$"

Nexus_Text_Steven_Registeel_ChampionDefeat:
	.string "You found an opening without needing\n"
	.string "to break it.$"

Nexus_Text_Steven_Registeel_ChampionAfter:
	.string "{SPEAKER NAME_STEVEN}We tend to call a material perfect\n"
	.string "when we cannot change it. That tells\l"
	.string "us little about what lives inside.\p"
	.string "Treat the small remainder as a\n"
	.string "companion, even if its shell refuses\l"
	.string "every tool you own.$"

Nexus_Text_Ramos_WoChien_ChampionIntro:
	.string "Old grievances have taken root in\n"
	.string "those wooden slips. The grass wilts\l"
	.string "just listening.\p"
	.string "A gardener knows neglect can outlast\n"
	.string "the hands that caused it. Come,\l"
	.string "sprout. Show me something worth\l"
	.string "tending.$"

Nexus_Text_Ramos_WoChien_ChampionDefeat:
	.string "Good roots. You held even in that\n"
	.string "bitter soil.$"

Nexus_Text_Ramos_WoChien_ChampionAfter:
	.string "{SPEAKER NAME_RAMOS}Don't tear up a whole garden because\n"
	.string "one corner has gone sour. Work the\l"
	.string "soil, a little each day.\p"
	.string "If a small life comes out of that old\n"
	.string "bitterness, give it a patch where\l"
	.string "nothing is owed.$"

Nexus_Text_Ramos_Shaymin_ChampionIntro:
	.string "Well now. The little flowers are\n"
	.string "returning before the ash has finished\l"
	.string "falling.\p"
	.string "I've planted in poor soil, but never\n"
	.string "in tomorrow's ruins. Let's see if your\l"
	.string "care is as sturdy as those shoots.$"

Nexus_Text_Ramos_Shaymin_ChampionDefeat:
	.string "Hoho! Something good will grow from\n"
	.string "that effort.$"

Nexus_Text_Ramos_Shaymin_ChampionAfter:
	.string "{SPEAKER NAME_RAMOS}Gratitude isn't a payment you collect\n"
	.string "after tending a garden. Sometimes it's\l"
	.string "simply the first green thing that\l"
	.string "returns.\p"
	.string "Give the small one room to wander. A\n"
	.string "flower that visits another garden\l"
	.string "hasn't deserted yours.$"

Nexus_Text_Guzma_Buzzwole_ChampionIntro:
	.string "Look at it flex. Doesn't even check\n"
	.string "whether anyone's watching.\p"
	.string "Back home, everybody wanted me to\n"
	.string "stand a certain way. That thing makes\l"
	.string "the whole sky its stupid victory pose.\l"
	.string "Let's knock something over!$"

Nexus_Text_Guzma_Buzzwole_ChampionDefeat:
	.string "Tch. You can stand tall without\n"
	.string "showing off. Annoying.$"

Nexus_Text_Guzma_Buzzwole_ChampionAfter:
	.string "{SPEAKER NAME_GUZMA}Maybe it ain't trying to impress\n"
	.string "anybody. Maybe that's just how it\l"
	.string "likes standing.\p"
	.string "If a little version comes out of this\n"
	.string "mess, don't spend its whole life\l"
	.string "telling it to look smaller. Had enough\l"
	.string "of that myself.$"

Nexus_Text_Guzma_Okidogi_ChampionIntro:
	.string "One chain, a whole lot of muscle, and\n"
	.string "a face daring you to laugh.\p"
	.string "I know what it's like to get strong\n"
	.string "because you're sick of being shoved\l"
	.string "around. Doesn't mean you get to shove\l"
	.string "everyone else!$"

Nexus_Text_Guzma_Okidogi_ChampionDefeat:
	.string "Yeah, yeah. You put me down fair.$"

Nexus_Text_Guzma_Okidogi_ChampionAfter:
	.string "{SPEAKER NAME_GUZMA}That chain looks like proof it finally\n"
	.string "matters. Funny how proof can turn into\l"
	.string "a leash.\p"
	.string "Whatever it leaves behind, don't make\n"
	.string "strength the price of a place on your\l"
	.string "team. Let the little punk belong\l"
	.string "first.$"

Nexus_Text_Soliera_Necrozma_ChampionIntro:
	.string "My instruments report light where my\n"
	.string "eyes report none. The readings carry\l"
	.string "tomorrow's date.\p"
	.string "In my world, darkness became an order\n"
	.string "we followed without question. I will\l"
	.string "not repeat that error. Demonstrate\l"
	.string "your readiness.$"

Nexus_Text_Soliera_Necrozma_ChampionDefeat:
	.string "Assessment complete. You can act\n"
	.string "without surrendering judgment.$"

Nexus_Text_Soliera_Necrozma_ChampionAfter:
	.string "{SPEAKER NAME_SOLIERA}The hunger beyond us is older than any\n"
	.string "order I received. Obedience will not\l"
	.string "satisfy it.\p"
	.string "If its struggle leaves a small\n"
	.string "beginning, protect that life. We were\l"
	.string "sent to recover light. We must learn\l"
	.string "to care for what bears it.$"

Nexus_Text_Soliera_Nihilego_ChampionIntro:
	.string "The transparent body is not evidence\n"
	.string "of harmlessness. I have seen a patrol\l"
	.string "follow its own gestures as though\l"
	.string "receiving orders.\p"
	.string "Here, the order arrived without a\n"
	.string "sender. Show me that your decisions\l"
	.string "remain yours.$"

Nexus_Text_Soliera_Nihilego_ChampionDefeat:
	.string "You maintained independent judgment.\n"
	.string "That was the necessary test.$"

Nexus_Text_Soliera_Nihilego_ChampionAfter:
	.string "{SPEAKER NAME_SOLIERA}My report cannot distinguish intention\n"
	.string "from instinct. I will not invent\l"
	.string "malice to make the uncertainty easier.\p"
	.string "If a small life remains, learn its\n"
	.string "limits carefully. Protecting it and\l"
	.string "protecting those around it are the\l"
	.string "same assignment.$"

Nexus_Text_Byron_Registeel_ChampionIntro:
	.string "Now there's metal worth sweating over!\n"
	.string "No seam, no rivet, and no mark from\l"
	.string "the years.\p"
	.string "My shovel rang against it yesterday. I\n"
	.string "can still hear the blow waiting to\l"
	.string "land. Let's make some honest noise!$"

Nexus_Text_Byron_Registeel_ChampionDefeat:
	.string "Hah! You found the weak point in my\n"
	.string "work!$"

Nexus_Text_Byron_Registeel_ChampionAfter:
	.string "{SPEAKER NAME_BYRON}A miner learns the difference between\n"
	.string "a wall and a thing that wants its door\l"
	.string "left shut.\p"
	.string "That old iron owes us no ore. If a\n"
	.string "small life remains, let it choose what\l"
	.string "it opens for you.$"

Nexus_Text_Byron_Melmetal_ChampionIntro:
	.string "Every little bit of metal seems to\n"
	.string "know where the others belong. Mine\l"
	.string "never puts itself back so neatly!\p"
	.string "This tunnel remembers the whole giant\n"
	.string "before the first piece arrives. Let's\l"
	.string "see how well your team fits together!$"

Nexus_Text_Byron_Melmetal_ChampionDefeat:
	.string "Strong joints! Nothing came loose when\n"
	.string "the pressure rose.$"

Nexus_Text_Byron_Melmetal_ChampionAfter:
	.string "{SPEAKER NAME_BYRON}Steel gets its strength from what\n"
	.string "joins it. Teams do, too.\p"
	.string "The little piece that remains won't\n"
	.string "look like much beside that giant.\l"
	.string "Don't discard it. I've built a career\l"
	.string "out of seeing what one small piece can\p"
	.string "become.$"

Nexus_Text_Fantina_Meloetta_ChampionIntro:
	.string "Ah! A song without a singer, and then\n"
	.string "a singer where the song has always\l"
	.string "been.\p"
	.string "My feet began the dance before I heard\n"
	.string "it. Such an invitation cannot be\l"
	.string "refused. Allez!$"

Nexus_Text_Fantina_Meloetta_ChampionDefeat:
	.string "Magnifique! You found a step I had\n"
	.string "forgotten!$"

Nexus_Text_Fantina_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_FANTINA}A dance belongs to the body performing\n"
	.string "it. Even an ancient melody must allow\l"
	.string "a new step.\p"
	.string "If a small voice remains, listen\n"
	.string "before you teach. Perhaps it has been\l"
	.string "waiting for an audience that will\l"
	.string "answer.$"

Nexus_Text_Fantina_Marshadow_ChampionIntro:
	.string "There is an extra dancer in my shadow.\n"
	.string "It learns every step and never takes a\l"
	.string "bow.\p"
	.string "Shall we offer it something worth\n"
	.string "remembering? I promise a most spirited\l"
	.string "performance!$"

Nexus_Text_Fantina_Marshadow_ChampionDefeat:
	.string "Ah! Even my shadow applauds you!$"

Nexus_Text_Fantina_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_FANTINA}I once spent months copying a dancer I\n"
	.string "admired. The first step that felt like\l"
	.string "mine was a mistake.\p"
	.string "Give the little shadow permission to\n"
	.string "miss a beat. It deserves a dance that\l"
	.string "belongs to it.$"

Nexus_Text_Red_Mewtwo_ChampionIntro:
	.string "...Made to win.\p"
	.string "...Still alone.\p"
	.string "...I know that part.\p"
	.string "...!$"

Nexus_Text_Red_Mewtwo_ChampionDefeat:
	.string "...Winning isn't everything.$"

Nexus_Text_Red_Mewtwo_ChampionAfter:
	.string "{SPEAKER NAME_RED}...The summit was quiet.\p"
	.string "...So is that cave.\p"
	.string "...If something small stays behind...\n"
	.string "stay with it.\p"
	.string "...Go.$"

Nexus_Text_Red_Zapdos_ChampionIntro:
	.string "...A flash.\p"
	.string "...The same one. Every night.\p"
	.string "...The storm can't finish.\p"
	.string "...!$"

Nexus_Text_Red_Zapdos_ChampionDefeat:
	.string "...You kept moving.$"

Nexus_Text_Red_Zapdos_ChampionAfter:
	.string "{SPEAKER NAME_RED}...I waited out storms on the\n"
	.string "mountain.\p"
	.string "...This one has forgotten morning.\p"
	.string "...Take care of the small spark.\p"
	.string "...Let it see a clear sky.$"

Nexus_Text_Blue_Zekrom_ChampionIntro:
	.string "A dragon that chooses someone with an\n"
	.string "ideal? Finally, a selection process\l"
	.string "with standards!\p"
	.string "Though the thunder here keeps\n"
	.string "answering questions I haven't asked.\l"
	.string "Beat me first. Then see what it thinks\l"
	.string "of your big plans.$"

Nexus_Text_Blue_Zekrom_ChampionDefeat:
	.string "All right. Your team believed you.\n"
	.string "Mine heard me bragging.$"

Nexus_Text_Blue_Zekrom_ChampionAfter:
	.string "{SPEAKER NAME_BLUE}I spent a long time calling being\n"
	.string "first a dream. Hard to build anything\l"
	.string "on that once someone passes you.\p"
	.string "If a little thunder follows you home,\n"
	.string "give it a reason to stay after the\l"
	.string "winning stops.$"

Nexus_Text_Brock_Regirock_ChampionIntro:
	.string "Look at those stones. Different ages,\n"
	.string "fitted into one body.\p"
	.string "The dust falls upward when it moves.\n"
	.string "Even here, it keeps rebuilding a solid\l"
	.string "place to stand. Show me how strong\l"
	.string "your foundation is!$"

Nexus_Text_Brock_Regirock_ChampionDefeat:
	.string "You held together. Every part\n"
	.string "supported the next.$"

Nexus_Text_Brock_Regirock_ChampionAfter:
	.string "{SPEAKER NAME_BROCK}A body of stone still needs care. The\n"
	.string "pieces that fit today may need\l"
	.string "replacing tomorrow.\p"
	.string "If a small beginning is left, help it\n"
	.string "find good stones. Being dependable\l"
	.string "doesn't mean never needing a hand.$"

Nexus_Text_Misty_Suicune_ChampionIntro:
	.string "That wind smells like rain on clean\n"
	.string "water. The river here has forgotten\l"
	.string "which way to run, but it clears\l"
	.string "wherever those paws touch.\p"
	.string "Let's see whether your battling can\n"
	.string "keep up with that current!$"

Nexus_Text_Misty_Suicune_ChampionDefeat:
	.string "You didn't waste a stroke. I like\n"
	.string "that!$"

Nexus_Text_Misty_Suicune_ChampionAfter:
	.string "{SPEAKER NAME_MISTY}I keep thinking I could follow it all\n"
	.string "the way to the sea. Here, the sea\l"
	.string "might come first.\p"
	.string "If something small is left, keep its\n"
	.string "water clean. Even a miracle deserves\l"
	.string "someone doing the ordinary work.$"

Nexus_Text_Erika_TapuBulu_ChampionIntro:
	.string "The roots have risen through a floor\n"
	.string "that remembers being a meadow. I\l"
	.string "believe the guardian remembers, too.\p"
	.string "Please tread gently. We may battle\n"
	.string "firmly without disturbing every\l"
	.string "flower.$"

Nexus_Text_Erika_TapuBulu_ChampionDefeat:
	.string "Such care, even in your final move.\n"
	.string "Thank you.$"

Nexus_Text_Erika_TapuBulu_ChampionAfter:
	.string "{SPEAKER NAME_ERIKA}There is a bell inside that great\n"
	.string "shell. The ground grows quiet to hear\l"
	.string "it.\p"
	.string "A garden can reclaim a city, yet still\n"
	.string "have room for a visitor. Teach the\l"
	.string "little life that remains which paths\l"
	.string "to leave open.$"

Nexus_Text_Koga_Munkidori_ChampionIntro:
	.string "A clever poison needs no blade. It\n"
	.string "changes the thought that would have\l"
	.string "raised your guard.\p"
	.string "Here, I found myself thanking it\n"
	.string "before we met. Clear your mind. We\l"
	.string "shall test what remains your own.$"

Nexus_Text_Koga_Munkidori_ChampionDefeat:
	.string "Good. You questioned the easy opening.$"

Nexus_Text_Koga_Munkidori_ChampionAfter:
	.string "{SPEAKER NAME_KOGA}An enemy who enters your thoughts may\n"
	.string "offer the very thing you wished to\l"
	.string "hear.\p"
	.string "If a small beginning remains, teach it\n"
	.string "honesty before cleverness. A ninja can\l"
	.string "live behind a mask without making\l"
	.string "every kindness a trap.$"

Nexus_Text_Koga_Okidogi_ChampionIntro:
	.string "That chain offers strength, but watch\n"
	.string "the neck beneath it. A weapon can\l"
	.string "choose its wielder's movements.\p"
	.string "A ninja inspects every gift. Let us\n"
	.string "see how carefully you inspect an\l"
	.string "opponent.$"

Nexus_Text_Koga_Okidogi_ChampionDefeat:
	.string "You saw the pull before the blow.\n"
	.string "Excellent.$"

Nexus_Text_Koga_Okidogi_ChampionAfter:
	.string "{SPEAKER NAME_KOGA}My daughter learned to leap beyond the\n"
	.string "places I taught her to hide. I am\l"
	.string "proud of that.\p"
	.string "Give the small life beyond that chain\n"
	.string "the same chance. Training should widen\l"
	.string "a future, never fasten it shut.$"

Nexus_Text_Sabrina_Uxie_ChampionIntro:
	.string "There is a thought missing from this\n"
	.string "room. I can feel the space it leaves.\p"
	.string "That creature keeps its eyes closed,\n"
	.string "and for once I cannot see what happens\l"
	.string "next. We will have to discover it\l"
	.string "together.$"

Nexus_Text_Sabrina_Uxie_ChampionDefeat:
	.string "An outcome I did not foresee. I\n"
	.string "welcome it.$"

Nexus_Text_Sabrina_Uxie_ChampionAfter:
	.string "{SPEAKER NAME_SABRINA}Knowing what will happen can become an\n"
	.string "excuse never to choose. Forgetting is\l"
	.string "no kinder.\p"
	.string "If a little life remains beside that\n"
	.string "empty thought, give it time. It need\l"
	.string "not surrender its secrets to deserve\l"
	.string "your care.$"

Nexus_Text_Blaine_GougingFire_ChampionIntro:
	.string "Quiz time! How old is a flame if it\n"
	.string "burns before the fuel exists?\p"
	.string "That crowned beast keeps bringing\n"
	.string "sunrise to a sky that hasn't had a\l"
	.string "night. Hah! Let's see whether you can\l"
	.string "take the heat!$"

Nexus_Text_Blaine_GougingFire_ChampionDefeat:
	.string "Correct! You kept your head when the\n"
	.string "temperature rose!$"

Nexus_Text_Blaine_GougingFire_ChampionAfter:
	.string "{SPEAKER NAME_BLAINE}I lost an island to fire. That does\n"
	.string "not make every flame my enemy.\p"
	.string "Whatever small ember survives that\n"
	.string "ancient furnace, raise it with care.\l"
	.string "Knowing when to lower the heat is part\l"
	.string "of being a Fire Trainer.$"

Nexus_Text_Giovanni_Landorus_ChampionIntro:
	.string "Land is a useful investment. That\n"
	.string "creature makes it fertile with a\l"
	.string "passing gesture.\p"
	.string "Yet none of my maps agree on where its\n"
	.string "fields end. An empire requires\l"
	.string "boundaries. Show me whether yours can\l"
	.string "hold.$"

Nexus_Text_Giovanni_Landorus_ChampionDefeat:
	.string "Hm. You yielded ground without\n"
	.string "surrendering it.$"

Nexus_Text_Giovanni_Landorus_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}I once treated every patch of earth as\n"
	.string "territory waiting for an owner. That\l"
	.string "field grows perfectly well without\l"
	.string "one.\p"
	.string "If a small beginning remains, remember\n"
	.string "who does the growing. A deed has never\l"
	.string "taught a seed anything.$"

Nexus_Text_Lance_Zygarde_ChampionIntro:
	.string "There are eyes in every fallen leaf,\n"
	.string "and they all turn toward the same\l"
	.string "wound in the ground.\p"
	.string "A dragon's strength can be the\n"
	.string "strength of many lives agreeing. Show\l"
	.string "me what your partners have agreed to\l"
	.string "defend!$"

Nexus_Text_Lance_Zygarde_ChampionDefeat:
	.string "Your team answered together. That is a\n"
	.string "worthy strength.$"

Nexus_Text_Lance_Zygarde_ChampionAfter:
	.string "{SPEAKER NAME_LANCE}I have flown over cities that looked\n"
	.string "peaceful from above. Down in the\l"
	.string "streets, the story was different.\p"
	.string "Care for the small part left behind.\n"
	.string "Balance begins with noticing a life\l"
	.string "that others would overlook.$"

Nexus_Text_Archer_Zamazenta_ChampionIntro:
	.string "A shield that remembers a king no one\n"
	.string "here can name. I understand keeping a\l"
	.string "place for an absent leader.\p"
	.string "The difference is that it still\n"
	.string "protects someone. Let us see whom your\l"
	.string "loyalty serves.$"

Nexus_Text_Archer_Zamazenta_ChampionDefeat:
	.string "You protected your partners. Your\n"
	.string "purpose was clear.$"

Nexus_Text_Archer_Zamazenta_ChampionAfter:
	.string "{SPEAKER NAME_ARCHER}I waited for a voice on the radio\n"
	.string "while other people needed orders. The\l"
	.string "shield did not wait.\p"
	.string "If a small guardian remains, give it\n"
	.string "people to stand beside. Waiting alone\l"
	.string "should never become its duty.$"

Nexus_Text_Ariana_Fezandipiti_ChampionIntro:
	.string "One drift of those feathers, and\n"
	.string "suspicion becomes admiration. Very\l"
	.string "efficient.\p"
	.string "I have watched soldiers salute an\n"
	.string "empty patch of sky here. Let us find\l"
	.string "out whether you can resist a more\l"
	.string "direct influence.$"

Nexus_Text_Ariana_Fezandipiti_ChampionDefeat:
	.string "You kept your judgment. That makes you\n"
	.string "troublesome.$"

Nexus_Text_Ariana_Fezandipiti_ChampionAfter:
	.string "{SPEAKER NAME_ARIANA}Beauty can deliver an instruction\n"
	.string "before anyone notices they have\l"
	.string "obeyed. I appreciate the mechanism.\p"
	.string "Still, the little life left behind\n"
	.string "will need more than admiration. Teach\l"
	.string "it to accept an answer it did not\l"
	.string "arrange.$"

Nexus_Text_Ariana_Enamorus_ChampionIntro:
	.string "Every heart-shaped cloud promises a\n"
	.string "gentle spring. The field beneath one\l"
	.string "is already drowning in vines.\p"
	.string "Excess can be a useful weapon. I would\n"
	.string "like to see how you handle it.$"

Nexus_Text_Ariana_Enamorus_ChampionDefeat:
	.string "You knew when to stop committing\n"
	.string "resources. Sensible.$"

Nexus_Text_Ariana_Enamorus_ChampionAfter:
	.string "{SPEAKER NAME_ARIANA}I have ordered growth before its time.\n"
	.string "The results were impressive. They were\l"
	.string "not gentle.\p"
	.string "Whatever remains of that spring, give\n"
	.string "it seasons. A thing should not have to\l"
	.string "bloom whenever someone else demands\l"
	.string "it.$"

Nexus_Text_Proton_ChiYu_ChampionIntro:
	.string "Tiny thing, huge appetite. Whole rooms\n"
	.string "melt while those beads keep smiling.\p"
	.string "I used to think a fortune should fit\n"
	.string "in your pocket. This one would burn\l"
	.string "straight through! Come on, try your\l"
	.string "luck!$"

Nexus_Text_Proton_ChiYu_ChampionDefeat:
	.string "Tch! You didn't reach for the bait.$"

Nexus_Text_Proton_ChiYu_ChampionAfter:
	.string "{SPEAKER NAME_PROTON}All that old envy, squeezed into a\n"
	.string "pair of jewels. Can't spend it. Can't\l"
	.string "even hold it.\p"
	.string "If a little spark is left, feed it\n"
	.string "something besides wanting what belongs\l"
	.string "to somebody else. Sounds expensive\l"
	.string "enough already.$"

Nexus_Text_Petrel_Fezandipiti_ChampionIntro:
	.string "Beautiful entrance, irresistible\n"
	.string "voice, and everyone looking exactly\l"
	.string "where it wants. A professional!\p"
	.string "I practiced its smile. The mirror\n"
	.string "applauded before I started. Let's see\l"
	.string "if you can spot a less graceful\l"
	.string "impostor!$"

Nexus_Text_Petrel_Fezandipiti_ChampionDefeat:
	.string "Ahahaha! You saw straight through the\n"
	.string "act. Mine, anyway.$"

Nexus_Text_Petrel_Fezandipiti_ChampionAfter:
	.string "{SPEAKER NAME_PETREL}A good disguise lets you enter a room.\n"
	.string "That perfume makes the room grateful\l"
	.string "you arrived. Quite the advantage.\p"
	.string "If a little performer remains, teach\n"
	.string "it a greeting without a trick. Even I\l"
	.string "like being recognized occasionally.$"

Nexus_Text_Silver_Silvally_ChampionIntro:
	.string "Someone built it to obey, then called\n"
	.string "it a failure when the mask didn't\l"
	.string "hold.\p"
	.string "Funny. The broken pieces here keep\n"
	.string "trying to become a mask again. Show me\l"
	.string "you know when to break something.$"

Nexus_Text_Silver_Silvally_ChampionDefeat:
	.string "You trusted them. Didn't need to force\n"
	.string "it.$"

Nexus_Text_Silver_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_SILVER}I used to call anything weak if it\n"
	.string "didn't do what I wanted.\p"
	.string "That little beginning beyond the mask\n"
	.string "isn't a failed weapon. Let it decide\l"
	.string "what it becomes. ...You don't have to\l"
	.string "tell anyone I said that.$"

Nexus_Text_Silver_Darkrai_ChampionIntro:
	.string "It stays away from sleepers. The\n"
	.string "nightmares follow anyway.\p"
	.string "This place dreams about it before it\n"
	.string "arrives. I know what it's like to be\l"
	.string "blamed for the name you carry. Come\l"
	.string "on.$"

Nexus_Text_Silver_Darkrai_ChampionDefeat:
	.string "You didn't flinch at a bad start.$"

Nexus_Text_Silver_Darkrai_ChampionAfter:
	.string "{SPEAKER NAME_SILVER}I don't think it wants company at any\n"
	.string "cost. I wouldn't.\p"
	.string "If a small life comes out of that\n"
	.string "nightmare, give it somewhere safe to\l"
	.string "be alone. Then make sure alone is\l"
	.string "still a choice.$"

Nexus_Text_Falkner_Lugia_ChampionIntro:
	.string "My father taught me to read a bird's\n"
	.string "wings. Those wings are folded, and the\l"
	.string "air is still afraid.\p"
	.string "Here, even the storm seems inherited\n"
	.string "from another sky. Show me how you\l"
	.string "carry what came before you!$"

Nexus_Text_Falkner_Lugia_ChampionDefeat:
	.string "You kept your balance without\n"
	.string "borrowing someone else's wings.$"

Nexus_Text_Falkner_Lugia_ChampionAfter:
	.string "{SPEAKER NAME_FALKNER}A powerful wing does not have to prove\n"
	.string "itself with every stroke. Sometimes\l"
	.string "flying gently takes more skill.\p"
	.string "If a small life remains after that\n"
	.string "storm, let it learn its own pace. My\l"
	.string "father's birds taught me that much.$"

Nexus_Text_Falkner_Articuno_ChampionIntro:
	.string "There is frost on the feather before\n"
	.string "the feather falls. The sky seems to be\l"
	.string "remembering winter.\p"
	.string "My father would have stopped to admire\n"
	.string "it. I'll do that after our battle.\l"
	.string "Ready?$"

Nexus_Text_Falkner_Articuno_ChampionDefeat:
	.string "A clean flight. You earned your place\n"
	.string "in this sky.$"

Nexus_Text_Falkner_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_FALKNER}People admire a beautiful bird and\n"
	.string "forget the harsh air it crosses.\p"
	.string "The little life left behind will still\n"
	.string "need shelter. Respecting its wings\l"
	.string "does not mean expecting it to face\l"
	.string "every storm alone.$"

Nexus_Text_Bugsy_Genesect_ChampionIntro:
	.string "Under the metal, an ancient Bug still\n"
	.string "knows how to hunt. The fossil and the\l"
	.string "machine disagree on its age.\p"
	.string "I'd like to ask what survived between\n"
	.string "them. A battle might give us a clue!$"

Nexus_Text_Bugsy_Genesect_ChampionDefeat:
	.string "You adapted faster than my notes could\n"
	.string "follow!$"

Nexus_Text_Bugsy_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_BUGSY}We call a feature an improvement when\n"
	.string "it helps the job we chose. That tells\l"
	.string "us nothing about the creature's own\l"
	.string "life.\p"
	.string "If a small beginning survives, let it\n"
	.string "be curious. It has been someone's\l"
	.string "project long enough.$"

Nexus_Text_Whitney_Meloetta_ChampionIntro:
	.string "I heard a little song and started\n"
	.string "dancing. Then the song changed, and my\l"
	.string "feet got all tangled!\p"
	.string "The echo here keeps singing the next\n"
	.string "verse first. Let's try a battle I can\l"
	.string "actually follow!$"

Nexus_Text_Whitney_Meloetta_ChampionDefeat:
	.string "Aw! I missed the beat again. You\n"
	.string "didn't!$"

Nexus_Text_Whitney_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_WHITNEY}People expect a cute face to keep\n"
	.string "smiling through every song. That's\l"
	.string "tiring, you know!\p"
	.string "If a little singer comes home with\n"
	.string "you, let it have quiet days. You can\l"
	.string "be wonderful without being cheerful\l"
	.string "all the time.$"

Nexus_Text_Morty_Lunala_ChampionIntro:
	.string "The moon has cast a shadow where no\n"
	.string "moon has risen. Something opens its\l"
	.string "wings inside it.\p"
	.string "In Ecruteak, I waited years for a\n"
	.string "glimpse of a legend. Here, I must\l"
	.string "learn to look without expecting.$"

Nexus_Text_Morty_Lunala_ChampionDefeat:
	.string "You watched the darkness without\n"
	.string "turning away.$"

Nexus_Text_Morty_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_MORTY}Waiting can become a way of refusing\n"
	.string "the life already beside you. I know\l"
	.string "that habit well.\p"
	.string "If a small cloud remains after those\n"
	.string "wings pass, keep it company. It should\l"
	.string "not have to become a legend to be\l"
	.string "noticed.$"

Nexus_Text_Chuck_Buzzwole_ChampionIntro:
	.string "WAHAHAH! Now there's a training\n"
	.string "partner! It flexed once, and the echo\l"
	.string "knocked the sweat off my brow!\p"
	.string "No weights here seem to agree how\n"
	.string "heavy they are. Good thing I brought\l"
	.string "my own body. Brace yourself!$"

Nexus_Text_Chuck_Buzzwole_ChampionDefeat:
	.string "HAH! Strong form! You didn't just\n"
	.string "swing harder!$"

Nexus_Text_Chuck_Buzzwole_ChampionAfter:
	.string "{SPEAKER NAME_CHUCK}A bigger muscle isn't always a better\n"
	.string "answer. My wife has been telling me\l"
	.string "that for years.\p"
	.string "If that giant leaves a little life\n"
	.string "behind, teach it to rest too. Training\l"
	.string "only works if there's someone left to\l"
	.string "enjoy the strength.$"

Nexus_Text_Jasmine_Registeel_ChampionIntro:
	.string "...That metal has no scar I can find.\n"
	.string "I wondered whether anything had ever\l"
	.string "been able to reach it.\p"
	.string "Then it turned when I spoke softly.\n"
	.string "Perhaps we should begin that way, too.$"

Nexus_Text_Jasmine_Registeel_ChampionDefeat:
	.string "You were firm without being cruel.\n"
	.string "Thank you.$"

Nexus_Text_Jasmine_Registeel_ChampionAfter:
	.string "{SPEAKER NAME_JASMINE}A hard shell can keep pain out. It can\n"
	.string "make kindness difficult to recognize\l"
	.string "as well.\p"
	.string "If something small remains, please\n"
	.string "keep speaking to it. Even when it does\l"
	.string "not seem to answer. Especially then.$"

Nexus_Text_Pryce_Regice_ChampionIntro:
	.string "A winter older than my oldest memory\n"
	.string "walks in that ice. It has not thawed,\l"
	.string "even where the floor remembers summer.\p"
	.string "Patience is a discipline, youngster.\n"
	.string "Show me how well you have learned it.$"

Nexus_Text_Pryce_Regice_ChampionDefeat:
	.string "You conserved your strength. A\n"
	.string "sensible way through winter.$"

Nexus_Text_Pryce_Regice_ChampionAfter:
	.string "{SPEAKER NAME_PRYCE}Age alone does not make a teacher. One\n"
	.string "must still notice when the pupil is\l"
	.string "cold.\p"
	.string "Whatever small life remains, provide a\n"
	.string "shelter. Admiring endurance is no\l"
	.string "excuse to demand it every day.$"

Nexus_Text_Clair_Regidrago_ChampionIntro:
	.string "A dragon made from the strength of\n"
	.string "dragons. Naturally, I recognized the\l"
	.string "standard at once.\p"
	.string "Its unfinished edges keep appearing in\n"
	.string "the wrong century. Let's see whether\l"
	.string "your training is more complete!$"

Nexus_Text_Clair_Regidrago_ChampionDefeat:
	.string "Fine. You found a weakness. That is\n"
	.string "what challengers do.$"

Nexus_Text_Clair_Regidrago_ChampionAfter:
	.string "{SPEAKER NAME_CLAIR}Everyone keeps a picture of the dragon\n"
	.string "they expect me to be. I am rather\l"
	.string "tired of fitting it.\p"
	.string "If a small one remains, let it grow\n"
	.string "beyond the shape its maker planned.\l"
	.string "...That is sound advice.$"

Nexus_Text_Clair_Latias_ChampionIntro:
	.string "It changed its appearance before I\n"
	.string "could get a proper look. Then it\l"
	.string "looked back as though I were the one\l"
	.string "hiding.\p"
	.string "A dragon need not announce itself to\n"
	.string "be strong. I will, though. Prepare\l"
	.string "yourself!$"

Nexus_Text_Clair_Latias_ChampionDefeat:
	.string "You saw through my approach. Well\n"
	.string "done. There, I said it.$"

Nexus_Text_Clair_Latias_ChampionAfter:
	.string "{SPEAKER NAME_CLAIR}I tried to insist it show its true\n"
	.string "face. It waited until I stopped\l"
	.string "insisting.\p"
	.string "Give whatever little life remains the\n"
	.string "freedom to approach you. A dragon's\l"
	.string "trust should never be another badge\l"
	.string "you demand.$"

Nexus_Text_Will_Hoopa_ChampionIntro:
	.string "A ring hangs in the air, and the other\n"
	.string "side shows the back of my own mask. A\l"
	.string "most ambitious trick.\p"
	.string "Let us see whether your eyes follow\n"
	.string "the opening or the hand that offers\l"
	.string "it.$"

Nexus_Text_Will_Hoopa_ChampionDefeat:
	.string "You watched the right hand. Even I\n"
	.string "nearly didn't.$"

Nexus_Text_Will_Hoopa_ChampionAfter:
	.string "{SPEAKER NAME_WILL}A magician chooses where an audience\n"
	.string "looks. That creature chooses where the\l"
	.string "world meets itself.\p"
	.string "If a small life remains, ask before\n"
	.string "opening every door it can offer. Some\l"
	.string "curtains are closed for a reason.$"

Nexus_Text_Karen_Zarude_ChampionIntro:
	.string "People see the thorns and decide what\n"
	.string "kind of creature it must be. Beyond\l"
	.string "them, something small is being\l"
	.string "sheltered.\p"
	.string "I prefer to judge a partner by its\n"
	.string "choices. Let's see what yours choose\l"
	.string "today.$"

Nexus_Text_Karen_Zarude_ChampionDefeat:
	.string "Your favorites stood by you. I can\n"
	.string "respect that.$"

Nexus_Text_Karen_Zarude_ChampionAfter:
	.string "{SPEAKER NAME_KAREN}A rough hand can still hold someone\n"
	.string "carefully. A beautiful one can grip\l"
	.string "too hard.\p"
	.string "Give the small life that remains room\n"
	.string "among your favorites. It needn't\l"
	.string "become gentler to deserve a home.$"

Nexus_Text_Brendan_Deoxys_ChampionIntro:
	.string "My notes say it changed shape three\n"
	.string "times. The drawing says four. I\l"
	.string "haven't drawn the last one yet.\p"
	.string "Dad's field guides never covered this!\n"
	.string "Let's see how fast we can both adapt.$"

Nexus_Text_Brendan_Deoxys_ChampionDefeat:
	.string "Right! I need a new page for that\n"
	.string "adjustment!$"

Nexus_Text_Brendan_Deoxys_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}I keep trying to write down what it\n"
	.string "is. Maybe I should record what it does\l"
	.string "when someone is kind to it.\p"
	.string "If a little life remains, leave a few\n"
	.string "blank pages. It hasn't finished\l"
	.string "introducing itself.$"

Nexus_Text_May_Latias_ChampionIntro:
	.string "It borrowed my face for a moment, then\n"
	.string "took off laughing. At least, I think\l"
	.string "that was laughter.\p"
	.string "The reflection here remembers the\n"
	.string "smile before I do. Let's give it a\l"
	.string "real one to copy!$"

Nexus_Text_May_Latias_ChampionDefeat:
	.string "Oh! That was a much better surprise\n"
	.string "than mine!$"

Nexus_Text_May_Latias_ChampionAfter:
	.string "{SPEAKER NAME_MAY}Traveling means meeting someone before\n"
	.string "you know how to talk to them. A shared\l"
	.string "smile is usually a good start.\p"
	.string "If a small life follows you out of\n"
	.string "that reflection, let it choose the\l"
	.string "face it feels safe wearing.$"

Nexus_Text_Wally_Keldeo_ChampionIntro:
	.string "Its hooves leave little splashes on a\n"
	.string "path that hasn't remembered the river\l"
	.string "yet. It keeps practicing anyway.\p"
	.string "I understand wanting to catch up with\n"
	.string "the others. Let me show you how far\l"
	.string "I've come.$"

Nexus_Text_Wally_Keldeo_ChampionDefeat:
	.string "I lost, but I didn't stop trying.\n"
	.string "Neither did you.$"

Nexus_Text_Wally_Keldeo_ChampionAfter:
	.string "{SPEAKER NAME_WALLY}I used to think courage would mean\n"
	.string "never needing to catch my breath. It\l"
	.string "doesn't.\p"
	.string "If a small student remains after that\n"
	.string "blade of water, stay beside it while\l"
	.string "it practices. It doesn't have to earn\l"
	.string "the right to start.$"

Nexus_Text_Roxanne_Regirock_ChampionIntro:
	.string "These stones come from different\n"
	.string "strata, yet none seems out of place in\l"
	.string "the body. An excellent problem for a\l"
	.string "classroom!\p"
	.string "The dates in my notes keep exchanging\n"
	.string "places. Let us test something we can\l"
	.string "observe directly.$"

Nexus_Text_Roxanne_Regirock_ChampionDefeat:
	.string "A persuasive demonstration. I shall\n"
	.string "revise my explanation.$"

Nexus_Text_Roxanne_Regirock_ChampionAfter:
	.string "{SPEAKER NAME_ROXANNE}The oldest part is not necessarily the\n"
	.string "part holding everything together. I\l"
	.string "must remember that when I teach.\p"
	.string "Help the small life left behind find\n"
	.string "its own pieces. An education should\l"
	.string "offer materials, not dictate a\l"
	.string "finished shape.$"

Nexus_Text_Brawly_Urshifu_ChampionIntro:
	.string "One clean strike. Like finding the\n"
	.string "exact moment a wave breaks.\p"
	.string "The echo gets here before the punch,\n"
	.string "but the stance never wavers. That's\l"
	.string "some serious focus! Let's see if you\l"
	.string "can ride it out!$"

Nexus_Text_Brawly_Urshifu_ChampionDefeat:
	.string "Whoa! You read the break before I did!$"

Nexus_Text_Brawly_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_BRAWLY}You can paddle all day and still miss\n"
	.string "a wave if you won't wait.\p"
	.string "If a small fighter is left, teach it\n"
	.string "how to listen to the quiet. That's\l"
	.string "where a good strike begins. Same as a\l"
	.string "good ride.$"

Nexus_Text_Wattson_Xurkitree_ChampionIntro:
	.string "Wahahaha! A whole power station on\n"
	.string "legs, and not one sensible socket!\p"
	.string "My meter starts laughing before I do.\n"
	.string "Now that's a circuit I haven't built\l"
	.string "yet. Shall we see what lights up?$"

Nexus_Text_Wattson_Xurkitree_ChampionDefeat:
	.string "You tripped my plan without tripping\n"
	.string "over it! Splendid!$"

Nexus_Text_Wattson_Xurkitree_ChampionAfter:
	.string "{SPEAKER NAME_WATTSON}I used to think every new light meant\n"
	.string "progress. Then I had to ask who was\l"
	.string "still sitting in the dark.\p"
	.string "If a little spark is left, build it a\n"
	.string "home before you ask it to power one.$"

Nexus_Text_Flannery_Entei_ChampionIntro:
	.string "Its breath feels like the mountain\n"
	.string "just before the springs grow hot.\l"
	.string "Grandpa would know exactly what to\l"
	.string "say.\p"
	.string "I... think it wants us to stand\n"
	.string "steady. Right! Let's give it a proper\l"
	.string "battle!$"

Nexus_Text_Flannery_Entei_ChampionDefeat:
	.string "Okay! That was steady. Yours, I mean.\n"
	.string "I'll work on mine.$"

Nexus_Text_Flannery_Entei_ChampionAfter:
	.string "{SPEAKER NAME_FLANNERY}A volcano doesn't need to sound\n"
	.string "experienced. It simply carries its\l"
	.string "fire.\p"
	.string "If something small remains from that\n"
	.string "great roar, don't rush it into being\l"
	.string "impressive. I'm still learning to let\l"
	.string "my own heat speak for itself.$"

Nexus_Text_Norman_Regigigas_ChampionIntro:
	.string "Those hands once pulled whole\n"
	.string "continents. Here, the floor still\l"
	.string "waits for the effort to begin.\p"
	.string "Strength built over years can look\n"
	.string "slow to someone passing through. Let\l"
	.string "me see what your training has given\l"
	.string "you.$"

Nexus_Text_Norman_Regigigas_ChampionDefeat:
	.string "You kept working after the first\n"
	.string "obstacle. Good.$"

Nexus_Text_Norman_Regigigas_ChampionAfter:
	.string "{SPEAKER NAME_NORMAN}A parent can mistake standing still\n"
	.string "for being dependable. Even a continent\l"
	.string "must sometimes move.\p"
	.string "If a small beginning is left, walk\n"
	.string "beside it. Do not make your own pace\l"
	.string "the measure of everything it can\l"
	.string "become.$"

Nexus_Text_Winona_Lugia_ChampionIntro:
	.string "The air gathers beneath folded wings.\n"
	.string "Even this scattered sky seems to wait\l"
	.string "for their permission.\p"
	.string "In Fortree, we learn to listen before\n"
	.string "we climb. Let us see what the wind\l"
	.string "tells your partners.$"

Nexus_Text_Winona_Lugia_ChampionDefeat:
	.string "You changed direction without losing\n"
	.string "your grace.$"

Nexus_Text_Winona_Lugia_ChampionAfter:
	.string "{SPEAKER NAME_WINONA}A bird may choose the deep sea because\n"
	.string "its wings are too strong for the\l"
	.string "places it loves.\p"
	.string "The small life that remains should\n"
	.string "have room to learn a gentler flight.\l"
	.string "Strength need not mean a lifetime of\l"
	.string "distance.$"

Nexus_Text_Wallace_Meloetta_ChampionIntro:
	.string "A single note has dressed this empty\n"
	.string "room for a performance. The curtain's\l"
	.string "shadow rises before the curtain.\p"
	.string "I have rehearsed for quieter\n"
	.string "audiences. Shall we make an entrance\l"
	.string "worthy of the music?$"

Nexus_Text_Wallace_Meloetta_ChampionDefeat:
	.string "A beautiful finish. You allowed every\n"
	.string "partner a part.$"

Nexus_Text_Wallace_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_WALLACE}A perfect performance can still leave\n"
	.string "its artist lonely once the lights go\l"
	.string "down.\p"
	.string "If a small singer remains, listen when\n"
	.string "there is no stage. That is where you\l"
	.string "learn the voice that belongs to your\l"
	.string "companion.$"

Nexus_Text_Juan_Manaphy_ChampionIntro:
	.string "The sea has remembered every traveler\n"
	.string "who ever trusted its currents. That\l"
	.string "small presence seems to know them all.\p"
	.string "I taught a pupil who surpassed me. Let\n"
	.string "us see what we can teach one another.$"

Nexus_Text_Juan_Manaphy_ChampionDefeat:
	.string "Ah! A lesson delivered with admirable\n"
	.string "grace.$"

Nexus_Text_Juan_Manaphy_ChampionAfter:
	.string "{SPEAKER NAME_JUAN}One need not hold a heart still to\n"
	.string "understand it. Water carries a\l"
	.string "reflection better with an open hand.\p"
	.string "If a new little life remains, let your\n"
	.string "care be an invitation. A true bond\l"
	.string "leaves room for departure and return.$"

Nexus_Text_Sidney_GalarianMoltres_ChampionIntro:
	.string "Look at those black flames. People\n"
	.string "will decide it's wicked before it does\l"
	.string "a thing.\p"
	.string "The fire here burns the courage out of\n"
	.string "shadows. Let's see how yours handles\l"
	.string "an actual opponent!$"

Nexus_Text_Sidney_GalarianMoltres_ChampionDefeat:
	.string "Heh. Still standing inside, too. Nice.$"

Nexus_Text_Sidney_GalarianMoltres_ChampionAfter:
	.string "{SPEAKER NAME_SIDNEY}A frightening face doesn't tell you\n"
	.string "what a creature needs. Neither does a\l"
	.string "pleasant one.\p"
	.string "If a little ember is left, meet it on\n"
	.string "its own terms. No point calling\l"
	.string "yourself open-minded if you bring the\l"
	.string "verdict with you.$"

Nexus_Text_Phoebe_Marshadow_ChampionIntro:
	.string "There's someone giggling in my shadow!\n"
	.string "Every time I turn, it remembers being\l"
	.string "somewhere else.\p"
	.string "The spirits on Mt. Pyre would adore\n"
	.string "that game. Let's give our little guest\l"
	.string "something fun to watch!$"

Nexus_Text_Phoebe_Marshadow_ChampionDefeat:
	.string "Ahahaha! It copied your victory pose.\n"
	.string "I think you're friends!$"

Nexus_Text_Phoebe_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_PHOEBE}Shy spirits often borrow a movement\n"
	.string "before they risk a greeting. A wave is\l"
	.string "easier than a name.\p"
	.string "If something small stays behind,\n"
	.string "invite it to play. You don't have to\l"
	.string "drag it into the light to be together.$"

Nexus_Text_Phoebe_Lunala_ChampionIntro:
	.string "The dark under those wings is full of\n"
	.string "voices. They sound far away, but none\l"
	.string "sounds lost.\p"
	.string "My grandmother taught me to listen\n"
	.string "without calling everyone back. Let's\l"
	.string "see how your partners answer you!$"

Nexus_Text_Phoebe_Lunala_ChampionDefeat:
	.string "What a lovely answer! Even the quiet\n"
	.string "ones heard it.$"

Nexus_Text_Phoebe_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_PHOEBE}Not every spirit needs bringing home.\n"
	.string "Sometimes it only wants someone to\l"
	.string "hear that it arrived safely.\p"
	.string "If a small cloud remains, stay close\n"
	.string "while it learns the sky. It can choose\l"
	.string "its own distant paths later.$"

Nexus_Text_Glacia_Regice_ChampionIntro:
	.string "An ancient winter stands before us,\n"
	.string "untouched by the heat that tests all\l"
	.string "lesser ice.\p"
	.string "Yet the room remembers a thaw that\n"
	.string "never came. I wonder which of us will\l"
	.string "yield first. Shall we?$"

Nexus_Text_Glacia_Regice_ChampionDefeat:
	.string "Your resolve endured. A refreshing\n"
	.string "result.$"

Nexus_Text_Glacia_Regice_ChampionAfter:
	.string "{SPEAKER NAME_GLACIA}Ice can preserve a form long after the\n"
	.string "reason for preserving it is gone.\p"
	.string "Whatever small life remains, do not\n"
	.string "ask it to keep an old winter intact.\l"
	.string "Let it discover what deserves its\l"
	.string "strength today.$"

Nexus_Text_Drake_Rayquaza_ChampionIntro:
	.string "I have seen storms that left no\n"
	.string "horizon. That dragon travels above\l"
	.string "them all.\p"
	.string "Here, the wake of its flight arrives\n"
	.string "years before the wings. Stand firm,\l"
	.string "sailor. Show me your heading!$"

Nexus_Text_Drake_Rayquaza_ChampionDefeat:
	.string "You held your course when the sky gave\n"
	.string "you none.$"

Nexus_Text_Drake_Rayquaza_ChampionAfter:
	.string "{SPEAKER NAME_DRAKE}A captain earns a crew's trust on\n"
	.string "ordinary days, well before the sea\l"
	.string "turns.\p"
	.string "If a little life remains from that\n"
	.string "great sky, begin there. You will not\l"
	.string "earn a dragon's loyalty by waiting for\l"
	.string "a grand occasion.$"

Nexus_Text_Noland_Genesect_ChampionIntro:
	.string "Ancient instincts, new equipment.\n"
	.string "Whoever fitted the cannon thought\l"
	.string "they'd solved the whole match.\p"
	.string "The targeting shadow here points at\n"
	.string "yesterday. Let's see what you can do\l"
	.string "when the manual stops being useful!$"

Nexus_Text_Noland_Genesect_ChampionDefeat:
	.string "Good adaptation! You didn't just\n"
	.string "memorize my opening!$"

Nexus_Text_Noland_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_NOLAND}A move list tells you what a partner\n"
	.string "can attempt. Watching tells you why it\l"
	.string "hesitates.\p"
	.string "If something small survives that\n"
	.string "weapon, pay attention. Even a Factory\l"
	.string "Head ought to learn more than the\l"
	.string "specifications.$"

Nexus_Text_Greta_Buzzwole_ChampionIntro:
	.string "Body? No doubt about that one! Skill?\n"
	.string "Let's find out. Mind? It just flexed\l"
	.string "at its own shadow.\p"
	.string "The shadow flexed first. This is going\n"
	.string "to need a very unusual scorecard.\l"
	.string "Ready?$"

Nexus_Text_Greta_Buzzwole_ChampionDefeat:
	.string "Mind, Skill, Body! You earned every\n"
	.string "mark!$"

Nexus_Text_Greta_Buzzwole_ChampionAfter:
	.string "{SPEAKER NAME_GRETA}I can't judge its whole life from\n"
	.string "three turns of posing. Maybe it trains\l"
	.string "when nobody watches.\p"
	.string "If a little fighter remains, give it\n"
	.string "more than one way to earn your praise.\l"
	.string "A score should never be a home.$"

Nexus_Text_Tucker_Meloetta_ChampionIntro:
	.string "Hear that opening note? The seats\n"
	.string "remember an audience that has not\l"
	.string "arrived! At last, a proper overture!\p"
	.string "I shall supply the spectacle. You, my\n"
	.string "friend, must supply a worthy rival!$"

Nexus_Text_Tucker_Meloetta_ChampionDefeat:
	.string "Bravo! I would demand an encore if the\n"
	.string "star were mine!$"

Nexus_Text_Tucker_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_TUCKER}The finest performer in the room may\n"
	.string "be the one listening from the wings. I\l"
	.string "forget that rather easily.\p"
	.string "If a small voice remains after the\n"
	.string "music, ask what it would like to sing.\l"
	.string "Then give it the stage.$"

Nexus_Text_Lucy_Spectrier_ChampionIntro:
	.string "...Hooves behind every door.\p"
	.string "The tracks lead out. The sound comes\n"
	.string "in.\p"
	.string "That one chooses without being seen.\n"
	.string "Your turn.$"

Nexus_Text_Lucy_Spectrier_ChampionDefeat:
	.string "...You heard the right step.$"

Nexus_Text_Lucy_Spectrier_ChampionAfter:
	.string "{SPEAKER NAME_LUCY}I don't open every door.\p"
	.string "Some things on the other side are\n"
	.string "frightened, too.\p"
	.string "If a small shadow stays, leave a way\n"
	.string "out.\p"
	.string "Let it decide to stay.$"

Nexus_Text_Spenser_Calyrex_ChampionIntro:
	.string "Hoho. A crown without a kingdom, and\n"
	.string "the seeds still bow as it passes.\p"
	.string "My old knees bowed too. They insist\n"
	.string "that was respect. Let us see what\l"
	.string "nature asks of your partners.$"

Nexus_Text_Spenser_Calyrex_ChampionDefeat:
	.string "They chose well. So did you, by\n"
	.string "listening.$"

Nexus_Text_Spenser_Calyrex_ChampionAfter:
	.string "{SPEAKER NAME_SPENSER}A ruler who remembers every harvest\n"
	.string "might still need one person willing to\l"
	.string "plant beside him.\p"
	.string "If a small beginning remains, tend it\n"
	.string "without ceremony. A crown is poor\l"
	.string "shelter from the rain.$"

Nexus_Text_Anabel_Lunala_ChampionIntro:
	.string "A path has opened in the dark. My\n"
	.string "notes say I used it to leave. My\l"
	.string "footprints say I have just arrived.\p"
	.string "I will not confuse either record with\n"
	.string "your history. Show me how you handle\l"
	.string "uncertainty.$"

Nexus_Text_Anabel_Lunala_ChampionDefeat:
	.string "You assessed what was here. You did\n"
	.string "not chase an echo.$"

Nexus_Text_Anabel_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_ANABEL}In my fragment, I learned that a way\n"
	.string "home and a way back are different\l"
	.string "things. Those wings offer both without\l"
	.string "explaining either.\p"
	.string "If something small remains, give it a\n"
	.string "safe place to begin before asking it\l"
	.string "for directions.$"

Nexus_Text_Maxie_Volcanion_ChampionIntro:
	.string "Fire and water, working in the same\n"
	.string "body. A rather pointed correction to\l"
	.string "my old proposal.\p"
	.string "The steam here condenses into rain\n"
	.string "that has already fallen. Let us test a\l"
	.string "more practical balance.$"

Nexus_Text_Maxie_Volcanion_ChampionDefeat:
	.string "You made opposing forces cooperate. I\n"
	.string "shall remember that.$"

Nexus_Text_Maxie_Volcanion_ChampionAfter:
	.string "{SPEAKER NAME_MAXIE}I argued that one element needed more\n"
	.string "room. That creature makes a life at\l"
	.string "their meeting.\p"
	.string "If a small beginning remains from that\n"
	.string "pressure, provide space for both sides\l"
	.string "of its nature. My mistake need not\l"
	.string "become its inheritance.$"

Nexus_Text_Archie_Manaphy_ChampionIntro:
	.string "Fwahahaha! All that sea, and the\n"
	.string "strongest pull is a little heartbeat!\p"
	.string "I heard the tide here answer before it\n"
	.string "called. Let's see if your crew can\l"
	.string "answer each other half as well!$"

Nexus_Text_Archie_Manaphy_ChampionDefeat:
	.string "Aye! Nobody on your team was left\n"
	.string "drifting!$"

Nexus_Text_Archie_Manaphy_ChampionAfter:
	.string "{SPEAKER NAME_ARCHIE}I wanted an ocean big enough for every\n"
	.string "life. Nearly forgot the people already\l"
	.string "swimming in it.\p"
	.string "If a small heart comes back from that\n"
	.string "tide, listen to it. Loving the whole\l"
	.string "sea starts with caring for one little\l"
	.string "swimmer.$"

Nexus_Text_Archie_Lugia_ChampionIntro:
	.string "A wingbeat down there could turn the\n"
	.string "whole sea over. It keeps the wings\l"
	.string "folded.\p"
	.string "The waves here remember the storm it\n"
	.string "decided not to make! That's strength\l"
	.string "worth a look. Come on, let's have it!$"

Nexus_Text_Archie_Lugia_ChampionDefeat:
	.string "Ha! You knew when to ease off the\n"
	.string "sail!$"

Nexus_Text_Archie_Lugia_ChampionAfter:
	.string "{SPEAKER NAME_ARCHIE}I used to think loving the sea meant\n"
	.string "making it louder. That quiet giant has\l"
	.string "a better answer.\p"
	.string "Give the little life left behind a\n"
	.string "calm harbor. There'll be enough storms\l"
	.string "without you asking it to make one.$"

Nexus_Text_Gladion_Mewtwo_ChampionIntro:
	.string "They made it strong enough to obey no\n"
	.string "one, then acted surprised when it\l"
	.string "left.\p"
	.string "Those empty walls keep remembering the\n"
	.string "lock. I'm not helping them close it.\l"
	.string "Show me what your partners chose.$"

Nexus_Text_Gladion_Mewtwo_ChampionDefeat:
	.string "They stayed with you. That tells me\n"
	.string "enough.$"

Nexus_Text_Gladion_Mewtwo_ChampionAfter:
	.string "{SPEAKER NAME_GLADION}I know what a laboratory can call a\n"
	.string "success. It isn't the same thing as a\l"
	.string "life.\p"
	.string "If something small remains, don't give\n"
	.string "it another purpose it never asked for.\l"
	.string "Let it find a name for itself first.$"

Nexus_Text_Kukui_Zeraora_ChampionIntro:
	.string "Woo! It kicks off the air like the air\n"
	.string "owes it a rematch!\p"
	.string "I tried timing the discharge. The\n"
	.string "bruise arrived before my stopwatch\l"
	.string "started. Let's test something with a\l"
	.string "little less thunder, cousin!$"

Nexus_Text_Kukui_Zeraora_ChampionDefeat:
	.string "That's a move worth studying! My ribs\n"
	.string "are grateful we battled normally.$"

Nexus_Text_Kukui_Zeraora_ChampionAfter:
	.string "{SPEAKER NAME_KUKUI}A move makes sense when you get\n"
	.string "what the body needs to do. That\l"
	.string "creature seems to be teaching the sky\l"
	.string "new rules.\p"
	.string "If a little spark remains, watch how\n"
	.string "it plays. Research starts with letting\l"
	.string "a life be itself.$"

Nexus_Text_Lusamine_Nihilego_ChampionIntro:
	.string "It moves as though a hand were\n"
	.string "carrying a veil. There is no hand.\p"
	.string "I once mistook that delicacy for an\n"
	.string "invitation. Here, the invitation\l"
	.string "arrives before the creature does. Let\l"
	.string "us proceed with greater care.$"

Nexus_Text_Lusamine_Nihilego_ChampionDefeat:
	.string "You held your distance without turning\n"
	.string "cruel. Thank you.$"

Nexus_Text_Lusamine_Nihilego_ChampionAfter:
	.string "{SPEAKER NAME_LUSAMINE}Wanting to keep a beautiful thing safe\n"
	.string "can become wanting it unable to leave.\l"
	.string "I know that confusion.\p"
	.string "Whatever small life remains beneath\n"
	.string "that veil, give it boundaries it can\l"
	.string "understand. And respect the ones it\l"
	.string "gives you.$"

Nexus_Text_Janine_Marshadow_ChampionIntro:
	.string "Ha! There's a student hiding in my\n"
	.string "shadow, copying every jump!\p"
	.string "Trouble is, it lands before I take\n"
	.string "off. Father's lessons didn't cover\l"
	.string "that. Let's give it a demonstration\l"
	.string "worth copying!$"

Nexus_Text_Janine_Marshadow_ChampionDefeat:
	.string "Hyah! You found the real opening, not\n"
	.string "my decoy!$"

Nexus_Text_Janine_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_JANINE}A good apprentice learns your moves. A\n"
	.string "great one eventually invents a move\l"
	.string "you couldn't teach.\p"
	.string "If a little shadow follows you, make\n"
	.string "room for that day. I'm still looking\l"
	.string "forward to surprising Father with\l"
	.string "mine.$"

Nexus_Text_Leaf_Celebi_ChampionIntro:
	.string "I turned a page and found notes in my\n"
	.string "own handwriting. I haven't visited\l"
	.string "those woods yet.\p"
	.string "Something small is carrying spring\n"
	.string "through the gaps between the dates.\l"
	.string "Let's make this a day worth recording!$"

Nexus_Text_Leaf_Celebi_ChampionDefeat:
	.string "Oh! I'm keeping that page, even if the\n"
	.string "date changes.$"

Nexus_Text_Leaf_Celebi_ChampionAfter:
	.string "{SPEAKER NAME_GREEN}I wanted to see every creature. I\n"
	.string "didn't realize that could mean meeting\l"
	.string "the same one in a different spring.\p"
	.string "If a little life remains, let it enjoy\n"
	.string "today. A journey doesn't improve\l"
	.string "because you rush to its last page.$"

Nexus_Text_AZ_Xerneas_ChampionIntro:
	.string "The branches shine with life that has\n"
	.string "not yet decided what to become. I once\l"
	.string "tore such life from the world to\l"
	.string "answer a loss.\p"
	.string "Let me see what you choose to protect.$"

Nexus_Text_AZ_Xerneas_ChampionDefeat:
	.string "You kept faith with the living. Keep\n"
	.string "it.$"

Nexus_Text_AZ_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_AZ}I wanted one flower back. I made a\n"
	.string "weapon that asked the world to pay for\l"
	.string "my grief.\p"
	.string "If a small beginning remains beneath\n"
	.string "those shining branches, let it grow\l"
	.string "without a debt. No life owes another\l"
	.string "its existence.$"

Nexus_Text_AZ_Yveltal_ChampionIntro:
	.string "That shadow gathers everything that\n"
	.string "has reached its end. Here, the endings\l"
	.string "arrive before the lives.\p"
	.string "I have lived far past the years I was\n"
	.string "given. Show me what you do with yours.$"

Nexus_Text_AZ_Yveltal_ChampionDefeat:
	.string "You spent your strength without\n"
	.string "wasting your companions.$"

Nexus_Text_AZ_Yveltal_ChampionAfter:
	.string "{SPEAKER NAME_AZ}An end can be terrible without being\n"
	.string "an enemy. I refused one, and gave so\l"
	.string "many to others.\p"
	.string "Whatever small life is left, do not\n"
	.string "burden it with making you whole. It\l"
	.string "has its own years to live.$"

Nexus_Text_AZ_Celebi_ChampionIntro:
	.string "The forest offers me a path toward a\n"
	.string "day I cannot forgive. Each leaf points\l"
	.string "backward.\p"
	.string "I have walked long enough to know that\n"
	.string "returning is not repairing. Will you\l"
	.string "walk forward with your partners?$"

Nexus_Text_AZ_Celebi_ChampionDefeat:
	.string "Yes. You allowed a moment to pass\n"
	.string "without throwing it away.$"

Nexus_Text_AZ_Celebi_ChampionAfter:
	.string "{SPEAKER NAME_AZ}I could spend another thousand years\n"
	.string "trying to reach the hour before my\l"
	.string "choice. Someone would still have to\l"
	.string "choose differently.\p"
	.string "If a little green life remains, give\n"
	.string "it a future worth visiting. That is\l"
	.string "work I can still do.$"

Nexus_Text_Agatha_Spectrier_ChampionIntro:
	.string "Hear the hooves? Stop looking for a\n"
	.string "shape to put around them.\p"
	.string "That horse is feeding on your\n"
	.string "hesitation while its tracks wait for\l"
	.string "yesterday. I haven't the patience to\l"
	.string "become its supper. Have you?$"

Nexus_Text_Agatha_Spectrier_ChampionDefeat:
	.string "Hmph. You kept your nerve. That will\n"
	.string "be useful.$"

Nexus_Text_Agatha_Spectrier_ChampionAfter:
	.string "{SPEAKER NAME_AGATHA}Young fools assume a ghost is waiting\n"
	.string "to be explained away. Some older fools\l"
	.string "do the same.\p"
	.string "If a small shadow stays behind, learn\n"
	.string "to live beside the mystery. You\l"
	.string "needn't stare through a friend to know\l"
	.string "it is there.$"

Nexus_Text_Agatha_Marshadow_ChampionIntro:
	.string "Something in your shadow has been\n"
	.string "studying your stance. Mine tried\l"
	.string "copying my cane.\p"
	.string "I told it to find an opponent its own\n"
	.string "age. It couldn't find yesterday,\l"
	.string "either. Show it a better lesson.$"

Nexus_Text_Agatha_Marshadow_ChampionDefeat:
	.string "Good. Your shadow has something worth\n"
	.string "practicing.$"

Nexus_Text_Agatha_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_AGATHA}An old trick stays useful until\n"
	.string "somebody learns to see it. That little\l"
	.string "watcher learns quickly.\p"
	.string "Give what remains a chance to invent\n"
	.string "something of its own. I didn't spend\l"
	.string "my life training ghosts to make them\l"
	.string "copies of me.$"

Nexus_Text_Agatha_Giratina_ChampionIntro:
	.string "The floor keeps arguing with my feet.\n"
	.string "A great shadow has decided that being\l"
	.string "cast out means writing its own rules.\p"
	.string "Hah! I might almost approve. Let's see\n"
	.string "how well you stand without familiar\l"
	.string "ground.$"

Nexus_Text_Agatha_Giratina_ChampionDefeat:
	.string "You stayed upright. Even with the\n"
	.string "world sulking around you.$"

Nexus_Text_Agatha_Giratina_ChampionAfter:
	.string "{SPEAKER NAME_AGATHA}People call a place empty when the\n"
	.string "lives inside it don't suit them. They\l"
	.string "say the same about the dead.\p"
	.string "If a small beginning comes from that\n"
	.string "exile, make it welcome. Save the\l"
	.string "judgment for something you actually\l"
	.string "understand.$"

Nexus_Text_Alder_SlitherWing_ChampionIntro:
	.string "Ha! A sun you can warm your hands\n"
	.string "beside, before the moth ever learned\l"
	.string "to fly.\p"
	.string "The dawn here is walking on six legs.\n"
	.string "Come on! Let's give it a battle worth\l"
	.string "waking for!$"

Nexus_Text_Alder_SlitherWing_ChampionDefeat:
	.string "Ha ha! That put some warmth back in\n"
	.string "these old bones!$"

Nexus_Text_Alder_SlitherWing_ChampionAfter:
	.string "{SPEAKER NAME_ALDER}I knew a partner whose warmth seemed\n"
	.string "certain to last forever. It didn't.\l"
	.string "The time we shared still matters.\p"
	.string "If a little life remains, share a meal\n"
	.string "today. Don't save every good thing for\l"
	.string "when it has grown strong.$"

Nexus_Text_Alder_Groudon_ChampionIntro:
	.string "That great back lifts, and another\n"
	.string "patch of ground remembers becoming\l"
	.string "land. Plenty of room for a traveler!\p"
	.string "Though I suppose the ocean might\n"
	.string "disagree. Let's see whether your team\l"
	.string "can leave room for one another.$"

Nexus_Text_Alder_Groudon_ChampionDefeat:
	.string "Well fought! Nobody had to disappear\n"
	.string "for someone else to shine.$"

Nexus_Text_Alder_Groudon_ChampionAfter:
	.string "{SPEAKER NAME_ALDER}I have walked a great deal of land.\n"
	.string "Most of it was already home to\l"
	.string "someone.\p"
	.string "If a small beginning remains from that\n"
	.string "rising earth, teach it to notice its\l"
	.string "neighbors. A wide world still needs\l"
	.string "considerate feet.$"

Nexus_Text_Alder_HoOh_ChampionIntro:
	.string "Those colors make a road across a sky\n"
	.string "that cannot remember the rain. I have\l"
	.string "followed less promising roads.\p"
	.string "Come, traveler! Let us see what you\n"
	.string "carry beneath all that hope.$"

Nexus_Text_Alder_HoOh_ChampionDefeat:
	.string "A fine answer! You fought as though\n"
	.string "tomorrow were worth reaching.$"

Nexus_Text_Alder_HoOh_ChampionAfter:
	.string "{SPEAKER NAME_ALDER}Hope is easier to praise than to\n"
	.string "practice after a loss. Some mornings,\l"
	.string "practice is simply getting up and\l"
	.string "feeding your partners.\p"
	.string "If a small flame remains, care for it\n"
	.string "on those mornings. Rebirth can begin\l"
	.string "very quietly.$"

Nexus_Text_Allister_Lunala_ChampionIntro:
	.string "Um... the dark has wings. It folded\n"
	.string "them so I could see the stars again.\p"
	.string "I think it was being kind. My shadow\n"
	.string "remembers being there before me. Would\l"
	.string "you... battle us first?$"

Nexus_Text_Allister_Lunala_ChampionDefeat:
	.string "Oh. You weren't afraid of the dark\n"
	.string "around us.$"

Nexus_Text_Allister_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_ALLISTER}I used to think being seen meant\n"
	.string "losing somewhere safe to hide. Those\l"
	.string "wings make shelter without closing the\l"
	.string "sky.\p"
	.string "If a little cloud remains, let it come\n"
	.string "out when it's ready. You can keep\l"
	.string "watch until then.$"

Nexus_Text_Allister_Spectrier_ChampionIntro:
	.string "I can hear it walking. It stops\n"
	.string "whenever I try to speak.\p"
	.string "Maybe it's shy too. The mist has\n"
	.string "already heard the words I haven't\l"
	.string "said. Um... let's try a battle.$"

Nexus_Text_Allister_Spectrier_ChampionDefeat:
	.string "It stayed to listen. So did you. Thank\n"
	.string "you.$"

Nexus_Text_Allister_Spectrier_ChampionAfter:
	.string "{SPEAKER NAME_ALLISTER}People keep trying to find its face in\n"
	.string "the fog. I wish they'd wait for it to\l"
	.string "turn toward them.\p"
	.string "If a little shadow stays behind, don't\n"
	.string "pull it out. Sit nearby. Being patient\l"
	.string "can be a way to say hello.$"

Nexus_Text_Allister_Marshadow_ChampionIntro:
	.string "Something small is hiding in my\n"
	.string "shadow. It waves whenever I forget to\l"
	.string "be nervous.\p"
	.string "The wave reached the wall before my\n"
	.string "hand moved. Um... maybe a battle will\l"
	.string "help us say hello.$"

Nexus_Text_Allister_Marshadow_ChampionDefeat:
	.string "Oh... it copied your smile. I think\n"
	.string "that means thank you.$"

Nexus_Text_Allister_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_ALLISTER}I don't mind sharing a shadow. It's\n"
	.string "easier than standing alone where\l"
	.string "everyone can see.\p"
	.string "You can sit beside the little one\n"
	.string "afterward. It might borrow your wave\l"
	.string "before it finds a greeting of its own.$"

Nexus_Text_Avery_Mewtwo_ChampionIntro:
	.string "Its mind moved the stones before I\n"
	.string "could announce my own powers. A\l"
	.string "regrettably impatient introduction.\p"
	.string "The stones now insist they have always\n"
	.string "been there. Prepare for a\l"
	.string "demonstration with rather better\l"
	.string "manners!$"

Nexus_Text_Avery_Mewtwo_ChampionDefeat:
	.string "An exceptional performance. Almost as\n"
	.string "exceptional as my composure.$"

Nexus_Text_Avery_Mewtwo_ChampionAfter:
	.string "{SPEAKER NAME_AVERY}To be born with such power and still\n"
	.string "leave one's makers behind... I admit,\l"
	.string "the freedom is impressive.\p"
	.string "If a small beginning remains, praise\n"
	.string "something besides its gifts. One does\l"
	.string "tire of being measured against the\l"
	.string "family reputation.$"

Nexus_Text_Avery_GalarianArticuno_ChampionIntro:
	.string "An elegant gaze, a flawless posture,\n"
	.string "and a mind that could freeze an\l"
	.string "audience in place. Finally, an\l"
	.string "appropriate standard!\p"
	.string "My hat bowed before I did. I shall now\n"
	.string "recover the initiative.$"

Nexus_Text_Avery_GalarianArticuno_ChampionDefeat:
	.string "You have penetrated my defenses. My\n"
	.string "dignity remains airborne.$"

Nexus_Text_Avery_GalarianArticuno_ChampionAfter:
	.string "{SPEAKER NAME_AVERY}I thought its distant stare meant it\n"
	.string "was admiring my technique. Perhaps we\l"
	.string "both hoped the other would look\l"
	.string "impressed.\p"
	.string "Whatever small life remains, let it be\n"
	.string "ordinary sometimes. Maintaining an\l"
	.string "astonishing presence is exhausting\l"
	.string "work.$"

Nexus_Text_Avery_Hoopa_ChampionIntro:
	.string "It levitated a ring beside my hat.\n"
	.string "Inside was another hat, which I have\l"
	.string "yet to purchase.\p"
	.string "I applaud the presentation, though the\n"
	.string "theft lacks refinement. Watch a proper\l"
	.string "psychic performance!$"

Nexus_Text_Avery_Hoopa_ChampionDefeat:
	.string "A temporary reversal! There must be\n"
	.string "another opening somewhere.$"

Nexus_Text_Avery_Hoopa_ChampionAfter:
	.string "{SPEAKER NAME_AVERY}I can make a ball float. That creature\n"
	.string "makes distance disappear. Comparisons\l"
	.string "are unhelpful, and I intend to stop\l"
	.string "making them.\p"
	.string "If a small companion remains, do not\n"
	.string "rank its wonders. Allow it the\l"
	.string "satisfaction of surprising you.$"

Nexus_Text_Barry_Uxie_ChampionIntro:
	.string "Wait! I had a really important\n"
	.string "thought! Then that little one looked\l"
	.string "this way, and...\p"
	.string "Hold on. My notebook says I already\n"
	.string "forgot it tomorrow. Fine! I'll battle\l"
	.string "before I lose the rest!$"

Nexus_Text_Barry_Uxie_ChampionDefeat:
	.string "I remember that loss perfectly! Hey,\n"
	.string "that isn't fair!$"

Nexus_Text_Barry_Uxie_ChampionAfter:
	.string "{SPEAKER NAME_BARRY}I rush because I don't want to miss\n"
	.string "anything. Makes it awkward when I\l"
	.string "can't remember what I saw.\p"
	.string "If a little life stays behind, slow\n"
	.string "down beside it. I'm trying that.\l"
	.string "Starting right after this\l"
	.string "conversation.$"

Nexus_Text_Barry_Deoxys_ChampionIntro:
	.string "It changed shape, and the path got\n"
	.string "shorter. Or I got faster. Either way,\l"
	.string "I reached the finish before I started!\p"
	.string "Finally, something around here\n"
	.string "understands my schedule! Think you can\l"
	.string "keep up?$"

Nexus_Text_Barry_Deoxys_ChampionDefeat:
	.string "Whoa! You changed plans even faster\n"
	.string "than I did!$"

Nexus_Text_Barry_Deoxys_ChampionAfter:
	.string "{SPEAKER NAME_BARRY}I keep acting like arriving first\n"
	.string "means I've understood the place. That\l"
	.string "thing arrived from somewhere I can't\l"
	.string "even point at.\p"
	.string "If a small beginning remains, give it\n"
	.string "a chance to settle. You can explore\l"
	.string "together afterward. Fast, obviously.$"

Nexus_Text_Barry_Azelf_ChampionIntro:
	.string "That little one keeps pushing at a\n"
	.string "door the room says isn't there yet. I\l"
	.string "like its attitude!\p"
	.string "The handle's already on the other\n"
	.string "side. Let's see if your willpower can\l"
	.string "handle a proper challenge!$"

Nexus_Text_Barry_Azelf_ChampionDefeat:
	.string "You didn't quit when the plan went\n"
	.string "wrong. Nice!$"

Nexus_Text_Barry_Azelf_ChampionAfter:
	.string "{SPEAKER NAME_BARRY}Dad always looks so relaxed before a\n"
	.string "battle. I used to think that meant he\l"
	.string "didn't care as much.\p"
	.string "Maybe determination doesn't have to\n"
	.string "shout. If something small remains,\l"
	.string "listen for its quiet decisions too.\l"
	.string "I'm working on mine.$"

Nexus_Text_Bea_Marshadow_ChampionIntro:
	.string "There is a second stance inside my\n"
	.string "shadow. It corrects itself whenever I\l"
	.string "do.\p"
	.string "The last correction arrived before my\n"
	.string "foot moved. I cannot train that by\l"
	.string "repetition alone. Please face us.$"

Nexus_Text_Bea_Marshadow_ChampionDefeat:
	.string "Your stance held. Mine must become\n"
	.string "less predictable.$"

Nexus_Text_Bea_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_BEA}Copying a movement can teach the body\n"
	.string "its shape. Understanding the reason\l"
	.string "for it takes longer.\p"
	.string "If a small student remains in that\n"
	.string "shadow, allow mistakes. A dojo where\l"
	.string "nobody can fail has stopped teaching.$"

Nexus_Text_Bea_Urshifu_ChampionIntro:
	.string "A single movement, practiced beyond\n"
	.string "the need for thought. Its echo stands\l"
	.string "ahead of it, waiting.\p"
	.string "I have spent many mornings seeking\n"
	.string "that economy. Let us see what our\l"
	.string "training has earned.$"

Nexus_Text_Bea_Urshifu_ChampionDefeat:
	.string "You recognized the moment. That is a\n"
	.string "difficult skill.$"

Nexus_Text_Bea_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_BEA}I sometimes keep training after my\n"
	.string "partners need rest. Determination can\l"
	.string "conceal poor judgment.\p"
	.string "If a small pupil remains, teach it to\n"
	.string "end a session properly. A powerful\l"
	.string "strike begins with a body that has\l"
	.string "been cared for.$"

Nexus_Text_Bea_GalarianZapdos_ChampionIntro:
	.string "It runs instead of taking the easy\n"
	.string "distance of flight. Each footfall\l"
	.string "leaves a challenge in the stone.\p"
	.string "Here, the prints climb a stair that\n"
	.string "has not been built. Please take your\l"
	.string "stance.$"

Nexus_Text_Bea_GalarianZapdos_ChampionDefeat:
	.string "You met the pressure without rushing.\n"
	.string "Well done.$"

Nexus_Text_Bea_GalarianZapdos_ChampionAfter:
	.string "{SPEAKER NAME_BEA}A difficult path is useful only when\n"
	.string "there is a reason to take it.\l"
	.string "Suffering is not a lesson by itself.\p"
	.string "Give the little life left behind firm\n"
	.string "ground and proper rest. It can choose\l"
	.string "its own steep climbs later.$"

Nexus_Text_Brycen_Kyurem_ChampionIntro:
	.string "There is a shape inside that ice where\n"
	.string "something should be. The frost keeps\l"
	.string "its place.\p"
	.string "I know how to hold a silence for an\n"
	.string "audience. That silence has no\l"
	.string "audience. Watch carefully.$"

Nexus_Text_Brycen_Kyurem_ChampionDefeat:
	.string "You saw the pause. You did not mistake\n"
	.string "it for surrender.$"

Nexus_Text_Brycen_Kyurem_ChampionAfter:
	.string "{SPEAKER NAME_BRYCEN}A missing part is not always a part\n"
	.string "waiting for someone else to supply it.\p"
	.string "Whatever small beginning remains, let\n"
	.string "it stand as itself. Do not cast it in\l"
	.string "a role written for a whole that no\l"
	.string "longer exists.$"

Nexus_Text_Brycen_Articuno_ChampionIntro:
	.string "A feather falls through the snow. The\n"
	.string "cold reaches the ground first.\p"
	.string "Every movement is exact, even where\n"
	.string "the seasons have forgotten their\l"
	.string "order. Let us try to meet that\l"
	.string "discipline.$"

Nexus_Text_Brycen_Articuno_ChampionDefeat:
	.string "Your movements wasted nothing. A clean\n"
	.string "finish.$"

Nexus_Text_Brycen_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_BRYCEN}I left the stage and learned to speak\n"
	.string "through training. That bird seems to\l"
	.string "shape silence with a wing.\p"
	.string "If a small life remains, offer shelter\n"
	.string "without demanding a performance. There\l"
	.string "is value in an unwitnessed day.$"

Nexus_Text_Brycen_Regice_ChampionIntro:
	.string "An ancient cold remembers a world no\n"
	.string "audience has seen. Nothing inside it\l"
	.string "moves for our applause.\p"
	.string "Here, even its stillness casts a\n"
	.string "moving shadow. Let us begin without\l"
	.string "wasting a gesture.$"

Nexus_Text_Brycen_Regice_ChampionDefeat:
	.string "You endured the stillness and chose\n"
	.string "your moment.$"

Nexus_Text_Brycen_Regice_ChampionAfter:
	.string "{SPEAKER NAME_BRYCEN}An actor can preserve a pose until it\n"
	.string "loses every meaning it once carried. I\l"
	.string "have done that.\p"
	.string "If a small life remains, allow it to\n"
	.string "change. Even a body of old ice should\l"
	.string "not be sentenced to repeat the past.$"

Nexus_Text_Cheren_Cobalion_ChampionIntro:
	.string "It stood between armed people and a\n"
	.string "burning forest. A clear answer to what\l"
	.string "strength might be for.\p"
	.string "The ash here falls from a fire that\n"
	.string "has not started. Show me what you\l"
	.string "would stand between.$"

Nexus_Text_Cheren_Cobalion_ChampionDefeat:
	.string "You protected the option your partner\n"
	.string "needed. A thoughtful answer.$"

Nexus_Text_Cheren_Cobalion_ChampionAfter:
	.string "{SPEAKER NAME_CHEREN}My students expect an answer whenever\n"
	.string "I ask a question. I owe them the\l"
	.string "honesty of saying when I am still\l"
	.string "learning.\p"
	.string "If a small guardian remains, teach it\n"
	.string "to question the battle as well as win\l"
	.string "it.$"

Nexus_Text_Cheren_Kyurem_ChampionIntro:
	.string "A lesson has been written here with\n"
	.string "half the words missing. The cold\l"
	.string "preserves every gap.\p"
	.string "I once believed gathering enough\n"
	.string "strength would answer every question.\l"
	.string "Let us test what your strength can\l"
	.string "actually explain.$"

Nexus_Text_Cheren_Kyurem_ChampionDefeat:
	.string "A clear result. My explanation needs\n"
	.string "more work.$"

Nexus_Text_Cheren_Kyurem_ChampionAfter:
	.string "{SPEAKER NAME_CHEREN}I chased strength as though my life\n"
	.string "were waiting to be completed by it.\l"
	.string "That hollow outline is an\l"
	.string "uncomfortable reminder.\p"
	.string "If a small beginning remains, let it\n"
	.string "learn without calling it incomplete. A\l"
	.string "student is already a person.$"

Nexus_Text_Cheren_Zamazenta_ChampionIntro:
	.string "The shield bears the marks of blows\n"
	.string "this room has not delivered. Someone\l"
	.string "decided to stand before each one.\p"
	.string "A teacher makes smaller decisions like\n"
	.string "that every day. I would like to see\l"
	.string "yours.$"

Nexus_Text_Cheren_Zamazenta_ChampionDefeat:
	.string "You kept the vulnerable part of your\n"
	.string "plan protected.$"

Nexus_Text_Cheren_Zamazenta_ChampionAfter:
	.string "{SPEAKER NAME_CHEREN}Being a shield does not mean taking\n"
	.string "every blow yourself. I teach that more\l"
	.string "easily than I practice it.\p"
	.string "If a small guardian remains, give it\n"
	.string "partners who will protect it in\l"
	.string "return. Responsibility should not\l"
	.string "require loneliness.$"

Nexus_Text_Cilan_Virizion_ChampionIntro:
	.string "The air carries the scent of grass\n"
	.string "after rain, though no rain here\l"
	.string "recalls falling. An exquisite\l"
	.string "freshness.\p"
	.string "Those elegant steps conceal a\n"
	.string "defender's strength. Shall we see how\l"
	.string "your team's qualities combine?$"

Nexus_Text_Cilan_Virizion_ChampionDefeat:
	.string "A beautifully balanced response!\n"
	.string "Nothing overwhelmed the finish.$"

Nexus_Text_Cilan_Virizion_ChampionAfter:
	.string "{SPEAKER NAME_CILAN}I might describe that grace as a\n"
	.string "delicate flavor, but the forest it\l"
	.string "defended was anything but delicate.\p"
	.string "If a small life remains, learn what it\n"
	.string "needs before choosing a place for it.\l"
	.string "A companion is more than an\l"
	.string "ingredient.$"

Nexus_Text_Cilan_Groudon_ChampionIntro:
	.string "Such heat! Enough to dry every leaf in\n"
	.string "my pantry, and then the pantry itself!\p"
	.string "The new ground remembers being an\n"
	.string "ocean. A strong ingredient needs\l"
	.string "careful balance. Let us see how you\l"
	.string "manage yours!$"

Nexus_Text_Cilan_Groudon_ChampionDefeat:
	.string "You balanced the pressure admirably. I\n"
	.string "over-seasoned my approach.$"

Nexus_Text_Cilan_Groudon_ChampionAfter:
	.string "{SPEAKER NAME_CILAN}One bold flavor can ruin a meal when\n"
	.string "the cook forgets everything beside it.\l"
	.string "The earth and sea seem to know that\l"
	.string "lesson painfully.\p"
	.string "Give the small beginning a balanced\n"
	.string "life. Even the sun needs an evening.$"

Nexus_Text_Cilan_Shaymin_ChampionIntro:
	.string "A field of flowers is appearing behind\n"
	.string "those tiny steps. The scent reaches me\l"
	.string "from a spring still several pages\l"
	.string "away.\p"
	.string "A modest presence can transform the\n"
	.string "whole table. Shall we test a few\l"
	.string "combinations?$"

Nexus_Text_Cilan_Shaymin_ChampionDefeat:
	.string "A delightful finish! I should offer my\n"
	.string "compliments to every partner.$"

Nexus_Text_Cilan_Shaymin_ChampionAfter:
	.string "{SPEAKER NAME_CILAN}Gratitude cannot be extracted by\n"
	.string "serving a meal, however carefully\l"
	.string "prepared. It arrives freely, or it\l"
	.string "means very little.\p"
	.string "If a little life remains in those\n"
	.string "flowers, let it come and go. A welcome\l"
	.string "should have no hidden bill.$"

Nexus_Text_Cynthia_Giratina_ChampionIntro:
	.string "One version of the old story calls it\n"
	.string "banishment. Another calls it the first\l"
	.string "place that could contain its nature.\p"
	.string "The writing here turns over when I\n"
	.string "read it. Let us examine an answer we\l"
	.string "can choose ourselves.$"

Nexus_Text_Cynthia_Giratina_ChampionDefeat:
	.string "You adapted when the ground stopped\n"
	.string "supporting your assumptions.$"

Nexus_Text_Cynthia_Giratina_ChampionAfter:
	.string "{SPEAKER NAME_CYNTHIA}A myth often tells us more about the\n"
	.string "people who preserved it than the\l"
	.string "creature at its heart.\p"
	.string "If a small life remains from that\n"
	.string "inverted world, meet it before you\l"
	.string "name its crime. Exile need not be its\l"
	.string "inheritance.$"

Nexus_Text_Cynthia_Palkia_ChampionIntro:
	.string "The pillars are the same distance\n"
	.string "apart in every direction, including\l"
	.string "the one behind us. A fascinating\l"
	.string "difficulty for an archaeologist.\p"
	.string "Something is deciding what distance\n"
	.string "means. Let us see how close your\l"
	.string "partners can stand in purpose.$"

Nexus_Text_Cynthia_Palkia_ChampionDefeat:
	.string "A fine demonstration. Your team kept\n"
	.string "its shape.$"

Nexus_Text_Cynthia_Palkia_ChampionAfter:
	.string "{SPEAKER NAME_CYNTHIA}A border can separate two worlds\n"
	.string "without making either one less real.\l"
	.string "We forget that when writing our\l"
	.string "histories.\p"
	.string "Give the little life that remains a\n"
	.string "place of its own. Friendship can cross\l"
	.string "a distance without erasing it.$"

Nexus_Text_Cynthia_Arceus_ChampionIntro:
	.string "Every tablet seems to remember a\n"
	.string "different beginning. None explains who\l"
	.string "was there to write it down.\p"
	.string "I have spent years studying those\n"
	.string "questions. A battle will not settle\l"
	.string "them, but it may tell us something\l"
	.string "about ourselves.$"

Nexus_Text_Cynthia_Arceus_ChampionDefeat:
	.string "A wonderful battle. There is always\n"
	.string "another question after the answer.$"

Nexus_Text_Cynthia_Arceus_ChampionAfter:
	.string "{SPEAKER NAME_CYNTHIA}People seek a creator hoping it will\n"
	.string "explain their purpose. I suspect\l"
	.string "purpose still asks something of the\l"
	.string "people seeking it.\p"
	.string "If a small beginning remains, care for\n"
	.string "the life before the legend. A\l"
	.string "beginning has no duty to repeat a\l"
	.string "myth.$"

Nexus_Text_Cyrus_Dialga_ChampionIntro:
	.string "Each clock insists on a different\n"
	.string "hour. They agree only when the iron\l"
	.string "pulse beneath us strikes.\p"
	.string "Time can be brought into order. Human\n"
	.string "feeling resists the same correction.\l"
	.string "Show me whether your decisions can\l"
	.string "remain precise.$"

Nexus_Text_Cyrus_Dialga_ChampionDefeat:
	.string "Your timing was exact. The emotional\n"
	.string "cause remains an inefficiency.$"

Nexus_Text_Cyrus_Dialga_ChampionAfter:
	.string "{SPEAKER NAME_CYRUS}I intended a world without the\n"
	.string "disorder of longing. This place\l"
	.string "contains time without agreement, and\l"
	.string "still I find myself waiting.\p"
	.string "If a small remainder survives, observe\n"
	.string "it carefully. I cannot yet account for\l"
	.string "why that matters to me.$"

Nexus_Text_Cyrus_Palkia_ChampionIntro:
	.string "These distances obey no stable\n"
	.string "measure. The far wall is closer than\l"
	.string "the palm of my hand.\p"
	.string "Space without order cannot support a\n"
	.string "complete world. I will test whether\l"
	.string "your judgment is any more coherent.$"

Nexus_Text_Cyrus_Palkia_ChampionDefeat:
	.string "You maintained coordination under\n"
	.string "contradictory conditions. Noted.$"

Nexus_Text_Cyrus_Palkia_ChampionAfter:
	.string "{SPEAKER NAME_CYRUS}I thought separation could remove the\n"
	.string "failures people bring to one another.\l"
	.string "Here, separation itself is broken, and\l"
	.string "my thoughts persist.\p"
	.string "Take the small remainder if it\n"
	.string "survives. Removing something from\l"
	.string "sight has not made it cease to exist.$"

Nexus_Text_Cyrus_Mesprit_ChampionIntro:
	.string "An emotion passes through the room\n"
	.string "before the memory that might explain\l"
	.string "it. The creature at the lake appears\l"
	.string "to accept this.\p"
	.string "I do not. Show me what purpose such\n"
	.string "disorder can serve.$"

Nexus_Text_Cyrus_Mesprit_ChampionDefeat:
	.string "You acted on concern before\n"
	.string "calculation. The result was effective.$"

Nexus_Text_Cyrus_Mesprit_ChampionAfter:
	.string "{SPEAKER NAME_CYRUS}I can identify the pulse without\n"
	.string "explaining why the empty lake\l"
	.string "unsettles me. Rejection has not\l"
	.string "removed the phenomenon.\p"
	.string "If a small life remains, keep your\n"
	.string "observations honest. Do not call a\l"
	.string "thing absent merely because it\l"
	.string "contradicts your theory.$"

Nexus_Text_Dawn_Palkia_ChampionIntro:
	.string "The ribbons of light keep crossing\n"
	.string "without meeting. I tried practicing\l"
	.string "between them and came back to the same\l"
	.string "step from the other side!\p"
	.string "No need to worry. We'll make space for\n"
	.string "a proper battle!$"

Nexus_Text_Dawn_Palkia_ChampionDefeat:
	.string "You found room for every partner!\n"
	.string "That's a wonderful combination!$"

Nexus_Text_Dawn_Palkia_ChampionAfter:
	.string "{SPEAKER NAME_DAWN}A good routine needs space for the\n"
	.string "partner, even when the audience only\l"
	.string "notices the Trainer.\p"
	.string "If a small life remains where those\n"
	.string "distances meet, let it choose how\l"
	.string "close to come. You can build a lovely\l"
	.string "combination from there.$"

Nexus_Text_Dawn_Cresselia_ChampionIntro:
	.string "I dreamed of a ribbon floating on a\n"
	.string "lake. Then I woke up beside it, with\l"
	.string "the dream still reflected below.\p"
	.string "That soft light makes it easier to\n"
	.string "breathe. Let's give it something happy\l"
	.string "to watch!$"

Nexus_Text_Dawn_Cresselia_ChampionDefeat:
	.string "Oh! Even the reflection looked pleased\n"
	.string "with that finish!$"

Nexus_Text_Dawn_Cresselia_ChampionAfter:
	.string "{SPEAKER NAME_DAWN}Mom says you can't rehearse away every\n"
	.string "worry. Sometimes you need someone to\l"
	.string "sit beside you until it passes.\p"
	.string "If a small life remains in that\n"
	.string "moonlight, be that someone. It should\l"
	.string "be allowed a bad dream too.$"

Nexus_Text_Dawn_Mesprit_ChampionIntro:
	.string "I started smiling before I remembered\n"
	.string "anything funny. Then that little one\l"
	.string "turned, and the lake seemed to smile\l"
	.string "back.\p"
	.string "A feeling can begin a combination!\n"
	.string "Let's see what yours becomes!$"

Nexus_Text_Dawn_Mesprit_ChampionDefeat:
	.string "I can feel how proud your partners\n"
	.string "are. You should be too!$"

Nexus_Text_Dawn_Mesprit_ChampionAfter:
	.string "{SPEAKER NAME_DAWN}I used to practice the expression\n"
	.string "before the step, hoping the right\l"
	.string "feeling would follow. My partners\l"
	.string "always knew.\p"
	.string "If a little life stays behind, let it\n"
	.string "feel whatever comes. We don't need a\l"
	.string "happy face for every moment together.$"

Nexus_Text_Diantha_Xerneas_ChampionIntro:
	.string "Those antlers hold enough color for a\n"
	.string "thousand costumes. The shadows below\l"
	.string "them have not yet decided which lives\l"
	.string "to become.\p"
	.string "Every role begins with possibility.\n"
	.string "Shall we see what you bring to this\l"
	.string "one?$"

Nexus_Text_Diantha_Xerneas_ChampionDefeat:
	.string "Beautifully played. You gave every\n"
	.string "partner a future in that scene.$"

Nexus_Text_Diantha_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_DIANTHA}An audience remembers a face long\n"
	.string "after the person wearing it has\l"
	.string "changed. Life asks us to allow the\l"
	.string "change anyway.\p"
	.string "If a small beginning remains, admire\n"
	.string "what it becomes tomorrow as warmly as\l"
	.string "what shines today.$"

Nexus_Text_Diantha_IronValiant_ChampionIntro:
	.string "A perfect silhouette waits at the end\n"
	.string "of the hall. It turns before the cue I\l"
	.string "have yet to give.\p"
	.string "Someone seems to have written an ideal\n"
	.string "hero and forgotten the life within the\l"
	.string "costume. Let us improvise.$"

Nexus_Text_Diantha_IronValiant_ChampionDefeat:
	.string "You found an answer the script had not\n"
	.string "anticipated.$"

Nexus_Text_Diantha_IronValiant_ChampionAfter:
	.string "{SPEAKER NAME_DIANTHA}I have played characters whose courage\n"
	.string "was decided before I arrived. Living\l"
	.string "courage has no such guarantee.\p"
	.string "If a small beginning survives that\n"
	.string "shining design, give it room to\l"
	.string "hesitate. It deserves choices beyond a\l"
	.string "flawless performance.$"

Nexus_Text_Diantha_Meloetta_ChampionIntro:
	.string "The overture has begun without an\n"
	.string "orchestra. A voice moves between song\l"
	.string "and dance as though the distinction\l"
	.string "were only a costume.\p"
	.string "I should like to answer with a\n"
	.string "performance of our own. Shall we?$"

Nexus_Text_Diantha_Meloetta_ChampionDefeat:
	.string "Such timing! You let the silence\n"
	.string "complete the scene.$"

Nexus_Text_Diantha_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_DIANTHA}A voice can be praised until its owner\n"
	.string "is afraid to sing anything new. Fame\l"
	.string "has that curious cruelty.\p"
	.string "If a little singer remains, listen\n"
	.string "without demanding your favorite song.\l"
	.string "An artist needs a home beyond the\l"
	.string "applause.$"

Nexus_Text_Gardenia_Shaymin_ChampionIntro:
	.string "Flowers! Real flowers, right through\n"
	.string "all this ash! I knew something could\l"
	.string "grow here.\p"
	.string "The petals remember a sunny day this\n"
	.string "sky hasn't had yet. Let's give those\l"
	.string "roots a reason to hold on!$"

Nexus_Text_Gardenia_Shaymin_ChampionDefeat:
	.string "Wow! That put even more life into the\n"
	.string "room!$"

Nexus_Text_Gardenia_Shaymin_ChampionAfter:
	.string "{SPEAKER NAME_GARDENIA}I love plants because they keep\n"
	.string "reaching for whatever light they can\l"
	.string "find. That little gardener seems to\l"
	.string "carry some of its own.\p"
	.string "If something small remains, give it\n"
	.string "fresh soil. Gratitude grows better\l"
	.string "when nobody is pulling at the leaves.$"

Nexus_Text_Gardenia_Zygarde_ChampionIntro:
	.string "There are tiny watchers in the roots.\n"
	.string "They all looked up when I stepped on a\l"
	.string "new shoot.\p"
	.string "Creepy? A little! But they're\n"
	.string "protecting the garden. Let's show them\l"
	.string "we know how to look after our\l"
	.string "partners!$"

Nexus_Text_Gardenia_Zygarde_ChampionDefeat:
	.string "Your team kept its balance. Even the\n"
	.string "roots stopped trembling!$"

Nexus_Text_Gardenia_Zygarde_ChampionAfter:
	.string "{SPEAKER NAME_GARDENIA}I get frightened when I can't tell\n"
	.string "what's watching me. Then I remember\l"
	.string "how many lives a forest has to watch\l"
	.string "over.\p"
	.string "Care for the small part that stays\n"
	.string "behind. The whole garden starts with\l"
	.string "noticing one living thing.$"

Nexus_Text_Gardenia_Celebi_ChampionIntro:
	.string "A green blur just carried a seed into\n"
	.string "yesterday. The tree is already shading\l"
	.string "my notebook!\p"
	.string "I have questions. Lots of questions.\n"
	.string "First, let's see how your team handles\l"
	.string "a little unexpected growth!$"

Nexus_Text_Gardenia_Celebi_ChampionDefeat:
	.string "That was brilliant! I'd plant a whole\n"
	.string "bed for a moment like that!$"

Nexus_Text_Gardenia_Celebi_ChampionAfter:
	.string "{SPEAKER NAME_GARDENIA}I'd love to visit every forest before\n"
	.string "anyone cut its first tree. But the\l"
	.string "gardens growing now still need\l"
	.string "watering.\p"
	.string "If a little traveler remains, make\n"
	.string "today a place it wants to return to.\l"
	.string "We can start with some good soil.$"

Nexus_Text_Ghetsis_Kyurem_ChampionIntro:
	.string "An empty vessel, waiting for the\n"
	.string "strength that should command it. Even\l"
	.string "the ice preserves a place for its\l"
	.string "master.\p"
	.string "The chains here recall an order not\n"
	.string "yet spoken. You will learn to\l"
	.string "anticipate mine as well.$"

Nexus_Text_Ghetsis_Kyurem_ChampionDefeat:
	.string "Impossible! A command does not become\n"
	.string "optional because you dislike it!$"

Nexus_Text_Ghetsis_Kyurem_ChampionAfter:
	.string "{SPEAKER NAME_GHETSIS}They call that emptiness tragic. I\n"
	.string "call it available. Yet the silence\l"
	.string "continues after every order I give.\p"
	.string "Take the small remainder if you wish.\n"
	.string "You will discover that caring for a\l"
	.string "thing is far less efficient than\l"
	.string "commanding it.$"

Nexus_Text_Ghetsis_Cobalion_ChampionIntro:
	.string "It once opposed humans to defend the\n"
	.string "weak. Admirable theater. Every\l"
	.string "rebellion eventually discovers the\l"
	.string "need for a leader.\p"
	.string "This forest remembers my promises\n"
	.string "before its own fire. Let us establish\l"
	.string "whose voice carries further.$"

Nexus_Text_Ghetsis_Cobalion_ChampionDefeat:
	.string "You dare make my authority the\n"
	.string "obstacle?!$"

Nexus_Text_Ghetsis_Cobalion_ChampionAfter:
	.string "{SPEAKER NAME_GHETSIS}It will not lower its head. Not for\n"
	.string "the title, the cause, or the reward.\l"
	.string "An irritating consistency.\p"
	.string "If something small remains, perhaps\n"
	.string "you can persuade it to bow. I suspect\l"
	.string "you will waste the opportunity by\l"
	.string "asking what it wants.$"

Nexus_Text_Ghetsis_Pecharunt_ChampionIntro:
	.string "One sweet offering, and gratitude\n"
	.string "becomes obedience. How many speeches\l"
	.string "such a gift could spare!\p"
	.string "The hands here applaud before they\n"
	.string "have accepted it. You will join them\l"
	.string "after a proper demonstration.$"

Nexus_Text_Ghetsis_Pecharunt_ChampionDefeat:
	.string "No! You will not deny me the result I\n"
	.string "am owed!$"

Nexus_Text_Ghetsis_Pecharunt_ChampionAfter:
	.string "{SPEAKER NAME_GHETSIS}An order hidden inside a kindness is\n"
	.string "still an order. Most people only\l"
	.string "resent learning that they obeyed.\p"
	.string "Take whatever little thing remains. If\n"
	.string "you insist on giving it choices, do\l"
	.string "not complain when it refuses you. I\l"
	.string "would not tolerate it.$"

Nexus_Text_Gloria_Zacian_ChampionIntro:
	.string "I found a sword's shadow lying across\n"
	.string "a forest path. The blade hadn't\l"
	.string "arrived yet, but something was already\l"
	.string "guarding it.\p"
	.string "My team picked this road. Let's give\n"
	.string "them a challenge worthy of the choice!$"

Nexus_Text_Gloria_Zacian_ChampionDefeat:
	.string "That felt like a proper story! You\n"
	.string "earned the next page.$"

Nexus_Text_Gloria_Zacian_ChampionAfter:
	.string "{SPEAKER NAME_GLORIA}Where I come from, the sword was rusty\n"
	.string "before anyone called it a legend.\l"
	.string "Someone still reached for it when help\l"
	.string "was needed.\p"
	.string "Whatever small life remains, meet it\n"
	.string "that way. No ceremony. Just be there\l"
	.string "when it needs a hand.$"

Nexus_Text_Gloria_Zamazenta_ChampionIntro:
	.string "There are dents in that shield from a\n"
	.string "battle the clearing hasn't remembered\l"
	.string "yet. It stands ready anyway.\p"
	.string "I promised my partners a proper\n"
	.string "challenge. Can yours stand together\l"
	.string "when the pressure comes?$"

Nexus_Text_Gloria_Zamazenta_ChampionDefeat:
	.string "You covered each other all the way\n"
	.string "through. Brilliant!$"

Nexus_Text_Gloria_Zamazenta_ChampionAfter:
	.string "{SPEAKER NAME_GLORIA}A shield makes a promise with its\n"
	.string "whole body. I'm still learning what it\l"
	.string "takes to keep one like that.\p"
	.string "The little beginning left behind\n"
	.string "deserves someone willing to stand in\l"
	.string "front for a change. That's a promise\l"
	.string "you can practice.$"

Nexus_Text_Gloria_Eternatus_ChampionIntro:
	.string "The sky has started another match\n"
	.string "without asking the stadium. Those red\l"
	.string "bones are drawing every light toward\l"
	.string "them.\p"
	.string "My team says we're ready. I believe\n"
	.string "them. Let's make sure you are too!$"

Nexus_Text_Gloria_Eternatus_ChampionDefeat:
	.string "You stayed with your team when\n"
	.string "everything went red. Well done!$"

Nexus_Text_Gloria_Eternatus_ChampionAfter:
	.string "{SPEAKER NAME_GLORIA}An empty stadium can still make you\n"
	.string "feel as though everyone is waiting for\l"
	.string "you to save the day.\p"
	.string "Don't let the little life left\n"
	.string "afterward grow up under that weight.\l"
	.string "It deserves an ordinary afternoon\l"
	.string "before another legend.$"

Nexus_Text_Grusha_Kyurem_ChampionIntro:
	.string "There's a hollow in that ice the wind\n"
	.string "can't fill. The slope remembers a fall\l"
	.string "that hasn't happened.\p"
	.string "I know better than to trust a quiet\n"
	.string "surface. Keep your balance. We begin\l"
	.string "here.$"

Nexus_Text_Grusha_Kyurem_ChampionDefeat:
	.string "You held your line. I couldn't push\n"
	.string "you off it.$"

Nexus_Text_Grusha_Kyurem_ChampionAfter:
	.string "{SPEAKER NAME_GRUSHA}I used to think one perfect run could\n"
	.string "answer everything I'd lost. It never\l"
	.string "did.\p"
	.string "That frozen outline doesn't owe anyone\n"
	.string "a missing piece. Give the small\l"
	.string "beginning room to become something\l"
	.string "other than a repair.$"

Nexus_Text_Grusha_ChienPao_ChampionIntro:
	.string "Two broken ends of a blade, and a\n"
	.string "whole blizzard holding them together.\l"
	.string "The snow reaches the bottom before it\l"
	.string "falls.\p"
	.string "One wrong turn will cost you. Show me\n"
	.string "you can read the slope.$"

Nexus_Text_Grusha_ChienPao_ChampionDefeat:
	.string "You didn't let the sharp edge choose\n"
	.string "your route. Good.$"

Nexus_Text_Grusha_ChienPao_ChampionAfter:
	.string "{SPEAKER NAME_GRUSHA}People admire a dangerous line once\n"
	.string "someone survives it. They rarely ask\l"
	.string "about the price.\p"
	.string "The small life in that snow can learn\n"
	.string "a gentler path. You don't need to keep\l"
	.string "proving what it can endure.$"

Nexus_Text_Grusha_Articuno_ChampionIntro:
	.string "A feather touches the slope, and\n"
	.string "winter spreads uphill. The wind has\l"
	.string "forgotten which side of the mountain\l"
	.string "we stand on.\p"
	.string "Watch what actually moves. A beautiful\n"
	.string "view won't keep you balanced.$"

Nexus_Text_Grusha_Articuno_ChampionDefeat:
	.string "Clean turns. No wasted panic. I\n"
	.string "respect that.$"

Nexus_Text_Grusha_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_GRUSHA}I miss the mountains most when the\n"
	.string "snow looks untouched. Then I remember\l"
	.string "how much can lie beneath a perfect\l"
	.string "surface.\p"
	.string "Give the little life left behind\n"
	.string "shelter from that cold. Admiration\l"
	.string "won't keep it warm.$"

Nexus_Text_Hassel_Rayquaza_ChampionIntro:
	.string "A dragon has drawn a green curve\n"
	.string "across a sky without edges. Oh, what a\l"
	.string "line! My students would fill a room\l"
	.string "with attempts to follow it!\p"
	.string "Please, show me how your partners\n"
	.string "express themselves!$"

Nexus_Text_Hassel_Rayquaza_ChampionDefeat:
	.string "Wonderful! Such confidence in every\n"
	.string "stroke! Forgive the tears.$"

Nexus_Text_Hassel_Rayquaza_ChampionAfter:
	.string "{SPEAKER NAME_HASSEL}My family expected me to follow a path\n"
	.string "already drawn. I found my own through\l"
	.string "art, then returned to dragons by\l"
	.string "choice.\p"
	.string "That vast sky leaves a small\n"
	.string "beginning. Let it choose its own line.\l"
	.string "You may be amazed where it leads.$"

Nexus_Text_Hassel_Regidrago_ChampionIntro:
	.string "Its maker seems to have left an\n"
	.string "unfinished dragon. Yet look at the\l"
	.string "strength already present!\p"
	.string "The missing edges cast a complete\n"
	.string "shadow here. We must judge the living\l"
	.string "work with care. Please, take your\l"
	.string "stance!$"

Nexus_Text_Hassel_Regidrago_ChampionDefeat:
	.string "Magnificent! You found something new\n"
	.string "in an unexpected shape!$"

Nexus_Text_Hassel_Regidrago_ChampionAfter:
	.string "{SPEAKER NAME_HASSEL}I have seen students erase their\n"
	.string "finest ideas trying to match an image\l"
	.string "in their heads. A teacher must know\l"
	.string "when to stop correcting.\p"
	.string "The small life beyond that ancient\n"
	.string "work deserves encouragement before\l"
	.string "comparison. Let it surprise its own\l"
	.string "outline.$"

Nexus_Text_Hassel_Latias_ChampionIntro:
	.string "A dragon borrowed my face, then looked\n"
	.string "terribly embarrassed when I began to\l"
	.string "cry. Such sensitivity!\p"
	.string "The reflection here changes before its\n"
	.string "subject. Let us offer it an honest\l"
	.string "expression to follow!$"

Nexus_Text_Hassel_Latias_ChampionDefeat:
	.string "Oh... a beautiful answer! I shall need\n"
	.string "a moment.$"

Nexus_Text_Hassel_Latias_ChampionAfter:
	.string "{SPEAKER NAME_HASSEL}We sometimes hide a feeling because it\n"
	.string "matters too much to show. I have the\l"
	.string "opposite difficulty.\p"
	.string "You needn't demand a true face from\n"
	.string "the little one afterward. Offer a\l"
	.string "place where showing it feels safe.\l"
	.string "That is a teacher's work as well.$"

Nexus_Text_Hau_TapuKoko_ChampionIntro:
	.string "That shell snapped shut, and the whole\n"
	.string "sky jumped! I dropped my malasada. The\l"
	.string "echo caught it before I did.\p"
	.string "Grandpa would tell me to show some\n"
	.string "respect. A great battle counts, right?\l"
	.string "Let's go!$"

Nexus_Text_Hau_TapuKoko_ChampionDefeat:
	.string "Whoa! Bet even that restless guardian\n"
	.string "enjoyed watching you!$"

Nexus_Text_Hau_TapuKoko_ChampionAfter:
	.string "{SPEAKER NAME_HAU}Being a kahuna's grandson makes\n"
	.string "everyone watch how you stand. That one\l"
	.string "looks as though it would rather keep\l"
	.string "moving too.\p"
	.string "Let the little spark afterward play\n"
	.string "before anyone starts giving it titles.\l"
	.string "I'll bring the snacks.$"

Nexus_Text_Hau_Solgaleo_ChampionIntro:
	.string "The sun's got paws! It walked past,\n"
	.string "and every shadow pointed toward a\l"
	.string "morning I haven't seen yet.\p"
	.string "Makes me want to get moving, you know?\n"
	.string "Let's start with a battle!$"

Nexus_Text_Hau_Solgaleo_ChampionDefeat:
	.string "That was bright enough to wake up a\n"
	.string "whole island!$"

Nexus_Text_Hau_Solgaleo_ChampionAfter:
	.string "{SPEAKER NAME_HAU}Grandpa says a new day is another\n"
	.string "chance to do right by someone. I like\l"
	.string "that more than calling it a chance to\l"
	.string "win.\p"
	.string "If a little cloud stays behind, keep\n"
	.string "it company through its first mornings.\l"
	.string "Plenty of time for being the sun\l"
	.string "later.$"

Nexus_Text_Hau_TapuLele_ChampionIntro:
	.string "Those little scales fixed a scrape\n"
	.string "before I knew I'd got one. Then the\l"
	.string "flowers started drifting off to sleep.\p"
	.string "Grandpa always says enough can be\n"
	.string "plenty. Let's have a battle while\l"
	.string "we're both still awake!$"

Nexus_Text_Hau_TapuLele_ChampionDefeat:
	.string "That was plenty! In the good way.\n"
	.string "Really good!$"

Nexus_Text_Hau_TapuLele_ChampionAfter:
	.string "{SPEAKER NAME_HAU}I like giving people treats. I had to\n"
	.string "learn that a third malasada isn't\l"
	.string "always doing someone a favor.\p"
	.string "Let the little one afterward hear a\n"
	.string "gentle no sometimes. Caring for\l"
	.string "somebody includes listening when\l"
	.string "they've had enough.$"

Nexus_Text_Hilda_Reshiram_ChampionIntro:
	.string "It burns through a lie without needing\n"
	.string "to hear the end. Useful. I've followed\l"
	.string "too many promises that led nowhere.\p"
	.string "The white flame here remembers an\n"
	.string "answer I haven't found. First, I need\l"
	.string "through this door. Battle!$"

Nexus_Text_Hilda_Reshiram_ChampionDefeat:
	.string "Fine. You meant every move. I can\n"
	.string "respect that.$"

Nexus_Text_Hilda_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_HILDA}I told myself I was chasing the truth.\n"
	.string "Sometimes I think I just wanted a\l"
	.string "reason to keep moving.\p"
	.string "That small beginning left by the fire\n"
	.string "won't answer for someone who's gone.\l"
	.string "Let it have its own journey. I'll keep\l"
	.string "walking mine.$"

Nexus_Text_Hilda_Tornadus_ChampionIntro:
	.string "The wind threw my map back at me with\n"
	.string "tomorrow's road already torn out. That\l"
	.string "green troublemaker seemed pleased.\p"
	.string "Fine. I don't need a map to know\n"
	.string "you're in my way. Let's battle!$"

Nexus_Text_Hilda_Tornadus_ChampionDefeat:
	.string "You changed direction without losing\n"
	.string "the goal. Good.$"

Nexus_Text_Hilda_Tornadus_ChampionAfter:
	.string "{SPEAKER NAME_HILDA}I thought the next town would always\n"
	.string "hold the person I was looking for.\l"
	.string "This wind keeps offering another town.\p"
	.string "Stay with the small life afterward for\n"
	.string "a while. Leaving should be a choice,\l"
	.string "not the only thing you know how to do.$"

Nexus_Text_Hilda_Victini_ChampionIntro:
	.string "A little flame keeps finding its way\n"
	.string "back into my hands. Every time I lose\l"
	.string "sight of the road, it's waiting at the\l"
	.string "next turn.\p"
	.string "It hasn't promised a victory. Good.\n"
	.string "I'd rather earn one. Ready?$"

Nexus_Text_Hilda_Victini_ChampionDefeat:
	.string "You earned that one. No miracle\n"
	.string "needed.$"

Nexus_Text_Hilda_Victini_ChampionAfter:
	.string "{SPEAKER NAME_HILDA}Winning doesn't make the next goodbye\n"
	.string "easier. I learned that later than I\l"
	.string "should have.\p"
	.string "The small companion left by that flame\n"
	.string "deserves affection on losing days too.\l"
	.string "Don't make it responsible for keeping\l"
	.string "hope alive all by itself.$"

Nexus_Text_Hop_Zamazenta_ChampionIntro:
	.string "The shield's already scarred by a\n"
	.string "fight this clearing hasn't had. It\l"
	.string "still stands as though the next person\l"
	.string "matters most.\p"
	.string "That's the kind of strength I want to\n"
	.string "understand. Let's see yours!$"

Nexus_Text_Hop_Zamazenta_ChampionDefeat:
	.string "Right! You protected the opening your\n"
	.string "partner needed. Brilliant!$"

Nexus_Text_Hop_Zamazenta_ChampionAfter:
	.string "{SPEAKER NAME_HOP}I spent ages trying to battle like my\n"
	.string "brother. A shield can't do its job\l"
	.string "while pretending to be someone else's\l"
	.string "sword.\p"
	.string "I'll be taking notes on that. Give the\n"
	.string "little guardian afterward a chance to\l"
	.string "find its own way too.$"

Nexus_Text_Hop_Silvally_ChampionIntro:
	.string "That mask broke, and the creature\n"
	.string "underneath finally got to decide what\l"
	.string "kind of partner it wanted to be.\p"
	.string "The pieces here keep remembering the\n"
	.string "lock. Let's show it a team that\l"
	.string "doesn't need one!$"

Nexus_Text_Hop_Silvally_ChampionDefeat:
	.string "Your partners knew they could count on\n"
	.string "you. I saw it!$"

Nexus_Text_Hop_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_HOP}I used to read a defeat as proof I\n"
	.string "wasn't becoming the right person.\l"
	.string "Maybe becoming was the useful part.\p"
	.string "The little life past that broken mask\n"
	.string "doesn't need a role chosen in advance.\l"
	.string "Let it grow alongside you. Take notes,\l"
	.string "if that helps!$"

Nexus_Text_Hop_Suicune_ChampionIntro:
	.string "The water clears before those paws\n"
	.string "reach it. I've got the order written\l"
	.string "down three different ways already!\p"
	.string "Maybe I should watch instead of\n"
	.string "rushing the notes. A battle first,\l"
	.string "then? There's loads to learn!$"

Nexus_Text_Hop_Suicune_ChampionDefeat:
	.string "Brilliant! You watched what your\n"
	.string "partners needed, not just my moves!$"

Nexus_Text_Hop_Suicune_ChampionAfter:
	.string "{SPEAKER NAME_HOP}Research sounded quieter than battling\n"
	.string "until I tried following a north wind\l"
	.string "with a notebook. There is so much to\l"
	.string "notice.\p"
	.string "Check the little one's water\n"
	.string "afterward. Understanding a legend\l"
	.string "should start with doing something\l"
	.string "useful for the life in front of you.$"

Nexus_Text_Iono_Miraidon_ChampionIntro:
	.string "Your eyeballs are MINE! We've got a\n"
	.string "guest whose entrance lit the room\l"
	.string "before the room existed!\p"
	.string "Those wheels aren't on any road I can\n"
	.string "see. Think your team can handle that\l"
	.string "much voltage? Let's find out!$"

Nexus_Text_Iono_Miraidon_ChampionDefeat:
	.string "Bzzt! You cut right through the\n"
	.string "static! What a finish!$"

Nexus_Text_Iono_Miraidon_ChampionAfter:
	.string "{SPEAKER NAME_IONO}I tried filming that glow. The\n"
	.string "recording shows a city nobody here has\l"
	.string "built. For once, I haven't got a\l"
	.string "caption.\p"
	.string "Keep the little spark afterward off\n"
	.string "camera until it wants an audience.\l"
	.string "Some debuts deserve a little privacy.$"

Nexus_Text_Iono_Regieleki_ChampionIntro:
	.string "Breaking news! The walking power surge\n"
	.string "has arrived, and my equipment has\l"
	.string "decided to retire!\p"
	.string "Those bands are doing a LOT of work.\n"
	.string "Let's see how you handle a little\l"
	.string "pressure without blowing the whole\l"
	.string "show!$"

Nexus_Text_Iono_Regieleki_ChampionDefeat:
	.string "You grounded my big finish! The\n"
	.string "audience would go wild!$"

Nexus_Text_Iono_Regieleki_ChampionAfter:
	.string "{SPEAKER NAME_IONO}Everyone asks how bright it can get.\n"
	.string "I'm starting to wonder whether anyone\l"
	.string "asks how tired it is.\p"
	.string "Give the little spark a place with the\n"
	.string "lights turned down. Even I need to\l"
	.string "stop being on sometimes. Don't quote\l"
	.string "that clip.$"

Nexus_Text_Iono_Xurkitree_ChampionIntro:
	.string "Is that a tree? A cable? A guest who\n"
	.string "brought its own lighting rig? The\l"
	.string "shadow here keeps plugging into\l"
	.string "tomorrow!\p"
	.string "I'm calling that a spectacular\n"
	.string "entrance. Now let's see your battle\l"
	.string "face!$"

Nexus_Text_Iono_Xurkitree_ChampionDefeat:
	.string "You just rewired the whole match!\n"
	.string "That's prime viewing!$"

Nexus_Text_Iono_Xurkitree_ChampionAfter:
	.string "{SPEAKER NAME_IONO}I keep checking for a signal. That\n"
	.string "creature seems quite happy making its\l"
	.string "own. Maybe that's a lesson.\p"
	.string "The little life left afterward can\n"
	.string "learn to shine without a crowd. You'll\l"
	.string "still be there to see it. That ought\l"
	.string "to count.$"

Nexus_Text_Iris_Reshiram_ChampionIntro:
	.string "That big white dragon listens as\n"
	.string "though it can hear the bit of a story\l"
	.string "you left out.\p"
	.string "The blue fire knows an ending the\n"
	.string "storyteller hasn't reached! My dragons\l"
	.string "want to answer. Let's go!$"

Nexus_Text_Iris_Reshiram_ChampionDefeat:
	.string "Wow! You and your partners weren't\n"
	.string "hiding anything!$"

Nexus_Text_Iris_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_IRIS}People ask whether I understand\n"
	.string "dragons. I think they understand when\l"
	.string "I'm trying. That's why they stay.\p"
	.string "Let the little one after that flame\n"
	.string "hear you say when you're wrong. Trust\l"
	.string "grows better with the whole story.$"

Nexus_Text_Iris_Latias_ChampionIntro:
	.string "It looked like a girl for a moment,\n"
	.string "then laughed and flew right through\l"
	.string "the shape!\p"
	.string "Its reflection is still trying on\n"
	.string "faces. Heehee! Let's give it a proper\l"
	.string "battle to watch!$"

Nexus_Text_Iris_Latias_ChampionDefeat:
	.string "That was fun! Even the shy little\n"
	.string "watcher stayed!$"

Nexus_Text_Iris_Latias_ChampionAfter:
	.string "{SPEAKER NAME_IRIS}A dragon doesn't need to look fierce\n"
	.string "for its feelings to be strong.\l"
	.string "Sometimes it just needs you to notice\l"
	.string "it's nervous.\p"
	.string "You can wait while the little one\n"
	.string "afterward chooses how to say hello.\l"
	.string "The best friendships aren't races.$"

Nexus_Text_Iris_Regidrago_ChampionIntro:
	.string "Everybody keeps looking at the bits\n"
	.string "that aren't there. I'm looking at the\l"
	.string "dragon that is!\p"
	.string "Its shadow runs ahead with a body it\n"
	.string "hasn't grown. Come on! Let's show it\l"
	.string "what a whole team can do!$"

Nexus_Text_Iris_Regidrago_ChampionDefeat:
	.string "Your team was amazing! Everybody\n"
	.string "brought something different!$"

Nexus_Text_Iris_Regidrago_ChampionAfter:
	.string "{SPEAKER NAME_IRIS}When I was little, people were always\n"
	.string "telling me what I had left to learn.\l"
	.string "My dragons noticed what I could\l"
	.string "already do.\p"
	.string "Do that for the little life afterward.\n"
	.string "It's easier to grow when someone sees\l"
	.string "you now.$"

Nexus_Text_JessieJames_Meloetta_ChampionIntro:
	.string "Jessie: A voice that could make us\n"
	.string "stars!\p"
	.string "James: The echo has already signed our\n"
	.string "autographs!\p"
	.string "Jessie: Then let's give it a\n"
	.string "performance!\p"
	.string "James: Preferably one with a victory\n"
	.string "at the end!$"

Nexus_Text_JessieJames_Meloetta_ChampionDefeat:
	.string "Jessie: A tragic finale!\p"
	.string "James: At least we stayed in tune!$"

Nexus_Text_JessieJames_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_JESSIE_JAMES}Jessie: We could have filled a theater\n"
	.string "with that voice.\p"
	.string "James: It sounded lonely without\n"
	.string "anyone singing back.\p"
	.string "Jessie: Well, the little one afterward\n"
	.string "can rehearse with us.\p"
	.string "James: An equal share of the applause!\p"
	.string "Jessie: Don't promise the takings!$"

Nexus_Text_JessieJames_Zygarde_ChampionIntro:
	.string "Jessie: Tiny green spies in every\n"
	.string "corner!\p"
	.string "James: And every corner seems to be\n"
	.string "spying on next week!\p"
	.string "Jessie: They're watching for trouble.\p"
	.string "James: Then we've certainly made an\n"
	.string "impression.\p"
	.string "Jessie: Battle positions!$"

Nexus_Text_JessieJames_Zygarde_ChampionDefeat:
	.string "Jessie: Too many witnesses!\p"
	.string "James: And not one on our side!$"

Nexus_Text_JessieJames_Zygarde_ChampionAfter:
	.string "{SPEAKER NAME_JESSIE_JAMES}James: All those little parts working\n"
	.string "together. Rather touching.\p"
	.string "Jessie: We work together. Usually.\p"
	.string "James: Perhaps the small one afterward\n"
	.string "needs a team too.\p"
	.string "Jessie: Fine. But it can help carry\n"
	.string "the equipment.\p"
	.string "James: I think that means welcome.$"

Nexus_Text_JessieJames_Hoopa_ChampionIntro:
	.string "Jessie: A golden ring! At last, a\n"
	.string "valuable discovery!\p"
	.string "James: It's showing the inside of our\n"
	.string "empty purse.\p"
	.string "Jessie: From the future?\p"
	.string "James: Hard to tell.\p"
	.string "Jessie: Then we'll start by winning\n"
	.string "this battle!$"

Nexus_Text_JessieJames_Hoopa_ChampionDefeat:
	.string "James: Another door closed.\p"
	.string "Jessie: Stop narrating our defeats!$"

Nexus_Text_JessieJames_Hoopa_ChampionAfter:
	.string "{SPEAKER NAME_JESSIE_JAMES}Jessie: Imagine all the places those\n"
	.string "rings could take us.\p"
	.string "James: I'd settle for a quiet meal\n"
	.string "somewhere warm.\p"
	.string "Jessie: Bring the little one\n"
	.string "afterward.\p"
	.string "James: A table for one more?\p"
	.string "Jessie: Before it steals the table,\n"
	.string "yes.$"

Nexus_Text_Juniper_Genesect_ChampionIntro:
	.string "An ancient body carries a very recent\n"
	.string "idea of improvement. The fossil record\l"
	.string "here keeps editing out the weapon.\p"
	.string "I'd like to know what endured beneath\n"
	.string "it. A battle may help us ask better\l"
	.string "questions!$"

Nexus_Text_Juniper_Genesect_ChampionDefeat:
	.string "Excellent! Your partners used their\n"
	.string "history without being trapped by it.$"

Nexus_Text_Juniper_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_JUNIPER}A specimen can tell us where a life\n"
	.string "began. It cannot tell us every life it\l"
	.string "might choose afterward.\p"
	.string "Give the small beginning beyond that\n"
	.string "metal something its makers overlooked:\l"
	.string "the opportunity to surprise the person\l"
	.string "studying it.$"

Nexus_Text_Juniper_Meloetta_ChampionIntro:
	.string "There is a melody here older than any\n"
	.string "instrument I know. The echo remembers\l"
	.string "singers the hall has never held.\p"
	.string "Origins are my field, but choices\n"
	.string "interest me just as much. Shall we\l"
	.string "listen to your team's?$"

Nexus_Text_Juniper_Meloetta_ChampionDefeat:
	.string "A wonderful response! Every partner\n"
	.string "added something of its own.$"

Nexus_Text_Juniper_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_JUNIPER}We preserve a song by letting another\n"
	.string "generation sing it. A perfect\l"
	.string "recording alone cannot do that work.\p"
	.string "The little voice afterward may change\n"
	.string "the melody. Listen carefully before\l"
	.string "deciding something has been lost. You\l"
	.string "may be hearing a beginning.$"

Nexus_Text_Juniper_Mew_ChampionIntro:
	.string "A small shape keeps appearing at the\n"
	.string "edges of my notes. Every description I\l"
	.string "try seems to fit some other creature\l"
	.string "as well.\p"
	.string "Here, the family tree has branches\n"
	.string "older than its roots. Shall we\l"
	.string "investigate together?$"

Nexus_Text_Juniper_Mew_ChampionDefeat:
	.string "Marvelous! The most interesting result\n"
	.string "is always the one I didn't predict.$"

Nexus_Text_Juniper_Mew_ChampionAfter:
	.string "{SPEAKER NAME_JUNIPER}I study beginnings. It is tempting to\n"
	.string "expect a single beginning to explain\l"
	.string "everything that followed. Living\l"
	.string "things are less tidy.\p"
	.string "Let the little life afterward be your\n"
	.string "companion first. A friendship can\l"
	.string "answer questions a specimen jar never\l"
	.string "will.$"

Nexus_Text_Katy_Genesect_ChampionIntro:
	.string "Under all that sharp metal is a little\n"
	.string "Bug's long history. Someone seems to\l"
	.string "have mistaken a cannon for a finishing\l"
	.string "touch.\p"
	.string "The old shell's shadow arrives first.\n"
	.string "Shall we see what patience can\l"
	.string "accomplish?$"

Nexus_Text_Katy_Genesect_ChampionDefeat:
	.string "Oh, lovely work! A delicate answer to\n"
	.string "a rather forceful recipe.$"

Nexus_Text_Katy_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_KATY}One can decorate a cake until nobody\n"
	.string "remembers the flavor underneath. I\l"
	.string "suspect someone made a similar mistake\l"
	.string "here.\p"
	.string "Let the little life afterward enjoy\n"
	.string "being a creature. It has worn someone\l"
	.string "else's grand idea for quite long\l"
	.string "enough.$"

Nexus_Text_Katy_SlitherWing_ChampionIntro:
	.string "Such warm colors, and such determined\n"
	.string "little feet! The sun here seems to\l"
	.string "have started walking before it learned\l"
	.string "to rise.\p"
	.string "Growing into something wonderful takes\n"
	.string "patience. I do hope you brought a\l"
	.string "little appetite for a challenge!$"

Nexus_Text_Katy_SlitherWing_ChampionDefeat:
	.string "A splendid finish, dear! You handled\n"
	.string "the heat beautifully.$"

Nexus_Text_Katy_SlitherWing_ChampionAfter:
	.string "{SPEAKER NAME_KATY}People hurry past the small stages,\n"
	.string "waiting for the wings. There is so\l"
	.string "much worth loving before the first\l"
	.string "flight.\p"
	.string "The little beginning afterward need\n"
	.string "not rush. Feed it, let it rest, and\l"
	.string "enjoy who is sharing your kitchen\l"
	.string "today.$"

Nexus_Text_Katy_Pheromosa_ChampionIntro:
	.string "Oh my. Those precise steps could cross\n"
	.string "my kitchen without disturbing a\l"
	.string "dusting of flour. It seems quite\l"
	.string "offended by the floor.\p"
	.string "Even the footprints refuse to arrive\n"
	.string "together. Shall we offer a little\l"
	.string "tasteful competition?$"

Nexus_Text_Katy_Pheromosa_ChampionDefeat:
	.string "Beautifully done! You kept your\n"
	.string "balance through every turn.$"

Nexus_Text_Katy_Pheromosa_ChampionAfter:
	.string "{SPEAKER NAME_KATY}A flawless appearance can make\n"
	.string "everyone forget a creature might be\l"
	.string "uncomfortable. It is allowed to\l"
	.string "dislike the mess.\p"
	.string "Make a clean, quiet place for the\n"
	.string "little one afterward. Care needn't\l"
	.string "turn into a lesson about being less\l"
	.string "particular.$"

Nexus_Text_Klara_Munkidori_ChampionIntro:
	.string "It offered me the sweetest little\n"
	.string "smile. I almost thanked it for a\l"
	.string "headache I hadn't had yet!\p"
	.string "Someone else has been practicing\n"
	.string "charming entrances. How lovely. Let's\l"
	.string "see whose audience you turn out to be!$"

Nexus_Text_Klara_Munkidori_ChampionDefeat:
	.string "Oh, come ON! ...I mean, a very\n"
	.string "perceptive performance.$"

Nexus_Text_Klara_Munkidori_ChampionAfter:
	.string "{SPEAKER NAME_KLARA}A little suggestion can save so much\n"
	.string "effort. Then you can't tell whether\l"
	.string "anyone actually liked you.\p"
	.string "The small one afterward might\n"
	.string "appreciate a compliment it didn't\l"
	.string "arrange. I suppose we could both try\l"
	.string "hearing one honestly.$"

Nexus_Text_Klara_Eternatus_ChampionIntro:
	.string "All that poison, and it still knows\n"
	.string "how to make an entrance. The sky turns\l"
	.string "its color before it arrives!\p"
	.string "Don't look so impressed. I'm standing\n"
	.string "right here. You'll have to get through\l"
	.string "my performance first!$"

Nexus_Text_Klara_Eternatus_ChampionDefeat:
	.string "Bitter finish. Just terribly bitter.\n"
	.string "...Well played.$"

Nexus_Text_Klara_Eternatus_ChampionAfter:
	.string "{SPEAKER NAME_KLARA}Being noticed isn't much use when\n"
	.string "everyone only remembers the damage. I\l"
	.string "have learned that occasionally.\p"
	.string "Whatever little spark is left\n"
	.string "afterward, let it have attention\l"
	.string "without a disaster. A proper\l"
	.string "introduction might spare everyone a\p"
	.string "lot of poison.$"

Nexus_Text_Klara_Fezandipiti_ChampionIntro:
	.string "One flutter of those feathers and\n"
	.string "everyone adores it. No rehearsals, no\l"
	.string "aching cheeks. Honestly!\p"
	.string "Even the applause gets here before the\n"
	.string "smile. Well, you're about to see some\l"
	.string "actual effort. Ready, darling?$"

Nexus_Text_Klara_Fezandipiti_ChampionDefeat:
	.string "You saw through my sweetest opening.\n"
	.string "How deeply inconvenient.$"

Nexus_Text_Klara_Fezandipiti_ChampionAfter:
	.string "{SPEAKER NAME_KLARA}I'd say beauty is hard work, but that\n"
	.string "one seems determined to make me a\l"
	.string "liar.\p"
	.string "The little life afterward should learn\n"
	.string "how friendship feels without perfume\l"
	.string "doing the asking. ...I would like to\l"
	.string "know, too. Eventually.$"

Nexus_Text_Korrina_Urshifu_ChampionIntro:
	.string "One stance, one opening, one strike! I\n"
	.string "tried matching the timing, and the\l"
	.string "echo beat my wheels across the floor.\p"
	.string "A bond should move faster than a plan.\n"
	.string "Let's see how well yours flows!$"

Nexus_Text_Korrina_Urshifu_ChampionDefeat:
	.string "Whoa! You and your partner found the\n"
	.string "opening together!$"

Nexus_Text_Korrina_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_KORRINA}Grandpa taught me that a great power\n"
	.string "asks for a stronger bond. It's easy to\l"
	.string "remember the power and hurry past the\l"
	.string "rest.\p"
	.string "Practice the quiet moments with the\n"
	.string "little one afterward. That's where\l"
	.string "moving together begins.$"

Nexus_Text_Korrina_Koraidon_ChampionIntro:
	.string "That dragon hits the ground like it's\n"
	.string "challenging the whole road! The skid\l"
	.string "marks remember a race nobody started\l"
	.string "yet.\p"
	.string "My wheels are itching to answer. You\n"
	.string "and your team ready? Let's move!$"

Nexus_Text_Korrina_Koraidon_ChampionDefeat:
	.string "Now THAT was a proper response! I\n"
	.string "nearly forgot to brake!$"

Nexus_Text_Korrina_Koraidon_ChampionAfter:
	.string "{SPEAKER NAME_KORRINA}You can keep rolling after the reason\n"
	.string "for the race has disappeared. I've\l"
	.string "done that.\p"
	.string "The small life afterward doesn't need\n"
	.string "every road to be a contest. Take a\l"
	.string "slow lap together. Let it find out\l"
	.string "what else moving can mean.$"

Nexus_Text_Korrina_Zeraora_ChampionIntro:
	.string "It leaps off a spark like I push off\n"
	.string "the pavement! Except the spark is\l"
	.string "already waiting on the other side of\l"
	.string "the room.\p"
	.string "All right, partner, let's show a\n"
	.string "little footwork of our own!$"

Nexus_Text_Korrina_Zeraora_ChampionDefeat:
	.string "You read the landing before we got\n"
	.string "there! Amazing!$"

Nexus_Text_Korrina_Zeraora_ChampionAfter:
	.string "{SPEAKER NAME_KORRINA}I used to practice a trick until I\n"
	.string "could do it alone, then expect my\l"
	.string "partner to catch up. We've learned\l"
	.string "better.\p"
	.string "The little spark afterward will have\n"
	.string "its own timing. Listen for it. Sharing\l"
	.string "a rhythm beats making someone chase\l"
	.string "yours.$"

Nexus_Text_Larry_Terapagos_ChampionIntro:
	.string "The floor appears to contain several\n"
	.string "skies. A small shell seems\l"
	.string "responsible.\p"
	.string "I was hoping for a location with fewer\n"
	.string "reporting requirements. The reflection\l"
	.string "has already filed tomorrow's form. We\l"
	.string "should finish the battle first.$"

Nexus_Text_Larry_Terapagos_ChampionDefeat:
	.string "You managed the available space\n"
	.string "efficiently. I can respect that.$"

Nexus_Text_Larry_Terapagos_ChampionAfter:
	.string "{SPEAKER NAME_LARRY}Everyone calls a rare discovery\n"
	.string "exciting. Someone still has to check\l"
	.string "whether it has eaten.\p"
	.string "Whatever little life is left, see to\n"
	.string "that. A regular meal and a quiet place\l"
	.string "are perfectly respectable\l"
	.string "contributions to a miracle.$"

Nexus_Text_Larry_Tornadus_ChampionIntro:
	.string "The wind has scattered my paperwork\n"
	.string "into a day I am not scheduled to work.\l"
	.string "That seems excessive.\p"
	.string "The green one looks pleased. Let us\n"
	.string "complete a straightforward battle\l"
	.string "before it rearranges my lunch break as\l"
	.string "well.$"

Nexus_Text_Larry_Tornadus_ChampionDefeat:
	.string "That settles it. You adjusted better\n"
	.string "than my schedule did.$"

Nexus_Text_Larry_Tornadus_ChampionAfter:
	.string "{SPEAKER NAME_LARRY}I spend enough time being sent\n"
	.string "somewhere without being asked. I won't\l"
	.string "hold the creature's wandering against\l"
	.string "it.\p"
	.string "Give the small life afterward\n"
	.string "somewhere it is welcome to return. A\l"
	.string "destination can help more than another\l"
	.string "assignment.$"

Nexus_Text_Larry_Regigigas_ChampionIntro:
	.string "It seems to have been assigned the\n"
	.string "task of moving continents. I hope\l"
	.string "someone approved the overtime.\p"
	.string "The ground has begun shifting before\n"
	.string "it stands. We should conduct our\l"
	.string "business while the floor remains\l"
	.string "reasonably level.$"

Nexus_Text_Larry_Regigigas_ChampionDefeat:
	.string "Good preparation. You completed the\n"
	.string "task without wasting your team.$"

Nexus_Text_Larry_Regigigas_ChampionAfter:
	.string "{SPEAKER NAME_LARRY}Taking a long time to begin does not\n"
	.string "always mean someone is unwilling.\l"
	.string "Sometimes the load is simply enormous.\p"
	.string "Don't hand the little life afterward\n"
	.string "the same workload. Let it have a day\l"
	.string "without being useful to someone.$"

Nexus_Text_Lenora_Arceus_ChampionIntro:
	.string "Every stone tablet claims to be the\n"
	.string "first page. A museum director could\l"
	.string "spend a lifetime sorting this display.\p"
	.string "Something out there remembers the room\n"
	.string "before there was a floor. Let's see\l"
	.string "what your choices leave behind!$"

Nexus_Text_Lenora_Arceus_ChampionDefeat:
	.string "Now that's a record worth keeping!\n"
	.string "Every partner mattered.$"

Nexus_Text_Lenora_Arceus_ChampionAfter:
	.string "{SPEAKER NAME_LENORA}An origin story can tell people where\n"
	.string "they came from. It oughtn't decide\l"
	.string "every place they're allowed to go.\p"
	.string "The little life beyond those tablets\n"
	.string "is beginning now. Give it a history of\l"
	.string "its own, instead of a label under\l"
	.string "glass.$"

Nexus_Text_Lenora_Meloetta_ChampionIntro:
	.string "We have instruments in my museum whose\n"
	.string "players left no written names. I think\l"
	.string "I just heard one answer a song from an\l"
	.string "empty room.\p"
	.string "History has found its voice! Let's\n"
	.string "give it a lively question!$"

Nexus_Text_Lenora_Meloetta_ChampionDefeat:
	.string "A fine answer! Wish I'd recorded the\n"
	.string "whole performance!$"

Nexus_Text_Lenora_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_LENORA}A museum can preserve a melody and\n"
	.string "still forget the person who needed to\l"
	.string "sing it. That's something I try to\l"
	.string "watch for.\p"
	.string "The little voice afterward deserves an\n"
	.string "audience that will listen to a new\l"
	.string "song, too.$"

Nexus_Text_Lenora_Regirock_ChampionIntro:
	.string "Those stones belong to different ages.\n"
	.string "Someone reading only the surface would\l"
	.string "write a very confused label!\p"
	.string "The old tracks keep appearing ahead of\n"
	.string "its feet. Let's test how well your\l"
	.string "team holds its pieces together!$"

Nexus_Text_Lenora_Regirock_ChampionDefeat:
	.string "Solid work! You found the story\n"
	.string "connecting the separate parts.$"

Nexus_Text_Lenora_Regirock_ChampionAfter:
	.string "{SPEAKER NAME_LENORA}An object becomes more interesting\n"
	.string "when the evidence refuses the simple\l"
	.string "explanation. A living creature\l"
	.string "deserves at least that much patience.\p"
	.string "Help the little one afterward find\n"
	.string "pieces that fit today. We can honor\l"
	.string "its past without making it wear every\l"
	.string "century.$"

Nexus_Text_Leon_Eternatus_ChampionIntro:
	.string "Every stadium light is pointing\n"
	.string "inward. The stands remember a crowd\l"
	.string "that hasn't arrived, and the sky is\l"
	.string "already red.\p"
	.string "A Champion has to act before the\n"
	.string "cheering starts. Show me you're ready!$"

Nexus_Text_Leon_Eternatus_ChampionDefeat:
	.string "Brilliant! You kept your team together\n"
	.string "under all that pressure!$"

Nexus_Text_Leon_Eternatus_ChampionAfter:
	.string "{SPEAKER NAME_LEON}People think an undefeated record\n"
	.string "means never being afraid. It mostly\l"
	.string "means they don't see the moments\l"
	.string "before you act.\p"
	.string "Give the little life after that red\n"
	.string "storm a chance to be seen without a\l"
	.string "scoreboard. I'll try the same myself.$"

Nexus_Text_Leon_Zacian_ChampionIntro:
	.string "A sword's gleam has cut a path through\n"
	.string "the fog. Oddly, the path ends behind\l"
	.string "us. I may have taken a wrong turn.\p"
	.string "Still! A worthy challenger is right\n"
	.string "here. Let's make it a Champion time!$"

Nexus_Text_Leon_Zacian_ChampionDefeat:
	.string "A sharp performance! You earned that\n"
	.string "victory from the first turn!$"

Nexus_Text_Leon_Zacian_ChampionAfter:
	.string "{SPEAKER NAME_LEON}A title can become something you hold\n"
	.string "between yourself and everyone else.\l"
	.string "That blade seems to care more about\l"
	.string "who stands beside it.\p"
	.string "Stay close to the little beginning\n"
	.string "afterward. There are better directions\l"
	.string "than always trying to be first.$"

Nexus_Text_Leon_Urshifu_ChampionIntro:
	.string "One perfect strike, and the whole\n"
	.string "stadium seems to remember the impact\l"
	.string "before the fist moves.\p"
	.string "You can't rely on a crowd to tell you\n"
	.string "when the moment comes. Let's see if\l"
	.string "you can find it yourself!$"

Nexus_Text_Leon_Urshifu_ChampionDefeat:
	.string "You chose the moment and trusted your\n"
	.string "partner. Outstanding!$"

Nexus_Text_Leon_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_LEON}I spent years giving people the ending\n"
	.string "they expected. It's easy to forget\l"
	.string "that every battle still starts\l"
	.string "uncertain.\p"
	.string "The little pupil afterward deserves to\n"
	.string "lose a few practice bouts without\l"
	.string "losing your confidence. That's how a\l"
	.string "better answer grows.$"

Nexus_Text_Lorelei_Glastrier_ChampionIntro:
	.string "The hoofprints have frozen a harvest\n"
	.string "that has not been planted. Something\l"
	.string "out there considers the whole field\l"
	.string "its own.\p"
	.string "Confidence is useful. Possession is\n"
	.string "another matter. Let us see which your\l"
	.string "team has learned.$"

Nexus_Text_Lorelei_Glastrier_ChampionDefeat:
	.string "You stood firm without turning rigid.\n"
	.string "A sensible response.$"

Nexus_Text_Lorelei_Glastrier_ChampionAfter:
	.string "{SPEAKER NAME_LORELEI}A powerful creature can make every\n"
	.string "boundary look like a personal\l"
	.string "challenge. That does not make\l"
	.string "boundaries unkind.\p"
	.string "The little life afterward needs clear\n"
	.string "ones, and care on both sides. Even\l"
	.string "winter should leave somewhere warm to\l"
	.string "return to.$"

Nexus_Text_Lorelei_Kyurem_ChampionIntro:
	.string "The ice preserves the outline of an\n"
	.string "absence. No matter how cold the room\l"
	.string "grows, the empty place remains.\p"
	.string "I know how a beautiful surface can\n"
	.string "hide dangerous depths. Show me that\l"
	.string "you do, too.$"

Nexus_Text_Lorelei_Kyurem_ChampionDefeat:
	.string "You watched beneath the surface. That\n"
	.string "kept you standing.$"

Nexus_Text_Lorelei_Kyurem_ChampionAfter:
	.string "{SPEAKER NAME_LORELEI}We can spend years maintaining a\n"
	.string "perfect outline of something already\l"
	.string "gone. I have kept a few such things\l"
	.string "myself.\p"
	.string "Whatever small beginning remains, do\n"
	.string "not ask it to fill an old shape. Learn\l"
	.string "who has actually come to stay.$"

Nexus_Text_Lorelei_Articuno_ChampionIntro:
	.string "A single feather carries the cold of a\n"
	.string "mountain I cannot find on any map. Its\l"
	.string "shadow remembers the snow before it\l"
	.string "falls.\p"
	.string "Elegance is no substitute for\n"
	.string "preparation. We shall test yours.$"

Nexus_Text_Lorelei_Articuno_ChampionDefeat:
	.string "A clean victory. You respected the\n"
	.string "cold without fearing it.$"

Nexus_Text_Lorelei_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_LORELEI}I grew up learning which water was\n"
	.string "safe to cross. A beautiful frozen\l"
	.string "surface never gave enough information.\p"
	.string "Give the little life afterward\n"
	.string "practical care as well as admiration.\l"
	.string "A warm place to rest will mean more\l"
	.string "than a perfect description.$"

Nexus_Text_Lysandre_Yveltal_ChampionIntro:
	.string "Its wings gather the last breath of a\n"
	.string "world. This room has already prepared\l"
	.string "a silence for the lives not yet born.\p"
	.string "Beauty is always asked to pay for the\n"
	.string "hunger around it. Show me what you\l"
	.string "would preserve.$"

Nexus_Text_Lysandre_Yveltal_ChampionDefeat:
	.string "You still refuse the necessity of an\n"
	.string "ending. Even after that display.$"

Nexus_Text_Lysandre_Yveltal_ChampionAfter:
	.string "{SPEAKER NAME_LYSANDRE}I thought one final act could spare\n"
	.string "beauty the indignity of being\l"
	.string "consumed. The shadow answers by\l"
	.string "consuming everything.\p"
	.string "Take the small remainder. Perhaps you\n"
	.string "can tolerate watching something\l"
	.string "precious become a thing you never\l"
	.string "intended. I found that difficult.$"

Nexus_Text_Lysandre_Xerneas_ChampionIntro:
	.string "Those antlers offer life without\n"
	.string "examining who receives it. An\l"
	.string "extravagant generosity.\p"
	.string "The flowers bloom here before anyone\n"
	.string "has decided whether they deserve the\l"
	.string "earth. Let us test your own judgment.$"

Nexus_Text_Lysandre_Xerneas_ChampionDefeat:
	.string "Such strength, spent so freely. I\n"
	.string "cannot call it careless.$"

Nexus_Text_Lysandre_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_LYSANDRE}I wanted to preserve the beautiful\n"
	.string "things exactly as I loved them. Life\l"
	.string "seems determined to change its shape.\p"
	.string "The little beginning afterward will\n"
	.string "change as well. If you can welcome\l"
	.string "that, perhaps you grasp something\l"
	.string "my plans could not contain.$"

Nexus_Text_Lysandre_Volcanion_ChampionIntro:
	.string "Fire and water held together by\n"
	.string "pressure. A controlled force can\l"
	.string "accomplish so much.\p"
	.string "Yet the steam remembers a sealed room\n"
	.string "bursting open tomorrow. Show me\l"
	.string "whether you can command power without\l"
	.string "losing its purpose.$"

Nexus_Text_Lysandre_Volcanion_ChampionDefeat:
	.string "You released the pressure at the right\n"
	.string "moment. A rare restraint.$"

Nexus_Text_Lysandre_Volcanion_ChampionAfter:
	.string "{SPEAKER NAME_LYSANDRE}I built my plans around the belief\n"
	.string "that the world must be forced into a\l"
	.string "better shape. This creature carries a\l"
	.string "different kind of balance.\p"
	.string "The little life afterward needs a\n"
	.string "home, not a place in a design. I can\l"
	.string "recognize the distinction, at least.$"

Nexus_Text_Marnie_GalarianMoltres_ChampionIntro:
	.string "Those flames burn dark, but they still\n"
	.string "make a shadow. Funny thing is, the\l"
	.string "shadow seems to have more nerve than\l"
	.string "the room.\p"
	.string "I know what people say about a\n"
	.string "frightening face. Let's give them\l"
	.string "something better to talk about.$"

Nexus_Text_Marnie_GalarianMoltres_ChampionDefeat:
	.string "You kept your head. Fair play to you.$"

Nexus_Text_Marnie_GalarianMoltres_ChampionAfter:
	.string "{SPEAKER NAME_MARNIE}People back home have been called\n"
	.string "rough enough times to expect it.\l"
	.string "Doesn't mean the words don't land.\p"
	.string "Give the little ember afterward a\n"
	.string "welcome before you start explaining\l"
	.string "it. A place to belong can do more than\l"
	.string "a better reputation.$"

Nexus_Text_Marnie_Yveltal_ChampionIntro:
	.string "The wings have folded, and every voice\n"
	.string "seems to be waiting for the silence\l"
	.string "after them.\p"
	.string "My fans would make enough noise to\n"
	.string "test that. I'll have to do the work\l"
	.string "myself. Ready?$"

Nexus_Text_Marnie_Yveltal_ChampionDefeat:
	.string "You didn't let the quiet make the\n"
	.string "decision for you. Good.$"

Nexus_Text_Marnie_Yveltal_ChampionAfter:
	.string "{SPEAKER NAME_MARNIE}Spikemuth isn't a lost cause because\n"
	.string "someone else stopped listening.\l"
	.string "Neither is a life because it looks\l"
	.string "like an ending.\p"
	.string "The small beginning afterward deserves\n"
	.string "a chance without a crowd deciding what\l"
	.string "it means. Stand beside it. That's a\l"
	.string "start.$"

Nexus_Text_Marnie_Darkrai_ChampionIntro:
	.string "It keeps away from the sleepers, even\n"
	.string "when the dreams follow it. The empty\l"
	.string "beds remember being frightened first.\p"
	.string "I know how hard it is to answer a\n"
	.string "reputation. Let's see how your team\l"
	.string "handles the dark.$"

Nexus_Text_Marnie_Darkrai_ChampionDefeat:
	.string "You looked after your partners even\n"
	.string "when you couldn't see the next move.$"

Nexus_Text_Marnie_Darkrai_ChampionAfter:
	.string "{SPEAKER NAME_MARNIE}Being left alone isn't always what a\n"
	.string "quiet person wants. Sometimes it's\l"
	.string "simply what everyone decided was\l"
	.string "easiest.\p"
	.string "Leave the little one afterward a\n"
	.string "choice. A quiet corner, and someone\l"
	.string "willing to share it when asked. No\l"
	.string "fuss needed.$"

Nexus_Text_Melony_Calyrex_ChampionIntro:
	.string "A crown sits above a very determined\n"
	.string "pair of eyes. The bare field is\l"
	.string "already preparing a harvest.\p"
	.string "I recognize the look of someone trying\n"
	.string "to care for everyone without admitting\l"
	.string "they're tired. Come, love. Let's warm\l"
	.string "up!$"

Nexus_Text_Melony_Calyrex_ChampionDefeat:
	.string "Lovely teamwork! I hope every one of\n"
	.string "you knows it.$"

Nexus_Text_Melony_Calyrex_ChampionAfter:
	.string "{SPEAKER NAME_MELONY}Children notice when you are worried,\n"
	.string "however warmly you smile. I imagine a\l"
	.string "whole field does the same.\p"
	.string "Let the little one afterward be cared\n"
	.string "for in return. A crown is no reason to\l"
	.string "expect someone never to need a\l"
	.string "blanket.$"

Nexus_Text_Melony_Articuno_ChampionIntro:
	.string "Such lovely feathers! The snowfall has\n"
	.string "arranged itself like an audience\l"
	.string "before the bird arrives.\p"
	.string "Now, don't let the pretty scene make\n"
	.string "you careless, love. A warm welcome can\l"
	.string "still lead to a very chilly battle!$"

Nexus_Text_Melony_Articuno_ChampionDefeat:
	.string "Beautifully handled! You kept moving\n"
	.string "without losing your composure.$"

Nexus_Text_Melony_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_MELONY}I always want my children to have\n"
	.string "somewhere warm to come back to,\l"
	.string "however far their ambitions take them.\p"
	.string "Offer the little life afterward the\n"
	.string "same. It can love the snow and still\l"
	.string "appreciate someone waiting with a safe\l"
	.string "place to rest.$"

Nexus_Text_Melony_Glastrier_ChampionIntro:
	.string "That one has stamped its claim on the\n"
	.string "whole field. I have seen a smaller\l"
	.string "version of that look over the last\l"
	.string "helping at dinner.\p"
	.string "The frost got here before the hoof.\n"
	.string "Let's practice keeping our balance,\l"
	.string "shall we?$"

Nexus_Text_Melony_Glastrier_ChampionDefeat:
	.string "Very nicely done! Firm, without making\n"
	.string "a scene.$"

Nexus_Text_Melony_Glastrier_ChampionAfter:
	.string "{SPEAKER NAME_MELONY}A stubborn spirit can grow into\n"
	.string "admirable determination. It still\l"
	.string "needs someone who will say enough.\p"
	.string "The little one afterward deserves\n"
	.string "patient teaching. And the teacher\l"
	.string "deserves a rest now and then. I remind\l"
	.string "myself of that surprisingly often.$"

Nexus_Text_Molly_Entei_ChampionIntro:
	.string "I heard that roar and remembered a\n"
	.string "room where every wish could have\l"
	.string "walls. Here, the walls arrive before I\l"
	.string "ask.\p"
	.string "I am grown now. I know a friend isn't\n"
	.string "something you invent to win. Would you\l"
	.string "meet mine?$"

Nexus_Text_Molly_Entei_ChampionDefeat:
	.string "We lost, and everyone is still here.\n"
	.string "That's what matters.$"

Nexus_Text_Molly_Entei_ChampionAfter:
	.string "{SPEAKER NAME_MOLLY}Once, I wanted a father who could make\n"
	.string "every frightening thing disappear. The\l"
	.string "world couldn't live inside that wish.\p"
	.string "The little life beyond the roar\n"
	.string "doesn't owe me an old dream. I'll be\l"
	.string "glad if it gets to have dreams of its\l"
	.string "own.$"

Nexus_Text_Molly_Xerneas_ChampionIntro:
	.string "The flowers keep opening into rooms\n"
	.string "from my childhood. Their colors are\l"
	.string "brighter than the windows were.\p"
	.string "I used to want a world that would\n"
	.string "never disappoint me. These days, I'd\l"
	.string "rather have friends who can surprise\l"
	.string "me. Shall we?$"

Nexus_Text_Molly_Xerneas_ChampionDefeat:
	.string "You gave everyone a chance to stay\n"
	.string "part of the story.$"

Nexus_Text_Molly_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_MOLLY}Something can be beautiful without\n"
	.string "promising it will last forever. I\l"
	.string "didn't understand that when I was\l"
	.string "small.\p"
	.string "Let the little life afterward grow\n"
	.string "past your favorite memory of it.\l"
	.string "Loving someone should leave enough\l"
	.string "room for the next day.$"

Nexus_Text_Molly_Cresselia_ChampionIntro:
	.string "A quiet light is resting on the bed of\n"
	.string "a room I only remember. Nobody has to\l"
	.string "dream it into being.\p"
	.string "I used to be afraid of what waking up\n"
	.string "would take away. Let's make something\l"
	.string "real together, just for a battle.$"

Nexus_Text_Molly_Cresselia_ChampionDefeat:
	.string "I can wake up from this and still be\n"
	.string "glad we met.$"

Nexus_Text_Molly_Cresselia_ChampionAfter:
	.string "{SPEAKER NAME_MOLLY}A kind dream can shelter you for a\n"
	.string "night. It cannot be the whole house\l"
	.string "forever.\p"
	.string "If a little life is left in that\n"
	.string "moonlight, give it gentle mornings\l"
	.string "too. Someone can be there when the\l"
	.string "beautiful part ends. That helps.$"

Nexus_Text_Mustard_Urshifu_ChampionIntro:
	.string "Heh heh! One strike, and every hour of\n"
	.string "practice stands behind it. Here, the\l"
	.string "hours seem to have queued on the wrong\l"
	.string "side.\p"
	.string "Never mind the clock. Show this old\n"
	.string "man your best opening!$"

Nexus_Text_Mustard_Urshifu_ChampionDefeat:
	.string "Ho ho! You found the moment before I\n"
	.string "could close it!$"

Nexus_Text_Mustard_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_MUSTARD}Students sometimes ask for the secret\n"
	.string "technique before they have learned how\l"
	.string "to sit quietly together. They do enjoy\l"
	.string "skipping the useful bits.\p"
	.string "Give the little pupil afterward a\n"
	.string "patient friend. The punch can wait. I\l"
	.string "promise it won't escape.$"

Nexus_Text_Mustard_Koraidon_ChampionIntro:
	.string "That old dragon looks as though it has\n"
	.string "challenged every road it ever crossed!\l"
	.string "One skid mark here leads straight into\l"
	.string "next week.\p"
	.string "Good spirit. Poor braking. Let's see\n"
	.string "how you manage an unexpected turn!$"

Nexus_Text_Mustard_Koraidon_ChampionDefeat:
	.string "Ha! You changed your footing without\n"
	.string "losing your purpose!$"

Nexus_Text_Mustard_Koraidon_ChampionAfter:
	.string "{SPEAKER NAME_MUSTARD}I used to enjoy pushing a student\n"
	.string "until the old plan broke. These days I\l"
	.string "pay closer attention to what breaks\l"
	.string "with it.\p"
	.string "Let the little one afterward feel safe\n"
	.string "enough to stop. Starting again is\l"
	.string "easier with a place to rest.$"

Nexus_Text_Mustard_Marshadow_ChampionIntro:
	.string "There's a quiet pupil taking notes in\n"
	.string "my shadow. No notebook, of course.\l"
	.string "Just very good feet.\p"
	.string "It copied tomorrow's stance before I\n"
	.string "thought of it. Heh! Better give it\l"
	.string "something new to study!$"

Nexus_Text_Mustard_Marshadow_ChampionDefeat:
	.string "Well now! Even the little watcher\n"
	.string "missed that opening!$"

Nexus_Text_Mustard_Marshadow_ChampionAfter:
	.string "{SPEAKER NAME_MUSTARD}I've taught plenty of champions. The\n"
	.string "ones who stayed curious learned more\l"
	.string "after the title than before it.\p"
	.string "Let the little shadow afterward try a\n"
	.string "move you never taught. Being a teacher\l"
	.string "is partly learning to enjoy being\l"
	.string "surprised.$"

Nexus_Text_N_Zekrom_ChampionIntro:
	.string "It hears an ideal and answers with\n"
	.string "thunder. I once believed the loudest\l"
	.string "answer must be the clearest.\p"
	.string "Here, the thunder has arrived before\n"
	.string "the question. I would like to hear\l"
	.string "what your partners choose.$"

Nexus_Text_N_Zekrom_ChampionDefeat:
	.string "Their voices agreed without becoming\n"
	.string "one voice. That matters.$"

Nexus_Text_N_Zekrom_ChampionAfter:
	.string "{SPEAKER NAME_N}An ideal can make a cage if you decide\n"
	.string "it belongs to everyone. I have stood\l"
	.string "inside such a cage and called it\l"
	.string "freedom.\p"
	.string "The small beginning afterward should\n"
	.string "have a voice in the world you offer\l"
	.string "it. Listen, even when it disagrees.$"

Nexus_Text_N_Reshiram_ChampionIntro:
	.string "The flame is very quiet until someone\n"
	.string "says something they do not believe.\l"
	.string "Then the room seems to remember\l"
	.string "another version of the words.\p"
	.string "I am still learning to hear that\n"
	.string "difference in myself. Will you show me\l"
	.string "your answer?$"

Nexus_Text_N_Reshiram_ChampionDefeat:
	.string "They trusted what you meant. I could\n"
	.string "hear it.$"

Nexus_Text_N_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_N}I was taught a truth that left out\n"
	.string "every voice capable of questioning it.\l"
	.string "The white flame does not make that\l"
	.string "truth more complete.\p"
	.string "Let the little life afterward ask\n"
	.string "questions you cannot answer. You may\l"
	.string "both learn something worth keeping.$"

Nexus_Text_N_Silvally_ChampionIntro:
	.string "It was given a purpose before anyone\n"
	.string "asked whether it wanted one. Then it\l"
	.string "broke the thing that made refusal\l"
	.string "impossible.\p"
	.string "The mask's echo still gives orders\n"
	.string "here. I would rather hear your\l"
	.string "partners.$"

Nexus_Text_N_Silvally_ChampionDefeat:
	.string "They answered you freely. The\n"
	.string "difference is unmistakable.$"

Nexus_Text_N_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_N}Freedom is not simply a broken\n"
	.string "restraint. Someone has to leave enough\l"
	.string "space for the next choice.\p"
	.string "The little beginning afterward may\n"
	.string "need help before it can choose much at\l"
	.string "all. Help it without quietly deciding\l"
	.string "the rest of its life.$"

Nexus_Text_Nemona_Koraidon_ChampionIntro:
	.string "That dragon just challenged a cliff by\n"
	.string "running into it! The cliff moved aside\l"
	.string "before the impact.\p"
	.string "Okay, maybe the cliff is strange. The\n"
	.string "enthusiasm is PERFECT. You and me\l"
	.string "first! Let's battle!$"

Nexus_Text_Nemona_Koraidon_ChampionDefeat:
	.string "YES! That was exactly the kind of\n"
	.string "answer I wanted!$"

Nexus_Text_Nemona_Koraidon_ChampionAfter:
	.string "{SPEAKER NAME_NEMONA}I keep asking whether someone is ready\n"
	.string "for another battle. Sometimes I should\l"
	.string "ask what else they'd enjoy.\p"
	.string "The little one afterward might love\n"
	.string "racing as much as I do. Or it might\l"
	.string "want a nap. I can learn to wait.\l"
	.string "Probably.$"

Nexus_Text_Nemona_WalkingWake_ChampionIntro:
	.string "It ran right across the water! The\n"
	.string "splashes are still waiting for the\l"
	.string "river to appear!\p"
	.string "I've never seen footwork like that. My\n"
	.string "team wants to try keeping up. Please\l"
	.string "tell me yours is ready too!$"

Nexus_Text_Nemona_WalkingWake_ChampionDefeat:
	.string "Amazing! You found your rhythm without\n"
	.string "copying mine!$"

Nexus_Text_Nemona_WalkingWake_ChampionAfter:
	.string "{SPEAKER NAME_NEMONA}That fierce silhouette keeps\n"
	.string "surprising people who expected a\l"
	.string "gentler story. I like meeting the\l"
	.string "creature before deciding how it ought\p"
	.string "to move.\p"
	.string "Let the little beginning afterward\n"
	.string "show you its own favorite game.\l"
	.string "There's always something new to learn\l"
	.string "together.$"

Nexus_Text_Nemona_IronValiant_ChampionIntro:
	.string "A fighter that looks ready for every\n"
	.string "possible challenger? Oh, I HAVE to see\l"
	.string "it move!\p"
	.string "Its blade's reflection is already\n"
	.string "finishing tomorrow's match. First,\l"
	.string "let's give it a really good one to\l"
	.string "watch today!$"

Nexus_Text_Nemona_IronValiant_ChampionDefeat:
	.string "That was incredible! Your choices were\n"
	.string "better than any perfect prediction!$"

Nexus_Text_Nemona_IronValiant_ChampionAfter:
	.string "{SPEAKER NAME_NEMONA}When everyone expects you to win,\n"
	.string "asking for help can feel harder than\l"
	.string "the battle. I know that one.\p"
	.string "Give the little fighter afterward\n"
	.string "permission to get things wrong. It\l"
	.string "deserves a partner it doesn't have to\l"
	.string "impress all the time.$"

Nexus_Text_Nessa_Kyogre_ChampionIntro:
	.string "The tide has filled a horizon that has\n"
	.string "not been drawn. Beneath that surface,\l"
	.string "something vast is turning.\p"
	.string "A calm face tells you very little\n"
	.string "about the current. Take your stance.\l"
	.string "I'll show you.$"

Nexus_Text_Nessa_Kyogre_ChampionDefeat:
	.string "You read the current and held your\n"
	.string "ground. Well done.$"

Nexus_Text_Nessa_Kyogre_ChampionAfter:
	.string "{SPEAKER NAME_NESSA}I have two careers, and people keep\n"
	.string "asking which one is the real me. The\l"
	.string "sea doesn't divide its depths that\l"
	.string "neatly.\p"
	.string "Let the little life afterward be more\n"
	.string "than the power you first saw. There is\l"
	.string "always more below the surface.$"

Nexus_Text_Nessa_TapuFini_ChampionIntro:
	.string "The mist keeps showing a shore I can't\n"
	.string "place. Each time I approach, it\l"
	.string "remembers being farther away.\p"
	.string "That guardian decides who gets to\n"
	.string "cross. Let's see whether you can keep\l"
	.string "your heading when the view changes.$"

Nexus_Text_Nessa_TapuFini_ChampionDefeat:
	.string "You trusted your team without trusting\n"
	.string "every reflection. Sensible.$"

Nexus_Text_Nessa_TapuFini_ChampionAfter:
	.string "{SPEAKER NAME_NESSA}A beautiful surface can show you\n"
	.string "exactly what you want to see. That\l"
	.string "doesn't mean the water is lying. You\l"
	.string "still have to look carefully.\p"
	.string "Give the small life afterward honest\n"
	.string "company. It shouldn't need a mist to\l"
	.string "be understood.$"

Nexus_Text_Nessa_Suicune_ChampionIntro:
	.string "The north wind has touched every pool\n"
	.string "at once. Clear water runs along a path\l"
	.string "the ground has forgotten.\p"
	.string "There's strength in leaving a place\n"
	.string "better than you found it. Show me how\l"
	.string "your team handles a clean current.$"

Nexus_Text_Nessa_Suicune_ChampionDefeat:
	.string "A precise finish. No wasted force, no\n"
	.string "partner left behind.$"

Nexus_Text_Nessa_Suicune_ChampionAfter:
	.string "{SPEAKER NAME_NESSA}When I get a quiet morning by the\n"
	.string "water, I remember why I started\l"
	.string "training before anyone took my\l"
	.string "photograph.\p"
	.string "Keep the little one's water clean\n"
	.string "afterward. Some of the best care is\l"
	.string "ordinary enough that nobody thinks to\l"
	.string "watch it.$"

Nexus_Text_Olivia_TapuLele_ChampionIntro:
	.string "Those scales shine like jewelry, but\n"
	.string "you can feel them closing every little\l"
	.string "hurt. The flowers look almost too\l"
	.string "comfortable.\p"
	.string "A gem can be overworked. So can\n"
	.string "kindness. Let's test your touch!$"

Nexus_Text_Olivia_TapuLele_ChampionDefeat:
	.string "You knew when to press and when to\n"
	.string "ease off. Nicely cut!$"

Nexus_Text_Olivia_TapuLele_ChampionAfter:
	.string "{SPEAKER NAME_OLIVIA}A kahuna learns to help without\n"
	.string "keeping everybody inside a helpful\l"
	.string "little box. Some days, I learn it\l"
	.string "again.\p"
	.string "Let the small one afterward hear a\n"
	.string "loving no. Even a blessing needs\l"
	.string "someone willing to set a limit.$"

Nexus_Text_Olivia_Necrozma_ChampionIntro:
	.string "Light is caught in every dark facet.\n"
	.string "The whole room is waiting for a\l"
	.string "sunrise that seems to have happened\l"
	.string "inside it.\p"
	.string "I've worked with stubborn stones. This\n"
	.string "one deserves more than a jeweler's\l"
	.string "eye. Ready?$"

Nexus_Text_Olivia_Necrozma_ChampionDefeat:
	.string "You found the angle without forcing\n"
	.string "the stone. Good work!$"

Nexus_Text_Olivia_Necrozma_ChampionAfter:
	.string "{SPEAKER NAME_OLIVIA}When a gem is cut too far, more\n"
	.string "pressure won't restore what it lost.\l"
	.string "You have to understand what is still\l"
	.string "there.\p"
	.string "The small life after that broken light\n"
	.string "needs care more than polishing. Let it\l"
	.string "shine in whatever way it can.$"

Nexus_Text_Olivia_Diancie_ChampionIntro:
	.string "A jewel that makes more jewels! I\n"
	.string "should be delighted. Instead, I'm\l"
	.string "wondering who ever asks whether it\l"
	.string "would like a day off.\p"
	.string "These crystals remember the hammer\n"
	.string "before it was lifted. Let's use a\l"
	.string "lighter touch, shall we?$"

Nexus_Text_Olivia_Diancie_ChampionDefeat:
	.string "A beautiful finish! Nothing precious\n"
	.string "had to be broken.$"

Nexus_Text_Olivia_Diancie_ChampionAfter:
	.string "{SPEAKER NAME_OLIVIA}I've sold people stones for promises,\n"
	.string "apologies, and beginnings. The stone\l"
	.string "never does the work of keeping the\l"
	.string "promise.\p"
	.string "Give the little life afterward\n"
	.string "something beyond admiration. Show up,\l"
	.string "feed it, listen. That's a setting\l"
	.string "worth growing into.$"

Nexus_Text_Peonia_Lugia_ChampionIntro:
	.string "Dad's notes would call those wings a\n"
	.string "legendary discovery in enormous\l"
	.string "letters. I rather like how quietly\l"
	.string "they're folded.\p"
	.string "The sea here remembers a storm that\n"
	.string "never happened. Fancy a battle before\l"
	.string "anyone gets a banner out?$"

Nexus_Text_Peonia_Lugia_ChampionDefeat:
	.string "Now that was worth the detour! You\n"
	.string "read the air perfectly!$"

Nexus_Text_Peonia_Lugia_ChampionAfter:
	.string "{SPEAKER NAME_PEONIA}I keep choosing a different path so\n"
	.string "the adventure will feel like mine.\l"
	.string "That quiet giant chose an entire sea\l"
	.string "to find some peace.\p"
	.string "Leave the little one afterward a\n"
	.string "choice of its own. An invitation works\l"
	.string "better than an itinerary.$"

Nexus_Text_Peonia_Suicune_ChampionIntro:
	.string "A north wind just turned my map into a\n"
	.string "very damp suggestion. The pawprints on\l"
	.string "it lead to a lake I've never visited.\p"
	.string "Dad would be halfway through a title\n"
	.string "by now. I'd rather have a battle. You\l"
	.string "in?$"

Nexus_Text_Peonia_Suicune_ChampionDefeat:
	.string "Brilliant! A clear head beats a\n"
	.string "perfect route!$"

Nexus_Text_Peonia_Suicune_ChampionAfter:
	.string "{SPEAKER NAME_PEONIA}Sometimes I want to go somewhere\n"
	.string "simply because nobody has decided it\l"
	.string "for me. That traveler seems to\l"
	.string "understand.\p"
	.string "Keep a place for the little one\n"
	.string "afterward, but don't make staying the\l"
	.string "price of your help. A welcome can\l"
	.string "survive a journey.$"

Nexus_Text_Peonia_Articuno_ChampionIntro:
	.string "The snow has arranged a trail behind\n"
	.string "those wings. Somehow the destination\l"
	.string "is already written beside our starting\l"
	.string "point.\p"
	.string "A shortcut, or a very elaborate\n"
	.string "detour? Let's warm up before we find\l"
	.string "out!$"

Nexus_Text_Peonia_Articuno_ChampionDefeat:
	.string "Lovely work! You handled the slippery\n"
	.string "part better than I did!$"

Nexus_Text_Peonia_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_PEONIA}Dad would worry himself hoarse if he\n"
	.string "knew half the cold places I've chosen\l"
	.string "to visit. I do appreciate the concern.\l"
	.string "From a distance.\p"
	.string "The small life afterward can have both\n"
	.string "shelter and room to explore. They're\l"
	.string "not difficult things to offer\l"
	.string "together.$"

Nexus_Text_Peony_Registeel_ChampionIntro:
	.string "Now THERE'S a metal mystery! No seam,\n"
	.string "no maker's mark, and it won't even\l"
	.string "dent my notes for a rubbing!\p"
	.string "The ring of my hammer got here first.\n"
	.string "Right, chief! Let's hear what your\l"
	.string "team can do!$"

Nexus_Text_Peony_Registeel_ChampionDefeat:
	.string "Ha! Solid work! I'll need a bigger\n"
	.string "notebook for that!$"

Nexus_Text_Peony_Registeel_ChampionAfter:
	.string "{SPEAKER NAME_PEONY}I get carried away writing grand\n"
	.string "titles. The creature's still standing\l"
	.string "there waiting for me to notice it.\p"
	.string "The little one afterward deserves a\n"
	.string "proper welcome before the next\l"
	.string "expedition. Take it from a dad who's\l"
	.string "missed that cue a few times.$"

Nexus_Text_Peony_Calyrex_ChampionIntro:
	.string "A tiny crown, a huge presence, and\n"
	.string "crops rising through stone! That's an\l"
	.string "expedition all by itself!\p"
	.string "The harvest has tomorrow's date.\n"
	.string "Right! We'll start by testing today's\l"
	.string "teamwork. Ready, chief?$"

Nexus_Text_Peony_Calyrex_ChampionDefeat:
	.string "What a discovery! You stood together\n"
	.string "without needing a royal order!$"

Nexus_Text_Peony_Calyrex_ChampionAfter:
	.string "{SPEAKER NAME_PEONY}A grand title doesn't stop someone\n"
	.string "needing a good meal. Or company. Easy\l"
	.string "things to forget when you're busy\l"
	.string "being impressed.\p"
	.string "Sit with the little one afterward. You\n"
	.string "can write the glorious chapter once\l"
	.string "it's had dinner.$"

Nexus_Text_Peony_Dialga_ChampionIntro:
	.string "Metal plates, a mighty roar, and every\n"
	.string "clock in my pack claiming I missed\l"
	.string "breakfast!\p"
	.string "The shadow says I'm here next\n"
	.string "Thursday. Never mind that, chief! A\l"
	.string "battle will tell us where we stand!$"

Nexus_Text_Peony_Dialga_ChampionDefeat:
	.string "Ha! Your timing was a sight worth the\n"
	.string "whole expedition!$"

Nexus_Text_Peony_Dialga_ChampionAfter:
	.string "{SPEAKER NAME_PEONY}I keep planning another trip with my\n"
	.string "daughter. Time with her somehow slips\l"
	.string "away while I'm making the plans.\p"
	.string "Spend an ordinary hour with the little\n"
	.string "one afterward. No legend in the world\l"
	.string "can do that hour for you.$"

Nexus_Text_Rowan_Dialga_ChampionIntro:
	.string "Time has left several ages of the same\n"
	.string "footprint in this floor. The creature\l"
	.string "beyond it appears unchanged.\p"
	.string "Evolution is my field. A world without\n"
	.string "a reliable sequence complicates the\l"
	.string "question. Show me how you respond to\l"
	.string "change.$"

Nexus_Text_Rowan_Dialga_ChampionDefeat:
	.string "Good. You adapted instead of insisting\n"
	.string "on your first conclusion.$"

Nexus_Text_Rowan_Dialga_ChampionAfter:
	.string "{SPEAKER NAME_ROWAN}A lifetime of study has taught me to\n"
	.string "distrust the word finished. Even a\l"
	.string "creature that seems timeless still\l"
	.string "meets new circumstances.\p"
	.string "The small beginning afterward needs\n"
	.string "time to become itself. Give it that\l"
	.string "before you ask for proof of a theory.$"

Nexus_Text_Rowan_Uxie_ChampionIntro:
	.string "There is a gap in my notes where a\n"
	.string "useful observation should be. The\l"
	.string "handwriting on either side is mine.\p"
	.string "Knowledge can be lost without a page\n"
	.string "being torn. Let us establish what you\l"
	.string "understand through practice.$"

Nexus_Text_Rowan_Uxie_ChampionDefeat:
	.string "Sound judgment. You knew why your next\n"
	.string "move mattered.$"

Nexus_Text_Rowan_Uxie_ChampionAfter:
	.string "{SPEAKER NAME_ROWAN}Collecting facts is easier than\n"
	.string "admitting which one your explanation\l"
	.string "cannot hold. I expect that honesty\l"
	.string "from my students and myself.\p"
	.string "Meet the little one afterward without\n"
	.string "pretending to know it already. Years\l"
	.string "of study are a reason to listen\l"
	.string "carefully.$"

Nexus_Text_Rowan_Silvally_ChampionIntro:
	.string "It was engineered toward a prescribed\n"
	.string "result. Its decisive change followed a\l"
	.string "bond its makers could not command.\p"
	.string "The broken mask here remembers both\n"
	.string "outcomes. Show me which conditions\l"
	.string "your partners grow under.$"

Nexus_Text_Rowan_Silvally_ChampionDefeat:
	.string "You allowed the response to develop.\n"
	.string "Sensible training.$"

Nexus_Text_Rowan_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_ROWAN}People call evolution a change of form\n"
	.string "and forget the conditions that make\l"
	.string "change possible. Trust deserves closer\l"
	.string "attention.\p"
	.string "Care for the small life afterward\n"
	.string "without demanding a result. A\l"
	.string "relationship is not an experiment you\l"
	.string "abandon when the data surprises you.$"

Nexus_Text_Rosa_Reshiram_ChampionIntro:
	.string "The white flame keeps lighting a face\n"
	.string "I haven't made yet. I tried a camera\l"
	.string "smile, and the fire went very still.\p"
	.string "Okay! An honest battle should help.\n"
	.string "Let's give it something real!$"

Nexus_Text_Rosa_Reshiram_ChampionDefeat:
	.string "There it is! A real smile, even after\n"
	.string "losing!$"

Nexus_Text_Rosa_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_ROSA}On a set, somebody tells you what the\n"
	.string "brave person says. In a battle, you\l"
	.string "have to decide whether you mean it.\p"
	.string "Let the little life afterward see you\n"
	.string "when the scene is over. Trust grows in\l"
	.string "those untidy moments between the\l"
	.string "speeches.$"

Nexus_Text_Rosa_Virizion_ChampionIntro:
	.string "Such elegant steps! The grass bends\n"
	.string "around them as though it remembers a\l"
	.string "dancer from another age.\p"
	.string "But those eyes are watching for\n"
	.string "someone to protect. Let's show it a\l"
	.string "team worth looking after!$"

Nexus_Text_Rosa_Virizion_ChampionDefeat:
	.string "A lovely combination! Every partner\n"
	.string "had someone at its side!$"

Nexus_Text_Rosa_Virizion_ChampionAfter:
	.string "{SPEAKER NAME_ROSA}I used to worry about looking like a\n"
	.string "hero. That forest guardian seems more\l"
	.string "interested in noticing who needs help.\p"
	.string "The little one afterward won't care\n"
	.string "about the camera. Be there when it\l"
	.string "needs you, even if the moment looks\l"
	.string "ordinary.$"

Nexus_Text_Rosa_Meloetta_ChampionIntro:
	.string "A song without a soundtrack! It\n"
	.string "changed the rhythm while the room was\l"
	.string "still waiting for the first note.\p"
	.string "That's a cue even I can't miss. Ready\n"
	.string "to give it a proper scene?$"

Nexus_Text_Rosa_Meloetta_ChampionDefeat:
	.string "What a finish! Nobody could have\n"
	.string "scripted that smile!$"

Nexus_Text_Rosa_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_ROSA}Sometimes the camera catches a smile I\n"
	.string "didn't know I was making. Those are my\l"
	.string "favorite takes.\p"
	.string "Let the little singer afterward try\n"
	.string "something nobody has rehearsed. You\l"
	.string "don't need a perfect performance to\l"
	.string "share a very good moment.$"

Nexus_Text_Serena_Xerneas_ChampionIntro:
	.string "The branches are full of colors I\n"
	.string "can't name. Every petal below them\l"
	.string "seems to be choosing a different\l"
	.string "tomorrow.\p"
	.string "I used to watch someone else's\n"
	.string "progress. Today, I'd like to see what\l"
	.string "my team and I can make.$"

Nexus_Text_Serena_Xerneas_ChampionDefeat:
	.string "That was yours. Every choice carried\n"
	.string "your own care.$"

Nexus_Text_Serena_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_SERENA}It is easy to admire someone so much\n"
	.string "that your own path becomes a list of\l"
	.string "places they reached first. Life offers\l"
	.string "more branches than that.\p"
	.string "Let the small beginning afterward grow\n"
	.string "toward its own light. I'll be\l"
	.string "practicing the same.$"

Nexus_Text_Serena_Diancie_ChampionIntro:
	.string "The jewels keep appearing in the\n"
	.string "reflection before the light touches\l"
	.string "them. Beautiful, but difficult to\l"
	.string "follow.\p"
	.string "I once tried to match another person's\n"
	.string "shine. Now I'd rather find a clear\l"
	.string "answer with my own partners. Shall we?$"

Nexus_Text_Serena_Diancie_ChampionDefeat:
	.string "A clear finish. I can learn from that\n"
	.string "without making it my whole path.$"

Nexus_Text_Serena_Diancie_ChampionAfter:
	.string "{SPEAKER NAME_SERENA}Pressure brings out something in a\n"
	.string "stone. Too much can break what you\l"
	.string "hoped to reveal.\p"
	.string "Care for the little one afterward\n"
	.string "without comparing it to the brilliance\l"
	.string "you saw here. Being precious should\l"
	.string "not require a daily demonstration.$"

Nexus_Text_Serena_Latias_ChampionIntro:
	.string "It borrowed my face, then tilted its\n"
	.string "head as though trying to decide\l"
	.string "whether the expression suited it.\p"
	.string "The reflection is already practicing\n"
	.string "another one. Let's give it a battle\l"
	.string "that belongs to us.$"

Nexus_Text_Serena_Latias_ChampionDefeat:
	.string "You made that victory your own. I\n"
	.string "respect it.$"

Nexus_Text_Serena_Latias_ChampionAfter:
	.string "{SPEAKER NAME_SERENA}Trying on someone else's expression\n"
	.string "can help you understand them. Staying\l"
	.string "inside it can make you forget how you\l"
	.string "feel.\p"
	.string "Let the little life afterward show you\n"
	.string "a face it chose. You needn't decide\l"
	.string "which version is the most beautiful.$"

Nexus_Text_Shelly_Manaphy_ChampionIntro:
	.string "The current is making a circuit\n"
	.string "through hearts instead of water. I\l"
	.string "checked the readings twice. Then I\l"
	.string "checked how I felt.\p"
	.string "This sea remembers a different crew.\n"
	.string "Let's see how well yours holds\l"
	.string "together.$"

Nexus_Text_Shelly_Manaphy_ChampionDefeat:
	.string "A good crew. Nobody needed threatening\n"
	.string "to stay aboard.$"

Nexus_Text_Shelly_Manaphy_ChampionAfter:
	.string "{SPEAKER NAME_SHELLY}I left a uniform on a boat seat once.\n"
	.string "Leaving the things I believed was\l"
	.string "rather harder.\p"
	.string "The little heart afterward needs a\n"
	.string "bond it can enter freely. I would like\l"
	.string "to think I've learned enough not to\l"
	.string "confuse that with recruiting.$"

Nexus_Text_Shelly_Kyogre_ChampionIntro:
	.string "The ocean has reached the ceiling\n"
	.string "without wetting the stairs. Somewhere\l"
	.string "below, a great pulse is deciding what\l"
	.string "the shore means.\p"
	.string "I once helped a man who wanted an\n"
	.string "answer that large. Show me your\l"
	.string "judgment.$"

Nexus_Text_Shelly_Kyogre_ChampionDefeat:
	.string "You knew when to stop pushing. An\n"
	.string "undervalued skill.$"

Nexus_Text_Shelly_Kyogre_ChampionAfter:
	.string "{SPEAKER NAME_SHELLY}The sea never asked us to speak for\n"
	.string "every life in it. We found that\l"
	.string "convenient to forget.\p"
	.string "Whatever small beginning the tide\n"
	.string "leaves, listen before planning its\l"
	.string "future. An ocean's worth of good\l"
	.string "intentions can still drown somebody.$"

Nexus_Text_Shelly_Volcanion_ChampionIntro:
	.string "Fire and water sharing a pressure\n"
	.string "system. I can almost hear two old\l"
	.string "uniforms arguing with the result.\p"
	.string "The steam froze yesterday. I can't\n"
	.string "pretend my instruments explain that.\l"
	.string "Let's test something practical\l"
	.string "instead!$"

Nexus_Text_Shelly_Volcanion_ChampionDefeat:
	.string "You kept the pressure useful. That's\n"
	.string "good work.$"

Nexus_Text_Shelly_Volcanion_ChampionAfter:
	.string "{SPEAKER NAME_SHELLY}We divided the world into opposing\n"
	.string "elements because it made the speeches\l"
	.string "easier. That creature never attended\l"
	.string "the meeting.\p"
	.string "Give its little beginning a life wider\n"
	.string "than our old argument. Some\l"
	.string "discoveries ought to make the uniforms\l"
	.string "unnecessary.$"

Nexus_Text_Skyla_Tornadus_ChampionIntro:
	.string "The wind sock is pointing in three\n"
	.string "directions, and one of them seems to\l"
	.string "be tomorrow!\p"
	.string "That green passenger hasn't filed a\n"
	.string "flight plan. Never mind. Let's see how\l"
	.string "you handle a little unexpected\l"
	.string "turbulence!$"

Nexus_Text_Skyla_Tornadus_ChampionDefeat:
	.string "A perfect adjustment! You kept every\n"
	.string "partner on course!$"

Nexus_Text_Skyla_Tornadus_ChampionAfter:
	.string "{SPEAKER NAME_SKYLA}I check the weather before every\n"
	.string "flight. That doesn't mean I can tell\l"
	.string "the wind what to do.\p"
	.string "Give the small traveler afterward a\n"
	.string "safe place to land. A good home can be\l"
	.string "part of an adventurous life, too.$"

Nexus_Text_Skyla_Lugia_ChampionIntro:
	.string "Those folded wings have made every\n"
	.string "draft in the room hold its breath. My\l"
	.string "altimeter has started measuring depth.\p"
	.string "I think we're near a sea the sky\n"
	.string "remembers. Ready for a test flight on\l"
	.string "firmer ground?$"

Nexus_Text_Skyla_Lugia_ChampionDefeat:
	.string "Beautiful landing! Even with that\n"
	.string "crosswind in the final turn!$"

Nexus_Text_Skyla_Lugia_ChampionAfter:
	.string "{SPEAKER NAME_SKYLA}A pilot learns that choosing not to\n"
	.string "take off can be the strongest decision\l"
	.string "of the day. The great wings seem to\l"
	.string "understand.\p"
	.string "Let the little one afterward rest\n"
	.string "without calling it timid. Clear skies\l"
	.string "are worth waiting for together.$"

Nexus_Text_Skyla_Celesteela_ChampionIntro:
	.string "A passenger that carries its own\n"
	.string "launch tower! The clouds here remember\l"
	.string "an ascent that hasn't started.\p"
	.string "I checked the space above us. It seems\n"
	.string "to be somewhere else entirely. Let's\l"
	.string "run your team's checks first!$"

Nexus_Text_Skyla_Celesteela_ChampionDefeat:
	.string "All systems working together! That was\n"
	.string "a lovely approach!$"

Nexus_Text_Skyla_Celesteela_ChampionAfter:
	.string "{SPEAKER NAME_SKYLA}People ask whether flying still\n"
	.string "excites me. It does, but bringing\l"
	.string "everyone home matters more.\p"
	.string "The small beginning after that great\n"
	.string "ascent deserves a place to land.\l"
	.string "Wonder is easier to enjoy when someone\l"
	.string "has checked the return route.$"

Nexus_Text_Tulip_Lunala_ChampionIntro:
	.string "That crescent has turned the darkness\n"
	.string "into a frame. The light disappears\l"
	.string "first; then the wings arrive to\l"
	.string "explain it.\p"
	.string "Presentation can reveal a presence or\n"
	.string "hide one. Show me how well you hold\l"
	.string "your own.$"

Nexus_Text_Tulip_Lunala_ChampionDefeat:
	.string "Beautiful composure. You kept your\n"
	.string "shape under changing light.$"

Nexus_Text_Tulip_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_TULIP}A face under the lights still belongs\n"
	.string "to someone who must go home afterward.\l"
	.string "I try to remember that in my work.\p"
	.string "Give the small cloud afterward\n"
	.string "somewhere it needn't be striking.\l"
	.string "Quiet company brings out a different\l"
	.string "sort of beauty.$"

Nexus_Text_Tulip_Cresselia_ChampionIntro:
	.string "The lake reflects a dream I haven't\n"
	.string "had. That soft light makes even\l"
	.string "uncertainty look gentle.\p"
	.string "A flattering view is still a view we\n"
	.string "should examine. Let us see how your\l"
	.string "composure holds without the\l"
	.string "reflection's help.$"

Nexus_Text_Tulip_Cresselia_ChampionDefeat:
	.string "Poised, even at the turning point.\n"
	.string "Beautifully handled.$"

Nexus_Text_Tulip_Cresselia_ChampionAfter:
	.string "{SPEAKER NAME_TULIP}A careful touch can help someone feel\n"
	.string "more like themselves. It can also\l"
	.string "become a mask they fear removing.\p"
	.string "Let the little life afterward have\n"
	.string "unguarded mornings. It needn't arrive\l"
	.string "beautifully prepared to deserve your\l"
	.string "attention.$"

Nexus_Text_Tulip_GalarianArticuno_ChampionIntro:
	.string "Such an exact gaze. It has noticed\n"
	.string "every weakness in the pose before the\l"
	.string "pose is finished.\p"
	.string "Even the mirror has begun standing\n"
	.string "straighter. Let's see whether your\l"
	.string "calm is more than a pleasing surface.$"

Nexus_Text_Tulip_GalarianArticuno_ChampionDefeat:
	.string "You kept your poise without\n"
	.string "stiffening. A lovely distinction.$"

Nexus_Text_Tulip_GalarianArticuno_ChampionAfter:
	.string "{SPEAKER NAME_TULIP}The trouble with a perfect stare is\n"
	.string "that everyone starts arranging\l"
	.string "themselves for it. Real confidence\l"
	.string "leaves space to breathe.\p"
	.string "Give the little one afterward time\n"
	.string "away from scrutiny. It may show you\l"
	.string "something beautiful when nobody is\l"
	.string "measuring.$"

Nexus_Text_Valerie_Xerneas_ChampionIntro:
	.string "The branches carry every color a\n"
	.string "living cloth could wish to hold. Here,\l"
	.string "the shadows are still choosing their\l"
	.string "bodies.\p"
	.string "I wonder how it feels to wear a whole\n"
	.string "spring. Shall we ask through movement?$"

Nexus_Text_Valerie_Xerneas_ChampionDefeat:
	.string "How lovely. Your partners seemed\n"
	.string "entirely at home in themselves.$"

Nexus_Text_Valerie_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_VALERIE}I make clothes hoping to feel a little\n"
	.string "of another creature's life. No costume\l"
	.string "can give me the whole answer.\p"
	.string "The little one afterward will have its\n"
	.string "own seasons. Leave room in every\l"
	.string "pattern you imagine for it to outgrow\l"
	.string "the drawing.$"

Nexus_Text_Valerie_Diancie_ChampionIntro:
	.string "A jewel has given itself a body. The\n"
	.string "reflections try on shapes before the\l"
	.string "light arrives.\p"
	.string "I have spent so long asking cloth to\n"
	.string "do something like that. Perhaps a\l"
	.string "battle can teach my hands another way.$"

Nexus_Text_Valerie_Diancie_ChampionDefeat:
	.string "Such a delicate turn. There was\n"
	.string "strength inside every line.$"

Nexus_Text_Valerie_Diancie_ChampionAfter:
	.string "{SPEAKER NAME_VALERIE}A beautiful setting should hold a\n"
	.string "jewel safely without hiding what makes\l"
	.string "it itself. I wish the same care were\l"
	.string "simpler with people.\p"
	.string "Let the small beginning afterward\n"
	.string "choose how close to shine. You needn't\l"
	.string "place it where everyone can admire it.$"

Nexus_Text_Valerie_Pheromosa_ChampionIntro:
	.string "Those limbs make the air seem like\n"
	.string "fabric folded in exactly the right\l"
	.string "direction. It steps away from every\l"
	.string "touch.\p"
	.string "The footprints here appear before the\n"
	.string "feet agree to make them. Would you\l"
	.string "care to show it our own movement?$"

Nexus_Text_Valerie_Pheromosa_ChampionDefeat:
	.string "A lovely response. You allowed space\n"
	.string "for every changing step.$"

Nexus_Text_Valerie_Pheromosa_ChampionAfter:
	.string "{SPEAKER NAME_VALERIE}I wonder whether its elegance feels\n"
	.string "effortless from inside. People often\l"
	.string "assume a beautiful shape must be\l"
	.string "comfortable.\p"
	.string "Make room for the little life\n"
	.string "afterward to be particular about its\l"
	.string "surroundings. Understanding begins\l"
	.string "with listening to the refusal as well\p"
	.string "as the invitation.$"

Nexus_Text_Viola_Genesect_ChampionIntro:
	.string "My camera keeps finding an ancient\n"
	.string "silhouette beneath the cannon. The old\l"
	.string "shape appears a frame before the\l"
	.string "metal.\p"
	.string "A photograph can miss what a creature\n"
	.string "is trying to become. Let's see what\l"
	.string "your partners show in motion!$"

Nexus_Text_Viola_Genesect_ChampionDefeat:
	.string "Fantastic! That final expression was\n"
	.string "completely your own!$"

Nexus_Text_Viola_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_VIOLA}A picture tells people what was in\n"
	.string "front of the lens. It can't tell them\l"
	.string "everything outside the frame.\p"
	.string "Meet the small beginning afterward\n"
	.string "without letting the weapon fill the\l"
	.string "whole portrait. A quiet day might\l"
	.string "reveal the better story.$"

Nexus_Text_Viola_Buzzwole_ChampionIntro:
	.string "Hold that pose! Oh, it was already\n"
	.string "holding one. The shadow is flexing for\l"
	.string "a photograph I haven't taken yet!\p"
	.string "That's a very confident subject. Let's\n"
	.string "see how you look when you give a\l"
	.string "battle everything!$"

Nexus_Text_Viola_Buzzwole_ChampionDefeat:
	.string "What a finish! Even the background\n"
	.string "couldn't sit still!$"

Nexus_Text_Viola_Buzzwole_ChampionAfter:
	.string "{SPEAKER NAME_VIOLA}I thought it was showing off for me.\n"
	.string "Then I put the camera down, and it\l"
	.string "looked just as pleased.\p"
	.string "Let the little life afterward enjoy\n"
	.string "itself without becoming your favorite\l"
	.string "shot. Some of the best moments can\l"
	.string "remain uncollected.$"

Nexus_Text_Viola_Kartana_ChampionIntro:
	.string "An edge so thin my camera keeps losing\n"
	.string "it. The leaves fall into perfect\l"
	.string "halves before I hear the cut.\p"
	.string "A beautiful line can still be\n"
	.string "dangerous. Let's see if your team can\l"
	.string "find the right angle!$"

Nexus_Text_Viola_Kartana_ChampionDefeat:
	.string "Sharp timing! You caught the moment\n"
	.string "before it slipped away!$"

Nexus_Text_Viola_Kartana_ChampionAfter:
	.string "{SPEAKER NAME_VIOLA}I spend my days choosing a frame. That\n"
	.string "little blade seems to cut the world\l"
	.string "into frames of its own.\p"
	.string "The small beginning afterward deserves\n"
	.string "a space without anyone trimming it to\l"
	.string "fit a picture. Leave the edges where\l"
	.string "they grow.$"

Nexus_Text_Zinnia_Rayquaza_ChampionIntro:
	.string "There it is. The green line through\n"
	.string "every story my people kept. Here, the\l"
	.string "sky remembers the prayer before\l"
	.string "anybody speaks.\p"
	.string "I've heard enough endings chosen in\n"
	.string "advance. Let's see what you can do\l"
	.string "with an open one!$"

Nexus_Text_Zinnia_Rayquaza_ChampionDefeat:
	.string "Ahaha! You made the old story stop and\n"
	.string "look!$"

Nexus_Text_Zinnia_Rayquaza_ChampionAfter:
	.string "{SPEAKER NAME_ZINNIA}I carried a duty because someone\n"
	.string "before me couldn't finish it. Easy to\l"
	.string "call that purpose when you're afraid\l"
	.string "to put it down.\p"
	.string "Let the little one afterward live\n"
	.string "before you give it a prophecy. A sky\l"
	.string "ought to have room beyond the legend.$"

Nexus_Text_Zinnia_Jirachi_ChampionIntro:
	.string "The tags on those wishes have dates\n"
	.string "nobody here remembers. One of them\l"
	.string "looks like my handwriting.\p"
	.string "A falling star makes everybody think\n"
	.string "they get a second chance. Let's see\l"
	.string "what you do with the first opening!$"

Nexus_Text_Zinnia_Jirachi_ChampionDefeat:
	.string "That wasn't luck. You were ready when\n"
	.string "the chance came.$"

Nexus_Text_Zinnia_Jirachi_ChampionAfter:
	.string "{SPEAKER NAME_ZINNIA}I could name a wish before you\n"
	.string "finished asking. That doesn't mean\l"
	.string "asking a small life to grant it would\l"
	.string "be fair.\p"
	.string "Keep the little one afterward company\n"
	.string "when it sleeps. Some things deserve\l"
	.string "protecting without promising anything\l"
	.string "in return.$"

Nexus_Text_Zinnia_Deoxys_ChampionIntro:
	.string "The star didn't fall so much as arrive\n"
	.string "in several shapes at once. My people's\l"
	.string "stories never agreed on that part.\p"
	.string "Good. Gives us something to find out\n"
	.string "ourselves. Ready to change your mind\l"
	.string "quickly?$"

Nexus_Text_Zinnia_Deoxys_ChampionDefeat:
	.string "You kept up when the shape changed.\n"
	.string "Nice! Very nice.$"

Nexus_Text_Zinnia_Deoxys_ChampionAfter:
	.string "{SPEAKER NAME_ZINNIA}I was taught what came from beyond the\n"
	.string "sky would need an answer. Nobody\l"
	.string "thought to ask whether it had a\l"
	.string "question.\p"
	.string "Give the small beginning afterward\n"
	.string "time to ask. You might save more than\l"
	.string "one world by listening before you\l"
	.string "reach for the old story.$"

Nexus_Text_Lillie_Solgaleo_ChampionIntro:
	.string "A little cloud used to hide in my bag.\n"
	.string "Where I come from, it grew into wings\l"
	.string "of night.\p"
	.string "Here, I can hear morning in those\n"
	.string "paws. I... would like to understand\l"
	.string "that, too. Will you battle me first?$"

Nexus_Text_Lillie_Solgaleo_ChampionDefeat:
	.string "You didn't hurry your partners. I\n"
	.string "think the light noticed.$"

Nexus_Text_Lillie_Solgaleo_ChampionAfter:
	.string "{SPEAKER NAME_LILLIE}I keep writing down the differences,\n"
	.string "as though enough notes will tell me\l"
	.string "which story was meant to happen.\l"
	.string "Perhaps both were.\p"
	.string "The little cloud afterward doesn't\n"
	.string "need to carry my version of the sky.\l"
	.string "Please let it find the morning or the\l"
	.string "night with you.$"
@ ---- campeoes extras (fim) ----

@ ---- lote de 31/10/2026 (inicio) ----
Nexus_EventScript_AZ_Fight::
	nexus_fight TRAINER_NEXUS_AZ, Nexus_Text_AZ_Intro, Nexus_Text_AZ_Defeat
	return

Nexus_EventScript_Agatha_Fight::
	nexus_fight TRAINER_NEXUS_AGATHA, Nexus_Text_Agatha_Intro, Nexus_Text_Agatha_Defeat
	return

Nexus_EventScript_Alder_Fight::
	nexus_fight TRAINER_NEXUS_ALDER, Nexus_Text_Alder_Intro, Nexus_Text_Alder_Defeat
	return

Nexus_EventScript_Allister_Fight::
	nexus_fight TRAINER_NEXUS_ALLISTER, Nexus_Text_Allister_Intro, Nexus_Text_Allister_Defeat
	return

Nexus_EventScript_Avery_Fight::
	nexus_fight TRAINER_NEXUS_AVERY, Nexus_Text_Avery_Intro, Nexus_Text_Avery_Defeat
	return

Nexus_EventScript_Barry_Fight::
	nexus_fight TRAINER_NEXUS_BARRY, Nexus_Text_Barry_Intro, Nexus_Text_Barry_Defeat
	return

Nexus_EventScript_Bea_Fight::
	nexus_fight TRAINER_NEXUS_BEA, Nexus_Text_Bea_Intro, Nexus_Text_Bea_Defeat
	return

Nexus_EventScript_Brycen_Fight::
	nexus_fight TRAINER_NEXUS_BRYCEN, Nexus_Text_Brycen_Intro, Nexus_Text_Brycen_Defeat
	return

Nexus_EventScript_Cheren_Fight::
	nexus_fight TRAINER_NEXUS_CHEREN, Nexus_Text_Cheren_Intro, Nexus_Text_Cheren_Defeat
	return

Nexus_EventScript_Cilan_Fight::
	nexus_fight TRAINER_NEXUS_CILAN, Nexus_Text_Cilan_Intro, Nexus_Text_Cilan_Defeat
	return

Nexus_EventScript_Cynthia_Fight::
	nexus_fight TRAINER_NEXUS_CYNTHIA, Nexus_Text_Cynthia_Intro, Nexus_Text_Cynthia_Defeat
	return

Nexus_EventScript_Cyrus_Fight::
	nexus_fight TRAINER_NEXUS_CYRUS, Nexus_Text_Cyrus_Intro, Nexus_Text_Cyrus_Defeat
	return

Nexus_EventScript_Dawn_Fight::
	nexus_fight TRAINER_NEXUS_DAWN, Nexus_Text_Dawn_Intro, Nexus_Text_Dawn_Defeat
	return

Nexus_EventScript_Diantha_Fight::
	nexus_fight TRAINER_NEXUS_DIANTHA, Nexus_Text_Diantha_Intro, Nexus_Text_Diantha_Defeat
	return

Nexus_EventScript_Gardenia_Fight::
	nexus_fight TRAINER_NEXUS_GARDENIA, Nexus_Text_Gardenia_Intro, Nexus_Text_Gardenia_Defeat
	return

Nexus_EventScript_Ghetsis_Fight::
	nexus_fight TRAINER_NEXUS_GHETSIS, Nexus_Text_Ghetsis_Intro, Nexus_Text_Ghetsis_Defeat
	return

Nexus_EventScript_Gloria_Fight::
	nexus_fight TRAINER_NEXUS_GLORIA, Nexus_Text_Gloria_Intro, Nexus_Text_Gloria_Defeat
	return

Nexus_EventScript_Grusha_Fight::
	nexus_fight TRAINER_NEXUS_GRUSHA, Nexus_Text_Grusha_Intro, Nexus_Text_Grusha_Defeat
	return

Nexus_EventScript_Hassel_Fight::
	nexus_fight TRAINER_NEXUS_HASSEL, Nexus_Text_Hassel_Intro, Nexus_Text_Hassel_Defeat
	return

Nexus_EventScript_Hau_Fight::
	nexus_fight TRAINER_NEXUS_HAU, Nexus_Text_Hau_Intro, Nexus_Text_Hau_Defeat
	return

Nexus_EventScript_Hilda_Fight::
	nexus_fight TRAINER_NEXUS_HILDA, Nexus_Text_Hilda_Intro, Nexus_Text_Hilda_Defeat
	return

Nexus_EventScript_Hop_Fight::
	nexus_fight TRAINER_NEXUS_HOP, Nexus_Text_Hop_Intro, Nexus_Text_Hop_Defeat
	return

Nexus_EventScript_Iono_Fight::
	nexus_fight TRAINER_NEXUS_IONO, Nexus_Text_Iono_Intro, Nexus_Text_Iono_Defeat
	return

Nexus_EventScript_Iris_Fight::
	nexus_fight TRAINER_NEXUS_IRIS, Nexus_Text_Iris_Intro, Nexus_Text_Iris_Defeat
	return

Nexus_EventScript_JessieJames_Fight::
	nexus_fight TRAINER_NEXUS_JESSIE_JAMES, Nexus_Text_JessieJames_Intro, Nexus_Text_JessieJames_Defeat
	return

Nexus_EventScript_Juniper_Fight::
	nexus_fight TRAINER_NEXUS_JUNIPER, Nexus_Text_Juniper_Intro, Nexus_Text_Juniper_Defeat
	return

Nexus_EventScript_Katy_Fight::
	nexus_fight TRAINER_NEXUS_KATY, Nexus_Text_Katy_Intro, Nexus_Text_Katy_Defeat
	return

Nexus_EventScript_Klara_Fight::
	nexus_fight TRAINER_NEXUS_KLARA, Nexus_Text_Klara_Intro, Nexus_Text_Klara_Defeat
	return

Nexus_EventScript_Korrina_Fight::
	nexus_fight TRAINER_NEXUS_KORRINA, Nexus_Text_Korrina_Intro, Nexus_Text_Korrina_Defeat
	return

Nexus_EventScript_Larry_Fight::
	nexus_fight TRAINER_NEXUS_LARRY, Nexus_Text_Larry_Intro, Nexus_Text_Larry_Defeat
	return

Nexus_EventScript_Lenora_Fight::
	nexus_fight TRAINER_NEXUS_LENORA, Nexus_Text_Lenora_Intro, Nexus_Text_Lenora_Defeat
	return

Nexus_EventScript_Leon_Fight::
	nexus_fight TRAINER_NEXUS_LEON, Nexus_Text_Leon_Intro, Nexus_Text_Leon_Defeat
	return

Nexus_EventScript_Lorelei_Fight::
	nexus_fight TRAINER_NEXUS_LORELEI, Nexus_Text_Lorelei_Intro, Nexus_Text_Lorelei_Defeat
	return

Nexus_EventScript_Lysandre_Fight::
	nexus_fight TRAINER_NEXUS_LYSANDRE, Nexus_Text_Lysandre_Intro, Nexus_Text_Lysandre_Defeat
	return

Nexus_EventScript_Marnie_Fight::
	nexus_fight TRAINER_NEXUS_MARNIE, Nexus_Text_Marnie_Intro, Nexus_Text_Marnie_Defeat
	return

Nexus_EventScript_Melony_Fight::
	nexus_fight TRAINER_NEXUS_MELONY, Nexus_Text_Melony_Intro, Nexus_Text_Melony_Defeat
	return

Nexus_EventScript_Molly_Fight::
	nexus_fight TRAINER_NEXUS_MOLLY, Nexus_Text_Molly_Intro, Nexus_Text_Molly_Defeat
	return

Nexus_EventScript_Mustard_Fight::
	nexus_fight TRAINER_NEXUS_MUSTARD, Nexus_Text_Mustard_Intro, Nexus_Text_Mustard_Defeat
	return

Nexus_EventScript_N_Fight::
	nexus_fight TRAINER_NEXUS_N, Nexus_Text_N_Intro, Nexus_Text_N_Defeat
	return

Nexus_EventScript_Nemona_Fight::
	nexus_fight TRAINER_NEXUS_NEMONA, Nexus_Text_Nemona_Intro, Nexus_Text_Nemona_Defeat
	return

Nexus_EventScript_Nessa_Fight::
	nexus_fight TRAINER_NEXUS_NESSA, Nexus_Text_Nessa_Intro, Nexus_Text_Nessa_Defeat
	return

Nexus_EventScript_Olivia_Fight::
	nexus_fight TRAINER_NEXUS_OLIVIA, Nexus_Text_Olivia_Intro, Nexus_Text_Olivia_Defeat
	return

Nexus_EventScript_Peonia_Fight::
	nexus_fight TRAINER_NEXUS_PEONIA, Nexus_Text_Peonia_Intro, Nexus_Text_Peonia_Defeat
	return

Nexus_EventScript_Peony_Fight::
	nexus_fight TRAINER_NEXUS_PEONY, Nexus_Text_Peony_Intro, Nexus_Text_Peony_Defeat
	return

Nexus_EventScript_Rowan_Fight::
	nexus_fight TRAINER_NEXUS_ROWAN, Nexus_Text_Rowan_Intro, Nexus_Text_Rowan_Defeat
	return

Nexus_EventScript_Rosa_Fight::
	nexus_fight TRAINER_NEXUS_ROSA, Nexus_Text_Rosa_Intro, Nexus_Text_Rosa_Defeat
	return

Nexus_EventScript_Serena_Fight::
	nexus_fight TRAINER_NEXUS_SERENA, Nexus_Text_Serena_Intro, Nexus_Text_Serena_Defeat
	return

Nexus_EventScript_Shelly_Fight::
	nexus_fight TRAINER_NEXUS_SHELLY, Nexus_Text_Shelly_Intro, Nexus_Text_Shelly_Defeat
	return

Nexus_EventScript_Skyla_Fight::
	nexus_fight TRAINER_NEXUS_SKYLA, Nexus_Text_Skyla_Intro, Nexus_Text_Skyla_Defeat
	return

Nexus_EventScript_Tulip_Fight::
	nexus_fight TRAINER_NEXUS_TULIP, Nexus_Text_Tulip_Intro, Nexus_Text_Tulip_Defeat
	return

Nexus_EventScript_Valerie_Fight::
	nexus_fight TRAINER_NEXUS_VALERIE, Nexus_Text_Valerie_Intro, Nexus_Text_Valerie_Defeat
	return

Nexus_EventScript_Viola_Fight::
	nexus_fight TRAINER_NEXUS_VIOLA, Nexus_Text_Viola_Intro, Nexus_Text_Viola_Defeat
	return

Nexus_EventScript_Zinnia_Fight::
	nexus_fight TRAINER_NEXUS_ZINNIA, Nexus_Text_Zinnia_Intro, Nexus_Text_Zinnia_Defeat
	return

Nexus_Text_AZ_Intro:
	.string "{SPEAKER NAME_AZ}I once mistook a weapon for an\n"
	.string "answer. The flowers have outlived\l"
	.string "every stone I raised.\p"
	.string "These companions stayed. I would\n"
	.string "like you to understand why.$"

Nexus_Text_AZ_Defeat:
	.string "You fought without throwing\n"
	.string "anything away. Hold on to that.$"

Nexus_Text_Agatha_Intro:
	.string "{SPEAKER NAME_AGATHA}Hah! Another youngster. I'm\n"
	.string "Agatha. I was battling with ghosts\l"
	.string "before your grandparents learned\l"
	.string "to walk.\p"
	.string "People call me scary. Nonsense!\n"
	.string "I'm only honest. Pokemon are for\l"
	.string "battling, child, and I'll prove\l"
	.string "it.$"

Nexus_Text_Agatha_Defeat:
	.string "Oh ho! You're something special,\n"
	.string "child!$"

Nexus_Text_Alder_Intro:
	.string "{SPEAKER NAME_ALDER}Ha ha! Another traveler! Sit,\n"
	.string "sit... No? Battle first? Just like\l"
	.string "the young ones!\p"
	.string "Very well! Show me how you and\n"
	.string "your Pokemon get along!$"

Nexus_Text_Alder_Defeat:
	.string "Ha! Wonderful! That's a team that\n"
	.string "eats dinner together.$"

Nexus_Text_Allister_Intro:
	.string "{SPEAKER NAME_ALLISTER}Um... you can look at my mask.\n"
	.string "Please don't ask me to take it\l"
	.string "off.\p"
	.string "My friends are less shy than I am.\n"
	.string "They'll do the introductions.$"

Nexus_Text_Allister_Defeat:
	.string "Oh... they like you. I think I do,\n"
	.string "too.$"

Nexus_Text_Avery_Intro:
	.string "{SPEAKER NAME_AVERY}Avery, at your service. Do try to\n"
	.string "contain your astonishment.\p"
	.string "My psychic powers are exceptional.\n"
	.string "My victory shall be equally so!$"

Nexus_Text_Avery_Defeat:
	.string "An unforeseen development! I shall\n"
	.string "levitate above this indignity.$"

Nexus_Text_Barry_Intro:
	.string "{SPEAKER NAME_BARRY}Whoa, whoa! You're in my way!\n"
	.string "...Wait, no, I'm in yours.\l"
	.string "Whatever! Battle!\p"
	.string "I'm Barry! I'm gonna be the\n"
	.string "strongest Trainer ever. Stronger\l"
	.string "than my dad, even!\p"
	.string "And if you're slow about it, I'm\n"
	.string "fining you ten million! Let's GO!$"

Nexus_Text_Barry_Defeat:
	.string "Aaargh! How?! Okay, okay. I'll\n"
	.string "fine myself this time. Ten\l"
	.string "million. Ouch.$"

Nexus_Text_Bea_Intro:
	.string "{SPEAKER NAME_BEA}Training teaches you to stand when\n"
	.string "your legs say you cannot.\p"
	.string "My partners and I have practiced.\n"
	.string "Let us see what we have learned.$"

Nexus_Text_Bea_Defeat:
	.string "A clean victory. I must train\n"
	.string "harder. Thank you.$"

Nexus_Text_Brycen_Intro:
	.string "{SPEAKER NAME_BRYCEN}I once spoke for an audience. Now\n"
	.string "my partners speak for me.\p"
	.string "Watch their movements. There is no\n"
	.string "wasted motion.$"

Nexus_Text_Brycen_Defeat:
	.string "Your resolve did not freeze. Well\n"
	.string "done.$"

Nexus_Text_Cheren_Intro:
	.string "{SPEAKER NAME_CHEREN}On the first day, I ask every\n"
	.string "student the same question: what is\l"
	.string "strength for?\p"
	.string "No one has given me the right\n"
	.string "answer yet. Including me. Let's\l"
	.string "see if you can.$"

Nexus_Text_Cheren_Defeat:
	.string "That was an answer. I'll need to\n"
	.string "write it down.$"

Nexus_Text_Cilan_Intro:
	.string "{SPEAKER NAME_CILAN}A good battle, like a fine meal,\n"
	.string "needs balance.\p"
	.string "I'm Cilan. Let me see how your\n"
	.string "partners bring out each other's\l"
	.string "strengths!$"

Nexus_Text_Cilan_Defeat:
	.string "A remarkable finish! I shall\n"
	.string "remember that combination.$"

Nexus_Text_Cynthia_Intro:
	.string "{SPEAKER NAME_CYNTHIA}I'm Cynthia. I study myths -- the\n"
	.string "stories people tell when they\l"
	.string "can't explain what they saw.\p"
	.string "Every myth I've read began with\n"
	.string "someone who stood where you're\l"
	.string "standing, and decided to look\l"
	.string "closer.\p"
	.string "So. Let me see what you've\n"
	.string "decided.$"

Nexus_Text_Cynthia_Defeat:
	.string "...Wonderful. I'll have to write\n"
	.string "this down before it turns into a\l"
	.string "legend.$"

Nexus_Text_Cyrus_Intro:
	.string "{SPEAKER NAME_CYRUS}I am Cyrus. I once believed the\n"
	.string "heart was an incomplete machine.\p"
	.string "Fear. Pride. Grief. Noise, which\n"
	.string "makes a person hesitate at the\l"
	.string "precise moment it matters.\p"
	.string "You seem hesitant. Allow me to\n"
	.string "correct that.$"

Nexus_Text_Cyrus_Defeat:
	.string "...Irregular. I will have to\n"
	.string "recalculate what I expected of\l"
	.string "you.$"

Nexus_Text_Dawn_Intro:
	.string "{SPEAKER NAME_DAWN}Hi! I'm Dawn. I was practicing a\n"
	.string "new combination, but a battle\l"
	.string "sounds even better!\p"
	.string "No need to worry! That's what I\n"
	.string "tell myself before the tricky\l"
	.string "part.$"

Nexus_Text_Dawn_Defeat:
	.string "Oh! That was the tricky part. Your\n"
	.string "team was amazing!$"

Nexus_Text_Diantha_Intro:
	.string "{SPEAKER NAME_DIANTHA}Oh! An audience. How wonderful.\p"
	.string "I've played queens, thieves and\n"
	.string "ghosts. Tonight, I'll play your\l"
	.string "opponent.\p"
	.string "Don't worry. I never break\n"
	.string "character. Shall we begin?$"

Nexus_Text_Diantha_Defeat:
	.string "Bravo! Truly.\p"
	.string "I'd give you a standing ovation,\n"
	.string "but I'm already standing.$"

Nexus_Text_Gardenia_Intro:
	.string "{SPEAKER NAME_GARDENIA}Hey there! I'm Gardenia! I grow\n"
	.string "things. Pokemon, trees, flowers...\l"
	.string "if it's green, I've got it\l"
	.string "covered!\p"
	.string "Come on, let's battle! My team's\n"
	.string "been stuck in one pot way too\l"
	.string "long!$"

Nexus_Text_Gardenia_Defeat:
	.string "Wow! You cut right through my\n"
	.string "garden. That's okay. Gardens grow\l"
	.string "back!$"

Nexus_Text_Ghetsis_Intro:
	.string "{SPEAKER NAME_GHETSIS}People call obedience peace when\n"
	.string "the voice giving orders is\l"
	.string "pleasant enough.\p"
	.string "I have dispensed with the pleasant\n"
	.string "voice. You will learn obedience\l"
	.string "all the same.$"

Nexus_Text_Ghetsis_Defeat:
	.string "You dare deny me? Even now, you\n"
	.string "dare?!$"

Nexus_Text_Gloria_Intro:
	.string "{SPEAKER NAME_GLORIA}I'm Gloria! I promised my team a\n"
	.string "proper challenge today.\p"
	.string "They've been watching every\n"
	.string "Trainer we pass. Looks like\l"
	.string "they've picked you!$"

Nexus_Text_Gloria_Defeat:
	.string "You gave them exactly what they\n"
	.string "wanted. Me too!$"

Nexus_Text_Grusha_Intro:
	.string "{SPEAKER NAME_GRUSHA}I know what it costs to miss a\n"
	.string "turn. You don't get every chance\l"
	.string "twice.\p"
	.string "Keep your balance. I'm not slowing\n"
	.string "down for you.$"

Nexus_Text_Grusha_Defeat:
	.string "You held your line. I respect\n"
	.string "that.$"

Nexus_Text_Hassel_Intro:
	.string "{SPEAKER NAME_HASSEL}Ah, a young Trainer! Every battle\n"
	.string "shows me something my students\l"
	.string "have yet to teach me.\p"
	.string "Please, express yourself! My\n"
	.string "dragons and I will answer with all\l"
	.string "our hearts!$"

Nexus_Text_Hassel_Defeat:
	.string "Oh... wonderful! Forgive the\n"
	.string "tears. I am very proud of you.$"

Nexus_Text_Hau_Intro:
	.string "{SPEAKER NAME_HAU}Hey! Alola! Wanna battle? 'Course\n"
	.string "you do! Everybody does!\p"
	.string "I've got a malasada in my bag for\n"
	.string "after. Maybe even two, if you win.\p"
	.string "Let's make this one fun, yeah?$"

Nexus_Text_Hau_Defeat:
	.string "Ahaha! Aw man, that was awesome!\p"
	.string "Okay, okay. The malasada's yours.\n"
	.string "...Half of it.$"

Nexus_Text_Hilda_Intro:
	.string "{SPEAKER NAME_HILDA}Sorry, I'm in a hurry. I've been\n"
	.string "in a hurry for about two years\l"
	.string "now.\p"
	.string "Somebody left without saying where\n"
	.string "he was going. I'm going to catch\l"
	.string "up.\p"
	.string "You're standing between me and the\n"
	.string "next door. So... battle!$"

Nexus_Text_Hilda_Defeat:
	.string "Fine. This one's yours. I still\n"
	.string "have to keep going.$"

Nexus_Text_Hop_Intro:
	.string "{SPEAKER NAME_HOP}I used to measure every win\n"
	.string "against my brother's.\p"
	.string "Now I watch my partners. They're\n"
	.string "ready, and that's all the reason I\l"
	.string "need. Come on!$"

Nexus_Text_Hop_Defeat:
	.string "Right! I'll remember how they\n"
	.string "moved. There's loads to learn from\l"
	.string "you!$"

Nexus_Text_Iono_Intro:
	.string "{SPEAKER NAME_IONO}Your eyeballs are MINE! Iono's got\n"
	.string "a challenger with a very\l"
	.string "interesting look!\p"
	.string "Think you can keep up when the\n"
	.string "voltage spikes? Let's find out!$"

Nexus_Text_Iono_Defeat:
	.string "Bzzt! You just blew the ratings\n"
	.string "through the roof!$"

Nexus_Text_Iris_Intro:
	.string "{SPEAKER NAME_IRIS}Hi! I'm Iris! My dragons get\n"
	.string "restless when I talk for too long.\p"
	.string "See? That one already wants to\n"
	.string "start. Let's make this a good one!$"

Nexus_Text_Iris_Defeat:
	.string "Wow! We lost, but everybody's\n"
	.string "still smiling!$"

Nexus_Text_JessieJames_Intro:
	.string "{SPEAKER NAME_JESSIE_JAMES}JESSIE: Prepare for trouble!\p"
	.string "JAMES: We've rehearsed this\n"
	.string "entrance all morning!\p"
	.string "MEOWTH: Then quit talkin' and\n"
	.string "start battlin'!$"

Nexus_Text_JessieJames_Defeat:
	.string "JESSIE: Our perfect plan!\p"
	.string "JAMES: Perhaps we should have\n"
	.string "rehearsed the battle, too.$"

Nexus_Text_Juniper_Intro:
	.string "{SPEAKER NAME_JUNIPER}I'm Professor Juniper. I study how\n"
	.string "Pokemon began, but their choices\l"
	.string "still surprise me.\p"
	.string "Would you help with a little\n"
	.string "fieldwork? A battle tells me what\l"
	.string "a specimen jar never could.$"

Nexus_Text_Juniper_Defeat:
	.string "Excellent! Every time I think I\n"
	.string "understand them, they teach me\l"
	.string "something new.$"

Nexus_Text_Katy_Intro:
	.string "{SPEAKER NAME_KATY}A lovely cake takes patience. So\n"
	.string "does raising a tiny bug into\l"
	.string "something magnificent.\p"
	.string "I do hope you saved room for a\n"
	.string "challenge, dear.$"

Nexus_Text_Katy_Defeat:
	.string "Oh, how delightful! A little\n"
	.string "bitter for me, but beautifully\l"
	.string "made.$"

Nexus_Text_Klara_Intro:
	.string "{SPEAKER NAME_KLARA}Oh, a challenger! How sweet. You\n"
	.string "won't mind losing to me, will you?\p"
	.string "I've worked terribly hard on this\n"
	.string "smile. Don't make me drop it.$"

Nexus_Text_Klara_Defeat:
	.string "Oh, come ON! ...I mean,\n"
	.string "congratulations. Truly.$"

Nexus_Text_Korrina_Intro:
	.string "{SPEAKER NAME_KORRINA}Hear those wheels? That's your\n"
	.string "warning! I'm Korrina!\p"
	.string "My partner and I have been\n"
	.string "practicing until we move together\l"
	.string "without thinking. Ready?$"

Nexus_Text_Korrina_Defeat:
	.string "Whoa! You read us perfectly! Let's\n"
	.string "practice even harder, partner!$"

Nexus_Text_Larry_Intro:
	.string "{SPEAKER NAME_LARRY}I'm Larry. I was told this battle\n"
	.string "counts toward my working hours.\p"
	.string "I'd appreciate a straightforward\n"
	.string "match. My lunch break is\l"
	.string "approaching.$"

Nexus_Text_Larry_Defeat:
	.string "That settles it. I'll put the loss\n"
	.string "in my report.$"

Nexus_Text_Lenora_Intro:
	.string "{SPEAKER NAME_LENORA}I'm Lenora. At the museum, I piece\n"
	.string "together lives from what they\l"
	.string "leave behind.\p"
	.string "Battling is easier. You can ask\n"
	.string "your questions while the other\l"
	.string "side is still standing!$"

Nexus_Text_Lenora_Defeat:
	.string "Now there's a story worth\n"
	.string "preserving. Well fought!$"

Nexus_Text_Leon_Intro:
	.string "{SPEAKER NAME_LEON}Well, hello! I was looking for the\n"
	.string "stadium. It was left, wasn't it?\l"
	.string "Or... the other left?\p"
	.string "Never mind! Wherever there's a\n"
	.string "battle, that's where I was headed\l"
	.string "all along.\p"
	.string "Let's have a champion time!$"

Nexus_Text_Leon_Defeat:
	.string "Ha! Brilliant! That's the kind of\n"
	.string "battle that brings a whole stadium\l"
	.string "to its feet!$"

Nexus_Text_Lorelei_Intro:
	.string "{SPEAKER NAME_LORELEI}Welcome. I am Lorelei. No one can\n"
	.string "best me when it comes to icy\l"
	.string "Pokemon.\p"
	.string "Freezing moves are powerful. Your\n"
	.string "Pokemon will be at my mercy when\l"
	.string "they are frozen solid! ...Are you\l"
	.string "ready?$"

Nexus_Text_Lorelei_Defeat:
	.string "...Things shouldn't be this way!$"

Nexus_Text_Lysandre_Intro:
	.string "{SPEAKER NAME_LYSANDRE}Everything beautiful is asked to\n"
	.string "endure those who would consume it.\p"
	.string "Show me whether your strength\n"
	.string "preserves anything worth keeping.$"

Nexus_Text_Lysandre_Defeat:
	.string "Such power... And still you refuse\n"
	.string "my conclusion.$"

Nexus_Text_Marnie_Intro:
	.string "{SPEAKER NAME_MARNIE}I'm Marnie. My fans make enough\n"
	.string "noise for both of us.\p"
	.string "I'll let my team handle the rest.\n"
	.string "Don't expect us to hold back.$"

Nexus_Text_Marnie_Defeat:
	.string "You earned that. I'll have to give\n"
	.string "everyone a better show next time.$"

Nexus_Text_Melony_Intro:
	.string "{SPEAKER NAME_MELONY}Oh, don't look so tense, love. I\n"
	.string "always give my challengers a warm\l"
	.string "welcome.\p"
	.string "After that, things get rather\n"
	.string "chilly. Shall we?$"

Nexus_Text_Melony_Defeat:
	.string "Beautifully done! I hope my\n"
	.string "children were paying attention.$"

Nexus_Text_Molly_Intro:
	.string "{SPEAKER NAME_MOLLY}I used to make up friends who\n"
	.string "could never lose.\p"
	.string "These ones stayed even after I\n"
	.string "learned that losing was real. Want\l"
	.string "to meet them?$"

Nexus_Text_Molly_Defeat:
	.string "We lost... but nobody disappeared.\n"
	.string "Let's all stay friends, okay?$"

Nexus_Text_Mustard_Intro:
	.string "{SPEAKER NAME_MUSTARD}Heh heh! Stiff shoulders, busy\n"
	.string "eyes. You've been practicing,\l"
	.string "haven't you?\p"
	.string "Let's see what happens when the\n"
	.string "old man makes you change your\l"
	.string "plans!$"

Nexus_Text_Mustard_Defeat:
	.string "Ho ho! Good! You found the opening\n"
	.string "before I could close it.$"

Nexus_Text_N_Intro:
	.string "{SPEAKER NAME_N}Your Pokemon are talking. They say\n"
	.string "you walk too fast, and that you\l"
	.string "apologize to them afterward.\p"
	.string "...Interesting. Mine say I think\n"
	.string "too much. Shall we find out which\l"
	.string "of us is right?$"

Nexus_Text_N_Defeat:
	.string "Their voices were so clear.\n"
	.string "Clearer than mine. Hm.$"

Nexus_Text_Nemona_Intro:
	.string "{SPEAKER NAME_NEMONA}You! You've got that look! The one\n"
	.string "Trainers get when they're ready\l"
	.string "for a really good battle!\p"
	.string "I'm Nemona. Please tell me your\n"
	.string "team is ready, because mine\l"
	.string "absolutely is!$"

Nexus_Text_Nemona_Defeat:
	.string "YES! That was incredible! I'm\n"
	.string "already thinking about our next\l"
	.string "battle!$"

Nexus_Text_Nessa_Intro:
	.string "{SPEAKER NAME_NESSA}A still surface doesn't tell you\n"
	.string "how strong the current is.\p"
	.string "I'm Nessa. Take your stance.\n"
	.string "You'll feel the difference soon\l"
	.string "enough.$"

Nexus_Text_Nessa_Defeat:
	.string "You read the current and held your\n"
	.string "ground. Nicely done.$"

Nexus_Text_Olivia_Intro:
	.string "{SPEAKER NAME_OLIVIA}Alola! Kahuna of Akala, part-time\n"
	.string "jeweler, full-time rock\l"
	.string "enthusiast.\p"
	.string "You know what gems are? Just rocks\n"
	.string "that got squeezed hard enough, for\l"
	.string "long enough.\p"
	.string "So let's squeeze. Hard!$"

Nexus_Text_Olivia_Defeat:
	.string "Oof. You cut clean. Nice facets.\p"
	.string "I'd put you right in the front\n"
	.string "window.$"

Nexus_Text_Peonia_Intro:
	.string "{SPEAKER NAME_PEONIA}Dad planned another expedition. I\n"
	.string "took the other path before he\l"
	.string "finished the title.\p"
	.string "I'm Peonia. Fancy a battle? It's\n"
	.string "much more fun when I pick the\l"
	.string "adventure myself.$"

Nexus_Text_Peonia_Defeat:
	.string "Now that was worth the detour!\n"
	.string "Don't tell Dad. He'll make a\l"
	.string "banner.$"

Nexus_Text_Peony_Intro:
	.string "{SPEAKER NAME_PEONY}Chief Peony, reporting for\n"
	.string "adventure! Got my notes, my team,\l"
	.string "and absolutely no idea where my\l"
	.string "daughter went!\p"
	.string "A battle first? That's the spirit!$"

Nexus_Text_Peony_Defeat:
	.string "Ha! What a discovery! I'll need a\n"
	.string "whole page for that one!$"

Nexus_Text_Rowan_Intro:
	.string "{SPEAKER NAME_ROWAN}Rowan. I study evolution.\p"
	.string "I have spent a lifetime watching\n"
	.string "Pokemon change. A Trainer should\l"
	.string "be capable of the same. Show me.$"

Nexus_Text_Rowan_Defeat:
	.string "Good. You adapted. Keep asking\n"
	.string "what you might become.$"

Nexus_Text_Rosa_Intro:
	.string "{SPEAKER NAME_ROSA}I'm Rosa! I've tried smiling for\n"
	.string "the camera, but my team always\l"
	.string "knows when I'm faking it.\p"
	.string "A battle gets a real smile out of\n"
	.string "me. Let's see if it does the same\l"
	.string "for you!$"

Nexus_Text_Rosa_Defeat:
	.string "There it is! Even after a loss, I\n"
	.string "can't stop smiling!$"

Nexus_Text_Serena_Intro:
	.string "{SPEAKER NAME_SERENA}I used to count how often somebody\n"
	.string "else won. It didn't help my team\l"
	.string "get any stronger.\p"
	.string "I'm Serena. Today I'll give you a\n"
	.string "battle that belongs to us.$"

Nexus_Text_Serena_Defeat:
	.string "That was yours. I'll take what I\n"
	.string "learned and build on it.$"

Nexus_Text_Shelly_Intro:
	.string "{SPEAKER NAME_SHELLY}Ahahahaha! Look at that\n"
	.string "confidence!\p"
	.string "I used to wear a uniform, you\n"
	.string "know. Stripes, a bandana, the\l"
	.string "whole act.\p"
	.string "I left it folded on a boat seat\n"
	.string "somewhere. I don't miss it.\l"
	.string "...Much.\p"
	.string "Now then. Let's see what you're\n"
	.string "made of, child!$"

Nexus_Text_Shelly_Defeat:
	.string "Ahahaha... Well. That stung.\p"
	.string "Fine. I've lost bigger things than\n"
	.string "a battle.$"

Nexus_Text_Skyla_Intro:
	.string "{SPEAKER NAME_SKYLA}I'm Skyla! I check the wind before\n"
	.string "every flight. My partners do the\l"
	.string "rest.\p"
	.string "Ready for takeoff? Let's see how\n"
	.string "well you handle a little\l"
	.string "turbulence!$"

Nexus_Text_Skyla_Defeat:
	.string "A perfect landing! Even if I was\n"
	.string "the one who came down first.$"

Nexus_Text_Tulip_Intro:
	.string "{SPEAKER NAME_TULIP}A little care can bring out\n"
	.string "something lovely. A little\l"
	.string "pressure reveals whether it will\l"
	.string "last.\p"
	.string "I'm Tulip. Let's see how your\n"
	.string "composure holds under the lights.$"

Nexus_Text_Tulip_Defeat:
	.string "Beautiful. You kept your poise\n"
	.string "right through the final move.$"

Nexus_Text_Valerie_Intro:
	.string "{SPEAKER NAME_VALERIE}I try to make clothes that feel\n"
	.string "the way a Pokemon must feel in its\l"
	.string "own skin.\p"
	.string "Battling brings me a little\n"
	.string "closer. Would you care to join us?$"

Nexus_Text_Valerie_Defeat:
	.string "How lovely. For a moment, I almost\n"
	.string "understood their language.$"

Nexus_Text_Viola_Intro:
	.string "{SPEAKER NAME_VIOLA}Hold that pose! Ah, too late. The\n"
	.string "best moments never wait for the\l"
	.string "camera.\p"
	.string "I'm Viola. Let's battle. I want to\n"
	.string "see the expression you make when\l"
	.string "you give it everything!$"

Nexus_Text_Viola_Defeat:
	.string "Fantastic! A picture couldn't have\n"
	.string "caught half of that!$"

Nexus_Text_Zinnia_Intro:
	.string "{SPEAKER NAME_ZINNIA}Hey! I'm always last. Last one to\n"
	.string "the party, last one out the door.\p"
	.string "Doesn't mean I lose, though.\n"
	.string "C'mon, let's see if you can keep\l"
	.string "up!$"

Nexus_Text_Zinnia_Defeat:
	.string "Ahaha! Wow. Okay, you're good.\p"
	.string "Guess I'm last again. I'm used to\n"
	.string "it.$"
@ ---- lote de 31/10/2026 (fim) ----
