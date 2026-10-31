# Juniper

**Região da ficha:** Unova

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_JUNIPER` = **1189** (bloco 2, flag `0xB19`), luta genérica `Nexus_EventScript_Juniper_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_JUNIPER ===
Name: Juniper
Class: Pkmn Trainer 1
Pic: Juniper
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Amoonguss @ Rocky Helmet
Bold Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spore
- Rage Powder
- Pollen Puff
- Clear Smog

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

Meloetta @ Throat Spray
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Focus Blast
- U-turn

Audino @ Normalite
Bold Nature
Level: 100
Ability: Healer
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Dazzling Gleam
- Calm Mind
- Heal Pulse

Cinccino @ Loaded Dice
Jolly Nature
Level: 100
Ability: Skill Link
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tail Slap
- Bullet Seed
- Rock Blast
- Protect

Sawsbuck @ Life Orb
Jolly Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Horn Leech
- Double-Edge
- High Horsepower
- Swords Dance
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Genesect** — `Nexus_EventScript_Juniper_Genesect_ChampionFight` (falas `Nexus_Text_Juniper_Genesect_Champion*`)
- **Meloetta** — `Nexus_EventScript_Juniper_Meloetta_ChampionFight` (falas `Nexus_Text_Juniper_Meloetta_Champion*`)
- **Mew** — `Nexus_EventScript_Juniper_Mew_ChampionFight` (falas `Nexus_Text_Juniper_Mew_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Juniper_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Professor Juniper. I study how Pokemon began, but their choices still surprise me.
>
> Would you help with a little fieldwork? A battle tells me what a specimen jar never could.

**Derrota**

> Excellent! Every time I think I understand them, they teach me something new.

### Diálogo associado ao lendário

_Não escrito._
