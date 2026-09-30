# Colress

**Região da ficha:** Unova

Aparece no checklist como:

- **Colress** (Unova · Team Plasma) — cientista interessado em descobrir como liberar o potencial máximo dos Pokémon.

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
| `OBJ_EVENT_GFX_COLRESS` | `graphics/object_events/pics/people/special/colress.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_COLRESS` | `graphics/trainers/front_pics/colress.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_COLRESS` = **975** (flag de batalha `0x8CF`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Colress_Fight` (genérica) e `Nexus_EventScript_Colress_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Colress.

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_COLRESS`, campeão da Nihilego. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Genesect**, semi-lendário **Iron Hands**, Mega **Golurk** (Groundite: Terra/Fantasma, Unseen Fist), mais Klinklang, Magnezone e Porygon-Z. **Todos são Pokémon artificiais**: o Genesect que a Team Plasma reconstruiu, o robô vindo do futuro, o autômato antigo de Unova, as engrenagens, o ímã e o programa. É o time de quem quer ver até onde vai uma máquina. *Plano:* Genesect de Scarf e Magnezone de Specs giram com U-turn e Volt Switch até o Klinklang ter um turno para o Shift Gear. Em Doubles, o Iron Hands abre com Fake Out e a Mega Golurk bate através de Protect.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Genesect | Choice Scarf | Download | Naive | U-turn, Iron Head, Thunderbolt, Flamethrower |
| Iron Hands | Assault Vest | Quark Drive | Adamant | Fake Out, Drain Punch, Wild Charge, Ice Punch |
| Golurk | Groundite | No Guard | Adamant | Earthquake, Shadow Punch, Ice Punch, Drain Punch |
| Klinklang | Sitrus Berry | Clear Body | Adamant | Shift Gear, Gear Grind, Wild Charge, Protect |
| Magnezone | Choice Specs | Magnet Pull | Modest | Thunderbolt, Flash Cannon, Volt Switch, Tri Attack |
| Porygon-Z | Life Orb | Adaptability | Timid | Tri Attack, Shadow Ball, Ice Beam, Nasty Plot |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_COLRESS ===
Name: Colress
Class: Scientist
Pic: Colress
Gender: Male
Music: Suspicious
Double Battle: No
AI: Smart Trainer

Genesect @ Choice Scarf
Naive Nature
Level: 100
Ability: Download
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- U-turn
- Iron Head
- Thunderbolt
- Flamethrower

Iron Hands @ Assault Vest
Adamant Nature
Level: 100
Ability: Quark Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Drain Punch
- Wild Charge
- Ice Punch

Golurk @ Groundite
Adamant Nature
Level: 100
Ability: No Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earthquake
- Shadow Punch
- Ice Punch
- Drain Punch

Klinklang @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shift Gear
- Gear Grind
- Wild Charge
- Protect

Magnezone @ Choice Specs
Modest Nature
Level: 100
Ability: Magnet Pull
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flash Cannon
- Volt Switch
- Tri Attack

Porygon-Z @ Life Orb
Timid Nature
Level: 100
Ability: Adaptability
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tri Attack
- Shadow Ball
- Ice Beam
- Nasty Plot
```

</details>


### Lendário associado

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Colress_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Nihilego** (UB-01 Symbiont). Colress é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Colress, o cientista de Black 2/White 2, cujo objetivo declarado é descobrir como trazer à tona a força verdadeira dos Pokémon.

**A criatura.** A Pokédex diz que a Nihilego produz uma neurotoxina forte, e que ela dá grande poder a quem é injetado enquanto derruba as inibições. O mundo dela, em USUM, é o Ultra Deep Sea.

**O fragmento.** Água funda que não afoga. Luzes pálidas flutuando, arrastando fios. Onde uma toca o chão de vidro, o vidro brilha mais forte e trinca um pouco. Leitura visual: laboratório submerso, tons de azul e branco.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> The rift let out into deep water that did not drown you.
>
> Pale lights drifted overhead, trailing threads. Wherever one touched the glass floor, the glass glowed brighter, and cracked a little.

**Boss**

> The lights in the water drew together into one shape.
>
> It hung in front of you, weightless and patient, as if waiting to be let in.

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

> File UB-01. Symbiont.
>
> A scientist who spent his life trying to remove a Pokémon's limits, and a creature that removes them for free.
>
> You tell me he asked you to refuse it. I have underlined that. I did not expect to.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Symbiont_Arrival:
	.string "The rift let out into deep water that\n"
	.string "did not drown you.\p"
	.string "Pale lights drifted overhead, trailing\n"
	.string "threads. Wherever one touched the\l"
	.string "glass floor, the glass glowed brighter,\l"
	.string "and cracked a little.$"

Nexus_Text_Symbiont_Boss:
	.string "The lights in the water drew together\n"
	.string "into one shape.\p"
	.string "It hung in front of you, weightless and\n"
	.string "patient, as if waiting to be let in.$"

Nexus_Text_Symbiont_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-01. Symbiont.\p"
	.string "A scientist who spent his life trying to\n"
	.string "remove a Pokémon's limits, and a\l"
	.string "creature that removes them for free.\p"
	.string "You tell me he asked you to refuse it. I\n"
	.string "have underlined that. I did not expect\l"
	.string "to.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Colress_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Colress cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Ah! A test subject. Forgive me -- a challenger.
>
> I don't remember how I arrived here, and I find I don't mind. A new place is only a new set of conditions.
>
> My question is the same one I always ask: what draws out a Pokémon's true strength? Let's collect another answer!

**Derrota**

> Remarkable. I am going to need a larger notebook.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Colress_Intro:
	.string "Ah! A test subject. Forgive me -- a\n"
	.string "challenger.\p"
	.string "I don't remember how I arrived here,\n"
	.string "and I find I don't mind. A new place is\l"
	.string "only a new set of conditions.\p"
	.string "My question is the same one I always\n"
	.string "ask: what draws out a Pokémon's true\l"
	.string "strength? Let's collect another\l"
	.string "answer!$"

Nexus_Text_Colress_Defeat:
	.string "Remarkable. I am going to need a larger\n"
	.string "notebook.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Cada variação pega um ângulo diferente do personagem.

**Variação 2 — método científico.** Humor de laboratório: hipótese, método, controle nenhum. Na derrota, a alegria de estar certo e perder ao mesmo tempo.

**Antes da luta**

> Hypothesis: this Trainer is stronger than they look.
>
> Method: battle. Controls: none whatsoever. My colleagues would be horrified.
>
> Let us proceed!

**Derrota**

> Hypothesis confirmed. How delightful, to be right and to lose at once.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Colress_Intro2:
	.string "Hypothesis: this Trainer is stronger\n"
	.string "than they look.\p"
	.string "Method: battle. Controls: none\n"
	.string "whatsoever. My colleagues would be\l"
	.string "horrified.\p"
	.string "Let us proceed!$"

Nexus_Text_Colress_Defeat2:
	.string "Hypothesis confirmed. How delightful,\n"
	.string "to be right and to lose at once.$"
```

</details>

**Variação 3 — já nos vimos?.** R21 em jogo: ele tem a sensação de já ter construído uma máquina para fazer o jogador perder. Pode ter acontecido, ou não; a fala não depende disso.

**Antes da luta**

> Have we met? I have the curious feeling I once built a machine to make you lose.
>
> It didn't work, I assume. They so rarely do on the interesting ones.
>
> Shall we test a new variable?

**Derrota**

> Ah… The variable was you. It is always you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Colress_Intro3:
	.string "Have we met? I have the curious feeling\n"
	.string "I once built a machine to make you lose.\p"
	.string "It didn't work, I assume. They so rarely\n"
	.string "do on the interesting ones.\p"
	.string "Shall we test a new variable?$"

Nexus_Text_Colress_Defeat3:
	.string "Ah… The variable was you. It is always\n"
	.string "you.$"
```

</details>



### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Colress_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Colress é o **campeão**, a luta logo antes da Nihilego. A fala é sobre a criatura, sem dizer o nome dela.

O Colress passou a vida tentando tirar os limites dos Pokémon, e encontra uma criatura que faz exatamente isso, de graça, para quem ficar parado. Ele vê o próprio sonho realizado e descobre que não gosta de assistir. A vitória do jogador é a força que veio dos Pokémon, sem toxina nenhuma. O que fica: foi preciso aquela criatura para ele entender para que serve um limite, e o pedido final é o mais honesto dele: "recuse. Digo isso como alguém que teria aceitado".

**Antes da luta**

> You feel it too, don't you? Something in the water, deciding whether to let us in.
>
> I have been observing it. It does not attack. It offers.
>
> Whatever it touches grows stronger and forgets how to stop. It is everything I ever set out to find…
>
> …and I find I do not enjoy watching it. Before it chooses you, show me what your Pokémon are without it!

**Derrota**

> …There. That was their own strength, every last point of it. No toxin could have measured that.

**Depois da luta**

> I spent years trying to take away a Pokémon's limits. It took that creature to show me what a limit is for.
>
> It will offer you strength. It will be very generous about it.
>
> Refuse. I say that as a man who would have said yes.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Colress_ChampionIntro:
	.string "You feel it too, don't you? Something in\n"
	.string "the water, deciding whether to let us\l"
	.string "in.\p"
	.string "I have been observing it. It does not\n"
	.string "attack. It offers.\p"
	.string "Whatever it touches grows stronger and\n"
	.string "forgets how to stop. It is everything I\l"
	.string "ever set out to find…\p"
	.string "…and I find I do not enjoy watching it.\n"
	.string "Before it chooses you, show me what\l"
	.string "your Pokémon are without it!$"

Nexus_Text_Colress_ChampionDefeat:
	.string "…There. That was their own strength,\n"
	.string "every last point of it. No toxin could\l"
	.string "have measured that.$"

Nexus_Text_Colress_ChampionAfter:
	.string "{SPEAKER NAME_COLRESS}I spent years trying to take away a\n"
	.string "Pokémon's limits. It took that creature\l"
	.string "to show me what a limit is for.\p"
	.string "It will offer you strength. It will be\n"
	.string "very generous about it.\p"
	.string "Refuse. I say that as a man who would\n"
	.string "have said yes.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1: sobre a criatura, pelo olhar dele, sem dizer o nome da espécie. Labels no padrão `Nexus_Text_Colress_Champion*` + sufixo.

**Variação 2 — a amostra.** O Colress guardou uma gota de amostra e pegou a seringa onze vezes sem usar. Curiosidade virou medo, e medo é dado novo. No fim ele despejou a amostra na água funda.

**Antes da luta**

> I collected a sample. Only a drop, from a thread it left on the glass.
>
> I have not tested it. I have picked up the syringe eleven times.
>
> A scientist is supposed to be curious. It turns out I am also afraid. That is new data.
>
> Let's gather some more. Battle!

**Derrota**

> A result I can trust. Thank you, sincerely.

**Depois da luta**

> I poured the sample out this morning, into the deep water. It glowed all the way down.
>
> Eleven attempts and one decision. Not a bad ratio.
>
> When it drifts close, don't hold still. It only chooses what stays still long enough.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Colress_ChampionIntro2:
	.string "I collected a sample. Only a drop, from a\n"
	.string "thread it left on the glass.\p"
	.string "I have not tested it. I have picked up\n"
	.string "the syringe eleven times.\p"
	.string "A scientist is supposed to be curious.\n"
	.string "It turns out I am also afraid. That is\l"
	.string "new data.\p"
	.string "Let's gather some more. Battle!$"

Nexus_Text_Colress_ChampionDefeat2:
	.string "A result I can trust. Thank you,\n"
	.string "sincerely.$"

Nexus_Text_Colress_ChampionAfter2:
	.string "{SPEAKER NAME_COLRESS}I poured the sample out this morning,\n"
	.string "into the deep water. It glowed all the\l"
	.string "way down.\p"
	.string "Eleven attempts and one decision. Not a\n"
	.string "bad ratio.\p"
	.string "When it drifts close, don't hold still.\n"
	.string "It only chooses what stays still long\l"
	.string "enough.$"
```

</details>

**Variação 3 — a mulher de branco.** Alguém disse sim antes do jogador: uma mulher de branco, muito certa, muito bonita, que queria ser amada sem condição (a Lusamine de algum fragmento, nunca nomeada — fio Alola). Ele anotou tudo e não disse “pare”. O conselho: o time é quem diz pare.

**Antes da luta**

> Someone before you said yes to it. A woman in white. Very certain. Very beautiful.
>
> She wanted to be loved without conditions. It offered exactly that, and she let it in.
>
> I took notes. That is the part I think about.
>
> Show me your Pokémon's strength. Their own. Please.

**Derrota**

> Yes. That is what I should have been measuring.

**Depois da luta**

> A good experiment needs someone who can say stop. She had no one. I was standing right there.
>
> If it offers you anything, anything at all, look to your team first.
>
> They are your someone. Let them say stop.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Colress_ChampionIntro3:
	.string "Someone before you said yes to it. A\n"
	.string "woman in white. Very certain. Very\l"
	.string "beautiful.\p"
	.string "She wanted to be loved without\n"
	.string "conditions. It offered exactly that,\l"
	.string "and she let it in.\p"
	.string "I took notes. That is the part I think\n"
	.string "about.\p"
	.string "Show me your Pokémon's strength. Their\n"
	.string "own. Please.$"

Nexus_Text_Colress_ChampionDefeat3:
	.string "Yes. That is what I should have been\n"
	.string "measuring.$"

Nexus_Text_Colress_ChampionAfter3:
	.string "{SPEAKER NAME_COLRESS}A good experiment needs someone who\n"
	.string "can say stop. She had no one. I was\l"
	.string "standing right there.\p"
	.string "If it offers you anything, anything at\n"
	.string "all, look to your team first.\p"
	.string "They are your someone. Let them say\n"
	.string "stop.$"
```

</details>

