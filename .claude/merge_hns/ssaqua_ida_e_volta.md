# S.S. Aqua ida-e-volta, e o flagheap que apagava Kanto (24/10/2026)

Fecha a pendência da Fase 6 ("adaptar o reset de flags do `LeaveBoat` à costura
de pós-game do S; decisão: o navio volta a funcionar ida-e-volta").

## O que estava errado

**1. O barco não ia e voltava — nem saía de Olivine.** O marinheiro do porto de
Olivine só oferecia o Altar do Sol e da Lua e a Faraway Island; a S.S. Aqua não
existia daquele lado. A única forma de usar o navio era ir a pé até Vermilion
(Route 28) e embarcar lá, no caminho `MaidenVoyage` — que roda a história de
bordo e **desembarca em Vermilion**, o mesmo porto de onde o jogador saiu.

**2. O flagheap do desembarque apagava progresso de Kanto.** `LeaveBoat` trazia
da base HnS 105 `setflag`/`clearflag`/`setvar`. No HnS fazia sentido: lá o barco
é a porta de entrada de Kanto e aquilo era a inicialização da região. Em
SoulGold Kanto se alcança **a pé** (o `map_graph` mostra o caminho New Bark →
Route 27 → Route 26 → Route 22 → Viridian → … → Vermilion) e o barco é
repetível. Rodando a cada desembarque, o heap:

- limpava `FLAG_BADGE09_GET`..`16` e forçava `VAR_NUM_BADGES, 8` — as insígnias
  de Kanto sumiam;
- limpava 11 `FLAG_GOT_*` (TM Psychic, Super Rod, Up-Grade, Cleanse Tag, nuggets,
  starter de Hoenn…) — item duplicável a cada viagem;
- limpava `FLAG_HIDE_<lendário>` (Mewtwo, as três aves, Latias/Latios, Groudon,
  Kyogre, Rayquaza, Snorlax) — lendário já capturado voltava;
- zerava `VAR_KANTO_ROCKET_STORY_STATE`, `VAR_BILLS_GRANDPA`,
  `VAR_MT_SILVER_STATE`, `VAR_CINNABAR_ISLAND_STATE`, `VAR_PALLETTOWN_LABSTATE`
  e mais;
- **desfazia o sistema dos líderes de ginásio**. Encontrar um líder no mundo
  (Falkner no Celadon 5F, Bugsy na Viridian Forest, Morty na Bellchime…) faz
  `setflag FLAG_HIDE_<lugar>` + `clearflag FLAG_HIDE_DOJO_<líder>`: ele se muda
  para o Fighting Dojo. O heap fazia exatamente o inverso nos 16: esvaziava o
  Dojo e espalhava todo mundo de volta.

Nada disso dá erro de build e nada aparece no jogo até alguém viajar duas vezes.

## O que ficou

| Arquivo | Mudança |
|---|---|
| `data/scripts/new_game.inc` | os 10 `setflag FLAG_HIDE_*` que eram **inicialização de verdade** (Clefairy Doll do Copycat, treinadores do ginásio de Cerulean, Eusine em Celadon, gym guy de Seafoam, Blue em Viridian, os 4 Pichu da Viridian Forest, barco da Route 13). Agora valem para quem chega a pé também — antes só para quem chegava de barco |
| `data/maps/SSAqua_1F/scripts.inc` | o resto do flagheap saiu; o desembarque ficou com a camada SoulGold (`clearflag FLAG_HIDE_MTSILVER_RIVAL`), `VAR_SSAQUA_STATE 7` e o warp |
| `data/maps/OlivineCity_PortInside/scripts.pory` | o marinheiro passou a oferecer a S.S. Aqua **antes** do fluxo do Altar: com o S.S.Ticket, "sails for Vermilion City" — primeira vez é a viagem inaugural (entra no navio, história do avô e da neta); depois é travessia direta. Quem recusa cai no fluxo de sempre, então Altar e Faraway continuam inteiros |
| `data/maps/VermilionCity_PortInside/scripts.inc` | o `MaidenVoyage` daqui virou `FirstSail`: quem chegou a pé embarca e **vai para Olivine**, com `VAR_SSAQUA_STATE 7` (libera o menu do porto dos dois lados). Antes mandava para dentro do navio e "chegava" no mesmo porto |
| idem | `setrespawn HEAL_LOCATION_OLIVINE_CITY` na travessia para Johto — o `EnterShip` deixa o respawn em Vermilion (certo para as ilhas, que não têm Centro), e sem isto quem desmaiasse em Johto acordava em Kanto |
| idem | **"Exit" levava para o Battle Frontier**: `MULTI_VERMILION_HARBOR` tem 5 itens e o item 4 é "Exit", mas o `case 4` era o Frontier (que está em `rom_excluded_groups`). O case 4 agora é recusa; para reabrir o Frontier um dia, trocar para `MULTI_VERMILION_HARBOR_RED` |

Fluxo final: **Olivine → Vermilion** com a história na primeira vez; depois
`VAR_SSAQUA_STATE` 7 e travessia direta nos dois sentidos, pelo menu do porto
(Vermilion) ou pela pergunta do marinheiro (Olivine).

## Auditoria das flags de Kanto (pedida junto)

- `flag_audit.py --csv`: **nenhuma flag mudou de status** por causa destas
  edições (conferido regerando o CSV num worktree em HEAD e comparando). O diff
  grande do CSV é o catálogo commitado que estava defasado.
- **80 flags lidas** por script dos 209 mapas de Kanto: **nenhuma sem
  escritor** — não há porta que nunca abre.
- Flags de ocultação de NPC de Kanto: 10 são de mão única por projeto (fóssil
  levado, engenheiro que vai embora, Blue que muda de cidade); 23 não têm
  `setflag` literal, mas 21 delas são `FLAG_ITEM_*`/`FLAG_HIDDEN_ITEM_*` de
  Poké Ball no chão, escritas pelo `callstd STD_FIND_ITEM` (o engine escreve a
  flag do próprio objeto). As duas restantes são inofensivas:
  `FLAG_HIDE_CERULEANCAVE_GUARD` (NPC só de fala, nunca precisa sumir) e
  `FLAG_HIDE_VERMILION_STEVEN` (objeto estacionado em `y = -5`, fora do mapa;
  a cena o traz por `applymovement`).
- `VAR_VERMILION_CITY_STATE`, que o heap punha em 1, **ninguém lê** — var morta.

## Falta testar no jogo

Nada disto foi jogado ainda: embarcar em Olivine (viagem inaugural), a história
de bordo até a chegada, desembarcar, voltar de Vermilion, e o menu do porto dos
dois lados. O resto da Fase 6 também segue sem QA (rádio, Snorlax, menu da mãe).
