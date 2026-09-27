# Koga

**Região da ficha:** Kanto

Aparece no checklist como:

- **Koga — Veneno** (Kanto · Líderes de Ginásio) — ninja de Fuchsia que posteriormente entra para a Elite Four.
- **Koga — Veneno** (Johto · Elite Four e Campeão) — antigo Líder de Fuchsia promovido à Elite Four.

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
| `OBJ_EVENT_GFX_KOGA` | `graphics/object_events/pics/people/elite_four/koga.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_KOGA` | `graphics/trainers/front_pics/elite_four_koga.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_KOGA` | `graphics/field_mugshots/koga.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_KOGA_2` | 204 | 0x5CC | Toxapex Lv85, Overqwil Lv85, Roserade Lv85, Muk Alola Lv85, Scolipede Lv85, Crobat Lv85 · VS: Pink | `PokemonLeague_KogasRoom` |
| `TRAINER_KOGA_1` | 383 | 0x67F | Toxapex Lv68, Overqwil Lv69, Roserade Lv68, Muk Alola Lv68, Scolipede Lv69, Crobat Lv69 · *dupla* · VS: Pink | `PokemonLeague_KogasRoom` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_KOGA`, campeão de Pecharunt. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: No` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Eternatus**, o veneno em escala de desastre: o dragão que drenou a energia de Galar no Darkest Day. Para um mestre de Veneno, é o maior veneno que existe, e o Koga o trata com a paciência de ninja. Semi-lendário **Pecharunt**, de quem ele é campeão: Poison Puppeteer deixa confuso quem ele envenena. Mega **Scolipede** (Poisontite), a centopeia do time dele na Liga. Mais **Toxapex** e **Crobat** (time da Liga; o Crobat é o ás dele em GSC) e **Weezing**, o Pokémon do Koga desde o Red/Blue. *Plano (Singles):* atrito. O Toxapex arma Toxic Spikes e segura com Baneful Bunker e Regenerator, o Weezing queima com Will-O-Wisp, o Pecharunt envenena e confunde (Malignant Chain + Poison Puppeteer) e sai de Parting Shot, e o Eternatus fecha. *Plano (Doubles):* o Crobat dá Tailwind e Taunt, o Pecharunt espalha veneno e confusão, o Toxapex apaga boosts com Haze, e a Mega Scolipede usa Protect para acumular Speed Boost antes de atacar.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Eternatus | Life Orb | Pressure | Timid | Dynamax Cannon, Sludge Bomb, Flamethrower, Recover |
| Pecharunt | Leftovers | Poison Puppeteer | Bold | Malignant Chain, Hex, Recover, Parting Shot |
| Scolipede | Poisontite | Speed Boost | Jolly | Megahorn, Poison Jab, Swords Dance, Protect |
| Toxapex | Black Sludge | Regenerator | Bold | Toxic Spikes, Baneful Bunker, Recover, Haze |
| Crobat | Sitrus Berry | Infiltrator | Jolly | Cross Poison, U-turn, Taunt, Tailwind |
| Weezing | Rocky Helmet | Levitate | Bold | Sludge Bomb, Will-O-Wisp, Pain Split, Fire Blast |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_KOGA ===
Name: Koga
Class: Elite Four
Pic: Elite Four Koga
Gender: Male
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Eternatus @ Life Orb
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dynamax Cannon
- Sludge Bomb
- Flamethrower
- Recover

Pecharunt @ Leftovers
Bold Nature
Level: 100
Ability: Poison Puppeteer
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Malignant Chain
- Hex
- Recover
- Parting Shot

Scolipede @ Poisontite
Jolly Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Megahorn
- Poison Jab
- Swords Dance
- Protect

Toxapex @ Black Sludge
Bold Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Toxic Spikes
- Baneful Bunker
- Recover
- Haze

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Cross Poison
- U-turn
- Taunt
- Tailwind

Weezing @ Rocky Helmet
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Will-O-Wisp
- Pain Split
- Fire Blast
```

</details>


### Lendário associado

#### Pecharunt

📝 **Proposta de 27/09/2026, aguardando o autor.** **Pecharunt**. Koga é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Koga, o ninja de Fuchsia: ginásio de paredes invisíveis, técnicas de veneno, sono e confusão, depois Elite Four. Deixou o ginásio para a filha, Janine.

**A criatura.** Pecharunt, o Pokémon da subjugação. Vive numa casca de pêssego e dá mochi venenoso a pessoas e Pokémon; quem come fica preso a ele e obedece. Foi assim que prendeu os Loyal Three de Kitakami.

**O fragmento.** Uma festa de vila sem ninguém cuidando dela: lanternas acesas, barracas cheias de doces rosados de graça. As pessoas estão em fila, sorrindo para o nada, mastigando devagar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A village festival with no one running it. Lanterns lit, stalls piled high with pink rice cakes, free for the taking.
>
> People stood in neat rows, smiling at nothing, chewing slowly.

**Boss**

> Every head in the rows turned toward you at once.
>
> At the end of the path, a small peach-colored shell cracked open, and something inside it giggled.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-1025. Subjugation.
>
> A festival where everyone smiled because they had to, and an old ninja who refused a free sweet.
>
> He says nothing in this world is free except a trap.
>
> What came back with you is a tiny shell with no sweets in it. Keep it that way.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Koga cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Fwahahaha! You think you found me? No. You found the spot where I allowed you to look.
>
> I once ran a Gym of invisible walls. Children bumped their noses for an hour and thanked me afterward.
>
> Here, the walls are your own doubts. Let us see how you find your way!

**Derrota**

> Fwahaha… Your path was straighter than my walls.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>


### Diálogo associado ao lendário

#### Pecharunt

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Koga é o **campeão**, a luta logo antes do Pecharunt. A fala é sobre a criatura, sem dizer o nome dela.

O Koga passou pela barraca de doces e não comeu: um ninja reconhece veneno pelo sorriso. Quem comeu agora segue a coisinha na casca, obediente. A virada é a lealdade: a que vem de um doce não é lealdade. Depois ele fala da Janine: ensinou a ela todos os venenos e ela escolheu, sem nada a obrigando, ficar com o ginásio dele. É assim que ele sabe que foi de verdade. A criatura nunca vai saber disso; tudo em volta dela sorri porque precisa.

**Antes da luta**

> Fwahahaha! You passed the stalls of sweets on your way here, yes? Pink. Sticky. Free.
>
> I did not eat one. A ninja knows poison by its smile.
>
> Those who ate now follow the little thing in the shell. Smiling. Obedient.
>
> Loyalty that comes from a sweet is not loyalty. Let me show you the kind I trained!

**Derrota**

> Hm! My poison could not find a single gap in you.

**Depois da luta**

> I have a daughter. I taught her every poison I know, and still she chose to take my Gym.
>
> Nothing forced her. That is how I know it was real.
>
> The thing in the shell will never know that feeling. All around it smile because they must.
>
> Do not eat what it offers you. Not even one bite.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>


Falante novo: `SP_NAME_KOGA` (ainda não existe em `include/constants/speaker_names.h`).
