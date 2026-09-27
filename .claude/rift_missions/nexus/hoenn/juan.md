# Juan

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Juan — Água** (Hoenn · Líderes de Ginásio) — mentor de Wallace e Líder de Sootopolis em *Emerald*.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_JUAN` | `graphics/object_events/pics/people/gym_leaders/juan.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_JUAN` | `graphics/trainers/front_pics/leader_juan.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_JUAN_2` | 798 | 0x81E | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_JUAN_3` | 799 | 0x81F | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_JUAN_4` | 800 | 0x820 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_JUAN_5` | 801 | 0x821 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_457` (ex-`TRAINER_JUAN_1`, 272).

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_JUAN`, campeão de Tapu Fini e Walking Wake. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Palkia** (Água/Dragão, a dona do espaço: o Juan é o artista que "esculpe ilusões de água", e a Palkia é a água que dobra o próprio palco); semi-lendário **Walking Wake** (Água/Dragão, o dragão ancestral da água, de quem ele é campeão); Mega **Starmie** (Watertite; neste hack a Mega é física, com Huge Power: a estrela-joia, o brilho do dândi). Mais **Kingdra** (o ás dele em Emerald, também Água/Dragão), **Crawdaunt** (do time dele em Emerald) e **Pelipper** (Drizzle). O time é uma coreografia de chuva com três dragões de água.

*Plano (Singles):* o Pelipper abre a chuva e sai de U-turn; Kingdra (Swift Swim), Palkia e Walking Wake batem com Água reforçada e Thunder certeiro; a Mega Starmie tira hazards com Rapid Spin e limpa com Huge Power; o Crawdaunt de Sash sobe Swords Dance e fecha com Aqua Jet.

*Plano (Doubles):* Pelipper põe chuva **e** Tailwind no primeiro turno; Kingdra e Palkia atacam lado a lado; o Walking Wake entra de Specs e sai de Flip Turn. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Palkia | Life Orb | Pressure | Modest | Spacial Rend, Hydro Pump, Thunder, Fire Blast |
| Walking Wake | Choice Specs | Protosynthesis | Timid | Hydro Steam, Draco Meteor, Flamethrower, Flip Turn |
| Starmie | Watertite | Analytic | Jolly | Liquidation, Zen Headbutt, Rapid Spin, Recover |
| Kingdra | Wise Glasses | Swift Swim | Modest | Hydro Pump, Draco Meteor, Ice Beam, Protect |
| Pelipper | Damp Rock | Drizzle | Bold | Hurricane, Scald, Tailwind, U-turn |
| Crawdaunt | Focus Sash | Adaptability | Adamant | Crabhammer, Knock Off, Aqua Jet, Swords Dance |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_JUAN ===
Name: Juan
Class: Leader
Pic: Leader Juan
Gender: Male
Music: Elite Four
Double Battle: Yes
AI: Smart Trainer

Palkia @ Life Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spacial Rend
- Hydro Pump
- Thunder
- Fire Blast

Walking Wake @ Choice Specs
Timid Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Steam
- Draco Meteor
- Flamethrower
- Flip Turn

Starmie @ Watertite
Jolly Nature
Level: 100
Ability: Analytic
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Zen Headbutt
- Rapid Spin
- Recover

Kingdra @ Wise Glasses
Modest Nature
Level: 100
Ability: Swift Swim
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Draco Meteor
- Ice Beam
- Protect

Pelipper @ Damp Rock
Bold Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Scald
- Tailwind
- U-turn

Crawdaunt @ Focus Sash
Adamant Nature
Level: 100
Ability: Adaptability
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Crabhammer
- Knock Off
- Aqua Jet
- Swords Dance
```

</details>


### Lendário associado

#### Tapu Fini

📝 **Proposta de 27/09/2026, aguardando o autor.** **Tapu Fini**. Juan é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Juan, Líder de Sootopolis antes do Wallace e mestre dele. Dândi, dançarino, trata a batalha como espetáculo de água; voltou ao ginásio em Emerald quando o Wallace virou Campeão.

**A criatura.** Tapu Fini, a guardiã de Poni (Água/Fada). Cria uma névoa que cura e purifica, mas quem a provoca pode ser engolido por ela; quando se sente ameaçada, fecha-se numa concha.

**O fragmento.** Uma ilha envolta numa névoa tão densa que não se vê o próprio pé. A névoa lava os cortes de quem entra com calma e fecha a garganta de quem entra com raiva.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An island wrapped in a mist so thick you could not see your own feet.
>
> It smelled of salt and of something clean, like a wound after it has been washed.

**Boss**

> The mist parted like a curtain.
>
> A shell of stone hung above the water, and the fog was pouring out of it.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-788. The Mist Warden.
>
> A mist that heals the calm and drowns the angry, and a dancer who never once raised his voice inside it.
>
> What came back with you is small, and damp, and very calm. He says the water only returns what you bring to it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_TapuFini_Arrival:
	.string "An island wrapped in a mist so thick\n"
	.string "you could not see your own feet.\p"
	.string "It smelled of salt and of something\n"
	.string "clean, like a wound after it has been\l"
	.string "washed.$"

Nexus_Text_TapuFini_Boss:
	.string "The mist parted like a curtain.\p"
	.string "A shell of stone hung above the water,\n"
	.string "and the fog was pouring out of it.$"

Nexus_Text_TapuFini_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-788. The Mist Warden.\p"
	.string "A mist that heals the calm and drowns\n"
	.string "the angry, and a dancer who never once\l"
	.string "raised his voice inside it.\p"
	.string "What came back with you is small, and\n"
	.string "damp, and very calm. He says the water\l"
	.string "only returns what you bring to it.$"
```

</details>


#### Walking Wake

📝 **Proposta de 27/09/2026, aguardando o autor.** **Walking Wake**. Juan é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Juan, o mestre que ensinou ao Wallace tudo sobre água e elegância.

**A criatura.** Walking Wake, Pokémon Paradoxo antigo (Água/Dragão). Lembra uma fera lendária de Johto em versão pré-histórica, com jubas de água; só se conhecia por relatos e uma revista de mistérios.

**O fragmento.** Um lago pré-histórico sob chuva quente. Samambaias do tamanho de casas, e no barro pegadas enormes que ainda estão se enchendo de água.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Warm rain over a lake older than any map.
>
> Ferns as tall as houses leaned over the water. In the mud, huge footprints were still filling up.

**Boss**

> The lake rose all at once, like a wave that had waited a very long time.
>
> Something with a mane of water came out of it, running.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1009. The Ancient Wake.
>
> A lake from before anyone, and a man who taught water to dance showing off for a thing that already knew how.
>
> What you brought back is small, and it splashes whenever it walks. He bowed to it. I believe it bowed back.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_WalkingWake_Arrival:
	.string "Warm rain over a lake older than any\n"
	.string "map.\p"
	.string "Ferns as tall as houses leaned over\n"
	.string "the water. In the mud, huge footprints\l"
	.string "were still filling up.$"

Nexus_Text_WalkingWake_Boss:
	.string "The lake rose all at once, like a wave\n"
	.string "that had waited a very long time.\p"
	.string "Something with a mane of water came\n"
	.string "out of it, running.$"

Nexus_Text_WalkingWake_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1009. The Ancient Wake.\p"
	.string "A lake from before anyone, and a man\n"
	.string "who taught water to dance showing off\l"
	.string "for a thing that already knew how.\p"
	.string "What you brought back is small, and it\n"
	.string "splashes whenever it walks. He bowed\l"
	.string "to it. I believe it bowed back.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Juan cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Ah, a visitor! Forgive me, I was rehearsing.
>
> It was I who taught Wallace everything he knows of water and grace. He surpassed me, of course.
>
> A teacher should only ever be proud of that.
>
> Now then! Let the water and I show you a grand illusion!

**Derrota**

> Aahahaha! Excellent! Even the illusion applauds.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_Intro:
	.string "Ah, a visitor! Forgive me, I was\n"
	.string "rehearsing.\p"
	.string "It was I who taught Wallace everything\n"
	.string "he knows of water and grace. He\l"
	.string "surpassed me, of course.\p"
	.string "A teacher should only ever be proud of\n"
	.string "that.\p"
	.string "Now then! Let the water and I show you\n"
	.string "a grand illusion!$"

Nexus_Text_Juan_Defeat:
	.string "Aahahaha! Excellent! Even the illusion\n"
	.string "applauds.$"
```

</details>


### Diálogo associado ao lendário

#### Tapu Fini

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Juan é o **campeão**, a luta logo antes da Tapu Fini. A fala é sobre a criatura, sem dizer o nome dela.

O Juan passou a vida fazendo a água ficar bonita para uma plateia: ilusão é gentileza, mostrar algo mais lindo que a verdade. A névoa da guardiã faz o contrário: devolve exatamente o que você trouxe. A virada é que ele não sabe o que ela viu nele, o dançarino ou o velho escondido atrás da capa. O conselho final é de mestre: entre calmo.

**Antes da luta**

> Did you walk through the mist? It did not hurt you, I see. Good.
>
> It washes clean those who come calmly. Those who come angry, it simply swallows.
>
> I have spent my life making water beautiful for an audience. This one makes water honest.
>
> Aahaha! How I envy it. Shall we?

**Derrota**

> Aahahaha… the mist saw right through my flourish.

**Depois da luta**

> An illusion is a kindness, you know. We show people something lovelier than the truth.
>
> That mist refuses to. It shows you exactly what you carried in.
>
> I wonder what it saw in me. A dancer? Or an old man hiding behind his cape?
>
> Go gently. Bring it calm, and it will return calm.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_TapuFini_ChampionIntro:
	.string "Did you walk through the mist? It did\n"
	.string "not hurt you, I see. Good.\p"
	.string "It washes clean those who come calmly.\n"
	.string "Those who come angry, it simply\l"
	.string "swallows.\p"
	.string "I have spent my life making water\n"
	.string "beautiful for an audience. This one\l"
	.string "makes water honest.\p"
	.string "Aahaha! How I envy it. Shall we?$"

Nexus_Text_Juan_TapuFini_ChampionDefeat:
	.string "Aahahaha… the mist saw right through\n"
	.string "my flourish.$"

Nexus_Text_Juan_TapuFini_ChampionAfter:
	.string "{SPEAKER NAME_JUAN}An illusion is a kindness, you know. We\n"
	.string "show people something lovelier than\l"
	.string "the truth.\p"
	.string "That mist refuses to. It shows you\n"
	.string "exactly what you carried in.\p"
	.string "I wonder what it saw in me. A dancer? Or\n"
	.string "an old man hiding behind his cape?\p"
	.string "Go gently. Bring it calm, and it will\n"
	.string "return calm.$"
```

</details>


#### Walking Wake

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Juan é o **campeão**, a luta logo antes do Walking Wake. A fala é sobre a criatura, sem dizer o nome dele.

O Juan é o professor: ensinou a água a dançar e ensinou o Wallace. Diante de uma criatura que dança a água desde antes de haver gente, ele percebe que não inventou nada; a água já dançava, ele só aprendeu a ficar parado para ver. A virada: o Wallace entendeu isso antes dele, e o Juan nunca disse isso ao aluno.

**Antes da luta**

> Did you see its mane? Water, flowing backward, like a cape in a gale.
>
> I spent a lifetime teaching water to move with grace. I taught Wallace, you know.
>
> That creature was doing it before there was anyone to teach.
>
> Aahaha! How humbling. How marvelous! Come!

**Derrota**

> Aahahaha! Out-danced twice in one day.

**Depois da luta**

> A teacher likes to believe he invented something.
>
> But the water was already dancing. I only learned to stand still long enough to see it.
>
> Wallace understood that before I did. I have never told him so.
>
> Go on. It is waiting in the rain, and it does not like to wait.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_WalkingWake_ChampionIntro:
	.string "Did you see its mane? Water, flowing\n"
	.string "backward, like a cape in a gale.\p"
	.string "I spent a lifetime teaching water to\n"
	.string "move with grace. I taught Wallace, you\l"
	.string "know.\p"
	.string "That creature was doing it before\n"
	.string "there was anyone to teach.\p"
	.string "Aahaha! How humbling. How marvelous!\n"
	.string "Come!$"

Nexus_Text_Juan_WalkingWake_ChampionDefeat:
	.string "Aahahaha! Out-danced twice in one day.$"

Nexus_Text_Juan_WalkingWake_ChampionAfter:
	.string "{SPEAKER NAME_JUAN}A teacher likes to believe he invented\n"
	.string "something.\p"
	.string "But the water was already dancing. I\n"
	.string "only learned to stand still long enough\l"
	.string "to see it.\p"
	.string "Wallace understood that before I did.\n"
	.string "I have never told him so.\p"
	.string "Go on. It is waiting in the rain, and it\n"
	.string "does not like to wait.$"
```

</details>


Falante novo: `SP_NAME_JUAN` (ainda não existe em `include/constants/speaker_names.h`).
