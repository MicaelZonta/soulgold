# Steven Stone

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Steven Stone — Campeão** (Hoenn · Elite Four e Campeões) — colecionador de pedras raras e especialista em Pokémon de Aço.

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
| `OBJ_EVENT_GFX_STEVEN` | `graphics/object_events/pics/people/steven.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_STEVEN` | `graphics/trainers/front_pics/steven.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_STEVEN` | `graphics/field_mugshots/steven.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_STEVEN2` | 568 | 0x738 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_STEVEN` | 804 | 0x824 | Gholdengo Lv84, Aggron Lv85, Cradily Lv85, Excadrill Lv85, Archeops Lv85, Metagross Lv86 · *dupla* · VS: Purple | `Kitakami_Houses`, `MeteorFalls_StevensCave`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_STEVEN` | 878 | 0x86E | Gholdengo Lv84, Aggron Lv85, Cradily Lv85, Excadrill Lv85, Archeops Lv85, Metagross Lv86 · *dupla* · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_STEVEN` (até Lv86).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
