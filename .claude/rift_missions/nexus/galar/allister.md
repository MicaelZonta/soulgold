# Allister

**Região da ficha:** Galar

Aparece no checklist como:

- **Allister — Fantasma** (Galar · Líderes de Ginásio) — Líder exclusivo de *Shield*, tímido e sempre mascarado.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_ALISTER`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_ALLISTER` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_ALISTER` | `graphics/object_events/pics/people/special/alister.png` (boneco 16x22, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_ALISTER`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Alister/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ALLISTER` | `graphics/trainers/front_pics/allister.png` (64x64) + `allister_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_ALLISTER` = **1167** (bloco 2, flag `0xB03`), luta genérica `Nexus_EventScript_Allister_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_ALLISTER ===
Name: Allister
Class: Leader
Pic: Allister
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Mimikyu @ Mental Herb
Jolly Nature
Level: 100
Ability: Disguise
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Play Rough
- Shadow Sneak
- Thunder Wave
- Swords Dance

Lunala @ Leftovers
Timid Nature
Level: 100
Ability: Shadow Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moongeist Beam
- Psyshock
- Moonblast
- Calm Mind

Spectrier @ Life Orb
Timid Nature
Level: 100
Ability: Grim Neigh
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Dark Pulse
- Nasty Plot
- Protect

Gengar @ Ghostite
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Sludge Bomb
- Focus Blast
- Protect

Cursola @ Power Herb
Quiet Nature
Level: 100
Ability: Perish Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Meteor Beam
- Shadow Ball
- Earth Power
- Protect

Dusknoir @ Sitrus Berry
Brave Nature
Level: 100
Ability: Frisk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poltergeist
- Icy Wind
- Shadow Sneak
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Lunala** — `Nexus_EventScript_Allister_Lunala_ChampionFight` (falas `Nexus_Text_Allister_Lunala_Champion*`)
- **Spectrier** — `Nexus_EventScript_Allister_Spectrier_ChampionFight` (falas `Nexus_Text_Allister_Spectrier_Champion*`)
- **Marshadow** — `Nexus_EventScript_Allister_Marshadow_ChampionFight` (falas `Nexus_Text_Allister_Marshadow_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Allister_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Um... you can look at my mask. Please don't ask me to take it off.
>
> My friends are less shy than I am. They'll do the introductions.

**Derrota**

> Oh... they like you. I think I do, too.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
