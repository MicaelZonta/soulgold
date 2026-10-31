# Dawn

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Dawn** (Sinnoh · Rival) — protagonista feminina de *Diamond/Pearl/Platinum*.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_DAWN`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_DAWN` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_DAWN` | `graphics/object_events/pics/people/special/dawn.png` (boneco 14x20, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_DAWN`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Dawn/Sprite - Aveontrainer.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_DAWN` | `graphics/trainers/front_pics/dawn.png` (64x64) + `dawn_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_DAWN` = **1176** (bloco 2, flag `0xB0C`), luta genérica `Nexus_EventScript_Dawn_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_DAWN ===
Name: Dawn
Class: Pkmn Trainer 1
Pic: Dawn
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Palkia @ Life Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spacial Rend
- Hydro Pump
- Thunder
- Fire Blast

Cresselia @ Leftovers
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Psyshock
- Moonlight
- Thunder Wave

Lopunny @ Normalite
Jolly Nature
Level: 100
Ability: Limber
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Return
- Close Combat
- Ice Punch

Empoleon @ Leftovers
Modest Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Flash Cannon
- Ice Beam
- Grass Knot

Togekiss @ Sitrus Berry
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Air Slash
- Dazzling Gleam
- Follow Me
- Roost

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
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Palkia** — `Nexus_EventScript_Dawn_Palkia_ChampionFight` (falas `Nexus_Text_Dawn_Palkia_Champion*`)
- **Cresselia** — `Nexus_EventScript_Dawn_Cresselia_ChampionFight` (falas `Nexus_Text_Dawn_Cresselia_Champion*`)
- **Mesprit** — `Nexus_EventScript_Dawn_Mesprit_ChampionFight` (falas `Nexus_Text_Dawn_Mesprit_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Dawn_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Hi! I'm Dawn. I was practicing a new combination, but a battle sounds even better!
>
> No need to worry! That's what I tell myself before the tricky part.

**Derrota**

> Oh! That was the tricky part. Your team was amazing!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
