# Brycen

**Região da ficha:** Unova

Aparece no checklist como:

- **Brycen — Gelo** (Unova · Líderes de Ginásio) — antigo ator e Líder de Icirrus.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_BRYCEN` = **1171** (bloco 2, flag `0xB07`), luta genérica `Nexus_EventScript_Brycen_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_BRYCEN ===
Name: Brycen
Class: Leader
Pic: Brycen
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Kyurem @ Life Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Freeze-Dry
- Draco Meteor
- Earth Power

Articuno @ Heavy-Duty Boots
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Hurricane
- Roost
- Haze

Abomasnow @ Icetite
Quiet Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Giga Drain
- Earth Power
- Protect

Beartic @ Life Orb
Adamant Nature
Level: 100
Ability: Slush Rush
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Crash
- Close Combat
- Aqua Jet
- Protect

Mamoswine @ Life Orb
Adamant Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Crash
- High Horsepower
- Ice Shard
- Stealth Rock

Froslass @ Focus Sash
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icy Wind
- Shadow Ball
- Will-O-Wisp
- Destiny Bond
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Kyurem** — `Nexus_EventScript_Brycen_Kyurem_ChampionFight` (falas `Nexus_Text_Brycen_Kyurem_Champion*`)
- **Articuno** — `Nexus_EventScript_Brycen_Articuno_ChampionFight` (falas `Nexus_Text_Brycen_Articuno_Champion*`)
- **Regice** — `Nexus_EventScript_Brycen_Regice_ChampionFight` (falas `Nexus_Text_Brycen_Regice_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Brycen_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I once spoke for an audience. Now my partners speak for me.
>
> Watch their movements. There is no wasted motion.

**Derrota**

> Your resolve did not freeze. Well done.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
