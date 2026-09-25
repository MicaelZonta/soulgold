# May

**Região da ficha:** Hoenn

Aparece no checklist como:

- **May** (Hoenn · Rivais) — protagonista ou rival, filha do Professor Birch.

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
| `OBJ_EVENT_GFX_LINK_RS_MAY` | `graphics/object_events/pics/people/ruby_sapphire_may/walking.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RS_MAY` | `graphics/trainers/front_pics/may_rs.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** `OBJ_EVENT_GFX_MAY_*` e `TRAINER_PIC_FRONT_MAY` **não são a May**: neste hack a arte foi trocada pela protagonista **Kris/Crystal** (os `TRAINER_RIVALCRYSTAL*` usam essa pic). A May de Hoenn de verdade é a arte de *Ruby/Sapphire* (`RS_`), listada acima. O overworld RS só tem andar/correr (sem bike/surf).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MAY_PLACEHOLDER` | 854 | 0x856 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_409` (ex-`TRAINER_MAY_ROUTE_103_MUDKIP`, 529), `TRAINER_UNUSED_398` (ex-`TRAINER_MAY_ROUTE_110_MUDKIP`, 530), `TRAINER_UNUSED_404` (ex-`TRAINER_MAY_ROUTE_119_MUDKIP`, 531), `TRAINER_UNUSED_410` (ex-`TRAINER_MAY_ROUTE_103_TREECKO`, 532), `TRAINER_UNUSED_399` (ex-`TRAINER_MAY_ROUTE_110_TREECKO`, 533), `TRAINER_UNUSED_405` (ex-`TRAINER_MAY_ROUTE_119_TREECKO`, 534), `TRAINER_UNUSED_411` (ex-`TRAINER_MAY_ROUTE_103_TORCHIC`, 535), `TRAINER_UNUSED_400` (ex-`TRAINER_MAY_ROUTE_110_TORCHIC`, 536), `TRAINER_UNUSED_406` (ex-`TRAINER_MAY_ROUTE_119_TORCHIC`, 537), `TRAINER_UNUSED_415` (ex-`TRAINER_MAY_RUSTBORO_MUDKIP`, 600), `TRAINER_UNUSED_421` (ex-`TRAINER_MAY_LILYCOVE_MUDKIP`, 664), `TRAINER_UNUSED_422` (ex-`TRAINER_MAY_LILYCOVE_TREECKO`, 665), `TRAINER_UNUSED_423` (ex-`TRAINER_MAY_LILYCOVE_TORCHIC`, 666), `TRAINER_UNUSED_416` (ex-`TRAINER_MAY_RUSTBORO_TREECKO`, 768), `TRAINER_UNUSED_417` (ex-`TRAINER_MAY_RUSTBORO_TORCHIC`, 769).

### Time das Rift Missions

_Não definido._

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
