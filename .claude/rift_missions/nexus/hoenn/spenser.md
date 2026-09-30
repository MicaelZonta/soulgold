# Spenser

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Spenser — Battle Palace** (Hoenn · Battle Frontier — Frontier Brains) — sábio que testa a autonomia e a natureza dos Pokémon.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_SPENSER` | `graphics/object_events/pics/people/frontier_brains/spenser.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PALACE_MAVEN_SPENSER` | `graphics/trainers/front_pics/palace_maven_spenser.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_SPENSER` | 807 | 0x827 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_SPENSER` = **1032** (flag de batalha `0x908`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Spenser_Fight`; campeão: `Nexus_EventScript_Spenser_Dialga_ChampionFight` (para Dialga), `Nexus_EventScript_Spenser_Celebi_ChampionFight` (para Celebi). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Spenser.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_SPENSER`, campeão de Celebi e Dialga. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Dialga**, semi-lendário **Celebi** (os dois do tempo), Mega **Lapras** (Icetite: Lapras Gmax), com Slaking, Crobat e Arcanine, do time do Spenser em Emerald. O Battle Palace é o lugar onde o Pokémon age pela própria natureza; o Spenser é velho e sábio e **deixa cada Pokémon ser o que é**: o Slaking com Truant, a Celebi com Natural Cure. O lendário e o semi-lendário são o tempo, o assunto de um homem velho. *Plano:* **aguentar e deixar o tempo trabalhar.** Tailwind do Crobat dá velocidade, Intimidate do Arcanine protege, Leech Seed e Recover da Celebi desgastam, e o Dialga (Adamant Orb) e a Lapras Gmax batem.

*Plano (Singles):* Arcanine queima físicos com Will-O-Wisp; Celebi planta Leech Seed e se cura; Crobat abre Tailwind e faz pivô de U-turn para o Dialga ou para o Slaking entrar com velocidade dobrada; a Lapras usa Freeze-Dry contra Water. *Plano (Doubles):* Tailwind no primeiro turno, Intimidate e Snarl do Arcanine; o Slaking aproveita Tailwind para bater com Double-Edge nos turnos em que age; Ice Shard da Lapras e Extreme Speed do Arcanine fecham. Nada no time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Dialga | Adamant Orb | Pressure | Modest | Draco Meteor, Flash Cannon, Fire Blast, Thunderbolt |
| Celebi | Leftovers | Natural Cure | Bold | Giga Drain, Psychic, Leech Seed, Recover |
| Lapras | Icetite | Water Absorb | Modest | Freeze-Dry, Hydro Pump, Thunderbolt, Ice Shard |
| Slaking | Life Orb | Truant | Adamant | Double-Edge, Knock Off, Hammer Arm, Fire Punch |
| Crobat | Sitrus Berry | Infiltrator | Jolly | Brave Bird, Tailwind, Super Fang, U-turn |
| Arcanine | Leftovers | Intimidate | Adamant | Flare Blitz, Extreme Speed, Will-O-Wisp, Snarl |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_SPENSER ===
Name: Spenser
Class: Palace Maven
Pic: Palace Maven Spenser
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Dialga @ Adamant Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Flash Cannon
- Fire Blast
- Thunderbolt

Celebi @ Leftovers
Bold Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Psychic
- Leech Seed
- Recover

Lapras @ Icetite
Modest Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freeze-Dry
- Hydro Pump
- Thunderbolt
- Ice Shard

Slaking @ Life Orb
Adamant Nature
Level: 100
Ability: Truant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Knock Off
- Hammer Arm
- Fire Punch

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Tailwind
- Super Fang
- U-turn

Arcanine @ Leftovers
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Extreme Speed
- Will-O-Wisp
- Snarl
```

</details>


### Lendário associado

#### Celebi

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Celebi_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Celebi**. Spenser é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Spenser, Palace Maven da Battle Frontier de Hoenn, um velho sábio que acredita que o Pokémon luta melhor seguindo a própria natureza.

**A criatura.** Mítico que viaja no tempo. Aparece em florestas saudáveis e dizem que, quando surge, garante um futuro verde. Em Johto tem um santuário na Ilex Forest.

**O fragmento.** Uma floresta onde cada árvore está numa idade diferente: um broto ao lado de um tronco morto, uma árvore em flor ao lado de outra que ainda nem nasceu, só uma sombra no chão. O ar cheira a chuva de muito tempo atrás.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest where every tree was a different age.
>
> A seedling stood beside a dead trunk. A tree in full blossom stood beside a shadow on the ground where a tree had not grown yet.
>
> The air smelled like rain from a long time ago.

**Boss**

> A small green light moved between the trees, and wherever it passed, the ages shifted.
>
> The dead trunk put out a leaf. The seedling grew old and bowed.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-251. Forest Time.
>
> A forest of every age at once, and an old man who was glad to be only one of them.
>
> What came back with you is very small and very green. It keeps looking at me as if it knows how I will look when I am old. I have asked it not to tell me.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>


#### Dialga

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Dialga_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Dialga**. Spenser é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Spenser, o velho da Palace, que deixa cada Pokémon agir no próprio ritmo.

**A criatura.** Lendário de Sinnoh que governa o tempo: dizem que o tempo passa enquanto o coração dele bate. Foi visto no alto de Spear Pillar.

**O fragmento.** Um salão de pedra cheio de relógios, cada um num ritmo. Um adianta, outro atrasa, um parou há séculos. No chão, uma batida grave faz todos os ponteiros tremerem ao mesmo tempo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A stone hall full of clocks, each one keeping its own time.
>
> One ran fast. One ran slow. One had stopped centuries ago.
>
> Under the floor, a deep beat shook, and every hand on every clock trembled at once.

**Boss**

> The beat got louder, and closer, and the clocks began to agree with it.
>
> Something steel and blue stood at the end of the hall. Its chest glowed on every beat.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-483. Heartbeat.
>
> A hall where the clocks obey a heart, and an old man who would not ask it for one more minute.
>
> What came back with you has a small, quick heartbeat. The clock on my wall has started keeping time with it. I have decided not to mind.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Spenser_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Spenser cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hohoho. Come in, young one. Spenser, the Palace Maven. Sit, if there were anywhere to sit.
>
> In my Palace, a Pokémon fights by its own nature. I simply get out of the way.
>
> At my age, getting out of the way is the one skill that still improves. Now, let us see yours.

**Derrota**

> Hohoho! Your Pokémon knew their hearts better than mine did today.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)), além da que já está no jogo (variação 1). O sorteio de qual variação toca ainda não existe no código.

**Variação 2** — lembrança: o Spenser jovem, que mandava nos Pokémon como capitão de navio e perdia.

**Antes da luta**

> Hohoho. When I was young, I ordered my Pokémon about like a ship's captain. Left! Right! Now!
>
> They obeyed. And they lost. Every single time.
>
> It took me forty years to learn to be quiet. Let us see whether you learned it faster.

**Derrota**

> Hohoho! Faster indeed. Much faster than I did.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Spenser_Intro2:
	.string "Hohoho. When I was young, I ordered my\n"
	.string "Pokémon about like a ship's captain.\l"
	.string "Left! Right! Now!\p"
	.string "They obeyed. And they lost. Every\n"
	.string "single time.\p"
	.string "It took me forty years to learn to be\n"
	.string "quiet. Let us see whether you learned it\l"
	.string "faster.$"

Nexus_Text_Spenser_Defeat2:
	.string "Hohoho! Faster indeed. Much faster\n"
	.string "than I did.$"
```

</details>

**Variação 3** — humor e R21: os aniversários dele chegam fora de ordem; o homem de sobretudo que perguntou as horas.

**Antes da luta**

> Ah, a visitor. Tell me, young one, what year is it where you come from?
>
> No, no, don't answer. I stopped counting birthdays when they stopped arriving in order.
>
> A gentleman in a long coat asked me the time once. I said, “Which one?” He wrote that down.
>
> Hohoho! Come. Let your Pokémon be themselves.

**Derrota**

> Hohoho. Whatever year it is, it is yours.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Spenser_Intro3:
	.string "Ah, a visitor. Tell me, young one, what\n"
	.string "year is it where you come from?\p"
	.string "No, no, don't answer. I stopped\n"
	.string "counting birthdays when they stopped\l"
	.string "arriving in order.\p"
	.string "A gentleman in a long coat asked me the\n"
	.string "time once. I said, “Which one?” He wrote\l"
	.string "that down.\p"
	.string "Hohoho! Come. Let your Pokémon be\n"
	.string "themselves.$"

Nexus_Text_Spenser_Defeat3:
	.string "Hohoho. Whatever year it is, it is yours.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Spenser é o campeão, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Celebi

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Spenser_Celebi_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Spenser, velho, vê a criatura da floresta andar entre as idades das árvores e sente a tentação que qualquer velho sente: voltar. Ela passa e uma árvore morta brota de novo. A virada: o Spenser não quer. Ele diz que a Palace ensina a deixar o Pokémon ser o que é, e que isso vale para árvore, para gente, para ele: a idade dele é a natureza dele. E conta que a criatura só aparece onde a floresta é saudável, então a presença dela não é milagre: é elogio.

**Antes da luta**

> Hohoho. Did you see it? The little green light, walking between the trees?
>
> Wherever it passes, the dead wood sprouts again. An old man watches a thing like that and thinks, "Ah. Me next?"
>
> But no. I have been exactly this old for a while now, and I have grown fond of it.
>
> Come. Let us fight the way we are.

**Derrota**

> Splendid. You did not wish to be anything but yourself. Neither did your Pokémon.

**Depois da luta**

> They say that little one only appears where a forest is healthy.
>
> So it is not a miracle when it comes. It is a compliment. The forest was already doing well.
>
> My Palace teaches the same thing. A Pokémon is at its best when no one asks it to be something else.
>
> Go on. Let the forest keep its ages.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — lembrança: a luz verde mostrou a ele o menino que ele foi, e ele não quer voltar para corrigir o menino.

**Antes da luta**

> Hohoho. That little light showed me a boy just now. Skinny knees, loud voice, shouting orders at his Pokémon.
>
> It was me, of course. Sixty years ago, in a forest much like this one.
>
> I wanted to tell him to hush and let them fight. He would not have listened. I never did.
>
> Come. Let us show him how it is done.

**Derrota**

> Hohoho! The boy would have hated losing. I rather enjoyed it.

**Depois da luta**

> That little one could take me back, you know. It has offered.
>
> I would only make the same mistakes more slowly. That boy needs his mistakes. They are how he becomes me.
>
> A forest does not skip its young trees to reach the old ones sooner.
>
> Go on. And leave that boy where he is.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Spenser_Celebi_ChampionIntro2:
	.string "Hohoho. That little light showed me a\n"
	.string "boy just now. Skinny knees, loud voice,\l"
	.string "shouting orders at his Pokémon.\p"
	.string "It was me, of course. Sixty years ago, in\n"
	.string "a forest much like this one.\p"
	.string "I wanted to tell him to hush and let\n"
	.string "them fight. He would not have listened.\l"
	.string "I never did.\p"
	.string "Come. Let us show him how it is done.$"

Nexus_Text_Spenser_Celebi_ChampionDefeat2:
	.string "Hohoho! The boy would have hated\n"
	.string "losing. I rather enjoyed it.$"

Nexus_Text_Spenser_Celebi_ChampionAfter2:
	.string "{SPEAKER NAME_SPENSER}That little one could take me back, you\n"
	.string "know. It has offered.\p"
	.string "I would only make the same mistakes\n"
	.string "more slowly. That boy needs his\l"
	.string "mistakes. They are how he becomes me.\p"
	.string "A forest does not skip its young trees\n"
	.string "to reach the old ones sooner.\p"
	.string "Go on. And leave that boy where he is.$"
```

</details>

**Variação 3** — humor: a criatura está sempre atrasada, um “momento” dela é um século; o tronco morto também é vida.

**Antes da luta**

> Late again, that little green one. It says it will come “in a moment,” and its moments can last a century.
>
> I have waited on this stump so long, the stump has turned back into a sapling.
>
> Hohoho! Do not look so worried. Waiting is the Palace way.
>
> Now. While we wait, a battle!

**Derrota**

> Splendid. The moment passed, and you used it.

**Depois da luta**

> Do you know why it keeps the forest at every age? Because every age is needed.
>
> Seedlings for tomorrow. Old trunks for the beetles, and the moss, and the shade.
>
> An old man is a dead trunk, if you like. Plenty of life still living on him.
>
> Go. Mind the moss on your way out.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Spenser_Celebi_ChampionIntro3:
	.string "Late again, that little green one. It\n"
	.string "says it will come “in a moment,” and its\l"
	.string "moments can last a century.\p"
	.string "I have waited on this stump so long, the\n"
	.string "stump has turned back into a sapling.\p"
	.string "Hohoho! Do not look so worried. Waiting\n"
	.string "is the Palace way.\p"
	.string "Now. While we wait, a battle!$"

Nexus_Text_Spenser_Celebi_ChampionDefeat3:
	.string "Splendid. The moment passed, and you\n"
	.string "used it.$"

Nexus_Text_Spenser_Celebi_ChampionAfter3:
	.string "{SPEAKER NAME_SPENSER}Do you know why it keeps the forest at\n"
	.string "every age? Because every age is\l"
	.string "needed.\p"
	.string "Seedlings for tomorrow. Old trunks for\n"
	.string "the beetles, and the moss, and the\l"
	.string "shade.\p"
	.string "An old man is a dead trunk, if you like.\n"
	.string "Plenty of life still living on him.\p"
	.string "Go. Mind the moss on your way out.$"
```

</details>


#### Dialga

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Spenser_Dialga_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Spenser encontra a criatura cujo coração faz o tempo passar. Um velho diante disso poderia pedir mais tempo. Ele percebe outra coisa: o bicho não controla o tempo por vontade, só bate, e o tempo segue. A virada é que o Spenser se vê na criatura: os dois não mandam em nada, só seguem a própria natureza, e o mundo se ajusta. Ele não pede um minuto a mais; pede que o jogador use bem o dele.

**Antes da luta**

> Hohoho. You heard it too. Boom… boom… Every clock in that hall shivers on the beat.
>
> They say time only moves because that heart keeps beating.
>
> An old man could ask it for a few more years, you know. It would be the natural thing to ask.
>
> I won't. Come, let us spend a little of the time we have.

**Derrota**

> Hohoho. Well spent. Very well spent.

**Depois da luta**

> You know what I noticed? That creature does not command time. It only beats.
>
> Time follows it the way my Pokémon follow their natures. Nobody forces anything.
>
> I have one heart, and it is slower now. It still keeps its own time.
>
> Go. Do not ask it for more minutes. Just use yours well.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — dúvida: o coração dele falha uma batida à noite, e ele se pergunta se o coração do tempo falha junto.

**Antes da luta**

> Listen. Boom… boom… I have been counting. Sixty beats a minute, near enough.
>
> That is no accident, young one. We made the minute to match that heart, without ever knowing it.
>
> Every clock in the world is a copy of it. Mine included.
>
> Hohoho! Come, let us fight in time with it.

**Derrota**

> Hohoho. You kept the rhythm better than I did.

**Depois da luta**

> I will tell you a secret. Some nights, my heart skips a beat.
>
> And I wonder, when it does, whether that great heart skips one too. Whether the world loses a second.
>
> It does not, of course. It only feels that way to an old man in the dark.
>
> Go. Its beat is steady. Yours will be, too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Spenser_Dialga_ChampionIntro2:
	.string "Listen. Boom… boom… I have been\n"
	.string "counting. Sixty beats a minute, near\l"
	.string "enough.\p"
	.string "That is no accident, young one. We made\n"
	.string "the minute to match that heart, without\l"
	.string "ever knowing it.\p"
	.string "Every clock in the world is a copy of it.\n"
	.string "Mine included.\p"
	.string "Hohoho! Come, let us fight in time with\n"
	.string "it.$"

Nexus_Text_Spenser_Dialga_ChampionDefeat2:
	.string "Hohoho. You kept the rhythm better\n"
	.string "than I did.$"

Nexus_Text_Spenser_Dialga_ChampionAfter2:
	.string "{SPEAKER NAME_SPENSER}I will tell you a secret. Some nights, my\n"
	.string "heart skips a beat.\p"
	.string "And I wonder, when it does, whether\n"
	.string "that great heart skips one too. Whether\l"
	.string "the world loses a second.\p"
	.string "It does not, of course. It only feels\n"
	.string "that way to an old man in the dark.\p"
	.string "Go. Its beat is steady. Yours will be,\n"
	.string "too.$"
```

</details>

**Variação 3** — R21 e fio Tempo: alguém pôs uma corrente vermelha nesse coração; as horas apagadas caíram na floresta dele.

**Antes da luta**

> Hohoho. Did you see the marks on it? Old ones. Someone put a chain on that heart once.
>
> A red chain, from a man who wanted time to stop and never start again.
>
> Imagine it. Holding the whole world still, just to stop being hurt by it.
>
> I understand him a little. That is why we must fight. Come!

**Derrota**

> Hohoho. The chain did not hold. Neither did I.

**Depois da luta**

> The hours that man erased had to fall somewhere. They fell into my forest, like leaves.
>
> A small green friend of mine gathers them. That is why the trees there are every age at once.
>
> Nothing is lost, you see. Only put somewhere else, to wait.
>
> Go. That heart has room for every hour. Even the ones we threw away.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Spenser_Dialga_ChampionIntro3:
	.string "Hohoho. Did you see the marks on it? Old\n"
	.string "ones. Someone put a chain on that heart\l"
	.string "once.\p"
	.string "A red chain, from a man who wanted time\n"
	.string "to stop and never start again.\p"
	.string "Imagine it. Holding the whole world\n"
	.string "still, just to stop being hurt by it.\p"
	.string "I understand him a little. That is why we\n"
	.string "must fight. Come!$"

Nexus_Text_Spenser_Dialga_ChampionDefeat3:
	.string "Hohoho. The chain did not hold. Neither\n"
	.string "did I.$"

Nexus_Text_Spenser_Dialga_ChampionAfter3:
	.string "{SPEAKER NAME_SPENSER}The hours that man erased had to fall\n"
	.string "somewhere. They fell into my forest,\l"
	.string "like leaves.\p"
	.string "A small green friend of mine gathers\n"
	.string "them. That is why the trees there are\l"
	.string "every age at once.\p"
	.string "Nothing is lost, you see. Only put\n"
	.string "somewhere else, to wait.\p"
	.string "Go. That heart has room for every hour.\n"
	.string "Even the ones we threw away.$"
```

</details>


Falante novo: `SP_NAME_SPENSER` (não existe em `include/constants/speaker_names.h`).
