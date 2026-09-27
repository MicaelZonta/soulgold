# Leaf

**Região da ficha:** Kanto

Aparece no checklist como:

- **Leaf** (Kanto · Rivais e protagonistas) — protagonista feminina de *FireRed/LeafGreen*; no hack batalha como "Green" (pós-jogo).

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
| `OBJ_EVENT_GFX_LEAF` | `graphics/object_events/pics/people/leaf.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEAF` | `graphics/trainers/front_pics/leaf.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_LEAF` | `graphics/field_mugshots/leaf.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LEAF` | 852 | 0x854 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_NAMELESS_LEAF` | 899 | 0x883 | Chansey Lv85, Volcarona Lv86, Thundurus-Therian Lv85, Tapu Fini Lv86, Dragapult Lv86, Venusaur Lv87 | `CeruleanCave_B2F` |
| `TRAINER_TITLE_DEFENSE_LEAF` | 950 | 0x8B6 | Chansey Lv85, Volcarona Lv86, Thundurus-Therian Lv85, Tapu Fini Lv86, Dragapult Lv86, Venusaur Lv87 · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LEAF`, campeão de Mew e Iron Leaves. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Deoxys na forma Defense**: em FireRed/LeafGreen o Deoxys da Birth Island aparece na forma Attack no FireRed e na forma **Defense no LeafGreen**, e a Leaf é a protagonista do LeafGreen. Semi-lendário **Mew** (ela é campeã dele; Iron Leaves, o outro, fica fora porque só cabe um semi). Mega **Venusaur** (Grasstite), o inicial de quem joga LeafGreen, que também fecha o time dela na Cerulean Cave. Mais Volcarona, Dragapult e Chansey, do `TRAINER_NAMELESS_LEAF` da campanha (o Thundurus e a Tapu Fini saem: são semi-lendários). Ela é uma colecionadora de Pokédex, e o time é de quem joga a longa.

Observação para o autor: no hack a Leaf batalha como **"Green"** (o `Name:` segue o `TRAINER_NAMELESS_LEAF`). A plaquinha de fala mostra **Green** (decisão do autor, 27/09/2026: `SP_NAME_GREEN`); as falas de campeão usam essa confusão de nome de propósito.

*Plano (Singles):* desgaste. O Deoxys-D põe Stealth Rock, dá Taunt em quem tenta armar e tira dano fixo com Night Shade; a Chansey (Eviolite) segura o especial e limpa status com Heal Bell; a Mega Venusaur (Thick Fat) aguenta Fogo e Gelo e drena com Leech Seed e Giga Drain; o Mew queima os físicos com Will-O-Wisp; a Volcarona sobe Quiver Dance no fim e o Dragapult entra e sai com U-turn.

*Plano (Doubles):* o Mew põe Tailwind, a Volcarona (Heavy-Duty Boots) usa Heat Wave com o vento a favor, a Chansey dá Helping Hand, e a Mega Venusaur adormece com Sleep Powder. O Deoxys-D com Taunt corta Trick Room. Nenhum golpe acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Deoxys-Defense | Leftovers | Pressure | Bold | Stealth Rock, Night Shade, Recover, Taunt |
| Mew | Leftovers | Synchronize | Timid | Tailwind, Will-O-Wisp, Psychic, Roost |
| Venusaur | Grasstite | Chlorophyll | Bold | Giga Drain, Sludge Bomb, Sleep Powder, Leech Seed |
| Volcarona | Heavy-Duty Boots | Flame Body | Timid | Quiver Dance, Fiery Dance, Heat Wave, Bug Buzz |
| Dragapult | Life Orb | Clear Body | Jolly | Dragon Darts, Phantom Force, U-turn, Will-O-Wisp |
| Chansey | Eviolite | Natural Cure | Bold | Seismic Toss, Soft-Boiled, Heal Bell, Helping Hand |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_LEAF ===
Name: Green
Class: Pkmn Trainer 1
Pic: Leaf
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Deoxys-Defense @ Leftovers
Bold Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Night Shade
- Recover
- Taunt

Mew @ Leftovers
Timid Nature
Level: 100
Ability: Synchronize
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Will-O-Wisp
- Psychic
- Roost

Venusaur @ Grasstite
Bold Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Sludge Bomb
- Sleep Powder
- Leech Seed

Volcarona @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Flame Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Quiver Dance
- Fiery Dance
- Heat Wave
- Bug Buzz

Dragapult @ Life Orb
Jolly Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Darts
- Phantom Force
- U-turn
- Will-O-Wisp

Chansey @ Eviolite
Bold Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Seismic Toss
- Soft-Boiled
- Heal Bell
- Helping Hand
```

</details>

### Lendário associado

#### Mew

📝 **Proposta de 27/09/2026, aguardando o autor.** **Mew**. Leaf é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Leaf, a protagonista de FireRed/LeafGreen: completou a Pokédex de Kanto e das Sevii Islands para o Professor Oak. No hack é a treinadora sem nome que espera no fundo da Cerulean Cave, e batalha com o nome "Green".

**A criatura.** Mew, o Pokémon Nova Espécie, é dito conter o código genético de todos os Pokémon; pode ficar invisível quando quer e aprende qualquer golpe. Foi dos genes dele que fizeram o Mewtwo. Em Emerald aparece na Faraway Island.

**O fragmento.** Uma floresta tropical, quente e barulhenta. A lama está cheia de pegadas, cada uma de um tipo diferente de Pokémon, e todas vão estreitando até virar um único par de pegadas pequenas. Todos os caminhos voltam ao mesmo começo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A rainforest, warm and loud.
>
> The mud was full of tracks, each one from a different kind of Pokémon, and every trail narrowed down into one small set of footprints.

**Boss**

> The small footprints ended in the middle of a clearing.
>
> Something giggled above you. When you looked up there was nothing there. Then there was.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-151. New Species.
>
> A forest where every path leads back to the same small beginning, and a young woman who answers to a name that is not quite hers.
>
> What came back with you is small enough to hold. It already looks like it might become anything.
>
> She was not bothered about the name. She says names are like tracks: you leave them, and you keep walking.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Mew_Arrival:
	.string "A rainforest, warm and loud.\p"
	.string "The mud was full of tracks, each one\n"
	.string "from a different kind of Pokémon, and\l"
	.string "every trail narrowed down into one\l"
	.string "small set of footprints.$"

Nexus_Text_Mew_Boss:
	.string "The small footprints ended in the\n"
	.string "middle of a clearing.\p"
	.string "Something giggled above you. When you\n"
	.string "looked up there was nothing there.\l"
	.string "Then there was.$"

Nexus_Text_Mew_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-151. New Species.\p"
	.string "A forest where every path leads back\n"
	.string "to the same small beginning, and a\l"
	.string "young woman who answers to a name\l"
	.string "that is not quite hers.\p"
	.string "What came back with you is small\n"
	.string "enough to hold. It already looks like it\l"
	.string "might become anything.\p"
	.string "She was not bothered about the name.\n"
	.string "She says names are like tracks: you\l"
	.string "leave them, and you keep walking.$"
```

</details>

#### Iron Leaves

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Leaves**. Leaf é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** A mesma Leaf, colecionadora: o que a move é ver cada Pokémon de perto e anotar. O nome dela é uma folha.

**A criatura.** Iron Leaves é um Pokémon Paradoxo do futuro (Scarlet/Violet), parecido com o Virizion dos Swords of Justice: um corpo de máquina verde, com lâminas na cabeça que ele carrega com energia psíquica (o golpe Psyblade). Veio parar em Paldea pela máquina do tempo da Area Zero.

**O fragmento.** Uma floresta de aço. As folhas são lâminas, tocam umas nas outras como sinos quando o vento passa, e nenhuma nunca caiu. É um outono que esqueceu como acontecer.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest, but the leaves were steel.
>
> When the wind moved, the branches rang against each other like blades. Not one leaf had ever fallen.

**Boss**

> The ringing stopped all at once.
>
> Something stepped out of the trees with its head lowered like a knight's, and the long green edges on its brow began to glow.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1010. Paradox.
>
> A forest that has forgotten how to be autumn, and a young woman named for the thing it cannot do.
>
> What came back with you is the size of a seedling. Its edges are still soft. I do not know what time it belongs to now.
>
> I asked her what her name had to do with it. She said, 'Nothing,' and smiled. I have written that down too.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronLeaves_Arrival:
	.string "A forest, but the leaves were steel.\p"
	.string "When the wind moved, the branches rang\n"
	.string "against each other like blades. Not one\l"
	.string "leaf had ever fallen.$"

Nexus_Text_IronLeaves_Boss:
	.string "The ringing stopped all at once.\p"
	.string "Something stepped out of the trees\n"
	.string "with its head lowered like a knight's,\l"
	.string "and the long green edges on its brow\l"
	.string "began to glow.$"

Nexus_Text_IronLeaves_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1010. Paradox.\p"
	.string "A forest that has forgotten how to be\n"
	.string "autumn, and a young woman named for\l"
	.string "the thing it cannot do.\p"
	.string "What came back with you is the size of\n"
	.string "a seedling. Its edges are still soft. I\l"
	.string "do not know what time it belongs to\l"
	.string "now.\p"
	.string "I asked her what her name had to do\n"
	.string "with it. She said, 'Nothing,' and smiled.\l"
	.string "I have written that down too.$"
```

</details>

### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Leaf cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Oh! A new place. I'll need a new page for this one.
>
> Professor Oak gave me a Pokédex once and said, 'See every Pokémon there is.' I took it a little too seriously.
>
> Show me yours! I want to see them up close!

**Derrota**

> Wow… I'm writing that one down.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Leaf_Intro:
	.string "Oh! A new place. I'll need a new page\n"
	.string "for this one.\p"
	.string "Professor Oak gave me a Pokédex once\n"
	.string "and said, 'See every Pokémon there is.'\l"
	.string "I took it a little too seriously.\p"
	.string "Show me yours! I want to see them up\n"
	.string "close!$"

Nexus_Text_Leaf_Defeat:
	.string "Wow… I'm writing that one down.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Leaf é a **campeã**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Mew

A Leaf passou anos enchendo uma Pokédex, uma página por vez. Aqui ela descobre que todas as páginas eram uma só: as pegadas de todos os Pokémon voltam para aquela criaturinha. Ela não fica triste; quer ver com os próprios olhos. Depois, a virada: no hack ela é chamada por um nome que não escolheu (Green), e a criatura é todos os Pokémon ao mesmo tempo e atende por todos. Talvez um nome seja só onde alguém te encontrou.

**Antes da luta**

> I followed the tracks here. Hundreds of them, from every kind of Pokémon, all shrinking into one little set of paws.
>
> I spent years filling a Pokédex, one page at a time. Turns out it was all one page.
>
> …I'm not upset! I just want to see it with my own eyes first!

**Derrota**

> Ah… I got so busy looking, I forgot to battle.

**Depois da luta**

> People call me by a different name here. I didn't pick it, but I answer to it.
>
> That little one is every Pokémon at once, and it answers to all of them.
>
> Maybe a name is just the place where someone found you.
>
> Go on. It's watching you. It always was.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Leaf_Mew_ChampionIntro:
	.string "I followed the tracks here. Hundreds\n"
	.string "of them, from every kind of Pokémon,\l"
	.string "all shrinking into one little set of\l"
	.string "paws.\p"
	.string "I spent years filling a Pokédex, one\n"
	.string "page at a time. Turns out it was all one\l"
	.string "page.\p"
	.string "…I'm not upset! I just want to see it\n"
	.string "with my own eyes first!$"

Nexus_Text_Leaf_Mew_ChampionDefeat:
	.string "Ah… I got so busy looking, I forgot to\n"
	.string "battle.$"

Nexus_Text_Leaf_Mew_ChampionAfter:
	.string "{SPEAKER NAME_GREEN}People call me by a different name\n"
	.string "here. I didn't pick it, but I answer to\l"
	.string "it.\p"
	.string "That little one is every Pokémon at\n"
	.string "once, and it answers to all of them.\p"
	.string "Maybe a name is just the place where\n"
	.string "someone found you.\p"
	.string "Go on. It's watching you. It always\n"
	.string "was.$"
```

</details>

#### Iron Leaves

O nome dela é uma folha, e folha de verdade cai todo outono e volta na primavera. As desta floresta não caem nunca: vieram de um tempo tão à frente que até as folhas esqueceram. A Leaf prefere ser do tipo que cai; a derrota dela é exatamente isso ("eu caí; tudo bem, eu volto"). No fim ela fala do cavaleiro verde com carinho, torcendo para ele ver um outono, uma vez que seja.

**Antes da luta**

> Did you hear the trees out there? They ring. The leaves are steel, and not one of them has ever fallen.
>
> My name's a leaf, you know. The real kind falls every autumn, and grows back in spring.
>
> I think I'd rather be that kind. Let's battle!

**Derrota**

> Ah! I fell. …That's fine. I grow back.

**Depois da luta**

> Something like a knight came out of those trees. Sharp, green, and very polite about it.
>
> It's from a time that hasn't happened yet. So far ahead that even the leaves forgot how to fall.
>
> I hope it gets to see an autumn. Just once.
>
> Go on! Be gentle with it, if you can.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Leaf_IronLeaves_ChampionIntro:
	.string "Did you hear the trees out there? They\n"
	.string "ring. The leaves are steel, and not one\l"
	.string "of them has ever fallen.\p"
	.string "My name's a leaf, you know. The real\n"
	.string "kind falls every autumn, and grows\l"
	.string "back in spring.\p"
	.string "I think I'd rather be that kind. Let's\n"
	.string "battle!$"

Nexus_Text_Leaf_IronLeaves_ChampionDefeat:
	.string "Ah! I fell. …That's fine. I grow back.$"

Nexus_Text_Leaf_IronLeaves_ChampionAfter:
	.string "{SPEAKER NAME_GREEN}Something like a knight came out of\n"
	.string "those trees. Sharp, green, and very\l"
	.string "polite about it.\p"
	.string "It's from a time that hasn't happened\n"
	.string "yet. So far ahead that even the leaves\l"
	.string "forgot how to fall.\p"
	.string "I hope it gets to see an autumn. Just\n"
	.string "once.\p"
	.string "Go on! Be gentle with it, if you can.$"
```

</details>

Falante novo: `SP_NAME_GREEN` (ainda não existe em `include/constants/speaker_names.h`); a plaquinha mostra "Green", decisão do autor de 27/09/2026.
