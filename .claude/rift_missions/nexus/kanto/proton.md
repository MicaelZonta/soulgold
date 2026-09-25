# Proton

**Região da ficha:** Kanto

Aparece no checklist como:

- **Proton** (Kanto · Team Rocket) — executivo conhecido por sua crueldade e pelas operações no Slowpoke Well.
- **Proton** (Johto · Team Rocket) — lidera ataques contra Slowpoke e outras ações violentas.

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
| `OBJ_EVENT_GFX_PROTON` | `graphics/object_events/pics/people/rockets/proton.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PROTON` | `graphics/trainers/front_pics/proton.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_PROTON` | `graphics/field_mugshots/proton.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PROTON_2` | 279 | 0x617 | Crobat Lv52, Farigiraf Lv52, Cacturne Lv52, Porygon Z Lv53, Nidoking Lv52, Scrafty Lv53 | `GoldenrodCity_RadioTower_4F`, `src/battle_setup.c` |
| `TRAINER_PROTON_1` | 862 | 0x85E | Nosepass Lv17, Houndour Lv17, Porygon Lv18 | `SlowpokeWell_B1F`, `src/battle_setup.c`, `src/match_call.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_PROTON_2` (até Lv53).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
