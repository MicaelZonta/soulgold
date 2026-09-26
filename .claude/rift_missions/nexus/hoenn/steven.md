# Steven Stone

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Steven Stone — Campeão** (Hoenn · Elite Four e Campeões) — colecionador de pedras raras e especialista em Pokémon de Aço.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_STEVEN` | `graphics/object_events/pics/people/steven.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_STEVEN` | `graphics/trainers/front_pics/steven.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_STEVEN` | `graphics/field_mugshots/steven.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_STEVEN2` | 568 | 0x738 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_STEVEN` | 804 | 0x824 | Gholdengo Lv84, Aggron Lv85, Cradily Lv85, Excadrill Lv85, Archeops Lv85, Metagross Lv86 · *dupla* · VS: Purple | `Kitakami_Houses`, `MeteorFalls_StevensCave`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_STEVEN` | 878 | 0x86E | Gholdengo Lv84, Aggron Lv85, Cradily Lv85, Excadrill Lv85, Archeops Lv85, Metagross Lv86 · *dupla* · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_STEVEN`, campeão da Celesteela. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Deoxys**, semi-lendário **Jirachi**, Mega **Metagross** (Steeltite, a pedra do Steven neste hack), mais Skarmory, Claydol e Cradily. **Tudo veio do céu ou da rocha antiga**: o Deoxys chegou num meteoro, o Jirachi acorda com um cometa, o Cradily é fóssil e o Claydol é argila antiga. É a coleção do Steven. *Plano:* Deoxys e Claydol armam Stealth Rock e as telas, o Skarmory espalha Spikes e põe Tailwind em Doubles, e a Mega Metagross limpa.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Deoxys | Life Orb | Pressure | Naive | Psycho Boost, Knock Off, Ice Beam, Stealth Rock |
| Jirachi | Leftovers | Serene Grace | Careful | Iron Head, Body Slam, Wish, U-turn |
| Metagross | Steeltite | Clear Body | Jolly | Meteor Mash, Zen Headbutt, Earthquake, Bullet Punch |
| Skarmory | Rocky Helmet | Sturdy | Impish | Spikes, Tailwind, Brave Bird, Roost |
| Claydol | Light Clay | Levitate | Bold | Stealth Rock, Earth Power, Reflect, Light Screen |
| Cradily | Leftovers | Storm Drain | Careful | Giga Drain, Rock Slide, Recover, Toxic |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_STEVEN ===
Name: Steven
Class: Champion
Pic: Steven
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Deoxys @ Life Orb
Naive Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psycho Boost
- Knock Off
- Ice Beam
- Stealth Rock

Jirachi @ Leftovers
Careful Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Body Slam
- Wish
- U-turn

Metagross @ Steeltite
Jolly Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Meteor Mash
- Zen Headbutt
- Earthquake
- Bullet Punch

Skarmory @ Rocky Helmet
Impish Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spikes
- Tailwind
- Brave Bird
- Roost

Claydol @ Light Clay
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Earth Power
- Reflect
- Light Screen

Cradily @ Leftovers
Careful Nature
Level: 100
Ability: Storm Drain
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Rock Slide
- Recover
- Toxic
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Celesteela** (UB-04 Blaster). Steven é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Steven, colecionador de pedras raras, especialista em Aço, e o homem do Space Center de Mossdeep e do meteoro do Delta Episode.

**A criatura.** Celesteela tem o corpo entre um ônibus espacial e um broto de bambu. Testemunhas a viram incendiar uma floresta expelindo gás pelos dois braços. Mundo em USUM: Ultra Crater.

**O fragmento.** Uma cratera sob um céu lotado de estrelas. Brotos de aço altos como bambu, queimados de preto na base, todos apontando para cima.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A crater under a sky crowded with stars.
>
> Tall steel shoots rose from the floor like bamboo, scorched black at the base, all pointing straight up.

**Boss**

> The ground shook, and one of the steel shoots began to rise.
>
> It was not a tower. It had arms, and both of them were glowing.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB-04. Blaster.
>
> A crater where nothing falls, and a collector of fallen stones waiting for one.
>
> I have closed this file very gently. I cannot tell you why.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Blaster_Arrival:
	.string "A crater under a sky crowded with\n"
	.string "stars.\p"
	.string "Tall steel shoots rose from the floor\n"
	.string "like bamboo, scorched black at the\l"
	.string "base, all pointing straight up.$"

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
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Steven cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Oh -- hello. I was looking at the stones here. They're nothing like the ones back home.
>
> Every stone has a history, and so does every Trainer. I'd like to know yours.
>
> Shall we?

**Derrota**

> A fine battle. I'll keep it the way I keep a rare stone.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Steven é o **campeão**, a luta logo antes da Celesteela. A fala é sobre a criatura, sem dizer o nome dela.

O Steven passou a vida juntando o que o céu deixou cair, e a criatura faz o caminho contrário: queima uma floresta para sair do chão e nunca volta. Ele não sabe se ela está fugindo ou voltando para casa. A vitória do jogador: os Pokémon dele ficaram com os pés no chão o tempo todo. O que fica: não persiga algo assim; pare antes que ela parta, ou deixe partir, "as duas são respostas". E ele fica esperando que algo lá de cima deixe cair uma pedra.

**Antes da luta**

> All my life, I've collected what the sky let fall. Meteorites. Shards. Small pieces of somewhere else.
>
> The creature here goes the other way. It burns a forest to lift itself off the ground, and it never comes back down.
>
> I can't decide if it's running from something, or going home.
>
> …Forgive me. You didn't come here to listen to me think. Let's battle.

**Derrota**

> Your Pokémon kept their feet on the ground the whole time. I admire that more than I can say.

**Depois da luta**

> If it takes off while you're near it, don't chase it. Nothing can follow something like that.
>
> Stop it before it leaves. Or let it leave. Both are answers.
>
> I'll stay a while. Something that high up might drop a stone for me, sooner or later.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

