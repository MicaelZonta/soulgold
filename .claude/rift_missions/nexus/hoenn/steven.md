# Steven Stone

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Steven Stone — Campeão** (Hoenn · Elite Four e Campeões) — colecionador de pedras raras e especialista em Pokémon de Aço.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_STEVEN` | `graphics/object_events/pics/people/steven.png` |

Desde 26/09/2026 é a arte 32x32 de doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine), na campanha e no Nexus.

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

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_STEVEN` = **979** (flag de batalha `0x8D3`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Steven_Fight` (genérica) e `Nexus_EventScript_Steven_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Steven.

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_STEVEN`, campeão da Celesteela. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Deoxys**, semi-lendário **Jirachi**, Mega **Metagross** (Steeltite, a pedra do Steven neste hack), mais Skarmory, Claydol e Cradily. **Tudo veio do céu ou da rocha antiga**: o Deoxys chegou num meteoro, o Jirachi acorda com um cometa, o Cradily é fóssil e o Claydol é argila antiga. É a coleção do Steven. *Plano:* Deoxys e Claydol armam Stealth Rock e as telas, o Skarmory espalha Spikes e põe Tailwind em Doubles, e a Mega Metagross limpa.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Deoxys | Life Orb | Pressure | Naive | Psycho Boost, Knock Off, Ice Beam, Stealth Rock |
| Jirachi | Leftovers | Serene Grace | Careful | Iron Head, Body Slam, Wish, U-turn |
| Metagross | Steeltite | Clear Body | Jolly | Meteor Mash, Zen Headbutt, Earthquake, Bullet Punch |
| Skarmory | Rocky Helmet | Sturdy | Impish | Spikes, Tailwind, Brave Bird, Roost |
| Claydol | Light Clay | Allseeing Idol | Bold | Stealth Rock, Earth Power, Reflect, Light Screen |
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
Ability: Allseeing Idol
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

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Steven_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Celesteela** (UB-04 Blaster). Steven é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

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

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Steven_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Steven cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código). Nenhuma cita o lugar nem a criatura do dia.

**Variação 2** — lembrança e humor: cascalho em todos os bolsos, hábito antigo. O pai (dono de uma empresa) queria o filho atrás de uma mesa; ele levou o peso de papel da mesa — que era um fóssil. Nunca olhou para trás.

**Antes da luta**

> Please excuse me. I have gravel in every pocket. An old habit.
>
> My father runs a company, and hoped I would sit behind a desk. I took the desk's paperweight instead.
>
> It turned out to be a fossil. I never looked back.
>
> Now then. Let's see what you're made of.

**Derrota**

> Remarkable. You're made of something harder than I thought.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Steven_Intro2:
	.string "Please excuse me. I have gravel in\n"
	.string "every pocket. An old habit.\p"
	.string "My father runs a company, and hoped I\n"
	.string "would sit behind a desk. I took the\l"
	.string "desk's paperweight instead.\p"
	.string "It turned out to be a fossil. I never\n"
	.string "looked back.\p"
	.string "Now then. Let's see what you're made\n"
	.string "of.$"

Nexus_Text_Steven_Defeat2:
	.string "Remarkable. You're made of something\n"
	.string "harder than I thought.$"
```

</details>

**Variação 3** — [R21](../NEXUS_REGRAS.md) e dúvida: alguém disse a ele que em algum lugar ele é Campeão; espera que o outro Steven esteja bem. Aqui é um homem que olha pedras, e prefere assim: título pesa, pedra também, mas é honesta sobre isso.

**Antes da luta**

> Someone told me I'm a Champion somewhere. I hope that other me is doing well.
>
> Here, I'm a man who looks at rocks. I think I prefer it.
>
> A title is heavy. A stone is heavy too, but at least it's honest about it.
>
> Shall we?

**Derrota**

> Well fought. I think that other me would have lost too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Steven_Intro3:
	.string "Someone told me I'm a Champion\n"
	.string "somewhere. I hope that other me is\l"
	.string "doing well.\p"
	.string "Here, I'm a man who looks at rocks. I\n"
	.string "think I prefer it.\p"
	.string "A title is heavy. A stone is heavy too,\n"
	.string "but at least it's honest about it.\p"
	.string "Shall we?$"

Nexus_Text_Steven_Defeat3:
	.string "Well fought. I think that other me\n"
	.string "would have lost too.$"
```

</details>


### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Steven_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Steven é o **campeão**, a luta logo antes da Celesteela. A fala é sobre a criatura, sem dizer o nome dela.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela; para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código).

**Variação 2** — lembrança: o Steven menino via os foguetes do Space Center de Mossdeep até virarem estrelas. A criatura parece um daqueles foguetes, só que cresceu do chão. Depois: os foguetes levavam satélites, instrumentos, esperança; ele não sabe o que ela carrega — talvez tudo o que já foi. “Se ela partir, acene.”

**Antes da luta**

> As a boy, I'd visit the Space Center in Mossdeep and watch the rockets until they became stars.
>
> The creature here looks a great deal like those rockets. Except it grew out of the ground.
>
> Something that grows toward the sky, instead of being built for it. Let's battle.

**Derrota**

> You stayed grounded again. It's a rare quality.

**Depois da luta**

> The rockets I watched all carried something up. Satellites. Instruments. Hope, mostly.
>
> I can't tell what that creature is carrying.
>
> Maybe that's why it burns so hot. It's carrying everything it's ever been.
>
> Be careful. And if it leaves, wave. Someone should.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Steven_ChampionIntro2:
	.string "As a boy, I'd visit the Space Center in\n"
	.string "Mossdeep and watch the rockets until\l"
	.string "they became stars.\p"
	.string "The creature here looks a great deal\n"
	.string "like those rockets. Except it grew out\l"
	.string "of the ground.\p"
	.string "Something that grows toward the sky,\n"
	.string "instead of being built for it. Let's\l"
	.string "battle.$"

Nexus_Text_Steven_ChampionDefeat2:
	.string "You stayed grounded again. It's a rare\n"
	.string "quality.$"

Nexus_Text_Steven_ChampionAfter2:
	.string "{SPEAKER NAME_STEVEN}The rockets I watched all carried\n"
	.string "something up. Satellites. Instruments.\l"
	.string "Hope, mostly.\p"
	.string "I can't tell what that creature is\n"
	.string "carrying.\p"
	.string "Maybe that's why it burns so hot. It's\n"
	.string "carrying everything it's ever been.\p"
	.string "Be careful. And if it leaves, wave.\n"
	.string "Someone should.$"
```

</details>

**Variação 3** — ciência e melancolia: bambu cresce um metro por dia, e a criatura é bambu de aço crescendo para as estrelas na mesma velocidade. Ele senta ao lado para medir e é sempre lento demais. Depois: a lista dos brotos e das alturas — todos mais altos, todos partindo devagar. Um dia a cratera vazia e uma lista de coisas que foram embora.

**Antes da luta**

> Have you ever watched bamboo grow? It can grow a whole meter in a single day.
>
> The creature here is like bamboo made of steel, growing toward the stars at the same terrible speed.
>
> I keep sitting down beside it to measure. I'm always too slow.
>
> Perhaps you're faster. Let's find out.

**Derrota**

> Faster, and much steadier. I'll write that down.

**Depois da luta**

> I've been keeping a list. Every steel shoot here, and how tall it was when I found it.
>
> They're all taller now. Every one of them is leaving, very slowly.
>
> One day this crater will be empty, and I'll have a list of things that went away.
>
> Go on. Make it stay a little longer.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Steven_ChampionIntro3:
	.string "Have you ever watched bamboo grow? It\n"
	.string "can grow a whole meter in a single day.\p"
	.string "The creature here is like bamboo made\n"
	.string "of steel, growing toward the stars at\l"
	.string "the same terrible speed.\p"
	.string "I keep sitting down beside it to\n"
	.string "measure. I'm always too slow.\p"
	.string "Perhaps you're faster. Let's find out.$"

Nexus_Text_Steven_ChampionDefeat3:
	.string "Faster, and much steadier. I'll write\n"
	.string "that down.$"

Nexus_Text_Steven_ChampionAfter3:
	.string "{SPEAKER NAME_STEVEN}I've been keeping a list. Every steel\n"
	.string "shoot here, and how tall it was when I\l"
	.string "found it.\p"
	.string "They're all taller now. Every one of\n"
	.string "them is leaving, very slowly.\p"
	.string "One day this crater will be empty, and\n"
	.string "I'll have a list of things that went\l"
	.string "away.\p"
	.string "Go on. Make it stay a little longer.$"
```

</details>

