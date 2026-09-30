# Whitney

**Região da ficha:** Johto

Aparece no checklist como:

- **Whitney — Normal** (Johto · Líderes de Ginásio) — Líder de Goldenrod, famosa pelo poderoso Miltank.

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
| `OBJ_EVENT_GFX_WHITNEY` | `graphics/object_events/pics/people/gym_leaders/whitney.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_WHITNEY` | `graphics/trainers/front_pics/leader_whitney.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_WHITNEY` | `graphics/field_mugshots/whitney.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WHITNEY_1` | 604 | 0x75C | Maushold Lv27, Audino Lv27, Cinccino Lv27, Miltank Lv27 · *dupla* · VS: Yellow | `GoldenrodCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h`, `src/match_call.c` |
| `TRAINER_WHITNEY_2` | 607 | 0x75F | Ursaluna Lv78, Indeedee-F Lv77, Zoroark Hisui Lv77, Drampa Lv78, Maushold Lv77, Porygon-Z Lv78 · *dupla* | `GoldenrodCity_DepartmentStore_6F`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_WHITNEY` | 893 | 0x87D | Ursaluna Lv85, Regigigas Lv85, Zoroark Hisui Lv85, Drampa Lv85, Maushold Lv85, Porygon-Z Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_WHITNEY` = **1003** (flag de batalha `0x8EB`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Whitney_Fight`; campeão: `Nexus_EventScript_Whitney_Regigigas_ChampionFight` (para Regigigas), `Nexus_EventScript_Whitney_ScreamTail_ChampionFight` (para Scream Tail). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Whitney.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_WHITNEY`, campeã do Regigigas e da Scream Tail. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Terapagos**, o Normal lendário de Área Zero, uma tartaruga de cristal que parece um bichinho de pelúcia até brilhar: a Whitney é Líder de tipo Normal e quer o mais fofo e o mais forte ao mesmo tempo. Semi-lendário **Scream Tail**, a ancestral cor-de-rosa e fofa que grita (ela é campeã dela e do Regigigas; a Scream Tail entra por ser a cara da Whitney e porque o Slow Start do Regigigas não serve num time de ritmo). Mega **Drampa** (Normalite): já é do time de revanche dela, e a Berserk (fica mais forte quando apanha) é a Whitney que chora e volta mais brava. Mais **Miltank**, o terror do Rollout, Maushold e Ursaluna.

*Plano (Singles):* a Miltank põe Stealth Rock e se cura com Milk Drink, a Scream Tail paralisa e prende com Encore, o Terapagos sobe Calm Mind, e o Ursaluna de Guts e a Mega Drampa limpam. *Plano (Doubles):* o Maushold redireciona com Follow Me enquanto a Mega Drampa usa Hyper Voice nos dois alvos, Glare e Thunder Wave controlam a velocidade, e o Terapagos (Tera Shell ao entrar) aguenta o primeiro golpe de cada um.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Terapagos | Leftovers | Tera Shift | Modest | Tera Starstorm, Earth Power, Calm Mind, Protect |
| Scream Tail | Booster Energy | Protosynthesis | Timid | Encore, Thunder Wave, Dazzling Gleam, Protect |
| Drampa | Normalite | Berserk | Modest | Hyper Voice, Draco Meteor, Flamethrower, Glare |
| Miltank | Leftovers | Thick Fat | Careful | Body Slam, Rollout, Milk Drink, Stealth Rock |
| Maushold | Loaded Dice | Technician | Jolly | Population Bomb, Tidy Up, Follow Me, Bite |
| Ursaluna | Flame Orb | Guts | Adamant | Headlong Rush, Facade, Fire Punch, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_WHITNEY ===
Name: Whitney
Class: Leader
Pic: Leader Whitney
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Terapagos @ Leftovers
Modest Nature
Level: 100
Ability: Tera Shift
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tera Starstorm
- Earth Power
- Calm Mind
- Protect

Scream Tail @ Booster Energy
Timid Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Encore
- Thunder Wave
- Dazzling Gleam
- Protect

Drampa @ Normalite
Modest Nature
Level: 100
Ability: Berserk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Draco Meteor
- Flamethrower
- Glare

Miltank @ Leftovers
Careful Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- Rollout
- Milk Drink
- Stealth Rock

Maushold @ Loaded Dice
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Population Bomb
- Tidy Up
- Follow Me
- Bite

Ursaluna @ Flame Orb
Adamant Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Headlong Rush
- Facade
- Fire Punch
- Protect
```

</details>

### Lendário associado

#### Regigigas

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Regigigas_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Regigigas**. Whitney é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Whitney, Líder de Goldenrod, famosa pelo Miltank e pelo choro quando perde.

**A criatura.** Regigigas, dos Regis. Diz a lenda que puxou os continentes com cordas e que moldou os outros Regis de argila, gelo e magma. Dorme como estátua (no Snowpoint Temple em Sinnoh) e começa as lutas devagar (Slow Start).

**O fragmento.** Um mar em que a terra está sendo arrastada. O chão se move devagar como uma barcaça, e cordas grossas como torres vão da borda até o horizonte, rangendo, puxando um país inteiro.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> The ground under your feet was moving. Slowly, like a barge.
>
> Ropes as thick as towers ran from its edge to the horizon, creaking, pulling a whole country along behind them.

**Boss**

> The ropes went slack.
>
> At the end of them stood something huge and very still, and it took a long time to decide to look at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-486. Colossal.
>
> A land being dragged across the sea, and a girl from a big city who cried when she lost and then did not stop trying.
>
> What you brought back is small enough to carry. The ropes did not come.
>
> I told her that is also how continents move. She hit me. Gently.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Regigigas_Arrival:
	.string "The ground under your feet was\n"
	.string "moving. Slowly, like a barge.\p"
	.string "Ropes as thick as towers ran from its\n"
	.string "edge to the horizon, creaking, pulling\l"
	.string "a whole country along behind them.$"

Nexus_Text_Regigigas_Boss:
	.string "The ropes went slack.\p"
	.string "At the end of them stood something\n"
	.string "huge and very still, and it took a long\l"
	.string "time to decide to look at you.$"

Nexus_Text_Regigigas_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-486. Colossal.\p"
	.string "A land being dragged across the sea,\n"
	.string "and a girl from a big city who cried\l"
	.string "when she lost and then did not stop\l"
	.string "trying.\p"
	.string "What you brought back is small enough\n"
	.string "to carry. The ropes did not come.\p"
	.string "I told her that is also how\n"
	.string "continents move. She hit me. Gently.$"
```

</details>

#### Scream Tail

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_ScreamTail_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Scream Tail**. Whitney é a campeã dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Whitney, a mesma, diante de uma criatura fofa e cor-de-rosa como ela gosta, e que grita.

**A criatura.** Scream Tail é um Paradoxo que lembra uma Jigglypuff muito antiga, descrita num velho diário de expedição. Fada/Psíquico, cor-de-rosa, com uma cauda longa como cabelo.

**O fragmento.** Um prado de flores altas como árvores, sob uma lua grande demais. Tudo é silencioso demais: cada som volta mais baixo, como se alguém tivesse abaixado o volume.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A meadow of flowers as tall as trees, under a moon that was far too big.
>
> It was quiet. Too quiet. Every sound you made came back softer, as if someone had turned it down.

**Boss**

> Then the song started.
>
> It was a lullaby, until it wasn't. It became a scream, and the flowers closed all at once.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-985. Old Lullaby.
>
> A meadow that forgot how to be quiet, and a Gym Leader who sang back at it until it stopped.
>
> What you brought back is asleep. Let it stay that way a little longer.
>
> I did not know she could sing. I have not told her I was listening.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_ScreamTail_Arrival:
	.string "A meadow of flowers as tall as trees,\n"
	.string "under a moon that was far too big.\p"
	.string "It was quiet. Too quiet. Every sound\n"
	.string "you made came back softer, as if\l"
	.string "someone had turned it down.$"

Nexus_Text_ScreamTail_Boss:
	.string "Then the song started.\p"
	.string "It was a lullaby, until it wasn't. It\n"
	.string "became a scream, and the flowers\l"
	.string "closed all at once.$"

Nexus_Text_ScreamTail_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-985. Old Lullaby.\p"
	.string "A meadow that forgot how to be quiet,\n"
	.string "and a Gym Leader who sang back at it\l"
	.string "until it stopped.\p"
	.string "What you brought back is asleep. Let it\n"
	.string "stay that way a little longer.\p"
	.string "I did not know she could sing. I have\n"
	.string "not told her I was listening.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Whitney_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Whitney cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hiya! I'm Whitney! Everybody back in Goldenrod says my Pokémon are the cutest.
>
> Everybody who battles me says my Miltank is the scariest. Both are true!
>
> So don't cry when you lose, okay? That's my job!

**Derrota**

> Waaah! That wasn't fair! ...Okay, it was fair. Waaah!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_Intro:
	.string "Hiya! I'm Whitney! Everybody back in\n"
	.string "Goldenrod says my Pokémon are the\l"
	.string "cutest.\p"
	.string "Everybody who battles me says my\n"
	.string "Miltank is the scariest. Both are\l"
	.string "true!\p"
	.string "So don't cry when you lose, okay?\n"
	.string "That's my job!$"

Nexus_Text_Whitney_Defeat:
	.string "Waaah! That wasn't fair! ...Okay, it\n"
	.string "was fair. Waaah!$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Ainda não estão no código.

**Variação 2 — a loja de departamentos.** Goldenrod, compras e choro: ela já chorou em todos os andares da loja, e não foi por batalha.

**Antes da luta**

> Do you know how many floors the Goldenrod Department Store has? I do. I've cried on every single one!
>
> Not because of battles. Because of sales! They end so fast!
>
> Battles end fast too. Mostly yours! Let's go!

**Derrota**

> Waaah! Sold out AND beaten! Worst. Day. Ever!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_Intro2:
	.string "Do you know how many floors the\n"
	.string "Goldenrod Department Store has? I do.\l"
	.string "I've cried on every single one!\p"
	.string "Not because of battles. Because of\n"
	.string "sales! They end so fast!\p"
	.string "Battles end fast too. Mostly yours!\n"
	.string "Let's go!$"

Nexus_Text_Whitney_Defeat2:
	.string "Waaah! Sold out AND beaten! Worst. Day.\n"
	.string "Ever!$"
```

</details>

**Variação 3 — "ela não dura uma semana".** O lado teimoso: disseram que ela não duraria como Líder, por ser emotiva e barulhenta. Continua ali, e continua barulhenta.

**Antes da luta**

> When I became a Gym Leader, people said I wouldn't last a week.
>
> 'Too emotional,' they said. 'Too loud.'
>
> That was years ago. I'm still loud! Let's battle!

**Derrota**

> Waaah! …Still here, though. Still loud!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_Intro3:
	.string "When I became a Gym Leader, people said\n"
	.string "I wouldn't last a week.\p"
	.string "'Too emotional,' they said. 'Too loud.'\p"
	.string "That was years ago. I'm still loud!\n"
	.string "Let's battle!$"

Nexus_Text_Whitney_Defeat3:
	.string "Waaah! …Still here, though. Still loud!$"
```

</details>

### Diálogo associado ao lendário

#### Regigigas

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Whitney_Regigigas_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Whitney é a **campeã**, a luta logo antes do Regigigas. A fala é sobre a criatura, sem dizer o nome dela.

A Whitney é impaciente e acha o gigante devagar demais: puxou um país inteiro até ali e agora não se mexe. Aí reconhece a própria estratégia: o Rollout da Miltank também começa devagar, e todo mundo ri no primeiro turno. Ninguém ri no quinto. Depois de chorar (quase tudo), dá o conselho de quem conhece o ritmo: algo desse tamanho não começa devagar por preguiça, começa devagar porque, quando se mexe, não para. Bata cedo. E, se ele engrenar, corra, que também é estratégia.

**Antes da luta**

> Did you see the big guy at the end of the ropes? He's been standing there since I got here!
>
> He pulled a whole country here, and now he won't even move. So slow!
>
> ...You know what? My Miltank's Rollout starts slow too. Everybody laughs at the first turn.
>
> Nobody laughs at the fifth! Let's go!

**Derrota**

> Waaah! I rolled and rolled and it wasn't enough!

**Depois da luta**

> Okay, I'm done crying. Mostly.
>
> Something that big doesn't start slow because it's lazy. It starts slow because once it moves, it can't stop.
>
> Don't let it get going. Hit it hard and hit it early!
>
> ...And if it gets going anyway? Then run. That's a strategy too. I use it all the time.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_Regigigas_ChampionIntro:
	.string "Did you see the big guy at the end of\n"
	.string "the ropes? He's been standing there\l"
	.string "since I got here!\p"
	.string "He pulled a whole country here, and\n"
	.string "now he won't even move. So slow!\p"
	.string "...You know what? My Miltank's Rollout\n"
	.string "starts slow too. Everybody laughs at\l"
	.string "the first turn.\p"
	.string "Nobody laughs at the fifth! Let's go!$"

Nexus_Text_Whitney_Regigigas_ChampionDefeat:
	.string "Waaah! I rolled and rolled and it\n"
	.string "wasn't enough!$"

Nexus_Text_Whitney_Regigigas_ChampionAfter:
	.string "{SPEAKER NAME_WHITNEY}Okay, I'm done crying. Mostly.\p"
	.string "Something that big doesn't start slow\n"
	.string "because it's lazy. It starts slow\l"
	.string "because once it moves, it can't stop.\p"
	.string "Don't let it get going. Hit it hard\n"
	.string "and hit it early!\p"
	.string "...And if it gets going anyway? Then\n"
	.string "run. That's a strategy too. I use it\l"
	.string "all the time.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1: a criatura pelo olhar do campeão, sem o nome da espécie. Ainda não estão no código.

**Variação 2 — o trem que não vai a lugar nenhum.** Puxa o fragmento do caderno dela: o Magnet Train para Saffron termina sobre a água. Ela fica brava, e depois entende que o gigante não está roubando a terra: está arrumando.

**Antes da luta**

> The train to Saffron doesn't go anywhere anymore. The tracks just stop over the water.
>
> That big guy at the end of the ropes is taking us somewhere. Nobody asked me!
>
> I had plans! Shopping plans! Let's battle, I'm so mad!

**Derrota**

> Waaah! Now I'm mad AND I lost!

**Depois da luta**

> Okay, fine, I thought about it. He isn't stealing us. He's putting things back.
>
> Like tidying up after a party. Everything back where it was before anybody moved it.
>
> I don't like it. But I'd do it too, if I were that big. Go on. Tell him I said hi. Loudly.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_Regigigas_ChampionIntro2:
	.string "The train to Saffron doesn't go\n"
	.string "anywhere anymore. The tracks just stop\l"
	.string "over the water.\p"
	.string "That big guy at the end of the ropes is\n"
	.string "taking us somewhere. Nobody asked me!\p"
	.string "I had plans! Shopping plans! Let's\n"
	.string "battle, I'm so mad!$"

Nexus_Text_Whitney_Regigigas_ChampionDefeat2:
	.string "Waaah! Now I'm mad AND I lost!$"

Nexus_Text_Whitney_Regigigas_ChampionAfter2:
	.string "{SPEAKER NAME_WHITNEY}Okay, fine, I thought about it. He isn't\n"
	.string "stealing us. He's putting things back.\p"
	.string "Like tidying up after a party.\n"
	.string "Everything back where it was before\l"
	.string "anybody moved it.\p"
	.string "I don't like it. But I'd do it too, if I\n"
	.string "were that big. Go on. Tell him I said hi.\l"
	.string "Loudly.$"
```

</details>

**Variação 3 — os três que ele fez.** A lenda: ele moldou os outros Regis de argila, gelo e magma, e eles dormem longe, cada um na sua caverna. Ela imagina que ele fica sozinho, e compara com a Miltank que a vigia enquanto ela cochila.

**Antes da luta**

> They say the big one made three friends. Out of clay, and ice, and fire rock.
>
> Then he fell asleep, and they had to guard him for ages and ages!
>
> Like me and my Miltank. I nap, she guards. Let's battle!

**Derrota**

> Waaah! Miltank, where were you?!

**Depois da luta**

> If he made three friends out of nothing, I bet he gets lonely.
>
> Nobody stays awake with him. They're all asleep in their own caves, far away.
>
> Be nice to him, okay? Beat him, but be nice. You're allowed to do both.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_Regigigas_ChampionIntro3:
	.string "They say the big one made three\n"
	.string "friends. Out of clay, and ice, and fire\l"
	.string "rock.\p"
	.string "Then he fell asleep, and they had to\n"
	.string "guard him for ages and ages!\p"
	.string "Like me and my Miltank. I nap, she\n"
	.string "guards. Let's battle!$"

Nexus_Text_Whitney_Regigigas_ChampionDefeat3:
	.string "Waaah! Miltank, where were you?!$"

Nexus_Text_Whitney_Regigigas_ChampionAfter3:
	.string "{SPEAKER NAME_WHITNEY}If he made three friends out of\n"
	.string "nothing, I bet he gets lonely.\p"
	.string "Nobody stays awake with him. They're\n"
	.string "all asleep in their own caves, far away.\p"
	.string "Be nice to him, okay? Beat him, but be\n"
	.string "nice. You're allowed to do both.$"
```

</details>

#### Scream Tail

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Whitney_ScreamTail_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Whitney é a **campeã**, a luta logo antes da Scream Tail. A fala é sobre a criatura, sem dizer o nome dela.

A Whitney adora coisas fofas, e esta é cor-de-rosa, peluda, tem a caudinha mais linda do mundo, e gritou na cara dela. Ela fica ofendida, até lembrar que fofo e assustador é exatamente o que dizem dela e da Miltank. O que fica: em casa a chamam de chorona como se fosse a história toda. A criatura grita porque quer ser deixada em paz; a Whitney chora porque quer tanto ganhar que dói. Nenhuma das duas vai parar.

**Antes da luta**

> It's pink! It's fluffy! It has the cutest little tail in the whole world!
>
> And it SCREAMED at me. Right in my face. My hair's still standing up!
>
> ...Cute things are allowed to be scary. Ask anyone who's lost to me!

**Derrota**

> Waaah! I screamed louder and it still didn't work!

**Depois da luta**

> People back home call me a crybaby. They say it like it's the whole story.
>
> That little thing screams because it wants to be left alone. I cry because I want to win so bad it hurts.
>
> Neither of us is gonna stop. Go sing it something nice. Then beat it!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_ScreamTail_ChampionIntro:
	.string "It's pink! It's fluffy! It has the\n"
	.string "cutest little tail in the whole world!\p"
	.string "And it SCREAMED at me. Right in my\n"
	.string "face. My hair's still standing up!\p"
	.string "...Cute things are allowed to be scary.\n"
	.string "Ask anyone who's lost to me!$"

Nexus_Text_Whitney_ScreamTail_ChampionDefeat:
	.string "Waaah! I screamed louder and it still\n"
	.string "didn't work!$"

Nexus_Text_Whitney_ScreamTail_ChampionAfter:
	.string "{SPEAKER NAME_WHITNEY}People back home call me a crybaby.\n"
	.string "They say it like it's the whole story.\p"
	.string "That little thing screams because it\n"
	.string "wants to be left alone. I cry because\l"
	.string "I want to win so bad it hurts.\p"
	.string "Neither of us is gonna stop. Go sing it\n"
	.string "something nice. Then beat it!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1: a criatura pelo olhar do campeão, sem o nome da espécie. Ainda não estão no código.

**Variação 2 — a canção que termina.** Lore da linhagem da Jigglypuff: canta até todos dormirem. Ela acha que a criatura grita porque não quer que a canção acabe, como ela chora quando a festa acaba.

**Antes da luta**

> Its song starts so pretty. I almost fell asleep standing up!
>
> Then it gets louder, and louder, and then… AAAAH! Just like that!
>
> I sing like that too. Ask my Miltank. …Actually, don't. Let's battle!

**Derrota**

> Waaah! Encore! No, wait, not an encore!

**Depois da luta**

> I think it screams when the song ends. Like it doesn't want the song to be over.
>
> I get that. I cry when parties end. Every single time.
>
> So go on. Just… don't be the one who ends its song too fast, okay?

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_ScreamTail_ChampionIntro2:
	.string "Its song starts so pretty. I almost fell\n"
	.string "asleep standing up!\p"
	.string "Then it gets louder, and louder, and\n"
	.string "then… AAAAH! Just like that!\p"
	.string "I sing like that too. Ask my Miltank.\n"
	.string "…Actually, don't. Let's battle!$"

Nexus_Text_Whitney_ScreamTail_ChampionDefeat2:
	.string "Waaah! Encore! No, wait, not an encore!$"

Nexus_Text_Whitney_ScreamTail_ChampionAfter2:
	.string "{SPEAKER NAME_WHITNEY}I think it screams when the song ends.\n"
	.string "Like it doesn't want the song to be\l"
	.string "over.\p"
	.string "I get that. I cry when parties end.\n"
	.string "Every single time.\p"
	.string "So go on. Just… don't be the one who\n"
	.string "ends its song too fast, okay?$"
```

</details>

**Variação 3 — fofo sempre foi assustador.** O homem de sobretudo (fio 3 do diário) contou a ela que aquilo é como as coisas fofas eram há muito tempo. Ela se sente vingada.

**Antes da luta**

> A man in a long coat told me that little pink thing is what cute things looked like, a really long time ago.
>
> Fluffy. Pink. Scary teeth. So cute was always a little bit scary!
>
> I KNEW it! I've been saying that for years! Battle!

**Derrota**

> Waaah! Proven right, and I still lost!

**Depois da luta**

> Everybody back home thinks cute means soft. Easy. Harmless.
>
> That thing's been cute forever, and nobody's pushed it around once.
>
> I want that. I'm getting that. Go on, go learn from it. I'll be right behind you!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Whitney_ScreamTail_ChampionIntro3:
	.string "A man in a long coat told me that little\n"
	.string "pink thing is what cute things looked\l"
	.string "like, a really long time ago.\p"
	.string "Fluffy. Pink. Scary teeth. So cute was\n"
	.string "always a little bit scary!\p"
	.string "I KNEW it! I've been saying that for\n"
	.string "years! Battle!$"

Nexus_Text_Whitney_ScreamTail_ChampionDefeat3:
	.string "Waaah! Proven right, and I still lost!$"

Nexus_Text_Whitney_ScreamTail_ChampionAfter3:
	.string "{SPEAKER NAME_WHITNEY}Everybody back home thinks cute means\n"
	.string "soft. Easy. Harmless.\p"
	.string "That thing's been cute forever, and\n"
	.string "nobody's pushed it around once.\p"
	.string "I want that. I'm getting that. Go on, go\n"
	.string "learn from it. I'll be right behind you!$"
```

</details>

Falante novo: `SP_NAME_WHITNEY` (ainda não existe em `include/constants/speaker_names.h`; skill `nomear-falante`).
