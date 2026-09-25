# Lance

**Região da ficha:** Kanto

Aparece no checklist como:

- **Lance — Dragão** (Kanto · Elite Four e Campeões) — mestre de dragões que posteriormente se torna Campeão de Johto.
- **Lance — Campeão** (Johto · Elite Four e Campeão) — mestre de Pokémon Dragão e principal Campeão de Johto.

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
| `OBJ_EVENT_GFX_LANCE` | `graphics/object_events/pics/people/elite_four/lance.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_CHAMPION_LANCE` | `graphics/trainers/front_pics/champion_lance.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_LANCE` | `graphics/field_mugshots/lance.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LANCE_1` | 249 | 0x5F9 | Baxcalibur Lv70, Dragonite Lv71, Exeggutor-Alola Lv71, Hydrapple Lv71, Dragapult Lv71, Archaludon Lv71 · *dupla* · VS: Purple | `PokemonLeague_ChampionsRoom`, `src/battle_dome.c`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_LANCE_2` | 250 | 0x5FA | Salamence Lv69, Dragonite Lv68, Gyarados Lv69, Charizard Lv68, Aerodactyl Lv69, Altaria Lv70 · VS: Purple | `PokemonLeague_ChampionsRoom`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_LANCE` | 877 | 0x86D | Baxcalibur Lv85, Dragonite Lv86, Exeggutor-Alola Lv86, Hydrapple Lv86, Dragapult Lv86, Archaludon Lv86 · *dupla* · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_LANCE` (até Lv86).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
