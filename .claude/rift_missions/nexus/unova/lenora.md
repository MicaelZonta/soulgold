# Lenora

**Região da ficha:** Unova

Aparece no checklist como:

- **Lenora — Normal** (Unova · Líderes de Ginásio) — arqueóloga, diretora de museu e Líder de Nacrene.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_LENORA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_LENORA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_LENORA` | `graphics/object_events/pics/people/special/lenora.png` (boneco 16x21, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_LENORA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Lenora/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LENORA` | `graphics/trainers/front_pics/lenora.png` (64x64) + `lenora_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — arte BW2 de `.filetransfer/.trainers/Lenora/Trainer - IA.png`, 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_LENORA` = **1194** (bloco 2, flag `0xB1E`), luta genérica `Nexus_EventScript_Lenora_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_LENORA ===
Name: Lenora
Class: Leader
Pic: Lenora
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Kangaskhan @ Normalite
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Sucker Punch
- Drain Punch
- Fake Out

Arceus @ Life Orb
Adamant Nature
Level: 100
Ability: Multitype
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Extreme Speed
- Swords Dance
- Shadow Claw
- Recover

Meloetta @ Throat Spray
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Focus Blast
- U-turn

Stoutland @ Leftovers
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Return
- Crunch
- Wild Charge
- Protect

Watchog @ Focus Sash
Jolly Nature
Level: 100
Ability: Illuminate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hypnosis
- Super Fang
- Knock Off
- Low Kick

Braviary @ Sharp Beak
Adamant Nature
Level: 100
Ability: Defiant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Close Combat
- Tailwind
- Rock Slide
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Arceus** — `Nexus_EventScript_Lenora_Arceus_ChampionFight` (falas `Nexus_Text_Lenora_Arceus_Champion*`)
- **Meloetta** — `Nexus_EventScript_Lenora_Meloetta_ChampionFight` (falas `Nexus_Text_Lenora_Meloetta_Champion*`)
- **Regirock** — `Nexus_EventScript_Lenora_Regirock_ChampionFight` (falas `Nexus_Text_Lenora_Regirock_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Lenora_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Lenora. At the museum, I piece together lives from what they leave behind.
>
> Battling is easier. You can ask your questions while the other side is still standing!

**Derrota**

> Now there's a story worth preserving. Well fought!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
