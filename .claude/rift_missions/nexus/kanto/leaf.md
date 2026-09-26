# Leaf

**Região da ficha:** Kanto

Aparece no checklist como:

- **Leaf** (Kanto · Rivais e protagonistas) — protagonista feminina de *FireRed/LeafGreen*; no hack batalha como "Green" (pós-jogo).

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
| `OBJ_EVENT_GFX_LEAF` | `graphics/object_events/pics/people/leaf.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEAF` | `graphics/trainers/front_pics/leaf.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_LEAF` | `graphics/field_mugshots/leaf.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LEAF` | 852 | 0x854 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_NAMELESS_LEAF` | 899 | 0x883 | Chansey Lv85, Volcarona Lv86, Thundurus-Therian Lv85, Tapu Fini Lv86, Dragapult Lv86, Venusaur Lv87 | `CeruleanCave_B2F` |
| `TRAINER_TITLE_DEFENSE_LEAF` | 950 | 0x8B6 | Chansey Lv85, Volcarona Lv86, Thundurus-Therian Lv85, Tapu Fini Lv86, Dragapult Lv86, Venusaur Lv87 · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_NAMELESS_LEAF` (até Lv87).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
