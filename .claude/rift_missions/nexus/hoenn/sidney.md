# Sidney

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Sidney — Noturno** (Hoenn · Elite Four e Campeões) — treinador descontraído que aprecia batalhas intensas.

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
| `OBJ_EVENT_GFX_SIDNEY` | `graphics/object_events/pics/people/elite_four/sidney.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_SIDNEY` | `graphics/trainers/front_pics/elite_four_sidney.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_SIDNEY2` | 860 | 0x85C | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

Homônimos genéricos, **não** são este personagem: `TRAINER_SIDNEY` ("Sidney", pic Hiker).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_SIDNEY` = **1024** (flag de batalha `0x900`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Sidney_Fight`; campeão: `Nexus_EventScript_Sidney_BruteBonnet_ChampionFight` (para Brute Bonnet), `Nexus_EventScript_Sidney_Yveltal_ChampionFight` (para Yveltal). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Sidney.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_SIDNEY`, campeão de Yveltal e Brute Bonnet. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Yveltal**, a destruição em forma de asa: o Sidney sempre defendeu os Pokémon que o povo chama de mau agouro, e este é o agouro de verdade; semi-lendário **Brute Bonnet** (Planta/Sombrio, o cogumelo antigo que espera a presa dormir: primo selvagem do Shiftry e do Cacturne dele); Mega **Absol** (Darktite; em ORAS é o ás dele e mega-evolui). Mais **Mightyena** (o primeiro Pokémon dele), **Shiftry** e **Sharpedo**, do time dele em ORAS. O Dark Aura do Yveltal reforça os golpes Sombrios do time inteiro (Knock Off, Sucker Punch, Crunch).

*Plano (Singles):* o Mightyena entra com Intimidate, Taunt e Yawn para forçar trocas; o Brute Bonnet põe para dormir com Spore; a Mega Absol rebate hazards e status com Magic Bounce e sobe Swords Dance; o Sharpedo ganha velocidade com Speed Boost e o Yveltal fecha.

*Plano (Doubles):* o Shiftry abre com Fake Out e Tailwind (o Wind Rider sobe o Ataque dele junto); Mightyena solta Snarl e Intimidate; o Yveltal bate com Heat Wave e o Dark Aura vale também para o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Yveltal | Life Orb | Dark Aura | Modest | Dark Pulse, Oblivion Wing, Heat Wave, Roost |
| Brute Bonnet | Booster Energy | Protosynthesis | Adamant | Spore, Seed Bomb, Sucker Punch, Close Combat |
| Absol | Darktite | Super Luck | Jolly | Knock Off, Sucker Punch, Play Rough, Swords Dance |
| Mightyena | Sitrus Berry | Intimidate | Impish | Crunch, Taunt, Yawn, Snarl |
| Shiftry | Focus Sash | Wind Rider | Adamant | Tailwind, Fake Out, Leaf Blade, Knock Off |
| Sharpedo | Life Orb | Speed Boost | Adamant | Liquidation, Crunch, Ice Fang, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_SIDNEY ===
Name: Sidney
Class: Elite Four
Pic: Elite Four Sidney
Gender: Male
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Yveltal @ Life Orb
Modest Nature
Level: 100
Ability: Dark Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Oblivion Wing
- Heat Wave
- Roost

Brute Bonnet @ Booster Energy
Adamant Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spore
- Seed Bomb
- Sucker Punch
- Close Combat

Absol @ Darktite
Jolly Nature
Level: 100
Ability: Super Luck
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Knock Off
- Sucker Punch
- Play Rough
- Swords Dance

Mightyena @ Sitrus Berry
Impish Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Crunch
- Taunt
- Yawn
- Snarl

Shiftry @ Focus Sash
Adamant Nature
Level: 100
Ability: Wind Rider
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Fake Out
- Leaf Blade
- Knock Off

Sharpedo @ Life Orb
Adamant Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Crunch
- Ice Fang
- Protect
```

</details>


### Lendário associado

#### Yveltal

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Yveltal_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Yveltal**. Sidney é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Sidney, o primeiro da Elite Four de Hoenn, especialista em Sombrio. Descontraído, gosta de luta intensa e perde rindo.

**A criatura.** Yveltal, o Pokémon da destruição (Sombrio/Voador), de Kalos. Quando a vida dele chega ao fim, absorve a vida de tudo ao redor e vira um casulo, dormindo até despertar de novo.

**O fragmento.** Uma floresta inteira virada pedra cinza: árvores, capim, um bando de pássaros no meio da decolagem, tudo cinza e parado. No centro, um casulo do tamanho de uma casa pende de um galho seco.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest, turned to grey stone.
>
> Trees, grass, a flock of birds in the middle of taking off. All grey. All still.
>
> In the middle of it hung a cocoon the size of a house.

**Boss**

> The cocoon split down the middle.
>
> Wings opened out of it, red and black, and the grey crept a little further across the ground.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-717. The Last Wing.
>
> A forest drained to stone, and a young man who walked into it grinning and called it the most honest place he had ever seen.
>
> What came back with you is small and warm. The grey did not follow it. I checked twice.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Yveltal_Arrival:
	.string "A forest, turned to grey stone.\p"
	.string "Trees, grass, a flock of birds in the\n"
	.string "middle of taking off. All grey. All still.\p"
	.string "In the middle of it hung a cocoon the\n"
	.string "size of a house.$"

Nexus_Text_Yveltal_Boss:
	.string "The cocoon split down the middle.\p"
	.string "Wings opened out of it, red and black,\n"
	.string "and the grey crept a little further\l"
	.string "across the ground.$"

Nexus_Text_Yveltal_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-717. The Last Wing.\p"
	.string "A forest drained to stone, and a young\n"
	.string "man who walked into it grinning and\l"
	.string "called it the most honest place he had\l"
	.string "ever seen.\p"
	.string "What came back with you is small and\n"
	.string "warm. The grey did not follow it. I\l"
	.string "checked twice.$"
```

</details>


#### Brute Bonnet

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_BruteBonnet_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Brute Bonnet**. Sidney é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Sidney, da Elite Four de Hoenn, o especialista em Sombrio que adora uma luta barulhenta.

**A criatura.** Brute Bonnet, Pokémon Paradoxo antigo (Planta/Sombrio), parente pré-histórico dos cogumelos que soltam esporos. Um cogumelo enorme com mandíbula, descrito em relatos de expedição à Area Zero.

**O fragmento.** Uma selva antiga, úmida e escura, onde os cogumelos são mais altos que as árvores. Esporos brilham fraco no ar; dá sono só de respirar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An ancient jungle, dark and wet.
>
> The mushrooms here were taller than the trees, and the air glittered with spores.
>
> Just breathing it made your eyes heavy.

**Boss**

> One of the mushrooms had teeth.
>
> It had been standing still for a very long time, waiting for something to fall asleep near it.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-986. The Patient Jaw.
>
> A jungle that eats whatever sleeps, and a man who stayed wide awake in it out of pure stubbornness.
>
> What you carried out is small, and it naps constantly. He says that is fine. It is only a baby.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_BruteBonnet_Arrival:
	.string "An ancient jungle, dark and wet.\p"
	.string "The mushrooms here were taller than\n"
	.string "the trees, and the air glittered with\l"
	.string "spores.\p"
	.string "Just breathing it made your eyes\n"
	.string "heavy.$"

Nexus_Text_BruteBonnet_Boss:
	.string "One of the mushrooms had teeth.\p"
	.string "It had been standing still for a very\n"
	.string "long time, waiting for something to fall\l"
	.string "asleep near it.$"

Nexus_Text_BruteBonnet_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-986. The Patient Jaw.\p"
	.string "A jungle that eats whatever sleeps,\n"
	.string "and a man who stayed wide awake in it\l"
	.string "out of pure stubbornness.\p"
	.string "What you carried out is small, and it\n"
	.string "naps constantly. He says that is fine.\l"
	.string "It is only a baby.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Sidney_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Sidney cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey, I like that look you're giving me.
>
> Folks always call Dark types bad news. Sneaky. Mean.
>
> Me, I think they're honest. They fight to win, and they don't pretend otherwise.
>
> So don't hold back, and I won't either. Let's make some noise!

**Derrota**

> Ha! I lost! Eh, it was fun, so it doesn't matter.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_Intro:
	.string "Hey, I like that look you're giving me.\p"
	.string "Folks always call Dark types bad news.\n"
	.string "Sneaky. Mean.\p"
	.string "Me, I think they're honest. They fight\n"
	.string "to win, and they don't pretend\l"
	.string "otherwise.\p"
	.string "So don't hold back, and I won't either.\n"
	.string "Let's make some noise!$"

Nexus_Text_Sidney_Defeat:
	.string "Ha! I lost! Eh, it was fun, so it doesn't\n"
	.string "matter.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código). Nenhuma cita o lugar nem a criatura do dia.

**Variação 2** — lembrança: o primeiro Pokémon dele, um Poochyena que o mordeu no dia em que se conheceram. A cicatriz é o melhor aperto de mão da vida dele: quer dizer “não vou fingir com você”. Convite para o jogador morder também.

**Antes da luta**

> Heh. Know what my first Pokémon was? A little Poochyena that bit me the day we met.
>
> Right here, on the hand. Still got the mark.
>
> Best handshake I ever had. It meant, 'I'm not gonna pretend with you.'
>
> So go ahead. Bite. Let's go!

**Derrota**

> Ha! That one left a mark too. I'm keeping it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_Intro2:
	.string "Heh. Know what my first Pokémon was? A\n"
	.string "little Poochyena that bit me the day\l"
	.string "we met.\p"
	.string "Right here, on the hand. Still got the\n"
	.string "mark.\p"
	.string "Best handshake I ever had. It meant,\n"
	.string "'I'm not gonna pretend with you.'\p"
	.string "So go ahead. Bite. Let's go!$"

Nexus_Text_Sidney_Defeat2:
	.string "Ha! That one left a mark too. I'm\n"
	.string "keeping it.$"
```

</details>

**Variação 3** — humor e ofício: “primeira sala? Claro.” Em casa ele é o primeiro da Elite Four, o que “aquece” o desafiante. Todo mundo acha o posto fácil; ele é quem descobre se o jogador fala sério.

**Antes da luta**

> First room, huh? Figures. I always get the first room.
>
> Back home they made me the first of the Elite Four. The guy who warms you up.
>
> Folks think that's the easy spot. Nah. I'm the one who finds out if you're serious.
>
> So? You serious? Let's go!

**Derrota**

> Ha! Yeah, you're serious. Go on. The next one's worse.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_Intro3:
	.string "First room, huh? Figures. I always get\n"
	.string "the first room.\p"
	.string "Back home they made me the first of\n"
	.string "the Elite Four. The guy who warms you\l"
	.string "up.\p"
	.string "Folks think that's the easy spot. Nah.\n"
	.string "I'm the one who finds out if you're\l"
	.string "serious.\p"
	.string "So? You serious? Let's go!$"

Nexus_Text_Sidney_Defeat3:
	.string "Ha! Yeah, you're serious. Go on. The\n"
	.string "next one's worse.$"
```

</details>


### Diálogo associado ao lendário

#### Yveltal

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Sidney_Yveltal_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Sidney é o **campeão**, a luta logo antes do Yveltal. A fala é sobre a criatura, sem dizer o nome dele.

O Sidney passou a vida defendendo o Absol, que leva a culpa pelos desastres que só avisa. Aqui encontra algo que não avisa ninguém: é o próprio desastre. Pela primeira vez o sorriso dele falha, e mesmo assim ele respeita a honestidade da coisa. A virada: até o fim do mundo se cansa e dorme num casulo, e o Absol dele tremeu o caminho inteiro porque sabia.

**Antes da luta**

> You see those stone birds back there? They were flying when it happened.
>
> My Absol gets blamed for disasters it only warns folks about. I've been defending it my whole life.
>
> Well, that thing up ahead doesn't warn anybody. It IS the disaster.
>
> …Heh. Still gotta respect the honesty. Let's go!

**Derrota**

> Ha… I lost. Didn't even feel it. Kinda like those birds.

**Depois da luta**

> Here's the thing. When it's done taking, it wraps itself up and sleeps. Just a big quiet cocoon.
>
> Even the end of the world gets tired.
>
> My Absol was shaking the whole walk here, you know. It knew.
>
> Go on. Wake it up and show it somebody's still breathing.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_Yveltal_ChampionIntro:
	.string "You see those stone birds back there?\n"
	.string "They were flying when it happened.\p"
	.string "My Absol gets blamed for disasters it\n"
	.string "only warns folks about. I've been\l"
	.string "defending it my whole life.\p"
	.string "Well, that thing up ahead doesn't warn\n"
	.string "anybody. It IS the disaster.\p"
	.string "…Heh. Still gotta respect the honesty.\n"
	.string "Let's go!$"

Nexus_Text_Sidney_Yveltal_ChampionDefeat:
	.string "Ha… I lost. Didn't even feel it. Kinda\n"
	.string "like those birds.$"

Nexus_Text_Sidney_Yveltal_ChampionAfter:
	.string "{SPEAKER NAME_SIDNEY}Here's the thing. When it's done\n"
	.string "taking, it wraps itself up and sleeps.\l"
	.string "Just a big quiet cocoon.\p"
	.string "Even the end of the world gets tired.\p"
	.string "My Absol was shaking the whole walk\n"
	.string "here, you know. It knew.\p"
	.string "Go on. Wake it up and show it\n"
	.string "somebody's still breathing.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela; para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código).

**Variação 2** — dúvida: o cinza levou árvores, pássaros, capim, e não levou o Sidney. Por quê? A virada, descoberta durante a luta: a criatura não escolhe, só leva o que está perto; o Absol dele passou o caminho inteiro puxando-o para longe. O “mau agouro” era o único que o protegia.

**Antes da luta**

> Funny thing about the grey out there. It took the trees, the birds, the grass. Didn't take me.
>
> I keep asking myself why. Maybe it's not hungry for guys who grin.
>
> Or maybe it's saving me for last. Heh. That'd be a compliment, right?
>
> Let's find out which! Let's go!

**Derrota**

> Ha… guess I'm still not on the menu.

**Depois da luta**

> Figured it out while we were fighting. It doesn't pick. It just takes whatever's close.
>
> My Absol kept me far away the whole time. Always walking ahead. Always pulling.
>
> Folks call Absol a bad omen. Mine was the only one keeping me off the menu.
>
> Go on. Walk in close. Just don't stand still.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_Yveltal_ChampionIntro2:
	.string "Funny thing about the grey out there.\n"
	.string "It took the trees, the birds, the\l"
	.string "grass. Didn't take me.\p"
	.string "I keep asking myself why. Maybe it's\n"
	.string "not hungry for guys who grin.\p"
	.string "Or maybe it's saving me for last. Heh.\n"
	.string "That'd be a compliment, right?\p"
	.string "Let's find out which! Let's go!$"

Nexus_Text_Sidney_Yveltal_ChampionDefeat2:
	.string "Ha… guess I'm still not on the menu.$"

Nexus_Text_Sidney_Yveltal_ChampionAfter2:
	.string "{SPEAKER NAME_SIDNEY}Figured it out while we were fighting.\n"
	.string "It doesn't pick. It just takes\l"
	.string "whatever's close.\p"
	.string "My Absol kept me far away the whole\n"
	.string "time. Always walking ahead. Always\l"
	.string "pulling.\p"
	.string "Folks call Absol a bad omen. Mine was\n"
	.string "the only one keeping me off the menu.\p"
	.string "Go on. Walk in close. Just don't stand\n"
	.string "still.$"
```

</details>

**Variação 3** — humor e reverência: ele bateu no casulo como numa porta (“toc toc”); ninguém atendeu, e a floresta ficou um pouco mais cinza. Depois da luta, a pergunta: a criatura dorme sobre toda a vida que tomou, como quem só a guarda para alguém. Talvez devolva ao acordar.

**Antes da luta**

> Real talk? I tried knocking on the cocoon. Like a door. Knock knock.
>
> Nobody answered. The whole forest got a little greyer, though.
>
> Lesson learned. Some folks you don't wake up before they're ready.
>
> You, on the other hand? You're wide awake. Let's go!

**Derrota**

> Ha! Okay, okay. I'll stop knocking.

**Depois da luta**

> Here's what gets me. It takes all that life, and then it just sleeps on it.
>
> Like it doesn't even want it. Like it's only holding it for somebody.
>
> Maybe when it wakes up, it gives some back. Maybe that's the part nobody sticks around for.
>
> Stick around, kid. Tell me later.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_Yveltal_ChampionIntro3:
	.string "Real talk? I tried knocking on the\n"
	.string "cocoon. Like a door. Knock knock.\p"
	.string "Nobody answered. The whole forest got\n"
	.string "a little greyer, though.\p"
	.string "Lesson learned. Some folks you don't\n"
	.string "wake up before they're ready.\p"
	.string "You, on the other hand? You're wide\n"
	.string "awake. Let's go!$"

Nexus_Text_Sidney_Yveltal_ChampionDefeat3:
	.string "Ha! Okay, okay. I'll stop knocking.$"

Nexus_Text_Sidney_Yveltal_ChampionAfter3:
	.string "{SPEAKER NAME_SIDNEY}Here's what gets me. It takes all that\n"
	.string "life, and then it just sleeps on it.\p"
	.string "Like it doesn't even want it. Like it's\n"
	.string "only holding it for somebody.\p"
	.string "Maybe when it wakes up, it gives some\n"
	.string "back. Maybe that's the part nobody\l"
	.string "sticks around for.\p"
	.string "Stick around, kid. Tell me later.$"
```

</details>


#### Brute Bonnet

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Sidney_BruteBonnet_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Sidney é o **campeão**, a luta logo antes do Brute Bonnet. A fala é sobre a criatura, sem dizer o nome dele.

O Sidney vive para a luta intensa. O predador daqui é o oposto: vence fazendo a presa dormir, sem luta nenhuma. Ele reconhece o truque (o Cacturne dele segue viajantes no deserto até caírem de cansaço) e diz que é imune porque se empolga demais para dormir. A virada: a pior derrota é a que você dorme, e o conselho é ficar barulhento.

**Antes da luta**

> Careful breathing out there. That stuff in the air makes you sleepy.
>
> Big mushroom with a mouth, and it doesn't even chase you. It just waits till you nod off.
>
> My Cacturne does the same thing in the desert. Follows folks till they drop.
>
> Guess I'm immune. I get way too fired up to sleep! Let's go!

**Derrota**

> Ha, okay. I'm awake now. Real awake.

**Depois da luta**

> Worst way to lose a fight is sleeping through it.
>
> That thing never loses, 'cause nobody's ever awake to fight it.
>
> So stay loud. Stay angry if you gotta.
>
> Just don't close your eyes in there.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_BruteBonnet_ChampionIntro:
	.string "Careful breathing out there. That\n"
	.string "stuff in the air makes you sleepy.\p"
	.string "Big mushroom with a mouth, and it\n"
	.string "doesn't even chase you. It just waits\l"
	.string "till you nod off.\p"
	.string "My Cacturne does the same thing in the\n"
	.string "desert. Follows folks till they drop.\p"
	.string "Guess I'm immune. I get way too fired\n"
	.string "up to sleep! Let's go!$"

Nexus_Text_Sidney_BruteBonnet_ChampionDefeat:
	.string "Ha, okay. I'm awake now. Real awake.$"

Nexus_Text_Sidney_BruteBonnet_ChampionAfter:
	.string "{SPEAKER NAME_SIDNEY}Worst way to lose a fight is sleeping\n"
	.string "through it.\p"
	.string "That thing never loses, 'cause\n"
	.string "nobody's ever awake to fight it.\p"
	.string "So stay loud. Stay angry if you gotta.\p"
	.string "Just don't close your eyes in there.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela; para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código).

**Variação 2** — provocação e recorde: três dias acordado lá dentro. O Mightyena apagou no segundo dia e ele o carregou. A proibição da palavra “yawn”. O truque que ele ensina: cantarolar alto e desafinado, porque tudo que foi comido ali ficou quieto primeiro.

**Antes da luta**

> Three days. That's how long I've been awake in there. New record!
>
> My Mightyena conked out on day two. I carried him the rest of the way. Heavy guy.
>
> Every mushroom out there's been watching me, waiting for me to yawn.
>
> …Don't. Say. Yawn. Let's go!

**Derrota**

> Ha… that battle woke me right up. Thanks.

**Depois da luta**

> Here's a trick. Hum something. Loud and off-key.
>
> Everything that ever got eaten in there went quiet first.
>
> I've been humming since I got here. Same song. I don't even know the words.
>
> Go. Make a racket for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_BruteBonnet_ChampionIntro2:
	.string "Three days. That's how long I've been\n"
	.string "awake in there. New record!\p"
	.string "My Mightyena conked out on day two. I\n"
	.string "carried him the rest of the way. Heavy\l"
	.string "guy.\p"
	.string "Every mushroom out there's been\n"
	.string "watching me, waiting for me to yawn.\p"
	.string "…Don't. Say. Yawn. Let's go!$"

Nexus_Text_Sidney_BruteBonnet_ChampionDefeat2:
	.string "Ha… that battle woke me right up.\n"
	.string "Thanks.$"

Nexus_Text_Sidney_BruteBonnet_ChampionAfter2:
	.string "{SPEAKER NAME_SIDNEY}Here's a trick. Hum something. Loud and\n"
	.string "off-key.\p"
	.string "Everything that ever got eaten in\n"
	.string "there went quiet first.\p"
	.string "I've been humming since I got here.\n"
	.string "Same song. I don't even know the\l"
	.string "words.\p"
	.string "Go. Make a racket for me.$"
```

</details>

**Variação 3** — dúvida e contraste: o que incomoda o Sidney é a paciência da criatura, parada no mesmo lugar há mais tempo que existe gente. Paciência é vencer sem lutar (o Cacturne e o Shiftry dele sabem); ele prefere perder alto. Mas admite: ninguém fica tão velho sendo barulhento.

**Antes da luta**

> Know what bugs me about that big mushroom? It's patient.
>
> Real patient. Stood in one spot longer than there's been people.
>
> Me, I can't sit still for five minutes. We're gonna get along terribly.
>
> Let's go before I lose my nerve!

**Derrota**

> Ha! Lost it anyway. Worth it.

**Depois da luta**

> Patience is just a way to win without fighting. My Cacturne knows it. So does my Shiftry.
>
> Me? I'd rather lose loud than win like that.
>
> But I gotta admit, it's old. You don't get that old by being loud.
>
> So be loud anyway. Be the first thing it's ever met that won't wait.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sidney_BruteBonnet_ChampionIntro3:
	.string "Know what bugs me about that big\n"
	.string "mushroom? It's patient.\p"
	.string "Real patient. Stood in one spot longer\n"
	.string "than there's been people.\p"
	.string "Me, I can't sit still for five minutes.\n"
	.string "We're gonna get along terribly.\p"
	.string "Let's go before I lose my nerve!$"

Nexus_Text_Sidney_BruteBonnet_ChampionDefeat3:
	.string "Ha! Lost it anyway. Worth it.$"

Nexus_Text_Sidney_BruteBonnet_ChampionAfter3:
	.string "{SPEAKER NAME_SIDNEY}Patience is just a way to win without\n"
	.string "fighting. My Cacturne knows it. So does\l"
	.string "my Shiftry.\p"
	.string "Me? I'd rather lose loud than win like\n"
	.string "that.\p"
	.string "But I gotta admit, it's old. You don't\n"
	.string "get that old by being loud.\p"
	.string "So be loud anyway. Be the first thing\n"
	.string "it's ever met that won't wait.$"
```

</details>


Falante novo: `SP_NAME_SIDNEY` (ainda não existe em `include/constants/speaker_names.h`).
