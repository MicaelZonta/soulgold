# Pool de lendários — o que existe no jogo e como se obtém

Levantamento de todas as espécies **lendárias, míticas e "únicas"** que o engine tem
ativas neste hack, e de **qual delas o jogador consegue obter hoje**. Serve de
base para o pool do loop pós-Necrozma (design §10) e para as fichas do [Nexus](README.md).

Conferido no código em 25/09/2026.

## Critérios

- **Quem entra.** Toda espécie com `isRestrictedLegendary`, `isSubLegendary`, `isMythical`, `isUltraBeast` ou `isParadox` em `src/data/pokemon/species_info/` (as 9 gerações estão ligadas em `species_enabled.h`). "Único" aqui = **Ultra Beasts e Paradoxos**, as duas categorias especiais que não são lendário nem mítico. Formas (Mega, Primal, Origin, Therian, Gmax, Tera…) contam dentro da espécie; as **aves de Galar** ficam separadas porque são outro Pokémon.
- **O que conta como método:** encontro estático (`legendaryencounter`, `bosslegendaryencounter*`, `setwildbattle`, `seteventmon` com captura liberada), selvagem (`wild_encounters.json`), presente (`givemon`/`giveegg`), recompensa do Battle Café, troca in-game, roamer, evolução ou breeding a partir de algo obtível.
- **O que não conta:** batalha com `B_FLAG_NO_CATCHING` (as UBs das Rift Missions e o Ultra Necrozma), e método em mapa **fora da ROM** ou **inalcançável**.
- **Fora da ROM / alcançável.** `data/maps/map_groups.json` exclui da ROM os grupos `gMapGroup_Emerald1..5` (`rom_excluded_groups`): dos 1105 mapas do repositório, só 619 são compilados. Dos 619, **555 são alcançáveis** a partir do quarto do jogador. Todos os encontros "extras" de Hoenn (Navel Rock, Birth Island, Sky Pillar, Terra/Marine Cave, New Mauville…) estão em mapas **fora da ROM**. Para refazer a conta: `python3 dev_scripts/map_graph.py info <mapa>` (skill `mapa-de-ligacoes`). **Não** conferi se a cena está liberada pela história; só que o mapa existe e é visitável.

## Resumo

| | Espécies |
|---|---|
| ✅ Tem método | **96** |
| ⚠️ Só em mapa fora da ROM | **1** |
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

## Campeão de cada lendário

O campeão é a quinta luta do Daily, logo antes da boss battle (R5 em
[`NEXUS_REGRAS.md`](NEXUS_REGRAS.md)). A ficha do treinador traz o time, o
fragmento e as falas. Todo lendário do jogo tem campeão (distribuição de 27/09/2026: 121 lendários
para os 68 treinadores prontos, todos usados pelo menos uma vez). **Kyogre**
tem dois campeões: nos dias dele o sorteio escolhe entre Misty e Archie. As
pré-evoluções **não são boss**: Cosmog, Cosmoem, Type: Null, Kubfu, Meltan,
Phione e Poipole. Elas são o que o jogador **recebe** quando vence a forma
final da família, sempre no nível 1 ([R17](NEXUS_REGRAS.md)): Solgaleo/Lunala
→ Cosmog, Silvally → Type: Null, Urshifu → Kubfu, Melmetal → Meltan, Manaphy →
Phione, Naganadel → Poipole.

**Poipole não tem dia próprio** (decisão do autor, 26/09/2026): ele vem
junto com a luta do **Naganadel** — o jogador ganha um Poipole nela. Detalhes
na ficha da [Soliera](alola/soliera.md).

| Lendário | Categoria | Campeão | Situação |
|---|---|---|---|
| Kyogre | Lendário restrito | [Misty](kanto/misty.md), [Archie](hoenn/archie.md) | aprovado (design §10) · time e falas 📝 proposta, 27/09 |
| Mewtwo | Lendário restrito | [Giovanni](kanto/giovanni.md) | aprovado (design §10) · time e falas 📝 proposta, 27/09 |
| Genesect | Mítico | [Giovanni](kanto/giovanni.md) | aprovado (design §10) · time e falas 📝 proposta, 27/09 |
| Nihilego | Ultra Beast | [Colress](unova/colress.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Buzzwole | Ultra Beast | [Bruno](kanto/bruno.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Pheromosa | Ultra Beast | [Elesa](unova/elesa.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Xurkitree | Ultra Beast | [Volkner](sinnoh/volkner.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Celesteela | Ultra Beast | [Steven](hoenn/steven.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Kartana | Ultra Beast | [Ramos](kalos/ramos.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Guzzlord | Ultra Beast | [Guzma](alola/guzma.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Naganadel | Ultra Beast | [Soliera](alola/soliera.md) | campeão no código (fala em `nexus.inc`), 26/09 · só depois de capturado (R1) · a luta dá um **Poipole** |
| Stakataka | Ultra Beast | [Byron](sinnoh/byron.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Blacephalon | Ultra Beast | [Fantina](sinnoh/fantina.md) | campeão no código (fala em `nexus.inc`), 26/09 |
| Lugia | Lendário restrito | [Jasmine](johto/jasmine.md) | 📝 proposta, 27/09 |
| Ho-Oh | Lendário restrito | [Morty](johto/morty.md) | 📝 proposta, 27/09 |
| Groudon | Lendário restrito | [Maxie](hoenn/maxie.md) | 📝 proposta, 27/09 |
| Rayquaza | Lendário restrito | [Lance](kanto/lance.md) | 📝 proposta, 27/09 |
| Dialga | Lendário restrito | [Spenser](hoenn/spenser.md) | 📝 proposta, 27/09 |
| Palkia | Lendário restrito | [Sabrina](kanto/sabrina.md) | 📝 proposta, 27/09 |
| Giratina | Lendário restrito | [Silver](johto/silver.md) | 📝 proposta, 27/09 |
| Solgaleo | Lendário restrito | [Professor Kukui](alola/kukui.md) | 📝 proposta, 27/09 |
| Lunala | Lendário restrito | [Lillie](alola/lillie.md) | 📝 proposta, 27/09 |
| Necrozma | Lendário restrito | [Anabel](hoenn/anabel.md) | 📝 proposta, 27/09 |
| Koraidon | Lendário restrito | [Greta](hoenn/greta.md) | 📝 proposta, 27/09 |
| Miraidon | Lendário restrito | [Noland](hoenn/noland.md) | 📝 proposta, 27/09 |
| Silvally | Sub-lendário | [Gladion](alola/gladion.md) | 📝 proposta, 27/09 |
| Ogerpon | Sub-lendário | [Petrel](kanto/petrel.md) | 📝 proposta, 27/09 |
| Articuno | Sub-lendário | [Pryce](johto/pryce.md) | 📝 proposta, 27/09 |
| Galarian Articuno | Sub-lendário | [Sabrina](kanto/sabrina.md) | 📝 proposta, 27/09 |
| Zapdos | Sub-lendário | [Lt. Surge](kanto/lt_surge.md) | 📝 proposta, 27/09 |
| Galarian Zapdos | Sub-lendário | [Winona](hoenn/winona.md) | 📝 proposta, 27/09 |
| Moltres | Sub-lendário | [Blaine](kanto/blaine.md) | 📝 proposta, 27/09 |
| Galarian Moltres | Sub-lendário | [Karen](johto/karen.md) | 📝 proposta, 27/09 |
| Raikou | Sub-lendário | [Eusine](johto/eusine.md) | 📝 proposta, 27/09 |
| Entei | Sub-lendário | [Eusine](johto/eusine.md) | 📝 proposta, 27/09 |
| Suicune | Sub-lendário | [Eusine](johto/eusine.md) | 📝 proposta, 27/09 |
| Regirock | Sub-lendário | [Brandon](hoenn/brandon.md) | 📝 proposta, 27/09 |
| Regice | Sub-lendário | [Brandon](hoenn/brandon.md) | 📝 proposta, 27/09 |
| Registeel | Sub-lendário | [Brandon](hoenn/brandon.md) | 📝 proposta, 27/09 |
| Latias | Sub-lendário | [Tate e Liza](hoenn/tate_e_liza.md) | 📝 proposta, 27/09 |
| Latios | Sub-lendário | [Tate e Liza](hoenn/tate_e_liza.md) | 📝 proposta, 27/09 |
| Uxie | Sub-lendário | [Roxanne](hoenn/roxanne.md) | 📝 proposta, 27/09 |
| Mesprit | Sub-lendário | [May](hoenn/may.md) | 📝 proposta, 27/09 |
| Azelf | Sub-lendário | [Wally](hoenn/wally.md) | 📝 proposta, 27/09 |
| Heatran | Sub-lendário | [Flannery](hoenn/flannery.md) | 📝 proposta, 27/09 |
| Regigigas | Sub-lendário | [Whitney](johto/whitney.md) | 📝 proposta, 27/09 |
| Cresselia | Sub-lendário | [Ariana](kanto/ariana.md) | 📝 proposta, 27/09 |
| Cobalion | Sub-lendário | [Chuck](johto/chuck.md) | 📝 proposta, 27/09 |
| Terrakion | Sub-lendário | [Brock](kanto/brock.md) | 📝 proposta, 27/09 |
| Virizion | Sub-lendário | [Erika](kanto/erika.md) | 📝 proposta, 27/09 |
| Tornadus | Sub-lendário | [Falkner](johto/falkner.md) | 📝 proposta, 27/09 |
| Thundurus | Sub-lendário | [Winona](hoenn/winona.md) | 📝 proposta, 27/09 |
| Landorus | Sub-lendário | [Maxie](hoenn/maxie.md) | 📝 proposta, 27/09 |
| Tapu Koko | Sub-lendário | [Professor Kukui](alola/kukui.md) | 📝 proposta, 27/09 |
| Tapu Lele | Sub-lendário | [Lillie](alola/lillie.md) | 📝 proposta, 27/09 |
| Tapu Bulu | Sub-lendário | [Gladion](alola/gladion.md) | 📝 proposta, 27/09 |
| Tapu Fini | Sub-lendário | [Juan](hoenn/juan.md) | 📝 proposta, 27/09 |
| Urshifu | Sub-lendário | [Chuck](johto/chuck.md) | 📝 proposta, 27/09 |
| Enamorus | Sub-lendário | [Lusamine](alola/lusamine.md) | 📝 proposta, 27/09 |
| Chien-Pao | Sub-lendário | [Glacia](hoenn/glacia.md) | 📝 proposta, 27/09 |
| Chi-Yu | Sub-lendário | [Flannery](hoenn/flannery.md) | 📝 proposta, 27/09 |
| Fezandipiti | Sub-lendário | [Lusamine](alola/lusamine.md) | 📝 proposta, 27/09 |
| Arceus | Mítico | [Red](kanto/red.md) | 📝 proposta, 27/09 |
| Mew | Mítico | [Leaf](kanto/leaf.md) | 📝 proposta, 27/09 |
| Celebi | Mítico | [Spenser](hoenn/spenser.md) | 📝 proposta, 27/09 |
| Jirachi | Mítico | [Brendan](hoenn/brendan.md) | 📝 proposta, 27/09 |
| Manaphy | Mítico | [Misty](kanto/misty.md) | 📝 proposta, 27/09 |
| Darkrai | Mítico | [Karen](johto/karen.md) | 📝 proposta, 27/09 |
| Shaymin | Mítico | [Erika](kanto/erika.md) | 📝 proposta, 27/09 |
| Victini | Mítico | [Blue/Green](kanto/blue.md) | 📝 proposta, 27/09 |
| Meloetta | Mítico | [Petrel](kanto/petrel.md) | 📝 proposta, 27/09 |
| Diancie | Mítico | [Wallace](hoenn/wallace.md) | 📝 proposta, 27/09 |
| Hoopa | Mítico | [Tucker](hoenn/tucker.md) | 📝 proposta, 27/09 |
| Magearna | Mítico | [Wattson](hoenn/wattson.md) | 📝 proposta, 27/09 |
| Marshadow | Mítico | [Archer](kanto/archer.md) | 📝 proposta, 27/09 |
| Zeraora | Mítico | [Wattson](hoenn/wattson.md) | 📝 proposta, 27/09 |
| Melmetal | Mítico | [Jasmine](johto/jasmine.md) | 📝 proposta, 27/09 |
| Zarude | Mítico | [Norman](hoenn/norman.md) | 📝 proposta, 27/09 |
| Great Tusk | Paradoxo | [Greta](hoenn/greta.md) | 📝 proposta, 27/09 |
| Scream Tail | Paradoxo | [Whitney](johto/whitney.md) | 📝 proposta, 27/09 |
| Brute Bonnet | Paradoxo | [Sidney](hoenn/sidney.md) | 📝 proposta, 27/09 |
| Flutter Mane | Paradoxo | [Phoebe](hoenn/phoebe.md) | 📝 proposta, 27/09 |
| Slither Wing | Paradoxo | [Bugsy](johto/bugsy.md) | 📝 proposta, 27/09 |
| Sandy Shocks | Paradoxo | [Lt. Surge](kanto/lt_surge.md) | 📝 proposta, 27/09 |
| Iron Treads | Paradoxo | [Noland](hoenn/noland.md) | 📝 proposta, 27/09 |
| Iron Bundle | Paradoxo | [Glacia](hoenn/glacia.md) | 📝 proposta, 27/09 |
| Iron Hands | Paradoxo | [Brawly](hoenn/brawly.md) | 📝 proposta, 27/09 |
| Iron Jugulis | Paradoxo | [Lucy](hoenn/lucy.md) | 📝 proposta, 27/09 |
| Iron Moth | Paradoxo | [Bugsy](johto/bugsy.md) | 📝 proposta, 27/09 |
| Iron Thorns | Paradoxo | [Brock](kanto/brock.md) | 📝 proposta, 27/09 |
| Roaring Moon | Paradoxo | [Proton](kanto/proton.md) | 📝 proposta, 27/09 |
| Iron Valiant | Paradoxo | [Wally](hoenn/wally.md) | 📝 proposta, 27/09 |
| Walking Wake | Paradoxo | [Juan](hoenn/juan.md) | 📝 proposta, 27/09 |
| Iron Leaves | Paradoxo | [Leaf](kanto/leaf.md) | 📝 proposta, 27/09 |
| Gouging Fire | Paradoxo | [Lance](kanto/lance.md) | 📝 proposta, 27/09 |
| Raging Bolt | Paradoxo | [Drake](hoenn/drake.md) | 📝 proposta, 27/09 |
| Iron Boulder | Paradoxo | [Tate e Liza](hoenn/tate_e_liza.md) | 📝 proposta, 27/09 |
| Iron Crown | Paradoxo | [Will](johto/will.md) | 📝 proposta, 27/09 |
| Deoxys | Mítico | [Anabel](hoenn/anabel.md) | 📝 proposta, 27/09 |
| Reshiram | Lendário restrito | [Brendan](hoenn/brendan.md) | 📝 proposta, 27/09 |
| Zekrom | Lendário restrito | [May](hoenn/may.md) | 📝 proposta, 27/09 |
| Kyurem | Lendário restrito | [Clair](johto/clair.md) | 📝 proposta, 27/09 |
| Keldeo | Mítico | [Brawly](hoenn/brawly.md) | 📝 proposta, 27/09 |
| Xerneas | Lendário restrito | [Wallace](hoenn/wallace.md) | 📝 proposta, 27/09 |
| Yveltal | Lendário restrito | [Sidney](hoenn/sidney.md) | 📝 proposta, 27/09 |
| Zygarde | Lendário restrito | [Lucy](hoenn/lucy.md) | 📝 proposta, 27/09 |
| Volcanion | Mítico | [Blaine](kanto/blaine.md) | 📝 proposta, 27/09 |
| Zacian | Lendário restrito | [Blue/Green](kanto/blue.md) | 📝 proposta, 27/09 |
| Zamazenta | Lendário restrito | [Norman](hoenn/norman.md) | 📝 proposta, 27/09 |
| Eternatus | Lendário restrito | [Tucker](hoenn/tucker.md) | 📝 proposta, 27/09 |
| Regieleki | Sub-lendário | [Lt. Surge](kanto/lt_surge.md) | 📝 proposta, 27/09 |
| Regidrago | Sub-lendário | [Drake](hoenn/drake.md) | 📝 proposta, 27/09 |
| Glastrier | Sub-lendário | [Pryce](johto/pryce.md) | 📝 proposta, 27/09 |
| Spectrier | Sub-lendário | [Morty](johto/morty.md) | 📝 proposta, 27/09 |
| Calyrex | Lendário restrito | [Will](johto/will.md) | 📝 proposta, 27/09 |
| Wo-Chien | Sub-lendário | [Archer](kanto/archer.md) | 📝 proposta, 27/09 |
| Ting-Lu | Sub-lendário | [Proton](kanto/proton.md) | 📝 proposta, 27/09 |
| Okidogi | Sub-lendário | [Janine](kanto/janine.md) | 📝 proposta, 27/09 |
| Munkidori | Sub-lendário | [Janine](kanto/janine.md) | 📝 proposta, 27/09 |
| Terapagos | Lendário restrito | [Roxanne](hoenn/roxanne.md) | 📝 proposta, 27/09 |
| Pecharunt | Mítico | [Koga](kanto/koga.md) | 📝 proposta, 27/09 |

## Sem método de obtenção

Estes são os candidatos naturais para o pool do loop: existem no jogo e o jogador não tem como pegar.

| Espécie | Categoria | Situação |
|---|---|---|
| **Deoxys** | Mítico | ⚠️ só em mapa fora da ROM: `BirthIsland_Exterior` |
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

- **Métodos duplicados em mapas mortos.** Vários lendários de Johto/Kanto também têm o encontro original do Emerald num mapa **fora da ROM** (Articuno em `MeteorFalls_Articuno`, Mewtwo em `CeruleanCave3`, Raikou em `NewMauville_Inside_Raikou`, Kyogre/Groudon/Rayquaza em Marine/Terra Cave e Sky Pillar, Lugia/Ho-Oh em Navel Rock, Latias/Latios em Southern Island, Mew em `FarawayIsland_Interior`). Não fazem falta, porque cada um tem outro método alcançável, mas continuam na ROM.
- **Deoxys** só existe na Birth Island do Emerald, que está fora da ROM. Na prática, sem método.
- **As 7 UBs das missões + Stakataka e Blacephalon** aparecem só como batalha sem captura (Rift Missions). O design prevê a Anabel vendendo Beast Balls no `UltraSpaceArena` (§10), o que já aponta para o loop como o lugar onde elas passam a ser capturáveis.
- **Necrozma** é presente no fim do clímax (`UltraSpaceArena`, Lv75). O Ultra Necrozma do boss não é capturável. Dusk Mane e Dawn Wings dependem de fusão com Solgaleo/Lunala.
- **Evoluções customizadas:** Manaphy evolui de **Phione** no Lv58 (Phione é pescado na `Route33South_2`); Melmetal de Meltan no Lv60; Naganadel de Poipole no Lv50; Cosmog → Cosmoem (Lv43) → Solgaleo/Lunala (Lv53). Os pergaminhos do Urshifu são vendidos no `GoldenrodBattleAracdeLobby`.
- **Battle Café** troca 5 pontos por um Lv70 de: Tornadus, Thundurus, Landorus, Enamorus, os quatro Tapus, as três aves de Galar, Koraidon e Miraidon (e Diancie como presente à parte).
- **Celebi** tem uma entrada na tabela da Hidden Grotto, mas é a `HIDDEN_GROTTO_JOHTO_UNUSED2`; o método real é o evento da Ilex Forest.
- **Lendários já capturados continuam elegíveis** no loop (design §10). Esta tabela diz só se há **algum** jeito de obter; não restringe o pool.
