# Whitney

**Região da ficha:** Johto

Aparece no checklist como:

- **Whitney — Normal** (Johto · Líderes de Ginásio) — Líder de Goldenrod, famosa pelo poderoso Miltank.

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
| `OBJ_EVENT_GFX_WHITNEY` | `graphics/object_events/pics/people/gym_leaders/whitney.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_WHITNEY` | `graphics/trainers/front_pics/leader_whitney.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_WHITNEY` | `graphics/field_mugshots/whitney.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WHITNEY_1` | 604 | 0x75C | Maushold Lv27, Audino Lv27, Cinccino Lv27, Miltank Lv27 · *dupla* · VS: Yellow | `GoldenrodCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h`, `src/match_call.c` |
| `TRAINER_WHITNEY_2` | 607 | 0x75F | Ursaluna Lv78, Indeedee-F Lv77, Zoroark Hisui Lv77, Drampa Lv78, Maushold Lv77, Porygon-Z Lv78 · *dupla* | `GoldenrodCity_DepartmentStore_6F`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_WHITNEY` | 893 | 0x87D | Ursaluna Lv85, Regigigas Lv85, Zoroark Hisui Lv85, Drampa Lv85, Maushold Lv85, Porygon-Z Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_WHITNEY` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
