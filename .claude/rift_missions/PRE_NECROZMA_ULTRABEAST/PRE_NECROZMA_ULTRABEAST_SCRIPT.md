# Pré-Necrozma — a reunião de Olivine — roteiro

**O que é este arquivo:** a cena como ela acontece na tela — as falas literais
(em inglês, exatamente como estão na ROM) e a coreografia, beat a beat.
Estado, flags, objetos, orçamento, arquivos tocados e checklist de teste ficam em
[`PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md).

**Fonte:** `data/maps/OlivineCity_House1/scripts.pory`.
Ao mudar uma fala, mude no `.pory` e traga a mudança para cá.

**O que esta cena é:** não tem batalha, não tem Ultra Beast e não tem fenda. É a
sala pequena onde todo mundo do arco se encontra depois da derrota de New Bark,
a única do arco em que eles **não** estão trabalhando — e é onde o jogo faz a
**única checagem de time do arco inteiro**: Solgaleo **ou** Lunala, na equipe.

---

## Elenco e marcação

```text
       x= 0  1  2  3  4  5  6  7  8  9 10
  y= 2   .  .  .  .  .  .  .  .  .  .  .     fora da câmera
  y= 3   .  .  .  .  .  .  .  .  .  .  .     fora da câmera
  y= 4   .  .  .  .  .  #  #  .  .  .  .     a mesa (5-6, 4-5) é sólida
  y= 5   .  .  .  .  L  #  #  A  .  .  .     L Looker (4,5)      A Anabel (7,5)
  y= 6   .  .  N  I  .  .  .  .  .  U  .     N Ninetales (2,6)   I Lillie (3,6)   U Lusamine (9,6)
  y= 7   .  .  S  G  .  .  .  .  K  .  .     S Silvally (2,7)    G Gladion (3,7)  K Kukui (8,7)
  y= 8   #  .  .  .  W  .  .  .  .  .  #     W porta (4,8): único warp, e onde o jogador fica
  y= 9   #  #  #  #  #  #  #  #  #  #  #
```

**A encenação é a distância.** Os dois irmãos e os parceiros deles ficam num
bloco 2x2 à esquerda; a **Lusamine fica sozinha do outro lado da sala**,
encostada na parede leste. Não é conveniência: é a distância que a conversa de
família **não** resolve.

**Ninguém fica ao sul do jogador**, então a caixa de texto não cobre ninguém. A
coluna do jogador é x=4: quem está a oeste (x=2,3) olha para **leste**; quem
está a leste (x=8,9) olha para **oeste**.

---

## Ato 1 — A chegada (estado 10)

O jogador entra pela porta (4,8). "!" sobre o Looker, e os dois descem pelos
**mesmos** caminhos dos quatro briefings:

| Quem | De → para | Movimento |
|---|---|---|
| Looker | (4,5) → (4,7) | `walk_down x2 > face_down` |
| Anabel | (7,5) → (5,7) | `walk_down x2 > walk_left x2 > face_down` |

**Ninguém volta para o lugar no fim.** Nos quatro briefings os dois caminhavam de
volta; aqui a reunião **continua acontecendo** depois que a caixa fecha, e os
dois ficam onde pararam até o próximo load. A porta não fica bloqueada porque o
jogador termina a cena **em cima** dela.

A cena longa roda **uma vez só**: ela sempre termina no estado 11 ou 12, e
nenhum dos dois volta a entrar nela. É a lição da M4 aplicada antes de custar
caro — a versão longa toca uma vez, e "seu parceiro já evoluiu?" é um ramo curto.

---

## Ato 2 — A conversa

### 1. O Looker fecha o relatório de New Bark e dá nome à sala

```text
# OlivineCity_House1_Text_ReunionOpen
LOOKER
  {PLAYER}. Come in.

  Mind the chairs - there are
  not enough of them, and I
  have stopped apologising.

  New Bark holds. Four in four,
  and I am not certain that is
  the word for it.

  The file is closed. What is in
  it is worse than what we
  opened it for.

  Which is why everyone in this
  room came when I asked.

  Look at them. I did not have
  to explain twice.
```

### 2. O Kukui: a marcação da Anabel mais as seis semanas do Elm viraram um LUGAR

Ele já está olhando para o oeste, para dentro da sala — não precisa de `turnobject`.

```text
# OlivineCity_House1_Text_ReunionKukui
KUKUI
  Your rifts closed
  toward one bearing.

  Anabel's number, Elm's six
  weeks of it, my rhythm.

  Three wrong tools, one
  answer.

  There's a place out there,
  {PLAYER}. An altar.

  We can put a boat on it.
```

### 3. A Lusamine diz por que pediu essa reunião

```text
# OlivineCity_House1_Text_ReunionLusamineCalled
LUSAMINE
  I asked the
  Inspector to call this
  meeting.

  Not as Aether. Aether would
  have sent a report.

  I owe the people in this room
  an accounting, and two of
  them are mine.
```

### 4. Os dois irmãos se olham

Lillie (3,6) e Gladion (3,7) estão na **mesma coluna**, um tile de distância —
então dá para eles olharem **um para o outro**. Como y cresce para baixo, a
Lillie vira para **sul** e o Gladion para **norte**.

```text
# OlivineCity_House1_Text_ReunionLillie
LILLIE
  …You asked for us.
  Both of us.

  I'm not going to pretend
  that's nothing.

  It isn't nothing.
```

```text
# OlivineCity_House1_Text_ReunionGladion
GLADION
  We'll do the
  accounting after.

  Whatever is at that altar, it
  doesn't wait for our family
  to sort itself out.
```

Os dois voltam para **leste**, encarando a sala e a mãe.

```text
# OlivineCity_House1_Text_ReunionCross
LUSAMINE
  Then let me say the
  rest of it plainly.

  I intend to cross.

  I have been on the other side
  of a door like that one.

  Nobody else in this room has.
```

### 5. A condição

A Anabel vira para **leste** para dizer, e volta para **sul** depois.

```text
# OlivineCity_House1_Text_ReunionCondition
ANABEL
  You have. I have as
  well, and I came back wrong,
  and I told you all so in New
  Bark.

  So here is my condition,
  Madame, and it is not
  negotiable:

  Nobody crosses without a way
  back.

  Not you. Not me.
  Not the Champion.
```

---

## Ato 3 — A única checagem de time do arco

`checkspecies SPECIES_SOLGALEO`, depois `checkspecies SPECIES_LUNALA`. **Duas
checagens, nunca uma, e nunca uma checagem da família.** Só conta o que está na
**equipe**: no PC não vale, Pokédex não vale, Cosmog e Cosmoem não passam, e
nenhuma evolução acontece aqui.

Esta pergunta é alcançada de três lugares — da cena longa, do gatilho do estado
11 e dos scripts de objeto do Looker e da Anabel —, então ela tem de se ler
sozinha.

```text
# OlivineCity_House1_Text_ReunionAsk
ANABEL
  And a way through
  needs something that can open
  it.

  Not a machine. We tried
  machines for six weeks.

LOOKER
  {PLAYER}. Your
  partner.

  The one that started as an
  egg.

  May we see them?
```

### Ainda não

Nada é gasto: nenhuma missão é refeita, ninguém sai da sala, e a única coisa que
muda é 10 → 11 — que é o que impede a cena longa de tocar de novo.

```text
# OlivineCity_House1_Text_ReunionNotYet
LOOKER
  …Ah. Not yet.

KUKUI
  That's not a no!
  That's a “give it time”.

  It's still growing into what
  it's going to be.

LOOKER
  Then we prepare, and
  you raise them.

  Come back when they have
  finished becoming Solgaleo
  or Lunala.

  We are not going anywhere.

  Frankly, there is nowhere for
  six people to go in this
  room.
```

### Confirmado

A sala reconhece o Pokémon que saiu do ovo que o Gladion entregou em Violet.

```text
# OlivineCity_House1_Text_ReunionSeeIt
LOOKER
  …Oh.

ANABEL
  That is it.

  That is the reading, standing
  in a living room in Olivine.
```

```text
# OlivineCity_House1_Text_ReunionGladionEgg
GLADION
  I handed you that
  egg in Violet and told you to
  keep it away from people
  like us.

  You did better than that.
  You raised it.
```

```text
# OlivineCity_House1_Text_ReunionLillieProud
LILLIE
  I knew the whole way.

  Every time we met, I knew.

  I just wanted to be here when
  somebody finally said it out
  loud.
```

```text
# OlivineCity_House1_Text_ReunionLusamineKnows
LUSAMINE
  That light is what
  opens the way.

  I am the only person alive
  who knows what it looks like
  from the other side.

  Thank you for not letting me
  do this alone.

  I am told that is the lesson.
```

```text
# OlivineCity_House1_Text_ReunionWayBack
ANABEL
  My condition stands.

  We go together, and we come
  back.
```

### O gancho para o altar

```text
# OlivineCity_House1_Text_ReunionHook
LOOKER
  Then it is settled.

  There is a ship at the
  Olivine port, and it is ours
  for as long as this takes.

  We sail for the altar,
  {PLAYER}.

  You, your partner, and
  everyone in this room who can
  keep up.

  Come to the port when you are
  ready. Rest first.

  Whatever is waiting at that
  altar has waited a long time.

  It can wait for you to heal.
```

### O passe da balsa

Item-chave — a mochila não pode estar cheia. O marinheiro do porto só oferece a
rota do altar para quem carrega isso.

```text
# OlivineCity_House1_Text_ReunionTicket
LOOKER
  One more thing.
  Take this.
```

`giveitem ITEM_SUN_MOON_TICKET`

```text
# OlivineCity_House1_Text_ReunionTicketUse
  Show it to the sailor at the
  port. He will take you to the
  altar, and bring you back.
```

`FADE_TO_BLACK` → `setflag FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` (**nunca
limpada**) + `setvar VAR_RIFT_MISSIONS_STATE, 12` → `warpsilent` para **(4,7)**,
e não (4,8): não se faz o jogador renascer em cima do único warp da sala. Os
seis visitantes somem (foram na frente para o porto), Looker e Anabel voltam aos
tiles de template e o follower volta.

---

## Ato 4 — Conversas soltas (estado 11)

O estado 11 é o **único** em que o jogador anda pela sala com todo mundo
presente: no 10 a cena roda na chegada e no 12 eles já não estão mais lá.

**Lusamine:**

```text
# OlivineCity_House1_Text_IdleLusamine
LUSAMINE
  I will not pace.

  Pacing is for people without
  instruments.
```

**Lillie:**

```text
# OlivineCity_House1_Text_IdleLillie
LILLIE
  Take your time with
  them.

  I mean it - that's not a
  polite thing to say, it's the
  actual advice.
```

**Gladion:**

```text
# OlivineCity_House1_Text_IdleGladion
GLADION
  Go and train.

  That's not an insult, it's
  what I'd be doing.
```

**Kukui:**

```text
# OlivineCity_House1_Text_IdleKukui
KUKUI
  Six weeks of bad data
  and one good afternoon!

  Science, {PLAYER}!
```

A Ninetales e o Silvally têm `"script": "NULL"`: são os parceiros fora da bola
dos donos, dividem a flag de visibilidade com eles e **vêm e vão juntos**.

Falar com o Looker ou com a Anabel no estado 10 entra na cena longa; no estado
11, na pergunta.

---

## Ato 5 — Depois que o passe é entregue (estado ≥ 12)

Repetível de propósito: quem salvou e voltou tem de poder perguntar para onde ir.

**Looker:**

```text
# OlivineCity_House1_Text_LookerAltar
LOOKER
  The ship is at the
  port whenever you are ready,
  {PLAYER}.

  Madame Lusamine went ahead.
  Of course she did.
```

**Anabel:**

```text
# OlivineCity_House1_Text_AnabelAltar
ANABEL
  We leave when you do,
  not before.

  And we come back.

  That part is the whole plan.
```

---

## Ato 6 — A sala depois de tudo (estado ≥ 16)

Os três que voltam. **Não há batalha nenhuma nesta sala no pós-jogo:** este é o
lugar onde eles não estão trabalhando.

**Lusamine:**

```text
# OlivineCity_House1_Text_HouseLusaminePost
LUSAMINE
  The Inspector left us the key and a
  note asking us not to reorganise
  anything.

  I have reorganised three things.

  …Sit down, {PLAYER}. Nobody here is
  going anywhere for several hours, which
  I understand is what people do.
```

**Lillie:**

```text
# OlivineCity_House1_Text_HouseLilliePost
LILLIE
  Two days a week. That's what we agreed
  on -- two days, here, no instruments, no
  reports.

  The first one was terrible. We all sat in
  different corners.

  This is the fourth one. It's getting
  better. It's allowed to take a while.
```

**Gladion:**

```text
# OlivineCity_House1_Text_HouseGladionPost
GLADION
  I'm not good at this part.

  …Silvally likes it. Look at him. He's
  asleep under the table where Looker
  used to put his files.

  If he's fine with it, I'm fine with it.
  That's the system I'm using.
```

---

## Apêndice — movimentos, em um lugar só

| Label | Sequência |
|---|---|
| `OlivineCity_House1_Movement_LookerApproach` | walk_down x2 > face_down |
| `OlivineCity_House1_Movement_AnabelApproach` | walk_down x2 > walk_left x2 > face_down |
| `OlivineCity_House1_Movement_LookerReturn` | walk_up x2 > face_down |
| `OlivineCity_House1_Movement_AnabelReturn` | walk_right x2 > walk_up x2 > face_down |

Os dois `Return` **não** são usados pela reunião — continuam no arquivo para os
quatro briefings das missões.
