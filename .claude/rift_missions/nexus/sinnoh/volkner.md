# Volkner

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Volkner — Elétrico** (Sinnoh · Líderes de Ginásio) — talentoso Líder de Sunyshore que busca um desafio verdadeiro.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_VOLKNER`, campeão da Xurkitree. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zekrom**, semi-lendário **Raikou**, Mega **Raichu** (Electrite: Mega Raichu X, com Electric Surge), mais Luxray, Electivire e Ambipom. Raichu, Ambipom, Electivire e Luxray são do time dele em Platinum; o Raikou é o trovão de Johto. *Plano:* um gerador. A Mega Raichu X liga o terreno ao megaevoluir, o Zekrom sobe com Dragon Dance e o Raikou de Specs gira com Volt Switch. Em Doubles, dois Fake Outs (Raichu e Ambipom) e o Intimidate do Luxray.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zekrom | Life Orb | Teravolt | Adamant | Bolt Strike, Dragon Claw, Stone Edge, Dragon Dance |
| Raikou | Choice Specs | Pressure | Timid | Thunderbolt, Shadow Ball, Extrasensory, Volt Switch |
| Raichu | Electrite | Static | Timid | Fake Out, Thunderbolt, Grass Knot, Nasty Plot |
| Luxray | Choice Band | Intimidate | Adamant | Wild Charge, Crunch, Ice Fang, Play Rough |
| Electivire | Expert Belt | Motor Drive | Adamant | Wild Charge, Ice Punch, Cross Chop, Earthquake |
| Ambipom | Silk Scarf | Technician | Jolly | Fake Out, Double Hit, U-turn, Knock Off |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_VOLKNER ===
Name: Volkner
Class: Leader
Pic: Volkner
Gender: Male
Music: Cool
Double Battle: No
AI: Smart Trainer

Zekrom @ Life Orb
Adamant Nature
Level: 100
Ability: Teravolt
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bolt Strike
- Dragon Claw
- Stone Edge
- Dragon Dance

Raikou @ Choice Specs
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Shadow Ball
- Extrasensory
- Volt Switch

Raichu @ Electrite
Timid Nature
Level: 100
Ability: Static
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Thunderbolt
- Grass Knot
- Nasty Plot

Luxray @ Choice Band
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wild Charge
- Crunch
- Ice Fang
- Play Rough

Electivire @ Expert Belt
Adamant Nature
Level: 100
Ability: Motor Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wild Charge
- Ice Punch
- Cross Chop
- Earthquake

Ambipom @ Silk Scarf
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Double Hit
- U-turn
- Knock Off
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Xurkitree** (UB-03 Lighting). Volkner é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Volkner, líder de Sunyshore. Em Platinum, entediado e sem desafiantes à altura, ele reformou os equipamentos elétricos do ginásio e a cidade ficou sem luz.

**A criatura.** A Pokédex conta que a Xurkitree invadiu uma usina elétrica, e por isso se acha que ela se alimenta de eletricidade. Mundo em USUM: Ultra Plant.

**O fragmento.** Uma cidade de torres e cabos sob um céu sem estrelas. Todas as janelas apagadas, menos uma, lá no alto, queimando em branco. Todos os cabos correm até ela.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A city of towers and cables, under a sky with no stars.
>
> Every window was dark but one, high up, burning white. All the cables ran toward it.

**Boss**

> Every cable in the room went taut at once.
>
> The window flickered, and something that was mostly wire stood up in the light.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB-03. Lighting.
>
> The old file says the creature once emptied a power plant. Your witness says he once emptied a town, for a good battle.
>
> I find I am not sure which of the two I am filing.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Lighting_Arrival:
	.string "A city of towers and cables, under a sky\n"
	.string "with no stars.\p"
	.string "Every window was dark but one, high up,\n"
	.string "burning white. All the cables ran toward\l"
	.string "it.$"

Nexus_Text_Lighting_Boss:
	.string "Every cable in the room went taut at\n"
	.string "once.\p"
	.string "The window flickered, and something\n"
	.string "that was mostly wire stood up in the\l"
	.string "light.$"

Nexus_Text_Lighting_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-03. Lighting.\p"
	.string "The old file says the creature once\n"
	.string "emptied a power plant. Your witness\l"
	.string "says he once emptied a town, for a good\l"
	.string "battle.\p"
	.string "I find I am not sure which of the two I\n"
	.string "am filing.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Volkner cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Huh. A challenger. Out here, of all places.
>
> I've been bored so long I stopped noticing where I was.
>
> Go on. Give me a reason to pay attention.

**Derrota**

> Ha… That's more like it. Now I'm awake.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Volkner_Intro:
	.string "Huh. A challenger. Out here, of all\n"
	.string "places.\p"
	.string "I've been bored so long I stopped\n"
	.string "noticing where I was.\p"
	.string "Go on. Give me a reason to pay\n"
	.string "attention.$"

Nexus_Text_Volkner_Defeat:
	.string "Ha… That's more like it. Now I'm awake.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Volkner é o **campeão**, a luta logo antes da Xurkitree. A fala é sobre a criatura, sem dizer o nome dela.

A criatura está secando a cidade rua por rua, e o Volkner queria odiá-la, mas é o último com esse direito: ele mesmo apagou a própria cidade para ter o que fazer. Ele se reconhece nela. A vitória do jogador é a faísca que vale todo aquele escuro. O que fica: ela não é cruel, só está com fome e achou uma cidade inteira para comer, e é exatamente isso que o assusta, porque ele entende.

**Antes da luta**

> See that light up there? That's it. It's been drinking this city dry, one street at a time.
>
> I'd like to say I hate it. I'm the last guy who gets to.
>
> Back home I pulled so much power into my Gym that the whole town went dark. Just so I'd have something to do.
>
> So. Show me you're the kind of spark worth all that dark.

**Derrota**

> …Yeah. That's the kind. Worth every light in town.

**Depois da luta**

> That thing isn't cruel. It's hungry, and it found a whole city to eat.
>
> I get it. That's what scares me.
>
> Go pull the plug on it, challenger. I'll be here, learning to be bored in the dark.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Volkner_ChampionIntro:
	.string "See that light up there? That's it.\n"
	.string "It's been drinking this city dry, one\l"
	.string "street at a time.\p"
	.string "I'd like to say I hate it. I'm the last\n"
	.string "guy who gets to.\p"
	.string "Back home I pulled so much power into\n"
	.string "my Gym that the whole town went dark.\l"
	.string "Just so I'd have something to do.\p"
	.string "So. Show me you're the kind of spark\n"
	.string "worth all that dark.$"

Nexus_Text_Volkner_ChampionDefeat:
	.string "…Yeah. That's the kind. Worth every\n"
	.string "light in town.$"

Nexus_Text_Volkner_ChampionAfter:
	.string "{SPEAKER NAME_VOLKNER}That thing isn't cruel. It's hungry, and\n"
	.string "it found a whole city to eat.\p"
	.string "I get it. That's what scares me.\p"
	.string "Go pull the plug on it, challenger. I'll\n"
	.string "be here, learning to be bored in the\l"
	.string "dark.$"
```

</details>

