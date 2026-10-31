# Grusha

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Grusha — Gelo** (Paldea (Kitakami e Blueberry) · Líderes de Ginásio) — antigo snowboarder e Líder de Glaseado.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_GRUSHA` = **1181** (bloco 2, flag `0xB11`), luta genérica `Nexus_EventScript_Grusha_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_GRUSHA ===
Name: Grusha
Class: Leader
Pic: Grusha
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Ninetales-Alola @ Light Clay
Timid Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Aurora Veil
- Blizzard
- Moonblast
- Encore

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

Chien-Pao @ Focus Sash
Jolly Nature
Level: 100
Ability: Sword of Ruin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Crash
- Sacred Sword
- Sucker Punch
- Protect

Altaria @ Dragotite
Modest Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Flamethrower
- Tailwind
- Roost

Cetitan @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Slush Rush
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Belly Drum
- Ice Spinner
- High Horsepower
- Ice Shard

Frosmoth @ Heavy-Duty Boots
Modest Nature
Level: 100
Ability: Ice Scales
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Quiver Dance
- Ice Beam
- Bug Buzz
- Wide Guard
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Kyurem** — `Nexus_EventScript_Grusha_Kyurem_ChampionFight` (falas `Nexus_Text_Grusha_Kyurem_Champion*`)
- **Chien Pao** — `Nexus_EventScript_Grusha_ChienPao_ChampionFight` (falas `Nexus_Text_Grusha_ChienPao_Champion*`)
- **Articuno** — `Nexus_EventScript_Grusha_Articuno_ChampionFight` (falas `Nexus_Text_Grusha_Articuno_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Grusha_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I know what it costs to miss a turn. You don't get every chance twice.
>
> Keep your balance. I'm not slowing down for you.

**Derrota**

> You held your line. I respect that.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
