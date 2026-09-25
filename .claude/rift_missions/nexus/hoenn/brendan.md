# Brendan

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brendan** (Hoenn · Rivais) — protagonista ou rival, filho do Professor Birch.

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
| `OBJ_EVENT_GFX_LINK_RS_BRENDAN` | `graphics/object_events/pics/people/ruby_sapphire_brendan/walking.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RS_BRENDAN` | `graphics/trainers/front_pics/brendan_rs.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** `OBJ_EVENT_GFX_BRENDAN_*` e `TRAINER_PIC_FRONT_BRENDAN` **não são o Brendan**: neste hack a arte foi trocada pelo protagonista **Gold** (os `TRAINER_RIVALGOLD*` usam essa pic). O Brendan de Hoenn de verdade é a arte de *Ruby/Sapphire* (`RS_`), listada acima. O overworld RS só tem andar/correr (sem bike/surf).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BRENDAN_PLACEHOLDER` | 853 | 0x855 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_401` (ex-`TRAINER_BRENDAN_ROUTE_119_MUDKIP`, 522), `TRAINER_UNUSED_407` (ex-`TRAINER_BRENDAN_ROUTE_103_TREECKO`, 523), `TRAINER_UNUSED_396` (ex-`TRAINER_BRENDAN_ROUTE_110_TREECKO`, 524), `TRAINER_UNUSED_402` (ex-`TRAINER_BRENDAN_ROUTE_119_TREECKO`, 525), `TRAINER_UNUSED_408` (ex-`TRAINER_BRENDAN_ROUTE_103_TORCHIC`, 526), `TRAINER_UNUSED_397` (ex-`TRAINER_BRENDAN_ROUTE_110_TORCHIC`, 527), `TRAINER_UNUSED_403` (ex-`TRAINER_BRENDAN_ROUTE_119_TORCHIC`, 528), `TRAINER_UNUSED_412` (ex-`TRAINER_BRENDAN_RUSTBORO_TREECKO`, 592), `TRAINER_UNUSED_413` (ex-`TRAINER_BRENDAN_RUSTBORO_MUDKIP`, 593), `TRAINER_UNUSED_414` (ex-`TRAINER_BRENDAN_RUSTBORO_TORCHIC`, 599), `TRAINER_UNUSED_418` (ex-`TRAINER_BRENDAN_LILYCOVE_MUDKIP`, 661), `TRAINER_UNUSED_419` (ex-`TRAINER_BRENDAN_LILYCOVE_TREECKO`, 662), `TRAINER_UNUSED_420` (ex-`TRAINER_BRENDAN_LILYCOVE_TORCHIC`, 663).

### Time das Rift Missions

_Não definido._

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
