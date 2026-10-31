# Rowan

**Região da ficha:** Sinnoh

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_ROWAN` = **1208** (bloco 2, flag `0xB2C`), luta genérica `Nexus_EventScript_Rowan_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_ROWAN ===
Name: Rowan
Class: Pkmn Trainer 1
Pic: Rowan
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Infernape @ Focus Sash
Jolly Nature
Level: 100
Ability: Iron Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Fire Punch
- Mach Punch

Dialga @ Adamant Orb
Quiet Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunder Wave
- Draco Meteor
- Flash Cannon
- Fire Blast

Uxie @ Light Clay
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Reflect
- Light Screen
- U-turn

Gallade @ Psychite
Jolly Nature
Level: 100
Ability: Sharpness
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sacred Sword
- Psycho Cut
- Leaf Blade
- Swords Dance

Torterra @ Leftovers
Adamant Nature
Level: 100
Ability: Shell Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wood Hammer
- High Horsepower
- Stone Edge
- Synthesis

Empoleon @ Leftovers
Modest Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Flash Cannon
- Ice Beam
- Grass Knot
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Dialga** — `Nexus_EventScript_Rowan_Dialga_ChampionFight` (falas `Nexus_Text_Rowan_Dialga_Champion*`)
- **Uxie** — `Nexus_EventScript_Rowan_Uxie_ChampionFight` (falas `Nexus_Text_Rowan_Uxie_Champion*`)
- **Silvally** — `Nexus_EventScript_Rowan_Silvally_ChampionFight` (falas `Nexus_Text_Rowan_Silvally_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Rowan_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Rowan. I study evolution.
>
> I have spent a lifetime watching Pokemon change. A Trainer should be capable of the same. Show me.

**Derrota**

> Good. You adapted. Keep asking what you might become.

### Diálogo associado ao lendário

_Não escrito._
