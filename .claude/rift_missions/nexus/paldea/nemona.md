# Nemona

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Nemona** (Paldea (Kitakami e Blueberry) · Rivais e companheiros) — Campeã extremamente entusiasmada por batalhas e principal rival do jogador.
- **Nemona — nível Campeão** (Paldea (Kitakami e Blueberry) · Elite Four e Campeões) — já possui o título antes de iniciar uma nova jornada ao lado do jogador.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_NEMONA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_NEMONA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_NEMONA` | `graphics/object_events/pics/people/special/nemona.png` (boneco 20x22, quadro 32x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_NEMONA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Nemona/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_NEMONA` | `graphics/trainers/front_pics/nemona.png` (64x64) + `nemona_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_NEMONA` = **1203** (bloco 2, flag `0xB27`), luta genérica `Nexus_EventScript_Nemona_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_NEMONA ===
Name: Nemona
Class: Rival
Pic: Nemona
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Pawmot @ Focus Sash
Jolly Nature
Level: 100
Ability: Iron Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Double Shock
- Close Combat
- Revival Blessing

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

Walking Wake @ Choice Specs
Timid Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Steam
- Draco Meteor
- Flamethrower
- Flip Turn

Gallade @ Psychite
Jolly Nature
Level: 100
Ability: Sharpness
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sacred Sword
- Psycho Cut
- Leaf Blade
- Swords Dance

Goodra-Hisui @ Assault Vest
Modest Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Fire Blast
- Sludge Bomb
- Thunderbolt

Meowscarada @ Life Orb
Jolly Nature
Level: 100
Ability: Protean
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flower Trick
- Knock Off
- U-turn
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Koraidon** — `Nexus_EventScript_Nemona_Koraidon_ChampionFight` (falas `Nexus_Text_Nemona_Koraidon_Champion*`)
- **Walking Wake** — `Nexus_EventScript_Nemona_WalkingWake_ChampionFight` (falas `Nexus_Text_Nemona_WalkingWake_Champion*`)
- **Iron Valiant** — `Nexus_EventScript_Nemona_IronValiant_ChampionFight` (falas `Nexus_Text_Nemona_IronValiant_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Nemona_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> You! You've got that look! The one Trainers get when they're ready for a really good battle!
>
> I'm Nemona. Please tell me your team is ready, because mine absolutely is!

**Derrota**

> YES! That was incredible! I'm already thinking about our next battle!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
