# Soliera

**Região da ficha:** Alola

Aparece no checklist como:

- **Soliera** (Alola · Ultra Recon Squad) — comandante da equipe encontrada principalmente em *Ultra Moon*.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_SOLIERA`, campeão da Naganadel. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Eternatus**, Veneno/Dragão como o Naganadel e chegado do espaço; semi-lendário **Latios**, o jato do céu; Mega **Beedrill** (Bugtite: Adaptability), o ferrão. Mais Crobat, Dragapult e Drapion. *Plano:* velocidade e um golpe só. O Crobat abre com Tailwind e Taunt, e a Mega Beedrill e o Dragapult batem antes de tudo. O Fell Stinger do Beedrill é o golpe que termina e ainda sobe o ataque. O Drapion arma Toxic Spikes e o Eternatus fecha com Dynamax Cannon e Recover.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Eternatus | Life Orb | Pressure | Timid | Dynamax Cannon, Sludge Bomb, Flamethrower, Recover |
| Latios | Choice Specs | Levitate | Timid | Draco Meteor, Luster Purge, Aura Sphere, Surf |
| Beedrill | Bugtite | Sniper | Jolly | Poison Jab, Fell Stinger, U-turn, Drill Run |
| Crobat | Sitrus Berry | Infiltrator | Jolly | Tailwind, Brave Bird, Cross Poison, Taunt |
| Dragapult | Choice Band | Clear Body | Jolly | Dragon Darts, Phantom Force, U-turn, Sucker Punch |
| Drapion | Leftovers | Battle Armor | Careful | Knock Off, Poison Jab, Toxic Spikes, Swords Dance |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_SOLIERA ===
Name: Soliera
Class: Pkmn Ranger
Pic: Soliera
Gender: Female
Music: Intense
Double Battle: No
AI: Smart Trainer

Eternatus @ Life Orb
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dynamax Cannon
- Sludge Bomb
- Flamethrower
- Recover

Latios @ Choice Specs
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Luster Purge
- Aura Sphere
- Surf

Beedrill @ Bugtite
Jolly Nature
Level: 100
Ability: Sniper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poison Jab
- Fell Stinger
- U-turn
- Drill Run

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Brave Bird
- Cross Poison
- Taunt

Dragapult @ Choice Band
Jolly Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Darts
- Phantom Force
- U-turn
- Sucker Punch

Drapion @ Leftovers
Careful Nature
Level: 100
Ability: Battle Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Knock Off
- Poison Jab
- Toxic Spikes
- Swords Dance
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Naganadel** (UB Stinger). Soliera é o campeão dela: a quinta luta do Daily, logo antes da boss battle. **R1:** o Naganadel evolui do Poipole, que é presente em `Route40_House4`; este fragmento só entra no sorteio depois de o jogador capturar um Naganadel.

**Quem é.** Soliera, a integrante da Ultra Recon Squad focada na missão acima de tudo, e quem entrega o Poipole ao jogador em Ultra Sun.

**A criatura.** Naganadel guarda centenas de litros de líquido venenoso no corpo e voa rápido demais para acompanhar. É o Poipole crescido.

**O fragmento.** O topo de uma torre, muito acima de uma cidade de luzes (a Megalo Tower lembrada de longe). Vento de todos os lados. Riscos longos e retos cortados no telhado, todos apontando para o mesmo ponto.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> The top of a tower, far above a city of lights.
>
> The wind came from every side at once. Long straight scars were cut into the roof, all of them pointing at the same spot.

**Boss**

> Something passed overhead too fast to see. Then again, lower.
>
> The twelfth time, it stopped in the air in front of you, and pointed.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB Stinger.
>
> You tell me it carries enough poison to fill a bathtub, and flies faster than you could follow.
>
> I have moved my desk slightly further from the window. For no reason.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Stinger_Arrival:
	.string "The top of a tower, far above a city of\n"
	.string "lights.\p"
	.string "The wind came from every side at once.\n"
	.string "Long straight scars were cut into the\l"
	.string "roof, all of them pointing at the same\l"
	.string "spot.$"

Nexus_Text_Stinger_Boss:
	.string "Something passed overhead too fast to\n"
	.string "see. Then again, lower.\p"
	.string "The twelfth time, it stopped in the air\n"
	.string "in front of you, and pointed.$"

Nexus_Text_Stinger_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Stinger.\p"
	.string "You tell me it carries enough poison to\n"
	.string "fill a bathtub, and flies faster than\l"
	.string "you could follow.\p"
	.string "I have moved my desk slightly further\n"
	.string "from the window. For no reason.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Soliera cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Identify yourself. …No matter.
>
> I do not know how I arrived here. My orders have not changed.
>
> Obstacles are removed. Prepare yourself.

**Derrota**

> Understood. Obstacle not removed. Adjusting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Soliera_Intro:
	.string "Identify yourself. …No matter.\p"
	.string "I do not know how I arrived here. My\n"
	.string "orders have not changed.\p"
	.string "Obstacles are removed. Prepare\n"
	.string "yourself.$"

Nexus_Text_Soliera_Defeat:
	.string "Understood. Obstacle not removed.\n"
	.string "Adjusting.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Soliera é o **campeão**, a luta logo antes da Naganadel. A fala é sobre a criatura, sem dizer o nome dela.

A criatura já passou onze vezes sobre a torre, cada vez mais baixo, e a Soliera contou. No mundo dela, entregaram um pequeno como aquele a quem os ajudou, e foi ela quem entregou. Nunca soube no que ele se tornou, e talvez esteja prestes a descobrir. Na derrota, ela não pede segunda chance. O que fica: se foi nisso que ele cresceu, alguém o criou bem, ou ninguém criou; de perto, o jogador vai saber. E o único aviso que a criatura dá: a agulha aponta antes do golpe. (A narração do boss fecha a conta: "the twelfth time".)

**Antes da luta**

> It has passed over this tower eleven times. I have counted.
>
> It is faster than anything in our records, and it carries enough venom to fell a city. Every pass comes lower.
>
> In my world, we gave a small one like it to someone who helped us. I was the one who handed it over.
>
> I never learned what it became. …Perhaps I am about to. Prepare yourself.

**Derrota**

> My strike missed. I will not ask for a second.

**Depois da luta**

> If that is what it grew into, then someone raised it well. Or no one did.
>
> I cannot tell which from here. You will be close enough to see.
>
> Watch the needle. It points before it strikes. That is the only warning it gives.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Soliera_ChampionIntro:
	.string "It has passed over this tower eleven\n"
	.string "times. I have counted.\p"
	.string "It is faster than anything in our\n"
	.string "records, and it carries enough venom to\l"
	.string "fell a city. Every pass comes lower.\p"
	.string "In my world, we gave a small one like it\n"
	.string "to someone who helped us. I was the one\l"
	.string "who handed it over.\p"
	.string "I never learned what it became.\n"
	.string "…Perhaps I am about to. Prepare\l"
	.string "yourself.$"

Nexus_Text_Soliera_ChampionDefeat:
	.string "My strike missed. I will not ask for a\n"
	.string "second.$"

Nexus_Text_Soliera_ChampionAfter:
	.string "{SPEAKER NAME_SOLIERA}If that is what it grew into, then\n"
	.string "someone raised it well. Or no one did.\p"
	.string "I cannot tell which from here. You will\n"
	.string "be close enough to see.\p"
	.string "Watch the needle. It points before it\n"
	.string "strikes. That is the only warning it\l"
	.string "gives.$"
```

</details>

