# Giovanni

**Região da ficha:** Kanto

Aparece no checklist como:

- **Giovanni — Terra** (Kanto · Líderes de Ginásio) — Líder de Viridian e chefe do Team Rocket.
- **Giovanni** (Kanto · Team Rocket) — líder do sindicato criminoso que explora Pokémon em busca de poder e lucro.

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
| `OBJ_EVENT_GFX_GIOVANNI` | `graphics/object_events/pics/people/rockets/giovanni.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_GIOVANNI` | `graphics/trainers/front_pics/giovanni.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_GIOVANNI` | 95 | 0x55F | Kangaskhan Lv60, Honchkrow Lv61, Nidoqueen Lv61, Persian Lv61, Ursaluna Lv60, Nidoking Lv62 | `src/battle_dome.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_GIOVANNI` (até Lv62).

### Lendário associado

**Mewtwo** ou **Genesect** — exemplo aprovado no design (`SOULGOLD_RIFT_MISSIONS_DESIGN.md` §10, "Estrutura do loop": "Giovanni podendo anteceder Mewtwo ou Genesect"). Aprovado só como associação; nada implementado.

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
