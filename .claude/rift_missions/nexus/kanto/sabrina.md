# Sabrina

**Região da ficha:** Kanto

Aparece no checklist como:

- **Sabrina — Psíquico** (Kanto · Líderes de Ginásio) — poderosa médium e Líder de Saffron.

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
| `OBJ_EVENT_GFX_SABRINA` | `graphics/object_events/pics/people/gym_leaders/sabrina.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_SABRINA` | `graphics/trainers/front_pics/sabrina.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_SABRINA` | 304 | 0x630 | Mr Mime Lv65, Indeedee Lv64, Slowbro Lv64, Wobbuffet Lv64, Espeon Lv65, Alakazam Lv66 | `SaffronCity_FightingDojoVIP`, `SaffronCity_Gym`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_SABRINA` = **992** (flag de batalha `0x8E0`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Sabrina_Fight`; campeão: `Nexus_EventScript_Sabrina_Palkia_ChampionFight` (para Palkia), `Nexus_EventScript_Sabrina_GalarianArticuno_ChampionFight` (para Galarian Articuno). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Sabrina.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_SABRINA`, campeã de Palkia e Galarian Articuno. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: Yes` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Palkia**, o senhor do espaço: o ginásio da Sabrina é um labirinto de teletransportes, espaço dobrado em pequeno, e o Palkia é quem dobra o horizonte. Semi-lendário **Articuno de Galar**, de quem ela também é campeã, a ave Psíquico/Voador que congela com o olhar. Mega **Alakazam** (Psychite), o ás dela desde o Red/Blue. Mais **Mr. Mime** (Red/Blue), **Espeon** (HGSS) e **Indeedee** (do time de campanha). *Plano (Singles):* o Mr. Mime (Filter, Light Clay) arma Reflect e Light Screen; atrás das telas o Articuno de Galar sobe Calm Mind (Competitive pune Intimidate), o Palkia bate com Lustrous Orb, e o Espeon com Magic Bounce devolve hazards e status. *Plano (Doubles):* a Indeedee entra com Psychic Surge (Fake Out e prioridade não pegam no chão), puxa golpes com Follow Me e dá Helping Hand; Alakazam, Mr. Mime e Espeon espalham Dazzling Gleam; Healing Wish traz o atacante de volta inteiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Palkia | Lustrous Orb | Pressure | Modest | Spacial Rend, Hydro Pump, Thunderbolt, Flamethrower |
| Articuno-Galar | Leftovers | Competitive | Timid | Freezing Glare, Hurricane, Calm Mind, Recover |
| Alakazam | Psychite | Magic Guard | Timid | Psychic, Focus Blast, Shadow Ball, Dazzling Gleam |
| Indeedee-F | Sitrus Berry | Psychic Surge | Bold | Follow Me, Psychic, Helping Hand, Healing Wish |
| Mr. Mime | Light Clay | Filter | Timid | Reflect, Light Screen, Dazzling Gleam, Psychic |
| Espeon | Life Orb | Magic Bounce | Timid | Psyshock, Dazzling Gleam, Shadow Ball, Calm Mind |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_SABRINA ===
Name: Sabrina
Class: Leader
Pic: Leader Sabrina
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Palkia @ Lustrous Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spacial Rend
- Hydro Pump
- Thunderbolt
- Flamethrower

Articuno-Galar @ Leftovers
Timid Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freezing Glare
- Hurricane
- Calm Mind
- Recover

Alakazam @ Psychite
Timid Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Focus Blast
- Shadow Ball
- Dazzling Gleam

Indeedee-F @ Sitrus Berry
Bold Nature
Level: 100
Ability: Psychic Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Follow Me
- Psychic
- Helping Hand
- Healing Wish

Mr Mime @ Light Clay
Timid Nature
Level: 100
Ability: Filter
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Dazzling Gleam
- Psychic

Espeon @ Life Orb
Timid Nature
Level: 100
Ability: Magic Bounce
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psyshock
- Dazzling Gleam
- Shadow Ball
- Calm Mind
```

</details>


### Lendário associado

#### Palkia

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Palkia_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Palkia**. Sabrina é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Sabrina, Líder de Saffron e médium: dobrava colheres com a mente quando criança e prevê quem vai chegar ao ginásio dela, um labirinto de placas de teletransporte.

**A criatura.** Palkia, o Pokémon espacial, que controla e distorce o espaço. É dito que vive num espaço paralelo; na mitologia de Sinnoh é uma das divindades da criação, parceira do Dialga, que rege o tempo.

**O fragmento.** Uma planície de pedra clara que vai longe demais. O horizonte está dobrado e um segundo horizonte pende de cabeça para baixo sobre o primeiro. Os passos do jogador ecoam na frente dele.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A plain of pale stone that went on too far. The horizon was folded, and a second horizon hung upside down above the first.
>
> Your own footsteps echoed from somewhere in front of you.

**Boss**

> The distance between you and the far mountains vanished. They were simply here.
>
> Between them stood a great pearl-shouldered shape, and space rippled off it like heat.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-484. Spatial.
>
> A place where far and near had traded places, and a woman who sees tomorrow but never where she stands.
>
> What came home with you fits in your arms. The room around it is perfectly straight. I measured.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Palkia_Arrival:
	.string "A plain of pale stone that went on too\n"
	.string "far. The horizon was folded, and a\l"
	.string "second horizon hung upside down above\l"
	.string "the first.\p"
	.string "Your own footsteps echoed from\n"
	.string "somewhere in front of you.$"

Nexus_Text_Palkia_Boss:
	.string "The distance between you and the far\n"
	.string "mountains vanished. They were simply\l"
	.string "here.\p"
	.string "Between them stood a great\n"
	.string "pearl-shouldered shape, and space\l"
	.string "rippled off it like heat.$"

Nexus_Text_Palkia_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-484. Spatial.\p"
	.string "A place where far and near had traded\n"
	.string "places, and a woman who sees tomorrow\l"
	.string "but never where she stands.\p"
	.string "What came home with you fits in your\n"
	.string "arms. The room around it is perfectly\l"
	.string "straight. I measured.$"
```

</details>


#### Galarian Articuno

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_GalarianArticuno_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Galarian Articuno**. Sabrina é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Sabrina, a médium de Saffron. Quando criança assustava as outras crianças; em HGSS já aprendeu a ser mais gentil com as pessoas.

**A criatura.** Articuno de Galar, o Pokémon cruel, Psíquico/Voador. Flutua com poder psíquico em vez de bater as asas, e dos olhos dispara raios que congelam o adversário no lugar (Freezing Glare).

**O fragmento.** Um lago congelado sob um céu violeta pálido. A neve fica parada no ar sem cair. Sobre o gelo, pessoas e Pokémon imóveis, todos olhando para cima.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A frozen lake under a pale violet sky. Snow hung in the air and did not fall.
>
> Figures stood on the ice, people and Pokémon, perfectly still, all looking up.

**Boss**

> The snow began to turn, slowly, around a single point.
>
> A blue-violet bird hung over the lake without beating its wings, and its eyes began to glow.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-144. Cruel.
>
> A lake of frozen watchers, and a medium who once froze people with a look and chose to stop.
>
> The fragment you carried out has not learned that look yet. Be the first thing it sees kindly.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_GalarianArticuno_Arrival:
	.string "A frozen lake under a pale violet sky.\n"
	.string "Snow hung in the air and did not fall.\p"
	.string "Figures stood on the ice, people and\n"
	.string "Pokémon, perfectly still, all looking up.$"

Nexus_Text_GalarianArticuno_Boss:
	.string "The snow began to turn, slowly, around a\n"
	.string "single point.\p"
	.string "A blue-violet bird hung over the lake\n"
	.string "without beating its wings, and its eyes\l"
	.string "began to glow.$"

Nexus_Text_GalarianArticuno_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-144. Cruel.\p"
	.string "A lake of frozen watchers, and a medium\n"
	.string "who once froze people with a look and\l"
	.string "chose to stop.\p"
	.string "The fragment you carried out has not\n"
	.string "learned that look yet. Be the first\l"
	.string "thing it sees kindly.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Sabrina_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Sabrina cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I saw you coming. I always do.
>
> In my Gym, the floor sends you from room to room. Most challengers get lost. I never have.
>
> …Still, there is a first time for everything. Show me yours.

**Derrota**

> I foresaw this. It still stings.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sabrina_Intro:
	.string "I saw you coming. I always do.\p"
	.string "In my Gym, the floor sends you from room\n"
	.string "to room. Most challengers get lost. I\l"
	.string "never have.\p"
	.string "…Still, there is a first time for\n"
	.string "everything. Show me yours.$"

Nexus_Text_Sabrina_Defeat:
	.string "I foresaw this. It still stings.$"
```

</details>


### Diálogo associado ao lendário

#### Palkia

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Sabrina_Palkia_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Sabrina é a **campeã**, a luta logo antes do Palkia. A fala é sobre a criatura, sem dizer o nome dela.

A Sabrina tinha orgulho das portinhas no chão do ginásio dela. A criatura faz o mesmo com montanhas: dobrou o horizonte como uma carta e, quando abriu, a Sabrina estava de pé atrás de si mesma. A virada: ela vê o futuro, e nunca viu onde está. Depois, o conselho de quem entende de distância: não confie no quanto parece longe, confie no quanto sente que está longe. E ela fica para ver, pela primeira vez, uma coisa que não previu.

**Antes da luta**

> My Gym is full of little doors in the floor. Step on one, and you are across the room. I've always been rather proud of them.
>
> The creature here does the same thing with mountains.
>
> I watched it fold the horizon like a letter. When it unfolded it, I was standing behind myself.
>
> I can see the future. I have never once seen where I am. Come.

**Derrota**

> You found the straight line in a crooked room.

**Depois da luta**

> It isn't angry. It is simply large, the way the sky is large.
>
> When it roars, the distance between things changes. Your Pokémon may be a step away, then a mile.
>
> Don't trust how far away it looks. Trust how far away it feels.
>
> …I'll wait here. I'd like to see one thing I didn't foresee.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sabrina_Palkia_ChampionIntro:
	.string "My Gym is full of little doors in the\n"
	.string "floor. Step on one, and you are across\l"
	.string "the room. I've always been rather proud\l"
	.string "of them.\p"
	.string "The creature here does the same thing\n"
	.string "with mountains.\p"
	.string "I watched it fold the horizon like a\n"
	.string "letter. When it unfolded it, I was\l"
	.string "standing behind myself.\p"
	.string "I can see the future. I have never once\n"
	.string "seen where I am. Come.$"

Nexus_Text_Sabrina_Palkia_ChampionDefeat:
	.string "You found the straight line in a\n"
	.string "crooked room.$"

Nexus_Text_Sabrina_Palkia_ChampionAfter:
	.string "{SPEAKER NAME_SABRINA}It isn't angry. It is simply large, the\n"
	.string "way the sky is large.\p"
	.string "When it roars, the distance between\n"
	.string "things changes. Your Pokémon may be a\l"
	.string "step away, then a mile.\p"
	.string "Don't trust how far away it looks.\n"
	.string "Trust how far away it feels.\p"
	.string "…I'll wait here. I'd like to see one\n"
	.string "thing I didn't foresee.$"
```

</details>


#### Galarian Articuno

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Sabrina_GalarianArticuno_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Sabrina é a **campeã**, a luta logo antes do Galarian Articuno. A fala é sobre a criatura, sem dizer o nome dela.

A Sabrina sentiu a ave olhando: quando os olhos dela acenderam, as pernas da Sabrina não mexeram, e aquilo não era poder psíquico, era só o olhar. A virada: quando menina, as outras crianças diziam que a Sabrina fazia isso com elas; ela não acreditava, agora acredita. Depois ela conta que aprender a olhar para as pessoas com gentileza demorou mais que aprender a dobrar uma colher. A ave nunca aprendeu. Então não desvie o olhar: olhe de volta, sem medo. Ela nunca viu isso.

**Antes da luta**

> Did you feel it watching? A bird, blue as a bruise. It does not fly with its wings. It holds itself up with its mind.
>
> When it looked at me, my legs would not move. That was not psychic power. Only its eyes.
>
> When I was a girl, other children said I did that to them.
>
> I never believed them. Now I do.

**Derrota**

> You moved when it told you not to. Well done.

**Depois da luta**

> For years I would not meet anyone's eyes, so I would not frighten them.
>
> Then I learned to look at people kindly. It took far longer than learning to bend a spoon.
>
> That bird never learned. It only knows the cold look.
>
> Don't look away from it. Look back, without fear. It has never seen that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Sabrina_GalarianArticuno_ChampionIntro:
	.string "Did you feel it watching? A bird, blue as\n"
	.string "a bruise. It does not fly with its wings.\l"
	.string "It holds itself up with its mind.\p"
	.string "When it looked at me, my legs would not\n"
	.string "move. That was not psychic power. Only\l"
	.string "its eyes.\p"
	.string "When I was a girl, other children said I\n"
	.string "did that to them.\p"
	.string "I never believed them. Now I do.$"

Nexus_Text_Sabrina_GalarianArticuno_ChampionDefeat:
	.string "You moved when it told you not to. Well\n"
	.string "done.$"

Nexus_Text_Sabrina_GalarianArticuno_ChampionAfter:
	.string "{SPEAKER NAME_SABRINA}For years I would not meet anyone's\n"
	.string "eyes, so I would not frighten them.\p"
	.string "Then I learned to look at people kindly.\n"
	.string "It took far longer than learning to\l"
	.string "bend a spoon.\p"
	.string "That bird never learned. It only knows\n"
	.string "the cold look.\p"
	.string "Don't look away from it. Look back,\n"
	.string "without fear. It has never seen that.$"
```

</details>


Falante novo: `SP_NAME_SABRINA` (ainda não existe em `include/constants/speaker_names.h`).
