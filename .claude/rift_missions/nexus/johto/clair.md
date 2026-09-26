# Clair

**Região da ficha:** Johto

Aparece no checklist como:

- **Clair — Dragão** (Johto · Líderes de Ginásio) — orgulhosa Líder de Blackthorn e prima de Lance.

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
| `OBJ_EVENT_GFX_CLAIR` | `graphics/object_events/pics/people/gym_leaders/clair.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_CLAIR` | `graphics/trainers/front_pics/leader_clair.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_CLAIR` | `graphics/field_mugshots/clair.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_CLAIR_1` | 541 | 0x71D | Goodra-Hisui Lv58, Gyarados Lv58, Dragonite Lv58, Altaria Lv58, Hydrapple Lv58, Kingdra Lv59 · *dupla* · VS: Green | `BlackthornCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_CLAIR_2` | 542 | 0x71E | Goodra Lv81, Kingdra Lv82, Haxorus Lv82, Noivern Lv83, Kommo-o Lv83, Charizard Lv84 · *dupla* | `DragonsDen_Cavern`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_CLAIR` | 898 | 0x882 | Goodra Lv85, Kingdra Lv85, Haxorus Lv85, Rayquaza Lv85, Kommo-o Lv85, Charizard Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_CLAIR` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
