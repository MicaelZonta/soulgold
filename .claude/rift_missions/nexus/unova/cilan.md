# Cilan

**Região da ficha:** Unova

Aparece no checklist como:

- **Cilan — Grama** (Unova · Líderes de Ginásio) — garçom e Pokémon Connoisseur do Striaton Gym.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_CILAN` = **1173** (bloco 2, flag `0xB09`), luta genérica `Nexus_EventScript_Cilan_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_CILAN ===
Name: Cilan
Class: Leader
Pic: Cilan
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Groudon @ Leftovers
Adamant Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Precipice Blades
- Heat Crash
- Stealth Rock
- Protect

Whimsicott @ Covert Cloak
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Tailwind
- Encore
- Sunny Day

Virizion @ Life Orb
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leaf Blade
- Close Combat
- Stone Edge
- Protect

Sceptile @ Grasstite
Timid Nature
Level: 100
Ability: Overgrow
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Solar Beam
- Dragon Pulse
- Focus Blast
- Protect

Simisage @ Focus Sash
Jolly Nature
Level: 100
Ability: Overgrow
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Seed Bomb
- Knock Off
- Rock Slide
- Taunt

Crustle @ White Herb
Adamant Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shell Smash
- Rock Slide
- X-Scissor
- Knock Off
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Virizion** — `Nexus_EventScript_Cilan_Virizion_ChampionFight` (falas `Nexus_Text_Cilan_Virizion_Champion*`)
- **Groudon** — `Nexus_EventScript_Cilan_Groudon_ChampionFight` (falas `Nexus_Text_Cilan_Groudon_Champion*`)
- **Shaymin Land** — `Nexus_EventScript_Cilan_Shaymin_ChampionFight` (falas `Nexus_Text_Cilan_Shaymin_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Cilan_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> A good battle, like a fine meal, needs balance.
>
> I'm Cilan. Let me see how your partners bring out each other's strengths!

**Derrota**

> A remarkable finish! I shall remember that combination.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
