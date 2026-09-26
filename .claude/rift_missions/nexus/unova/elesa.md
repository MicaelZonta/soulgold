# Elesa

**Região da ficha:** Unova

Aparece no checklist como:

- **Elesa — Elétrico** (Unova · Líderes de Ginásio) — modelo famosa e Líder de Nimbasa.

**Pronto para o Nexus:** ❌ não — falta sprite de overworld e battle sprite (os dois são obrigatórios).

## Checklist

- [ ] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

Não existe. Criar com a skill `adicionar-npc`.

### Battle sprite (front pic)

Não existe. Criar com a skill `adicionar-grafico-trainer`.

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

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

📝 **Proposta de 26/09/2026, aguardando o autor.** **Pheromosa** (UB-02 Beauty). Elesa é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Ficha do Looker, no altar, no dia em que a UB é capturada**

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

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Elesa cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Elesa é o **campeão**, a luta logo antes da Pheromosa. A fala é sobre a criatura, sem dizer o nome dela.

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

