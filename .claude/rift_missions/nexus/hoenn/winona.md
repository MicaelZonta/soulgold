# Winona

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Winona — Voador** (Hoenn · Líderes de Ginásio) — graciosa Líder de Fortree.

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
| `OBJ_EVENT_GFX_WINONA` | `graphics/object_events/pics/people/gym_leaders/winona.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_WINONA` | `graphics/trainers/front_pics/leader_winona.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WINONA_2` | 790 | 0x816 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WINONA_3` | 791 | 0x817 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WINONA_4` | 792 | 0x818 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WINONA_5` | 793 | 0x819 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_455` (ex-`TRAINER_WINONA_1`, 270).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_WINONA` = **1020** (flag de batalha `0x8FC`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Winona_Fight`; campeão: `Nexus_EventScript_Winona_GalarianZapdos_ChampionFight` (para Galarian Zapdos), `Nexus_EventScript_Winona_Thundurus_ChampionFight` (para Thundurus). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Winona.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_WINONA`, campeã de Thundurus e Galarian Zapdos. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Rayquaza**, o senhor do céu de Hoenn, que mora no alto do Sky Pillar; Mega pelo Dragon Ascent (ocupa as vagas de lendário e de Mega, R10). Semi-lendário **Thundurus**, a tempestade que ela conhece de Fortree. Mais o time dela de sempre: **Altaria** (o ás), **Swellow**, **Pelipper** e **Skarmory**.

*Plano (Singles):* o Skarmory de Sturdy arma Spikes e força trocas com Whirlwind; o Thundurus de Prankster põe Thunder Wave e Taunt com prioridade; a Altaria sobe com Cotton Guard e cura com Roost. A Mega Rayquaza traz o Delta Stream, que tira as fraquezas do tipo Voador (Gelo, Elétrico, Pedra) do time inteiro enquanto ela está em campo, e limpa com Dragon Dance.

*Plano (Doubles):* o Pelipper põe Tailwind e o Thundurus paralisa com prioridade; o Swellow de Flame Orb usa Protect no turno 1 para ativar o Guts. Quando a Rayquaza sai e o Delta Stream acaba, o Drizzle do Pelipper entra e o Hurricane passa a não errar. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Rayquaza | Life Orb | Air Lock | Adamant | Dragon Ascent, Dragon Claw, Extreme Speed, Dragon Dance |
| Thundurus | Sitrus Berry | Prankster | Timid | Thunderbolt, Knock Off, Thunder Wave, Taunt |
| Altaria | Leftovers | Natural Cure | Bold | Cotton Guard, Roost, Draco Meteor, Hurricane |
| Swellow | Flame Orb | Guts | Jolly | Facade, Brave Bird, Quick Attack, Protect |
| Pelipper | Damp Rock | Drizzle | Modest | Hurricane, Scald, Tailwind, U-turn |
| Skarmory | Rocky Helmet | Sturdy | Impish | Spikes, Brave Bird, Roost, Whirlwind |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_WINONA ===
Name: Winona
Class: Leader
Pic: Leader Winona
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Rayquaza @ Life Orb
Adamant Nature
Level: 100
Ability: Air Lock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Ascent
- Dragon Claw
- Extreme Speed
- Dragon Dance

Thundurus @ Sitrus Berry
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Knock Off
- Thunder Wave
- Taunt

Altaria @ Leftovers
Bold Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Cotton Guard
- Roost
- Draco Meteor
- Hurricane

Swellow @ Flame Orb
Jolly Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Facade
- Brave Bird
- Quick Attack
- Protect

Pelipper @ Damp Rock
Modest Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Scald
- Tailwind
- U-turn

Skarmory @ Rocky Helmet
Impish Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spikes
- Brave Bird
- Roost
- Whirlwind
```

</details>


### Lendário associado

#### Thundurus

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Thundurus_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Thundurus**. Winona é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Winona, Líder de Fortree, a cidade construída nas copas das árvores, especialista em Voador.

**A criatura.** Thundurus (Elétrico/Voador) cruza os céus de Unova numa nuvem, disparando raios e provocando incêndios na floresta. Rival do Tornadus; os dois foram contidos pelo Landorus.

**O fragmento.** Uma floresta de casas nas copas, pontes de corda balançando entre elas. O céu é uma nuvem só, tão baixa que os telhados mais altos somem dentro dela.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest of treetop houses, with rope bridges swaying between them.
>
> The sky was one enormous cloud, hanging so low that the highest roofs vanished into it.

**Boss**

> The cloud crackled.
>
> Someone was riding it -- a figure with a tail of lightning, laughing -- and every bolt it threw landed a little closer to the bridges.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-642. Bolt Strike.
>
> A sky that throws lightning at the tallest thing it can find, and a woman who has always lived as high as she could.
>
> What came back with you is small, and it does not ride a cloud. I checked twice. It still laughs when it thunders.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Thundurus_Arrival:
	.string "A forest of treetop houses, with rope\n"
	.string "bridges swaying between them.\p"
	.string "The sky was one enormous cloud,\n"
	.string "hanging so low that the highest roofs\l"
	.string "vanished into it.$"

Nexus_Text_Thundurus_Boss:
	.string "The cloud crackled.\p"
	.string "Someone was riding it -- a figure with a\n"
	.string "tail of lightning, laughing -- and every\l"
	.string "bolt it threw landed a little closer to\l"
	.string "the bridges.$"

Nexus_Text_Thundurus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-642. Bolt Strike.\p"
	.string "A sky that throws lightning at the\n"
	.string "tallest thing it can find, and a woman\l"
	.string "who has always lived as high as she\l"
	.string "could.\p"
	.string "What came back with you is small, and it\n"
	.string "does not ride a cloud. I checked twice.\l"
	.string "It still laughs when it thunders.$"
```

</details>

#### Galarian Zapdos

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_GalarianZapdos_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Galarian Zapdos**. Winona é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Winona, Líder de Fortree, que ensina aos jovens Treinadores que pássaro nasceu para o céu.

**A criatura.** O Zapdos de Galar (Lutador/Voador) quase não voa: corre, com pernas fortíssimas, e é rápido demais para ser seguido. As penas estalam quando roçam umas nas outras, e por esse som foi confundido com o Zapdos antigo.

**O fragmento.** Uma planície larga sob um céu vazio, riscada por sulcos retos, como se alguma coisa tivesse corrido de um lado para o outro a noite toda. Penas douradas nos sulcos, estalando.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A wide, flat plain under an empty sky.
>
> Deep grooves ran across it in straight lines, as if something had sprinted back and forth all night. Golden feathers lay in the grooves, crackling.

**Boss**

> The ground shook in a quick, steady rhythm.
>
> Something came running over the horizon, fast as thunder, with its wings folded tight. Not once did it try to fly.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-145. Strong Legs.
>
> A bird that chose the ground, and a woman who has never once chosen it.
>
> What came back with you followed me into the next room on foot. I let it. It seemed important.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_GalarianZapdos_Arrival:
	.string "A wide, flat plain under an empty sky.\p"
	.string "Deep grooves ran across it in straight\n"
	.string "lines, as if something had sprinted\l"
	.string "back and forth all night. Golden\l"
	.string "feathers lay in the grooves, crackling.$"

Nexus_Text_GalarianZapdos_Boss:
	.string "The ground shook in a quick, steady\n"
	.string "rhythm.\p"
	.string "Something came running over the\n"
	.string "horizon, fast as thunder, with its\l"
	.string "wings folded tight. Not once did it try\l"
	.string "to fly.$"

Nexus_Text_GalarianZapdos_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-145. Strong Legs.\p"
	.string "A bird that chose the ground, and a\n"
	.string "woman who has never once chosen it.\p"
	.string "What came back with you followed me\n"
	.string "into the next room on foot. I let it. It\l"
	.string "seemed important.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Winona_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Winona cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I am Winona. In Fortree, we build our homes among the treetops, so that we may live close to the sky.
>
> I do not know this place. But the air moves here, and where the air moves, my birds can fly.
>
> Let us dance in the wind together.

**Derrota**

> You flew higher than I did. How lovely.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Winona_Intro:
	.string "I am Winona. In Fortree, we build our\n"
	.string "homes among the treetops, so that we\l"
	.string "may live close to the sky.\p"
	.string "I do not know this place. But the air\n"
	.string "moves here, and where the air moves, my\l"
	.string "birds can fly.\p"
	.string "Let us dance in the wind together.$"

Nexus_Text_Winona_Defeat:
	.string "You flew higher than I did. How lovely.$"
```

</details>


### Diálogo associado ao lendário

#### Thundurus

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Winona_Thundurus_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Winona é a **campeã**, a luta logo antes do Thundurus. A fala é sobre a criatura, sem dizer o nome dela.

A tempestade atira raios no ponto mais alto que encontra, e em Fortree o ponto mais alto são as casas. A Winona sempre viveu o mais alto possível, perto do céu, e nunca pensou que o céu pudesse querê-la longe. A virada vem dos pássaros dela: na tempestade, não se voa por cima, voa-se por baixo, baixo e rápido, e espera-se. Por anos ela achou que planar era a única coisa que valia aprender; os pássaros a ensinaram a pousar.

**Antes da luta**

> The storm here throws lightning at the tallest thing it can find. In Fortree, the tallest things are our homes.
>
> My birds and I have always lived as high as we could. Closer to the sky.
>
> I never thought the sky could want us gone.
>
> …Forgive me. Let us fly while we still can!

**Derrota**

> You flew straight through the storm. Remarkable.

**Depois da luta**

> Every bird Pokémon knows something that people forget.
>
> When the storm comes, you do not fly above it. You fly beneath it, low and quick, and you wait.
>
> For years I believed soaring was the only thing worth learning. My birds taught me how to land.
>
> Go now. Keep your head low, and your heart high.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Winona_Thundurus_ChampionIntro:
	.string "The storm here throws lightning at the\n"
	.string "tallest thing it can find. In Fortree,\l"
	.string "the tallest things are our homes.\p"
	.string "My birds and I have always lived as\n"
	.string "high as we could. Closer to the sky.\p"
	.string "I never thought the sky could want us\n"
	.string "gone.\p"
	.string "…Forgive me. Let us fly while we still\n"
	.string "can!$"

Nexus_Text_Winona_Thundurus_ChampionDefeat:
	.string "You flew straight through the storm.\n"
	.string "Remarkable.$"

Nexus_Text_Winona_Thundurus_ChampionAfter:
	.string "{SPEAKER NAME_WINONA}Every bird Pokémon knows something\n"
	.string "that people forget.\p"
	.string "When the storm comes, you do not fly\n"
	.string "above it. You fly beneath it, low and\l"
	.string "quick, and you wait.\p"
	.string "For years I believed soaring was the\n"
	.string "only thing worth learning. My birds\l"
	.string "taught me how to land.\p"
	.string "Go now. Keep your head low, and your\n"
	.string "heart high.$"
```

</details>

#### Galarian Zapdos

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Winona_GalarianZapdos_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Winona é a **campeã**, a luta logo antes do Zapdos de Galar. A fala é sobre a criatura, sem dizer o nome dela.

Na planície há um pássaro que não voa: corre, mais rápido do que qualquer coisa que a Winona já viu no céu. Da primeira vez ela sentiu pena (um pássaro de asas dobradas); depois o viu correr e passou a se sentir pequena. A virada: ela passou a vida dizendo aos jovens que pássaros foram feitos para o céu, e aquele ouviu a mesma coisa e decidiu diferente. Liberdade não é a altura que se alcança, é escolher para onde vão os próprios pés. Ela vai precisar de um discurso novo no ginásio.

**Antes da luta**

> There is a bird out on that plain that does not fly. It runs. Faster than anything I have ever seen in the sky.
>
> I confess, the first time I saw it, I felt sorry for it. A bird with folded wings.
>
> Then I watched it run, and I stopped feeling sorry. I started feeling… small.
>
> Let us battle. I need to think.

**Derrota**

> You did not need wings to beat me.

**Depois da luta**

> All my life, I have told young Trainers that birds are meant for the sky.
>
> That one heard the same thing, I think, and simply decided otherwise.
>
> Freedom is not the height you reach. It is choosing where your own feet go.
>
> …I will need a new speech for my Gym. Go on. The plain is waiting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Winona_GalarianZapdos_ChampionIntro:
	.string "There is a bird out on that plain that\n"
	.string "does not fly. It runs. Faster than\l"
	.string "anything I have ever seen in the sky.\p"
	.string "I confess, the first time I saw it, I\n"
	.string "felt sorry for it. A bird with folded\l"
	.string "wings.\p"
	.string "Then I watched it run, and I stopped\n"
	.string "feeling sorry. I started feeling… small.\p"
	.string "Let us battle. I need to think.$"

Nexus_Text_Winona_GalarianZapdos_ChampionDefeat:
	.string "You did not need wings to beat me.$"

Nexus_Text_Winona_GalarianZapdos_ChampionAfter:
	.string "{SPEAKER NAME_WINONA}All my life, I have told young Trainers\n"
	.string "that birds are meant for the sky.\p"
	.string "That one heard the same thing, I think,\n"
	.string "and simply decided otherwise.\p"
	.string "Freedom is not the height you reach. It\n"
	.string "is choosing where your own feet go.\p"
	.string "…I will need a new speech for my Gym. Go\n"
	.string "on. The plain is waiting.$"
```

</details>

Falante novo: `SP_NAME_WINONA` (não existe ainda em `include/constants/speaker_names.h`).
