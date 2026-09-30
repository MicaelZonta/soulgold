# Auditoria de itens — SoulGold

Levantamento completo do espaço de itens: o que cada `ITEM_*` faz, se é
obtível na campanha de Johto/Kanto e por onde. Feito para achar itens
órfãos — item que existe no código mas não tem nenhum jeito de chegar na
bolsa do jogador.

- Levantamento: 27/09/2026 · branch `soulgold-rift-missions`
- Fonte de verdade: `include/constants/items.h` (933 itens nomeados) +
  varredura de `data/maps/**/scripts.{inc,pory}`, `data/scripts/*.inc`,
  `data/event_scripts.s`, `src/data/pokemon/species_info/*.h`,
  `src/data/trainers.party` e `src/battle_script_commands.c`
- Tabela linha a linha: [`docs/SOULGOLD_ITEMS_AUDIT.csv`](../docs/SOULGOLD_ITEMS_AUDIT.csv)
- Para refazer: `python3 dev_scripts/item_audit.py --csv`

---

## 1. Resumo executivo

| Status | Quantos | O que significa |
|---|---|---|
| **OBTIVEL** | 428 | Tem `giveitem`/`additem`/loja/item escondido/Pickup alcançável na campanha |
| **SEM FONTE** | 390 | Nenhuma fonte encontrada — candidato a órfão |
| **SO VIA ROUBO/GOLPE** | 63 | Só existe como held item de Pokémon selvagem ou de treinador (Roubo/Golpe do Dia) |
| **SO EM MAPA FORA DA CAMPANHA** | 27 | Só tem fonte em mapa de Hoenn (`rom_excluded_groups`) — não existe pra quem joga a campanha |
| **SO MENCIONADO** | 25 | Aparece num script (`checkitem`, `setvar`, texto) mas nenhuma linha realmente entrega o item — verificar a mão |

**O grosso dos 390 "sem fonte" não é bug — é conteúdo do motor que este
romhack não usa.** pokeemerald-expansion carrega o item set completo de
Gen 1 a 9 + Legends Z-A; SoulGold é um remake de Johto/Kanto sem Mega
Evolution, Z-Moves, Terastal, Dynamax nem as formas regionais que viriam com
Plate/Drive/Memory. Isso sozinho explica **247** dos 390:

| Seção | Sem fonte / total | Por quê |
|---|---|---|
| Mega Stones | 0/47 | Sem mecânica de Mega Evolution |
| Z-Crystals | 0/35 | Sem Z-Moves |
| Legends Z-A Mega Stones | 0/26 | Idem, remake não usa Legends Z-A |
| Legends Z-A: Mega Dimension DLC | 25/34 | Idem |
| GEN IX ITEMS | 55/71 | Tera Shards, Booster Energy etc. — sem Terastal/Paldea |
| Memories | 19/19 | Silvally não é usável assim aqui |
| Plates | 17/17 | Arceus idem |
| Drives | 4/4 | Genesect idem |

Os **143 restantes** é que valem a leitura — são itens de Johto/Kanto,
narrativos ou de jogabilidade normal, sem fonte encontrada. Seção 2.

---

## 2. Achados reais (o que vale investigar)

### 2.1 TMs: 76 das 110 só existem pós-jogo, numa única loja

Nenhum ginásio, líder ou NPC de história dá TM em lugar nenhum da campanha.
A única fonte com item literal é `BattleFrontier_Mart` (34 TMs, `.2byte
ITEM_TM01..`), que é pós-Liga. As outras 76 TMs (a maioria dos movimentos
modernos) não têm fonte nenhuma no levantamento atual.

Se a intenção é TM ser recompensa rara de ginásio/rota como no GSC original,
isso é o buraco mais largo do levantamento — vale conferir se os scripts de
ginásio ainda não got portados com o `giveitem` de TM, ou se a decisão de
design realmente foi "TM só no Battle Frontier".

### 2.2 O arco pós-jogo de Kanto: chave e mais nada

`ITEM_PARCEL`, `ITEM_SECRET_KEY`, `ITEM_BIKE_VOUCHER`, `ITEM_GOLD_TEETH`,
`ITEM_LIFT_KEY`, `ITEM_SILPH_SCOPE`, `ITEM_TRI_PASS`, `ITEM_RAINBOW_PASS`,
`ITEM_TEA`, `ITEM_RUBY`, `ITEM_SAPPHIRE` — **sem fonte nenhuma**, apesar dos
mapas de Kanto (Viridian, Pewter, Cerulean, Vermilion, Lavender, Celadon,
Saffron, Fuchsia, Cinnabar, Indigo) existirem no `map_groups.json` como
grupos próprios, fora do Hoenn excluído.

Isso é consistente com "o pós-jogo de Kanto ainda não foi escrito" — o
mapa existe, a missão (Rocket Game Corner, Silph Co., torre de Lavender)
não. Não é bug de item, é conteúdo pendente.

Por outro lado `ITEM_CARD_KEY` e `ITEM_BASEMENT_KEY` **são** obtíveis
(`GoldenrodCity_UndergroundStorage`, `GoldenrodCity_RadioTower_5F`) — os
nomes clássicos de Kanto foram reaproveitados para o arco do Radio Tower de
Goldenrod, não para Silph Co.

### 2.3 Apricorns: confirmado, não é bug

As 7 cores + Wishing Piece/Galarica Twig/Armorite/Dynite Ore: zero fonte.
Isso já é documentado e decidido em
[`KURT_BALL_CRAFT_DESIGN.md`](KURT_BALL_CRAFT_DESIGN.md) §1.5 — a árvore de
apricorn (`APRICORN_TREE_COUNT`) está vazia de propósito, e o crafting do
Kurt usa **berry** em vez de apricorn justamente por isso. Nenhuma ação
necessária aqui.

### 2.4 Fosseis: 1 de 15 obtível

Só a rota de fóssil que já existisse ganhou fonte; as 14 variantes
(`ITEM_ARMOR_FOSSIL`, `ITEM_SKULL_FOSSIL`, os 4 `ITEM_FOSSILIZED_*` etc.)
não têm nenhum presente de história. Se o Mt. Moon / museu de Pewter vai
ter revive de fóssil, esse conteúdo ainda não foi escrito.

### 2.5 Itens menores sem fonte, baixa prioridade

- **Evolution Items (Sweets do Milcery)**: as 7 `*_SWEET` — sem fonte, mas
  só importa se Milcery/Alcremie entrarem na dex da campanha.
  **Charms** (Shiny/Catching/Exp): sem fonte — normalmente prêmio de
  pós-jogo tardio (Rotom Dex), não implementado.
- **Mail** de sabor de contest (`Glitter/Bead/Tropic/Dream/Fab Mail`): sem
  fonte — coerente com não ter Contest Hall na campanha.
- **Mulch** (4 tipos): sem fonte — só importa se houver minigame de
  jardinagem de berry além do plantio simples.
- **Bicycle, Town Map, TM Case, Berry Pouch, Poké Radar, Poké Flute, Fame
  Checker, Teachy TV**: sem fonte em lugar nenhum, nem em C. `ITEM_BICYCLE`
  quase certo é vestígio — o expansion usa `ITEM_ACRO_BIKE`/`ITEM_MACH_BIKE`
  em vez dele (achado no `data/scripts/debug.inc`). Os outros sete **valem
  confirmação com o autor**: é possível que o motor moderno os torne
  desnecessários (Town Map/TM Case viram tela de menu, não item de bolsa),
  mas nenhum arquivo do jogo confirma isso — pode ser lacuna real também.

### 2.6 Ponto a confirmar: Lilycove Dept. Store 2F ainda vende Great/Ultra Ball

O redesenho do Kurt (`KURT_BALL_CRAFT_DESIGN.md` §2.1) tirou Great Ball e
Ultra Ball de **todas** as lojas — `src/shop.c` já não referencia nenhuma
das duas, e as 9 lojas/balcões especiais listados no documento também não.
Mas `LilycoveCity_DepartmentStore_2F/scripts.inc` ainda tem as duas na
lista (`mart` block), e esse mapa está em `rom_shared_script_maps` — ou
seja, o script dele é considerado "vivo" mesmo sendo pasta do grupo
`gMapGroup_Emerald1`. Duas possibilidades:

1. O mapa não é de fato alcançável pela campanha (a entrada em
   `rom_shared_script_maps` é por outro motivo, ex. reaproveitamento de
   asset) — nesse caso não é um problema.
2. É alcançável e escapou do redesenho do Kurt — nesse caso é a única loja
   que ainda vende bola fora de Poké Ball.

Vale checar com a skill `mapa-de-ligacoes` se esse mapa está de fato
ligado ao mundo da campanha.

---

## 3. O que o script NÃO pega (limitações do método)

- **Só detecta `giveitem`/`additem`/`mart` literais, mais um padrão
  "var computada"** (`setvar VAR_X, ITEM_Y` seguido de `giveitem VAR_X` no
  mesmo arquivo — é assim que o crafting do Kurt entrega bola, uma
  sub-rotina só para as 27 receitas). Um `giveitem` cuja var venha de um
  caminho mais indireto (ex. carregada de outro arquivo, ou de uma tabela)
  passa batido e o item aparece como **SEM FONTE** por engano.
- **Held item de espécie selvagem não confere se a espécie realmente
  aparece em algum encontro alcançável** — só que o campo `itemCommon`/
  `itemRare` existe na tabela de espécie.
- **"Fora da campanha" é só o filtro de `map_groups.json`.** Um mapa de
  Johto/Kanto morto (existe mas nenhuma ligação leva até ele) não é pego
  aqui — isso é auditoria de mapa (skill `mapa-de-ligacoes`), não de item.
- Itens marcados **SO MENCIONADO** merecem leitura manual da linha: às
  vezes é um `checkitem`/`checkitemspace` de uma receita ou quest que
  consome o item (não entrega), e às vezes é de fato um presente que o
  script computa de um jeito que o regex não reconheceu.

---

## 4. Como reler o CSV

Colunas: `id, name, section, pocket, status, how, description, example_source`.
`how` lista as categorias de fonte encontradas (pode ter mais de uma);
`example_source` é o primeiro arquivo:linha (ou mapa) onde a fonte
apareceu — abra esse arquivo para confirmar antes de agir.
