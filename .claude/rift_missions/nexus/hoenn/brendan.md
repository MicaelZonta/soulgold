# Brendan

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brendan** (Hoenn · Rivais) — protagonista ou rival, filho do Professor Birch.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_BRENDAN_HOENN` | `graphics/object_events/pics/people/special/brendan_hoenn.png` (arte hyo-oppa, 32x32, 12 quadros) — usar este no Nexus |
| `OBJ_EVENT_GFX_LINK_RS_BRENDAN` | `graphics/object_events/pics/people/ruby_sapphire_brendan/walking.png` (antigo, RS) |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RS_BRENDAN` | `graphics/trainers/front_pics/brendan_rs.png` (64x64) + `brendan_rs_large.png` (80x80 hyo-oppa, só na batalha) |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** `OBJ_EVENT_GFX_BRENDAN_*` e `TRAINER_PIC_FRONT_BRENDAN` **não são o Brendan**: neste hack a arte foi trocada pelo protagonista **Gold** (os `TRAINER_RIVALGOLD*` usam essa pic). O Brendan de Hoenn de verdade é a arte de *Ruby/Sapphire* (`RS_`), listada acima. O overworld RS só tem andar/correr (sem bike/surf).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BRENDAN_PLACEHOLDER` | 853 | 0x855 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_401` (ex-`TRAINER_BRENDAN_ROUTE_119_MUDKIP`, 522), `TRAINER_UNUSED_407` (ex-`TRAINER_BRENDAN_ROUTE_103_TREECKO`, 523), `TRAINER_UNUSED_396` (ex-`TRAINER_BRENDAN_ROUTE_110_TREECKO`, 524), `TRAINER_UNUSED_402` (ex-`TRAINER_BRENDAN_ROUTE_119_TREECKO`, 525), `TRAINER_UNUSED_408` (ex-`TRAINER_BRENDAN_ROUTE_103_TORCHIC`, 526), `TRAINER_UNUSED_397` (ex-`TRAINER_BRENDAN_ROUTE_110_TORCHIC`, 527), `TRAINER_UNUSED_403` (ex-`TRAINER_BRENDAN_ROUTE_119_TORCHIC`, 528), `TRAINER_UNUSED_412` (ex-`TRAINER_BRENDAN_RUSTBORO_TREECKO`, 592), `TRAINER_UNUSED_413` (ex-`TRAINER_BRENDAN_RUSTBORO_MUDKIP`, 593), `TRAINER_UNUSED_414` (ex-`TRAINER_BRENDAN_RUSTBORO_TORCHIC`, 599), `TRAINER_UNUSED_418` (ex-`TRAINER_BRENDAN_LILYCOVE_MUDKIP`, 661), `TRAINER_UNUSED_419` (ex-`TRAINER_BRENDAN_LILYCOVE_TREECKO`, 662), `TRAINER_UNUSED_420` (ex-`TRAINER_BRENDAN_LILYCOVE_TORCHIC`, 663).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BRENDAN` = **1012** (flag de batalha `0x8F4`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Brendan_Fight`; campeão: `Nexus_EventScript_Brendan_Jirachi_ChampionFight` (para Jirachi), `Nexus_EventScript_Brendan_Reshiram_ChampionFight` (para Reshiram). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Brendan.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BRENDAN`, campeão do Reshiram e do Jirachi. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Pic `RS Brendan` (`TRAINER_PIC_FRONT_RS_BRENDAN`), a arte de Ruby/Sapphire; a `Brendan` deste hack é o Gold (ver a atenção acima). Lendário **Reshiram**, o dragão da verdade, do qual ele é campeão: o filho do Professor Birch faz pesquisa de campo e só anota o que é verdade. Semi-lendário **Jirachi**, o outro de que é campeão, o Pokémon dos desejos de Hoenn. Mega **Sceptile** (Grasstite), a linha do Treecko, inicial de Hoenn. Mais **Torkoal** (Drought), **Swellow** (o Taillow que o rival sempre carrega em Emerald) e **Hariyama**, todos de Hoenn.

*Plano:* sol. O Torkoal liga o Drought e o Reshiram queima com Blue Flare e Heat Wave; a Mega Sceptile solta Solar Beam sem carregar; o Swellow bate de Guts com Flame Orb; o Jirachi dá Wish e segura o ritmo.
*Plano (Singles):* o Torkoal arma Stealth Rock e limpa hazards com Rapid Spin antes de soltar a Eruption; o Jirachi pivota com U-turn e Wish; o Reshiram de Choice Specs quebra; o Swellow limpa no fim.
*Plano (Doubles):* o formato em que o time brilha. Hariyama dá Fake Out enquanto o Torkoal solta Eruption nos dois oponentes; o Reshiram usa Heat Wave no sol; o Jirachi dá Helping Hand; a Mega Sceptile (Lightning Rod) puxa os golpes Elétricos para longe dos parceiros.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Reshiram | Choice Specs | Turboblaze | Modest | Blue Flare, Draco Meteor, Heat Wave, Earth Power |
| Jirachi | Leftovers | Serene Grace | Careful | Iron Head, Helping Hand, Wish, U-turn |
| Sceptile | Grasstite | Overgrow | Timid | Solar Beam, Dragon Pulse, Focus Blast, Protect |
| Torkoal | Charcoal | Drought | Quiet | Eruption, Heat Wave, Stealth Rock, Rapid Spin |
| Swellow | Flame Orb | Guts | Jolly | Facade, Brave Bird, U-turn, Protect |
| Hariyama | Assault Vest | Thick Fat | Adamant | Fake Out, Close Combat, Knock Off, Heavy Slam |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BRENDAN ===
Name: Brendan
Class: Rival
Pic: RS Brendan
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Reshiram @ Choice Specs
Modest Nature
Level: 100
Ability: Turboblaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blue Flare
- Draco Meteor
- Heat Wave
- Earth Power

Jirachi @ Leftovers
Careful Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Helping Hand
- Wish
- U-turn

Sceptile @ Grasstite
Timid Nature
Level: 100
Ability: Overgrow
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Solar Beam
- Dragon Pulse
- Focus Blast
- Protect

Torkoal @ Charcoal
Quiet Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Eruption
- Heat Wave
- Stealth Rock
- Rapid Spin

Swellow @ Flame Orb
Jolly Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Facade
- Brave Bird
- U-turn
- Protect

Hariyama @ Assault Vest
Adamant Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Knock Off
- Heavy Slam
```

</details>

### Lendário associado

#### Reshiram

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Reshiram_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Reshiram**. Brendan é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brendan, filho do Professor Birch, de Littleroot. Rival em Ruby/Sapphire/Emerald, faz pesquisa de campo para o pai, e depois de perder para o jogador volta a ajudar na pesquisa.

**A criatura.** Reshiram (Dragão/Fogo), o Pokémon da verdade, que ajuda quem quer construir um mundo de verdade. Quando a cauda dele se inflama, o calor movimenta a atmosfera e muda o clima do mundo. Mundo em Black/White: Dragonspiral Tower.

**O fragmento.** Um deserto de cinza branca, debaixo de um céu que queima azul nas bordas. Não há sombra nenhuma: tudo é iluminado de todos os lados ao mesmo tempo, como se nada tivesse permissão de se esconder.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A desert of white ash, under a sky that burned blue at the edges.
>
> There were no shadows. Everything was lit from every side at once, as if nothing here was allowed to hide.

**Boss**

> The heat rose all at once, and the sky itself began to move.
>
> Something white turned its head, and a great tail began to spin, bright as a furnace.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-643. Vast White.
>
> A place where nothing can hide, and a young man who finally stopped hiding one small thing.
>
> What came back with you is small and glows faintly. It glowed brighter when he laughed. I have no explanation.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Reshiram_Arrival:
	.string "A desert of white ash, under a sky that\n"
	.string "burned blue at the edges.\p"
	.string "There were no shadows. Everything was\n"
	.string "lit from every side at once, as if\l"
	.string "nothing here was allowed to hide.$"

Nexus_Text_Reshiram_Boss:
	.string "The heat rose all at once, and the sky\n"
	.string "itself began to move.\p"
	.string "Something white turned its head, and a\n"
	.string "great tail began to spin, bright as a\l"
	.string "furnace.$"

Nexus_Text_Reshiram_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-643. Vast White.\p"
	.string "A place where nothing can hide, and a\n"
	.string "young man who finally stopped hiding\l"
	.string "one small thing.\p"
	.string "What came back with you is small and\n"
	.string "glows faintly. It glowed brighter when\l"
	.string "he laughed. I have no explanation.$"
```

</details>

#### Jirachi

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Jirachi_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Jirachi**. Brendan é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brendan, filho do Professor Birch, de Littleroot. Rival em Ruby/Sapphire/Emerald, faz pesquisa de campo para o pai, e depois de perder para o jogador volta a ajudar na pesquisa.

**A criatura.** Jirachi (Aço/Psíquico) acorda só por sete dias a cada mil anos. Os desejos escritos nas tirinhas de papel da cabeça dele se realizam, e ele tem um terceiro olho na barriga. Ligado a Hoenn pelo Millennium Comet do filme.

**O fragmento.** Um morro debaixo de um cometa que não se move. Tirinhas de papel amarradas em cada folha de grama, milhares, cada uma com um desejo escrito.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A hill, and above it a comet that did not move.
>
> Paper tags were tied to every blade of grass, thousands of them, and each one had a wish written on it.

**Boss**

> The comet flared. One tag tore loose and flew up toward something small and sleeping.
>
> It woke, and the eye on its belly opened last.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-385. Wish.
>
> A hill full of other people's wishes, and a young man who wished for the smallest thing on it.
>
> What came back with you is asleep. It will likely stay asleep a long time. That is how it keeps its promises.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Jirachi_Arrival:
	.string "A hill, and above it a comet that did not\n"
	.string "move.\p"
	.string "Paper tags were tied to every blade of\n"
	.string "grass, thousands of them, and each one\l"
	.string "had a wish written on it.$"

Nexus_Text_Jirachi_Boss:
	.string "The comet flared. One tag tore loose\n"
	.string "and flew up toward something small and\l"
	.string "sleeping.\p"
	.string "It woke, and the eye on its belly opened\n"
	.string "last.$"

Nexus_Text_Jirachi_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-385. Wish.\p"
	.string "A hill full of other people's wishes, and\n"
	.string "a young man who wished for the smallest\l"
	.string "thing on it.\p"
	.string "What came back with you is asleep. It\n"
	.string "will likely stay asleep a long time. That\l"
	.string "is how it keeps its promises.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brendan_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brendan cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey! Hold still a sec, I'm writing this down.
>
> My dad sends me out to record every Pokémon I see. Habitat, height, what it eats.
>
> So what do you eat? …Kidding. Let's battle, I'll take notes after!

**Derrota**

> Huh. You're pretty good. That's going in the notebook, underlined.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Intro:
	.string "Hey! Hold still a sec, I'm writing this\n"
	.string "down.\p"
	.string "My dad sends me out to record every\n"
	.string "Pokémon I see. Habitat, height, what it\l"
	.string "eats.\p"
	.string "So what do you eat? …Kidding. Let's\n"
	.string "battle, I'll take notes after!$"

Nexus_Text_Brendan_Defeat:
	.string "Huh. You're pretty good. That's going\n"
	.string "in the notebook, underlined.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas para as quatro primeiras salas, com ângulos diferentes da variação 1 (que está no jogo). Seguem o [R16](../NEXUS_REGRAS.md): falam dele mesmo, sem o lugar nem a criatura do dia.

**Variação 2** — a casa vazia ao lado (R21: o vizinho que nunca chegou pode ser o jogador, sem depender disso).

**Antes da luta**

> Oh, hey. Sorry, you looked like someone for a second.
>
> There's a house next to mine that's been empty my whole life. Moving truck and everything. Nobody ever got out.
>
> I always figured whoever it was would be a Trainer. A good one. …Let's see if I guessed right!

**Derrota**

> Yep. Guessed right. I'm keeping that page.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Intro2:
	.string "Oh, hey. Sorry, you looked like someone\n"
	.string "for a second.\p"
	.string "There's a house next to mine that's\n"
	.string "been empty my whole life. Moving truck\l"
	.string "and everything. Nobody ever got out.\p"
	.string "I always figured whoever it was would\n"
	.string "be a Trainer. A good one. …Let's see if I\l"
	.string "guessed right!$"

Nexus_Text_Brendan_Defeat2:
	.string "Yep. Guessed right. I'm keeping that\n"
	.string "page.$"
```

</details>

**Variação 3** — humor: o rival que sempre perde e ainda ajuda o vencedor.

**Antes da luta**

> You know what I'm tired of? Losing to people and then helping them with their Pokédex.
>
> Don't laugh. It happens a lot. They beat me, I say 'nice job,' I show them where the good grass is.
>
> Not today. Today I'm keeping the good grass to myself!

**Derrota**

> …Nice job. See? I said it again. I can't help it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Intro3:
	.string "You know what I'm tired of? Losing to\n"
	.string "people and then helping them with their\l"
	.string "Pokédex.\p"
	.string "Don't laugh. It happens a lot. They\n"
	.string "beat me, I say 'nice job,' I show them\l"
	.string "where the good grass is.\p"
	.string "Not today. Today I'm keeping the good\n"
	.string "grass to myself!$"

Nexus_Text_Brendan_Defeat3:
	.string "…Nice job. See? I said it again. I can't\n"
	.string "help it.$"
```

</details>


### Diálogo associado ao lendário

#### Reshiram

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brendan_Reshiram_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brendan é o **campeão**, a luta logo antes do Reshiram. A fala é sobre a criatura, sem dizer o nome dela.

O Brendan leu em três livros que o dragão branco só escuta quem fala a verdade. Então contou tudo o que já viu: cada Pokémon, cada rota. O dragão não ligou; esperava a única coisa que ele deixou de fora. A virada é essa verdade: o Brendan sempre quis ser a pessoa sobre quem os outros escrevem, e virou o cara do caderno, anotando o que o jogador fez. Quando disse isso em voz alta, a cauda do dragão esfriou um pouco.

**Antes da luta**

> That white dragon out there only listens to people who tell the truth. I read that in three different books.
>
> So I tried. I told it everything I've ever seen. Every Pokémon, every route.
>
> It didn't care. I think it was waiting for the one thing I left out.
>
> …Battle first. Truth later.

**Derrota**

> Okay. Okay. There's the truth, I guess.

**Depois da luta**

> Here's what I left out. I always wanted to be the one people write about.
>
> Instead I'm the guy with the notebook, writing down what you did.
>
> I said that out loud to it, and its tail stopped burning so hot. Weird, right?
>
> Anyway. Go on. I'll write this part down properly.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Reshiram_ChampionIntro:
	.string "That white dragon out there only\n"
	.string "listens to people who tell the truth. I\l"
	.string "read that in three different books.\p"
	.string "So I tried. I told it everything I've\n"
	.string "ever seen. Every Pokémon, every route.\p"
	.string "It didn't care. I think it was waiting\n"
	.string "for the one thing I left out.\p"
	.string "…Battle first. Truth later.$"

Nexus_Text_Brendan_Reshiram_ChampionDefeat:
	.string "Okay. Okay. There's the truth, I guess.$"

Nexus_Text_Brendan_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}Here's what I left out. I always wanted\n"
	.string "to be the one people write about.\p"
	.string "Instead I'm the guy with the notebook,\n"
	.string "writing down what you did.\p"
	.string "I said that out loud to it, and its tail\n"
	.string "stopped burning so hot. Weird, right?\p"
	.string "Anyway. Go on. I'll write this part down\n"
	.string "properly.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)); a variação 1 é a que está no jogo.

**Variação 2** — a mentira de teste: o deserto esquenta quando alguém mente.

**Antes da luta**

> Tried an experiment out there. I told the white dragon one tiny lie. Just to see.
>
> I said I'd never lost a battle. The whole desert went hot, like standing in front of an oven.
>
> So, for the record: I lose a lot. Probably about to lose again. Let's go!

**Derrota**

> See? Totally true. Still hot, though.

**Depois da luta**

> Funny thing. Out there, there's no shade anywhere. Nothing gets to hide.
>
> I kept waiting for my shadow to show up. It never did. I don't think it's allowed.
>
> When you go in, don't try to look tougher than you are. It can tell. Trust me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Reshiram_ChampionIntro2:
	.string "Tried an experiment out there. I told\n"
	.string "the white dragon one tiny lie. Just to\l"
	.string "see.\p"
	.string "I said I'd never lost a battle. The\n"
	.string "whole desert went hot, like standing in\l"
	.string "front of an oven.\p"
	.string "So, for the record: I lose a lot.\n"
	.string "Probably about to lose again. Let's go!$"

Nexus_Text_Brendan_Reshiram_ChampionDefeat2:
	.string "See? Totally true. Still hot, though.$"

Nexus_Text_Brendan_Reshiram_ChampionAfter2:
	.string "{SPEAKER NAME_BRENDAN}Funny thing. Out there, there's no\n"
	.string "shade anywhere. Nothing gets to hide.\p"
	.string "I kept waiting for my shadow to show up.\n"
	.string "It never did. I don't think it's allowed.\p"
	.string "When you go in, don't try to look\n"
	.string "tougher than you are. It can tell. Trust\l"
	.string "me.$"
```

</details>

**Variação 3** — o gêmeo: verdade e ideal separados em duas pessoas (aceno à May sem nomeá-la; fio Unova).

**Antes da luta**

> The books say that dragon had a twin. A black one, for people with big dreams.
>
> I only got the white one. The one for people who just… tell it how it is.
>
> Kind of a boring hero, right? Let's make it interesting!

**Derrota**

> Not boring. I'll give you that.

**Depois da luta**

> Sometimes I think the black one ended up with someone I'd have liked. Someone who dreams big and laughs a lot.
>
> Truth and ideals, split up. Two people who never meet.
>
> Weird thing to be sad about. Go on. Tell it I said hi. Truthfully.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Reshiram_ChampionIntro3:
	.string "The books say that dragon had a twin. A\n"
	.string "black one, for people with big dreams.\p"
	.string "I only got the white one. The one for\n"
	.string "people who just… tell it how it is.\p"
	.string "Kind of a boring hero, right? Let's make\n"
	.string "it interesting!$"

Nexus_Text_Brendan_Reshiram_ChampionDefeat3:
	.string "Not boring. I'll give you that.$"

Nexus_Text_Brendan_Reshiram_ChampionAfter3:
	.string "{SPEAKER NAME_BRENDAN}Sometimes I think the black one ended\n"
	.string "up with someone I'd have liked. Someone\l"
	.string "who dreams big and laughs a lot.\p"
	.string "Truth and ideals, split up. Two people\n"
	.string "who never meet.\p"
	.string "Weird thing to be sad about. Go on. Tell\n"
	.string "it I said hi. Truthfully.$"
```

</details>

#### Jirachi

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brendan_Jirachi_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brendan é o **campeão**, a luta logo antes do Jirachi. A fala é sobre a criatura, sem dizer o nome dela.

No morro do cometa, o Brendan leu uns cinquenta desejos pendurados na grama; quase todos eram sobre voltar para casa. Ele escreveu o dele e não quer contar. A virada é que o desejo é pequeno: nem "ser campeão", nem "vencer você", só "quero contar ao meu pai sobre este lugar". É o pesquisador de campo inteiro numa frase. O pedido: se achar a tirinha dele, deixe onde está.

**Antes da luta**

> Up on the hill there's a comet that doesn't move, and paper tags tied to every blade of grass.
>
> Every tag has a wish on it. I read about fifty. Most of them are about going home.
>
> I wrote one too. Don't ask. …Okay, you can ask after I win!

**Derrota**

> Nope. Guess that wish is on hold.

**Depois da luta**

> Fine, my wish. It said: 'I want to tell my dad about this place.'
>
> Not 'be Champion.' Not 'beat you.' Just that.
>
> It only wakes up for a week every thousand years, so hurry. And if you find my tag, leave it where it is.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Jirachi_ChampionIntro:
	.string "Up on the hill there's a comet that\n"
	.string "doesn't move, and paper tags tied to\l"
	.string "every blade of grass.\p"
	.string "Every tag has a wish on it. I read about\n"
	.string "fifty. Most of them are about going\l"
	.string "home.\p"
	.string "I wrote one too. Don't ask. …Okay, you\n"
	.string "can ask after I win!$"

Nexus_Text_Brendan_Jirachi_ChampionDefeat:
	.string "Nope. Guess that wish is on hold.$"

Nexus_Text_Brendan_Jirachi_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}Fine, my wish. It said: 'I want to tell my\n"
	.string "dad about this place.'\p"
	.string "Not 'be Champion.' Not 'beat you.' Just\n"
	.string "that.\p"
	.string "It only wakes up for a week every\n"
	.string "thousand years, so hurry. And if you\l"
	.string "find my tag, leave it where it is.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)); a variação 1 é a que está no jogo.

**Variação 2** — o pesquisador cataloga os desejos (humor).

**Antes da luta**

> I've been cataloging the wishes on the hill. Research habit. Can't stop.
>
> Twelve want money. Forty want to go home. One just says 'more berries.' I respect that one.
>
> My dad would call this great data. Let's add a battle to it!

**Derrota**

> Data point: you're strong. Very consistent result.

**Depois da luta**

> The one that grants them is asleep almost all the time. Seven days awake, then a thousand years of sleep.
>
> Imagine waking up to a hill full of people asking for stuff. I'd go back to sleep too.
>
> So when you meet it, maybe don't ask for anything. Just say good morning.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Jirachi_ChampionIntro2:
	.string "I've been cataloging the wishes on the\n"
	.string "hill. Research habit. Can't stop.\p"
	.string "Twelve want money. Forty want to go\n"
	.string "home. One just says 'more berries.' I\l"
	.string "respect that one.\p"
	.string "My dad would call this great data. Let's\n"
	.string "add a battle to it!$"

Nexus_Text_Brendan_Jirachi_ChampionDefeat2:
	.string "Data point: you're strong. Very\n"
	.string "consistent result.$"

Nexus_Text_Brendan_Jirachi_ChampionAfter2:
	.string "{SPEAKER NAME_BRENDAN}The one that grants them is asleep\n"
	.string "almost all the time. Seven days awake,\l"
	.string "then a thousand years of sleep.\p"
	.string "Imagine waking up to a hill full of\n"
	.string "people asking for stuff. I'd go back to\l"
	.string "sleep too.\p"
	.string "So when you meet it, maybe don't ask\n"
	.string "for anything. Just say good morning.$"
```

</details>

**Variação 3** — os desejos que ele rasgou antes do pequeno (dúvida; liga à casa vazia da variação 2 genérica).

**Antes da luta**

> The comet up there hasn't moved since I got here. Seven days are supposed to go by. They won't start.
>
> I think it's waiting for someone to finish their wish. I keep rewriting mine.
>
> Maybe a battle will help me decide!

**Derrota**

> Okay. Decided. …Not telling you.

**Depois da luta**

> My first wish was 'let me be the hero of something.' I tore it up.
>
> The second was 'let someone move in next door.' Tore that up too. Not fair, asking someone to live somewhere.
>
> The one up there now is small. Small ones come true, I think. Go on. It's awake.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Jirachi_ChampionIntro3:
	.string "The comet up there hasn't moved since\n"
	.string "I got here. Seven days are supposed to\l"
	.string "go by. They won't start.\p"
	.string "I think it's waiting for someone to\n"
	.string "finish their wish. I keep rewriting mine.\p"
	.string "Maybe a battle will help me decide!$"

Nexus_Text_Brendan_Jirachi_ChampionDefeat3:
	.string "Okay. Decided. …Not telling you.$"

Nexus_Text_Brendan_Jirachi_ChampionAfter3:
	.string "{SPEAKER NAME_BRENDAN}My first wish was 'let me be the hero of\n"
	.string "something.' I tore it up.\p"
	.string "The second was 'let someone move in\n"
	.string "next door.' Tore that up too. Not fair,\l"
	.string "asking someone to live somewhere.\p"
	.string "The one up there now is small. Small ones\n"
	.string "come true, I think. Go on. It's awake.$"
```

</details>

Falante novo: `SP_NAME_BRENDAN` (o `_ChampionAfter` usa `{SPEAKER NAME_BRENDAN}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
