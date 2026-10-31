# Peonia

**Região da ficha:** Galar

Aparece no checklist como:

- **Peonia** (Galar · Isle of Armor e Crown Tundra) — filha de Peony, interessada nas Dynamax Adventures.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_PEONIA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_PEONIA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_PEONIA` | `graphics/object_events/pics/people/special/peonia.png` (boneco 16x21, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_PEONIA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Peonia/Sprite - CyberStryke7.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PEONIA` | `graphics/trainers/front_pics/peonia.png` (64x64) + `peonia_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_PEONIA` = **1206** (bloco 2, flag `0xB2A`), luta genérica `Nexus_EventScript_Peonia_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_PEONIA ===
Name: Peonia
Class: Pkmn Trainer 1
Pic: Peonia
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

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

Suicune @ Leftovers
Bold Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Snarl
- Calm Mind
- Tailwind

Aerodactyl @ Rocktite
Jolly Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Dual Wingbeat
- Ice Fang
- Tailwind

Tyrantrum @ Life Orb
Adamant Nature
Level: 100
Ability: Rock Head
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Head Smash
- Dragon Claw
- Rock Slide
- Dragon Dance

Toxtricity @ Throat Spray
Modest Nature
Level: 100
Ability: Punk Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Overdrive
- Sludge Bomb
- Volt Switch
- Protect

Rotom-Wash @ Sitrus Berry
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Will-O-Wisp
- Thunderbolt
- Volt Switch
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Lugia** — `Nexus_EventScript_Peonia_Lugia_ChampionFight` (falas `Nexus_Text_Peonia_Lugia_Champion*`)
- **Suicune** — `Nexus_EventScript_Peonia_Suicune_ChampionFight` (falas `Nexus_Text_Peonia_Suicune_Champion*`)
- **Articuno** — `Nexus_EventScript_Peonia_Articuno_ChampionFight` (falas `Nexus_Text_Peonia_Articuno_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Peonia_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Dad planned another expedition. I took the other path before he finished the title.
>
> I'm Peonia. Fancy a battle? It's much more fun when I pick the adventure myself.

**Derrota**

> Now that was worth the detour! Don't tell Dad. He'll make a banner.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
