# Flannery

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Flannery — Fogo** (Hoenn · Líderes de Ginásio) — nova Líder de Lavaridge que tenta parecer mais experiente.

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
| `OBJ_EVENT_GFX_FLANNERY` | `graphics/object_events/pics/people/gym_leaders/flannery.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_FLANNERY` | `graphics/trainers/front_pics/leader_flannery.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_FLANNERY` = **1018** (flag de batalha `0x8FA`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Flannery_Fight`; campeão: `Nexus_EventScript_Flannery_Heatran_ChampionFight` (para Heatran), `Nexus_EventScript_Flannery_ChiYu_ChampionFight` (para Chi-Yu). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Flannery.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_FLANNERY`, campeã de Heatran e Chi-Yu. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Groudon** com Red Orb (a Primal ocupa a vaga de Mega, R10): o continente e a lava de Hoenn, o vulcão ao lado de Lavaridge; semi-lendário **Heatran**, o domo de lava que anda pelo teto. Mais **Torkoal** (o ás dela), **Camerupt** (o Mt. Chimney que ela vê da janela), **Talonflame** e **Arcanine**.

*Plano (Singles):* o Heatran arma Stealth Rock; o Primal Groudon põe o Desolate Land, que evapora qualquer golpe de Água, e sobe com Swords Dance. Se o Groudon cai, o Torkoal de Drought devolve o sol e o Eruption do Torkoal e do Camerupt sai com HP cheio; o Arcanine de Intimidate e Will-O-Wisp amacia os atacantes físicos.

*Plano (Doubles):* o Talonflame de Gale Wings põe Tailwind com prioridade; o Arcanine entra com Intimidate e Snarl; sob Tailwind e sol, Eruption e Heat Wave do Torkoal e Precipice Blades do Groudon (alvo duplo, só nos adversários). Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Groudon | Red Orb | Drought | Adamant | Precipice Blades, Fire Punch, Stone Edge, Swords Dance |
| Heatran | Leftovers | Flash Fire | Modest | Magma Storm, Earth Power, Flash Cannon, Stealth Rock |
| Torkoal | Charcoal | Drought | Quiet | Eruption, Heat Wave, Solar Beam, Rapid Spin |
| Camerupt | Life Orb | Solid Rock | Modest | Eruption, Earth Power, Fire Blast, Yawn |
| Talonflame | Sharp Beak | Gale Wings | Jolly | Brave Bird, Flare Blitz, Tailwind, U-turn |
| Arcanine | Sitrus Berry | Intimidate | Adamant | Flare Blitz, Extreme Speed, Will-O-Wisp, Snarl |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_FLANNERY ===
Name: Flannery
Class: Leader
Pic: Leader Flannery
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Groudon @ Red Orb
Adamant Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Precipice Blades
- Fire Punch
- Stone Edge
- Swords Dance

Heatran @ Leftovers
Modest Nature
Level: 100
Ability: Flash Fire
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Magma Storm
- Earth Power
- Flash Cannon
- Stealth Rock

Torkoal @ Charcoal
Quiet Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Eruption
- Heat Wave
- Solar Beam
- Rapid Spin

Camerupt @ Life Orb
Modest Nature
Level: 100
Ability: Solid Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Eruption
- Earth Power
- Fire Blast
- Yawn

Talonflame @ Sharp Beak
Jolly Nature
Level: 100
Ability: Gale Wings
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Flare Blitz
- Tailwind
- U-turn

Arcanine @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Extreme Speed
- Will-O-Wisp
- Snarl
```

</details>


### Lendário associado

#### Heatran

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Heatran_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Heatran**. Flannery é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Flannery, a Líder nova de Lavaridge, que herdou o ginásio do avô e passa o tempo tentando parecer mais experiente do que é.

**A criatura.** Heatran (Fogo/Aço) vive nas cavernas vulcânicas do Stark Mountain, em Sinnoh. O sangue dele ferve como magma, e ele anda por paredes e tetos com os pés em forma de cruz.

**O fragmento.** O interior de uma montanha, iluminado de baixo. As paredes são ferro esfriando, e alguma coisa arranha o teto.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> The inside of a mountain, lit from below.
>
> The walls were iron, slowly cooling, and the lava in the channels glowed brighter every time you looked away.

**Boss**

> Something scraped across the ceiling, right above you.
>
> It hung upside down on cross-shaped feet, and its body glowed like metal fresh from the forge.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-485. Lava Dome.
>
> A mountain with a furnace for a heart, and a young Gym Leader trying very hard to burn as hot as her grandfather.
>
> What came back with you is small and warm, and it clings to anything above it. I have noted the ceiling. I am not sure why.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Heatran_Arrival:
	.string "The inside of a mountain, lit from\n"
	.string "below.\p"
	.string "The walls were iron, slowly cooling, and\n"
	.string "the lava in the channels glowed\l"
	.string "brighter every time you looked away.$"

Nexus_Text_Heatran_Boss:
	.string "Something scraped across the ceiling,\n"
	.string "right above you.\p"
	.string "It hung upside down on cross-shaped\n"
	.string "feet, and its body glowed like metal\l"
	.string "fresh from the forge.$"

Nexus_Text_Heatran_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-485. Lava Dome.\p"
	.string "A mountain with a furnace for a heart,\n"
	.string "and a young Gym Leader trying very\l"
	.string "hard to burn as hot as her\l"
	.string "grandfather.\p"
	.string "What came back with you is small and\n"
	.string "warm, and it clings to anything above\l"
	.string "it. I have noted the ceiling. I am not\l"
	.string "sure why.$"
```

</details>

#### Chi-Yu

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_ChiYu_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Chi-Yu**. Flannery é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Flannery, a Líder de Lavaridge, cidade das fontes termais ao pé do vulcão.

**A criatura.** Chi-Yu (Sombrio/Fogo) é um dos Tesouros da Ruína de Paldea, nascido de contas antigas e amaldiçoadas. Parece um peixinho de fogo; derrete rocha e areia num mar de lava e nada nele. A habilidade Beads of Ruin enfraquece a Sp. Def de todos ao redor.

**O fragmento.** Um lago de lava sob um céu preto. Na margem, contas de jade chamuscadas, e ficar perto delas deixa todo mundo mais fraco.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A lake of lava, glowing red under a black sky.
>
> Old jade beads lay scorched along the shore. Standing near them made everything feel weaker, as if the air had been thinned.

**Boss**

> Something small swam up through the molten rock, like a goldfish rising in a pond.
>
> Around it, the beads on the shore began to burn again.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-1004. The Ruinous.
>
> A lake of fire made from melted stone, and a young woman who burns hottest when she fears she is not enough.
>
> What came back with you swims in circles in the palm of a hand, warm as a coal. It is not ruinous yet. I intend to write that down every day.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_ChiYu_Arrival:
	.string "A lake of lava, glowing red under a\n"
	.string "black sky.\p"
	.string "Old jade beads lay scorched along the\n"
	.string "shore. Standing near them made\l"
	.string "everything feel weaker, as if the air\l"
	.string "had been thinned.$"

Nexus_Text_ChiYu_Boss:
	.string "Something small swam up through the\n"
	.string "molten rock, like a goldfish rising in a\l"
	.string "pond.\p"
	.string "Around it, the beads on the shore\n"
	.string "began to burn again.$"

Nexus_Text_ChiYu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1004. The Ruinous.\p"
	.string "A lake of fire made from melted stone,\n"
	.string "and a young woman who burns hottest\l"
	.string "when she fears she is not enough.\p"
	.string "What came back with you swims in\n"
	.string "circles in the palm of a hand, warm as a\l"
	.string "coal. It is not ruinous yet. I intend to\l"
	.string "write that down every day.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Flannery_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Flannery cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> W-welcome! I'm Flannery, Gym Leader of Lavaridge! I'll show you the hot moves of a… ahem.
>
> I don't know this place. But Grandpa always said a real Fire Trainer brings her own heat.
>
> So get ready to get burned! …Wait, that came out wrong. Let's just battle!

**Derrota**

> Ugh! I got way too fired up again, didn't I?

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_Intro:
	.string "W-welcome! I'm Flannery, Gym Leader of\n"
	.string "Lavaridge! I'll show you the hot moves\l"
	.string "of a… ahem.\p"
	.string "I don't know this place. But Grandpa\n"
	.string "always said a real Fire Trainer brings\l"
	.string "her own heat.\p"
	.string "So get ready to get burned! …Wait, that\n"
	.string "came out wrong. Let's just battle!$"

Nexus_Text_Flannery_Defeat:
	.string "Ugh! I got way too fired up again,\n"
	.string "didn't I?$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): falam só dela mesma, sem o lugar nem a criatura do dia. A variação 1 é a de cima, que está no jogo; as novas não a repetem. Nada disto está no código.

**Variação 2** — o ensaio que dá errado: ela tenta três aberturas de Líder, desiste das quarenta do caderno e vai direto para a luta.

**Antes da luta**

> Okay. Deep breath. 'Welcome, challenger! My flames will…' No. 'Behold my…' NO!
>
> Grandpa never needed lines. He'd just smile, and the whole room got warmer.
>
> I wrote forty openings in my notebook. You get none of them. Let's go!

**Derrota**

> …I should've used opening number twelve.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_Intro2:
	.string "Okay. Deep breath. 'Welcome,\n"
	.string "challenger! My flames will…' No. 'Behold\l"
	.string "my…' NO!\p"
	.string "Grandpa never needed lines. He'd just\n"
	.string "smile, and the whole room got warmer.\p"
	.string "I wrote forty openings in my notebook.\n"
	.string "You get none of them. Let's go!$"

Nexus_Text_Flannery_Defeat2:
	.string "…I should've used opening number\n"
	.string "twelve.$"
```

</details>

**Variação 3** — R21, com humor: no fragmento dela, as fontes termais de Lavaridge esfriaram de uma hora para outra e todo mundo olhou para ela.

**Antes da luta**

> Back home, the hot springs went cold one morning. Just like that. Everyone looked at me, like I should fix it.
>
> I'm a Fire Trainer! Not a plumber! …But I did try. For weeks.
>
> They're still cold. So I'm extra fired up today. Sorry in advance!

**Derrota**

> Cooled off. Like the springs. Great.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_Intro3:
	.string "Back home, the hot springs went cold\n"
	.string "one morning. Just like that. Everyone\l"
	.string "looked at me, like I should fix it.\p"
	.string "I'm a Fire Trainer! Not a plumber! …But I\n"
	.string "did try. For weeks.\p"
	.string "They're still cold. So I'm extra fired\n"
	.string "up today. Sorry in advance!$"

Nexus_Text_Flannery_Defeat3:
	.string "Cooled off. Like the springs. Great.$"
```

</details>

### Diálogo associado ao lendário

#### Heatran

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Flannery_Heatran_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Flannery é a **campeã**, a luta logo antes do Heatran. A fala é sobre a criatura, sem dizer o nome dela.

A Flannery treina a pose de Líder durante meses: falas no espelho, cara de durona. A criatura não ensaia nada, anda de cabeça para baixo no teto e é quente por inteiro. Ela fica brava e luta "por inteiro". A virada: o bicho nunca olha para ninguém para ver se impressionou, e o avô também era assim; ele nunca tentou ser o Treinador mais quente de Lavaridge, ele simplesmente era. Ela estava copiando o estilo dele quando devia estar achando o próprio fogo.

**Antes da luta**

> Did you see it? It walked straight across the ceiling. Upside down. Glowing like iron in a forge.
>
> I've been practicing my fierce Gym Leader look for months. Lines in the mirror. A cool pose.
>
> That thing doesn't practice anything. It's just hot. Hot all the way through.
>
> …Grr! Fine! Let me show you my heat, all the way through!

**Derrota**

> You didn't even flinch. Not once.

**Depois da luta**

> Know what I noticed? It never looks at anyone to see if they're impressed.
>
> Grandpa was like that. He never tried to be the hottest Trainer in Lavaridge. He just was.
>
> I've been copying his moves, when I should've been finding my own fire.
>
> Go on ahead! And if it melts your shoes, walk on the ceiling! Ha!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_Heatran_ChampionIntro:
	.string "Did you see it? It walked straight\n"
	.string "across the ceiling. Upside down.\l"
	.string "Glowing like iron in a forge.\p"
	.string "I've been practicing my fierce Gym\n"
	.string "Leader look for months. Lines in the\l"
	.string "mirror. A cool pose.\p"
	.string "That thing doesn't practice anything.\n"
	.string "It's just hot. Hot all the way through.\p"
	.string "…Grr! Fine! Let me show you my heat, all\n"
	.string "the way through!$"

Nexus_Text_Flannery_Heatran_ChampionDefeat:
	.string "You didn't even flinch. Not once.$"

Nexus_Text_Flannery_Heatran_ChampionAfter:
	.string "{SPEAKER NAME_FLANNERY}Know what I noticed? It never looks at\n"
	.string "anyone to see if they're impressed.\p"
	.string "Grandpa was like that. He never tried\n"
	.string "to be the hottest Trainer in Lavaridge.\l"
	.string "He just was.\p"
	.string "I've been copying his moves, when I\n"
	.string "should've been finding my own fire.\p"
	.string "Go on ahead! And if it melts your shoes,\n"
	.string "walk on the ceiling! Ha!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para Heatran: sobre a criatura, sem o nome da espécie. A variação 1 é a de cima, que está no jogo. Nada disto está no código.

**Variação 2** — humor e medo: ela tentou subir a parede para ver melhor e ele ficou olhando, divertido, do teto. Depois percebe que ele se agarra à rocha com força, com medo de cair: tanto fogo e medo de cair.

**Antes da luta**

> Okay, confession. I tried climbing the wall to get a better look at it. I got about this high.
>
> It just watched me from the ceiling. Upside down. I swear it looked amused.
>
> Well, I'm not upside down now! Let's battle, right side up!

**Derrota**

> Flipped over. Totally flipped.

**Depois da luta**

> You know how it stays up there? Its feet grip the rock. Tight, like it's afraid to fall.
>
> All that fire, and it's scared of falling. That made me like it a lot more.
>
> I'm scared too. Of letting Lavaridge down. Doesn't mean I stop climbing. Go on!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_Heatran_ChampionIntro2:
	.string "Okay, confession. I tried climbing the\n"
	.string "wall to get a better look at it. I got\l"
	.string "about this high.\p"
	.string "It just watched me from the ceiling.\n"
	.string "Upside down. I swear it looked amused.\p"
	.string "Well, I'm not upside down now! Let's\n"
	.string "battle, right side up!$"

Nexus_Text_Flannery_Heatran_ChampionDefeat2:
	.string "Flipped over. Totally flipped.$"

Nexus_Text_Flannery_Heatran_ChampionAfter2:
	.string "{SPEAKER NAME_FLANNERY}You know how it stays up there? Its\n"
	.string "feet grip the rock. Tight, like it's\l"
	.string "afraid to fall.\p"
	.string "All that fire, and it's scared of\n"
	.string "falling. That made me like it a lot more.\p"
	.string "I'm scared too. Of letting Lavaridge\n"
	.string "down. Doesn't mean I stop climbing. Go\l"
	.string "on!$"
```

</details>

**Variação 3** — a lore de Platinum: a Magma Stone, que alguém tentou roubar do Stark Mountain, e o homem de sobretudo que impediu e foi embora sem agradecimento (o Looker de Platinum, que o Nexus nunca nomeia; fio do casaco). A pedra dela é o ginásio que herdou.

**Antes da luta**

> There's a stone deep in this mountain. Red and warm, like a heart. The creature sleeps near it.
>
> Somebody tried to steal it once. A man in a long coat stopped them, I heard. Then he just left.
>
> Didn't even stay to be thanked. That's so cool. …I mean -- let's battle!

**Derrota**

> Ugh. You'd leave without being thanked too, wouldn't you?

**Depois da luta**

> Without that stone the mountain goes cold, and so does the creature. The stone is what keeps it warm.
>
> Grandpa gave me the Gym. That's my stone, I guess. Sometimes it feels heavy.
>
> But I checked. It's still warm. Go on, now. And don't take anything from this mountain!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_Heatran_ChampionIntro3:
	.string "There's a stone deep in this mountain.\n"
	.string "Red and warm, like a heart. The creature\l"
	.string "sleeps near it.\p"
	.string "Somebody tried to steal it once. A man\n"
	.string "in a long coat stopped them, I heard.\l"
	.string "Then he just left.\p"
	.string "Didn't even stay to be thanked. That's\n"
	.string "so cool. …I mean -- let's battle!$"

Nexus_Text_Flannery_Heatran_ChampionDefeat3:
	.string "Ugh. You'd leave without being thanked\n"
	.string "too, wouldn't you?$"

Nexus_Text_Flannery_Heatran_ChampionAfter3:
	.string "{SPEAKER NAME_FLANNERY}Without that stone the mountain goes\n"
	.string "cold, and so does the creature. The\l"
	.string "stone is what keeps it warm.\p"
	.string "Grandpa gave me the Gym. That's my\n"
	.string "stone, I guess. Sometimes it feels\l"
	.string "heavy.\p"
	.string "But I checked. It's still warm. Go on,\n"
	.string "now. And don't take anything from this\l"
	.string "mountain!$"
```

</details>

#### Chi-Yu

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Flannery_ChiYu_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Flannery é a **campeã**, a luta logo antes do Chi-Yu. A fala é sobre a criatura, sem dizer o nome dela.

A Flannery vê uma coisinha do tamanho do peixinho dourado que ela tinha na infância, que derrete o chão num lago de fogo e, pior, deixa todo mundo ao redor mais fraco, como quem abre espaço para parecer grande. Ela conhece o truque. A virada é uma confissão: quando virou Líder, ela meio que queria que os outros parecessem pequenos, para ela parecer forte. Mas as fontes termais de Lavaridge não queimam ninguém: esquentam as pessoas para elas seguirem em frente. É para isso que serve o fogo.

**Antes da luta**

> It's tiny. Honestly, it's about the size of the goldfish I had as a kid.
>
> But it melted the ground into a lake of fire, and it swims in there like it's bath water.
>
> And standing near it, everything feels weaker. Your Pokémon, you, me. Like it's making room to look big.
>
> …I know that trick. I don't like it. Let's battle!

**Derrota**

> Wow. You stayed strong, even after all that.

**Depois da luta**

> When I first became a Gym Leader, I kind of wanted everyone else to look small.
>
> If they were weak, then maybe I'd look strong. That's exactly what that little thing does.
>
> But the hot springs in Lavaridge don't burn anybody. They warm people up, so they can keep going.
>
> That's what fire is for. Go and remind it!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_ChiYu_ChampionIntro:
	.string "It's tiny. Honestly, it's about the\n"
	.string "size of the goldfish I had as a kid.\p"
	.string "But it melted the ground into a lake of\n"
	.string "fire, and it swims in there like it's\l"
	.string "bath water.\p"
	.string "And standing near it, everything feels\n"
	.string "weaker. Your Pokémon, you, me. Like it's\l"
	.string "making room to look big.\p"
	.string "…I know that trick. I don't like it.\n"
	.string "Let's battle!$"

Nexus_Text_Flannery_ChiYu_ChampionDefeat:
	.string "Wow. You stayed strong, even after all\n"
	.string "that.$"

Nexus_Text_Flannery_ChiYu_ChampionAfter:
	.string "{SPEAKER NAME_FLANNERY}When I first became a Gym Leader, I\n"
	.string "kind of wanted everyone else to look\l"
	.string "small.\p"
	.string "If they were weak, then maybe I'd look\n"
	.string "strong. That's exactly what that\l"
	.string "little thing does.\p"
	.string "But the hot springs in Lavaridge don't\n"
	.string "burn anybody. They warm people up, so\l"
	.string "they can keep going.\p"
	.string "That's what fire is for. Go and remind\n"
	.string "it!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para Chi-Yu: sobre a criatura, sem o nome da espécie. A variação 1 é a de cima, que está no jogo. Nada disto está no código.

**Variação 2** — a lore dos Tesouros da Ruína: as contas eram de alguém que sempre quis ser o mais brilhante da sala, e o querer entrou nelas. Ela pegou uma conta, sentiu todo mundo ficar mais apagado e gostou, e isso a assusta.

**Antes da luta**

> Those beads on the shore? Somebody wore them once. Somebody who always wanted to be the brightest one in the room.
>
> The wanting soaked into the beads. And then the beads… woke up.
>
> Yikes. Note to self: stop wanting so loud. Let's battle!

**Derrota**

> I wanted to win… quietly. It didn't work.

**Depois da luta**

> I picked up one of the beads. It was warm, and for a second everyone else got a little dimmer.
>
> It felt great. That's the scary part.
>
> I put it back. Took me three tries. Go, before I change my mind about that bead.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_ChiYu_ChampionIntro2:
	.string "Those beads on the shore? Somebody\n"
	.string "wore them once. Somebody who always\l"
	.string "wanted to be the brightest one in the\l"
	.string "room.\p"
	.string "The wanting soaked into the beads. And\n"
	.string "then the beads… woke up.\p"
	.string "Yikes. Note to self: stop wanting so\n"
	.string "loud. Let's battle!$"

Nexus_Text_Flannery_ChiYu_ChampionDefeat2:
	.string "I wanted to win… quietly. It didn't\n"
	.string "work.$"

Nexus_Text_Flannery_ChiYu_ChampionAfter2:
	.string "{SPEAKER NAME_FLANNERY}I picked up one of the beads. It was\n"
	.string "warm, and for a second everyone else\l"
	.string "got a little dimmer.\p"
	.string "It felt great. That's the scary part.\p"
	.string "I put it back. Took me three tries. Go,\n"
	.string "before I change my mind about that\l"
	.string "bead.$"
```

</details>

**Variação 3** — a lembrança, puxando o fio da variação 1: o peixinho dourado da infância se chamava Ember e viveu nove anos. A criatura nada igual; derreteu o chão porque queria um aquário maior.

**Antes da luta**

> I had a goldfish as a kid. Named it Ember. Ember lived nine years. Nine! Nobody believes me.
>
> That thing swims in the lava the exact same way. Little circles. Tail wiggle. I nearly cried.
>
> …Don't laugh! Or do. Just battle me after!

**Derrota**

> Okay. Now you can laugh.

**Depois da luta**

> Ember was never scary. Ember was just small and orange and very sure about its bowl.
>
> That creature's the same, I think. It melted the ground because it wanted a bigger bowl.
>
> You can't blame a fish for that. But you can give it a better one. Go on!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Flannery_ChiYu_ChampionIntro3:
	.string "I had a goldfish as a kid. Named it\n"
	.string "Ember. Ember lived nine years. Nine!\l"
	.string "Nobody believes me.\p"
	.string "That thing swims in the lava the exact\n"
	.string "same way. Little circles. Tail wiggle. I\l"
	.string "nearly cried.\p"
	.string "…Don't laugh! Or do. Just battle me\n"
	.string "after!$"

Nexus_Text_Flannery_ChiYu_ChampionDefeat3:
	.string "Okay. Now you can laugh.$"

Nexus_Text_Flannery_ChiYu_ChampionAfter3:
	.string "{SPEAKER NAME_FLANNERY}Ember was never scary. Ember was just\n"
	.string "small and orange and very sure about\l"
	.string "its bowl.\p"
	.string "That creature's the same, I think. It\n"
	.string "melted the ground because it wanted a\l"
	.string "bigger bowl.\p"
	.string "You can't blame a fish for that. But you\n"
	.string "can give it a better one. Go on!$"
```

</details>

Falante novo: `SP_NAME_FLANNERY` (não existe ainda em `include/constants/speaker_names.h`).
