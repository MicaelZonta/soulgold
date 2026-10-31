# Mustard

**Região da ficha:** Galar

Aparece no checklist como:

- **Mustard** (Galar · Isle of Armor e Crown Tundra) — antigo Campeão de Galar e mestre do Master Dojo.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_MUSTARD`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_MUSTARD` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_MUSTARD` | `graphics/object_events/pics/people/special/mustard.png` (boneco 16x20, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_MUSTARD`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Mustard/Sprite - Lolw3e932.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_MUSTARD` | `graphics/trainers/front_pics/mustard.png` (64x64) + `mustard_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_MUSTARD` = **1201** (bloco 2, flag `0xB25`), luta genérica `Nexus_EventScript_Mustard_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_MUSTARD ===
Name: Mustard
Class: Expert
Pic: Mustard
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

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

Koraidon @ Life Orb
Jolly Nature
Level: 100
Ability: Orichalcum Pulse
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Collision Course
- Flare Blitz
- Dragon Claw
- U-turn

Urshifu @ Choice Band
Adamant Nature
Level: 100
Ability: Unseen Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wicked Blow
- Close Combat
- Sucker Punch
- U-turn

Lucario @ Fightite
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Meteor Mash
- Extreme Speed
- Swords Dance

Corviknight @ Rocky Helmet
Impish Nature
Level: 100
Ability: Mirror Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Body Press
- Tailwind
- Roost

Luxray @ Choice Band
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wild Charge
- Crunch
- Ice Fang
- Play Rough
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Urshifu Single Strike** — `Nexus_EventScript_Mustard_Urshifu_ChampionFight` (falas `Nexus_Text_Mustard_Urshifu_Champion*`)
- **Koraidon** — `Nexus_EventScript_Mustard_Koraidon_ChampionFight` (falas `Nexus_Text_Mustard_Koraidon_Champion*`)
- **Marshadow** — `Nexus_EventScript_Mustard_Marshadow_ChampionFight` (falas `Nexus_Text_Mustard_Marshadow_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Mustard_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Heh heh! Stiff shoulders, busy eyes. You've been practicing, haven't you?
>
> Let's see what happens when the old man makes you change your plans!

**Derrota**

> Ho ho! Good! You found the opening before I could close it.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
