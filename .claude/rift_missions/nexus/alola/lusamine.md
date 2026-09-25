# Lusamine

**Região da ficha:** Alola

Aparece no checklist como:

- **Lusamine** (Alola · Team Skull e Aether Foundation) — presidente da Aether Foundation obcecada pelas Ultra Beasts.

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
| `OBJ_EVENT_GFX_LUSAMINE` | `graphics/object_events/pics/people/special/lusamine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LUSAMINE` | `graphics/trainers/front_pics/lusamine.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem do arco das Rift Missions; `TRAINER_LUSAMINE_ALTAR` é o duelo do clímax (ALTAR_SUN_MOON).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LUSAMINE` | 964 | 0x8C4 | Clefable Lv70, Lilligant Lv70, Mismagius Lv71, Bewear Lv71, Milotic Lv72 | `SunMoonAltar` |
| `TRAINER_LUSAMINE_ALTAR` | 972 | 0x8CC | Clefable Lv78, Lilligant Lv78, Mismagius Lv79, Bewear Lv79, Milotic Lv79, Nihilego Lv80 | `SunMoonAltar` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_LUSAMINE_ALTAR` (até Lv80).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
