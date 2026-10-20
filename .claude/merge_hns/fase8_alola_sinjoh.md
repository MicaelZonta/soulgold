# Fase 8 — Alola + Sinjoh + Snowswept (19/10/2026)

39 mapas (Alola 20, New Sinjoh 8, Sinjoh Ruins 10, Snowswept 1). Build limpo (`make -j`),
`map_graph.py check` ok (615 alcançáveis). **Não testado no jogo.**

## O que a importação anterior deixou sem fechar (descoberto ao compilar)

O build quebrava em 9 pontos; todos resolvidos nesta fase:

| Problema | Correção |
|---|---|
| `map_groups.json`: os 4 grupos novos estavam *depois* de `rom_excluded_groups`, fora de `group_order` | `gMapGroup_OutdoorAlola`, `gMapGroup_IndoorAlola`, `gMapGroup_Sinjoh` entram no fim de `group_order` (nenhum grupo existente renumerado); `gMapGroup_IndoorSinjoh` (vazio) removido |
| Scripts dos 39 mapas não incluídos | `.include` em `data/event_scripts.s` (depois do Nexus) |
| `Melemele_House` usava `local_id` `LOCALID_NURSE` (vira `#define` e quebra o `.set LOCALID_NURSE` de 14 Pokémon Centers) | renomeado `LOCALID_MELEMELE_HOUSE_NURSE` |
| 9 tilesets só tinham a pasta (sem registro) | `graphics.h`/`metatiles.h`/`headers.h`: `AlolaIsland`, `AlolaIslandSecondary`, `ArceusRoom_Hns`, `JohtoMart_Hns`, `MtEmber_Hns`, `MtSilver_Ancient_Hns`, `MtSilver_Exp_Hns`, `MtSilver_NewSinjoh_Hns`, `RuinsOfAlphWriting_Hns` (tiles `.fastSmol`; callbacks: `MtEmber_Hns` usa `InitTilesetAnim_MtEmber`, os outros NULL) |
| 13 `MAPSEC_*` e 2 `HEAL_LOCATION_*` inexistentes | `region_map_sections.json` (só nome, sem x/y: não aparece na região do mapa) e `heal_locations.json` (`MELEMELE_ISLE`, `NEW_SINJOH`) |
| `INGAME_TRADE_TAUROS_{WATER,FIGHT,FIRE}` (Jessica, Melemele) | enum em `trade.h` + 3 entradas em `src/data/trade.h` (Tauros de Paldea; sem espécie pedida) |
| `setwildbossbattle` (comando do HnS) não existia | macro em `asm/macros/event.inc` + `ScriptSetWildBossBattle` (`scrcmd.c`) + `CreateScriptedWildBossMon` (`script_pokemon_util.c`); mon selvagem com item e golpes definidos; inicia com `dowildbattle` ou `special BattleSetup_StartLegendaryBattle` |
| Specials `GivePartyMonSkyRibbon`, `GivePartyMonMarineRibbon`, `OpenScreenshotsFromScript`; `SELECT_PC_MON_PLA_TUTOR` | os 2 primeiros portados (`field_specials.c`, `specials.inc`); tutor PLA portado em `chooseboxmon.c` (tabela `sPLATutorLearnsets` + enum); **viewer de screenshots NÃO portado** (ver pendências) |
| `gTutorMoves` passou de 160 (tutores novos de Alola/Sinjoh) e o `STATIC_ASSERT` do relearner falhou | `MAX_RELEARNER_MOVES` 160 -> 200 |
| 5 músicas desligadas em `songs_enabled.h` e usadas pelos mapas | ligadas: `DP_AZURE_FLUTE`, `DP_HALL_OF_ORIGIN`, `DP_SNOWPOINT_DAY`, `HG_VS_ARCEUS`, `HG_WIFI_PLAZA` (custo de ROM; ROM = 36 972 752 B) |
| `FLAG_NO_WILD_CATCHING/RUNNING`, `FLAG_SMART_WILD_AI` não eram lidas no S | scripts: `FLAG_NO_WILD_CATCHING` -> `FLAG_NO_CATCHING` (a flag crua que `B_FLAG_NO_CATCHING` lê). `battle.h`: `B_FLAG_NO_RUNNING = FLAG_NO_WILD_RUNNING` e `B_SMART_WILD_AI_FLAG = FLAG_SMART_WILD_AI` (como no P) para as lutas de Totem/Noble funcionarem. `FLAG_NO_SHINY` nem o P lê; captura desligada já impede shiny |

## 1. Treinadores (25, não 21)

IDs em slots `TRAINER_UNUSED_*` com valor < 1056 (`UNUSED_192` em diante é o bloco de flags reclamadas: `STATIC_ASSERT` em `global.h`). Times copiados de `trainers_hns.party`.
Conversões: `Class`/`Pic` sem sufixo ` Hns`; `Professor Hns` -> **Scientist**; `Officer Hns` -> **Policeman** (classe e pic); `Rg Gym Leader` -> `Dp Elite Four`; mugshot `Light Blue` -> `Blue`.
Pic novo: `TRAINER_PIC_FRONT_SAMSON_OAK` (`graphics/trainers/front_pics/samson_oak.png`, 64x64, inserido antes de `FRONT_COUNT`).

SAMSON_OAK, MELEMELE_SWIMMER_1/2, AKALA_SWIMMER_1/2/3, PONI_SWIMMER_1/2, AKALA_HIKER/PICNICKER/CAMPER, AKALA_FOREST_BUGCATCHER_1/2, AKALA_CAVE_PICNICKER/CAMPER/HIKER, ULAULA_PICNICKER/YOUNGSTER/HIKER/COOLTRAINER, MILKMAN, MIHARU, YOUKO, SHIZUKO, MUALANI (valores em `opponents.h`, comentário `HnS Fase 8 (was TRAINER_UNUSED_n)`).

## 2. Sprites

| Define | Solução |
|---|---|
| `OBJ_EVENT_GFX_KIMONO` | alias de `KIMONO_GIRL` |
| `OBJ_EVENT_GFX_LIGHT` | alias de `LIGHT_SPRITE` |
| `OBJ_EVENT_GFX_SWIMMER_F_LAND` | alias de `SWIMMER_F` (o terrestre; `_WATER` é o nadando) |
| `OBJ_EVENT_GFX_SKIER_F` / `SKIER_M` | importados do P (32x32, 4x4 metatile, paleta própria `OBJ_EVENT_PAL_TAG_SKIER_F/M` 0x11A8/9, ids 391/392, `NUM_OBJ_EVENT_GFX` 393). PNGs 320x32 (10 quadros; a pic table usa 9, igual ao P) |

## 3. `MAP_BATTLE_SCENE_INDOOR_2`

`#define ... MAP_BATTLE_SCENE_NORMAL` em `map_types.h`, `TODO(hns)` (usada só em `NewSinjoh_House3`).

## 4. Bosses (`bosslegendaryencounter`)

| Espécie | Mapa | Nv | Barras | Flag |
|---|---|---|---|---|
| Tapu Koko | MelemeleIsle | 60 | 2 | FLAG_HIDE_TAPU_KOKO |
| Tapu Lele | AkalaIsle | 60 | 2 | FLAG_HIDE_TAPU_LELE |
| Tapu Bulu | UlaUla_Forest | 60 | 2 | FLAG_HIDE_TAPU_BULU |
| Tapu Fini | PoniIsle | 60 | 2 | FLAG_HIDE_TAPU_FINI |
| Regirock / Regice / Registeel / Regieleki / Regidrago | SinjohRuins_*Room | 80 | 2 | FLAG_HIDE_SINJOHRUINS_* |
| Regigigas | SinjohRuins_RegigigasRoom | 80 | 3 | FLAG_HIDE_SINJOHRUINS_REGIGIGAS |
| Arceus fase 1 | SinjohRuins_ArceusRoom | Arceus-Steel 100 | 3, **não capturável** | (storyline -> 12) |
| Arceus fase 2 | idem | Arceus 80 | 3, capturável | FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS |

- Tapus: cenas de flyover intactas; o `msgbox` vem antes do macro (o cry é tocado pelo macro); os blocos `_2/_3` (CAUGHT/WON) que setam `FLAG_BATTLED_TAPU_*` e escondem o objeto foram mantidos, lendo `GetBattleOutcome` de novo depois do macro.
- Regis: só a luta foi trocada; o scanner do Temple e `VAR_REGIS_SCANNED=5` não foram tocados. Fuga/derrota mantém o objeto (retry), como na Fase 7.
- Arceus fase 1: `setwildbossbattle` (Iron Plate; Judgment/Hydro Pump/Recover/Dazzling Gleam) + `setbossbattle 3` + `FLAG_NO_CATCHING` (a do P, `FLAG_NO_WILD_CATCHING`, não é lida no S). O `settotemboost` do P foi **removido** (boss de 3 barras + +2 em tudo seria demais; reavaliar no teste). Fase 2 usa `bosslegendaryencounterwithmoves` (Extreme Speed/Earth Power/Recover/Hyper Beam); a Sky Ribbon só sai se capturar (se o jogador nocautear sem capturar, o Arceus fica e dá para repetir; `VAR_SINJOH_STORYLINE` já está em 12 e o trigger do Steven segue). Música: `BattleSetup_StartLegendaryBattle` ganhou `case SPECIES_ARCEUS(_STEEL)` -> `MUS_HG_VS_ARCEUS`. O `playbgm` solto do P foi removido.
- Texto "ARCEUS: Dodogyuuun!" e demais falas dos mapas novos ainda estão no formato `Nome:` (sem plaquinha `{SPEAKER}`) — fora de escopo.

## 5. Oak (GoldenrodCity_RadioTower_2F, só `.pory`)

Com a Johto Dex completa, em vez do ovo de Arceus: escolha de Bulbasaur/Charmander/Squirtle Lv5 (`MULTI_KANTO_STARTERS` = 137 em `script_menu.h`), checagem de espaço (party E PC) **antes da oferta**, confirmação "Are you sure?", guarda `MON_CANT_GIVE` antes do `setflag`. A flag `FLAG_ARCEUS_EGG_GIVE` (0x26) foi **reaproveitada** como "Oak já deu o inicial" (saves que já pegaram o ovo continuam marcados). Plaquinha `{SPEAKER NAME_OAK}` nas falas do Oak.

## 6. Acesso e fiação

Alola: já liga pelo `Route13` (barco, `VAR_ALOLA_TRAVEL`). Sinjoh no HnS:
`MtSilver_1F_WaterfallRoom` (43,7) -> `SnowsweptCavern` -> **Route 49 do HnS** -> `NewSinjoh` -> **Route 50 do HnS** -> `SinjohRuins`.

**Problema:** Route49/Route50 do HnS têm o *mesmo nome* de mapas do S (outros mapas: deserto de Vajra / Lake of Rage). As conexões importadas (`MAP_ROUTE49/50`) apontavam para os mapas errados. Além disso, importar as duas rotas exige **15 flags novas** (`FLAG_HIDE_ROUTE49_NOBLE_{OVERQWIL,WYRDEER}`, `FLAG_HIDE_ROUTE49_TM_ROCK_CLIMB`, `FLAG_ROUTE_49_{ITEM_LURE,ITEM_STARDUST,KIMONOGIRL,HIDDENITEM_ICESTONE,HIDDENITEM_KINGSROCK,HIDDENITEM_ULTRABALL}`, `FLAG_HIDE_ROUTE50_NOBLE_{ELECTRODE,KLEAVOR}`, `FLAG_ROUTE50_{HIDDENITEM_1..3,ITEMBALL_1,2}`); a regra desta fase proibia editar `flags.h`, então as rotas **não foram importadas**.

Solução provisória (reversível):
- Conexões de `NewSinjoh` e `SinjohRuins` removidas (`"connections": []`).
- Warps: `SnowsweptCavern` (49,3) -> `NewSinjoh` warp 7 = (8,50); `NewSinjoh` (2,0) -> `SinjohRuins` warp 10 = (8,74); `SinjohRuins` (8,74) -> `NewSinjoh` warp 8; `NewSinjoh` warp 7 volta ao Snowswept warp 1. Coordenadas em tiles andáveis (conferido no `map.bin`).
- **Ponte de storyline** em `NewSinjoh_On_Transition`: se `VAR_SINJOH_STORYLINE == 3` vira 4 (a cena da Kimono Girl na Route 49 fazia isso; o `NewSinjoh_KimonoHideout` só roda com 4).

Gatilhos de `VAR_SINJOH_STORYLINE` (documentação): 1 = `MtSilver_PokemonCenter` (Meara, fora desta fase) -> 2 `MtSilver_1F_WaterfallRoom` (cena do cientista) -> 3 `SnowsweptCavern` (pedra/Machamp) -> 4 Route 49 (cena da Kimono; **ponte**) -> 5 `KimonoHideout` -> 6/7/8 `SinjohRuins_House1` (6 = Kimonos/Mualani/Skylar dão as plates; 7, 8) -> 9/10 `SinjohRuins` -> 11 `ArceusRoom` (cena da flauta) -> 12 (Arceus fase 1 vencida) -> 13 (Steven; libera rematches da Liga e Red pós-OBC). Plates: `VAR_PLATECOUNTER` (3/6/9/12/15/16).

**Perda conhecida:** sem a Route 49/50 não existem a Sky Plate do Skylar, o Wyrdeer/Overqwil/Kleavor/Electrode "noble" e os itens dessas rotas. Se o contador de plates exigir a Sky Plate para o 16, ele não chega lá até a importação.

Mapa de ligações: `map_graph.py check` -> "615 mapas alcançáveis, nenhum mapa novo desligado" (sem `--atualizar`).

## Pendências

1. **Importar Route49/Route50 do HnS** com nomes novos (sugestão `Route49_Sinjoh`/`Route50_Sinjoh`, layouts `LAYOUT_ROUTE49_SINJOH`, prefixo de labels diferente do S) depois de alocar as 15 flags (skill `alocar-flag` + `catalogar-flags`); recolocar as conexões do P (NewSinjoh up->50 offset 20, down->49 offset 10; Ruins down->50 offset 6) e remover warps provisórios e a ponte.
2. Viewer de screenshots (`ui_screenshots.c` do HnS): os "mapas de parede" de `Melemele_House` e `NewSinjoh_PokemonCenter` só mostram o texto. `TODO(hns)`.
3. `InitTilesetAnim_AlolaIslands` (água/flores do primário `AlolaIsland`) não portado; `MtSilver_Exp_Hns` também sem animação.
4. Region map: `MAPSEC_*` novos sem x/y (não aparecem no mapa); popups/nuzlocke tables não receberam os MAPSEC novos.
5. Cenário de batalha dedicado `MAP_BATTLE_SCENE_INDOOR_2`.
6. Battle Café ainda oferece os 4 Tapus (agora também bosses em Alola). Remoção aguarda confirmação do autor.
7. `settotemboost` do Arceus fase 1 removido; rever a dificuldade no teste.
8. Rodar `flag_audit.py --csv` (não rodei, ordem do pedido): `FLAG_ARCEUS_EGG_GIVE` mudou de sentido; `FLAG_NO_WILD_CATCHING` ficou sem leitores; flags dos Tapus/Regis/Arceus já existiam.
9. Aviso do assembler (10x): `setvar VAR_OBJ_GFX_ID_n, OBJ_EVENT_GFX_SPECIES(...)` dispara "might be a VAR_ constant"; falso positivo (mesmo padrão do P).
10. Teste no jogo pendente (pedir permissão ao autor): boss de cada Tapu/Regi, Arceus 2 fases, Oak, warps provisórios, trades Tauros, tutor PLA.

## Adendo 19/10 — Oak dá o Mystery Egg (Manaphy)
Decisão do autor: o Oak NÃO dá starter de Kanto; dá um **Mystery Egg com
Manaphy** (diálogo evoca o Mystery Egg de GSC). Starter multichoice removida.
Phione: encounters de pesca removidos (viraram Finizen), evolução
Phione→Manaphy removida; Phione agora só por breeding do Manaphy (nativo no
daycare) e fragmento do Nexus. Manaphy segue no Nexus (campeã da Misty,
requiresCaught). FLAG_ARCEUS_EGG_GIVE re-ressignificada (comentário).

## Adendo 19/10 — Route 49/50 de Sinjoh importadas (atalho desfeito)
- Importadas RENOMEADAS (`Route49Sinjoh`/`Route50Sinjoh`, MAP_/LAYOUT_
  *_SINJOH) para não colidir com as nossas rotas 49/50 custom.
- Cadeia fiel ao HnS restaurada: Waterfall → Snowswept → (warp 49,3) →
  Route49Sinjoh → NewSinjoh → Route50Sinjoh → SinjohRuins; atalho e ponte
  de storyline removidos (a Kimono da Route 49 volta a fazer 3→4).
- 16 flags novas com infixo SINJOH (0x1173+); 3 treinadores (SKYLAR com a
  Sky Plate — classe/pic Picnicker provisórios, TODO Skier; FINLEY, WESSEL);
  nobles Wyrdeer/Overqwil/Kleavor/Electrode via setwildbossbattle já portado.
- ITEM_TM_ROCK_CLIMB→ITEM_HM_ROCK_CLIMB (no S é HM); MAPSEC_ROUTE_50
  adicionada no FIM do enum (meio do enum deslocaria met-locations).
