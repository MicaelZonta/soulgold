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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_ZOSSIE`, treinador das salas (sem lendário associado). Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

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

Nenhum. A proposta de 26/09 a fazia campeã da Poipole, mas o autor tirou o
Poipole do pool (26/09/2026): ele agora vem junto com a luta do Naganadel
(ficha da [Soliera](soliera.md)). Zossie fica só como treinadora das quatro
primeiras salas.


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

Nenhum (sem lendário associado).
