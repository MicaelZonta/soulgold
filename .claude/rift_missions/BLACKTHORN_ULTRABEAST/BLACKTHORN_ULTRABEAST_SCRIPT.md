# Blackthorn — Necrozma, Buzzwole + Pheromosa (Rift Mission 1) — roteiro

**O que é este arquivo:** a cena como ela acontece na tela — as falas literais
(em inglês, exatamente como estão na ROM) e a coreografia, beat a beat.
Estado, flags, objetos, arquivos tocados, riscos e checklist de teste ficam em
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md).

**Fonte:** `data/maps/NewBarkTown/scripts.pory`,
`data/maps/OlivineCity_House1/scripts.pory`,
`data/maps/BlackthornCity/scripts.inc` (revisão 4, 23/09/2026).
Ao mudar uma fala, mude no `.pory`/`.inc` e traga a mudança para cá.

**Vozes (design §3.1):** Looker teatral e caloroso, direto no perigo; Anabel
precisa e calma; Gladion curto e concreto; Clair orgulhosa, dona da cidade.
**Ninguém nomeia o Necrozma** — para todos é "the creature" / "that crystal
thing". **Ninguém diz onde será a próxima fenda.**

---

## Elenco e marcação

```text
       x= 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
  y=44     .  .  .  .  .  .  s  g  .  .  .  .  .  .  .     s/g spawn de Silvally/Gladion (escondidos)
  y=45     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
  y=46     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
  y=47     #  #  #  #  #  .  |  |  .  .  .  .  #  #  #
  y=48     .  #  #  W  #  .  v  |  .  .  .  .  #  #  W     W (16,48) Mart, (27,48) Centro
  y=49     #  .  .  .  K  C  :  G  .  .  .  .  .  .  f     f (27,49) pouso do Fly
  y=50     .  N  B  >  >  b  S  *  .  .  .  .  .  .  .     * (20,50) posição de combate do jogador
  y=51     .  .  P  >  >  p  .  .  .  .  .  .  .  .  .
  y=52     .  .  #  .  .  #  #  .  .  .  #  #  t  a  .     t (25,52) ÚNICO tile para falar com Looker
  y=53     #  #  #  #  #  #  #  .  .  .  #  #  L  A  #

  N Necrozma (14,50)   K Kingdra (17,49)   C Clair (18,49)   L Looker (25,53)   A Anabel (26,53)
  B Buzzwole (15,50) → carga até b (18,50) → recua para (17,50) → arrastado para (15,50)
  P Pheromosa (15,51) → carga até p (18,51) → recua para (17,51) → arrastado para (15,51)
  s Silvally (19,44) → desce a coluna 19 → jump_2 sobre (19,49) → S (19,50)
  g Gladion (20,44) → desce a coluna 20 → G (20,49), logo acima do jogador
```

O jogador entra a pé em (25,52) para falar com o Looker; a cena o leva a (20,50).
`#` = bloqueado (dump real, bit 11). Direções derivadas das coordenadas, com **y
crescendo para baixo**.

---

## Ato 1 — A ligação (New Bark Town)

Dispara sozinha no primeiro frame em New Bark depois do Hall of Fame, logo
**depois** da ligação do Elm. `pokenavcall` — tela de telefone, sem coreografia.

Abertura teatral que ele mesmo corrige; confissão do "homem de férias"; só o
pedido para ir a Olivine. **Nenhuma criatura, cidade ou nome é revelado no telefone.**

```text
# NewBarkTown_Text_LookerCall
LOOKER
  Hello? Is this {PLAYER}?
  The Champion of Johto?

  …Forgive me. Allow me to begin
  again.

  My name is Looker.
  International Police.

  We have not been introduced,
  but you may have passed me in
  Olivine. The man on holiday.

  Yes. That was me.

  I am afraid the holiday was
  not entirely a holiday.

  Something is happening in
  Johto, and I would rather
  explain it in person.

  Our house is on the north
  side of Olivine, closest to
  the Gym.

  Please come when you can.

  And, {PLAYER}… congratulations.
  Truly.
```

---

## Ato 2 — O briefing (Olivine City, House1)

O jogador entra pela porta em (4,8). O gatilho de frame encena; falar com o
Looker ou com a Anabel fora desse momento roda o mesmo texto **sem** coreografia.

### Antes do Hall of Fame — os dois "de férias"

```text
# OlivineCity_House1_Text_LookerHoliday
LOOKER
  Hm? Oh, pay no
  attention to moi.

  I am simply… on holiday.
  Yes. A holiday by the sea.
```

```text
# OlivineCity_House1_Text_AnabelHoliday
ANABEL
  Looker insists we are
  on vacation.

  He has been reading the same
  newspaper for three days.
```

### Coreografia da chegada

| Quem | De → para | Movimento |
|---|---|---|
| Looker | (4,5) → (4,7), olhando para baixo | `Common_Movement_ExclamationMark`, depois `walk_down x2 > face_down` |
| Anabel | (7,5) → (5,7), olhando para baixo | `walk_down x2 > walk_left x2 > face_down` |

Os dois caminhos não compartilham nenhum tile em nenhum passo → andam juntos.
No fim da fala voltam pelos caminhos inversos:
Looker `walk_up x2 > face_down`,
Anabel `walk_right x2 > walk_up x2 > face_down`.

### O briefing

Looker se apresenta de verdade e apresenta a chefe; Anabel explica o "holiday";
as leituras que em Alola precediam Ultra Wormholes; a definição de Ultra Beast
("não são vilões"); a ligação da Líder de Blackthorn; o ponto de encontro.
**Não menciona Gladion nem as duas Ultra Beasts** — são as surpresas da cena.

```text
# OlivineCity_House1_Text_Briefing
LOOKER
  Ah, {PLAYER}! You came.
  Please, come in.

  First, the truth. Looker,
  International Police.

  And this is my Chief, Anabel.

ANABEL
  Thank you for coming,
  Champion. We owe you an
  explanation for the holiday.

LOOKER
  We came to Johto
  following readings.
  Distortions in space.

  In Alola, readings like these
  came before Ultra Wormholes.

ANABEL
  Openings to other
  worlds. What comes through,
  we call Ultra Beasts.

  They are not villains. Most
  are lost, and frightened,
  and very strong.

LOOKER
  This morning the Gym
  Leader of Blackthorn called us.

  She described a Pokémon
  standing in the middle of her
  town. A Pokémon… made of light.

ANABEL
  Clair has ordered
  everyone indoors and is
  holding it off herself.

  We need to be there.
  And we would like you with us.

LOOKER
  Meet us by the Pokémon
  Center in Blackthorn.

  Prepare as you would for the
  League, {PLAYER}. Perhaps more.
```

### Depois do briefing — "vá na frente"

```text
# OlivineCity_House1_Text_LookerGoAhead
LOOKER
  Blackthorn, {PLAYER}!
  Clair cannot hold it forever.

  We are leaving right behind
  you!
```

```text
# OlivineCity_House1_Text_AnabelGoAhead
ANABEL
  Go on ahead.

  We'll be there before you
  reach the Pokémon Center.
```

---

## Ato 3 — Blackthorn, antes da cena

Cidade vazia. Toda porta recusa o jogador **menos a do Centro Pokémon**.

```text
# BlackthornCity_Text_DoorLocked
  The door is locked tight.

  A note is taped to it:
  “Stay inside until I say so.
  --Clair, Gym Leader”
```

### Conversas soltas

**Anabel** (`UBAnabel`) — `faceplayer`.

```text
# BlackthornCity_Text_UBAnabelIdle
ANABEL
  Every house is sealed
  and the Center is open.

  Clair hasn't taken one step
  back since we arrived.

  Speak with Looker when you
  are ready. Not before.
```

Com um Pokémon da família Cosmog na equipe, ela emenda:

```text
# BlackthornCity_Text_UBAnabelIdleCosmog
ANABEL
  …Is that a {STR_VAR_1}
  traveling with you?

  In Alola they call them
  children of the stars.

  Keep it close today.
```

**Clair** (`UBClair`) — **sem** `faceplayer`: ela não tira os olhos do Necrozma e
fala por cima do ombro.

```text
# BlackthornCity_Text_UBClairIdle
CLAIR
  Stay back. I've got it.

  It came out of a flash of
  light this morning and hasn't
  moved since.

  It isn't hurting anyone.
  It's… waiting for something.

  If you want to be useful, talk
  to the detective by the
  Pokémon Center.
```

**Kingdra** (`UBKingdra`) — grito + narração.

```text
# BlackthornCity_Text_UBKingdraIdle
  Kingdra won't take its eyes
  off the creature.
```

**Necrozma** (`UBNecrozma`) — narração pura; ele não reage ao jogador.

```text
# BlackthornCity_Text_UBNecrozmaIdle
  A Pokémon made of something
  like black crystal.

  Light keeps gathering along
  its body, then vanishing into
  it.

  It doesn't seem to notice
  you at all.
```

Com a família Cosmog na equipe, ele reage — e o grito toca:

```text
# BlackthornCity_Text_UBNecrozmaIdleCosmog
  …!

  It turned its head.

  Not toward you. Toward the
  Poké Ball that holds your
  {STR_VAR_1}.
```

---

## Ato 4 — O convite do Looker (o último ponto de saída)

Só dá para falar com ele de (25,52), olhando para baixo.

```text
# BlackthornCity_Text_UBLookerGreet
LOOKER
  {PLAYER}! You came.
  Good. Very good.

  Everyone is safe indoors.
  Clair saw to that before we
  even arrived.

  The creature is down the
  street, to the west.

  It has not moved in an hour.
  Neither has she.
```

**Equipe cheia E PC cheio** (o presente do fim da missão não caberia) — a "regra
da Anabel", dita **antes** de qualquer oferta e sem revelar o presente:

```text
# BlackthornCity_Text_UBNoRoom
LOOKER
  Ah--but first, one of
  Anabel's rules.

  On every operation, you keep
  room for one more Pokémon.
  In your party or your Boxes.

  Yours are both full.

  If a rift leaves a Pokémon
  stranded, it must have
  somewhere safe to go.

  Make some room, and come
  back to me. I will be here.
```

Senão, a pergunta (`MSGBOX_YESNO`):

```text
# BlackthornCity_Text_UBReady
LOOKER
  Once we step out
  there, there is no stepping
  back.

  Are you and your Pokémon
  ready?
```

**NÃO:**

```text
# BlackthornCity_Text_UBNotReady
LOOKER
  Of course. Heal up.
  Check your team.

  Clair can hold a little
  longer. She has made that
  very clear to me.
```

**SIM →** a cena começa e não para mais.

---

## Ato 5 — A cena

`lockall` + `hidefollower`. Daqui até o fim, tudo é scriptado.

### Beat 1 — O jogador entra na linha

| Quem | Movimento |
|---|---|
| Jogador | (25,52) → (20,50): `walk_up x2 > walk_left x5 > face_left` |
| Looker (25,53) e Anabel (26,53) | um passo acima, juntos: `walk_up > face_left` |

### Beat 2 — Clair reconhece o Campeão e ataca

Clair vira para o leste (o jogador em (20,50) está a dx=+2 dela, que domina o dy).

```text
# BlackthornCity_Text_UBClairArrive
CLAIR
  So you're the new
  Champion. Lance mentioned you.

  Then watch closely. I've been
  trying to hurt this thing for
  an hour.

  Kingdra! Dragon Pulse!
```

Ela volta a olhar para o oeste. Kingdra ataca **no lugar**, ainda de frente para o
Necrozma: `walk_in_place_fast_left x2` + grito → flash branco
(`UBFlash`) → Necrozma `walk_in_place_fast_right x3`.

```text
# BlackthornCity_Text_UBNoEffect
CLAIR
  …Nothing.
  Not even a scratch.

  It doesn't fight back.
  It just… drinks the light.
```

### Beat 3 — A ruptura

Grito do Necrozma → `UBShake` (tremor de câmera: 12 tremidas, delay 4) →
`FADE_TO_WHITE` → `addobject` de Buzzwole (15,50) e Pheromosa (15,51) →
`FADE_FROM_WHITE` → os dois gritos.

```text
# BlackthornCity_Text_UBAppear
ANABEL
  Rift opening!
  Two signatures!

LOOKER
  {PLAYER}, get back!
  They are coming right at you!
```

### Beat 4 — A carga

As duas passam direto pela Clair e vão **no jogador**, juntas, em linhas
deslocadas — a formação se mantém.

| Quem | De → para | Movimento |
|---|---|---|
| Buzzwole | (15,50) → (18,50) | `walk_fast_right x3` |
| Pheromosa | (15,51) → (18,51) | `walk_fast_right x3` |

### Beat 5 — O resgate

`addobject` de Silvally e Gladion em y=44 — seis linhas acima, fora da câmera.

| Quem | De → para | Movimento |
|---|---|---|
| Silvally | (19,44) → (19,50), entre o Buzzwole e o jogador | `walk_faster_down x4 > jump_2_down > face_left` |
| Gladion | (20,44) → (20,49), logo acima do jogador | `walk_fast_down x5 > face_left` |

Colunas diferentes → descem juntos. Grito do Silvally → `UBShake` → as duas Ultra
Beasts recuam **um tile de costas**, sem virar o rosto, para (17,50) e (17,51):
`lock_facing_direction > walk_fast_left > unlock_facing_direction`.

"!" sobre Looker, Anabel e Clair.

```text
# BlackthornCity_Text_UBGladionArrives
GLADION
  …Don't just stand
  there.

LOOKER
  And who might YOU be?!

GLADION
  Gladion.

  I saw the light over the
  mountains. Figured someone
  would need help.

CLAIR
  Another Trainer? Fine.
  The more the better!
```

### Beat 6 — A escolha

Estrutura padrão de todas as Rift Missions: `dynmultichoice` com `ignoreBPress =
TRUE` (a cena já começou, não há cancelar). A escolha vale por tentativa — depois
de um blackout o jogador escolhe de novo.

Ninguém precisa virar: jogador (20,50), Silvally (19,50) e Gladion (20,49) já
estão a leste das duas em x=17, e elas olham para leste.

```text
# BlackthornCity_Text_UBChoosePrompt
GLADION
  Two of them.
  Two of us.

  Pick one, {PLAYER}.
  Silvally and I take the other.

CLAIR
  And I'll keep that
  crystal thing busy. Go!
```

Opções do menu: `  Buzzwole` / `  Pheromosa`.
"!" sobre a escolhida, e:

```text
# BlackthornCity_Text_UBPickedBuzzwole
GLADION
  The big one's yours.

  Silvally--the fast one.
  Don't let it get past you!
```

```text
# BlackthornCity_Text_UBPickedPheromosa
GLADION
  Then we take the
  heavy one.

  Silvally, hold the line.
  Nothing gets near the houses.
```

### Beat 7 — A batalha

Boss pelo sistema do projeto, contra a que o jogador escolheu. Captura bloqueada;
**sem** `B_FLAG_NO_WHITEOUT` — perder é blackout e refazer.

Números do chefe (barras, nível, item, golpes, escala entre missões) ficam em
[`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) §6.4 —
fonte única, para os dois docs não divergirem.

Se a batalha não termina em vitória, a cena se desfaz e recomeça do Looker:

```text
# BlackthornCity_Text_UBGotAway
LOOKER
  They pulled back into
  the rift…

  It is not over. Regroup, and
  we try again.
```

---

## Ato 6 — A absorção

A luta do Gladion é narrativa: ela se resolve junto com a vitória do jogador e só
a fala muda com a escolha.

```text
# BlackthornCity_Text_UBGladionFoughtPheromosa
GLADION
  Silvally!

  …Good. It's down.

  Pheromosa was fast.
  Silvally was faster.
```

```text
# BlackthornCity_Text_UBGladionFoughtBuzzwole
GLADION
  That's enough,
  Silvally.

  It hit like a wall. We didn't
  give it an inch.
```

Então — o padrão de **todas** as missões:

1. Necrozma pulsa (`walk_in_place_fast_right x3`) + grito.
2. As duas são **arrastadas de costas** de (17,y) para (15,y), ao lado dele:
   `lock_facing_direction > walk_slow_left x2 > unlock_facing_direction`.
3. `UBShake` → `FADE_TO_WHITE` → `removeobject` das duas → `FADE_FROM_WHITE` → grito.
4. "!" sobre Clair, Gladion, Looker e Anabel.

```text
# BlackthornCity_Text_UBAbsorbed
CLAIR
  What…?
  It's pulling them in!

LOOKER
  It… took them.
  Both of them. Just like that.

GLADION
  It didn't fight them.
  It fed on them.

ANABEL
  That is not how an
  Ultra Beast behaves.

  That is not how anything
  behaves.
```

### Reação opcional à família Cosmog

Checada **depois** da batalha, de propósito: a batalha pode evoluir o Pokémon.
Sem família Cosmog na equipe, a cena segue direto.

Necrozma dá um passo para o jogador, (14,50) → (15,50) — tile livre desde a
remoção do Buzzwole: `walk_slow_right`. "!" sobre o
jogador + grito.

**Cosmog / Cosmoem:**

```text
# BlackthornCity_Text_UBNecrozmaSensesCosmog
  The creature is staring past
  you… at the Poké Ball that
  holds your {STR_VAR_1}.

  Your {STR_VAR_1} is trembling.

GLADION
  Silvally, in front!
  Don't let it closer!
```

**Solgaleo / Lunala:**

```text
# BlackthornCity_Text_UBNecrozmaSensesLegend
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
# BlackthornCity_Text_UBNecrozmaGone
CLAIR
  …It's gone.

  Opened a hole in the sky over
  my town, ate what came out,
  and left.
```

---

## Ato 7 — Conversa, presente e gancho

### Coreografia

| Quem | De → para | Movimento |
|---|---|---|
| Looker | (25,52) → (21,50), olhando oeste | `walk_up x2 > walk_left x4 > face_left` |
| Anabel | (26,52) → (22,51), olhando oeste | `walk_up > walk_left x4 > face_left` |

**Sequencial, nunca junto:** o caminho da Anabel cruza (25,51), que o Looker ocupa
no primeiro passo dele. Depois: Clair e Kingdra viram para leste, Gladion para sul
(o jogador está abaixo dele), Silvally para leste, e o jogador vira para leste.

### A conversa

As pessoas primeiro — Looker pergunta dos feridos antes do relatório.

```text
# BlackthornCity_Text_UBAftermath
LOOKER
  Is anyone hurt?
  {PLAYER}? Your Pokémon?

  …Good. Good. The report can
  wait a moment.

CLAIR
  Blackthorn owes you
  both. You and… Gladion, was it?

  I'll tell the town it's safe.
  Then I'm going to train until
  I understand what I just saw.

ANABEL
  It opened the rift.
  It took the two that came
  through. Then it left.

  It wasn't attacking Blackthorn.
  It was feeding.

GLADION
  …I've seen light like
  that before. In Alola.

LOOKER
  Then we would very much
  like to hear what you know.

GLADION
  Later.
```

Com a família Cosmog na equipe, um bloco a mais:

```text
# BlackthornCity_Text_UBAftermathCosmog
GLADION
  It looked at your
  {STR_VAR_1}. Not at us.

  Keep it close, {PLAYER}.
  I mean it.

ANABEL
  Children of the
  stars… I would like to know
  what that creature wanted
  with one.
```

```text
# BlackthornCity_Text_UBAftermathLegend
GLADION
  It flinched at your
  {STR_VAR_1}. Remember that.

ANABEL
  In Alola, {STR_VAR_1} is a
  legend of the sky itself.

  For something made of light
  to flinch at one… that means
  something.
```

### O presente

O jogador vira para o norte, para o Gladion.

```text
# BlackthornCity_Text_UBGladionGift
GLADION
  {PLAYER}.
  There's something else.

  Two weeks ago I found another
  Type: Null. In the mountains
  past Route 45.

  Alone. Someone left it
  behind. Same as mine.

  It won't settle with me. It
  keeps trying to be Silvally's
  shadow.

  It needs its own Trainer.

  It watched you fight just
  now. …I think it's decided.

  Take care of it.
```

`givemon SPECIES_TYPE_NULL, 50` → fanfarra, apelido e aviso de PC
(`Common_EventScript_GiftMon`).

```text
# BlackthornCity_Text_UBGladionGiftAfter
GLADION
  Don't decide
  everything for it.

  Let it take the first step.
  It'll surprise you.
```

"Don't decide everything for it" é a lição do arco do próprio Gladion (design §3).

Guarda (inalcançável, o espaço foi checado antes do SIM — mas nunca se perde o
presente: cai aqui e a missão é refeita do começo):

```text
# BlackthornCity_Text_UBGiftNoRoom
GLADION
  …You don't have room
  for it. Not in your team, not
  in your Boxes.

  Sort that out. Then we'll do
  this properly.
```

### O gancho

O jogador vira para o leste. **Sem destino** — a Missão 2 só é revelada no
briefing seguinte.

```text
# BlackthornCity_Text_UBHook
ANABEL
  The readings haven't
  settled. That creature will
  open another rift.

  Where, and when, we don't
  know yet.

LOOKER
  So we keep watching.

  Rest, {PLAYER}. Then come to
  our house in Olivine.

  The moment something opens,
  you will be the first to know.

GLADION
  …If it shows up
  again, it won't be alone.

  Silvally. We're going.
```

`FADE_TO_BLACK` → a flag do evento é limpa e o estado vira 4 → `warpsilent` no
mesmo lugar (20,50). A cidade repovoa, o elenco some e as portas destrancam de
uma vez, debaixo do fade.

---

## Apêndice — movimentos, em um lugar só

| Label | Sequência |
|---|---|
| `BlackthornCity_Movement_PlayerToLine` | walk_up x2 > walk_left x5 > face_left |
| `BlackthornCity_Movement_StepUpFaceLeft` | walk_up > face_left |
| `BlackthornCity_Movement_AttackInPlaceLeft` | walk_in_place_fast_left x2 |
| `BlackthornCity_Movement_PulseInPlaceRight` | walk_in_place_fast_right x3 |
| `BlackthornCity_Movement_UBCharge` | walk_fast_right x3 |
| `BlackthornCity_Movement_SilvallyRescue` | walk_faster_down x4 > jump_2_down > face_left |
| `BlackthornCity_Movement_GladionArrive` | walk_fast_down x5 > face_left |
| `BlackthornCity_Movement_UBKnockedBack` | lock_facing_direction > walk_fast_left > unlock_facing_direction |
| `BlackthornCity_Movement_UBPulledIn` | lock_facing_direction > walk_slow_left x2 > unlock_facing_direction |
| `BlackthornCity_Movement_NecrozmaLean` | walk_slow_right |
| `BlackthornCity_Movement_LookerToPlayer` | walk_up x2 > walk_left x4 > face_left |
| `BlackthornCity_Movement_AnabelToPlayer` | walk_up > walk_left x4 > face_left |

**Flash da cena:** `fadescreenswapbuffers FADE_TO_WHITE` / `FADE_FROM_WHITE`, nunca
`fadescreen` — o motivo (e o bug do escurecimento noturno) está no
[`_IMPLEMENTATION`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) §14.

**Tremor da cena** (`UBShake`): `ShakeCamera` com pan 1/1, 12 tremidas, delay 4.
