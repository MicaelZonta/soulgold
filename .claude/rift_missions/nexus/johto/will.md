# Will

**Região da ficha:** Johto

Aparece no checklist como:

- **Will — Psíquico** (Johto · Elite Four e Campeão) — ilusionista viajante que aperfeiçoou suas habilidades pelo mundo.

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
| `OBJ_EVENT_GFX_WILL` | `graphics/object_events/pics/people/elite_four/will.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_WILL` | `graphics/trainers/front_pics/elite_four_will.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_WILL` | `graphics/field_mugshots/will.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WILL_2` | 376 | 0x678 | Farigiraf Lv85, Reuniclus Lv85, Espeon Lv85, Slowbro Lv85, Braviary-Hisui Lv85, Alakazam Lv85 · VS: Purple | `PokemonLeague_WillsRoom`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_WILL_1` | 736 | 0x7E0 | Farigiraf Lv68, Reuniclus Lv69, Espeon Lv68, Slowbro Lv68, Braviary-Hisui Lv68, Alakazam Lv69 · *dupla* · VS: Purple | `PokemonLeague_WillsRoom` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_WILL_2` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
