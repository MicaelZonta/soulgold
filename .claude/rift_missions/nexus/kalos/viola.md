# Viola

**Região da ficha:** Kalos

Aparece no checklist como:

- **Viola — Inseto** (Kalos · Líderes de Ginásio) — fotógrafa e Líder de Santalune.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_VIOLA` = **1215** (bloco 2, flag `0xB33`), luta genérica `Nexus_EventScript_Viola_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_VIOLA ===
Name: Viola
Class: Leader
Pic: Viola
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Masquerain @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Hydro Pump
- Air Slash
- Tailwind

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

Buzzwole @ Leftovers
Adamant Nature
Level: 100
Ability: Beast Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leech Life
- Drain Punch
- Ice Punch
- Bulk Up

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

- **Genesect** — `Nexus_EventScript_Viola_Genesect_ChampionFight` (falas `Nexus_Text_Viola_Genesect_Champion*`)
- **Buzzwole** — `Nexus_EventScript_Viola_Buzzwole_ChampionFight` (falas `Nexus_Text_Viola_Buzzwole_Champion*`)
- **Kartana** — `Nexus_EventScript_Viola_Kartana_ChampionFight` (falas `Nexus_Text_Viola_Kartana_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Viola_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Hold that pose! Ah, too late. The best moments never wait for the camera.
>
> I'm Viola. Let's battle. I want to see the expression you make when you give it everything!

**Derrota**

> Fantastic! A picture couldn't have caught half of that!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
