# Proton

**Região da ficha:** Kanto

Aparece no checklist como:

- **Proton** (Kanto · Team Rocket) — executivo conhecido por sua crueldade e pelas operações no Slowpoke Well.
- **Proton** (Johto · Team Rocket) — lidera ataques contra Slowpoke e outras ações violentas.

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
| `OBJ_EVENT_GFX_PROTON` | `graphics/object_events/pics/people/rockets/proton.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PROTON` | `graphics/trainers/front_pics/proton.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_PROTON` | `graphics/field_mugshots/proton.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PROTON_2` | 279 | 0x617 | Crobat Lv52, Farigiraf Lv52, Cacturne Lv52, Porygon Z Lv53, Nidoking Lv52, Scrafty Lv53 | `GoldenrodCity_RadioTower_4F`, `src/battle_setup.c` |
| `TRAINER_PROTON_1` | 862 | 0x85E | Nosepass Lv17, Houndour Lv17, Porygon Lv18 | `SlowpokeWell_B1F`, `src/battle_setup.c`, `src/match_call.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_PROTON` = **998** (flag de batalha `0x8E6`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Proton_Fight`; campeão: `Nexus_EventScript_Proton_RoaringMoon_ChampionFight` (para Roaring Moon), `Nexus_EventScript_Proton_TingLu_ChampionFight` (para Ting-Lu). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Proton.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_PROTON`, campeão de Ting-Lu e Roaring Moon. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zygarde**, na forma Complete e com Dragotite (lendário + Mega, as duas vagas): a criatura feita de pedaços, que se espalha em células e se junta de novo. Para o homem que corta caudas de Slowpoke, é a ironia do time. Semi-lendário **Ting-Lu**, de que ele é campeão (a outra, Roaring Moon, fica só como campeão). Mais **Crobat**, **Scrafty**, **Nidoking** e **Cacturne**, todos do time dele neste hack. A sinergia é o Vessel of Ruin: ele corta o Ataque Especial de **todo mundo** em campo, menos do Ting-Lu, e o time do Proton é todo físico.

*Plano (Singles):* Ting-Lu põe Stealth Rock e força troca com Whirlwind; Crobat tira metade do HP com Super Fang e Taunt; Scrafty entra com Intimidate e sobe com Bulk Up; Zygarde sobe com Dragon Dance e o Thousand Arrows acerta até Voador e Levitate; o Power Construct o segura quando cai para metade do HP.

*Plano (Doubles):* Scrafty abre com Fake Out e Intimidate, Crobat com Tailwind; o Thousand Arrows acerta os dois oponentes e nunca o parceiro; o Vessel of Ruin corta o Heat Wave e o Hyper Voice do jogador; Cacturne com Spiky Shield e Sucker Punch castiga quem vem para cima.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zygarde-Complete | Dragotite | Power Construct | Adamant | Thousand Arrows, Outrage, Dragon Dance, Stone Edge |
| Ting-Lu | Leftovers | Vessel of Ruin | Impish | Stealth Rock, Ruination, Stomping Tantrum, Whirlwind |
| Crobat | Sitrus Berry | Inner Focus | Jolly | Brave Bird, Super Fang, Tailwind, Taunt |
| Scrafty | Sitrus Berry | Intimidate | Careful | Fake Out, Knock Off, Drain Punch, Bulk Up |
| Nidoking | Life Orb | Sheer Force | Jolly | Poison Jab, Megahorn, Stone Edge, Sucker Punch |
| Cacturne | Focus Sash | Water Absorb | Adamant | Spiky Shield, Seed Bomb, Sucker Punch, Swords Dance |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_PROTON ===
Name: Proton
Class: RocketA
Pic: Proton
Gender: Male
Music: Rocket
Double Battle: Yes
AI: Smart Trainer

Zygarde-Complete @ Dragotite
Adamant Nature
Level: 100
Ability: Power Construct
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thousand Arrows
- Outrage
- Dragon Dance
- Stone Edge

Ting-Lu @ Leftovers
Impish Nature
Level: 100
Ability: Vessel of Ruin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Ruination
- Stomping Tantrum
- Whirlwind

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Super Fang
- Tailwind
- Taunt

Scrafty @ Sitrus Berry
Careful Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Knock Off
- Drain Punch
- Bulk Up

Nidoking @ Life Orb
Jolly Nature
Level: 100
Ability: Sheer Force
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poison Jab
- Megahorn
- Stone Edge
- Sucker Punch

Cacturne @ Focus Sash
Adamant Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spiky Shield
- Seed Bomb
- Sucker Punch
- Swords Dance
```

</details>


### Lendário associado

#### Ting-Lu

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_TingLu_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Ting-Lu**. Proton é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Proton, executivo do Team Rocket que se gaba de ser o mais cruel da organização; foi ele quem comandou o corte das caudas de Slowpoke no Slowpoke Well.

**A criatura.** Ting-Lu é um dos quatro Tesouros da Ruína de Paldea: um vaso cerimonial tomado por um rancor antigo, lacrado por estacas num santuário. A presença dele enfraquece o Ataque Especial de todos em volta.

**O fragmento.** Um vale seco cheio de estacas de madeira arrancadas do chão, uma a uma. No meio, um vaso cerimonial enorme, rachado, cheio até a borda de terra preta. O ar pesa, como se cada pensamento tivesse de levantar uma pedra.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A dry valley full of wooden stakes, pulled out of the ground one by one.
>
> In the middle sat a huge ceremonial bowl, cracked, and filled to the brim with black earth.

**Boss**

> The black earth in the bowl began to breathe.
>
> Two great antlers pushed up through it, and the air went heavy, as if every thought had to lift a stone.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-1003. Vessel.
>
> A valley of pulled stakes, and a man who likes being feared more than he likes anything.
>
> What you brought back fits in a cupped hand and is heavy for its size. It is afraid of nothing yet. Let us keep it that way.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_TingLu_Arrival:
	.string "A dry valley full of wooden stakes,\n"
	.string "pulled out of the ground one by one.\p"
	.string "In the middle sat a huge ceremonial\n"
	.string "bowl, cracked, and filled to the brim\l"
	.string "with black earth.$"

Nexus_Text_TingLu_Boss:
	.string "The black earth in the bowl began to\n"
	.string "breathe.\p"
	.string "Two great antlers pushed up through it,\n"
	.string "and the air went heavy, as if every\l"
	.string "thought had to lift a stone.$"

Nexus_Text_TingLu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1003. Vessel.\p"
	.string "A valley of pulled stakes, and a man who\n"
	.string "likes being feared more than he likes\l"
	.string "anything.\p"
	.string "What you brought back fits in a cupped\n"
	.string "hand and is heavy for its size. It is\l"
	.string "afraid of nothing yet. Let us keep it\l"
	.string "that way.$"
```

</details>

#### Roaring Moon

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_RoaringMoon_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Roaring Moon**. Proton é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Proton, executivo do Team Rocket, o que quer ser a coisa mais assustadora de qualquer sala.

**A criatura.** Roaring Moon é um Pokémon Paradoxo de Dragão/Noturno, da Area Zero de Paldea, parecido com uma versão antiga de Salamence. Talvez seja a criatura descrita num diário de expedição antigo, cheio de mistérios, em que pouca gente acreditou.

**O fragmento.** Um cânion de antes das pessoas, sob uma lua vermelha grande demais, perto a ponto de se ver as crateras. Marcas fundas de garra descem pelas duas paredes até o fundo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A canyon from a time before people.
>
> The moon hung huge and red over the rim, close enough to count its craters. Deep claw marks ran down both walls, all the way to the bottom.

**Boss**

> Wings like torn banners blotted out the red moon.
>
> It landed without a sound, and the claw marks on the walls suddenly made sense.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-1005. Red Moon.
>
> A canyon under a moon too large, and a man who wants to be the scariest thing in the room.
>
> The fragment that came back with you is all claws and no wings. It has not learned to frighten anyone. Nobody needs to teach it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_RoaringMoon_Arrival:
	.string "A canyon from a time before people.\p"
	.string "The moon hung huge and red over the\n"
	.string "rim, close enough to count its craters.\l"
	.string "Deep claw marks ran down both walls, all\l"
	.string "the way to the bottom.$"

Nexus_Text_RoaringMoon_Boss:
	.string "Wings like torn banners blotted out the\n"
	.string "red moon.\p"
	.string "It landed without a sound, and the claw\n"
	.string "marks on the walls suddenly made sense.$"

Nexus_Text_RoaringMoon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1005. Red Moon.\p"
	.string "A canyon under a moon too large, and a\n"
	.string "man who wants to be the scariest thing\l"
	.string "in the room.\p"
	.string "The fragment that came back with you\n"
	.string "is all claws and no wings. It has not\l"
	.string "learned to frighten anyone. Nobody\l"
	.string "needs to teach it.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Proton_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Proton cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> They call me the scariest, cruelest guy in Team Rocket. I earned that.
>
> Slowpoke tails sell for a fortune, and they grow back. You know how long a Slowpoke takes to notice one's gone?
>
> Neither do I. I never stay to watch. Let's go!

**Derrota**

> Tch. You're no fun. You didn't even flinch.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Proton_Intro:
	.string "They call me the scariest, cruelest guy\n"
	.string "in Team Rocket. I earned that.\p"
	.string "Slowpoke tails sell for a fortune, and\n"
	.string "they grow back. You know how long a\l"
	.string "Slowpoke takes to notice one's gone?\p"
	.string "Neither do I. I never stay to watch.\n"
	.string "Let's go!$"

Nexus_Text_Proton_Defeat:
	.string "Tch. You're no fun. You didn't even\n"
	.string "flinch.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é o homem que nunca fica para ver. A 2 é a técnica do medo (sorrir, não fazer careta), com Azalea como vítima. A 3 é a dúvida: um Slowpoke que ele teve antes do uniforme, e em que pensa mais do que gostaria.

**Variação 2 — o sorriso**

**Antes da luta**

> Want to know the trick to being scary? Smile. People expect a scowl. A smile, they can't read.
>
> I smiled at a whole town once. Azalea. They locked their doors for a week.
>
> So… smile! Let's go!

**Derrota**

> You smiled back. That's cheating.

**Variação 3 — o Slowpoke dele**

**Antes da luta**

> I had a Slowpoke once. Before the uniform. Kept it by a well.
>
> It never did anything. Sat there. Yawned. I thought it was the stupidest animal alive.
>
> Now I think about it more than I'd like. Why am I talking? Let's go!

**Derrota**

> Beat me and made me talk about a Slowpoke. What a day.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Proton_Intro2:
	.string "Want to know the trick to being scary?\n"
	.string "Smile. People expect a scowl. A smile,\l"
	.string "they can't read.\p"
	.string "I smiled at a whole town once. Azalea.\n"
	.string "They locked their doors for a week.\p"
	.string "So… smile! Let's go!$"

Nexus_Text_Proton_Defeat2:
	.string "You smiled back. That's cheating.$"

Nexus_Text_Proton_Intro3:
	.string "I had a Slowpoke once. Before the\n"
	.string "uniform. Kept it by a well.\p"
	.string "It never did anything. Sat there.\n"
	.string "Yawned. I thought it was the stupidest\l"
	.string "animal alive.\p"
	.string "Now I think about it more than I'd like.\n"
	.string "Why am I talking? Let's go!$"

Nexus_Text_Proton_Defeat3:
	.string "Beat me and made me talk about a\n"
	.string "Slowpoke. What a day.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Proton é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela.

#### Ting-Lu

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Proton_TingLu_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Proton fez carreira assustando os outros, e ao lado da criatura ele também sente medo. Dizem que ela é feita de medo, o de outras pessoas, derramado num vaso e deixado ali. A virada: se o medo dela é emprestado, o dele também é. Ninguém tinha medo do Proton; tinham medo do R no peito dele. E ele pede para o jogador não contar.

**Antes da luta**

> You feel that? The air here's heavy. Like your arms forgot how strong they are.
>
> That's the big one in the bowl. Folks say it's made of fear. Somebody else's, poured in and left to set.
>
> I've made a career out of scaring people. Standing next to that thing, I'm scared too. Let's fix that!

**Derrota**

> Heh. So I'm not even the scariest thing in this valley.

**Depois da luta**

> Here's what I figured out. That thing isn't scary on its own. It's full of other people's fear. It's borrowed.
>
> Mine's borrowed too. Nobody was ever scared of Proton. They were scared of the R on my chest.
>
> Take that off and… well. Don't tell anyone I said that. Go on, get lost.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Proton_TingLu_ChampionIntro:
	.string "You feel that? The air here's heavy.\n"
	.string "Like your arms forgot how strong they\l"
	.string "are.\p"
	.string "That's the big one in the bowl. Folks\n"
	.string "say it's made of fear. Somebody else's,\l"
	.string "poured in and left to set.\p"
	.string "I've made a career out of scaring\n"
	.string "people. Standing next to that thing,\l"
	.string "I'm scared too. Let's fix that!$"

Nexus_Text_Proton_TingLu_ChampionDefeat:
	.string "Heh. So I'm not even the scariest thing\n"
	.string "in this valley.$"

Nexus_Text_Proton_TingLu_ChampionAfter:
	.string "{SPEAKER NAME_PROTON}Here's what I figured out. That thing\n"
	.string "isn't scary on its own. It's full of\l"
	.string "other people's fear. It's borrowed.\p"
	.string "Mine's borrowed too. Nobody was ever\n"
	.string "scared of Proton. They were scared of\l"
	.string "the R on my chest.\p"
	.string "Take that off and… well. Don't tell\n"
	.string "anyone I said that. Go on, get lost.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é o medo emprestado. A 2 é a confissão de que foi ele quem arrancou as estacas do santuário (e o Archer cobra as notas: liga com o caderno do Archer), e o pior insulto da carreira: a criatura acordou e não fez nada com ele. A 3 é humor: ele tentou assustar o vaso e as pernas dele sentaram sozinhas.

**Variação 2 — as estacas**

**Antes da luta**

> Want a secret? I pulled the stakes around that bowl. Every one. A buyer said they were worth a fortune.
>
> Archer keeps asking for the invoices. I keep saying ‘later.’
>
> Nobody told me what the stakes were holding down. Guess I found out. Let's go!

**Derrota**

> Well. That's one more thing I let loose today.

**Depois da luta**

> Every stake I pulled, the air got heavier. By the last one I could barely lift my arm to toss it in the sack.
>
> The bowl woke up, looked at me, and did nothing. Like I wasn't worth the effort.
>
> Worst insult of my career. …Go on. See if it thinks you're worth it.

**Variação 3 — as pernas**

**Antes da luta**

> I tried to scare it. Walked right up to the bowl. The voice, the grin, the whole act.
>
> It just… breathed. And I sat down. My legs decided that on their own.
>
> Nobody saw that. Nobody! Let's go!

**Derrota**

> Sitting down again. Different reason.

**Depois da luta**

> Here's the thing about fear. It's heavy. Pour it into something and it doesn't go away. It just sits.
>
> That bowl's been full for a thousand years. Nobody ever emptied it. They just kept making more.
>
> …I made a lot. Go on. Tell it I'm sorry. No, don't. Just go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Proton_TingLu_ChampionIntro2:
	.string "Want a secret? I pulled the stakes\n"
	.string "around that bowl. Every one. A buyer\l"
	.string "said they were worth a fortune.\p"
	.string "Archer keeps asking for the invoices. I\n"
	.string "keep saying ‘later.’\p"
	.string "Nobody told me what the stakes were\n"
	.string "holding down. Guess I found out. Let's\l"
	.string "go!$"

Nexus_Text_Proton_TingLu_ChampionDefeat2:
	.string "Well. That's one more thing I let loose\n"
	.string "today.$"

Nexus_Text_Proton_TingLu_ChampionAfter2:
	.string "{SPEAKER NAME_PROTON}Every stake I pulled, the air got\n"
	.string "heavier. By the last one I could barely\l"
	.string "lift my arm to toss it in the sack.\p"
	.string "The bowl woke up, looked at me, and did\n"
	.string "nothing. Like I wasn't worth the\l"
	.string "effort.\p"
	.string "Worst insult of my career. …Go on. See if\n"
	.string "it thinks you're worth it.$"

Nexus_Text_Proton_TingLu_ChampionIntro3:
	.string "I tried to scare it. Walked right up to\n"
	.string "the bowl. The voice, the grin, the whole\l"
	.string "act.\p"
	.string "It just… breathed. And I sat down. My\n"
	.string "legs decided that on their own.\p"
	.string "Nobody saw that. Nobody! Let's go!$"

Nexus_Text_Proton_TingLu_ChampionDefeat3:
	.string "Sitting down again. Different reason.$"

Nexus_Text_Proton_TingLu_ChampionAfter3:
	.string "{SPEAKER NAME_PROTON}Here's the thing about fear. It's\n"
	.string "heavy. Pour it into something and it\l"
	.string "doesn't go away. It just sits.\p"
	.string "That bowl's been full for a thousand\n"
	.string "years. Nobody ever emptied it. They\l"
	.string "just kept making more.\p"
	.string "…I made a lot. Go on. Tell it I'm sorry.\n"
	.string "No, don't. Just go.$"
```

</details>

#### Roaring Moon

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Proton_RoaringMoon_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A criatura saiu de um diário de expedição em que ninguém acreditou: selvagem demais, má demais. Para o Proton é o sonho: ser a história em que ninguém acredita até ser tarde. Mas ele passou uma hora olhando para ela, e a virada é o que viu: ela não é cruel. É velha e faminta, e ninguém nunca lhe deu nada além de medo. E ele não quer que o jogador olhe para ele daquele jeito.

**Antes da luta**

> Some old expedition journal talks about a monster under a red moon. Nobody believed it. Too wild. Too mean.
>
> And there it is. Claw marks down every wall. Wings like rags.
>
> That's the dream, kid. Be the story nobody believes until it's too late. Let's go!

**Derrota**

> Too wild, too mean… and still not enough.

**Depois da luta**

> Funny thing. I watched it for an hour. It isn't cruel.
>
> It's old and it's hungry, and nobody ever gave it anything but fear.
>
> …Don't look at me like that. Go on. Wake it up. And don't write any of this down. Nobody would believe you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Proton_RoaringMoon_ChampionIntro:
	.string "Some old expedition journal talks\n"
	.string "about a monster under a red moon.\l"
	.string "Nobody believed it. Too wild. Too mean.\p"
	.string "And there it is. Claw marks down every\n"
	.string "wall. Wings like rags.\p"
	.string "That's the dream, kid. Be the story\n"
	.string "nobody believes until it's too late.\l"
	.string "Let's go!$"

Nexus_Text_Proton_RoaringMoon_ChampionDefeat:
	.string "Too wild, too mean… and still not\n"
	.string "enough.$"

Nexus_Text_Proton_RoaringMoon_ChampionAfter:
	.string "{SPEAKER NAME_PROTON}Funny thing. I watched it for an hour.\n"
	.string "It isn't cruel.\p"
	.string "It's old and it's hungry, and nobody\n"
	.string "ever gave it anything but fear.\p"
	.string "…Don't look at me like that. Go on. Wake\n"
	.string "it up. And don't write any of this down.\l"
	.string "Nobody would believe you.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a história em que ninguém acredita. A 2 é o rabo de Slowpoke atirado para o monstro, o primeiro freguês que não pechinchou, e ele deitando para dormir aos pés do Proton (a imagem da página 3 do diário). A 3 é o fim do diário de expedição ("the moon is closer tonight") e as marcas de garra que só descem.

**Variação 2 — o freguês**

**Antes da luta**

> I tossed it a Slowpoke tail. Top quality. Worth more than your bike.
>
> It ate it in one bite, then stared at me like I owed it another.
>
> First customer I ever had who didn't haggle. Let's go!

**Derrota**

> Tch. And I'm out of tails.

**Depois da luta**

> You know what it did after? Lay down. Right at my feet. Put its head on the rocks and went to sleep.
>
> Nobody ever fell asleep next to me before. They're usually running.
>
> …Wake it up gently. I mean it. Go.

**Variação 3 — a última página**

**Antes da luta**

> I found the rest of that expedition journal. The last page just says ‘the moon is closer tonight.’ Then nothing.
>
> Look up. Count the craters. It was right.
>
> Whoever wrote it never came back. Great story. I'm not ending up in it. Let's go!

**Derrota**

> Not ending up in it… yet.

**Depois da luta**

> Every claw mark on these walls goes down. Not one goes up. It never tried to climb out.
>
> Something that strong, and it just stayed in its hole, under its moon.
>
> Kind of like a guy who never quits a job he hates. …Forget it. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Proton_RoaringMoon_ChampionIntro2:
	.string "I tossed it a Slowpoke tail. Top quality.\n"
	.string "Worth more than your bike.\p"
	.string "It ate it in one bite, then stared at me\n"
	.string "like I owed it another.\p"
	.string "First customer I ever had who didn't\n"
	.string "haggle. Let's go!$"

Nexus_Text_Proton_RoaringMoon_ChampionDefeat2:
	.string "Tch. And I'm out of tails.$"

Nexus_Text_Proton_RoaringMoon_ChampionAfter2:
	.string "{SPEAKER NAME_PROTON}You know what it did after? Lay down.\n"
	.string "Right at my feet. Put its head on the\l"
	.string "rocks and went to sleep.\p"
	.string "Nobody ever fell asleep next to me\n"
	.string "before. They're usually running.\p"
	.string "…Wake it up gently. I mean it. Go.$"

Nexus_Text_Proton_RoaringMoon_ChampionIntro3:
	.string "I found the rest of that expedition\n"
	.string "journal. The last page just says ‘the\l"
	.string "moon is closer tonight.’ Then nothing.\p"
	.string "Look up. Count the craters. It was\n"
	.string "right.\p"
	.string "Whoever wrote it never came back. Great\n"
	.string "story. I'm not ending up in it. Let's go!$"

Nexus_Text_Proton_RoaringMoon_ChampionDefeat3:
	.string "Not ending up in it… yet.$"

Nexus_Text_Proton_RoaringMoon_ChampionAfter3:
	.string "{SPEAKER NAME_PROTON}Every claw mark on these walls goes\n"
	.string "down. Not one goes up. It never tried to\l"
	.string "climb out.\p"
	.string "Something that strong, and it just\n"
	.string "stayed in its hole, under its moon.\p"
	.string "Kind of like a guy who never quits a job\n"
	.string "he hates. …Forget it. Go.$"
```

</details>

Falante novo: `SP_NAME_PROTON`.
