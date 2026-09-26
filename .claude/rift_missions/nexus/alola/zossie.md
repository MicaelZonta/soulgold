# Zossie

**Região da ficha:** Alola

Aparece no checklist como:

- **Zossie** (Alola · Ultra Recon Squad) — jovem e curiosa parceira de Dulse.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_ZOSSIE`, campeão da Poipole. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Magearna**, feita à mão e com um coração artificial (Soul-Heart); semi-lendário **Mew**, curioso e brincalhão como o Poipole; Mega **Clefable** (Fairytite: Fada/Voador, Magic Bounce). Mais Mimikyu, Ribombee e Goodra. Tudo gruda ou cuida (Sticky Web, Gooey, Follow Me), e o Mimikyu só quer ser amado, como ela. *Plano:* apoio em Doubles. A Clefable puxa os golpes com Follow Me, o Mew põe Tailwind e queima com Will-O-Wisp, o Ribombee arma a teia, e a Magearna fica mais forte a cada Pokémon que cai.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Magearna | Leftovers | Soul-Heart | Modest | Fleur Cannon, Flash Cannon, Aura Sphere, Ice Beam |
| Mew | Leftovers | Synchronize | Timid | Psychic, Nasty Plot, Tailwind, Will-O-Wisp |
| Clefable | Fairytite | Magic Guard | Bold | Moonblast, Follow Me, Moonlight, Thunder Wave |
| Mimikyu | Life Orb | Disguise | Jolly | Play Rough, Shadow Claw, Shadow Sneak, Swords Dance |
| Ribombee | Focus Sash | Shield Dust | Timid | Sticky Web, Moonblast, Pollen Puff, Stun Spore |
| Goodra | Assault Vest | Gooey | Modest | Draco Meteor, Sludge Bomb, Fire Blast, Thunderbolt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_ZOSSIE ===
Name: Zossie
Class: Pkmn Ranger
Pic: Zossie
Gender: Female
Music: Girl
Double Battle: Yes
AI: Smart Trainer

Magearna @ Leftovers
Modest Nature
Level: 100
Ability: Soul-Heart
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fleur Cannon
- Flash Cannon
- Aura Sphere
- Ice Beam

Mew @ Leftovers
Timid Nature
Level: 100
Ability: Synchronize
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Nasty Plot
- Tailwind
- Will-O-Wisp

Clefable @ Fairytite
Bold Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Follow Me
- Moonlight
- Thunder Wave

Mimikyu @ Life Orb
Jolly Nature
Level: 100
Ability: Disguise
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Play Rough
- Shadow Claw
- Shadow Sneak
- Swords Dance

Ribombee @ Focus Sash
Timid Nature
Level: 100
Ability: Shield Dust
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Moonblast
- Pollen Puff
- Stun Spore

Goodra @ Assault Vest
Modest Nature
Level: 100
Ability: Gooey
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Sludge Bomb
- Fire Blast
- Thunderbolt
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Poipole** (UB Adhesive). Zossie é o campeão dela: a quinta luta do Daily, logo antes da boss battle. **R1:** o Poipole tem método fora do Nexus (presente em `Route40_House4`), então este fragmento só entra no sorteio depois de o jogador capturar um.

**Quem é.** Zossie, a mais nova e mais entusiasmada da Ultra Recon Squad, vinda de Ultra Megalopolis, o mundo que perdeu a luz.

**A criatura.** O filhote das Ultra Beasts, dado ao jogador pela Ultra Recon Squad em USUM. O codinome é *Adhesive*: o veneno dele gruda.

**O fragmento.** Uma sala pequena, clara, sem cantos. Luzes macias perto do teto. Quando uma encosta na manga do jogador, fica grudada um instante antes de soltar. É o único fragmento sem ameaça, e a expedição mais leve do loop.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A small bright room with no corners.
>
> Soft lights floated near the ceiling. When one brushed your sleeve, it stayed there a moment before letting go.

**Boss**

> One of the lights drifted down from the ceiling and landed in front of you.
>
> It had a face, and it was very, very curious about yours.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB Adhesive.
>
> No harm done. No damage. One very small creature that followed you all the way to the door.
>
> It is the shortest file I have. I have read it four times.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Adhesive_Arrival:
	.string "A small bright room with no corners.\p"
	.string "Soft lights floated near the ceiling.\n"
	.string "When one brushed your sleeve, it stayed\l"
	.string "there a moment before letting go.$"

Nexus_Text_Adhesive_Boss:
	.string "One of the lights drifted down from the\n"
	.string "ceiling and landed in front of you.\p"
	.string "It had a face, and it was very, very\n"
	.string "curious about yours.$"

Nexus_Text_Adhesive_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Adhesive.\p"
	.string "No harm done. No damage. One very small\n"
	.string "creature that followed you all the way\l"
	.string "to the door.\p"
	.string "It is the shortest file I have. I have\n"
	.string "read it four times.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Zossie cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hiii! Wait, where am I? It's not dark, so it's definitely not home!
>
> You're a Trainer, right? Battle me! Please please please!

**Derrota**

> Aww! You're really good! Can we be friends now? That's how it works, right?

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zossie_Intro:
	.string "Hiii! Wait, where am I? It's not dark, so\n"
	.string "it's definitely not home!\p"
	.string "You're a Trainer, right? Battle me!\n"
	.string "Please please please!$"

Nexus_Text_Zossie_Defeat:
	.string "Aww! You're really good! Can we be\n"
	.string "friends now? That's how it works,\l"
	.string "right?$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Zossie é o **campeão**, a luta logo antes da Poipole. A fala é sobre a criatura, sem dizer o nome dela.

Tem um pequeno escondido nas luzes, seguindo a Zossie o dia todo. É venenoso, a cabeça inteira é uma agulha, mas só gruda em quem ele gosta, e ele quer ver se gosta do jogador. A vitória: "ele gostou de você!". O que fica é o mundo dela: ficou escuro por tanto tempo que esqueceram como é quando uma coisa pequena e brilhante só quer ficar perto. Ele vai vir dizer oi, talvez dê uma picadinha, e ela pede que o jogador prometa ser gentil.

**Antes da luta**

> There's a little one hiding up in the lights. It's been following me around all day!
>
> It's poisonous, you know. Its whole head is a needle. But it only sticks to people it likes.
>
> I think it likes me! …And I think it wants to see if it likes you.
>
> So let's show it a really, really good battle!

**Derrota**

> Aww… It liked that! It liked you! I could tell!

**Depois da luta**

> Where I'm from, it was dark for so long. We forgot what it feels like when something small and bright just… wants to be near you.
>
> It's going to come say hi. It might sting a little. That's just how it says hello!
>
> Be gentle with it, okay? Promise.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zossie_ChampionIntro:
	.string "There's a little one hiding up in the\n"
	.string "lights. It's been following me around\l"
	.string "all day!\p"
	.string "It's poisonous, you know. Its whole\n"
	.string "head is a needle. But it only sticks to\l"
	.string "people it likes.\p"
	.string "I think it likes me! …And I think it\n"
	.string "wants to see if it likes you.\p"
	.string "So let's show it a really, really good\n"
	.string "battle!$"

Nexus_Text_Zossie_ChampionDefeat:
	.string "Aww… It liked that! It liked you! I could\n"
	.string "tell!$"

Nexus_Text_Zossie_ChampionAfter:
	.string "{SPEAKER NAME_ZOSSIE}Where I'm from, it was dark for so long.\n"
	.string "We forgot what it feels like when\l"
	.string "something small and bright just… wants\l"
	.string "to be near you.\p"
	.string "It's going to come say hi. It might\n"
	.string "sting a little. That's just how it says\l"
	.string "hello!\p"
	.string "Be gentle with it, okay? Promise.$"
```

</details>

