# Falkner

**Região da ficha:** Johto

Aparece no checklist como:

- **Falkner — Voador** (Johto · Líderes de Ginásio) — jovem Líder de Violet que herdou os Pokémon de seu pai.

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
| `OBJ_EVENT_GFX_FALKNER` | `graphics/object_events/pics/people/gym_leaders/falkner.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_FALKNER` | `graphics/trainers/front_pics/leader_falkner.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_FALKNER` | `graphics/field_mugshots/falkner.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_FALKNER_1` | 19 | 0x513 | Rufflet Lv12, Noibat Lv12, Gligar Lv13, Pidgeotto Lv13 · *dupla* · VS: Blue | `VioletCity_Gym`, `src/data/level_scaling_rules.h` |
| `TRAINER_FALKNER_2` | 26 | 0x51A | Salamence Lv78, Flamigo Lv78, Braviary Lv78, Corviknight Lv78, Honchkrow Lv78, Gliscor Lv78 · *dupla* | `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `VioletCity_TrainerSchool`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_FALKNER` | 891 | 0x87B | Salamence Lv85, Flamigo Lv85, Landorus Therian Lv85, Corviknight Lv85, Honchkrow Lv85, Gliscor Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_FALKNER` = **1001** (flag de batalha `0x8E9`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Falkner_Fight`; campeão: `Nexus_EventScript_Falkner_ChampionFight` (para Tornadus). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Falkner.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_FALKNER`, campeão do Tornadus. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Lugia**, a ave que guarda os mares e cujo bater de asas vira tempestade: o maior pássaro de Johto no time do homem que jura que pássaro não é fraco. Semi-lendário **Tornadus**, o dono do vento de cauda (Prankster Tailwind). Mega **Pidgeot** (Flyingite, No Guard): a linha do Pidgeotto que o Falkner herdou do pai e que é o ás dele desde Gold/Silver. Mais Corviknight, Gliscor e Honchkrow, do time dele na revanche e na Title Defense. **Todo o time voa** (o Gliscor é Terra/Voador), então o Earthquake do Gliscor não acerta ninguém do próprio lado.

*Plano (Singles):* o Gliscor põe Stealth Rock e se cura com Poison Heal, o Tornadus usa Taunt e Tailwind com prioridade, o Corviknight faz pivot com U-turn, a Lugia sobe Calm Mind atrás da Multiscale e a Mega Pidgeot fecha com Hurricane que não erra. *Plano (Doubles):* Tailwind de Prankster no turno 1, Bleakwind Storm e Heat Wave nos dois alvos, e o Earthquake do Gliscor livre porque o parceiro sempre voa. O risco do time é Pedra, Gelo e Elétrico; o Corviknight (Mirror Armor) e a Lugia seguram o que dá.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Lugia | Leftovers | Multiscale | Timid | Aeroblast, Ice Beam, Calm Mind, Roost |
| Tornadus | Focus Sash | Prankster | Timid | Tailwind, Bleakwind Storm, Heat Wave, Taunt |
| Pidgeot | Flyingite | Big Pecks | Timid | Hurricane, Heat Wave, U-turn, Roost |
| Corviknight | Rocky Helmet | Mirror Armor | Impish | Brave Bird, Body Press, U-turn, Roost |
| Gliscor | Toxic Orb | Poison Heal | Impish | Earthquake, Knock Off, Stealth Rock, Protect |
| Honchkrow | Life Orb | Super Luck | Adamant | Brave Bird, Sucker Punch, Night Slash, Superpower |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_FALKNER ===
Name: Falkner
Class: Leader
Pic: Leader Falkner
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Lugia @ Leftovers
Timid Nature
Level: 100
Ability: Multiscale
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Aeroblast
- Ice Beam
- Calm Mind
- Roost

Tornadus @ Focus Sash
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Bleakwind Storm
- Heat Wave
- Taunt

Pidgeot @ Flyingite
Timid Nature
Level: 100
Ability: Big Pecks
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Heat Wave
- U-turn
- Roost

Corviknight @ Rocky Helmet
Impish Nature
Level: 100
Ability: Mirror Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Body Press
- U-turn
- Roost

Gliscor @ Toxic Orb
Impish Nature
Level: 100
Ability: Poison Heal
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earthquake
- Knock Off
- Stealth Rock
- Protect

Honchkrow @ Life Orb
Adamant Nature
Level: 100
Ability: Super Luck
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Sucker Punch
- Night Slash
- Superpower
```

</details>

### Lendário associado

#### Tornadus

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Tornadus_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Tornadus**. Falkner é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Falkner, Líder de Violet, que herdou o ginásio e os pássaros do pai e passou a vida ouvindo que Pokémon Voador cai com um choque elétrico.

**A criatura.** Tornadus, do trio das Forças da Natureza de Unova (com Thundurus e Landorus). A parte de baixo do corpo é envolta numa nuvem; voa a mais de 300 km/h levantando ventanias que derrubam casas. O Reveal Glass mostra a forma Therian.

**O fragmento.** Um céu sem chão. Telhados arrancados de cidades inteiras giram devagar no vento, como folhas que se recusam a cair, e o caminho é uma fila de telhas soltas que só o vento segura.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Roofs. Hundreds of them, torn off whole towns and turning slowly in the air, like leaves that refuse to fall.
>
> The path was a line of loose tiles, held up by nothing but the wind.

**Boss**

> The wind stopped pushing and started pulling.
>
> Something rode down on a cloud, laughing, and every roof in the sky turned to face it.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-641. Whirlwind.
>
> A sky full of stolen roofs, and a young man who fought under it without once looking down.
>
> What you carried back is only a gust of it. It still tugs at my hat.
>
> He says his father's birds never look down either. I have written that down as a family trait.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Tornadus_Arrival:
	.string "Roofs. Hundreds of them, torn off\n"
	.string "whole towns and turning slowly in the\l"
	.string "air, like leaves that refuse to fall.\p"
	.string "The path was a line of loose tiles,\n"
	.string "held up by nothing but the wind.$"

Nexus_Text_Tornadus_Boss:
	.string "The wind stopped pushing and started\n"
	.string "pulling.\p"
	.string "Something rode down on a cloud,\n"
	.string "laughing, and every roof in the sky\l"
	.string "turned to face it.$"

Nexus_Text_Tornadus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-641. Whirlwind.\p"
	.string "A sky full of stolen roofs, and a young\n"
	.string "man who fought under it without once\l"
	.string "looking down.\p"
	.string "What you carried back is only a gust\n"
	.string "of it. It still tugs at my hat.\p"
	.string "He says his father's birds never look\n"
	.string "down either. I have written that down\l"
	.string "as a family trait.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Falkner_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Falkner cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> People say you can ground a bird Pokémon with one jolt of electricity.
>
> I've heard it since I was a boy, with my father's Pidgeotto on my arm.
>
> He never argued with them. He just flew. So will I!

**Derrota**

> ...Grounded. Don't tell my father.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Falkner_Intro:
	.string "People say you can ground a bird\n"
	.string "Pokémon with one jolt of electricity.\p"
	.string "I've heard it since I was a boy, with\n"
	.string "my father's Pidgeotto on my arm.\p"
	.string "He never argued with them. He just\n"
	.string "flew. So will I!$"

Nexus_Text_Falkner_Defeat:
	.string "...Grounded. Don't tell my father.$"
```

</details>

### Diálogo associado ao lendário

#### Tornadus

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Falkner_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Falkner é o **campeão**, a luta logo antes do Tornadus. A fala é sobre a criatura, sem dizer o nome dela.

O Falkner vê uma criatura que é vento sem destino: arranca telhados só para vê-los voar e nunca pousou na vida. Por um segundo ele sente inveja, e é por isso que luta: para lembrar por que não. A lição do pai era que todo voo precisa de um lugar para pousar. O que fica: os pássaros dele voltam ao mesmo poleiro de Violet toda noite, e ele sempre achou que isso os fazia menos livres; agora acha que é isso que os faz dele.

**Antes da luta**

> Did you see the roofs? It tore them off just to watch them fly.
>
> My father taught me that every flight needs a place to land. A branch. A perch. An arm.
>
> That thing up there has never landed in its life. And for a second... I envied it.
>
> That's why I'm fighting you. To remember why I don't!

**Derrota**

> You stayed on the ground and still won. That's a new one.

**Depois da luta**

> It flies faster than anything I've ever raised. But it has nowhere to go back to.
>
> My birds all come back to the same perch in Violet every night.
>
> I always thought that made them less free. Now I think it makes them mine.
>
> Go on. Knock it out of the sky. Then give it somewhere to land.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Falkner_ChampionIntro:
	.string "Did you see the roofs? It tore them off\n"
	.string "just to watch them fly.\p"
	.string "My father taught me that every flight\n"
	.string "needs a place to land. A branch. A\l"
	.string "perch. An arm.\p"
	.string "That thing up there has never landed\n"
	.string "in its life. And for a second... I\l"
	.string "envied it.\p"
	.string "That's why I'm fighting you. To\n"
	.string "remember why I don't!$"

Nexus_Text_Falkner_ChampionDefeat:
	.string "You stayed on the ground and still\n"
	.string "won. That's a new one.$"

Nexus_Text_Falkner_ChampionAfter:
	.string "{SPEAKER NAME_FALKNER}It flies faster than anything I've ever\n"
	.string "raised. But it has nowhere to go back\l"
	.string "to.\p"
	.string "My birds all come back to the same\n"
	.string "perch in Violet every night.\p"
	.string "I always thought that made them less\n"
	.string "free. Now I think it makes them mine.\p"
	.string "Go on. Knock it out of the sky. Then\n"
	.string "give it somewhere to land.$"
```

</details>

Falante novo: `SP_NAME_FALKNER` (ainda não existe em `include/constants/speaker_names.h`; skill `nomear-falante`).
