# Análise de diversidade de Wild Encounters em Johto — SoulGold

Data: 2026-10-05
Fonte: `src/data/wild_encounters.json` (grupo `gWildMonHeaders`) + `docs/data/species.json` (dex nacional por espécie)

## Metodologia

- **"Mapa de Johto"** = os mapas clássicos da região (rotas 29–48, rotas 26–28 que
  ligam a Indigo Plateau, cidades de Johto, Mt Silver, Tohjo Falls/Pass, Safari
  Zone, Rocket Hideout, Dark Cave, Union Cave, Ilex Forest, National Park etc.).
  Foram **excluídos**: Kanto clássico (Victory Road Kanto, Cerulean Cave, porto de
  Vermilion) e as regiões novas do SoulGold (Kitakami, Vajra Desert/Pyramid,
  Railway Cave, Rinto Village, Faraway Island, Foggy Forest/Shore, Battle Cafe,
  Battle Factory Grounds, Southern/South Passage, Meteor Cave, Snowtop Mountain,
  Routes 49/50) — 91 mapas de Johto entraram na análise, 1917 slots de encontro no
  total (land + water + rock smash + fishing).
- **"Johto" por espécie** = dex nacional 152–251 (Geração 2), independente de em
  qual mapa ela aparece. Formas regionais (Paldean Wooper, Hisuian Sneasel,
  Galarian Corsola) herdam o dex da forma base e contam como "Johto" nessa
  contagem, mesmo quando usadas tematicamente para outra região dentro do hack —
  vale revisar caso a caso se isso é o que se quer transmitir ao jogador.
- **Diversidade por mapa** = nº de espécies distintas e índice de Shannon
  normalizado (0 a 1; 0 = um único "sabor" dominando o mapa, 1 = todas as espécies
  do mapa com peso parecido).
- Os slots de wild encounter no engine têm posição = raridade fixa (land: 12
  posições com pesos padrão 20/20/10/10/10/10/5/5/4/4/1/1; água/rock smash: 5
  posições, padrão 60/30/5/4/1). **Reordenar a posição de uma espécie dentro do
  array muda sua raridade sem tirá-la do mapa** — é a alavanca usada nas
  recomendações abaixo. (Confirme os pesos exatos vigentes em
  `src/wild_encounter.c` antes de aplicar, pois podem ter sido customizados.)

## Entregáveis

- `wild_encounter_diversidade_por_mapa.csv` — 91 mapas de Johto, com métodos de
  captura presentes, total de slots, espécies únicas, Shannon normalizado e % de
  espécies de fora de Johto.
- `wild_encounter_representacao_por_especie.csv` — 460 espécies (variando por
  forma) que aparecem em pelo menos um mapa de Johto, com geração de origem, nº
  de mapas em que aparece e nº de slots que ocupa.

## 1. Panorama geral: quem domina os encontros de Johto

| Geração | Slots | % dos slots | Espécies distintas |
|---|---:|---:|---:|
| Gen 1 (Kanto) | 716 | **37.4%** | 112 |
| **Gen 2 (Johto)** | **266** | **13.9%** | 58 |
| Gen 3 | 187 | 9.8% | 48 |
| Gen 4 | 229 | 11.9% | 46 |
| Gen 5 | 154 | 8.0% | 67 |
| Gen 6 | 91 | 4.7% | 35 |
| Gen 7 | 109 | 5.7% | 32 |
| Gen 8 | 86 | 4.5% | 30 |
| Gen 9 | 79 | 4.1% | 32 |

**O achado central**: dentro dos próprios mapas de Johto, Pokémon de Kanto (Gen 1)
ocupam **quase 3x mais slots** do que Pokémon nativos de Johto (37.4% vs 13.9%).
Somando tudo que não é Johto, **86.1% dos encontros em Johto são de fora da
região** — o inverso do que se espera de uma rota de Johto. Isso bate com o
pedido do autor: a presença de outras regiões é legítima e bem-vinda (dá
variedade), mas hoje ela não é "mais rara", ela é **a norma**, e Johto é que
parece convidado.

## 2. Mapas com pouca diversidade

Do CSV `wild_encounter_diversidade_por_mapa.csv`, ordenado por nº de espécies
únicas:

| Mapa | Slots | Espécies | Shannon | % fora de Johto | Observação |
|---|---:|---:|---:|---:|---|
| Ruins of Alph B1F | 12 | 1 (Unown) | 0.00 | 0% | **Falso positivo** — câmara do Unown é mono-espécie por design, não mexer |
| Tohjo Pass | 12 | "4" (só Floette) | 0.86 | 100% | **Falso positivo de contagem** — as 4 "espécies" são recolors cosméticos de Floette; na prática é 1 Pokémon só na rota toda |
| Blackthorn City | 15 | 3 | 0.80 | 100% | Água/pesca = só Magikarp/Poliwag/Poliwhirl, todos Kanto |
| Rocket Hideout B1F | 12 | 3 | 0.87 | 100% | Voltorb/Geodude/Koffing — temático (base da Equipe Rocket), mas 0% Johto |
| Ecruteak City | 15 | 4 | 0.94 | 75% | Água/pesca dominada por Poliwag/Magikarp/Qwilfish |
| Route33South / Route33South_2 | 14–15 | 4–5 | 0.93–0.96 | 100% | Mapa novo do hack sem nenhuma espécie de Johto |
| Tin Tower (3F–9F) | 12 cada | 4–6 | 0.94–1.00 | 100% | Torre temática a fantasmas, mas sem nenhum fantasma/voador de Johto (Gastly, Misdreavus, Murkrow, Hoothoot/Noctowl) |
| Olivine City Port Outside | 30 | 6 | 0.91 | 66.7% | — |

A lista completa (todos os 91 mapas) está no CSV. Os dois primeiros da tabela
(Ruins of Alph e Tohjo Pass) são **falsos positivos** do índice — não precisam de
ação. Os demais são reais: concentram poucas espécies e quase nenhuma de Johto,
mesmo em locais com forte identidade de Johto (cidades de Johto, Torre de
Prata).

## 3. Mapas com boa diversidade (referência do que funciona)

| Mapa | Slots | Espécies | Shannon | % fora de Johto |
|---|---:|---:|---:|---:|
| Ruins of Alph Outside | 32 | 22 | 0.98 | 81.8% |
| Ilex Forest | 27 | 19 | 0.93 | 84.2% |
| Union Cave B2F | 27 | 18 | 0.96 | 83.3% |
| Route 35 | 27 | 18 | 0.95 | 94.4% |
| Route 34 / Route 47 | 27 | 17 | 0.97 | 82–88% |

Mesmo os mapas "mais diversos" ainda têm 75–94% de espécies de fora de Johto —
ou seja, o problema de proporção Johto/não-Johto é transversal: diversidade alta
não está puxando a presença de Johto, só adicionando mais Kanto/Hoenn/Sinnoh/etc.
em cima.

## 4. Espécies sobre-representadas (fora de Johto dominando o mapa)

Top do CSV `wild_encounter_representacao_por_especie.csv`, por nº de mapas de
Johto em que aparecem:

| Espécie | Geração | Mapas de Johto | Slots |
|---|---:|---:|---:|
| Magikarp | 1 | 44 | 159 |
| Finneon | 4 | 17 | 51 |
| Poliwag | 1 | 12 | 51 |
| Lumineon | 4 | 19 | 33 |
| Basculin | 5 | 7 | 29 |
| Tentacool | 1 | 7 | 26 |
| Mimikyu | 7 | 7 | 28 |
| Golbat | 1 | 9 | 19 |
| Staryu | 1 | 9 | 18 |
| Carvanha | 3 | 6 | 17 |
| Sneasel (+ forma Hisui) | 2 | 6 | 19 |

Magikarp sozinho está em **quase metade** dos mapas de Johto (44 de 91) — isso é
esperado para Magikarp especificamente (tradição da série, pesca de baixo
nível), mas Finneon/Lumineon (Gen 4) estarem em 17–19 mapas de Johto é
desproporcional: a linha evolutiva de uma região distante está mais presente em
Johto do que a maioria dos próprios Pokémon de Johto.

## 5. Espécies de Johto sub-representadas ou ausentes

58 formas de Johto (55 espécies únicas, já que 3 têm também uma forma regional
contada à parte) aparecem em pelo menos um mapa de Johto, de um total de 100
espécies da geração. **45 espécies de Johto não aparecem em nenhum mapa de Johto
na wild encounter table.**

A maioria é esperada por design (starters, evoluções obtidas só por evolução,
bebês de breeding, lendários):

```
Chikorita/Bayleef/Meganium, Cyndaquil/Quilava/Typhlosion, Totodile/Croconaw/Feraligatr
Igglybuff, Cleffa, Togepi/Togetic, Tyrogue/Hitmontop, Smoochum, Elekid, Magby
Raikou, Entei, Suicune, Lugia, Ho-Oh, Celebi
Furret, Noctowl, Ledian, Crobat, Xatu, Ampharos, Bellossom, Sudowoodo, Jumpluff,
Sunflora, Espeon, Umbreon, Forretress, Granbull, Scizor, Magcargo, Remoraid,
Octillery, Kingdra, Porygon2
```

Essas evoluções (Furret, Noctowl, Crobat etc.) seguem o padrão clássico da série
(só a pré-evolução é selvagem) e **não** precisam de correção.

**Um caso é anômalo e não se encaixa em nenhuma dessas categorias: Sentret
(#161) não aparece em NENHUM mapa de todo o jogo** (não só em Johto — em lugar
nenhum da ROM). Sentret é a pré-evolução básica e historicamente um dos
primeiros Pokémon encontráveis em Johto (Route 29/30 no original). Sua ausência
total não parece decisão de design — é o tipo de buraco que passa no build
limpo e só aparece quando alguém procura "onde pego um Sentret" no jogo.

## Recomendações (diversidade mais natural, sem perder disponibilidade)

O pedido é explícito: **nada deve deixar de existir** — o ajuste é de
*frequência*, não de *remoção*. A ferramenta certa para isso é a posição dentro
do array de 12 (land) ou 5 (water/rock) slots, que já define raridade por peso
fixo. Trocar a posição de uma espécie com outra no mesmo mapa não tira
ninguém do mapa, só muda quem é comum e quem é raro.

1. **Promover Johto para os slots comuns (posições 0–5, pesos 10–20%) nos mapas
   onde ela já aparece, mas num slot raro.** Ex.: em mapas onde Chinchou/Marill/
   Quagsire estão nas posições 8–11 (4%/1%) e uma espécie de Kanto/outra região
   ocupa a posição 0–1 (20%), inverter as posições.
2. **Empurrar espécies de fora de Johto para os slots raros (posições 8–11,
   4%/1%) quando elas não têm papel temático especial no mapa.** Isso mantém a
   espécie **disponível** (ainda é capturável ali) só que como achado raro, que é
   exatamente o espírito pedido: "Pokémon de outras regiões devem existir, mas
   ser mais raros".
3. **Priorizar essa troca nas espécies mais desproporcionais**: Magikarp (manter
   — é tradição de pesca de baixo nível, mas pode perder uma ou duas posições
   comuns para Poliwag/Goldeen em mapas específicos), Finneon/Lumineon (Gen 4 —
   claro candidato a virar raro, hoje está mais presente que quase toda a Gen 2),
   Basculin, Mimikyu.
4. **Corrigir a ausência total do Sentret** — não é um ajuste de raridade, é um
   buraco: adicionar Sentret num slot comum de Route 29 ou Route 30 (trocando de
   lugar com uma espécie de fora de Johto que hoje ocupa slot comum ali, por
   exemplo Zigzagoon ou Rattata na Route 29).
5. **Mapas com problema real de diversidade e 0% Johto** (Blackthorn City,
   Ecruteak City, Route33South/Route33South_2, Tin Tower 3F–9F, Rocket Hideout
   B1F): adicionar 1–2 espécies de Johto temáticas nesses mapas **sem remover o
   que já existe** — há sempre pelo menos uma posição de slot raro livre para
   ocupar com algo novo se o mapa ainda não usa todos os 12/5 slots, e senão,
   aplicar a troca de posição da recomendação 2.
   - Tin Tower (torre fantasma): Gastly, Misdreavus, Murkrow — reforça o tema E
     traz Johto.
   - Blackthorn/Ecruteak (lagos): Chinchou, Marill, Qwilfish (Qwilfish já está
     em Ecruteak — bom, manter e subir sua posição).
6. **Tohjo Pass**: hoje "diverso" só na aparência — são 4 cores do mesmo
   Floette. Não é um problema de região (Floette é Gen 6, correto como raro ali),
   mas vale considerar se a rota não devia ter pelo menos uma segunda espécie
   real para não ser percebida como vazia pelo jogador, já que o contador do
   jogo mostra "nova espécie" só na primeira captura de cada cor.
7. **Não mexer em Ruins of Alph B1F** (câmara do Unown) — baixa diversidade ali é
   a mecânica correta, não um problema.
8. Depois de qualquer edição em `src/data/wild_encounters.json`, rodar `make -j$(nproc)`
   (o build regenera o `.h` derivado) e conferir no `docs/data/romhack-docs.json`
   gerado pelo `build_docs.py` se a tabela nova bate com o esperado antes de
   fechar a tarefa.
