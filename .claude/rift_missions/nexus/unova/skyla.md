# Skyla

**Região da ficha:** Unova

Aparece no checklist como:

- **Skyla — Voador** (Unova · Líderes de Ginásio) — piloto que administra o Ginásio de Mistralton.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_SKYLA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_SKYLA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_SKYLA` | `graphics/object_events/pics/people/special/skyla.png` (boneco 16x21, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_SKYLA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Skyla/Sprite - Miused.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_SKYLA` | `graphics/trainers/front_pics/skyla.png` (64x64) + `skyla_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_SKYLA` = **1212** (bloco 2, flag `0xB30`), luta genérica `Nexus_EventScript_Skyla_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_SKYLA ===
Name: Skyla
Class: Leader
Pic: Skyla
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

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

Lugia @ Leftovers
Timid Nature
Level: 100
Ability: Multiscale
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Aeroblast
- Ice Beam
- Calm Mind
- Roost

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

Swanna @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Hydration
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Hurricane
- Tailwind
- Roost

Skarmory @ Rocky Helmet
Impish Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spikes
- Tailwind
- Brave Bird
- Roost

Swoobat @ Focus Sash
Timid Nature
Level: 100
Ability: Simple
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Calm Mind
- Stored Power
- Air Slash
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Tornadus Incarnate** — `Nexus_EventScript_Skyla_Tornadus_ChampionFight` (falas `Nexus_Text_Skyla_Tornadus_Champion*`)
- **Lugia** — `Nexus_EventScript_Skyla_Lugia_ChampionFight` (falas `Nexus_Text_Skyla_Lugia_Champion*`)
- **Celesteela** — `Nexus_EventScript_Skyla_Celesteela_ChampionFight` (falas `Nexus_Text_Skyla_Celesteela_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Skyla_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Skyla! I check the wind before every flight. My partners do the rest.
>
> Ready for takeoff? Let's see how well you handle a little turbulence!

**Derrota**

> A perfect landing! Even if I was the one who came down first.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
