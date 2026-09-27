# Ramos

**Região da ficha:** Kalos

Aparece no checklist como:

- **Ramos — Grama** (Kalos · Líderes de Ginásio) — jardineiro veterano e Líder de Coumarine.

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
| `OBJ_EVENT_GFX_RAMOS` | `graphics/object_events/pics/people/special/ramos.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RAMOS` | `graphics/trainers/front_pics/ramos.png` |

Reduzido de uma arte grande sem grade de pixels (`.filetransfer/Ramos/Ramos - Trainer.png`); o rosto foi redesenhado à mão depois da redução.

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_RAMOS` = **980** (flag de batalha `0x8D4`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Ramos_Fight` (genérica) e `Nexus_EventScript_Ramos_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Ramos.

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_RAMOS`, campeão da Kartana. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Xerneas**, semi-lendário **Celebi**, Mega **Victreebel** (Poisontite: Innards Out), mais Gogoat, Jumpluff e Ferrothorn. O Xerneas dá vida e vira árvore quando descansa; o Celebi é o guardião das florestas. São "algo que cresce", que é o que o eco pede. *Plano:* um jardim de desgaste. Leech Seed (Celebi, Jumpluff, Ferrothorn), Sleep Powder e Spikes; o Xerneas usa Geomancy no primeiro turno com Power Herb; a Mega Victreebel pune quem a derruba. Em Doubles, o Jumpluff põe Tailwind.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Grass Knot, Focus Blast |
| Celebi | Leftovers | Natural Cure | Bold | Giga Drain, Psychic, Recover, Leech Seed |
| Victreebel | Poisontite | Chlorophyll | Modest | Sludge Bomb, Leaf Storm, Sleep Powder, Sucker Punch |
| Gogoat | Sitrus Berry | Sap Sipper | Adamant | Horn Leech, Bulk Up, Earthquake, Milk Drink |
| Jumpluff | Focus Sash | Infiltrator | Jolly | Sleep Powder, Tailwind, Leech Seed, U-turn |
| Ferrothorn | Leftovers | Iron Barbs | Relaxed | Power Whip, Gyro Ball, Leech Seed, Spikes |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_RAMOS ===
Name: Ramos
Class: Leader
Pic: Ramos
Gender: Male
Music: Hg Sage
Double Battle: No
AI: Smart Trainer

Xerneas @ Power Herb
Modest Nature
Level: 100
Ability: Fairy Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Geomancy
- Moonblast
- Grass Knot
- Focus Blast

Celebi @ Leftovers
Bold Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Psychic
- Recover
- Leech Seed

Victreebel @ Poisontite
Modest Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Leaf Storm
- Sleep Powder
- Sucker Punch

Gogoat @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Horn Leech
- Bulk Up
- Earthquake
- Milk Drink

Jumpluff @ Focus Sash
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sleep Powder
- Tailwind
- Leech Seed
- U-turn

Ferrothorn @ Leftovers
Relaxed Nature
Level: 100
Ability: Iron Barbs
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Power Whip
- Gyro Ball
- Leech Seed
- Spikes
```

</details>


### Lendário associado

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Ramos_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Kartana** (UB-04 Blade). Ramos é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Ramos, líder de Coumarine, jardineiro que leva a mesma tesoura de poda há trinta anos e chama o jogador de "sprout".

**A criatura.** Kartana é um origami: corpo fino como papel, afiado como espada. Foi vista derrubando uma torre de aço com um golpe só. Mundo em USUM: Ultra Forest.

**O fragmento.** Uma floresta de árvores brancas, todas dobradas. Galhos vincados em ângulos limpos, folhas cortadas no mesmo formato. Nada cresce: tudo foi podado.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A forest of white trees, every one of them folded.
>
> Branches creased at clean angles. Leaves cut to the same shape. Nothing was growing. Everything had been trimmed.

**Boss**

> A leaf came loose from the nearest branch and did not fall.
>
> It stood up and unfolded one arm, and the tree behind it slid apart in two clean pieces.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB-04. Blade.
>
> A gardener in a forest where nothing grows, and a creature as thin as paper that once cut down a steel tower.
>
> I have put a paperweight on this file. It seemed only sensible.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Blade_Arrival:
	.string "A forest of white trees, every one of\n"
	.string "them folded.\p"
	.string "Branches creased at clean angles.\n"
	.string "Leaves cut to the same shape. Nothing\l"
	.string "was growing. Everything had been\l"
	.string "trimmed.$"

Nexus_Text_Blade_Boss:
	.string "A leaf came loose from the nearest\n"
	.string "branch and did not fall.\p"
	.string "It stood up and unfolded one arm, and\n"
	.string "the tree behind it slid apart in two\l"
	.string "clean pieces.$"

Nexus_Text_Blade_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-04. Blade.\p"
	.string "A gardener in a forest where nothing\n"
	.string "grows, and a creature as thin as paper\l"
	.string "that once cut down a steel tower.\p"
	.string "I have put a paperweight on this file.\n"
	.string "It seemed only sensible.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Ramos_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Ramos cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hoho! Now where has this old gardener wandered off to?
>
> Never mind, never mind. Wherever there's ground, something can grow. And wherever something grows, there's a sprout to test.
>
> Let's see how deep your roots go!

**Derrota**

> Hohoho! Deep roots, sprout. Deep roots.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Ramos_Intro:
	.string "Hoho! Now where has this old gardener\n"
	.string "wandered off to?\p"
	.string "Never mind, never mind. Wherever\n"
	.string "there's ground, something can grow. And\l"
	.string "wherever something grows, there's a\l"
	.string "sprout to test.\p"
	.string "Let's see how deep your roots go!$"

Nexus_Text_Ramos_Defeat:
	.string "Hohoho! Deep roots, sprout. Deep roots.$"
```

</details>


### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Ramos_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Ramos é o **campeão**, a luta logo antes da Kartana. A fala é sobre a criatura, sem dizer o nome dela.

O segredo de trinta anos de tesoura: você nunca corta para ferir a árvore, corta para ela voltar mais forte. A criatura corta melhor do que ele jamais cortou, limpo, perfeito, até aço, e nunca deixou nada crescer de volta. A vitória do jogador é "algo que cresce". O que fica: não tente ser mais afiado que ela; seja algo que volta a crescer, "a única coisa que uma lâmina nunca consegue terminar".

**Antes da luta**

> Thirty years with these shears, sprout. Want to know the secret?
>
> You never cut to hurt the tree. You cut so it grows back stronger.
>
> The little thing in this forest cuts better than I ever could. Clean. Perfect. Through steel, even.
>
> And not once has it let anything grow back. Show me something with roots!

**Derrota**

> Hohoho! Now that's growing, that is. Nothing here could trim that down.

**Depois da luta**

> It's light enough for the wind to carry, and sharp enough to halve a mountain.
>
> Don't try to be sharper than it, sprout. You'll lose.
>
> Be something that grows back. That's the one thing a blade can never finish.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Ramos_ChampionIntro:
	.string "Thirty years with these shears, sprout.\n"
	.string "Want to know the secret?\p"
	.string "You never cut to hurt the tree. You cut\n"
	.string "so it grows back stronger.\p"
	.string "The little thing in this forest cuts\n"
	.string "better than I ever could. Clean.\l"
	.string "Perfect. Through steel, even.\p"
	.string "And not once has it let anything grow\n"
	.string "back. Show me something with roots!$"

Nexus_Text_Ramos_ChampionDefeat:
	.string "Hohoho! Now that's growing, that is.\n"
	.string "Nothing here could trim that down.$"

Nexus_Text_Ramos_ChampionAfter:
	.string "{SPEAKER NAME_RAMOS}It's light enough for the wind to carry,\n"
	.string "and sharp enough to halve a mountain.\p"
	.string "Don't try to be sharper than it, sprout.\n"
	.string "You'll lose.\p"
	.string "Be something that grows back. That's\n"
	.string "the one thing a blade can never finish.$"
```

</details>

