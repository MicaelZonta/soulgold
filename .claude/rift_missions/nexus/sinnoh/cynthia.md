# Cynthia

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Cynthia — Campeã** (Sinnoh · Elite Four e Campeã) — arqueóloga, pesquisadora de mitos e uma das Campeãs mais poderosas.
- **Cynthia** (Unova · Outros notáveis) — Campeã visitante que pode ser desafiada em Undella Town.

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
| `OBJ_EVENT_GFX_CYNTHIA` | `graphics/object_events/pics/people/special/cynthia.png` (32x32, 9 quadros; a folha de origem não tem o lado direito). Arte oficial (Pokémon Platinum) |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_CYNTHIA` | `graphics/trainers/front_pics/cynthia_front_pic.png` (64x64) + `cynthia_large.png` (80x80, só na batalha). Arte oficial (Pokémon Platinum) |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).


### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

_Não definido._

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
