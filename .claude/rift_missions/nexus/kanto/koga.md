# Koga

**Região da ficha:** Kanto

Aparece no checklist como:

- **Koga — Veneno** (Kanto · Líderes de Ginásio) — ninja de Fuchsia que posteriormente entra para a Elite Four.
- **Koga — Veneno** (Johto · Elite Four e Campeão) — antigo Líder de Fuchsia promovido à Elite Four.

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
| `OBJ_EVENT_GFX_KOGA` | `graphics/object_events/pics/people/elite_four/koga.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_KOGA` | `graphics/trainers/front_pics/elite_four_koga.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_KOGA` | `graphics/field_mugshots/koga.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_KOGA_2` | 204 | 0x5CC | Toxapex Lv85, Overqwil Lv85, Roserade Lv85, Muk Alola Lv85, Scolipede Lv85, Crobat Lv85 · VS: Pink | `PokemonLeague_KogasRoom` |
| `TRAINER_KOGA_1` | 383 | 0x67F | Toxapex Lv68, Overqwil Lv69, Roserade Lv68, Muk Alola Lv68, Scolipede Lv69, Crobat Lv69 · *dupla* · VS: Pink | `PokemonLeague_KogasRoom` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_KOGA_2` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
