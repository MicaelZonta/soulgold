# Avery

**Região da ficha:** Galar

Aparece no checklist como:

- **Avery — Psíquico** (Galar · Rivais de Galar) — rival de *Shield* no Isle of Armor, orgulhoso e teatral.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_AVERY`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_AVERY` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_AVERY` | `graphics/object_events/pics/people/special/avery.png` (boneco 16x20, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_AVERY`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Avery/Sprite - Aveontrainer.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_AVERY` | `graphics/trainers/front_pics/avery.png` (64x64) + `avery_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_AVERY` = **1168** (bloco 2, flag `0xB04`), luta genérica `Nexus_EventScript_Avery_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_AVERY ===
Name: Avery
Class: Pkmn Trainer 1
Pic: Avery
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Indeedee-F @ Sitrus Berry
Bold Nature
Level: 100
Ability: Psychic Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Follow Me
- Psychic
- Dazzling Gleam
- Healing Wish

Mewtwo @ Leftovers
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psystrike
- Aura Sphere
- Ice Beam
- Calm Mind

Articuno-Galar @ Leftovers
Timid Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freezing Glare
- Hurricane
- Tailwind
- Recover

Alakazam @ Psychite
Timid Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Focus Blast
- Shadow Ball
- Dazzling Gleam

Slowking-Galar @ Colbur Berry
Calm Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Psyshock
- Slack Off
- Chilly Reception

Espeon @ Life Orb
Timid Nature
Level: 100
Ability: Magic Bounce
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psyshock
- Dazzling Gleam
- Shadow Ball
- Calm Mind
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Mewtwo** — `Nexus_EventScript_Avery_Mewtwo_ChampionFight` (falas `Nexus_Text_Avery_Mewtwo_Champion*`)
- **Articuno Galar** — `Nexus_EventScript_Avery_GalarianArticuno_ChampionFight` (falas `Nexus_Text_Avery_GalarianArticuno_Champion*`)
- **Hoopa Confined** — `Nexus_EventScript_Avery_Hoopa_ChampionFight` (falas `Nexus_Text_Avery_Hoopa_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Avery_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Avery, at your service. Do try to contain your astonishment.
>
> My psychic powers are exceptional. My victory shall be equally so!

**Derrota**

> An unforeseen development! I shall levitate above this indignity.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
