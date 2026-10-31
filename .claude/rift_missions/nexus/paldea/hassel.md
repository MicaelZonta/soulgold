# Hassel

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Hassel — Dragão** (Paldea (Kitakami e Blueberry) · Elite Four e Campeões) — professor de arte e herdeiro de uma família de treinadores de dragões.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_HASSEL` = **1182** (bloco 2, flag `0xB12`), luta genérica `Nexus_EventScript_Hassel_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_HASSEL ===
Name: Hassel
Class: Elite Four
Pic: Hassel
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Rayquaza @ Life Orb
Naive Nature
Level: 100
Ability: Air Lock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Extreme Speed
- Flamethrower
- Protect

Regidrago @ Dragon Fang
Modest Nature
Level: 100
Ability: Dragons Maw
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Energy
- Dragon Pulse
- Ancient Power
- Protect

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

Baxcalibur @ Loaded Dice
Adamant Nature
Level: 100
Ability: Thermal Exchange
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Spear
- Scale Shot
- High Horsepower
- Protect

Noivern @ Focus Sash
Timid Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Hurricane
- Flamethrower
- U-turn

Dragalge @ Assault Vest
Modest Nature
Level: 100
Ability: Adaptability
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Draco Meteor
- Hydro Pump
- Focus Blast
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Rayquaza** — `Nexus_EventScript_Hassel_Rayquaza_ChampionFight` (falas `Nexus_Text_Hassel_Rayquaza_Champion*`)
- **Regidrago** — `Nexus_EventScript_Hassel_Regidrago_ChampionFight` (falas `Nexus_Text_Hassel_Regidrago_Champion*`)
- **Latias** — `Nexus_EventScript_Hassel_Latias_ChampionFight` (falas `Nexus_Text_Hassel_Latias_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Hassel_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Ah, a young Trainer! Every battle shows me something my students have yet to teach me.
>
> Please, express yourself! My dragons and I will answer with all our hearts!

**Derrota**

> Oh... wonderful! Forgive the tears. I am very proud of you.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
