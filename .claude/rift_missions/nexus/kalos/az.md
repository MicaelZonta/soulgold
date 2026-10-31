# AZ

**Região da ficha:** Kalos

Aparece no checklist como:

- **AZ** (Kalos · Outros notáveis) — antigo rei de Kalos ligado à guerra, à arma suprema e a Floette.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_AZ` = **1164** (bloco 2, flag `0xB00`), luta genérica `Nexus_EventScript_AZ_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_AZ ===
Name: AZ
Class: Pkmn Trainer 1
Pic: AZ
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Sigilyph @ Flame Orb
Timid Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psycho Shift
- Air Slash
- Roost
- Tailwind

Xerneas @ Power Herb
Modest Nature
Level: 100
Ability: Fairy Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Geomancy
- Moonblast
- Protect
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

Floette-Eternal @ Fairytite
Timid Nature
Level: 100
Ability: Flower Veil
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Light of Ruin
- Moonblast
- Giga Drain
- Protect

Golurk @ Assault Vest
Adamant Nature
Level: 100
Ability: Iron Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Shadow Punch
- Ice Punch
- Drain Punch

Torkoal @ Heat Rock
Bold Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Solar Beam
- Yawn
- Rapid Spin
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Xerneas** — `Nexus_EventScript_AZ_Xerneas_ChampionFight` (falas `Nexus_Text_AZ_Xerneas_Champion*`)
- **Yveltal** — `Nexus_EventScript_AZ_Yveltal_ChampionFight` (falas `Nexus_Text_AZ_Yveltal_Champion*`)
- **Celebi** — `Nexus_EventScript_AZ_Celebi_ChampionFight` (falas `Nexus_Text_AZ_Celebi_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_AZ_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I once mistook a weapon for an answer. The flowers have outlived every stone I raised.
>
> These companions stayed. I would like you to understand why.

**Derrota**

> You fought without throwing anything away. Hold on to that.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
