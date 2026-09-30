# O Rei da Colheita — a horta do Berry Master, completa

> **Proposta rev1 — 30/09/2026.** Nada implementado. Junta num sistema só a
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
