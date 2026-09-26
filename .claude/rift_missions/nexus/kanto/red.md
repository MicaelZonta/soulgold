# Red

**Região da ficha:** Kanto

Aparece no checklist como:

- **Red** (Kanto · Rivais e protagonistas) — protagonista original de Kanto e um dos treinadores mais fortes da franquia.
- **Red** (Johto · Outros notáveis) — superchefe silencioso encontrado no topo do Mt. Silver.
- **Red** (Alola · Outros notáveis) — veterano e chefe da Battle Tree.

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
| `OBJ_EVENT_GFX_RED` | `graphics/object_events/pics/people/red.png` |
| `OBJ_EVENT_GFX_RED_NORMAL` | `graphics/object_events/pics/people/red.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RED` | `graphics/trainers/front_pics/red.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_RED_1` | 230 | 0x5E6 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_RED_2` | 231 | 0x5E7 | Pikachu Lv93, Snorlax Lv75, Charizard Lv77, Venusaur Lv77, Blastoise Lv77, Espeon Lv80 | `src/battle_setup.c` |
| `TRAINER_RED` | 851 | 0x853 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_RED_2` (até Lv93).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
