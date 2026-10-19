# Fase 3 — Lote (168 mapas)

- 163 + piloto + MtSilver_1F_WaterfallRoom. Adiados: 13 fronteiras (F4) e
  17 de conteúdo S pesado (F5) — .claude/pokehns/DEFER_FASES_4_5.txt.
- 69 tilesets _hns (lookup de pasta pelo INCBIN do metatiles.h do P; anim
  dirs removidos — reusam as dos gêmeos S; callbacks = callback do gêmeo).
- 34 treinadores _POSTOBC/_2 em slots TRAINER_UNUSED (agente; música "Hg
  Elite Four"→"Dp Elite Four", classes sem sufixo, mugshot colors aproximadas).
- 12 OBJ_EVENT_GFX: 6 aliases, 6 importados (S.S. Aqua 96x40, Lapras surf
  192x32/6q, trem 64x64, Snorlax 32x32, Gold/Kris 16x32/9q). Defines SEM
  sufixo _HNS (o importador tira dos scripts).
- 131 flags + 10 vars em lote; 153 tabelas de encontro (47 mapas; 18 custom
  S mantidas; rótulos _Day/_Night funcionam igual nos dois geradores).
- 14 TMs novos (TM100 reusa a vaga 681; TM101–113 = 939–951) + Azure Flute
  (938, ícone provisório Poké Flute).
- Specials: CheckPartyForSpecies e Teleporter (Convert/GetRegionalForm SEM
  as aves) portados; CheckRadioStation e InitKantoRoamers = stubs TODO
  (Fase 6); AnimateTeleporter* = stub cosmético.
- Correções no caminho: enfermeiras LOCALID_<CIDADE>_NURSE; label duplicado
  MoltresRan no VictoryRoadKanto_B1F antigo; blocos do Lilycove copiados
  localmente (filtro de ROM); help windows Teleporter/Alola criadas
  (include/constants/help_window.h novo, espelha o enum).
