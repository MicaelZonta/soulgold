# Bruno

**Região da ficha:** Kanto

Aparece no checklist como:

- **Bruno — Lutador** (Kanto · Elite Four e Campeões) — artista marcial que usa Pokémon Lutadores e resistentes.
- **Bruno — Lutador** (Johto · Elite Four e Campeão) — veterano que permanece na Elite Four entre as duas gerações.

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
| `OBJ_EVENT_GFX_BRUNO` | `graphics/object_events/pics/people/elite_four/bruno.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_BRUNO` | `graphics/trainers/front_pics/elite_four_bruno.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BRUNO` | `graphics/field_mugshots/bruno.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BRUNO_1` | 379 | 0x67B | Hitmontop Lv69, Staraptor Lv69, Gallade Lv69, Annihilape Lv70, Kommo O Lv70, Machamp Lv70 · *dupla* · VS: Yellow | `PokemonLeague_BrunosRoom`, `src/battle_setup.c` |
| `TRAINER_BRUNO_2` | 380 | 0x67C | Hitmontop Lv85, Staraptor Lv85, Gallade Lv85, Annihilape Lv85, Kommo O Lv85, Machamp Lv85 | `PokemonLeague_BrunosRoom`, `src/battle_setup.c` |

### Time das Rift Missions

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_BRUNO`, campeão da Buzzwole. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Marshadow**, semi-lendário **Urshifu** (Single Strike), Mega **Heracross** (Bugtite: Skill Link), mais Machamp, Hitmontop e Hitmonlee. O Spectral Thief do Marshadow **rouba os aumentos do adversário**: é o conceito de Absorption na mão do Bruno, virado contra quem se fortalece de graça. O Urshifu ganhou a forma que tem treinando numa torre: força conquistada. *Plano:* Bulk Up e prioridade (Mach Punch, Sucker Punch, Shadow Sneak). Em Doubles, o Hitmontop abre com Intimidate e Fake Out, e o Urshifu atravessa Protect. Marshadow e Urshifu cobrem os pontos fracos do Lutador (Fantasma e Psíquico).

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Marshadow | Life Orb | Technician | Jolly | Spectral Thief, Close Combat, Shadow Sneak, Bulk Up |
| Urshifu | Choice Band | Unseen Fist | Adamant | Wicked Blow, Close Combat, Sucker Punch, U-turn |
| Heracross | Bugtite | Guts | Jolly | Pin Missile, Rock Blast, Close Combat, Swords Dance |
| Machamp | Leftovers | No Guard | Adamant | Dynamic Punch, Stone Edge, Knock Off, Bulk Up |
| Hitmontop | Assault Vest | Intimidate | Adamant | Fake Out, Close Combat, Sucker Punch, Rapid Spin |
| Hitmonlee | White Herb | Unburden | Jolly | Close Combat, Knock Off, Poison Jab, Mach Punch |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BRUNO ===
Name: Bruno
Class: Elite Four
Pic: Elite Four Bruno
Gender: Male
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Marshadow @ Life Orb
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spectral Thief
- Close Combat
- Shadow Sneak
- Bulk Up

Urshifu @ Choice Band
Adamant Nature
Level: 100
Ability: Unseen Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wicked Blow
- Close Combat
- Sucker Punch
- U-turn

Heracross @ Bugtite
Jolly Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Pin Missile
- Rock Blast
- Close Combat
- Swords Dance

Machamp @ Leftovers
Adamant Nature
Level: 100
Ability: No Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dynamic Punch
- Stone Edge
- Knock Off
- Bulk Up

Hitmontop @ Assault Vest
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Sucker Punch
- Rapid Spin

Hitmonlee @ White Herb
Jolly Nature
Level: 100
Ability: Unburden
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Knock Off
- Poison Jab
- Mach Punch
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Buzzwole** (UB-02 Absorption). Bruno é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Bruno, o homem que construiu a própria força treinando todo dia.

**A criatura.** Buzzwole anda por aí exibindo os músculos anormalmente inchados. O codinome é *Absorption*: ela suga energia com a probóscide. Mundo em USUM: Ultra Jungle.

**O fragmento.** Calor que bate na chegada. Uma copa verde onde tudo cresceu demais (folhas maiores que portas, raízes grossas como pilares), e tudo parece exausto. A força do lugar foi tirada de alguém.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> Heat hit you the moment you stepped through.
>
> Under a green canopy, everything had grown too large. Leaves wider than doors, roots as thick as pillars.
>
> And every one of them looked tired.

**Boss**

> The canopy shook.
>
> Something landed in the clearing, flexed once, and waited to be admired.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB-02. Absorption.
>
> A creature that drinks strength from others and then shows it off, and a man who built his own and would not call that strength.
>
> “Look at the legs,” he told you. I have no idea what it means, and I have written it down anyway.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Absorption_Arrival:
	.string "Heat hit you the moment you stepped\n"
	.string "through.\p"
	.string "Under a green canopy, everything had\n"
	.string "grown too large. Leaves wider than\l"
	.string "doors, roots as thick as pillars.\p"
	.string "And every one of them looked tired.$"

Nexus_Text_Absorption_Boss:
	.string "The canopy shook.\p"
	.string "Something landed in the clearing,\n"
	.string "flexed once, and waited to be admired.$"

Nexus_Text_Absorption_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-02. Absorption.\p"
	.string "A creature that drinks strength from\n"
	.string "others and then shows it off, and a man\l"
	.string "who built his own and would not call\l"
	.string "that strength.\p"
	.string "“Look at the legs,” he told you. I have\n"
	.string "no idea what it means, and I have\l"
	.string "written it down anyway.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Bruno cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I woke in a strange place, so I did what I always do. I trained until the sun came up.
>
> There is no sun here. So I am still training.
>
> You will make a fine partner. Brace yourself!

**Derrota**

> Hoo hah! A good blow. I will remember it in my training.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bruno_Intro:
	.string "I woke in a strange place, so I did what\n"
	.string "I always do. I trained until the sun\l"
	.string "came up.\p"
	.string "There is no sun here. So I am still\n"
	.string "training.\p"
	.string "You will make a fine partner. Brace\n"
	.string "yourself!$"

Nexus_Text_Bruno_Defeat:
	.string "Hoo hah! A good blow. I will remember it\n"
	.string "in my training.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Bruno é o **campeão**, a luta logo antes da Buzzwole. A fala é sobre a criatura, sem dizer o nome dela.

O Bruno observou a criatura por três dias: ela não levanta nada, não treina, só posa e bebe a força dos outros, e ainda assim é mais forte que qualquer lutador que ele já enfrentou. Ele não a odeia, mas se recusa a chamar aquilo de força. A vitória do jogador é "a outra força", a que não se bebe de ninguém. O que fica é um conselho de lutador: ela vai se exibir antes de bater, então não olhe os músculos, olhe as pernas.

**Antes da luta**

> I have watched it for three days. It lifts nothing. It trains nothing. It poses, and it drinks.
>
> And it is stronger than any fighter I have ever faced.
>
> I do not hate it. It is only doing what it is. But I will not stand beside it and call that strength.
>
> Show me the other kind!

**Derrota**

> Hoo hah! Yes. That. It cannot drink that from anyone.

**Depois da luta**

> When it comes, it will flex first. It wants you to fear its size before it ever throws a punch.
>
> Do not look at the muscles. Look at the legs. Anything that strong still has to stand somewhere.
>
> Go. I will be here. Training.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bruno_ChampionIntro:
	.string "I have watched it for three days. It\n"
	.string "lifts nothing. It trains nothing. It\l"
	.string "poses, and it drinks.\p"
	.string "And it is stronger than any fighter I\n"
	.string "have ever faced.\p"
	.string "I do not hate it. It is only doing what\n"
	.string "it is. But I will not stand beside it and\l"
	.string "call that strength.\p"
	.string "Show me the other kind!$"

Nexus_Text_Bruno_ChampionDefeat:
	.string "Hoo hah! Yes. That. It cannot drink that\n"
	.string "from anyone.$"

Nexus_Text_Bruno_ChampionAfter:
	.string "{SPEAKER NAME_BRUNO}When it comes, it will flex first. It\n"
	.string "wants you to fear its size before it\l"
	.string "ever throws a punch.\p"
	.string "Do not look at the muscles. Look at the\n"
	.string "legs. Anything that strong still has to\l"
	.string "stand somewhere.\p"
	.string "Go. I will be here. Training.$"
```

</details>

