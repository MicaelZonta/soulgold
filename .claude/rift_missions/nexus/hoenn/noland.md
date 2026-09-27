# Noland

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Noland — Battle Factory** (Hoenn · Battle Frontier — Frontier Brains) — testa a capacidade de batalhar com Pokémon alugados.

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
| `OBJ_EVENT_GFX_NOLAND` | `graphics/object_events/pics/people/frontier_brains/noland.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_FACTORY_HEAD_NOLAND` | `graphics/trainers/front_pics/factory_head_noland.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

Homônimos genéricos, **não** são este personagem: `TRAINER_NOLAND` ("Noland", pic Hiker).

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_NOLAND`, campeão de Miraidon e Iron Treads. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Miraidon**, semi-lendário **Iron Treads** (os dois vindos do futuro), Mega **Manectric** (Electrite). O Noland é o cérebro da Battle Factory: vive de conhecer Pokémon que não criou, e aqui o time inteiro é **coisa fabricada ou máquina**: o Porygon2 foi programado, o Rotom-Wash mora dentro de uma máquina de lavar, a Tinkaton forja o próprio martelo, e o Miraidon e o Iron Treads parecem saídos de uma linha de montagem que ainda não existe. *Plano:* **uma fábrica movida a Electric Terrain.** O Hadron Engine do Miraidon liga o terreno ao entrar, o terreno acende o Quark Drive do Iron Treads, e o time todo bate com Electric reforçado. O Iron Treads (Ground) absorve Electric de graça, e o Rotom-Wash (Levitate, Water) cobre a fraqueza a Ground dos elétricos.

*Plano (Singles):* Tinkaton arma Stealth Rock, Iron Treads limpa hazards com Rapid Spin, Manectric e Rotom-Wash fazem pivô de Volt Switch (o Rotom queima físicos com Will-O-Wisp) para trazer o Miraidon de Choice Specs com o terreno no lugar; Porygon2 segura com Recover e Thunder Wave. *Plano (Doubles):* o Miraidon entra com o terreno e Dazzling Gleam acerta os dois; a Mega Manectric abre com Snarl nos dois alvos; o Rotom-Wash usa Protect e Will-O-Wisp para cobrir o parceiro e recebe Ground no lugar dele; o Iron Treads não sofre nada dos golpes elétricos do parceiro. Nada no time tem Earthquake ou golpe que acerte o aliado.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Miraidon | Choice Specs | Hadron Engine | Timid | Electro Drift, Draco Meteor, Dazzling Gleam, Volt Switch |
| Iron Treads | Assault Vest | Quark Drive | Jolly | High Horsepower, Iron Head, Knock Off, Rapid Spin |
| Manectric | Electrite | Static | Timid | Thunderbolt, Overheat, Snarl, Volt Switch |
| Rotom-Wash | Sitrus Berry | Levitate | Bold | Hydro Pump, Volt Switch, Will-O-Wisp, Protect |
| Porygon2 | Eviolite | Download | Calm | Tri Attack, Ice Beam, Recover, Thunder Wave |
| Tinkaton | Leftovers | Mold Breaker | Jolly | Gigaton Hammer, Play Rough, Knock Off, Stealth Rock |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_NOLAND ===
Name: Noland
Class: Factory Head
Pic: Factory Head Noland
Gender: Male
Music: Male
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
- Dazzling Gleam
- Volt Switch

Iron Treads @ Assault Vest
Jolly Nature
Level: 100
Ability: Quark Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Iron Head
- Knock Off
- Rapid Spin

Manectric @ Electrite
Timid Nature
Level: 100
Ability: Static
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Overheat
- Snarl
- Volt Switch

Rotom-Wash @ Sitrus Berry
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Volt Switch
- Will-O-Wisp
- Protect

Porygon2 @ Eviolite
Calm Nature
Level: 100
Ability: Download
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tri Attack
- Ice Beam
- Recover
- Thunder Wave

Tinkaton @ Leftovers
Jolly Nature
Level: 100
Ability: Mold Breaker
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Gigaton Hammer
- Play Rough
- Knock Off
- Stealth Rock
```

</details>


### Lendário associado

#### Miraidon

📝 **Proposta de 27/09/2026, aguardando o autor.** **Miraidon**. Noland é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Noland, Factory Head da Battle Frontier de Hoenn. Na Battle Factory o desafiante luta com Pokémon alugados: o que vale é conhecimento, não laço.

**A criatura.** Paradoxo do futuro (Violet), trazido pela máquina do tempo do laboratório de Area Zero. Parece uma máquina e é Pokémon; o Hadron Engine cria Electric Terrain ao entrar, e ele se dobra em forma de moto para levar alguém.

**O fragmento.** Uma rodovia de luz violeta sobre uma cidade que ninguém construiu ainda. Os postes zumbem, e o asfalto acende um passo à frente de quem anda, como se já soubesse o caminho. Não há ninguém dirigindo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A highway of violet light, running over a city no one has built yet.
>
> The lamps hummed. The road lit up one step ahead of your feet, as if it already knew where you were going.
>
> Nobody was driving.

**Boss**

> Two lights came on at the end of the road.
>
> They were not headlights. They blinked, and the whole street hummed louder, the way a machine does when it wakes up.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1008. The Road Ahead.
>
> A highway to a city not built yet, and a man who swears a manual beats a friendship.
>
> What came back with you is small, and warm like an engine left running. There is no manual for it. I checked.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Miraidon_Arrival:
	.string "A highway of violet light, running over\n"
	.string "a city no one has built yet.\p"
	.string "The lamps hummed. The road lit up one\n"
	.string "step ahead of your feet, as if it\l"
	.string "already knew where you were going.\p"
	.string "Nobody was driving.$"

Nexus_Text_Miraidon_Boss:
	.string "Two lights came on at the end of the\n"
	.string "road.\p"
	.string "They were not headlights. They blinked,\n"
	.string "and the whole street hummed louder,\l"
	.string "the way a machine does when it wakes\l"
	.string "up.$"

Nexus_Text_Miraidon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1008. The Road Ahead.\p"
	.string "A highway to a city not built yet, and a\n"
	.string "man who swears a manual beats a\l"
	.string "friendship.\p"
	.string "What came back with you is small, and\n"
	.string "warm like an engine left running. There\l"
	.string "is no manual for it. I checked.$"
```

</details>


#### Iron Treads

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Treads**. Noland é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Noland, o homem que conhece todo Pokémon de aluguel da Factory, Donphan inclusive.

**A criatura.** Paradoxo do futuro, descrito no Violet Book como um Donphan de metal. Dizem que rola em alta velocidade e que as presas conduzem eletricidade; o Quark Drive dele acorda com Electric Terrain.

**O fragmento.** Uma planície de poeira riscada por trilhas retas demais para qualquer animal, todas paralelas, todas sumindo no horizonte. Na beira de cada trilha, uma presa de aço partida.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A dusty plain, crossed by tracks.
>
> They were too straight for any animal, all of them parallel, all of them vanishing at the horizon.
>
> Beside each one lay a broken steel tusk.

**Boss**

> A wheel of steel came rolling out of the dust.
>
> It stopped, unrolled, and raised two tusks that crackled at the tips.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-990. Future Tusk.
>
> A plain of perfect tracks, and a man who knows every Donphan ever rented.
>
> What came back with you is new, and it rolls in circles on my floor. It has not yet learned to go straight. I find that reassuring.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronTreads_Arrival:
	.string "A dusty plain, crossed by tracks.\p"
	.string "They were too straight for any animal,\n"
	.string "all of them parallel, all of them\l"
	.string "vanishing at the horizon.\p"
	.string "Beside each one lay a broken steel\n"
	.string "tusk.$"

Nexus_Text_IronTreads_Boss:
	.string "A wheel of steel came rolling out of\n"
	.string "the dust.\p"
	.string "It stopped, unrolled, and raised two\n"
	.string "tusks that crackled at the tips.$"

Nexus_Text_IronTreads_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-990. Future Tusk.\p"
	.string "A plain of perfect tracks, and a man\n"
	.string "who knows every Donphan ever rented.\p"
	.string "What came back with you is new, and it\n"
	.string "rolls in circles on my floor. It has not\l"
	.string "yet learned to go straight. I find that\l"
	.string "reassuring.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Noland cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey, hey! Noland, Factory Head. You know the drill at my place: you get a team you didn't raise, and you figure it out fast.
>
> Funny thing. I woke up in here with these six, and nobody handed me a receipt.
>
> I read their moves once. That's all I need. Knowledge beats a long friendship any day. Let's test that!

**Derrota**

> Ha! You read them faster than I did. That's the whole job, you know.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Noland_Intro:
	.string "Hey, hey! Noland, Factory Head. You\n"
	.string "know the drill at my place: you get a\l"
	.string "team you didn't raise, and you figure\l"
	.string "it out fast.\p"
	.string "Funny thing. I woke up in here with\n"
	.string "these six, and nobody handed me a\l"
	.string "receipt.\p"
	.string "I read their moves once. That's all I\n"
	.string "need. Knowledge beats a long\l"
	.string "friendship any day. Let's test that!$"

Nexus_Text_Noland_Defeat:
	.string "Ha! You read them faster than I did.\n"
	.string "That's the whole job, you know.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Noland é o campeão, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Miraidon

O Noland se orgulha de ler um Pokémon em segundos: ficha, golpes, pronto. Ele tenta ler a criatura da estrada e não acha ficha nenhuma: nenhum livro fala de um bicho de um futuro que ainda não aconteceu. A virada é que ele gostou. Quem vive de saber tudo descobre que a melhor parte da Factory sempre foi o primeiro minuto, quando ainda não sabia. E ele nota o detalhe que o incomoda: a máquina que trouxe aquilo foi feita por alguém, e esse alguém não voltou para buscar.

**Antes da luta**

> Hey, hey. You saw the road, right? Lights on, nobody driving. I tried to read that thing like a rental.
>
> Type, moves, weak spots. Two seconds, tops. That's my trick.
>
> Couldn't do it. There's no page on it anywhere. It's from a day that hasn't happened yet.
>
> And, honestly? Best feeling I've had in years. Let's go!

**Derrota**

> Whoa. You read me better than I read it.

**Depois da luta**

> Here's the part that bugs me. It didn't walk here. Something carried it back. A machine.
>
> And somebody built that machine, flipped the switch, and never came to pick it up.
>
> I rent Pokémon out every day. I always get them back.
>
> Go on. Somebody ought to meet it at the end of that road.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Noland_Miraidon_ChampionIntro:
	.string "Hey, hey. You saw the road, right?\n"
	.string "Lights on, nobody driving. I tried to\l"
	.string "read that thing like a rental.\p"
	.string "Type, moves, weak spots. Two seconds,\n"
	.string "tops. That's my trick.\p"
	.string "Couldn't do it. There's no page on it\n"
	.string "anywhere. It's from a day that hasn't\l"
	.string "happened yet.\p"
	.string "And, honestly? Best feeling I've had\n"
	.string "in years. Let's go!$"

Nexus_Text_Noland_Miraidon_ChampionDefeat:
	.string "Whoa. You read me better than I read\n"
	.string "it.$"

Nexus_Text_Noland_Miraidon_ChampionAfter:
	.string "{SPEAKER NAME_NOLAND}Here's the part that bugs me. It\n"
	.string "didn't walk here. Something carried it\l"
	.string "back. A machine.\p"
	.string "And somebody built that machine,\n"
	.string "flipped the switch, and never came to\l"
	.string "pick it up.\p"
	.string "I rent Pokémon out every day. I always\n"
	.string "get them back.\p"
	.string "Go on. Somebody ought to meet it at\n"
	.string "the end of that road.$"
```

</details>


#### Iron Treads

Na Factory o Noland já emprestou mais Donphan do que consegue contar; é o Pokémon que ele conhece de olhos fechados. A criatura da planície tem a forma de um Donphan e nada mais dele: é aço, trilha reta, função. A virada: o Noland percebe que é isso que acontece quando alguém só conhece a ficha de um Pokémon. Com tempo suficiente, sobra a ficha e some o bicho. E ele, que sempre disse que conhecimento vence laço, fica em dúvida pela primeira vez.

**Antes da luta**

> Donphan. I know Donphan. I've rented out more Donphan than I can count.
>
> That thing out there has the shape. Tusks, the roll, the whole spec sheet.
>
> But there's nothing else in it. No Donphan in there. Just the sheet, in steel.
>
> Kinda makes me wonder what I look like from the outside. Let's find out!

**Derrota**

> Yeah. Knowing the sheet wasn't enough, huh.

**Depois da luta**

> I always said knowledge beats friendship. Read the Pokémon, win the battle.
>
> Then I saw what's left of a Donphan when all you keep is the knowledge. Straight lines. Nobody home.
>
> Maybe I'll let the next challenger keep their rental a little longer.
>
> Go on. Roll that thing over for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Noland_IronTreads_ChampionIntro:
	.string "Donphan. I know Donphan. I've rented\n"
	.string "out more Donphan than I can count.\p"
	.string "That thing out there has the shape.\n"
	.string "Tusks, the roll, the whole spec sheet.\p"
	.string "But there's nothing else in it. No\n"
	.string "Donphan in there. Just the sheet, in\l"
	.string "steel.\p"
	.string "Kinda makes me wonder what I look like\n"
	.string "from the outside. Let's find out!$"

Nexus_Text_Noland_IronTreads_ChampionDefeat:
	.string "Yeah. Knowing the sheet wasn't\n"
	.string "enough, huh.$"

Nexus_Text_Noland_IronTreads_ChampionAfter:
	.string "{SPEAKER NAME_NOLAND}I always said knowledge beats\n"
	.string "friendship. Read the Pokémon, win the\l"
	.string "battle.\p"
	.string "Then I saw what's left of a Donphan\n"
	.string "when all you keep is the knowledge.\l"
	.string "Straight lines. Nobody home.\p"
	.string "Maybe I'll let the next challenger\n"
	.string "keep their rental a little longer.\p"
	.string "Go on. Roll that thing over for me.$"
```

</details>


Falante novo: `SP_NAME_NOLAND` (não existe em `include/constants/speaker_names.h`).
