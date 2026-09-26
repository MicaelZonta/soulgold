# Eusine

**Região da ficha:** Johto

Aparece no checklist como:

- **Eusine** (Johto · Outros notáveis) — pesquisador e treinador obcecado em encontrar Suicune.

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
| `OBJ_EVENT_GFX_EUSINE` | `graphics/object_events/pics/people/special/eusine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_EUSINE` | `graphics/trainers/front_pics/eusine.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_EUSINE` | `graphics/field_mugshots/eusine.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_EUSINE` | 560 | 0x730 | Golisopod Lv38, Wobbuffet Lv38, Magnezone Lv39 | `CianwoodCity` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_EUSINE` (até Lv39).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
