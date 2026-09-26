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
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_5, VAR_RESULT
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro \trainer, \defeat_text
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_3, VAR_RESULT
	cleartrainerflag \trainer
	call_if_eq VAR_TEMP_5, FALSE, Nexus_EventScript_ClearNoWhiteout
	.endm

Nexus_EventScript_ClearNoWhiteout::
	clearflag B_FLAG_NO_WHITEOUT
	return

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
