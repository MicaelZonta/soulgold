# Will

**Região da ficha:** Johto

Aparece no checklist como:

- **Will — Psíquico** (Johto · Elite Four e Campeão) — ilusionista viajante que aperfeiçoou suas habilidades pelo mundo.

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
| `OBJ_EVENT_GFX_WILL` | `graphics/object_events/pics/people/elite_four/will.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_WILL` | `graphics/trainers/front_pics/elite_four_will.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_WILL` | `graphics/field_mugshots/will.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WILL_2` | 376 | 0x678 | Farigiraf Lv85, Reuniclus Lv85, Espeon Lv85, Slowbro Lv85, Braviary-Hisui Lv85, Alakazam Lv85 · VS: Purple | `PokemonLeague_WillsRoom`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_WILL_1` | 736 | 0x7E0 | Farigiraf Lv68, Reuniclus Lv69, Espeon Lv68, Slowbro Lv68, Braviary-Hisui Lv68, Alakazam Lv69 · *dupla* · VS: Purple | `PokemonLeague_WillsRoom` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_WILL`, campeão do Calyrex e do Iron Crown. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Lunala**, a besta que chama a lua e atravessa buracos entre mundos: o ilusionista que treinou pelo mundo inteiro com um Psíquico/Fantasma que esconde tudo atrás do Shadow Shield. Semi-lendário **Iron Crown**, o Paradoxo do qual ele é campeão: uma máscara de metal sem ninguém por trás, o medo dele. Mega **Alakazam** (Psychite), do time dele na campanha. Mais **Xatu**, o ás dele em Gold/Silver/Crystal, e **Farigiraf** e **Slowbro**, da campanha.

*Plano:* a ilusão é o controle de velocidade. O jogador nunca sabe para que lado o tempo vai correr: o Xatu dá Tailwind aos rápidos (Lunala, Alakazam, Iron Crown), ou Farigiraf e Slowbro armam Trick Room para os lentos.
*Plano (Singles):* Xatu de Light Clay arma Reflect e Light Screen, o Magic Bounce devolve hazards e status, e o U-turn traz o Lunala para o Calm Mind; a Mega Alakazam e o Iron Crown (Booster Energy) limpam. Se o jogador for mais rápido, o Slowbro (Regenerator) inverte com Trick Room.
*Plano (Doubles):* Farigiraf com Armor Tail bloqueia Fake Out e Sucker Punch contra os dois lados do Will (a prioridade de Sombrio é o terror de todo time Psíquico) e dá Helping Hand ou Trick Room; Hyper Voice e Dazzling Gleam acertam os dois oponentes; Xatu põe Tailwind quando o Trick Room não compensa.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Lunala | Leftovers | Shadow Shield | Timid | Moongeist Beam, Psyshock, Moonblast, Calm Mind |
| Iron Crown | Booster Energy | Quark Drive | Timid | Tachyon Cutter, Focus Blast, Flash Cannon, Volt Switch |
| Alakazam | Psychite | Magic Guard | Timid | Psychic, Focus Blast, Shadow Ball, Dazzling Gleam |
| Farigiraf | Sitrus Berry | Armor Tail | Quiet | Hyper Voice, Psychic, Trick Room, Helping Hand |
| Xatu | Light Clay | Magic Bounce | Timid | Tailwind, Reflect, Light Screen, U-turn |
| Slowbro | Colbur Berry | Regenerator | Relaxed | Scald, Psyshock, Slack Off, Trick Room |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_WILL ===
Name: Will
Class: Elite Four
Pic: Elite Four Will
Gender: Male
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Lunala @ Leftovers
Timid Nature
Level: 100
Ability: Shadow Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moongeist Beam
- Psyshock
- Moonblast
- Calm Mind

Iron Crown @ Booster Energy
Timid Nature
Level: 100
Ability: Quark Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tachyon Cutter
- Focus Blast
- Flash Cannon
- Volt Switch

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

Farigiraf @ Sitrus Berry
Quiet Nature
Level: 100
Ability: Armor Tail
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Trick Room
- Helping Hand

Xatu @ Light Clay
Timid Nature
Level: 100
Ability: Magic Bounce
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Reflect
- Light Screen
- U-turn

Slowbro @ Colbur Berry
Relaxed Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Psyshock
- Slack Off
- Trick Room
```

</details>

### Lendário associado

#### Calyrex

📝 **Proposta de 27/09/2026, aguardando o autor.** **Calyrex**. Will é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Will, o Psíquico da Elite Four de Johto, mascarado, que "treinou pelo mundo inteiro" até ser aceito na Liga. Um ilusionista: a máscara é parte do número.

**A criatura.** Calyrex (Psíquico/Planta), o Pokémon Rei, piedoso, capaz de curar e fazer crescer as plantas. Reinou sobre Galar em tempos antigos. Conforme o povo o esqueceu, o poder dele minguou e ele perdeu o corcel. Mundo em Sword/Shield: Crown Tundra.

**O fragmento.** Um campo de colheita debaixo de neve, as plantas secas de pé onde ninguém veio colher. No meio, um trono feito de um toco de árvore, e sobre ele uma coroa pequena demais para qualquer cabeça.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A harvest field under snow.
>
> The crops had died standing up, waiting for hands that never came to gather them.
>
> In the middle of the field was a tree stump carved into a throne. On it sat a crown, far too small for any head.

**Boss**

> The crown moved.
>
> Something small wore it, and the dead crops around the throne began, very slowly, to turn green.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-898. King.
>
> A kingdom with nobody left to believe in it, and a man in a mask who knows exactly how that works.
>
> What came back with you is small. So is every king, before anyone kneels.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Calyrex_Arrival:
	.string "A harvest field under snow.\p"
	.string "The crops had died standing up, waiting\n"
	.string "for hands that never came to gather\l"
	.string "them.\p"
	.string "In the middle of the field was a tree\n"
	.string "stump carved into a throne. On it sat a\l"
	.string "crown, far too small for any head.$"

Nexus_Text_Calyrex_Boss:
	.string "The crown moved.\p"
	.string "Something small wore it, and the dead\n"
	.string "crops around the throne began, very\l"
	.string "slowly, to turn green.$"

Nexus_Text_Calyrex_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-898. King.\p"
	.string "A kingdom with nobody left to believe in\n"
	.string "it, and a man in a mask who knows\l"
	.string "exactly how that works.\p"
	.string "What came back with you is small. So is\n"
	.string "every king, before anyone kneels.$"
```

</details>

#### Iron Crown

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Crown**. Will é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Will, o Psíquico da Elite Four de Johto, mascarado, que "treinou pelo mundo inteiro" até ser aceito na Liga. Um ilusionista: a máscara é parte do número.

**A criatura.** Iron Crown (Aço/Psíquico) é um Paradoxo: uma máquina que lembra uma lenda antiga, com a crista em forma de lâmina, vinda de um futuro possível pela máquina do tempo da Area Zero. Mundo em Scarlet/Violet (The Indigo Disk).

**O fragmento.** Um campo de lâminas de aço cravadas no chão em fileiras perfeitas, polidas como espelhos. Em cada uma você se vê um pouco mais tarde do que agora.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A field of steel blades, driven into the ground in perfect rows.
>
> Each one was polished to a mirror. In every blade you saw yourself, a little later than now.

**Boss**

> One of the mirrors moved.
>
> Its crown was a blade, and the face beneath it showed nothing at all. Not even you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1023. Paradox.
>
> A copy of an old legend, wearing a crown with nobody under it, and a man in a mask who checked, twice, that his own face was still there.
>
> What came back with you is small, and it hums. I have not worked out the song.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronCrown_Arrival:
	.string "A field of steel blades, driven into the\n"
	.string "ground in perfect rows.\p"
	.string "Each one was polished to a mirror. In\n"
	.string "every blade you saw yourself, a little\l"
	.string "later than now.$"

Nexus_Text_IronCrown_Boss:
	.string "One of the mirrors moved.\p"
	.string "Its crown was a blade, and the face\n"
	.string "beneath it showed nothing at all. Not\l"
	.string "even you.$"

Nexus_Text_IronCrown_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1023. Paradox.\p"
	.string "A copy of an old legend, wearing a crown\n"
	.string "with nobody under it, and a man in a\l"
	.string "mask who checked, twice, that his own\l"
	.string "face was still there.\p"
	.string "What came back with you is small, and it\n"
	.string "hums. I have not worked out the song.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Will cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Welcome. I am Will. I have trained all around the world… and now, it seems, beyond it.
>
> Do you know why I wear this mask? So that you look at it, and not at my hands.
>
> Too late. The battle has already begun.

**Derrota**

> I… I can't believe it. You were watching my hands.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_Intro:
	.string "Welcome. I am Will. I have trained all\n"
	.string "around the world… and now, it seems,\l"
	.string "beyond it.\p"
	.string "Do you know why I wear this mask? So\n"
	.string "that you look at it, and not at my\l"
	.string "hands.\p"
	.string "Too late. The battle has already begun.$"

Nexus_Text_Will_Defeat:
	.string "I… I can't believe it. You were watching\n"
	.string "my hands.$"
```

</details>


### Diálogo associado ao lendário

#### Calyrex

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Will é o **campeão**, a luta logo antes do Calyrex. A fala é sobre a criatura, sem dizer o nome dela.

O Will fala do Calyrex como de um colega de ofício: um rei que a região inteira reverenciava e que foi encolhendo, ano a ano, conforme o povo esquecia. Uma ilusão só dura enquanto alguém acredita, e o Will vive disso. A virada é a máscara: debaixo dela há só um garoto que treinou sozinho em cem cidades, e é a máscara que as pessoas lembram, não ele. O rei nunca teve máscara; quando o esqueceram, não sobrou nada para segurá-lo de pé. O pedido final é pequeno e sincero: lembre dele, mesmo pequeno.

**Antes da luta**

> Did you meet the little king? It sits on a stump in the snow, waiting for a harvest nobody plants.
>
> Once, a whole region knelt to it. Then people forgot, and every year it grew a little smaller.
>
> An illusion only lasts while someone believes in it. I would know. I have built a career on that.
>
> Come. Let me show you what I can make you believe.

**Derrota**

> …A trick needs an audience. You stopped believing in me.

**Depois da luta**

> Here is a secret. Under the mask there is only a boy who trained alone in a hundred towns.
>
> The mask is what people remember. The boy, nobody would.
>
> That king never had a mask. When they forgot it, there was nothing left to hold it up.
>
> Remember it for me, would you? Even small. Especially small.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_Calyrex_ChampionIntro:
	.string "Did you meet the little king? It sits on\n"
	.string "a stump in the snow, waiting for a\l"
	.string "harvest nobody plants.\p"
	.string "Once, a whole region knelt to it. Then\n"
	.string "people forgot, and every year it grew a\l"
	.string "little smaller.\p"
	.string "An illusion only lasts while someone\n"
	.string "believes in it. I would know. I have built\l"
	.string "a career on that.\p"
	.string "Come. Let me show you what I can make\n"
	.string "you believe.$"

Nexus_Text_Will_Calyrex_ChampionDefeat:
	.string "…A trick needs an audience. You stopped\n"
	.string "believing in me.$"

Nexus_Text_Will_Calyrex_ChampionAfter:
	.string "{SPEAKER NAME_WILL}Here is a secret. Under the mask there\n"
	.string "is only a boy who trained alone in a\l"
	.string "hundred towns.\p"
	.string "The mask is what people remember. The\n"
	.string "boy, nobody would.\p"
	.string "That king never had a mask. When they\n"
	.string "forgot it, there was nothing left to\l"
	.string "hold it up.\p"
	.string "Remember it for me, would you? Even\n"
	.string "small. Especially small.$"
```

</details>

#### Iron Crown

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Will é o **campeão**, a luta logo antes do Iron Crown. A fala é sobre a criatura, sem dizer o nome dela.

Para o Will, que vive de máscara, o Iron Crown é o primeiro disfarce que dá medo: copia com perfeição a pose de uma lenda antiga, mas não tem ninguém dentro da cópia. A virada: depois de vê-lo, o Will tirou a máscara só para conferir se o próprio rosto ainda estava lá, e ficou mais aliviado do que admite. Uma máscara só é espetáculo se tem alguém por trás; aquilo é só máscara. O conselho é de ilusionista: ele vai parecer o que você espera; não espere nada.

**Antes da luta**

> The metal one out there wears a crown shaped like a blade, and its face is a mirror.
>
> I watched it for an hour. It holds the pose of some ancient legend perfectly.
>
> But there is no one inside the copy. Only the pose.
>
> …It is the first mask that has ever frightened me. Let us begin.

**Derrota**

> You saw through the pose. Mine too, I suppose.

**Depois da luta**

> I took off my mask after I saw it. Just to check.
>
> My face was still there. I was more relieved than I would like to admit.
>
> A mask is only a performance if someone is behind it. That thing is all mask.
>
> Be careful. It will look like whatever you expect. So expect nothing.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_IronCrown_ChampionIntro:
	.string "The metal one out there wears a crown\n"
	.string "shaped like a blade, and its face is a\l"
	.string "mirror.\p"
	.string "I watched it for an hour. It holds the\n"
	.string "pose of some ancient legend perfectly.\p"
	.string "But there is no one inside the copy.\n"
	.string "Only the pose.\p"
	.string "…It is the first mask that has ever\n"
	.string "frightened me. Let us begin.$"

Nexus_Text_Will_IronCrown_ChampionDefeat:
	.string "You saw through the pose. Mine too, I\n"
	.string "suppose.$"

Nexus_Text_Will_IronCrown_ChampionAfter:
	.string "{SPEAKER NAME_WILL}I took off my mask after I saw it. Just\n"
	.string "to check.\p"
	.string "My face was still there. I was more\n"
	.string "relieved than I would like to admit.\p"
	.string "A mask is only a performance if someone\n"
	.string "is behind it. That thing is all mask.\p"
	.string "Be careful. It will look like whatever\n"
	.string "you expect. So expect nothing.$"
```

</details>

Falante novo: `SP_NAME_WILL` (o `_ChampionAfter` usa `{SPEAKER NAME_WILL}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
