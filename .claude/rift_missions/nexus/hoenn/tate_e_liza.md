# Tate e Liza

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Tate e Liza — Psíquico** (Hoenn · Líderes de Ginásio) — irmãos gêmeos que lutam em perfeita sincronia.

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
| `OBJ_EVENT_GFX_TATE` | `graphics/object_events/pics/people/gym_leaders/tate.png` |
| `OBJ_EVENT_GFX_LIZA` | `graphics/object_events/pics/people/gym_leaders/liza.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_TATE_AND_LIZA` | `graphics/trainers/front_pics/leader_tate_and_liza.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_TATE_AND_LIZA_2` | 794 | 0x81A | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_TATE_AND_LIZA_3` | 795 | 0x81B | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_TATE_AND_LIZA_4` | 796 | 0x81C | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_TATE_AND_LIZA_5` | 797 | 0x81D | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_456` (ex-`TRAINER_TATE_AND_LIZA_1`, 271).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_TATE_AND_LIZA` = **1021** (flag de batalha `0x8FD`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_TateAndLiza_Fight`; campeão: `Nexus_EventScript_TateAndLiza_Latias_ChampionFight` (para Latias), `Nexus_EventScript_TateAndLiza_Latios_ChampionFight` (para Latios), `Nexus_EventScript_TateAndLiza_IronBoulder_ChampionFight` (para Iron Boulder). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Tate&Liza.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_TATE_AND_LIZA`, campeões de Latias, Latios e Iron Boulder. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

O time é um par de metades espelhadas, como Solrock e Lunatone. Lendário **Solgaleo**, o sol, que faz par com o Solrock (se o autor preferir a lua, o **Lunala** entra no mesmo lugar sem mexer no resto); semi-lendário **Latias** com Dragotite (semi + Mega, R10): da dupla Eon, os irmãos que dividem o que veem por telepatia, exatamente como os gêmeos. Mais **Solrock** e **Lunatone** (os deles), e o par **Gallade** / **Gardevoir**, irmão e irmã da mesma linha.

*Plano (Singles):* o Solrock arma Stealth Rock e queima atacantes físicos com Will-O-Wisp; a Lunatone põe as duas telas; atrás delas a Mega Latias acumula Calm Mind e se cura com Recover. O Solgaleo de Full Metal Body não perde status e a Weakness Policy transforma o golpe super efetivo em +2 de Atk e Sp. Atk.

*Plano (Doubles, o formato das batalhas deles):* Solrock e Lunatone lideram juntos (os dois com Levitate): Rock Slide de um lado, telas do outro. A Gardevoir de Telepathy não toma dano do parceiro e usa Dazzling Gleam; o Gallade protege o lado com Wide Guard; a Mega Latias e o Solgaleo fecham. Nenhum golpe do time acerta o parceiro.

Nome no `trainers.party`: `Tate&Liza` (cabe nos 10 caracteres, no estilo dos Twins do jogo, "Amy&May"), com a pic de dupla `Leader Tate And Liza`.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Solgaleo | Weakness Policy | Full Metal Body | Adamant | Sunsteel Strike, Psychic Fangs, Flare Blitz, Close Combat |
| Latias | Dragotite | Levitate | Timid | Draco Meteor, Psyshock, Recover, Calm Mind |
| Solrock | Leftovers | Levitate | Relaxed | Stealth Rock, Rock Slide, Morning Sun, Will-O-Wisp |
| Lunatone | Light Clay | Levitate | Bold | Moonblast, Psychic, Reflect, Light Screen |
| Gallade | Life Orb | Sharpness | Jolly | Sacred Sword, Psycho Cut, Leaf Blade, Wide Guard |
| Gardevoir | Choice Scarf | Telepathy | Timid | Dazzling Gleam, Psychic, Mystical Fire, Trick |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_TATE_AND_LIZA ===
Name: Tate&Liza
Class: Leader
Pic: Leader Tate And Liza
Gender: Male
Music: Intense
Double Battle: Yes
AI: Smart Trainer

Solgaleo @ Weakness Policy
Adamant Nature
Level: 100
Ability: Full Metal Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sunsteel Strike
- Psychic Fangs
- Flare Blitz
- Close Combat

Latias @ Dragotite
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Psyshock
- Recover
- Calm Mind

Solrock @ Leftovers
Relaxed Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Rock Slide
- Morning Sun
- Will-O-Wisp

Lunatone @ Light Clay
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Psychic
- Reflect
- Light Screen

Gallade @ Life Orb
Jolly Nature
Level: 100
Ability: Sharpness
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sacred Sword
- Psycho Cut
- Leaf Blade
- Wide Guard

Gardevoir @ Choice Scarf
Timid Nature
Level: 100
Ability: Telepathy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dazzling Gleam
- Psychic
- Mystical Fire
- Trick
```

</details>


### Lendário associado

#### Latias

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Latias_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Latias**. Tate e Liza é os campeões dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Tate e Liza, os gêmeos Líderes de Mossdeep, especialistas em Psíquico, que lutam em sincronia perfeita.

**A criatura.** Latias, da dupla Eon com o Latios. Entende a fala humana e se torna invisível dobrando a luz com as penas, que parecem vidro. Os dois irmãos vivem juntos e se comunicam por telepatia.

**O fragmento.** Uma ilha ao entardecer, num mar liso como vidro. O ar acima da água se dobra como calor sobre o asfalto, e de vez em quando se dobra no formato de asas.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An island at dusk, in a sea as still as glass.
>
> The air above the water kept bending, like heat over a road. Now and then, it bent into the shape of wings.

**Boss**

> The bent air folded in on itself and became something red and white, hovering at eye level.
>
> It tilted its head, the way a person does when they are listening.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-380. The Eon Sister.
>
> An island where the air hides someone who understands every word you say, and twins who have never needed words.
>
> What came back with you hides behind my coat whenever I look at it directly. So I have stopped looking directly. We get along much better.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>

#### Latios

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Latios_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Latios**. Tate e Liza é os campeões dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Tate e Liza, os gêmeos de Mossdeep. O Tate sempre fala primeiro; a Liza repete.

**A criatura.** Latios, da dupla Eon com a Latias. Consegue mostrar a outros, por telepatia, o que está vendo, e entende a fala humana. Protege a irmã.

**O fragmento.** Uma ilha ao entardecer com o céu cheio de imagens: cidades nunca visitadas, salas meio lembradas, rostos vistos de cima, tudo passando como se alguém longe dividisse o que vê.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An island at dusk. The sky was full of pictures.
>
> Cities you had never visited, rooms you half remembered, faces seen from above. All of it drifted past, as if someone far away were sharing what it saw.

**Boss**

> The pictures stopped.
>
> Something blue and white came down out of them, fast, and for a moment you saw yourself through its eyes.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-381. The Eon Brother.
>
> An island where someone shares everything it sees, and twins who have never had a thought they did not share.
>
> What came back with you showed me, very briefly, my own desk. From above. It needs tidying. I did not need to be told.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>

#### Iron Boulder

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronBoulder_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Boulder**. Tate e Liza é os campeões dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Tate e Liza, os gêmeos de Mossdeep, a quem todo mundo chama de "duas metades de uma pessoa só". Pedra e Psíquico, como o Solrock e a Lunatone deles.

**A criatura.** Iron Boulder (Pedra/Psíquico) é um Paradoxo da Area Zero: parece um Terrakion de um futuro possível, de pedra e metal, com um chifre que corta como lâmina (Mighty Cleave).

**O fragmento.** Um campo de pedras, todas cortadas ao meio com um golpe limpo. As duas metades de cada uma ficam uma de frente para a outra, com as faces lisas e brilhantes como espelhos.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste Paradoxo):

**Chegada**

> A field of boulders, every one of them cut cleanly in half.
>
> The two halves of each stone lay facing each other, their cut sides as smooth and bright as mirrors.

**Boss**

> One more boulder split, with a sound like a bell.
>
> Between the halves stood something shaped like a great horned beast, built of stone and metal. Its horn hummed like a blade.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-1022. The Blade Stone.
>
> A field where every stone was split into a pair, and twins who have spent their whole lives being called two halves of one thing.
>
> What came back with you is one piece, whole, and cold to the touch. I thought the twins would want to know that.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_TateAndLiza_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Tate e Liza caem numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala deles mesmos, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hehehe… Were you surprised?  
> Fufufu… Were you surprised?
>
> We don't know how we got here.  
> But we got here together. We always do.
>
> We can tell what you're thinking.  
> So can we. Shall we begin?

**Derrota**

> We lost…  
> …together, at least.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>


### Diálogo associado ao lendário

#### Latias

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_TateAndLiza_Latias_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Tate e Liza são os **campeões**, a luta logo antes da Latias. A fala é sobre a criatura, sem dizer o nome dela.

A criatura se esconde na luz, mas ouve tudo e entende as pessoas melhor do que muita gente. Os gêmeos sempre foram vistos em par, nunca um de cada vez. A virada é da Liza, a que fala em segundo: ela pede para dizer uma coisa sozinha, uma vez, e confessa que às vezes quis ser invisível, para saber quem era sem eco. Mas a criatura não se esconde para ficar sozinha: esconde-se para escutar alguém que ama, e o irmão está sempre por perto.

**Antes da luta**

> It hides in the light. It bends the air around itself, so no one can see it.
>
> But it hears everything. Every word. It understands people better than most people do.
>
> We have always been seen as a pair.  
> Never one at a time.
>
> Hehehe…  
> Fufufu… Let's battle, as a pair!

**Derrota**

> We lost…  
> …and we both saw it coming.

**Depois da luta**

> Can I say something alone, just once?  
> …Thank you, brother.
>
> Sometimes I wanted to be like that creature. Invisible. Just to know who I was, without an echo.
>
> But it doesn't hide to be alone. It hides so it can listen to someone it loves. Its brother is always close by.
>
> Hehehe…  
> Fufufu… Go on. It's listening already.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

#### Latios

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_TateAndLiza_Latios_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Tate e Liza são os **campeões**, a luta logo antes do Latios. A fala é sobre a criatura, sem dizer o nome dela.

A criatura manda para os outros o que vê: cidades, céus, rostos. Os gêmeos fazem isso a vida toda, o que um vê o outro já sabe; estranho, para eles, é ficar sozinho dentro da própria cabeça. A virada: as imagens não são para diversão, servem para avisar do perigo a tempo de o outro fugir. O Tate achava que falava primeiro por ser o mais velho (por três minutos); a Liza sempre soube o motivo: era para ele levar o golpe primeiro.

**Antes da luta**

> It shows you what it sees. Cities, skies, faces. It sends them to anyone who can listen.
>
> We've done that our whole lives.  
> Whatever one of us sees, the other already knows.
>
> People think that's strange.  
> We think being alone in your own head is strange.
>
> Hehehe…  
> Fufufu… Let's see what you're thinking!

**Derrota**

> We saw it coming…  
> …and we still couldn't stop it.

**Depois da luta**

> The pictures it sends aren't for fun. It shows danger, so the other one can get away in time.
>
> I always speak first. I thought it was because I'm the older one. …By three minutes.
>
> Liza says she always knew why. It was so I'd be the one who got hit first.
>
> …Fufufu. Now he's embarrassed. Go on, before he starts blushing.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

#### Iron Boulder

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_TateAndLiza_IronBoulder_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Tate e Liza são os **campeões**, a luta logo antes do Iron Boulder. A fala é sobre a criatura, sem dizer o nome dela.

A criatura corta tudo em dois, e as metades ficam se olhando como espelhos. É Pedra e Psíquico como o Solrock e a Lunatone deles, só que de um tempo que não aconteceu. Os gêmeos passaram a vida ouvindo que são "duas metades de uma pessoa" e gostariam de trocar uma palavra com quem inventou isso. A virada: nas pedras cortadas, as duas faces são lisas; nenhuma é a metade quebrada. Eles não são metades, são duas pessoas inteiras que concordam em quase tudo. Quase: ele gosta do sol, ela da lua.

**Antes da luta**

> Every stone out there has been cut in two. The halves lie facing each other, like mirrors.
>
> Rock and Psychic, just like our Solrock and Lunatone. But it isn't from our time. It's from one that hasn't happened.
>
> People always call us two halves of one person.  
> Hehehe… Fufufu…
>
> We'd like a word with whoever started that. Let's battle!

**Derrota**

> Two against one…  
> …and still you won.

**Depois da luta**

> Did you look at the cut stones? Both halves were smooth. Neither one was the broken one.
>
> We aren't halves. We're two whole people who happen to agree about almost everything.
>
> Almost. He likes the sun. I like the moon.  
> Hehehe… Fufufu…
>
> That thing cuts everything in two. Go show it something that stays whole.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

Falante novo: `SP_NAME_TATE_AND_LIZA` (não existe ainda em `include/constants/speaker_names.h`).
