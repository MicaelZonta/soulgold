# Iris

**Região da ficha:** Unova

Aparece no checklist como:

- **Iris — Dragão** (Unova · Líderes de Ginásio) — prodígio que se torna Campeã em *Black 2/White 2*.
- **Iris — Campeã** (Unova · Elite Four e Campeões) — jovem mestre de dragões e Campeã na sequência de Unova.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_IRIS` = **1187** (bloco 2, flag `0xB17`), luta genérica `Nexus_EventScript_Iris_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_IRIS ===
Name: Iris
Class: Champion
Pic: Iris
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

Latias @ Soul Dew
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Psyshock
- Recover
- Calm Mind

Salamence @ Dragotite
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Dragon Claw
- Brick Break
- Dragon Dance

Haxorus @ Lum Berry
Jolly Nature
Level: 100
Ability: Mold Breaker
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Dragon Claw
- Poison Jab
- Stomping Tantrum

Lapras @ Assault Vest
Modest Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freeze-Dry
- Hydro Pump
- Ice Shard
- Thunderbolt

Archeops @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Defeatist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Acrobatics
- Rock Slide
- Tailwind
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Reshiram** — `Nexus_EventScript_Iris_Reshiram_ChampionFight` (falas `Nexus_Text_Iris_Reshiram_Champion*`)
- **Latias** — `Nexus_EventScript_Iris_Latias_ChampionFight` (falas `Nexus_Text_Iris_Latias_Champion*`)
- **Regidrago** — `Nexus_EventScript_Iris_Regidrago_ChampionFight` (falas `Nexus_Text_Iris_Regidrago_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Iris_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Hi! I'm Iris! My dragons get restless when I talk for too long.
>
> See? That one already wants to start. Let's make this a good one!

**Derrota**

> Wow! We lost, but everybody's still smiling!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
