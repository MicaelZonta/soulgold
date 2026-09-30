# Archer

**Região da ficha:** Kanto

Aparece no checklist como:

- **Archer** (Kanto · Team Rocket) — executivo de alto escalão que tenta restaurar o Team Rocket.
- **Archer** (Johto · Team Rocket) — comanda a tentativa de trazer Giovanni de volta.

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
| `OBJ_EVENT_GFX_ARCHER` | `graphics/object_events/pics/people/rockets/archer.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ARCHER` | `graphics/trainers/front_pics/archer.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_ARCHER` | `graphics/field_mugshots/archer.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_ARCHER_1` | 273 | 0x611 | Weezing Lv39, Tauros Lv38, Houndoom Lv38 | `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_ARCHER_4` | 276 | 0x614 | Porygon Z Lv39, Tauros Lv38, Gyarados Lv39, Houndoom Lv38, Slowbro Lv40 | `src/battle_setup.c` |
| `TRAINER_ARCHER_5` | 277 | 0x615 | Porygon Z Lv39, Tauros Lv38, Gyarados Lv39, Houndoom Lv38, Slowbro Lv40 | `src/battle_setup.c` |
| `TRAINER_ARCHER` | 468 | 0x6D4 | Ninetales Lv54, Tauros Paldea Blaze Lv55, Marowak Alola Lv54, Rotom Heat Lv55, Slowking Galar Lv55, Houndoom Lv57 | `GoldenrodCity_RadioTower_5F`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ARCHER` = **996** (flag de batalha `0x8E4`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Archer_Fight`; campeão: `Nexus_EventScript_Archer_Marshadow_ChampionFight` (para Marshadow), `Nexus_EventScript_Archer_WoChien_ChampionFight` (para Wo-Chien). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Archer.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_ARCHER`, campeão de Marshadow e Wo-Chien. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Mewtwo**: poder fabricado num laboratório, o tipo de arma que o Team Rocket sempre quis ter nas mãos. Semi-lendário **Wo-Chien**, de que ele é campeão: tábuas de madeira e rancor, e o Archer é quem guarda os registros da organização. Mega **Houndoom** (Darktite), o ás dele desde Johto. Mais **Weezing** (o Koffing de HGSS), **Slowking-Galar** e **Rotom-Wash** (Levitate, cobre o ponto fraco a Terra do Houndoom), do time dele neste hack. A sinergia é o Tablets of Ruin: ele corta o Ataque físico de **todo mundo** em campo, menos do Wo-Chien, e o time do Archer é todo especial, então o corte só dói do lado do jogador.

*Plano (Singles):* Weezing espalha Toxic Spikes e queima com Will-O-Wisp; Slowking-Galar pivota com Chilly Reception e volta pelo Regenerator; Wo-Chien segura com Leech Seed e Protect; a Mega Houndoom sobe com Nasty Plot e o Mewtwo limpa. Rotom-Wash pivota com Volt Switch e segura Fogo e Água que ameaçam o Houndoom.

*Plano (Doubles):* Wo-Chien no campo desde o começo, Weezing com Levitate e Will-O-Wisp no atacante físico que sobrou; Mega Houndoom de Heat Wave nos dois; Mewtwo com Psystrike e Recover; Rotom-Wash com Levitate e Protect ao lado do Weezing deixa o jogador sem alvo para Earthquake; Wo-Chien e Weezing se cobrem com Protect e Taunt.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Mewtwo | Life Orb | Unnerve | Timid | Psystrike, Aura Sphere, Ice Beam, Recover |
| Wo-Chien | Leftovers | Tablets of Ruin | Careful | Ruination, Giga Drain, Leech Seed, Protect |
| Houndoom | Darktite | Flash Fire | Timid | Heat Wave, Dark Pulse, Nasty Plot, Sludge Bomb |
| Weezing | Black Sludge | Levitate | Bold | Will-O-Wisp, Toxic Spikes, Sludge Bomb, Taunt |
| Slowking-Galar | Colbur Berry | Regenerator | Calm | Sludge Bomb, Psyshock, Slack Off, Chilly Reception |
| Rotom-Wash | Sitrus Berry | Levitate | Modest | Hydro Pump, Thunderbolt, Volt Switch, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_ARCHER ===
Name: Archer
Class: RocketA
Pic: Archer
Gender: Male
Music: Rocket
Double Battle: Yes
AI: Smart Trainer

Mewtwo @ Life Orb
Timid Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psystrike
- Aura Sphere
- Ice Beam
- Recover

Wo-Chien @ Leftovers
Careful Nature
Level: 100
Ability: Tablets of Ruin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Ruination
- Giga Drain
- Leech Seed
- Protect

Houndoom @ Darktite
Timid Nature
Level: 100
Ability: Flash Fire
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Dark Pulse
- Nasty Plot
- Sludge Bomb

Weezing @ Black Sludge
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Will-O-Wisp
- Toxic Spikes
- Sludge Bomb
- Taunt

Slowking-Galar @ Colbur Berry
Calm Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Psyshock
- Slack Off
- Chilly Reception

Rotom-Wash @ Sitrus Berry
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Thunderbolt
- Volt Switch
- Protect
```

</details>


### Lendário associado

#### Marshadow

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Marshadow_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Marshadow**. Archer é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Archer, executivo do Team Rocket que assumiu o comando depois que o Giovanni sumiu, e que tomou a Radio Tower para mandar uma mensagem ao chefe.

**A criatura.** Marshadow vive escondido na sombra dos outros, raramente é visto, e copia os movimentos de quem segue; o golpe dele rouba a força do oponente pela sombra.

**O fragmento.** Uma cidade ao entardecer onde toda sombra cai para o lado errado, na direção dos postes. Num muro há a sombra de um homem de casaco comprido, e ninguém de pé na frente dela.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A city at dusk, empty and quiet.
>
> Every shadow fell the wrong way: toward the lamps, not away from them.
>
> On one wall was the shadow of a man in a long coat. Nobody was standing there to cast it.

**Boss**

> Your own shadow stretched, then peeled up off the ground.
>
> It stood, small and gray, and moved the way you were about to move.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-802. Gloomdweller.
>
> A city of misplaced shadows, and a man who has stood in someone else's for three years.
>
> The fragment that followed you home hides behind your heel. It has not chosen whose shadow it wants yet.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>

#### Wo-Chien

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_WoChien_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Wo-Chien**. Archer é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Archer, executivo do Team Rocket, frio e metódico, o homem que mantém a organização de pé à espera do chefe.

**A criatura.** Wo-Chien é um dos quatro Tesouros da Ruína de Paldea. Conta a Pokédex que ele é o rancor de alguém punido por escrever os crimes de um rei em tábuas de madeira, que se cobriu de folhas mortas e virou Pokémon. A presença dele enfraquece o Ataque de todos em volta.

**O fragmento.** Uma floresta onde as folhas já morreram e continuam caindo. Em cada tronco há uma tábua de madeira pregada, escrita de ponta a ponta, e toda a escrita foi riscada por outra mão.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest where the leaves had all died and kept falling anyway.
>
> Wooden tablets hung from every trunk. Someone had written on all of them. Someone else had scratched it all out.

**Boss**

> The dead leaves shifted and rose.
>
> Under them was a tablet, and under the tablet was something that remembered every word scratched off it.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-1001. Tablets.
>
> A forest of erased writing, and an executive who keeps a record of everything in his own hand.
>
> What you carried out is a handful of leaves around a small piece of wood. It is blank. What gets written on it now is up to you.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
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
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Archer_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Archer cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Three years ago, Team Rocket disbanded. I have been waiting ever since.
>
> I once broadcast a message across all of Johto, meant for one man. He never answered.
>
> I still keep a radio on. Even here. Now, out of my way.

**Derrota**

> Static. As always.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a espera pelo rádio. A 2 é o executivo frio, que reduz o jogador a um relatório de uma linha. A 3 é a gravata endireitada toda noite para um homem que não entra, e um boato de que, em outro lugar, ele voltou (R21).

**Variação 2 — o relatório**

**Antes da luta**

> You're a child. I have reports on children like you. They are all very short.
>
> They begin with ‘an unknown Trainer interfered’ and end with ‘the operation failed.’
>
> Let us see how short yours will be.

**Derrota**

> …Another short report. Unknown Trainer interfered. Filed.

**Variação 3 — a gravata**

**Antes da luta**

> Every night, at the same hour, I straighten my tie. In case he walks in.
>
> Three years. The tie has never been crooked, and he has never walked in.
>
> I have heard that somewhere, he did come back. I refuse to be jealous of a rumor. Begin.

**Derrota**

> My tie is still straight. That will have to be enough.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Archer_Intro2:
	.string "You're a child. I have reports on\n"
	.string "children like you. They are all very\l"
	.string "short.\p"
	.string "They begin with ‘an unknown Trainer\n"
	.string "interfered’ and end with ‘the operation\l"
	.string "failed.’\p"
	.string "Let us see how short yours will be.$"

Nexus_Text_Archer_Defeat2:
	.string "…Another short report. Unknown Trainer\n"
	.string "interfered. Filed.$"

Nexus_Text_Archer_Intro3:
	.string "Every night, at the same hour, I\n"
	.string "straighten my tie. In case he walks in.\p"
	.string "Three years. The tie has never been\n"
	.string "crooked, and he has never walked in.\p"
	.string "I have heard that somewhere, he did\n"
	.string "come back. I refuse to be jealous of a\l"
	.string "rumor. Begin.$"

Nexus_Text_Archer_Defeat3:
	.string "My tie is still straight. That will have\n"
	.string "to be enough.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Archer é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela.

#### Marshadow

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Archer_Marshadow_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Archer vê uma criatura que mora na sombra de alguém e copia tudo o que a pessoa faz, e percebe que é o retrato dele: três anos dando ordens do jeito do Giovanni, de mãos para trás e queixo erguido. A sombra aprendeu essa pose com ele. A virada: a criatura escolhe quem seguir. Ele nunca escolheu, só ficou.

**Antes da luta**

> Something lives in the shadows of this place. It borrows a body's outline and copies whatever it does.
>
> I watched it follow me for an hour. It walked like me. It stood like me.
>
> Then it stood like him. Hands behind the back, chin up. It learned that from me.
>
> …Enough. Show me something it can't copy.

**Derrota**

> You fight like yourself. How irritating.

**Depois da luta**

> For three years I've given orders the way he gave them. Held my Pokémon the way he held his. Every habit, copied.
>
> That little shadow does the same, but it picks the one it follows. I never picked. I only stayed.
>
> Go on. Take a piece of it home, if it lets you. Just don't let it learn to stand like me.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a sombra que aprendeu a pose do chefe. A 2 é a sombra do homem de sobretudo no muro (fio do casaco): o Archer achou que era do chefe, e a criatura, dentro dela, fica de pé como um detetive. A 3 é o Spectral Thief visto de fora, e a primeira vez em três anos que a sombra do Archer fica de pé como ele mesmo.

**Variação 2 — a sombra no muro**

**Antes da luta**

> There is a shadow on a wall in this city. A man in a long coat. Nobody stands in front of it.
>
> At first I thought it was his. The boss wore a long coat the night he left, in the rain.
>
> It isn't. His shadow would never wait so patiently. Battle me.

**Derrota**

> Patient. Like that shadow. I dislike the comparison.

**Depois da luta**

> The little one lives in that shadow sometimes. It likes the coat. It stands inside it like a child in a doorway.
>
> Once it stepped out and stood like the coat's owner. Hands in pockets. Head tilted, listening.
>
> Not a boss's stance. A detective's. …Go. I don't want to know whose it is.

**Variação 3 — o que ela rouba**

**Antes da luta**

> Earlier, my Houndoom powered up. The shadow reached across and took it. All of it.
>
> It steals whatever you build. I have spent three years building. Imagine what it could take from me.
>
> …Don't imagine. Fight.

**Derrota**

> You built nothing it could take. Clever. Or lucky.

**Depois da luta**

> It doesn't cast a shadow. It is one. Stand under a lamp beside it and there is only yours.
>
> Tonight I stood under a lamp and watched my own for a long time. It stood like me. Not like him. Like me.
>
> I hadn't seen that in three years. …Go, before I say something sentimental.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Archer_Marshadow_ChampionIntro2:
	.string "There is a shadow on a wall in this city.\n"
	.string "A man in a long coat. Nobody stands in\l"
	.string "front of it.\p"
	.string "At first I thought it was his. The boss\n"
	.string "wore a long coat the night he left, in\l"
	.string "the rain.\p"
	.string "It isn't. His shadow would never wait so\n"
	.string "patiently. Battle me.$"

Nexus_Text_Archer_Marshadow_ChampionDefeat2:
	.string "Patient. Like that shadow. I dislike the\n"
	.string "comparison.$"

Nexus_Text_Archer_Marshadow_ChampionAfter2:
	.string "{SPEAKER NAME_ARCHER}The little one lives in that shadow\n"
	.string "sometimes. It likes the coat. It stands\l"
	.string "inside it like a child in a doorway.\p"
	.string "Once it stepped out and stood like the\n"
	.string "coat's owner. Hands in pockets. Head\l"
	.string "tilted, listening.\p"
	.string "Not a boss's stance. A detective's.\n"
	.string "…Go. I don't want to know whose it is.$"

Nexus_Text_Archer_Marshadow_ChampionIntro3:
	.string "Earlier, my Houndoom powered up. The\n"
	.string "shadow reached across and took it. All\l"
	.string "of it.\p"
	.string "It steals whatever you build. I have\n"
	.string "spent three years building. Imagine\l"
	.string "what it could take from me.\p"
	.string "…Don't imagine. Fight.$"

Nexus_Text_Archer_Marshadow_ChampionDefeat3:
	.string "You built nothing it could take. Clever.\n"
	.string "Or lucky.$"

Nexus_Text_Archer_Marshadow_ChampionAfter3:
	.string "{SPEAKER NAME_ARCHER}It doesn't cast a shadow. It is one.\n"
	.string "Stand under a lamp beside it and there\l"
	.string "is only yours.\p"
	.string "Tonight I stood under a lamp and\n"
	.string "watched my own for a long time. It stood\l"
	.string "like me. Not like him. Like me.\p"
	.string "I hadn't seen that in three years. …Go,\n"
	.string "before I say something sentimental.$"
```

</details>

#### Wo-Chien

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Archer_WoChien_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A criatura nasceu de alguém que escreveu os crimes de um rei e foi punido por isso. O Archer também escreve: toda operação, toda ordem, com a letra dele, para que nada se perca quando o chefe voltar. Ele nunca tinha pensado de que lado dessa história estaria. A virada, no fim: escreveu para o Giovanni ter orgulho, e começa a achar que escreveu uma confissão.

**Antes da luta**

> They say this creature was made from a grudge. Someone wrote down a king's crimes on wooden tablets, and was punished for it.
>
> I keep records too. Every operation. Every order. All in my own hand, so nothing is lost when the boss returns.
>
> I never asked myself which side of that story I'd be on. Let's not start now.

**Derrota**

> Noted. In ink.

**Depois da luta**

> The tablets in this forest were written by someone brave and scratched out by someone powerful.
>
> My ledgers would read the same, if anyone found them. Every order. Every date. My handwriting.
>
> I wrote them so he'd be proud. I'm starting to think they're a confession.
>
> Go. It won't forgive you for anything. It doesn't know how.

<details><summary><code>.inc</code></summary>

```asm
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
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é o livro-caixa que vira confissão. A 2 é humor de organização: o Proton cobra por estaca arrancada (os Tesouros da Ruína eram lacrados por estacas) e o Archer quer as notas fiscais — liga com o caderno do Proton. A 3 é a única linha ainda não riscada numa tábua, e a criatura que a risca por ele.

**Variação 2 — as notas do Proton**

**Antes da luta**

> Four of these creatures were sealed with stakes. Someone has been pulling them out, one by one.
>
> I know who. He sends me an invoice for each. Proton charges by the stake.
>
> …Team Rocket is an organization. Even here. Let's get this over with.

**Derrota**

> This goes in the ledger under ‘losses.’ It is a long column.

**Depois da luta**

> It hides under the leaves because the leaves are all that's left of its forest. It wears them like a uniform.
>
> I understand. I've worn this one for three years with nobody left to wear it for.
>
> Go. Its presence weakens everyone around it. Mine only weakens me.

**Variação 3 — a linha não riscada**

**Antes da luta**

> I found one tablet here that hadn't been scratched out. One line. ‘The servant who keeps the king's books is guiltier than the king.’
>
> An old saying, surely. From someone else's kingdom.
>
> Surely. …Battle me.

**Derrota**

> Guiltier than the king. We'll see who writes the last line.

**Depois da luta**

> The creature came up while I was reading. It didn't attack. It waited for me to finish.
>
> Then it scratched that line out. For me, I think. Or against me. I can't tell which.
>
> Go. If it offers to scratch something out for you, refuse. Some things you should have to read.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Archer_WoChien_ChampionIntro2:
	.string "Four of these creatures were sealed\n"
	.string "with stakes. Someone has been pulling\l"
	.string "them out, one by one.\p"
	.string "I know who. He sends me an invoice for\n"
	.string "each. Proton charges by the stake.\p"
	.string "…Team Rocket is an organization. Even\n"
	.string "here. Let's get this over with.$"

Nexus_Text_Archer_WoChien_ChampionDefeat2:
	.string "This goes in the ledger under ‘losses.’\n"
	.string "It is a long column.$"

Nexus_Text_Archer_WoChien_ChampionAfter2:
	.string "{SPEAKER NAME_ARCHER}It hides under the leaves because the\n"
	.string "leaves are all that's left of its\l"
	.string "forest. It wears them like a uniform.\p"
	.string "I understand. I've worn this one for\n"
	.string "three years with nobody left to wear it\l"
	.string "for.\p"
	.string "Go. Its presence weakens everyone\n"
	.string "around it. Mine only weakens me.$"

Nexus_Text_Archer_WoChien_ChampionIntro3:
	.string "I found one tablet here that hadn't\n"
	.string "been scratched out. One line. ‘The\l"
	.string "servant who keeps the king's books is\l"
	.string "guiltier than the king.’\p"
	.string "An old saying, surely. From someone\n"
	.string "else's kingdom.\p"
	.string "Surely. …Battle me.$"

Nexus_Text_Archer_WoChien_ChampionDefeat3:
	.string "Guiltier than the king. We'll see who\n"
	.string "writes the last line.$"

Nexus_Text_Archer_WoChien_ChampionAfter3:
	.string "{SPEAKER NAME_ARCHER}The creature came up while I was\n"
	.string "reading. It didn't attack. It waited for\l"
	.string "me to finish.\p"
	.string "Then it scratched that line out. For me,\n"
	.string "I think. Or against me. I can't tell\l"
	.string "which.\p"
	.string "Go. If it offers to scratch something\n"
	.string "out for you, refuse. Some things you\l"
	.string "should have to read.$"
```

</details>

Falante novo: `SP_NAME_ARCHER`.
