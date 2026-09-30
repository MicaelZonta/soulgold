# Maxie

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Maxie** (Hoenn · Team Magma) — líder que pretende expandir as massas de terra usando Groudon.

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
| `OBJ_EVENT_GFX_MAXIE` | `graphics/object_events/pics/people/team_magma/maxie.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_MAGMA_LEADER_MAXIE` | `graphics/trainers/front_pics/magma_leader_maxie.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MAXIE_MOSSDEEP` | 734 | 0x7DE | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_477` (ex-`TRAINER_MAXIE_MAGMA_HIDEOUT`, 601), `TRAINER_UNUSED_478` (ex-`TRAINER_MAXIE_MT_CHIMNEY`, 602).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_MAXIE` = **1035** (flag de batalha `0x90B`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Maxie_Fight`; campeão: `Nexus_EventScript_Maxie_Groudon_ChampionFight` (para Groudon), `Nexus_EventScript_Maxie_Landorus_ChampionFight` (para Landorus). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Maxie.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_MAXIE`, campeão de Groudon e Landorus. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário e Mega na mesma peça: **Groudon** com Red Orb (Primal conta como Mega, R10), a criatura que ele acordou para expandir a terra; semi-lendário **Landorus** (Terra/Voador, o senhor da colheita: a terra fértil que o Maxie prometia à humanidade), de quem ele também é campeão. Mais **Camerupt**, **Crobat**, **Mightyena** e **Weezing**, do time dele em ORAS. O Desolate Land da Primal anula golpes de Água: o problema de sempre do Maxie, o mar, some.

*Plano (Singles):* o Landorus arma Stealth Rock e bate com Sheer Force; o Weezing queima com Will-O-Wisp; o Crobat usa Taunt; o Groudon Primal sobe Swords Dance e limpa com Precipice Blades; o Camerupt solta Eruption no sol.

*Plano (Doubles):* Precipice Blades e Heat Wave em área; Weezing (Levitate) e Crobat (Voador) são imunes ao chão; o Crobat põe Tailwind e o Mightyena entra com Intimidate.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Groudon | Red Orb | Drought | Adamant | Precipice Blades, Heat Crash, Stone Edge, Swords Dance |
| Landorus | Life Orb | Sheer Force | Modest | Earth Power, Sludge Bomb, Focus Blast, Stealth Rock |
| Camerupt | Charcoal | Solid Rock | Quiet | Eruption, Heat Wave, Earth Power, Protect |
| Crobat | Sitrus Berry | Inner Focus | Jolly | Tailwind, Brave Bird, Super Fang, Taunt |
| Mightyena | Sitrus Berry | Intimidate | Adamant | Crunch, Sucker Punch, Play Rough, Taunt |
| Weezing | Black Sludge | Levitate | Bold | Will-O-Wisp, Sludge Bomb, Fire Blast, Pain Split |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_MAXIE ===
Name: Maxie
Class: Magma Leader
Pic: Magma Leader Maxie
Gender: Male
Music: Magma
Double Battle: No
AI: Smart Trainer

Groudon @ Red Orb
Adamant Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Precipice Blades
- Heat Crash
- Stone Edge
- Swords Dance

Landorus @ Life Orb
Modest Nature
Level: 100
Ability: Sheer Force
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earth Power
- Sludge Bomb
- Focus Blast
- Stealth Rock

Camerupt @ Charcoal
Quiet Nature
Level: 100
Ability: Solid Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Eruption
- Heat Wave
- Earth Power
- Protect

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Brave Bird
- Super Fang
- Taunt

Mightyena @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Crunch
- Sucker Punch
- Play Rough
- Taunt

Weezing @ Black Sludge
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Will-O-Wisp
- Sludge Bomb
- Fire Blast
- Pain Split
```

</details>


### Lendário associado

#### Groudon

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Groudon_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Groudon**. Maxie é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Maxie, líder da Team Magma. Cientista frio, quis expandir a terra para a humanidade prosperar e despertou o Groudon para isso; na crise de Sootopolis viu, junto com o Archie, o que tinha feito.

**A criatura.** Groudon, a personificação da terra (Terra), de Hoenn. Ergueu continentes, lutou contra o Kyogre e dormia no magma; com a Red Orb assume a forma Primal, cujo sol seca qualquer chuva.

**O fragmento.** Um mar que secou por inteiro: salinas e rachaduras até o horizonte, cascos de navio encalhados em terra firme, e um sol tão forte que não existe sombra.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A sea that had dried up completely.
>
> Salt flats and cracks all the way to the horizon, and the hulls of ships stranded on dry land.
>
> The sun was so strong there were no shadows.

**Boss**

> The ground split open. It was not a crack. It was a seam of magma.
>
> Something climbed out of it, glowing with lines like a map, and the last puddle in the world boiled away.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-383. The Continent.
>
> All the land a man could ever ask for, and the man who once asked for it.
>
> What came back with you is small, and warm to the touch. He looked at it a long time. Then he asked me whether anyone had been aboard those ships.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Groudon_Arrival:
	.string "A sea that had dried up completely.\p"
	.string "Salt flats and cracks all the way to\n"
	.string "the horizon, and the hulls of ships\l"
	.string "stranded on dry land.\p"
	.string "The sun was so strong there were no\n"
	.string "shadows.$"

Nexus_Text_Groudon_Boss:
	.string "The ground split open. It was not a\n"
	.string "crack. It was a seam of magma.\p"
	.string "Something climbed out of it, glowing\n"
	.string "with lines like a map, and the last\l"
	.string "puddle in the world boiled away.$"

Nexus_Text_Groudon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-383. The Continent.\p"
	.string "All the land a man could ever ask for,\n"
	.string "and the man who once asked for it.\p"
	.string "What came back with you is small, and\n"
	.string "warm to the touch. He looked at it a\l"
	.string "long time. Then he asked me whether\l"
	.string "anyone had been aboard those ships.$"
```

</details>


#### Landorus

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Landorus_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Landorus**. Maxie é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Maxie, o ex-líder da Team Magma que prometia terra para a humanidade.

**A criatura.** Landorus, o Pokémon da abundância (Terra/Voador), das Forças da Natureza de Unova. Onde ele passa, as colheitas são fartas; é chamado de guardião dos campos e castiga os dois irmãos da tempestade.

**O fragmento.** Campos de trigo dourado até todos os horizontes, maduros e curvados de peso, sem ninguém para colher. Uma nuvem baixa passa por cima e deixa cair sementes como chuva.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Fields of golden wheat to every horizon, heavy and bent with grain.
>
> No one had come to harvest them.
>
> Overhead, a single cloud drifted low, and seeds fell from it like rain.

**Boss**

> The cloud came down to the field.
>
> Someone was riding it, laughing like thunder over the hills, and the wheat bowed flat as it passed.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-645. The Harvest Cloud.
>
> Endless harvest and no hands to gather it, and a scientist who once promised land to all of humanity.
>
> What came back with you is small, and it sleeps on the windowsill in the sun. He said, very quietly, that he had forgotten to count the farmers.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Landorus_Arrival:
	.string "Fields of golden wheat to every\n"
	.string "horizon, heavy and bent with grain.\p"
	.string "No one had come to harvest them.\p"
	.string "Overhead, a single cloud drifted low,\n"
	.string "and seeds fell from it like rain.$"

Nexus_Text_Landorus_Boss:
	.string "The cloud came down to the field.\p"
	.string "Someone was riding it, laughing like\n"
	.string "thunder over the hills, and the wheat\l"
	.string "bowed flat as it passed.$"

Nexus_Text_Landorus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-645. The Harvest Cloud.\p"
	.string "Endless harvest and no hands to\n"
	.string "gather it, and a scientist who once\l"
	.string "promised land to all of humanity.\p"
	.string "What came back with you is small, and it\n"
	.string "sleeps on the windowsill in the sun. He\l"
	.string "said, very quietly, that he had\l"
	.string "forgotten to count the farmers.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Maxie_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Maxie cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I am Maxie, of Team Magma. Or I was. The title is harder to put down than it looks.
>
> I once believed humanity needed more land to flourish. I nearly boiled the sea to prove it.
>
> I was wrong about the method. I have not yet decided whether I was wrong about the dream.
>
> Let us see if you can help me decide.

**Derrota**

> Hm. Once again, a young Trainer corrects my calculations.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Intro:
	.string "I am Maxie, of Team Magma. Or I was. The\n"
	.string "title is harder to put down than it\l"
	.string "looks.\p"
	.string "I once believed humanity needed more\n"
	.string "land to flourish. I nearly boiled the\l"
	.string "sea to prove it.\p"
	.string "I was wrong about the method. I have\n"
	.string "not yet decided whether I was wrong\l"
	.string "about the dream.\p"
	.string "Let us see if you can help me decide.$"

Nexus_Text_Maxie_Defeat:
	.string "Hm. Once again, a young Trainer\n"
	.string "corrects my calculations.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)), além da que já está no jogo (variação 1). O sorteio de qual variação toca ainda não existe no código.

**Variação 2** — o cientista: ele mede tudo, inclusive o jogador, e prevê a própria derrota.

**Antes da luta**

> Maxie. Formerly of Team Magma. I measure things. Temperatures, depths, ratios. It calms me.
>
> I measured you as you walked in. Heart rate elevated. Stride confident.
>
> My prediction is that I lose. My predictions about young Trainers are, historically, correct.
>
> Let us test the hypothesis.

**Derrota**

> Hm. Hypothesis confirmed. How very unsatisfying.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Intro2:
	.string "Maxie. Formerly of Team Magma. I\n"
	.string "measure things. Temperatures, depths,\l"
	.string "ratios. It calms me.\p"
	.string "I measured you as you walked in. Heart\n"
	.string "rate elevated. Stride confident.\p"
	.string "My prediction is that I lose. My\n"
	.string "predictions about young Trainers are,\l"
	.string "historically, correct.\p"
	.string "Let us test the hypothesis.$"

Nexus_Text_Maxie_Defeat2:
	.string "Hm. Hypothesis confirmed. How very\n"
	.string "unsatisfying.$"
```

</details>

**Variação 3** — o que ele perdeu: o rival que discordava dele; sem o Archie ele erra mais e percebe menos.

**Antes da luta**

> Have you ever lost the one person who disagreed with you?
>
> I had a rival once. Loud, wet, impossible. We fought over the whole world, as if it were ours to divide.
>
> Without him, no one argues with me. I am wrong more often, and I notice it less.
>
> So. Argue with me. With Pokémon, if you please.

**Derrota**

> Hm. A convincing argument. He would have made it louder.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Intro3:
	.string "Have you ever lost the one person who\n"
	.string "disagreed with you?\p"
	.string "I had a rival once. Loud, wet, impossible.\n"
	.string "We fought over the whole world, as if it\l"
	.string "were ours to divide.\p"
	.string "Without him, no one argues with me. I am\n"
	.string "wrong more often, and I notice it less.\p"
	.string "So. Argue with me. With Pokémon, if you\n"
	.string "please.$"

Nexus_Text_Maxie_Defeat3:
	.string "Hm. A convincing argument. He would\n"
	.string "have made it louder.$"
```

</details>


### Diálogo associado ao lendário

#### Groudon

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Maxie_Groudon_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Maxie é o **campeão**, a luta logo antes do Groudon. A fala é sobre a criatura, sem dizer o nome dele.

O fragmento é o mundo que o Maxie pediu: só terra, até o horizonte. Anos atrás ele choraria de alegria. Agora ele vê os navios encalhados e pensa em quem estava a bordo. A virada: ele achou que a criatura era da humanidade porque era a terra, e ela só responde ao sol, que não tem opinião sobre gente. O Maxie aceita, pela primeira vez, errar na frente de alguém.

**Antes da luta**

> Do you see what it has done? Not an ocean left. Only land, to the horizon.
>
> Years ago I would have wept with joy at this sight.
>
> Now I see the ships, stranded, and I wonder who was aboard them.
>
> Come. Let me be wrong in front of you once more.

**Derrota**

> Hm. Correct again. You make a habit of it.

**Depois da luta**

> I called it the embodiment of the land. I thought that made it ours.
>
> It was never ours. It answers only the sun, and the sun has no opinion of people.
>
> Archie and I nearly learned that too late, in a cave beneath Sootopolis.
>
> Go. Remind it that land is where people stand, not what they own.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Groudon_ChampionIntro:
	.string "Do you see what it has done? Not an\n"
	.string "ocean left. Only land, to the horizon.\p"
	.string "Years ago I would have wept with joy at\n"
	.string "this sight.\p"
	.string "Now I see the ships, stranded, and I\n"
	.string "wonder who was aboard them.\p"
	.string "Come. Let me be wrong in front of you\n"
	.string "once more.$"

Nexus_Text_Maxie_Groudon_ChampionDefeat:
	.string "Hm. Correct again. You make a habit of\n"
	.string "it.$"

Nexus_Text_Maxie_Groudon_ChampionAfter:
	.string "{SPEAKER NAME_MAXIE}I called it the embodiment of the land.\n"
	.string "I thought that made it ours.\p"
	.string "It was never ours. It answers only the\n"
	.string "sun, and the sun has no opinion of\l"
	.string "people.\p"
	.string "Archie and I nearly learned that too\n"
	.string "late, in a cave beneath Sootopolis.\p"
	.string "Go. Remind it that land is where people\n"
	.string "stand, not what they own.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — dúvida: o mundo sem sombra que ele desenhou; a criatura deu exatamente o que ele pediu.

**Antes da luta**

> Feel that sun? There is no shade anywhere. Not a single shadow for a hundred kilometers.
>
> I once wrote that the ideal world would waste no space. No water where land could be.
>
> It seems I also designed a world with nowhere to rest.
>
> Come. Let us see which of us wilts first.

**Derrota**

> Hm. I wilted. The data is clear.

**Depois da luta**

> The ancient people of Hoenn prayed to that creature for sunlight. Just enough to ripen a harvest.
>
> I asked for all of it. Every ray, every hectare. I never asked what “enough” was.
>
> It gave me exactly what I asked for. That is the cruelest thing a god can do.
>
> Go. And when you pray for something, specify a quantity.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Groudon_ChampionIntro2:
	.string "Feel that sun? There is no shade\n"
	.string "anywhere. Not a single shadow for a\l"
	.string "hundred kilometers.\p"
	.string "I once wrote that the ideal world would\n"
	.string "waste no space. No water where land\l"
	.string "could be.\p"
	.string "It seems I also designed a world with\n"
	.string "nowhere to rest.\p"
	.string "Come. Let us see which of us wilts first.$"

Nexus_Text_Maxie_Groudon_ChampionDefeat2:
	.string "Hm. I wilted. The data is clear.$"

Nexus_Text_Maxie_Groudon_ChampionAfter2:
	.string "{SPEAKER NAME_MAXIE}The ancient people of Hoenn prayed to\n"
	.string "that creature for sunlight. Just\l"
	.string "enough to ripen a harvest.\p"
	.string "I asked for all of it. Every ray, every\n"
	.string "hectare. I never asked what “enough”\l"
	.string "was.\p"
	.string "It gave me exactly what I asked for.\n"
	.string "That is the cruelest thing a god can do.\p"
	.string "Go. And when you pray for something,\n"
	.string "specify a quantity.$"
```

</details>

**Variação 3** — lembrança da Red Orb (a marca na palma) e R21: o navio da Aqua encalhado que ele visita todo dia.

**Antes da luta**

> I held the orb that woke it. Red, warm, singing. It left a mark on my palm. You see?
>
> I thought the orb gave me control. It did not. It only made me the first thing the creature looked at.
>
> Being looked at by the land itself is… instructive.
>
> Come. Let me show you what I learned.

**Derrota**

> Hm. You learned faster.

**Depois da luta**

> One of those stranded ships belongs to Team Aqua. It dried where it stood when that creature took the sea.
>
> It is empty. Dry as bone. I walk out to it every day and check anyway.
>
> I call it scientific curiosity. It is not. I miss having someone to blame.
>
> Go. If you meet a loud man who smells of the sea, tell him the land won. And that I am sorry.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Groudon_ChampionIntro3:
	.string "I held the orb that woke it. Red, warm,\n"
	.string "singing. It left a mark on my palm. You\l"
	.string "see?\p"
	.string "I thought the orb gave me control. It\n"
	.string "did not. It only made me the first thing\l"
	.string "the creature looked at.\p"
	.string "Being looked at by the land itself is…\n"
	.string "instructive.\p"
	.string "Come. Let me show you what I learned.$"

Nexus_Text_Maxie_Groudon_ChampionDefeat3:
	.string "Hm. You learned faster.$"

Nexus_Text_Maxie_Groudon_ChampionAfter3:
	.string "{SPEAKER NAME_MAXIE}One of those stranded ships belongs to\n"
	.string "Team Aqua. It dried where it stood when\l"
	.string "that creature took the sea.\p"
	.string "It is empty. Dry as bone. I walk out to\n"
	.string "it every day and check anyway.\p"
	.string "I call it scientific curiosity. It is not.\n"
	.string "I miss having someone to blame.\p"
	.string "Go. If you meet a loud man who smells of\n"
	.string "the sea, tell him the land won. And that\l"
	.string "I am sorry.$"
```

</details>


#### Landorus

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Maxie_Landorus_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Maxie é o **campeão**, a luta logo antes do Landorus. A fala é sobre a criatura, sem dizer o nome dele.

A criatura é o que o Maxie prometia à Team Magma: terra que alimenta o mundo. E a colheita apodrece no pé, porque não há ninguém. A virada é o cálculo que ele nunca fez: passou anos calculando quanta terra a humanidade precisa e nunca quantas pessoas são precisas para cuidar dela. Abundância sem ninguém é só um silêncio maior.

**Antes da luta**

> Wheat, as far as the eye can see. Heavy, golden, and not a single hand to gather it.
>
> That one on the cloud blesses every field it passes.
>
> It is everything I promised Team Magma. Land that feeds the world.
>
> And it is rotting on the stalk. Come.

**Derrota**

> Hm. Another harvest I do not get to keep.

**Depois da luta**

> I spent years calculating how much land humanity needs.
>
> I never once calculated how many people it takes to tend it.
>
> Abundance with no one to share it is only a larger silence.
>
> Go on. Let it bless one field that someone will actually harvest.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Landorus_ChampionIntro:
	.string "Wheat, as far as the eye can see.\n"
	.string "Heavy, golden, and not a single hand to\l"
	.string "gather it.\p"
	.string "That one on the cloud blesses every\n"
	.string "field it passes.\p"
	.string "It is everything I promised Team\n"
	.string "Magma. Land that feeds the world.\p"
	.string "And it is rotting on the stalk. Come.$"

Nexus_Text_Maxie_Landorus_ChampionDefeat:
	.string "Hm. Another harvest I do not get to\n"
	.string "keep.$"

Nexus_Text_Maxie_Landorus_ChampionAfter:
	.string "{SPEAKER NAME_MAXIE}I spent years calculating how much\n"
	.string "land humanity needs.\p"
	.string "I never once calculated how many\n"
	.string "people it takes to tend it.\p"
	.string "Abundance with no one to share it is\n"
	.string "only a larger silence.\p"
	.string "Go on. Let it bless one field that\n"
	.string "someone will actually harvest.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — lore de Unova: a criatura castiga os dois irmãos da tempestade; o Maxie e o Archie eram esses irmãos.

**Antes da luta**

> Did you hear it laughing, up on its cloud? Like thunder rolling over the hills.
>
> In Unova they say it punishes two brothers who wreck the fields with wind and lightning.
>
> Two brothers making a mess of the world, until something bigger steps in. The story is uncomfortably familiar.
>
> Come.

**Derrota**

> Hm. Punished. I suppose I had it coming.

**Depois da luta**

> Archie and I were those brothers. Sea and land, and a whole world caught in between.
>
> No one stepped in for us. We had to stop ourselves, and very nearly did not.
>
> That one on the cloud keeps the fields safe from fools like us.
>
> Go. And be kind to whoever keeps your fields.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Landorus_ChampionIntro2:
	.string "Did you hear it laughing, up on its\n"
	.string "cloud? Like thunder rolling over the\l"
	.string "hills.\p"
	.string "In Unova they say it punishes two\n"
	.string "brothers who wreck the fields with wind\l"
	.string "and lightning.\p"
	.string "Two brothers making a mess of the\n"
	.string "world, until something bigger steps in.\l"
	.string "The story is uncomfortably familiar.\p"
	.string "Come.$"

Nexus_Text_Maxie_Landorus_ChampionDefeat2:
	.string "Hm. Punished. I suppose I had it coming.$"

Nexus_Text_Maxie_Landorus_ChampionAfter2:
	.string "{SPEAKER NAME_MAXIE}Archie and I were those brothers. Sea\n"
	.string "and land, and a whole world caught in\l"
	.string "between.\p"
	.string "No one stepped in for us. We had to stop\n"
	.string "ourselves, and very nearly did not.\p"
	.string "That one on the cloud keeps the fields\n"
	.string "safe from fools like us.\p"
	.string "Go. And be kind to whoever keeps your\n"
	.string "fields.$"
```

</details>

**Variação 3** — humor e mudança: o cientista pegou uma foice; uma fileira de trigo, mãos em bolha, o primeiro trabalho honesto.

**Antes da luta**

> You will not believe this. Yesterday I picked up a scythe.
>
> One man, one field. I calculated it would take me four hundred years to bring it all in.
>
> I did one row. My hands have never hurt so much in my life.
>
> It was, I think, the first honest work I have ever done. Come.

**Derrota**

> Hm. My hands are too sore to argue.

**Depois da luta**

> That creature gives, and gives, and never asks who will do the gathering.
>
> I used to think abundance was the answer. It is only the question.
>
> The answer is people. Tired, blistered, arguing people, bringing it in together.
>
> Go. I have another row to do.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Maxie_Landorus_ChampionIntro3:
	.string "You will not believe this. Yesterday I\n"
	.string "picked up a scythe.\p"
	.string "One man, one field. I calculated it would\n"
	.string "take me four hundred years to bring it\l"
	.string "all in.\p"
	.string "I did one row. My hands have never hurt\n"
	.string "so much in my life.\p"
	.string "It was, I think, the first honest work I\n"
	.string "have ever done. Come.$"

Nexus_Text_Maxie_Landorus_ChampionDefeat3:
	.string "Hm. My hands are too sore to argue.$"

Nexus_Text_Maxie_Landorus_ChampionAfter3:
	.string "{SPEAKER NAME_MAXIE}That creature gives, and gives, and\n"
	.string "never asks who will do the gathering.\p"
	.string "I used to think abundance was the\n"
	.string "answer. It is only the question.\p"
	.string "The answer is people. Tired, blistered,\n"
	.string "arguing people, bringing it in together.\p"
	.string "Go. I have another row to do.$"
```

</details>


Falante novo: `SP_NAME_MAXIE` (ainda não existe em `include/constants/speaker_names.h`).
