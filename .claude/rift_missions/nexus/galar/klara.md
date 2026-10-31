# Klara

**Região da ficha:** Galar

Aparece no checklist como:

- **Klara — Veneno** (Galar · Rivais de Galar) — rival de *Sword* no Isle of Armor, ambiciosa e trapaceira.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_KLARA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_KLARA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_KLARA` | `graphics/object_events/pics/people/special/klara.png` (boneco 16x20, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_KLARA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Klara/Sprite - Aveontrainer.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_KLARA` | `graphics/trainers/front_pics/klara.png` (64x64) + `klara_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_KLARA` = **1191** (bloco 2, flag `0xB1B`), luta genérica `Nexus_EventScript_Klara_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_KLARA ===
Name: Klara
Class: Pkmn Trainer 1
Pic: Klara
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Eternatus @ Life Orb
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dynamax Cannon
- Sludge Bomb
- Flamethrower
- Recover

Munkidori @ Focus Sash
Timid Nature
Level: 100
Ability: Toxic Chain
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Sludge Bomb
- Psychic
- U-turn

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

Slowbro-Galar @ Assault Vest
Modest Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shell Side Arm
- Psychic
- Flamethrower
- Ice Beam

Scolipede @ Life Orb
Jolly Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Megahorn
- Poison Jab
- Swords Dance
- Protect

Weezing @ Black Sludge
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Will-O-Wisp
- Toxic Spikes
- Sludge Bomb
- Taunt
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Munkidori** — `Nexus_EventScript_Klara_Munkidori_ChampionFight` (falas `Nexus_Text_Klara_Munkidori_Champion*`)
- **Eternatus** — `Nexus_EventScript_Klara_Eternatus_ChampionFight` (falas `Nexus_Text_Klara_Eternatus_Champion*`)
- **Fezandipiti** — `Nexus_EventScript_Klara_Fezandipiti_ChampionFight` (falas `Nexus_Text_Klara_Fezandipiti_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Klara_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Oh, a challenger! How sweet. You won't mind losing to me, will you?
>
> I've worked terribly hard on this smile. Don't make me drop it.

**Derrota**

> Oh, come ON! ...I mean, congratulations. Truly.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
