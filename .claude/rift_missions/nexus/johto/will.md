# Will

**Região da ficha:** Johto

Aparece no checklist como:

- **Will — Psíquico** (Johto · Elite Four e Campeão) — ilusionista viajante que aperfeiçoou suas habilidades pelo mundo.

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

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_WILL` = **1009** (flag de batalha `0x8F1`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Will_Fight`; campeão: `Nexus_EventScript_Will_IronCrown_ChampionFight` (para Iron Crown), `Nexus_EventScript_Will_Calyrex_ChampionFight` (para Calyrex). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Will.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Calyrex_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronCrown_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Will_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas para as **quatro primeiras salas** ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. A variação 1 é a de cima, que já está no jogo; o sorteio de qual variação toca ainda não existe no código.

**Variação 2** — humor de ilusionista: o truque da Poké Ball escolhida. No fim ele revela qual era, e continua "nunca errado, só derrotado".

**Antes da luta**

> Pick a card. …Ah, you have no cards. Pick a Poké Ball, then. Any one of mine.
>
> Remember it. Now keep your eye on it while we battle.
>
> At the end, I'll tell you which one it was. I am never wrong. Begin!

**Derrota**

> It was the third one. …You see? Never wrong. Only defeated.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_Intro2:
	.string "Pick a card. …Ah, you have no cards. Pick\n"
	.string "a Poké Ball, then. Any one of mine.\p"
	.string "Remember it. Now keep your eye on it\n"
	.string "while we battle.\p"
	.string "At the end, I'll tell you which one it\n"
	.string "was. I am never wrong. Begin!$"

Nexus_Text_Will_Defeat2:
	.string "It was the third one. …You see? Never\n"
	.string "wrong. Only defeated.$"
```

</details>

**Variação 3** — a lembrança da máscara: ganhou de um velho cuja máscara era de gelo (o **Pryce** de outro fragmento; as crianças mascaradas de Pokémon Adventures). R21 com leveza.

**Antes da luta**

> I was given this mask when I was very small. By an old man whose own mask was made of ice.
>
> He said a mask lets you become someone who doesn't lose. He was wrong about that.
>
> …But it does let you pretend, which is nearly as good. Shall we?

**Derrota**

> …Nearly as good. Not quite.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_Intro3:
	.string "I was given this mask when I was very\n"
	.string "small. By an old man whose own mask was\l"
	.string "made of ice.\p"
	.string "He said a mask lets you become someone\n"
	.string "who doesn't lose. He was wrong about\l"
	.string "that.\p"
	.string "…But it does let you pretend, which is\n"
	.string "nearly as good. Shall we?$"

Nexus_Text_Will_Defeat3:
	.string "…Nearly as good. Not quite.$"
```

</details>

### Diálogo associado ao lendário

#### Calyrex

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Will_Calyrex_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — a reverência: o Will se curvou ao rei pequeno até a neve, e o rei ficou surpreso. Reis e artistas precisam disso. Depois: o rei perdeu os corcéis e escuta cascos; o Will imitou o som e foi a primeira plateia que ele não enganou.

**Antes da luta**

> I bowed to the little king when I arrived. Properly. All the way down to the snow.
>
> It looked very surprised. I don't think anyone has bowed to it in a long, long time.
>
> Kings need that, you know. So do performers. …You may bow to me after I win!

**Derrota**

> Well. I suppose I'll be the one bowing.

**Depois da luta**

> It lost its steeds, did you know? One of frost, one of shadow. It sits there listening for hooves.
>
> I tried to imitate the sound. Snow, two coconut shells, a very good ear.
>
> It wasn't fooled. The first audience I have never fooled. Go, and bow first.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_Calyrex_ChampionIntro2:
	.string "I bowed to the little king when I\n"
	.string "arrived. Properly. All the way down to\l"
	.string "the snow.\p"
	.string "It looked very surprised. I don't think\n"
	.string "anyone has bowed to it in a long, long\l"
	.string "time.\p"
	.string "Kings need that, you know. So do\n"
	.string "performers. …You may bow to me after I\l"
	.string "win!$"

Nexus_Text_Will_Calyrex_ChampionDefeat2:
	.string "Well. I suppose I'll be the one bowing.$"

Nexus_Text_Will_Calyrex_ChampionAfter2:
	.string "{SPEAKER NAME_WILL}It lost its steeds, did you know? One of\n"
	.string "frost, one of shadow. It sits there\l"
	.string "listening for hooves.\p"
	.string "I tried to imitate the sound. Snow, two\n"
	.string "coconut shells, a very good ear.\p"
	.string "It wasn't fooled. The first audience I\n"
	.string "have never fooled. Go, and bow first.$"
```

</details>

**Variação 3** — a cenoura: a aldeia deixava cenouras para o rei (as Shaderoot/Iceroot Carrots da Crown Tundra). O Will comprou um saco e não teve coragem de deixar. Depois deixou: o rei plantou.

**Antes da luta**

> In the village below the throne, people used to leave carrots for their king. Only the finest.
>
> Nobody leaves them anymore. I bought a whole sack at a market three worlds ago.
>
> …I haven't had the nerve to leave one. What if it doesn't want me? Battle first.

**Derrota**

> …Fine. I'll leave the carrot.

**Depois da luta**

> I left the carrot. It didn't eat it. It planted it.
>
> There is a very small green thing growing in the snow now, next to the stump.
>
> I suppose that is what believing in something looks like. Go. Take your time.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_Calyrex_ChampionIntro3:
	.string "In the village below the throne, people\n"
	.string "used to leave carrots for their king.\l"
	.string "Only the finest.\p"
	.string "Nobody leaves them anymore. I bought a\n"
	.string "whole sack at a market three worlds\l"
	.string "ago.\p"
	.string "…I haven't had the nerve to leave one.\n"
	.string "What if it doesn't want me? Battle\l"
	.string "first.$"

Nexus_Text_Will_Calyrex_ChampionDefeat3:
	.string "…Fine. I'll leave the carrot.$"

Nexus_Text_Will_Calyrex_ChampionAfter3:
	.string "{SPEAKER NAME_WILL}I left the carrot. It didn't eat it. It\n"
	.string "planted it.\p"
	.string "There is a very small green thing\n"
	.string "growing in the snow now, next to the\l"
	.string "stump.\p"
	.string "I suppose that is what believing in\n"
	.string "something looks like. Go. Take your time.$"
```

</details>

#### Iron Crown

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Will_IronCrown_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — o reflexo nas lâminas: o Will olhou, claro, e se viu daqui a dez anos, sem máscara, se apresentando para cadeiras vazias. A criatura mostra *um* futuro, do qual foi feita, não o seu.

**Antes da luta**

> Every blade out there shows you a little later. I looked, of course. Who wouldn't?
>
> I saw myself in ten years. No mask. Still performing. Nobody in the seats.
>
> …Perhaps the blades lie. Help me find out.

**Derrota**

> You were in the seats. That's something.

**Depois da luta**

> The metal one doesn't show your future. It shows a future. It was built from one.
>
> Somewhere, someone made a crown with nobody under it and called it a king.
>
> Don't let it tell you who you'll become. That's my job, and I'm off duty.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_IronCrown_ChampionIntro2:
	.string "Every blade out there shows you a\n"
	.string "little later. I looked, of course. Who\l"
	.string "wouldn't?\p"
	.string "I saw myself in ten years. No mask. Still\n"
	.string "performing. Nobody in the seats.\p"
	.string "…Perhaps the blades lie. Help me find\n"
	.string "out.$"

Nexus_Text_Will_IronCrown_ChampionDefeat2:
	.string "You were in the seats. That's\n"
	.string "something.$"

Nexus_Text_Will_IronCrown_ChampionAfter2:
	.string "{SPEAKER NAME_WILL}The metal one doesn't show your\n"
	.string "future. It shows a future. It was built\l"
	.string "from one.\p"
	.string "Somewhere, someone made a crown with\n"
	.string "nobody under it and called it a king.\p"
	.string "Don't let it tell you who you'll become.\n"
	.string "That's my job, and I'm off duty.$"
```

</details>

**Variação 3** — humor e ciúme de ofício: a criatura copiou a reverência, o floreio da capa e a entrada que ele levou vinte anos para aperfeiçoar. O que ela não copia: o nervosismo.

**Antes da luta**

> It copied my bow. Perfectly. Then my cape flourish. Then my entrance.
>
> I have spent twenty years perfecting that entrance. It learned it in a minute.
>
> …I am not jealous. I am professionally concerned. Let's battle.

**Derrota**

> It will probably copy how I lost, too. Wonderful.

**Depois da luta**

> Here's what it couldn't copy. When I bow, I'm nervous. Every single time.
>
> It bowed with nothing behind it. No nerves, no hope, no one.
>
> Go and face it. If it copies you, be nervous. It can't do that part.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Will_IronCrown_ChampionIntro3:
	.string "It copied my bow. Perfectly. Then my\n"
	.string "cape flourish. Then my entrance.\p"
	.string "I have spent twenty years perfecting\n"
	.string "that entrance. It learned it in a\l"
	.string "minute.\p"
	.string "…I am not jealous. I am professionally\n"
	.string "concerned. Let's battle.$"

Nexus_Text_Will_IronCrown_ChampionDefeat3:
	.string "It will probably copy how I lost, too.\n"
	.string "Wonderful.$"

Nexus_Text_Will_IronCrown_ChampionAfter3:
	.string "{SPEAKER NAME_WILL}Here's what it couldn't copy. When I\n"
	.string "bow, I'm nervous. Every single time.\p"
	.string "It bowed with nothing behind it. No\n"
	.string "nerves, no hope, no one.\p"
	.string "Go and face it. If it copies you, be\n"
	.string "nervous. It can't do that part.$"
```

</details>

Falante novo: `SP_NAME_WILL` (o `_ChampionAfter` usa `{SPEAKER NAME_WILL}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
