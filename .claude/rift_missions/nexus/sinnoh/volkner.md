# Volkner

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Volkner — Elétrico** (Sinnoh · Líderes de Ginásio) — talentoso Líder de Sunyshore que busca um desafio verdadeiro.

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
| `OBJ_EVENT_GFX_VOLKNER` | `graphics/object_events/pics/people/special/volkner.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_VOLKNER` | `graphics/trainers/front_pics/volkner.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_VOLKNER` = **978** (flag de batalha `0x8D2`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Volkner_Fight` (genérica) e `Nexus_EventScript_Volkner_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Volkner.

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

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Volkner_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Xurkitree** (UB-03 Lighting). Volkner é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

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

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Volkner_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Volkner cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Cada variação pega um ângulo diferente do personagem.

**Variação 2 — o amigo que tem razão.** O Flint (sem nome), o melhor amigo, que diz que o Volkner acharia um jeito de se entediar dentro de um vulcão. Ele nunca admite que o amigo tem razão.

**Antes da luta**

> You know what my friend says? That I'd find a way to be bored inside a volcano.
>
> He's probably right. He usually is. I never tell him.
>
> Go on. Prove him wrong, for once.

**Derrota**

> Heh. Okay. That was worth staying awake for.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Volkner_Intro2:
	.string "You know what my friend says? That I'd\n"
	.string "find a way to be bored inside a volcano.\p"
	.string "He's probably right. He usually is. I\n"
	.string "never tell him.\p"
	.string "Go on. Prove him wrong, for once.$"

Nexus_Text_Volkner_Defeat2:
	.string "Heh. Okay. That was worth staying awake\n"
	.string "for.$"
```

</details>

**Variação 3 — consertando coisas.** Mania de mexer em fiação quando nada acontece (foi assim que ele apagou Sunyshore em Platinum). Humor seco: agora ele quer ver se o jogador ainda funciona.

**Antes da luta**

> Sorry. One second. I'm rewiring something.
>
> Old habit. When nothing's happening, I take things apart to see if they still work.
>
> …Right. Done. Let's see if you still work.

**Derrota**

> Everything works. Great. Now I've got nothing to fix.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Volkner_Intro3:
	.string "Sorry. One second. I'm rewiring\n"
	.string "something.\p"
	.string "Old habit. When nothing's happening, I\n"
	.string "take things apart to see if they still\l"
	.string "work.\p"
	.string "…Right. Done. Let's see if you still\n"
	.string "work.$"

Nexus_Text_Volkner_Defeat3:
	.string "Everything works. Great. Now I've got\n"
	.string "nothing to fix.$"
```

</details>



### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Volkner_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Volkner é o **campeão**, a luta logo antes da Xurkitree. A fala é sobre a criatura, sem dizer o nome dela.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1: sobre a criatura, pelo olhar dele, sem dizer o nome da espécie. Labels no padrão `Nexus_Text_Volkner_Champion*` + sufixo.

**Variação 2 — medo da melhor luta.** Ele conta as ruas que ainda têm luz. A dúvida: por que não luta com ela? Medo de que seja a melhor luta da vida dele, e depois nada. O conselho é técnico e autoirônico: ela acha você pela corrente.

**Antes da luta**

> The lights go out one street at a time. I've been counting. Forty-two left.
>
> Someone asked why I don't just fight it. Fair question. I'm a Gym Leader. That's the whole job.
>
> I think I'm scared it'd be the best battle of my life. And then what?
>
> …Forget it. You first.

**Derrota**

> Ha. Okay. That one I'll remember in the dark.

**Depois da luta**

> It has no eyes. It finds you by current. Anything carrying a charge, it leans toward.
>
> So maybe don't lead with an Electric type. Take it from a guy who only brings Electric types.
>
> Forty-one streets now. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Volkner_ChampionIntro2:
	.string "The lights go out one street at a time.\n"
	.string "I've been counting. Forty-two left.\p"
	.string "Someone asked why I don't just fight\n"
	.string "it. Fair question. I'm a Gym Leader.\l"
	.string "That's the whole job.\p"
	.string "I think I'm scared it'd be the best\n"
	.string "battle of my life. And then what?\p"
	.string "…Forget it. You first.$"

Nexus_Text_Volkner_ChampionDefeat2:
	.string "Ha. Okay. That one I'll remember in the\n"
	.string "dark.$"

Nexus_Text_Volkner_ChampionAfter2:
	.string "{SPEAKER NAME_VOLKNER}It has no eyes. It finds you by current.\n"
	.string "Anything carrying a charge, it leans\l"
	.string "toward.\p"
	.string "So maybe don't lead with an Electric\n"
	.string "type. Take it from a guy who only brings\l"
	.string "Electric types.\p"
	.string "Forty-one streets now. Go.$"
```

</details>

**Variação 3 — o farol.** O farol de Sunyshore (Vista Lighthouse, sem nome), onde ele se sentava quando ninguém o desafiava. A criatura subiu na torre mais alta na primeira noite: os dois gostam da mesma vista. Ele fica mantendo uma luz acesa para alguém achar o caminho de volta.

**Antes da luta**

> There's a lighthouse back home. Best view in the region. I'd sit up there when nobody came to challenge me.
>
> That thing climbed the tallest tower in town the first night. Guess it likes the view too.
>
> We'd probably get along. That's the problem.
>
> Come on. Remind me which side I'm on.

**Derrota**

> Right. Your side. Got it.

**Depois da luta**

> When it plugs into something, it stops moving. It won't let go of a good source.
>
> Cut the line, and it has to come looking for you. That's when it's slow.
>
> Me? I'm keeping one light on. Someone has to find their way back.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Volkner_ChampionIntro3:
	.string "There's a lighthouse back home. Best\n"
	.string "view in the region. I'd sit up there\l"
	.string "when nobody came to challenge me.\p"
	.string "That thing climbed the tallest tower in\n"
	.string "town the first night. Guess it likes the\l"
	.string "view too.\p"
	.string "We'd probably get along. That's the\n"
	.string "problem.\p"
	.string "Come on. Remind me which side I'm on.$"

Nexus_Text_Volkner_ChampionDefeat3:
	.string "Right. Your side. Got it.$"

Nexus_Text_Volkner_ChampionAfter3:
	.string "{SPEAKER NAME_VOLKNER}When it plugs into something, it stops\n"
	.string "moving. It won't let go of a good\l"
	.string "source.\p"
	.string "Cut the line, and it has to come looking\n"
	.string "for you. That's when it's slow.\p"
	.string "Me? I'm keeping one light on. Someone\n"
	.string "has to find their way back.$"
```

</details>

