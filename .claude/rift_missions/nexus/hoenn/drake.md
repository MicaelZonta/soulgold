# Drake

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Drake — Dragão** (Hoenn · Elite Four e Campeões) — marinheiro veterano que respeita a ligação entre pessoas e Pokémon.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_DRAKE` | `graphics/object_events/pics/people/elite_four/drake.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_DRAKE` | `graphics/trainers/front_pics/elite_four_drake.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_DRAKE`, campeão de Raging Bolt e Regidrago. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Eternatus** (Veneno/Dragão, o dragão que caiu do céu num meteoro: o maior dragão que o Drake já viu, e o que não tem parceiro nenhum); semi-lendário **Raging Bolt** (Elétrico/Dragão, o dragão ancestral que carrega a tempestade nas costas, de quem ele é campeão); Mega **Salamence** (Dragotite; em ORAS é o ás dele e mega-evolui). Mais **Flygon**, **Altaria** e **Kingdra**, do time dele em Emerald.

*Plano (Singles):* o Salamence entra com Intimidate e sobe Dragon Dance para a Mega (Aerilate) varrer; o Eternatus segura com Recover; a Altaria limpa boosts com Haze; o Flygon de Scarf faz pivot de U-turn; o Kingdra usa Focus Energy com Sniper e Scope Lens; o Raging Bolt sobe Calm Mind e fecha com Thunderclap.

*Plano (Doubles):* Altaria põe Tailwind, Salamence dá Intimidate; o Flygon usa Rock Slide em área (o Earthquake só com Salamence, Altaria ou Flygon ao lado); o Eternatus e o Raging Bolt batem forte sob Tailwind.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Eternatus | Leftovers | Pressure | Timid | Dynamax Cannon, Sludge Bomb, Flamethrower, Recover |
| Raging Bolt | Booster Energy | Protosynthesis | Modest | Thunderclap, Draco Meteor, Dragon Pulse, Calm Mind |
| Salamence | Dragotite | Intimidate | Adamant | Double-Edge, Dragon Claw, Earthquake, Dragon Dance |
| Flygon | Choice Scarf | Levitate | Jolly | Earthquake, Outrage, Rock Slide, U-turn |
| Altaria | Leftovers | Natural Cure | Bold | Tailwind, Roost, Dragon Pulse, Haze |
| Kingdra | Scope Lens | Sniper | Modest | Focus Energy, Hydro Pump, Draco Meteor, Ice Beam |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_DRAKE ===
Name: Drake
Class: Elite Four
Pic: Elite Four Drake
Gender: Male
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Eternatus @ Leftovers
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dynamax Cannon
- Sludge Bomb
- Flamethrower
- Recover

Raging Bolt @ Booster Energy
Modest Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderclap
- Draco Meteor
- Dragon Pulse
- Calm Mind

Salamence @ Dragotite
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Dragon Claw
- Earthquake
- Dragon Dance

Flygon @ Choice Scarf
Jolly Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earthquake
- Outrage
- Rock Slide
- U-turn

Altaria @ Leftovers
Bold Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Roost
- Dragon Pulse
- Haze

Kingdra @ Scope Lens
Modest Nature
Level: 100
Ability: Sniper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Focus Energy
- Hydro Pump
- Draco Meteor
- Ice Beam
```

</details>


### Lendário associado

#### Raging Bolt

📝 **Proposta de 27/09/2026, aguardando o autor.** **Raging Bolt**. Drake é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Drake, o último da Elite Four de Hoenn, mestre dos Dragões. Velho de ar de marinheiro, sempre pergunta o que é preciso para lutar com um Pokémon como parceiro.

**A criatura.** Raging Bolt, Pokémon Paradoxo antigo (Elétrico/Dragão), parente pré-histórico de uma fera lendária do trovão. Pescoço longo e uma nuvem de tempestade nas costas.

**O fragmento.** Uma planície de pedra queimada sob uma tempestade que nunca acaba. Os raios caem sempre no mesmo ponto, como se alguma coisa ali os chamasse.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A plain of burned stone under a storm that never ended.
>
> The lightning kept striking the same spot, over and over, as if something there kept calling it down.

**Boss**

> The spot where the lightning struck stood up.
>
> It had a neck like a mountain ridge, and a thundercloud sat on its back like a saddle.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1021. The Storm Rider.
>
> An endless storm, and an old sailor who said he had weathered worse.
>
> What you brought back is small, and its hair stands on end. He has not weathered worse. He simply refuses to admit it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_RagingBolt_Arrival:
	.string "A plain of burned stone under a storm\n"
	.string "that never ended.\p"
	.string "The lightning kept striking the same\n"
	.string "spot, over and over, as if something\l"
	.string "there kept calling it down.$"

Nexus_Text_RagingBolt_Boss:
	.string "The spot where the lightning struck\n"
	.string "stood up.\p"
	.string "It had a neck like a mountain ridge, and\n"
	.string "a thundercloud sat on its back like a\l"
	.string "saddle.$"

Nexus_Text_RagingBolt_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1021. The Storm Rider.\p"
	.string "An endless storm, and an old sailor who\n"
	.string "said he had weathered worse.\p"
	.string "What you brought back is small, and its\n"
	.string "hair stands on end. He has not\l"
	.string "weathered worse. He simply refuses to\l"
	.string "admit it.$"
```

</details>


#### Regidrago

📝 **Proposta de 27/09/2026, aguardando o autor.** **Regidrago**. Drake é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Drake, o mestre dos Dragões da Elite Four de Hoenn.

**A criatura.** Regidrago, o Regi de Galar feito de energia de dragão cristalizada (Dragão). O corpo lembra a cabeça de um dragão antigo; há uma teoria de que os braços dele já foram essa cabeça.

**O fragmento.** Ruínas de pedra onde toda parede é uma cabeça de dragão entalhada. Só cabeças, nenhum corpo. No centro, um cristal verde pulsa como um coração.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Ruins of carved stone, and every wall was a dragon's head.
>
> Heads, and only heads. No bodies anywhere.
>
> In the center, a green crystal pulsed like a heart.

**Boss**

> The crystal went dark.
>
> In the walls, stone jaws opened, and all of them moved together.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-895. The Head Without a Dragon.
>
> Ruins that remember only a dragon's teeth, and an old man who has spent his life asking what a dragon needs besides them.
>
> What came back with you is small, and it follows me around the office. He says the answer is a partner. He said it very quietly.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Regidrago_Arrival:
	.string "Ruins of carved stone, and every wall\n"
	.string "was a dragon's head.\p"
	.string "Heads, and only heads. No bodies\n"
	.string "anywhere.\p"
	.string "In the center, a green crystal pulsed\n"
	.string "like a heart.$"

Nexus_Text_Regidrago_Boss:
	.string "The crystal went dark.\p"
	.string "In the walls, stone jaws opened, and all\n"
	.string "of them moved together.$"

Nexus_Text_Regidrago_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-895. The Head Without a Dragon.\p"
	.string "Ruins that remember only a dragon's\n"
	.string "teeth, and an old man who has spent his\l"
	.string "life asking what a dragon needs\l"
	.string "besides them.\p"
	.string "What came back with you is small, and it\n"
	.string "follows me around the office. He says\l"
	.string "the answer is a partner. He said it very\l"
	.string "quietly.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Drake cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I am Drake, and I have sailed a long way to be here.
>
> Dragons are wild things. Free things. They do not need us.
>
> So when one chooses to fight beside you, that is not obedience. It is a gift.
>
> Show me you know the difference!

**Derrota**

> Superb, it should be said. You know the difference.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Drake_Intro:
	.string "I am Drake, and I have sailed a long way\n"
	.string "to be here.\p"
	.string "Dragons are wild things. Free things.\n"
	.string "They do not need us.\p"
	.string "So when one chooses to fight beside\n"
	.string "you, that is not obedience. It is a\l"
	.string "gift.\p"
	.string "Show me you know the difference!$"

Nexus_Text_Drake_Defeat:
	.string "Superb, it should be said. You know the\n"
	.string "difference.$"
```

</details>


### Diálogo associado ao lendário

#### Raging Bolt

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Drake é o **campeão**, a luta logo antes do Raging Bolt. A fala é sobre a criatura, sem dizer o nome dele.

O Drake é homem do mar: todo marinheiro aprende que não se luta contra a tempestade, se atravessa. Aqui ele vê um dragão que simplesmente pegou a tempestade e foi embora com ela. Ele gosta. A virada: anos com medo do tempo que não podia mudar, e a liberdade é não ter medo do que se carrega.

**Antes da luta**

> Did you see it, under that storm? It carries the thundercloud on its back.
>
> Every sailor learns the same lesson. You do not fight a storm. You ride it out.
>
> That beast never learned. It just picked the storm up and walked off with it.
>
> Ha! I like it. Come!

**Derrota**

> Superb. You rode it out.

**Depois da luta**

> I spent years at sea, fearing weather I could not change.
>
> And here is a dragon that simply decided the storm was his.
>
> Freedom, I suppose, is refusing to be afraid of what you carry.
>
> Go. Do not fight the storm. Fight the one holding it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Drake_RagingBolt_ChampionIntro:
	.string "Did you see it, under that storm? It\n"
	.string "carries the thundercloud on its back.\p"
	.string "Every sailor learns the same lesson.\n"
	.string "You do not fight a storm. You ride it\l"
	.string "out.\p"
	.string "That beast never learned. It just\n"
	.string "picked the storm up and walked off\l"
	.string "with it.\p"
	.string "Ha! I like it. Come!$"

Nexus_Text_Drake_RagingBolt_ChampionDefeat:
	.string "Superb. You rode it out.$"

Nexus_Text_Drake_RagingBolt_ChampionAfter:
	.string "{SPEAKER NAME_DRAKE}I spent years at sea, fearing weather\n"
	.string "I could not change.\p"
	.string "And here is a dragon that simply\n"
	.string "decided the storm was his.\p"
	.string "Freedom, I suppose, is refusing to be\n"
	.string "afraid of what you carry.\p"
	.string "Go. Do not fight the storm. Fight the\n"
	.string "one holding it.$"
```

</details>


#### Regidrago

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Drake é o **campeão**, a luta logo antes do Regidrago. A fala é sobre a criatura, sem dizer o nome dele.

A pergunta de sempre do Drake é o que é preciso para lutar com um dragão como parceiro. Aqui alguém construiu um dragão só de força: dentes e mandíbulas, sem asa, sem coração, sem parceiro. A virada: força é a parte fácil; os construtores esqueceram que um dragão precisa de um lugar para ir e de alguém com quem ir.

**Antes da luta**

> Do you know what I saw in those ruins? Heads. Only heads. Jaws and teeth, and nothing else.
>
> Someone once built a dragon out of nothing but power.
>
> No wings. No heart. No partner.
>
> Ha! Let me show you what it is missing!

**Derrota**

> Superb… I have taught you nothing you did not already have.

**Depois da luta**

> Power is the easy part of a dragon. Any fool can carve teeth.
>
> What those builders forgot is that a dragon needs somewhere to go, and someone to go there with.
>
> That thing has waited in the dark with its mouth open for a very long time.
>
> Show it the rest. Show it a partner.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Drake_Regidrago_ChampionIntro:
	.string "Do you know what I saw in those ruins?\n"
	.string "Heads. Only heads. Jaws and teeth, and\l"
	.string "nothing else.\p"
	.string "Someone once built a dragon out of\n"
	.string "nothing but power.\p"
	.string "No wings. No heart. No partner.\p"
	.string "Ha! Let me show you what it is missing!$"

Nexus_Text_Drake_Regidrago_ChampionDefeat:
	.string "Superb… I have taught you nothing you\n"
	.string "did not already have.$"

Nexus_Text_Drake_Regidrago_ChampionAfter:
	.string "{SPEAKER NAME_DRAKE}Power is the easy part of a dragon. Any\n"
	.string "fool can carve teeth.\p"
	.string "What those builders forgot is that a\n"
	.string "dragon needs somewhere to go, and\l"
	.string "someone to go there with.\p"
	.string "That thing has waited in the dark with\n"
	.string "its mouth open for a very long time.\p"
	.string "Show it the rest. Show it a partner.$"
```

</details>


Falante novo: `SP_NAME_DRAKE` (ainda não existe em `include/constants/speaker_names.h`).
