# Ariana

**Região da ficha:** Kanto

Aparece no checklist como:

- **Ariana** (Kanto · Team Rocket) — executiva habilidosa e uma das figuras centrais da organização após Giovanni.
- **Ariana** (Johto · Team Rocket) — supervisiona operações importantes, incluindo a base de Mahogany.

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
| `OBJ_EVENT_GFX_ARIANA` | `graphics/object_events/pics/people/rockets/ariana.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ARIANA` | `graphics/trainers/front_pics/ariana.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_ARIANA` | `graphics/field_mugshots/ariana.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_ARIANA_1` | 127 | 0x57F | Arbok Lv48, Vileplume Lv48, Dragalge Lv49 | `RocketHideout_B2F`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_ARIANA_2` | 132 | 0x584 | Arbok Lv52, Toxapex Lv53, Vileplume Lv54, Roserade Lv54, Trevenant Lv53, Dragalge Lv54 | `GoldenrodCity_RadioTower_5F`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_ARIANA_2` (até Lv54).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
