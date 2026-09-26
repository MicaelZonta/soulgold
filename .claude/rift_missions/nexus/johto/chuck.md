# Chuck

**Região da ficha:** Johto

Aparece no checklist como:

- **Chuck — Lutador** (Johto · Líderes de Ginásio) — Líder de Cianwood dedicado ao treinamento físico.

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
| `OBJ_EVENT_GFX_CHUCK` | `graphics/object_events/pics/people/gym_leaders/chuck.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_CHUCK` | `graphics/trainers/front_pics/leader_chuck.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_CHUCK` | `graphics/field_mugshots/chuck.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_CHUCK_2` | 402 | 0x692 | Mienshao Lv78, Annihilape Lv78, Lilligant Hisui Lv77, Pawmot Lv78, Hawlucha Lv79, Poliwrath Lv78 · *dupla* | `KitakamiRoad_House`, `Route47`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_CHUCK_1_2` | 442 | 0x6BA | Hitmontop Lv45, Sirfetch'd Lv45, Mienshao Lv45, Poliwrath Lv45, Falinks Lv46 · *dupla* · VS: Pink | `CianwoodGym` |
| `TRAINER_CHUCK_1` | 510 | 0x6FE | Hitmontop Lv42, Annihilape Lv42, Mienshao Lv42, Poliwrath Lv42, Falinks Lv42 · *dupla* · VS: Pink | `CianwoodGym`, `src/data/level_scaling_rules.h` |
| `TRAINER_CHUCK_1_3` | 538 | 0x71A | Hitmontop Lv48, Sirfetch'd Lv48, Mienshao Lv48, Poliwrath Lv48, Falinks Lv49 · *dupla* · VS: Pink | `CianwoodGym`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_TITLE_DEFENSE_CHUCK` | 895 | 0x87F | Mienshao Lv85, Annihilape Lv85, Lilligant Hisui Lv85, Pawmot Lv85, Hawlucha Lv85, Zamazenta Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_CHUCK` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
