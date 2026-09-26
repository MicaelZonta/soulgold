# Bugsy

**Região da ficha:** Johto

Aparece no checklist como:

- **Bugsy — Inseto** (Johto · Líderes de Ginásio) — pesquisador de Pokémon Inseto e Líder de Azalea.

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
| `OBJ_EVENT_GFX_BUGSY` | `graphics/object_events/pics/people/gym_leaders/bugsy.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BUGSY` | `graphics/trainers/front_pics/leader_bugsy.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BUGSY` | `graphics/field_mugshots/bugsy.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BUGSY_1` | 596 | 0x754 | Scizor Lv20, Beedrill Lv20, Pinsir Lv20, Larvesta Lv20 · *dupla* · VS: Purple | `AzaleaTown_Gym`, `src/data/level_scaling_rules.h` |
| `TRAINER_BUGSY_2` | 697 | 0x7B9 | Kleavor Lv77, Ribombee Lv77, Centiskorch Lv77, Scizor Lv78, Volcarona Lv77, Golisopod Lv77 · *dupla* | `KitakamiRoad_House`, `NationalPark_Normal`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_BUGSY` | 892 | 0x87C | Kleavor Lv85, Ribombee Lv85, Centiskorch Lv85, Scizor Lv85, Volcarona Lv85, Genesect Lv85 | `src/title_defense.c` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_TITLE_DEFENSE_BUGSY` (até Lv85).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
