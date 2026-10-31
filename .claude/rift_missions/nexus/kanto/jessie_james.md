# Jessie e James

**Região da ficha:** Kanto

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_JESSIE_JAMES` = **1188** (bloco 2, flag `0xB18`), luta genérica `Nexus_EventScript_JessieJames_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_JESSIE_JAMES ===
Name: Jess&James
Class: Team Rocket
Pic: Jessie James
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Mewtwo @ Life Orb
Timid Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psystrike
- Aura Sphere
- Ice Beam
- Recover

Mew @ Mental Herb
Timid Nature
Level: 100
Ability: Synchronize
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Will-O-Wisp
- Tailwind
- Knock Off

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

Arbok @ Black Sludge
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Gunk Shot
- Glare
- Sucker Punch
- Knock Off

Victreebel @ Life Orb
Modest Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Leaf Storm
- Sleep Powder
- Sucker Punch

Meowth @ Eviolite
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Feint
- Knock Off
- U-turn
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Meloetta** — `Nexus_EventScript_JessieJames_Meloetta_ChampionFight` (falas `Nexus_Text_JessieJames_Meloetta_Champion*`)
- **Zygarde** — `Nexus_EventScript_JessieJames_Zygarde_ChampionFight` (falas `Nexus_Text_JessieJames_Zygarde_Champion*`)
- **Hoopa Confined** — `Nexus_EventScript_JessieJames_Hoopa_ChampionFight` (falas `Nexus_Text_JessieJames_Hoopa_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_JessieJames_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> JESSIE: Prepare for trouble!
>
> JAMES: We've rehearsed this entrance all morning!
>
> MEOWTH: Then quit talkin' and start battlin'!

**Derrota**

> JESSIE: Our perfect plan!
>
> JAMES: Perhaps we should have rehearsed the battle, too.

### Diálogo associado ao lendário

_Não escrito._
