# Nessa

**Região da ficha:** Galar

Aparece no checklist como:

- **Nessa — Água** (Galar · Líderes de Ginásio) — modelo e poderosa rival esportiva de Sonia.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_NESSA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_NESSA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_NESSA` | `graphics/object_events/pics/people/special/nessa.png` (boneco 17x24, quadro 32x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_NESSA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Nessa/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_NESSA` | `graphics/trainers/front_pics/nessa.png` (64x64) + `nessa_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_NESSA` = **1204** (bloco 2, flag `0xB28`), luta genérica `Nexus_EventScript_Nessa_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_NESSA ===
Name: Nessa
Class: Leader
Pic: Nessa
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Pelipper @ Damp Rock
Bold Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Tailwind
- Roost
- Protect

Kyogre @ Choice Specs
Modest Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Water Spout
- Origin Pulse
- Ice Beam
- Thunder

Suicune @ Leftovers
Bold Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Snarl
- Calm Mind
- Protect

Gyarados @ Watertite
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Waterfall
- Crunch
- Ice Fang

Drednaw @ Life Orb
Adamant Nature
Level: 100
Ability: Swift Swim
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Rock Slide
- High Horsepower
- Protect

Barraskewda @ Choice Band
Adamant Nature
Level: 100
Ability: Swift Swim
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Close Combat
- Psychic Fangs
- Flip Turn
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Kyogre** — `Nexus_EventScript_Nessa_Kyogre_ChampionFight` (falas `Nexus_Text_Nessa_Kyogre_Champion*`)
- **Tapu Fini** — `Nexus_EventScript_Nessa_TapuFini_ChampionFight` (falas `Nexus_Text_Nessa_TapuFini_Champion*`)
- **Suicune** — `Nexus_EventScript_Nessa_Suicune_ChampionFight` (falas `Nexus_Text_Nessa_Suicune_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Nessa_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> A still surface doesn't tell you how strong the current is.
>
> I'm Nessa. Take your stance. You'll feel the difference soon enough.

**Derrota**

> You read the current and held your ground. Nicely done.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
