# Katy

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Katy — Inseto** (Paldea (Kitakami e Blueberry) · Líderes de Ginásio) — confeiteira de Cortondo e primeiro desafio recomendado.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_KATY` = **1190** (bloco 2, flag `0xB1A`), luta genérica `Nexus_EventScript_Katy_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_KATY ===
Name: Katy
Class: Leader
Pic: Katy
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

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

Slither Wing @ Booster Energy
Adamant Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- First Impression
- Close Combat
- Leech Life
- Protect

Beedrill @ Bugtite
Jolly Nature
Level: 100
Ability: Sniper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poison Jab
- Fell Stinger
- U-turn
- Drill Run

Ursaring @ Flame Orb
Adamant Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Facade
- Close Combat
- Crunch
- Protect

Vivillon @ Focus Sash
Timid Nature
Level: 100
Ability: Compound Eyes
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sleep Powder
- Hurricane
- Quiver Dance
- Protect

Forretress @ Leftovers
Relaxed Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Gyro Ball
- Body Press
- Rapid Spin
- Spikes
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Genesect** — `Nexus_EventScript_Katy_Genesect_ChampionFight` (falas `Nexus_Text_Katy_Genesect_Champion*`)
- **Slither Wing** — `Nexus_EventScript_Katy_SlitherWing_ChampionFight` (falas `Nexus_Text_Katy_SlitherWing_Champion*`)
- **Pheromosa** — `Nexus_EventScript_Katy_Pheromosa_ChampionFight` (falas `Nexus_Text_Katy_Pheromosa_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Katy_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> A lovely cake takes patience. So does raising a tiny bug into something magnificent.
>
> I do hope you saved room for a challenge, dear.

**Derrota**

> Oh, how delightful! A little bitter for me, but beautifully made.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
