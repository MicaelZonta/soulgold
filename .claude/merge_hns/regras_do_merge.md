# Regras permanentes do merge HnS → SoulGold

Aprendidas nas Fases 0–5 (19/10/2026). Valem para qualquer porte futuro
(Alola, Sinjoh, Snowswept, Match Call, rádio...).

## Renomes
- `_HNS`/`_hns` somem **inclusive no meio** de identificador
  (`PalletTown_hns_MapScripts`). Regex: `_hns(?=_|\b)` / `_HNS(?=_|\b)`.
- `OBJ_EVENT_GFX_MON_BASE+SPECIES_X` → `OBJ_EVENT_GFX_SPECIES(X)`;
  `addvar VAR, OBJ_EVENT_GFX_MON_BASE` → `addvar VAR, OBJ_EVENT_MON`.
- Tilesets **mantêm** o sufixo (`gTileset_*_Hns`, pasta `*_hns`) — mapas não.
- Ferramenta: `dev_scripts/importa_mapa_hns.py` (faz tudo isso + layout +
  layouts.json + preservação de local_id).

## Formato de mapa
- map.bin: metatile 10→11 bits, ID ≥640 → **+384**, colisão 2 bits→1.
- metatiles.bin 16→24 B (triple layer) pelo layer type dos atributos.
- Behaviors: 30 novos em slot idêntico; **4 remaps** (0xD7→0x2E, 0xF0→0x2F,
  0xF1→0x59, 0xF2→0x5C); bytes sem nome no P → 0 (MB_NORMAL).
  Tabela: `.claude/pokehns/behavior_remap.json`.
- Conversor: `dev_scripts/converte_kanto_hns.py` — nunca in-place.
- Divisão primário/secundário e paletas são IGUAIS (640 tiles, 7 pals) —
  sem rebase de tile, sem shift de paleta.
- Teto de secundário: 384 tiles no PNG (lavaridge_hns veio com 464; cortar).

## Constantes
- **Número de flag/var/trainer NUNCA viaja.** Re-alocar por nome:
  CUSTOM_FLAGS (marcador `PROXIMA FLAG NOVA`), vars idem, trainers em slots
  `TRAINER_UNUSED_*`.
- Itens **nunca renumeram**: item novo = id novo no fim (precedente
  ITEM_HM11=937). TM novo = id no fim + move na `FOREACH_TM` (o mapeamento
  move↔item é por lista, não aritmético). A posição na lista define o
  número do nome ("TM100...").
- `local_id` precisa do prefixo `LOCALID_` para gerar constante; enfermeira
  de Centro precisa de LOCALID_<CIDADE>_NURSE (heal_locations referencia).
- `ITEM_TM_<GOLPE>` já existe por alias se o golpe está na FOREACH_TM.

## Scripts e build
- Labels de mapa **fora da ROM** são filtrados do event_scripts
  (filter_event_scripts.py) — referência a eles quebra o link; copie o bloco
  para o mapa que usa.
- Números de linha de erro do assembler em scripts.inc são deslocados pelo
  pipeline preproc/charmap — não confie neles, ache o símbolo indefinido.
- Specials novos entram no FIM de data/specials.inc (indexados por ordem).
- Comandos de script novos: opcode no fim da tabela (último usado: 0xF2
  `checkpartymove`).
- Warp para mapa que ainda não existe → stub self-warp + linha em
  `.claude/pokehns/WARPS_STUBADOS.txt` + TODO(hns) no script.
- Música desligada em `include/config/songs_enabled.h` derruba o
  check-song-config: ligar a `SONG_MUS_*` que o mapa usa.

## O que NUNCA se copia do P
- `include/config/*` (filosofias opostas), `global.h`, `map_groups.json`,
  `species_info`/learnsets (nossos GMAX são Megas), charmap (FD 48 colide;
  {SPEAKER} deles é 1 byte).

## Reaplicação de conteúdo S (Fase 5+)
- Fonte: `.claude/pokehns/patches_soulgold/<Mapa>.diff` + `git show
  pre-kanto-hns:...`. **Nunca `git apply`** — ler e reimplementar por cima.
- Direção certa: a base HnS fica; a camada S entra POR CIMA. Nunca apagar
  conteúdo HnS para "voltar" ao S (ver fase5: agente interrompido fez isso e
  foi revertido).
- Posição antiga pode ter virado parede no layout novo — conferir
  andabilidade e realocar (expert da Route 27: (52,26)→(41,23)).
- Flagheaps do S antigo (ex. LeaveBoat do S.S. Aqua limpando FLAG_HIDE_* de
  lendários) NÃO voltam por cópia: no barco multi-viagem do HnS isso
  respawnaria boss capturado a cada viagem. Respawn é design da Fase 7.
