# Kanto no site de docs — a lista de exclusão que virou mentira

27/10/2026. O site (`tools/soulgold_docs/`) escondia **Kanto inteiro**. Isso
estava certo quando foi escrito: o SoulGold tinha fechado o acesso a Kanto, e
mostrar aquele conteúdo na Pokédex do site era prometer o que o jogador não
alcançava. Com o Kanto do HnS adotado (197 mapas, alcançáveis a partir do
quarto do jogador), a exclusão passou a mentir no outro sentido.

## O que estava escondido

`EXCLUDED_TRAINER_MAP_GROUPS` / `_NAMES` / `_PREFIXES` em
`tools/soulgold_docs/constants.py`, lidas por `is_docs_excluded_map()` e usadas
pelos parsers de **gifts, encounters, items e forms**: 12 grupos `Indoor*` de
Kanto (158 mapas), as 11 cidades, as 25 rotas, os prefixos `MtMoon`,
`SeafoamIslands`, `RockTunnel`, `DiglettsCave`, `ViridianForest`, `MtEmber`,
`Route19_Cave` — e, pelo sufixo `_Frlg`, os 21 mapas de One Island e Mt. Ember.
Todos na ROM hoje; nenhum dos excluídos estava fora.

Efeito medido: espécies que **têm** fonte apareciam como "sem fonte". Articuno
do `SeafoamIslands_B1F`, Zapdos da `Route10`, Jirachi do `MtMoon_Outside`,
Koraidon do `SeafoamIslands_SecretCave`, Miraidon do `Route19_Cave`, o Snorlax
de Vermilion, e os treinadores/itens/encontros de Kanto inteiro. O
`dev_scripts/fontes_legitimas.py` lê o site, então a auditoria de "toda espécie
precisa de fonte legítima" herdava a mentira.

Os encontros selvagens **não** estavam escondidos (o parser de
`wild_encounters.json` passa por outro caminho), então o site vinha mostrando
Kanto por metade: mato sim, lendário não.

## O que ficou

A regra agora é só "o jogador não pode mesmo visitar":

- grupos fora da ROM (`gMapGroup_Emerald1..5`, o que `rom_excluded_groups` do
  `map_groups.json` exclui);
- quatro mapas de desenvolvimento: `NewMap1`, `TestingMap`, `Trees`,
  `Saffron_Temp`.

O sufixo `_Frlg` **não** quer dizer "fora do jogo": os 21 mapas `_Frlg` têm
conteúdo vivo — o marinheiro do Mystic Ticket em `OneIsland_Harbor_Frlg`, o
Moltres do `MtEmber_Summit_Frlg`, a Flannery em rota pelo Mt. Ember.
Alcançabilidade de verdade continua sendo assunto do
`dev_scripts/map_graph.py`, que mede o grafo; a lista do site não tenta imitar.

## Resultado

`dev_scripts/fontes_legitimas.py` depois de rodar o `build_docs.py`:

| Só vem de | Antes | Agora |
|---|---|---|
| Nexus | 47 famílias | **29** |
| Gachapon | 12 | **2** (Togepi, Gimmighoul Roaming) |
| Battle Café (e Nexus) | 18 | **9** (Forças da Natureza + Diancie) |

O import pagou quase toda a dívida de uma vez — o que a Parte E da análise
previa ("10 das 13 linhas órfãs ganham fonte com o import") era verdade e
estava invisível.

## Testes

A suíte do site (`~/.venvs/soulgold-docs/bin/python -m unittest discover -s
tools/soulgold_docs/tests -t .`) estava com **11 falhas e 1 erro** antes desta
rodada, todas expectativas velhas congeladas desde antes do import. Agora
passam as 77:

- `test_battle_cafe_prizes_are_point_exchange_sources` esperava as aves de
  Galar, os quatro Tapus, Koraidon e Miraidon no balcão de pontos; eles saíram
  do Café na Fase 7 (política do autor). O teste agora cobre o balcão de hoje —
  as Forças da Natureza — e **exige que os nove removidos não voltem**.
- `test_arceus_is_identified_as_oaks_pokedex_completion_reward`: o ovo do Oak
  não é mais de Arceus. Virou `test_oaks_pokedex_reward_is_the_manaphy_mystery_egg`.
  O `GIFT_LOCATION_NAME_OVERRIDES` também apontava para Arceus e foi para
  Manaphy.
- `test_live_kanto_snorlax_is_not_listed` → `..._is_listed`.
- `test_kanto_and_legacy_encounters_are_hidden` → `test_kanto_encounters_are_listed`.

## Achado de brinde (não é do import)

A suíte apontava `Route41` listando Tentacruel Lv100 capturável. Os quatro
guardiões da rota usam o mesmo texto e o mesmo fluxo, mas só o **primeiro**
tinha `setflag B_FLAG_NO_CATCHING` antes do `setwildbattle` e `clearflag`
depois. Os guardiões 2, 3 e 4 deixavam capturar um Tentacruel nível 100.
Corrigido copiando o padrão do primeiro.

## Nota do Oak

A decisão de 19/10 ("o ovo do Oak vira inicial de Kanto") **não** foi o que
ficou no código: o commit `4dd64a961e` fez o Oak dar o Mystery Egg, que é de
Manaphy, e tirou o Phione dos encontros de pesca. Não existe `givemon
SPECIES_BULBASAUR` em `data/` — inicial de Kanto pelo Oak nunca foi
implementado. Os catálogos que repetiam a decisão foram corrigidos para o que o
código faz.
