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
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_BRUNO` | `graphics/object_events/pics/people/elite_four/bruno.png` |

Desde 26/09/2026 é a arte 32x32 de doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine), na campanha e no Nexus.

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

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BRUNO` = **976** (flag de batalha `0x8D0`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Bruno_Fight` (genérica) e `Nexus_EventScript_Bruno_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Bruno.

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

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Bruno_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Buzzwole** (UB-02 Absorption). Bruno é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

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

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Bruno_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Bruno cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Três ângulos do mesmo homem. A variação 1 é o treino que não para. A 2 é humor de dojo: sem tábuas para quebrar, ele quebra o silêncio. A 3 brinca com o fragmento dele (R21): uma Liga em que ninguém nunca passou da porta do Bruno (fio da Liga de Kanto), e ele está feliz de finalmente perder.

**Variação 2 — humor de dojo**

**Antes da luta**

> Every morning I break a board with my bare hand. Here, I found no boards.
>
> So I have been breaking the silence instead. It does not break as easily.
>
> Hm. You look sturdier than silence. Hoo hah!

**Derrota**

> My hand is fine. My pride has a small crack in it. Good. Cracks heal stronger.

**Variação 3 — o que faltou no fragmento dele**

**Antes da luta**

> Where I come from, no challenger ever got past my door. Not one, in all my years.
>
> People called that strength. I called it lonely.
>
> So forgive me if I am glad to see you. Do not hold back!

**Derrota**

> …There. Someone finally got past my door. I have waited a long time to lose to somebody.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bruno_Intro2:
	.string "Every morning I break a board with my\n"
	.string "bare hand. Here, I found no boards.\p"
	.string "So I have been breaking the silence\n"
	.string "instead. It does not break as easily.\p"
	.string "Hm. You look sturdier than silence. Hoo\n"
	.string "hah!$"

Nexus_Text_Bruno_Defeat2:
	.string "My hand is fine. My pride has a small\n"
	.string "crack in it. Good. Cracks heal stronger.$"

Nexus_Text_Bruno_Intro3:
	.string "Where I come from, no challenger ever\n"
	.string "got past my door. Not one, in all my\l"
	.string "years.\p"
	.string "People called that strength. I called it\n"
	.string "lonely.\p"
	.string "So forgive me if I am glad to see you. Do\n"
	.string "not hold back!$"

Nexus_Text_Bruno_Defeat3:
	.string "…There. Someone finally got past my\n"
	.string "door. I have waited a long time to lose\l"
	.string "to somebody.$"
```

</details>

### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Bruno_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Bruno é o **campeão**, a luta logo antes da Buzzwole. A fala é sobre a criatura, sem dizer o nome dela.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é o julgamento (aquilo não é força). A 2 é o espelho cômico: os dois posando um para o outro até escurecer, e a lição que o diário explica (ela bebe do que para). A 3 é o que ele viu acontecer com a própria Liga e a Beast Ball rachada que guarda no cinto (fio Ultra; ver o diário dele).

**Variação 2 — o espelho**

**Antes da luta**

> This morning it posed for me. I posed back. We stood like that until the jungle got dark.
>
> Neither of us blinked. I think it believes we are the same.
>
> We are not. I sweat for mine. Come! Show it the difference!

**Derrota**

> Hoo hah! Your muscles do not show, and still they hit. It will hate that.

**Depois da luta**

> Look at the trees. Every one grew too big and too tired. It drank from them, and they grew for nothing.
>
> Strength you did not earn does not stay. It only sits on you, heavy.
>
> When you face it, keep moving. It drinks from things that stand still. Go!

**Variação 3 — a Liga cansada**

**Antes da luta**

> The other three of my League walked into this jungle. They came back quiet. They sit down a great deal now.
>
> I asked what it took from them. None of them could remember.
>
> It will not take you too. First, let me see if you are worth guarding!

**Derrota**

> Worth guarding? No. You can guard yourself. Hoo!

**Depois da luta**

> Long ago a quiet woman came through here holding a strange ball, striped, cracked down the middle.
>
> She threw it at the creature. It laughed, if it can laugh. She left the ball behind.
>
> I keep it on my belt. Some things are not meant to be caught. Go and learn that for yourself.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bruno_ChampionIntro2:
	.string "This morning it posed for me. I posed\n"
	.string "back. We stood like that until the\l"
	.string "jungle got dark.\p"
	.string "Neither of us blinked. I think it\n"
	.string "believes we are the same.\p"
	.string "We are not. I sweat for mine. Come! Show\n"
	.string "it the difference!$"

Nexus_Text_Bruno_ChampionDefeat2:
	.string "Hoo hah! Your muscles do not show, and\n"
	.string "still they hit. It will hate that.$"

Nexus_Text_Bruno_ChampionAfter2:
	.string "{SPEAKER NAME_BRUNO}Look at the trees. Every one grew too\n"
	.string "big and too tired. It drank from them,\l"
	.string "and they grew for nothing.\p"
	.string "Strength you did not earn does not\n"
	.string "stay. It only sits on you, heavy.\p"
	.string "When you face it, keep moving. It drinks\n"
	.string "from things that stand still. Go!$"

Nexus_Text_Bruno_ChampionIntro3:
	.string "The other three of my League walked\n"
	.string "into this jungle. They came back quiet.\l"
	.string "They sit down a great deal now.\p"
	.string "I asked what it took from them. None of\n"
	.string "them could remember.\p"
	.string "It will not take you too. First, let me\n"
	.string "see if you are worth guarding!$"

Nexus_Text_Bruno_ChampionDefeat3:
	.string "Worth guarding? No. You can guard\n"
	.string "yourself. Hoo!$"

Nexus_Text_Bruno_ChampionAfter3:
	.string "{SPEAKER NAME_BRUNO}Long ago a quiet woman came through\n"
	.string "here holding a strange ball, striped,\l"
	.string "cracked down the middle.\p"
	.string "She threw it at the creature. It\n"
	.string "laughed, if it can laugh. She left the\l"
	.string "ball behind.\p"
	.string "I keep it on my belt. Some things are\n"
	.string "not meant to be caught. Go and learn\l"
	.string "that for yourself.$"
```

</details>

