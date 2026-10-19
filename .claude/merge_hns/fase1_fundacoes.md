# Fase 1 — Fundações de engine (19/10/2026)

- 34 behaviors novos por **rename de slots MB_UNUSED_*** (zero mudança de
  valor no enum); predicados portados/estendidos em metatile_behavior.c;
  consumidores em field_control_avatar (placas, strength button, água
  rápida, headbutt), field_player_avatar (spin tiles; actions realocadas
  0xB4–0xB7 porque 0xB2/0xB3 eram do path finder), bike.c (Cycling Road
  Mach+Acro), event_object_movement (IsNorthBlocked).
- Scripts de placa + textos: data/scripts/hns_interactions.inc.
- Headbutt completo: comando `checkpartymove` (0xF2) com a regra "usa se
  souber OU puder aprender (TM/HM na bolsa quando houver máquina)";
  encontro reusa a tabela de rock smash do mapa, com waitstate (semântica S,
  mais correta que a do P).
- Fora do porte (não usados pelos tilesets _hns): MB_COMPUTER, MB_FOOD etc.
- Conversores validados bit a bit (0 erros): converte_kanto_hns.py.
- Gerador de constantes: gera_mapa_constantes_hns.py →
  .claude/pokehns/mapa_constantes.{md,json}.
