# Archer

**Região da ficha:** Kanto

Aparece no checklist como:

- **Archer** (Kanto · Team Rocket) — executivo de alto escalão que tenta restaurar o Team Rocket.
- **Archer** (Johto · Team Rocket) — comanda a tentativa de trazer Giovanni de volta.

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
| `OBJ_EVENT_GFX_ARCHER` | `graphics/object_events/pics/people/rockets/archer.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ARCHER` | `graphics/trainers/front_pics/archer.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_ARCHER` | `graphics/field_mugshots/archer.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_ARCHER_1` | 273 | 0x611 | Weezing Lv39, Tauros Lv38, Houndoom Lv38 | `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_ARCHER_4` | 276 | 0x614 | Porygon Z Lv39, Tauros Lv38, Gyarados Lv39, Houndoom Lv38, Slowbro Lv40 | `src/battle_setup.c` |
| `TRAINER_ARCHER_5` | 277 | 0x615 | Porygon Z Lv39, Tauros Lv38, Gyarados Lv39, Houndoom Lv38, Slowbro Lv40 | `src/battle_setup.c` |
| `TRAINER_ARCHER` | 468 | 0x6D4 | Ninetales Lv54, Tauros Paldea Blaze Lv55, Marowak Alola Lv54, Rotom Heat Lv55, Slowking Galar Lv55, Houndoom Lv57 | `GoldenrodCity_RadioTower_5F`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_ARCHER` (até Lv57).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
