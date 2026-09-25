# Jasmine

**Região da ficha:** Johto

Aparece no checklist como:

- **Jasmine — Aço** (Johto · Líderes de Ginásio) — gentil Líder de Olivine e cuidadora do Ampharos do farol.

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
| `OBJ_EVENT_GFX_JASMINE` | `graphics/object_events/pics/people/gym_leaders/jasmine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_JASMINE` | `graphics/trainers/front_pics/leader_jasmine.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_JASMINE` | `graphics/field_mugshots/jasmine.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_JASMINE_1_3` | 180 | 0x5B4 | Corviknight Lv48, Tinkaton Lv49, Magnezone Lv48, Scizor Lv49, Steelix Lv49 · *dupla* · VS: Blue | `OlivineCity_Gym` |
| `TRAINER_JASMINE` | 359 | 0x667 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_JASMINE_2` | 427 | 0x6AB | Corviknight Lv78, Magnezone Lv78, Metagross Lv78, Steelix Lv78, Archaludon Lv79, Lucario Lv80 · *dupla* | `KitakamiRoad_House`, `OlivineCity_Cafe`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_JASMINE_1` | 513 | 0x701 | Corviknight Lv42, Tinkaton Lv42, Magnezone Lv42, Scizor Lv42, Steelix Lv42 · *dupla* · VS: Blue | `OlivineCity_Gym` |
| `TRAINER_JASMINE_1_2` | 651 | 0x78B | Corviknight Lv45, Tinkaton Lv45, Magnezone Lv45, Scizor Lv45, Steelix Lv45 · *dupla* · VS: Blue | `OlivineCity_Gym` |
| `TRAINER_TITLE_DEFENSE_JASMINE` | 896 | 0x880 | Skarmory Lv85, Magnezone Lv85, Metagross Lv85, Dialga Lv85, Archaludon Lv85, Lucario Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_JASMINE` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
