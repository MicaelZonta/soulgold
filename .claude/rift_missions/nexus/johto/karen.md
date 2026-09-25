# Karen

**Região da ficha:** Johto

Aparece no checklist como:

- **Karen — Noturno** (Johto · Elite Four e Campeão) — defensora da ideia de vencer usando os Pokémon de que se gosta.

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
| `OBJ_EVENT_GFX_KAREN` | `graphics/object_events/pics/people/elite_four/karen.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_KAREN` | `graphics/trainers/front_pics/elite_four_karen.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_KAREN` | `graphics/field_mugshots/karen.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_KAREN_3` | 283 | 0x61B | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_KAREN_4` | 284 | 0x61C | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_KAREN_5` | 285 | 0x61D | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_KAREN_1` | 381 | 0x67D | Grimmsnarl Lv70, Absol Lv71, Umbreon Lv70, Kingambit Lv70, Scrafty Lv70, Honchkrow Lv70 · *dupla* · VS: Blue | `PokemonLeague_KarensRoom`, `Route116`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_KAREN_2` | 382 | 0x67E | Grimmsnarl Lv85, Absol Lv85, Umbreon Lv85, Kingambit Lv85, Scrafty Lv85, Honchkrow Lv85 · VS: Blue | `PokemonLeague_KarensRoom`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_KAREN_2` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
