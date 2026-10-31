# Lysandre

**Região da ficha:** Kalos

Aparece no checklist como:

- **Lysandre** (Kalos · Team Flare) — líder que pretende usar a arma suprema para criar um mundo “belo”.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_LYSANDRE` = **1197** (bloco 2, flag `0xB21`), luta genérica `Nexus_EventScript_Lysandre_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_LYSANDRE ===
Name: Lysandre
Class: Pkmn Trainer 1
Pic: Lysandre
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Yveltal @ Life Orb
Naive Nature
Level: 100
Ability: Dark Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Oblivion Wing
- Heat Wave
- Sucker Punch

Volcanion @ Assault Vest
Modest Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Steam Eruption
- Heat Wave
- Sludge Bomb
- Earth Power

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

Pyroar @ Life Orb
Timid Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Hyper Voice
- Dark Pulse
- Protect

Mienshao @ Focus Sash
Jolly Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Knock Off
- Wide Guard

Honchkrow @ Scope Lens
Adamant Nature
Level: 100
Ability: Super Luck
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Night Slash
- Sucker Punch
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Yveltal** — `Nexus_EventScript_Lysandre_Yveltal_ChampionFight` (falas `Nexus_Text_Lysandre_Yveltal_Champion*`)
- **Xerneas** — `Nexus_EventScript_Lysandre_Xerneas_ChampionFight` (falas `Nexus_Text_Lysandre_Xerneas_Champion*`)
- **Volcanion** — `Nexus_EventScript_Lysandre_Volcanion_ChampionFight` (falas `Nexus_Text_Lysandre_Volcanion_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Lysandre_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Everything beautiful is asked to endure those who would consume it.
>
> Show me whether your strength preserves anything worth keeping.

**Derrota**

> Such power... And still you refuse my conclusion.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
