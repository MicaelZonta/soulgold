# Larry

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Larry — Normal** (Paldea (Kitakami e Blueberry) · Líderes de Ginásio) — funcionário exausto que também integra a Elite Four.
- **Larry — Voador** (Paldea (Kitakami e Blueberry) · Elite Four e Campeões) — usa Pokémon Voadores na Elite Four por ordem de Geeta.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_LARRY` = **1193** (bloco 2, flag `0xB1D`), luta genérica `Nexus_EventScript_Larry_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_LARRY ===
Name: Larry
Class: Elite Four
Pic: Larry
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Terapagos @ Leftovers
Modest Nature
Level: 100
Ability: Tera Shift
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tera Starstorm
- Earth Power
- Calm Mind
- Protect

Tornadus @ Covert Cloak
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bleakwind Storm
- Tailwind
- Taunt
- Protect

Pidgeot @ Flyingite
Timid Nature
Level: 100
Ability: Keen Eye
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Heat Wave
- Tailwind
- Roost

Staraptor @ Choice Scarf
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Close Combat
- Double-Edge
- U-turn

Dudunsparce @ Leftovers
Careful Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- Coil
- Roost
- Rock Slide

Flamigo @ Life Orb
Jolly Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Brave Bird
- Tailwind
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Terapagos** — `Nexus_EventScript_Larry_Terapagos_ChampionFight` (falas `Nexus_Text_Larry_Terapagos_Champion*`)
- **Tornadus Incarnate** — `Nexus_EventScript_Larry_Tornadus_ChampionFight` (falas `Nexus_Text_Larry_Tornadus_Champion*`)
- **Regigigas** — `Nexus_EventScript_Larry_Regigigas_ChampionFight` (falas `Nexus_Text_Larry_Regigigas_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Larry_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Larry. I was told this battle counts toward my working hours.
>
> I'd appreciate a straightforward match. My lunch break is approaching.

**Derrota**

> That settles it. I'll put the loss in my report.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
