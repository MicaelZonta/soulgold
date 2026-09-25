# Sabrina

**Região da ficha:** Kanto

Aparece no checklist como:

- **Sabrina — Psíquico** (Kanto · Líderes de Ginásio) — poderosa médium e Líder de Saffron.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_SABRINA` | `graphics/object_events/pics/people/gym_leaders/sabrina.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_SABRINA` | `graphics/trainers/front_pics/sabrina.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_SABRINA` | 304 | 0x630 | Mr Mime Lv65, Indeedee Lv64, Slowbro Lv64, Wobbuffet Lv64, Espeon Lv65, Alakazam Lv66 | `SaffronCity_FightingDojoVIP`, `SaffronCity_Gym`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_SABRINA` (até Lv66).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
