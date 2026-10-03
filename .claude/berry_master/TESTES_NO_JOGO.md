# Berry Master — testes no jogo, em ordem (Partes 1 a 12)

> Roteiro único para rodar **de cima para baixo**. Cada teste parte do estado que o
> anterior deixou, então não pule nenhum sem ler o “Estado ao fim”. Cada um diz qual
> parte do `PLANO_DE_IMPLEMENTACAO.md` ele verifica.
>
> Escrito em 30/09/2026 contra o commit que traz o menu de debug. As falas citadas são
> as do código; se uma fala sair diferente, isso já é um achado.

---

## 0. Antes de começar

**Build.** `make -j$(nproc)` (o de desenvolvimento). O `make release` **não tem** o menu
de debug. Rodar no mGBA patchado (`tools/mgba-master`).

**Save.** Qualquer save que já passou da introdução, com o **relógio configurado** (sem
relógio o jogo não conta os dias e metade destes testes não acontece). Não precisa estar
na Route 30.

**Menu de debug.** No campo, **segure L e aperte START**. Os caminhos abaixo são escritos
assim: `Berry Master… → Clock… → +24 hours`.

**Savestate.** Faça um savestate no mGBA antes de cada bloco (A, B, C…). Se um teste
falhar, você volta ao começo do bloco em vez do começo do roteiro.

**A oferta de reforma aparece sozinha.** Com o Livro em 12 ou mais, a cada **visita nova**
à casa (inclusive depois de um teleporte ou de uma opção do `Clock…`, que recarregam o
mapa) o Bram oferece a próxima reforma. Nos blocos A a E, responda **No** (“Suit
yourself. The offer keeps.”); ela só é o assunto no bloco F.

**Desde a Parte 8 o Bram muda de lugar com a hora** (relógio do jogo): de **manhã
(6–10)** ele está na **horta**, em (27,44), logo acima de onde o `Go: the garden` te
deixa; de **dia (10–19)** em casa; de **noite (19–6)** dorme à mesa e não dá nada (quem
entrega o presente é a Laurel). Os blocos A a F dizem “fale com o Bram na casa”: faça-os
**de dia**, ou fale com ele onde ele estiver — a conversa é a mesma nos dois lugares.
Depois de `Next morning, 7:00`, ele está na **horta**. O tutorial (T02) é a exceção:
antes dele o Bram fica em casa a qualquer hora.

**Relógio: `+24 hours` × `Next morning, 7:00`.** O `+24 hours` sempre vira o dia. O
`Next morning, 7:00` vai para a **próxima** 7:00, que pode ser a de hoje se ainda não deu
7h — e aí **não** vira o dia. Quando o teste precisa de dia novo, ele diz `+24 hours`.

**Números úteis** (para `Give X… → Give item XYZ…`, onde você escolhe o item pelo número):

| Item | Número |
|---|---|
| Squirtbottle (regador) | 722 |
| Cheri Berry | 514 |
| Chesto Berry | 515 |
| Leppa Berry | 519 |
| Oran Berry | 520 |
| Lum Berry | 522 |
| Sitrus Berry | 523 |
| Micle Berry | 575 |
| Custap Berry | 576 |

**Onde fica cada coisa** (x cresce para a direita, y para baixo):

| O quê | Onde |
|---|---|
| Canteiro A (6 covas) | Route 30, (28..30, 43..44) — à direita e abaixo da porta da casa |
| Canteiro B (4 covas) | Route 30, (30..31, 41..42) — logo acima do A, colado no lago |
| Canteiro da Laurel | Route 30, (23,38) — à esquerda da casa |
| Onde o teleporte “Go: the garden” te deixa | Route 30, (27,45) — à esquerda do A |
| Bram | manhã: horta (27,44); dia: casa (4,4); noite: casa (4,4), dormindo |
| Laurel | casa (3,4); dia de semana à tarde: horta (27,43) |
| Tilly (sáb e dom) | manhã: casa, cadeira azul (7,5); tarde: banquinha na horta (24,41) |
| Bugsy (ter e qui, Ato 1 feito) | tarde: horta (29,41) |
| Sunflora | casa, sob a janela (6,2) |
| Laurel | dentro da casa, (3,4) |

**Tela de Status** (`Berry Master… → Status`), três páginas:
1. `Level L   Work W` / `Planted garden plots: N/10`
2. `Book B/67   Paid P` / `Milestone owed: M`
3. `Hour H   Today bits T` / `Harvest King state: S`
e por fim `Bram's gift: taken today.` ou `…still waiting today.` e a linha do pedido:
`Order: none drawn today.`, `Order: 3 Cheri Berries, open.`, `Order: DISCOVERY Aguav
Berry, open.` ou `Order: … delivered.`

`Work`: 0 = nenhuma obra; 2, 3 ou 4 = obra paga daquele nível, fica pronta amanhã;
12, 13 ou 14 = pronta, o Bram ainda não falou dela.
`Today bits`: número que soma as marcas do dia: 1 = pedido sorteado, 2 = pedido entregue,
4 = canal regou hoje.

---

## Bloco A — Começo limpo e tutorial do Bram (Partes 2 e 3)

### T01 · Reset do Berry Master (menu de debug) - OK
- **Passos:** `Berry Master… → Reset Berry Master` → **Yes**.
- **Esperado:** “Berry Master reset. Bram will give the tutorial again.” e o mapa
  recarrega no mesmo lugar.
- **Se falhar:** anote a mensagem e onde você estava.

### T02 · Status zerado ok
- **Passos:** `Berry Master… → Status`.
- **Esperado:** `Level 0   Work 0`, `Planted garden plots: 0/10`, `Book 0/67   Paid 0`,
  `Milestone owed: 0`, `Harvest King state: 0`, `Bram's gift: still waiting today.`

### T03 · A horta antes do tutorial (Parte 2) ok
- **Passos:** `Berry Master… → Go: the garden`. Olhe em volta.
- **Esperado:**
  - Canteiro A: 6 covas de **terra redonda**, iguais à cova da Laurel, em 2 linhas de 3,
    à sua direita. **Não** podem ser blocos rosa (bug 1, corrigido em 02/10/2026).
  - Canteiro B: **grama comum** (nada de terra) acima do A, perto do lago.
  - Em (23,38), à esquerda da casa: uma cova de terra, **sem planta**.
  - **Não existe mais** o Weedle decorativo que ficava parado em (19,42), na beira da
    mata a oeste do caminho que desce da casa.
- **Se falhar:** screenshot da área.

### T04 · Canteiro B trancado dá para andar (Parte 2) ok
- **Passos:** ande por cima das 4 casas do B (30..31, 41..42) e aperte A olhando para elas.
- **Esperado:** você anda por cima normalmente; apertar A não mostra nada (nem “plantar?”).

### T05 · Canteiro da Laurel trancado (Parte 2)  ok
- **Passos:** fique ao lado de (23,38) (por exemplo em (23,39), abaixo dele), olhe para
  ele e aperte A. Tente andar para cima dele.
- **Esperado:** “The soil here is hard and cold. / Nothing's grown in it for a long
  time.” **Não** pergunta se quer plantar. Não dá para andar em cima.

### T06 · Canteiro A funciona antes do tutorial (Parte 2 pl)
- **Passos:** olhe para uma cova do A e aperte A.
- **Esperado:** “It's soft, loamy soil.” (ou “…Want to plant a Berry?” se você já tiver
  alguma berry). O canteiro A é aberto desde sempre, de propósito. Tente **andar para
  cima** de uma cova: não dá (são bloqueio, como toda árvore de berry).

### T07 · Tutorial do Bram (Partes 2 e 3) ok
- **Passos:** `Berry Master… → Go: Bram's house`. Fale com o **Bram** (o careca, em (4,4)).
- **Esperado, nesta ordem, sem a caixa fechar e reabrir no meio:**
  1. “When you follow that path up north… tell you about Berries! … Here. I'll share one
     with you!” → recebe **1 Cheri Berry**.
  2. “One more thing. Every Berry you pick yourself goes in the Book. / Off my trees, off
     any tree on any road. Buying one doesn't count. / I don't hand out what I don't grow,
     sprout. And I only grow what's in the Book. / Get it in the Book and I'll have seed
     for you by morning.”
  3. “And since you're here, take two more. / There's always more tomorrow.” (e **não**
     “You came back!”) → recebe **2 berries**, cada uma entre Cheri, Chesto, Pecha,
     Rawst, Aspear, Leppa, Oran e Persim.
  4. “And don't eat both of them. Plant one. …”
- **Se falhar:** anote qual fala veio fora de ordem ou qual berry veio fora das 8.

### T08 · Presente é um por dia (Parte 3) ok
- **Passos:** fale com o Bram de novo.
- **Esperado:** nenhuma berry; ele diz a fala do dia (banco B à tarde, banco A de manhã
  na horta — desde a Parte 9 no lugar de “That's your two for today…”).

### T09 · Status depois do tutorial (Partes 2 e 3) OK
- **Passos:** `Berry Master… → Status`.
- **Esperado:** `Level 1`, `Book 8/67`, `Bram's gift: taken today.`

### T10 · Laurel antes da Liga (Parte 3)  OK
- **Passos:** fale com a **Laurel** (em (3,4), ao lado do Bram).
- **Esperado:** “My husband hands out the easy ones. / I keep the others. …” e nada mais.

**Estado ao fim do bloco A:** tutorial feito, nível 1, Livro 8, presente de hoje já pego.

---

## Bloco B — A horta física (Parte 2)

### T11 · Plantar, regar e colher no A ok
- **Passos:**
  1. `Give X… → Give item XYZ… → 722` (Squirtbottle), se você não tiver.
  2. `Go: the garden`. Plante a Cheri numa cova do A.
  3. Use a Squirtbottle na mesma cova.
  4. `Berry Master… → Ripen the garden`. Colha.
- **Esperado:** plantar, regar e colher funcionam como numa árvore de rota. Na colheita,
  “You found N Cheri Berries!” e elas vão para a bolsa. `Status` antes de colher:
  `Planted garden plots: 1/10`.

### T11b · Terra molhada (bug 2, 02/10/2026) ij
- **Passos:**
  1. Plante uma berry no A. Olhe a cova: terra **clara**.
  2. Use a Squirtbottle nela.
  3. `Berry Master… → Grow garden 1 stage`.
  4. Regue de novo. Depois `Ripen the garden`.
  5. Salve, feche, abra e continue (com a cova molhada).
- **Esperado:** no passo 2 a terra fica **escura** (molhada) assim que a caixa “watered
  the …” **fecha**; enquanto a fala está aberta ela ainda aparece clara. No passo 3, estágio
  novo, ela volta a ficar **clara** (secou: cada estágio pede uma regada, como sempre foi
  a regra). No passo 4, escura de novo; madura, clara. No passo 5, continua como estava.
  As covas vazias, a da Laurel e as de outras rotas fora desta lista não mudam nunca.
- **Onde vale:** mapas com o tileset secundário de Cherrygrove (Route 30, Cherrygrove,
  Route 31, Route 46 e a frente do Mt. Moon), em árvore sobre a terra de berry comum.

### T12 · A trava do B sobrevive a menu, batalha e save (Parte 2) ok
- **Passos:**
  1. Na Route 30, perto da horta, abra e feche a bolsa.
  2. Ande na grama alta até uma batalha selvagem; fuja.
  3. Salve o jogo pelo menu do jogo, feche o mGBA, abra e continue.
- **Esperado:** nos três casos o B continua **grama**, andável.
- **Se falhar:** diga em qual dos três passos a terra do B apareceu.

### T13 · Nível 2 abre o B (Parte 2) ok 
- **Passos:** `Berry Master… → Garden level… → 2 Proper Garden`.
- **Esperado:** “Garden level 2; works cleared.”, o mapa recarrega, e o B vira **4 covas
  de terra** (não dá mais para andar em cima). Olhe uma cova do B: “It's soft, loamy soil.”
- Plante qualquer berry numa cova do B.

### T14 · Voltar ao nível 1 esconde o B sem perder o que foi plantado (Parte 2) ok
- **Passos:** `Garden level… → 1 Backyard Plot`. Depois `Garden level… → 2 Proper Garden`.
- **Esperado:** no nível 1 o B volta a ser grama (a planta some da vista). No nível 2 a
  planta **reaparece** no mesmo lugar e no mesmo estágio.

### T15 · Árvores de fora da horta continuam iguais (Parte 2, regressão) ok
- **Passos:**
  1. Na Route 30, árvore de Pecha em (30,4) (norte da rota, perto da casa do Mr. Pokémon):
     colher se estiver madura.
  2. Vá ao **WorldHub** (pela casa do jogador em New Bark). Na horta de árvores dele, a
     árvore em (4,31) é **Oran**: colha.
- **Esperado:** as duas funcionam como antes. A Oran do WorldHub dá **Oran** e, depois
  de colhida, volta sozinha com o tempo (`Clock… → +24 hours` e olhe de novo).
- **Atenção:** no QA de 03/10/2026 a Oran nunca aparecia (16 slots de objeto cheios).
  Desde então o limite é 24 e os NPCs do WorldHub foram afastados do pomar: a Oran e as
  outras 15 árvores devem aparecer chegando por qualquer lado (`objetos.py` lista todas).
- **Por que importa:** antes da Parte 2 a Oran do WorldHub e a árvore de (23,38) dividiam
  a mesma vaga do save; agora são separadas.

**Estado ao fim do bloco B:** nível 2, com alguma planta no A e no B.
Volte para o nível 1 para o bloco C: `Garden level… → 1 Backyard Plot`.

---

## Bloco C — Livro de Berries (Parte 3)

### T16 · Colher registra no Livro
- **Passos:** `Status` (anote o Livro: 8). No **WorldHub**, colha a **Sitrus** em (7,31)
  (se não estiver madura: `Clock… → +24 hours`). `Status` de novo.
- **Esperado:** `Book 9/67`.

### T17 · Colheita que não cabe na bolsa não registra
- **Passos:**
  1. `Book of Berries… → Bram's 8 only` (Livro 8, sem Sitrus).
  2. `PC/Bag… → Clear Bag`, depois `PC/Bag… → Fill Pocket Berries` (999 de cada berry).
     O Clear Bag vem antes porque o Fill só cria pilhas das berries que você **ainda não
     tem**: uma pilha que já existe (ex.: as Sitrus colhidas no T16) fica como está, e a
     colheita cabe nela.
  3. Plante uma Sitrus no A, `Ripen the garden`, colha.
  4. `Status`.
- **Esperado:** “The Bag's Berries Pocket is full. / The Sitrus Berry couldn't be taken.” e
  o Livro **continua 8**.
- **Observação:** se a colheita for de só 1 berry, ela cabe (998 + 1). Nesse caso,
  plante de novo e repita.
- Depois: `PC/Bag… → Clear Bag` e dê de novo a Squirtbottle (722) (o Clear Bag do passo 2
  também a levou).

### T18 · Com 11 no Livro, nenhum marco
- **Passos:** `Book of Berries… → 11`. `Go: Bram's house`, fale com o Bram.
- **Esperado:** nenhum prêmio. Só o presente do dia (se o dia virou em algum teste
  anterior) ou a fala do dia (se não virou).

### T19 · Marco 12 (e a oferta de reforma junto)
- **Passos:** `Book of Berries… → 12 (level 2)`. Fale com o Bram.
- **Esperado, em ordem:**
  1. “Let me see that Book of yours... / 12 Berries! You're getting the hang of this,
     sprout. / Here. Something for the garden.” → recebe **5 Growth Mulch**.
  2. O presente do dia, ou a fala do dia.
  3. **Por último**, a caixa de dinheiro aparece e ele oferece a reforma: “12 Berries in
     your Book now. Time this was a proper garden. / Four more beds by the pond, dug by
     morning. ¥5,000 for the lot. Shall I?” → responda **No** → “Suit yourself. The offer
     keeps.” e a conversa acaba. (O número é o tamanho do **Livro**, nunca o dinheiro —
     bug 3, corrigido.)
- Fale com ele **de novo na mesma visita**.
- **Esperado:** nem o marco nem a oferta se repetem.

### T20 · Vários marcos atrasados saem em ordem
- **Passos:** `Book of Berries… → 32`. Saia da casa e entre de novo. Fale com o Bram.
- **Esperado:** dois prêmios na mesma conversa, nesta ordem: **20** → 3 Rich Mulch;
  **30** → 3 Surprise Mulch (o 32 não é marco; o próximo é 40). Depois o presente (ou
  “That's your two…”) e, no fim, a oferta de reforma (responda **No**). `Status`: `Paid 30`.

### T21 · Marco com a bolsa cheia não se perde
- **Passos:**
  1. `Book of Berries… → 60 (last milestone)`.
  2. `PC/Bag… → Fill Pocket Items` (999 de cada item comum, adubos incluídos).
  3. Fale com o Bram.
- **Esperado:** “Let me see that Book of yours... / 40 Berries!…” e em seguida “Your Bag's
  too full for what I've got for you. I'll keep it. Come back.” `Status`: `Paid 30`
  (não andou) e `Milestone owed: 40`.
- **Passos:** `PC/Bag… → Clear Bag`. Fale com o Bram de novo (mesma visita serve).
- **Esperado:** 40 → 3 Amaze Mulch; 50 → **Berry Pouch** (item-chave); 60 → 5 Boost
  Mulch. `Status`: `Paid 60`, `Milestone owed: 0`.

### T22 · O presente só sai do Livro
- **Passos:** `Book of Berries… → Bram's 8 only`. Faça 3 vezes: `Clock… → New day, keep
  clock` e fale com o Bram (dentro da casa).
- **Esperado:** todo presente é de berries entre as 8 iniciais.
- **Passos:** `Book of Berries… → 67 (every Berry)`. Repita 5 dias.
- **Esperado:** variedade grande, e **nunca** Lansat, Starf ou Enigma.

### T23 · A rara da Laurel
- **Passos:**
  1. `League clear: toggle` até dizer “League cleared…”.
  2. `Book of Berries… → Bram's 8 only`. Fale com a Laurel.
- **Esperado:** “The rare ones only come from the Book, dear. Yours hasn't got one yet. /
  Grow one yourself first. Then we'll talk.” Falar de novo: a **mesma** fala (o dia dela
  não foi gasto).
- **Passos:** `Book of Berries… → 67 (every Berry)`. Fale com a Laurel. Fale de novo.
- **Esperado:** primeira vez: “…One a day. Don't argue.” e uma rara (Liechi a Maranga),
  **nunca Enigma**. Segunda vez: a fala do dia dela (desde a Parte 9), sem rara.
- Depois: `League clear: toggle` de volta para “League NOT cleared.”

**Estado ao fim do bloco C:** Livro 67, nível 1, marcos pagos até 60, Liga desligada.

---

## Bloco D — Cruzamento (Parte 4)

> A mutação é sorteada **na hora de plantar** a segunda berry (25%, contra o vizinho já
> plantado) e só aparece **na colheita**. Por isso cada tentativa é: plantar o vizinho →
> plantar a segunda → `Ripen the garden` → olhar a segunda. Se não cruzou:
> `Empty the garden` e repita (em média 4 tentativas; 10 sem sucesso já é suspeito).
>
> Para ter espaço na bolsa, **não** use Fill Pocket Berries aqui. Dê as berries pelo
> `Give item XYZ` (números no começo do documento), 10 de cada.

### T24 · Cheri ao lado de Chesto dá Lum, e a Lum entra no Livro
- **Preparação:** `Book of Berries… → Bram's 8 only`; dê 10 Cheri (514) e 10 Chesto (515).
- **Passos:** `Empty the garden`. Plante **Chesto em (28,43)** (A1), depois **Cheri em
  (29,43)** (A2, à direita). `Ripen the garden`. Fale com a Cheri.
- **Esperado:** “You found N Cheri Berries / and 1 Lum Berry! / Do you want to pick
  them?” → Yes → a Lum vai para a bolsa. `Status`: `Book 9/67` (a Lum entrou).

### T25 · Vizinho sem receita não atrapalha
- **Preparação:** dê 10 Oran (520).
- **Passos:** `Empty the garden`. Plante **Chesto em (28,43)** e **Oran em (30,43)**
  (as duas pontas da linha de cima). Plante **Cheri no meio, (29,43)**. `Ripen`, olhe a
  Cheri. Repita algumas vezes.
- **Esperado:** a Lum continua saindo mais ou menos **1 vez em 4**. (Cheri + Oran não tem
  receita; antes da Parte 4, um vizinho sem receita podia roubar a chance.)

### T26 · Três gerações
- **Preparação:** dê 10 Leppa (519), 10 Oran (520), 5 Lum (522) e 5 Sitrus (523).
- **Passos e esperado:**
  1. Oran ao lado de **Leppa** → **Sitrus**.
  2. Lum ao lado de **Sitrus** → **Tamato**.
  3. (Terceira, opcional) Tamato ao lado de **Spelon** → Occa; ou use qualquer par da
     tabela do `REI_DA_COLHEITA.md` §4.2.

### T27 · Lansat só depois da Liga
- **Preparação:** dê 10 Micle (575) e 10 Custap (576). Confirme “League NOT cleared”.
- **Passos:** Custap em A1, Micle em A2, `Ripen`, olhe a Micle. Faça **10 tentativas**.
- **Esperado:** **nunca** aparece Lansat.
- **Passos:** `League clear: toggle` (ligado). Repita.
- **Esperado:** a Lansat aparece (em média em 4 tentativas).
- Depois: desligue a Liga de novo.

**Estado ao fim do bloco D:** Livro com as berries novas, horta com plantas, Liga desligada.

---

## Bloco E — Estado diário (Parte 5)

### T28 · O dia da horta recomeça uma vez
- **Passos:**
  1. `Garden level… → 3 Water Channel`. `Go: the garden`. `Status`.
  2. `Go: Bram's house`. `Status`.
  3. `Go: the garden` de novo. `Status`.
  4. `Go: Bram's house`. `Clock… → +24 hours`. `Status` (ainda dentro da casa).
  5. `Go: the garden`. `Status`.
- **Esperado:** `Today bits` = **4** em 1, 2 e 3 (o canal regou uma vez, e a marca fica o
  dia inteiro); **0** em 4 (dia novo, e dentro da casa não há canal); **4** em 5.
- **Se falhar:** anote os cinco valores.

### T29 · Meia-noite sem trocar de mapa (opcional, demorado)
- **Passos:** ajuste o relógio do jogo (`Clock… → +1 hour` várias vezes) até ~23:50.
  Entre na casa do Bram e **espere dentro** passar da meia-noite (use o avanço rápido do
  mGBA). Sem sair, fale com o Bram.
- **Esperado:** ele dá o presente do dia novo (o dia foi percebido na conversa, sem
  recarregar o mapa).

---

## Bloco F — Níveis da horta (Parte 6)

### T30 · Preparação
- `Garden level… → 1 Backyard Plot`. `Book of Berries… → 22 (level 3)`. `Money: set to ¥0`.
  `Berry Master… → Status`: `Level 1   Work 0`.

### T31 · A oferta diz o número real e recusa sem dinheiro
- **Passos:** `Go: Bram's house`. Fale com o Bram.
- **Esperado:** “**22** Berries in your Book now.…¥5,000 for the lot. Shall I?” → **Yes**
  → “Hah. Come back when you've got the money, sprout.” A caixa de dinheiro mostra ¥0 e
  nada é cobrado. `Status`: `Work 0`.

### T32 · Pagar
- **Passos:** `Give ¥10,000`. **Saia e entre** na casa (a oferta é uma vez por visita).
  Fale com o Bram → **Yes**.
- **Esperado:** o presente do dia (ou “That's your two…”) vem **antes**; a oferta fecha a
  conversa: som de compra, a caixa desce para ¥5,000, “Done deal. Come and look in the
  morning.” e acabou (nada de presente depois). `Status`: `Level 1   Work 2`.

### T33 · Nada muda no mesmo dia
- **Passos:** `Go: the garden`. `Go: Bram's house` e fale com o Bram.
- **Esperado:** o B continua grama; o Bram não oferece nada (a obra está andando).

### T34 · Pronta no dia seguinte, e o Bram conta
- **Passos:** `Clock… → +24 hours` (dentro da casa). `Status`: `Level 2   Work 12`.
  Fale com o Bram.
- **Esperado, em ordem:**
  1. “Four more beds! Laurel dug them. / Don't tell her I said so. She'll say I helped.”
  2. Presente novo: a fala do dia do banco R (ex.: “Here. From the Book. Grow 'em
     well.”), depois “Three today -- the garden earns its keep. Or have you got one in
     mind?” e um menu com **Surprise me** / **I've got one**.
  3. Com o Livro em 22 e o Ato 1 por fazer, a conversa termina com “I've got the next
     thing in mind for the garden. But it's more than one old man can dig. I'd need
     somebody to help.” É a mesma fala do T36 e está certa aqui também.
- `Status`: `Work 0`. `Go: the garden`: o B está aberto (4 covas).

### T35 · Semente encomendada
- **Passos:** no menu do T34, **I've got one** → “Go on, then. Which one?” → lista.
  Role a lista inteira e aperte **B**.
- **Esperado:** a lista tem as berries do Livro (22), em ordem, e B volta ao **sorteio de
  3** (3 berries + “And don't eat them all. Plant one.…”).
- **Passos:** `Book of Berries… → 67`, `Clock… → New day, keep clock`, fale com o Bram →
  **I've got one** → escolha **Sitrus**.
- **Esperado:** a lista **não tem Enigma** (66 linhas); “Good pick. Plant it next to
  something it gets along with.” → **1 Sitrus**. Falar de novo: “That's your three for
  today.…”

### T36 · Nível 3: primeiro falta ajuda, depois o canal
- **Passos:** `Book of Berries… → 22`. Confira `Act 1 done: toggle` em “back to state 0”.
  Saia e entre na casa, fale com o Bram. Fale de novo.
- **Esperado:** na primeira conversa, “I've got the next thing in mind for the garden.
  But it's more than one old man can dig. I'd need somebody to help.” Na segunda (mesma
  visita), essa fala **não** se repete.
- **Passos:** `Act 1 done: toggle` → “Act 1 done (4)”. `Give ¥10,000`. Saia e entre, fale
  com o Bram → oferta do canal (“22 in the Book... I could dig a channel from the pond.…
  ¥10,000. Shall I?”) → **Yes**. `Clock… → +24 hours`. Fale com o Bram.
- **Esperado:** duas plaquinhas de nome: **Berry Master** — “See that channel? Runs right
  from the pond.…” — e **Laurel** — “He dug it at three in the morning. The neighbors
  thought it was a Diglett.” `Status`: `Level 3`.
- **Passos:** `Go: the garden`, `Status`.
- **Esperado:** `Today bits 4` (o canal regou), e toda cova plantada aparece **escura**
  (molhada) ao entrar.

### T37 · Nível 4: o Bug Hotel é de graça
- **Passos:** `Book of Berries… → 32`. `Money: set to ¥0`. Saia e entre, fale com o Bram.
- **Esperado:** **sem** caixa de dinheiro: “Bugsy wants to build a Bug Hotel by the beds.
  Won't take a coin for it. / Says the bugs will come for the Berries and stay for the
  architecture. / Well? Do I let him?” → **Yes** → “Done deal. Come and look in the
  morning.” (com ¥0).
- **Passos:** `Clock… → +24 hours`, fale com o Bram.
- **Esperado:** “Bugsy finished his Bug Hotel last night. Hollow stems, bark, a pile of
  stones... / He means more bugs. He's happy about more bugs.” `Status`: `Level 4`. Nas
  próximas conversas, nenhuma oferta (acabaram as reformas do Bram).

### T38 · Save antigo: tutorial feito antes de a horta existir (Partes 2 e 3)
- **Contexto:** quem jogou antes destas partes já tem o tutorial feito, mas nível 0 e
  Livro vazio. O jogo corrige sozinho; este teste simula esse save.
- **Passos:**
  1. `Reset Berry Master`.
  2. `Flags & Vars… → Set Flag XYZ…` → escolha **732** (a tela mostra também 0x2DC;
     é a `FLAG_GOT_BERRY_ROUTE_30_HOUSE`, “o tutorial do Bram já foi”) e ligue.
  3. `Status`: `Level 0`, `Book 0/67`.
  4. `Go: the garden`. `Status`.
  5. `Go: Bram's house`. Fale com o Bram. `Status`.
- **Esperado:** no passo 4, `Level 1` (entrar na Route 30 corrigiu o nível). No passo 5,
  **sem** tutorial: vai direto ao presente (fala do banco R, 2 berries das 8 iniciais),
  e o `Status` mostra `Book 8/67` (a conversa registrou as 8 do Bram).

---

## Bloco F2 — Pedidos do dia (Parte 7)

Um pedido por dia, sorteado na primeira conversa com o Bram (a qualquer hora, por
enquanto; a rotina por horário é da Parte 8). **Comum**: N de uma berry do Livro (3 a 5
das fáceis, 1 das difíceis), paga ₽ por berry + 1 adubo (Growth ou Damp, alternando por
dia). **Descoberta** (horta nível 2+, 1 dia em 3): 1 berry que ainda **não** está no Livro
mas cujos dois pais estão; o Bram manda perguntar à Laurel; paga o dobro + Surprise Mulch.

Valores por “geração” (quantos cruzamentos separam a berry das 8 do Bram):

| Geração | 0 (as 8) | 1 | 2 | 3 | 4 | 5+ |
|---|---|---|---|---|---|---|
| Pede | 3 | 5 | 5 | 3 | 3 | 1 |
| ₽ por berry | 100 | 150 | 200 | 300 | 400 | 600–1000 |

Debug: `Order: new common` / `Order: new discovery` apagam o pedido de hoje; a próxima
conversa com o Bram sorteia e anuncia um novo daquele tipo (descoberta sem candidata →
comum). Os pedidos são lidos no `Status` (última linha).

### T41 · Não há pedido no dia do tutorial
- **Passos:** `Reset Berry Master`. Fale com o Bram (tutorial inteiro). Fale de novo sem sair.
- **Esperado:** nenhuma fala de pedido nas duas conversas; `Status`: `Order: none drawn today.`
- **Passos:** saia da casa, entre de novo, fale com o Bram.
- **Esperado:** agora ele anuncia o pedido (“The girls at the Goldenrod flower shop want 3
  Cheri Berries…”, o cliente varia). Se você já tiver as berries, ele pergunta na hora
  “That's 3 Cheri Berries! Hand them over?”.

### T42 · O pedido não muda no mesmo dia
- **Passos:** sem as berries pedidas, fale com o Bram de novo; saia, entre e fale mais uma vez.
- **Esperado:** na mesma visita ele não repete nada do pedido; depois de sair e entrar,
  **um** lembrete curto do **mesmo** pedido (mesma berry, mesma quantidade). `Status` igual.

### T43 · Entregar um pedido comum
- **Passos:** `Order: new common`, fale com o Bram (anúncio). Dê-se as berries pedidas
  (`Give item`: Cheri = 514 e as outras em sequência, na ordem da bolsa; Aguav = 527), fale com ele, **No** no “Hand them over?”, e de novo, **Yes**.
- **Esperado:** **No** → ele não tira nada e a conversa segue. **Yes** → as berries saem,
  agradecimento do cliente, “{nome} received ¥N.” com o valor da tabela × quantidade,
  e 1 Growth ou Damp Mulch. `Status`: `…, delivered.` Falar de novo: nada de pedido.

### T44 · Bolsa sem espaço para o adubo
- **Passos:** `Order: new common`, fale (anúncio). `PC/Bag… → Clear Bag`, `Fill Pocket
  Items` (999 de cada item, adubos inclusive) e dê-se as berries pedidas. Fale com o
  Bram, **Yes**. Depois `Clear Bag` e dê de novo a Squirtbottle (722).
- **Esperado:** ele avisa que a bolsa está cheia **antes** de tirar as berries; as berries
  continuam na bolsa, nada de dinheiro, `Status` continua `open`.

### T45 · Pedido de descoberta e a dica da Laurel
- **Preparação:** nível 2+ (`Garden level… → 2`), Livro com as 8 do Bram.
- **Passos:** `Order: new discovery`, fale com o Bram. Fale com a Laurel. Fale com ela de novo.
- **Esperado:** o Bram: “Kurt swears there's a Berry called X… Ask Laurel”. A Laurel, na
  primeira conversa da visita: “X. Y beside Z.” — Y e Z são os pais de verdade (ex.: Aguav
  = Rawst ao lado de Leppa); na segunda, sem dica.
- **Passos:** plante Y e Z lado a lado na horta, `Ripen` até sair a X (ou dê-se a X), entregue.
- **Esperado:** “That's the X Berry! Hand it over?” (singular), pagamento em dobro
  (Aguav: ₽300) e **Surprise Mulch**.

### T46 · Dia seguinte, pedido novo
- **Passos:** com um pedido entregue, `Clock… → +24 h`, entre na casa e fale com o Bram.
- **Esperado:** pedido novo anunciado (a berry pode repetir, mas o anúncio aparece de novo),
  `Status` `open`.

---

## Bloco F3 — Elenco e rotina (Parte 8)

Ninguém troca de lugar na sua frente: a posição e a fala de cada um são decididas ao
**entrar no mapa**. Depois de cada `Clock…` (que recarrega o mapa), confira os dois mapas:
a Route 30 (horta) e a casa. Para saber o dia da semana sem calendário: a Tilly só aparece
sábado e domingo, e a fala dela diz qual dos dois (“Welcome to Tilly's Mulch Emporium!” =
sábado).

### T47 · De dia, em dia de semana
- **Passos:** `Clock…` até dar entre 10h e 19h num dia em que a Tilly **não** está na
  banquinha. Olhe a horta e entre na casa.
- **Esperado:** horta: só a Laurel, em (27,43), virada para os canteiros; falando com ela:
  uma fala do banco E (ou, na primeira conversa do dia, uma reação: ver T58). Casa: Bram na mesa
  (fala de sempre: presente, pedido…), Sunflora sob a janela (“Floraaa!”, com plaquinha
  e grito). Ninguém ocupa o único acesso de um canteiro: todos os 10 se alcançam a pé.

### T48 · De noite
- **Passos:** `Clock… → +6 hours` até passar das 19h. Horta e casa.
- **Esperado:** horta vazia. Casa: Bram à mesa **virado para ela**; falando com ele, uma
  fala de sonho (“Zzz…”), e ele **não** se vira para você; Laurel à mesa.
- **Passos:** fale com a Laurel. Saia e entre, fale de novo.
- **Esperado:** na primeira conversa da visita, uma receita do caderno (“X. Y beside Z.
  Touching, side by side…”), com Y e Z no seu Livro e X fora dele; na segunda, “I'm
  reading. You've had your page.”; depois de sair e entrar, outra receita (pode repetir).

### T49 · O presente à noite
- **Preparação:** presente do dia ainda não retirado (`Clock… → New day, keep clock`, de
  noite).
- **Passos:** fale com a Laurel.
- **Esperado:** “He's asleep. He left these on the table for you. / He counted them twice.
  Don't tell him I watched.” e 2 berries do Livro (3 no nível 2+). Falar de novo: sem
  presente. De manhã o Bram vai direto à fala do dia (o presente já saiu).

### T50 · De manhã
- **Passos:** `Clock… → Next morning, 7:00`. Horta e casa.
- **Esperado:** horta: Bram em (27,44), virado para a fileira de baixo; a conversa com ele
  é a mesma da casa (obra pronta, marcos, pedido, presente, reforma). Casa: só a Laurel
  (fala do banco D) e a Sunflora.

### T51 · Fim de semana
- **Passos:** `Clock… → +24 hours` até a Tilly aparecer (de manhã em casa, à tarde na
  horta).
- **Esperado:** sábado/domingo de manhã: Tilly na cadeira azul da casa (“Grandpa's out
  watering! I'm eating toast…”). À tarde: Tilly na banquinha (24,41) com a fala do dia,
  “Buy some! Buy LOTS!” e a loja: Growth, Damp, Stable, Gooey Mulch (₽200). Ao sair da
  loja: “Come back next weekend! Bring money!”. A Laurel **não** está na horta (dia de
  forno): em casa, na primeira conversa do dia, “Bread day. Don't open the oven…”.

### T52 · Loja no nível 4
- **Passos:** `Garden level… → 4`, fale com a Tilly num fim de semana à tarde.
- **Esperado:** a lista tem também Rich e Surprise Mulch. Volte para o nível que estava.

### T53 · Bugsy
- **Passos:** `Act 1 done: toggle` → ligado. Terça ou quinta à tarde, horta.
- **Esperado:** Bugsy em (29,41), virado para o canteiro B, com uma fala do banco H. Com o Ato 1 desligado,
  ele não vem. Nunca no mesmo dia que a Tilly. Desligue o Ato 1 de volta.

### T54 · Tutorial a qualquer hora
- **Passos:** `Reset Berry Master`, `Next morning, 7:00` (ou de noite). Horta e casa.
- **Esperado:** antes do tutorial o Bram está **em casa**, acordado, a qualquer hora; o
  tutorial roda normal. Depois dele, a rotina vale (de manhã, na próxima entrada, ele vai
  para a horta).

---

## Bloco F4 — Banco de falas e corações (Parte 9)

Cada pessoa tem um banco de 10 falas; a do dia é `dias de jogo % N` (a mesma o dia todo).
Bram, Laurel e Tilly têm **corações**: +1 por dia em que você fala com eles; com 0–4 só
as falas 1–4 saem, com 5–11 até a 7, com 12+ todas. `Berry Master… → Hearts…` põe todos
em 0, 5, 12 ou 15; a última página do `Status` mostra os corações. Na **primeira
conversa do dia** pode vir uma **reação** no lugar da fala do dia.

### T55 · Corações sobem uma vez por dia
- **Passos:** `Hearts… → 0`. Fale com a Laurel duas vezes. `Status`. `Clock… → New day,
  keep clock`, fale com ela de novo. `Status`.
- **Esperado:** Laurel 1 depois das duas conversas; 2 no dia seguinte. Bram e Tilly não
  mudam.

### T56 · O presente tem fala própria e não repete o tutorial
- **Passos:** dia novo, fale com o Bram (presente ainda não retirado).
- **Esperado:** uma fala do banco R (“Here. From the Book. Grow 'em well.”, “Hold out
  your hands…”…), as berries e **nenhum** “And don't eat both of them. Plant one…” (isso é
  só do tutorial). No nível 2+: depois da fala R, “Three today -- the garden earns its
  keep. Or have you got one in mind?” com o menu — sem “You came back!” e sem “Name it…”
  antes do menu.

### T57 · Depois do presente, a fala do dia
- **Passos:** fale com o Bram de novo, de tarde (em casa) e de manhã (na horta).
- **Esperado:** de tarde, uma fala do banco B (“Seed day. Sit down…”, “I've got a seed
  here I can't name…”); de manhã, do banco A (“Water before the sun's up…”, “I talk to the
  trees…”). A mesma fala o dia todo; com `Hearts… → 12`, também as falas 8–10 aparecem
  ao longo dos dias.

### T58 · Reações da Laurel
- **Esperado, na primeira conversa do dia (de manhã ou à tarde, nunca à noite):**
  - segunda-feira, antes da Liga: “My husband hands out the easy ones. / I keep the
    others…”;
  - quarta-feira com um Pokémon de Planta te seguindo: “That one would like it here. /
    Let it out sometime.”;
  - horta toda vazia (`Empty the garden`): “Empty beds. Like an empty table…”;
  - sábado ou domingo à tarde (em casa): “Bread day. Don't open the oven…”.
  Na segunda conversa do dia: a fala do banco (D de manhã, E à tarde).

### T59 · O caderno da Laurel à noite
- **Passos:** de noite, fale com ela em dias diferentes.
- **Esperado:** a receita sai cada dia com uma fala diferente do banco F (“The page with
  the coffee stain…”, “My grandmother's hand…”, “Sit. No, closer, the lamp's bad…”), com
  a berry nova e os dois pais certos. Com pedido de descoberta aberto, a dica do pedido à
  noite também usa essas falas; de dia, a fala simples (“X. Y beside Z. Touching…”).

### T60 · O Bram comemora a primeira colheita
- **Preparação:** `Reset Berry Master`, tutorial, plante uma berry num canteiro da horta,
  `Ripen the garden`, colha.
- **Esperado:** na conversa seguinte com o Bram: “Your first! Hold it up. No -- higher. /
  There. Now you're a farmer.” Só uma vez no jogo; colher numa árvore de rota não conta.

### T61 · O Bram comemora berry nova cruzada
- **Passos:** cruze duas berries na horta até sair uma que não está no Livro (ou plante
  uma berry de fora do Livro), colha, fale com o Bram.
- **Esperado:** “You grew a {berry}? I've never seen one! / Laurel! LAUREL!”, uma vez por
  berry nova. As 8 do Bram e berries colhidas fora da horta não contam.

### T62 · Reações da manhã do Bram
- **Esperado, de manhã, na primeira conversa do dia:** domingo — “Sunday! Tilly's
  selling out front this afternoon…”; terça e quinta, com o Ato 1 feito — “Bugsy's coming
  today…”.

### T63 · Tilly e Bugsy
- **Esperado:** Tilly na banquinha diz uma fala do banco G antes da loja (reações: Livro
  com 66, “You grew ALL of them?…”; domingo com inseto te seguindo, “Is that a …?!”).
  Bugsy diz uma fala do banco H; com a horta no nível 4, a primeira conversa de cada
  visita é “The hotel's full! Well, one Combee. / It's a start.”.

---

## Bloco F5 — Pragas e ervas (Parte 10)

Só os 10 canteiros da horta têm praga e erva; árvore de rota nunca. A praga aparece ao
falar com uma planta **crescendo** (não madura). Debug: `Utilities… → Berry Functions… →
Give map trees pests / weeds` (põe em todas as árvores na tela; a praga só em planta que
já passou de “plantada”: use `Berry Master… → Grow garden 1 stage` antes).

### T64 · Praga na horta
- **Passos:** plante uma berry num canteiro, `Grow garden 1 stage`, `Give map trees
  pests`, fale com a planta.
- **Esperado:** uma narração do banco P (“Something is nibbling at the leaves!”, “A tiny
  face peeks out…”), depois batalha selvagem. Nível `10 + 4 × insígnias` (teto 60). Cor da
  berry → praga: vermelha de dia Ledyba (de noite Spinarak); azul/roxa Blipbug (noite
  Volbeat); rosa Cutiefly (noite Illumise); verde Burmy (noite Kricketot); amarela Combee
  (noite Venonat).

### T65 · Adubo muda a praga
- **Passos:** adube um canteiro com Stable Mulch e plante; repita T64 algumas vezes.
  Depois com Gooey ou Rich Mulch.
- **Esperado:** metade das vezes Dwebble (Stable) ou Rellor (Gooey/Rich).

### T66 · Árvore de rota nunca
- **Passos:** numa árvore de rota crescendo, `Give map trees pests`, fale com ela.
- **Esperado:** nenhuma batalha, nenhuma narração (a praga some).

### T67 · Erva daninha
- **Passos:** `Give map trees weeds`, fale com uma planta da horta crescendo.
- **Esperado:** “A weed is growing here. Do you want to pull it out?” → Yes → “… pulled
  out the weed!”. Com erva num canteiro, a Laurel (primeira conversa do dia, de dia)
  diz “There's a weed in bed A. I'm not pulling it. / It's your bed.” (ou B).

### T68 · As 8 famílias só na horta
- **Passos:** ande na grama da Route 30, 31, 37, National Park e Kitakami Border, e use
  Rock Smash na Cliff Edge Cave.
- **Esperado:** nunca Blipbug, Combee, Scatterbug, Rellor, Wurmple, Illumise, Volbeat
  nem Dwebble. Com os 8 capturados, o Bugsy diz “You found all of them? / I'm going to
  have to write a second notebook.”

---

## Bloco F6 — Batalhas de sempre e o assalto da Klara (Parte 11)

Nenhuma dá blackout nem custa dinheiro (perder cura o time), uma por dia por pessoa,
prêmio só na vitória. Os times acompanham o nível do seu time (sempre, como o Nexus).

### T69 · Tilly
- **Preparação:** `Act 1 done: toggle` (ligado), sábado ou domingo à tarde.
- **Esperado:** depois da fala dela, “Mulch, or a battle? Mulch is cheaper.” com o menu
  **Buy mulch / Battle / Bye**. Battle → “Battle time! My bugs have names…” → Bug Catcher
  Tilly (Mr. Roly e Buzzbelle; com a horta no nível 3–4 também Pebbles e Squiggles; no 5 o
  time evoluído). Vencer: “You won! Here, two from the shop…” e 2 de um adubo dela.
  Perder: “Mr. Roly WINS!…”, time curado. De novo no mesmo dia: “Mr. Roly needs a nap…”.
  Sem o Ato 1 (estado 0): só a loja, sem menu.

### T70 · Bugsy
- **Preparação:** Ato 1 ligado, terça ou quinta à tarde.
- **Esperado:** depois da fala, “Field test!… For science! Are you in?” (Yes/No). Yes →
  batalha (sempre com Scizor, ou Scyther se o seu time for baixo). Vencer: “Your bugs
  earned this…” e 3 berries do Livro. No mesmo dia: “I'm still writing up the last one.”

### T71 · Klara aparece
- **Passos:** horta no nível 2+, um canteiro maduro (`Ripen the garden`), de manhã:
  `Berry Master… → Klara: raid this morning`.
- **Esperado:** a Klara de pé na frente de um canteiro maduro, virada para ele.

### T72 · Perder para a Klara
- **Esperado:** abertura (uma de 10, ex.: “Oh, it's YOU. The Berry police.”), batalha,
  derrota sem blackout, uma fala dela levando o canteiro (“Ooh, this one's heavy!…”),
  fade e ela some; o canteiro fica vazio, **sem** gráficos corrompidos no Bram. O Bram,
  na conversa seguinte, comenta (“She took the WHOLE bed?…”).

### T73 · Vencer a Klara
- **Esperado:** uma fala de derrota dela, ela some, o canteiro fica. O Bram: “You chased
  her off? Ha!…”. Na 5ª vitória: “You know what? Berries are SO last season. Mochi…”.

### T74 · Sair sem falar com ela
- **Passos:** com a Klara na horta, entre na casa e volte.
- **Esperado:** ela não está mais, o canteiro dela está vazio, e o Bram comenta.

---

## Bloco F7 — A história, prólogo ao Ato 4 (Parte 12)

`Berry Master… → Story…` põe o estado (0–8) e marca as falas de uma vez anteriores;
`Enigma sprouts (Laurel)` planta a Enigma brotada no canteiro dela. Insígnias: jogue até
elas ou use o menu de flags do debug (`FLAG_BADGE02_GET`, `FLAG_BADGE07_GET`).

### T75 · Prólogo
- **Passos:** `Reset Berry Master`, tutorial com o Bram.
- **Esperado:** no fim da conversa, com a Laurel na mesa: “Now that's the talk…” e a troca
  “Not the patch by the door.” / “…Not the patch by the door.” / “That one's mine.” (com
  plaquinhas). Sem a Laurel em casa: o Bram sozinho, “…That one's Laurel's. Don't ask me
  why. I asked once.” `Status`: estado 1.

### T76 · Ato 1a — a primeira praga
- **Passos:** estado 1; vença ou capture uma praga na horta, de dia, com a Laurel lá.
- **Esperado:** depois da batalha, a Laurel vira: “A Ledyba. In the beds. / Fifty years…”.
  Na conversa seguinte, o Bram: “BUGS? In MY beds?…” (uma vez). Estado 2.

### T77 · Ato 1b — o Bugsy chega
- **Passos:** estado 2 + 2ª insígnia, Route 30 de dia.
- **Esperado:** o Bugsy na horta (29,41); falando com ele: “Shh! Don't move. There's a
  Blipbug on the third bed…”. Estado 3; ele passa a vir terça e quinta.

### T78 · Ato 1c — o censo
- **Esperado:** com menos de 3 famílias exclusivas capturadas: “Any luck? You've caught N of
  them so far…”. Com 3: “Three of them!…” e a **Silver Powder**. Estado 4 (níveis 3 e 4 da
  horta e a batalha do Bugsy liberados).

### T79 · Ato 2 — o visitante da noite
- **Passos:** estado 4, horta nível 3, de noite; entre na casa do Bram e saia.
- **Esperado:** ao sair, um cavalo escuro no canteiro B; exclamação, ele vira, grita, flash
  e foge pelo lago; “Something dark and tall…” e “Hoofprints…”. Estado 5. Falar com ele
  (chegando pelo outro lado) dá a mesma cena. Na manhã seguinte, a Laurel: “You were out
  late…” (uma vez).

### T80 · Ato 2b — o Bram acorda
- **Esperado:** estado 5, de noite: o Bram acorda (exclamação) e conta da semente de
  Freezington. Estado 6.

### T81 · Ato 3 — o caderno
- **Passos:** estado 6, Livro ≥ 40, 7ª insígnia, Laurel de noite.
- **Esperado:** a Sunflora grita; a Laurel conta a história do rei e dos dois cavalos e dá a
  **Enigma Berry**. O canteiro dela (23,38) aparece. Estado 7. Com a bolsa cheia: “Come
  back when you have room…”, nada muda. Sem a Enigma depois (plantada num canteiro comum ou
  vendida): uma por dia, com “That's a bed…” ou “You lost it?…”.

### T82 · Ato 4 — a primeira folha
- **Passos:** plante a Enigma no canteiro da Laurel e espere brotar (ou `Enigma sprouts`);
  de dia, Route 30.
- **Esperado:** a Laurel ajoelhada em (23,39), olhando o broto (não está em casa). Falando
  com ela: “… / It came up.”, o Bram sai pela porta e para ao lado, o diálogo dos dois
  (plaquinhas), “Go on, sprout. Give us a minute.”, recarga; estado 8. Na noite seguinte:
  “I wrote to Freezington…”. Nas manhãs de segunda, quarta, sexta e domingo, cartas
  (“From Honey. …”, “From Kurt. …”).

---

## Bloco G — Regressão fora da horta

### T39 · Plaquinhas de nome em outras cenas
- **Contexto:** no mesmo dia da horta, o índice das plaquinhas mudou para 2 bytes e a
  base passou de 255 para 250 (revisão das partes 1–3).
- **Passos:** fale com qualquer personagem que use plaquinha fora da horta (por exemplo,
  o Prof. Elm no laboratório de New Bark).
- **Esperado:** a plaquinha aparece com o nome certo, sem letra estranha logo depois do
  nome e sem quebra de linha fora do lugar.
- **Passos:** jogo novo (ou `NewBarkTown_PlayersHouse_1F` com `VAR_NEWBARK_TOWN_STATE` 1):
  desça a escada e deixe a mãe falar.
- **Esperado:** **todas** as falas da mãe com retrato têm a plaquinha **Mom**, inclusive
  “Oh, {PLAYER}…! Our neighbor, Prof. Elm…” e “Oh, and don't forget your Running Shoes!”
  (corrigidas depois do QA de 03/10/2026).

### T40 · Árvores de rota comuns
- **Passos:** colha uma árvore de berry em outra rota (Route 29, Route 31…).
- **Esperado:** igual a antes. Colher fora da horta **também** registra no Livro
  (T16), e isso é de propósito.

---

## Como reportar um problema

Para cada teste que falhar, mande:
1. O número do teste (ex.: **T21**) e o passo.
2. O que apareceu (a fala exata, ou um screenshot).
3. A saída do `Berry Master… → Status` logo depois.
4. Se possível, o savestate do começo do bloco.

Achados que já são esperados e **não** são defeito:
- O B planta e depois “some” quando você volta para o nível 1 pelo debug (T14): a planta
  fica guardada e reaparece.
- Falar com o Bram no mesmo dia depois de pagar não mostra oferta (T33).
- `Clock…` só anda para a frente.
