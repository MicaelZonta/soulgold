# Silver

**Região da ficha:** Johto

Aparece no checklist como:

- **Silver** (Johto · Rival) — filho de Giovanni; começa cruel e aprende gradualmente a respeitar seus Pokémon.

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
| `OBJ_EVENT_GFX_SILVER` | `graphics/object_events/pics/people/special/silver.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_SILVER` | `graphics/trainers/front_pics/silver.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_SILVER` | `graphics/field_mugshots/silver.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_RIVAL_TOTODILE_5` | 226 | 0x5E2 | Gengar Lv66, Kingambit Lv67, Staraptor Lv66, Victreebel Lv67, Feraligatr Lv67, Armarouge Lv66 · VS: Pink | `VictoryRoadKanto_1F`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_RIVAL_TOTODILE_6` | 228 | 0x5E4 | Ursaluna Bloodmoon Lv64, Crobat Lv64, Victreebel Lv64, Houndoom Lv64, Feraligatr Lv64, Tyranitar Lv64 · VS: Green | `MtMoon_Cave`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_7` | 229 | 0x5E5 | Ursaluna Bloodmoon Lv68, Crobat Lv68, Victreebel Lv68, Houndoom Lv68, Feraligatr Lv68, Tyranitar Lv68 · VS: Pink | `IndigoPlateau_PokemonCenter`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_1` | 251 | 0x5FB | Chikorita Lv5 · VS: Purple | `CherrygroveCity`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_2` | 252 | 0x5FC | Haunter Lv20, Pawniard Lv20, Pidgeotto Lv21, Bayleef Lv21 · VS: Yellow | `AzaleaTown`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_3` | 253 | 0x5FD | Floatzel Lv31, Pawniard Lv31, Staravia Lv32, Lampent Lv32, Bayleef Lv32 · VS: Blue | `BurnedTower_1F`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_3` | 326 | 0x646 | Haunter Lv31, Pawniard Lv31, Staravia Lv32, Weepinbell Lv31, Croconaw Lv33 · VS: Blue | `BurnedTower_1F` |
| `TRAINER_RIVAL_CYNDAQUIL_2` | 351 | 0x65F | Haunter Lv20, Pawniard Lv20, Pidgeotto Lv21, Quilava Lv22 · VS: Yellow | `AzaleaTown` |
| `TRAINER_RIVAL_TOTODILE_4` | 503 | 0x6F7 | Gengar Lv49, Bisharp Lv50, Staraptor Lv49, Victreebel Lv50, Feraligatr Lv51 · VS: Blue | `GoldenrodCity_UndergroundSwitches` |
| `TRAINER_RIVAL_CHIKORITA_4` | 552 | 0x728 | Floatzel Lv49, Bisharp Lv50, Staraptor Lv49, Chandelure Lv50, Meganium Lv51 · VS: Pink | `GoldenrodCity_UndergroundSwitches`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_RIVAL_CHIKORITA_5` | 555 | 0x72B | Floatzel Lv66, Kingambit Lv67, Staraptor Lv66, Chandelure Lv66, Meganium Lv67, Haxorus Lv66 · VS: Pink | `VictoryRoadKanto_1F`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_6` | 556 | 0x72C | Ursaluna Bloodmoon Lv64, Crobat Lv64, Houndoom Lv64, Meganium Lv64, Tyranitar Lv64 · VS: Green | `MtMoon_Cave`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_7` | 557 | 0x72D | Ursaluna Bloodmoon Lv68, Crobat Lv68, Houndoom Lv68, Meganium Lv68, Tyranitar Lv68 · VS: Pink | `IndigoPlateau_PokemonCenter`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_1` | 558 | 0x72E | Cyndaquil Lv5 · VS: Purple | `CherrygroveCity`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_1` | 605 | 0x75D | Totodile Lv5 · VS: Purple | `CherrygroveCity`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_4` | 621 | 0x76D | Gengar Lv49, Bisharp Lv50, Staraptor Lv49, Clodsire Lv50, Typhlosion Lv51 · VS: Blue | `GoldenrodCity_UndergroundSwitches`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_RIVAL_CYNDAQUIL_5` | 622 | 0x76E | Gengar Lv66, Kingambit Lv67, Staraptor Lv66, Clodsire Lv67, Typhlosion Lv67, Eelektross Lv66 · VS: Pink | `VictoryRoadKanto_1F`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_6` | 623 | 0x76F | Ursaluna Bloodmoon Lv64, Crobat Lv64, Victreebel Lv64, Typhlosion Lv64, Tyranitar Lv64 · VS: Green | `MtMoon_Cave`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_7` | 624 | 0x770 | Ursaluna Bloodmoon Lv68, Crobat Lv68, Victreebel Lv68, Typhlosion Lv68, Tyranitar Lv68 · VS: Pink | `IndigoPlateau_PokemonCenter`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_2` | 625 | 0x771 | Haunter Lv20, Pawniard Lv20, Pidgeotto Lv21, Croconaw Lv21 · VS: Yellow | `AzaleaTown` |
| `TRAINER_RIVAL_CYNDAQUIL_3` | 749 | 0x7ED | Haunter Lv30, Pawniard Lv30, Staravia Lv31, Clodsire Lv30, Quilava Lv32 · VS: Blue | `BurnedTower_1F` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_RIVAL_TOTODILE_7` (até Lv68).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
