# Brock

**Região da ficha:** Kanto

Aparece no checklist como:

- **Brock — Pedra** (Kanto · Líderes de Ginásio) — Líder de Pewter, conhecido por sua resistência e pelo Onix.

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
| `OBJ_EVENT_GFX_BROCK` | `graphics/object_events/pics/people/gym_leaders/brock.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BROCK` | `graphics/trainers/front_pics/brock.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BROCK` | 543 | 0x71F | Golem Lv66, Aerodactyl Lv66, Kabutops Lv66, Archeops Lv66, Garganacl Lv66, Kleavor Lv66 | `PewterCity_Gym`, `SaffronCity_FightingDojoVIP`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BROCK` = **987** (flag de batalha `0x8DB`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Brock_Fight`; campeão: `Nexus_EventScript_Brock_Terrakion_ChampionFight` (para Terrakion), `Nexus_EventScript_Brock_IronThorns_ChampionFight` (para Iron Thorns). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Brock.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BROCK`, campeão de Terrakion e Iron Thorns. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zygarde** (forma 50% com Power Construct, que vira Complete com metade do HP): o guardião do ecossistema, que vigia a terra de dentro das cavernas; é a pedra do Brock pensada em escala de mundo. Semi-lendário **Terrakion**, de quem ele é campeão (o Iron Thorns, o outro, fica fora porque só cabe um semi), o protetor que derruba muralhas para salvar os pequenos. Mega **Steelix** (Steeltite): o Onix do Brock, evoluído. Mais Tyranitar, Garganacl e Aerodactyl: o Aerodactyl é o fóssil do Old Amber do museu de Pewter, e o Garganacl vem do time da campanha. Tudo Pedra, Aço e Terra, tudo defesa "dura como pedra".

*Plano (Singles):* areia. O Tyranitar põe Sand Stream (SpD +50% nos Pedra), a Mega Steelix ganha Sand Force; o Aerodactyl (Focus Sash) e a Steelix põem Stealth Rock; o Garganacl segura com Salt Cure + Recover; o Zygarde sobe Dragon Dance atrás de Protect e bate com Thousand Arrows, que acerta até quem voa.

*Plano (Doubles):* o Aerodactyl põe Tailwind e dá Taunt; Rock Slide vem de três lados (Aerodactyl, Terrakion de Choice Band, Tyranitar, Steelix) e flincha com o vento a favor; o Thousand Arrows do Zygarde acerta os dois oponentes e **não** o parceiro, então substitui o Earthquake; o Garganacl tem Wide Guard contra golpes em área e o Terrakion tem Quick Guard contra Fake Out e prioridade.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zygarde-50-Power-Construct | Leftovers | Power Construct | Adamant | Thousand Arrows, Dragon Dance, Stone Edge, Protect |
| Terrakion | Choice Band | Justified | Jolly | Rock Slide, Close Combat, Stone Edge, Quick Guard |
| Steelix | Steeltite | Sturdy | Impish | Heavy Slam, Stealth Rock, Rock Slide, Protect |
| Tyranitar | Chople Berry | Sand Stream | Adamant | Rock Slide, Crunch, Low Kick, Dragon Dance |
| Garganacl | Leftovers | Purifying Salt | Careful | Salt Cure, Recover, Protect, Wide Guard |
| Aerodactyl | Focus Sash | Unnerve | Jolly | Tailwind, Rock Slide, Stealth Rock, Taunt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BROCK ===
Name: Brock
Class: Leader
Pic: Leader Brock
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Zygarde-50-Power-Construct @ Leftovers
Adamant Nature
Level: 100
Ability: Power Construct
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thousand Arrows
- Dragon Dance
- Stone Edge
- Protect

Terrakion @ Choice Band
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Close Combat
- Stone Edge
- Quick Guard

Steelix @ Steeltite
Impish Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Stealth Rock
- Rock Slide
- Protect

Tyranitar @ Chople Berry
Adamant Nature
Level: 100
Ability: Sand Stream
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Crunch
- Low Kick
- Dragon Dance

Garganacl @ Leftovers
Careful Nature
Level: 100
Ability: Purifying Salt
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Salt Cure
- Recover
- Protect
- Wide Guard

Aerodactyl @ Focus Sash
Jolly Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Rock Slide
- Stealth Rock
- Taunt
```

</details>

### Lendário associado

#### Terrakion

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Terrakion_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Terrakion**. Brock é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brock, Líder de Pewter, especialista em Pedra, "rock-hard willpower". Pewter tem o Museu de Ciência com os fósseis de Kanto. O Onix é o parceiro de sempre.

**A criatura.** Terrakion, um dos Swords of Justice, é dito ter protegido os Pokémon cujas casas foram destruídas numa guerra entre pessoas. Sua carga derruba até muralhas de castelo. Em Black/White vive na Victory Road.

**O fragmento.** A muralha de um castelo, com um buraco aberto de uma vez, mais alto que uma casa. Do outro lado, Pokémon dormindo no entulho como se fosse o lugar mais seguro que conhecem. A muralha não foi quebrada para entrar; foi quebrada para tirá-los de lá.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A castle, or the wall of one. A hole had been punched straight through it, taller than a house.
>
> On the far side, Pokémon were asleep in the rubble, as if it were the safest place they knew.

**Boss**

> The ground shook. Something heavy and grey, with horns like a battering ram, stepped into the gap in the wall.
>
> The Pokémon behind it did not wake up. They did not need to.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-639. Cavern.
>
> A broken wall with the weak asleep behind it, and a Gym Leader who has spent his life being the wall.
>
> What came back with you is a calf. It planted its feet in front of me the moment I came near. It is guarding already.
>
> He told me walls are not made to be hit. They are made to be leaned on.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Terrakion_Arrival:
	.string "A castle, or the wall of one. A hole had\n"
	.string "been punched straight through it,\l"
	.string "taller than a house.\p"
	.string "On the far side, Pokémon were asleep in\n"
	.string "the rubble, as if it were the safest\l"
	.string "place they knew.$"

Nexus_Text_Terrakion_Boss:
	.string "The ground shook. Something heavy and\n"
	.string "grey, with horns like a battering ram,\l"
	.string "stepped into the gap in the wall.\p"
	.string "The Pokémon behind it did not wake up.\n"
	.string "They did not need to.$"

Nexus_Text_Terrakion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-639. Cavern.\p"
	.string "A broken wall with the weak asleep\n"
	.string "behind it, and a Gym Leader who has\l"
	.string "spent his life being the wall.\p"
	.string "What came back with you is a calf. It\n"
	.string "planted its feet in front of me the\l"
	.string "moment I came near. It is guarding\l"
	.string "already.\p"
	.string "He told me walls are not made to be hit.\n"
	.string "They are made to be leaned on.$"
```

</details>

#### Iron Thorns

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronThorns_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Thorns**. Brock é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** O mesmo Brock, agora como o menino de Pewter que cresceu ao lado do museu de fósseis: para ele, pedra conta o que viveu.

**A criatura.** Iron Thorns é um Pokémon Paradoxo do futuro (Scarlet/Violet), Pedra/Elétrico, que lembra um Tyranitar feito de máquina. O diário de expedição que o descreve é o único registro dele; veio pela máquina do tempo da Area Zero.

**O fragmento.** Um sítio de escavação montado com cuidado: cordas, grade, bandeirinhas na terra. Os ossos que aparecem são de metal, e alguns ainda estão quentes. Um fóssil que ainda não morreu.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A dig site. Ropes, grids, little flags in the dirt, everything a careful person would set up.
>
> The bones in the ground were made of metal. Some of them were still warm.

**Boss**

> A spine of rock plates slid up out of the dig, humming.
>
> It stood, and a crackle ran along its back, as if someone far in the future had just switched it on.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-995. Paradox.
>
> A fossil that has not died yet, and a man who has spent his life reading the ones that have.
>
> What came back with you is small, and cool to the touch, and it hums when it sleeps. Nothing has been built on it yet.
>
> He took notes the whole time. I asked to see them. Every page ends with the same two words: 'Not yet.'

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronThorns_Arrival:
	.string "A dig site. Ropes, grids, little flags in\n"
	.string "the dirt, everything a careful person\l"
	.string "would set up.\p"
	.string "The bones in the ground were made of\n"
	.string "metal. Some of them were still warm.$"

Nexus_Text_IronThorns_Boss:
	.string "A spine of rock plates slid up out of\n"
	.string "the dig, humming.\p"
	.string "It stood, and a crackle ran along its\n"
	.string "back, as if someone far in the future\l"
	.string "had just switched it on.$"

Nexus_Text_IronThorns_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-995. Paradox.\p"
	.string "A fossil that has not died yet, and a\n"
	.string "man who has spent his life reading the\l"
	.string "ones that have.\p"
	.string "What came back with you is small, and\n"
	.string "cool to the touch, and it hums when it\l"
	.string "sleeps. Nothing has been built on it\l"
	.string "yet.\p"
	.string "He took notes the whole time. I asked\n"
	.string "to see them. Every page ends with the\l"
	.string "same two words: 'Not yet.'$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brock_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brock cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I'm Brock! Wherever I end up, one thing never changes: rock-hard determination.
>
> Back in Pewter, I battle every rookie who walks in. My Onix, well, it's a Steelix now, has taken more first hits than any Pokémon alive.
>
> So come on. Hit me with your best one!

**Derrota**

> Solid. Just like a good rock should be.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brock_Intro:
	.string "I'm Brock! Wherever I end up, one thing\n"
	.string "never changes: rock-hard\l"
	.string "determination.\p"
	.string "Back in Pewter, I battle every rookie\n"
	.string "who walks in. My Onix, well, it's a\l"
	.string "Steelix now, has taken more first hits\l"
	.string "than any Pokémon alive.\p"
	.string "So come on. Hit me with your best one!$"

Nexus_Text_Brock_Defeat:
	.string "Solid. Just like a good rock should be.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Variação 2: o Brock cozinheiro e irmão mais velho de nove (anime), com humor de R20: a cesta de bolinhos ficou em outro mundo. Variação 3: a dúvida — criador, médico? — e o novato de sorriso largo que o faz ficar no ginásio.

**Variação 2 — antes da luta**

> Hey there! You look like you haven't eaten since you got here. Wherever here is.
>
> I've got nine brothers and sisters back home, so trust me, I can tell.
>
> Battle first, then rice balls. That's the Pewter way!

**Variação 2 — derrota**

> Good battle! Here, take one for the road. …Oh. I left the basket in another world.

**Variação 3 — antes da luta**

> Some days I wonder what I'd be if I weren't a Gym Leader. A breeder, maybe. A doctor, even.
>
> Then a rookie walks in with a nervous Pokémon and a big grin, and I remember why I stay.
>
> You don't look nervous. Let's see that grin!

**Variação 3 — derrota**

> There it is. Now go grin at somebody tougher than me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brock_Intro2:
	.string "Hey there! You look like you haven't\n"
	.string "eaten since you got here. Wherever here\l"
	.string "is.\p"
	.string "I've got nine brothers and sisters\n"
	.string "back home, so trust me, I can tell.\p"
	.string "Battle first, then rice balls. That's\n"
	.string "the Pewter way!$"

Nexus_Text_Brock_Defeat2:
	.string "Good battle! Here, take one for the\n"
	.string "road. …Oh. I left the basket in another\l"
	.string "world.$"

Nexus_Text_Brock_Intro3:
	.string "Some days I wonder what I'd be if I\n"
	.string "weren't a Gym Leader. A breeder, maybe.\l"
	.string "A doctor, even.\p"
	.string "Then a rookie walks in with a nervous\n"
	.string "Pokémon and a big grin, and I remember\l"
	.string "why I stay.\p"
	.string "You don't look nervous. Let's see that\n"
	.string "grin!$"

Nexus_Text_Brock_Defeat3:
	.string "There it is. Now go grin at somebody\n"
	.string "tougher than me.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brock é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Terrakion

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brock_Terrakion_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Brock é o muro: o líder que aguenta o primeiro golpe de todo novato, o mais velho de casa atrás de quem os pequenos se escondem. Ele reconhece na criatura alguém do mesmo tipo, mas a virada é que ela não é muro: ela correu contra a muralha, porque às vezes ser sólido é ser quem arrebenta a parede. E ela só sai da frente dos que dormem quando você prova que não é ameaça.

**Antes da luta**

> Did you see the wall out there? Something charged straight through it, and the Pokémon behind it fell asleep in the rubble.
>
> It didn't break that wall to get in. It broke it to get them out.
>
> I know that kind. Back home, I'm the one the little ones hide behind.
>
> Let's see if you can get past me!

**Derrota**

> You got past me. …Good. Just don't wake them.

**Depois da luta**

> People think being solid means never moving. That's wrong.
>
> Sometimes the solid one is the one who runs at the wall.
>
> It'll stand in front of those sleeping Pokémon until you prove you're not a threat.
>
> So don't be one. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brock_Terrakion_ChampionIntro:
	.string "Did you see the wall out there?\n"
	.string "Something charged straight through it,\l"
	.string "and the Pokémon behind it fell asleep\l"
	.string "in the rubble.\p"
	.string "It didn't break that wall to get in. It\n"
	.string "broke it to get them out.\p"
	.string "I know that kind. Back home, I'm the\n"
	.string "one the little ones hide behind.\p"
	.string "Let's see if you can get past me!$"

Nexus_Text_Brock_Terrakion_ChampionDefeat:
	.string "You got past me. …Good. Just don't\n"
	.string "wake them.$"

Nexus_Text_Brock_Terrakion_ChampionAfter:
	.string "{SPEAKER NAME_BROCK}People think being solid means never\n"
	.string "moving. That's wrong.\p"
	.string "Sometimes the solid one is the one who\n"
	.string "runs at the wall.\p"
	.string "It'll stand in front of those sleeping\n"
	.string "Pokémon until you prove you're not a\l"
	.string "threat.\p"
	.string "So don't be one. Go on.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Variação 2: a lembrança do pai que saiu para ser treinador e dos muros de pedra no quintal que os irmãos pulavam; a lição é que os pequenos não precisavam de muro, precisavam de alguém ao lado. Variação 3: os Swords of Justice como um ginásio com menos papelada; a criatura é a forte do grupo, a que bate no muro para os outros não precisarem.

**Variação 2 — antes da luta**

> My dad left Pewter to be a trainer when I was a kid. I built walls out of rocks in the yard, so the little ones felt safe.
>
> They weren't very good walls. My brothers climbed over them every day.
>
> The one out there breaks real walls. Let's see if I've gotten any better!

**Variação 2 — derrota**

> Climbed right over me. …Just like old times.

**Variação 2 — depois da luta**

> Here's something I figured out late. The little ones didn't need walls. They needed somebody standing next to them.
>
> That big guy out there gets it. It knocked down a castle, then lay down in the rubble so they could sleep.
>
> Be gentle out there. Go on.

**Variação 3 — antes da luta**

> I hear it has friends. One green and quick, one blue and in charge. They all look out for the little guys.
>
> Sounds like a Gym to me. We just have more paperwork.
>
> Alright! Let's see how you handle a real defense!

**Variação 3 — derrota**

> Ha! Good. You'd make a fine Sword yourself.

**Variação 3 — depois da luta**

> The one out there is the strong one of its group. It hits the walls so the others don't have to.
>
> That's a lonely job. Trust me, I know.
>
> If it charges you, don't run. Stand still and let it see you. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brock_Terrakion_ChampionIntro2:
	.string "My dad left Pewter to be a trainer when\n"
	.string "I was a kid. I built walls out of rocks in\l"
	.string "the yard, so the little ones felt safe.\p"
	.string "They weren't very good walls. My\n"
	.string "brothers climbed over them every day.\p"
	.string "The one out there breaks real walls.\n"
	.string "Let's see if I've gotten any better!$"

Nexus_Text_Brock_Terrakion_ChampionDefeat2:
	.string "Climbed right over me. …Just like old\n"
	.string "times.$"

Nexus_Text_Brock_Terrakion_ChampionAfter2:
	.string "{SPEAKER NAME_BROCK}Here's something I figured out late.\n"
	.string "The little ones didn't need walls. They\l"
	.string "needed somebody standing next to them.\p"
	.string "That big guy out there gets it. It\n"
	.string "knocked down a castle, then lay down in\l"
	.string "the rubble so they could sleep.\p"
	.string "Be gentle out there. Go on.$"

Nexus_Text_Brock_Terrakion_ChampionIntro3:
	.string "I hear it has friends. One green and\n"
	.string "quick, one blue and in charge. They all\l"
	.string "look out for the little guys.\p"
	.string "Sounds like a Gym to me. We just have\n"
	.string "more paperwork.\p"
	.string "Alright! Let's see how you handle a real\n"
	.string "defense!$"

Nexus_Text_Brock_Terrakion_ChampionDefeat3:
	.string "Ha! Good. You'd make a fine Sword\n"
	.string "yourself.$"

Nexus_Text_Brock_Terrakion_ChampionAfter3:
	.string "{SPEAKER NAME_BROCK}The one out there is the strong one of\n"
	.string "its group. It hits the walls so the\l"
	.string "others don't have to.\p"
	.string "That's a lonely job. Trust me, I know.\p"
	.string "If it charges you, don't run. Stand\n"
	.string "still and let it see you. Go on.$"
```

</details>


#### Iron Thorns

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brock_IronThorns_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Brock lê fósseis desde criança; o trato da pedra é contar o que já viveu. Este está quente, zumbe e vem do futuro: quebra o trato. Ele pede uma luta "que faça sentido" para se acalmar. Depois conta que mediu as placas escondido: o padrão de um velho tirano de armadura, só que construído, não crescido. A virada: ele pensa que um dia alguém vai desenterrar o time dele e perguntar o que eles foram, e torce para acertarem.

**Antes da luta**

> I've been digging up fossils since I was a kid. Pewter has a whole museum of them.
>
> A fossil tells you what used to live. That's the deal. That's what rock is for.
>
> The one out there is warm, and it's humming. It's not from the past at all.
>
> …Let me battle something that makes sense for a minute!

**Derrota**

> Ha! At least you make sense.

**Depois da luta**

> I measured its plates while it wasn't looking. Same pattern as an old armored tyrant.
>
> Just… made. Built, not grown.
>
> Maybe someday somebody digs up my team and wonders what we were.
>
> I hope they get it right. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brock_IronThorns_ChampionIntro:
	.string "I've been digging up fossils since I\n"
	.string "was a kid. Pewter has a whole museum of\l"
	.string "them.\p"
	.string "A fossil tells you what used to live.\n"
	.string "That's the deal. That's what rock is\l"
	.string "for.\p"
	.string "The one out there is warm, and it's\n"
	.string "humming. It's not from the past at all.\p"
	.string "…Let me battle something that makes\n"
	.string "sense for a minute!$"

Nexus_Text_Brock_IronThorns_ChampionDefeat:
	.string "Ha! At least you make sense.$"

Nexus_Text_Brock_IronThorns_ChampionAfter:
	.string "{SPEAKER NAME_BROCK}I measured its plates while it wasn't\n"
	.string "looking. Same pattern as an old armored\l"
	.string "tyrant.\p"
	.string "Just… made. Built, not grown.\p"
	.string "Maybe someday somebody digs up my\n"
	.string "team and wonders what we were.\p"
	.string "I hope they get it right. Go on.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Variação 2: humor de museu — todo fóssil tem etiqueta, e não dá para etiquetar algo que ainda está ligando; depois, pedra é tempo empilhado, e esse aí não tem camada nenhuma: tudo ainda está pela frente. Variação 3: as duas alas do Museu de Pewter (fósseis e o ônibus espacial), ele corria para os fósseis e a irmã para o foguete.

**Variação 2 — antes da luta**

> Every fossil I've ever dug up got a little label. Old Amber. Dome. Helix. 'Probably ancient.'
>
> I tried to label the one out there. It kept switching on while I wrote.
>
> You can't label something that's still booting up! Let's battle!

**Variação 2 — derrota**

> Ha! Label that one 'Beaten, recently.'

**Variação 2 — depois da luta**

> Rock is just time, stacked. You read the layers and you know what happened.
>
> That one out there has no layers. Nothing has happened to it yet. Everything is still ahead of it.
>
> Kind of jealous, honestly. Go on.

**Variação 3 — antes da luta**

> Pewter Museum has two wings. One for fossils, one for a space shuttle. Old things and new things, under one roof.
>
> As a kid I always ran to the fossils. My little sister always ran to the rocket.
>
> That one out there would've made us both happy. Let's battle!

**Variação 3 — derrota**

> You'd have liked the rocket wing too. I can tell.

**Variação 3 — depois da luta**

> My sister used to say the future is just a fossil nobody has dug up yet.
>
> I told her that didn't make sense. Now I'm standing next to one, and it's humming.
>
> I owe her an apology. Go on, before it finishes booting up.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brock_IronThorns_ChampionIntro2:
	.string "Every fossil I've ever dug up got a\n"
	.string "little label. Old Amber. Dome. Helix.\l"
	.string "'Probably ancient.'\p"
	.string "I tried to label the one out there. It\n"
	.string "kept switching on while I wrote.\p"
	.string "You can't label something that's still\n"
	.string "booting up! Let's battle!$"

Nexus_Text_Brock_IronThorns_ChampionDefeat2:
	.string "Ha! Label that one 'Beaten, recently.'$"

Nexus_Text_Brock_IronThorns_ChampionAfter2:
	.string "{SPEAKER NAME_BROCK}Rock is just time, stacked. You read the\n"
	.string "layers and you know what happened.\p"
	.string "That one out there has no layers.\n"
	.string "Nothing has happened to it yet.\l"
	.string "Everything is still ahead of it.\p"
	.string "Kind of jealous, honestly. Go on.$"

Nexus_Text_Brock_IronThorns_ChampionIntro3:
	.string "Pewter Museum has two wings. One for\n"
	.string "fossils, one for a space shuttle. Old\l"
	.string "things and new things, under one roof.\p"
	.string "As a kid I always ran to the fossils. My\n"
	.string "little sister always ran to the rocket.\p"
	.string "That one out there would've made us\n"
	.string "both happy. Let's battle!$"

Nexus_Text_Brock_IronThorns_ChampionDefeat3:
	.string "You'd have liked the rocket wing too. I\n"
	.string "can tell.$"

Nexus_Text_Brock_IronThorns_ChampionAfter3:
	.string "{SPEAKER NAME_BROCK}My sister used to say the future is\n"
	.string "just a fossil nobody has dug up yet.\p"
	.string "I told her that didn't make sense. Now\n"
	.string "I'm standing next to one, and it's\l"
	.string "humming.\p"
	.string "I owe her an apology. Go on, before it\n"
	.string "finishes booting up.$"
```

</details>


Falante novo: `SP_NAME_BROCK` (ainda não existe em `include/constants/speaker_names.h`).
