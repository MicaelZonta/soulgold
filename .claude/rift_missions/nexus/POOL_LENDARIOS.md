# Pool de lendários — o que existe no jogo e como se obtém

Levantamento de todas as espécies **lendárias, míticas e "únicas"** que o engine tem
ativas neste hack, e de **qual delas o jogador consegue obter hoje**. Serve de
base para o pool do loop pós-Necrozma (design §10) e para as fichas do [Nexus](README.md).

Conferido no código em 25/09/2026.

## Critérios

- **Quem entra.** Toda espécie com `isRestrictedLegendary`, `isSubLegendary`, `isMythical`, `isUltraBeast` ou `isParadox` em `src/data/pokemon/species_info/` (as 9 gerações estão ligadas em `species_enabled.h`). "Único" aqui = **Ultra Beasts e Paradoxos**, as duas categorias especiais que não são lendário nem mítico. Formas (Mega, Primal, Origin, Therian, Gmax, Tera…) contam dentro da espécie; as **aves de Galar** ficam separadas porque são outro Pokémon.
- **O que conta como método:** encontro estático (`legendaryencounter`, `bosslegendaryencounter*`, `setwildbattle`, `seteventmon` com captura liberada), selvagem (`wild_encounters.json`), presente (`givemon`/`giveegg`), recompensa do Battle Café, troca in-game, roamer, evolução ou breeding a partir de algo obtível.
- **O que não conta:** batalha com `B_FLAG_NO_CATCHING` (as UBs das Rift Missions e o Ultra Necrozma), e método em mapa **inalcançável**.
- **Alcançável** = existe caminho de warps/conexões/`warp` de script a partir do quarto do jogador (554 de 1105 mapas da ROM). Os mapas de Hoenn herdados do Emerald (Navel Rock, Birth Island, Sky Pillar, Terra/Marine Cave, New Mauville…) caem fora. **Não** conferi se a cena está liberada pela história; só que o mapa é visitável.

## Resumo

| | Espécies |
|---|---|
| ✅ Tem método | **96** |
| ⚠️ Só em mapa inalcançável | **1** |
| 🚫 Só batalha sem captura | **9** |
| ❌ Nenhum método | **22** |
| **Total** | **128** |

| Categoria | Total | ✅ | Sem método (⚠️ + 🚫 + ❌) |
|---|---|---|---|
| Lendário restrito | 27 | 16 | 11 |
| Sub-lendário | 47 | 39 | 8 |
| Mítico | 23 | 19 | 4 |
| Ultra Beast | 11 | 2 | 9 |
| Paradoxo | 20 | 20 | 0 |

## Sem método de obtenção

Estes são os candidatos naturais para o pool do loop: existem no jogo e o jogador não tem como pegar.

| Espécie | Categoria | Situação |
|---|---|---|
| **Deoxys** | Mítico | ⚠️ só em mapa inalcançável: `BirthIsland_Exterior` |
| **Reshiram** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Zekrom** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Kyurem** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Keldeo** | Mítico | ❌ nenhuma referência de obtenção no código |
| **Xerneas** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Yveltal** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Zygarde** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Volcanion** | Mítico | ❌ nenhuma referência de obtenção no código |
| **Nihilego** | Ultra Beast | 🚫 só aparece em batalha sem captura: `NewBarkTown` |
| **Buzzwole** | Ultra Beast | 🚫 só aparece em batalha sem captura: `BlackthornCity` |
| **Pheromosa** | Ultra Beast | 🚫 só aparece em batalha sem captura: `BlackthornCity` |
| **Xurkitree** | Ultra Beast | 🚫 só aparece em batalha sem captura: `Mahoganytown` |
| **Celesteela** | Ultra Beast | 🚫 só aparece em batalha sem captura: `Mahoganytown` |
| **Kartana** | Ultra Beast | 🚫 só aparece em batalha sem captura: `NewBarkTown` |
| **Guzzlord** | Ultra Beast | 🚫 só aparece em batalha sem captura: `NewBarkTown` |
| **Stakataka** | Ultra Beast | 🚫 só aparece em batalha sem captura: `CherrygroveCity` |
| **Blacephalon** | Ultra Beast | 🚫 só aparece em batalha sem captura: `CherrygroveCity` |
| **Zacian** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Zamazenta** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Eternatus** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Regieleki** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Regidrago** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Glastrier** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Spectrier** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Calyrex** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Wo-Chien** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Ting-Lu** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Okidogi** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Munkidori** | Sub-lendário | ❌ nenhuma referência de obtenção no código |
| **Terapagos** | Lendário restrito | ❌ nenhuma referência de obtenção no código |
| **Pecharunt** | Mítico | ❌ nenhuma referência de obtenção no código |

## Com método de obtenção

### Lendário restrito

| Espécie | Como obter | Formas no engine |
|---|---|---|
| **Mewtwo** | boss (bosslegendaryencounter) — `CeruleanCave_B2F` Lv80; encontro estático (seteventmon) — `CeruleanCave_B2F` Lv80 | MEWTWO, MEWTWO_MEGA_X, MEWTWO_MEGA_Y |
| **Lugia** | boss (bosslegendaryencounter) — `WhirlIslands_LugiaChamber` Lv65; boss (bosslegendaryencounter) — `WhirlIslands_LugiaChamber` Lv80 | LUGIA, LUGIA_SHADOW |
| **Ho-Oh** | boss (bosslegendaryencounter) — `TinTower_RoofDay` Lv65; boss (bosslegendaryencounter) — `TinTower_RoofDay` Lv80 |  |
| **Kyogre** | encontro estático — `EmbeddedTower` Lv70; boss (bosslegendaryencounter) — `Route33South_UnderwaterCave` Lv80 | KYOGRE, KYOGRE_PRIMAL |
| **Groudon** | encontro estático — `EmbeddedTower` Lv70; boss (bosslegendaryencounter) — `Route50UnderwaterCave2` Lv80 | GROUDON, GROUDON_PRIMAL |
| **Rayquaza** | boss (bosslegendaryencounter) — `EmbeddedTower` Lv70 | RAYQUAZA, RAYQUAZA_MEGA |
| **Dialga** | boss (bosslegendaryencounter) — `SpearPillarTop` Lv85 | DIALGA, DIALGA_ORIGIN, DIALGA_PRIMAL |
| **Palkia** | boss (bosslegendaryencounter) — `SpearPillarTop` Lv85 | PALKIA, PALKIA_ORIGIN |
| **Giratina** | boss (bosslegendaryencounter) — `SpearPillarTop` Lv85 | GIRATINA_ALTERED, GIRATINA_ORIGIN |
| **Cosmog** | ovo (giveegg) — `VioletCity_PokemonCenter` |  |
| **Cosmoem** | evolui de Cosmog (Lv43) |  |
| **Solgaleo** | evolui de Cosmoem (Lv53) |  |
| **Lunala** | evolui de Cosmoem (Lv53) |  |
| **Necrozma** | presente (givemon) — `UltraSpaceArena` Lv75 | NECROZMA, NECROZMA_DUSK_MANE, NECROZMA_DAWN_WINGS, NECROZMA_ULTRA |
| **Koraidon** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Miraidon** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |

### Sub-lendário

| Espécie | Como obter | Formas no engine |
|---|---|---|
| **Silvally** | evolui de Type Null (amizade) |  |
| **Ogerpon** | boss (bosslegendaryencounter) — `KitakamiMountainEnclave` Lv55 |  |
| **Articuno** | encontro estático (seteventmon) — `SeafoamIslands_B1F` Lv50; encontro estático — `SnowtopMountainOutside` Lv50 |  |
| **Articuno de Galar** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Zapdos** | encontro estático — `OlivineCity_LighthouseTop` Lv50; encontro estático (seteventmon) — `Route10` Lv50 |  |
| **Zapdos de Galar** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Moltres** | encontro estático — `VictoryRoadKanto_B1F` Lv60 |  |
| **Moltres de Galar** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Raikou** | roamer (após Burned Tower / Hall of Fame) — `BurnedTower_B1F` |  |
| **Entei** | roamer (após Burned Tower / Hall of Fame) — `BurnedTower_B1F` |  |
| **Suicune** | encontro estático (seteventmon) — `Route25` Lv50; roamer (após Burned Tower / Hall of Fame) — `BurnedTower_B1F` |  |
| **Regirock** | encontro estático — `RegirockChamber` Lv50 |  |
| **Regice** | encontro estático — `SnowtopMountain_B1F_2` Lv50 |  |
| **Registeel** | encontro estático — `RailwayCave_Registeel_Room` Lv50 |  |
| **Latias** | boss (bosslegendaryencounter) — `LatiTempleLatias` Lv80 | LATIAS, LATIAS_MEGA |
| **Latios** | boss (bosslegendaryencounter) — `LatiTempleLatios` Lv80 | LATIOS, LATIOS_MEGA |
| **Uxie** | encontro estático — `AcuityCavern` Lv50 |  |
| **Mesprit** | encontro estático — `VerityCavern` Lv50 |  |
| **Azelf** | encontro estático — `ValorCavern` Lv50 |  |
| **Heatran** | boss (bosslegendaryencounter) — `MtMortar_Depths_1` Lv70 | HEATRAN, HEATRAN_MEGA |
| **Regigigas** | boss (bosslegendaryencounter) — `MtSilver_1F_RegigigasRoom` Lv70 |  |
| **Cresselia** | boss (bosslegendaryencounter) — `LakeOfRageCresseliaDen` Lv60 |  |
| **Cobalion** | boss (bosslegendaryencounter) — `RailwayCave_3F` Lv80 |  |
| **Terrakion** | boss (bosslegendaryencounter) — `DarkCave_NorthSide` Lv80 |  |
| **Virizion** | boss (bosslegendaryencounter) — `Route50` Lv80 |  |
| **Tornadus** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` | TORNADUS_INCARNATE, TORNADUS_THERIAN |
| **Thundurus** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` | THUNDURUS_INCARNATE, THUNDURUS_THERIAN |
| **Landorus** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` | LANDORUS_INCARNATE, LANDORUS_THERIAN |
| **Type: Null** | presente (givemon) — `BlackthornCity` Lv50 |  |
| **Tapu Koko** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Tapu Lele** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Tapu Bulu** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Tapu Fini** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` |  |
| **Kubfu** | presente (givemon) — `BlackthornCave` Lv5 |  |
| **Urshifu** | evolui de Kubfu (item ITEM_SCROLL_OF_DARKNESS); evolui de Kubfu (item ITEM_SCROLL_OF_WATERS) | URSHIFU_SINGLE_STRIKE, URSHIFU_SINGLE_STRIKE_GMAX, URSHIFU_RAPID_STRIKE, URSHIFU_RAPID_STRIKE_GMAX |
| **Enamorus** | recompensa do Battle Café (5 pontos, Lv70) — `BattleCafe` | ENAMORUS_INCARNATE, ENAMORUS_THERIAN |
| **Chien-Pao** | boss (bosslegendaryencounter) — `IcePath_Depths2` Lv70 |  |
| **Chi-Yu** | selvagem (fishing) — `BattleCafe` Lv60-60 |  |
| **Fezandipiti** | encontro estático — `KitakamiWell_B1F` Lv55 |  |

### Mítico

| Espécie | Como obter | Formas no engine |
|---|---|---|
| **Arceus** | ovo (giveegg) — `GoldenrodCity_RadioTower_2F` |  |
| **Genesect** | boss (bosslegendaryencounter) — `AbandonedRocketHideoutBackroom` Lv70 |  |
| **Mew** | encontro estático — `FarawayIslandDepths` Lv55 |  |
| **Celebi** | encontro estático (seteventmon) — `IlexForest` Lv40 |  |
| **Jirachi** | ovo (giveegg) — `MtSilver_SummitDay` |  |
| **Phione** | selvagem (fishing) — `Route33South_2` Lv5-5; selvagem (fishing) — `Route33South_2` Lv40-45; breeding: ovo de Manaphy |  |
| **Manaphy** | evolui de Phione (Lv58) |  |
| **Darkrai** | boss (bosslegendaryencounter) — `DarkraiInnFinalRoom` Lv70 | DARKRAI, DARKRAI_MEGA |
| **Shaymin** | encontro estático — `DreamGarden` Lv50 | SHAYMIN_LAND, SHAYMIN_SKY |
| **Victini** | presente (givemon) — `KitakamiRoad_House` Lv50 |  |
| **Meloetta** | encontro estático — `EcruteakCity_Theater` Lv65 | MELOETTA_ARIA, MELOETTA_PIROUETTE |
| **Diancie** | presente (givemon) — `BattleCafe` Lv70 | DIANCIE, DIANCIE_MEGA |
| **Hoopa** | boss (bosslegendaryencounter) — `VajraPyramidFinalChamber` Lv80 | HOOPA_CONFINED, HOOPA_UNBOUND |
| **Magearna** | boss (bosslegendaryencounter) — `GoldenrodApartment` Lv75; presente (givemon) — `Route40_House4` Lv80 | MAGEARNA, MAGEARNA_ORIGINAL, MAGEARNA_MEGA, MAGEARNA_ORIGINAL_MEGA |
| **Marshadow** | encontro estático — `SproutTower_Basement` Lv50 |  |
| **Zeraora** | boss (bosslegendaryencounter) — `TrainerHill_Courtyard` Lv80 | ZERAORA, ZERAORA_MEGA |
| **Meltan** | troca in-game — `RintoHouse3` |  |
| **Melmetal** | evolui de Meltan (Lv60) | MELMETAL, MELMETAL_GMAX |
| **Zarude** | presente (givemon) — `Route40_House4` Lv50 | ZARUDE, ZARUDE_DADA |

### Ultra Beast

| Espécie | Como obter | Formas no engine |
|---|---|---|
| **Poipole** | presente (givemon) — `Route40_House4` Lv5 |  |
| **Naganadel** | evolui de Poipole (Lv50) |  |

### Paradoxo

| Espécie | Como obter | Formas no engine |
|---|---|---|
| **Great Tusk** | selvagem (land) — `MeteorCave1` Lv56-59 |  |
| **Scream Tail** | selvagem (land) — `MeteorCave1` Lv56-59 |  |
| **Brute Bonnet** | selvagem (land) — `MeteorCave1` Lv56-59 |  |
| **Flutter Mane** | encontro estático — `MeteorCave1` Lv70 |  |
| **Slither Wing** | selvagem (land) — `MeteorCave1` Lv57-60 |  |
| **Sandy Shocks** | selvagem (land) — `MeteorCave1` Lv56-59 |  |
| **Iron Treads** | selvagem (land) — `MeteorCave2` Lv56-59 |  |
| **Iron Bundle** | selvagem (land) — `MeteorCave2` Lv56-59 |  |
| **Iron Hands** | selvagem (land) — `MeteorCave2` Lv56-59 |  |
| **Iron Jugulis** | selvagem (land) — `MeteorCave2` Lv56-59 |  |
| **Iron Moth** | selvagem (land) — `MeteorCave2` Lv57-60 |  |
| **Iron Thorns** | selvagem (land) — `MeteorCave2` Lv57-60 |  |
| **Roaring Moon** | selvagem (land) — `MeteorCave1` Lv57-60 |  |
| **Iron Valiant** | encontro estático — `MeteorCave2` Lv70 |  |
| **Walking Wake** | boss (bosslegendaryencounter) — `MeteorCave1_LegendaryRoom` Lv75 |  |
| **Iron Leaves** | boss (bosslegendaryencounter) — `MeteorCave2_LegendaryRoom` Lv75 |  |
| **Gouging Fire** | boss (bosslegendaryencounter) — `MeteorCave1_LegendaryRoom` Lv75 |  |
| **Raging Bolt** | boss (bosslegendaryencounter) — `MeteorCave1_LegendaryRoom` Lv75 |  |
| **Iron Boulder** | boss (bosslegendaryencounter) — `MeteorCave2_LegendaryRoom` Lv75 |  |
| **Iron Crown** | boss (bosslegendaryencounter) — `MeteorCave2_LegendaryRoom` Lv75 |  |

## Observações

- **Métodos duplicados em mapas mortos.** Vários lendários de Johto/Kanto também têm o encontro original do Emerald num mapa inalcançável (Articuno em `MeteorFalls_Articuno`, Mewtwo em `CeruleanCave3`, Raikou em `NewMauville_Inside_Raikou`, Kyogre/Groudon/Rayquaza em Marine/Terra Cave e Sky Pillar, Lugia/Ho-Oh em Navel Rock, Latias/Latios em Southern Island, Mew em `FarawayIsland_Interior`). Não fazem falta, porque cada um tem outro método alcançável, mas continuam na ROM.
- **Deoxys** só existe na Birth Island do Emerald, que é inalcançável. Na prática, sem método.
- **As 7 UBs das missões + Stakataka e Blacephalon** aparecem só como batalha sem captura (Rift Missions). O design prevê a Anabel vendendo Beast Balls no `UltraSpaceArena` (§10), o que já aponta para o loop como o lugar onde elas passam a ser capturáveis.
- **Necrozma** é presente no fim do clímax (`UltraSpaceArena`, Lv75). O Ultra Necrozma do boss não é capturável. Dusk Mane e Dawn Wings dependem de fusão com Solgaleo/Lunala.
- **Evoluções customizadas:** Manaphy evolui de **Phione** no Lv58 (Phione é pescado na `Route33South_2`); Melmetal de Meltan no Lv60; Naganadel de Poipole no Lv50; Cosmog → Cosmoem (Lv43) → Solgaleo/Lunala (Lv53). Os pergaminhos do Urshifu são vendidos no `GoldenrodBattleAracdeLobby`.
- **Battle Café** troca 5 pontos por um Lv70 de: Tornadus, Thundurus, Landorus, Enamorus, os quatro Tapus, as três aves de Galar, Koraidon e Miraidon (e Diancie como presente à parte).
- **Celebi** tem uma entrada na tabela da Hidden Grotto, mas é a `HIDDEN_GROTTO_JOHTO_UNUSED2`; o método real é o evento da Ilex Forest.
- **Lendários já capturados continuam elegíveis** no loop (design §10). Esta tabela diz só se há **algum** jeito de obter; não restringe o pool.
