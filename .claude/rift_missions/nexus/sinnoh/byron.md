# Byron

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Byron — Aço** (Sinnoh · Líderes de Ginásio) — Líder de Canalave e pai de Roark.

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
| `OBJ_EVENT_GFX_BYRON` | `graphics/object_events/pics/people/special/byron.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_BYRON` | `graphics/trainers/front_pics/byron.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BYRON` = **983** (flag de batalha `0x8D7`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Byron_Fight` (genérica) e `Nexus_EventScript_Byron_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Byron.

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_BYRON`, campeão da Stakataka. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zamazenta** (com o Rusted Shield, a forma Crowned: o escudo), semi-lendário **Registeel**, Mega **Steelix** (Steeltite: Aço/Terra, Sand Force), mais Bastiodon, Bronzong e Tyranitar. O muro, peça por peça. *Plano:* areia e Trick Room. O Tyranitar chama a tempestade de areia, o Bronzong inverte a ordem dos turnos, e os lentos batem primeiro: a Mega Steelix na areia, Bastiodon e Zamazenta com Iron Defense e Body Press, o Registeel com Stealth Rock e o Bastiodon com Wide Guard em Doubles. Em Singles, o mesmo time joga como parede.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zamazenta | Rusted Shield | Dauntless Shield | Impish | Body Press, Iron Defense, Iron Head, Crunch |
| Registeel | Leftovers | Clear Body | Careful | Iron Head, Body Press, Stealth Rock, Thunder Wave |
| Steelix | Steeltite | Sturdy | Brave | Earthquake, Heavy Slam, Rock Slide, Curse |
| Bastiodon | Custap Berry | Sturdy | Relaxed | Body Press, Iron Defense, Metal Burst, Wide Guard |
| Bronzong | Mental Herb | Levitate | Sassy | Trick Room, Gyro Ball, Hypnosis, Reflect |
| Tyranitar | Smooth Rock | Sand Stream | Brave | Rock Slide, Crunch, Earthquake, Low Kick |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BYRON ===
Name: Byron
Class: Leader
Pic: Byron
Gender: Male
Music: Hiker
Double Battle: Yes
AI: Smart Trainer

Zamazenta @ Rusted Shield
Impish Nature
Level: 100
Ability: Dauntless Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Press
- Iron Defense
- Iron Head
- Crunch

Registeel @ Leftovers
Careful Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Body Press
- Stealth Rock
- Thunder Wave

Steelix @ Steeltite
Brave Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earthquake
- Heavy Slam
- Rock Slide
- Curse

Bastiodon @ Custap Berry
Relaxed Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Press
- Iron Defense
- Metal Burst
- Wide Guard

Bronzong @ Mental Herb
Sassy Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Gyro Ball
- Hypnosis
- Reflect

Tyranitar @ Smooth Rock
Brave Nature
Level: 100
Ability: Sand Stream
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Crunch
- Earthquake
- Low Kick
```

</details>


### Lendário associado

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Byron_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Stakataka** (UB Assembly). Byron é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Byron, líder de Canalave, minerador, "o homem de corpo de aço", pai do Roark, e dono de um Bastiodon, ele mesmo um muro vivo.

**A criatura.** Parece feita de pedras empilhadas, mas cada "pedra" é uma forma de vida separada. Muros que começaram a andar e atacar. Segundo o Phyco, uma Stakataka reúne quase 150 dessas criaturas.

**O fragmento.** Uma pedreira de pedra cinza, com muros em todas as direções. O jogador tinha certeza de que o caminho atrás dele estava aberto um instante antes.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A quarry of grey stone, with walls in every direction.
>
> You were sure the way behind you had been open a moment ago.

**Boss**

> The wall ahead shifted, brick by brick, and stood up on four thin legs.
>
> Every stone in it turned to look at you.

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

> File UB Assembly.
>
> One creature that is really a hundred and fifty, all holding each other up.
>
> I have been told it is a threat. I have filed it under threats. I keep wanting to move it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Assembly_Arrival:
	.string "A quarry of grey stone, with walls in\n"
	.string "every direction.\p"
	.string "You were sure the way behind you had\n"
	.string "been open a moment ago.$"

Nexus_Text_Assembly_Boss:
	.string "The wall ahead shifted, brick by brick,\n"
	.string "and stood up on four thin legs.\p"
	.string "Every stone in it turned to look at you.$"

Nexus_Text_Assembly_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Assembly.\p"
	.string "One creature that is really a hundred\n"
	.string "and fifty, all holding each other up.\p"
	.string "I have been told it is a threat. I have\n"
	.string "filed it under threats. I keep wanting\l"
	.string "to move it.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Byron_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Byron cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hah! No idea how I ended up here, but there's stone under my boots, so I'm not complaining!
>
> I'm a miner, youngster. Hard rock, hard steel, hard battles.
>
> Let's see what you're made of!

**Derrota**

> Hah! Solid! You'd make a fine miner.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Byron_Intro:
	.string "Hah! No idea how I ended up here, but\n"
	.string "there's stone under my boots, so I'm\l"
	.string "not complaining!\p"
	.string "I'm a miner, youngster. Hard rock, hard\n"
	.string "steel, hard battles.\p"
	.string "Let's see what you're made of!$"

Nexus_Text_Byron_Defeat:
	.string "Hah! Solid! You'd make a fine miner.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Cada variação pega um ângulo diferente do personagem.

**Variação 2 — a picareta perdida.** O Byron perdeu a picareta em algum fragmento e nem liga: a ferramenta de verdade do minerador é o time. Humor e tranquilidade de quem confia em pedra.

**Antes da luta**

> Hah! You've got the look of someone who's been walking a long while. So have I.
>
> I keep reaching for my pickaxe. Left it somewhere. Some harbor, some year.
>
> Doesn't matter! A miner's real tool is his team. Show me yours!

**Derrota**

> Hah! Struck a vein of pure steel there!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Byron_Intro2:
	.string "Hah! You've got the look of someone\n"
	.string "who's been walking a long while. So have\l"
	.string "I.\p"
	.string "I keep reaching for my pickaxe. Left it\n"
	.string "somewhere. Some harbor, some year.\p"
	.string "Doesn't matter! A miner's real tool is\n"
	.string "his team. Show me yours!$"

Nexus_Text_Byron_Defeat2:
	.string "Hah! Struck a vein of pure steel there!$"
```

</details>

**Variação 3 — o fóssil do filho.** Lembrança do Roark (sem nome): o fóssil que o Byron deu de aniversário, e o filho tentando vencer o pai com pedras desde então. A derrota é o pai pedindo segredo.

**Antes da luta**

> When my boy was small, I gave him a fossil for his birthday. Best rock he ever got, he said.
>
> He's been trying to beat his old man with rocks ever since. You've got the same look in your eye.
>
> Hah! Come on, then! Dig in!

**Derrota**

> Hah! Well, don't tell him about this. I'd never hear the end of it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Byron_Intro3:
	.string "When my boy was small, I gave him a\n"
	.string "fossil for his birthday. Best rock he\l"
	.string "ever got, he said.\p"
	.string "He's been trying to beat his old man\n"
	.string "with rocks ever since. You've got the\l"
	.string "same look in your eye.\p"
	.string "Hah! Come on, then! Dig in!$"

Nexus_Text_Byron_Defeat3:
	.string "Hah! Well, don't tell him about this. I'd\n"
	.string "never hear the end of it.$"
```

</details>



### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Byron_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Byron é o **campeão**, a luta logo antes da Stakataka. A fala é sobre a criatura, sem dizer o nome dela.

O Byron corta pedra de montanha a vida inteira e sabe que aquele muro não é pedra: cada tijolo está vivo, uns cento e cinquenta, cada um segurando o próximo. Ele e o filho não concordam nem em como empilhar uma prateleira, e aquelas criaturas levantaram uma fortaleza juntas. A vitória: um time que segura, sem rachadura. O que fica: não procure o tijolo fraco, não existe; bata no muro inteiro, com tudo, de uma vez. E depois vá ligar para a família. Ele vai ligar para a dele.

**Antes da luta**

> Youngster, I've spent my whole life cutting stone out of mountains. I know rock.
>
> That wall over there isn't rock. Every brick of it is alive. A hundred and fifty, near as I can count, each one holding up the next.
>
> My son and I can't agree on how to stack a shelf. These things built a fortress together.
>
> Hah! Let's see if you and your team hold together half as well!

**Derrota**

> Hah! Now THAT'S a team that holds! Not a crack in it!

**Depois da luta**

> When it comes, don't hunt for the weak brick. There isn't one. They share the load.
>
> Hit the whole wall. Hit it with everything you've got, all at once.
>
> …Then maybe go home and call your family. I'm going to call mine.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Byron_ChampionIntro:
	.string "Youngster, I've spent my whole life\n"
	.string "cutting stone out of mountains. I know\l"
	.string "rock.\p"
	.string "That wall over there isn't rock. Every\n"
	.string "brick of it is alive. A hundred and fifty,\l"
	.string "near as I can count, each one holding up\l"
	.string "the next.\p"
	.string "My son and I can't agree on how to\n"
	.string "stack a shelf. These things built a\l"
	.string "fortress together.\p"
	.string "Hah! Let's see if you and your team\n"
	.string "hold together half as well!$"

Nexus_Text_Byron_ChampionDefeat:
	.string "Hah! Now THAT'S a team that holds! Not\n"
	.string "a crack in it!$"

Nexus_Text_Byron_ChampionAfter:
	.string "{SPEAKER NAME_BYRON}When it comes, don't hunt for the weak\n"
	.string "brick. There isn't one. They share the\l"
	.string "load.\p"
	.string "Hit the whole wall. Hit it with\n"
	.string "everything you've got, all at once.\p"
	.string "…Then maybe go home and call your\n"
	.string "family. I'm going to call mine.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1: sobre a criatura, pelo olhar dele, sem dizer o nome da espécie. Labels no padrão `Nexus_Text_Byron_Champion*` + sufixo.

**Variação 2 — o muro que prende a respiração.** O Byron escuta a pedra e percebe que o muro respira. Nunca bateu em nada que estivesse prendendo o fôlego. O conselho vira pergunta: ninguém ergue um muro à toa, o que ele estava segurando lá fora?

**Antes da luta**

> I've been listening to that wall, youngster. Put your ear on stone long enough and it talks.
>
> This one isn't talking. It's breathing. A hundred and fifty little breaths, all in time.
>
> Could've brought it down the first day. Didn't. Never swung at a thing that was holding its breath.
>
> Hah! I'll swing at you, though! Come on!

**Derrota**

> Hah! Didn't give an inch! Just like a good wall should!

**Depois da luta**

> Here's the thing about walls. Nobody builds one for no reason.
>
> Something scared those little stones into holding each other that tight.
>
> Knock it down if you have to. Just ask yourself what it was keeping out.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Byron_ChampionIntro2:
	.string "I've been listening to that wall,\n"
	.string "youngster. Put your ear on stone long\l"
	.string "enough and it talks.\p"
	.string "This one isn't talking. It's breathing.\n"
	.string "A hundred and fifty little breaths, all\l"
	.string "in time.\p"
	.string "Could've brought it down the first day.\n"
	.string "Didn't. Never swung at a thing that was\l"
	.string "holding its breath.\p"
	.string "Hah! I'll swing at you, though! Come on!$"

Nexus_Text_Byron_ChampionDefeat2:
	.string "Hah! Didn't give an inch! Just like a\n"
	.string "good wall should!$"

Nexus_Text_Byron_ChampionAfter2:
	.string "{SPEAKER NAME_BYRON}Here's the thing about walls. Nobody\n"
	.string "builds one for no reason.\p"
	.string "Something scared those little stones\n"
	.string "into holding each other that tight.\p"
	.string "Knock it down if you have to. Just ask\n"
	.string "yourself what it was keeping out.$"
```

</details>

**Variação 3 — o capacete na terceira fileira.** Humor e perda: tudo que alguém larga no fragmento vira parte do muro, inclusive o capacete do Byron. O aviso é não largar nada lá dentro, nem a guarda.

**Antes da luta**

> Lost my hard hat in this quarry. Went back for it, and the wall had moved. Twice.
>
> It isn't chasing me. It's tidying. Anything you set down, it builds right in.
>
> My hat's in there now. Third row, left side. Hah! It wears it better than I did.
>
> Right! Before I lose anything else, let's battle!

**Derrota**

> Hah! There goes my pride. That'll end up in the wall too.

**Depois da luta**

> Don't set anything down in there, youngster. Not your bag, not your Poké Balls, not your guard.
>
> Whatever it keeps, it keeps for good. Every stone in it was somebody's once.
>
> …Bring me back my hat if you see it. Third row. Left side.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Byron_ChampionIntro3:
	.string "Lost my hard hat in this quarry. Went\n"
	.string "back for it, and the wall had moved.\l"
	.string "Twice.\p"
	.string "It isn't chasing me. It's tidying.\n"
	.string "Anything you set down, it builds right\l"
	.string "in.\p"
	.string "My hat's in there now. Third row, left\n"
	.string "side. Hah! It wears it better than I did.\p"
	.string "Right! Before I lose anything else,\n"
	.string "let's battle!$"

Nexus_Text_Byron_ChampionDefeat3:
	.string "Hah! There goes my pride. That'll end up\n"
	.string "in the wall too.$"

Nexus_Text_Byron_ChampionAfter3:
	.string "{SPEAKER NAME_BYRON}Don't set anything down in there,\n"
	.string "youngster. Not your bag, not your Poké\l"
	.string "Balls, not your guard.\p"
	.string "Whatever it keeps, it keeps for good.\n"
	.string "Every stone in it was somebody's once.\p"
	.string "…Bring me back my hat if you see it.\n"
	.string "Third row. Left side.$"
```

</details>

