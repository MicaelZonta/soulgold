# Peony

**Região da ficha:** Galar

Aparece no checklist como:

- **Peony** (Galar · Isle of Armor e Crown Tundra) — ex-Líder e aventureiro, irmão mais novo de Rose.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_PEONY`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_PEONY` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_PEONY` | `graphics/object_events/pics/people/special/peony.png` (boneco 17x23, quadro 32x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_PEONY`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Peony/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PEONY` | `graphics/trainers/front_pics/peony.png` (64x64) + `peony_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_PEONY` = **1207** (bloco 2, flag `0xB2B`), luta genérica `Nexus_EventScript_Peony_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_PEONY ===
Name: Peony
Class: Pkmn Trainer 1
Pic: Peony
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Perrserker @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Steely Spirit
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Iron Head
- Close Combat
- U-turn

Dialga @ Adamant Orb
Quiet Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Draco Meteor
- Flash Cannon
- Fire Blast

Registeel @ Leftovers
Careful Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Body Press
- Protect
- Iron Defense

Aggron @ Steeltite
Adamant Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Body Press
- Rock Slide
- Protect

Copperajah @ Assault Vest
Adamant Nature
Level: 100
Ability: Heavy Metal
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Power Whip
- High Horsepower
- Rock Slide

Bronzong @ Mental Herb
Sassy Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Iron Head
- Hypnosis
- Reflect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Registeel** — `Nexus_EventScript_Peony_Registeel_ChampionFight` (falas `Nexus_Text_Peony_Registeel_Champion*`)
- **Calyrex** — `Nexus_EventScript_Peony_Calyrex_ChampionFight` (falas `Nexus_Text_Peony_Calyrex_Champion*`)
- **Dialga** — `Nexus_EventScript_Peony_Dialga_ChampionFight` (falas `Nexus_Text_Peony_Dialga_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Peony_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Chief Peony, reporting for adventure! Got my notes, my team, and absolutely no idea where my daughter went!
>
> A battle first? That's the spirit!

**Derrota**

> Ha! What a discovery! I'll need a whole page for that one!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
