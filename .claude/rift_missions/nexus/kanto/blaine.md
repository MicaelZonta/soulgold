# Blaine

**Região da ficha:** Kanto

Aparece no checklist como:

- **Blaine — Fogo** (Kanto · Líderes de Ginásio) — cientista excêntrico e Líder de Cinnabar.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_BLAINE` | `graphics/object_events/pics/people/gym_leaders/blaine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BLAINE` | `graphics/trainers/front_pics/blaine.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BLAINE` | `graphics/field_mugshots/blaine.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BLAINE_OLIVINE` | 43 | 0x52B | Ninetales Lv60, Cinderace Lv60, Ceruledge Lv61, Magmortar Lv61, Volcarona Lv61, Emboar Lv62 | `OlivineCity_PortInside` |
| `TRAINER_BLAINE` | 306 | 0x632 | Rapidash Lv66, Magmortar Lv65, Houndoom Lv66, Torkoal Lv67, Camerupt Lv67 | `SaffronCity_FightingDojoVIP`, `SeafoamIslands_Gym`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_BLAINE` (até Lv67).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
