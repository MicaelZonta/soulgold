# O Rei da Colheita — a horta do Berry Master, completa

> **Proposta rev1 — 30/09/2026; rev2 (Galar) §13; rev3 (revisão, Crown Tundra, 10 falas por evento, batalhas de sempre) §14; rev4 (as dungeons dos corcéis; sem o Will) §15.** Nada implementado. Junta num sistema só a
> horta ([`BERRY_MASTER_DESIGN.md`](BERRY_MASTER_DESIGN.md)), as infestações e o
> lendário ([`LENDARIO_E_INFESTACAO.md`](LENDARIO_E_INFESTACAO.md)). **Onde este
> documento e os dois anteriores discordam, vale este.**
>
> Pedidos do autor que ele responde:
>
> | Pedido | Onde |
> |---|---|
> | Sidequest “O Rei da Colheita” inteira, com eventos e diálogos | §8 |
> | Personagens para deixar a sidequest interessante | §1 |
> | Rellor, Blipbug, Scatterbug, Combee, Volbeat, Illumise, Wurmple e Dwebble **só** por infestação, mais outros comuns | §7 |
> | O Berry Master só dá berries que você **abriu** | §3 |
> | **Todas** as berries obteníveis pela horta | §4 (58 receitas, das 8 iniciais até Lansat e Starf) |
> | Upgrade de nível da horta | §5 |
> | Tarefa repetitiva com muitas falas diferentes, em lugares diferentes por horário (“mini Harvest Moon”) | §2 e §9 |
>
> Texto do documento em português; **tudo que aparece no jogo, em inglês**. As
> falas estão em prosa: quebrar linha com `nomear-falante/medir_linha.py` na hora
> de escrever o `.inc`.

---

## 0. Em uma tela

**O dia na horta** (repete para sempre):

1. De manhã o Bram rega a horta. Você fala com ele: ele te dá **2 ou 3 berries do
   seu Livro** e o **pedido do dia**.
2. Você planta, rega, arranca erva, **enfrenta a praga** (o inseto que só vive ali).
3. Duas berries diferentes plantadas lado a lado podem **cruzar**. A berry nova que
   você colhe pela primeira vez entra no **Livro de Berries**.
4. A Laurel passa o dia na horta e, à noite, estuda o caderno. É ela quem diz qual
   par plantar para descobrir a próxima berry.
5. O Livro cheio e o dinheiro pagam as **reformas da horta** (nível 1 a 5).

**A história** (uma vez): pragas na horta → o Bugsy vem estudar → pegadas de cavalo
à noite → o segredo da Laurel → a semente do rei → o Calyrex no canteiro dela → a
escolha do corcel → o rei volta a ter colheita.

| Peça | Resumo | Custo novo |
|---|---|---|
| Rotina por horário | Bram, Laurel, Tilly e Bugsy trocam de lugar por período e dia da semana | 0 flag: `FLAG_TEMP` no `ON_TRANSITION` |
| Livro de Berries | 67 flags contíguas; o Bram só dá o que está no livro | 67 flags (`0x1053..0x1095`) |
| Cruzamento completo | 58 receitas; campo de mutação de 4 → 6 bits | C em `berry.c` + 2 bits de `padding` |
| Níveis da horta | 5 níveis: canteiro B, irrigação, hotel de insetos, horta do rei | 1 var |
| Infestação | 8 famílias só daqui; tabela por cor, horário, adubo e geração da berry | C em `berry.c`; tira 8 famílias de `wild_encounters.json` |
| Sidequest | 7 atos + epílogo; Glastrier **ou** Spectrier, depois Calyrex | 1 var de história |

---

## 1. Elenco

| Personagem | Quem é | Voz | Sprite | Plaquinha |
|---|---|---|---|---|
| **Bram, o Berry Master** | O careca da casa da Route 30. Planta há 50 anos. Acorda às 4h. | Caloroso, repete ditados de roça, chama o jogador de “sprout”. Esconde coisas mal. | `BALDING_MAN` (já no mapa) | `NAME_BERRY_MASTER` (nova) |
| **Laurel** | A esposa. Veio de **Freezington**, na Crown Tundra de Galar, há 40 anos. A avó cuidava do campo do rei. | Seca, exata, frases curtas. Nunca diz “por favor”. Carinho só em ação. | `WOMAN_3` (já no mapa) | `NAME_LAUREL` (nova) |
| **Tilly** | A neta, 9 anos. Vem nos fins de semana. Quer ser Bug Catcher. Dá nome a todo inseto. | Barulhenta, pergunta tudo, exagera. | `LITTLE_GIRL` (existe) | `NAME_TILLY` (nova) |
| **Bugsy** | Líder de Azalea. Vem estudar os insetos que só aparecem na horta. | Educado, entusiasmado, fala como pesquisador. | `BUGSY` (existe) | `NAME_BUGSY` (existe) |
| **Kurt** | Velho amigo do Bram e cliente fixo (as berries viram bolas). | Rabugento, carinhoso sem admitir. | só citado; aparece no epílogo por fala do Bram | `NAME_KURT` (existe) |
| **Pryce** | Líder de Mahogany. Guarda o Ice Path. No caminho do Glastrier. | Velho, severo, lento. | `PRYCE` (conferir) | `NAME_PRYCE` (existe) |
| **Morty** | Líder de Ecruteak. Sente espíritos. No caminho do Spectrier. | Místico, calmo. | `MORTY` (existe, no `BurnedTower_1F`) | `NAME_MORTY` (existe) |
| **Calyrex** | O Rei da Colheita Farta. Perdeu o poder e os corcéis. | Telepatia, formal, gentil. | `SPECIES(CALYREX)` (overworld existe) | `???` até se apresentar, depois `NAME_CALYREX` (nova) |
| **Glastrier / Spectrier** | Os corcéis. O Spectrier é o “visitante noturno” do Ato 2. | — | overworld dos dois existe | — |
| **Sunflora da Laurel** | Fica dentro de casa (orçamento de objetos). Reage às cenas com grito. | — | `SPECIES(SUNFLORA)` | — |

**Por que esse elenco.** O Bugsy dá sentido às infestações e é um líder que o
jogador já conhece no começo. Pryce e Morty são os dois lugares da escolha, cada um
com a sua cidade. A Tilly é o respiro cômico da rotina e a “loja” dos fins de semana.
O Kurt é quem liga a horta à economia das bolas.

---

## 2. A rotina (o mini Harvest Moon)

O jogo tem três períodos (`include/constants/rtc.h`): **manhã 4h–10h, dia 10h–18h,
noite 18h–4h**.

### 2.1 Quem está onde

| Período | Bram | Laurel | Tilly (sáb e dom) | Bugsy (ter e qui, depois do Ato 1) |
|---|---|---|---|---|
| **Manhã** | **Horta**, regando, em (31,45) | Casa, na mesa (3,4), café | Casa, (5,5), comendo | — |
| **Dia** | Casa, mesa (4,4), separando sementes | **Horta**, (27,43), olhando o canteiro | **Horta**, banquinha em (24,41) | **Horta**, (31,43), de lupa |
| **Noite** | Casa, **dormindo** (fala dormindo) | Casa, (3,4), **lendo o caderno** | — (foi embora) | — |

Coordenadas de fora são **sugestões**: medir com `dump_mapa.py Route30` antes
(skill `encenar-cutscene`). Regra: ninguém em pé numa célula que seja o **único**
acesso a um canteiro (lista em `BERRY_MASTER_DESIGN.md` §2.1).

### 2.2 Como se faz sem flag nenhuma

Um script `ON_TRANSITION` em `Route30` e outro em `Route30_House`:

```asm
Route30_OnTransition::
	specialvar VAR_RESULT, GetTimeOfDay        @ MORNING / DAY / NIGHT
	@ cada NPC de horário tem uma FLAG_TEMP própria como flag de ocultação;
	@ o script seta as de quem NÃO está aqui neste período
	...
```

- `FLAG_TEMP_*` zera a cada carregamento de mapa; o script decide de novo em toda
  entrada. Nada vai para o save. Padrão e armadilhas: skill `visibilidade-e-gatilhos`.
- Se a hora vira com o jogador parado no mapa, o NPC só troca de lugar na próxima
  entrada. É o que acontece em Harvest Moon também, e evita objeto sumindo na cara.
- Dia da semana: `specialvar VAR_RESULT, GetDayOfWeek` (já usado em Cherrygrove).

### 2.3 Orçamento de objetos

O limite é 16 objetos ativos, contando jogador e follower. Pior caso: **dia de
terça ou quinta, com a horta cheia**:

| Objeto | Qtd |
|---|---|
| Canteiros A + B | 10 |
| Canteiro da Laurel (hoje é a árvore Oran de rota em (23,38), §5) | 1 |
| Laurel | 1 |
| Bugsy | 1 |
| Jogador + follower | 2 |
| **Total** | **15** |

Para caber, o **Weedle decorativo de (19,42) sai do mapa** (ele não tem script). A
Tilly nunca coincide com o Bugsy (fim de semana × terça/quinta). À noite, o Calyrex
e o Spectrier ocupam a vaga da Laurel, que está em casa.

---

## 3. O Livro de Berries

### 3.1 A regra

- Cada berry tem **uma flag** no Livro. A flag liga quando o jogador **colhe** a berry
  de qualquer árvore (horta ou rota).
- As **8 iniciais** (Cheri, Chesto, Pecha, Rawst, Aspear, Leppa, Oran, Persim) já
  entram no Livro no tutorial: são as que o Bram planta desde sempre.
- **O Bram só dá berries do Livro.** Se você nunca colheu uma Sitrus, ele não te dá
  Sitrus. Comprar na loja **não** registra: o Livro é do que você cultivou.
- A Laurel, depois da Liga, dá uma rara **do Livro**, e nunca a Enigma.

> **Bram:** I don't hand out what I don't grow, sprout. And I only grow what's in
> the book.
> Get it in the book and I'll have seed for you by morning.

### 3.2 Onde mora

67 flags **contíguas** no fim do bloco `CUSTOM_FLAGS`, a partir de `0x1053` (hoje a
última é `FLAG_PYRAMID_ACHIEVEMENT_MIGRATION_COMPLETE`, `0x1052`):

```c
// Berry Ledger (.claude/berry_master/REI_DA_COLHEITA.md section 3): one flag per
// berry, in item order. FLAG_BERRY_LEDGER_START + (item - FIRST_BERRY_INDEX).
#define FLAG_BERRY_LEDGER_START   0x1053   // Cheri
#define FLAG_BERRY_LEDGER_END     0x1095   // Maranga (67 flags)
#define CUSTOM_FLAGS_END          FLAG_BERRY_LEDGER_END
```

Contíguas porque o C calcula a flag por soma, e porque o `flag_audit.py` e a skill
`catalogar-flags` precisam ver o bloco inteiro de uma vez.

### 3.3 Código (C, `src/berry.c`)

| Special | Faz | Quem chama |
|---|---|---|
| `BerryLedger_Register` | liga a flag da berry em `VAR_0x8004` | `BerryTree_EventScript_PickBerry` (e a versão com mutação), logo depois da colheita |
| `BerryLedger_Count` | quantas estão no Livro | Bram (marcos, reformas) |
| `BerryLedger_RandomRegistered` | sorteia uma berry do Livro (sem Lansat, Starf e Enigma) | presente diário, pedido comum |
| `BerryLedger_BuildSeedMenu` | monta a lista com rolagem das berries do Livro | semente encomendada (§3.5) |
| `BerryLedger_NextDiscovery` | sorteia uma berry **fora** do Livro cujos **dois pais estão no Livro**, e põe os pais em `VAR_0x8005/8006` | pedido de descoberta (§6), dica da Laurel |

A dica da Laurel é **um texto só** com os nomes dos pais nos buffers
(`bufferitemname`): nada de 58 textos.

### 3.4 Marcos do Livro

| No Livro | Prêmio (entregue pelo Bram na próxima conversa) |
|---|---|
| 12 | 5 Growth Mulch |
| 20 | 3 Rich Mulch *(sem fonte hoje)* |
| 30 | 3 Surprise Mulch *(sem fonte hoje)* |
| 40 | 3 Amaze Mulch *(sem fonte hoje)* |
| 50 | Berry Pouch *(item-chave sem fonte hoje; cosmético)* |
| 60 | 5 Boost Mulch *(sem fonte hoje)* |
| **66** (todas menos a Enigma) | Título: ele passa a te chamar de **“Berry Master”**, e a Laurel diz o seu nome pela primeira vez |

### 3.5 Repetível para sempre (estado final)

Toda berry tem que poder ser obtida **de novo, sem limite**, depois que a história
acaba. Conferido berry a berry. O que o motor faz hoje (`src/berry.c`):

- **Colher esvazia o canteiro** (`ObjectEventInteractionRemoveBerryTree`): tem que
  replantar. Árvore madura que ninguém colhe dá fruto de novo até 10 vezes (15 com
  Gooey Mulch) e depois morre (`BerryTreeGrow`, `:1911`).
- Rendimento com `OW_BERRY_YIELD_RATE = GEN_6_XY`: comuns dão de 4 a 15 por pé; as
  raras, **de 1 a 5**. Uma berry plantada **nunca devolve menos que 1**, e com rega
  devolve mais. Replantar sozinho já mantém qualquer berry para sempre, desde que o
  jogador não gaste a última.

A rede de segurança, para o jogador que gastou a última:

| Fonte diária | Cobre | Quando |
|---|---|---|
| Presente do Bram (2–3, sorteado do Livro) | as 64 do Livro menos Lansat, Starf e Enigma | desde o tutorial |
| **Semente encomendada** (nova, abaixo) | **qualquer uma do Livro**, à escolha, 1 por dia | nível 2 da horta |
| Rara diária da Laurel (sorteada do Livro, raras) | Lansat, Starf e as outras raras | pós-Liga |
| **Canteiro da Laurel** no nível 5 | a **Enigma**, que nenhuma fonte diária dava | depois do epílogo |

**Semente encomendada.** Uma vez por dia, em vez do presente sorteado, o jogador pode
pedir ao Bram **uma berry específica do Livro**. Lista com rolagem, montada em C com
as berries registradas (`dynmultichoice` já existe no repo e é usado em
`BlackthornCity`, `BattleCafe`). Sem isso, pegar uma berry certa entre 64 pelo
sorteio levaria semanas.

> **Berry Master:** Got one in mind? Name it. If it's in the Book, I've got seed for it.

**A Enigma.** No estado 13, o canteiro da Laurel vira fonte fixa: se estiver vazio
de manhã, ele **se replanta sozinho com uma Enigma** (o C trata esse ID como árvore
natural de Enigma, com a regeneração que já existe para as árvores de rota,
`StartNaturalBerryTreeRegeneration`). O jogador pode plantar outra coisa lá; quando
colher e deixar vazio, a Enigma volta. A Laurel explica uma vez:

> **Laurel:** Leave it empty and it grows his Berry back on its own. It remembers
> now. Don't ask me how. I stopped asking questions too.

**Lansat e Starf** só **cruzam** depois da Liga (§4.1), mas replantar é livre: quem
já tem uma mantém para sempre.

---

## 4. Cruzamento: as 67 berries a partir de 8

### 4.1 O motor

- Liga `OW_BERRY_MUTATIONS`.
- **4 → 6 bits.** Hoje o resultado do cruzamento fica em `mutationA:2` + `mutationB:2`
  (`include/global.berry.h:80`), o que dá 15 receitas. O struct tem `padding:2`
  livre: vira `mutationC:2`, e cabem **63**. As 58 abaixo cabem com folga. Mexer
  em `GetTreeMutationValue` e `SetTreeMutations` (o `union TreeMutation` ganha o
  campo `c`).
- `sBerryMutations` passa de 13 para 58 linhas. Uma linha por par; o mesmo par
  nunca dá duas berries (conferido por script).
- **Lansat e Starf só cruzam depois da Liga:** `TryForMutation` ignora essas duas
  linhas enquanto `FLAG_SYS_GAME_CLEAR` estiver desligada. Protege as receitas de
  nível 20 do Kurt, como pede `KURT_BALL_CRAFT_DESIGN.md`.
- A **Enigma** não tem receita: é a semente da história (§8).

### 4.2 Todas as receitas

As 13 marcadas “jogo” são as do motor, intocadas. As outras 45 seguem o tema da
berry (quem cura sono + quem cura paralisia dá a Lum; as de resistência saem de
sabor + EV do tipo). Geração = quantos cruzamentos separam a berry das 8 iniciais.

| Geração | Berry | Plante lado a lado | Origem |
|---|---|---|---|
| 1 | **Lum** | Cheri + Chesto | nova |
| 1 | **Sitrus** | Oran + Leppa | nova |
| 1 | **Figy** | Cheri + Rawst | nova |
| 1 | **Wiki** | Chesto + Aspear | nova |
| 1 | **Mago** | Pecha + Persim | nova |
| 1 | **Aguav** | Rawst + Leppa | nova |
| 1 | **Iapapa** | Aspear + Oran | nova |
| 1 | **Razz** | Cheri + Pecha | nova |
| 1 | **Bluk** | Chesto + Oran | nova |
| 1 | **Nanab** | Pecha + Aspear | nova |
| 1 | **Wepear** | Rawst + Persim | nova |
| 1 | **Pinap** | Aspear + Cheri | nova |
| 1 | **Kelpsy** | Chesto + Persim | jogo (canon) |
| 1 | **Qualot** | Oran + Pecha | jogo (canon) |
| 1 | **Hondew** | Aspear + Leppa | jogo (canon) |
| 2 | **Pomeg** | Iapapa + Mago | jogo (canon) |
| 2 | **Grepa** | Aguav + Figy | jogo (canon) |
| 2 | **Tamato** | Lum + Sitrus | jogo (canon) |
| 2 | **Cornn** | Bluk + Wiki | nova |
| 2 | **Magost** | Nanab + Mago | nova |
| 2 | **Rabuta** | Aguav + Wepear | nova |
| 2 | **Nomel** | Pinap + Iapapa | nova |
| 2 | **Spelon** | Razz + Figy | nova |
| 2 | **Pamtre** | Bluk + Kelpsy | nova |
| 2 | **Chilan** | Nanab + Razz | nova |
| 2 | **Passho** | Kelpsy + Oran | nova |
| 2 | **Rindo** | Wepear + Hondew | nova |
| 2 | **Tanga** | Lum + Wepear | nova |
| 3 | **Watmel** | Magost + Pomeg | nova |
| 3 | **Durin** | Rabuta + Hondew | nova |
| 3 | **Belue** | Cornn + Pamtre | nova |
| 3 | **Occa** | Spelon + Tamato | nova |
| 3 | **Wacan** | Pinap + Nomel | nova |
| 3 | **Yache** | Wiki + Cornn | nova |
| 3 | **Chople** | Pomeg + Razz | nova |
| 3 | **Kebia** | Rabuta + Pomeg | nova |
| 3 | **Shuca** | Grepa + Nomel | nova |
| 3 | **Payapa** | Magost + Spelon | nova |
| 3 | **Charti** | Nomel + Qualot | nova |
| 3 | **Roseli** | Nanab + Magost | nova |
| 3 | **Ganlon** | Qualot + Tanga | jogo (canon) |
| 4 | **Coba** | Belue + Pamtre | nova |
| 4 | **Kasib** | Magost + Belue | nova |
| 4 | **Haban** | Durin + Tamato | nova |
| 4 | **Colbur** | Kebia + Magost | nova |
| 4 | **Babiri** | Durin + Qualot | nova |
| 4 | **Liechi** | Hondew + Yache | jogo (canon) |
| 4 | **Salac** | Grepa + Roseli | jogo (canon) |
| 4 | **Apicot** | Kelpsy + Wacan | jogo (canon) |
| 5 | **Petaya** | Pomeg + Kasib | jogo (canon) |
| 5 | **Custap** | Ganlon + Apicot | nova |
| 5 | **Jaboca** | Chople + Babiri | nova |
| 5 | **Rowap** | Payapa + Colbur | nova |
| 5 | **Kee** | Ganlon + Liechi | jogo (canon) |
| 6 | **Micle** | Liechi + Petaya | nova |
| 6 | **Maranga** | Salac + Petaya | jogo (canon) |
| 7 | **Lansat** | Micle + Custap | nova, **só pós-Liga** |
| 7 | **Starf** | Kee + Maranga | nova, **só pós-Liga** |

| Geração | Berries | Ritmo esperado |
|---|---|---|
| 0 | 8 iniciais | tutorial |
| 1 | 15 | primeira semana |
| 2 | 13 | segunda e terceira semanas |
| 3 | 13 | primeiro mês |
| 4 | 8 | segundo mês |
| 5–6 | 7 | fim da campanha |
| 7 | Lansat, Starf | pós-Liga |

> Cada cruzamento é 25% por plantio (50% com Surprise ou Amaze Mulch) e exige os
> dois pais **vizinhos** no canteiro. Quanto mais canteiros, mais pares por vez:
> é isso que faz o canteiro B e as reformas valerem a pena.

---

## 5. Níveis da horta (reformas)

O Bram faz a reforma quando o Livro chega no número e o jogador paga. A reforma
acontece **de um dia para o outro**: você paga, e na manhã seguinte ela está pronta,
com uma cena curta.

| Nível | Nome (in-game) | Pede | Destrava |
|---|---|---|---|
| 1 | Backyard Plot | tutorial | Canteiro A (6), presente de 2 berries por dia, pedidos comuns |
| 2 | Proper Garden | Livro 12 + ₽5.000 | **Canteiro B** (+4), presente de **3** berries, pedidos de descoberta |
| 3 | Water Channel | Livro 22 + ₽10.000 + Ato 1 feito | **Irrigação:** a horta amanhece regada todo dia |
| 4 | Bug Hotel | Livro 32 + Ato 1 feito (o Bugsy constrói) | Chance de praga **15% → 30%** e o slot raro ×1,5 (§7) |
| 5 | King's Garden | fim da sidequest | O canteiro da Laurel dá **colheita dobrada**; a rara diária da Laurel |

**Irrigação (nível 3).** Um special `WaterGardenTrees` no `ON_TRANSITION` de `Route30`
marca como regado o estágio atual de todo canteiro da horta, uma vez por dia
(`FLAG_DAILY_GARDEN_WATERED`). Regar à mão continua valendo para árvore de rota.

**Canteiro da Laurel.** Hoje em (23,38) há uma árvore de rota natural
(`BERRY_TREE_ORAN_2`, Oran). Ela vira o **canteiro da Laurel**: a Oran natural sai de
`sNaturalBerriesByTreeId` e de `EventScript_ResetAllBerries`, e o objeto troca para o
ID `BERRY_TREE_KINGS_PLOT` (apelido de mais um ID de Hoenn). Até o Ato 3 o objeto
fica escondido (`FLAG_TEMP` no `ON_TRANSITION`), e um `bg_event` no mesmo tile
responde:

> The soil here is hard and cold. Nothing's grown in it for a long time.

**As cenas de reforma** (manhã seguinte ao pagamento, ao entrar na Route 30):

> *Nível 2*
> **Bram:** Four more beds! Laurel dug them. Don't tell her I said so. She'll say I
> helped.
>
> *Nível 3*
> **Bram:** See that channel? Runs right from the pond. The whole garden drinks
> before you're even out of bed now.
> **Laurel:** He dug it at three in the morning. The neighbors thought it was a
> Diglett.
>
> *Nível 4*
> **Bugsy:** It's done! A proper Bug Hotel. Hollow stems for the Combee, bark for the
> Wurmple, a stone pile for Dwebble...
> They'll come for the berries and they'll stay for the architecture!
> **Bram:** He means more bugs. He's happy about more bugs.

---

## 6. Os pedidos

Substitui `BERRY_MASTER_DESIGN.md` §3. Dois tipos, **um por dia**, sorteado na
primeira conversa (`FLAG_DAILY_BERRY_ORDER_ROLLED`):

| Tipo | Quando | O que pede | Paga |
|---|---|---|---|
| **Comum** | sempre | N de uma berry **do Livro** (`BerryLedger_RandomRegistered`) | ₽ por berry + 1 adubo |
| **Descoberta** | nível 2+, 1 dia em 3 | **1** berry que ainda não está no Livro, mas cujos pais estão (`BerryLedger_NextDiscovery`) | ₽ em dobro + Surprise Mulch |

No pedido de descoberta, o Bram **não sabe** a receita. Ele manda o jogador perguntar
à Laurel, e é assim que a esposa entra no ciclo todo dia:

> **Bram:** Now here's one I've never grown. Kurt swears there's a Berry called
> {STR_VAR_1}. I think he's pulling my leg.
> Ask Laurel. If anyone knows, she knows. She just won't tell ME.
>
> **Laurel:** {STR_VAR_1}. {STR_VAR_2} beside {STR_VAR_3}. Touching, side by side.
> Not corner to corner. People always do corner to corner.

Clientes, só para o texto (muda a primeira frase): Kurt, a floricultura de
Goldenrod, a Nurse de Cherrygrove, a Moomoo Farm, o Day Care. **Nunca** paga Poké
Ball (o Kurt é a única fábrica). Entrega na ordem `checkitem` → `yesno` →
`checkitemspace` → `removeitem` → `giveitem`, como no design rev1 §3.4.

---

## 7. Infestações

### 7.1 Só daqui

Estas 8 famílias **saem da natureza** e passam a existir **só** como praga da horta:

| Família | Tirar de (`src/data/wild_encounters.json`) |
|---|---|
| Rellor → Rabsca | Route 37 (grama) |
| Blipbug → Dottler → Orbeetle | Route 30 (grama) |
| Scatterbug → Spewpa → Vivillon | National Park (grama) |
| Combee → Vespiquen | Route 31 (grama) |
| Volbeat | Kitakami Border (grama) |
| Illumise | Kitakami Border (grama) |
| Wurmple → Silcoon/Cascoon → Beautifly/Dustox | Route 37 (grama) |
| Dwebble → Crustle | Cliff Edge Cave (Rock Smash) |

Nenhuma é do Bug Catching Contest nem aparece no Gachapon. Os slots que ficam
vazios nessas rotas recebem o que já existe nelas (redistribuir a porcentagem;
não inventar espécie nova na rota).

### 7.2 A tabela de pragas

A **cor** da berry escolhe o grupo, o **horário** troca o comum, e a **geração** da
berry (§4) pesa o raro. Nível: `10 + 4 × insígnias`, teto 60.

| Cor | Comum (manhã/dia) | Comum (noite) | Incomum | Raro |
|---|---|---|---|---|
| Vermelha | Ledyba | Spinarak | **Wurmple** | Heracross |
| Azul | **Blipbug** | **Volbeat** | Surskit | Joltik |
| Rosa | Cutiefly | **Illumise** | **Scatterbug** | Shuckle |
| Verde | Burmy | Kricketot | **Scatterbug** | Sewaddle |
| Amarela | **Combee** | Venonat | Kricketot | Heracross |

| Berry plantada | Comum | Incomum | Raro |
|---|---|---|---|
| Geração 0–1 | 70% | 27% | 3% |
| Geração 2–3 | 50% | 38% | 12% |
| Geração 4+ | 30% | 40% | 30% |

**O adubo muda a praga** (antes da tabela acima, metade das vezes):

| Adubo no canteiro | Praga |
|---|---|
| Gooey ou Rich Mulch (composto) | **Rellor**, que rola bolinhas de adubo |
| Stable Mulch (pedrinha) | **Dwebble**, que faz casa na pedra |

Assim cada exclusivo tem um jeito claro de aparecer: Wurmple nas vermelhas, Blipbug
nas azuis de dia, Volbeat nas azuis de noite, Illumise nas rosas de noite, Scatterbug
nas rosas e verdes, Combee nas amarelas de dia, Rellor e Dwebble pelo adubo.

A dica mora no Bugsy (Ato 1) e nas falas da Tilly (§9), então o jogador descobre as
regras conversando.

### 7.3 Código

- `GetBerryPestSpecies` (`src/berry.c:2568`) vira uma tabela `[cor][slot]` com o
  horário (`GetTimeOfDay`), a geração da berry e o adubo (`GetMulchByBerryTreeId`).
- Pragas e ervas **só nos canteiros da horta** (`IsBerryGardenTree`, design rev1 §6.1).
- `BERRY_PESTS_CHANCE` 15%, e 30% com a horta no nível 4.
- O `CreateScriptedWildMon` já existe (`src/berry.c:2397`); só troca a espécie e o
  nível.

---

## 8. A sidequest: O Rei da Colheita

### 8.1 O arco em uma tabela

Estado numa var só, `VAR_HARVEST_KING` (0..13). Nenhum ato trava a rotina: a horta
funciona igual em qualquer estado.

| Estado | Ato | Gatilho para entrar | Onde |
|---|---|---|---|
| 0 → 1 | **Prólogo** — O canteiro frio | tutorial do Bram (primeira visita) | `Route30_House` |
| 1 → 2 | **Ato 1a** — Visitantes | primeira praga vencida ou capturada na horta | `Route30` (horta) |
| 2 → 3 | **Ato 1b** — O pesquisador | 2ª insígnia + entrar na Route 30 de dia | `Route30` (horta) |
| 3 → 4 | **Ato 1c** — O censo | registrar 3 exclusivos da horta na Pokédex (`getcaughtmon`) e falar com o Bugsy | `Route30` / Ginásio de Azalea |
| 4 → 5 | **Ato 2** — Pegadas | horta nível 3 + entrar na Route 30 **de noite** | `Route30` (lago) |
| 5 → 6 | **Ato 2b** — O que o Bram sabe | falar com o Bram à noite (ele acorda) | `Route30_House` |
| 6 → 7 | **Ato 3** — O caderno | Livro 40 + 7ª insígnia + falar com a Laurel à noite | `Route30_House` |
| 7 → 8 | **Ato 4** — A primeira folha | a Enigma plantada no canteiro da Laurel brota | `Route30` |
| 8 → 9 | **Ato 5** — O Rei | a Enigma madura + noite | `Route30` (canteiro da Laurel) |
| 9 → 10/11 | **Ato 6** — A escolha | Glastrier (Ice Path Depths) **ou** Spectrier (Burned Tower B1F, noite) capturado | `IcePath_Depths` / `BurnedTower_B1F` |
| 10/11 → 12 | **Ato 7** — Colheita Farta | voltar à horta de noite com o corcel na party | `Route30` |
| 12 → 13 | **Epílogo** | manhã seguinte | `Route30` / `Route30_House` |

Estado 10 = escolheu o Glastrier; 11 = escolheu o Spectrier. O corcel que ficou
para trás continua **só no Nexus**. Pela R1 (`NEXUS_REGRAS.md`), Calyrex e o corcel
escolhido só entram no sorteio do Nexus depois de capturados; atualizar
`POOL_LENDARIOS.md`.

**Retry.** Nenhuma batalha avança o estado se o jogador fugir ou perder: o lendário
volta na próxima noite (objeto escondido por `FLAG_TEMP`, sempre setada no load,
como manda a skill `evoluir-historia-de-evento` §3). Só `captured` avança. Se o
jogador **derrotar** sem capturar, o lendário volta na noite seguinte com uma fala
curta (“It stands again, as if it never fell.”) — ninguém perde lendário da história.

**Surpresa.** O nome Calyrex, a palavra “king” e os corcéis **não aparecem** em
nenhum texto antes do Ato 3. Conferir com `grep` antes de fechar.

---

### 8.2 Prólogo — O canteiro frio (estado 0 → 1)

*Primeira conversa com o Bram, logo depois do tutorial que já existe (a Cheri).
A Laurel está na mesa. Ninguém se mexe; ninguém ao sul do jogador.*

> **Berry Master:** Now that's the talk. Here's the part the talk leaves out.
> Out the door, to the right. Six beds. They're yours.
> Plant what you like. Water it, pull the weeds, chase off whatever comes to eat it.
> Everything you pick, I write down in the Book. And what's in the Book, I can grow
> seed for.
> Come by in the mornings. I'll have something for you.
>
> **Laurel:** Not the patch by the door.
>
> **Berry Master:** ...Not the patch by the door.
>
> **Laurel:** That one's mine.

*Estado 1. As 8 iniciais entram no Livro. Se o jogador tentar o canteiro da Laurel,
sai o texto do `bg_event` (“The soil here is hard and cold…”).*

---

### 8.3 Ato 1a — Visitantes (1 → 2)

*A primeira praga da horta termina (vencida ou capturada). O script de praga de
`berry_tree.inc` chama, depois da batalha, uma sub-rotina que só age em estado 1
e dia.*

*Se de dia a Laurel está na horta: ela vira para o jogador.*

> **Laurel:** A {STR_VAR_1}. In the beds.
> Fifty years we've had this garden. Fifty years and not one bug.
> Now you come along, and they come along.
> ...It isn't a complaint. Go and tell him. He'll want to shout.

*Na próxima conversa com o Bram (qualquer período, acordado):*

> **Berry Master:** BUGS? In MY beds?
> ...What kind? Ooh. I've never even seen one of those.
> Laurel says write to the boy in Azalea. The Gym Leader. Knows every bug from here
> to Kanto.
> I'll post the letter. You go get yourself a badge from him, so he knows you're
> serious.

*Estado 2. Se o jogador já tem a 2ª insígnia, pula direto para o 1b na próxima
entrada de dia.*

---

### 8.4 Ato 1b — O pesquisador (2 → 3)

*2ª insígnia (`FLAG_BADGE02_GET`) + entrar na Route 30 de dia. O Bugsy está
agachado na frente do canteiro A, de lupa (objeto com `FLAG_TEMP`, só nesta cena e
depois nas visitas de terça e quinta). Olhar dele: para o canteiro, **sem**
`faceplayer` até o jogador falar.*

> **Bugsy:** Shh! Don't move. There's a Blipbug on the third bed.
> ...It's gone. Hello! You must be {PLAYER}. I got a letter. Well, the letter was
> mostly about how big the berries were.
> But this garden is remarkable. I've catalogued every bug in Johto, and some of the
> ones coming here don't live ANYWHERE in Johto.
> Wurmple. Combee. Fireflies at night. A Dwebble living in a pebble!
> They aren't lost. They came for the berries. Different berries, different bugs.
> Will you help me? Catch three of the ones that only come here, and bring me the
> data.
> I'll be in Azalea. And here, now and then. I can't stay away from a place like
> this.

*Estado 3. O Bugsy passa a visitar terça e quinta de dia (§2.1).*

---

### 8.5 Ato 1c — O censo (3 → 4)

*Três espécies da lista do §7.1 capturadas (`getcaughtmon`, uma a uma, contando
famílias pela espécie base ou qualquer evolução). Falar com o Bugsy na horta (terça
ou quinta) ou no Ginásio de Azalea.*

> **Bugsy:** Three of them! Let me see...
> It's the colors. Red berries, red bugs. Blue berries bring Blipbug in the day and
> Volbeat after dark. And whatever you put in the soil matters too.
> Compost brings Rellor. Gravel brings Dwebble. It's a whole little world out there!
> I'm going to build something for them. A Bug Hotel. When your garden's ready for
> it, tell Bram to call me.
> Oh, and take this. For the bugs you'll raise.

*Dá **Silver Powder** (checkitemspace antes). Estado 4. O nível 4 da horta passa
a ficar disponível quando o Livro chegar a 32.*

---

### 8.6 Ato 2 — Pegadas (4 → 5)

*Horta no nível 3 + entrar na Route 30 **de noite**. Gatilho `ON_FRAME` com estado 4
e `GetTimeOfDay == NIGHT`, uma vez (seta o estado antes de soltar o jogador, para
não travar — skill `visibilidade-e-gatilhos`).*

*A trilha sai (`fadeoutbgm`). O Spectrier já está no canteiro B, comendo, de
costas para o jogador. A cena começa com o jogador andando sozinho dois tiles em
direção à horta (`applymovement OBJ_EVENT_ID_PLAYER`), para o cavalo entrar no
quadro.*

1. O jogador para. `Common_Movement_ExclamationMark` no jogador.
2. O Spectrier vira para o jogador (`face_up`/o lado que medir). Grito
   (`playmoncry SPECIES_SPECTRIER, CRY_MODE_ENCOUNTER`).
3. Flash (`fadescreenswapbuffers`, **nunca** `fadescreen`: é noite e a tela
   escureceria mais a cada flash).
4. `walk_faster` para a direita até sair pelo lago, `removeobject`.

> *(narração, sem plaquinha)* Something dark and tall was eating from the beds.
> It looked at you for a long moment. Then it was gone, and it made no sound at all.
> *(no canteiro)* Hoofprints, pressed deep into the soil. They stop at the edge of
> the pond.

*Estado 5. `fadedefaultbgm`. Na manhã seguinte, se o jogador fala com a Laurel (ela
está em casa de manhã):*

> **Laurel:** You were out late.
> ...Don't tell me. I heard it. I've heard it before.
> Eat your breakfast. It isn't here for you.

---

### 8.7 Ato 2b — O que o Bram sabe (5 → 6)

*Estado 5 + falar com o Bram **de noite**. Ele está dormindo; em vez da fala
dormindo, ele acorda (`Common_Movement_ExclamationMark`) e fala baixo.*

> **Berry Master:** Hm? Oh. It's you. Keep it down. She's reading.
> ...She told you it isn't here for you. She's right. It's here for her. Or for what
> she brought.
> Laurel isn't from Johto, sprout. She's from Freezington. Up past the snow, in Galar.
> Her grandmother kept a field there. An old field. For someone important.
> When Laurel came here she brought one seed from it. She's planted it in that patch
> by the door every spring for forty years.
> It has never, once, come up.
> Don't ask her about it. She'll tell you when the Book's big enough. That's what she
> said to me, anyway. I've been waiting forty years.

*Estado 6.*

---

### 8.8 Ato 3 — O caderno (6 → 7)

*Livro ≥ 40 + 7ª insígnia (o Ice Path e a Burned Tower já estão abertos) + falar com
a Laurel **de noite**, lendo o caderno. A Sunflora grita antes de ela falar.*

> **Laurel:** Forty. Forty Berries, and you grew every one of them.
> Sit. No, sit.
> Where I come from there's a story. There was a king who made the fields grow.
> Whatever he walked past, it fruited.
> He rode two horses. A white one that walked through the snow, and a black one that
> walked through the dark.
> People forgot him. When people forget, a king like that gets small. He loses his
> horses. He loses the harvest.
> My grandmother didn't forget. She kept his field.
> When I left, she gave me this. She said: plant it where the land remembers.
> Johto never remembered. Not for forty years.
> Then you came, and the bugs came. And three nights ago, the black horse came.
> The land remembers something now. I think it's you.
> Take it. Plant it in my patch. Not yours. Mine.

*Dá a **Enigma Berry** (`checkitemspace` antes; se a bolsa estiver cheia, ela
guarda: “Come back when you have room. It's waited forty years.”). O canteiro da
Laurel aparece (limpa a `FLAG_TEMP` de ocultação neste e em todo load com estado ≥ 7).
Estado 7.*

*Se o jogador plantar a Enigma em outro canteiro, ela cresce normal e entra no Livro,
mas a história não anda. A Laurel comenta (dia, na horta):*

> **Laurel:** That's a bed. I said my patch. It isn't the same soil. Trust me.

*E devolve outra Enigma na próxima conversa, uma vez por dia, enquanto o estado for 7.*

---

### 8.9 Ato 4 — A primeira folha (7 → 8)

*Special `GetKingsPlotStage` ≥ `BERRY_STAGE_SPROUTED` com a Enigma no canteiro da
Laurel. Entrar na Route 30 de dia. A Laurel está **no canteiro dela**, não no lugar
de sempre, de joelhos (virada para o canteiro).*

> **Laurel:** ...
> It came up.
> *(o Bram sai de casa: `addobject` na porta, anda até o lado dela)*
> **Berry Master:** Laurel? Laurel, what's the—
> ...Oh.
> Oh, would you look at that.
> **Laurel:** Don't. Don't say anything.
> **Berry Master:** I wasn't going to say anything.
> **Laurel:** You were going to cry.
> **Berry Master:** I was not.
> *(pausa; o Bram vira para o jogador)*
> **Berry Master:** Go on, sprout. Give us a minute.

*Estado 8.*

---

### 8.10 Ato 5 — O Rei (8 → 9)

*Enigma madura no canteiro da Laurel + noite. Entrar na Route 30. `fadeoutbgm`.
O Calyrex já está ao lado do canteiro, pequeno, sem corcel. Luz fraca: um
`LIGHT_SPRITE` (custa zero no orçamento) no canteiro, se couber.*

> **???:** ...You can hear me. Good.
> Do not be afraid. I have not had a voice in this land for a very long time.
> This Berry... it was grown with care. By someone who remembered.
> *(o Calyrex anda até o canteiro; `walk_in_place` duas vezes: ele come)*
> Ah. I had forgotten what that was like.
> I am Calyrex. Once, they called me the King of Bountiful Harvest.
> I was a king with no field, and no one to carry me. My steeds left when the people
> forgot.
> One still wanders this land at night, looking for food. You have met him, I think.
> The other sleeps under ice that never melts.
> I cannot call them. I am too weak. But you could.
> Bring one of them home to me, and I will show you what this garden can become.

*A porta abre: a Laurel sai, de camisola (`addobject` + anda até o jogador).*

> **Laurel:** ...It's true, then. All of it.
> *(ela olha para o Calyrex; `Common_Movement_ExclamationMark` nela)*
> My grandmother used to sing me to sleep with it. The song goes:
> “The white one sleeps where the ice never thaws.
> The black one walks where the fire took the bells.”
> Ice that never thaws. That's the Ice Path. Past Mahogany.
> Where the fire took the bells. That's the old tower in Ecruteak.
> One horse. The king said one. Choose.

*O Calyrex some num flash (`removeobject`; volta toda noite no canteiro, com uma
fala curta, até o Ato 7). Estado 9. `fadedefaultbgm`.*

> **Calyrex (noites seguintes):** I will wait here. I have grown very good at waiting.

---

### 8.11 Ato 6 — A escolha (9 → 10 ou 11)

**Caminho do Glastrier — `IcePath_Depths`.** Estado 9 + entrar no mapa. O Pryce
está na frente da câmara mais funda (objeto com `FLAG_TEMP`, só em estado 9).

> **Pryce:** You hear it too. Under the ice. All winter, like hooves on a frozen lake.
> I came to see it in my youth. It didn't care for me.
> Laurel from Route 30... I knew a girl from Freezington once. Long ago. She sang a
> song about a white horse.
> ...So she sent you. Then go. And don't be proud. The cold doesn't care how many
> badges you have.

*O Glastrier está parado no fundo (objeto; script = batalha de encontro fixo,
`seteventmon SPECIES_GLASTRIER` + `dowildbattle` no padrão do Celebi do Ilex).
Capturado → estado 10, o Pryce some no próximo load. Fugiu/perdeu/derrotou → volta.*

> **Pryce (depois):** White as the old stories. Tell Laurel the song was right.

**Caminho do Spectrier — `BurnedTower_B1F`, só de noite.** Estado 9 + noite. O Morty
está no B1F, perto de onde ficavam as três feras.

> **Morty:** You feel it, don't you? A cold that isn't the cold.
> Something has been walking these ruins at night. It isn't one of the three beasts.
> It came from far away. It's hungry, and it's lonely.
> It keeps going to Route 30 and coming back here to sleep. Almost as if it can't
> decide which place is home.
> Go gently. It only looks frightening.

*O Spectrier é o mesmo do Ato 2. Mesmo padrão de batalha. Capturado → estado 11.*

> **Morty (depois):** It went quiet. That's the first time it's been quiet.

**O que ficou para trás.** Com estado 10 ou 11, o outro mapa não tem mais corcel.
O Pryce ou o Morty (quem ficou) diz uma linha só, se o jogador for lá:

> **Pryce:** The ice is quiet now. Whatever lived here went elsewhere. Perhaps it
> heard the other one was chosen.
>
> **Morty:** It stopped coming. I think it knew you'd chosen the other road.

---

### 8.12 Ato 7 — Colheita Farta (10/11 → 12)

*Estado 10/11 + noite + o corcel escolhido na party (`checkspecies`; sem ele, o
Calyrex diz “Where is my steed? Bring him to me.”). O Calyrex no canteiro. A Laurel
na porta.*

> **Calyrex:** You found him.
> *(o corcel sai da bola: `addobject` do objeto de espécie ao lado do jogador;
> anda até o Calyrex; os dois `walk_in_place` juntos)*
> *(Glastrier)* Still stubborn. Still cold. Still mine.
> *(Spectrier)* So it was you, eating the Berries at night. I should have known.
> Now. A king returns to his power the old way. Show me yours.

*Batalha: `seteventmon SPECIES_CALYREX` + encontro fixo. Nível: §12, decisão 5.
**Captura** → estado 12.*

*Depois da batalha, fade curto (`fadescreenswapbuffers`), e a horta inteira está em
estágio de fruto (special `RipenGardenTrees`, uma vez). É a “colheita farta”.*

> **Laurel:** ...
> My grandmother said he'd come back when someone grew a garden for him instead of
> for themselves.
> This belonged to her. It's for riding. You'll know what to do with it.

*Dá as **Reins of Unity** (`checkitemspace` antes). A Enigma entra no Livro.*

---

### 8.13 Epílogo (12 → 13)

*Manhã seguinte. O Bram na horta, como sempre. Horta vira nível 5.*

> **Berry Master:** You know what Laurel did this morning? She sang. At breakfast.
> Forty years. I didn't know she could sing.
> The patch by the door's yours too now. She said so. Plant whatever you want in it.
> It gives double. Don't ask me how. I stopped asking questions last night.
> Oh — Kurt came by at dawn. First time he's left Azalea since I don't know when.
> Said he “felt it in his knees.” Took a sack of Berries and left. Didn't pay.

*Estado 13. A Laurel passa a dar a rara diária do Livro (pós-Liga, como hoje).*

> **Laurel (primeira conversa depois):** Good morning, {PLAYER}.
> ...What? I know your name. I've always known your name.

---

## 9. O banco de falas da rotina

Uma fala **por dia da semana** (`GetDayOfWeek`), por personagem e período. Não
repete dentro da semana, e a mesma conversa dá a mesma fala o dia todo (como um
aldeão de Harvest Moon). Antes da fala fixa, entram as reações de contexto (§9.6).

### 9.1 Bram — de manhã, na horta (depois do presente e do pedido)

| Dia | Fala |
|---|---|
| Dom | Sunday! Tilly's selling out front. Buy something, or she'll follow you to Violet. |
| Seg | Water before the sun's up and the leaves won't burn. My father told me that. Then he watered at noon every day of his life. |
| Ter | Bugsy's coming today. He brought a notebook last time. The time before, two. |
| Qua | You know how you tell a ripe Berry? You don't. The Berry tells you. |
| Qui | I talk to the trees. Laurel says it doesn't help. The trees haven't complained. |
| Sex | Kurt wants Berries again. I asked what for. He said “Balls.” Then he hung up on me. |
| Sáb | Half the garden's asleep till ten. Like Tilly. |

### 9.2 Bram — de dia, em casa, separando sementes

| Dia | Fala |
|---|---|
| Dom | Seed day. Sit down. No — not on those. Those are Persim. |
| Seg | Every seed in this jar is a tree someday. Every one. That's what gets me up in the morning. That and Laurel. |
| Ter | Laurel's out in the beds. Don't tell her anything's wilting. She already knows, and she'll be cross that you noticed. |
| Qua | I've got a seed here I can't name. Could be a Wiki. Could be a pebble. We'll find out. |
| Qui | Forty years married. The trick is, she's always right, and I'm always hungry. |
| Sex | When I was your age I wanted to be a Pokémon Trainer. Then I grew a tomato. That was that. |
| Sáb | Tilly asked why the sky is blue. I said, “Because the Oran Berries are.” She believed me for a whole year. |

### 9.3 Bram — de noite, dormindo

Sorteio (`random 6`), porque sonho não tem calendário:

- *Zzz... No, no, the Sitrus goes by the fence...*
- *Zzz... Laurel... there's a Combee in my hat...*
- *Zzz... Forty-one... forty-two... forty-three Pecha...*
- *Zzz... Kurt, you owe me for the Leppa...*
- *Zzz... Hm? The Book? ...Six more... zzz...*
- *Zzz... it came up... it finally came up... zzz...* *(só com estado ≥ 8)*

### 9.4 Laurel — de dia, na horta

| Dia | Fala |
|---|---|
| Dom | Tilly counts the money. I count the Berries. Neither of us trusts the other one. |
| Seg | Too much water. Not you. Him. |
| Ter | The Azalea boy's coming. He lies down in the dirt. Every time. |
| Qua | Weeds are just plants in the wrong place. I'm not sentimental about it. |
| Qui | Freezington had one road and one shop. I liked it. Don't tell him. |
| Sex | You're standing on a sprout. ...No. The other foot. |
| Sáb | She'll ask you to buy mulch. Say no once. It's good for her. |

### 9.5 Laurel — de noite, lendo o caderno

De noite, a fala dela é **a dica do dia**: `BerryLedger_NextDiscovery` escolhe uma
berry que o jogador pode descobrir agora.

> **Laurel:** Page {STR_VAR_4}. {STR_VAR_1}. You get it from {STR_VAR_2} beside
> {STR_VAR_3}.
> I'm not telling you twice. ...I'll tell you tomorrow, if you forget.

Se o Livro está completo: *“Nothing left in here you haven't grown. I don't know
whether to be proud or bored.”*

### 9.6 Tilly — fins de semana, de dia, na banquinha

Ela é a **loja** (um `pokemart` de adubo: Growth, Damp, Stable, Gooey e, a partir do
nível 4 da horta, Rich e Surprise). Antes da loja, uma fala:

| Situação | Fala |
|---|---|
| Sábado | Welcome to Tilly's Mulch Emporium! It's mulch. It's the best mulch. Grandpa made it but I named it. |
| Domingo | Do you know what Rellor do with mulch? They ROLL it. I'm going to have ten Rellor. Grandma said one. |
| Bug na party | Is that a {STR_VAR_1}?! Can I hold it? I'm holding it. |
| Depois do Ato 2 | Grandma said there's no horse. There's hoofprints. So there's a horse. |
| Depois do Ato 7 | Grandma's singing! It's weird! I like it! |
| Livro completo | You grew ALL of them? Even the Kee? The Kee is so ugly. I love it. |

### 9.7 Bugsy — terça e quinta, de dia, na horta

| Situação | Fala |
|---|---|
| Padrão (terça) | Every color of Berry calls a different bug. I've got a chart. It's twelve pages. |
| Padrão (quinta) | Try Stable Mulch on one bed. Watch what moves in. You'll love him. |
| Bug Hotel pronto | The hotel's full! Well, one Combee. It's a start. |
| Todos os 8 exclusivos capturados | You found all of them? I'm going to have to write a second notebook. |
| Depois do Ato 7 | Something's different here. The bugs are fatter. That's a compliment! |

### 9.8 Reações de contexto (antes da fala fixa)

Sem estado novo; conferem algo do jogo e falam por cima da fala do dia.

| Quem | Condição | Fala |
|---|---|---|
| Bram | primeira berry colhida na horta | Your first! Hold it up. No — higher. There. Now you're a farmer. |
| Bram | cruzamento novo registrado ontem | You grew a {STR_VAR_1}? I've never seen one! Laurel! LAUREL! |
| Bram | marco do Livro (§3.4) | *(fala do marco + prêmio)* |
| Laurel | um canteiro com erva daninha | There's a weed in bed {STR_VAR_1}. I'm not pulling it. It's your bed. |
| Laurel | Grass-type na party | That one would like it here. Let it out sometime. |
| Laurel | horta vazia (nada plantado) | Empty beds. Like an empty table. Don't make me look at it. |

---

## 10. Estado e custos

| Recurso | Qtd | O quê |
|---|---|---|
| Var | 3 | `VAR_BERRY_GARDEN_LEVEL` (1..5), `VAR_BERRY_ORDER`, `VAR_HARVEST_KING` (0..13) — reciclar `VAR_GIFT_UNUSED_5/6/7` (conferir antes que ninguém escreve) |
| Flag persistente | **67** | Livro de Berries, `0x1053..0x1095`, contíguas |
| Daily flag | 3 | `ORDER_ROLLED`, `ORDER_DONE`, `GARDEN_WATERED` em `FLAG_UNUSED_0x952..0x954`; o presente e a semente encomendada dividem a flag diária que o Bram já usa |
| `FLAG_TEMP` | ~6 | ocultação por horário (Bram fora/dentro, Laurel fora/dentro, Tilly, Bugsy), canteiro da Laurel, lendários |
| Vaga de árvore | 11 | 10 canteiros + o canteiro da Laurel, apelidos de IDs de Hoenn |
| Objetos `Route30` | +14 | 10 canteiros, Bram (fora), Laurel (fora), Tilly, Bugsy; **−1** Weedle; Calyrex e Spectrier (cena) |
| Objetos `Route30_House` | +2 | Tilly (manhã de fim de semana), Sunflora; Laurel e Bram ganham versão de dia/noite |
| Objetos `IcePath_Depths` / `BurnedTower_B1F` | +2 cada | Pryce + Glastrier / Morty + Spectrier |
| Plaquinhas novas | 4 | `NAME_BERRY_MASTER`, `NAME_LAUREL`, `NAME_TILLY`, `NAME_CALYREX` (skill `nomear-falante`) |
| C (`src/berry.c`) | médio | 6 bits de mutação, 58 receitas, trava pós-Liga, Livro (4 specials), irrigação, `GetKingsPlotStage`, `RipenGardenTrees`, tabela de pragas |
| Config | 3 | `OW_BERRY_MUTATIONS`, `_WEEDS`, `_PESTS` = TRUE |
| Encontros | −8 famílias | `wild_encounters.json` (§7.1) |
| Árvore natural | −1 | Oran de (23,38) sai de `sNaturalBerriesByTreeId` e `EventScript_ResetAllBerries` |

---

## 11. Ordem de implementação

Cada passo compila e se testa **no jogo** sozinho (um build limpo não prova a cena).

1. **Livro de Berries**: flags, 4 specials, gancho na colheita, presente do Bram só do
   Livro. Testar: colher uma Sitrus de rota → o Bram passa a dá-la.
2. **Cruzamento de 6 bits + 58 receitas**, com a trava pós-Liga. Testar três gerações
   em debug e a Lansat recusando antes da Liga.
3. **Níveis da horta**: canteiro B, irrigação, cenas de reforma.
4. **Rotina por horário** (§2) e **banco de falas** (§9). Testar os três períodos
   mudando o relógio e contar objetos na pior hora.
5. **Pedidos** (§6) com a dica da Laurel.
6. **Infestações** (§7): tabela, adubo, horário; tirar as 8 famílias da natureza.
7. **Sidequest**, ato por ato, com o estado em debug. Por último, a reação dos
   lendários e as falas de retry.
8. Fechamento: `catalogar-flags`, `nomear-falante` (checar e medir), `mapa-de-ligacoes`
   (nenhum mapa novo), atualizar `POOL_LENDARIOS.md`, render da Route 30.

---

## 12. Decisões do autor

| # | Pergunta | Recomendação |
|---|---|---|
| 1 | Nome do Berry Master na história | **Bram** (a plaquinha continua “Berry Master”) |
| 2 | Livro só registra ao **colher** (comprar não conta)? | Sim: é o que faz a horta ser a fonte |
| 3 | Tirar da loja as 24 berries vendidas hoje? | **Não**: a horta é *a* fonte completa, a loja continua como atalho |
| 4 | Glastrier e Spectrier: Ice Path Depths e Burned Tower B1F à noite | Assim |
| 5 | Nível de Glastrier/Spectrier e Calyrex | 60 e 65, sem escala; ou escala do Nexus |
| 6 | Pryce ter conhecido a Laurel jovem (Ato 6) | Sim, uma linha só, sem explicar |
| 7 | Tirar o Weedle decorativo de (19,42) | Sim, para caber o Bugsy |
| 8 | 67 flags para o Livro | Aceitável: o bloco `CUSTOM_FLAGS` tem mais de mil livres |

---

## 13. Rev 2 — Galar na horta (30/09/2026)

Pedido do autor: encaixar treinadores de Sword/Shield ligados ao Calyrex, também
no dia a dia, e pensar em notáveis com ligação com a Laurel, com o Calyrex e com
os lendários. **Sprites não são bloqueio** (o autor providencia): os renders usam
sprites genéricos como substitutos, marcados na legenda.

### 13.1 Quem entra

| Personagem | Ligação | Papel | Substituto no render | Sprite a providenciar |
|---|---|---|---|---|
| **Peony** | Em Crown Tundra, o Calyrex fala **pelo corpo dele**. Aqui, a Laurel foi babá dele em Freezington, antes de vir para Johto: ele a chama de “Auntie Laurel” | Chega no Ato 5 por causa da carta dela; o Calyrex fala por ele. Depois da história, acampa no lago nas noites de fim de semana | `HIKER` | overworld + front pic |
| **Peonia** | Filha do Peony; séria, cuida do pai | Chega correndo atrás dele no Ato 5; acompanha o jogador no Ato 6, no caminho escolhido; faz dupla com a Tilly na banquinha | `PICNICKER` | overworld + front pic |
| **Klara** | Rival de veneno do Isle of Armor, influenciadora | **Vilã do dia a dia:** algumas manhãs aparece colhendo a horta “para o canal”. Gancho do arco do Pecharunt (veneno + mochi) | `LASS` | overworld + front pic |
| **Avery** | Rival psíquico do Isle of Armor, dramático | O Calyrex é Psychic: depois da história, toda sexta ele vem “conversar telepaticamente” com o canteiro da Laurel | `PSYCHIC_M` | overworld + front pic |
| **Honey** (e Mustard) | A “esposa do mestre” do Dojo, como a Laurel é a esposa do Berry Master. Amigas por carta há 45 anos | **Cartas** que a Laurel lê de manhã; o Mustard sempre põe um P.S. | só cartas | nenhum (opcional depois) |
| **Sonia** | Pesquisadora das lendas de Galar | Uma carta depois do Ato 5: o Rei está no livro dela | só carta | nenhum |
| Pryce e Morty | Já são os campeões de Glastrier e Spectrier no Nexus | Mantidos no Ato 6 — a história agora concorda com o Nexus | existem | — |

### 13.2 Ligações com os lendários

| Lendário | Quem | Como | Status |
|---|---|---|---|
| Calyrex | **Peony** (voz), Laurel (semente) | Telepatia pelo Peony, como em Crown Tundra | nesta sidequest |
| Glastrier | Pryce, Molly Hale, Peonia | Caminho branco: **Greenfield**, o prado de cristal (§15) | nesta sidequest |
| Spectrier | Morty, Eusine, Kimono Girls, Peonia | Caminho escuro: **a Torre de Bronze na noite do incêndio** (§15); é o visitante noturno | nesta sidequest |
| **Regieleki / Regidrago** (sem fonte) | **Peony** | As Split-Decision Ruins de Crown Tundra têm uma escolha entre os dois. O Peony acha a mesma escolha em Johto: **Expedição do Peony**, pós-história | gancho (§13.5) |
| **Pecharunt, Okidogi, Munkidori** (sem fonte) | **Klara** | Veneno, mochi feito com as Pecha que ela rouba da horta, Kitakami | gancho (§13.5) |
| Aves de Galar | Peonia (fã das Dynamax Adventures) | Hoje só no Battle Café, que não conta como fonte | ideia solta, sem proposta |

### 13.3 O que muda nos atos

**Ato 4 — A primeira folha.** Na noite seguinte, a Laurel, lendo:

> **Laurel:** I wrote to Freezington. First letter in forty years.
> Someone there used to follow me around like a Yamper. He'll come. He never could
> leave a thing alone.

**Ato 5 — O Rei (substitui o §8.10).** *Enigma madura + noite. `hidefollower`. O
Peony já está ajoelhado junto ao canteiro da Laurel (chegou no barco da tarde); o
Calyrex ao lado. O Peony é quem fala pelo rei.*

> **Peony:** Auntie Laurel! Peony here! Got your letter, came on the first boat, and—
> ...hold on. Something's... tickling the back of me head...
> *(flash com `fadescreenswapbuffers`; exclamação no Peony; a plaquinha vira “???”)*
> **???:** ...You can hear me. Good. Forgive me for borrowing this one. He is loud,
> but his heart is open, and I have not the strength to speak on my own.
> **???:** This Berry... it was grown with care. By someone who remembered.
> *(o Calyrex come; `walk_in_place` duas vezes)*
> **Calyrex:** I am Calyrex. Once, they called me the King of Bountiful Harvest.
> I was a king with no field, and no one to carry me. My steeds left when the
> people forgot.
> One still wanders this land at night, looking for food. You have met him, I think.
> The other sleeps under ice that never melts.
> Bring one of them home to me, and I will show you what this garden can become.
> *(flash; o Calyrex some — `removeobject`, libera a vaga)*
> **Peony:** ...Wh— what was I on about? Why am I kneeling? Why was a turnip looking
> at me?
> *(a Laurel sai de casa e para ao lado dele)*
> **Laurel:** Hello, Peony. You got tall.
> **Peony:** AUNTIE! Ha! You haven't changed one bit! ...Did I just say something daft?
> **Laurel:** You said something true. For once.
> *(a Peonia chega correndo pela trilha — `addobject` fora da câmera)*
> **Peonia:** DAD! You can't just jump off a ship before it docks!
> ...Is that soil glowing? Is that — Grandma's story? The king?
> **Laurel:** The white one sleeps where the ice never thaws. The black one walks where
> the fire took the bells.
> Ice Path, past Mahogany. The old tower in Ecruteak. One horse. Choose.
> **Peonia:** I'm going with {PLAYER}. Someone in this family has to be sensible.

**Orçamento do Ato 5:** 11 canteiros + Calyrex + Peony + Laurel + jogador = 15, com o
follower escondido. A Peonia só entra **depois** do `removeobject` do Calyrex.

**Ato 6 — A escolha.** A Peonia espera na entrada do mapa escolhido (objeto com
`FLAG_TEMP`, estado 9):

> *Ice Path*
> **Peonia:** Peonia here! Dad's keeping the king company. They're talking about
> vegetables. I don't want to know.
> This cold is nothing. Freezington's colder. ...Okay, it's close.
>
> *Burned Tower*
> **Peonia:** I don't like ghosts. I'm fine. I'm totally fine. You go first.

Depois da captura, dos dois lados:

> **Peonia:** Wait till Dad sees! He'll say he knew all along. He didn't.

**Ato 7 — Colheita Farta.** O Peony está com o Calyrex; a Laurel **só sai de casa
depois da captura** (orçamento: 11 + Calyrex + corcel + Peony + jogador = 16 com o
follower escondido). Antes da batalha:

> **Peony:** Chum, that's a KING. I've met a king before. Well, a Chairman. My big
> brother. Not the same. Go easy on him! No — don't go easy. He'd hate that.

Depois:

> **Peony:** Grand! Absolutely grand!
> You know, back home there's ruins with a choice in 'em too. Two doors, one pick.
> Johto's got ruins. I've got a feeling. Come find me when you're ready for an
> expedition.

**Epílogo.** Linha nova da Laurel, com uma carta:

> **Laurel:** Honey wrote. Mustard cried when he read about the king.
> He says it was hay fever. He's lived on an island with no hay for fifty years.

### 13.4 Vida na horta: os visitantes de Galar

| Quem | Quando | Onde | Condição |
|---|---|---|---|
| **Klara** | 1 manhã em 7 (sorteio da primeira entrada do dia) | na frente de um canteiro maduro | horta nível 2+ e algum canteiro com fruto |
| **Avery** | sextas, de dia | diante do canteiro da Laurel | estado 13 |
| **Peony + Peonia** | sábado e domingo, de noite | acampados no lago | estado 13 |
| **Cartas** | todo dia, de manhã, lidas pela Laurel à mesa | casa | a partir do Ato 4 |

Orçamento: Klara de manhã (Bram fora, Laurel em casa) = 11 + 2 + 2 = 15; Avery na
sexta (sem Bugsy nem Tilly) = 15; Peony e Peonia à noite (Laurel em casa) = 15.

**A Klara — assalto da manhã.** Se o jogador fala com ela: batalha de veneno com
escala de nível, **sem blackout** (skill `batalha-sem-blackout`).

- **Vitória:** ela vai embora e o canteiro fica.
- **Derrota, ou o jogador sai do mapa sem falar com ela:** ela leva a colheita. Um
  special em C (`EmptyRandomRipeGardenTree`) esvazia um canteiro maduro.
- 2 daily flags: `KLARA_RAID` (sorteada e acontecendo hoje) e `KLARA_BEATEN`.

> **Klara:** Oopsie! Didn't see you there, hun~
> These are for my channel. “Top 10 Johto Snacks — Number 7 Will SHOCK You.”
> *(vitória)* Ugh, FINE. Keep your dumb Berries. ...Can I at least keep one Pecha?
> No? Rude. So rude.
> *(derrota)* Thanks for the content, hun! Like and subscribe~
> **Berry Master (depois):** That girl again. Laurel says she's got a Slowbro greener
> than my Wepear.

Depois de 5 vitórias contra ela (contador em `VAR_BERRY_ORDER`, byte alto livre, ou
var própria):

> **Klara:** You know what? Berries are SO last season. Mochi is the new thing.
> There's this cute little shop in Kitakami... Toodles~

*(gancho do arco do Pecharunt; nada muda no jogo agora)*

**O Avery — sextas.**

> **Avery:** Ahem. O King of Bountiful Harvest. It is I, Avery, psychic prodigy.
> ...He is not answering. The patch is not answering me.
> **Laurel:** It's a patch of dirt, dear. The king's in {PLAYER}'s bag.
> **Avery:** I KNEW that.

Uma fala por sexta, em rodízio pelo número de dias (`VAR_DAYS` mod 4):

- *Perhaps the king prefers a quieter mind. I shall be quieter. ...Starting tomorrow.*
- *My Slowpoke understands me. Why can't a vegetable monarch?*
- *I have brought an offering. It is a scone. Mother made it.*
- *Klara says I'm talking to a garden. I am communing. There is a difference.*

**Peony e Peonia — noites de fim de semana.**

> **Peony:** Peony here! Johto's grand, chum. The stars are the same as back home,
> just a bit to the left.
> **Peonia:** Dad, that's not how stars work.
> **Peony:** It's how MY stars work.

Rodízio de causos do Peony (`random 4`): a vez em que caiu num lago congelado
procurando o Glastrier; a vez em que o irmão dele, Rose, tentou comprar Freezington;
a vez em que a Laurel o tirou de cima de uma árvore; e “a vez em que eu era o
Chairman… não, espera, esse era o meu irmão”.

**Cartas da manhã** (a Laurel lê em voz alta, uma por dia da semana, depois do Ato 4):

| Dia | De | Carta |
|---|---|---|
| Seg | Honey | “The students ate every Berry you sent in one sitting. Mustard says his knees are fine. They are not.” |
| Qua | Freezington | “The whole village read your letter. The Mayor wants to know if Johto sells carrots.” |
| Sex | Honey | “Mustard asks if your husband can arm wrestle. Please say no. He will fly over.” |
| Dom | Sonia *(depois do Ato 5)* | “The King of Bountiful Harvest is chapter nine of my book! May I visit? I'll bring Yamper. He's very polite. He is not polite.” |

Nos outros dias, a fala normal dela de manhã.

### 13.5 Ganchos (propostas futuras, não fazem parte desta sidequest)

- **Expedição do Peony (Regieleki ou Regidrago).** O Peony acha nas Ruins of Alph
  uma câmara com duas portas e uma só chance, como as Split-Decision Ruins. O jogador
  escolhe **um** Regi; o outro fica no Nexus. Mesmo padrão do Ato 6 e da R1 do Nexus.
- **Klara e o mochi (Pecharunt, Okidogi, Munkidori).** A loja de mochi em Kitakami,
  as Pecha roubadas da horta e a Klara como a primeira vítima. Fecha os Loyal Three,
  como proposto em `LENDARIO_E_INFESTACAO.md` §1.2.

### 13.6 Custos a mais

| Recurso | Qtd |
|---|---|
| Daily flag | +2 (`KLARA_RAID`, `KLARA_BEATEN`) em `FLAG_UNUSED_0x955..0x956` |
| Plaquinhas | +4: `NAME_PEONY`, `NAME_PEONIA`, `NAME_KLARA`, `NAME_AVERY` |
| Sprites (o autor providencia) | Peony, Peonia, Klara, Avery: overworld + front pic |
| Treinadores | Klara (time de veneno, escala de nível); Avery e Peony opcionais como revanche |
| C | `EmptyRandomRipeGardenTree` |

### 13.7 Decisões do autor

| # | Pergunta | Recomendação |
|---|---|---|
| 1 | O Calyrex falar pelo Peony (como em Crown Tundra) | Sim |
| 2 | A Laurel ter sido babá do Peony em Freezington | Sim: explica por que ele vem na hora |
| 3 | Klara como vilã do dia a dia, sem blackout | Sim, e ela vira o gancho do Pecharunt |
| 4 | Avery nas sextas | Sim, cômico e barato |
| 5 | Honey só por carta, ou visita depois | Só carta na primeira versão |
| 6 | Expedição do Peony (Regieleki/Regidrago) | Proposta própria, depois desta |

---

## 14. Rev 3 — revisão, Crown Tundra de verdade, a horta viva e as batalhas de sempre (30/09/2026)

Pedido do autor: mais uma revisão; integrar mais os NPCs de Sword/Shield
importantes para o Calyrex na história; **10 variações de fala** para cada evento
repetitivo (“pensa em Harvest Moon”); e chance de **lutar de novo** com os NPCs
novos. **Onde a §14 e as seções anteriores discordam, vale a §14.**

| Pedido | Onde |
|---|---|
| Revisão | §14.1 (problemas achados e a correção de cada um) |
| NPCs de SWSH do Calyrex mais dentro da história | §14.2 (Peony hóspede e voz do Rei, sementes de cenoura, prova pelo corpo do Peony, estátua de Freezington) |
| 10 falas por evento repetitivo | §14.3 (como funciona) e §14.4 (as falas) |
| Batalhas repetíveis com os NPCs novos | §14.5 |
| Custo | §14.6 |

### 14.1 Revisão: o que estava errado ou frágil

| # | Onde | Problema | Correção |
|---|---|---|---|
| 1 | §9.5 | A dica da Laurel usa `{STR_VAR_4}` (“Page {STR_VAR_4}”). O `charmap.txt` só tem `STR_VAR_1..3`: **não compila**. | As 10 falas novas da dica (§14.4 F) usam só 3 buffers: berry, pai 1, pai 2. |
| 2 | §9.1 e §9.4 | Falas presas ao dia da semana citam o Bugsy (“Bugsy's coming today”, “The Azalea boy's coming”) **antes do Ato 1b**, quando ele nem foi chamado, e continuam dizendo isso se o jogador nunca fizer o censo. | Tudo que depende de progresso sai do rodízio e vira **reação de contexto com condição** (§14.3). O rodízio só tem fala que vale em qualquer estado. |
| 3 | §9 inteiro | Uma fala por dia da semana: no fim do primeiro mês o jogador decorou os 7. | Rodízio de **10**, com **corações** liberando as falas mais íntimas (§14.3). |
| 4 | §3.4 × §8.13 | Duas “primeiras vezes” que a Laurel diz o nome do jogador: no marco 66 do Livro **e** no epílogo. Quem chegar primeiro rouba a fala do outro. | Uma cena só, `LaurelSaysName`, na primeira das duas; a outra toca a fala alternativa (§14.4 D, reações). |
| 5 | §10 e §13.6 | 5 flags diárias soltas (`ORDER_ROLLED`, `ORDER_DONE`, `GARDEN_WATERED`, `KLARA_RAID`, `KLARA_BEATEN`), e a rev3 precisaria de mais 11. Cuidado extra: no bloco diário os nomes `FLAG_UNUSED_0x952..` repetem números que **fora** dele são flags vivas (`0x952` = `FLAG_TM_SLEEP_TALK`). | **1 flag diária + 1 var de bits** (`VAR_GARDEN_TODAY`), igual ao Kurt (`VAR_KURT_TODAY` + `FLAG_DAILY_KURT_NEW_DAY`) e ao Nexus. Layout em §14.6. |
| 6 | §13.4 | Contador de vitórias da Klara no “byte alto de `VAR_BERRY_ORDER`”. Script não faz conta de bits; ia virar bug. | Var própria `VAR_GARDEN_RIVALS` (vars livres a partir de `0x4127`). |
| 7 | §13.4 | “Peonia faz dupla com a Tilly na banquinha” no sábado de dia: 11 canteiros + Laurel + Tilly + Peonia + jogador + follower = **16**, no limite. | No fim de semana a Laurel fica **em casa** (dia de forno, §14.3). Fica 15, e a Laurel ganha um lugar novo na rotina. |
| 8 | §8.11 | As duas feras disponíveis ao mesmo tempo: o jogador descobre que “escolheu” só depois de capturar, e a tela de escolha nunca existe. | A escolha vira a **semente de cenoura**, como em Crown Tundra (§14.2): escolhe, planta, colhe, e só aparece o corcel da cenoura que você tem. |
| 9 | §13.3 | O Peony aparece no Ato 5 e some da história até o Ato 7. É a pessoa mais importante do Calyrex em SWSH e fica sem nada para fazer. | Peony e Peonia viram **hóspedes** da casa do Bram durante a busca (estados 9–13): rotina, falas, a voz do Rei de noite e a prova do Ato 7 (§14.2). |

Conferido e **ok**: orçamento de objetos dos atos (§13.3), regra da surpresa (nenhuma
fala do rodízio antes do estado 7 cita rei, corcel ou Calyrex — as falas com
isso só existem em NPCs que só aparecem depois), ordem `checkitemspace` antes de
todo presente, e o retry de todas as batalhas de história.

### 14.2 Crown Tundra na horta

Em Crown Tundra o Calyrex **fala pelo corpo do Peony**, pede o campo de volta, dá
ao jogador a escolha entre **Iceroot Carrot** (Glastrier) e **Shaderoot Carrot**
(Spectrier), e o povo de **Freezington** refaz a **estátua** do rei. A rev3 traz as
quatro coisas para a história da Laurel.

#### Estados novos (substitui a tabela do §8.1 a partir do estado 9)

| Estado | Ato | Gatilho | Onde |
|---|---|---|---|
| 0–8 | como no §8.1 | — | — |
| 8 → 9 | **Ato 5** — O Rei (versão §13.3) + **as sementes** (abaixo) | Enigma madura + noite | `Route30` |
| 9 → 10 / 11 | **Ato 5b** — A semente do corcel | plantar uma das sementes no canteiro da Laurel | `Route30` |
| 10 / 11 | *(sub-estado: tem a cenoura?)* | na noite seguinte, o canteiro dá a cenoura (item-chave) | `Route30` |
| 10 → 12 | **Ato 6 branco** | Glastrier capturado, com a Iceroot Carrot na bolsa | `IcePath_Depths` |
| 11 → 13 | **Ato 6 escuro** | Spectrier capturado, com a Shaderoot Carrot na bolsa, de noite | `BurnedTower_B1F` |
| 12 / 13 → 14 | **Ato 7** — A prova do Rei + Colheita Farta | noite, corcel na party | `Route30` |
| 14 → 15 | **Epílogo** | manhã seguinte | `Route30` / `Route30_House` |

**Estado final: 15.** Onde a rev1/rev2 dizem “estado 13”, leia 15; onde dizem
“10 = Glastrier, 11 = Spectrier”, leia 12 e 13.

#### Fim do Ato 5: as sementes

Depois do “One horse. Choose.” da Laurel (§13.3):

> **Peony:** Oi — why've I got seeds in me pocket? I haven't got pockets in this
> coat. I checked. Twice.
>
> **Laurel:** ...Iceroot. And Shaderoot. My grandmother grew both. Never at once.
> The white one won't go near the dark one's food. The dark one won't touch the
> white one's.
> One seed, in my patch. The horse comes for the carrot. Not for you. Remember that.
>
> **Peonia:** Carrots. A legendary horse. For CARROTS.
>
> **Peony:** Everyone likes a carrot, love.

*O Calyrex comeu a Enigma: o canteiro da Laurel fica vazio (special
`EmptyKingsPlot`). A escolha é feita **no canteiro**, não numa fala: ao interagir com
ele em estado 9, `multichoice` com as duas sementes e “Not yet”. Nada muda até o
jogador plantar.*

> *(ao plantar)* You planted the {STR_VAR_1}. The cold soil seems to hold its breath.

*Estado 10 (Iceroot) ou 11 (Shaderoot). As sementes **não** são itens: a escolha fica
no estado. Na **noite seguinte**, o canteiro mostra a folha da cenoura; interagir
dá o item-chave `ITEM_ICEROOT_CARROT` ou `ITEM_SHADEROOT_CARROT` (2 itens novos,
`checkitemspace` não se aplica a item-chave). Sem a cenoura na bolsa, o corcel
não aparece no mapa dele (`checkitem` no `ON_TRANSITION`, junto da `FLAG_TEMP`).*

> **Laurel (manhã seguinte ao plantio):** You picked. Good. Don't tell me which. I'll
> know when I see the leaves.

**No Ato 6**, Pryce e Morty reconhecem a cenoura (substituem a primeira linha deles
no §8.11):

> **Pryce:** ...That smell. Iceroot. My mother fed it to the Mamoswine in the worst
> winters. It calms the proud ones.
>
> **Morty:** Shaderoot. The spirits in this tower like the smell. So will he.

*Captura: `removeitem` da cenoura, estado 12 ou 13. Fugiu, perdeu ou derrotou sem
capturar: a cenoura fica, o corcel volta na próxima visita (retry do §8.1).*

#### Peony e Peonia hóspedes (estados 9–14)

Chegaram no Ato 5 e **ficam na casa do Bram** até o epílogo. Entram na rotina:

| Período | Peony | Peonia |
|---|---|---|
| Manhã | **Horta**, “ajudando” o Bram (derruba o regador; §14.4 K) | Casa, na mesa, com a Laurel |
| Dia | Casa, **dormindo no sofá** (fuso de Galar) | Na entrada do mapa escolhido (§13.3, Ato 6), se a cenoura já saiu; senão na horta com a Laurel |
| Noite | Casa, sofá: **o Calyrex fala por ele dormindo** (§14.4 M) | Casa, arrumando a mochila |

Orçamento da manhã: 11 + Bram + Peony + jogador + follower = **15**. O Calyrex
**não** fica mais no canteiro de noite nos estados 9–13 (a rev1 o deixava lá, com uma
fala fixa): ele está “dentro” do Peony. Libera a vaga e cabe a Peonia nas cenas.

Casa (`Route30_House`): +2 objetos (Peony, Peonia), com `FLAG_TEMP` pelo estado.

#### Ato 7 — A prova do Rei (substitui a batalha do §8.12)

Em Crown Tundra, o Rei testa o jogador pelo corpo do Peony. Aqui, **duas batalhas**:

1. **A prova.** O Calyrex toma o Peony (flash, exclamação, plaquinha “Calyrex”) e
   luta com o **time do Peony** (`TRAINER_HARVEST_KING_TRIAL`, classe e nome
   “Calyrex”; front pic do Peony). **Sem blackout** (skill `batalha-sem-blackout`):
   perdeu, tenta de novo na próxima noite; ganhou, segue.
2. **O Rei.** Encontro fixo com o Calyrex (nível do §12, decisão 5). Só a captura
   avança para o estado 14.

> **Calyrex (pelo Peony):** You found him. Good. Now a king must know who carries
> his harvest.
> This one's Pokémon are strong, and very fond of him. They will fight for me
> tonight. Forgive us both.
>
> *(vitória)* **Calyrex:** Yes. You are the one the field remembers.
> *(flash; o Peony cai sentado)*
> **Peony:** ...Did I win? I feel like I lost. Me Copperajah's looking at me funny.

Depois da captura seguem as falas do §13.3 (“Grand! Absolutely grand!”) e o
presente das Reins of Unity da Laurel (§8.12).

#### A estátua de Freezington

Em Crown Tundra o povo refaz a estátua do rei e ele volta a ter força. Aqui é a
**carta do Freezington** que chega depois do epílogo (§14.4 O, carta 8), e o
Calyrex sente de longe (§14.4 N, fala 6). Não custa nada e fecha o paralelo: a
Laurel lembrou em Johto, e a vila dela lembrou em Galar.

#### Quem é quem, agora

| Personagem | SWSH | Rev 3 |
|---|---|---|
| **Peony** | Voz do Calyrex; dá as sementes; ex-Líder de Aço, irmão do Rose | Hóspede; o Rei fala por ele dormindo; a **prova do Ato 7** é com o time dele; batalha semanal depois (§14.5) |
| **Peonia** | Filha do Peony, Max Lair | Hóspede; acompanha o Ato 6; ajudante da banquinha da Tilly; batalha e **dupla com a Tilly** (§14.5) |
| **Freezington** | Vila que refaz a estátua | Terra da Laurel; cartas; a estátua refeita no pós-história |
| **Honey e Mustard** | Mestres do Dojo | Cartas; o **Mustard aparece em pessoa**, raramente, e luta (§14.5) |
| **Klara e Avery** | Rivais do Isle of Armor | Visitantes do dia a dia; batalha repetível (§14.5) |
| **Sonia** | Lendas de Galar | Cartas |

### 14.3 Como a horta fica viva

**Rodízio de 10.** Cada evento repetitivo tem um banco de 10 falas. O índice é
`VAR_DAYS % N`: a mesma fala o dia todo (como um aldeão de Harvest Moon), e nenhuma
se repete antes de N dias. Um special genérico escolhe:

```c
// GardenLine_Pick: VAR_0x8004 = pool (GARDEN_POOL_*), VAR_0x8005 = hearts tier
// returns in VAR_RESULT the line index 0..N-1 (N = 4, 7 or 10 by tier)
```

O script faz `switch VAR_RESULT` para os 10 `msgbox`. Nada de flag.

**Corações (Harvest Moon).** Quatro personagens têm corações: **Bram, Laurel, Tilly e
Peony**. Sobe 1 por **dia em que o jogador fala com ele** (uma vez por dia, bit em
`VAR_GARDEN_TODAY`), até 15. As falas 1–4 valem sempre; 5–7 com **5 dias**; 8–10 com
**12 dias** (as mais íntimas). O jogador sente o personagem se abrindo sem ver
número nenhum. Os outros (Bugsy, Klara, Avery, Peonia, Calyrex, cartas, pragas,
pedidos) rodam os 10 direto.

```c
// VAR_GARDEN_HEARTS: 4 bits por personagem (0..15)
//   bits 0-3 Bram, 4-7 Laurel, 8-11 Tilly, 12-15 Peony
// GardenHearts_Talk: VAR_0x8004 = personagem; soma 1 se ainda não falou hoje;
//   devolve o tier (0, 1, 2) em VAR_RESULT
```

**Ordem de cada conversa** (a primeira que casar, ganha):

1. Cena de história pendente (atos).
2. **Reação de contexto** (tabelas “reações” em cada banco do §14.4 e §9.8): algo
   aconteceu (cruzamento novo, marco do Livro, Klara levou um canteiro, Calyrex na
   party…). Só na **primeira** conversa do dia com aquele personagem.
3. Fala do rodízio.

**A semana, com a rev3:**

| Período | Seg–Sex | Sáb e Dom |
|---|---|---|
| Manhã | Bram na horta; Laurel em casa (café, cartas) | igual; Tilly em casa |
| Dia | Laurel na horta; Bram em casa; Bugsy ter/qui; Avery sex (pós-história) | **Laurel em casa, dia de forno**; Tilly (+ Peonia, pós-história) na banquinha |
| Noite | Bram dormindo; Laurel lendo | igual; Peony e Peonia acampados no lago (pós-história) |

Eventos que **sorteiam** o dia (primeira entrada do dia na Route 30, special
`GardenRollDay`, grava em `VAR_GARDEN_TODAY`):

| Evento | Chance | Exclui |
|---|---|---|
| Assalto da Klara | 1 manhã em 7 (horta nível 2+ e algum canteiro maduro) | Mustard |
| Visita do Mustard | 1 domingo em 4 (estado 15) | Klara |

### 14.4 O banco de falas

Tudo em inglês, em prosa (quebrar linha com `nomear-falante/medir_linha.py` ao
escrever o `.inc`). Coluna ♥: **0** sempre, **1** com 5 dias de conversa, **2** com 12.

#### A. Bram — manhã, na horta, depois do presente

| # | ♥ | Fala |
|---|---|---|
| 1 | 0 | Water before the sun's up and the leaves won't burn. My father told me that. Then he watered at noon every day of his life. |
| 2 | 0 | You know how you tell a ripe Berry? You don't. The Berry tells you. |
| 3 | 0 | I talk to the trees. Laurel says it doesn't help. The trees haven't complained. |
| 4 | 0 | Dew on the leaves, sprout. That's the garden saying good morning. Say it back. ...Out loud. There you go. |
| 5 | 1 | My knees know the weather before the radio does. Today they say "sunny, with a chance of Bram sitting down." |
| 6 | 1 | First tree I ever planted was an Oran. I was six. Watered it so much it drowned. Planted another right on top. That one's still out back. |
| 7 | 1 | Kurt wants Berries again. I asked what for. He said "Balls." Then he hung up on me. |
| 8 | 2 | You're here every morning now. Tilly asked if you live here. I said, "Near enough." |
| 9 | 2 | When the garden was just me, I talked to the trees. Now I talk to you. The trees were better listeners. Don't tell them I said that. |
| 10 | 2 | Laurel set out a third cup this morning. Didn't say a word about it. That one's yours, sprout. That's how she says it. |

Reações (primeira conversa do dia; além das do §9.8):

| Condição | Fala |
|---|---|
| terça ou quinta, estado ≥ 3 | Bugsy's coming today. He brought a notebook last time. The time before, two. |
| domingo | Sunday! Tilly's selling out front. Buy something, or she'll follow you to Violet. |
| a Klara levou um canteiro ontem | *(uma das 5 falas “Bram depois da Klara”, em I)* |
| hóspedes em casa (estados 9–14) | Peony's "helping." He's knocked over the watering can three times. I've started filling it with less water. |

#### B. Bram — de dia, em casa, separando sementes

| # | ♥ | Fala |
|---|---|---|
| 1 | 0 | Seed day. Sit down. No — not on those. Those are Persim. |
| 2 | 0 | I've got a seed here I can't name. Could be a Wiki. Could be a pebble. We'll find out. |
| 3 | 0 | Every seed in this jar is a tree someday. Every one. That's what gets me up in the morning. That and Laurel. |
| 4 | 0 | You sort seeds by size, then by shape, then by smell. Then Laurel comes in and sorts them all again. |
| 5 | 1 | Forty years married. The trick is, she's always right, and I'm always hungry. |
| 6 | 1 | When I was your age I wanted to be a Pokémon Trainer. Then I grew a tomato. That was that. |
| 7 | 1 | Tilly asked why the sky is blue. I said, "Because the Oran Berries are." She believed me for a whole year. |
| 8 | 2 | I wrote your name on the seed jar. Laurel crossed it out and wrote it again, neater. That's a compliment, sprout. From her, that's a medal. |
| 9 | 2 | My old man said a farmer's rich if he's got more seed than worry. Most days I'm rich now. You helped. |
| 10 | 2 | Want to know a secret? I don't know half the Berries in that Book. I just nod when Laurel says them. |

#### C. Bram — de noite, dormindo

Sem corações (sonho não tem intimidade): `random 10`.

| # | Fala |
|---|---|
| 1 | Zzz... No, no, the Sitrus goes by the fence... |
| 2 | Zzz... Laurel... there's a Combee in my hat... |
| 3 | Zzz... Forty-one... forty-two... forty-three Pecha... |
| 4 | Zzz... Kurt, you owe me for the Leppa... |
| 5 | Zzz... Hm? The Book? ...Six more... zzz... |
| 6 | Zzz... Tilly... that's not a Rellor... that's my breakfast... |
| 7 | Zzz... biggest Oran in Johto... the judges are weeping... |
| 8 | Zzz... sprout... water the... the... zzz... |
| 9 | Zzz... Bugsy... put it down... that's the salt... |
| 10 | *estado < 8:* Zzz... just one more row... · *8–14:* Zzz... it came up... it finally came up... · *15:* Zzz... Laurel... you're singing... |

#### D. Laurel — de manhã, em casa (dias sem carta)

| # | ♥ | Fala |
|---|---|---|
| 1 | 0 | Sit. Eat. The Berries can wait ten minutes. He can't, but they can. |
| 2 | 0 | Toast. No, you don't want jam. That's Tilly's jam. Nobody wants Tilly's jam. |
| 3 | 0 | He left at four. He always leaves at four. I stopped setting an alarm years ago. |
| 4 | 0 | Wipe your feet. ...The other one too. |
| 5 | 1 | The kettle's older than you. It whistles off-key. I won't replace it. |
| 6 | 1 | He talks to the trees. I talk to the kettle. Everyone needs someone who doesn't answer back. |
| 7 | 1 | Where I grew up, breakfast was fish and bread and more bread. This is better. Don't tell anyone I said so. |
| 8 | 2 | You've got soil under your nails. Good. Hands that are too clean don't grow anything. |
| 9 | 2 | Frost on the window. Not real frost. Johto frost. ...I miss real frost. That's all. Eat. |
| 10 | 2 | I made too much. I always make too much now. ...Take it with you. |

Reações:

| Condição | Fala |
|---|---|
| a primeira das duas: Livro 66 **ou** estado 15 (`LaurelSaysName`) | Good morning, {PLAYER}. ...What? I know your name. I've always known your name. |
| a segunda das duas | {PLAYER}. There. I'll say it twice now. Don't get used to it. |
| sábado ou domingo, de dia (dia de forno) | Bread day. Don't open the oven. Don't look at the oven. The oven can feel you looking. |
| hóspedes em casa (estados 9–14) | Peony ate four breakfasts. Peonia ate one and apologized for him four times. |

*(sábado e domingo de dia a Laurel está em casa: usa o banco E, com a reação do forno
na primeira conversa.)*

#### E. Laurel — de dia (horta; em casa no fim de semana)

| # | ♥ | Fala |
|---|---|---|
| 1 | 0 | Too much water. Not you. Him. |
| 2 | 0 | Weeds are just plants in the wrong place. I'm not sentimental about it. |
| 3 | 0 | You're standing on a sprout. ...No. The other foot. |
| 4 | 0 | Tilly counts the money. I count the Berries. Neither of us trusts the other one. |
| 5 | 1 | Freezington had one road and one shop. I liked it. Don't tell him. |
| 6 | 1 | Plant the sour ones by the pond. They like wet feet. Like him. |
| 7 | 1 | Forty years I've knelt in this dirt. My knees are Johto now. The rest of me hasn't decided. |
| 8 | 2 | My grandmother kept a field. Harder soil than this. She'd have liked you. She didn't like anyone. |
| 9 | 2 | You come every day. I noticed. I don't say things I notice. I'm saying this one. |
| 10 | 2 | When I'm gone, this garden... No. Never mind. Pull that weed. |

#### F. Laurel — de noite, a dica do caderno

Buffers: `STR_VAR_1` = berry nova, `STR_VAR_2` e `STR_VAR_3` = pais
(`BerryLedger_NextDiscovery` + `bufferitemname`). Sem corações: todo mundo recebe a
dica, só o jeito muda.

| # | Fala |
|---|---|
| 1 | {STR_VAR_1}. {STR_VAR_2} beside {STR_VAR_3}. Touching, side by side. Not corner to corner. People always do corner to corner. |
| 2 | The page with the coffee stain. {STR_VAR_1}. You'll want {STR_VAR_2} next to {STR_VAR_3}. I'm not telling you twice. |
| 3 | My grandmother's hand. Hard to read. ...{STR_VAR_2} and {STR_VAR_3}, side by side, and you get {STR_VAR_1}. Probably. |
| 4 | You want something. Fine. {STR_VAR_1}. Plant {STR_VAR_2} by {STR_VAR_3}. Now let me read. |
| 5 | Here. {STR_VAR_1}. {STR_VAR_2}, then {STR_VAR_3} right beside it. Don't crowd them. They sulk. |
| 6 | He'd tell you this with a song and a dance. I'll just tell you. {STR_VAR_2} next to {STR_VAR_3}. That's {STR_VAR_1}. |
| 7 | {STR_VAR_1}. I grew one once, in a teacup, on a windowsill in Freezington. {STR_VAR_2} and {STR_VAR_3}. Side by side. |
| 8 | It says here: "{STR_VAR_2} and {STR_VAR_3}, touching, make {STR_VAR_1}." Somebody underlined it three times. It was me. |
| 9 | Sit. No, closer, the lamp's bad. {STR_VAR_1}. {STR_VAR_2} beside {STR_VAR_3}. There. Go to bed. |
| 10 | You're still up. So am I. {STR_VAR_1}: {STR_VAR_2} with {STR_VAR_3}. ...I'll tell you tomorrow, if you forget. |

Sem descoberta possível (Livro completo, ou nenhum par pronto):

| Condição | Fala |
|---|---|
| Livro completo | Nothing left in here you haven't grown. I don't know whether to be proud or bored. |
| nenhum par com os dois pais no Livro | Nothing for you tonight. Grow what you've got. The book isn't going anywhere. |

#### G. Tilly — fim de semana, de dia, na banquinha (antes da loja)

| # | ♥ | Fala |
|---|---|---|
| 1 | 0 | Welcome to Tilly's Mulch Emporium! It's mulch. It's the best mulch. Grandpa made it but I named it. |
| 2 | 0 | Do you know what Rellor do with mulch? They ROLL it. I'm going to have ten Rellor. Grandma said one. |
| 3 | 0 | Today's special is mulch! Yesterday's special was ALSO mulch. It's a very special shop. |
| 4 | 0 | I named a Combee Buzzbelle. She stung Grandpa. Now she's Buzzbelle the Brave. |
| 5 | 1 | Grandma says a good shopkeeper doesn't talk too much. Grandma's wrong about that. Grandma's wrong about ONE thing. |
| 6 | 1 | Buy three mulch and you get a sticker! I'm out of stickers. You get a high five. Up top! |
| 7 | 1 | I'm going to be a Bug Catcher. The best one. Better than Bugsy. Don't tell Bugsy. Actually, tell him. He'll laugh. |
| 8 | 2 | Grandpa lets me water the Pecha. Grandma watches me water the Pecha. I think she thinks I'll drown it. |
| 9 | 2 | You come every weekend! That makes you a regular. Regulars get the good mulch. It's the same mulch. But I SAY it's good. |
| 10 | 2 | When I grow up I'll have a garden next to Grandpa's. And you can have one next to mine. And we'll share the bugs. |

Reações (substituem as situações do §9.6): inseto na party (“Is that a {STR_VAR_1}?!
Can I hold it? I'm holding it.”), depois do Ato 2, depois do Ato 7 e Livro completo,
como estão lá.

#### H. Bugsy — terça e quinta, na horta (estado ≥ 3)

| # | Fala |
|---|---|
| 1 | Every color of Berry calls a different bug. I've got a chart. It's twelve pages. |
| 2 | Try Stable Mulch on one bed. Watch what moves in. You'll love him. |
| 3 | Don't swat anything! Everything here is somebody's data. |
| 4 | A Volbeat's tail blinks in patterns. I think this one's saying "more Berries." Or it's broken. |
| 5 | I've started lying down in the dirt. Bugs are less shy at eye level. Laurel hates it. |
| 6 | The Scatterbug here have a wing pattern I've never seen. Your garden is making its own Vivillon! |
| 7 | My Gym Trainers keep asking where I go on Tuesdays. I say "fieldwork." They think it's a date. |
| 8 | Combee visit one flower at a time. Your red beds get the morning shift. The yellow beds get the afternoon. |
| 9 | Kurt says bugs are a waste of good Berries. Then he asks me what bait catches a Heracross. Every time. |
| 10 | When I was little I had a garden like this. Well, a flowerpot. Well, a flowerpot with one Caterpie in it. This is better. |

Reações: as do §9.7 (hotel pronto, os 8 exclusivos, depois do Ato 7).

#### I. Klara — o assalto da manhã

Abertura (10):

| # | Fala |
|---|---|
| 1 | Oopsie! Didn't see you there, hun~ These are for my channel. "Top 10 Johto Snacks — Number 7 Will SHOCK You." |
| 2 | Shh! I'm live! ...Hi, besties! Today we're foraging! Foraging means taking. Don't tell anyone~ |
| 3 | Oh, it's YOU. The Berry police. Ugh, fine. Arrest me. In battle. Cutely. |
| 4 | These Pecha are, like, SO pink. My followers need them. It's basically charity. |
| 5 | I'm not stealing, hun. I'm "sourcing locally." It's a whole trend. |
| 6 | Don't look at me like that! I left a thank-you note! ...It says "thx." It counts! |
| 7 | My Slowbro's hungry. And when she's hungry she's mean. Like me! Hehe~ |
| 8 | You again?! Do you, like, LIVE in this garden? Get a hobby. Oh wait. This is your hobby. Cringe. |
| 9 | New video idea: "I Battled a Farmer for Snacks!" You're the farmer. Smile! |
| 10 | Okay, okay. Final offer: I take ONE bed, you get a shout-out. ...No? Fine. Battle me, hun~ |

Ela perde (5) · ela ganha e leva um canteiro (5) · o Bram na conversa seguinte (5):

| # | Klara perde | Klara ganha | Bram depois |
|---|---|---|---|
| 1 | Ugh, FINE. Keep your dumb Berries. ...Can I at least keep one Pecha? No? Rude. So rude. | Thanks for the content, hun! Like and subscribe~ | That girl again. Laurel says she's got a Slowbro greener than my Wepear. |
| 2 | That footage is SO getting deleted. | Ooh, this one's heavy! Must be the good stuff. Byeee~ | She took the WHOLE bed? ...Well. It'll grow back. Everything grows back. That's the nice thing about Berries. |
| 3 | My ring light was in my eyes. That's why. Obviously. | Tell the old man I said hi! Actually, don't. | She left a note. "thx." With a heart. Laurel's framing it. Out of spite, I think. |
| 4 | Whatever! Berries have, like, carbs anyway. | Harvest complete! Klara out~ | When I was a boy we had a word for her kind. The word was "Tuesday." Don't ask. |
| 5 | You're lucky I'm nice. I'm not nice. You're just lucky. | Don't cry, hun. You can grow more. That's, like, what plants DO. | You chased her off? Ha! Sprout, you're a real farmer now. Farmers have enemies. |

*(a coluna “Bram depois” toca a do mesmo número da última fala da Klara; a 5ª só se o
jogador venceu)*

#### J. Avery — sextas, de dia, no canteiro da Laurel (estado 15)

| # | Fala |
|---|---|
| 1 | Ahem. O King of Bountiful Harvest. It is I, Avery, psychic prodigy. ...He is not answering. The patch is not answering me. |
| 2 | Perhaps the king prefers a quieter mind. I shall be quieter. ...Starting tomorrow. |
| 3 | My Slowpoke understands me. Why can't a vegetable monarch? |
| 4 | I have brought an offering. It is a scone. Mother made it. |
| 5 | Klara says I'm talking to a garden. I am COMMUNING. There is a difference. |
| 6 | I sense... great power. Oh. It's you. Hello. You may go. |
| 7 | I bent a spoon for the king. As tribute. Laurel took it for the kitchen. |
| 8 | The Master says the strongest mind is an empty one. I've been practicing. It's very hard for someone as gifted as I am. |
| 9 | The king spoke to ME once. Well. It was a sneeze. But a very meaningful sneeze. |
| 10 | I came to Johto to train. Also because Klara came. Not BECAUSE of Klara. Coincidence. ...Psychics don't believe in coincidence. Forget I said that. |

Reação (Calyrex na party): **Laurel:** It's a patch of dirt, dear. The king's in
{PLAYER}'s bag. · **Avery:** I KNEW that. *(a cena do §13.4, agora só quando é
verdade)*

#### K. Peony — manhã na horta (hóspede) e noites de fim de semana no lago (pós-história)

| # | ♥ | Fala |
|---|---|---|
| 1 | 0 | Peony here! Johto's grand, chum. The stars are the same as back home, just a bit to the left. |
| 2 | 0 | Did I ever tell you about the time I fell in a frozen lake looking for the white horse? Came out a Peony-sicle! Worth it! |
| 3 | 0 | Me Copperajah's asleep by the pond. Snores like a steam train. Tilly thinks it's a monster. It IS a monster! A lovely one! |
| 4 | 0 | You know what they call me in Freezington? "That loud one." Ha! Fair! |
| 5 | 1 | My big brother Rose tried to buy Freezington once. The whole village. The Mayor sold him a hat and sent him home. |
| 6 | 1 | I was a Gym Leader once, y'know! Steel types! ...Then I quit. Rose was ever so cross. Best day of me life. |
| 7 | 1 | The king still talks through me sometimes. In me sleep. Peonia says I say "carrots" a lot. |
| 8 | 2 | Auntie Laurel pulled me out of a tree once. I was eight. Up there three hours. She never asked why. Brought me a sandwich. |
| 9 | 2 | When I was a lad, Auntie told us the king would come back if someone grew a garden for him. We thought it was a bedtime story. Shows what we knew! |
| 10 | 2 | Chum... thanks. For Auntie. She hasn't smiled this much since... well. Since ever, honestly. Ha! |

Hóspede de manhã (estados 9–14), antes do rodízio, na primeira conversa do dia:
*“Peony here! Bram's put me on watering duty. I've watered the path, the fence, and
Bram. The Berries are next!”* A fala 7 só vale no estado 15.

#### L. Peonia — hóspede de manhã em casa; banquinha no fim de semana (pós-história)

| # | Fala |
|---|---|
| 1 | Peonia here! ...Why is everyone in Johto so calm? It's suspicious. |
| 2 | Dad got lost going to the Pokémon Center. It's across the road. He went the long way. Through the pond. |
| 3 | Tilly's hired me. I'm "Assistant Mulch Manager." I get paid in Berries. Mostly Pecha. Mostly bitten. |
| 4 | Back home I do Dynamax Adventures. Here I carry mulch. Honestly? Mulch is harder. |
| 5 | Don't tell Dad, but I think Johto's prettier than Galar. Don't tell Galar either. |
| 6 | Grandpa Bram — he said I could call him that — taught me how to tell a ripe Berry. You don't. The Berry tells you. I think he made that up. |
| 7 | Dad cries at everything. He cried at a sunset on the boat. It was a normal sunset. |
| 8 | Auntie Laurel's the only one who can tell Dad "no" and make it stick. I'm studying her technique. |
| 9 | I'm training for a real expedition someday. Not Dad's kind. The kind with maps. |
| 10 | Thanks for taking me along, back then. I was scared. I'm telling you that once. Only once. |

*(nos estados 9–13, só 1, 2, 4, 5 e 7: as outras dependem da história acabada)*

#### M. O Calyrex pelo Peony dormindo (estados 9–13, noite, sofá)

Plaquinha `NAME_CALYREX`; antes da fala, `Common_Movement_ExclamationMark` no Peony.

| # | Fala |
|---|---|
| 1 | ...Peony is sleeping. I am not. Do not be alarmed. I will return him by morning. |
| 2 | The Berry your Laurel grew... I can still taste it. Forty years of patience, in one fruit. |
| 3 | The white one was proud. The black one was lonely. Either will do. Neither will come easily. |
| 4 | In the old days, whole villages brought me their harvest. Now one old woman, one old man, and you. It is enough. It is more than enough. |
| 5 | This one's dreams are very loud. He is dreaming of a sandwich. It is an enormous sandwich. |
| 6 | The land here is young. It remembers little. But it remembers you — every morning you came, every seed. That is how a field learns. |
| 7 | Laurel sings in her sleep. She does not know. I will not tell her. Neither will you. |
| 8 | When I was strong, I did not need to borrow. Now I borrow. Thank this one for me. He will not remember. |
| 9 | A king is only what his people remember. Your Book... it is a kind of remembering. |
| 10 | Go and sleep. Farmers wake early. Even kings know that. |

#### N. O Calyrex na party, no canteiro da Laurel (estado 15, noite)

Interagir com o canteiro de noite com o Calyrex na party, antes do menu de berry:

| # | Fala |
|---|---|
| 1 | This field has grown fond of you. So have I. |
| 2 | Leave the Enigma here. I like to know where it is. |
| 3 | The steed wants to run. Let him, sometime. |
| 4 | Bram talks to the trees. They do listen. I would know. |
| 5 | Tilly asked me if I am a turnip. I said yes. It seemed kind. |
| 6 | In Freezington they have mended my statue. I felt it, all the way here. It tickled. |
| 7 | When you are old, grow something. It does not matter what. |
| 8 | I have eaten three Pecha tonight. A king may do as he likes. |
| 9 | The bugs of this garden are very well fed. Your Bugsy is a good steward. |
| 10 | Thank you. I do not say it enough. Kings rarely do. |

*(a 6 só depois da carta 8 do banco O ter sido lida — ou sempre no estado 15, se não
quiser amarrar)*

#### O. As cartas da manhã (a Laurel lê à mesa; a partir do Ato 4)

Segunda, quarta, sexta e domingo, no lugar da fala do banco D. Carta = `VAR_DAYS % 10`;
se a carta sorteada ainda não pode (coluna “Desde”), vale a fala do banco D.

| # | De | Desde | Carta |
|---|---|---|---|
| 1 | Honey | Ato 4 | "The students ate every Berry you sent in one sitting. Mustard says his knees are fine. They are not." |
| 2 | Freezington | Ato 4 | "The whole village read your letter. The Mayor wants to know if Johto sells carrots." |
| 3 | Honey | Ato 4 | "Mustard asks if your husband can arm wrestle. Please say no. He will fly over." P.S., in different handwriting: "I would win." |
| 4 | Sonia | Ato 5 | "The King of Bountiful Harvest is chapter nine of my book! May I visit? I'll bring Yamper. He's very polite. He is not polite." |
| 5 | Honey | Ato 4 | "I tried your Pecha jam. It exploded. Mustard ate it off the ceiling." |
| 6 | Freezington | Ato 4 | "Snow's up to the windows. The children built a snow Laurel. It's frowning. It's very accurate." |
| 7 | Kurt | Ato 4 | "Berries arrived. Some bruised. Send more. — K." **Laurel:** From Kurt, that's a love letter. |
| 8 | Freezington | estado 15 | "We mended the old statue in the square. Nobody remembers who suggested it. The Mayor cried. So did the statue, a bit, when the ice melted." |
| 9 | Honey | estado 15 | "Mustard has taken up gardening. He planted one seed and named it. He talks to it. I hear you know the type." |
| 10 | Sonia | Ato 5 | "Leon says hello. Well — Leon got lost on the way to the post office, so I'm saying it for him." |

#### P. A praga aparece (só nos canteiros da horta)

Troca o “A Pokémon appeared!” de `BerryTree_EventScript_EncounterPests`
(`data/scripts/berry_tree.inc:458`) por um sorteio de 10 — só em `IsBerryGardenTree`;
fora da horta fica o texto do motor. Narração, sem plaquinha.

| # | Fala |
|---|---|
| 1 | Something is nibbling at the leaves! |
| 2 | The branches are shaking... there's a bug in this tree! |
| 3 | A tiny face peeks out from between the Berries! |
| 4 | Crunch. Crunch. Crunch. Somebody's having breakfast! |
| 5 | A trail of bitten leaves leads straight into the tree! |
| 6 | The whole tree is buzzing! |
| 7 | Something drops out of the branches, hugging a Berry! |
| 8 | Two little eyes are glowing between the leaves! |
| 9 | Someone got here before you — and they're still here! |
| 10 | The Berries are moving. Berries shouldn't move. |

#### Q. O pedido do dia — quem pede

`STR_VAR_1` = berry no plural (`bufferitemnameplural`), `STR_VAR_2` = quantidade
(`buffernumberstring`). O cliente é o índice do rodízio; o pedido em si continua
sorteado do Livro (§6).

| # | Cliente | Fala |
|---|---|---|
| 1 | Kurt | Kurt called. Wants {STR_VAR_2} {STR_VAR_1}. Said "by tomorrow." Kurt thinks everything's by tomorrow. |
| 2 | Floricultura de Goldenrod | The girls at the Goldenrod flower shop want {STR_VAR_2} {STR_VAR_1} for the window. Pretty ones, they said. As if I grow ugly ones. |
| 3 | Nurse de Cherrygrove | Nurse in Cherrygrove's running low. {STR_VAR_2} {STR_VAR_1}. For the patients, she says. For her tea, I say. |
| 4 | Moomoo Farm | Moomoo Farm's Miltank have gone off their feed. {STR_VAR_2} {STR_VAR_1} ought to fix that. |
| 5 | Day Care | The Day Care couple want {STR_VAR_2} {STR_VAR_1}. The babies love them. The old man loves them more. |
| 6 | Bugsy *(estado ≥ 3; senão cai no 1)* | Bugsy wants {STR_VAR_2} {STR_VAR_1}. "For bait," he says. The bait always gets eaten by Bugsy. |
| 7 | Teatro de Ecruteak | Letter from Ecruteak. The dance theater wants {STR_VAR_2} {STR_VAR_1}. Those Kimono Girls eat like Snorlax, I'm told. |
| 8 | Farol de Olivine | The lighthouse in Olivine. {STR_VAR_2} {STR_VAR_1}, for the Ampharos. That Ampharos eats better than I do. |
| 9 | Escola de Violet | The teacher at the Violet school wants {STR_VAR_2} {STR_VAR_1} for a lesson. Kids learn more from a Berry than a book, I say. |
| 10 | Laurel | Laurel wants {STR_VAR_2} {STR_VAR_1}. She won't say why. She never says why. Just bring them. |

Entrega (rodízio de 5, mesmo índice % 5):

| # | Fala |
|---|---|
| 1 | That's the lot! Here's your pay. Don't spend it all on mulch. Spend some of it on mulch. |
| 2 | Look at the size of these! They'll think I grew them. I'll let them. |
| 3 | Perfect. You pick 'em better than I do now. Don't tell anyone. |
| 4 | Right on time. Kurt'll be furious. He likes being disappointed. |
| 5 | Good work, sprout. That's a farmer's money. Earned in dirt. |

#### R. O presente da manhã (o Bram dá as berries do Livro)

| # | Fala |
|---|---|
| 1 | Morning, sprout! Picked these at dawn. Still cold. That's how you know they're good. |
| 2 | Here. From the Book. Grow 'em well. |
| 3 | Hold out your hands. No — both hands. There. |
| 4 | These practically jumped into the basket. Take 'em before they jump out. |
| 5 | Laurel said give you the good ones. These are the good ones. The bad ones I ate. |
| 6 | Fresh as the morning! Which it is. Morning, I mean. |
| 7 | Something for your beds, and something for your pocket, in case you get hungry. |
| 8 | Wrote these down in the Book twice. Big day for these ones. |
| 9 | Eh? Oh! Almost forgot. Here. Don't tell Tilly, she'll want a cut. |
| 10 | For you. Same as every day. Tomorrow too. That's a promise, sprout. |

#### S. Mustard — a visita rara (domingo de manhã, 1 em 4, estado 15)

Ele aparece na horta ao lado do Bram, sem avisar. Rodízio de 5 (visitas raras).

| # | Fala |
|---|---|
| 1 | Hmhm! So YOU'RE the one Honey keeps writing about! The berries are real! I thought she was making it up to get me to exercise! |
| 2 | Bram! Arm wrestle! ...No? Then I'll arm wrestle your student. With Pokémon. It's the same thing. |
| 3 | My knees? Perfect! Never better! ...Could I sit down for a moment? Just a small moment. |
| 4 | I told my students, "Go to Johto and learn humility from a garden." None of them went. So I came myself! |
| 5 | Laurel! Honey sends her love, and a jar of jam. It hasn't exploded yet. Stand back, just in case. |

### 14.5 As batalhas de sempre

Todas seguem o padrão do Nexus (`data/scripts/nexus.inc`, macro `nexus_fight`):
`cleartrainerflag` antes e depois, `B_FLAG_NO_WHITEOUT` só durante a batalha,
resultado em `GetBattleOutcome`. **Perder não custa nada** (exceto o assalto da
Klara, que leva o canteiro). **Uma por dia por NPC** (bit em `VAR_GARDEN_TODAY`);
prêmio só na vitória. Nível pela escala do repo (`src/level_scaling.c`, como a Klara
da rev2). Proposta: macro `garden_fight` em `data/scripts/berry_garden.inc`, cópia da
`nexus_fight`.

| NPC | Quando | Onde | Desde | Time (rodízio `VAR_DAYS % 3`) | Prêmio |
|---|---|---|---|---|---|
| **Tilly** | sáb e dom, dia | banquinha | estado 1 | Os insetos que ela batizou (abaixo). Tamanho pelo **nível da horta**, não pelo rodízio | 2 adubos da loja dela |
| **Tilly + Peonia** (dupla, `trainerbattle_two_trainers`) | sáb e dom, dia | banquinha | estado 15 | 2 da Tilly + 2 da Peonia | 1 Surprise Mulch |
| **Bugsy** | ter e qui, dia | horta | Ato 1c (estado 4) | Vermelho: Ledian, Heracross, Beautifly · Azul: Orbeetle, Volbeat, Galvantula · Rosa/verde: Ribombee, Vivillon, Leavanny — sempre com o Scizor | 3 berries do Livro |
| **Klara** | manhã sorteada (§14.3) | horta | nível 2 da horta | Galarian Slowbro sempre + (Skuntank, Galarian Weezing) · (Salazzle, Toxapex) · (Toxicroak, Glimmora) | salva o canteiro; na 5ª vitória, o gancho do mochi (§13.4) |
| **Avery** | sex, dia | canteiro da Laurel | estado 15 | Galarian Slowking sempre + (Alakazam, Swoobat) · (Espathra, Gardevoir) · (Bronzong, Hatterene) | 1 berry rara do Livro |
| **Peony** | estados 9–14: manhã, horta · 15: sáb e dom, noite, lago | horta / lago | Ato 5 | Copperajah sempre + (Aggron, Bronzong) · (Excadrill, Perrserker) · (Corviknight, Duraludon) | 1 Exp. Candy M *(conferir no `SOULGOLD_ITEMS_AUDIT.md`)* |
| **Peonia** | estado 15: sáb e dom, noite, lago (escolhe “Dad” ou “Me”) | lago | estado 15 | Gelo de Freezington: Mr. Rime sempre + (Frosmoth, Eiscue) · (Galarian Darmanitan, Arctozolt) · (Cetitan, Glalie) | 2 adubos |
| **Mustard** | domingo sorteado, manhã | horta | estado 15 | Luxray, Corviknight, Cloyster, Kommo-o, Sirfetch'd, Galarian Rapidash — **sem Urshifu** (lendário: regra R1 do `NEXUS_REGRAS.md`) | 1 item grande *(o autor escolhe)* |

**O time da Tilly** (Bug Catcher; apelidos no `trainers.party`). São os insetos que só
existem na horta (§7.1), então ela é o primeiro lugar onde o jogador **vê** um deles:

| Nível da horta | Time |
|---|---|
| 1–2 | Rellor “Mr. Roly”, Combee “Buzzbelle” |
| 3–4 | + Dwebble “Pebbles”, Wurmple “Squiggles” |
| 5 | Rabsca “Mr. Roly”, Vespiquen “Buzzbelle”, Crustle “Pebbles”, Beautifly “Squiggles”, Vivillon “Sprinkles”, Illumise “Twinkle” |

**Falas das batalhas** (abertura · derrota do NPC · depois, se falar de novo no dia):

| NPC | Abertura | Derrota | Já lutou hoje |
|---|---|---|---|
| Tilly | Battle time! My bugs have names, so they're stronger. That's science. | NOOO! Mr. Roly! ...He's fine. He's rolling. He's fine. | Mr. Roly needs a nap. Come back tomorrow! He'll be ready. I'll be READIER. |
| Tilly + Peonia | **Tilly:** Team Mulch! **Peonia:** We are NOT calling it that. **Tilly:** Team Mulch!! | **Peonia:** Okay. We can call it Team Mulch. | **Tilly:** Team Mulch is resting. **Peonia:** Team Mulch is eating all the Pecha. |
| Bugsy | Field test! I want to see how garden-raised bugs do against a real trainer. For science! | Fascinating! They lost, but they lost in a very well-documented way. | I'm still writing up the last one. Twelve pages so far. |
| Avery | The king ignores me. You will not. Behold — a psychic prodigy! | Hmph. I was holding back. Out of courtesy. To the vegetables. | My mind is exhausted. I am resting it. By talking. Leave. |
| Peony | Peony here! Fancy a scrap, chum? Me and Copperajah haven't had a proper one since Galar! | Ha! GRAND! Knocked me flat and I loved every second! | Once a day, chum. Me back's not what it was. Me front neither. |
| Peonia | Dad talks. I battle. Let's go! | ...Okay. You're good. Don't tell Dad I said that. | Rematch tomorrow. I'm writing down everything you did. |
| Mustard | Hmhm! Let's see what the garden taught you! Master Mustard, ready! | Wonderful! Wonderful! My knees hurt, but WONDERFUL! | I've had my fun! Now I'll have my nap. Bram said I can use his chair. |

### 14.6 Estado diário e custos (substitui o daily do §10 e do §13.6)

```c
// FLAG_DAILY_GARDEN_NEW_DAY: 1 flag diaria (DAILY_FLAGS_START + 0x32, hoje FLAG_UNUSED_0x952 do bloco DAILY)
// VAR_GARDEN_TODAY (0x4127): zerada por GardenRollDay quando a flag acima esta limpa
//   bit 0  pedido sorteado          bit 8  lutou com Peony
//   bit 1  pedido entregue          bit 9  lutou com Peonia / dupla
//   bit 2  horta regada (nivel 3)   bit 10 Mustard vem hoje
//   bit 3  Klara vem hoje           bit 11 lutou com Mustard
//   bit 4  Klara resolvida          bit 12 falou com Bram   (coracao)
//   bit 5  lutou com Tilly          bit 13 falou com Laurel (coracao)
//   bit 6  lutou com Bugsy          bit 14 falou com Tilly  (coracao)
//   bit 7  lutou com Avery          bit 15 falou com Peony  (coracao)
// Specials: GardenRollDay, GardenToday_Check / GardenToday_Set (VAR_0x8004 = bit)
```

| Recurso | Qtd | O quê |
|---|---|---|
| Flag diária | **1** (era 5) | `FLAG_DAILY_GARDEN_NEW_DAY` |
| Var | +3 | `VAR_GARDEN_TODAY`, `VAR_GARDEN_HEARTS`, `VAR_GARDEN_RIVALS` (vitórias da Klara; o resto livre) em `0x4127..0x4129` — conferir com a skill `alocar-flag` antes |
| `VAR_HARVEST_KING` | 0..15 | era 0..13 (§14.2) |
| Itens novos | 2 | `ITEM_ICEROOT_CARROT`, `ITEM_SHADEROOT_CARROT` (item-chave) |
| Treinadores | 20 | Tilly ×3, Peonia ×3 (+1 da dupla), Bugsy ×3, Klara ×3, Avery ×3, Peony ×3, Mustard ×1, `TRAINER_HARVEST_KING_TRIAL` ×1 |
| Plaquinhas | +1 | `NAME_MUSTARD` (as outras já estão no §10 e no §13.6) |
| Sprites (o autor providencia) | +1 | Mustard (overworld + front pic); os de Peony, Peonia, Klara e Avery servem também às fichas do Nexus (`.claude/rift_missions/nexus/galar/`) |
| Objetos `Route30_House` | +2 | Peony e Peonia (estados 9–14) |
| C | pequeno | `GardenLine_Pick`, `GardenHearts_Talk`, `GardenRollDay`, `GardenToday_Check/Set`, `EmptyKingsPlot` |
| Texto | ~230 falas | §14.4 + §14.5; `nomear-falante` para medir |

### 14.7 Decisões do autor (rev 3)

| # | Pergunta | Recomendação |
|---|---|---|
| 1 | A escolha pelo **tipo de cenoura** (Crown Tundra) em vez de ir a um dos dois mapas | Sim: a escolha fica explícita e irreversível, e casa com SWSH |
| 2 | Peony e Peonia **hóspedes** até o epílogo, e o Rei falando pelo Peony dormindo | Sim |
| 3 | Prova do Ato 7 com o **time do Peony** tomado pelo Rei, antes do Calyrex | Sim, sem blackout |
| 4 | Corações (5 e 12 dias) liberando as falas mais íntimas | Sim; invisível para o jogador |
| 5 | Laurel em casa no fim de semana (dia de forno) | Sim: resolve o orçamento e varia a rotina |
| 6 | Mustard em pessoa, raro, e sem Urshifu | Sim |
| 7 | Prêmios das batalhas | Leves (adubo, berries do Livro); o autor fecha os itens grandes |

---

## 15. Rev 4 — As dungeons dos corcéis (30/09/2026)

Pedido do autor: **tirar o Will** (a ligação dele com o Calyrex é só do Nexus, não da
lore) e, com liberdade, **propor uma dungeon para o Glastrier e outra para o
Spectrier** em lugares de Johto que existem na lore e **nunca foram representados**
num jogo, ligando a história a eles. **Onde a §15 e as anteriores discordam, vale a
§15.**

**O Will saiu** de tudo: elenco da rev2 (§13.1), tabela de lendários (§13.2) e a fala
dele no epílogo (§13.3). Pryce e Morty ficam porque têm motivo **na história**
(gelo e espíritos), não por causa do Nexus.

### 15.1 A ideia: a canção da Laurel estava certa, a leitura dela não

> *“The white one sleeps where the ice never thaws.
> The black one walks where the fire took the bells.”*

A Laurel sempre achou que era o Ice Path e a Burned Tower. São as pistas
**erradas** — e quem corrige são os dois líderes que entendem de gelo e de espíritos:

| Verso | O que a Laurel acha | O que é de verdade | Lugar da lore, nunca jogável |
|---|---|---|---|
| *where the ice never thaws* | O Ice Path | O Ice Path **derrete toda primavera** (Pryce). O gelo que nunca derrete **não é gelo**: é o **cristal dos Unown** | **Greenfield**, a cidade de Johto coberta de cristal pelos Unown (filme *Spell of the Unown*, 2000) |
| *where the fire took the bells* | A Burned Tower de hoje | O cavalo não anda na ruína: anda **na noite do incêndio**, há 150 anos, quando o fogo derreteu os sinos da **Torre de Bronze** | **A Torre de Bronze intacta, na noite em que queimou** — a lenda de Ecruteak (os três Pokémon que morreram e o Ho-Oh reviveu) que os jogos só contam, nunca mostram |

Cada dungeon responde por que o corcel é do jeito que é:

- **Glastrier é orgulhoso e frio.** Esquecido pelo rei, quis **nunca mais ser
  esquecido**. Os Unown fazem o que se deseja com força (o filme inteiro é isso): deram
  a ele um castelo de cristal onde **nada muda nem se perde**. Greenfield parou no
  tempo junto.
- **Spectrier é solitário e é Fantasma.** Fugiu de uma Galar que esqueceu o rei,
  atravessou o mar e foi acolhido nos estábulos da Torre de Bronze por um sábio que o
  alimentava toda noite. No incêndio, o Ho-Oh reviveu os três Pokémon **desta terra**
  e passou por cima do cavalo estrangeiro. Ele sobreviveu, mas **ficou naquela noite**
  — por isso é Fantasma, e por isso volta a ela toda madrugada, procurando quem o
  alimentava.

### 15.2 Como o jogador chega (substitui o §8.11 e o Ato 6 do §14.2)

O fim do Ato 5 continua igual, com uma linha a mais da Laurel:

> **Laurel:** Ice that never thaws. I always took that for the Ice Path. Ask the old
> man in Mahogany. He knows ice better than I know Berries.
> Where the fire took the bells. The tower in Ecruteak. Ask the boy who sees things.

O Pryce **no ginásio de Mahogany** (Iceroot na bolsa) e o Morty **no ginásio de
Ecruteak** (Shaderoot na bolsa) viram o gatilho da dungeon. Com a cenoura errada,
ou sem cenoura, cada um diz uma linha de gancho e nada mais.

> **Pryce:** Iceroot. My mother fed it to the Mamoswine in the worst winters.
> ...The Ice Path? Child, the Ice Path thaws every spring. I've watched it for fifty
> years.
> Ice that never thaws isn't ice. There's a town west of the Ruins of Alph. Greenfield.
> The Unown covered it in crystal, once, when I was younger. It went away.
> Last winter, it came back.
> I went there, the first time. A little girl asked me to stay for dinner. I didn't.
> I have regretted few things in my life. That is one of them.
> Go. And if she's still there, tell her the old man from Mahogany says good evening.

> **Morty:** Shaderoot. The spirits in my tower like the smell. So does he.
> You won't find him in the ruin. He doesn't walk in what the tower is. He walks in
> what it was, on the night it burned.
> There's only one way into a memory that old. The Kimono Girls dance it every year,
> on the anniversary. Tonight, they'll dance it for you.
> Come to the Dance Theater after dark. Bring your carrot. Bring your courage.

### 15.3 Caminho branco — Greenfield, o prado de cristal

**Lugar.** Greenfield, cidade de flores a oeste das Ruins of Alph. No filme, os Unown
cobriram a casa do Professor **Spencer Hale** (que estudava os Unown e sumiu na
dimensão deles) e a cidade em cristal, a pedido da filha, **Molly**. O cristal se
desfez. **Voltou no inverno passado** — quando o Glastrier chegou.

**Entrada.** Um portão novo na borda oeste de `RuinsOfAlph_Outside` (medir com
`mapa-de-ligacoes` e `dump_mapa.py`). Abre no estado 10 (Iceroot plantada); antes,
um cientista do laboratório de Alph bloqueia: *“The crystal's spreading. Nobody goes
west until we know why.”* Os cientistas do `RuinsOfAlph_Lab` ganham falas sobre o
Professor Hale (eles o conheciam: Alph + Unown).

**Quem está lá.**

| Personagem | Quem é | Sprite |
|---|---|---|
| **Molly Hale** | A menina do filme, agora adulta (uns 20 anos depois). Mora sozinha na mansão, cuidando da cidade parada. Gentil, cansada, um pouco culpada: acha que o cristal voltou por causa dela | novo (o autor providencia); substituto `WOMAN_2` |
| **Pryce** | Chega depois do chefe, se o jogador levou o recado (abaixo) | `PRYCE` |
| **Peonia** | Acompanha (§13.3) | substituto `PICNICKER` |
| **As notas do Professor Hale** | 5 páginas espalhadas pela dungeon (`bg_event`), contam a lore em pedaços | — |

**Os mapas** (5 novos):

| # | Mapa | O que tem | Mecânica | Tileset |
|---|---|---|---|---|
| G1 | **Greenfield** (fora) | A cidade de flores sob cristal: casas, fonte, a mansão ao fundo. 3 moradores “parados” (falam, mas repetem a mesma frase: estão presos no mesmo dia) | Nenhuma; é o choque visual | `johto_general` + secundário novo `Greenfield` (flores + cristal; `montar-tileset`) |
| G2 | **Mansão Hale — saguão** | Molly; o piano; a nota 1 | Cena | interior + paleta de cristal |
| G3 | **Jardim de Cristal** | Flores presas no cristal; a nota 2 | **Deslizar no cristal** (a mecânica do Ice Path, `MB_SLIDE_*`), com as flores de cristal como paradas | `cave_ice` com paleta nova |
| G4 | **Biblioteca das Letras** | Estantes, Unown nas paredes; as notas 3 e 4 | **Palavra dos Unown**: pisar nas letras do chão na ordem da palavra certa (a pista está nas notas). Errou, o chão reseta | `ruins_of_alph_writing` + cristal |
| G5 | **O Trono de Gelo** | O salão onde o Glastrier dorme; a nota 5 | Chefe | cristal |

**A palavra do G4 é `REMEMBER`.** A nota 4 do Hale: *“The Unown answer the strongest
wish in the room. This one isn't a child's. It's older, and prouder. It wishes to be
REMEMBERED.”* Soletrar `REMEMBER` abre o salão: o jogador “lembra” o Glastrier, e o
cristal deixa passar.

**Encontros selvagens** (G3–G4): Unown, Snorunt, Bergmite, Cryogonal, Snom, Glimmet,
Sneasel. Nenhum lendário, nenhum exclusivo da horta.

**Treinadores** (uma vez cada): 2 Scientists do laboratório de Alph (vieram estudar e
ficaram presos no “mesmo dia”), 1 Psychic que ouve os Unown, 1 Skier/Ruin Maniac de
Mahogany que veio atrás de rumores. Times de gelo/psíquico, nível da região.

**As notas do Professor Hale** (narração, sem plaquinha; `bg_event`, lidas quantas
vezes quiser):

1. *“Day 1. The Unown are back. Not angry. Waiting. For what, I can't tell.”*
2. *“The flowers stopped growing and never died. Nothing here ages. Molly says it's
   pretty. It is. That's what frightens me.”*
3. *“Something large sleeps at the heart of the crystal. Its breath frosts the pages as
   I write. It dreams of a rider.”*
4. *“The Unown answer the strongest wish in the room. This one isn't a child's. It's
   older, and prouder. It wishes to be REMEMBERED.”*
5. *“If you are reading this, you came for it. Be kind. Everyone who ever loved it
   left.”*

**Cenas.**

*Entrada em G1, primeira vez:*

> **Peonia:** It's... it's all glass. The flowers are glass. The FOUNTAIN is glass.
> Freezington's colder, though. ...Okay, it isn't.

*G2, Molly ao piano (ela para de tocar ao ouvir o jogador):*

> **Molly:** Oh. A visitor. We don't get visitors. We don't get anything. That's the
> point, I think.
> When I was little, I wished for a family, and the Unown made one out of crystal.
> I thought I'd done it again. I didn't. I checked. I'm not wishing for anything.
> Something else is. Something in the heart of the house.
> It isn't cruel. It's just... afraid of being forgotten. I know that feeling.
> My father's notes are all over the house. He'd know what to do. He always did, and
> then he got lost.

*Se o jogador tem o recado do Pryce:*

> **Molly:** The old man from Mahogany? ...He never came to dinner.
> Tell him the invitation stands.

*G5, o chefe.* O Glastrier dorme sobre um estrado de cristal. Ao se aproximar, os
Unown do salão se juntam (flash com `fadescreenswapbuffers`) numa **aparição de
cristal do Calyrex montado no Glastrier** — o que o corcel sonha.

> **???:** ...Do you remember me? No one remembers me. Then no one will pass.

*Batalha 1 — **Phantom Rider*** (treinador `TRAINER_CRYSTAL_RIDER`, plaquinha “???”, sem
blackout): Unown ×2, Glalie, Cryogonal e um Avalugg com o apelido “Glastrier?”, o
corcel falso que os Unown montaram. Vitória: a aparição se desfaz em letras.

> *(narração)* The Unown scatter like snow. The great horse opens one eye.
> *(o jogador oferece a Iceroot Carrot; `playmoncry SPECIES_GLASTRIER`)*
> *(narração)* It knows the smell. It knew it before it knew you.

*Batalha 2 — Glastrier* (encontro fixo; `seteventmon`; retry do §8.1). **Capturado:**
`removeitem` da cenoura, estado 12.

*Depois* (fade): o cristal racha. Ao sair, **Greenfield volta a ter cor** (layout
alternativo ou paleta por estado ≥ 12 no `ON_LOAD`; os 3 moradores “parados” ganham
falas novas: o dia deles andou).

> **Molly:** It's melting. Everything's melting. The flowers are — they're growing.
> ...I'd forgotten flowers do that.
> Here. Papa kept this on his desk. He said it was ice that never melted, and that
> it was the only thing in the house that never changed. It should go with the horse.

*Dá **Never-Melt Ice** (`checkitemspace` antes).* Se o jogador passar em Mahogany
depois, o Pryce ganha uma linha:

> **Pryce:** ...She said the invitation stands? Hm. I'll need a better coat.

E, dali em diante, o Pryce **aparece na mansão** aos domingos à noite (objeto por dia da
semana, como a rotina da horta): jantando com a Molly. Nenhuma fala longa; é a
recompensa emocional.

**Gancho (não faz parte desta proposta):** a nota escondida do Hale, no fundo do G4,
*“The Unown's world has doors. I found one. I'm going through.”* — o Professor Hale
perdido na dimensão dos Unown pode virar um evento das Rift Missions depois.

### 15.4 Caminho escuro — a Torre de Bronze, na noite do incêndio

**Lugar.** A lenda de Ecruteak (GSC/HGSS): há 150 anos a **Torre de Bronze** pegou fogo
com um raio e queimou por três dias; três Pokémon sem nome morreram e o Ho-Oh os
reviveu como Raikou, Entei e Suicune; os sinos da torre derreteram. Os jogos só
mostram a ruína. Aqui o jogador **entra na noite em que ela queimou** — uma memória,
não uma viagem no tempo.

**Entrada.** O Morty e as Kimono Girls fazem a **Dança da Torre de Bronze** no
`EcruteakCity_Theater`, à noite, com a Shaderoot na bolsa (estado 11). Cada uma das
cinco dança com uma fita de cor; a ordem das cores **é a pista do puzzle dos sinos**
(S3). Tela em sépia (paleta cinza por `fadescreenswapbuffers` + `setweather` de
cinzas, ou paleta fixa nos mapas da memória) e warp para S1.

**Quem está lá.**

| Personagem | Quem é | Sprite |
|---|---|---|
| **Morty** | Guia a dança; no fim, puxa o jogador de volta | `MORTY` |
| **Eusine** | Já existe no `BurnedTower_1F` (caçador do Suicune). Convencido de que o cavalo negro é “**a quarta fera**” da torre. Entra na memória junto, atrapalha, e sai humilde | `EUSINE` |
| **Kimono Girls** | As cinco do teatro (`EcruteakCity_Theater`); a dança | `KIMONO_GIRL` |
| **Os Sábios de 150 anos atrás** | Memórias; tratam o jogador como noviço. São os antepassados dos Sábios do `EcruteakCity_SageOffice` | `SAGE` (paleta cinza) |
| **Sábio Tomo** | O sábio que alimentava o cavalo toda noite. Chefe do meio. Em Ecruteak de hoje, uma lápide com o nome dele no quintal do Sage Office (`bg_event` novo) | `SAGE` |
| **Peonia** | Entra junto, com medo (§13.3) | substituto |

**Os mapas** (4 novos, todos “memória”; a saída é sempre o `BurnedTower_B1F` de hoje):

| # | Mapa | O que tem | Mecânica | Tileset |
|---|---|---|---|---|
| S1 | **Torre de Bronze — 1F, entardecer** | A torre **intacta**, Sábios fazendo a ronda, lanternas. Nota: o estábulo lá fora | Nenhuma; conversar. O jogador vê o que a Burned Tower **era** | secundário novo `BrassTower` a partir de `burned_tower` (as peças queimadas repintadas inteiras; `montar-tileset`) |
| S2 | **2F — o raio** | Trovão ao entrar (flash + `playse`), o fogo começa | **Fogo que avança**: a cada N passos um special troca metatiles de chão por fogo (`setmetatile` + `special DrawWholeMapView`) atrás do jogador. Encurralado → *“The memory folds back.”* e volta ao começo do andar, sem perda | `BrassTower` + metatiles de fogo |
| S3 | **3F — os sinos** | Cinco sinos pendurados | **Tocar os sinos na ordem das fitas da dança.** Cada sino tocado **derrete** (setmetatile) — “o fogo levou os sinos”. Ordem errada: os que sobraram tocam sozinhos, e reseta | `BrassTower` |
| S4 | **Telhado e estábulo** | O céu em chamas; o Sábio Tomo guardando o cavalo; a sombra do Ho-Oh | Chefe do meio + chefe | `BrassTower` + noite |

**Encontros selvagens** (S1–S3, “memórias de Pokémon”): Gastly, Misdreavus, Litwick,
Sinistea, Phantump, Houndour (Ecruteak antiga). Nada que não exista hoje na região.

**Treinadores** (uma vez cada): 3 Sábios-memória (classe `SAGE`, times de Bellsprout/
fantasma, como na Sprout Tower) e 1 Kimono Girl-memória no S3 — a avó de uma das
dançarinas de hoje. Ao vencer, eles “somem em fumaça” (`removeobject` + `FLAG_TEMP`).

**Cenas.**

*Teatro, antes da dança:*

> **Morty:** Stand in the middle. Don't move until the last ribbon falls.
> When you're inside, remember: nothing there can hurt you. But it can keep you.
>
> **Eusine:** Wait! Morty! I heard everything through the door!
> A black beast, in the Brass Tower, on the night of the fire? A FOURTH beast?!
> I'm coming. Don't argue. I've waited my whole life for a fourth beast.

*S1, um Sábio-memória (rodízio de 5 falas entre os Sábios):*

> **Sage:** New novice? Sweep the third floor, then feed the black horse in the stable.
> Brother Tomo spoils it. It came from over the sea, they say. It won't eat anything
> but what Tomo gives it.

*S2, o raio:*

> *(narração)* Thunder. Then light. Then the smell of smoke.
> **Eusine:** It's happening! Exactly like the scrolls! ...Why is it so HOT? The scrolls
> didn't say it was hot!

*S3, depois do último sino derreter:*

> *(narração)* The last bell melts before it finishes ringing. Somewhere below, three
> great voices cry out, and then fall silent.

*S4, o Sábio Tomo diante do estábulo em chamas (batalha 1, `TRAINER_SAGE_TOMO`, sem
blackout; Gengar, Houndoom, Mismagius, Chandelure, Bellossom):*

> **Tomo:** Stay back! No one takes him. He came to us with nothing, from a land that
> forgot his name. I won't let this one forget him too.
>
> *(vitória)* **Tomo:** ...You carry a Shaderoot. That's his food. From his home.
> Then you came from his king.
> I fed him every night for eleven years. Tell him... tell him the old monk says he
> can stop waiting.
> *(o Tomo some em fumaça)*

*A sombra do Ho-Oh passa (objeto grande, `walk_fast` pela tela, ou só o flash
arco-íris com `setflashlevel`) — e não para no estábulo.*

> **Morty:** *(voz, sem objeto: é a visão dele)* There. You see? It revived the three
> of this land. It passed him by. He's been standing in that night ever since.
>
> **Eusine:** ...Not a fourth beast. Just a horse nobody came back for.
> I think I'll stop calling him a beast.

*Batalha 2 — Spectrier* (encontro fixo; retry do §8.1). **Capturado:** `removeitem`
da cenoura, estado 13, fade para o `BurnedTower_B1F` de hoje.

> **Morty:** Welcome back. You were gone for three minutes. It felt longer, didn't it?
> The tower's quieter now. For the first time since I was a boy, it's quiet.

*Dá **Spell Tag** (`checkitemspace` antes).* E, no quintal do `EcruteakCity_SageOffice1`,
a lápide nova:

> *(bg_event)* “Brother Tomo. He fed the ones who had nowhere else to go.”
> *(com o Spectrier na party, uma linha a mais)* Your Spectrier lowers its head.

**O Eusine depois:** passa a ter uma fala nova no `BurnedTower_1F` — *“I've been
reading the scrolls again. They never mention the horse. I'm going to write it in
myself.”* — e o gancho dele com o Suicune continua como está.

### 15.5 O que muda no resto

| Onde | Muda |
|---|---|
| §8.11 e §14.2 (Ato 6) | `IcePath_Depths` e `BurnedTower_B1F` deixam de ter corcel. O Pryce e o Morty saem desses mapas e ficam nos **ginásios** (gatilho da dungeon) |
| §13.3 (Peonia no Ato 6) | Ela espera na **entrada de Greenfield** ou **no teatro**, com as falas que já tem |
| §14.2, tabela de estados | Estados 10 → 12 e 11 → 13 passam por Greenfield e pela Torre de Bronze |
| Retry | Mesmo do §8.1. Sair da memória (Spectrier) ou de Greenfield no meio **não** perde o progresso dos puzzles: `VAR_HARVEST_DUNGEON` guarda até onde o jogador chegou (só uma dungeon por jogo, então uma var serve às duas) |
| O corcel não escolhido | Greenfield (com Spectrier escolhido): a cidade existe, a mansão está trancada pelo cristal — *“Something inside is waiting for someone else.”* O teatro (com Glastrier escolhido): as Kimono Girls não dançam a Torre de Bronze. O outro corcel continua só no Nexus |
| `IcePath_Depths2` | Nada: o Chien-Pao continua lá |

### 15.6 Outros lugares de Johto que a lore tem e o jogo não (para depois)

Não entram nesta proposta; ficam anotados porque combinam com o mesmo jeito de
contar (um lugar da lore, um lendário sem fonte, um personagem que já existe):

| Lugar | De onde | Combina com |
|---|---|---|
| **Arborville** e a floresta do tempo | filme *Celebi: Voice of the Forest* (Johto) | Ilex Forest, o Celebi que já existe no Ilex |
| **Alto Mare**, a cidade dos canais | filme *Pokémon Heroes* (Johto) | Latias/Latios, se não tiverem fonte |
| **Charicific Valley**, o santuário dos Charizard | anime, Johto | Blackthorn/Dragon's Den |
| **Sinjoh Ruins** | HGSS (evento do Arceus) | Ruins of Alph, Mt. Silver |
| **A dimensão dos Unown** e o Professor Hale | filme *Spell of the Unown* | Rift Missions (gancho da nota escondida do §15.3) |

### 15.7 Custos (a mais)

| Recurso | Qtd |
|---|---|
| Mapas novos | **9**: Greenfield + mansão + 3 salas (G1–G5); Torre de Bronze 1F, 2F, 3F, telhado (S1–S4) |
| Tilesets | 3 secundários: `Greenfield` (flores + cristal), cristal interior (paleta do `cave_ice`), `BrassTower` (a partir do `burned_tower`) — `montar-tileset` e `adicionar-tileset` |
| Ligação | 1 portão novo em `RuinsOfAlph_Outside`; os mapas da memória só se ligam pelo teatro e pelo `BurnedTower_B1F` (conferir com `mapa-de-ligacoes`) |
| Var | +1: `VAR_HARVEST_DUNGEON` (progresso da dungeon escolhida) |
| Treinadores | 10: 4 em Greenfield + `TRAINER_CRYSTAL_RIDER`; 4 na torre + `TRAINER_SAGE_TOMO` |
| Sprite (o autor providencia) | Molly Hale adulta (overworld); o resto reaproveita (`PRYCE`, `MORTY`, `EUSINE`, `KIMONO_GIRL`, `SAGE`) |
| Plaquinhas | +3: `NAME_MOLLY`, `NAME_EUSINE` (conferir se já existe), `NAME_TOMO` |
| C | special de fogo que avança (S2), puzzle das letras (G4) e dos sinos (S3) por script com `VAR_TEMP` |
| Itens | nenhum novo (Never-Melt Ice e Spell Tag existem) |

### 15.8 Decisões do autor (rev 4)

| # | Pergunta | Recomendação |
|---|---|---|
| 1 | Greenfield e a Molly (do filme) como o lugar do Glastrier | Sim: é Johto, tem “gelo” que nunca derrete, e os Unown já existem no jogo |
| 2 | A noite do incêndio da Torre de Bronze como o lugar do Spectrier | Sim: explica por que ele é Fantasma e por que é solitário |
| 3 | Entrar na memória pela dança das Kimono Girls, sem viagem no tempo | Sim: não depende do Celebi nem abre paradoxo |
| 4 | Pryce jantando com a Molly aos domingos depois | Sim, pequeno e bonito |
| 5 | O Professor Hale perdido na dimensão dos Unown como gancho | Só anotado, para as Rift Missions |
| 6 | Tamanho: 9 mapas e 3 tilesets | É o maior custo da sidequest; dá para cortar G3 e S2 (as salas de mecânica) e manter a história inteira |
