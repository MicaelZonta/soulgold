# Colress

**Região da ficha:** Unova

Aparece no checklist como:

- **Colress** (Unova · Team Plasma) — cientista interessado em descobrir como liberar o potencial máximo dos Pokémon.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** **Nihilego** (UB-01 Symbiont). Colress é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Ficha do Looker, no altar, no dia em que a UB é capturada**

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

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Colress cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Colress é o **campeão**, a luta logo antes da Nihilego. A fala é sobre a criatura, sem dizer o nome dela.

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

