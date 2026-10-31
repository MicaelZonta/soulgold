# Lorelei

**Região da ficha:** Kanto

Aparece no checklist como:

- **Lorelei — Gelo** (Kanto · Elite Four e Campeões) — primeira integrante da Elite Four de Kanto, com preferência por Pokémon de Água e Gelo.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Lorelei/` (o overworld já está registrado; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Lorelei/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido — 📝 proposta de 30/09/2026 abaixo (validada), fora do código
- [x] Associado a um lendário — 📝 proposta de 30/09/2026: Glastrier (cedido pelo Pryce)
- [x] Diálogo genérico escrito — 📝 proposta de 30/09/2026 (3 variações)
- [x] Diálogo associado ao lendário escrito — 📝 proposta de 30/09/2026 (3 variações)

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_LORELEI` = **1196** (bloco 2, flag `0xB20`), luta genérica `Nexus_EventScript_Lorelei_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_LORELEI ===
Name: Lorelei
Class: Elite Four
Pic: Lorelei
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Slowbro @ Mental Herb
Relaxed Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Scald
- Psychic
- Slack Off

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
- Ice Beam

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

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Glastrier** — `Nexus_EventScript_Lorelei_Glastrier_ChampionFight` (falas `Nexus_Text_Lorelei_Glastrier_Champion*`)
- **Kyurem** — `Nexus_EventScript_Lorelei_Kyurem_ChampionFight` (falas `Nexus_Text_Lorelei_Kyurem_Champion*`)
- **Articuno** — `Nexus_EventScript_Lorelei_Articuno_ChampionFight` (falas `Nexus_Text_Lorelei_Articuno_Champion*`)


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

✅ **Implementado em 31/10/2026:** `Nexus_Text_Lorelei_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Welcome. I am Lorelei. No one can best me when it comes to icy Pokemon.
>
> Freezing moves are powerful. Your Pokemon will be at my mercy when they are frozen solid! ...Are you ready?

**Derrota**

> ...Things shouldn't be this way!

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
