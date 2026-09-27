# Lucy

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Lucy — Battle Pike** (Hoenn · Battle Frontier — Frontier Brains) — misteriosa chefe de um desafio baseado em escolhas e sorte.

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
| `OBJ_EVENT_GFX_LUCY` | `graphics/object_events/pics/people/frontier_brains/lucy.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PIKE_QUEEN_LUCY` | `graphics/trainers/front_pics/pike_queen_lucy.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LUCY` | 810 | 0x82A | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LUCY`, campeão de Zygarde e Iron Jugulis. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zygarde**, semi-lendário **Iron Jugulis**, Mega **Steelix** (Steeltite). A Battle Pike tem a forma de um Seviper, e o time da Lucy aqui é **só serpente**: o Zygarde da Forma 50% é uma serpente de células, o Iron Jugulis é o futuro do Hydreigon, e com eles vêm Seviper (o ás dela), Milotic, Mega Steelix e Serperior. *Plano:* **paralisar e apertar.** Glare do Seviper e do Serperior (não falha contra Ground como Thunder Wave), Icy Wind da Milotic e Tailwind do Iron Jugulis controlam velocidade; depois o Zygarde sobe com Dragon Dance e o Serperior com Contrary.

*Plano (Singles):* Mega Steelix arma Stealth Rock e segura com Curse; Glare no que for rápido; o Zygarde bate com Thousand Arrows (acerta até Flying e Levitate) e o Serperior limpa com Leaf Storm (que sobe o SpA). *Plano (Doubles):* Thousand Arrows e Icy Wind acertam os dois lados sem tocar no parceiro; Tailwind do Iron Jugulis no primeiro turno; Glare nos atacantes rápidos. Milotic de Competitive pune Intimidate.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zygarde | Leftovers | Aura Break | Adamant | Thousand Arrows, Outrage, Dragon Dance, Stone Edge |
| Iron Jugulis | Booster Energy | Quark Drive | Timid | Hurricane, Dark Pulse, Earth Power, Tailwind |
| Steelix | Steeltite | Sturdy | Impish | Heavy Slam, Stone Edge, Stealth Rock, Curse |
| Seviper | Focus Sash | Infiltrator | Naive | Glare, Gunk Shot, Flamethrower, Knock Off |
| Milotic | Leftovers | Competitive | Bold | Scald, Ice Beam, Icy Wind, Recover |
| Serperior | Life Orb | Contrary | Timid | Leaf Storm, Dragon Pulse, Glare, Substitute |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_LUCY ===
Name: Lucy
Class: Pike Queen
Pic: Pike Queen Lucy
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Zygarde @ Leftovers
Adamant Nature
Level: 100
Ability: Aura Break
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thousand Arrows
- Outrage
- Dragon Dance
- Stone Edge

Iron Jugulis @ Booster Energy
Timid Nature
Level: 100
Ability: Quark Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Dark Pulse
- Earth Power
- Tailwind

Steelix @ Steeltite
Impish Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Stone Edge
- Stealth Rock
- Curse

Seviper @ Focus Sash
Naive Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Glare
- Gunk Shot
- Flamethrower
- Knock Off

Milotic @ Leftovers
Bold Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Ice Beam
- Icy Wind
- Recover

Serperior @ Life Orb
Timid Nature
Level: 100
Ability: Contrary
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leaf Storm
- Dragon Pulse
- Glare
- Substitute
```

</details>


### Lendário associado

#### Zygarde

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zygarde**. Lucy é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lucy, Pike Queen da Battle Frontier de Hoenn, calada e dura, dona do desafio de escolhas e sorte da Battle Pike, prédio com a forma de um Seviper.

**A criatura.** Guardião do ecossistema de Kalos. Vive espalhado em Cells e Cores, que vigiam em silêncio; quando a ordem do mundo é ameaçada, se juntam em formas maiores: 10%, 50% (uma serpente) e Complete.

**O fragmento.** Uma floresta onde cada folha verde tem um ponto que pisca, devagar, como um olho. Os pontos seguem quem anda. Não há vento, e mesmo assim as folhas se viram na sua direção.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest where every green leaf had a small point of light on it, blinking slowly, like an eye.
>
> There was no wind. The leaves turned to follow you anyway.

**Boss**

> All the points of light left the leaves at once and ran together along the ground.
>
> They made a shape. Long, green and black, coiled, watching.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-718. Order.
>
> A forest that watches, and a woman who says so little that it listened back.
>
> What came back with you is one small green cell. It sits on my desk, blinking. I do not think it is waiting for me. I think it is counting.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zygarde_Arrival:
	.string "A forest where every green leaf had a\n"
	.string "small point of light on it, blinking\l"
	.string "slowly, like an eye.\p"
	.string "There was no wind. The leaves turned to\n"
	.string "follow you anyway.$"

Nexus_Text_Zygarde_Boss:
	.string "All the points of light left the leaves\n"
	.string "at once and ran together along the\l"
	.string "ground.\p"
	.string "They made a shape. Long, green and\n"
	.string "black, coiled, watching.$"

Nexus_Text_Zygarde_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-718. Order.\p"
	.string "A forest that watches, and a woman who\n"
	.string "says so little that it listened back.\p"
	.string "What came back with you is one small\n"
	.string "green cell. It sits on my desk, blinking.\l"
	.string "I do not think it is waiting for me. I\l"
	.string "think it is counting.$"
```

</details>


#### Iron Jugulis

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Jugulis**. Lucy é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lucy, a Pike Queen; na Battle Pike o desafiante escolhe uma de três portas sem saber o que há atrás.

**A criatura.** Paradoxo do futuro, descrito no Violet Book com a forma de um Hydreigon de metal. Voa por jatos, e as duas cabeças laterais parecem ser só braços, como as do Hydreigon.

**O fragmento.** Um céu noturno sem estrelas, riscado por três luzes que voam juntas. Duas delas mudam de direção ao mesmo tempo; a do meio segue sem olhar. Abaixo, três portas de metal fincadas no nada.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A night sky with no stars in it, crossed by three lights flying together.
>
> The two outer lights turned at the same moment. The middle one followed without looking.
>
> Below them stood three metal doors, in nothing at all.

**Boss**

> One of the doors swung open on its own.
>
> Behind it there was only sky, and three lights coming straight at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-993. Blind Sky.
>
> Three doors and three lights, and a woman who has always chosen doors without looking.
>
> What came back with you bumps into things. Gently. It trusts the room to be there. I have moved the lamp.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronJugulis_Arrival:
	.string "A night sky with no stars in it, crossed\n"
	.string "by three lights flying together.\p"
	.string "The two outer lights turned at the\n"
	.string "same moment. The middle one followed\l"
	.string "without looking.\p"
	.string "Below them stood three metal doors, in\n"
	.string "nothing at all.$"

Nexus_Text_IronJugulis_Boss:
	.string "One of the doors swung open on its own.\p"
	.string "Behind it there was only sky, and three\n"
	.string "lights coming straight at you.$"

Nexus_Text_IronJugulis_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-993. Blind Sky.\p"
	.string "Three doors and three lights, and a\n"
	.string "woman who has always chosen doors\l"
	.string "without looking.\p"
	.string "What came back with you bumps into\n"
	.string "things. Gently. It trusts the room to\l"
	.string "be there. I have moved the lamp.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lucy cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> …Lucy.
>
> I don't talk much. At the Pike, you pick a door, and you live with what's behind it.
>
> I picked one, and I ended up here. …I'm living with it. Your turn.

**Derrota**

> …Hmph. Fine. That one was yours.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_Intro:
	.string "…Lucy.\p"
	.string "I don't talk much. At the Pike, you pick\n"
	.string "a door, and you live with what's behind\l"
	.string "it.\p"
	.string "I picked one, and I ended up here. …I'm\n"
	.string "living with it. Your turn.$"

Nexus_Text_Lucy_Defeat:
	.string "…Hmph. Fine. That one was yours.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lucy é a campeã, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Zygarde

A Lucy quase não fala, e reconhece na criatura da floresta uma igual: ela não fala nada, só vigia e conta. A virada é que a Lucy percebe que a criatura não é calada por ser fria: é calada porque está prestando atenção em tudo ao mesmo tempo. E a Lucy admite, do jeito dela, em quatro palavras, que também é assim: fica quieta porque está contando.

**Antes da luta**

> …You felt it. The leaves. Watching.
>
> It doesn't talk either. It just counts. Every tree. Every step.
>
> People think I'm quiet because I'm cold.
>
> …I'm counting too. Go.

**Derrota**

> …Counted wrong. Hmph.

**Depois da luta**

> …That thing doesn't hate us. It's keeping track.
>
> Every cell is watching a piece of the forest, so nothing gets lost.
>
> At the Pike, I watch every door. Nobody notices.
>
> …Go. It noticed you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_Zygarde_ChampionIntro:
	.string "…You felt it. The leaves. Watching.\p"
	.string "It doesn't talk either. It just counts.\n"
	.string "Every tree. Every step.\p"
	.string "People think I'm quiet because I'm\n"
	.string "cold.\p"
	.string "…I'm counting too. Go.$"

Nexus_Text_Lucy_Zygarde_ChampionDefeat:
	.string "…Counted wrong. Hmph.$"

Nexus_Text_Lucy_Zygarde_ChampionAfter:
	.string "{SPEAKER NAME_LUCY}…That thing doesn't hate us. It's\n"
	.string "keeping track.\p"
	.string "Every cell is watching a piece of the\n"
	.string "forest, so nothing gets lost.\p"
	.string "At the Pike, I watch every door. Nobody\n"
	.string "notices.\p"
	.string "…Go. It noticed you.$"
```

</details>


#### Iron Jugulis

A Battle Pike é escolher porta sem ver o que tem atrás; a Lucy vive disso. A criatura do céu é o mesmo: a cabeça do meio segue as outras duas no escuro, sem olhar, e não erra. A virada: a Lucy, que parece ser a pessoa mais desconfiada de Hoenn, revela que escolher às cegas é confiança, não sorte. Ela sempre soube disso, e o Seviper dela também.

**Antes da luta**

> …Three doors. You saw them.
>
> At the Pike, you choose without seeing. People call it luck.
>
> That thing flies like that. The middle head can't see. It just trusts the other two.
>
> …It's not luck. Pick.

**Derrota**

> …You picked right.

**Depois da luta**

> …You think I'm the Pike Queen because I'm lucky.
>
> No. You open a door blind because you trust what's beside you.
>
> That thing never misses in the dark. It isn't looking. It's trusting.
>
> …Go on. Door's open.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_IronJugulis_ChampionIntro:
	.string "…Three doors. You saw them.\p"
	.string "At the Pike, you choose without seeing.\n"
	.string "People call it luck.\p"
	.string "That thing flies like that. The middle\n"
	.string "head can't see. It just trusts the\l"
	.string "other two.\p"
	.string "…It's not luck. Pick.$"

Nexus_Text_Lucy_IronJugulis_ChampionDefeat:
	.string "…You picked right.$"

Nexus_Text_Lucy_IronJugulis_ChampionAfter:
	.string "{SPEAKER NAME_LUCY}…You think I'm the Pike Queen because\n"
	.string "I'm lucky.\p"
	.string "No. You open a door blind because you\n"
	.string "trust what's beside you.\p"
	.string "That thing never misses in the dark. It\n"
	.string "isn't looking. It's trusting.\p"
	.string "…Go on. Door's open.$"
```

</details>


Falante novo: `SP_NAME_LUCY` (não existe em `include/constants/speaker_names.h`).
