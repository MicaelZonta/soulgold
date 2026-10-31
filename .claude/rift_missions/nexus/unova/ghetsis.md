# Ghetsis

**Região da ficha:** Unova

Aparece no checklist como:

- **Ghetsis** (Unova · Team Plasma) — manipulador que usa a falsa libertação dos Pokémon para buscar domínio.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_GHETSIS` = **1179** (bloco 2, flag `0xB0F`), luta genérica `Nexus_EventScript_Ghetsis_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_GHETSIS ===
Name: Ghetsis
Class: Team Plasma
Pic: Ghetsis
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Cobalion @ Chople Berry
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Close Combat
- Thunder Wave
- Stone Edge

Kyurem-White @ Life Orb
Modest Nature
Level: 100
Ability: Turboblaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Ice Beam
- Draco Meteor
- Fusion Flare
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

Hydreigon @ Life Orb
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Draco Meteor
- Flamethrower
- Protect

Eelektross @ Assault Vest
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flamethrower
- Giga Drain
- Knock Off

Cofagrigus @ Leftovers
Relaxed Nature
Level: 100
Ability: Mummy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Will-O-Wisp
- Icy Wind
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Kyurem** — `Nexus_EventScript_Ghetsis_Kyurem_ChampionFight` (falas `Nexus_Text_Ghetsis_Kyurem_Champion*`)
- **Cobalion** — `Nexus_EventScript_Ghetsis_Cobalion_ChampionFight` (falas `Nexus_Text_Ghetsis_Cobalion_Champion*`)
- **Pecharunt** — `Nexus_EventScript_Ghetsis_Pecharunt_ChampionFight` (falas `Nexus_Text_Ghetsis_Pecharunt_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Ghetsis_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> People call obedience peace when the voice giving orders is pleasant enough.
>
> I have dispensed with the pleasant voice. You will learn obedience all the same.

**Derrota**

> You dare deny me? Even now, you dare?!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
