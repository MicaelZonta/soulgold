# Pokémon Desabilitados — Auditoria de Innates e Plano de Distribuição

> Continuação de [POKEMON_AVAILABILITY_AUDIT.md](POKEMON_AVAILABILITY_AUDIT.md).
> Branch `master`, commit `692c07cd71643e970f4206fbc9099004579323b7`, análise de 2026-09-05.
> Nenhum arquivo de código-fonte foi modificado.

**Anexos**
* [`POKEMON_DISABLED_SPECIES.csv`](POKEMON_DISABLED_SPECIES.csv) — 539 entradas desabilitadas (323 espécies-base + 216 formas)
* [`POKEMON_DISABLED_FAMILIES.csv`](POKEMON_DISABLED_FAMILIES.csv) — 181 famílias `P_FAMILY_* = FALSE`

---

## 1. Resumo executivo

| | Valor |
|---|---|
| Famílias desabilitadas (`P_FAMILY_* = FALSE`) | **181** de 539 |
| Espécies-base desabilitadas | **323** |
| Formas desabilitadas | **216** |
| Espécies-base desabilitadas **com innates completos** | **234** (134 famílias) |
| Espécies-base desabilitadas **sem innates** | **89** (47 famílias) |
| Desabilitadas que são **lendárias/míticas** | **0 míticos, 0 lendários restritos** |
| Desabilitadas **sublendárias** | **5** (Type: Null, Wo-Chien, Ting-Lu, Okidogi, Munkidori) |
| Desabilitadas **Ultra Beast** | **9** |
| Desabilitadas **comuns** | **309** |
| Famílias desabilitadas que **já têm conteúdo alcançável no jogo** | **13** ⚠️ |

### Três descobertas centrais

**1. A correlação innates ⇄ habilitação é quase perfeita.**
Na faixa da Gen 5 (dex 494‑649), 112 de 113 espécies **habilitadas** têm innates,
contra apenas 2 de 78 **desabilitadas**. As famílias não foram desligadas por espaço de ROM ou por
decisão de design de conteúdo — foram desligadas **porque o trabalho de innates parou pela metade**.
Gen 5 e Gen 6 são exatamente as duas gerações onde isso aconteceu.

| Geração | Desabilitadas COM innates | Desabilitadas SEM innates |
|---|---|---|
| 1 | 19 | 0 |
| 2 | 17 | 0 |
| 3 | 51 | 0 |
| 4 | 24 | 1 |
| 5 | 2 | **69** |
| 6 | 0 | **18** |
| 7 | 41 | 1 |
| 8 | 40 | 0 |
| 9 | 40 | 0 |
| **Total** | **234** | **89** |

Consequência prática: **234 espécies (134 famílias) estão prontas para entrar no jogo hoje** —
têm base stats, tipos, learnsets, sprites, paletas, ícones, cries, descrições **e innates**.
O único trabalho restante é ligar a flag e distribuir.

**2. Treze famílias desabilitadas já são entregues/sorteadas por conteúdo alcançável.**
Isso é um bug ativo: o jogador recebe uma espécie cuja `gSpeciesInfo` não é compilada
(struct zerada — sem nome, sem sprite, sem learnset).

| Família | Como o jogo já a entrega | Evidência |
|---|---|---|
| **SPEAROW** | Presente “**KENYA**” (Spearow) do Randy no portão Goldenrod↔Route 35 | `src/scrcmd.c:3498` `species = SPECIES_SPEAROW`; `data/maps/Gate_GoldenrodCity_Route35/scripts.inc:36` |
| **SHUCKLE** | Presente “**SHUCKIE**” (Shuckle) do Kirk em Cianwood | `src/scrcmd.c` (`givenamedmon 2`); `data/maps/CianwoodHouse3/scripts.inc:30` |
| **OMANYTE** | Revivificação do **Helix Fossil** no laboratório das Ruins of Alph | `data/maps/RuinsOfAlph_Lab/scripts.inc:538` |
| **ANORITH** | Revivificação do **Claw Fossil** no mesmo laboratório | `data/maps/RuinsOfAlph_Lab/scripts.inc:448` |
| **SPINDA** | Presente do Gramps na casa do Bill (Route 25) | `data/maps/Route25_BillsHouse/scripts.inc:144` |
| **CASTFORM** | Pool do gacha + presente | `src/game_corner_gacha.c` |
| **LOTAD** (Lotad/Lombre/Ludicolo) | Pool do gacha + presente Bill's House | `src/game_corner_gacha.c`; `Route25_BillsHouse/scripts.inc:146` |
| **SEEDOT** (Seedot/Nuzleaf/Shiftry) | Pool do gacha | `src/game_corner_gacha.c` |
| **SENTRET** (Sentret/Furret) | Pool do gacha | `src/game_corner_gacha.c` |
| **REMORAID** (Remoraid/Octillery) | Pool do gacha | `src/game_corner_gacha.c` |
| **CLAMPERL** (Clamperl/Huntail/Gorebyss) | Pool do gacha | `src/game_corner_gacha.c` |
| **RELICANTH** | Pool do gacha | `src/game_corner_gacha.c` |
| **KECLEON** | `data/scripts/kecleon.inc:74` — script global, mas só chamado de mapas de Hoenn inalcançáveis | precisa de novo posicionamento |

**Todas as 13 têm innates completos.** Ligar as flags resolve o bug e adiciona 24 espécies —
12 delas ficam obteníveis no mesmo instante, sem escrever uma linha de conteúdo.

**3. Três conjuntos temáticos estão pela metade.**

| Conjunto | Já no jogo | Faltando (desabilitado) |
|---|---|---|
| **Tesouros da Ruína** | Chien-Pao (boss, Ice Path Depths 2), Chi-Yu (pesca no Battle Café) | **Wo-Chien**, **Ting-Lu** |
| **Os Três Leais** | Fezandipiti (estático, Kitakami Well B1F) | **Okidogi**, **Munkidori** |
| **Ultra Beasts** | Poipole/Naganadel (presente, Route 40 House 4) | **9 UBs** (Nihilego, Buzzwole, Pheromosa, Xurkitree, Celesteela, Kartana, Guzzlord, Stakataka, Blacephalon) |
| **Paradox** | **20/20 completos e obteníveis** ✅ | — |

Os Paradox mostram que o time já sabe fazer isso bem (Meteor Cave 1 = Ancient, Meteor Cave 2 = Future).
Fechar os outros três conjuntos custa 15 espécies e ~13 scripts.

---

## 2. Auditoria de innates

### 2.1 Como o sistema funciona

```c
// include/constants/global.h:132,137
#define MAX_MON_INNATES_INTERNAL 3   // máximo na definição da espécie
#define MAX_MON_INNATES          3   // máximo habilitado em gameplay
```
```c
// src/data/pokemon/species_info/gen_1_families.h:25,99,180
[SPECIES_BULBASAUR] .innates = { ABILITY_SEED_SOWER },
[SPECIES_IVYSAUR]   .innates = { ABILITY_SEED_SOWER, ABILITY_LEAF_GUARD },
[SPECIES_VENUSAUR]  .innates = { ABILITY_SEED_SOWER, ABILITY_LEAF_GUARD, ABILITY_CHANNEL_EARTH },
```
Lido em `GetSpeciesInnate` (`src/pokemon.c:7793`) e copiado para o battle mon em
`src/pokemon.c:3419`. A convenção do projeto é **1 innate por estágio evolutivo**
(básico = 1, meio = 2, final = 3), o que corresponde ao “aprender múltiplas habilidades no pós-game”
descrito no README.

### 2.2 Cobertura

| Escopo | Com innates | Sem innates |
|---|---|---|
| Todas as 1577 entradas | 1239 | 338 |
| Entradas **habilitadas** (1038) | **1038** | **0** |
| Espécies-base habilitadas (702) | **702** | **0** |
| Espécies-base desabilitadas (323) | 234 | 89 |

**Nenhuma espécie habilitada está sem innates.** As 7 espécies-base habilitadas que parecem
não ter o campo (`SPECIES_UNOWN`, `SPECIES_ARCEUS_NORMAL`, `SPECIES_GENESECT`, `SPECIES_FLABEBE_RED`,
`SPECIES_FLOETTE_RED`, `SPECIES_FLORGES_RED`, `SPECIES_OGERPON_TEAL`) recebem os innates por
**macro**:

| Macro | Innates | Local |
|---|---|---|
| `UNOWN_MISC_INFO` | `ABILITY_ENIGMA` | `gen_2_families.h:4273` |
| `ARCEUS_SPECIES_INFO` | `ABILITY_OMEGA, ABILITY_AURA_SHIELD, ABILITY_AIR_LOCK` | `gen_4_families.h:8132` |
| `GENESECT_SPECIES_INFO` | `ABILITY_LIGHT_METAL, ABILITY_SWARM, ABILITY_GENERALIST` | `gen_5_families.h:14291` |
| `FLABEBE_MISC_INFO` | `ABILITY_LEVITATE` | `gen_6_families.h:2002` |
| `FLOETTE_NORMAL_INFO` | `ABILITY_LEVITATE, ABILITY_SOOTHING, ABILITY_DAZZLING` | `gen_6_families.h:2106` |
| `FLORGES_MISC_INFO` | `ABILITY_LEVITATE, ABILITY_SOOTHING, ABILITY_NATURAL_CURE` | `gen_6_families.h:2257` |
| `SILVALLY_SPECIES_INFO` | `{innate1, innate2, innate3}` — 3 por tipo | `gen_7_families.h:4779` |
| `OGERPON_SPECIES_INFO` | `{innate1, innate2, innate3}` — 3 por máscara | `gen_9_families.h:8294` |
| `ALCREMIE_MISC_INFO` | `ABILITY_HEALER, ABILITY_AROMA_VEIL, ABILITY_SWEET_VEIL` | `gen_8_families.h:5206` |

Macros **sem** innates (todas de famílias desabilitadas):
`MOTHIM_SPECIES_INFO`, `SCATTERBUG_SPECIES_INFO`, `SPEWPA_SPECIES_INFO`, `VIVILLON_MISC_INFO`,
`FURFROU_MISC_INFO`, `MINIOR_MISC_INFO`.

### 2.3 As 234 espécies “prontas” têm mesmo todos os dados?

Sim — verificado campo a campo nas 232 espécies-base desabilitadas com innates que não usam macro:

| Campo | Faltando |
|---|---|
| `levelUpLearnset`, `teachableLearnset` | 0 |
| `frontPic`, `backPic`, `iconSprite` | 0 |
| `palette`, `shinyPalette`, `iconPalette` | 0 |
| `cryId`, `description`, `natDexNum` | 0 |
| `innates` | 0 |
| `eggMoveLearnset` | 122 — **não é defeito** |

`eggMoveLearnset` só existe na forma-base de cada cadeia em todo o projeto
(Bulbasaur tem, Ivysaur e Venusaur não; Zubat tem, Golbat não). As 122 “faltas” são todas
formas evoluídas, seguindo a mesma convenção das espécies habilitadas.

**Conclusão: as 234 espécies estão tecnicamente completas.** O único trabalho pendente é
`P_FAMILY_* = FALSE → <geração>` e a distribuição.

### 2.4 As 47 famílias que precisam de innates antes de qualquer distribuição

**Gen 5 (41 famílias, 76 espécies)**
Patrat, Lillipup, Purrloin, Pansage, Pansear, Panpour, Munna, Pidove, Blitzle, Roggenrola,
Woobat, Timburr, Tympole, Throh, Sawk, Dwebble, Sigilyph, Tirtouga, Trubbish, Gothita, Ducklett,
Vanillite, Deerling, Foongus, Frillish, Alomomola, Klink, Elgyem, Cubchoo, Cryogonal, Shelmet,
Druddigon, Bouffalant, Heatmor, Durant

**Gen 6 (10 famílias, 18 espécies)**
Bunnelby, Scatterbug/Spewpa/Vivillon, Pancham, Furfrou, Spritzee, Swirlix, Helioptile, Dedenne,
Carbink, Pumpkaboo/Gourgeist

**Outras (2)**
Burmy/Wormadam/**Mothim** (Mothim é o único membro sem innates da família), **Minior**

> Estimativa de esforço: 89 espécies × 1‑3 innates = ~180 linhas de `.innates` a projetar.
> É o único bloqueio real para a Gen 5/6 — todo o resto do dado já existe.

---

## 3. Regra de distribuição adotada

Conforme pedido: **não é preciso colocar a linha evolutiva inteira no mundo — basta um membro
por família**, desde que o resto seja alcançável por evolução ou reprodução.

Validações feitas para garantir que a regra funciona:

* **Reprodução funciona** — Day Care da Route 34 alcançável e funcional
  (`data/maps/Route34_DayCare/scripts.inc:476`, `GiveEggFromDaycare`), Ditto disponível
  (Hidden Grotto Route 47), `P_INCENSE_BREEDING = GEN_LATEST` (sem incensos).
  Logo, colocar **qualquer** membro dá acesso à linha inteira: sobe por evolução, desce por ovo.
* **Nenhuma das 134 famílias prontas tem evolução travada por item ausente.** Verificado
  item a item contra a lista de itens distribuídos.
* **18 famílias prontas são `EGG_GROUP_NO_EGGS_DISCOVERED`** — nelas a regra não vale e
  **cada espécie precisa de fonte própria**: os 9 Ultra Beasts, Wo-Chien, Ting-Lu, Okidogi,
  Munkidori, Dracozolt, Arctozolt, Dracovish, Arctovish e Type: Null
  (Silvally sai por evolução por amizade, então Type: Null basta).

### 3.1 Três exceções que exigem trabalho extra

| Caso | Problema | Correção necessária |
|---|---|---|
| **Milcery / Alcremie** | `SPECIES_MILCERY` **não tem `.evolutions`** neste repositório, e nenhum `ITEM_*_SWEET` é distribuído | adicionar a evolução (ou distribuir Alcremie direto) **e** vender as 7 Sweets |
| **Karrablast / Shelmet** | única evolução é `EVO_TRADE` com `IF_TRADE_PARTNER_SPECIES` — **sem alternativa por item** (ao contrário das outras 18 evoluções por troca do jogo) | adicionar `{EVO_ITEM, ITEM_LINKING_CORD, SPECIES_ESCAVALIER/ACCELGOR}` |
| **Cranidos / Shieldon / Tirtouga** | evoluem por nível ✅, mas Skull/Armor/Cover Fossil **não existem como item distribuído** | adicionar os 3 fósseis a `sRockSmashItems_RuinsOfAlph` (`src/wild_encounter.c:120`) e 3 opções no laboratório |

---

## 4. Onde há espaço para distribuir

As tabelas de encontro têm tamanho fixo (`include/constants/wild_encounter.h`):
land 12, water 5, rock smash 5, fishing 10. **Todas as 123 tabelas terrestres estão cheias** —
mas há muito espaço estrutural:

### 4.1 Tabelas por horário — a maior alavanca

`OW_TIME_OF_DAY_ENCOUNTERS = TRUE` (`include/config/overworld.h:97`).
O gerador (`tools/wild_encounters/wild_encounters_to_header.py:226-231`) escolhe o horário
**pelo sufixo do `base_label`**: `_Morning`, `_Day`, `_Evening`, `_Night`.
Horários sem tabela caem em `TIME_MORNING`
(`OW_TIME_OF_DAY_FALLBACK`, `OW_TIME_OF_DAY_DISABLE_FALLBACK = FALSE`).

**Só 11 de 138 mapas têm variante noturna.** Adicionar um bloco `_Night` (ou `_Evening`) a um mapa
cria uma tabela de 12 slots **sem remover nada** — e é o recurso de design mais barato do projeto:

```json
{ "map": "MAP_ROUTE30", "base_label": "gRoute30_Night",
  "land_mons": { "encounter_rate": 20, "mons": [ ...12 entradas... ] } }
```

### 4.2 Tabelas vazias ou redundantes (ganho imediato)

| Local | Situação hoje | Slots aproveitáveis |
|---|---|---|
| `MAP_OLIVINE_CITY_PORT_OUTSIDE` (land, dia + noite) | **12 × `SPECIES_NONE`** em cada tabela | **24** |
| `MAP_VERMILION_CITY_PORT_OUTSIDE` (land, dia + noite) | **12 × `SPECIES_NONE`** em cada tabela | **24** |
| `MAP_MT_SILVER_1F_ITEM_ROOM` (water) | 5 × `SPECIES_NONE` | 5 |
| `MAP_TIN_TOWER_3F` … `9F` | **7 tabelas idênticas** (Mimikyu×4, Haunter, Raticate, Manectric, Falinks) | ~24 (diversificar 4 andares) |
| `MAP_ROCKET_HIDEOUT_B1F` | 3 espécies únicas — **Koffing ocupa 7 slots** | ~5 |
| `MAP_SNOWTOP_MOUNTAIN` / `_OUTSIDE` | 4 espécies únicas cada | ~4 |
| `MAP_ICE_PATH_1F` / `_B1F` (dia + noite) | 5 espécies únicas | ~4 |
| `MAP_VAJRA_PYRAMID_FLOOR1..4` | 4 tabelas idênticas | ~12 |
| `MAP_KITAKAMI_MOUNTAIN1F..4F` | 4 tabelas idênticas | ~12 |
| `MAP_RAILWAY_CAVE_2F` / `_3F` | tabelas idênticas | ~6 |

> O idioma de design do projeto é **6 espécies × 2 slots** por tabela terrestre (83 das 123 tabelas
> seguem exatamente isso). As propostas abaixo respeitam esse padrão.

### 4.3 Níveis

`B_LEVEL_SCALING_ENABLED = TRUE` e `B_WILD_SCALING_DEFAULT_MODE = LEVEL_SCALING_PARTY_AVG`
com `B_WILD_SCALING_LEVEL_AUGMENT = -8` (`include/config/level_scaling.h:52-59`).
Os níveis do JSON funcionam como **piso**, não como valor final — basta manter coerência com a
tabela vizinha do mesmo mapa.

### 4.4 Sistemas não-selvagens reutilizáveis

| Sistema | Capacidade | Arquivo |
|---|---|---|
| Gacha do Game Corner | 16 pools, 307 espécies hoje — cresce livremente | `src/game_corner_gacha.c` |
| Hidden Grottos | 10 grutas × 4 espécies = 40 slots (rotativos, diários) | `src/hidden_grotto.c` |
| Trocas com NPC | 15 trocas hoje | `src/data/trade.h` |
| Battle Café (Café Points) | já vende 14 lendários por 5 pts | `data/maps/BattleCafe/scripts.pory` |
| Laboratório de fósseis | 8 fósseis → 8 espécies | `data/maps/RuinsOfAlph_Lab/scripts.inc` |
| Loja de BP do Battle Arcade | já vende Scrolls of Darkness/Waters | `data/maps/GoldenrodBattleAracdeLobby/scripts.inc:81` |
| Estáticos / bosses | 29 `bosslegendaryencounter` + 19 `legendaryencounter` | `data/maps/*/scripts.inc` |

---

## 5. Plano de distribuição

### Onda 0 — Correções de bug (13 famílias, 24 espécies) · custo: ~13 linhas

Todas com innates completos. **Basta trocar `FALSE` pelo valor da geração** em
`include/config/species_enabled.h`:

```c
#define P_FAMILY_SPEAROW      P_GEN_1_POKEMON   // corrige o presente KENYA
#define P_FAMILY_OMANYTE      P_GEN_1_POKEMON   // corrige a revivificação do Helix Fossil
#define P_FAMILY_SENTRET      P_GEN_2_POKEMON   // já está no gacha
#define P_FAMILY_SHUCKLE      P_GEN_2_POKEMON   // corrige o presente SHUCKIE
#define P_FAMILY_REMORAID     P_GEN_2_POKEMON   // já está no gacha
#define P_FAMILY_LOTAD        P_GEN_3_POKEMON   // já está no gacha + presente
#define P_FAMILY_SEEDOT       P_GEN_3_POKEMON   // já está no gacha
#define P_FAMILY_SPINDA       P_GEN_3_POKEMON   // corrige o presente do Gramps
#define P_FAMILY_ANORITH      P_GEN_3_POKEMON   // corrige a revivificação do Claw Fossil
#define P_FAMILY_CASTFORM     P_GEN_3_POKEMON   // já está no gacha + presente
#define P_FAMILY_KECLEON      P_GEN_3_POKEMON   // precisa de novo posicionamento (§5.3)
#define P_FAMILY_CLAMPERL     P_GEN_3_POKEMON   // já está no gacha
#define P_FAMILY_RELICANTH    P_GEN_3_POKEMON   // já está no gacha
```

**Resultado:** 24 espécies entram e **23 ficam obteníveis imediatamente**, sem nenhum conteúdo novo:

| Via | Espécies |
|---|---|
| Presente já existente | Spearow (Kenya), Shuckle (Shuckie), Spinda |
| Fóssil já existente | Omanyte, Anorith |
| Gacha (pools já escritas) | Sentret, Furret, Remoraid, Octillery, Lotad, Lombre, Ludicolo, Seedot, Nuzleaf, Shiftry, Castform, Clamperl, Huntail, Gorebyss, Relicanth |
| Evolução do acima | Fearow, Armaldo, Omastar |

A **única** que ainda fica sem fonte é **Kecleon** — ver §7, item 2.

> Clamperl→Huntail/Gorebyss já funciona: `ITEM_DEEP_SEA_TOOTH` e `ITEM_DEEP_SEA_SCALE` são
> recompensas do Gramps na casa do Bill (`data/maps/Route25_BillsHouse/scripts.inc:83,117`)
> e itens segurados por Carvanha/Chinchou selvagens.

---

### Onda 1 — Fechar os conjuntos (14 famílias, 15 espécies) · custo: ~13 scripts

Todas `NO_EGGS` → cada uma precisa de fonte própria.

#### 1a. Tesouros da Ruína — completar 4/4

| Espécie | Método proposto | Local | Nível | Justificativa |
|---|---|---|---|---|
| **Wo-Chien** (Grama/Sombrio) | `legendaryencounter` | `MAP_DEEP_ILEX_FOREST` | 70 | mapa dedicado que já hospeda um estático (Larvesta); floresta antiga combina com a tabuleta de madeira |
| **Ting-Lu** (Terra/Sombrio) | `bosslegendaryencounter` | `MAP_VAJRA_DESERT_EAST_CAVE` | 70 | caverna profunda no deserto; o mapa hoje só tem tabela selvagem, sem estático |

Espelha o padrão existente: Chien-Pao é boss em `IcePath_Depths2`, Chi-Yu é pescado no Battle Café.

#### 1b. Os Três Leais — completar 3/3

| Espécie | Método | Local | Nível |
|---|---|---|---|
| **Okidogi** (Veneno/Lutador) | `legendaryencounter` | `MAP_KITAKAMI_MOUNTAIN4F` | 55 |
| **Munkidori** (Veneno/Psíquico) | `legendaryencounter` | `MAP_KITAKAMI_BORDER` (sub-área/santuário) | 55 |

Fezandipiti já está em `MAP_KITAKAMI_WELL_B1F` no nível 55 — os três ficam em Kitakami, como em SV.
Sugestão de gameplay: exigir os três capturados para liberar um NPC que entrega o
`ITEM_PRISON_BOTTLE`… ou, melhor, para desbloquear **Pecharunt** (hoje inobtenível, §12 da auditoria
anterior) — fecha o arco dos Loyal Three e resolve um dos 24 buracos da Pokédex de graça.

#### 1c. Ultra Beasts — 9 espécies, um “Ultra Wormhole” pós-liga

O padrão dos Paradox (Meteor Cave 1 = Ancient, Meteor Cave 2 = Future) pede um terceiro eixo.
Proposta de menor custo — **um estático por bioma correspondente**, todos com flag própria,
liberados após a Elite Four:

| UB | Tipos | Local proposto | Nível | Por quê |
|---|---|---|---|---|
| Nihilego | Rocha/Veneno | `MAP_CERULEAN_CAVE_B1F` | 65 | caverna “corrompida” pós-jogo |
| Buzzwole | Inseto/Lutador | `MAP_MT_SILVER_MOUNTAIN_SIDE` | 65 | encosta de escalada |
| Pheromosa | Inseto/Lutador | `MAP_FARAWAY_ISLAND_JUNGLE` | 65 | selva isolada, já é mapa de conteúdo raro |
| Xurkitree | Elétrico | `MAP_RAILWAY_CAVE_3F` | 65 | hub elétrico do jogo |
| Celesteela | Aço/Voador | `MAP_VAJRA_PYRAMID_FLOOR4` | 65 | câmara alta da pirâmide |
| Kartana | Grama/Aço | `MAP_FOGGY_FOREST` (área profunda) | 65 | floresta densa |
| Guzzlord | Sombrio/Dragão | `MAP_METEOR_CAVE2` (câmara lateral) | 65 | já é o mapa das anomalias |
| Stakataka | Rocha/Aço | `MAP_VICTORY_ROAD_KANTO_B2F` | 65 | ruína de pedra |
| Blacephalon | Fogo/Fantasma | `MAP_TIN_TOWER_9F` | 65 | topo da torre, hoje com tabela duplicada |

Alternativa mais elegante (custo maior): um NPC no Battle Café que abre buracos por
**Café Points** — reaproveita literalmente o menu que já entrega Tapus e Forças da Natureza
(`BattleCafe_RewardMenu`), e resolve os 9 UBs com um único sistema.

#### 1d. Type: Null / Silvally

| Espécie | Método | Local |
|---|---|---|
| **Type: Null** | `givemon` | `MAP_ROUTE40_HOUSE4` — a “casa dos presentes míticos” que já entrega Poipole, Zarude, Magearna Original, Floette Eternal e Greninja-Bond |
| Silvally | evolução por amizade ✅ | automático |
| 17 formas de Silvally | exigem as **Memories** (nenhuma distribuída) | vender as 17 na loja de BP do `MAP_GOLDENROD_BATTLE_ARACDE_LOBBY`, que já vende os Scrolls |

---

### Onda 2 — Preencher buracos de tipo (107 famílias prontas restantes, 193 espécies)

#### Diagnóstico: quais tipos estão magros

| Tipo | Obteníveis hoje | Disponíveis no pool desabilitado |
|---|---|---|
| **Gelo** | **31** | 15 |
| **Fada** | **32** | 15 |
| **Inseto** | 39 | 48 |
| **Aço** | 42 | 19 |
| **Rocha** | 44 | 29 |
| **Sombrio** | 48 | 20 |
| **Elétrico** | 49 | 17 |
| **Fantasma** | 50 | 11 |
| … | … | … |
| Água | 102 | 50 |
| Grama | 85 | 40 |
| Voador | 76 | 28 |

Gelo e Fada são os gargalos reais de time-building; Água/Grama/Voador estão saturados.
As propostas abaixo priorizam Gelo, Fada, Aço, Rocha, Fantasma e Elétrico.

#### 2a. Rotas iniciais — devolver o sabor HGSS (tabelas `_Night` novas)

As rotas 29‑31 hoje repetem Rattata/Hoothoot/Pidgey em 12 slots com só 5 espécies únicas.
Quatro famílias desabilitadas são **canonicamente** dessas rotas em HGSS:

| Nova tabela | 6 espécies (2 slots cada) | Níveis |
|---|---|---|
| `gRoute29_Night` | **Spearow**, **Sentret**, Hoothoot, Rattata, **Ledyba**, Zigzagoon | 2‑4 |
| `gRoute30_Night` | **Ledyba**, **Kricketot**, Hoothoot, **Spinda**, Poliwag, Bellsprout | 4‑8 |
| `gRoute31_Night` | **Sentret**, **Bidoof**, Zubat, **Venonat**, Bellsprout, Hoothoot | 5‑9 |
| `gRoute46_Night` | **Spearow**, **Doduo**, Geodude, **Skitty**, Rattata, Mankey | 2‑5 |

> Ledyba já é noturno em HGSS; Kricketot também. Ganha-se variedade sem tocar nas tabelas diurnas.

#### 2b. Gelo — Snowtop Mountain e Ice Path

| Nova tabela | 6 espécies | Níveis | Nota |
|---|---|---|---|
| `gSnowtopMountain_Night` | **Smoochum**, **Snom**, **Cetoddle**, Snorunt, Bergmite, Spheal | 26‑31 | Smoochum/Jynx e Snom entram no ciclo noturno; Snom→Frosmoth exige amizade **à noite** ✅ |
| `gSnowtopMountain_B1F_Night` | **Eiscue**, **Cetitan**, Frigibax, Vulpix-Alola, Snorunt, Bergmite | 26‑31 | |
| `gIcePath_B4F_Night` | **Jynx**, **Frosmoth**, Sneasel, Delibird, Swinub, Snorunt | 33‑42 | |
| `gMtSilver_Snow_Night` | **Arctozolt**, **Arctovish**, Weavile, Froslass, Abomasnow, Mamoswine | 61‑69 | ver §5.4 se preferir a rota dos fósseis |

Ganho: **Gelo passa de 31 → ~42 espécies obteníveis.**

#### 2c. Fada — pastagens e floresta

| Onde | Espécies | Níveis | Nota |
|---|---|---|---|
| `gRoute38_Night` (nova) | **Snubbull**, **Fidough**, Miltank, Tauros, Meowth, Growlithe | 19‑26 | Granbull é da Route 38 em HGSS |
| `gIlexForest_Night` (nova) | **Comfey**, **Morelull**, Oddish, Paras, Psyduck, Dewpider | 10‑15 | Morelull/Comfey exigem innates? não — ambas prontas |
| Hidden Grotto Ilex (rotação) | **Milcery** | 10 | requer a correção da evolução (§3.1) |

Ganho: **Fada passa de 32 → ~40.**

#### 2d. Aço e Rocha — Ruins of Alph, Railway Cave, Meteor Cave

| Onde | Espécies | Níveis | Justificativa |
|---|---|---|---|
| `gRuinsOfAlph_Night` (nova, land) | **Bronzor**, **Solrock**, **Lunatone**, Natu, Smeargle, Baltoy | 6‑12 | tema arqueológico perfeito; Solrock/Lunatone dia vs. noite |
| `gRailwayCave_Night` (nova) | **Cufant**, **Rolycoly**, **Varoom**, Magnemite, Diglett-Alola, Stunfisk | 25‑29 | mina/ferrovia: carvão, cobre e motores |
| `gMeteorCave1_Night` (nova) | **Lunatone**, **Solrock**, **Stonjourner**, Great Tusk, Scream Tail, Sandy Shocks | 56‑60 | Lunatone/Solrock são literalmente Pokémon-meteoro |
| `gCliffEdgeCave_Night` (nova) | **Klawf**, **Shuckle**, **Dwebble**\*, Onix, Binacle, Dugtrio | 23‑31 | “Cliff Edge” combina com Klawf (caranguejo de penhasco) |
| `gRocketHideout_Night` (substituir 5 dos 7 Koffing) | **Varoom**, **Orthworm**, **Stunky**, Voltorb, Geodude, Koffing | 21 | base industrial |

\* Dwebble é Gen 5 — só entra após a Onda 3.

Ganho: **Aço 42 → ~50, Rocha 44 → ~54.**

#### 2e. Fantasma e Elétrico

| Onde | Espécies | Níveis |
|---|---|---|
| `gVajraPyramidFloor2` (rebalancear — hoje é cópia do Floor1) | **Sandygast**, **Greavard**, **Bramblin**, Cofagrigus, Sableye, Mismagius | 58‑60 |
| `gVajraDesert_Night` (nova) | **Sandygast**, **Bramblin**, **Orthworm**, Sandile, Trapinch, Cacnea | 26‑30 |
| `gRailwayCave_2F_Night` (nova) | **Tadbulb**, **Togedemaru**, **Pincurchin**, Tynamo, Toxel, Pikachu | 25‑29 |
| `gRoute34_Night` (nova) | **Yamper**, **Plusle**, **Minun**, Drowzee, Snubbull, Abra | 10‑16 |
| `gGoldenrodCity` — via gacha | **Morpeko** (pool Great) | — |

Ganho: **Fantasma 50 → ~57, Elétrico 49 → ~58.**

#### 2f. Portos vazios — 48 slots de graça

| Tabela | 6 espécies | Níveis |
|---|---|---|
| `gOlivineCity_PortOutside` (land, hoje 12× `NONE`) | **Krabby**, **Wiglett**, **Cramorant**, **Skwovet**, Wingull, Machop | 14‑18 |
| `gOlivineCity_PortOutside_Night` | **Krabby**, **Nickit**, **Maschiff**, **Bombirdier**, Wingull, Grimer | 14‑18 |
| `gVermilionCity_PortOutside` (land, hoje 12× `NONE`) | **Psyduck**, **Krabby**, **Arrokuda**, **Chewtle**, Machoke, Magnemite | 30‑36 |
| `gVermilionCity_PortOutside_Night` | **Psyduck**, **Golduck**, **Nickit**, **Veluza**, Grimer, Koffing | 30‑36 |

> Isso também resolve os 48 slots `SPECIES_NONE` apontados na auditoria anterior (§11.4).

#### 2g. Safari Zone — o hub natural do “resto”

A Safari Zone é o hub de formas regionais (6 áreas × 6 espécies). Duas áreas têm faixa
19‑56, o que comporta bem espécies de outras regiões. Proposta: adicionar tabelas `_Night`
às 6 áreas, distribuindo as famílias Normais/Água “sem casa temática” que sobram:

`Taillow`, `Skitty`, `Whismur`, `Slakoth`, `Zangoose`, `Seviper`, `Gulpin`, `Spoink`,
`Glameow`, `Chatot`, `Carnivine`, `Croagunk`, `Pikipek`, `Yungoos`, `Stufful`, `Komala`,
`Oranguru`, `Passimian`, `Lechonk`, `Wooloo`, `Squawkabilly`, `Nymble`, `Tarountula`,
`Maschiff`, `Shroodle`, `Fidough`, `Smoliv`, `Toedscool`, `Rellor`, `Gossifleur`.

#### 2h. Água — pesca e superfície (já saturado, usar com parcimônia)

Só as famílias com forte identidade HGSS/nicho:
`Goldeen` (pesca comum), `Remoraid`/`Octillery` (Whirl Islands — canônico),
`Psyduck` (Route 30‑32 surf — canônico), `Corphish` (Route 33 South underwater),
`Clamperl`/`Relicanth` (underwater — canônico), `Luvdisc` (Route 41),
`Wishiwashi` (surf Route 41), `Dewpider` (Ilex), `Bruxish`/`Veluza`/`Wiglett` (Kitakami/South Passage).

#### 2i. Fósseis — 3 novos + 4 opcionais

Adicionar a `sRockSmashItems_RuinsOfAlph` (`src/wild_encounter.c:120`) e ao menu do laboratório:

| Fóssil | Espécie | Situação |
|---|---|---|
| `ITEM_SKULL_FOSSIL` | **Cranidos** | pronta (innates ✅) |
| `ITEM_ARMOR_FOSSIL` | **Shieldon** | pronta (innates ✅) |
| `ITEM_COVER_FOSSIL` | Tirtouga | ⏳ Gen 5, precisa de innates |
| `ITEM_FOSSILIZED_BIRD/FISH/DRAKE/DINO` | **Dracozolt/Arctozolt/Dracovish/Arctovish** | prontas — alternativa mais canônica que colocá-las selvagens |

---

### Onda 3 — Gen 5 e Gen 6 (47 famílias, 91 espécies) · bloqueada por innates

**Pré-requisito:** projetar ~180 linhas de `.innates` seguindo a convenção 1/2/3 por estágio.

Depois disso, os destinos naturais (todos já mapeados acima):

| Grupo | Destino |
|---|---|
| Cubchoo, Vanillite, Cryogonal + Deerling | tabelas `_Night` de Snowtop/Ice Path (Gelo passa a ~50) |
| Spritzee, Swirlix, Dedenne, Carbink | pastagens/floresta (Fada passa a ~48) |
| Klink, Durant, Tirtouga | Railway Cave / Ruins of Alph / fósseis |
| Roggenrola, Dwebble, Sigilyph | Cliff Edge Cave / Ruins of Alph |
| Frillish, Pumpkaboo, Gothita | Vajra Pyramid / Foggy Forest |
| Trubbish, Garbodor | Rocket Hideout |
| Timburr, Throh, Sawk, Pancham | Mt. Mortar (dojo/treino) |
| Pansage/Pansear/Panpour | Ilex Forest / Burned Tower / Route 41 (um por bioma) |
| Blitzle, Helioptile | Route 42/48, Vajra Desert |
| Scatterbug/Vivillon | National Park — `P_SCATTERBUG_LINE_FORM_BREED` já aponta para `SPECIES_SCATTERBUG_FANCY` |
| Furfrou, Minior, Mothim | precisam de innates **e** de método de forma (§8 da auditoria anterior) |

**Correções obrigatórias junto com a Onda 3:**
* `Karrablast`/`Shelmet`: adicionar alternativa `EVO_ITEM, ITEM_LINKING_CORD` (hoje só `EVO_TRADE`).
* `Milcery`: adicionar `.evolutions` + distribuir as 7 Sweets.
* `Mothim`, `Furfrou`, `Minior`, `Scatterbug`/`Spewpa`/`Vivillon`: innates nas macros.

---

## 6. Impacto projetado

| Cenário | Espécies na Pokédex configurada | Obteníveis | Déficit | Custo |
|---|---|---|---|---|
| **Hoje** | 702 | 678 | **24** | — |
| + Onda 0 | 726 (+24) | 701 (+23) | 25 | 13 linhas de config |
| + Onda 0 + Kecleon reposicionado | 726 | 702 (+24) | 24 | +1 chamada de script |
| + Onda 1 | 741 (+15) | 717 (+15) | 24 | ~13 scripts |
| + Onda 1 com Pecharunt atrelado aos Loyal Three | 741 | 718 | **23** | +1 script |
| + Onda 2 | 934 (+193) | ~911 | ~23 | ~30 tabelas `_Night` + ajustes |
| + Onda 3 (todas as 181 famílias) | **1025** (+91) | ~1002 | ~23 | ~180 linhas de innates + distribuição |
| + resolver os 23 lendários restantes (§12 da auditoria anterior) | 1025 | **1025** | **0** | ~23 scripts |

> Os números de “obteníveis” assumem que cada família recebe ao menos um membro no mundo
> e que evolução/reprodução cobrem o resto — regra validada em §3. As 18 famílias `NO_EGGS`
> (§3) já estão contadas com uma fonte por espécie.
>
> O déficit residual de 23–24 são os lendários/míticos listados na
> [auditoria anterior §12](POKEMON_AVAILABILITY_AUDIT.md) — **todos já habilitados**, apenas
> sem conteúdo. Nenhum deles aparece neste documento porque nenhum está desabilitado.

---

## 7. Ordem de execução recomendada

1. **Onda 0** — 13 linhas de config. Corrige 4 presentes quebrados (Kenya, Shuckie, Helix, Claw)
   e ~15 entradas inválidas no gacha. *Maior retorno por esforço de todo o plano.*
2. **Reposicionar Kecleon** — `data/scripts/kecleon.inc` já existe e está pronto; só falta ser
   chamado de um mapa alcançável (sugestão: Route 42 ou Ilex Forest, no estilo “Kecleon invisível”).
3. **Onda 1** — 13 scripts fecham Tesouros da Ruína, Loyal Three e Ultra Beasts.
   Amarrar Pecharunt aos Loyal Three elimina 1 dos 24 buracos de Pokédex de graça.
4. **Portos vazios (§2f)** — 48 slots já alocados, hoje desperdiçados com `SPECIES_NONE`.
5. **Ondas 2b–2e (Gelo/Fada/Aço/Rocha/Fantasma/Elétrico)** — corrige os gargalos reais de
   time-building.
6. **Fósseis (§2i)** — 2 espécies prontas (Cranidos, Shieldon) + 4 opcionais, reutilizando
   um sistema que já existe.
7. **Onda 3** — só depois do trabalho de innates da Gen 5/6.

---

## 8. Como reproduzir esta análise

Scripts em diretório temporário fora do repositório (não versionados):

```bash
# 1. innates de todas as 1577 entradas
python3 innates.py                # -> innates.json  (1239 com innates / 338 sem)

# 2. flags corretas — o fork NÃO usa .isLegendary
grep -rhoE "^\s+\.is[A-Za-z]+\s*=\s*TRUE" src/data/pokemon/species_info/gen_*_families.h \
  | sed 's/ *//g' | sort | uniq -c | sort -rn
# .isSubLegendary 57 | .isRestrictedLegendary 55 | .isMythical 38 | .isParadox 20 | .isUltraBeast 11

# 3. mapear cada espécie à sua família seguindo os #if P_FAMILY_* do species_info
python3 families.py               # -> disabled_families.json (181 famílias)

# 4. tabelas de encontro: redundância e slots livres
python3 -c "...map_tables..."     # 123 tabelas terrestres: 83 no padrão 6 espécies x 2 slots;
                                  # 6 com 1 especie unica (5 delas 100% SPECIES_NONE + Unown em Ruins of Alph)

# 5. checar se alguma família pronta tem evolução travada por item
#    (resultado: nenhuma)
```

Fontes de configuração consultadas:
`include/config/species_enabled.h`, `include/constants/global.h:132-137`,
`include/constants/wild_encounter.h`, `include/config/overworld.h:97-99`,
`include/config/level_scaling.h:52-59`, `tools/wild_encounters/wild_encounters_to_header.py:226-231`,
`src/pokemon.c:3419,7793`, `src/scrcmd.c:3475-3498`, `src/wild_encounter.c:118-163`.
