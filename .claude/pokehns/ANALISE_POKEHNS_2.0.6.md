# Análise: pokehns-expansion 2.0.6 (Heart & Soul) × SoulGold

> Atualizado em 19/10/2026, com o dump COMPLETO em
> `.filetransfer/pokehns-expansion-Release-v2.0.6/` (0 diretórios vazios;
> conferido). P = pokehns, S = SoulGold. Sondagem por 7 agentes (mapas,
> gráficos, engine, conflitos, lendários/eventos, lacunas de eventos,
> dimensionamento da troca de Kanto).
>
> **Decisão do autor (19/10/2026):** o Kanto do S ficou para trás; adotar o
> Kanto do P como **fonte de verdade** (jogável, testado por milhares de
> jogadores). Este documento detalha o plano.

## TL;DR

1. **O SoulGold descende do Heart & Soul.** Johto e Kanto do S são os mapas
   do HnS sem o sufixo `_hns` (503/544 têm par exato). O git confirma ports
   anteriores (`cf5b0732a8` rádio, `44c11bc004` Elm call, `73a66207ee` surf
   sprites, `2b11ed7d36` run options). Mesma base exata: expansion **1.15.2**,
   mesmos IDs de species e de música.
2. **Correção de premissa**: o acesso a Kanto **não** foi removido do S.
   Existe por terra (Route 27 → Tohjo Falls → Route 26 → Route26North →
   Route 22 → Viridian) e pelo Magnet Train. O commit `666d92bda2`
   (08/06/2026) removeu só o **IndigoPlateau externo** e ligou a Liga pela
   Route 28. O que falta de verdade (cf. `docs/KANTO_AUDITORIA.md`):
   encontros selvagens, Fly, S.S. Aqua e Red.
3. **A troca é viável e mecânica em boa parte**: 197 mapas, todos com
   homônimo no S. Mas `map.bin`/tilesets **não podem ser copiados crus**
   (seção K3) e existe conteúdo SoulGold dentro de Kanto que precisa ser
   **preservado por patch** (seção K2) — Liga/Hall of Fame (hub de lendários
   do pós-game), Rift Missions, Mewtwo boss, rival, ginásios com rematch.
4. Os gargalos reais são: **tilesets** (importar ~4 primários + ~65
   secundários como tilesets novos `_Hns`), **metatile behaviors** (~35 IDs em
   conflito, ex. `HEADBUTT_TREE` do P = `SANDPIT_EAST` no S) e **reaplicar o
   conteúdo S** por cima. O resto é conversão automatizável (scripts
   `expand_metatiles.py` e `triple_layer_convertor.py` já existem no repo).

---

# Decisões do autor (19/10/2026)

| Tema | Decisão |
|---|---|
| Kanto | HnS 2.0.6 é a fonte de verdade; **Mewtwo fica o do SoulGold** (boss Lv80 + Leaf) |
| Route 26 → Viridian | A ligação foi adicionada pelo autor no S (no original estava fechado); no Kanto novo a conexão vem do HnS |
| S.S. Aqua | Voltar a funcionar como nos jogos oficiais — ir E voltar, igual ao HnS |
| Battle Café | Lendários vão sendo removidos aos poucos: tudo que ficar obtível via Kanto/HnS sai do Café |
| Rádio 12 estações | IMPORTAR |
| Match Call GSC | IMPORTAR |
| Alola + Sinjoh/Arceus | IMPORTAR |
| Mom's Savings | IMPORTAR |
| Surf sprites Gen 4 | IMPORTAR |
| Fanfarras HGSS | IMPORTAR |
| Encontros de Kanto | IMPORTAR |
| `TryShowRoamerFlash` | IMPORTAR |
| GBS / GB Player | **IGNORAR** |
| Lendários | Fazer o inventário completo P × S, ver conflitos e decidir caso a caso (ver Parte D quando preenchida) |

---

# PARTE A — Plano: Kanto do HnS como fonte de verdade

## K1. Escopo: 197 mapas

Conjunto medido em `P/data/maps/map_groups.json` (grupos `*_Hns`), já
excluindo o que é Johto (Rocket Hideout de Mahogany, Safari do Baoba,
`Saffron_Temp` morto):

| Bloco | Mapas |
|---|---|
| 10 cidades + IndigoPlateau | 11 |
| Rotas 1–25 | 25 |
| Route26, Route26North, Route27, Route28 | 4 |
| Interiores (IndoorPallet..IndoorIndigo = 82; IndoorKantoRoutes = 28) | 110 |
| Dungeons (Tohjo Falls, Victory Road Kanto ×3, Viridian Forest, Mt. Moon ×2, Rock Tunnel ×2, Cerulean Cave ×3, Diglett's ×3, Seafoam ×4, Mt. Silver ×10, Route19_Cave) | 31 |
| S.S. Aqua | 11 |
| Safari de Fuchsia | 5 |
| **Total** | **197** |

Volume: 197 layouts, 1352 objetos (S: 1135), 126 treinadores avistadores,
18.481 linhas de `scripts.inc`, 407 KB de `map.bin`. O Kanto do P é **maior**
que o nosso (Route13 455×117 linhas; Viridian Forest 291×26; 20 mapas com
dimensões diferentes — ex. ViridianCity 56x50 vs 48x40, Route1 50x40 vs
30x40 → warps/conexões de entrada precisam de revisão).

**Mapas de fronteira — não sobrescrever cegamente** (têm lado Johto/custom):
Route 26/26North/27/28 (warps p/ ReceptionGate e casas), TohjoFalls_Cavern e
GiovanniRoom (o S tem TohjoPass + evento do Shaymin), VictoryRoadKanto_B2F e
Route22 (ReceptionGate), SaffronCity_TrainStation (warp p/ Goldenrod),
MtSilver_Outside/1F_WaterfallRoom (PokemonCenter e RegigigasRoom do S),
SSAqua_1F (porto de Olivine), CeruleanCave_1F (o S tem KitakamiBorder
apontando pra ela). Ficam intactos fora do conjunto: ReceptionGate,
Route27_House, Route28_House, KitakamiBorder, TohjoPass,
MtSilver_PokemonCenter, MtSilver_1F_RegigigasRoom, GoldenrodCity_TrainStation.
**Não copiar `map_groups.json` do P** — a troca é por nome, os grupos do S
ficam.

## K2. Conteúdo SoulGold dentro de Kanto — preservar por patch

A base dos dois é o commit `a57644df9a` (13/11/2025). Desde então, 120 dos
mapas do conjunto receberam commits não-bulk no S. O que se perderia numa
sobrescrita cega, por prioridade de preservação:

1. **Liga / Hall of Fame** (30 commits): hub de lendários do pós-game
   (Cresselia, Magearna, Heatran, Genesect, Hoopa, criação, UBs, Zeraora),
   Title Defense (2 mapas que o P nem tem), salas E4 com rematch dobrado e
   lighting; IndigoPlateau_PokemonCenter (merchant de evo items, 13 commits).
2. **Fronteiras**: Route27 (16 commits, expert da rota, ability patch),
   Route26North/28/26 (hidden items, mugshots), TohjoFalls (megastone,
   Shaymin/Gracidea).
3. **VictoryRoadKanto_1F/B1F/B2F**: Moltres, rival Silver, Rock Climb,
   tutores (B1F: 53 linhas no S vs 12 no P).
4. **CeruleanCave_B2F** (Mewtwo Lv80 boss + Leaf, 132 vs 32 linhas),
   **MtSilver_SummitDay/Night** (rival final, 148 vs 72), MtSilver_Outside
   (Fly).
5. **8 ginásios de Kanto**: rematches pós-Liga, hidden grottos, TMs,
   `FLAG_DEFEATED_*_GYM`; ViridianCity_Gym lê `FLAG_IS_KANTO_CHAMPION`.
6. **SSAqua_1F** (rival, Cameron/GS Ball), FuchsiaCity_SafariZoneEntrance
   (Steven), **Rift Missions** (Route10, Route4, Route26North,
   SaffronCity_FightingDojo; VIP do Dojo: 2016 vs 926 linhas).
7. Pontuais: BP rewards (Pallet/Viridian), Route25_BillsHouse, IV herbs
   (Route12_House), MtMoon_Shop, LavenderTown_RadioStation, Celadon Dept 4F/5F.

Perda quantificada se não preservar: 68 FLAG/VAR do S (Rift Missions, rival,
caps de história), 25 OBJ_EVENT_GFX só do S, **195 tags `{SPEAKER}` em 51
mapas** (plaquinhas teriam de ser reaplicadas), 8 `scripts.pory` (apagar ou
refazer — `.pory` regenera o `.inc`).

## K3. Conversão de formato (obrigatória)

| Item | P (vanilla) | S |
|---|---|---|
| Metatile ID no map.bin | 10 bits (máscara 0x03FF) | 11 bits (0x07FF) |
| Colisão | bits 10–11 | bit 11 |
| `NUM_METATILES_IN_PRIMARY` | 640 | 1024 |
| metatiles.bin | 16 B/metatile (dual-layer) | 24 B (triple-layer) |
| Atributos | 2 B (layer em 0xF000) | 2 B (bits de layer limpos) |

Regras: ID ≥ 640 → **+384**; colisão de 2 bits → 1 bit; metatiles 16→24 B
usando o layer type dos atributos. Ferramentas **já existentes no repo**:
- `expand_metatiles.py` — converte map.bin/border.bin 640→1024. **Perigo: roda
  in-place em `data/layouts` inteiro**; adaptar para operar só nos 197
  arquivos novos (senão reconverte o que já está convertido).
- `triple_layer_convertor.py` — metatiles.bin 16→24 B, detecta formato
  `emerald` (o caso do P).
- Não existe conversor para `setmetatile` com ID literal em script: 9 mapas
  do P usam (VermilionCity_Gym 30×, salas da Liga ~22×) → +384 à mão/sed.

**Metatile behaviors**: 43 IDs divergem; o Kanto do P usa ~35 deles. Conflitos
reais: `0xF0 HEADBUTT_TREE` (P) = `SANDPIT_EAST` (S); `0xA7 COMPUTER` =
`SANDPIT_NW`; `0xD7 TALL_GRASS_IMPASSABLE_NORTH` = `SANDPIT_NE`; spin tiles
`0x54..0x58` (Viridian Gym, Silph Co.), `CYCLING_ROAD_PULL_DOWN`,
`STRENGTH_BUTTON`, `CAVE_IMPASSABLE_NORTH` caem em `UNUSED_*` no S. Sem
portar os behaviors (+ código que os trata), o Kanto compila e anda, mas
Cycling Road, Rock Tunnel e os ginásios de puzzle quebram em silêncio — e
areia movediça aparece onde não devia.

## K4. Tilesets: importar como novos, nunca sobrescrever

- O Kanto externo do **S usa `Johto_General`** (785 metatiles) como primário;
  o do **P usa `Kanto_General_Hns`** (640). Os map.bin do P não casam com os
  tilesets do S (ex.: 181/640 metatiles diferem já convertidos; secundários
  com contagens incompatíveis — ViridianCity 280 vs 160, SaffronCity 311 vs
  230).
- Também não dá para sobrescrever `Johto_General`/`Johto_Building`/
  `Johto_NorthEast` do S — **Johto fica intocado**.
- Caminho seguro: importar os tilesets do P **com os nomes `_Hns`**
  (`gTileset_Kanto_General_Hns` etc.): ~4 primários + ~65 secundários,
  reconvertidos (triple-layer, +384) e registrados em
  `src/data/tilesets/*.h` + `data/layouts/layouts.json` (skill
  `adicionar-tileset`). 14 secundários são byte-idênticos e reutilizáveis
  (PokemonLeague, PalletTown, SilphCo, HallOfFame, 4 ginásios, Dept Store…).
- O rename "sem sufixo" vale para **mapas**, não para tilesets (colidiriam).

## K5. Dependências dos scripts do P (197 mapas)

| Tipo | Distintos | Sem equivalente no S (pós-rename) | Ação |
|---|---|---|---|
| FLAG_* | 339 | **135** (55 hidden-item, 43 HIDE, 34 outras) | criar em CUSTOM_FLAGS 0x1097+ (hidden-item no bloco 0x1F4); skills `alocar-flag` + `catalogar-flags` |
| VAR_* | 53 | **12** (VAR_PEWTER_CITY_STATE, VAR_ROUTE28_SCIENTIST, VAR_VERMILION_CITY_STEVEN, VAR_VIRIDIAN_FOREST_PICHU, VAR_ALOLA/SINJOH…) | criar em 0x4132+ |
| TRAINER_* | 201 | **34** (quase todos `*_POSTOBC_HNS`/`*_2_HNS` — rematches) | alocar IDs novos; 167 casam por nome (decidir: time do S ou do P) |
| OBJ_EVENT_GFX_* | 106 | **13** (SLEEPING_SNORLAX, SS_AQUA, SWIMMING_LAPRAS, TRAIN_WEST, OFFICER…) | maioria mapeia p/ sprite existente sob outro nome |
| ITEM_* | 135 | **46** (AZURE_FLUTE + 45 `ITEM_TM_<MOVE>` — o S numera TMs) | mapa de renomeação de TM |
| Specials | — | **10** (CheckRadioStation, InitKantoRoamers, AnimateTeleporter*, ConvertToRegionalForm, CheckPartyForSpecies, ribbons…) | portar junto; entram no fim de `data/specials.inc` |
| MUS/SE/SPECIES | — | 0 | nada |

Mais: `Common_EventScript_SetGymTrainers_hns`
(`P/data/scripts/set_gym_trainers.inc`), e os números de flag/var/trainer
**nunca viajam** (765/786 flags e 100% das vars do P colidem em número — tudo
re-aloca por nome).

## K6. Encontros selvagens

`P/src/data/wild_encounters.json`: 645 entradas, com tabelas `_Day`/`_Night`
separadas (149/90). **71 mapas de Kanto têm tabela no P vs 25 no S** (e as 25
do S são só fronteiras/dungeons custom: Mt. Silver, Cerulean Cave, Victory
Road, Routes 26–28). Rotas 1–25, Viridian Forest, Mt. Moon, Rock Tunnel,
Diglett's e Seafoam: zero no S. Água e pesca incluídas (Routes 12/19/22/26).
Atenção: rótulos do P são `gRouteX_hns_Day/_Night`; confirmar que o gerador
do S aceita o par Day/Night (nosso `wild_encounter.c` trata TIME_OF_DAY).

## K7. Etapas, por risco (menor → maior)

1. **(Baixo)** Congelar: branch + tag; gerar patch-por-mapa do conteúdo S
   (lista K2) para reaplicar depois.
2. **(Baixo)** Fixar escopo (197) e regra de fronteira: sobrescrever interior,
   preservar warps/conexões/eventos de ligação.
3. **(Baixo)** Copiar map.json/scripts.inc/layouts dos 197 por rename `_hns`→
   sem sufixo; apagar os 8 `scripts.pory` substituídos; **não** copiar
   `map_groups.json`.
4. **(Médio)** Constantes: 135 flags + 12 vars + 34 trainers + 13 GFX + 46
   itens (TMs); reaplicar `{SPEAKER}` nos 51 mapas.
5. **(Médio)** Portar os ~10 specials + set_gym_trainers do P.
6. **(Alto)** Converter 197 map.bin/border.bin (`expand_metatiles.py`
   adaptado) + `setmetatile` hex de 9 mapas (+384).
7. **(Alto)** Tilesets: 4 primários + ~65 secundários novos `_Hns`
   (`triple_layer_convertor.py`), registrar headers + layouts.json.
8. **(Alto)** Behaviors: portar ~35 IDs (Cycling Road, spin, headbutt,
   strength button) e resolver o choque com `SANDPIT_*`.
9. **(Alto)** Reaplicar conteúdo S (K2): Liga/HOF + TitleDefense, fronteiras,
   VictoryRoad B1F, CeruleanCave B2F, MtSilver Summit, ginásios, Rift
   Missions. É a parte que mais quebra sem acusar no build.
10. **(Alto)** Encontros: importar as 71 tabelas Day/Night, decidindo onde as
    25 custom do S prevalecem.
11. Validar: `make`, `dev_scripts/flag_audit.py --csv`, `map_graph.py check`,
    e teste no jogo (skill `testar-no-jogo`, com permissão): Route27→Tohjo→
    Route26→Viridian, Magnet Train, Reception Gate.

**Gargalos**: etapas 7 (tilesets), 8 (behaviors) e 9 (reaplicar S). As etapas
3 e 6 são mecânicas.

## K8. Diálogos e texto

Os diálogos de Kanto **vêm de graça** com a adoção: trocar o `scripts.inc` é
trocar o texto junto. E o texto do HnS é muito mais rico que o nosso Kanto
atual (Route13 455 vs 117 linhas, Viridian Forest 291 vs 26, Bill's House 625
vs 227; trades in-game de Kanto, presentes por telefone, evento do Pichu de
orelha espetada, times "Crystal Legacy"). O trabalho de texto é a camada
**nossa** por cima:

1. **Plaquinhas `{SPEAKER}`**: reaplicar nos 51 mapas (195 tags hoje) — regra
   do projeto é todo "Nome:" virar plaquinha (skill `nomear-falante`).
   Lembrar que o `{SPEAKER}` do HnS é outro formato (1 byte) — o texto deles
   não traz plaquinha, traz "Nome:" cru ou nada.
2. **Caixa/decap**: o S passou decap em massa nos textos; conferir o padrão de
   caixa do texto HnS importado (se vier MAIÚSCULA GSC, rodar o mesmo decap).
3. **Charmap**: texto do HnS com `{B_RIVAL_NAME}` (FD 48) colide com nosso
   `B_EFF2_TEAM1` — remapear na importação.
4. Texto do jogo permanece em inglês (regra do projeto).

## K9. Roadmap de execução — por onde começar

**Fase 0 — Preparar o terreno (1 sessão, sem risco)** ✅ FEITA (19/10/2026)
- ✅ Branch `kanto-hns-adoption` criado; tag `pre-kanto-hns` em `1ebed1705b`.
- ✅ Escopo canônico gerado: `.claude/pokehns/KANTO_ESCOPO.txt` (197 mapas,
  31 dungeons — bateu com o inventário K1).
- ✅ Patches de preservação: `.claude/pokehns/patches_soulgold/` — 197 diffs
  (`git diff a57644df9a..HEAD` por mapa, 1.2 MB) + `MANIFEST.txt` por tamanho
  + `README.md` com o modo de uso (reaplicação seletiva na Fase 5, nunca
  `git apply` cru).
- ✅ Tabela de lendários (Parte D) fechada com o autor.

**Fase 1 — Fundações de engine (nenhum mapa ainda)** ✅ FEITA (19/10/2026)
- Porte de behaviors concluído e **compilando limpo** (807 linhas em 19
  arquivos + `data/scripts/hns_interactions.inc` novo): 34 renames no enum,
  predicados novos/estendidos, spin tiles completos (movement actions
  0xB4–0xB7, anims, `lastSpinTile`), Cycling Road (Mach + Acro com rampa),
  `IsNorthBlocked`, placas/objetos interativos com textos, água rápida,
  Strength Button (boulder dispara coord event na Victory Road).
- **Headbutt completo**: comando novo `checkpartymove` (opcode 0xF2, com a
  regra HnS de "pode usar se puder aprender; TM/HM na bolsa quando o golpe
  tem máquina"), `EventScript_Headbutt` em hns_interactions.inc com encontro
  pela tabela de rock smash do mapa (semântica do S, com waitstate).
- Fora do porte por não serem usados pelos tilesets `_hns`: MB_COMPUTER,
  MB_FOOD/CABINET/SNACKS etc. (0 ocorrências nos atributos). Bike "Standard"
  do FRLG também não (é IS_FRLG).
- Bônus descoberto: o S já tinha `baobacheckmon` (0xEC) e `giveoddegg` (0xED)
  — a quest do Baoba e o Odd Egg (decisão do Togepi!) já estão no engine.
- ✅ 1.1 Análise de behaviors: `.claude/pokehns/behavior_remap.json` — 221
  behaviors usados pelos tilesets `_hns`; 180 idênticos, **30 novos em slot
  idêntico** (sem remap de byte), **4 remaps reais** (0xD7→0x2E HEADBUTT em
  0xF0→0x2F, 0xF1→0x59, 0xF2→0x5C) e 7 bytes-lixo→MB_NORMAL. Porte do código
  (header + predicados + field_control_avatar/field_player_avatar/bike/
  event_object_movement + scripts de placa) delegado a agente — ver resultado
  abaixo.
- ✅ 1.2 Conversor: `dev_scripts/converte_kanto_hns.py` (subcomandos `layout`
  e `tileset`; nunca in-place; valida dual-layer antes). Testado bit a bit em
  PalletTown + kanto_general_hns: 0 erros.
- ✅ 1.3 Constantes: `dev_scripts/gera_mapa_constantes_hns.py` →
  `.claude/pokehns/mapa_constantes.{md,json}`: 669 ok, 463 por rename `_HNS`,
  **214 faltantes** = 135 FLAG (propostas 0x1097+), 12 VAR (0x4132+), 36
  TRAINER, 13 GFX, 15 ITEM (14 TMs cujo golpe não está no FOREACH_TM do S +
  Azure Flute), 3 MAP (BATTLE_SCENE_LANCE; Melemele→Fase 8; SnowsweptCavern).
  Bônus: os aliases `ITEM_TM_<GOLPE>` do S derrubaram os TMs faltantes de 46
  para 14; e `MAP_BATTLE_SCENE_WILL/KOGA/BRUNO/KAREN` **já existem no S**.
- ⚠️ Descoberta: `SnowsweptCavern_hns` (conteúdo estendido do Mt. Silver no
  HnS, referenciado por MtSilver_1F_WaterfallRoom) **não existe no S** —
  entrar como mapa novo no lote (como Alola/Sinjoh) ou ajustar o warp.
- 1.4 Specials: adiado para quando cada sistema entrar (CheckRadioStation
  depende do rádio, InitKantoRoamers dos roamers etc.) — nenhum é usado pelo
  piloto da Fase 2.

1. **Behaviors**: adicionar os ~35 `MB_*` do P em IDs **livres** do S (não
   nos números do P — lá colidem com `SANDPIT_*`) + portar o código que os
   trata (Cycling Road, spin tiles, headbutt, strength button). Manter uma
   tabela de remapeamento `ID_P → ID_S` para usar na conversão dos atributos.
2. **Conversores**: adaptar `expand_metatiles.py` para receber lista de
   arquivos (nunca o repo todo) e aplicar também o remap de behaviors;
   validar `triple_layer_convertor.py` num tileset de teste.
3. **Constantes**: gerar automaticamente (script novo em `dev_scripts/`) o
   mapa de renomeação: 135 flags → CUSTOM_FLAGS 0x1097+, 12 vars → 0x4132+,
   34 trainers → IDs novos, 13 GFX → sprites equivalentes, 45 TMs → nomes do
   S. Saída: um `sed`-mapa reutilizável por todo o lote.
4. **Specials/comandos**: portar os ~10 specials só-P + `set_gym_trainers` +
   comandos de script que o Kanto usa (`baobacheckmon` não — é Johto).

**Fase 2 — Piloto vertical (prova o pipeline inteiro)**
- Escopo: **Pallet Town + Route 1 + PalletTown_Lab + um ginásio de puzzle
  (Viridian, por causa dos spin tiles)**.
- Pipeline por mapa: copiar `map.json`+`scripts.inc`+layout do P → rename
  `_hns` → converter map.bin/border.bin → registrar layout → aplicar sed-mapa
  de constantes → tilesets `_Hns` necessários → `make`.
- Validar de verdade: render (skill `prototipo-de-mapa`), colisão/BFS, e
  teste no jogo (skill `testar-no-jogo`, **pedir permissão antes**). Só
  avançar para a Fase 3 com o piloto aprovado no jogo.

**Fase 3 — Lote completo (197 − fronteiras)**
- Script de migração que roda o pipeline da Fase 2 em lote.
- Encontros junto (as 71 tabelas Day/Night do P), já que é o mesmo diff de
  dados.
- `make` + `map_graph.py check` a cada sub-lote (cidades → rotas →
  interiores → dungeons).

**Fase 4 — Fronteiras à mão**
- Route 26/26N/27/28, Tohjo Falls, VictoryRoadKanto_B2F↔ReceptionGate,
  SaffronCity_TrainStation, MtSilver_Outside, SSAqua_1F, CeruleanCave_1F
  (↔Kitakami): sobrescrever interior preservando warps/conexões/eventos de
  ligação do S.

**Fase 5 — Reaplicar o conteúdo SoulGold (patches da Fase 0)**
- Liga/HOF + TitleDefense, Rift Missions, Mewtwo boss (decisão: fica o
  nosso), rival, ginásios, BP rewards, plaquinhas `{SPEAKER}` (K8).
- `flag_audit.py --csv` + diff ao final (skill `catalogar-flags`).

**Fase 6 — Sistemas decididos como IMPORTAR**
- Ordem sugerida pela cadeia de dependências:
  1. **Rádio 12 estações** (pré-requisito do Snorlax e do Hoenn Sound);
  2. **S.S. Aqua** ida-e-volta (destrava Vermilion, Latis, ilhas; cuidado com
     o reset de flags do `LeaveBoat` — adaptar à nossa costura de pós-game);
  3. **Roamers de Kanto + `TryShowRoamerFlash`**;
  4. **Match Call GSC** (reverter `FREE_MATCH_CALL`, redesenhar headers);
  5. **Mom's Savings**, **surf sprites Gen 4**, **fanfarras HGSS**.

**Fase 7 — Lendários + Battle Café**
- Executar a tabela de decisão da Parte D; remover do Café o que ficou
  obtível; aves Galarian em Johto com flags novas; atualizar
  `POOL_LENDARIOS.md`.

**Fase 8 — Alola + Sinjoh/Arceus**
- 41 mapas sem par no S + tilesets próprios (alola_island, arceus_room,
  mt_silver_ancient/newsinjoh) + `VAR_ALOLA_STATE`/`VAR_SINJOH_STORYLINE`.
  Mesmo pipeline do Kanto, escopo menor.

**Fase 9 — QA de regressão**
- Roteiro de testes no jogo: travessia Johto→Kanto pelos dois caminhos,
  Magnet Train, S.S. Aqua ida/volta, um ginásio de puzzle, Snorlax via rádio,
  um lendário de cada método, Liga/HOF do S intacta, Rift Missions intactas.

---

# PARTE B — Eventos de Kanto/lendários no P (referência de implementação)

Padrão geral dos lendários: `seteventmon` + `special
BattleSetup_StartLegendaryBattle` + `GetBattleOutcome`; em `B_OUTCOME_RAN` o
mon permanece (retry); vitória/captura → `removeobject` + `setflag
FLAG_HIDE_*`. A Liga (`PokemonLeague_HallOfFame_hns`) e o desembarque do
S.S. Aqua resetam as flags de Kanto.

| Evento | Essência |
|---|---|
| **Articuno** | `SeafoamIslands_B1F_hns` Lv50, `FLAG_HIDE_ARTICUNO`; TM Ice Beam na sala |
| **Zapdos** | `Route10_hns` Lv50 |
| **Moltres** | `MtSilver_1F_MoltresRoom_hns` Lv50 |
| **Mewtwo** | `CeruleanCave_B2F_hns` Lv80, guarda liberado no game clear |
| **Lugia/Ho-Oh** | Escolha Gold/Silver na `Route39_hns` (`VAR_LUGIA_OR_HOOH`); Kimono Girls Lv48 (Eeveelutions com `settotemboost`) no teatro → Tidal/Clear Bell; cutscene de dança + descida do lendário; Lv50, pós-game Lv70; o NÃO-escolhido é liberado no pós-game pelo vovô de Pewter (asa trocada) |
| **Latias/Latios** | Steven em Vermilion (`VAR_VERMILION_CITY_STEVEN`): escolha via multichoice → `InitKantoRoamers` (roamer Lv60 em Kanto); o outro fica na Southern Island Lv50 (acesso: Eon Ticket do Steven em Fuchsia com `FLAG_IS_KANTO_CHAMPION`, via barco) |
| **Snorlax** | Vermilion, Lv50; acorda só com o **rádio sintonizado na estação Poké Flute** (`special CheckRadioStation` compara com `MUS_HG_RADIO_POKE_FLUTE`; exige `FLAG_KANTO_RADIO_GOT` do diretor de Lavender + estar em Kanto). **Dependência direta do porte do rádio de 12 estações.** |
| **S.S. Aqua** | Máquina de estados `VAR_SSAQUA_STATE` 0–7: ticket do Elm, cena do avô/neta (Metal Coat), 10+ treinadores a bordo, cama que cura; após estado 7 vira balsa multi-destino (Olivine↔Vermilion, Southern/Birth/Faraway Island, Battle Frontier) por multichoice com checagem de ticket. **Armadilha: o `LeaveBoat` reseta uma pilha de flags/vars de Kanto** (badges 9–16, estados de cidade) |
| **Safari ×2** | Johto (Baoba, Cianwood): quest 4 etapas `baobacheckmon` (comando custom), ¥200k/etapa. Kanto (Devon/Steven, Fuchsia): "Safari Level" 1–4 comprado (¥200–400k) libera Beach→Brush→Mountain→Cave. Ambas: 30 Safari Balls no bag, 1000 passos, ¥500 |
| **Pós-game** | Oak com 16 badges abre Mt. Silver; segunda Liga por `FLAG_IS_KANTO_CHAMPION` (times `_2`/`_3`/`_POSTOBC`); Red no Summit (`TRAINER_RED_HNS`), vencer dispara créditos; 16 gym rematches escalonados por badge |

## Aves Galarian em Johto (ideia do autor)

- `SPECIES_*_GALAR` (atenção: `_GALAR`, não `_GALARIAN`) habilitadas nos dois
  (`P_GALARIAN_FORMS TRUE`); o P não as usa em evento — a ideia é nossa.
- Com o Kanto do P adotado, as originais ficam: Articuno/Seafoam,
  Zapdos/Route10, Moltres/MtSilver_MoltresRoom.
- Casas Johto do S hoje duplicam as aves (Snowtop p/ Articuno, farol de
  Olivine p/ Zapdos) **compartilhando a mesma flag** — trocar por Galarian
  com **flags novas** (CUSTOM_FLAGS 0x1097+) para as 6 coexistirem;
  Moltres-Galar precisa de casa (Burned Tower pós-game? Mt. Silver lado
  Johto?).
- Registrar no Nexus: as Galar já são prêmio do Battle Café (5 pts, Lv70) e
  campeãs de Sabrina/Winona/Karen → atualizar `POOL_LENDARIOS.md` e decidir
  se o Café continua vendendo.
- Antes: `python3 dev_scripts/map_graph.py info SnowtopMountainOutside`.

---

# PARTE C — Features do P além de Kanto

## O que o S já tem (não puxar)
Followers/surf únicos (mais avançado aqui), day/night + DNS em batalha (mais
avançado aqui), Pokémon de fundo (1493 obj vs 931; `OBJECT_EVENTS_COUNT` 24
vs 16), Voltorb Flip, música HGSS (superconjunto, IDs idênticos), battle bgs
snow/volcano/pond, apricorns/Kurt/gym rematch, rádio base (4 estações).

## Vale puxar
| Esforço | Feature | Nota |
|---|---|---|
| Baixo | Encontros de Kanto | = etapa 10 do plano |
| Baixo | `TryShowRoamerFlash` | ~100 linhas: cry + sprite virtual ao entrar na rota do roamer |
| Baixo | Fanfarras HGSS (`sFanfaresHnS`) | `sound.c` |
| Baixo | Surf sprites Gen 4 | 24+ PNGs (Bibarel, Buizel/Floatzel, Shellos/Gastrodon E/W, Finneon/Lumineon); registrar via `src/data/object_events/surfable/` do P (agora presente no dump) |
| Baixo | Ice Path boulders | só map.json |
| Médio | **Rádio 12 estações** | pré-requisito do Snorlax e do Hoenn Sound (5% Hoenn em Kanto); depende de `regions.c` (`IsPlayerInJohto`) |
| Médio | Mom's Savings | 8 B SB1 + 2 flags + hooks em 5 arquivos |
| Médio | Roamers Kanto | `ROAMER_COUNT 4`, `locationTableId`, latis, atração 2%/lendário |
| Médio | Battle bgs "modern" + CAVE_WATER/GRAY_CAVE | arte agora disponível no dump; tabela `sMapDefaultEnvironments[]` é mais limpa que nossas funções |
| Médio | Clock Type runtime (`UseFakeRtc`) | 1 bit SB3 |
| Alto | Match Call GSC | conflita com `FREE_MATCH_CALL TRUE` |
| Alto | GBS/GB Player | invasivo no m4a; testar no mGBA patchado |
| Alto | Menu customização | não portar inteiro; cereja: Party Limit, Exp Mult, Shiny Chance, Item Drops |
| — | Alola + Sinjoh/Arceus | 41 mapas que não temos; candidato a conteúdo extra futuro |

## Regras do merge seletivo (resumo)
1. Números de flag/var/trainer **nunca** viajam — re-alocar por nome
   (CUSTOM_FLAGS 0x1097+, VAR 0x4132+); fechar com `catalogar-flags`.
2. charmap: `{B_RIVAL_NAME}` deles = `FD 48` = nosso `B_EFF2_TEAM1`;
   `{SPEAKER}` deles é 1 byte, nosso é 2 bytes (279 nomes).
3. `global.h` nunca por cópia (Achievements, storage tail…); SB1 tem **140 B
   livres** (não 428 — `OBJECT_EVENTS_COUNT 24` custou 288 B; corrigir a
   skill `limites-do-engine`), SB3 1528 B livres.
4. `species_info`/learnsets não se importam (nossos `*_GMAX` carregam o
   design Gigantamax-Mega).
5. Specials/comandos entram no fim das tabelas; configs têm filosofias
   opostas (eles GEN_3, nós GEN_LATEST) — nunca copiar `include/config/*`.

## Pendências abertas
- [ ] Fechar a Parte D (tabela de lendários P × S) com o autor — inclui Red
      do P × rival final do S no Summit, e times de ginásio (S ou P).
- [ ] `map_graph.py info SnowtopMountainOutside` antes das aves Galarian.
- [ ] Corrigir "428 B livres" na skill `limites-do-engine` → 140 B.
- [ ] Adaptar o reset de flags do `LeaveBoat` (S.S. Aqua) à costura de
      pós-game do S (decisão: o navio volta a funcionar ida-e-volta).
- [ ] Conferir caixa (decap) do texto HnS importado (K8).

---

# PARTE D — Lendários: inventário e decisões

Inventário completo em 19/10/2026 (grep nos scripts dos dois lados +
`POOL_LENDARIOS.md`). Políticas decididas:
- **Battle Café vai sendo esvaziado** — toda espécie que ganhar fonte via
  Kanto/HnS sai do Café.
- **Todo lendário importado do HnS é convertido para Boss Fight** (nosso
  sistema `bosslegendaryencounter`/perfis de fase), nunca o `seteventmon`
  simples deles.

## D1. Tabela de conflito (existem nos dois lados)

Legenda da coluna Decisão: ✅ = decidido; ⚠️ = **decidir com o autor**.

| Espécie | No P (HnS) | No S (SoulGold) | Recomendação | Decisão |
|---|---|---|---|---|
| Mewtwo | Cerulean B2F Lv80 estático | Cerulean B2F Lv80 **boss 4 fases + Leaf** | manter o do S | ✅ fica o do S |
| Articuno | Seafoam B1F Lv50 | Seafoam + Snowtop (mesma flag) | Kanto fica com a original; casa de Johto vira **Articuno-Galar** com flag nova | ✅ (plano das aves) |
| Zapdos | Route10 Lv50 | Route10 + farol de Olivine (mesma flag) | idem: farol vira **Zapdos-Galar** | ✅ |
| Moltres | **MtSilver_1F_MoltresRoom** Lv50 | **VictoryRoadKanto_B1F** Lv60 | — | ✅ original vai p/ sala do Mt. Silver (HnS, como boss); **Victory Road fica com Moltres-Galar** (resolve a casa dele) |
| Lugia | Lv50/70 estático | **boss 65/80 + Shadow Lugia** | — | ✅ ficam os do S |
| Ho-Oh | Lv50/70 estático | **boss 65/80** | — | ✅ fica o do S |
| Celebi | Ilex ×2 Lv40 | Ilex ×2 Lv40 | iguais — manter o do S | ✅ trivial |
| Suicune | Route25 Lv50 (série Eusine) | Route25 Lv50 **+ roamer Lv40** | manter o do S | ✅ trivial |
| Raikou/Entei | roamers Lv40 | roamers Lv40 | iguais; importar só o `TryShowRoamerFlash` | ✅ |
| Latias/Latios | roamer de Kanto Lv60 + o outro na Southern Island Lv50 | boss Lv80 no LatiTemple | — | ✅ **só o LatiTemple**; roamer/ilha do HnS não entram (Southern Island vira só destino de barco) |
| Rayquaza | EmbeddedTower Lv70 estático | EmbeddedTower **boss 4 fases** | manter o do S (mesmo mapa) | ✅ trivial |
| Groudon | **Seafoam_SecretCave** Lv70 | EmbeddedTower Lv70 + boss Lv80 Route50 | — | ✅ mantém os do S; a **SecretCave de Seafoam vira casa do Koraidon** (boss) |
| Kyogre | **Route19_Cave** Lv70 | EmbeddedTower Lv70 + boss Lv80 Route33 | — | ✅ mantém os do S; a **Route19_Cave vira casa do Miraidon** (boss) — os dois saem do Café (25 pts) quando entregues |
| Regis (os 5) + Regigigas | Sinjoh: Regirock/Regice/Registeel/Regieleki/Regidrago Lv80 + Regigigas (porta exige os 5, `VAR_REGIS_SCANNED`) | 3 clássicos Lv50 + Regigigas boss Lv70 no Mt. Silver; **Eleki/Drago sem fonte** | — | ✅ **Sinjoh é a fonte prioritária** (todos como boss). Destino das câmaras clássicas e do Regigigas do Mt. Silver: aposentar/reaproveitar — confirmar na implementação |
| Arceus | Sinjoh: boss Arceus-Steel Lv100 (não capturável) + Arceus Lv80 capturável (`VAR_SINJOH_STORYLINE` 11→13) | ovo do Oak (dex de Johto completa) | — | ✅ **Sinjoh vira a fonte**; o Oak passa a dar **um starter de Kanto** pela dex |
| Jirachi | MtMoon_Outside Lv50 (pedra à noite) | ovo do rival Silver no Summit | — | ✅ **fica o do HnS** (como boss); o rival passa a dar **ovo de Terapagos** — 1ª fonte dele (confirmado: sem fonte em P nem S; hoje só campeão da Roxanne no Nexus) |
| Deoxys | Birth Island Lv70 capturável | só fragmento no Nexus (Birth Island fora da ROM) | — | ✅ **fica o do HnS** (como boss), viável com o S.S. Aqua ida-e-volta |
| Mew | FarawayIsland_Interior Lv50 | FarawayIslandDepths Lv55 | manter o do S | ✅ trivial |
| Tapus ×4 | Alola, Lv60 estáticos (serão importados) | Battle Café 5 pts | **importar Alola → remover os 4 do Café** | ✅ (política do Café) |
| Aves de Galar | **Teleporter do Bill**: transforma a sua ave de Kanto na forma Galar (sem mon novo) | Battle Café 5 pts + campeãs do Nexus | — | ✅ encontro próprio em Johto (farol/Snowtop/Victory Road); **Teleporter entra SEM as aves** (fica p/ outras formas regionais); saem do Café quando entregues |
| Snorlax/Lapras/Sudowoodo | Vermilion/UnionCave/Route36 | mesmas flags | vêm com o Kanto novo; Snorlax depende do rádio | ✅ |

## D2. Exclusivos (sem conflito)

- **Só no P (entram com os imports):** Pichu de orelha espetada (Viridian
  Forest, Lv35, evento de 3 perseguições), Deoxys capturável, roamer de Kanto
  dos latis, Regieleki/Regidrago, cena do Arceus em Sinjoh, Tapus estáticos.
- **Só no S (intocados):** Dialga/Palkia/Giratina (+ Primal), lago trio,
  Heatran, Cresselia, Darkrai, Shaymin (DreamGarden), Manaphy/Phione,
  Victini, Meloetta, Genesect, Hoopa, Zeraora, Magearna, Marshadow, Zarude,
  espadas da justiça, corcéis + Calyrex, Ogerpon/Fezandipiti, Chien-Pao/
  Chi-Yu, linha Cosmog, Type: Null, Kubfu, Necrozma, Meltan, Poipole, UBs
  (Rift Missions), Paradoxos, Koraidon/Miraidon, gênios (Café), Nexus inteiro.

## D3. Observações para a decisão

1. **Teleporter do Bill** (Route25_BillsHouse do P): transforma mons em formas
   regionais (aves Galar, Meowth, Ponyta, Slowpoke…). Conflita com a direção
   "Galar = encontro próprio", mas é um candidato natural para resolver
   **fontes provisórias de outras formas regionais** (cf.
   `.claude/evolucoes.md`) — sugerido: importar o Teleporter **sem** as aves.
2. **Flags compartilhadas** (`FLAG_HIDE_GROUDON`/`KYOGRE` em 2 mapas no S; o
   P as usa em mapas diferentes; HoF e S.S. Aqua as limpam): qualquer fusão
   exige flag própria por casa (regra das aves vale para todos).
3. **Respawn**: o P re-spawna quase tudo na HoF e no desembarque do S.S.
   Aqua; o S já tem seu próprio hub de respawn na HoF — ao importar eventos,
   integrar ao nosso `clearflag` central, não criar um segundo.
4. **Erros achados em `POOL_LENDARIOS.md`** (corrigir quando for atualizado):
   Koraidon/Miraidon custam **25** pontos, não 5; Shaymin fica no
   **DreamGarden**, não no TohjoFalls_GiovanniRoom.

---

# PARTE E — Redistribuição do Gachapon (fontes normais via Kanto/Alola/Sinjoh)

Levantamento de 19/10/2026 (`src/game_corner_gacha.c`, pools nas linhas
1631–2060; auditoria base em `.claude/evolucoes.md`).

## E0. Descoberta: as máquinas Basic/Great/Ultra estão DESLIGADAS

O commit `2623fe46be` ("starter gacha poggers") deixou só a máquina **Master**
(29 iniciais + Pikachu/Eevee Starter) no `map.json` do
`MauvilleCity_GameCorner`. Os scripts das outras 3 existem mas nenhum mapa os
chama — ou seja, hoje as 13 linhas "só-gacha" não saem de lugar nenhum.
✅ **Decisão do autor (19/10): é intencional — o Gachapon fica só com a
Master (iniciais).** Basic/Great/Ultra aposentadas de vez; limpar os scripts
mortos e corrigir o site/`evolucoes.md` quando a redistribuição (E2/E3)
estiver entregue.

## E1. Linhas órfãs (sem fonte legítima hoje): 13

Cleffa/Clefairy, Sentret, Clamperl, Lotad, Seedot, Remoraid/Octillery,
Spinda, Relicanth, Togepi/Togetic, Porygon/Porygon2, Castform, e duas formas:
Gimmighoul Roaming e Pichu Spiky-eared.

## E2. Ganham fonte DE GRAÇA com o import (nada a fazer além do import)

| Linha | Onde (P) | Método/nível |
|---|---|---|
| Clefairy (linha toda via breeding/evolução) | Mt. Moon Cave; Routes 3/4 à noite | grama Lv46–50 |
| Sentret/Furret | Route 1 | grama Lv42–48 |
| Seedot/Nuzleaf | Routes 12/13 (+ Rock Smash) | grama Lv41–49 |
| Spinda | Route 5 | grama Lv43–47 |
| Clamperl | Route 20 (pesca) + águas de Alola | pesca Lv40–45 |
| Remoraid/Octillery | águas de Alola (Melemele/UlaUla) | pesca Lv43–45 |
| Lotad/Lombre | **Safari de Fuchsia (Beach)** | grama Lv42–45 |
| Relicanth | **Safari de Fuchsia (Cave)** | surf Lv42–45 |
| Castform | **Safari de Fuchsia (Brush)** | grama Lv48 |
| **Pichu Spiky-eared** | **evento de Viridian Forest** (3 perseguições, captura Lv35) — o agente de gacha não viu, mas o evento vem com o Kanto (Parte D2) | evento |

As tabelas da Safari de Fuchsia (4) entram junto com os 5 mapas dela, que já
estão no escopo dos 197 — basta não esquecê-las na etapa de encontros.
Obs.: Huntail/Gorebyss precisam de Deep Sea Tooth/Scale — conferir fonte dos
itens (só achamos Tooth em Route25_BillsHouse).

## E3. Continuam órfãs → redistribuição manual (3 linhas) — ✅ DECIDIDO (19/10)

| Linha | Decisão do autor |
|---|---|
| **Porygon** (+2/+Z) | ✅ Presente na **Silph Co.** (vem com o Kanto novo). Up-Grade/Dubious Disc junto. |
| **Togepi** (+Togetic/Togekiss) | ✅ O **Odd Egg da frente do Daycare** (o ovo de evento que hoje vem com bebê aleatório com chance de shiny — Elekid etc.) passa a **sempre chocar Togepi**, mantendo a mecânica de shiny. |
| **Gimmighoul Roaming** | ✅ **Sinjoh Ruins** (moedas espalhadas pelas ruínas); a forma Chest já tem fonte em Cianwood. |

As listas E2 (fontes de graça via import, incl. Safari de Fuchsia e o evento
do Pichu) também foram aprovadas como estão.

## E4. Conferências
- Ditto: fonte legítima única é Hidden Grotto (frágil, mas válida).
- As demais ~145 linhas das pools eram redundantes (já têm fonte no S).
- Ao implementar cada fonte nova: atualizar `.claude/evolucoes.md` (e remover
  a espécie do Gacha se a política for a mesma do Café — decidir).
