# Tilesets do Navel Rock — folhas numeradas

Gerado em 27/10/2026. Os números nas folhas são os **IDs que vão no mapa**, os
mesmos que o Porymap mostra.

| Arquivo | Tileset | IDs |
|---|---|---|
| `kanto_general_hns_numerado_a.png` | primário `gTileset_Kanto_General_Hns` | 0–319 |
| `kanto_general_hns_numerado_b.png` | primário, resto | 320–639 |
| `mt_ember_hns_numerado.png` | secundário `gTileset_MtEmber_Hns` | 1024–1289 |

Os seis mapas usam esse par. No Porymap eles estão em **`gMapGroup_SpecialArea`**.

## O que está no repositório agora

| Mapa | Tamanho | Estado |
|---|---|---|
| `NavelRock_Exterior` | 21×24 | **minha versão** (ilha de areia com maciço) — a que você achou feia |
| `NavelRock_Entrance` | 21×14 | original, sala retangular |
| `NavelRock_Shaft` | 21×30 | original, corredor |
| `NavelRock_FireVent` | 19×14 | original |
| `NavelRock_SeaBreach` | 19×14 | original |
| `NavelRock_SteamChamber` | 24×20 | original (a melhor das cinco) |
| `BirthIsland_Exterior` | 30×30 | **minha versão** (ilha de grama com cratera) |

## Coordenadas que não podem mudar

Se o warp ou o objeto sair do lugar, o script quebra.

| Mapa | Trava |
|---|---|
| `NavelRock_Exterior` | boca da caverna **(10,10)** · desembarque **(10,18)** |
| `NavelRock_Entrance` | **(10,12)** → Exterior · **(10,2)** → Shaft |
| `NavelRock_Shaft` | **(10,28)** → Entrance · **(10,2)** → FireVent · **(4,26)** → SeaBreach · **(18,14)** → SteamChamber |
| `NavelRock_FireVent` | **(9,12)** → Shaft · placa **(9,6)** = a fenda |
| `NavelRock_SeaBreach` | **(9,2)** → Shaft · placa **(9,12)** = a brecha |
| `NavelRock_SteamChamber` | **(11,18)** → Shaft · Volcanion **(11,7)** |
| `BirthIsland_Exterior` | desembarque **(15,24)** · gatilho **(15,16)** · Meteorite **(12,16)** · Colress **(10,16)** · Soliera **(20,16)** · triângulo **(15,12)** · a coluna **x=15** de y3 a y12, por onde o Deoxys desce |

## Peças que eu já identifiquei

Do secundário (`mt_ember_hns`), lidas dos mapas que já existem:

| Peça | ID |
|---|---|
| Piso de caverna | 1025 |
| Face da parede (a que fica logo acima do chão) | 1092 |
| Maciço de rocha | 1094 |
| Beira direita | 1095 |
| Escada / saída | 1267 |
| Água da poça | 1209 · beiradas 1203 / 1208 / 1210 |
| Preto (vazio) | 1024 |

Do primário (`kanto_general_hns`), para o exterior:

| Peça | ID |
|---|---|
| Mar | 299 |
| Areia | 220 · praia N 269, S 285, O 276, L 278 · cantos 268 / 270 / 284 / 286 |
| Grama (normal) | 8 — **cuidado: 13 é mato de encontro** (`MB_TALL_GRASS`) |
| Areia com grama | N 212, S 228, O 219, L 221 · cantos 211 / 210 / 227 / 226 |
| Maciço de rocha | corpo 113 (beiras 115 / 117) · parede 124 (pontas 123 / 125) · base 121 (pontas 120 / 122) |
| Boca de caverna | 169 |

**Atenção:** 112 e 114 são a transição da rocha para **grama** — ficam com pixel
verde se usados na areia.

## Mapa de referência

O único mapa do repositório desenhado à mão com esse mesmo par de tilesets é o
**`NewSinjoh_HotSprings`** (55×42). Vale abrir ao lado: é de lá que saem as
convenções de parede (topo, face, canto) e de poça com borda.

## Quando terminar

Me avise e eu rodo por cima: `map_graph`, BFS de cada sala provando que dá para
ir do desembarque até o Volcanion, conferência das travas acima e o build. Eu
**não** regenero mapa por cima do seu — a regra aqui é comparar antes com o
`diff_mapas.py` e aplicar só o que você pedir.

`grades_do_codex.txt` nesta pasta tem as plantas que o Codex propôs, em ASCII,
caso queiram servir de ponto de partida. `.` chão, `#` parede, `:` vazio,
`~` água, `S` escada, `*` objeto.
