# Lucy

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Lucy — Battle Pike** (Hoenn · Battle Frontier — Frontier Brains) — misteriosa chefe de um desafio baseado em escolhas e sorte.

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

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_LUCY` = **1031** (flag de batalha `0x907`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Lucy_Fight`; campeão: `Nexus_EventScript_Lucy_IronJugulis_ChampionFight` (para Iron Jugulis), `Nexus_EventScript_Lucy_Zygarde_ChampionFight` (para Zygarde). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Lucy.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zygarde_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronJugulis_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lucy_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a porta da Pike e viver com o que há atrás. Na 2, a birra do Seviper com Zangoose (a rivalidade clássica) e a dela com quem fala durante a luta: a Lucy elogia o silêncio do jogador. Na 3, o R21: no fragmento dela a última sala da Pike tem quatro portas, e ninguém abriu a quarta; ela diz que não tem curiosidade, e admite que é mentira (a quarta porta é o miolo do diário).

**Variação 2 — o que ela odeia**

**Antes da luta**

> …
>
> My Seviper hates one thing. The white ones with claws.
>
> I used to hate one thing too. People who talk during battle.
>
> …You're not talking. Good. Start.

**Derrota**

> …You didn't say a word. I like that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_Intro2:
	.string "…\p"
	.string "My Seviper hates one thing. The white\n"
	.string "ones with claws.\p"
	.string "I used to hate one thing too. People\n"
	.string "who talk during battle.\p"
	.string "…You're not talking. Good. Start.$"

Nexus_Text_Lucy_Defeat2:
	.string "…You didn't say a word. I like that.$"
```

</details>

**Variação 3 — a quarta porta**

**Antes da luta**

> …Lucy.
>
> Where I'm from, the Pike has four doors at the end. Not three. Nobody's opened the fourth.
>
> People ask what's behind it. I tell them the truth. …I don't know. I'm not curious.
>
> …That's a lie. Go.

**Derrota**

> …Hmph. Two things I don't know now.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_Intro3:
	.string "…Lucy.\p"
	.string "Where I'm from, the Pike has four doors\n"
	.string "at the end. Not three. Nobody's opened\l"
	.string "the fourth.\p"
	.string "People ask what's behind it. I tell them\n"
	.string "the truth. …I don't know. I'm not\l"
	.string "curious.\p"
	.string "…That's a lie. Go.$"

Nexus_Text_Lucy_Defeat3:
	.string "…Hmph. Two things I don't know now.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lucy é a campeã, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Zygarde

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lucy_Zygarde_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Na variação 1 a Lucy se reconhece na criatura que fica quieta porque está contando. Na 2, humor seco: uma célula verde entrou no quarto dela e as duas estão numa disputa de quem pisca primeiro (a célula pisca: ela perde); o fecho é sobre time: sozinha a célula não é nada, juntas elas ficam de pé. Na 3, a dúvida: a criatura só se junta quando algo está errado; no fragmento dela foi a quarta porta, e ela ficou ao lado das células sem ninguém pedir.

**Variação 2 — quem pisca primeiro**

**Antes da luta**

> …There's a green cell in my room. Small. It blinks.
>
> I didn't bring it in. It came in. Sat on the table. Hasn't moved in days.
>
> …It's watching me. I'm watching it. Neither of us blinks first.
>
> …Well. It does. Go.

**Derrota**

> …It blinked. Hmph.

**Depois da luta**

> …Every one of those cells watches one small piece of the world.
>
> Alone, they're nothing. Put enough together and they stand up.
>
> …At the Pike, nobody gets through alone either. Three doors. You need a team.
>
> …Go. It has a team. Millions.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_Zygarde_ChampionIntro2:
	.string "…There's a green cell in my room. Small.\n"
	.string "It blinks.\p"
	.string "I didn't bring it in. It came in. Sat on\n"
	.string "the table. Hasn't moved in days.\p"
	.string "…It's watching me. I'm watching it.\n"
	.string "Neither of us blinks first.\p"
	.string "…Well. It does. Go.$"

Nexus_Text_Lucy_Zygarde_ChampionDefeat2:
	.string "…It blinked. Hmph.$"

Nexus_Text_Lucy_Zygarde_ChampionAfter2:
	.string "{SPEAKER NAME_LUCY}…Every one of those cells watches one\n"
	.string "small piece of the world.\p"
	.string "Alone, they're nothing. Put enough\n"
	.string "together and they stand up.\p"
	.string "…At the Pike, nobody gets through alone\n"
	.string "either. Three doors. You need a team.\p"
	.string "…Go. It has a team. Millions.$"
```

</details>

**Variação 3 — algo está errado**

**Antes da luta**

> …It only gathers when something's wrong. Everyone knows that.
>
> It's gathered here. …So, something's wrong.
>
> I checked. It's not you. …Probably.
>
> Let's make sure. Go.

**Derrota**

> …Not you. Confirmed.

**Depois da luta**

> …Where I'm from, a door opened that shouldn't have.
>
> The cells came from everywhere. Leaves, rocks, water. They stood in front of it.
>
> …I stood next to them. Nobody asked me. Seemed right.
>
> …Go. If it gets in your way, it's not personal. It's order.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_Zygarde_ChampionIntro3:
	.string "…It only gathers when something's\n"
	.string "wrong. Everyone knows that.\p"
	.string "It's gathered here. …So, something's\n"
	.string "wrong.\p"
	.string "I checked. It's not you. …Probably.\p"
	.string "Let's make sure. Go.$"

Nexus_Text_Lucy_Zygarde_ChampionDefeat3:
	.string "…Not you. Confirmed.$"

Nexus_Text_Lucy_Zygarde_ChampionAfter3:
	.string "{SPEAKER NAME_LUCY}…Where I'm from, a door opened that\n"
	.string "shouldn't have.\p"
	.string "The cells came from everywhere. Leaves,\n"
	.string "rocks, water. They stood in front of it.\p"
	.string "…I stood next to them. Nobody asked me.\n"
	.string "Seemed right.\p"
	.string "…Go. If it gets in your way, it's not\n"
	.string "personal. It's order.$"
```

</details>


#### Iron Jugulis

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lucy_IronJugulis_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Na variação 1 escolher às cegas é confiança. Na 2, uma provocação ("feche os olhos" — brincadeira) e o ângulo do futuro: alguém construiu aquilo a partir da ideia de um dragão; o Deino morde tudo o que não vê, e este não morde: aprendeu alguma coisa. Na 3, a lembrança do dia em que ela abriu a quarta porta: céu sem chão, três luzes, e a do meio chegando perto como quem escuta o coração; ela nunca contou a ninguém.

**Variação 2 — feche os olhos**

**Antes da luta**

> …Close your eyes.
>
> …Kidding. But that thing out there flies with its eyes shut. Always.
>
> It doesn't need to see where it's going. It listens to the other two.
>
> …You need your eyes. I'll allow it. Go.

**Derrota**

> …You kept your eyes open. Smart.

**Depois da luta**

> …It's from later. A day nobody's lived yet.
>
> Somebody built it from the idea of a dragon. Three heads. One brain. No eyes in the middle.
>
> …The one it copies bites everything it can't see. This one doesn't. It learned something.
>
> …Go. Somebody from later is waiting to meet you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_IronJugulis_ChampionIntro2:
	.string "…Close your eyes.\p"
	.string "…Kidding. But that thing out there flies\n"
	.string "with its eyes shut. Always.\p"
	.string "It doesn't need to see where it's\n"
	.string "going. It listens to the other two.\p"
	.string "…You need your eyes. I'll allow it. Go.$"

Nexus_Text_Lucy_IronJugulis_ChampionDefeat2:
	.string "…You kept your eyes open. Smart.$"

Nexus_Text_Lucy_IronJugulis_ChampionAfter2:
	.string "{SPEAKER NAME_LUCY}…It's from later. A day nobody's lived\n"
	.string "yet.\p"
	.string "Somebody built it from the idea of a\n"
	.string "dragon. Three heads. One brain. No eyes\l"
	.string "in the middle.\p"
	.string "…The one it copies bites everything it\n"
	.string "can't see. This one doesn't. It learned\l"
	.string "something.\p"
	.string "…Go. Somebody from later is waiting to\n"
	.string "meet you.$"
```

</details>

**Variação 3 — o dia da quarta porta**

**Antes da luta**

> …I opened a door once without looking. You know that.
>
> …Behind it was sky. No floor. Three lights, coming.
>
> I didn't step back. …Don't know why. Pike Queen thing.
>
> …Your turn not to step back. Go.

**Derrota**

> …Didn't step back. Good.

**Depois da luta**

> …It stopped a meter from my face. Just hung there. Three lights.
>
> The middle one leaned in. Close. Like it was listening for my heartbeat.
>
> …Then it left. I shut the door. Never told anyone. …Until now.
>
> …Go. It'll listen for yours too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lucy_IronJugulis_ChampionIntro3:
	.string "…I opened a door once without looking.\n"
	.string "You know that.\p"
	.string "…Behind it was sky. No floor. Three\n"
	.string "lights, coming.\p"
	.string "I didn't step back. …Don't know why.\n"
	.string "Pike Queen thing.\p"
	.string "…Your turn not to step back. Go.$"

Nexus_Text_Lucy_IronJugulis_ChampionDefeat3:
	.string "…Didn't step back. Good.$"

Nexus_Text_Lucy_IronJugulis_ChampionAfter3:
	.string "{SPEAKER NAME_LUCY}…It stopped a meter from my face. Just\n"
	.string "hung there. Three lights.\p"
	.string "The middle one leaned in. Close. Like it\n"
	.string "was listening for my heartbeat.\p"
	.string "…Then it left. I shut the door. Never\n"
	.string "told anyone. …Until now.\p"
	.string "…Go. It'll listen for yours too.$"
```

</details>


Falante novo: `SP_NAME_LUCY` (não existe em `include/constants/speaker_names.h`).
