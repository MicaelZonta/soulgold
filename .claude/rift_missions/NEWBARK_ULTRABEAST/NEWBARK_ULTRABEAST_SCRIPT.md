# New Bark — Necrozma, Kartana + Guzzlord + Nihilego (Rift Mission 4) — roteiro

**O que é este arquivo:** a cena como ela acontece na tela — as falas literais
(em inglês, exatamente como estão na ROM) e a coreografia, beat a beat.
Estado, flags, objetos, arquivos tocados, riscos e checklist de teste ficam em
[`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md).

**Fonte:** `data/maps/OlivineCity_House1/scripts.pory`,
`data/maps/NewBarkTown/scripts.pory`.
Ao mudar uma fala, mude no `.pory` e traga a mudança para cá.

**A história em quatro linhas.** Três fendas abrem sobre New Bark e as três
Ultra Beasts **não se comportam como três**: elas se mexem no mesmo instante, na
mesma direção, como uma coisa só vestindo três corpos. O único contra é quebrar
as três ao mesmo tempo, o que exige **quatro pares de mãos** — e é assim que o
garoto que ouviu "não" é aceito, pela mulher que acabou de ser ensinada a
perguntar. E quando as três caem, a criatura das outras três missões sai da luz,
**come** as três, vira outra coisa e põe os quatro no chão num movimento só.

**A cidade fica de pé. Ninguém ganha. Era esse o plano desde a primeira missão.**

---

## Elenco e marcação

Não existe um tile de água em `LAYOUT_NEW_BARK_TOWN`, então aqui o bit de
colisão é a verdade inteira — ao contrário da praia de Cherrygrove.

```text
       x= 2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
   y= 9   #  #  #  .  .  #  #  #  D  #  .  #  .  .  .  .  #  #  #  #  #  #  #  #
   y=10   #  #  .  .  .  .  .  .  .  E' .  .  .  1  1a 1b #  #  #  #  #  #  #  #
   y=11   .  .  .  .  .  .  .  .  .  .  .  .  .  .  Nk #  #  #  d  #  #  .  .  .
   y=12   .  U' .  .  .  .  .  .  .  .  .  .  .  .  N  U  M  *  K  A  E  .  .  .
   y=13   .  .  .  .  .  .  .  .  .  .  .  .  2  2a 2b 2c 2d 2e .  G  z  .  .  .
   y=14   .  .  .  .  .  .  .  #  .  .  .  .  .  .  a3 a2 a1 aX .  .  z' .  .  .
   y=15   #  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  3  3a 3b

   D  porta do laboratório, warp (10,9)      d  porta da casa do jogador, warp (20,11)
   *  jogador (20,12)      K Looker (21,12)      A Anabel (22,12)
   M  Mom (19,12)          G Gold/Crystal (21,13)
   z  Azumarill começa (22,13)    z' Azumarill depois do corte (19,14)
   U' Lusamine começa (3,12)      U Lusamine depois do fade (18,12), depois (17,12)
   E' Elm começa (11,10)          E Elm depois do fade (23,12)
   1  Kartana (15,10) → 1a → 1b (17,10) no drift em uníssono
   2  Nihilego (14,13) → 2a → 2b no drift, depois 2c 2d 2e na investida,
      terminando em (19,13), a um passo diagonal do jogador e **embaixo da Mom**
   3  Guzzlord (23,15) → 3a → 3b (25,15); (26,15) é parede
   a1 a2 a3  a carga do Azumarill contra a criatura, terminando em (16,14)
   N  a criatura (16,12) — e também onde fica o que ela vira
   Nk (16,11) é para onde a Kartana é arrastada antes de ser comida
```

**O bolso do Looker:** (21,11) é a parede da casa do jogador, (22,12) é a Anabel
e (21,13) é o Gold/Crystal. O **único** tile de onde se fala com ele é (20,12),
olhando para leste. E (20,12) é exatamente onde o jogo põe o jogador duas vezes:
é o `HEAL_LOCATION` **e** o pouso do Fly. **Retry custa zero passos** — a única
missão do arco em que isso é verdade.

**(20,13) fica deliberadamente vazio**, antes e durante a cena. Nada é
estacionado ali: é o que garante que a caixa de texto nunca cubra ninguém.

---

## Ato 1 — O briefing da Missão 4 (Olivine City, House1)

Três caixas. A do meio é a **conversa do Faller** — o autor foi explícito: ela
não pertence ao meio de uma luta, acontece aqui, sentada, com tempo.

```text
# OlivineCity_House1_Text_BriefingM4
LOOKER
  {PLAYER}. Sit down.

  No - actually, don't.

  There isn't time, and you would
  not anyway.

  Cherrygrove holds.

  And the Professor? Did he eat
  something, at last?

ANABEL
  He ate, and then he
  read every log in Johto.

  He telephoned at six this
  morning, from a post office, to
  read us somebody else's
  notebook.

  Professor Elm has had the same
  reading for six weeks. He wrote
  “check the sensor” in the
  margin every time.

  And then he posted the whole
  thing to Alola anyway.

LOOKER
  A man who suspects he
  is wrong and files it in
  writing. There are worse
  witnesses.

  Is the Professor going?

ANABEL
  No. He is going home.

  He did the one thing only he
  could do, which was recognise
  it, and he handed it to us.

  Elm is the one on the ground
  now. It is his instrument, his
  six weeks and his town.
```

```text
# OlivineCity_House1_Text_BriefingM4Faller
LOOKER
  …Three, Anabel?

ANABEL
  Three.

  Opening together. Closing
  together.

  …Looker, I need the chair.

LOOKER
  Chief-

ANABEL
  I'm fine. Sit down,
  {PLAYER}. This part is for you
  and I would rather say it here
  than shout it later.

  On that beach in Cherrygrove I
  told you what I am.

  I did not tell you the rest.

  A Faller is someone who came
  through one of those tears and
  stayed on this side.

  I don't remember where I came
  from. I've stopped pretending
  that will come back.

  I remember someone's hand.

  That is the whole memory.
  Someone reached down, and I
  wasn't alone anymore.

  And I feel them open. Only
  that, and only a few seconds
  before the meter does.

  Blackthorn I felt from the
  street. The Lake from the
  street. The beach from the
  sand.
```

```text
# OlivineCity_House1_Text_BriefingM4NewBark
ANABEL
  {PLAYER} - I felt these three
  from this chair.

  From Olivine. Sixty miles of
  water and a mountain.

LOOKER
  …You have never once
  put that in a report.

ANABEL
  Put it in this one.

  I'll sign it.

LOOKER
  {PLAYER}. New Bark Town
  has no Pokémon Center.

  No Gym.

  It has a laboratory and about
  forty people.

  We told them to leave.

  Half of them would not.

  Your mother is one of the half.

  Three missions, {PLAYER}, and I
  have never once asked you this.

  …Do you want to go?

ANABEL
  Heal everything.

  Take these.

  And we are going with you -
  that part is not a question.
```

> Esta caixa e `CherrygroveCity_Text_UBHook` são **um par**: o Kukui não vai a
> New Bark — o que ele faz é achar as seis semanas de "sensor quebrado" do Elm e
> telefonar para a polícia. Nunca edite uma sem a outra.

### Depois do briefing — "vá na frente"

```text
# OlivineCity_House1_Text_LookerGoAheadM4
LOOKER
  New Bark Town,
  {PLAYER}. Your own front door.

  I am sorry it is this one.
```

```text
# OlivineCity_House1_Text_AnabelGoAheadM4
ANABEL
  Go.

  We'll be a step behind you the
  whole way.
```

---

## Ato 2 — A estrada, antes da cena

Cada conversa termina devolvendo o ator ao olhar que o `map.json` pede, para que
uma fala de um tile torto não deixe ninguém de lado quando a cena começar.

**Lusamine** (`UBLusamine`), sozinha na estrada em (3,12) — **a primeira fala
dela no arco inteiro.** Ninguém a anunciou: o briefing de Olivine não a menciona
uma vez sequer, de propósito. Ela não entrega nada do nó que vem depois.

```text
# NewBarkTown_Text_UBLusamineIdle
LUSAMINE
  You are taller than
  the photographs.

  …Forgive me. I have practiced
  this, and I am still doing it
  badly.

  Lillie writes about you.

  Gladion does not write, but he
  mentions you, which from him is
  the same thing.

  Nobody sent for me. I read the
  same numbers they did and I got
  in a boat.

  We will talk properly when this
  is over.

  If I am still someone you want
  to talk to.
```

Com a família Cosmog na equipe — ela é a **única pessoa viva** que sabe como
aquela luz é do outro lado, porque ela usou uma. Regra inegociável: a cena não
sugere, em nenhum momento, que nada disso é culpa do jogador — e é **ela** quem
diz isso em voz alta.

```text
# NewBarkTown_Text_UBLusamineIdleCosmog
LUSAMINE
  …Oh.

  Oh, you brought it with you.

  {STR_VAR_1} is standing on a
  road with three tears over it,
  and it is not frightened.

  I knew one of those, once.

  I did not deserve it, and I
  used it, and I would like you
  to hear the next part from me
  before anyone else says it.

  They shine. Things on the other
  side can see that.

  That is not your fault and it
  never was.

  It is why I came.
```

**Elm** (`UBElm`), em (11,10), do lado de fora da porta do próprio laboratório.

```text
# NewBarkTown_Text_UBElmIdle
ELM
  Six weeks.

  Six weeks of the same reading,
  and every time I wrote “check
  the sensor” in the margin.

  Then Cherrygrove was in the
  morning paper.

  So I posted the whole log to
  the one man in the world who
  would not laugh at it, and he
  telephoned the police before he
  finished reading it.

  Professor Kukui works fast when
  he is frightened.

  Everyone who would come is in
  the lab. It's the strongest
  building in town, which is not
  saying much.
```

Com a família Cosmog — ele é quem identificou o ovo, lá atrás:

```text
# NewBarkTown_Text_UBElmIdleCosmog
ELM
  And there it is.

  I had a {STR_VAR_1} on my table
  in a shell, and now it is on my
  street, and I still cannot tell
  you what it is.

  …I'm going to stop looking at
  it now.

  Every instrument in my window
  leans when it walks past.
```

**Mom** (`UBMom`), em (19,12) — mandaram ela entrar e ela não entrou.

```text
# NewBarkTown_Text_UBMomIdle
MOM
  I'm not going into the
  lab, {PLAYER}.

  Don't ask me again.

  I've been watching that road
  for two years.

  I know how to watch a road.
```

**Gold/Crystal** (`UBRival`), em (21,13). **Eles pedem para entrar na luta
aqui, cedo.** A recusa vem depois, na câmera, e quem derruba a recusa também.
As três metades são uma coisa só — não apague nenhuma.

```text
# NewBarkTown_Text_UBRivalIdle
  Every house on this street,
  twice.

  The Hanlons wouldn't open the
  door until I said your name.

  Which is the story of the last
  two years, honestly.

  Hey - when it starts, put me
  in.

  I've got a full team. I've had
  a full team for a year, and I
  have never once been in the
  room where it mattered.
```

**Anabel** (`UBAnabel`), em (22,12) — só alcançável pela volta longa, por y=14.
Ela **não planta nada** aqui e **não se explica** aqui: isso tudo aconteceu em
Olivine, no briefing. Nesta estrada ela está trabalhando.

```text
# NewBarkTown_Text_UBAnabelIdle
ANABEL
  Three signatures, and
  they are breathing together.

  In, and out.

  I told you in Olivine what that
  does to me. I won't say it
  twice on an open road.

  Stay on this street.

  If I tell you to move, move
  first and ask me after.
```

---

## Ato 3 — O convite do Looker (o último ponto de saída)

A contagem do Elm é lida **antes** do SIM de propósito: é o relógio que
transforma "três fendas" em "agora" — o mesmo trabalho que a leitura da Lillie
fez na M2 e a do Kukui na M3.

Mas o Elm ainda está em (11,10), nove tiles a oeste e **fora da câmera**: por
isso é a **Anabel quem repassa** o log dele aqui, e o Elm só fala por si depois
de entrar em quadro. Não devolva a voz dele para cá sem mover o objeto também.

```text
# NewBarkTown_Text_UBLookerGreet
LOOKER
  {PLAYER}. Right on your
  own doorstep.

  I have worked a great many
  streets, and I have never liked
  one less than this.
```

```text
# NewBarkTown_Text_UBClockRelay
ANABEL
  The Professor called it
  in four minutes ago.

  Three minutes, he says. Maybe
  four - the interval has been
  shortening all morning.

  All three breathe together.

  He had six weeks of that on
  paper and called it a fault.

  It took a stranger in Alola one
  page to tell him it wasn't.

LOOKER
  And so we are here, on
  a road with no Pokémon Center,
  because a man in a laboratory
  was brave enough to be wrong in
  writing.
```

A pergunta (`MSGBOX_YESNO`):

```text
# NewBarkTown_Text_UBReady
LOOKER
  Worse than Cherrygrove.

  Worse than anything we have
  sent you into.

ANABEL
  Are you ready?
```

**NÃO:**

```text
# NewBarkTown_Text_UBNotReady
LOOKER
  Then take the time.

  Your mother is not moving,
  and neither am I.
```

**SIM →** a cena começa e não para mais.

---

## Ato 4 — A cena

`lockall` + `hidefollower`.

### Beat 1 — Elm e Lusamine entram em quadro (debaixo do fade)

`FADE_TO_BLACK` → os dois são **reposicionados pelo template**, não por
`setobjectxy` (que falharia em silêncio fora da câmera; ver o `_IMPLEMENTATION`):

| Quem | De → para | Olhar final |
|---|---|---|
| Elm | (11,10) → (23,12) | oeste, para a fila de gente |
| Lusamine | (3,12) → (18,12) | leste, para a Mom e o jogador |

`FADE_FROM_BLACK`.

```text
# NewBarkTown_Text_UBTheyArrive
LUSAMINE
  Professor. Your log.

  You kept six weeks of a reading
  you were certain was wrong.

ELM
  I kept it because I
  thought it was wrong.

  That is not the same as being
  useful.

LUSAMINE
  Today it is exactly
  the same thing.

LOOKER
  Madame. Nobody told me
  you were coming.

LUSAMINE
  Nobody told me either,
  Inspector.
```

### Beat 2 — Três fendas de uma vez

Tremor **maior que o padrão** (pan 2/1, 32 tremidas) → `FADE_TO_WHITE` →
`addobject` das **três** Ultra Beasts ao mesmo tempo → `FADE_FROM_WHITE` → os
três gritos.

```text
# NewBarkTown_Text_UBAppear
LOOKER
  Three.

  Over the laboratory, over the
  road, over this street.

ELM
  That's them. That's the
  reading.

  Six weeks of it, standing in
  my town.
```

### Beat 3 — A sinergia, mostrada antes de explicada

As três andam **um tile a leste no mesmo instante**, de três cantos do mapa que
não se enxergam: `walk_slow_right` nas três de uma vez.

```text
# NewBarkTown_Text_UBSynergyFirst
ELM
  Wait.

  Wait, they all moved.

LUSAMINE
  Yes. Toward us. That is
  what they do.

ELM
  No, madame - they all
  moved at the SAME time.

  I have a clock. That is the
  only thing I am good for today.
```

De novo, igual.

```text
# NewBarkTown_Text_UBSynergyNamed
ELM
  Again. Same instant.

  There are two buildings between
  them. They cannot see each
  other.

ANABEL
  Then stop counting them
  as three.

  That is one thing wearing three
  bodies, and it has been doing
  it since Blackthorn.

LUSAMINE
  …In Alola they never
  did that.

  Not once. Not for me.
```

O Elm é quem percebe que é o **mesmo instante** — ele é o único na estrada com
um relógio na mão.

### Beat 4 — Perigo direto, e a primeira coisa que alguém consegue parar

`SE_PIN` + "!" sobre a Anabel. A Nihilego quebra a formação e corre os últimos
três tiles de y=13 até (19,13) — encostando diagonalmente no jogador e
**bem embaixo da Mom**, a única pessoa da estrada que mandaram entrar e não
entrou.

| Quem | De → para | Movimento |
|---|---|---|
| Nihilego | (16,13) → (19,13) | `walk_fast_right x3` |
| Azumarill | (22,13) → (19,14), **pela volta**, por y=14 | `walk_fast_down > walk_fast_left x3 > face_up` |

Os dois caminhos nunca dividem um tile. `UBShake`.

```text
# NewBarkTown_Text_UBCutOff
ANABEL
  MOVE!

NONE
  Azumarill, cut it off!
  Go around, go around!

ANABEL
  …It stopped.

  It came straight down the road
  at a fifteen-year-old and a
  woman who refused to go inside,
  and a Pokémon nobody asked for
  is what stopped it.

MOM
  I'm still not going
  inside.
```

### Beat 5 — O nó: a Lusamine quer levar as três, e a Mom a impede

Lusamine (18,12) → (17,12), um passo a oeste, na direção das fendas:
`walk_left > face_left`.

```text
# NewBarkTown_Text_UBLusamineTakesThree
LUSAMINE
  It went for your child.

  In front of you. In front of
  me.

  Three of them. Then I will take
  three.

  No - listen to me.

  I know what they are. I know it
  better than anyone standing on
  this road.

  Nobody else here has to go near
  them.
```

A **Mom vira as costas para a própria filha/filho** para encarar a Lusamine.
**A virada É o beat** — não encurte.

```text
# NewBarkTown_Text_UBMomStopsHer
MOM
  Ma'am.

  My child is standing right
  there, and I'm not going inside
  either, so I won't lecture you.

  But you're not protecting
  anyone.

  You're making sure that if it
  goes wrong, it goes wrong to
  you.

  I know the difference. I've
  wanted to do it too.

  Every week, for two years.

  And then one morning I stood at
  that door and let a ten-year-
  old walk to Cherrygrove alone.

  That's the part nobody tells
  you. Believing in somebody is
  worse than doing it yourself.

  It just happens to be the thing
  that works.

LUSAMINE
  …

  My daughter said something very
  close to that to me, once.

  I did not hear it either.
```

A Lusamine se vira para o leste e pergunta.

```text
# NewBarkTown_Text_UBLusamineAsks
LUSAMINE
  Very well.

  Then I will do the thing I am
  worst at.

  Anabel. What do your
  instruments give me?
```

### Beat 6 — A Anabel responde, e responder custa

Três fendas de uma vez é mais do que ela consegue encarar calada. Ela **não se
explica aqui** — duas caixas, e na terceira ela já voltou ao trabalho.

```text
# NewBarkTown_Text_UBAnabelBreaks
ANABEL
  They give me… they
  give me…

  …

LOOKER
  Chief. Chief.
```

`SE_PIN` + "!" sobre o Looker; ele se vira para ela (leste), espera, e depois
volta para o jogador (oeste).

```text
# NewBarkTown_Text_UBAnabelStands
ANABEL
  I'm here. Let go,
  Looker. I can stand.

  Three at once is loud.

  {PLAYER} knows why. I'm not
  saying it again in the middle
  of a road.

LOOKER
  You are not required
  to.
```

O que ela dá para a cena é o **contra** — e é o contra que transforma o menu
padrão "escolha uma Ultra Beast" num plano: três coisas que se movem num
instante têm de ser quebradas num instante, e isso precisa de um quarto par de
mãos.

```text
# NewBarkTown_Text_UBCounter
ANABEL
  Here is what the
  instruments give you, madame.

  One thing, three bodies, one
  instant.

  Break one and the other two
  carry it. Break two and the
  third one carries both.

  They have to go down in the
  same instant or they do not go
  down at all.

LUSAMINE
  Then I cannot take
  three.

ANABEL
  No. You take one, I
  take one, {PLAYER} takes one.

  And the one {PLAYER} takes is
  the one that has already tried
  for them once.

  It will not go down to one
  trainer.
```

### Beat 7 — O garoto entra

Paga a fala solta do Ato 2. Gold/Crystal viram para oeste (não há direção
cardinal que aponte para o jogador na diagonal; a coluna do jogador é o que
mais se parece com "virar para ele").

```text
# NewBarkTown_Text_UBRivalAsks
  Then take me.

  I asked first. I asked before
  any of you got here.

  My Azumarill is the reason that
  thing is still ten feet away.
```

A resposta é **não**, por um motivo que é sobre eles e não sobre o plano:

```text
# NewBarkTown_Text_UBRivalRefused
LOOKER
  You are the only person
  on this road who is not police,
  not Aether, and not the
  Champion.

ANABEL
  Forty people came back
  out of their houses because you
  knocked.

  If this goes badly they will
  need someone who knows which
  doors are which.

NONE
  …Right. Doors.

  It's always doors.
```

E quem derruba o não é a **Lusamine**, trinta segundos depois de ter ouvido que
decidir por todo mundo não é proteger. É esse o ponto da cena inteira: a Mom
ensina ela a perguntar, e a primeira coisa que ela faz com isso é **acreditar no
filho dos outros**.

```text
# NewBarkTown_Text_UBLusamineLetsHimIn
LUSAMINE
  No.

  Inspector, you are wrong, and I
  am the last person in Johto
  with the right to say so.

  I have spent my life deciding
  who was ready.

  I was told, four minutes ago,
  what that actually is.

  We need four. There are four of
  us standing here.

MOM
  Ma'am.

LUSAMINE
  I heard you the first
  time.
```

`SE_PIN` + "!" sobre Gold/Crystal.

```text
# NewBarkTown_Text_UBRivalIn
  …Say that again.

  No. Don't. If you say it again
  I'll cry, and I am NOT doing
  that in front of {PLAYER}.

  Azumarill! Back to me!

  We're in. We're actually in.
```

### Beat 8 — A escolha (três opções)

Quatro pessoas, três Ultra Beasts, um instante. A **Lusamine fica com a
Nihilego sempre que o jogador não a escolhe** — é a que ela veio buscar e a que
ela tem de responder por. Decisão de personagem, não conveniência:

| Escolha do jogador | Lusamine | Anabel |
|---|---|---|
| Kartana | Nihilego | Guzzlord |
| Guzzlord | Nihilego | Kartana |
| Nihilego | Guzzlord | Kartana |

Gold/Crystal são o quarto par de mãos **na que o jogador pegar**. Cada fala de
escolha **diz** quem fica com quem, para a tabela ser legível de dentro do jogo.

```text
# NewBarkTown_Text_UBChoosePrompt
LUSAMINE
  {PLAYER} - which one
  will you take?

  I am asking. I am not deciding
  it for you.

LOOKER
  Choose, {PLAYER}.

  Quickly, and then not again.
```

Opções: `  Kartana` / `  Guzzlord` / `  Nihilego`.
"!" sobre a escolhida, e:

```text
# NewBarkTown_Text_UBPickedKartana
LUSAMINE
  The blade.

  Then I take the one that
  matters to me, and Anabel takes
  the weight.

ANABEL
  Nihilego is hers.
  Guzzlord is mine.

NONE
  And I'm on the blade
  with {PLAYER}.

ANABEL
  On my mark. All four.
```

```text
# NewBarkTown_Text_UBPickedGuzzlord
LUSAMINE
  The mouth.

  Be careful - it does not stop
  because you are tired.

  I take Nihilego. It is the one
  I came for.

ANABEL
  Then the blade is
  mine.

NONE
  And I'm on the mouth
  with {PLAYER}.

ANABEL
  On my mark. All four.
```

O ramo em que a Lusamine **perde** a que veio buscar. Uma fala, e ela aceita —
não transforme isso numa discussão:

```text
# NewBarkTown_Text_UBPickedNihilego
LUSAMINE
  …That one was mine to
  answer for.

  No. That is exactly the
  sentence I promised my children
  I would stop saying.

  Thank you for taking it.

  I will take the mouth instead.

ANABEL
  And I'll take the
  blade.

NONE
  I'm going where
  {PLAYER} goes.

ANABEL
  On my mark. All four.
```

### Beat 9 — A batalha

Boss contra a escolhida, quarto degrau da escala. Números em
[`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md).

Se não termina em vitória, a cena inteira se desfaz — e o blackout devolve o
jogador **curado, em (20,12)**, que é o tile de falar com o Looker:

```text
# NewBarkTown_Text_UBGotAway
LOOKER
  It is still here.

  All three of them are still
  here.

ANABEL
  Back to the line,
  {PLAYER}. We go again.

  All four of us.
```

---

## Ato 5 — O plano funciona (e não adianta)

As lutas da Lusamine, da Anabel e do Gold/Crystal são narrativas: resolvem com a
vitória do jogador, e a fala muda com a escolha para a divisão em quatro ser
legível de dentro do jogo.

**As três Ultra Beasts NÃO são removidas aqui.** Elas estão caídas, não sumidas —
precisam continuar na estrada para o que vem recolhê-las.

```text
# NewBarkTown_Text_UBAfterKartana
ANABEL
  Down. All three, inside
  the same second.

LUSAMINE
  Mine folded the moment
  yours did.

  They came together and they
  fall together - of course they
  do.

NONE
  We did it. We actually
  did it.
```

```text
# NewBarkTown_Text_UBAfterGuzzlord
ANABEL
  Down. All three, inside
  the same second.

LUSAMINE
  You stood in front of
  that thing for how long?

  …Lillie was right about you.

  She is right a great deal
  lately.

NONE
  We did it. We actually
  did it.
```

```text
# NewBarkTown_Text_UBAfterNihilego
ANABEL
  Down. All three, inside
  the same second.

LUSAMINE
  I watched you do that.

  I made myself watch all of it.

  Thank you. I will not say it a
  third time, but I mean it more
  each time.

NONE
  We did it. We actually
  did it.
```

### A consequência

Mesma entrada das três missões anteriores — `UBShake`, flash branco, `addobject`
—, só que desta vez ela sai **na própria estrada**, em (16,12), um tile a oeste
da Lusamine, no meio da rua que ela vem abrindo há quatro missões.

```text
# NewBarkTown_Text_UBNecrozmaArrives
  The road opens.

  Not a tear this time. The air
  itself steps aside, and
  something walks out of it onto
  the street.

LOOKER
  …That is the thing from
  Blackthorn.

ELM
  It's on the ROAD. The
  others came out of the sky and
  that one used the road.

LUSAMINE
  I have seen light like
  that before.

ANABEL
  Madame.

LUSAMINE
  …Later.
```

### O garoto vai para cima

Ninguém mandou. E desta vez ninguém pode mandar parar — eles foram aceitos há
trinta segundos, e é isso que ser aceito parece para quem passou o jogo inteiro
se sentindo peça sobressalente.

```text
# NewBarkTown_Text_UBRivalCharges
  It's walking past them.

  It's not even looking at the
  three of them, it's-

  No. No, I got let in.

  AZUMARILL!
```

Azumarill (19,14) → (16,14), dois tiles ao sul da criatura
(`walk_fast_left x3 > face_up`), olha para o norte e bate duas
vezes (`walk_in_place_fast_up x2`) + grito → `UBFlash` → é jogado de
volta para (18,14) **sem se virar**, ainda encarando a coisa:
`lock_facing_direction > walk_fast_right x2 > unlock_facing_direction` → `UBShake`.

```text
# NewBarkTown_Text_UBRivalRepelled
ANABEL
  Get it back! Now!

NONE
  It's up. It's up, it's
  fine, it's-

  It didn't block. It didn't
  dodge. It didn't do anything.

LOOKER
  My friend, that was
  the bravest useless thing I
  have seen in twenty years of
  this work.

  Do not do it twice.
```

### Ela come as três

Mesmo padrão das missões 1, 2 e 3 — pulso, arrasto, flash, `removeobject` —
exceto que desta vez são **três**, e desta vez alguém na estrada faz a conta em
voz alta depois.

Necrozma `walk_in_place_fast_right x3` + grito. Arrastos, todos
medidos, nenhum cruzando o outro:

| Quem | De → para | Movimento |
|---|---|---|
| Kartana | (17,10) → (16,11), direto ao norte dela | `lock_facing_direction > walk_slow_left > walk_slow_down > unlock_facing_direction` |
| Nihilego | (19,13) → (17,13) | `lock_facing_direction > walk_slow_left x2 > unlock_facing_direction` |
| Guzzlord | (25,15) → (23,15) | `lock_facing_direction > walk_slow_left x2 > unlock_facing_direction` |

`UBShake` → `FADE_TO_WHITE` → `removeobject` das três → `FADE_FROM_WHITE` → grito.

```text
# NewBarkTown_Text_UBAbsorbed
ELM
  They're moving. They
  were down and they're moving.

ANABEL
  They are not moving.
  They are being moved.

LUSAMINE
  It is not fighting
  them.

  Inspector - it is not fighting
  them, it is COLLECTING them.

LOOKER
  Three at once.

  It took two in Blackthorn. Two
  at the Lake. Two on the beach.
```

---

## Ato 6 — O que ela vira

A criatura é removida e o **outro objeto é adicionado no mesmo tile (16,12)
debaixo de um flash só** — os dois nunca existem ao mesmo tempo.

```text
# NewBarkTown_Text_UBUltraRises
  The light does not go out this
  time.

  It folds. It keeps folding,
  into something with a shape,
  and the shape is standing in
  the middle of New Bark Town.

ANABEL
  Formation. NOW.

  Same mark. Same instant. It is
  the only thing that has worked
  all day.

LUSAMINE
  All four. Together.
```

Então os quatro fazem **exatamente o que funcionou dez segundos atrás** — o
mesmo instante, o mesmo plano: `walk_in_place_fast_left x2` em
Lusamine, Anabel, Gold/Crystal **e no jogador**, os quatro de uma vez.

E não adianta nada. É esse o ponto: o contra que quebrou as três não é nada
contra a coisa que estava recolhendo elas.

`walk_in_place_fast_right x4` → flash → tremor **maior que qualquer
outro da cena** (pan 3/2, 48 tremidas, delay 3).

```text
# NewBarkTown_Text_UBUltraBreaksThem
  It was over before any of them
  finished the motion.

  One light, across the whole
  road, at once.

ANABEL
  …Report.

  Somebody report. Anybody.

LUSAMINE
  I am on the ground,
  Chief.

  We are all on the ground.
```

### Reação opcional à família Cosmog

Checada **aqui** e não antes da batalha, de propósito: a batalha pode evoluir o
Pokémon. "!" sobre o jogador → `UltraFlare` → grito.

**Cosmog / Cosmoem:**

```text
# NewBarkTown_Text_UBUltraSensesCosmog
  It turns.

  Not to Lusamine, not to the
  police. To {STR_VAR_1}, which is
  the only thing on this road
  still standing up.

LUSAMINE
  Don't move. Don't you
  move, either of you.

ANABEL
  It is not going to
  take it.

LUSAMINE
  No. It is not.

  It is WAITING for it.
```

**Solgaleo / Lunala:**

```text
# NewBarkTown_Text_UBUltraSensesLegend
  It turns.

  {STR_VAR_1} stands up between
  the light and everyone lying in
  the road, and does not step
  back.

  And the thing in the street
  stops.

LUSAMINE
  …It knows that shape.

ANABEL
  Madame, it just
  hesitated. That thing flattened
  four trainers and it just
  hesitated.

LUSAMINE
  Write that down,
  Professor. Write exactly that
  down.
```

### A saída

Ela vai embora do jeito que chegou, e **ninguém a impede**.

```text
# NewBarkTown_Text_UBUltraGone
  It steps back into the place
  the road opened, and the road
  closes behind it.

  Nothing is broken. No house, no
  fence, no window.

  It never wanted the town at
  all.
```

---

## Ato 7 — A cidade de pé, a missão perdida

**Ninguém anda.** Todo mundo já está na linha e ninguém está em (20,13), então a
caixa de texto não esconde ninguém. O Azumarill fica em (18,14) e a Lusamine em
(17,12), onde a luta deixou os dois — é essa a fotografia que a cena quer.

A ordem das caixas **é o argumento**: as pessoas primeiro (Looker, sempre),
depois o custo, depois o que aquilo era, depois os três que têm de continuar
morando nesta cidade, depois a promessa — a única coisa que ainda sobrou —, e só
então o gancho.

```text
# NewBarkTown_Text_UBAftermathHurt
LOOKER
  Is anyone hurt?

  {PLAYER}? Your Pokémon?

  Chief? Madame?

  …And you. The one with the
  Azumarill. Look at me when I
  ask you.

  …Good. Good.

  The report can wait a moment.
```

```text
# NewBarkTown_Text_UBElmCost
ELM
  The sensors are gone.

  Every one of them. Melted, or
  whatever that was.

  …I don't mind. I have six weeks
  of data.

  The last thirty seconds of it
  are three signatures going into
  one signature.

  Three into one. I watched a
  number do that.
```

```text
# NewBarkTown_Text_UBWhatItWas
ANABEL
  Nine.

LOOKER
  Chief?

ANABEL
  Nine Ultra Beasts.
  Blackthorn, the Lake, the
  beach, this road.

  It has been at every one of
  them, and it has left with
  every single one of them.

  It was never attacking Johto.

  It was never attacking us at
  all.

LOOKER
  …It was collecting.

ANABEL
  And we softened them
  for it. Four times.

  Put that in the report, Looker.

  Put that in first.
```

```text
# NewBarkTown_Text_UBLusamineLost
LUSAMINE
  We held the street.

  Not one person on it is hurt,
  and not one window is broken,
  and I want that said plainly
  before anything else.

  And we lost.

  It came for something, it took
  it, and it walked out.

  I have been on the other end of
  a plan like that.

  You do not notice it is a plan
  until it is finished.
```

Gold/Crystal viram para a coluna do jogador:

```text
# NewBarkTown_Text_UBRival
  I got in.

  I finally got in, and I hit it
  with everything I've got, and
  it didn't even turn its head.

LUSAMINE
  Neither did mine.

  Neither did the Champion's.

  That is not a thing that
  happened to you. That is a
  thing that happened to all of
  us, and you were in it.

NONE
  …Yeah.

  Yeah, okay.

  Right. Doors. Forty people to
  let back out.
```

A Mom volta a encarar a própria filha/filho (leste):

```text
# NewBarkTown_Text_UBMom
MOM
  Come inside when you can.

  I'll leave the light on.

  You know I will.
```

```text
# NewBarkTown_Text_UBAnabelPromise
ANABEL
  {PLAYER}.

  What I told you in that office,
  before any of this.

  Everyone who comes through gets
  a hand. Everyone who goes in
  comes home.

  We lost the road today. We did
  not lose that.

  Both. Always both.
```

Com a família Cosmog na equipe — a Lusamine diz **sem ninguém perguntar**, e diz
a outra metade também: que nada disso é obra do jogador.

```text
# NewBarkTown_Text_UBAftermathCosmog
LUSAMINE
  {PLAYER}.

  It looked at {STR_VAR_1} and it
  chose to leave.

  I have never once known that
  thing to leave something it
  wanted.

  Keep them close. Not because
  they are in danger.

  Because they are the only
  reason it stopped.
```

### O gancho

```text
# NewBarkTown_Text_UBHook
ANABEL
  Looker. They didn't
  scatter.

  It left on a bearing, and the
  three rifts closed toward the
  same one.

  I can put a place on a map now.

  I have never once been able to
  do that.

LOOKER
  Then the investigation
  is finished, and something else
  begins.

LUSAMINE
  Inspector. Call my
  children. Both of them.

  And Professor Kukui - he has
  earned the room twice over
  without ever setting foot in
  it.

  Not as Aether.

  I owe these people an
  accounting, and two of them are
  mine.

LOOKER
  Olivine, then.

  All of us, in that small room.

  I apologise in advance for the
  chairs.

  {PLAYER} - bring your partner.

  Not for a test.

  Everyone in that room has been
  waiting a long time to meet
  them.
```

`FADE_TO_BLACK` → a flag do evento é limpa, o estado vira 10 → `warpsilent` no
mesmo lugar (20,12). Os sete moradores voltam, as lâmpadas voltam a depender só
do relógio, o elenco some, Elm e Lusamine voltam aos tiles de template e o
follower volta — tudo debaixo do fade.

---

## Apêndice — movimentos, em um lugar só

| Label | Sequência |
|---|---|
| `NewBarkTown_Movement_StepLeftFaceLeft` | walk_left > face_left |
| `NewBarkTown_Movement_UBDrift` | walk_slow_right |
| `NewBarkTown_Movement_NihilegoLunge` | walk_fast_right x3 |
| `NewBarkTown_Movement_AzumarillCutOff` | walk_fast_down > walk_fast_left x3 > face_up |
| `NewBarkTown_Movement_AzumarillCharge` | walk_fast_left x3 > face_up |
| `NewBarkTown_Movement_StrikeUp` | walk_in_place_fast_up x2 |
| `NewBarkTown_Movement_StrikeWest` | walk_in_place_fast_left x2 |
| `NewBarkTown_Movement_AzumarillThrown` | lock_facing_direction > walk_fast_right x2 > unlock_facing_direction |
| `NewBarkTown_Movement_UBPulledInWest` | lock_facing_direction > walk_slow_left x2 > unlock_facing_direction |
| `NewBarkTown_Movement_KartanaPulledIn` | lock_facing_direction > walk_slow_left > walk_slow_down > unlock_facing_direction |
| `NewBarkTown_Movement_NecrozmaPulse` | walk_in_place_fast_right x3 |
| `NewBarkTown_Movement_UltraFlare` | walk_in_place_fast_right x4 |

**Flash da cena:** `fadescreenswapbuffers FADE_TO_WHITE` / `FADE_FROM_WHITE`,
nunca `fadescreen`.

**Tremores, em escala crescente:**

| Momento | pan v/h | tremidas | delay |
|---|---|---|---|
| Padrão (`UBShake`) | 1 / 1 | 12 | 4 |
| As três fendas abrindo | 2 / 1 | 32 | 4 |
| O golpe que põe os quatro no chão | 3 / 2 | 48 | 3 |
