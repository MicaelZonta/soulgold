# Kanto no SoulGold — auditoria de estado (28/09/2026)

Levantamento estático de **quanto de Kanto está funcional**, o que existe só
como casca e o que falta para a região funcionar de ponta a ponta. Fonte:
`data/maps/*/map.json`, `data/layouts/layouts.json`, `scripts.inc`,
`src/data/wild_encounters.json`, `src/data/trainers.party`,
`src/data/region_map/*`, `dev_scripts/map_graph.py` e o catálogo de flags.
Não substitui teste no jogo: um build limpo prova só que compila.

## 1. Veredito em uma tela

| Camada | Estado | Nota |
|---|---|---|
| Mapas (chão, colisão, portas, conexões) | **Pronto** | 196 mapas; 173 alcançáveis a partir do quarto do jogador. Nenhum mapa novo desligado (`map_graph check` ok). |
| Tilesets | **Pronto** | Todo mapa de Kanto usa `johto_general`/`johto_building` + secundário próprio (`pallet_town`, `viridian_city`, `saffron_city`…). Todos com `tiles.png`, `metatiles.bin`, atributos e paletas. |
| Acesso a Kanto | **Pronto** | Por terra (Rota 27 → 26 → 26 Norte → 22 → Viridian) via Reception Gate, e pelo Magnet Train (Goldenrod ↔ Saffron). |
| Ginásios e insígnias 9–16 | **Pronto** | 8 líderes com time, texto e insígnia. Cartão de treinador desenha via `FLAG_DEFEATED_*_GYM`. |
| Treinadores de rota | **Pronto** | 142 `trainerbattle` em mapas alcançáveis, todos com party. 99 treinadores com raio de visão nas rotas. |
| Histórias de Kanto | **Pronto** | Power Plant/Rocket (0→7), Safari Zone com Steven (0→4), Snorlax + Expn Card, Suicune em Vermilion, Blue Cinnabar→Viridian, Blaine em Seafoam, Bill, Copycat, Dojo VIP (revanches). |
| Lendários de Kanto | **Pronto** | Zapdos (Rota 10), Articuno (Seafoam B1F), Moltres (Victory Road B1F), Mewtwo lv80 boss + Leaf (Cerulean Cave B2F), Regigigas (Mt Silver). |
| **Encontros selvagens** | **AUSENTE** | **Zero** tabelas para Rotas 1–25, Viridian Forest, Mt Moon, Rock Tunnel, Diglett's Cave, Seafoam, Safari Zone de Fuchsia e mar das Rotas 19–21. Grama, Surf e pesca não dão nada. |
| **Mapa da região / Fly** | **AUSENTE** | Os MAPSECs de Kanto não têm posição no mapa; a segunda página do mapa é `NULL`; o código de Kanto em `region_map.c` está comentado. Não dá para voar para Kanto. |
| **S.S. Aqua** | **QUEBRADO** | 11 mapas do navio inalcançáveis; Olivine não vai para Vermilion; o marinheiro de Vermilion anima o embarque e **não faz warp** (provável softlock, ver §5.3). |
| Red | **AUSENTE** | `TRAINER_RED` sem party e sem script. O cume do Mt Silver tem o rival final (lv 75–76). |

Resumo: **Kanto está andável, com ginásios, treinadores, itens e história
funcionando; falta o que faz uma região "viva": Pokémon selvagem, mapa da
região com voo, e o navio.** Os três são trabalho de dados, não de mapa.

## 2. Como se chega em Kanto

- **Terra:** New Bark → Rota 27 → Tohjo Falls → Rota 26 → Rota 26 Norte →
  Rota 22 → Viridian. O Reception Gate libera com `FLAG_BADGE08_GET` **e**
  `FLAG_LEGENDARY_STORY_CAP` (ou `FLAG_IS_CHAMPION`). A Rota 26 Norte também
  liga à Rota 28 → Mt Silver e ao Centro da Liga (Indigo).
- **Magnet Train:** `GoldenrodCity_TrainStation` ↔ `SaffronCity_TrainStation`,
  precisa de `ITEM_PASS`; sem Pass e com `FLAG_RETURNED_MACHINE_PART` o
  atendente nega. Funciona nos dois sentidos.
- **Navio:** não existe rota Johto → Kanto por mar (ver §5.3).
- **Liga:** `Route28` entra direto em `IndigoPlateau_PokemonCenter`, que leva
  à sala do Will (Elite Four compartilhada). O exterior `IndigoPlateau` e a
  `Route23` existem mas ninguém chega neles (inalcançáveis de propósito).

Kanto é conteúdo pós-lendário/pós-Liga: os treinadores de rota estão em
lv 54–65 no `trainers.party` e os líderes em lv 57–69. Com
`B_LEVEL_SCALING_ENABLED TRUE` (média da party) esses números são só base.

## 3. Inventário por área

Legenda: **G** ginásio, **C** centro, **L** loja. "vazia" = interior
alcançável com script de 2 linhas e sem NPC.

| Área | Exterior | Interiores | Destaques | Problemas |
|---|---|---|---|---|
| Pallet Town | 24x20 | Red's House 1F/2F, House2 (Daisy), Lab (137 linhas) | — | `PalletTown_House3` sem porta (órfã) |
| Viridian City | 48x40 | **G** (Blue, Earth), **C**, **L**, House1, House2 | Blue só aparece depois de Cinnabar | House2 vazia |
| Rota 22 / 2 / Viridian Forest | ok | Route2_House, gate | 345 linhas na Rota 22: cena Giovanni/Silver disparada com Celebi na party | — |
| Pewter City | 52x44 | **G** (Brock + 1), **C**, **L**, House1/2, Museum 1F/2F | Rainbow/Silver Wing | — |
| Rotas 3 / 4 / Mt Moon | ok | Route4_PokemonCenter, MtMoon_Shop | Mt Moon Cave (3 treinadores), Outside (Clefairy) | Centro da Rota 4 tem script vazio, mas os NPCs usam scripts compartilhados (funciona) |
| Cerulean City | 56x40 | **G** (Misty + 3), **C**, **L**, House1/2/3, BikeShop | Rocket na academia (parte da história do Power Plant) | BikeShop vazia (0 objetos) |
| Rotas 24 / 25 | ok | Bill's House (227 linhas) | 8 treinadores na 25, cena Rocket na ponte | — |
| Cerulean Cave | 1F/B1F/B2F | — | **Tem tabela de encontro**; Mewtwo lv80 boss + Leaf lv85–87 | — |
| Vermilion City | 71x55 | **G** (Lt. Surge + 3), **C**, **L**, Port Outside/Inside, Fan Club, House1/2/3 | Snorlax (Expn Card), cena de Suicune (369 linhas) | Porto sem destino (§5.3) |
| Diglett's Cave / Rotas 5–8 / túneis | ok | Route5_House, 4 entradas de túnel, Saffron Tunnel NS/SW | Túneis ligados nos dois lados | túneis sem nada dentro (como no original) |
| Lavender Town | 28x21 | **C**, **L**, House1/2/3, Radio Station, Soul House | Radio Station dá `FLAG_KANTO_RADIO_GOT` | House3 vazia |
| Rotas 9 / 10 / Rock Tunnel / Power Plant | ok | Route9_PokemonCenter, PowerPlant Entrance/BackRoom | História Rocket completa (estados 0→7), Zapdos lv50 | — |
| Rotas 11–15 | ok | Route12_House | 22 treinadores | — |
| Celadon City | 60x40 | **G** (Erika + 5), **C**, House1 (café), House2, Apartments 1F–3F + telhado dia/noite + casa do telhado, Game Corner, Dept Store 1F–5F + telhado dia/noite | Layout noturno trocado por `setmaplayoutindex` (os mapas `*Night` são só layout) | House2 vazia |
| Rotas 16–18 (Cycling Road) | ok | Route16_House | 6 treinadores | — |
| Saffron City | 66x55 | **G** (Sabrina + 4), **C**, **L**, Train Station, Fighting Dojo, Dojo VIP, Silph Co, Copycat 1F/2F, House1 | Dojo VIP: 16 revanches de líderes por BP (2016 linhas). Silph Co entrega starter de Hoenn | `Saffron_Temp` é cópia morta do exterior |
| Fuchsia City | 48x40 | **G** (Janine + 4), **C**, **L**, House1/2, gates 15 e 19, Safari Entrance + Beach/Brush/Mountain/Cave | História do Safari com Steven (0→4), modo Safari ligado | Gate da Rota 19 sem porta; **áreas do Safari sem tabela de encontro** |
| Rotas 19–21 (mar) | ok | — | 10 treinadores nadadores | Sem Pokémon na água nem na pesca |
| Cinnabar Island | 72x44 | só **C** | Blaine e Blue na ilha (como HGSS). Usa secundário `lavaridge` (Hoenn) | — |
| Seafoam Islands | 1F/B1F/Gym/SecretCave | Blaine (Volcano) | Articuno lv50 | SecretCave vazia; Blaine seta `FLAG_GARBAGEFLAG` onde deveria setar `FLAG_BADGE15_GET` (ver §5.5) |
| Indigo Plateau | 24x20 | **C** (→ Will) | — | Exterior e Rota 23 inalcançáveis (Rota 28 entra direto no Centro) |
| Rotas 26 / 27 / 28, Tohjo Falls | ok | 2 casas na 26, casa na 27 e na 28 | **Têm tabela de encontro** (terra, água, pesca); 17 treinadores | — |
| Mt Silver | Outside, MountainSide, 1F (3 salas), 2F, 3F, Snow, Summit dia/noite, **C** | Regigigas (com os 3 Regis), rival final lv75–76 | **Tem tabela** em 8 mapas | `MtSilver_1F_MoltresRoom` vazia e sem porta (Moltres está na Victory Road B1F) |
| Victory Road (Kanto) | 1F/B1F/B2F | — | **Tem tabela**; HM Rock Climb; Moltres; itens | — |

Totais em mapas alcançáveis de Kanto: 44 item balls, 5 itens escondidos,
99 treinadores de rota, 495 Pokémon de overworld (`OBJ_EVENT_GFX_SPECIES`).

## 4. Tilesets

- **Exteriores:** todos em `gTileset_JohtoGeneral` (primário). Secundários por
  cidade: `pallet_town`, `viridian_city`, `pewter_city`, `cerulean_city`,
  `vermilion`, `lavender_town`, `celadon_city`, `saffron_city`, `fuchsia`,
  `indigo_plateau`, `viridian_forest`, `cave_mt_moon`, `cycling_road`,
  `mt_silver_snow`. Cinnabar usa `lavaridge` (Hoenn) e Mt Moon Outside usa
  `cherrygrove_city`. Todos os 196 mapas têm os quatro arquivos do tileset.
- **Interiores:** `johto_building` + `kanto_pokemon_center`, `kanto_mart`,
  `house_lab`, `silph_co`, `celadon_apartments`, `department_store`,
  `game_corner`, `museum`, `sea_cottage`, `soul_house`, `power_plant_generator_room`,
  `safari_zone_entrance`, ginásios próprios (`viridian_city_gym`,
  `cerulean_city_gym`, `vermilion_city_gym`, `fuchsia_city_gym`,
  `saffron_city_gym`, `azalea_town_gym` em Celadon, `ecruteak_theater` em
  Pewter/Dojo, `blackthorn_gym` em Seafoam).
- **Peso morto:** `gTileset_KantoGeneral` existe completo (16 paletas,
  animações) e **nenhum layout o usa**. `gTileset_KantoBuilding` é usado por
  lojas, Silph Co, Apartments, Safari Entrance e o gate da Rota 15. Os
  tilesets `*_frlg` (FireRed) também estão no repositório sem uso em Kanto.
- Nada em Kanto depende de tileset faltante. Não há trabalho de tileset
  pendente para a região funcionar.

## 5. O que falta ou está quebrado

### 5.1 Encontros selvagens (bloqueador)

`src/data/wild_encounters.json` cobre **21/21 rotas de Johto** e **0/25
rotas de Kanto**. Em Kanto só têm tabela: Cerulean Cave (3), Mt Silver (8),
Rotas 26/27/28, Tohjo Falls/Pass, Vermilion Port Outside, Victory Road
Kanto (3) e o Safari de Johto (6). Sem cabeçalho,
`GetCurrentMapWildMonHeaderId` devolve `HEADER_NONE` e grama, Surf, pesca e
Rock Smash não geram batalha.

Os 495 Pokémon de overworld em Kanto **não substituem isso**: 403 têm
`script: NULL` (decorativos, não batalham nem falam), 72 usam
`FLAG_NIGHT_POKEMON` e 24 `FLAG_DAY_POKEMON` para trocar com o horário, e os
demais só tocam o cry e mostram texto. Na Rota 1 dois deles (Pidgey e
Rattata) estão parados em `x=0` sem movimento, sobra de posicionamento.

Precisa de tabela (terra / água / pesca conforme o mapa) para: Rotas 1–25,
Viridian Forest, Mt Moon Cave/Outside, Rock Tunnel 1F/B1F, Diglett's Cave
Tunnel, Seafoam 1F/B1F, Route19_Cave, e as 4 áreas do Safari de Fuchsia
(Beach/Brush/Mountain/Cave, que hoje entram em modo Safari sem nada para
capturar). São ~40 cabeçalhos.

### 5.2 Mapa da região e Fly (bloqueador de conforto)

- `src/data/region_map/region_map_sections.json`: os MAPSECs de Kanto
  (`MAPSEC_PALLET_TOWN` … `MAPSEC_ROUTE_25`, `MAPSEC_MT_MOON`,
  `MAPSEC_ROCK_TUNNEL`, `MAPSEC_KANTO_VICTORY_ROAD`, `MAPSEC_POWER_PLANT`,
  `MAPSEC_CERULEAN_CAVE` …) só têm `name`; sem `x/y/width/height` não
  aparecem em mapa nenhum. Só `MAPSEC_INDIGO_PLATEAU` e `MAPSEC_SEAFOAM_ISLANDS`
  têm posição, herdada de Hoenn.
- `src/region_map.c`: `REGION_MAP_SECOND_PAGE_LAYOUT` é `NULL`; a terceira
  página é Sevii. `region_map_layout_kanto.h` (`sRegionMapSections_Kanto`)
  está incluído mas o `switch` que o escolheria está dentro de `/* … */`.
- `heal_locations.json` já tem Pallet, Viridian, Pewter, Cerulean,
  Vermilion, Lavender, Celadon, Saffron, Fuchsia, Cinnabar e Indigo. O voo
  não funciona porque o alvo não está no mapa, não por falta de heal location.
- Existe `graphics/map_popup/kanto.png` e o tema `MAPPOPUP_THEME_KANTO_ROUTE`
  já é aplicado aos MAPSECs de Kanto: a plaquinha de nome funciona.

Para funcionar: um `johtomap`-equivalente de Kanto (tilemap + paleta em
`graphics/pokenav/region_map/`), posições x/y para ~40 MAPSECs, ligar a
segunda página ao layout de Kanto (o offset de rolagem já existe:
`MAP_PAGE_SCROLL_X`) e descomentar/ajustar a seleção de região.

### 5.3 S.S. Aqua (quebrado)

- Os 11 mapas `SSAqua_*` estão na ROM e inalcançáveis.
- `OlivineCity_PortInside` só navega para Faraway Island e o Altar do Sol e
  da Lua. Não há viagem Olivine → Vermilion.
- `VermilionCity_PortInside`: o marinheiro pede `ITEM_SS_TICKET`; em
  `Sailor_MaidenVoyage` chama `EnterShip` (anima o jogador entrando no barco,
  `removeobject OBJ_EVENT_ID_PLAYER`, barco sai, `setrespawn`) e depois só
  `setvar VAR_SSAQUA_STATE, 1` / `release` / `end` — **sem `warp`**. O jogador
  fica removido do mapa. Mesmo padrão em `ChoseBattleFrontier`. **Provável
  softlock; confirmar no jogo** com SS Ticket e `FLAG_RETURNED_MACHINE_PART`.
- `SSAqua_1F/scripts.inc` zera `VAR_KANTO_ROCKET_STORY_STATE` e
  `VAR_KANTO_SAFARI_ZONE_PROGRESS` e limpa flags de guardas: era o gatilho
  original de "chegou em Kanto". Como o navio está fora do fluxo, esses
  resets nunca rodam (as duas histórias começam em 0 por `new_game.inc`, então
  funcionam mesmo assim).

Decisão de design pendente: ou ligar o navio (warp de Olivine para
`SSAqua_*` e de lá para Vermilion, e o inverso), ou trocar o marinheiro de
Vermilion por um warp direto para `OlivineCity_PortInside`, ou remover o
embarque e deixar só as viagens que já funcionam.

### 5.4 Mapas órfãos, vazios ou sobras

| Mapa | Situação | Sugestão |
|---|---|---|
| `PalletTown_House3` | 13x10, sem porta de entrada, sem NPC | Ligar como casa do Blue ou apagar |
| `FuchsiaCity_Route19_Gate` | sem porta, script vazio | Ligar (Fuchsia ↔ Rota 19) ou apagar |
| `Route23`, `IndigoPlateau` (exterior) | só ligados entre si | Manter como estão (Rota 28 → Centro) ou abrir o caminho pela Victory Road |
| `Saffron_Temp` | cópia 66x55 de Saffron, sem nada | Apagar |
| `SafariZone1/2/3`, `SafariZoneIndoor` | sobras, sem porta | Apagar |
| `MtSilver_1F_MoltresRoom` | 35x35 vazio, sem porta; Moltres já está na Victory Road B1F | Apagar ou reaproveitar |
| `CeladonCity_House2`, `ViridianCity_House2`, `LavenderTown_House3` | casa alcançável com 1 NPC e script de 2 linhas | Dar um texto ao NPC |
| `CeruleanCity_BikeShop` | alcançável, 0 objetos | NPC ou fechar a porta |
| `SeafoamIslands_SecretCave`, `Route19_Cave`, `DiglettsCave_EntranceSouth` | sem script; ok como corredor | — |
| `CeruleanCave1/2/3`, `SafariZone_*` (Hoenn), `SafariZone_RestHouse` | fora da ROM | nada a fazer |

### 5.5 Flags e treinadores

- `FLAG_IS_KANTO_CHAMPION` é lida em `ViridianCity_Gym` (manda Blue para o
  Dojo) e em `OlivineCity` (Eon Ticket), mas **ninguém a seta**; só
  `new_game.inc` a limpa. Blue nunca vai para o Dojo por esse caminho.
- `FLAG_BADGE15_GET` nunca é setada: Blaine seta `FLAG_GARBAGEFLAG` no lugar.
  Não afeta o cartão (que usa `FLAG_DEFEATED_CINNABAR_ISLAND_GYM`), mas
  qualquer checagem futura de 16 insígnias por `FLAG_BADGE*_GET` vai falhar.
  As `FLAG_BADGE09..16_GET` são redundantes (já apontado no
  `SOULGOLD_FLAGS_AUDIT.md` §7.5).
- `TRAINER_RED`, `TRAINER_RED_1`, `TRAINER_RED_2` existem em `opponents.h`
  sem party e sem script. O único "Red" do jogo é a versão Nexus
  (`.claude/rift_missions/nexus/kanto/red.md`).
- `ViridianCity_Gym` dá `ITEM_POTION` com comentário `@ NOT POTION`
  (prêmio do Blue é placeholder). `Route8` e `SaffronCity_FightingDojoVIP`
  têm marcações `TODO`.

## 6. Ordem sugerida para "fazer Kanto funcionar"

1. **Encontros selvagens** — ~40 cabeçalhos em `wild_encounters.json`. É o
   único item que impede Kanto de ser jogável como região Pokémon. Aproveitar
   as tabelas de Rota 26–28/Mt Silver como referência de nível.
2. **S.S. Aqua** — decidir o destino do marinheiro de Vermilion e fechar o
   provável softlock (um `warp` resolve o pior caso).
3. **Mapa da região + Fly** — tilemap de Kanto, x/y dos MAPSECs, segunda
   página do mapa. Trabalho de gráfico + dados; o código já tem os ganchos.
4. **Flags** — setar `FLAG_IS_KANTO_CHAMPION` (onde a história decidir),
   trocar `FLAG_GARBAGEFLAG` por `FLAG_BADGE15_GET` em Seafoam, prêmio do Blue.
   Depois rodar `python3 dev_scripts/flag_audit.py --csv`.
5. **Órfãos e vazios** — `PalletTown_House3`, gate da Rota 19, casas sem
   texto, e limpeza de `Saffron_Temp`, `SafariZone1-3`, `MoltresRoom`,
   `KantoGeneral`. Depois `python3 dev_scripts/map_graph.py check --atualizar`.
6. **Red no Mt Silver** — decisão de história (hoje o cume é do rival).

Tudo acima é trabalho de dados e script; **nenhum mapa de Kanto precisa ser
redesenhado nem ganhar tileset novo.**

## 7. Números de referência

| | |
|---|---|
| Mapas com prefixo de Kanto no repositório | 196 |
| Na ROM e alcançáveis | 173 |
| Na ROM e inalcançáveis | 13 |
| Fora da ROM (`gMapGroup_Emerald*`) | 10 |
| Rotas 1–25 com tabela de encontro | 0 / 25 |
| Rotas 29–48 (Johto) com tabela de encontro | 21 / 21 |
| `trainerbattle` em Kanto alcançável / sem party | 142 / 0 |
| Pokémon de overworld em Kanto / com `script: NULL` | 495 / 403 |
| MAPSECs de Kanto com posição no mapa da região | 2 (herdadas de Hoenn) |

Regenerar os dados brutos deste levantamento:

```bash
python3 dev_scripts/kanto_audit.py          # tabela por mapa + dev_scripts/kanto_rows.json
python3 dev_scripts/map_graph.py inalcancaveis
```
