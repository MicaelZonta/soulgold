# Morty

**Região da ficha:** Johto

Aparece no checklist como:

- **Morty — Fantasma** (Johto · Líderes de Ginásio) — místico de Ecruteak que busca encontrar Pokémon lendários.

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
| `OBJ_EVENT_GFX_MORTY` | `graphics/object_events/pics/people/gym_leaders/morty.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_MORTY` | `graphics/trainers/front_pics/leader_morty.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_MORTY` | `graphics/field_mugshots/morty.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MORTY_1` | 608 | 0x760 | Mimikyu Lv34, Misdreavus Lv34, Shedinja Lv34, Doublade Lv34, Gengar Lv34 · *dupla* · VS: Purple | `EcruteakCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_MORTY_2` | 609 | 0x761 | Aegislash Lv78, Dragapult Lv78, Gengar Lv78, Mismagius Lv77, Basculegion Lv77, Cofagrigus Lv78 · *dupla* | `BellchimeTrail`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_MORTY` | 894 | 0x87E | Aegislash Lv85, Dragapult Lv85, Gengar Lv85, Mismagius Lv85, Basculegion Lv85, Giratina Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_MORTY` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
