# Lance

**Região da ficha:** Kanto

Aparece no checklist como:

- **Lance — Dragão** (Kanto · Elite Four e Campeões) — mestre de dragões que posteriormente se torna Campeão de Johto.
- **Lance — Campeão** (Johto · Elite Four e Campeão) — mestre de Pokémon Dragão e principal Campeão de Johto.

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
| `OBJ_EVENT_GFX_LANCE` | `graphics/object_events/pics/people/elite_four/lance.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_CHAMPION_LANCE` | `graphics/trainers/front_pics/champion_lance.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_LANCE` | `graphics/field_mugshots/lance.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LANCE_1` | 249 | 0x5F9 | Baxcalibur Lv70, Dragonite Lv71, Exeggutor-Alola Lv71, Hydrapple Lv71, Dragapult Lv71, Archaludon Lv71 · *dupla* · VS: Purple | `PokemonLeague_ChampionsRoom`, `src/battle_dome.c`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_LANCE_2` | 250 | 0x5FA | Salamence Lv69, Dragonite Lv68, Gyarados Lv69, Charizard Lv68, Aerodactyl Lv69, Altaria Lv70 · VS: Purple | `PokemonLeague_ChampionsRoom`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_LANCE` | 877 | 0x86D | Baxcalibur Lv85, Dragonite Lv86, Exeggutor-Alola Lv86, Hydrapple Lv86, Dragapult Lv86, Archaludon Lv86 · *dupla* · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_LANCE` = **995** (flag de batalha `0x8E3`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Lance_Fight`; campeão: `Nexus_EventScript_Lance_Rayquaza_ChampionFight` (para Rayquaza), `Nexus_EventScript_Lance_GougingFire_ChampionFight` (para Gouging Fire). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Lance.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LANCE`, campeão de Rayquaza e Gouging Fire. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Rayquaza**, o dragão que vive acima do céu: o único que o mestre dos dragões não alcança. Semi-lendário **Gouging Fire**, o Paradoxo Fogo/Dragão de que ele também é campeão. Mega **Dragonite** (Dragotite), o ás de sempre (três Dragonite no time de HGSS). Mais **Gyarados** (o Lance chega em Johto investigando o Gyarados vermelho do Lake of Rage), **Aerodactyl** (do time dele em Kanto e Johto) e **Archaludon** (do time dele neste hack, que segura Fada e Gelo pelos dragões). Rayquaza sem Dragon Ascent de propósito: a vaga de Mega é do Dragonite. O Air Lock apaga o clima dos dois lados, e o Gouging Fire liga o Protosynthesis pela Booster Energy, sem precisar de sol.

*Plano (Singles):* Aerodactyl de Sash põe Stealth Rock e Taunt; Gyarados entra com Intimidate e Thunder Wave; a Mega Dragonite sobe com Dragon Dance atrás do Multiscale e fecha com Extreme Speed; Rayquaza de Life Orb e Gouging Fire (Dragon Dance) são a segunda onda.

*Plano (Doubles):* Aerodactyl abre com Tailwind e Rock Slide, Gyarados com Intimidate; Gouging Fire usa Breaking Swipe (acerta os dois e baixa o Ataque) e Burning Bulwark; Rayquaza e Gyarados têm Protect; Archaludon de Assault Vest e Stamina aguenta o golpe de Fada ou de Gelo que o jogador guardou para os dragões.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Rayquaza | Life Orb | Air Lock | Naive | Draco Meteor, Extreme Speed, Flamethrower, Protect |
| Gouging Fire | Booster Energy | Protosynthesis | Adamant | Flare Blitz, Breaking Swipe, Dragon Dance, Burning Bulwark |
| Dragonite | Dragotite | Multiscale | Adamant | Dragon Dance, Extreme Speed, Scale Shot, Fire Punch |
| Gyarados | Sitrus Berry | Intimidate | Adamant | Waterfall, Thunder Wave, Taunt, Protect |
| Aerodactyl | Focus Sash | Unnerve | Jolly | Stealth Rock, Tailwind, Rock Slide, Taunt |
| Archaludon | Assault Vest | Stamina | Modest | Flash Cannon, Draco Meteor, Thunderbolt, Body Press |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_LANCE ===
Name: Lance
Class: Champion
Pic: Champion Lance
Gender: Male
Music: Hg Champion
Double Battle: Yes
AI: Smart Trainer

Rayquaza @ Life Orb
Naive Nature
Level: 100
Ability: Air Lock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Extreme Speed
- Flamethrower
- Protect

Gouging Fire @ Booster Energy
Adamant Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Breaking Swipe
- Dragon Dance
- Burning Bulwark

Dragonite @ Dragotite
Adamant Nature
Level: 100
Ability: Multiscale
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Extreme Speed
- Scale Shot
- Fire Punch

Gyarados @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Waterfall
- Thunder Wave
- Taunt
- Protect

Aerodactyl @ Focus Sash
Jolly Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Tailwind
- Rock Slide
- Taunt

Archaludon @ Assault Vest
Modest Nature
Level: 100
Ability: Stamina
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flash Cannon
- Draco Meteor
- Thunderbolt
- Body Press
```

</details>


### Lendário associado

#### Rayquaza

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Rayquaza_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Rayquaza**. Lance é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lance, mestre dos dragões do clã de Blackthorn, Campeão da Liga e primo da Clair. Voa no Dragonite e usa capa.

**A criatura.** Rayquaza vive há centenas de milhões de anos na camada de ozônio, comendo a água e as partículas da atmosfera (e meteoroides). Desce do céu para apartar Kyogre e Groudon quando os dois brigam, e volta para cima.

**O fragmento.** Uma torre sem base e sem topo, acima das nuvens. Lá em cima o céu é escuro ao meio-dia e uma poeira fina cai como neve: pó de estrela cadente. Alguma coisa aqui come o que cai do céu.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A tower with no bottom and no top.
>
> Above the clouds the sky was dark even at noon, and fine dust drifted down like snow.
>
> It tasted of iron. Something up here had been eating falling stars.

**Boss**

> A green line crossed the dark sky, turned, and came straight down.
>
> The dust stopped falling. It had all been swallowed.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-384. Sky High.
>
> A tower above the weather, and a Champion who flew up on his own dragon to meet it.
>
> What came back down with you fits in two hands. It still looks up. I have written that down.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Rayquaza_Arrival:
	.string "A tower with no bottom and no top.\p"
	.string "Above the clouds the sky was dark even\n"
	.string "at noon, and fine dust drifted down\l"
	.string "like snow.\p"
	.string "It tasted of iron. Something up here\n"
	.string "had been eating falling stars.$"

Nexus_Text_Rayquaza_Boss:
	.string "A green line crossed the dark sky,\n"
	.string "turned, and came straight down.\p"
	.string "The dust stopped falling. It had all\n"
	.string "been swallowed.$"

Nexus_Text_Rayquaza_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-384. Sky High.\p"
	.string "A tower above the weather, and a\n"
	.string "Champion who flew up on his own dragon\l"
	.string "to meet it.\p"
	.string "What came back down with you fits in\n"
	.string "two hands. It still looks up. I have\l"
	.string "written that down.$"
```

</details>

#### Gouging Fire

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_GougingFire_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Gouging Fire**. Lance é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lance, mestre dos dragões do clã de Blackthorn, que conhece a linhagem de cada dragão que treina.

**A criatura.** Gouging Fire é um Pokémon Paradoxo de Fogo/Dragão, da Area Zero de Paldea, parecido com uma versão antiga de um dos cães lendários. Há pouquíssimos relatos dele; os que existem falam de uma fera que derruba pilares de pedra com os chifres.

**O fragmento.** Um vale de antes de qualquer mapa: samambaias da altura de casas, vapor saindo das rachaduras do chão e dezenas de pilares de pedra, todos quebrados na mesma altura, como se tivessem levado uma chifrada.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A valley from before anyone drew maps.
>
> Ferns taller than houses. Steam rising from cracks in the ground. And stone pillars, dozens of them, all broken off at the same height.

**Boss**

> The ground was warm, then hot.
>
> Horns came through the steam first, low and burning, aimed at the last pillar still standing. Then at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-1020. Ancient Blaze.
>
> A valley that never was, and a dragon master who could not find its family line in any book.
>
> The fragment you brought home is warm to the touch and has no past at all. It will have to start one with you.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_GougingFire_Arrival:
	.string "A valley from before anyone drew maps.\p"
	.string "Ferns taller than houses. Steam rising\n"
	.string "from cracks in the ground. And stone\l"
	.string "pillars, dozens of them, all broken off\l"
	.string "at the same height.$"

Nexus_Text_GougingFire_Boss:
	.string "The ground was warm, then hot.\p"
	.string "Horns came through the steam first, low\n"
	.string "and burning, aimed at the last pillar\l"
	.string "still standing. Then at you.$"

Nexus_Text_GougingFire_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1020. Ancient Blaze.\p"
	.string "A valley that never was, and a dragon\n"
	.string "master who could not find its family\l"
	.string "line in any book.\p"
	.string "The fragment you brought home is warm\n"
	.string "to the touch and has no past at all. It\l"
	.string "will have to start one with you.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lance_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lance cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I've flown over a lot of strange places on Dragonite's back. This one isn't on any map.
>
> The Elder of the Dragon's Den asks every dragon Trainer the same question: what matters most to a Trainer?
>
> I've answered it a dozen times. The answer keeps changing. Let's find out what it is today!

**Derrota**

> …Hm. That's the answer I'll give next year.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lance_Intro:
	.string "I've flown over a lot of strange places\n"
	.string "on Dragonite's back. This one isn't on\l"
	.string "any map.\p"
	.string "The Elder of the Dragon's Den asks\n"
	.string "every dragon Trainer the same\l"
	.string "question: what matters most to a\l"
	.string "Trainer?\p"
	.string "I've answered it a dozen times. The\n"
	.string "answer keeps changing. Let's find out\l"
	.string "what it is today!$"

Nexus_Text_Lance_Defeat:
	.string "…Hm. That's the answer I'll give next\n"
	.string "year.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lance é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela.

#### Rayquaza

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lance_Rayquaza_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Lance passou a vida acreditando que os dragões dele eram os que voavam mais alto. Viu o Dragonite subir até faltar ar, e a criatura continuava acima, comendo pedras que caíam do céu. Lá em cima ele é só um homem de capa. O que ela revela: ela só desce quando dois gigantes brigam pelo mundo, apaga a briga e vai embora sem esperar agradecimento, e o Lance admite que é isso que um Campeão devia ser, e que às vezes ele esquece. Termina com o aviso de que ninguém doma o céu (casa com o R17: o jogador leva um fragmento, não a criatura).

**Antes da luta**

> I used to think my dragons flew higher than any Pokémon alive.
>
> Then this one passed over us. Dragonite climbed until it couldn't breathe, and the thing was still above us, eating stones that fell from the sky.
>
> People call me a master of dragons. Up there, I'm just a man in a cape. Show me what you've got!

**Derrota**

> Beaten from below. That's a first.

**Depois da luta**

> It only comes down when two giants start fighting over the world. It ends the fight and flies home. Nobody ever thanks it.
>
> I think that's what a Champion is supposed to be. I forget, sometimes. The cape helps people see me. It doesn't make me better.
>
> Go on up. If it lets you close, don't call it tamed. Nobody tames the sky.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lance_Rayquaza_ChampionIntro:
	.string "I used to think my dragons flew higher\n"
	.string "than any Pokémon alive.\p"
	.string "Then this one passed over us.\n"
	.string "Dragonite climbed until it couldn't\l"
	.string "breathe, and the thing was still above\l"
	.string "us, eating stones that fell from the\l"
	.string "sky.\p"
	.string "People call me a master of dragons. Up\n"
	.string "there, I'm just a man in a cape. Show me\l"
	.string "what you've got!$"

Nexus_Text_Lance_Rayquaza_ChampionDefeat:
	.string "Beaten from below. That's a first.$"

Nexus_Text_Lance_Rayquaza_ChampionAfter:
	.string "{SPEAKER NAME_LANCE}It only comes down when two giants\n"
	.string "start fighting over the world. It ends\l"
	.string "the fight and flies home. Nobody ever\l"
	.string "thanks it.\p"
	.string "I think that's what a Champion is\n"
	.string "supposed to be. I forget, sometimes.\l"
	.string "The cape helps people see me. It\l"
	.string "doesn't make me better.\p"
	.string "Go on up. If it lets you close, don't\n"
	.string "call it tamed. Nobody tames the sky.$"
```

</details>

#### Gouging Fire

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lance_GougingFire_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Lance sabe de cor a linhagem de todo dragão: Dratini até Dragonite, Bagon até Salamence, até onde vão os registros do clã. Esta criatura não está em nenhum: sem pais, sem filhotes, parece um palpite de alguém sobre o passado. E luta como dragão mesmo assim. A virada: ele cresceu achando que a linhagem fazia o dragão, e a criatura derrubou todos os pilares do vale sem ter nenhuma. A prima dele ia odiar. Ele gosta.

**Antes da luta**

> I know every dragon's line. Dratini to Dragonite, Bagon to Salamence, back as far as the clan's records go.
>
> The one in this valley isn't in any of them. No parents. No young. It looks like somebody's guess about the past.
>
> And it still fights like a dragon. Let's see if you do too!

**Derrota**

> No lineage on your side either. Just nerve. Well done.

**Depois da luta**

> My clan counts generations. Who trained whom, which Dratini came from which pool. I grew up thinking that was what made a dragon.
>
> That creature has none of it, and it gored through every pillar in this valley anyway.
>
> My cousin would hate it. I think I like it.
>
> Go. It won't care who your teacher was, either.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lance_GougingFire_ChampionIntro:
	.string "I know every dragon's line. Dratini to\n"
	.string "Dragonite, Bagon to Salamence, back as\l"
	.string "far as the clan's records go.\p"
	.string "The one in this valley isn't in any of\n"
	.string "them. No parents. No young. It looks\l"
	.string "like somebody's guess about the past.\p"
	.string "And it still fights like a dragon. Let's\n"
	.string "see if you do too!$"

Nexus_Text_Lance_GougingFire_ChampionDefeat:
	.string "No lineage on your side either. Just\n"
	.string "nerve. Well done.$"

Nexus_Text_Lance_GougingFire_ChampionAfter:
	.string "{SPEAKER NAME_LANCE}My clan counts generations. Who\n"
	.string "trained whom, which Dratini came from\l"
	.string "which pool. I grew up thinking that was\l"
	.string "what made a dragon.\p"
	.string "That creature has none of it, and it\n"
	.string "gored through every pillar in this\l"
	.string "valley anyway.\p"
	.string "My cousin would hate it. I think I like\n"
	.string "it.\p"
	.string "Go. It won't care who your teacher was,\n"
	.string "either.$"
```

</details>

Falante novo: `SP_NAME_LANCE`.
