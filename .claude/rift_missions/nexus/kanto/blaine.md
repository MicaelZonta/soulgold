# Blaine

**Região da ficha:** Kanto

Aparece no checklist como:

- **Blaine — Fogo** (Kanto · Líderes de Ginásio) — cientista excêntrico e Líder de Cinnabar.

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
| `OBJ_EVENT_GFX_BLAINE` | `graphics/object_events/pics/people/gym_leaders/blaine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BLAINE` | `graphics/trainers/front_pics/blaine.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BLAINE` | `graphics/field_mugshots/blaine.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BLAINE_OLIVINE` | 43 | 0x52B | Ninetales Lv60, Cinderace Lv60, Ceruledge Lv61, Magmortar Lv61, Volcarona Lv61, Emboar Lv62 | `OlivineCity_PortInside` |
| `TRAINER_BLAINE` | 306 | 0x632 | Rapidash Lv66, Magmortar Lv65, Houndoom Lv66, Torkoal Lv67, Camerupt Lv67 | `SaffronCity_FightingDojoVIP`, `SeafoamIslands_Gym`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BLAINE`, campeão de Moltres e Volcanion. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: Yes` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Reshiram**, o dragão das chamas da verdade: o Blaine é o homem do quiz, que quer sempre a resposta certa. Semi-lendário **Moltres**, de quem ele é campeão, a ave de fogo de Kanto que mora perto de Cinnabar. Mega **Camerupt** (Firetite), o vulcão ambulante, do time de campanha dele: o Blaine perdeu Cinnabar para um vulcão e continua amando fogo. Mais **Torkoal** (campanha), **Magmortar** (o Magmar é o ás dele em GSC/HGSS) e **Arcanine** (Red/Blue). *Plano (Singles):* sol. O Torkoal (Drought, Heat Rock) liga o sol, tira hazards com Rapid Spin e força troca com Yawn; a Mega Camerupt (Sheer Force) arma Stealth Rock; o Reshiram bate Blue Flare no sol; o Arcanine entra com Intimidate e Will-O-Wisp. Solar Beam e o Thunderbolt do Magmortar respondem aos tipos Água. *Plano (Doubles):* Heat Wave de três Pokémon diferentes sob sol, Tailwind do Moltres, Intimidate do Arcanine, e Protect da Camerupt para esperar o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Reshiram | Life Orb | Turboblaze | Modest | Blue Flare, Draco Meteor, Heat Wave, Earth Power |
| Moltres | Heavy-Duty Boots | Pressure | Timid | Heat Wave, Air Slash, Roost, Tailwind |
| Camerupt | Firetite | Solid Rock | Quiet | Heat Wave, Earth Power, Stealth Rock, Protect |
| Torkoal | Heat Rock | Drought | Bold | Heat Wave, Solar Beam, Yawn, Rapid Spin |
| Magmortar | Expert Belt | Vital Spirit | Modest | Fire Blast, Thunderbolt, Focus Blast, Psychic |
| Arcanine | Sitrus Berry | Intimidate | Adamant | Flare Blitz, Extreme Speed, Will-O-Wisp, Morning Sun |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_BLAINE ===
Name: Blaine
Class: Leader
Pic: Leader Blaine
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Reshiram @ Life Orb
Modest Nature
Level: 100
Ability: Turboblaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blue Flare
- Draco Meteor
- Heat Wave
- Earth Power

Moltres @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Air Slash
- Roost
- Tailwind

Camerupt @ Firetite
Quiet Nature
Level: 100
Ability: Solid Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Earth Power
- Stealth Rock
- Protect

Torkoal @ Heat Rock
Bold Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Solar Beam
- Yawn
- Rapid Spin

Magmortar @ Expert Belt
Modest Nature
Level: 100
Ability: Vital Spirit
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fire Blast
- Thunderbolt
- Focus Blast
- Psychic

Arcanine @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Extreme Speed
- Will-O-Wisp
- Morning Sun
```

</details>


### Lendário associado

#### Moltres

📝 **Proposta de 27/09/2026, aguardando o autor.** **Moltres**. Blaine é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Blaine, Líder de Cinnabar, especialista em Fogo e amante de charadas. O vulcão da ilha entrou em erupção e destruiu o ginásio; desde então ele luta numa caverna das Seafoam Islands.

**A criatura.** Moltres, o Pokémon chama, uma das aves lendárias de Kanto. Dizem que a chegada dele anuncia o fim do inverno e o começo da primavera; com o fogo das asas ilumina o céu.

**O fragmento.** Um vale congelado sob nuvens cinzentas, preso num inverno que não acaba. Atravessando a neve, uma faixa derretida, soltando vapor, com brotos verdes no barro.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A frozen valley under grey cloud, locked in a winter that would not end.
>
> But a strip of melted snow ran across it, steaming, with green shoots poking out of the mud.

**Boss**

> The clouds lit up from underneath, orange and gold.
>
> A great bird of fire swept down over the snow, and the valley behind it turned to spring.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-146. Flame.
>
> A winter that would not end, and a man whose island was taken by fire, still waiting for it to be kind.
>
> What you brought back is a small flame, barely a candle. The snow around the altar melted anyway.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Moltres_Arrival:
	.string "A frozen valley under grey cloud, locked\n"
	.string "in a winter that would not end.\p"
	.string "But a strip of melted snow ran across\n"
	.string "it, steaming, with green shoots poking\l"
	.string "out of the mud.$"

Nexus_Text_Moltres_Boss:
	.string "The clouds lit up from underneath,\n"
	.string "orange and gold.\p"
	.string "A great bird of fire swept down over the\n"
	.string "snow, and the valley behind it turned to\l"
	.string "spring.$"

Nexus_Text_Moltres_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-146. Flame.\p"
	.string "A winter that would not end, and a man\n"
	.string "whose island was taken by fire, still\l"
	.string "waiting for it to be kind.\p"
	.string "What you brought back is a small flame,\n"
	.string "barely a candle. The snow around the\l"
	.string "altar melted anyway.$"
```

</details>


#### Volcanion

📝 **Proposta de 27/09/2026, aguardando o autor.** **Volcanion**. Blaine é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Blaine, o cientista das charadas de Cinnabar. Depois da erupção, levou o ginásio de Fogo para dentro de uma caverna no mar.

**A criatura.** Volcanion, o Pokémon vapor, Fogo/Água. Solta o vapor de dentro pelos braços das costas, com força para explodir uma montanha, e some na névoa densa que ele mesmo faz. Dizem que vive em montanhas aonde as pessoas não vão.

**O fragmento.** Uma montanha enrolada numa névoa tão grossa que dá para se apoiar nela. O chão chia; fontes quentes fervem ao lado de riachos de neve derretida. A cada poucos segundos, a encosta inteira suspira uma nuvem.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A mountain wrapped in fog so thick you could lean on it. The ground hissed. Hot springs boiled beside streams of snowmelt.
>
> Every few seconds, the whole slope sighed out a cloud.

**Boss**

> The fog went silent.
>
> Then it tore open, and a heavy red shape with two great arms on its back blew the mist away in a single breath.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-721. Steam.
>
> A mountain of fire and water that would not destroy each other, and an old quizmaster who has lived the same way for years.
>
> What followed you out is small, and puffs a little steam when it is nervous. He says that is the right answer.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Volcanion_Arrival:
	.string "A mountain wrapped in fog so thick you\n"
	.string "could lean on it. The ground hissed. Hot\l"
	.string "springs boiled beside streams of\l"
	.string "snowmelt.\p"
	.string "Every few seconds, the whole slope\n"
	.string "sighed out a cloud.$"

Nexus_Text_Volcanion_Boss:
	.string "The fog went silent.\p"
	.string "Then it tore open, and a heavy red\n"
	.string "shape with two great arms on its back\l"
	.string "blew the mist away in a single breath.$"

Nexus_Text_Volcanion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-721. Steam.\p"
	.string "A mountain of fire and water that would\n"
	.string "not destroy each other, and an old\l"
	.string "quizmaster who has lived the same way\l"
	.string "for years.\p"
	.string "What followed you out is small, and\n"
	.string "puffs a little steam when it is nervous.\l"
	.string "He says that is the right answer.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Blaine cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hah! Quiz time! What burns hotter than a volcano?
>
> Wrong! Whatever you said, it's wrong. I lost my whole island to a volcano, so I'd know!
>
> These days my Gym is in a sea cave. Fire in a wet place, hah! Hope you packed Burn Heal!

**Derrota**

> Hah! Correct answer! My flame's out… for now.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Blaine_Intro:
	.string "Hah! Quiz time! What burns hotter than\n"
	.string "a volcano?\p"
	.string "Wrong! Whatever you said, it's wrong. I\n"
	.string "lost my whole island to a volcano, so\l"
	.string "I'd know!\p"
	.string "These days my Gym is in a sea cave. Fire\n"
	.string "in a wet place, hah! Hope you packed\l"
	.string "Burn Heal!$"

Nexus_Text_Blaine_Defeat:
	.string "Hah! Correct answer! My flame's out…\n"
	.string "for now.$"
```

</details>


### Diálogo associado ao lendário

#### Moltres

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Blaine é o **campeão**, a luta logo antes do Moltres. A fala é sobre a criatura, sem dizer o nome dela.

O Blaine abre com um quiz que ele sabe responder: o que o fogo faz? Queima tudo. A ilha, o ginásio, as anotações do laboratório. A virada: aquela ave passou sobre a neve e, por onde a sombra dela foi, o gelo quebrou e o verde subiu. Segunda pergunta, e essa ele não sabe. Depois ele confessa: jurou que nunca mais olharia uma chama do mesmo jeito, e mentiu na manhã seguinte. Talvez primavera seja só fogo que aprendeu bons modos.

**Antes da luta**

> Hah! Pop quiz! What does fire do?
>
> It burns things down! Correct! My island, my Gym, my lab notes. I know that answer better than anyone.
>
> Then that bird flew over the snow here. Wherever its shadow passed, the ice cracked and green came up.
>
> Second question, and I don't know the answer. Let's find it together!

**Derrota**

> Hah! You answered before I finished asking!

**Depois da luta**

> When the volcano took Cinnabar, I swore I'd never look at a flame the same way again.
>
> I lied. I looked at it the same way the very next morning. I love the stuff.
>
> The old stories say spring follows that bird. Maybe spring is just fire that learned some manners.
>
> Go on. And if spring ever wants a home, my sea cave could use one.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Blaine_Moltres_ChampionIntro:
	.string "Hah! Pop quiz! What does fire do?\p"
	.string "It burns things down! Correct! My\n"
	.string "island, my Gym, my lab notes. I know that\l"
	.string "answer better than anyone.\p"
	.string "Then that bird flew over the snow here.\n"
	.string "Wherever its shadow passed, the ice\l"
	.string "cracked and green came up.\p"
	.string "Second question, and I don't know the\n"
	.string "answer. Let's find it together!$"

Nexus_Text_Blaine_Moltres_ChampionDefeat:
	.string "Hah! You answered before I finished\n"
	.string "asking!$"

Nexus_Text_Blaine_Moltres_ChampionAfter:
	.string "{SPEAKER NAME_BLAINE}When the volcano took Cinnabar, I swore\n"
	.string "I'd never look at a flame the same way\l"
	.string "again.\p"
	.string "I lied. I looked at it the same way the\n"
	.string "very next morning. I love the stuff.\p"
	.string "The old stories say spring follows that\n"
	.string "bird. Maybe spring is just fire that\l"
	.string "learned some manners.\p"
	.string "Go on. And if spring ever wants a home,\n"
	.string "my sea cave could use one.$"
```

</details>


#### Volcanion

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Blaine é o **campeão**, a luta logo antes do Volcanion. A fala é sobre a criatura, sem dizer o nome dela.

Outro quiz: o que acontece quando fogo encontra água? Quase todo mundo diz que o fogo apaga. Errado: vira vapor, e vapor arranca o topo de uma montanha. A criatura vive disso, com os dois dentro e sem deixar nenhum vencer. A virada: depois do vulcão o Blaine levou o fogo dele para uma caverna no mar, e desde então ele também é vapor. Depois, a lição de cientista: vapor é invisível; a nuvem branca é só a parte que está esfriando. Não corra atrás da nuvem, observe a pressão.

**Antes da luta**

> Hah! Quiz! What happens when fire meets water?
>
> Most folks say the fire goes out. Wrong! You get steam. And steam can blow the top off a mountain!
>
> The creature here lives on exactly that. It keeps both inside and won't let either one win.
>
> After my volcano, I moved my fire into a sea cave. I suppose I've been steam ever since!

**Derrota**

> Hah! You held more pressure than I did!

**Depois da luta**

> Here's one I never put in my quizzes. Real steam is invisible. That white cloud is only the part cooling off.
>
> The power is in the part you can't see.
>
> That creature hides in its own fog, and it doesn't much care for people. Can't blame it.
>
> Don't chase the cloud. Watch the pressure. When it goes quiet, get ready.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Blaine_Volcanion_ChampionIntro:
	.string "Hah! Quiz! What happens when fire meets\n"
	.string "water?\p"
	.string "Most folks say the fire goes out. Wrong!\n"
	.string "You get steam. And steam can blow the\l"
	.string "top off a mountain!\p"
	.string "The creature here lives on exactly\n"
	.string "that. It keeps both inside and won't\l"
	.string "let either one win.\p"
	.string "After my volcano, I moved my fire into a\n"
	.string "sea cave. I suppose I've been steam\l"
	.string "ever since!$"

Nexus_Text_Blaine_Volcanion_ChampionDefeat:
	.string "Hah! You held more pressure than I did!$"

Nexus_Text_Blaine_Volcanion_ChampionAfter:
	.string "{SPEAKER NAME_BLAINE}Here's one I never put in my quizzes.\n"
	.string "Real steam is invisible. That white\l"
	.string "cloud is only the part cooling off.\p"
	.string "The power is in the part you can't see.\p"
	.string "That creature hides in its own fog, and\n"
	.string "it doesn't much care for people. Can't\l"
	.string "blame it.\p"
	.string "Don't chase the cloud. Watch the\n"
	.string "pressure. When it goes quiet, get ready.$"
```

</details>


Falante novo: `SP_NAME_BLAINE` (ainda não existe em `include/constants/speaker_names.h`).
