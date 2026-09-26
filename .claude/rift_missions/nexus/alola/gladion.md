# Gladion

**Região da ficha:** Alola

Aparece no checklist como:

- **Gladion** (Alola · Rivais) — rival sério que foge da Aether Foundation com Type: Null.
- **Gladion** (Alola · Team Skull e Aether Foundation) — enforcer temporário do Team Skull que possui Type: Null.

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
| `OBJ_EVENT_GFX_GLADION` | `graphics/object_events/pics/people/special/gladion.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_GLADION` | `graphics/trainers/front_pics/gladion.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem do arco das Rift Missions, com várias batalhas de história. `TRAINER_GLADION_POSTGAME` é o time mais forte já escrito.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_GLADION` | 967 | 0x8C7 | Grubbin Lv14, Sandile Lv14, Rockruff Lv14, Type: Null Lv15 | `VioletCity_PokemonCenter` |
| `TRAINER_GLADION_CIANWOOD` | 969 | 0x8C9 | Krookodile Lv43, Vikavolt Lv43, Lycanroc Midday Lv44, Type: Null Lv44 | `CianwoodCity` |
| `TRAINER_GLADION_VICTORY_ROAD` | 971 | 0x8CB | Silvally Lv65, Krookodile Lv64, Vikavolt Lv63, Lycanroc Midday Lv63, Zoroark Lv64, Gastrodon West Lv64 | `ReceptionGate` |
| `TRAINER_GLADION_POSTGAME` | 974 | 0x8CE | Lucario Lv78, Crobat Lv78, Weavile Lv79, Zoroark Lv79, Umbreon Lv79, Silvally Lv80 | `CianwoodCity` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_GLADION_POSTGAME` (até Lv80).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
