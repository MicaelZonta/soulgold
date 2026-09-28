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
	.string "{SPEAKER NAME_SILVER}That thing's been angry so long it\n"
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
