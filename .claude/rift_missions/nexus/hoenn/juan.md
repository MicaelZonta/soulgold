# Juan

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Juan — Água** (Hoenn · Líderes de Ginásio) — mentor de Wallace e Líder de Sootopolis em *Emerald*.

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

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_JUAN` = **1023** (flag de batalha `0x8FF`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Juan_Fight`; campeão: `Nexus_EventScript_Juan_TapuFini_ChampionFight` (para Tapu Fini), `Nexus_EventScript_Juan_WalkingWake_ChampionFight` (para Walking Wake). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Juan.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_TapuFini_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_WalkingWake_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Juan_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código). Nenhuma cita o lugar nem a criatura do dia.

**Variação 2** — provocação e ofício: o Juan entrega o segredo da capa (ela chega meio tempo depois do dançarino, e a plateia olha para ela e esquece as mãos). Humor de mágico que ensina o truque e desafia o jogador a não cair nele.

**Antes da luta**

> Ah! Do not mind the cape. It is not for warmth. It is for the turn.
>
> A cape arrives half a beat after the dancer. The audience watches it, and forgets to watch my hands.
>
> That is the whole secret of an illusion. Keep it, please. I have plenty.
>
> Now! Watch my hands, if you can!

**Derrota**

> Aahahaha! You watched my hands. How very rude, and how very right.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_Intro2:
	.string "Ah! Do not mind the cape. It is not for\n"
	.string "warmth. It is for the turn.\p"
	.string "A cape arrives half a beat after the\n"
	.string "dancer. The audience watches it, and\l"
	.string "forgets to watch my hands.\p"
	.string "That is the whole secret of an illusion.\n"
	.string "Keep it, please. I have plenty.\p"
	.string "Now! Watch my hands, if you can!$"

Nexus_Text_Juan_Defeat2:
	.string "Aahahaha! You watched my hands. How\n"
	.string "very rude, and how very right.$"
```

</details>

**Variação 3** — o que ele perdeu ([R21](../NEXUS_REGRAS.md)): o Juan pergunta se o jogador é aluno dele. No fragmento dele todos os alunos o superaram e foram ser Campeões em outro lugar; ser superado é lindo e deixa um silêncio. Serve com ou sem o jogador conhecer o Wallace.

**Antes da luta**

> Forgive an old man a question. Are you, perhaps, one of my students?
>
> No? A pity. I had so many once. Where I come from, they all left to become Champions somewhere else.
>
> It is a lovely thing, to be surpassed. It is also rather quiet afterward.
>
> Aahaha! Enough! Come and fill the quiet with me!

**Derrota**

> Aahahaha! Splendid. You would have been my finest student, and the quickest to leave.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_Intro3:
	.string "Forgive an old man a question. Are you,\n"
	.string "perhaps, one of my students?\p"
	.string "No? A pity. I had so many once. Where I\n"
	.string "come from, they all left to become\l"
	.string "Champions somewhere else.\p"
	.string "It is a lovely thing, to be surpassed.\n"
	.string "It is also rather quiet afterward.\p"
	.string "Aahaha! Enough! Come and fill the quiet\n"
	.string "with me!$"

Nexus_Text_Juan_Defeat3:
	.string "Aahahaha! Splendid. You would have\n"
	.string "been my finest student, and the\l"
	.string "quickest to leave.$"
```

</details>


### Diálogo associado ao lendário

#### Tapu Fini

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Juan_TapuFini_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela; para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código).

**Variação 2** — humor: o Juan tentou se apresentar para a névoa, com número completo. Ela não aplaudiu; lavou o ruge do rosto dele e foi embora. A plateia mais honesta em cinquenta anos. O conselho: entrar sem nada pintado.

**Antes da luta**

> I confess I tried to perform for the mist. A full routine: the spiral, the bow, the cape.
>
> It did not applaud. It simply washed the rouge off my cheeks and drifted away.
>
> In fifty years, no audience has ever been so honest with me.
>
> Aahaha! Let us see if you are kinder!

**Derrota**

> Aahahaha… no. No kinder at all.

**Depois da luta**

> The guardian of that island is not cruel, you know. It is only exact.
>
> It heals what is calm. It does not heal what is pretending to be calm.
>
> I learned that with my cheeks bare and my cape soaked through.
>
> Go in with nothing painted on. It is far less tiring.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_TapuFini_ChampionIntro2:
	.string "I confess I tried to perform for the\n"
	.string "mist. A full routine: the spiral, the\l"
	.string "bow, the cape.\p"
	.string "It did not applaud. It simply washed\n"
	.string "the rouge off my cheeks and drifted\l"
	.string "away.\p"
	.string "In fifty years, no audience has ever\n"
	.string "been so honest with me.\p"
	.string "Aahaha! Let us see if you are kinder!$"

Nexus_Text_Juan_TapuFini_ChampionDefeat2:
	.string "Aahahaha… no. No kinder at all.$"

Nexus_Text_Juan_TapuFini_ChampionAfter2:
	.string "{SPEAKER NAME_JUAN}The guardian of that island is not\n"
	.string "cruel, you know. It is only exact.\p"
	.string "It heals what is calm. It does not heal\n"
	.string "what is pretending to be calm.\p"
	.string "I learned that with my cheeks bare and\n"
	.string "my cape soaked through.\p"
	.string "Go in with nothing painted on. It is far\n"
	.string "less tiring.$"
```

</details>

**Variação 3** — dúvida e espelho: quando se assusta, a guardiã se fecha numa concha de pedra e deixa a névoa falar. O Juan reconhece o truque (capa, risada, chapéu). A virada: a concha não é armadura, é cortina; não se bate, espera-se o bis.

**Antes da luta**

> When it is frightened, it shuts itself in a shell of stone and lets the fog do the talking.
>
> I know that trick. I have a cape, a laugh, and a very large hat for the same purpose.
>
> We are two old performers, it and I, hiding in plain sight.
>
> Aahaha! Come, find me in the fog!

**Derrota**

> Aahahaha! Found. How very embarrassing.

**Depois da luta**

> A secret between performers. That shell is not armor. It is a curtain.
>
> It closes when it cannot bear to be looked at any longer.
>
> If it shuts itself away when you arrive, do not knock. Wait, be quiet, and let it choose the encore.
>
> Aahaha… I waited once. It was the best seat in the house.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_TapuFini_ChampionIntro3:
	.string "When it is frightened, it shuts itself\n"
	.string "in a shell of stone and lets the fog do\l"
	.string "the talking.\p"
	.string "I know that trick. I have a cape, a\n"
	.string "laugh, and a very large hat for the\l"
	.string "same purpose.\p"
	.string "We are two old performers, it and I,\n"
	.string "hiding in plain sight.\p"
	.string "Aahaha! Come, find me in the fog!$"

Nexus_Text_Juan_TapuFini_ChampionDefeat3:
	.string "Aahahaha! Found. How very\n"
	.string "embarrassing.$"

Nexus_Text_Juan_TapuFini_ChampionAfter3:
	.string "{SPEAKER NAME_JUAN}A secret between performers. That\n"
	.string "shell is not armor. It is a curtain.\p"
	.string "It closes when it cannot bear to be\n"
	.string "looked at any longer.\p"
	.string "If it shuts itself away when you\n"
	.string "arrive, do not knock. Wait, be quiet,\l"
	.string "and let it choose the encore.\p"
	.string "Aahaha… I waited once. It was the best\n"
	.string "seat in the house.$"
```

</details>


#### Walking Wake

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Juan_WalkingWake_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela; para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código).

**Variação 2** — lembrança engraçada: o Juan pôs o pé numa pegada e o sapato coube num dedo só; riu tanto que caiu no lago, e a criatura parou para olhar. Depois da luta, o elo com a lenda da fera do vento norte que purifica a água (sem nome): toda lenda foi bicho selvagem um dia.

**Antes da luta**

> Its footprints in the mud were still filling with water. I put my own foot in one.
>
> My whole shoe fit inside a single toe. I laughed so hard I fell into the lake.
>
> It stopped running to look at me. I believe it had never seen anything so ridiculous.
>
> Aahaha! My finest performance! Come!

**Derrota**

> Aahahaha! Into the lake again, it seems.

**Depois da luta**

> There is an old story of a beast that runs on the north wind and makes dirty water clean.
>
> I think that creature is the story before anyone told it. Rough, and wild, and in no hurry to be pure.
>
> Every legend was a wild thing once. Even the elegant ones.
>
> Go. Laugh if you fall in. It likes that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_WalkingWake_ChampionIntro2:
	.string "Its footprints in the mud were still\n"
	.string "filling with water. I put my own foot in\l"
	.string "one.\p"
	.string "My whole shoe fit inside a single toe. I\n"
	.string "laughed so hard I fell into the lake.\p"
	.string "It stopped running to look at me. I\n"
	.string "believe it had never seen anything so\l"
	.string "ridiculous.\p"
	.string "Aahaha! My finest performance! Come!$"

Nexus_Text_Juan_WalkingWake_ChampionDefeat2:
	.string "Aahahaha! Into the lake again, it\n"
	.string "seems.$"

Nexus_Text_Juan_WalkingWake_ChampionAfter2:
	.string "{SPEAKER NAME_JUAN}There is an old story of a beast that\n"
	.string "runs on the north wind and makes dirty\l"
	.string "water clean.\p"
	.string "I think that creature is the story\n"
	.string "before anyone told it. Rough, and wild,\l"
	.string "and in no hurry to be pure.\p"
	.string "Every legend was a wild thing once.\n"
	.string "Even the elegant ones.\p"
	.string "Go. Laugh if you fall in. It likes that.$"
```

</details>

**Variação 3** — ofício e pecado de professor: o Juan tenta marcar o compasso da criatura (ela corre em três, uma valsa mais velha que qualquer salão) e erra sempre, porque insiste num quarto tempo que não existe. Professor quer explicar cada passo; a criatura nunca explicou nada.

**Antes da luta**

> I have been trying to keep time with it. It runs in the rain, and the rain runs in threes.
>
> One, two, three. One, two, three. A waltz older than any ballroom!
>
> I miss the fourth beat every time. There is no fourth beat. I keep adding one.
>
> Aahaha! Perhaps you hear it better. Shall we dance?

**Derrota**

> Aahahaha! Ah, you heard it. One, two, three.

**Depois da luta**

> A teacher adds beats. That is the sin of teachers. We want every step explained.
>
> That creature has never explained a thing. It simply runs, and the lake follows.
>
> Do not count when you face it. Counting is how I fell behind.
>
> Listen for the three, and go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Juan_WalkingWake_ChampionIntro3:
	.string "I have been trying to keep time with it.\n"
	.string "It runs in the rain, and the rain runs in\l"
	.string "threes.\p"
	.string "One, two, three. One, two, three. A waltz\n"
	.string "older than any ballroom!\p"
	.string "I miss the fourth beat every time.\n"
	.string "There is no fourth beat. I keep adding\l"
	.string "one.\p"
	.string "Aahaha! Perhaps you hear it better.\n"
	.string "Shall we dance?$"

Nexus_Text_Juan_WalkingWake_ChampionDefeat3:
	.string "Aahahaha! Ah, you heard it. One, two,\n"
	.string "three.$"

Nexus_Text_Juan_WalkingWake_ChampionAfter3:
	.string "{SPEAKER NAME_JUAN}A teacher adds beats. That is the sin\n"
	.string "of teachers. We want every step\l"
	.string "explained.\p"
	.string "That creature has never explained a\n"
	.string "thing. It simply runs, and the lake\l"
	.string "follows.\p"
	.string "Do not count when you face it.\n"
	.string "Counting is how I fell behind.\p"
	.string "Listen for the three, and go.$"
```

</details>


Falante novo: `SP_NAME_JUAN` (ainda não existe em `include/constants/speaker_names.h`).
