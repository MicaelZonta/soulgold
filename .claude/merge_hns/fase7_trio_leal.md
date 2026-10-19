# Fase 7 (início) — Steven de Vermilion vira o evento do Trio Leal

Decisão do autor (19/10/2026): manter o evento do Steven, reescrito para
Okidogi × Munkidori (latis ficam só no LatiTemple). Com o Fezandipiti do
poço de Kitakami, 3/3 do Trio Leal distribuídos. Pecharunt: evento futuro
quando o trio inteiro estiver capturado (anotado no POOL_LENDARIOS).

## Como foi mergeado
- Cena do Steven (VermilionCity, importada do HnS): coreografia intacta;
  textos reescritos com plaquinha {SPEAKER NAME_STEVEN}; multichoice nova
  MULTI_LOYAL_TWO (136). A fala planta a pista do Pecharunt ("o mestre dos
  fantoches virá atrás de VOCÊ").
- InitKantoRoamers (roamer.c) real: escolhido vira roamer de Kanto Lv60
  (dex seen marcada), usando o slot vago da Fase 6.
- SouthernIsland_Interior: estrutura vanilla dos latis reaproveitada por
  inteiro (objeto dinâmico via VAR_OBJ_GFX_ID_1 = OBJ_EVENT_GFX_SPECIES(x),
  espécie em VAR_TEMP_4, BattleSetup_StartLatiBattle) — só trocamos as
  espécies (Lv60, sem item) e renomeamos as flags vanilla órfãs:
  LATIOS_OR_LATIAS_ROAMING→LOYAL_ROAMER_RELEASED,
  {DEFEATED,CAUGHT,ENCOUNTERED}_LATIAS_OR_LATIOS→*_LOYAL_ISLAND_MON
  (renomear é grátis; números intactos).
- **Ilhas de volta à ROM**: SouthernIsland_Exterior/Interior,
  BirthIsland_Exterior, FarawayIsland_Entrance/Interior saíram dos grupos
  Emerald (rom_excluded_groups) para gMapGroup_SpecialArea — o barco do
  S.S. Aqua agora leva a destinos reais (629 mapas na ROM). Dois nomes de
  LOCALID velhos no script da ilha corrigidos (nunca montava antes).
- VAR_ROAMER_POKEMON ressignificada (0=Okidogi roama, 1=Munkidori).

## QA sugerido
- Escolher cada um; ver o aviso animado do roamer numa rota de Kanto; a
  ilha com o preterido (Eon Ticket via Steven campeão em Fuchsia);
  fuga/derrota/captura na ilha; TV/casa (scripts vanilla fora da ROM que
  setavam a flag renomeada seguem inertes).
