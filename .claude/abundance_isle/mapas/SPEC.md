# Abundance Isle — 20 mapas (especificação comum)

Pasta base: /tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha
Kit: `kit2.py` (Grid, stamp, nine, put, plateau, cave_wall, slide_reach, learn_walls, JOHTO, pick_sand,
pick_forest, tree_base, render_blocks, check_objects, draw_object) e `desenho.py` (Tela, reduzir).
Exemplos de uso: `exterior.py`, `frost.py`, `summit.py`, `renders.py`.

## Regras
- **Só tilesets que já existem** no repositório (par primário+secundário de um layout existente). Aprenda as
  peças dos mapas que já usam o par (dump, learn_walls, neighbours_of, stamp/nine de trechos). Nada de peça "no olho".
- Peça errada não dá erro: **renderize e olhe** cada mapa antes de entregar; corrija emendas.
- Cada mapa precisa ser **interessante de explorar e temático**: segredos, itens, atalhos, um quebra-cabeça
  ou rota alternativa, treinadores coerentes. Coerente com a história abaixo e com a lore.
- Conferir: `check_objects` sem NPC em bloqueio/água; BFS da(s) entrada(s) até cada item/warp/ponto da história.
- Desenho novo só se indispensável: então 4 propostas (Tela, <=15 cores) em `<Mapa>/props/`.
- Nada no repositório é alterado. Texto de página em português; nomes no jogo em inglês.
- Sprites: N = OBJ_EVENT_GFX_N; Ghetsis = OBJ_EVENT_GFX_SAGE (placeholder); Plasma = OBJ_EVENT_GFX_SCIENTIST_1
  (placeholder); lendários = OBJ_EVENT_GFX_SPECIES(X); itens = OBJ_EVENT_GFX_ITEM_BALL.

## Entrega por mapa: `m20/<Mapa>/`
- `map.bin`, `border.bin`
- `dia.png` (render 2x com objetos), `colisao.png` (overlay=True, marcas roxas nos warps), e opcional
  `estado.png` (outro estado da história) — legenda no info.
- `info.json`:
```
{"map": "AbundanceIsle_HarvestFields", "ingame": "Harvest Fields", "w":.., "h":..,
 "primary": "gTileset_...", "secondary": "gTileset_...", "map_type": "MAP_TYPE_ROUTE|TOWN|INDOOR|UNDERGROUND",
 "warps": [{"x":..,"y":..,"dest_map":"MAP_...","dest_warp_id":"0","nota":"..."}],
 "connections": [{"direction":"east","map":"MAP_ABUNDANCE_ISLE","offset":0}],
 "objects": [ ...object_events no formato do map.json... ],
 "explorar": ["frase curta por atrativo"], "historia": "papel do mapa na história (1-3 frases)",
 "estados": {"dia":"legenda", "estado":"legenda (se houver)"}, "conferido": "o que foi verificado (BFS, check_objects)"}
```

## Mapa do mundo (20)
| # | Mapa (MAP_*) | Quem faz | Tileset sugerido | Liga com |
|---|---|---|---|---|
| 1 | ABUNDANCE_ISLE (hub, já existe 46x54) | principal | johto_general + route38_farmland | W=Harvest Fields, E=Windswept Cape, N=Gale Shore (conexões pelo mar); boca (11,16)->Frostfall 1F; boca (25,8)->Thunder Ridge; celeiro (30,23); casa (36,23) |
| 2 | ABUNDANCE_ISLE_HARVEST_FIELDS | fork A1 | johto_general + route38_farmland | E: hub (mar/surf); trilha para Spring Grove; casa do guardião |
| 3 | ABUNDANCE_ISLE_SPRING_GROVE | fork A1 | floresta (ilex_forest ou similar) | sai de Harvest Fields; jardim do Enamorus |
| 4 | ABUNDANCE_ISLE_BARN | fork A1 | interior (ex.: layout Route39_Barn como base) | hub (30,23) |
| 5 | ABUNDANCE_ISLE_FARMHOUSE | fork A1 | interior (Route39_FarmHouse como base) | hub (36,23) |
| 6 | ABUNDANCE_ISLE_KEEPER_HOUSE | fork A1 | interior de casa | Harvest Fields |
| 7 | ABUNDANCE_ISLE_WINDSWEPT_CAPE | fork A2 | johto_general + cianwood_city (tem PC) | W: hub (mar/surf); PC; cais do Plasma Frigate; boca da Gale Cave |
| 8 | ABUNDANCE_ISLE_POKEMON_CENTER | fork A2 | interior de PC | Windswept Cape |
| 9 | ABUNDANCE_ISLE_GALE_SHORE | fork A2 | praia (johto_general + secundário de costa) | S: hub (mar); pouso do Tornadus |
| 10 | ABUNDANCE_ISLE_GALE_CAVE | fork A2 | caverna (cave_default/whirl islands etc.) | Windswept Cape <-> Gale Shore (passagem por baixo do cabo) |
| 11 | FROSTFALL_CRATER_1F | fork B | johto_general + cave_ice | hub (11,16); recrutas |
| 12 | FROSTFALL_CRATER_B1F | fork B | cave_ice | quebra-cabeça de gelo (reaproveitar/expandir o de frost.py) |
| 13 | FROSTFALL_CRATER_LAB | fork B | cave_ice | Ghetsis + máquina (desenho já existe: arte_maquina, área 3x2) |
| 14 | FROSTFALL_CRATER_CORE | fork B | cave_ice | câmara do fragmento do meteorito (eco do Kyurem), segredo opcional |
| 15 | THUNDER_RIDGE | fork C | johto_general + montanha (rocha) | hub (25,8); base da Thunderspire; Thundurus |
| 16 | THUNDERSPIRE_1F | fork C | torre em ruínas (burned_tower / tin tower / mirage) | Thunder Ridge |
| 17 | THUNDERSPIRE_2F | fork C | idem | 1F <-> Summit |
| 18 | THUNDERSPIRE_SUMMIT (já existe 40x45) | principal | spear_pillar | chegada (15,34) vem do 2F |
| 19 | PLASMA_FRIGATE_DECK | fork C | navio (ssaqua_hns / port) | ancorado no cais da Windswept Cape |
| 20 | PLASMA_FRIGATE_HOLD | fork C | navio | porão: pesquisa dos DNA Splicers, Colress-like scientist |

Warps entre mapas de forks diferentes: anote no info o `dest_map` e a posição; o principal acerta os pares no fim.

## História (resumo; detalhe no index.html já publicado)
Inverno fora de época numa ilha de colheita. Ghetsis (Neo Plasma) drena o frio de um fragmento do meteorito do
Kyurem (Frostfall Crater) -> ar gelado x mar quente = tempestades -> Tornadus e Thundurus enlouquecem -> os raios
acordam a Pedra Escura no cume da Thunderspire. Quer Zekrom + Kyurem (DNA Splicers) = Kyurem Black.
N ouve a dor dos ventos e ajuda. O Plasma Frigate está ancorado no cabo (base de apoio).
Atos: 1 neve na colheita (hub) · 2 cratera (máquina) · 3 a tempestade desce (Tornadus em Gale Shore,
Thundurus em Thunder Ridge) · 4 Thunderspire (Ghetsis, Zekrom, DNA Splicers via N) · 5 primavera
(Landorus no santuário + Reveal Glass do guardião; Enamorus em Spring Grove).
Lore: Landorus vem com Tornadus+Thundurus presentes; Enamorus "Arauto da Primavera" chega pelo mar ao fim do
inverno e pune quem desrespeita a vida; Kyurem caiu num meteorito de gelo (Giant Chasm); Ghetsis usou o Kyurem
para congelar Opelucid e o Plasma Frigate; Pedra Escura na Dragonspiral Tower, despertada pelo N.

## ADENDO (Reshiram) — mais 6 mapas, so prototipo (nada no repositorio)
Os mapas 1–24 ja estao prontos; NAO mexa neles, nem no repositorio (data/, src/, include/).
Ato 6 "The Light of Truth": depois da despedida, a Lenora (que juntou a estela) descobre que os seguidores do
Heroi da Verdade esconderam a Light Stone (Reshiram adormecido) numa ilha de areia ao sul, sob ruinas como a
Relic Castle. Ghetsis escapou e manda o que sobrou do Plasma escavar. Hilda (que no BW foi escolhida pelo Reshiram)
vai junto. Na camara final o Reshiram desperta, recusa o Plasma e testa o jogador (captura). Fecho: no Santuario do
Primeiro Dragao, N e Hilda fazem uma batalha dupla final contra o jogador; murais contam o dragao original
dividido (Reshiram/Zekrom/Kyurem) e ali o jogador pode usar os DNA Splicers (Kyurem Black e White).
| # | Mapa | Quem faz | Tileset sugerido | Liga com |
|---|---|---|---|---|
| 25 | ABUNDANCE_ISLE_SUNSET_STRAIT (rota de mar) | fork D | johto_general + secundario de mar/costa | conexao NORTE com MAP_ABUNDANCE_ISLE_HARVEST_FIELDS (borda sul dela, offset a combinar; HF tem 40 de largura e cais na linha ~49, x~17); conexao SUL com Emberdune; ilhota com porta para o Santuario |
| 26 | EMBERDUNE_ISLE (ilha de areia/deserto) | fork D | johto_general + desert (VajraPyramidOutside/RegirockChamber) ou desert_village | norte: Strait (conexao); entrada das ruinas |
| 27 | TRUTHSAND_RUINS_1F | fork E | ruinas de areia (desert/pyramid/cave_sandy/ruins of alph, aprenda) | Emberdune; desce ao B1F |
| 28 | TRUTHSAND_RUINS_B1F | fork E | idem | areia movedica que derruba (buracos para baixo) como na Relic Castle; leva a Hall |
| 29 | TRUTHSAND_RUINS_HALL_OF_TRUTH | fork E | idem (ou spear_pillar/lati temple) | camara da Light Stone (Reshiram) |
| 30 | SHRINE_OF_THE_FIRST_DRAGON | fork D | santuario (dragons_den_shrine, lati_temple, spear_pillar…) | porta numa ilhota da Sunset Strait |
Personagens do Nexus sem mapa ainda livres para usar: Leon, Bea, Diantha, Agatha, Juan, Tucker, Spenser, Greta, Lucy,
Roxanne, Phoebe, Shelly, Fantina, Dawn, Cyrus, Tate, Liza, Brendan. Use 1–3 por mapa onde fizer sentido (ex.: Lucy
e Spenser exploradoras/arqueologos nas ruinas; Shelly no mar; Tate e Liza no santuario dos gemeos; Juan no estreito).
Objetos da Light Stone: reaproveite a ideia da Pedra Escura (OBJ_EVENT_GFX_DARK_STONE e sprite NOVO ainda nao no repo) —
desenhe 4 propostas da Light Stone (32x32) em props/ do Hall. Mesma entrega (map.bin, border.bin, dia.png,
colisao.png, estado.png se houver, info.json com explorar/historia, gerar.py), check_objects e BFS.
