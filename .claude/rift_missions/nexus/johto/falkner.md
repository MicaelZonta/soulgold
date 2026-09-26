# Falkner

**Região da ficha:** Johto

Aparece no checklist como:

- **Falkner — Voador** (Johto · Líderes de Ginásio) — jovem Líder de Violet que herdou os Pokémon de seu pai.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_FALKNER` | `graphics/object_events/pics/people/gym_leaders/falkner.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_FALKNER` | `graphics/trainers/front_pics/leader_falkner.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_FALKNER` | `graphics/field_mugshots/falkner.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_FALKNER_1` | 19 | 0x513 | Rufflet Lv12, Noibat Lv12, Gligar Lv13, Pidgeotto Lv13 · *dupla* · VS: Blue | `VioletCity_Gym`, `src/data/level_scaling_rules.h` |
| `TRAINER_FALKNER_2` | 26 | 0x51A | Salamence Lv78, Flamigo Lv78, Braviary Lv78, Corviknight Lv78, Honchkrow Lv78, Gliscor Lv78 · *dupla* | `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `VioletCity_TrainerSchool`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_FALKNER` | 891 | 0x87B | Salamence Lv85, Flamigo Lv85, Landorus Therian Lv85, Corviknight Lv85, Honchkrow Lv85, Gliscor Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_FALKNER` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
