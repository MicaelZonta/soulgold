# Mahogany — Necrozma, Xurkitree + Celesteela (Rift Mission 2) — roteiro

**O que é este arquivo:** a cena como ela acontece na tela — as falas literais
(em inglês, exatamente como estão na ROM) e a coreografia, beat a beat.
Estado, flags, objetos, arquivos tocados, riscos e checklist de teste ficam em
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md).

**Fonte:** `data/maps/OlivineCity_House1/scripts.pory`,
`data/maps/Mahoganytown/scripts.inc` (revisão 5, 23/09/2026).
Ao mudar uma fala, mude no `.pory`/`.inc` e traga a mudança para cá.

**Vozes:** Lillie observa, explica e **corrige o próprio plano em voz alta**;
Pryce seco, dono da cidade, cuida do povo antes de tudo; Looker teatral, direto
no perigo; Anabel precisa. **Ninguém nomeia o Necrozma** — para o Looker e a
Anabel é "the creature from Blackthorn"; a Lillie **reconhece** e se recusa a
falar na rua. O nome fica para a reunião de Olivine.

---

## Elenco e marcação

```text
       x= 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23
  y=19     #  W  #  #  .  .  .  .  .  .  #  #  W  #  #   W (10,19) Ginásio, (21,19) Centro
  y=20     .  O  P  X  >  >  .  .  .  .  .  .  f  .  .   f (21,20) pouso do Fly
  y=21     .  B  M  :  >  n  N  L  .  .  .  .  t  .  .   t (21,21) ÚNICO tile para falar com Looker
  y=22     .  .  .  C  >  >  *  .  .  n  L  K  A  .  .   * (17,22) posição do jogador
  y=23     #  #  #  #  #  #  #  #  #  #  #  #  #  #  #

  Antes da cena: O velho (10,20)  B menino (10,21)  P Pryce (11,20)  M Mamoswine (11,21)
                 n Ninetales (19,22)  L Lillie (20,22)  K Looker (21,22)  A Anabel (22,22)
  Na cena:       Pryce → (14,20), Mamoswine → (13,21) (linha de frente)
                 Ninetales → (15,21) → (14,21) na parede; Lillie → (16,21)
                 Necrozma aparece em (11,21); X Xurkitree (12,20), C Celesteela (12,22)
                 ':' (12,21) = o vão entre as duas, onde a parede de gelo sobe
```

Câmera com o jogador em (17,22): x 10..24. A porta do Ginásio (10,19) está na
tela — a evacuação e a saída do Pryce acontecem **à vista**. **Ninguém fica ao
sul do jogador** em nenhum momento.

---

## Ato 1 — O briefing da Missão 2 (Olivine City, House1)

Mesma coreografia da Missão 1: "!" sobre o Looker, os dois descem até o jogador
na porta (4,8) e voltam no fim. O que muda é só o texto.

Cita a ligação do Pryce e o apagão, e mais nada: a Lillie, a evacuação e o
Necrozma são o que o jogador **encontra** em Mahogany.

```text
# OlivineCity_House1_Text_BriefingM2
LOOKER
  {PLAYER}! Your timing
  is uncanny. It has started
  again. Mahogany Town.

ANABEL
  Two signatures again.
  One electrical. One… heavy.

LOOKER
  The town lost its power
  three nights ago.

  Every lamp, every machine.
  Only the Pokémon Center still
  has light.

ANABEL
  The readings come from
  the town itself. Every night,
  at the same hour.

  No sign of the light from
  Blackthorn. Not yet.

LOOKER
  The Gym Leader, Pryce,
  telephoned us himself.

  He said four words.
  “Lights out. Come now.”

  …I have decided to find that
  reassuring.

ANABEL
  Meet us by the Pokémon
  Center, {PLAYER}.

  Prepare for two of them.
  Not one.
```

"No sign of the light from Blackthorn. Not yet." é a promessa que a cena quebra.

### Depois do briefing — "vá na frente"

```text
# OlivineCity_House1_Text_LookerGoAheadM2
LOOKER
  Mahogany, {PLAYER}!
  We are right behind you.
```

```text
# OlivineCity_House1_Text_AnabelGoAheadM2
ANABEL
  Go on.

  Mr. Pryce does not strike me
  as a man who calls for help
  lightly.
```

---

## Ato 2 — Mahogany, antes da cena

Cidade apagada e vazia. Toda porta recusa o jogador **menos a do Centro Pokémon**.

```text
# Mahoganytown_Text_DoorLocked
  The door is locked tight.

  A note is taped to it, stiff
  with frost:

  “Everyone is safe. This door
  stays shut until I say so.
  --Pryce”
```

### Conversas soltas

**Anabel** (`UBAnabel`) — `faceplayer`.

```text
# Mahoganytown_Text_UBAnabelIdle
ANABEL
  The Pokémon Center
  runs on its own generator.

  It is the only light left in
  this town. Heal there first.

  Then speak with Looker.
```

**Lillie** (`UBLillie`) — a descoberta da missão, mas **não** uma desconhecida.
Ela olha para o norte, para a rua; o `turnobject DIR_NORTH` no fim devolve o
olhar dela para lá.

```text
# Mahoganytown_Text_UBLillieIdle
LILLIE
  {PLAYER}! It's really
  you.

  The detective kept saying the
  Champion was on the way.

  He never said it would be
  someone I've battled three
  times.

  I stopped in Mahogany for one
  night. Ninetales loves this
  cold.

  Then the lights went out, and
  I saw what was standing in
  the street.

  I knew what they were the
  moment I saw them. I was
  never supposed to see one
  again.

  I've written down everything
  for two days and I still
  don't understand any of it.

  Talk to Looker. I'd rather
  show it to everyone at once.
```

Com a família Cosmog na equipe, a Ninetales dá "!" primeiro e a Lillie emenda —
ela lembra do Nebby, e **nunca** chama o Pokémon do jogador de Nebby.

**Cosmog:**

```text
# Mahoganytown_Text_UBLillieIdleCosmog
LILLIE
  Your {STR_VAR_1} keeps
  looking up at the sky.

  Nebby used to do that. Right
  before something went wrong.

  …Keep it close tonight.
  Please.
```

**Cosmoem:**

```text
# Mahoganytown_Text_UBLillieIdleCosmoem
LILLIE
  Your {STR_VAR_1} has gone
  so still.

  Nebby went still like that,
  once. It was the hardest
  night of my life.

  …I'm sorry. It's only the
  dark. Keep it close.
```

**Solgaleo / Lunala:**

```text
# Mahoganytown_Text_UBLillieIdleLegend
LILLIE
  Your {STR_VAR_1} hasn't
  taken its eyes off the west
  end of town since you came.

  Whatever comes tonight…
  I think it already knows.
```

**Pryce** (`UBPryce`) — **sem** `faceplayer`: está ocupado evacuando e fala por
cima do ombro. Só alcançável de (12,20).

```text
# Mahoganytown_Text_UBPryceIdle
PRYCE
  Hm. The Champion.

  Every soul in Mahogany is
  under my Gym tonight.

  Every soul but this one.

OLD_MAN
  I'm not leaving my
  lamp, Pryce.

PRYCE
  …The detective is by
  the Pokémon Center. Go.

  I've been arguing with this
  man for forty years. I can
  manage one more night.
```

Com a família Cosmog:

```text
# Mahoganytown_Text_UBPryceIdleCosmog
PRYCE
  That {STR_VAR_1} of yours
  is shivering in its ball.

  It isn't the cold.
  I would know.
```

**Mamoswine** (`UBMamoswine`) — grito + narração.

```text
# Mahoganytown_Text_UBMamoswineIdle
  Mamoswine is standing guard
  beside Pryce, still as ice.
```

**O velho** (`UBOldMan`) — volta a encarar o Pryce (leste) no fim.

```text
# Mahoganytown_Text_UBOldManIdle
  Sixty years I've lit the lamp
  on my porch. Every night.

  I'm not hiding under a Gym
  because the power's out!
```

**O menino** (`UBBoy`) — volta a olhar para o avô (norte) no fim.

```text
# Mahoganytown_Text_UBBoyIdle
  Grandpa says the monster only
  eats electricity.

  …It doesn't eat Pokémon too,
  does it?
```

---

## Ato 3 — O convite do Looker (o último ponto de saída)

Só dá para falar com ele de (21,21). A leitura da Lillie vem **antes** do SIM,
de propósito: ela precisa ter contado ao grupo o que viu antes de alguém se
mexer. O que ela ainda **não** sabe — que separar as duas não basta — é o que a
cena ensina.

```text
# Mahoganytown_Text_UBLookerGreet
LOOKER
  {PLAYER}! You came.
  Good. Very good.

  And yes, before you ask. That
  is a young lady with a
  notebook.

  She was here before any of us.
  Two days, alone, in a town
  with no light.

  Mr. Pryce asked her to leave.
  Twice. She thanked him very
  politely, both times.
```

```text
# Mahoganytown_Text_UBLillieTheory
LILLIE
  I'm sorry. I couldn't
  go. Not before I understood
  them.

  There are two, and they come
  at about the same hour.

  I've never seen where they
  come from. The street is too
  dark, and I was watching from
  a window.

  By the time I find them,
  they're already there.

  But I did see this much.

  One of them pulls the
  electricity out of
  everything. The lamps. The
  lines. The houses.

  The other takes it, burns it,
  and gives it right back.

ANABEL
  A closed loop. Each one
  keeping the other alive.

LILLIE
  …Yes. I think so.

  I couldn't have said it that
  cleanly.

LOOKER
  Hm. That is a great
  deal to conclude from one
  notebook, mademoiselle.

LILLIE
  It's two nights of
  notes, and I could still be
  wrong about all of it.

  I'd rather be wrong out loud
  than quiet and right.

ANABEL
  My instruments say
  what her notebook says. And
  they say tonight is close.

LILLIE
  Then… if we keep them
  apart, neither one can feed
  the other.

  It's the only idea I have.
```

A pergunta (`MSGBOX_YESNO`):

```text
# Mahoganytown_Text_UBReady
LOOKER
  Then we do it her way.

  Once it opens, there is no
  stepping back, {PLAYER}.

  Are you and your Pokémon
  ready?
```

**NÃO:**

```text
# Mahoganytown_Text_UBNotReady
LOOKER
  Of course. Heal up.
  Check your team.

  Miss Anabel says we still have
  a little time, and I have
  learned not to argue with her
  instruments.
```

**SIM →** a cena começa e não para mais.

---

## Ato 4 — A cena

`lockall` + `hidefollower`.

### Beat 1 — Aproximação (a ordem é obrigatória)

Lillie/Ninetales **primeiro**, depois o jogador, depois Looker/Anabel — a
Ninetales passa por (17,22), que é o tile final do jogador, e Looker/Anabel só
sobem quando o jogador desocupa (21,21).

| Quem | De → para | Movimento |
|---|---|---|
| Ninetales (vai na frente) | (19,22) → (15,21) | `walk_left x4 > walk_up > face_left` |
| Lillie | (20,22) → (16,21) | `walk_up > walk_left x4 > face_left` |
| Jogador | (21,21) → (17,22) | `walk_left x4 > walk_down > face_left` |
| Looker e Anabel | (21,22) e (22,22), um passo acima | `walk_up > face_left` |

### Beat 2 — A evacuação, terminada na tela

A Anabel dá a hora; a Lillie chama o Pryce **pelo morador**, não pelo relógio.

```text
# Mahoganytown_Text_UBTimeIsClose
ANABEL
  The readings are
  climbing. It is close.

LILLIE
  Mr. Pryce, please!
  He shouldn't be out here!
```

O velho vira para o Pryce (leste).

```text
# Mahoganytown_Text_UBPryceEvacuates
PRYCE
  You heard her, Hector.
  Inside. Now.

OLD_MAN
  Sixty years, Pryce.
  Not one night without my lamp.

PRYCE
  Then don't make tonight
  the night I lose you over it.

  You'll light it tomorrow.
  Take the boy. In.
```

`opendoor 10,19` → velho (10,20) → (10,19) `walk_up > set_invisible`,
`removeobject` → **depois** o menino (10,21) → (10,19)
`walk_up x2 > set_invisible`, `removeobject` → `closedoor`.
Sequencial: o menino pisa no tile que o velho acabou de deixar.

### Beat 3 — Pryce assume a linha de frente

| Quem | De → para | Movimento |
|---|---|---|
| Pryce | (11,20) → (14,20) | `walk_right x3 > face_left` |
| Mamoswine | (11,21) → (13,21) | `walk_right x2 > face_left` |

Linhas diferentes → andam juntos. Pryce vira para o leste (o jogador em (17,22)
está a dx=+3 dele, que domina) e diz **ele mesmo** que evacuou:

```text
# Mahoganytown_Text_UBPryceMeets
PRYCE
  That's the last of
  them. Mahogany is empty.

  Three nights without light.
  I moved every family into my
  Gym myself.

  So. You're the Champion the
  detective keeps promising me.

  I've stood in the cold for
  fifty years, child. I don't
  go inside when told.

  The girl says it comes at
  this hour. We'll see it
  together.
```

Volta a olhar para o oeste.

### Beat 4 — A luz chega (ninguém a anuncia)

A Anabel vê o instrumento sair do que ela conhece; o Pryce vê a luz na rua dele.
A Lillie **não fala aqui**: a voz dela chega no choque.

```text
# Mahoganytown_Text_UBLightComing
ANABEL
  It's starting--

  …No. That is not the reading
  I know. That is something
  else.

PRYCE
  Light. In the middle of
  my street.
```

`UBShake` → `FADE_TO_WHITE` → `addobject` do Necrozma em **(11,21)**, o tile que
o Mamoswine acabou de largar → `FADE_FROM_WHITE` → grito → "!" sobre Lillie,
Pryce, Looker e Anabel.

```text
# Mahoganytown_Text_UBNecrozmaArrives
LOOKER
  That… that is the
  creature from Blackthorn!

ANABEL
  Then it is not only
  feeding on the rifts.

  It is the one opening them.

LILLIE
  …No.

  No. No, not that. Not here.

ANABEL
  Lillie?

LILLIE
  I know that light. I
  know it.

  It has no business being
  anywhere near this town.

  …Please don't ask me. Not
  now.

PRYCE
  Whatever it is, it's
  standing in my town.

  Mamoswine! Blizzard!
```

### Beat 5 — A autoridade local tenta e falha

Mamoswine ataca no lugar, para o oeste, ao longo da linha 21:
`walk_in_place_fast_left x2` + grito → `UBFlash` → Necrozma
`walk_in_place_fast_right x3`.

```text
# Mahoganytown_Text_UBNoEffect
PRYCE
  …Nothing.
  Not even frost on it.

  Fifty years. I've never seen a
  Pokémon shrug off a Blizzard.

LOOKER
  In Blackthorn it was
  the same. It does not fight
  back. It does not even look.
```

### Beat 6 — A ruptura

Grito do Necrozma → `UBShake` → `FADE_TO_WHITE` → `addobject` de Xurkitree
(12,20) e Celesteela (12,22), **uma de cada lado da fenda** → `FADE_FROM_WHITE`
→ os dois gritos.

```text
# Mahoganytown_Text_UBAppear
ANABEL
  Rift opening!
  Two signatures!

  …I felt that one before the
  readings moved.

  Never mind. Later.

LOOKER
  Xurkitree!
  And Celesteela!
```

### Beat 7 — A sinergia, mostrada antes de explicada

Xurkitree pulsa (`walk_in_place_fast_right x3` = drena), manda
a corrente para baixo (`walk_in_place_fast_down x3 > face_right`), flash, e a
Celesteela recebe de baixo (`walk_in_place_fast_up x3 > face_right`) com grito.

```text
# Mahoganytown_Text_UBSynergy
  Xurkitree drank the last glow
  out of the street…

  …and the current leapt across
  to Celesteela, which burned
  it like fuel.

ANABEL
  Energy passing between
  the two signatures. Both ways.

LILLIE
  That's it. That's what
  I kept seeing from the
  window.

  One drinks, the other burns.
  Together they never run dry.
```

### Beat 8 — Perigo direto ao jogador

```text
# Mahoganytown_Text_UBCharge
LOOKER
  {PLAYER}! The heavy one!
  It is coming at you!
```

Celesteela (12,22) → (15,22) pela linha 22, vazia:
`walk_fast_right x3` — para **dois tiles antes** do jogador.
A Ninetales, logo acima em (15,21), ataca para baixo
(`walk_in_place_fast_down x2`) + grito → `UBShake` →
`UBFlash` → a Celesteela é jogada de volta a (12,22) **de costas**, sem virar o
rosto: `lock_facing_direction > walk_fast_left x3 > unlock_facing_direction`.

```text
# Mahoganytown_Text_UBSaved
LILLIE
  Ninetales, Icy Wind!
  Keep it away from {PLAYER}!

  …Are you all right?
  Good. Good.

PRYCE
  Hmph. That one's got a
  good cold in her.
```

### Beat 9 — A escolha

Estrutura padrão das Rift Missions. Aqui a escolha vale para as **duas** rodadas.
Ninguém precisa virar: jogador (17,22), Lillie (16,21) e Ninetales (15,21) já
estão a leste das duas em x=12.

```text
# Mahoganytown_Text_UBChoosePrompt
LILLIE
  We keep them apart.
  Now, before they feed again.

  Pick one, {PLAYER}. Ninetales and
  I will hold the other.

  …I think this works. I'm not
  certain. I'm sorry.

PRYCE
  And I'll watch the
  crystal one. For whatever
  good it does.
```

Opções: `  Xurkitree` / `  Celesteela`.
"!" sobre a escolhida, e:

```text
# Mahoganytown_Text_UBPickedXurkitree
LILLIE
  Then the tall one is
  yours.

  Ninetales, Snow! Keep the
  heavy one on the ground!
```

```text
# Mahoganytown_Text_UBPickedCelesteela
LILLIE
  Then the heavy one is
  yours.

  Ninetales, get between the
  tall one and the lines!
```

### Beat 10 — Rodada 1

Boss contra a escolhida, **curto de propósito**: precisa parecer vitória para a
virada funcionar. Números em
[`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) §4.4.

Se não termina em vitória, a cena inteira se desfaz — rodada 1 inclusive:

```text
# Mahoganytown_Text_UBGotAway
LOOKER
  They slipped back
  through the tear…

LILLIE
  It will open again.
  It always does.

LOOKER
  Then we regroup,
  and we are ready for it.
```

---

## Ato 5 — A virada: a sinergia revive a derrotada

A Lillie comemora e se corta no meio.

**Se o jogador escolheu o Xurkitree:**

```text
# Mahoganytown_Text_UBDownXurkitree
LILLIE
  It's down! {PLAYER}, you
  did it! It's--

  …Wait. Celesteela!
```

A parceira **manda** — Celesteela pulsa para cima
(`walk_in_place_fast_up x3 > face_right`) + grito → `UBFlash` → o Xurkitree
**recebe** (`walk_in_place_fast_down x3 > face_right`) + grito.

```text
# Mahoganytown_Text_UBRevivedXurkitree
  Celesteela's engines roared,
  and the heat poured across
  the street into Xurkitree.

  Xurkitree stood up again,
  crackling, whole.
```

**Se escolheu a Celesteela:**

```text
# Mahoganytown_Text_UBDownCelesteela
LILLIE
  It's down! {PLAYER}, you
  did it! It's--

  …Wait. Xurkitree!
```

```text
# Mahoganytown_Text_UBRevivedCelesteela
  Xurkitree's cables blazed,
  and the current poured across
  the street into Celesteela.

  Celesteela rose again, its
  engines burning, whole.
```

### O plano refeito

"!" sobre Lillie, Pryce, Looker e Anabel. Ela **admite o erro na frente de todos**
e refaz o plano.

```text
# Mahoganytown_Text_UBLilliePlan
LOOKER
  Impossible!
  We had it!

ANABEL
  The loop. Whatever
  one loses, the other gives
  back.

PRYCE
  Like melting a glacier
  with a match.

LILLIE
  …I was wrong.

  Keeping them apart isn't
  enough. The current still
  jumps the gap between them.

  So we close the gap. With
  something it can't cross.

  Ice doesn't carry current.

  Mr. Pryce, can Mamoswine make
  ice? A lot of it? Right
  between them?

PRYCE
  Can it make ice.

  …Girl, you are standing in
  Mahogany.

ANABEL
  Then do it. But first,
  {PLAYER}. Your Pokémon.
```

### Cuidado antes da luta

Anabel (22,21) → (18,22), ao lado do jogador (a linha 22 está vazia desde a
aproximação): `walk_down > walk_left x4 > face_left`. Ela fica ali até o
fim da cena. O jogador vira para ela.

```text
# Mahoganytown_Text_UBAnabelHeals
ANABEL
  Hold still. Let me see
  them. All of them.
```

`FADE_TO_BLACK` → `HealPlayerParty` → `MUS_HEAL` → `FADE_FROM_BLACK`.

```text
# Mahoganytown_Text_UBAnabelHealed
ANABEL
  There. Every one of
  them, ready.

  Now finish it.
```

### A parede de gelo

O jogador vira de volta para o oeste. Ninetales (15,21) → (14,21), ao lado do
Mamoswine (13,21): `walk_left > face_left`.

```text
# Mahoganytown_Text_UBWallOrder
LILLIE
  Ninetales, Aurora Veil!
  Right between them!

PRYCE
  Mamoswine.
  Freeze it solid.
```

Os dois atacam para o oeste, no vão (12,21):
`walk_in_place_fast_left x2` + gritos → `UBShake` → `UBFlash`.
As duas UBs tentam a ligação de novo (uma pulsa para a outra) e morre no gelo.

```text
# Mahoganytown_Text_UBWallHolds
  A wall of ice rose across the
  street, between Xurkitree and
  Celesteela.

  The current crackled against
  it… and died.

LILLIE
  It's holding!
  They can't reach each other!

  {PLAYER}, now! This time it
  stays down!
```

**A sinergia nossa** (Lillie + Pryce, gelo de dois Pokémon) vence **a sinergia
deles**. É a leitura do tema da missão.

### Rodada 2

Mesma escolhida, agora no alvo da escala do design. Perder aqui recomeça tudo.

---

## Ato 6 — A absorção

A luta da Lillie é narrativa: resolve junto com a vitória do jogador e só a fala
muda com a escolha.

```text
# Mahoganytown_Text_UBLillieFoughtCelesteela
LILLIE
  Ninetales! …It's down.
  Celesteela's down too.

  It kept reaching for the
  other one. There was nothing
  left to reach.
```

```text
# Mahoganytown_Text_UBLillieFoughtXurkitree
LILLIE
  Ninetales! …It's down.
  Xurkitree's down too.

  It kept pulling at the wall.
  Ice doesn't give anything
  back.
```

Então — o padrão de **todas** as missões:

1. Necrozma pulsa (`walk_in_place_fast_right x3`) + grito.
2. As duas são **arrastadas de costas** um tile até ele, (12,20)→(11,20) e
   (12,22)→(11,22): `lock_facing_direction > walk_slow_left > unlock_facing_direction`.
3. `UBShake` → `FADE_TO_WHITE` → `removeobject` das duas → `FADE_FROM_WHITE` → grito.
4. "!" sobre Pryce, Lillie, Looker e Anabel.

```text
# Mahoganytown_Text_UBAbsorbed
PRYCE
  It's… swallowing them.

LOOKER
  Again! Just as in
  Blackthorn. Both of them!

ANABEL
  It opened the tear,
  let them feed for three
  nights…

  …and now it collects them.

LILLIE
  It's feeding.
  The same way it did before.

LOOKER
  Before? Mademoiselle,
  before WHEN?

LILLIE
  …Later. I promise.
```

O corte da Lillie ("…Later. I promise.") é o mesmo do Gladion em Blackthorn
("In Alola." — "Later."): os dois irmãos sabem, nenhum dos dois conta ainda.

### Reação opcional à família Cosmog

Checada **depois** das batalhas. Necrozma dá um passo para o jogador,
(11,21)→(12,21) — o vão onde a parede esteve, vazio:
`walk_slow_right`. "!" sobre o jogador + grito.

**Cosmog / Cosmoem:**

```text
# Mahoganytown_Text_UBNecrozmaSensesCosmog
  The creature is staring past
  you… at the Poké Ball that
  holds your {STR_VAR_1}.

  Your {STR_VAR_1} is trembling.

LILLIE
  No! Not that one!
  Ninetales, stay by {PLAYER}!
```

**Solgaleo / Lunala:**

```text
# Mahoganytown_Text_UBNecrozmaSensesLegend
  Light flares between the
  creature and your
  {STR_VAR_1}'s Poké Ball!

  It recoils… then steadies,
  and stares.

  Your {STR_VAR_1} doesn't look
  away.
```

### A saída dele

`UBShake` → `FADE_TO_WHITE` → `removeobject` do Necrozma → `FADE_FROM_WHITE`.

```text
# Mahoganytown_Text_UBNecrozmaGone
PRYCE
  …Gone.

LOOKER
  And the lamps!
  {PLAYER}, look! The lamps are
  coming back on!
```

---

## Ato 7 — Conversa, a volta do Pryce e o gancho

### Coreografia

Looker (21,21) → (18,21), olhando oeste: `walk_left x3 > face_left`.
A Anabel já está em (18,22) desde a cura. Depois: Pryce, Mamoswine e Ninetales
viram para leste; a Lillie para **sul** (dx=+1 e dy=+1 empatam — sul é o que
impede ela de olhar através da Ninetales); o jogador vira para leste.

### A conversa

As pessoas primeiro — Looker pergunta dos feridos antes do relatório.

```text
# Mahoganytown_Text_UBAftermath
LOOKER
  Is anyone hurt?
  {PLAYER}? Mademoiselle?
  Mr. Pryce?

  …Good. Then the report can
  wait a moment.

PRYCE
  Hmph. I've seen more
  winters than the three of you
  put together, detective.

  Not one like this, though.

ANABEL
  Two Ultra Beasts that
  kept each other alive. And
  something that came back for
  both of them.

  Twice now. That is not chance.
  That is a pattern.

LOOKER
  Mademoiselle. You said
  you knew that light.

LILLIE
  …I do. I saw it in
  Alola.

  I thought that was the end of
  it. I thought it was over.

  I'll tell you everything I
  know. Truly.

  Just… not in the middle of the
  street. Not tonight.

LOOKER
  Then we will wait.
  Waiting is also detective
  work.
```

Com a família Cosmog na equipe, um bloco a mais:

```text
# Mahoganytown_Text_UBAftermathCosmog
LILLIE
  {PLAYER}. It looked at
  your {STR_VAR_1}. Only at it.

  Promise me you'll keep it
  close. Always.

ANABEL
  In Blackthorn, and
  now here. It keeps finding
  one.

  I would very much like to know
  why.
```

```text
# Mahoganytown_Text_UBAftermathLegend
LILLIE
  It backed away from
  your {STR_VAR_1}.

  I've never seen that light
  back away from anything.

ANABEL
  Something made of
  light, afraid of a legend of
  the sky… That means
  something.
```

### Pryce volta para o seu povo

O jogador vira para o oeste.

```text
# Mahoganytown_Text_UBPryceGoodbye
PRYCE
  Champion. Mahogany owes
  you a night of light.

  And you, girl. That was clear
  thinking with a storm in your
  face. Winter would approve.

  I'll tell them they can go
  home.

  And Hector can light his
  blasted lamp.
```

`opendoor 10,19` → Pryce (14,20) → (10,19)
`walk_left x4 > walk_up > set_invisible`, `removeobject` → **depois** o Mamoswine
(13,21) → (10,19) `walk_left x3 > walk_up x2 > set_invisible`, `removeobject` →
`closedoor`. Sequencial: os dois últimos tiles do Mamoswine são os do Pryce.

### O gancho

O jogador vira para o leste. **Sem destino** — a Missão 3 só é revelada no
briefing seguinte.

```text
# Mahoganytown_Text_UBHook
ANABEL
  Lillie. May I copy your
  notes? Your reading was better
  than my instruments.

LILLIE
  You can have all of
  them.

  I'd like to stay a few more
  days. In case it comes back.

ANABEL
  The readings haven't
  settled. It will open another
  rift.

  Where, and when, we don't know
  yet.

LOOKER
  So we keep watching.

  Rest, {PLAYER}. Then come back
  to our house in Olivine.

  The moment something opens,
  you will be the first to know.

LILLIE
  {PLAYER}…
  Thank you for listening.

  To my plan, I mean. Both of
  them. Even the wrong one.
```

`FADE_TO_BLACK` → a flag do evento é limpa, o estado vira 6 → `warpsilent` no
mesmo lugar (17,22). A cidade repovoa, o elenco some, as portas destrancam e o
follower volta, tudo debaixo do fade.

---

## Apêndice — movimentos, em um lugar só

| Label | Sequência |
|---|---|
| `Mahoganytown_Movement_NinetalesAdvance` | walk_left x4 > walk_up > face_left |
| `Mahoganytown_Movement_LillieAdvance` | walk_up > walk_left x4 > face_left |
| `Mahoganytown_Movement_PlayerToLine` | walk_left x4 > walk_down > face_left |
| `Mahoganytown_Movement_StepUpFaceLeft` | walk_up > face_left |
| `Mahoganytown_Movement_EnterGymFromFront` | walk_up > set_invisible |
| `Mahoganytown_Movement_BoyEnterGym` | walk_up x2 > set_invisible |
| `Mahoganytown_Movement_PryceToFront` | walk_right x3 > face_left |
| `Mahoganytown_Movement_MamoswineToFront` | walk_right x2 > face_left |
| `Mahoganytown_Movement_AttackInPlaceLeft` | walk_in_place_fast_left x2 |
| `Mahoganytown_Movement_AttackInPlaceDown` | walk_in_place_fast_down x2 |
| `Mahoganytown_Movement_PulseInPlaceRight` | walk_in_place_fast_right x3 |
| `Mahoganytown_Movement_UBFeedDown` | walk_in_place_fast_down x3 > face_right |
| `Mahoganytown_Movement_UBFeedUp` | walk_in_place_fast_up x3 > face_right |
| `Mahoganytown_Movement_UBCharge` | walk_fast_right x3 |
| `Mahoganytown_Movement_UBKnockedBack` | lock_facing_direction > walk_fast_left x3 > unlock_facing_direction |
| `Mahoganytown_Movement_NinetalesToWall` | walk_left > face_left |
| `Mahoganytown_Movement_UBPulledIn` | lock_facing_direction > walk_slow_left > unlock_facing_direction |
| `Mahoganytown_Movement_NecrozmaLean` | walk_slow_right |
| `Mahoganytown_Movement_LookerToPlayer` | walk_left x3 > face_left |
| `Mahoganytown_Movement_AnabelToPlayer` | walk_down > walk_left x4 > face_left |
| `Mahoganytown_Movement_PryceToGym` | walk_left x4 > walk_up > set_invisible |
| `Mahoganytown_Movement_MamoswineToGym` | walk_left x3 > walk_up x2 > set_invisible |

**Flash da cena:** `fadescreenswapbuffers FADE_TO_WHITE` / `FADE_FROM_WHITE`, nunca
`fadescreen` — o motivo está no
[`_IMPLEMENTATION`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) §15.

**Tremor da cena** (`UBShake`): `ShakeCamera` com pan 1/1, 12 tremidas, delay 4.
