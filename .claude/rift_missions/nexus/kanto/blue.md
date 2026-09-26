# Blue/Green

**Região da ficha:** Kanto

Aparece no checklist como:

- **Blue/Green** (Kanto · Rivais e protagonistas) — rival de Red, primeiro Campeão enfrentado pelo jogador e futuro Líder de Viridian.
- **Blue — Campeão** (Kanto · Elite Four e Campeões) — conquista o título pouco antes da chegada de Red.
- **Blue** (Alola · Outros notáveis) — veterano, chefe da Battle Tree e antigo Campeão.

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
| `OBJ_EVENT_GFX_BLUE` | `graphics/object_events/pics/people/gym_leaders/blue.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BLUE` | `graphics/trainers/front_pics/leader_blue.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BLUE` | 595 | 0x753 | Rhyperior Lv69, Pidgeot Lv68, Machamp Lv67, Exeggutor Lv68, Tyranitar Lv68, Arcanine Lv69 | `SaffronCity_FightingDojoVIP`, `ViridianCity_Gym`, `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_386` (ex-`TRAINER_BLUE_2`, 282).

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_BLUE` (até Lv69).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
