# Altar do Sol e da Lua — Ultra Necrozma — roteiro

**O que é este arquivo:** o evento como ele acontece na tela — as falas literais
(em inglês, exatamente como estão na ROM) e a coreografia, ato a ato.
Estado, flags, objetos, tileset, orçamento, arquivos tocados, riscos e checklist
de teste ficam em
[`ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON_IMPLEMENTATION.md).

**Fonte:** `data/maps/OlivineCity_PortInside/scripts.pory`,
`data/maps/SunMoonAltar/scripts.inc`, `data/maps/UltraSpaceArena/scripts.inc`.
Ao mudar uma fala, mude no `.inc`/`.pory` e traga a mudança para cá.

**O que este evento é:** o fecho do arco. Cinco atos, dois mapas, **uma** batalha
de treinador que não pode ser perdida de verdade e **uma** boss battle que pode.
Pela primeira vez no arco o que trava a história **não é uma criatura, é um
desacordo entre pessoas** — e quem desempata é o jogador.

---

## Marcação do altar

```text
      x= 8  9 10 11 12 13 14 15 16 17 18 19 20
  y= 4     #  #  #  #  #  #  #  #  #  #  #  #  #    o paredão e o disco
  y= 5     #  #  #  #  #  D  D  D  #  #  #  #  #    D = disco (13..15, 5..6)
  y= 6     #  #  #  #  #  D  D  D  #  #  #  #  #
  y= 7     #  #  #  #  #  #  d  #  #  #  #  #  #    d = base do disco (14,7)
  y= 8     #  #  #  #  #  #  #  #  #  #  #  #  #
  y= 9     #  #  .  .  .  .  U  .  .  .  .  #  #    U = Lusamine (14,9)
  y=10     #  #  .  .  .  .  R  .  .  .  .  #  #    R = A FENDA (14,10), objeto
  y=11     #  #  .  N  I  .  .  .  G  S  .  #  #    N Ninetales(11) I Lillie(12)
  y=12     #  #  #  #  #  .  .  .  #  #  #  #  #        G Gladion(16) S Silvally(17)
  y=13     .  #  .  #  .  L  .  A  .  #  .  #  .    L = Looker (13,13)
  y=14     .  .  K  .  .  .  .  .  .  .  .  .  #    A = Anabel (15,13)
  y=15     #  #  #  #  T  T  T  T  T  #  #  #  #    K = Kukui (10,14)
  y=16     .  .  .  .  .  .  .  .  .  .  .  .  .    T = gatilhos dos Atos I e V
```

- O **pescoço** em y=12 tem três tiles: é por onde se sobe e desce do terraço.
- A **escada** em y=15 tem cinco tiles (12..16): é a única entrada pelo sul, e os
  cinco `coord_event` cobrem 100% das chegadas.
- **Ninguém fica ao sul do jogador** nas caixas dos Atos I e V.
- A Lusamine entra olhando **para cima**, para o disco — e é isso que a fala
  final dela desfaz.

---

## Ato 0 — O cais de Olivine

O passe da balsa vem do Looker, no fim da reunião. O marinheiro tem uma rede de
segurança: se o save foi feito depois da reunião mas antes de o item existir,
ele entrega o passe ali mesmo.

```text
SAILOR
  Oh! A man in a trench coat left
  this here for you.
```

Com só o passe do altar, é um sim/não; com o de Faraway Island também, vira menu
("Sun & Moon Altar" / "Faraway Island" / "Cancel").

```text
SAILOR
  Ah, the Sun & Moon Ticket!
  Shall we set sail for the altar?

  {PLAYER} flashed the
  Sun & Moon Ticket.

  Anchors aweigh! Next stop,
  the Sun and Moon Altar!
```

O navio larga o jogador no cais do altar, em (14,27), ao lado do marinheiro que
faz a volta.

---

## Ato I — A chegada (estado 12 → 13)

Dispara ao subir a escada. O jogador sempre está um tile ao sul do terraço, em
qualquer x de 12 a 16.

**Nada aqui usa `faceplayer`:** numa cena automática `gSelectedObjectEvent` é
indefinido e o `faceplayer` viraria um objeto qualquer. Todo olhar é um
`turnobject` explícito, com direção derivada das coordenadas.

### Beat 1 — Sobe e olha

Jogador `walk_up > face_up`. Looker e Anabel viram para o
sul; o Kukui, que está na mesma linha a oeste, vira para leste.

```text
# SunMoonAltar_Text_ArrivalDisc
  The disc above the altar is turning.

  There is no wind.
```

### Beat 2 — A autoridade tenta e falha

O instrumento do Kukui não está errado: está **sendo lido por outra coisa**.

```text
# SunMoonAltar_Text_ArrivalKukui
KUKUI
  Six weeks I spent on this thing. Two
  moving parts and a whole lot of hope.

  Look at the needle, {PLAYER}. It's flat.
  Not zero -- flat. Like something else is
  already holding the number still.

  That's not a reading going wrong.
  That's a reading being taken. By
  something that isn't me.
```

`fadeoutbgm 4`.

```text
# SunMoonAltar_Text_ArrivalAnabel
ANABEL
  It isn't opening.

  It's open. It has been open a great
  deal longer than we have been standing
  here.

  Don't ask me how I know that. You were
  on the beach in Cherrygrove. You
  already know how I know.
```

```text
# SunMoonAltar_Text_ArrivalLooker
LOOKER
  Then we are neither early nor late. We
  are merely… present.

  …Forgive me. That was going to sound
  considerably better than it did.
```

### Beat 3 — O disco deixa de ser disco

`playbgm MUS_DP_LEGEND_APPEARS, TRUE` → `Shake` → `FADE_TO_WHITE` →
`DiscToPortal` (`setmetatile`, não `map.bin`) → `FADE_FROM_WHITE` →
`setweather WEATHER_VOLCANIC_ASH`: a cinza começa a cair.

```text
# SunMoonAltar_Text_ArrivalTurns
  The face of the disc stopped being a
  face.

  Ash began to fall across the altar --
  and half of it fell upward.
```

### Reação opcional do parceiro

Sem nada da família Cosmog na equipe a cena é idêntica e nada falta. "!" sobre o
jogador, e:

**Cosmog / Cosmoem:**

```text
# SunMoonAltar_Text_PartnerStirsSmall
  {STR_VAR_1}'s Poké Ball shook once,
  hard, and went still.

  It has never done that before.
```

**Solgaleo / Lunala:**

```text
# SunMoonAltar_Text_PartnerStirsLegend
  {STR_VAR_1} came out of its Ball without
  being asked.

  It did not look at the ash, or at the
  people. It looked straight up, at the
  hole where the disc used to be, and it
  did not blink.
```

### Beat 4 — Os irmãos

"!" sobre o Gladion.

```text
# SunMoonAltar_Text_ArrivalGladionBack
GLADION
  Silvally. Back. All the way back.

  Nobody goes up those steps. Not to
  look, not to measure, not for one
  second.
```

```text
# SunMoonAltar_Text_ArrivalLillieDoor
LILLIE
  That isn't a door any more.

  A door has two sides that agree with
  each other about where they are.

  Whatever is on the other side of that
  isn't agreeing with anything.
```

### Beat 5 — A oferta

A Lusamine desce do terraço, (14,9) → (14,11):
`walk_down x2 > face_down`. Os dois filhos viram para ela —
Lillie para leste, Gladion para oeste: os dois **flanqueiam a mãe**.

```text
# SunMoonAltar_Text_ArrivalOffer
LUSAMINE
  Then I will go first.
```

```text
# SunMoonAltar_Text_ArrivalOfferWhy
LUSAMINE
  I would like to be precise about my
  reasons, because I was imprecise about
  them once and other people paid the
  invoice.

  I am not offering because I am brave. I
  am offering because I am the correct
  person to spend.

  There is an unstable passage on this
  island. The reason anyone is standing
  beside it at all is that I spent a great
  many years teaching the world to want
  what is on the other side of one.
```

```text
# SunMoonAltar_Text_ArrivalOfferCost
LUSAMINE
  I have sent other people's children
  through doors, and called it a
  programme.

  Two of the children were mine.

  So I will go, and I will go alone, and if it
  shuts behind me it shuts behind the
  woman who opened the subject. That is
  not tragedy. That is bookkeeping.
```

### Beat 6 — Os filhos

```text
# SunMoonAltar_Text_ArrivalLillieNo
LILLIE
  No.

  …I'm sorry. I said that faster than I
  meant to.

  I'm not sorry for saying it.
```

```text
# SunMoonAltar_Text_ArrivalLillieNoTwo
LILLIE
  Mother, you are doing it again. You
  decided, and then you came here to tell
  us, and you dressed it up so well that it
  sounded like an apology.

  You are allowed to be the one who goes.

  You are not allowed to be the one who
  decides that by yourself. Not any more.
  Not with us standing right here.
```

O Silvally se mexe no lugar (`Common_Movement_WalkInPlaceFasterLeft`).

```text
# SunMoonAltar_Text_ArrivalGladionNo
GLADION
  I'm not arguing with her. I've done
  that. It doesn't work.

  I'm just not moving.

  The last time you went looking for
  something like this, it took us years to
  find our way back to each other. You
  want to spend yourself? Get in line.
  It's a long line and I'm at the front of
  it.
```

```text
# SunMoonAltar_Text_ArrivalAnabelCondition
ANABEL
  Madame. My condition from Olivine has
  not changed and it is not going to
  change on a beach in the middle of the
  sea.

  Nobody crosses without a way back. Not
  you. Not me. Not the Champion.

  And nothing on this island is a way back
  yet. That is a hole. A door is something
  else.
```

### Beat 7 — Ela volta a olhar para a porta

`walk_up x2 > face_up` — de volta a (14,9), olhando para cima.

```text
# SunMoonAltar_Text_ArrivalLusamineWaits
LUSAMINE
  Then we appear to have reached an
  impasse, and I am going to stand here
  and look at it until somebody moves.

  I have always been very good at this
  part.
```

### Beat 8 — O Looker passa a bola para o jogador

Ele dá **um passo para o oeste**, para fora da discussão — a encenação da fala
dele: `walk_left > face_down`.

```text
# SunMoonAltar_Text_ArrivalLookerAside
LOOKER
  {PLAYER}. A word, if I may.

  Four of my colleagues have now
  explained to me what happens next, and
  no two of them agree.

  This is not a police matter. I have
  nothing to arrest, and nobody to
  protect anybody from, and I have never
  in my career been less useful.
```

```text
# SunMoonAltar_Text_ArrivalLookerHand
LOOKER
  Madame Lusamine will not be talked out
  of this by her children. I have watched
  them try. I will not ask them to try
  again.

  She might listen to somebody with
  nothing to prove and nothing to
  apologise for.

  Go and speak with her. Take as long as
  you need. Nothing here is going
  anywhere -- which is, regrettably, the
  entire problem.
```

E volta: `walk_right > face_down`.

**Sem warp e sem batalha.** O ato acaba com o jogador **solto** no pátio, no meio
de uma discussão aberta — é o pedido literal do autor, e é a melhor coisa que
este evento faz. O estado vira 13 e o altar vira destino de Fly.

---

## Ato II — O duelo da Lusamine (estado 13 → 14)

Falar com ela. **Nada muda de estado antes do SIM.**

```text
# SunMoonAltar_Text_DuelApproach
LUSAMINE
  You walked up here instead of going
  round.

  Everybody else on this island has spent
  the last hour finding somewhere else to
  look.
```

```text
# SunMoonAltar_Text_DuelAsk
LUSAMINE
  You want to tell me I am wrong. Everyone
  does, today.

  I have been told I am wrong by my
  daughter, my son, a police inspector and
  a professor, and I am still standing
  exactly where I was.

  So don't tell me. Show me. Battle me,
  here, now, and let us find out whether
  the strongest person on this island is
  the one I keep refusing to listen to.
```

**NÃO** não custa nada — nenhuma flag, nenhuma var, nenhum movimento. Dá para ir
embora, curar, voltar e ser perguntado de novo, palavra por palavra:

```text
# SunMoonAltar_Text_DuelDeclined
LUSAMINE
  Sensible.

  I will be here. The passage is not in a
  hurry and neither, apparently, am I.
```

**SIM:**

```text
# SunMoonAltar_Text_DuelAccept
LUSAMINE
  Good.

  Do me the courtesy of trying.
```

### A batalha que não muda nada

Duelo **narrativo**: `B_FLAG_NO_WHITEOUT` ligada, sem blackout e sem penalidade,
e **os dois resultados levam ao estado 14**. A vitória do jogador não é o que
convence ela, e a derrota do jogador não para a história — **quem encerra a
discussão é a Lillie, em todos os ramos.**

Fala de derrota dela (`trainerbattle_no_intro`):

```text
# SunMoonAltar_Text_DuelLusamineBeaten
LUSAMINE
  …Ah.

  There it is.
```

**Venceu** — ela não é convencida por perder, é **interrompida** por perder:

```text
# SunMoonAltar_Text_DuelWon
LUSAMINE
  You did not win an argument. You won a
  battle. I am perfectly aware of the
  difference and I would thank you not to
  confuse them.

  But I asked to be shown, and I have
  been shown, and I am not a woman who
  asks a question twice.

  …It has been a long time since I lost to
  anyone who did not want something from
  me afterwards.
```

**Perdeu** — ela ganhou e não mudou nada, que é a cena melhor:

```text
# SunMoonAltar_Text_DuelLost
LUSAMINE
  And there we are. I am still right, and I
  am still going, and nothing on this
  island has changed.

  …Why does nobody look pleased? I won.
```

**Empate:**

```text
# SunMoonAltar_Text_DuelDrew
LUSAMINE
  Both of us on the ground at once. How
  appropriate.

  Neither of us proved a thing. Do note
  that I am counting that as my result as
  well.
```

**Desistiu:**

```text
# SunMoonAltar_Text_DuelForfeited
LUSAMINE
  You stopped.

  …Most people do not stop. They keep
  going until there is nothing left to go
  with. I have made an entire career out
  of not stopping.

  Perhaps that was the demonstration
  after all.
```

**Resultado inesperado** — esta cena é alcançada **falando** com ela, não por
gatilho de frame, então ela pode parar. Nada é marcado e é só falar de novo.
Nunca é vitória:

```text
# SunMoonAltar_Text_DuelUnexpected
LUSAMINE
  …Something went wrong with that, and I
  do not propose to pretend otherwise.

  Ask me again when you are ready. I have
  not moved in an hour and I do not intend
  to start now.
```

---

## Ato III — A fenda abre (dentro do desfecho do duelo)

A batalha **não** recarrega o mapa e ninguém se moveu durante ela. Se o jogador
estiver em (14,10) — um dos três tiles de onde se fala com a Lusamine, e
exatamente onde a fenda vai nascer — ele é empurrado um tile ao sul primeiro
(`walk_down > face_up`): um objeto sempre bloqueia o
próprio tile.

Lillie (12,11) → (13,11), olhando para cima:
`walk_right > face_up`.

```text
# SunMoonAltar_Text_DuelLillieEnds
LILLIE
  Mother. Look at me instead of at the
  disc. Just for this.

  You keep saying you are the correct
  person to spend. You are not spending
  anything. You are leaving.

  Spending would be staying here and
  being useful and letting somebody else
  be the brave one. That's the part
  you've never once done.
```

```text
# SunMoonAltar_Text_DuelLusamineYields
LUSAMINE
  …

  I had already decided what would be
  best for you. Again.

  Tell me your plan, Lillie. This time, I will
  listen.
```

```text
# SunMoonAltar_Text_DuelGladion
GLADION
  The plan is {PLAYER} goes through, we
  hold this side, and everybody comes
  back.

  That's the whole plan. It took us four
  cities to get this far. Don't make it
  complicated now.
```

### O parceiro responde ao altar

`playbgm MUS_DP_LEGEND_APPEARS, TRUE` → entra **exatamente um** dos dois
lendários, escolhido pelo que está de fato na equipe, em (13,10) → `Shake` →
`FADE_TO_WHITE` → `addobject` da **fenda** em (14,10) → `FADE_FROM_WHITE` →
`SE_WARP_IN`.

```text
# SunMoonAltar_Text_RiftOpens
  Something on the altar answered.

  A tear opened in the air above the
  stone floor, three paces from where
  Lusamine had been standing, and hung
  there, patient as a mouth.
```

```text
# SunMoonAltar_Text_RiftKukui
KUKUI
  Whoa. WHOA. Okay, okay -- needle's
  moving! Needle's moving and I do not
  like where it's going!

  That's not the disc any more, {PLAYER}.
  The disc was the lock. THAT'S the door.

  And it's sitting at ground level, on our
  side, and it opened when your partner
  looked at it. Write that down. Somebody
  write that down.
```

```text
# SunMoonAltar_Text_RiftAnabel
ANABEL
  Then we have a way through.

  Before anyone uses it: my rule, once,
  and then I will stop saying it.

  Room in your team for one more. If
  something on the other side needs to
  come back with us, it comes back with
  us. That is not caution. That is the
  entire job.
```

Estado 14 → `warpsilent` no lugar, para (14,14). **O parceiro não sobrevive a
esse warp, e é assim que tem de ser:** ele saiu para responder ao altar e voltou
para a bola. O Ato IV é quem o traz de volta.

---

## Ato III-b — A fenda, antes de atravessar

Falar com a fenda no estado 14, na ordem em que o script pergunta:

**1. A regra da Anabel, antes de qualquer oferta.** Equipe cheia **E** PC cheio
bloqueia — porque a cena do outro lado termina num `givemon`. Equipe cheia
**sozinha** não bloqueia: o `givemon` manda para a caixa sozinho. Checar aqui e
não na arena é deliberado: a alternativa é atravessar, vencer a luta mais difícil
do jogo e descobrir na última caixa que nada pode ser recebido.

```text
# SunMoonAltar_Text_RiftNoRoom
ANABEL
  Stop. Look at me.

  Your team is full and every box you own
  is full. I said room for one more and I
  meant it as a condition, not as advice.

  Go and make space, and come straight
  back. The passage has waited a long
  time. It can wait for a Pokémon Center.
```

**2. O parceiro.** É o "só se entra com o Solgaleo" do autor — e é um **portão,
não um enigma**: não custa nada, não muda nada e é repetível para sempre. Só vale
o que está na **equipe**: Cosmog, Cosmoem, ovo ou PC não satisfazem.

```text
# SunMoonAltar_Text_RiftNoPartner
ANABEL
  Not like that.

  The tear held still when your partner
  looked at it, and it is holding still now
  because of the light, and I am not
  sending anyone in there on a light that
  is sitting in a box in a Pokémon Center.

  Bring Solgaleo. Or Lunala. Whichever one
  yours chose to become. Then we go.
```

**3. O último ponto de saída.**

```text
# SunMoonAltar_Text_RiftAsk
LOOKER
  One more time, so that it is in the
  record and in your ears.

  Through there, and then back out
  through the same tear, and Madame
  Lusamine, Lillie, Gladion and the
  professor hold this end open while you
  do it.

  The Chief goes with you. I do not -- I
  have no Pokémon for a thing like that,
  and I have never been more honest
  about anything.

  Are you ready, {PLAYER}?
```

**NÃO:**

```text
# SunMoonAltar_Text_RiftNotYet
LOOKER
  Quite right. Prepare properly.

  I shall be here, holding a notebook and
  feeling largely decorative.
```

**SIM:**

```text
# SunMoonAltar_Text_RiftGo
ANABEL
  With me, then. Close. Don't stop in the
  middle of it, whatever it looks like in
  there.
```

---

## Ato IV — `MAP_ULTRA_SPACE_ARENA` (estado 14 → 15)

A fenda sempre larga o jogador em **(10,19)**, olhando para cima. Um gatilho de
frame (e não `coord_event`) porque a coreografia precisa saber **exatamente**
onde o jogador está.

### Beat 1 — A subida do corredor

O corredor tem exatamente três tiles de largura (x=9..11) de y=15 a y=19, então
as três colunas nunca se cruzam:

| Quem | De → para | Movimento |
|---|---|---|
| Parceiro (Solgaleo **ou** Lunala) | (9,19) → (9,11) | `walk_up x8 > face_up` |
| Jogador | (10,19) → (10,11) | `walk_up x8 > face_up` |
| Anabel | (11,19) → (11,11) | `walk_up x8 > face_up` |

```text
# UltraSpaceArena_Text_ArenaLook
  There is a floor, and there is light, and
  there is nothing in any direction that
  looks like a direction.

  Somewhere behind, the tear they came
  through is still holding its shape.
```

### Beat 2 — Já está aqui, e não é o que New Bark deixou

`FADE_TO_WHITE` → `addobject` do Necrozma em (10,8), três linhas ao norte do
jogador → `FADE_FROM_WHITE` → grito.

```text
# UltraSpaceArena_Text_ArenaAnabelReads
ANABEL
  There.

  …I want to be careful about how I say
  this, because I have been wrong about
  it for four cities.

  It isn't attacking anything. It never
  was. Look at how it's holding itself.
  That is an animal that has not been full
  in a very long time.
```

```text
# UltraSpaceArena_Text_ArenaStarving
ANABEL
  Nine of them, {PLAYER}. Nine, out of four
  towns, and it did not hurt one person
  doing it.

  It has been eating. That's all this has
  ever been.

  …I have spent my whole career learning
  to tell the difference between a threat
  and a thing in trouble, and I have never
  in my life wanted to be wrong about it
  more than right now.
```

### Beat 3 — O parceiro entra na frente, e a coisa toma a luz

O parceiro sobe dois tiles da própria coluna, para (9,9) — **ao lado** da coluna
da criatura, não em cima dela — e vira para leste:
`walk_up x2 > face_right` + grito. Ele se põe entre a coisa
e o jogador **sem ninguém mandar**.

`Shake` → `FADE_TO_WHITE` → `removeobject` do Necrozma + `addobject` do Ultra
Necrozma **no mesmo tile** → `FADE_FROM_WHITE` → grito.

```text
# UltraSpaceArena_Text_ArenaUltra
  It did not take the light the way a
  thief takes something.

  It took it the way a drowning thing
  takes air.

  The armour came back on in pieces, and
  every piece of it was something it had
  swallowed in Johto.
```

### Beat 4 — A Anabel entra na frente dele, uma vez, do jeito que ela sempre faz

(11,11) → (11,10): uma linha acima, **ao lado** da coluna do jogador, nunca em
cima dela.

```text
# UltraSpaceArena_Text_ArenaAnabelFront
ANABEL
  Behind me. Now.

  …Right. It looked at you, and I did that
  without thinking about it, and we are
  both going to pretend that was a plan.
```

```text
# UltraSpaceArena_Text_ArenaAnabelRead
ANABEL
  Here is what I have, and then I will get
  out of your way.

  It wants the light. It will come for the
  brightest thing on this floor and it will
  keep coming, and no, that is not a
  prediction -- it is the fourth time I
  have watched it do exactly that.

  So don't give it yours. Take its.
```

### Beat 5 — De onde vem a Beast Ball

Ela diz isso **antes** da luta, não depois. É o único lugar do arco inteiro em
que alguém explica aquele item — e é o gancho do
[`KURT_BALL_CRAFT_DESIGN.md`](../../KURT_BALL_CRAFT_DESIGN.md). **Não há
`giveitem` aqui:** ela não entrega nenhuma, ela diz que pediu.

```text
# UltraSpaceArena_Text_ArenaAnabelBall
ANABEL
  One more thing, and then I will shut up
  and let you work.

  Four years ago I wrote to an old man in
  Azalea Town. I sent him everything the
  International Police had on what a rift
  does to a Pokémon that comes through
  one, and I asked him whether he could
  make something that would hold one
  without hurting it.

  He wrote back in nine days. He called it
  a Beast Ball, and he has been making
  them for me by hand ever since, because
  nobody else in the world knows how.
```

```text
# UltraSpaceArena_Text_ArenaAnabelBallTwo
ANABEL
  I have four of them left, and I have
  been carrying them for four cities
  without using one.

  I'm not giving you one yet. Ask me again
  when we know what we're looking at.

  His name is Kurt. If we both walk out of
  here, go to Azalea and tell him they
  work.
```

### Beat 6 — Ela volta ao tile dela e não sai mais

(11,10) → (11,11). **Esta é a razão, dentro da ficção, de a Anabel não lutar:**
daqui em diante as mãos dela estão segurando o caminho de volta aberto. Depois
desta caixa, tudo que se move é o jogador, o parceiro ou a criatura — **nunca
ela**.

```text
# UltraSpaceArena_Text_ArenaAnabelAnchor
ANABEL
  Listen, because I am about to become
  useless and I would rather you heard
  why from me.

  That tear does not stay open on its
  own. Somebody holds it, from this side,
  and it has to be somebody who has been
  through one. I don't know why. I
  stopped needing to know why on a beach
  in Cherrygrove.

  So this is where I stand. If I let go,
  you don't get home.
```

```text
# UltraSpaceArena_Text_ArenaAnabelAnchorTwo
ANABEL
  Which makes the fight yours. All of it. I
  cannot throw so much as a Poké Ball
  from here and I am not going to try.

  …I have spent twenty years being the
  one who gets in front of things.
  Standing still is the hardest thing
  anyone has asked of me all year.

  Go on, {PLAYER}. I've got the door.
```

### Beat 7 — A batalha

Batalha de **ameaça**, não duelo de personagem: `B_FLAG_NO_WHITEOUT` **não** é
setada. Perder é blackout e refazer — e refazer é de graça, porque o estado fica
14 e o `ON_TRANSITION` deste mapa põe tudo de volta. Números e perfil de fases em
[`ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON_IMPLEMENTATION.md) §8.4.

```text
# UltraSpaceArena_Text_Unresolved
  The tear pulled shut, and the floor went
  out from under everything, and the
  altar was there again.
```

---

## Ato IV-b — A vitória, que é cutscene

Do "venceu" em diante **não há como perder o Pokémon**.

`FADE_TO_WHITE` → o Ultra Necrozma sai e o Necrozma volta no lugar dele →
`FADE_FROM_WHITE` → grito.

```text
# UltraSpaceArena_Text_VictoryArmourOff
  The armour came off the way frost
  comes off a window.

  What was left of it was not very large
  at all.
```

```text
# UltraSpaceArena_Text_VictoryAnabel
ANABEL
  …Oh.

  That's it? That's what was
  underneath?

  Four towns. Nine of them. And this is
  what has been carrying it around.
```

### O parceiro faz a coisa que ninguém planejou

Ele sobe um tile da própria coluna, para (9,8), ficando **ao lado** da coisa
pequena em vez de em cima dela, e se vira para a fenda: está segurando a
passagem aberta **por dentro** enquanto todo mundo sai.
`walk_up > face_down` + grito + `Shake`.

```text
# UltraSpaceArena_Text_VictoryHarmony
  {STR_VAR_1} walked past {PLAYER}
  without being asked, and put itself
  between the small thing and the tear,
  and stopped.

  The light did not get brighter. It got
  even.

  Somewhere behind them, the way home
  stopped shivering.
```

```text
# UltraSpaceArena_Text_VictoryBall
ANABEL
  It isn't running.

  …Here. Take it. This is the one I've
  been saving, and I have just worked out
  what I was saving it for.

  Room for one more, {PLAYER}. That was my
  condition in Olivine and this is the
  whole reason it was a condition. Go on.
  Slowly. Nothing has ever carried this
  one anywhere.
```

### A captura

`givemon SPECIES_NECROZMA, 75` — **`SPECIES_NECROZMA` e não `NECROZMA_ULTRA`**
(as formas Ultra / Dusk Mane / Dawn Wings são formas de batalha), e **nível 75 e
não 90**, porque o que o jogador recebe é a criatura **depois** de perder a luz.

```text
# UltraSpaceArena_Text_VictoryCaught
  It did not fight the Ball.

  It went in the way something goes into
  a house it has been standing outside of
  for a very long time.
```

`FADE_TO_WHITE` → `removeobject` → `FADE_FROM_WHITE`.

```text
# UltraSpaceArena_Text_VictoryLeave
ANABEL
  Then we're done here.

  Out. Same way. Don't look at anything
  on the way.
```

Guarda (deve ser inalcançável — a fenda recusou quem estava cheio). **Nada é
marcado:** o estado fica 14, o jogador volta para o altar e o ato inteiro é
refeito. Nenhum progresso se perde.

```text
# UltraSpaceArena_Text_NoRoom
ANABEL
  There's nowhere to put it.

  …That is my fault. That was my one job
  and I asked you once and then I
  stopped checking.

  Out. Make room, and we come straight
  back -- it isn't going anywhere, and
  neither am I.
```

Estado 15 → `warpsilent` para o altar, em (14,11) — um tile **ao sul** da fenda,
então o jogador sai do rasgo **de frente para ele**.

---

## Ato V — A despedida (estado 15 → 16)

Posições na entrada são as dos templates. **Repare em quem está onde:** o jogador
está **entre a fenda e todo mundo**, e a Lusamine está do outro lado da fenda.
Ninguém se mexe na primeira metade da cena, porque a fotografia já está certa.

### As pessoas primeiro — Looker, sempre

```text
# SunMoonAltar_Text_FarewellHurt
LOOKER
  {PLAYER}! Chief! Is anyone -- are you
  both --

  …Sit down. Both of you. The report can
  wait. The report can wait a very long
  time, and I intend to make it.
```

```text
# SunMoonAltar_Text_FarewellShowThem
LOOKER
  Now then. I have five people here who
  have been staring at a hole in the air
  for forty minutes without saying a word
  to each other.

  Would you show them what came out of
  it?
```

### O que o jogador trouxe de volta

O parceiro é mostrado de novo.

```text
# SunMoonAltar_Text_FarewellKukui
KUKUI
  …That's it.

  That's the thing that walked out of
  Blackthorn with two Ultra Beasts in its
  hands.

  {PLAYER}, it fits in a Poké Ball. I've
  been building instruments for six weeks
  to measure something that fits in a
  Poké Ball.
```

```text
# SunMoonAltar_Text_FarewellLillie
LILLIE
  May I -- thank you.

  …It's warm. I thought it would be cold.
  I don't know why I thought that.

  It was hungry. All of it, the whole way,
  four towns, and every single one of us
  called it an attack because it was big
  and it was bright and we were
  frightened.
```

```text
# SunMoonAltar_Text_FarewellGladion
GLADION
  Don't do that.

  It wasn't nobody's fault and it wasn't
  anybody's monster. It was hungry, and
  now it isn't, and {PLAYER} is the one who
  sorted that out while the rest of us
  held a rope.

  …That's the right way round, for once.
  Let it be the right way round.
```

### A Lusamine desce, pela última vez

`walk_left > face_down` — ela sai da coluna do disco, para
(13,9), e se vira para o grupo. **É esse o ponto da fala dela: pela primeira vez
no evento inteiro ela não está olhando para a porta.**

```text
# SunMoonAltar_Text_FarewellLusamine
LUSAMINE
  I have been standing here looking at
  that door for the better part of a day,
  and I want to tell you all what I was
  actually doing.

  I was waiting for it to be my turn.
  Because if it was my turn, then all of
  this was about me, and if it was about
  me, then it was something I could fix by
  paying for it.

  It was not about me. It has never once
  been about me.
```

```text
# SunMoonAltar_Text_FarewellLusamineAsks
LUSAMINE
  Lillie. Gladion.

  I am not going to ask to be forgiven.
  That is a thing people ask for so that
  the conversation can end.

  I am going to ask something much more
  inconvenient. May I come back? Here, to
  this island, regularly, for as long as
  there is work on it?
```

```text
# SunMoonAltar_Text_FarewellLillieAnswers
LILLIE
  …Yes.

  Not because everything is all right.
  Because you asked, and you have never
  asked.

  Ask again next time. Every time. That's
  the part I want.
```

### O altar volta

`fadeoutbgm 4` → `Shake` → `FADE_TO_WHITE` → `DiscToCalm` → `FADE_FROM_WHITE` →
`setweather WEATHER_NONE`: a cinza para.

```text
# SunMoonAltar_Text_FarewellCalm
  The ash stopped.

  High on the wall, the disc turned once
  more and stopped being a hole, and the
  sun came back into the middle of it.
```

### Mas não volta inteiro

`SE_WARP_IN`.

```text
# SunMoonAltar_Text_FarewellStillThere
  At the foot of the steps, three paces
  from where Lusamine had been standing,
  the tear was still there.

  It was smaller, and it was steady, and it
  was not going anywhere.
```

```text
# SunMoonAltar_Text_FarewellAnabelStays
ANABEL
  It won't close. I don't think it's
  supposed to.

  There are eight more that we know about
  and I would guess a great many that we
  don't, and every one of them has
  something on the other side of it.

  I'll stay. I was on the other side of
  one of these, and somebody was
  standing here when I came through, and
  I would like to be that person for
  whoever comes next.
```

```text
# SunMoonAltar_Text_FarewellLookerStays
LOOKER
  And where the Chief stays, I stay --
  chiefly because somebody has to file
  all of this, and she writes appallingly.

  …Also because I like it here. Do not put
  that in the report.

  Come back, {PLAYER}. It opens most
  mornings. Bring your partner; bring the
  small one; bring anything you like.
```

```text
# SunMoonAltar_Text_FarewellGoodbye
LOOKER
  Rift Missions, the Chief is calling them.
  I think it sounds rather grand.

  Go home and sleep. The sea is flat and
  the sailor is patient and Johto has
  been extremely calm for four entire
  hours.

  …Which, in my professional experience,
  is exactly how long that lasts.
```

Estado 16 → `warpsilent` no lugar, em (14,11). Cinco visitantes e os dois
parceiros vão embora de vez, e a fenda vira uma coisa diária.

---

## Conversas soltas — a crise (estados 12-14)

Um evento que solta o jogador no meio dele precisa que os sete tenham o que
dizer enquanto ele decide.

**Looker** — e ele **cura desde o estado 13**, não desde o 16: 13 e 14 são
exatamente os estados em que isso importa, porque o retry do boss larga o jogador
no continente e o barco de volta não passa por Centro nenhum.

```text
# SunMoonAltar_Text_LookerCrisis
LOOKER
  I have written the words “situation
  ongoing” four times and crossed them
  out three.

  Go on, {PLAYER}. She is not going to come
  to you.
```

```text
# SunMoonAltar_Text_LookerHeal
LOOKER
  Before anything else. Your Pokémon. May
  I?

  There is no Center on this island and I
  have made it my business to be the next
  best thing.
```

```text
# SunMoonAltar_Text_LookerHealed
LOOKER
  There. Right as rain, as somebody's
  grandmother says.

  Now. Was there anything else, or did you
  come all this way to be fussed over?
  …Either is perfectly acceptable.
```

```text
# SunMoonAltar_Text_LookerNoHeal
LOOKER
  As you wish. The offer does not expire.
```

**Anabel:**

```text
# SunMoonAltar_Text_AnabelCrisis
ANABEL
  I can't help you with this part. If I
  could order her to stand down I would
  have done it an hour ago.

  …For what it's worth: she is not wrong
  about being the one who should go. She
  is wrong about going alone. Those are
  different arguments and she keeps
  having the first one.
```

**Lillie:**

```text
# SunMoonAltar_Text_LillieCrisis
LILLIE
  I've said everything I know how to say
  to her.

  Twice. In both of the ways I know how.

  …Would you try? She listens to people
  who haven't been disappointed by her
  yet.
```

**Gladion:**

```text
# SunMoonAltar_Text_GladionCrisis
GLADION
  I'm holding this side of it. That's my
  job today.

  Deal with her. I mean it -- I'd rather
  you did it than me. I'd say something I
  can't take back.
```

**Kukui:**

```text
# SunMoonAltar_Text_KukuiCrisis
KUKUI
  Between you and me? The instrument is
  useless and I'm keeping it in my hands
  so I have something to hold.

  …Go talk to her, {PLAYER}. That's the
  science right now. That's the whole
  experiment.
```

**A Anabel na arena** (alcançável só na teoria — o ato roda sob `lockall` de
ponta a ponta, mas um objeto com `script: NULL` seria um A mudo):

```text
# UltraSpaceArena_Text_AnabelHold
ANABEL
  Both hands, {PLAYER}. Ask me anything
  you like afterwards.

  Go and finish it.
```

---

## Conversas soltas — a fenda aberta (estado 14) e o intervalo (estado 15)

**Lusamine, segurando a âncora:**

```text
# SunMoonAltar_Text_LusamineAnchor
LUSAMINE
  I am holding the light on this side,
  which is, I am informed, “the useful
  thing”.

  I intend to be extremely good at it.
```

**Lillie:**

```text
# SunMoonAltar_Text_LillieAnchor
LILLIE
  We'll be right here. All four of us, the
  whole time.

  …Come back. That's not a request,
  that's the plan, and I helped write it.
```

**Gladion:**

```text
# SunMoonAltar_Text_GladionAnchor
GLADION
  Silvally has your scent. If that tear so
  much as flickers we're coming through
  after you.

  Don't make us. It'd be embarrassing for
  everybody.
```

**Kukui:**

```text
# SunMoonAltar_Text_KukuiAnchor
KUKUI
  Needle's steady! Steady is GOOD,
  {PLAYER}, steady is the best word in my
  whole job!

  Whatever your partner did, it's still
  doing it. Go.
```

**Estado 15** — os poucos segundos antes da despedida:

```text
# SunMoonAltar_Text_LookerIdle
LOOKER
  I shall be right here. Holding a
  notebook. Being decorative.
```

```text
# SunMoonAltar_Text_AnabelIdle
ANABEL
  …Give me a moment, {PLAYER}. I am still
  catching up with the last ten minutes.
```

```text
# SunMoonAltar_Text_LusamineIdle
LUSAMINE
  Not now.

  …I am sorry. That was shorter than you
  deserved, and I will do better in a
  minute.
```

```text
# SunMoonAltar_Text_RiftSettling
KUKUI
  Don't touch it! Don't -- okay, don't
  touch it yet. It's still deciding what
  shape it wants to be.
```

---

## Depois de tudo (estado ≥ 16)

**Looker, em casa:**

```text
# SunMoonAltar_Text_LookerHome
LOOKER
  {PLAYER}! The Inspector is IN.

  Eight files open, one tear that keeps
  its own hours, and a kettle that the
  Chief refuses to describe as mine.

  This was a very strange place to end up
  and I would not trade it for a
  promotion.
```

**Anabel** — ela não vende nada; ela manda o jogador para Azalea:

```text
# SunMoonAltar_Text_AnabelHome
ANABEL
  It opens most mornings, about an hour
  after the light hits the disc.

  Nine, that we have counted. Nothing has
  come through yet that needed help, and
  I am not going to stop being here on the
  day one does.

  …Looker has started calling it a
  posting. It is not a posting. I asked
  for it.
```

```text
# SunMoonAltar_Text_AnabelKurt
ANABEL
  If you need Beast Balls, don't ask me. I
  have two left and I am keeping them.

  Ask Kurt, in Azalea. He is the man who
  invented them, he is the only person
  alive who can make one, and he will make
  you a batch a day if you bring him what
  he needs.

  Tell him I sent you. He will pretend not
  to remember me and then he will ask
  after my Pokémon by name.
```

**Lusamine** — ela está em `FLAG_TEMP_5`, então **pode genuinamente ainda estar
no altar no dia seguinte**. Isso está correto, não é bug, e a fala dela do estado
≥ 16 assume exatamente isso.

```text
# SunMoonAltar_Text_LusaminePost
LUSAMINE
  {PLAYER}. Good.

  I come out three days a week and I
  stand exactly where I stood that day
  and I look at exactly what I looked at,
  and the Inspector has decided this is
  very healthy of me.

  It is not healthy. It is bookkeeping.
  But I have started bringing lunch, and
  Lillie says that counts as progress.
```

Revanche, uma por dia:

```text
# SunMoonAltar_Text_LusamineRematchAsk
LUSAMINE
  While you are here. I have had rather a
  lot of time to think about how that
  battle went.

  I have made some adjustments. One of
  them is the Nihilego, and I would like to
  say out loud where she came from,
  because people will assume.

  She is not a trophy and she is not a
  symptom. She is one of the nine we
  brought back, she is the one the
  Foundation gave me, and I am the one
  who has to be worth it.

  Would you care to see them?
```

```text
# SunMoonAltar_Text_LusamineRematchNo
LUSAMINE
  Another day, then. I shall be here, being
  healthy.
```

```text
# SunMoonAltar_Text_LusamineRematchBeaten
LUSAMINE
  …Again. Marvellous.
```

```text
# SunMoonAltar_Text_LusamineRematchAfter
LUSAMINE
  Do not let me keep you. I have notes to
  make and, apparently, a great deal of
  humility to practise.
```

```text
# SunMoonAltar_Text_LusamineDoneToday
LUSAMINE
  Once a day, {PLAYER}. I am fifty-one and
  I have a foundation to run.
```

**O marinheiro do cais do altar:**

```text
# SunMoonAltar_Text_Sailor
  The ship's ready whenever you are.

  Shall we head back to Olivine?
```

```text
# SunMoonAltar_Text_SailorDepart
  Aye! Back to Olivine we go!
```

```text
# SunMoonAltar_Text_SailorStay
  Right. I'll be here on the pier.
```

### A expedição diária

A flag do dia é setada **na entrada, não na saída**: quem entra, dá meia-volta e
sai já usou a fenda de hoje. É deliberado — a alternativa é um laço de reentrada
que o doc do loop teria de desfazer.

```text
# SunMoonAltar_Text_RiftDailyAsk
ANABEL
  It opened again this morning. They
  always do, now -- once, and then it
  closes itself by nightfall.

  Looker has a file for each one. I have a
  Ball for each one.

  Going in?
```

```text
# SunMoonAltar_Text_RiftDailyNo
ANABEL
  Then it will be here tomorrow. They
  always are.
```

Do outro lado, por enquanto, a sala está vazia — **este é o ponto de entrega para
o documento do loop:**

```text
# UltraSpaceArena_Text_EmptyRift
  The floor goes on in every direction and
  there is nothing standing on it today.

  Somewhere behind, the way back is still
  open.
```

---

## Apêndice — movimentos, em um lugar só

| Label | Sequência |
|---|---|
| `SunMoonAltar_Movement_PlayerStepUp` | walk_up > face_up |
| `SunMoonAltar_Movement_PlayerStepDown` | walk_down > face_up |
| `SunMoonAltar_Movement_LusamineDown` | walk_down x2 > face_down |
| `SunMoonAltar_Movement_LusamineUp` | walk_up x2 > face_up |
| `SunMoonAltar_Movement_LusamineAside` | walk_left > face_down |
| `SunMoonAltar_Movement_LookerAside` | walk_left > face_down |
| `SunMoonAltar_Movement_LookerBack` | walk_right > face_down |
| `SunMoonAltar_Movement_LillieForward` | walk_right > face_up |
| `UltraSpaceArena_Movement_PlayerUp` | walk_up x8 > face_up |
| `UltraSpaceArena_Movement_EscortUp` | walk_up x8 > face_up |
| `UltraSpaceArena_Movement_PartnerForward` | walk_up x2 > face_right |
| `UltraSpaceArena_Movement_PartnerHarmonise` | walk_up > face_down |

**Flash de cena:** `fadescreenswapbuffers` em tudo que volta para o mesmo mapa;
`fadescreen` **só** imediatamente antes de um `warpsilent`, porque o load
reconstrói as paletas de qualquer jeito.

**Tremor** (`Shake`, nos dois mapas): `ShakeCamera` com pan 1/1, 12 tremidas,
delay 4. `ShakeCamera` lê **quatro** vars, não duas — passar só duas deixa o
tremor com duração aleatória, sem nada no build denunciando.
