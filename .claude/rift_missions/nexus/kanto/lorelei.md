# Lorelei

**Região da ficha:** Kanto

Aparece no checklist como:

- **Lorelei — Gelo** (Kanto · Elite Four e Campeões) — primeira integrante da Elite Four de Kanto, com preferência por Pokémon de Água e Gelo.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic) registrado no código.

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Lorelei/` (o overworld já está registrado; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Lorelei/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta de 30/09/2026 abaixo (validada), fora do código
- [ ] Associado a um lendário — 📝 proposta de 30/09/2026: Glastrier (cedido pelo Pryce)
- [ ] Diálogo genérico escrito — 📝 proposta de 30/09/2026 (3 variações)
- [ ] Diálogo associado ao lendário escrito — 📝 proposta de 30/09/2026 (3 variações)

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_LORELEI` (362; paleta `OBJ_EVENT_PAL_TAG_LORELEI` = `0x118B`) | `graphics/object_events/pics/people/special/lorelei.png` (32x32, doze quadros, `sAnimTable_StandardAsym`; `gObjectEventGraphicsInfo_Lorelei` em `src/data/object_events/object_event_graphics_info.h`) |

Nenhum mapa usa ainda. Folha de origem em `.filetransfer/.trainers/Lorelei/`: `Sprite - Purple Zaffre.png` (autor **Purple Zaffre**); comparação no jogo em `Sprite - comparacao no jogo.png`.

### Battle sprite (front pic)

Não existe no código (`TRAINER_PIC_FRONT_LORELEI` não existe). A arte chegou:

| Arquivo | O que é |
|---|---|
| `.filetransfer/.trainers/Lorelei/Trainer - KingdomXathers.png` | front pic, 50x82 (RGB, sem paleta), autor **KingdomXathers** |
| `.filetransfer/.trainers/Lorelei/outras/Trainer 1x 2x 4x - KingdomXathers.png` | a mesma arte em 1x, 2x e 4x |
| `.filetransfer/.trainers/Lorelei/Trainer - comparacao no jogo.png` | comparação no jogo |

Falta converter para 64x64 (skill `converter-sprite`; a arte tem 82 px de altura, mais que os 64 da front pic) e registrar (skill `adicionar-grafico-trainer`). O overworld já foi feito com a skill `adicionar-npc`.

### Field mugshot

Não existe, e a pasta `.filetransfer/.trainers/Lorelei/` não traz arte de mugshot. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_LORELEI`, ID **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163), campeã do Glastrier. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). **Pic provisória** (`Elite Four Glacia`, a outra dama do gelo da Elite Four) até registrar a arte.

⚠️ **O Glastrier é semi-lendário neste engine** (`isSubLegendary`; o Pryce, que o campeia hoje, nem o leva no time: leva o Calyrex-Ice e o Articuno). Por isso ele ocupa a vaga de **semi-lendário**, e a vaga de lendário vai para outro: **Kyurem**. O validador confirma: `L=KYUREM S=GLASTRIER`.

Lendário **Kyurem**, o dragão de gelo vazio que perdeu a metade de si (a verdade e o ideal foram embora nos outros dois dragões): combina com uma treinadora que só mostra a moldura dos óculos. Semi-lendário **Glastrier**, o corcel de gelo do rei (ver "Lendário associado" e o diário). Mega **Lapras** (`Icetite`, que neste hack vira a forma Gigantamax como Mega: Arctic Aura, abaixa o Ataque dos oponentes no fim de cada turno): a Lorelei de FireRed/LeafGreen salva os Lapras de Icefall Cave, em Four Island, da Team Rocket. Mais **Slowbro**, **Cloyster** e **Jynx**, do time dela em Red/Blue (o Dewgong fica no banco: o Glastrier cobre o papel de tanque lento de gelo).

*Plano (Singles):* dois ritmos. **Trick Room:** o Slowbro (Regenerator) ou a Jynx armam o Trick Room, e o Glastrier (Brave, velocidade base 30) entra com Weakness Policy e vira bola de neve com Chilling Neigh; a Mega Lapras segura tudo com Arctic Aura e bate com Hyper Voice (vira Água pelo inato Liquid Voice) e Freeze-Dry. **Sem Trick Room:** o Cloyster usa Shell Smash (White Herb devolve as defesas) e varre com Skill Link; o Kyurem de Choice Specs quebra com Freeze-Dry, Draco Meteor e Earth Power.

*Plano (Doubles):* dois armadores de Trick Room (Slowbro e Jynx), para um Taunt só não bastar; a Jynx põe um dos oponentes para dormir com Lovely Kiss. Dentro do Trick Room, a Mega Lapras acerta os dois oponentes com Hyper Voice e abaixa o Ataque dos dois com Arctic Aura, o Kyurem acerta os dois com Blizzard e o Glastrier bate com High Horsepower (alvo único: não acerta o parceiro, ao contrário de Earthquake). Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyurem | Choice Specs | Pressure | Modest | Freeze-Dry, Draco Meteor, Earth Power, Blizzard |
| Glastrier | Weakness Policy | Chilling Neigh | Brave | Icicle Crash, High Horsepower, Close Combat, Protect |
| Lapras | Icetite | Water Absorb | Quiet | Hyper Voice, Freeze-Dry, Thunderbolt, Protect |
| Slowbro | Colbur Berry | Regenerator | Relaxed | Trick Room, Scald, Psychic, Slack Off |
| Cloyster | White Herb | Skill Link | Adamant | Shell Smash, Icicle Spear, Rock Blast, Ice Shard |
| Jynx | Focus Sash | Dry Skin | Timid | Lovely Kiss, Ice Beam, Psychic, Trick Room |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_LORELEI ===
Name: Lorelei
Class: Elite Four
Pic: Elite Four Glacia
Gender: Female
Music: Elite Four
Double Battle: Yes
AI: Smart Trainer

Glastrier @ Weakness Policy
Brave Nature
Level: 100
Ability: Chilling Neigh
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Crash
- High Horsepower
- Close Combat
- Protect

Kyurem @ Choice Specs
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freeze-Dry
- Draco Meteor
- Earth Power
- Blizzard

Lapras @ Icetite
Quiet Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Freeze-Dry
- Thunderbolt
- Protect

Slowbro @ Colbur Berry
Relaxed Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Scald
- Psychic
- Slack Off

Cloyster @ White Herb
Adamant Nature
Level: 100
Ability: Skill Link
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shell Smash
- Icicle Spear
- Rock Blast
- Ice Shard

Jynx @ Focus Sash
Timid Nature
Level: 100
Ability: Dry Skin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Lovely Kiss
- Ice Beam
- Psychic
- Trick Room
```

</details>

### Lendário associado

#### Glastrier

📝 **Proposta de 30/09/2026, aguardando o autor.** **Glastrier**. Lorelei é a campeã dele: a quinta luta do Daily, logo antes da boss battle. Vem da tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md): quem cede é o **Pryce** (`johto/pryce.md`), que fica com o **Articuno**. Enquanto o autor não aprova, a ficha do Pryce e o código continuam como estão (`Nexus_EventScript_Pryce_Glastrier_ChampionFight`).

**Quem é.** Lorelei, a primeira da Elite Four de Kanto em Red/Blue/Yellow e FireRed/LeafGreen: óculos, calma, "No one can best me when it comes to icy Pokémon". Em FireRed/LeafGreen ela voltou para casa em Four Island (Sevii Islands), guarda uma coleção de bonecos de pelúcia e enfrenta com o jogador a Team Rocket que caçava os Lapras de Icefall Cave. Em Gold/Silver o **Will** ocupa a cadeira dela na Elite Four. No fio **Liga de Kanto** do diário, ela e a Agatha guardam os corcéis do rei e procuram o Will, que tem o rei (Calyrex).

**A criatura.** Glastrier, o corcel de gelo da Crown Tundra, montaria do Calyrex. Usa uma máscara de gelo, solta um frio intenso pelos cascos e é belicoso: o que quer, toma à força. Só volta a se aproximar atraído pela Iceroot Carrot que o Calyrex planta. Chilling Neigh: fica mais forte a cada adversário que derruba.

**O fragmento.** O campo de colheita congelado, com trigo que toca como sino, que o jogo já usa. No fragmento da Lorelei (diário), a Elite Four nunca perdeu e ninguém sai da Liga; ela é a primeira a pedir demissão, para voltar a Four Island, onde os caçadores voltaram atrás dos Lapras. O cavalo chegou com o sino de gelo no pescoço (a máscara do Pryce, no caderno dele), congelou a única plantação da ilha — e depois congelou o lago inteiro para **esconder** os Lapras dos caçadores. A Lorelei monta nele para levá-lo ao rei.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário) — **já estão no jogo**, com o Pryce como campeão: `Nexus_Text_Glastrier_Arrival`, `Nexus_Text_Glastrier_Boss` e o Looker File `Nexus_Text_Glastrier_LookerFile` (**File L-896. Wild Horse.**) em `data/scripts/nexus.inc`. Não se repete nada aqui.

**Chegada** (existente)

> A harvest field, frozen solid. The wheat had turned to ice and rang like bells when you touched it.
>
> Hoofprints crossed it, each one a small crater of frost.

**Boss** (existente)

> The field went white under a single stamp.
>
> It wore a mask of ice and breathed out winter, and it wanted the field you were standing on.

**Ficha do Looker** (existente, File L-896)

> File L-896. Wild Horse.
>
> A harvest nobody will eat, and an old man who knew exactly how long the field had been frozen.
>
> What you brought back stamps its foot at me. I have decided to allow it.
>
> He did not say how long. He only said spring is always later than you think.

⚠️ O File L-896 fala de **um velho** ("an old man who knew exactly how long the field had been frozen", "He did not say how long"): é o Pryce. Se a troca for aprovada, **a segunda e a quarta caixas** precisam de outra pessoa (a primeira e a terceira servem para qualquer campeão). Fica para o autor decidir; esta ficha não reescreve o File. O `.inc` é o de `nexus.inc` (e o da ficha do Pryce).

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Lorelei cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)). Três ângulos: apresentação clássica (RBY/FRLG): ninguém a vence no gelo (1); a coleção de bonecos de pelúcia (FRLG, a casa dela em Four Island) (2); R21: os Lapras da caverna de gelo e os ladrões — no fragmento dela, ela era criança quando eles vieram (3).

#### Variação 1

**Antes da luta**

> Welcome. I am Lorelei. No one can best me when it comes to icy Pokémon.
>
> Freezing moves are powerful. Your Pokémon will be at my mercy when they are frozen solid! …Are you ready?

**Derrota**

> …Things shouldn't be this way!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lorelei_Intro:
	.string "Welcome. I am Lorelei. No one can best\n"
	.string "me when it comes to icy Pokémon.\p"
	.string "Freezing moves are powerful. Your\n"
	.string "Pokémon will be at my mercy when they\l"
	.string "are frozen solid! …Are you ready?$"

Nexus_Text_Lorelei_Defeat:
	.string "…Things shouldn't be this way!$"
```

</details>

#### Variação 2

**Antes da luta**

> Please don't laugh. At home, I keep a collection of plush dolls. Hundreds of them.
>
> Each one reminds me of a Trainer I battled. The ones who beat me go on the front shelf.
>
> The front shelf is very empty. Let's keep it that way!

**Derrota**

> …I'll have to find a doll that looks like you. Please hold still.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lorelei_Intro2:
	.string "Please don't laugh. At home, I keep a\n"
	.string "collection of plush dolls. Hundreds of\l"
	.string "them.\p"
	.string "Each one reminds me of a Trainer I\n"
	.string "battled. The ones who beat me go on\l"
	.string "the front shelf.\p"
	.string "The front shelf is very empty. Let's\n"
	.string "keep it that way!$"

Nexus_Text_Lorelei_Defeat2:
	.string "…I'll have to find a doll that looks\n"
	.string "like you. Please hold still.$"
```

</details>

#### Variação 3

**Antes da luta**

> Where I grew up, the island was all ice caves and cold water. And Lapras, singing in the dark.
>
> Once, some bad people came to take them away. I was very small, and very angry.
>
> I'm not small anymore. I'm still a little angry. Let's battle!

**Derrota**

> Hm. You battle like someone protecting something. Good. Keep doing that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lorelei_Intro3:
	.string "Where I grew up, the island was all ice\n"
	.string "caves and cold water. And Lapras,\l"
	.string "singing in the dark.\p"
	.string "Once, some bad people came to take\n"
	.string "them away. I was very small, and very\l"
	.string "angry.\p"
	.string "I'm not small anymore. I'm still a\n"
	.string "little angry. Let's battle!$"

Nexus_Text_Lorelei_Defeat3:
	.string "Hm. You battle like someone protecting\n"
	.string "something. Good. Keep doing that.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Lorelei é a **campeã**, a luta logo antes do Glastrier. A fala é sobre a criatura, pelo olhar dela, sem dizer o nome da espécie ([R16](../NEXUS_REGRAS.md)).

#### Glastrier

##### Variação 1

*Ângulo:* a máscara de gelo e os óculos dela: gelo não é frio por maldade, é frio porque guarda alguma coisa.

**Antes da luta**

> It wears a mask of ice. Did you notice? Thick as a wall.
>
> I wear glasses. Same idea. People see the frames, and not what's behind them.
>
> Now then. Shall we see what's behind yours?

**Derrota**

> My glasses fogged up. That is my excuse, and I'm keeping it.

**Depois da luta**

> Ice isn't cold because it's mean. Ice is cold because it's keeping something safe.
>
> Under that mask is a horse that misses someone. It holds very still, so it won't have to feel it.
>
> I know that trick. I've used it. Go on. Crack it gently.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lorelei_ChampionIntro:
	.string "It wears a mask of ice. Did you notice?\n"
	.string "Thick as a wall.\p"
	.string "I wear glasses. Same idea. People see\n"
	.string "the frames, and not what's behind\l"
	.string "them.\p"
	.string "Now then. Shall we see what's behind\n"
	.string "yours?$"

Nexus_Text_Lorelei_ChampionDefeat:
	.string "My glasses fogged up. That is my\n"
	.string "excuse, and I'm keeping it.$"

Nexus_Text_Lorelei_ChampionAfter:
	.string "{SPEAKER NAME_LORELEI}Ice isn't cold because it's mean. Ice\n"
	.string "is cold because it's keeping something\l"
	.string "safe.\p"
	.string "Under that mask is a horse that misses\n"
	.string "someone. It holds very still, so it\l"
	.string "won't have to feel it.\p"
	.string "I know that trick. I've used it. Go on.\n"
	.string "Crack it gently.$"
```

</details>

##### Variação 2

*Ângulo:* fio Liga de Kanto: o cavalo procura o rei, ela procura o rapaz de máscara que levou o rei — e que, em outro mundo, ficou com a cadeira dela na Liga (Will substituiu a Lorelei em GSC).

**Antes da luta**

> The horse is searching for its king. I'm searching for a young man in a mask.
>
> In some other world, I'm told, he took my seat at the League. In this one, he took the king. He does get around.
>
> Well. Let's warm up while we wait. Frozen solid, if you please!

**Derrota**

> Hmph. Now I'm warmed up, and I have nowhere to go.

**Depois da luta**

> When the king rode it, that horse never had to take anything. Everything it needed was given.
>
> Alone, it takes. It doesn't know another way yet.
>
> If you meet a young man in a mask with a small king beside him… tell him two of us are coming.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lorelei_ChampionIntro2:
	.string "The horse is searching for its king.\n"
	.string "I'm searching for a young man in a\l"
	.string "mask.\p"
	.string "In some other world, I'm told, he took\n"
	.string "my seat at the League. In this one, he\l"
	.string "took the king. He does get around.\p"
	.string "Well. Let's warm up while we wait.\n"
	.string "Frozen solid, if you please!$"

Nexus_Text_Lorelei_ChampionDefeat2:
	.string "Hmph. Now I'm warmed up, and I have\n"
	.string "nowhere to go.$"

Nexus_Text_Lorelei_ChampionAfter2:
	.string "{SPEAKER NAME_LORELEI}When the king rode it, that horse never\n"
	.string "had to take anything. Everything it\l"
	.string "needed was given.\p"
	.string "Alone, it takes. It doesn't know\n"
	.string "another way yet.\p"
	.string "If you meet a young man in a mask with\n"
	.string "a small king beside him… tell him two of\l"
	.string "us are coming.$"
```

</details>

##### Variação 3

*Ângulo:* os Lapras do lago congelado: o cavalo gelou o lago, e os Lapras continuaram cantando por baixo.

**Antes da luta**

> It stamped once, and the lake behind my house froze solid. Every Lapras in it went quiet under the ice.
>
> Don't worry. They're fine. I checked. Twice.
>
> But nobody freezes my friends without asking me first. Let's go!

**Derrota**

> Oh dear. Now I owe that horse an apology AND a rematch.

**Depois da luta**

> Later, I went back to the lake. The Lapras were singing under the ice, as if nothing had happened.
>
> The horse was lying on the shore, listening. It had stopped stamping.
>
> Everyone likes a song. Even the angry ones. Especially them.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lorelei_ChampionIntro3:
	.string "It stamped once, and the lake behind\n"
	.string "my house froze solid. Every Lapras in\l"
	.string "it went quiet under the ice.\p"
	.string "Don't worry. They're fine. I checked.\n"
	.string "Twice.\p"
	.string "But nobody freezes my friends without\n"
	.string "asking me first. Let's go!$"

Nexus_Text_Lorelei_ChampionDefeat3:
	.string "Oh dear. Now I owe that horse an\n"
	.string "apology AND a rematch.$"

Nexus_Text_Lorelei_ChampionAfter3:
	.string "{SPEAKER NAME_LORELEI}Later, I went back to the lake. The\n"
	.string "Lapras were singing under the ice, as\l"
	.string "if nothing had happened.\p"
	.string "The horse was lying on the shore,\n"
	.string "listening. It had stopped stamping.\p"
	.string "Everyone likes a song. Even the angry\n"
	.string "ones. Especially them.$"
```

</details>

Falante novo: `SP_NAME_LORELEI` (ainda não existe em `include/constants/speaker_names.h`; `{SPEAKER NAME_LORELEI}` só no `ChampionAfter`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/lorelei/`](diario_looker/lorelei/) ([formato](../DIARIO_LOOKER.md)): [começo](diario_looker/lorelei/1_comeco.md) (Four Island, a caverna que parou de cantar, a primeira da Elite Four a pedir demissão, o cavalo com o sino de gelo), [meio](diario_looker/lorelei/2_meio.md) (o cavalo congelou o lago para esconder os cantores dos caçadores), [fim](diario_looker/lorelei/3_fim.md) (September 31st: o gelo se abre, a pedra sem dono fica com uma boneca no cais, e ela monta no cavalo rumo ao rei). See also: File L-896.
