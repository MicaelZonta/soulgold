# Berry Master — testes no jogo, em ordem (Partes 1 a 6)

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
| Bram | dentro da casa, (4,4) |
| Laurel | dentro da casa, (3,4) |

**Tela de Status** (`Berry Master… → Status`), três páginas:
1. `Level L   Work W` / `Planted garden plots: N/10`
2. `Book B/67   Paid P` / `Milestone owed: M`
3. `Hour H   Today bits T` / `Harvest King state: S`
e por fim `Bram's gift: taken today.` ou `…still waiting today.`

`Work`: 0 = nenhuma obra; 2, 3 ou 4 = obra paga daquele nível, fica pronta amanhã;
12, 13 ou 14 = pronta, o Bram ainda não falou dela.
`Today bits`: número que soma as marcas do dia; hoje só existe o 4 (= “canal regou hoje”).

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
- **Esperado:** “That's your two for today. / Go and plant one. I'll pick more by morning
  -- I always do.”

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
- **Esperado:** no passo 2 a terra fica **escura** na hora (molhada). No passo 3, estágio
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
  2. `PC/Bag… → Fill Pocket Berries` (999 de cada berry).
  3. Plante uma Sitrus no A, `Ripen the garden`, colha.
  4. `Status`.
- **Esperado:** “The Bag's Berries Pocket is full. / The Sitrus Berry couldn't be taken.” e
  o Livro **continua 8**.
- **Observação:** se a colheita for de só 1 berry, ela cabe (998 + 1). Nesse caso,
  plante de novo e repita.
- Depois: `PC/Bag… → Clear Bag` e dê de novo a Squirtbottle (722).

### T18 · Com 11 no Livro, nenhum marco
- **Passos:** `Book of Berries… → 11`. `Go: Bram's house`, fale com o Bram.
- **Esperado:** nenhum prêmio. Só o presente do dia (se o dia virou em algum teste
  anterior) ou “That's your two for today…” (se não virou).

### T19 · Marco 12 (e a oferta de reforma junto)
- **Passos:** `Book of Berries… → 12 (level 2)`. Fale com o Bram.
- **Esperado, em ordem:**
  1. “Let me see that Book of yours... / 12 Berries! You're getting the hang of this,
     sprout. / Here. Something for the garden.” → recebe **5 Growth Mulch**.
  2. O presente do dia, ou “That's your two for today…”.
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
  **nunca Enigma**. Segunda vez: “One a day. I said don't argue.”
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
  2. Presente novo: “You came back! … / Three today -- the garden earns its keep. Or have
     you got one in mind? / Name it. If it's in the Book, I've got seed for it.” e um
     menu com **Surprise me** / **I've got one**.
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
  **sem** tutorial: vai direto ao presente (“You came back!…”, 2 berries das 8 iniciais),
  e o `Status` mostra `Book 8/67` (a conversa registrou as 8 do Bram).

---

## Bloco G — Regressão fora da horta

### T39 · Plaquinhas de nome em outras cenas
- **Contexto:** no mesmo dia da horta, o índice das plaquinhas mudou para 2 bytes e a
  base passou de 255 para 250 (revisão das partes 1–3).
- **Passos:** fale com qualquer personagem que use plaquinha fora da horta (por exemplo,
  o Prof. Elm no laboratório de New Bark).
- **Esperado:** a plaquinha aparece com o nome certo, sem letra estranha logo depois do
  nome e sem quebra de linha fora do lugar.

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
