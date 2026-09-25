# Pryce

**Região da ficha:** Johto

Aparece no checklist como:

- **Pryce — Gelo** (Johto · Líderes de Ginásio) — treinador veterano e experiente de Mahogany.

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
| `OBJ_EVENT_GFX_PRYCE` | `graphics/object_events/pics/people/gym_leaders/pryce.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_PRYCE` | `graphics/trainers/front_pics/leader_pryce.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_PRYCE` | `graphics/field_mugshots/pryce.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PRYCE_2` | 244 | 0x5F4 | Ninetales-Alola Lv79, Lapras Lv81, Cloyster Lv80, Weavile Lv80, Darmanitan-Galar Lv80, Baxcalibur Lv81 · *dupla* | `KitakamiRoad_House`, `LakeOfRage`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_PRYCE_1` | 546 | 0x722 | Ninetales-Alola Lv42, Darmanitan-Galar Lv42, Mamoswine Lv42, Glaceon Lv42, Weavile Lv42, Froslass Lv42 · *dupla* · VS: Green | `MahoganyTown_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_PRYCE_1_2` | 578 | 0x742 | Darmanitan-Galar Lv45, Ninetales-Alola Lv45, Mamoswine Lv45, Glaceon Lv45, Weavile Lv45, Froslass Lv46 · *dupla* · VS: Green | `MahoganyTown_Gym` |
| `TRAINER_PRYCE_1_3` | 707 | 0x7C3 | Darmanitan-Galar Lv48, Ninetales-Alola Lv48, Mamoswine Lv48, Glaceon Lv48, Weavile Lv48, Froslass Lv49 · *dupla* · VS: Green | `MahoganyTown_Gym` |
| `TRAINER_TITLE_DEFENSE_PRYCE` | 897 | 0x881 | Ninetales-Alola Lv85, Lapras Lv85, Cloyster Lv85, Kyurem Lv85, Darmanitan-Galar Lv85, Baxcalibur Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_PRYCE` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
