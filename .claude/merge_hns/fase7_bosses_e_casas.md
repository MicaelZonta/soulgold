# Fase 7 — lendários do HnS viram Boss Fight (19/10/2026)

Regra do autor: todo lendário importado vira Boss Fight (`bosslegendaryencounter`). Build limpo (`make`).

| Espécie | Mapa | Nível | Barras | Flag de ocultação |
|---|---|---|---|---|
| Articuno | SeafoamIslands_B1F | 50 | 2 | FLAG_HIDE_ARTICUNO |
| Zapdos | Route10 | 50 | 2 | FLAG_HIDE_ZAPDOS |
| Moltres | MtSilver_1F_MoltresRoom | 50 | 2 | FLAG_HIDE_MOLTRES |
| Jirachi | MtMoon_Outside | 50 | 2 | FLAG_HIDE_MTMOON_JIRACHI |
| Deoxys | BirthIsland_Exterior | 70 (era 30) | 3 | flags próprias (puzzle intacto) |
| Koraidon (era Groudon) | SeafoamIslands_SecretCave | 75 | 3 | FLAG_HIDE_KORAIDON |
| Miraidon (era Kyogre) | Route19_Cave | 75 | 3 | FLAG_HIDE_MIRAIDON |
| Articuno de Galar (era Articuno) | SnowtopMountainOutside (.pory) | 60 | 2 | FLAG_HIDE_ARTICUNO_GALAR |
| Zapdos de Galar (era Zapdos) | OlivineCity_LighthouseTop (.pory) | 60 | 2 | FLAG_HIDE_ZAPDOS_GALAR |
| Moltres de Galar (era Moltres) | VictoryRoadKanto_B1F (.pory) | 60 | 2 | FLAG_HIDE_MOLTRES_GALAR |

Notas:
- Nos mapas com cena (Seafoam B1F, Route10, Mt Silver, Mt Moon) o grito, o texto e o `delay` foram mantidos; o macro repete o grito (aceitável).
- Deoxys: não usa o macro; só `setbossbattle 3` antes do `seteventmon` (Lv70) — fluxo de FLAG_BATTLED/DEFEATED_DEOXYS e puzzle intactos.
- map.json trocado (gfx `SPECIES(...)` + flag nova) em SecretCave, Route19_Cave, Snowtop, LighthouseTop, VictoryRoadKanto_B1F. LighthouseTop: o clima de tempestade agora lê FLAG_HIDE_ZAPDOS_GALAR.
- Rugidos genéricos de Koraidon/Miraidon: não havia texto de rugido; só o cry do macro.
- Os `.inc` de Snowtop/LighthouseTop/VictoryRoad/BattleCafe são gerados do `.pory`.

## Battle Café
Removidos: menus "G. Articuno/Zapdos/Moltres", "Miraidon", "Koraidon"; handlers `BattleCafe_Choose{Articuno,Zapdos,Moltres,Miraidon,Koraidon}`, `BattleCafe_ConfirmParadoxLegend`, cases de setflag 0-2, chamada de `BattleCafe_GetParadoxRewardEligibility`. Tapus, gênios e Diancie intactos (menu usa IDs explícitos, sem reindexar).

## Pendências
- `src/achievements.c` (`ObtainedGalarianBirds`, `ObtainedParadoxLegends`, linhas ~1283-1289) ainda lê FLAG_BATTLE_CAFE_{ARTICUNO,ZAPDOS,MOLTRES,MIRAIDON,KORAIDON}_RECEIVED, que ninguém mais seta: essas conquistas ficaram inalcançáveis. Trocar por `Achievement_PredicateCaughtSpecies` (ou flags de captura). Não feito (fora do escopo).
- `BattleCafe_GetParadoxRewardEligibility` (src/battle_tower.c) e `BattleCafe_NotEnoughLegendPoints` ficaram sem uso.
- Flags FLAG_BATTLE_CAFE_*_RECEIVED dessas 5 espécies ficaram órfãs (rodar flag_audit/catalogar na fase final).
- SSAqua_1F ainda faz `clearflag FLAG_HIDE_GROUDON/KYOGRE` (herança; afeta EmbeddedTower, não os novos mapas).
- Testar no jogo (não feito): fuga mantém o mon para retry; captura some o objeto.
