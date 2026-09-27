# Spenser

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Spenser — Battle Palace** (Hoenn · Battle Frontier — Frontier Brains) — sábio que testa a autonomia e a natureza dos Pokémon.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

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


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Spenser é o campeão, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Celebi

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
	.string "thing like that and thinks, "Ah. Me\l"
	.string "next?"\p"
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


#### Dialga

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


Falante novo: `SP_NAME_SPENSER` (não existe em `include/constants/speaker_names.h`).
