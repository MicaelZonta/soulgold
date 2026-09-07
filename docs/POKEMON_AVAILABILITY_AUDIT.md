# Auditoria de Disponibilidade de Pokémon e Formas — Pokémon Heart & Soul (Soulgold)

> Documento gerado por análise estática do repositório. Cobre **todas** as 1577 entradas de
> `gSpeciesInfo` (1025 espécies-base + 552 formas), com separação explícita entre
> **“existe no repositório”** e **“pode ser conseguido no jogo”**.

---

## 1. Resumo executivo

| Pergunta | Resposta curta |
|---|---|
| Quantas entradas de espécie existem no repositório? | **1577** (1025 espécies-base + 552 formas) |
| Quantas espécies-base estão **habilitadas** na configuração atual? | **702** (= `JOHTO_DEX_COUNT − 1`) |
| Quantas espécies-base são **realmente obteníveis** num save normal? | **677** (678 “slots” da Pokédex, contando Oricorio via forma alternativa) |
| Quantas espécies-base habilitadas **não** são obteníveis? | **25 constantes / 24 slots de Pokédex** — todas lendárias/míticas |
| Quantas espécies-base estão desabilitadas por configuração? | **323** |
| Quantas formas existem? | **552** (336 habilitadas, 216 desabilitadas) |
| Quantas formas são **colecionáveis permanentemente**? | **142** |
| Quantas transformações de batalha são **ativáveis**? | **127** distintas (112 Megas, 2 Primals, 4 Ogerpon-Tera, 9 outras) |
| Quantas transformações de batalha estão **bloqueadas**? | **22** (14 Gigantamax, Necrozma-Ultra, Zacian/Zamazenta-Crowned, Terapagos ×2, Zygarde ×2, Xerneas-Active, Zygarde-Mega) |
| É possível completar a Pokédex configurada num único save? | **Não.** Faltam 24 slots (ver §12). |
| É possível obter todas as formas num único save? | **Não.** 194 formas habilitadas nunca ficam permanentemente disponíveis. |

**Principais achados**

1. A Pokédex regional configurada (`JOHTO_DEX`) tem **702 espécies**; **678** delas têm pelo menos
   uma fonte legítima. As **24** restantes (Deoxys, Reshiram, Zekrom, Kyurem, Keldeo, Xerneas,
   Yveltal, Zygarde, Volcanion, linha Cosmog/Solgaleo/Lunala, Necrozma, Zacian, Zamazenta,
   Eternatus, Regieleki, Regidrago, Glastrier, Spectrier, Calyrex, Terapagos, Pecharunt)
   **não têm nenhum encontro, script, presente ou evolução no jogo**.
2. **Dynamax/Gigantamax está desligado de facto**: `B_FLAG_DYNAMAX_BATTLE = 0` e
   `ITEM_DYNAMAX_BAND` não é distribuído. As 14 formas G-Max acionadas por
   `FORM_CHANGE_BATTLE_GIGANTAMAX` são inatingíveis — **exceto** Butterfree-GMAX,
   Toxtricity-Amped-GMAX e Toxtricity-Low-Key-GMAX, que o hack reaproveitou como *Megas*
   (acionadas por `FORM_CHANGE_BATTLE_MEGA_EVOLUTION_ITEM`).
3. **Terastalização é inatingível**: `ITEM_TERA_ORB` não é distribuído em nenhum mapa/loja.
   As formas Ogerpon-*-Tera continuam acessíveis porque o hack também as liga às máscaras
   via gatilho de Mega.
4. **Todas as 18 megapedras genéricas por tipo** (`ITEM_*TITE`) + `ITEM_BONDSTONE` são
   distribuídas; **112 Megas** são ativáveis em batalha.
5. **As formas de aparelho do Rotom são inatingíveis**: a tabela usa
   `FORM_CHANGE_MOVE … WHEN_LEARNED` com Overheat/Hydro Pump/Blizzard/Air Slash/Leaf Storm,
   mas Rotom não consegue aprender **nenhum** desses golpes nesta build.
6. **Inconsistência real**: conteúdo alcançável ainda entrega/sorteia **espécies desabilitadas**
   (Omanyte e Anorith na revivificação de fósseis, e ~15 espécies no gacha do Game Corner).
7. Evoluções por troca foram todas resolvidas com alternativas por item — só
   `ITEM_GIMMIGHOUL_COIN` ficou sem fonte (irrelevante: Gholdengo tem rota alternativa por nível).

---

## 2. Identificação da análise

| Campo | Valor |
|---|---|
| Repositório | `/home/ADMIN/decomps/soulgold` (Pokémon Heart & Soul / Soulgold) |
| Branch | `master` (branch padrão) |
| Commit analisado | `692c07cd71643e970f4206fbc9099004579323b7` |
| Data do commit | 2026-09-04 19:16:30 +0300 |
| Mensagem do commit | `update docs` |
| Estado da árvore | limpa (`git status --porcelain` vazio) antes da geração deste documento |
| Data da análise | 2026-09-05 |
| Base upstream | pokeemerald-expansion (RHH) |

**Nenhum arquivo de código-fonte do projeto foi modificado.** Os únicos arquivos criados são este
documento e os dois anexos CSV em `docs/`. Todos os scripts de análise ficaram fora do repositório
(diretório temporário de trabalho).

### 2.1 Compilação

A ROM **não foi compilada**. Em vez disso, a configuração real foi resolvida com o
**pré-processador C do próprio projeto** (mesmos headers, mesmas macros), o que dá o mesmo
resultado que a compilação para as questões de “o que entra no binário”:

```bash
gcc -E -P -nostdinc -DTRUE=1 -DFALSE=0 \
    -I <repo>/include -I <repo> <esqueleto>.h -o <saida>.txt
```

O esqueleto contém apenas as diretivas `#if/#elif/#else/#endif` extraídas de
`src/data/pokemon/species_info/gen_*_families.h` mais um marcador por entrada `[SPECIES_X] =`.
Resultado: **1038 de 1577** entradas sobrevivem à configuração atual.
`TRUE`/`FALSE` precisam ser definidos manualmente porque vêm de `include/gba/defines.h`,
que não é incluído pelos headers de config.

O mesmo método foi aplicado a `form_species_tables.h`, `form_change_tables.h` e
`include/constants/pokedex.h` (para obter `NATIONAL_DEX_COUNT` e `JOHTO_DEX_COUNT`).

---

## 3. Metodologia

1. **Universo de espécies** — `include/constants/species.h` foi pré-processado para resolver
   todos os 1676 identificadores `SPECIES_*` (incluindo *aliases* como
   `SPECIES_GIMMIGHOUL → SPECIES_GIMMIGHOUL_CHEST`) para 1578 IDs numéricos.
2. **Base vs. forma** — `src/data/pokemon/form_species_tables.h` define 248 grupos de forma
   cobrindo 800 espécies. A **espécie-base** é o primeiro elemento da tabela
   (é o que `GET_BASE_SPECIES_ID` devolve, ver `NationalPokedexNumToSpecies`,
   `src/pokemon.c:4791`). Resultado: **1025 bases + 552 formas** — coincide exatamente com
   `NATIONAL_DEX_COUNT = 1025`.
3. **Habilitação** — determinada pelo pré-processador (§2.1), não por leitura visual dos `#if`.
4. **Fontes de obtenção** — coletadas automaticamente de:
   `src/data/wild_encounters.json`, `src/hidden_grotto.c`, `src/game_corner_gacha.c`,
   `src/data/trade.h`, `src/roamer.c`, `src/ui_birch_case.c`, e todos os
   `data/maps/*/scripts.inc` + `data/scripts/*.inc` (comandos `givemon`, `giveegg`,
   `setwildbattle`, `legendaryencounter`, `bosslegendaryencounter[withmoves]`, `seteventmon`,
   e `setvar VAR_TEMP_TRANSFERRED_SPECIES/VAR_TEMP_1`).
5. **Acessibilidade de mapa** — grafo dirigido construído a partir de
   `connections` + `warp_events` de todos os 1105 `data/maps/*/map.json`, mais **todos** os
   comandos de warp dos scripts (`warp`, `warpsilent`, `warpwhitefade`, `warphole`,
   `warpteleport`, `setwarp`, `setdivewarp`, `setdynamicwarp`, `setescapewarp`, `setholewarp`,
   `warpdoor`, `warpspinenter`, `warpmossdeepgym`). BFS a partir de `MAP_NEW_BARK_TOWN`
   → **551 de 1105 mapas alcançáveis**. Qualquer fonte num mapa não alcançável foi descartada.
6. **Fechamento evolutivo e reprodutivo** — ponto-fixo sobre o grafo de evolução compilado
   (345 definições `.evolutions` habilitadas), validando por entrada:
   item exigido distribuído? mapa exigido alcançável? espécie de party exigida obtenível?
   Reprodução adiciona a raiz da cadeia quando a espécie evoluída é obtenível e o grupo de ovo
   não é `EGG_GROUP_NO_EGGS_DISCOVERED` (Day Care da Route 34 é alcançável e funcional —
   `data/maps/Route34_DayCare/scripts.inc:476` `specialvar VAR_0x8008, GiveEggFromDaycare`).
7. **Itens** — fontes coletadas de `giveitem/additem/finditem`, listas de loja (`.2byte ITEM_*`),
   *object/bg events* dos `map.json` (item balls e itens ocultos), itens raros das Hidden Grottos,
   tabela de Rock Smash / pesca (`src/wild_encounter.c:118-163`), itens segurados por Pokémon
   selvagens (`.itemCommon`/`.itemRare` em `species_info`) e itens segurados por Pokémon de troca
   (`src/data/trade.h`).

### 3.1 O que **não** foi contado como fonte legítima

* Debug menu (`src/debug.c`, `data/scripts/debug.inc`).
* Times de treinadores (`src/data/trainers.party`) e rosters de instalações de batalha
  (`src/data/battle_frontier/battle_frontier_mons.h`, Battle Tower/Factory/Pike/Pyramid/Arcade) —
  são apenas oponentes/alugados, não entram no save.
* `setwildbattle` em blocos que fixam `FLAG_SYS_NO_CATCHING` (ex.: os seis Pokémon de treino de EV
  do Fighting Dojo em `data/maps/SaffronCity_FightingDojo/scripts.inc:44-52`).
* Mapas não alcançáveis (§10).
* Link trade / Union Room / Record Corner — **nenhum Cable Club é alcançável** (todos os
  `*_PokemonCenter_2F` com `CableClub_OnFrame` estão fora do grafo).
* Mystery Gift — `EnableMysteryGift()` (`src/event_data.c:230`) **nunca é chamado** por nenhum
  script, logo `FLAG_SYS_MYSTERY_GIFT_ENABLE` nunca é setado e a opção nunca aparece no menu
  (`src/main_menu.c:660`).

---

## 4. Configurações relevantes

### 4.1 Específicas do Heart & Soul (divergem do padrão do pokeemerald-expansion)

| Config | Valor | Arquivo | Efeito |
|---|---|---|---|
| `P_FAMILY_*` | **181 famílias = `FALSE`** | `include/config/species_enabled.h` | Remove 323 espécies-base e 216 formas do binário |
| `P_PIKACHU_EXTRA_FORMS` | `FALSE` | `include/config/species_enabled.h:42` | Remove Cosplay Pikachu (6) e Cap Pikachu (8) |
| `P_FOOTPRINTS` | `FALSE` | `include/config/pokemon.h` | Sem pegadas (economia de ROM) |
| `P_LEGACY_LVL_UP_LEARNSETS` | `TRUE` | `include/config/pokemon.h:21` | Camada de compatibilidade USUM sobre learnsets Gen 9 |
| `P_SHOW_TERA_TYPE` | `GEN_8` | `include/config/pokemon.h` | Tera type oculto no sumário |
| `P_CAN_FORGET_HIDDEN_MOVE` | `TRUE` | `include/config/pokemon.h` | HMs esquecíveis |
| `B_FLAG_DYNAMAX_BATTLE` | `0` | `include/config/battle.h:262` | **Dynamax/Gigantamax indisponível para o jogador** |
| `B_FLAG_TERA_ORB_CHARGED` | `0` | `include/config/battle.h:263` | Tera Orb nunca é recarregado automaticamente |
| Megapedras | genéricas por tipo (`ITEM_GRASSTITE`, `ITEM_FIRETITE`, …) | `src/data/pokemon/form_change_tables.h` | Uma pedra por tipo, distribuídas pelo mundo |
| Evoluções por troca | **todas** ganharam alternativa `EVO_ITEM` | `src/data/pokemon/species_info/*` | Ver §9 |
| Rotom | `FORM_CHANGE_MOVE` (estilo Gen 4/5) em vez de Rotom Catalog | `form_change_tables.h` | Ver §8.3 |
| Dialga/Palkia/Giratina Origin | aceitam **Adamant/Lustrous/Griseous Orb** (Gen 4) além dos itens de LA | `form_change_tables.h` | Formas Origin obteníveis |

### 4.2 Herdadas do pokeemerald-expansion (valores padrão mantidos)

```
P_GEN_1_POKEMON … P_GEN_9_POKEMON   = TRUE   (todas as 9 gerações ligadas)
P_NEW_EVOS_IN_REGIONAL_DEX          = TRUE
P_MEGA_EVOLUTIONS                   = TRUE
P_PRIMAL_REVERSIONS                 = TRUE
P_ULTRA_BURST_FORMS                 = TRUE
P_GIGANTAMAX_FORMS                  = TRUE
P_TERA_FORMS                        = TRUE
P_FUSION_FORMS                      = TRUE
P_REGIONAL_FORMS (Alola/Galar/Hisui/Paldea) = TRUE
P_CROSS_GENERATION_EVOS             = TRUE
P_GENDER_DIFFERENCES                = TRUE
P_CRIES_ENABLED                     = TRUE
P_UPDATED_* / P_LVL_UP_LEARNSETS    = GEN_LATEST (GEN_9)
OW_BATTLE_ONLY_FORMS                = FALSE
```
Fonte: `include/config/pokemon.h`, `include/config/species_enabled.h`, `include/config/general.h`,
`include/config/battle.h`, `include/config/overworld.h`.

### 4.3 Pokédex configurada

`include/constants/pokedex.h` define duas ordens:

* `enum NationalDexOrder` — **não** é filtrada por config; `NATIONAL_DEX_COUNT = NATIONAL_DEX_PECHARUNT = 1025`.
* `enum JohtoDexOrder` — **é** filtrada por `P_FAMILY_*`; após o pré-processador,
  `JOHTO_DEX_COUNT = 703`, ou seja **702 espécies na Pokédex regional jogável**.

Esse número bate exatamente com as 702 espécies-base habilitadas em `gSpeciesInfo`.

---

## 5. Cobertura por geração (espécies-base)

| Geração | Espécies no repo | Habilitadas | Obteníveis | Desabilitadas | Habilitadas mas inobteníveis |
|---|---|---|---|---|---|
| Gen 1 | 151 | 132 | 132 | 19 | 0 |
| Gen 2 | 100 | 83 | 83 | 17 | 0 |
| Gen 3 | 135 | 84 | 83 | 51 | 1 |
| Gen 4 | 107 | 82 | 82 | 25 | 0 |
| Gen 5 | 156 | 85 | 81 | 71 | 4 |
| Gen 6 | 72 | 54 | 50 | 18 | 4 |
| Gen 7 | 88 | 46 | 40 | 42 | 6 |
| Gen 8 | 96 | 56 | 48 | 40 | 8 |
| Gen 9 | 120 | 80 | 78 | 40 | 2 |
| **Total** | **1025** | **702** | **677** | **323** | **25** |

> “Obteníveis” conta a *forma-base*. O total de **slots de Pokédex** obteníveis é **678**, porque
> Oricorio é preenchido pela forma Sensu (a forma Baile em si não é obtenível).
> Os contadores por geração usam os limites do dex nacional
> (1‑151, 152‑251, 252‑386, 387‑493, 494‑649, 650‑721, 722‑809, 810‑905, 906‑1025); a diferença
> em relação aos totais “clássicos” vem de espécies cuja forma-base do repositório é uma forma
> regional/cosmética (ex.: `SPECIES_MOTHIM_PLANT`, `SPECIES_FLABEBE_RED`).

---

## 6. Tabela completa de espécies

A tabela completa das **1025 espécies-base** está no anexo:

* **`docs/POKEMON_AVAILABILITY_SPECIES.csv`**

Colunas: `NatDex, Especie, Const, Geracao, ExisteNoRepo, Habilitada, Obtivel, Classificacao,
MetodoLocal, Evidencia`.

### 6.1 Distribuição por classificação

| Classificação | Espécies-base |
|---|---|
| Obtível normalmente | 552 |
| Desabilitado por configuração | 323 |
| Obtível somente por evolução | 113 |
| Existe no código, mas não é obtível | 25 |
| Obtível somente por reprodução | 9 |
| Obtível somente por troca/comunicação (troca com NPC) | 3 |
| **Total** | **1025** |

> **Sobre “Condicional à escolha do jogador”:** os 9 iniciais (Chespin, Fennekin, Froakie,
> Chikorita, Cyndaquil, Totodile, Sprigatito, Torchic, Popplio — `src/ui_birch_case.c:138-149`)
> **não** ficam trancados pela escolha: todos os 9 também estão no pool
> `sGachaBasicSpeciesUltraRare`/`sGachaGreatSpecies*` do Game Corner
> (`src/game_corner_gacha.c`), e Froakie ainda aparece selvagem na Route 45.
> Por isso foram classificados como **Obtível normalmente**, com a observação de que a
> primeira cópia depende da escolha inicial. **Nenhuma espécie do jogo é mutuamente exclusiva
> num mesmo save.**
>
> Não há nenhuma espécie classificada como *Implementação incompleta*, *Não encontrado no
> repositório*, *Obtível somente no pós-game*, *Obtível somente por evento*,
> *Mutuamente exclusivo no mesmo save* ou *Incerto* — ver §11.6 e §13.

### 6.2 Método principal das 677 espécies-base obteníveis

Cada espécie recebe **um** método primário (o primeiro encontrado, na ordem de prioridade
fonte-direta → evolução → reprodução); muitas têm várias fontes — o CSV lista todas.

| Método primário | Espécies |
|---|---|
| Gacha do Game Corner (Mauville/Goldenrod) | 290 |
| Encontro selvagem (terra/surf/pesca/Rock Smash) | 163 |
| Evolução (única via) | 113 |
| Batalha de boss lendário | 30 |
| Hidden Grotto | 22 |
| Presente de NPC | 20 |
| Lendário estático | 14 |
| Reprodução (única via) | 9 |
| Troca com NPC | 8 |
| Batalha de evento roteirizada (`seteventmon`) | 3 |
| Lendário errante (roamer) | 3 |
| Ovo de presente | 2 |
| **Total** | **677** |

> O gacha (`src/game_corner_gacha.c`, 16 *pools* Basic/Great/Ultra/Master × Common/Uncommon/Rare/UltraRare,
> 307 espécies distintas) é o maior distribuidor único. Acessado por
> `MauvilleCity_GameCorner_EventScript_Gacha_*` → `special StartGacha`
> (`data/maps/MauvilleCity_GameCorner/scripts.pory:386`). O mapa é alcançado a partir de
> **Goldenrod City** (`data/maps/GoldenrodCity/map.json:680` → `dest_map: MAP_MAUVILLE_CITY_GAME_CORNER`).

### 6.3 Espécies obteníveis apenas por reprodução

Nove pré-evoluções não aparecem em nenhuma tabela/roteiro e só existem como ovo da Day Care
(Route 34), a partir do estágio evoluído capturável:

| Espécie | Ovo de |
|---|---|
| Starly (396) | Staravia (selvagem) |
| Mime Jr. (439) | Mr. Mime (selvagem) |
| Happiny (440) | Chansey (selvagem / Hidden Grotto Route 47) |
| Mantyke (458) | Mantine (selvagem / gacha) |
| Axew (610) | Fraxure (selvagem) |
| Flabébé (669) | Floette (selvagem, Tohjo Pass) |
| Goomy (704) | Sliggoo (selvagem) |
| Capsakid (951) | Scovillain (selvagem) |
| Flittle (955) | Espathra (selvagem / Hidden Grotto Route 38) |

(À parte destas, `SPECIES_GIMMIGHOUL_ROAMING` — contabilizado como **forma** — também só é
obtenível como ovo de Gholdengo.)

### 6.4 Espécies obteníveis apenas por troca com NPC

Três espécies-base só têm como fonte `src/data/trade.h`:

| Espécie | Troca | Pede |
|---|---|---|
| Bonsly (438) | `[INGAME_TRADE_BONSLY]` | Rhyhorn |
| Honedge (679) | `[INGAME_TRADE_HONEDGE]` | Clefairy |
| Meltan (808) | `[INGAME_TRADE_MELTAN]` (segura `ITEM_METAL_ALLOY`) | Tinkaton |

As trocas in-game **disparam evolução por troca** no Pokémon **recebido**
(`src/trade.c:4380-4392`, `STATE_TRY_EVOLUTION`: `TradeMons()` troca os mons e só então
`GetEvolutionTargetSpecies(canEvolveMon, EVO_MODE_TRADE, …)` é chamado sobre
`gPlayerParty[gSpecialVar_0x8004]`).

---

## 7. Tabela completa de formas

A tabela completa das **552 formas** está no anexo:

* **`docs/POKEMON_AVAILABILITY_FORMS.csv`**

Colunas: `EspecieBase, Forma, ConstInterna, Categoria, ExisteNoRepo, Habilitada,
ObtivelPermanente, ComoObter/Ativar, TransformacaoDeBatalha, Evidencia`.

### 7.1 Resumo por categoria

| Categoria | Existe | Habilitada | Colecionável permanentemente |
|---|---|---|---|
| Alternativa / cosmética / de batalha | 337 | 134 | 84 |
| Mega Evolution | 113 | 113 | 0 (só transformação de batalha) |
| Gigantamax | 22 | 14 | 0 |
| Regional (Galar) | 20 | 20 | 19 |
| Regional (Alola) | 18 | 18 | 18 |
| Regional (Hisui) | 16 | 16 | 16 |
| Totem | 12 | 7 | 0 |
| Forma Terastal | 5 | 5 | 0 |
| Regional (Paldea) | 4 | 4 | 4 |
| Primal Reversion | 2 | 2 | 0 |
| Forma especial do hack (Shadow) | 2 | 2 | 1 |
| Ultra Burst | 1 | 1 | 0 |
| **Total** | **552** | **336** | **142** |

### 7.2 Transformações temporárias de batalha

| Situação | Formas distintas |
|---|---|
| **Ativáveis** em batalha | **127** (112 Megas + 2 Primals + 4 Ogerpon-Tera + 9 outras: Aegislash-Blade, Darmanitan-Zen ×2, Meloetta-Pirouette, Mimikyu-Busted ×2, Greninja-Ash, Palafin-Hero, Zygarde-Complete¹) |
| **Bloqueadas** | **22** |

Bloqueadas e por quê:

| Forma | Bloqueio |
|---|---|
| Venusaur/Blastoise/Charizard/Pikachu/Meowth/Gengar/Eevee/Melmetal/Grimmsnarl/Duraludon/Flapple/Appletun/Urshifu ×2 GMAX (14) | `B_FLAG_DYNAMAX_BATTLE = 0` **e** `ITEM_DYNAMAX_BAND` sem fonte |
| `SPECIES_NECROZMA_ULTRA` | `ITEM_ULTRANECROZIUM_Z` sem fonte (e Necrozma inobtenível) |
| `SPECIES_ZACIAN_CROWNED` / `SPECIES_ZAMAZENTA_CROWNED` | `ITEM_RUSTED_SWORD` / `ITEM_RUSTED_SHIELD` sem fonte (e espécies inobteníveis) |
| `SPECIES_TERAPAGOS_TERASTAL` / `SPECIES_TERAPAGOS_STELLAR` | Terapagos inobtenível; Stellar exige Terastalização (sem `ITEM_TERA_ORB`) |
| `SPECIES_ZYGARDE_COMPLETE` / `SPECIES_ZYGARDE_MEGA` | Zygarde inobtenível |
| `SPECIES_XERNEAS_ACTIVE` | Xerneas inobtenível |

¹ Zygarde-Complete aparece nas duas listas apenas porque o gatilho (`Power Construct`, HP ≤ 50 %)
existe e funcionaria; na prática está bloqueado porque Zygarde não é obtenível.

---

## 8. Formas por família (detalhamento das solicitadas)

### 8.1 Diferenças de gênero
`P_GENDER_DIFFERENCES = TRUE` e `P_CUSTOM_GENDER_DIFF_ICONS = TRUE`
(`include/config/pokemon.h`). São diferenças **puramente gráficas** (campos
`OVERWORLD_FEMALE(...)`, `frontPicFemale`, `iconSpriteFemale`), **não** espécies separadas —
por isso não contam como formas nesta auditoria.
Formas de gênero que **são** espécies separadas: Meowstic M/F, Indeedee M/F,
Oinkologne M/F (desabilitada), Basculegion M/F.

### 8.2 Formas regionais — 58 habilitadas, 57 obteníveis
* **Alola (18/18)**, **Hisui (16/16)**, **Paldea (4/4)** — todas obteníveis.
* **Galar (19/20)** — a única não colecionável é `SPECIES_DARMANITAN_GALAR_ZEN`
  (Zen Mode, transformação de batalha via `ABILITY_ZEN_MODE`, HP ≤ 50 %).
* Principais fontes: Safari Zone (`MAP_SAFARI_ZONE_TOP_LEFT/LOW_MID/TOP_MID/…`),
  Cherrygrove City (presentes de Zigzagoon-Galar e Rattata-Alola,
  `data/maps/CherrygroveCity/scripts.inc:1324,1347`) e Hidden Grottos.

### 8.3 Rotom — **5 formas habilitadas, 0 obteníveis** ⚠️
```
sRotomFormChangeTable  (src/data/pokemon/form_change_tables.h)
  FORM_CHANGE_MOVE, SPECIES_ROTOM_HEAT,  MOVE_OVERHEAT,   WHEN_LEARNED
  FORM_CHANGE_MOVE, SPECIES_ROTOM_WASH,  MOVE_HYDRO_PUMP, WHEN_LEARNED
  FORM_CHANGE_MOVE, SPECIES_ROTOM_FROST, MOVE_BLIZZARD,   WHEN_LEARNED
  FORM_CHANGE_MOVE, SPECIES_ROTOM_FAN,   MOVE_AIR_SLASH,  WHEN_LEARNED
  FORM_CHANGE_MOVE, SPECIES_ROTOM_MOW,   MOVE_LEAF_STORM, WHEN_LEARNED
```
`src/data/pokemon/all_learnables.json` → chave `"ROTOM"`: 66 golpes, **nenhum** dos cinco acima.
`ITEM_ROTOM_CATALOG` também não é distribuído (aparece só em `src/party_menu.c` /
`src/swsh_party_menu.c`). Rotom base é obtenível (troca com NPC, `src/data/trade.h`), mas as
formas de aparelho são **“Existe no código, mas não é obtível”**.

> Ressalva: `src/data/pokemon/teachable_learnsets.h` é gerado em tempo de build por
> `tools/learnset_helpers/make_teachables.py` a partir de `all_learnables.json`. Como o gerador
> só *filtra* essa lista (por TMs/tutores disponíveis), o resultado não pode conter golpes ausentes
> da lista de origem — logo a conclusão se mantém.

### 8.4 Arceus — 18 formas habilitadas, **1 obtenível** (Normal)
`sArceusFormChangeTable` usa `FORM_CHANGE_ITEM_HOLD` com as 17 Placas e os 17 Cristais Z.
**Nenhuma Placa e nenhum Cristal Z tem fonte no jogo.** Arceus em si é obtenível
(ovo em `data/maps/GoldenrodCity_RadioTower_2F/scripts.inc:1239` — `giveegg SPECIES_ARCEUS`).

### 8.5 Genesect — 4 formas habilitadas, 0 obteníveis
`ITEM_DOUSE_DRIVE`, `ITEM_SHOCK_DRIVE`, `ITEM_BURN_DRIVE`, `ITEM_CHILL_DRIVE` só aparecem em
`form_change_tables.h`. Genesect base é obtenível
(`bosslegendaryencounter SPECIES_GENESECT`, `data/maps/AbandonedRocketHideoutBackroom/scripts.inc:49`).

### 8.6 Deoxys — 3 formas habilitadas, 0 obteníveis
`FORM_CHANGE_ITEM_USE … ITEM_METEORITE`; `ITEM_METEORITE` não é distribuído.
A própria espécie também não é obtenível (§10).

### 8.7 Formas Origin (Gen 4)
| Forma | Item aceito | Fonte | Situação |
|---|---|---|---|
| Giratina Origin | `ITEM_GRISEOUS_ORB` **ou** `ITEM_GRISEOUS_CORE` | Orb: `finditem`, `data/maps/SpearPillarTop/scripts.inc:125` | **Obtenível** |
| Dialga Origin | `ITEM_ADAMANT_CRYSTAL` **ou** `ITEM_ADAMANT_ORB` | Orb: `data/maps/SpearPillarTop/scripts.inc:49` | **Obtenível** |
| Palkia Origin | `ITEM_LUSTROUS_GLOBE` **ou** `ITEM_LUSTROUS_ORB` | Orb: `data/maps/SpearPillarTop/scripts.inc:87` | **Obtenível** |
| `SPECIES_DIALGA_PRIMAL` (exclusivo do hack) | — | `bosslegendaryencounterwithmoves SPECIES_DIALGA_PRIMAL`, `data/maps/SpearPillarTop/scripts.inc:183` | **Obtenível (captura direta)** |

### 8.8 Forças da Natureza + Enamorus — **obteníveis**
Tornadus / Thundurus / Landorus / Enamorus vêm do **Battle Café** por 5 Café Points cada
(`data/maps/BattleCafe/scripts.pory:777-815`, `.inc` correspondente), e o café **entrega o
`ITEM_REVEAL_GLASS` junto** (`data/maps/BattleCafe/scripts.inc:1663`), logo as formas
**Therian** também são obteníveis (`FORM_CHANGE_ITEM_USE`).

### 8.9 Oricorio — 4 formas, **1 obtenível como captura, 4 acessíveis**
Só **Sensu** aparece selvagem (Route 47, `gRoute47`) e na Hidden Grotto do Lake of Rage.
Os quatro néctares (`ITEM_RED/YELLOW/PINK/PURPLE_NECTAR`) são vendidos em Olivine City
(`data/maps/OlivineCity/scripts.inc:740-746`), portanto **Baile, Pom-Pom e Pa'u são
alcançáveis por uso de item** a partir do Sensu capturado.
(Na tabela CSV elas aparecem como *não* obteníveis diretamente porque a fonte é a forma Sensu +
item; o slot de Pokédex está garantido.)

### 8.10 Ogerpon — 4 máscaras obteníveis, 4 formas Tera bloqueadas
Ogerpon é capturável (`bosslegendaryencounter SPECIES_OGERPON`,
`data/maps/KitakamiMountainEnclave/scripts.inc:11`). As três máscaras são entregues em
`data/maps/Kitakami_Temple_Storage/scripts.inc:62-66`, então Teal/Wellspring/Hearthflame/
Cornerstone são todas colecionáveis. As formas `*_TERA` só existem em batalha e o gatilho de
Terastalização está indisponível (o gatilho alternativo por “mega item” funciona em batalha,
mas a forma reverte no fim).

### 8.11 Zygarde — 5 formas habilitadas, 0 obteníveis
`ITEM_ZYGARDE_CUBE` só existe em `form_change_tables.h`; Zygarde 50 % também não tem fonte.

### 8.12 Kyurem / Necrozma / Calyrex (fusões) — 0 obteníveis
`P_FUSION_FORMS = TRUE`, mas **não existem** `sKyuremFormChangeTable`,
`sCalyrexFormChangeTable` nem tabelas de fusão de Necrozma na build habilitada, e
`ITEM_DNA_SPLICERS`, `ITEM_N_SOLARIZER`, `ITEM_N_LUNARIZER`, `ITEM_REINS_OF_UNITY`
não têm nenhuma fonte. Todas as espécies-base envolvidas também são inobteníveis.

### 8.13 Unown — 28 letras, **todas obteníveis**
Unown selvagem em `MAP_RUINS_OF_ALPH_B1F` (`gRuinsOfAlph_1`). A letra é derivada da
personality em `GetUnownSpeciesId` (`src/pokemon.c:2018`), e a Pokédex guarda
`gSaveBlock2Ptr->pokedex.unownPersonality` (`src/pokemon.c:5994`).
As 27 constantes `SPECIES_UNOWN_B..QUESTION` são espécies de exibição.

### 8.14 Famílias inteiramente desabilitadas por config (formas incluídas)
Castform (4), Cherrim (2), Burmy/Wormadam/Mothim (7), Deerling/Sawsbuck (8), Furfrou (10),
Vivillon + Scatterbug + Spewpa (57), Pumpkaboo/Gourgeist (8), Silvally (18), Minior (14),
Wishiwashi (2), Cramorant (2), Alcremie (63), Eiscue (2), Morpeko (2), Squawkabilly (4),
Type: Null (1), Sinistea/Polteageist — *habilitadas*, ver abaixo.
**Total: 216 formas removidas do binário.**

### 8.15 Outras famílias solicitadas — situação resumida

| Família | Formas hab. | Colecionáveis | Observação |
|---|---|---|---|
| Castform | 0 | 0 | `P_FAMILY_CASTFORM = FALSE` (mas ainda referenciada por scripts — §11) |
| Basculin | 3 | 3 | Red/Blue/White-Striped todos selvagens |
| Basculegion | 2 | 2 | M selvagem; F selvagem (Mt. Silver) |
| Darmanitan | 4 | 2 | Standard normal + Galar Standard; ambas Zen só em batalha |
| Deerling/Sawsbuck | 0 | 0 | desabilitados |
| Kyurem | 2 | 0 | sem DNA Splicers, Kyurem inobtenível |
| Keldeo | 2 | 0 | espécie inobtenível |
| Meloetta | 2 | 1 | Aria obtenível (`legendaryencounter`, Ecruteak Theater); Pirouette só em batalha |
| Genesect | 4 | 0 | sem Drives |
| Flabébé/Floette/Florges | 15 | 15 | 5 cores; Floette selvagem em Tohjo Pass; Flabébé por ovo; Florges por Shiny Stone; **Floette Eternal** é presente de NPC (`Route40_House4`) |
| Aegislash | 1 | 0 | Blade só em batalha |
| Hoopa | 1 | 1 | Unbound via `ITEM_PRISON_BOTTLE` (Vajra Pyramid) |
| Lycanroc | 3 | 3 | Midday/Midnight/Dusk todos selvagens em Mt. Silver |
| Mimikyu | 2 (+2 Totem) | 1 | Busted só em batalha; Totem sem fonte |
| Magearna | 3 | 2 | Magearna (boss, Goldenrod Apartment) + Original (presente Route40_House4) |
| Toxtricity | 3 | 2 | Amped/Low-Key por natureza; GMAX ×2 só em batalha (via `ITEM_ELECTRITE`) |
| Sinistea/Polteageist | 2 | 2 | Antique via `ITEM_CHIPPED_POT`/`ITEM_CRACKED_POT` (Safari Zone Gate) |
| Urshifu | 3 | 2 | Kubfu em `BlackthornCave`; Scrolls no Battle Arcade lobby; GMAX bloqueadas |
| Palafin | 1 | 0 | Hero só em batalha |
| Maushold | 2 | 2 | Three/Four por PID |
| Tatsugiri | 5 | 1 | só **Curly** tem fonte; Droopy/Stretchy sem nenhuma |
| Dudunsparce | 2 | 2 | Two/Three-Segment por PID + `MOVE_HYPER_DRILL` |
| Gimmighoul | 2 | 2 | Chest (presente `CianwoodHouse3`), Roaming por ovo de Gholdengo |
| Tauros de Paldea | 3 | 3 | Combat/Blaze/Aqua na Safari Zone |
| Pikachu/Eevee (chapéus, trajes) | 2 | 2 | só `PIKACHU_STARTER`/`EEVEE_STARTER`; 14 formas de chapéu/Cosplay desabilitadas |
| Zarude | 1 (Dada) | 0 | Zarude normal é presente; `ZARUDE_DADA` sem gatilho |
| Pichu Spiky-Eared | 1 | 0 | sem gatilho nem fonte |
| Lugia Shadow | 1 | 1 | forma exclusiva do hack, capturável no Whirl Islands Lugia Chamber |
| Eternatus Eternamax | 1 | 0 | sem gatilho; Eternatus inobtenível |
| Totem (7) | 7 | 0 | `EVO_NONE` para Marowak/Vikavolt/Ribombee-Totem; nenhum encontro |

---

## 9. Métodos de obtenção implementados

| Método | Implementado? | Evidência |
|---|---|---|
| Encontros terrestres | ✅ | `src/data/wild_encounters.json`, campo `land_mons` |
| Surf | ✅ | `water_mons` |
| Pesca (Old/Good/Super Rod) | ✅ | `fishing_mons`, `src/fishing.c` |
| Rock Smash | ✅ | `rock_smash_mons`; itens em `sRockSmashItemTables` (`src/wild_encounter.c:133`) |
| Headbutt | ❌ | nenhuma tabela/implementação encontrada |
| Hordas | ❌ | não implementado |
| Enxames (Mass Outbreak) | ⚠️ | engine presente (`src/wild_encounter.c:675 SetUpMassOutbreakEncounter`), mas nenhum script chama `StartMassOutbreak` |
| Hidden Grottos | ✅ | `src/hidden_grotto.c`; 10 grutas alcançáveis (Route 32/33/35/38/44/47, Goldenrod Shore, Ilex, Lake of Rage, Vajra Desert West) |
| Árvores de Apricorn | ✅ (itens) | `src/apricorn_tree.c` — dá itens, não Pokémon |
| Pokémon estáticos | ✅ | `setwildbattle`, `legendaryencounter`, `seteventmon` |
| Presentes de NPC | ✅ | 49 `givemon` em mapas alcançáveis |
| Ovos de presente | ✅ | `giveegg`: Togepi (Violet PC), Pichu (`gift_pichu.inc`), Arceus (Radio Tower 2F), Jirachi (Mt. Silver Summit) |
| Iniciais | ✅ | 9 opções, `src/ui_birch_case.c:138-149` (`Task_OpenBirchCase`, `src/script.c:682`) |
| Fósseis | ✅ | Rock Smash em Ruins of Alph dá 6 fósseis; +Claw (Pewter Museum), +Old Amber (gacha); revivificação em `data/maps/RuinsOfAlph_Lab/scripts.inc` → Lileep, Anorith, Omanyte, Kabuto, Aerodactyl, Archen, Tyrunt, Amaura |
| Trocas com NPC | ✅ | 15 trocas em `src/data/trade.h` |
| Game Corner / gacha | ✅ | `src/game_corner_gacha.c` (307 espécies) |
| Eventos de roteiro | ✅ | 29 `bosslegendaryencounter`, 19 `legendaryencounter`, 12 `seteventmon` |
| Roaming | ✅ | Entei/Raikou/Suicune, `InitRoamer` em `data/maps/BurnedTower_B1F/scripts.inc:129` |
| Lendários | ✅ | ~45 encontros distintos |
| Pós-game | ✅ | Cerulean Cave, Mt. Silver, Meteor Cave, Spear Pillar, Kitakami, Vajra Pyramid, Battle Café |
| Mystery Gift | ❌ | `EnableMysteryGift()` nunca chamado |
| Reprodução (Day Care) | ✅ | Route 34 Day Care alcançável e funcional |
| Troca por link / Union Room | ❌ | nenhum Cable Club alcançável |

### 9.1 Evoluções — métodos usados na configuração habilitada

345 espécies têm `.evolutions`; 421 entradas no total:

| Método | Entradas |
|---|---|
| `EVO_LEVEL` (inclui amizade, hora, mapa, golpe, gênero, natureza, PID… via `CONDITIONS`) | 307 |
| `EVO_ITEM` | 88 |
| `EVO_TRADE` | 18 |
| `EVO_NONE` (Totems — inatingível por design) | 3 |
| `EVO_LEVEL_BATTLE_ONLY` (Tandemaus) | 2 |
| `EVO_BATTLE_END` (Farfetch'd-Galar → Sirfetch'd) | 1 |
| `EVO_SPLIT_FROM_EVO` (Nincada → Shedinja) | 1 |
| `EVO_SCRIPT_TRIGGER` (Yamask-Galar → Runerigus) | 1 |

Condições usadas: `IF_MIN_FRIENDSHIP` (17), `IF_HOLD_ITEM` (17), `IF_TIME` (16),
`IF_NOT_TIME` (14), `IF_KNOWS_MOVE` (12), `IF_GENDER` (6), `IF_WEATHER` (5),
`IF_IN_MAPSEC` (3), `IF_NOT_REGION` (3), `IF_IN_MAP` (3), `IF_USED_MOVE_X_TIMES` (2),
`IF_PID_MODULO_100_*` (4), `IF_BAG_ITEM_COUNT` (2), `IF_RECOIL_DAMAGE_GE` (2),
`IF_CRITICAL_HITS_GE`, `IF_ATK_*_DEF` (3), `IF_KNOWS_MOVE_TYPE`, `IF_SPECIES_IN_PARTY`,
`IF_MIN_BEAUTY`, `IF_CURRENT_DAMAGE_GE`, `IF_AMPED_NATURE`, `IF_LOW_KEY_NATURE`.

### 9.2 Evoluções por troca — todas com alternativa por item ✅

O projeto adicionou uma linha `EVO_ITEM` paralela a **todas** as 18 evoluções `EVO_TRADE`:

| Pré-evolução | Alternativa | Item distribuído? |
|---|---|---|
| Kadabra, Machoke, Graveler, Graveler-Alola, Haunter, Phantump | `ITEM_LINKING_CORD` | ✅ 4 fontes (Route 38 item ball, gacha, …) |
| Poliwhirl, Slowpoke | `ITEM_KINGS_ROCK` | ✅ Mahogany Shop, Mt. Mortar, Slowpoke Well |
| Onix, Scyther | `ITEM_METAL_COAT` | ✅ Mahogany Shop + item segurado |
| Rhydon | `ITEM_PROTECTOR` | ✅ Kitakami Temple Storage + item segurado (Rhyhorn/Rhydon) |
| Seadra | `ITEM_DRAGON_SCALE` | ✅ Mahogany Shop, Mt. Mortar 2F |
| Electabuzz | `ITEM_ELECTIRIZER` | ✅ **apenas** como item segurado por Elekid/Electabuzz/Electivire selvagens |
| Magmar | `ITEM_MAGMARIZER` | ✅ Rinto Village + item segurado |
| Porygon / Porygon2 | `ITEM_UPGRADE` / `ITEM_DUBIOUS_DISC` | ✅ Safari Zone Gate / Mahogany Shop |
| Feebas | `ITEM_PRISM_SCALE` | ✅ Route 47, gacha, item segurado |
| Dusclops | `ITEM_REAPER_CLOTH` | ✅ Kitakami Mountain 4F + item segurado |

> `IF_MIN_BEAUTY, 170` (Feebas → Milotic) foi tratado como **não satisfazível** (não há Pokéblocks/
> concursos acessíveis confirmados); a rota por Prism Scale torna isso irrelevante.

### 9.3 Evoluções por local / clima / hora

| Condição | Mapa/estado | Alcançável? |
|---|---|---|
| `IF_IN_MAPSEC, MAPSEC_RAILWAY_CAVE` (Magnezone, Probopass, Vikavolt) | Railway Cave | ✅ |
| `IF_IN_MAP, MAP_ILEX_FOREST` (Leafeon) | Ilex Forest | ✅ (também há Leaf Stone) |
| `IF_IN_MAP, MAP_ICE_PATH_B4F` (Glaceon) | Ice Path B4F | ✅ (também há Ice Stone) |
| `IF_IN_MAP, MAP_SNOWTOP_MOUNTAIN_B1F` (Crabominable) | Snowtop Mountain B1F | ✅ |
| `IF_WEATHER, WEATHER_RAIN/FOG` (Goodra, Sliggoo-Hisui) | 9 mapas com `WEATHER_RAIN` + 1 com `WEATHER_FOG_HORIZONTAL` alcançáveis | ✅ |
| `IF_NOT_REGION, REGION_ALOLA/GALAR` (Marowak, Weezing, Mr. Mime) | `GetCurrentRegion()` retorna sempre `REGION_HOENN` (`include/regions.h:8`) | ✅ sempre verdadeiro |
| `IF_TIME / IF_NOT_TIME` | RTC do jogo | ✅ |

### 9.4 Item evolutivo sem fonte

| Item | Afeta | Impacto real |
|---|---|---|
| `ITEM_GIMMIGHOUL_COIN` | `SPECIES_GIMMIGHOUL_ROAMING → GHOLDENGO` (`IF_BAG_ITEM_COUNT … 999`) | **Nenhum** — o hack adicionou `SPECIES_GIMMIGHOUL_CHEST → GHOLDENGO` por `EVO_LEVEL, 55` |

Também sem fonte, mas **sem impacto** por não serem usados em nenhuma evolução habilitada:
`ITEM_SACHET`, `ITEM_WHIPPED_DREAM` (Spritzee/Swirlix desabilitados),
`ITEM_BLACK_AUGURITE` **tem** fonte (Lake of Rage), `ITEM_OVAL_STONE` tem fonte apenas como
item segurado por Happiny/Chansey/Blissey selvagens.

---

## 10. Mapas e eventos inacessíveis

**551 de 1105 mapas** (`data/maps/*/map.json`) são alcançáveis a partir de `MAP_NEW_BARK_TOWN`.
Os 554 restantes são, em quase totalidade, mapas de Hoenn/Kanto herdados do pokeemerald que o hack
não conectou.

### 10.1 Mapas com tabela de encontro selvagem inacessíveis

Apenas **1**: `MAP_SOUTHERN_ISLAND_EXTERIOR` — e sua tabela contém somente `SPECIES_NONE`.
**Nenhuma espécie depende de um mapa de encontro inacessível.**

### 10.2 Mapas inacessíveis com scripts que entregam/posicionam Pokémon (29)

| Mapa | Pokémon | Existe fonte alternativa? |
|---|---|---|
| `MAP_BIRTH_ISLAND_EXTERIOR` | Deoxys | ❌ **não** — é a única fonte de Deoxys |
| `MAP_NAVEL_ROCK_BOTTOM` / `_TOP` | Lugia / Ho-Oh | ✅ Whirl Islands / Tin Tower |
| `MAP_SOUTHERN_ISLAND_INTERIOR` | Latias, Latios | ✅ Lati Temple |
| `MAP_FARAWAY_ISLAND_INTERIOR` | Mew | ✅ `MAP_FARAWAY_ISLAND_DEPTHS` |
| `MAP_MAGMA_HIDEOUT_3F_1R_ENTEI` | Entei | ✅ roamer |
| `MAP_NEW_MAUVILLE_INSIDE_RAIKOU` | Raikou | ✅ roamer |
| `MAP_SHOAL_CAVE_LOW_TIDE_ICE_ROOM_SUICUNE` | Suicune | ✅ Route 25 (`seteventmon`) |
| `MAP_METEOR_FALLS_ARTICUNO` | Articuno | ✅ Snowtop Mountain / Seafoam |
| `MAP_SCORCHED_SLAB_ZAPDOS` | Zapdos | ✅ Route 10 / Olivine Lighthouse |
| `MAP_VICTORY_ROAD_MOLTRES2` | Moltres | ✅ Victory Road Kanto B1F |
| `MAP_CERULEAN_CAVE3` | Mewtwo | ✅ `MAP_CERULEAN_CAVE_B2F` |
| `MAP_SKY_PILLAR_TOP` / `MARINE_CAVE_END` / `TERRA_CAVE_END` | Rayquaza / Kyogre / Groudon | ✅ Embedded Tower, Route 33 South Underwater Cave, Route 50 Underwater Cave 2 |
| `MAP_DESERT_RUINS` / `ISLAND_CAVE` / `ANCIENT_TOMB` | Regirock / Regice / Registeel | ✅ Regirock Chamber, Snowtop B1F-2, Railway Cave Registeel Room |
| `MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB` | Chikorita/Cyndaquil/Totodile | ✅ seleção de iniciais (`ui_birch_case.c`) |
| `MAP_GOLDENROD_CITY_GAME_CORNER` | Deino, Munchlax, Pawniard, Porygon, Sneasel-Hisui | ✅ todos disponíveis por outras vias |
| `MAP_ROUTE119_WEATHER_INSTITUTE_2F` | Castform | ⚠️ espécie desabilitada (§11) |
| `MAP_RUSTBORO_CITY_DEVON_CORP_2F` | Lileep, Anorith | ✅ Ruins of Alph Lab / selvagem |
| `MAP_MOSSDEEP_CITY_STEVENS_HOUSE` | Beldum | ✅ Safari Zone Gate |
| `MAP_LAVARIDGE_TOWN` | Wynaut (ovo) | ✅ gacha |
| `MAP_ROUTE120` | Kecleon | ✅ `data/scripts/kecleon.inc` (global) |
| `MAP_AQUA_HIDEOUT_B1F`, `MAP_NEW_MAUVILLE_INSIDE` | Electrode, Voltorb | ✅ Rocket Hideout / gacha |
| `MAP_BATTLE_FRONTIER_OUTSIDE_EAST` | Sudowoodo | ✅ Route 36 |

### 10.3 Hidden Grottos “mortas”

`src/hidden_grotto.c` declara 20 grutas. As 9 entradas `HIDDEN_GROTTO_KANTO_UNUSED1..9`
apontam todas para `MAP_HIDDEN_GROTTO_UNUSED` com o mesmo pool
(Charmander/Squirtle/Bulbasaur/Pikachu) e **nunca são selecionadas**: `GetCurrentHiddenGrottoId`
(`src/hidden_grotto.c:557`) devolve a **primeira** entrada que casa com o mapa atual, e essa é
`HIDDEN_GROTTO_VAJRA_DESERT_WEST` (índice 9), que é a gruta realmente usada
(`warp MAP_HIDDEN_GROTTO_UNUSED`, `data/maps/VajraDesert/scripts.inc:110`).
`HIDDEN_GROTTO_JOHTO_UNUSED2` (Cyndaquil/Totodile/Chikorita/**Celebi**) também é inalcançável
pelo mesmo motivo.

### 10.4 Instalações de batalha

O Battle Frontier de Hoenn (`MAP_BATTLE_FRONTIER_OUTSIDE_EAST` etc.) **não** é alcançável.
O hack usa `MAP_GOLDENROD_BATTLE_ARACDE_LOBBY` e `MAP_BATTLE_FACTORY_GROUNDS`, ambos
alcançáveis. Os Pokémon dessas instalações (`src/data/battle_frontier/battle_frontier_mons.h`,
grupos `gBattlePyramidWildMonHeaders` / `gBattlePikeWildMonHeaders`) **não** são obteníveis.

---

## 11. Inconsistências encontradas

### 11.1 Espécies **desabilitadas** ainda referenciadas por conteúdo alcançável ⚠️

**21 espécies** (das 22 constantes reportadas pelo verificador; a 22ª é `SPECIES_NONE`, §11.4)
aparecem em conteúdo cuja entrada em `gSpeciesInfo` **não é compilada** — a struct fica zerada
(sem nome, sem sprite, sem learnset). Detectadas cruzando `sources_raw.json` × `enabled_species.txt`:

| Espécie | Onde | Gravidade |
|---|---|---|
| `SPECIES_OMANYTE` | `data/maps/RuinsOfAlph_Lab/scripts.inc:538` (revivificação do Helix Fossil) | **Alta** — o Helix Fossil é obtenível por Rock Smash em Ruins of Alph |
| `SPECIES_ANORITH` | `data/maps/RuinsOfAlph_Lab/scripts.inc:448` (Claw Fossil) | **Alta** — Claw Fossil obtenível em Pewter Museum |
| `SPECIES_CASTFORM_NORMAL` | gacha (`src/game_corner_gacha.c`) | Alta |
| `SPECIES_SPINDA` | `data/maps/Route25_BillsHouse/scripts.inc:144` | Média |
| `SPECIES_LOTAD/LOMBRE/LUDICOLO`, `SEEDOT/NUZLEAF/SHIFTRY`, `SENTRET/FURRET`, `REMORAID/OCTILLERY`, `CLAMPERL/HUNTAIL/GOREBYSS`, `RELICANTH` | pools do gacha | Média — o gacha pode sortear uma espécie inexistente |
| `SPECIES_SHUCKLE` | `data/maps/CianwoodHouse3/scripts.inc:30` (`setvar VAR_TEMP_*`) | Baixa (uso como variável) |
| `SPECIES_SPEAROW` | `data/maps/Gate_GoldenrodCity_Route35/scripts.inc:36` | Baixa |
| `SPECIES_KECLEON` | `data/scripts/kecleon.inc:74` + `data/maps/Route120/scripts.inc:193` | **Baixa** — o script só é referenciado por `FortreeCity`/`Route120` (mapas inalcançáveis) |

### 11.2 Formas com dados mas **sem método de ativação**

`SPECIES_ZARUDE_DADA`, `SPECIES_PICHU_SPIKY_EARED`, `SPECIES_TATSUGIRI_DROOPY`,
`SPECIES_TATSUGIRI_STRETCHY`, `SPECIES_KYUREM_BLACK`, `SPECIES_KYUREM_WHITE`,
`SPECIES_CALYREX_ICE`, `SPECIES_CALYREX_SHADOW`, `SPECIES_NECROZMA_DUSK_MANE`,
`SPECIES_NECROZMA_DAWN_WINGS`, `SPECIES_ETERNATUS_ETERNAMAX`,
`SPECIES_MAROWAK_ALOLA_TOTEM`, `SPECIES_VIKAVOLT_TOTEM`, `SPECIES_RIBOMBEE_TOTEM`,
`SPECIES_RATICATE_ALOLA_TOTEM`, `SPECIES_KOMMO_O_TOTEM`, `SPECIES_MIMIKYU_TOTEM_DISGUISED`,
`SPECIES_MIMIKYU_BUSTED_TOTEM`.

### 11.3 Feature com engine mas sem conteúdo

* **Mass Outbreak / enxames** — `SetUpMassOutbreakEncounter` existe, `StartMassOutbreak` nunca é chamado.
* **Mystery Gift** — código completo, flag nunca setada.
* **Cable Club / Union Room / Record Corner** — mapas existem, nenhum alcançável.

### 11.4 Slots `SPECIES_NONE` em tabelas de encontro (65)

`MAP_OLIVINE_CITY_PORT_OUTSIDE` (dia+noite), `MAP_VERMILION_CITY_PORT_OUTSIDE` (dia+noite),
`MAP_SOUTHERN_ISLAND_EXTERIOR` — 12 slots terrestres cada, todos `SPECIES_NONE`;
`MAP_MT_SILVER_1F_ITEM_ROOM` — 5 slots de água. Comportamento em jogo: encontros vazios.

### 11.5 Megas customizados sem paleta de ícone própria (49)

`SPECIES_DRAGONITE_MEGA`, `SPECIES_TYPHLOSION_MEGA`… usam `.iconPalIndex` (paleta compartilhada
GBA) em vez de `.iconPalette` própria. **Não é um defeito** — é válido no engine — mas significa
que esses 49 Megas não têm paleta de ícone shiny dedicada.

### 11.6 Verificações que passaram (sem achados)

* Toda espécie **habilitada** tem `levelUpLearnset`, `frontPic`, `backPic`, `iconSprite`,
  `palette`, `shinyPalette`, `cryId`, `description`, `teachableLearnset` e `natDexNum`.
  → **Nenhuma “implementação incompleta”.**
* Nenhuma espécie aparece em tabela de encontro estando desabilitada.
* Nenhuma espécie fica bloqueada por item evolutivo ausente (exceto o caso irrelevante da §9.4).

---

## 12. Espécies existentes no código mas indisponíveis no jogo

25 constantes (24 slots de Pokédex — Oricorio é coberto pela forma Sensu). **Todas são
lendárias, míticas ou paradoxais.**

| Nº | Espécie | Const | Gen |
|---|---|---|---|
| 386 | Deoxys | `SPECIES_DEOXYS_NORMAL` | 3 |
| 643 | Reshiram | `SPECIES_RESHIRAM` | 5 |
| 644 | Zekrom | `SPECIES_ZEKROM` | 5 |
| 646 | Kyurem | `SPECIES_KYUREM` | 5 |
| 647 | Keldeo | `SPECIES_KELDEO_ORDINARY` | 5 |
| 716 | Xerneas | `SPECIES_XERNEAS_NEUTRAL` | 6 |
| 717 | Yveltal | `SPECIES_YVELTAL` | 6 |
| 718 | Zygarde | `SPECIES_ZYGARDE_50` | 6 |
| 721 | Volcanion | `SPECIES_VOLCANION` | 6 |
| 741 | Oricorio (Baile) | `SPECIES_ORICORIO_BAILE` | 7 |
| 789 | Cosmog | `SPECIES_COSMOG` | 7 |
| 790 | Cosmoem | `SPECIES_COSMOEM` | 7 |
| 791 | Solgaleo | `SPECIES_SOLGALEO` | 7 |
| 792 | Lunala | `SPECIES_LUNALA` | 7 |
| 800 | Necrozma | `SPECIES_NECROZMA` | 7 |
| 888 | Zacian | `SPECIES_ZACIAN_HERO` | 8 |
| 889 | Zamazenta | `SPECIES_ZAMAZENTA_HERO` | 8 |
| 890 | Eternatus | `SPECIES_ETERNATUS` | 8 |
| 894 | Regieleki | `SPECIES_REGIELEKI` | 8 |
| 895 | Regidrago | `SPECIES_REGIDRAGO` | 8 |
| 896 | Glastrier | `SPECIES_GLASTRIER` | 8 |
| 897 | Spectrier | `SPECIES_SPECTRIER` | 8 |
| 898 | Calyrex | `SPECIES_CALYREX` | 8 |
| 1024 | Terapagos | `SPECIES_TERAPAGOS_NORMAL` | 9 |
| 1025 | Pecharunt | `SPECIES_PECHARUNT` | 9 |

Evidência: nenhuma dessas constantes (nem seus *aliases*) aparece em
`src/data/wild_encounters.json`, `src/hidden_grotto.c`, `src/game_corner_gacha.c`,
`src/data/trade.h`, `src/roamer.c`, `src/ui_birch_case.c`, nem em qualquer
`givemon`/`giveegg`/`setwildbattle`/`legendaryencounter`/`bosslegendaryencounter`/`seteventmon`
de mapa alcançável. Deoxys aparece apenas em
`data/maps/BirthIsland_Exterior/scripts.inc:84` (mapa inalcançável), e Cosmoem/Solgaleo/Lunala
dependem de Cosmog, que não tem fonte.

---

## 13. Formas existentes mas indisponíveis

**194 formas habilitadas** não são colecionáveis permanentemente. Resumo:

| Grupo | Qtd. | Motivo |
|---|---|---|
| Mega Evolutions | 113 | Por natureza são transformações de batalha (112 **são ativáveis** em batalha) |
| Gigantamax | 14 | Dynamax desligado (`B_FLAG_DYNAMAX_BATTLE = 0`, sem `ITEM_DYNAMAX_BAND`) |
| Arceus (placas) | 17 | Placas e Cristais Z sem fonte |
| Totem | 7 | `EVO_NONE` / sem encontro |
| Formas Terastal | 5 | `ITEM_TERA_ORB` sem fonte |
| Rotom (aparelhos) | 5 | Golpes-gatilho não aprendíveis por Rotom |
| Genesect (drives) | 4 | Drives sem fonte |
| Zygarde | 4 | `ITEM_ZYGARDE_CUBE` sem fonte + espécie inobtenível |
| Deoxys | 3 | `ITEM_METEORITE` sem fonte + espécie inobtenível |
| Necrozma / Kyurem / Calyrex fusões | 6 | Itens de fusão sem fonte + espécies inobteníveis |
| Zacian/Zamazenta Crowned, Xerneas Active, Eternamax | 4 | Itens ausentes / espécies inobteníveis |
| Dialga Origin, Palkia Origin | 0 | ✅ **obteníveis** via Adamant/Lustrous Orb |
| Primal Groudon/Kyogre | 2 | transformação de batalha (ativável, Red/Blue Orb distribuídos) |
| Formas de batalha (Aegislash, Mimikyu, Darmanitan-Zen, Meloetta-Pirouette, Greninja-Ash, Palafin-Hero) | 8 | por design, revertem no fim da batalha |
| Tatsugiri Droopy/Stretchy, Zarude Dada, Pichu Spiky-Eared | 4 | sem gatilho nem fonte |
| Restante (formas base de grupos, ex.: Oricorio Baile/Pom-Pom/Pa'u alcançáveis por néctar) | ~8 | ver CSV |

Além disso, **216 formas estão desabilitadas por configuração** (todas as formas das 181 famílias
desligadas + Cosplay/Cap Pikachu).

---

## 14. Conteúdo dependente de flags/configs desativadas

| Recurso | O que já existe no repo | O que a flag habilita | Basta ligar a flag? |
|---|---|---|---|
| **Dynamax / Gigantamax** | 22 formas G-Max com sprites, paletas, ícones, cries; `src/battle_dynamax.c` completo; gráficos em `graphics/gimmicks`; `GIMMICK_DYNAMAX` registrado em `src/data/gimmicks.h` | `B_FLAG_DYNAMAX_BATTLE = <flag>` liga o gatilho | **Não.** Também é preciso **distribuir `ITEM_DYNAMAX_BAND`** (nenhuma fonte) e setar a flag por script. Depois disso as 14 G-Max habilitadas ficam ativáveis em batalha — mas continuam **não colecionáveis** |
| **Terastalização** | `src/battle_terastal.c`, `GIMMICK_TERA`, formas `*_TERA` de Ogerpon, `SPECIES_TERAPAGOS_TERASTAL/STELLAR`, `P_TERA_FORMS = TRUE` | `B_FLAG_TERA_ORB_CHARGED` só controla a recarga | **Não.** É preciso **distribuir `ITEM_TERA_ORB`** (`src/battle_terastal.c:76` exige o item na mochila). `P_SHOW_TERA_TYPE = GEN_8` também esconde o tipo Tera no sumário |
| **Ultra Burst** | `SPECIES_NECROZMA_ULTRA`, `GIMMICK_ULTRA_BURST`, `P_ULTRA_BURST_FORMS = TRUE` | — | **Não.** Falta `ITEM_ULTRANECROZIUM_Z` **e** Necrozma obtenível |
| **Z-Moves** | `src/battle_z_move.c`, `GIMMICK_Z_MOVE`, 18 `ITEM_*IUM_Z` definidos | — | **Não.** Nenhum Cristal Z é distribuído |
| **Formas de Arceus / Silvally** | 18 formas Arceus (habilitadas) + 18 Silvally (desabilitadas) | `P_FAMILY_SILVALLY`/`P_FAMILY_TYPE_NULL` | **Não.** Faltam as 17 Placas e as 17 Memories |
| **Genesect Drives** | 4 formas | — | **Não.** Faltam os 4 Drives |
| **Fusões (Kyurem/Necrozma/Calyrex)** | `P_FUSION_FORMS = TRUE`, formas presentes | — | **Não.** Faltam `ITEM_DNA_SPLICERS`, `ITEM_N_SOLARIZER`, `ITEM_N_LUNARIZER`, `ITEM_REINS_OF_UNITY` **e** as espécies-base |
| **Zygarde Cube** | 5 formas Zygarde + `ZYGARDE_MEGA` | — | **Não.** Falta `ITEM_ZYGARDE_CUBE` e Zygarde |
| **Zacian/Zamazenta Crowned** | 2 formas | — | **Não.** Faltam Rusted Sword/Shield e as espécies |
| **Cosplay / Cap Pikachu** | 14 formas com sprites completos | `P_PIKACHU_EXTRA_FORMS = TRUE` | **Parcialmente.** Ligar a flag as compila, mas continuam sem método de obtenção (precisariam de eventos/Mystery Gift) |
| **181 famílias desligadas** | dados, sprites, learnsets, cries completos no repo | `P_FAMILY_X = P_GEN_N_POKEMON` | **Parcialmente.** Ligar a flag as compila e as adiciona à Johto Dex; a maioria precisaria também de encontros/scripts para virar obtenível (algumas já são referenciadas — §11.1 — e passariam a funcionar imediatamente) |
| **Mystery Gift** | UI e código completos | `FLAG_SYS_MYSTERY_GIFT_ENABLE` | **Não.** É preciso chamar `EnableMysteryGift()` de algum script |
| **Mass Outbreak** | engine em `src/wild_encounter.c` | — | **Não.** Falta chamar `StartMassOutbreak` e definir conteúdo |

---

## 15. Evoluções bloqueadas ou problemáticas

| Caso | Situação |
|---|---|
| Todas as 18 `EVO_TRADE` | ✅ Resolvidas por alternativa `EVO_ITEM` (§9.2) |
| `SPECIES_GIMMIGHOUL_ROAMING → GHOLDENGO` | ⚠️ `ITEM_GIMMIGHOUL_COIN` sem fonte — **sem impacto** (rota por nível existe no Chest) |
| `SPECIES_CUBONE → MAROWAK_ALOLA_TOTEM` (`EVO_NONE`) | 🔒 Inatingível por design |
| `SPECIES_CHARJABUG → VIKAVOLT_TOTEM` (`EVO_NONE`) | 🔒 Inatingível por design |
| `SPECIES_CUTIEFLY → RIBOMBEE_TOTEM` (`EVO_NONE`) | 🔒 Inatingível por design |
| `SPECIES_FEEBAS → MILOTIC` por `IF_MIN_BEAUTY, 170` | ⚠️ Beleza dificilmente alcançável — rota por `ITEM_PRISM_SCALE` disponível |
| `SPECIES_COSMOEM → SOLGALEO/LUNALA` | 🔒 Pré-evolução (Cosmog) inobtenível |
| `SPECIES_YAMASK_GALAR → RUNERIGUS` (`EVO_SCRIPT_TRIGGER`) | ✅ O hack adicionou `EVO_LEVEL, 34` como alternativa |
| `SPECIES_DUNSPARCE → DUDUNSPARCE_*` (`IF_KNOWS_MOVE, MOVE_HYPER_DRILL`) | ✅ Dunsparce aprende Hyper Drill no learnset Gen 9 |
| `SPECIES_PRIMEAPE → ANNIHILAPE` (`IF_USED_MOVE_X_TIMES, MOVE_RAGE_FIST, 20`) | ✅ funcional |
| `SPECIES_STANTLER → WYRDEER` (`MOVE_PSYSHIELD_BASH, 14×`) | ✅ funcional |
| `SPECIES_BASCULIN_WHITE_STRIPED → BASCULEGION_*` (`IF_RECOIL_DAMAGE_GE, 294`) | ✅ funcional (além disso ambos aparecem selvagens) |
| `SPECIES_HAPPINY → CHANSEY` (`ITEM_OVAL_STONE`) | ✅ Oval Stone só como item segurado por Chansey/Blissey selvagens — funciona, mas é obscuro |
| `SPECIES_ELECTABUZZ → ELECTIVIRE` (`ITEM_ELECTIRIZER`) | ✅ Electirizer só como item segurado por Elekid/Electabuzz selvagens — funciona, mas é obscuro |
| `SPECIES_DURALUDON → ARCHALUDON` (`ITEM_METAL_ALLOY`) | ✅ Metal Alloy vem segurado pelo Meltan da troca (`src/data/trade.h:1124`) e por Duraludon selvagem |

Não há nenhuma evolução cuja pré-evolução seja indisponível **e** que a espécie evoluída não tenha
outra fonte — exceto a linha Cosmog.

---

## 16. Conclusões

### 16.1 Pokédex completa num único save? **Não.**

* Pokédex configurada (`JOHTO_DEX`): **702 espécies**.
* Máximo alcançável: **678**.
* **Faltam 24** (§12) — todas lendárias/míticas sem qualquer fonte no jogo.
* Nenhum dos 24 casos é *mutuamente exclusivo* nem depende de escolha do jogador: são
  simplesmente conteúdo não implementado.
* As 9 escolhas de inicial **não** impedem a Pokédex: as 9 espécies iniciais também aparecem
  no gacha do Game Corner e/ou em Hidden Grottos, então nada é perdido por escolher um inicial.
* Não há espécies mutuamente exclusivas num mesmo save (não existem versões/exclusivos de versão).

### 16.2 Todas as formas num único save? **Não.**

* **142 de 336** formas habilitadas são colecionáveis permanentemente.
* **127 de 149** transformações de batalha são ativáveis.
* Bloqueios estruturais: Dynamax desligado, Tera Orb ausente, Placas/Memories/Drives/Cristais Z
  ausentes, itens de fusão ausentes, golpes-gatilho do Rotom não aprendíveis.

### 16.3 Resposta às duas definições de “disponível”

| | A. Existe no repositório | B. Pode ser conseguido no jogo |
|---|---|---|
| Espécies-base | **1025** (todas as 1025 do dex nacional) | **677** (678 slots) |
| Espécies-base compiladas | **702** | **677** |
| Formas | **552** | **142** permanentes + **127** transformações de batalha |
| Formas compiladas | **336** | idem |

---

## 17. Resumo quantitativo obrigatório

| Métrica | Valor | Como foi calculado |
|---|---|---|
| Total de espécies-base encontradas | **1025** | Entradas `[SPECIES_X] =` em `species_info/gen_*_families.h` cuja `formSpeciesIdTable` (se houver) tem essa espécie como primeiro elemento; confere com `NATIONAL_DEX_COUNT` |
| Total de espécies-base habilitadas | **702** | Sobreviventes ao pré-processador com a config real; confere com `JOHTO_DEX_COUNT − 1` |
| Total de espécies-base obteníveis | **677** (**678** slots de Pokédex) | Ponto-fixo: fonte direta em mapa alcançável ∪ evolução válida ∪ reprodução |
| Total de espécies-base não obteníveis (habilitadas) | **25** constantes / **24** slots | 702 − 677; Oricorio coberto pela forma Sensu |
| Total de espécies-base desabilitadas | **323** | 1025 − 702 |
| Total de formas encontradas | **552** | 1577 entradas − 1025 bases |
| Total de formas habilitadas | **336** | pré-processador |
| Total de formas obteníveis (permanentes) | **142** | fonte direta ∪ evolução ∪ reprodução ∪ mudança de forma persistente com item distribuído |
| Total de formas só como dados / batalha temporária | **194** | 336 − 142 |
| Total de formas desabilitadas por configuração | **216** | 552 − 336 |
| Transformações de batalha ativáveis | **127** | gatilho de batalha + item distribuído + espécie-base obtenível |
| Transformações de batalha bloqueadas | **22** | ver §7.2 |
| Total dependente de configs desativadas | **323 espécies + 216 formas** | famílias `P_FAMILY_* = FALSE` + `P_PIKACHU_EXTRA_FORMS = FALSE` |
| Total de casos “Incerto” | **0** espécies-base; **0** formas | todas as conclusões têm evidência direta (a única ressalva metodológica é a §8.3) |
| Necessário para completar a Pokédex configurada | **702** | `JOHTO_DEX_COUNT − 1` |
| Realmente alcançável em um único save | **678** | §16.1 |
| **Déficit da Pokédex** | **24** | 702 − 678 |

> **Formas nunca foram contadas como espécies-base.** Uma espécie é “base” se e somente se
> `GET_BASE_SPECIES_ID(x) == x`, ou seja, se ela é o primeiro elemento da sua
> `formSpeciesIdTable` (ou não pertence a nenhuma). Isso produz exatamente 1025 bases, igual ao
> `NATIONAL_DEX_COUNT` do projeto — validação cruzada independente.

---

## 18. Recomendações de implementação

Ordenadas por custo/benefício.

### Prioridade 1 — Corrigir inconsistências (baixo custo, alto impacto)

1. **Fósseis quebrados.** `SPECIES_OMANYTE` e `SPECIES_ANORITH` estão desabilitados mas são
   entregues pela revivificação em `RuinsOfAlph_Lab`. Ou ligar `P_FAMILY_OMANYTE`/`P_FAMILY_ANORITH`,
   ou remover Helix/Claw Fossil das fontes (`sRockSmashItems_RuinsOfAlph`,
   `PewterCity_Museum_1F`) e do menu do laboratório.
2. **Pools do gacha.** Remover (ou reabilitar) as ~15 espécies desabilitadas listadas em §11.1
   de `src/game_corner_gacha.c`; hoje o gacha pode sortear uma espécie sem dados.
3. **Castform.** Ou ligar `P_FAMILY_CASTFORM`, ou remover das pools/scripts.
4. **Kecleon.** `data/scripts/kecleon.inc` é global e alcançável, mas `P_FAMILY_KECLEON = FALSE`.
5. **Slots `SPECIES_NONE`** nas tabelas de Olivine/Vermilion Port e Mt. Silver Item Room.

### Prioridade 2 — Tornar as 24 lendárias obteníveis

Todas já têm dados completos; falta só conteúdo. Sugestões de baixo custo, aproveitando mapas
que já existem e são alcançáveis:

| Espécie | Sugestão |
|---|---|
| Deoxys | conectar `MAP_BIRTH_ISLAND_EXTERIOR` (script já pronto) ou reusar `MAP_METEOR_CAVE2` + distribuir `ITEM_METEORITE` para as 4 formas |
| Reshiram / Zekrom / Kyurem | `bosslegendaryencounter` em `MAP_VAJRA_PYRAMID_*` ou `MAP_METEOR_CAVE*`; distribuir `ITEM_DNA_SPLICERS` para Black/White |
| Xerneas / Yveltal / Zygarde | `legendaryencounter` em Kitakami/Foggy Forest; distribuir `ITEM_ZYGARDE_CUBE` |
| Keldeo | encontro após capturar Cobalion/Terrakion/Virizion (todos já obteníveis) |
| Volcanion | evento pós-game; nenhuma dependência de item |
| Cosmog → Solgaleo/Lunala | um único presente de Cosmog resolve 4 slots (Cosmog, Cosmoem, Solgaleo, Lunala) |
| Necrozma | encontro + `ITEM_N_SOLARIZER`/`N_LUNARIZER`/`ULTRANECROZIUM_Z` para as formas |
| Zacian / Zamazenta / Eternatus | encontro + `ITEM_RUSTED_SWORD`/`RUSTED_SHIELD` |
| Regieleki / Regidrago | reusar o padrão das câmaras dos Regis já existentes |
| Glastrier / Spectrier / Calyrex | um evento resolve 3 slots + 2 formas (com `ITEM_REINS_OF_UNITY`) |
| Terapagos / Pecharunt | encontro pós-game |

### Prioridade 3 — Formas

1. **Rotom** — trocar a tabela para `FORM_CHANGE_ITEM_USE_MULTICHOICE` com `ITEM_ROTOM_CATALOG`
   (e distribuir o item), **ou** adicionar Overheat/Hydro Pump/Blizzard/Air Slash/Leaf Storm à
   lista de aprendizado de Rotom em `src/data/pokemon/all_learnables.json`.
2. **Arceus** — distribuir as 17 Placas (ex.: uma por área/prêmio do Battle Arcade): +17 formas.
3. **Genesect** — distribuir os 4 Drives: +4 formas.
4. **Dynamax** — atribuir uma flag real a `B_FLAG_DYNAMAX_BATTLE`, distribuir
   `ITEM_DYNAMAX_BAND` e setar a flag num evento: destrava 14 G-Max.
5. **Terastalização** — distribuir `ITEM_TERA_ORB`: destrava as 5 formas Tera
   (e o Ogerpon-Tera passa a funcionar pelo gatilho “correto”).
6. **Tatsugiri Droopy/Stretchy** — adicioná-los à tabela de encontro junto com Curly.
7. **Zarude Dada / Pichu Spiky-Eared** — dar um `givemon` direto (são formas de evento).
8. **Totem** — se forem desejados, precisam de encontros dedicados (as evoluções `EVO_NONE` nunca
   disparam).

### Prioridade 4 — Higiene

* Remover ou reaproveitar as 9 `HIDDEN_GROTTO_KANTO_UNUSED*` (código morto) e mover
  `HIDDEN_GROTTO_VAJRA_DESERT_WEST` para um `MAP_HIDDEN_GROTTO_VAJRA_DESERT_WEST` próprio.
* Aproveitar `HIDDEN_GROTTO_JOHTO_UNUSED2` (contém Celebi) ou removê-la.
* Remover os ~554 mapas de Hoenn/Kanto órfãos, ou documentá-los como intencionalmente inativos.
* Habilitar Mystery Gift (`EnableMysteryGift()`) se houver intenção de distribuir eventos.

---

## 19. Apêndice — comandos, scripts e buscas utilizados

Todos os scripts de análise foram criados **fora** do repositório, em
`$SCRATCH = /tmp/claude-1000/.../scratchpad/audit`, e não foram adicionados ao Git.

### 19.1 Resolução da configuração (pré-processador)

```bash
# Wrapper usado em todas as resoluções
cat > $SCRATCH/pp.sh <<'EOF'
#!/bin/bash
gcc -E -P -nostdinc -DTRUE=1 -DFALSE=0 \
  -I /home/ADMIN/decomps/soulgold/include \
  -I /home/ADMIN/decomps/soulgold "$1" -o "$2" 2>/dev/null
EOF
chmod +x $SCRATCH/pp.sh
```

* `extract_skel3.py` — extrai de `species_info/gen_*_families.h` apenas as diretivas
  `#if/#elif/#else/#endif` + marcadores `@@SPECIES@@` e blocos `@@EVOSTART@@ … @@EVOEND@@`
  (preservando condicionais aninhadas dentro de `.evolutions`).
  → 1038/1577 espécies habilitadas, 345 definições de evolução.
* `fst_in.h` / `fct_in.h` — `form_species_tables.h` e `form_change_tables.h` precedidos dos
  headers de config → 214 tabelas de forma e 159 tabelas de mudança de forma habilitadas.
* `dex.h` — `constants/pokedex.h` → `NATIONAL_DEX_COUNT = NATIONAL_DEX_PECHARUNT` (1025),
  `JOHTO_DEX_COUNT = 703`.
* `spid.h` — resolve os 1676 identificadores `SPECIES_*` para IDs numéricos
  (nomes passados como *string literal* para não serem expandidos pelo cpp).

### 19.2 Grafo de mapas

* `mapgraph3.py` — lê os 1105 `data/maps/*/map.json` (`connections`, `warp_events`) + todos os
  comandos de warp dos `scripts.inc`; BFS a partir de `MAP_NEW_BARK_TOWN`.
  → **551 mapas alcançáveis**.

Regex de warp usada:
```
^\s*([a-z_]*warp[a-z_]*)\s+(MAP_[A-Z0-9_]+)
```
(cobre `warp`, `warpsilent`, `warpwhitefade`, `warphole`, `warpteleport`, `warpdoor`,
`warpspinenter`, `warpmossdeepgym`, `setwarp`, `setdivewarp`, `setdynamicwarp`,
`setescapewarp`, `setholewarp`).

### 19.3 Coleta de fontes

* `collect.py` — encontros selvagens, Hidden Grottos, gacha, scripts de mapa, trocas, roamers, iniciais.
* `items2.py` — fontes de itens (scripts, lojas `.2byte ITEM_*`, eventos de `map.json`, grottos).
* `wild_held_items.json` / `trade_held_items.json` — itens obtidos de Pokémon selvagens
  (`.itemCommon`/`.itemRare`) e de Pokémon de troca (`.heldItem`).

Buscas globais representativas:

```bash
# comandos de script que recebem uma espécie
grep -rhoE "^\s+[a-z_]+ +SPECIES_[A-Z0-9_]+" data/maps/*/scripts.inc data/scripts/*.inc \
  | awk '{print $1}' | sort | uniq -c | sort -rn
# → playmoncry 271, givemon 90, setwildbattle 49, bosslegendaryencounter 29,
#   checkspecies 21, legendaryencounter 19, getcaughtmon 14, seteventmon 12, giveegg 8 …

# famílias desabilitadas
grep -E '^#define\s+P_FAMILY_\w+\s+FALSE' include/config/species_enabled.h | wc -l   # 181

# gimmicks
grep -n "B_FLAG_DYNAMAX_BATTLE\|B_FLAG_TERA_ORB" include/config/battle.h
grep -rn "ITEM_TERA_ORB\|ITEM_DYNAMAX_BAND" src/ data/

# métodos de mudança de forma habilitados
grep -oE "FORM_CHANGE_[A-Z_]+" $SCRATCH/fct_out.txt | sort | uniq -c | sort -rn
```

### 19.4 Análise de obtenibilidade

* `analyze.py` — ponto-fixo sobre fontes diretas + evolução + reprodução, validando itens,
  mapas e espécies exigidas.
* `export2.py` / `export_forms.py` — geram os dois CSV anexos.
* `checks.py` / `formstats.py` — verificações de consistência e estatísticas.

### 19.5 Verificações de consistência executadas

| Verificação | Resultado |
|---|---|
| Espécie existe mas não aparece em nenhuma fonte | 25 (§12) |
| Espécie aparece em conteúdo alcançável mas está desabilitada | 21 espécies + `SPECIES_NONE` (§11.1) |
| Forma tem dados mas não tem método de ativação | 18 (§11.2) |
| Evolução exige item nunca distribuído | 1 (`ITEM_GIMMIGHOUL_COIN`, sem impacto) |
| Espécie só originável de outra espécie indisponível | 3 (Cosmoem, Solgaleo, Lunala) |
| Mapa possui encontros mas é inacessível | 1 (só com `SPECIES_NONE`) |
| Conteúdo protegido por `#if` desativado | 323 espécies + 216 formas |
| Espécie habilitada com dados incompletos | 0 |

### 19.6 Anexos

| Arquivo | Conteúdo |
|---|---|
| `docs/POKEMON_AVAILABILITY_SPECIES.csv` | 1025 espécies-base, uma por linha |
| `docs/POKEMON_AVAILABILITY_FORMS.csv` | 552 formas, uma por linha |

