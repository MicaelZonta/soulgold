# Misty

**Região da ficha:** Kanto

Aparece no checklist como:

- **Misty — Água** (Kanto · Líderes de Ginásio) — Líder de Cerulean, treinadora veloz associada a Starmie.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [x] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_MISTY` | `graphics/object_events/pics/people/gym_leaders/misty.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_MISTY` | `graphics/trainers/front_pics/misty.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MISTY` | 544 | 0x720 | Quagsire Lv62, Vaporeon Lv61, Milotic Lv61, Lapras Lv62, Starmie Lv63 | `CeruleanCity_Gym`, `SaffronCity_FightingDojoVIP`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_MISTY` (até Lv63).

### Lendário associado

**Kyogre** — exemplo aprovado no design (`SOULGOLD_RIFT_MISSIONS_DESIGN.md` §10, "Estrutura do loop"). Aprovado só como associação; nada implementado.

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
