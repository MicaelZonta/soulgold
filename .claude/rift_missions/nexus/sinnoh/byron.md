# Byron

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Byron — Aço** (Sinnoh · Líderes de Ginásio) — Líder de Canalave e pai de Roark.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** **Stakataka** (UB Assembly). Byron é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Ficha do Looker, no altar, no dia em que a UB é capturada**

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

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Byron cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Byron é o **campeão**, a luta logo antes da Stakataka. A fala é sobre a criatura, sem dizer o nome dela.

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

