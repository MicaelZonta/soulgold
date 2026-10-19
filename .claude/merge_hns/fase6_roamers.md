# Fase 6 - Roamers (porte do P/src/roamer.c)

Arquivos: src/roamer.c, include/roamer.h, src/overworld.c. Os dois .o compilam (roamer.o, overworld.o); make completo nao rodado.

## O que entrou
- Tabelas por id: `ROAMER_LOC_TABLE_JOHTO/KANTO`. `sRoamerLocationsJohto` = a tabela ORIGINAL do SoulGold (nao a do P, que difere). `sRoamerLocationsKanto` = copia do P (rotas 1-25), sem sufixo _HNS.
- `TryAddRoamer(species, level, tableId)`; `locationTableId` gravado em `CreateInitialRoamerMon`. Save antigo: id 0 = Johto, compativel.
- `InitRoamer` continua Raikou/Entei/Suicune Lv40 na tabela Johto; deduplicacao/checagem de especie ativa so olha roamers Johto.
- `RoamerMove`/`RoamerMoveToOtherLocationSet` leem a tabela do roamer. Mantida a regra do S de evitar o mapa de 2 passos atras (o P removeu).
- `TryAttractRoamer`: 2% por lendario na party (max 12%), usa isRestrictedLegendary/isSubLegendary/isMythical (nomes iguais no S). Chamada em MoveAllRoamers.
- `TryShowRoamerFlash` + tasks (cross/race/peek) portados; hook em overworld.c logo apos `MoveAllRoamers()` (bloco de CB2_LoadMap, ~linha 897).

## Decisao dos latis
`InitKantoRoamers` existe (special ja declarado) mas so desativa roamers da tabela Kanto; NAO cria Latias/Latios. Decisao Parte D: latis so no LatiTemple. Mantida para o script do Steven (Vermilion) nao quebrar; remover junto com o special quando o Steven for re-roteirizado na Fase 7. Nao ha fonte de roamer Kanto agora (tabela Kanto fica sem uso ate alguem chamar TryAddRoamer com ROAMER_LOC_TABLE_KANTO).

## Desvios / pendencias
1. `CountFreeSpriteTiles` NAO existe no S (so no P/sprite.c). Implementado como static em roamer.c via SpriteTileAllocBitmapOp(i,2). Alternativa: portar para sprite.c.
2. `OBJ_EVENT_GFX_MON_BASE` nao existe no S; usado `OBJ_EVENT_MON`.
3. **src/debug.c:1977 chama `TryAddRoamer(sRoamerSpecies[i], 40)` com 2 args: QUEBRA o build** (fora do meu escopo). Corrigir para `TryAddRoamer(..., 40, 0)` (ROAMER_LOC_TABLE_JOHTO; incluir roamer.h ja existe).
4. P tinha dex-seen (GetSetPokedexFlag) em InitRoamer; nao portado (S nao tinha).
5. Sem teste no jogo (flash, atracao).
