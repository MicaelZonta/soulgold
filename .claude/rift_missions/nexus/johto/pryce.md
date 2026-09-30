# Pryce

**Região da ficha:** Johto

Aparece no checklist como:

- **Pryce — Gelo** (Johto · Líderes de Ginásio) — treinador veterano e experiente de Mahogany.

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
| `OBJ_EVENT_GFX_PRYCE` | `graphics/object_events/pics/people/gym_leaders/pryce.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_PRYCE` | `graphics/trainers/front_pics/leader_pryce.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_PRYCE` | `graphics/field_mugshots/pryce.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PRYCE_2` | 244 | 0x5F4 | Ninetales-Alola Lv79, Lapras Lv81, Cloyster Lv80, Weavile Lv80, Darmanitan-Galar Lv80, Baxcalibur Lv81 · *dupla* | `KitakamiRoad_House`, `LakeOfRage`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_PRYCE_1` | 546 | 0x722 | Ninetales-Alola Lv42, Darmanitan-Galar Lv42, Mamoswine Lv42, Glaceon Lv42, Weavile Lv42, Froslass Lv42 · *dupla* · VS: Green | `MahoganyTown_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_PRYCE_1_2` | 578 | 0x742 | Darmanitan-Galar Lv45, Ninetales-Alola Lv45, Mamoswine Lv45, Glaceon Lv45, Weavile Lv45, Froslass Lv46 · *dupla* · VS: Green | `MahoganyTown_Gym` |
| `TRAINER_PRYCE_1_3` | 707 | 0x7C3 | Darmanitan-Galar Lv48, Ninetales-Alola Lv48, Mamoswine Lv48, Glaceon Lv48, Weavile Lv48, Froslass Lv49 · *dupla* · VS: Green | `MahoganyTown_Gym` |
| `TRAINER_TITLE_DEFENSE_PRYCE` | 897 | 0x881 | Ninetales-Alola Lv85, Lapras Lv85, Cloyster Lv85, Kyurem Lv85, Darmanitan-Galar Lv85, Baxcalibur Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_PRYCE` = **1007** (flag de batalha `0x8EF`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Pryce_Fight`; campeão: `Nexus_EventScript_Pryce_Articuno_ChampionFight` (para Articuno), `Nexus_EventScript_Pryce_Glastrier_ChampionFight` (para Glastrier). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Pryce.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_PRYCE`, campeão do Articuno e do Glastrier. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Calyrex** montado no **Glastrier** (`Calyrex-Ice`, As One): o rei da colheita no cavalo de gelo de que ele é campeão; o Calyrex-Ice conta como o lendário e leva o Glastrier junto, sem ocupar a vaga de semi. Semi-lendário **Articuno**, a ave do gelo que aparece a quem se perde na montanha (ele é campeão dela). Mega **Abomasnow** (Icetite), que traz a neve (Snow Warning) e faz o Blizzard não errar. Mais **Mamoswine**, a linha do Piloswine, ás dele desde Gold/Silver, Ninetales de Alola e Lapras, dos times de revanche e Title Defense. Um velho, gelo e **Trick Room**: o time é lento de propósito.

*Plano (Singles):* a Ninetales põe neve e Aurora Veil, o Mamoswine arma Stealth Rock, o Calyrex-Ice arma Trick Room atrás do Veil e, com ele, Calyrex, Mamoswine, Abomasnow e Lapras batem primeiro; o Articuno segura com Roost e Haze. *Plano (Doubles):* neve e Aurora Veil no turno 1, Trick Room do Calyrex com Protect no parceiro, e depois Glacial Lance e Blizzard nos dois alvos. Sem Trick Room, a neve e o Veil ainda deixam o time de pé.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Calyrex-Ice | Leftovers | As One Ice Rider | Brave | Glacial Lance, High Horsepower, Trick Room, Protect |
| Articuno | Heavy-Duty Boots | Pressure | Modest | Blizzard, Hurricane, Roost, Haze |
| Abomasnow | Icetite | Snow Warning | Quiet | Blizzard, Giga Drain, Earth Power, Protect |
| Mamoswine | Life Orb | Thick Fat | Adamant | Icicle Crash, High Horsepower, Ice Shard, Stealth Rock |
| Ninetales-Alola | Light Clay | Snow Warning | Timid | Aurora Veil, Blizzard, Moonblast, Encore |
| Lapras | Leftovers | Water Absorb | Quiet | Hydro Pump, Freeze-Dry, Thunderbolt, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_PRYCE ===
Name: Pryce
Class: Leader
Pic: Leader Pryce
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Calyrex-Ice @ Leftovers
Brave Nature
Level: 100
Ability: As One Ice Rider
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Glacial Lance
- High Horsepower
- Trick Room
- Protect

Articuno @ Heavy-Duty Boots
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Hurricane
- Roost
- Haze

Abomasnow @ Icetite
Quiet Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Giga Drain
- Earth Power
- Protect

Mamoswine @ Life Orb
Adamant Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Crash
- High Horsepower
- Ice Shard
- Stealth Rock

Ninetales-Alola @ Light Clay
Timid Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Aurora Veil
- Blizzard
- Moonblast
- Encore

Lapras @ Leftovers
Quiet Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Freeze-Dry
- Thunderbolt
- Protect
```

</details>

### Lendário associado

#### Articuno

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Articuno_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Articuno**. Pryce é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Pryce, Líder de Mahogany, o treinador mais velho de Johto, que diz ter visto e sofrido muito na vida.

**A criatura.** Articuno, a ave lendária do gelo. Congela a umidade do ar para fazer nevascas, e diz a lenda que aparece para viajantes perdidos nas montanhas geladas.

**O fragmento.** Uma passagem de montanha numa nevasca que parou de se mexer: cada floco suspenso no ar. Pegadas antigas sobem a encosta e terminam, uma a uma, no meio do nada.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A mountain pass in a blizzard, except the blizzard had stopped moving.
>
> Every snowflake hung in the air. Old footprints ran up the slope and ended, one by one, in the middle of nowhere.

**Boss**

> The snowflakes began to fall again, all at once.
>
> A long blue tail swept through them, and the air turned so cold it rang.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-144. Freeze.
>
> A pass where travelers stop walking, and an old man who walked it anyway, slowly, and did not stop.
>
> What you brought back is cold to the touch. It has no intention of melting.
>
> He said the cold was an old friend. I have written that down, and then sat with it for a while.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Articuno_Arrival:
	.string "A mountain pass in a blizzard, except\n"
	.string "the blizzard had stopped moving.\p"
	.string "Every snowflake hung in the air. Old\n"
	.string "footprints ran up the slope and ended,\l"
	.string "one by one, in the middle of nowhere.$"

Nexus_Text_Articuno_Boss:
	.string "The snowflakes began to fall again, all\n"
	.string "at once.\p"
	.string "A long blue tail swept through them,\n"
	.string "and the air turned so cold it rang.$"

Nexus_Text_Articuno_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-144. Freeze.\p"
	.string "A pass where travelers stop walking,\n"
	.string "and an old man who walked it anyway,\l"
	.string "slowly, and did not stop.\p"
	.string "What you brought back is cold to the\n"
	.string "touch. It has no intention of melting.\p"
	.string "He said the cold was an old friend. I\n"
	.string "have written that down, and then sat\l"
	.string "with it for a while.$"
```

</details>

#### Glastrier

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Glastrier_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Glastrier**. Pryce é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Pryce, o mesmo, diante de uma criatura que é o contrário da paciência dele.

**A criatura.** Glastrier, o cavalo de gelo de Galar, montaria do Calyrex. Usa uma máscara de gelo, solta um frio intenso pelos cascos e é belicoso: o que quer, toma à força.

**O fragmento.** Um campo de colheita congelado. O trigo virou gelo e toca como sinos quando se encosta nele, e o atravessam pegadas de cascos, cada uma uma pequena cratera de geada.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A harvest field, frozen solid. The wheat had turned to ice and rang like bells when you touched it.
>
> Hoofprints crossed it, each one a small crater of frost.

**Boss**

> The field went white under a single stamp.
>
> It wore a mask of ice and breathed out winter, and it wanted the field you were standing on.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-896. Wild Horse.
>
> A harvest nobody will eat, and an old man who knew exactly how long the field had been frozen.
>
> What you brought back stamps its foot at me. I have decided to allow it.
>
> He did not say how long. He only said spring is always later than you think.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Glastrier_Arrival:
	.string "A harvest field, frozen solid. The\n"
	.string "wheat had turned to ice and rang like\l"
	.string "bells when you touched it.\p"
	.string "Hoofprints crossed it, each one a\n"
	.string "small crater of frost.$"

Nexus_Text_Glastrier_Boss:
	.string "The field went white under a single\n"
	.string "stamp.\p"
	.string "It wore a mask of ice and breathed out\n"
	.string "winter, and it wanted the field you\l"
	.string "were standing on.$"

Nexus_Text_Glastrier_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-896. Wild Horse.\p"
	.string "A harvest nobody will eat, and an old\n"
	.string "man who knew exactly how long the\l"
	.string "field had been frozen.\p"
	.string "What you brought back stamps its foot\n"
	.string "at me. I have decided to allow it.\p"
	.string "He did not say how long. He only said\n"
	.string "spring is always later than you think.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Pryce_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Pryce cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hm. Another young one.
>
> I have been with Pokémon since before you were born. Ice teaches you to be patient.
>
> Most young people run out of patience before I run out of ice. Let us see about you.

**Derrota**

> Hmph. The ice has cracked. It does that, eventually.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Intro:
	.string "Hm. Another young one.\p"
	.string "I have been with Pokémon since before\n"
	.string "you were born. Ice teaches you to be\l"
	.string "patient.\p"
	.string "Most young people run out of patience\n"
	.string "before I run out of ice. Let us see\l"
	.string "about you.$"

Nexus_Text_Pryce_Defeat:
	.string "Hmph. The ice has cracked. It does\n"
	.string "that, eventually.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas para as **quatro primeiras salas** ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. A variação 1 é a de cima, que já está no jogo; o sorteio de qual variação toca ainda não existe no código.

**Variação 2** — humor de velho: os joelhos avisaram que o jogador vinha. Na idade dele toda luta pode ser a última boa, então ele não gasta tempo com cortesia.

**Antes da luta**

> Hm. My knees told me you were coming. They are rarely wrong about the weather, either.
>
> At my age, every battle might be the last good one. So I do not waste them on being polite.
>
> Come. Make it a good one.

**Derrota**

> Hmph. It was a good one. My knees will complain about it tomorrow.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Intro2:
	.string "Hm. My knees told me you were coming.\n"
	.string "They are rarely wrong about the\l"
	.string "weather, either.\p"
	.string "At my age, every battle might be the\n"
	.string "last good one. So I do not waste them on\l"
	.string "being polite.\p"
	.string "Come. Make it a good one.$"

Nexus_Text_Pryce_Defeat2:
	.string "Hmph. It was a good one. My knees will\n"
	.string "complain about it tomorrow.$"
```

</details>

**Variação 3** — a máscara de gelo. Em outro inverno ele usou uma (o Homem Mascarado de Pokémon Adventures) para não ver o que tinha perdido. R21: o jogador pode ou não conhecer essa história.

**Antes da luta**

> You are looking at my face as if you expected a mask. Hm. You would not be the first.
>
> In another winter I wore one, made of ice. I told myself it was to hide from the world.
>
> It was to hide from what I had lost. …Enough of that. Begin.

**Derrota**

> Hm. Some ice does not crack. It only waits for spring. Well done.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Intro3:
	.string "You are looking at my face as if you\n"
	.string "expected a mask. Hm. You would not be\l"
	.string "the first.\p"
	.string "In another winter I wore one, made of\n"
	.string "ice. I told myself it was to hide from\l"
	.string "the world.\p"
	.string "It was to hide from what I had lost.\n"
	.string "…Enough of that. Begin.$"

Nexus_Text_Pryce_Defeat3:
	.string "Hm. Some ice does not crack. It only\n"
	.string "waits for spring. Well done.$"
```

</details>

### Diálogo associado ao lendário

#### Articuno

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Pryce_Articuno_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Pryce é o **campeão**, a luta logo antes do Articuno. A fala é sobre a criatura, sem dizer o nome dela.

Dizem que a ave da passagem aparece para quem não vai voltar para casa, e ela apareceu para o Pryce de manhã. Ele não se assusta: viu e sofreu muito na vida, um pouco de frio não o assusta. A derrota vira a frase dele: "então você é quem vai voltar para casa". A virada é a correção da lenda: ela não vem pelos que estão morrendo, vem pelos perdidos. As pegadas na encosta terminam porque quem andava parou, não porque ela os levou. Continue andando, que é tudo o que o gelo pede.

**Antes da luta**

> They say the bird of this pass shows itself to travelers who will not make it home.
>
> It showed itself to me this morning. ...Don't look so worried, child.
>
> I have seen and suffered much in my life. A little cold does not frighten me. Show me what you have.

**Derrota**

> Hm. So you are the one who will make it home.

**Depois da luta**

> I have walked in snow longer than your parents have been alive.
>
> I thought it came for the dying. It doesn't. It comes for the lost.
>
> Those footprints on the slope ended because the walkers stopped. Not because it took them.
>
> Keep walking when you face it. That is all the ice ever asks.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Articuno_ChampionIntro:
	.string "They say the bird of this pass shows\n"
	.string "itself to travelers who will not make\l"
	.string "it home.\p"
	.string "It showed itself to me this morning.\n"
	.string "...Don't look so worried, child.\p"
	.string "I have seen and suffered much in my\n"
	.string "life. A little cold does not frighten\l"
	.string "me. Show me what you have.$"

Nexus_Text_Pryce_Articuno_ChampionDefeat:
	.string "Hm. So you are the one who will make\n"
	.string "it home.$"

Nexus_Text_Pryce_Articuno_ChampionAfter:
	.string "{SPEAKER NAME_PRYCE}I have walked in snow longer than your\n"
	.string "parents have been alive.\p"
	.string "I thought it came for the dying. It\n"
	.string "doesn't. It comes for the lost.\p"
	.string "Those footprints on the slope ended\n"
	.string "because the walkers stopped. Not\l"
	.string "because it took them.\p"
	.string "Keep walking when you face it. That is\n"
	.string "all the ice ever asks.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — a lembrança de menino: perdido numa nevasca acima de Mahogany, gritou com a ave e ela voou de volta pelo caminho de onde ele veio. Ele seguiu. Sessenta anos pensando se foi de propósito.

**Antes da luta**

> I saw that bird once before. I was younger than you, and lost in a snowstorm above Mahogany.
>
> I thought it had come to take me. So I shouted at it. A small boy, shouting at a legend.
>
> It turned and flew back the way I had come. I followed. Hm. Your turn to follow.

**Derrota**

> Hm. You follow well.

**Depois da luta**

> For sixty years I have wondered if it led me home on purpose, or simply went home itself.
>
> I have decided it does not matter. I got home.
>
> When you face it, watch which way it flies. Then do not be too proud to follow.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Articuno_ChampionIntro2:
	.string "I saw that bird once before. I was\n"
	.string "younger than you, and lost in a\l"
	.string "snowstorm above Mahogany.\p"
	.string "I thought it had come to take me. So I\n"
	.string "shouted at it. A small boy, shouting at a\l"
	.string "legend.\p"
	.string "It turned and flew back the way I had\n"
	.string "come. I followed. Hm. Your turn to\l"
	.string "follow.$"

Nexus_Text_Pryce_Articuno_ChampionDefeat2:
	.string "Hm. You follow well.$"

Nexus_Text_Pryce_Articuno_ChampionAfter2:
	.string "{SPEAKER NAME_PRYCE}For sixty years I have wondered if it\n"
	.string "led me home on purpose, or simply went\l"
	.string "home itself.\p"
	.string "I have decided it does not matter. I got\n"
	.string "home.\p"
	.string "When you face it, watch which way it\n"
	.string "flies. Then do not be too proud to\l"
	.string "follow.$"
```

</details>

**Variação 3** — o medo de velho: a ave não olhou para ele hoje nenhuma vez. Ou ele não está mais perdido, ou está perdido demais para ser achado. A derrota responde.

**Antes da luta**

> Let me tell you what frightens an old man. Not the cold. Not losing.
>
> It is that the bird of this pass has not looked at me once today. Not once.
>
> Either I am no longer lost… or I am too lost to find. Help me work out which.

**Derrota**

> Hm. Not lost, then. Only beaten.

**Depois da luta**

> When you go, it will look at you. Everyone gets looked at once.
>
> Do not look away. I did, the first time, and I have regretted it for a long while.
>
> …Go. And close the door behind you. There is a draft.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Articuno_ChampionIntro3:
	.string "Let me tell you what frightens an old\n"
	.string "man. Not the cold. Not losing.\p"
	.string "It is that the bird of this pass has not\n"
	.string "looked at me once today. Not once.\p"
	.string "Either I am no longer lost… or I am too\n"
	.string "lost to find. Help me work out which.$"

Nexus_Text_Pryce_Articuno_ChampionDefeat3:
	.string "Hm. Not lost, then. Only beaten.$"

Nexus_Text_Pryce_Articuno_ChampionAfter3:
	.string "{SPEAKER NAME_PRYCE}When you go, it will look at you.\n"
	.string "Everyone gets looked at once.\p"
	.string "Do not look away. I did, the first time,\n"
	.string "and I have regretted it for a long while.\p"
	.string "…Go. And close the door behind you.\n"
	.string "There is a draft.$"
```

</details>

#### Glastrier

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Pryce_Glastrier_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Pryce é o **campeão**, a luta logo antes do Glastrier. A fala é sobre a criatura, sem dizer o nome dela.

O cavalo toma o que quer à força, e tomou a colheita inteira. O gelo não funciona assim: o gelo espera, tem todo o tempo do mundo. O Pryce quer saber qual dos dois tem razão, e perde para uma criança (força e paciência perderam juntas). A virada está nas costas do cavalo: um lugar gasto para um cavaleiro que não está lá. Ele toma e toma porque não tem ninguém para mandar parar. O Pryce sabe alguma coisa sobre esperar quem não volta.

**Antes da luta**

> The horse of this field takes whatever it wants. By force. It has taken this whole harvest.
>
> Ice does not work that way. Ice waits. It has all the time in the world.
>
> ...I wonder which of us is right. You will do, as a question.

**Derrota**

> Hm. Force and patience both lost. To a child. Wonderful.

**Depois da luta**

> Look at its back. There is a place there for a rider, worn smooth.
>
> It takes and takes because no one is there to tell it to stop.
>
> I know something of waiting for someone who does not come back. ...Go on. Be gentle with it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Glastrier_ChampionIntro:
	.string "The horse of this field takes whatever\n"
	.string "it wants. By force. It has taken this\l"
	.string "whole harvest.\p"
	.string "Ice does not work that way. Ice waits.\n"
	.string "It has all the time in the world.\p"
	.string "...I wonder which of us is right. You\n"
	.string "will do, as a question.$"

Nexus_Text_Pryce_Glastrier_ChampionDefeat:
	.string "Hm. Force and patience both lost. To\n"
	.string "a child. Wonderful.$"

Nexus_Text_Pryce_Glastrier_ChampionAfter:
	.string "{SPEAKER NAME_PRYCE}Look at its back. There is a place\n"
	.string "there for a rider, worn smooth.\p"
	.string "It takes and takes because no one is\n"
	.string "there to tell it to stop.\p"
	.string "I know something of waiting for\n"
	.string "someone who does not come back.\l"
	.string "...Go on. Be gentle with it.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — humor: o Piloswine dele e o cavalo se encaram desde o amanhecer, dois teimosos que não se mexem primeiro. O Pryce é o terceiro teimoso.

**Antes da luta**

> My Piloswine and that horse have been staring at each other since dawn.
>
> Two stubborn creatures, neither willing to move first. I have seen marriages like that.
>
> …I am the third stubborn creature here. Let us see who blinks.

**Derrota**

> Hm. The child blinked last. Remarkable.

**Depois da luta**

> The horse stamped. My Piloswine stamped back. Neither has moved an inch since.
>
> Force does not listen. Patience does not talk. Somebody has to say something first.
>
> …You say it. You are young. You still believe it helps.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Glastrier_ChampionIntro2:
	.string "My Piloswine and that horse have been\n"
	.string "staring at each other since dawn.\p"
	.string "Two stubborn creatures, neither willing\n"
	.string "to move first. I have seen marriages\l"
	.string "like that.\p"
	.string "…I am the third stubborn creature here.\n"
	.string "Let us see who blinks.$"

Nexus_Text_Pryce_Glastrier_ChampionDefeat2:
	.string "Hm. The child blinked last. Remarkable.$"

Nexus_Text_Pryce_Glastrier_ChampionAfter2:
	.string "{SPEAKER NAME_PRYCE}The horse stamped. My Piloswine\n"
	.string "stamped back. Neither has moved an inch\l"
	.string "since.\p"
	.string "Force does not listen. Patience does\n"
	.string "not talk. Somebody has to say\l"
	.string "something first.\p"
	.string "…You say it. You are young. You still\n"
	.string "believe it helps.$"
```

</details>

**Variação 3** — o cavaleiro: o Pryce ouviu que o dono do cavalo era um rei pequeno que faz os campos crescerem. Disse ao cavalo que o rei está em outra história, com um homem de máscara (o **Will**). Fio do diário.

**Antes da luta**

> I have heard the rider of that horse was a king. A small king, who made things grow.
>
> A beast that freezes every field it crosses, carrying a king who makes fields grow.
>
> …They must have argued constantly. I understand horses better than kings. Begin.

**Derrota**

> Hm. Beaten by someone half the size of the argument.

**Depois da luta**

> I told the horse its king is somewhere else. In another story, with a man in a mask.
>
> It stamped so hard the whole field rang. I believe that meant 'where.'
>
> I do not know where. Neither will you. But go and tell it someone is still looking.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Pryce_Glastrier_ChampionIntro3:
	.string "I have heard the rider of that horse\n"
	.string "was a king. A small king, who made things\l"
	.string "grow.\p"
	.string "A beast that freezes every field it\n"
	.string "crosses, carrying a king who makes\l"
	.string "fields grow.\p"
	.string "…They must have argued constantly. I\n"
	.string "understand horses better than kings.\l"
	.string "Begin.$"

Nexus_Text_Pryce_Glastrier_ChampionDefeat3:
	.string "Hm. Beaten by someone half the size of\n"
	.string "the argument.$"

Nexus_Text_Pryce_Glastrier_ChampionAfter3:
	.string "{SPEAKER NAME_PRYCE}I told the horse its king is somewhere\n"
	.string "else. In another story, with a man in a\l"
	.string "mask.\p"
	.string "It stamped so hard the whole field rang.\n"
	.string "I believe that meant 'where.'\p"
	.string "I do not know where. Neither will you.\n"
	.string "But go and tell it someone is still\l"
	.string "looking.$"
```

</details>
