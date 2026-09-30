# Jasmine

**Região da ficha:** Johto

Aparece no checklist como:

- **Jasmine — Aço** (Johto · Líderes de Ginásio) — gentil Líder de Olivine e cuidadora do Ampharos do farol.

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
| `OBJ_EVENT_GFX_JASMINE` | `graphics/object_events/pics/people/gym_leaders/jasmine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_JASMINE` | `graphics/trainers/front_pics/leader_jasmine.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_JASMINE` | `graphics/field_mugshots/jasmine.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_JASMINE_1_3` | 180 | 0x5B4 | Corviknight Lv48, Tinkaton Lv49, Magnezone Lv48, Scizor Lv49, Steelix Lv49 · *dupla* · VS: Blue | `OlivineCity_Gym` |
| `TRAINER_JASMINE` | 359 | 0x667 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_JASMINE_2` | 427 | 0x6AB | Corviknight Lv78, Magnezone Lv78, Metagross Lv78, Steelix Lv78, Archaludon Lv79, Lucario Lv80 · *dupla* | `KitakamiRoad_House`, `OlivineCity_Cafe`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_JASMINE_1` | 513 | 0x701 | Corviknight Lv42, Tinkaton Lv42, Magnezone Lv42, Scizor Lv42, Steelix Lv42 · *dupla* · VS: Blue | `OlivineCity_Gym` |
| `TRAINER_JASMINE_1_2` | 651 | 0x78B | Corviknight Lv45, Tinkaton Lv45, Magnezone Lv45, Scizor Lv45, Steelix Lv45 · *dupla* · VS: Blue | `OlivineCity_Gym` |
| `TRAINER_TITLE_DEFENSE_JASMINE` | 896 | 0x880 | Skarmory Lv85, Magnezone Lv85, Metagross Lv85, Dialga Lv85, Archaludon Lv85, Lucario Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_JASMINE` = **1006** (flag de batalha `0x8EE`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Jasmine_Fight`; campeão: `Nexus_EventScript_Jasmine_Lugia_ChampionFight` (para Lugia), `Nexus_EventScript_Jasmine_Melmetal_ChampionFight` (para Melmetal). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Jasmine.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_JASMINE`, campeã da Lugia e do Melmetal. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Dialga**, o Aço que controla o tempo, já do time dela na Title Defense; aqui ele é quem arma o Trick Room de um time pesado e lento. (A Jasmine também é campeã da Lugia, a guardiã do mar de Olivine; a Lugia não entra para o time ter um só lendário e ficar de Aço.) Semi-lendário **Melmetal**, o Aço que se desfaz e volta pequeno, a criatura de que ela é campeã. Mega **Steelix** (Steeltite), o ás dela desde Gold/Silver. Mais **Ampharos**, a Amphy do farol, Skarmory (do time de Gold/Silver) e Archaludon.

*Plano (Singles):* o Skarmory põe Spikes, o Steelix (Sturdy) põe Stealth Rock, o Dialga arma Trick Room e, com ele, Melmetal, Mega Steelix e Archaludon batem primeiro; a Ampharos faz pivot com Volt Switch. *Plano (Doubles):* Trick Room do Dialga no turno 1 com o parceiro batendo, Rock Slide do Steelix, Electro Shot sem carregar (Power Herb) e Dazzling Gleam nos dois alvos. Sem Trick Room, o time ainda aguenta pelas resistências do Aço.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Dialga | Adamant Orb | Pressure | Quiet | Trick Room, Draco Meteor, Flash Cannon, Fire Blast |
| Melmetal | Assault Vest | Iron Fist | Brave | Double Iron Bash, Thunder Punch, Ice Punch, Superpower |
| Steelix | Steeltite | Sturdy | Brave | Heavy Slam, Stomping Tantrum, Rock Slide, Stealth Rock |
| Ampharos | Sitrus Berry | Static | Quiet | Thunderbolt, Dragon Pulse, Dazzling Gleam, Volt Switch |
| Skarmory | Rocky Helmet | Sturdy | Impish | Spikes, Brave Bird, Body Press, Roost |
| Archaludon | Power Herb | Stamina | Modest | Electro Shot, Flash Cannon, Draco Meteor, Body Press |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_JASMINE ===
Name: Jasmine
Class: Leader
Pic: Leader Jasmine
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Dialga @ Adamant Orb
Quiet Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Draco Meteor
- Flash Cannon
- Fire Blast

Melmetal @ Assault Vest
Brave Nature
Level: 100
Ability: Iron Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double Iron Bash
- Thunder Punch
- Ice Punch
- Superpower

Steelix @ Steeltite
Brave Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Stomping Tantrum
- Rock Slide
- Stealth Rock

Ampharos @ Sitrus Berry
Quiet Nature
Level: 100
Ability: Static
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Dragon Pulse
- Dazzling Gleam
- Volt Switch

Skarmory @ Rocky Helmet
Impish Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spikes
- Brave Bird
- Body Press
- Roost

Archaludon @ Power Herb
Modest Nature
Level: 100
Ability: Stamina
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Electro Shot
- Flash Cannon
- Draco Meteor
- Body Press
```

</details>

### Lendário associado

#### Lugia

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Lugia_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Lugia**. Jasmine é a campeã dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Jasmine, Líder de Olivine, tímida e gentil, que cuida da Ampharos que ilumina o farol da cidade.

**A criatura.** Lugia, a guardiã dos mares. Dorme no fundo do mar, nas Whirl Islands, perto de Olivine, porque um único bater das asas dela basta para uma tempestade de quarenta dias.

**O fragmento.** Um farol no mar aberto, sem costa e sem cidade. A cada volta da luz aparecem ondas congeladas no meio da quebra, como vidro, e embaixo da torre gira um redemoinho enorme.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A lighthouse standing in the open sea. No shore, no town. Just the tower and its light.
>
> Every sweep of the beam lit up waves that had frozen mid-crash, like glass.

**Boss**

> The whirlpool under the tower went quiet.
>
> Something silver rose out of it, and when it opened its wings, the frozen waves began to fall.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-249. Guardian of the Deep.
>
> A lighthouse with no harbor, and a Gym Leader who could not stop worrying about the ships that were not there.
>
> What you brought back fits in your two hands. The sea stayed calm for it.
>
> She kept the light on the whole time. I have noted that I never asked her to.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>

#### Melmetal

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Melmetal_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Melmetal**. Jasmine é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Jasmine, a mesma, que ama o Aço porque ele dura.

**A criatura.** Melmetal, a evolução do Meltan (neste hack, no nível 60). Era venerado na antiguidade por criar ferro do nada e voltou à vida depois de 3.000 anos. No fim da vida enferruja e se desfaz, e os pedaços que sobram renascem como Meltan.

**O fragmento.** Uma forja antiga debaixo da terra. Ferro derretido corre em canais pelo chão como água num jardim, e milhares de porquinhas de metal rolam sozinhas pela pedra, todas para o mesmo lugar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An ancient forge, deep underground. Molten iron ran through channels in the floor like water in a garden.
>
> Thousands of little hex nuts were rolling across the stone. All of them toward the same place.

**Boss**

> The hex nuts stopped rolling.
>
> They had built something out of themselves, and it looked at you with a single bright eye.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-809. Hex Nut.
>
> A forge where iron comes from nothing, and a young woman who loves steel because it lasts.
>
> What you carried out of the forge was small, and it fit in your hand.
>
> I told her this one falls apart in the end and comes back small. She said that counts as lasting.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Jasmine_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Jasmine cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> ...Oh. Um. Hello.
>
> I'm sorry. I get nervous with people I don't know. With Steel Pokémon, I never do.
>
> They're hard on the outside because they care about what's inside. So am I. ...Please, let's begin.

**Derrota**

> ...You were very kind to my Pokémon, even while beating them. Thank you.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas para as **quatro primeiras salas** ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. A variação 1 é a de cima, que já está no jogo; o sorteio de qual variação toca ainda não existe no código.

**Variação 2** — o remédio que ninguém trouxe. No fragmento dela, a criança que devia atravessar o mar com o remédio da Ampharos nunca veio, e ela aprendeu a remar (R21: brinca com o jogador sem depender dele).

**Antes da luta**

> …Um. Hello. Do you ever feel like someone was supposed to come, and didn't?
>
> Once, my Ampharos fell ill. I waited by the window for someone to cross the sea with medicine.
>
> Nobody came. So I learned to row. …I'm stronger than I look. Please, let's battle.

**Derrota**

> …You would have come. I can tell. Thank you anyway.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Jasmine_Intro2:
	.string "…Um. Hello. Do you ever feel like someone\n"
	.string "was supposed to come, and didn't?\p"
	.string "Once, my Ampharos fell ill. I waited by\n"
	.string "the window for someone to cross the\l"
	.string "sea with medicine.\p"
	.string "Nobody came. So I learned to row. …I'm\n"
	.string "stronger than I look. Please, let's\l"
	.string "battle.$"

Nexus_Text_Jasmine_Defeat2:
	.string "…You would have come. I can tell. Thank\n"
	.string "you anyway.$"
```

</details>

**Variação 3** — o aço quente. Humor tímido: ela explica como faz amigos do mesmo jeito que o aço esquenta na mão.

**Antes da luta**

> Um… may I tell you something? People think Steel Pokémon are cold to the touch.
>
> They're not. If you hold one long enough, it becomes exactly as warm as your hand.
>
> …That's how I make friends, too. Slowly. Shall we begin?

**Derrota**

> …Your hands must be very warm. My Pokémon liked you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Jasmine_Intro3:
	.string "Um… may I tell you something? People\n"
	.string "think Steel Pokémon are cold to the\l"
	.string "touch.\p"
	.string "They're not. If you hold one long\n"
	.string "enough, it becomes exactly as warm as\l"
	.string "your hand.\p"
	.string "…That's how I make friends, too. Slowly.\n"
	.string "Shall we begin?$"

Nexus_Text_Jasmine_Defeat3:
	.string "…Your hands must be very warm. My\n"
	.string "Pokémon liked you.$"
```

</details>

### Diálogo associado ao lendário

#### Lugia

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Jasmine_Lugia_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Jasmine é a **campeã**, a luta logo antes da Lugia. A fala é sobre a criatura, sem dizer o nome dela.

A Jasmine vive num farol. Aqui há um farol sem navio nenhum, e ela conferiu a luz mesmo assim, duas vezes. A criatura que dorme embaixo do redemoinho também é um farol, vigia o mar inteiro, mas se esconde: é forte a ponto de um bater de asas ser uma tempestade. A virada é sobre a própria timidez: em casa dizem que ela é quieta demais. A criatura dorme no fundo do mar de propósito, para não machucar ninguém, e ninguém a chama de quieta demais.

**Antes da luta**

> There's a lighthouse here, but there are no ships. I checked the light anyway. Twice.
>
> The one sleeping under the whirlpool is like a lighthouse too. It watches the whole sea.
>
> ...But it hides. It's so strong that one beat of its wings is a storm. Please... let's battle.

**Derrota**

> ...Your light was brighter than mine.

**Depois da luta**

> Back home, people say I'm too quiet. That I should speak up more.
>
> It sleeps at the bottom of the sea on purpose, so it won't hurt anyone. Nobody calls it too quiet.
>
> ...Please be gentle when you wake it. I'll keep the light on for you.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — a pena prateada que subiu do redemoinho até a galeria do farol. Ela não sabe se é obrigado ou adeus; na derrota, decide. A pena some (fio do diário).

**Antes da luta**

> I found a feather on the gallery of the lighthouse. Silver, and cold, like a spoon left out at night.
>
> It must have come from the one below. It never comes up. But it left this, for the light.
>
> …Maybe it's saying thank you. Or maybe goodbye. Let's battle, and I'll decide.

**Derrota**

> …I think it was thank you.

**Depois da luta**

> I keep the feather in my pocket. It hums when the sea gets rough.
>
> If it hums while you're down there, please don't be afraid. It means the sea is listening.
>
> …Oh. And if the feather goes missing, it wasn't me. It does that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Jasmine_Lugia_ChampionIntro2:
	.string "I found a feather on the gallery of the\n"
	.string "lighthouse. Silver, and cold, like a\l"
	.string "spoon left out at night.\p"
	.string "It must have come from the one below.\n"
	.string "It never comes up. But it left this, for\l"
	.string "the light.\p"
	.string "…Maybe it's saying thank you. Or maybe\n"
	.string "goodbye. Let's battle, and I'll decide.$"

Nexus_Text_Jasmine_Lugia_ChampionDefeat2:
	.string "…I think it was thank you.$"

Nexus_Text_Jasmine_Lugia_ChampionAfter2:
	.string "{SPEAKER NAME_JASMINE}I keep the feather in my pocket. It\n"
	.string "hums when the sea gets rough.\p"
	.string "If it hums while you're down there,\n"
	.string "please don't be afraid. It means the\l"
	.string "sea is listening.\p"
	.string "…Oh. And if the feather goes missing, it\n"
	.string "wasn't me. It does that.$"
```

</details>

**Variação 3** — a dúvida: acordar a criatura é certo? A Jasmine faz um trato tímido: se ganhar, deixam dormir. Perde, e pede que o jogador bata como numa porta.

**Antes da luta**

> …Can I ask you something first? Do you have to wake it?
>
> It has slept down there so long that the whirlpool turns around it like a music box.
>
> I'll battle you. But if I win, you let it sleep. Is that fair?

**Derrota**

> …That's fair. You won. You may wake it.

**Depois da luta**

> Then please wake it gently. Knock, like on a door. Don't shout.
>
> When it opens its eyes, the first thing it will see is my light. I made sure of that.
>
> …That way it'll know someone was here. Someone kept watch.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Jasmine_Lugia_ChampionIntro3:
	.string "…Can I ask you something first? Do you\n"
	.string "have to wake it?\p"
	.string "It has slept down there so long that\n"
	.string "the whirlpool turns around it like a\l"
	.string "music box.\p"
	.string "I'll battle you. But if I win, you let it\n"
	.string "sleep. Is that fair?$"

Nexus_Text_Jasmine_Lugia_ChampionDefeat3:
	.string "…That's fair. You won. You may wake it.$"

Nexus_Text_Jasmine_Lugia_ChampionAfter3:
	.string "{SPEAKER NAME_JASMINE}Then please wake it gently. Knock, like\n"
	.string "on a door. Don't shout.\p"
	.string "When it opens its eyes, the first thing\n"
	.string "it will see is my light. I made sure of\l"
	.string "that.\p"
	.string "…That way it'll know someone was here.\n"
	.string "Someone kept watch.$"
```

</details>

#### Melmetal

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Jasmine_Melmetal_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Jasmine é a **campeã**, a luta logo antes do Melmetal. A fala é sobre a criatura, sem dizer o nome dela.

A Jasmine ama o Aço porque ele dura: chuva, anos, batalhas. A criatura da forja envelhece, enferruja, se desfaz e volta pequena, e ela não sabe se isso é triste ou bonito. A virada vem pela Amphy: quando a Ampharos adoeceu no farol, a Jasmine achou que a resposta era ser duro e não quebrar. Mas a Amphy não melhorou por ser dura; melhorou porque alguém atravessou o mar com o remédio. Coisas quebram, coisas voltam.

**Antes da luta**

> I love steel because it lasts. Rain, years, battles. It stays.
>
> But the one in the forge... when it grows old, it rusts. It falls apart. And then it comes back, very small.
>
> ...I don't know if that's sad or beautiful. Maybe battling will tell me.

**Derrota**

> ...Ah. I've fallen apart a little.

**Depois da luta**

> When my Ampharos got sick at the lighthouse, I thought steel was the answer. Be hard. Don't break.
>
> But it didn't get better by being hard. It got better because someone crossed the sea with medicine.
>
> I think that creature knows. Things break. Things come back. Please go and meet it.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — as porquinhas que seguem a Jasmine pela forja. Humor: elas esperavam que ela fosse de ferro. A virada: a criatura é milhares de pedacinhos decidindo ser uma coisa só, como um Ginásio.

**Antes da luta**

> When I came in, three little hex nuts followed me. They rolled right behind my shoes.
>
> I think they were hoping I was made of iron. I'm sorry. I'm only a Gym Leader.
>
> …They're still behind me. Please be careful where you step. Let's begin.

**Derrota**

> …Oh. They've rolled over to you now.

**Depois da luta**

> They go wherever something strong is standing. I think that's how the big one is made.
>
> Thousands of little pieces, deciding to be one thing together.
>
> …My Gym is a bit like that. Please go. They're waiting to see what you're made of.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Jasmine_Melmetal_ChampionIntro2:
	.string "When I came in, three little hex nuts\n"
	.string "followed me. They rolled right behind my\l"
	.string "shoes.\p"
	.string "I think they were hoping I was made of\n"
	.string "iron. I'm sorry. I'm only a Gym Leader.\p"
	.string "…They're still behind me. Please be\n"
	.string "careful where you step. Let's begin.$"

Nexus_Text_Jasmine_Melmetal_ChampionDefeat2:
	.string "…Oh. They've rolled over to you now.$"

Nexus_Text_Jasmine_Melmetal_ChampionAfter2:
	.string "{SPEAKER NAME_JASMINE}They go wherever something strong is\n"
	.string "standing. I think that's how the big\l"
	.string "one is made.\p"
	.string "Thousands of little pieces, deciding to\n"
	.string "be one thing together.\p"
	.string "…My Gym is a bit like that. Please go.\n"
	.string "They're waiting to see what you're\l"
	.string "made of.$"
```

</details>

**Variação 3** — a grade do farol que enferruja todo inverno e ela lixa e pinta toda primavera. A criatura não se conserta: se desfaz e confia nos pedaços. A Jasmine acha isso coragem que ela não tem.

**Antes da luta**

> The railing of my lighthouse rusts every winter. Every spring I sand it and paint it again.
>
> People say that's wasted work. I think it's the whole point.
>
> …I'd like to know what the one in the forge would say. Please, let's battle.

**Derrota**

> …I'll need a new coat of paint.

**Depois da luta**

> The one in the forge doesn't sand itself or paint itself. It just falls apart, and trusts the pieces.
>
> I'm not that brave. I paint the railing.
>
> …Please tell it I think it's brave. It probably won't care. Tell it anyway.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Jasmine_Melmetal_ChampionIntro3:
	.string "The railing of my lighthouse rusts\n"
	.string "every winter. Every spring I sand it and\l"
	.string "paint it again.\p"
	.string "People say that's wasted work. I think\n"
	.string "it's the whole point.\p"
	.string "…I'd like to know what the one in the\n"
	.string "forge would say. Please, let's battle.$"

Nexus_Text_Jasmine_Melmetal_ChampionDefeat3:
	.string "…I'll need a new coat of paint.$"

Nexus_Text_Jasmine_Melmetal_ChampionAfter3:
	.string "{SPEAKER NAME_JASMINE}The one in the forge doesn't sand\n"
	.string "itself or paint itself. It just falls\l"
	.string "apart, and trusts the pieces.\p"
	.string "I'm not that brave. I paint the railing.\p"
	.string "…Please tell it I think it's brave. It\n"
	.string "probably won't care. Tell it anyway.$"
```

</details>

Falante novo: `SP_NAME_JASMINE` (ainda não existe em `include/constants/speaker_names.h`; skill `nomear-falante`).
