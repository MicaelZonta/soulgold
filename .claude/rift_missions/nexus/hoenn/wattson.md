# Wattson

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Wattson — Elétrico** (Hoenn · Líderes de Ginásio) — inventor alegre responsável pelo Ginásio de Mauville.

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
| `OBJ_EVENT_GFX_WATTSON` | `graphics/object_events/pics/people/gym_leaders/wattson.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_WATTSON` | `graphics/trainers/front_pics/leader_wattson.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WATTSON_4` | 780 | 0x80C | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WATTSON_5` | 781 | 0x80D | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_453` (ex-`TRAINER_WATTSON_1`, 267).

### Time das Rift Missions

_Não definido._

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
