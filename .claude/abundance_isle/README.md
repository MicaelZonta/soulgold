# Abundance Isle — protótipo e estado da implementação

Aventura de 35 mapas (6 ilhas) que dá fonte de verdade a Zekrom, Reshiram, Kyurem Black/White
(DNA Splicers), Tornadus, Thundurus, Landorus e Enamorus, com N, Hilda e Ghetsis.
Proposta completa (história, lore, cenas, missões, mapas, desenhos):
**https://claude.ai/artifact/G3mY3cP6pfrz1rwntS52c1** (cópia em `pagina/index.html`).
Método e lições: skill `criar-aventura`.

## Pastas

- `mapas/<Mapa>/` — `map.bin`, `border.bin`, `info.json` (warps, conexões, objetos, explorar,
  história), `gerar.py` e `props/` (propostas de desenho). Os nomes de pasta são os do protótipo;
  o nome final de cada mapa está em `instalar/maps.py` (`MAPS`).
- `instalar/` — `maps.py` (layouts, map.json, grupo, MAPSEC, flags, var, includes), `scripts.py` +
  `cond.py` (scripts.inc esqueleto com visibilidade por estado), `do_art.py` + `art.py` (desenhos nos
  secundários clonados), `state.json` (itens e treinadores pendentes).
  **Os caminhos de origem apontam para o scratchpad da sessão de 30/10/2026**: ajuste `SC`/`M20` para
  `.claude/abundance_isle/mapas` antes de rodar de novo.

## Decisões do autor

Santuário **A** (hokora), máquina **D** (divisor de DNA), Pedra Escura **C** (escama em espiral),
avião **A** (cargueiro), Light Stone **C**, canto de brinquedos do N **A** (tileset `ns_room`), acesso por
**barco em Olivine depois da Liga**.

## Estado no repositório (30/10/2026, sem commit; build limpo, 659 mapas alcançáveis)

Pipeline (rodar nesta ordem a partir da raiz do repo):
`instalar/fase3.py` (posições → `extras.json`) → `instalar/maps.py` → `instalar/treinadores.py` → `instalar/maps.py` →
`instalar/fase2.py` (chama `fase3.build`) → `instalar/scripts.py` → `instalar/selvagens.py` → `instalar/fauna_johto.py` → `make`.
(`instalar/grama.py` só uma vez, antes do `maps.py`: pinta a grama no map.bin do protótipo.)
Os caminhos já apontam para `.claude/abundance_isle/`. `scripts.py` não sobrescreve um `scripts.inc` com o marcador `@ FASE2`.

Feito:
- **Fase 1:** 35 mapas (grupo `gMapGroup_AbundanceIsle`), 14 MAPSECs, tilesets clonados `abundance_farmland`,
  `frostfall_crater`, `skyla_hangar`, `thunder_ridge`, `ns_room` (canto de brinquedos A); sprites `DARK_STONE` (C) e `LIGHT_STONE` (C); warps que caem em peça sem comportamento de warp viram gatilho de coordenada; barco Olivine <-> ilha
  pós-Liga (`OlivineCity_PortOutside/scripts.pory` + `fase2/AbundanceIsle.inc`); var 0x4157; flags 0x1199..0x11EF
  (6 lendários + 81 itens), catalogadas.
- **Fase 2a:** 58 treinadores comuns + 5 de história (`TRAINER_ABUNDANCE_*`), times por área (70–80), sem ability/itens.
  Plasma usa classe/pic Scientist (placeholder); Ghetsis usa Sage; N & Hilda usa Psychic M.
- **Fase 2b:** história completa em `fase2/*.inc` (gerada por `instalar/fase2.py`): estados 0..14, Ghetsis 1/2/3, máquina,
  neve, atalhos de gelo, 6 lendários (`bosslegendaryencounter`), Reveal Glass, DNA Splicers, dupla final, murais.
  25 falantes novos. `requiresCaught` no Nexus para Zekrom e Reshiram. `.claude/evolucoes.md` atualizado.

- **Fase 3** (`instalar/fase3.py`): as 16 missões secundárias (estela, pergaminhos da Cynthia, sementes + barraca
  diária, Jessie & James em 3 estágios, Skyla com voo para Olivine, Winona → Volkner, trocas do Byron, Zinnia com
  Kyurem, velas do Allister, uniforme do Frigate + Rosa, Barry, Nemona diária, perguntas do Alder, jardim do Ramos,
  murais da Lucy, Tate & Liza, Greta, Noland); quadro de avisos, carta do N, revanche diária de N & Hilda, Arena do
  Festival (sorteio diário entre 4 bancos), para-raios do 3F (portões por `setmetatile` + `FLAG_TEMP_15..18`;
  simulado: só abre com os 4 portões, 10 toques no caminho mínimo), ponto de cura da Windswept Cape, e fala própria
  em todo NPC que dizia "...". `place()` só põe placa/item em célula alcançável a partir dos warps (o fragmento 2
  fica atrás da pedra do Rock Smash, no esconderijo do Noland, de propósito). 127 flags da ilha `EM_USO`.

- **Selvagens** (`instalar/selvagens.py`, 31/10/2026): 17 mapas em `wild_encounters.json` — mar/lago e pesca,
  cavernas de gelo (Deino/Zweilous/Hydreigon raros no Lab/Core), torre (elétricos, fantasmas, Golurk, Fraxure/Haxorus),
  navio afundado (fantasmas, fósseis de Unova), Spring Grove (primavera: Deerling/Sawsbuck, Comfey), Gale Cave
  (Woobat/Noivern, Rock Smash), Emberdune (deserto: Krookodile, Darmanitan, Larvesta rara), fundo do estreito.
  Níveis 66–76. Só onde há peça de encontro; Engine Room do Frigate sem encontro de propósito.

- **31/10/2026, parte 2:** grama alta pintada no hub, Harvest Fields, Gale Shore e Thunder Ridge (`instalar/grama.py`, no map.bin
  do protótipo); sábados (N & Hilda em dupla na arena com os bancos vazios, Mulch na barraca, oferenda no santuário,
  barraca "honesta" de Jessie & James); noite (20h–6h) com portas trancadas na Cape e na Keeper House (`sLockedTownDoors`)
  e sino às 18h na Cape depois da primavera; dias de tempestade pós-jogo (1 em 3, `VAR_ABUNDANCE_STORM`): chuva com raios no
  Ridge, temporal na Gale Shore, tabela de selvagens própria (`src/wild_encounter.c`) e revanches de Volkner, Elesa e Winona;
  quedas com animação (`DoFallWarp`) nos 6 buracos/sumidouros; sacos de sementes e fragmentos da estela visíveis (objetos);
  Togetic, Gimmighoul Roaming e Porygon2 (presos ao Gachapon) como selvagens da ilha.

Falta:
- velas, murais e navio Plasma Frigate: 4 propostas de arte cada em https://claude.ai/artifact/SwhnvPEEqaueG74rYz1S8u
  (`arte_nova/`), esperando a escolha do autor;
- encontro raro "do frio" na plantação à noite no ato 1;
- **teste no jogo**: rodada 1 em 31/10/2026 (19 testes, https://claude.ai/artifact/8P7Li95wVnaTDB2L4KvfDk) e rodada 2
  (15 testes, sábados/noite/sino/tempestade/queda/sacos/Team Plasma + Nexus, https://claude.ai/artifact/NwWg6gNqAA9eTFqZLwkBhK).
  Rodada 3 (história principal 1→14, PASS; corredor do Lab corrigido): https://claude.ai/artifact/RWcKcesmaozazxUeYLG8pw.
  Rodada 4 (missões Cynthia, Zinnia, Allister, Ramos, Lucy, Spenser, Tate & Liza, carta do N: PASS; recruta do Thunderspire 2F
  tirado do corredor): https://claude.ai/artifact/RJbxdXfpBJzYBEZpQui2cz. Ferramenta: criar-aventura/ferramentas/treinador_tranca.py;
- fauna: `instalar/fauna_johto.py` enxugou os mapas densos de Johto (38 mudanças, log em `instalar/fauna_johto.log`;
  16 espécies de Unova ganharam lugar na ilha). Rotas com 9 espécies e só exclusivas de fora (ex.: Route 33) ficaram como estavam.
