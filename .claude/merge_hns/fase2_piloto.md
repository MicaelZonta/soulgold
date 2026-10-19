# Fase 2 — Piloto (Pallet, Route 1, Lab, ginásio de Viridian)

- Pipeline inteiro provado e depois validado NO JOGO (QA mGBA headless,
  prints em scratchpad): carga, travessia com popup/offset, diálogo, noite,
  spin (via injeção de RAM) e headbutt (idem).
- Ensina: _hns no meio de identificador; preservar local_id nomeado
  (LOCALID_PROF_OAK ↔ heal location de Pallet); anim do kanto_general reusa
  a do johto_general (frames idênticos, callback InitTilesetAnim_General).
- Descoberta de conteúdo: NENHUM mapa do escopo usa spin tiles (ginásio de
  Viridian do HnS é sem labirinto — autor decidiu ficar fiel); headbutt
  trees existem em 16 mapas do escopo.
