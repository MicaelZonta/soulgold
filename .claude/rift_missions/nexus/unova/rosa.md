# Rosa

**Região da ficha:** Unova

Aparece no checklist como:

- **Rosa** (Unova · Rivais) — protagonista feminina de *Black 2/White 2*.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_ROSA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_ROSA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_ROSA` | `graphics/object_events/pics/people/special/rosa.png` (boneco 16x20, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_ROSA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Rosa/Sprite - Aveontrainer.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ROSA` | `graphics/trainers/front_pics/rosa.png` (64x64) + `rosa_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_ROSA` = **1209** (bloco 2, flag `0xB2D`), luta genérica `Nexus_EventScript_Rosa_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_ROSA ===
Name: Rosa
Class: Pkmn Trainer 1
Pic: Rosa
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Reshiram @ Life Orb
Modest Nature
Level: 100
Ability: Turboblaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blue Flare
- Draco Meteor
- Heat Wave
- Earth Power

Virizion @ Life Orb
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leaf Blade
- Close Combat
- Stone Edge
- Protect

Lucario @ Fightite
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Meteor Mash
- Extreme Speed
- Swords Dance

Serperior @ Life Orb
Timid Nature
Level: 100
Ability: Contrary
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leaf Storm
- Dragon Pulse
- Glare
- Substitute

Chandelure @ Choice Scarf
Modest Nature
Level: 100
Ability: Flash Fire
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Heat Wave
- Energy Ball
- Trick

Braviary @ Sharp Beak
Adamant Nature
Level: 100
Ability: Defiant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Close Combat
- Tailwind
- Rock Slide
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Reshiram** — `Nexus_EventScript_Rosa_Reshiram_ChampionFight` (falas `Nexus_Text_Rosa_Reshiram_Champion*`)
- **Virizion** — `Nexus_EventScript_Rosa_Virizion_ChampionFight` (falas `Nexus_Text_Rosa_Virizion_Champion*`)
- **Meloetta** — `Nexus_EventScript_Rosa_Meloetta_ChampionFight` (falas `Nexus_Text_Rosa_Meloetta_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Rosa_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Rosa! I've tried smiling for the camera, but my team always knows when I'm faking it.
>
> A battle gets a real smile out of me. Let's see if it does the same for you!

**Derrota**

> There it is! Even after a loss, I can't stop smiling!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
