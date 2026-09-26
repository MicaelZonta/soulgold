# Petrel

**Região da ficha:** Kanto

Aparece no checklist como:

- **Petrel** (Kanto · Team Rocket) — mestre dos disfarces responsável por imitar o Diretor da Radio Tower.
- **Petrel** (Johto · Team Rocket) — infiltra-se na Radio Tower usando disfarces.

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
| `OBJ_EVENT_GFX_PETREL` | `graphics/object_events/pics/people/rockets/petrel.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PETREL` | `graphics/trainers/front_pics/petrel.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_PETREL` | `graphics/field_mugshots/petrel.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PETREL_2` | 278 | 0x616 | Scrafty Lv49, Honchkrow Lv49, Persian Alola Lv49, Pyroar Lv51, Weezing Galar Lv50, Rotom-Wash Lv50 | `GoldenrodCity_RadioTower_5F` |
| `TRAINER_PETREL_1` | 467 | 0x6D3 | Scrafty Lv48, Persian Alola Lv48, Pyroar Lv49, Weezing Galar Lv48, Rotom-Wash Lv48 | `RocketHideout_B3F`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_PETREL_2` (até Lv51).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
