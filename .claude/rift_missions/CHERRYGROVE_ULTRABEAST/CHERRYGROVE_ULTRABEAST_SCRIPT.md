# Cherrygrove — Necrozma, Blacephalon + Stakataka (Rift Mission 3) — roteiro

**O que é este arquivo:** a cena como ela acontece na tela — as falas literais
(em inglês, exatamente como estão na ROM) e a coreografia, beat a beat.
Estado, flags, objetos, arquivos tocados, riscos e checklist de teste ficam em
[`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md).

**Fonte:** `data/maps/OlivineCity_House1/scripts.pory`,
`data/maps/CherrygroveCity/scripts.pory` (revisão 4, 23/09/2026).
Ao mudar uma fala, mude no `.pory` e traga a mudança para cá.

**A história em três linhas:** a Anabel **sente** a fenda antes de qualquer
instrumento e diz isso; o Necrozma sobe da água parada, rasga a fenda e manda as
duas Ultra Beasts; o truque delas é que a **clara cega a baía** e, quando a luz
passa, a **pesada simplesmente está mais perto**. O Kukui — que o Looker tratou a
missão inteira como um civil de jaleco — põe um Incineroar entre a coisa e o
jogador. Depois o Necrozma **mira o jogador**, a Anabel entra na frente e conta,
de joelho na areia molhada, que é uma **Faller**.

**Ninguém nomeia o Necrozma.** O nome fica para a reunião de Olivine.

---

## Elenco e marcação

A colisão **não** basta numa praia: metade deste mapa tem colisão 0 e ainda é
água. A divisão areia / raso / oceano vem do `metatile_attributes.bin`.

```text
       x= 21 22 23 24 25 26 27 28 29 30 31 32
   y= 5     #  #  #  #  #  #  #  #  #  #  #  #
   y= 6     #  #  #  #  #  #  #  #  #  #  #  #   parede norte
   y= 7     ~  w  w  w  w  U  K  A  s  .  .  .   U Kukui (26,7)  K Looker (27,7)
   y= 8     ~  ~  ~  ~  w  u  t  a  .  .  .  .   A Anabel (28,7)
   y= 9     ~  ~  n  B  w  i  l  n  .  .  .  .   t (27,8) = ÚNICO tile de fala
   y=10     ~  N  n  S  w  X  p  P  k  .  .  .   B Blacephalon (24,9)
   y=11     ~  ~  ~  ~  w  s  s  .  .  .  .  #   S Stakataka   (24,10)
   y=12     ~  ~  ~  ~  w  s  s  .  .  #  #  #   N Necrozma    (22,10)

   #  colisão          s  MB_SAND          .  MB_NORMAL
   ~  MB_OCEAN_WATER   — só de Surf; a pé o jogador NÃO entra
   w  MB_SHALLOW_WATER — colisão 0; a pé o jogador ANDA em cima

   Depois da aproximação:  u Kukui (26,8)  l Looker (27,8)  a Anabel (28,9)  p jogador (27,10)
   Depois de a Anabel entrar na frente:
      l Looker (27,9)   p Anabel (27,10)   P jogador (28,10)   k Kukui (29,10)
      i Incineroar (26,9)   X (26,10) = onde a Stakataka termina o avanço silencioso
      n = os tiles de oceano que a absorção usa, (23,9) e (23,10)
```

As Ultra Beasts e o Necrozma ficam **sobre o oceano** de propósito: ninguém
chega neles a pé. A coluna x=25 e a faixa (22..25,7) são água **rasa** — o
jogador atravessa andando; só x≤24 é oceano de verdade.

O Looker fica num bolso: (27,6) é parede, (26,7) é o Kukui e (28,7) a Anabel. O
**único** tile de onde se fala com ele é (27,8), olhando para cima — é isso que
torna o começo da cena determinístico sem `getplayerxy`.

---

## Ato 1 — O briefing da Missão 3 (Olivine City, House1)

Mesma coreografia das missões anteriores. O briefing é quem **revela** o lugar.

```text
# OlivineCity_House1_Text_BriefingM3
LOOKER
  {PLAYER}! Come in, come
  in. It has opened again.

  Cherrygrove City.

ANABEL
  Two signatures.

  One of them will not hold
  still.

LOOKER
  And here is the part I
  cannot account for.

  We did not find it.

  It was reported to us. By
  telephone. Four days ago.

ANABEL
  A researcher from Alola.

  He gave us a time window, a
  bearing, and the tide.

  Then he called back and
  corrected the window.

LOOKER
  Twice.

  He was right twice.

  Anabel, read me his file
  again.

ANABEL
  “Professor Kukui.
  Pokémon move research.”

  No enforcement record. No
  combat authorisation.

  It is two pages long, Looker.

LOOKER
  Two pages, and he is
  sitting on a beach under an
  open sky.

  {PLAYER}, we have evacuated
  Cherrygrove into the Violet
  Gym. Every soul but one.

ANABEL
  He will not leave the
  shore. He says somebody has to
  be looking when it opens.

LOOKER
  He is quite right, and
  that is what frightens me.

  The northwest beach, {PLAYER}.

  Prepare for two of them, and
  go and stand in front of that
  man.
```

### Depois do briefing — "vá na frente"

```text
# OlivineCity_House1_Text_LookerGoAheadM3
LOOKER
  The northwest shore,
  {PLAYER}.

  You cannot miss him.

  He is the only man left in
  that town, and he is wearing a
  lab coat on a beach.
```

```text
# OlivineCity_House1_Text_AnabelGoAheadM3
ANABEL
  Go on.

  And whatever he is doing when
  you get there, {PLAYER}-

  make him sit down for one
  minute.
```

---

## Ato 2 — Cherrygrove, antes da cena

Cidade vazia. Toda porta recusa o jogador **menos a do Centro Pokémon**.

```text
# CherrygroveCity_Text_DoorLocked
  The door is locked tight.

  A note is taped to it:
  “Closed until further notice.
  The town is at the Violet Gym.”
```

### Conversas soltas

**Anabel** (`UBAnabel`) — `faceplayer`, e `turnobject DIR_SOUTH` no fim para ela
voltar a encarar a água.

```text
# CherrygroveCity_Text_UBAnabelIdle
ANABEL
  Cherrygrove is in the
  Violet Gym.

  Two buses and one argument,
  which I won.

  Talk to Looker when you're
  ready. Not a moment before.
```

Com a família Cosmog na equipe:

```text
# CherrygroveCity_Text_UBAnabelIdleCosmog
ANABEL
  …A child of the stars.

  Keep that one close today,
  {PLAYER}.

  Closer than you usually do.
```

**Kukui** (`UBKukui`) — `faceplayer`, mesmo `turnobject` de guarda. Ele reconhece
um Cosmog de cara — morou com um — mas **nunca** chama o Pokémon do jogador pelo
nome do que ele conheceu.

```text
# CherrygroveCity_Text_UBKukuiIdle
KUKUI
  {PLAYER}! Four days on
  this beach, cousin.

  I'm tired. I'm not bored.
  There's a difference.

  Don't make me tell it twice,
  though. Go on, talk to Looker.

  You'll get the whole thing at
  once.
```

Com a família Cosmog na equipe:

```text
# CherrygroveCity_Text_UBKukuiIdleCosmog
KUKUI
  …Hold on.

  Hold on, that's a {STR_VAR_1}.

  I've met exactly one of those.

  It cost me a roof, a boat and
  eleven weeks of paperwork.

  You and I are having a very
  long talk. After.
```

---

## Ato 3 — O convite do Looker (o último ponto de saída)

A leitura do Kukui vem **antes** do SIM, e ela está **errada de propósito** num
detalhe: ele acha que a pesada entra andando atrás das luzes. A cena corrige ele
— é assim que a sinergia é **mostrada** antes de explicada.

```text
# CherrygroveCity_Text_UBLookerGreet
LOOKER
  {PLAYER}! Over here.

  And mind your footing. That
  water is not behaving.

  It has opened twice since dawn.

  Twice we ran. Twice it closed
  before we arrived.

  The Professor, meanwhile, has
  not run anywhere.

  He has been sitting in it.
```

```text
# CherrygroveCity_Text_UBKukuiTheory
KUKUI
  {PLAYER}! Man, am I glad
  it's you.

  Okay. Four days, three
  openings, one notebook.

  There are two of them, and
  they never come through
  together.

  The bright one shows first. It
  lights up the whole bay and
  everybody looks.

  Everybody. You can't help it.

  And by the time you can see
  again, the big one is closer
  than it was.

LOOKER
  Professor. Four days.
  On a beach.

  Under a hole in the sky.

KUKUI
  Yeah. And if it opened
  with nobody watching, who tells
  this town when to run?

  I stayed so somebody would
  know.

ANABEL
  He called the second
  opening eleven minutes early.

  He has earned the sand.

KUKUI
  So here's the play.

  One of us takes the bright
  one's eyes. The other takes
  the wall.

  Nobody gets to hide if somebody
  is always looking.
```

A pergunta (`MSGBOX_YESNO`):

```text
# CherrygroveCity_Text_UBReady
LOOKER
  One warning, {PLAYER}.

  These two are worse than
  Mahogany.

ANABEL
  Bring everything you
  have.

  Are you ready?
```

**NÃO:**

```text
# CherrygroveCity_Text_UBNotReady
LOOKER
  Wise.

  The Center is open, and I am
  not moving from this sand.
```

**SIM →** a cena começa e não para mais.

---

## Ato 4 — A cena

`lockall` + `hidefollower`.

### Beat 1 — Aproximação (a ordem é obrigatória)

Kukui **primeiro** — é ele que está há quatro dias mais perto da água —, depois
o jogador, depois Looker e Anabel: o Looker só desce quando o jogador desocupa
(27,8). Ninguém pisa na água.

| Quem | De → para | Movimento |
|---|---|---|
| Kukui | (26,7) → (26,8) | `walk_down > face_left` |
| Jogador | (27,8) → (27,10) | `walk_down x2 > face_left` |
| Looker | (27,7) → (27,8) | `walk_down > face_left` |
| Anabel | (28,7) → (28,9) | `walk_down x2 > face_left` |

O Kukui para em (26,8) e **não** em (26,10): (26,9) precisa ficar livre para o
Incineroar dele e (26,10) para o avanço silencioso da Stakataka.

### Beat 2 — A Anabel sente antes do instrumento

`SE_PIN` + "!" sobre ela. **Primeira metade do pagamento do Faller** — aqui não
se explica nada.

```text
# CherrygroveCity_Text_UBAnabelSenses
ANABEL
  Professor, stay east of
  the tide line, and if anything
  comes through you will-

  …

LOOKER
  Chief?

ANABEL
  It's here.

LOOKER
  There is nothing on the
  meter.

ANABEL
  I know.

KUKUI
  Whoa-look at the water!

  It's going flat. That's the
  tell! Everybody back!
```

`fadeoutbgm 4` — a cidade **para** de tocar o tema alegre dela aqui.

### Beat 3 — A coisa sobe da água

`UBShake` → `FADE_TO_WHITE` → `addobject` do Necrozma em (22,10), cinco tiles a
oeste do jogador e bem dentro da câmera → `FADE_FROM_WHITE` →
`playbgm MUS_DP_LEGEND_APPEARS, TRUE` (com `save_song`, para a trilha voltar
depois da batalha) → grito.

```text
# CherrygroveCity_Text_UBNecrozmaArrives
  Something stands up out of the
  flat water.

  It is made of light, and it is
  looking at the beach.

LOOKER
  …That is the thing from
  Blackthorn.

KUKUI
  That is not a Pokémon I
  know.

  And, cousin, I know a lot of
  them.

ANABEL
  It was standing there
  before my instruments said so.

  It always is.
```

### Beat 4 — Ele mesmo abre a fenda

Necrozma `walk_in_place_fast_right x3` → `UBFlash`.

```text
# CherrygroveCity_Text_UBRift
KUKUI
  It's- wait. Wait!

  It isn't coming through the
  tear.

  It's making it!

LOOKER
  Behind me, Professor.
  Behind me, please.

KUKUI
  Nah.
```

Grito → `UBShake` → `FADE_TO_WHITE` → `addobject` de Blacephalon (24,9) e
Stakataka (24,10) → `FADE_FROM_WHITE` → os dois gritos.

```text
# CherrygroveCity_Text_UBAppear
LOOKER
  Blacephalon! And that
  is- what is that?

KUKUI
  Stakataka! Whoa.

  That's not one Pokémon,
  cousin.

  That's a whole crowd of them,
  stacked up.
```

### Beat 5 — A sinergia (o coração da missão)

A Blacephalon **apaga a baía de branco** e, quando a tela volta, a Stakataka
simplesmente **está mais perto**. Ela nunca anda: o `setobjectxy` debaixo do
flash **é** o truque, não um atalho.

1. Blacephalon `walk_in_place_fast_right x3` + grito →
   `FADE_TO_WHITE` → `setobjectxy` Stakataka **(25,10)** → `FADE_FROM_WHITE`.

```text
# CherrygroveCity_Text_UBSynergy
KUKUI
  Here it comes-don't look
  at the ligh-

  …

KUKUI
  Okay. Okay, I had it
  wrong.

  It isn't walking in behind the
  lights.

  It isn't walking at all.

ANABEL
  It crossed four lengths
  while the bay was white.

LOOKER
  Then we simply do not
  blink.

KUKUI
  That's the problem,
  cousin.

  Nobody can not blink.
```

2. De novo — e desta vez ela cai **ao lado do jogador**: `FADE_TO_WHITE` →
   `setobjectxy` Stakataka **(26,10)** → `FADE_FROM_WHITE` → grito → "!" sobre o
   Looker.

```text
# CherrygroveCity_Text_UBSynergyClose
LOOKER
  {PLAYER}! It is on top
  of you-!
```

### Beat 6 — A surpresa: quem é o Kukui

O Looker passou a missão inteira tratando ele como civil de jaleco; ninguém viu
uma Poké Ball com ele em quatro dias.

```text
# CherrygroveCity_Text_UBKukuiSendsOut
KUKUI
  Not on my beach.

  Incineroar-BETWEEN them!
```

`UBFlash` → `addobject` do Incineroar em **(26,9)**, exatamente ao norte da
Stakataka e ao sul do Kukui → grito → ataque para baixo
(`walk_in_place_fast_down x2`) → `UBShake` → `UBFlash` →
a Stakataka é jogada de volta pela linha 10 até o tile dela, ainda olhando para
leste: `lock_facing_direction > walk_fast_left x2 > unlock_facing_direction`. O Incineroar vira para
oeste.

```text
# CherrygroveCity_Text_UBKukuiRevealed
LOOKER
  …Professor.

  You are a civilian.

  Your file is two pages long.

KUKUI
  Yeah, it would be.

  Nobody back home writes reports
  on the guy who built the
  League.

  Alola didn't have one. I made
  it.

  Then somebody had to stand at
  the end of it, and that was me
  too. For a while.

ANABEL
  …Sir. I apologise for
  the file.

KUKUI
  Keep it! It's restful.

  Now quit looking at me. That
  thing in the water isn't done.
```

### Beat 7 — A coisa mira o jogador; a Anabel entra na frente

Necrozma `walk_in_place_fast_right x3`.

```text
# CherrygroveCity_Text_UBNecrozmaTargets
  The creature turns.

  Not toward the Professor.
  Not toward the Ultra Beasts.

  Toward you.

ANABEL
  -MOVE!
```

`SE_PIN` — ela **já está se movendo**. A troca é sequencial e nunca disputa tile:

| Ordem | Quem | De → para | Movimento |
|---|---|---|---|
| 1 | Anabel | (28,9) → (27,9) | `walk_fast_left` |
| 2 | Jogador | puxado (27,10) → (28,10), **ainda olhando oeste** | `lock_facing_direction > walk_fast_right > unlock_facing_direction` |
| 3 | Anabel | cai no (27,10) vago, entre o jogador e a luz | `walk_fast_down > face_left` |

Grito → `UBFlash` → `UBShake`. Looker (27,8) → (27,9), olhando para baixo, para
ela: `walk_fast_down`.

```text
# CherrygroveCity_Text_UBAnabelFaller
  She is in front of you before
  you have finished turning your
  head.

  The bay goes white.

  When it comes back, Anabel is
  on one knee in the wet sand.

LOOKER
  CHIEF-

ANABEL
  I'm here. I'm here.

  Let go, Looker. I can stand.

  {PLAYER}. You should hear this
  from me, and not from a file.

  I knew it was coming because I
  have been on the other side of
  one.

  I'm a Faller. I came through a
  tear like that one.

  There are years of me I have
  not got back.

LOOKER
  …Chief.

ANABEL
  The rest of it later.

  There are two of them in the
  water and one of you.

  Professor. Your plan. Now.
```

O Looker volta a olhar para o oeste — **ela também**: ela nunca para de
trabalhar, e é essa a caracterização.

### Beat 8 — A escolha

Separar as duas não é conveniência de menu: é a **contramedida** à sinergia que a
cena acabou de mostrar — quem está sendo olhado não consegue se esconder.

Ninguém precisa virar: jogador (28,10), Anabel (27,10), Looker (27,9), Kukui
(26,8) e Incineroar (26,9) estão todos a leste e olhando para oeste.

```text
# CherrygroveCity_Text_UBChoosePrompt
KUKUI
  Right. Call it,
  {PLAYER}! Which one do you
  want?

  I'll take whatever's left, and
  I will keep it looking at me.

  That's the whole trick.

  Nobody gets to hide.
```

Opções: `  Blacephalon` / `  Stakataka`.
"!" sobre a escolhida, e:

```text
# CherrygroveCity_Text_UBPickedBlacephalon
KUKUI
  The bright one's yours!

  Don't watch the lights. Watch
  the water under it.

  I've got the wall.
  Incineroar, eyes on the big
  guy-don't lose it!
```

```text
# CherrygroveCity_Text_UBPickedStakataka
KUKUI
  The wall is yours!

  Get under it before it
  settles!

  I'll take the fireworks.
  Incineroar, close your eyes-
  you won't need them!
```

### Beat 9 — A batalha

Boss contra a escolhida, terceiro degrau da escala. Números em
[`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) §4.7.

Se não termina em vitória, a cena se desfaz e recomeça do Looker:

```text
# CherrygroveCity_Text_UBGotAway
LOOKER
  The light closed over
  them.

  We are back where we started.

KUKUI
  Then we go again.

  I'm not leaving this beach
  either.

ANABEL
  Heal, and come back.
  We hold here.
```

---

## Ato 5 — A vitória do Kukui e a absorção

A luta do Kukui é **encenada, não jogada**: o Incineroar dá um golpe para oeste
(`walk_in_place_fast_left x2`) + grito → `UBFlash`, e é só
isso. Batalha de verdade contra o Kukui **não** é o plano.

```text
# CherrygroveCity_Text_UBKukuiFoughtStakataka
KUKUI
  Incineroar-through the
  middle! Don't let it set!

  …Down.

  It never got to settle once.

  Thing weighs as much as a
  house, cousin.

  But a house still has to decide
  where to stand.
```

```text
# CherrygroveCity_Text_UBKukuiFoughtBlacephalon
KUKUI
  Eyes shut, Incineroar!
  Swing where it was!

  …Yeah. That's it.

  That's the one thing all those
  lights can't beat.

  Somebody who isn't looking.
```

Então — o padrão de **todas** as missões:

1. Necrozma pulsa (`walk_in_place_fast_right x3`) + grito.
2. As duas são **arrastadas de costas** um tile a oeste, (24,9)→(23,9) e
   (24,10)→(23,10), colando nele — os dois tiles são oceano aberto:
   `lock_facing_direction > walk_slow_left > unlock_facing_direction`.
3. `UBShake` → `FADE_TO_WHITE` → `removeobject` das duas → `FADE_FROM_WHITE` → grito.
4. "!" sobre Kukui, Looker e Anabel.

```text
# CherrygroveCity_Text_UBAbsorbed
KUKUI
  Hey-hey!
  What is it doing?

LOOKER
  It took them.
  Both of them.

  It did not fight them.

KUKUI
  That's feeding.

  I have watched a lot of things
  eat. That's feeding.

ANABEL
  And nothing that comes
  through a tear behaves like
  that.

  It doesn't come through them.

  It opens them.
```

### Reação opcional à família Cosmog

Checada **depois** da batalha. Necrozma se inclina para leste, (22,10)→(23,10) —
livre desde a remoção da Stakataka: `walk_slow_right`.
"!" sobre o jogador + grito.

**Cosmog / Cosmoem:**

```text
# CherrygroveCity_Text_UBNecrozmaSensesCosmog
  The creature is staring past
  you… at the Poké Ball that
  holds your {STR_VAR_1}.

  Your {STR_VAR_1} is trembling.

KUKUI
  Incineroar! In front!
  Don't let it any closer!
```

**Solgaleo / Lunala:**

```text
# CherrygroveCity_Text_UBNecrozmaSensesLegend
  Light flares between the
  creature and your
  {STR_VAR_1}'s Poké Ball!

  It pulls back… then steadies,
  and stares.

KUKUI
  …It flinched.
  Cousin, that thing flinched.
```

### A saída dele

`UBShake` → `FADE_TO_WHITE` → `removeobject` do Necrozma → `FADE_FROM_WHITE`.

```text
# CherrygroveCity_Text_UBNecrozmaGone
KUKUI
  …And it's gone.

  Back through a hole it made
  itself.

LOOKER
  It opened the sky over a
  town, ate what came out of it,
  and left.

  That is the third time.
```

---

## Ato 6 — Conversa, o convite e o gancho

`fadedefaultbgm` — a ameaça foi embora e o tema de Cherrygrove volta.

As pessoas primeiro — Looker pergunta dos feridos antes do relatório.

```text
# CherrygroveCity_Text_UBAftermath
LOOKER
  Is anyone hurt?
  {PLAYER}? Your Pokémon?

  Chief?

  …Good. Good.

  The report can wait a moment.

ANABEL
  I am standing, Looker.

  And you may put all of it in
  the file this time.

  I'll sign it myself.
```

### Coreografia

`UBFlash` → o Incineroar é recolhido (`removeobject`), o que **libera (26,9)**
para o primeiro passo do Kukui. Depois o elenco se alinha **ortogonalmente** em
volta do jogador em (28,10) — e **ninguém** fica em (28,11), para a caixa de
texto não cobrir nenhum deles:

| Quem | De → para | Movimento |
|---|---|---|
| Looker | (27,9) → (28,9), ao norte do jogador | `walk_right > face_down` |
| Kukui | (26,8) → (29,10) pela linha 8 e pela coluna 29, a leste | `walk_right x3 > walk_down x2 > face_left` |
| Anabel | já está em (27,10); vira para leste | `turnobject DIR_EAST` |

```text
# CherrygroveCity_Text_UBKukuiRecognition
KUKUI
  {PLAYER}.

  That thing about not blinking?
  Write it down.

  Somebody out there is going to
  need it.

  And listen-when this is
  finished.

  Alola has a League now. I put
  it together myself.

  It's still missing the one
  thing you can't build.

  Somebody worth standing at the
  end of it.

  Come take a swing at it,
  cousin. I mean that.
```

Com a família Cosmog na equipe, um bloco a mais:

```text
# CherrygroveCity_Text_UBAftermathCosmog
KUKUI
  It looked at your
  {STR_VAR_1}.

  Not at me. Not at the Ultra
  Beasts. At that.

ANABEL
  A child of the stars,
  and a thing made of light.

  Keep it where you can reach it,
  {PLAYER}.
```

```text
# CherrygroveCity_Text_UBAftermathLegend
KUKUI
  It pulled back from
  your {STR_VAR_1}. I saw it.

  Back home, {STR_VAR_1} is the
  sky itself, cousin.

ANABEL
  Whatever that creature
  is made of, it knew exactly
  what it was looking at.

  That is worth more than my
  instruments gave me all week.
```

### O gancho

**Sem destino** — a Missão 4 é revelada no briefing de Olivine. O Kukui **não**
vai junto: o que ele faz é a corrente que **começa** a Missão 4 — vai ler, acha
as seis semanas de "sensor quebrado" do Elm e telefona para a polícia.

> Esta caixa e `OlivineCity_House1_Text_BriefingM4` são **um par**. Nunca edite
> uma sem a outra.

```text
# CherrygroveCity_Text_UBHook
LOOKER
  Professor, you will now
  come off this beach and eat
  something.

  That is not a request.

KUKUI
  Yeah, yeah.

ANABEL
  The readings haven't
  settled. It will open another
  one.

  Where, and when, we don't know
  yet.

LOOKER
  So we keep watching.

  Rest, {PLAYER}. Then come back
  to our house in Olivine.

  The moment something opens, you
  will be the first to know.

KUKUI
  I'm going home,
  cousin. But not tonight.

  Tonight I'm going to sit in
  every library in this region
  and read every log nobody
  thought was worth sending.

  Somebody out there has been
  writing this down for weeks and
  calling it a broken sensor.

  I'd bet the League on it.
```

`FADE_TO_BLACK` → a flag do evento é limpa, o estado vira 8 → `warpsilent` no
mesmo lugar (28,10). A cidade repovoa (os catorze moradores **e** os Pokémon de
presente do Friendly Trader), o elenco some, as portas destrancam e o follower
volta, tudo debaixo do fade.

---

## Apêndice — movimentos, em um lugar só

| Label | Sequência |
|---|---|
| `CherrygroveCity_Movement_StepDownFaceLeft` | walk_down > face_left |
| `CherrygroveCity_Movement_PlayerToLine` | walk_down x2 > face_left |
| `CherrygroveCity_Movement_AnabelToLine` | walk_down x2 > face_left |
| `CherrygroveCity_Movement_PulseInPlaceRight` | walk_in_place_fast_right x3 |
| `CherrygroveCity_Movement_AttackInPlaceDown` | walk_in_place_fast_down x2 |
| `CherrygroveCity_Movement_AttackInPlaceLeft` | walk_in_place_fast_left x2 |
| `CherrygroveCity_Movement_UBKnockedBack` | lock_facing_direction > walk_fast_left x2 > unlock_facing_direction |
| `CherrygroveCity_Movement_UBPulledIn` | lock_facing_direction > walk_slow_left > unlock_facing_direction |
| `CherrygroveCity_Movement_NecrozmaLean` | walk_slow_right |
| `CherrygroveCity_Movement_AnabelStepWest` | walk_fast_left |
| `CherrygroveCity_Movement_PlayerPulledAside` | lock_facing_direction > walk_fast_right > unlock_facing_direction |
| `CherrygroveCity_Movement_AnabelTakesTheFront` | walk_fast_down > face_left |
| `CherrygroveCity_Movement_LookerToAnabel` | walk_fast_down |
| `CherrygroveCity_Movement_LookerToPlayerSide` | walk_right > face_down |
| `CherrygroveCity_Movement_KukuiToPlayer` | walk_right x3 > walk_down x2 > face_left |

**Flash da cena:** `fadescreenswapbuffers FADE_TO_WHITE` / `FADE_FROM_WHITE`, nunca
`fadescreen` — o motivo está no
[`_IMPLEMENTATION`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) §14.

**Tremor da cena** (`UBShake`): `ShakeCamera` com pan 1/1, 12 tremidas, delay 4.

**Trilha:** `fadeoutbgm 4` quando a Anabel sente; `playbgm MUS_DP_LEGEND_APPEARS,
TRUE` quando o Necrozma aparece; `fadedefaultbgm` na conversa final.
