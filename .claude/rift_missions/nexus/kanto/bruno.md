# Bruno

**Região da ficha:** Kanto

Aparece no checklist como:

- **Bruno — Lutador** (Kanto · Elite Four e Campeões) — artista marcial que usa Pokémon Lutadores e resistentes.
- **Bruno — Lutador** (Johto · Elite Four e Campeão) — veterano que permanece na Elite Four entre as duas gerações.

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
| `OBJ_EVENT_GFX_BRUNO` | `graphics/object_events/pics/people/elite_four/bruno.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_BRUNO` | `graphics/trainers/front_pics/elite_four_bruno.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BRUNO` | `graphics/field_mugshots/bruno.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BRUNO_1` | 379 | 0x67B | Hitmontop Lv69, Staraptor Lv69, Gallade Lv69, Annihilape Lv70, Kommo O Lv70, Machamp Lv70 · *dupla* · VS: Yellow | `PokemonLeague_BrunosRoom`, `src/battle_setup.c` |
| `TRAINER_BRUNO_2` | 380 | 0x67C | Hitmontop Lv85, Staraptor Lv85, Gallade Lv85, Annihilape Lv85, Kommo O Lv85, Machamp Lv85 | `PokemonLeague_BrunosRoom`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_BRUNO_2` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
