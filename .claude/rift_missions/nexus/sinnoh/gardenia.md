# Gardenia

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Gardenia — Grama** (Sinnoh · Líderes de Ginásio) — Líder de Eterna que tem medo de fantasmas.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic), obrigatório.

**Arte disponível:** ✅ overworld (já registrado) e front pic em `.filetransfer/.trainers/Gardenia/`.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)* — 📦 arte pronta em `.filetransfer`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026)
- [ ] Associado a um lendário — 📝 proposta abaixo (30/09/2026)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo (30/09/2026)
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo (30/09/2026)

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_GARDENIA` | `graphics/object_events/pics/people/special/gardenia.png` (16x32, 9 quadros, `sAnimTable_Standard`) |

Registrado em 30/09/2026. Origem em `.filetransfer/.trainers/Gardenia/`: `Sprite - oficial Platinum.png` (arte oficial de Platinum) e `Sprite - comparacao no jogo.png`.

### Battle sprite (front pic)

Não registrado no código. **Arte pronta** em `.filetransfer/.trainers/Gardenia/`:

- `Trainer - desconhecido.png` (80x80, autor **desconhecido**)
- `Trainer - comparacao no jogo.png` (comparação no jogo)

Falta registrar: skills `converter-sprite` (conferir/reduzir para 64x64, ≤16 cores) e `adicionar-grafico-trainer` (`TRAINER_PIC_FRONT_GARDENIA`). Até lá o bloco do time usa uma **pic provisória** (ver abaixo).

### Field mugshot

Não existe (a pasta da arte não tem retrato). Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_GARDENIA` (ID **a alocar**: livre abaixo de 1056, nunca 1056–1163), campeã de Shaymin. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). Validado com `python3 dev_scripts/nexus_validar_time.py` (✓). **Pic provisória `Aroma Lady`** até registrar a arte; classe `Leader`. `Double Battle: Yes`: o Flower Gift da Cherrim e o Tailwind da Shaymin rendem mais em dupla; o plano vale nos dois.

A Shaymin é **semi-lendária** (R10), então o time leva também um lendário. Lendário **Zygarde (Forma 50%, Power Construct)**: o guardião da ordem do ecossistema, para a Líder que cuida de uma floresta — no fragmento dela, as células dele contam o que sobrou debaixo da cinza; abaixo da metade do HP ele vira a Forma Completa. Semi-lendário **Shaymin, Forma Céu**, de que ela é campeã. Mega **Meganium** (Bondstone; Mega Grama/Fada com **Mega Sol**: os golpes dela agem como sob sol — Solar Beam sem carregar, Growth dobrado, Synthesis cheia), a flor no pescoço. Mais **Roserade** e **Cherrim**, do time dela em Platinum, e **Torterra** (o Turtwig dela em Platinum). Se o autor preferir uma Mega de Sinnoh, não há Grama com Mega; a alternativa é a Mega Sceptile (Grasstite).

*Plano (Singles):* a Roserade de Focus Sash põe Spikes e Sleep Powder; a Cherrim liga o sol (Flower Gift) e o Weather Ball vira Fogo; a Mega Meganium sobe Growth e solta Solar Beam na hora, com ou sem sol; a Shaymin-Sky usa Air Slash com Serene Grace (60% de flinch); o Torterra bate físico; o Zygarde sobe Dragon Dance e varre com Thousand Arrows (que acerta Voador e Levitate), virando a Forma Completa quando apanha.

*Plano (Doubles):* Tailwind da Shaymin-Sky no turno 1; a Cherrim chama o sol e o Flower Gift dá Ataque e Defesa Especial ao parceiro (Zygarde ou Torterra); o Thousand Arrows acerta os dois adversários e nunca o parceiro; a Cherrim guarda Healing Wish para trazer a Shaymin de volta. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zygarde-50-Power-Construct | Leftovers | Power Construct | Adamant | Dragon Dance, Thousand Arrows, Scale Shot, Stone Edge |
| Shaymin-Sky | Leftovers | Serene Grace | Timid | Seed Flare, Air Slash, Earth Power, Tailwind |
| Meganium | Bondstone | Overgrow | Modest | Growth, Solar Beam, Dazzling Gleam, Synthesis |
| Roserade | Focus Sash | Natural Cure | Timid | Sleep Powder, Giga Drain, Sludge Bomb, Spikes |
| Torterra | Leftovers | Shell Armor | Adamant | Wood Hammer, High Horsepower, Stone Edge, Synthesis |
| Cherrim | Heat Rock | Flower Gift | Modest | Sunny Day, Weather Ball, Giga Drain, Healing Wish |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_GARDENIA ===
Name: Gardenia
Class: Leader
Pic: Aroma Lady
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Zygarde-50-Power-Construct @ Leftovers
Adamant Nature
Level: 100
Ability: Power Construct
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Thousand Arrows
- Scale Shot
- Stone Edge

Shaymin-Sky @ Leftovers
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Seed Flare
- Air Slash
- Earth Power
- Tailwind

Meganium @ Bondstone
Modest Nature
Level: 100
Ability: Overgrow
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Growth
- Solar Beam
- Dazzling Gleam
- Synthesis

Roserade @ Focus Sash
Timid Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sleep Powder
- Giga Drain
- Sludge Bomb
- Spikes

Torterra @ Leftovers
Adamant Nature
Level: 100
Ability: Shell Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wood Hammer
- High Horsepower
- Stone Edge
- Synthesis

Cherrim @ Heat Rock
Modest Nature
Level: 100
Ability: Flower Gift
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sunny Day
- Weather Ball
- Giga Drain
- Healing Wish
```

</details>

### Lendário associado

#### Shaymin

📝 **Proposta de 30/09/2026, aguardando o autor.** **Shaymin**. A Gardenia é a campeã dela; quem cede é a **Erika**, que fica com a Virizion (tabela de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)). Enquanto o autor não aprova, a ficha da Erika e o código continuam como estão.

**Quem é.** Gardenia, Líder de Ginásio de Eterna City em Diamond/Pearl/Platinum, especialista em Grama, apaixonada pela Floresta de Eterna. Animada e direta, tem pavor de fantasmas — e a mansão assombrada da região, a Old Chateau, fica justamente na floresta dela.

**A criatura.** Shaymin, o Pokémon da gratidão. Absorve as toxinas do ar e da terra e transforma chão arruinado em campo de flores. Tímida: se enrola e se disfarça de moita. Com a flor Gracidea vira a Forma Céu e sai voando, espalhando sementes.

**O fragmento.** O campo de cinza atravessado por uma linha de flores (`Nexus_Text_Shaymin_Arrival`). No fragmento da Gardenia, a Floresta de Eterna queimou na noite em que o prédio da Galactic explodiu. A única casa que sobrou foi a mansão assombrada; ela, que tem medo de fantasma, foi morar lá para guardar as sementes. Toda manhã planta uma. A criatura anda na frente, deixando flores; a Gardenia vai atrás.

**Falas do fragmento** (narração; **já estão no jogo**, `Nexus_Text_Shaymin_Arrival` e `Nexus_Text_Shaymin_Boss` em `data/scripts/nexus.inc` — valem para qualquer campeão deste lendário e não mudam):

**Chegada**

> A field of grey ash under a grey sky. Nothing grew, and the air tasted of smoke.
>
> But a thin line of fresh flowers ran across it, bright as footprints.

**Boss**

> The flowers at your feet shivered.
>
> Something small rose out of the grass, and the grey air around it was already turning clear.

**Ficha do Looker** — **já existe no jogo**: `Nexus_EventScript_Shaymin_LookerFile` → `Nexus_Text_Shaymin_LookerFile` (`data/scripts/nexus.inc`). Não reescrita aqui; o texto atual, para referência:

> File L-492. Gratitude.
>
> A dead field, and a small thing walking across it, leaving flowers behind.
>
> The woman who sells perfume in Celadon asked me who it was thanking. I had no answer.
>
> What came back with you is very small, and asleep inside a blossom. She says that is how they begin.

O File L-492 atual fala da Erika (“The woman who sells perfume in Celadon”). Não serve para o fragmento da Gardenia. Proponho uma **versão alternativa**, para substituir o texto de `Nexus_Text_Shaymin_LookerFile` **só se** a troca de campeão for aprovada (o Looker File é por lendário, R18).

**Versão alternativa** (📝 30/09/2026):

> File L-492. Gratitude.
>
> A burned forest, and a Gym Leader who is afraid of ghosts, living in the only house the fire would not take.
>
> What came back with you is very small, and asleep inside a blossom. It thanked me for the tea. I had not offered any.

<details><summary><code>.inc</code> da versão alternativa</summary>

```asm
Nexus_Text_Shaymin_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-492. Gratitude.\p"
	.string "A burned forest, and a Gym Leader who\n"
	.string "is afraid of ghosts, living in the only\l"
	.string "house the fire would not take.\p"
	.string "What came back with you is very small,\n"
	.string "and asleep inside a blossom. It\l"
	.string "thanked me for the tea. I had not\l"
	.string "offered any.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Gardenia cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

Voz da Gardenia de DP/Pt: animada, direta, meio moleca, fala de planta como quem fala de gente e morre de medo de fantasma. As três variações: a apresentação (a jardineira), o medo de fantasma (humor) e a floresta que ela perdeu no fragmento dela, sem explicar como.

**Antes da luta**

> Hey there! I'm Gardenia! I grow things. Pokémon, trees, flowers -- if it's green, I've got it covered.
>
> Weird place, huh? Nothing grows here. So I brought my own green!
>
> Come on, let's battle! My team's been stuck in one pot way too long!

**Derrota**

> Wow! You cut right through my garden. That's okay. Gardens grow back!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gardenia_Intro:
	.string "Hey there! I'm Gardenia! I grow things.\n"
	.string "Pokémon, trees, flowers -- if it's\l"
	.string "green, I've got it covered.\p"
	.string "Weird place, huh? Nothing grows here.\n"
	.string "So I brought my own green!\p"
	.string "Come on, let's battle! My team's been\n"
	.string "stuck in one pot way too long!$"

Nexus_Text_Gardenia_Defeat:
	.string "Wow! You cut right through my garden.\n"
	.string "That's okay. Gardens grow back!$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o medo de fantasma, no humor

**Antes da luta**

> Okay, first question, super important: are you a ghost? You're not see-through, are you?
>
> Phew. Sorry. I'm, uh, not great with ghosts. Or old houses. Or dark hallways. Or the word “boo.”
>
> Anyway! Real Trainer, real battle! That I can handle!

**Derrota**

> Ahh! You beat me! …Was that a ghost behind you? No? Okay. Good. Great.

**Variação 3** — a floresta que virou cinza e a semente de cada manhã

**Antes da luta**

> Where I'm from, there used to be a whole forest. Big, old, full of moss and bugs and noise.
>
> It's mostly ash now. But I plant something new every single morning. One seed. Every day.
>
> So don't you dare think I'm the type to give up. Let's go!

**Derrota**

> Heh. You're tough. I'm tougher about it. Tomorrow I'll plant two.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gardenia_Intro2:
	.string "Okay, first question, super important:\n"
	.string "are you a ghost? You're not\l"
	.string "see-through, are you?\p"
	.string "Phew. Sorry. I'm, uh, not great with\n"
	.string "ghosts. Or old houses. Or dark hallways.\l"
	.string "Or the word “boo.”\p"
	.string "Anyway! Real Trainer, real battle! That\n"
	.string "I can handle!$"

Nexus_Text_Gardenia_Defeat2:
	.string "Ahh! You beat me! …Was that a ghost\n"
	.string "behind you? No? Okay. Good. Great.$"

Nexus_Text_Gardenia_Intro3:
	.string "Where I'm from, there used to be a\n"
	.string "whole forest. Big, old, full of moss and\l"
	.string "bugs and noise.\p"
	.string "It's mostly ash now. But I plant\n"
	.string "something new every single morning.\l"
	.string "One seed. Every day.\p"
	.string "So don't you dare think I'm the type\n"
	.string "to give up. Let's go!$"

Nexus_Text_Gardenia_Defeat3:
	.string "Heh. You're tough. I'm tougher about\n"
	.string "it. Tomorrow I'll plant two.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Gardenia é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Shaymin

A Gardenia olha a criatura como colega de ofício: ela planta uma semente por dia, e o bichinho faz um campo antes do almoço. No fragmento dela a Floresta de Eterna queimou e a única casa que sobrou é a mansão assombrada (a Old Chateau), onde ela, que tem pavor de fantasma, foi morar para guardar as sementes. As três variações: inveja de jardineira (o trabalho, não a mágica), a gratidão (a criatura agradece a quem ainda está vivo, e agradeceu a ela) e a flor que faz a criatura voar (a Gracidea), que ela guarda prensada para não perdê-la.

**Antes da luta**

> There's a little one in there that walks across dead ground and leaves flowers behind it. Every step!
>
> I've spent my whole life planting things one seed at a time. It does a whole field before lunch.
>
> I'm not jealous. I'm a LITTLE jealous. Battle!

**Derrota**

> Ha! Okay! You've got a green thumb, all right!

**Depois da luta**

> It pulls the poison out of the air and turns it into flowers. People say it's magic.
>
> It isn't. It's work. Tiny, stubborn, every-single-day work. I'd know.
>
> Go on. Be gentle. It's shy, it's small, and it's the hardest worker you'll ever meet.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gardenia_ChampionIntro:
	.string "There's a little one in there that\n"
	.string "walks across dead ground and leaves\l"
	.string "flowers behind it. Every step!\p"
	.string "I've spent my whole life planting\n"
	.string "things one seed at a time. It does a\l"
	.string "whole field before lunch.\p"
	.string "I'm not jealous. I'm a LITTLE jealous.\n"
	.string "Battle!$"

Nexus_Text_Gardenia_ChampionDefeat:
	.string "Ha! Okay! You've got a green thumb, all\n"
	.string "right!$"

Nexus_Text_Gardenia_ChampionAfter:
	.string "{SPEAKER NAME_GARDENIA}It pulls the poison out of the air and\n"
	.string "turns it into flowers. People say it's\l"
	.string "magic.\p"
	.string "It isn't. It's work. Tiny, stubborn,\n"
	.string "every-single-day work. I'd know.\p"
	.string "Go on. Be gentle. It's shy, it's small,\n"
	.string "and it's the hardest worker you'll\l"
	.string "ever meet.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a gratidão, e o dia em que ela percebeu que era com ela

**Antes da luta**

> They call it the Gratitude Pokémon. You know what I asked myself? Grateful for what?
>
> It walks across ash. It breathes smoke. Nobody ever thanks it back.
>
> So I do. Every morning. Out loud. Now let's battle!

**Derrota**

> Thank you! No, really. That was a good one.

**Depois da luta**

> I think it's grateful for anything that's still alive. A weed. A bug. A girl who's scared of the dark.
>
> One day I figured out it was thanking ME. I cried in front of a hedgehog. Don't tell anyone.
>
> Go on. And say thank you when you meet it. It'll pretend it didn't hear. It heard.

**Variação 3** — a flor que faz voar, guardada prensada por egoísmo

**Antes da luta**

> There's a flower that makes it fly. A little pink one. It smells it, and it just… lifts off the ground.
>
> I've got one pressed in my notebook. I never let it smell it. I didn't want it to leave.
>
> …That's selfish, huh? Battle me. I need to think.

**Derrota**

> Okay. Okay. I'll let it go. After lunch.

**Depois da luta**

> When it flies, it scatters seeds from the sky. A whole field at once. Everything comes back.
>
> It'd fix my forest in one afternoon. And then it'd be gone, and I'd be alone with the ghosts again.
>
> Go. If it wants to fly, let it. …I'm working on it. I'm getting there.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gardenia_ChampionIntro2:
	.string "They call it the Gratitude Pokémon. You\n"
	.string "know what I asked myself? Grateful for\l"
	.string "what?\p"
	.string "It walks across ash. It breathes\n"
	.string "smoke. Nobody ever thanks it back.\p"
	.string "So I do. Every morning. Out loud. Now\n"
	.string "let's battle!$"

Nexus_Text_Gardenia_ChampionDefeat2:
	.string "Thank you! No, really. That was a good\n"
	.string "one.$"

Nexus_Text_Gardenia_ChampionAfter2:
	.string "{SPEAKER NAME_GARDENIA}I think it's grateful for anything\n"
	.string "that's still alive. A weed. A bug. A girl\l"
	.string "who's scared of the dark.\p"
	.string "One day I figured out it was thanking\n"
	.string "ME. I cried in front of a hedgehog.\l"
	.string "Don't tell anyone.\p"
	.string "Go on. And say thank you when you meet\n"
	.string "it. It'll pretend it didn't hear. It\l"
	.string "heard.$"

Nexus_Text_Gardenia_ChampionIntro3:
	.string "There's a flower that makes it fly. A\n"
	.string "little pink one. It smells it, and it\l"
	.string "just… lifts off the ground.\p"
	.string "I've got one pressed in my notebook. I\n"
	.string "never let it smell it. I didn't want it\l"
	.string "to leave.\p"
	.string "…That's selfish, huh? Battle me. I need\n"
	.string "to think.$"

Nexus_Text_Gardenia_ChampionDefeat3:
	.string "Okay. Okay. I'll let it go. After lunch.$"

Nexus_Text_Gardenia_ChampionAfter3:
	.string "{SPEAKER NAME_GARDENIA}When it flies, it scatters seeds from\n"
	.string "the sky. A whole field at once.\l"
	.string "Everything comes back.\p"
	.string "It'd fix my forest in one afternoon.\n"
	.string "And then it'd be gone, and I'd be alone\l"
	.string "with the ghosts again.\p"
	.string "Go. If it wants to fly, let it. …I'm\n"
	.string "working on it. I'm getting there.$"
```

</details>

Falante novo: `SP_NAME_GARDENIA` (ainda não existe em `include/constants/speaker_names.h`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/gardenia/`](diario_looker/gardenia/) ([formato e fios](../DIARIO_LOOKER.md)): [`1_comeco.md`](diario_looker/gardenia/1_comeco.md), [`2_meio.md`](diario_looker/gardenia/2_meio.md), [`3_fim.md`](diario_looker/gardenia/3_fim.md). Labels `Nexus_Text_Diary_Gardenia_1` a `_3`.
