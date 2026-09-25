# Lillie

**Região da ficha:** Alola

Aparece no checklist como:

- **Lillie** (Alola · Outros notáveis) — filha de Lusamine e protagonista do arco de Alola do hack.

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
| `OBJ_EVENT_GFX_LILLIE` | `graphics/object_events/pics/people/special/lillie.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LILLIE` | `graphics/trainers/front_pics/lillie.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem central do arco das Rift Missions; `TRAINER_LILLIE_POSTGAME` é o time mais forte já escrito.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LILLIE` | 965 | 0x8C5 | Vulpix Alola Lv7 | `Route30_MrPokemonsHouse` |
| `TRAINER_LILLIE_GOLDENROD` | 968 | 0x8C8 | Clefairy Lv28, Ribombee Lv29, Comfey Lv28, Vulpix Alola Lv29 | `GoldenrodCity_FlowerShop` |
| `TRAINER_LILLIE_DRAGONS_DEN` | 970 | 0x8CA | Ninetales Alola Lv62, Ribombee Lv59, Clefable Lv60, Lilligant Lv59, Milotic Lv61, Comfey Lv60 | `DragonsDen_Shrine` |
| `TRAINER_LILLIE_POSTGAME` | 973 | 0x8CD | Clefable Lv76, Comfey Lv76, Ribombee Lv77, Primarina Lv77, Togekiss Lv78, Ninetales Alola Lv78 | `CherrygroveCity` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_LILLIE_POSTGAME` (até Lv78).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
