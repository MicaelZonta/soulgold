# Horta do Berry Master — lendário e infestações

> **Superado em parte por [`REI_DA_COLHEITA.md`](REI_DA_COLHEITA.md) (30/09/2026).** Onde os dois discordam, vale aquele.

> **Análise rev1 — 30/09/2026.** Continuação de
> [`BERRY_MASTER_DESIGN.md`](BERRY_MASTER_DESIGN.md). Duas perguntas do autor:
> 1. Tem lendário **sem fonte** que dá para ligar à horta numa sidequest?
> 2. Onde cada inseto do jogo aparece hoje, para decidir quais viram
>    **só-infestação** e como cada berry puxa uma praga diferente.
>
> **Regra de fonte (do autor):** Nexus e Battle Café **não contam**. Pela mesma
> regra de `dev_scripts/fontes_legitimas.py`, também não contam Gachapon, prêmio
> de troféu (Route 40), Game Corner e Odd Egg — esses aparecem na coluna “só
> sistema”, nunca como fonte.
>
> **De onde saem os dados:** gerados do código agora, com o mesmo parser do site
> (`tools/soulgold_docs`: `parse_wild_encounters` + todas as fontes de script), e
> não do `docs/data` publicado, que pode estar atrasado. Lendários conferidos também
> contra `.claude/rift_missions/nexus/POOL_LENDARIOS.md`.

---

## Parte 1 — O lendário da horta

### 1.1 Quem está sem fonte

**Nenhum lendário “inteiro” está sem nada**: todos saem pelo menos do Nexus. Sem
fonte **de verdade** (tirando Nexus e Battle Café), são estes 29, pela lista de
`POOL_LENDARIOS.md` §“Sem método” revisada:

| Grupo | Espécies |
|---|---|
| Ultra Beasts (só batalha sem captura nas Rift Missions) | Nihilego, Buzzwole, Pheromosa, Xurkitree, Celesteela, Kartana, Guzzlord, Stakataka, Blacephalon |
| Unova / Kalos | Reshiram, Zekrom, Kyurem, Keldeo, Xerneas, Yveltal, Zygarde, Volcanion |
| Galar | Zacian, Zamazenta, Eternatus, Regieleki, Regidrago, **Glastrier, Spectrier, Calyrex** |
| Paldea / Kitakami | Wo-Chien, Ting-Lu, **Okidogi, Munkidori**, Terapagos, **Pecharunt** |
| Outros | Deoxys (só na Birth Island, fora da ROM) |

> Correção de passagem: o site lista o **Celebi** como “só Nexus”, mas ele tem
> fonte — o evento do Ilex usa `seteventmon`, que o parser do site não lê
> (`IlexForest/scripts.inc:272`). O mesmo vale para outros encontros com
> `seteventmon`; a lista de cima já está corrigida por isso.

### 1.2 Os que combinam com a horta

| Candidato | Por que encaixa | Traz junto | Nota |
|---|---|---|---|
| **Calyrex** (+ Glastrier / Spectrier) | É literalmente o **Rei da Colheita Farta**: no jogo original, o jogador **planta** uma semente no campo do rei para ele recuperar o poder, e escolhe um dos dois cavalos | 3 lendários sem fonte | `ITEM_REINS_OF_UNITY` existe e também **não tem fonte** |
| **Pecharunt** (+ Okidogi / Munkidori) | Pêssego venenoso, mochi que enfeitiça; história de Kitakami, que **existe e é alcançável** aqui. Pecha é berry da horta | 3 sem fonte; fecha os **Loyal Three** (a Fezandipiti já está no `KitakamiWell_B1F`, os outros dois não) | Mais sombrio; puxa Kitakami para a trama |
| Wo-Chien | Tábua que seca as plantas em volta: “a praga que não é inseto” | 1 | Encaixa como vilão de uma infestação, mas é pouco |
| Buzzwole / Pheromosa | Os insetos lendários | 2 | **Não recomendo:** são das Rift Missions |

### 1.3 Recomendação: “O Rei da Colheita” (Calyrex)

É a que mais **usa** a horta, em vez de só passar por ela, e dá história ao casal.

**A premissa.** A esposa não é de Johto. Veio de **Freezington**, na Crown Tundra,
onde a avó cuidava do campo do rei. Trouxe uma semente que nunca brotou em solo de
Johto — e é por isso que ela ficou a vida inteira estudando cruzamento. O Berry
Master sabe; nunca conta. É o segredo dela, e explica a voz seca: é a voz de quem
tenta a mesma coisa há quarenta anos.

**A semente é a Enigma Berry.** É uma berry de verdade (dá para plantar sem item
novo), a descrição é “uma berry de outro mundo”, e ela **não** está na tabela de
cruzamento. Basta tirá-la do sorteio pós-Liga da esposa (a faixa Lansat..Rowap
passa a pular a Enigma, ou vira Lansat..Starf + Micle..Rowap).

| Ato | Quando | O que acontece |
|---|---|---|
| 1. O caderno | grau 4 + primeira Kee **ou** Maranga colhida (3ª geração) | Ela vê a Kee e fica em silêncio. Mostra a última página do caderno: um desenho de um rei com cabeça de nabo. Conta de Freezington. Entrega a semente (Enigma) |
| 2. A plantação | jogador planta a Enigma num canteiro da horta | Ela brota — pela primeira vez em quarenta anos. Ela chora; ele finge que não viu |
| 3. A visita | primeira noite com a Enigma madura na horta | Calyrex aparece na horta, fraco, sem cavalo. Fala por telepatia (plaquinha `???`). Come a Enigma. Pede o cavalo de volta |
| 4. A escolha | o jogador decide | A esposa conta a canção de ninar: o rei cavalgava um cavalo branco pela neve e um preto pela sombra. **Glastrier** no Ice Path, **Spectrier** num lugar só de noite (ex.: Burned Tower). O jogador vai a **um** só — como no original |
| 5. O rei | volta à horta à noite com o cavalo | Batalha contra o Calyrex no lago da horta. Depois, a esposa entrega as **Reins of Unity** (herança da avó) |

**O cavalo que não foi escolhido continua no Nexus**, e pela R1 do Nexus
(`NEXUS_REGRAS.md`) Calyrex e o cavalo escolhido passam a só aparecer lá depois de
capturados. Atualizar `POOL_LENDARIOS.md` junto.

**O que precisa de código novo:** um `special` pequeno em C que diga se há uma
Enigma madura num canteiro da horta (`GardenHasRipeBerry`, ~10 linhas sobre
`gSaveBlock1Ptr->berryTrees[BERRY_TREE_GARDEN_FIRST..LAST]`). O resto é script:
`seteventmon` + batalha (skill `adicionar-batalha-npc` não se aplica; é encontro
fixo como o do Celebi), a visita noturna com `FLAG_TEMP` (skill
`visibilidade-e-gatilhos`) e flags de progresso (skill `alocar-flag`: 1 var de
estado resolve os 5 atos sem flag).

**Alternativa:** Pecharunt como **segundo** arco, depois deste. Os pedidos de Pecha
do Berry Master sobem sem motivo; em Kitakami alguém vende mochi feito com as Pecha
da horta. Fecha os Loyal Three e dá uso a Kitakami. Fica como proposta futura.

---

## Parte 2 — Insetos

### 2.1 Onde cada inseto aparece hoje

45 famílias com algum membro Bug (Arceus e Silvally ficam de fora: só têm forma
Bug). A chance é a soma dos slots da tabela naquele mapa; “só sistema” não conta
como fonte.

| # | Família | Tipo | Onde aparece (método · nível · chance) | Nº de lugares | Só sistema |
|---|---|---|---|---|---|
| 1 | Caterpie → Metapod → Butterfree | Bug / Bug/Flying | **Route 30** — grama · Nv 3–4 · 30%<br>**Route 31** — grama · Nv 5 · 10%<br>**National Park Bug Contest** (Butterfree, Caterpie, Metapod) — grama · Nv 12–16 · 35%<br>**National Park Normal** (Metapod) — grama · Nv 13–15 · 10% | 4 | Goldenrod Gachapon |
| 2 | Weedle → Kakuna → Beedrill | Bug/Poison | **Route 30** — grama · Nv 3–4 · 10%<br>**National Park Bug Contest** (Beedrill, Kakuna, Weedle) — grama · Nv 15–17 · 35%<br>**National Park Normal** (Kakuna) — grama · Nv 13–15 · 10% | 3 | Goldenrod Gachapon |
| 3 | Paras → Parasect | Bug/Grass | **Route 30** — grama · Nv 3–4 · 20% | 1 | — |
| 4 | Venonat → Venomoth | Bug/Poison | **Route 31** — grama · Nv 5 · 10% | 1 | — |
| 5 | Scyther → Kleavor → Scizor | Bug/Flying / Bug/Rock / Bug/Steel | **Route 28** (Kleavor) — grama · Nv 53–58 · 5%<br>**National Park Normal** — grama · Nv 17–18 · 1%<br>**National Park Bug Contest** — grama · Nv 16–18 · 5%<br>**Nameless Cave B2F** (Scizor) — grama · Nv 58–68 · 30% | 4 | Goldenrod Gachapon |
| 6 | Pinsir | Bug | **National Park Normal** — grama · Nv 17–18 · 1%<br>**National Park Bug Contest** — grama · Nv 16–18 · 5% | 2 | Goldenrod Gachapon |
| 7 | Ledyba → Ledian | Bug/Flying | **Ilex Forest** — grama · Nv 11–15 · 5% | 1 | — |
| 8 | Spinarak → Ariados | Bug/Poison | **Route 30** — grama · Nv 4 · 5%<br>**Route 48** (Ariados) — grama · Nv 30–33 · 10% | 2 | Goldenrod Gachapon |
| 9 | Yanma → Yanmega | Bug/Flying | **Route 35** — grama · Nv 15–16 · 20% | 1 | Goldenrod Gachapon |
| 10 | Pineco → Forretress | Bug / Bug/Steel | **Route 36** — grama, dia · Nv 6–7 · 20% | 1 | — |
| 11 | Shuckle | Bug/Rock | **Cianwood City** — Rock Smash · Nv 20–22 · 30% | 1 | — |
| 12 | Heracross | Bug/Fighting | **Route 48** — grama · Nv 30–33 · 5%<br>**Goldenrod Shore** — Hidden Grotto · Nv 20 | 2 | Goldenrod Gachapon |
| 13 | Wurmple → Cascoon → Silcoon → Beautifly → Dustox | Bug / Bug/Flying / Bug/Poison | **Route 37** — grama · Nv 18–22 · 4% | 1 | — |
| 14 | Surskit → Masquerain | Bug/Water / Bug/Flying | **Route 34** — surf · Nv 15–24 · 30% | 1 | — |
| 15 | Nincada → Ninjask → Shedinja | Bug/Ground / Bug/Flying / Bug/Ghost | **Ruins of Alph Outside** — grama · Nv 7–8 · 15%<br>**National Park Normal** — grama · Nv 13–14 · 10%<br>**Route 50** (Ninjask) — grama · Nv 50–55 · 5% | 3 | Goldenrod Gachapon |
| 16 | Volbeat | Bug | **Kitakami Border** — grama · Nv 42–48 · 4% | 1 | — |
| 17 | Illumise | Bug | **Kitakami Border** — grama · Nv 42–48 · 20% | 1 | — |
| 18 | Anorith → Armaldo | Rock/Bug | **Ruins of Alph Lab** — fóssil (Claw) · Nv 20 | 1 | — |
| 19 | Kricketot → Kricketune | Bug | **Route 30** — grama · Nv 4 · 5% | 1 | — |
| 20 | Burmy → Mothim → Wormadam | Bug / Bug/Flying / Bug/Grass | **Ilex Forest** — grama · Nv 12–18 · 1% | 1 | — |
| 21 | Combee → Vespiquen | Bug/Flying | **Route 31** — grama · Nv 5–6 · 5% | 1 | — |
| 22 | Skorupi → Drapion | Poison/Bug / Poison/Dark | **Route 42** — grama · Nv 20–24 · 30% | 1 | — |
| 23 | Sewaddle → Swadloon → Leavanny | Bug/Grass | **National Park Normal** — grama · Nv 13–14 · 30%<br>**National Park Bug Contest** — grama · Nv 14 · 10%<br>**Route 50** (Leavanny) — grama · Nv 50–56 · 5% | 3 | — |
| 24 | Venipede → Whirlipede → Scolipede | Bug/Poison | **Ilex Forest** — grama · Nv 11–15 · 5%<br>**National Park Bug Contest** — grama · Nv 12–17 · 10%<br>**Route 45** (Scolipede) — grama · Nv 40–47 · 2% | 3 | — |
| 25 | Dwebble → Crustle | Bug/Rock | **Cliff Edge Cave** — Rock Smash · Nv 28–31 · 4% | 1 | — |
| 26 | Karrablast → Escavalier | Bug / Bug/Steel | **Route 36** — grama, noite · Nv 7–8 · 5% | 1 | — |
| 27 | Joltik → Galvantula | Bug/Electric | **Mt. Silver 1F Item Room** (Galvantula) — grama · Nv 64–65 · 2%<br>**Mt. Silver 1F Waterfall Room** (Galvantula) — grama · Nv 60–65 · 2%<br>**Ilex Forest** — grama · Nv 10–14 · 20% | 3 | — |
| 28 | Shelmet → Accelgor | Bug | **Ilex Forest** — grama · Nv 10–15 · 10% | 1 | — |
| 29 | Durant | Bug/Steel | **Union Cave B2F** — grama · Nv 23 · 1% | 1 | — |
| 30 | Larvesta → Volcarona | Bug/Fire | **Route 47** — Hidden Grotto · Nv 40<br>**Deep Ilex Forest** — encontro fixo · Nv 30 | 2 | — |
| 31 | Genesect | Bug/Steel | **Abandoned Rocket Hideout Backroom** — encontro fixo · Nv 70 | 1 | Nexus |
| 32 | Scatterbug → Spewpa → Vivillon | Bug / Bug/Flying | **National Park Normal** — Land Mons (random form) · Nv 14–17<br>**National Park Normal** — grama · Nv 14–17 · 4% | 1 | — |
| 33 | Grubbin → Charjabug → Vikavolt | Bug / Bug/Electric | **Ilex Forest** — grama · Nv 12–15 · 4%<br>**Railway Cave** (Charjabug) — grama · Nv 25–28 · 15% | 2 | — |
| 34 | Cutiefly → Ribombee | Bug/Fairy | **Route 32** — grama · Nv 7–12 · 4% | 1 | — |
| 35 | Dewpider → Araquanid | Water/Bug | **Whirl Islands 1F** — pesca · Nv 20 · 60% | 1 | — |
| 36 | Wimpod → Golisopod | Bug/Water | **Ilex Forest** (Golisopod, Wimpod) — surf · Nv 10–30 · 95%<br>**Mt Mortar 1F South** (Golisopod, Wimpod) — pesca · Nv 10–40 · 34%<br>**Mt Mortar 1F North** (Golisopod, Wimpod) — pesca · Nv 10–40 · 34%<br>**Mt Mortar B1F** (Golisopod, Wimpod) — pesca · Nv 10–40 · 34%<br>**Mt Mortar 2F** (Golisopod, Wimpod) — pesca · Nv 10–40 · 34%<br>**Mt. Silver 1F Waterfall Room** (Golisopod) — surf · Nv 60–65 · 60%<br>**Mt. Silver 2F** (Golisopod) — surf · Nv 60–65 · 60%<br>**Route 35** — surf · Nv 15–24 · 1%<br>**Mt Mortar 1F South** — surf · Nv 15–21 · 64%<br>**Mt Mortar 1F North** — surf · Nv 15–24 · 64%<br>**Mt Mortar B1F** — surf · Nv 15–24 · 64%<br>**Mt Mortar 2F** — surf · Nv 15–24 · 64% | 8 | — |
| 37 | Buzzwole | Bug/Fighting | — | 0 | Nexus |
| 38 | Pheromosa | Bug/Fighting | — | 0 | Nexus |
| 39 | Blipbug → Dottler → Orbeetle | Bug / Bug/Psychic | **Route 30** — grama · Nv 3–5 · 1% | 1 | — |
| 40 | Sizzlipede → Centiskorch | Fire/Bug | **Mt. Silver Mountain Side** (Centiskorch) — grama · Nv 55–62 · 5%<br>**Route 27** (Centiskorch) — grama · Nv 45–55 · 5%<br>**Route 26** (Centiskorch) — grama · Nv 45–55 · 5%<br>**Route 43** — grama · Nv 25–28 · 4% | 4 | — |
| 41 | Snom → Frosmoth | Ice/Bug | **Ice Path B2F** — grama, noite · Nv 31–40 · 10% | 1 | — |
| 42 | Tarountula → Spidops | Bug | **Ilex Forest** — grama · Nv 12–16 · 1% | 1 | — |
| 43 | Nymble → Lokix | Bug / Bug/Dark | **National Park Normal** — grama · Nv 14–15 · 5% | 1 | — |
| 44 | Rellor → Rabsca | Bug / Bug/Psychic | **Route 37** — grama · Nv 18–21 · 4% | 1 | — |
| 45 | Slither Wing | Bug/Fighting | **Meteor Island** — grama · Nv 57–60 · 5% | 1 | Nexus |

**O que a tabela mostra:**

- **Só 2 famílias não têm fonte:** Buzzwole e Pheromosa (Rift Missions). Todo o resto já aparece em algum lugar.
- **29 famílias estão num lugar só.** São as candidatas naturais a virar só-infestação: sai de um mapa, entra na horta.
- **A Route 30, onde fica a horta, já é a rota dos insetos:** Caterpie, Weedle, Paras, Spinarak, Kricketot e Blipbug.
- **O Bug Catching Contest** (National Park Bug Contest) usa Caterpie, Weedle, Scyther, Pinsir, Sewaddle e Venipede. **Não cortar** esses sem mexer no concurso.

### 2.2 Como o motor escolhe a praga hoje

`GetBerryPestSpecies` (`src/berry.c:2568`) olha só a **cor** da berry e devolve **uma**
espécie fixa, em **nível 14–16 fixo**. Com as cores de ORAS (`OW_BERRY_COLORS`),
as 67 berries caem em 5 cores; o roxo só tem a Enigma do e-Reader, que não existe no jogo:

| Cor | Berries | Praga hoje |
|---|---|---|
| Vermelha (12) | Cheri, Leppa, Figy, Razz, Pomeg, Tamato, Occa, Chople, Payapa, Haban, Roseli, Custap | Ledyba |
| Azul (14) | Chesto, Oran, Wiki, Bluk, Kelpsy, Cornn, Pamtre, Belue, Passho, Yache, Coba, Ganlon, Apicot, Rowap | Volbeat |
| Rosa (12) | Pecha, Persim, Mago, Nanab, Qualot, Magost, Spelon, Kasib, Colbur, Petaya, Lansat, Kee | Spewpa |
| Verde (15) | Rawst, Lum, Aguav, Wepear, Hondew, Rabuta, Watmel, Durin, Rindo, Kebia, Tanga, Babiri, Salac, Starf, Micle | Burmy |
| Amarela (14) | Aspear, Sitrus, Iapapa, Pinap, Grepa, Nomel, Chilan, Wacan, Shuca, Charti, Liechi, Enigma, Jaboca, Maranga | Combee |
| Roxa | só a Enigma do e-Reader | Illumise (na prática nunca sai) |

### 2.3 Proposta: cor escolhe o grupo, a raridade da berry escolhe o slot

Cada cor ganha **3 slots** (comum / incomum / raro). A **berry** decide o peso do
raro: berry comum quase nunca puxa o raro; berry de cruzamento puxa muito mais.
Assim “berries diferentes, chances diferentes” sai de duas coisas que o jogador
entende: a cor do fruto e o quanto ele custou para crescer.

| Cor | Comum | Incomum | Raro | Tema |
|---|---|---|---|---|
| Vermelha | Ledyba | Paras | **Heracross** | joaninha, cogumelo; besouro da seiva |
| Azul | Volbeat | Surskit | **Joltik** | vaga-lume, água do lago ao lado; aranha elétrica |
| Rosa | Cutiefly | Scatterbug | **Illumise** | polinizadores; volta a Illumise que hoje nunca sai |
| Verde | Burmy | Pineco | **Sewaddle** | casulo de folha, pinha |
| Amarela | Combee | Kricketot | **Heracross** | abelha, grilo; o besouro volta no mel |

| Berry plantada | Comum | Incomum | Raro |
|---|---|---|---|
| Faixa 1–2 do pedido (comuns) | 70% | 27% | 3% |
| Faixa 3–4 (EV e resistência) | 50% | 38% | 12% |
| Faixa 5 e 3ª geração de cruzamento | 30% | 40% | 30% |

Nível: `10 + 4 × insígnias`, teto 60 (como no `BERRY_MASTER_DESIGN.md` §6.2). A
chance de aparecer praga continua a do motor (15% por estágio, `BERRY_PESTS_CHANCE`).

### 2.4 Quem viraria só-infestação

**Sugestão para você decidir.** Critério: está em **um lugar só** (ou um lugar e o
Gachapon), **não** é do Bug Contest e combina com planta.

| Família | Hoje só em | Na horta | Recomendação |
|---|---|---|---|
| Ledyba | Ilex Forest (5%) | vermelha, comum | **cortar** |
| Combee | Route 31 (5%) | amarela, comum | **cortar** — é “a abelha da horta” |
| Burmy | Ilex Forest (1%) | verde, comum | **cortar** — hoje quase impossível de achar |
| Cutiefly | Route 32 (4%) | rosa, comum | **cortar** |
| Volbeat / Illumise | Kitakami Border (4% / 20%) | azul / rosa | **cortar** — hoje só aparecem no fim do jogo |
| Pineco | Route 36, dia (20%) | verde, incomum | cortar ou manter (é comum na Route 36) |
| Kricketot | Route 30 (5%) | amarela, incomum | cortar — está na mesma rota da horta |
| Scatterbug | National Park (4%) | rosa, incomum | cortar; a forma do Vivillon pode seguir aleatória |
| Heracross | Route 48 (5%) + grotto | raro em 2 cores | **manter** a Route 48 e o grotto; a horta é uma 2ª fonte |
| Paras, Surskit, Joltik, Sewaddle | vários | incomum/raro | **manter** — estão em 2+ lugares ou no Bug Contest |

Se cortar tudo que está em **cortar**: **8 famílias** passam a sair só da horta,
Heracross ganha uma segunda fonte, e a Illumise, que o motor nunca sorteia, passa a
sair.

**Custo de código:** trocar o `switch` de `GetBerryPestSpecies` por uma tabela
`[cor][slot]` e um peso por faixa de berry, mais tirar as espécies cortadas de
`src/data/wild_encounters.json`. Sem flag nova.

---

## Decisões

| # | Pergunta | Recomendação |
|---|---|---|
| 1 | Qual lendário liga à horta? | **Calyrex** (+ Glastrier/Spectrier); Pecharunt fica para depois |
| 2 | A esposa ser de Freezington (Crown Tundra)? | Sim — dá motivo a tudo que ela faz |
| 3 | Enigma Berry como a semente do rei? | Sim, e sair do sorteio pós-Liga dela |
| 4 | Onde vivem os cavalos? | Glastrier no Ice Path, Spectrier na Burned Tower à noite — **a confirmar** com o mapa |
| 5 | Quais insetos viram só-infestação? | Os 8 marcados **cortar** na §2.4 |
| 6 | Tabela de pragas por cor (§2.3) | Assim, e ajustar depois de jogar |
