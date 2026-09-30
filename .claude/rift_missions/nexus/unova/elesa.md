# Elesa

**Região da ficha:** Unova

Aparece no checklist como:

- **Elesa — Elétrico** (Unova · Líderes de Ginásio) — modelo famosa e Líder de Nimbasa.

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
| `OBJ_EVENT_GFX_ELESA` | `graphics/object_events/pics/people/special/elesa.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELESA` | `graphics/trainers/front_pics/elesa.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ELESA` = **977** (flag de batalha `0x8D1`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Elesa_Fight` (genérica) e `Nexus_EventScript_Elesa_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Elesa.

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_ELESA`, campeão da Pheromosa. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Miraidon**, semi-lendário **Zapdos**, Mega **Eelektross** (Electrite: Eelevate), mais Zebstrika, Galvantula e Emolga. O Miraidon é o palco: acende o Electric Terrain ao entrar (Hadron Engine), e todo golpe elétrico do time sobe. *Plano:* o Zapdos põe Tailwind, a Galvantula arma Sticky Web e a Emolga prende com Encore e Light Screen. Zapdos e Emolga voam, e o Eelektross flutua, então o time não cai de uma vez para um golpe de Terra.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Miraidon | Choice Specs | Hadron Engine | Timid | Electro Drift, Draco Meteor, Volt Switch, Dazzling Gleam |
| Zapdos | Leftovers | Static | Timid | Tailwind, Thunderbolt, Hurricane, Roost |
| Eelektross | Electrite | Levitate | Modest | Thunderbolt, Flamethrower, Giga Drain, Knock Off |
| Zebstrika | Life Orb | Sap Sipper | Jolly | Supercell Slam, High Horsepower, Flame Charge, Volt Switch |
| Galvantula | Focus Sash | Compound Eyes | Timid | Sticky Web, Thunder, Bug Buzz, Energy Ball |
| Emolga | Light Clay | Motor Drive | Timid | Nuzzle, Encore, Light Screen, U-turn |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_ELESA ===
Name: Elesa
Class: Leader
Pic: Elesa
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Miraidon @ Choice Specs
Timid Nature
Level: 100
Ability: Hadron Engine
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Electro Drift
- Draco Meteor
- Volt Switch
- Dazzling Gleam

Zapdos @ Leftovers
Timid Nature
Level: 100
Ability: Static
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Thunderbolt
- Hurricane
- Roost

Eelektross @ Electrite
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flamethrower
- Giga Drain
- Knock Off

Zebstrika @ Life Orb
Jolly Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Supercell Slam
- High Horsepower
- Flame Charge
- Volt Switch

Galvantula @ Focus Sash
Timid Nature
Level: 100
Ability: Compound Eyes
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Thunder
- Bug Buzz
- Energy Ball

Emolga @ Light Clay
Timid Nature
Level: 100
Ability: Motor Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Nuzzle
- Encore
- Light Screen
- U-turn
```

</details>


### Lendário associado

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Elesa_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Pheromosa** (UB-02 Beauty). Elesa é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Elesa, líder de Nimbasa e modelo famosa.

**A criatura.** Pheromosa se recusa a tocar em qualquer coisa, talvez por sentir alguma impureza neste mundo. Emite um feromônio que deixa quem a encara confuso, como se atingido pela beleza dela. Mundo em USUM: Ultra Desert.

**O fragmento.** Areia branca e uma passarela reta, branca, iluminada por baixo. Nada deixa marca: quando o jogador olha para trás, as próprias pegadas já sumiram. Leitura visual: passarela de desfile no deserto.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> White sand, and a straight white path across it, lit from below.
>
> Nothing marked it. When you looked back, your own footprints were already gone.

**Boss**

> Someone was already standing at the end of the path. Perfectly still. Perfectly clean.
>
> For a moment, you forgot what you were doing there.

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

> File UB-02. Beauty.
>
> You described the creature, and I wrote down the word “lovely.”
>
> I have crossed it out. It is still perfectly legible. That, I think, is the whole report.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Beauty_Arrival:
	.string "White sand, and a straight white path\n"
	.string "across it, lit from below.\p"
	.string "Nothing marked it. When you looked\n"
	.string "back, your own footprints were already\l"
	.string "gone.$"

Nexus_Text_Beauty_Boss:
	.string "Someone was already standing at the\n"
	.string "end of the path. Perfectly still.\l"
	.string "Perfectly clean.\p"
	.string "For a moment, you forgot what you were\n"
	.string "doing there.$"

Nexus_Text_Beauty_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-02. Beauty.\p"
	.string "You described the creature, and I wrote\n"
	.string "down the word “lovely.”\p"
	.string "I have crossed it out. It is still\n"
	.string "perfectly legible. That, I think, is the\l"
	.string "whole report.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Elesa_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Elesa cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> No stage, no lights, no audience. This is the strangest runway I've ever walked.
>
> Well. I never stop in the middle of a show.
>
> You'll have to be my audience -- and my opponent. Try to keep up!

**Derrota**

> You made me forget my pose. Nobody does that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Elesa_Intro:
	.string "No stage, no lights, no audience. This is\n"
	.string "the strangest runway I've ever walked.\p"
	.string "Well. I never stop in the middle of a\n"
	.string "show.\p"
	.string "You'll have to be my audience -- and my\n"
	.string "opponent. Try to keep up!$"

Nexus_Text_Elesa_Defeat:
	.string "You made me forget my pose. Nobody\n"
	.string "does that.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Cada variação pega um ângulo diferente do personagem.

**Variação 2 — o Musical.** Os Pokémon Musicals de Nimbasa: ela achava que a batalha devia parecer um Musical, depois entendeu que devia ser sentida como um. O “electric” da derrota é autoironia.

**Antes da luta**

> Have you ever seen a Pokémon Musical? Costumes, lights, Pokémon dancing on a real stage.
>
> I used to think my battles should look like that. Then I learned they should feel like that.
>
> Show me how yours feel!

**Derrota**

> That felt electric. …Yes, I say that a lot. It's still true.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Elesa_Intro2:
	.string "Have you ever seen a Pokémon Musical?\n"
	.string "Costumes, lights, Pokémon dancing on a\l"
	.string "real stage.\p"
	.string "I used to think my battles should look\n"
	.string "like that. Then I learned they should\l"
	.string "feel like that.\p"
	.string "Show me how yours feel!$"

Nexus_Text_Elesa_Defeat2:
	.string "That felt electric. …Yes, I say that a\n"
	.string "lot. It's still true.$"
```

</details>

**Variação 3 — o visual de uma estação.** A Elesa muda de visual toda estação (BW → BW2). Aqui não há estações, e ela está há tempo demais com o mesmo. Um momento de insegurança que a batalha resolve.

**Antes da luta**

> I change my look every season. People expect it.
>
> There are no seasons here, so I've kept this one far too long. Be honest -- is it working?
>
> …Never mind. Your battle will tell me.

**Derrota**

> So it's the battle that shines, not the outfit. Noted.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Elesa_Intro3:
	.string "I change my look every season. People\n"
	.string "expect it.\p"
	.string "There are no seasons here, so I've kept\n"
	.string "this one far too long. Be honest -- is it\l"
	.string "working?\p"
	.string "…Never mind. Your battle will tell me.$"

Nexus_Text_Elesa_Defeat3:
	.string "So it's the battle that shines, not the\n"
	.string "outfit. Noted.$"
```

</details>



### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Elesa_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Elesa é o **campeão**, a luta logo antes da Pheromosa. A fala é sobre a criatura, sem dizer o nome dela.

A Elesa só viu a criatura de longe, porque ela não deixa nada chegar perto: move-se como a última coisa limpa do mundo e olha todo o resto como uma mancha. Todo mundo para e encara, e a Elesa conhece esse olhar do outro lado, de uma carreira inteira. A vitória do jogador: ele nunca encarou, estava ocupado lutando. O que fica: ser admirado não é ser amado, é mais solitário, e a criatura acha que nunca ter sido tocada é perfeição. "Vá mostrar o que ela está perdendo. Suje as mãos."

**Antes da luta**

> I've seen it. From a distance -- it won't allow anything closer.
>
> It moves like the only clean thing left in the world, and it looks at everything else like a stain.
>
> Everyone who sees it stops and stares. I know that look. I've been on the other side of it my whole career.
>
> …Enough. Battle me. And don't you dare just stand there staring.

**Derrota**

> You never stared once. You were too busy fighting. …Good.

**Depois da luta**

> People think being admired is the same as being loved. It isn't. It's lonelier.
>
> That creature has never been touched by anything in its life, and it thinks that's perfection.
>
> Go show it what it's missing. Get your hands dirty.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Elesa_ChampionIntro:
	.string "I've seen it. From a distance -- it\n"
	.string "won't allow anything closer.\p"
	.string "It moves like the only clean thing left\n"
	.string "in the world, and it looks at everything\l"
	.string "else like a stain.\p"
	.string "Everyone who sees it stops and stares.\n"
	.string "I know that look. I've been on the\l"
	.string "other side of it my whole career.\p"
	.string "…Enough. Battle me. And don't you dare\n"
	.string "just stand there staring.$"

Nexus_Text_Elesa_ChampionDefeat:
	.string "You never stared once. You were too\n"
	.string "busy fighting. …Good.$"

Nexus_Text_Elesa_ChampionAfter:
	.string "{SPEAKER NAME_ELESA}People think being admired is the same\n"
	.string "as being loved. It isn't. It's lonelier.\p"
	.string "That creature has never been touched\n"
	.string "by anything in its life, and it thinks\l"
	.string "that's perfection.\p"
	.string "Go show it what it's missing. Get your\n"
	.string "hands dirty.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1: sobre a criatura, pelo olhar dele, sem dizer o nome da espécie. Labels no padrão `Nexus_Text_Elesa_Champion*` + sufixo.

**Variação 2 — um dia andando como ela.** A Elesa tentou andar como a criatura por um dia inteiro: linha reta, sem erro, sem tocar em nada. À noite não lembrava a última vez que tinha rido. A dica: a criatura hesita antes do contato.

**Antes da luta**

> I tried to walk like it. For a whole day. Straight lines, no mistakes, never touching anything.
>
> By evening, I couldn't remember the last time I'd laughed.
>
> It must never laugh. Laughing is messy.
>
> So let's be messy. Battle me!

**Derrota**

> Ha! That was a disaster. I loved it.

**Depois da luta**

> It's faster than anything I've ever seen, but it hates to be touched. It hesitates, right before contact.
>
> That's where you catch it. The moment it decides whether you're worth getting dirty for.
>
> Be worth it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Elesa_ChampionIntro2:
	.string "I tried to walk like it. For a whole day.\n"
	.string "Straight lines, no mistakes, never\l"
	.string "touching anything.\p"
	.string "By evening, I couldn't remember the\n"
	.string "last time I'd laughed.\p"
	.string "It must never laugh. Laughing is messy.\p"
	.string "So let's be messy. Battle me!$"

Nexus_Text_Elesa_ChampionDefeat2:
	.string "Ha! That was a disaster. I loved it.$"

Nexus_Text_Elesa_ChampionAfter2:
	.string "{SPEAKER NAME_ELESA}It's faster than anything I've ever\n"
	.string "seen, but it hates to be touched. It\l"
	.string "hesitates, right before contact.\p"
	.string "That's where you catch it. The moment\n"
	.string "it decides whether you're worth\l"
	.string "getting dirty for.\p"
	.string "Be worth it.$"
```

</details>

**Variação 3 — a primeira fila.** A noite em que a criatura foi a um desfile dela: primeira fila, ninguém sentou ao lado, e na metade do show toda a plateia virou para olhá-la. A Elesa terminou a passarela sem ninguém olhando. O que fica: deixar marca, das grandes.

**Antes da luta**

> It came to one of my shows once. Front row. The only seat nobody would sit beside.
>
> Halfway through, every head in the house had turned around to look at it instead of me.
>
> I kept walking. I finished the runway. Nobody was watching.
>
> …Watch me now. That's all I ask.

**Derrota**

> You watched until the end. Thank you. Really.

**Depois da luta**

> After the show, it left without a sound. Not a single footprint.
>
> I'd give a lot to leave no marks. And I'd hate every second of it.
>
> When you face it, leave a mark. A big, messy, wonderful one.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Elesa_ChampionIntro3:
	.string "It came to one of my shows once. Front\n"
	.string "row. The only seat nobody would sit\l"
	.string "beside.\p"
	.string "Halfway through, every head in the\n"
	.string "house had turned around to look at it\l"
	.string "instead of me.\p"
	.string "I kept walking. I finished the runway.\n"
	.string "Nobody was watching.\p"
	.string "…Watch me now. That's all I ask.$"

Nexus_Text_Elesa_ChampionDefeat3:
	.string "You watched until the end. Thank you.\n"
	.string "Really.$"

Nexus_Text_Elesa_ChampionAfter3:
	.string "{SPEAKER NAME_ELESA}After the show, it left without a sound.\n"
	.string "Not a single footprint.\p"
	.string "I'd give a lot to leave no marks. And\n"
	.string "I'd hate every second of it.\p"
	.string "When you face it, leave a mark. A big,\n"
	.string "messy, wonderful one.$"
```

</details>

