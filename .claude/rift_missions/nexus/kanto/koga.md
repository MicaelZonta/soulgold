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
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

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

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_KOGA` = **991** (flag de batalha `0x8DF`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Koga_Fight`; campeão: `Nexus_EventScript_Koga_ChampionFight` (para Pecharunt). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Koga.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Pecharunt_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Koga_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas para Koga, com a variação 1 (acima, já no jogo) formam as três do sorteio. Mesmo registro do [R16](../NEXUS_REGRAS.md): fala de si, sem citar o lugar nem a criatura do dia.

**Variação 2 — a provocação do ninja.** Humor e provocação: ele está atrás do jogador há três salas… e agora, obviamente, na frente. A lição dupla do Koga: ninja nunca está onde se olha, veneno nunca tem o gosto que parece.

**Antes da luta**

> Fwahahaha! I have been standing behind you for three rooms. You did not notice.
>
> No, do not turn around. I am in front of you now. Obviously.
>
> A ninja is never where you look. A poison is never what you taste. Learn both lessons today!

**Derrota**

> Fwahaha… You looked in the right place. How very rude.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Koga_Intro2:
	.string "Fwahahaha! I have been standing behind\n"
	.string "you for three rooms. You did not notice.\p"
	.string "No, do not turn around. I am in front of\n"
	.string "you now. Obviously.\p"
	.string "A ninja is never where you look. A poison\n"
	.string "is never what you taste. Learn both\l"
	.string "lessons today!$"

Nexus_Text_Koga_Defeat2:
	.string "Fwahaha… You looked in the right place.\n"
	.string "How very rude.$"
```

</details>

**Variação 3 — a Liga que nunca perdeu.** O que o fragmento dele tem de diferente (R21): uma Elite Four que nenhum desafiante jamais passou. Para o Koga isso não é força, é porta trancada. Prepara o diário (Liga de Kanto).

**Antes da luta**

> Hm. You have the look of one who wins. I have not faced that look in a long time.
>
> Where I come from, I sat among the Elite Four. No challenger ever passed us. Not one, in all those years.
>
> That is not strength. It is a locked door. Show me whether you are the key!

**Derrota**

> …So. The door was never locked. Only unopened.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Koga_Intro3:
	.string "Hm. You have the look of one who wins. I\n"
	.string "have not faced that look in a long time.\p"
	.string "Where I come from, I sat among the Elite\n"
	.string "Four. No challenger ever passed us. Not\l"
	.string "one, in all those years.\p"
	.string "That is not strength. It is a locked\n"
	.string "door. Show me whether you are the key!$"

Nexus_Text_Koga_Defeat3:
	.string "…So. The door was never locked. Only\n"
	.string "unopened.$"
```

</details>


### Diálogo associado ao lendário

#### Pecharunt

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Koga_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário; com a variação 1 (acima, já no jogo) formam as três. Sobre a criatura, sem dizer o nome dela; só o `ChampionAfter` leva plaquinha.

**Variação 2 — o veneno sem gosto.** O profissional do veneno: provou cem venenos e deu nome a todos; este não tem gosto, é doce e a pessoa simplesmente concorda. Ele o batizou de "Yes". Depois, a lenda dos três vassalos de Kitakami, que comeram primeiro e ganharam estátuas de herói — mestre que precisa de doce para ser servido é mestre fraco.

**Antes da luta**

> Fwahahaha! Poison is my craft. I have tasted a hundred kinds and lived to name each one.
>
> The little shell's poison has no taste at all. It is sweet, and then you simply agree.
>
> A ninja who cannot name a poison cannot fight it. So I have named it. 'Yes.'
>
> Now, let us see how you say no!

**Derrota**

> Fwahaha! A firm no. Excellent!

**Depois da luta**

> The old tales of the north speak of three retainers who served a small master. They ate first.
>
> Then they fought for it, and lied for it, and let a village raise statues to them as heroes.
>
> All for a sweet. A master who needs a sweet to be served is a weak master.
>
> If it hides behind the others, strike the shell. Only the shell.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Koga_ChampionIntro2:
	.string "Fwahahaha! Poison is my craft. I have\n"
	.string "tasted a hundred kinds and lived to\l"
	.string "name each one.\p"
	.string "The little shell's poison has no taste\n"
	.string "at all. It is sweet, and then you simply\l"
	.string "agree.\p"
	.string "A ninja who cannot name a poison cannot\n"
	.string "fight it. So I have named it. 'Yes.'\p"
	.string "Now, let us see how you say no!$"

Nexus_Text_Koga_ChampionDefeat2:
	.string "Fwahaha! A firm no. Excellent!$"

Nexus_Text_Koga_ChampionAfter2:
	.string "{SPEAKER NAME_KOGA}The old tales of the north speak of\n"
	.string "three retainers who served a small\l"
	.string "master. They ate first.\p"
	.string "Then they fought for it, and lied for it,\n"
	.string "and let a village raise statues to them\l"
	.string "as heroes.\p"
	.string "All for a sweet. A master who needs a\n"
	.string "sweet to be served is a weak master.\p"
	.string "If it hides behind the others, strike\n"
	.string "the shell. Only the shell.$"
```

</details>

**Variação 3 — os colegas que comeram.** O que ele perdeu (R21 + fio da Liga): entre os que sorriem em fila estão dois colegas da Elite Four; o terceiro, "o mascarado", saiu antes dos doces (aceno ao Will, que no fio da Liga leva o rei). O pior veneno é o que deixa a gente feliz. Termina pedindo que o jogador lembre um nome — o dele.

**Antes da luta**

> Hm. You walked between the smiling ones without looking at them. Good. Do not look.
>
> Two of them I once called colleagues. The third, the one in the mask, left before the sweets came.
>
> They were hungry for something. I never knew what. The little shell knew.
>
> It will not take one more. Face me!

**Derrota**

> Your will was sharper than any blade I own.

**Depois da luta**

> The worst poison is not the one that kills. It is the one that makes you glad.
>
> My old colleagues are glad now. Glad and quiet. I bring them tea, and they do not remember my name.
>
> If it offers you anything, remember a name first. Yours, or mine. Hold it in your teeth.
>
> …Koga. Remember that one.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Koga_ChampionIntro3:
	.string "Hm. You walked between the smiling ones\n"
	.string "without looking at them. Good. Do not\l"
	.string "look.\p"
	.string "Two of them I once called colleagues.\n"
	.string "The third, the one in the mask, left\l"
	.string "before the sweets came.\p"
	.string "They were hungry for something. I never\n"
	.string "knew what. The little shell knew.\p"
	.string "It will not take one more. Face me!$"

Nexus_Text_Koga_ChampionDefeat3:
	.string "Your will was sharper than any blade I\n"
	.string "own.$"

Nexus_Text_Koga_ChampionAfter3:
	.string "{SPEAKER NAME_KOGA}The worst poison is not the one that\n"
	.string "kills. It is the one that makes you glad.\p"
	.string "My old colleagues are glad now. Glad and\n"
	.string "quiet. I bring them tea, and they do not\l"
	.string "remember my name.\p"
	.string "If it offers you anything, remember a\n"
	.string "name first. Yours, or mine. Hold it in\l"
	.string "your teeth.\p"
	.string "…Koga. Remember that one.$"
```

</details>



Falante novo: `SP_NAME_KOGA` (ainda não existe em `include/constants/speaker_names.h`).
